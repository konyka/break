#include <ecs/world_session.h>

#include <network/break_net_message_registry.h>

#include <stdlib.h>
#include <string.h>

#define WORLD_STREAM_HASH_OFFSET UINT64_C(1469598103934665603)
#define WORLD_STREAM_HASH_PRIME UINT64_C(1099511628211)
#define WORLD_SESSION_DEFAULT_HISTORY_ENTRIES 8u
#define WORLD_SESSION_MAX_HISTORY_ENTRIES 1024u
#define WORLD_SESSION_DEFAULT_HISTORY_BYTES (1024u * 1024u)
#define WORLD_SESSION_MAX_HISTORY_BYTES (64u * 1024u * 1024u)
#define WORLD_SESSION_DEFAULT_PACKET_BYTES BREAK_NET_MAX_PAYLOAD_SIZE
#define WORLD_SESSION_DEFAULT_NEED_FULL_INTERVAL 30u

typedef struct {
    u64 delta_id;
    BreakWorldSnapshot *target;
    size_t packet_bytes;
} BreakWorldSessionHistoryEntry;

typedef struct {
    bool active;
    bool full;
    u64 delta_id;
    BreakWorldSnapshot *target;
    BreakReplicationFragment *fragments;
    size_t fragment_count;
    size_t next_fragment;
    u8 *payload;
    size_t packet_bytes;
} BreakWorldSessionAttempt;

typedef struct {
    BreakConnectionKey key;
    BreakWorldSnapshot *baseline;
    BreakWorldSnapshot *confirmed;
    BreakWorldSessionHistoryEntry *history;
    size_t history_count;
    size_t history_bytes;
    BreakWorldSessionAttempt attempt;
    u64 next_delta_id;
    bool force_full;
    bool need_full_pending;
    BreakWorldSessionControl need_full_control;
    bool need_full_tick_valid;
    u64 last_need_full_tick;
    bool ack_pending;
    BreakWorldSessionControl ack_control;
} BreakWorldSessionConnection;

struct BreakWorldSession {
    const BreakComponentSchemaRegistry *schemas;
    u64 protocol_version;
    u64 initial_level_generation;
    u64 level_generation;
    BreakNetReactor *reactor;
    BreakReplicationSessionBridge *bridge;
    BreakWorldSessionConnection *connections;
    size_t max_connections;
    size_t history_entry_limit;
    size_t history_byte_limit;
    size_t packet_byte_limit;
    size_t fragment_byte_limit;
    size_t fragment_count_limit;
    u64 need_full_tick_interval;
    size_t applied_packets;
    size_t need_full_packets;
    size_t rejected_packets;
    size_t drained_packets;
    size_t need_full_suppressed;
    size_t published_full_packets;
    size_t published_delta_packets;
    size_t acknowledged_packets;
};

static void put16(u8 *out, u16 value)
{
    out[0] = (u8)value;
    out[1] = (u8)(value >> 8u);
}

static u16 get16(const u8 *bytes)
{
    return (u16)bytes[0] | ((u16)bytes[1] << 8u);
}

static void put64(u8 *out, u64 value)
{
    for (u32 i = 0u; i < 8u; ++i) out[i] = (u8)(value >> (i * 8u));
}

static u64 get64(const u8 *bytes)
{
    u64 value = 0u;
    for (u32 i = 0u; i < 8u; ++i) value |= (u64)bytes[i] << (i * 8u);
    return value;
}

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

static void world_session_clear_attempt(BreakWorldSessionAttempt *attempt)
{
    break_replication_fragments_free(attempt->fragments, attempt->fragment_count);
    free(attempt->payload);
    break_world_snapshot_release(attempt->target);
    memset(attempt, 0, sizeof(*attempt));
}

static void world_session_clear_history(BreakWorldSessionConnection *connection)
{
    for (size_t i = 0u; i < connection->history_count; ++i)
        break_world_snapshot_release(connection->history[i].target);
    if (connection->history && connection->history_count != 0u) {
        memset(connection->history, 0,
               connection->history_count * sizeof(connection->history[0]));
    }
    connection->history_count = 0u;
    connection->history_bytes = 0u;
}

