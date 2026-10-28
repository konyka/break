/* break_crash — Stage 5 Phase C Tasks 1-3 implementation: the canonical crash
 * record ("break-crash-v1"), the bounded on-disk spool, the
 * async-signal-safe capture (install/handler), the pure redaction pass, and
 * the caller-supplied upload seam with its persisted retry/discard policy.
 * The grammar and every behavioral contract are documented in break_crash.h;
 * the parse discipline
 * mirrors the Phase A manifest parser (break_update.c): ASCII subset + LF
 * only, fixed key order, fixed-width lowercase hex, two passes (validate
 * everything BEFORE filling — allocation size here is a fixed struct, never
 * attacker-derived), NULL = the only oracle.
 *
 * Zero external
 * dependencies: the write-side PAL (platform_fs.h) and the build identity
 * (break_version.h) are consumed header-only and resolved at the consumer's
 * final link (the test_break_update / test_break_version precedent). */

#if !defined(_WIN32)
/* glibc under -std=c11 (__STRICT_ANSI__) hides open(O_DIRECTORY)/fsync
 * without a feature test macro (the platform_fs.c precedent); _GNU_SOURCE
 * adds ucontext's REG_RIP/REG_RSP/REG_RBP indices. */
#define _DEFAULT_SOURCE
#if !defined(_GNU_SOURCE)
#define _GNU_SOURCE
#endif
#endif

#include <crash/break_crash.h>

#include <core/break_version.h>
#include <platform/platform_fs.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if !defined(_WIN32)
#include <fcntl.h>
#include <signal.h>
#include <stdatomic.h>
#include <unistd.h>
#if defined(__linux__)
#include <sys/syscall.h>
#include <ucontext.h>
#elif defined(__APPLE__)
#include <pthread.h>
#endif
#endif

/* ==========================================================================
 *  Record: strict grammar
 * ========================================================================== */

static int bc_hexval(u8 c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return -1;
}

typedef struct {
    const u8 *text;
    usize len;
    usize pos;
} BcCursor;

/* Next LF-terminated line (content excludes the LF). False at end of input;
 * the caller's final-LF pre-check makes a missing LF unreachable. */
static bool bc_next_line(BcCursor *c, const u8 **line, usize *line_len) {
    if (c->pos >= c->len) return false;
    const u8 *start = c->text + c->pos;
    const u8 *nl = memchr(start, '\n', c->len - c->pos);
    if (!nl) return false;
    *line = start;
    *line_len = (usize)(nl - start);
    c->pos += *line_len + 1;
    return true;
}

static bool bc_starts_with(const u8 *line, usize n, const char *prefix) {
    usize p = strlen(prefix);
    return n >= p && memcmp(line, prefix, p) == 0;
}

/* Exactly n lowercase hex chars → u64 (n ≤ 16: no overflow possible). */
static bool bc_parse_hex(const u8 *s, usize n, u64 *out) {
    u64 v = 0;
    usize i;
    for (i = 0; i < n; i++) {
        int h = bc_hexval(s[i]);
        if (h < 0) return false;
        v = (v << 4) | (u64)h;
    }
    *out = v;
    return true;
}

/* Line is exactly "<key>" + " " + <width lowercase hex>. key includes ':'. */
static bool bc_line_hex(const u8 *line, usize n, const char *key, usize width, u64 *out) {
    usize k = strlen(key);
    if (n != k + 1 + width) return false;
    if (memcmp(line, key, k) != 0) return false;
    if (line[k] != ' ') return false;
    return bc_parse_hex(line + k + 1, width, out);
}

/* "build-id: " + 1..64 chars of [0-9a-z-]. */
static bool bc_valid_build_id_line(const u8 *line, usize n) {
    const usize prefix = 10; /* "build-id: " */
    if (n < prefix + 1 || n > prefix + 64) return false;
    if (!bc_starts_with(line, n, "build-id: ")) return false;
    usize i;
    for (i = prefix; i < n; i++) {
        u8 c = line[i];
        if (!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || c == '-'))
            return false;
    }
    return true;
}

/* "module: " + 16hex + " " + 16hex + " " + name(1..255 of 0x21-0x7E minus '/') */
static bool bc_valid_module_line(const u8 *line, usize n) {
    const usize prefix = 8; /* "module: " */
    if (n < prefix + 16 + 1 + 16 + 1 + 1) return false;
    u64 v;
    if (!bc_parse_hex(line + prefix, 16, &v)) return false;
    if (line[prefix + 16] != ' ') return false;
    if (!bc_parse_hex(line + prefix + 17, 16, &v)) return false;
    if (line[prefix + 33] != ' ') return false;
    const u8 *nm = line + prefix + 34;
    usize nl = n - prefix - 34;
    if (nl > 255) return false; /* (nl ≥ 1 via the n bound above) */
    usize i;
    for (i = 0; i < nl; i++) {
        u8 c = nm[i];
        if (c < 0x21 || c > 0x7E || c == '/') return false;
    }
    return true;
}

/* "<key>:" then EOL (empty form — NO trailing space), or " " + even-count
 * lowercase hex of 2..2*max_bytes chars. key includes ':'. */
static bool bc_valid_hexblob_line(const u8 *line, usize n, const char *key, usize max_bytes) {
    usize k = strlen(key);
    if (n < k || memcmp(line, key, k) != 0) return false;
    if (n == k) return true; /* empty */
    if (line[k] != ' ') return false;
    usize hex = n - k - 1;
    if (hex == 0 || (hex & 1u) != 0 || hex > 2 * max_bytes) return false;
    usize i;
    for (i = 0; i < hex; i++) {
        if (bc_hexval(line[k + 1 + i]) < 0) return false;
    }
    return true;
}

/* Pass 1: validate the whole structure (nothing stored). */
static bool bc_validate(const u8 *bytes, usize len) {
    BcCursor cur = {bytes, len, 0};
    const u8 *line;
    usize n;
    u64 v;

    if (!bc_next_line(&cur, &line, &n)) return false;
    if (n != 14 || memcmp(line, "break-crash-v1", 14) != 0) return false;

    static const struct { const char *key; usize width; } FIXED[8] = {
        {"signo:", 8}, {"code:", 8},
        {"fault_addr:", 16}, {"pid:", 16}, {"tid:", 16},
        {"rip:", 16}, {"rsp:", 16}, {"rbp:", 16},
    };
    int i;
    for (i = 0; i < 8; i++) {
        if (!bc_next_line(&cur, &line, &n)) return false;
        if (!bc_line_hex(line, n, FIXED[i].key, FIXED[i].width, &v)) return false;
    }

    if (!bc_next_line(&cur, &line, &n)) return false;
    if (!bc_valid_build_id_line(line, n)) return false;

    u64 modules = 0;
    for (;;) {
        if (!bc_next_line(&cur, &line, &n)) return false;
        if (!bc_starts_with(line, n, "module: ")) break; /* → stack-window */
        if (!bc_valid_module_line(line, n)) return false;
        if (modules >= BREAK_CRASH_MODULE_MAX) return false;
        modules++;
    }
    if (!bc_valid_hexblob_line(line, n, "stack-window:", BREAK_CRASH_STACK_WINDOW_MAX))
        return false;
    if (!bc_next_line(&cur, &line, &n)) return false;
    if (!bc_valid_hexblob_line(line, n, "context-blob:", BREAK_CRASH_CONTEXT_BLOB_MAX))
        return false;
    return cur.pos == cur.len; /* context-blob is the last line */
}

typedef struct {
    u64 offset;
    u64 size;
    char name[256];
} BcModule;

struct BreakCrashRecord {
    int signo;
    int code;
    u64 fault_addr;
    u64 pid;
    u64 tid;
    u64 rip;
    u64 rsp;
    u64 rbp;
    char build_id[65];
    u64 module_count;
    BcModule modules[BREAK_CRASH_MODULE_MAX];
    u8 stack_window[BREAK_CRASH_STACK_WINDOW_MAX];
    usize stack_window_len;
    u8 context_blob[BREAK_CRASH_CONTEXT_BLOB_MAX];
    usize context_blob_len;
};

/* Decodes a validated hexblob line into out (cap ≥ max_bytes). Returns the
 * byte count (0 for the empty form). */
static usize bc_decode_hexblob(const u8 *line, usize n, const char *key, u8 *out) {
    usize k = strlen(key);
    if (n == k) return 0;
    const u8 *h = line + k + 1;
    usize bytes = (n - k - 1) / 2;
    usize i;
    for (i = 0; i < bytes; i++) {
        out[i] = (u8)((bc_hexval(h[2 * i]) << 4) | bc_hexval(h[2 * i + 1]));
    }
    return bytes;
}

