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

TEST(core_app_trace_uses_ts_us_as_the_event_time)
{
    const char *text =
        "COREAPPTRACE version=1 event=a ts_us=1500 generation=1\n"
        "COREAPPTRACE version=1 ts_us=0 event=b\n"
        "COREAPPTRACE version=1 event=c k=v\n"
        "COREAPPTRACE version=1 event=d ts_us=999999999999999999\n";
    BreakTraceCoreAppReport report;
    ASSERT_EQ(convert(text, &report), BREAK_TRACE_CONVERT_OK);
    ASSERT_EQ(report.events, 4u);
    ASSERT_EQ(report.skipped, 0u);
    ASSERT_EQ(report.timestamped, 3u);
    const char *want =
        "{\"traceEvents\":[\n" EVENT_HEAD("a", "1500") "\"generation\":1}},\n"
        EVENT_HEAD("b", "0") "}},\n"
        EVENT_HEAD("c", "2") "\"k\":\"v\"}},\n"
        EVENT_HEAD("d", "999999999999999999") "}}\n"
        "]," BREAK_TRACE_OTHER_DATA "}\n";
    ASSERT_STR_EQ(g_out, want);
    ASSERT_EQ(report.bytes, (u64)strlen(want));

    ASSERT_EQ(convert("COREAPPTRACE version=1 event=a\n", &report), BREAK_TRACE_CONVERT_OK);
    ASSERT_EQ(report.timestamped, 0u);
}

TEST(core_app_trace_skips_a_non_canonical_ts_us)
{
    expect_skipped("COREAPPTRACE version=1 event=a ts_us=01");
    expect_skipped("COREAPPTRACE version=1 event=a ts_us=-1");
    expect_skipped("COREAPPTRACE version=1 event=a ts_us=1a");
    expect_skipped("COREAPPTRACE version=1 event=a ts_us=");
    expect_skipped("COREAPPTRACE version=1 event=a ts_us=1000000000000000000");
    BreakTraceCoreAppReport report;
    ASSERT_EQ(convert("COREAPPTRACE version=1 event=a ts_us=x\n"
                      "COREAPPTRACE version=1 event=b ts_us=7\n",
                      &report),
              BREAK_TRACE_CONVERT_OK);
    ASSERT_EQ(report.events, 1u);
    ASSERT_EQ(report.skipped, 1u);
    ASSERT_EQ(report.timestamped, 1u);
    ASSERT_TRUE(strstr(g_out, EVENT_HEAD("b", "7") "}}") != NULL);
}

static u64 g_fake_now;
static u64 fake_clock(void)
{
    return g_fake_now;
}

/* Runs the writer into a temporary file and returns what it wrote. */
static const char *written(const char *text, bool formatted)
{
    static char buf[8192];
    FILE *f = tmpfile();
    if (!f) return "<no tmpfile>";
    int n = formatted ? break_trace_core_app_fprintf(f, "%s", text)
                      : break_trace_core_app_write(f, text);
    rewind(f);
    usize got = fread(buf, 1u, sizeof buf - 1u, f);
    buf[got] = '\0';
    fclose(f);
    if (n < 0 || (usize)n != got) return "<bad return>";
    return buf;
}

