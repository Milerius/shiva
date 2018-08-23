if (SHIVA_USE_IMGUI)
    find_package(imgui CONFIG REQUIRED)
    include(CMakeSources.cmake)
    set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
    CREATE_MODULE_PLUGIN(shiva::shiva-system-imgui "${MODULE_SOURCES}" ${MODULE_PATH} "systems" "imgui/shiva")
    target_link_libraries(shiva-system-imgui PRIVATE shiva::ecs imgui::imgui shiva::lua)
    target_compile_options(shiva-system-imgui
            PRIVATE $<$<CXX_COMPILER_ID:Clang>:-Wno-conditional-uninitialized -Wno-unused-variable -Wno-double-promotion -Wno-shadow -Wno-conversion -Wno-old-style-cast -Wno-zero-as-null-pointer-constant -Wno-missing-prototypes -Wno-missing-variable-declarations -Wno-unused-macros>
            PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/wd4189 /wd4701 /wd4459>)
    AUTO_TARGETS_PLUGINS_INSTALL(shiva-system-imgui shiva-imgui)
    PREPARE_MODULE_INSTALLATION(shiva-imgui)
endif()