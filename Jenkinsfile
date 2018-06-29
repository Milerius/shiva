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
        sh '''cd build
ctest --no-compress-output -T Test -D ExperimentalMemCheck || exit 1

cd ../bin
for i in *-test; do
	./$i --gtest_output="xml:${i}-${TYPE}-result.xml" || exit 1
done
cd ..'''
      }
    }
    stage('Coverage') {
      steps {
        sh '''coveralls --gcov gcov-7 --gcov-options \'\\-lp\' --root $PWD --build-root $PWD/build --extension cpp --extension hpp --include modules
'''
      }
    }
  }
  environment {
    PATH = '/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/var/lib/jenkins:/var/lib/jenkins/.local/bin'
    COVERALLS_REPO_TOKEN = 'bVhcCed4om8PxhwUhYamyapXQQ8D4F7IX'
  }
}