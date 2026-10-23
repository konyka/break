/* break_update_client — Stage 5 Phase B Task 1 implementation. The contract
 * (on-disk layout, canonical state format, write-ahead discipline, rollback
 * policy, error enum semantics) is documented in break_update_client.h; the
 * parser deliberately mirrors the Phase A manifest discipline in
 * break_update.c (strict grammars, unknown/malformed → fail, no repair).
 * No download/stage/activate code exists here yet (Tasks 2/3). */

#include <update/break_update_client.h>

#include <platform/platform_fs.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPC_STATE_MAX_BYTES (64u * 1024u) /* state file ≤ 64 KiB */
#define UPC_HEX_NAME_LEN    64u
#define UPC_TEXT_CAP        512u /* worst-case serialized state ≈ 324 bytes */

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
    /* Tightest suffix: "/state" + the atomic writer's ".tmpXXXXXX" + NUL
     * (covers "/slots/A" too). Checked once up front so every later join is
     * safe by construction. */
    if (n == 0 || n + 6 + 10 + 1 > PLATFORM_FS_PATH_CAPACITY) return NULL;
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