/* Pass 2: fill the record (cannot fail — pass 1 validated every line). */
static void bc_fill(BreakCrashRecord *r, const u8 *bytes, usize len) {
    BcCursor cur = {bytes, len, 0};
    const u8 *line;
    usize n;
    u64 v = 0;

    bc_next_line(&cur, &line, &n); /* magic — validated */

    bc_next_line(&cur, &line, &n);
    bc_line_hex(line, n, "signo:", 8, &v);
    r->signo = (int)(u32)v;
    bc_next_line(&cur, &line, &n);
    bc_line_hex(line, n, "code:", 8, &v);
    r->code = (int)(u32)v;
    bc_next_line(&cur, &line, &n);
    bc_line_hex(line, n, "fault_addr:", 16, &r->fault_addr);
    bc_next_line(&cur, &line, &n);
    bc_line_hex(line, n, "pid:", 16, &r->pid);
    bc_next_line(&cur, &line, &n);
    bc_line_hex(line, n, "tid:", 16, &r->tid);
    bc_next_line(&cur, &line, &n);
    bc_line_hex(line, n, "rip:", 16, &r->rip);
    bc_next_line(&cur, &line, &n);
    bc_line_hex(line, n, "rsp:", 16, &r->rsp);
    bc_next_line(&cur, &line, &n);
    bc_line_hex(line, n, "rbp:", 16, &r->rbp);

    bc_next_line(&cur, &line, &n);
    memcpy(r->build_id, line + 10, n - 10);
    r->build_id[n - 10] = '\0';

    while (bc_next_line(&cur, &line, &n) && bc_starts_with(line, n, "module: ")) {
        BcModule *m = &r->modules[r->module_count++];
        bc_parse_hex(line + 8, 16, &m->offset);
        bc_parse_hex(line + 8 + 17, 16, &m->size);
        usize nl = n - 8 - 34;
        memcpy(m->name, line + 8 + 34, nl);
        m->name[nl] = '\0';
    }
    r->stack_window_len = bc_decode_hexblob(line, n, "stack-window:", r->stack_window);
    bc_next_line(&cur, &line, &n);
    r->context_blob_len = bc_decode_hexblob(line, n, "context-blob:", r->context_blob);
}

BreakCrashRecord *break_crash_record_parse(const void *text, usize len) {
    if (!text || len == 0) return NULL;
    if (len > BREAK_CRASH_RECORD_MAX) return NULL;
    const u8 *bytes = text;

    /* ASCII subset + LF only; the text ends with a final LF. */
    if (bytes[len - 1] != '\n') return NULL;
    usize i;
    for (i = 0; i < len; i++) {
        u8 c = bytes[i];
        if (c != '\n' && (c < 0x20 || c > 0x7E)) return NULL;
    }

    if (!bc_validate(bytes, len)) return NULL;   /* pass 1 */
    BreakCrashRecord *r = calloc(1, sizeof(*r));
    if (!r) return NULL;
    bc_fill(r, bytes, len);                       /* pass 2: cannot fail */
    return r;
}

void break_crash_record_destroy(BreakCrashRecord *r) {
    free(r); /* free(NULL) is the documented no-op */
}

int break_crash_record_signo(const BreakCrashRecord *r) {
    return r ? r->signo : 0;
}

u64 break_crash_record_fault_addr(const BreakCrashRecord *r) {
    return r ? r->fault_addr : 0;
}

u64 break_crash_record_pid(const BreakCrashRecord *r) {
    return r ? r->pid : 0;
}

u64 break_crash_record_tid(const BreakCrashRecord *r) {
    return r ? r->tid : 0;
}

void break_crash_record_registers(const BreakCrashRecord *r, u64 out_rip_rsp_rbp[3]) {
    if (!out_rip_rsp_rbp) return;
    out_rip_rsp_rbp[0] = r ? r->rip : 0;
    out_rip_rsp_rbp[1] = r ? r->rsp : 0;
    out_rip_rsp_rbp[2] = r ? r->rbp : 0;
}

const char *break_crash_record_build_id(const BreakCrashRecord *r) {
    return r ? r->build_id : NULL;
}

u64 break_crash_record_module_count(const BreakCrashRecord *r) {
    return r ? r->module_count : 0;
}

bool break_crash_record_module_at(const BreakCrashRecord *r, u64 i,
                                  const char **out_name, u64 *out_offset, u64 *out_size) {
    if (!r || !out_name || !out_offset || !out_size) return false;
    if (i >= r->module_count) return false;
    const BcModule *m = &r->modules[i];
    *out_name = m->name;
    *out_offset = m->offset;
    *out_size = m->size;
    return true;
}

usize break_crash_record_stack_window(const BreakCrashRecord *r, const u8 **out_bytes) {
    if (!r) {
        if (out_bytes) *out_bytes = NULL;
        return 0;
    }
    if (out_bytes) *out_bytes = r->stack_window;
    return r->stack_window_len;
}

usize break_crash_record_context_blob(const BreakCrashRecord *r, const u8 **out_bytes) {
    if (!r) {
        if (out_bytes) *out_bytes = NULL;
        return 0;
    }
    if (out_bytes) *out_bytes = r->context_blob;
    return r->context_blob_len;
}

/* ==========================================================================
 *  Record: builder (normal-context writer)
 * ========================================================================== */

struct BreakCrashRecordBuilder {
    int signo;
    int code;
    u64 fault_addr;
    u64 pid;
    u64 tid;
    u64 rip;
    u64 rsp;
    u64 rbp;
    char build_id[65];
    u32 module_count;
    BcModule modules[BREAK_CRASH_MODULE_MAX];
    u8 stack_window[BREAK_CRASH_STACK_WINDOW_MAX];
    usize stack_window_len;
    u8 context_blob[BREAK_CRASH_CONTEXT_BLOB_MAX];
    usize context_blob_len;
};

BreakCrashRecordBuilder *break_crash_record_builder_create(void) {
    BreakCrashRecordBuilder *b = calloc(1, sizeof(*b));
    if (!b) return NULL;
    memcpy(b->build_id, "unknown", sizeof("unknown")); /* includes NUL */
    return b;
}

void break_crash_record_builder_set_signal(BreakCrashRecordBuilder *b, int signo,
                                           int code, u64 fault_addr) {
    if (!b) return;
    b->signo = signo;
    b->code = code;
    b->fault_addr = fault_addr;
}

void break_crash_record_builder_set_process(BreakCrashRecordBuilder *b, u64 pid, u64 tid) {
    if (!b) return;
    b->pid = pid;
    b->tid = tid;
}

void break_crash_record_builder_set_registers(BreakCrashRecordBuilder *b, u64 rip,
                                              u64 rsp, u64 rbp) {
    if (!b) return;
    b->rip = rip;
    b->rsp = rsp;
    b->rbp = rbp;
}

void break_crash_record_builder_set_build_id(BreakCrashRecordBuilder *b, const char *id) {
    if (!b || !id) return;
    usize n = strlen(id);
    if (n < 1 || n > 64) return;
    usize i;
    for (i = 0; i < n; i++) {
        u8 c = (u8)id[i];
        if (!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || c == '-'))
            return; /* invalid id: bounded no-op (void return) */
    }
    memcpy(b->build_id, id, n + 1);
}

bool break_crash_record_builder_add_module(BreakCrashRecordBuilder *b, const char *name,
                                           u64 offset, u64 size) {
    if (!b || !name) return false;
    usize n = strlen(name);
    if (n < 1 || n > 255) return false;
    usize i;
    for (i = 0; i < n; i++) {
        u8 c = (u8)name[i];
        if (c < 0x21 || c > 0x7E || c == '/') return false;
    }
    if (b->module_count >= BREAK_CRASH_MODULE_MAX) return false;
    BcModule *m = &b->modules[b->module_count++];
    m->offset = offset;
    m->size = size;
    memcpy(m->name, name, n + 1);
    return true;
}

void break_crash_record_builder_set_stack_window(BreakCrashRecordBuilder *b,
                                                 const u8 *bytes, usize len) {
    if (!b) return;
    if (!bytes) len = 0;
    if (len > BREAK_CRASH_STACK_WINDOW_MAX) len = BREAK_CRASH_STACK_WINDOW_MAX;
    if (len) memcpy(b->stack_window, bytes, len);
    b->stack_window_len = len;
}

