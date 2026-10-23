/* break_update_client — Stage 5 Phase B Tasks 1+2+3 implementation. The
 * contract (on-disk layout, canonical state format, write-ahead discipline,
 * rollback policy, error enum semantics, download/resume semantics, the
 * stage/activate/unstage pipeline) is documented in break_update_client.h;
 * the parser deliberately mirrors the Phase A manifest discipline in
 * break_update.c (strict grammars, unknown/malformed → fail, no repair). */

#include <update/break_update_client.h>

#include <crypto/break_crypto.h>
#include <platform/platform_fs.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPC_STATE_MAX_BYTES (64u * 1024u) /* state file ≤ 64 KiB */
#define UPC_HEX_NAME_LEN    64u
#define UPC_TEXT_CAP        512u /* worst-case serialized state ≈ 324 bytes */
#define UPC_CHUNK_NAME_MAX  128u /* manifest chunk-name cap (break_update.c) */
#define UPC_WRITER_TMP_LEN  10u  /* PlatformAtomicWriter's ".tmpXXXXXX" */

typedef struct {
    char current; /* 'A' | 'B' | '-' (none) */
    char staged;  /* 'A' | 'B' | '-' (none) */
    bool pending;
    bool confirmed;
    u32 current_v[3]; /* valid iff current != '-' (parse invariant) */
    bool has_previous;
    u32 previous_v[3]; /* valid iff has_previous */
    u32 min_rollback_v[3];
    bool has_resume;
    char resume_hash[UPC_HEX_NAME_LEN + 1]; /* valid iff has_resume */
    u64 resume_offset;
} UpcState;

struct BreakUpdateClient {
    char root[PLATFORM_FS_PATH_CAPACITY];       /* <root> (chunks live below) */
    char state_path[PLATFORM_FS_PATH_CAPACITY]; /* "<root>/state" */
    UpcState st;
    BreakUpdateClientError last_error;
};

static const UpcState UPC_INITIAL = {
    '-', '-', false, false, {0, 0, 0}, false, {0, 0, 0}, {0, 0, 0}, false, {0}, 0
};

/* ---- strict field grammars (manifest discipline) ------------------------- */

static int upc_hexval_lower(u8 c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return -1;
}

/* MAJOR.MINOR.PATCH: decimal, no leading zeros ("0" allowed), u32-range. */
static bool upc_parse_version(const u8 *s, usize n, u32 out[3]) {
    if (n == 0 || n > 64) return false;
    usize i = 0;
    int comp;
    for (comp = 0; comp < 3; comp++) {
        usize start = i;
        u64 val = 0;
        while (i < n && s[i] >= '0' && s[i] <= '9') {
            val = val * 10u + (u64)(s[i] - '0');
            if (val > 4294967295ull) return false; /* u32 overflow */
            i++;
        }
        usize digits = i - start;
        if (digits == 0 || digits > 10) return false;
        if (digits > 1 && s[start] == '0') return false;
        out[comp] = (u32)val;
        if (comp < 2) {
            if (i >= n || s[i] != '.') return false;
            i++;
        }
    }
    return i == n;
}

/* Decimal u64, no leading zeros, overflow-checked. */
static bool upc_parse_u64(const u8 *s, usize n, u64 *out) {
    if (n < 1 || n > 20) return false;
    if (n > 1 && s[0] == '0') return false;
    u64 val = 0;
    usize i;
    for (i = 0; i < n; i++) {
        u8 c = s[i];
        if (c < '0' || c > '9') return false;
        u64 d = (u64)(c - '0');
        if (val > (UINT64_MAX - d) / 10u) return false;
        val = val * 10u + d;
    }
    *out = val;
    return true;
}

static bool upc_parse_slot(const u8 *s, usize n, char *out) {
    if (n == 1 && (s[0] == 'A' || s[0] == 'B')) {
        *out = (char)s[0];
        return true;
    }
    if (n == 4 && memcmp(s, "none", 4) == 0) {
        *out = '-';
        return true;
    }
    return false;
}

static bool upc_parse_yesno(const u8 *s, usize n, bool *out) {
    if (n == 3 && memcmp(s, "yes", 3) == 0) {
        *out = true;
        return true;
    }
    if (n == 2 && memcmp(s, "no", 2) == 0) {
        *out = false;
        return true;
    }
    return false;
}

static bool upc_parse_version_or_none(const u8 *s, usize n, u32 out[3], bool *is_none) {
    if (n == 4 && memcmp(s, "none", 4) == 0) {
        *is_none = true;
        return true;
    }
    *is_none = false;
    return upc_parse_version(s, n, out);
}

/* "none" or exactly 64 lowercase hex + '|' + decimal u64 offset. */
static bool upc_parse_resume(const u8 *s, usize n, UpcState *out) {
    if (n == 4 && memcmp(s, "none", 4) == 0) {
        out->has_resume = false;
        return true;
    }
    if (n < UPC_HEX_NAME_LEN + 2) return false; /* hash + '|' + >=1 digit */
    usize i;
    for (i = 0; i < UPC_HEX_NAME_LEN; i++) {
        if (upc_hexval_lower(s[i]) < 0) return false;
    }
    if (s[UPC_HEX_NAME_LEN] != '|') return false;
    u64 off = 0;
    if (!upc_parse_u64(s + UPC_HEX_NAME_LEN + 1, n - UPC_HEX_NAME_LEN - 1, &off))
        return false;
    memcpy(out->resume_hash, s, UPC_HEX_NAME_LEN);
    out->resume_hash[UPC_HEX_NAME_LEN] = '\0';
    out->resume_offset = off;
    out->has_resume = true;
    return true;
}

/* ---- canonical text parse ------------------------------------------------- */

typedef struct {
    const u8 *text;
    usize len;
    usize pos;
} UpcCursor;