TEST(core_app_trace_writer_stamps_lines_only_when_a_clock_is_set)
{
    break_trace_core_app_set_clock(NULL);
    ASSERT_STR_EQ(written("COREAPPTRACE version=1 event=a k=1\n", true),
                  "COREAPPTRACE version=1 event=a k=1\n");
    g_fake_now = 1234567u;
    break_trace_core_app_set_clock(fake_clock);
    ASSERT_STR_EQ(written("COREAPPTRACE version=1 event=a k=1\n", true),
                  "COREAPPTRACE version=1 ts_us=1234567 event=a k=1\n");
    ASSERT_STR_EQ(written("COREAPPTRACE version=1 event=b\n", false),
                  "COREAPPTRACE version=1 ts_us=1234567 event=b\n");
    g_fake_now = 0u;
    ASSERT_STR_EQ(written("COREAPPTRACE version=1 event=c\n", true),
                  "COREAPPTRACE version=1 ts_us=0 event=c\n");
    /* continuation chunks and other text are written verbatim */
    ASSERT_STR_EQ(written("1,2,3", true), "1,2,3");
    ASSERT_STR_EQ(written(" sun_y=1\n", false), " sun_y=1\n");
    ASSERT_STR_EQ(written("COREAPPTRACE version=2 event=a\n", true),
                  "COREAPPTRACE version=2 event=a\n");
    ASSERT_STR_EQ(written("", true), "");
    break_trace_core_app_set_clock(NULL);
    ASSERT_STR_EQ(written("COREAPPTRACE version=1 event=d\n", false),
                  "COREAPPTRACE version=1 event=d\n");
    ASSERT_EQ(break_trace_core_app_fprintf(NULL, "x"), -1);
    ASSERT_EQ(break_trace_core_app_write(NULL, "x"), -1);
}

TEST(core_app_trace_writer_handles_long_lines_and_round_trips)
{
    static char line[3000];
    static char want[3100];
    usize used = (usize)snprintf(line, sizeof line, "COREAPPTRACE version=1 event=wide objects=");
    while (used + 3u < sizeof line - 2u) used += (usize)snprintf(line + used, sizeof line - used, "%u,", 7u);
    snprintf(line + used, sizeof line - used, "\n");
    g_fake_now = 999999999999999999u;
    break_trace_core_app_set_clock(fake_clock);
    snprintf(want, sizeof want, "COREAPPTRACE version=1 ts_us=999999999999999999 %s",
             line + strlen("COREAPPTRACE version=1 "));
    ASSERT_STR_EQ(written(line, true), want);
    ASSERT_STR_EQ(written(line, false), want);

    g_fake_now = 42u;
    const char *a = written("COREAPPTRACE version=1 event=a generation=1\n", true);
    static char text[256];
    snprintf(text, sizeof text, "%s", a);
    g_fake_now = 43u;
    usize n = strlen(text);
    snprintf(text + n, sizeof text - n, "%s", written("COREAPPTRACE version=1 event=b\n", false));
    break_trace_core_app_set_clock(NULL);
    BreakTraceCoreAppReport report;
    ASSERT_EQ(convert(text, &report), BREAK_TRACE_CONVERT_OK);
    ASSERT_EQ(report.events, 2u);
    ASSERT_EQ(report.timestamped, 2u);
    ASSERT_TRUE(strstr(g_out, EVENT_HEAD("a", "42") "\"generation\":1}}") != NULL);
    ASSERT_TRUE(strstr(g_out, EVENT_HEAD("b", "43") "}}") != NULL);
}

static BreakTraceClockOffsetStatus clock_offset_of(const char *text, i64 *offset, u64 *error)
{
    return break_trace_core_app_clock_offset(text, strlen(text), offset, error);
}

TEST(core_app_trace_clock_offset_reads_the_single_peer_line)
{
    i64 offset = 7;
    u64 error = 7u;
    ASSERT_EQ(clock_offset_of("COREAPPTRACE version=1 event=level_loaded generation=1\n"
                              "COREAPPTRACE version=1 ts_us=99 event=network_clock_offset"
                              " session=1 peer_hint=7 bytes_us=3 offset_us=-1234 samples=4"
                              " error_us=56\r\n",
                              &offset, &error),
              BREAK_TRACE_CLOCK_OFFSET_OK);
    ASSERT_EQ(offset, -1234);
    ASSERT_EQ(error, 56u);
    ASSERT_EQ(clock_offset_of("COREAPPTRACE version=1 event=network_clock_offset offset_us=0"
                              " error_us=0",
                              &offset, &error),
              BREAK_TRACE_CLOCK_OFFSET_OK);
    ASSERT_EQ(offset, 0);
    ASSERT_EQ(error, 0u);
    ASSERT_EQ(clock_offset_of("COREAPPTRACE version=1 event=network_clock_offset"
                              " offset_us=999999999999999999 error_us=999999999999999999\n",
                              &offset, &error),
              BREAK_TRACE_CLOCK_OFFSET_OK);
    ASSERT_EQ(offset, 999999999999999999ll);
    ASSERT_EQ(error, 999999999999999999ull);
    ASSERT_EQ(clock_offset_of("COREAPPTRACE version=1 event=network_clock_offset"
                              " offset_us=-999999999999999999 error_us=3\n",
                              &offset, &error),
              BREAK_TRACE_CLOCK_OFFSET_OK);
    ASSERT_EQ(offset, -999999999999999999ll);
}

