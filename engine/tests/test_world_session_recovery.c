#include "test_framework.h"

#include <ecs/world_session.h>
#include <network/break_net_envelope.h>
#include <network/break_net_message_registry.h>
#include <network/break_replication_wire.h>
#include <snow/acceptor.h>
#include <snow/endpoint.h>

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define TEST_COMPONENT 11u
#define TEST_PROTOCOL 1u
#define TEST_LEVEL 7u

typedef struct {
    u32 value;
} Value;

typedef struct {
    BreakComponentSchemaRegistry *schemas;
    World *authoritative;
    World *remote;
    BreakWorldSession *session;
    BreakNetReactor *reactor;
    SnowAcceptor *acceptor;
    u64 now;
    u64 epoch;
} Fixture;

typedef struct {
    u64 delta_id;
    BreakWorldDeltaWireKind kind;
    u64 base_snapshot_id;
    u64 base_tick;
    u64 target_snapshot_id;
    u64 target_tick;
    u64 level_generation;
    u8 *payload;
    usize payload_size;
} AttemptWire;

static u64 test_clock(void *user)
{
    return *(const u64 *)user;
}

static u64 get64(const u8 *bytes)
{
    u64 value = 0u;
    for (u32 i = 0u; i < 8u; ++i) value |= (u64)bytes[i] << (i * 8u);
    return value;
}

static void put16(u8 *out, u16 value)
{
    out[0] = (u8)value;
    out[1] = (u8)(value >> 8u);
}

static void put64(u8 *out, u64 value)
{
    for (u32 i = 0u; i < 8u; ++i) out[i] = (u8)(value >> (i * 8u));
}

static bool reactor_start(Fixture *fixture)
{
    BreakNetReactorConfig config = {BREAK_NET_DRIVE_STEP, 0, 4u, 1000, 1000u, 1u};
    SnowEndpoint *endpoint = NULL;
    if (SnowEndpointCreate(&endpoint) != SNOW_OK ||
        SnowEndpointSetHost(endpoint, "127.0.0.1") != SNOW_OK ||
        SnowEndpointSetPort(endpoint, 0) != SNOW_OK ||
        SnowAcceptorCreate(endpoint, &fixture->acceptor) != SNOW_OK) {
        SnowEndpointDestroy(endpoint);
        return false;
    }
    SnowEndpointDestroy(endpoint);
    if (SnowAcceptorBind(fixture->acceptor, 1) != SNOW_OK) return false;
    fixture->reactor = break_net_reactor_create(&config);
    return fixture->reactor &&
           break_net_reactor_set_acceptor(fixture->reactor, fixture->acceptor) &&
           break_net_reactor_start(fixture->reactor);
}

static bool add_value(World *world, Entity entity, u32 value)
{
    Value *component = (Value *)world_add_component(world, entity, TEST_COMPONENT);
    if (!component) return false;
    component->value = value;
    return true;
}

static bool set_value(World *world, u32 value)
{
    Value *component;
    if (break_world_entity_count(world) == 0u) {
        Entity entity = world_create_entity(world);
        return add_value(world, entity, value);
    }
    component = (Value *)world_get_component(world, (Entity){1u, 1u}, TEST_COMPONENT);
    if (!component) return false;
    component->value = value;
    return true;
}

static bool fixture_init_scaled(Fixture *fixture, usize history_entries,
                                usize history_bytes, usize packet_bytes,
                                usize fragment_bytes, usize completion_capacity,
                                usize fragment_count)
{
    BreakComponentSchema schema;
    BreakWorldSessionConfig config;
    memset(fixture, 0, sizeof(*fixture));
    memset(&schema, 0, sizeof(schema));
    schema.component_id = TEST_COMPONENT;
    schema.version = 1u;
    schema.size = sizeof(Value);
    schema.alignment = _Alignof(Value);
    schema.flags = BREAK_SCHEMA_FLAG_DETERMINISTIC_POD | BREAK_SCHEMA_FLAG_RAW_BYTES;
    fixture->schemas = break_schema_registry_create();
    fixture->authoritative = world_create();
    fixture->remote = world_create();
    if (!fixture->schemas || !fixture->authoritative || !fixture->remote ||
        break_schema_register(fixture->schemas, &schema) != BREAK_SCHEMA_OK ||
        !reactor_start(fixture)) {
        return false;
    }
    world_register_component(fixture->authoritative, TEST_COMPONENT, sizeof(Value));
    world_register_component(fixture->remote, TEST_COMPONENT, sizeof(Value));
    memset(&config, 0, sizeof(config));
    config.schemas = fixture->schemas;
    config.protocol_version = TEST_PROTOCOL;
    config.level_generation = TEST_LEVEL;
    config.bridge.reactor = fixture->reactor;
    config.bridge.max_connections = 2u;
    config.bridge.stream_capacity = 4u;
    config.bridge.max_pending_bytes_per_connection = 8192u;
    config.bridge.max_total_pending_bytes = 16384u;
    config.bridge.max_fragment_bytes = fragment_bytes;
    config.bridge.max_fragment_count = fragment_count;
    config.bridge.completion_capacity = completion_capacity;
    config.bridge.max_completion_packet_bytes = 8192u;
    config.bridge.max_completion_queue_bytes = 16384u;
    config.bridge.clock = test_clock;
    config.bridge.clock_user = &fixture->now;
    config.history_entry_limit = history_entries;
    config.history_byte_limit = history_bytes;
    config.packet_byte_limit = packet_bytes;
    config.need_full_tick_interval = 5u;
    fixture->session = break_world_session_create(&config);
    if (!fixture->session || !break_world_session_open(fixture->session, 11u)) return false;
    fixture->epoch = break_world_session_stream_epoch(
        TEST_PROTOCOL, break_schema_hash(fixture->schemas), TEST_LEVEL);
    return true;
}

static bool fixture_init(Fixture *fixture)
{
    return fixture_init_scaled(fixture, 4u, 16384u, 4096u, 4096u, 8u, 64u);
}

static void fixture_dispose(Fixture *fixture)
{
    break_world_session_destroy(fixture->session);
    world_destroy(fixture->remote);
    world_destroy(fixture->authoritative);
    break_schema_registry_destroy(fixture->schemas);
    if (fixture->reactor) {
        (void)break_net_reactor_stop(fixture->reactor, 1000u);
        break_net_reactor_destroy(fixture->reactor);
    }
    if (fixture->acceptor) SnowAcceptorDestroy(fixture->acceptor);
    memset(fixture, 0, sizeof(*fixture));
}

static bool encode_message(BreakWorldDeltaWire *message, u8 **out_wire, usize *out_size)
{
    usize size = 0u;
    u8 *wire;
    bool ok;
    if (break_world_delta_wire_encoded_size(message, &size) != BREAK_WORLD_DELTA_WIRE_OK) {
        free(message->records);
        return false;
    }
    wire = (u8 *)malloc(size);
    if (!wire) {
        free(message->records);
        return false;
    }
    ok = break_world_delta_wire_encode(message, wire, size, &size) ==
         BREAK_WORLD_DELTA_WIRE_OK;
    free(message->records);
    if (!ok) {
        free(wire);
        return false;
    }
    *out_wire = wire;
    *out_size = size;
    return true;
}

static bool encode_full(const BreakWorldSnapshot *snapshot, u8 **out_wire, usize *out_size)
{
    BreakWorldDeltaWire message;
    usize entity_count = break_world_snapshot_entity_count(snapshot);
    usize count = 0u;
    usize slot = 0u;
    memset(&message, 0, sizeof(message));
    for (usize i = 0u; i < entity_count; ++i) {
        Entity entity = break_world_snapshot_entity_at(snapshot, i);
        ++count;
        for (u32 component = 0u; component < ECS_MAX_COMPONENTS; ++component) {
            const void *bytes = NULL;
            usize size = 0u;
            if (break_world_snapshot_component_bytes(snapshot, entity, component,
                                                      &bytes, &size)) {
                ++count;
            }
        }
    }
    if (count > UINT32_MAX) return false;
    message.kind = BREAK_WORLD_DELTA_WIRE_FULL;
    message.schema_hash = break_world_snapshot_schema_hash(snapshot);
    message.level_generation = TEST_LEVEL;
    message.target_snapshot_id = break_world_snapshot_id(snapshot);
    message.target_tick = break_world_snapshot_tick(snapshot);
    message.record_count = (u32)count;
    if (count != 0u) {
        message.records = (BreakWorldDeltaRecord *)calloc(count, sizeof(*message.records));
        if (!message.records) return false;
    }
    for (usize i = 0u; i < entity_count; ++i) {
        Entity entity = break_world_snapshot_entity_at(snapshot, i);
        message.records[slot].kind = BREAK_DELTA_ENTITY_CREATE;
        message.records[slot].entity = entity;
        ++slot;
        for (u32 component = 0u; component < ECS_MAX_COMPONENTS; ++component) {
            const void *bytes = NULL;
            usize size = 0u;
            if (break_world_snapshot_component_bytes(snapshot, entity, component,
                                                      &bytes, &size)) {
                message.records[slot].kind = BREAK_DELTA_COMPONENT_ADD;
                message.records[slot].entity = entity;
                message.records[slot].component = component;
                message.records[slot].bytes = bytes;
                message.records[slot].size = size;
                ++slot;
            }
        }
    }
    return encode_message(&message, out_wire, out_size);
}

static bool encode_delta(const BreakWorldSnapshot *base, const BreakWorldSnapshot *target,
                         u8 **out_wire, usize *out_size)
{
    BreakWorldDelta *delta = break_world_delta_diff(base, target);
    BreakWorldDeltaWire message;
    usize count;
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
    message.level_generation = TEST_LEVEL;
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
        for (usize i = 0u; i < count; ++i) {
            if (!break_world_delta_record_at(delta, i, &message.records[i])) {
                free(message.records);
                break_world_delta_release(delta);
                return false;
            }
        }
    }
    ok = encode_message(&message, out_wire, out_size);
    break_world_delta_release(delta);
    return ok;
}

static bool push_bytes(Fixture *fixture, u64 delta_id, const void *bytes, usize size)
{
    BreakReplicationFragment *fragments = NULL;
    usize count = 0u;
    bool handled = true;
    if (break_replication_fragment_payload(delta_id, fixture->epoch, bytes, size, 23u,
                                           &fragments, &count) !=
        BREAK_REPLICATION_FRAGMENT_OK) {
        return false;
    }
    for (usize i = 0u; i < count; ++i) {
        u8 wire[BREAK_REPLICATION_WIRE_HEADER_SIZE + 64u];
        usize wire_size = 0u;
        BreakNetOwnedMessage message;
        memset(&message, 0, sizeof(message));
        if (break_replication_wire_encode(&fragments[i], wire, sizeof(wire), &wire_size) !=
            BREAK_REPLICATION_FRAGMENT_OK) {
            handled = false;
            break;
        }
        message.message_id = BREAK_NET_MESSAGE_ID_WORLD_DELTA;
        message.protocol_version = BREAK_REPLICATION_WIRE_VERSION;
        message.sequence = (u32)i + 1u;
        message.data = wire;
        message.size = wire_size;
        if (!break_replication_session_handle_message(
                11u, &message, break_world_session_bridge(fixture->session))) {
            handled = false;
            break;
        }
    }
    break_replication_fragments_free(fragments, count);
    return handled;
}

