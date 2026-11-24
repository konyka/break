#include "test_framework.h"

#include <core/platform_thread.h>
#include <network/break_net_message_registry.h>
#include <runtime/runtime_world_session.h>
#include <snow/acceptor.h>
#include <snow/endpoint.h>

#include <stdatomic.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define TEST_COMPONENT 11u
#define TEST_PROTOCOL 1u
#define KEY_A UINT64_C(0x100000001)
#define KEY_B UINT64_C(0x200000002)
#define KEY_C UINT64_C(0x300000003)
#define HIGH_CID UINT64_C(0xF123456789ABCDEF)

_Static_assert(sizeof(BreakRuntimeWorldCommand) == 56u, "command size");
_Static_assert(offsetof(BreakRuntimeWorldCommand, kind) == 0u, "kind offset");
_Static_assert(offsetof(BreakRuntimeWorldCommand, reserved_zero) == 4u, "reserved offset");
_Static_assert(offsetof(BreakRuntimeWorldCommand, connection_key) == 8u, "key offset");
_Static_assert(offsetof(BreakRuntimeWorldCommand, connection_epoch) == 16u, "epoch offset");
_Static_assert(offsetof(BreakRuntimeWorldCommand, level_generation) == 24u, "level offset");
_Static_assert(offsetof(BreakRuntimeWorldCommand, delta_id) == 32u, "delta offset");
_Static_assert(offsetof(BreakRuntimeWorldCommand, target_snapshot_id) == 40u, "target offset");
_Static_assert(offsetof(BreakRuntimeWorldCommand, target_tick) == 48u, "tick offset");

typedef struct {
    u32 value;
} Value;

typedef struct {
    BreakComponentSchemaRegistry *schemas;
    World *world;
    BreakWorldSession *session;
    BreakNetReactor *reactor;
    SnowAcceptor *acceptor;
    BreakRuntimeBus *bus;
    BreakRuntimeWorldSession *adapter;
    u64 now;
} Fixture;

static u64 test_clock(void *user)
{
    return *(const u64 *)user;
}

static u16 get16(const u8 *bytes)
{
    return (u16)((u16)bytes[0] | ((u16)bytes[1] << 8u));
}

static u64 get64(const u8 *bytes)
{
    u64 value = 0u;
    for (u32 i = 0u; i < 8u; ++i) value |= (u64)bytes[i] << (i * 8u);
    return value;
}

static bool reactor_start(Fixture *fixture)
{
    BreakNetReactorConfig config = {BREAK_NET_DRIVE_STEP, 0, 8u, 1000, 1000u, 1u, false};
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

static bool fixture_init_without_adapter(Fixture *fixture, u64 level)
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
    fixture->world = world_create();
    if (!fixture->schemas || !fixture->world ||
        break_schema_register(fixture->schemas, &schema) != BREAK_SCHEMA_OK ||
        break_runtime_bus_create(&fixture->bus) != BREAK_RUNTIME_OK ||
        !reactor_start(fixture)) {
        return false;
    }
    world_register_component(fixture->world, TEST_COMPONENT, sizeof(Value));
    memset(&config, 0, sizeof(config));
    config.schemas = fixture->schemas;
    config.protocol_version = TEST_PROTOCOL;
    config.level_generation = level;
    config.bridge.reactor = fixture->reactor;
    config.bridge.max_connections = 2u;
    config.bridge.stream_capacity = 4u;
    config.bridge.max_pending_bytes_per_connection = 8192u;
    config.bridge.max_total_pending_bytes = 16384u;
    config.bridge.max_metadata_bytes_per_connection = 8192u;
    config.bridge.max_total_metadata_bytes = 16384u;
    config.bridge.max_fragment_bytes = 4096u;
    config.bridge.max_fragment_count = 64u;
    config.bridge.completion_capacity = 8u;
    config.bridge.max_completion_packet_bytes = 8192u;
    config.bridge.max_completion_queue_bytes = 16384u;
    config.bridge.clock = test_clock;
    config.bridge.clock_user = &fixture->now;
    config.history_entry_limit = 8u;
    config.history_byte_limit = 16384u;
    config.packet_byte_limit = 4096u;
    config.need_full_tick_interval = 5u;
    fixture->session = break_world_session_create(&config);
    return fixture->session != NULL;
}

static bool fixture_attach(Fixture *fixture, u32 queue_capacity, u32 max_connections)
{
    BreakRuntimeWorldSessionConfig config;
    memset(&config, 0, sizeof(config));
    config.session = fixture->session;
    config.bus = fixture->bus;
    config.queue_capacity = queue_capacity;
    config.max_connections = max_connections;
    fixture->adapter = break_runtime_world_session_create(&config);
    return fixture->adapter != NULL;
}

static bool fixture_init(Fixture *fixture, u64 level, u32 max_connections)
{
    return fixture_init_without_adapter(fixture, level) &&
           fixture_attach(fixture, 0u, max_connections);
}

static void clear_outbound(Fixture *fixture)
{
    BreakNetOwnedMessage message;
    u64 key = 0u;
    while (break_net_reactor_poll_outbound_for_test(fixture->reactor, &key, &message) ==
           BREAK_NET_EVENT_OK) {
        break_net_message_release(&message);
    }
}

static void fixture_dispose(Fixture *fixture)
{
    if (fixture->adapter) {
        break_runtime_world_session_close(fixture->adapter);
        for (u32 i = 0u; i < 4u && break_runtime_world_session_pending(fixture->adapter) != 0u; ++i) {
            usize drained = 0u;
            clear_outbound(fixture);
            (void)break_runtime_world_session_drain(fixture->adapter, 256u, &drained);
        }
        (void)break_runtime_world_session_destroy(fixture->adapter);
    }
    break_runtime_bus_destroy(fixture->bus);
    break_world_session_destroy(fixture->session);
    world_destroy(fixture->world);
    break_schema_registry_destroy(fixture->schemas);
    if (fixture->reactor) {
        (void)break_net_reactor_stop(fixture->reactor, 1000u);
        break_net_reactor_destroy(fixture->reactor);
    }
    if (fixture->acceptor) SnowAcceptorDestroy(fixture->acceptor);
    memset(fixture, 0, sizeof(*fixture));
}

static BreakRuntimeWorldCommand command(u32 kind, u64 key, u64 epoch, u64 level)
{
    BreakRuntimeWorldCommand result;
    memset(&result, 0, sizeof(result));
    result.kind = kind;
    result.connection_key = key;
    result.connection_epoch = epoch;
    result.level_generation = level;
    return result;
}

static BreakRuntimeError publish_external(BreakRuntimeBus *bus,
                                          const BreakRuntimeWorldCommand *item,
                                          u64 correlation_id, u32 *out_delivered)
{
    BreakRuntimeMessageView view;
    memset(&view, 0, sizeof(view));
    view.kind = BREAK_RUNTIME_WORLD_SESSION_CONTROL_KIND;
    view.version = 1u;
    view.sequence = UINT64_MAX;
    view.correlation_id = correlation_id;
    view.data = item;
    view.size = sizeof(*item);
    return break_runtime_bus_publish(bus, &view, out_delivered);
}

static bool open_connection(Fixture *fixture, u64 key, u64 level, u64 *out_epoch)
{
    BreakRuntimeWorldCommand open = command(BREAK_RUNTIME_WORLD_COMMAND_OPEN, key, 0u, level);
    usize drained = 0u;
    *out_epoch = 0u;
    return break_runtime_world_session_submit(fixture->adapter, &open, 0u) == BREAK_RUNTIME_OK &&
           break_runtime_world_session_drain(fixture->adapter, 1u, &drained) == BREAK_RUNTIME_OK &&
           drained == 1u &&
           break_runtime_world_session_connection_epoch(fixture->adapter, key, out_epoch) &&
           *out_epoch != 0u;
}

static bool next_control(Fixture *fixture, u64 *out_key, BreakNetOwnedMessage *out_message)
{
    for (;;) {
        if (break_net_reactor_poll_outbound_for_test(fixture->reactor, out_key, out_message) !=
            BREAK_NET_EVENT_OK) {
            return false;
        }
        if (out_message->message_id == BREAK_NET_MESSAGE_ID_WORLD_CONTROL) return true;
        break_net_message_release(out_message);
    }
}

static bool control_payload_matches(const BreakNetOwnedMessage *message,
                                    BreakWorldSessionControlKind kind, u64 delta_id,
                                    u64 target_id, u64 target_tick, u64 level)
{
    const u8 *bytes = (const u8 *)message->data;
    usize expected_size = message->protocol_version == 2u
                              ? BREAK_WORLD_SESSION_CONTROL_WIRE_SIZE_V2
                              : BREAK_WORLD_SESSION_CONTROL_WIRE_SIZE;
    if (message->size != expected_size || message->size < 32u ||
        memcmp(bytes, "BRWC", 4u) != 0 || get16(bytes + 4u) != message->protocol_version ||
        get16(bytes + 6u) != (u16)kind || get64(bytes + 8u) != delta_id ||
        get64(bytes + 16u) != target_id || get64(bytes + 24u) != target_tick) {
        return false;
    }
    return message->protocol_version == 1u ||
           (message->protocol_version == 2u && get64(bytes + 32u) == level);
}

static bool set_world_value(Fixture *fixture, u32 value)
{
    Value *component;
    if (break_world_entity_count(fixture->world) == 0u) {
        Entity entity = world_create_entity(fixture->world);
        component = (Value *)world_add_component(fixture->world, entity, TEST_COMPONENT);
    } else {
        component = (Value *)world_get_component(fixture->world, (Entity){1u, 1u}, TEST_COMPONENT);
    }
    if (!component) return false;
    component->value = value;
    return true;
}

static BreakWorldSnapshot *make_target(Fixture *fixture, u32 value, u64 tick)
{
    if (!set_world_value(fixture, value)) return NULL;
    return break_world_snapshot_build(fixture->world, fixture->schemas, tick);
}

