#include "test_framework.h"

#include <core/trace_core_app.h>
#include <core/trace_merge.h>
#include <core/trace_schema.h>

#include <string.h>

#define TAIL "]," BREAK_TRACE_OTHER_DATA "}"

static char g_out[8192];

static const char k_profiler_doc[] =
    "{\"traceEvents\":[\n"
    "{\"name\":\"tick\",\"cat\":\"cpu\",\"ph\":\"X\",\"ts\":5,\"dur\":3,\"pid\":1,\"tid\":1,"
    "\"args\":{\"thread\":\"main\"}},\n"
    "{\"name\":\"thread_name\",\"ph\":\"M\",\"pid\":1,\"tid\":1,\"args\":{\"name\":\"main\"}}\n"
    TAIL "\n";

static const char k_core_app_doc[] =
    "{\"traceEvents\":[\r\n"
    "{\"name\":\"frame\",\"cat\":\"core_app\",\"ph\":\"i\",\"s\":\"g\",\"ts\":0,\"pid\":1,"
    "\"tid\":1,\"args\":{\"ts\":9,\"pid\":7}},\r\n"
    "{\"name\":\"a,\\\"pid\\\":3\",\"cat\":\"core_app\",\"ph\":\"i\",\"s\":\"g\",\"ts\":1,"
    "\"pid\":1,\"tid\":1,\"args\":{}}\r\n"
    TAIL "\r\n";

static BreakTraceMergeStatus merge(const BreakTraceMergeInput *inputs, u32 count,
                                   BreakTraceMergeReport *report)
{
    memset(g_out, 0x5a, sizeof g_out);
    return break_trace_merge(inputs, count, g_out, sizeof g_out, report);
}

TEST(trace_merge_assigns_pids_offsets_and_labels)
{
    BreakTraceMergeInput inputs[2] = {
        {k_profiler_doc, sizeof k_profiler_doc - 1u, 10u, 0u, "authority"},
        {k_core_app_doc, sizeof k_core_app_doc - 1u, 20u, 1000u, "user \"A\""},
    };
    BreakTraceMergeReport report;
    ASSERT_EQ(merge(inputs, 2u, &report), BREAK_TRACE_MERGE_OK);
    ASSERT_EQ(report.events, 4u);
    const char *want =
        "{\"traceEvents\":[\n"
        "{\"name\":\"process_name\",\"ph\":\"M\",\"pid\":10,\"args\":{\"name\":\"authority\"}},\n"
        "{\"name\":\"tick\",\"cat\":\"cpu\",\"ph\":\"X\",\"ts\":5,\"dur\":3,\"pid\":10,\"tid\":1,"
        "\"args\":{\"thread\":\"main\"}},\n"
        "{\"name\":\"thread_name\",\"ph\":\"M\",\"pid\":10,\"tid\":1,\"args\":{\"name\":\"main\"}},\n"
        "{\"name\":\"process_name\",\"ph\":\"M\",\"pid\":20,\"args\":{\"name\":\"user \\\"A\\\"\"}},\n"
        "{\"name\":\"frame\",\"cat\":\"core_app\",\"ph\":\"i\",\"s\":\"g\",\"ts\":1000,\"pid\":20,"
        "\"tid\":1,\"args\":{\"ts\":9,\"pid\":7}},\n"
        "{\"name\":\"a,\\\"pid\\\":3\",\"cat\":\"core_app\",\"ph\":\"i\",\"s\":\"g\",\"ts\":1001,"
        "\"pid\":20,\"tid\":1,\"args\":{}}\n"
        TAIL "\n";
    ASSERT_STR_EQ(g_out, want);
    ASSERT_EQ(report.bytes, (u64)strlen(want));

    BreakTraceMergeInput unlabeled = {k_profiler_doc, sizeof k_profiler_doc - 1u, 3u, 7u, NULL};
    ASSERT_EQ(merge(&unlabeled, 1u, &report), BREAK_TRACE_MERGE_OK);
    ASSERT_EQ(report.events, 2u);
    ASSERT_TRUE(strstr(g_out, "process_name") == NULL);
    ASSERT_TRUE(strstr(g_out, "\"ts\":12,\"dur\":3,\"pid\":3,") != NULL);
    ASSERT_TRUE(strstr(g_out, "\"ph\":\"M\",\"pid\":3,\"tid\":1") != NULL);

    ASSERT_EQ(merge(NULL, 0u, &report), BREAK_TRACE_MERGE_OK);
    ASSERT_STR_EQ(g_out, "{\"traceEvents\":[\n" TAIL "\n");
    ASSERT_EQ(report.events, 0u);
}

