/* ==========================================================================
 *  test_break_crash.c — Stage 5 Phase C Tasks 1+2 tests: canonical crash
 *  record ("break-crash-v1") builder/parse byte-level round-trip + rejection
 *  battery + builder clamps, the bounded spool (layout creation,
 *  put/read/mark, retention 16/16/16, inbox recovery, reopen persistence),
 *  and the Task 2 signal-capture fork tests (child installs, dies by a real
 *  signal, the parent recovers the inbox and parses the record).
 *
 *  The grammar is byte-pinned here: the Task 2 signal-side writer must
 *  produce byte-identical output (one grammar, two writers — see
 *  break_crash.h); the fork tests interlock the two through the Task 1
 *  parser (a deviating signal writer fails to parse).
 * ========================================================================== */

/* glibc under -std=c11 (__STRICT_ANSI__) hides sigaction/SA_SIGINFO/WIF*
 * without a feature test macro (the test_platform_fs_write.c precedent). */
#if !defined(_WIN32)
#define _DEFAULT_SOURCE
#endif

#include "test_framework.h"

#include <core/break_version.h>
#include <crash/break_crash.h>
#include <platform/platform_fs.h>

#include <string.h>

#if !defined(_WIN32)
#include <sys/stat.h> /* mkdir behind TEST_MKDIR (test_platform_fs_write precedent) */
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#endif

#ifndef __has_feature
#define __has_feature(x) 0
#endif
#if defined(__SANITIZE_ADDRESS__) || __has_feature(address_sanitizer)
/* The fork-crash children install break_crash's own SIGSEGV handler over the
 * ASan runtime's; state the permission explicitly (merged with, and
 * overridden per-option by, any ASAN_OPTIONS in the environment). */
const char *__asan_default_options(void) {
    return "allow_user_segv_handler=1";
}
#endif

/* ---- golden grammar fixture (byte-pinned) ------------------------------- */

#define H_MAGIC   "break-crash-v1\n"
#define F_SIGNO   "signo: 0000000b\n"
#define F_CODE    "code: 00000001\n"
#define F_FAULT   "fault_addr: 00000000deadbeef\n"
#define F_PID     "pid: 00000000000004d2\n"
#define F_TID     "tid: 000000000000162e\n"
#define F_RIP     "rip: 0000000000401000\n"
#define F_RSP     "rsp: 00007fffffffe000\n"
#define F_RBP     "rbp: 00007fffffffe100\n"
#define F_BUILD   "build-id: abc123-x\n"
#define F_MODS    "module: 0000000000002000 00000000001f0000 libc.so.6\n" \
                  "module: 0000000000001000 0000000000005000 app\n"
#define F_WINDOW  "stack-window: 0123abcd\n"
#define F_BLOB    "context-blob: ff\n"
#define F_ALL     F_SIGNO F_CODE F_FAULT F_PID F_TID F_RIP F_RSP F_RBP F_BUILD

static const char GOLDEN_RECORD[] = H_MAGIC F_ALL F_MODS F_WINDOW F_BLOB;

static const char DEFAULT_RECORD[] =
    H_MAGIC
    "signo: 00000000\n"
    "code: 00000000\n"
    "fault_addr: 0000000000000000\n"
    "pid: 0000000000000000\n"
    "tid: 0000000000000000\n"
    "rip: 0000000000000000\n"
    "rsp: 0000000000000000\n"
    "rbp: 0000000000000000\n"
    "build-id: unknown\n"
    "stack-window:\n"
    "context-blob:\n";

/* Builds the golden record with tid := tag (0x162e reproduces GOLDEN_RECORD
 * byte-exactly). Returns the byte count (0 = failure). */
static usize build_record(u8 *out, usize cap, u64 tag) {
    static const u8 window[4] = {0x01, 0x23, 0xab, 0xcd};
    static const u8 blob[1] = {0xff};
    BreakCrashRecordBuilder *b = break_crash_record_builder_create();
    if (!b) return 0;
    break_crash_record_builder_set_signal(b, 11, 1, 0xdeadbeefu);
    break_crash_record_builder_set_process(b, 1234, tag);
    break_crash_record_builder_set_registers(b, 0x401000, 0x7fffffffe000ull,
                                             0x7fffffffe100ull);
    break_crash_record_builder_set_build_id(b, "abc123-x");
    break_crash_record_builder_add_module(b, "libc.so.6", 0x2000, 0x1f0000);
    break_crash_record_builder_add_module(b, "app", 0x1000, 0x5000);
    break_crash_record_builder_set_stack_window(b, window, 4);
    break_crash_record_builder_set_context_blob(b, blob, 1);
    usize n = break_crash_record_builder_finish(b, out, cap);
    break_crash_record_builder_destroy(b);
    return n;
}

/* ---- parse helpers ------------------------------------------------------- */

static BreakCrashRecord *parse_cstr(const char *s) {
    return break_crash_record_parse(s, strlen(s));
}

static bool parses(const char *s) {
    BreakCrashRecord *r = parse_cstr(s);
    if (!r) return false;
    break_crash_record_destroy(r);
    return true;
}

/* Checked string append for composed fixtures (keeps NUL at the end). */
static int g_compose_overflow = 0;
static void capp(char *out, usize cap, usize *off, const char *s) {
    usize n = strlen(s);
    if (*off + n >= cap) {
        g_compose_overflow = 1;
        return;
    }
    memcpy(out + *off, s, n + 1);
    *off += n;
}

/* Composes a structurally valid record with n module lines. */
static usize compose_with_modules(char *out, usize cap, int n_modules) {
    usize off = 0;
    int i;
    capp(out, cap, &off, H_MAGIC F_ALL);
    for (i = 0; i < n_modules; i++) {
        char line[96];
        snprintf(line, sizeof(line), "module: %016llx %016llx m%d\n",
                 (unsigned long long)(0x1000 + i), (unsigned long long)(0x100 + i), i);
        capp(out, cap, &off, line);
    }
    capp(out, cap, &off, F_WINDOW F_BLOB);
    return off;
}

/* Composes a structurally valid record whose stack-window holds window_bytes
 * bytes and whose context-blob holds blob_bytes bytes. The window hex cycles
 * "0123456789abcdef" from index 0 (byte k = nibbles 2k,2k+1), the blob from
 * index 1 (byte 0 = 0x12). */
static usize compose_sized(char *out, usize cap, usize window_bytes, usize blob_bytes) {
    static const char HEXC[] = "0123456789abcdef";
    usize off = 0;
    usize i;
    capp(out, cap, &off, H_MAGIC F_ALL F_MODS);
    capp(out, cap, &off, "stack-window:");
    if (window_bytes) {
        capp(out, cap, &off, " ");
        for (i = 0; i < 2 * window_bytes; i++) {
            char c[2] = {HEXC[i & 15], '\0'};
            capp(out, cap, &off, c);
        }
    }
    capp(out, cap, &off, "\n");
    capp(out, cap, &off, "context-blob:");
    if (blob_bytes) {
        capp(out, cap, &off, " ");
        for (i = 0; i < 2 * blob_bytes; i++) {
            char c[2] = {HEXC[(i + 1) & 15], '\0'};
            capp(out, cap, &off, c);
        }
    }
    capp(out, cap, &off, "\n");
    return off;
}

/* ---- record: golden round-trip + defaults -------------------------------- */

TEST(roundtrip_golden_bytes) {
    u8 buf[1024];
    usize n = build_record(buf, sizeof(buf), 0x162e);
    ASSERT_TRUE(n > 0);
    ASSERT_EQ(n, strlen(GOLDEN_RECORD));
    ASSERT_TRUE(memcmp(buf, GOLDEN_RECORD, n) == 0);

    /* Determinism: a second identical builder emits the same bytes. */
    u8 buf2[1024];
    usize n2 = build_record(buf2, sizeof(buf2), 0x162e);
    ASSERT_EQ(n2, n);
    ASSERT_TRUE(memcmp(buf2, buf, n) == 0);

    BreakCrashRecord *r = break_crash_record_parse(buf, n);
    ASSERT_NOT_NULL(r);
    ASSERT_EQ(break_crash_record_signo(r), 11);
    ASSERT_EQ(break_crash_record_fault_addr(r), 0xdeadbeefull);
    ASSERT_EQ(break_crash_record_pid(r), 1234ull);
    ASSERT_EQ(break_crash_record_tid(r), 0x162eull);
    u64 regs[3] = {0, 0, 0};
    break_crash_record_registers(r, regs);
    ASSERT_EQ(regs[0], 0x401000ull);
    ASSERT_EQ(regs[1], 0x7fffffffe000ull);
    ASSERT_EQ(regs[2], 0x7fffffffe100ull);
    ASSERT_STR_EQ(break_crash_record_build_id(r), "abc123-x");
    ASSERT_EQ(break_crash_record_module_count(r), 2ull);
    const char *name = NULL;
    u64 off = 0, size = 0;
    ASSERT_TRUE(break_crash_record_module_at(r, 0, &name, &off, &size));
    ASSERT_STR_EQ(name, "libc.so.6");
    ASSERT_EQ(off, 0x2000ull);
    ASSERT_EQ(size, 0x1f0000ull);
    ASSERT_TRUE(break_crash_record_module_at(r, 1, &name, &off, &size));
    ASSERT_STR_EQ(name, "app");
    ASSERT_EQ(off, 0x1000ull);
    ASSERT_EQ(size, 0x5000ull);
    ASSERT_FALSE(break_crash_record_module_at(r, 2, &name, &off, &size));
    const u8 *bytes = NULL;
    ASSERT_EQ(break_crash_record_stack_window(r, &bytes), 4u);
    ASSERT_NOT_NULL(bytes);
    ASSERT_EQ(bytes[0], 0x01);
    ASSERT_EQ(bytes[1], 0x23);
    ASSERT_EQ(bytes[2], 0xab);
    ASSERT_EQ(bytes[3], 0xcd);
    ASSERT_EQ(break_crash_record_context_blob(r, &bytes), 1u);
    ASSERT_NOT_NULL(bytes);
    ASSERT_EQ(bytes[0], 0xff);
    break_crash_record_destroy(r);
}

