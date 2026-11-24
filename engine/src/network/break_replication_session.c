#include "network/break_replication_session.h"

#include <stdlib.h>
#include <string.h>

#include "network/break_net_message_registry.h"
#include "network/break_replication_wire.h"

typedef struct BreakReplicationSessionConnection {
    BreakConnectionKey key;
    uint64_t expected_base_id;
    BreakReplicationReassemblyPool *pool;
} BreakReplicationSessionConnection;

struct BreakReplicationSessionBridge {
    BreakReplicationSessionBridgeConfig config;
    BreakReplicationSessionConnection *connections;
    size_t connection_count;
    BreakReplicationSessionCompletion *completions;
    size_t completion_head;
    size_t completion_count;
    size_t completion_bytes;
    uint8_t *scratch;
    uint64_t rejected_fragments;
    uint64_t duplicate_fragments;
    uint64_t completed_packets;
    uint64_t dropped_completions;
    uint64_t expired_streams;
};

static bool bridge_config_valid(const BreakReplicationSessionBridgeConfig *config)
{
    if (!config || !config->clock) return false;
    if (config->max_connections == 0u ||
        config->max_connections > SIZE_MAX / sizeof(BreakReplicationSessionConnection))
        return false;
    if (config->stream_capacity == 0u ||
        config->stream_capacity > BREAK_REPLICATION_REASSEMBLY_POOL_MAX_STREAMS)
        return false;
    if (config->max_pending_bytes_per_connection == 0u ||
        config->max_pending_bytes_per_connection > BREAK_REPLICATION_MAX_REASSEMBLY_SIZE)
        return false;
    if (config->max_connections >
            SIZE_MAX / config->max_pending_bytes_per_connection ||
        config->max_connections * config->max_pending_bytes_per_connection >
            config->max_total_pending_bytes)
        return false;
    if (config->max_fragment_bytes == 0u ||
        config->max_fragment_bytes > BREAK_REPLICATION_WIRE_MAX_FRAGMENT_DATA_SIZE)
        return false;
    if (config->max_fragment_count == 0u ||
        config->max_fragment_count > BREAK_REPLICATION_WIRE_MAX_FRAGMENT_COUNT)
        return false;
    if (config->completion_capacity == 0u ||
        config->completion_capacity > SIZE_MAX / sizeof(BreakReplicationSessionCompletion))
        return false;
    if (config->max_completion_packet_bytes == 0u ||
        config->max_completion_packet_bytes > BREAK_REPLICATION_MAX_REASSEMBLY_SIZE)
        return false;
    return config->max_completion_queue_bytes >= config->max_completion_packet_bytes;
}

BreakReplicationSessionBridge *break_replication_session_bridge_create(
    const BreakReplicationSessionBridgeConfig *config)
{
    BreakReplicationSessionBridge *bridge;
    if (!bridge_config_valid(config)) return NULL;
    bridge = (BreakReplicationSessionBridge *)calloc(1u, sizeof(*bridge));
    if (!bridge) return NULL;
    bridge->config = *config;
    if (bridge->config.message_id == 0u)
        bridge->config.message_id = BREAK_NET_MESSAGE_ID_REPLICATION_FRAGMENT;
    bridge->connections = (BreakReplicationSessionConnection *)calloc(
        config->max_connections, sizeof(*bridge->connections));
    bridge->completions = (BreakReplicationSessionCompletion *)calloc(
        config->completion_capacity, sizeof(*bridge->completions));
    bridge->scratch = (uint8_t *)malloc(BREAK_NET_MAX_PAYLOAD_SIZE);
    if (!bridge->connections || !bridge->completions || !bridge->scratch) {
        free(bridge->connections);
        free(bridge->completions);
        free(bridge->scratch);
        free(bridge);
        return NULL;
    }
    return bridge;
}

static BreakReplicationSessionCompletion *bridge_completion_at(
    BreakReplicationSessionBridge *bridge, size_t offset)
{
    return &bridge->completions[(bridge->completion_head + offset) %
                                bridge->config.completion_capacity];
}

