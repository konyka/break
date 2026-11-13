foreach(var CORE_APP ASSET_ROOT SCENARIO WORK)
    if(NOT DEFINED ${var})
        message(FATAL_ERROR "${var} is required")
    endif()
endforeach()

set_property(GLOBAL PROPERTY CORE_APP_LIFECYCLE_ERRORS "")
set_property(GLOBAL PROPERTY CORE_APP_LIFECYCLE_REMAINDER "")

function(record_error text)
    get_property(errors GLOBAL PROPERTY CORE_APP_LIFECYCLE_ERRORS)
    string(APPEND errors "${text}\n")
    set_property(GLOBAL PROPERTY CORE_APP_LIFECYCLE_ERRORS "${errors}")
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
    get_property(remaining GLOBAL PROPERTY CORE_APP_LIFECYCLE_REMAINDER)
    string(FIND "${remaining}" "${text}\n" position)
    if(position LESS 0)
        record_error("missing or out-of-order trace line: ${text}; remainder=${remaining}")
    else()
        string(LENGTH "${text}\n" prefix_length)
        math(EXPR offset "${position} + ${prefix_length}")
        string(SUBSTRING "${remaining}" ${offset} -1 next_remaining)
        set_property(GLOBAL PROPERTY CORE_APP_LIFECYCLE_REMAINDER "${next_remaining}")
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
        COMMAND "${CORE_APP}" --render=record --audio=record
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
    set(CORE_APP_LIFECYCLE_TRACE "${trace}" PARENT_SCOPE)
    set(CORE_APP_LIFECYCLE_STDERR "${err}" PARENT_SCOPE)
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
            "${CORE_APP}" --render=record --audio=record
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
    set(CORE_APP_LIFECYCLE_TRACE "${trace}" PARENT_SCOPE)
    set(CORE_APP_LIFECYCLE_STDERR "${err}" PARENT_SCOPE)
endfunction()

function(expect_initial_failure name stage assets)
    run_app("${name}" "${assets}" "${SCENARIO}" 2)
    set(trace "${CORE_APP_LIFECYCLE_TRACE}")
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
    if(NOT CORE_APP_LIFECYCLE_STDERR MATCHES "stage=${stage}")
        record_error("${name}: fixture did not reach its intended ${stage} failure: ${CORE_APP_LIFECYCLE_STDERR}")
    endif()
endfunction()

function(player_position name trace tick out_var)
    string(REGEX MATCH
        "event=player tick=${tick} generation=[0-9]+ x=([^ \n]+) y=([^ \n]+) z=([^ \n]+)\n"
        match "${trace}")
    if(match STREQUAL "")
        record_error("${name}: no player position for tick ${tick}; trace=${trace}")
        set(${out_var} "" PARENT_SCOPE)
    else()
        set(${out_var} "${CMAKE_MATCH_1};${CMAKE_MATCH_2};${CMAKE_MATCH_3}" PARENT_SCOPE)
    endif()
endfunction()

function(expect_forward_beyond_two_meters name position)
    list(LENGTH position fields)
    if(NOT fields EQUAL 3)
        return()
    endif()
    list(GET position 2 z)
    if(NOT z GREATER 2)
        record_error("${name}: player did not move more than 2 m forward: z=${z}")
    endif()
endfunction()

function(write_input_scenario path body)
    if(ARGC GREATER 2)
        message(FATAL_ERROR "write_input_scenario takes exactly one body string")
    endif()
    file(WRITE "${path}"
        "core-app-scenario 1\nseed 12648430\nfixed-dt-ns 16666667\n${body}")
endfunction()

