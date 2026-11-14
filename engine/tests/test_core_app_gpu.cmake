# Real-device capture contract for the application's optional GPU lane.
#
# Runs the real executable on the requested backend with --require-device and
# asserts what the record lane cannot prove:
#   1. a real device existed (backend and device name in the trace),
#   2. a frame with draws was submitted and the device was shut down cleanly,
#   3. the captured PPM has the expected size and contains pixels that are not
#      the clear colour, i.e. geometry actually reached the target.
#
# A host without a display or device is reported as UNAVAILABLE (skipped), and
# a failure after a device existed is a hard failure, never a skip.

foreach(var CORE_APP BACKEND WORK SCENARIO ASSET_ROOT Python3_EXECUTABLE)
    if(NOT DEFINED ${var} OR "${${var}}" STREQUAL "")
        message(FATAL_ERROR "${var} is required")
    endif()
endforeach()

# BACKEND is the --render value. EXPECT_BACKEND is the backend the device must
# actually report; it differs only for the creation-time fallback case, where
# --render=auto runs with BREAK_RHI_FAIL_VULKAN=1 and must land on OpenGL.
if(NOT DEFINED EXPECT_BACKEND OR "${EXPECT_BACKEND}" STREQUAL "")
    set(EXPECT_BACKEND "${BACKEND}")
endif()
set(run_env "")
if(BACKEND STREQUAL "auto")
    if(DEFINED FAIL_VULKAN AND FAIL_VULKAN)
        list(APPEND run_env "BREAK_RHI_FAIL_VULKAN=1")
    endif()
else()
    # An explicit backend must never be satisfied by a fallback.
    list(APPEND run_env "BREAK_RHI_BACKEND=${BACKEND}" "BREAK_RHI_NO_FALLBACK=1")
endif()

file(REMOVE_RECURSE "${WORK}")
file(MAKE_DIRECTORY "${WORK}")

set(trace "${WORK}/gpu.trace")
set(shot "${WORK}/gpu.ppm")
file(WRITE "${SCENARIO}"
    "core-app-scenario 1\n"
    "seed 12648430\n"
    "fixed-dt-ns 16666667\n"
    "1 level\n"
    "60 screenshot\n"
    "65 quit\n")

execute_process(
    COMMAND "${CMAKE_COMMAND}" -E env ${run_env}
        "${CORE_APP}" --render=${BACKEND} --require-device --audio=null --fixed-step
        --assets "${ASSET_ROOT}"
        --scenario "${SCENARIO}" --screenshot "${shot}" --trace "${trace}"
    RESULT_VARIABLE run_rc
    OUTPUT_VARIABLE run_out
    ERROR_VARIABLE run_err
    TIMEOUT 300)
if(NOT run_rc EQUAL 0)
    # Exit 77 is the explicit environment-unavailable contract. A build whose
    # RHI was compiled without the requested backend can also fail while
    # creating the device; that path is only acceptable when the trace names
    # the failure as unavailable. Any failure after a device existed must fail
    # this test, so a trace with result=ready is never treated as a skip.
    if(run_rc EQUAL 77)
        message(STATUS "UNAVAILABLE backend=${BACKEND}: no display or device")
        return()
    endif()
    if(EXISTS "${trace}")
        file(READ "${trace}" early_trace)
        if(early_trace MATCHES "event=gpu result=unavailable backend=${BACKEND}" AND
           NOT early_trace MATCHES "event=gpu result=ready")
            message(STATUS "UNAVAILABLE backend=${BACKEND}: device could not be created")
            return()
        endif()
    endif()
    message(FATAL_ERROR "core_app ${BACKEND} exited ${run_rc}\n${run_out}\n${run_err}")
endif()

if(NOT EXISTS "${trace}")
    message(FATAL_ERROR "missing trace ${trace}")
endif()
file(READ "${trace}" trace_text)
if(NOT trace_text MATCHES "event=gpu result=ready backend=${EXPECT_BACKEND} device=[^\n]+")
    message(FATAL_ERROR "no real ${EXPECT_BACKEND} device was created for --render=${BACKEND}")
endif()
if(NOT trace_text MATCHES "event=gpu backend=${EXPECT_BACKEND} .*draws=[1-9][0-9]*")
    message(FATAL_ERROR "no frame with draws was rendered on ${EXPECT_BACKEND}")
