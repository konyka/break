# Drives test_core_app_network_loopback and test_core_app_network_offline.
#
# MODE=loopback: starts the real core_app with --network next to
# test_core_app_net_client. CMake runs the COMMANDs of one execute_process
# concurrently, so the server and the peer run at the same time. Then the
# same scenario runs offline, and every non-network trace line must be
# byte-identical: hostile network input never changes the simulation.
#
# MODE=offline: the same scenario twice without --network must give
# byte-identical traces with no network line. In a build without the
# transport, nm must find no break_net_/break_session_/snow_/Snow symbol.
foreach(var MODE CORE_APP ASSET_DIR SCENARIO WORK_DIR)
    if(NOT DEFINED ${var} OR "${${var}}" STREQUAL "")
        message(FATAL_ERROR "${var} is required")
    endif()
endforeach()

file(REMOVE_RECURSE "${WORK_DIR}")
file(MAKE_DIRECTORY "${WORK_DIR}")
set(common_args --render=record --audio=record --assets "${ASSET_DIR}" --fixed-step
    --scenario "${SCENARIO}")

function(run_offline name)
    execute_process(
        COMMAND "${CORE_APP}" ${common_args} --trace "${WORK_DIR}/${name}.trace"
        RESULT_VARIABLE rc OUTPUT_VARIABLE out ERROR_VARIABLE err TIMEOUT 120)
    if(NOT rc EQUAL 0)
        message(FATAL_ERROR "offline run ${name} failed: rc=${rc}\n${out}${err}")
    endif()
endfunction()

function(read_core_lines path out_var)
    file(STRINGS "${path}" lines REGEX "^COREAPPTRACE ")
    list(FILTER lines EXCLUDE REGEX "event=network")
    set(${out_var} "${lines}" PARENT_SCOPE)
endfunction()

function(stat_value text key out_var)
    if(NOT text MATCHES " ${key}=([0-9]+)")
        message(FATAL_ERROR "network_stats has no ${key}: ${text}")
    endif()
    set(${out_var} "${CMAKE_MATCH_1}" PARENT_SCOPE)
endfunction()

function(expect_at_least text key minimum)
    stat_value("${text}" ${key} value)
    if(value LESS minimum)
        message(FATAL_ERROR "network_stats ${key}=${value}, want >= ${minimum}: ${text}")
    endif()
endfunction()

if(MODE STREQUAL "offline")
    run_offline(first)
    run_offline(second)
    file(SHA256 "${WORK_DIR}/first.trace" first_hash)
    file(SHA256 "${WORK_DIR}/second.trace" second_hash)
    if(NOT first_hash STREQUAL second_hash)
        message(FATAL_ERROR "offline traces differ between two runs of one scenario")
    endif()
    file(STRINGS "${WORK_DIR}/first.trace" network_lines REGEX "event=network")
    if(network_lines)
        message(FATAL_ERROR "offline run created network objects: ${network_lines}")
    endif()
    if(NOT NETWORK_TRANSPORT)
        if(NOT NM_CAPABLE OR NOT DEFINED NM OR "${NM}" STREQUAL "")
            message(STATUS "UNVERIFIED: nm cannot read this binary format, symbol scan skipped")
            if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.29)
                cmake_language(EXIT 77)
            endif()
            message(FATAL_ERROR "UNVERIFIED: no nm and this CMake cannot emit skip code 77")
        endif()
        execute_process(COMMAND "${NM}" "${CORE_APP}"
            RESULT_VARIABLE nm_rc OUTPUT_VARIABLE nm_out ERROR_VARIABLE nm_err TIMEOUT 30)
        if(NOT nm_rc EQUAL 0)
            message(FATAL_ERROR "nm failed: ${nm_err}")
        endif()
        if(NOT nm_out MATCHES "core_app_run")
            message(FATAL_ERROR "nm output lacks core_app_run; the scan proves nothing")
        endif()
        string(REGEX MATCHALL "[^\n]*(break_net_|break_session_|snow_|[ _]Snow[A-Z])[^\n]*"
            leaked "${nm_out}")
        if(leaked)
            message(FATAL_ERROR "offline core_app links network code:\n${leaked}")
        endif()
    endif()
    message(STATUS "core_app offline network contract passed")
    return()
endif()

if(NOT MODE STREQUAL "loopback")
    message(FATAL_ERROR "unknown MODE=${MODE}")