static bool receive_full(Fixture *fixture, const BreakWorldSnapshot *snapshot, u64 delta_id)
{
    u8 *wire = NULL;
    usize size = 0u;
    bool ok = encode_full(snapshot, &wire, &size) && push_bytes(fixture, delta_id, wire, size) &&
              break_world_session_drain(fixture->session, 11u, fixture->remote, 1u) == 1u;
    free(wire);
    return ok;
}

static bool receive_bad_delta(Fixture *fixture, const BreakWorldSnapshot *base,
                              const BreakWorldSnapshot *target, u64 delta_id)
{
    u8 *wire = NULL;
    usize size = 0u;
    bool ok;
    if (!encode_delta(base, target, &wire, &size)) return false;
    wire[24] ^= 1u;
    ok = push_bytes(fixture, delta_id, wire, size) &&
         break_world_session_drain(fixture->session, 11u, fixture->remote, 1u) == 1u;
    free(wire);
    return ok;
}

static bool collect_attempt_for_connection(Fixture *fixture, BreakConnectionKey connection,
                                           AttemptWire *out)
{
    BreakReplicationReassembler *reassembler =
        break_replication_reassembler_create(fixture->epoch);
    BreakNetOwnedMessage message;
    u64 outbound_connection = 0u;
    BreakWorldDeltaWire decoded;
    bool ok = reassembler != NULL;
    memset(out, 0, sizeof(*out));
    while (ok && break_net_reactor_poll_outbound_for_test(
                      fixture->reactor, &outbound_connection, &message) ==
                      BREAK_NET_EVENT_OK) {
        BreakReplicationFragment fragment;
        BreakReplicationReassemblyResult result;
        if (outbound_connection != connection ||
            message.message_id != BREAK_NET_MESSAGE_ID_WORLD_DELTA ||
            break_replication_wire_decode(message.data, message.size, &fragment) !=
                BREAK_REPLICATION_FRAGMENT_OK) {
            break_net_message_release(&message);
            ok = false;
            break;
        }
        result = break_replication_reassembler_push(reassembler, &fragment,
                                                    &out->payload, &out->payload_size);
        if (result == BREAK_REPLICATION_REASSEMBLY_COMPLETE) {
            out->delta_id = fragment.delta_id;
        } else if (result != BREAK_REPLICATION_REASSEMBLY_INCOMPLETE) {
            ok = false;
        }
        break_net_message_release(&message);
    }
    break_replication_reassembler_destroy(reassembler);
    if (!ok || !out->payload ||
        break_world_delta_wire_decode(out->payload, out->payload_size, &decoded) !=
            BREAK_WORLD_DELTA_WIRE_OK) {
        break_replication_reassembly_free(out->payload);
        memset(out, 0, sizeof(*out));
        return false;
    }
    out->kind = decoded.kind;
    out->base_snapshot_id = decoded.base_snapshot_id;
    out->base_tick = decoded.base_tick;
    out->target_snapshot_id = decoded.target_snapshot_id;
    out->target_tick = decoded.target_tick;
    out->level_generation = decoded.level_generation;
    break_world_delta_wire_clear(&decoded);
    return true;
}

static void clear_attempt(AttemptWire *attempt)
{
    break_replication_reassembly_free(attempt->payload);
    memset(attempt, 0, sizeof(*attempt));
}

static bool publish_attempt_for_connection(Fixture *fixture, BreakConnectionKey connection,
                                           u32 value, u64 tick, AttemptWire *out)
{
    if (!set_value(fixture->authoritative, value) ||
        break_world_session_publish(fixture->session, connection, fixture->authoritative,
                                    tick) != BREAK_NET_SEND_OK) {
        return false;
    }
    return collect_attempt_for_connection(fixture, connection, out);
}

static bool publish_attempt(Fixture *fixture, u32 value, u64 tick, AttemptWire *out)
{
    return publish_attempt_for_connection(fixture, 11u, value, tick, out);
}

static bool publish_snapshot_attempt_for_connection(Fixture *fixture,
                                                    BreakConnectionKey connection,
                                                    BreakWorldSnapshot *target,
                                                    u64 level_generation, AttemptWire *out)
{
    if (break_world_session_publish_snapshot(fixture->session, connection, target,
                                             level_generation) != BREAK_NET_SEND_OK) {
        return false;
    }
    return collect_attempt_for_connection(fixture, connection, out);
}

static bool send_control_version_to_session(Fixture *fixture, BreakConnectionKey connection,
                                            u16 outer_version, u16 payload_version,
                                            usize payload_size, u64 level_generation,
                                            const BreakWorldSessionControl *control)
{
    u8 payload[BREAK_WORLD_SESSION_CONTROL_WIRE_SIZE_V2 + 1u];
    BreakNetOwnedMessage message;
    memset(payload, 0, sizeof(payload));
    memcpy(payload, "BRWC", 4u);
    put16(payload + 4u, payload_version);
    put16(payload + 6u, (u16)control->kind);
    put64(payload + 8u, control->delta_id);
    put64(payload + 16u, control->target_snapshot_id);
    put64(payload + 24u, control->target_tick);
    put64(payload + 32u, level_generation);
    memset(&message, 0, sizeof(message));
    message.message_id = BREAK_NET_MESSAGE_ID_WORLD_CONTROL;
    message.protocol_version = outer_version;
    message.sequence = 1u;
    message.data = payload;
    message.size = payload_size;
    return break_world_session_handle_control(connection, &message, fixture->session);
}

static bool send_control_to_session(Fixture *fixture,
                                    const BreakWorldSessionControl *control)
{
    return send_control_version_to_session(fixture, 11u, 1u, 1u,
                                           BREAK_WORLD_SESSION_CONTROL_WIRE_SIZE, 0u,
                                           control);
}

static bool send_control_v2_to_session(Fixture *fixture, BreakConnectionKey connection,
                                       u64 level_generation,
                                       const BreakWorldSessionControl *control)
{
    return send_control_version_to_session(fixture, connection, 2u, 2u,
                                           BREAK_WORLD_SESSION_CONTROL_WIRE_SIZE_V2,
                                           level_generation, control);
}

static bool ack_attempt_for_connection(Fixture *fixture, BreakConnectionKey connection,
                                       const AttemptWire *attempt, u16 version,
                                       u64 level_generation)
{
    BreakWorldSessionControl control;
    memset(&control, 0, sizeof(control));
    control.kind = BREAK_WORLD_SESSION_CONTROL_ACK;
    control.delta_id = attempt->delta_id;
    control.target_snapshot_id = attempt->target_snapshot_id;
    control.target_tick = attempt->target_tick;
    control.level_generation = level_generation;
    if (version == 1u) {
        return send_control_version_to_session(fixture, connection, 1u, 1u,
                                               BREAK_WORLD_SESSION_CONTROL_WIRE_SIZE, 0u,
                                               &control);
    }
    return send_control_version_to_session(fixture, connection, version, version,
                                           version == 2u
                                               ? BREAK_WORLD_SESSION_CONTROL_WIRE_SIZE_V2
                                               : BREAK_WORLD_SESSION_CONTROL_WIRE_SIZE,
                                           level_generation, &control);
}

static bool ack_attempt(Fixture *fixture, const AttemptWire *attempt)
{
    return ack_attempt_for_connection(fixture, 11u, attempt, 1u, 0u);
}

static bool ack_attempt_v2(Fixture *fixture, BreakConnectionKey connection,
                           const AttemptWire *attempt, u64 level_generation)
{
    return ack_attempt_for_connection(fixture, connection, attempt, 2u, level_generation);
}

static bool invalid_snapshot_publish_preserves_state(
    Fixture *fixture, BreakConnectionKey connection, BreakWorldSnapshot *target,
    u64 level_generation, const BreakWorldSessionSenderState *before,
    const BreakWorldSessionStats *stats_before)
{
    BreakWorldSessionSenderState after;
    BreakWorldSessionStats stats_after;
    if (break_world_session_publish_snapshot(fixture->session, connection, target,
                                             level_generation) != BREAK_NET_SEND_INVALID) {
        return false;
    }
    if (!break_world_session_sender_state(fixture->session, connection, &after)) return false;
    break_world_session_stats(fixture->session, &stats_after);
    return memcmp(before, &after, sizeof(after)) == 0 &&
           memcmp(stats_before, &stats_after, sizeof(stats_after)) == 0 &&
           break_net_reactor_outbound_count(fixture->reactor) == 0u;
}

static void clear_controls(Fixture *fixture)
{
    BreakWorldSessionControl control;
    while (break_world_session_poll_control(fixture->session, 11u, &control)) {
    }
}

TEST(world_session_need_full_is_rate_limited_and_control_wire_has_last_good)
{
    Fixture fixture;
    BreakWorldSnapshot *base;
    BreakWorldSnapshot *target;
    BreakWorldSessionControl control;
    BreakWorldSessionStats stats;
    BreakNetOwnedMessage outbound;
    u64 outbound_connection = 0u;

    ASSERT_TRUE(fixture_init(&fixture));
    ASSERT_TRUE(set_value(fixture.authoritative, 10u));
    base = break_world_snapshot_build(fixture.authoritative, fixture.schemas, 10u);
    ASSERT_NOT_NULL(base);
    ASSERT_TRUE(receive_full(&fixture, base, 90u));
    clear_controls(&fixture);

    ASSERT_TRUE(set_value(fixture.authoritative, 11u));
    target = break_world_snapshot_build(fixture.authoritative, fixture.schemas, 20u);
    ASSERT_NOT_NULL(target);
    ASSERT_TRUE(receive_bad_delta(&fixture, base, target, 91u));
    break_world_snapshot_release(target);
    ASSERT_TRUE(break_world_session_poll_control(fixture.session, 11u, &control));
    ASSERT_EQ(control.kind, BREAK_WORLD_SESSION_CONTROL_NEED_FULL);
    ASSERT_EQ(control.delta_id, 0u);
    ASSERT_EQ(control.target_snapshot_id, break_world_snapshot_id(base));
    ASSERT_EQ(control.target_tick, 10u);
    ASSERT_EQ(break_world_session_send_control(fixture.session, 11u, &control),
              BREAK_NET_SEND_OK);
    ASSERT_EQ(break_net_reactor_poll_outbound_for_test(
                  fixture.reactor, &outbound_connection, &outbound),
              BREAK_NET_EVENT_OK);
    ASSERT_EQ(outbound.message_id, BREAK_NET_MESSAGE_ID_WORLD_CONTROL);
    ASSERT_EQ(outbound.protocol_version, 1u);
    ASSERT_EQ(outbound.size, (usize)BREAK_WORLD_SESSION_CONTROL_WIRE_SIZE);
    ASSERT_TRUE(memcmp(outbound.data, "BRWC", 4u) == 0);
    ASSERT_EQ(get64((const u8 *)outbound.data + 16u), break_world_snapshot_id(base));
    ASSERT_EQ(get64((const u8 *)outbound.data + 24u), 10u);
    break_net_message_release(&outbound);
    ASSERT_FALSE(break_world_session_poll_control(fixture.session, 11u, &control));

    target = break_world_snapshot_build(fixture.authoritative, fixture.schemas, 21u);
    ASSERT_NOT_NULL(target);
    ASSERT_TRUE(receive_bad_delta(&fixture, base, target, 92u));
    break_world_snapshot_release(target);
    ASSERT_FALSE(break_world_session_poll_control(fixture.session, 11u, &control));
    break_world_session_stats(fixture.session, &stats);
    ASSERT_EQ(stats.need_full_packets, 2u);
    ASSERT_EQ(stats.need_full_suppressed, 1u);

    target = break_world_snapshot_build(fixture.authoritative, fixture.schemas, 25u);
    ASSERT_NOT_NULL(target);
    ASSERT_TRUE(receive_bad_delta(&fixture, base, target, 93u));
    break_world_snapshot_release(target);
    ASSERT_TRUE(break_world_session_poll_control(fixture.session, 11u, &control));
    ASSERT_EQ(control.kind, BREAK_WORLD_SESSION_CONTROL_NEED_FULL);
    ASSERT_EQ(control.target_snapshot_id, break_world_snapshot_id(base));
    break_world_snapshot_release(base);
    fixture_dispose(&fixture);
}

