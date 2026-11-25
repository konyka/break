#include "test_framework.h"

#include <core/platform_thread.h>
#include <ecs/world_snapshot_publication.h>
#include <network/break_net_message_registry.h>
#include <runtime/runtime_world_session.h>
#include <runtime/runtime_world_session_lifecycle.h>
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
_Static_assert(sizeof(BreakRuntimeWorldPublishCurrentNotice) == 16u, "notice size");
_Static_assert(offsetof(BreakRuntimeWorldPublishCurrentNotice, level_generation) == 0u,
               "notice level offset");
_Static_assert(offsetof(BreakRuntimeWorldPublishCurrentNotice, reserved_zero) == 8u,
               "notice reserved offset");

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
    BreakWorldSnapshotPublication *publication;
    bool fair_outbound_admission;
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
    BreakNetReactorConfig config = {
        BREAK_NET_DRIVE_STEP, 0, 8u, 1000, 1000u, 1u,
        fixture->fair_outbound_admission
    };
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

static bool fixture_init_without_adapter_scaled(Fixture *fixture, u64 level,
                                                u32 max_connections)
{
    BreakComponentSchema schema;
    BreakWorldSessionConfig config;
    bool fair_outbound_admission = fixture->fair_outbound_admission;
    memset(fixture, 0, sizeof(*fixture));
    fixture->fair_outbound_admission = fair_outbound_admission;
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
    config.bridge.max_connections = max_connections;
    config.bridge.stream_capacity = 4u;
    config.bridge.max_pending_bytes_per_connection = 8192u;
    config.bridge.max_total_pending_bytes = max_connections * 8192u;
    config.bridge.max_metadata_bytes_per_connection = 8192u;
    config.bridge.max_total_metadata_bytes = max_connections * 8192u;
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

static bool fixture_init_without_adapter(Fixture *fixture, u64 level)
{
    return fixture_init_without_adapter_scaled(fixture, level, 2u);
}

static bool fixture_attach_publication(Fixture *fixture, u32 queue_capacity,
                                       u32 max_connections,
                                       BreakWorldSnapshotPublication *publication,
                                       u32 publish_connection_budget)
{
    BreakRuntimeWorldSessionConfig config;
    memset(&config, 0, sizeof(config));
    config.session = fixture->session;
    config.bus = fixture->bus;
    config.queue_capacity = queue_capacity;
    config.max_connections = max_connections;
    config.publication = publication;
    config.publish_connection_budget = publish_connection_budget;
    fixture->adapter = break_runtime_world_session_create(&config);
    return fixture->adapter != NULL;
}

static bool fixture_attach(Fixture *fixture, u32 queue_capacity, u32 max_connections)
{
    return fixture_attach_publication(fixture, queue_capacity, max_connections, NULL, 0u);
}

static bool fixture_init(Fixture *fixture, u64 level, u32 max_connections)
{
    return fixture_init_without_adapter(fixture, level) &&
           fixture_attach(fixture, 0u, max_connections);
}

static bool fixture_init_publication(Fixture *fixture, u64 level,
                                     u32 max_connections, u32 publish_connection_budget)
{
    BreakWorldSnapshotPublicationConfig config;
    if (!fixture_init_without_adapter(fixture, level)) return false;
    memset(&config, 0, sizeof(config));
    config.schema_hash = break_schema_hash(fixture->schemas);
    config.level_generation = level;
    fixture->publication = break_world_snapshot_publication_create(&config);
    return fixture->publication &&
           fixture_attach_publication(fixture, 0u, max_connections,
                                      fixture->publication, publish_connection_budget);
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
    if (fixture->publication) {
        break_world_snapshot_publication_close(fixture->publication);
        break_world_snapshot_publication_destroy(fixture->publication);
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

static BreakRuntimeError submit_current(Fixture *fixture, u64 level, u64 correlation_id)
{
    BreakRuntimeWorldPublishCurrentNotice notice = {level, 0u};
    return break_runtime_world_session_submit_publish_current(
        fixture->adapter, &notice, correlation_id);
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

TEST(publish_notice_layout_submit_and_external_bus_contract)
{
    {
        Fixture fixture;
        BreakRuntimeWorldPublishCurrentNotice notice = {7u, 0u};
        BreakRuntimeWorldPublishCurrentNotice bad = {7u, 1u};
        BreakRuntimeWorldSessionConfig config;
        BreakRuntimeWorldSessionStats stats;
        BreakRuntimeMessageView view;
        BreakWorldSnapshotPublicationConfig publication_config;
        BreakWorldSnapshotPublication *publication;
        u32 delivered = 99u;
        u32 budget;

        ASSERT_TRUE(fixture_init_without_adapter(&fixture, 7u));
        memset(&config, 0, sizeof(config));
        memset(&publication_config, 0, sizeof(publication_config));
        publication_config.schema_hash = break_schema_hash(fixture.schemas);
        publication_config.level_generation = 7u;
        publication = break_world_snapshot_publication_create(&publication_config);
        ASSERT_NOT_NULL(publication);
        fixture.publication = publication;

        config.session = fixture.session;
        config.bus = fixture.bus;
        config.subscriber_name = NULL;
        config.queue_capacity = 1u;
        config.max_connections = 2u;
        config.publication = NULL;
        config.publish_connection_budget = 1u;
        ASSERT_EQ(break_runtime_world_session_create(&config), NULL);
        config.publication = publication;
        config.publish_connection_budget = 65u;
        ASSERT_EQ(break_runtime_world_session_create(&config), NULL);
        for (budget = 1u; budget <= 64u; ++budget) {
            config.publish_connection_budget = budget;
            fixture.adapter = break_runtime_world_session_create(&config);
            ASSERT_NOT_NULL(fixture.adapter);
            ASSERT_TRUE(break_runtime_world_session_destroy(fixture.adapter));
            fixture.adapter = NULL;
        }

        config.publish_connection_budget = 0u;
        fixture.adapter = break_runtime_world_session_create(&config);
        ASSERT_NOT_NULL(fixture.adapter);
        ASSERT_EQ(break_runtime_world_session_submit_publish_current(
                      fixture.adapter, NULL, HIGH_CID), BREAK_RUNTIME_INVALID);
        ASSERT_EQ(break_runtime_world_session_submit_publish_current(
                      fixture.adapter, &bad, HIGH_CID), BREAK_RUNTIME_INVALID);
        ASSERT_EQ(break_runtime_world_session_submit_publish_current(
                      fixture.adapter, &notice, HIGH_CID), BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_world_session_submit_publish_current(
                      fixture.adapter, &notice, HIGH_CID), BREAK_RUNTIME_OVERLOAD);
        break_runtime_world_session_stats(fixture.adapter, &stats);
        ASSERT_EQ(stats.submitted, 1u);
        ASSERT_EQ(stats.drained, 0u);
        ASSERT_EQ(stats.next_sequence, 2u);
        ASSERT_EQ(stats.queued, 1u);
        ASSERT_EQ(stats.publish_overloads, 0u);

        memset(&view, 0, sizeof(view));
        view.kind = BREAK_RUNTIME_WORLD_SESSION_PUBLISH_CURRENT_KIND;
        view.version = BREAK_RUNTIME_WORLD_SESSION_PUBLISH_CURRENT_VERSION;
        view.sequence = UINT64_MAX;
        view.correlation_id = HIGH_CID;
        view.data = &notice;
        view.size = sizeof(notice);
        ASSERT_EQ(break_runtime_bus_publish(fixture.bus, &view, &delivered),
                  BREAK_RUNTIME_REJECTED);
        ASSERT_EQ(delivered, 0u);
        break_runtime_world_session_stats(fixture.adapter, &stats);
        ASSERT_EQ(stats.queued, 1u);

        break_runtime_world_session_close(fixture.adapter);
        ASSERT_EQ(break_runtime_world_session_submit_publish_current(
                      fixture.adapter, &notice, HIGH_CID), BREAK_RUNTIME_CLOSED);
        fixture_dispose(&fixture);
    }
    {
        Fixture fixture;
        BreakRuntimeWorldPublishCurrentNotice notice = {7u, 0u};
        BreakWorldSessionSenderState before;
        BreakWorldSessionSenderState after;
        BreakRuntimeWorldSessionStats stats_before;
        BreakRuntimeWorldSessionStats stats_after;
        u64 epoch = 0u;

        ASSERT_TRUE(fixture_init(&fixture, 7u, 2u));
        ASSERT_TRUE(open_connection(&fixture, KEY_A, 7u, &epoch));
        ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_A, &before));
        break_runtime_world_session_stats(fixture.adapter, &stats_before);
        ASSERT_EQ(break_runtime_world_session_submit_publish_current(
                      fixture.adapter, &notice, HIGH_CID), BREAK_RUNTIME_REJECTED);
        ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_A, &after));
        ASSERT_EQ(memcmp(&before, &after, sizeof(after)), 0);
        break_runtime_world_session_stats(fixture.adapter, &stats_after);
        ASSERT_EQ(stats_after.next_sequence, stats_before.next_sequence);
        ASSERT_EQ(stats_after.submitted, stats_before.submitted);
        ASSERT_EQ(stats_after.drained, stats_before.drained);
        ASSERT_EQ(break_net_reactor_outbound_count(fixture.reactor), 0u);
        fixture_dispose(&fixture);
    }
}

TEST(publish_notice_basic_s1_full_has_no_pre_drain_effects)
{
    Fixture fixture;
    BreakWorldSnapshot *s1;
    BreakWorldSessionSenderState before;
    BreakWorldSessionSenderState after;
    BreakWorldSessionStats world_before;
    BreakWorldSessionStats world_after;
    BreakRuntimeWorldSessionStats stats;
    u64 epoch_a = 0u;
    usize drained = 0u;

    ASSERT_TRUE(fixture_init_publication(&fixture, 7u, 2u, 0u));
    ASSERT_TRUE(open_connection(&fixture, KEY_A, 7u, &epoch_a));
    s1 = make_target(&fixture, 42u, 10u);
    ASSERT_NOT_NULL(s1);
    ASSERT_TRUE(break_world_snapshot_publication_publish(fixture.publication, s1, 7u));
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_A, &before));
    break_world_session_stats(fixture.session, &world_before);
    ASSERT_EQ(break_net_reactor_outbound_count(fixture.reactor), 0u);

    ASSERT_EQ(submit_current(&fixture, 7u, HIGH_CID), BREAK_RUNTIME_OK);
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_A, &after));
    break_world_session_stats(fixture.session, &world_after);
    ASSERT_EQ(memcmp(&before, &after, sizeof(after)), 0);
    ASSERT_EQ(memcmp(&world_before, &world_after, sizeof(world_after)), 0);
    ASSERT_EQ(break_net_reactor_outbound_count(fixture.reactor), 0u);

    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(drained, 1u);
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_A, &after));
    ASSERT_EQ(after.history_count, 1u);
    ASSERT_EQ(after.next_delta_id, 2u);
    ASSERT_FALSE(after.attempt_pending);
    break_world_session_stats(fixture.session, &world_after);
    ASSERT_EQ(world_after.published_full_packets, 1u);
    ASSERT_EQ(world_after.published_delta_packets, 0u);
    break_runtime_world_session_stats(fixture.adapter, &stats);
    ASSERT_FALSE(stats.publish_pending);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 0u);
    break_world_snapshot_release(s1);
    fixture_dispose(&fixture);
}

TEST(publish_notice_connections_keep_independent_full_delta_and_dedup)
{
    Fixture fixture;
    BreakWorldSnapshot *s1;
    BreakWorldSnapshot *s2;
    BreakWorldSessionSenderState a_state;
    BreakWorldSessionSenderState b_state;
    BreakWorldSessionStats before;
    BreakWorldSessionStats after;
    BreakRuntimeWorldSessionStats runtime_stats;
    u64 submitted_before;
    u64 drained_before;
    u64 epoch_a = 0u;
    u64 epoch_b = 0u;
    usize drained = 0u;

    ASSERT_TRUE(fixture_init_publication(&fixture, 7u, 2u, 0u));
    ASSERT_TRUE(open_connection(&fixture, KEY_A, 7u, &epoch_a));
    ASSERT_TRUE(open_connection(&fixture, KEY_B, 7u, &epoch_b));
    s1 = make_target(&fixture, 42u, 10u);
    ASSERT_NOT_NULL(s1);
    ASSERT_TRUE(break_world_snapshot_publication_publish(fixture.publication, s1, 7u));
    ASSERT_EQ(submit_current(&fixture, 7u, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
              BREAK_RUNTIME_OK);
    break_world_session_stats(fixture.session, &after);
    ASSERT_EQ(after.published_full_packets, 2u);
    ASSERT_EQ(after.published_delta_packets, 0u);
    ASSERT_TRUE(control_via_adapter(&fixture, BREAK_RUNTIME_WORLD_COMMAND_ACK,
                                    KEY_A, epoch_a, 7u, 1u, s1, 0u));

    s2 = make_target(&fixture, 43u, 20u);
    ASSERT_NOT_NULL(s2);
    ASSERT_TRUE(break_world_snapshot_publication_publish(fixture.publication, s2, 7u));
    ASSERT_EQ(submit_current(&fixture, 7u, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
              BREAK_RUNTIME_OK);
    break_world_session_stats(fixture.session, &after);
    ASSERT_EQ(after.published_full_packets, 3u);
    ASSERT_EQ(after.published_delta_packets, 1u);
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_A, &a_state));
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_B, &b_state));
    ASSERT_EQ(a_state.confirmed_snapshot_id, break_world_snapshot_id(s1));
    ASSERT_EQ(a_state.history_count, 1u);
    ASSERT_EQ(a_state.next_delta_id, 3u);
    ASSERT_EQ(b_state.confirmed_snapshot_id, 0u);
    ASSERT_EQ(b_state.history_count, 1u);
    ASSERT_EQ(b_state.next_delta_id, 3u);

    before = after;
    break_runtime_world_session_stats(fixture.adapter, &runtime_stats);
    submitted_before = runtime_stats.submitted;
    drained_before = runtime_stats.drained;
    ASSERT_EQ(submit_current(&fixture, 7u, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(submit_current(&fixture, 7u, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 2u, &drained),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(drained, 2u);
    break_runtime_world_session_stats(fixture.adapter, &runtime_stats);
    ASSERT_EQ(runtime_stats.submitted, submitted_before + 2u);
    ASSERT_EQ(runtime_stats.drained, drained_before + 2u);
    ASSERT_FALSE(runtime_stats.publish_pending);
    break_world_session_stats(fixture.session, &after);
    ASSERT_EQ(memcmp(&before, &after, sizeof(after)), 0);
    break_world_snapshot_release(s2);
    break_world_snapshot_release(s1);
    fixture_dispose(&fixture);
}

TEST(publish_notice_empty_closed_wrong_level_and_no_open_connections)
{
    {
        Fixture fixture;
        BreakWorldSnapshot *s1;
        BreakWorldSessionStats world_after;
        u64 epoch_a = 0u;
        usize drained = 0u;

        ASSERT_TRUE(fixture_init_publication(&fixture, 0u, 2u, 0u));
        ASSERT_TRUE(open_connection(&fixture, KEY_A, 0u, &epoch_a));
        s1 = make_target(&fixture, 42u, 10u);
        ASSERT_NOT_NULL(s1);
        ASSERT_TRUE(break_world_snapshot_publication_publish(fixture.publication, s1, 0u));
        ASSERT_EQ(submit_current(&fixture, 0u, 0u), BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
                  BREAK_RUNTIME_OK);
        ASSERT_EQ(drained, 1u);
        break_world_session_stats(fixture.session, &world_after);
        ASSERT_EQ(world_after.published_full_packets, 1u);
        break_world_snapshot_release(s1);
        fixture_dispose(&fixture);
    }
    {
        Fixture fixture;
        BreakWorldSnapshotLease lease;
        BreakWorldSessionSenderState sender;
        u64 epoch_a = 0u;
        usize drained = 0u;

        ASSERT_TRUE(fixture_init_publication(&fixture, 7u, 2u, 0u));
        ASSERT_TRUE(open_connection(&fixture, KEY_A, 7u, &epoch_a));
        memset(&lease, 0, sizeof(lease));
        ASSERT_EQ(break_world_snapshot_publication_acquire(fixture.publication, &lease),
                  BREAK_WORLD_SNAPSHOT_ACQUIRE_EMPTY);
        ASSERT_EQ(lease.snapshot, NULL);
        ASSERT_EQ(submit_current(&fixture, 7u, 0u), BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
                  BREAK_RUNTIME_OK);
        ASSERT_EQ(drained, 1u);
        ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 0u);
        ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_A, &sender));
        ASSERT_EQ(sender.next_delta_id, 1u);
        fixture_dispose(&fixture);
    }
    {
        Fixture fixture;
        BreakWorldSnapshot *s1;
        BreakWorldSessionSenderState sender;
        BreakWorldSessionStats world_after;
        BreakRuntimeWorldSessionStats stats;
        u64 epoch_a = 0u;
        usize drained = 0u;

        ASSERT_TRUE(fixture_init_publication(&fixture, 7u, 2u, 0u));
        ASSERT_TRUE(open_connection(&fixture, KEY_A, 7u, &epoch_a));
        ASSERT_EQ(submit_current(&fixture, 8u, 0u), BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
                  BREAK_RUNTIME_STALE);
        ASSERT_EQ(drained, 1u);
        ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 0u);
        ASSERT_EQ(break_net_reactor_outbound_count(fixture.reactor), 0u);
        ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_A, &sender));
        ASSERT_EQ(sender.next_delta_id, 1u);

        s1 = make_target(&fixture, 42u, 10u);
        ASSERT_NOT_NULL(s1);
        ASSERT_TRUE(break_world_snapshot_publication_publish(fixture.publication, s1, 7u));
        ASSERT_EQ(submit_current(&fixture, 7u, 0u), BREAK_RUNTIME_OK);
        ASSERT_EQ(submit_current(&fixture, 8u, 0u), BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 2u, &drained),
                  BREAK_RUNTIME_STALE);
        ASSERT_EQ(drained, 2u);
        break_world_session_stats(fixture.session, &world_after);
        ASSERT_EQ(world_after.published_full_packets, 1u);
        ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 0u);
        break_runtime_world_session_stats(fixture.adapter, &stats);
        ASSERT_EQ(stats.stale_rejected, 2u);
        break_world_snapshot_release(s1);
        fixture_dispose(&fixture);
    }
    {
        Fixture fixture;
        BreakWorldSnapshot *s1;
        BreakWorldSessionSenderState sender;
        BreakWorldSessionStats world_after;
        u64 epoch_b = 0u;
        usize drained = 0u;

        ASSERT_TRUE(fixture_init_publication(&fixture, 7u, 2u, 0u));
        s1 = make_target(&fixture, 42u, 10u);
        ASSERT_NOT_NULL(s1);
        ASSERT_TRUE(break_world_snapshot_publication_publish(fixture.publication, s1, 7u));
        ASSERT_EQ(submit_current(&fixture, 7u, 0u), BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
                  BREAK_RUNTIME_OK);
        ASSERT_EQ(drained, 1u);
        ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 0u);
        break_world_session_stats(fixture.session, &world_after);
        ASSERT_EQ(world_after.published_full_packets, 0u);
        ASSERT_EQ(world_after.published_delta_packets, 0u);
        ASSERT_TRUE(open_connection(&fixture, KEY_B, 7u, &epoch_b));
        ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_B, &sender));
        ASSERT_EQ(sender.next_delta_id, 1u);
        break_world_snapshot_release(s1);
        fixture_dispose(&fixture);
    }
    {
        Fixture fixture;
        BreakWorldSnapshotLease lease;
        BreakWorldSessionSenderState sender;
        BreakRuntimeWorldSessionStats stats;
        u64 epoch_a = 0u;
        usize drained = 0u;

        ASSERT_TRUE(fixture_init_publication(&fixture, 7u, 2u, 0u));
        ASSERT_TRUE(open_connection(&fixture, KEY_A, 7u, &epoch_a));
        break_world_snapshot_publication_close(fixture.publication);
        memset(&lease, 0, sizeof(lease));
        ASSERT_EQ(break_world_snapshot_publication_acquire(fixture.publication, &lease),
                  BREAK_WORLD_SNAPSHOT_ACQUIRE_CLOSED);
        ASSERT_EQ(lease.snapshot, NULL);
        ASSERT_EQ(submit_current(&fixture, 7u, 0u), BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
                  BREAK_RUNTIME_CLOSED);
        ASSERT_EQ(drained, 1u);
        break_runtime_world_session_stats(fixture.adapter, &stats);
        ASSERT_EQ(stats.publish_terminal, 1u);
        ASSERT_FALSE(stats.publish_pending);
        ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_A, &sender));
        ASSERT_EQ(sender.next_delta_id, 1u);
        fixture_dispose(&fixture);
    }
}

