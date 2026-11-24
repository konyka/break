#include "test_framework.h"

#include <network/break_net_message.h>
#include <network/break_net_message_registry.h>
#include <network/break_online_aspect_session.h>
#include <network/break_replication_wire.h>
#include <snow/acceptor.h>
#include <snow/endpoint.h>

#include <stdint.h>
#include <string.h>

#define TEST_PACKET_CAPACITY 256u
#define TEST_COMPLETION_CAPACITY 8u

typedef struct AspectSessionFixture {
    BreakAspectStore *authoritative;
    BreakAspectStore *remote;
    BreakAspectSession *session;
    BreakOnlineHandle object;
    uint64_t now;
} AspectSessionFixture;

typedef struct AspectReactorFixture {
    BreakNetReactor *reactor;
    SnowAcceptor *acceptor;
} AspectReactorFixture;

static uint64_t test_aspect_session_clock(void *user)
{
    return *(const uint64_t *)user;
}

static BreakAspectSessionConfig test_aspect_session_config(BreakAspectStore *store,
                                                            uint64_t *now)
{
    BreakAspectSessionConfig config;
    memset(&config, 0, sizeof(config));
    config.store = store;
    config.bridge.max_connections = 2u;
    config.bridge.stream_capacity = 4u;
    config.bridge.max_pending_bytes_per_connection = 1024u;
    config.bridge.max_total_pending_bytes = 2048u;
    config.bridge.max_fragment_bytes = 64u;
    config.bridge.max_fragment_count = 16u;
    config.bridge.completion_capacity = TEST_COMPLETION_CAPACITY;
    config.bridge.max_completion_packet_bytes = TEST_PACKET_CAPACITY;
    config.bridge.max_completion_queue_bytes = 2u * TEST_PACKET_CAPACITY;
    config.bridge.expiry_interval = 5u;
    config.bridge.expiry_max_idle = 10u;
    config.bridge.clock = test_aspect_session_clock;
    config.bridge.clock_user = now;
    return config;
}

static BreakAspectStore *test_aspect_store(void)
{
    BreakAspectStoreConfig config = {4u, 16u, TEST_PACKET_CAPACITY};
    BreakAspectSchema health = {2u, 1u, BREAK_ASPECT_U32, 4u};
    BreakAspectStore *store = NULL;
    if (break_aspect_store_create(&config, &store) != BREAK_RUNTIME_OK) return NULL;
    if (break_aspect_schema_register(store, &health) != BREAK_RUNTIME_OK) {
        break_aspect_store_destroy(store);
        return NULL;
    }
    return store;
}

static bool test_fixture_init_with(AspectSessionFixture *fixture,
                                   BreakNetReactor *reactor, bool expiry_enabled)
{
    BreakAspectSessionConfig config;
    memset(fixture, 0, sizeof(*fixture));
    fixture->authoritative = test_aspect_store();
    fixture->remote = test_aspect_store();
    if (!fixture->authoritative || !fixture->remote ||
        break_aspect_object_create(fixture->authoritative, &fixture->object) !=
            BREAK_RUNTIME_OK ||
        break_aspect_object_adopt(fixture->remote, fixture->object) != BREAK_RUNTIME_OK) {
        return false;
    }
    config = test_aspect_session_config(fixture->remote, &fixture->now);
    config.bridge.reactor = reactor;
    config.bridge.expiry_enabled = expiry_enabled;
    fixture->session = break_aspect_session_create(&config);
    return fixture->session != NULL;
}

static bool test_fixture_init(AspectSessionFixture *fixture)
{
    return test_fixture_init_with(fixture, NULL, false);
}

static void test_fixture_dispose(AspectSessionFixture *fixture)
{
    break_aspect_session_destroy(fixture->session);
    break_aspect_store_destroy(fixture->remote);
    break_aspect_store_destroy(fixture->authoritative);
    memset(fixture, 0, sizeof(*fixture));
}