if(DEFINED INPUT_MODE)
    file(REMOVE_RECURSE "${WORK}")
    file(MAKE_DIRECTORY "${WORK}")
    set(key_scenario "${WORK}/input_key.scenario")
    write_input_scenario("${key_scenario}" "1 level\n1 key w 1\n181 quit\n")
    if(INPUT_MODE STREQUAL "key" OR INPUT_MODE STREQUAL "touch")
        run_app(input_key "${ASSET_ROOT}" "${key_scenario}" 0)
        set(key_trace "${CORE_APP_LIFECYCLE_TRACE}")
        expect_event_count(input_key "${key_trace}" "event=player tick=" 180)
        expect_event_count(input_key_haptic "${key_trace}" "event=haptic area=0 " 1)
        if(NOT key_trace MATCHES "event=haptic area=0 generation=1 tick=[0-9]+ status=(disconnected|unsupported) request=0\n")
            record_error("input_key: area haptic without a feedback pad was not reported as disconnected/unsupported: ${key_trace}")
        endif()
        player_position(input_key "${key_trace}" 180 key_position)
        expect_forward_beyond_two_meters(input_key "${key_position}")
        if(NOT key_trace MATCHES "event=runtime_stopped\n")
            record_error("input_key: run did not stop normally: ${key_trace}")
        endif()
    endif()
    if(INPUT_MODE STREQUAL "key")
        run_app(determinism_a "${ASSET_ROOT}" "${SCENARIO}" 0)
        set(determinism_a "${CORE_APP_LIFECYCLE_TRACE}")
        run_app(determinism_b "${ASSET_ROOT}" "${SCENARIO}" 0)
        set(determinism_b "${CORE_APP_LIFECYCLE_TRACE}")
        expect_event_count(determinism "${determinism_a}" "event=player tick=" 180)
        if(determinism_a STREQUAL "" OR NOT determinism_a STREQUAL determinism_b)
            record_error("determinism: two runs of ${SCENARIO} produced different traces")
        endif()
    endif()
    if(INPUT_MODE STREQUAL "touch")
        set(touch_scenario "${WORK}/input_touch.scenario")
        write_input_scenario("${touch_scenario}"
            "1 level\n1 touch 3 down 0.5 0.5\n1 touch 3 move 0.5 0.3\n181 quit\n")
        run_app(input_touch "${ASSET_ROOT}" "${touch_scenario}" 0)
        set(touch_trace "${CORE_APP_LIFECYCLE_TRACE}")
        expect_event_count(input_touch "${touch_trace}" "event=player tick=" 180)
        player_position(input_touch "${touch_trace}" 180 touch_position)
        expect_forward_beyond_two_meters(input_touch "${touch_position}")
        if(NOT "${touch_position}" STREQUAL "${key_position}")
            record_error("input_touch: touch drag final position ${touch_position} differs from key ${key_position}")
        endif()
    elseif(INPUT_MODE STREQUAL "cancel")
        set(release_scenario "${WORK}/input_release.scenario")
        write_input_scenario("${release_scenario}"
            "1 level\n1 key w 1\n11 key w 0\n21 quit\n")
        set(cancel_scenario "${WORK}/input_cancel.scenario")
        write_input_scenario("${cancel_scenario}"
            "1 level\n1 touch 3 down 0.5 0.5\n1 touch 3 move 0.5 0.3\n11 touch 3 cancel 0.5 0.3\n21 quit\n")
        foreach(case release cancel)
            run_app(input_${case} "${ASSET_ROOT}" "${${case}_scenario}" 0)
            set(case_trace "${CORE_APP_LIFECYCLE_TRACE}")
            player_position(input_${case} "${case_trace}" 10 before)
            player_position(input_${case} "${case_trace}" 11 stopped)
            player_position(input_${case} "${case_trace}" 20 after)
            list(LENGTH before before_fields)
            if(before_fields EQUAL 3)
                list(GET before 2 before_z)
                if(before_z STREQUAL "0")
                    record_error("input_${case}: player never moved before ${case}")
                endif()
            endif()
            list(LENGTH stopped stopped_fields)
            list(LENGTH after after_fields)
            if(NOT before_fields EQUAL 3 OR NOT stopped_fields EQUAL 3 OR
               NOT after_fields EQUAL 3)
                record_error("input_${case}: missing tick 10/11/20 positions; trace=${case_trace}")
                continue()
            endif()
            foreach(axis 0 2)
                list(GET before ${axis} before_axis)
                list(GET stopped ${axis} stopped_axis)
                list(GET after ${axis} after_axis)
                if(NOT stopped_axis STREQUAL before_axis OR NOT after_axis STREQUAL before_axis)
                    record_error("input_${case}: horizontal axis ${axis} moved after ${case}: tick10=${before} tick11=${stopped} tick20=${after}")
                endif()
            endforeach()
        endforeach()
    elseif(NOT INPUT_MODE STREQUAL "key")
        message(FATAL_ERROR "unknown INPUT_MODE ${INPUT_MODE}")
    endif()
    get_property(errors GLOBAL PROPERTY CORE_APP_LIFECYCLE_ERRORS)
    if(NOT errors STREQUAL "")
        message(FATAL_ERROR "core_app input lifecycle (${INPUT_MODE}) failed:\n${errors}")
    endif()
    message(STATUS "core_app real-process input lifecycle (${INPUT_MODE}) passed")
    return()
