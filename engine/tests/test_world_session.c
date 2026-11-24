#include "test_framework.h"

#include <ecs/world_session.h>
#include <network/break_net_message_registry.h>
#include <network/break_replication_wire.h>

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
    u64 now;
    u64 epoch;
} Fixture;

static u64 test_clock(void *user)
{
    return *(const u64 *)user;
}

static BreakWorldSessionConfig test_config(Fixture *fixture)
{
    BreakWorldSessionConfig config;
    memset(&config, 0, sizeof(config));
    config.schemas = fixture->schemas;
    config.protocol_version = TEST_PROTOCOL;
    config.level_generation = TEST_LEVEL;
    config.bridge.max_connections = 2u;
    config.bridge.stream_capacity = 4u;
    config.bridge.max_pending_bytes_per_connection = 4096u;
    config.bridge.max_total_pending_bytes = 8192u;
    config.bridge.max_fragment_bytes = 64u;
    config.bridge.max_fragment_count = 64u;
    config.bridge.completion_capacity = 8u;
    config.bridge.max_completion_packet_bytes = 4096u;
    config.bridge.max_completion_queue_bytes = 8192u;
    config.bridge.clock = test_clock;
    config.bridge.clock_user = &fixture->now;
    return config;
}

static bool add_value(World *world, Entity entity, u32 value)
{
    Value *component = (Value *)world_add_component(world, entity, TEST_COMPONENT);
    if (!component) return false;
    component->value = value;
    return true;
}

static u32 remote_value(Fixture *fixture)
{
    Value *component = (Value *)world_get_component(
        fixture->remote, (Entity){1u, 1u}, TEST_COMPONENT);
    return component ? component->value : 0u;
}

static bool fixture_init(Fixture *fixture)
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
        break_schema_register(fixture->schemas, &schema) != BREAK_SCHEMA_OK) {
        return false;
    }
    world_register_component(fixture->authoritative, TEST_COMPONENT, sizeof(Value));
    world_register_component(fixture->remote, TEST_COMPONENT, sizeof(Value));
    config = test_config(fixture);
    fixture->session = break_world_session_create(&config);
    if (!fixture->session) return false;
    fixture->epoch = break_world_session_stream_epoch(
        TEST_PROTOCOL, break_schema_hash(fixture->schemas), TEST_LEVEL);
    return true;
}

static void fixture_dispose(Fixture *fixture)
{
    break_world_session_destroy(fixture->session);
    world_destroy(fixture->remote);
    world_destroy(fixture->authoritative);
    break_schema_registry_destroy(fixture->schemas);
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

static bool push_bytes_with_epoch(Fixture *fixture, BreakConnectionKey connection,
                                  u64 delta_id, u64 epoch, const void *bytes, usize size)
{
    BreakReplicationFragment *fragments = NULL;
    usize count = 0u;
    bool handled = true;
    if (break_replication_fragment_payload(delta_id, epoch, bytes, size, 23u,
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
                connection, &message, break_world_session_bridge(fixture->session))) {
            handled = false;
            break;
        }
    }
    break_replication_fragments_free(fragments, count);
    return handled;
}

static bool push_bytes(Fixture *fixture, BreakConnectionKey connection, u64 delta_id,
                       const void *bytes, usize size)
{
    return push_bytes_with_epoch(fixture, connection, delta_id, fixture->epoch, bytes, size);
}

static void put64(u8 *out, u64 value)
{
    for (u32 i = 0u; i < 8u; ++i) out[i] = (u8)(value >> (i * 8u));
}

static bool remote_matches(Fixture *fixture, u64 tick, u64 expected_id)
{
    BreakWorldSnapshot *snapshot = break_world_snapshot_build(
        fixture->remote, fixture->schemas, tick);
    bool matches;
    if (!snapshot) return false;
    matches = break_world_snapshot_id(snapshot) == expected_id;
    break_world_snapshot_release(snapshot);
    return matches;
}

static bool baseline_matches(Fixture *fixture, BreakConnectionKey connection,
                             u64 expected_id, u64 expected_tick)
{
    u64 id = 0u;
    u64 tick = 0u;
    return break_world_session_baseline(fixture->session, connection, &id, &tick) &&
           id == expected_id && tick == expected_tick;
}

