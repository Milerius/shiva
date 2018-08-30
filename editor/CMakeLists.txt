file(GLOB_RECURSE SOURCES sources/*.cpp)
add_executable(shiva-editor ${SOURCES})
find_package(imgui CONFIG REQUIRED)
target_link_libraries(shiva-editor PUBLIC shiva::shiva PRIVATE imgui::imgui)
target_include_directories(shiva-editor PUBLIC widgets)
set_target_properties(shiva-editor
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/editor_output"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/editor_output"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/editor_output"
        LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/editor_output"
        LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/editor_output"
        RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/editor_output"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/editor_output"
        PDB_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/editor_output"
        PDB_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/editor_output"
        PDB_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/editor_output")

add_dependencies(shiva-editor
        shiva::shiva-system-sfml-graphics
        shiva::shiva-system-sfml-inputs
        shiva::shiva-system-sfml-resources
        shiva::shiva-system-sfml-animation
        shiva::shiva-system-box2d
        shiva::shiva-system-imgui
        shiva::shiva-system-sfml-video)


#print_target_properties(shiva::shiva-system-box2d)

add_custom_command(TARGET shiva-editor POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE} ${CMAKE_SOURCE_DIR}/editor_output/${CMAKE_BUILD_TYPE})