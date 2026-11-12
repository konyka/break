foreach(var ENGINE_CMAKE CORE_APP NETWORK_ENABLED CONTRACT_BUILD_ROOT
        TARGET_CONTRACT NM_SYMBOL_MISSING_CONTRACT NM_WRAPPER NM_CAPABLE
        NESTED_ENGINE_RHI_BACKEND NESTED_CMAKE_C_COMPILER)
    if(NOT DEFINED ${var} OR "${${var}}" STREQUAL "")
        message(FATAL_ERROR "${var} is required for the nested core_app contract")
    endif()
endforeach()
if(NM_CAPABLE AND (NOT DEFINED NM OR "${NM}" STREQUAL ""))
    message(FATAL_ERROR "NM is required when NM_CAPABLE=TRUE")
endif()

set_property(GLOBAL PROPERTY CORE_APP_NESTED_ERRORS "")
function(record_error text)
    get_property(errors GLOBAL PROPERTY CORE_APP_NESTED_ERRORS)
    string(APPEND errors "${text}\n")
    set_property(GLOBAL PROPERTY CORE_APP_NESTED_ERRORS "${errors}")
endfunction()

set(nested_toolchain_defs
    "-DNESTED_ENGINE_RHI_BACKEND=${NESTED_ENGINE_RHI_BACKEND}"
    "-DNESTED_CMAKE_C_COMPILER=${NESTED_CMAKE_C_COMPILER}"
    "-DCMAKE_C_COMPILER=${NESTED_CMAKE_C_COMPILER}")
set(all_sdk_paths TRUE)
foreach(cache_var Vulkan_LIBRARY Vulkan_INCLUDE_DIR SHADERC_LIB SHADERC_INCLUDE_DIR)
    if(DEFINED ${cache_var} AND NOT "${${cache_var}}" STREQUAL "")
        list(APPEND nested_toolchain_defs "-D${cache_var}=${${cache_var}}")
        set(expected_${cache_var} "${${cache_var}}")
    else()
        set(all_sdk_paths FALSE)
    endif()
endforeach()

if(NESTED_ENGINE_RHI_BACKEND STREQUAL "vulkan" AND NOT all_sdk_paths)
    message(FATAL_ERROR
        "a Vulkan parent must provide Vulkan_LIBRARY, Vulkan_INCLUDE_DIR, SHADERC_LIB, and SHADERC_INCLUDE_DIR")
endif()
foreach(cache_var Vulkan_LIBRARY SHADERC_LIB)
    if(DEFINED ${cache_var} AND NOT "${${cache_var}}" STREQUAL ""
            AND NOT EXISTS "${${cache_var}}")
        message(FATAL_ERROR "${cache_var} is not a real file: ${${cache_var}}")
    endif()
endforeach()
if(DEFINED Vulkan_INCLUDE_DIR AND NOT "${Vulkan_INCLUDE_DIR}" STREQUAL ""
        AND NOT EXISTS "${Vulkan_INCLUDE_DIR}/vulkan/vulkan.h")
    message(FATAL_ERROR "Vulkan_INCLUDE_DIR has no real vulkan/vulkan.h: ${Vulkan_INCLUDE_DIR}")
endif()
if(DEFINED SHADERC_INCLUDE_DIR AND NOT "${SHADERC_INCLUDE_DIR}" STREQUAL ""
        AND NOT EXISTS "${SHADERC_INCLUDE_DIR}/shaderc/shaderc.h")
    message(FATAL_ERROR "SHADERC_INCLUDE_DIR has no real shaderc/shaderc.h: ${SHADERC_INCLUDE_DIR}")
endif()

