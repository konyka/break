foreach(var CORE_APP CRASH_RECORD ASSET_ROOT WORK FAULT_LIBRARY FAULT_SUPPORTED
        SANITIZER_PRELOAD CROSSCOMPILING)
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

set(errors "")
file(REMOVE_RECURSE "${WORK}")
file(MAKE_DIRECTORY "${WORK}")
set(scenario "${WORK}/crash.scenario")
set(trace "${WORK}/crash.trace")
set(spool "${WORK}/spool")
file(WRITE "${scenario}"
    "core-app-scenario 1\n"
    "seed 12648430\n"
    "fixed-dt-ns 16666667\n"
    "1 level\n"
    "1 key w 1\n"
    "3 quit\n")

set(preload "${FAULT_LIBRARY}")
if(NOT "${SANITIZER_PRELOAD}" STREQUAL "")
    set(preload "${SANITIZER_PRELOAD}:${FAULT_LIBRARY}")
endif()
set(ENV{LD_PRELOAD} "${preload}")
set(ENV{CORE_APP_TEST_ABORT_ON_FRAME} "2")
execute_process(
    COMMAND "${CORE_APP}" --render=record --audio=record --fixed-step
        --assets "${ASSET_ROOT}" --scenario "${scenario}" --trace "${trace}"
        --crash-context "${spool}"
    RESULT_VARIABLE crash_rc
    OUTPUT_VARIABLE crash_out
    ERROR_VARIABLE crash_err
    TIMEOUT 30)
set(ENV{LD_PRELOAD} "")
set(ENV{CORE_APP_TEST_ABORT_ON_FRAME} "")

if(NOT "${crash_rc}" STREQUAL "Subprocess aborted")
    string(APPEND errors
        "core_app did not terminate with SIGABRT at frame 2: result=${crash_rc}; stdout=${crash_out}; stderr=${crash_err}\n")
else()
    execute_process(
        COMMAND "${CRASH_RECORD}" "${spool}" 1
        RESULT_VARIABLE verify_rc
        OUTPUT_VARIABLE verify_out
        ERROR_VARIABLE verify_err
        TIMEOUT 20)
    if(NOT verify_rc EQUAL 0)
        string(APPEND errors
            "core_app_crash_record ${spool} 1 failed: exit=${verify_rc}; stdout=${verify_out}; stderr=${verify_err}\n")
    endif()

    file(GLOB pending_records "${spool}/pending/*.bcr")
    list(LENGTH pending_records pending_count)
    if(NOT pending_count EQUAL 1)
        string(APPEND errors "pending crash records=${pending_count}, want=1\n")
    else()
        list(GET pending_records 0 pending_record)
        file(READ "${pending_record}" record_text)
        if(NOT record_text MATCHES "signo: 00000006\n")
            string(APPEND errors "crash record does not contain SIGABRT (6): ${record_text}\n")
        endif()
    endif()

    if(NOT EXISTS "${trace}")
        string(APPEND errors "the real record-backend run wrote no trace\n")
    else()
        file(READ "${trace}" trace_text)
        if(NOT trace_text MATCHES "event=level_loaded generation=1\n" OR
                NOT trace_text MATCHES "event=frame frame=1 generation=1\n")
            string(APPEND errors
                "the run did not complete its valid level and first frame: ${trace_text}\n")
        endif()
    endif()
endif()

file(REMOVE_RECURSE "${WORK}")
if(NOT "${errors}" STREQUAL "")
    message(FATAL_ERROR "core_app crash-context full-process contract failed:\n${errors}")
endif()
message(STATUS
    "core_app SIGABRT signo=6 at frame 2; core_app_crash_record(root,1)=0 verified record/none/live=false/keys=1")
