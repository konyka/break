/* break_update — Stage 5 Phase A Task 4 implementation. The contract and
 * canonical-format rules are documented in break_update.h; the trust-chain
 * position in docs/design/security_threat_model.md §4. No cryptography is
 * implemented here: hashing goes through break_crypto (OpenSSL EVP), file
 * commits through the Task 3 write-side PAL (PlatformAtomicWriter). */

#include <update/break_update.h>

#include <crypto/break_crypto.h>
#include <platform/platform_fs.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UPD_MANIFEST_MAX_BYTES (1024u * 1024u)          /* total ≤ 1 MiB */
#define UPD_MAX_CHUNKS         65536u
#define UPD_FIELD_VALUE_MAX    64u
#define UPD_CHUNK_NAME_MAX     128u
#define UPD_STORE_CHUNK_MAX    (128u * 1024u * 1024u)   /* 128 MiB (VFS_MAX_FILE_BYTES) */
#define UPD_SIG_B64_LEN        88u                      /* 86 data chars + "==" */
#define UPD_HEX_NAME_LEN       64u

/* Internal-only failure categorization. The public oracle is exactly
 * "NULL = structure invalid"; the enum lets a debugger/grep see WHICH
 * canonical rule fired, is consumed here, and never crosses the TU
 * boundary (documented decision, plan Global Constraints). */
typedef enum {
    UPD_FAIL_SIZE = 1,
    UPD_FAIL_CHARSET,
    UPD_FAIL_STRUCTURE,
    UPD_FAIL_LIMIT,
    UPD_FAIL_OOM
} UpdFailReason;

static BreakUpdateManifest *upd_parse_fail(UpdFailReason reason) {
    (void)reason;
    return NULL;
}

/* ---- line cursor --------------------------------------------------------- */

typedef struct {
    const u8 *text;
    usize len;
    usize pos;
} UpdCursor;

/* Next LF-terminated line (content excludes the LF). False at end of input;
 * the caller's final-LF pre-check makes a missing LF unreachable. */
static bool upd_next_line(UpdCursor *c, const u8 **line, usize *line_len) {
    if (c->pos >= c->len) return false;
    const u8 *start = c->text + c->pos;
    const u8 *nl = memchr(start, '\n', c->len - c->pos);
    if (!nl) return false;
    *line = start;
    *line_len = (usize)(nl - start);
    c->pos += *line_len + 1;
    return true;
}

static bool upd_starts_with(const u8 *line, usize n, const char *prefix) {
    usize p = strlen(prefix);
    return n >= p && memcmp(line, prefix, p) == 0;
}

/* ---- strict field grammars ------------------------------------------------ */

static int upd_hexval_lower(u8 c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return -1;
}