/* Next LF-terminated line (content excludes the LF). False at end of input;
 * the caller's final-LF pre-check makes a missing LF unreachable. */
static bool upc_next_line(UpcCursor *c, const u8 **line, usize *line_len) {
    if (c->pos >= c->len) return false;
    const u8 *start = c->text + c->pos;
    const u8 *nl = memchr(start, '\n', c->len - c->pos);
    if (!nl) return false;
    *line = start;
    *line_len = (usize)(nl - start);
    c->pos += *line_len + 1;
    return true;
}

static bool upc_starts_with(const u8 *line, usize n, const char *prefix) {
    usize p = strlen(prefix);
    return n >= p && memcmp(line, prefix, p) == 0;
}

/* Full canonical parse; ANY deviation → false (no partial parse, no repair).
 * The cross-field invariants are documented in the header. */
static bool upc_parse_state(const u8 *bytes, usize len, UpcState *out) {
    if (!bytes || len == 0 || len > UPC_STATE_MAX_BYTES) return false;
    if (bytes[len - 1] != '\n') return false;
    usize i;
    for (i = 0; i < len; i++) {
        u8 c = bytes[i];
        if (c != '\n' && (c < 0x20 || c > 0x7E)) return false;
    }

    UpcCursor cur = {bytes, len, 0};
    const u8 *line;
    usize n;
    UpcState st = UPC_INITIAL;

    if (!upc_next_line(&cur, &line, &n)) return false;
    if (n != 21 || memcmp(line, "break-update-state-v1", 21) != 0) return false;

    if (!upc_next_line(&cur, &line, &n)) return false;
    if (!upc_starts_with(line, n, "current: ")) return false;
    if (!upc_parse_slot(line + 9, n - 9, &st.current)) return false;

    if (!upc_next_line(&cur, &line, &n)) return false;
    if (!upc_starts_with(line, n, "staged: ")) return false;
    if (!upc_parse_slot(line + 8, n - 8, &st.staged)) return false;

    if (!upc_next_line(&cur, &line, &n)) return false;
    if (!upc_starts_with(line, n, "pending: ")) return false;
    if (!upc_parse_yesno(line + 9, n - 9, &st.pending)) return false;

    if (!upc_next_line(&cur, &line, &n)) return false;
    if (!upc_starts_with(line, n, "confirmed: ")) return false;
    if (!upc_parse_yesno(line + 11, n - 11, &st.confirmed)) return false;

    bool cur_ver_none = false;
    if (!upc_next_line(&cur, &line, &n)) return false;
    if (!upc_starts_with(line, n, "current-version: ")) return false;
    if (!upc_parse_version_or_none(line + 17, n - 17, st.current_v, &cur_ver_none))
        return false;

    bool prev_none = false;
    if (!upc_next_line(&cur, &line, &n)) return false;
    if (!upc_starts_with(line, n, "previous-version: ")) return false;
    if (!upc_parse_version_or_none(line + 18, n - 18, st.previous_v, &prev_none))
        return false;
    st.has_previous = !prev_none;

    if (!upc_next_line(&cur, &line, &n)) return false;
    if (!upc_starts_with(line, n, "min-rollback-version: ")) return false;
    if (!upc_parse_version(line + 22, n - 22, st.min_rollback_v)) return false;

    if (!upc_next_line(&cur, &line, &n)) return false;
    if (!upc_starts_with(line, n, "resume-chunk: ")) return false;
    if (!upc_parse_resume(line + 14, n - 14, &st)) return false;

    if (cur.pos != cur.len) return false; /* nothing may follow */

    /* Cross-field invariants: states no legal transition can produce. */
    bool cur_none = st.current == '-';
    if (cur_ver_none != cur_none) return false;
    if (cur_none && st.has_previous) return false;
    if (st.pending && st.confirmed) return false;
    if (st.pending && cur_none) return false;
    if (st.confirmed && cur_none) return false;

    *out = st;
    return true;
}

/* ---- canonical text serialize + write-ahead persist ----------------------- */

static bool upc_append(char *buf, usize cap, usize *off, const char *s) {
    usize n = strlen(s);
    if (*off + n + 1 > cap) return false; /* keep room for the NUL */
    memcpy(buf + *off, s, n + 1);
    *off += n;
    return true;
}

static bool upc_append_line(char *buf, usize cap, usize *off, const char *line) {
    return upc_append(buf, cap, off, line);
}

static bool upc_append_fmt(char *buf, usize cap, usize *off, const char *key,
                           const char *value) {
    char line[160];
    int r = snprintf(line, sizeof(line), "%s%s\n", key, value);
    if (r < 0 || (usize)r >= sizeof(line)) return false;
    return upc_append_line(buf, cap, off, line);
}

/* Worst case "4294967295.4294967295.4294967295" + NUL = 33. */
static void upc_format_version(char out[33], const u32 v[3]) {
    snprintf(out, 33, "%lu.%lu.%lu", (unsigned long)v[0], (unsigned long)v[1],
             (unsigned long)v[2]);
}

