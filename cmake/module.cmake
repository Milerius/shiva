include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

macro(CREATE_MODULE ModuleAlias LibSources BuildInterfaceDirectory)
    MSG_CYAN_BOLD(STATUS "Creating Module:" "${ModuleAlias}" "")
    string(REPLACE "::" "-" ModuleName ${ModuleAlias})
    string(REPLACE "::" ";" ListArg ${ModuleAlias})
    list(GET ListArg 1 RealModuleName)
    add_library(${RealModuleName} INTERFACE)
    if (USE_CLION_AS_IDE)
        target_sources(${RealModuleName} INTERFACE ${LibSources})
    endif ()
    target_include_directories(${RealModuleName} INTERFACE
            $<BUILD_INTERFACE:${BuildInterfaceDirectory}>
            $<INSTALL_INTERFACE:include/shiva/modules/${RealModuleName}>)
    add_library(${ModuleAlias} ALIAS ${RealModuleName})
    MSG_CYAN_BOLD(STATUS "Module" "${ModuleAlias}" "successfully created.")
endmacro()

macro(AUTO_TARGETS_MODULE_INSTALL MODULE_NAME)
    if (NOT USE_CLION_AS_IDE)
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