TEST(core_app_trace_clock_offset_rejects_missing_repeated_and_malformed_lines)
{
    static const char *const malformed[] = {
        "COREAPPTRACE version=1 event=network_clock_offset error_us=1\n",
        "COREAPPTRACE version=1 event=network_clock_offset offset_us=1\n",
        "COREAPPTRACE version=1 event=network_clock_offset offset_us= error_us=1\n",
        "COREAPPTRACE version=1 event=network_clock_offset offset_us=- error_us=1\n",
        "COREAPPTRACE version=1 event=network_clock_offset offset_us=-0 error_us=1\n",
        "COREAPPTRACE version=1 event=network_clock_offset offset_us=01 error_us=1\n",
        "COREAPPTRACE version=1 event=network_clock_offset offset_us=+1 error_us=1\n",
        "COREAPPTRACE version=1 event=network_clock_offset offset_us=1x error_us=1\n",
        "COREAPPTRACE version=1 event=network_clock_offset offset_us=1 error_us=-1\n",
        "COREAPPTRACE version=1 event=network_clock_offset offset_us=1 error_us=07\n",
        "COREAPPTRACE version=1 event=network_clock_offset"
        " offset_us=1000000000000000000 error_us=1\n",
        "COREAPPTRACE version=1 event=network_clock_offset offset_us=1"
        " error_us=1000000000000000000\n",
    };
    for (usize i = 0u; i < sizeof(malformed) / sizeof(malformed[0]); ++i) {
        i64 offset = 7;
        u64 error = 9u;
        ASSERT_EQ(clock_offset_of(malformed[i], &offset, &error),
                  BREAK_TRACE_CLOCK_OFFSET_MALFORMED);
        ASSERT_EQ(offset, 7);
        ASSERT_EQ(error, 9u);
    }
    i64 offset = 7;
    u64 error = 9u;
    ASSERT_EQ(clock_offset_of("", &offset, &error), BREAK_TRACE_CLOCK_OFFSET_NOT_FOUND);
    ASSERT_EQ(clock_offset_of("COREAPPTRACE version=1 event=network_stats offset_us=1"
                              " error_us=1\n"
                              "COREAPPTRACE version=2 event=network_clock_offset offset_us=1"
                              " error_us=1\n"
                              "network_clock_offset offset_us=1 error_us=1\n"
                              "COREAPPTRACE version=1 event=network_clock_offset_x offset_us=1"
                              " error_us=1\n",
                              &offset, &error),
              BREAK_TRACE_CLOCK_OFFSET_NOT_FOUND);
    ASSERT_EQ(clock_offset_of("COREAPPTRACE version=1 event=network_clock_offset offset_us=1"
                              " error_us=1\n"
                              "COREAPPTRACE version=1 event=network_clock_offset offset_us=2"
                              " error_us=1\n",
                              &offset, &error),
              BREAK_TRACE_CLOCK_OFFSET_AMBIGUOUS);
    ASSERT_EQ(clock_offset_of("COREAPPTRACE version=1 event=network_clock_offset offset_us=1"
                              " error_us=1\n"
                              "COREAPPTRACE version=1 event=network_clock_offset offset_us=x"
                              " error_us=1\n",
                              &offset, &error),
              BREAK_TRACE_CLOCK_OFFSET_MALFORMED);
    ASSERT_EQ(offset, 7);
    ASSERT_EQ(error, 9u);
}