static bool upc_serialize(const UpcState *st, char *buf, usize cap, usize *out_len) {
    usize off = 0;
    char ver[33];
    char value[UPC_HEX_NAME_LEN + 1 + 20 + 1];

    if (!upc_append_line(buf, cap, &off, "break-update-state-v1\n")) return false;

    if (!upc_append_fmt(buf, cap, &off, "current: ",
                        st->current == '-' ? "none" : (st->current == 'A' ? "A" : "B")))
        return false;
    if (!upc_append_fmt(buf, cap, &off, "staged: ",
                        st->staged == '-' ? "none" : (st->staged == 'A' ? "A" : "B")))
        return false;
    if (!upc_append_fmt(buf, cap, &off, "pending: ", st->pending ? "yes" : "no"))
        return false;
    if (!upc_append_fmt(buf, cap, &off, "confirmed: ", st->confirmed ? "yes" : "no"))
        return false;

    if (st->current == '-') {
        if (!upc_append_fmt(buf, cap, &off, "current-version: ", "none")) return false;
    } else {
        upc_format_version(ver, st->current_v);
        if (!upc_append_fmt(buf, cap, &off, "current-version: ", ver)) return false;
    }
    if (!st->has_previous) {
        if (!upc_append_fmt(buf, cap, &off, "previous-version: ", "none")) return false;
    } else {
        upc_format_version(ver, st->previous_v);
        if (!upc_append_fmt(buf, cap, &off, "previous-version: ", ver)) return false;
    }
    upc_format_version(ver, st->min_rollback_v);
    if (!upc_append_fmt(buf, cap, &off, "min-rollback-version: ", ver)) return false;

    if (!st->has_resume) {
        if (!upc_append_fmt(buf, cap, &off, "resume-chunk: ", "none")) return false;
    } else {
        int r = snprintf(value, sizeof(value), "%s|%llu", st->resume_hash,
                         (unsigned long long)st->resume_offset);
        if (r < 0 || (usize)r >= sizeof(value)) return false;
        if (!upc_append_fmt(buf, cap, &off, "resume-chunk: ", value)) return false;
    }

    *out_len = off;
    return true;
}

/* Write-ahead: the serialized NEXT state is committed through the atomic
 * writer BEFORE the caller flips the in-memory state. */
static bool upc_persist(const char *state_path, const UpcState *st) {
    char text[UPC_TEXT_CAP];
    usize len = 0;
    if (!upc_serialize(st, text, sizeof(text), &len)) return false;
    PlatformAtomicWriter *w = platform_atomic_writer_open(state_path);
    if (!w) return false;
    if (!platform_atomic_writer_write(w, text, len)) {
        platform_atomic_writer_abort(w); /* consumes the writer */
        return false;
    }
    return platform_atomic_writer_commit(w); /* consumes the writer */
}

/* ---- open ------------------------------------------------------------------ */

static bool upc_read_state(const char *path, u64 size, UpcState *out) {
    u8 *buf = malloc(size ? (usize)size : 1); /* always a freeable pointer */
    if (!buf) return false;
    usize got = 0;
    FILE *fp = fopen(path, "rb");
    if (fp) {
        if (size) got = fread(buf, 1, (usize)size, fp);
        fclose(fp);
    }
    if (!fp || got != (usize)size) { /* missing/short read (incl. concurrent shrink) */
        free(buf);
        return false;
    }
    bool ok = upc_parse_state(buf, (usize)size, out);
    free(buf);
    return ok;
}

BreakUpdateClient *break_update_client_open(const char *root_path) {
    if (!root_path) return NULL;
    usize n = strlen(root_path);
    /* Tightest suffix: "/slots/A/files/" + a 128-byte manifest chunk name +
     * the writer's ".tmpXXXXXX" + NUL (Task 3's materialization path; covers
     * "/chunks/<64hex>.part", "/slots/A/update-version" and "/state" too).
     * Checked once up front so every later join is safe by construction. */
    if (n == 0 ||
        n + 15 + UPC_CHUNK_NAME_MAX + UPC_WRITER_TMP_LEN + 1 > PLATFORM_FS_PATH_CAPACITY)
        return NULL;
    if (!platform_mkdir(root_path)) return NULL;

    char p[PLATFORM_FS_PATH_CAPACITY];
    memcpy(p, root_path, n + 1);
    static const char *const dirs[] = {"/chunks", "/slots", "/slots/A", "/slots/B"};
    usize i;
    for (i = 0; i < sizeof(dirs) / sizeof(dirs[0]); i++) {
        memcpy(p + n, dirs[i], strlen(dirs[i]) + 1);
        if (!platform_mkdir(p)) return NULL;
    }

    char state_path[PLATFORM_FS_PATH_CAPACITY];
    memcpy(state_path, root_path, n);
    memcpy(state_path + n, "/state", sizeof("/state")); /* includes NUL */

    UpcState st;
    u64 size = 0;
    if (platform_file_size(state_path, &size)) {
        if (size > UPC_STATE_MAX_BYTES) return NULL;
        if (!upc_read_state(state_path, size, &st)) return NULL;
    } else {
        /* Absent (or not a regular file — then the atomic commit fails
         * closed below) → create the initial state. */
        st = UPC_INITIAL;
        if (!upc_persist(state_path, &st)) return NULL;
    }

    BreakUpdateClient *c = calloc(1, sizeof(*c));
    if (!c) return NULL; /* layout + initial state survive; next open parses them */
    memcpy(c->root, root_path, n + 1);
    memcpy(c->state_path, state_path, n + 6 + 1);
    c->st = st;
    c->last_error = BREAK_UPDATE_CLIENT_OK;
    return c;
}

void break_update_client_destroy(BreakUpdateClient *c) {
    free(c); /* free(NULL) is the abort(NULL)-style no-op */
}

/* ---- queries ---------------------------------------------------------------- */

BreakUpdateClientError break_update_client_last_error(const BreakUpdateClient *c) {
    return c ? c->last_error : BREAK_UPDATE_CLIENT_INVALID;
}

char break_update_client_current_slot(const BreakUpdateClient *c) {
    return c ? c->st.current : '-';
}

bool break_update_client_pending(const BreakUpdateClient *c) {
    return c ? c->st.pending : false;
}

bool break_update_client_confirmed(const BreakUpdateClient *c) {
    return c ? c->st.confirmed : false;
}

void break_update_client_current_version(const BreakUpdateClient *c, u32 out[3]) {
    if (!out) return;
    if (!c || c->st.current == '-') {
        out[0] = 0;
        out[1] = 0;
        out[2] = 0;
        return;
    }
    out[0] = c->st.current_v[0];
    out[1] = c->st.current_v[1];
    out[2] = c->st.current_v[2];
}

