# Contract for opening audio devices by name from the application CLI.
#
# Deterministic on every host:
#   1. --audio-device with a name no device has exits 2 (not 77) and the
#      trace carries "event=audio mode=device result=rejected
#      reason=device_name", with or without --require-device,
#   2. both options are refused without the device mode they need.
# With a playback device (voice needs one before it looks up the capture):
#   3. --voice-capture-device with an unknown name exits 2 with
#      "event=voice mode=device result=rejected reason=device_name",
#   4. the default device's name from the ready line opens again by name and
#      the ready line names the same device.
# A host without a playback device runs 1-2 and reports a skip.

foreach(var CORE_APP WORK ASSET_ROOT)
    if(NOT DEFINED ${var} OR "${${var}}" STREQUAL "")
        message(FATAL_ERROR "${var} is required")
    endif()
endforeach()

file(REMOVE_RECURSE "${WORK}")
file(MAKE_DIRECTORY "${WORK}")

set(trace "${WORK}/named.trace")
set(scenario "${WORK}/named.scenario")
file(WRITE "${scenario}"
    "core-app-scenario 1\n"
    "seed 12648430\n"
    "fixed-dt-ns 16666667\n"
    "1 level\n"
    "10 quit\n")

function(run_core_app out_rc out_trace)
    file(REMOVE "${trace}")
    execute_process(
        COMMAND "${CORE_APP}" --render=record --fixed-step --assets "${ASSET_ROOT}"
            --scenario "${scenario}" --trace "${trace}" ${ARGN}
        RESULT_VARIABLE rc
        OUTPUT_VARIABLE out
        ERROR_VARIABLE err
        TIMEOUT 120)
    set(text "")
    if(EXISTS "${trace}")
        file(READ "${trace}" text)
    endif()
    set(${out_rc} "${rc}" PARENT_SCOPE)
    set(${out_trace} "${text}\n${out}\n${err}" PARENT_SCOPE)
endfunction()

foreach(required "" "--require-device")
    run_core_app(rc text --audio=device ${required} --audio-device "no such speaker")
    if(NOT rc EQUAL 2)
        message(FATAL_ERROR "unknown playback name ${required} exited ${rc}\n${text}")
    endif()
    if(NOT text MATCHES "event=audio mode=device result=rejected reason=device_name\n")
        message(FATAL_ERROR "unknown playback name was not rejected\n${text}")
    endif()
    if(text MATCHES "event=audio mode=device result=(ready|unavailable)")
        message(FATAL_ERROR "unknown playback name opened or degraded\n${text}")
    endif()
endforeach()

execute_process(
    COMMAND "${CORE_APP}" --audio=null --audio-device "x"
    RESULT_VARIABLE rc ERROR_VARIABLE err OUTPUT_QUIET TIMEOUT 30)
if(NOT rc EQUAL 2 OR NOT err MATCHES "--audio-device requires --audio=device")
    message(FATAL_ERROR "--audio-device without --audio=device: ${rc}\n${err}")
endif()
execute_process(
    COMMAND "${CORE_APP}" --audio=device --voice-capture-device "x"
    RESULT_VARIABLE rc ERROR_VARIABLE err OUTPUT_QUIET TIMEOUT 30)
if(NOT rc EQUAL 2 OR NOT err MATCHES "--voice-capture-device requires --voice=device")
    message(FATAL_ERROR "--voice-capture-device without --voice=device: ${rc}\n${err}")
endif()

run_core_app(rc text --require-device --audio=device)
if(rc EQUAL 77)
    message(STATUS "CORE_APP_NAMED_DEVICE_UNAVAILABLE: no playback device for the named reopen")
    if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.29)
        cmake_language(EXIT 77)
    endif()
    message(FATAL_ERROR "CORE_APP_NAMED_DEVICE_UNAVAILABLE: this CMake cannot emit skip code 77")
endif()
if(NOT rc EQUAL 0)
    message(FATAL_ERROR "core_app --audio=device exited ${rc}\n${text}")
endif()
if(NOT text MATCHES "event=audio mode=device result=ready backend=[^ \n]+ device=([^\n]+) probe_source=")
    message(FATAL_ERROR "no ready line with a device name\n${text}")
endif()
set(device "${CMAKE_MATCH_1}")

# The capture name lookup runs after the playback device opened, so the
# rejection is reached on any host that has a playback device.
run_core_app(rc text --audio=device --voice=device --voice-capture-device "no such microphone")
if(NOT rc EQUAL 2)
    message(FATAL_ERROR "unknown capture name exited ${rc}\n${text}")
endif()
if(NOT text MATCHES "event=voice mode=device result=rejected reason=device_name\n")
    message(FATAL_ERROR "unknown capture name was not rejected\n${text}")
endif()

run_core_app(rc text --require-device --audio=device --audio-device "${device}")
if(NOT rc EQUAL 0)
    message(FATAL_ERROR "reopening '${device}' by name exited ${rc}\n${text}")
endif()
if(NOT text MATCHES "result=ready backend=[^ \n]+ device=([^\n]+) probe_source=")
    message(FATAL_ERROR "no ready line for '${device}'\n${text}")
endif()
if(NOT CMAKE_MATCH_1 STREQUAL device)
    message(FATAL_ERROR "opened '${CMAKE_MATCH_1}' instead of '${device}'")
endif()
message(STATUS "named playback device '${device}' reopened by name")
