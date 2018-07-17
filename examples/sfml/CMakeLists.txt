if (SHIVA_USE_SFML_AS_RENDERER)
    add_executable(sfml-example sfml-example.cpp sfml-example.hpp)
    add_dependencies(sfml-example shiva::system-sfml-graphics shiva::system-sfml-inputs)
    target_compile_options(sfml-example PUBLIC -fvisibility=default)
    target_link_libraries(sfml-example shiva::shiva)
    set_target_properties(sfml-example
            PROPERTIES
            ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
            LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin"
            LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin"
            RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin"
            RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin"
            PDB_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
            PDB_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin"
            PDB_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin")
endif()