TEST(core_app_trace_clock_offset_refuses_invalid_arguments)
{
    const char *text = "COREAPPTRACE version=1 event=network_clock_offset offset_us=1 error_us=1";
    i64 offset = 7;
    u64 error = 9u;
    ASSERT_EQ(break_trace_core_app_clock_offset(text, strlen(text), NULL, &error),
              BREAK_TRACE_CLOCK_OFFSET_INVALID);
    ASSERT_EQ(break_trace_core_app_clock_offset(text, strlen(text), &offset, NULL),
              BREAK_TRACE_CLOCK_OFFSET_INVALID);
    ASSERT_EQ(break_trace_core_app_clock_offset(NULL, 1u, &offset, &error),
              BREAK_TRACE_CLOCK_OFFSET_INVALID);
    ASSERT_EQ(break_trace_core_app_clock_offset(NULL, 0u, &offset, &error),
              BREAK_TRACE_CLOCK_OFFSET_NOT_FOUND);
    ASSERT_EQ(break_trace_core_app_clock_offset(text, 30u, &offset, &error),
              BREAK_TRACE_CLOCK_OFFSET_NOT_FOUND);
    ASSERT_EQ(offset, 7);
    ASSERT_EQ(error, 9u);
}

static BreakTraceClockOffsetStatus session_offset_of(const char *text, u64 session, i64 *offset,
                                                     u64 *error)
{
    return break_trace_core_app_clock_offset_for_session(text, strlen(text), session, offset,
                                                         error);
}

#define CLK "COREAPPTRACE version=1 event=network_clock_offset "

TEST(core_app_trace_clock_offset_for_session_picks_that_peer)
{
    const char *trace = "COREAPPTRACE version=1 event=level_loaded generation=1\n"
                        "COREAPPTRACE version=1 ts_us=4 event=network_clock_offset session=1"
                        " offset_us=-500 error_us=4 samples=4\n"
                        CLK "session=12 offset_us=300 error_us=5 samples=4\r\n"
                        CLK "session=2 offset_us=0 error_us=6 samples=4";
    i64 offset = 7;
    u64 error = 7u;
    ASSERT_EQ(session_offset_of(trace, 1u, &offset, &error), BREAK_TRACE_CLOCK_OFFSET_OK);
    ASSERT_EQ(offset, -500);
    ASSERT_EQ(error, 4u);
    ASSERT_EQ(session_offset_of(trace, 12u, &offset, &error), BREAK_TRACE_CLOCK_OFFSET_OK);
    ASSERT_EQ(offset, 300);
    ASSERT_EQ(error, 5u);
    ASSERT_EQ(session_offset_of(trace, 2u, &offset, &error), BREAK_TRACE_CLOCK_OFFSET_OK);
    ASSERT_EQ(offset, 0);
    ASSERT_EQ(error, 6u);
    ASSERT_EQ(session_offset_of(CLK "session=18446744073709551615 offset_us=1 error_us=2\n",
                                UINT64_MAX, &offset, &error),
              BREAK_TRACE_CLOCK_OFFSET_OK);
    ASSERT_EQ(offset, 1);
    /* another session's malformed offset does not matter */
    ASSERT_EQ(session_offset_of(CLK "session=3 offset_us=x error_us=1\n"
                                CLK "session=4 offset_us=9 error_us=1\n",
                                4u, &offset, &error),
              BREAK_TRACE_CLOCK_OFFSET_OK);
    ASSERT_EQ(offset, 9);
}

/* A peer trace names its own session (design 2026-11-20-trace-peer-session). */
#define WELCOME "COREAPPTRACE version=1 event=network_session_welcome "

