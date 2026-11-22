cmake_minimum_required(VERSION 3.25)

if(NOT DEFINED SOURCE_DIR OR NOT DEFINED BINARY_DIR)
    message(FATAL_ERROR "SOURCE_DIR and BINARY_DIR are required")
endif()

set(WORK_DIR "${BINARY_DIR}/framework-runtime-build-contract")
file(REMOVE_RECURSE "${WORK_DIR}")

function(configure_tree tree)
    file(MAKE_DIRECTORY "${tree}/.cmake/api/v1/query")
    file(WRITE "${tree}/.cmake/api/v1/query/codemodel-v2" "")
    execute_process(
        COMMAND "${CMAKE_COMMAND}" -S "${SOURCE_DIR}" -B "${tree}" ${ARGN}
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
        COMMAND "${CMAKE_COMMAND}" --build "${tree}" --target "${target}" ${ARGN}
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
    string(JSON target_count LENGTH "${codemodel}" configurations 0 targets)
    set(index 0)
    while(index LESS target_count)
        string(JSON name GET "${codemodel}" configurations 0 targets ${index} name)
        if(name STREQUAL target_name)
            string(JSON json_file GET "${codemodel}"
                configurations 0 targets ${index} jsonFile)
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
    -DBREAK_FRAMEWORK_ENABLE_RUNTIME=OFF
    -DBUILD_TESTING=OFF)
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
message(STATUS "Explicit engine tests contract passed without duplicate framework targets")
