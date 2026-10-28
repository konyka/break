#include "test_framework.h"
#include <network/break_replication.h>
#include <network/break_net_adapter.h>
#include <snow/acceptor.h>
#include <snow/endpoint.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

static snow_acceptor_t *g_test_acceptor;

static BreakNetReactor *make_reactor(void)
{
    BreakNetReactorConfig config = {0};
    snow_endpoint_t *endpoint = NULL;
    BreakNetReactor *reactor;

    config.drive_mode = BREAK_NET_DRIVE_STEP;
    config.logical_index = 0;
    config.max_connections = 8u;
    config.empty_connection_timeout_ms = 1000;
    config.watchdog_interval_ms = 1000u;
    config.step_timeout_ms = 1u;
    reactor = break_net_reactor_create(&config);
    if (reactor == NULL || snow_endpoint_create(&endpoint) != SNOW_OK ||
        snow_endpoint_set_host(endpoint, "127.0.0.1") != SNOW_OK ||
        snow_endpoint_set_port(endpoint, 0) != SNOW_OK ||
        snow_acceptor_create(endpoint, &g_test_acceptor) != SNOW_OK) {
        snow_endpoint_destroy(endpoint);
        return reactor;
    }
    snow_endpoint_destroy(endpoint);
    if (snow_acceptor_bind(g_test_acceptor, 1) != SNOW_OK ||
        !break_net_reactor_set_acceptor(reactor, g_test_acceptor) ||
        !break_net_reactor_start(reactor))
        return reactor;
    return reactor;
}

static void destroy_reactor(BreakNetReactor *reactor)
{
    if (reactor != NULL) {
        break_net_reactor_stop(reactor, 1000u);
        break_net_reactor_destroy(reactor);
    }
    if (g_test_acceptor != NULL) {
        snow_acceptor_destroy(g_test_acceptor);
        g_test_acceptor = NULL;
    }
}

TEST(replication_scope_sends_baseline_then_dirty_and_destroy)
{
    BreakNetReactor *reactor = make_reactor();
    BreakReplication *replication = break_replication_create(reactor, 10u, 11u, 12u, 13u);
    BreakReplicationObject object = {42u, 7u, {0.0f, 0.0f, 0.0f}, 0u, 5u};
    const uint8_t baseline[] = {1u, 2u};
    const uint8_t delta[] = {3u};
    BreakAoIResult result = {0};

    ASSERT_NOT_NULL(reactor);
    ASSERT_NOT_NULL(replication);
    ASSERT_TRUE(break_replication_register(replication, &object, baseline, sizeof(baseline)));
    ASSERT_TRUE(break_replication_connection_open(replication, 9u, 100u));
    result.enter = &object.entity_id;
    result.enter_count = 1u;
    ASSERT_TRUE(break_replication_sync(replication, 9u, &result));
    ASSERT_EQ(break_net_reactor_outbound_count(reactor), 1u);
    ASSERT_TRUE(break_replication_mark_dirty(replication, object.entity_id, delta, sizeof(delta)));
    result.enter = NULL;
    result.enter_count = 0u;
    result.stay = &object.entity_id;
    result.stay_count = 1u;
    ASSERT_TRUE(break_replication_sync(replication, 9u, &result));
    ASSERT_EQ(break_net_reactor_outbound_count(reactor), 2u);
    result.stay = NULL;
    result.stay_count = 0u;
    result.leave = &object.entity_id;
    result.leave_count = 1u;
    ASSERT_TRUE(break_replication_sync(replication, 9u, &result));
    ASSERT_EQ(break_net_reactor_outbound_count(reactor), 3u);
    break_replication_destroy(replication);
    destroy_reactor(reactor);
}

