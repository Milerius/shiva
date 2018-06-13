#!/usr/bin/env bash

mkdir build
cd build
rm -rf *
cmake -DCMAKE_TOOLCHAIN_FILE="/var/lib/jenkins/vcpkg/scripts/buildsystems/vcpkg.cmake" -DCMAKE_BUILD_TYPE="Debug" -DCMAKE_CXX_COMPILER=g++-7 -DCMAKE_C_COMPILER=gcc-7 -DSHIVA_BUILD_TESTS=ON -DSHIVA_BUILD_EXAMPLES=ON -DPROJECT_COVERAGE=1 ..
make -j8
ctest --no-compress-output -T Test -D ExperimentalMemCheck || exit 1
cd ../bin
for i in *-test; do
	./$i --gtest_output="xml:${i}-${TYPE}-result.xml" || exit 1
done
cd ..
mkdir -p test-result/ctest
cp bin/*.xml test-result/
cp build/Testing/*/*.xml test-result/ctest/
