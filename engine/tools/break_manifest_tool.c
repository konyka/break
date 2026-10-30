/* break_manifest_tool — OFFLINE release tooling for signed update manifests
 * (docs/design/update_client.md §11 item 4, security_threat_model.md §4).
 * Runs on the release machine only: the client never links a signer
 * (break_crypto is verify-only by contract).
 *
 *   keygen <private key file> <public key hex file>
 *       Fresh Ed25519 key pair. The private file holds the 32-byte raw seed
 *       (created exclusively, mode 0600 — an existing key is never
 *       overwritten); the public file holds 64 lowercase hex chars + LF, the
 *       value to compile into the client as its trusted key.
 *   build <dir> <version> <channel> <platform> <min-version> <body out>
 *       The canonical unsigned body (everything before "signature:") for
 *       every regular file under <dir>: one "chunk: <sha256> <size> <name>"
 *       line per file, names relative with '/', sorted byte-wise.
 *   sign <private key file> <body file> <manifest out>
 *       Appends the Ed25519 signature line over the body bytes. The body
 *       must already be a structurally valid manifest prefix: the tool
 *       re-parses body + signature with the client's grammar rules before
 *       writing, so it never emits a manifest the client would reject.
 *
 * Exit 0 on success, 1 on failure, 2 on usage. Key bytes are wiped. */
#define _POSIX_C_SOURCE 200809L
#include <openssl/evp.h>

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define MT_MAX_MANIFEST (1024u * 1024u)
#define MT_MAX_FILES 4096u
#define MT_MAX_NAME 128u

static void mt_wipe(void *p, size_t n) {
    volatile unsigned char *v = (volatile unsigned char *)p;
    while (n-- > 0u) *v++ = 0u;
}

static int mt_field_ok(const char *s) { /* [a-z0-9-], 1..64 */
    size_t i, n = strlen(s);
    if (n == 0u || n > 64u) return 0;
    for (i = 0u; i < n; i++) {
        char c = s[i];
        if (!((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '-')) return 0;
    }
    return 1;
}

static int mt_num_ok(const char *s, size_t n) { /* decimal u32, no leading zero */
    size_t i;
    unsigned long long v = 0u;
    if (n == 0u || n > 10u || (n > 1u && s[0] == '0')) return 0;
    for (i = 0u; i < n; i++) {
        if (s[i] < '0' || s[i] > '9') return 0;
        v = v * 10u + (unsigned)(s[i] - '0');
    }
    return v <= 0xffffffffull;
}

static int mt_version_ok(const char *s) {
    const char *a = strchr(s, '.'), *b;
    if (a == NULL) return 0;
    b = strchr(a + 1, '.');
    if (b == NULL || strchr(b + 1, '.') != NULL) return 0;
    return mt_num_ok(s, (size_t)(a - s)) && mt_num_ok(a + 1, (size_t)(b - a - 1)) &&
           mt_num_ok(b + 1, strlen(b + 1));
}

static int mt_name_ok(const char *n) {
    size_t i, len = strlen(n);
    if (len == 0u || len > MT_MAX_NAME || n[0] == '/' || strstr(n, "..") != NULL) return 0;
    for (i = 0u; i < len; i++) {
        char c = n[i];
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') ||
              c == '.' || c == '_' || c == '/' || c == '-'))
            return 0;
    }
    return 1;
}

/* ---------------- keygen ---------------- */