static bool test_encode_baseline(AspectSessionFixture *fixture, u32 value, u64 epoch,
                                 u8 *packet, usize *packet_size)
{
    return break_aspect_set_u32(fixture->authoritative, fixture->object, 2u, value) ==
               BREAK_RUNTIME_OK &&
           break_aspect_encode_with_epoch(
               fixture->authoritative, fixture->object,
               break_aspect_active_mask(fixture->authoritative, fixture->object),
               BREAK_ASPECT_BASELINE, epoch, packet, TEST_PACKET_CAPACITY,
               packet_size) == BREAK_RUNTIME_OK;
}

static bool test_encode_dirty(AspectSessionFixture *fixture, u32 value, u64 epoch,
                              u8 *packet, usize *packet_size)
{
    return break_aspect_set_u32(fixture->authoritative, fixture->object, 2u, value) ==
               BREAK_RUNTIME_OK &&
           break_aspect_encode_with_epoch(
               fixture->authoritative, fixture->object, UINT64_C(1) << 1u,
               BREAK_ASPECT_DIRTY, epoch, packet, TEST_PACKET_CAPACITY,
               packet_size) == BREAK_RUNTIME_OK;
}

static bool test_push_fragment(BreakAspectSession *session, BreakConnectionKey connection,
                               const BreakReplicationFragment *fragment)
{
    u8 wire[BREAK_REPLICATION_WIRE_HEADER_SIZE + 64u];
    usize wire_size = 0u;
    BreakNetOwnedMessage message;
    memset(&message, 0, sizeof(message));
    if (break_replication_wire_encode(fragment, wire, sizeof(wire), &wire_size) !=
        BREAK_REPLICATION_FRAGMENT_OK) {
        return false;
    }
    message.message_id = BREAK_NET_MESSAGE_ID_REPLICATION_FRAGMENT;
    message.protocol_version = BREAK_REPLICATION_WIRE_VERSION;
    message.sequence = 1u;
    message.data = wire;
    message.size = wire_size;
    return break_replication_session_handle_message(
        connection, &message, break_aspect_session_bridge(session));
}

static bool test_push_payload(BreakAspectSession *session, BreakConnectionKey connection,
                              u64 delta_id, u64 base_id, const void *payload,
                              usize payload_size)
{
    BreakReplicationFragment *fragments = NULL;
    usize count = 0u;
    usize i;
    bool handled = true;
    if (break_replication_fragment_payload(delta_id, base_id, payload, payload_size,
                                           17u, &fragments, &count) !=
        BREAK_REPLICATION_FRAGMENT_OK) {
        return false;
    }
    for (i = 0u; i < count; ++i) {
        if (!test_push_fragment(session, connection, &fragments[i])) {
            handled = false;
            break;
        }
    }
    break_replication_fragments_free(fragments, count);
    return handled;
}

static bool test_push_fixture_packet(AspectSessionFixture *fixture,
                                     BreakConnectionKey connection, u64 delta_id,
                                     const void *packet, usize packet_size)
{
    return test_push_payload(fixture->session, connection, delta_id,
                             break_aspect_schema_hash(fixture->remote), packet,
                             packet_size);
}

static void test_store_u64(u8 *out, u64 value)
{
    u32 i;
    for (i = 0u; i < 8u; ++i) out[i] = (u8)(value >> (i * 8u));
}

static bool test_reactor_start(AspectReactorFixture *fixture)
{
    BreakNetReactorConfig config = {BREAK_NET_DRIVE_STEP, 0, 4u, 1000, 1000u, 1u};
    SnowEndpoint *endpoint = NULL;
    memset(fixture, 0, sizeof(*fixture));
    if (SnowEndpointCreate(&endpoint) != SNOW_OK ||
        SnowEndpointSetHost(endpoint, "127.0.0.1") != SNOW_OK ||
        SnowEndpointSetPort(endpoint, 0) != SNOW_OK ||
        SnowAcceptorCreate(endpoint, &fixture->acceptor) != SNOW_OK) {
        SnowEndpointDestroy(endpoint);
        return false;
    }
    SnowEndpointDestroy(endpoint);
    if (SnowAcceptorBind(fixture->acceptor, 1) != SNOW_OK) {
        SnowAcceptorDestroy(fixture->acceptor);
        fixture->acceptor = NULL;
        return false;
    }
    fixture->reactor = break_net_reactor_create(&config);
    if (!fixture->reactor ||
        !break_net_reactor_set_acceptor(fixture->reactor, fixture->acceptor) ||
        !break_net_reactor_start(fixture->reactor)) {
        break_net_reactor_destroy(fixture->reactor);
        SnowAcceptorDestroy(fixture->acceptor);
        memset(fixture, 0, sizeof(*fixture));
        return false;
    }
    return true;
}

