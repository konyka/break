cmake_minimum_required(VERSION 3.25)

if(NOT DEFINED SOURCE_DIR OR SOURCE_DIR STREQUAL "")
    message(FATAL_ERROR "SOURCE_DIR is required and must not be empty")
endif()
if(NOT DEFINED BINARY_DIR OR BINARY_DIR STREQUAL "")
    message(FATAL_ERROR "BINARY_DIR is required and must not be empty")
endif()
cmake_path(ABSOLUTE_PATH BINARY_DIR NORMALIZE OUTPUT_VARIABLE NORMALIZED_BINARY_DIR)
cmake_path(GET NORMALIZED_BINARY_DIR ROOT_PATH BINARY_ROOT_PATH)
if(NORMALIZED_BINARY_DIR STREQUAL BINARY_ROOT_PATH)
    message(FATAL_ERROR "BINARY_DIR must not be a filesystem root")
endif()
set(BINARY_DIR "${NORMALIZED_BINARY_DIR}")
set(WORK_DIR "${BINARY_DIR}/framework-runtime-build-contract")
cmake_path(GET WORK_DIR PARENT_PATH WORK_PARENT_DIR)
if(NOT WORK_PARENT_DIR STREQUAL BINARY_DIR)
    message(FATAL_ERROR "Refusing to remove anything outside the fixed contract subdirectory")
endif()
file(REMOVE_RECURSE "${WORK_DIR}")

function(configure_tree tree)
    file(MAKE_DIRECTORY "${tree}/.cmake/api/v1/query")
    file(WRITE "${tree}/.cmake/api/v1/query/codemodel-v2" "")
    execute_process(
        COMMAND "${CMAKE_COMMAND}" -S "${SOURCE_DIR}" -B "${tree}"
            -DCMAKE_BUILD_TYPE=Debug ${ARGN}
        RESULT_VARIABLE result
        OUTPUT_VARIABLE output
        ERROR_VARIABLE error)
    if(NOT result EQUAL 0)
        message(FATAL_ERROR
            "Configure failed for ${tree}:\n${output}\n${error}")
    endif()
endfunction()

function(build_target tree target result_variable output_variable)
    execute_process(
        COMMAND "${CMAKE_COMMAND}" --build "${tree}" --target "${target}"
            --config Debug ${ARGN}
        RESULT_VARIABLE result
        OUTPUT_VARIABLE output
        ERROR_VARIABLE error)
    set("${result_variable}" "${result}" PARENT_SCOPE)
    set("${output_variable}" "${output}\n${error}" PARENT_SCOPE)
endfunction()

function(get_target_json tree target_name output_variable)
    file(GLOB replies LIST_DIRECTORIES FALSE
        "${tree}/.cmake/api/v1/reply/codemodel-v2-*.json")
    if(NOT replies)
        message(FATAL_ERROR "No codemodel reply in ${tree}")
    endif()
    list(SORT replies)
    list(GET replies -1 reply)
    file(READ "${reply}" codemodel)
    string(JSON configuration_count LENGTH "${codemodel}" configurations)
    set(configuration_index 0)
    set(debug_configuration_index -1)
    while(configuration_index LESS configuration_count)
        string(JSON configuration_name GET "${codemodel}"
            configurations ${configuration_index} name)
        if(configuration_name STREQUAL "Debug")
            set(debug_configuration_index "${configuration_index}")
            break()
        endif()
        math(EXPR configuration_index "${configuration_index} + 1")
    endwhile()
    if(debug_configuration_index LESS 0)
        message(FATAL_ERROR "No Debug configuration in ${reply}")
    endif()
    string(JSON target_count LENGTH "${codemodel}"
        configurations ${debug_configuration_index} targets)
    set(index 0)
    while(index LESS target_count)
        string(JSON name GET "${codemodel}"
            configurations ${debug_configuration_index} targets ${index} name)
        if(name STREQUAL target_name)
            string(JSON json_file GET "${codemodel}"
                configurations ${debug_configuration_index} targets ${index} jsonFile)
            get_filename_component(reply_directory "${reply}" DIRECTORY)
            file(READ "${reply_directory}/${json_file}" target_json)
            set("${output_variable}" "${target_json}" PARENT_SCOPE)
            return()
        endif()
        math(EXPR index "${index} + 1")
    endwhile()
    set("${output_variable}" "" PARENT_SCOPE)