TEST(publish_budget_one_round_robin_continues_without_queue_message)
{
    Fixture fixture;
    BreakWorldSnapshot *s1;
    BreakWorldSessionSenderState a_state;
    BreakWorldSessionSenderState b_state;
    BreakRuntimeWorldSessionStats stats;
    u64 epoch_a = 0u;
    u64 epoch_b = 0u;
    usize drained = 0u;

    ASSERT_TRUE(fixture_init_publication(&fixture, 7u, 2u, 1u));
    ASSERT_TRUE(open_connection(&fixture, KEY_A, 7u, &epoch_a));
    ASSERT_TRUE(open_connection(&fixture, KEY_B, 7u, &epoch_b));
    s1 = make_target(&fixture, 42u, 10u);
    ASSERT_NOT_NULL(s1);
    ASSERT_TRUE(break_world_snapshot_publication_publish(fixture.publication, s1, 7u));
    ASSERT_EQ(submit_current(&fixture, 7u, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(drained, 1u);
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_A, &a_state));
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_B, &b_state));
    ASSERT_EQ(a_state.history_count, 1u);
    ASSERT_EQ(b_state.history_count, 0u);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 1u);
    break_runtime_world_session_stats(fixture.adapter, &stats);
    ASSERT_TRUE(stats.publish_pending);
    ASSERT_FALSE(stats.control_pending);

    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 0u, &drained),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(drained, 0u);
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_B, &b_state));
    ASSERT_EQ(b_state.history_count, 0u);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 1u);

    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(drained, 0u);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 0u);
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_A, &a_state));
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_B, &b_state));
    ASSERT_EQ(a_state.history_count, 1u);
    ASSERT_EQ(a_state.next_delta_id, 2u);
    ASSERT_EQ(b_state.history_count, 1u);
    ASSERT_EQ(b_state.next_delta_id, 2u);
    break_runtime_world_session_stats(fixture.adapter, &stats);
    ASSERT_FALSE(stats.publish_pending);
    break_world_snapshot_release(s1);
    fixture_dispose(&fixture);
}

TEST(publish_default_budget_eight_defers_ninth_connection)
{
    enum { CONNECTION_COUNT = 9 };
    Fixture fixture;
    BreakWorldSnapshotPublicationConfig publication_config;
    BreakWorldSnapshot *s1;
    BreakWorldSessionSenderState state;
    BreakRuntimeWorldSessionStats stats;
    u64 epochs[CONNECTION_COUNT] = {0u};
    u64 next_delta_ids[CONNECTION_COUNT];
    usize drained = 0u;

    ASSERT_TRUE(fixture_init_without_adapter_scaled(&fixture, 7u, CONNECTION_COUNT));
    memset(&publication_config, 0, sizeof(publication_config));
    publication_config.schema_hash = break_schema_hash(fixture.schemas);
    publication_config.level_generation = 7u;
    fixture.publication = break_world_snapshot_publication_create(&publication_config);
    ASSERT_NOT_NULL(fixture.publication);
    ASSERT_TRUE(fixture_attach_publication(&fixture, 0u, CONNECTION_COUNT,
                                           fixture.publication, 0u));
    for (u32 i = 0u; i < CONNECTION_COUNT; ++i) {
        ASSERT_TRUE(open_connection(&fixture, KEY_A + i, 7u, &epochs[i]));
    }
    s1 = make_target(&fixture, 42u, 10u);
    ASSERT_NOT_NULL(s1);
    ASSERT_TRUE(break_world_snapshot_publication_publish(fixture.publication, s1, 7u));
    ASSERT_EQ(submit_current(&fixture, 7u, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(drained, 1u);
    for (u32 i = 0u; i < CONNECTION_COUNT; ++i) {
        ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_A + i, &state));
        ASSERT_EQ(state.history_count, i < 8u ? 1u : 0u);
        ASSERT_EQ(state.next_delta_id, i < 8u ? 2u : 1u);
        next_delta_ids[i] = state.next_delta_id;
    }
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 1u);
    break_runtime_world_session_stats(fixture.adapter, &stats);
    ASSERT_TRUE(stats.publish_pending);

    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(drained, 0u);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 0u);
    for (u32 i = 0u; i < CONNECTION_COUNT; ++i) {
        ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_A + i, &state));
        ASSERT_EQ(state.history_count, 1u);
        if (i < 8u) {
            ASSERT_EQ(state.next_delta_id, next_delta_ids[i]);
        } else {
            ASSERT_EQ(state.next_delta_id, 2u);
        }
    }
    break_runtime_world_session_stats(fixture.adapter, &stats);
    ASSERT_FALSE(stats.publish_pending);
    break_world_snapshot_release(s1);
    fixture_dispose(&fixture);
}

TEST(publish_overload_resumes_e1_before_latest_e2)
{
    /* socketless fixture: open_connection() creates no reactor identity, so the
     * reactor fair-share OVERLOAD path (active_count>=2) cannot fire. A single
     * connection with a globally full outbound queue is the only way to force
     * break_world_session_publish_snapshot() to return OVERLOAD here, so this
     * test drives the E1 OVERLOAD -> publish E2 -> resume old E1 accounting with
     * one connection. The cross-connection "B is not blocked" guarantee is
     * covered by publish_budget_one_round_robin (5) and Task 4's real dual
     * socket step 4, not by this socketless test. */
    Fixture fixture;
    BreakWorldSnapshot *s1;
    BreakWorldSnapshot *s2;
    BreakWorldSessionSenderState a_state;
    BreakWorldSessionSenderState a_before_repeat;
    BreakRuntimeWorldSessionStats stats;
    u64 epoch_a = 0u;
    usize drained = 0u;

    ASSERT_TRUE(fixture_init_publication(&fixture, 7u, 2u, 0u));
    ASSERT_TRUE(open_connection(&fixture, KEY_A, 7u, &epoch_a));
    s1 = make_target(&fixture, 42u, 10u);
    ASSERT_NOT_NULL(s1);
    ASSERT_TRUE(break_world_snapshot_publication_publish(fixture.publication, s1, 7u));
    for (u32 i = 0u; i < BREAK_NET_OUTBOUND_QUEUE_CAPACITY; ++i) {
        ASSERT_EQ(break_net_reactor_send(fixture.reactor, KEY_A, BREAK_NET_MESSAGE_ID_PING,
                                         1u, "x", 1u),
                  BREAK_NET_SEND_OK);
    }
    ASSERT_EQ(submit_current(&fixture, 7u, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
              BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(drained, 1u);
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_A, &a_state));
    ASSERT_TRUE(a_state.attempt_pending);
    ASSERT_EQ(a_state.attempt_target_snapshot_id, break_world_snapshot_id(s1));
    ASSERT_EQ(a_state.attempt_target_tick, 10u);
    ASSERT_EQ(a_state.history_count, 0u);
    ASSERT_EQ(a_state.next_delta_id, 2u);
    break_runtime_world_session_stats(fixture.adapter, &stats);
    ASSERT_EQ(stats.publish_overloads, 1u);
    ASSERT_EQ(stats.publish_terminal, 0u);
    ASSERT_EQ(stats.transport_overloads, 0u);
    ASSERT_TRUE(stats.publish_pending);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 1u);

    clear_outbound(&fixture);
    s2 = make_target(&fixture, 84u, 20u);
    ASSERT_NOT_NULL(s2);
    ASSERT_TRUE(break_world_snapshot_publication_publish(fixture.publication, s2, 7u));
    /* Empty-queue continuation drain acquires E2 but A still has the active E1
     * attempt, so publish_snapshot resumes E1. Any OK that marks E2 completed
     * here fails: current must stay dirty, pending must stay 1. */
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(drained, 0u);
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_A, &a_state));
    ASSERT_FALSE(a_state.attempt_pending);
    ASSERT_EQ(a_state.history_count, 1u);
    ASSERT_EQ(a_state.next_delta_id, 2u);
    break_runtime_world_session_stats(fixture.adapter, &stats);
    ASSERT_TRUE(stats.publish_pending);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 1u);

    /* Now that A has no active attempt, the next continuation drain really
     * creates and completes E2. */
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(drained, 0u);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 0u);
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_A, &a_state));
    ASSERT_EQ(a_state.next_delta_id, 3u);
    a_before_repeat = a_state;
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
              BREAK_RUNTIME_OK);
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_A, &a_state));
    ASSERT_EQ(memcmp(&a_before_repeat, &a_state, sizeof(a_state)), 0);
    break_runtime_world_session_stats(fixture.adapter, &stats);
    ASSERT_EQ(stats.publish_overloads, 1u);
    ASSERT_EQ(stats.transport_overloads, 0u);
    ASSERT_FALSE(stats.publish_pending);
    break_world_snapshot_release(s2);
    break_world_snapshot_release(s1);
    fixture_dispose(&fixture);
}

TEST(publish_unknown_old_attempt_does_not_complete_current)
{
    Fixture fixture;
    BreakWorldSnapshot *s0;
    BreakWorldSnapshot *s1;
    BreakWorldSessionSenderState state;
    BreakRuntimeWorldSessionStats stats;
    u64 epoch_a = 0u;
    usize drained = 0u;

    ASSERT_TRUE(fixture_init_publication(&fixture, 7u, 2u, 0u));
    ASSERT_TRUE(open_connection(&fixture, KEY_A, 7u, &epoch_a));
    s0 = make_target(&fixture, 21u, 5u);
    ASSERT_NOT_NULL(s0);
    for (u32 i = 0u; i < BREAK_NET_OUTBOUND_QUEUE_CAPACITY; ++i) {
        ASSERT_EQ(break_net_reactor_send(fixture.reactor, KEY_A, BREAK_NET_MESSAGE_ID_PING,
                                         1u, "x", 1u),
                  BREAK_NET_SEND_OK);
    }
    ASSERT_EQ(break_world_session_publish_snapshot(fixture.session, KEY_A, s0, 7u),
              BREAK_NET_SEND_OVERLOAD);
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_A, &state));
    ASSERT_TRUE(state.attempt_pending);
    ASSERT_EQ(state.attempt_target_snapshot_id, break_world_snapshot_id(s0));
    ASSERT_EQ(state.attempt_target_tick, 5u);
    clear_outbound(&fixture);

    s1 = make_target(&fixture, 42u, 10u);
    ASSERT_NOT_NULL(s1);
    ASSERT_TRUE(break_world_snapshot_publication_publish(fixture.publication, s1, 7u));
    ASSERT_EQ(submit_current(&fixture, 7u, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(drained, 1u);
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_A, &state));
    ASSERT_FALSE(state.attempt_pending);
    ASSERT_EQ(state.history_count, 1u);
    ASSERT_EQ(state.next_delta_id, 2u);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 1u);
    break_runtime_world_session_stats(fixture.adapter, &stats);
    ASSERT_TRUE(stats.publish_pending);
    ASSERT_EQ(stats.publish_overloads, 0u);
    ASSERT_EQ(stats.publish_terminal, 0u);

    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(drained, 0u);
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_A, &state));
    ASSERT_EQ(state.next_delta_id, 3u);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 0u);
    break_runtime_world_session_stats(fixture.adapter, &stats);
    ASSERT_FALSE(stats.publish_pending);
    break_world_snapshot_release(s1);
    break_world_snapshot_release(s0);
    fixture_dispose(&fixture);
}