TEST(world_session_ack_trims_history_and_need_full_publishes_fresh_full)
{
    Fixture fixture;
    AttemptWire first;
    AttemptWire second;
    AttemptWire third;
    AttemptWire fourth;
    AttemptWire fifth;
    BreakWorldSessionSenderState state;
    BreakWorldSessionControl recovery;
    BreakWorldSessionStats stats;

    ASSERT_TRUE(fixture_init(&fixture));
    ASSERT_TRUE(publish_attempt(&fixture, 10u, 10u, &first));
    ASSERT_EQ(first.kind, BREAK_WORLD_DELTA_WIRE_FULL);
    ASSERT_EQ(first.delta_id, 1u);
    ASSERT_TRUE(ack_attempt(&fixture, &first));
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 11u, &state));
    ASSERT_EQ(state.history_count, 0u);
    ASSERT_EQ(state.confirmed_snapshot_id, first.target_snapshot_id);

    ASSERT_TRUE(publish_attempt(&fixture, 11u, 20u, &second));
    ASSERT_EQ(second.kind, BREAK_WORLD_DELTA_WIRE_DELTA);
    ASSERT_EQ(second.base_snapshot_id, first.target_snapshot_id);
    ASSERT_TRUE(publish_attempt(&fixture, 12u, 30u, &third));
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 11u, &state));
    ASSERT_EQ(state.history_count, 2u);
    ASSERT_EQ(state.history_bytes, second.payload_size + third.payload_size);
    ASSERT_TRUE(ack_attempt(&fixture, &second));
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 11u, &state));
    ASSERT_EQ(state.history_count, 1u);
    ASSERT_EQ(state.history_bytes, third.payload_size);
    ASSERT_EQ(state.confirmed_snapshot_id, second.target_snapshot_id);

    memset(&recovery, 0, sizeof(recovery));
    recovery.kind = BREAK_WORLD_SESSION_CONTROL_NEED_FULL;
    recovery.target_snapshot_id = second.target_snapshot_id;
    recovery.target_tick = second.target_tick;
    ASSERT_TRUE(send_control_to_session(&fixture, &recovery));
    ASSERT_TRUE(publish_attempt(&fixture, 13u, 40u, &fourth));
    ASSERT_EQ(fourth.kind, BREAK_WORLD_DELTA_WIRE_FULL);
    ASSERT_EQ(fourth.delta_id, 4u);
    ASSERT_EQ(fourth.base_snapshot_id, 0u);
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 11u, &state));
    ASSERT_EQ(state.history_count, 1u);
    ASSERT_EQ(state.history_bytes, fourth.payload_size);
    ASSERT_EQ(state.confirmed_snapshot_id, 0u);
    ASSERT_EQ(state.next_delta_id, 5u);

    ASSERT_TRUE(ack_attempt(&fixture, &fourth));
    ASSERT_TRUE(publish_attempt(&fixture, 14u, 50u, &fifth));
    ASSERT_EQ(fifth.kind, BREAK_WORLD_DELTA_WIRE_DELTA);
    ASSERT_EQ(fifth.base_snapshot_id, fourth.target_snapshot_id);
    break_world_session_stats(fixture.session, &stats);
    ASSERT_EQ(stats.published_full_packets, 2u);
    ASSERT_EQ(stats.published_delta_packets, 3u);
    ASSERT_EQ(stats.acknowledged_packets, 3u);
    clear_attempt(&fifth);
    clear_attempt(&fourth);
    clear_attempt(&third);
    clear_attempt(&second);
    clear_attempt(&first);
    fixture_dispose(&fixture);
}

TEST(world_session_ack_after_need_full_does_not_reuse_unconfirmed_baseline)
{
    Fixture fixture;
    AttemptWire initial;
    AttemptWire first;
    AttemptWire second;
    AttemptWire recovered;
    BreakWorldSnapshot *receiver_first;
    BreakWorldSnapshot *receiver_second;
    BreakWorldSessionControl recovery;
    BreakWorldSessionSenderState state;

    ASSERT_TRUE(fixture_init(&fixture));
    ASSERT_TRUE(publish_attempt(&fixture, 5u, 5u, &initial));
    ASSERT_TRUE(ack_attempt(&fixture, &initial));
    ASSERT_TRUE(publish_attempt(&fixture, 10u, 10u, &first));
    receiver_first = break_world_snapshot_build(fixture.authoritative, fixture.schemas, 10u);
    ASSERT_NOT_NULL(receiver_first);
    ASSERT_TRUE(receive_full(&fixture, receiver_first, 90u));
    ASSERT_TRUE(publish_attempt(&fixture, 20u, 20u, &second));
    receiver_second = break_world_snapshot_build(fixture.authoritative, fixture.schemas, 20u);
    ASSERT_NOT_NULL(receiver_second);
    ASSERT_TRUE(receive_bad_delta(&fixture, receiver_first, receiver_second, 91u));
    ASSERT_TRUE(break_world_session_poll_control(fixture.session, 11u, &recovery));
    ASSERT_EQ(recovery.kind, BREAK_WORLD_SESSION_CONTROL_NEED_FULL);
    ASSERT_EQ(recovery.target_snapshot_id, first.target_snapshot_id);
    ASSERT_TRUE(send_control_to_session(&fixture, &recovery));
    ASSERT_TRUE(ack_attempt(&fixture, &first));
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 11u, &state));
    ASSERT_EQ(state.history_count, 1u);
    ASSERT_EQ(state.confirmed_snapshot_id, first.target_snapshot_id);

    ASSERT_TRUE(publish_attempt(&fixture, 30u, 30u, &recovered));
    ASSERT_EQ(recovered.kind, BREAK_WORLD_DELTA_WIRE_FULL);
    ASSERT_EQ(recovered.delta_id, 4u);
    ASSERT_EQ(recovered.base_snapshot_id, 0u);
    ASSERT_NEQ(recovered.base_snapshot_id, second.target_snapshot_id);
    clear_attempt(&recovered);
    break_world_snapshot_release(receiver_second);
    break_world_snapshot_release(receiver_first);
    clear_attempt(&second);
    clear_attempt(&first);
    clear_attempt(&initial);
    fixture_dispose(&fixture);
}

static void check_history_fallback(bool byte_limited)
{
    Fixture fixture;
    AttemptWire initial;
    AttemptWire second;
    AttemptWire third;
    AttemptWire fourth;
    BreakWorldSessionSenderState state;
    usize entries = byte_limited ? 8u : 2u;
    usize bytes = byte_limited ? 128u : 16384u;

    ASSERT_TRUE(fixture_init_scaled(&fixture, entries, bytes, 4096u, 4096u, 8u, 64u));
    ASSERT_TRUE(publish_attempt(&fixture, 10u, 10u, &initial));
    ASSERT_TRUE(ack_attempt(&fixture, &initial));
    ASSERT_TRUE(publish_attempt(&fixture, 11u, 20u, &second));
    ASSERT_EQ(second.kind, BREAK_WORLD_DELTA_WIRE_DELTA);
    ASSERT_TRUE(publish_attempt(&fixture, 12u, 30u, &third));
    if (!byte_limited) {
        ASSERT_EQ(third.kind, BREAK_WORLD_DELTA_WIRE_DELTA);
        ASSERT_TRUE(publish_attempt(&fixture, 13u, 40u, &fourth));
    } else {
        fourth = third;
        memset(&third, 0, sizeof(third));
    }
    ASSERT_EQ(fourth.kind, BREAK_WORLD_DELTA_WIRE_FULL);
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 11u, &state));
    ASSERT_EQ(state.history_count, 1u);
    ASSERT_EQ(state.history_bytes, fourth.payload_size);
    if (!byte_limited) clear_attempt(&third);
    clear_attempt(&fourth);
    clear_attempt(&second);
    clear_attempt(&initial);
    fixture_dispose(&fixture);
}

TEST(world_session_history_count_and_byte_limits_fall_back_to_full)
{
    check_history_fallback(false);
    check_history_fallback(true);
}

TEST(world_session_packet_limit_rejects_without_allocating_history)
{
    Fixture fixture;
    BreakWorldSessionSenderState state;

    ASSERT_TRUE(fixture_init_scaled(&fixture, 4u, 16384u, 80u, 4096u, 8u, 64u));
    ASSERT_TRUE(set_value(fixture.authoritative, 10u));
    ASSERT_EQ(break_world_session_publish(fixture.session, 11u, fixture.authoritative, 10u),
              BREAK_NET_SEND_INVALID);
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 11u, &state));
    ASSERT_EQ(state.history_count, 0u);
    ASSERT_EQ(state.history_bytes, 0u);
    ASSERT_EQ(state.next_delta_id, 1u);
    ASSERT_EQ(break_net_reactor_outbound_count(fixture.reactor), 0u);
    fixture_dispose(&fixture);
}

TEST(world_session_fragment_count_invalid_releases_attempt)
{
    Fixture fixture;
    BreakWorldSessionSenderState state;

    ASSERT_TRUE(fixture_init_scaled(&fixture, 4u, 16384u, 4096u, 64u, 8u, 1u));
    ASSERT_TRUE(set_value(fixture.authoritative, 42u));
    ASSERT_EQ(break_world_session_publish(fixture.session, 11u, fixture.authoritative, 10u),
              BREAK_NET_SEND_INVALID);
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 11u, &state));
    ASSERT_FALSE(state.attempt_pending);
    ASSERT_EQ(state.history_count, 0u);
    ASSERT_EQ(state.history_bytes, 0u);
    ASSERT_EQ(state.next_delta_id, 1u);
    ASSERT_EQ(break_net_reactor_outbound_count(fixture.reactor), 0u);
    fixture_dispose(&fixture);
}

