foreach(var TRACE_MERGE WORK)
    if(NOT DEFINED ${var})
        message(FATAL_ERROR "${var} is required")
    endif()
endforeach()

set_property(GLOBAL PROPERTY TRACE_MERGE_TOOL_ERRORS "")
function(record_error text)
    get_property(errors GLOBAL PROPERTY TRACE_MERGE_TOOL_ERRORS)
    string(APPEND errors "${text}\n")
    set_property(GLOBAL PROPERTY TRACE_MERGE_TOOL_ERRORS "${errors}")
endfunction()

function(run_tool name expected_rc)
    execute_process(COMMAND "${TRACE_MERGE}" ${ARGN}
        RESULT_VARIABLE rc OUTPUT_VARIABLE out ERROR_VARIABLE err TIMEOUT 20)
    set(TOOL_ERR "${err}" PARENT_SCOPE)
    if(NOT "${rc}" STREQUAL "${expected_rc}")
        record_error("${name}: exit=${rc}, want=${expected_rc}; stdout=${out}; stderr=${err}")
    endif()
endfunction()

function(expect_err name pattern)
    if(NOT "${TOOL_ERR}" MATCHES "${pattern}")
        record_error("${name}: stderr did not match '${pattern}': ${TOOL_ERR}")
    endif()
endfunction()

file(REMOVE_RECURSE "${WORK}")
file(MAKE_DIRECTORY "${WORK}")
set(tail "],\"otherData\":{\"schema\":\"break.trace\",\"schema_version\":1}}\n")
file(WRITE "${WORK}/a.json"
    "{\"traceEvents\":[\n"
    "{\"name\":\"tick\",\"cat\":\"cpu\",\"ph\":\"X\",\"ts\":5,\"dur\":3,\"pid\":1,\"tid\":1,\"args\":{}}\n"
    "${tail}")
file(WRITE "${WORK}/b.json"
    "{\"traceEvents\":[\n"
    "{\"name\":\"frame\",\"cat\":\"core_app\",\"ph\":\"i\",\"s\":\"g\",\"ts\":0,\"pid\":1,\"tid\":1,\"args\":{}}\n"
    "${tail}")
file(WRITE "${WORK}/bad.json" "{\"traceEvents\":[\nnot an object\n${tail}")

run_tool(merge 0 --out "${WORK}/merged.json"
    --label authority "${WORK}/a.json" --offset-us 1000 --label "user A" "${WORK}/b.json")
if(NOT EXISTS "${WORK}/merged.json")
    record_error("merge: output was not written")
else()
    file(READ "${WORK}/merged.json" merged)
    string(CONCAT want
        "{\"traceEvents\":[\n"
        "{\"name\":\"process_name\",\"ph\":\"M\",\"pid\":1,\"args\":{\"name\":\"authority\"}},\n"
        "{\"name\":\"tick\",\"cat\":\"cpu\",\"ph\":\"X\",\"ts\":5,\"dur\":3,\"pid\":1,\"tid\":1,\"args\":{}},\n"
        "{\"name\":\"process_name\",\"ph\":\"M\",\"pid\":2,\"args\":{\"name\":\"user A\"}},\n"
        "{\"name\":\"frame\",\"cat\":\"core_app\",\"ph\":\"i\",\"s\":\"g\",\"ts\":1000,\"pid\":2,\"tid\":1,\"args\":{}}\n"
        "${tail}")
    if(NOT merged STREQUAL want)
        record_error("merge: unexpected output:\n${merged}")
    endif()
endif()

run_tool(options_reset 0 --out "${WORK}/reset.json"
    --offset-us 7 --label only "${WORK}/a.json" "${WORK}/b.json")
file(READ "${WORK}/reset.json" reset)
string(REGEX MATCHALL "process_name" reset_labels "${reset}")
list(LENGTH reset_labels reset_label_count)
if(NOT reset MATCHES "\"ts\":12,\"dur\":3,\"pid\":1," OR NOT reset MATCHES "\"ts\":0,\"pid\":2,"
   OR NOT reset_label_count EQUAL 1)
    record_error("options_reset: --offset-us must apply to the next input only:\n${reset}")
endif()

run_tool(bad_document 1 --out "${WORK}/never.json" "${WORK}/a.json" "${WORK}/bad.json")
expect_err(bad_document "input 2 .*bad.json.* line 2")
if(EXISTS "${WORK}/never.json")
    record_error("bad_document: output was written for a rejected merge")
endif()
run_tool(missing_input 1 --out "${WORK}/never.json" "${WORK}/missing.json")
expect_err(missing_input "cannot read .*missing.json")
run_tool(no_out 2 "${WORK}/a.json")
expect_err(no_out "--out is required")
run_tool(no_inputs 2 --out "${WORK}/never.json")
expect_err(no_inputs "at least one input")
run_tool(dangling_label 2 --out "${WORK}/never.json" "${WORK}/a.json" --label x)
expect_err(dangling_label "--label/--offset-us must precede an input")
run_tool(bad_offset 2 --out "${WORK}/never.json" --offset-us 1x "${WORK}/a.json")
expect_err(bad_offset "--offset-us requires a nonnegative integer")
run_tool(bad_offset_sign 2 --out "${WORK}/never.json" --offset-us -1 "${WORK}/a.json")
expect_err(bad_offset_sign "--offset-us requires a nonnegative integer")
run_tool(missing_value 2 --out)
expect_err(missing_value "--out requires a value")
# execute_process drops empty arguments; pass an empty --out through sh.
if(CMAKE_HOST_UNIX)
    execute_process(COMMAND /bin/sh -c "\"$0\" --out '' \"$1\"" "${TRACE_MERGE}" "${WORK}/a.json"
        RESULT_VARIABLE empty_rc ERROR_VARIABLE empty_err TIMEOUT 20)
    if(NOT empty_rc EQUAL 2 OR NOT empty_err MATCHES "--out requires a value")
        record_error("empty_value: exit=${empty_rc}, want 2; stderr=${empty_err}")
    endif()
endif()
run_tool(unknown_option 2 --out "${WORK}/never.json" --bogus "${WORK}/a.json")
expect_err(unknown_option "unknown or malformed argument")
run_tool(unwritable 1 --out "${WORK}/no_dir/x.json" "${WORK}/a.json")
expect_err(unwritable "cannot write")
run_tool(help 0 --help)

get_property(errors GLOBAL PROPERTY TRACE_MERGE_TOOL_ERRORS)
if(NOT errors STREQUAL "")
    message(FATAL_ERROR "trace_merge tool contract failed:\n${errors}")
endif()
message(STATUS "trace_merge tool contract passed")
