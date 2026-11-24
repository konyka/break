#include "test_framework.h"

#include <network/break_net_adapter.h>
#include <network/break_replication_session.h>
#include <network/break_replication_wire.h>
#include <network/break_session.h>
#include <snow/acceptor.h>
#include <snow/endpoint.h>

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define TEST_MAX_PENDING_BYTES (16u * 1024u * 1024u)

static uint64_t test_bridge_clock(void *user)
{
    return *(const uint64_t *)user;
}

static BreakReplicationSessionBridgeConfig test_bridge_config(uint64_t *now)
{
    BreakReplicationSessionBridgeConfig config;
    memset(&config, 0, sizeof(config));
    config.reactor = NULL;
    config.max_connections = 2u;
    config.stream_capacity = 4u;
    config.max_pending_bytes_per_connection = 64u;
    config.max_total_pending_bytes = 128u;
    config.max_fragment_bytes = 32u;
    config.max_fragment_count = 8u;
    config.completion_capacity = 4u;
    config.max_completion_packet_bytes = 64u;
    config.max_completion_queue_bytes = 256u;
    config.expiry_enabled = false;
    config.expiry_interval = 5u;
    config.expiry_max_idle = 10u;
    config.clock = test_bridge_clock;
    config.clock_user = now;
    return config;
}

static bool test_push_fragment(BreakReplicationSessionBridge *bridge,
                               BreakConnectionKey connection,
                               const BreakReplicationFragment *fragment)
{
    uint8_t wire[256];
    size_t wire_size = 0u;
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
    return break_replication_session_handle_message(connection, &message, bridge);
}

static bool test_push_payload(BreakReplicationSessionBridge *bridge,
                              BreakConnectionKey connection, uint64_t delta_id,
                              uint64_t base_id, const void *payload, size_t payload_size)
{
    BreakReplicationFragment *fragments = NULL;
    size_t count = 0u;
    bool handled;
    if (break_replication_fragment_payload(delta_id, base_id, payload, payload_size,
                                           payload_size, &fragments, &count) !=
            BREAK_REPLICATION_FRAGMENT_OK ||
        count != 1u) {
        break_replication_fragments_free(fragments, count);
        return false;
    }
    handled = test_push_fragment(bridge, connection, &fragments[0]);
    break_replication_fragments_free(fragments, count);
    return handled;
}

static void test_check_invalid_config(const BreakReplicationSessionBridgeConfig *config)
{
    BreakReplicationSessionBridge *bridge =
        break_replication_session_bridge_create(config);
    if (bridge != NULL) break_replication_session_bridge_destroy(bridge);
    ASSERT_TRUE(bridge == NULL);
}

TEST(bridge_create_validates_ranges_products_and_null_calls)
{
    uint64_t now = 0u;
    BreakReplicationSessionBridgeConfig config = test_bridge_config(&now);
    BreakReplicationSessionBridgeConfig invalid;
    BreakReplicationSessionBridge *bridge;
    BreakReplicationSessionBridgeStats stats;
    BreakReplicationSessionCompletion completion;
    uint8_t data = 0x5au;
    BreakReplicationFragment fragment = {1u, 0u, 0u, 1u, 0u, &data, 1u};

    ASSERT_TRUE(break_replication_session_bridge_create(NULL) == NULL);
    invalid = config;
    invalid.clock = NULL;
    test_check_invalid_config(&invalid);
    invalid = config;
    invalid.max_connections = 0u;
    test_check_invalid_config(&invalid);
    invalid = config;
    invalid.stream_capacity = 0u;
    test_check_invalid_config(&invalid);
    invalid = config;
    invalid.stream_capacity = 65u;
    test_check_invalid_config(&invalid);
    invalid = config;
    invalid.max_pending_bytes_per_connection = 0u;
    test_check_invalid_config(&invalid);
    invalid = config;
    invalid.max_pending_bytes_per_connection = TEST_MAX_PENDING_BYTES + 1u;
    test_check_invalid_config(&invalid);
    invalid = config;
    invalid.max_total_pending_bytes = 127u;
    test_check_invalid_config(&invalid);
    invalid = config;
    invalid.max_fragment_bytes = 0u;
    test_check_invalid_config(&invalid);
    invalid = config;
    invalid.max_fragment_bytes = 65497u;
    test_check_invalid_config(&invalid);
    invalid = config;
    invalid.max_fragment_count = 0u;
    test_check_invalid_config(&invalid);
    invalid = config;
    invalid.max_fragment_count = 1048577u;
    test_check_invalid_config(&invalid);
    invalid = config;
    invalid.completion_capacity = 0u;
    test_check_invalid_config(&invalid);
    invalid = config;
    invalid.max_completion_packet_bytes = 0u;
    test_check_invalid_config(&invalid);
    invalid = config;
    invalid.max_completion_packet_bytes = TEST_MAX_PENDING_BYTES + 1u;
    test_check_invalid_config(&invalid);
    invalid = config;
    invalid.max_completion_queue_bytes = 63u;
    test_check_invalid_config(&invalid);
    invalid = config;
    invalid.max_connections = SIZE_MAX / TEST_MAX_PENDING_BYTES + 1u;
    invalid.max_pending_bytes_per_connection = TEST_MAX_PENDING_BYTES;
    invalid.max_total_pending_bytes = SIZE_MAX;
    test_check_invalid_config(&invalid);
    invalid = config;
    invalid.max_connections = SIZE_MAX;
    invalid.max_pending_bytes_per_connection = 1u;
    invalid.max_total_pending_bytes = SIZE_MAX;
    test_check_invalid_config(&invalid);
    invalid = config;
    invalid.completion_capacity = SIZE_MAX;
    invalid.max_completion_queue_bytes = SIZE_MAX;
    test_check_invalid_config(&invalid);

    config.max_connections = 1u;
    config.stream_capacity = 64u;
    config.max_pending_bytes_per_connection = TEST_MAX_PENDING_BYTES;
    config.max_total_pending_bytes = TEST_MAX_PENDING_BYTES;
    config.max_fragment_bytes = 65496u;
    config.max_fragment_count = 1048576u;
    config.completion_capacity = 1u;
    config.max_completion_packet_bytes = TEST_MAX_PENDING_BYTES;
    config.max_completion_queue_bytes = TEST_MAX_PENDING_BYTES;
    config.expiry_enabled = true;
    config.expiry_interval = 0u;
    config.expiry_max_idle = 0u;
    bridge = break_replication_session_bridge_create(&config);
    ASSERT_NOT_NULL(bridge);
    break_replication_session_bridge_stats(bridge, NULL);
    memset(&stats, 0xa5, sizeof(stats));
    break_replication_session_bridge_stats(NULL, &stats);
    ASSERT_EQ(stats.connections, 0u);
    ASSERT_EQ(stats.pending_bytes, 0u);
    ASSERT_EQ(stats.completion_count, 0u);
    ASSERT_EQ(stats.completion_bytes, 0u);
    ASSERT_EQ(stats.rejected_fragments, 0u);
    ASSERT_EQ(stats.duplicate_fragments, 0u);
    ASSERT_EQ(stats.completed_packets, 0u);
    ASSERT_EQ(stats.dropped_completions, 0u);
    ASSERT_EQ(stats.expired_streams, 0u);
    ASSERT_FALSE(break_replication_session_connection_open(NULL, 1u, 0u));
    ASSERT_FALSE(break_replication_session_connection_close(NULL, 1u));
    ASSERT_EQ(break_replication_session_bridge_tick(NULL, 0u), 0u);
    ASSERT_EQ(break_replication_session_poll_completed(NULL, &completion, 1u), 0u);
    ASSERT_EQ(break_replication_session_poll_completed(bridge, NULL, 1u), 0u);
    ASSERT_EQ(break_replication_session_poll_completed(bridge, &completion, 0u), 0u);
    ASSERT_EQ(break_replication_session_send_fragment(NULL, 1u, &fragment),
              BREAK_NET_SEND_CLOSED);
    break_replication_session_completion_release(NULL);
    break_replication_session_bridge_destroy(bridge);
    break_replication_session_bridge_destroy(NULL);
}