TEST(world_session_overload_resumes_same_immutable_attempt)
{
    Fixture fixture;
    BreakWorldSnapshot *expected;
    BreakWorldSessionSenderState state;
    BreakNetOwnedMessage outbound;
    u64 outbound_connection = 0u;
    u8 first_wire[256];
    usize first_size = 0u;
    u8 *expected_wire = NULL;
    usize expected_size = 0u;
    u8 *payload = NULL;
    usize payload_size = 0u;
    BreakReplicationReassembler *reassembler;
    bool found_first = false;

    ASSERT_TRUE(fixture_init_scaled(&fixture, 4u, 16384u, 4096u, 64u, 8u, 64u));
    ASSERT_TRUE(set_value(fixture.authoritative, 42u));
    expected = break_world_snapshot_build(fixture.authoritative, fixture.schemas, 10u);
    ASSERT_NOT_NULL(expected);
    ASSERT_TRUE(encode_full(expected, &expected_wire, &expected_size));
    ASSERT_TRUE(expected_size > 64u);
    for (usize i = 0u; i < BREAK_NET_OUTBOUND_QUEUE_CAPACITY - 1u; ++i) {
        ASSERT_EQ(break_net_reactor_send(fixture.reactor, 11u,
                                         BREAK_NET_MESSAGE_ID_PING, 1u, "x", 1u),
                  BREAK_NET_SEND_OK);
    }
    ASSERT_EQ(break_world_session_publish(fixture.session, 11u, fixture.authoritative, 10u),
              BREAK_NET_SEND_OVERLOAD);
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 11u, &state));
    ASSERT_TRUE(state.attempt_pending);
    ASSERT_EQ(state.next_delta_id, 2u);
    ASSERT_EQ(state.history_count, 0u);
    ASSERT_TRUE(set_value(fixture.authoritative, 99u));

    while (break_net_reactor_poll_outbound_for_test(
               fixture.reactor, &outbound_connection, &outbound) == BREAK_NET_EVENT_OK) {
        if (outbound.message_id == BREAK_NET_MESSAGE_ID_WORLD_DELTA) {
            ASSERT_FALSE(found_first);
            ASSERT_TRUE(outbound.size <= sizeof(first_wire));
            memcpy(first_wire, outbound.data, outbound.size);
            first_size = outbound.size;
            found_first = true;
        }
        break_net_message_release(&outbound);
    }
    ASSERT_TRUE(found_first);
    ASSERT_EQ(break_world_session_publish(fixture.session, 11u, fixture.authoritative, 999u),
              BREAK_NET_SEND_OK);

    reassembler = break_replication_reassembler_create(fixture.epoch);
    ASSERT_NOT_NULL(reassembler);
    {
        BreakReplicationFragment fragment;
        ASSERT_EQ(break_replication_wire_decode(first_wire, first_size, &fragment),
                  BREAK_REPLICATION_FRAGMENT_OK);
        ASSERT_EQ(fragment.delta_id, 1u);
        ASSERT_EQ(break_replication_reassembler_push(reassembler, &fragment,
                                                     &payload, &payload_size),
                  BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    }
    ASSERT_EQ(break_net_reactor_poll_outbound_for_test(
                  fixture.reactor, &outbound_connection, &outbound),
              BREAK_NET_EVENT_OK);
    {
        BreakReplicationFragment fragment;
        ASSERT_EQ(outbound.message_id, BREAK_NET_MESSAGE_ID_WORLD_DELTA);
        ASSERT_EQ(break_replication_wire_decode(outbound.data, outbound.size, &fragment),
                  BREAK_REPLICATION_FRAGMENT_OK);
        ASSERT_EQ(fragment.delta_id, 1u);
        ASSERT_EQ(break_replication_reassembler_push(reassembler, &fragment,
                                                     &payload, &payload_size),
                  BREAK_REPLICATION_REASSEMBLY_COMPLETE);
    }
    break_net_message_release(&outbound);
    ASSERT_EQ(break_net_reactor_outbound_count(fixture.reactor), 0u);
    ASSERT_EQ(payload_size, expected_size);
    ASSERT_TRUE(memcmp(payload, expected_wire, expected_size) == 0);
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 11u, &state));
    ASSERT_FALSE(state.attempt_pending);
    ASSERT_EQ(state.history_count, 1u);
    ASSERT_EQ(state.history_bytes, expected_size);
    break_replication_reassembly_free(payload);
    break_replication_reassembler_destroy(reassembler);
    free(expected_wire);
    break_world_snapshot_release(expected);
    fixture_dispose(&fixture);
}

TEST(world_session_reconnect_clears_sender_receiver_and_rate_state)
{
    Fixture fixture;
    AttemptWire first;
    AttemptWire reopened;
    BreakWorldSnapshot *receiver_base;
    BreakWorldSnapshot *receiver_target;
    BreakWorldSessionControl control;
    BreakWorldSessionSenderState state;
    BreakNetOwnedMessage outbound;
    u64 outbound_connection = 0u;
    u64 baseline_id = 99u;
    u64 baseline_tick = 99u;

    ASSERT_TRUE(fixture_init(&fixture));
    ASSERT_TRUE(publish_attempt(&fixture, 10u, 10u, &first));
    receiver_base = break_world_snapshot_build(fixture.authoritative, fixture.schemas, 10u);
    ASSERT_NOT_NULL(receiver_base);
    ASSERT_TRUE(receive_full(&fixture, receiver_base, 90u));
    ASSERT_TRUE(ack_attempt(&fixture, &first));
    ASSERT_TRUE(set_value(fixture.authoritative, 20u));
    receiver_target = break_world_snapshot_build(fixture.authoritative, fixture.schemas, 20u);
    ASSERT_NOT_NULL(receiver_target);
    ASSERT_TRUE(receive_bad_delta(&fixture, receiver_base, receiver_target, 91u));
    ASSERT_TRUE(break_world_session_baseline(fixture.session, 11u,
                                             &baseline_id, &baseline_tick));
    ASSERT_EQ(baseline_id, first.target_snapshot_id);
    ASSERT_EQ(baseline_tick, 10u);
    for (usize i = 0u; i < BREAK_NET_OUTBOUND_QUEUE_CAPACITY; ++i) {
        ASSERT_EQ(break_net_reactor_send(fixture.reactor, 11u,
                                         BREAK_NET_MESSAGE_ID_PING, 1u, "x", 1u),
                  BREAK_NET_SEND_OK);
    }
    ASSERT_EQ(break_world_session_publish(fixture.session, 11u, fixture.authoritative, 30u),
              BREAK_NET_SEND_OVERLOAD);
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 11u, &state));
    ASSERT_TRUE(state.attempt_pending);
    ASSERT_EQ(state.next_delta_id, 3u);
    ASSERT_EQ(state.confirmed_snapshot_id, first.target_snapshot_id);
    ASSERT_TRUE(break_world_session_close(fixture.session, 11u));
    ASSERT_FALSE(break_world_session_sender_state(fixture.session, 11u, &state));
    ASSERT_EQ(state.history_count, 0u);
    ASSERT_EQ(state.next_delta_id, 0u);
    while (break_net_reactor_poll_outbound_for_test(
               fixture.reactor, &outbound_connection, &outbound) == BREAK_NET_EVENT_OK) {
        break_net_message_release(&outbound);
    }
    ASSERT_TRUE(break_world_session_open(fixture.session, 11u));
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 11u, &state));
    ASSERT_EQ(state.history_count, 0u);
    ASSERT_EQ(state.history_bytes, 0u);
    ASSERT_EQ(state.confirmed_snapshot_id, 0u);
    ASSERT_EQ(state.confirmed_tick, 0u);
    ASSERT_EQ(state.next_delta_id, 1u);
    ASSERT_FALSE(state.attempt_pending);
    ASSERT_TRUE(break_world_session_baseline(fixture.session, 11u,
                                             &baseline_id, &baseline_tick));
    ASSERT_EQ(baseline_id, 0u);
    ASSERT_EQ(baseline_tick, 0u);
    ASSERT_FALSE(break_world_session_poll_control(fixture.session, 11u, &control));
    ASSERT_TRUE(publish_attempt(&fixture, 40u, 40u, &reopened));
    ASSERT_EQ(reopened.delta_id, 1u);
    ASSERT_EQ(reopened.kind, BREAK_WORLD_DELTA_WIRE_FULL);
    clear_attempt(&reopened);
    break_world_snapshot_release(receiver_target);
    break_world_snapshot_release(receiver_base);
    clear_attempt(&first);
    fixture_dispose(&fixture);
}

TEST(world_session_rebaseline_resets_sender_and_requires_current_ack)
{
    Fixture fixture;
    AttemptWire initial;
    AttemptWire old_delta;
    AttemptWire recovered;
    AttemptWire delta;
    BreakWorldSessionSenderState state;
    BreakWorldSessionStats before;
    BreakWorldSessionStats after;

    ASSERT_TRUE(fixture_init(&fixture));
    ASSERT_TRUE(publish_attempt(&fixture, 10u, 10u, &initial));
    ASSERT_EQ(initial.kind, BREAK_WORLD_DELTA_WIRE_FULL);
    ASSERT_EQ(initial.level_generation, TEST_LEVEL);
    ASSERT_TRUE(ack_attempt(&fixture, &initial));
    ASSERT_TRUE(publish_attempt(&fixture, 11u, 20u, &old_delta));
    ASSERT_EQ(old_delta.kind, BREAK_WORLD_DELTA_WIRE_DELTA);
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 11u, &state));
    ASSERT_EQ(state.history_count, 1u);
    ASSERT_EQ(state.confirmed_snapshot_id, initial.target_snapshot_id);
    ASSERT_EQ(state.next_delta_id, 3u);
    break_world_session_stats(fixture.session, &before);

    ASSERT_TRUE(break_world_session_rebaseline(fixture.session, 8u));
    ASSERT_EQ(break_world_session_level_generation(fixture.session), 8u);
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 11u, &state));
    ASSERT_EQ(state.history_count, 0u);
    ASSERT_EQ(state.history_bytes, 0u);
    ASSERT_EQ(state.confirmed_snapshot_id, 0u);
    ASSERT_EQ(state.confirmed_tick, 0u);
    ASSERT_EQ(state.next_delta_id, 1u);
    ASSERT_FALSE(state.attempt_pending);
    break_world_session_stats(fixture.session, &after);
    ASSERT_TRUE(memcmp(&before, &after, sizeof(before)) == 0);

    fixture.epoch = break_world_session_stream_epoch(
        TEST_PROTOCOL, break_schema_hash(fixture.schemas), 8u);
    ASSERT_TRUE(publish_attempt(&fixture, 11u, 20u, &recovered));
    ASSERT_EQ(recovered.kind, BREAK_WORLD_DELTA_WIRE_FULL);
    ASSERT_EQ(recovered.delta_id, 1u);
    ASSERT_EQ(recovered.level_generation, 8u);
    ASSERT_EQ(recovered.target_snapshot_id, old_delta.target_snapshot_id);
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 11u, &state));
    ASSERT_EQ(state.history_count, 1u);
    ASSERT_EQ(state.confirmed_snapshot_id, 0u);
    ASSERT_EQ(state.next_delta_id, 2u);
    ASSERT_TRUE(ack_attempt_v2(&fixture, 11u, &recovered, 8u));
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 11u, &state));
    ASSERT_EQ(state.history_count, 0u);
    ASSERT_EQ(state.confirmed_snapshot_id, recovered.target_snapshot_id);

    ASSERT_TRUE(publish_attempt(&fixture, 12u, 30u, &delta));
    ASSERT_EQ(delta.kind, BREAK_WORLD_DELTA_WIRE_DELTA);
    ASSERT_EQ(delta.delta_id, 2u);
    ASSERT_EQ(delta.base_snapshot_id, recovered.target_snapshot_id);
    ASSERT_EQ(delta.level_generation, 8u);
    break_world_session_stats(fixture.session, &after);
    ASSERT_EQ(after.published_full_packets, 2u);
    ASSERT_EQ(after.published_delta_packets, 2u);
    ASSERT_EQ(after.acknowledged_packets, 2u);

    clear_attempt(&delta);
    clear_attempt(&recovered);
    clear_attempt(&old_delta);
    clear_attempt(&initial);
    fixture_dispose(&fixture);
}

