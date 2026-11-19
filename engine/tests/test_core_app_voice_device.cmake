# Real-device contract for the core_app voice lane.
#
# Runs the real executable with --audio=device --voice=device --require-device
# and asserts that the voice worker read the default capture device and the
# playback device's reference tap, and that the CoreAppThread consumed every
# produced frame in sequence. A fixed-step run is much faster than real time,
# so the scenario is long enough for the devices to deliver whole packets.
#
# A host without a playback or capture device exits 77 and is reported as
# skipped. This test does not claim anything about how the voice sounds.

foreach(var CORE_APP WORK ASSET_ROOT)
    if(NOT DEFINED ${var} OR "${${var}}" STREQUAL "")
        message(FATAL_ERROR "${var} is required")
    endif()
endforeach()

file(REMOVE_RECURSE "${WORK}")
file(MAKE_DIRECTORY "${WORK}")

set(trace "${WORK}/voice.trace")
set(scenario "${WORK}/voice.scenario")
file(WRITE "${scenario}"
    "core-app-scenario 1\n"
    "seed 12648430\n"
    "fixed-dt-ns 16666667\n"
    "1 level\n"
    "6000 quit\n")

execute_process(
    COMMAND "${CORE_APP}" --render=record --audio=device --voice=device --require-device
        --fixed-step --assets "${ASSET_ROOT}" --scenario "${scenario}" --trace "${trace}"
    RESULT_VARIABLE run_rc
    OUTPUT_VARIABLE run_out
    ERROR_VARIABLE run_err
    TIMEOUT 120)

if(run_rc EQUAL 77)
    set(reason "no playback device")
    if(EXISTS "${trace}")
        file(READ "${trace}" early_trace)
        if(early_trace MATCHES "event=voice mode=device result=ready")
            message(FATAL_ERROR "exit 77 after the voice lane was ready\n${early_trace}")
        endif()
        if(early_trace MATCHES "event=voice mode=device result=unavailable reason=([a-z]+)")
            set(reason "voice ${CMAKE_MATCH_1} unavailable")
        endif()
    endif()
    message(STATUS "CORE_APP_VOICE_DEVICE_UNAVAILABLE: ${reason}")
    if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.29)
        cmake_language(EXIT 77)
    endif()
    message(FATAL_ERROR "CORE_APP_VOICE_DEVICE_UNAVAILABLE: this CMake cannot emit skip code 77")
endif()
if(NOT run_rc EQUAL 0)
    message(FATAL_ERROR "core_app --voice=device exited ${run_rc}\n${run_out}\n${run_err}")
endif()

file(READ "${trace}" trace_text)
if(NOT trace_text MATCHES "event=voice mode=device result=ready frames=480 capture=([^ \n]+)\n")
    message(FATAL_ERROR "the voice lane never became ready\n${run_err}")
endif()
if(CMAKE_MATCH_1 STREQUAL "none")
    message(FATAL_ERROR "the voice lane is ready without a named capture device\n${trace_text}")
endif()
if(NOT trace_text MATCHES
   "event=voice mode=device result=stopped produced=([0-9]+) consumed=([0-9]+) dropped=([0-9]+) sequence_gaps=([0-9]+) peak=[0-9]+ capture_overruns=[0-9]+ reference_overruns=[0-9]+ capture_recoveries=[0-9]+ capture_reopen_failures=[0-9]+ playback_recoveries=[0-9]+ capture_switches=[0-9]+ capture_switch_rejected=[0-9]+ capture_switch_failures=[0-9]+ drift_corrections=[0-9]+ drift_ppb=-?[0-9]+\n")
    message(FATAL_ERROR "the voice lane never stopped")
endif()
set(produced "${CMAKE_MATCH_1}")
set(consumed "${CMAKE_MATCH_2}")
set(dropped "${CMAKE_MATCH_3}")
set(gaps "${CMAKE_MATCH_4}")
if(produced LESS 1)
    message(FATAL_ERROR "the voice worker produced no packet from the devices")
endif()
# produced counts queued packets only (a full queue counts a drop instead),
# so the consumer must have read every one of them. A worker drop still
# advances the sequence, so every gap must be explained by a drop.
if(NOT consumed EQUAL produced OR NOT gaps LESS_EQUAL dropped)
    message(FATAL_ERROR "voice frames lost: produced=${produced} consumed=${consumed}"
                        " dropped=${dropped} sequence_gaps=${gaps}")
endif()

string(FIND "${trace_text}" "event=voice mode=device result=stopped" voice_stopped_at)
string(FIND "${trace_text}" "event=audio mode=device result=stopped" audio_stopped_at)
if(audio_stopped_at LESS 0 OR NOT voice_stopped_at LESS audio_stopped_at)
    message(FATAL_ERROR "the voice lane did not stop before the playback device closed")
endif()
message(STATUS "core_app voice device: produced=${produced} consumed=${consumed}")

# Runtime capture switch on the real devices: an unknown name is refused and
# the old input keeps running, then the default input opens again. The worker
# handles each request on its own thread, so the requests are far apart.
set(switch_trace "${WORK}/switch.trace")
set(switch_scenario "${WORK}/switch.scenario")
file(WRITE "${switch_scenario}"
    "core-app-scenario 1\n"
    "seed 12648430\n"
    "fixed-dt-ns 16666667\n"
    "1 level\n"
    "100 voice-capture-device no such microphone\n"
    "3000 voice-capture-device\n"
    "6000 quit\n")
execute_process(
    COMMAND "${CORE_APP}" --render=record --audio=device --voice=device --require-device
        --fixed-step --assets "${ASSET_ROOT}" --scenario "${switch_scenario}"
        --trace "${switch_trace}"
    RESULT_VARIABLE switch_rc
    OUTPUT_VARIABLE switch_out
    ERROR_VARIABLE switch_err
    TIMEOUT 120)
if(NOT switch_rc EQUAL 0)
    message(FATAL_ERROR "capture switch run exited ${switch_rc}\n${switch_out}\n${switch_err}")
endif()
file(READ "${switch_trace}" switch_text)
string(FIND "${switch_text}"
    "event=voice_capture_device result=rejected reason=device_name\n" refused_at)
string(FIND "${switch_text}"
    "event=voice_capture_device result=switched device=default\n" switched_at)
if(refused_at LESS 0 OR switched_at LESS 0 OR NOT refused_at LESS switched_at)
    message(FATAL_ERROR "capture switch results missing or out of order\n${switch_text}")
endif()
if(NOT switch_text MATCHES
   "event=voice mode=device result=stopped produced=([0-9]+) consumed=([0-9]+) [^\n]* capture_switches=1 capture_switch_rejected=1 capture_switch_failures=0 drift_corrections=[0-9]+ drift_ppb=-?[0-9]+\n")
    message(FATAL_ERROR "the stopped line does not count the switches\n${switch_text}")
endif()
if(NOT CMAKE_MATCH_1 EQUAL CMAKE_MATCH_2)
    message(FATAL_ERROR "capture switch run lost frames: produced=${CMAKE_MATCH_1}"
                        " consumed=${CMAKE_MATCH_2}")
endif()
message(STATUS "core_app voice device switch: refused unknown name, reopened default")