TEST(bridge_open_capacity_close_and_key_reuse_start_fresh)
{
    uint64_t now = 0u;
    BreakReplicationSessionBridgeConfig config = test_bridge_config(&now);
    BreakReplicationSessionBridge *bridge =
        break_replication_session_bridge_create(&config);
    BreakReplicationSessionCompletion completion;
    BreakReplicationSessionBridgeStats stats;

    ASSERT_NOT_NULL(bridge);
    ASSERT_FALSE(break_replication_session_connection_open(bridge, 0u, 10u));
    ASSERT_TRUE(break_replication_session_connection_open(bridge, 11u, 10u));
    ASSERT_FALSE(break_replication_session_connection_open(bridge, 11u, 10u));
    ASSERT_TRUE(break_replication_session_connection_open(bridge, 12u, 20u));
    ASSERT_FALSE(break_replication_session_connection_open(bridge, 13u, 30u));
    ASSERT_TRUE(test_push_payload(bridge, 11u, 9u, 10u, "old", 3u));
    ASSERT_EQ(break_replication_session_poll_completed(bridge, &completion, 1u), 1u);
    ASSERT_EQ(completion.delta_id, 9u);
    break_replication_session_completion_release(&completion);
    ASSERT_TRUE(break_replication_session_connection_close(bridge, 11u));
    ASSERT_FALSE(break_replication_session_connection_close(bridge, 11u));
    ASSERT_TRUE(break_replication_session_connection_open(bridge, 13u, 30u));
    ASSERT_TRUE(break_replication_session_connection_close(bridge, 13u));
    ASSERT_TRUE(break_replication_session_connection_open(bridge, 11u, 10u));
    ASSERT_TRUE(test_push_payload(bridge, 11u, 1u, 10u, "new", 3u));
    ASSERT_EQ(break_replication_session_poll_completed(bridge, &completion, 1u), 1u);
    ASSERT_EQ(completion.delta_id, 1u);
    ASSERT_EQ(completion.payload_size, 3u);
    ASSERT_TRUE(memcmp(completion.payload, "new", 3u) == 0);
    break_replication_session_completion_release(&completion);
    break_replication_session_bridge_stats(bridge, &stats);
    ASSERT_EQ(stats.connections, 2u);
    ASSERT_EQ(stats.pending_bytes, 0u);
    break_replication_session_bridge_destroy(bridge);
}

TEST(bridge_routes_connections_and_enforces_expected_base)
{
    uint64_t now = 0u;
    BreakReplicationSessionBridgeConfig config = test_bridge_config(&now);
    BreakReplicationSessionBridge *bridge =
        break_replication_session_bridge_create(&config);
    BreakReplicationSessionCompletion completions[2];
    BreakReplicationSessionBridgeStats stats;

    ASSERT_NOT_NULL(bridge);
    ASSERT_TRUE(break_replication_session_connection_open(bridge, 101u, 11u));
    ASSERT_TRUE(break_replication_session_connection_open(bridge, 202u, 22u));
    ASSERT_FALSE(test_push_payload(bridge, 202u, 7u, 11u, "wrong", 5u));
    ASSERT_TRUE(test_push_payload(bridge, 101u, 7u, 11u, "first", 5u));
    ASSERT_TRUE(test_push_payload(bridge, 202u, 7u, 22u, "second", 6u));
    ASSERT_EQ(break_replication_session_poll_completed(bridge, completions, 2u), 2u);
    ASSERT_EQ(completions[0].connection, 101u);
    ASSERT_EQ(completions[0].delta_id, 7u);
    ASSERT_TRUE(memcmp(completions[0].payload, "first", 5u) == 0);
    ASSERT_EQ(completions[1].connection, 202u);
    ASSERT_EQ(completions[1].delta_id, 7u);
    ASSERT_TRUE(memcmp(completions[1].payload, "second", 6u) == 0);
    break_replication_session_completion_release(&completions[0]);
    break_replication_session_completion_release(&completions[1]);
    break_replication_session_bridge_stats(bridge, &stats);
    ASSERT_EQ(stats.rejected_fragments, 1u);
    ASSERT_EQ(stats.completed_packets, 2u);
    ASSERT_EQ(stats.pending_bytes, 0u);
    break_replication_session_bridge_destroy(bridge);
}

