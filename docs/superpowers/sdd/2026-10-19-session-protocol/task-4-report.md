# Task 4: GameThread-owned SessionManager

## Scope

Implemented SessionManager event integration only. Snowflake adapter connection/callback source was not modified. SessionManager remains an opaque C11 handle and owns all session mutations; adapter callbacks continue to enqueue immutable events only.

## RED evidence

Added focused tests in `engine/tests/test_break_session.c` for:

- attaching a manager to an adapter and polling opened/message events;
- AUTH handler registration and exactly-once first-auth dispatch;
- rejecting message/open events after a close watermark;
- preserving owned event payload lifetime until the manager releases the event.

Before implementation, `build-session-red` failed to compile because the required attach, handler-registration, and adapter-poll APIs did not exist.

## Implementation

- `engine/src/network/break_session.h`: exposes reactor attachment, message-handler registration, and GameThread adapter polling APIs.
- `engine/src/network/break_session.c`: polls the adapter FIFO, applies lifecycle events deterministically, validates the attached registry/version/payload limits, enforces definition-driven phase and duplicate policy, transitions AUTH through `NEW -> AUTHENTICATING -> AUTHENTICATED` only after handler success, and releases each owned event after dispatch.
- `BreakSessionConfig.registry` is an optional borrowed registry attachment; NULL selects the default registry. Duplicate tracking is per definition slot, so future registry entries follow the same `REJECT`/`IDEMPOTENT` policy without message-ID special cases.
- Closed entries are deliberately retained and are not reclaimed/rebound. This is the explicit capacity contract: `max_sessions` is a lifetime connection-key binding capacity for a manager, and a closed key cannot be rebound.
- No Session/ECS/Lua/UI calls occur from adapter callbacks. Handler callbacks are GameThread dispatch callbacks and receive only connection key plus borrowed event message during the call.

## Verification

All focused tests passed:

- Normal: `cmake --build build-session-red --target test_break_session -j2`; `ctest --test-dir build-session-red --output-on-failure -R '^test_break_session$'` — 13/13 passed.
- ASan: `cmake --build build-session-asan --target test_break_session -j2`; `ASAN_OPTIONS=detect_leaks=1 ctest --test-dir build-session-asan --output-on-failure -R '^test_break_session$'` — passed.
- TSan: `cmake --build build-outbound-tsan --target test_break_session -j2`; `TSAN_OPTIONS=halt_on_error=1 ctest --test-dir build-outbound-tsan --output-on-failure -R '^test_break_session$'` — passed.
- `git diff --check` — passed.

## Remaining boundary

This task does not implement Snowflake outbound send wiring. The adapter still documents and preserves its existing ownership blocker in `break_net_drain_outbound`; no fake sent result was added. Full CTest/build was not run because this focused task is gated on the Snowflake-enabled session targets and the working tree contains unrelated task changes.

## Follow-up: owned-message test construction

The ping duplicate test initially shallow-copied `BreakNetOwnedMessage` with `duplicate = first` and then attempted a second copy. Because `break_net_message_copy` rejects a destination that already owns payload state, that copy returned `BREAK_NET_MESSAGE_INVALID`; the two aliased events then also caused incorrect release behavior. The test now leaves both zero-initialized event structs independent and copies the same borrowed view into `first.message` and `duplicate.message` separately, so each event owns and releases its payload exactly once. The duplicate assertion reflects the existing API contract: duplicate application returns `false`, records `BREAK_SESSION_APPLY_DUPLICATE`, and does not dispatch the handler twice.

Verification after rebuilding the current 16-test source:

- Normal: `cmake --build build-session-red --target test_break_session -j2`; `ctest --test-dir build-session-red --output-on-failure -R '^test_break_session$'` — passed.
- ASan: `cmake --build build-session-asan --target test_break_session -j2`; `ASAN_OPTIONS=detect_leaks=1:halt_on_error=1 ctest --test-dir build-session-asan --output-on-failure -R '^test_break_session$'` — passed, no leak/error output.
- TSan: `cmake --build build-outbound-tsan --target test_break_session -j2`; `TSAN_OPTIONS=halt_on_error=1 ctest --test-dir build-outbound-tsan --output-on-failure -R '^test_break_session$'` — passed, no race report.
- `git diff --check` — passed.
- Production Session logic now includes registry-driven policy; Snowflake and adapter callback source were not modified.
- Production Session logic was not modified.