void break_crash_record_builder_set_context_blob(BreakCrashRecordBuilder *b,
                                                 const u8 *bytes, usize len) {
    if (!b) return;
    if (!bytes) len = 0;
    if (len > BREAK_CRASH_CONTEXT_BLOB_MAX) len = BREAK_CRASH_CONTEXT_BLOB_MAX;
    if (len) memcpy(b->context_blob, bytes, len);
    b->context_blob_len = len;
}

/* Pure-memory append helpers (the Task 2 signal-side writer uses the same
 * hand-rolled shapes — no stdio formatting anywhere near the grammar). */
static void bc_put_str(u8 **p, const char *s) {
    usize n = strlen(s);
    memcpy(*p, s, n);
    *p += n;
}

static void bc_put_hex(u8 **p, u64 v, usize width) {
    static const char h[] = "0123456789abcdef";
    usize i;
    for (i = width; i-- > 0;) {
        (*p)[i] = (u8)h[v & 15];
        v >>= 4;
    }
    *p += width;
}

static void bc_put_hexbytes(u8 **p, const u8 *in, usize n) {
    static const char h[] = "0123456789abcdef";
    usize i;
    for (i = 0; i < n; i++) {
        (*p)[2 * i] = (u8)h[in[i] >> 4];
        (*p)[2 * i + 1] = (u8)h[in[i] & 15];
    }
    *p += 2 * n;
}

/* Exact serialized size (≤ 35746 bytes by construction — the 64 KiB cap is
 * unreachable from the builder but enforced at emit regardless). */
typedef struct {
    int signo, code;
    u64 fault_addr, pid, tid, rip, rsp, rbp;
    const char *build_id;
    u64 module_count;
    const BcModule *modules;
    const u8 *stack_window;
    usize stack_window_len;
    const u8 *context_blob;
    usize context_blob_len;
} BcView;

static usize bc_view_size(const BcView *v) {
    usize n = 15;             /* "break-crash-v1\n" */
    n += 7 + 8 + 1;           /* "signo: " hex8 LF */
    n += 6 + 8 + 1;           /* "code: " */
    n += 12 + 16 + 1;         /* "fault_addr: " */
    n += (5 + 16 + 1) * 5;    /* pid/tid/rip/rsp/rbp */
    n += 10 + strlen(v->build_id) + 1;
    u64 i;
    for (i = 0; i < v->module_count; i++) {
        n += 8 + 16 + 1 + 16 + 1 + strlen(v->modules[i].name) + 1;
    }
    n += 13 + (v->stack_window_len ? 1 + 2 * v->stack_window_len : 0) + 1;
    n += 13 + (v->context_blob_len ? 1 + 2 * v->context_blob_len : 0) + 1;
    return n;
}

/* The ONE normal-context writer: the builder's finish and Task 3's record
 * serialize both emit through this (byte-identical output pinned by the
 * golden test; the signal-side writer stays the second, interlocked writer). */
static usize bc_view_emit(const BcView *v, u8 *out, usize capacity) {
    usize need = bc_view_size(v);
    if (capacity < need) return 0;
    if (need > BREAK_CRASH_RECORD_MAX) return 0; /* unreachable by construction */

    u8 *p = out;
    u64 i;
    bc_put_str(&p, "break-crash-v1\n");
    bc_put_str(&p, "signo: ");
    bc_put_hex(&p, (u32)v->signo, 8);
    *p++ = '\n';
    bc_put_str(&p, "code: ");
    bc_put_hex(&p, (u32)v->code, 8);
    *p++ = '\n';
    bc_put_str(&p, "fault_addr: ");
    bc_put_hex(&p, v->fault_addr, 16);
    *p++ = '\n';
    bc_put_str(&p, "pid: ");
    bc_put_hex(&p, v->pid, 16);
    *p++ = '\n';
    bc_put_str(&p, "tid: ");
    bc_put_hex(&p, v->tid, 16);
    *p++ = '\n';
    bc_put_str(&p, "rip: ");
    bc_put_hex(&p, v->rip, 16);
    *p++ = '\n';
    bc_put_str(&p, "rsp: ");
    bc_put_hex(&p, v->rsp, 16);
    *p++ = '\n';
    bc_put_str(&p, "rbp: ");
    bc_put_hex(&p, v->rbp, 16);
    *p++ = '\n';
    bc_put_str(&p, "build-id: ");
    bc_put_str(&p, v->build_id);
    *p++ = '\n';
    for (i = 0; i < v->module_count; i++) {
        bc_put_str(&p, "module: ");
        bc_put_hex(&p, v->modules[i].offset, 16);
        *p++ = ' ';
        bc_put_hex(&p, v->modules[i].size, 16);
        *p++ = ' ';
        bc_put_str(&p, v->modules[i].name);
        *p++ = '\n';
    }
    bc_put_str(&p, "stack-window:");
    if (v->stack_window_len) {
        *p++ = ' ';
        bc_put_hexbytes(&p, v->stack_window, v->stack_window_len);
    }
    *p++ = '\n';
    bc_put_str(&p, "context-blob:");
    if (v->context_blob_len) {
        *p++ = ' ';
        bc_put_hexbytes(&p, v->context_blob, v->context_blob_len);
    }
    *p++ = '\n';
    return (usize)(p - out); /* == need by construction */
}

usize break_crash_record_builder_finish(const BreakCrashRecordBuilder *b, u8 *out,
                                        usize capacity) {
    if (!b || !out) return 0;
    BcView v;
    v.signo = b->signo;
    v.code = b->code;
    v.fault_addr = b->fault_addr;
    v.pid = b->pid;
    v.tid = b->tid;
    v.rip = b->rip;
    v.rsp = b->rsp;
    v.rbp = b->rbp;
    v.build_id = b->build_id;
    v.module_count = b->module_count;
    v.modules = b->modules;
    v.stack_window = b->stack_window;
    v.stack_window_len = b->stack_window_len;
    v.context_blob = b->context_blob;
    v.context_blob_len = b->context_blob_len;
    return bc_view_emit(&v, out, capacity);
}

void break_crash_record_builder_destroy(BreakCrashRecordBuilder *b) {
    free(b);
}

/* ==========================================================================
 *  Redaction + serialization (Task 3)
 * ========================================================================== */

usize break_crash_record_serialize(const BreakCrashRecord *r, u8 *out, usize capacity) {
    if (!r || !out) return 0;
    BcView v;
    v.signo = r->signo;
    v.code = r->code;
    v.fault_addr = r->fault_addr;
    v.pid = r->pid;
    v.tid = r->tid;
    v.rip = r->rip;
    v.rsp = r->rsp;
    v.rbp = r->rbp;
    v.build_id = r->build_id;
    v.module_count = r->module_count;
    v.modules = r->modules;
    v.stack_window = r->stack_window;
    v.stack_window_len = r->stack_window_len;
    v.context_blob = r->context_blob;
    v.context_blob_len = r->context_blob_len;
    return bc_view_emit(&v, out, capacity);
}

/* Basename over BOTH '/' and '\' separators, in place (the NUL-terminated
 * name buffer is fixed-size; basename only ever shortens). A name that ends
 * at a separator has no basename → the "redacted" placeholder (§6 permits
 * remove-or-placeholder; module count/offsets stay aligned). */
static void bc_basename_inplace(char *name) {
    const char *base = name;
    const char *p;
    for (p = name; *p; p++) {
        if (*p == '/' || *p == '\\') base = p + 1;
    }
    if (base == name) return; /* already a basename: idempotent no-op */
    if (!*base) {
        memcpy(name, "redacted", sizeof("redacted")); /* includes NUL */
        return;
    }
    memmove(name, base, strlen(base) + 1);
}

BreakCrashRecord *break_crash_record_redact(const BreakCrashRecord *r) {
    if (!r) return NULL;
    /* Field-level rules per break_crash.h: every field is copied verbatim
     * EXCEPT module names, which basename in place. The transformed record
     * is re-serialized and re-parsed so the result provably satisfies the
     * grammar (fail closed: NULL on anomaly — unreachable for a valid input;
     * OOM also reports as NULL here). */
    BreakCrashRecord *tmp = malloc(sizeof(*tmp));
    if (!tmp) return NULL;
    memcpy(tmp, r, sizeof(*tmp));
    u64 i;
    for (i = 0; i < tmp->module_count; i++) {
        bc_basename_inplace(tmp->modules[i].name);
    }
    u8 *text = malloc(BREAK_CRASH_RECORD_MAX);
    if (!text) {
        free(tmp);
        return NULL;
    }
    usize n = break_crash_record_serialize(tmp, text, BREAK_CRASH_RECORD_MAX);
    free(tmp);
    BreakCrashRecord *out = n ? break_crash_record_parse(text, n) : NULL;
    free(text);
    return out;
}

