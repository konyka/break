#pragma once
#include <core/types.h>
#include <core/alloc.h>

/* ---- Logging API ---- */

typedef enum {
    LOG_TRACE,
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
    LOG_FATAL,
} LogLevel;

/* Set minimum log level (default: LOG_INFO) */
void log_set_level(LogLevel level);

/* Core log function. Prefer macros below. */
void log_write(LogLevel level, const char *file, int line,
               const char *fmt, ...);

/* Convenience macros — auto-fill file:line */
#define LOG_TRACE(...) log_write(LOG_TRACE, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_DEBUG(...) log_write(LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_INFO(...)  log_write(LOG_INFO,  __FILE__, __LINE__, __VA_ARGS__)
#define LOG_WARN(...)  log_write(LOG_WARN,  __FILE__, __LINE__, __VA_ARGS__)
#define LOG_ERROR(...) log_write(LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_FATAL(...) log_write(LOG_FATAL, __FILE__, __LINE__, __VA_ARGS__)
