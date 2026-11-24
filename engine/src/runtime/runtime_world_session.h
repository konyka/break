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
    u64 submitted;
    u64 drained;
    u64 applied;
    u64 rejected;
    u64 stale_rejected;
    u64 transport_overloads;
    u64 next_sequence;
    usize queued;
    bool control_pending;
} BreakRuntimeWorldSessionStats;

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

#ifdef __cplusplus
}
#endif
