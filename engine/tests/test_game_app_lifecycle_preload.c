#define _GNU_SOURCE
#include <dlfcn.h>
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef int (*GameVfprintfFn)(FILE *, const char *, va_list);
typedef int (*GameFflushFn)(FILE *);
typedef FILE *(*GameFopenFn)(const char *, const char *);
typedef size_t (*GameFreadFn)(void *, size_t, size_t, FILE *);

static GameVfprintfFn real_vfprintf;
static GameFflushFn real_fflush;
static GameFopenFn real_fopen;
static GameFreadFn real_fread;
static FILE *slow_stream;
static unsigned long slow_microseconds;
static int fail_unload_flush;
static int fail_io_stop_flush;
static int fail_next_flush;
static int slow_completed;

static void load_symbol(void *destination, size_t size, const char *name) {
    void *symbol = dlsym(RTLD_NEXT, name);
    if (!symbol || size != sizeof(symbol)) _exit(127);
    memcpy(destination, &symbol, size);
}

__attribute__((constructor)) static void game_faults_init(void) {
    load_symbol(&real_vfprintf, sizeof(real_vfprintf), "vfprintf");
    load_symbol(&real_fflush, sizeof(real_fflush), "fflush");
    load_symbol(&real_fopen, sizeof(real_fopen), "fopen");
    load_symbol(&real_fread, sizeof(real_fread), "fread");
    const char *slow = getenv("GAME_TEST_SLOW_BSCN_US");
    slow_microseconds = slow ? strtoul(slow, NULL, 10) : 0u;
    fail_unload_flush = getenv("GAME_TEST_FAIL_UNLOAD_FLUSH") != NULL;
    fail_io_stop_flush = getenv("GAME_TEST_FAIL_IO_STOP_FLUSH") != NULL;
}

int vfprintf(FILE *stream, const char *format, va_list args) {
    if ((fail_unload_flush && strstr(format, "event=level_unloaded")) ||
        (fail_io_stop_flush && strstr(format, "event=io_stopped"))) {
        fail_next_flush = 1;
    }
    return real_vfprintf(stream, format, args);
}

int fflush(FILE *stream) {
    if (fail_next_flush) {
        fail_next_flush = 0;
        errno = EIO;
        return EOF;
    }
    return real_fflush(stream);
}

FILE *fopen(const char *path, const char *mode) {
    FILE *file = real_fopen(path, mode);
    if (file && slow_microseconds > 0u && !slow_completed &&
        strstr(path, "/timeout_bscn/level.bscn")) {
        slow_stream = file;
    }
    return file;
}

size_t fread(void *data, size_t size, size_t count, FILE *stream) {
    if (stream == slow_stream && !slow_completed) {
        slow_completed = 1;
        slow_stream = NULL;
        usleep((useconds_t)slow_microseconds);
    }
    return real_fread(data, size, count, stream);
}