void break_replication_session_bridge_destroy(BreakReplicationSessionBridge *bridge)
{
    size_t i;
    if (!bridge) return;
    for (i = 0u; i < bridge->config.max_connections; ++i)
        break_replication_reassembly_pool_destroy(bridge->connections[i].pool);
    for (i = 0u; i < bridge->completion_count; ++i)
        break_replication_reassembly_free(bridge_completion_at(bridge, i)->payload);
    free(bridge->connections);
    free(bridge->completions);
    free(bridge->scratch);
    free(bridge);
}

static BreakReplicationSessionConnection *bridge_find(
    BreakReplicationSessionBridge *bridge, BreakConnectionKey key)
{
    size_t i;
    if (key == 0u) return NULL;
    for (i = 0u; i < bridge->config.max_connections; ++i) {
        if (bridge->connections[i].pool && bridge->connections[i].key == key)
            return &bridge->connections[i];
    }
    return NULL;
}

bool break_replication_session_connection_open(
    BreakReplicationSessionBridge *bridge, BreakConnectionKey connection,
    uint64_t expected_base_id)
{
    BreakReplicationSessionConnection *slot = NULL;
    size_t i;
    if (!bridge || connection == 0u || bridge_find(bridge, connection)) return false;
    for (i = 0u; i < bridge->config.max_connections; ++i) {
        if (!bridge->connections[i].pool) {
            slot = &bridge->connections[i];
            break;
        }
    }
    if (!slot) return false;
    slot->pool = break_replication_reassembly_pool_create(
        expected_base_id, bridge->config.stream_capacity,
        bridge->config.max_pending_bytes_per_connection);
    if (!slot->pool) return false;
    if (bridge->config.expiry_enabled) {
        break_replication_reassembly_pool_set_expiry_schedule(
            slot->pool, bridge->config.expiry_interval, bridge->config.expiry_max_idle);
    }
    slot->key = connection;
    slot->expected_base_id = expected_base_id;
    bridge->connection_count++;
    return true;
}

bool break_replication_session_connection_close(
    BreakReplicationSessionBridge *bridge, BreakConnectionKey connection)
{
    BreakReplicationSessionConnection *slot;
    size_t kept = 0u;
    size_t i;
    if (!bridge) return false;
    slot = bridge_find(bridge, connection);
    if (!slot) return false;
    for (i = 0u; i < bridge->completion_count; ++i) {
        BreakReplicationSessionCompletion *entry = bridge_completion_at(bridge, i);
        if (entry->connection == connection) {
            bridge->completion_bytes -= entry->payload_size;
            break_replication_reassembly_free(entry->payload);
            memset(entry, 0, sizeof(*entry));
            bridge->dropped_completions++;
            continue;
        }
        if (kept != i) {
            BreakReplicationSessionCompletion *target = bridge_completion_at(bridge, kept);
            *target = *entry;
            memset(entry, 0, sizeof(*entry));
        }
        kept++;
    }
    bridge->completion_count = kept;
    break_replication_reassembly_pool_destroy(slot->pool);
    memset(slot, 0, sizeof(*slot));
    bridge->connection_count--;
    return true;
}

void break_replication_session_rebaseline(
    BreakReplicationSessionBridge *bridge, uint64_t expected_base_id)
{
    size_t i;
    if (!bridge) return;
    for (i = 0u; i < bridge->config.max_connections; ++i) {
        if (!bridge->connections[i].pool) continue;
        break_replication_reassembly_pool_rebaseline(
            bridge->connections[i].pool, expected_base_id);
        bridge->connections[i].expected_base_id = expected_base_id;
    }
    for (i = 0u; i < bridge->completion_count; ++i) {
        BreakReplicationSessionCompletion *entry = bridge_completion_at(bridge, i);
        break_replication_reassembly_free(entry->payload);
        memset(entry, 0, sizeof(*entry));
    }
    bridge->dropped_completions += bridge->completion_count;
    bridge->completion_head = 0u;
    bridge->completion_count = 0u;
    bridge->completion_bytes = 0u;
}

