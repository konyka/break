#define _POSIX_C_SOURCE 200809L
#define _DEFAULT_SOURCE
#include <crash/break_crash_cluster.h>

#include <crypto/break_crypto.h>
#include <platform/platform_fs.h>

#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <unistd.h>

#define HEADER "break-crash-stats v1\n"

typedef struct {
    char sig[65];
    u64 count;
    u32 first_build;
    u32 last_build;    /* the latest-released build that reported it */
    i32 fixed_build;   /* -1 = never marked fixed */
    bool regressed;
    char symbol[BREAK_CRASH_CLUSTER_SYMBOL_MAX + 1u]; /* "" = none */
} Cluster;

struct BreakCrashClusterStore {
    u32 build_count;
    u32 seen_count;
    u32 sig_count;
    char builds[BREAK_CRASH_CLUSTER_MAX_BUILDS][65];
    char seen[BREAK_CRASH_CLUSTER_MAX_SEEN][65];
    Cluster sigs[BREAK_CRASH_CLUSTER_MAX_SIGNATURES];   /* sorted by sig, ascending */
};

/* ---------------------------------------------------------------- validation */

static bool is_hex64(const char *s) {
    if (s == NULL) return false;
    for (usize i = 0u; i < 64u; i++) {
        char c = s[i];
        if (!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f'))) return false;
    }
    return s[64] == '\0';
}

static bool build_id_ok(const char *id) {
    usize n;
    if (id == NULL) return false;
    n = strlen(id);
    if (n == 0u || n > 64u) return false;
    for (usize i = 0u; i < n; i++) {
        char c = id[i];
        if (!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || c == '-')) return false;
    }
    return true;
}

static void sanitize_symbol(const char *in, char out[BREAK_CRASH_CLUSTER_SYMBOL_MAX + 1u]) {
    usize n = 0u;
    if (in != NULL) {
        for (; in[n] != '\0' && n < BREAK_CRASH_CLUSTER_SYMBOL_MAX; n++) {
            unsigned char c = (unsigned char)in[n];
            out[n] = (c >= 0x21u && c <= 0x7eu) ? (char)c : '?';
        }
    }
    out[n] = '\0';
    if (strcmp(out, "-") == 0) out[0] = '\0';   /* "-" is the file's spelling of "none" */
}

/* ----------------------------------------------------------------- signature */

typedef struct { char *p; usize cap, len; bool bad; } Buf;

static void bput(Buf *b, const char *fmt, ...) {
    va_list ap;
    int n;
    if (b->bad) return;
    va_start(ap, fmt);
    n = vsnprintf(b->p + b->len, b->cap - b->len, fmt, ap);
    va_end(ap);
    if (n < 0 || (usize)n >= b->cap - b->len) {
        b->bad = true;
        return;
    }
    b->len += (usize)n;
}

bool break_crash_signature(int signo, const BreakCrashFrame *frames, u32 n, char out_hex[65]) {
    char text[1024];
    Buf b = {text, sizeof(text), 0u, false};
    u8 digest[32];
    static const char hex[] = "0123456789abcdef";
    if (out_hex == NULL || signo < 1 || signo > 64 || (n > 0u && frames == NULL)) return false;
    bput(&b, "break-crash-sig-v1\nsigno=%d\n", signo);
    for (u32 i = 0u; i < n && i < 3u; i++) {
        const BreakCrashFrame *f = &frames[i];
        if (f->resolved && f->symbol[0] != '\0') {
            bput(&b, "f:%.255s!%.127s\n", f->module, f->symbol);
        } else if (f->module[0] != '\0') {
            bput(&b, "m:%.255s+%llx\n", f->module, (unsigned long long)f->module_offset);
        } else {
            bput(&b, "?\n");
        }
    }
    if (b.bad || !break_crypto_sha256(text, b.len, digest)) return false;
    for (usize i = 0u; i < 32u; i++) {
        out_hex[2u * i] = hex[digest[i] >> 4];
        out_hex[2u * i + 1u] = hex[digest[i] & 0xfu];
    }
    out_hex[64] = '\0';
    return true;
}

/* --------------------------------------------------------------------- store */

static BreakCrashClusterStore *store_new(void) {
    return (BreakCrashClusterStore *)calloc(1u, sizeof(BreakCrashClusterStore));
}

void break_crash_cluster_destroy(BreakCrashClusterStore *s) {
    free(s);
}

