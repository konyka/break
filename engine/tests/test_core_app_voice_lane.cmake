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
#      --voice-null-capture without --voice=device are CLI errors (exit 2),
#   5. scenario voice-capture-device switches are traced and counted (see
#      the section below),
#   6. --voice-aligner-sinc and --voice-aligner-crossfade reach the lane's
#      aligner, and misuse of either is a CLI error,
#   7. --voice-bypass reaches the lane's processor, and misuse is a CLI error.

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
        COMMAND ${CORE_APP_RUNNER} "${CORE_APP}" --render=record --audio=record --fixed-step
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
   "event=voice mode=fake result=stopped produced=([0-9]+) consumed=([0-9]+) dropped=([0-9]+) sequence_gaps=([0-9]+) peak=([0-9]+) capture_overruns=([0-9]+) reference_overruns=([0-9]+) capture_recoveries=0 capture_reopen_failures=0 playback_recoveries=0 capture_switches=0 capture_switch_rejected=0 capture_switch_failures=0 drift_corrections=[0-9]+ drift_ppb=-?[0-9]+\n")
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

# 5. Runtime capture switches: a FAKE capture accepts the default and
#    refuses a name; both results are traced in order, the stopped line
#    counts them, the run keeps producing every frame, two runs stay
#    byte-identical, and without --voice the request is refused (mode).
set(switch_scenario "${WORK}/switch.scenario")
file(WRITE "${switch_scenario}"
    "core-app-scenario 1\n"
    "seed 12648430\n"
    "fixed-dt-ns 16666667\n"
    "1 level\n"
    "10 voice-capture-device\n"
    "20 voice-capture-device no such microphone\n"
    "100 quit\n")
set(scenario_saved "${scenario}")
set(scenario "${switch_scenario}")
run_app(switch_a switch_a --voice=fake)
run_app(switch_b switch_b --voice=fake)
run_app(switch_off switch_off)
set(scenario "${scenario_saved}")
string(FIND "${switch_a}"
    "event=voice_capture_device result=switched device=default\n" switched_at)
string(FIND "${switch_a}"
    "event=voice_capture_device result=rejected reason=device_name\n" refused_at)
if(switched_at LESS 0 OR refused_at LESS 0 OR NOT switched_at LESS refused_at)
    message(FATAL_ERROR "capture switch results missing or out of order\n${switch_a}")
endif()
if(NOT switch_a MATCHES
   "event=voice mode=fake result=stopped produced=([0-9]+) consumed=([0-9]+) dropped=0 sequence_gaps=0 [^\n]* capture_switches=1 capture_switch_rejected=1 capture_switch_failures=0 drift_corrections=[0-9]+ drift_ppb=-?[0-9]+\n")
    message(FATAL_ERROR "the stopped line does not count the switches\n${switch_a}")
endif()
if(NOT CMAKE_MATCH_1 EQUAL CMAKE_MATCH_2 OR CMAKE_MATCH_1 LESS 150)
    message(FATAL_ERROR "switch run lost frames: produced=${CMAKE_MATCH_1}"
                        " consumed=${CMAKE_MATCH_2}")
endif()
if(NOT switch_a STREQUAL switch_b)
    message(FATAL_ERROR "two identical capture switch runs wrote different traces")
endif()
if(NOT switch_off MATCHES
   "event=voice_capture_device result=rejected tick=10 reason=mode\n.*event=voice_capture_device result=rejected tick=20 reason=mode\n")
    message(FATAL_ERROR "a switch without --voice was not refused\n${switch_off}")
endif()

# 6. A request accepted on the quit tick is never pumped: it still gets
#    exactly one result line, reason=stopped, before the stopped line.
set(late_scenario "${WORK}/late.scenario")
file(WRITE "${late_scenario}"
    "core-app-scenario 1\n"
    "seed 12648430\n"
    "fixed-dt-ns 16666667\n"
    "1 level\n"
    "50 voice-capture-device\n"
    "50 quit\n")
set(scenario "${late_scenario}")
run_app(late late --voice=fake)
set(scenario "${scenario_saved}")
string(REGEX MATCHALL "event=voice_capture_device result=[^\n]*\n" late_results "${late}")
list(LENGTH late_results late_count)
if(NOT late_count EQUAL 1 OR NOT late MATCHES
   "event=voice_capture_device result=failed reason=stopped\n[^\n]*\n?.*event=voice mode=fake result=stopped [^\n]* capture_switches=0 capture_switch_rejected=0 capture_switch_failures=0 drift_corrections=[0-9]+ drift_ppb=-?[0-9]+\n")
    message(FATAL_ERROR "a request left at stop got no single stopped result\n${late}")
endif()