static bool establish_baseline(Fixture *fixture, BreakConnectionKey connection,
                               u32 value, BreakWorldSnapshot **out_base)
{
    Entity entity = world_create_entity(fixture->authoritative);
    BreakWorldSnapshot *base;
    u8 *wire = NULL;
    usize size = 0u;
    bool ok;
    if (!add_value(fixture->authoritative, entity, value)) return false;
    base = break_world_snapshot_build(fixture->authoritative, fixture->schemas, 10u);
    if (!base) return false;
    ok = encode_full(base, &wire, &size) &&
         push_bytes(fixture, connection, 1u, wire, size) &&
         break_world_session_drain(fixture->session, connection, fixture->remote, 1u) == 1u;
    free(wire);
    if (!ok) {
        break_world_snapshot_release(base);
        return false;
    }
    *out_base = base;
    return true;
}

static void check_delta_rejection(usize offset)
{
    Fixture fixture;
    BreakWorldSnapshot *base = NULL;
    BreakWorldSnapshot *target = NULL;
    BreakWorldSessionStats stats;
    Value *value;
    u8 *wire = NULL;
    usize size = 0u;
    u64 changed;

    ASSERT_TRUE(fixture_init(&fixture));
    ASSERT_TRUE(break_world_session_open(fixture.session, 11u));
    ASSERT_TRUE(establish_baseline(&fixture, 11u, 10u, &base));
    value = (Value *)world_get_component(fixture.authoritative, (Entity){1u, 1u},
                                         TEST_COMPONENT);
    ASSERT_NOT_NULL(value);
    value->value = 12u;
    target = break_world_snapshot_build(fixture.authoritative, fixture.schemas, 20u);
    ASSERT_NOT_NULL(target);
    ASSERT_TRUE(encode_delta(base, target, &wire, &size));
    memcpy(&changed, wire + offset, sizeof(changed));
    put64(wire + offset, changed ^ 1u);
    ASSERT_TRUE(push_bytes(&fixture, 11u, 2u, wire, size));
    ASSERT_TRUE(remote_matches(&fixture, 10u, break_world_snapshot_id(base)));
    ASSERT_EQ(break_world_session_drain(fixture.session, 11u, fixture.remote, 1u), 1u);
    ASSERT_TRUE(remote_matches(&fixture, 10u, break_world_snapshot_id(base)));
    ASSERT_TRUE(baseline_matches(&fixture, 11u, break_world_snapshot_id(base), 10u));
    break_world_session_stats(fixture.session, &stats);
    ASSERT_EQ(stats.applied_packets, 1u);
    ASSERT_EQ(stats.need_full_packets, 1u);
    ASSERT_EQ(stats.rejected_packets, 1u);
    ASSERT_EQ(stats.drained_packets, 2u);
    free(wire);
    break_world_snapshot_release(target);
    break_world_snapshot_release(base);
    fixture_dispose(&fixture);
}

