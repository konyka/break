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

# --clock-offset: input 1 is the server, input 2 the peer; offset_us is
# peer minus server, so a negative offset shifts the peer forward.
set(clk "COREAPPTRACE version=1 ts_us=9 event=network_clock_offset session=1")
file(WRITE "${WORK}/behind.trace"
    "COREAPPTRACE version=1 ts_us=1 event=level_loaded generation=1\n"
    "${clk} offset_us=-1000 error_us=12 samples=4\n")
file(WRITE "${WORK}/ahead.trace" "${clk} offset_us=40 error_us=3 samples=4\n")
file(WRITE "${WORK}/none.trace" "COREAPPTRACE version=1 event=level_loaded generation=1\n")
file(WRITE "${WORK}/two.trace"
    "${clk} offset_us=1 error_us=1 samples=4\n${clk} offset_us=2 error_us=1 samples=4\n")
file(WRITE "${WORK}/malformed.trace" "${clk} offset_us=01 error_us=1 samples=4\n")

execute_process(COMMAND "${TRACE_MERGE}" --out "${WORK}/behind.json"
    --clock-offset "${WORK}/behind.trace" "${WORK}/a.json" "${WORK}/b.json"
    RESULT_VARIABLE behind_rc OUTPUT_VARIABLE behind_out ERROR_VARIABLE behind_err TIMEOUT 20)
if(NOT behind_rc EQUAL 0 OR NOT behind_out MATCHES "clock offset offset_us=-1000 error_us=12")
    record_error("clock_behind: exit=${behind_rc}; stdout=${behind_out}; stderr=${behind_err}")
else()
    file(READ "${WORK}/behind.json" behind)
    if(NOT behind MATCHES "\"ts\":5,\"dur\":3,\"pid\":1," OR
       NOT behind MATCHES "\"ts\":1000,\"pid\":2,")
        record_error("clock_behind: the peer must move forward by 1000 us:\n${behind}")
    endif()
endif()
run_tool(clock_ahead 0 --out "${WORK}/ahead.json"
    --clock-offset "${WORK}/ahead.trace" "${WORK}/a.json" "${WORK}/b.json")
set(ahead "")
if(EXISTS "${WORK}/ahead.json")
    file(READ "${WORK}/ahead.json" ahead)
endif()
if(NOT ahead MATCHES "\"ts\":45,\"dur\":3,\"pid\":1," OR NOT ahead MATCHES "\"ts\":0,\"pid\":2,")
    record_error("clock_ahead: the server must move forward by 40 us:\n${ahead}")
endif()
run_tool(clock_one_input 2 --out "${WORK}/never.json"
    --clock-offset "${WORK}/ahead.trace" "${WORK}/a.json")
expect_err(clock_one_input "--clock-offset needs exactly two inputs")
run_tool(clock_three_inputs 2 --out "${WORK}/never.json"
    --clock-offset "${WORK}/ahead.trace" "${WORK}/a.json" "${WORK}/b.json" "${WORK}/a.json")
expect_err(clock_three_inputs "--clock-offset needs exactly two inputs")
run_tool(clock_with_offset 2 --out "${WORK}/never.json"
    --clock-offset "${WORK}/ahead.trace" --offset-us 5 "${WORK}/a.json" "${WORK}/b.json")
expect_err(clock_with_offset "--clock-offset cannot be combined with --offset-us")
run_tool(clock_twice 2 --out "${WORK}/never.json" --clock-offset "${WORK}/ahead.trace"
    --clock-offset "${WORK}/ahead.trace" "${WORK}/a.json" "${WORK}/b.json")
expect_err(clock_twice "--clock-offset given twice")
run_tool(clock_missing 1 --out "${WORK}/never.json"
    --clock-offset "${WORK}/nope.trace" "${WORK}/a.json" "${WORK}/b.json")
expect_err(clock_missing "cannot read .*nope.trace")
run_tool(clock_none 1 --out "${WORK}/never.json"
    --clock-offset "${WORK}/none.trace" "${WORK}/a.json" "${WORK}/b.json")
expect_err(clock_none "no network_clock_offset line in .*none.trace")
run_tool(clock_two 1 --out "${WORK}/never.json"
    --clock-offset "${WORK}/two.trace" "${WORK}/a.json" "${WORK}/b.json")
expect_err(clock_two "several network_clock_offset lines in .*two.trace")
run_tool(clock_malformed 1 --out "${WORK}/never.json"
    --clock-offset "${WORK}/malformed.trace" "${WORK}/a.json" "${WORK}/b.json")
expect_err(clock_malformed "malformed network_clock_offset line in .*malformed.trace")

