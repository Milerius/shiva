###### CTest ######
include(CTest)
###################

###### GTest ######
find_package(GTest REQUIRED)

###################
SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR})
foreach(subdir ${SUBDIRS})
    ADD_SUBDIRECTORY(${subdir})
endforeach()