static bool bridge_fragment_within_limits(const BreakReplicationSessionBridge *bridge,
                                          const BreakReplicationFragment *fragment)
{
    return fragment->size <= bridge->config.max_fragment_bytes &&
           (size_t)fragment->fragment_count <= bridge->config.max_fragment_count;
}

BreakNetSendResult break_replication_session_send_fragment(
    BreakReplicationSessionBridge *bridge, BreakConnectionKey connection,
    const BreakReplicationFragment *fragment)
{
    BreakReplicationSessionConnection *slot;
    size_t wire_size = 0u;
    if (!bridge) return BREAK_NET_SEND_CLOSED;
    slot = bridge_find(bridge, connection);
    if (!slot) return BREAK_NET_SEND_CLOSED;
    if (!fragment || !bridge->config.reactor ||
        fragment->base_id != slot->expected_base_id ||
        !bridge_fragment_within_limits(bridge, fragment))
        return BREAK_NET_SEND_INVALID;
    if (break_replication_wire_encode(fragment, bridge->scratch, BREAK_NET_MAX_PAYLOAD_SIZE,
                                      &wire_size) != BREAK_REPLICATION_FRAGMENT_OK)
        return BREAK_NET_SEND_INVALID;
    return break_net_reactor_send(bridge->config.reactor, connection,
                                  bridge->config.message_id,
                                  BREAK_REPLICATION_WIRE_VERSION, bridge->scratch, wire_size);
}

size_t break_replication_session_bridge_tick(BreakReplicationSessionBridge *bridge,
                                             uint64_t now)
{
    size_t expired = 0u;
    size_t i;
    if (!bridge) return 0u;
    for (i = 0u; i < bridge->config.max_connections; ++i) {
        if (bridge->connections[i].pool)
            expired += break_replication_reassembly_pool_tick(bridge->connections[i].pool, now);
    }
    bridge->expired_streams += expired;
    return expired;
}

static void bridge_enqueue_completion(BreakReplicationSessionBridge *bridge,
                                      BreakConnectionKey connection, uint64_t delta_id,
                                      uint8_t *payload, size_t payload_size)
{
    BreakReplicationSessionCompletion *entry;
    if (payload_size > bridge->config.max_completion_packet_bytes ||
        bridge->completion_count == bridge->config.completion_capacity ||
        payload_size > bridge->config.max_completion_queue_bytes - bridge->completion_bytes) {
        break_replication_reassembly_free(payload);
        bridge->dropped_completions++;
        return;
    }
    entry = bridge_completion_at(bridge, bridge->completion_count);
    entry->connection = connection;
    entry->delta_id = delta_id;
    entry->payload = payload;
    entry->payload_size = payload_size;
    bridge->completion_count++;
    bridge->completion_bytes += payload_size;
}

bool break_replication_session_handle_message(
    BreakConnectionKey connection, const BreakNetOwnedMessage *message,
    void *user_data)
{
    BreakReplicationSessionBridge *bridge = (BreakReplicationSessionBridge *)user_data;
    BreakReplicationSessionConnection *slot;
    BreakReplicationFragment fragment;
    BreakReplicationReassemblyResult result;
    uint64_t completed_delta_id = 0u;
    uint8_t *payload = NULL;
    size_t payload_size = 0u;
    if (!bridge) return false;
    slot = bridge_find(bridge, connection);
    if (!slot || !message ||
        message->message_id != bridge->config.message_id ||
        message->protocol_version != BREAK_REPLICATION_WIRE_VERSION ||
        break_replication_wire_decode(message->data, message->size, &fragment) !=
            BREAK_REPLICATION_FRAGMENT_OK ||
        !bridge_fragment_within_limits(bridge, &fragment)) {
        bridge->rejected_fragments++;
        return false;
    }
    {
        const uint64_t now = bridge->config.clock(bridge->config.clock_user);
        bridge->expired_streams +=
            break_replication_reassembly_pool_tick(slot->pool, now);
        result = break_replication_reassembly_pool_push_at(
            slot->pool, &fragment, now,
            &completed_delta_id, &payload, &payload_size);
    }
    switch (result) {
    case BREAK_REPLICATION_REASSEMBLY_INCOMPLETE:
        return true;
    case BREAK_REPLICATION_REASSEMBLY_DUPLICATE:
        bridge->duplicate_fragments++;
        return true;
    case BREAK_REPLICATION_REASSEMBLY_COMPLETE:
        if (completed_delta_id != fragment.delta_id) {
            break_replication_reassembly_free(payload);
            bridge->rejected_fragments++;
            return false;
        }
        bridge->completed_packets++;
        bridge_enqueue_completion(bridge, connection, completed_delta_id, payload,
                                  payload_size);
        return true;
    default:
        break_replication_reassembly_free(payload);
        bridge->rejected_fragments++;
        return false;
    }
}