TEST(world_session_rebaseline_discards_old_overload_attempt)
{
    Fixture fixture;
    AttemptWire recovered;
    BreakWorldSessionSenderState state;
    BreakNetOwnedMessage outbound;
    u64 outbound_connection = 0u;

    ASSERT_TRUE(fixture_init_scaled(&fixture, 4u, 16384u, 4096u, 64u, 8u, 64u));
    ASSERT_TRUE(set_value(fixture.authoritative, 42u));
    for (usize i = 0u; i < BREAK_NET_OUTBOUND_QUEUE_CAPACITY - 1u; ++i) {
        ASSERT_EQ(break_net_reactor_send(fixture.reactor, 11u,
                                         BREAK_NET_MESSAGE_ID_PING, 1u, "x", 1u),
                  BREAK_NET_SEND_OK);
    }
    ASSERT_EQ(break_world_session_publish(fixture.session, 11u, fixture.authoritative, 10u),
              BREAK_NET_SEND_OVERLOAD);
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 11u, &state));
    ASSERT_TRUE(state.attempt_pending);
    ASSERT_EQ(state.next_delta_id, 2u);

    ASSERT_TRUE(break_world_session_rebaseline(fixture.session, 8u));
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 11u, &state));
    ASSERT_FALSE(state.attempt_pending);
    ASSERT_EQ(state.history_count, 0u);
    ASSERT_EQ(state.confirmed_snapshot_id, 0u);
    ASSERT_EQ(state.next_delta_id, 1u);
    while (break_net_reactor_poll_outbound_for_test(
               fixture.reactor, &outbound_connection, &outbound) == BREAK_NET_EVENT_OK) {
        break_net_message_release(&outbound);
    }
    fixture.epoch = break_world_session_stream_epoch(
        TEST_PROTOCOL, break_schema_hash(fixture.schemas), 8u);
    ASSERT_TRUE(publish_attempt(&fixture, 43u, 20u, &recovered));
    ASSERT_EQ(recovered.kind, BREAK_WORLD_DELTA_WIRE_FULL);
    ASSERT_EQ(recovered.delta_id, 1u);
    ASSERT_EQ(recovered.target_tick, 20u);
    ASSERT_EQ(recovered.level_generation, 8u);
    ASSERT_EQ(break_net_reactor_outbound_count(fixture.reactor), 0u);
    clear_attempt(&recovered);
    fixture_dispose(&fixture);
}

TEST(world_session_rebaseline_rejects_stale_v1_v2_control_collisions)
{
    Fixture fixture;
    AttemptWire old_full;
    AttemptWire new_full;
    AttemptWire delta;
    BreakWorldSessionControl old_ack;
    BreakWorldSessionControl old_need_full;
    BreakWorldSessionSenderState before;
    BreakWorldSessionSenderState after;
    BreakWorldSessionStats stats;

    ASSERT_TRUE(fixture_init(&fixture));
    ASSERT_TRUE(publish_attempt(&fixture, 10u, 10u, &old_full));
    ASSERT_TRUE(break_world_session_rebaseline(fixture.session, 8u));
    fixture.epoch = break_world_session_stream_epoch(
        TEST_PROTOCOL, break_schema_hash(fixture.schemas), 8u);
    ASSERT_TRUE(publish_attempt(&fixture, 10u, 10u, &new_full));
    ASSERT_EQ(old_full.delta_id, 1u);
    ASSERT_EQ(new_full.delta_id, old_full.delta_id);
    ASSERT_EQ(new_full.target_snapshot_id, old_full.target_snapshot_id);
    ASSERT_EQ(new_full.target_tick, old_full.target_tick);
    ASSERT_EQ(old_full.level_generation, TEST_LEVEL);
    ASSERT_EQ(new_full.level_generation, 8u);
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 11u, &before));
    ASSERT_EQ(before.history_count, 1u);
    ASSERT_EQ(before.confirmed_snapshot_id, 0u);

    memset(&old_ack, 0, sizeof(old_ack));
    old_ack.kind = BREAK_WORLD_SESSION_CONTROL_ACK;
    old_ack.delta_id = old_full.delta_id;
    old_ack.target_snapshot_id = old_full.target_snapshot_id;
    old_ack.target_tick = old_full.target_tick;
    old_ack.level_generation = TEST_LEVEL;
    memset(&old_need_full, 0, sizeof(old_need_full));
    old_need_full.kind = BREAK_WORLD_SESSION_CONTROL_NEED_FULL;
    old_need_full.target_snapshot_id = old_full.target_snapshot_id;
    old_need_full.target_tick = old_full.target_tick;
    old_need_full.level_generation = TEST_LEVEL;

    ASSERT_FALSE(send_control_to_session(&fixture, &old_ack));
    ASSERT_FALSE(send_control_to_session(&fixture, &old_need_full));
    ASSERT_FALSE(send_control_v2_to_session(&fixture, 11u, TEST_LEVEL, &old_ack));
    ASSERT_FALSE(send_control_v2_to_session(&fixture, 11u, TEST_LEVEL, &old_need_full));
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 11u, &after));
    ASSERT_TRUE(memcmp(&before, &after, sizeof(before)) == 0);

    ASSERT_TRUE(send_control_v2_to_session(&fixture, 11u, 8u, &old_ack));
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 11u, &after));
    ASSERT_EQ(after.history_count, 0u);
    ASSERT_EQ(after.confirmed_snapshot_id, new_full.target_snapshot_id);
    ASSERT_TRUE(publish_attempt(&fixture, 11u, 20u, &delta));
    ASSERT_EQ(delta.kind, BREAK_WORLD_DELTA_WIRE_DELTA);
    ASSERT_EQ(delta.delta_id, 2u);
    break_world_session_stats(fixture.session, &stats);
    ASSERT_EQ(stats.acknowledged_packets, 1u);
    ASSERT_EQ(stats.published_full_packets, 2u);
    ASSERT_EQ(stats.published_delta_packets, 1u);

    clear_attempt(&delta);
    clear_attempt(&new_full);
    clear_attempt(&old_full);
    fixture_dispose(&fixture);
}

TEST(world_session_rebaseline_multi_connection_ack_is_independent)
{
    Fixture fixture;
    AttemptWire a_full;
    AttemptWire b_full;
    AttemptWire a_delta;
    AttemptWire b_next;
    BreakWorldSessionSenderState a_state;
    BreakWorldSessionSenderState b_state;
    BreakWorldSessionStats stats;

    ASSERT_TRUE(fixture_init(&fixture));
    ASSERT_TRUE(break_world_session_open(fixture.session, 22u));
    ASSERT_TRUE(break_world_session_rebaseline(fixture.session, 8u));
    fixture.epoch = break_world_session_stream_epoch(
        TEST_PROTOCOL, break_schema_hash(fixture.schemas), 8u);
    ASSERT_TRUE(publish_attempt_for_connection(&fixture, 11u, 10u, 10u, &a_full));
    ASSERT_TRUE(publish_attempt_for_connection(&fixture, 22u, 10u, 10u, &b_full));
    ASSERT_EQ(a_full.kind, BREAK_WORLD_DELTA_WIRE_FULL);
    ASSERT_EQ(b_full.kind, BREAK_WORLD_DELTA_WIRE_FULL);
    ASSERT_EQ(a_full.delta_id, 1u);
    ASSERT_EQ(b_full.delta_id, 1u);

    ASSERT_TRUE(ack_attempt_v2(&fixture, 11u, &a_full, 8u));
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 11u, &a_state));
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 22u, &b_state));
    ASSERT_EQ(a_state.history_count, 0u);
    ASSERT_EQ(a_state.confirmed_snapshot_id, a_full.target_snapshot_id);
    ASSERT_EQ(b_state.history_count, 1u);
    ASSERT_EQ(b_state.confirmed_snapshot_id, 0u);

    ASSERT_TRUE(publish_attempt_for_connection(&fixture, 11u, 11u, 20u, &a_delta));
    ASSERT_TRUE(publish_attempt_for_connection(&fixture, 22u, 11u, 20u, &b_next));
    ASSERT_EQ(a_delta.kind, BREAK_WORLD_DELTA_WIRE_DELTA);
    ASSERT_EQ(a_delta.delta_id, 2u);
    ASSERT_EQ(b_next.kind, BREAK_WORLD_DELTA_WIRE_FULL);
    ASSERT_EQ(b_next.delta_id, 2u);
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 22u, &b_state));
    ASSERT_EQ(b_state.confirmed_snapshot_id, 0u);
    ASSERT_EQ(b_state.history_count, 1u);
    break_world_session_stats(fixture.session, &stats);
    ASSERT_EQ(stats.acknowledged_packets, 1u);
    ASSERT_EQ(stats.published_full_packets, 3u);
    ASSERT_EQ(stats.published_delta_packets, 1u);

    clear_attempt(&b_next);
    clear_attempt(&a_delta);
    clear_attempt(&b_full);
    clear_attempt(&a_full);
    fixture_dispose(&fixture);
}

