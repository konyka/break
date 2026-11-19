# Plan: a single-session peer and the merge chain

Spec: `docs/superpowers/specs/2026-11-20-single-session-peer-design.md`.

1. **GREEN (client)**: the `single` scenario, reusing
   `client_answer_server_probes` so the server traces this session's offset.
2. **GREEN (tool)**: `trace_convert`, and the self-naming lookup no longer
   gated on more than two inputs.
3. **RED/GREEN (driver)**: `MODE=single` converts both traces, merges with
   no `--session`, and asserts the reported session, the offset line and
   both inputs in the result; the loopback statistics are scoped out of
   this mode.
4. **Mutations** (must fail the new test): the self-naming lookup disabled.
5. **Docs**: `docs/Implementation_Status.md`,
   `docs/cross_engine/missing_capabilities.md`, spec Result.
6. **Verification**: full `ctest` in `build-core-app-net` (the loopback and
   late-auth tests must stay green), push, CI.
