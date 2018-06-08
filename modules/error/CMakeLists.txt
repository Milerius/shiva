include(CMakeSources.cmake)
set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
CREATE_MODULE(shiva::error "${MODULE_SOURCES}" ${MODULE_PATH})
target_link_libraries(shiva-error INTERFACE shiva::stacktrace shiva::filesystem shiva::entt)