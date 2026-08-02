cmake_minimum_required(VERSION 3.25)

project (break)
set (CMAKE_C_STANDARD 11)
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("${PROJECT_SOURCE_DIR}/framework/common")
include_directories("${PROJECT_SOURCE_DIR}/framework/interface")

add_subdirectory(framework)
add_subdirectory(empty)
