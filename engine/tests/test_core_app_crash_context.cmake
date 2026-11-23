foreach(var CORE_APP CRASH_RECORD ASSET_ROOT WORK FAULT_LIBRARY FAULT_SUPPORTED
        SANITIZER_PRELOAD CROSSCOMPILING SANITIZER_ASAN SANITIZER_TSAN SANITIZER_UBSAN)
    if(NOT DEFINED ${var})
        message(FATAL_ERROR "${var} is required")
    endif()
endforeach()

if(NOT FAULT_SUPPORTED OR CROSSCOMPILING OR "${FAULT_LIBRARY}" STREQUAL "")
    message(STATUS
        "UNVERIFIED: core_app crash-context full-process case skipped: native LD_PRELOAD is unavailable")
    if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.29)
        cmake_language(EXIT 77)
    endif()
    message(FATAL_ERROR
        "UNVERIFIED: core_app crash-context full-process case skipped; this CMake cannot emit skip code 77")
endif()
if((SANITIZER_ASAN OR SANITIZER_TSAN) AND "${SANITIZER_PRELOAD}" STREQUAL "")
    message(STATUS
        "UNVERIFIED: core_app crash-context full-process case skipped: ASan/TSan runtime preload is unavailable")
    if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.29)
        cmake_language(EXIT 77)
    endif()
    message(FATAL_ERROR
        "UNVERIFIED: core_app crash-context full-process case skipped; this CMake cannot emit skip code 77")
endif()
if(NOT "${SANITIZER_PRELOAD}" STREQUAL "")
    set(sanitizer_runtime_valid TRUE)
    if(NOT EXISTS "${SANITIZER_PRELOAD}" OR IS_DIRECTORY "${SANITIZER_PRELOAD}")
        set(sanitizer_runtime_valid FALSE)
    else()
        file(READ "${SANITIZER_PRELOAD}" sanitizer_magic OFFSET 0 LIMIT 4 HEX)
        if(NOT sanitizer_magic STREQUAL "7f454c46")
            set(sanitizer_runtime_valid FALSE)
        endif()
    endif()
    if(NOT sanitizer_runtime_valid)
        message(STATUS
            "UNVERIFIED: core_app crash-context full-process case skipped: sanitizer runtime is not an ELF shared object")
        if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.29)
            cmake_language(EXIT 77)
        endif()
        message(FATAL_ERROR
            "UNVERIFIED: core_app crash-context full-process case skipped; this CMake cannot emit skip code 77")
    endif()
endif()

find_program(CORE_APP_ENV_EXECUTABLE NAMES env REQUIRED)
set_property(GLOBAL PROPERTY CORE_APP_CRASH_CONTEXT_ERRORS "")
function(record_error text)
    get_property(errors GLOBAL PROPERTY CORE_APP_CRASH_CONTEXT_ERRORS)
    string(APPEND errors "${text}\n")
    set_property(GLOBAL PROPERTY CORE_APP_CRASH_CONTEXT_ERRORS "${errors}")
endfunction()

function(save_environment name)
    if(DEFINED ENV{${name}})
        set_property(GLOBAL PROPERTY "CORE_APP_SAVED_ENV_${name}_PRESENT" TRUE)
        set_property(GLOBAL PROPERTY "CORE_APP_SAVED_ENV_${name}_VALUE" "$ENV{${name}}")
    else()
        set_property(GLOBAL PROPERTY "CORE_APP_SAVED_ENV_${name}_PRESENT" FALSE)
        set_property(GLOBAL PROPERTY "CORE_APP_SAVED_ENV_${name}_VALUE" "")
    endif()
endfunction()

function(expect_environment_restored name)
    get_property(present GLOBAL PROPERTY "CORE_APP_SAVED_ENV_${name}_PRESENT")
    get_property(value GLOBAL PROPERTY "CORE_APP_SAVED_ENV_${name}_VALUE")
    if(present)
        if(NOT DEFINED ENV{${name}})
            record_error("environment ${name} is unset, want original empty/value")
        elseif(NOT "$ENV{${name}}" STREQUAL "${value}")
            record_error("environment ${name}='$ENV{${name}}', want original '${value}'")
        endif()
    elseif(DEFINED ENV{${name}})
        record_error("environment ${name} is set, want original unset")
    endif()
endfunction()

macro(save_crash_environment)
    foreach(name LD_PRELOAD CORE_APP_TEST_ABORT_ON_FRAME
            CORE_APP_TEST_ABORT_BEFORE_RUNTIME_RUNNING CORE_APP_TEST_TRACE_SIGACTION)
        save_environment("${name}")
    endforeach()