TEST(core_app_trace_session_reads_what_the_peer_recorded)
{
    u64 session = 7u;
    ASSERT_EQ(break_trace_core_app_session(WELCOME "session=12", strlen(WELCOME "session=12"),
                                           &session),
              BREAK_TRACE_CLOCK_OFFSET_OK);
    ASSERT_EQ(session, 12u);
    /* other lines around it do not matter */
    {
        const char *trace = "COREAPPTRACE version=1 event=level_loaded generation=1\n"
                            WELCOME "session=4 tick=7\r\n"
                            "COREAPPTRACE version=1 event=network_clock_offset session=4"
                            " offset_us=5 error_us=1\n";
        ASSERT_EQ(break_trace_core_app_session(trace, strlen(trace), &session),
                  BREAK_TRACE_CLOCK_OFFSET_OK);
        ASSERT_EQ(session, 4u);
    }
    /* a reconnect re-traces the same session: still one answer */
    {
        const char *trace = WELCOME "session=9\n" WELCOME "session=9\n";
        ASSERT_EQ(break_trace_core_app_session(trace, strlen(trace), &session),
                  BREAK_TRACE_CLOCK_OFFSET_OK);
        ASSERT_EQ(session, 9u);
    }
    ASSERT_EQ(break_trace_core_app_session(WELCOME "session=18446744073709551615",
                                           strlen(WELCOME "session=18446744073709551615"),
                                           &session),
              BREAK_TRACE_CLOCK_OFFSET_OK);
    ASSERT_EQ(session, UINT64_MAX);
}

TEST(core_app_trace_session_rejects_missing_conflicting_and_malformed)
{
    u64 session = 7u;
    /* no welcome line at all */
    ASSERT_EQ(break_trace_core_app_session("COREAPPTRACE version=1 event=level_loaded x=1",
                                           44u, &session),
              BREAK_TRACE_CLOCK_OFFSET_NOT_FOUND);
    ASSERT_EQ(break_trace_core_app_session(NULL, 0u, &session),
              BREAK_TRACE_CLOCK_OFFSET_NOT_FOUND);
    /* two different sessions in one trace */
    {
        const char *trace = WELCOME "session=1\n" WELCOME "session=2\n";
        ASSERT_EQ(break_trace_core_app_session(trace, strlen(trace), &session),
                  BREAK_TRACE_CLOCK_OFFSET_AMBIGUOUS);
    }
    /* a welcome line with no session, or a non-canonical one */
    ASSERT_EQ(break_trace_core_app_session(WELCOME "tick=3", strlen(WELCOME "tick=3"),
                                           &session),
              BREAK_TRACE_CLOCK_OFFSET_MALFORMED);
    ASSERT_EQ(break_trace_core_app_session(WELCOME "session=01", strlen(WELCOME "session=01"),
                                           &session),
              BREAK_TRACE_CLOCK_OFFSET_MALFORMED);
    ASSERT_EQ(break_trace_core_app_session(WELCOME "session=-1", strlen(WELCOME "session=-1"),
                                           &session),
              BREAK_TRACE_CLOCK_OFFSET_MALFORMED);
    ASSERT_EQ(break_trace_core_app_session(WELCOME "session=x", strlen(WELCOME "session=x"),
                                           &session),
              BREAK_TRACE_CLOCK_OFFSET_MALFORMED);
    /* a line the converter rejects is not a welcome line */
    ASSERT_EQ(break_trace_core_app_session("COREAPPTRACE version=2 event=network_session_welcome"
                                           " session=5",
                                           52u, &session),
              BREAK_TRACE_CLOCK_OFFSET_NOT_FOUND);
    ASSERT_EQ(break_trace_core_app_session(WELCOME "session=1", 10u, &session),
              BREAK_TRACE_CLOCK_OFFSET_NOT_FOUND);
    ASSERT_EQ(break_trace_core_app_session(WELCOME "session=1", strlen(WELCOME "session=1"),
                                           NULL),
              BREAK_TRACE_CLOCK_OFFSET_INVALID);
    ASSERT_EQ(break_trace_core_app_session(NULL, 4u, &session),
              BREAK_TRACE_CLOCK_OFFSET_INVALID);
    ASSERT_EQ(session, 7u); /* nothing written on any failure */
}