static size_t test_apply_count;

TEST(bridge_interleaves_deltas_connections_duplicates_and_conflicts)
{
    static const char first[] = "abcdefghij";
    static const char second[] = "KLMNOPQR";
    static const char other[] = "123456";
    static const char conflicting[] = "Xbcdefghij";
    uint64_t now = 0u;
    BreakReplicationSessionBridgeConfig config = test_bridge_config(&now);
    BreakReplicationSessionBridge *bridge =
        break_replication_session_bridge_create(&config);
    BreakReplicationFragment *first_fragments = NULL;
    BreakReplicationFragment *second_fragments = NULL;
    BreakReplicationFragment *other_fragments = NULL;
    BreakReplicationFragment *conflicting_fragments = NULL;
    size_t first_count = 0u;
    size_t second_count = 0u;
    size_t other_count = 0u;
    size_t conflicting_count = 0u;
    BreakReplicationSessionCompletion completions[3];
    BreakReplicationSessionBridgeStats stats;
    size_t i;

    ASSERT_NOT_NULL(bridge);
    ASSERT_TRUE(break_replication_session_connection_open(bridge, 1u, 5u));
    ASSERT_TRUE(break_replication_session_connection_open(bridge, 2u, 6u));
    ASSERT_EQ(break_replication_fragment_payload(10u, 5u, first, 10u, 4u,
                                                  &first_fragments, &first_count),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(break_replication_fragment_payload(11u, 5u, second, 8u, 4u,
                                                  &second_fragments, &second_count),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(break_replication_fragment_payload(10u, 6u, other, 6u, 4u,
                                                  &other_fragments, &other_count),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(break_replication_fragment_payload(10u, 5u, conflicting, 10u, 4u,
                                                  &conflicting_fragments,
                                                  &conflicting_count),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(first_count, 3u);
    ASSERT_EQ(second_count, 2u);
    ASSERT_EQ(other_count, 2u);
    ASSERT_EQ(conflicting_count, 3u);

    ASSERT_TRUE(test_push_fragment(bridge, 1u, &first_fragments[0]));
    ASSERT_TRUE(test_push_fragment(bridge, 2u, &other_fragments[0]));
    ASSERT_TRUE(test_push_fragment(bridge, 1u, &second_fragments[0]));
    ASSERT_TRUE(test_push_fragment(bridge, 1u, &first_fragments[0]));
    ASSERT_FALSE(test_push_fragment(bridge, 1u, &conflicting_fragments[0]));
    ASSERT_TRUE(test_push_fragment(bridge, 1u, &second_fragments[1]));
    ASSERT_TRUE(test_push_fragment(bridge, 2u, &other_fragments[1]));
    ASSERT_TRUE(test_push_fragment(bridge, 1u, &first_fragments[2]));
    ASSERT_TRUE(test_push_fragment(bridge, 1u, &first_fragments[1]));
    ASSERT_EQ(test_apply_count, 0u);
    break_replication_session_bridge_stats(bridge, &stats);
    ASSERT_EQ(stats.rejected_fragments, 1u);
    ASSERT_EQ(stats.duplicate_fragments, 1u);
    ASSERT_EQ(stats.completed_packets, 3u);
    ASSERT_EQ(stats.pending_bytes, 0u);
    ASSERT_EQ(stats.completion_count, 3u);
    ASSERT_EQ(stats.completion_bytes, 24u);
    ASSERT_EQ(test_apply_count, 0u);

    ASSERT_EQ(break_replication_session_poll_completed(bridge, completions, 3u), 3u);
    ASSERT_EQ(completions[0].connection, 1u);
    ASSERT_EQ(completions[0].delta_id, 11u);
    ASSERT_EQ(completions[0].payload_size, 8u);
    ASSERT_TRUE(memcmp(completions[0].payload, second, 8u) == 0);
    ASSERT_EQ(completions[1].connection, 2u);
    ASSERT_EQ(completions[1].delta_id, 10u);
    ASSERT_EQ(completions[1].payload_size, 6u);
    ASSERT_TRUE(memcmp(completions[1].payload, other, 6u) == 0);
    ASSERT_EQ(completions[2].connection, 1u);
    ASSERT_EQ(completions[2].delta_id, 10u);
    ASSERT_EQ(completions[2].payload_size, 10u);
    ASSERT_TRUE(memcmp(completions[2].payload, first, 10u) == 0);
    for (i = 0u; i < 3u; ++i) {
        ++test_apply_count;
        break_replication_session_completion_release(&completions[i]);
    }
    ASSERT_EQ(test_apply_count, 3u);
    break_replication_fragments_free(first_fragments, first_count);
    break_replication_fragments_free(second_fragments, second_count);
    break_replication_fragments_free(other_fragments, other_count);
    break_replication_fragments_free(conflicting_fragments, conflicting_count);
    break_replication_session_bridge_destroy(bridge);
}

TEST(bridge_completion_fifo_partial_poll_and_release_transfer_ownership)
{
    uint64_t now = 0u;
    BreakReplicationSessionBridgeConfig config = test_bridge_config(&now);
    BreakReplicationSessionBridge *bridge =
        break_replication_session_bridge_create(&config);
    BreakReplicationSessionCompletion completions[2];
    BreakReplicationSessionCompletion last;
    BreakReplicationSessionBridgeStats stats;

    ASSERT_NOT_NULL(bridge);
    ASSERT_TRUE(break_replication_session_connection_open(bridge, 1u, 1u));
    ASSERT_TRUE(test_push_payload(bridge, 1u, 1u, 1u, "one", 3u));
    ASSERT_TRUE(test_push_payload(bridge, 1u, 2u, 1u, "two!", 4u));
    ASSERT_TRUE(test_push_payload(bridge, 1u, 3u, 1u, "three", 5u));
    ASSERT_EQ(break_replication_session_poll_completed(bridge, NULL, 3u), 0u);
    ASSERT_EQ(break_replication_session_poll_completed(bridge, completions, 0u), 0u);
    break_replication_session_bridge_stats(bridge, &stats);
    ASSERT_EQ(stats.completion_count, 3u);
    ASSERT_EQ(stats.completion_bytes, 12u);
    ASSERT_EQ(break_replication_session_poll_completed(bridge, completions, 2u), 2u);
    ASSERT_EQ(completions[0].delta_id, 1u);
    ASSERT_EQ(completions[1].delta_id, 2u);
    ASSERT_TRUE(memcmp(completions[0].payload, "one", 3u) == 0);
    ASSERT_TRUE(memcmp(completions[1].payload, "two!", 4u) == 0);
    break_replication_session_bridge_stats(bridge, &stats);
    ASSERT_EQ(stats.completion_count, 1u);
    ASSERT_EQ(stats.completion_bytes, 5u);
    break_replication_session_completion_release(&completions[0]);
    ASSERT_TRUE(completions[0].payload == NULL);
    ASSERT_EQ(completions[0].payload_size, 0u);
    ASSERT_EQ(completions[0].connection, 0u);
    ASSERT_EQ(completions[0].delta_id, 0u);
    break_replication_session_completion_release(&completions[0]);
    break_replication_session_completion_release(&completions[1]);
    ASSERT_EQ(break_replication_session_poll_completed(bridge, &last, 1u), 1u);
    ASSERT_EQ(last.delta_id, 3u);
    ASSERT_TRUE(memcmp(last.payload, "three", 5u) == 0);
    break_replication_session_completion_release(&last);
    break_replication_session_bridge_stats(bridge, &stats);
    ASSERT_EQ(stats.completion_count, 0u);
    ASSERT_EQ(stats.completion_bytes, 0u);
    ASSERT_EQ(break_replication_session_poll_completed(bridge, &last, 1u), 0u);
    break_replication_session_bridge_destroy(bridge);
}

TEST(bridge_completion_count_overflow_drops_without_overwriting)
{
    uint64_t now = 0u;
    BreakReplicationSessionBridgeConfig config = test_bridge_config(&now);
    BreakReplicationSessionBridge *bridge;
    BreakReplicationSessionCompletion completion;
    BreakReplicationSessionBridgeStats stats;
    config.completion_capacity = 1u;
    config.max_completion_packet_bytes = 8u;
    config.max_completion_queue_bytes = 16u;
    bridge = break_replication_session_bridge_create(&config);
    ASSERT_NOT_NULL(bridge);
    ASSERT_TRUE(break_replication_session_connection_open(bridge, 1u, 1u));
    ASSERT_TRUE(test_push_payload(bridge, 1u, 1u, 1u, "first", 5u));
    ASSERT_TRUE(test_push_payload(bridge, 1u, 2u, 1u, "sec", 3u));
    break_replication_session_bridge_stats(bridge, &stats);
    ASSERT_EQ(stats.completed_packets, 2u);
    ASSERT_EQ(stats.dropped_completions, 1u);
    ASSERT_EQ(stats.completion_count, 1u);
    ASSERT_EQ(stats.completion_bytes, 5u);
    ASSERT_EQ(break_replication_session_poll_completed(bridge, &completion, 1u), 1u);
    ASSERT_EQ(completion.delta_id, 1u);
    ASSERT_EQ(completion.payload_size, 5u);
    ASSERT_TRUE(memcmp(completion.payload, "first", 5u) == 0);
    break_replication_session_completion_release(&completion);
    break_replication_session_bridge_destroy(bridge);
}

TEST(bridge_completion_packet_and_queue_byte_limits)
{
    uint64_t now = 0u;
    BreakReplicationSessionBridgeConfig config = test_bridge_config(&now);
    BreakReplicationSessionBridge *bridge;
    BreakReplicationSessionCompletion completions[3];
    BreakReplicationSessionBridgeStats stats;
    size_t i;
    config.max_completion_packet_bytes = 4u;
    config.max_completion_queue_bytes = 8u;
    bridge = break_replication_session_bridge_create(&config);
    ASSERT_NOT_NULL(bridge);
    ASSERT_TRUE(break_replication_session_connection_open(bridge, 1u, 1u));
    ASSERT_TRUE(test_push_payload(bridge, 1u, 1u, 1u, "five5", 5u));
    ASSERT_TRUE(test_push_payload(bridge, 1u, 2u, 1u, "aa", 2u));
    ASSERT_TRUE(test_push_payload(bridge, 1u, 3u, 1u, "bbb", 3u));
    ASSERT_TRUE(test_push_payload(bridge, 1u, 4u, 1u, "cccc", 4u));
    ASSERT_TRUE(test_push_payload(bridge, 1u, 5u, 1u, "ddd", 3u));
    break_replication_session_bridge_stats(bridge, &stats);
    ASSERT_EQ(stats.completed_packets, 5u);
    ASSERT_EQ(stats.dropped_completions, 2u);
    ASSERT_EQ(stats.completion_count, 3u);
    ASSERT_EQ(stats.completion_bytes, 8u);
    ASSERT_EQ(break_replication_session_poll_completed(bridge, completions, 3u), 3u);
    ASSERT_EQ(completions[0].delta_id, 2u);
    ASSERT_EQ(completions[1].delta_id, 3u);
    ASSERT_EQ(completions[2].delta_id, 5u);
    for (i = 0u; i < 3u; ++i) break_replication_session_completion_release(&completions[i]);
    break_replication_session_bridge_stats(bridge, &stats);
    ASSERT_EQ(stats.completion_count, 0u);
    ASSERT_EQ(stats.completion_bytes, 0u);
    break_replication_session_bridge_destroy(bridge);
}

TEST(bridge_close_drops_only_that_connections_completions_and_pending)
{
    uint64_t now = 0u;
    BreakReplicationSessionBridgeConfig config = test_bridge_config(&now);
    BreakReplicationSessionBridge *bridge =
        break_replication_session_bridge_create(&config);
    BreakReplicationFragment *pending = NULL;
    size_t pending_count = 0u;
    BreakReplicationSessionCompletion completion;
    BreakReplicationSessionBridgeStats stats;

    ASSERT_NOT_NULL(bridge);
    ASSERT_TRUE(break_replication_session_connection_open(bridge, 1u, 1u));
    ASSERT_TRUE(break_replication_session_connection_open(bridge, 2u, 1u));
    ASSERT_EQ(break_replication_fragment_payload(50u, 1u, "abcdefgh", 8u, 4u,
                                                  &pending, &pending_count),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_TRUE(test_push_fragment(bridge, 1u, &pending[0]));
    ASSERT_TRUE(test_push_payload(bridge, 1u, 1u, 1u, "one", 3u));
    ASSERT_TRUE(test_push_payload(bridge, 2u, 2u, 1u, "two!", 4u));
    ASSERT_TRUE(test_push_payload(bridge, 1u, 3u, 1u, "three", 5u));
    break_replication_session_bridge_stats(bridge, &stats);
    ASSERT_EQ(stats.pending_bytes, 4u);
    ASSERT_EQ(stats.completion_count, 3u);
    ASSERT_EQ(stats.completion_bytes, 12u);
    ASSERT_TRUE(break_replication_session_connection_close(bridge, 1u));
    break_replication_session_bridge_stats(bridge, &stats);
    ASSERT_EQ(stats.connections, 1u);
    ASSERT_EQ(stats.pending_bytes, 0u);
    ASSERT_EQ(stats.completion_count, 1u);
    ASSERT_EQ(stats.completion_bytes, 4u);
    ASSERT_EQ(stats.dropped_completions, 2u);
    ASSERT_EQ(break_replication_session_poll_completed(bridge, &completion, 1u), 1u);
    ASSERT_EQ(completion.connection, 2u);
    ASSERT_EQ(completion.delta_id, 2u);
    ASSERT_TRUE(memcmp(completion.payload, "two!", 4u) == 0);
    break_replication_session_completion_release(&completion);
    break_replication_fragments_free(pending, pending_count);
    break_replication_session_bridge_destroy(bridge);
}

TEST(bridge_static_pending_budget_is_per_connection_and_duplicate_safe)
{
    uint64_t now = 0u;
    BreakReplicationSessionBridgeConfig config = test_bridge_config(&now);
    BreakReplicationSessionBridge *bridge;
    BreakReplicationFragment *first = NULL;
    BreakReplicationFragment *second = NULL;
    size_t first_count = 0u;
    size_t second_count = 0u;
    BreakReplicationSessionBridgeStats stats;
    config.stream_capacity = 2u;
    config.max_pending_bytes_per_connection = 4u;
    config.max_total_pending_bytes = 8u;
    bridge = break_replication_session_bridge_create(&config);
    ASSERT_NOT_NULL(bridge);
    ASSERT_TRUE(break_replication_session_connection_open(bridge, 1u, 3u));
    ASSERT_TRUE(break_replication_session_connection_open(bridge, 2u, 3u));
    ASSERT_EQ(break_replication_fragment_payload(1u, 3u, "abcdefgh", 8u, 4u,
                                                  &first, &first_count),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(break_replication_fragment_payload(2u, 3u, "ijklmnop", 8u, 4u,
                                                  &second, &second_count),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_TRUE(test_push_fragment(bridge, 1u, &first[0]));
    ASSERT_TRUE(test_push_fragment(bridge, 2u, &second[0]));
    break_replication_session_bridge_stats(bridge, &stats);
    ASSERT_EQ(stats.pending_bytes, 8u);
    ASSERT_TRUE(test_push_fragment(bridge, 1u, &first[0]));
    break_replication_session_bridge_stats(bridge, &stats);
    ASSERT_EQ(stats.pending_bytes, 8u);
    ASSERT_EQ(stats.duplicate_fragments, 1u);
    ASSERT_FALSE(test_push_fragment(bridge, 1u, &second[0]));
    break_replication_session_bridge_stats(bridge, &stats);
    ASSERT_EQ(stats.pending_bytes, 8u);
    ASSERT_TRUE(break_replication_session_connection_close(bridge, 1u));
    break_replication_session_bridge_stats(bridge, &stats);
    ASSERT_EQ(stats.pending_bytes, 4u);
    ASSERT_TRUE(break_replication_session_connection_close(bridge, 2u));
    break_replication_session_bridge_stats(bridge, &stats);
    ASSERT_EQ(stats.pending_bytes, 0u);
    break_replication_fragments_free(first, first_count);
    break_replication_fragments_free(second, second_count);
    break_replication_session_bridge_destroy(bridge);
}

TEST(bridge_handler_rejects_wrong_envelope_malformed_wire_and_bad_fragments)
{
    uint64_t now = 0u;
    BreakReplicationSessionBridgeConfig config = test_bridge_config(&now);
    BreakReplicationSessionBridge *bridge =
        break_replication_session_bridge_create(&config);
    BreakReplicationFragment *fragments = NULL;
    size_t count = 0u;
    uint8_t wire[64];
    size_t wire_size = 0u;
    BreakNetOwnedMessage message;
    BreakReplicationSessionBridgeStats stats;

    ASSERT_NOT_NULL(bridge);
    ASSERT_TRUE(break_replication_session_connection_open(bridge, 1u, 2u));
    ASSERT_EQ(break_replication_fragment_payload(1u, 2u, "data", 4u, 4u,
                                                  &fragments, &count),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(break_replication_wire_encode(&fragments[0], wire, sizeof(wire),
                                             &wire_size),
              BREAK_REPLICATION_FRAGMENT_OK);
    memset(&message, 0, sizeof(message));
    message.message_id = BREAK_NET_MESSAGE_ID_PING;
    message.protocol_version = 1u;
    message.data = wire;
    message.size = wire_size;
    ASSERT_FALSE(break_replication_session_handle_message(1u, &message, bridge));
    message.message_id = BREAK_NET_MESSAGE_ID_REPLICATION_FRAGMENT;
    message.protocol_version = 2u;
    ASSERT_FALSE(break_replication_session_handle_message(1u, &message, bridge));
    message.protocol_version = 1u;
    message.size = 3u;
    ASSERT_FALSE(break_replication_session_handle_message(1u, &message, bridge));
    message.size = wire_size;
    ASSERT_FALSE(break_replication_session_handle_message(99u, &message, bridge));
    ASSERT_FALSE(break_replication_session_handle_message(1u, NULL, bridge));
    fragments[0].base_id = 3u;
    ASSERT_FALSE(test_push_fragment(bridge, 1u, &fragments[0]));
    fragments[0].base_id = 2u;
    fragments[0].checksum ^= 1u;
    ASSERT_FALSE(test_push_fragment(bridge, 1u, &fragments[0]));
    ASSERT_FALSE(break_replication_session_handle_message(1u, &message, NULL));
    break_replication_session_bridge_stats(bridge, &stats);
    ASSERT_EQ(stats.rejected_fragments, 7u);
    ASSERT_EQ(stats.completed_packets, 0u);
    ASSERT_EQ(stats.completion_count, 0u);
    break_replication_fragments_free(fragments, count);
    break_replication_session_bridge_destroy(bridge);
}

TEST(bridge_handler_enforces_configured_fragment_size_and_count)
{
    static const uint8_t data[33] = {0};
    uint64_t now = 0u;
    BreakReplicationSessionBridgeConfig config = test_bridge_config(&now);
    BreakReplicationSessionBridge *bridge =
        break_replication_session_bridge_create(&config);
    BreakReplicationFragment *fragments = NULL;
    BreakReplicationFragment fragment;
    size_t fragment_count = 0u;
    BreakReplicationSessionBridgeStats stats;

    ASSERT_EQ(break_replication_fragment_payload(1u, 4u, data, 32u, 32u,
                                                 &fragments, &fragment_count),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(fragment_count, 1u);
    fragment = fragments[0];
    ASSERT_NOT_NULL(bridge);
    ASSERT_TRUE(break_replication_session_connection_open(bridge, 1u, 4u));
    fragment.size = 33u;
    ASSERT_FALSE(test_push_fragment(bridge, 1u, &fragment));
    fragment.size = 32u;
    fragment.fragment_count = 9u;
    ASSERT_FALSE(test_push_fragment(bridge, 1u, &fragment));
    break_replication_session_bridge_stats(bridge, &stats);
    ASSERT_EQ(stats.rejected_fragments, 2u);
    ASSERT_EQ(stats.pending_bytes, 0u);
    fragment.fragment_count = 8u;
    ASSERT_TRUE(test_push_fragment(bridge, 1u, &fragment));
    break_replication_session_bridge_stats(bridge, &stats);
    ASSERT_EQ(stats.rejected_fragments, 2u);
    ASSERT_EQ(stats.pending_bytes, 32u);
    break_replication_session_bridge_destroy(bridge);
    break_replication_fragments_free(fragments, fragment_count);
}

typedef struct TestReactorFixture {
    BreakNetReactor *reactor;
    SnowAcceptor *acceptor;
} TestReactorFixture;

static bool test_reactor_start(TestReactorFixture *fixture)
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
    if (fixture->reactor == NULL ||
        !break_net_reactor_set_acceptor(fixture->reactor, fixture->acceptor) ||
        !break_net_reactor_start(fixture->reactor)) {
        break_net_reactor_destroy(fixture->reactor);
        SnowAcceptorDestroy(fixture->acceptor);
        memset(fixture, 0, sizeof(*fixture));
        return false;
    }
    return true;
}

static void test_reactor_destroy(TestReactorFixture *fixture)
{
    if (fixture->reactor != NULL) {
        (void)break_net_reactor_stop(fixture->reactor, 1000u);
        break_net_reactor_destroy(fixture->reactor);
    }
    if (fixture->acceptor != NULL) SnowAcceptorDestroy(fixture->acceptor);
    memset(fixture, 0, sizeof(*fixture));
}

static BreakReplicationFragment test_outbound_fragment(void)
{
    static const uint8_t data[] = {0xaau, 0xbbu, 0xccu, 0xddu};
    BreakReplicationFragment fragment = {
        1u, 2u, 0u, 1u, 0x11223344u, data, sizeof(data)
    };
    return fragment;
}

TEST(bridge_send_validates_and_encodes_through_real_reactor)
{
    static const uint8_t expected[] = {
        0x42u, 0x52u, 0x46u, 0x47u, 0x01u, 0x00u, 0x28u, 0x00u,
        0x01u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x02u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x01u, 0x00u, 0x00u, 0x00u,
        0x44u, 0x33u, 0x22u, 0x11u, 0x04u, 0x00u, 0x00u, 0x00u,
        0xaau, 0xbbu, 0xccu, 0xddu
    };
    uint64_t now = 0u;
    BreakReplicationSessionBridgeConfig config = test_bridge_config(&now);
    BreakReplicationSessionBridge *bridge;
    BreakReplicationFragment fragment = test_outbound_fragment();
    TestReactorFixture fixture;
    BreakNetOwnedMessage outbound;
    uint64_t outbound_connection = 0u;

    config.max_fragment_bytes = 4u;
    config.max_fragment_count = 4u;
    bridge = break_replication_session_bridge_create(&config);
    ASSERT_NOT_NULL(bridge);
    ASSERT_TRUE(break_replication_session_connection_open(bridge, 1u, 2u));
    ASSERT_EQ(break_replication_session_send_fragment(bridge, 99u, &fragment),
              BREAK_NET_SEND_CLOSED);
    ASSERT_EQ(break_replication_session_send_fragment(bridge, 1u, NULL),
              BREAK_NET_SEND_INVALID);
    fragment.base_id = 3u;
    ASSERT_EQ(break_replication_session_send_fragment(bridge, 1u, &fragment),
              BREAK_NET_SEND_INVALID);
    fragment = test_outbound_fragment();
    fragment.size = 5u;
    ASSERT_EQ(break_replication_session_send_fragment(bridge, 1u, &fragment),
              BREAK_NET_SEND_INVALID);
    fragment = test_outbound_fragment();
    fragment.fragment_count = 5u;
    ASSERT_EQ(break_replication_session_send_fragment(bridge, 1u, &fragment),
              BREAK_NET_SEND_INVALID);
    fragment = test_outbound_fragment();
    fragment.delta_id = 0u;
    ASSERT_EQ(break_replication_session_send_fragment(bridge, 1u, &fragment),
              BREAK_NET_SEND_INVALID);
    fragment = test_outbound_fragment();
    fragment.data = NULL;
    ASSERT_EQ(break_replication_session_send_fragment(bridge, 1u, &fragment),
              BREAK_NET_SEND_INVALID);
    fragment = test_outbound_fragment();
    fragment.size = 0u;
    ASSERT_EQ(break_replication_session_send_fragment(bridge, 1u, &fragment),
              BREAK_NET_SEND_INVALID);
    fragment = test_outbound_fragment();
    fragment.fragment_index = 1u;
    ASSERT_EQ(break_replication_session_send_fragment(bridge, 1u, &fragment),
              BREAK_NET_SEND_INVALID);
    fragment = test_outbound_fragment();
    ASSERT_EQ(break_replication_session_send_fragment(bridge, 1u, &fragment),
              BREAK_NET_SEND_INVALID);
    break_replication_session_bridge_destroy(bridge);

    ASSERT_TRUE(test_reactor_start(&fixture));
    config.reactor = fixture.reactor;
    bridge = break_replication_session_bridge_create(&config);
    ASSERT_NOT_NULL(bridge);
    ASSERT_TRUE(break_replication_session_connection_open(bridge, 0x123u, 2u));
    ASSERT_EQ(break_replication_session_send_fragment(bridge, 0x123u, &fragment),
              BREAK_NET_SEND_OK);
    ASSERT_EQ(break_net_reactor_poll_outbound_for_test(
                  fixture.reactor, &outbound_connection, &outbound),
              BREAK_NET_EVENT_OK);
    ASSERT_EQ(outbound_connection, 0x123u);
    ASSERT_EQ(outbound.message_id, BREAK_NET_MESSAGE_ID_REPLICATION_FRAGMENT);
    ASSERT_EQ(outbound.protocol_version, BREAK_REPLICATION_WIRE_VERSION);
    ASSERT_EQ(outbound.size, sizeof(expected));
    ASSERT_TRUE(memcmp(outbound.data, expected, sizeof(expected)) == 0);
    break_net_message_release(&outbound);
    break_replication_session_bridge_destroy(bridge);
    test_reactor_destroy(&fixture);
}

TEST(bridge_send_propagates_reactor_closed_overload_and_caller_retry)
{
    uint64_t now = 0u;
    BreakReplicationSessionBridgeConfig config = test_bridge_config(&now);
    BreakNetReactorConfig reactor_config = {BREAK_NET_DRIVE_STEP, 0, 4u, 0, 0u, 0u};
    BreakNetReactor *closed_reactor = break_net_reactor_create(&reactor_config);
    BreakReplicationSessionBridge *bridge;
    BreakReplicationFragment fragment = test_outbound_fragment();
    TestReactorFixture fixture;
    BreakNetOwnedMessage outbound;
    uint64_t outbound_connection = 0u;
    size_t i;

    ASSERT_NOT_NULL(closed_reactor);
    config.reactor = closed_reactor;
    config.max_fragment_bytes = 4u;
    config.max_fragment_count = 4u;
    bridge = break_replication_session_bridge_create(&config);
    ASSERT_NOT_NULL(bridge);
    ASSERT_TRUE(break_replication_session_connection_open(bridge, 1u, 2u));
    ASSERT_EQ(break_replication_session_send_fragment(bridge, 1u, &fragment),
              BREAK_NET_SEND_CLOSED);
    break_replication_session_bridge_destroy(bridge);
    break_net_reactor_destroy(closed_reactor);

    ASSERT_TRUE(test_reactor_start(&fixture));
    config.reactor = fixture.reactor;
    bridge = break_replication_session_bridge_create(&config);
    ASSERT_NOT_NULL(bridge);
    ASSERT_TRUE(break_replication_session_connection_open(bridge, 1u, 2u));
    for (i = 0u; i < BREAK_NET_OUTBOUND_QUEUE_CAPACITY; ++i) {
        ASSERT_EQ(break_net_reactor_send(fixture.reactor, 1u,
                                         BREAK_NET_MESSAGE_ID_PING, 1u, "x", 1u),
                  BREAK_NET_SEND_OK);
    }
    ASSERT_EQ(break_replication_session_send_fragment(bridge, 1u, &fragment),
              BREAK_NET_SEND_OVERLOAD);
    ASSERT_EQ(break_net_reactor_poll_outbound_for_test(
                  fixture.reactor, &outbound_connection, &outbound),
              BREAK_NET_EVENT_OK);
    break_net_message_release(&outbound);
    ASSERT_EQ(break_replication_session_send_fragment(bridge, 1u, &fragment),
              BREAK_NET_SEND_OK);
    ASSERT_EQ(break_net_reactor_outbound_count(fixture.reactor),
              BREAK_NET_OUTBOUND_QUEUE_CAPACITY);
    break_replication_session_bridge_destroy(bridge);
    test_reactor_destroy(&fixture);
}

TEST(bridge_tick_expires_every_connection_without_traffic_and_honors_disable)
{
    uint64_t now = 100u;
    BreakReplicationSessionBridgeConfig config = test_bridge_config(&now);
    BreakReplicationSessionBridge *bridge;
    BreakReplicationFragment *first = NULL;
    BreakReplicationFragment *second = NULL;
    size_t first_count = 0u;
    size_t second_count = 0u;
    BreakReplicationSessionBridgeStats stats;
    config.expiry_enabled = true;
    config.expiry_interval = 5u;
    config.expiry_max_idle = 10u;
    bridge = break_replication_session_bridge_create(&config);
    ASSERT_NOT_NULL(bridge);
    ASSERT_TRUE(break_replication_session_connection_open(bridge, 1u, 7u));
    ASSERT_TRUE(break_replication_session_connection_open(bridge, 2u, 7u));
    ASSERT_EQ(break_replication_fragment_payload(1u, 7u, "abcdefgh", 8u, 4u,
                                                  &first, &first_count),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(break_replication_fragment_payload(2u, 7u, "ijklmnop", 8u, 4u,
                                                  &second, &second_count),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_TRUE(test_push_fragment(bridge, 1u, &first[0]));
    ASSERT_TRUE(test_push_fragment(bridge, 2u, &second[0]));
    ASSERT_EQ(break_replication_session_bridge_tick(bridge, 100u), 0u);
    ASSERT_EQ(break_replication_session_bridge_tick(bridge, 104u), 0u);
    ASSERT_EQ(break_replication_session_bridge_tick(bridge, 105u), 0u);
    ASSERT_EQ(break_replication_session_bridge_tick(bridge, 99u), 0u);
    ASSERT_EQ(break_replication_session_bridge_tick(bridge, 110u), 2u);
    break_replication_session_bridge_stats(bridge, &stats);
    ASSERT_EQ(stats.expired_streams, 2u);
    ASSERT_EQ(stats.pending_bytes, 0u);
    break_replication_session_bridge_destroy(bridge);
    break_replication_fragments_free(first, first_count);
    break_replication_fragments_free(second, second_count);

    config.expiry_enabled = false;
    bridge = break_replication_session_bridge_create(&config);
    ASSERT_NOT_NULL(bridge);
    ASSERT_TRUE(break_replication_session_connection_open(bridge, 1u, 7u));
    ASSERT_EQ(break_replication_fragment_payload(1u, 7u, "abcdefgh", 8u, 4u,
                                                  &first, &first_count),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_TRUE(test_push_fragment(bridge, 1u, &first[0]));
    ASSERT_EQ(break_replication_session_bridge_tick(bridge, 1000u), 0u);
    break_replication_session_bridge_stats(bridge, &stats);
    ASSERT_EQ(stats.expired_streams, 0u);
    ASSERT_EQ(stats.pending_bytes, 4u);
    break_replication_session_bridge_destroy(bridge);
    break_replication_fragments_free(first, first_count);
}

TEST(bridge_non_auth_handler_failure_keeps_session_authenticated)
{
    uint64_t now = 0u;
    BreakReplicationSessionBridgeConfig config = test_bridge_config(&now);
    BreakReplicationSessionBridge *bridge =
        break_replication_session_bridge_create(&config);
    BreakSessionConfig session_config = {0};
    BreakSessionManager *manager = break_session_manager_create(&session_config);
    BreakReplicationFragment *fragments = NULL;
    size_t count = 0u;
    uint8_t wire[64];
    size_t wire_size = 0u;
    BreakNetEvent event;
    BreakSessionApplyStats stats;

    ASSERT_NOT_NULL(bridge);
    ASSERT_NOT_NULL(manager);
    ASSERT_TRUE(break_replication_session_connection_open(bridge, 1u, 2u));
    ASSERT_TRUE(break_session_manager_bind(manager, 1u));
    ASSERT_TRUE(break_session_manager_begin_auth(manager, 1u));
    ASSERT_TRUE(break_session_manager_auth_succeeded(manager, 1u));
    ASSERT_TRUE(break_session_manager_set_message_handler(
        manager, BREAK_NET_MESSAGE_ID_REPLICATION_FRAGMENT,
        break_replication_session_handle_message, bridge));
    ASSERT_EQ(break_replication_fragment_payload(1u, 2u, "data", 4u, 4u,
                                                  &fragments, &count),
              BREAK_REPLICATION_FRAGMENT_OK);
    fragments[0].checksum ^= 1u;
    ASSERT_EQ(break_replication_wire_encode(&fragments[0], wire, sizeof(wire),
                                             &wire_size),
              BREAK_REPLICATION_FRAGMENT_OK);
    memset(&event, 0, sizeof(event));
    event.type = BREAK_NET_EVENT_MESSAGE_RECEIVED;
    event.connection_key = 1u;
    event.message.message_id = BREAK_NET_MESSAGE_ID_REPLICATION_FRAGMENT;
    event.message.protocol_version = 1u;
    event.message.sequence = 1u;
    event.message.data = wire;
    event.message.size = wire_size;
    ASSERT_FALSE(break_session_manager_apply_adapter_event(manager, &event));
    ASSERT_EQ(break_session_manager_last_result(manager),
              BREAK_SESSION_APPLY_HANDLER_FAILED);
    ASSERT_EQ(break_session_manager_state(manager, 1u), BREAK_SESSION_AUTHENTICATED);
    break_session_manager_apply_stats(manager, &stats);
    ASSERT_EQ(stats.handler_failed, 1u);
    break_replication_fragments_free(fragments, count);
    break_session_manager_destroy(manager);
    break_replication_session_bridge_destroy(bridge);
}

TEST_MAIN_BEGIN()
    RUN_TEST(bridge_create_validates_ranges_products_and_null_calls);
    RUN_TEST(bridge_open_capacity_close_and_key_reuse_start_fresh);
    RUN_TEST(bridge_routes_connections_and_enforces_expected_base);
    RUN_TEST(bridge_interleaves_deltas_connections_duplicates_and_conflicts);
    RUN_TEST(bridge_completion_fifo_partial_poll_and_release_transfer_ownership);
    RUN_TEST(bridge_completion_count_overflow_drops_without_overwriting);
    RUN_TEST(bridge_completion_packet_and_queue_byte_limits);
    RUN_TEST(bridge_close_drops_only_that_connections_completions_and_pending);
    RUN_TEST(bridge_static_pending_budget_is_per_connection_and_duplicate_safe);
    RUN_TEST(bridge_handler_rejects_wrong_envelope_malformed_wire_and_bad_fragments);
    RUN_TEST(bridge_handler_enforces_configured_fragment_size_and_count);
    RUN_TEST(bridge_send_validates_and_encodes_through_real_reactor);
    RUN_TEST(bridge_send_propagates_reactor_closed_overload_and_caller_retry);
    RUN_TEST(bridge_tick_expires_every_connection_without_traffic_and_honors_disable);
    RUN_TEST(bridge_non_auth_handler_failure_keeps_session_authenticated);
TEST_MAIN_END()