TEST(publish_overload_across_connections_does_not_abort_fanout)
{
    /* Both connections share the global 256-slot outbound queue. Filling it
     * forces A and B to OVERLOAD on the same drain; a mutation that aborts the
     * fanout after A's OVERLOAD leaves B with publish_overloads==1 and B's
     * attempt absent, which this test rejects. */
    Fixture fixture;
    BreakWorldSnapshot *s1;
    BreakWorldSessionSenderState a_state;
    BreakWorldSessionSenderState b_state;
    BreakRuntimeWorldSessionStats stats;
    u64 epoch_a = 0u;
    u64 epoch_b = 0u;
    usize drained = 0u;

    ASSERT_TRUE(fixture_init_publication(&fixture, 7u, 2u, 0u));
    ASSERT_TRUE(open_connection(&fixture, KEY_A, 7u, &epoch_a));
    ASSERT_TRUE(open_connection(&fixture, KEY_B, 7u, &epoch_b));
    s1 = make_target(&fixture, 42u, 10u);
    ASSERT_NOT_NULL(s1);
    ASSERT_TRUE(break_world_snapshot_publication_publish(fixture.publication, s1, 7u));
    for (u32 i = 0u; i < BREAK_NET_OUTBOUND_QUEUE_CAPACITY; ++i) {
        ASSERT_EQ(break_net_reactor_send(fixture.reactor, KEY_A, BREAK_NET_MESSAGE_ID_PING,
                                         1u, "x", 1u),
                  BREAK_NET_SEND_OK);
    }
    ASSERT_EQ(submit_current(&fixture, 7u, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
              BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(drained, 1u);
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_A, &a_state));
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_B, &b_state));
    ASSERT_TRUE(a_state.attempt_pending);
    ASSERT_TRUE(b_state.attempt_pending);
    ASSERT_EQ(a_state.attempt_target_snapshot_id, break_world_snapshot_id(s1));
    ASSERT_EQ(b_state.attempt_target_snapshot_id, break_world_snapshot_id(s1));
    break_runtime_world_session_stats(fixture.adapter, &stats);
    ASSERT_EQ(stats.publish_overloads, 2u);
    ASSERT_EQ(stats.publish_terminal, 0u);
    ASSERT_EQ(stats.transport_overloads, 0u);
    ASSERT_TRUE(stats.publish_pending);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 1u);

    clear_outbound(&fixture);
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(drained, 0u);
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_A, &a_state));
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_B, &b_state));
    ASSERT_EQ(a_state.history_count, 1u);
    ASSERT_EQ(b_state.history_count, 1u);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 0u);
    break_world_snapshot_release(s1);
    fixture_dispose(&fixture);
}

TEST(publish_terminal_dedup_new_epoch_and_need_full_rules)
{
    { /* strict-tick INVALID is terminal, same-epoch dedups, new epoch retries. */
        Fixture fixture;
        BreakWorldSnapshot *history_target;
        BreakWorldSnapshot *s1;
        BreakWorldSnapshot *s2;
        BreakWorldSessionSenderState a_state;
        BreakWorldSessionStats world_before;
        BreakWorldSessionStats world_after;
        BreakRuntimeWorldSessionStats stats;
        u64 epoch_a = 0u;
        u64 history_delta = 0u;
        usize drained = 0u;

        ASSERT_TRUE(fixture_init_publication(&fixture, 7u, 2u, 0u));
        ASSERT_TRUE(open_connection(&fixture, KEY_A, 7u, &epoch_a));
        history_target = make_target(&fixture, 10u, 100u);
        ASSERT_NOT_NULL(history_target);
        ASSERT_TRUE(publish_target(&fixture, KEY_A, history_target, 7u, &history_delta));
        s1 = make_target(&fixture, 42u, 10u);
        ASSERT_NOT_NULL(s1);
        ASSERT_TRUE(break_world_snapshot_publication_publish(fixture.publication, s1, 7u));
        break_world_session_stats(fixture.session, &world_before);
        ASSERT_EQ(submit_current(&fixture, 7u, 0u), BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
                  BREAK_RUNTIME_INVALID);
        ASSERT_EQ(drained, 1u);
        break_runtime_world_session_stats(fixture.adapter, &stats);
        ASSERT_EQ(stats.publish_terminal, 1u);
        ASSERT_EQ(stats.publish_overloads, 0u);
        ASSERT_FALSE(stats.publish_pending);
        ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 0u);
        ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_A, &a_state));
        ASSERT_FALSE(a_state.attempt_pending);
        break_world_session_stats(fixture.session, &world_after);
        ASSERT_EQ(memcmp(&world_before, &world_after, sizeof(world_after)), 0);

        ASSERT_EQ(submit_current(&fixture, 7u, 0u), BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
                  BREAK_RUNTIME_OK);
        ASSERT_EQ(drained, 1u);
        break_runtime_world_session_stats(fixture.adapter, &stats);
        ASSERT_EQ(stats.publish_terminal, 1u);
        ASSERT_FALSE(stats.publish_pending);
        break_world_session_stats(fixture.session, &world_after);
        ASSERT_EQ(memcmp(&world_before, &world_after, sizeof(world_after)), 0);
        ASSERT_EQ(break_net_reactor_outbound_count(fixture.reactor), 0u);

        s2 = make_target(&fixture, 84u, 110u);
        ASSERT_NOT_NULL(s2);
        ASSERT_TRUE(break_world_snapshot_publication_publish(fixture.publication, s2, 7u));
        ASSERT_EQ(submit_current(&fixture, 7u, 0u), BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
                  BREAK_RUNTIME_OK);
        ASSERT_EQ(drained, 1u);
        break_runtime_world_session_stats(fixture.adapter, &stats);
        ASSERT_EQ(stats.publish_terminal, 1u);
        ASSERT_FALSE(stats.publish_pending);
        break_world_session_stats(fixture.session, &world_after);
        ASSERT_EQ(world_after.published_full_packets,
                  world_before.published_full_packets + 1u);
        ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 0u);
        break_world_snapshot_release(s2);
        break_world_snapshot_release(s1);
        break_world_snapshot_release(history_target);
        fixture_dispose(&fixture);
    }
    { /* reactor stop maps to terminal CLOSED without a permanent pending. */
        Fixture fixture;
        BreakWorldSnapshot *s1;
        BreakRuntimeWorldSessionStats stats;
        u64 epoch_a = 0u;
        usize drained = 0u;

        ASSERT_TRUE(fixture_init_publication(&fixture, 7u, 2u, 0u));
        ASSERT_TRUE(open_connection(&fixture, KEY_A, 7u, &epoch_a));
        s1 = make_target(&fixture, 42u, 10u);
        ASSERT_NOT_NULL(s1);
        ASSERT_TRUE(break_world_snapshot_publication_publish(fixture.publication, s1, 7u));
        ASSERT_TRUE(break_net_reactor_stop(fixture.reactor, 1000u));
        ASSERT_EQ(submit_current(&fixture, 7u, 0u), BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
                  BREAK_RUNTIME_CLOSED);
        ASSERT_EQ(drained, 1u);
        break_runtime_world_session_stats(fixture.adapter, &stats);
        ASSERT_EQ(stats.publish_terminal, 1u);
        ASSERT_EQ(stats.publish_overloads, 0u);
        ASSERT_FALSE(stats.publish_pending);
        ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 0u);
        ASSERT_TRUE(break_runtime_world_session_destroy(fixture.adapter));
        fixture.adapter = NULL;
        break_world_snapshot_release(s1);
        fixture_dispose(&fixture);
    }
    { /* NEED_FULL forces a new full but never clears a completed epoch. */
        Fixture fixture;
        BreakWorldSnapshot *s1;
        BreakWorldSnapshot *s2;
        BreakWorldSessionStats before;
        BreakWorldSessionStats after;
        BreakRuntimeWorldSessionStats stats;
        u64 epoch_a = 0u;
        usize drained = 0u;

        ASSERT_TRUE(fixture_init_publication(&fixture, 7u, 2u, 0u));
        ASSERT_TRUE(open_connection(&fixture, KEY_A, 7u, &epoch_a));
        s1 = make_target(&fixture, 42u, 10u);
        ASSERT_NOT_NULL(s1);
        ASSERT_TRUE(break_world_snapshot_publication_publish(fixture.publication, s1, 7u));
        ASSERT_EQ(submit_current(&fixture, 7u, 0u), BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
                  BREAK_RUNTIME_OK);
        ASSERT_EQ(drained, 1u);
        ASSERT_TRUE(control_via_adapter(&fixture, BREAK_RUNTIME_WORLD_COMMAND_ACK,
                                        KEY_A, epoch_a, 7u, 1u, s1, 0u));
        ASSERT_TRUE(control_via_adapter(&fixture, BREAK_RUNTIME_WORLD_COMMAND_NEED_FULL,
                                        KEY_A, epoch_a, 7u, 0u, s1, 0u));
        break_world_session_stats(fixture.session, &before);
        ASSERT_EQ(submit_current(&fixture, 7u, 0u), BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
                  BREAK_RUNTIME_OK);
        ASSERT_EQ(drained, 1u);
        break_world_session_stats(fixture.session, &after);
        ASSERT_EQ(memcmp(&before, &after, sizeof(after)), 0);
        ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 0u);

        s2 = make_target(&fixture, 84u, 20u);
        ASSERT_NOT_NULL(s2);
        ASSERT_TRUE(break_world_snapshot_publication_publish(fixture.publication, s2, 7u));
        ASSERT_EQ(submit_current(&fixture, 7u, 0u), BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
                  BREAK_RUNTIME_OK);
        ASSERT_EQ(drained, 1u);
        break_world_session_stats(fixture.session, &after);
        ASSERT_EQ(after.published_full_packets, before.published_full_packets + 1u);
        ASSERT_EQ(after.published_delta_packets, before.published_delta_packets);
        break_runtime_world_session_stats(fixture.adapter, &stats);
        ASSERT_EQ(stats.publish_terminal, 0u);
        ASSERT_EQ(stats.publish_overloads, 0u);
        ASSERT_FALSE(stats.publish_pending);
        break_world_snapshot_release(s2);
        break_world_snapshot_release(s1);
        fixture_dispose(&fixture);
    }
}

TEST(publish_lifecycle_resets_scalar_state_and_cancels_old_level)
{
    Fixture fixture;
    BreakRuntimeWorldCommand close_a;
    BreakRuntimeWorldCommand rebase;
    BreakWorldSessionSenderState a_state;
    BreakWorldSessionSenderState b_state;
    BreakWorldSessionStats before;
    BreakWorldSessionStats after;
    BreakRuntimeWorldSessionStats stats;
    BreakWorldSnapshotLease lease;
    BreakWorldSnapshot *s1;
    BreakWorldSnapshot *s2;
    u64 epoch_a = 0u;
    u64 epoch_b = 0u;
    u64 old_epoch = 0u;
    usize drained = 0u;

    { /* close/reopen restarts the connection epoch and sends a fresh full. */
        ASSERT_TRUE(fixture_init_publication(&fixture, 7u, 2u, 0u));
        ASSERT_TRUE(open_connection(&fixture, KEY_A, 7u, &epoch_a));
        s1 = make_target(&fixture, 42u, 10u);
        ASSERT_NOT_NULL(s1);
        ASSERT_TRUE(break_world_snapshot_publication_publish(fixture.publication, s1, 7u));
        ASSERT_EQ(submit_current(&fixture, 7u, 0u), BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
                  BREAK_RUNTIME_OK);
        ASSERT_TRUE(control_via_adapter(&fixture, BREAK_RUNTIME_WORLD_COMMAND_ACK,
                                        KEY_A, epoch_a, 7u, 1u, s1, HIGH_CID));
        break_world_session_stats(fixture.session, &before);

        close_a = command(BREAK_RUNTIME_WORLD_COMMAND_CLOSE, KEY_A, epoch_a, 7u);
        ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &close_a, 0u),
                  BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
                  BREAK_RUNTIME_OK);
        ASSERT_EQ(drained, 1u);
        old_epoch = epoch_a;
        ASSERT_TRUE(open_connection(&fixture, KEY_A, 7u, &epoch_a));
        ASSERT_TRUE(epoch_a > old_epoch);
        ASSERT_EQ(submit_current(&fixture, 7u, 0u), BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
                  BREAK_RUNTIME_OK);
        ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_A, &a_state));
        ASSERT_EQ(a_state.next_delta_id, 2u);
        ASSERT_EQ(a_state.history_count, 1u);
        ASSERT_EQ(a_state.confirmed_snapshot_id, 0u);
        ASSERT_FALSE(a_state.attempt_pending);
        ASSERT_EQ(a_state.attempt_target_snapshot_id, 0u);
        ASSERT_EQ(a_state.attempt_target_tick, 0u);
        break_world_session_stats(fixture.session, &after);
        ASSERT_EQ(after.published_full_packets, before.published_full_packets + 1u);
        ASSERT_EQ(after.published_delta_packets, before.published_delta_packets);
        break_world_snapshot_release(s1);
        fixture_dispose(&fixture);
    }

    { /* rebaseline before publishing level8 clears old fanout and cursor. */
        ASSERT_TRUE(fixture_init_publication(&fixture, 7u, 2u, 1u));
        ASSERT_TRUE(open_connection(&fixture, KEY_A, 7u, &epoch_a));
        ASSERT_TRUE(open_connection(&fixture, KEY_B, 7u, &epoch_b));
        s1 = make_target(&fixture, 42u, 10u);
        ASSERT_NOT_NULL(s1);
        ASSERT_TRUE(break_world_snapshot_publication_publish(fixture.publication, s1, 7u));
        ASSERT_EQ(submit_current(&fixture, 7u, 0u), BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
                  BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 1u);

        s2 = make_target(&fixture, 84u, 20u);
        ASSERT_NOT_NULL(s2);
        ASSERT_TRUE(break_world_snapshot_publication_publish(fixture.publication, s2, 8u));
        rebase = command(BREAK_RUNTIME_WORLD_COMMAND_REBASELINE, 0u, 0u, 8u);
        ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &rebase, 0u),
                  BREAK_RUNTIME_OK);
        ASSERT_EQ(submit_current(&fixture, 7u, 0u), BREAK_RUNTIME_OK); /* old level, STALE */
        ASSERT_EQ(submit_current(&fixture, 8u, 0u), BREAK_RUNTIME_OK); /* new valid request */
        break_world_session_stats(fixture.session, &before);
        ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 3u, &drained),
                  BREAK_RUNTIME_STALE);
        ASSERT_EQ(drained, 3u);
        ASSERT_EQ(break_world_session_level_generation(fixture.session), 8u);
        ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_A, &a_state));
        ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_B, &b_state));
        ASSERT_EQ(a_state.next_delta_id, 2u); /* level8 delta_id=1 after rebaseline */
        ASSERT_EQ(a_state.history_count, 1u);
        ASSERT_EQ(b_state.next_delta_id, 1u); /* budget=1, B waits for next drain */
        ASSERT_EQ(b_state.history_count, 0u);
        break_world_session_stats(fixture.session, &after);
        ASSERT_EQ(after.published_full_packets, before.published_full_packets + 1u);
        break_runtime_world_session_stats(fixture.adapter, &stats);
        ASSERT_EQ(stats.publish_terminal, 0u);
        ASSERT_TRUE(stats.publish_pending);
        ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 1u);
        memset(&lease, 0, sizeof(lease));
        ASSERT_EQ(break_world_snapshot_publication_acquire(fixture.publication, &lease),
                  BREAK_WORLD_SNAPSHOT_ACQUIRE_OK);
        ASSERT_TRUE(lease.snapshot == s2);
        ASSERT_EQ(lease.level_generation, 8u);
        ASSERT_EQ(lease.publication_epoch, 2u);
        break_world_snapshot_lease_release(&lease);
        break_world_snapshot_release(s2);
        break_world_snapshot_release(s1);
        fixture_dispose(&fixture);
    }

    { /* lease level older than the rebaselined Session is terminal STALE. */
        ASSERT_TRUE(fixture_init_publication(&fixture, 7u, 2u, 0u));
        ASSERT_TRUE(open_connection(&fixture, KEY_A, 7u, &epoch_a));
        s1 = make_target(&fixture, 42u, 10u);
        ASSERT_NOT_NULL(s1);
        ASSERT_TRUE(break_world_snapshot_publication_publish(fixture.publication, s1, 7u));
        rebase = command(BREAK_RUNTIME_WORLD_COMMAND_REBASELINE, 0u, 0u, 8u);
        ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &rebase, 0u),
                  BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
                  BREAK_RUNTIME_OK);
        ASSERT_EQ(break_world_session_level_generation(fixture.session), 8u);
        ASSERT_EQ(submit_current(&fixture, 8u, 0u), BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
                  BREAK_RUNTIME_STALE);
        ASSERT_EQ(drained, 1u);
        ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 0u);
        ASSERT_EQ(break_net_reactor_outbound_count(fixture.reactor), 0u);
        break_runtime_world_session_stats(fixture.adapter, &stats);
        ASSERT_EQ(stats.publish_terminal, 1u);
        ASSERT_FALSE(stats.publish_pending);
        break_world_snapshot_release(s1);
        fixture_dispose(&fixture);
    }

    { /* wrong-level notice records STALE but does not cancel B's continuation. */
        ASSERT_TRUE(fixture_init_publication(&fixture, 7u, 2u, 1u));
        ASSERT_TRUE(open_connection(&fixture, KEY_A, 7u, &epoch_a));
        ASSERT_TRUE(open_connection(&fixture, KEY_B, 7u, &epoch_b));
        s1 = make_target(&fixture, 42u, 10u);
        ASSERT_NOT_NULL(s1);
        ASSERT_TRUE(break_world_snapshot_publication_publish(fixture.publication, s1, 7u));
        ASSERT_EQ(submit_current(&fixture, 7u, 0u), BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
                  BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 1u);
        ASSERT_EQ(submit_current(&fixture, 8u, 0u), BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
                  BREAK_RUNTIME_STALE);
        ASSERT_EQ(drained, 1u);
        ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_A, &a_state));
        ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_B, &b_state));
        ASSERT_EQ(a_state.next_delta_id, 2u); /* A does not resend */
        ASSERT_EQ(b_state.next_delta_id, 2u); /* existing continuation finishes B */
        ASSERT_EQ(b_state.history_count, 1u);
        ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 0u);
        break_runtime_world_session_stats(fixture.adapter, &stats);
        ASSERT_EQ(stats.stale_rejected, 1u);
        ASSERT_FALSE(stats.publish_pending);
        break_world_snapshot_release(s1);
        fixture_dispose(&fixture);
    }
}