static bool publish_target(Fixture *fixture, u64 key, BreakWorldSnapshot *target,
                           u64 level, u64 *out_delta_id)
{
    BreakWorldSessionSenderState before;
    if (!break_world_session_sender_state(fixture->session, key, &before) ||
        break_world_session_publish_snapshot(fixture->session, key, target, level) !=
            BREAK_NET_SEND_OK) {
        return false;
    }
    *out_delta_id = before.next_delta_id;
    clear_outbound(fixture);
    return true;
}

static bool control_via_adapter(Fixture *fixture, u32 command_kind, u64 key, u64 epoch,
                                u64 level, u64 delta_id, const BreakWorldSnapshot *target,
                                u64 correlation_id)
{
    BreakRuntimeWorldCommand control = command(command_kind, key, epoch, level);
    BreakNetOwnedMessage outbound;
    BreakWorldSessionControlKind wire_kind;
    u64 target_id = target ? break_world_snapshot_id(target) : 0u;
    u64 target_tick = target ? break_world_snapshot_tick(target) : 0u;
    u64 outbound_key = 0u;
    usize drained = 0u;
    bool handled;
    control.delta_id = delta_id;
    control.target_snapshot_id = target_id;
    control.target_tick = target_tick;
    wire_kind = command_kind == BREAK_RUNTIME_WORLD_COMMAND_ACK
                    ? BREAK_WORLD_SESSION_CONTROL_ACK
                    : BREAK_WORLD_SESSION_CONTROL_NEED_FULL;
    if (break_runtime_world_session_submit(fixture->adapter, &control, correlation_id) !=
            BREAK_RUNTIME_OK ||
        break_runtime_world_session_drain(fixture->adapter, 1u, &drained) != BREAK_RUNTIME_OK ||
        drained != 1u || !next_control(fixture, &outbound_key, &outbound)) {
        return false;
    }
    if (outbound_key != key || outbound.correlation_id != correlation_id ||
        !control_payload_matches(&outbound, wire_kind, delta_id, target_id, target_tick, level)) {
        break_net_message_release(&outbound);
        return false;
    }
    handled = break_world_session_handle_control(key, &outbound, fixture->session);
    break_net_message_release(&outbound);
    return handled;
}

TEST(layout_registry_defaults_and_invalid_configs)
{
    Fixture fixture;
    BreakRuntimeWorldSessionConfig config;
    BreakRuntimeWorldSessionConfig bad;
    BreakRuntimeBusKind expected = {BREAK_RUNTIME_WORLD_SESSION_CONTROL_KIND, 1u, 56u,
                                    "world_session.control", true, 0u};
    BreakRuntimeWorldCommand open;
    BreakRuntimeWorldSessionStats stats;
    BreakRuntimeBus *other_bus = NULL;
    ASSERT_TRUE(fixture_init_without_adapter(&fixture, 0u));
    ASSERT_EQ(break_runtime_world_session_create(NULL), NULL);
    memset(&config, 0, sizeof(config));
    config.session = fixture.session;
    config.bus = fixture.bus;
    bad = config;
    bad.session = NULL;
    ASSERT_EQ(break_runtime_world_session_create(&bad), NULL);
    bad = config;
    bad.bus = NULL;
    ASSERT_EQ(break_runtime_world_session_create(&bad), NULL);
    bad = config;
    bad.queue_capacity = 257u;
    ASSERT_EQ(break_runtime_world_session_create(&bad), NULL);
    bad = config;
    bad.max_connections = 65u;
    ASSERT_EQ(break_runtime_world_session_create(&bad), NULL);
    bad = config;
    bad.subscriber_name = "bad name";
    ASSERT_EQ(break_runtime_world_session_create(&bad), NULL);
    ASSERT_EQ(break_runtime_bus_create(&other_bus), BREAK_RUNTIME_OK);
    expected.max_payload = 55u;
    ASSERT_EQ(break_runtime_bus_register_kind(other_bus, &expected), BREAK_RUNTIME_OK);
    bad = config;
    bad.bus = other_bus;
    ASSERT_EQ(break_runtime_world_session_create(&bad), NULL);
    break_runtime_bus_destroy(other_bus);
    expected.max_payload = 56u;

    ASSERT_TRUE(fixture_attach(&fixture, 0u, 0u));
    ASSERT_EQ(break_runtime_bus_kind_matches(fixture.bus, &expected), BREAK_RUNTIME_OK);
    open = command(BREAK_RUNTIME_WORLD_COMMAND_OPEN, KEY_A, 0u, 0u);
    for (u32 i = 0u; i < 64u; ++i) {
        ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &open, 0u), BREAK_RUNTIME_OK);
        ASSERT_FALSE(break_world_session_baseline(fixture.session, KEY_A, NULL, NULL));
    }
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &open, 0u), BREAK_RUNTIME_OVERLOAD);
    break_runtime_world_session_stats(fixture.adapter, &stats);
    ASSERT_EQ(stats.submitted, 64u);
    ASSERT_EQ(stats.drained, 0u);
    ASSERT_EQ(stats.next_sequence, 65u);
    ASSERT_EQ(stats.queued, 64u);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 64u);
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 0u, NULL), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 64u);
    fixture_dispose(&fixture);
}

TEST(stateless_validation_defers_connection_and_level_state)
{
    Fixture fixture;
    BreakRuntimeWorldCommand item = {0};
    BreakRuntimeWorldSessionStats stats;
    usize drained = 99u;
    ASSERT_TRUE(fixture_init(&fixture, 7u, 2u));
    ASSERT_EQ(break_runtime_world_session_submit(NULL, &item, 0u), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, NULL, 0u), BREAK_RUNTIME_INVALID);
    item = command(0u, KEY_A, 0u, 7u);
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &item, 0u), BREAK_RUNTIME_INVALID);
    item = command(BREAK_RUNTIME_WORLD_COMMAND_OPEN, KEY_A, 0u, 7u);
    item.reserved_zero = 1u;
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &item, 0u), BREAK_RUNTIME_INVALID);
    item = command(BREAK_RUNTIME_WORLD_COMMAND_OPEN, 0u, 0u, 7u);
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &item, 0u), BREAK_RUNTIME_INVALID);
    item = command(BREAK_RUNTIME_WORLD_COMMAND_OPEN, KEY_A, 1u, 7u);
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &item, 0u), BREAK_RUNTIME_INVALID);
    item = command(BREAK_RUNTIME_WORLD_COMMAND_CLOSE, KEY_A, 0u, 7u);
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &item, 0u), BREAK_RUNTIME_INVALID);
    item = command(BREAK_RUNTIME_WORLD_COMMAND_REBASELINE, KEY_A, 0u, 8u);
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &item, 0u), BREAK_RUNTIME_INVALID);
    item = command(BREAK_RUNTIME_WORLD_COMMAND_REBASELINE, 0u, 1u, 8u);
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &item, 0u), BREAK_RUNTIME_INVALID);
    item = command(BREAK_RUNTIME_WORLD_COMMAND_OPEN, KEY_A, 0u, 7u);
    item.target_tick = 1u;
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &item, 0u), BREAK_RUNTIME_INVALID);
    item = command(BREAK_RUNTIME_WORLD_COMMAND_ACK, KEY_A, 1u, 7u);
    item.target_snapshot_id = 2u;
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &item, 0u), BREAK_RUNTIME_INVALID);
    item.delta_id = 1u;
    item.target_snapshot_id = 0u;
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &item, 0u), BREAK_RUNTIME_INVALID);
    item = command(BREAK_RUNTIME_WORLD_COMMAND_NEED_FULL, KEY_A, 1u, 7u);
    item.delta_id = 1u;
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &item, 0u), BREAK_RUNTIME_INVALID);
    break_runtime_world_session_stats(fixture.adapter, &stats);
    ASSERT_EQ(stats.submitted, 0u);
    ASSERT_EQ(stats.next_sequence, 1u);
    ASSERT_EQ(break_world_session_level_generation(fixture.session), 7u);
    ASSERT_EQ(break_net_reactor_outbound_count(fixture.reactor), 0u);

    item = command(BREAK_RUNTIME_WORLD_COMMAND_OPEN, KEY_A, 0u, 99u);
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &item, 0u), BREAK_RUNTIME_OK);
    ASSERT_FALSE(break_world_session_baseline(fixture.session, KEY_A, NULL, NULL));
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained), BREAK_RUNTIME_STALE);
    ASSERT_EQ(drained, 1u);
    ASSERT_EQ(break_runtime_world_session_drain(NULL, 1u, &drained), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(drained, 0u);
    ASSERT_EQ(break_runtime_world_session_pending(NULL), 0u);
    ASSERT_FALSE(break_runtime_world_session_connection_epoch(NULL, KEY_A, &item.connection_epoch));
    ASSERT_EQ(item.connection_epoch, 0u);
    break_runtime_world_session_stats(NULL, &stats);
    ASSERT_EQ(stats.submitted, 0u);
    ASSERT_EQ(stats.next_sequence, 0u);
    break_runtime_world_session_close(NULL);
    fixture_dispose(&fixture);
}

