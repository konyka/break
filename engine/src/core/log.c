#include <core/log.h>
#include <stdio.h>
#include <stdarg.h>

static LogLevel min_level = LOG_INFO;

static const char *level_strings[] = {
    "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL",
};

static const char *level_colors[] = {
    "\033[90m", "\033[36m", "\033[32m", "\033[33m", "\033[31m", "\033[35m",
};

void log_set_level(LogLevel level) {
    min_level = level;
}

void log_write(LogLevel level, const char *file, int line,
               const char *fmt, ...) {
    if (level < min_level) return;

    const char *basename = file;
    for (const char *p = file; *p; p++) {
        if (*p == '/') basename = p + 1;
    }

    fprintf(stderr, "%s[%-5s]\033[0m \033[90m%s:%d\033[0m ",
            level_colors[level], level_strings[level], basename, line);

    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);

    fprintf(stderr, "\n");
    fflush(stderr);
}