/* MAJOR.MINOR.PATCH: decimal, no leading zeros ("0" allowed), u32-range. */
static bool upd_parse_version(const u8 *s, usize n, u32 out[3]) {
    if (n == 0 || n > UPD_FIELD_VALUE_MAX) return false;
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

/* channel/platform: 1..64 chars of [a-z0-9-]. */
static bool upd_parse_tag(const u8 *s, usize n, char out[UPD_FIELD_VALUE_MAX + 1]) {
    if (n < 1 || n > UPD_FIELD_VALUE_MAX) return false;
    usize i;
    for (i = 0; i < n; i++) {
        u8 c = s[i];
        if (!((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '-'))
            return false;
    }
    memcpy(out, s, n);
    out[n] = '\0';
    return true;
}

static bool upd_parse_hash_hex(const u8 *s, usize n, u8 out[32]) {
    if (n != UPD_HEX_NAME_LEN) return false;
    usize i;
    for (i = 0; i < 32; i++) {
        int hi = upd_hexval_lower(s[2 * i]);
        int lo = upd_hexval_lower(s[2 * i + 1]);
        if (hi < 0 || lo < 0) return false;
        out[i] = (u8)((hi << 4) | lo);
    }
    return true;
}

/* Decimal u64, no leading zeros, overflow-checked. */
static bool upd_parse_u64(const u8 *s, usize n, u64 *out) {
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

/* 1..128 chars of [A-Za-z0-9._/-], no leading '/', no ".." substring. */
static bool upd_valid_chunk_name(const u8 *s, usize n) {
    if (n < 1 || n > UPD_CHUNK_NAME_MAX) return false;
    if (s[0] == '/') return false;
    usize i;
    for (i = 0; i < n; i++) {
        u8 c = s[i];
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
              (c >= '0' && c <= '9') || c == '.' || c == '_' ||
              c == '/' || c == '-'))
            return false;
        if (c == '.' && i + 1 < n && s[i + 1] == '.') return false;
    }
    return true;
}

static int upd_b64val(u8 c) {
    if (c >= 'A' && c <= 'Z') return c - 'A';
    if (c >= 'a' && c <= 'z') return c - 'a' + 26;
    if (c >= '0' && c <= '9') return c - '0' + 52;
    if (c == '+') return 62;
    if (c == '/') return 63;
    return -1;
}

/* Canonical base64 of a 64-byte signature: exactly 88 chars (86 data +
 * "=="), charset-checked, unused low 4 bits of the last data char zero. */
static bool upd_decode_signature(const u8 *s, usize n, u8 out[64]) {
    if (n != UPD_SIG_B64_LEN) return false;
    if (s[86] != '=' || s[87] != '=') return false;
    int v[86];
    usize i;
    for (i = 0; i < 86; i++) {
        v[i] = upd_b64val(s[i]);
        if (v[i] < 0) return false;
    }
    if (v[85] & 15) return false; /* non-canonical pad bits */
    for (i = 0; i < 21; i++) {    /* 84 chars → bytes 0..62 */
        out[3 * i]     = (u8)((v[4 * i] << 2) | (v[4 * i + 1] >> 4));
        out[3 * i + 1] = (u8)((v[4 * i + 1] << 4) | (v[4 * i + 2] >> 2));
        out[3 * i + 2] = (u8)((v[4 * i + 2] << 6) | v[4 * i + 3]);
    }
    out[63] = (u8)((v[84] << 2) | (v[85] >> 4));
    return true;
}

/* "chunk: <64hex> <size-dec> <name>" — exactly two separators, name = rest. */
static bool upd_parse_chunk_line(const u8 *line, usize n, u8 hash[32], u64 *size,
                                 const u8 **name, usize *name_len) {
    const usize prefix = 7; /* "chunk: " */
    if (!upd_starts_with(line, n, "chunk: ")) return false;
    usize rem = n - prefix;
    if (rem < UPD_HEX_NAME_LEN + 1 + 1 + 1) return false; /* hash sp digit sp name */
    const u8 *p = line + prefix;
    if (!upd_parse_hash_hex(p, UPD_HEX_NAME_LEN, hash)) return false;
    if (p[UPD_HEX_NAME_LEN] != ' ') return false;
    const u8 *size_s = p + UPD_HEX_NAME_LEN + 1;
    usize size_rem = rem - (UPD_HEX_NAME_LEN + 1);
    const u8 *sp = memchr(size_s, ' ', size_rem);
    if (!sp) return false;
    usize size_len = (usize)(sp - size_s);
    if (!upd_parse_u64(size_s, size_len, size)) return false;
    const u8 *nm = sp + 1;
    usize nm_len = size_rem - size_len - 1;
    if (!upd_valid_chunk_name(nm, nm_len)) return false;
    *name = nm;
    *name_len = nm_len;
    return true;
}

/* strcmp-equivalent byte order for a NUL-terminated accumulated name and a
 * raw (ptr, len) name — lexicographic, shorter-is-smaller on prefix. */
static int upd_name_cmp(const char *a, usize an, const u8 *b, usize bn) {
    usize m = an < bn ? an : bn;
    int r = m ? memcmp(a, b, m) : 0;
    if (r != 0) return r;
    if (an < bn) return -1;
    if (an > bn) return 1;
    return 0;
}

/* ---- manifest -------------------------------------------------------------- */

typedef struct {
    char *name; /* into the names arena; stable for the manifest's lifetime */
    u8 hash[32];
    u64 size;
} UpdChunkEntry;

struct BreakUpdateManifest {
    u8 *text;         /* owned copy of the full input */
    usize text_len;
    usize sig_offset; /* signed region = text[0, sig_offset) */
    u8 signature[BREAK_CRYPTO_ED25519_SIG_SIZE];
    u32 version[3];
    u32 min_version[3];
    char channel[UPD_FIELD_VALUE_MAX + 1];
    char platform[UPD_FIELD_VALUE_MAX + 1];
    UpdChunkEntry *chunks;
    char *names; /* arena: NUL-terminated names back to back */
    u64 chunk_count;
};

BreakUpdateManifest *break_update_manifest_parse(const void *text, usize len) {
    if (!text || len == 0) return upd_parse_fail(UPD_FAIL_STRUCTURE);
    if (len > UPD_MANIFEST_MAX_BYTES) return upd_parse_fail(UPD_FAIL_SIZE);
    const u8 *bytes = text;

    /* ASCII subset + LF only; the text ends with a final LF. */
    if (bytes[len - 1] != '\n') return upd_parse_fail(UPD_FAIL_CHARSET);
    usize i;
    for (i = 0; i < len; i++) {
        u8 c = bytes[i];
        if (c != '\n' && (c < 0x20 || c > 0x7E)) return upd_parse_fail(UPD_FAIL_CHARSET);
    }

    UpdCursor cur = {bytes, len, 0};
    const u8 *line;
    usize n;

    if (!upd_next_line(&cur, &line, &n)) return upd_parse_fail(UPD_FAIL_STRUCTURE);
    if (n != 17 || memcmp(line, "break-manifest-v1", 17) != 0)
        return upd_parse_fail(UPD_FAIL_STRUCTURE);

    u32 version[3], min_version[3];
    char channel[UPD_FIELD_VALUE_MAX + 1], platform[UPD_FIELD_VALUE_MAX + 1];
    if (!upd_next_line(&cur, &line, &n)) return upd_parse_fail(UPD_FAIL_STRUCTURE);
    if (!upd_starts_with(line, n, "version: ")) return upd_parse_fail(UPD_FAIL_STRUCTURE);
    if (!upd_parse_version(line + 9, n - 9, version)) return upd_parse_fail(UPD_FAIL_STRUCTURE);
    if (!upd_next_line(&cur, &line, &n)) return upd_parse_fail(UPD_FAIL_STRUCTURE);
    if (!upd_starts_with(line, n, "channel: ")) return upd_parse_fail(UPD_FAIL_STRUCTURE);
    if (!upd_parse_tag(line + 9, n - 9, channel)) return upd_parse_fail(UPD_FAIL_STRUCTURE);
    if (!upd_next_line(&cur, &line, &n)) return upd_parse_fail(UPD_FAIL_STRUCTURE);
    if (!upd_starts_with(line, n, "platform: ")) return upd_parse_fail(UPD_FAIL_STRUCTURE);
    if (!upd_parse_tag(line + 10, n - 10, platform)) return upd_parse_fail(UPD_FAIL_STRUCTURE);
    if (!upd_next_line(&cur, &line, &n)) return upd_parse_fail(UPD_FAIL_STRUCTURE);
    if (!upd_starts_with(line, n, "min-version: ")) return upd_parse_fail(UPD_FAIL_STRUCTURE);
    if (!upd_parse_version(line + 13, n - 13, min_version)) return upd_parse_fail(UPD_FAIL_STRUCTURE);

    /* Pass 1: validate everything (chunk grammar, sorted-unique names,
     * signature line, nothing after it) BEFORE any allocation sized by the
     * attacker-controlled count. */
    u64 count = 0;
    usize names_bytes = 0;
    char prev_name[UPD_CHUNK_NAME_MAX + 1];
    usize prev_len = 0;
    usize sig_offset = 0;
    u8 signature[BREAK_CRYPTO_ED25519_SIG_SIZE];
    bool have_sig = false;
    while (upd_next_line(&cur, &line, &n)) {
        if (upd_starts_with(line, n, "chunk: ")) {
            u8 h[32];
            u64 sz;
            const u8 *nm;
            usize nm_len;
            if (!upd_parse_chunk_line(line, n, h, &sz, &nm, &nm_len))
                return upd_parse_fail(UPD_FAIL_STRUCTURE);
            if (count >= UPD_MAX_CHUNKS) return upd_parse_fail(UPD_FAIL_LIMIT);
            if (prev_len && upd_name_cmp(prev_name, prev_len, nm, nm_len) >= 0)
                return upd_parse_fail(UPD_FAIL_STRUCTURE); /* unsorted or duplicate */
            memcpy(prev_name, nm, nm_len);
            prev_name[nm_len] = '\0';
            prev_len = nm_len;
            count++;
            names_bytes += nm_len + 1;
        } else if (upd_starts_with(line, n, "signature: ")) {
            if (!upd_decode_signature(line + 11, n - 11, signature))
                return upd_parse_fail(UPD_FAIL_STRUCTURE);
            sig_offset = (usize)(line - bytes);
            have_sig = true;
            break; /* the signature line must be the last line */
        } else {
            return upd_parse_fail(UPD_FAIL_STRUCTURE); /* unknown key */
        }
    }
    if (!have_sig) return upd_parse_fail(UPD_FAIL_STRUCTURE);
    if (cur.pos != cur.len) return upd_parse_fail(UPD_FAIL_STRUCTURE);

    BreakUpdateManifest *m = calloc(1, sizeof(*m));
    if (!m) return upd_parse_fail(UPD_FAIL_OOM);
    m->text = malloc(len);
    m->chunks = count ? malloc(count * sizeof(*m->chunks)) : NULL;
    m->names = names_bytes ? malloc(names_bytes) : NULL;
    if (!m->text || (count && !m->chunks) || (names_bytes && !m->names)) {
        break_update_manifest_destroy(m);
        return upd_parse_fail(UPD_FAIL_OOM);
    }
    memcpy(m->text, bytes, len);
    m->text_len = len;
    m->sig_offset = sig_offset;
    memcpy(m->signature, signature, sizeof(signature));
    memcpy(m->version, version, sizeof(version));
    memcpy(m->min_version, min_version, sizeof(min_version));
    memcpy(m->channel, channel, sizeof(channel));
    memcpy(m->platform, platform, sizeof(platform));
    m->chunk_count = count;

    /* Pass 2: fill the arrays (cannot fail — pass 1 validated every line). */
    if (count) {
        UpdCursor c2 = {bytes, len, 0};
        u64 idx = 0;
        usize name_off = 0;
        int skip;
        for (skip = 0; skip < 5; skip++) {
            if (!upd_next_line(&c2, &line, &n)) {
                break_update_manifest_destroy(m);
                return upd_parse_fail(UPD_FAIL_STRUCTURE);
            }
        }
        while (idx < count && upd_next_line(&c2, &line, &n)) {
            UpdChunkEntry *e = &m->chunks[idx];
            const u8 *nm;
            usize nm_len;
            if (!upd_parse_chunk_line(line, n, e->hash, &e->size, &nm, &nm_len)) {
                break_update_manifest_destroy(m);
                return upd_parse_fail(UPD_FAIL_STRUCTURE);
            }
            memcpy(m->names + name_off, nm, nm_len);
            m->names[name_off + nm_len] = '\0';
            e->name = m->names + name_off;
            name_off += nm_len + 1;
            idx++;
        }
        if (idx != count) {
            break_update_manifest_destroy(m);
            return upd_parse_fail(UPD_FAIL_STRUCTURE);
        }
    }
    return m;
}

bool break_update_manifest_verify(const BreakUpdateManifest *m, const u8 pubkey[32]) {
    if (!m || !pubkey) return false;
    return break_crypto_ed25519_verify(m->signature, m->text, m->sig_offset, pubkey);
}

void break_update_manifest_destroy(BreakUpdateManifest *m) {
    if (!m) return;
    free(m->text);
    free(m->chunks);
    free(m->names);
    free(m);
}

void break_update_manifest_version(const BreakUpdateManifest *m, u32 out[3]) {
    if (!m || !out) return;
    memcpy(out, m->version, sizeof(m->version));
}

void break_update_manifest_min_version(const BreakUpdateManifest *m, u32 out[3]) {
    if (!m || !out) return;
    memcpy(out, m->min_version, sizeof(m->min_version));
}

const char *break_update_manifest_channel(const BreakUpdateManifest *m) {
    return m ? m->channel : NULL;
}

const char *break_update_manifest_platform(const BreakUpdateManifest *m) {
    return m ? m->platform : NULL;
}

u64 break_update_manifest_chunk_count(const BreakUpdateManifest *m) {
    return m ? m->chunk_count : 0;
}

bool break_update_manifest_chunk_at(const BreakUpdateManifest *m, u64 index,
                                    const char **out_name, u8 out_hash[32], u64 *out_size) {
    if (!m || !out_name || !out_hash || !out_size) return false;
    if (index >= m->chunk_count) return false;
    const UpdChunkEntry *e = &m->chunks[index];
    *out_name = e->name;
    memcpy(out_hash, e->hash, sizeof(e->hash));
    *out_size = e->size;
    return true;
}

bool break_update_manifest_compatible(const BreakUpdateManifest *m, const char *channel,
                                      const char *platform, u32 cur_major, u32 cur_minor,
                                      u32 cur_patch) {
    if (!m || !channel || !platform) return false;
    if (strcmp(m->channel, channel) != 0) return false;
    if (strcmp(m->platform, platform) != 0) return false;
    u32 cur[3];
    cur[0] = cur_major;
    cur[1] = cur_minor;
    cur[2] = cur_patch;
    int i;
    for (i = 0; i < 3; i++) {
        if (cur[i] > m->min_version[i]) return true;
        if (cur[i] < m->min_version[i]) return false;
    }
    return true; /* equal triple */
}

/* ---- content-addressed store ------------------------------------------------ */

struct BreakUpdateStore {
    /* "<root>/chunks"; length bounded at open so that "/" + 64 hex + NUL fit. */
    char chunks_dir[PLATFORM_FS_PATH_CAPACITY];
};

static void upd_hex_encode(const u8 *in, usize n, char *out) {
    static const char h[] = "0123456789abcdef";
    usize i;
    for (i = 0; i < n; i++) {
        out[2 * i] = h[in[i] >> 4];
        out[2 * i + 1] = h[in[i] & 15];
    }
    out[2 * n] = '\0';
}

static bool upd_valid_hex_name(const char *name) {
    if (!name) return false;
    if (strlen(name) != UPD_HEX_NAME_LEN) return false;
    usize i;
    for (i = 0; i < UPD_HEX_NAME_LEN; i++) {
        if (upd_hexval_lower((u8)name[i]) < 0) return false;
    }
    return true;
}

static bool upd_join_chunk_path(char *out, usize cap, const char *dir, const char *name) {
    usize dn = strlen(dir);
    usize nn = strlen(name);
    if (dn + 1 + nn + 1 > cap) return false;
    memcpy(out, dir, dn);
    out[dn] = '/';
    memcpy(out + dn + 1, name, nn + 1);
    return true;
}

BreakUpdateStore *break_update_store_open(const char *root_path) {
    if (!root_path) return NULL;
    usize n = strlen(root_path);
    /* room for "/chunks" + "/" + 64 hex + NUL inside PLATFORM_FS_PATH_CAPACITY */
    if (n == 0 || n + 7 + 1 + UPD_HEX_NAME_LEN + 1 > PLATFORM_FS_PATH_CAPACITY)
        return NULL;
    if (!platform_mkdir(root_path)) return NULL;
    BreakUpdateStore *s = malloc(sizeof(*s));
    if (!s) return NULL;
    memcpy(s->chunks_dir, root_path, n);
    memcpy(s->chunks_dir + n, "/chunks", sizeof("/chunks")); /* includes NUL */
    if (!platform_mkdir(s->chunks_dir)) {
        free(s);
        return NULL;
    }
    return s;
}

void break_update_store_destroy(BreakUpdateStore *s) {
    free(s); /* free(NULL) is the abort(NULL)-style no-op */
}

bool break_update_store_put_chunk(BreakUpdateStore *s, const void *data, usize len) {
    if (!s) return false;
    if (len > UPD_STORE_CHUNK_MAX) return false; /* BEFORE touching data */
    if (!data && len) return false;
    u8 hash[BREAK_CRYPTO_SHA256_SIZE];
    if (!break_crypto_sha256(data, len, hash)) return false;
    char name[UPD_HEX_NAME_LEN + 1];
    upd_hex_encode(hash, sizeof(hash), name); /* the name IS the computed hash */
    char path[PLATFORM_FS_PATH_CAPACITY];
    if (!upd_join_chunk_path(path, sizeof(path), s->chunks_dir, name)) return false;
    PlatformAtomicWriter *w = platform_atomic_writer_open(path);
    if (!w) return false;
    if (!platform_atomic_writer_write(w, data, len)) {
        platform_atomic_writer_abort(w); /* consumes the writer */
        return false;
    }
    return platform_atomic_writer_commit(w); /* consumes the writer */
}

bool break_update_store_has_chunk(BreakUpdateStore *s, const char *sha256_hex_name) {
    if (!s || !upd_valid_hex_name(sha256_hex_name)) return false;
    char path[PLATFORM_FS_PATH_CAPACITY];
    if (!upd_join_chunk_path(path, sizeof(path), s->chunks_dir, sha256_hex_name))
        return false;
    u64 size = 0;
    return platform_file_size(path, &size); /* existence/type only, no content check */
}

bool break_update_store_get_chunk(BreakUpdateStore *s, const char *sha256_hex_name,
                                  u8 **out_buf, u64 *out_len) {
    if (!s || !out_buf || !out_len) return false;
    if (!upd_valid_hex_name(sha256_hex_name)) return false;
    char path[PLATFORM_FS_PATH_CAPACITY];
    if (!upd_join_chunk_path(path, sizeof(path), s->chunks_dir, sha256_hex_name))
        return false;
    u64 size = 0;
    if (!platform_file_size(path, &size)) return false;
    if (size > UPD_STORE_CHUNK_MAX) return false;
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
    u8 actual[BREAK_CRYPTO_SHA256_SIZE];
    u8 expect[BREAK_CRYPTO_SHA256_SIZE];
    bool ok = break_crypto_sha256(buf, (usize)size, actual) &&
              upd_parse_hash_hex((const u8 *)sha256_hex_name, UPD_HEX_NAME_LEN, expect) &&
              memcmp(actual, expect, sizeof(expect)) == 0;
    if (!ok) { /* verify-on-read: corrupted content never leaves the store */
        free(buf);
        return false;
    }
    *out_buf = buf;
    *out_len = size;
    return true;
}

bool break_update_rollout_bucket(const char *device_id, const u32 version[3],
                                 u32 *out_bucket) {
    char msg[32 + BREAK_UPDATE_ROLLOUT_DEVICE_ID_MAX + 48];
    u8 digest[BREAK_CRYPTO_SHA256_SIZE];
    usize id_len;
    int n;
    if (device_id == NULL || version == NULL || out_bucket == NULL) {
        return false;
    }
    id_len = strlen(device_id);
    if (id_len == 0u || id_len > BREAK_UPDATE_ROLLOUT_DEVICE_ID_MAX) {
        return false;
    }
    n = snprintf(msg, sizeof(msg), "break-rollout-v1\n%s\n%u.%u.%u", device_id,
                 (unsigned)version[0], (unsigned)version[1],
                 (unsigned)version[2]);
    if (n <= 0 || (usize)n >= sizeof(msg) ||
        !break_crypto_sha256(msg, (usize)n, digest)) {
        return false;
    }
    *out_bucket = (((u32)digest[0] << 24) | ((u32)digest[1] << 16) |
                   ((u32)digest[2] << 8) | (u32)digest[3]) %
                  BREAK_UPDATE_ROLLOUT_BUCKETS;
    return true;
}

bool break_update_rollout_admits(u32 bucket, u32 percent_bp) {
    if (bucket >= BREAK_UPDATE_ROLLOUT_BUCKETS) return false;
    if (percent_bp > BREAK_UPDATE_ROLLOUT_BUCKETS) {
        percent_bp = BREAK_UPDATE_ROLLOUT_BUCKETS;
    }
    return bucket < percent_bp;
}

bool break_update_rollout_listed(const char *device_id, const char *list, usize len,
                                 bool *out_listed) {
    usize id_len, pos = 0u;
    bool found = false;
    if (device_id == NULL || out_listed == NULL || (list == NULL && len > 0u) ||
        len > BREAK_UPDATE_ROLLOUT_LIST_MAX) {
        return false;
    }
    id_len = strlen(device_id);
    if (id_len == 0u || id_len > BREAK_UPDATE_ROLLOUT_DEVICE_ID_MAX) return false;
    /* validate the whole list first: a malformed list is never half-applied */
    while (pos < len) {
        usize end = pos;
        while (end < len && list[end] != '\n') {
            if (list[end] == '\r') return false;
            end++;
        }
        if (end - pos > BREAK_UPDATE_ROLLOUT_DEVICE_ID_MAX) return false;
        if (end - pos == id_len && memcmp(list + pos, device_id, id_len) == 0) found = true;
        pos = end + 1u;
    }
    *out_listed = found;
    return true;
}
