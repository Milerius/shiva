macro(CREATE_MODULE ModuleAlias LibSources BuildInterfaceDirectory)
    MSG_CYAN_BOLD(STATUS "Creating Module:" "${ModuleAlias}" "")
    string(REPLACE "::" "-" ModuleName ${ModuleAlias})
    string(REPLACE "::" ";" ListArg ${ModuleAlias})
    list(GET ListArg 1 RealModuleName)
    add_library(${ModuleName} INTERFACE)
    target_sources(${ModuleName} INTERFACE ${LibSources})
    target_include_directories(${ModuleName} INTERFACE
            $<BUILD_INTERFACE:${BuildInterfaceDirectory}>
            $<INSTALL_INTERFACE:${PROJECT_NAME}/${RealModuleName}>)
    add_library(${ModuleAlias} ALIAS ${ModuleName})
    MSG_CYAN_BOLD(STATUS "Module" "${ModuleAlias}" "successfully created.")
endmacro()