/* RUNTIME_WORLD_TASK3_TESTS_ANCHOR */
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

#define LIFECYCLE_PHASE_CAPACITY 32u

typedef struct {
    Fixture *fixture;
    const char *phases[LIFECYCLE_PHASE_CAPACITY];
    u32 phase_count;
    u32 stop_producers_calls;
    u32 join_calls;
    u32 join_timeouts;
    u32 destroy_calls;
    u32 on_destroy_calls;
    bool phase_overflow;
    bool admission_closed;
    bool pending_empty_at_join;
    bool pending_empty_at_destroy;
    BreakRuntimeWorldSessionStats stats_at_join;
} LifecycleProbe;

static void lifecycle_trace(void *user_data, const char *phase)
{
    LifecycleProbe *probe = (LifecycleProbe *)user_data;
    if (probe->phase_count < LIFECYCLE_PHASE_CAPACITY) {
        probe->phases[probe->phase_count] = phase;
    } else {
        probe->phase_overflow = true;
    }
    probe->phase_count++;
    if (strcmp(phase, "destroy") == 0) {
        probe->destroy_calls++;
        probe->pending_empty_at_destroy =
            break_runtime_world_session_pending(probe->fixture->adapter) == 0u;
    }
}

static void lifecycle_on_destroy(void *user_data)
{
    LifecycleProbe *probe = (LifecycleProbe *)user_data;
    probe->on_destroy_calls++;
}

static BreakRuntimeError lifecycle_stop_producers(void *user_data)
{
    LifecycleProbe *probe = (LifecycleProbe *)user_data;
    BreakRuntimeWorldCommand item =
        command(BREAK_RUNTIME_WORLD_COMMAND_REBASELINE, 0u, 0u, 8u);
    probe->stop_producers_calls++;
    probe->admission_closed =
        break_runtime_world_session_submit(probe->fixture->adapter, &item, 0u) ==
        BREAK_RUNTIME_CLOSED;
    return BREAK_RUNTIME_OK;
}

static BreakRuntimeError lifecycle_join(void *user_data)
{
    LifecycleProbe *probe = (LifecycleProbe *)user_data;
    probe->join_calls++;
    probe->pending_empty_at_join =
        break_runtime_world_session_pending(probe->fixture->adapter) == 0u;
    break_runtime_world_session_stats(probe->fixture->adapter, &probe->stats_at_join);
    if (probe->join_timeouts != 0u) {
        probe->join_timeouts--;
        return BREAK_RUNTIME_TIMEOUT;
    }
    return BREAK_RUNTIME_OK;
}

static BreakRuntimeError lifecycle_fatal_stop_producers(void *user_data)
{
    LifecycleProbe *probe = (LifecycleProbe *)user_data;
    probe->stop_producers_calls++;
    return BREAK_RUNTIME_UNAVAILABLE;
}

static BreakRuntimeError lifecycle_fatal_join(void *user_data)
{
    LifecycleProbe *probe = (LifecycleProbe *)user_data;
    probe->join_calls++;
    return BREAK_RUNTIME_UNAVAILABLE;
}

#define RUNTIME_NOTICE_RACE_ROUNDS 32u

typedef struct {
    Fixture *fixture;
    _Atomic u32 ready;
    _Atomic bool go;
    _Atomic bool done;
    _Atomic bool failed;
    u32 accepted;
} RuntimeNoticeRace;

static PLATFORM_THREAD_RET runtime_notice_race_producer(PLATFORM_THREAD_ARG argument)
{
    RuntimeNoticeRace *race = (RuntimeNoticeRace *)argument;
    atomic_store_explicit(&race->ready, 1u, memory_order_release);
    while (!atomic_load_explicit(&race->go, memory_order_acquire)) {
        platform_thread_yield();
    }
    for (u32 i = 0u; i < RUNTIME_NOTICE_RACE_ROUNDS; ++i) {
        BreakWorldSnapshot *snapshot = make_target(race->fixture, 100u + i, (u64)i + 1u);
        if (!snapshot ||
            !break_world_snapshot_publication_publish(race->fixture->publication,
                                                       snapshot, 7u)) {
            atomic_store_explicit(&race->failed, true, memory_order_release);
            break;
        }
        for (u32 spin = 0u; spin < 1000000u; ++spin) {
            BreakRuntimeError result = submit_current(race->fixture, 7u,
                                                       UINT64_C(0xD5754) + i);
            if (result == BREAK_RUNTIME_OK) { race->accepted++; break; }
            if (result != BREAK_RUNTIME_OVERLOAD || spin == 999999u) {
                atomic_store_explicit(&race->failed, true, memory_order_release);
                break;
            }
            platform_thread_yield();
        }
        break_world_snapshot_release(snapshot);
        if (atomic_load_explicit(&race->failed, memory_order_relaxed)) break;
    }
    atomic_store_explicit(&race->done, true, memory_order_release);
    return PLATFORM_THREAD_RETURN;
}

TEST(publish_notice_producer_races_owner_drain_without_losing_latest)
{
    Fixture fixture;
    RuntimeNoticeRace race;
    PlatformThread thread;
    BreakWorldSnapshotPublicationConfig publication_config;
    BreakWorldSnapshotLease lease;
    BreakWorldSessionSenderState a_state;
    BreakRuntimeWorldSessionStats stats;
    u64 epoch_a = 0u;
    usize drained = 0u;
    bool ready = false;

    ASSERT_TRUE(fixture_init_without_adapter(&fixture, 7u));
    memset(&publication_config, 0, sizeof(publication_config));
    publication_config.schema_hash = break_schema_hash(fixture.schemas);
    publication_config.level_generation = 7u;
    fixture.publication = break_world_snapshot_publication_create(&publication_config);
    ASSERT_NOT_NULL(fixture.publication);
    ASSERT_TRUE(fixture_attach_publication(&fixture, 0u, 2u, fixture.publication, 0u));
    ASSERT_TRUE(open_connection(&fixture, KEY_A, 7u, &epoch_a));

    memset(&race, 0, sizeof(race));
    race.fixture = &fixture;
    atomic_init(&race.ready, 0u);
    atomic_init(&race.go, false);
    atomic_init(&race.done, false);
    atomic_init(&race.failed, false);
    ASSERT_TRUE(platform_thread_create(&thread, runtime_notice_race_producer, &race));
    for (u32 spin = 0u; spin < 1000000u && !ready; ++spin) {
        ready = atomic_load_explicit(&race.ready, memory_order_acquire) != 0u;
        if (!ready) platform_thread_yield();
    }
    ASSERT_TRUE(ready);
    atomic_store_explicit(&race.go, true, memory_order_release);

    for (u32 spin = 0u;
         spin < 1000000u && !atomic_load_explicit(&race.done, memory_order_acquire);
         ++spin) {
        (void)break_runtime_world_session_drain(fixture.adapter, 4u, &drained);
        clear_outbound(&fixture);
        platform_thread_yield();
    }
    platform_thread_join(thread);
    for (u32 round = 0u;
         round < 1024u && break_runtime_world_session_pending(fixture.adapter) != 0u;
         ++round) {
        clear_outbound(&fixture);
        (void)break_runtime_world_session_drain(fixture.adapter, 4u, &drained);
    }

    ASSERT_FALSE(atomic_load_explicit(&race.failed, memory_order_acquire));
    ASSERT_EQ(race.accepted, RUNTIME_NOTICE_RACE_ROUNDS);
    ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_A, &a_state));
    ASSERT_FALSE(a_state.attempt_pending);
    break_runtime_world_session_stats(fixture.adapter, &stats);
    ASSERT_EQ(stats.submitted, RUNTIME_NOTICE_RACE_ROUNDS + 1u); /* includes OPEN */
    ASSERT_EQ(stats.drained, RUNTIME_NOTICE_RACE_ROUNDS + 1u);
    ASSERT_FALSE(stats.publish_pending);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 0u);
    memset(&lease, 0, sizeof(lease));
    ASSERT_EQ(break_world_snapshot_publication_acquire(fixture.publication, &lease),
              BREAK_WORLD_SNAPSHOT_ACQUIRE_OK);
    ASSERT_EQ(break_world_snapshot_tick(lease.snapshot), (u64)RUNTIME_NOTICE_RACE_ROUNDS);
    break_world_snapshot_lease_release(&lease);

    /* A already holds the latest published target: a fresh notice for the same
     * epoch clean-skips without a new send. */
    {
        u64 next_delta_before = a_state.next_delta_id;
        ASSERT_EQ(submit_current(&fixture, 7u, 0u), BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 4u, &drained),
                  BREAK_RUNTIME_OK);
        ASSERT_EQ(drained, 1u);
        ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_A, &a_state));
        ASSERT_EQ(a_state.next_delta_id, next_delta_before);
        ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 0u);
    }
    fixture_dispose(&fixture);
}

TEST(publish_pending_gates_destroy_and_coordinator_resumes_fanout_cursor)
{
    { /* continuation pending blocks destroy; a later drain finishes B. */
        Fixture fixture;
        BreakWorldSnapshot *s1;
        BreakWorldSessionSenderState a_state;
        BreakWorldSessionSenderState b_state;
        BreakWorldSnapshotLease lease;
        u64 epoch_a = 0u;
        u64 epoch_b = 0u;
        usize drained = 0u;

        ASSERT_TRUE(fixture_init_publication(&fixture, 7u, 2u, 1u));
        ASSERT_TRUE(open_connection(&fixture, KEY_A, 7u, &epoch_a));
        ASSERT_TRUE(open_connection(&fixture, KEY_B, 7u, &epoch_b));
        s1 = make_target(&fixture, 42u, 10u);
        ASSERT_NOT_NULL(s1);
        ASSERT_TRUE(break_world_snapshot_publication_publish(fixture.publication, s1, 7u));
        ASSERT_EQ(submit_current(&fixture, 7u, 0u), BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
                  BREAK_RUNTIME_OK);
        ASSERT_EQ(drained, 1u);
        ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 1u);
        ASSERT_FALSE(break_runtime_world_session_destroy(fixture.adapter));
        ASSERT_EQ(submit_current(&fixture, 7u, 0u), BREAK_RUNTIME_CLOSED);
        ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_B, &b_state));
        ASSERT_EQ(b_state.history_count, 0u);

        ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
                  BREAK_RUNTIME_OK);
        ASSERT_EQ(drained, 0u);
        ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 0u);
        ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_A, &a_state));
        ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_B, &b_state));
        ASSERT_EQ(a_state.history_count, 1u);
        ASSERT_EQ(b_state.history_count, 1u);
        ASSERT_TRUE(break_runtime_world_session_destroy(fixture.adapter));
        fixture.adapter = NULL;
        memset(&lease, 0, sizeof(lease));
        ASSERT_EQ(break_world_snapshot_publication_acquire(fixture.publication, &lease),
                  BREAK_WORLD_SNAPSHOT_ACQUIRE_OK);
        ASSERT_TRUE(lease.snapshot == s1);
        break_world_snapshot_lease_release(&lease);
        break_world_snapshot_release(s1);
        fixture_dispose(&fixture);
    }

    { /* publication close while a continuation is pending is terminal CLOSED. */
        Fixture fixture;
        BreakWorldSnapshot *s1;
        BreakWorldSessionSenderState b_state;
        BreakRuntimeWorldSessionStats stats;
        u64 epoch_a = 0u;
        u64 epoch_b = 0u;
        usize drained = 0u;

        ASSERT_TRUE(fixture_init_publication(&fixture, 7u, 2u, 1u));
        ASSERT_TRUE(open_connection(&fixture, KEY_A, 7u, &epoch_a));
        ASSERT_TRUE(open_connection(&fixture, KEY_B, 7u, &epoch_b));
        s1 = make_target(&fixture, 42u, 10u);
        ASSERT_NOT_NULL(s1);
        ASSERT_TRUE(break_world_snapshot_publication_publish(fixture.publication, s1, 7u));
        ASSERT_EQ(submit_current(&fixture, 7u, 0u), BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
                  BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 1u);
        break_world_snapshot_publication_close(fixture.publication);
        ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
                  BREAK_RUNTIME_CLOSED);
        ASSERT_EQ(drained, 0u);
        ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 0u);
        break_runtime_world_session_stats(fixture.adapter, &stats);
        ASSERT_EQ(stats.publish_terminal, 1u);
        ASSERT_FALSE(stats.publish_pending);
        ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_B, &b_state));
        ASSERT_EQ(b_state.history_count, 0u);
        ASSERT_EQ(b_state.next_delta_id, 1u);
        ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
                  BREAK_RUNTIME_OK);
        ASSERT_EQ(drained, 0u);
        ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 0u);
        break_world_snapshot_release(s1);
        fixture_dispose(&fixture);
    }

    { /* Coordinator resumes the fanout cursor across two stop() calls. */
        Fixture fixture;
        BreakRuntimeCoordinator *coordinator = NULL;
        BreakRuntimeWorldSessionLifecycle lifecycle;
        LifecycleProbe probe;
        BreakWorldSnapshot *s1;
        BreakWorldSessionSenderState a_state;
        BreakWorldSessionSenderState b_state;
        u64 epoch_a = 0u;
        u64 epoch_b = 0u;
        static const char *expected_phases[7] = {
            "stop_admission", "stop_producers", "close_queues",
            "drain", "drain", "join", "destroy"
        };

        memset(&probe, 0, sizeof(probe));
        ASSERT_TRUE(fixture_init_publication(&fixture, 7u, 2u, 1u));
        probe.fixture = &fixture;
        ASSERT_TRUE(open_connection(&fixture, KEY_A, 7u, &epoch_a));
        ASSERT_TRUE(open_connection(&fixture, KEY_B, 7u, &epoch_b));
        s1 = make_target(&fixture, 42u, 10u);
        ASSERT_NOT_NULL(s1);
        ASSERT_TRUE(break_world_snapshot_publication_publish(fixture.publication, s1, 7u));
        ASSERT_EQ(submit_current(&fixture, 7u, 0u), BREAK_RUNTIME_OK);

        memset(&lifecycle, 0, sizeof(lifecycle));
        lifecycle.drain_budget = 1u;
        lifecycle.stop_producers = lifecycle_stop_producers;
        lifecycle.join = lifecycle_join;
        lifecycle.on_destroy = lifecycle_on_destroy;
        lifecycle.user_data = &probe;
        ASSERT_EQ(break_runtime_coordinator_create(NULL, &coordinator), BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_world_session_register_subsystem(
                      fixture.adapter, coordinator, &lifecycle),
                  BREAK_RUNTIME_OK);
        break_runtime_world_session_lifecycle_set_trace_for_test(lifecycle_trace, &probe);
        ASSERT_EQ(break_runtime_coordinator_start(coordinator), BREAK_RUNTIME_OK);

        ASSERT_EQ(break_runtime_coordinator_stop(coordinator), BREAK_RUNTIME_TIMEOUT);
        ASSERT_EQ(break_runtime_coordinator_state(coordinator), BREAK_RUNTIME_DRAINING);
        ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 1u);
        ASSERT_EQ(probe.stop_producers_calls, 1u);
        ASSERT_EQ(probe.join_calls, 0u);
        ASSERT_EQ(probe.phase_count, 4u);
        ASSERT_TRUE(probe.admission_closed);
        ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_A, &a_state));
        ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_B, &b_state));
        ASSERT_EQ(a_state.history_count, 1u);
        ASSERT_EQ(b_state.history_count, 0u);

        ASSERT_EQ(break_runtime_coordinator_stop(coordinator), BREAK_RUNTIME_OK);
        fixture.adapter = NULL;
        ASSERT_EQ(break_runtime_coordinator_state(coordinator), BREAK_RUNTIME_STOPPED);
        ASSERT_EQ(probe.on_destroy_calls, 1u);
        ASSERT_EQ(probe.join_calls, 1u);
        ASSERT_EQ(probe.destroy_calls, 1u);
        ASSERT_EQ(probe.phase_count, 7u);
        ASSERT_FALSE(probe.phase_overflow);
        for (u32 i = 0u; i < 7u; ++i) ASSERT_STR_EQ(probe.phases[i], expected_phases[i]);
        ASSERT_TRUE(probe.pending_empty_at_join);
        ASSERT_TRUE(probe.pending_empty_at_destroy);
        break_runtime_world_session_lifecycle_set_trace_for_test(NULL, NULL);
        ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_A, &a_state));
        ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_B, &b_state));
        ASSERT_EQ(a_state.history_count, 1u); /* A not resent */
        ASSERT_EQ(a_state.next_delta_id, 2u);
        ASSERT_EQ(b_state.history_count, 1u);
        break_runtime_coordinator_destroy(coordinator);
        break_world_snapshot_release(s1);
        fixture_dispose(&fixture);
    }
}