TEST(defaults_minimal_record) {
    BreakCrashRecordBuilder *b = break_crash_record_builder_create();
    ASSERT_NOT_NULL(b);
    u8 buf[512];
    usize n = break_crash_record_builder_finish(b, buf, sizeof(buf));
    break_crash_record_builder_destroy(b);
    ASSERT_EQ(n, strlen(DEFAULT_RECORD));
    ASSERT_TRUE(memcmp(buf, DEFAULT_RECORD, n) == 0);

    BreakCrashRecord *r = break_crash_record_parse(buf, n);
    ASSERT_NOT_NULL(r);
    ASSERT_EQ(break_crash_record_signo(r), 0);
    ASSERT_EQ(break_crash_record_fault_addr(r), 0ull);
    ASSERT_EQ(break_crash_record_pid(r), 0ull);
    ASSERT_EQ(break_crash_record_tid(r), 0ull);
    u64 regs[3] = {9, 9, 9};
    break_crash_record_registers(r, regs);
    ASSERT_EQ(regs[0], 0ull);
    ASSERT_EQ(regs[1], 0ull);
    ASSERT_EQ(regs[2], 0ull);
    ASSERT_STR_EQ(break_crash_record_build_id(r), "unknown");
    ASSERT_EQ(break_crash_record_module_count(r), 0ull);
    const u8 *bytes = (const u8 *)0x1;
    ASSERT_EQ(break_crash_record_stack_window(r, &bytes), 0u);
    ASSERT_EQ(break_crash_record_context_blob(r, &bytes), 0u);
    break_crash_record_destroy(r);
}

TEST(parse_scalars_max) {
    static const char MAXED[] =
        H_MAGIC
        "signo: 00000016\n"
        "code: 00000006\n"
        "fault_addr: ffffffffffffffff\n"
        "pid: ffffffffffffffff\n"
        "tid: ffffffffffffffff\n"
        "rip: ffffffffffffffff\n"
        "rsp: ffffffffffffffff\n"
        "rbp: ffffffffffffffff\n"
        "build-id: 0\n"
        "stack-window:\n"
        "context-blob:\n";
    BreakCrashRecord *r = parse_cstr(MAXED);
    ASSERT_NOT_NULL(r);
    ASSERT_EQ(break_crash_record_signo(r), 0x16);
    ASSERT_EQ(break_crash_record_fault_addr(r), 0xffffffffffffffffull);
    ASSERT_EQ(break_crash_record_pid(r), 0xffffffffffffffffull);
    ASSERT_EQ(break_crash_record_tid(r), 0xffffffffffffffffull);
    u64 regs[3] = {0, 0, 0};
    break_crash_record_registers(r, regs);
    ASSERT_EQ(regs[0], 0xffffffffffffffffull);
    ASSERT_EQ(regs[2], 0xffffffffffffffffull);
    ASSERT_STR_EQ(break_crash_record_build_id(r), "0");
    break_crash_record_destroy(r);
}

/* ---- record: canonical rejection battery ---------------------------------- */

TEST(reject_battery_literals) {
    static const char *const bad[] = {
        "",                                          /* empty */
        "break-crash-v2\n" F_ALL F_MODS F_WINDOW F_BLOB,  /* wrong magic */
        F_ALL F_MODS F_WINDOW F_BLOB,                /* missing magic */
        /* unknown key */
        H_MAGIC F_SIGNO F_CODE F_FAULT F_PID F_TID F_RIP F_RSP F_RBP F_BUILD
            "oops: 1\n" F_MODS F_WINDOW F_BLOB,
        /* misordered pid/tid */
        H_MAGIC F_SIGNO F_CODE F_FAULT F_TID F_PID F_RIP F_RSP F_RBP F_BUILD
            F_MODS F_WINDOW F_BLOB,
        /* duplicated signo */
        H_MAGIC F_SIGNO F_SIGNO F_CODE F_FAULT F_PID F_TID F_RIP F_RSP F_RBP
            F_BUILD F_MODS F_WINDOW F_BLOB,
        /* uppercase hex (rip / module offset / blob) */
        H_MAGIC F_SIGNO F_CODE F_FAULT F_PID F_TID
            "rip: 000000000040100A\n" F_RSP F_RBP F_BUILD F_MODS F_WINDOW F_BLOB,
        H_MAGIC F_ALL
            "module: 000000000000200A 00000000001f0000 libc.so.6\n"
            F_WINDOW F_BLOB,
        H_MAGIC F_ALL F_MODS F_WINDOW "context-blob: FF\n",
        /* non-hex letter */
        H_MAGIC F_SIGNO F_CODE F_FAULT F_PID F_TID
            "rip: 000000000040100g\n" F_RSP F_RBP F_BUILD F_MODS F_WINDOW F_BLOB,
        /* fixed-width violations: 7 and 9 hex digits for a hex8 field,
         * 15 for a hex16 field */
        H_MAGIC "signo: 000000b\n" F_CODE F_FAULT F_PID F_TID F_RIP F_RSP F_RBP
            F_BUILD F_MODS F_WINDOW F_BLOB,
        H_MAGIC "signo: 0000000bb\n" F_CODE F_FAULT F_PID F_TID F_RIP F_RSP F_RBP
            F_BUILD F_MODS F_WINDOW F_BLOB,
        H_MAGIC F_SIGNO F_CODE "fault_addr: 0000000deadbeef\n" F_PID F_TID
            F_RIP F_RSP F_RBP F_BUILD F_MODS F_WINDOW F_BLOB,
        /* missing separator space */
        H_MAGIC "signo:0000000b\n" F_CODE F_FAULT F_PID F_TID F_RIP F_RSP F_RBP
            F_BUILD F_MODS F_WINDOW F_BLOB,
        /* build-id: uppercase / empty value / bad char */
        H_MAGIC F_SIGNO F_CODE F_FAULT F_PID F_TID F_RIP F_RSP F_RBP
            "build-id: ABC123\n" F_MODS F_WINDOW F_BLOB,
        H_MAGIC F_SIGNO F_CODE F_FAULT F_PID F_TID F_RIP F_RSP F_RBP
            "build-id: \n" F_MODS F_WINDOW F_BLOB,
        H_MAGIC F_SIGNO F_CODE F_FAULT F_PID F_TID F_RIP F_RSP F_RBP
            "build-id: abc_123\n" F_MODS F_WINDOW F_BLOB,
        /* module name with '/' and with a space */
        H_MAGIC F_ALL
            "module: 0000000000001000 0000000000005000 lib/a.so\n"
            F_WINDOW F_BLOB,
        H_MAGIC F_ALL
            "module: 0000000000001000 0000000000005000 my app\n"
            F_WINDOW F_BLOB,
        /* odd hex count in stack-window */
        H_MAGIC F_ALL F_MODS "stack-window: 012\n" F_BLOB,
        /* trailing-space empty stack-window (the empty form has no space) */
        H_MAGIC F_ALL F_MODS "stack-window: \n" F_BLOB,
        /* truncated: ends (with LF) after fault_addr */
        H_MAGIC F_SIGNO F_CODE F_FAULT,
        /* missing stack-window line */
        H_MAGIC F_ALL F_MODS F_BLOB,
        /* context-blob must be last: extra line after it */
        H_MAGIC F_ALL F_MODS F_WINDOW F_BLOB "extra\n",
        /* module lines must precede stack-window */
        H_MAGIC F_ALL F_WINDOW
            "module: 0000000000001000 0000000000005000 app\n" F_BLOB,
    };
    usize i;
    for (i = 0; i < sizeof(bad) / sizeof(bad[0]); i++) {
        if (parses(bad[i])) {
            printf("  battery case %llu unexpectedly parsed\n", (unsigned long long)i);
        }
        ASSERT_FALSE(parses(bad[i]));
    }
    /* NULL/zero-length argument forms */
    ASSERT_TRUE(break_crash_record_parse(NULL, 5) == NULL);
    ASSERT_TRUE(break_crash_record_parse(GOLDEN_RECORD, 0) == NULL);
}

TEST(reject_battery_mutations) {
    const usize glen = strlen(GOLDEN_RECORD);
    static char buf[70000];

    /* missing final LF */
    memcpy(buf, GOLDEN_RECORD, glen - 1);
    ASSERT_TRUE(break_crash_record_parse(buf, glen - 1) == NULL);

    /* CRLF line endings */
    usize w = 0;
    usize i;
    for (i = 0; i < glen; i++) {
        if (GOLDEN_RECORD[i] == '\n') {
            buf[w++] = '\r';
        }
        buf[w++] = GOLDEN_RECORD[i];
    }
    ASSERT_TRUE(break_crash_record_parse(buf, w) == NULL);

    /* bare CR line endings */
    w = 0;
    for (i = 0; i < glen; i++) {
        if (GOLDEN_RECORD[i] == '\n') {
            buf[w++] = '\r';
        } else {
            buf[w++] = GOLDEN_RECORD[i];
        }
    }
    ASSERT_TRUE(break_crash_record_parse(buf, w) == NULL);

    /* embedded NUL (same length, byte inside the build-id value) */
    memcpy(buf, GOLDEN_RECORD, glen + 1);
    const char *bid = strstr(GOLDEN_RECORD, "abc123-x");
    ASSERT_NOT_NULL(bid);
    buf[bid - GOLDEN_RECORD] = '\0';
    ASSERT_TRUE(break_crash_record_parse(buf, glen) == NULL);

    /* byte >= 0x80 and a TAB are both outside the charset */
    memcpy(buf, GOLDEN_RECORD, glen + 1);
    buf[bid - GOLDEN_RECORD] = (char)0x80;
    ASSERT_TRUE(break_crash_record_parse(buf, glen) == NULL);
    memcpy(buf, GOLDEN_RECORD, glen + 1);
    buf[bid - GOLDEN_RECORD] = '\t';
    ASSERT_TRUE(break_crash_record_parse(buf, glen) == NULL);

    /* oversize: > 64 KiB total (prefix is the valid record) */
    ASSERT_TRUE(glen < 65537u);
    memcpy(buf, GOLDEN_RECORD, glen);
    memset(buf + glen, 'a', 65537u - glen);
    buf[65536] = '\n';
    ASSERT_TRUE(break_crash_record_parse(buf, 65537u) == NULL);
}

