#if defined(__linux__) && !defined(BREAK_SYSTEM_TEST_UNSUPPORTED)
#define _GNU_SOURCE
#endif

#include <platform/platform_dynamic.h>

#include <crypto/break_crypto.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#elif defined(__linux__)
#include <dlfcn.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#else
#include <dlfcn.h>
#endif

struct PlatformDynamicLibrary {
#if defined(_WIN32)
    HMODULE handle;
#else
    void *handle;
#endif
#if defined(__linux__) && !defined(BREAK_SYSTEM_TEST_UNSUPPORTED)
    int verified_fd;
#endif
};

#if defined(BREAK_SYSTEM_TESTING)
static PlatformDynamicTestHookFn test_before_open;
static void *test_before_open_user;
void platform_dynamic_test_set_before_open(PlatformDynamicTestHookFn hook, void *user) {
    test_before_open = hook;
    test_before_open_user = user;
}
#endif

static bool platform_dynamic_path_valid(const char *path) {
    usize length;
    if (!path) return false;
    length = strlen(path);
    return length > 0u && length < 1024u;
}

#if defined(__linux__) && !defined(BREAK_SYSTEM_TEST_UNSUPPORTED)

static bool platform_write_all(int fd, const u8 *data, usize size) {
    while (size > 0u) {
        ssize_t written = write(fd, data, size);
        if (written < 0) {
            if (errno == EINTR) continue;
            return false;
        }
        if (written == 0) return false;
        data += (usize)written;
        size -= (usize)written;
    }
    return true;
}

static PlatformDynamicOpenStatus platform_open_linux(PlatformDynamicLibrary *library,
                                                     const char *path,
                                                     const u8 expected[32]) {
    int source = -1;
    int verified = -1;
    BreakCryptoSha256Ctx *ctx = NULL;
    PlatformDynamicOpenStatus status = PLATFORM_DYNAMIC_OPEN_FAILED;
    u8 digest[32];
    u8 buffer[65536];
    u64 total = 0u;
    bool copied = false;
    struct stat st;
    source = open(path, O_RDONLY | O_CLOEXEC | O_NOFOLLOW);
    if (source < 0) goto done;
    if (fstat(source, &st) != 0 || !S_ISREG(st.st_mode) || st.st_size < 0) goto done;
    if ((u64)st.st_size > PLATFORM_DYNAMIC_MAX_FILE_BYTES) {
        status = PLATFORM_DYNAMIC_OPEN_OVERLOAD;
        goto done;
    }
    verified = memfd_create("break-verified-plugin", MFD_CLOEXEC | MFD_ALLOW_SEALING);
    if (verified < 0) goto done;
    ctx = break_crypto_sha256_ctx_create();
    if (!ctx) goto done;
    copied = true;
    for (;;) {
        ssize_t count = read(source, buffer, sizeof(buffer));
        if (count < 0) {
            if (errno == EINTR) continue;
            copied = false;
            break;
        }
        if (count == 0) break;
        total += (u64)count;
        if (total > PLATFORM_DYNAMIC_MAX_FILE_BYTES) {
            status = PLATFORM_DYNAMIC_OPEN_OVERLOAD;
            copied = false;
            break;
        }
        if (!break_crypto_sha256_update(ctx, buffer, (usize)count) ||
            !platform_write_all(verified, buffer, (usize)count)) {
            copied = false;
            break;
        }
    }
    if (!copied || !break_crypto_sha256_final(ctx, digest)) goto done;
    if (fcntl(verified, F_ADD_SEALS,
              F_SEAL_WRITE | F_SEAL_GROW | F_SEAL_SHRINK | F_SEAL_SEAL) != 0) goto done;
    if (memcmp(digest, expected, 32u) != 0) {
        status = PLATFORM_DYNAMIC_OPEN_MISMATCH;
        goto done;
    }
    {
        char verified_path[64];
        int length = snprintf(verified_path, sizeof(verified_path), "/proc/self/fd/%d", verified);
        if (length < 0 || (usize)length >= sizeof(verified_path)) goto done;
#if defined(BREAK_SYSTEM_TESTING)
        if (test_before_open) test_before_open(test_before_open_user);
#endif
        library->handle = dlopen(verified_path, RTLD_NOW | RTLD_LOCAL);
    }
    if (!library->handle) goto done;
    status = PLATFORM_DYNAMIC_OPEN_OK;

done:
    if (ctx) break_crypto_sha256_ctx_destroy(ctx);
    if (status == PLATFORM_DYNAMIC_OPEN_OK) {
        library->verified_fd = verified;
        verified = -1;
    }
    if (verified >= 0) close(verified);
    if (source >= 0) close(source);
    return status;
}

#elif defined(_WIN32) && !defined(BREAK_SYSTEM_TEST_UNSUPPORTED)