endif()

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

file(READ "${SCENARIO}" formal_scenario)
if(NOT formal_scenario MATCHES "^core-app-scenario 1\n")
    record_error("formal scenario does not start with core-app-scenario 1")
endif()
string(ASCII 71 65 77 69 65 80 80 84 82 65 67 69 legacy_trace_prefix)
string(ASCII 103 97 109 101 45 97 112 112 45 115 99 101 110 97 114 105 111
    legacy_scenario_prefix)
run_app(load_unload "${ASSET_ROOT}" "${SCENARIO}" 0)
set(normal_trace "${CORE_APP_LIFECYCLE_TRACE}")
if(normal_trace STREQUAL "")
    record_error("load_unload: trace is absent; missing level_loaded/frame/audio listener/level_unloaded/runtime_stopped events")
else()
    if(NOT normal_trace MATCHES "^COREAPPTRACE version=1 event=runtime_running\n")
        record_error("load_unload: first trace field is not COREAPPTRACE version=1: ${normal_trace}")
    endif()
    if(normal_trace MATCHES "^${legacy_trace_prefix}")
        record_error("load_unload: legacy trace prefix was emitted: ${normal_trace}")
    endif()
    set_property(GLOBAL PROPERTY CORE_APP_LIFECYCLE_REMAINDER "${normal_trace}")
    expect_ordered("COREAPPTRACE version=1 event=runtime_running")
    expect_ordered("COREAPPTRACE version=1 event=level_loaded generation=1")
    expect_ordered("COREAPPTRACE version=1 event=frame frame=1 generation=1")
    expect_ordered("COREAPPTRACE version=1 event=audio kind=listener generation=1")
    expect_ordered("COREAPPTRACE version=1 event=level_unloaded generation=1")
    expect_ordered("COREAPPTRACE version=1 event=level_loaded generation=2")
    expect_ordered("COREAPPTRACE version=1 event=runtime_stopped")
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

set(legacy_scenario "${WORK}/legacy.scenario")
file(WRITE "${legacy_scenario}"
    "${legacy_scenario_prefix} 1\nseed 12648430\nfixed-dt-ns 16666667\n"
    "1 level ${WORK}/good\n"
    "2 quit\n")
run_app(legacy_scenario "${WORK}/good" "${legacy_scenario}" 2)
if(NOT CORE_APP_LIFECYCLE_STDERR MATCHES "stage=scenario")
    record_error("legacy_scenario: rejection did not identify the scenario stage: ${CORE_APP_LIFECYCLE_STDERR}")
endif()
if(NOT CORE_APP_LIFECYCLE_TRACE STREQUAL "COREAPPTRACE version=1 event=runtime_failed\n")
    record_error("legacy_scenario: rejection did not produce exactly the rollback trace: ${CORE_APP_LIFECYCLE_TRACE}")
endif()

expect_initial_failure(missing_bscn bscn "${WORK}/missing_bscn")
expect_initial_failure(bad_flow flow "${WORK}/bad_flow")
expect_initial_failure(unknown_actor actor "${WORK}/unknown_actor")
expect_initial_failure(missing_lua lua "${WORK}/missing_lua")

set(replacement_scenario "${WORK}/replacement.scenario")
file(WRITE "${replacement_scenario}"
    "core-app-scenario 1\nseed 12648430\nfixed-dt-ns 16666667\n"
    "1 level ${WORK}/good\n"
    "2 level ${WORK}/bad_flow\n"
    "3 unload\n"
    "4 quit\n")
run_app(rejected_replacement "${WORK}/good" "${replacement_scenario}" 0)
set(replacement_trace "${CORE_APP_LIFECYCLE_TRACE}")
if(replacement_trace STREQUAL "")
    record_error("rejected_replacement: trace is absent; old-level retention was not exercised")