/* ==========================================================================
 *  Spool
 * ========================================================================== */

enum { BC_CLASS_PENDING = 0, BC_CLASS_SENT = 1, BC_CLASS_DISCARDED = 2 };

/* Bounded listing cap per class dir (retention keeps ≤ 17 transiently;
 * overflow here is corrupt/foreign state → fail closed). */
#define BC_LIST_CAP 4096u

struct BreakCrashSpool {
    char root[PLATFORM_FS_PATH_CAPACITY];
    char pending[PLATFORM_FS_PATH_CAPACITY];
    char sent[PLATFORM_FS_PATH_CAPACITY];
    char discarded[PLATFORM_FS_PATH_CAPACITY];
    char inbox[PLATFORM_FS_PATH_CAPACITY];
    u64 next_id;
};

static const char *bc_class_dir(const BreakCrashSpool *s, int class_) {
    if (class_ == BC_CLASS_PENDING) return s->pending;
    if (class_ == BC_CLASS_SENT) return s->sent;
    if (class_ == BC_CLASS_DISCARDED) return s->discarded;
    return NULL;
}

/* Canonical record name: "<id>.bcr", id ≥ 1, 1..20 digits, no leading zeros. */
static bool bc_name_to_id(const char *name, u64 *out_id) {
    usize n = strlen(name);
    if (n < 5 || n > 24) return false;
    if (memcmp(name + n - 4, ".bcr", 4) != 0) return false;
    usize digits = n - 4;
    if (digits > 1 && name[0] == '0') return false;
    u64 v = 0;
    usize i;
    for (i = 0; i < digits; i++) {
        char c = name[i];
        if (c < '0' || c > '9') return false;
        u64 d = (u64)(c - '0');
        if (v > (UINT64_MAX - d) / 10u) return false;
        v = v * 10u + d;
    }
    if (v == 0) return false;
    *out_id = v;
    return true;
}

static void bc_id_to_name(u64 id, char out[25]) {
    snprintf(out, 25, "%llu.bcr", (unsigned long long)id);
}

static bool bc_join(char *out, usize cap, const char *dir, const char *name) {
    usize dn = strlen(dir);
    usize nn = strlen(name);
    if (dn + 1 + nn + 1 > cap) return false;
    memcpy(out, dir, dn);
    out[dn] = '/';
    memcpy(out + dn + 1, name, nn + 1);
    return true;
}

static int bc_id_cmp(const void *a, const void *b) {
    u64 x = *(const u64 *)a;
    u64 y = *(const u64 *)b;
    return (x > y) - (x < y);
}

/* Canonical ids in a class dir, sorted ascending. false on IO error or a
 * listing over BC_LIST_CAP entries (corrupt/foreign flood — fail closed).
 * Foreign (non-canonical) entries are skipped, never counted. */
static bool bc_list_ids(const char *dir, u64 **out_ids, u32 *out_count) {
    *out_ids = NULL;
    *out_count = 0;
    PlatformDirEntry *entries = malloc(BC_LIST_CAP * sizeof(*entries));
    if (!entries) return false;
    u32 total = 0;
    bool ok = platform_list_dir(dir, entries, BC_LIST_CAP, &total);
    if (!ok || total > BC_LIST_CAP) {
        free(entries);
        return false;
    }
    u64 *ids = malloc((total ? total : 1) * sizeof(*ids));
    if (!ids) {
        free(entries);
        return false;
    }
    u32 count = 0;
    u32 i;
    for (i = 0; i < total; i++) {
        u64 id;
        if (!entries[i].is_dir && bc_name_to_id(entries[i].name, &id)) {
            ids[count++] = id;
        }
    }
    free(entries);
    qsort(ids, count, sizeof(*ids), bc_id_cmp);
    *out_ids = ids;
    *out_count = count;
    return true;
}

/* Best-effort directory fsync after a rename/remove (POSIX; on Win32 there
 * is no userland directory-fsync equivalent — compile-only branch, the
 * platform_fs.h durability precedent). The rename itself already happened:
 * nothing to roll back, so the result is intentionally ignored. */
static void bc_dir_fsync(const char *path) {
#if defined(_WIN32)
    (void)path;
#else
    int fd = open(path, O_RDONLY | O_DIRECTORY);
    if (fd < 0) return;
    (void)fsync(fd);
    (void)close(fd);
#endif
}

/* pending/<id>.meta — the upload retry sidecar (Task 3). */
static bool bc_meta_path(const BreakCrashSpool *s, u64 id, char *out, usize cap) {
    char name[26]; /* ≤20 digits + ".meta" + NUL */
    snprintf(name, sizeof(name), "%llu.meta", (unsigned long long)id);
    return bc_join(out, cap, s->pending, name);
}

/* Attempt count from the sidecar. Absent OR corrupt → 0: retry metadata is
 * local bookkeeping, never a reason to discard crash evidence — a corrupt
 * sidecar is atomically rewritten on the next failed pass (self-heals). */
static u32 bc_meta_read_attempts(const BreakCrashSpool *s, u64 id) {
    char path[PLATFORM_FS_PATH_CAPACITY];
    if (!bc_meta_path(s, id, path, sizeof(path))) return 0;
    u64 size = 0;
    if (!platform_file_size(path, &size)) return 0; /* absent: no failures yet */
    /* the largest valid sidecar is 41 bytes (30 + 10 digits + LF) */
    if (size == 0 || size >= 64) return 0;
    u8 buf[64];
    FILE *fp = fopen(path, "rb");
    if (!fp) return 0;
    usize got = fread(buf, 1, (usize)size, fp);
    fclose(fp);
    if (got != (usize)size) return 0;
    /* canonical: "break-crash-meta-v1\nattempts: <u32 decimal>\n" */
    static const char PREFIX[] = "break-crash-meta-v1\nattempts: ";
    const usize plen = sizeof(PREFIX) - 1; /* 30 */
    if ((usize)size <= plen + 1) return 0; /* need ≥ 1 digit + final LF */
    if (memcmp(buf, PREFIX, plen) != 0) return 0;
    if (buf[size - 1] != '\n') return 0;
    usize digits = (usize)size - plen - 1;
    if (digits > 10) return 0;
    if (digits > 1 && buf[plen] == '0') return 0; /* no leading zeros */
    u64 v = 0;
    usize i;
    for (i = 0; i < digits; i++) {
        u8 c = buf[plen + i];
        if (c < '0' || c > '9') return 0;
        v = v * 10u + (u64)(c - '0');
    }
    if (v > 0xffffffffull) return 0;
    /* ≥ ATTEMPTS_MAX is foreign/corrupt: the writer only ever emits 1..4 (the
     * 5th failure discards the record instead), so a resting value ≥ 5 can
     * never be spool-authored. Reading it raw would let a planted u32-max
     * wrap the increment to 0 and grant unbounded retries — clamp to 0; the
     * next failed pass rewrites the sidecar (self-heals). */
    if (v >= BREAK_CRASH_UPLOAD_ATTEMPTS_MAX) return 0;
    return (u32)v;
}

/* Atomically rewrites the sidecar (PlatformAtomicWriter: tmp+fsync+rename —
 * a crash mid-pass leaves the OLD or the NEW count, never a torn file). */
static bool bc_meta_write_attempts(BreakCrashSpool *s, u64 id, u32 attempts) {
    char path[PLATFORM_FS_PATH_CAPACITY];
    if (!bc_meta_path(s, id, path, sizeof(path))) return false;
    char text[48];
    int n = snprintf(text, sizeof(text), "break-crash-meta-v1\nattempts: %llu\n",
                     (unsigned long long)attempts);
    if (n <= 0 || (usize)n >= sizeof(text)) return false;
    PlatformAtomicWriter *w = platform_atomic_writer_open(path);
    if (!w) return false;
    bool ok = platform_atomic_writer_write(w, text, (usize)n);
    /* commit ALWAYS runs: it consumes the writer on every outcome (closes the
     * fd, unlinks the tmp on failure, frees the handle — platform_fs.c:361) —
     * short-circuiting on a failed write would leak both. */
    ok = platform_atomic_writer_commit(w) && ok;
    return ok;
}

/* The sidecar's lifetime is bound to the record's stay in pending/: every
 * path that removes a record from pending removes its sidecar (best-effort —
 * a leftover is foreign-name residue, never counted, never shipped). */
