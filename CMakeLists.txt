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

option(BREAK_FRAMEWORK_ENABLE_RUNTIME "Enable the optional C++ runtime bus bridge" OFF)
if(BREAK_FRAMEWORK_ENABLE_RUNTIME)
    if(NOT DEFINED ENGINE_BUILD_TESTS)
        set(ENGINE_BUILD_TESTS OFF CACHE BOOL "Build unit tests")
    endif()
    find_package(Threads REQUIRED)
    add_subdirectory(engine)
endif()

if(NOT TARGET common)
    add_subdirectory(framework)
endif()
add_subdirectory(empty)

include(CTest)
if(BUILD_TESTING)
    add_test(NAME test_framework_runtime_build_contract
        COMMAND "${CMAKE_COMMAND}"
            "-DSOURCE_DIR=${PROJECT_SOURCE_DIR}"
            "-DBINARY_DIR=${PROJECT_BINARY_DIR}"
            -P "${PROJECT_SOURCE_DIR}/framework/common/test_runtime_build_contract.cmake")
    set_tests_properties(test_framework_runtime_build_contract PROPERTIES
        LABELS "framework;platform_contract" TIMEOUT 1200)
endif()