/* The same from the converted document trace_merge actually reads. */
TEST(core_app_trace_session_from_chrome_reads_the_converted_event)
{
    char json[4096];
    BreakTraceCoreAppReport report;
    u64 session = 7u;
    const char *trace = "COREAPPTRACE version=1 event=level_loaded generation=1\n"
                        WELCOME "session=12 tick=3\n";
    ASSERT_EQ(break_trace_core_app_to_chrome(trace, strlen(trace), json, sizeof json, &report),
              BREAK_TRACE_CONVERT_OK);
    ASSERT_EQ(break_trace_core_app_session_from_chrome(json, strlen(json), &session),
              BREAK_TRACE_CLOCK_OFFSET_OK);
    ASSERT_EQ(session, 12u);
    /* a document without the event */
    {
        const char *plain = "COREAPPTRACE version=1 event=level_loaded generation=1\n";
        ASSERT_EQ(break_trace_core_app_to_chrome(plain, strlen(plain), json, sizeof json,
                                                 &report),
                  BREAK_TRACE_CONVERT_OK);
        ASSERT_EQ(break_trace_core_app_session_from_chrome(json, strlen(json), &session),
                  BREAK_TRACE_CLOCK_OFFSET_NOT_FOUND);
    }
    /* two different sessions */
    {
        const char *two = WELCOME "session=1\n" WELCOME "session=2\n";
        ASSERT_EQ(break_trace_core_app_to_chrome(two, strlen(two), json, sizeof json, &report),
                  BREAK_TRACE_CONVERT_OK);
        ASSERT_EQ(break_trace_core_app_session_from_chrome(json, strlen(json), &session),
                  BREAK_TRACE_CLOCK_OFFSET_AMBIGUOUS);
    }
    /* the same session twice is one answer */
    {
        const char *same = WELCOME "session=5\n" WELCOME "session=5\n";
        ASSERT_EQ(break_trace_core_app_to_chrome(same, strlen(same), json, sizeof json, &report),
                  BREAK_TRACE_CONVERT_OK);
        ASSERT_EQ(break_trace_core_app_session_from_chrome(json, strlen(json), &session),
                  BREAK_TRACE_CLOCK_OFFSET_OK);
        ASSERT_EQ(session, 5u);
    }
    /* the event without a session in its args */
    {
        const char *bare = WELCOME "tick=3\n";
        ASSERT_EQ(break_trace_core_app_to_chrome(bare, strlen(bare), json, sizeof json, &report),
                  BREAK_TRACE_CONVERT_OK);
        ASSERT_EQ(break_trace_core_app_session_from_chrome(json, strlen(json), &session),
                  BREAK_TRACE_CLOCK_OFFSET_MALFORMED);
    }
    session = 7u;
    ASSERT_EQ(break_trace_core_app_session_from_chrome(NULL, 4u, &session),
              BREAK_TRACE_CLOCK_OFFSET_INVALID);
    ASSERT_EQ(break_trace_core_app_session_from_chrome("{}", 2u, NULL),
              BREAK_TRACE_CLOCK_OFFSET_INVALID);
    ASSERT_EQ(break_trace_core_app_session_from_chrome(NULL, 0u, &session),
              BREAK_TRACE_CLOCK_OFFSET_NOT_FOUND);
    ASSERT_EQ(session, 7u);
}