else()
    set_property(GLOBAL PROPERTY CORE_APP_LIFECYCLE_REMAINDER "${replacement_trace}")
    expect_ordered("COREAPPTRACE version=1 event=level_loaded generation=1")
    expect_ordered("COREAPPTRACE version=1 event=frame frame=1 generation=1")
    expect_ordered("COREAPPTRACE version=1 event=load_rejected generation=1 stage=flow")
    expect_ordered("COREAPPTRACE version=1 event=frame frame=2 generation=1")
    expect_ordered("COREAPPTRACE version=1 event=level_unloaded generation=1")
    expect_ordered("COREAPPTRACE version=1 event=runtime_stopped")
    if(replacement_trace MATCHES "event=level_loaded generation=2|event=frame frame=2 generation=2")
        record_error("rejected_replacement: failed Flow candidate consumed/published generation 2: ${replacement_trace}")
    endif()
    if(NOT replacement_trace MATCHES "event=io_stopped active=0\n")
        record_error("rejected_replacement: old requests survived shutdown: ${replacement_trace}")
    endif()
endif()

set(crossref_scenario "${WORK}/crossref_replacement.scenario")
file(WRITE "${crossref_scenario}"
    "core-app-scenario 1\nseed 12648430\nfixed-dt-ns 16666667\n"
    "1 level ${WORK}/good\n"
    "2 level ${WORK}/crossref_bscn\n"
    "3 unload\n"
    "4 quit\n")
run_app(crossref_replacement "${WORK}/good" "${crossref_scenario}" 0)
set(crossref_trace "${CORE_APP_LIFECYCLE_TRACE}")
set_property(GLOBAL PROPERTY CORE_APP_LIFECYCLE_REMAINDER "${crossref_trace}")
expect_ordered("COREAPPTRACE version=1 event=level_loaded generation=1")
expect_ordered("COREAPPTRACE version=1 event=frame frame=1 generation=1")
expect_ordered("COREAPPTRACE version=1 event=load_rejected generation=1 stage=crossref")
expect_ordered("COREAPPTRACE version=1 event=frame frame=2 generation=1")
expect_ordered("COREAPPTRACE version=1 event=level_unloaded generation=1")
expect_ordered("COREAPPTRACE version=1 event=runtime_stopped")
if(crossref_trace MATCHES "event=level_loaded generation=2|event=frame frame=2 generation=2")
    record_error("crossref_replacement: rejected candidate consumed generation 2: ${crossref_trace}")
endif()

set(mount_scenario "${WORK}/mount_isolation.scenario")
file(WRITE "${mount_scenario}"
    "core-app-scenario 1\nseed 12648430\nfixed-dt-ns 16666667\n"
    "1 level ${WORK}/good\n")
foreach(frame RANGE 2 18)
    file(APPEND "${mount_scenario}" "${frame} level ${WORK}/missing_bscn\n")
endforeach()
file(APPEND "${mount_scenario}"
    "19 level ${WORK}/good\n"
    "20 unload\n"
    "21 quit\n")
run_app(mount_isolation "${WORK}/good" "${mount_scenario}" 0)
set(mount_trace "${CORE_APP_LIFECYCLE_TRACE}")
if(mount_trace STREQUAL "")
    record_error("mount_isolation: trace is absent")