static i32 find_build(const BreakCrashClusterStore *s, const char *id) {
    for (u32 i = 0u; i < s->build_count; i++) {
        if (strcmp(s->builds[i], id) == 0) return (i32)i;
    }
    return -1;
}

bool break_crash_cluster_build_known(const BreakCrashClusterStore *s, const char *build_id) {
    return s != NULL && build_id_ok(build_id) && find_build(s, build_id) >= 0;
}

bool break_crash_cluster_register_build(BreakCrashClusterStore *s, const char *build_id) {
    if (s == NULL || !build_id_ok(build_id) || s->build_count >= BREAK_CRASH_CLUSTER_MAX_BUILDS ||
        find_build(s, build_id) >= 0) {
        return false;
    }
    memcpy(s->builds[s->build_count], build_id, strlen(build_id) + 1u);
    s->build_count++;
    return true;
}

/* index of the first cluster whose sig >= key; *found when equal */
static u32 sig_lower_bound(const BreakCrashClusterStore *s, const char *sig, bool *found) {
    u32 lo = 0u, hi = s->sig_count;
    while (lo < hi) {
        u32 mid = lo + (hi - lo) / 2u;
        if (strcmp(s->sigs[mid].sig, sig) < 0) lo = mid + 1u; else hi = mid;
    }
    *found = lo < s->sig_count && strcmp(s->sigs[lo].sig, sig) == 0;
    return lo;
}

static void sig_remove(BreakCrashClusterStore *s, u32 at) {
    memmove(&s->sigs[at], &s->sigs[at + 1u], (usize)(s->sig_count - at - 1u) * sizeof(Cluster));
    s->sig_count--;
}

bool break_crash_cluster_add(BreakCrashClusterStore *s, const char *record_hash_hex,
                             const char *signature_hex, const char *build_id,
                             const char *top_symbol, BreakCrashClusterOutcome *out) {
    BreakCrashClusterOutcome local;
    BreakCrashClusterOutcome *o = out != NULL ? out : &local;
    i32 build;
    bool found;
    u32 at;
    Cluster *c;
    memset(o, 0, sizeof(*o));
    if (s == NULL || !is_hex64(record_hash_hex) || !is_hex64(signature_hex) || !build_id_ok(build_id)) {
        return false;
    }
    build = find_build(s, build_id);
    if (build < 0) {
        o->unknown_build = true;
        return false;
    }
    for (u32 i = 0u; i < s->seen_count; i++) {
        if (strcmp(s->seen[i], record_hash_hex) == 0) {
            at = sig_lower_bound(s, signature_hex, &found);
            o->duplicate = true;
            o->count = found ? s->sigs[at].count : 0u;
            return true;
        }
    }
    if (s->seen_count == BREAK_CRASH_CLUSTER_MAX_SEEN) {
        memmove(s->seen[0], s->seen[1], (usize)(BREAK_CRASH_CLUSTER_MAX_SEEN - 1u) * sizeof(s->seen[0]));
        s->seen_count--;
    }
    memcpy(s->seen[s->seen_count++], record_hash_hex, 65u);

    at = sig_lower_bound(s, signature_hex, &found);
    if (!found) {
        if (s->sig_count == BREAK_CRASH_CLUSTER_MAX_SIGNATURES) {
            u32 victim = 0u;
            for (u32 i = 1u; i < s->sig_count; i++) {
                if (s->sigs[i].count < s->sigs[victim].count) victim = i;
            }
            sig_remove(s, victim);
            at = sig_lower_bound(s, signature_hex, &found);
        }
        memmove(&s->sigs[at + 1u], &s->sigs[at], (usize)(s->sig_count - at) * sizeof(Cluster));
        s->sig_count++;
        c = &s->sigs[at];
        memset(c, 0, sizeof(*c));
        memcpy(c->sig, signature_hex, 65u);
        c->count = 1u;
        c->first_build = (u32)build;
        c->last_build = (u32)build;
        c->fixed_build = -1;
        sanitize_symbol(top_symbol, c->symbol);
        o->new_signature = true;
    } else {
        c = &s->sigs[at];
        if (c->count < UINT64_MAX) c->count++;
        if ((u32)build > c->last_build) c->last_build = (u32)build;
    }
    if (c->fixed_build >= 0 && build > c->fixed_build && !c->regressed) {
        c->regressed = true;
        o->regression_started = true;
    }
    o->count = c->count;
    return true;
}

