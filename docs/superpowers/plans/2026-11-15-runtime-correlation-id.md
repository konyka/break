# Runtime correlation IDs (2026-11-15)

Gap: `docs/cross_engine/missing_capabilities.md` §13 lists "跨线程/网络关联 ID"
as missing. `docs/design/runtime_message_model.md:163` already plans a
`correlation_id` envelope field, but `engine/src/runtime/` has none.

## Task 1: message correlation ID

- `BreakRuntimeMessageView` gains `u64 correlation_id` (0 = uncorrelated).
  Every existing construction site zeroes the view first, so they keep 0.
- `break_runtime_message_copy` stores it; `break_runtime_message_view`
  returns it.
- `break_runtime_correlation_next()`: process-wide, thread-safe (C11 atomic),
  never returns 0, strictly increasing per process.

Tests (`engine/tests/test_runtime_facade.c`):
`message_copy_keeps_correlation_id`,
`correlation_next_is_unique_across_threads` (4 threads x 1000 ids, all
distinct and non-zero).

## Task 2: profiler events carry the correlation ID

- `break_runtime_profiler_record_correlated(profiler, name, correlation_id)`;
  `break_runtime_profiler_record` is the same call with 0.
- Exported meta value: `tid=N ts=US` when the ID is 0, otherwise
  `tid=N ts=US cid=ID`. `BREAK_RUNTIME_PROFILER_VALUE_CAPACITY` grows from 56
  to 80 so the longest value fits without truncation.

Test (`engine/tests/test_runtime_reload.c`):
`profiler_correlated_events_export_cid`, including two events recorded on
different threads that share one ID.

## Out of scope

Network wire format (`BreakNetEnvelope`) and Chrome trace flow events. Both
are follow-ups once a consumer exists.

## Verification

Full CTest in `build-core-app-master`, plus a mutation check per new branch.
Docs: `runtime_message_model.md` addendum, `Implementation_Status.md`.