/* ---- boot lifecycle ----------------------------------------------------------- */

bool break_update_client_confirm_boot(BreakUpdateClient *c) {
    if (!c) return false;
    if (!c->st.pending) {
        c->last_error = BREAK_UPDATE_CLIENT_STATE;
        return false;
    }
    UpcState next = c->st;
    next.pending = false;
    next.confirmed = true;
    if (!upc_persist(c->state_path, &next)) { /* persist BEFORE the flip */
        c->last_error = BREAK_UPDATE_CLIENT_IO;
        return false;
    }
    c->st = next;
    c->last_error = BREAK_UPDATE_CLIENT_OK;
    return true;
}

static int upc_version_cmp(const u32 a[3], const u32 b[3]) {
    int i;
    for (i = 0; i < 3; i++) {
        if (a[i] < b[i]) return -1;
        if (a[i] > b[i]) return 1;
    }
    return 0;
}

bool break_update_client_rollback(BreakUpdateClient *c) {
    if (!c) return false;
    if (c->st.staged != '-') { /* clean the staged slot first (Task 3 unstage) */
        c->last_error = BREAK_UPDATE_CLIENT_STATE;
        return false;
    }
    if (!c->st.has_previous) {
        c->last_error = BREAK_UPDATE_CLIENT_STATE;
        return false;
    }
    if (upc_version_cmp(c->st.previous_v, c->st.min_rollback_v) < 0) {
        c->last_error = BREAK_UPDATE_CLIENT_POLICY;
        return false;
    }
    /* current != '-' here: has_previous ⇒ current set (parse invariant and
     * every transition preserve it). Swap slot AND version; the rolled-back
     * boot is known-good (it confirmed once before) → confirmed=yes. */
    UpcState next = c->st;
    next.current = c->st.current == 'A' ? 'B' : 'A';
    memcpy(next.current_v, c->st.previous_v, sizeof(next.current_v));
    memcpy(next.previous_v, c->st.current_v, sizeof(next.previous_v));
    next.pending = false;
    next.confirmed = true;
    if (!upc_persist(c->state_path, &next)) { /* persist BEFORE the flip */
        c->last_error = BREAK_UPDATE_CLIENT_IO;
        return false;
    }
    c->st = next;
    c->last_error = BREAK_UPDATE_CLIENT_OK;
    return true;
}

/* ---- Task 2: chunked downloader with byte-level resume -----------------------
 * Semantics are documented in the header ("Task 2 semantics"): manifest-size
 * clamping, one .part at a time, block-granular write-ahead progress, resume
 * triage (stale-complete → silent clear; corrupt → STATE clean restart),
 * digest-gated store put. */

#define UPC_FETCH_BLOCK (64u * 1024u) /* fixed spool block; never sized by the manifest */

static void upc_hex_encode(const u8 *in, usize n, char *out) {
    static const char h[] = "0123456789abcdef";
    usize i;
    for (i = 0; i < n; i++) {
        out[2 * i] = h[in[i] >> 4];
        out[2 * i + 1] = h[in[i] & 15];
    }
    out[2 * n] = '\0';
}

/* "<root>/chunks/<name64><suffix>" — safe by construction after the open-time
 * path bound (which covers exactly this join); checked anyway. */
static bool upc_chunk_path(const BreakUpdateClient *c, const char *hex,
                           const char *suffix, char *out, usize cap) {
    usize rn = strlen(c->root);
    usize sn = strlen(suffix);
    if (rn + 8 + UPC_HEX_NAME_LEN + sn + 1 > cap) return false;
    memcpy(out, c->root, rn);
    memcpy(out + rn, "/chunks/", 8);
    memcpy(out + rn + 8, hex, UPC_HEX_NAME_LEN);
    memcpy(out + rn + 8 + UPC_HEX_NAME_LEN, suffix, sn + 1);
    return true;
}

/* Persist-then-flip transitions of the resume entry (the same write-ahead
 * discipline as the boot lifecycle ops: on persist failure the in-memory
 * state stays put, so memory and disk never disagree). */
static bool upc_set_resume(BreakUpdateClient *c, const char *hex, u64 off) {
    UpcState next = c->st;
    next.has_resume = true;
    memcpy(next.resume_hash, hex, UPC_HEX_NAME_LEN + 1);
    next.resume_offset = off;
    if (!upc_persist(c->state_path, &next)) return false;
    c->st = next;
    return true;
}

static bool upc_clear_resume(BreakUpdateClient *c) {
    UpcState next = c->st;
    next.has_resume = false;
    next.resume_offset = 0;
    if (!upc_persist(c->state_path, &next)) return false;
    c->st = next;
    return true;
}

/* .part on disk consistent with resume offset O: absent iff O == 0, exact
 * size otherwise (O == size is valid: a fully-spooled chunk pending
 * verify+store). */
static bool upc_part_consistent(const char *part_path, u64 off) {
    u64 sz = 0;
    if (!platform_file_size(part_path, &sz)) return off == 0;
    return sz == off;
}

static bool upc_remove_part(const char *part_path) {
    u64 sz = 0;
    if (!platform_file_size(part_path, &sz)) return true; /* absent */
    return remove(part_path) == 0;
}

/* One chunk: spool to .part from `offset` (the resume entry hash|offset is
 * already persisted), streaming-hash as bytes land, verify the full digest
 * against the manifest, store_put (which recomputes the hash — the chunk
 * lands under the manifest name by construction), remove the .part, clear
 * the entry. false → c->last_error set (FETCH/VERIFY/IO). */