TEST(coordinator_runs_real_six_phase_shutdown_and_preserves_borrowed_owners)
{
    enum { COMMAND_COUNT = 32 };
    Fixture fixture;
    BreakRuntimeCoordinator *coordinator = NULL;
    BreakRuntimeWorldSessionLifecycle lifecycle;
    LifecycleProbe probe;
    BreakRuntimeWorldSessionStats stats;
    BreakRuntimeBusKind expected_kind = {
        BREAK_RUNTIME_WORLD_SESSION_CONTROL_KIND, 1u, 56u,
        "world_session.control", true, 0u
    };
    BreakRuntimeBusKindStats bus_stats;
    BreakWorldSnapshotPublicationConfig publication_config;
    BreakWorldSnapshotPublication *publication = NULL;
    BreakWorldSnapshot *snapshot = NULL;
    BreakWorldSnapshotLease lease;
    BreakRuntimeWorldCommand item;
    BreakNetOwnedMessage outbound;
    BreakRuntimeError stop_result;
    BreakRuntimeError repeated_stop_result = BREAK_RUNTIME_INVALID;
    u64 expected_correlations[COMMAND_COUNT];
    u64 epoch = 0u;
    u64 key = 0u;
    u32 delivered = 0u;
    bool outputs_valid = true;
    static const char *expected_phases[6] = {
        "stop_admission", "stop_producers", "close_queues", "drain", "join", "destroy"
    };

    memset(&probe, 0, sizeof(probe));
    memset(&lease, 0, sizeof(lease));
    ASSERT_TRUE(fixture_init(&fixture, 7u, 2u));
    probe.fixture = &fixture;
    ASSERT_TRUE(open_connection(&fixture, KEY_A, 7u, &epoch));
    ASSERT_EQ(break_runtime_coordinator_create(NULL, &coordinator), BREAK_RUNTIME_OK);
    ASSERT_NOT_NULL(coordinator);

    snapshot = make_target(&fixture, 42u, 10u);
    ASSERT_NOT_NULL(snapshot);
    memset(&publication_config, 0, sizeof(publication_config));
    publication_config.schema_hash = break_schema_hash(fixture.schemas);
    publication_config.level_generation = 7u;
    publication = break_world_snapshot_publication_create(&publication_config);
    ASSERT_NOT_NULL(publication);
    ASSERT_TRUE(break_world_snapshot_publication_publish(publication, snapshot, 7u));

    for (u32 i = 0u; i < COMMAND_COUNT; ++i) {
        item = command(BREAK_RUNTIME_WORLD_COMMAND_ACK, KEY_A, epoch, 7u);
        item.delta_id = (u64)i + 1u;
        item.target_snapshot_id = 1000u + (u64)i;
        item.target_tick = 2000u + (u64)i;
        if ((i & 1u) == 0u) {
            expected_correlations[i] = UINT64_C(0xD100) + (u64)i;
            ASSERT_EQ(break_runtime_world_session_submit(
                          fixture.adapter, &item, expected_correlations[i]),
                      BREAK_RUNTIME_OK);
        } else {
            expected_correlations[i] = UINT64_C(0xE100) + (u64)i;
            ASSERT_EQ(publish_external(fixture.bus, &item, expected_correlations[i], &delivered),
                      BREAK_RUNTIME_OK);
            ASSERT_EQ(delivered, 1u);
        }
    }
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), COMMAND_COUNT);

    memset(&lifecycle, 0, sizeof(lifecycle));
    lifecycle.stop_producers = lifecycle_stop_producers;
    lifecycle.join = lifecycle_join;
    lifecycle.on_destroy = lifecycle_on_destroy;
    lifecycle.user_data = &probe;
    ASSERT_EQ(break_runtime_world_session_register_subsystem(
                  fixture.adapter, coordinator, &lifecycle),
              BREAK_RUNTIME_OK);
    memset(&lifecycle, 0, sizeof(lifecycle));
    break_runtime_world_session_lifecycle_set_trace_for_test(lifecycle_trace, &probe);
    ASSERT_EQ(break_runtime_coordinator_start(coordinator), BREAK_RUNTIME_OK);
    stop_result = break_runtime_coordinator_stop(coordinator);
    if (stop_result == BREAK_RUNTIME_OK) {
        fixture.adapter = NULL;
        repeated_stop_result = break_runtime_coordinator_stop(coordinator);
    }
    break_runtime_world_session_lifecycle_set_trace_for_test(NULL, NULL);

    ASSERT_EQ(stop_result, BREAK_RUNTIME_OK);
    ASSERT_EQ(repeated_stop_result, BREAK_RUNTIME_OK);
    ASSERT_EQ(probe.on_destroy_calls, 1u);
    ASSERT_EQ(break_runtime_coordinator_state(coordinator), BREAK_RUNTIME_STOPPED);
    ASSERT_EQ(probe.phase_count, 6u);
    ASSERT_FALSE(probe.phase_overflow);
    for (u32 i = 0u; i < 6u; ++i) {
        ASSERT_STR_EQ(probe.phases[i], expected_phases[i]);
    }
    ASSERT_EQ(probe.stop_producers_calls, 1u);
    ASSERT_EQ(probe.join_calls, 1u);
    ASSERT_TRUE(probe.admission_closed);
    ASSERT_TRUE(probe.pending_empty_at_join);
    ASSERT_TRUE(probe.pending_empty_at_destroy);
    stats = probe.stats_at_join;
    ASSERT_EQ(stats.submitted, 17u);
    ASSERT_EQ(stats.drained, 33u);
    ASSERT_EQ(stats.applied, 33u);
    ASSERT_EQ(stats.rejected, 0u);
    ASSERT_EQ(stats.stale_rejected, 0u);
    ASSERT_EQ(stats.transport_overloads, 0u);
    ASSERT_EQ(stats.next_sequence, 18u);
    ASSERT_EQ(stats.queued, 0u);
    ASSERT_FALSE(stats.control_pending);

    for (u32 i = 0u; i < COMMAND_COUNT; ++i) {
        if (!next_control(&fixture, &key, &outbound)) {
            outputs_valid = false;
            break;
        }
        if (key != KEY_A || outbound.correlation_id != expected_correlations[i] ||
            !control_payload_matches(&outbound, BREAK_WORLD_SESSION_CONTROL_ACK,
                                     (u64)i + 1u, 1000u + (u64)i, 2000u + (u64)i, 7u)) {
            outputs_valid = false;
        }
        break_net_message_release(&outbound);
    }
    ASSERT_TRUE(outputs_valid);
    ASSERT_EQ(break_net_reactor_outbound_count(fixture.reactor), 0u);

    ASSERT_EQ(break_runtime_bus_kind_matches(fixture.bus, &expected_kind), BREAK_RUNTIME_OK);
    item = command(BREAK_RUNTIME_WORLD_COMMAND_ACK, KEY_A, epoch, 7u);
    item.delta_id = 99u;
    item.target_snapshot_id = 1099u;
    item.target_tick = 2099u;
    ASSERT_EQ(publish_external(fixture.bus, &item, HIGH_CID, &delivered), BREAK_RUNTIME_OK);
    ASSERT_EQ(delivered, 0u);
    ASSERT_EQ(break_runtime_bus_kind_stats(
                  fixture.bus, BREAK_RUNTIME_WORLD_SESSION_CONTROL_KIND, &bus_stats),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(bus_stats.published, 17u);
    ASSERT_EQ(bus_stats.delivered, 16u);
    ASSERT_EQ(bus_stats.dropped, 0u);
    ASSERT_EQ(break_world_session_level_generation(fixture.session), 7u);
    ASSERT_TRUE(break_world_session_baseline(fixture.session, KEY_A, NULL, NULL));
    ASSERT_EQ(break_world_snapshot_publication_acquire(publication, &lease),
              BREAK_WORLD_SNAPSHOT_ACQUIRE_OK);
    ASSERT_TRUE(lease.snapshot == snapshot);
    ASSERT_EQ(lease.level_generation, 7u);
    ASSERT_EQ(lease.publication_epoch, 1u);
    break_world_snapshot_lease_release(&lease);

    break_world_snapshot_publication_close(publication);
    break_world_snapshot_publication_destroy(publication);
    break_world_snapshot_release(snapshot);
    break_runtime_coordinator_destroy(coordinator);
    fixture_dispose(&fixture);
}

TEST(coordinator_null_lifecycle_uses_default_noop_hooks)
{
    Fixture fixture;
    BreakRuntimeCoordinator *coordinator = NULL;
    LifecycleProbe probe;
    BreakRuntimeError stop_result;
    static const char *expected_phases[6] = {
        "stop_admission", "stop_producers", "close_queues", "drain", "join", "destroy"
    };
    memset(&probe, 0, sizeof(probe));
    ASSERT_TRUE(fixture_init(&fixture, 7u, 2u));
    probe.fixture = &fixture;
    ASSERT_EQ(break_runtime_coordinator_create(NULL, &coordinator), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_register_subsystem(fixture.adapter, coordinator, NULL),
              BREAK_RUNTIME_OK);
    break_runtime_world_session_lifecycle_set_trace_for_test(lifecycle_trace, &probe);
    ASSERT_EQ(break_runtime_coordinator_start(coordinator), BREAK_RUNTIME_OK);
    stop_result = break_runtime_coordinator_stop(coordinator);
    if (stop_result == BREAK_RUNTIME_OK) fixture.adapter = NULL;
    break_runtime_world_session_lifecycle_set_trace_for_test(NULL, NULL);
    ASSERT_EQ(stop_result, BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_coordinator_state(coordinator), BREAK_RUNTIME_STOPPED);
    ASSERT_EQ(probe.phase_count, 6u);
    ASSERT_FALSE(probe.phase_overflow);
    for (u32 i = 0u; i < 6u; ++i) ASSERT_STR_EQ(probe.phases[i], expected_phases[i]);
    ASSERT_EQ(probe.stop_producers_calls, 0u);
    ASSERT_EQ(probe.join_calls, 0u);
    ASSERT_TRUE(probe.pending_empty_at_destroy);
    break_runtime_coordinator_destroy(coordinator);
    fixture_dispose(&fixture);
}

TEST(coordinator_registration_rejects_closed_adapter_without_state_changes)
{
    Fixture fixture;
    BreakRuntimeCoordinator *coordinator = NULL;
    BreakRuntimeWorldSessionStats before;
    BreakRuntimeWorldSessionStats after;
    ASSERT_TRUE(fixture_init(&fixture, 7u, 2u));
    ASSERT_EQ(break_runtime_coordinator_create(NULL, &coordinator), BREAK_RUNTIME_OK);
    break_runtime_world_session_close(fixture.adapter);
    break_runtime_world_session_stats(fixture.adapter, &before);
    ASSERT_EQ(break_runtime_world_session_register_subsystem(fixture.adapter, coordinator, NULL),
              BREAK_RUNTIME_REJECTED);
    break_runtime_world_session_stats(fixture.adapter, &after);
    ASSERT_EQ(memcmp(&before, &after, sizeof(before)), 0);
    ASSERT_EQ(break_runtime_coordinator_state(coordinator), BREAK_RUNTIME_CREATED);
    ASSERT_EQ(break_runtime_coordinator_last_error(coordinator), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_coordinator_start(coordinator), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_coordinator_stop(coordinator), BREAK_RUNTIME_OK);
    break_runtime_coordinator_destroy(coordinator);
    fixture_dispose(&fixture);
}

TEST(coordinator_registration_rejects_non_created_without_state_changes)
{
    Fixture fixture;
    BreakRuntimeCoordinator *coordinator = NULL;
    BreakRuntimeWorldSessionStats before;
    BreakRuntimeWorldSessionStats after;
    BreakRuntimeWorldCommand item;
    u64 epoch = 0u;
    usize drained = 0u;
    ASSERT_TRUE(fixture_init(&fixture, 7u, 2u));
    ASSERT_EQ(break_runtime_coordinator_create(NULL, &coordinator), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_coordinator_start(coordinator), BREAK_RUNTIME_OK);
    break_runtime_world_session_stats(fixture.adapter, &before);
    ASSERT_EQ(break_runtime_world_session_register_subsystem(fixture.adapter, coordinator, NULL),
              BREAK_RUNTIME_REJECTED);
    break_runtime_world_session_stats(fixture.adapter, &after);
    ASSERT_EQ(memcmp(&before, &after, sizeof(before)), 0);
    ASSERT_EQ(break_runtime_coordinator_state(coordinator), BREAK_RUNTIME_RUNNING);
    ASSERT_EQ(break_runtime_coordinator_last_error(coordinator), BREAK_RUNTIME_OK);
    ASSERT_TRUE(open_connection(&fixture, KEY_A, 7u, &epoch));
    ASSERT_EQ(break_runtime_coordinator_stop(coordinator), BREAK_RUNTIME_OK);
    item = command(BREAK_RUNTIME_WORLD_COMMAND_CLOSE, KEY_A, epoch, 7u);
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &item, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained), BREAK_RUNTIME_OK);
    ASSERT_EQ(drained, 1u);
    break_runtime_coordinator_destroy(coordinator);
    fixture_dispose(&fixture);
}

TEST(coordinator_registration_overload_preserves_adapter_and_coordinator)
{
    Fixture fixture;
    BreakRuntimeCoordinator *coordinator = NULL;
    BreakRuntimeCoordinatorConfig config;
    BreakRuntimeSubsystem filler;
    BreakRuntimeWorldSessionStats before;
    BreakRuntimeWorldSessionStats after;
    BreakRuntimeWorldCommand item;
    usize drained = 0u;
    memset(&config, 0, sizeof(config));
    memset(&filler, 0, sizeof(filler));
    config.max_subsystems = 1u;
    filler.name = "filler";
    ASSERT_TRUE(fixture_init(&fixture, 7u, 2u));
    ASSERT_EQ(break_runtime_coordinator_create(&config, &coordinator), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_coordinator_register_subsystem(coordinator, &filler),
              BREAK_RUNTIME_OK);
    break_runtime_world_session_stats(fixture.adapter, &before);
    ASSERT_EQ(break_runtime_world_session_register_subsystem(fixture.adapter, coordinator, NULL),
              BREAK_RUNTIME_OVERLOAD);
    break_runtime_world_session_stats(fixture.adapter, &after);
    ASSERT_EQ(memcmp(&before, &after, sizeof(before)), 0);
    ASSERT_EQ(break_runtime_coordinator_state(coordinator), BREAK_RUNTIME_CREATED);
    ASSERT_EQ(break_runtime_coordinator_last_error(coordinator), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_coordinator_start(coordinator), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_coordinator_stop(coordinator), BREAK_RUNTIME_OK);
    item = command(BREAK_RUNTIME_WORLD_COMMAND_OPEN, KEY_A, 0u, 7u);
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &item, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained), BREAK_RUNTIME_OK);
    ASSERT_EQ(drained, 1u);
    break_runtime_coordinator_destroy(coordinator);
    fixture_dispose(&fixture);
}