TEST(trace_merge_merges_empty_and_converted_documents)
{
    static char converted[2048];
    const char *text =
        "COREAPPTRACE version=1 event=runtime_running\n"
        "COREAPPTRACE version=1 event=level_loaded generation=1\n";
    BreakTraceCoreAppReport conv;
    ASSERT_EQ(break_trace_core_app_to_chrome(text, strlen(text), converted, sizeof converted,
                                             &conv),
              BREAK_TRACE_CONVERT_OK);
    char empty[256];
    BreakTraceCoreAppReport empty_report;
    ASSERT_EQ(break_trace_core_app_to_chrome("", 0u, empty, sizeof empty, &empty_report),
              BREAK_TRACE_CONVERT_OK);

    BreakTraceMergeInput inputs[3] = {
        {empty, (usize)empty_report.bytes, 1u, 0u, NULL},
        {converted, (usize)conv.bytes, 2u, 50u, "B"},
        {empty, (usize)empty_report.bytes, 3u, 0u, "C"},
    };
    BreakTraceMergeReport report;
    ASSERT_EQ(merge(inputs, 3u, &report), BREAK_TRACE_MERGE_OK);
    ASSERT_EQ(report.events, 2u);
    const char *want =
        "{\"traceEvents\":[\n"
        "{\"name\":\"process_name\",\"ph\":\"M\",\"pid\":2,\"args\":{\"name\":\"B\"}},\n"
        "{\"name\":\"runtime_running\",\"cat\":\"core_app\",\"ph\":\"i\",\"s\":\"g\",\"ts\":50,"
        "\"pid\":2,\"tid\":1,\"args\":{}},\n"
        "{\"name\":\"level_loaded\",\"cat\":\"core_app\",\"ph\":\"i\",\"s\":\"g\",\"ts\":51,"
        "\"pid\":2,\"tid\":1,\"args\":{\"generation\":1}},\n"
        "{\"name\":\"process_name\",\"ph\":\"M\",\"pid\":3,\"args\":{\"name\":\"C\"}}\n"
        TAIL "\n";
    ASSERT_STR_EQ(g_out, want);
}

static void expect_bad(const char *doc, u32 want_line)
{
    BreakTraceMergeInput inputs[2] = {
        {k_profiler_doc, sizeof k_profiler_doc - 1u, 1u, 0u, NULL},
        {doc, strlen(doc), 2u, 0u, NULL},
    };
    BreakTraceMergeReport report;
    ASSERT_EQ(merge(inputs, 2u, &report), BREAK_TRACE_MERGE_BAD_DOCUMENT);
    ASSERT_EQ(report.error_input, 1u);
    ASSERT_EQ(report.error_line, want_line);
}

#define EV(ts) "{\"name\":\"x\",\"ph\":\"i\",\"ts\":" ts ",\"pid\":1,\"tid\":1,\"args\":{}}"

TEST(trace_merge_rejects_bad_documents)
{
    expect_bad("{\"traceEvents\":[" EV("0") "\n" TAIL, 1u);
    expect_bad("[\n" EV("0") "\n" TAIL, 1u);
    expect_bad("{\"traceEvents\":[\n" EV("0") "\n", 3u);
    expect_bad("{\"traceEvents\":[\n" EV("0") "\n]}", 3u);
    expect_bad("{\"traceEvents\":[\n" EV("0") "\n" TAIL "x", 3u);
    expect_bad("{\"traceEvents\":[\n" EV("0") ",\n" TAIL "\n\n", 4u);
    expect_bad("{\"traceEvents\":[\n" EV("0") ",\nnot an object\n" TAIL, 3u);
    expect_bad("{\"traceEvents\":[\n{\"name\":\"x\",\"ph\":\"i\",\"ts\":0,\"tid\":1}\n" TAIL, 2u);
    expect_bad("{\"traceEvents\":[\n{\"name\":\"x\",\"pid\":,\"tid\":1}\n" TAIL, 2u);
    expect_bad("{\"traceEvents\":[\n" EV("-1") "\n" TAIL, 2u);
    expect_bad("{\"traceEvents\":[\n[\"name\":\"x\",\"pid\":1}\n" TAIL, 2u);
    expect_bad("{\"traceEvents\":[\n{\"name\":\"x\",\"pid\":1]\n" TAIL, 2u);
    expect_bad("{\"traceEvents\":[\n{\"name\":\"x\",\"args\":{\"a\":1,\"pid\":2}}\n" TAIL, 2u);
}

