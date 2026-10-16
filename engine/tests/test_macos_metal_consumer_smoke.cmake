# Plan C Task 13: consumer smoke for the macOS Metal lane.
# Asserts dxx_break / engine_demo binaries exist and engine_demo can run
# --frames 3 to a clean exit on a real Mac. Exits 77 (ctest SKIP) when the
# lane is not APPLE+metal or no window service is available.
cmake_policy(SET CMP0054 NEW)
if(NOT DEFINED BUILD_DIR OR NOT DEFINED SOURCE_DIR OR NOT DEFINED METAL_LANE)
    message(FATAL_ERROR "BUILD_DIR, SOURCE_DIR and METAL_LANE are required")
endif()
if(NOT METAL_LANE)
    return()   # registered metal-only; nothing to do on other lanes
endif()

set(failures 0)
foreach(binary dxx_break engine_demo)
    if(NOT EXISTS "${BUILD_DIR}/${binary}")
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
    COMMAND "${BUILD_DIR}/engine_demo" --frames 3
    WORKING_DIRECTORY "${SOURCE_DIR}"
    TIMEOUT 180
    RESULT_VARIABLE rc
    OUTPUT_VARIABLE out
    ERROR_VARIABLE err
)
set(log "${out}\n${err}")
if(rc EQUAL 0)
    string(FIND "${log}" "device lost" lost_pos)
    if(NOT lost_pos EQUAL -1)
        message(FATAL_ERROR "engine_demo exited 0 but logged device lost")
    endif()
    message(STATUS "test_macos_metal_consumer_smoke: engine_demo --frames 3 exit 0")
    return()
endif()
if(rc EQUAL 77)
    return()   # app chose to skip (no window service)
endif()
# Window-service unavailability (SSH without a console session, headless CI)
# fails BEFORE "Platform initialized"; anything after it (render init,
# shaders, pipelines) is a real failure, never a skip.
string(FIND "${log}" "Platform initialized" plat_pos)
if(plat_pos EQUAL -1)
    message(STATUS "engine_demo never initialized a platform window -> SKIP")
    return()
endif()
message(FATAL_ERROR "engine_demo --frames 3 failed (rc=${rc}):\n${log}")
