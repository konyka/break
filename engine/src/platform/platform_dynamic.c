#include <platform/platform_dynamic.h>

#include <stdlib.h>
#include <string.h>

#if defined(_WIN32)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#else
#include <dlfcn.h>
#endif

struct PlatformDynamicLibrary {
#if defined(_WIN32)
    HMODULE handle;
#else
    void *handle;
#endif
};

static bool platform_dynamic_path_valid(const char *path) {
    usize length;
    if (!path) return false;
    length = strlen(path);
    return length > 0u && length < 1024u;
}

PlatformDynamicLibrary *platform_dynamic_open(const char *path) {
    PlatformDynamicLibrary *library;
    if (!platform_dynamic_path_valid(path)) return NULL;
    library = (PlatformDynamicLibrary *)calloc(1u, sizeof(*library));
    if (!library) return NULL;
#if defined(_WIN32)
    library->handle = LoadLibraryA(path);
    if (!library->handle) {
        free(library);
        return NULL;
    }
#else
    library->handle = dlopen(path, RTLD_NOW | RTLD_LOCAL);
    if (!library->handle) {
        free(library);
        return NULL;
    }
#endif
    return library;
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
    free(library);
}
