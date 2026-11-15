# Merge break.trace documents from several processes

## Goal
The profiler, the runtime profiler and `core_app --trace-json` each write one
Chrome trace document, always with `"pid":1`. Traces from two processes (for
example an authority and a client) cannot be opened as one timeline. Add a
merge that gives every input its own process track and an optional time
offset.

## Design
`engine/src/core/trace_merge.{h,c}`:

- `BreakTraceMergeInput { text, size, pid, ts_offset_us, label }`.
- `break_trace_merge(inputs, count, out, capacity, report)`.
- Accepted input: the layout every engine exporter writes. The document starts
  with `{"traceEvents":[` and a newline, has one event object per line
  (optionally followed by `,`), and ends with a line
  `],"otherData":{"schema":"break.trace","schema_version":1}}` plus an
  optional newline. CRLF is accepted. Anything else is
  `BREAK_TRACE_MERGE_BAD_DOCUMENT` with `error_input` and a 1-based
  `error_line`.
- Per event, only the part before the first `,"args":` is rewritten (string
  values are JSON-escaped, so `,"pid":`, `,"ts":` and `,"args":` cannot occur
  inside a name). The `,"pid":<digits>` value becomes the input's pid; a
  missing pid is BAD_DOCUMENT. A `,"ts":<digits>` value, if present, gets
  `ts_offset_us` added; overflow past 2^63-1 is BAD_DOCUMENT.
- When `label` is non-NULL, a `process_name` metadata event
  `{"name":"process_name","ph":"M","pid":N,"args":{"name":<label>}}` is
  written before that input's events (label JSON-escaped).
- pid 0 or a pid used by two inputs is `BREAK_TRACE_MERGE_INVALID`.
- Output and size query follow `break_trace_core_app_to_chrome`: NULL/0
  queries `report->bytes`; TOO_SMALL writes nothing at or past `capacity`.

## Tests
`test_trace_merge` (headless): merges a profiler-style and a core_app-style
document into exact expected JSON (pids, offsets, labels, escaping, CRLF,
events whose args contain `ts`/`pid` keys); rejects bad header, bad trailer,
non-object line, missing pid, ts overflow, duplicate or zero pid; size query;
and a round trip that merges a real `profiler_export_chrome_trace` file with
a real `break_trace_core_app_to_chrome` document.

## Docs
Status here, `docs/Implementation_Status.md`,
`docs/cross_engine/missing_capabilities.md` section 13.

## Status
- RED: `test_trace_merge` built against a stub returning INVALID; 0/5.
- GREEN: `engine/src/core/trace_merge.{h,c}` (also compiled into `engine`);
  5/5. The round-trip case merges a real `break_trace_core_app_to_chrome`
  document with a profiler-layout document; it does not link the profiler.
- Mutation: 22 single-site mutations, all killed after adding cases for a
  non-object line, a `pid` only inside `args`, a `ts` only inside `args`, and
  a ts of 2^63.
- Still missing: no CLI wraps the merge yet, and the core_app text trace has
  ordinal timestamps only, so offsets must come from the caller.
