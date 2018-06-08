include(CMakeSources.cmake)
set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})


CREATE_MODULE(shiva::event "${MODULE_SOURCES}" ${MODULE_PATH})
target_include_directories(shiva-event INTERFACE shiva::entt)