mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug -DSHIVA_BUILD_TESTS=ON -DSHIVA_BUILD_EXAMPLES=ON -G "Visual Studio 15 2017 Win64" -DCMAKE_TOOLCHAIN_FILE=C:/Users/milerius/vcpkg/scripts/buildsystems/vcpkg.cmake ..
cmake --build . --config Debug -- /verbosity:minimal /maxcpucount:3
ctest --no-compress-output -T Test -C Debug
cd ../bin
$filePattern = '*-test.exe'
foreach ($file in get-ChildItem $filePattern)
{
    $var = $file.name
    & ./$var --gtest_output="xml:$var-result.xml"
}
cd ..
mkdir test-result
cd test-result
mkdir ctest
cd ..
cp bin/*.xml test-result
cp build/Testing/*/*.xml test-result/ctest