static int mt_keygen(const char *priv_path, const char *pub_path) {
    static const char hex[] = "0123456789abcdef";
    EVP_PKEY *key = NULL;
    EVP_PKEY_CTX *ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_ED25519, NULL);
    unsigned char seed[32], pub[32];
    size_t seed_len = sizeof(seed), pub_len = sizeof(pub), i;
    char pub_hex[65];
    int fd, ok = 0;
    FILE *f;
    if (ctx == NULL || EVP_PKEY_keygen_init(ctx) <= 0 || EVP_PKEY_keygen(ctx, &key) <= 0 ||
        EVP_PKEY_get_raw_private_key(key, seed, &seed_len) <= 0 || seed_len != 32u ||
        EVP_PKEY_get_raw_public_key(key, pub, &pub_len) <= 0 || pub_len != 32u) {
        fprintf(stderr, "break_manifest_tool: key generation failed\n");
        goto out;
    }
    fd = open(priv_path, O_CREAT | O_EXCL | O_WRONLY, 0600);
    if (fd < 0) {
        fprintf(stderr, "break_manifest_tool: cannot create '%s' (an existing key is never overwritten)\n",
                priv_path);
        goto out;
    }
    ok = write(fd, seed, sizeof(seed)) == (ssize_t)sizeof(seed);
    if (close(fd) != 0) ok = 0;
    if (!ok) {
        (void)remove(priv_path);
        fprintf(stderr, "break_manifest_tool: writing the private key failed\n");
        goto out;
    }
    for (i = 0u; i < 32u; i++) {
        pub_hex[2u * i] = hex[pub[i] >> 4];
        pub_hex[2u * i + 1u] = hex[pub[i] & 15u];
    }
    pub_hex[64] = '\0';
    f = fopen(pub_path, "wb");
    ok = f != NULL && fprintf(f, "%s\n", pub_hex) == 65;
    if (f != NULL && fclose(f) != 0) ok = 0;
    if (!ok) {
        (void)remove(priv_path);
        fprintf(stderr, "break_manifest_tool: writing the public key failed\n");
        goto out;
    }
    printf("break_manifest_tool: public key %s\n", pub_hex);
out:
    mt_wipe(seed, sizeof(seed));
    EVP_PKEY_free(key);
    EVP_PKEY_CTX_free(ctx);
    return ok ? 0 : 1;
}

/* ---------------- build ---------------- */

typedef struct {
    char name[MT_MAX_NAME + 1u];
} MtFile;

static MtFile *g_files;
static unsigned g_file_count;

static int mt_walk(const char *root, const char *rel) {
    char path[4096];
    DIR *d;
    struct dirent *e;
    int ok = 1;
    snprintf(path, sizeof(path), "%s%s%s", root, rel[0] ? "/" : "", rel);
    d = opendir(path);
    if (d == NULL) return 0;
    while (ok && (e = readdir(d)) != NULL) {
        char child_rel[MT_MAX_NAME + 2u];
        char child[4096];
        struct stat st;
        if (strcmp(e->d_name, ".") == 0 || strcmp(e->d_name, "..") == 0) continue;
        if ((size_t)snprintf(child_rel, sizeof(child_rel), "%s%s%s", rel, rel[0] ? "/" : "",
                             e->d_name) >= sizeof(child_rel)) {
            fprintf(stderr, "break_manifest_tool: name too long under %s\n", path);
            ok = 0;
            break;
        }
        snprintf(child, sizeof(child), "%s/%s", root, child_rel);
        if (lstat(child, &st) != 0) {
            ok = 0;
        } else if (S_ISDIR(st.st_mode)) {
            ok = mt_walk(root, child_rel);
        } else if (S_ISREG(st.st_mode)) {
            if (!mt_name_ok(child_rel) || g_file_count >= MT_MAX_FILES) {
                fprintf(stderr, "break_manifest_tool: unsupported file name or too many files: %s\n",
                        child_rel);
                ok = 0;
            } else {
                memcpy(g_files[g_file_count++].name, child_rel, strlen(child_rel) + 1u);
            }
        } else {
            fprintf(stderr, "break_manifest_tool: not a regular file: %s\n", child_rel);
            ok = 0;
        }
    }
    closedir(d);
    return ok;
}

static int mt_name_cmp(const void *a, const void *b) {
    return strcmp(((const MtFile *)a)->name, ((const MtFile *)b)->name);
}

static int mt_hash_file(const char *path, unsigned char out[32], unsigned long long *size) {
    unsigned char buf[65536];
    EVP_MD_CTX *md = EVP_MD_CTX_new();
    FILE *f = fopen(path, "rb");
    size_t n;
    unsigned len = 0u;
    int ok = md != NULL && f != NULL && EVP_DigestInit_ex(md, EVP_sha256(), NULL) == 1;
    *size = 0u;
    while (ok && (n = fread(buf, 1u, sizeof(buf), f)) > 0u) {
        ok = EVP_DigestUpdate(md, buf, n) == 1;
        *size += n;
    }
    if (ok && f != NULL && ferror(f)) ok = 0;
    if (ok) ok = EVP_DigestFinal_ex(md, out, &len) == 1 && len == 32u;
    if (f != NULL) fclose(f);
    EVP_MD_CTX_free(md);
    return ok;
}

