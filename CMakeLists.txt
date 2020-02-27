#####################################
#
#	Authors:
#	1. Ramanathan Arun - ra831@scarletmail.rutgers.edu
#	2. Sri Harsha -
#
#####################################

cmake_minimum_required (VERSION 3.5.0)

#######
# Project name
######

project (A_Star)

#######
# Set necessary flags
######

set(CMAKE_CXX_FLAGS          "-fPIC -O3 -std=c++11")

#####
# Include directories
#####

include_directories("${PROJECT_SOURCE_DIR}/include/")

#####
# Source files
#####

file(GLOB SRC_FILES "${PROJECT_SOURCE_DIR}/src/*.cpp")

#####
# Set Face Recog library generation path
#####

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
add_library(astar STATIC ${SRC_FILES})
set(ASTAR_LIB ${LIBRARY_OUTPUT_PATH}/libastar.a)
set_target_properties(astar PROPERTIES COMPILE_FLAGS "${CMAKE_CXX_FLAGS}")
add_custom_command(OUTPUT ${LIBRARY_OUTPUT_PATH}/libastar.a
                         COMMAND ar ARGS -x ${ASTAR_LIB}
                         COMMAND rm ARGS -f ${ASTAR_LIB}
                         COMMAND ar ARGS -r ${LIBRARY_OUTPUT_PATH}/libastar.a *.o
                         COMMAND rm ARGS -f *.o
                         DEPENDS "astar")