endfunction()

function(check_empty_link tree)
    get_target_json("${tree}" empty target_json)
    if(NOT target_json)
        message(FATAL_ERROR "No empty target in ${tree}")
    endif()
    string(JSON fragment_count LENGTH "${target_json}" link commandFragments)
    set(index 0)
    while(index LESS fragment_count)
        string(JSON fragment GET "${target_json}" link commandFragments ${index} fragment)
        string(JSON role GET "${target_json}" link commandFragments ${index} role)
        if(role STREQUAL "libraries" AND
           (fragment MATCHES "(^|[/\\\\])(lib)?(common_runtime|runtime_core|engine)(\\.|$)" OR
            fragment MATCHES "^-l(common_runtime|runtime_core|engine)$"))
            message(FATAL_ERROR
                "empty must not link the runtime bridge or engine: ${fragment}")
        endif()
        math(EXPR index "${index} + 1")
    endwhile()
    message(STATUS "empty link dependency contract passed in ${tree}")
endfunction()

set(default_tree "${WORK_DIR}/default")
configure_tree("${default_tree}"
    -DBUILD_TESTING=OFF)
file(STRINGS "${default_tree}/CMakeCache.txt" default_runtime_cache_entry
    REGEX "^BREAK_FRAMEWORK_ENABLE_RUNTIME:BOOL=")
if(NOT default_runtime_cache_entry STREQUAL "BREAK_FRAMEWORK_ENABLE_RUNTIME:BOOL=OFF")
    message(FATAL_ERROR
        "Runtime bridge must default to OFF; cache entry: ${default_runtime_cache_entry}")
endif()
build_target("${default_tree}" empty default_empty_result default_empty_output --parallel 2)
if(NOT default_empty_result EQUAL 0)
    message(FATAL_ERROR "Default empty build failed:\n${default_empty_output}")
endif()
check_empty_link("${default_tree}")
build_target("${default_tree}" common_runtime default_runtime_result default_runtime_output
    --parallel 2)
if(default_runtime_result EQUAL 0)
    message(FATAL_ERROR "common_runtime unexpectedly built in the default tree")
endif()
get_target_json("${default_tree}" common_runtime default_runtime_json)
if(default_runtime_json)
    message(FATAL_ERROR "common_runtime target exists in the default tree")
endif()
foreach(unexpected_target runtime_core engine)
    get_target_json("${default_tree}" "${unexpected_target}" unexpected_target_json)
    if(unexpected_target_json)
        message(FATAL_ERROR "${unexpected_target} target exists in the default tree")
    endif()
endforeach()
message(STATUS "Default runtime isolation contract passed")

set(enabled_tree "${WORK_DIR}/enabled")
configure_tree("${enabled_tree}"
    -DBREAK_FRAMEWORK_ENABLE_RUNTIME=ON
    -DENGINE_BUILD_TESTS=OFF
    -DBUILD_TESTING=OFF
    -DENGINE_RHI_BACKEND=vulkan
    -DMYUI_PAL=dummy)
get_target_json("${enabled_tree}" test_framework_runtime_bus explicit_off_test_json)
if(explicit_off_test_json)
    message(FATAL_ERROR
        "test_framework_runtime_bus exists with explicit ENGINE_BUILD_TESTS=OFF")
endif()
message(STATUS "Explicit OFF keeps test_framework_runtime_bus absent")
build_target("${enabled_tree}" common_runtime enabled_runtime_result enabled_runtime_output
    --parallel 2)
