foreach(var ENGINE_CMAKE CORE_APP NETWORK_ENABLED CONTRACT_BUILD_ROOT NM TARGET_CONTRACT NM_WRAPPER
        NESTED_ENGINE_RHI_BACKEND)
    if(NOT DEFINED ${var} OR "${${var}}" STREQUAL "")
        message(FATAL_ERROR "${var} is required for the wrapped-nm negative test")
    endif()
endforeach()

execute_process(
    COMMAND "${NM}" --defined-only "${CORE_APP}"
    RESULT_VARIABLE nm_preflight_result
    OUTPUT_VARIABLE nm_preflight_output
    ERROR_VARIABLE nm_preflight_error
    TIMEOUT 20)
if(NOT nm_preflight_result EQUAL 0)
    set(skip_reason "CORE_APP_NM_NEGATIVE_UNAVAILABLE: real nm does not support --defined-only: ${nm_preflight_error}")
    message(STATUS "UNVERIFIED: ${skip_reason}")
    if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.29)
        cmake_language(EXIT 77)
    endif()
    # Older script-mode CMake exits 1 here; the unique token above matches this
    # test's SKIP_REGULAR_EXPRESSION without hiding wrapped-contract failures.
    message(FATAL_ERROR "UNVERIFIED: ${skip_reason}; cmake < 3.29 cannot exit 77")
endif()

file(REMOVE_RECURSE "${CONTRACT_BUILD_ROOT}")
file(MAKE_DIRECTORY "${CONTRACT_BUILD_ROOT}")
set(filtered_symbols "${CONTRACT_BUILD_ROOT}/filtered-symbols.txt")
set(nested_toolchain_defs
    "-DNESTED_ENGINE_RHI_BACKEND=${NESTED_ENGINE_RHI_BACKEND}")
foreach(cache_var Vulkan_LIBRARY Vulkan_INCLUDE_DIR SHADERC_LIB SHADERC_INCLUDE_DIR)
    if(DEFINED ${cache_var} AND NOT "${${cache_var}}" STREQUAL "")
        list(APPEND nested_toolchain_defs "-D${cache_var}=${${cache_var}}")
    endif()
endforeach()
execute_process(
    COMMAND "${CMAKE_COMMAND}"
        -DENGINE_CMAKE=${ENGINE_CMAKE}
        -DCORE_APP=${CORE_APP}
        -DNETWORK_ENABLED=${NETWORK_ENABLED}
        -DCONTRACT_BUILD_ROOT=${CONTRACT_BUILD_ROOT}/no-tests
        -DNM=${NM}
        -DNM_CAPABLE=TRUE
        -DNM_WRAPPER=${NM_WRAPPER}
        -DNM_OUTPUT_FILE=${filtered_symbols}
        ${nested_toolchain_defs}
        -P ${TARGET_CONTRACT}
    RESULT_VARIABLE contract_result
    OUTPUT_VARIABLE contract_output
    ERROR_VARIABLE contract_error
    TIMEOUT 120)
set(contract_log "${contract_output}${contract_error}")
if(contract_log MATCHES "no-tests target/scope configure failed")
    message(FATAL_ERROR "wrapped target contract had a nested configure failure: ${contract_log}")
endif()
if("${contract_result}" STREQUAL "0")
    message(FATAL_ERROR "target contract passed with core_app_run filtered from real nm output")
endif()
if("${contract_result}" STREQUAL "77")
    message(FATAL_ERROR "missing core_app_run incorrectly took SKIP 77: ${contract_log}")
endif()
if(NOT contract_log MATCHES "nm output did not expose required core_app_run symbol")
    message(FATAL_ERROR "missing-symbol failure was not the expected contract error: ${contract_log}")
endif()
if(NOT contract_log MATCHES "CORE_APP_NM_ONLY_MISSING_SYMBOL")
    message(FATAL_ERROR "wrapped target contract had failures besides the real missing symbol: ${contract_log}")
endif()
if(NOT EXISTS "${filtered_symbols}")
    message(FATAL_ERROR "wrapped nm did not produce filtered symbol output")
endif()
file(READ "${filtered_symbols}" symbol_output)
if(symbol_output MATCHES "core_app_run")
    message(FATAL_ERROR "wrapper did not filter core_app_run")
endif()
if(NOT symbol_output MATCHES "core_app_render_start")
    message(FATAL_ERROR "wrapper did not preserve the normal control symbol")
endif()
message(STATUS "real wrapped nm without core_app_run produced FAIL, not SKIP")