endif()
# The fallback case must show the chain actually rejected Vulkan before it
# selected OpenGL; a device that was OpenGL from the start proves nothing.
if(BACKEND STREQUAL "auto" AND DEFINED FAIL_VULKAN AND FAIL_VULKAN)
    set(run_log "${run_out}${run_err}")
    if(NOT run_log MATCHES "RHIEVT [{]\"event\":\"fallback\",\"backend\":\"vulkan\"")
        message(FATAL_ERROR "no vulkan fallback event was emitted\n${run_log}")
    endif()
    if(NOT run_log MATCHES "RHIEVT [{]\"event\":\"backend_selected\",\"backend\":\"opengl\",\"reason\":\"config-fallback\"")
        message(FATAL_ERROR "opengl was not selected as the fallback\n${run_log}")
    endif()
endif()
if(NOT trace_text MATCHES "event=gpu result=stopped frames=[1-9][0-9]* screenshots=1")
    message(FATAL_ERROR "the device was not shut down after one capture on ${BACKEND}")
endif()

if(NOT EXISTS "${shot}")
    message(FATAL_ERROR "missing capture ${shot}")
endif()

# Pixel inspection: a P6 header parse, a size check, and a strided sample that
# must find at least one colour other than the clear colour.
set(pixel_check [=[
import sys
path, backend = sys.argv[1], sys.argv[2]
data = open(path, "rb").read()
index = 0
fields = []
while len(fields) < 4:
    while index < len(data) and data[index] in b" \t\r\n":
        index += 1
    start = index
    while index < len(data) and data[index] not in b" \t\r\n":
        index += 1
    fields.append(data[start:index])
if fields[0] != b"P6":
    raise SystemExit(backend + ": capture is not a P6 PPM")
width, height, maxval = int(fields[1]), int(fields[2]), int(fields[3])
if width <= 0 or height <= 0 or maxval != 255:
    raise SystemExit(backend + ": implausible PPM header")
index += 1
pixels = data[index:]
if len(pixels) != width * height * 3:
    raise SystemExit(backend + ": pixel payload is " + str(len(pixels)) +
                     " bytes, want " + str(width * height * 3))
colours = {}
step = 3 * 37
for offset in range(0, len(pixels) - 2, step):
    key = tuple(pixels[offset:offset + 3])
    colours[key] = colours.get(key, 0) + 1
background = max(colours.items(), key=lambda item: item[1])
drawn = sum(count for colour, count in colours.items() if colour != background[0])
if drawn == 0:
    raise SystemExit(backend + ": every sampled pixel equals the clear colour " +
                     str(background[0]))
print(backend + ": " + str(width) + "x" + str(height) + " distinct=" +
      str(len(colours)) + " background=" + str(background[0]) +
      " drawn_samples=" + str(drawn))
]=])
execute_process(
    COMMAND "${Python3_EXECUTABLE}" -c "${pixel_check}" "${shot}" "${BACKEND}"
    RESULT_VARIABLE pixel_rc
    OUTPUT_VARIABLE pixel_out
    ERROR_VARIABLE pixel_err)
if(NOT pixel_rc EQUAL 0)
    message(FATAL_ERROR "capture check failed for ${BACKEND}: ${pixel_out}${pixel_err}")
endif()
message(STATUS "verified ${pixel_out}")

# Both backends render the same scenario, so the drawn-pixel count is a
# cross-backend invariance the individual runs cannot check alone. The
# comparison is skipped when only one backend produced a capture.
if(DEFINED COMPARE_SHOT AND NOT "${COMPARE_SHOT}" STREQUAL "" AND EXISTS "${COMPARE_SHOT}")
    set(compare_check [=[
import sys
first, second = sys.argv[1], sys.argv[2]
def drawn(path):
    data = open(path, "rb").read()
    index = 0
    fields = []
    while len(fields) < 4:
        while data[index] in b" \t\r\n":
            index += 1
        start = index
        while data[index] not in b" \t\r\n":
            index += 1
        fields.append(data[start:index])
    index += 1
    pixels = data[index:]
    colours = {}
    step = 3 * 37
    for offset in range(0, len(pixels) - 2, step):
        key = tuple(pixels[offset:offset + 3])
        colours[key] = colours.get(key, 0) + 1
    background = max(colours.items(), key=lambda item: item[1])
    return sum(count for colour, count in colours.items() if colour != background[0])
a, b = drawn(first), drawn(second)
if a != b:
    raise SystemExit("cross-backend drawn samples differ: " + str(a) + " vs " + str(b))
print("cross-backend drawn samples match at " + str(a))
]=])
    execute_process(
        COMMAND "${Python3_EXECUTABLE}" -c "${compare_check}" "${shot}" "${COMPARE_SHOT}"
        RESULT_VARIABLE compare_rc
        OUTPUT_VARIABLE compare_out
        ERROR_VARIABLE compare_err)
    if(NOT compare_rc EQUAL 0)
        message(FATAL_ERROR "cross-backend comparison failed: ${compare_out}${compare_err}")
    endif()
    message(STATUS "${compare_out}")
endif()