TEST(trace_merge_ts_offset_overflow_and_invalid_inputs)
{
    const char doc[] = "{\"traceEvents\":[\n" EV("9223372036854775806") "\n" TAIL;
    BreakTraceMergeInput input = {doc, sizeof doc - 1u, 1u, 1u, NULL};
    BreakTraceMergeReport report;
    ASSERT_EQ(merge(&input, 1u, &report), BREAK_TRACE_MERGE_OK);
    ASSERT_TRUE(strstr(g_out, "\"ts\":9223372036854775807,") != NULL);
    input.ts_offset_us = 2u;
    ASSERT_EQ(merge(&input, 1u, &report), BREAK_TRACE_MERGE_BAD_DOCUMENT);
    ASSERT_EQ(report.error_input, 0u);
    ASSERT_EQ(report.error_line, 2u);

    const char huge[] = "{\"traceEvents\":[\n" EV("99999999999999999999") "\n" TAIL;
    BreakTraceMergeInput big = {huge, sizeof huge - 1u, 1u, 0u, NULL};
    ASSERT_EQ(merge(&big, 1u, &report), BREAK_TRACE_MERGE_BAD_DOCUMENT);
    const char above[] = "{\"traceEvents\":[\n" EV("9223372036854775808") "\n" TAIL;
    BreakTraceMergeInput above_input = {above, sizeof above - 1u, 1u, 0u, NULL};
    ASSERT_EQ(merge(&above_input, 1u, &report), BREAK_TRACE_MERGE_BAD_DOCUMENT);

    const char args_ts[] =
        "{\"traceEvents\":[\n"
        "{\"name\":\"m\",\"ph\":\"M\",\"pid\":1,\"tid\":1,\"args\":{\"ts\":4}}\n" TAIL;
    BreakTraceMergeInput args_input = {args_ts, sizeof args_ts - 1u, 6u, 100u, NULL};
    ASSERT_EQ(merge(&args_input, 1u, &report), BREAK_TRACE_MERGE_OK);
    ASSERT_TRUE(strstr(g_out, "\"pid\":6,\"tid\":1,\"args\":{\"ts\":4}}") != NULL);

    BreakTraceMergeInput pair[2] = {
        {k_profiler_doc, sizeof k_profiler_doc - 1u, 4u, 0u, NULL},
        {k_profiler_doc, sizeof k_profiler_doc - 1u, 4u, 0u, NULL},
    };
    ASSERT_EQ(merge(pair, 2u, &report), BREAK_TRACE_MERGE_INVALID);
    pair[1].pid = 0u;
    ASSERT_EQ(merge(pair, 2u, &report), BREAK_TRACE_MERGE_INVALID);
    pair[1].pid = 5u;
    pair[1].text = NULL;
    ASSERT_EQ(merge(pair, 2u, &report), BREAK_TRACE_MERGE_INVALID);
    pair[1].text = k_profiler_doc;
    ASSERT_EQ(merge(NULL, 1u, &report), BREAK_TRACE_MERGE_INVALID);
    ASSERT_EQ(merge(pair, 2u, NULL), BREAK_TRACE_MERGE_INVALID);
    ASSERT_EQ(merge(pair, 2u, &report), BREAK_TRACE_MERGE_OK);
}

TEST(trace_merge_size_query_and_small_buffer)
{
    BreakTraceMergeInput input = {k_profiler_doc, sizeof k_profiler_doc - 1u, 2u, 0u, "A"};
    BreakTraceMergeReport report;
    ASSERT_EQ(break_trace_merge(&input, 1u, NULL, 0u, &report), BREAK_TRACE_MERGE_TOO_SMALL);
    u64 need = report.bytes;
    ASSERT_TRUE(need > 0u && need < sizeof g_out);
    memset(g_out, 0x5a, sizeof g_out);
    ASSERT_EQ(break_trace_merge(&input, 1u, g_out, (usize)need, &report),
              BREAK_TRACE_MERGE_TOO_SMALL);
    ASSERT_EQ((unsigned char)g_out[need], 0x5au);
    memset(g_out, 0x5a, sizeof g_out);
    ASSERT_EQ(break_trace_merge(&input, 1u, g_out, (usize)need + 1u, &report),
              BREAK_TRACE_MERGE_OK);
    ASSERT_EQ(g_out[need], '\0');
    ASSERT_EQ((unsigned char)g_out[need + 1u], 0x5au);
    ASSERT_EQ(break_trace_merge(&input, 1u, NULL, 4u, &report), BREAK_TRACE_MERGE_INVALID);
}

TEST_MAIN_BEGIN()
    RUN_TEST(trace_merge_assigns_pids_offsets_and_labels);
    RUN_TEST(trace_merge_merges_empty_and_converted_documents);
    RUN_TEST(trace_merge_rejects_bad_documents);
    RUN_TEST(trace_merge_ts_offset_overflow_and_invalid_inputs);
    RUN_TEST(trace_merge_size_query_and_small_buffer);
TEST_MAIN_END()
