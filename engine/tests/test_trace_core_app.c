#include "test_framework.h"

#include <core/trace_core_app.h>
#include <core/trace_schema.h>

#include <stdio.h>
#include <string.h>

static char g_out[4096];

#define EVENT_HEAD(name, ts) \
    "{\"name\":\"" name "\",\"cat\":\"core_app\",\"ph\":\"i\",\"s\":\"g\",\"ts\":" ts \
    ",\"pid\":1,\"tid\":1,\"args\":{"

static BreakTraceConvertStatus convert(const char *text, BreakTraceCoreAppReport *report)
{
    memset(g_out, 0x5a, sizeof g_out);
    return break_trace_core_app_to_chrome(text, strlen(text), g_out, sizeof g_out, report);
}

TEST(core_app_trace_converts_lines_to_chrome_events)
{
    const char *text =
        "COREAPPTRACE version=1 event=level_loaded generation=1\r\n"
        "\n"
        "  \t\r\n"
        "garbage line\n"
        "COREAPPTRACE version=1 event=audio kind=listener  sequence=0 id=007 q=a\"b\\c\x01\x1f t=1:2 "
        "big=1234567890123456789\n"
        "COREAPPTRACE version=1 event=runtime_stopped";
    BreakTraceCoreAppReport report;
    ASSERT_EQ(convert(text, &report), BREAK_TRACE_CONVERT_OK);
    ASSERT_EQ(report.events, 3u);
    ASSERT_EQ(report.skipped, 1u);
    const char *want =
        "{\"traceEvents\":[\n" EVENT_HEAD("level_loaded", "0") "\"generation\":1}},\n"
        EVENT_HEAD("audio", "1")
        "\"kind\":\"listener\",\"sequence\":0,\"id\":\"007\",\"q\":\"a\\\"b\\\\c\\u0001\\u001f\",\"t\":\"1:2\","
        "\"big\":\"1234567890123456789\"}},\n"
        EVENT_HEAD("runtime_stopped", "2") "}}\n"
        "]," BREAK_TRACE_OTHER_DATA "}\n";
    ASSERT_STR_EQ(g_out, want);
    ASSERT_EQ(report.bytes, (u64)strlen(want));
}

TEST(core_app_trace_size_query_and_small_buffer)
{
    const char *text = "COREAPPTRACE version=1 event=frame frame=3 generation=1\n";
    BreakTraceCoreAppReport report;
    ASSERT_EQ(break_trace_core_app_to_chrome(text, strlen(text), NULL, 0u, &report),
              BREAK_TRACE_CONVERT_TOO_SMALL);
    ASSERT_EQ(report.events, 1u);
    u64 need = report.bytes;
    ASSERT_TRUE(need > 0u && need < sizeof g_out);

    memset(g_out, 0x5a, sizeof g_out);
    ASSERT_EQ(break_trace_core_app_to_chrome(text, strlen(text), g_out, (usize)need, &report),
              BREAK_TRACE_CONVERT_TOO_SMALL);
    ASSERT_EQ((unsigned char)g_out[need], 0x5au);

    memset(g_out, 0x5a, sizeof g_out);
    ASSERT_EQ(break_trace_core_app_to_chrome(text, strlen(text), g_out, (usize)need + 1u,
                                             &report),
              BREAK_TRACE_CONVERT_OK);
    ASSERT_EQ(g_out[need], '\0');
    ASSERT_EQ((unsigned char)g_out[need + 1u], 0x5au);
    ASSERT_EQ(report.bytes, need);

    ASSERT_EQ(convert("", &report), BREAK_TRACE_CONVERT_OK);
    ASSERT_STR_EQ(g_out, "{\"traceEvents\":[\n]," BREAK_TRACE_OTHER_DATA "}\n");
    ASSERT_EQ(report.events, 0u);
    ASSERT_EQ(report.skipped, 0u);

    ASSERT_EQ(break_trace_core_app_to_chrome(NULL, 1u, g_out, sizeof g_out, &report),
              BREAK_TRACE_CONVERT_INVALID);
    ASSERT_EQ(break_trace_core_app_to_chrome(text, strlen(text), g_out, sizeof g_out, NULL),
              BREAK_TRACE_CONVERT_INVALID);
    ASSERT_EQ(break_trace_core_app_to_chrome(NULL, 0u, g_out, sizeof g_out, &report),
              BREAK_TRACE_CONVERT_OK);
}

static void expect_skipped(const char *line)
{
    BreakTraceCoreAppReport report;
    ASSERT_EQ(convert(line, &report), BREAK_TRACE_CONVERT_OK);
    ASSERT_EQ(report.events, 0u);
    ASSERT_EQ(report.skipped, 1u);
}

TEST(core_app_trace_skips_malformed_lines)
{
    expect_skipped("COREAPPTRACEversion=1 event=a");
    expect_skipped("XCOREAPPTRACE version=1 event=a");
    expect_skipped("COREAPPTRACE version=2 event=a");
    expect_skipped("COREAPPTRACE version=10 event=a");
    expect_skipped("COREAPPTRACE event=a");
    expect_skipped("COREAPPTRACE version=1 kind=a");
    expect_skipped("COREAPPTRACE version=1 event= kind=a");
    expect_skipped("COREAPPTRACE version=1 event=a kind");
    expect_skipped("COREAPPTRACE version=1 event=a =b");
    expect_skipped("COREAPPTRACE version=1 event=a k=1 k=2");
    expect_skipped("COREAPPTRACE version=1 event=a event=b");
    expect_skipped("COREAPPTRACE version=1 version=1 event=a");

    char wide[1024];
    usize used = (usize)snprintf(wide, sizeof wide, "COREAPPTRACE version=1 event=a");
    for (u32 i = 0u; i < BREAK_TRACE_CORE_APP_MAX_FIELDS; ++i) {
        used += (usize)snprintf(wide + used, sizeof wide - used, " k%u=%u", i, i);
    }
    expect_skipped(wide);

    BreakTraceCoreAppReport report;
    used = (usize)snprintf(wide, sizeof wide, "COREAPPTRACE version=1 event=a");
    for (u32 i = 0u; i + 2u < BREAK_TRACE_CORE_APP_MAX_FIELDS; ++i) {
        used += (usize)snprintf(wide + used, sizeof wide - used, " k%u=%u", i, i);
    }
    ASSERT_EQ(convert(wide, &report), BREAK_TRACE_CONVERT_OK);
    ASSERT_EQ(report.events, 1u);
    ASSERT_TRUE(strstr(g_out, "\"k29\":29}}") != NULL);

    ASSERT_EQ(convert("COREAPPTRACE version=1 event=a v=0 w=-1 x=01 y=1a z=", &report),
              BREAK_TRACE_CONVERT_OK);
    ASSERT_EQ(report.events, 1u);
    ASSERT_TRUE(strstr(g_out, "\"v\":0,\"w\":\"-1\",\"x\":\"01\",\"y\":\"1a\",\"z\":\"\"}}") !=
                NULL);
}

TEST_MAIN_BEGIN()
    RUN_TEST(core_app_trace_converts_lines_to_chrome_events);
    RUN_TEST(core_app_trace_size_query_and_small_buffer);
    RUN_TEST(core_app_trace_skips_malformed_lines);
TEST_MAIN_END()