TEST(coordinator_bounded_drain_external_join_retry_exactly_once)
{
    enum { COMMAND_COUNT = 6 };
    Fixture fixture;
    BreakRuntimeCoordinator *coordinator = NULL;
    BreakRuntimeWorldSessionLifecycle lifecycle;
    LifecycleProbe probe;
    BreakRuntimeWorldSessionStats stats;
    BreakRuntimeBusKindStats bus_stats;
    BreakRuntimeWorldCommand item;
    BreakNetOwnedMessage outbound;
    u64 expected_correlations[COMMAND_COUNT];
    u64 epoch = 0u;
    u64 key = 0u;
    u32 delivered = 99u;
    static const char *expected_phases[9] = {
        "stop_admission", "stop_producers", "close_queues", "drain",
        "drain", "drain", "join", "join", "destroy"
    };

    memset(&probe, 0, sizeof(probe));
    ASSERT_TRUE(fixture_init(&fixture, 7u, 2u));
    probe.fixture = &fixture;
    probe.join_timeouts = 1u;
    ASSERT_TRUE(open_connection(&fixture, KEY_A, 7u, &epoch));
    for (u32 i = 0u; i < COMMAND_COUNT; ++i) {
        item = command(BREAK_RUNTIME_WORLD_COMMAND_ACK, KEY_A, epoch, 7u);
        item.delta_id = (u64)i + 1u;
        item.target_snapshot_id = 1000u + (u64)i;
        item.target_tick = 2000u + (u64)i;
        if ((i & 1u) == 0u) {
            expected_correlations[i] = UINT64_C(0xD200) + (u64)i;
            ASSERT_EQ(break_runtime_world_session_submit(
                          fixture.adapter, &item, expected_correlations[i]),
                      BREAK_RUNTIME_OK);
        } else {
            expected_correlations[i] = UINT64_C(0xE200) + (u64)i;
            ASSERT_EQ(publish_external(fixture.bus, &item, expected_correlations[i], &delivered),
                      BREAK_RUNTIME_OK);
            ASSERT_EQ(delivered, 1u);
        }
    }
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), COMMAND_COUNT);

    memset(&lifecycle, 0, sizeof(lifecycle));
    lifecycle.drain_budget = 2u;
    lifecycle.stop_producers = lifecycle_stop_producers;
    lifecycle.join = lifecycle_join;
    lifecycle.on_destroy = lifecycle_on_destroy;
    lifecycle.user_data = &probe;
    ASSERT_EQ(break_runtime_coordinator_create(NULL, &coordinator), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_register_subsystem(
                  fixture.adapter, coordinator, &lifecycle),
              BREAK_RUNTIME_OK);
    break_runtime_world_session_lifecycle_set_trace_for_test(lifecycle_trace, &probe);
    ASSERT_EQ(break_runtime_coordinator_start(coordinator), BREAK_RUNTIME_OK);

    ASSERT_EQ(break_runtime_coordinator_stop(coordinator), BREAK_RUNTIME_TIMEOUT);
    ASSERT_EQ(break_runtime_coordinator_state(coordinator), BREAK_RUNTIME_DRAINING);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 4u);
    ASSERT_EQ(probe.stop_producers_calls, 1u);
    ASSERT_EQ(probe.join_calls, 0u);
    ASSERT_EQ(probe.destroy_calls, 0u);
    ASSERT_EQ(probe.phase_count, 4u);
    ASSERT_TRUE(probe.admission_closed);

    item = command(BREAK_RUNTIME_WORLD_COMMAND_ACK, KEY_A, epoch, 7u);
    item.delta_id = 99u;
    item.target_snapshot_id = 1099u;
    item.target_tick = 2099u;
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &item, HIGH_CID),
              BREAK_RUNTIME_CLOSED);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 4u);
    ASSERT_EQ(publish_external(fixture.bus, &item, HIGH_CID, &delivered),
              BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(delivered, 0u);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 4u);

    ASSERT_EQ(break_runtime_coordinator_stop(coordinator), BREAK_RUNTIME_TIMEOUT);
    ASSERT_EQ(break_runtime_coordinator_state(coordinator), BREAK_RUNTIME_DRAINING);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 2u);
    ASSERT_EQ(probe.stop_producers_calls, 1u);
    ASSERT_EQ(probe.join_calls, 0u);
    ASSERT_EQ(probe.destroy_calls, 0u);
    ASSERT_EQ(probe.phase_count, 5u);
    ASSERT_STR_EQ(probe.phases[4], "drain");

    ASSERT_EQ(break_runtime_coordinator_stop(coordinator), BREAK_RUNTIME_TIMEOUT);
    ASSERT_EQ(break_runtime_coordinator_state(coordinator), BREAK_RUNTIME_STOPPING);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 0u);
    ASSERT_EQ(probe.stop_producers_calls, 1u);
    ASSERT_EQ(probe.join_calls, 1u);
    ASSERT_EQ(probe.destroy_calls, 0u);
    ASSERT_EQ(probe.phase_count, 7u);
    ASSERT_STR_EQ(probe.phases[5], "drain");
    ASSERT_STR_EQ(probe.phases[6], "join");

    ASSERT_EQ(break_runtime_coordinator_stop(coordinator), BREAK_RUNTIME_OK);
    fixture.adapter = NULL;
    ASSERT_EQ(break_runtime_coordinator_state(coordinator), BREAK_RUNTIME_STOPPED);
    ASSERT_EQ(probe.stop_producers_calls, 1u);
    ASSERT_EQ(probe.join_calls, 2u);
    ASSERT_EQ(probe.destroy_calls, 1u);
    ASSERT_EQ(probe.phase_count, 9u);
    ASSERT_EQ(break_runtime_coordinator_stop(coordinator), BREAK_RUNTIME_OK);
    ASSERT_EQ(probe.phase_count, 9u);
    ASSERT_EQ(probe.join_calls, 2u);
    ASSERT_EQ(probe.destroy_calls, 1u);
    break_runtime_world_session_lifecycle_set_trace_for_test(NULL, NULL);

    ASSERT_FALSE(probe.phase_overflow);
    for (u32 i = 0u; i < 9u; ++i) ASSERT_STR_EQ(probe.phases[i], expected_phases[i]);
    ASSERT_TRUE(probe.pending_empty_at_join);
    ASSERT_TRUE(probe.pending_empty_at_destroy);
    stats = probe.stats_at_join;
    ASSERT_EQ(stats.submitted, 4u);
    ASSERT_EQ(stats.drained, 7u);
    ASSERT_EQ(stats.applied, 7u);
    ASSERT_EQ(stats.rejected, 0u);
    ASSERT_EQ(stats.stale_rejected, 0u);
    ASSERT_EQ(stats.transport_overloads, 0u);
    ASSERT_EQ(stats.next_sequence, 5u);
    ASSERT_EQ(stats.queued, 0u);
    ASSERT_FALSE(stats.control_pending);

    for (u32 i = 0u; i < COMMAND_COUNT; ++i) {
        ASSERT_TRUE(next_control(&fixture, &key, &outbound));
        ASSERT_EQ(key, KEY_A);
        ASSERT_EQ(outbound.correlation_id, expected_correlations[i]);
        ASSERT_TRUE(control_payload_matches(&outbound, BREAK_WORLD_SESSION_CONTROL_ACK,
                                            (u64)i + 1u, 1000u + (u64)i,
                                            2000u + (u64)i, 7u));
        break_net_message_release(&outbound);
    }
    ASSERT_EQ(break_net_reactor_outbound_count(fixture.reactor), 0u);
    ASSERT_EQ(publish_external(fixture.bus, &item, HIGH_CID + 1u, &delivered),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(delivered, 0u);
    ASSERT_EQ(break_runtime_bus_kind_stats(
                  fixture.bus, BREAK_RUNTIME_WORLD_SESSION_CONTROL_KIND, &bus_stats),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(bus_stats.published, 5u);
    ASSERT_EQ(bus_stats.delivered, 3u);
    ASSERT_EQ(bus_stats.dropped, 1u);
    ASSERT_EQ(break_world_session_level_generation(fixture.session), 7u);
    ASSERT_TRUE(break_world_session_baseline(fixture.session, KEY_A, NULL, NULL));

    break_runtime_coordinator_destroy(coordinator);
    fixture_dispose(&fixture);
}

TEST(coordinator_transport_retry_preserves_control_then_join_retry)
{
    Fixture fixture;
    BreakRuntimeCoordinator *coordinator = NULL;
    BreakRuntimeWorldSessionLifecycle lifecycle;
    LifecycleProbe probe;
    BreakRuntimeWorldSessionStats stats;
    BreakRuntimeWorldCommand ack;
    BreakRuntimeWorldCommand need_full;
    BreakNetOwnedMessage outbound;
    u64 epoch_a = 0u;
    u64 epoch_b = 0u;
    u64 current_epoch = 0u;
    u64 key = 0u;
    static const char *expected_phases[9] = {
        "stop_admission", "stop_producers", "close_queues", "drain",
        "drain", "drain", "join", "join", "destroy"
    };

    memset(&probe, 0, sizeof(probe));
    ASSERT_TRUE(fixture_init(&fixture, 7u, 2u));
    probe.fixture = &fixture;
    probe.join_timeouts = 1u;
    ASSERT_TRUE(open_connection(&fixture, KEY_A, 7u, &epoch_a));
    ASSERT_TRUE(open_connection(&fixture, KEY_B, 7u, &epoch_b));
    ack = command(BREAK_RUNTIME_WORLD_COMMAND_ACK, KEY_A, epoch_a, 7u);
    ack.delta_id = UINT64_C(0x10000000A);
    ack.target_snapshot_id = UINT64_C(0x20000000B);
    ack.target_tick = 77u;
    need_full = command(BREAK_RUNTIME_WORLD_COMMAND_NEED_FULL, KEY_B, epoch_b, 7u);
    need_full.target_snapshot_id = 88u;
    need_full.target_tick = 99u;
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &ack, HIGH_CID),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &need_full, HIGH_CID - 1u),
              BREAK_RUNTIME_OK);
    for (u32 i = 0u; i < BREAK_NET_OUTBOUND_QUEUE_CAPACITY; ++i) {
        ASSERT_EQ(break_net_reactor_send(fixture.reactor, KEY_A, BREAK_NET_MESSAGE_ID_PING,
                                         1u, "x", 1u),
                  BREAK_NET_SEND_OK);
    }

    memset(&lifecycle, 0, sizeof(lifecycle));
    lifecycle.drain_budget = 8u;
    lifecycle.stop_producers = lifecycle_stop_producers;
    lifecycle.join = lifecycle_join;
    lifecycle.on_destroy = lifecycle_on_destroy;
    lifecycle.user_data = &probe;
    ASSERT_EQ(break_runtime_coordinator_create(NULL, &coordinator), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_register_subsystem(
                  fixture.adapter, coordinator, &lifecycle),
              BREAK_RUNTIME_OK);
    break_runtime_world_session_lifecycle_set_trace_for_test(lifecycle_trace, &probe);
    ASSERT_EQ(break_runtime_coordinator_start(coordinator), BREAK_RUNTIME_OK);

    ASSERT_EQ(break_runtime_coordinator_stop(coordinator), BREAK_RUNTIME_TIMEOUT);
    ASSERT_EQ(break_runtime_coordinator_state(coordinator), BREAK_RUNTIME_DRAINING);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 2u);
    break_runtime_world_session_stats(fixture.adapter, &stats);
    ASSERT_EQ(stats.submitted, 4u);
    ASSERT_EQ(stats.drained, 3u);
    ASSERT_EQ(stats.applied, 2u);
    ASSERT_EQ(stats.rejected, 0u);
    ASSERT_EQ(stats.transport_overloads, 1u);
    ASSERT_EQ(stats.queued, 1u);
    ASSERT_TRUE(stats.control_pending);
    ASSERT_EQ(probe.join_calls, 0u);
    ASSERT_EQ(probe.destroy_calls, 0u);
    ASSERT_EQ(probe.phase_count, 4u);

    ASSERT_EQ(break_runtime_coordinator_stop(coordinator), BREAK_RUNTIME_TIMEOUT);
    ASSERT_EQ(break_runtime_coordinator_state(coordinator), BREAK_RUNTIME_DRAINING);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 2u);
    break_runtime_world_session_stats(fixture.adapter, &stats);
    ASSERT_EQ(stats.drained, 3u);
    ASSERT_EQ(stats.applied, 2u);
    ASSERT_EQ(stats.transport_overloads, 2u);
    ASSERT_EQ(stats.queued, 1u);
    ASSERT_TRUE(stats.control_pending);
    ASSERT_EQ(probe.stop_producers_calls, 1u);
    ASSERT_EQ(probe.join_calls, 0u);
    ASSERT_EQ(probe.destroy_calls, 0u);
    ASSERT_EQ(probe.phase_count, 5u);
    ASSERT_STR_EQ(probe.phases[4], "drain");
    ASSERT_EQ(break_world_session_level_generation(fixture.session), 7u);
    ASSERT_TRUE(break_runtime_world_session_connection_epoch(fixture.adapter, KEY_A,
                                                              &current_epoch));
    ASSERT_EQ(current_epoch, epoch_a);
    ASSERT_TRUE(break_runtime_world_session_connection_epoch(fixture.adapter, KEY_B,
                                                              &current_epoch));
    ASSERT_EQ(current_epoch, epoch_b);

    clear_outbound(&fixture);
    ASSERT_EQ(break_runtime_coordinator_stop(coordinator), BREAK_RUNTIME_TIMEOUT);
    ASSERT_EQ(break_runtime_coordinator_state(coordinator), BREAK_RUNTIME_STOPPING);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 0u);
    break_runtime_world_session_stats(fixture.adapter, &stats);
    ASSERT_EQ(stats.submitted, 4u);
    ASSERT_EQ(stats.drained, 4u);
    ASSERT_EQ(stats.applied, 4u);
    ASSERT_EQ(stats.rejected, 0u);
    ASSERT_EQ(stats.transport_overloads, 2u);
    ASSERT_EQ(stats.queued, 0u);
    ASSERT_FALSE(stats.control_pending);
    ASSERT_EQ(probe.join_calls, 1u);
    ASSERT_EQ(probe.destroy_calls, 0u);
    ASSERT_EQ(probe.phase_count, 7u);

    ASSERT_EQ(break_runtime_coordinator_stop(coordinator), BREAK_RUNTIME_OK);
    fixture.adapter = NULL;
    ASSERT_EQ(break_runtime_coordinator_state(coordinator), BREAK_RUNTIME_STOPPED);
    ASSERT_EQ(probe.stop_producers_calls, 1u);
    ASSERT_EQ(probe.join_calls, 2u);
    ASSERT_EQ(probe.destroy_calls, 1u);
    ASSERT_EQ(probe.phase_count, 9u);
    ASSERT_EQ(break_runtime_coordinator_stop(coordinator), BREAK_RUNTIME_OK);
    ASSERT_EQ(probe.phase_count, 9u);
    ASSERT_EQ(probe.destroy_calls, 1u);
    break_runtime_world_session_lifecycle_set_trace_for_test(NULL, NULL);

    ASSERT_FALSE(probe.phase_overflow);
    for (u32 i = 0u; i < 9u; ++i) ASSERT_STR_EQ(probe.phases[i], expected_phases[i]);
    ASSERT_TRUE(probe.pending_empty_at_join);
    ASSERT_TRUE(probe.pending_empty_at_destroy);
    ASSERT_TRUE(next_control(&fixture, &key, &outbound));
    ASSERT_EQ(key, KEY_A);
    ASSERT_EQ(outbound.correlation_id, HIGH_CID);
    ASSERT_TRUE(control_payload_matches(&outbound, BREAK_WORLD_SESSION_CONTROL_ACK,
                                        ack.delta_id, ack.target_snapshot_id,
                                        ack.target_tick, 7u));
    break_net_message_release(&outbound);
    ASSERT_TRUE(next_control(&fixture, &key, &outbound));
    ASSERT_EQ(key, KEY_B);
    ASSERT_EQ(outbound.correlation_id, HIGH_CID - 1u);
    ASSERT_TRUE(control_payload_matches(&outbound, BREAK_WORLD_SESSION_CONTROL_NEED_FULL,
                                        0u, 88u, 99u, 7u));
    break_net_message_release(&outbound);
    ASSERT_EQ(break_net_reactor_outbound_count(fixture.reactor), 0u);

    break_runtime_coordinator_destroy(coordinator);
    fixture_dispose(&fixture);
}

