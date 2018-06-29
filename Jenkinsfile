pipeline {
  agent {
    node {
      label 'master'
    }

  }
  stages {
    stage('Build') {
      steps {
        sh 'git submodule update --init --recursive'
        sh '''mkdir build
cd build
rm -rf *
cmake -DCMAKE_TOOLCHAIN_FILE="/var/lib/jenkins/vcpkg/scripts/buildsystems/vcpkg.cmake" -DCMAKE_BUILD_TYPE="Debug" -DCMAKE_CXX_COMPILER=g++-7 -DCMAKE_C_COMPILER=gcc-7 -DSHIVA_BUILD_TESTS=ON -DSHIVA_BUILD_EXAMPLES=ON -DPROJECT_COVERAGE=1 ..
make -j8'''
      }
    }
    stage('Unit Tests') {
      steps {
        sh '''ls && pwd
ctest --no-compress-output -T Test -D ExperimentalMemCheck || exit 1

cd ../bin
for i in *-test; do
	./$i --gtest_output="xml:${i}-${TYPE}-result.xml" || exit 1
done
cd ..'''
      }
    }
  }
}