# Several peers: --session N names the session of the next input, each
# peer's line is picked from the server trace. offset 300 for session 2
# puts the server 300 us ahead; session 1 (offset -500) moves by 800.
file(WRITE "${WORK}/c.json"
    "{\"traceEvents\":[\n"
    "{\"name\":\"frame\",\"cat\":\"core_app\",\"ph\":\"i\",\"s\":\"g\",\"ts\":2,\"pid\":1,\"tid\":1,\"args\":{}}\n"
    "${tail}")
set(clk1 "COREAPPTRACE version=1 ts_us=9 event=network_clock_offset")
file(WRITE "${WORK}/peers.trace"
    "${clk1} session=1 offset_us=-500 error_us=4 samples=4\n"
    "${clk1} session=2 offset_us=300 error_us=6 samples=4\n"
    "${clk1} session=3 offset_us=x error_us=1 samples=4\n")
execute_process(COMMAND "${TRACE_MERGE}" --out "${WORK}/peers.json"
    --clock-offset "${WORK}/peers.trace" "${WORK}/a.json"
    --session 1 "${WORK}/b.json" --session 2 "${WORK}/c.json"
    RESULT_VARIABLE peers_rc OUTPUT_VARIABLE peers_out ERROR_VARIABLE peers_err TIMEOUT 20)
if(NOT peers_rc EQUAL 0 OR
   NOT peers_out MATCHES "session=1 offset_us=-500 error_us=4" OR
   NOT peers_out MATCHES "session=2 offset_us=300 error_us=6")
    record_error("clock_peers: exit=${peers_rc}; stdout=${peers_out}; stderr=${peers_err}")
else()
    file(READ "${WORK}/peers.json" peers)
    if(NOT peers MATCHES "\"ts\":305,\"dur\":3,\"pid\":1," OR
       NOT peers MATCHES "\"ts\":800,\"pid\":2," OR
       NOT peers MATCHES "\"ts\":2,\"pid\":3,")
        record_error("clock_peers: every input must land on one timeline:\n${peers}")
    endif()
endif()
# --session also works for a single peer next to other sessions' lines
run_tool(clock_one_session 0 --out "${WORK}/one_session.json"
    --clock-offset "${WORK}/peers.trace" "${WORK}/a.json" --session 2 "${WORK}/c.json")
run_tool(session_no_clock 2 --out "${WORK}/never.json" "${WORK}/a.json"
    --session 1 "${WORK}/b.json")
expect_err(session_no_clock "--session needs --clock-offset")
run_tool(session_on_server 2 --out "${WORK}/never.json" --clock-offset "${WORK}/peers.trace"
    --session 1 "${WORK}/a.json" --session 2 "${WORK}/b.json")
expect_err(session_on_server "the first input is the server and takes no --session")
run_tool(session_partial 2 --out "${WORK}/never.json" --clock-offset "${WORK}/peers.trace"
    "${WORK}/a.json" --session 1 "${WORK}/b.json" "${WORK}/c.json")
expect_err(session_partial "every peer input needs --session")
run_tool(session_bad 2 --out "${WORK}/never.json" --clock-offset "${WORK}/peers.trace"
    "${WORK}/a.json" --session 01 "${WORK}/b.json")
expect_err(session_bad "--session requires a nonnegative integer")
run_tool(session_dangling 2 --out "${WORK}/never.json" --clock-offset "${WORK}/peers.trace"
    "${WORK}/a.json" "${WORK}/b.json" --session 1)
expect_err(session_dangling "must precede an input")
run_tool(session_absent 1 --out "${WORK}/never.json" --clock-offset "${WORK}/peers.trace"
    "${WORK}/a.json" --session 7 "${WORK}/b.json")
expect_err(session_absent "no network_clock_offset line for session 7 in .*peers.trace")
run_tool(session_malformed 1 --out "${WORK}/never.json" --clock-offset "${WORK}/peers.trace"
    "${WORK}/a.json" --session 3 "${WORK}/b.json")
expect_err(session_malformed "malformed network_clock_offset line for session 3 in .*peers.trace")
file(WRITE "${WORK}/peers_twice.trace"
    "${clk1} session=1 offset_us=1 error_us=1\n${clk1} session=1 offset_us=2 error_us=1\n")
run_tool(session_twice 1 --out "${WORK}/never.json" --clock-offset "${WORK}/peers_twice.trace"
    "${WORK}/a.json" --session 1 "${WORK}/b.json")
expect_err(session_twice "several network_clock_offset lines for session 1 in .*peers_twice.trace")

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
expect_err(dangling_label "--label/--offset-us/--session must precede an input")
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