TEST(open_close_reopen_capacity_and_old_epoch_are_isolated)
{
    Fixture fixture;
    BreakRuntimeWorldCommand item;
    BreakRuntimeWorldSessionStats stats;
    BreakNetOwnedMessage outbound;
    u64 epoch_a = 0u, epoch_b = 0u, old_epoch = 0u, key = 0u;
    usize drained = 0u;
    ASSERT_TRUE(fixture_init(&fixture, 7u, 2u));
    ASSERT_TRUE(open_connection(&fixture, KEY_A, 7u, &epoch_a));
    ASSERT_TRUE(open_connection(&fixture, KEY_B, 7u, &epoch_b));
    ASSERT_TRUE(epoch_b > epoch_a);
    ASSERT_TRUE(break_world_session_baseline(fixture.session, KEY_A, NULL, NULL));
    ASSERT_TRUE(break_world_session_baseline(fixture.session, KEY_B, NULL, NULL));

    item = command(BREAK_RUNTIME_WORLD_COMMAND_OPEN, KEY_A, 0u, 7u);
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &item, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained), BREAK_RUNTIME_REJECTED);
    item = command(BREAK_RUNTIME_WORLD_COMMAND_OPEN, KEY_C, 0u, 7u);
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &item, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained), BREAK_RUNTIME_REJECTED);
    ASSERT_FALSE(break_runtime_world_session_connection_epoch(fixture.adapter, KEY_C, &key));
    ASSERT_EQ(key, 0u);
    ASSERT_TRUE(break_world_session_baseline(fixture.session, KEY_B, NULL, NULL));

    item = command(BREAK_RUNTIME_WORLD_COMMAND_ACK, KEY_A, epoch_a, 7u);
    item.delta_id = 10u;
    item.target_snapshot_id = 20u;
    item.target_tick = 30u;
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &item, HIGH_CID), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained), BREAK_RUNTIME_OK);
    ASSERT_TRUE(next_control(&fixture, &key, &outbound));
    ASSERT_EQ(key, KEY_A);
    ASSERT_EQ(outbound.correlation_id, HIGH_CID);
    break_net_message_release(&outbound);
    ASSERT_TRUE(break_world_session_baseline(fixture.session, KEY_B, NULL, NULL));

    item = command(BREAK_RUNTIME_WORLD_COMMAND_CLOSE, KEY_A, epoch_a, 7u);
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &item, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained), BREAK_RUNTIME_OK);
    ASSERT_FALSE(break_world_session_baseline(fixture.session, KEY_A, NULL, NULL));
    ASSERT_TRUE(break_world_session_baseline(fixture.session, KEY_B, NULL, NULL));
    old_epoch = epoch_a;
    ASSERT_TRUE(open_connection(&fixture, KEY_A, 7u, &epoch_a));
    ASSERT_TRUE(epoch_a > old_epoch);

    item = command(BREAK_RUNTIME_WORLD_COMMAND_CLOSE, KEY_A, old_epoch, 7u);
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &item, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained), BREAK_RUNTIME_STALE);
    ASSERT_TRUE(break_world_session_baseline(fixture.session, KEY_A, NULL, NULL));
    item = command(BREAK_RUNTIME_WORLD_COMMAND_ACK, KEY_A, old_epoch, 7u);
    item.delta_id = 10u;
    item.target_snapshot_id = 20u;
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &item, HIGH_CID), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained), BREAK_RUNTIME_STALE);
    ASSERT_EQ(break_net_reactor_outbound_count(fixture.reactor), 0u);
    item = command(BREAK_RUNTIME_WORLD_COMMAND_CLOSE, KEY_C, 1u, 7u);
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &item, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained), BREAK_RUNTIME_STALE);
    break_runtime_world_session_stats(fixture.adapter, &stats);
    ASSERT_EQ(stats.stale_rejected, 3u);
    ASSERT_TRUE(break_world_session_baseline(fixture.session, KEY_B, NULL, NULL));
    fixture_dispose(&fixture);
}

TEST(level_zero_and_rebaseline_require_strict_increase)
{
    Fixture fixture;
    BreakRuntimeWorldCommand item;
    BreakNetOwnedMessage outbound;
    u64 epoch = 0u, key = 0u;
    usize drained = 0u;
    ASSERT_TRUE(fixture_init(&fixture, 0u, 2u));
    ASSERT_TRUE(open_connection(&fixture, KEY_A, 0u, &epoch));
    item = command(BREAK_RUNTIME_WORLD_COMMAND_ACK, KEY_A, epoch, 0u);
    item.delta_id = 1u;
    item.target_snapshot_id = 2u;
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &item, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained), BREAK_RUNTIME_OK);
    ASSERT_TRUE(next_control(&fixture, &key, &outbound));
    ASSERT_EQ(outbound.protocol_version, 1u);
    ASSERT_EQ(outbound.correlation_id, 0u);
    ASSERT_EQ(outbound.size, BREAK_WORLD_SESSION_CONTROL_WIRE_SIZE);
    break_net_message_release(&outbound);

    item = command(BREAK_RUNTIME_WORLD_COMMAND_REBASELINE, 0u, 0u, 0u);
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &item, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained), BREAK_RUNTIME_STALE);
    item.level_generation = 1u;
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &item, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_world_session_level_generation(fixture.session), 1u);
    ASSERT_TRUE(break_runtime_world_session_connection_epoch(fixture.adapter, KEY_A, &key));
    ASSERT_EQ(key, epoch);
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &item, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained), BREAK_RUNTIME_STALE);
    item.level_generation = 0u;
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &item, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained), BREAK_RUNTIME_STALE);
    ASSERT_EQ(break_world_session_level_generation(fixture.session), 1u);
    item = command(BREAK_RUNTIME_WORLD_COMMAND_CLOSE, KEY_A, epoch, 0u);
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &item, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained), BREAK_RUNTIME_STALE);
    ASSERT_TRUE(break_world_session_baseline(fixture.session, KEY_A, NULL, NULL));
    fixture_dispose(&fixture);
}

TEST(queued_old_level_and_level7_to8_ack_cannot_touch_new_history)
{
    Fixture fixture;
    BreakRuntimeWorldCommand rebase;
    BreakRuntimeWorldCommand old_ack;
    BreakWorldSnapshot *old_target = NULL;
    BreakWorldSnapshot *new_target = NULL;
    BreakWorldSessionSenderState state;
    u64 epoch = 0u, old_delta = 0u, new_delta = 0u, current_epoch = 0u;
    usize drained = 0u;
    ASSERT_TRUE(fixture_init(&fixture, 7u, 2u));
    ASSERT_TRUE(open_connection(&fixture, KEY_A, 7u, &epoch));
    old_target = make_target(&fixture, 10u, 10u);
    ASSERT_NOT_NULL(old_target);
    ASSERT_TRUE(publish_target(&fixture, KEY_A, old_target, 7u, &old_delta));
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_A, &state));
    ASSERT_EQ(state.history_count, 1u);

    rebase = command(BREAK_RUNTIME_WORLD_COMMAND_REBASELINE, 0u, 0u, 8u);
    old_ack = command(BREAK_RUNTIME_WORLD_COMMAND_ACK, KEY_A, epoch, 7u);
    old_ack.delta_id = old_delta;
    old_ack.target_snapshot_id = break_world_snapshot_id(old_target);
    old_ack.target_tick = break_world_snapshot_tick(old_target);
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &rebase, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &old_ack, HIGH_CID), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 2u, &drained), BREAK_RUNTIME_STALE);
    ASSERT_EQ(drained, 2u);
    ASSERT_EQ(break_world_session_level_generation(fixture.session), 8u);
    ASSERT_EQ(break_net_reactor_outbound_count(fixture.reactor), 0u);
    ASSERT_TRUE(break_runtime_world_session_connection_epoch(fixture.adapter, KEY_A, &current_epoch));
    ASSERT_EQ(current_epoch, epoch);
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_A, &state));
    ASSERT_EQ(state.history_count, 0u);

    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &rebase, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained), BREAK_RUNTIME_STALE);
    rebase.level_generation = 7u;
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &rebase, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained), BREAK_RUNTIME_STALE);
    new_target = make_target(&fixture, 20u, 20u);
    ASSERT_NOT_NULL(new_target);
    ASSERT_TRUE(publish_target(&fixture, KEY_A, new_target, 8u, &new_delta));
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_A, &state));
    ASSERT_EQ(state.history_count, 1u);
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &old_ack, HIGH_CID), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained), BREAK_RUNTIME_STALE);
    ASSERT_EQ(break_net_reactor_outbound_count(fixture.reactor), 0u);
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_A, &state));
    ASSERT_EQ(state.history_count, 1u);
    ASSERT_TRUE(control_via_adapter(&fixture, BREAK_RUNTIME_WORLD_COMMAND_ACK, KEY_A, epoch,
                                    8u, new_delta, new_target, HIGH_CID));
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_A, &state));
    ASSERT_EQ(state.history_count, 0u);
    break_world_snapshot_release(new_target);
    break_world_snapshot_release(old_target);
    fixture_dispose(&fixture);
}

TEST(correlation_and_runtime_sequence_survive_bus_queue_and_brwc)
{
    Fixture fixture;
    BreakRuntimeQueueConfig queue_config = {8u, 0u};
    BreakRuntimeQueue *observer = NULL;
    BreakRuntimeOwnedMessage *message = NULL;
    BreakRuntimeWorldCommand item;
    BreakRuntimeWorldSessionStats stats;
    BreakNetOwnedMessage outbound;
    u64 epoch = 0u, key = 0u, fresh_cid;
    u32 observer_id = 0u;
    usize drained = 0u;
    const u16 kinds[1] = {BREAK_RUNTIME_WORLD_SESSION_CONTROL_KIND};
    ASSERT_TRUE(fixture_init(&fixture, 7u, 2u));
    ASSERT_EQ(break_runtime_queue_create(&queue_config, &observer), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_bus_subscribe(fixture.bus, "observer", observer, kinds, 1u,
                                          &observer_id), BREAK_RUNTIME_OK);
    item = command(BREAK_RUNTIME_WORLD_COMMAND_OPEN, KEY_A, 0u, 7u);
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &item, 0u), BREAK_RUNTIME_OK);
    break_runtime_world_session_stats(fixture.adapter, &stats);
    ASSERT_EQ(stats.next_sequence, 2u);
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained), BREAK_RUNTIME_OK);
    ASSERT_TRUE(break_runtime_world_session_connection_epoch(fixture.adapter, KEY_A, &epoch));

    item = command(BREAK_RUNTIME_WORLD_COMMAND_ACK, KEY_A, epoch, 7u);
    item.delta_id = UINT64_C(0x100000002);
    item.target_snapshot_id = UINT64_C(0x200000003);
    item.target_tick = UINT64_C(0x300000004);
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &item, HIGH_CID), BREAK_RUNTIME_OK);
    fresh_cid = break_runtime_correlation_next();
    ASSERT_NEQ(fresh_cid, 0u);
    ASSERT_TRUE(break_runtime_correlation_next() > fresh_cid);
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &item, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &item, fresh_cid), BREAK_RUNTIME_OK);
    break_runtime_world_session_stats(fixture.adapter, &stats);
    ASSERT_EQ(stats.next_sequence, 5u);

    ASSERT_EQ(break_runtime_queue_poll(observer, &message), BREAK_RUNTIME_OK);
    ASSERT_EQ(message, NULL);
    ASSERT_EQ(break_runtime_bus_unsubscribe(fixture.bus, observer_id), BREAK_RUNTIME_OK);
    break_runtime_queue_destroy(observer);

    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 3u, &drained), BREAK_RUNTIME_OK);
    ASSERT_EQ(drained, 3u);
    ASSERT_TRUE(next_control(&fixture, &key, &outbound));
    ASSERT_EQ(key, KEY_A);
    ASSERT_EQ(outbound.correlation_id, HIGH_CID);
    ASSERT_EQ(outbound.sequence, 0u);
    ASSERT_TRUE(control_payload_matches(&outbound, BREAK_WORLD_SESSION_CONTROL_ACK,
                                        item.delta_id, item.target_snapshot_id,
                                        item.target_tick, 7u));
    break_net_message_release(&outbound);
    ASSERT_TRUE(next_control(&fixture, &key, &outbound));
    ASSERT_EQ(outbound.correlation_id, 0u);
    break_net_message_release(&outbound);
    ASSERT_TRUE(next_control(&fixture, &key, &outbound));
    ASSERT_EQ(outbound.correlation_id, fresh_cid);
    break_net_message_release(&outbound);
    fixture_dispose(&fixture);
}

