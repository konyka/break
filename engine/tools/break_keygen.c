/* break_keygen — provisions one per-device AUTH-v2 key for the editor
 * remote session (docs/design/editor_remote.md, "Keyring").
 *
 *   break_keygen <keyring file> <16 hex key id> <device psk file>
 *
 * Generates 32 random bytes (break_crypto_random, the OpenSSL CSPRNG) and
 *   - appends "<key id> <64 hex psk>\n" to the keyring file read by
 *     `editor --remote-keyring-file` (created with mode 0600 if missing;
 *     a running editor reloads it on change), and
 *   - writes the same 32 raw bytes to the device file (created exclusively
 *     with mode 0600; it must not exist), the format a client loads like
 *     `--remote-psk-file`.
 * Refuses an invalid or duplicate key id, a full ring (8 keys), an existing
 * device file, or a keyring line that is not "<16 hex> <64 hex>". On any
 * failure neither file is changed (the device file is removed again if the
 * keyring append fails). Key bytes are wiped before exit. */
#include <crypto/break_crypto.h>

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#if defined(_WIN32)
#include <io.h>
#define KG_OPEN _open
#define KG_CLOSE _close
#define KG_WRITE _write
#define KG_MODE (_S_IREAD | _S_IWRITE)
#define KG_EXCL (_O_CREAT | _O_EXCL | _O_WRONLY | _O_BINARY)
#define KG_APPEND (_O_CREAT | _O_APPEND | _O_WRONLY | _O_BINARY)
#else
#include <unistd.h>
#define KG_OPEN open
#define KG_CLOSE close
#define KG_WRITE write
#define KG_MODE 0600
#define KG_EXCL (O_CREAT | O_EXCL | O_WRONLY)
#define KG_APPEND (O_CREAT | O_APPEND | O_WRONLY)
#endif

#define KG_MAX_KEYS 8u
#define KG_MAX_RING 2047u

static void kg_wipe(void *p, size_t n) {
    volatile unsigned char *v = (volatile unsigned char *)p;
    while (n-- > 0u) {
        *v++ = 0u;
    }
}

static int kg_hex_digit(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return -1;
}

static int kg_is_hex(const char *s, size_t n) {
    size_t i;
    for (i = 0u; i < n; i++) {
        if (kg_hex_digit(s[i]) < 0) return 0;
    }
    return 1;
}

static int kg_lower_eq(const char *a, const char *b, size_t n) {
    size_t i;
    for (i = 0u; i < n; i++) {
        if (kg_hex_digit(a[i]) != kg_hex_digit(b[i])) return 0;
    }
    return 1;
}

/* Validates the existing keyring and counts keys; fails on a duplicate id. */
static int kg_scan_ring(const char *path, const char *id, unsigned *count,
                        int *needs_lf) {
    char text[KG_MAX_RING + 2u];
    size_t n, pos = 0u;
    FILE *f = fopen(path, "rb");
    *count = 0u;
    *needs_lf = 0;
    if (f == NULL) {
        return errno == ENOENT ? 1 : 0; /* missing = empty ring */
    }
    n = fread(text, 1u, sizeof(text) - 1u, f);
    fclose(f);
    if (n > KG_MAX_RING) {
        fprintf(stderr, "break_keygen: keyring file is too large\n");
        kg_wipe(text, sizeof(text));
        return 0;
    }
    *needs_lf = n > 0u && text[n - 1u] != '\n';
    while (pos < n) {
        size_t end = pos, len;
        while (end < n && text[end] != '\n') end++;
        len = end - pos;
        if (len > 0u && text[pos + len - 1u] == '\r') len--;
        if (len != 0u && text[pos] != '#') {
            if (len != 81u || text[pos + 16u] != ' ' ||
                !kg_is_hex(text + pos, 16u) || !kg_is_hex(text + pos + 17u, 64u)) {
                fprintf(stderr, "break_keygen: keyring has a malformed line\n");
                kg_wipe(text, sizeof(text));
                return 0;
            }
            if (kg_lower_eq(text + pos, id, 16u)) {
                fprintf(stderr, "break_keygen: key id already in the keyring\n");
                kg_wipe(text, sizeof(text));
                return 0;
            }
            (*count)++;
        }
        pos = end + 1u;
    }
    kg_wipe(text, sizeof(text));
    if (*count >= KG_MAX_KEYS) {
        fprintf(stderr, "break_keygen: keyring is full (%u keys)\n", KG_MAX_KEYS);
        return 0;
    }
    return 1;
}

static int kg_write_all(int fd, const void *p, size_t n) {
    const unsigned char *b = (const unsigned char *)p;
    while (n > 0u) {
        int w = (int)KG_WRITE(fd, b, (unsigned)n);
        if (w <= 0) return 0;
        b += w;
        n -= (size_t)w;
    }
    return 1;
}

int main(int argc, char **argv) {
    static const char hex[] = "0123456789abcdef";
    unsigned char psk[32];
    char line[16u + 1u + 64u + 1u];
    unsigned count = 0u;
    int needs_lf = 0;
    int fd, ok;
    size_t i;
    if (argc != 4) {
        fprintf(stderr, "usage: break_keygen <keyring file> <16 hex key id> "
                        "<device psk file>\n");
        return 2;
    }
    if (strlen(argv[2]) != 16u || !kg_is_hex(argv[2], 16u)) {
        fprintf(stderr, "break_keygen: key id must be 16 hex digits\n");
        return 2;
    }
    if (!kg_scan_ring(argv[1], argv[2], &count, &needs_lf)) {
        return 1;
    }
    if (!break_crypto_random(psk, sizeof(psk))) {
        fprintf(stderr, "break_keygen: CSPRNG failure\n");
        return 1;
    }
    fd = KG_OPEN(argv[3], KG_EXCL, KG_MODE);
    if (fd < 0) {
        fprintf(stderr, "break_keygen: cannot create device file '%s' "
                        "(it must not exist)\n", argv[3]);
        kg_wipe(psk, sizeof(psk));
        return 1;
    }
    ok = kg_write_all(fd, psk, sizeof(psk));
    if (KG_CLOSE(fd) != 0) ok = 0;
    if (!ok) {
        (void)remove(argv[3]);
        kg_wipe(psk, sizeof(psk));
        fprintf(stderr, "break_keygen: writing the device file failed\n");
        return 1;
    }
    for (i = 0u; i < 16u; i++) {
        char c = argv[2][i];
        line[i] = (c >= 'A' && c <= 'F') ? (char)(c - 'A' + 'a') : c;
    }
    line[16] = ' ';
    for (i = 0u; i < 32u; i++) {
        line[17u + 2u * i] = hex[psk[i] >> 4];
        line[18u + 2u * i] = hex[psk[i] & 0x0fu];
    }
    line[81] = '\n';
    kg_wipe(psk, sizeof(psk));
    fd = KG_OPEN(argv[1], KG_APPEND, KG_MODE);
    /* a hand-edited ring may lack the final LF: terminate it first so the
     * new key never merges into the previous line */
    ok = fd >= 0 && (!needs_lf || kg_write_all(fd, "\n", 1u)) &&
         kg_write_all(fd, line, sizeof(line));
    if (fd >= 0 && KG_CLOSE(fd) != 0) ok = 0;
    kg_wipe(line, sizeof(line));
    if (!ok) {
        (void)remove(argv[3]);
        fprintf(stderr, "break_keygen: appending to the keyring failed\n");
        return 1;
    }
    printf("break_keygen: key %s added (%u keys in the ring)\n", argv[2],
           count + 1u);
    return 0;
}
