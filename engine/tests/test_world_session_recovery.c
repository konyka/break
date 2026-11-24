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
    u64 target_snapshot_id;
    u64 target_tick;
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
    config.bridge.max_connections = 1u;
    config.bridge.stream_capacity = 4u;
    config.bridge.max_pending_bytes_per_connection = 8192u;
    config.bridge.max_total_pending_bytes = 8192u;
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

static bool collect_attempt(Fixture *fixture, AttemptWire *out)
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
        if (outbound_connection != 11u ||
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
    out->target_snapshot_id = decoded.target_snapshot_id;
    out->target_tick = decoded.target_tick;
    break_world_delta_wire_clear(&decoded);
    return true;
}

static void clear_attempt(AttemptWire *attempt)
{
    break_replication_reassembly_free(attempt->payload);
    memset(attempt, 0, sizeof(*attempt));
}

static bool publish_attempt(Fixture *fixture, u32 value, u64 tick, AttemptWire *out)
{
    if (!set_value(fixture->authoritative, value) ||
        break_world_session_publish(fixture->session, 11u, fixture->authoritative, tick) !=
            BREAK_NET_SEND_OK) {
        return false;
    }
    return collect_attempt(fixture, out);
}

static bool send_control_to_session(Fixture *fixture,
                                    const BreakWorldSessionControl *control)
{
    u8 payload[BREAK_WORLD_SESSION_CONTROL_WIRE_SIZE];
    BreakNetOwnedMessage message;
    memset(payload, 0, sizeof(payload));
    memcpy(payload, "BRWC", 4u);
    put16(payload + 4u, 1u);
    put16(payload + 6u, (u16)control->kind);
    put64(payload + 8u, control->delta_id);
    put64(payload + 16u, control->target_snapshot_id);
    put64(payload + 24u, control->target_tick);
    memset(&message, 0, sizeof(message));
    message.message_id = BREAK_NET_MESSAGE_ID_WORLD_CONTROL;
    message.protocol_version = 1u;
    message.sequence = 1u;
    message.data = payload;
    message.size = sizeof(payload);
    return break_world_session_handle_control(11u, &message, fixture->session);
}

static bool ack_attempt(Fixture *fixture, const AttemptWire *attempt)
{
    BreakWorldSessionControl control;
    memset(&control, 0, sizeof(control));
    control.kind = BREAK_WORLD_SESSION_CONTROL_ACK;
    control.delta_id = attempt->delta_id;
    control.target_snapshot_id = attempt->target_snapshot_id;
    control.target_tick = attempt->target_tick;
    return send_control_to_session(fixture, &control);
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

TEST_MAIN_BEGIN()
    RUN_TEST(world_session_need_full_is_rate_limited_and_control_wire_has_last_good);
    RUN_TEST(world_session_ack_trims_history_and_need_full_publishes_fresh_full);
    RUN_TEST(world_session_ack_after_need_full_does_not_reuse_unconfirmed_baseline);
    RUN_TEST(world_session_history_count_and_byte_limits_fall_back_to_full);
    RUN_TEST(world_session_packet_limit_rejects_without_allocating_history);
    RUN_TEST(world_session_fragment_count_invalid_releases_attempt);
    RUN_TEST(world_session_overload_resumes_same_immutable_attempt);
    RUN_TEST(world_session_reconnect_clears_sender_receiver_and_rate_state);
TEST_MAIN_END()
