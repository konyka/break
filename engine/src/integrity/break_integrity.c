#include <integrity/break_integrity.h>

#include <crypto/break_crypto.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if !defined(_WIN32)
#include <sys/stat.h>
#endif

#define BINT_READ_BLOCK 65536u

/* Streams the file through SHA-256. false when it cannot be read in full. */
static bool hash_file(const char *path, u8 out[32]) {
    static const u8 zero = 0u;
    BreakCryptoSha256Ctx *ctx;
    FILE *f;
    u8 buf[BINT_READ_BLOCK];
    bool ok = false;
#if !defined(_WIN32)
    struct stat st;
    if (stat(path, &st) != 0 || !S_ISREG(st.st_mode)) {
        return false;
    }
#endif
    f = fopen(path, "rb");
    if (f == NULL) {
        return false;
    }
    ctx = break_crypto_sha256_ctx_create();
    if (ctx != NULL) {
        usize n;
        ok = break_crypto_sha256_update(ctx, &zero, 0u);
        while (ok && (n = fread(buf, 1u, sizeof(buf), f)) > 0u) {
            ok = break_crypto_sha256_update(ctx, buf, n);
        }
        if (ok && ferror(f)) {
            ok = false;
        }
        if (ok) {
            ok = break_crypto_sha256_final(ctx, out);
        }
        break_crypto_sha256_ctx_destroy(ctx);
    }
    fclose(f);
    return ok;
}

BreakIntegritySignals break_integrity_check_files(const BreakIntegrityFile *files, u32 count) {
    BreakIntegritySignals sig = 0u;
    if (files == NULL || count == 0u || count > BREAK_INTEGRITY_MAX_FILES) {
        return BINT_SIG_CHECK_ERROR;
    }
    for (u32 i = 0u; i < count; i++) {
        u8 got[32];
        if (files[i].path == NULL || files[i].path[0] == '\0' ||
            !hash_file(files[i].path, got)) {
            sig |= BINT_SIG_CHECK_ERROR;
            continue;
        }
        if (memcmp(got, files[i].sha256, 32u) != 0) {
            sig |= BINT_SIG_FILE_MISMATCH;
        }
    }
    return sig;
}

#if defined(__linux__)

BreakIntegritySignals break_integrity_check_debugger(void) {
    FILE *f = fopen("/proc/self/status", "r");
    char line[256];
    bool found = false;
    long tracer = 0;
    if (f == NULL) {
        return BINT_SIG_CHECK_ERROR;
    }
    while (fgets(line, sizeof(line), f) != NULL) {
        if (strncmp(line, "TracerPid:", 10) == 0) {
            char *end = NULL;
            errno = 0;
            tracer = strtol(line + 10, &end, 10);
            found = end != line + 10 && errno == 0;
            break;
        }
    }
    fclose(f);
    if (!found || tracer < 0) {
        return BINT_SIG_CHECK_ERROR;
    }
    return tracer != 0 ? BINT_SIG_DEBUGGER : 0u;
}

BreakIntegritySignals break_integrity_check_modules(const char *const *allowed_basenames,
                                                    u32 count) {
    BreakIntegritySignals sig = 0u;
    FILE *f;
    char line[4096];
    if (allowed_basenames == NULL || count == 0u || count > BREAK_INTEGRITY_MAX_MODULES) {
        return BINT_SIG_CHECK_ERROR;
    }
    for (u32 i = 0u; i < count; i++) {
        if (allowed_basenames[i] == NULL || allowed_basenames[i][0] == '\0') {
            return BINT_SIG_CHECK_ERROR;
        }
    }
    f = fopen("/proc/self/maps", "r");
    if (f == NULL) {
        return BINT_SIG_CHECK_ERROR;
    }
    while (fgets(line, sizeof(line), f) != NULL) {
        char *path = strchr(line, '/');
        char *name, *end;
        bool allowed = false;
        usize len;
        if (strchr(line, '\n') == NULL && !feof(f)) {
            /* a line longer than the buffer: the rest would be misparsed as
             * its own lines; report that the check could not run */
            sig |= BINT_SIG_CHECK_ERROR;
            while (fgets(line, sizeof(line), f) != NULL && strchr(line, '\n') == NULL) {
            }
            continue;
        }
        if (path == NULL) {
            continue; /* anonymous mapping or [heap]/[stack]/[vdso] */
        }
        end = strchr(path, '\n');
        if (end != NULL) {
            *end = '\0';
        }
        end = strstr(path, " (deleted)");
        if (end != NULL) {
            *end = '\0';
        }
        name = strrchr(path, '/') + 1;
        len = strlen(name);
        if (len == 0u) {
            continue;
        }
        for (u32 i = 0u; i < count; i++) {
            if (strcmp(allowed_basenames[i], name) == 0) {
                allowed = true;
                break;
            }
        }
        if (!allowed) {
            sig |= BINT_SIG_UNKNOWN_MODULE;
        }
    }
    if (ferror(f)) {
        sig |= BINT_SIG_CHECK_ERROR;
    }
    fclose(f);
    return sig;
}

#else

BreakIntegritySignals break_integrity_check_debugger(void) {
    return BINT_SIG_CHECK_ERROR; /* not implemented here: never report "clean" */
}

BreakIntegritySignals break_integrity_check_modules(const char *const *allowed_basenames,
                                                    u32 count) {
    (void)allowed_basenames;
    (void)count;
    return BINT_SIG_CHECK_ERROR;
}

#endif
