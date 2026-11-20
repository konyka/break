#include <unistd.h>
#include <confname.h>
#include <dlfcn.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fopen(const char *path, const char *mode)
{
    const char *redirect = getenv("SWIFTSHADER_GRAPHICS_CONF");
    if (redirect != NULL && redirect[0] != '\0' &&
        strcmp(path, "/dev/screen/.config") == 0) {
        path = redirect;
    }

    void *symbol = dlsym(RTLD_NEXT, "fopen");
    FILE *(*real_fopen)(const char *, const char *) = NULL;
    if (symbol != NULL) {
        memcpy(&real_fopen, &symbol, sizeof(real_fopen));
        return real_fopen(path, mode);
    }
    errno = ENOSYS;
    return NULL;
}

size_t confstr(int name, char *buffer, size_t length)
{
    const char *redirect = name == _CS_GRAPHICS
        ? getenv("SWIFTSHADER_GRAPHICS_CONF") : NULL;
    if (redirect != NULL && redirect[0] != '\0') {
        size_t needed = strlen(redirect) + 1u;
        if (buffer != NULL && length > 0u) {
            size_t copy = needed < length ? needed : length;
            memcpy(buffer, redirect, copy);
            buffer[copy - 1u] = '\0';
        }
        return needed;
    }

    void *symbol = dlsym(RTLD_NEXT, "confstr");
    size_t (*real_confstr)(int, char *, size_t) = NULL;
    if (symbol != NULL) {
        memcpy(&real_confstr, &symbol, sizeof(real_confstr));
        return real_confstr(name, buffer, length);
    }
    errno = ENOSYS;
    return (size_t)-1;
}