file(REMOVE_RECURSE "${CONTRACT_BUILD_ROOT}")
file(MAKE_DIRECTORY "${CONTRACT_BUILD_ROOT}")
set(case_toolchain_defs ${nested_toolchain_defs})
if(all_sdk_paths)
    set(sdk_root "${CONTRACT_BUILD_ROOT}/real-sdk")
    file(MAKE_DIRECTORY "${sdk_root}/lib" "${sdk_root}/include")
    foreach(cache_var Vulkan_LIBRARY SHADERC_LIB)
        get_filename_component(library_name "${${cache_var}}" NAME)
        set(staged_library "${sdk_root}/lib/${library_name}")
        execute_process(
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                "${${cache_var}}" "${staged_library}"
            RESULT_VARIABLE copy_result
            OUTPUT_VARIABLE copy_output
            ERROR_VARIABLE copy_error)
        if(NOT copy_result EQUAL 0 OR NOT EXISTS "${staged_library}")
            message(FATAL_ERROR
                "failed to stage the real ${cache_var}: ${copy_output}${copy_error}")
        endif()
        set(expected_${cache_var} "${staged_library}")
    endforeach()
    foreach(include_component vulkan vk_video)
        if(EXISTS "${Vulkan_INCLUDE_DIR}/${include_component}")
            file(COPY "${Vulkan_INCLUDE_DIR}/${include_component}"
                DESTINATION "${sdk_root}/include")
        endif()
    endforeach()
    if(EXISTS "${Vulkan_INCLUDE_DIR}/vulkan.hpp")
        file(COPY "${Vulkan_INCLUDE_DIR}/vulkan.hpp"
            DESTINATION "${sdk_root}/include")
    endif()
    file(COPY "${SHADERC_INCLUDE_DIR}/shaderc"
        DESTINATION "${sdk_root}/include")
    set(staged_include_dir "${sdk_root}/include")
    if(NOT EXISTS "${staged_include_dir}/vulkan/vulkan.h"
            OR NOT EXISTS "${staged_include_dir}/shaderc/shaderc.h")
        message(FATAL_ERROR "staging did not preserve the real Vulkan/shaderc headers")
    endif()
    set(expected_Vulkan_INCLUDE_DIR "${staged_include_dir}")
    set(expected_SHADERC_INCLUDE_DIR "${staged_include_dir}")
    set(case_toolchain_defs
        "-DNESTED_ENGINE_RHI_BACKEND=${NESTED_ENGINE_RHI_BACKEND}"
        "-DNESTED_CMAKE_C_COMPILER=${NESTED_CMAKE_C_COMPILER}"
        "-DCMAKE_C_COMPILER=${NESTED_CMAKE_C_COMPILER}"
        "-DVulkan_LIBRARY=${expected_Vulkan_LIBRARY}"
        "-DVulkan_INCLUDE_DIR=${expected_Vulkan_INCLUDE_DIR}"
        "-DSHADERC_LIB=${expected_SHADERC_LIB}"
        "-DSHADERC_INCLUDE_DIR=${expected_SHADERC_INCLUDE_DIR}")
endif()

function(expect_cache_value name build_root cache_var expected)
    set(cache_file "${build_root}/CMakeCache.txt")
    if(NOT EXISTS "${cache_file}")
        record_error("${name}: missing independent nested cache ${cache_file}")
        return()
    endif()
    file(STRINGS "${cache_file}" cache_lines REGEX "^${cache_var}:[^=]*=")
    list(LENGTH cache_lines line_count)
    if(NOT line_count EQUAL 1)
        record_error("${name}: ${cache_var} cache entries=${line_count}, expected exactly one")
        return()
    endif()
    string(REGEX REPLACE "^[^=]*=" "" actual "${cache_lines}")
    if(NOT "${actual}" STREQUAL "${expected}")
        record_error("${name}: ${cache_var}='${actual}', expected real forwarded value '${expected}'")
    endif()
endfunction()

function(expect_nested_cache name contract_root)
    if(name STREQUAL "positive")
        set(build_root "${contract_root}")
    else()
        set(build_root "${contract_root}/no-tests")
    endif()
    expect_cache_value(${name} "${build_root}" ENGINE_RHI_BACKEND
        "${NESTED_ENGINE_RHI_BACKEND}")
    if(NOT NESTED_ENGINE_RHI_BACKEND STREQUAL "auto")
        expect_cache_value(${name} "${build_root}" ENGINE_RHI_BACKEND_EFFECTIVE
            "${NESTED_ENGINE_RHI_BACKEND}")
    endif()
    foreach(cache_var Vulkan_LIBRARY Vulkan_INCLUDE_DIR SHADERC_LIB SHADERC_INCLUDE_DIR)
        if(DEFINED expected_${cache_var})
            expect_cache_value(${name} "${build_root}" ${cache_var}
                "${expected_${cache_var}}")
        endif()
    endforeach()
endfunction()

function(run_target_contract name engine_cmake network_enabled contract_root)
    execute_process(
        COMMAND "${CMAKE_COMMAND}"
            "-DENGINE_CMAKE=${engine_cmake}"
            "-DCORE_APP=${CORE_APP}"
            "-DNETWORK_ENABLED=${network_enabled}"
            "-DCONTRACT_BUILD_ROOT=${contract_root}"
            "-DNM=${NM}"
            "-DNM_CAPABLE=${NM_CAPABLE}"
            ${case_toolchain_defs}
            -P "${TARGET_CONTRACT}"
        RESULT_VARIABLE contract_result
        OUTPUT_VARIABLE contract_output
        ERROR_VARIABLE contract_error
        TIMEOUT 120)
    set_property(GLOBAL PROPERTY CORE_APP_NESTED_LAST_RESULT "${contract_result}")
    set_property(GLOBAL PROPERTY CORE_APP_NESTED_LAST_LOG
        "${contract_output}${contract_error}")
endfunction()

