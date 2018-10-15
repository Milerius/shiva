#set(CMAKE_POSITION_INDEPENDENT_CODE OFF)

macro(mini_module module_name additional_library)
    include(shiva/sfml/${module_name}/CMakeSources.cmake)
    set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
    CREATE_MODULE_PLUGIN(shiva::shiva-system-sfml-${module_name} "${MODULE_SOURCES}" ${MODULE_PATH} "systems" "sfml/shiva")
    target_link_libraries(shiva-system-sfml-${module_name} PUBLIC shiva::ecs "${additional_library}")
    AUTO_TARGETS_PLUGINS_INSTALL(shiva-system-sfml-${module_name} shiva-sfml)
endmacro()

if (SHIVA_USE_SFML_AS_RENDERER)
    ##! Find SFML
    find_package(SFML CONFIG REQUIRED system window graphics audio)

    ##! Common
    include(shiva/sfml/common/CMakeSources.cmake)
    CREATE_MODULE(shiva::sfml-common "${MODULE_SOURCES}" ${MODULE_PATH})
    target_link_libraries(sfml-common INTERFACE sfml-graphics shiva::json)
    AUTO_TARGETS_PLUGINS_INSTALL(sfml-common shiva-sfml)

    ##! IMGUI
    find_package(sfml-imgui CONFIG REQUIRED)

    ##! Plugins
    mini_module(resources "sfml-graphics;sfml-audio;shiva::lua;sfml-common")
    mini_module(animation "sfml-graphics;sfml-common;shiva::lua")
    mini_module(graphics "sfml-graphics;shiva::json;sfml-imgui::sfml-imgui;shiva::lua")
    mini_module(inputs "sfml-graphics;sfml-imgui::sfml-imgui")

    ##! SFEMOVIE
    if(NOT SFEMOVIE_LIBRARY)
        find_library(SFEMOVIE_LIBRARY_RELEASE NAMES sfeMovie)
        MARK_AS_ADVANCED(SFEMOVIE_LIBRARY_RELEASE)

        find_library(SFEMOVIE_LIBRARY_DEBUG NAMES sfeMovie-d)
        MARK_AS_ADVANCED(SFEMOVIE_LIBRARY_DEBUG)

        include(SelectLibraryConfigurations)
        select_library_configurations(SFEMOVIE)
    endif()
    message("sfeMovie library -> ${SFEMOVIE_LIBRARY}")
    FIND_PATH(SFEMOVIE_INCLUDE_DIR sfeMovie/Movie.hpp)
    message("sfeMovie header -> ${SFEMOVIE_INCLUDE_DIR}")
    mini_module(video "sfml-graphics;shiva::lua")
    target_include_directories(shiva-system-sfml-video PUBLIC ${SFEMOVIE_INCLUDE_DIR})
    target_link_libraries(shiva-system-sfml-video PUBLIC ${SFEMOVIE_LIBRARY})
    target_include_directories(shiva-system-sfml-resources PUBLIC ${SFEMOVIE_INCLUDE_DIR})
    target_link_libraries(shiva-system-sfml-resources PUBLIC ${SFEMOVIE_LIBRARY})


    PREPARE_MODULE_INSTALLATION(shiva-sfml)
endif ()