endmacro()

macro(expect_crash_environment_restored)
    foreach(name LD_PRELOAD CORE_APP_TEST_ABORT_ON_FRAME
            CORE_APP_TEST_ABORT_BEFORE_RUNTIME_RUNNING CORE_APP_TEST_TRACE_SIGACTION)
        expect_environment_restored("${name}")
    endforeach()
endmacro()

function(expect_marker name text prefix expected)
    string(REGEX MATCHALL "${prefix}=[0-9]+" markers "${text}")
    list(LENGTH markers marker_count)
    if(NOT marker_count EQUAL 1)
        record_error("${name}: marker ${prefix} count=${marker_count}, want=1; output=${text}")
    else()
        list(GET markers 0 actual)
        if(NOT "${actual}" STREQUAL "${prefix}=${expected}")
            record_error("${name}: marker=${actual}, want=${prefix}=${expected}; output=${text}")
        endif()
    endif()
endfunction()

function(expect_no_pending name root)
    file(GLOB pending_records "${root}/pending/*.bcr")
    list(LENGTH pending_records pending_count)
    if(NOT pending_count EQUAL 0)
        record_error("${name}: pending crash records=${pending_count}, want=0")
    endif()
endfunction()

function(verify_crash_record name root tick gpu keys)
    if("${gpu}" STREQUAL "")
        execute_process(
            COMMAND "${CORE_APP_ENV_EXECUTABLE}" --unset=LD_PRELOAD
                "${CRASH_RECORD}" "${root}" "${tick}"
            RESULT_VARIABLE verify_rc
            OUTPUT_VARIABLE verify_out
            ERROR_VARIABLE verify_err
            TIMEOUT 20)
    else()
        execute_process(
            COMMAND "${CORE_APP_ENV_EXECUTABLE}" --unset=LD_PRELOAD
                "${CRASH_RECORD}" "${root}" "${tick}" "${gpu}" "${keys}"
            RESULT_VARIABLE verify_rc
            OUTPUT_VARIABLE verify_out
            ERROR_VARIABLE verify_err
            TIMEOUT 20)
    endif()
    if(NOT verify_rc EQUAL 0)
        record_error("${name}: core_app_crash_record failed: exit=${verify_rc}; stdout=${verify_out}; stderr=${verify_err}")
    endif()
    file(GLOB pending_records "${root}/pending/*.bcr")
    list(LENGTH pending_records pending_count)
    if(NOT pending_count EQUAL 1)
        record_error("${name}: pending crash records=${pending_count}, want=1")
    else()
        list(GET pending_records 0 pending_record)
        file(READ "${pending_record}" record_text)
        if(NOT record_text MATCHES "signo: 00000006\n")
            record_error("${name}: crash record does not contain SIGABRT (6)")
        endif()
    endif()
endfunction()

function(run_stop_case name expected_rc scenario)
    set(root "${WORK}/${name}-spool")
    set(trace "${WORK}/${name}.trace")
    execute_process(
        COMMAND "${CORE_APP_ENV_EXECUTABLE}"
            --unset=CORE_APP_TEST_ABORT_ON_FRAME
            --unset=CORE_APP_TEST_ABORT_BEFORE_RUNTIME_RUNNING
            "LD_PRELOAD=${preload}" "CORE_APP_TEST_TRACE_SIGACTION=1"
            "${CORE_APP}" --render=record --audio=record --fixed-step
            --assets "${ASSET_ROOT}" --scenario "${scenario}" --trace "${trace}"
            --crash-context "${root}"
        RESULT_VARIABLE rc
        OUTPUT_VARIABLE out
        ERROR_VARIABLE err
        TIMEOUT 30)
    expect_crash_environment_restored()
    if(NOT "${rc}" STREQUAL "${expected_rc}")
        record_error("${name}: exit=${rc}, want=${expected_rc}; stdout=${out}; stderr=${err}")
    endif()
    expect_marker("${name}" "${out}${err}" "CORE_APP_TEST_SIGACTION_TOTAL" 10)
    expect_no_pending("${name}" "${root}")
    if(expected_rc EQUAL 2 AND NOT "${err}" MATCHES "runtime returned FAILED")
        record_error("${name}: runtime failure did not preserve its diagnostic: ${err}")
    endif()
endfunction()

save_crash_environment()
set(preload "${FAULT_LIBRARY}")
if(NOT "${SANITIZER_PRELOAD}" STREQUAL "")
    set(preload "${SANITIZER_PRELOAD}:${FAULT_LIBRARY}")