TEST(need_full_ack_and_close_leave_other_connection_independent)
{
    Fixture fixture;
    BreakWorldSnapshot *a_base = NULL, *b_base = NULL;
    BreakWorldSnapshot *a_delta = NULL, *b_delta = NULL;
    BreakWorldSnapshot *a_next = NULL, *b_next = NULL;
    BreakWorldSessionSenderState a_state, b_state;
    BreakWorldSessionStats before, after;
    BreakRuntimeWorldCommand close_a;
    u64 epoch_a = 0u, epoch_b = 0u;
    u64 a_base_id = 0u, b_base_id = 0u, a_delta_id = 0u, b_delta_id = 0u;
    u64 ignored = 0u;
    usize drained = 0u;
    ASSERT_TRUE(fixture_init(&fixture, 7u, 2u));
    ASSERT_TRUE(open_connection(&fixture, KEY_A, 7u, &epoch_a));
    ASSERT_TRUE(open_connection(&fixture, KEY_B, 7u, &epoch_b));
    a_base = make_target(&fixture, 10u, 10u);
    b_base = make_target(&fixture, 11u, 11u);
    ASSERT_NOT_NULL(a_base);
    ASSERT_NOT_NULL(b_base);
    ASSERT_TRUE(publish_target(&fixture, KEY_A, a_base, 7u, &a_base_id));
    ASSERT_TRUE(publish_target(&fixture, KEY_B, b_base, 7u, &b_base_id));
    ASSERT_TRUE(control_via_adapter(&fixture, BREAK_RUNTIME_WORLD_COMMAND_ACK, KEY_A, epoch_a,
                                    7u, a_base_id, a_base, 0u));
    ASSERT_TRUE(control_via_adapter(&fixture, BREAK_RUNTIME_WORLD_COMMAND_ACK, KEY_B, epoch_b,
                                    7u, b_base_id, b_base, 0u));

    a_delta = make_target(&fixture, 20u, 20u);
    b_delta = make_target(&fixture, 21u, 21u);
    ASSERT_TRUE(publish_target(&fixture, KEY_A, a_delta, 7u, &a_delta_id));
    ASSERT_TRUE(publish_target(&fixture, KEY_B, b_delta, 7u, &b_delta_id));
    ASSERT_TRUE(control_via_adapter(&fixture, BREAK_RUNTIME_WORLD_COMMAND_ACK, KEY_A, epoch_a,
                                    7u, a_delta_id, a_delta, HIGH_CID));
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_A, &a_state));
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_B, &b_state));
    ASSERT_EQ(a_state.history_count, 0u);
    ASSERT_EQ(a_state.confirmed_snapshot_id, break_world_snapshot_id(a_delta));
    ASSERT_EQ(b_state.history_count, 1u);
    ASSERT_EQ(b_state.confirmed_snapshot_id, break_world_snapshot_id(b_base));

    ASSERT_TRUE(control_via_adapter(&fixture, BREAK_RUNTIME_WORLD_COMMAND_NEED_FULL, KEY_A,
                                    epoch_a, 7u, 0u, a_delta, HIGH_CID));
    break_world_session_stats(fixture.session, &before);
    a_next = make_target(&fixture, 30u, 30u);
    b_next = make_target(&fixture, 31u, 31u);
    ASSERT_TRUE(publish_target(&fixture, KEY_A, a_next, 7u, &ignored));
    ASSERT_TRUE(publish_target(&fixture, KEY_B, b_next, 7u, &ignored));
    break_world_session_stats(fixture.session, &after);
    ASSERT_EQ(after.published_full_packets, before.published_full_packets + 1u);
    ASSERT_EQ(after.published_delta_packets, before.published_delta_packets + 1u);
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_B, &b_state));
    ASSERT_EQ(b_state.history_count, 2u);

    close_a = command(BREAK_RUNTIME_WORLD_COMMAND_CLOSE, KEY_A, epoch_a, 7u);
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &close_a, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained), BREAK_RUNTIME_OK);
    ASSERT_FALSE(break_world_session_baseline(fixture.session, KEY_A, NULL, NULL));
    ASSERT_TRUE(break_world_session_baseline(fixture.session, KEY_B, NULL, NULL));
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_B, &b_state));
    ASSERT_EQ(b_state.history_count, 2u);
    break_world_snapshot_release(b_next);
    break_world_snapshot_release(a_next);
    break_world_snapshot_release(b_delta);
    break_world_snapshot_release(a_delta);
    break_world_snapshot_release(b_base);
    break_world_snapshot_release(a_base);
    fixture_dispose(&fixture);
}

TEST(queue_overload_defers_world_and_retries_identical_command)
{
    Fixture fixture;
    BreakRuntimeWorldCommand need_full;
    BreakRuntimeWorldCommand ack;
    BreakRuntimeWorldSessionStats stats;
    BreakWorldSessionStats world_before;
    BreakWorldSessionStats world_after;
    BreakWorldSessionSenderState sender_before;
    BreakWorldSessionSenderState sender_after;
    BreakNetOwnedMessage outbound;
    u64 epoch = 0u, current_epoch = 0u, key = 0u;
    usize drained = 99u;
    ASSERT_TRUE(fixture_init_without_adapter(&fixture, 7u));
    ASSERT_TRUE(fixture_attach(&fixture, 1u, 2u));
    ASSERT_TRUE(open_connection(&fixture, KEY_A, 7u, &epoch));
    need_full = command(BREAK_RUNTIME_WORLD_COMMAND_NEED_FULL, KEY_A, epoch, 7u);
    need_full.target_snapshot_id = 11u;
    need_full.target_tick = 101u;
    ack = command(BREAK_RUNTIME_WORLD_COMMAND_ACK, KEY_A, epoch, 7u);
    ack.delta_id = UINT64_C(0x10000000A);
    ack.target_snapshot_id = UINT64_C(0x20000000B);
    ack.target_tick = 77u;
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &need_full, 1u),
              BREAK_RUNTIME_OK);
    break_world_session_stats(fixture.session, &world_before);
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_A, &sender_before));
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &ack, HIGH_CID),
              BREAK_RUNTIME_OVERLOAD);
    break_world_session_stats(fixture.session, &world_after);
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_A, &sender_after));
    ASSERT_EQ(memcmp(&world_before, &world_after, sizeof(world_before)), 0);
    ASSERT_EQ(memcmp(&sender_before, &sender_after, sizeof(sender_before)), 0);
    ASSERT_EQ(break_net_reactor_outbound_count(fixture.reactor), 0u);
    break_runtime_world_session_stats(fixture.adapter, &stats);
    ASSERT_EQ(stats.submitted, 2u);
    ASSERT_EQ(stats.drained, 1u);
    ASSERT_EQ(stats.applied, 1u);
    ASSERT_EQ(stats.rejected, 0u);
    ASSERT_EQ(stats.next_sequence, 3u);
    ASSERT_EQ(stats.queued, 1u);
    ASSERT_EQ(stats.transport_overloads, 0u);

    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(drained, 1u);
    ASSERT_TRUE(next_control(&fixture, &key, &outbound));
    ASSERT_EQ(key, KEY_A);
    ASSERT_EQ(outbound.correlation_id, 1u);
    ASSERT_TRUE(control_payload_matches(&outbound, BREAK_WORLD_SESSION_CONTROL_NEED_FULL,
                                        0u, 11u, 101u, 7u));
    break_net_message_release(&outbound);
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &ack, HIGH_CID),
              BREAK_RUNTIME_OK);
    break_runtime_world_session_stats(fixture.adapter, &stats);
    ASSERT_EQ(stats.submitted, 3u);
    ASSERT_EQ(stats.next_sequence, 4u);
    ASSERT_EQ(stats.queued, 1u);
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(drained, 1u);
    ASSERT_TRUE(next_control(&fixture, &key, &outbound));
    ASSERT_EQ(key, KEY_A);
    ASSERT_EQ(outbound.correlation_id, HIGH_CID);
    ASSERT_TRUE(control_payload_matches(&outbound, BREAK_WORLD_SESSION_CONTROL_ACK,
                                        UINT64_C(0x10000000A), UINT64_C(0x20000000B),
                                        77u, 7u));
    break_net_message_release(&outbound);
    ASSERT_EQ(break_net_reactor_outbound_count(fixture.reactor), 0u);
    ASSERT_TRUE(break_runtime_world_session_connection_epoch(fixture.adapter, KEY_A,
                                                              &current_epoch));
    ASSERT_EQ(current_epoch, epoch);
    break_runtime_world_session_stats(fixture.adapter, &stats);
    ASSERT_EQ(stats.submitted, 3u);
    ASSERT_EQ(stats.drained, 3u);
    ASSERT_EQ(stats.applied, 3u);
    ASSERT_EQ(stats.rejected, 0u);
    ASSERT_EQ(stats.next_sequence, 4u);
    ASSERT_EQ(stats.queued, 0u);
    ASSERT_EQ(stats.transport_overloads, 0u);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 0u);
    fixture_dispose(&fixture);
}

