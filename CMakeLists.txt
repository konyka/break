cmake_minimum_required(VERSION 3.25)

project (break)
set (CMAKE_C_STANDARD 11)
set (CMAKE_CXX_STANDARD 11)

message(STATUS "111  " ${PROJECT_SOURCE_DIR})
include_directories("${PROJECT_SOURCE_DIR}/framework/common")
include_directories("${PROJECT_SOURCE_DIR}/framework/interface")

add_subdirectory(framework)
add_subdirectory(empty)