TEST(world_session_epoch_open_close_and_empty_baseline)
{
    Fixture fixture;
    BreakWorldSessionConfig invalid;
    BreakWorldSessionStats stats;
    BreakWorldSessionStats zero;
    u64 id = 99u;
    u64 tick = 99u;

    ASSERT_EQ(break_world_session_stream_epoch(
                  1u, UINT64_C(0x1122334455667788), 7u),
              UINT64_C(0x66dd9f4887da0d55));
    ASSERT_NEQ(break_world_session_stream_epoch(
                   2u, UINT64_C(0x1122334455667788), 7u),
               UINT64_C(0x66dd9f4887da0d55));
    ASSERT_NEQ(break_world_session_stream_epoch(
                   1u, UINT64_C(0x1122334455667789), 7u),
               UINT64_C(0x66dd9f4887da0d55));
    ASSERT_NEQ(break_world_session_stream_epoch(
                   1u, UINT64_C(0x1122334455667788), 8u),
               UINT64_C(0x66dd9f4887da0d55));
    ASSERT_TRUE(break_world_session_create(NULL) == NULL);
    ASSERT_TRUE(fixture_init(&fixture));
    invalid = test_config(&fixture);
    invalid.schemas = NULL;
    ASSERT_TRUE(break_world_session_create(&invalid) == NULL);
    invalid = test_config(&fixture);
    invalid.protocol_version = 0u;
    ASSERT_TRUE(break_world_session_create(&invalid) == NULL);
    invalid = test_config(&fixture);
    invalid.bridge.clock = NULL;
    ASSERT_TRUE(break_world_session_create(&invalid) == NULL);
    ASSERT_NOT_NULL(break_world_session_bridge(fixture.session));
    ASSERT_TRUE(break_world_session_bridge(NULL) == NULL);
    ASSERT_FALSE(break_world_session_baseline(NULL, 11u, &id, &tick));
    ASSERT_EQ(id, 0u);
    ASSERT_EQ(tick, 0u);
    ASSERT_FALSE(break_world_session_open(NULL, 11u));
    ASSERT_FALSE(break_world_session_open(fixture.session, 0u));
    ASSERT_TRUE(break_world_session_open(fixture.session, 11u));
    ASSERT_FALSE(break_world_session_open(fixture.session, 11u));
    ASSERT_TRUE(baseline_matches(&fixture, 11u, 0u, 0u));
    ASSERT_FALSE(push_bytes_with_epoch(&fixture, 11u, 1u, fixture.epoch ^ 1u, "x", 1u));
    ASSERT_EQ(break_world_session_drain(NULL, 11u, fixture.remote, 1u), 0u);
    ASSERT_EQ(break_world_session_drain(fixture.session, 11u, NULL, 1u), 0u);
    ASSERT_TRUE(break_world_session_close(fixture.session, 11u));
    ASSERT_FALSE(break_world_session_baseline(fixture.session, 11u, &id, &tick));
    ASSERT_FALSE(break_world_session_close(fixture.session, 11u));
    ASSERT_TRUE(break_world_session_open(fixture.session, 11u));
    ASSERT_TRUE(baseline_matches(&fixture, 11u, 0u, 0u));
    memset(&stats, 0xa5, sizeof(stats));
    memset(&zero, 0, sizeof(zero));
    break_world_session_stats(NULL, &stats);
    ASSERT_TRUE(memcmp(&stats, &zero, sizeof(stats)) == 0);
    break_world_session_stats(fixture.session, NULL);
    fixture_dispose(&fixture);
    break_world_session_destroy(NULL);
}

TEST(world_session_full_is_applied_only_by_drain_and_advances_baseline)
{
    Fixture fixture;
    BreakWorldSnapshot *target;
    BreakWorldSessionStats stats;
    Entity entity;
    u8 *wire = NULL;
    usize size = 0u;

    ASSERT_TRUE(fixture_init(&fixture));
    ASSERT_TRUE(break_world_session_open(fixture.session, 11u));
    entity = world_create_entity(fixture.authoritative);
    ASSERT_TRUE(add_value(fixture.authoritative, entity, 42u));
    target = break_world_snapshot_build(fixture.authoritative, fixture.schemas, 10u);
    ASSERT_NOT_NULL(target);
    ASSERT_TRUE(encode_full(target, &wire, &size));
    ASSERT_TRUE(push_bytes(&fixture, 11u, 1u, wire, size));
    ASSERT_EQ(break_world_entity_count(fixture.remote), 0u);
    ASSERT_EQ(remote_value(&fixture), 0u);
    ASSERT_TRUE(baseline_matches(&fixture, 11u, 0u, 0u));
    break_world_session_stats(fixture.session, &stats);
    ASSERT_EQ(stats.bridge.completed_packets, 1u);
    ASSERT_EQ(stats.bridge.completion_count, 1u);
    ASSERT_EQ(stats.applied_packets, 0u);
    ASSERT_EQ(stats.drained_packets, 0u);
    ASSERT_EQ(break_world_session_drain(fixture.session, 11u, fixture.remote, 0u), 0u);
    ASSERT_EQ(break_world_session_drain(fixture.session, 99u, fixture.remote, 1u), 0u);
    ASSERT_EQ(break_world_entity_count(fixture.remote), 0u);
    ASSERT_EQ(break_world_session_drain(fixture.session, 11u, fixture.remote, 1u), 1u);
    ASSERT_EQ(remote_value(&fixture), 42u);
    ASSERT_TRUE(remote_matches(&fixture, 10u, break_world_snapshot_id(target)));
    ASSERT_TRUE(baseline_matches(&fixture, 11u, break_world_snapshot_id(target), 10u));
    break_world_session_stats(fixture.session, &stats);
    ASSERT_EQ(stats.applied_packets, 1u);
    ASSERT_EQ(stats.need_full_packets, 0u);
    ASSERT_EQ(stats.rejected_packets, 0u);
    ASSERT_EQ(stats.drained_packets, 1u);
    ASSERT_EQ(stats.bridge.completion_count, 0u);
    free(wire);
    break_world_snapshot_release(target);
    fixture_dispose(&fixture);
}

