# Snowflake C11 Network Adapter Design

**Status:** Approved for implementation as the first independent subsystem.

## Goal

Integrate the Break C11 runtime with `/home/timeshift/opensource/snowflake` without reimplementing transport primitives, while preserving strict GameThread ownership of game state and enabling both a dedicated reactor-thread mode and a deterministic step-driven test/editor mode.

## Scope

This subsystem owns the Break-side adapter only:

- Snowflake reactor lifecycle.
- Dedicated host-thread and caller-driven step modes.
- Inbound message ownership transfer to Break.
- Outbound send-command transfer to Snowflake.
- Protocol envelope length/version/sequence validation.
- Connection event translation.
- Shutdown, drain, cancellation, and error mapping.
- C11 API and tests.

It does not implement ECS replication, AoI, login business rules, Lua bindings, editor RPC, online updates, anti-cheat, or multi-process service decomposition. Those consume this adapter through stable C11 interfaces in later subsystems.

## Source Contracts

Snowflake is a C project (`project(... LANGUAGES C)`, C11 interface) and currently exposes a passive `snow_net_thread_t` reactor. The reactor is driven by `snow_net_thread_run()` or `snow_net_thread_step()` on exactly one driver thread. It does not create the host pthread itself. Cross-context `_send`, `_close`, and `_terminate` operations use Snowflake's notification path and are drained by the reactor.

The adapter may use Snowflake's `snow_net_thread_t`, `snow_connection_t`, `snow_connection_list_t`, `snow_acceptor_t`, `snow_epoller_t`, `snow_send_context_t`, `snow_recv_context_t`, `snow_network_buffer_t`, `snow_thread_t`, atomic primitives, and queues. It must not expose those concrete types through the game-facing API.

## Architecture

```text
Break GameThread
  |  validated inbound messages
  v
BreakNetAdapter inbound queue
  ^
  | parser callback copies/transfers bounded payload
Snowflake reactor host thread
  | snow_net_thread_run / snow_net_thread_step
  +-- epoll/io_uring/kqueue/IOCP
  +-- acceptor
  +-- connection list
  +-- parser and recv queue
  +-- send queue
  ^
  | outbound commands
BreakNetAdapter outbound queue
  ^
  | GameThread submits send request
Break GameThread
```

### Drive modes

- `BREAK_NET_DRIVE_THREAD`: Break creates one host OS thread for each adapter reactor. That thread alone calls Snowflake run/step APIs.
- `BREAK_NET_DRIVE_STEP`: the caller alone drives `step`; used by deterministic unit tests, offline tools, and editor-local preview.
- A reactor cannot switch modes after `start`.
- No adapter API performs a blocking wait on the GameThread.

### Ownership

- Snowflake owns socket/fd, epoller, connection internals, and transport queues.
- The reactor thread owns Snowflake connection mutation.
- Break owns copied inbound envelopes after the parser callback returns.
- Break owns outbound command payloads until the reactor callback converts them to Snowflake send contexts.
- `BreakNetMessageView.data` is callback/poll scoped and must not be retained.
- GameThread owns sessions, ECS, World, and Lua.

## Public C11 API

```c
typedef struct BreakNetReactor BreakNetReactor;
typedef struct BreakNetConnection BreakNetConnection;

typedef enum BreakNetDriveMode {
    BREAK_NET_DRIVE_THREAD = 0,
    BREAK_NET_DRIVE_STEP = 1
} BreakNetDriveMode;

typedef struct BreakNetReactorConfig {
    BreakNetDriveMode drive_mode;
    int logical_index;
    uint32_t max_connections;
    int empty_connection_timeout_ms;
    uint32_t watchdog_interval_ms;
    uint32_t step_timeout_ms;
} BreakNetReactorConfig;

typedef struct BreakNetMessageView {
    uint16_t message_id;
    uint16_t protocol_version;
    uint32_t sequence;
    const void *data;
    size_t size;
} BreakNetMessageView;

BreakNetReactor *break_net_reactor_create(const BreakNetReactorConfig *config);
void break_net_reactor_destroy(BreakNetReactor *reactor);
bool break_net_reactor_start(BreakNetReactor *reactor);
bool break_net_reactor_step(BreakNetReactor *reactor, int timeout_ms);
bool break_net_reactor_stop(BreakNetReactor *reactor, uint32_t timeout_ms);
bool break_net_reactor_is_ready(const BreakNetReactor *reactor);
```

The implementation may add a bounded polling API and an outbound send API, but all additions must remain C11, use opaque handles, document ownership, and avoid exposing Snowflake headers beyond the adapter translation unit.

## Thread Rules

- Snowflake parser/connection callbacks only validate framing, copy or transfer bounded data, update metrics, and enqueue an event.
- They must not call Lua, mutate ECS/World, call UI/RHI, perform blocking file/database work, or wait for GameThread.
- GameThread is the only owner of game sessions and gameplay state.
- `break_net_reactor_step` and Snowflake run APIs are single-driver operations.
- Stop first prevents new application messages, then wakes the reactor, stops accepts, drains or rejects sends according to policy, closes connections, joins the host thread, and only then destroys Snowflake objects.

## Protocol Envelope

The adapter validates before dispatch:

1. minimum header size;
2. total length within configured maximum;
3. protocol version supported by the adapter;
4. message ID registered or explicitly classified as unknown;
5. sequence policy (duplicate, backward, or excessive jump);
6. connection/session binding;
7. payload bounds;
8. optional authentication/integrity metadata supplied by the later protocol layer.

The adapter never interprets gameplay payload fields.

## Error Model

Snowflake status values are mapped to Break-owned categories:

- invalid argument/configuration;
- lifecycle/state violation;
- allocation failure;
- queue full/overload;
- timeout during stop;
- protocol framing/version/sequence rejection;
- transport closed;
- platform/initialization failure.

The mapping must preserve the original Snowflake status in diagnostics without exposing Snowflake ownership or requiring callers to include Snowflake headers.

## TDD Acceptance Criteria

The first implementation is accepted only when tests cover:

- null and invalid configuration rejection;
- step-mode create/start/step/stop/destroy;
- thread-mode create/start/stop/join/destroy;
- duplicate start and idempotent stop;
- readiness state transitions;
- stop wake-up and bounded timeout behavior;
- inbound copy lifetime and queue ownership;
- outbound queue ownership and send conversion;
- queue overload mapping;
- invalid length/version/sequence rejection;
- unknown message behavior;
- callback never directly mutating GameThread-owned state;
- Snowflake-disabled configuration failure without a hidden fallback;
- Linux C11 build;
- Windows C11 build when the platform toolchain is available;
- AddressSanitizer and ThreadSanitizer-compatible tests where supported.

## Future Consumers

Later subsystems depend only on the adapter contract:

- Session/login layer consumes connection events and sends authenticated responses.
- Replication/AoI consumes validated inbound commands and immutable snapshots.
- Lua consumes GameThread-dispatched messages only.
- myui Scene Editor uses a separate editor protocol over the same adapter.
- Diagnostics consumes adapter metrics and bounded event records.

## Non-goals and Limits

The adapter does not promise that external Snowflake or platform library internals are thread-safe beyond the documented single-driver and queue contracts. It does not provide client trust, anti-cheat guarantees, gameplay authorization, or encryption policy by itself. Those are later protocol/security layers and must not be silently inferred from transport availability.