TEST(fifo_bounded_drain_close_and_destroy_preserve_world_lifetime)
{
    Fixture fixture;
    BreakRuntimeWorldCommand item;
    BreakNetOwnedMessage outbound;
    BreakRuntimeMessageView view;
    BreakRuntimeWorldSessionStats stats;
    u64 epoch_a = 0u, epoch_b = 0u, key = 0u;
    usize drained = 99u;
    u32 delivered = 99u;
    ASSERT_TRUE(fixture_init(&fixture, 7u, 2u));
    ASSERT_TRUE(open_connection(&fixture, KEY_A, 7u, &epoch_a));
    ASSERT_TRUE(open_connection(&fixture, KEY_B, 7u, &epoch_b));
    item = command(BREAK_RUNTIME_WORLD_COMMAND_NEED_FULL, KEY_A, epoch_a, 7u);
    item.target_snapshot_id = 11u;
    item.target_tick = 101u;
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &item, 1u), BREAK_RUNTIME_OK);
    item = command(BREAK_RUNTIME_WORLD_COMMAND_NEED_FULL, KEY_B, epoch_b, 7u);
    item.target_snapshot_id = 22u;
    item.target_tick = 201u;
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &item, 2u), BREAK_RUNTIME_OK);
    item = command(BREAK_RUNTIME_WORLD_COMMAND_NEED_FULL, KEY_A, epoch_a, 7u);
    item.target_snapshot_id = 33u;
    item.target_tick = 102u;
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &item, 3u), BREAK_RUNTIME_OK);
    break_runtime_world_session_close(fixture.adapter);
    break_runtime_world_session_close(fixture.adapter);
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &item, 4u), BREAK_RUNTIME_CLOSED);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 3u);
    ASSERT_FALSE(break_runtime_world_session_destroy(fixture.adapter));
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 3u);
    ASSERT_TRUE(break_runtime_world_session_connection_epoch(fixture.adapter, KEY_A, &key));
    ASSERT_EQ(key, epoch_a);
    ASSERT_TRUE(break_runtime_world_session_connection_epoch(fixture.adapter, KEY_B, &key));
    ASSERT_EQ(key, epoch_b);
    ASSERT_TRUE(break_world_session_baseline(fixture.session, KEY_A, NULL, NULL));
    ASSERT_TRUE(break_world_session_baseline(fixture.session, KEY_B, NULL, NULL));
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 2u, &drained), BREAK_RUNTIME_OK);
    ASSERT_EQ(drained, 2u);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 1u);
    ASSERT_FALSE(break_runtime_world_session_destroy(fixture.adapter));
    ASSERT_TRUE(break_runtime_world_session_connection_epoch(fixture.adapter, KEY_A, &key));
    ASSERT_EQ(key, epoch_a);
    ASSERT_TRUE(break_world_session_baseline(fixture.session, KEY_A, NULL, NULL));
    ASSERT_TRUE(break_world_session_baseline(fixture.session, KEY_B, NULL, NULL));
    break_runtime_world_session_stats(fixture.adapter, &stats);
    ASSERT_EQ(stats.submitted, 5u);
    ASSERT_EQ(stats.drained, 4u);
    ASSERT_EQ(stats.applied, 4u);
    ASSERT_EQ(stats.rejected, 0u);
    ASSERT_EQ(stats.queued, 1u);
    ASSERT_TRUE(next_control(&fixture, &key, &outbound));
    ASSERT_EQ(key, KEY_A);
    ASSERT_EQ(outbound.correlation_id, 1u);
    ASSERT_TRUE(control_payload_matches(&outbound, BREAK_WORLD_SESSION_CONTROL_NEED_FULL,
                                        0u, 11u, 101u, 7u));
    break_net_message_release(&outbound);
    ASSERT_TRUE(next_control(&fixture, &key, &outbound));
    ASSERT_EQ(key, KEY_B);
    ASSERT_EQ(outbound.correlation_id, 2u);
    ASSERT_TRUE(control_payload_matches(&outbound, BREAK_WORLD_SESSION_CONTROL_NEED_FULL,
                                        0u, 22u, 201u, 7u));
    break_net_message_release(&outbound);
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 0u, &drained), BREAK_RUNTIME_OK);
    ASSERT_EQ(drained, 0u);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 1u);
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained), BREAK_RUNTIME_OK);
    ASSERT_EQ(drained, 1u);
    ASSERT_TRUE(next_control(&fixture, &key, &outbound));
    ASSERT_EQ(key, KEY_A);
    ASSERT_EQ(outbound.correlation_id, 3u);
    ASSERT_TRUE(control_payload_matches(&outbound, BREAK_WORLD_SESSION_CONTROL_NEED_FULL,
                                        0u, 33u, 102u, 7u));
    break_net_message_release(&outbound);
    ASSERT_EQ(break_net_reactor_outbound_count(fixture.reactor), 0u);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 0u);
    break_runtime_world_session_stats(fixture.adapter, &stats);
    ASSERT_EQ(stats.submitted, 5u);
    ASSERT_EQ(stats.drained, 5u);
    ASSERT_EQ(stats.applied, 5u);
    ASSERT_EQ(stats.rejected, 0u);
    ASSERT_EQ(stats.transport_overloads, 0u);
    ASSERT_EQ(stats.queued, 0u);
    ASSERT_FALSE(stats.control_pending);
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(drained, 0u);
    ASSERT_EQ(break_net_reactor_outbound_count(fixture.reactor), 0u);
    ASSERT_TRUE(break_runtime_world_session_destroy(fixture.adapter));
    fixture.adapter = NULL;
    ASSERT_TRUE(break_world_session_baseline(fixture.session, KEY_A, NULL, NULL));
    ASSERT_TRUE(break_world_session_baseline(fixture.session, KEY_B, NULL, NULL));
    memset(&view, 0, sizeof(view));
    view.kind = BREAK_RUNTIME_WORLD_SESSION_CONTROL_KIND;
    view.version = 1u;
    view.data = &item;
    view.size = sizeof(item);
    ASSERT_EQ(break_runtime_bus_publish(fixture.bus, &view, &delivered), BREAK_RUNTIME_OK);
    ASSERT_EQ(delivered, 0u);
    fixture_dispose(&fixture);
}

TEST(transport_overload_retries_same_control_before_fifo)
{
    Fixture fixture;
    BreakRuntimeWorldCommand ack;
    BreakRuntimeWorldCommand need_full;
    BreakRuntimeWorldSessionStats stats;
    BreakNetOwnedMessage outbound;
    u64 epoch_a = 0u, epoch_b = 0u, key = 0u;
    usize drained = 99u;
    ASSERT_TRUE(fixture_init(&fixture, 7u, 2u));
    ASSERT_TRUE(open_connection(&fixture, KEY_A, 7u, &epoch_a));
    ASSERT_TRUE(open_connection(&fixture, KEY_B, 7u, &epoch_b));
    ack = command(BREAK_RUNTIME_WORLD_COMMAND_ACK, KEY_A, epoch_a, 7u);
    ack.delta_id = UINT64_C(0x10000000A);
    ack.target_snapshot_id = UINT64_C(0x20000000B);
    ack.target_tick = 77u;
    need_full = command(BREAK_RUNTIME_WORLD_COMMAND_NEED_FULL, KEY_B, epoch_b, 7u);
    need_full.target_snapshot_id = 88u;
    need_full.target_tick = 99u;
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &ack, HIGH_CID), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &need_full, 0u), BREAK_RUNTIME_OK);
    for (u32 i = 0u; i < BREAK_NET_OUTBOUND_QUEUE_CAPACITY; ++i) {
        ASSERT_EQ(break_net_reactor_send(fixture.reactor, KEY_A, BREAK_NET_MESSAGE_ID_PING,
                                         1u, "x", 1u), BREAK_NET_SEND_OK);
    }
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 2u, &drained), BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(drained, 1u);
    break_runtime_world_session_stats(fixture.adapter, &stats);
    ASSERT_EQ(stats.submitted, 4u);
    ASSERT_EQ(stats.drained, 3u);
    ASSERT_EQ(stats.applied, 2u);
    ASSERT_EQ(stats.transport_overloads, 1u);
    ASSERT_EQ(stats.queued, 1u);
    ASSERT_TRUE(stats.control_pending);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 2u);
    ASSERT_FALSE(break_runtime_world_session_destroy(fixture.adapter));
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 2u, &drained), BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(drained, 0u);
    break_runtime_world_session_stats(fixture.adapter, &stats);
    ASSERT_EQ(stats.transport_overloads, 2u);
    ASSERT_EQ(stats.applied, 2u);
    clear_outbound(&fixture);
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 2u, &drained), BREAK_RUNTIME_OK);
    ASSERT_EQ(drained, 1u);
    break_runtime_world_session_stats(fixture.adapter, &stats);
    ASSERT_EQ(stats.drained, 4u);
    ASSERT_EQ(stats.applied, 4u);
    ASSERT_EQ(stats.transport_overloads, 2u);
    ASSERT_EQ(stats.queued, 0u);
    ASSERT_FALSE(stats.control_pending);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 0u);
    ASSERT_TRUE(next_control(&fixture, &key, &outbound));
    ASSERT_EQ(key, KEY_A);
    ASSERT_EQ(outbound.correlation_id, HIGH_CID);
    ASSERT_TRUE(control_payload_matches(&outbound, BREAK_WORLD_SESSION_CONTROL_ACK,
                                        ack.delta_id, ack.target_snapshot_id,
                                        ack.target_tick, 7u));
    break_net_message_release(&outbound);
    ASSERT_TRUE(next_control(&fixture, &key, &outbound));
    ASSERT_EQ(key, KEY_B);
    ASSERT_EQ(outbound.correlation_id, 0u);
    ASSERT_TRUE(control_payload_matches(&outbound, BREAK_WORLD_SESSION_CONTROL_NEED_FULL,
                                        0u, 88u, 99u, 7u));
    break_net_message_release(&outbound);
    ASSERT_TRUE(break_runtime_world_session_destroy(fixture.adapter));
    fixture.adapter = NULL;
    fixture_dispose(&fixture);
}

