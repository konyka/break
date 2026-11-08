cmake_minimum_required(VERSION 3.25)

project (break)
set (CMAKE_C_STANDARD 11)
# Dual-language policy (docs/Build_Guide.md): the engine stays pure C11; every
# C++ TU (framework, app glue, C++ wrappers) builds as C++20, and the public
# C API headers stay C++20-consumable (extern "C" guards, gated by
# test_public_api_cpp20 in the engine suite).
set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("${PROJECT_SOURCE_DIR}/framework/common")
include_directories("${PROJECT_SOURCE_DIR}/framework/interface")

add_subdirectory(framework)
add_subdirectory(empty)
