foreach(var GAME_APP ASSET_ROOT SCENARIO WORK)
    if(NOT DEFINED ${var})
        message(FATAL_ERROR "${var} is required")
    endif()
endforeach()

set_property(GLOBAL PROPERTY GAME_LIFECYCLE_ERRORS "")
set_property(GLOBAL PROPERTY GAME_LIFECYCLE_REMAINDER "")

function(record_error text)
    get_property(errors GLOBAL PROPERTY GAME_LIFECYCLE_ERRORS)
    string(APPEND errors "${text}\n")
    set_property(GLOBAL PROPERTY GAME_LIFECYCLE_ERRORS "${errors}")
endfunction()

function(read_trace path out_var)
    if(EXISTS "${path}")
        file(READ "${path}" content)
        string(REPLACE "\r\n" "\n" content "${content}")
        set(${out_var} "${content}" PARENT_SCOPE)
    else()
        set(${out_var} "" PARENT_SCOPE)
    endif()
endfunction()

function(expect_ordered text)
    get_property(remaining GLOBAL PROPERTY GAME_LIFECYCLE_REMAINDER)
    string(FIND "${remaining}" "${text}\n" position)
    if(position LESS 0)
        record_error("missing or out-of-order trace line: ${text}; remainder=${remaining}")
    else()
        string(LENGTH "${text}\n" prefix_length)
        math(EXPR offset "${position} + ${prefix_length}")
        string(SUBSTRING "${remaining}" ${offset} -1 next_remaining)
        set_property(GLOBAL PROPERTY GAME_LIFECYCLE_REMAINDER "${next_remaining}")
    endif()
endfunction()

function(expect_event_count name trace pattern expected)
    string(REGEX MATCHALL "${pattern}" matches "${trace}")
    list(LENGTH matches count)
    if(NOT count EQUAL expected)
        record_error("${name}: event '${pattern}' count=${count}, want=${expected}; trace=${trace}")
    endif()
endfunction()

function(run_app name assets scenario expected_rc)
    set(trace_path "${WORK}/${name}.trace")
    execute_process(
        COMMAND "${GAME_APP}" --render=record --audio=record
            --assets "${assets}" --fixed-step --scenario "${scenario}"
            --trace "${trace_path}"
        RESULT_VARIABLE rc
        OUTPUT_VARIABLE out
        ERROR_VARIABLE err
        TIMEOUT 30)
    if(NOT "${rc}" STREQUAL "${expected_rc}")
        record_error("${name}: exit=${rc}, want=${expected_rc}; stdout=${out}; stderr=${err}")
    endif()
    read_trace("${trace_path}" trace)
    set(GAME_LIFECYCLE_TRACE "${trace}" PARENT_SCOPE)
    set(GAME_LIFECYCLE_STDERR "${err}" PARENT_SCOPE)
endfunction()

function(run_fault_app name assets scenario expected_rc fault_var)
    set(trace_path "${WORK}/${name}.trace")
    set(preload "${FAULT_LIBRARY}")
    if(DEFINED SANITIZER_PRELOAD AND NOT SANITIZER_PRELOAD STREQUAL "")
        set(preload "${SANITIZER_PRELOAD}:${FAULT_LIBRARY}")
    endif()
    set(fault_value "1")
    if(ARGC GREATER 5)
        set(fault_value "${ARGV5}")
    endif()
    execute_process(
        COMMAND "${CMAKE_COMMAND}" -E env "LD_PRELOAD=${preload}" "${fault_var}=${fault_value}"
            "${GAME_APP}" --render=record --audio=record
            --assets "${assets}" --fixed-step --scenario "${scenario}"
            --trace "${trace_path}"
        RESULT_VARIABLE rc
        OUTPUT_VARIABLE out
        ERROR_VARIABLE err
        TIMEOUT 30)
    if(NOT "${rc}" STREQUAL "${expected_rc}")
        record_error("${name}: exit=${rc}, want=${expected_rc}; stdout=${out}; stderr=${err}")
    endif()
    read_trace("${trace_path}" trace)
    set(GAME_LIFECYCLE_TRACE "${trace}" PARENT_SCOPE)
    set(GAME_LIFECYCLE_STDERR "${err}" PARENT_SCOPE)
