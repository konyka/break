/* break_crash — Stage 5 Phase C Task 1 implementation: the canonical crash
 * record ("break-crash-v1") + the bounded on-disk spool. The grammar and
 * every behavioral contract are documented in break_crash.h; the parse
 * discipline mirrors the Phase A manifest parser (break_update.c): ASCII
 * subset + LF only, fixed key order, fixed-width lowercase hex, two passes
 * (validate everything BEFORE filling — allocation size here is a fixed
 * struct, never attacker-derived), NULL = the only oracle.
 *
 * Signal capture (Task 2) and redaction/upload (Task 3) are deliberately
 * absent. Zero external dependencies: the write-side PAL
 * (platform_fs.h) is consumed header-only and resolved at the consumer's
 * final link (the test_break_update precedent). */

#if !defined(_WIN32)
/* glibc under -std=c11 (__STRICT_ANSI__) hides open(O_DIRECTORY)/fsync
 * without a feature test macro (the platform_fs.c precedent). */
#define _DEFAULT_SOURCE
#endif

#include <crash/break_crash.h>

#include <platform/platform_fs.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if !defined(_WIN32)
#include <fcntl.h>
#include <unistd.h>
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
 * unreachable from the builder but enforced at finish regardless). */
static usize bc_record_size(const BreakCrashRecordBuilder *b) {
    usize n = 15;             /* "break-crash-v1\n" */
    n += 7 + 8 + 1;           /* "signo: " hex8 LF */
    n += 6 + 8 + 1;           /* "code: " */
    n += 12 + 16 + 1;         /* "fault_addr: " */
    n += (5 + 16 + 1) * 5;    /* pid/tid/rip/rsp/rbp */
    n += 10 + strlen(b->build_id) + 1;
    u32 i;
    for (i = 0; i < b->module_count; i++) {
        n += 8 + 16 + 1 + 16 + 1 + strlen(b->modules[i].name) + 1;
    }
    n += 13 + (b->stack_window_len ? 1 + 2 * b->stack_window_len : 0) + 1;
    n += 13 + (b->context_blob_len ? 1 + 2 * b->context_blob_len : 0) + 1;
    return n;
}

usize break_crash_record_builder_finish(const BreakCrashRecordBuilder *b, u8 *out,
                                        usize capacity) {
    if (!b || !out) return 0;
    usize need = bc_record_size(b);
    if (capacity < need) return 0;
    if (need > BREAK_CRASH_RECORD_MAX) return 0; /* unreachable by construction */

    u8 *p = out;
    u32 i;
    bc_put_str(&p, "break-crash-v1\n");
    bc_put_str(&p, "signo: ");
    bc_put_hex(&p, (u32)b->signo, 8);
    *p++ = '\n';
    bc_put_str(&p, "code: ");
    bc_put_hex(&p, (u32)b->code, 8);
    *p++ = '\n';
    bc_put_str(&p, "fault_addr: ");
    bc_put_hex(&p, b->fault_addr, 16);
    *p++ = '\n';
    bc_put_str(&p, "pid: ");
    bc_put_hex(&p, b->pid, 16);
    *p++ = '\n';
    bc_put_str(&p, "tid: ");
    bc_put_hex(&p, b->tid, 16);
    *p++ = '\n';
    bc_put_str(&p, "rip: ");
    bc_put_hex(&p, b->rip, 16);
    *p++ = '\n';
    bc_put_str(&p, "rsp: ");
    bc_put_hex(&p, b->rsp, 16);
    *p++ = '\n';
    bc_put_str(&p, "rbp: ");
    bc_put_hex(&p, b->rbp, 16);
    *p++ = '\n';
    bc_put_str(&p, "build-id: ");
    bc_put_str(&p, b->build_id);
    *p++ = '\n';
    for (i = 0; i < b->module_count; i++) {
        bc_put_str(&p, "module: ");
        bc_put_hex(&p, b->modules[i].offset, 16);
        *p++ = ' ';
        bc_put_hex(&p, b->modules[i].size, 16);
        *p++ = ' ';
        bc_put_str(&p, b->modules[i].name);
        *p++ = '\n';
    }
    bc_put_str(&p, "stack-window:");
    if (b->stack_window_len) {
        *p++ = ' ';
        bc_put_hexbytes(&p, b->stack_window, b->stack_window_len);
    }
    *p++ = '\n';
    bc_put_str(&p, "context-blob:");
    if (b->context_blob_len) {
        *p++ = ' ';
        bc_put_hexbytes(&p, b->context_blob, b->context_blob_len);
    }
    *p++ = '\n';
    return (usize)(p - out); /* == need by construction */
}

void break_crash_record_builder_destroy(BreakCrashRecordBuilder *b) {
    free(b);
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
        bool ok = platform_atomic_writer_write(w, buf, (usize)size) &&
                  platform_atomic_writer_commit(w); /* consumes the writer */
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
    bool ok = platform_atomic_writer_write(w, record_bytes, len) &&
              platform_atomic_writer_commit(w); /* consumes the writer */
    if (!ok) return false; /* the id stays unconsumed (no target was created) */
    s->next_id++;
    bc_enforce_retention(s, BC_CLASS_PENDING);
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

static bool bc_mark(BreakCrashSpool *s, u64 index, int target_class) {
    if (!s) return false;
    const char *target_dir = bc_class_dir(s, target_class);
    if (!target_dir) return false;
    u64 *ids = NULL;
    u32 count = 0;
    if (!bc_list_ids(s->pending, &ids, &count)) return false;
    if (index >= count) {
        free(ids);
        return false;
    }
    u64 id = ids[count - 1 - index]; /* newest-first, same as read */
    free(ids);

    char name[25];
    bc_id_to_name(id, name);
    char src[PLATFORM_FS_PATH_CAPACITY];
    char dst[PLATFORM_FS_PATH_CAPACITY];
    if (!bc_join(src, sizeof(src), s->pending, name)) return false;
    if (!bc_join(dst, sizeof(dst), target_dir, name)) return false;
    if (rename(src, dst) != 0) return false; /* same filesystem by construction */
    bc_dir_fsync(s->pending);
    bc_dir_fsync(target_dir);
    bc_enforce_retention(s, target_class);
    return true;
}

bool break_crash_spool_mark_sent(BreakCrashSpool *s, u64 index) {
    return bc_mark(s, index, BC_CLASS_SENT);
}

bool break_crash_spool_mark_discarded(BreakCrashSpool *s, u64 index) {
    return bc_mark(s, index, BC_CLASS_DISCARDED);
}
