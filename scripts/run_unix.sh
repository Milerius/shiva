#!/usr/bin/env bash

mkdir -p build && cd build
cmake -DCMAKE_TOOLCHAIN_FILE=${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake -DCMAKE_BUILD_TYPE=Release -DSHIVA_BUILD_TESTS=ON -DSHIVA_BUILD_EXAMPLES=ON ..
make -j
#ctest --no-compress-output -T Test -D ExperimentalMemCheck || exit 1
ctest --no-compress-output -T Test -C Release
cd ../bin
for i in *-test; do
	./$i --gtest_output="xml:${i}-Release-result.xml" || exit 1
    done
    cd ..
    mkdir -p test-result/ctest
    cp bin/*.xml test-result/
cp build/Testing/*/*.xml test-result/ctest/
#rm -rf Testing
#rm -rf build
#rm -rf test-result