endfunction()

function(expect_initial_failure name stage assets)
    run_app("${name}" "${assets}" "${SCENARIO}" 2)
    set(trace "${GAME_LIFECYCLE_TRACE}")
    if(trace STREQUAL "")
        record_error("${name}: no trace; missing runtime_running, load_rejected, and io_stopped evidence")
    else()
        if(NOT trace MATCHES "event=runtime_running\n")
            record_error("${name}: runtime did not reach RUNNING before the staged load")
        endif()
        if(NOT trace MATCHES "event=load_rejected generation=0 stage=${stage}\n")
            record_error("${name}: wrong rejected stage/generation: ${trace}")
        endif()
        if(NOT trace MATCHES "event=io_stopped active=0\n")
            record_error("${name}: IO requests/workers were not drained: ${trace}")
        endif()
        if(trace MATCHES "event=level_loaded|event=frame frame=|event=level_unloaded|event=runtime_stopped")
            record_error("${name}: failed initial load published a partial level or normal stop: ${trace}")
        endif()
    endif()
    if(NOT GAME_LIFECYCLE_STDERR MATCHES "stage=${stage}")
        record_error("${name}: fixture did not reach its intended ${stage} failure: ${GAME_LIFECYCLE_STDERR}")
    endif()
endfunction()

file(REMOVE_RECURSE "${WORK}")
file(MAKE_DIRECTORY "${WORK}")
foreach(fixture good missing_bscn bad_flow unknown_actor missing_lua timeout_bscn crossref_bscn)
    file(COPY "${ASSET_ROOT}/" DESTINATION "${WORK}/${fixture}")
endforeach()
file(REMOVE "${WORK}/missing_bscn/level.bscn")
file(WRITE "${WORK}/bad_flow/level.fg" "BFLW definitely-not-a-flow-graph\n")
set(patch_crossref [=[
import struct
import sys
path = sys.argv[1]
with open(path, "rb") as source:
    data = bytearray(source.read())
magic, version, count = struct.unpack_from("<III", data, 0)
if magic != 0x4E534342:
    raise SystemExit("not a BSCN fixture")
for index in range(count):
    offset = 12 + index * 12
    if struct.unpack_from("<I", data, offset)[0] == 6:
        struct.pack_into("<I", data, offset, 255)
        break
else:
    raise SystemExit("MESH_DATA chunk not found")
with open(path, "wb") as output:
    output.write(data)
]=])
execute_process(COMMAND "${Python3_EXECUTABLE}" -c "${patch_crossref}"
    "${WORK}/crossref_bscn/level.bscn"
    RESULT_VARIABLE patch_result ERROR_VARIABLE patch_error)
if(NOT patch_result EQUAL 0)
    message(FATAL_ERROR "failed to construct crossref fixture: ${patch_error}")
endif()
file(READ "${WORK}/unknown_actor/actors.sidecar" sidecar)
string(REPLACE "2 Player" "2 UnknownPlayer" changed_sidecar "${sidecar}")
if(changed_sidecar STREQUAL sidecar)
    message(FATAL_ERROR "formal actor sidecar no longer contains the Player row")
endif()
file(WRITE "${WORK}/unknown_actor/actors.sidecar" "${changed_sidecar}")
file(REMOVE "${WORK}/missing_lua/player.lua")

run_app(load_unload "${ASSET_ROOT}" "${SCENARIO}" 0)
set(normal_trace "${GAME_LIFECYCLE_TRACE}")
if(normal_trace STREQUAL "")
    record_error("load_unload: trace is absent; missing level_loaded/frame/audio listener/level_unloaded/runtime_stopped events")
