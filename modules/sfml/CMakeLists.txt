#set(CMAKE_POSITION_INDEPENDENT_CODE OFF)

macro(mini_module module_name additional_library)
    include(shiva/sfml/${module_name}/CMakeSources.cmake)
    set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
    CREATE_MODULE_PLUGIN(shiva::shiva-system-sfml-${module_name} "${MODULE_SOURCES}" ${MODULE_PATH} "systems" "sfml/shiva")
    target_link_libraries(shiva-system-sfml-${module_name} PUBLIC shiva::ecs "${additional_library}")
    AUTO_TARGETS_PLUGINS_INSTALL(shiva-system-sfml-${module_name} shiva-sfml)
endmacro()

if (SHIVA_USE_SFML_AS_RENDERER)
    find_package(SFML CONFIG REQUIRED system window graphics audio)

    include(shiva/sfml/common/CMakeSources.cmake)
    CREATE_MODULE(shiva::sfml-common "${MODULE_SOURCES}" ${MODULE_PATH})
    target_link_libraries(sfml-common INTERFACE sfml-graphics shiva::json)
    AUTO_TARGETS_PLUGINS_INSTALL(sfml-common shiva-sfml)

    mini_module(resources "sfml-graphics;sfml-audio;shiva::lua;sfml-common")
    mini_module(animation "sfml-graphics;sfml-common;shiva::lua")
    mini_module(graphics "sfml-graphics;shiva::json")
    mini_module(inputs sfml-graphics)
    PREPARE_MODULE_INSTALLATION(shiva-sfml)
endif ()
