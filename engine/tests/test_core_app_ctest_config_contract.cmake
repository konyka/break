foreach(var ENGINE_SOURCE_DIR REPOSITORY_ROOT PLAN_FILE DESIGN_FILE GIT_EXECUTABLE
        CORE_APP NETWORK_ENABLED CTEST_EXECUTABLE WORK NESTED_ENGINE_RHI_BACKEND
        NESTED_CMAKE_GENERATOR)
    if(NOT DEFINED ${var} OR "${${var}}" STREQUAL "")
        message(FATAL_ERROR "${var} is required")
    endif()
endforeach()
if(NOT DEFINED NESTED_CTEST_CONFIG)
    message(FATAL_ERROR "NESTED_CTEST_CONFIG must be defined; an empty single-config value is valid")
endif()

set(nested_toolchain_defs
    "-DNESTED_ENGINE_RHI_BACKEND=${NESTED_ENGINE_RHI_BACKEND}")
foreach(cache_var Vulkan_LIBRARY Vulkan_INCLUDE_DIR SHADERC_LIB SHADERC_INCLUDE_DIR)
    if(DEFINED ${cache_var} AND NOT "${${cache_var}}" STREQUAL "")
        list(APPEND nested_toolchain_defs "-D${cache_var}=${${cache_var}}")
    endif()
endforeach()
if(NESTED_ENGINE_RHI_BACKEND STREQUAL "vulkan")
    foreach(required Vulkan_LIBRARY Vulkan_INCLUDE_DIR SHADERC_LIB SHADERC_INCLUDE_DIR)
        if(NOT DEFINED ${required} OR "${${required}}" STREQUAL "")
            message(FATAL_ERROR "real Vulkan input is required: ${required}")
        endif()
    endforeach()
endif()

execute_process(
    COMMAND "${CMAKE_COMMAND}" -E capabilities
    RESULT_VARIABLE capabilities_result
    OUTPUT_VARIABLE capabilities_output
    ERROR_VARIABLE capabilities_error)
if(NOT capabilities_result EQUAL 0)
    message(FATAL_ERROR "cmake -E capabilities failed: ${capabilities_output}${capabilities_error}")
endif()
string(FIND "${capabilities_output}" "\"name\":\"Ninja Multi-Config\"" ninja_multi_config_index)
if(ninja_multi_config_index LESS 0)
    message(FATAL_ERROR "Ninja Multi-Config is not available in this CMake")
endif()
find_program(NINJA_EXECUTABLE NAMES ninja)
if(NOT NINJA_EXECUTABLE)
    message(FATAL_ERROR "a real ninja executable is required")
endif()
execute_process(
    COMMAND "${NINJA_EXECUTABLE}" --version
    RESULT_VARIABLE ninja_result
    OUTPUT_VARIABLE ninja_output
    ERROR_VARIABLE ninja_error
    OUTPUT_STRIP_TRAILING_WHITESPACE)
if(NOT ninja_result EQUAL 0)
    message(FATAL_ERROR "ninja --version failed: ${ninja_output}${ninja_error}")
endif()
message(STATUS "using real Ninja ${ninja_output}: ${NINJA_EXECUTABLE}")

function(run_compat name default_generator nested_generator nested_config work)
    execute_process(
        COMMAND "${CMAKE_COMMAND}" -E env
            "CMAKE_GENERATOR=${default_generator}"
            "${CMAKE_COMMAND}"
            "-DENGINE_SOURCE_DIR=${ENGINE_SOURCE_DIR}"
            "-DREPOSITORY_ROOT=${REPOSITORY_ROOT}"
            "-DPLAN_FILE=${PLAN_FILE}"
            "-DDESIGN_FILE=${DESIGN_FILE}"
            "-DGIT_EXECUTABLE=${GIT_EXECUTABLE}"
            "-DCORE_APP=${CORE_APP}"
            "-DNETWORK_ENABLED=${NETWORK_ENABLED}"
            "-DCTEST_EXECUTABLE=${CTEST_EXECUTABLE}"
            "-DWORK=${work}"
            "-DNESTED_CMAKE_GENERATOR=${nested_generator}"
            "-DNESTED_CTEST_CONFIG=${nested_config}"
            ${nested_toolchain_defs}
            -P "${ENGINE_SOURCE_DIR}/tests/test_core_app_contract_compat.cmake"
        RESULT_VARIABLE result
        OUTPUT_VARIABLE output
        ERROR_VARIABLE error)
    set(log "${output}${error}")
    message(STATUS "${name}: result=${result}\n${log}")
    set(COMPAT_RESULT "${result}" PARENT_SCOPE)
    set(COMPAT_LOG "${log}" PARENT_SCOPE)