else()
    set_property(GLOBAL PROPERTY GAME_LIFECYCLE_REMAINDER "${normal_trace}")
    expect_ordered("GAMEAPPTRACE version=1 event=runtime_running")
    expect_ordered("GAMEAPPTRACE version=1 event=level_loaded generation=1")
    expect_ordered("GAMEAPPTRACE version=1 event=frame frame=1 generation=1")
    expect_ordered("GAMEAPPTRACE version=1 event=audio kind=listener generation=1")
    expect_ordered("GAMEAPPTRACE version=1 event=level_unloaded generation=1")
    expect_ordered("GAMEAPPTRACE version=1 event=level_loaded generation=2")
    expect_ordered("GAMEAPPTRACE version=1 event=runtime_stopped")
    if(NOT normal_trace MATCHES "event=render kind=resource generation=1 id=[1-9][0-9]*")
        record_error("load_unload: record render emitted no nonzero generation-1 resource id")
    endif()
    if(NOT normal_trace MATCHES "event=io_stopped active=0\n")
        record_error("load_unload: runtime IO did not finish with zero live requests")
    endif()
    if(normal_trace MATCHES "event=load_rejected")
        record_error("load_unload: formal assets were unexpectedly rejected: ${normal_trace}")
    endif()
endif()

expect_initial_failure(missing_bscn bscn "${WORK}/missing_bscn")
expect_initial_failure(bad_flow flow "${WORK}/bad_flow")
expect_initial_failure(unknown_actor actor "${WORK}/unknown_actor")
expect_initial_failure(missing_lua lua "${WORK}/missing_lua")

set(replacement_scenario "${WORK}/replacement.scenario")
file(WRITE "${replacement_scenario}"
    "game-app-scenario 1\nseed 12648430\nfixed-dt-ns 16666667\n"
    "frame 1 load ${WORK}/good\n"
    "frame 2 load ${WORK}/bad_flow\n"
    "frame 3 unload\n"
    "frame 4 end\n")
run_app(rejected_replacement "${WORK}/good" "${replacement_scenario}" 0)
set(replacement_trace "${GAME_LIFECYCLE_TRACE}")
if(replacement_trace STREQUAL "")
    record_error("rejected_replacement: trace is absent; old-level retention was not exercised")
else()
    set_property(GLOBAL PROPERTY GAME_LIFECYCLE_REMAINDER "${replacement_trace}")
    expect_ordered("GAMEAPPTRACE version=1 event=level_loaded generation=1")
    expect_ordered("GAMEAPPTRACE version=1 event=frame frame=1 generation=1")
    expect_ordered("GAMEAPPTRACE version=1 event=load_rejected generation=1 stage=flow")
    expect_ordered("GAMEAPPTRACE version=1 event=frame frame=2 generation=1")
    expect_ordered("GAMEAPPTRACE version=1 event=level_unloaded generation=1")
    expect_ordered("GAMEAPPTRACE version=1 event=runtime_stopped")
    if(replacement_trace MATCHES "event=level_loaded generation=2|event=frame frame=2 generation=2")
        record_error("rejected_replacement: failed Flow candidate consumed/published generation 2: ${replacement_trace}")
    endif()
    if(NOT replacement_trace MATCHES "event=io_stopped active=0\n")
        record_error("rejected_replacement: old requests survived shutdown: ${replacement_trace}")
    endif()
endif()

set(crossref_scenario "${WORK}/crossref_replacement.scenario")
file(WRITE "${crossref_scenario}"
    "game-app-scenario 1\nseed 12648430\nfixed-dt-ns 16666667\n"
    "frame 1 load ${WORK}/good\n"
    "frame 2 load ${WORK}/crossref_bscn\n"
    "frame 3 unload\n"
    "frame 4 end\n")
run_app(crossref_replacement "${WORK}/good" "${crossref_scenario}" 0)
set(crossref_trace "${GAME_LIFECYCLE_TRACE}")
set_property(GLOBAL PROPERTY GAME_LIFECYCLE_REMAINDER "${crossref_trace}")
expect_ordered("GAMEAPPTRACE version=1 event=level_loaded generation=1")
expect_ordered("GAMEAPPTRACE version=1 event=frame frame=1 generation=1")
expect_ordered("GAMEAPPTRACE version=1 event=load_rejected generation=1 stage=crossref")
expect_ordered("GAMEAPPTRACE version=1 event=frame frame=2 generation=1")
expect_ordered("GAMEAPPTRACE version=1 event=level_unloaded generation=1")
expect_ordered("GAMEAPPTRACE version=1 event=runtime_stopped")
if(crossref_trace MATCHES "event=level_loaded generation=2|event=frame frame=2 generation=2")
    record_error("crossref_replacement: rejected candidate consumed generation 2: ${crossref_trace}")
endif()