else()
    set_property(GLOBAL PROPERTY CORE_APP_LIFECYCLE_REMAINDER "${mount_trace}")
    expect_ordered("COREAPPTRACE version=1 event=level_loaded generation=1")
    expect_ordered("COREAPPTRACE version=1 event=frame frame=1 generation=1")
    expect_ordered("COREAPPTRACE version=1 event=load_rejected generation=1 stage=bscn")
    expect_ordered("COREAPPTRACE version=1 event=frame frame=2 generation=1")
    expect_ordered("COREAPPTRACE version=1 event=level_unloaded generation=1")
    expect_ordered("COREAPPTRACE version=1 event=level_destroyed generation=1")
    expect_ordered("COREAPPTRACE version=1 event=level_loaded generation=2")
    expect_ordered("COREAPPTRACE version=1 event=frame frame=19 generation=2")
    expect_ordered("COREAPPTRACE version=1 event=level_unloaded generation=2")
    expect_ordered("COREAPPTRACE version=1 event=level_destroyed generation=2")
    expect_ordered("COREAPPTRACE version=1 event=runtime_stopped")
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
        "core-app-scenario 1\nseed 12648430\nfixed-dt-ns 16666667\n"
        "1 level ${WORK}/good\n"
        "2 level ${WORK}/good\n"
        "3 unload\n"
        "4 quit\n")
    run_fault_app(commit_tail "${WORK}/good" "${commit_tail_scenario}" 2
        CORE_APP_TEST_FAIL_UNLOAD_FLUSH)
    set(commit_trace "${CORE_APP_LIFECYCLE_TRACE}")
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
    if(NOT CORE_APP_LIFECYCLE_STDERR MATCHES "stage=commit")
        record_error("commit_tail: diagnostic did not identify the commit tail: ${CORE_APP_LIFECYCLE_STDERR}")
    endif()
    expect_event_count(commit_tail_old_destroy "${commit_trace}"
        "event=level_destroyed generation=1" 1)
    expect_event_count(commit_tail_new_destroy "${commit_trace}"
        "event=level_destroyed generation=2" 1)

    set(sticky_scenario "${WORK}/sticky_failed.scenario")
    file(WRITE "${sticky_scenario}"
        "core-app-scenario 1\nseed 12648430\nfixed-dt-ns 16666667\n"
        "1 level ${WORK}/good\n"
        "2 quit\n")
    run_fault_app(sticky_failed "${WORK}/good" "${sticky_scenario}" 2
        CORE_APP_TEST_FAIL_IO_STOP_FLUSH)
    set(sticky_trace "${CORE_APP_LIFECYCLE_TRACE}")
    if(NOT sticky_trace MATCHES "event=runtime_failed\n" OR
       NOT sticky_trace MATCHES "event=io_stopped active=0\n")
        record_error("sticky_failed: coordinator callback did not reach explicit rollback: ${sticky_trace}")
    endif()
    if(sticky_trace MATCHES "event=runtime_stopped|event=load_rejected")
        record_error("sticky_failed: sticky failure was reported as normal stop/reject: ${sticky_trace}")
    endif()
    expect_event_count(sticky_level_destroy "${sticky_trace}"
        "event=level_destroyed generation=1" 1)
    if(NOT CORE_APP_LIFECYCLE_STDERR MATCHES "stage=shutdown")
        record_error("sticky_failed: shutdown callback diagnostic missing: ${CORE_APP_LIFECYCLE_STDERR}")
    endif()

    set(timeout_scenario "${WORK}/io_timeout.scenario")
    file(WRITE "${timeout_scenario}"
        "core-app-scenario 1\nseed 12648430\nfixed-dt-ns 16666667\n"
        "1 level ${WORK}/good\n"
        "2 level ${WORK}/timeout_bscn\n"
        "3 level ${WORK}/good\n"
        "4 unload\n"
        "5 quit\n")
    run_fault_app(io_timeout "${WORK}/good" "${timeout_scenario}" 0
        CORE_APP_TEST_SLOW_BSCN_US 6000000)
    set(timeout_trace "${CORE_APP_LIFECYCLE_TRACE}")
    set_property(GLOBAL PROPERTY CORE_APP_LIFECYCLE_REMAINDER "${timeout_trace}")
    expect_ordered("COREAPPTRACE version=1 event=level_loaded generation=1")
    expect_ordered("COREAPPTRACE version=1 event=frame frame=1 generation=1")
    expect_ordered("COREAPPTRACE version=1 event=io_quiesced")
    expect_ordered("COREAPPTRACE version=1 event=load_rejected generation=1 stage=bscn")
    expect_ordered("COREAPPTRACE version=1 event=frame frame=2 generation=1")
    expect_ordered("COREAPPTRACE version=1 event=level_unloaded generation=1")
    expect_ordered("COREAPPTRACE version=1 event=level_loaded generation=2")
    expect_ordered("COREAPPTRACE version=1 event=frame frame=3 generation=2")
    expect_ordered("COREAPPTRACE version=1 event=runtime_stopped")
    if(NOT timeout_trace MATCHES "event=io_stopped active=0\n")
        record_error("io_timeout: worker/request cleanup did not reach active=0: ${timeout_trace}")
    endif()
else()
    message(STATUS "UNVERIFIED: LD_PRELOAD lifecycle fault injection requires Linux")
endif()

get_property(errors GLOBAL PROPERTY CORE_APP_LIFECYCLE_ERRORS)
if(NOT errors STREQUAL "")
    message(FATAL_ERROR "core_app lifecycle contract failed:\n${errors}")
endif()
message(STATUS "core_app real-process load/unload, failure rollback, and record lifecycle passed")
