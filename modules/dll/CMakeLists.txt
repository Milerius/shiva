include(CMakeSources.cmake)
set(MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

CREATE_MODULE(shiva::dll "${MODULE_SOURCES}" ${MODULE_PATH})

find_package(Boost COMPONENTS system REQUIRED)

##! EASTL
find_library(EASTL_LIBRARY EASTL)
message(STATUS "${EASTL_LIBRARY}")

target_link_libraries(dll INTERFACE Boost::boost ${CMAKE_DL_LIBS} ${EASTL_LIBRARY} shiva::filesystem)

AUTO_TARGETS_MODULE_INSTALL(dll)