TEST(reject_battery_composed) {
    static char big[80000];
    g_compose_overflow = 0;

    /* 65 module lines exceed BREAK_CRASH_MODULE_MAX */
    usize n = compose_with_modules(big, sizeof(big), 65);
    ASSERT_FALSE(g_compose_overflow);
    ASSERT_TRUE(break_crash_record_parse(big, n) == NULL);

    /* 4 KiB + 1 byte stack window / context blob */
    n = compose_sized(big, sizeof(big), 4097, 1);
    ASSERT_FALSE(g_compose_overflow);
    ASSERT_TRUE(break_crash_record_parse(big, n) == NULL);
    n = compose_sized(big, sizeof(big), 4, 4097);
    ASSERT_TRUE(break_crash_record_parse(big, n) == NULL);

    /* 256-char module name */
    usize off = 0;
    g_compose_overflow = 0;
    capp(big, sizeof(big), &off, H_MAGIC F_ALL);
    capp(big, sizeof(big), &off, "module: 0000000000001000 0000000000005000 ");
    int i;
    for (i = 0; i < 256; i++) capp(big, sizeof(big), &off, "n");
    capp(big, sizeof(big), &off, "\n" F_WINDOW F_BLOB);
    ASSERT_FALSE(g_compose_overflow);
    ASSERT_TRUE(break_crash_record_parse(big, off) == NULL);

    /* 65-char build-id */
    off = 0;
    capp(big, sizeof(big), &off, H_MAGIC F_SIGNO F_CODE F_FAULT F_PID F_TID
         F_RIP F_RSP F_RBP "build-id: ");
    for (i = 0; i < 65; i++) capp(big, sizeof(big), &off, "a");
    capp(big, sizeof(big), &off, "\n" F_MODS F_WINDOW F_BLOB);
    ASSERT_FALSE(g_compose_overflow);
    ASSERT_TRUE(break_crash_record_parse(big, off) == NULL);
}

TEST(accept_edge_battery) {
    static char big[80000];
    g_compose_overflow = 0;

    /* exactly 64 modules */
    usize n = compose_with_modules(big, sizeof(big), 64);
    ASSERT_FALSE(g_compose_overflow);
    BreakCrashRecord *r = break_crash_record_parse(big, n);
    ASSERT_NOT_NULL(r);
    ASSERT_EQ(break_crash_record_module_count(r), 64ull);
    const char *name = NULL;
    u64 off = 0, size = 0;
    ASSERT_TRUE(break_crash_record_module_at(r, 63, &name, &off, &size));
    ASSERT_STR_EQ(name, "m63");
    ASSERT_EQ(off, 0x1000ull + 63ull);
    ASSERT_FALSE(break_crash_record_module_at(r, 64, &name, &off, &size));
    break_crash_record_destroy(r);

    /* exactly 4 KiB window + 4 KiB blob, content decoded correctly */
    n = compose_sized(big, sizeof(big), 4096, 4096);
    r = break_crash_record_parse(big, n);
    ASSERT_NOT_NULL(r);
    const u8 *bytes = NULL;
    ASSERT_EQ(break_crash_record_stack_window(r, &bytes), 4096u);
    ASSERT_EQ(bytes[0], 0x01);       /* hex pattern "0123..." */
    ASSERT_EQ(bytes[1], 0x23);
    ASSERT_EQ(bytes[4095], 0xef);    /* nibbles 8190/8191 of the 16-cycle */
    ASSERT_EQ(break_crash_record_context_blob(r, &bytes), 4096u);
    ASSERT_EQ(bytes[0], 0x12);       /* blob pattern offset by one nibble */
    break_crash_record_destroy(r);

    /* empty window + non-empty blob and vice versa */
    n = compose_sized(big, sizeof(big), 0, 4);
    r = break_crash_record_parse(big, n);
    ASSERT_NOT_NULL(r);
    ASSERT_EQ(break_crash_record_stack_window(r, &bytes), 0u);
    ASSERT_EQ(break_crash_record_context_blob(r, &bytes), 4u);
    break_crash_record_destroy(r);
    n = compose_sized(big, sizeof(big), 4, 0);
    r = break_crash_record_parse(big, n);
    ASSERT_NOT_NULL(r);
    ASSERT_EQ(break_crash_record_stack_window(r, &bytes), 4u);
    ASSERT_EQ(break_crash_record_context_blob(r, &bytes), 0u);
    break_crash_record_destroy(r);

    /* 255-char module name; 64-char build-id */
    usize off2 = 0;
    g_compose_overflow = 0;
    capp(big, sizeof(big), &off2, H_MAGIC F_SIGNO F_CODE F_FAULT F_PID F_TID
         F_RIP F_RSP F_RBP "build-id: ");
    int i;
    for (i = 0; i < 64; i++) capp(big, sizeof(big), &off2, "b");
    capp(big, sizeof(big), &off2, "\n");
    capp(big, sizeof(big), &off2, "module: 0000000000001000 0000000000005000 ");
    for (i = 0; i < 255; i++) capp(big, sizeof(big), &off2, "n");
    capp(big, sizeof(big), &off2, "\n" F_WINDOW F_BLOB);
    ASSERT_FALSE(g_compose_overflow);
    r = break_crash_record_parse(big, off2);
    ASSERT_NOT_NULL(r);
    ASSERT_EQ(strlen(break_crash_record_build_id(r)), 64u);
    ASSERT_TRUE(break_crash_record_module_at(r, 0, &name, &off, &size));
    ASSERT_EQ(strlen(name), 255u);
    break_crash_record_destroy(r);
}

/* ---- builder clamps / bounded no-ops ------------------------------------- */

TEST(builder_clamps) {
    BreakCrashRecordBuilder *b = break_crash_record_builder_create();
    ASSERT_NOT_NULL(b);

    /* 5 KiB blob/window clamp to 4 KiB (prefix bytes kept) */
    u8 src[5000];
    usize i;
    for (i = 0; i < sizeof(src); i++) src[i] = (u8)(i & 0xff);
    break_crash_record_builder_set_context_blob(b, src, sizeof(src));
    break_crash_record_builder_set_stack_window(b, src + 7, 4993);
    u8 out[70000];
    usize n = break_crash_record_builder_finish(b, out, sizeof(out));
    ASSERT_TRUE(n > 0);
    BreakCrashRecord *r = break_crash_record_parse(out, n);
    ASSERT_NOT_NULL(r);
    const u8 *bytes = NULL;
    ASSERT_EQ(break_crash_record_context_blob(r, &bytes), 4096u);
    ASSERT_TRUE(memcmp(bytes, src, 4096) == 0);
    ASSERT_EQ(break_crash_record_stack_window(r, &bytes), 4096u);
    ASSERT_TRUE(memcmp(bytes, src + 7, 4096) == 0);
    break_crash_record_destroy(r);

    /* a 255-char name is valid; then fill to exactly 64 modules */
    char longname[300];
    memset(longname, 'x', 255);
    longname[255] = '\0';
    ASSERT_TRUE(break_crash_record_builder_add_module(b, longname, 0, 0));
    int m;
    for (m = 1; m < 64; m++) {
        char nm[32];
        snprintf(nm, sizeof(nm), "mod%d.so", m);
        ASSERT_TRUE(break_crash_record_builder_add_module(b, nm, (u64)m, (u64)(m * 2)));
    }
    /* the 65th module is refused */
    ASSERT_FALSE(break_crash_record_builder_add_module(b, "one-too-many", 0, 0));
    /* invalid names refuse: NULL / empty / '/' / space / 256 chars */
    ASSERT_FALSE(break_crash_record_builder_add_module(b, NULL, 0, 0));
    ASSERT_FALSE(break_crash_record_builder_add_module(b, "", 0, 0));
    ASSERT_FALSE(break_crash_record_builder_add_module(b, "a/b", 0, 0));
    ASSERT_FALSE(break_crash_record_builder_add_module(b, "a b", 0, 0));
    memset(longname, 'x', sizeof(longname) - 1);
    longname[sizeof(longname) - 1] = '\0';
    ASSERT_FALSE(break_crash_record_builder_add_module(b, longname, 0, 0)); /* 299 > 255 */

    /* build-id: invalid values are bounded no-ops (void return) */
    break_crash_record_builder_set_build_id(b, "valid-id-1");
    break_crash_record_builder_set_build_id(b, NULL);
    break_crash_record_builder_set_build_id(b, "");
    break_crash_record_builder_set_build_id(b, "UPPERCASE");
    {
        char longid[80];
        memset(longid, 'z', sizeof(longid) - 1);
        longid[sizeof(longid) - 1] = '\0';
        break_crash_record_builder_set_build_id(b, longid); /* 79 > 64: no-op */
    }
    n = break_crash_record_builder_finish(b, out, sizeof(out));
    ASSERT_TRUE(n > 0);
    r = break_crash_record_parse(out, n);
    ASSERT_NOT_NULL(r);
    ASSERT_STR_EQ(break_crash_record_build_id(r), "valid-id-1");
    ASSERT_EQ(break_crash_record_module_count(r), 64ull);
    const char *name = NULL;
    u64 off = 0, size = 0;
    ASSERT_TRUE(break_crash_record_module_at(r, 0, &name, &off, &size));
    ASSERT_EQ(strlen(name), 255u);
    break_crash_record_destroy(r);
    break_crash_record_builder_destroy(b);
}

