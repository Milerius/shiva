if (SHIVA_USE_SFML_AS_RENDERER)
    add_executable(sfml-example sfml-example.cpp sfml-example.hpp)
    add_dependencies(sfml-example shiva::shiva-system-sfml-graphics shiva::shiva-system-sfml-inputs shiva::shiva-system-sfml-resources)
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

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/game_scene.lua
            ${CMAKE_SOURCE_DIR}/bin/assets/scripts/scenes/lua/game_scene.lua
            COPYONLY)
endif()