if(NOT enabled_runtime_result EQUAL 0)
    message(FATAL_ERROR "Enabled common_runtime build failed:\n${enabled_runtime_output}")
endif()
build_target("${enabled_tree}" empty enabled_empty_result enabled_empty_output
    --parallel 2 --verbose)
if(NOT enabled_empty_result EQUAL 0)
    message(FATAL_ERROR "Enabled empty build failed:\n${enabled_empty_output}")
endif()
check_empty_link("${enabled_tree}")
message(STATUS "Enabled runtime bridge contract passed")

set(default_tests_tree "${WORK_DIR}/engine-tests-default")
configure_tree("${default_tests_tree}"
    -DBREAK_FRAMEWORK_ENABLE_RUNTIME=ON
    -DBUILD_TESTING=OFF
    -DENGINE_RHI_BACKEND=vulkan
    -DMYUI_PAL=dummy)
get_target_json("${default_tests_tree}" common_runtime default_tests_runtime_json)
if(NOT default_tests_runtime_json)
    message(FATAL_ERROR
        "common_runtime is missing when ENGINE_BUILD_TESTS uses the root default")
endif()
get_target_json("${default_tests_tree}" test_framework_runtime_bus default_tests_test_json)
if(default_tests_test_json)
    message(FATAL_ERROR
        "test_framework_runtime_bus exists when ENGINE_BUILD_TESTS uses the root default")
endif()
file(STRINGS "${default_tests_tree}/CMakeCache.txt" default_tests_cache_entry
    REGEX "^ENGINE_BUILD_TESTS:BOOL=")
if(NOT default_tests_cache_entry STREQUAL "ENGINE_BUILD_TESTS:BOOL=OFF")
    message(FATAL_ERROR
        "Root default must set ENGINE_BUILD_TESTS=OFF; cache entry: ${default_tests_cache_entry}")
endif()
message(STATUS "Default engine tests setting keeps the runtime bridge without test targets")

set(tests_tree "${WORK_DIR}/engine-tests-enabled")
configure_tree("${tests_tree}"
    -DBREAK_FRAMEWORK_ENABLE_RUNTIME=ON
    -DENGINE_BUILD_TESTS=ON
    -DBUILD_TESTING=OFF
    -DENGINE_RHI_BACKEND=vulkan
    -DMYUI_PAL=dummy)
get_target_json("${tests_tree}" test_framework_runtime_bus runtime_bus_test_json)
if(NOT runtime_bus_test_json)
    message(FATAL_ERROR
        "test_framework_runtime_bus target is missing with ENGINE_BUILD_TESTS=ON")
endif()
build_target("${tests_tree}" test_framework_runtime_bus runtime_bus_test_build_result
    runtime_bus_test_build_output --parallel 2)
if(NOT runtime_bus_test_build_result EQUAL 0)
    message(FATAL_ERROR
        "Explicit ON test_framework_runtime_bus build failed:\n${runtime_bus_test_build_output}")
endif()
execute_process(
    COMMAND "${CMAKE_CTEST_COMMAND}" --test-dir "${tests_tree}/engine"
        -C Debug -R "^test_framework_runtime_bus$" --output-on-failure
        --no-tests=error
    RESULT_VARIABLE runtime_bus_ctest_result
    OUTPUT_VARIABLE runtime_bus_ctest_output
    ERROR_VARIABLE runtime_bus_ctest_error)
set(runtime_bus_ctest_log "${runtime_bus_ctest_output}\n${runtime_bus_ctest_error}")
if(NOT runtime_bus_ctest_result EQUAL 0)
    message(FATAL_ERROR
        "Explicit ON test_framework_runtime_bus CTest failed:\n${runtime_bus_ctest_log}")
endif()
message(STATUS "Explicit ON test_framework_runtime_bus CTest passed:\n${runtime_bus_ctest_log}")
message(STATUS "Explicit engine tests contract passed without duplicate framework targets")