TEST(transport_overload_retries_need_full_before_later_ack)
{
    Fixture fixture;
    BreakRuntimeWorldCommand need_full;
    BreakRuntimeWorldCommand ack;
    BreakRuntimeWorldSessionStats stats;
    BreakNetOwnedMessage outbound;
    u64 epoch_a = 0u, epoch_b = 0u, current_epoch = 0u, key = 0u;
    usize drained = 99u;
    ASSERT_TRUE(fixture_init(&fixture, 7u, 2u));
    ASSERT_TRUE(open_connection(&fixture, KEY_A, 7u, &epoch_a));
    ASSERT_TRUE(open_connection(&fixture, KEY_B, 7u, &epoch_b));
    need_full = command(BREAK_RUNTIME_WORLD_COMMAND_NEED_FULL, KEY_A, epoch_a, 7u);
    need_full.target_snapshot_id = UINT64_C(0x20000000C);
    need_full.target_tick = 101u;
    ack = command(BREAK_RUNTIME_WORLD_COMMAND_ACK, KEY_B, epoch_b, 7u);
    ack.delta_id = UINT64_C(0x10000000D);
    ack.target_snapshot_id = UINT64_C(0x20000000E);
    ack.target_tick = 202u;
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &need_full, HIGH_CID),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &ack, HIGH_CID - 1u),
              BREAK_RUNTIME_OK);
    for (u32 i = 0u; i < BREAK_NET_OUTBOUND_QUEUE_CAPACITY; ++i) {
        ASSERT_EQ(break_net_reactor_send(fixture.reactor, KEY_A, BREAK_NET_MESSAGE_ID_PING,
                                         1u, "x", 1u), BREAK_NET_SEND_OK);
    }
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 2u, &drained),
              BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(drained, 1u);
    break_runtime_world_session_stats(fixture.adapter, &stats);
    ASSERT_EQ(stats.submitted, 4u);
    ASSERT_EQ(stats.drained, 3u);
    ASSERT_EQ(stats.applied, 2u);
    ASSERT_EQ(stats.rejected, 0u);
    ASSERT_EQ(stats.transport_overloads, 1u);
    ASSERT_EQ(stats.queued, 1u);
    ASSERT_TRUE(stats.control_pending);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 2u);
    ASSERT_FALSE(break_runtime_world_session_destroy(fixture.adapter));
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &ack, HIGH_CID + 1u),
              BREAK_RUNTIME_CLOSED);
    {
        u32 delivered = 99u;
        (void)publish_external(fixture.bus, &ack, HIGH_CID + 2u, &delivered);
        ASSERT_EQ(delivered, 0u);
    }
    ASSERT_TRUE(break_runtime_world_session_connection_epoch(fixture.adapter, KEY_A,
                                                              &current_epoch));
    ASSERT_EQ(current_epoch, epoch_a);
    ASSERT_TRUE(break_runtime_world_session_connection_epoch(fixture.adapter, KEY_B,
                                                              &current_epoch));
    ASSERT_EQ(current_epoch, epoch_b);
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 2u, &drained),
              BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(drained, 0u);
    break_runtime_world_session_stats(fixture.adapter, &stats);
    ASSERT_EQ(stats.drained, 3u);
    ASSERT_EQ(stats.applied, 2u);
    ASSERT_EQ(stats.transport_overloads, 2u);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 2u);
    clear_outbound(&fixture);
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 2u, &drained),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(drained, 1u);
    break_runtime_world_session_stats(fixture.adapter, &stats);
    ASSERT_EQ(stats.submitted, 4u);
    ASSERT_EQ(stats.drained, 4u);
    ASSERT_EQ(stats.applied, 4u);
    ASSERT_EQ(stats.rejected, 0u);
    ASSERT_EQ(stats.transport_overloads, 2u);
    ASSERT_EQ(stats.queued, 0u);
    ASSERT_FALSE(stats.control_pending);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 0u);
    ASSERT_TRUE(next_control(&fixture, &key, &outbound));
    ASSERT_EQ(key, KEY_A);
    ASSERT_EQ(outbound.correlation_id, HIGH_CID);
    ASSERT_TRUE(control_payload_matches(&outbound, BREAK_WORLD_SESSION_CONTROL_NEED_FULL,
                                        0u, UINT64_C(0x20000000C), 101u, 7u));
    break_net_message_release(&outbound);
    ASSERT_TRUE(next_control(&fixture, &key, &outbound));
    ASSERT_EQ(key, KEY_B);
    ASSERT_EQ(outbound.correlation_id, HIGH_CID - 1u);
    ASSERT_TRUE(control_payload_matches(&outbound, BREAK_WORLD_SESSION_CONTROL_ACK,
                                        UINT64_C(0x10000000D), UINT64_C(0x20000000E),
                                        202u, 7u));
    break_net_message_release(&outbound);
    ASSERT_EQ(break_net_reactor_outbound_count(fixture.reactor), 0u);
    ASSERT_TRUE(break_runtime_world_session_connection_epoch(fixture.adapter, KEY_A,
                                                              &current_epoch));
    ASSERT_EQ(current_epoch, epoch_a);
    ASSERT_TRUE(break_runtime_world_session_connection_epoch(fixture.adapter, KEY_B,
                                                              &current_epoch));
    ASSERT_EQ(current_epoch, epoch_b);
    ASSERT_TRUE(break_runtime_world_session_destroy(fixture.adapter));
    fixture.adapter = NULL;
    fixture_dispose(&fixture);
}

TEST(terminal_pending_result_is_counted_and_released)
{
    Fixture fixture;
    BreakRuntimeWorldCommand ack;
    BreakRuntimeWorldSessionStats stats;
    u64 epoch = 0u;
    usize drained = 99u;
    ASSERT_TRUE(fixture_init(&fixture, 7u, 2u));
    ASSERT_TRUE(open_connection(&fixture, KEY_A, 7u, &epoch));
    ack = command(BREAK_RUNTIME_WORLD_COMMAND_ACK, KEY_A, epoch, 7u);
    ack.delta_id = 1u;
    ack.target_snapshot_id = 2u;
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &ack, HIGH_CID), BREAK_RUNTIME_OK);
    for (u32 i = 0u; i < BREAK_NET_OUTBOUND_QUEUE_CAPACITY; ++i) {
        ASSERT_EQ(break_net_reactor_send(fixture.reactor, KEY_A, BREAK_NET_MESSAGE_ID_PING,
                                         1u, "x", 1u), BREAK_NET_SEND_OK);
    }
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained), BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(drained, 1u);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 1u);
    ASSERT_TRUE(break_net_reactor_stop(fixture.reactor, 1000u));
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained), BREAK_RUNTIME_CLOSED);
    ASSERT_EQ(drained, 0u);
    break_runtime_world_session_stats(fixture.adapter, &stats);
    ASSERT_EQ(stats.applied, 1u);
    ASSERT_EQ(stats.rejected, 1u);
    ASSERT_EQ(stats.transport_overloads, 1u);
    ASSERT_FALSE(stats.control_pending);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 0u);
    ASSERT_TRUE(break_runtime_world_session_destroy(fixture.adapter));
    fixture.adapter = NULL;
    fixture_dispose(&fixture);
}

#define CONCURRENT_ATTEMPTS 32u
#define CONCURRENT_DIRECT_CID UINT64_C(0xD000)
#define CONCURRENT_EXTERNAL_CID UINT64_C(0xE000)

typedef struct {
    _Atomic u32 go;
    _Atomic u32 stop;
    _Atomic u32 direct_accepted;
    _Atomic u32 external_accepted;
} ConcurrentShared;

typedef struct {
    Fixture *fixture;
    BreakRuntimeWorldSession *adapter;
    ConcurrentShared *shared;
    u64 epoch;
    bool external;
    bool accepted[CONCURRENT_ATTEMPTS];
} ConcurrentProducer;

typedef struct {
    BreakRuntimeWorldSession *adapter;
    ConcurrentShared *shared;
} ConcurrentDrain;

typedef struct {
    BreakRuntimeWorldSession *adapter;
    bool result;
} ConcurrentDestroy;

static PLATFORM_THREAD_RET concurrent_producer_main(PLATFORM_THREAD_ARG argument)
{
    ConcurrentProducer *producer = (ConcurrentProducer *)argument;
    while (!atomic_load_explicit(&producer->shared->go, memory_order_relaxed)) {
        platform_thread_yield();
    }
    for (u32 i = 0u; i < CONCURRENT_ATTEMPTS; ++i) {
        BreakRuntimeWorldCommand item = command(BREAK_RUNTIME_WORLD_COMMAND_ACK, KEY_A,
                                                producer->epoch, 7u);
        u64 cid = (producer->external ? CONCURRENT_EXTERNAL_CID : CONCURRENT_DIRECT_CID) + i;
        bool accepted = false;
        item.delta_id = (u64)i + 1u;
        item.target_snapshot_id = (producer->external ? 2000u : 1000u) + (u64)i;
        item.target_tick = 3000u + (u64)i;
        if (producer->external) {
            u32 delivered = 0u;
            BreakRuntimeError result = publish_external(producer->fixture->bus, &item, cid,
                                                        &delivered);
            accepted = result == BREAK_RUNTIME_OK && delivered == 1u;
            if (accepted) {
                atomic_fetch_add_explicit(&producer->shared->external_accepted, 1u,
                                          memory_order_relaxed);
            }
        } else {
            accepted = break_runtime_world_session_submit(producer->adapter, &item, cid) ==
                       BREAK_RUNTIME_OK;
            if (accepted) {
                atomic_fetch_add_explicit(&producer->shared->direct_accepted, 1u,
                                          memory_order_relaxed);
            }
        }
        producer->accepted[i] = accepted;
        platform_thread_yield();
    }
    return PLATFORM_THREAD_RETURN;
}

static PLATFORM_THREAD_RET concurrent_drain_main(PLATFORM_THREAD_ARG argument)
{
    ConcurrentDrain *drain = (ConcurrentDrain *)argument;
    while (!atomic_load_explicit(&drain->shared->go, memory_order_relaxed)) {
        platform_thread_yield();
    }
    while (!atomic_load_explicit(&drain->shared->stop, memory_order_relaxed)) {
        usize drained = 0u;
        (void)break_runtime_world_session_drain(drain->adapter, 8u, &drained);
        if (drained == 0u) platform_thread_yield();
    }
    return PLATFORM_THREAD_RETURN;
}