# 6. Aligner modes from the command line: the lane traces the settings its
#    aligner reports, still delivers every frame, stays deterministic, and a
#    run without the flags writes no aligner line.
run_app(modes_a modes_a --voice=fake --voice-aligner-sinc --voice-aligner-crossfade 480)
run_app(modes_b modes_b --voice=fake --voice-aligner-sinc --voice-aligner-crossfade 480)
run_app(sinc_only sinc_only --voice=fake --voice-aligner-sinc)
if(NOT modes_a MATCHES "event=voice mode=fake result=ready frames=480 capture=fake\nCOREAPPTRACE version=1 event=voice_aligner sinc=1 crossfade=480\n")
    message(FATAL_ERROR "the aligner modes were not traced after ready\n${modes_a}")
endif()
if(NOT sinc_only MATCHES "event=voice_aligner sinc=1 crossfade=0\n")
    message(FATAL_ERROR "--voice-aligner-sinc alone was not traced\n${sinc_only}")
endif()
if(NOT modes_a MATCHES "result=stopped produced=([0-9]+) consumed=([0-9]+) dropped=0 sequence_gaps=0 ")
    message(FATAL_ERROR "the aligner modes lost voice frames\n${modes_a}")
endif()
if(CMAKE_MATCH_1 LESS 160 OR NOT CMAKE_MATCH_1 EQUAL CMAKE_MATCH_2)
    message(FATAL_ERROR "the aligner modes produced ${CMAKE_MATCH_1}, consumed ${CMAKE_MATCH_2}")
endif()
if(NOT modes_a STREQUAL modes_b)
    message(FATAL_ERROR "two identical aligner-mode runs wrote different traces")
endif()
if(fake_a MATCHES "event=voice_aligner")
    message(FATAL_ERROR "a run without aligner flags traced aligner modes\n${fake_a}")
endif()

# 7. Processor bypass from the command line: the lane traces the stages its
#    processor skips, in a fixed order after the aligner line, still delivers
#    every frame and stays deterministic; misuse is a CLI error.
run_app(bypass_a bypass_a --voice=fake --voice-bypass=gate,agc)
run_app(bypass_b bypass_b --voice=fake --voice-bypass=gate,agc)
run_app(bypass_all bypass_all --voice=fake --voice-bypass agc,echo,noise,gate,echo
        --voice-aligner-sinc)
if(NOT bypass_a MATCHES "event=voice mode=fake result=ready frames=480 capture=fake\nCOREAPPTRACE version=1 event=voice_bypass echo=0 noise=0 gate=1 agc=1\n")
    message(FATAL_ERROR "the bypassed stages were not traced after ready\n${bypass_a}")
endif()
if(NOT bypass_all MATCHES "event=voice_aligner sinc=1 crossfade=0\nCOREAPPTRACE version=1 event=voice_bypass echo=1 noise=1 gate=1 agc=1\n")
    message(FATAL_ERROR "the aligner and bypass lines are out of order\n${bypass_all}")
endif()
if(NOT bypass_a MATCHES "result=stopped produced=([0-9]+) consumed=([0-9]+) dropped=0 sequence_gaps=0 ")
    message(FATAL_ERROR "the bypass run lost voice frames\n${bypass_a}")
endif()
if(CMAKE_MATCH_1 LESS 160 OR NOT CMAKE_MATCH_1 EQUAL CMAKE_MATCH_2)
    message(FATAL_ERROR "the bypass run produced ${CMAKE_MATCH_1}, consumed ${CMAKE_MATCH_2}")
endif()
if(NOT bypass_a STREQUAL bypass_b)
    message(FATAL_ERROR "two identical bypass runs wrote different traces")
endif()
if(fake_a MATCHES "event=voice_bypass" OR modes_a MATCHES "event=voice_bypass")
    message(FATAL_ERROR "a run without --voice-bypass traced bypassed stages")
endif()

foreach(bad_args "--voice=bogus" "--voice=device" "--voice-null-capture"
                 "--voice=fake;--voice-null-capture"
                 "--voice-aligner-sinc" "--voice-aligner-crossfade;480"
                 "--voice=fake;--voice-aligner-crossfade;0"
                 "--voice=fake;--voice-aligner-crossfade;48001"
                 "--voice=fake;--voice-aligner-crossfade;12x"
                 "--voice-bypass=gate" "--voice=fake;--voice-bypass=gate,,agc"
                 "--voice=fake;--voice-bypass=reverb" "--voice=fake;--voice-bypass=,"
                 "--voice=fake;--voice-bypass=gate,")
    execute_process(
        COMMAND ${CORE_APP_RUNNER} "${CORE_APP}" --render=record --audio=record --fixed-step
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
