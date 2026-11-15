#pragma once
/* Merges break.trace Chrome trace documents written by different processes
 * into one document, giving each input its own process track.
 *
 * Accepted input is the layout the engine exporters write: a first line
 * {"traceEvents":[ , one event object per line (optionally followed by ','),
 * and a last line ],"otherData":{"schema":"break.trace","schema_version":1}}
 * followed by at most one newline. CRLF is accepted.
 *
 * In each event, only the part before the first ,"args": is rewritten: the
 * ,"pid":<digits> value becomes the input's pid (an event without one is
 * rejected) and a ,"ts":<digits> value, when present, is shifted by
 * ts_offset_us. A shifted ts above 2^63-1 is rejected. When label is set, a
 * process_name metadata event comes before that input's events. */
#include <core/types.h>

typedef enum BreakTraceMergeStatus {
    BREAK_TRACE_MERGE_OK = 0,
    BREAK_TRACE_MERGE_INVALID,
    BREAK_TRACE_MERGE_BAD_DOCUMENT,
    BREAK_TRACE_MERGE_TOO_SMALL,
} BreakTraceMergeStatus;

typedef struct BreakTraceMergeInput {
    const char *text;
    usize size;
    u32 pid; /* nonzero and unique among the inputs */
    u64 ts_offset_us;
    const char *label; /* NULL: no process_name event */
} BreakTraceMergeInput;

typedef struct BreakTraceMergeReport {
    u32 events;      /* input events copied, process_name events excluded */
    u32 error_input; /* BAD_DOCUMENT: index of the input */
    u32 error_line;  /* BAD_DOCUMENT: 1-based line in that input */
    u64 bytes;       /* merged size without the terminating NUL */
} BreakTraceMergeReport;

/* Writes the NUL-terminated merged document when capacity > report->bytes;
 * otherwise returns TOO_SMALL and writes nothing at or past out[capacity].
 * out may be NULL with capacity 0 to query the size; inputs may be NULL when
 * count is 0. */
BreakTraceMergeStatus break_trace_merge(const BreakTraceMergeInput *inputs, u32 count,
                                        char *out, usize capacity,
                                        BreakTraceMergeReport *report);
