# Snowflake outbound send

## Contract

`break_net_reactor_send` accepts commands only while the reactor is `STARTED`; CREATED/FAILED/STOPPING/STOPPED return `BREAK_NET_SEND_CLOSED` before queue allocation. `max_connections` is bounded by the adapter's fixed 256-slot identity capacity; oversized configurations fail at create. When accepted, the function copies the Break message into a bounded outbound command. The reactor driver drains commands in both step and thread mode. A command is encoded as the 18-byte `BreakNetEnvelope` before it enters Snowflake; raw replication payload bytes are never passed to `snow_send_context_create_with`.

On connection open, the adapter copies the Snowflake identity needed for an outbound context: UID, fd, reactor/thread index, peer address text and port. It stores no raw `snow_connection_t *`. The adapter creates an independent `snow_recv_context_t` from that copied identity and creates a `snow_send_context_t` with `snow_send_context_create_with`.

`SNOW_OK` from `snow_net_thread_send` transfers send-context ownership to Snowflake. Any failure retains the Break command and frees the send context. A stale UID with no copied identity is dropped because it cannot be delivered safely. Queue capacity returns `BREAK_NET_SEND_OVERLOAD` before allocation beyond the bounded queue.

## Lifecycle

The step driver drains outbound commands before one Snowflake step. The dedicated host thread drains outbound commands before every Snowflake step. A successful send increments an identity in-flight reference; send-drained clears it. Close marks the identity closing and defers recv-context release until the pending count reaches zero. Failed sends release their temporary send context immediately.

Stop uses an adapter-owned bounded deadline in both drive modes. Thread mode calls Snowflake terminate, then waits for the host entry point to publish `host_exited`; step mode first publishes step-driver ownership and waits for an active step to publish completion. A timed-out call returns false and retains `STOPPING`, the Snowflake reactor, and live thread/step ownership; `destroy` remains a no-op and a later stop can finish. Only the cleanup owner that observes completion calls the unbounded platform join, Snowflake destroy, and terminal state transition. POSIX uses `pthread_cond_timedwait`; Windows uses `SleepConditionVariableCS`; no timed-join extension is used. Lifecycle waits never hold the lifecycle mutex while calling Snowflake.

Callbacks only enqueue Break events and perform bounded ownership operations; they do not call GameThread, ECS, Lua, or gameplay handlers.

## Verification

- RED: `break_net_adapter_thread_mode_drains_queued_command_before_step` failed before the fix because thread mode left the queued command untouched (`outbound_attempts == 0`); the test uses a real loopback socket and accepted Snowflake identity.
- GREEN: `cmake --build build-outbound-contract --target test_break_net_adapter -j2` and `./build-outbound-contract/test_break_net_adapter` passed (30/30 tests), including real loopback close-event delivery (`CONNECTION_CLOSED`/`TRANSPORT_ERROR`) and identity cleanup after client close.

Sanitizer verification:

- ASan: `cmake --build build-outbound-asan --target test_break_net_adapter test_break_session -j2`, `ASAN_OPTIONS=detect_leaks=1 ./build-outbound-asan/test_break_net_adapter`, and `ASAN_OPTIONS=detect_leaks=1 ./build-outbound-asan/test_break_session` passed (30/30 adapter; 20/20 Session), including the real close-event assertions.
- TSan: `cmake --build build-outbound-tsan --target test_break_net_adapter test_break_session -j2`, `TSAN_OPTIONS=halt_on_error=1 ./build-outbound-tsan/test_break_net_adapter`, and `TSAN_OPTIONS=halt_on_error=1 ./build-outbound-tsan/test_break_session` passed (30/30 adapter; 20/20 Session), with no race report.

## Compile follow-up

The adapter source was re-read after the reported compiler errors. `struct BreakNetReactor` now precedes the complete `break_net_identity_find` and `break_net_drain_outbound` definitions, so the helpers access a complete type; the identity helper is defined exactly once. Normal adapter target compilation succeeds.

The requested Session target compiles and runs through the adapter dependency; its focused normal, ASan, and TSan lanes pass. This change intentionally does not modify Session logic or Snowflake production code.

## Replication fixture follow-up

The four replication failures were caused by the tests creating a reactor in `CREATED` state while the production outbound contract requires `STARTED`. The replication fixture now creates a real loopback Snowflake endpoint and acceptor, binds it, calls `set_acceptor`, and starts the step reactor before exercising replication. It only inspects Break's outbound queue; it does not fake sockets or change the production send gate. Cleanup stops and destroys the reactor before destroying the acceptor.

Verification:

- Normal: `test_break_replication` 7/7, `test_break_net_adapter` 30/30, `test_break_session` 20/20, `test_break_replication_fragment` 7/7.
- ASan: the same four targets pass with `ASAN_OPTIONS=detect_leaks=1` (adapter 30/30; Session 20/20; replication and fragment 7/7).
- TSan: the same four targets pass with `TSAN_OPTIONS=halt_on_error=1` (adapter 30/30; Session 20/20; replication and fragment 7/7), with no race report.

The adapter limitation is not wire E2E or stop timeout: real inbound/outbound/close loopback E2E and bounded stop are implemented and covered. Remaining boundaries are coarse per-context Snowflake completion/drop notification, non-Linux platform lanes not verified on this host, full CTest's unrelated known failures, default full-tree fuzz executables intentionally not built (explicit fuzz lane passes 5/5), and the Session custom-registry codec boundary.

## Replication version-wrap hardening

The replication Real version is a monotonic `uint64_t` value. `break_replication_register` (existing object update) and `break_replication_mark_dirty` now fail closed when the current version is `UINT64_MAX`; there is no implicit epoch rollover. The guard runs before payload allocation or replacement, so a rejected update preserves the old payload, terminal version, and any per-connection Ghost state. New objects still start at version 1.

TDD evidence: the two `UINT64_MAX` tests were observed RED before the guard (both APIs accepted the update and wrapped), then GREEN after the guard with the old payload still sent in the baseline. Normal, ASan, and TSan `test_break_replication` each pass 7/7 with no sanitizer report.
