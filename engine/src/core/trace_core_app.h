#pragma once
/* Converts the core_app text trace (core_app --trace PATH) into a Chrome
 * trace-event JSON document marked with the break.trace schema.
 *
 * Input lines look like
 *   COREAPPTRACE version=1 event=<name> key=value key=value ...
 * Each valid line becomes one instant event in category "core_app". An
 * optional ts_us=<microseconds> field (canonical decimal, at most 18 digits)
 * becomes the event's "ts" and is not copied to "args"; a line without it
 * gets its 0-based event ordinal as "ts", so traces written before ts_us
 * convert unchanged. A producer writes ts_us on every line or on none.
 * Other fields go to "args": digit-only values without a leading zero (up to
 * 18 digits) become JSON numbers, everything else a JSON string.
 *
 * Lines that do not start with "COREAPPTRACE ", have a version other than 1,
 * lack event=, carry a ts_us that is not canonical decimal, contain a field
 * without '=' or with an empty key, repeat a key or carry more than
 * BREAK_TRACE_CORE_APP_MAX_FIELDS fields are skipped and
 * counted. Blank lines are ignored. A trailing '\r' is dropped. */
#include <core/types.h>

#include <stdarg.h>
#include <stdio.h>

#define BREAK_TRACE_CORE_APP_MAX_FIELDS 32u

typedef enum BreakTraceConvertStatus {
    BREAK_TRACE_CONVERT_OK = 0,
    BREAK_TRACE_CONVERT_INVALID,
    BREAK_TRACE_CONVERT_TOO_SMALL,
} BreakTraceConvertStatus;

typedef struct BreakTraceCoreAppReport {
    u32 events;
    u32 skipped;
    u32 timestamped; /* events whose "ts" came from ts_us */
    u64 bytes; /* document size without the terminating NUL */
} BreakTraceCoreAppReport;

/* Writes the NUL-terminated document to out when capacity > report->bytes;
 * otherwise returns TOO_SMALL and writes nothing at or past out[capacity].
 * out may be NULL with capacity 0 to query the size. text may be NULL only
 * when size is 0. */
BreakTraceConvertStatus break_trace_core_app_to_chrome(const char *text, usize size, char *out,
                                                       usize capacity,
                                                       BreakTraceCoreAppReport *report);

typedef enum BreakTraceClockOffsetStatus {
    BREAK_TRACE_CLOCK_OFFSET_OK = 0,
    BREAK_TRACE_CLOCK_OFFSET_INVALID,
    BREAK_TRACE_CLOCK_OFFSET_NOT_FOUND,
    BREAK_TRACE_CLOCK_OFFSET_AMBIGUOUS,
    BREAK_TRACE_CLOCK_OFFSET_MALFORMED,
} BreakTraceClockOffsetStatus;

/* Reads the peer clock offset a core_app server traced as
 *   COREAPPTRACE version=1 event=network_clock_offset ... offset_us=N error_us=M
 * (offset = peer clock minus server clock). Only lines the converter
 * accepts are considered. offset_us is an optionally negative canonical
 * decimal (no leading zero, no "-0", at most 18 digits), error_us a
 * canonical decimal. NOT_FOUND when no such line exists, AMBIGUOUS when
 * there are several (one per peer), MALFORMED when a matching line lacks a
 * field or carries a non-canonical one. INVALID for NULL outputs or NULL
 * text with a non-zero size. The outputs are written only on OK. */
BreakTraceClockOffsetStatus break_trace_core_app_clock_offset(const char *text, usize size,
                                                              i64 *offset_us, u64 *error_us);

/* ---- writer side --------------------------------------------------------
 * core_app writes every trace line through these functions. When a clock is
 * set, a line that starts with "COREAPPTRACE version=1 " gets
 * "ts_us=<clock()> " inserted right after that prefix; any other text
 * (continuation chunks of a long line included) is written verbatim. Each
 * call is a single fwrite, so concurrent writers do not interleave inside a
 * call. Callers still flush. */
typedef u64 (*BreakTraceClockFn)(void);

/* Process-wide; NULL (the default) turns stamping off. Set it before any
 * trace thread starts. Without a clock the fprintf variants call vfprintf
 * directly, so output and libc calls are exactly as before. */
void break_trace_core_app_set_clock(BreakTraceClockFn now_us);

/* fprintf-like: the bytes written, or -1 on a NULL argument or an I/O or
 * allocation failure. */
int break_trace_core_app_fprintf(FILE *out, const char *format, ...)
#if defined(__GNUC__) || defined(__clang__)
    __attribute__((format(printf, 2, 3)))
#endif
    ;
int break_trace_core_app_vfprintf(FILE *out, const char *format, va_list args);
int break_trace_core_app_write(FILE *out, const char *text);
