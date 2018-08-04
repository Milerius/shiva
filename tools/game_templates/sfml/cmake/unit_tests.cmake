include(GoogleTest)

###################### INTERNAL ####################################
macro(__internal_specific_unit_test_platform_configuration EXECUTABLE_NAME)
    if (WIN32)
        target_compile_definitions(${EXECUTABLE_NAME} PRIVATE _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING)
        ##DLL BASE CLASS WARNING SUPPRESION
        set_target_properties(${EXECUTABLE_NAME} PROPERTIES COMPILE_FLAGS "${CMAKE_CXX_FLAGS} /wd4251 /wd4275")
    endif (WIN32)
    if (CLANG)
        set_target_properties(${EXECUTABLE_NAME} PROPERTIES COMPILE_FLAGS "${CMAKE_CXX_FLAGS} -Wno-global-constructors")
    endif()
endmacro()

macro(__internal_specific_unit_test_properties EXECUTABLE_NAME)
    set_target_properties(${EXECUTABLE_NAME}
            PROPERTIES
            ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
            LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/lib"
            LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/lib"
            RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin"
            RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin"
            VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
            PDB_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
            PDB_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin"
            PDB_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin")
endmacro()
###################### INTERNAL ####################################

macro(CREATE_UNIT_TEST EXECUTABLE_NAME PREFIX_NAME SOURCES)
    add_executable(${EXECUTABLE_NAME} ${SOURCES})
    target_link_libraries(${EXECUTABLE_NAME} GTest::GTest GTest::Main)
    __internal_specific_unit_test_platform_configuration(${EXECUTABLE_NAME})
    __internal_specific_unit_test_properties(${EXECUTABLE_NAME})
    if (NOT EMSCRIPTEN)
        gtest_discover_tests(${EXECUTABLE_NAME} WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/bin TEST_PREFIX ${PREFIX_NAME} TIMEOUT 5)
    endif()
endmacro()