TEST(world_session_control_send_uses_exact_v1_and_v2_wire)
{
    static const u8 expected_v1[BREAK_WORLD_SESSION_CONTROL_WIRE_SIZE] = {
        0x42, 0x52, 0x57, 0x43, 0x01, 0x00, 0x02, 0x00,
        0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    static const u8 expected_v2[BREAK_WORLD_SESSION_CONTROL_WIRE_SIZE_V2] = {
        0x42, 0x52, 0x57, 0x43, 0x02, 0x00, 0x02, 0x00,
        0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    Fixture fixture;
    BreakWorldSessionControl control;
    BreakNetOwnedMessage outbound;
    u64 outbound_connection = 0u;

    ASSERT_EQ(BREAK_WORLD_SESSION_CONTROL_WIRE_SIZE, 32u);
    ASSERT_EQ(BREAK_WORLD_SESSION_CONTROL_WIRE_SIZE_V2, 40u);
    ASSERT_TRUE(fixture_init(&fixture));
    memset(&control, 0, sizeof(control));
    control.kind = BREAK_WORLD_SESSION_CONTROL_ACK;
    control.delta_id = 1u;
    control.target_snapshot_id = 2u;
    control.target_tick = 3u;
    ASSERT_EQ(break_world_session_send_control(fixture.session, 11u, &control),
              BREAK_NET_SEND_OK);
    ASSERT_EQ(break_net_reactor_poll_outbound_for_test(
                  fixture.reactor, &outbound_connection, &outbound), BREAK_NET_EVENT_OK);
    ASSERT_EQ(outbound_connection, 11u);
    ASSERT_EQ(outbound.message_id, BREAK_NET_MESSAGE_ID_WORLD_CONTROL);
    ASSERT_EQ(outbound.protocol_version, 1u);
    ASSERT_EQ(outbound.size, 32u);
    ASSERT_TRUE(memcmp(outbound.data, expected_v1, sizeof(expected_v1)) == 0);
    break_net_message_release(&outbound);

    control.level_generation = TEST_LEVEL;
    ASSERT_EQ(break_world_session_send_control(fixture.session, 11u, &control),
              BREAK_NET_SEND_OK);
    ASSERT_EQ(break_net_reactor_poll_outbound_for_test(
                  fixture.reactor, &outbound_connection, &outbound), BREAK_NET_EVENT_OK);
    ASSERT_EQ(outbound.protocol_version, 1u);
    ASSERT_EQ(outbound.size, 32u);
    ASSERT_TRUE(memcmp(outbound.data, expected_v1, sizeof(expected_v1)) == 0);
    break_net_message_release(&outbound);
    control.level_generation = 8u;
    ASSERT_EQ(break_world_session_send_control(fixture.session, 11u, &control),
              BREAK_NET_SEND_INVALID);
    ASSERT_EQ(break_net_reactor_outbound_count(fixture.reactor), 0u);

    ASSERT_TRUE(break_world_session_rebaseline(fixture.session, 8u));
    control.level_generation = 0u;
    ASSERT_EQ(break_world_session_send_control(fixture.session, 11u, &control),
              BREAK_NET_SEND_INVALID);
    control.level_generation = TEST_LEVEL;
    ASSERT_EQ(break_world_session_send_control(fixture.session, 11u, &control),
              BREAK_NET_SEND_INVALID);
    control.level_generation = 9u;
    ASSERT_EQ(break_world_session_send_control(fixture.session, 11u, &control),
              BREAK_NET_SEND_INVALID);
    ASSERT_EQ(break_net_reactor_outbound_count(fixture.reactor), 0u);
    control.level_generation = 8u;
    ASSERT_EQ(break_world_session_send_control(fixture.session, 11u, &control),
              BREAK_NET_SEND_OK);
    ASSERT_EQ(break_net_reactor_poll_outbound_for_test(
                  fixture.reactor, &outbound_connection, &outbound), BREAK_NET_EVENT_OK);
    ASSERT_EQ(outbound.message_id, BREAK_NET_MESSAGE_ID_WORLD_CONTROL);
    ASSERT_EQ(outbound.protocol_version, 2u);
    ASSERT_EQ(outbound.size, 40u);
    ASSERT_TRUE(memcmp(outbound.data, expected_v2, sizeof(expected_v2)) == 0);
    break_net_message_release(&outbound);
    fixture_dispose(&fixture);
}

TEST(world_session_control_rejects_version_length_and_level_mismatch)
{
    Fixture fixture;
    AttemptWire current;
    BreakWorldSessionControl control;
    BreakWorldSessionSenderState state;

    ASSERT_TRUE(fixture_init(&fixture));
    ASSERT_TRUE(break_world_session_rebaseline(fixture.session, 8u));
    fixture.epoch = break_world_session_stream_epoch(
        TEST_PROTOCOL, break_schema_hash(fixture.schemas), 8u);
    ASSERT_TRUE(publish_attempt(&fixture, 10u, 10u, &current));
    memset(&control, 0, sizeof(control));
    control.kind = BREAK_WORLD_SESSION_CONTROL_ACK;
    control.delta_id = current.delta_id;
    control.target_snapshot_id = current.target_snapshot_id;
    control.target_tick = current.target_tick;
    control.level_generation = 8u;

    ASSERT_FALSE(send_control_version_to_session(
        &fixture, 11u, 1u, 2u, BREAK_WORLD_SESSION_CONTROL_WIRE_SIZE_V2, 8u, &control));
    ASSERT_FALSE(send_control_version_to_session(
        &fixture, 11u, 3u, 2u, BREAK_WORLD_SESSION_CONTROL_WIRE_SIZE_V2, 8u, &control));
    ASSERT_FALSE(send_control_version_to_session(
        &fixture, 11u, 2u, 1u, BREAK_WORLD_SESSION_CONTROL_WIRE_SIZE_V2, 8u, &control));
    ASSERT_FALSE(send_control_version_to_session(
        &fixture, 11u, 2u, 3u, BREAK_WORLD_SESSION_CONTROL_WIRE_SIZE_V2, 8u, &control));
    ASSERT_FALSE(send_control_version_to_session(&fixture, 11u, 2u, 2u, 31u, 8u, &control));
    ASSERT_FALSE(send_control_version_to_session(&fixture, 11u, 2u, 2u, 32u, 8u, &control));
    ASSERT_FALSE(send_control_version_to_session(&fixture, 11u, 2u, 2u, 39u, 8u, &control));
    ASSERT_FALSE(send_control_version_to_session(&fixture, 11u, 2u, 2u, 41u, 8u, &control));
    ASSERT_FALSE(send_control_v2_to_session(&fixture, 11u, 0u, &control));
    ASSERT_FALSE(send_control_v2_to_session(&fixture, 11u, TEST_LEVEL, &control));
    ASSERT_FALSE(send_control_v2_to_session(&fixture, 11u, 9u, &control));
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 11u, &state));
    ASSERT_EQ(state.history_count, 1u);
    ASSERT_EQ(state.confirmed_snapshot_id, 0u);
    ASSERT_TRUE(send_control_v2_to_session(&fixture, 11u, 8u, &control));
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 11u, &state));
    ASSERT_EQ(state.history_count, 0u);
    ASSERT_EQ(state.confirmed_snapshot_id, current.target_snapshot_id);
    clear_attempt(&current);
    fixture_dispose(&fixture);
}

TEST(world_session_rebaseline_close_reopen_keeps_level_and_clears_connection)
{
    Fixture fixture;
    AttemptWire initial;
    AttemptWire current;
    AttemptWire reopened;
    BreakWorldSessionControl control;
    BreakWorldSessionSenderState state;

    ASSERT_TRUE(fixture_init(&fixture));
    ASSERT_TRUE(publish_attempt(&fixture, 10u, 10u, &initial));
    ASSERT_TRUE(break_world_session_rebaseline(fixture.session, 8u));
    fixture.epoch = break_world_session_stream_epoch(
        TEST_PROTOCOL, break_schema_hash(fixture.schemas), 8u);
    ASSERT_TRUE(publish_attempt(&fixture, 10u, 10u, &current));
    ASSERT_EQ(current.delta_id, 1u);
    ASSERT_TRUE(break_world_session_close(fixture.session, 11u));
    ASSERT_EQ(break_world_session_level_generation(fixture.session), 8u);
    ASSERT_FALSE(break_world_session_sender_state(fixture.session, 11u, &state));
    ASSERT_EQ(state.history_count, 0u);
    ASSERT_EQ(state.next_delta_id, 0u);
    ASSERT_TRUE(break_world_session_open(fixture.session, 11u));
    ASSERT_EQ(break_world_session_level_generation(fixture.session), 8u);
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 11u, &state));
    ASSERT_EQ(state.history_count, 0u);
    ASSERT_EQ(state.history_bytes, 0u);
    ASSERT_EQ(state.confirmed_snapshot_id, 0u);
    ASSERT_EQ(state.next_delta_id, 1u);
    ASSERT_FALSE(state.attempt_pending);
    ASSERT_FALSE(break_world_session_poll_control(fixture.session, 11u, &control));
    ASSERT_TRUE(publish_attempt(&fixture, 11u, 20u, &reopened));
    ASSERT_EQ(reopened.kind, BREAK_WORLD_DELTA_WIRE_FULL);
    ASSERT_EQ(reopened.delta_id, 1u);
    ASSERT_EQ(reopened.level_generation, 8u);
    clear_attempt(&reopened);
    clear_attempt(&current);
    clear_attempt(&initial);
    fixture_dispose(&fixture);
}

