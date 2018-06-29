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
      parallel {
        stage('Unit Tests') {
          steps {
            sh 'echo "Running Tests"'
          }
        }
        stage('CTest') {
          steps {
            sh '''cd build
ctest --no-compress-output -T Test -D ExperimentalMemCheck -j 5 || exit 1'''
          }
        }
        stage('GoogleTest') {
          steps {
            sh '''cd bin
for i in *-test; do
	./$i --gtest_output="xml:${i}-${TYPE}-result.xml" || exit 1
done'''
          }
        }
      }
    }
    stage('Coverage') {
      parallel {
        stage('Coverage') {
          steps {
            sh '''coveralls --gcov gcov-7 --gcov-options \'\\-lp\' --root $PWD --build-root $PWD/build --extension cpp --extension hpp --include modules
'''
          }
        }
        stage('Copy Tests results') {
          steps {
            sh '''mkdir -p test-result/ctest
cp bin/*.xml test-result/
cp build/Testing/*/*.xml test-result/ctest/'''
          }
        }
      }
    }
    stage('Publish Results') {
      steps {
                sh '''echo "lol"'''
            }
            post {
                always {
                    step([$class: 'XUnitBuilder',
                        thresholds: [
                            [$class: 'SkippedThreshold', failureThreshold: '0'],
                            // Allow for a significant number of failures
                            // Keeping this threshold so that overwhelming failures are guaranteed
                            //     to still fail the build
                            [$class: 'FailedThreshold', failureThreshold: '10']],
                        tools: [[$class: 'CTest', pattern: 'test-result/ctest/*.xml']]])
                }
            }
      }
    }
    environment {
      PATH = '/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/var/lib/jenkins:/var/lib/jenkins/.local/bin'
      COVERALLS_REPO_TOKEN = 'bVhcCed4om8PxhwUhYamyapXQQ8D4F7IX'
    }
  }
