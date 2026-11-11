foreach(var REAL_NM BINARY OUTPUT_FILE FILTER_SYMBOL)
    if(NOT DEFINED ${var} OR "${${var}}" STREQUAL "")
        message(FATAL_ERROR "${var} is required for the nm wrapper")
    endif()
endforeach()

execute_process(
    COMMAND "${REAL_NM}" --defined-only "${BINARY}"
    RESULT_VARIABLE nm_result
    OUTPUT_VARIABLE nm_output
    ERROR_VARIABLE nm_error
    TIMEOUT 20)
if(NOT nm_result EQUAL 0)
    message(FATAL_ERROR "real nm failed in the wrapper: ${nm_error}")
endif()
if(NOT nm_output MATCHES "${FILTER_SYMBOL}")
    message(FATAL_ERROR "wrapper fixture is missing ${FILTER_SYMBOL} before filtering")
endif()
if(NOT nm_output MATCHES "core_app_render_start")
    message(FATAL_ERROR "wrapper fixture is missing the control symbol core_app_render_start")
endif()

string(REPLACE "\n" ";" nm_lines "${nm_output}")
set(filtered_output "")
foreach(line IN LISTS nm_lines)
    if(NOT "${line}" MATCHES "${FILTER_SYMBOL}")
        string(APPEND filtered_output "${line}\n")
    endif()
endforeach()
file(WRITE "${OUTPUT_FILE}" "${filtered_output}")