bool break_crash_cluster_mark_fixed(BreakCrashClusterStore *s, const char *signature_hex,
                                    const char *build_id) {
    bool found;
    u32 at;
    i32 build;
    if (s == NULL || !is_hex64(signature_hex) || !build_id_ok(build_id)) return false;
    build = find_build(s, build_id);
    if (build < 0) return false;
    at = sig_lower_bound(s, signature_hex, &found);
    if (!found) return false;
    s->sigs[at].fixed_build = build;
    s->sigs[at].regressed = (i32)s->sigs[at].last_build > build;   /* later builds already reported it */
    return true;
}

bool break_crash_cluster_find(const BreakCrashClusterStore *s, const char *signature_hex, u64 *out_count,
                              bool *out_regressed) {
    bool found;
    u32 at;
    if (s == NULL || !is_hex64(signature_hex)) return false;
    at = sig_lower_bound(s, signature_hex, &found);
    if (!found) return false;
    if (out_count != NULL) *out_count = s->sigs[at].count;
    if (out_regressed != NULL) *out_regressed = s->sigs[at].regressed;
    return true;
}

u32 break_crash_cluster_signature_count(const BreakCrashClusterStore *s) {
    return s != NULL ? s->sig_count : 0u;
}

u32 break_crash_cluster_build_count(const BreakCrashClusterStore *s) {
    return s != NULL ? s->build_count : 0u;
}

/* ------------------------------------------------------------ canonical text */

usize break_crash_cluster_serialize(const BreakCrashClusterStore *s, char *out, usize cap) {
    Buf b;
    if (s == NULL || out == NULL || cap == 0u) return 0u;
    b.p = out;
    b.cap = cap;
    b.len = 0u;
    b.bad = false;
    bput(&b, HEADER);
    bput(&b, "builds: %u\n", s->build_count);
    for (u32 i = 0u; i < s->build_count; i++) bput(&b, "build: %s\n", s->builds[i]);
    bput(&b, "seen: %u\n", s->seen_count);
    for (u32 i = 0u; i < s->seen_count; i++) bput(&b, "seen: %s\n", s->seen[i]);
    bput(&b, "signatures: %u\n", s->sig_count);
    for (u32 i = 0u; i < s->sig_count; i++) {
        const Cluster *c = &s->sigs[i];
        char fixed[16];
        if (c->fixed_build >= 0) snprintf(fixed, sizeof(fixed), "%d", (int)c->fixed_build);
        else snprintf(fixed, sizeof(fixed), "-");
        bput(&b, "sig: %s %llu %u %u %s %d %s\n", c->sig, (unsigned long long)c->count, c->first_build,
             c->last_build, fixed,
             c->regressed ? 1 : 0, c->symbol[0] != '\0' ? c->symbol : "-");
    }
    return b.bad ? 0u : b.len;
}

typedef struct { const char *p; usize left; } Cur;

/* next line without its '\n'; false when there is no terminated line */
static bool next_line(Cur *c, const char **line, usize *n) {
    const char *nl = c->left > 0u ? (const char *)memchr(c->p, '\n', c->left) : NULL;
    if (nl == NULL) return false;
    *line = c->p;
    *n = (usize)(nl - c->p);
    c->left -= *n + 1u;
    c->p = nl + 1;
    return true;
}

static bool parse_u64(const char *s, usize n, u64 *out) {
    u64 v = 0u;
    if (n == 0u || n > 20u) return false;
    for (usize i = 0u; i < n; i++) {
        unsigned d;
        if (s[i] < '0' || s[i] > '9') return false;
        d = (unsigned)(s[i] - '0');
        if (v > (UINT64_MAX - d) / 10u) return false;
        v = v * 10u + d;
    }
    *out = v;
    return true;
}

static bool expect_count(Cur *c, const char *label, u64 max, u32 *out) {
    const char *line;
    usize n, ll = strlen(label);
    u64 v;
    if (!next_line(c, &line, &n) || n <= ll || memcmp(line, label, ll) != 0 || !parse_u64(line + ll, n - ll, &v) ||
        v > max) {
        return false;
    }
    *out = (u32)v;
    return true;
}

/* "<label><value>" where value is copied NUL-terminated into out (cap bytes) */
static bool expect_text(Cur *c, const char *label, char *out, usize cap) {
    const char *line;
    usize n, ll = strlen(label);
    if (!next_line(c, &line, &n) || n <= ll || n - ll >= cap || memcmp(line, label, ll) != 0) return false;
    memcpy(out, line + ll, n - ll);
    out[n - ll] = '\0';
    return true;
}