static void bc_meta_remove(const BreakCrashSpool *s, u64 id) {
    char path[PLATFORM_FS_PATH_CAPACITY];
    if (!bc_meta_path(s, id, path, sizeof(path))) return;
    if (remove(path) == 0) bc_dir_fsync(s->pending);
}

/* Retention: pending/sent overflow moves the OLDEST (lowest id) into
 * discarded; discarded overflow DELETES its oldest. Janitorial best-effort:
 * the triggering operation's own effect has already committed, and the
 * counts stay observable via break_crash_spool_count either way. */
static void bc_enforce_retention(BreakCrashSpool *s, int class_) {
    const char *dir = bc_class_dir(s, class_);
    if (!dir) return;
    for (;;) {
        u64 *ids = NULL;
        u32 count = 0;
        if (!bc_list_ids(dir, &ids, &count)) return;
        if (count <= BREAK_CRASH_SPOOL_KEEP) {
            free(ids);
            return;
        }
        u64 victim = ids[0];
        free(ids);
        char name[25];
        bc_id_to_name(victim, name);
        char src[PLATFORM_FS_PATH_CAPACITY];
        if (!bc_join(src, sizeof(src), dir, name)) return;
        if (class_ == BC_CLASS_DISCARDED) {
            if (remove(src) != 0) return;
            bc_dir_fsync(dir);
        } else {
            char dst[PLATFORM_FS_PATH_CAPACITY];
            if (!bc_join(dst, sizeof(dst), s->discarded, name)) return;
            if (rename(src, dst) != 0) return;
            bc_dir_fsync(dir);
            bc_dir_fsync(s->discarded);
            if (class_ == BC_CLASS_PENDING) bc_meta_remove(s, victim);
            bc_enforce_retention(s, BC_CLASS_DISCARDED);
        }
    }
}

/* Zero-byte atomic commit over the inbox (rename-over replaces any existing
 * content; tmp+fsync+rename+dir-fsync is the house durability order). */
static bool bc_reset_inbox(BreakCrashSpool *s) {
    PlatformAtomicWriter *w = platform_atomic_writer_open(s->inbox);
    if (!w) return false;
    return platform_atomic_writer_commit(w); /* consumes the writer */
}

/* Non-empty inbox recovery (the crash-spool acceptance path): valid bytes →
 * pending/<next-id>.bcr via the atomic writer + inbox reset; anything else
 * (torn/garbage/oversize/unreadable) → rename whole into discarded
 * (forensic bytes kept) + inbox recreated. Failures fail the open with the
 * inbox left recoverable. AT-LEAST-ONCE (break_crash.h documents the
 * duplicate window). */
static bool bc_recover_inbox(BreakCrashSpool *s) {
    u64 size = 0;
    if (!platform_file_size(s->inbox, &size)) return true; /* missing: caller creates */
    if (size == 0) return true;

    u8 *buf = NULL;
    bool valid = false;
    if (size <= BREAK_CRASH_RECORD_MAX) {
        buf = malloc((usize)size);
        if (!buf) return false;
        FILE *fp = fopen(s->inbox, "rb");
        usize got = 0;
        if (fp) {
            got = fread(buf, 1, (usize)size, fp);
            fclose(fp);
        }
        if (fp && got == (usize)size) {
            BreakCrashRecord *r = break_crash_record_parse(buf, (usize)size);
            valid = (r != NULL);
            break_crash_record_destroy(r);
        }
    }

    char name[25];
    bc_id_to_name(s->next_id, name);
    char dst[PLATFORM_FS_PATH_CAPACITY];

    if (valid) {
        if (!bc_join(dst, sizeof(dst), s->pending, name)) {
            free(buf);
            return false;
        }
        PlatformAtomicWriter *w = platform_atomic_writer_open(dst);
        if (!w) {
            free(buf);
            return false;
        }
        bool ok = platform_atomic_writer_write(w, buf, (usize)size);
        /* commit ALWAYS runs (consumes/cleans up the writer — see the
         * bc_meta_write_attempts note) */
        ok = platform_atomic_writer_commit(w) && ok;
        free(buf);
        if (!ok) return false; /* inbox left intact for the next open */
        s->next_id++;
        if (!bc_reset_inbox(s)) return false; /* record safe in pending */
        bc_enforce_retention(s, BC_CLASS_PENDING);
        return true;
    }

    free(buf);
    if (!bc_join(dst, sizeof(dst), s->discarded, name)) return false;
    if (rename(s->inbox, dst) != 0) return false;
    bc_dir_fsync(s->root);
    bc_dir_fsync(s->discarded);
    s->next_id++;
    if (!bc_reset_inbox(s)) return false;
    bc_enforce_retention(s, BC_CLASS_DISCARDED);
    return true;
}

BreakCrashSpool *break_crash_spool_open(const char *root_path) {
    if (!root_path) return NULL;
    usize n = strlen(root_path);
    while (n > 1 && root_path[n - 1] == '/') n--; /* strip trailing '/' */
    if (n == 0) return NULL;
    /* room for "/discarded" + "/" + max canonical name + NUL inside the PAL
     * path capacity (the longest path the spool ever builds) */
    if (n + 10 + 1 + 24 + 1 > PLATFORM_FS_PATH_CAPACITY) return NULL;

    BreakCrashSpool *s = calloc(1, sizeof(*s));
    if (!s) return NULL;
    memcpy(s->root, root_path, n);
    s->root[n] = '\0';
    memcpy(s->pending, s->root, n);
    memcpy(s->pending + n, "/pending", sizeof("/pending"));
    memcpy(s->sent, s->root, n);
    memcpy(s->sent + n, "/sent", sizeof("/sent"));
    memcpy(s->discarded, s->root, n);
    memcpy(s->discarded + n, "/discarded", sizeof("/discarded"));
    memcpy(s->inbox, s->root, n);
    memcpy(s->inbox + n, "/crash.inbox", sizeof("/crash.inbox"));

    if (!platform_mkdir(s->root)) goto fail;
    if (!platform_mkdir(s->pending)) goto fail;
    if (!platform_mkdir(s->sent)) goto fail;
    if (!platform_mkdir(s->discarded)) goto fail;

    /* next id = max existing canonical id across all classes + 1 */
    s->next_id = 1;
    {
        int c;
        for (c = 0; c < 3; c++) {
            u64 *ids = NULL;
            u32 count = 0;
            if (!bc_list_ids(bc_class_dir(s, c), &ids, &count)) goto fail;
            if (count) {
                if (ids[count - 1] == UINT64_MAX) {
                    free(ids);
                    goto fail; /* id space exhausted (absurd state) */
                }
                if (ids[count - 1] >= s->next_id) s->next_id = ids[count - 1] + 1;
            }
            free(ids);
        }
    }

    if (!bc_recover_inbox(s)) goto fail;

    /* ensure the inbox exists (fresh layout / external deletion) */
    {
        u64 sz = 0;
        if (!platform_file_size(s->inbox, &sz) && !bc_reset_inbox(s)) goto fail;
    }
    return s;

fail:
    free(s);
    return NULL;
}

void break_crash_spool_destroy(BreakCrashSpool *s) {
    free(s);
}

u64 break_crash_spool_count(const BreakCrashSpool *s, int class_) {
    if (!s) return 0;
    const char *dir = bc_class_dir(s, class_);
    if (!dir) return 0;
    u64 *ids = NULL;
    u32 count = 0;
    if (!bc_list_ids(dir, &ids, &count)) return 0;
    free(ids);
    return count;
}

bool break_crash_spool_put_pending(BreakCrashSpool *s, const void *record_bytes,
                                   usize len) {
    if (!s) return false;
    if (!record_bytes || len == 0) return false;
    if (len > BREAK_CRASH_RECORD_MAX) return false;
    /* pending/ holds parseable records only (fail closed at the gate) */
    BreakCrashRecord *r = break_crash_record_parse(record_bytes, len);
    if (!r) return false;
    break_crash_record_destroy(r);

    char path[PLATFORM_FS_PATH_CAPACITY];
    for (;;) {
        if (s->next_id == 0) return false; /* id space wrapped (UINT64_MAX) */
        char name[25];
        bc_id_to_name(s->next_id, name);
        if (!bc_join(path, sizeof(path), s->pending, name)) return false;
        u64 existing = 0;
        if (!platform_file_size(path, &existing)) break; /* free slot */
        s->next_id++; /* foreign collision: skip, never overwrite */
    }
    PlatformAtomicWriter *w = platform_atomic_writer_open(path);
    if (!w) return false;
    bool ok = platform_atomic_writer_write(w, record_bytes, len);
    /* commit ALWAYS runs (consumes/cleans up the writer — see the
     * bc_meta_write_attempts note) */
    ok = platform_atomic_writer_commit(w) && ok;
    if (!ok) return false; /* the id stays unconsumed (no target was created) */
    s->next_id++;
    bc_enforce_retention(s, BC_CLASS_PENDING);
    return true;
}