function(run_nm_negative name engine_cmake network_enabled contract_root)
    execute_process(
        COMMAND "${CMAKE_COMMAND}"
            "-DENGINE_CMAKE=${engine_cmake}"
            "-DCORE_APP=${CORE_APP}"
            "-DNETWORK_ENABLED=${network_enabled}"
            "-DCONTRACT_BUILD_ROOT=${contract_root}"
            "-DNM=${NM}"
            "-DTARGET_CONTRACT=${TARGET_CONTRACT}"
            "-DNM_WRAPPER=${NM_WRAPPER}"
            ${case_toolchain_defs}
            -P "${NM_SYMBOL_MISSING_CONTRACT}"
        RESULT_VARIABLE contract_result
        OUTPUT_VARIABLE contract_output
        ERROR_VARIABLE contract_error
        TIMEOUT 120)
    set_property(GLOBAL PROPERTY CORE_APP_NESTED_LAST_RESULT "${contract_result}")
    set_property(GLOBAL PROPERTY CORE_APP_NESTED_LAST_LOG
        "${contract_output}${contract_error}")
endfunction()

set(positive_root "${CONTRACT_BUILD_ROOT}/positive")
run_target_contract(positive "${ENGINE_CMAKE}" "${NETWORK_ENABLED}" "${positive_root}")
get_property(positive_result GLOBAL PROPERTY CORE_APP_NESTED_LAST_RESULT)
get_property(positive_log GLOBAL PROPERTY CORE_APP_NESTED_LAST_LOG)
if(NM_CAPABLE)
    if(NOT positive_result STREQUAL "0")
        record_error("positive nested target contract failed: ${positive_log}")
    endif()
elseif(NOT positive_result STREQUAL "77" AND NOT positive_result STREQUAL "1")
    record_error("nested target contract did not return its documented nm-unavailable skip: ${positive_log}")
elseif(NOT positive_log MATCHES "UNVERIFIED: core_app symbol scan skipped:"
        OR positive_log MATCHES "core_app contract failed before skip:")
    record_error("nested target contract did not prove its nm-unavailable skip: ${positive_log}")
else()
    message(STATUS "${positive_log}")
endif()
expect_nested_cache(positive "${positive_root}")

if(NM_CAPABLE)
    set(wrapped_root "${CONTRACT_BUILD_ROOT}/wrapped")
    run_nm_negative(wrapped "${ENGINE_CMAKE}" "${NETWORK_ENABLED}" "${wrapped_root}")
    get_property(wrapped_result GLOBAL PROPERTY CORE_APP_NESTED_LAST_RESULT)
    get_property(wrapped_log GLOBAL PROPERTY CORE_APP_NESTED_LAST_LOG)
    if(NOT wrapped_result STREQUAL "0")
        record_error("real missing-symbol wrapped negative did not pass: ${wrapped_log}")
    endif()
    if(wrapped_log MATCHES "no-tests target/scope configure failed")
        record_error("wrapped negative contained a nested configure failure")
    endif()
    expect_nested_cache(wrapped "${wrapped_root}")

    set(bad_engine_dir "${CONTRACT_BUILD_ROOT}/bad-engine")
    file(MAKE_DIRECTORY "${bad_engine_dir}")
    set(bad_engine_cmake "${bad_engine_dir}/CMakeLists.txt")
    file(WRITE "${bad_engine_cmake}"
        "engine_link_rhi_backend(core_app)\nmessage(FATAL_ERROR \"core_app nested configure sentinel\")\n")
    set(configure_error_probe_root "${CONTRACT_BUILD_ROOT}/configure-error-probe")
    run_target_contract(configure_error_probe "${bad_engine_cmake}"
        "${NETWORK_ENABLED}" "${configure_error_probe_root}")
    get_property(probe_result GLOBAL PROPERTY CORE_APP_NESTED_LAST_RESULT)
    get_property(probe_log GLOBAL PROPERTY CORE_APP_NESTED_LAST_LOG)
    if(probe_result STREQUAL "0" OR probe_result STREQUAL "77"
            OR NOT probe_log MATCHES "no-tests target/scope configure failed")
        record_error("false-green fixture did not exercise the real nested configure failure: ${probe_log}")
    endif()

    set(false_green_root "${CONTRACT_BUILD_ROOT}/false-green")
    run_nm_negative(false_green "${bad_engine_cmake}" "${NETWORK_ENABLED}"
        "${false_green_root}")
    get_property(false_green_result GLOBAL PROPERTY CORE_APP_NESTED_LAST_RESULT)
    get_property(false_green_log GLOBAL PROPERTY CORE_APP_NESTED_LAST_LOG)
    if(false_green_result STREQUAL "0" OR false_green_result STREQUAL "77")
        record_error("nested configure failure plus missing-symbol text was accepted: ${false_green_log}")
    elseif(NOT false_green_log MATCHES "no-tests target/scope configure failed")
        record_error("false-green case failed for an unrelated reason: ${false_green_log}")
    endif()
endif()

get_property(errors GLOBAL PROPERTY CORE_APP_NESTED_ERRORS)
if(NOT errors STREQUAL "")
    message(FATAL_ERROR "core_app nested contract failed:\n${errors}")
endif()
message(STATUS
    "core_app nested backend, real SDK forwarding, wrapped-nm, and false-green contracts passed")