static bool upc_fetch_chunk(BreakUpdateClient *c, BreakUpdateStore *s,
                            const char *hex, const u8 expect[32], u64 size,
                            u64 offset, BreakUpdateFetchFn fetch, void *user) {
    char part_path[PLATFORM_FS_PATH_CAPACITY];
    FILE *fp = NULL;
    FILE *in = NULL;
    BreakCryptoSha256Ctx *ctx = NULL;
    u8 *buf = NULL;
    u8 *all = NULL;
    u64 left, off, len;
    usize want, got;
    u8 digest[32];
    bool read_ok, hash_ok, readback_ok;
    int close_rc;
    bool ok = false;

    if (!upc_chunk_path(c, hex, ".part", part_path, sizeof(part_path))) {
        c->last_error = BREAK_UPDATE_CLIENT_IO;
        return false;
    }
    fp = fopen(part_path, offset ? "ab" : "wb"); /* append lands at exactly the offset */
    if (!fp) {
        c->last_error = BREAK_UPDATE_CLIENT_IO;
        return false;
    }
    ctx = break_crypto_sha256_ctx_create();
    buf = ctx ? malloc(UPC_FETCH_BLOCK) : NULL;
    if (!ctx || !buf) {
        c->last_error = BREAK_UPDATE_CLIENT_IO; /* OOM counts as local IO */
        goto out;
    }

    /* Re-hash the spooled prefix on resume (a prefix cannot be verified
     * against the final digest; these bytes are trusted until completion,
     * where the FULL digest gates the store). */
    left = offset;
    if (left) {
        in = fopen(part_path, "rb");
        if (!in) {
            c->last_error = BREAK_UPDATE_CLIENT_IO;
            goto out;
        }
        read_ok = true;
        while (left) {
            want = left < (u64)UPC_FETCH_BLOCK ? (usize)left : (usize)UPC_FETCH_BLOCK;
            got = fread(buf, 1, want, in);
            if (got != want || !break_crypto_sha256_update(ctx, buf, got)) {
                read_ok = false;
                break;
            }
            left -= want;
        }
        fclose(in);
        in = NULL;
        if (!read_ok) {
            c->last_error = BREAK_UPDATE_CLIENT_IO;
            goto out;
        }
    }

    off = offset;
    while (off < size) {
        len = size - off; /* off <= size: no underflow; off+len <= size <= UINT64_MAX */
        if (len > (u64)UPC_FETCH_BLOCK) len = (u64)UPC_FETCH_BLOCK;
        /* offset+len is overflow-free by construction (the interface's
         * "overflow-checked by the client before calling" contract). */
        if (!fetch(user, hex, off, len, buf)) {
            c->last_error = BREAK_UPDATE_CLIENT_FETCH; /* progress kept */
            goto out;
        }
        /* Write-ahead: bytes to the OS first, the new offset persists after. */
        if (fwrite(buf, 1, (usize)len, fp) != (usize)len || fflush(fp) != 0 ||
            !break_crypto_sha256_update(ctx, buf, (usize)len) ||
            !upc_set_resume(c, hex, off + len)) {
            /* A short write may leave .part LONGER than the persisted entry —
             * the next call's consistency check restarts the chunk clean. */
            c->last_error = BREAK_UPDATE_CLIENT_IO;
            goto out;
        }
        off += len;
    }

    hash_ok = break_crypto_sha256_final(ctx, digest);
    close_rc = fclose(fp);
    fp = NULL;
    if (!hash_ok || close_rc != 0) {
        c->last_error = BREAK_UPDATE_CLIENT_IO;
        goto out;
    }
    if (memcmp(digest, expect, sizeof(digest)) != 0) {
        /* VERIFY: discard the .part, clear the entry. If the cleanup itself
         * fails, report IO — the next call's triage self-heals. */
        if (!upc_remove_part(part_path) || !upc_clear_resume(c))
            c->last_error = BREAK_UPDATE_CLIENT_IO;
        else
            c->last_error = BREAK_UPDATE_CLIENT_VERIFY;
        goto out;
    }

    /* Verified: read the spool back fully and put it into the CAS. */
    if ((u64)(usize)size != size) { /* u64 → usize truncation guard (32-bit) */
        c->last_error = BREAK_UPDATE_CLIENT_IO;
        goto out;
    }
    all = malloc(size ? (usize)size : 1);
    if (!all) {
        c->last_error = BREAK_UPDATE_CLIENT_IO;
        goto out;
    }
    readback_ok = false;
    in = fopen(part_path, "rb");
    if (in) {
        got = size ? fread(all, 1, (usize)size, in) : 0;
        close_rc = fclose(in);
        in = NULL;
        readback_ok = close_rc == 0 && got == (usize)size;
    }
    /* put fails e.g. beyond the store's 128 MiB cap → IO (documented). On
     * failure the entry is kept: the next call re-verifies and re-puts the
     * fully-spooled chunk without any transport. */
    if (!readback_ok || !break_update_store_put_chunk(s, all, (usize)size)) {
        c->last_error = BREAK_UPDATE_CLIENT_IO;
        goto out;
    }
    free(all);
    all = NULL;

    if (!upc_remove_part(part_path) || !upc_clear_resume(c)) {
        /* The chunk IS in the CAS; a kept entry is the stale-complete case
         * the triage clears silently on the next call. */
        c->last_error = BREAK_UPDATE_CLIENT_IO;
        goto out;
    }
    ok = true;
out:
    free(all);
    free(buf);
    if (ctx) break_crypto_sha256_ctx_destroy(ctx);
    if (in) fclose(in);
    if (fp) fclose(fp);
    return ok;
}