TEST(builder_finish_capacity) {
    BreakCrashRecordBuilder *b = break_crash_record_builder_create();
    ASSERT_NOT_NULL(b);
    break_crash_record_builder_set_process(b, 7, 8);
    u8 out[512];
    usize n = break_crash_record_builder_finish(b, out, sizeof(out));
    ASSERT_TRUE(n > 0);
    /* exact capacity works; one byte less overflows to 0 */
    ASSERT_EQ(break_crash_record_builder_finish(b, out, n), n);
    ASSERT_EQ(break_crash_record_builder_finish(b, out, n - 1), 0u);
    ASSERT_EQ(break_crash_record_builder_finish(b, out, 0), 0u);
    ASSERT_EQ(break_crash_record_builder_finish(b, NULL, n), 0u);
    /* the failed finishes did not disturb the builder */
    ASSERT_EQ(break_crash_record_builder_finish(b, out, sizeof(out)), n);
    break_crash_record_builder_destroy(b);
}

/* ---- NULL matrix ---------------------------------------------------------- */

TEST(null_matrix) {
    /* record accessors on NULL */
    ASSERT_EQ(break_crash_record_signo(NULL), 0);
    ASSERT_EQ(break_crash_record_fault_addr(NULL), 0ull);
    ASSERT_EQ(break_crash_record_pid(NULL), 0ull);
    ASSERT_EQ(break_crash_record_tid(NULL), 0ull);
    u64 regs[3] = {9, 9, 9};
    break_crash_record_registers(NULL, regs);
    ASSERT_EQ(regs[0], 0ull);
    ASSERT_EQ(regs[1], 0ull);
    ASSERT_EQ(regs[2], 0ull);
    ASSERT_TRUE(break_crash_record_build_id(NULL) == NULL);
    ASSERT_EQ(break_crash_record_module_count(NULL), 0ull);
    const char *name = (const char *)0x1;
    u64 off = 9, size = 9;
    ASSERT_FALSE(break_crash_record_module_at(NULL, 0, &name, &off, &size));
    const u8 *bytes = (const u8 *)0x1;
    ASSERT_EQ(break_crash_record_stack_window(NULL, &bytes), 0u);
    ASSERT_TRUE(bytes == NULL);
    bytes = (const u8 *)0x1;
    ASSERT_EQ(break_crash_record_context_blob(NULL, &bytes), 0u);
    ASSERT_TRUE(bytes == NULL);
    break_crash_record_destroy(NULL); /* no-op */

    /* NULL out-params on a real record are bounded no-ops/false */
    BreakCrashRecord *r = parse_cstr(GOLDEN_RECORD);
    ASSERT_NOT_NULL(r);
    break_crash_record_registers(r, NULL); /* no-op */
    ASSERT_EQ(break_crash_record_stack_window(r, NULL), 4u); /* len still reported */
    ASSERT_EQ(break_crash_record_context_blob(r, NULL), 1u);
    ASSERT_FALSE(break_crash_record_module_at(r, 0, NULL, &off, &size));
    ASSERT_FALSE(break_crash_record_module_at(r, 0, &name, NULL, &size));
    ASSERT_FALSE(break_crash_record_module_at(r, 0, &name, &off, NULL));
    break_crash_record_destroy(r);

    /* builder ops on NULL */
    break_crash_record_builder_set_signal(NULL, 1, 2, 3);
    break_crash_record_builder_set_process(NULL, 1, 2);
    break_crash_record_builder_set_registers(NULL, 1, 2, 3);
    break_crash_record_builder_set_build_id(NULL, "x");
    ASSERT_FALSE(break_crash_record_builder_add_module(NULL, "m", 0, 0));
    break_crash_record_builder_set_stack_window(NULL, (const u8 *)"x", 1);
    break_crash_record_builder_set_context_blob(NULL, (const u8 *)"x", 1);
    u8 out[16];
    ASSERT_EQ(break_crash_record_builder_finish(NULL, out, sizeof(out)), 0u);
    break_crash_record_builder_destroy(NULL);

    /* NULL data with zero len clears sections (documented) */
    BreakCrashRecordBuilder *b = break_crash_record_builder_create();
    ASSERT_NOT_NULL(b);
    break_crash_record_builder_set_stack_window(b, (const u8 *)"xy", 2);
    break_crash_record_builder_set_stack_window(b, NULL, 0);
    break_crash_record_builder_set_context_blob(b, NULL, 0);
    u8 rec[256];
    usize n = break_crash_record_builder_finish(b, rec, sizeof(rec));
    ASSERT_TRUE(n > 0);
    r = break_crash_record_parse(rec, n);
    ASSERT_NOT_NULL(r);
    ASSERT_EQ(break_crash_record_stack_window(r, &bytes), 0u);
    ASSERT_EQ(break_crash_record_context_blob(r, &bytes), 0u);
    break_crash_record_destroy(r);
    break_crash_record_builder_destroy(b);

    /* spool ops on NULL */
    ASSERT_EQ(break_crash_spool_count(NULL, 0), 0ull);
    ASSERT_FALSE(break_crash_spool_put_pending(NULL, "x", 1));
    u8 *rbuf = (u8 *)0x1;
    u64 rlen = 9;
    ASSERT_FALSE(break_crash_spool_read_pending(NULL, 0, &rbuf, &rlen));
    ASSERT_FALSE(break_crash_spool_mark_sent(NULL, 0));
    ASSERT_FALSE(break_crash_spool_mark_discarded(NULL, 0));
    break_crash_spool_destroy(NULL);
}

/* ---- spool helpers -------------------------------------------------------- */

static void join2(char *out, usize cap, const char *a, const char *b) {
    snprintf(out, cap, "%s/%s", a, b);
}

static bool put_file(const char *path, const void *data, usize len) {
    FILE *fp = fopen(path, "wb");
    if (!fp) return false;
    if (len && fwrite(data, 1, len, fp) != len) {
        fclose(fp);
        return false;
    }
    return fclose(fp) == 0;
}

static long read_file(const char *path, u8 *buf, usize cap) {
    FILE *fp = fopen(path, "rb");
    if (!fp) return -1;
    usize n = fread(buf, 1, cap - 1, fp);
    int extra = fgetc(fp);
    fclose(fp);
    if (extra != EOF) return -2;
    buf[n] = '\0';
    return (long)n;
}

static bool dir_exists(const char *path) {
    u32 count = 0;
    return platform_list_dir(path, NULL, 0, &count);
}

static void rm_tree(const char *root) {
    const char *subs[3] = {"pending", "sent", "discarded"};
    char dir[1100];
    char path[1200];
    int i;
    for (i = 0; i < 3; i++) {
        join2(dir, sizeof(dir), root, subs[i]);
        PlatformDirEntry entries[64];
        u32 count = 0;
        if (platform_list_dir(dir, entries, 64, &count)) {
            u32 j;
            for (j = 0; j < count && j < 64; j++) {
                if (!entries[j].is_dir) {
                    join2(path, sizeof(path), dir, entries[j].name);
                    remove(path);
                }
            }
        }
        TEST_RMDIR(dir);
    }
    join2(path, sizeof(path), root, "crash.inbox");
    remove(path);
    TEST_RMDIR(root);
}

/* Reads the single file inside a spool class dir (white-box forensic pin).
 * Returns the byte count, or -1 when the dir does not hold exactly one file. */
static long read_single_class_file(const char *root, const char *cls, u8 *buf, usize cap) {
    char dir[1100];
    join2(dir, sizeof(dir), root, cls);
    PlatformDirEntry entries[8];
    u32 count = 0;
    if (!platform_list_dir(dir, entries, 8, &count) || count != 1) return -1;
    char path[1200];
    join2(path, sizeof(path), dir, entries[0].name);
    return read_file(path, buf, cap);
}

/* Puts a fresh golden-shaped record with tid := tag into the spool. */
static bool put_tagged(BreakCrashSpool *s, u64 tag) {
    u8 buf[1024];
    usize n = build_record(buf, sizeof(buf), tag);
    if (!n) return false;
    return break_crash_spool_put_pending(s, buf, n);
}

/* Reads pending[index], parses it, and reports its tid. */
static bool pending_tid(BreakCrashSpool *s, u64 index, u64 *out_tid) {
    u8 *buf = NULL;
    u64 len = 0;
    if (!break_crash_spool_read_pending(s, index, &buf, &len)) return false;
    BreakCrashRecord *r = break_crash_record_parse(buf, (usize)len);
    free(buf);
    if (!r) return false;
    *out_tid = break_crash_record_tid(r);
    break_crash_record_destroy(r);
    return true;
}

/* White-box forensic (Task 2 review M1): reads EVERY file in <root>/<cls>
 * and parses its tid, so retention tests pin WHICH records were quarantined
 * or deleted, not just how many. Returns the file count, or -1 on any
 * anomaly (missing dir, subdirectory, unreadable/unparseable file, > cap). */
static int collect_class_tids(const char *root, const char *cls, u64 *tids, usize cap) {
    char dir[1100];
    join2(dir, sizeof(dir), root, cls);
    PlatformDirEntry entries[64];
    u32 count = 0;
    if (!platform_list_dir(dir, entries, 64, &count)) return -1;
    usize n = 0;
    u32 i;
    for (i = 0; i < count; i++) {
        if (entries[i].is_dir) return -1;
        if (n >= cap) return -1;
        char path[1200];
        join2(path, sizeof(path), dir, entries[i].name);
        static u8 buf[70000];
        long len = read_file(path, buf, sizeof(buf));
        if (len <= 0) return -1;
        BreakCrashRecord *r = break_crash_record_parse(buf, (usize)len);
        if (!r) return -1;
        tids[n++] = break_crash_record_tid(r);
        break_crash_record_destroy(r);
    }
    return (int)n;
}