static void test_reactor_dispose(AspectReactorFixture *fixture)
{
    if (fixture->reactor) {
        (void)break_net_reactor_stop(fixture->reactor, 1000u);
        break_net_reactor_destroy(fixture->reactor);
    }
    if (fixture->acceptor) SnowAcceptorDestroy(fixture->acceptor);
    memset(fixture, 0, sizeof(*fixture));
}

TEST(aspect_session_create_validate_and_null_calls_are_safe)
{
    uint64_t now = 0u;
    BreakAspectStore *store = test_aspect_store();
    BreakAspectSessionConfig config = test_aspect_session_config(store, &now);
    BreakAspectSessionConfig invalid;
    BreakAspectSession *session;
    BreakAspectSessionStats stats;
    BreakAspectSessionStats zero;
    BreakReplicationFragment fragment;

    ASSERT_NOT_NULL(store);
    memset(&fragment, 0, sizeof(fragment));
    memset(&zero, 0, sizeof(zero));
    ASSERT_TRUE(break_aspect_session_create(NULL) == NULL);
    invalid = config;
    invalid.store = NULL;
    ASSERT_TRUE(break_aspect_session_create(&invalid) == NULL);
    invalid = config;
    invalid.bridge.clock = NULL;
    ASSERT_TRUE(break_aspect_session_create(&invalid) == NULL);
    session = break_aspect_session_create(&config);
    ASSERT_NOT_NULL(session);
    ASSERT_NOT_NULL(break_aspect_session_bridge(session));
    ASSERT_TRUE(break_aspect_session_bridge(NULL) == NULL);
    ASSERT_FALSE(break_aspect_session_open(NULL, 1u));
    ASSERT_FALSE(break_aspect_session_open(session, 0u));
    ASSERT_TRUE(break_aspect_session_open(session, 1u));
    ASSERT_FALSE(break_aspect_session_open(session, 1u));
    ASSERT_FALSE(break_aspect_session_close(NULL, 1u));
    ASSERT_FALSE(break_aspect_session_close(session, 2u));
    ASSERT_TRUE(break_aspect_session_close(session, 1u));
    ASSERT_EQ(break_aspect_session_tick(NULL, 0u), 0u);
    ASSERT_EQ(break_aspect_session_drain(NULL, 1u), 0u);
    ASSERT_EQ(break_aspect_session_send(NULL, 1u, &fragment), BREAK_RUNTIME_CLOSED);
    memset(&stats, 0xa5, sizeof(stats));
    break_aspect_session_stats(NULL, &stats);
    ASSERT_TRUE(memcmp(&stats, &zero, sizeof(stats)) == 0);
    break_aspect_session_stats(session, NULL);
    break_aspect_session_stats(session, &stats);
    ASSERT_TRUE(memcmp(&stats, &zero, sizeof(stats)) == 0);
    break_aspect_session_destroy(session);
    break_aspect_session_destroy(NULL);
    break_aspect_store_destroy(store);
}

