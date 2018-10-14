include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

macro(CREATE_MODULE ModuleAlias LibSources BuildInterfaceDirectory)
    MSG_CYAN_BOLD(STATUS "Creating Module:" "${ModuleAlias}" "")
    string(REPLACE "::" "-" ModuleName ${ModuleAlias})
    string(REPLACE "::" ";" ListArg ${ModuleAlias})
    list(GET ListArg 1 RealModuleName)
    add_library(${RealModuleName} INTERFACE)
    if (USE_PROJECT_IN_AN_IDE)
        target_sources(${RealModuleName} INTERFACE ${LibSources})
    endif ()

    set(ExtraMacroArgs ${ARGN})

    set(INSTALL_MODULE_NAME_DIRECTORY "${RealModuleName}")
    # Get the length of the list
    list(LENGTH ExtraMacroArgs NumExtraMacroArgs)

    # Execute the following block only if the length is > 0
    if(NumExtraMacroArgs GREATER 0)
        message(STATUS ">>> First optional arg = \"${ARGV2}\"")
        foreach(ExtraArg ${ExtraMacroArgs})
            message(STATUS ">>> Element of list of opt args = ${ExtraArg}")
            set(INSTALL_MODULE_NAME_DIRECTORY "${ExtraArg}")
        endforeach()
    endif()

    target_include_directories(${RealModuleName} INTERFACE
            $<BUILD_INTERFACE:${BuildInterfaceDirectory}>
            $<INSTALL_INTERFACE:include/shiva/modules/${INSTALL_MODULE_NAME_DIRECTORY}>)
    add_library(${ModuleAlias} ALIAS ${RealModuleName})
    MSG_CYAN_BOLD(STATUS "Module" "${ModuleAlias}" "successfully created.")
endmacro()

macro(CREATE_MODULE_PLUGIN ModuleAlias LibSources BuildInterfaceDirectory OutputDirectory InstallPath)
    MSG_CYAN_BOLD(STATUS "Creating Module Plugin:" "${ModuleAlias}" "")
    string(REPLACE "::" "-" ModuleName ${ModuleAlias})
    string(REPLACE "::" ";" ListArg ${ModuleAlias})
    list(GET ListArg 1 RealModuleName)
    add_library(${RealModuleName} SHARED ${LibSources})
    target_include_directories(${RealModuleName} PUBLIC
            $<BUILD_INTERFACE:${BuildInterfaceDirectory}>
            $<INSTALL_INTERFACE:include/shiva/modules/${InstallPath}>)
    add_library(${ModuleAlias} ALIAS ${RealModuleName})

    set_property(TARGET ${RealModuleName} PROPERTY POSITION_INDEPENDENT_CODE ON)
    set_target_properties(${RealModuleName}
            PROPERTIES
            ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/${OutputDirectory}"
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/${OutputDirectory}"
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/${OutputDirectory}"
            LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/${OutputDirectory}"
            LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/${OutputDirectory}"
            RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/${OutputDirectory}"
            RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/${OutputDirectory}")
    MSG_CYAN_BOLD(STATUS "Plugin module" "${ModuleAlias}" "successfully created.")
endmacro()

macro(AUTO_TARGETS_MODULE_INSTALL MODULE_NAME)
    if (NOT USE_PROJECT_IN_AN_IDE)
        install(TARGETS
                ${MODULE_NAME}
                EXPORT ${PROJECT_NAME}-${MODULE_NAME}-targets
                RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
                ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
                LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
                INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
                )

        install(EXPORT ${PROJECT_NAME}-${MODULE_NAME}-targets
                NAMESPACE ${PROJECT_NAME}::
                DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
                )
    endif ()
endmacro()

macro(AUTO_TARGETS_PLUGINS_INSTALL MODULE_NAME EXPORT_NAME)
    if (NOT USE_PROJECT_IN_AN_IDE)
        include(GNUInstallDirs)

        include(CMakePackageConfigHelpers)

        install(TARGETS
                ${MODULE_NAME}
                EXPORT ${PROJECT_NAME}-${MODULE_NAME}-targets
                RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/${PROJECT_NAME}/plugins/${EXPORT_NAME}/${CMAKE_BUILD_TYPE}
                ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME}/plugins/${EXPORT_NAME}/${CMAKE_BUILD_TYPE}
                LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME}/plugins/${EXPORT_NAME}/${CMAKE_BUILD_TYPE}
                INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
                )

        install(EXPORT ${PROJECT_NAME}-${MODULE_NAME}-targets
                NAMESPACE ${PROJECT_NAME}::
                DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${EXPORT_NAME}
                )
    endif ()
endmacro()

macro(PREPARE_MODULE_INSTALLATION EXPORT_NAME)
    configure_package_config_file(
            "${PROJECT_SOURCE_DIR}/cmake/${EXPORT_NAME}-config.cmake.in"
            "${PROJECT_BINARY_DIR}/${EXPORT_NAME}-config.cmake"
            INSTALL_DESTINATION lib/cmake/${EXPORT_NAME}
    )

    install(FILES
            "${PROJECT_BINARY_DIR}/${EXPORT_NAME}-config.cmake"
            DESTINATION lib/cmake/${EXPORT_NAME})
endmacro()
