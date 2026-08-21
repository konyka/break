/**
 * @file my_error.h
 * @brief myui return codes (awtk ret_t style) and logging macros.
 *
 * Convention: functions return my_ret_t, MY_RET_OK (0) on success and a
 * negative code on failure.
 */
#ifndef MY_ERROR_H
#define MY_ERROR_H

#include <stdarg.h>
#include <stdio.h>

/** @brief Return type of most myui functions. 0 = ok, negative = error. */
typedef int my_ret_t;

#define MY_RET_OK 0              /**< success */
#define MY_RET_FAIL -1           /**< generic failure */
#define MY_RET_OOM -2            /**< out of memory */
#define MY_RET_INVALID_PARAMS -3 /**< NULL or out-of-range argument */
#define MY_RET_NOT_FOUND -4      /**< requested item does not exist */
#define MY_RET_NOT_SUPPORTED -5  /**< operation not supported on this backend */
#define MY_RET_PENDING -6        /**< asynchronous operation has not completed */

/** @brief Log levels, ordered by verbosity. */
#define MY_LOG_LEVEL_DEBUG 0
#define MY_LOG_LEVEL_WARN 1
#define MY_LOG_LEVEL_ERROR 2
#define MY_LOG_LEVEL_OFF 3

#ifndef MY_LOG_LEVEL
#define MY_LOG_LEVEL MY_LOG_LEVEL_DEBUG
#endif

static inline void my_log_print(char level, const char* file, int line,
                                const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  fprintf(stderr, "[%c] %s:%d: ", level, file, line);
  vfprintf(stderr, fmt, args);
  fprintf(stderr, "\n");
  va_end(args);
}

#if MY_LOG_LEVEL <= MY_LOG_LEVEL_DEBUG
#define MY_LOGD(...) my_log_print('D', __FILE__, __LINE__, __VA_ARGS__)
#else
#define MY_LOGD(...) ((void)0)
#endif

#if MY_LOG_LEVEL <= MY_LOG_LEVEL_WARN
#define MY_LOGW(...) my_log_print('W', __FILE__, __LINE__, __VA_ARGS__)
#else
#define MY_LOGW(...) ((void)0)
#endif

#if MY_LOG_LEVEL <= MY_LOG_LEVEL_ERROR
#define MY_LOGE(...) my_log_print('E', __FILE__, __LINE__, __VA_ARGS__)
#else
#define MY_LOGE(...) ((void)0)
#endif

#endif /* MY_ERROR_H */