static PlatformDynamicOpenStatus platform_open_windows(PlatformDynamicLibrary *library,
                                                       const char *path,
                                                       const u8 expected[32]) {
    HANDLE source = INVALID_HANDLE_VALUE;
    BreakCryptoSha256Ctx *ctx = NULL;
    PlatformDynamicOpenStatus status = PLATFORM_DYNAMIC_OPEN_FAILED;
    BY_HANDLE_FILE_INFORMATION info;
    LARGE_INTEGER size;
    u8 digest[32];
    u8 buffer[65536];
    u64 total = 0u;
    char final_path[1024];
    DWORD final_length;
    source = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,
                         FILE_FLAG_OPEN_REPARSE_POINT, NULL);
    if (source == INVALID_HANDLE_VALUE) goto done;
    if (!GetFileInformationByHandle(source, &info) ||
        (info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0 ||
        (info.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT) != 0 ||
        !GetFileSizeEx(source, &size) || size.QuadPart < 0) goto done;
    if ((u64)size.QuadPart > PLATFORM_DYNAMIC_MAX_FILE_BYTES) {
        status = PLATFORM_DYNAMIC_OPEN_OVERLOAD;
        goto done;
    }
    ctx = break_crypto_sha256_ctx_create();
    if (!ctx) goto done;
    for (;;) {
        DWORD count = 0u;
        if (!ReadFile(source, buffer, (DWORD)sizeof(buffer), &count, NULL)) goto done;
        if (count == 0u) break;
        total += (u64)count;
        if (total > PLATFORM_DYNAMIC_MAX_FILE_BYTES) {
            status = PLATFORM_DYNAMIC_OPEN_OVERLOAD;
            goto done;
        }
        if (!break_crypto_sha256_update(ctx, buffer, count)) goto done;
    }
    if (!break_crypto_sha256_final(ctx, digest)) goto done;
    if (memcmp(digest, expected, 32u) != 0) {
        status = PLATFORM_DYNAMIC_OPEN_MISMATCH;
        goto done;
    }
    final_length = GetFinalPathNameByHandleA(source, final_path, (DWORD)sizeof(final_path),
                                             FILE_NAME_NORMALIZED | VOLUME_NAME_DOS);
    if (final_length == 0u || final_length >= sizeof(final_path)) goto done;
#if defined(BREAK_SYSTEM_TESTING)
    if (test_before_open) test_before_open(test_before_open_user);
#endif
    library->handle = LoadLibraryA(final_path);
    if (!library->handle) goto done;
    status = PLATFORM_DYNAMIC_OPEN_OK;

done:
    if (ctx) break_crypto_sha256_ctx_destroy(ctx);
    if (source != INVALID_HANDLE_VALUE) CloseHandle(source);
    return status;
}

#endif

PlatformDynamicOpenStatus platform_dynamic_open_verified(
    const char *path, const u8 expected_sha256[32],
    PlatformDynamicLibrary **out_library) {
    PlatformDynamicLibrary *library;
    PlatformDynamicOpenStatus status;
    if (out_library) *out_library = NULL;
    if (!out_library || !expected_sha256 || !platform_dynamic_path_valid(path))
        return PLATFORM_DYNAMIC_OPEN_INVALID;
    library = (PlatformDynamicLibrary *)calloc(1u, sizeof(*library));
    if (!library) return PLATFORM_DYNAMIC_OPEN_FAILED;
#if defined(__linux__) && !defined(BREAK_SYSTEM_TEST_UNSUPPORTED)
    library->verified_fd = -1;
    status = platform_open_linux(library, path, expected_sha256);
#elif defined(_WIN32) && !defined(BREAK_SYSTEM_TEST_UNSUPPORTED)
    status = platform_open_windows(library, path, expected_sha256);
#else
    (void)path;
    (void)expected_sha256;
    status = PLATFORM_DYNAMIC_OPEN_FAILED;
#endif
    if (status != PLATFORM_DYNAMIC_OPEN_OK) {
        free(library);
        return status;
    }
    *out_library = library;
    return status;
}

void *platform_dynamic_symbol(PlatformDynamicLibrary *library, const char *name) {
    if (!library || !name || !name[0]) return NULL;
#if defined(_WIN32)
    {
        FARPROC procedure = GetProcAddress(library->handle, name);
        void *symbol = NULL;
        if (!procedure || sizeof(procedure) != sizeof(symbol)) return NULL;
        memcpy(&symbol, &procedure, sizeof(symbol));
        return symbol;
    }
#else
    return dlsym(library->handle, name);
#endif
}

void platform_dynamic_close(PlatformDynamicLibrary *library) {
    if (!library) return;
#if defined(_WIN32)
    (void)FreeLibrary(library->handle);
#else
    (void)dlclose(library->handle);
#endif
#if defined(__linux__) && !defined(BREAK_SYSTEM_TEST_UNSUPPORTED)
    if (library->verified_fd >= 0) close(library->verified_fd);
#endif
    free(library);
}