/* Read one pending record by canonical id (the index-based public read and
 * the Task 3 upload pass both resolve through this). */
static bool bc_read_pending_id(const BreakCrashSpool *s, u64 id,
                               u8 **out_buf, u64 *out_len) {
    char name[25];
    bc_id_to_name(id, name);
    char path[PLATFORM_FS_PATH_CAPACITY];
    if (!bc_join(path, sizeof(path), s->pending, name)) return false;
    u64 size = 0;
    if (!platform_file_size(path, &size)) return false;
    if (size > BREAK_CRASH_RECORD_MAX) return false;
    u8 *buf = malloc(size ? (usize)size : 1); /* always a freeable pointer */
    if (!buf) return false;
    usize got = 0;
    FILE *fp = fopen(path, "rb");
    if (fp) {
        if (size) got = fread(buf, 1, (usize)size, fp);
        fclose(fp);
    }
    if (!fp || got != (usize)size) { /* missing/short read (concurrent edit) */
        free(buf);
        return false;
    }
    *out_buf = buf;
    *out_len = size;
    return true;
}

bool break_crash_spool_read_pending(const BreakCrashSpool *s, u64 index,
                                    u8 **out_buf, u64 *out_len) {
    if (!s || !out_buf || !out_len) return false;
    *out_buf = NULL;
    *out_len = 0;
    u64 *ids = NULL;
    u32 count = 0;
    if (!bc_list_ids(s->pending, &ids, &count)) return false;
    if (index >= count) {
        free(ids);
        return false;
    }
    u64 id = ids[count - 1 - index]; /* newest-first (documented) */
    free(ids);
    return bc_read_pending_id(s, id, out_buf, out_len);
}

static bool bc_mark_id(BreakCrashSpool *s, u64 id, int target_class) {
    const char *target_dir = bc_class_dir(s, target_class);
    if (!target_dir) return false;
    char name[25];
    bc_id_to_name(id, name);
    char src[PLATFORM_FS_PATH_CAPACITY];
    char dst[PLATFORM_FS_PATH_CAPACITY];
    if (!bc_join(src, sizeof(src), s->pending, name)) return false;
    if (!bc_join(dst, sizeof(dst), target_dir, name)) return false;
    if (rename(src, dst) != 0) return false; /* same filesystem by construction */
    bc_dir_fsync(s->pending);
    bc_dir_fsync(target_dir);
    bc_meta_remove(s, id); /* retry state ends with the stay in pending/ */
    bc_enforce_retention(s, target_class);
    return true;
}

static bool bc_mark(BreakCrashSpool *s, u64 index, int target_class) {
    if (!s) return false;
    u64 *ids = NULL;
    u32 count = 0;
    if (!bc_list_ids(s->pending, &ids, &count)) return false;
    if (index >= count) {
        free(ids);
        return false;
    }
    u64 id = ids[count - 1 - index]; /* newest-first, same as read */
    free(ids);
    return bc_mark_id(s, id, target_class);
}

bool break_crash_spool_mark_sent(BreakCrashSpool *s, u64 index) {
    return bc_mark(s, index, BC_CLASS_SENT);
}

bool break_crash_spool_mark_discarded(BreakCrashSpool *s, u64 index) {
    return bc_mark(s, index, BC_CLASS_DISCARDED);
}

/* ==========================================================================
 *  Upload seam (Task 3) — caller-supplied transport, persisted retry/discard
 * ========================================================================== */

u32 break_crash_spool_upload_pending(BreakCrashSpool *s, BreakCrashUploadFn up,
                                     void *user) {
    if (!s || !up) return 0; /* INVALID-style no-op */
    u64 *ids = NULL;
    u32 count = 0;
    if (!bc_list_ids(s->pending, &ids, &count)) return 0;
    u8 *text = malloc(BREAK_CRASH_RECORD_MAX); /* serialize buffer, per pass */
    if (!text) {
        free(ids);
        return 0;
    }
    u32 sent = 0;
    u32 k;
    for (k = 0; k < count; k++) {
        u64 id = ids[count - 1 - k]; /* newest-first over the id snapshot */
        u8 *buf = NULL;
        u64 len = 0;
        if (!bc_read_pending_id(s, id, &buf, &len)) continue; /* vanished/IO: skip */
        BreakCrashRecord *r = break_crash_record_parse(buf, (usize)len);
        free(buf);
        if (!r) {
            /* pending/ holds parseable records by construction; a foreign
             * unparseable entry fails closed into discarded/, never ships */
            (void)bc_mark_id(s, id, BC_CLASS_DISCARDED);
            continue;
        }
        BreakCrashRecord *red = break_crash_record_redact(r);
        break_crash_record_destroy(r);
        usize n = red ? break_crash_record_serialize(red, text, BREAK_CRASH_RECORD_MAX)
                      : 0;
        break_crash_record_destroy(red);
        if (!n) continue; /* allocation failure in practice: never ship
                           * unredactable bytes; the record stays pending */
        if (up(user, text, n)) {
            if (bc_mark_id(s, id, BC_CLASS_SENT)) sent++;
            /* a failed mark leaves the record pending: upload is
             * at-least-once, the next pass re-ships (server dedups) */
            continue;
        }
        u32 attempts = bc_meta_read_attempts(s, id) + 1;
        if (attempts >= BREAK_CRASH_UPLOAD_ATTEMPTS_MAX) {
            (void)bc_mark_id(s, id, BC_CLASS_DISCARDED); /* removes the sidecar */
        } else {
            (void)bc_meta_write_attempts(s, id, attempts); /* best-effort, documented */
        }
    }
    free(text);
    free(ids);
    return sent;
}

/* ==========================================================================
 *  Signal capture (Task 2) — POSIX; documented compile-time stub on _WIN32.
 *
 *  Everything the handler touches is pre-staged at install into static
 *  storage (no allocation anywhere near the handler). The handler's full
 *  call set is the whitelist table in break_crash.h; the bs_* helpers are
 *  hand-rolled pure-memory (no libc) so the reviewer can line-verify.
 * ========================================================================== */

#if !defined(_WIN32)

#define BC_CRASH_SIGNAL_COUNT 5
static const int BC_CRASH_SIGNALS[BC_CRASH_SIGNAL_COUNT] = {
    SIGSEGV, SIGABRT, SIGILL, SIGFPE, SIGBUS
};

static struct {
    int installed;      /* normal-context flag (install/uninstall not thread-safe) */
    int inbox_fd;       /* pre-opened crash.inbox fd, valid while installed */
    char build_id[65];  /* grammar-validated at capture */
    u32 module_count;
    BcModule modules[BREAK_CRASH_MODULE_MAX];
    u8 blob[BREAK_CRASH_CONTEXT_BLOB_MAX];
    usize blob_len;
    u8 record_buf[BREAK_CRASH_RECORD_MAX];
    struct sigaction old_act[BC_CRASH_SIGNAL_COUNT];
    /* Privacy zone (privacy-by-omission, capture-side enforcement): the
     * argv/env strings block sits at the TOP of the initial [stack] mapping;
     * a shallow main-thread crash's [rsp, rsp+4KiB) window would otherwise
     * hex-dump cmdline/env (usernames, HOME, secrets) into the record —
     * the threat model says those are NEVER captured. zone_lo = lowest
     * argv/env string address; the handler clamps the window below it. */
    u64 stack_lo;       /* [stack] mapping bounds (0/0 when absent) */
    u64 stack_hi;
    u64 zone_lo;        /* UINT64_MAX when no argv/env strings were found */
} g_crash = {.inbox_fd = -1};

/* One-shot capture guard, a separate static for ATOMIC_FLAG_INIT. */
static atomic_flag g_crash_once = ATOMIC_FLAG_INIT;

/* ---- install-time capture (normal context) ------------------------------- */

/* Basename validated against the module-name grammar (1..255 chars of
 * 0x21-0x7E minus '/'). */
static bool bc_capture_name_ok(const char *name) {
    usize n = strlen(name);
    if (n < 1 || n > 255) return false;
    usize i;
    for (i = 0; i < n; i++) {
        u8 c = (u8)name[i];
        if (c < 0x21 || c > 0x7E || c == '/') return false;
    }
    return true;
}

