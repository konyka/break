# core_app text trace in the break.trace schema

## Goal
`core_app --trace PATH` writes one `COREAPPTRACE version=1 event=... k=v`
line per event. Chrome trace viewers and the `break.trace` tooling cannot read
it. Convert those lines into a Chrome trace-event JSON document marked with
`BREAK_TRACE_OTHER_DATA`, without changing the text format that the lifecycle
tests depend on.

## Design
`engine/src/core/trace_core_app.{h,c}`:

- `break_trace_core_app_to_chrome(text, size, out, capacity, report)`.
- Each valid line becomes an instant event:
  `{"name":<event>,"cat":"core_app","ph":"i","s":"g","ts":<ordinal>,
  "pid":1,"tid":1,"args":{...}}`. The text trace carries no timestamps, so
  `ts` is the 0-based ordinal of the converted event (microseconds), which
  keeps the original order.
- `args` holds every other `key=value` field. Values made only of digits
  (no leading zero, up to 18 digits) are JSON numbers; everything else is a
  JSON string with `"`, `\` and control bytes escaped.
- Skipped lines (counted in `report->skipped`): not starting with
  `COREAPPTRACE `, `version` other than `1`, no `event=` field, a field
  without `=`, an empty key, or a duplicate key. Blank lines are ignored and
  not counted. CRLF is accepted.
- Output: `{"traceEvents":[...],` `BREAK_TRACE_OTHER_DATA` `}` plus `\n`.
  `report->bytes` is the size needed (without NUL). If `out` is NULL or too
  small the function returns `BREAK_TRACE_CONVERT_TOO_SMALL` and writes
  nothing past `capacity`.
- New category constant `BREAK_TRACE_CAT_CORE_APP "core_app"` in
  `core/trace_schema.h`.

## Tests
`test_trace_core_app` (headless): converts a sample with numbers, strings,
escapes and CRLF; checks event count, skipped count, exact JSON; the size query
path; and each skip rule.

## Docs
Status here, `docs/Implementation_Status.md`,
`docs/cross_engine/missing_capabilities.md` section 13,
`docs/design/core_app_integration.md` (trace section).

## Status
- RED: `test_trace_core_app` built against a stub returning INVALID; 0/3.
- GREEN: `engine/src/core/trace_core_app.{h,c}` (also compiled into
  `engine`), `BREAK_TRACE_CAT_CORE_APP` in `core/trace_schema.h`; 3/3.
- Mutation: 18 single-site mutations, all killed after adding a
  whitespace-only CRLF line, a `\x1f` byte and a `1:2` value to the sample.
- Still missing: no `core_app` CLI flag or tool writes the JSON next to the
  text trace yet; the converted events have ordinal timestamps only, so
  cross-process/network merge still has no shared clock.