TEST(coordinator_transport_close_rejects_pending_and_still_drains_queue)
{
    Fixture fixture;
    BreakRuntimeCoordinator *coordinator = NULL;
    BreakRuntimeWorldSessionLifecycle lifecycle;
    LifecycleProbe probe;
    BreakRuntimeWorldSessionStats stats;
    BreakRuntimeWorldCommand ack;
    BreakRuntimeWorldCommand need_full;
    u64 epoch_a = 0u;
    u64 epoch_b = 0u;
    static const char *expected_phases[8] = {
        "stop_admission", "stop_producers", "close_queues", "drain",
        "drain", "drain", "join", "destroy"
    };

    memset(&probe, 0, sizeof(probe));
    ASSERT_TRUE(fixture_init(&fixture, 7u, 2u));
    probe.fixture = &fixture;
    ASSERT_TRUE(open_connection(&fixture, KEY_A, 7u, &epoch_a));
    ASSERT_TRUE(open_connection(&fixture, KEY_B, 7u, &epoch_b));
    ack = command(BREAK_RUNTIME_WORLD_COMMAND_ACK, KEY_A, epoch_a, 7u);
    ack.delta_id = 11u;
    ack.target_snapshot_id = 22u;
    ack.target_tick = 33u;
    need_full = command(BREAK_RUNTIME_WORLD_COMMAND_NEED_FULL, KEY_B, epoch_b, 7u);
    need_full.target_snapshot_id = 44u;
    need_full.target_tick = 55u;
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &ack, HIGH_CID),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &need_full, HIGH_CID - 1u),
              BREAK_RUNTIME_OK);
    for (u32 i = 0u; i < BREAK_NET_OUTBOUND_QUEUE_CAPACITY; ++i) {
        ASSERT_EQ(break_net_reactor_send(fixture.reactor, KEY_A, BREAK_NET_MESSAGE_ID_PING,
                                         1u, "x", 1u),
                  BREAK_NET_SEND_OK);
    }

    memset(&lifecycle, 0, sizeof(lifecycle));
    lifecycle.drain_budget = 8u;
    lifecycle.stop_producers = lifecycle_stop_producers;
    lifecycle.join = lifecycle_join;
    lifecycle.on_destroy = lifecycle_on_destroy;
    lifecycle.user_data = &probe;
    ASSERT_EQ(break_runtime_coordinator_create(NULL, &coordinator), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_register_subsystem(
                  fixture.adapter, coordinator, &lifecycle),
              BREAK_RUNTIME_OK);
    break_runtime_world_session_lifecycle_set_trace_for_test(lifecycle_trace, &probe);
    ASSERT_EQ(break_runtime_coordinator_start(coordinator), BREAK_RUNTIME_OK);

    ASSERT_EQ(break_runtime_coordinator_stop(coordinator), BREAK_RUNTIME_TIMEOUT);
    ASSERT_EQ(break_runtime_coordinator_state(coordinator), BREAK_RUNTIME_DRAINING);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 2u);
    break_runtime_world_session_stats(fixture.adapter, &stats);
    ASSERT_EQ(stats.drained, 3u);
    ASSERT_EQ(stats.applied, 2u);
    ASSERT_EQ(stats.transport_overloads, 1u);
    ASSERT_EQ(stats.queued, 1u);
    ASSERT_TRUE(stats.control_pending);

    ASSERT_TRUE(break_net_reactor_stop(fixture.reactor, 1000u));
    clear_outbound(&fixture);
    ASSERT_EQ(break_runtime_coordinator_stop(coordinator), BREAK_RUNTIME_TIMEOUT);
    ASSERT_EQ(break_runtime_coordinator_state(coordinator), BREAK_RUNTIME_DRAINING);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 1u);
    break_runtime_world_session_stats(fixture.adapter, &stats);
    ASSERT_EQ(stats.drained, 3u);
    ASSERT_EQ(stats.applied, 2u);
    ASSERT_EQ(stats.rejected, 1u);
    ASSERT_EQ(stats.transport_overloads, 1u);
    ASSERT_EQ(stats.queued, 1u);
    ASSERT_FALSE(stats.control_pending);
    ASSERT_EQ(probe.join_calls, 0u);
    ASSERT_EQ(probe.destroy_calls, 0u);
    ASSERT_EQ(probe.phase_count, 5u);
    ASSERT_STR_EQ(probe.phases[4], "drain");

    ASSERT_EQ(break_runtime_coordinator_stop(coordinator), BREAK_RUNTIME_OK);
    fixture.adapter = NULL;
    ASSERT_EQ(break_runtime_coordinator_state(coordinator), BREAK_RUNTIME_STOPPED);
    ASSERT_EQ(probe.stop_producers_calls, 1u);
    ASSERT_EQ(probe.join_calls, 1u);
    ASSERT_EQ(probe.destroy_calls, 1u);
    ASSERT_EQ(probe.phase_count, 8u);
    ASSERT_EQ(break_runtime_coordinator_stop(coordinator), BREAK_RUNTIME_OK);
    ASSERT_EQ(probe.phase_count, 8u);
    break_runtime_world_session_lifecycle_set_trace_for_test(NULL, NULL);

    ASSERT_FALSE(probe.phase_overflow);
    for (u32 i = 0u; i < 8u; ++i) ASSERT_STR_EQ(probe.phases[i], expected_phases[i]);
    ASSERT_TRUE(probe.pending_empty_at_join);
    ASSERT_TRUE(probe.pending_empty_at_destroy);
    stats = probe.stats_at_join;
    ASSERT_EQ(stats.submitted, 4u);
    ASSERT_EQ(stats.drained, 4u);
    ASSERT_EQ(stats.applied, 2u);
    ASSERT_EQ(stats.rejected, 2u);
    ASSERT_EQ(stats.stale_rejected, 0u);
    ASSERT_EQ(stats.transport_overloads, 1u);
    ASSERT_EQ(stats.queued, 0u);
    ASSERT_FALSE(stats.control_pending);

    break_runtime_coordinator_destroy(coordinator);
    fixture_dispose(&fixture);
}

TEST(coordinator_consumed_terminal_results_with_zero_pending_complete)
{
    static const u64 expected_submitted[4] = {1u, 0u, 2u, 2u};
    static const u64 expected_drained[4] = {1u, 1u, 2u, 2u};
    static const u64 expected_applied[4] = {0u, 0u, 1u, 1u};
    static const u64 expected_stale[4] = {1u, 0u, 0u, 0u};

    for (u32 case_index = 0u; case_index < 4u; ++case_index) {
        Fixture fixture;
        BreakRuntimeCoordinator *coordinator = NULL;
        BreakRuntimeWorldSessionLifecycle lifecycle;
        LifecycleProbe probe;
        BreakRuntimeWorldSessionStats stats;
        BreakRuntimeWorldCommand item;
        u64 epoch = 0u;
        u32 delivered = 0u;

        memset(&probe, 0, sizeof(probe));
        ASSERT_TRUE(fixture_init(&fixture, 7u, 2u));
        probe.fixture = &fixture;
        if (case_index == 0u) {
            item = command(BREAK_RUNTIME_WORLD_COMMAND_OPEN, KEY_A, 0u, 8u);
            ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &item, 0u),
                      BREAK_RUNTIME_OK);
        } else if (case_index == 1u) {
            memset(&item, 0, sizeof(item));
            ASSERT_EQ(publish_external(fixture.bus, &item, HIGH_CID, &delivered),
                      BREAK_RUNTIME_OK);
            ASSERT_EQ(delivered, 1u);
        } else if (case_index == 2u) {
            item = command(BREAK_RUNTIME_WORLD_COMMAND_OPEN, KEY_A, 0u, 7u);
            ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &item, 0u),
                      BREAK_RUNTIME_OK);
            ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &item, 0u),
                      BREAK_RUNTIME_OK);
        } else {
            ASSERT_TRUE(open_connection(&fixture, KEY_A, 7u, &epoch));
            item = command(BREAK_RUNTIME_WORLD_COMMAND_ACK, KEY_A, epoch, 7u);
            item.delta_id = 1u;
            item.target_snapshot_id = 2u;
            ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &item, HIGH_CID),
                      BREAK_RUNTIME_OK);
            ASSERT_TRUE(break_net_reactor_stop(fixture.reactor, 1000u));
        }

        memset(&lifecycle, 0, sizeof(lifecycle));
        lifecycle.join = lifecycle_join;
        lifecycle.user_data = &probe;
        ASSERT_EQ(break_runtime_coordinator_create(NULL, &coordinator), BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_world_session_register_subsystem(
                      fixture.adapter, coordinator, &lifecycle),
                  BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_coordinator_start(coordinator), BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_coordinator_stop(coordinator), BREAK_RUNTIME_OK);
        fixture.adapter = NULL;
        ASSERT_EQ(break_runtime_coordinator_state(coordinator), BREAK_RUNTIME_STOPPED);
        ASSERT_EQ(probe.join_calls, 1u);
        ASSERT_TRUE(probe.pending_empty_at_join);
        stats = probe.stats_at_join;
        ASSERT_EQ(stats.submitted, expected_submitted[case_index]);
        ASSERT_EQ(stats.drained, expected_drained[case_index]);
        ASSERT_EQ(stats.applied, expected_applied[case_index]);
        ASSERT_EQ(stats.rejected, 1u);
        ASSERT_EQ(stats.stale_rejected, expected_stale[case_index]);
        ASSERT_EQ(stats.transport_overloads, 0u);
        ASSERT_EQ(stats.queued, 0u);
        ASSERT_FALSE(stats.control_pending);
        ASSERT_EQ(break_world_session_level_generation(fixture.session), 7u);

        break_runtime_coordinator_destroy(coordinator);
        fixture_dispose(&fixture);
    }
}

TEST(coordinator_destroy_false_times_out_and_retries_only_destroy)
{
    Fixture fixture;
    BreakRuntimeCoordinator *coordinator = NULL;
    BreakRuntimeWorldSessionLifecycle lifecycle;
    LifecycleProbe probe;
    BreakRuntimeWorldCommand item;
    u32 delivered = 99u;
    static const char *expected_phases[7] = {
        "stop_admission", "stop_producers", "close_queues", "drain",
        "join", "destroy", "destroy"
    };

    memset(&probe, 0, sizeof(probe));
    ASSERT_TRUE(fixture_init(&fixture, 7u, 2u));
    probe.fixture = &fixture;
    memset(&lifecycle, 0, sizeof(lifecycle));
    lifecycle.stop_producers = lifecycle_stop_producers;
    lifecycle.join = lifecycle_join;
    lifecycle.on_destroy = lifecycle_on_destroy;
    lifecycle.user_data = &probe;
    ASSERT_EQ(break_runtime_coordinator_create(NULL, &coordinator), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_register_subsystem(
                  fixture.adapter, coordinator, &lifecycle),
              BREAK_RUNTIME_OK);
    break_runtime_world_session_lifecycle_set_destroy_failures_for_test(1u);
    break_runtime_world_session_lifecycle_set_trace_for_test(lifecycle_trace, &probe);
    ASSERT_EQ(break_runtime_coordinator_start(coordinator), BREAK_RUNTIME_OK);

    ASSERT_EQ(break_runtime_coordinator_stop(coordinator), BREAK_RUNTIME_TIMEOUT);
    ASSERT_EQ(break_runtime_coordinator_state(coordinator), BREAK_RUNTIME_STOPPING);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 0u);
    ASSERT_TRUE(break_runtime_world_session_is_closed(fixture.adapter));
    ASSERT_EQ(probe.stop_producers_calls, 1u);
    ASSERT_EQ(probe.join_calls, 1u);
    ASSERT_EQ(probe.destroy_calls, 1u);
    ASSERT_EQ(probe.on_destroy_calls, 0u);
    ASSERT_EQ(probe.phase_count, 6u);
    item = command(BREAK_RUNTIME_WORLD_COMMAND_OPEN, KEY_A, 0u, 7u);
    ASSERT_EQ(publish_external(fixture.bus, &item, HIGH_CID, &delivered),
              BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(delivered, 0u);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 0u);

    ASSERT_EQ(break_runtime_coordinator_stop(coordinator), BREAK_RUNTIME_OK);
    fixture.adapter = NULL;
    ASSERT_EQ(break_runtime_coordinator_state(coordinator), BREAK_RUNTIME_STOPPED);
    ASSERT_EQ(probe.stop_producers_calls, 1u);
    ASSERT_EQ(probe.join_calls, 1u);
    ASSERT_EQ(probe.destroy_calls, 2u);
    ASSERT_EQ(probe.on_destroy_calls, 1u);
    ASSERT_EQ(probe.phase_count, 7u);
    ASSERT_EQ(break_runtime_coordinator_stop(coordinator), BREAK_RUNTIME_OK);
    ASSERT_EQ(probe.phase_count, 7u);
    ASSERT_EQ(probe.destroy_calls, 2u);
    ASSERT_EQ(probe.on_destroy_calls, 1u);
    break_runtime_world_session_lifecycle_set_trace_for_test(NULL, NULL);

    ASSERT_FALSE(probe.phase_overflow);
    for (u32 i = 0u; i < 7u; ++i) ASSERT_STR_EQ(probe.phases[i], expected_phases[i]);
    ASSERT_TRUE(probe.pending_empty_at_join);
    ASSERT_TRUE(probe.pending_empty_at_destroy);
    ASSERT_EQ(publish_external(fixture.bus, &item, HIGH_CID + 1u, &delivered),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(delivered, 0u);

    break_runtime_coordinator_destroy(coordinator);
    fixture_dispose(&fixture);
}

TEST(coordinator_duplicate_registration_same_coordinator_is_rejected)
{
    Fixture fixture;
    BreakRuntimeCoordinator *coordinator = NULL;
    BreakRuntimeWorldSessionStats before;
    BreakRuntimeWorldSessionStats after;
    LifecycleProbe probe;
    BreakRuntimeError stop_result;

    memset(&probe, 0, sizeof(probe));
    ASSERT_TRUE(fixture_init(&fixture, 7u, 2u));
    probe.fixture = &fixture;
    ASSERT_EQ(break_runtime_coordinator_create(NULL, &coordinator), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_register_subsystem(fixture.adapter, coordinator, NULL),
              BREAK_RUNTIME_OK);
    break_runtime_world_session_stats(fixture.adapter, &before);
    ASSERT_EQ(break_runtime_world_session_register_subsystem(fixture.adapter, coordinator, NULL),
              BREAK_RUNTIME_REJECTED);
    break_runtime_world_session_stats(fixture.adapter, &after);
    ASSERT_EQ(memcmp(&before, &after, sizeof(before)), 0);
    ASSERT_EQ(break_runtime_coordinator_state(coordinator), BREAK_RUNTIME_CREATED);
    ASSERT_EQ(break_runtime_coordinator_last_error(coordinator), BREAK_RUNTIME_OK);

    break_runtime_world_session_lifecycle_set_trace_for_test(lifecycle_trace, &probe);
    ASSERT_EQ(break_runtime_coordinator_start(coordinator), BREAK_RUNTIME_OK);
    stop_result = break_runtime_coordinator_stop(coordinator);
    if (stop_result == BREAK_RUNTIME_OK) fixture.adapter = NULL;
    break_runtime_world_session_lifecycle_set_trace_for_test(NULL, NULL);
    ASSERT_EQ(stop_result, BREAK_RUNTIME_OK);
    ASSERT_EQ(probe.phase_count, 6u);
    ASSERT_EQ(probe.destroy_calls, 1u);
    break_runtime_coordinator_destroy(coordinator);
    fixture_dispose(&fixture);
}