static int mt_build(char **a) {
    static const char hex[] = "0123456789abcdef";
    const char *dir = a[0], *version = a[1], *channel = a[2], *platform = a[3],
               *min_version = a[4], *out_path = a[5];
    FILE *out;
    unsigned i;
    int ok = 1;
    if (!mt_version_ok(version) || !mt_version_ok(min_version) || !mt_field_ok(channel) ||
        !mt_field_ok(platform)) {
        fprintf(stderr, "break_manifest_tool: versions must be MAJOR.MINOR.PATCH and channel/"
                        "platform 1..64 chars of [a-z0-9-]\n");
        return 1;
    }
    g_files = (MtFile *)calloc(MT_MAX_FILES, sizeof(MtFile));
    g_file_count = 0u;
    if (g_files == NULL || !mt_walk(dir, "")) {
        free(g_files);
        fprintf(stderr, "break_manifest_tool: cannot list '%s'\n", dir);
        return 1;
    }
    qsort(g_files, g_file_count, sizeof(MtFile), mt_name_cmp);
    out = fopen(out_path, "wb");
    if (out == NULL) {
        free(g_files);
        return 1;
    }
    fprintf(out, "break-manifest-v1\nversion: %s\nchannel: %s\nplatform: %s\nmin-version: %s\n",
            version, channel, platform, min_version);
    for (i = 0u; ok && i < g_file_count; i++) {
        char path[4096], digest_hex[65];
        unsigned char digest[32];
        unsigned long long size;
        unsigned k;
        snprintf(path, sizeof(path), "%s/%s", dir, g_files[i].name);
        if (!mt_hash_file(path, digest, &size)) {
            fprintf(stderr, "break_manifest_tool: cannot hash %s\n", path);
            ok = 0;
            break;
        }
        for (k = 0u; k < 32u; k++) {
            digest_hex[2u * k] = hex[digest[k] >> 4];
            digest_hex[2u * k + 1u] = hex[digest[k] & 15u];
        }
        digest_hex[64] = '\0';
        fprintf(out, "chunk: %s %llu %s\n", digest_hex, size, g_files[i].name);
    }
    if (fclose(out) != 0) ok = 0;
    free(g_files);
    if (!ok) (void)remove(out_path);
    else printf("break_manifest_tool: %u chunks\n", g_file_count);
    return ok ? 0 : 1;
}

/* ---------------- sign ---------------- */

