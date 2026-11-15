# Runtime profiler: Chrome trace flow events

Gap: `missing_capabilities.md` §13 — correlation IDs reach the profiler bridge
meta values (`cid=`), but Chrome/Perfetto cannot draw the causal chain.

## Approach

New bridge function in `engine/src/runtime/runtime_profiler.{h,c}`;
`engine/src/core/profiler.c` stays unchanged.

`break_runtime_profiler_export_flows(profiler, base_us, buf, cap, &len)`
(owner thread only) writes comma-separated Chrome trace event objects for the
presentation window, ready to splice into a `traceEvents` array:

- every correlated entry (cid != 0) -> 1 us slice `ph:"X"`, `dur:1`,
  `cat:"runtime"`, `ts = ts_us - base_us` (clamped at 0), `args.cid`; a slice
  (not an instant) so the flow events have an enclosing slice to bind to;
- a cid seen at least twice -> flow events `ph:"s"` (first), `"t"` (middle),
  `"f"` (last); all flow events carry `bp:"e"`, `id = cid`, `cat:"runtime.flow"`;
- a cid seen once -> slice only; uncorrelated entries -> nothing.
- names are JSON-escaped.
- buffer too small -> OVERLOAD with `*out_len` = bytes required (excluding
  NUL), nothing partial reported as success.

## Tasks

1. RED: `profiler_flow_export_links_cross_thread_chain` in
   `engine/tests/test_runtime_reload.c`.
2. GREEN: implement.
3. Mutation: phase selection, single-cid skip, overflow report, escape.
4. Docs: `runtime_thread_model.md` addendum, Implementation_Status entry.

## Status (2026-11-15)

Delivered. Tasks 1–4 done: test 34/34 in `test_runtime_reload`, six mutations killed, full ctest 401/401.
