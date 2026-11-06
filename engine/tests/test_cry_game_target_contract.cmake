foreach(var ENGINE_CMAKE CRY_GAME NETWORK_ENABLED CONTRACT_BUILD_ROOT)
    if(NOT DEFINED ${var})
        message(FATAL_ERROR "${var} is required")
    endif()
endforeach()

set_property(GLOBAL PROPERTY CRY_GAME_CONTRACT_ERRORS "")

function(record_error text)
    get_property(errors GLOBAL PROPERTY CRY_GAME_CONTRACT_ERRORS)
    string(APPEND errors "${text}\n")
    set_property(GLOBAL PROPERTY CRY_GAME_CONTRACT_ERRORS "${errors}")
endfunction()

function(contract_skip reason)
    get_property(errors GLOBAL PROPERTY CRY_GAME_CONTRACT_ERRORS)
    if(NOT errors STREQUAL "")
        message(FATAL_ERROR "cry_game contract failed before skip:\n${errors}")
    endif()
    message(STATUS "UNVERIFIED: cry_game symbol scan skipped: ${reason}")
    if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.29)
        cmake_language(EXIT 77)
    endif()
    message(FATAL_ERROR "UNVERIFIED: ${reason}; this CMake cannot emit skip code 77")
endfunction()

function(expect_exit name expected)
    execute_process(
        COMMAND "${CRY_GAME}" ${ARGN}
        RESULT_VARIABLE rc
        OUTPUT_VARIABLE out
        ERROR_VARIABLE err
        TIMEOUT 10)
    set_property(GLOBAL PROPERTY CRY_GAME_LAST_RC "${rc}")
    set_property(GLOBAL PROPERTY CRY_GAME_LAST_OUT "${out}")
    set_property(GLOBAL PROPERTY CRY_GAME_LAST_ERR "${err}")
    if(NOT "${rc}" STREQUAL "${expected}")
        record_error("${name}: exit=${rc}, want=${expected}; stdout=${out}; stderr=${err}")
    endif()
endfunction()

function(expect_last_error name pattern)
    get_property(err GLOBAL PROPERTY CRY_GAME_LAST_ERR)
    if(NOT "${err}" MATCHES "${pattern}")
        record_error("${name}: stderr did not match '${pattern}': ${err}")
    endif()
endfunction()

function(expect_runtime_failed name)
    expect_exit(${name} 2 ${ARGN})
    expect_last_error(${name}_failed "runtime returned FAILED")
    get_property(err GLOBAL PROPERTY CRY_GAME_LAST_ERR)
    if("${err}" MATCHES "runtime returned INVALID|unknown or malformed argument|invalid --|requires |unavailable in this build")
        record_error("${name}: legal input took a CLI/INVALID path: ${err}")
    endif()
endfunction()

get_filename_component(engine_source_dir "${ENGINE_CMAKE}" DIRECTORY)
file(READ "${ENGINE_CMAKE}" cmake_text)
if(NOT cmake_text MATCHES "engine_link_rhi_backend\\(cry_game\\)")
    record_error("cry_game does not use engine_link_rhi_backend")
endif()
execute_process(
    COMMAND "${CMAKE_COMMAND}" -S "${engine_source_dir}" -B "${CONTRACT_BUILD_ROOT}"
        -DENGINE_BUILD_TESTS=OFF -DENGINE_ENABLE_IPO=OFF
        -DENGINE_RHI_BACKEND=auto -DBREAK_ENABLE_SNOWFLAKE=OFF
        -DCRY_GAME_ENABLE_NETWORK=${NETWORK_ENABLED}
    RESULT_VARIABLE configure_rc
    OUTPUT_VARIABLE configure_out
    ERROR_VARIABLE configure_err
    TIMEOUT 120)
if(NOT configure_rc EQUAL 0)
    record_error("no-tests target/scope configure failed: ${configure_out}${configure_err}")
endif()

expect_exit(help 0 --help)
get_property(help_out GLOBAL PROPERTY CRY_GAME_LAST_OUT)
if(NOT help_out MATCHES "Usage: cry_game")
    record_error("help did not describe the real executable: ${help_out}")
endif()

expect_runtime_failed(default_reaches_runtime)
expect_runtime_failed(valid_record_options_reach_runtime
    --render=record --audio=record --assets . --scenario scenario.txt
    --checkpoint checkpoint --trace trace.txt --screenshot shot.ppm
    --fixed-step --frames 1 --require-device)

expect_exit(unknown_option 2 --definitely-unknown)
expect_last_error(unknown_option "unknown or malformed argument")
expect_exit(unknown_render 2 --render=headless)
expect_last_error(unknown_render "invalid --render value")
expect_exit(missing_value 2 --scenario)
expect_last_error(missing_value "--scenario requires a nonempty path")
expect_exit(help_rejects_extra_arguments 2 --help --definitely-unknown)
expect_last_error(help_rejects_extra_arguments "unknown or malformed argument")

if(NETWORK_ENABLED)
    expect_runtime_failed(network_enabled_but_unimplemented --network)
else()
    expect_exit(network_disabled 2 --network)
    expect_last_error(network_disabled "--network is unavailable in this build")
endif()

expect_exit(frames_zero 2 --frames 0)
expect_last_error(frames_zero "--frames requires a positive 32-bit integer")
expect_exit(frames_negative 2 --frames -1)
expect_last_error(frames_negative "--frames requires a positive 32-bit integer")
expect_exit(frames_nonnumeric 2 --frames nope)
expect_last_error(frames_nonnumeric "--frames requires a positive 32-bit integer")
expect_exit(frames_empty 2 --frames=)
expect_last_error(frames_empty "--frames requires a positive 32-bit integer")
expect_exit(frames_missing 2 --frames)
expect_last_error(frames_missing "--frames requires a positive 32-bit integer")
expect_runtime_failed(frames_u32_max --frames 4294967295)
expect_exit(frames_u32_overflow 2 --frames 4294967296)
expect_last_error(frames_u32_overflow "--frames requires a positive 32-bit integer")
expect_exit(frames_conversion_overflow 2 --frames 999999999999999999999999999)
expect_last_error(frames_conversion_overflow "--frames requires a positive 32-bit integer")
expect_exit(frames_leading_space 2 --frames " 1")
expect_last_error(frames_leading_space "--frames requires a positive 32-bit integer")
expect_exit(frames_plus 2 --frames +1)
expect_last_error(frames_plus "--frames requires a positive 32-bit integer")

if(NOT DEFINED NM OR "${NM}" STREQUAL "")
    contract_skip("NM was not provided")
endif()
if(NOT NM_CAPABLE)
    contract_skip("the selected toolchain/binary format has no supported nm scan")
endif()

execute_process(
    COMMAND "${NM}" --defined-only "${CRY_GAME}"
    RESULT_VARIABLE nm_rc
    OUTPUT_VARIABLE nm_out
    ERROR_VARIABLE nm_err
    TIMEOUT 20)
if(NOT nm_rc EQUAL 0)
    contract_skip("nm does not support --defined-only for this binary: ${nm_err}")
endif()
if(NOT nm_out MATCHES "cry_game_run")
    contract_skip("nm output format did not expose the expected cry_game_run symbol")
endif()
if(nm_out MATCHES "_for_test|test_hook")
    record_error("production cry_game contains a test hook")
endif()

get_property(errors GLOBAL PROPERTY CRY_GAME_CONTRACT_ERRORS)
if(NOT errors STREQUAL "")
    message(FATAL_ERROR "cry_game target/CLI contract failed:\n${errors}")
endif()
message(STATUS "cry_game target, real-process CLI, and symbol-scan contract passed")
