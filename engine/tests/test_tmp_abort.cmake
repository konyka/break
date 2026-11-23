if(NOT DEFINED PROBE OR NOT DEFINED MODE)
    message(FATAL_ERROR "PROBE and MODE are required")
endif()

string(REPEAT "x" 600 overflow_temp)
set(ENV{TEMP} "${overflow_temp}")
execute_process(
    COMMAND "${PROBE}" "${MODE}"
    RESULT_VARIABLE result
    OUTPUT_VARIABLE stdout
    ERROR_VARIABLE stderr
    TIMEOUT 30)
if("${result}" STREQUAL "0")
    message(FATAL_ERROR "${MODE} probe accepted a truncated path")
endif()
if(NOT "${stderr}" MATCHES "TEST PATH TRUNCATED")
    message(FATAL_ERROR "${MODE} probe failed without the truncation marker")
endif()
message(STATUS "${MODE} probe rejected the truncated path with the marker")