static bool tid_present(const u64 *tids, int n, u64 tid) {
    int i;
    for (i = 0; i < n; i++) {
        if (tids[i] == tid) return true;
    }
    return false;
}

/* ---- spool: layout + put/read round-trip --------------------------------- */

TEST(spool_fresh_open_creates_layout) {
    char root[512];
    test_tmp(root, sizeof(root), "cr_fresh");
    ASSERT_FALSE(dir_exists(root));

    BreakCrashSpool *s = break_crash_spool_open(root);
    ASSERT_NOT_NULL(s);
    ASSERT_TRUE(dir_exists(root));
    char sub[600];
    join2(sub, sizeof(sub), root, "pending");
    ASSERT_TRUE(dir_exists(sub));
    join2(sub, sizeof(sub), root, "sent");
    ASSERT_TRUE(dir_exists(sub));
    join2(sub, sizeof(sub), root, "discarded");
    ASSERT_TRUE(dir_exists(sub));
    join2(sub, sizeof(sub), root, "crash.inbox");
    u64 size = 99;
    ASSERT_TRUE(platform_file_size(sub, &size));
    ASSERT_EQ(size, 0ull);

    ASSERT_EQ(break_crash_spool_count(s, 0), 0ull);
    ASSERT_EQ(break_crash_spool_count(s, 1), 0ull);
    ASSERT_EQ(break_crash_spool_count(s, 2), 0ull);
    ASSERT_EQ(break_crash_spool_count(s, 3), 0ull);   /* unknown class → 0 */
    ASSERT_EQ(break_crash_spool_count(s, -1), 0ull);

    u8 *buf = (u8 *)0x1;
    u64 len = 9;
    ASSERT_FALSE(break_crash_spool_read_pending(s, 0, &buf, &len));
    ASSERT_FALSE(break_crash_spool_mark_sent(s, 0));
    ASSERT_FALSE(break_crash_spool_mark_discarded(s, 0));
    break_crash_spool_destroy(s);

    /* reopen keeps the empty layout (inbox stays empty, no phantom records) */
    s = break_crash_spool_open(root);
    ASSERT_NOT_NULL(s);
    ASSERT_EQ(break_crash_spool_count(s, 0), 0ull);
    ASSERT_EQ(break_crash_spool_count(s, 2), 0ull);
    break_crash_spool_destroy(s);
    rm_tree(root);
}

TEST(spool_put_read_roundtrip) {
    char root[512];
    test_tmp(root, sizeof(root), "cr_putread");
    BreakCrashSpool *s = break_crash_spool_open(root);
    ASSERT_NOT_NULL(s);

    u8 r1[1024], r2[1024];
    usize n1 = build_record(r1, sizeof(r1), 1);
    usize n2 = build_record(r2, sizeof(r2), 2);
    ASSERT_TRUE(n1 > 0 && n2 > 0);

    ASSERT_TRUE(break_crash_spool_put_pending(s, r1, n1));
    ASSERT_EQ(break_crash_spool_count(s, 0), 1ull);
    ASSERT_TRUE(break_crash_spool_put_pending(s, r2, n2));
    ASSERT_EQ(break_crash_spool_count(s, 0), 2ull);

    /* newest-first: index 0 is the second put; bytes round-trip exactly */
    u8 *buf = NULL;
    u64 len = 0;
    ASSERT_TRUE(break_crash_spool_read_pending(s, 0, &buf, &len));
    ASSERT_EQ(len, (u64)n2);
    ASSERT_TRUE(memcmp(buf, r2, n2) == 0);
    free(buf);
    buf = NULL;
    ASSERT_TRUE(break_crash_spool_read_pending(s, 1, &buf, &len));
    ASSERT_EQ(len, (u64)n1);
    ASSERT_TRUE(memcmp(buf, r1, n1) == 0);
    free(buf);
    buf = NULL;
    ASSERT_FALSE(break_crash_spool_read_pending(s, 2, &buf, &len));
    ASSERT_TRUE(buf == NULL);

    /* invalid puts refuse and change nothing */
    static u8 big[BREAK_CRASH_RECORD_MAX + 1u];
    memset(big, 'a', sizeof(big));
    ASSERT_FALSE(break_crash_spool_put_pending(s, big, sizeof(big))); /* oversize */
    ASSERT_FALSE(break_crash_spool_put_pending(s, "hello", 5));       /* unparseable */
    ASSERT_FALSE(break_crash_spool_put_pending(s, r1, 0));            /* empty */
    ASSERT_FALSE(break_crash_spool_put_pending(s, NULL, 10));         /* NULL data */
    ASSERT_EQ(break_crash_spool_count(s, 0), 2ull);
    break_crash_spool_destroy(s);
    rm_tree(root);
}

TEST(spool_retention_pending_overflow) {
    char root[512];
    test_tmp(root, sizeof(root), "cr_retpend");
    BreakCrashSpool *s = break_crash_spool_open(root);
    ASSERT_NOT_NULL(s);

    /* foreign entries are never counted/touched (tmp residue + leading-zero) */
    char fpath[600];
    join2(fpath, sizeof(fpath), root, "pending/notes.txt");
    ASSERT_TRUE(put_file(fpath, "foreign", 7));
    join2(fpath, sizeof(fpath), root, "pending/01.bcr");
    ASSERT_TRUE(put_file(fpath, "lz", 2));
    join2(fpath, sizeof(fpath), root, "pending/1.bcr.tmpXXXXXX");
    ASSERT_TRUE(put_file(fpath, "tmp", 3));

    u64 i;
    for (i = 1; i <= 17; i++) ASSERT_TRUE(put_tagged(s, i));
    ASSERT_EQ(break_crash_spool_count(s, 0), 16ull);
    ASSERT_EQ(break_crash_spool_count(s, 1), 0ull);
    ASSERT_EQ(break_crash_spool_count(s, 2), 1ull); /* oldest pending quarantined */

    /* oldest surviving pending record is tid 2 (tid 1 was discarded) */
    u64 tid = 0;
    ASSERT_TRUE(pending_tid(s, 15, &tid));
    ASSERT_EQ(tid, 2ull);
    ASSERT_TRUE(pending_tid(s, 0, &tid));
    ASSERT_EQ(tid, 17ull);

    /* one more put overflows again */
    ASSERT_TRUE(put_tagged(s, 18));
    ASSERT_EQ(break_crash_spool_count(s, 0), 16ull);
    ASSERT_EQ(break_crash_spool_count(s, 2), 2ull);
    ASSERT_TRUE(pending_tid(s, 15, &tid));
    ASSERT_EQ(tid, 3ull);

    /* foreign files survived everything */
    u64 fsz = 0;
    join2(fpath, sizeof(fpath), root, "pending/notes.txt");
    ASSERT_TRUE(platform_file_size(fpath, &fsz));
    ASSERT_EQ(fsz, 7ull);
    join2(fpath, sizeof(fpath), root, "pending/01.bcr");
    ASSERT_TRUE(platform_file_size(fpath, &fsz));
    join2(fpath, sizeof(fpath), root, "pending/1.bcr.tmpXXXXXX");
    ASSERT_TRUE(platform_file_size(fpath, &fsz));
    break_crash_spool_destroy(s);
    rm_tree(root);
}

TEST(spool_retention_sent_overflow) {
    char root[512];
    test_tmp(root, sizeof(root), "cr_retsent");
    BreakCrashSpool *s = break_crash_spool_open(root);
    ASSERT_NOT_NULL(s);
    /* interleave put+mark: pending itself never overflows (≤1 staged), sent
     * receives 17 records → the oldest is quarantined to discarded */
    u64 i;
    for (i = 1; i <= 17; i++) {
        ASSERT_TRUE(put_tagged(s, i));
        ASSERT_TRUE(break_crash_spool_mark_sent(s, 0));
    }
    ASSERT_EQ(break_crash_spool_count(s, 0), 0ull);
    ASSERT_EQ(break_crash_spool_count(s, 1), 16ull);
    ASSERT_EQ(break_crash_spool_count(s, 2), 1ull); /* oldest sent quarantined */
    break_crash_spool_destroy(s);

    /* content pin (review M1): the quarantined record IS the oldest (tid 1),
     * and sent/ retains exactly tids 2..17 */
    u64 tids[20];
    int n = collect_class_tids(root, "discarded", tids, 20);
    ASSERT_EQ(n, 1);
    ASSERT_EQ(tids[0], 1ull);
    n = collect_class_tids(root, "sent", tids, 20);
    ASSERT_EQ(n, 16);
    u64 t;
    for (t = 2; t <= 17; t++) ASSERT_TRUE(tid_present(tids, n, t));
    rm_tree(root);
}

TEST(spool_retention_discarded_delete) {
    char root[512];
    test_tmp(root, sizeof(root), "cr_retdisc");
    BreakCrashSpool *s = break_crash_spool_open(root);
    ASSERT_NOT_NULL(s);
    /* interleave put+mark: discarded receives 17 records → the oldest is
     * DELETED forever (discarded overflow does not re-quarantine) */
    u64 i;
    for (i = 1; i <= 17; i++) {
        ASSERT_TRUE(put_tagged(s, i));
        ASSERT_TRUE(break_crash_spool_mark_discarded(s, 0));
    }
    ASSERT_EQ(break_crash_spool_count(s, 0), 0ull);
    ASSERT_EQ(break_crash_spool_count(s, 1), 0ull);
    ASSERT_EQ(break_crash_spool_count(s, 2), 16ull);

    /* id counter is not confused by deletions: the next put lands at id 18 */
    ASSERT_TRUE(put_tagged(s, 99));
    u64 tid = 0;
    ASSERT_TRUE(pending_tid(s, 0, &tid));
    ASSERT_EQ(tid, 99ull);
    break_crash_spool_destroy(s);

    /* content pin (review M1): the DELETED record is the oldest (tid 1);
     * discarded/ retains exactly tids 2..17 */
    u64 tids[20];
    int n = collect_class_tids(root, "discarded", tids, 20);
    ASSERT_EQ(n, 16);
    ASSERT_FALSE(tid_present(tids, n, 1));
    u64 t;
    for (t = 2; t <= 17; t++) ASSERT_TRUE(tid_present(tids, n, t));
    rm_tree(root);
}

