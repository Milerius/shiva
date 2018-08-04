######## PREREQUISITES #######
set(TEST_PATH ${CORE_MODULE_PATH}/tests)
set(CURRENT_UNIT_TEST "")
set(NB_TESTS 1)
set(CURRENT_SUCCESS_TEST 0)

macro(__internal_cmake_unit_test_begin NAME)
    set(CURRENT_UNIT_TEST "${NAME}")
    MSG_YELLOW_BOLD(STATUS "################## TESTING FEATURES:" "${NAME}" "##################################")
endmacro()

macro(__internal_cmake_unit_test_result RESULT)
    MSG_YELLOW_BOLD(STATUS "################## TESTING ${CURRENT_UNIT_TEST} FEATURES RESULT:" "${RESULT}" "##################")
    set(CURRENT_UNIT_TEST "")
    if ("${RESULT}" STREQUAL "SUCCESS")
        MATH(EXPR CURRENT_SUCCESS_TEST "${CURRENT_SUCCESS_TEST}+1")
    endif ()
endmacro()
##############################

#########FEATURES#############
include(${CORE_MODULE_PATH}/color.cmake)
#############################


########TEST##################
include(${TEST_PATH}/test_color.cmake)
__internal_cmake_unit_test_begin("COLOR")
TEST_GLOBAL_COLOR()
TEST_SPECIFIC_COLORS()
TEST_ALL_COLOR()
__internal_cmake_unit_test_result("SUCCESS")
##############################

#####END OF TESTS#############
MSG_YELLOW_BOLD(STATUS "Tests results: " "${CURRENT_SUCCESS_TEST} / ${NB_TESTS}" "")
##############################