/* Flushes the pending maps group (bias/size/path) into the module list. */
static void bc_capture_flush(u64 bias, u64 size, const char *path) {
    if (g_crash.module_count >= BREAK_CRASH_MODULE_MAX) return;
    if (!path[0] || size == 0) return;
    const char *slash = strrchr(path, '/');
    const char *name = slash ? slash + 1 : path;
    if (!bc_capture_name_ok(name)) return;
    BcModule *m = &g_crash.modules[g_crash.module_count++];
    m->offset = bias;
    m->size = size;
    strcpy(m->name, name); /* bounded by bc_capture_name_ok (≤255 + NUL) */
}

/* Parses /proc/self/maps NOW. Keeps ≤ 64 file-backed entries in capture
 * order; contiguous same-path mappings merge into one entry whose
 * load-offset is (first-start − first-file-offset) — the ELF load bias — and
 * whose size spans the group. Non-'/' pathnames ([stack], [vdso], anon) and
 * unnameable basenames are skipped. */
static void bc_capture_modules(void) {
    g_crash.module_count = 0;
    FILE *fp = fopen("/proc/self/maps", "r");
    if (!fp) return;

    char line[2048];
    char cur_path[1024];
    u64 cur_start = 0, cur_end = 0, cur_bias = 0;
    cur_path[0] = '\0';
    while (fgets(line, sizeof(line), fp)) {
        const char *p = line;
        char *endp = NULL;
        u64 start = strtoull(p, &endp, 16);
        if (endp == p || *endp != '-') continue;
        u64 end = strtoull(endp + 1, &endp, 16);
        if (end <= start) continue;
        p = endp;
        /* skip the perms field, then parse the file offset */
        while (*p == ' ') p++;
        while (*p && *p != ' ') p++;
        while (*p == ' ') p++;
        u64 off = strtoull(p, &endp, 16);
        if (endp == p) continue;
        p = endp;
        /* skip the dev and inode fields */
        int f;
        for (f = 0; f < 2; f++) {
            while (*p == ' ') p++;
            while (*p && *p != ' ') p++;
        }
        while (*p == ' ') p++;
        /* path runs to EOL and may contain spaces; drop the EOL and a
         * trailing " (deleted)" marker */
        usize plen = strcspn(p, "\r\n");
        while (plen > 0 && p[plen - 1] == ' ') plen--;
        static const char DELETED[] = " (deleted)";
        if (plen >= sizeof(DELETED) - 1 &&
            memcmp(p + plen - (sizeof(DELETED) - 1), DELETED, sizeof(DELETED) - 1) == 0) {
            plen -= sizeof(DELETED) - 1;
        }

        /* the main thread's stack mapping bounds feed the privacy-zone
         * clamp (it is the only mapping that can hold argv/env strings) */
        if (plen == 6 && memcmp(p, "[stack]", 6) == 0) {
            g_crash.stack_lo = start;
            g_crash.stack_hi = end;
        }

        if (plen > 0 && p[0] == '/' && plen < sizeof(cur_path) &&
            plen == strlen(cur_path) && memcmp(p, cur_path, plen) == 0 &&
            start == cur_end) {
            cur_end = end; /* contiguous same-path mapping: extend the group */
            continue;
        }
        bc_capture_flush(cur_bias, cur_end - cur_start, cur_path);
        if (plen > 0 && p[0] == '/' && plen < sizeof(cur_path)) {
            memcpy(cur_path, p, plen);
            cur_path[plen] = '\0';
            cur_start = start;
            cur_end = end;
            cur_bias = start - off;
        } else {
            cur_path[0] = '\0';
            cur_start = cur_end = cur_bias = 0;
        }
    }
    bc_capture_flush(cur_bias, cur_end - cur_start, cur_path);
    fclose(fp);
}

/* Privacy zone = the argv/env strings block at the top of the initial
 * stack: zone_lo = the lowest string address among argv[0] (glibc's
 * program_invocation_name) and every environ[] entry. Candidates outside
 * the [stack] mapping (when its bounds are known) are ignored — setenv()
 * additions live on the heap and are never in the stack window anyway.
 * UINT64_MAX when nothing was found (no clamp then; documented). Normal
 * context (install); pure scans over live libc-owned pointers. */
static void bc_capture_privacy_zone(void) {
    g_crash.zone_lo = ~0ull;
    u64 lo = g_crash.stack_lo, hi = g_crash.stack_hi;
#if defined(__GLIBC__)
    extern char *program_invocation_name; /* argv[0] string on the stack top */
    if (program_invocation_name) {
        u64 a = (u64)(uintptr_t)program_invocation_name;
        if ((!lo && !hi) || (a >= lo && a < hi)) {
            if (a < g_crash.zone_lo) g_crash.zone_lo = a;
        }
    }
#endif
    extern char **environ;
    if (environ) {
        char **e = environ;
        for (; *e; e++) {
            u64 a = (u64)(uintptr_t)*e;
            if ((lo || hi) && !(a >= lo && a < hi)) continue;
            if (a < g_crash.zone_lo) g_crash.zone_lo = a;
        }
    }
}

/* Build id = the "+" suffix of break_version_string(), validated against the
 * grammar charset (≤ 64 chars of [0-9a-z-]); "unknown" otherwise. */
static void bc_capture_build_id(void) {
    const char *id = "unknown";
    const char *v = break_version_string(); /* static storage, never NULL */
    const char *plus = v ? strchr(v, '+') : NULL;
    if (plus && plus[1]) {
        usize n = strlen(plus + 1);
        if (n <= 64) {
            bool ok = true;
            usize i;
            for (i = 0; i < n; i++) {
                char c = plus[1 + i];
                if (!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || c == '-')) {
                    ok = false;
                    break;
                }
            }
            if (ok) id = plus + 1;
        }
    }
    usize n = strlen(id);
    memcpy(g_crash.build_id, id, n + 1);
}

/* ---- signal-side writer (handler context; whitelist only) ----------------- */

/* Hand-rolled pure-memory helpers — the ONLY formatting the handler does.
 * Byte-identical output to the builder (one grammar, two writers, pinned by
 * the fork tests through the Task 1 parser). */
static void bs_put(u8 **p, const char *s) {
    while (*s) {
        **p = (u8)*s;
        (*p)++;
        s++;
    }
}

static void bs_hex(u8 **p, u64 v, usize width) {
    static const char h[] = "0123456789abcdef";
    usize i;
    for (i = width; i-- > 0;) {
        (*p)[i] = (u8)h[v & 15];
        v >>= 4;
    }
    *p += width;
}

static void bs_hexbytes(u8 **p, const u8 *in, usize n) {
    static const char h[] = "0123456789abcdef";
    usize i;
    for (i = 0; i < n; i++) {
        (*p)[2 * i] = (u8)h[in[i] >> 4];
        (*p)[2 * i + 1] = (u8)h[in[i] & 15];
    }
    *p += 2 * n;
}

/* Restore-and-die tail: default action back, the signal unblocked (it is
 * blocked inside its own handler — no SA_NODEFER), then re-raised so the
 * process dies with the original semantics (core dump, WIFSIGNALED). The
 * _exit backstop covers the blocked/ignored edge; it is unreachable in the
 * normal flow. */
static void bc_crash_die(int sig) {
    (void)signal(sig, SIG_DFL);
    sigset_t set;
    (void)sigemptyset(&set);
    (void)sigaddset(&set, sig);
    (void)sigprocmask(SIG_UNBLOCK, &set, (void *)0);
    (void)raise(sig);
    _exit(128 + sig);
}

/* Kernel thread id for the record. Linux: gettid; macOS: syscall(2) is
 * deprecated, pthread_threadid_np gives the same per-thread 64-bit id. */
static u64 bc_thread_id(void) {
#if defined(__linux__)
    return (u64)(unsigned long)syscall(SYS_gettid);
#elif defined(__APPLE__)
    uint64_t tid = 0;
    (void)pthread_threadid_np((pthread_t)0, &tid);
    return (u64)tid;
#else
    return 0;
#endif
}