TEST(spool_mark_transitions_and_bad_index) {
    char root[512];
    test_tmp(root, sizeof(root), "cr_mark");
    BreakCrashSpool *s = break_crash_spool_open(root);
    ASSERT_NOT_NULL(s);
    ASSERT_TRUE(put_tagged(s, 1));
    ASSERT_TRUE(put_tagged(s, 2));
    ASSERT_TRUE(put_tagged(s, 3));
    u64 tid = 0;

    ASSERT_TRUE(break_crash_spool_mark_sent(s, 1)); /* tid 2 → sent */
    ASSERT_EQ(break_crash_spool_count(s, 0), 2ull);
    ASSERT_EQ(break_crash_spool_count(s, 1), 1ull);
    ASSERT_TRUE(pending_tid(s, 0, &tid));
    ASSERT_EQ(tid, 3ull);
    ASSERT_TRUE(pending_tid(s, 1, &tid));
    ASSERT_EQ(tid, 1ull);

    ASSERT_TRUE(break_crash_spool_mark_discarded(s, 1)); /* tid 1 → discarded */
    ASSERT_EQ(break_crash_spool_count(s, 0), 1ull);
    ASSERT_EQ(break_crash_spool_count(s, 2), 1ull);
    ASSERT_TRUE(pending_tid(s, 0, &tid));
    ASSERT_EQ(tid, 3ull);

    ASSERT_FALSE(break_crash_spool_mark_sent(s, 9));
    ASSERT_FALSE(break_crash_spool_mark_discarded(s, 9));
    ASSERT_FALSE(break_crash_spool_mark_sent(s, 1)); /* index 1 now OOB */

    ASSERT_TRUE(break_crash_spool_mark_sent(s, 0)); /* tid 3 → sent */
    ASSERT_EQ(break_crash_spool_count(s, 0), 0ull);
    ASSERT_EQ(break_crash_spool_count(s, 1), 2ull);
    ASSERT_FALSE(break_crash_spool_mark_sent(s, 0)); /* empty pending */
    ASSERT_FALSE(break_crash_spool_mark_discarded(s, 0));
    break_crash_spool_destroy(s);
    rm_tree(root);
}

/* ---- spool: inbox recovery ------------------------------------------------ */

TEST(spool_inbox_recover_valid) {
    char root[512];
    test_tmp(root, sizeof(root), "cr_inbox_ok");
    ASSERT_TRUE(TEST_MKDIR(root) == 0);
    char inbox[600];
    join2(inbox, sizeof(inbox), root, "crash.inbox");
    ASSERT_TRUE(put_file(inbox, GOLDEN_RECORD, strlen(GOLDEN_RECORD)));

    BreakCrashSpool *s = break_crash_spool_open(root);
    ASSERT_NOT_NULL(s);
    ASSERT_EQ(break_crash_spool_count(s, 0), 1ull);
    ASSERT_EQ(break_crash_spool_count(s, 2), 0ull);

    /* inbox reset to empty; the record bytes round-tripped byte-exactly */
    u64 size = 99;
    ASSERT_TRUE(platform_file_size(inbox, &size));
    ASSERT_EQ(size, 0ull);
    u8 *buf = NULL;
    u64 len = 0;
    ASSERT_TRUE(break_crash_spool_read_pending(s, 0, &buf, &len));
    ASSERT_EQ(len, (u64)strlen(GOLDEN_RECORD));
    ASSERT_TRUE(memcmp(buf, GOLDEN_RECORD, len) == 0);
    free(buf);
    break_crash_spool_destroy(s);

    /* reopen does not re-recover (inbox stayed empty) */
    s = break_crash_spool_open(root);
    ASSERT_NOT_NULL(s);
    ASSERT_EQ(break_crash_spool_count(s, 0), 1ull);
    ASSERT_EQ(break_crash_spool_count(s, 2), 0ull);
    u64 tid = 0;
    ASSERT_TRUE(pending_tid(s, 0, &tid));
    ASSERT_EQ(tid, 0x162eull); /* the golden record's tid */
    break_crash_spool_destroy(s);
    rm_tree(root);
}

TEST(spool_inbox_recover_torn_garbage_oversize) {
    u8 fbuf[70000];

    /* torn: a valid prefix truncated mid-line (no final LF) */
    char root[512];
    test_tmp(root, sizeof(root), "cr_inbox_torn");
    ASSERT_TRUE(TEST_MKDIR(root) == 0);
    char inbox[600];
    join2(inbox, sizeof(inbox), root, "crash.inbox");
    ASSERT_TRUE(put_file(inbox, GOLDEN_RECORD, 60));
    BreakCrashSpool *s = break_crash_spool_open(root);
    ASSERT_NOT_NULL(s);
    ASSERT_EQ(break_crash_spool_count(s, 0), 0ull);
    ASSERT_EQ(break_crash_spool_count(s, 2), 1ull);
    u64 size = 99;
    ASSERT_TRUE(platform_file_size(inbox, &size));
    ASSERT_EQ(size, 0ull);
    /* forensic bytes kept whole in discarded/ */
    ASSERT_EQ(read_single_class_file(root, "discarded", fbuf, sizeof(fbuf)), 60);
    ASSERT_TRUE(memcmp(fbuf, GOLDEN_RECORD, 60) == 0);
    break_crash_spool_destroy(s);
    /* reopen does not re-process */
    s = break_crash_spool_open(root);
    ASSERT_NOT_NULL(s);
    ASSERT_EQ(break_crash_spool_count(s, 0), 0ull);
    ASSERT_EQ(break_crash_spool_count(s, 2), 1ull);
    break_crash_spool_destroy(s);
    rm_tree(root);

    /* garbage */
    test_tmp(root, sizeof(root), "cr_inbox_junk");
    ASSERT_TRUE(TEST_MKDIR(root) == 0);
    join2(inbox, sizeof(inbox), root, "crash.inbox");
    static const char junk[] = "this is not a crash record\n";
    ASSERT_TRUE(put_file(inbox, junk, strlen(junk)));
    s = break_crash_spool_open(root);
    ASSERT_NOT_NULL(s);
    ASSERT_EQ(break_crash_spool_count(s, 0), 0ull);
    ASSERT_EQ(break_crash_spool_count(s, 2), 1ull);
    ASSERT_EQ(read_single_class_file(root, "discarded", fbuf, sizeof(fbuf)),
              (long)strlen(junk));
    ASSERT_TRUE(memcmp(fbuf, junk, strlen(junk)) == 0);
    break_crash_spool_destroy(s);
    rm_tree(root);

    /* oversize inbox (> 64 KiB): invalid without a full read, kept whole */
    test_tmp(root, sizeof(root), "cr_inbox_big");
    ASSERT_TRUE(TEST_MKDIR(root) == 0);
    join2(inbox, sizeof(inbox), root, "crash.inbox");
    memset(fbuf, 'x', sizeof(fbuf));
    ASSERT_TRUE(put_file(inbox, fbuf, sizeof(fbuf)));
    s = break_crash_spool_open(root);
    ASSERT_NOT_NULL(s);
    ASSERT_EQ(break_crash_spool_count(s, 0), 0ull);
    ASSERT_EQ(break_crash_spool_count(s, 2), 1ull);
    /* 70000 > cap-1 → -2: the whole file was preserved (not truncated) */
    ASSERT_EQ(read_single_class_file(root, "discarded", fbuf, sizeof(fbuf)), -2);
    break_crash_spool_destroy(s);
    rm_tree(root);
}

/* ---- spool: reopen persistence + id uniqueness ---------------------------- */

TEST(spool_reopen_persistence) {
    char root[512];
    test_tmp(root, sizeof(root), "cr_reopen");
    BreakCrashSpool *s = break_crash_spool_open(root);
    ASSERT_NOT_NULL(s);
    ASSERT_TRUE(put_tagged(s, 1));
    ASSERT_TRUE(put_tagged(s, 2));
    ASSERT_TRUE(put_tagged(s, 3));
    ASSERT_TRUE(break_crash_spool_mark_sent(s, 0)); /* tid 3 → sent */
    break_crash_spool_destroy(s);

    s = break_crash_spool_open(root);
    ASSERT_NOT_NULL(s);
    ASSERT_EQ(break_crash_spool_count(s, 0), 2ull);
    ASSERT_EQ(break_crash_spool_count(s, 1), 1ull);
    ASSERT_EQ(break_crash_spool_count(s, 2), 0ull);
    u64 tid = 0;
    ASSERT_TRUE(pending_tid(s, 0, &tid));
    ASSERT_EQ(tid, 2ull);
    ASSERT_TRUE(pending_tid(s, 1, &tid));
    ASSERT_EQ(tid, 1ull);

    /* the next id must be 4 — a reused id would silently overwrite an
     * existing record (the atomic writer renames over its target) */
    ASSERT_TRUE(put_tagged(s, 4));
    ASSERT_EQ(break_crash_spool_count(s, 0), 3ull);
    ASSERT_TRUE(pending_tid(s, 0, &tid));
    ASSERT_EQ(tid, 4ull);
    ASSERT_TRUE(pending_tid(s, 2, &tid));
    ASSERT_EQ(tid, 1ull); /* oldest intact: no overwrite happened */
    ASSERT_TRUE(break_crash_spool_mark_sent(s, 2)); /* oldest pending → sent */
    ASSERT_EQ(break_crash_spool_count(s, 0), 2ull);
    ASSERT_EQ(break_crash_spool_count(s, 1), 2ull);
    break_crash_spool_destroy(s);

    s = break_crash_spool_open(root);
    ASSERT_NOT_NULL(s);
    ASSERT_EQ(break_crash_spool_count(s, 0), 2ull);
    ASSERT_EQ(break_crash_spool_count(s, 1), 2ull);
    ASSERT_TRUE(pending_tid(s, 0, &tid));
    ASSERT_EQ(tid, 4ull);
    ASSERT_TRUE(pending_tid(s, 1, &tid));
    ASSERT_EQ(tid, 2ull);
    break_crash_spool_destroy(s);
    rm_tree(root);
}