TEST(world_session_shared_snapshot_fanout_uses_per_connection_base)
{
    Fixture fixture;
    BreakWorldSnapshot *first;
    BreakWorldSnapshot *second;
    BreakWorldSnapshot *third;
    AttemptWire a_first;
    AttemptWire b_first;
    AttemptWire a_second;
    AttemptWire b_second;
    AttemptWire a_third;
    AttemptWire b_third;
    BreakWorldSessionSenderState a_state;
    BreakWorldSessionSenderState b_state;
    u64 first_id;
    u64 second_id;
    u64 third_id;

    ASSERT_TRUE(fixture_init(&fixture));
    ASSERT_TRUE(break_world_session_open(fixture.session, 22u));
    ASSERT_TRUE(set_value(fixture.authoritative, 10u));
    first = break_world_snapshot_build(fixture.authoritative, fixture.schemas, 10u);
    ASSERT_NOT_NULL(first);
    first_id = break_world_snapshot_id(first);
    ASSERT_TRUE(publish_snapshot_attempt_for_connection(&fixture, 11u, first, TEST_LEVEL,
                                                        &a_first));
    ASSERT_TRUE(publish_snapshot_attempt_for_connection(&fixture, 22u, first, TEST_LEVEL,
                                                        &b_first));
    ASSERT_EQ(a_first.kind, BREAK_WORLD_DELTA_WIRE_FULL);
    ASSERT_EQ(b_first.kind, BREAK_WORLD_DELTA_WIRE_FULL);
    ASSERT_EQ(a_first.target_snapshot_id, first_id);
    ASSERT_EQ(b_first.target_snapshot_id, first_id);
    ASSERT_EQ(a_first.target_tick, 10u);
    ASSERT_EQ(b_first.target_tick, 10u);
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 11u, &a_state));
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 22u, &b_state));
    ASSERT_EQ(a_state.history_count, 1u);
    ASSERT_EQ(b_state.history_count, 1u);
    ASSERT_EQ(a_state.history_bytes, a_first.payload_size);
    ASSERT_EQ(b_state.history_bytes, b_first.payload_size);
    ASSERT_EQ(a_state.confirmed_snapshot_id, 0u);
    ASSERT_EQ(b_state.confirmed_snapshot_id, 0u);

    break_world_snapshot_release(first);
    ASSERT_TRUE(ack_attempt(&fixture, &a_first));
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 11u, &a_state));
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 22u, &b_state));
    ASSERT_EQ(a_state.history_count, 0u);
    ASSERT_EQ(a_state.confirmed_snapshot_id, first_id);
    ASSERT_EQ(a_state.confirmed_tick, 10u);
    ASSERT_EQ(b_state.history_count, 1u);
    ASSERT_EQ(b_state.history_bytes, b_first.payload_size);
    ASSERT_EQ(b_state.confirmed_snapshot_id, 0u);

    ASSERT_TRUE(set_value(fixture.authoritative, 11u));
    second = break_world_snapshot_build(fixture.authoritative, fixture.schemas, 20u);
    ASSERT_NOT_NULL(second);
    second_id = break_world_snapshot_id(second);
    ASSERT_TRUE(publish_snapshot_attempt_for_connection(&fixture, 11u, second, TEST_LEVEL,
                                                        &a_second));
    ASSERT_TRUE(publish_snapshot_attempt_for_connection(&fixture, 22u, second, TEST_LEVEL,
                                                        &b_second));
    ASSERT_EQ(a_second.kind, BREAK_WORLD_DELTA_WIRE_DELTA);
    ASSERT_EQ(a_second.base_snapshot_id, first_id);
    ASSERT_EQ(a_second.base_tick, 10u);
    ASSERT_EQ(a_second.target_snapshot_id, second_id);
    ASSERT_EQ(a_second.target_tick, 20u);
    ASSERT_EQ(b_second.kind, BREAK_WORLD_DELTA_WIRE_FULL);
    ASSERT_EQ(b_second.base_snapshot_id, 0u);
    ASSERT_EQ(b_second.target_snapshot_id, second_id);
    ASSERT_EQ(b_second.target_tick, 20u);
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 11u, &a_state));
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 22u, &b_state));
    ASSERT_EQ(a_state.history_count, 1u);
    ASSERT_EQ(a_state.history_bytes, a_second.payload_size);
    ASSERT_EQ(a_state.confirmed_snapshot_id, first_id);
    ASSERT_EQ(b_state.history_count, 1u);
    ASSERT_EQ(b_state.history_bytes, b_second.payload_size);
    ASSERT_EQ(b_state.confirmed_snapshot_id, 0u);

    break_world_snapshot_release(second);
    ASSERT_TRUE(ack_attempt(&fixture, &a_second));
    ASSERT_TRUE(ack_attempt_for_connection(&fixture, 22u, &b_second, 1u, 0u));
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 11u, &a_state));
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 22u, &b_state));
    ASSERT_EQ(a_state.confirmed_snapshot_id, second_id);
    ASSERT_EQ(b_state.confirmed_snapshot_id, second_id);
    ASSERT_EQ(a_state.confirmed_tick, 20u);
    ASSERT_EQ(b_state.confirmed_tick, 20u);
    ASSERT_EQ(a_state.history_count, 0u);
    ASSERT_EQ(b_state.history_count, 0u);

    ASSERT_TRUE(set_value(fixture.authoritative, 12u));
    third = break_world_snapshot_build(fixture.authoritative, fixture.schemas, 30u);
    ASSERT_NOT_NULL(third);
    third_id = break_world_snapshot_id(third);
    ASSERT_TRUE(publish_snapshot_attempt_for_connection(&fixture, 11u, third, TEST_LEVEL,
                                                        &a_third));
    ASSERT_TRUE(publish_snapshot_attempt_for_connection(&fixture, 22u, third, TEST_LEVEL,
                                                        &b_third));
    ASSERT_EQ(a_third.kind, BREAK_WORLD_DELTA_WIRE_DELTA);
    ASSERT_EQ(b_third.kind, BREAK_WORLD_DELTA_WIRE_DELTA);
    ASSERT_EQ(a_third.base_snapshot_id, second_id);
    ASSERT_EQ(b_third.base_snapshot_id, second_id);
    ASSERT_EQ(a_third.base_tick, 20u);
    ASSERT_EQ(b_third.base_tick, 20u);
    ASSERT_EQ(a_third.target_snapshot_id, third_id);
    ASSERT_EQ(b_third.target_snapshot_id, third_id);
    ASSERT_EQ(a_third.target_tick, 30u);
    ASSERT_EQ(b_third.target_tick, 30u);
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 11u, &a_state));
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 22u, &b_state));
    ASSERT_EQ(a_state.history_count, 1u);
    ASSERT_EQ(b_state.history_count, 1u);
    ASSERT_EQ(a_state.history_bytes, a_third.payload_size);
    ASSERT_EQ(b_state.history_bytes, b_third.payload_size);
    ASSERT_EQ(a_state.confirmed_snapshot_id, second_id);
    ASSERT_EQ(b_state.confirmed_snapshot_id, second_id);

    break_world_snapshot_release(third);
    ASSERT_TRUE(ack_attempt(&fixture, &a_third));
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 11u, &a_state));
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 22u, &b_state));
    ASSERT_EQ(a_state.history_count, 0u);
    ASSERT_EQ(a_state.confirmed_snapshot_id, third_id);
    ASSERT_EQ(b_state.history_count, 1u);
    ASSERT_EQ(b_state.confirmed_snapshot_id, second_id);
    ASSERT_TRUE(ack_attempt_for_connection(&fixture, 22u, &b_third, 1u, 0u));
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 22u, &b_state));
    ASSERT_EQ(b_state.history_count, 0u);
    ASSERT_EQ(b_state.confirmed_snapshot_id, third_id);

    clear_attempt(&b_third);
    clear_attempt(&a_third);
    clear_attempt(&b_second);
    clear_attempt(&a_second);
    clear_attempt(&b_first);
    clear_attempt(&a_first);
    fixture_dispose(&fixture);
}

TEST(world_session_snapshot_overload_is_independent_and_ignores_new_target)
{
    Fixture fixture;
    BreakWorldSnapshot *first;
    BreakWorldSnapshot *other;
    AttemptWire a_resumed;
    AttemptWire b_full;
    BreakWorldSessionSenderState a_state;
    BreakWorldSessionSenderState b_state;
    BreakNetOwnedMessage outbound;
    u64 outbound_connection = 0u;
    u64 first_id;
    u64 other_id;
    usize drained = 0u;

    ASSERT_TRUE(fixture_init(&fixture));
    ASSERT_TRUE(break_world_session_open(fixture.session, 22u));
    ASSERT_TRUE(set_value(fixture.authoritative, 42u));
    first = break_world_snapshot_build(fixture.authoritative, fixture.schemas, 10u);
    ASSERT_NOT_NULL(first);
    first_id = break_world_snapshot_id(first);
    for (usize i = 0u; i < BREAK_NET_OUTBOUND_QUEUE_CAPACITY; ++i) {
        ASSERT_EQ(break_net_reactor_send(fixture.reactor, 11u,
                                         BREAK_NET_MESSAGE_ID_PING, 1u, "x", 1u),
                  BREAK_NET_SEND_OK);
    }
    ASSERT_EQ(break_world_session_publish_snapshot(fixture.session, 11u, first, TEST_LEVEL),
              BREAK_NET_SEND_OVERLOAD);
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 11u, &a_state));
    ASSERT_TRUE(a_state.attempt_pending);
    ASSERT_EQ(a_state.next_delta_id, 2u);
    ASSERT_EQ(a_state.history_count, 0u);
    while (break_net_reactor_poll_outbound_for_test(
               fixture.reactor, &outbound_connection, &outbound) == BREAK_NET_EVENT_OK) {
        ASSERT_EQ(outbound.message_id, BREAK_NET_MESSAGE_ID_PING);
        break_net_message_release(&outbound);
        drained++;
    }
    ASSERT_EQ(drained, (usize)BREAK_NET_OUTBOUND_QUEUE_CAPACITY);

    ASSERT_TRUE(publish_snapshot_attempt_for_connection(&fixture, 22u, first, TEST_LEVEL,
                                                        &b_full));
    ASSERT_EQ(b_full.kind, BREAK_WORLD_DELTA_WIRE_FULL);
    ASSERT_EQ(b_full.target_snapshot_id, first_id);
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 11u, &a_state));
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 22u, &b_state));
    ASSERT_TRUE(a_state.attempt_pending);
    ASSERT_EQ(a_state.history_count, 0u);
    ASSERT_FALSE(b_state.attempt_pending);
    ASSERT_EQ(b_state.history_count, 1u);

    ASSERT_TRUE(set_value(fixture.authoritative, 99u));
    other = break_world_snapshot_build(fixture.authoritative, fixture.schemas, 30u);
    ASSERT_NOT_NULL(other);
    other_id = break_world_snapshot_id(other);
    break_world_snapshot_release(first);
    ASSERT_EQ(break_world_session_publish_snapshot(fixture.session, 11u, other, 8u),
              BREAK_NET_SEND_OK);
    ASSERT_TRUE(collect_attempt_for_connection(&fixture, 11u, &a_resumed));
    break_world_snapshot_release(other);
    ASSERT_EQ(a_resumed.kind, BREAK_WORLD_DELTA_WIRE_FULL);
    ASSERT_EQ(a_resumed.delta_id, b_full.delta_id);
    ASSERT_EQ(a_resumed.target_snapshot_id, first_id);
    ASSERT_NEQ(a_resumed.target_snapshot_id, other_id);
    ASSERT_EQ(a_resumed.target_tick, 10u);
    ASSERT_EQ(a_resumed.payload_size, b_full.payload_size);
    ASSERT_TRUE(memcmp(a_resumed.payload, b_full.payload, b_full.payload_size) == 0);

    ASSERT_TRUE(ack_attempt(&fixture, &a_resumed));
    ASSERT_TRUE(ack_attempt_for_connection(&fixture, 22u, &b_full, 1u, 0u));
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 11u, &a_state));
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 22u, &b_state));
    ASSERT_EQ(a_state.confirmed_snapshot_id, first_id);
    ASSERT_EQ(b_state.confirmed_snapshot_id, first_id);
    ASSERT_EQ(a_state.confirmed_tick, 10u);
    ASSERT_EQ(b_state.confirmed_tick, 10u);
    ASSERT_EQ(a_state.history_count, 0u);
    ASSERT_EQ(b_state.history_count, 0u);

    clear_attempt(&a_resumed);
    clear_attempt(&b_full);
    fixture_dispose(&fixture);
}

