#include <ecs/world_session.h>

#include <network/break_net_message_registry.h>

#include <stdlib.h>
#include <string.h>

#define WORLD_STREAM_HASH_OFFSET UINT64_C(1469598103934665603)
#define WORLD_STREAM_HASH_PRIME UINT64_C(1099511628211)

typedef struct {
    BreakConnectionKey key;
    BreakWorldSnapshot *baseline;
} BreakWorldSessionConnection;

struct BreakWorldSession {
    const BreakComponentSchemaRegistry *schemas;
    u64 protocol_version;
    u64 level_generation;
    BreakReplicationSessionBridge *bridge;
    BreakWorldSessionConnection *connections;
    size_t max_connections;
    size_t applied_packets;
    size_t need_full_packets;
    size_t rejected_packets;
    size_t drained_packets;
};

static u64 stream_hash_u64(u64 hash, u64 value)
{
    for (u32 i = 0u; i < 8u; ++i) {
        hash ^= (u8)(value >> (i * 8u));
        hash *= WORLD_STREAM_HASH_PRIME;
    }
    return hash;
}

u64 break_world_session_stream_epoch(u64 protocol_version, u64 schema_hash,
                                     u64 level_generation)
{
    u64 hash = WORLD_STREAM_HASH_OFFSET;
    hash = stream_hash_u64(hash, protocol_version);
    hash = stream_hash_u64(hash, schema_hash);
    return stream_hash_u64(hash, level_generation);
}

static size_t world_session_connection_index(const BreakWorldSession *session,
                                             BreakConnectionKey connection)
{
    if (!session || connection == 0u) return session ? session->max_connections : 0u;
    for (size_t i = 0u; i < session->max_connections; ++i) {
        if (session->connections[i].key == connection) return i;
    }
    return session->max_connections;
}

BreakWorldSession *break_world_session_create(const BreakWorldSessionConfig *config)
{
    BreakWorldSession *session;
    BreakReplicationSessionBridgeConfig bridge_config;
    if (!config || !config->schemas || config->protocol_version == 0u) return NULL;
    session = (BreakWorldSession *)calloc(1u, sizeof(*session));
    if (!session) return NULL;
    session->schemas = config->schemas;
    session->protocol_version = config->protocol_version;
    session->level_generation = config->level_generation;
    session->max_connections = config->bridge.max_connections;
    bridge_config = config->bridge;
    bridge_config.message_id = BREAK_NET_MESSAGE_ID_WORLD_DELTA;
    session->bridge = break_replication_session_bridge_create(&bridge_config);
    session->connections = (BreakWorldSessionConnection *)calloc(
        config->bridge.max_connections, sizeof(*session->connections));
    if (!session->bridge || !session->connections) {
        break_replication_session_bridge_destroy(session->bridge);
        free(session->connections);
        free(session);
        return NULL;
    }
    return session;
}

void break_world_session_destroy(BreakWorldSession *session)
{
    if (!session) return;
    for (size_t i = 0u; i < session->max_connections; ++i)
        break_world_snapshot_release(session->connections[i].baseline);
    free(session->connections);
    break_replication_session_bridge_destroy(session->bridge);
    free(session);
}

BreakReplicationSessionBridge *break_world_session_bridge(BreakWorldSession *session)
{
    return session ? session->bridge : NULL;
}

bool break_world_session_open(BreakWorldSession *session, BreakConnectionKey connection)
{
    size_t slot = session ? session->max_connections : 0u;
    u64 epoch;
    if (!session || connection == 0u ||
        world_session_connection_index(session, connection) != session->max_connections) {
        return false;
    }
    for (size_t i = 0u; i < session->max_connections; ++i) {
        if (session->connections[i].key == 0u) {
            slot = i;
            break;
        }
    }
    if (slot == session->max_connections) return false;
    epoch = break_world_session_stream_epoch(
        session->protocol_version, break_schema_hash(session->schemas),
        session->level_generation);
    if (!break_replication_session_connection_open(session->bridge, connection, epoch))
        return false;
    session->connections[slot].key = connection;
    session->connections[slot].baseline = NULL;
    return true;
}

bool break_world_session_close(BreakWorldSession *session, BreakConnectionKey connection)
{
    size_t slot;
    if (!session) return false;
    slot = world_session_connection_index(session, connection);
    if (slot == session->max_connections ||
        !break_replication_session_connection_close(session->bridge, connection)) {
        return false;
    }
    break_world_snapshot_release(session->connections[slot].baseline);
    memset(&session->connections[slot], 0, sizeof(session->connections[slot]));
    return true;
}

