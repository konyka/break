# Session Semantics Closeout Report

## Scope

This closeout implements Session-side semantic enforcement only. Snowflake and real adapter callback source remain unchanged.

## Contracts

- Message registry phase is enforced by `BreakSessionManager` on the GameThread.
- AUTH dispatch occurs while authenticating; a handler failure does not authenticate and moves the entry to `CLOSING`.
- PING is idempotent for a repeated `(connection, sequence)` and does not dispatch its handler twice.
- Closed entries retain their lifetime slot and classify later events as stale; they are never rebound.
- `break_session_manager_last_result` and `break_session_manager_apply_stats` expose applied, unknown, stale, invalid, phase-rejected, duplicate, and handler-failed outcomes.
- Handler message payloads are borrowed for the callback duration only; callers must copy data they retain.

## TDD Evidence

Focused tests in `engine/tests/test_break_session.c` lock AUTH failure, PING idempotence, stale close/pagination, lifetime capacity for closed slots, and apply statistics. The tests use the adapter event queue only through the public Session polling/apply API; Snowflake and adapter callback source remain unchanged.

## Verification

- Focused normal: `cmake --build build-outbound-contract --target test_break_net_adapter test_break_session -j2`, then both binaries passed (30/30 adapter; 20/20 Session), including real loopback client-close polling and final `CLOSED`/stale assertions.
- Focused ASan: `cmake --build build-outbound-asan --target test_break_net_adapter test_break_session -j2` and both binaries passed with `ASAN_OPTIONS=detect_leaks=1` (30/30 adapter; 20/20 Session).
- Focused TSan: `cmake --build build-outbound-tsan --target test_break_net_adapter test_break_session -j2` and both binaries passed with `TSAN_OPTIONS=halt_on_error=1` (30/30 adapter; 20/20 Session), with no race report.
- The adapter close test accepts either Snowflake close classification (`CONNECTION_CLOSED` or `TRANSPORT_ERROR`), requires the real connection key, and observes identity count return to zero. Session polling permits implementation-defined same-call `CLOSING` finalization but requires `CLOSED` before stale-event rejection.
- Snowflake and adapter/session production sources were not modified by this test task. No commit was created.
