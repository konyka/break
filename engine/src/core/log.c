#include <core/log.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

static LogLevel min_level = LOG_INFO;

static const char *level_strings[] = {
    "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL",
};

static const char *level_colors[] = {
    "\033[90m", "\033[36m", "\033[32m", "\033[33m", "\033[31m", "\033[35m",
};

void log_set_level(LogLevel level) {
    /* R420: clamp like log_write does — an out-of-range level (e.g.
     * log_set_level((LogLevel)99)) otherwise silently disables all logging. */
    if (level < LOG_TRACE) level = LOG_TRACE;
    if (level > LOG_FATAL) level = LOG_FATAL;
    min_level = level;
}

void log_write(LogLevel level, const char *file, int line,
               const char *fmt, ...) {
    /* R419: clamp level into the valid enum range — level_colors[] and
     * level_strings[] have exactly 6 entries; an out-of-range level (e.g. from
     * a cast or corrupt value) was an out-of-bounds read. */
    if (level < LOG_TRACE) level = LOG_TRACE;
    if (level > LOG_FATAL) level = LOG_FATAL;
    if (level < min_level) return;

    /* strrchr is SIMD-optimized in glibc, faster than manual linear scan */
    const char *slash = strrchr(file, '/');
    const char *basename = slash ? slash + 1 : file;

    fprintf(stderr, "%s[%-5s]\033[0m \033[90m%s:%d\033[0m ",
            level_colors[level], level_strings[level], basename, line);

    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);

    fprintf(stderr, "\n");
    fflush(stderr);
}
