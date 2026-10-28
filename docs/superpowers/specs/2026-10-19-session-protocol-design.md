# Break Session and Protocol Envelope Design

**Status:** Approved for staged implementation after Snowflake adapter completion.

## Goal

Add a C11 game-session and protocol-envelope layer above the completed Snowflake adapter without allowing network callbacks to mutate GameThread-owned World, ECS, Lua, or UI state.

## Scope

This phase adds:

- Stable envelope encode/decode.
- Message ID registry and version policy.
- Connection-open/close events translated to GameThread-owned events.
- Session state machine: `NEW`, `AUTHENTICATING`, `AUTHENTICATED`, `CLOSING`, `CLOSED`.
- Connection-to-session binding owned by GameThread.
- Inbound polling and outbound send-command transfer at the adapter boundary.
- Length, version, sequence, authentication-state, and replay-window checks.
- C11 tests and documentation.

It does not add player authentication backend, ECS replication, AoI, Lua gameplay callbacks, editor RPC, online updates, or security beyond envelope/session checks.

## Ownership

```text
Snowflake reactor thread
  -> parser/connection callback
  -> bounded adapter event queue
  -> GameThread poll
  -> SessionManager / World commands
  -> bounded outbound command queue
  -> Snowflake reactor send/close notification
```

Network callbacks may create immutable event records only. Sessions and their state transitions are GameThread-owned. A Snowflake connection is represented by a Break opaque connection key, never by a business object pointer exposed to Lua.

## Envelope

Every application message has a fixed C11-defined prefix:

```text
magic | protocol_version | message_id | flags | sequence | payload_size
```

The implementation must use explicit byte order helpers, checked arithmetic, a configured maximum payload, and a registry lookup. Unknown IDs, unsupported versions, malformed lengths, invalid flags, and replay-window violations are rejected before business dispatch.

## Session API

```c
typedef struct BreakSessionManager BreakSessionManager;
typedef uint64_t BreakConnectionKey;
typedef uint64_t BreakSessionId;

typedef enum BreakSessionState {
    BREAK_SESSION_NEW = 0,
    BREAK_SESSION_AUTHENTICATING,
    BREAK_SESSION_AUTHENTICATED,
    BREAK_SESSION_CLOSING,
    BREAK_SESSION_CLOSED
} BreakSessionState;

BreakSessionManager *break_session_manager_create(const BreakSessionConfig *config);
void break_session_manager_destroy(BreakSessionManager *manager);
size_t break_session_manager_poll(BreakSessionManager *manager, uint32_t max_events);
bool break_session_manager_bind(BreakSessionManager *manager, BreakConnectionKey connection);
bool break_session_manager_begin_auth(BreakSessionManager *manager, BreakConnectionKey connection);
bool break_session_manager_close(BreakSessionManager *manager, BreakConnectionKey connection, uint32_t reason);
BreakSessionState break_session_manager_state(const BreakSessionManager *manager, BreakConnectionKey connection);
```

Exact signatures may be adjusted to current Break error conventions during Task 1, but handles remain opaque and all mutation remains GameThread-only.

## Thread and failure policy

- Parser callbacks never call SessionManager directly.
- Polling an event after connection close is safe and deterministic.
- A connection may have at most one active session.
- A session cannot transition backward from `AUTHENTICATED` to `NEW`.
- Unknown connection keys are rejected.
- Duplicate authentication messages are rejected or treated idempotently according to the message registry, never executed twice accidentally.
- Outbound overload produces a bounded error and does not block GameThread.
- Session close releases business state only after all queued events for that connection are classified as stale.

## Acceptance

Tests must cover envelope round trips, endian correctness, malformed lengths, unknown IDs, version negotiation, sequence duplicates/backward jumps, connection event ordering, legal/illegal session transitions, stale events after close, outbound overload, and ASan/TSan-compatible queue ownership.
