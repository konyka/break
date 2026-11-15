# Unified trace schema marker and category names

## Goal
`core/profiler.c` and `runtime/runtime_profiler.c` both write Chrome trace
JSON, but each spells its category strings inline and neither file says
which format it follows. A consumer cannot tell a break trace from any other
Chrome trace, or which category set to expect.

## Design
- New header `engine/src/core/trace_schema.h` (no .c):
  - `BREAK_TRACE_SCHEMA_NAME "break.trace"`, `BREAK_TRACE_SCHEMA_VERSION 1`.
  - Category constants: `BREAK_TRACE_CAT_CPU "cpu"`, `_FRAME "frame"`,
    `_GPU "gpu"`, `_META "meta"`, `_RUNTIME "runtime"`,
    `_RUNTIME_FLOW "runtime.flow"`.
  - `BREAK_TRACE_OTHER_DATA` = the JSON member
    `"otherData":{"schema":"break.trace","schema_version":1}`.
- Both `profiler_export_chrome_trace` and `profiler_export_chrome_trace_ring`
  end the file with `],` + `BREAK_TRACE_OTHER_DATA` + `}` instead of `]}`.
  `otherData` is part of the Chrome Trace Event Format, so viewers still load
  the file.
- Every category literal in both exporters uses the constants. Output bytes
  for events do not change.
- `export_flows` writes fragments spliced into a caller's array, so it gets
  no marker; its categories use the constants.

## Tests (`test_profiler`)
- `profiler_export_marks_trace_schema`: both exporters' files contain the
  marker exactly once, end with `}}\n`, and every `"cat":"..."` value is one
  of the six constants.

## Docs
- `docs/design/runtime_thread_model.md` addendum: schema name, version,
  categories, and where they are defined.
- Status here, `docs/Implementation_Status.md`,
  `docs/cross_engine/missing_capabilities.md` section 13.

## Status
- Done. `test_profiler` RED (missing `core/trace_schema.h`), then GREEN.
- `test_runtime_reload` flow test also counts the `runtime` (4) and
  `runtime.flow` (3) categories, so the runtime exporter is covered too.
- `BREAK_TRACE_PID` was dropped from the design: no consumer needs it.
- Mutations (6): both document trailers reverted to `]}`, one `cpu`
  category per exporter renamed, the `runtime` and `runtime.flow`
  categories renamed. All killed.
- Still missing: merging traces across processes or network peers; the
  core_app text trace (COREAPPTRACE) does not use this schema.
- Follow-up: Windows CI (MSVC, MinGW, Clang, D3D12) failed
  `profiler_export_marks_trace_schema` because the exporters open the file
  in text mode and Windows ends it with `\r\n`. The test now strips one
  trailing `\n` and an optional `\r` before checking for `}}`. Both trailer
  mutations are still killed.