static PLATFORM_THREAD_RET concurrent_destroy_main(PLATFORM_THREAD_ARG argument)
{
    ConcurrentDestroy *destroy = (ConcurrentDestroy *)argument;
    destroy->result = break_runtime_world_session_destroy(destroy->adapter);
    return PLATFORM_THREAD_RETURN;
}

TEST(concurrent_ingress_close_drain_and_destroy_preserve_exactly_once)
{
    Fixture fixture;
    ConcurrentShared shared;
    ConcurrentProducer direct;
    ConcurrentProducer external;
    ConcurrentDrain drain;
    ConcurrentDestroy destroy;
    BreakRuntimeWorldCommand item;
    BreakRuntimeWorldSessionStats stats;
    BreakNetOwnedMessage outbound;
    PlatformThread threads[3];
    PlatformThread destroy_thread;
    bool direct_seen[CONCURRENT_ATTEMPTS] = {false};
    bool external_seen[CONCURRENT_ATTEMPTS] = {false};
    u64 epoch = 0u, key = 0u;
    u32 expected_direct;
    u32 expected_external;
    u32 output_count = 0u;
    usize drained = 0u;
    bool ready = false;
    ASSERT_TRUE(fixture_init(&fixture, 7u, 2u));
    ASSERT_TRUE(open_connection(&fixture, KEY_A, 7u, &epoch));
    for (u32 i = 0u; i < BREAK_NET_OUTBOUND_QUEUE_CAPACITY; ++i) {
        ASSERT_EQ(break_net_reactor_send(fixture.reactor, KEY_A, BREAK_NET_MESSAGE_ID_PING,
                                         1u, "x", 1u), BREAK_NET_SEND_OK);
    }
    memset(&direct, 0, sizeof(direct));
    memset(&external, 0, sizeof(external));
    memset(&drain, 0, sizeof(drain));
    memset(&destroy, 0, sizeof(destroy));
    atomic_init(&shared.go, 0u);
    atomic_init(&shared.stop, 0u);
    atomic_init(&shared.direct_accepted, 0u);
    atomic_init(&shared.external_accepted, 0u);
    direct.fixture = &fixture;
    direct.adapter = fixture.adapter;
    direct.shared = &shared;
    direct.epoch = epoch;
    external = direct;
    external.external = true;
    drain.adapter = fixture.adapter;
    drain.shared = &shared;
    destroy.adapter = fixture.adapter;
    ASSERT_TRUE(platform_thread_create(&threads[0], concurrent_producer_main, &direct));
    ASSERT_TRUE(platform_thread_create(&threads[1], concurrent_producer_main, &external));
    ASSERT_TRUE(platform_thread_create(&threads[2], concurrent_drain_main, &drain));
    atomic_store_explicit(&shared.go, 1u, memory_order_relaxed);
    for (u32 spin = 0u; spin < 1000000u && !ready; ++spin) {
        break_runtime_world_session_stats(fixture.adapter, &stats);
        ready = stats.control_pending &&
                atomic_load_explicit(&shared.external_accepted, memory_order_relaxed) != 0u;
        if (!ready) platform_thread_yield();
    }
    if (!ready) {
        break_runtime_world_session_close(fixture.adapter);
        atomic_store_explicit(&shared.stop, 1u, memory_order_relaxed);
        for (u32 i = 0u; i < 3u; ++i) platform_thread_join(threads[i]);
        clear_outbound(&fixture);
        fixture_dispose(&fixture);
        ASSERT_TRUE(ready);
        return;
    }
    break_runtime_world_session_close(fixture.adapter);
    ASSERT_TRUE(platform_thread_create(&destroy_thread, concurrent_destroy_main, &destroy));
    platform_thread_join(destroy_thread);
    ASSERT_FALSE(destroy.result);
    item = command(BREAK_RUNTIME_WORLD_COMMAND_ACK, KEY_A, epoch, 7u);
    item.delta_id = 99u;
    item.target_snapshot_id = 99u;
    {
        u32 delivered = 99u;
        (void)publish_external(fixture.bus, &item, HIGH_CID, &delivered);
        ASSERT_EQ(delivered, 0u);
    }
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &item, HIGH_CID),
              BREAK_RUNTIME_CLOSED);
    atomic_store_explicit(&shared.stop, 1u, memory_order_relaxed);
    for (u32 i = 0u; i < 3u; ++i) platform_thread_join(threads[i]);
    expected_direct = atomic_load_explicit(&shared.direct_accepted, memory_order_relaxed);
    expected_external = atomic_load_explicit(&shared.external_accepted, memory_order_relaxed);
    ASSERT_TRUE(expected_external != 0u);
    clear_outbound(&fixture);

    for (u32 round = 0u; round < 4u; ++round) {
        (void)break_runtime_world_session_drain(fixture.adapter, 256u, &drained);
        while (next_control(&fixture, &key, &outbound)) {
            bool external_message = outbound.correlation_id >= CONCURRENT_EXTERNAL_CID &&
                                    outbound.correlation_id < CONCURRENT_EXTERNAL_CID +
                                        CONCURRENT_ATTEMPTS;
            bool direct_message = outbound.correlation_id >= CONCURRENT_DIRECT_CID &&
                                  outbound.correlation_id < CONCURRENT_DIRECT_CID +
                                      CONCURRENT_ATTEMPTS;
            u32 index = external_message
                            ? (u32)(outbound.correlation_id - CONCURRENT_EXTERNAL_CID)
                            : (u32)(outbound.correlation_id - CONCURRENT_DIRECT_CID);
            bool valid = key == KEY_A && (external_message || direct_message) &&
                         index < CONCURRENT_ATTEMPTS;
            if (valid) {
                ConcurrentProducer *producer = external_message ? &external : &direct;
                bool *seen = external_message ? external_seen : direct_seen;
                valid = producer->accepted[index] && !seen[index] &&
                        control_payload_matches(&outbound, BREAK_WORLD_SESSION_CONTROL_ACK,
                                                (u64)index + 1u,
                                                (external_message ? 2000u : 1000u) + (u64)index,
                                                3000u + (u64)index, 7u);
                seen[index] = true;
            }
            break_net_message_release(&outbound);
            ASSERT_TRUE(valid);
            output_count++;
        }
        if (break_runtime_world_session_pending(fixture.adapter) == 0u) break;
    }
    ASSERT_EQ(output_count, expected_direct + expected_external);
    for (u32 i = 0u; i < CONCURRENT_ATTEMPTS; ++i) {
        ASSERT_EQ(direct_seen[i], direct.accepted[i]);
        ASSERT_EQ(external_seen[i], external.accepted[i]);
    }
    break_runtime_world_session_stats(fixture.adapter, &stats);
    ASSERT_EQ(stats.submitted, 1u + expected_direct);
    ASSERT_EQ(stats.drained, 1u + expected_direct + expected_external);
    ASSERT_EQ(stats.applied, 1u + expected_direct + expected_external);
    ASSERT_EQ(stats.next_sequence, 2u + expected_direct);
    ASSERT_EQ(stats.queued, 0u);
    ASSERT_FALSE(stats.control_pending);
    ASSERT_TRUE(stats.transport_overloads != 0u);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 0u);
    ASSERT_TRUE(break_runtime_world_session_destroy(fixture.adapter));
    fixture.adapter = NULL;
    fixture_dispose(&fixture);
}

TEST(external_bus_ingress_uses_actual_queue_accounting)
{
    Fixture fixture;
    BreakRuntimeWorldCommand item;
    BreakRuntimeWorldSessionStats stats;
    BreakNetOwnedMessage outbound;
    u64 epoch = 0u, key = 0u;
    u32 delivered = 0u;
    usize drained = 0u;
    ASSERT_TRUE(fixture_init(&fixture, 7u, 2u));
    item = command(BREAK_RUNTIME_WORLD_COMMAND_OPEN, KEY_A, 0u, 7u);
    ASSERT_EQ(publish_external(fixture.bus, &item, 0u, &delivered), BREAK_RUNTIME_OK);
    ASSERT_EQ(delivered, 1u);
    break_runtime_world_session_stats(fixture.adapter, &stats);
    ASSERT_EQ(stats.submitted, 0u);
    ASSERT_EQ(stats.drained, 0u);
    ASSERT_EQ(stats.queued, 1u);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 1u);
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained), BREAK_RUNTIME_OK);
    ASSERT_EQ(drained, 1u);
    ASSERT_TRUE(break_runtime_world_session_connection_epoch(fixture.adapter, KEY_A, &epoch));
    break_runtime_world_session_stats(fixture.adapter, &stats);
    ASSERT_EQ(stats.submitted, 0u);
    ASSERT_EQ(stats.drained, 1u);
    ASSERT_EQ(stats.queued, 0u);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 0u);

    item = command(BREAK_RUNTIME_WORLD_COMMAND_ACK, KEY_A, epoch, 7u);
    item.delta_id = 11u;
    item.target_snapshot_id = 22u;
    item.target_tick = 33u;
    ASSERT_EQ(publish_external(fixture.bus, &item, HIGH_CID, &delivered), BREAK_RUNTIME_OK);
    ASSERT_EQ(delivered, 1u);
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained), BREAK_RUNTIME_OK);
    ASSERT_EQ(drained, 1u);
    ASSERT_TRUE(next_control(&fixture, &key, &outbound));
    ASSERT_EQ(key, KEY_A);
    ASSERT_EQ(outbound.correlation_id, HIGH_CID);
    break_net_message_release(&outbound);
    break_runtime_world_session_stats(fixture.adapter, &stats);
    ASSERT_EQ(stats.submitted, 0u);
    ASSERT_EQ(stats.drained, 2u);
    ASSERT_EQ(stats.applied, 2u);
    ASSERT_EQ(stats.queued, 0u);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 0u);
    ASSERT_TRUE(break_runtime_world_session_destroy(fixture.adapter));
    fixture.adapter = NULL;
    fixture_dispose(&fixture);
}

