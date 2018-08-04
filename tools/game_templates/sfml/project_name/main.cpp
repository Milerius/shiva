#include "world/<project_name>_world.hpp"

int main()
{
    int res = 0;
    try {
#if defined(DEBUG)
        spdlog::set_level(spdlog::level::debug);
#endif
        spdlog::set_pattern("[%n][%r][pid: %P][%^%l%$]: %v");
        <project_name>::world world;
        res = world.run();
    }
    catch (const std::exception &error) {
        std::cerr << error.what() << std::endl;
    }
    return res;
}