endif()
foreach(var NET_CLIENT TLS_CERT TLS_KEY)
    if(NOT DEFINED ${var} OR "${${var}}" STREQUAL "")
        message(FATAL_ERROR "${var} is required for MODE=loopback")
    endif()
endforeach()

# Test-only key; it is passed through the environment, never on argv.
set(ENV{CORE_APP_TEST_PSK}
    "0f1e2d3c4b5a69788796a5b4c3d2e1f00112233445566778899aabbccddeeff0")
execute_process(
    COMMAND "${CORE_APP}" ${common_args} --trace "${WORK_DIR}/network.trace"
        --network --bind 127.0.0.1:0 --tls-cert "${TLS_CERT}" --tls-key "${TLS_KEY}"
        --psk-env CORE_APP_TEST_PSK --port-file "${WORK_DIR}/server.port"
    COMMAND "${NET_CLIENT}" "${WORK_DIR}/server.port" "${WORK_DIR}/client.report"
    RESULTS_VARIABLE results
    OUTPUT_VARIABLE out ERROR_VARIABLE err TIMEOUT 120)
unset(ENV{CORE_APP_TEST_PSK})
set(report "")
if(EXISTS "${WORK_DIR}/client.report")
    file(READ "${WORK_DIR}/client.report" report)
endif()
list(GET results 0 server_rc)
list(GET results 1 client_rc)
if(NOT server_rc EQUAL 0 OR NOT client_rc EQUAL 0)
    message(FATAL_ERROR
        "loopback failed: server=${server_rc} client=${client_rc}\n${report}\n${err}")
endif()
message(STATUS "client report:\n${report}")

file(READ "${WORK_DIR}/network.trace" trace)
if(trace MATCHES "CORE_APP_TEST_PSK|0f1e2d3c4b5a6978")
    message(FATAL_ERROR "the trace contains the secret or its variable name")
endif()
if(NOT trace MATCHES "event=network result=listening tls=1 auth=v2")
    message(FATAL_ERROR "the server never reported a TLS + AUTH-v2 listener")
endif()
if(NOT trace MATCHES "event=network_session result=authenticated")
    message(FATAL_ERROR "no session reached AUTHENTICATED")
endif()
if(NOT trace MATCHES "COREAPPTRACE version=1 event=network_stats[^\n]*")
    message(FATAL_ERROR "the server did not report network_stats on shutdown")
endif()
set(stats "${CMAKE_MATCH_0}")
message(STATUS "${stats}")
stat_value("${stats}" authenticated authenticated)
if(NOT authenticated EQUAL 1)
    message(FATAL_ERROR "exactly one peer holds the PSK; authenticated=${authenticated}")
endif()
expect_at_least("${stats}" opened 4)
expect_at_least("${stats}" snapshots_sent 2)
expect_at_least("${stats}" rejected_stale 1)
expect_at_least("${stats}" rejected_schema 1)
expect_at_least("${stats}" decode_failed 1)
expect_at_least("${stats}" session_phase_rejected 1)
expect_at_least("${stats}" session_handler_failed 2)
stat_value("${stats}" admitted admitted)
if(admitted GREATER 0)
    # An admitted snapshot is only diagnostic, but this peer sent nothing
    # that matches the live level and schema without a forged field.
    message(STATUS "note: admitted=${admitted} diagnostic snapshots")
endif()

run_offline(offline)
read_core_lines("${WORK_DIR}/network.trace" networked)
read_core_lines("${WORK_DIR}/offline.trace" offline)
list(LENGTH networked networked_count)
list(LENGTH offline offline_count)
if(NOT networked_count EQUAL offline_count OR NOT networked STREQUAL offline)
    message(FATAL_ERROR
        "network input changed the simulation: ${networked_count} vs ${offline_count} lines")
endif()
if(NOT report MATCHES "snapshot frame=[0-9]+ generation=([0-9]+) user_index=([0-9]+)")
    message(FATAL_ERROR "client report lacks the received snapshot")
endif()
set(peer_generation "${CMAKE_MATCH_1}")
if(NOT trace MATCHES "event=level_loaded generation=${peer_generation}\n")
    message(FATAL_ERROR "snapshot generation ${peer_generation} is not the live level")
endif()
message(STATUS "core_app authenticated loopback contract passed (${networked_count} lines)")
