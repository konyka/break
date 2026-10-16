# Plan C Task 13: consumer smoke for the macOS Metal lane.
# Asserts dxx_break / engine_demo binaries exist and engine_demo can run
# --frames 3 to a clean exit on a real Mac. Exits 77 (ctest SKIP) when the
# lane is not APPLE+metal or no window service is available.
cmake_policy(SET CMP0054 NEW)
if(POLICY CMP0140)
    cmake_policy(SET CMP0140 NEW)
endif()
if(NOT DEFINED BUILD_DIR OR NOT DEFINED SOURCE_DIR OR NOT DEFINED METAL_LANE)
    message(FATAL_ERROR "BUILD_DIR, SOURCE_DIR and METAL_LANE are required")
endif()
if(NOT DEFINED BIN_EXT)
    set(BIN_EXT "")
endif()

# Skip protocol (test_d3d12_dependency_gate.cmake precedent): SKIP_RETURN_CODE
# only works when the script actually EXITS with 77; a bare return() reports
# exit 0 = a structural false pass (review fix C1).
function(smoke_skip reason)
    message(STATUS "test_macos_metal_consumer_smoke: SKIP (${reason})")
    if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.29)
        cmake_language(EXIT 77)
    endif()
    # cmake_language(EXIT) was added in CMake 3.29; older script-mode cmake
    # cannot exit with code 77. Fail loudly instead — never a silent pass.
    message(FATAL_ERROR "test_macos_metal_consumer_smoke: SKIP fallback (${reason}; cmake < 3.29 cannot exit 77)")
endfunction()

if(NOT METAL_LANE)
    smoke_skip("not the APPLE+metal lane")
endif()

set(failures 0)
foreach(binary dxx_break engine_demo)
    if(NOT EXISTS "${BUILD_DIR}/${binary}${BIN_EXT}")
        message(WARNING "MISSING BINARY: ${BUILD_DIR}/${binary}")
        math(EXPR failures "${failures} + 1")
    endif()
endforeach()
if(failures GREATER 0)
    message(FATAL_ERROR "test_macos_metal_consumer_smoke: ${failures} binary check(s) failed")
endif()

# engine_demo must early-exit cleanly. Window-service failures (SSH without
# a console session, CI runner) map to SKIP, never a fabricated pass.
execute_process(
    COMMAND "${BUILD_DIR}/engine_demo${BIN_EXT}" --frames 3
    WORKING_DIRECTORY "${SOURCE_DIR}"
    TIMEOUT 180
    RESULT_VARIABLE rc
    OUTPUT_VARIABLE out
    ERROR_VARIABLE err
)
set(log "${out}\n${err}")
if(rc EQUAL 0)
    # Hard indicators (review fix I1): a clean exit code is not enough —
    # these log lines each pin a class of defect that once shipped a
    # green-looking but broken run.
    foreach(bad
            "device lost"
            "without an open render pass"
            "not in the offline manifest"
            "FATAL")
        string(FIND "${log}" "${bad}" bad_pos)
        if(NOT bad_pos EQUAL -1)
            message(FATAL_ERROR "engine_demo exited 0 but logged '${bad}'")
        endif()
    endforeach()
    message(STATUS "test_macos_metal_consumer_smoke: engine_demo --frames 3 exit 0, logs clean")
    return()
endif()
# Window-service unavailability fails BEFORE "Platform initialized";
# anything after it (render init, shaders, pipelines) is a real failure.
string(FIND "${log}" "Platform initialized" plat_pos)
if(plat_pos EQUAL -1)
    smoke_skip("engine_demo never initialized a platform window")
endif()
message(FATAL_ERROR "engine_demo --frames 3 failed (rc=${rc}):\n${log}")
