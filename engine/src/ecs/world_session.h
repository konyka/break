#pragma once

#include <ecs/world_delta_wire.h>
#include <network/break_replication_session.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Every function is owner-thread only. The bridge callback only reassembles and
 * queues BRFG completions; break_world_session_drain is the sole World apply
 * entry point. schemas, clock state and each drained World are borrowed. */
typedef struct BreakWorldSession BreakWorldSession;

typedef struct {
    const BreakComponentSchemaRegistry *schemas;
    u64 protocol_version;
    u64 level_generation;
    BreakReplicationSessionBridgeConfig bridge;
} BreakWorldSessionConfig;

typedef struct {
    size_t applied_packets;
    size_t need_full_packets;
    size_t rejected_packets;
    size_t drained_packets;
    BreakReplicationSessionBridgeStats bridge;
} BreakWorldSessionStats;

u64 break_world_session_stream_epoch(u64 protocol_version, u64 schema_hash,
                                     u64 level_generation);
BreakWorldSession *break_world_session_create(const BreakWorldSessionConfig *config);
void break_world_session_destroy(BreakWorldSession *session);
BreakReplicationSessionBridge *break_world_session_bridge(BreakWorldSession *session);
bool break_world_session_open(BreakWorldSession *session, BreakConnectionKey connection);
bool break_world_session_close(BreakWorldSession *session, BreakConnectionKey connection);
/* Returns false for an unknown connection. An open connection without a
 * confirmed target reports zero id/tick. Outputs are optional. */
bool break_world_session_baseline(const BreakWorldSession *session,
                                  BreakConnectionKey connection,
                                  u64 *out_snapshot_id, u64 *out_tick);
/* Drains only this connection, preserving every other connection's queue order.
 * Decode failures increment rejected_packets. Valid BRWD packets rejected for
 * base/schema/level/target/apply also increment need_full_packets; rejected is
 * therefore the total failure count and need_full is a subset. */
size_t break_world_session_drain(BreakWorldSession *session,
                                 BreakConnectionKey connection, World *world,
                                 size_t max_packets);
void break_world_session_stats(const BreakWorldSession *session,
                               BreakWorldSessionStats *out_stats);

#ifdef __cplusplus
}
#endif