size_t break_replication_session_poll_completed(
    BreakReplicationSessionBridge *bridge,
    BreakReplicationSessionCompletion *out, size_t out_capacity)
{
    size_t moved = 0u;
    if (!bridge || !out || out_capacity == 0u) return 0u;
    while (moved < out_capacity && bridge->completion_count > 0u) {
        BreakReplicationSessionCompletion *entry = bridge_completion_at(bridge, 0u);
        out[moved++] = *entry;
        bridge->completion_bytes -= entry->payload_size;
        memset(entry, 0, sizeof(*entry));
        bridge->completion_head =
            (bridge->completion_head + 1u) % bridge->config.completion_capacity;
        bridge->completion_count--;
    }
    return moved;
}

size_t break_replication_session_poll_completed_for_connection(
    BreakReplicationSessionBridge *bridge, BreakConnectionKey connection,
    BreakReplicationSessionCompletion *out, size_t out_capacity)
{
    size_t original_count;
    size_t kept = 0u;
    size_t moved = 0u;
    if (!bridge || connection == 0u || !out || out_capacity == 0u) return 0u;
    original_count = bridge->completion_count;
    for (size_t i = 0u; i < original_count; ++i) {
        BreakReplicationSessionCompletion *entry = bridge_completion_at(bridge, i);
        if (entry->connection == connection && moved < out_capacity) {
            out[moved++] = *entry;
            bridge->completion_bytes -= entry->payload_size;
            memset(entry, 0, sizeof(*entry));
            continue;
        }
        if (kept != i) {
            BreakReplicationSessionCompletion *target = bridge_completion_at(bridge, kept);
            *target = *entry;
            memset(entry, 0, sizeof(*entry));
        }
        kept++;
    }
    bridge->completion_count = kept;
    return moved;
}

void break_replication_session_completion_release(
    BreakReplicationSessionCompletion *completion)
{
    if (!completion) return;
    break_replication_reassembly_free(completion->payload);
    memset(completion, 0, sizeof(*completion));
}

void break_replication_session_bridge_stats(
    const BreakReplicationSessionBridge *bridge,
    BreakReplicationSessionBridgeStats *out_stats)
{
    size_t i;
    if (!out_stats) return;
    memset(out_stats, 0, sizeof(*out_stats));
    if (!bridge) return;
    out_stats->connections = bridge->connection_count;
    for (i = 0u; i < bridge->config.max_connections; ++i) {
        out_stats->pending_bytes +=
            break_replication_reassembly_pool_pending_bytes(bridge->connections[i].pool);
    }
    out_stats->completion_count = bridge->completion_count;
    out_stats->completion_bytes = bridge->completion_bytes;
    out_stats->rejected_fragments = bridge->rejected_fragments;
    out_stats->duplicate_fragments = bridge->duplicate_fragments;
    out_stats->completed_packets = bridge->completed_packets;
    out_stats->dropped_completions = bridge->dropped_completions;
    out_stats->expired_streams = bridge->expired_streams;
}