TEST(two_adapters_isolate_direct_submit_from_external_fanout)
{
    Fixture fixture;
    BreakRuntimeWorldSessionConfig config;
    BreakRuntimeWorldSession *second = NULL;
    BreakRuntimeWorldCommand item;
    BreakRuntimeWorldSessionStats first_stats;
    BreakRuntimeWorldSessionStats second_stats;
    BreakNetOwnedMessage outbound;
    u64 epoch_a = 0u, epoch_b = 0u, key = 0u;
    u32 delivered = 0u;
    usize drained = 0u;
    ASSERT_TRUE(fixture_init(&fixture, 7u, 2u));
    memset(&config, 0, sizeof(config));
    config.session = fixture.session;
    config.bus = fixture.bus;
    config.subscriber_name = "world_session.second";
    config.max_connections = 2u;
    second = break_runtime_world_session_create(&config);
    ASSERT_NOT_NULL(second);

    item = command(BREAK_RUNTIME_WORLD_COMMAND_OPEN, KEY_A, 0u, 7u);
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &item, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 1u);
    ASSERT_EQ(break_runtime_world_session_pending(second), 0u);
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained), BREAK_RUNTIME_OK);
    ASSERT_TRUE(break_runtime_world_session_connection_epoch(fixture.adapter, KEY_A, &epoch_a));
    item = command(BREAK_RUNTIME_WORLD_COMMAND_OPEN, KEY_B, 0u, 7u);
    ASSERT_EQ(break_runtime_world_session_submit(second, &item, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 0u);
    ASSERT_EQ(break_runtime_world_session_pending(second), 1u);
    ASSERT_EQ(break_runtime_world_session_drain(second, 1u, &drained), BREAK_RUNTIME_OK);
    ASSERT_TRUE(break_runtime_world_session_connection_epoch(second, KEY_B, &epoch_b));

    item = command(BREAK_RUNTIME_WORLD_COMMAND_NEED_FULL, KEY_A, epoch_a, 7u);
    item.target_snapshot_id = 41u;
    item.target_tick = 51u;
    ASSERT_EQ(publish_external(fixture.bus, &item, HIGH_CID, &delivered), BREAK_RUNTIME_OK);
    ASSERT_EQ(delivered, 2u);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 1u);
    ASSERT_EQ(break_runtime_world_session_pending(second), 1u);
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained), BREAK_RUNTIME_OK);
    ASSERT_TRUE(next_control(&fixture, &key, &outbound));
    ASSERT_EQ(key, KEY_A);
    ASSERT_EQ(outbound.correlation_id, HIGH_CID);
    break_net_message_release(&outbound);
    ASSERT_EQ(break_runtime_world_session_drain(second, 1u, &drained), BREAK_RUNTIME_STALE);
    ASSERT_EQ(break_net_reactor_outbound_count(fixture.reactor), 0u);
    ASSERT_TRUE(break_world_session_baseline(fixture.session, KEY_B, NULL, NULL));

    item = command(BREAK_RUNTIME_WORLD_COMMAND_NEED_FULL, KEY_B, epoch_b, 7u);
    item.target_snapshot_id = 42u;
    item.target_tick = 52u;
    ASSERT_EQ(break_runtime_world_session_submit(second, &item, HIGH_CID - 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 0u);
    ASSERT_EQ(break_runtime_world_session_pending(second), 1u);
    ASSERT_EQ(break_runtime_world_session_drain(second, 1u, &drained), BREAK_RUNTIME_OK);
    ASSERT_TRUE(next_control(&fixture, &key, &outbound));
    ASSERT_EQ(key, KEY_B);
    ASSERT_EQ(outbound.correlation_id, HIGH_CID - 1u);
    break_net_message_release(&outbound);
    ASSERT_EQ(break_net_reactor_outbound_count(fixture.reactor), 0u);

    item = command(BREAK_RUNTIME_WORLD_COMMAND_CLOSE, KEY_A, epoch_a, 7u);
    ASSERT_EQ(publish_external(fixture.bus, &item, 0u, &delivered), BREAK_RUNTIME_OK);
    ASSERT_EQ(delivered, 2u);
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_drain(second, 1u, &drained), BREAK_RUNTIME_STALE);
    ASSERT_FALSE(break_world_session_baseline(fixture.session, KEY_A, NULL, NULL));
    ASSERT_TRUE(break_world_session_baseline(fixture.session, KEY_B, NULL, NULL));
    break_runtime_world_session_stats(fixture.adapter, &first_stats);
    break_runtime_world_session_stats(second, &second_stats);
    ASSERT_EQ(first_stats.submitted, 1u);
    ASSERT_EQ(first_stats.drained, 3u);
    ASSERT_EQ(second_stats.submitted, 2u);
    ASSERT_EQ(second_stats.drained, 4u);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 0u);
    ASSERT_EQ(break_runtime_world_session_pending(second), 0u);
    ASSERT_TRUE(break_runtime_world_session_destroy(fixture.adapter));
    fixture.adapter = NULL;
    ASSERT_TRUE(break_runtime_world_session_destroy(second));
    fixture_dispose(&fixture);
}

TEST(destroy_attempt_closes_ingress_before_pending_retry)
{
    Fixture fixture;
    BreakRuntimeWorldCommand item;
    BreakRuntimeWorldSessionStats stats;
    BreakNetOwnedMessage outbound;
    u64 epoch = 0u, key = 0u;
    u32 delivered = 99u;
    usize drained = 0u;
    ASSERT_TRUE(fixture_init(&fixture, 7u, 2u));
    ASSERT_TRUE(open_connection(&fixture, KEY_A, 7u, &epoch));
    item = command(BREAK_RUNTIME_WORLD_COMMAND_ACK, KEY_A, epoch, 7u);
    item.delta_id = 61u;
    item.target_snapshot_id = 62u;
    item.target_tick = 63u;
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &item, HIGH_CID), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 1u);
    ASSERT_FALSE(break_runtime_world_session_destroy(fixture.adapter));
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &item, HIGH_CID + 1u),
              BREAK_RUNTIME_CLOSED);
    (void)publish_external(fixture.bus, &item, HIGH_CID + 2u, &delivered);
    ASSERT_EQ(delivered, 0u);
    break_runtime_world_session_stats(fixture.adapter, &stats);
    ASSERT_EQ(stats.submitted, 2u);
    ASSERT_EQ(stats.drained, 1u);
    ASSERT_EQ(stats.queued, 1u);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 1u);
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 4u, &drained), BREAK_RUNTIME_OK);
    ASSERT_EQ(drained, 1u);
    ASSERT_TRUE(next_control(&fixture, &key, &outbound));
    ASSERT_EQ(outbound.correlation_id, HIGH_CID);
    ASSERT_TRUE(control_payload_matches(&outbound, BREAK_WORLD_SESSION_CONTROL_ACK,
                                        61u, 62u, 63u, 7u));
    break_net_message_release(&outbound);
    ASSERT_EQ(break_net_reactor_outbound_count(fixture.reactor), 0u);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 0u);
    ASSERT_TRUE(break_runtime_world_session_destroy(fixture.adapter));
    fixture.adapter = NULL;
    fixture_dispose(&fixture);
}

TEST(connection_epoch_exhaustion_is_terminal_rejected)
{
    Fixture fixture;
    BreakRuntimeWorldCommand item;
    BreakRuntimeWorldSessionStats stats;
    u64 epoch = 0u;
    usize drained = 0u;
    ASSERT_TRUE(fixture_init(&fixture, 7u, 2u));
    break_runtime_world_session_set_next_connection_epoch_for_test(fixture.adapter, UINT64_MAX);
    ASSERT_TRUE(open_connection(&fixture, KEY_A, 7u, &epoch));
    ASSERT_EQ(epoch, UINT64_MAX);
    item = command(BREAK_RUNTIME_WORLD_COMMAND_OPEN, KEY_B, 0u, 7u);
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &item, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
              BREAK_RUNTIME_REJECTED);
    ASSERT_EQ(drained, 1u);
    ASSERT_FALSE(break_world_session_baseline(fixture.session, KEY_B, NULL, NULL));
    ASSERT_TRUE(break_world_session_baseline(fixture.session, KEY_A, NULL, NULL));
    break_runtime_world_session_stats(fixture.adapter, &stats);
    ASSERT_EQ(stats.submitted, 2u);
    ASSERT_EQ(stats.drained, 2u);
    ASSERT_EQ(stats.applied, 1u);
    ASSERT_EQ(stats.rejected, 1u);
    ASSERT_EQ(stats.stale_rejected, 0u);
    ASSERT_EQ(stats.transport_overloads, 0u);
    ASSERT_EQ(stats.queued, 0u);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 0u);
    fixture_dispose(&fixture);
}

TEST_MAIN_BEGIN()
RUN_TEST(layout_registry_defaults_and_invalid_configs);
RUN_TEST(stateless_validation_defers_connection_and_level_state);
RUN_TEST(open_close_reopen_capacity_and_old_epoch_are_isolated);
RUN_TEST(level_zero_and_rebaseline_require_strict_increase);
RUN_TEST(queued_old_level_and_level7_to8_ack_cannot_touch_new_history);
RUN_TEST(correlation_and_runtime_sequence_survive_bus_queue_and_brwc);
RUN_TEST(need_full_ack_and_close_leave_other_connection_independent);
RUN_TEST(queue_overload_defers_world_and_retries_identical_command);
RUN_TEST(fifo_bounded_drain_close_and_destroy_preserve_world_lifetime);
RUN_TEST(transport_overload_retries_same_control_before_fifo);
RUN_TEST(transport_overload_retries_need_full_before_later_ack);
RUN_TEST(terminal_pending_result_is_counted_and_released);
RUN_TEST(external_bus_ingress_uses_actual_queue_accounting);
RUN_TEST(two_adapters_isolate_direct_submit_from_external_fanout);
RUN_TEST(destroy_attempt_closes_ingress_before_pending_retry);
RUN_TEST(connection_epoch_exhaustion_is_terminal_rejected);
RUN_TEST(concurrent_ingress_close_drain_and_destroy_preserve_exactly_once);
TEST_MAIN_END()