static void world_session_release_connection(BreakWorldSessionConnection *connection)
{
    break_world_snapshot_release(connection->baseline);
    break_world_snapshot_release(connection->confirmed);
    world_session_clear_attempt(&connection->attempt);
    world_session_clear_history(connection);
    free(connection->history);
    memset(connection, 0, sizeof(*connection));
}

BreakWorldSession *break_world_session_create(const BreakWorldSessionConfig *config)
{
    BreakWorldSession *session;
    BreakReplicationSessionBridgeConfig bridge_config;
    size_t history_entries;
    size_t history_bytes;
    size_t packet_bytes;
    if (!config || !config->schemas || config->protocol_version == 0u) return NULL;
    history_entries = config->history_entry_limit != 0u
                          ? config->history_entry_limit
                          : WORLD_SESSION_DEFAULT_HISTORY_ENTRIES;
    history_bytes = config->history_byte_limit != 0u
                        ? config->history_byte_limit
                        : WORLD_SESSION_DEFAULT_HISTORY_BYTES;
    packet_bytes = config->packet_byte_limit != 0u
                       ? config->packet_byte_limit
                       : WORLD_SESSION_DEFAULT_PACKET_BYTES;
    if (history_entries > WORLD_SESSION_MAX_HISTORY_ENTRIES ||
        history_bytes > WORLD_SESSION_MAX_HISTORY_BYTES ||
        packet_bytes > BREAK_WORLD_DELTA_WIRE_MAX_BYTES) {
        return NULL;
    }
    session = (BreakWorldSession *)calloc(1u, sizeof(*session));
    if (!session) return NULL;
    session->schemas = config->schemas;
    session->protocol_version = config->protocol_version;
    session->initial_level_generation = config->level_generation;
    session->level_generation = config->level_generation;
    session->reactor = config->bridge.reactor;
    session->max_connections = config->bridge.max_connections;
    session->history_entry_limit = history_entries;
    session->history_byte_limit = history_bytes;
    session->packet_byte_limit = packet_bytes;
    session->fragment_byte_limit = config->bridge.max_fragment_bytes;
    session->fragment_count_limit = config->bridge.max_fragment_count;
    session->need_full_tick_interval = config->need_full_tick_interval != 0u
                                           ? config->need_full_tick_interval
                                           : WORLD_SESSION_DEFAULT_NEED_FULL_INTERVAL;
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
        world_session_release_connection(&session->connections[i]);
    free(session->connections);
    break_replication_session_bridge_destroy(session->bridge);
    free(session);
}

BreakReplicationSessionBridge *break_world_session_bridge(BreakWorldSession *session)
{
    return session ? session->bridge : NULL;
}

bool break_world_session_rebaseline(BreakWorldSession *session, u64 level_generation)
{
    u64 epoch;
    if (!session || level_generation == 0u || level_generation <= session->level_generation) {
        return false;
    }
    epoch = break_world_session_stream_epoch(
        session->protocol_version, break_schema_hash(session->schemas), level_generation);
    break_replication_session_rebaseline(session->bridge, epoch);
    for (size_t i = 0u; i < session->max_connections; ++i) {
        BreakWorldSessionConnection *state = &session->connections[i];
        if (state->key == 0u) continue;
        world_session_clear_attempt(&state->attempt);
        world_session_clear_history(state);
        break_world_snapshot_release(state->baseline);
        break_world_snapshot_release(state->confirmed);
        state->baseline = NULL;
        state->confirmed = NULL;
        state->next_delta_id = 1u;
        state->force_full = true;
        state->need_full_pending = false;
        state->ack_pending = false;
        state->need_full_tick_valid = false;
        state->last_need_full_tick = 0u;
        memset(&state->need_full_control, 0, sizeof(state->need_full_control));
        memset(&state->ack_control, 0, sizeof(state->ack_control));
    }
    session->level_generation = level_generation;
    return true;
}

u64 break_world_session_level_generation(const BreakWorldSession *session)
{
    return session ? session->level_generation : 0u;
}

