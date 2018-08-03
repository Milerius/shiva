cmake_minimum_required(VERSION 3.12)
project(<project_name>)

set(CMAKE_CXX_STANDARD 17)

find_package(shiva CONFIG REQUIRED)

find_package(shiva-sfml CONFIG REQUIRED)

add_executable(<project_name> main.cpp)

target_link_libraries(<project_name>
        shiva::shiva)