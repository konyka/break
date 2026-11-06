#pragma once

#include <network/break_online_aspect.h>
#include <network/break_replication_fragment.h>
#include <network/break_aoi.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct BreakAspectReplication BreakAspectReplication;

typedef BreakRuntimeError (*BreakAspectSendFn)(
    void *user, u64 connection_id, const BreakReplicationFragment *fragment);

typedef struct BreakAspectReplicationConfig {
    u32 max_connections;
    u32 max_objects;
    usize max_packet_bytes;
    u32 max_fragments;
    BreakAspectSendFn send;
    void *send_user;
} BreakAspectReplicationConfig;

BreakRuntimeError break_aspect_replication_create(
    const BreakAspectReplicationConfig *config, BreakAspectStore *store,
    BreakSpatialIndex *borrowed_index, BreakAspectReplication **out);
void break_aspect_replication_destroy(BreakAspectReplication *replication);
BreakRuntimeError break_aspect_object_register(
    BreakAspectReplication *replication, const BreakReplicationObject *desc,
    BreakOnlineHandle *out);
BreakRuntimeError break_aspect_connection_open(
    BreakAspectReplication *replication, u64 connection_id,
    usize bandwidth_budget, usize fragment_size);
BreakRuntimeError break_aspect_replication_disconnect(
    BreakAspectReplication *replication, u64 connection_id);
u32 break_aspect_replication_connection_count(
    const BreakAspectReplication *replication);

BreakRuntimeError break_aspect_replication_set_u32(
    BreakAspectReplication *replication, BreakOnlineHandle object,
    u32 aspect_id, u32 value);
BreakRuntimeError break_aspect_replication_set_i32(
    BreakAspectReplication *replication, BreakOnlineHandle object,
    u32 aspect_id, i32 value);
BreakRuntimeError break_aspect_replication_set_f32(
    BreakAspectReplication *replication, BreakOnlineHandle object,
    u32 aspect_id, f32 value);
BreakRuntimeError break_aspect_replication_set_bytes(
    BreakAspectReplication *replication, BreakOnlineHandle object,
    u32 aspect_id, const void *data, u32 size);
BreakRuntimeError break_aspect_replication_set_flags(
    BreakAspectReplication *replication, BreakOnlineHandle object, u32 flags);

BreakRuntimeError break_aspect_replication_sync(
    BreakAspectReplication *replication, u64 connection_id,
    const BreakAoIResult *aoi, usize bandwidth_budget);
BreakRuntimeError break_aspect_replication_sync_default(
    BreakAspectReplication *replication, u64 connection_id,
    const BreakAoIResult *aoi);

#ifdef __cplusplus
}
#endif