endfunction()

function(expect_compat_success name)
    set(problems "")
    if(NOT "${COMPAT_RESULT}" STREQUAL "0")
        string(APPEND problems "result=${COMPAT_RESULT}, expected 0\n")
    endif()
    string(FIND "${COMPAT_LOG}" "core_app compatibility contract passed" passed_index)
    if(passed_index LESS 0)
        string(APPEND problems "missing core_app compatibility contract passed\n")
    endif()
    if("${COMPAT_LOG}" MATCHES "Not Run|NOT_AVAILABLE")
        string(APPEND problems "nested CTest reported an unavailable or unrun test\n")
    endif()
    if(NOT problems STREQUAL "")
        message(FATAL_ERROR "${name}: compatibility success contract failed:\n${problems}${COMPAT_LOG}")
    endif()
    message(STATUS "${name}: compatibility success contract passed")
endfunction()

function(expect_multi_config_cache work fixture)
    set(cache "${work}/${fixture}-build/CMakeCache.txt")
    if(NOT EXISTS "${cache}")
        message(FATAL_ERROR "${fixture}: expected CMake cache was not generated: ${cache}")
    endif()
    file(STRINGS "${cache}" generator_line REGEX "^CMAKE_GENERATOR:INTERNAL=")
    if(NOT "${generator_line}" STREQUAL "CMAKE_GENERATOR:INTERNAL=Ninja Multi-Config")
        message(FATAL_ERROR
            "${fixture}: requested generator was not used: '${generator_line}'")
    endif()
    message(STATUS "${fixture}: CMAKE_GENERATOR=Ninja Multi-Config")
endfunction()

set(same_multi_work "${WORK}/same-ninja-multi-config")
run_compat(same_ninja_multi_config
    "Ninja Multi-Config" "Ninja Multi-Config" "Debug" "${same_multi_work}")
expect_compat_success(same_ninja_multi_config)

set(override_multi_work "${WORK}/override-with-ninja-multi-config")
run_compat(default_ninja_requested_ninja_multi_config
    "Ninja" "Ninja Multi-Config" "Debug" "${override_multi_work}")
expect_compat_success(default_ninja_requested_ninja_multi_config)
foreach(fixture IN ITEMS corrupt nm archive)
    expect_multi_config_cache("${override_multi_work}" "${fixture}")
endforeach()
set(permission_cache "${override_multi_work}/permission-build/CMakeCache.txt")
if(EXISTS "${permission_cache}")
    expect_multi_config_cache("${override_multi_work}" permission)
else()
    set(permission_required FALSE)
    if(UNIX)
        execute_process(COMMAND id -u
            RESULT_VARIABLE id_result
            OUTPUT_VARIABLE id_output
            OUTPUT_STRIP_TRAILING_WHITESPACE)
        if(id_result EQUAL 0 AND NOT id_output STREQUAL "0")
            set(permission_required TRUE)
        endif()
    endif()
    if(permission_required)
        message(FATAL_ERROR "permission fixture did not generate its expected CMake cache")
    endif()
    message(STATUS
        "permission fixture cache was not generated; existing UNIX/non-root fixture limitation applies")
endif()

set(single_config_work "${WORK}/single-config-empty")
run_compat(ninja_empty_config "Ninja" "Ninja" "" "${single_config_work}")
expect_compat_success(ninja_empty_config)

run_compat(ninja_multi_config_empty_config
    "Ninja Multi-Config" "Ninja Multi-Config" "" "${WORK}/multi-config-empty-rejected")
if("${COMPAT_RESULT}" STREQUAL "0")
    message(FATAL_ERROR "an empty multi-config NESTED_CTEST_CONFIG unexpectedly succeeded")
endif()
string(FIND "${COMPAT_LOG}" "a multi-config nested CTest requires NESTED_CTEST_CONFIG"
    required_config_error_index)
if(required_config_error_index LESS 0)
    message(FATAL_ERROR
        "empty multi-config input did not produce the explicit configuration error:\n${COMPAT_LOG}")
endif()
message(STATUS "ninja_multi_config_empty_config: explicit rejection passed")

message(STATUS "core_app nested CTest configuration contract passed")