BreakCrashClusterStore *break_crash_cluster_parse(const char *text, usize len) {
    BreakCrashClusterStore *s;
    Cur c;
    u32 nb, ns, nsig;
    char *again = NULL;
    usize again_len;
    if (text == NULL || len == 0u || len > BREAK_CRASH_CLUSTER_FILE_MAX) return NULL;
    s = store_new();
    if (s == NULL) return NULL;
    c.p = text;
    c.left = len;
    {
        const char *line;
        usize n;
        if (!next_line(&c, &line, &n) || n + 1u != sizeof(HEADER) - 1u || memcmp(line, HEADER, n) != 0) goto bad;
    }
    if (!expect_count(&c, "builds: ", BREAK_CRASH_CLUSTER_MAX_BUILDS, &nb)) goto bad;
    for (u32 i = 0u; i < nb; i++) {
        char id[65];
        if (!expect_text(&c, "build: ", id, sizeof(id)) || !build_id_ok(id)) goto bad;
        if (!break_crash_cluster_register_build(s, id)) goto bad;
    }
    if (!expect_count(&c, "seen: ", BREAK_CRASH_CLUSTER_MAX_SEEN, &ns)) goto bad;
    for (u32 i = 0u; i < ns; i++) {
        if (!expect_text(&c, "seen: ", s->seen[i], sizeof(s->seen[i])) || !is_hex64(s->seen[i])) goto bad;
    }
    s->seen_count = ns;
    if (!expect_count(&c, "signatures: ", BREAK_CRASH_CLUSTER_MAX_SIGNATURES, &nsig)) goto bad;
    for (u32 i = 0u; i < nsig; i++) {
        const char *line;
        usize n;
        Cluster *cl = &s->sigs[i];
        char tmp[320], *tok[7], *save;
        u64 v;
        int t = 0;
        if (!next_line(&c, &line, &n) || n < 5u || n >= sizeof(tmp) || memcmp(line, "sig: ", 5) != 0) goto bad;
        memcpy(tmp, line + 5, n - 5u);
        tmp[n - 5u] = '\0';
        for (char *p = strtok_r(tmp, " ", &save); p != NULL && t < 8; p = strtok_r(NULL, " ", &save)) {
            if (t < 7) tok[t] = p;
            t++;
        }
        if (t != 7 || !is_hex64(tok[0])) goto bad;
        memcpy(cl->sig, tok[0], 65u);
        if (!parse_u64(tok[1], strlen(tok[1]), &cl->count) || !parse_u64(tok[2], strlen(tok[2]), &v) ||
            v >= nb) {
            goto bad;
        }
        cl->first_build = (u32)v;
        if (!parse_u64(tok[3], strlen(tok[3]), &v) || v >= nb || v < cl->first_build) goto bad;
        cl->last_build = (u32)v;
        if (strcmp(tok[4], "-") == 0) {
            cl->fixed_build = -1;
        } else {
            if (!parse_u64(tok[4], strlen(tok[4]), &v) || v >= nb) goto bad;
            cl->fixed_build = (i32)v;
        }
        if (strcmp(tok[5], "0") == 0) cl->regressed = false;
        else if (strcmp(tok[5], "1") == 0) cl->regressed = true;
        else goto bad;
        if (strcmp(tok[6], "-") == 0) {
            cl->symbol[0] = '\0';
        } else {
            sanitize_symbol(tok[6], cl->symbol);
        }
        if (i > 0u && strcmp(s->sigs[i - 1u].sig, cl->sig) >= 0) goto bad;   /* strictly ascending */
    }
    s->sig_count = nsig;
    if (c.left != 0u) goto bad;
    /* canonical form: the text must be exactly what the serializer produces */
    again = (char *)malloc(len + 1u);
    if (again == NULL) goto bad;
    again_len = break_crash_cluster_serialize(s, again, len + 1u);
    if (again_len != len || memcmp(again, text, len) != 0) goto bad;
    free(again);
    return s;
bad:
    free(again);
    free(s);
    return NULL;
}

/* -------------------------------------------------------------------- files */