bool break_world_session_open(BreakWorldSession *session, BreakConnectionKey connection)
{
    size_t slot = session ? session->max_connections : 0u;
    BreakWorldSessionHistoryEntry *history;
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
    history = (BreakWorldSessionHistoryEntry *)calloc(
        session->history_entry_limit, sizeof(*history));
    if (!history) return false;
    epoch = break_world_session_stream_epoch(
        session->protocol_version, break_schema_hash(session->schemas),
        session->level_generation);
    if (!break_replication_session_connection_open(session->bridge, connection, epoch)) {
        free(history);
        return false;
    }
    session->connections[slot].key = connection;
    session->connections[slot].history = history;
    session->connections[slot].next_delta_id = 1u;
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
    world_session_release_connection(&session->connections[slot]);
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

static void world_session_queue_need_full(BreakWorldSession *session,
                                          BreakWorldSessionConnection *connection,
                                          u64 target_tick)
{
    if (connection->need_full_pending ||
        (connection->need_full_tick_valid &&
         (target_tick <= connection->last_need_full_tick ||
          target_tick - connection->last_need_full_tick <
              session->need_full_tick_interval))) {
        session->need_full_suppressed++;
        return;
    }
    memset(&connection->need_full_control, 0, sizeof(connection->need_full_control));
    connection->need_full_control.kind = BREAK_WORLD_SESSION_CONTROL_NEED_FULL;
    connection->need_full_control.target_snapshot_id =
        break_world_snapshot_id(connection->baseline);
    connection->need_full_control.target_tick = break_world_snapshot_tick(connection->baseline);
    connection->need_full_pending = true;
    connection->need_full_tick_valid = true;
    connection->last_need_full_tick = target_tick;
}

static void world_session_reject(BreakWorldSession *session,
                                 BreakWorldSessionConnection *connection,
                                 bool need_full, u64 target_tick)
{
    session->rejected_packets++;
    if (need_full) {
        session->need_full_packets++;
        world_session_queue_need_full(session, connection, target_tick);
    }
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

    session->drained_packets++;
    if (break_world_delta_wire_decode(completion->payload, completion->payload_size,
                                      &message) != BREAK_WORLD_DELTA_WIRE_OK) {
        world_session_reject(session, connection, false, 0u);
        return;
    }
    if (message.kind == BREAK_WORLD_DELTA_WIRE_DELTA &&
        (!connection->baseline ||
         message.base_snapshot_id != break_world_snapshot_id(connection->baseline) ||
         message.base_tick != break_world_snapshot_tick(connection->baseline))) {
        world_session_reject(session, connection, true, message.target_tick);
        break_world_delta_wire_clear(&message);
        return;
    }
    if (message.kind == BREAK_WORLD_DELTA_WIRE_FULL) {
        rebuild_result = break_world_delta_wire_apply_full(
            &message, session->schemas, session->level_generation, world, &target);
        if (rebuild_result != BREAK_WORLD_DELTA_WIRE_OK) {
            world_session_reject(session, connection, true, message.target_tick);
            goto done;
        }
    } else {
        rebuild_result = break_world_delta_wire_rebuild(
            &message, world, connection->baseline,
            session->schemas, session->level_generation, &target);
        if (rebuild_result != BREAK_WORLD_DELTA_WIRE_OK) {
            world_session_reject(session, connection, true, message.target_tick);
            goto done;
        }
        base = connection->baseline;
        if (!base) {
            world_session_reject(session, connection, true, message.target_tick);
            goto done;
        }
        delta = break_world_delta_diff(base, target);
        if (!delta) {
            world_session_reject(session, connection, true, message.target_tick);
            goto done;
        }
        apply_result = break_world_delta_apply(world, delta);
        if (apply_result != BREAK_DELTA_OK &&
            apply_result != BREAK_DELTA_ALREADY_APPLIED) {
            world_session_reject(session, connection, true, message.target_tick);
            goto done;
        }
    }
    break_world_snapshot_release(connection->baseline);
    connection->baseline = target;
    target = NULL;
    connection->ack_control.kind = BREAK_WORLD_SESSION_CONTROL_ACK;
    connection->ack_control.delta_id = completion->delta_id;
    connection->ack_control.target_snapshot_id =
        break_world_snapshot_id(connection->baseline);
    connection->ack_control.target_tick = break_world_snapshot_tick(connection->baseline);
    connection->ack_pending = true;
    session->applied_packets++;

done:
    break_world_delta_release(delta);
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

bool break_world_session_poll_control(BreakWorldSession *session,
                                      BreakConnectionKey connection,
                                      BreakWorldSessionControl *out_control)
{
    size_t slot;
    if (!out_control) return false;
    memset(out_control, 0, sizeof(*out_control));
    if (!session) return false;
    slot = world_session_connection_index(session, connection);
    if (slot == session->max_connections) return false;
    if (session->connections[slot].need_full_pending) {
        *out_control = session->connections[slot].need_full_control;
        out_control->level_generation = session->level_generation;
        session->connections[slot].need_full_pending = false;
        return true;
    }
    if (session->connections[slot].ack_pending) {
        *out_control = session->connections[slot].ack_control;
        out_control->level_generation = session->level_generation;
        session->connections[slot].ack_pending = false;
        return true;
    }
    return false;
}

static bool world_session_control_valid(const BreakWorldSessionControl *control)
{
    if (!control) return false;
    if (control->kind == BREAK_WORLD_SESSION_CONTROL_NEED_FULL)
        return control->delta_id == 0u;
    if (control->kind == BREAK_WORLD_SESSION_CONTROL_ACK)
        return control->delta_id != 0u && control->target_snapshot_id != 0u;
    return false;
}

BreakNetSendResult break_world_session_send_control(
    BreakWorldSession *session, BreakConnectionKey connection,
    const BreakWorldSessionControl *control)
{
    return break_world_session_send_control_correlated(session, connection, control, 0u);
}

BreakNetSendResult break_world_session_send_control_correlated(
    BreakWorldSession *session, BreakConnectionKey connection,
    const BreakWorldSessionControl *control, u64 correlation_id)
{
    u8 payload[BREAK_WORLD_SESSION_CONTROL_WIRE_SIZE_V2];
    u16 version;
    size_t payload_size;
    if (!session || !session->reactor) return BREAK_NET_SEND_CLOSED;
    if (world_session_connection_index(session, connection) == session->max_connections)
        return BREAK_NET_SEND_CLOSED;
    if (!world_session_control_valid(control)) return BREAK_NET_SEND_INVALID;
    if (session->level_generation == session->initial_level_generation) {
        if (control->level_generation != 0u &&
            control->level_generation != session->initial_level_generation) {
            return BREAK_NET_SEND_INVALID;
        }
        version = 1u;
        payload_size = BREAK_WORLD_SESSION_CONTROL_WIRE_SIZE;
    } else {
        if (control->level_generation == 0u ||
            control->level_generation != session->level_generation) {
            return BREAK_NET_SEND_INVALID;
        }
        version = 2u;
        payload_size = BREAK_WORLD_SESSION_CONTROL_WIRE_SIZE_V2;
    }
    memset(payload, 0, sizeof(payload));
    memcpy(payload, "BRWC", 4u);
    put16(payload + 4u, version);
    put16(payload + 6u, (u16)control->kind);
    put64(payload + 8u, control->delta_id);
    put64(payload + 16u, control->target_snapshot_id);
    put64(payload + 24u, control->target_tick);
    if (version == 2u) put64(payload + 32u, control->level_generation);
    return break_net_reactor_send_correlated(session->reactor, connection,
                                             BREAK_NET_MESSAGE_ID_WORLD_CONTROL, version,
                                             correlation_id, payload, payload_size);
}

bool break_world_session_handle_control(BreakConnectionKey connection,
                                        const BreakNetOwnedMessage *message,
                                        void *user_data)
{
    BreakWorldSession *session = (BreakWorldSession *)user_data;
    BreakWorldSessionConnection *state;
    BreakWorldSessionControl control;
    const u8 *payload;
    size_t slot;
    size_t ack_index;
    size_t released_bytes = 0u;
    if (!session || !message || !message->data ||
        message->message_id != BREAK_NET_MESSAGE_ID_WORLD_CONTROL) {
        return false;
    }
    slot = world_session_connection_index(session, connection);
    if (slot == session->max_connections) return false;
    payload = (const u8 *)message->data;
    if (message->size < 4u || memcmp(payload, "BRWC", 4u) != 0) return false;
    memset(&control, 0, sizeof(control));
    if (message->protocol_version == 1u) {
        if (session->level_generation != session->initial_level_generation ||
            message->size != BREAK_WORLD_SESSION_CONTROL_WIRE_SIZE ||
            get16(payload + 4u) != 1u) {
            return false;
        }
        control.level_generation = session->initial_level_generation;
    } else if (message->protocol_version == 2u) {
        if (message->size != BREAK_WORLD_SESSION_CONTROL_WIRE_SIZE_V2 ||
            get16(payload + 4u) != 2u) {
            return false;
        }
        control.level_generation = get64(payload + 32u);
        if (control.level_generation != session->level_generation) return false;
    } else {
        return false;
    }
    control.kind = (BreakWorldSessionControlKind)get16(payload + 6u);
    control.delta_id = get64(payload + 8u);
    control.target_snapshot_id = get64(payload + 16u);
    control.target_tick = get64(payload + 24u);
    if (!world_session_control_valid(&control)) return false;
    state = &session->connections[slot];
    if (control.kind == BREAK_WORLD_SESSION_CONTROL_NEED_FULL) {
        state->force_full = true;
        return true;
    }
    for (ack_index = 0u; ack_index < state->history_count; ++ack_index) {
        const BreakWorldSessionHistoryEntry *entry = &state->history[ack_index];
        if (entry->delta_id == control.delta_id &&
            break_world_snapshot_id(entry->target) == control.target_snapshot_id &&
            break_world_snapshot_tick(entry->target) == control.target_tick) {
            break;
        }
    }
    if (ack_index == state->history_count) return false;
    break_world_snapshot_retain(state->history[ack_index].target);
    break_world_snapshot_release(state->confirmed);
    state->confirmed = state->history[ack_index].target;
    for (size_t i = 0u; i <= ack_index; ++i) {
        released_bytes += state->history[i].packet_bytes;
        break_world_snapshot_release(state->history[i].target);
    }
    memmove(state->history, state->history + ack_index + 1u,
            (state->history_count - ack_index - 1u) * sizeof(state->history[0]));
    state->history_count -= ack_index + 1u;
    state->history_bytes -= released_bytes;
    memset(state->history + state->history_count, 0,
           (ack_index + 1u) * sizeof(state->history[0]));
    session->acknowledged_packets++;
    return true;
}

static bool world_session_encode_message(BreakWorldDeltaWire *message,
                                         u8 **out_wire, size_t *out_size)
{
    size_t size = 0u;
    u8 *wire;
    if (break_world_delta_wire_encoded_size(message, &size) != BREAK_WORLD_DELTA_WIRE_OK)
        return false;
    wire = (u8 *)malloc(size);
    if (!wire) return false;
    if (break_world_delta_wire_encode(message, wire, size, &size) !=
        BREAK_WORLD_DELTA_WIRE_OK) {
        free(wire);
        return false;
    }
    *out_wire = wire;
    *out_size = size;
    return true;
}

static bool world_session_encode_full(const BreakWorldSession *session,
                                      const BreakWorldSnapshot *target,
                                      u8 **out_wire, size_t *out_size)
{
    BreakWorldDeltaWire message;
    size_t entity_count = break_world_snapshot_entity_count(target);
    size_t count = 0u;
    size_t slot = 0u;
    bool ok;
    memset(&message, 0, sizeof(message));
    for (size_t i = 0u; i < entity_count; ++i) {
        Entity entity = break_world_snapshot_entity_at(target, i);
        count++;
        for (u32 component = 0u; component < ECS_MAX_COMPONENTS; ++component) {
            const void *bytes = NULL;
            size_t size = 0u;
            if (break_world_snapshot_component_bytes(target, entity, component,
                                                      &bytes, &size)) {
                count++;
            }
        }
    }
    if (count > UINT32_MAX) return false;
    message.kind = BREAK_WORLD_DELTA_WIRE_FULL;
    message.schema_hash = break_world_snapshot_schema_hash(target);
    message.level_generation = session->level_generation;
    message.target_snapshot_id = break_world_snapshot_id(target);
    message.target_tick = break_world_snapshot_tick(target);
    message.record_count = (u32)count;
    if (count != 0u) {
        message.records = (BreakWorldDeltaRecord *)calloc(count, sizeof(*message.records));
        if (!message.records) return false;
    }
    for (size_t i = 0u; i < entity_count; ++i) {
        Entity entity = break_world_snapshot_entity_at(target, i);
        message.records[slot].kind = BREAK_DELTA_ENTITY_CREATE;
        message.records[slot].entity = entity;
        slot++;
        for (u32 component = 0u; component < ECS_MAX_COMPONENTS; ++component) {
            const void *bytes = NULL;
            size_t size = 0u;
            if (break_world_snapshot_component_bytes(target, entity, component,
                                                      &bytes, &size)) {
                message.records[slot].kind = BREAK_DELTA_COMPONENT_ADD;
                message.records[slot].entity = entity;
                message.records[slot].component = component;
                message.records[slot].bytes = bytes;
                message.records[slot].size = size;
                slot++;
            }
        }
    }
    ok = world_session_encode_message(&message, out_wire, out_size);
    free(message.records);
    return ok;
}

static bool world_session_encode_delta(const BreakWorldSession *session,
                                       const BreakWorldSnapshot *base,
                                       const BreakWorldSnapshot *target,
                                       u8 **out_wire, size_t *out_size)
{
    BreakWorldDelta *delta = break_world_delta_diff(base, target);
    BreakWorldDeltaWire message;
    size_t count;
    bool ok;
    if (!delta) return false;
    count = break_world_delta_record_count(delta);
    if (count > UINT32_MAX) {
        break_world_delta_release(delta);
        return false;
    }
    memset(&message, 0, sizeof(message));
    message.kind = BREAK_WORLD_DELTA_WIRE_DELTA;
    message.schema_hash = break_world_delta_target_schema_hash(delta);
    message.level_generation = session->level_generation;
    message.base_snapshot_id = break_world_delta_base_id(delta);
    message.target_snapshot_id = break_world_delta_target_id(delta);
    message.base_tick = break_world_delta_base_tick(delta);
    message.target_tick = break_world_delta_target_tick(delta);
    message.record_count = (u32)count;
    if (count != 0u) {
        message.records = (BreakWorldDeltaRecord *)calloc(count, sizeof(*message.records));
        if (!message.records) {
            break_world_delta_release(delta);
            return false;
        }
        for (size_t i = 0u; i < count; ++i) {
            if (!break_world_delta_record_at(delta, i, &message.records[i])) {
                free(message.records);
                break_world_delta_release(delta);
                return false;
            }
        }
    }
    ok = world_session_encode_message(&message, out_wire, out_size);
    free(message.records);
    break_world_delta_release(delta);
    return ok;
}

static bool world_session_history_would_exceed(const BreakWorldSession *session,
                                               const BreakWorldSessionConnection *connection,
                                               size_t packet_bytes)
{
    if (connection->history_count >= session->history_entry_limit) return true;
    if (connection->history_bytes > session->history_byte_limit) return true;
    return packet_bytes > session->history_byte_limit - connection->history_bytes;
}

static bool world_session_build_attempt_from_snapshot(
    BreakWorldSession *session, BreakWorldSessionConnection *connection,
    BreakWorldSnapshot *target, u64 level_generation, bool strict_tick)
{
    BreakWorldSessionAttempt *attempt = &connection->attempt;
    const BreakWorldSnapshot *base = NULL;
    u8 *wire = NULL;
    size_t wire_size = 0u;
    bool full = connection->force_full || !connection->confirmed;
    BreakReplicationFragmentResult fragment_result;
    if (!target || break_world_snapshot_tick(target) == 0u ||
        break_world_snapshot_schema_hash(target) != break_schema_hash(session->schemas) ||
        level_generation != session->level_generation) {
        goto invalid;
    }
    base = connection->history_count != 0u
               ? connection->history[connection->history_count - 1u].target
               : connection->confirmed;
    if (base && break_world_snapshot_tick(target) <= break_world_snapshot_tick(base) &&
        (strict_tick || !full)) {
        goto invalid;
    }
    if (!full) {
        if (!base) goto invalid;
        if (!world_session_encode_delta(session, base, target, &wire, &wire_size) ||
            wire_size > session->packet_byte_limit ||
            world_session_history_would_exceed(session, connection, wire_size)) {
            free(wire);
            wire = NULL;
            wire_size = 0u;
            full = true;
        }
    }
    if (full && !world_session_encode_full(session, target, &wire, &wire_size)) goto invalid;
    if (wire_size == 0u || wire_size > session->packet_byte_limit ||
        wire_size > session->history_byte_limit || connection->next_delta_id == 0u) {
        goto invalid;
    }
    memset(attempt, 0, sizeof(*attempt));
    attempt->active = true;
    attempt->full = full;
    attempt->delta_id = connection->next_delta_id;
    attempt->target = target;
    attempt->packet_bytes = wire_size;
    attempt->payload = wire;
    target = NULL;
    wire = NULL;
    fragment_result = break_replication_fragment_payload(
        attempt->delta_id,
        break_world_session_stream_epoch(session->protocol_version,
                                         break_schema_hash(session->schemas),
                                         session->level_generation),
        attempt->payload, attempt->packet_bytes, session->fragment_byte_limit,
        &attempt->fragments, &attempt->fragment_count);
    if (fragment_result != BREAK_REPLICATION_FRAGMENT_OK ||
        attempt->fragment_count == 0u ||
        attempt->fragment_count > session->fragment_count_limit) {
        world_session_clear_attempt(attempt);
        return false;
    }
    connection->next_delta_id++;
    return true;

invalid:
    free(wire);
    break_world_snapshot_release(target);
    return false;
}

static BreakNetSendResult world_session_resume_attempt(
    BreakWorldSession *session, BreakWorldSessionConnection *connection)
{
    BreakWorldSessionAttempt *attempt = &connection->attempt;
    while (attempt->next_fragment < attempt->fragment_count) {
        BreakNetSendResult result = break_replication_session_send_fragment(
            session->bridge, connection->key, &attempt->fragments[attempt->next_fragment]);
        if (result != BREAK_NET_SEND_OK) {
            if (result != BREAK_NET_SEND_OVERLOAD) world_session_clear_attempt(attempt);
            return result;
        }
        attempt->next_fragment++;
    }
    if (attempt->full) {
        world_session_clear_history(connection);
        break_world_snapshot_release(connection->confirmed);
        connection->confirmed = NULL;
        connection->force_full = false;
    }
    connection->history[connection->history_count].delta_id = attempt->delta_id;
    connection->history[connection->history_count].target = attempt->target;
    connection->history[connection->history_count].packet_bytes = attempt->packet_bytes;
    attempt->target = NULL;
    connection->history_count++;
    connection->history_bytes += attempt->packet_bytes;
    if (attempt->full) {
        session->published_full_packets++;
    } else {
        session->published_delta_packets++;
    }
    world_session_clear_attempt(attempt);
    return BREAK_NET_SEND_OK;
}

BreakNetSendResult break_world_session_publish(BreakWorldSession *session,
                                               BreakConnectionKey connection,
                                               World *world, u64 tick)
{
    size_t slot;
    BreakWorldSessionConnection *state;
    BreakWorldSnapshot *owned;
    if (!session || !session->reactor) return BREAK_NET_SEND_CLOSED;
    slot = world_session_connection_index(session, connection);
    if (slot == session->max_connections) return BREAK_NET_SEND_CLOSED;
    state = &session->connections[slot];
    if (state->attempt.active) return world_session_resume_attempt(session, state);
    if (!world) return BREAK_NET_SEND_INVALID;
    owned = break_world_snapshot_build(world, session->schemas, tick);
    if (!world_session_build_attempt_from_snapshot(session, state, owned,
                                                   session->level_generation, false)) {
        return BREAK_NET_SEND_INVALID;
    }
    return world_session_resume_attempt(session, state);
}

BreakNetSendResult break_world_session_publish_filtered(
    BreakWorldSession *session, BreakConnectionKey connection, World *world,
    u64 tick, BreakWorldSnapshotEntityFilter keep, void *keep_user)
{
    size_t slot;
    BreakWorldSessionConnection *state;
    BreakWorldSnapshot *full;
    BreakWorldSnapshot *target;
    if (!keep) return break_world_session_publish(session, connection, world, tick);
    if (!session || !session->reactor) return BREAK_NET_SEND_CLOSED;
    slot = world_session_connection_index(session, connection);
    if (slot == session->max_connections) return BREAK_NET_SEND_CLOSED;
    state = &session->connections[slot];
    if (state->attempt.active) return world_session_resume_attempt(session, state);
    if (!world) return BREAK_NET_SEND_INVALID;
    full = break_world_snapshot_build(world, session->schemas, tick);
    if (!full) return BREAK_NET_SEND_INVALID;
    target = break_world_snapshot_filter(full, keep, keep_user);
    break_world_snapshot_release(full);
    if (!target) return BREAK_NET_SEND_INVALID;
    if (!world_session_build_attempt_from_snapshot(session, state, target,
                                                   session->level_generation, false)) {
        return BREAK_NET_SEND_INVALID;
    }
    return world_session_resume_attempt(session, state);
}

BreakNetSendResult break_world_session_publish_snapshot(
    BreakWorldSession *session, BreakConnectionKey connection,
    BreakWorldSnapshot *target, u64 level_generation)
{
    size_t slot;
    BreakWorldSessionConnection *state;
    if (!session || !session->reactor) return BREAK_NET_SEND_CLOSED;
    slot = world_session_connection_index(session, connection);
    if (slot == session->max_connections) return BREAK_NET_SEND_CLOSED;
    state = &session->connections[slot];
    if (state->attempt.active) return world_session_resume_attempt(session, state);
    break_world_snapshot_retain(target);
    if (!world_session_build_attempt_from_snapshot(session, state, target, level_generation,
                                                   true)) {
        return BREAK_NET_SEND_INVALID;
    }
    return world_session_resume_attempt(session, state);
}

BreakNetSendResult break_world_session_publish_snapshot_filtered(
    BreakWorldSession *session, BreakConnectionKey connection,
    BreakWorldSnapshot *target, u64 level_generation,
    BreakWorldSnapshotEntityFilter keep, void *keep_user)
{
    size_t slot;
    BreakWorldSessionConnection *state;
    BreakWorldSnapshot *view;
    if (!keep) {
        return break_world_session_publish_snapshot(session, connection, target,
                                                    level_generation);
    }
    if (!session || !session->reactor) return BREAK_NET_SEND_CLOSED;
    slot = world_session_connection_index(session, connection);
    if (slot == session->max_connections) return BREAK_NET_SEND_CLOSED;
    state = &session->connections[slot];
    if (state->attempt.active) return world_session_resume_attempt(session, state);
    if (!target) return BREAK_NET_SEND_INVALID;
    view = break_world_snapshot_filter(target, keep, keep_user);
    if (!view) return BREAK_NET_SEND_INVALID;
    if (!world_session_build_attempt_from_snapshot(session, state, view, level_generation,
                                                   true)) {
        return BREAK_NET_SEND_INVALID;
    }
    return world_session_resume_attempt(session, state);
}

bool break_world_session_sender_state(const BreakWorldSession *session,
                                      BreakConnectionKey connection,
                                      BreakWorldSessionSenderState *out_state)
{
    size_t slot;
    const BreakWorldSessionConnection *state;
    if (!out_state) return false;
    /* Zeroes the tail padding too; callers and tests compare states with memcmp. */
    memset(out_state, 0, sizeof(*out_state));
    if (!session) return false;
    slot = world_session_connection_index(session, connection);
    if (slot == session->max_connections) return false;
    state = &session->connections[slot];
    out_state->history_count = state->history_count;
    out_state->history_bytes = state->history_bytes;
    out_state->confirmed_snapshot_id = break_world_snapshot_id(state->confirmed);
    out_state->confirmed_tick = break_world_snapshot_tick(state->confirmed);
    out_state->next_delta_id = state->next_delta_id;
    out_state->attempt_pending = state->attempt.active;
    out_state->attempt_target_snapshot_id = state->attempt.active
        ? break_world_snapshot_id(state->attempt.target) : 0u;
    out_state->attempt_target_tick = state->attempt.active
        ? break_world_snapshot_tick(state->attempt.target) : 0u;
    out_state->force_full = state->force_full;
    return true;
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
    out_stats->need_full_suppressed = session->need_full_suppressed;
    out_stats->published_full_packets = session->published_full_packets;
    out_stats->published_delta_packets = session->published_delta_packets;
    out_stats->acknowledged_packets = session->acknowledged_packets;
    break_replication_session_bridge_stats(session->bridge, &out_stats->bridge);
}
