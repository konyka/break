# Real-device contract for the application's audio device lane.
#
# Runs the real executable with --audio=device --require-device and asserts
# what the record and null lanes cannot prove:
#   1. a playback backend other than miniaudio's Null backend was opened, and
#      the trace names that backend and the device,
#   2. the probe tone was played by the device (the cursor advanced),
#   3. the command queue drove the device: the listener followed the user on
#      every fixed tick, the Area enter started the chaser source, later ticks
#      moved it, the unload stopped it, and no command failed on the device,
#   4. the device was closed after the runtime stopped admitting work and
#      before the runtime reported it had stopped.
#
# A host without a playback device exits 77 and is reported as UNAVAILABLE
# (skipped). This test does not claim anything about how the sound is heard.

foreach(var CORE_APP WORK ASSET_ROOT)
    if(NOT DEFINED ${var} OR "${${var}}" STREQUAL "")
        message(FATAL_ERROR "${var} is required")
    endif()
endforeach()

file(REMOVE_RECURSE "${WORK}")
file(MAKE_DIRECTORY "${WORK}")

set(trace "${WORK}/audio.trace")
set(scenario "${WORK}/audio.scenario")
file(WRITE "${scenario}"
    "core-app-scenario 1\n"
    "seed 12648430\n"
    "fixed-dt-ns 16666667\n"
    "1 level\n"
    "1 key w 1\n"
    "40 key w 0\n"
    "41 unload\n"
    "42 level\n"
    "60 quit\n")

execute_process(
    COMMAND "${CORE_APP}" --render=record --audio=device --require-device --fixed-step
        --assets "${ASSET_ROOT}" --scenario "${scenario}" --trace "${trace}"
    RESULT_VARIABLE run_rc
    OUTPUT_VARIABLE run_out
    ERROR_VARIABLE run_err
    TIMEOUT 120)

if(run_rc EQUAL 77)
    set(reason "no playback device")
    if(EXISTS "${trace}")
        file(READ "${trace}" early_trace)
        if(early_trace MATCHES "event=audio mode=device result=ready")
            message(FATAL_ERROR "exit 77 after a device was opened\n${early_trace}")
        endif()
        if(early_trace MATCHES "event=audio mode=device result=unavailable backend=([^ \n]+)")
            set(reason "only the ${CMAKE_MATCH_1} backend opened")
        endif()
    endif()
    # CORE_APP_AUDIO_DEVICE_UNAVAILABLE is matched by SKIP_REGULAR_EXPRESSION
    # so a CMake older than 3.29 (no cmake_language EXIT) still reports a skip.
    message(STATUS "CORE_APP_AUDIO_DEVICE_UNAVAILABLE: ${reason}")
    if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.29)
        cmake_language(EXIT 77)
    endif()
    message(FATAL_ERROR "CORE_APP_AUDIO_DEVICE_UNAVAILABLE: this CMake cannot emit skip code 77")
endif()
if(NOT run_rc EQUAL 0)
    message(FATAL_ERROR "core_app --audio=device exited ${run_rc}\n${run_out}\n${run_err}")
endif()

if(NOT EXISTS "${trace}")
    message(FATAL_ERROR "missing trace ${trace}")
endif()
file(READ "${trace}" trace_text)

if(NOT trace_text MATCHES
   "event=audio mode=device result=ready backend=([^ \n]+) device=([^\n]+) probe_source=[1-9][0-9]*")
    message(FATAL_ERROR "no playback device was opened\n${trace_text}")
endif()
set(device_backend "${CMAKE_MATCH_1}")
set(device_name "${CMAKE_MATCH_2}")
if(device_backend STREQUAL "Null" OR device_backend STREQUAL "fake" OR
   device_backend STREQUAL "none")
    message(FATAL_ERROR "backend ${device_backend} is not a playback device")
endif()
if(device_name STREQUAL "none" OR device_name STREQUAL "")
    message(FATAL_ERROR "the device reported no name")
endif()

if(NOT trace_text MATCHES
   "event=audio mode=device result=stopped backend=${device_backend} probe_complete=([01]) probe_seconds=([0-9.]+) failures=([0-9]+) listener_updates=([0-9]+) plays=([0-9]+) moves=([0-9]+) stops=([0-9]+) evictions=([0-9]+)")
    message(FATAL_ERROR "the device was never closed\n${trace_text}")
endif()
set(probe_complete "${CMAKE_MATCH_1}")
set(probe_seconds "${CMAKE_MATCH_2}")
set(device_failures "${CMAKE_MATCH_3}")
set(listener_updates "${CMAKE_MATCH_4}")
set(device_plays "${CMAKE_MATCH_5}")
set(device_moves "${CMAKE_MATCH_6}")
set(device_stops "${CMAKE_MATCH_7}")
# Every device call after start-up must come from the audio owner thread.
if(NOT trace_text MATCHES "event=audio mode=device result=stopped [^\n]* owner_thread=1\n")
    message(FATAL_ERROR "the device was not driven by the audio owner thread\n${trace_text}")
endif()
# The listener follows the user once per fixed tick, so a 60-tick run must
# have driven the device listener on (almost) every tick, not just once.
if(listener_updates LESS 40)
    message(FATAL_ERROR "the command queue drove the device listener only ${listener_updates} times")
endif()
# Walking forward enters the trigger Area at tick 30: one PLAY_3D on the
# chaser, POSITION on ticks 31..40, and the tick-41 unload STOPs it.
if(NOT device_plays EQUAL 1 OR device_moves LESS 5 OR device_stops LESS 1)
    message(FATAL_ERROR "level sound did not reach the device: plays=${device_plays}"
                        " moves=${device_moves} stops=${device_stops}")
endif()
if(NOT device_failures EQUAL 0)
    message(FATAL_ERROR "${device_failures} commands failed on the device")
endif()
if(probe_seconds LESS_EQUAL 0)
    message(FATAL_ERROR "the device never played the probe (cursor ${probe_seconds}s)")
endif()

# Lifecycle order: ready before the runtime runs, stopped before it stops.
string(FIND "${trace_text}" "event=audio mode=device result=ready" ready_at)
string(FIND "${trace_text}" "event=runtime_running" running_at)
string(FIND "${trace_text}" "event=audio mode=device result=stopped" stopped_at)
string(FIND "${trace_text}" "event=runtime_stopped" runtime_stopped_at)
if(running_at LESS 0 OR runtime_stopped_at LESS 0)
    message(FATAL_ERROR "runtime lifecycle markers missing\n${trace_text}")
endif()
if(NOT (ready_at LESS running_at AND running_at LESS stopped_at AND
        stopped_at LESS runtime_stopped_at))
    message(FATAL_ERROR "device lifecycle out of order: ready=${ready_at} running=${running_at}"
                        " stopped=${stopped_at} runtime_stopped=${runtime_stopped_at}")
endif()

message(STATUS "verified audio device backend=${device_backend} device=${device_name}"
               " probe_complete=${probe_complete} probe_seconds=${probe_seconds}"
               " listener_updates=${listener_updates} plays=${device_plays}"
               " moves=${device_moves} stops=${device_stops}")
