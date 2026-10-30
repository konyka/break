#if !defined(_WIN32) && !defined(_POSIX_C_SOURCE)
#define _POSIX_C_SOURCE 200809L
#endif
#if defined(__linux__) && !defined(_DEFAULT_SOURCE)
#define _DEFAULT_SOURCE 1 /* flock */
#endif
#if defined(__APPLE__) && !defined(_DARWIN_C_SOURCE)
#define _DARWIN_C_SOURCE 1 /* flock, O_NOFOLLOW */
#endif
/* break_keygen — provisions one per-device AUTH-v2 key for the editor
 * remote session (docs/design/editor_remote.md, "Keyring").
 *
 *   break_keygen <keyring file> <16 hex key id> <device psk file>
 *
 * Generates 32 random bytes (break_crypto_random, the OpenSSL CSPRNG) and
 *   - appends "<key id> <64 hex psk>\n" to the keyring file read by
 *     `editor --remote-keyring-file` (created with mode 0600 if missing;
 *     a running editor reloads it on change). POSIX: the ring is opened
 *     without following symlinks, must be a regular file not accessible by
 *     group/other, is locked (flock) for the whole run so concurrent runs
 *     cannot both pass the full/duplicate checks, and the append is ONE
 *     write that is rolled back (truncate) if it comes up short, and
 *   - writes the same 32 raw bytes to the device file (created exclusively
 *     with mode 0600; it must not exist), the format a client loads like
 *     `--remote-psk-file`.
 * Refuses an invalid or duplicate key id, a full ring (8 keys), a ring that
 * would grow past the editor's 2047-byte keyring limit, an existing device
 * file, or a keyring line that is not "<16 hex> <64 hex>". On any failure
 * neither file is changed (the device file is removed again if the keyring
 * append fails, the ring is truncated back, a ring this run created is
 * removed). Key bytes are wiped before exit. Windows: file modes are not
 * owner-only there and no lock or symlink guard exists; the 0600 claim is
 * POSIX only. */
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
#define KG_READ _read
#define KG_LSEEK _lseek
#define KG_TRUNC _chsize
#else
#include <sys/file.h>
#include <unistd.h>
#define KG_READ read
#define KG_LSEEK lseek
#define KG_TRUNC ftruncate
#define KG_OPEN open
#define KG_CLOSE close
#define KG_WRITE write
#define KG_MODE 0600
#define KG_EXCL (O_CREAT | O_EXCL | O_WRONLY)
#endif

#define KG_MAX_KEYS 8u
#define KG_MAX_RING 2047u
#define KG_LINE 82u /* "<16 hex> <64 hex>\n" */

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

/* Opens the ring read/write and locks it. *created reports whether this run
 * created it. POSIX: no symlink follow, regular file only, and (unless this
 * run created it) not accessible by group/other. The lock is re-verified
 * against the path so a ring unlinked by a failing creator is retried. */
static int kg_open_ring(const char *path, int *created) {
    int attempt = 0;
    *created = 0;
#if defined(_WIN32)
    (void)attempt;
    return _open(path, _O_RDWR | _O_CREAT | _O_BINARY, KG_MODE); /* no lock or mode guard here */
#else
    for (attempt = 0; attempt < 8; attempt++) {
        struct stat fst, pst;
        int fd = open(path, O_RDWR | O_CREAT | O_EXCL | O_NOFOLLOW, 0600);
        if (fd >= 0) {
            *created = 1;
        } else if (errno == EEXIST) {
            fd = open(path, O_RDWR | O_NOFOLLOW);
        }
        if (fd < 0) {
            fprintf(stderr, "break_keygen: cannot open keyring '%s' (symlinks are not followed)\n",
                    path);
            return -1;
        }
        if (flock(fd, LOCK_EX) != 0 || fstat(fd, &fst) != 0 || !S_ISREG(fst.st_mode)) {
            fprintf(stderr, "break_keygen: keyring '%s' is not a lockable regular file\n", path);
            close(fd);
            return -1;
        }
        if (!*created && (fst.st_mode & 077) != 0) {
            fprintf(stderr, "break_keygen: keyring '%s' is accessible by group/other "
                            "(chmod 600 first)\n", path);
            close(fd);
            return -1;
        }
        if (lstat(path, &pst) == 0 && pst.st_ino == fst.st_ino && pst.st_dev == fst.st_dev) {
            return fd;
        }
        close(fd); /* unlinked or replaced while we waited for the lock: retry */
        *created = 0;
    }
    return -1;
#endif
}

/* Reads the whole ring through fd. Validates it and counts keys; fails on a
 * duplicate id, a full ring, or when the append would pass the editor limit. */