TEST(coordinator_duplicate_registration_across_coordinators_is_rejected)
{
    Fixture fixture;
    BreakRuntimeCoordinator *first = NULL;
    BreakRuntimeCoordinator *second = NULL;
    BreakRuntimeWorldSessionStats before;
    BreakRuntimeWorldSessionStats after;
    LifecycleProbe probe;
    BreakRuntimeError stop_result;

    memset(&probe, 0, sizeof(probe));
    ASSERT_TRUE(fixture_init(&fixture, 7u, 2u));
    probe.fixture = &fixture;
    ASSERT_EQ(break_runtime_coordinator_create(NULL, &first), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_coordinator_create(NULL, &second), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_register_subsystem(fixture.adapter, first, NULL),
              BREAK_RUNTIME_OK);
    break_runtime_world_session_stats(fixture.adapter, &before);
    ASSERT_EQ(break_runtime_world_session_register_subsystem(fixture.adapter, second, NULL),
              BREAK_RUNTIME_REJECTED);
    break_runtime_world_session_stats(fixture.adapter, &after);
    ASSERT_EQ(memcmp(&before, &after, sizeof(before)), 0);
    ASSERT_EQ(break_runtime_coordinator_state(first), BREAK_RUNTIME_CREATED);
    ASSERT_EQ(break_runtime_coordinator_state(second), BREAK_RUNTIME_CREATED);
    ASSERT_EQ(break_runtime_coordinator_last_error(first), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_coordinator_last_error(second), BREAK_RUNTIME_OK);

    break_runtime_world_session_lifecycle_set_trace_for_test(lifecycle_trace, &probe);
    ASSERT_EQ(break_runtime_coordinator_start(second), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_coordinator_stop(second), BREAK_RUNTIME_OK);
    ASSERT_EQ(probe.phase_count, 0u);
    ASSERT_EQ(break_runtime_coordinator_start(first), BREAK_RUNTIME_OK);
    stop_result = break_runtime_coordinator_stop(first);
    if (stop_result == BREAK_RUNTIME_OK) fixture.adapter = NULL;
    break_runtime_world_session_lifecycle_set_trace_for_test(NULL, NULL);
    ASSERT_EQ(stop_result, BREAK_RUNTIME_OK);
    ASSERT_EQ(probe.phase_count, 6u);
    ASSERT_EQ(probe.destroy_calls, 1u);
    break_runtime_coordinator_destroy(second);
    break_runtime_coordinator_destroy(first);
    fixture_dispose(&fixture);
}

TEST(coordinator_registered_adapter_direct_destroy_is_rejected)
{
    Fixture fixture;
    BreakRuntimeCoordinator *coordinator = NULL;
    BreakRuntimeWorldSessionStats before;
    BreakRuntimeWorldSessionStats after;
    LifecycleProbe probe;
    BreakRuntimeError stop_result;

    memset(&probe, 0, sizeof(probe));
    ASSERT_TRUE(fixture_init(&fixture, 7u, 2u));
    probe.fixture = &fixture;
    ASSERT_EQ(break_runtime_coordinator_create(NULL, &coordinator), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_register_subsystem(fixture.adapter, coordinator, NULL),
              BREAK_RUNTIME_OK);
    break_runtime_world_session_stats(fixture.adapter, &before);
    ASSERT_FALSE(break_runtime_world_session_destroy(fixture.adapter));
    break_runtime_world_session_stats(fixture.adapter, &after);
    ASSERT_EQ(memcmp(&before, &after, sizeof(before)), 0);
    ASSERT_FALSE(break_runtime_world_session_is_closed(fixture.adapter));
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 0u);

    break_runtime_world_session_lifecycle_set_trace_for_test(lifecycle_trace, &probe);
    ASSERT_EQ(break_runtime_coordinator_start(coordinator), BREAK_RUNTIME_OK);
    stop_result = break_runtime_coordinator_stop(coordinator);
    if (stop_result == BREAK_RUNTIME_OK) fixture.adapter = NULL;
    break_runtime_world_session_lifecycle_set_trace_for_test(NULL, NULL);
    ASSERT_EQ(stop_result, BREAK_RUNTIME_OK);
    ASSERT_EQ(probe.phase_count, 6u);
    ASSERT_EQ(probe.destroy_calls, 1u);
    break_runtime_coordinator_destroy(coordinator);
    fixture_dispose(&fixture);
}

TEST(coordinator_abandon_created_restores_adapter_ownership)
{
    Fixture fixture;
    BreakRuntimeCoordinator *coordinator = NULL;
    BreakRuntimeWorldSessionLifecycle lifecycle;
    LifecycleProbe probe;
    u64 epoch = 0u;

    memset(&probe, 0, sizeof(probe));
    ASSERT_TRUE(fixture_init(&fixture, 7u, 2u));
    probe.fixture = &fixture;
    memset(&lifecycle, 0, sizeof(lifecycle));
    lifecycle.on_destroy = lifecycle_on_destroy;
    lifecycle.user_data = &probe;
    ASSERT_EQ(break_runtime_coordinator_create(NULL, &coordinator), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_register_subsystem(fixture.adapter, coordinator, &lifecycle),
              BREAK_RUNTIME_OK);
    break_runtime_world_session_lifecycle_set_trace_for_test(lifecycle_trace, &probe);
    ASSERT_FALSE(break_runtime_world_session_abandon(NULL, coordinator));
    ASSERT_FALSE(break_runtime_world_session_abandon(fixture.adapter, NULL));
    ASSERT_TRUE(break_runtime_world_session_abandon(fixture.adapter, coordinator));
    ASSERT_EQ(break_runtime_coordinator_state(coordinator), BREAK_RUNTIME_CREATED);
    ASSERT_EQ(break_runtime_coordinator_last_error(coordinator), BREAK_RUNTIME_OK);
    ASSERT_EQ(probe.phase_count, 0u);
    ASSERT_FALSE(break_runtime_world_session_is_closed(fixture.adapter));

    ASSERT_EQ(break_runtime_coordinator_start(coordinator), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_coordinator_stop(coordinator), BREAK_RUNTIME_OK);
    ASSERT_EQ(probe.phase_count, 0u);
    ASSERT_TRUE(open_connection(&fixture, KEY_A, 7u, &epoch));
    ASSERT_TRUE(break_runtime_world_session_destroy(fixture.adapter));
    fixture.adapter = NULL;
    ASSERT_EQ(probe.on_destroy_calls, 0u);
    break_runtime_world_session_lifecycle_set_trace_for_test(NULL, NULL);
    break_runtime_coordinator_destroy(coordinator);
    fixture_dispose(&fixture);
}

TEST(coordinator_abandon_running_preserves_binding_for_normal_stop)
{
    Fixture fixture;
    BreakRuntimeCoordinator *coordinator = NULL;
    BreakRuntimeWorldSessionStats before;
    BreakRuntimeWorldSessionStats after;
    LifecycleProbe probe;
    BreakRuntimeError stop_result;

    memset(&probe, 0, sizeof(probe));
    ASSERT_TRUE(fixture_init(&fixture, 7u, 2u));
    probe.fixture = &fixture;
    ASSERT_EQ(break_runtime_coordinator_create(NULL, &coordinator), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_register_subsystem(fixture.adapter, coordinator, NULL),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_coordinator_start(coordinator), BREAK_RUNTIME_OK);
    break_runtime_world_session_stats(fixture.adapter, &before);
    ASSERT_FALSE(break_runtime_world_session_abandon(fixture.adapter, coordinator));
    break_runtime_world_session_stats(fixture.adapter, &after);
    ASSERT_EQ(memcmp(&before, &after, sizeof(before)), 0);
    ASSERT_EQ(break_runtime_coordinator_state(coordinator), BREAK_RUNTIME_RUNNING);
    ASSERT_EQ(break_runtime_coordinator_last_error(coordinator), BREAK_RUNTIME_OK);

    break_runtime_world_session_lifecycle_set_trace_for_test(lifecycle_trace, &probe);
    stop_result = break_runtime_coordinator_stop(coordinator);
    if (stop_result == BREAK_RUNTIME_OK) fixture.adapter = NULL;
    break_runtime_world_session_lifecycle_set_trace_for_test(NULL, NULL);
    ASSERT_EQ(stop_result, BREAK_RUNTIME_OK);
    ASSERT_EQ(probe.phase_count, 6u);
    ASSERT_EQ(probe.destroy_calls, 1u);
    break_runtime_coordinator_destroy(coordinator);
    fixture_dispose(&fixture);
}

TEST(coordinator_abandon_failed_stop_producers_allows_manual_drain_and_destroy)
{
    Fixture fixture;
    BreakRuntimeCoordinator *coordinator = NULL;
    BreakRuntimeWorldSessionLifecycle lifecycle;
    LifecycleProbe probe;
    BreakRuntimeWorldCommand item;
    usize drained = 0u;

    memset(&probe, 0, sizeof(probe));
    ASSERT_TRUE(fixture_init(&fixture, 7u, 2u));
    probe.fixture = &fixture;
    item = command(BREAK_RUNTIME_WORLD_COMMAND_OPEN, KEY_A, 0u, 7u);
    ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &item, 0u), BREAK_RUNTIME_OK);
    memset(&lifecycle, 0, sizeof(lifecycle));
    lifecycle.stop_producers = lifecycle_fatal_stop_producers;
    lifecycle.on_destroy = lifecycle_on_destroy;
    lifecycle.user_data = &probe;
    ASSERT_EQ(break_runtime_coordinator_create(NULL, &coordinator), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_register_subsystem(
                  fixture.adapter, coordinator, &lifecycle),
              BREAK_RUNTIME_OK);
    break_runtime_world_session_lifecycle_set_trace_for_test(lifecycle_trace, &probe);
    ASSERT_EQ(break_runtime_coordinator_start(coordinator), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_coordinator_stop(coordinator), BREAK_RUNTIME_UNAVAILABLE);
    ASSERT_EQ(break_runtime_coordinator_state(coordinator), BREAK_RUNTIME_STATE_FAILED);
    ASSERT_EQ(break_runtime_coordinator_last_error(coordinator), BREAK_RUNTIME_UNAVAILABLE);
    ASSERT_EQ(probe.phase_count, 2u);
    ASSERT_EQ(probe.destroy_calls, 0u);
    ASSERT_EQ(probe.on_destroy_calls, 0u);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 1u);
    ASSERT_TRUE(break_runtime_world_session_is_closed(fixture.adapter));

    ASSERT_TRUE(break_runtime_world_session_abandon(fixture.adapter, coordinator));
    ASSERT_EQ(break_runtime_coordinator_state(coordinator), BREAK_RUNTIME_STATE_FAILED);
    ASSERT_EQ(break_runtime_coordinator_last_error(coordinator), BREAK_RUNTIME_UNAVAILABLE);
    ASSERT_EQ(probe.phase_count, 2u);
    break_runtime_world_session_lifecycle_set_trace_for_test(NULL, NULL);
    break_runtime_coordinator_destroy(coordinator);

    break_runtime_world_session_close(fixture.adapter);
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(drained, 1u);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 0u);
    ASSERT_TRUE(break_runtime_world_session_destroy(fixture.adapter));
    fixture.adapter = NULL;
    ASSERT_EQ(probe.on_destroy_calls, 0u);
    fixture_dispose(&fixture);
}

TEST(coordinator_abandon_failed_join_allows_manual_destroy)
{
    Fixture fixture;
    BreakRuntimeCoordinator *coordinator = NULL;
    BreakRuntimeWorldSessionLifecycle lifecycle;
    LifecycleProbe probe;
    usize drained = 99u;

    memset(&probe, 0, sizeof(probe));
    ASSERT_TRUE(fixture_init(&fixture, 7u, 2u));
    probe.fixture = &fixture;
    memset(&lifecycle, 0, sizeof(lifecycle));
    lifecycle.join = lifecycle_fatal_join;
    lifecycle.on_destroy = lifecycle_on_destroy;
    lifecycle.user_data = &probe;
    ASSERT_EQ(break_runtime_coordinator_create(NULL, &coordinator), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_register_subsystem(
                  fixture.adapter, coordinator, &lifecycle),
              BREAK_RUNTIME_OK);
    break_runtime_world_session_lifecycle_set_trace_for_test(lifecycle_trace, &probe);
    ASSERT_EQ(break_runtime_coordinator_start(coordinator), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_coordinator_stop(coordinator), BREAK_RUNTIME_UNAVAILABLE);
    ASSERT_EQ(break_runtime_coordinator_state(coordinator), BREAK_RUNTIME_STATE_FAILED);
    ASSERT_EQ(break_runtime_coordinator_last_error(coordinator), BREAK_RUNTIME_UNAVAILABLE);
    ASSERT_EQ(probe.phase_count, 5u);
    ASSERT_EQ(probe.join_calls, 1u);
    ASSERT_EQ(probe.destroy_calls, 0u);
    ASSERT_EQ(probe.on_destroy_calls, 0u);
    ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 0u);

    ASSERT_TRUE(break_runtime_world_session_abandon(fixture.adapter, coordinator));
    ASSERT_EQ(break_runtime_coordinator_state(coordinator), BREAK_RUNTIME_STATE_FAILED);
    ASSERT_EQ(break_runtime_coordinator_last_error(coordinator), BREAK_RUNTIME_UNAVAILABLE);
    ASSERT_EQ(probe.phase_count, 5u);
    break_runtime_world_session_lifecycle_set_trace_for_test(NULL, NULL);
    break_runtime_coordinator_destroy(coordinator);

    break_runtime_world_session_close(fixture.adapter);
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(drained, 0u);
    ASSERT_TRUE(break_runtime_world_session_destroy(fixture.adapter));
    fixture.adapter = NULL;
    ASSERT_EQ(probe.on_destroy_calls, 0u);
    fixture_dispose(&fixture);
}

TEST_MAIN_BEGIN()
RUN_TEST(publish_notice_layout_submit_and_external_bus_contract);
RUN_TEST(publish_notice_basic_s1_full_has_no_pre_drain_effects);
RUN_TEST(publish_notice_connections_keep_independent_full_delta_and_dedup);
RUN_TEST(publish_notice_empty_closed_wrong_level_and_no_open_connections);
RUN_TEST(publish_budget_one_round_robin_continues_without_queue_message);
RUN_TEST(publish_default_budget_eight_defers_ninth_connection);
RUN_TEST(publish_overload_resumes_e1_before_latest_e2);
RUN_TEST(publish_unknown_old_attempt_does_not_complete_current);
RUN_TEST(publish_overload_across_connections_does_not_abort_fanout);
RUN_TEST(publish_terminal_dedup_new_epoch_and_need_full_rules);
RUN_TEST(publish_lifecycle_resets_scalar_state_and_cancels_old_level);
RUN_TEST(publish_pending_gates_destroy_and_coordinator_resumes_fanout_cursor);
RUN_TEST(publish_notice_producer_races_owner_drain_without_losing_latest);
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
RUN_TEST(coordinator_runs_real_six_phase_shutdown_and_preserves_borrowed_owners);
RUN_TEST(coordinator_null_lifecycle_uses_default_noop_hooks);
RUN_TEST(coordinator_registration_rejects_closed_adapter_without_state_changes);
RUN_TEST(coordinator_registration_rejects_non_created_without_state_changes);
RUN_TEST(coordinator_registration_overload_preserves_adapter_and_coordinator);
RUN_TEST(coordinator_bounded_drain_external_join_retry_exactly_once);
RUN_TEST(coordinator_transport_retry_preserves_control_then_join_retry);
RUN_TEST(coordinator_transport_close_rejects_pending_and_still_drains_queue);
RUN_TEST(coordinator_consumed_terminal_results_with_zero_pending_complete);
RUN_TEST(coordinator_destroy_false_times_out_and_retries_only_destroy);
RUN_TEST(coordinator_duplicate_registration_same_coordinator_is_rejected);
RUN_TEST(coordinator_duplicate_registration_across_coordinators_is_rejected);
RUN_TEST(coordinator_registered_adapter_direct_destroy_is_rejected);
RUN_TEST(coordinator_abandon_created_restores_adapter_ownership);
RUN_TEST(coordinator_abandon_running_preserves_binding_for_normal_stop);
RUN_TEST(coordinator_abandon_failed_stop_producers_allows_manual_drain_and_destroy);
RUN_TEST(coordinator_abandon_failed_join_allows_manual_destroy);
TEST_MAIN_END()