static void mt_base64(const unsigned char in[64], char out[89]) {
    static const char t[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    unsigned i, o = 0u;
    for (i = 0u; i + 3u <= 63u; i += 3u) {
        unsigned v = ((unsigned)in[i] << 16) | ((unsigned)in[i + 1u] << 8) | in[i + 2u];
        out[o++] = t[(v >> 18) & 63u];
        out[o++] = t[(v >> 12) & 63u];
        out[o++] = t[(v >> 6) & 63u];
        out[o++] = t[v & 63u];
    }
    /* last byte (64 = 21*3 + 1): two chars + "==" */
    out[o++] = t[in[63] >> 2];
    out[o++] = t[(in[63] & 3u) << 4];
    out[o++] = '=';
    out[o++] = '=';
    out[o] = '\0';
}

/* Structural check of the unsigned body: header in order, chunk lines well
 * formed and strictly sorted. Mirrors the client grammar so the tool never
 * signs something the client rejects (the client re-checks everything). */
static int mt_body_ok(const char *b, size_t n) {
    static const char *keys[4] = {"version: ", "channel: ", "platform: ", "min-version: "};
    size_t pos = 0u;
    unsigned k;
    char prev[MT_MAX_NAME + 1u] = "";
    int have_prev = 0;
    if (n == 0u || b[n - 1u] != '\n' || n > MT_MAX_MANIFEST) return 0;
    if (strncmp(b, "break-manifest-v1\n", 18u) != 0) return 0;
    pos = 18u;
    for (k = 0u; k < 4u; k++) {
        size_t kl = strlen(keys[k]), end = pos;
        char val[80];
        while (end < n && b[end] != '\n') end++;
        if (end - pos <= kl || end - pos - kl >= sizeof(val) ||
            strncmp(b + pos, keys[k], kl) != 0)
            return 0;
        memcpy(val, b + pos + kl, end - pos - kl);
        val[end - pos - kl] = '\0';
        if ((k == 0u || k == 3u) ? !mt_version_ok(val) : !mt_field_ok(val)) return 0;
        pos = end + 1u;
    }
    while (pos < n) {
        size_t end = pos, len;
        char line[300], name[MT_MAX_NAME + 1u];
        unsigned i;
        while (end < n && b[end] != '\n') end++;
        len = end - pos;
        if (len >= sizeof(line) || len < 7u + 64u + 3u || strncmp(b + pos, "chunk: ", 7u) != 0)
            return 0;
        memcpy(line, b + pos, len);
        line[len] = '\0';
        for (i = 7u; i < 71u; i++) {
            if (!((line[i] >= '0' && line[i] <= '9') || (line[i] >= 'a' && line[i] <= 'f')))
                return 0;
        }
        if (line[71] != ' ') return 0;
        {
            char *sp = strchr(line + 72, ' ');
            if (sp == NULL || sp == line + 72) return 0;
            if (!(sp - (line + 72) == 1 && line[72] == '0')) {
                char *q;
                if (line[72] == '0') return 0;
                for (q = line + 72; q < sp; q++)
                    if (*q < '0' || *q > '9') return 0;
            }
            if (strlen(sp + 1) > MT_MAX_NAME || !mt_name_ok(sp + 1)) return 0;
            memcpy(name, sp + 1, strlen(sp + 1) + 1u);
        }
        if (have_prev && strcmp(prev, name) >= 0) return 0;
        memcpy(prev, name, strlen(name) + 1u);
        have_prev = 1;
        pos = end + 1u;
    }
    return 1;
}

static int mt_sign(const char *priv_path, const char *body_path, const char *out_path) {
    unsigned char seed[33], sig[64];
    size_t seed_len, n, sig_len = sizeof(sig);
    char *body = NULL, b64[89];
    EVP_PKEY *key = NULL;
    EVP_MD_CTX *md = NULL;
    FILE *f;
    int ok = 0;
    f = fopen(priv_path, "rb");
    if (f == NULL) {
        fprintf(stderr, "break_manifest_tool: cannot open private key\n");
        return 1;
    }
    seed_len = fread(seed, 1u, sizeof(seed), f);
    fclose(f);
    if (seed_len != 32u) {
        fprintf(stderr, "break_manifest_tool: private key must be 32 raw bytes\n");
        goto out;
    }
    body = (char *)malloc(MT_MAX_MANIFEST + 1u);
    f = body != NULL ? fopen(body_path, "rb") : NULL;
    if (f == NULL) goto out;
    n = fread(body, 1u, MT_MAX_MANIFEST + 1u, f);
    fclose(f);
    if (n + 11u + 88u + 1u > MT_MAX_MANIFEST || !mt_body_ok(body, n)) {
        fprintf(stderr, "break_manifest_tool: body is not a canonical unsigned manifest\n");
        goto out;
    }
    key = EVP_PKEY_new_raw_private_key(EVP_PKEY_ED25519, NULL, seed, 32u);
    md = EVP_MD_CTX_new();
    if (key == NULL || md == NULL || EVP_DigestSignInit(md, NULL, NULL, NULL, key) != 1 ||
        EVP_DigestSign(md, sig, &sig_len, (const unsigned char *)body, n) != 1 ||
        sig_len != 64u) {
        fprintf(stderr, "break_manifest_tool: signing failed\n");
        goto out;
    }
    mt_base64(sig, b64);
    f = fopen(out_path, "wb");
    ok = f != NULL && fwrite(body, 1u, n, f) == n && fprintf(f, "signature: %s\n", b64) == 100;
    if (f != NULL && fclose(f) != 0) ok = 0;
    if (!ok) {
        (void)remove(out_path);
        fprintf(stderr, "break_manifest_tool: writing the manifest failed\n");
    }
out:
    mt_wipe(seed, sizeof(seed));
    EVP_MD_CTX_free(md);
    EVP_PKEY_free(key);
    free(body);
    return ok ? 0 : 1;
}

int main(int argc, char **argv) {
    if (argc == 4 && strcmp(argv[1], "keygen") == 0) return mt_keygen(argv[2], argv[3]);
    if (argc == 8 && strcmp(argv[1], "build") == 0) return mt_build(argv + 2);
    if (argc == 5 && strcmp(argv[1], "sign") == 0) return mt_sign(argv[2], argv[3], argv[4]);
    fprintf(stderr,
            "usage: break_manifest_tool keygen <private key> <public key hex out>\n"
            "       break_manifest_tool build <dir> <version> <channel> <platform> "
            "<min-version> <body out>\n"
            "       break_manifest_tool sign <private key> <body> <manifest out>\n");
    return 2;
}
