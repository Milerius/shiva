//
// Created by roman Sztergbaum on 15/06/2018.
//

#include "sfml-example.hpp"

int main()
{
    int res = 0;
    try {
        SetDllDirectoryA((shiva::fs::current_path() /= "systems").string().c_str());
        spdlog::set_pattern("[%n][%r][pid: %P][%^%l%$]: %v");
        shiva::examples::sfml::example_world world;
        res = world.run();
    }
    catch (...) {

    }
    return res;
}