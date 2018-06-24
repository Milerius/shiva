set(CMAKE_POSITION_INDEPENDENT_CODE ON)
macro(generate_local_plugin SOURCES EXECUTABLE)
    add_library(${EXECUTABLE} SHARED "${SOURCES}")
    target_link_libraries(${EXECUTABLE} shiva::world)
    set_property(TARGET ${EXECUTABLE} PROPERTY POSITION_INDEPENDENT_CODE ON)
    set_target_properties(${EXECUTABLE}
            PROPERTIES
            ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/systems_test"
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/systems_test"
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/systems_test"
            LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin/systems_test"
            LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin/systems_test"
            RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin/systems_test"
            RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin/systems_test")
endmacro()

set(SOURCES ecs-test.cpp)
CREATE_UNIT_TEST(ecs-test shiva: "${SOURCES}")

generate_local_plugin("plugins/system_plugged_bar.hpp;plugins/system_plugged_bar.cpp" system-plugin-bar)

target_link_libraries(ecs-test shiva::world)
add_dependencies(ecs-test system-plugin-bar)

magic_source_group(ecs-test)
