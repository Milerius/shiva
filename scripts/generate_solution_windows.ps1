function remove_old_build
{
    Remove-Item build -Recurse -ErrorAction Ignore
}

function prepare_solution()
{
    mkdir build
    cd build
    cmake -DCMAKE_BUILD_TYPE="Debug" -DSHIVA_BUILD_TESTS=ON -DSHIVA_BUILD_EXAMPLES=ON -G "Visual Studio 15 2017 Win64" -DCMAKE_TOOLCHAIN_FILE="$($env:VCPKG_ROOT)/scripts/buildsystems/vcpkg.cmake" ../
    cd ..
}

remove_old_build
prepare_solution
