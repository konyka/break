#define _GNU_SOURCE
#include <dlfcn.h>
#include <errno.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef int (*CoreAppVfprintfFn)(FILE *, const char *, va_list);
typedef int (*CoreAppFflushFn)(FILE *);
typedef FILE *(*CoreAppFopenFn)(const char *, const char *);
typedef size_t (*CoreAppFreadFn)(void *, size_t, size_t, FILE *);
typedef int (*CoreAppSigactionFn)(int, const struct sigaction *, struct sigaction *);

static CoreAppVfprintfFn real_vfprintf;
static CoreAppFflushFn real_fflush;
static CoreAppFopenFn real_fopen;
static CoreAppFreadFn real_fread;
static CoreAppSigactionFn real_sigaction;
static FILE *slow_stream;
static unsigned long slow_microseconds;
static int fail_unload_flush;
static int fail_io_stop_flush;
static int fail_quiesced_flush;
static int fail_next_flush;
static int slow_completed;
static unsigned long frame_messages;
static unsigned long abort_on_frame;
static int abort_before_runtime_running;
static int trace_sigactions;
static unsigned long sigaction_total;

static void load_symbol(void *destination, size_t size, const char *name) {
    void *symbol = dlsym(RTLD_NEXT, name);
    if (!symbol || size != sizeof(symbol)) _exit(127);
    memcpy(destination, &symbol, size);
}

static void emit_marker(const char *name, unsigned long value) {
    char text[96];
    int length = snprintf(text, sizeof(text), "%s=%lu\n", name, value);
    if (length > 0 && (size_t)length < sizeof(text))
        (void)write(STDERR_FILENO, text, (size_t)length);
}

__attribute__((constructor)) static void app_faults_init(void) {
    load_symbol(&real_vfprintf, sizeof(real_vfprintf), "vfprintf");
    load_symbol(&real_fflush, sizeof(real_fflush), "fflush");
    load_symbol(&real_fopen, sizeof(real_fopen), "fopen");
    load_symbol(&real_fread, sizeof(real_fread), "fread");
    load_symbol(&real_sigaction, sizeof(real_sigaction), "sigaction");
    const char *slow = getenv("CORE_APP_TEST_SLOW_BSCN_US");
    slow_microseconds = slow ? strtoul(slow, NULL, 10) : 0u;
    fail_unload_flush = getenv("CORE_APP_TEST_FAIL_UNLOAD_FLUSH") != NULL;
    fail_io_stop_flush = getenv("CORE_APP_TEST_FAIL_IO_STOP_FLUSH") != NULL;
    fail_quiesced_flush = getenv("CORE_APP_TEST_FAIL_QUIESCED_FLUSH") != NULL;
    const char *abort_frame = getenv("CORE_APP_TEST_ABORT_ON_FRAME");
    abort_on_frame = abort_frame ? strtoul(abort_frame, NULL, 10) : 0u;
    abort_before_runtime_running = getenv("CORE_APP_TEST_ABORT_BEFORE_RUNTIME_RUNNING") != NULL;
    trace_sigactions = getenv("CORE_APP_TEST_TRACE_SIGACTION") != NULL;
}

__attribute__((destructor)) static void app_faults_fini(void) {
    if (trace_sigactions) emit_marker("CORE_APP_TEST_SIGACTION_TOTAL", sigaction_total);
}

int vfprintf(FILE *stream, const char *format, va_list args) {
    int abort_frame = 0;
    if (abort_before_runtime_running && strstr(format, "event=runtime_running")) {
        emit_marker("CORE_APP_TEST_ABORT_BEFORE_RUNTIME_RUNNING", 1u);
        abort();
    }
    if ((fail_unload_flush && strstr(format, "event=level_unloaded")) ||
        (fail_io_stop_flush && strstr(format, "event=io_stopped")) ||
        (fail_quiesced_flush && strstr(format, "event=io_quiesced"))) {
        fail_next_flush = 1;
    }
    if (abort_on_frame > 0u && strstr(format, "event=frame frame=")) {
        ++frame_messages;
        abort_frame = frame_messages == abort_on_frame;
    }
    int result = real_vfprintf(stream, format, args);
    if (abort_frame) {
        emit_marker("CORE_APP_TEST_ABORT_ON_FRAME", frame_messages);
        abort();
    }
    return result;
}

int sigaction(int signal, const struct sigaction *action, struct sigaction *old_action) {
    if (!real_sigaction) load_symbol(&real_sigaction, sizeof(real_sigaction), "sigaction");
    int result = real_sigaction(signal, action, old_action);
    if (trace_sigactions) ++sigaction_total;
    return result;
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
