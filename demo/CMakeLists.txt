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

project (A_Star_demo)

#######
# Set necessary flags
######

set(CMAKE_CXX_FLAGS          "-fPIC -O3 -std=c++11")

#####
# Include directories
#####

include_directories("${PROJECT_SOURCE_DIR}/../include/")

#####
# Source files
#####

file(GLOB SRC_FILES "${PROJECT_SOURCE_DIR}/src/run_astar.cpp")

set(ASTAR_LIB ${PROJECT_SOURCE_DIR}/../lib/libastar.a)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
add_executable(run_astar ${PROJECT_SOURCE_DIR}/run_astar.cpp)
set_target_properties(run_astar PROPERTIES COMPILE_FLAGS "${CMAKE_CXX_FLAGS}")
target_link_libraries(run_astar ${ASTAR_LIB})