bool break_update_client_fetch_all(BreakUpdateClient *c, const BreakUpdateManifest *m,
                                   BreakUpdateFetchFn fetch, void *user) {
    BreakUpdateStore *s;
    u64 count, i;
    u64 resume_idx = UINT64_MAX;
    u64 resume_off = 0;
    bool ok = false;

    if (!c) return false;
    if (!m || !fetch) {
        c->last_error = BREAK_UPDATE_CLIENT_INVALID;
        return false;
    }
    s = break_update_store_open(c->root);
    if (!s) {
        c->last_error = BREAK_UPDATE_CLIENT_IO;
        return false;
    }
    count = break_update_manifest_chunk_count(m);

    /* Resume-entry triage (header "Task 2 semantics"). */
    if (c->st.has_resume) {
        char part_path[PLATFORM_FS_PATH_CAPACITY];
        char hex[UPC_HEX_NAME_LEN + 1];
        const char *rh = c->st.resume_hash;
        const char *nm;
        u8 h[32];
        u64 roff = c->st.resume_offset;
        u64 found_size = 0;
        bool found = false, resumable;
        if (!upc_chunk_path(c, rh, ".part", part_path, sizeof(part_path))) {
            c->last_error = BREAK_UPDATE_CLIENT_IO;
            goto out;
        }
        for (i = 0; i < count; i++) {
            if (!break_update_manifest_chunk_at(m, i, &nm, h, &found_size)) {
                c->last_error = BREAK_UPDATE_CLIENT_IO; /* i < count: unreachable */
                goto out;
            }
            upc_hex_encode(h, 32, hex);
            if (memcmp(hex, rh, UPC_HEX_NAME_LEN + 1) == 0) {
                found = true;
                resume_idx = i;
                break;
            }
        }
        if (found && break_update_store_has_chunk(s, rh)) {
            /* Stale entry (crash between store_put and entry-clear): clean
             * up and continue — a resumable partial state, not an error. */
            if (!upc_remove_part(part_path) || !upc_clear_resume(c)) {
                c->last_error = BREAK_UPDATE_CLIENT_IO;
                goto out;
            }
            resume_idx = UINT64_MAX;
        } else {
            resumable = found && roff <= found_size &&
                        upc_part_consistent(part_path, roff);
            if (!resumable) {
                /* Corrupt resume → restarted clean: the next call re-fetches
                 * the chunk from 0. */
                if (!upc_remove_part(part_path) || !upc_clear_resume(c)) {
                    c->last_error = BREAK_UPDATE_CLIENT_IO;
                    goto out;
                }
                c->last_error = BREAK_UPDATE_CLIENT_STATE;
                goto out;
            }
            resume_off = roff;
        }
    }

    /* A valid resume entry's chunk continues FIRST (starting any other chunk
     * would overwrite its entry), then the manifest in order. Sequential:
     * at most one .part exists at any moment. */
    if (resume_idx != UINT64_MAX) {
        const char *nm;
        u8 h[32];
        u64 csz;
        char hex[UPC_HEX_NAME_LEN + 1];
        if (!break_update_manifest_chunk_at(m, resume_idx, &nm, h, &csz)) {
            c->last_error = BREAK_UPDATE_CLIENT_IO; /* validated above */
            goto out;
        }
        upc_hex_encode(h, 32, hex);
        if (!upc_fetch_chunk(c, s, hex, h, csz, resume_off, fetch, user))
            goto out; /* last_error set inside */
    }
    for (i = 0; i < count; i++) {
        const char *nm;
        u8 h[32];
        u64 csz;
        char hex[UPC_HEX_NAME_LEN + 1];
        if (!break_update_manifest_chunk_at(m, i, &nm, h, &csz)) {
            c->last_error = BREAK_UPDATE_CLIENT_IO; /* i < count: unreachable */
            goto out;
        }
        upc_hex_encode(h, 32, hex);
        /* CAS dedup: present chunks are NEVER re-fetched (call-count pin).
         * Also skips the just-completed resume chunk. */
        if (break_update_store_has_chunk(s, hex)) continue;
        if (!upc_set_resume(c, hex, 0)) { /* intent persists BEFORE the .part */
            c->last_error = BREAK_UPDATE_CLIENT_IO;
            goto out;
        }
        if (!upc_fetch_chunk(c, s, hex, h, csz, 0, fetch, user)) goto out;
    }
    ok = true;
    c->last_error = BREAK_UPDATE_CLIENT_OK;
out:
    break_update_store_destroy(s);
    return ok;
}

/* ---- Task 3: stage → activate → unstage --------------------------------------
 * Semantics are documented in the header ("Task 3 semantics"): signature +
 * policy before ANY transport, clean-then-materialize into the inactive
 * slot, write-ahead staged mark last, slot-resident update-version marker,
 * failure ⇒ partial slot removed + state unchanged except resume progress. */

#define UPC_SLOT_TREE_DEPTH 64u /* manifest names ≤ 128 B ⇒ ≤ 64 components */

/* "<root>/slots/<slot><suffix>" — safe by construction after the open-time
 * path bound (which covers the deepest join); checked anyway. */
static bool upc_slot_path(const BreakUpdateClient *c, char slot,
                          const char *suffix, char *out, usize cap) {
    usize rn = strlen(c->root);
    usize sn = strlen(suffix);
    if (rn + 7 + 1 + sn + 1 > cap) return false;
    memcpy(out, c->root, rn);
    memcpy(out + rn, "/slots/", 7);
    out[rn + 7] = slot;
    memcpy(out + rn + 8, suffix, sn + 1);
    return true;
}

/* Removes the file or directory tree at path (post-order), depth-bounded;
 * an absent path is success. Entries are re-listed after each drained batch
 * so a directory holding more entries than one listing's capacity still
 * empties. Files and emptied directories both go through ISO-C remove()
 * (POSIX remove() unlinks files and rmdir's directories; Win32 is
 * compile-only this phase — no new _WIN32 branches, plan Global
 * Constraints). Fails closed: any unremovable entry → false. */