TEST(spool_put_skips_existing_id) {
    char root[512];
    test_tmp(root, sizeof(root), "cr_idskip");
    BreakCrashSpool *s = break_crash_spool_open(root);
    ASSERT_NOT_NULL(s);
    /* foreign canonical-named file lands at the id the next put would use */
    char fpath[600];
    join2(fpath, sizeof(fpath), root, "pending/1.bcr");
    static const char foreign[] = "foreign bytes, not a record";
    ASSERT_TRUE(put_file(fpath, foreign, strlen(foreign)));

    ASSERT_TRUE(put_tagged(s, 7)); /* must skip id 1, land at id 2 */
    ASSERT_EQ(break_crash_spool_count(s, 0), 2ull);
    u64 tid = 0;
    ASSERT_TRUE(pending_tid(s, 0, &tid));
    ASSERT_EQ(tid, 7ull);
    /* the foreign file is byte-intact (read returns bytes as stored) */
    u8 *buf = NULL;
    u64 len = 0;
    ASSERT_TRUE(break_crash_spool_read_pending(s, 1, &buf, &len));
    ASSERT_EQ(len, (u64)strlen(foreign));
    ASSERT_TRUE(memcmp(buf, foreign, len) == 0);
    free(buf);
    break_crash_spool_destroy(s);
    rm_tree(root);
}

TEST(spool_open_bounds) {
    ASSERT_TRUE(break_crash_spool_open(NULL) == NULL);
    ASSERT_TRUE(break_crash_spool_open("") == NULL);

    /* over-long root: no room for "/discarded/<max-id>.bcr" within the PAL
     * path capacity */
    char longroot[1200];
    memset(longroot, 'a', sizeof(longroot) - 1);
    longroot[sizeof(longroot) - 1] = '\0';
    ASSERT_TRUE(break_crash_spool_open(longroot) == NULL);

    /* root path colliding with an existing regular file */
    char root[512];
    test_tmp(root, sizeof(root), "cr_openfile");
    ASSERT_TRUE(put_file(root, "file not dir", 12));
    ASSERT_TRUE(break_crash_spool_open(root) == NULL);
    remove(root);

    /* trailing '/' is normalized away */
    char root2[512];
    test_tmp(root2, sizeof(root2), "cr_openslash");
    char with_slash[520];
    snprintf(with_slash, sizeof(with_slash), "%s/", root2);
    BreakCrashSpool *s = break_crash_spool_open(with_slash);
    ASSERT_NOT_NULL(s);
    ASSERT_EQ(break_crash_spool_count(s, 0), 0ull);
    break_crash_spool_destroy(s);
    rm_tree(root2);
}

/* ---- Task 2: signal capture (fork + waitpid; children die by signal) ---- */

#if !defined(_WIN32)

/* Deliberate null-page store: fault_addr must be 0 and rip nonzero.
 * no_sanitize keeps ASan's shadow checks and UBSan's null-store check from
 * intercepting the fault before the break_crash handler runs; noinline
 * keeps the store out of the caller's frame. */
#if defined(__GNUC__) || defined(__clang__)
__attribute__((noinline, no_sanitize("address"), no_sanitize("undefined"), no_sanitize("thread")))
#endif
static void crash_null_store(void) {
    *(volatile char *)0 = 0;
}

/* Deterministic context-blob pattern shared by the publishing child and the
 * verifying parent (byte i = (i*7+3) & 0xff). */
#define BLOB_PATTERN_PUBLISH 5000u /* publish > 4 KiB: the slot clamps */
static void blob_pattern_fill(u8 *out, usize n) {
    usize i;
    for (i = 0; i < n; i++) out[i] = (u8)((i * 7u + 3u) & 0xffu);
}

/* Child bodies: plain code + _exit only (never ASSERT, never return into the
 * test main, never stdio — fork duplicated the parent's buffers). Distinct
 * exit codes pinpoint the failed step; 90 = body returned without dying. */

static void child_segv_null(const char *root) {
    BreakCrashConfig cfg = {root};
    if (!break_crash_install(&cfg)) _exit(41);
    if (!break_crash_is_installed()) _exit(42);
    crash_null_store();
    _exit(43);
}

static void child_abrt(const char *root) {
    BreakCrashConfig cfg = {root};
    if (!break_crash_install(&cfg)) _exit(41);
    if (!break_crash_is_installed()) _exit(42);
    abort();
    _exit(43);
}

static void child_blob_segv(const char *root) {
    static u8 blob[BLOB_PATTERN_PUBLISH];
    blob_pattern_fill(blob, sizeof(blob));
    BreakCrashConfig cfg = {root};
    if (!break_crash_install(&cfg)) _exit(41);
    break_crash_set_context_blob(blob, sizeof(blob)); /* clamps to 4 KiB */
    crash_null_store();
    _exit(43);
}

static void child_double_install(const char *root) {
    BreakCrashConfig cfg = {root};
    if (break_crash_is_installed()) _exit(40);
    if (!break_crash_install(&cfg)) _exit(41);
    if (!break_crash_is_installed()) _exit(42);
    if (break_crash_install(&cfg)) _exit(44);       /* second install → false */
    if (!break_crash_is_installed()) _exit(45);     /* still installed */
    break_crash_uninstall();
    if (break_crash_is_installed()) _exit(46);
    if (!break_crash_install(&cfg)) _exit(47);      /* re-install after uninstall */
    break_crash_uninstall();
    _exit(0);
}

/* glibc ORs SA_RESTORER into every rt_sigaction install — including the
 * restore itself — while a never-touched signal's queried flags lack it;
 * mask it out of the disposition comparison (kernel-internal bit). */
#ifndef SA_RESTORER
#define SA_RESTORER 0x04000000u /* x86-64 Linux; only reachable behind _GNU_SOURCE */
#endif

/* glibc's sigaction QUERY fills only the kernel's first 64-bit mask word
 * (rt_sigaction sigsetsize=8) and leaves the libc sigset_t tail holding
 * stack garbage — compare the meaningful word only. */
static u64 sigmask_word0(const sigset_t *m) {
    u64 w;
    memcpy(&w, m, sizeof(w));
    return w;
}

static void child_uninstalled_segv(const char *root) {
    BreakCrashConfig cfg = {root};
    struct sigaction before;
    struct sigaction after;
    memset(&before, 0, sizeof(before));
    memset(&after, 0, sizeof(after));
    if (sigaction(SIGSEGV, (void *)0, &before) != 0) _exit(48);
    if (!break_crash_install(&cfg)) _exit(41);
    break_crash_uninstall();
    if (break_crash_is_installed()) _exit(46);
    if (sigaction(SIGSEGV, (void *)0, &after) != 0) _exit(49);
    /* uninstall restored the pre-install disposition exactly (under a
     * sanitizer runtime that is the runtime's own handler, not SIG_DFL) */
    if ((before.sa_flags & ~SA_RESTORER) != (after.sa_flags & ~SA_RESTORER)) _exit(50);
    if (sigmask_word0(&before.sa_mask) != sigmask_word0(&after.sa_mask)) _exit(51);
    if ((before.sa_flags & SA_SIGINFO)
            ? before.sa_sigaction != after.sa_sigaction
            : before.sa_handler != after.sa_handler) _exit(52);
    /* Die by a clean SIGSEGV regardless of any restored runtime handler:
     * death-by-signal with NO record is the pinned post-uninstall state. */
    (void)signal(SIGSEGV, SIG_DFL);
    crash_null_store();
    _exit(43);
}

static pid_t spawn_child(void (*fn)(const char *), const char *root) {
    pid_t pid = fork();
    if (pid == 0) {
        fn(root);
        _exit(90);
    }
    return pid;
}

static int wait_status(pid_t pid) {
    int st = 0;
    if (waitpid(pid, &st, 0) != pid) return -1;
    return st;
}

/* Opens the spool (recovering the child's inbox into pending/), requires
 * exactly one pending record and an empty discarded/, and returns that
 * record's bytes (caller frees). */
static bool fetch_recovered(const char *root, u8 **out_buf, u64 *out_len) {
    BreakCrashSpool *s = break_crash_spool_open(root);
    if (!s) return false;
    bool ok = break_crash_spool_count(s, 0) == 1ull &&
              break_crash_spool_count(s, 2) == 0ull &&
              break_crash_spool_read_pending(s, 0, out_buf, out_len);
    break_crash_spool_destroy(s);
    return ok;
}

/* The build id the child's install must have captured: the "+" suffix of
 * break_version_string() (same TU compile, same BREAK_BUILD_ID), or
 * "unknown" without one. */
static const char *expected_build_id(void) {
    const char *v = break_version_string();
    const char *plus = v ? strchr(v, '+') : NULL;
    return (plus && plus[1]) ? plus + 1 : "unknown";
}

/* Assertions every captured record shares: the child's pid/tid (main
 * thread: tid == pid), nonzero rip, the build-id suffix, and a non-empty
 * all-basename module list. */