TEST(aspect_session_handler_queues_valid_bra1_without_mutating_store)
{
    AspectSessionFixture fixture;
    BreakAspectSessionStats stats;
    u8 packet[TEST_PACKET_CAPACITY];
    usize packet_size = 0u;
    u32 value = 0u;

    ASSERT_TRUE(test_fixture_init(&fixture));
    ASSERT_TRUE(break_aspect_session_open(fixture.session, 11u));
    ASSERT_TRUE(test_encode_baseline(&fixture, 42u, 1u, packet, &packet_size));
    ASSERT_TRUE(test_push_fixture_packet(&fixture, 11u, 9u, packet, packet_size));
    break_aspect_session_stats(fixture.session, &stats);
    ASSERT_EQ(stats.bridge.connections, 1u);
    ASSERT_EQ(stats.bridge.completed_packets, 1u);
    ASSERT_EQ(stats.bridge.completion_count, 1u);
    ASSERT_EQ(stats.applied_packets, 0u);
    ASSERT_EQ(stats.rejected_packets, 0u);
    ASSERT_EQ(stats.drained_packets, 0u);
    ASSERT_EQ(break_aspect_active_mask(fixture.remote, fixture.object), 0u);
    ASSERT_EQ(break_aspect_get_u32(fixture.remote, fixture.object, 2u, &value),
              BREAK_RUNTIME_FAILED);
    ASSERT_EQ(value, 0u);
    test_fixture_dispose(&fixture);
}

