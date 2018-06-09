function update_solution()
{
    cd build
    cmake -DCMAKE_BUILD_TYPE="Debug" -DSHIVA_BUILD_TESTS=ON -DSHIVA_BUILD_EXAMPLES=ON -G "Visual Studio 15 2017 Win64" -DCMAKE_TOOLCHAIN_FILE="$($env:VCPKG_ROOT)/scripts/buildsystems/vcpkg.cmake" ../
    cd ..
}

update_solution