static int common_record_fields_fail(BreakCrashRecord *r, pid_t child_pid) {
    int failed = 0;
    u64 regs[3] = {0, 0, 0};
    break_crash_record_registers(r, regs);
    if (break_crash_record_pid(r) != (u64)child_pid) failed = 1;
    if (break_crash_record_tid(r) != (u64)child_pid) failed = 1;
    if (regs[0] == 0) failed = 1;                              /* rip nonzero */
    if (regs[1] == 0) failed = 1;                              /* rsp nonzero */
    if (strcmp(break_crash_record_build_id(r), expected_build_id()) != 0) failed = 1;
    u64 mods = break_crash_record_module_count(r);
    if (mods < 1) failed = 1;
    u64 i;
    for (i = 0; i < mods; i++) {
        const char *name = NULL;
        u64 off = 0, size = 0;
        if (!break_crash_record_module_at(r, i, &name, &off, &size)) failed = 1;
        else if (!name[0] || strchr(name, '/') != NULL) failed = 1; /* basename only */
    }
    return failed;
}

#endif /* !_WIN32 */

#if !defined(_WIN32)
/* Privacy pin helper: true when the lowercase-hex encoding of `plain`
 * (e.g. an env string) appears in the raw record bytes — i.e. when the
 * stack window leaked it. Hand-rolled bounded scan. */
static bool raw_contains_hex_of(const u8 *hay, usize haylen, const char *plain) {
    static const char h[] = "0123456789abcdef";
    usize n = strlen(plain);
    if (n < 4 || n > 256) return false; /* short patterns are not pinned */
    u8 pat[512];
    usize i;
    for (i = 0; i < n; i++) {
        pat[2 * i] = (u8)h[((const u8 *)plain)[i] >> 4];
        pat[2 * i + 1] = (u8)h[((const u8 *)plain)[i] & 15];
    }
    if (haylen < 2 * n) return false;
    for (i = 0; i + 2 * n <= haylen; i++) {
        if (memcmp(hay + i, pat, 2 * n) == 0) return true;
    }
    return false;
}
#endif

TEST(crash_segv_captures_record) {
#if defined(_WIN32)
    ASSERT_TRUE(1); /* POSIX signal path only this phase (Windows stub) */
#else
    char root[512];
    test_tmp(root, sizeof(root), "cr_segv");
    pid_t pid = spawn_child(child_segv_null, root);
    ASSERT_TRUE(pid > 0);
    int st = wait_status(pid);
    ASSERT_TRUE(st >= 0);
    ASSERT_TRUE(WIFSIGNALED(st));                 /* died BY the signal... */
    ASSERT_EQ(WTERMSIG(st), SIGSEGV);             /* ...with original semantics */

    u8 *rec = NULL;
    u64 rlen = 0;
    ASSERT_TRUE(fetch_recovered(root, &rec, &rlen));
    ASSERT_TRUE(rlen > 0 && rlen <= BREAK_CRASH_RECORD_MAX); /* ≤ 64 KiB */
    BreakCrashRecord *r = break_crash_record_parse(rec, (usize)rlen);
    ASSERT_NOT_NULL(r); /* signal writer byte-interlocked with the parser */
    ASSERT_EQ(break_crash_record_signo(r), SIGSEGV);
    ASSERT_EQ(break_crash_record_fault_addr(r), 0ull);
    ASSERT_FALSE(common_record_fields_fail(r, pid));
    const u8 *bytes = NULL;
    usize win = break_crash_record_stack_window(r, &bytes);
    ASSERT_TRUE(win > 0);                          /* stack window present */
    ASSERT_TRUE(win <= BREAK_CRASH_STACK_WINDOW_MAX);
    break_crash_record_destroy(r);
    /* privacy-by-omission pin: the argv/env strings block at the top of the
     * initial stack must NOT appear in the window — HOME is an original
     * stack-zone env string of this very process tree (fork-inherited by
     * the child), so without the zone clamp its hex encoding would be in
     * the record here. Skipped when HOME is absent/short. */
    const char *home = getenv("HOME");
    if (home) {
        ASSERT_FALSE(raw_contains_hex_of(rec, (usize)rlen, home));
    }
    free(rec);
    rm_tree(root);
#endif
}

TEST(crash_abrt_captures_record) {
#if defined(_WIN32)
    ASSERT_TRUE(1);
#else
    char root[512];
    test_tmp(root, sizeof(root), "cr_abrt");
    pid_t pid = spawn_child(child_abrt, root);
    ASSERT_TRUE(pid > 0);
    int st = wait_status(pid);
    ASSERT_TRUE(st >= 0);
    ASSERT_TRUE(WIFSIGNALED(st));
    ASSERT_EQ(WTERMSIG(st), SIGABRT);

    u8 *rec = NULL;
    u64 rlen = 0;
    ASSERT_TRUE(fetch_recovered(root, &rec, &rlen));
    ASSERT_TRUE(rlen > 0 && rlen <= BREAK_CRASH_RECORD_MAX);
    BreakCrashRecord *r = break_crash_record_parse(rec, (usize)rlen);
    ASSERT_NOT_NULL(r);
    ASSERT_EQ(break_crash_record_signo(r), SIGABRT);
    ASSERT_FALSE(common_record_fields_fail(r, pid));
    break_crash_record_destroy(r);
    free(rec);
    rm_tree(root);
#endif
}

TEST(crash_context_blob_captured) {
#if defined(_WIN32)
    ASSERT_TRUE(1);
#else
    char root[512];
    test_tmp(root, sizeof(root), "cr_blob");
    pid_t pid = spawn_child(child_blob_segv, root);
    ASSERT_TRUE(pid > 0);
    int st = wait_status(pid);
    ASSERT_TRUE(st >= 0);
    ASSERT_TRUE(WIFSIGNALED(st));
    ASSERT_EQ(WTERMSIG(st), SIGSEGV);

    u8 *rec = NULL;
    u64 rlen = 0;
    ASSERT_TRUE(fetch_recovered(root, &rec, &rlen));
    BreakCrashRecord *r = break_crash_record_parse(rec, (usize)rlen);
    ASSERT_NOT_NULL(r);
    /* the published 5000-byte blob clamped to the 4 KiB slot, prefix kept */
    static u8 want[BLOB_PATTERN_PUBLISH];
    blob_pattern_fill(want, sizeof(want));
    const u8 *bytes = NULL;
    ASSERT_EQ(break_crash_record_context_blob(r, &bytes), (usize)BREAK_CRASH_CONTEXT_BLOB_MAX);
    ASSERT_TRUE(memcmp(bytes, want, BREAK_CRASH_CONTEXT_BLOB_MAX) == 0);
    break_crash_record_destroy(r);
    free(rec);
    rm_tree(root);
#endif
}

TEST(crash_double_install_refused) {
#if defined(_WIN32)
    ASSERT_TRUE(1);
#else
    char root[512];
    test_tmp(root, sizeof(root), "cr_dbl");
    pid_t pid = spawn_child(child_double_install, root);
    ASSERT_TRUE(pid > 0);
    int st = wait_status(pid);
    ASSERT_TRUE(st >= 0);
    ASSERT_TRUE(WIFEXITED(st));
    ASSERT_EQ(WEXITSTATUS(st), 0);
    /* no crash happened: the spool exists but holds no records */
    BreakCrashSpool *s = break_crash_spool_open(root);
    ASSERT_NOT_NULL(s);
    ASSERT_EQ(break_crash_spool_count(s, 0), 0ull);
    ASSERT_EQ(break_crash_spool_count(s, 2), 0ull);
    break_crash_spool_destroy(s);
    rm_tree(root);
#endif
}

TEST(crash_uninstall_no_record) {
#if defined(_WIN32)
    ASSERT_TRUE(1);
#else
    char root[512];
    test_tmp(root, sizeof(root), "cr_uninst");
    pid_t pid = spawn_child(child_uninstalled_segv, root);
    ASSERT_TRUE(pid > 0);
    int st = wait_status(pid);
    ASSERT_TRUE(st >= 0);
    ASSERT_TRUE(WIFSIGNALED(st));
    ASSERT_EQ(WTERMSIG(st), SIGSEGV); /* still dies by SIGSEGV... */

    BreakCrashSpool *s = break_crash_spool_open(root);
    ASSERT_NOT_NULL(s);
    ASSERT_EQ(break_crash_spool_count(s, 0), 0ull); /* ...but WITHOUT a record */
    ASSERT_EQ(break_crash_spool_count(s, 2), 0ull);
    char inbox[600];
    join2(inbox, sizeof(inbox), root, "crash.inbox");
    u64 size = 99;
    ASSERT_TRUE(platform_file_size(inbox, &size));
    ASSERT_EQ(size, 0ull);
    break_crash_spool_destroy(s);
    rm_tree(root);
#endif
}

/* -------------------------------------------------------------------------- */

TEST_MAIN_BEGIN()
    RUN_TEST(roundtrip_golden_bytes);
    RUN_TEST(defaults_minimal_record);
    RUN_TEST(parse_scalars_max);
    RUN_TEST(reject_battery_literals);
    RUN_TEST(reject_battery_mutations);
    RUN_TEST(reject_battery_composed);
    RUN_TEST(accept_edge_battery);
    RUN_TEST(builder_clamps);
    RUN_TEST(builder_finish_capacity);
    RUN_TEST(null_matrix);
    RUN_TEST(spool_fresh_open_creates_layout);
    RUN_TEST(spool_put_read_roundtrip);
    RUN_TEST(spool_retention_pending_overflow);
    RUN_TEST(spool_retention_sent_overflow);
    RUN_TEST(spool_retention_discarded_delete);
    RUN_TEST(spool_mark_transitions_and_bad_index);
    RUN_TEST(spool_inbox_recover_valid);
    RUN_TEST(spool_inbox_recover_torn_garbage_oversize);
    RUN_TEST(spool_reopen_persistence);
    RUN_TEST(spool_put_skips_existing_id);
    RUN_TEST(spool_open_bounds);
    RUN_TEST(crash_segv_captures_record);
    RUN_TEST(crash_abrt_captures_record);
    RUN_TEST(crash_context_blob_captured);
    RUN_TEST(crash_double_install_refused);
    RUN_TEST(crash_uninstall_no_record);
TEST_MAIN_END()