static bool upc_remove_tree_at(const char *path, unsigned depth) {
    PlatformDirEntry entries[16];
    u32 count = 0;
    if (depth > UPC_SLOT_TREE_DEPTH) return false;
    if (!platform_list_dir(path, entries, 16, &count)) {
        u64 sz = 0;
        if (!platform_file_size(path, &sz)) return true; /* absent */
        return remove(path) == 0;                        /* a plain file */
    }
    for (;;) {
        u32 i;
        for (i = 0; i < count && i < 16; i++) {
            char child[PLATFORM_FS_PATH_CAPACITY];
            usize pn = strlen(path);
            usize en = strlen(entries[i].name);
            if (pn + 1 + en + 1 > sizeof(child)) return false;
            memcpy(child, path, pn);
            child[pn] = '/';
            memcpy(child + pn + 1, entries[i].name, en + 1);
            if (entries[i].is_dir) {
                if (!upc_remove_tree_at(child, depth + 1)) return false;
            } else if (remove(child) != 0) {
                return false;
            }
        }
        if (count <= 16) break; /* fully listed ⇒ fully drained */
        count = 0;
        if (!platform_list_dir(path, entries, 16, &count)) return false;
    }
    return remove(path) == 0; /* the now-empty directory itself */
}

/* Clears a slot's staged content: the files/ tree and the update-version
 * marker. The slot DIRECTORY itself is part of the fixed open-time layout
 * and is never removed. */
static bool upc_clean_slot(const BreakUpdateClient *c, char slot) {
    char p[PLATFORM_FS_PATH_CAPACITY];
    if (!upc_slot_path(c, slot, "/files", p, sizeof(p))) return false;
    if (!upc_remove_tree_at(p, 0)) return false;
    if (!upc_slot_path(c, slot, "/update-version", p, sizeof(p))) return false;
    return upc_remove_tree_at(p, 0);
}

/* The staged manifest's version rides inside the slot (the Task-1-pinned
 * state format has no staged-version field): one canonical "M.m.p\n" line
 * at slots/<slot>/update-version, written via the atomic writer. */
static bool upc_write_marker(const BreakUpdateClient *c, char slot, const u32 v[3]) {
    char path[PLATFORM_FS_PATH_CAPACITY];
    char text[40];
    int r = snprintf(text, sizeof(text), "%lu.%lu.%lu\n", (unsigned long)v[0],
                     (unsigned long)v[1], (unsigned long)v[2]);
    if (r < 0 || (usize)r >= sizeof(text)) return false;
    if (!upc_slot_path(c, slot, "/update-version", path, sizeof(path))) return false;
    PlatformAtomicWriter *w = platform_atomic_writer_open(path);
    if (!w) return false;
    if (!platform_atomic_writer_write(w, text, (usize)r)) {
        platform_atomic_writer_abort(w); /* consumes the writer */
        return false;
    }
    return platform_atomic_writer_commit(w); /* consumes the writer */
}

/* Strict marker read: 6..34 bytes ("0.0.0\n" .. u32-max triple + LF), one
 * line, manifest version grammar. Any deviation → false (fail closed). */
static bool upc_read_marker(const BreakUpdateClient *c, char slot, u32 v[3]) {
    char path[PLATFORM_FS_PATH_CAPACITY];
    u8 buf[40];
    u64 size = 0;
    usize got = 0;
    FILE *fp;
    if (!upc_slot_path(c, slot, "/update-version", path, sizeof(path))) return false;
    if (!platform_file_size(path, &size)) return false;
    if (size < 6 || size > 34) return false;
    fp = fopen(path, "rb");
    if (!fp) return false;
    got = fread(buf, 1, (usize)size, fp);
    if (fclose(fp) != 0) return false;
    if (got != (usize)size) return false;
    if (buf[size - 1] != '\n') return false;
    return upc_parse_version(buf, (usize)size - 1, v);
}

/* Clean the target slot, then materialize every manifest chunk from the CAS
 * (verify-on-read) to slots/<slot>/files/<name> via the atomic writer —
 * intermediate dirs per name component — and finally the version marker.
 * On ANY failure the partial slot tree is removed and false returned. */
static bool upc_materialize_slot(BreakUpdateClient *c, const BreakUpdateManifest *m,
                                 char slot) {
    char files_dir[PLATFORM_FS_PATH_CAPACITY];
    char dst[PLATFORM_FS_PATH_CAPACITY];
    char hex[UPC_HEX_NAME_LEN + 1];
    BreakUpdateStore *s = NULL;
    u64 count, i;
    usize fn;
    bool ok = false;

    if (!upc_clean_slot(c, slot)) goto out;
    if (!upc_slot_path(c, slot, "/files", files_dir, sizeof(files_dir))) goto out;
    if (!platform_mkdir(files_dir)) goto out;
    s = break_update_store_open(c->root);
    if (!s) goto out;
    fn = strlen(files_dir);
    count = break_update_manifest_chunk_count(m);
    for (i = 0; i < count; i++) {
        const char *nm;
        u8 h[32];
        u64 csz;
        u8 *buf = NULL;
        u64 len = 0;
        usize nn, comp;
        PlatformAtomicWriter *w;
        if (!break_update_manifest_chunk_at(m, i, &nm, h, &csz)) goto out; /* unreachable */
        nn = strlen(nm);
        /* Join + the writer's tmp suffix must fit (guaranteed by the
         * open-time bound; checked anyway). */
        if (fn + 1 + nn + UPC_WRITER_TMP_LEN + 1 > sizeof(dst)) goto out;
        memcpy(dst, files_dir, fn);
        dst[fn] = '/';
        memcpy(dst + fn + 1, nm, nn + 1);
        /* One platform_mkdir per intermediate component (names are manifest-
         * validated: [A-Za-z0-9._/-], no "..", no leading '/' — contained). */
        for (comp = fn + 1; comp < fn + 1 + nn; comp++) {
            if (dst[comp] == '/') {
                dst[comp] = '\0';
                if (!platform_mkdir(dst)) {
                    free(buf);
                    goto out;
                }
                dst[comp] = '/';
            }
        }
        upc_hex_encode(h, 32, hex);
        if (!break_update_store_get_chunk(s, hex, &buf, &len)) {
            free(buf);
            goto out;
        }
        w = platform_atomic_writer_open(dst);
        if (!w || !platform_atomic_writer_write(w, buf, (usize)len) ||
            !platform_atomic_writer_commit(w)) {
            platform_atomic_writer_abort(w); /* abort(NULL) is a safe no-op */
            free(buf);
            goto out;
        }
        free(buf);
    }
    {
        u32 v[3];
        break_update_manifest_version(m, v);
        if (!upc_write_marker(c, slot, v)) goto out;
    }
    ok = true;
out:
    if (s) break_update_store_destroy(s);
    if (!ok) upc_clean_slot(c, slot); /* partial staged slot removed */
    return ok;
}

