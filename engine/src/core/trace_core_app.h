#pragma once
/* Converts the core_app text trace (core_app --trace PATH) into a Chrome
 * trace-event JSON document marked with the break.trace schema.
 *
 * Input lines look like
 *   COREAPPTRACE version=1 event=<name> key=value key=value ...
 * Each valid line becomes one instant event in category "core_app". The text
 * trace carries no timestamps, so "ts" is the 0-based ordinal of the event.
 * Other fields go to "args": digit-only values without a leading zero (up to
 * 18 digits) become JSON numbers, everything else a JSON string.
 *
 * Lines that do not start with "COREAPPTRACE ", have a version other than 1,
 * lack event=, contain a field without '=' or with an empty key, repeat a key
 * or carry more than BREAK_TRACE_CORE_APP_MAX_FIELDS fields are skipped and
 * counted. Blank lines are ignored. A trailing '\r' is dropped. */
#include <core/types.h>

#define BREAK_TRACE_CORE_APP_MAX_FIELDS 32u

typedef enum BreakTraceConvertStatus {
    BREAK_TRACE_CONVERT_OK = 0,
    BREAK_TRACE_CONVERT_INVALID,
    BREAK_TRACE_CONVERT_TOO_SMALL,
} BreakTraceConvertStatus;

typedef struct BreakTraceCoreAppReport {
    u32 events;
    u32 skipped;
    u64 bytes; /* document size without the terminating NUL */
} BreakTraceCoreAppReport;

/* Writes the NUL-terminated document to out when capacity > report->bytes;
 * otherwise returns TOO_SMALL and writes nothing at or past out[capacity].
 * out may be NULL with capacity 0 to query the size. text may be NULL only
 * when size is 0. */
BreakTraceConvertStatus break_trace_core_app_to_chrome(const char *text, usize size, char *out,
                                                       usize capacity,
                                                       BreakTraceCoreAppReport *report);