TEST(core_app_trace_clock_offset_for_session_rejects_missing_repeated_and_malformed)
{
    i64 offset = 7;
    u64 error = 9u;
    ASSERT_EQ(session_offset_of(CLK "session=1 offset_us=1 error_us=1\n", 2u, &offset, &error),
              BREAK_TRACE_CLOCK_OFFSET_NOT_FOUND);
    ASSERT_EQ(session_offset_of("", 1u, &offset, &error), BREAK_TRACE_CLOCK_OFFSET_NOT_FOUND);
    ASSERT_EQ(session_offset_of(CLK "session=1 offset_us=1 error_us=1\n"
                                CLK "session=1 offset_us=2 error_us=1\n",
                                1u, &offset, &error),
              BREAK_TRACE_CLOCK_OFFSET_AMBIGUOUS);
    ASSERT_EQ(session_offset_of(CLK "session=1 offset_us=01 error_us=1\n", 1u, &offset, &error),
              BREAK_TRACE_CLOCK_OFFSET_MALFORMED);
    static const char *const bad_session[] = {
        CLK "offset_us=1 error_us=1\n",
        CLK "session= offset_us=1 error_us=1\n",
        CLK "session=01 offset_us=1 error_us=1\n",
        CLK "session=-1 offset_us=1 error_us=1\n",
        CLK "session=1x offset_us=1 error_us=1\n",
        /* below '0': with no digit check it would wrap to UINT64_MAX */
        CLK "session=/ offset_us=1 error_us=1\n",
        CLK "session=18446744073709551616 offset_us=1 error_us=1\n",
    };
    for (usize i = 0u; i < sizeof(bad_session) / sizeof(bad_session[0]); ++i) {
        ASSERT_EQ(session_offset_of(bad_session[i], 1u, &offset, &error),
                  BREAK_TRACE_CLOCK_OFFSET_MALFORMED);
    }
    ASSERT_EQ(offset, 7);
    ASSERT_EQ(error, 9u);
    const char *text = CLK "session=1 offset_us=1 error_us=1";
    ASSERT_EQ(break_trace_core_app_clock_offset_for_session(text, strlen(text), 1u, NULL, &error),
              BREAK_TRACE_CLOCK_OFFSET_INVALID);
    ASSERT_EQ(break_trace_core_app_clock_offset_for_session(text, strlen(text), 1u, &offset, NULL),
              BREAK_TRACE_CLOCK_OFFSET_INVALID);
    ASSERT_EQ(break_trace_core_app_clock_offset_for_session(NULL, 1u, 1u, &offset, &error),
              BREAK_TRACE_CLOCK_OFFSET_INVALID);
    ASSERT_EQ(break_trace_core_app_clock_offset_for_session(NULL, 0u, 1u, &offset, &error),
              BREAK_TRACE_CLOCK_OFFSET_NOT_FOUND);
    ASSERT_EQ(offset, 7);
    ASSERT_EQ(error, 9u);
}

#undef CLK

TEST_MAIN_BEGIN()
    RUN_TEST(core_app_trace_converts_lines_to_chrome_events);
    RUN_TEST(core_app_trace_size_query_and_small_buffer);
    RUN_TEST(core_app_trace_skips_malformed_lines);
    RUN_TEST(core_app_trace_uses_ts_us_as_the_event_time);
    RUN_TEST(core_app_trace_skips_a_non_canonical_ts_us);
    RUN_TEST(core_app_trace_writer_stamps_lines_only_when_a_clock_is_set);
    RUN_TEST(core_app_trace_writer_handles_long_lines_and_round_trips);
    RUN_TEST(core_app_trace_clock_offset_reads_the_single_peer_line);
    RUN_TEST(core_app_trace_clock_offset_rejects_missing_repeated_and_malformed_lines);
    RUN_TEST(core_app_trace_clock_offset_refuses_invalid_arguments);
    RUN_TEST(core_app_trace_session_reads_what_the_peer_recorded);
    RUN_TEST(core_app_trace_session_rejects_missing_conflicting_and_malformed);
    RUN_TEST(core_app_trace_session_from_chrome_reads_the_converted_event);
    RUN_TEST(core_app_trace_clock_offset_for_session_picks_that_peer);
    RUN_TEST(core_app_trace_clock_offset_for_session_rejects_missing_repeated_and_malformed);
TEST_MAIN_END()