TEST(replication_budget_defers_lower_priority_and_disconnect_cleans)
{
    BreakNetReactor *reactor = make_reactor();
    BreakReplication *replication = break_replication_create(reactor, 20u, 21u, 22u, 23u);
    BreakReplicationObject high = {1u, 0u, {0}, 0u, 10u};
    BreakReplicationObject low = {2u, 0u, {0}, 0u, 1u};
    const uint8_t payload[8] = {0};
    BreakAoIResult scope = {0};
    BreakAoIEntityId ids[] = {1u, 2u};

    ASSERT_NOT_NULL(replication);
    ASSERT_TRUE(break_replication_register(replication, &low, payload, sizeof(payload)));
    ASSERT_TRUE(break_replication_register(replication, &high, payload, sizeof(payload)));
    ASSERT_TRUE(break_replication_connection_open(replication, 5u, 25u));
    scope.enter = ids;
    scope.enter_count = 2u;
    ASSERT_TRUE(break_replication_sync_budget(replication, 5u, &scope, 25u));
    ASSERT_EQ(break_net_reactor_outbound_count(reactor), 1u);
    {
        BreakNetOwnedMessage message = {0};
        uint64_t connection = 0u;
        ASSERT_EQ(break_net_reactor_poll_outbound_for_test(reactor, &connection, &message), BREAK_NET_EVENT_OK);
        ASSERT_EQ(connection, 5u);
        ASSERT_EQ(message.message_id, 20u);
        ASSERT_EQ(((const uint8_t *)message.data)[0], BREAK_REPLICATION_BASELINE);
        ASSERT_EQ(((const uint8_t *)message.data)[1], 1u);
        break_net_message_release(&message);
    }
    ASSERT_TRUE(break_replication_disconnect(replication, 5u));
    ASSERT_EQ(break_replication_connection_count(replication), 0u);
    break_replication_destroy(replication);
    destroy_reactor(reactor);
}

TEST(replication_retries_dirty_and_duplicate_enter_without_duplicate_baseline)
{
    BreakNetReactor *reactor = make_reactor();
    BreakReplication *replication = break_replication_create(reactor, 20u, 21u, 22u, 23u);
    BreakReplicationObject object = {9u, 0u, {0}, 0u, 5u};
    uint8_t payload = 0xabu;
    BreakAoIResult result = {0};
    BreakNetOwnedMessage message = {0};
    uint64_t connection = 0u;

    ASSERT_TRUE(break_replication_register(replication, &object, &payload, 1u));
    ASSERT_TRUE(break_replication_connection_open(replication, 1u, 0u));
    result.enter = &object.entity_id;
    result.enter_count = 1u;
    ASSERT_TRUE(break_replication_sync_budget(replication, 1u, &result, 0u));
    ASSERT_EQ(break_net_reactor_outbound_count(reactor), 0u);
    ASSERT_TRUE(break_replication_sync_budget(replication, 1u, &result, 32u));
    ASSERT_EQ(break_net_reactor_outbound_count(reactor), 1u);
    ASSERT_TRUE(break_replication_sync_budget(replication, 1u, &result, 32u));
    ASSERT_EQ(break_net_reactor_outbound_count(reactor), 1u);
    payload = 0x5cu;
    ASSERT_TRUE(break_replication_mark_dirty(replication, object.entity_id, &payload, 1u));
    result.enter = NULL;
    result.enter_count = 0u;
    result.stay = &object.entity_id;
    result.stay_count = 1u;
    ASSERT_TRUE(break_replication_sync_budget(replication, 1u, &result, 0u));
    ASSERT_EQ(break_net_reactor_outbound_count(reactor), 1u);
    ASSERT_TRUE(break_replication_sync_budget(replication, 1u, &result, 32u));
    ASSERT_EQ(break_net_reactor_outbound_count(reactor), 2u);
    ASSERT_EQ(break_net_reactor_poll_outbound_for_test(reactor, &connection, &message), BREAK_NET_EVENT_OK);
    ASSERT_EQ(connection, 1u);
    ASSERT_EQ(message.message_id, 20u);
    ASSERT_EQ(message.size, 18u);
    ASSERT_EQ(((const uint8_t *)message.data)[0], BREAK_REPLICATION_BASELINE);
    ASSERT_EQ(((const uint8_t *)message.data)[17], 0xabu);
    break_net_message_release(&message);
    ASSERT_EQ(break_net_reactor_poll_outbound_for_test(reactor, &connection, &message), BREAK_NET_EVENT_OK);
    ASSERT_EQ(message.message_id, 21u);
    ASSERT_EQ(((const uint8_t *)message.data)[0], BREAK_REPLICATION_DIRTY);
    ASSERT_EQ(((const uint8_t *)message.data)[17], 0x5cu);
    break_net_message_release(&message);
    ASSERT_TRUE(break_replication_disconnect(replication, 1u));
    break_replication_destroy(replication);
    destroy_reactor(reactor);
}

