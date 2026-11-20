#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

__attribute__((constructor)) static void qnx_sanitizer_unbuffered(void)
{
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

__attribute__((destructor)) static void qnx_sanitizer_cleanup(void)
{
    static const char *const names[] = {"libc++.so.2", "libstdc++.so.6"};
    size_t i;
    for (i = 0; i < sizeof(names) / sizeof(names[0]); ++i) {
        void *handle = dlopen(names[i], RTLD_NOW | RTLD_LOCAL);
        void *symbol;
        void (*release)(void);
        if (handle == NULL) abort();
        symbol = dlsym(handle, "_ZN9__gnu_cxx9__freeresEv");
        if (symbol == NULL) abort();
        memcpy(&release, &symbol, sizeof(release));
        release();
    }
}
