# core_app: write ts_us into the text trace

Status: Done

## Context

The trace converter accepts an optional `ts_us=<microseconds>` field
(2026-11-16-core-app-trace-timestamps.md), but core_app never writes it, so
`--trace-json` output still uses event ordinals as time. The converter rule
is "every line or none".

## Design

- `core/trace_core_app.h` gains the writer side:
  - `break_trace_core_app_set_clock(u64 (*now_us)(void))`: process-wide,
    NULL (the default) turns timestamps off. Stored atomically; core_app
    sets it once before any trace thread starts.
  - `break_trace_core_app_fprintf(FILE *, const char *format, ...)`: formats
    the text, and when a clock is set and the text starts with
    `COREAPPTRACE version=1 `, inserts `ts_us=<now> ` right after that
    prefix. One `fwrite` per call (no interleaving between threads, as
    before). Returns the bytes written or a negative value, like fprintf.
  - `break_trace_core_app_write(FILE *, const char *text)`: the same for
    already-formatted text.
- Every core_app trace writer goes through these functions: `app_trace`
  (core_app.c), `render_trace` and the world / skinned lines
  (core_app_render.c), the audio lines (core_app_audio.c), `app_gpu_trace`
  (core_app_gpu.c), `net_trace` (core_app_net_transport.c). Continuation
  chunks of the world line do not start with the prefix and are written
  verbatim.
- `core_app --trace-timestamps` (requires `--trace`) sets the clock to
  `time_microseconds()` (monotonic; one host shares the origin, so traces of
  several processes on one machine line up in `trace_merge`). Without the
  flag every trace is byte-for-byte unchanged.

## Tests (written first)

1. test_trace_core_app: with a fake clock the prefix line gains `ts_us`;
   without a clock, and for text without the prefix, output is verbatim;
   a line longer than the stack buffer is stamped correctly; the stamped
   output converts with `timestamped == events`.
2. test_core_app_target_contract: `--trace-timestamps` without `--trace`
   exits 2 with a message; help lists the flag.
3. test_core_app_lifecycle: a run with `--trace-timestamps --trace-json`
   stamps every trace line, the JSON has no ordinal `"ts":0` start and
   `timestamped` equals the line count (checked through the JSON). The
   default run stays unchanged (all existing assertions).

## Verification

Unit and lifecycle tests, mutation run, ASan/TSan for the converter test,
three full build trees, banned-word check, commit and push.

## Result

test_trace_core_app 7/7; the core_app target contract and the lifecycle
load_unload test cover the flag (RED with the old main.c). Mutation: 10 of
10 killed. ASan and TSan clean on three runs. The writer calls vfprintf
directly when no clock is set, because the lifecycle fault-injection preload
hooks vfprintf to fail specific trace lines.
