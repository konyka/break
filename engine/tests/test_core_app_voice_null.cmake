# Contract for the voice lane's "no microphone" path.
#
# Runs the real executable with --audio=device --voice=device and
# --voice-null-capture, which forces miniaudio's Null capture backend. That
# backend opens successfully and would deliver silence forever, so the lane
# must treat it as an absent microphone:
#   1. with --require-device the run exits 77 and the trace names
#      reason=capture, and the lane never reports ready,
#   2. without --require-device the run succeeds, still reports the
#      unavailable line with fallback=off, and writes no ready or stopped line.
#
# A host without a playback device also exits 77, with event=audio ...
# result=unavailable in the trace; the test then reports itself skipped
# (exit 77) because the Null capture branch is unreachable there.

foreach(var CORE_APP WORK ASSET_ROOT)
    if(NOT DEFINED ${var} OR "${${var}}" STREQUAL "")
        message(FATAL_ERROR "${var} is required")
    endif()
endforeach()

file(REMOVE_RECURSE "${WORK}")
file(MAKE_DIRECTORY "${WORK}")

set(scenario "${WORK}/null.scenario")
file(WRITE "${scenario}"
    "core-app-scenario 1\n"
    "seed 12648430\n"
    "fixed-dt-ns 16666667\n"
    "1 level\n"
    "20 quit\n")

function(run_lane name require)
    set(trace "${WORK}/${name}.trace")
    if(require)
        set(flags --require-device)
    else()
        set(flags "")
    endif()
    execute_process(
        COMMAND "${CORE_APP}" --render=record --audio=device --voice=device
            --voice-null-capture ${flags}
            --fixed-step --assets "${ASSET_ROOT}" --scenario "${scenario}"
            --trace "${trace}"
        RESULT_VARIABLE rc
        OUTPUT_VARIABLE out
        ERROR_VARIABLE err)
    if(rc EQUAL 77 AND EXISTS "${trace}")
        file(READ "${trace}" early)
        if(early MATCHES "event=audio mode=device result=unavailable")
            # No playback device: the voice lane never gets as far as the
            # capture device, so this host cannot exercise the Null branch.
            message(STATUS "CORE_APP_VOICE_NULL_UNAVAILABLE: no playback device")
            if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.29)
                cmake_language(EXIT 77)
            endif()
            message(FATAL_ERROR "CORE_APP_VOICE_NULL_UNAVAILABLE: this CMake cannot emit skip code 77")
        endif()
    endif()
    if(require)
        if(NOT rc EQUAL 77)
            message(FATAL_ERROR "required voice device with a Null capture exited ${rc}\n${out}\n${err}")
        endif()
    else()
        if(NOT rc EQUAL 0)
            message(FATAL_ERROR "optional voice device with a Null capture exited ${rc}\n${out}\n${err}")
        endif()
    endif()
    file(READ "${trace}" text)
    if(NOT text MATCHES "event=voice mode=device result=unavailable reason=capture fallback=(none|off)")
        message(FATAL_ERROR "the Null capture backend was not reported unavailable\n${text}")
    endif()
    if(text MATCHES "event=voice mode=device result=ready")
        message(FATAL_ERROR "the Null capture backend reported the lane ready\n${text}")
    endif()
    if(text MATCHES "event=voice mode=device result=stopped")
        message(FATAL_ERROR "the Null capture backend reported a stop\n${text}")
    endif()
    if(require)
        if(NOT text MATCHES "fallback=none")
            message(FATAL_ERROR "a required voice device fell back instead of failing\n${text}")
        endif()
    else()
        if(NOT text MATCHES "fallback=off")
            message(FATAL_ERROR "an optional voice device did not fall back to off\n${text}")
        endif()
    endif()
    message(STATUS "core_app voice null capture: ${name} ok")
endfunction()

run_lane(required TRUE)
run_lane(optional FALSE)
