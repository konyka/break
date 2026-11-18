# Executable contract for the core_app voice lane (--voice).
#
# Runs the real executable and asserts:
#   1. --voice=fake pumps the voice PCM path inside the app: the voice lane is
#      ready before the runtime runs and stopped before it stops, every frame
#      it produced was consumed in sequence, none was dropped, and the
#      processed PCM is not silent. This is a smoke check of the wiring: with
#      a silent FAKE reference the processor configuration is close to
#      pass-through, so it does not measure echo cancellation quality,
#   2. two identical fake runs write byte-identical traces,
#   3. a run without --voice writes no voice event,
#   4. an unknown --voice value, --voice=device without --audio=device, and
#      --voice-null-capture without --voice=device are CLI errors (exit 2).

foreach(var CORE_APP WORK ASSET_ROOT)
    if(NOT DEFINED ${var} OR "${${var}}" STREQUAL "")
        message(FATAL_ERROR "${var} is required")
    endif()
endforeach()

file(REMOVE_RECURSE "${WORK}")
file(MAKE_DIRECTORY "${WORK}")

set(scenario "${WORK}/voice.scenario")
file(WRITE "${scenario}"
    "core-app-scenario 1\n"
    "seed 12648430\n"
    "fixed-dt-ns 16666667\n"
    "1 level\n"
    "1 key w 1\n"
    "40 key w 0\n"
    "100 quit\n")

function(run_app name out_trace)
    set(trace "${WORK}/${name}.trace")
    execute_process(
        COMMAND "${CORE_APP}" --render=record --audio=record --fixed-step
            --assets "${ASSET_ROOT}" --scenario "${scenario}" --trace "${trace}" ${ARGN}
        RESULT_VARIABLE rc
        OUTPUT_VARIABLE out
        ERROR_VARIABLE err
        TIMEOUT 60)
    if(NOT rc EQUAL 0)
        message(FATAL_ERROR "${name}: core_app exited ${rc}\n${out}\n${err}")
    endif()
    file(READ "${trace}" text)
    set(${out_trace} "${text}" PARENT_SCOPE)
endfunction()

run_app(fake_a fake_a --voice=fake)
run_app(fake_b fake_b --voice=fake)
run_app(off off)

if(NOT fake_a MATCHES "event=voice mode=fake result=ready frames=480 capture=fake\n")
    message(FATAL_ERROR "the voice lane never became ready\n${fake_a}")
endif()
if(NOT fake_a MATCHES
   "event=voice mode=fake result=stopped produced=([0-9]+) consumed=([0-9]+) dropped=([0-9]+) sequence_gaps=([0-9]+) peak=([0-9]+) capture_overruns=([0-9]+) reference_overruns=([0-9]+) capture_recoveries=0 capture_reopen_failures=0\n")
    message(FATAL_ERROR "the voice lane never stopped\n${fake_a}")
endif()
set(produced "${CMAKE_MATCH_1}")
set(consumed "${CMAKE_MATCH_2}")
set(dropped "${CMAKE_MATCH_3}")
set(gaps "${CMAKE_MATCH_4}")
set(peak "${CMAKE_MATCH_5}")
set(capture_overruns "${CMAKE_MATCH_6}")
set(reference_overruns "${CMAKE_MATCH_7}")
# 99 simulated ticks x 800 frames = 79200 frames = 165 packets of 480.
if(produced LESS 160)
    message(FATAL_ERROR "the voice lane produced only ${produced} packets")
endif()
if(NOT consumed EQUAL produced OR NOT dropped EQUAL 0 OR NOT gaps EQUAL 0)
    message(FATAL_ERROR "voice frames lost: produced=${produced} consumed=${consumed}"
                        " dropped=${dropped} sequence_gaps=${gaps}")
endif()
if(peak LESS_EQUAL 0)
    message(FATAL_ERROR "the processed voice PCM is silent")
endif()
if(NOT capture_overruns EQUAL 0 OR NOT reference_overruns EQUAL 0)
    message(FATAL_ERROR "voice overruns: capture=${capture_overruns}"
                        " reference=${reference_overruns}")
endif()

string(FIND "${fake_a}" "event=voice mode=fake result=ready" ready_at)
string(FIND "${fake_a}" "event=runtime_running" running_at)
string(FIND "${fake_a}" "event=voice mode=fake result=stopped" stopped_at)
string(FIND "${fake_a}" "event=runtime_stopped" runtime_stopped_at)
if(running_at LESS 0 OR runtime_stopped_at LESS 0)
    message(FATAL_ERROR "runtime lifecycle markers missing\n${fake_a}")
endif()
if(NOT (ready_at LESS running_at AND running_at LESS stopped_at AND
        stopped_at LESS runtime_stopped_at))
    message(FATAL_ERROR "voice lifecycle out of order: ready=${ready_at} running=${running_at}"
                        " stopped=${stopped_at} runtime_stopped=${runtime_stopped_at}")
endif()

if(NOT fake_a STREQUAL fake_b)
    message(FATAL_ERROR "two identical fake voice runs wrote different traces")
endif()
if(off MATCHES "event=voice")
    message(FATAL_ERROR "a run without --voice wrote a voice event\n${off}")
endif()

foreach(bad_args "--voice=bogus" "--voice=device" "--voice-null-capture"
                 "--voice=fake;--voice-null-capture")
    execute_process(
        COMMAND "${CORE_APP}" --render=record --audio=record --fixed-step
            --assets "${ASSET_ROOT}" --scenario "${scenario}" ${bad_args}
        RESULT_VARIABLE rc
        OUTPUT_VARIABLE out
        ERROR_VARIABLE err
        TIMEOUT 30)
    if(NOT rc EQUAL 2)
        message(FATAL_ERROR "${bad_args} with --audio=record exited ${rc}, want 2\n${err}")
    endif()
    # Exit 2 is also the runtime-failure code, so the CLI diagnostic is what
    # proves the arguments were rejected before the runtime started.
    if(err MATCHES "runtime returned" OR NOT err MATCHES "core_app: (invalid|--voice)")
        message(FATAL_ERROR "${bad_args} was not rejected as a CLI error\n${err}")
    endif()
endforeach()