set(mount_scenario "${WORK}/mount_isolation.scenario")
file(WRITE "${mount_scenario}"
    "game-app-scenario 1\nseed 12648430\nfixed-dt-ns 16666667\n"
    "frame 1 load ${WORK}/good\n")
foreach(frame RANGE 2 18)
    file(APPEND "${mount_scenario}" "frame ${frame} load ${WORK}/missing_bscn\n")
endforeach()
file(APPEND "${mount_scenario}"
    "frame 19 load ${WORK}/good\n"
    "frame 20 unload\n"
    "frame 21 end\n")
run_app(mount_isolation "${WORK}/good" "${mount_scenario}" 0)
set(mount_trace "${GAME_LIFECYCLE_TRACE}")
if(mount_trace STREQUAL "")
    record_error("mount_isolation: trace is absent")
else()
    set_property(GLOBAL PROPERTY GAME_LIFECYCLE_REMAINDER "${mount_trace}")
    expect_ordered("GAMEAPPTRACE version=1 event=level_loaded generation=1")
    expect_ordered("GAMEAPPTRACE version=1 event=frame frame=1 generation=1")
    expect_ordered("GAMEAPPTRACE version=1 event=load_rejected generation=1 stage=bscn")
    expect_ordered("GAMEAPPTRACE version=1 event=frame frame=2 generation=1")
    expect_ordered("GAMEAPPTRACE version=1 event=level_unloaded generation=1")
    expect_ordered("GAMEAPPTRACE version=1 event=level_destroyed generation=1")
    expect_ordered("GAMEAPPTRACE version=1 event=level_loaded generation=2")
    expect_ordered("GAMEAPPTRACE version=1 event=frame frame=19 generation=2")
    expect_ordered("GAMEAPPTRACE version=1 event=level_unloaded generation=2")
    expect_ordered("GAMEAPPTRACE version=1 event=level_destroyed generation=2")
    expect_ordered("GAMEAPPTRACE version=1 event=runtime_stopped")
    expect_event_count(mount_replacement_old_destroy "${mount_trace}"
        "event=level_destroyed generation=1" 1)
    expect_event_count(mount_replacement_new_destroy "${mount_trace}"
        "event=level_destroyed generation=2" 1)
    string(REGEX MATCHALL "event=load_rejected generation=1 stage=bscn" mount_rejects "${mount_trace}")
    list(LENGTH mount_rejects mount_reject_count)
    if(NOT mount_reject_count EQUAL 17)
        record_error("mount_isolation: got ${mount_reject_count} missing-BSCN rejects, want 17; trace=${mount_trace}")
    endif()
    if(mount_trace MATCHES "event=level_loaded generation=[3-9]|event=frame frame=2 generation=2")
        record_error("mount_isolation: a missing candidate consumed a generation or used an old mount: ${mount_trace}")
    endif()
endif()