static int kg_scan_ring(int fd, const char *id, unsigned *count, int *needs_lf,
                        size_t *size) {
    char text[KG_MAX_RING + 2u];
    size_t n = 0u, pos = 0u;
    *count = 0u;
    *needs_lf = 0;
    *size = 0u;
    if (KG_LSEEK(fd, 0, SEEK_SET) < 0) return 0;
    while (n < sizeof(text) - 1u) {
        int r = (int)KG_READ(fd, text + n, (unsigned)(sizeof(text) - 1u - n));
        if (r < 0) {
            if (errno == EINTR) continue;
            fprintf(stderr, "break_keygen: reading the keyring failed\n");
            kg_wipe(text, sizeof(text));
            return 0;
        }
        if (r == 0) break;
        n += (size_t)r;
    }
    if (n > KG_MAX_RING) {
        fprintf(stderr, "break_keygen: keyring file is too large\n");
        kg_wipe(text, sizeof(text));
        return 0;
    }
    *size = n;
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
    if (n + (*needs_lf ? 1u : 0u) + KG_LINE > KG_MAX_RING) {
        fprintf(stderr, "break_keygen: the new key would grow the keyring past %u bytes, the "
                        "limit the editor accepts\n", KG_MAX_RING);
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
    char line[16u + 1u + 64u + 1u + 1u];
    unsigned count = 0u;
    int needs_lf = 0, created = 0;
    int ring_fd, fd, ok;
    size_t i, ring_size = 0u, add;
    if (argc != 4) {
        fprintf(stderr, "usage: break_keygen <keyring file> <16 hex key id> "
                        "<device psk file>\n");
        return 2;
    }
    if (strlen(argv[2]) != 16u || !kg_is_hex(argv[2], 16u)) {
        fprintf(stderr, "break_keygen: key id must be 16 hex digits\n");
        return 2;
    }
    ring_fd = kg_open_ring(argv[1], &created);
    if (ring_fd < 0) {
        return 1;
    }
    if (!kg_scan_ring(ring_fd, argv[2], &count, &needs_lf, &ring_size)) {
        goto fail_ring;
    }
    if (!break_crypto_random(psk, sizeof(psk))) {
        fprintf(stderr, "break_keygen: CSPRNG failure\n");
        goto fail_ring;
    }
    fd = KG_OPEN(argv[3], KG_EXCL, KG_MODE);
    if (fd < 0) {
        fprintf(stderr, "break_keygen: cannot create device file '%s' "
                        "(it must not exist)\n", argv[3]);
        kg_wipe(psk, sizeof(psk));
        goto fail_ring;
    }
    ok = kg_write_all(fd, psk, sizeof(psk));
    if (KG_CLOSE(fd) != 0) ok = 0;
    if (!ok) {
        (void)remove(argv[3]);
        kg_wipe(psk, sizeof(psk));
        fprintf(stderr, "break_keygen: writing the device file failed\n");
        goto fail_ring;
    }
    /* A hand-edited ring may lack the final LF: terminate it in the SAME
     * write as the new line so the append is one unit and never merges. */
    add = 0u;
    if (needs_lf) line[add++] = '\n';
    for (i = 0u; i < 16u; i++) {
        char c = argv[2][i];
        line[add + i] = (c >= 'A' && c <= 'F') ? (char)(c - 'A' + 'a') : c;
    }
    line[add + 16u] = ' ';
    for (i = 0u; i < 32u; i++) {
        line[add + 17u + 2u * i] = hex[psk[i] >> 4];
        line[add + 18u + 2u * i] = hex[psk[i] & 0x0fu];
    }
    line[add + 81u] = '\n';
    kg_wipe(psk, sizeof(psk));
    ok = KG_LSEEK(ring_fd, 0, SEEK_END) >= 0 && kg_write_all(ring_fd, line, add + KG_LINE);
#if !defined(_WIN32)
    if (ok && fsync(ring_fd) != 0) ok = 0;
#endif
    kg_wipe(line, sizeof(line));
    if (!ok) {
        (void)remove(argv[3]);
        fprintf(stderr, "break_keygen: appending to the keyring failed\n");
        goto fail_ring;
    }
    if (KG_CLOSE(ring_fd) != 0) {
        fprintf(stderr, "break_keygen: closing the keyring failed\n");
        return 1;
    }
    printf("break_keygen: key %s added (%u keys in the ring)\n", argv[2],
           count + 1u);
    return 0;

fail_ring:
    /* Put the ring back exactly as found; a ring this run created is removed
     * again while the lock is still held. */
    (void)KG_TRUNC(ring_fd, (long)ring_size);
    if (created && ring_size == 0u) {
        (void)remove(argv[1]);
    }
    (void)KG_CLOSE(ring_fd);
    return 1;
}