TEST(world_session_delta_applies_and_advances_confirmed_baseline)
{
    Fixture fixture;
    BreakWorldSnapshot *base = NULL;
    BreakWorldSnapshot *target;
    BreakWorldSessionStats stats;
    Value *value;
    u8 *wire = NULL;
    usize size = 0u;

    ASSERT_TRUE(fixture_init(&fixture));
    ASSERT_TRUE(break_world_session_open(fixture.session, 11u));
    ASSERT_TRUE(establish_baseline(&fixture, 11u, 10u, &base));
    value = (Value *)world_get_component(fixture.authoritative, (Entity){1u, 1u},
                                         TEST_COMPONENT);
    ASSERT_NOT_NULL(value);
    value->value = 11u;
    target = break_world_snapshot_build(fixture.authoritative, fixture.schemas, 20u);
    ASSERT_NOT_NULL(target);
    ASSERT_TRUE(encode_delta(base, target, &wire, &size));
    ASSERT_TRUE(push_bytes(&fixture, 11u, 2u, wire, size));
    ASSERT_EQ(remote_value(&fixture), 10u);
    ASSERT_TRUE(baseline_matches(&fixture, 11u, break_world_snapshot_id(base), 10u));
    ASSERT_EQ(break_world_session_drain(fixture.session, 11u, fixture.remote, 1u), 1u);
    ASSERT_EQ(remote_value(&fixture), 11u);
    ASSERT_TRUE(remote_matches(&fixture, 20u, break_world_snapshot_id(target)));
    ASSERT_TRUE(baseline_matches(&fixture, 11u, break_world_snapshot_id(target), 20u));
    break_world_session_stats(fixture.session, &stats);
    ASSERT_EQ(stats.applied_packets, 2u);
    ASSERT_EQ(stats.rejected_packets, 0u);
    ASSERT_EQ(stats.drained_packets, 2u);
    free(wire);
    break_world_snapshot_release(target);
    break_world_snapshot_release(base);
    fixture_dispose(&fixture);
}

TEST(world_session_drain_is_per_connection_bounded_and_fifo)
{
    Fixture fixture;
    World *other_source = NULL;
    World *other_remote = NULL;
    BreakWorldSnapshot *first;
    BreakWorldSnapshot *second;
    BreakWorldSnapshot *other;
    BreakWorldSessionStats stats;
    Entity entity;
    Value *value;
    u8 *first_wire = NULL;
    u8 *second_wire = NULL;
    u8 *other_wire = NULL;
    usize first_size = 0u;
    usize second_size = 0u;
    usize other_size = 0u;

    ASSERT_TRUE(fixture_init(&fixture));
    other_source = world_create();
    other_remote = world_create();
    ASSERT_NOT_NULL(other_source);
    ASSERT_NOT_NULL(other_remote);
    world_register_component(other_source, TEST_COMPONENT, sizeof(Value));
    world_register_component(other_remote, TEST_COMPONENT, sizeof(Value));
    ASSERT_TRUE(break_world_session_open(fixture.session, 11u));
    ASSERT_TRUE(break_world_session_open(fixture.session, 22u));

    entity = world_create_entity(fixture.authoritative);
    ASSERT_TRUE(add_value(fixture.authoritative, entity, 11u));
    first = break_world_snapshot_build(fixture.authoritative, fixture.schemas, 11u);
    ASSERT_NOT_NULL(first);
    ASSERT_TRUE(encode_full(first, &first_wire, &first_size));
    value = (Value *)world_get_component(fixture.authoritative, entity, TEST_COMPONENT);
    ASSERT_NOT_NULL(value);
    value->value = 33u;
    second = break_world_snapshot_build(fixture.authoritative, fixture.schemas, 22u);
    ASSERT_NOT_NULL(second);
    ASSERT_TRUE(encode_full(second, &second_wire, &second_size));
    entity = world_create_entity(other_source);
    ASSERT_TRUE(add_value(other_source, entity, 22u));
    other = break_world_snapshot_build(other_source, fixture.schemas, 15u);
    ASSERT_NOT_NULL(other);
    ASSERT_TRUE(encode_full(other, &other_wire, &other_size));

    ASSERT_TRUE(push_bytes(&fixture, 11u, 1u, first_wire, first_size));
    ASSERT_TRUE(push_bytes(&fixture, 22u, 1u, other_wire, other_size));
    ASSERT_TRUE(push_bytes(&fixture, 11u, 2u, second_wire, second_size));
    ASSERT_EQ(break_world_session_drain(fixture.session, 22u, other_remote, 1u), 1u);
    ASSERT_EQ(remote_value(&fixture), 0u);
    ASSERT_EQ(break_world_entity_count(fixture.remote), 0u);
    ASSERT_EQ(((Value *)world_get_component(other_remote, (Entity){1u, 1u},
                                             TEST_COMPONENT))->value, 22u);
    ASSERT_EQ(break_world_session_drain(fixture.session, 11u, fixture.remote, 1u), 1u);
    ASSERT_EQ(remote_value(&fixture), 11u);
    ASSERT_TRUE(baseline_matches(&fixture, 11u, break_world_snapshot_id(first), 11u));
    break_world_session_stats(fixture.session, &stats);
    ASSERT_EQ(stats.bridge.completion_count, 1u);
    ASSERT_EQ(stats.drained_packets, 2u);
    ASSERT_EQ(break_world_session_drain(fixture.session, 11u, fixture.remote, 8u), 1u);
    ASSERT_EQ(remote_value(&fixture), 33u);
    ASSERT_TRUE(baseline_matches(&fixture, 11u, break_world_snapshot_id(second), 22u));
    break_world_session_stats(fixture.session, &stats);
    ASSERT_EQ(stats.applied_packets, 3u);
    ASSERT_EQ(stats.rejected_packets, 0u);
    ASSERT_EQ(stats.drained_packets, 3u);
    ASSERT_EQ(stats.bridge.completion_count, 0u);
    free(other_wire);
    free(second_wire);
    free(first_wire);
    break_world_snapshot_release(other);
    break_world_snapshot_release(second);
    break_world_snapshot_release(first);
    world_destroy(other_remote);
    world_destroy(other_source);
    fixture_dispose(&fixture);
}

