option(TEST_CMAKE_PERSONAL_FEATURES "test personal cmake features" OFF)

if (TEST_CMAKE_PERSONAL_FEATURES)
    include(${CMAKE_MODULE_PATH}/test_features.cmake)
endif()

include(${CMAKE_MODULE_PATH}/buildtype.cmake)
include(${CMAKE_MODULE_PATH}/color.cmake)
include(${CMAKE_MODULE_PATH}/platform.cmake)
include(${CMAKE_MODULE_PATH}/compiler.cmake)
include(${CMAKE_MODULE_PATH}/unit_tests.cmake)
include(${CMAKE_MODULE_PATH}/directory.cmake)
include(${CMAKE_MODULE_PATH}/module.cmake)