bool break_update_client_stage(BreakUpdateClient *c, const BreakUpdateManifest *m,
                               const u8 pubkey[32], const char *channel,
                               const char *platform, BreakUpdateFetchFn fetch,
                               void *user) {
    u32 cur[3] = {0, 0, 0};
    char target;
    UpcState next;

    if (!c) return false;
    if (!m || !pubkey || !channel || !platform || !fetch) {
        c->last_error = BREAK_UPDATE_CLIENT_INVALID;
        return false;
    }
    /* Signature BEFORE any transport or disk effect (the cross-cutting
     * gate): VERIFY/POLICY failures perform zero fetch calls, zero disk
     * writes, zero state changes. */
    if (!break_update_manifest_verify(m, pubkey)) {
        c->last_error = BREAK_UPDATE_CLIENT_VERIFY;
        return false;
    }
    /* Policy: current version from state; a fresh client (current=none) is
     * source version 0.0.0 — the full check still runs, so only a payload
     * with min-version 0.0.0 provisions a versionless device (documented). */
    if (c->st.current != '-') memcpy(cur, c->st.current_v, sizeof(cur));
    if (!break_update_manifest_compatible(m, channel, platform, cur[0], cur[1],
                                          cur[2])) {
        c->last_error = BREAK_UPDATE_CLIENT_POLICY;
        return false;
    }
    /* unstage is the ONLY non-activating way to clear a staged slot (plan
     * verbatim) — re-staging is unstage + stage, never implicit. */
    if (c->st.staged != '-') {
        c->last_error = BREAK_UPDATE_CLIENT_STATE;
        return false;
    }
    /* Download first: a transport failure never touches a slot (the retained
     * previous version's bytes survive a failed download). fetch_all sets
     * last_error (FETCH/VERIFY/IO/STATE) and mutates only resume progress. */
    if (!break_update_client_fetch_all(c, m, fetch, user)) return false;
    target = c->st.current == 'A' ? 'B' : 'A'; /* current=none → 'A' (fixed) */
    if (!upc_materialize_slot(c, m, target)) {
        c->last_error = BREAK_UPDATE_CLIENT_IO;
        return false;
    }
    next = c->st;
    next.staged = target;
    if (!upc_persist(c->state_path, &next)) { /* the mark persists LAST */
        upc_clean_slot(c, target);
        c->last_error = BREAK_UPDATE_CLIENT_IO;
        return false;
    }
    c->st = next;
    c->last_error = BREAK_UPDATE_CLIENT_OK;
    return true;
}

bool break_update_client_activate(BreakUpdateClient *c) {
    UpcState next;
    u32 v[3];
    char slot;

    if (!c) return false;
    if (c->st.staged == '-') {
        c->last_error = BREAK_UPDATE_CLIENT_STATE;
        return false;
    }
    slot = c->st.staged;
    /* The staged version comes from the slot marker; missing/corrupt → fail
     * closed with the state untouched. */
    if (!upc_read_marker(c, slot, v)) {
        c->last_error = BREAK_UPDATE_CLIENT_IO;
        return false;
    }
    next = c->st;
    next.has_previous = c->st.current != '-';
    if (next.has_previous)
        memcpy(next.previous_v, c->st.current_v, sizeof(next.previous_v));
    next.current = slot;
    next.staged = '-';
    memcpy(next.current_v, v, sizeof(next.current_v));
    next.pending = true;
    next.confirmed = false;
    if (!upc_persist(c->state_path, &next)) { /* persist BEFORE the flip */
        c->last_error = BREAK_UPDATE_CLIENT_IO;
        return false;
    }
    c->st = next;
    c->last_error = BREAK_UPDATE_CLIENT_OK;
    return true;
}

bool break_update_client_unstage(BreakUpdateClient *c) {
    UpcState next;
    char slot;

    if (!c) return false;
    if (c->st.staged == '-') {
        c->last_error = BREAK_UPDATE_CLIENT_STATE;
        return false;
    }
    slot = c->st.staged;
    next = c->st;
    next.staged = '-';
    /* Write-ahead: the cleared mark persists FIRST (a crash then leaves an
     * inert tree the next stage's clean reclaims — never a staged slot whose
     * tree is gone). */
    if (!upc_persist(c->state_path, &next)) {
        c->last_error = BREAK_UPDATE_CLIENT_IO;
        return false;
    }
    c->st = next;
    /* A removal failure after the persist reports IO with staged already
     * cleared (documented): the leftover is inert, and the staged-interlock
     * no longer blocks rollback. */
    if (!upc_clean_slot(c, slot)) {
        c->last_error = BREAK_UPDATE_CLIENT_IO;
        return false;
    }
    c->last_error = BREAK_UPDATE_CLIENT_OK;
    return true;
}
