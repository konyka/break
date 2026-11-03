#pragma once

#include <core/types.h>

#define PLATFORM_DYNAMIC_MAX_FILE_BYTES (64u * 1024u * 1024u)

typedef struct PlatformDynamicLibrary PlatformDynamicLibrary;

typedef enum PlatformDynamicOpenStatus {
    PLATFORM_DYNAMIC_OPEN_OK = 0,
    PLATFORM_DYNAMIC_OPEN_INVALID,
    PLATFORM_DYNAMIC_OPEN_MISMATCH,
    PLATFORM_DYNAMIC_OPEN_FAILED
} PlatformDynamicOpenStatus;

PlatformDynamicOpenStatus platform_dynamic_open_verified(
    const char *path, const u8 expected_sha256[32],
    PlatformDynamicLibrary **out_library);
void *platform_dynamic_symbol(PlatformDynamicLibrary *library, const char *name);
void platform_dynamic_close(PlatformDynamicLibrary *library);

#if defined(BREAK_SYSTEM_TESTING)
typedef void (*PlatformDynamicTestHookFn)(void *user);
void platform_dynamic_test_set_before_open(PlatformDynamicTestHookFn hook, void *user);
#endif