TEST(world_session_snapshot_invalid_input_is_atomic_and_preserves_delta_id)
{
    Fixture fixture;
    BreakComponentSchemaRegistry *other_schemas;
    BreakComponentSchema other_schema;
    BreakWorldSnapshot *initial;
    BreakWorldSnapshot *wrong_schema;
    BreakWorldSnapshot *zero_tick;
    BreakWorldSnapshot *older;
    BreakWorldSnapshot *second;
    AttemptWire initial_attempt;
    AttemptWire second_attempt;
    BreakWorldSessionSenderState before;
    BreakWorldSessionSenderState after;
    BreakWorldSessionStats stats_before;
    BreakWorldSessionStats stats_after;
    u64 initial_id;
    u64 second_id;

    ASSERT_TRUE(fixture_init(&fixture));
    ASSERT_TRUE(set_value(fixture.authoritative, 10u));
    initial = break_world_snapshot_build(fixture.authoritative, fixture.schemas, 10u);
    ASSERT_NOT_NULL(initial);
    initial_id = break_world_snapshot_id(initial);
    ASSERT_TRUE(publish_snapshot_attempt_for_connection(&fixture, 11u, initial, TEST_LEVEL,
                                                        &initial_attempt));
    ASSERT_TRUE(ack_attempt(&fixture, &initial_attempt));
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 11u, &before));
    ASSERT_EQ(before.confirmed_snapshot_id, initial_id);
    ASSERT_EQ(before.next_delta_id, 2u);
    break_world_session_stats(fixture.session, &stats_before);

    other_schemas = break_schema_registry_create();
    ASSERT_NOT_NULL(other_schemas);
    memset(&other_schema, 0, sizeof(other_schema));
    other_schema.component_id = TEST_COMPONENT;
    other_schema.version = 2u;
    other_schema.size = sizeof(Value);
    other_schema.alignment = _Alignof(Value);
    other_schema.flags = BREAK_SCHEMA_FLAG_DETERMINISTIC_POD | BREAK_SCHEMA_FLAG_RAW_BYTES;
    ASSERT_EQ(break_schema_register(other_schemas, &other_schema), BREAK_SCHEMA_OK);
    ASSERT_NEQ(break_schema_hash(other_schemas), break_schema_hash(fixture.schemas));
    wrong_schema = break_world_snapshot_build(fixture.authoritative, other_schemas, 20u);
    zero_tick = break_world_snapshot_build(fixture.authoritative, fixture.schemas, 0u);
    older = break_world_snapshot_build(fixture.authoritative, fixture.schemas, 9u);
    ASSERT_NOT_NULL(wrong_schema);
    ASSERT_NOT_NULL(zero_tick);
    ASSERT_NOT_NULL(older);
    ASSERT_TRUE(set_value(fixture.authoritative, 11u));
    second = break_world_snapshot_build(fixture.authoritative, fixture.schemas, 20u);
    ASSERT_NOT_NULL(second);
    second_id = break_world_snapshot_id(second);

    ASSERT_TRUE(invalid_snapshot_publish_preserves_state(&fixture, 11u, NULL, TEST_LEVEL,
                                                         &before, &stats_before));
    ASSERT_TRUE(invalid_snapshot_publish_preserves_state(&fixture, 11u, wrong_schema,
                                                         TEST_LEVEL, &before, &stats_before));
    ASSERT_TRUE(invalid_snapshot_publish_preserves_state(&fixture, 11u, zero_tick, TEST_LEVEL,
                                                         &before, &stats_before));
    ASSERT_TRUE(invalid_snapshot_publish_preserves_state(&fixture, 11u, initial, TEST_LEVEL,
                                                         &before, &stats_before));
    ASSERT_TRUE(invalid_snapshot_publish_preserves_state(&fixture, 11u, older, TEST_LEVEL,
                                                         &before, &stats_before));
    ASSERT_TRUE(invalid_snapshot_publish_preserves_state(&fixture, 11u, second, 0u, &before,
                                                         &stats_before));
    ASSERT_TRUE(invalid_snapshot_publish_preserves_state(&fixture, 11u, second, 8u, &before,
                                                         &stats_before));
    ASSERT_EQ(break_world_snapshot_tick(zero_tick), 0u);
    ASSERT_EQ(break_world_snapshot_tick(older), 9u);
    ASSERT_EQ(break_world_snapshot_id(second), second_id);

    ASSERT_TRUE(publish_snapshot_attempt_for_connection(&fixture, 11u, second, TEST_LEVEL,
                                                        &second_attempt));
    ASSERT_EQ(second_attempt.kind, BREAK_WORLD_DELTA_WIRE_DELTA);
    ASSERT_EQ(second_attempt.delta_id, 2u);
    ASSERT_EQ(second_attempt.base_snapshot_id, initial_id);
    ASSERT_EQ(second_attempt.base_tick, 10u);
    ASSERT_EQ(second_attempt.target_snapshot_id, second_id);
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 11u, &before));
    ASSERT_EQ(before.next_delta_id, 3u);
    ASSERT_EQ(before.history_count, 1u);
    ASSERT_EQ(before.confirmed_snapshot_id, initial_id);
    break_world_session_stats(fixture.session, &stats_before);
    ASSERT_TRUE(invalid_snapshot_publish_preserves_state(&fixture, 11u, second, TEST_LEVEL,
                                                         &before, &stats_before));
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 11u, &after));
    break_world_session_stats(fixture.session, &stats_after);
    ASSERT_EQ(after.next_delta_id, 3u);
    ASSERT_EQ(after.history_count, 1u);
    ASSERT_EQ(after.confirmed_snapshot_id, initial_id);

    clear_attempt(&second_attempt);
    clear_attempt(&initial_attempt);
    break_world_snapshot_release(second);
    break_world_snapshot_release(older);
    break_world_snapshot_release(zero_tick);
    break_world_snapshot_release(wrong_schema);
    break_world_snapshot_release(initial);
    break_schema_registry_destroy(other_schemas);
    fixture_dispose(&fixture);
}

TEST(world_session_snapshot_rebaseline_rejects_old_lease_and_refills_both)
{
    Fixture fixture;
    BreakWorldSnapshot *old_snapshot;
    BreakWorldSnapshot *current;
    AttemptWire a_old;
    AttemptWire b_old;
    AttemptWire a_current;
    AttemptWire b_current;
    BreakWorldSessionSenderState a_reset;
    BreakWorldSessionSenderState b_reset;
    BreakWorldSessionSenderState a_state;
    BreakWorldSessionSenderState b_state;
    BreakWorldSessionStats stats_reset;
    const void *bytes = NULL;
    usize size = 0u;
    Value old_value;
    u64 old_id;
    u64 current_id;

    ASSERT_TRUE(fixture_init(&fixture));
    ASSERT_TRUE(break_world_session_open(fixture.session, 22u));
    ASSERT_TRUE(set_value(fixture.authoritative, 10u));
    old_snapshot = break_world_snapshot_build(fixture.authoritative, fixture.schemas, 10u);
    ASSERT_NOT_NULL(old_snapshot);
    old_id = break_world_snapshot_id(old_snapshot);
    ASSERT_TRUE(publish_snapshot_attempt_for_connection(&fixture, 11u, old_snapshot,
                                                        TEST_LEVEL, &a_old));
    ASSERT_TRUE(publish_snapshot_attempt_for_connection(&fixture, 22u, old_snapshot,
                                                        TEST_LEVEL, &b_old));
    ASSERT_TRUE(ack_attempt(&fixture, &a_old));
    ASSERT_TRUE(break_world_session_rebaseline(fixture.session, 8u));
    fixture.epoch = break_world_session_stream_epoch(
        TEST_PROTOCOL, break_schema_hash(fixture.schemas), 8u);
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 11u, &a_reset));
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 22u, &b_reset));
    ASSERT_EQ(a_reset.next_delta_id, 1u);
    ASSERT_EQ(b_reset.next_delta_id, 1u);
    ASSERT_EQ(a_reset.history_count, 0u);
    ASSERT_EQ(b_reset.history_count, 0u);
    ASSERT_EQ(a_reset.confirmed_snapshot_id, 0u);
    ASSERT_EQ(b_reset.confirmed_snapshot_id, 0u);
    break_world_session_stats(fixture.session, &stats_reset);

    ASSERT_TRUE(break_world_snapshot_component_bytes(old_snapshot, (Entity){1u, 1u},
                                                      TEST_COMPONENT, &bytes, &size));
    ASSERT_EQ(size, sizeof(Value));
    memcpy(&old_value, bytes, sizeof(old_value));
    ASSERT_EQ(old_value.value, 10u);
    ASSERT_EQ(break_world_snapshot_id(old_snapshot), old_id);
    ASSERT_EQ(break_world_snapshot_tick(old_snapshot), 10u);
    ASSERT_TRUE(invalid_snapshot_publish_preserves_state(&fixture, 11u, old_snapshot,
                                                         TEST_LEVEL, &a_reset, &stats_reset));
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 22u, &b_state));
    ASSERT_TRUE(memcmp(&b_reset, &b_state, sizeof(b_state)) == 0);

    ASSERT_TRUE(set_value(fixture.authoritative, 20u));
    current = break_world_snapshot_build(fixture.authoritative, fixture.schemas, 5u);
    ASSERT_NOT_NULL(current);
    current_id = break_world_snapshot_id(current);
    ASSERT_TRUE(publish_snapshot_attempt_for_connection(&fixture, 11u, current, 8u,
                                                        &a_current));
    ASSERT_TRUE(publish_snapshot_attempt_for_connection(&fixture, 22u, current, 8u,
                                                        &b_current));
    ASSERT_EQ(a_current.kind, BREAK_WORLD_DELTA_WIRE_FULL);
    ASSERT_EQ(b_current.kind, BREAK_WORLD_DELTA_WIRE_FULL);
    ASSERT_EQ(a_current.delta_id, 1u);
    ASSERT_EQ(b_current.delta_id, 1u);
    ASSERT_EQ(a_current.level_generation, 8u);
    ASSERT_EQ(b_current.level_generation, 8u);
    ASSERT_EQ(a_current.target_snapshot_id, current_id);
    ASSERT_EQ(b_current.target_snapshot_id, current_id);
    ASSERT_EQ(a_current.target_tick, 5u);
    ASSERT_EQ(b_current.target_tick, 5u);
    break_world_snapshot_release(current);

    ASSERT_TRUE(ack_attempt_v2(&fixture, 11u, &a_current, 8u));
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 11u, &a_state));
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 22u, &b_state));
    ASSERT_EQ(a_state.history_count, 0u);
    ASSERT_EQ(a_state.confirmed_snapshot_id, current_id);
    ASSERT_EQ(a_state.confirmed_tick, 5u);
    ASSERT_EQ(b_state.history_count, 1u);
    ASSERT_EQ(b_state.history_bytes, b_current.payload_size);
    ASSERT_EQ(b_state.confirmed_snapshot_id, 0u);
    ASSERT_TRUE(ack_attempt_v2(&fixture, 22u, &b_current, 8u));
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, 22u, &b_state));
    ASSERT_EQ(b_state.history_count, 0u);
    ASSERT_EQ(b_state.confirmed_snapshot_id, current_id);
    ASSERT_EQ(b_state.confirmed_tick, 5u);

    bytes = NULL;
    size = 0u;
    ASSERT_TRUE(break_world_snapshot_component_bytes(old_snapshot, (Entity){1u, 1u},
                                                      TEST_COMPONENT, &bytes, &size));
    ASSERT_EQ(size, sizeof(Value));
    memcpy(&old_value, bytes, sizeof(old_value));
    ASSERT_EQ(old_value.value, 10u);
    break_world_snapshot_release(old_snapshot);
    clear_attempt(&b_current);
    clear_attempt(&a_current);
    clear_attempt(&b_old);
    clear_attempt(&a_old);
    fixture_dispose(&fixture);
}

TEST_MAIN_BEGIN()
    RUN_TEST(world_session_need_full_is_rate_limited_and_control_wire_has_last_good);
    RUN_TEST(world_session_ack_trims_history_and_need_full_publishes_fresh_full);
    RUN_TEST(world_session_ack_after_need_full_does_not_reuse_unconfirmed_baseline);
    RUN_TEST(world_session_history_count_and_byte_limits_fall_back_to_full);
    RUN_TEST(world_session_packet_limit_rejects_without_allocating_history);
    RUN_TEST(world_session_fragment_count_invalid_releases_attempt);
    RUN_TEST(world_session_overload_resumes_same_immutable_attempt);
    RUN_TEST(world_session_reconnect_clears_sender_receiver_and_rate_state);
    RUN_TEST(world_session_rebaseline_resets_sender_and_requires_current_ack);
    RUN_TEST(world_session_rebaseline_discards_old_overload_attempt);
    RUN_TEST(world_session_rebaseline_rejects_stale_v1_v2_control_collisions);
    RUN_TEST(world_session_rebaseline_multi_connection_ack_is_independent);
    RUN_TEST(world_session_control_send_uses_exact_v1_and_v2_wire);
    RUN_TEST(world_session_control_rejects_version_length_and_level_mismatch);
    RUN_TEST(world_session_rebaseline_close_reopen_keeps_level_and_clears_connection);
    RUN_TEST(world_session_shared_snapshot_fanout_uses_per_connection_base);
    RUN_TEST(world_session_snapshot_overload_is_independent_and_ignores_new_target);
    RUN_TEST(world_session_snapshot_invalid_input_is_atomic_and_preserves_delta_id);
    RUN_TEST(world_session_snapshot_rebaseline_rejects_old_lease_and_refills_both);
TEST_MAIN_END()
