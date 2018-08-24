if (SHIVA_USE_SFML_AS_RENDERER AND SHIVA_USE_BOX2D AND SHIVA_USE_IMGUI)
    add_executable(sfml-example sfml-example.cpp sfml-example.hpp)
    add_dependencies(sfml-example
            shiva::shiva-system-sfml-graphics
            shiva::shiva-system-sfml-inputs
            shiva::shiva-system-sfml-resources
            shiva::shiva-system-sfml-animation
            shiva::shiva-system-box2d
            shiva::shiva-system-imgui
            shiva::shiva-system-sfml-video)
    target_link_libraries(sfml-example shiva::shiva)
    ## uncomment to get templated generated
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Xclang -ast-print -fsyntax-only")
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

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/sprite_scene.lua
            ${CMAKE_SOURCE_DIR}/bin/assets/scripts/scenes/lua/sprite_scene.lua
            COPYONLY)

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/sfml_config.json
            ${CMAKE_SOURCE_DIR}/bin/assets/cfg/sfml_config.json
            COPYONLY)

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/bheet_arrival.json
            ${CMAKE_SOURCE_DIR}/bin/assets/cfg/anim_cfg/game_scene/bheet_arrival.json
            COPYONLY)


    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/player.lua
            ${CMAKE_SOURCE_DIR}/bin/assets/scripts/lua/player.lua
            COPYONLY)

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/intro_scene.lua
            ${CMAKE_SOURCE_DIR}/bin/assets/scripts/scenes/lua/intro_scene.lua
            COPYONLY)

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/intro.avi
            ${CMAKE_SOURCE_DIR}/bin/assets/videos/intro_scene/intro.avi
            COPYONLY)

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/kirito.png
            ${CMAKE_SOURCE_DIR}/bin/assets/textures/game_scene/kirito.png
            COPYONLY)

    magic_source_group(sfml-example)
    magic_source_group(shiva::shiva-system-sfml-graphics)
    magic_source_group(shiva::shiva-system-sfml-inputs)
    magic_source_group(shiva::shiva-system-sfml-resources)
    magic_source_group(shiva::shiva-system-sfml-animation)
    magic_source_group(shiva::shiva-system-box2d)
    magic_source_group(shiva::shiva-system-imgui)
    magic_source_group(shiva::shiva-system-sfml-video)
endif ()