TEST(world_session_base_mismatch_preserves_world_and_baseline)
{
    check_delta_rejection(24u);
}

TEST(world_session_schema_mismatch_preserves_world_and_baseline)
{
    check_delta_rejection(8u);
}

TEST(world_session_level_mismatch_preserves_world_and_baseline)
{
    check_delta_rejection(16u);
}

TEST(world_session_target_hash_mismatch_preserves_world_and_baseline)
{
    check_delta_rejection(32u);
}

TEST(world_session_malformed_packet_is_rejected_without_need_full)
{
    Fixture fixture;
    BreakWorldSnapshot *base = NULL;
    BreakWorldSessionStats stats;

    ASSERT_TRUE(fixture_init(&fixture));
    ASSERT_TRUE(break_world_session_open(fixture.session, 11u));
    ASSERT_TRUE(establish_baseline(&fixture, 11u, 10u, &base));
    ASSERT_TRUE(push_bytes(&fixture, 11u, 2u, "bad", 3u));
    ASSERT_EQ(break_world_session_drain(fixture.session, 11u, fixture.remote, 1u), 1u);
    ASSERT_TRUE(remote_matches(&fixture, 10u, break_world_snapshot_id(base)));
    ASSERT_TRUE(baseline_matches(&fixture, 11u, break_world_snapshot_id(base), 10u));
    break_world_session_stats(fixture.session, &stats);
    ASSERT_EQ(stats.applied_packets, 1u);
    ASSERT_EQ(stats.need_full_packets, 0u);
    ASSERT_EQ(stats.rejected_packets, 1u);
    ASSERT_EQ(stats.drained_packets, 2u);
    break_world_snapshot_release(base);
    fixture_dispose(&fixture);
}

