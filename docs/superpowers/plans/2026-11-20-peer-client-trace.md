# Plan: the loopback peer writes its own trace

Spec: `docs/superpowers/specs/2026-11-20-peer-client-trace-design.md`.

1. **GREEN (client)**: a `--trace PATH` argument (scanned after the optional
   scenario name), `break_trace_core_app_set_clock(now_us)` so the lines are
   stamped like core_app's, and one
   `event=network_session_welcome session=N` line per accepted welcome. The
   report gains `client trace_lines=N`.
2. **Build**: `test_core_app_net_client` links `src/core/trace_core_app.c`.
3. **RED/GREEN (driver)**: `test_core_app_network.cmake` passes `--trace`,
   then asserts the file exists, is stamped, names at least one session,
   that every named session was authenticated by the server, and that the
   counts agree with the server's authenticated lines.
4. **Mutations** (each must fail the loopback test): the traced session off
   by one, and the trace clock not set.
5. **Docs**: `docs/Implementation_Status.md`,
   `docs/cross_engine/missing_capabilities.md`, spec Result.
6. **Verification**: full `ctest` in `build-core-app-net`, push, CI.