TEST(aspect_session_open_uses_schema_base_and_drain_applies_valid_bra1)
{
    AspectSessionFixture fixture;
    BreakAspectSessionStats stats;
    u8 packet[TEST_PACKET_CAPACITY];
    usize packet_size = 0u;
    u32 value = 0u;

    ASSERT_TRUE(test_fixture_init(&fixture));
    ASSERT_TRUE(break_aspect_session_open(fixture.session, 11u));
    ASSERT_TRUE(test_encode_baseline(&fixture, 42u, 1u, packet, &packet_size));
    ASSERT_TRUE(test_push_fixture_packet(&fixture, 11u, 9u, packet, packet_size));
    break_aspect_session_stats(fixture.session, &stats);
    ASSERT_EQ(stats.bridge.connections, 1u);
    ASSERT_EQ(stats.bridge.completed_packets, 1u);
    ASSERT_EQ(stats.bridge.completion_count, 1u);
    ASSERT_EQ(stats.bridge.completion_bytes, packet_size);
    ASSERT_EQ(stats.applied_packets, 0u);
    ASSERT_EQ(stats.rejected_packets, 0u);
    ASSERT_EQ(stats.drained_packets, 0u);
    ASSERT_EQ(break_aspect_active_mask(fixture.remote, fixture.object), 0u);
    ASSERT_EQ(break_aspect_object_revision(fixture.remote, fixture.object), 0u);
    ASSERT_EQ(break_aspect_get_u32(fixture.remote, fixture.object, 2u, &value),
              BREAK_RUNTIME_FAILED);
    ASSERT_EQ(break_aspect_session_drain(fixture.session, 1u), 1u);
    ASSERT_EQ(break_aspect_get_u32(fixture.remote, fixture.object, 2u, &value),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(value, 42u);
    ASSERT_EQ(break_aspect_active_mask(fixture.remote, fixture.object), UINT64_C(1) << 1u);
    break_aspect_session_stats(fixture.session, &stats);
    ASSERT_EQ(stats.applied_packets, 1u);
    ASSERT_EQ(stats.rejected_packets, 0u);
    ASSERT_EQ(stats.drained_packets, 1u);
    ASSERT_EQ(stats.bridge.completed_packets, 1u);
    ASSERT_EQ(stats.bridge.completion_count, 0u);
    ASSERT_EQ(stats.bridge.completion_bytes, 0u);
    test_fixture_dispose(&fixture);
}

TEST(aspect_session_schema_mismatch_is_rejected_then_valid_packet_still_drains)
{
    AspectSessionFixture fixture;
    BreakAspectSessionStats stats;
    u8 packet[TEST_PACKET_CAPACITY];
    u8 mismatched[TEST_PACKET_CAPACITY];
    usize packet_size = 0u;
    u32 value = 0u;

    ASSERT_TRUE(test_fixture_init(&fixture));
    ASSERT_TRUE(break_aspect_session_open(fixture.session, 11u));
    ASSERT_EQ(break_aspect_set_u32(fixture.remote, fixture.object, 2u, 99u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_aspect_object_revision(fixture.remote, fixture.object), 1u);
    ASSERT_TRUE(test_encode_baseline(&fixture, 7u, 1u, packet, &packet_size));
    memcpy(mismatched, packet, packet_size);
    test_store_u64(mismatched + 4u, break_aspect_schema_hash(fixture.remote) ^ 1u);
    ASSERT_TRUE(test_push_fixture_packet(&fixture, 11u, 1u, mismatched, packet_size));
    ASSERT_EQ(break_aspect_session_drain(fixture.session, 1u), 1u);
    ASSERT_EQ(break_aspect_get_u32(fixture.remote, fixture.object, 2u, &value),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(value, 99u);
    ASSERT_EQ(break_aspect_object_revision(fixture.remote, fixture.object), 1u);
    break_aspect_session_stats(fixture.session, &stats);
    ASSERT_EQ(stats.applied_packets, 0u);
    ASSERT_EQ(stats.rejected_packets, 1u);
    ASSERT_EQ(stats.drained_packets, 1u);
    ASSERT_EQ(stats.bridge.completion_count, 0u);
    ASSERT_EQ(stats.bridge.completion_bytes, 0u);

    ASSERT_TRUE(test_push_fixture_packet(&fixture, 11u, 2u, packet, packet_size));
    ASSERT_EQ(break_aspect_session_drain(fixture.session, 1u), 1u);
    ASSERT_EQ(break_aspect_get_u32(fixture.remote, fixture.object, 2u, &value),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(value, 7u);
    break_aspect_session_stats(fixture.session, &stats);
    ASSERT_EQ(stats.applied_packets, 1u);
    ASSERT_EQ(stats.rejected_packets, 1u);
    ASSERT_EQ(stats.drained_packets, 2u);
    ASSERT_EQ(stats.drained_packets, stats.applied_packets + stats.rejected_packets);
    ASSERT_EQ(stats.bridge.completed_packets, 2u);
    ASSERT_EQ(stats.bridge.completion_count, 0u);
    ASSERT_EQ(stats.bridge.completion_bytes, 0u);
    test_fixture_dispose(&fixture);
}

TEST(aspect_session_drain_zero_leaves_completion_and_store_untouched)
{
    AspectSessionFixture fixture;
    BreakAspectSessionStats stats;
    u8 packet[TEST_PACKET_CAPACITY];
    usize packet_size = 0u;
    u32 value = 0u;

    ASSERT_TRUE(test_fixture_init(&fixture));
    ASSERT_TRUE(break_aspect_session_open(fixture.session, 11u));
    ASSERT_TRUE(test_encode_baseline(&fixture, 77u, 1u, packet, &packet_size));
    ASSERT_TRUE(test_push_fixture_packet(&fixture, 11u, 1u, packet, packet_size));
    ASSERT_EQ(break_aspect_session_drain(fixture.session, 0u), 0u);
    break_aspect_session_stats(fixture.session, &stats);
    ASSERT_EQ(stats.drained_packets, 0u);
    ASSERT_EQ(stats.bridge.completion_count, 1u);
    ASSERT_EQ(stats.bridge.completion_bytes, packet_size);
    ASSERT_EQ(break_aspect_active_mask(fixture.remote, fixture.object), 0u);
    ASSERT_EQ(break_aspect_get_u32(fixture.remote, fixture.object, 2u, &value),
              BREAK_RUNTIME_FAILED);
    ASSERT_EQ(break_aspect_session_drain(fixture.session, 1u), 1u);
    ASSERT_EQ(value, 0u);
    ASSERT_EQ(break_aspect_get_u32(fixture.remote, fixture.object, 2u, &value),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(value, 77u);
    test_fixture_dispose(&fixture);
}

TEST(aspect_session_drain_preserves_fifo_and_partial_limits)
{
    AspectSessionFixture fixture;
    BreakAspectSessionStats stats;
    u8 baseline[TEST_PACKET_CAPACITY];
    u8 dirty[TEST_PACKET_CAPACITY];
    usize baseline_size = 0u;
    usize dirty_size = 0u;
    u32 value = 0u;

    ASSERT_TRUE(test_fixture_init(&fixture));
    ASSERT_TRUE(break_aspect_session_open(fixture.session, 11u));
    ASSERT_TRUE(test_encode_baseline(&fixture, 10u, 1u, baseline, &baseline_size));
    ASSERT_TRUE(test_encode_dirty(&fixture, 11u, 2u, dirty, &dirty_size));
    ASSERT_TRUE(test_push_fixture_packet(&fixture, 11u, 1u, baseline, baseline_size));
    ASSERT_TRUE(test_push_fixture_packet(&fixture, 11u, 2u, dirty, dirty_size));
    break_aspect_session_stats(fixture.session, &stats);
    ASSERT_EQ(stats.bridge.completion_count, 2u);
    ASSERT_EQ(break_aspect_session_drain(fixture.session, 1u), 1u);
    ASSERT_EQ(break_aspect_get_u32(fixture.remote, fixture.object, 2u, &value),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(value, 10u);
    break_aspect_session_stats(fixture.session, &stats);
    ASSERT_EQ(stats.applied_packets, 1u);
    ASSERT_EQ(stats.drained_packets, 1u);
    ASSERT_EQ(stats.bridge.completion_count, 1u);
    ASSERT_EQ(stats.bridge.completion_bytes, dirty_size);
    ASSERT_EQ(break_aspect_session_drain(fixture.session, 8u), 1u);
    ASSERT_EQ(break_aspect_get_u32(fixture.remote, fixture.object, 2u, &value),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(value, 11u);
    break_aspect_session_stats(fixture.session, &stats);
    ASSERT_EQ(stats.applied_packets, 2u);
    ASSERT_EQ(stats.rejected_packets, 0u);
    ASSERT_EQ(stats.drained_packets, 2u);
    ASSERT_EQ(stats.bridge.completion_count, 0u);
    ASSERT_EQ(stats.bridge.completion_bytes, 0u);
    ASSERT_EQ(break_aspect_session_drain(fixture.session, 8u), 0u);
    test_fixture_dispose(&fixture);
}

TEST(aspect_session_close_drops_only_matching_completions)
{
    AspectSessionFixture fixture;
    BreakAspectSessionStats stats;
    u8 packet[TEST_PACKET_CAPACITY];
    usize packet_size = 0u;
    u32 value = 0u;

    ASSERT_TRUE(test_fixture_init(&fixture));
    ASSERT_TRUE(break_aspect_session_open(fixture.session, 11u));
    ASSERT_TRUE(break_aspect_session_open(fixture.session, 22u));
    ASSERT_TRUE(test_encode_baseline(&fixture, 5u, 1u, packet, &packet_size));
    ASSERT_TRUE(test_push_fixture_packet(&fixture, 11u, 40u, packet, packet_size));
    ASSERT_TRUE(test_push_fixture_packet(&fixture, 22u, 40u, packet, packet_size));
    ASSERT_TRUE(break_aspect_session_close(fixture.session, 11u));
    ASSERT_FALSE(break_aspect_session_close(fixture.session, 11u));
    break_aspect_session_stats(fixture.session, &stats);
    ASSERT_EQ(stats.bridge.connections, 1u);
    ASSERT_EQ(stats.bridge.completed_packets, 2u);
    ASSERT_EQ(stats.bridge.dropped_completions, 1u);
    ASSERT_EQ(stats.bridge.completion_count, 1u);
    ASSERT_EQ(stats.bridge.completion_bytes, packet_size);
    ASSERT_EQ(break_aspect_session_drain(fixture.session, 8u), 1u);
    ASSERT_EQ(break_aspect_get_u32(fixture.remote, fixture.object, 2u, &value),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(value, 5u);
    break_aspect_session_stats(fixture.session, &stats);
    ASSERT_EQ(stats.applied_packets, 1u);
    ASSERT_EQ(stats.drained_packets, 1u);
    ASSERT_EQ(stats.bridge.dropped_completions, 1u);
    ASSERT_EQ(stats.bridge.completion_count, 0u);
    test_fixture_dispose(&fixture);
}

TEST(aspect_session_key_reuse_resets_bridge_high_water)
{
    AspectSessionFixture fixture;
    BreakAspectSessionStats stats;
    u8 baseline[TEST_PACKET_CAPACITY];
    u8 dirty[TEST_PACKET_CAPACITY];
    usize baseline_size = 0u;
    usize dirty_size = 0u;
    u32 value = 0u;

    ASSERT_TRUE(test_fixture_init(&fixture));
    ASSERT_TRUE(break_aspect_session_open(fixture.session, 7u));
    ASSERT_TRUE(test_encode_baseline(&fixture, 1u, 1u, baseline, &baseline_size));
    ASSERT_TRUE(test_push_fixture_packet(&fixture, 7u, 40u, baseline, baseline_size));
    ASSERT_EQ(break_aspect_session_drain(fixture.session, 1u), 1u);
    ASSERT_TRUE(break_aspect_session_close(fixture.session, 7u));
    ASSERT_TRUE(break_aspect_session_open(fixture.session, 7u));
    ASSERT_TRUE(test_encode_dirty(&fixture, 2u, 2u, dirty, &dirty_size));
    ASSERT_TRUE(test_push_fixture_packet(&fixture, 7u, 1u, dirty, dirty_size));
    break_aspect_session_stats(fixture.session, &stats);
    ASSERT_EQ(stats.bridge.completed_packets, 2u);
    ASSERT_EQ(stats.bridge.rejected_fragments, 0u);
    ASSERT_EQ(stats.bridge.completion_count, 1u);
    ASSERT_EQ(break_aspect_session_drain(fixture.session, 1u), 1u);
    ASSERT_EQ(break_aspect_get_u32(fixture.remote, fixture.object, 2u, &value),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(value, 2u);
    break_aspect_session_stats(fixture.session, &stats);
    ASSERT_EQ(stats.applied_packets, 2u);
    ASSERT_EQ(stats.drained_packets, 2u);
    ASSERT_EQ(stats.bridge.connections, 1u);
    test_fixture_dispose(&fixture);
}

TEST(aspect_session_tick_forwards_bridge_expiry)
{
    AspectSessionFixture fixture;
    BreakAspectSessionStats stats;
    BreakReplicationFragment *fragments = NULL;
    usize fragment_count = 0u;
    u8 packet[TEST_PACKET_CAPACITY];
    usize packet_size = 0u;

    ASSERT_TRUE(test_fixture_init_with(&fixture, NULL, true));
    ASSERT_TRUE(break_aspect_session_open(fixture.session, 11u));
    ASSERT_TRUE(test_encode_baseline(&fixture, 3u, 1u, packet, &packet_size));
    fixture.now = 100u;
    ASSERT_EQ(break_replication_fragment_payload(
                  1u, break_aspect_schema_hash(fixture.remote), packet, packet_size,
                  8u, &fragments, &fragment_count),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_TRUE(fragment_count > 1u);
    ASSERT_TRUE(test_push_fragment(fixture.session, 11u, &fragments[0]));
    break_aspect_session_stats(fixture.session, &stats);
    ASSERT_EQ(stats.bridge.pending_bytes, 8u);
    ASSERT_EQ(break_aspect_session_tick(fixture.session, 104u), 0u);
    ASSERT_EQ(break_aspect_session_tick(fixture.session, 110u), 1u);
    break_aspect_session_stats(fixture.session, &stats);
    ASSERT_EQ(stats.bridge.expired_streams, 1u);
    ASSERT_EQ(stats.bridge.pending_bytes, 0u);
    ASSERT_EQ(stats.drained_packets, 0u);
    break_replication_fragments_free(fragments, fragment_count);
    test_fixture_dispose(&fixture);
}

TEST(aspect_session_send_maps_invalid_and_closed_without_reactor)
{
    AspectSessionFixture fixture;
    BreakReplicationFragment fragment;
    u8 data = 0x5au;

    ASSERT_TRUE(test_fixture_init(&fixture));
    ASSERT_TRUE(break_aspect_session_open(fixture.session, 11u));
    memset(&fragment, 0, sizeof(fragment));
    fragment.delta_id = 1u;
    fragment.base_id = break_aspect_schema_hash(fixture.remote);
    fragment.fragment_count = 1u;
    fragment.checksum = 1u;
    fragment.data = &data;
    fragment.size = 1u;
    ASSERT_EQ(break_aspect_session_send(fixture.session, 11u, &fragment),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_aspect_session_send(fixture.session, 99u, &fragment),
              BREAK_RUNTIME_CLOSED);
    test_fixture_dispose(&fixture);
}

TEST(aspect_session_send_forwards_brfg_v1_and_maps_overload)
{
    AspectReactorFixture reactor;
    AspectSessionFixture fixture;
    BreakReplicationFragment fragment;
    BreakReplicationFragment decoded;
    BreakNetOwnedMessage outbound;
    BreakConnectionKey outbound_connection = 0u;
    u8 data[] = {0xaau, 0xbbu, 0xccu, 0xddu};
    usize i;

    ASSERT_TRUE(test_reactor_start(&reactor));
    ASSERT_TRUE(test_fixture_init_with(&fixture, reactor.reactor, false));
    ASSERT_TRUE(break_aspect_session_open(fixture.session, 0x123u));
    memset(&fragment, 0, sizeof(fragment));
    fragment.delta_id = 1u;
    fragment.base_id = break_aspect_schema_hash(fixture.remote);
    fragment.fragment_count = 1u;
    fragment.checksum = 0x11223344u;
    fragment.data = data;
    fragment.size = sizeof(data);
    ASSERT_EQ(break_aspect_session_send(fixture.session, 0x123u, &fragment),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_net_reactor_poll_outbound_for_test(
                  reactor.reactor, &outbound_connection, &outbound),
              BREAK_NET_EVENT_OK);
    ASSERT_EQ(outbound_connection, 0x123u);
    ASSERT_EQ(outbound.message_id, BREAK_NET_MESSAGE_ID_REPLICATION_FRAGMENT);
    ASSERT_EQ(outbound.protocol_version, BREAK_REPLICATION_WIRE_VERSION);
    ASSERT_EQ(break_replication_wire_decode(outbound.data, outbound.size, &decoded),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(decoded.delta_id, fragment.delta_id);
    ASSERT_EQ(decoded.base_id, fragment.base_id);
    ASSERT_EQ(decoded.fragment_count, 1u);
    ASSERT_EQ(decoded.checksum, fragment.checksum);
    ASSERT_EQ(decoded.size, sizeof(data));
    ASSERT_TRUE(memcmp(decoded.data, data, sizeof(data)) == 0);
    break_net_message_release(&outbound);

    fragment.base_id++;
    ASSERT_EQ(break_aspect_session_send(fixture.session, 0x123u, &fragment),
              BREAK_RUNTIME_INVALID);
    fragment.base_id--;
    for (i = 0u; i < BREAK_NET_OUTBOUND_QUEUE_CAPACITY; ++i) {
        ASSERT_EQ(break_net_reactor_send(reactor.reactor, 0x123u,
                                         BREAK_NET_MESSAGE_ID_PING, 1u, "x", 1u),
                  BREAK_NET_SEND_OK);
    }
    ASSERT_EQ(break_aspect_session_send(fixture.session, 0x123u, &fragment),
              BREAK_RUNTIME_OVERLOAD);
    test_fixture_dispose(&fixture);
    test_reactor_dispose(&reactor);
}

TEST_MAIN_BEGIN()
    RUN_TEST(aspect_session_create_validate_and_null_calls_are_safe);
    RUN_TEST(aspect_session_handler_queues_valid_bra1_without_mutating_store);
    RUN_TEST(aspect_session_open_uses_schema_base_and_drain_applies_valid_bra1);
    RUN_TEST(aspect_session_schema_mismatch_is_rejected_then_valid_packet_still_drains);
    RUN_TEST(aspect_session_drain_zero_leaves_completion_and_store_untouched);
    RUN_TEST(aspect_session_drain_preserves_fifo_and_partial_limits);
    RUN_TEST(aspect_session_close_drops_only_matching_completions);
    RUN_TEST(aspect_session_key_reuse_resets_bridge_high_water);
    RUN_TEST(aspect_session_tick_forwards_bridge_expiry);
    RUN_TEST(aspect_session_send_maps_invalid_and_closed_without_reactor);
    RUN_TEST(aspect_session_send_forwards_brfg_v1_and_maps_overload);
TEST_MAIN_END()