bool break_world_session_baseline(const BreakWorldSession *session,
                                  BreakConnectionKey connection,
                                  u64 *out_snapshot_id, u64 *out_tick)
{
    size_t slot;
    const BreakWorldSnapshot *baseline;
    if (out_snapshot_id) *out_snapshot_id = 0u;
    if (out_tick) *out_tick = 0u;
    if (!session) return false;
    slot = world_session_connection_index(session, connection);
    if (slot == session->max_connections) return false;
    baseline = session->connections[slot].baseline;
    if (out_snapshot_id) *out_snapshot_id = break_world_snapshot_id(baseline);
    if (out_tick) *out_tick = break_world_snapshot_tick(baseline);
    return true;
}

static void world_session_reject(BreakWorldSession *session, bool need_full)
{
    session->rejected_packets++;
    if (need_full) session->need_full_packets++;
}

static void world_session_apply_completion(BreakWorldSession *session,
                                           BreakWorldSessionConnection *connection,
                                           World *world,
                                           BreakReplicationSessionCompletion *completion)
{
    BreakWorldDeltaWire message;
    BreakWorldDeltaWireResult rebuild_result;
    BreakWorldSnapshot *base = NULL;
    BreakWorldSnapshot *target = NULL;
    BreakWorldDelta *delta = NULL;
    BreakDeltaApplyResult apply_result;
    bool base_owned = false;

    session->drained_packets++;
    if (break_world_delta_wire_decode(completion->payload, completion->payload_size,
                                      &message) != BREAK_WORLD_DELTA_WIRE_OK) {
        world_session_reject(session, false);
        return;
    }
    if (message.kind == BREAK_WORLD_DELTA_WIRE_DELTA &&
        (!connection->baseline ||
         message.base_snapshot_id != break_world_snapshot_id(connection->baseline) ||
         message.base_tick != break_world_snapshot_tick(connection->baseline))) {
        world_session_reject(session, true);
        break_world_delta_wire_clear(&message);
        return;
    }
    rebuild_result = break_world_delta_wire_rebuild(
        &message,
        message.kind == BREAK_WORLD_DELTA_WIRE_DELTA ? world : NULL,
        message.kind == BREAK_WORLD_DELTA_WIRE_DELTA ? connection->baseline : NULL,
        session->schemas, session->level_generation, &target);
    if (rebuild_result != BREAK_WORLD_DELTA_WIRE_OK) {
        world_session_reject(session, true);
        goto done;
    }
    if (message.kind == BREAK_WORLD_DELTA_WIRE_FULL) {
        base = break_world_snapshot_build(world, session->schemas, 0u);
        base_owned = true;
    } else {
        base = connection->baseline;
    }
    if (!base) {
        world_session_reject(session, true);
        goto done;
    }
    delta = break_world_delta_diff(base, target);
    if (!delta) {
        world_session_reject(session, true);
        goto done;
    }
    apply_result = break_world_delta_apply(world, delta);
    if (apply_result != BREAK_DELTA_OK && apply_result != BREAK_DELTA_ALREADY_APPLIED) {
        world_session_reject(session, true);
        goto done;
    }
    break_world_snapshot_release(connection->baseline);
    connection->baseline = target;
    target = NULL;
    session->applied_packets++;

done:
    break_world_delta_release(delta);
    if (base_owned) break_world_snapshot_release(base);
    break_world_snapshot_release(target);
    break_world_delta_wire_clear(&message);
}

size_t break_world_session_drain(BreakWorldSession *session,
                                 BreakConnectionKey connection, World *world,
                                 size_t max_packets)
{
    size_t slot;
    size_t drained = 0u;
    if (!session || !world || max_packets == 0u) return 0u;
    slot = world_session_connection_index(session, connection);
    if (slot == session->max_connections) return 0u;
    while (drained < max_packets) {
        BreakReplicationSessionCompletion completion;
        if (break_replication_session_poll_completed_for_connection(
                session->bridge, connection, &completion, 1u) != 1u) {
            break;
        }
        world_session_apply_completion(session, &session->connections[slot], world,
                                       &completion);
        break_replication_session_completion_release(&completion);
        drained++;
    }
    return drained;
}

void break_world_session_stats(const BreakWorldSession *session,
                               BreakWorldSessionStats *out_stats)
{
    if (!out_stats) return;
    memset(out_stats, 0, sizeof(*out_stats));
    if (!session) return;
    out_stats->applied_packets = session->applied_packets;
    out_stats->need_full_packets = session->need_full_packets;
    out_stats->rejected_packets = session->rejected_packets;
    out_stats->drained_packets = session->drained_packets;
    break_replication_session_bridge_stats(session->bridge, &out_stats->bridge);
}