BreakCrashClusterStore *break_crash_cluster_open(const char *path) {
    FILE *f;
    struct stat sb;
    char *buf;
    BreakCrashClusterStore *s;
    if (path == NULL || path[0] == '\0') return NULL;
    f = fopen(path, "rb");
    if (f == NULL) return errno == ENOENT ? store_new() : NULL;
    if (fstat(fileno(f), &sb) != 0 || !S_ISREG(sb.st_mode) || sb.st_size <= 0 ||
        (u64)sb.st_size > BREAK_CRASH_CLUSTER_FILE_MAX) {
        fclose(f);
        return NULL;   /* empty, not a regular file or oversized: not a statistics file */
    }
    buf = (char *)malloc((usize)sb.st_size);
    if (buf == NULL || fread(buf, 1u, (usize)sb.st_size, f) != (usize)sb.st_size) {
        fclose(f);
        free(buf);
        return NULL;
    }
    fclose(f);
    s = break_crash_cluster_parse(buf, (usize)sb.st_size);
    free(buf);
    return s;
}

bool break_crash_cluster_save(const BreakCrashClusterStore *s, const char *path) {
    char *buf;
    usize n;
    PlatformAtomicWriter *w;
    if (s == NULL || path == NULL || path[0] == '\0') return false;
    buf = (char *)malloc(BREAK_CRASH_CLUSTER_FILE_MAX);
    if (buf == NULL) return false;
    n = break_crash_cluster_serialize(s, buf, BREAK_CRASH_CLUSTER_FILE_MAX);
    if (n == 0u) {
        free(buf);
        return false;
    }
    w = platform_atomic_writer_open(path);
    if (w == NULL) {
        free(buf);
        return false;
    }
    if (!platform_atomic_writer_write(w, buf, n)) {
        platform_atomic_writer_abort(w);
        free(buf);
        return false;
    }
    free(buf);
    return platform_atomic_writer_commit(w);
}

/* ------------------------------------------------------------------- report */

usize break_crash_cluster_report(const BreakCrashClusterStore *s, char *out, usize cap) {
    u32 *order;
    Buf b;
    if (s == NULL || out == NULL || cap == 0u) return 0u;
    order = (u32 *)malloc((usize)(s->sig_count ? s->sig_count : 1u) * sizeof(u32));
    if (order == NULL) return 0u;
    for (u32 i = 0u; i < s->sig_count; i++) {
        u32 j = i;
        while (j > 0u) {
            const Cluster *a = &s->sigs[order[j - 1u]], *x = &s->sigs[i];
            if (a->count > x->count || (a->count == x->count && strcmp(a->sig, x->sig) < 0)) break;
            order[j] = order[j - 1u];
            j--;
        }
        order[j] = i;
    }
    b.p = out;
    b.cap = cap;
    b.len = 0u;
    b.bad = false;
    bput(&b, "crash clusters: %u signatures, %u builds\n", s->sig_count, s->build_count);
    for (u32 i = 0u; i < s->sig_count; i++) {
        const Cluster *c = &s->sigs[order[i]];
        bput(&b, "%llu %.16s%s first=%s fixed=%s top=%s\n", (unsigned long long)c->count, c->sig,
             c->regressed ? " REGRESSED" : "", s->builds[c->first_build],
             c->fixed_build >= 0 ? s->builds[c->fixed_build] : "-", c->symbol[0] != '\0' ? c->symbol : "-");
    }
    free(order);
    return b.bad ? 0u : b.len;
}

/* --------------------------------------------------------------------- lock */

struct BreakCrashClusterLock { int fd; };

BreakCrashClusterLock *break_crash_cluster_lock(const char *path) {
    char lp[PLATFORM_FS_PATH_CAPACITY + 8u];
    BreakCrashClusterLock *l;
    int fd, n;
    if (path == NULL || path[0] == '\0') return NULL;
    n = snprintf(lp, sizeof(lp), "%s.lock", path);
    if (n <= 0 || (usize)n >= sizeof(lp)) return NULL;
    fd = open(lp, O_RDWR | O_CREAT | O_CLOEXEC | O_NOFOLLOW, 0600);
    if (fd < 0) return NULL;
    while (flock(fd, LOCK_EX) != 0) {
        if (errno != EINTR) {
            close(fd);
            return NULL;
        }
    }
    l = (BreakCrashClusterLock *)malloc(sizeof(*l));
    if (l == NULL) {
        close(fd);
        return NULL;
    }
    l->fd = fd;
    return l;
}

void break_crash_cluster_unlock(BreakCrashClusterLock *l) {
    if (l == NULL) return;
    (void)flock(l->fd, LOCK_UN);
    close(l->fd);
    free(l);
}
