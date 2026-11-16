# core_app text trace: real timestamps in the converter

Status: Done

## Context

`break_trace_core_app_to_chrome` (engine/src/core/trace_core_app.c) turns
`COREAPPTRACE version=1 ...` lines into Chrome trace events. The text trace
has no time field, so `"ts"` is the event ordinal and a merged timeline
(`trace_merge`) cannot line core_app events up with other processes.
`docs/cross_engine/missing_capabilities.md` lists real timestamps as missing.

This slice teaches the converter an optional time field. Making core_app
write it is the next slice.

## Design

- Optional field `ts_us=<microseconds>`: canonical decimal (no leading
  zero, at most 18 digits). When present it becomes the event's `"ts"` and
  is not copied to `"args"`.
- A line whose `ts_us` is not canonical decimal is malformed and skipped
  (counted in `skipped`).
- A line without `ts_us` keeps the old rule: `"ts"` is its 0-based ordinal.
  Existing traces convert byte-for-byte as before. A producer writes
  `ts_us` on every line or on none.
- `BreakTraceCoreAppReport.timestamped` counts events that used `ts_us`.

## Tests (engine/tests/test_trace_core_app.c, written first)

1. `ts_us` becomes `"ts"` (including 0 and the 18-digit maximum) and is
   removed from args; ordinals still advance for lines without it;
   `timestamped` counts only the timestamped events.
2. Non-canonical `ts_us` values (`01`, `-1`, `1a`, empty, 19 digits) skip
   the line.
3. The existing tests stay unchanged.

## Verification

test_trace_core_app, mutation run on the new code, the three full build
trees, banned-word check, commit and push.

Result: 5/5. Mutation: 9 of 9 killed.

## Docs

trace_core_app.h comment, docs/design/core_app_integration.md (trace
converter section), docs/Implementation_Status.md,
docs/cross_engine/missing_capabilities.md.
