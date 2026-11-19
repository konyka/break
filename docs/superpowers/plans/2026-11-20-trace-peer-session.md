# Plan: a peer trace that names its own session

Spec: `docs/superpowers/specs/2026-11-20-trace-peer-session-design.md`.

1. **RED (core, text)**: `break_trace_core_app_session` declared and a
   `test_trace_core_app` case over a welcome line, repeats, conflicts and
   the malformed forms. Fails to compile first.
2. **GREEN (core, text)**: the line scan, reusing `trace_parse_line` and
   `trace_parse_session`, with repeats of the same session accepted.
3. **RED/GREEN (core, JSON)**: `..._session_from_chrome` for the converted
   document trace_merge actually reads, since the tool's inputs are Chrome
   trace-event JSON rather than trace text.
4. **GREEN (tool)**: with `--clock-offset` and more than two inputs, a peer
   without `--session` has its own document read for the session; the
   "needs exactly two inputs or --session per peer" usage error narrows to
   the single-input case, so three peers that name themselves now merge.
5. **Mutations** (each must fail a test): the AMBIGUOUS check firing on a
   repeat of the same session, the event name length off by one, the session
   field not parsed, the output written before the NOT_FOUND return, the
   tool's lookup disabled, and the tool recording session 0.
6. **Docs**: `docs/Implementation_Status.md`,
   `docs/cross_engine/missing_capabilities.md`, spec Result.
7. **Verification**: full `ctest` in `build-core-app-net`, the ASan tree,
   push, CI.