TEST(world_session_apply_failure_rolls_back_world_and_empty_baseline)
{
    Fixture fixture;
    BreakWorldSnapshot *target;
    BreakWorldSessionStats stats;
    Entity first;
    Entity second;
    u64 id = 99u;
    u64 tick = 99u;
    u8 *wire = NULL;
    usize size = 0u;

    ASSERT_TRUE(fixture_init(&fixture));
    first = world_create_entity(fixture.remote);
    ASSERT_EQ(first.index, 1u);
    first = world_create_entity(fixture.authoritative);
    second = world_create_entity(fixture.authoritative);
    ASSERT_EQ(first.index, 1u);
    ASSERT_EQ(second.index, 2u);
    world_destroy_entity(fixture.authoritative, first);
    target = break_world_snapshot_build(fixture.authoritative, fixture.schemas, 5u);
    ASSERT_NOT_NULL(target);
    ASSERT_TRUE(encode_full(target, &wire, &size));
    ASSERT_TRUE(break_world_session_open(fixture.session, 11u));
    ASSERT_TRUE(push_bytes(&fixture, 11u, 1u, wire, size));
    ASSERT_EQ(break_world_session_drain(fixture.session, 11u, fixture.remote, 1u), 1u);
    ASSERT_TRUE(world_entity_exists(fixture.remote, (Entity){1u, 1u}));
    ASSERT_FALSE(world_entity_exists(fixture.remote, (Entity){2u, 1u}));
    ASSERT_EQ(break_world_entity_count(fixture.remote), 1u);
    ASSERT_TRUE(break_world_session_baseline(fixture.session, 11u, &id, &tick));
    ASSERT_EQ(id, 0u);
    ASSERT_EQ(tick, 0u);
    break_world_session_stats(fixture.session, &stats);
    ASSERT_EQ(stats.applied_packets, 0u);
    ASSERT_EQ(stats.need_full_packets, 1u);
    ASSERT_EQ(stats.rejected_packets, 1u);
    ASSERT_EQ(stats.drained_packets, 1u);
    free(wire);
    break_world_snapshot_release(target);
    fixture_dispose(&fixture);
}

TEST(world_session_close_releases_confirmed_baseline)
{
    Fixture fixture;
    BreakWorldSnapshot *base = NULL;
    BreakWorldSnapshot *target;
    BreakWorldSessionStats stats;
    Value *value;
    u8 *wire = NULL;
    usize size = 0u;

    ASSERT_TRUE(fixture_init(&fixture));
    ASSERT_TRUE(break_world_session_open(fixture.session, 11u));
    ASSERT_TRUE(establish_baseline(&fixture, 11u, 10u, &base));
    ASSERT_TRUE(break_world_session_close(fixture.session, 11u));
    ASSERT_FALSE(baseline_matches(&fixture, 11u, 0u, 0u));
    ASSERT_TRUE(break_world_session_open(fixture.session, 11u));
    ASSERT_TRUE(baseline_matches(&fixture, 11u, 0u, 0u));
    value = (Value *)world_get_component(fixture.authoritative, (Entity){1u, 1u},
                                         TEST_COMPONENT);
    ASSERT_NOT_NULL(value);
    value->value = 11u;
    target = break_world_snapshot_build(fixture.authoritative, fixture.schemas, 20u);
    ASSERT_NOT_NULL(target);
    ASSERT_TRUE(encode_delta(base, target, &wire, &size));
    ASSERT_TRUE(push_bytes(&fixture, 11u, 1u, wire, size));
    ASSERT_EQ(break_world_session_drain(fixture.session, 11u, fixture.remote, 1u), 1u);
    ASSERT_EQ(remote_value(&fixture), 10u);
    ASSERT_TRUE(baseline_matches(&fixture, 11u, 0u, 0u));
    break_world_session_stats(fixture.session, &stats);
    ASSERT_EQ(stats.applied_packets, 1u);
    ASSERT_EQ(stats.need_full_packets, 1u);
    ASSERT_EQ(stats.rejected_packets, 1u);
    ASSERT_EQ(stats.drained_packets, 2u);
    free(wire);
    break_world_snapshot_release(target);
    break_world_snapshot_release(base);
    fixture_dispose(&fixture);
}

TEST_MAIN_BEGIN()
    RUN_TEST(world_session_epoch_open_close_and_empty_baseline);
    RUN_TEST(world_session_full_is_applied_only_by_drain_and_advances_baseline);
    RUN_TEST(world_session_delta_applies_and_advances_confirmed_baseline);
    RUN_TEST(world_session_drain_is_per_connection_bounded_and_fifo);
    RUN_TEST(world_session_base_mismatch_preserves_world_and_baseline);
    RUN_TEST(world_session_schema_mismatch_preserves_world_and_baseline);
    RUN_TEST(world_session_level_mismatch_preserves_world_and_baseline);
    RUN_TEST(world_session_target_hash_mismatch_preserves_world_and_baseline);
    RUN_TEST(world_session_malformed_packet_is_rejected_without_need_full);
    RUN_TEST(world_session_apply_failure_rolls_back_world_and_empty_baseline);
    RUN_TEST(world_session_close_releases_confirmed_baseline);
TEST_MAIN_END()
