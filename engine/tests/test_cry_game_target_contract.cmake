if(NOT DEFINED ENGINE_CMAKE OR NOT DEFINED CRY_GAME)
    message(FATAL_ERROR "ENGINE_CMAKE and CRY_GAME are required")
endif()

file(READ "${ENGINE_CMAKE}" cmake_text)

if(NOT cmake_text MATCHES "add_library\\(cry_game_core STATIC[ \t\r\n]+apps/cry_game/cry_game.c\\)")
    message(FATAL_ERROR "missing top-level cry_game_core with its production source")
endif()
if(NOT cmake_text MATCHES "add_executable\\(cry_game apps/cry_game/main.c\\)")
    message(FATAL_ERROR "missing real cry_game executable")
endif()
if(NOT cmake_text MATCHES "option\\(CRY_GAME_ENABLE_NETWORK \"Enable the optional authenticated Snowflake channel\" OFF\\)")
    message(FATAL_ERROR "CRY_GAME_ENABLE_NETWORK must default to OFF")
endif()
if(NOT cmake_text MATCHES "target_link_libraries\\(cry_game_core PUBLIC[ \t\r\n]+engine break_game break_ai break_flow break_lua break_game_lua runtime_core\\)")
    message(FATAL_ERROR "cry_game_core does not name its explicit integration dependencies")
endif()
if(NOT cmake_text MATCHES "target_link_libraries\\(cry_game PRIVATE cry_game_core m\\)")
    message(FATAL_ERROR "cry_game does not link cry_game_core")
endif()
if(NOT cmake_text MATCHES "engine_link_rhi_backend\\(cry_game\\)")
    message(FATAL_ERROR "cry_game does not use the existing RHI selector")
endif()

string(REGEX MATCHALL "target_link_libraries\\((engine|engine_demo|dxx_break)[^\n]*"
    consumer_link_lines "${cmake_text}")
foreach(line IN LISTS consumer_link_lines)
    if(line MATCHES "break_game|break_flow|break_ai|break_lua|runtime_core|cry_game")
        message(FATAL_ERROR "P12 library leaked into legacy consumer: ${line}")
    endif()
endforeach()

if(NOT EXISTS "${CRY_GAME}")
    message(FATAL_ERROR "cry_game binary does not exist: ${CRY_GAME}")
endif()

set(errors "")
function(expect_exit name expected)
    execute_process(
        COMMAND "${CRY_GAME}" ${ARGN}
        RESULT_VARIABLE rc
        OUTPUT_VARIABLE out
        ERROR_VARIABLE err
        TIMEOUT 10)
    if(NOT "${rc}" STREQUAL "${expected}")
        string(APPEND errors "${name}: exit=${rc}, want=${expected}; stdout=${out}; stderr=${err}\n")
        set(errors "${errors}" PARENT_SCOPE)
    endif()
endfunction()

expect_exit(help 0 --help)
expect_exit(unknown_option 2 --definitely-unknown)
expect_exit(unknown_render 2 --render=headless)
expect_exit(missing_value 2 --scenario)
expect_exit(network_disabled 2 --network)
expect_exit(unimplemented_not_success 2)
expect_exit(valid_record_options_reach_unimplemented_runtime 2
    --render=record --audio=record --assets . --scenario scenario.txt
    --checkpoint checkpoint --trace trace.txt --screenshot shot.ppm
    --fixed-step --frames 1 --require-device)
expect_exit(help_rejects_extra_arguments 2 --help --definitely-unknown)

execute_process(
    COMMAND "${CRY_GAME}" --help
    RESULT_VARIABLE help_rc
    OUTPUT_VARIABLE help_out
    ERROR_VARIABLE help_err
    TIMEOUT 10)
if(help_rc EQUAL 0 AND NOT help_out MATCHES "Usage: cry_game")
    string(APPEND errors "help did not describe the real executable; stderr=${help_err}\n")
endif()

if(DEFINED NM AND NOT "${NM}" STREQUAL "")
    execute_process(
        COMMAND "${NM}" --defined-only "${CRY_GAME}"
        RESULT_VARIABLE nm_rc
        OUTPUT_VARIABLE nm_out
        ERROR_VARIABLE nm_err
        TIMEOUT 20)
    if(NOT nm_rc EQUAL 0)
        string(APPEND errors "nm failed: ${nm_err}\n")
    elseif(nm_out MATCHES "_for_test|test_hook")
        string(APPEND errors "production cry_game contains a test hook\n")
    endif()
else()
    message(STATUS "cry_game test-hook symbol scan not run: NM was not provided")
endif()

if(NOT errors STREQUAL "")
    message(FATAL_ERROR "cry_game target/CLI contract failed:\n${errors}")
endif()
message(STATUS "cry_game target and real-process CLI contract passed")