endif()
file(REMOVE_RECURSE "${WORK}")
file(MAKE_DIRECTORY "${WORK}")
set(scenario "${WORK}/crash.scenario")
file(WRITE "${scenario}"
    "core-app-scenario 1\n"
    "seed 12648430\n"
    "fixed-dt-ns 16666667\n"
    "1 level\n"
    "1 key w 1\n"
    "3 quit\n")

set(frame_spool "${WORK}/frame-spool")
set(frame_trace "${WORK}/frame.trace")
execute_process(
    COMMAND "${CORE_APP_ENV_EXECUTABLE}"
        --unset=CORE_APP_TEST_ABORT_BEFORE_RUNTIME_RUNNING
        --unset=CORE_APP_TEST_TRACE_SIGACTION
        "LD_PRELOAD=${preload}" "CORE_APP_TEST_ABORT_ON_FRAME=2"
        "${CORE_APP}" --render=record --audio=record --fixed-step
        --assets "${ASSET_ROOT}" --scenario "${scenario}" --trace "${frame_trace}"
        --crash-context "${frame_spool}"
    RESULT_VARIABLE frame_rc
    OUTPUT_VARIABLE frame_out
    ERROR_VARIABLE frame_err
    TIMEOUT 30)
expect_crash_environment_restored()
if(NOT "${frame_rc}" STREQUAL "Subprocess aborted")
    record_error("frame: result=${frame_rc}, want SIGABRT; stdout=${frame_out}; stderr=${frame_err}")
else()
    verify_crash_record(frame "${frame_spool}" 1 "" "")
endif()
expect_marker(frame "${frame_out}${frame_err}" "CORE_APP_TEST_ABORT_ON_FRAME" 2)
if(NOT EXISTS "${frame_trace}")
    record_error("frame: the real record-backend run wrote no trace")
else()
    file(READ "${frame_trace}" frame_trace_text)
    if(NOT frame_trace_text MATCHES "event=level_loaded generation=1\n" OR
            NOT frame_trace_text MATCHES "event=frame frame=1 generation=1\n")
        record_error("frame: valid level and first complete frame are missing: ${frame_trace_text}")
    endif()
endif()

set(initial_spool "${WORK}/initial-spool")
set(initial_trace "${WORK}/initial.trace")
execute_process(
    COMMAND "${CORE_APP_ENV_EXECUTABLE}"
        --unset=CORE_APP_TEST_ABORT_ON_FRAME
        --unset=CORE_APP_TEST_TRACE_SIGACTION
        "LD_PRELOAD=${preload}" "CORE_APP_TEST_ABORT_BEFORE_RUNTIME_RUNNING=1"
        "${CORE_APP}" --render=record --audio=record --fixed-step
        --assets "${ASSET_ROOT}" --scenario "${scenario}" --trace "${initial_trace}"
        --crash-context "${initial_spool}"
    RESULT_VARIABLE initial_rc
    OUTPUT_VARIABLE initial_out
    ERROR_VARIABLE initial_err
    TIMEOUT 30)
expect_crash_environment_restored()
if(NOT "${initial_rc}" STREQUAL "Subprocess aborted")
    record_error("initial: result=${initial_rc}, want SIGABRT before runtime_running; stdout=${initial_out}; stderr=${initial_err}")
else()
    verify_crash_record(initial "${initial_spool}" 0 pending 0)
endif()
expect_marker(initial "${initial_out}${initial_err}" "CORE_APP_TEST_ABORT_BEFORE_RUNTIME_RUNNING" 1)
if(EXISTS "${initial_trace}")
    file(READ "${initial_trace}" initial_trace_text)
    if(initial_trace_text MATCHES "event=runtime_running\n")
        record_error("initial: runtime_running was forwarded before the requested abort")
    endif()
endif()

run_stop_case(success 0 "${scenario}")
run_stop_case(runtime_failure 2 "${WORK}/missing.scenario")

expect_crash_environment_restored()
file(REMOVE_RECURSE "${WORK}")
get_property(errors GLOBAL PROPERTY CORE_APP_CRASH_CONTEXT_ERRORS)
if(NOT "${errors}" STREQUAL "")
    message(FATAL_ERROR "core_app crash-context full-process contract failed:\n${errors}")
endif()
message(STATUS "frame marker=CORE_APP_TEST_ABORT_ON_FRAME=2; tick=1 record verified")
message(STATUS "initial pre-runtime_running SIGABRT verified gpu=pending tick=0 keys=0")
message(STATUS "success/runtime_failure exits=0/2 and sigaction totals=10/10 with no pending records")