TEST(replication_rejects_overflowed_aoi_sizes_without_state_change)
{
    BreakNetReactor *reactor = make_reactor();
    BreakReplication *replication = break_replication_create(reactor, 40u, 41u, 42u, 43u);
    BreakReplicationObject object = {88u, 0u, {0}, 0u, 1u};
    BreakAoIResult scope = {0};
    BreakAoIEntityId id = object.entity_id;

    ASSERT_NOT_NULL(replication);
    ASSERT_TRUE(break_replication_register(replication, &object, NULL, 0u));
    ASSERT_TRUE(break_replication_connection_open(replication, 8u, 100u));
    scope.enter = &id;
    scope.enter_count = SIZE_MAX;
    ASSERT_TRUE(!break_replication_sync_budget(replication, 8u, &scope, 100u));
    ASSERT_EQ(break_replication_connection_count(replication), 1u);
    ASSERT_EQ(break_net_reactor_outbound_count(reactor), 0u);
    break_replication_destroy(replication);
    destroy_reactor(reactor);
}

TEST(replication_rejects_version_wrap_without_replacing_dirty_object)
{
    BreakNetReactor *reactor = make_reactor();
    BreakReplication *replication = break_replication_create(reactor, 50u, 51u, 52u, 53u);
    BreakReplicationObject object = {101u, 0u, {0}, 0u, 1u};
    const uint8_t old_payload = 0x11u;
    const uint8_t new_payload = 0x22u;
    BreakAoIResult result = {0};
    BreakNetOwnedMessage message = {0};
    uint64_t connection = 0u;

    ASSERT_TRUE(break_replication_register(replication, &object, &old_payload, 1u));
    ASSERT_TRUE(break_replication_test_set_version(replication, object.entity_id, UINT64_MAX));
    ASSERT_TRUE(!break_replication_mark_dirty(replication, object.entity_id, &new_payload, 1u));
    ASSERT_TRUE(break_replication_connection_open(replication, 10u, 32u));
    result.enter = &object.entity_id;
    result.enter_count = 1u;
    ASSERT_TRUE(break_replication_sync_budget(replication, 10u, &result, 32u));
    ASSERT_EQ(break_net_reactor_outbound_count(reactor), 1u);
    ASSERT_EQ(break_net_reactor_poll_outbound_for_test(reactor, &connection, &message), BREAK_NET_EVENT_OK);
    ASSERT_EQ(connection, 10u);
    ASSERT_EQ(message.message_id, 50u);
    ASSERT_EQ(((const uint8_t *)message.data)[17], old_payload);
    break_net_message_release(&message);
    break_replication_destroy(replication);
    destroy_reactor(reactor);
}

TEST(replication_rejects_version_wrap_without_replacing_registered_object)
{
    BreakNetReactor *reactor = make_reactor();
    BreakReplication *replication = break_replication_create(reactor, 60u, 61u, 62u, 63u);
    BreakReplicationObject object = {102u, 0u, {0}, 0u, 1u};
    const uint8_t old_payload = 0x33u;
    const uint8_t new_payload = 0x44u;
    BreakAoIResult result = {0};
    BreakNetOwnedMessage message = {0};
    uint64_t connection = 0u;

    ASSERT_TRUE(break_replication_register(replication, &object, &old_payload, 1u));
    ASSERT_TRUE(break_replication_test_set_version(replication, object.entity_id, UINT64_MAX));
    ASSERT_TRUE(!break_replication_register(replication, &object, &new_payload, 1u));
    ASSERT_TRUE(break_replication_connection_open(replication, 11u, 32u));
    result.enter = &object.entity_id;
    result.enter_count = 1u;
    ASSERT_TRUE(break_replication_sync_budget(replication, 11u, &result, 32u));
    ASSERT_EQ(break_net_reactor_outbound_count(reactor), 1u);
    ASSERT_EQ(break_net_reactor_poll_outbound_for_test(reactor, &connection, &message), BREAK_NET_EVENT_OK);
    ASSERT_EQ(connection, 11u);
    ASSERT_EQ(message.message_id, 60u);
    ASSERT_EQ(((const uint8_t *)message.data)[17], old_payload);
    break_net_message_release(&message);
    break_replication_destroy(replication);
    destroy_reactor(reactor);
}

