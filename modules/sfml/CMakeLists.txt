set(CMAKE_POSITION_INDEPENDENT_CODE ON)
macro(mini_module module_name additional_library)
    include(shiva/sfml/${module_name}/CMakeSources.cmake)
    set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
    CREATE_MODULE_PLUGIN(shiva::system-sfml-${module_name} "${MODULE_SOURCES}" ${MODULE_PATH} "systems" "sfml/shiva")
    target_link_libraries(system-sfml-${module_name} PUBLIC shiva::ecs shiva::sfml-event PUBLIC ${additional_library})
    AUTO_TARGETS_PLUGINS_INSTALL(system-sfml-${module_name} shiva-sfml)
endmacro()

if (SHIVA_USE_SFML_AS_RENDERER)
    include(shiva/sfml/event/CMakeSources.cmake)
    set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
    CREATE_MODULE(shiva::sfml-event "${MODULE_SOURCES}" ${MODULE_PATH})

    AUTO_TARGETS_MODULE_INSTALL(sfml-event)

    if (LINUX OR WIN32)
        set(SFML_STATIC_LIBRARIES TRUE)
    endif()

    find_package(SFML CONFIG REQUIRED system window graphics audio)

    mini_module(graphics sfml-graphics)
    mini_module(inputs shiva::system-sfml-graphics)

    #set_target_properties(system-sfml-inputs PROPERTIES LINK_FLAGS "-undefined dynamic_lookup")

    PREPARE_MODULE_INSTALLATION(shiva-sfml)
endif ()