if(FAULT_SUPPORTED)
    set(commit_tail_scenario "${WORK}/commit_tail.scenario")
    file(WRITE "${commit_tail_scenario}"
        "game-app-scenario 1\nseed 12648430\nfixed-dt-ns 16666667\n"
        "frame 1 load ${WORK}/good\n"
        "frame 2 load ${WORK}/good\n"
        "frame 3 unload\n"
        "frame 4 end\n")
    run_fault_app(commit_tail "${WORK}/good" "${commit_tail_scenario}" 2
        GAME_TEST_FAIL_UNLOAD_FLUSH)
    set(commit_trace "${GAME_LIFECYCLE_TRACE}")
    if(NOT commit_trace MATCHES "event=level_unloaded generation=1\n")
        record_error("commit_tail: replacement did not reach the old-generation commit tail: ${commit_trace}")
    endif()
    if(NOT commit_trace MATCHES "event=runtime_fault stage=commit generation=2\n")
        record_error("commit_tail: post-commit I/O error was not classified as runtime fatal: ${commit_trace}")
    endif()
    if(commit_trace MATCHES "event=load_rejected|event=runtime_stopped|event=frame frame=2")
        record_error("commit_tail: committed replacement falsely rejected/stopped or continued a frame: ${commit_trace}")
    endif()
    if(NOT commit_trace MATCHES "event=runtime_failed\n" OR
       NOT commit_trace MATCHES "event=io_stopped active=0\n")
        record_error("commit_tail: rollback did not finish IO and report failure: ${commit_trace}")
    endif()
    if(NOT GAME_LIFECYCLE_STDERR MATCHES "stage=commit")
        record_error("commit_tail: diagnostic did not identify the commit tail: ${GAME_LIFECYCLE_STDERR}")
    endif()
    expect_event_count(commit_tail_old_destroy "${commit_trace}"
        "event=level_destroyed generation=1" 1)
    expect_event_count(commit_tail_new_destroy "${commit_trace}"
        "event=level_destroyed generation=2" 1)

    set(sticky_scenario "${WORK}/sticky_failed.scenario")
    file(WRITE "${sticky_scenario}"
        "game-app-scenario 1\nseed 12648430\nfixed-dt-ns 16666667\n"
        "frame 1 load ${WORK}/good\n"
        "frame 2 end\n")
    run_fault_app(sticky_failed "${WORK}/good" "${sticky_scenario}" 2
        GAME_TEST_FAIL_IO_STOP_FLUSH)
    set(sticky_trace "${GAME_LIFECYCLE_TRACE}")
    if(NOT sticky_trace MATCHES "event=runtime_failed\n" OR
       NOT sticky_trace MATCHES "event=io_stopped active=0\n")
        record_error("sticky_failed: coordinator callback did not reach explicit rollback: ${sticky_trace}")
    endif()
    if(sticky_trace MATCHES "event=runtime_stopped|event=load_rejected")
        record_error("sticky_failed: sticky failure was reported as normal stop/reject: ${sticky_trace}")
    endif()
    expect_event_count(sticky_level_destroy "${sticky_trace}"
        "event=level_destroyed generation=1" 1)
    if(NOT GAME_LIFECYCLE_STDERR MATCHES "stage=shutdown")
        record_error("sticky_failed: shutdown callback diagnostic missing: ${GAME_LIFECYCLE_STDERR}")
    endif()

    set(timeout_scenario "${WORK}/io_timeout.scenario")
    file(WRITE "${timeout_scenario}"
        "game-app-scenario 1\nseed 12648430\nfixed-dt-ns 16666667\n"
        "frame 1 load ${WORK}/good\n"
        "frame 2 load ${WORK}/timeout_bscn\n"
        "frame 3 load ${WORK}/good\n"
        "frame 4 unload\n"
        "frame 5 end\n")
    run_fault_app(io_timeout "${WORK}/good" "${timeout_scenario}" 0
        GAME_TEST_SLOW_BSCN_US 6000000)
    set(timeout_trace "${GAME_LIFECYCLE_TRACE}")
    set_property(GLOBAL PROPERTY GAME_LIFECYCLE_REMAINDER "${timeout_trace}")
    expect_ordered("GAMEAPPTRACE version=1 event=level_loaded generation=1")
    expect_ordered("GAMEAPPTRACE version=1 event=frame frame=1 generation=1")
    expect_ordered("GAMEAPPTRACE version=1 event=io_quiesced")
    expect_ordered("GAMEAPPTRACE version=1 event=load_rejected generation=1 stage=bscn")
    expect_ordered("GAMEAPPTRACE version=1 event=frame frame=2 generation=1")
    expect_ordered("GAMEAPPTRACE version=1 event=level_unloaded generation=1")
    expect_ordered("GAMEAPPTRACE version=1 event=level_loaded generation=2")
    expect_ordered("GAMEAPPTRACE version=1 event=frame frame=3 generation=2")
    expect_ordered("GAMEAPPTRACE version=1 event=runtime_stopped")
    if(NOT timeout_trace MATCHES "event=io_stopped active=0\n")
        record_error("io_timeout: worker/request cleanup did not reach active=0: ${timeout_trace}")
    endif()
else()
    message(STATUS "UNVERIFIED: LD_PRELOAD lifecycle fault injection requires Linux")
endif()

get_property(errors GLOBAL PROPERTY GAME_LIFECYCLE_ERRORS)
if(NOT errors STREQUAL "")
    message(FATAL_ERROR "game_app lifecycle contract failed:\n${errors}")
endif()
message(STATUS "game_app real-process load/unload, failure rollback, and record lifecycle passed")