static void bc_crash_handler(int sig, siginfo_t *info, void *uctx) {
    /* One-shot guard: any re-entry (nested signal or a racing second
     * crashing thread) goes straight to the die tail — no nested formatting,
     * exactly one captured crash per process run. */
    if (atomic_flag_test_and_set(&g_crash_once)) bc_crash_die(sig);

    u64 rip = 0, rsp = 0, rbp = 0;
#if defined(__x86_64__) && defined(__linux__)
    if (uctx) {
        const ucontext_t *uc = (const ucontext_t *)uctx;
        rip = (u64)uc->uc_mcontext.gregs[REG_RIP];
        rsp = (u64)uc->uc_mcontext.gregs[REG_RSP];
        rbp = (u64)uc->uc_mcontext.gregs[REG_RBP];
    }
#else
    (void)uctx; /* other architectures: registers are zero (documented) */
#endif
    u64 fault = info ? (u64)(uintptr_t)info->si_addr : 0;
    u32 code = info ? (u32)info->si_code : 0;

    /* Stack window [rsp, rsp+4KiB): the handler executes on the faulting
     * thread's stack, so the window covers live frames. Skip it when a
     * SIGSEGV's fault address lies within ±8 KiB of rsp (stack-overflow
     * signature — the guard region is near) or rsp is zero. Then clamp the
     * window below the argv/env privacy zone: a shallow main-thread crash
     * must not hex-dump cmdline/env strings (usernames, HOME, secrets)
     * into the record — privacy by omission, enforced at capture. */
    const u8 *window = (const u8 *)0;
    usize window_len = 0;
    if (rsp != 0) {
        bool skip = false;
        if (sig == SIGSEGV) {
            u64 lo = rsp > 8192u ? rsp - 8192u : 0u;
            u64 hi = rsp < ~0ull - 8192u ? rsp + 8192u : ~0ull;
            if (fault >= lo && fault <= hi) skip = true;
        }
        if (!skip) {
            u64 wend = rsp < ~0ull - BREAK_CRASH_STACK_WINDOW_MAX
                           ? rsp + BREAK_CRASH_STACK_WINDOW_MAX
                           : ~0ull;
            if (rsp >= g_crash.zone_lo) {
                wend = rsp; /* crashing inside the argv/env zone: no window */
            } else if (wend > g_crash.zone_lo) {
                wend = g_crash.zone_lo;
            }
            window = (const u8 *)(uintptr_t)rsp;
            window_len = (usize)(wend - rsp);
        }
    }

    /* Format into the preallocated buffer. The maximal content (64 modules
     * × 255-char names + 4 KiB window + 4 KiB blob) is 35746 bytes — the
     * 64 KiB cap is unreachable by construction, same argument as the
     * builder's. */
    u8 *p = g_crash.record_buf;
    bs_put(&p, "break-crash-v1\n");
    bs_put(&p, "signo: ");
    bs_hex(&p, (u64)(u32)sig, 8);
    *p++ = '\n';
    bs_put(&p, "code: ");
    bs_hex(&p, (u64)code, 8);
    *p++ = '\n';
    bs_put(&p, "fault_addr: ");
    bs_hex(&p, fault, 16);
    *p++ = '\n';
    bs_put(&p, "pid: ");
    bs_hex(&p, (u64)(unsigned long)getpid(), 16);
    *p++ = '\n';
    bs_put(&p, "tid: ");
    bs_hex(&p, bc_thread_id(), 16);
    *p++ = '\n';
    bs_put(&p, "rip: ");
    bs_hex(&p, rip, 16);
    *p++ = '\n';
    bs_put(&p, "rsp: ");
    bs_hex(&p, rsp, 16);
    *p++ = '\n';
    bs_put(&p, "rbp: ");
    bs_hex(&p, rbp, 16);
    *p++ = '\n';
    bs_put(&p, "build-id: ");
    bs_put(&p, g_crash.build_id);
    *p++ = '\n';
    u32 i;
    for (i = 0; i < g_crash.module_count; i++) {
        bs_put(&p, "module: ");
        bs_hex(&p, g_crash.modules[i].offset, 16);
        *p++ = ' ';
        bs_hex(&p, g_crash.modules[i].size, 16);
        *p++ = ' ';
        bs_put(&p, g_crash.modules[i].name);
        *p++ = '\n';
    }
    bs_put(&p, "stack-window:");
    if (window_len) {
        *p++ = ' ';
        bs_hexbytes(&p, window, window_len);
    }
    *p++ = '\n';
    bs_put(&p, "context-blob:");
    if (g_crash.blob_len) {
        *p++ = ' ';
        bs_hexbytes(&p, g_crash.blob, g_crash.blob_len);
    }
    *p++ = '\n';

    /* Flush to the pre-opened inbox (best-effort: any IO failure still dies
     * true; a torn inbox is quarantined by the next open — fail closed). */
    (void)lseek(g_crash.inbox_fd, 0, SEEK_SET);
    const u8 *q = g_crash.record_buf;
    usize left = (usize)(p - g_crash.record_buf);
    while (left > 0) {
        ssize_t w = write(g_crash.inbox_fd, q, left);
        if (w <= 0) break;
        q += (usize)w;
        left -= (usize)w;
    }
    (void)fsync(g_crash.inbox_fd);

    bc_crash_die(sig);
}

/* ---- public install/uninstall (normal context; not thread-safe) ----------- */

bool break_crash_install(const BreakCrashConfig *config) {
    if (!config || !config->spool_root || !config->spool_root[0]) return false;
    if (g_crash.installed) return false; /* once per process while installed */

    /* Pre-stage everything BEFORE any handler can run. */
    bc_capture_modules();
    bc_capture_privacy_zone();
    bc_capture_build_id();
    g_crash.blob_len = 0;

    /* Spool open/close pass: creates the layout AND recovers a previous
     * run's crash.inbox into pending/ (the crash-spool acceptance path),
     * leaving an empty inbox behind. */
    BreakCrashSpool *s = break_crash_spool_open(config->spool_root);
    if (!s) return false;
    break_crash_spool_destroy(s);

    /* Normalize the root (strip trailing '/') like the spool, then open and
     * HOLD the inbox fd (no O_TRUNC: the file is already empty; a foreign
     * tail would fail the next open's parse and be quarantined — fail
     * closed). */
    const char *root = config->spool_root;
    usize rn = strlen(root);
    while (rn > 1 && root[rn - 1] == '/') rn--;
    char rootbuf[PLATFORM_FS_PATH_CAPACITY];
    if (rn + 1 > sizeof(rootbuf)) return false;
    memcpy(rootbuf, root, rn);
    rootbuf[rn] = '\0';
    char inbox[PLATFORM_FS_PATH_CAPACITY];
    if (!bc_join(inbox, sizeof(inbox), rootbuf, "crash.inbox")) return false;
    int fd = open(inbox, O_WRONLY | O_CREAT | O_CLOEXEC, 0600);
    if (fd < 0) return false;

    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_sigaction = bc_crash_handler;
    sa.sa_flags = SA_SIGINFO; /* no SA_NODEFER, no SA_ONSTACK (documented) */
    (void)sigfillset(&sa.sa_mask);
    struct sigaction old[BC_CRASH_SIGNAL_COUNT];
    int k;
    for (k = 0; k < BC_CRASH_SIGNAL_COUNT; k++) {
        if (sigaction(BC_CRASH_SIGNALS[k], &sa, &old[k]) != 0) {
            while (--k >= 0) (void)sigaction(BC_CRASH_SIGNALS[k], &old[k], (void *)0);
            (void)close(fd);
            return false;
        }
    }
    memcpy(g_crash.old_act, old, sizeof(old));
    g_crash.inbox_fd = fd;
    atomic_flag_clear(&g_crash_once);
    g_crash.installed = 1;
    return true;
}

bool break_crash_is_installed(void) {
    return g_crash.installed != 0;
}

void break_crash_set_context_blob(const void *data, usize len) {
    /* Pre-crash only (documented): no locking; a crash racing a publish may
     * capture a torn blob. The app pre-redacts the contents. */
    if (!data) {
        g_crash.blob_len = 0;
        return;
    }
    if (len > BREAK_CRASH_CONTEXT_BLOB_MAX) len = BREAK_CRASH_CONTEXT_BLOB_MAX;
    if (len) memcpy(g_crash.blob, data, len);
    g_crash.blob_len = len;
}

void break_crash_uninstall(void) {
    if (!g_crash.installed) return;
    int k;
    for (k = 0; k < BC_CRASH_SIGNAL_COUNT; k++) {
        (void)sigaction(BC_CRASH_SIGNALS[k], &g_crash.old_act[k], (void *)0);
    }
    (void)close(g_crash.inbox_fd);
    g_crash.inbox_fd = -1;
    g_crash.installed = 0;
}

#else /* _WIN32: documented compile-time stub (no SEH/VEH this phase) */

bool break_crash_install(const BreakCrashConfig *config) {
    (void)config;
    return false;
}

bool break_crash_is_installed(void) {
    return false;
}

void break_crash_set_context_blob(const void *data, usize len) {
    (void)data;
    (void)len;
}

void break_crash_uninstall(void) {
}

#endif
