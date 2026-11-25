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
    /* Zero selects 8 entries, 1 MiB of BRWD history, 64 KiB per packet and a
     * 30-tick need-full interval. Limits are per connection. */
    size_t history_entry_limit;
    size_t history_byte_limit;
    size_t packet_byte_limit;
    u64 need_full_tick_interval;
} BreakWorldSessionConfig;

#define BREAK_WORLD_SESSION_CONTROL_WIRE_SIZE 32u
#define BREAK_WORLD_SESSION_CONTROL_WIRE_SIZE_V2 40u

typedef enum {
    BREAK_WORLD_SESSION_CONTROL_NEED_FULL = 1,
    BREAK_WORLD_SESSION_CONTROL_ACK = 2
} BreakWorldSessionControlKind;

typedef struct {
    BreakWorldSessionControlKind kind;
    u64 delta_id;
    u64 target_snapshot_id;
    u64 target_tick;
    u64 level_generation;
} BreakWorldSessionControl;

typedef struct {
    size_t history_count;
    size_t history_bytes;
    u64 confirmed_snapshot_id;
    u64 confirmed_tick;
    u64 next_delta_id;
    bool attempt_pending;
    u64 attempt_target_snapshot_id;
    u64 attempt_target_tick;
} BreakWorldSessionSenderState;

typedef struct {
    size_t applied_packets;
    size_t need_full_packets;
    size_t rejected_packets;
    size_t drained_packets;
    size_t need_full_suppressed;
    size_t published_full_packets;
    size_t published_delta_packets;
    size_t acknowledged_packets;
    BreakReplicationSessionBridgeStats bridge;
} BreakWorldSessionStats;

u64 break_world_session_stream_epoch(u64 protocol_version, u64 schema_hash,
                                     u64 level_generation);
BreakWorldSession *break_world_session_create(const BreakWorldSessionConfig *config);
void break_world_session_destroy(BreakWorldSession *session);
BreakReplicationSessionBridge *break_world_session_bridge(BreakWorldSession *session);
bool break_world_session_rebaseline(BreakWorldSession *session, u64 level_generation);
u64 break_world_session_level_generation(const BreakWorldSession *session);
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
/* NEED_FULL is rate-limited per connection and takes priority over the latest
 * coalesced ACK. The caller may send the returned value more than once after a
 * transport overload; polling consumes only the local event. */
bool break_world_session_poll_control(BreakWorldSession *session,
                                      BreakConnectionKey connection,
                                      BreakWorldSessionControl *out_control);
BreakNetSendResult break_world_session_send_control(
    BreakWorldSession *session, BreakConnectionKey connection,
    const BreakWorldSessionControl *control);
BreakNetSendResult break_world_session_send_control_correlated(
    BreakWorldSession *session, BreakConnectionKey connection,
    const BreakWorldSessionControl *control, u64 correlation_id);
/* BreakSessionMessageHandler for 0x400B. ACK requires an exact history
 * (delta_id, target id, tick) match and trims through that entry. NEED_FULL
 * forces the next newly created attempt to be full. */
bool break_world_session_handle_control(BreakConnectionKey connection,
                                        const BreakNetOwnedMessage *message,
                                        void *user_data);
/* Publishes a full packet until an ACK establishes a baseline. Delta chains
 * use the newest unacknowledged target. History or packet budget pressure and
 * NEED_FULL fall back to full with a fresh delta_id. An OVERLOAD leaves the
 * immutable attempt pending; the next call resumes unsent fragments without
 * reading the supplied World again. */
BreakNetSendResult break_world_session_publish(BreakWorldSession *session,
                                               BreakConnectionKey connection,
                                               World *world, u64 tick);
/* Borrows an immutable target and lets this connection's attempt/history retain
 * it. An active attempt resumes without inspecting target or level_generation. */
BreakNetSendResult break_world_session_publish_snapshot(
    BreakWorldSession *session, BreakConnectionKey connection,
    BreakWorldSnapshot *target, u64 level_generation);
bool break_world_session_sender_state(const BreakWorldSession *session,
                                      BreakConnectionKey connection,
                                      BreakWorldSessionSenderState *out_state);
void break_world_session_stats(const BreakWorldSession *session,
                               BreakWorldSessionStats *out_stats);

#ifdef __cplusplus
}
#endif
