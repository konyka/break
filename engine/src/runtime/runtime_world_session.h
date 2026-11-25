#pragma once

#include <ecs/world_session.h>
#include <runtime/runtime_bus.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BREAK_RUNTIME_WORLD_SESSION_CONTROL_KIND 0x5753u

typedef enum {
    BREAK_RUNTIME_WORLD_COMMAND_OPEN = 1,
    BREAK_RUNTIME_WORLD_COMMAND_CLOSE = 2,
    BREAK_RUNTIME_WORLD_COMMAND_REBASELINE = 3,
    BREAK_RUNTIME_WORLD_COMMAND_ACK = 4,
    BREAK_RUNTIME_WORLD_COMMAND_NEED_FULL = 5
} BreakRuntimeWorldCommandKind;

typedef struct {
    u32 kind;
    u32 reserved_zero;
    u64 connection_key;
    u64 connection_epoch;
    u64 level_generation;
    u64 delta_id;
    u64 target_snapshot_id;
    u64 target_tick;
} BreakRuntimeWorldCommand;

BREAK_STATIC_ASSERT(sizeof(BreakRuntimeWorldCommand) == 56u,
                    "BreakRuntimeWorldCommand must be 56 bytes");

typedef struct BreakRuntimeWorldSession BreakRuntimeWorldSession;

typedef struct {
    BreakWorldSession *session;
    BreakRuntimeBus *bus;
    const char *subscriber_name;
    u32 queue_capacity;
    u32 max_connections;
} BreakRuntimeWorldSessionConfig;

typedef struct {
    u64 submitted;       /* successful direct submit calls only */
    u64 drained;         /* direct and external Bus messages actually consumed */
    u64 applied;
    u64 rejected;
    u64 stale_rejected;
    u64 transport_overloads;
    u64 next_sequence;
    usize queued;        /* queue enqueued-dequeued; excludes control_pending */
    bool control_pending;
} BreakRuntimeWorldSessionStats;

/* submit() validates, copies and enqueues only into this adapter's owned
 * queue; it never fans out through the bus. The registered kind/subscription
 * remains available to external producers: a direct Bus publish delivers an
 * independent copy to every adapter subscribed to that kind. Those external
 * messages increase drained/applied as consumed, never submitted or the
 * adapter-local Runtime sequence.
 *
 * submit(), close(), is_closed(), pending(), connection_epoch() and stats()
 * may run on any thread. drain() is the single-owner entry point and is the
 * only API that may call World Session. External Bus publishers use the bus' normal threading
 * contract and race only with queue admission, never with World calls.
 *
 * pending() is queue enqueued-dequeued plus control_pending, not
 * submitted-drained. destroy() first closes admission and unsubscribes, then
 * checks that actual pending count. Even a false destroy attempt therefore
 * prevents further direct or external ingress; drain/stats/epoch queries and
 * a later destroy retry remain valid, and the retry does not unsubscribe
 * twice. A fail-early destroy may overlap producers/drain only while pending
 * is known to keep it false. Before any destroy call that can succeed, the
 * caller must quiesce every other adapter API call and prevent new calls;
 * success invalidates the adapter. The borrowed bus/session stay caller-owned.
 */
BreakRuntimeWorldSession *break_runtime_world_session_create(
    const BreakRuntimeWorldSessionConfig *config);
bool break_runtime_world_session_destroy(
    BreakRuntimeWorldSession *adapter);
BreakRuntimeError break_runtime_world_session_submit(
    BreakRuntimeWorldSession *adapter,
    const BreakRuntimeWorldCommand *command,
    u64 correlation_id);
void break_runtime_world_session_close(
    BreakRuntimeWorldSession *adapter);
bool break_runtime_world_session_is_closed(
    const BreakRuntimeWorldSession *adapter);
BreakRuntimeError break_runtime_world_session_drain(
    BreakRuntimeWorldSession *adapter, usize max_messages,
    usize *out_drained);
usize break_runtime_world_session_pending(
    const BreakRuntimeWorldSession *adapter);
bool break_runtime_world_session_connection_epoch(
    const BreakRuntimeWorldSession *adapter, u64 connection_key,
    u64 *out_epoch);
void break_runtime_world_session_stats(
    const BreakRuntimeWorldSession *adapter,
    BreakRuntimeWorldSessionStats *out_stats);

#ifdef BREAK_RUNTIME_TESTING
void break_runtime_world_session_set_next_connection_epoch_for_test(
    BreakRuntimeWorldSession *adapter, u64 next_epoch);
#endif

#ifdef __cplusplus
}
#endif

#include <runtime/runtime_world_session_lifecycle.h>