TEST(replication_retries_after_outbound_queue_overload)
{
    BreakNetReactor *reactor = make_reactor();
    BreakReplication *replication = break_replication_create(reactor, 30u, 31u, 32u, 33u);
    BreakReplicationObject object = {77u, 0u, {0}, 0u, 1u};
    uint8_t payload = 0x44u;
    BreakAoIResult result = {&object.entity_id, 1u, NULL, 0u, NULL, 0u};
    size_t i;

    ASSERT_TRUE(break_replication_register(replication, &object, &payload, 1u));
    ASSERT_TRUE(break_replication_connection_open(replication, 7u, 32u));
    for (i = 0u; i < BREAK_NET_OUTBOUND_QUEUE_CAPACITY; ++i)
        ASSERT_EQ(break_net_reactor_send(reactor, 99u, 99u, 1u, &payload, 1u), BREAK_NET_SEND_OK);
    ASSERT_EQ(break_net_reactor_send(reactor, 99u, 99u, 1u, &payload, 1u), BREAK_NET_SEND_OVERLOAD);
    ASSERT_TRUE(break_replication_sync(replication, 7u, &result));
    ASSERT_EQ(break_net_reactor_outbound_count(reactor), BREAK_NET_OUTBOUND_QUEUE_CAPACITY);
    {
        BreakNetOwnedMessage message = {0};
        uint64_t connection = 0u;
        ASSERT_EQ(break_net_reactor_poll_outbound_for_test(reactor, &connection, &message), BREAK_NET_EVENT_OK);
        break_net_message_release(&message);
    }
    ASSERT_TRUE(break_replication_sync(replication, 7u, &result));
    ASSERT_EQ(break_net_reactor_outbound_count(reactor), BREAK_NET_OUTBOUND_QUEUE_CAPACITY);
    {
        bool found_replication = false;
        while (break_net_reactor_outbound_count(reactor) != 0u) {
            BreakNetOwnedMessage message = {0};
            uint64_t connection = 0u;
            ASSERT_EQ(break_net_reactor_poll_outbound_for_test(reactor, &connection, &message), BREAK_NET_EVENT_OK);
            if (connection == 7u) {
                ASSERT_EQ(message.message_id, 30u);
                ASSERT_EQ(((const uint8_t *)message.data)[0], BREAK_REPLICATION_BASELINE);
                ASSERT_EQ(((const uint8_t *)message.data)[17], payload);
                found_replication = true;
            }
            break_net_message_release(&message);
        }
        ASSERT_TRUE(found_replication);
    }
    break_replication_destroy(replication);
    destroy_reactor(reactor);
}

TEST_MAIN_BEGIN()
    RUN_TEST(replication_scope_sends_baseline_then_dirty_and_destroy);
    RUN_TEST(replication_budget_defers_lower_priority_and_disconnect_cleans);
    RUN_TEST(replication_retries_dirty_and_duplicate_enter_without_duplicate_baseline);
    RUN_TEST(replication_rejects_overflowed_aoi_sizes_without_state_change);
    RUN_TEST(replication_rejects_version_wrap_without_replacing_dirty_object);
    RUN_TEST(replication_rejects_version_wrap_without_replacing_registered_object);
    RUN_TEST(replication_retries_after_outbound_queue_overload);
TEST_MAIN_END()
