include(CMakeSources.cmake)
set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
CREATE_MODULE(shiva::ruby "${MODULE_SOURCES}" ${MODULE_PATH})

find_package(Ruby)

if (Ruby_FOUND)
    message("Ruby version is ${RUBY_VERSION}")
    message("Ruby include directory is ${RUBY_INCLUDE_DIR}")
else ()
    message(ERROR "Ruby not found")
endif ()

target_link_libraries(ruby INTERFACE shiva::ecs)
target_include_directories(ruby INTERFACE ${RUBY_INCLUDE_DIR})

AUTO_TARGETS_MODULE_INSTALL(ruby)
