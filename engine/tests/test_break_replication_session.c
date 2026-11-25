#include "test_framework.h"

#include <network/break_net_adapter.h>
#include <network/break_net_envelope.h>
#include <network/break_replication_session.h>
#include <network/break_replication_wire.h>
#include <network/break_session.h>
#include <snow/acceptor.h>
#include <snow/endpoint.h>

#include <arpa/inet.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

extern int usleep(unsigned int);

#define TEST_MAX_PENDING_BYTES (16u * 1024u * 1024u)

size_t break_test_replication_consumer_count = 0u;

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
    config.max_metadata_bytes_per_connection = 4096u;
    config.max_total_metadata_bytes = 8192u;
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
    invalid.max_metadata_bytes_per_connection = 0u;
    test_check_invalid_config(&invalid);
    invalid = config;
    invalid.max_metadata_bytes_per_connection = TEST_MAX_PENDING_BYTES + 1u;
    test_check_invalid_config(&invalid);
    invalid = config;
    invalid.max_total_metadata_bytes = 8191u;
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
    break_replication_session_bridge_stats(bridge, &stats);
    ASSERT_EQ(stats.rejected_fragments, 1u);
    ASSERT_EQ(stats.duplicate_fragments, 1u);
    ASSERT_EQ(stats.completed_packets, 3u);
    ASSERT_EQ(stats.pending_bytes, 0u);
    ASSERT_EQ(stats.completion_count, 3u);
    ASSERT_EQ(stats.completion_bytes, 24u);

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
    for (i = 0u; i < 3u; ++i)
        break_replication_session_completion_release(&completions[i]);
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

TEST(bridge_inbound_fragment_expiration_is_counted_without_owner_tick)
{
    static const char payload[] = "0123456789abcdef";
    uint64_t now = 0u;
    BreakReplicationSessionBridgeConfig config = test_bridge_config(&now);
    BreakReplicationSessionBridge *bridge;
    BreakReplicationFragment *fragments = NULL;
    size_t fragment_count = 0u;
    BreakReplicationSessionBridgeStats stats;

    config.expiry_enabled = true;
    bridge = break_replication_session_bridge_create(&config);
    ASSERT_NOT_NULL(bridge);
    ASSERT_TRUE(break_replication_session_connection_open(bridge, 1u, 7u));
    ASSERT_EQ(break_replication_fragment_payload(10u, 7u, payload, sizeof(payload) - 1u,
                                                 8u, &fragments, &fragment_count),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(fragment_count, 2u);
    ASSERT_TRUE(test_push_fragment(bridge, 1u, &fragments[0]));
    break_replication_session_bridge_stats(bridge, &stats);
    ASSERT_EQ(stats.pending_bytes, 8u);
    ASSERT_EQ(stats.expired_streams, 0u);
    now = config.expiry_interval + config.expiry_max_idle + 1u;
    ASSERT_TRUE(test_push_payload(bridge, 1u, 20u, 7u, "later", 5u));
    break_replication_session_bridge_stats(bridge, &stats);
    ASSERT_EQ(stats.expired_streams, 1u);
    break_replication_session_bridge_destroy(bridge);
    break_replication_fragments_free(fragments, fragment_count);
}

TEST(bridge_wrapped_fifo_close_compaction_preserves_survivor_order)
{
    uint64_t now = 0u;
    BreakReplicationSessionBridgeConfig config = test_bridge_config(&now);
    BreakReplicationSessionBridge *bridge =
        break_replication_session_bridge_create(&config);
    BreakReplicationSessionCompletion completions[4];
    BreakReplicationSessionBridgeStats stats;
    size_t i;

    ASSERT_NOT_NULL(bridge);
    ASSERT_TRUE(break_replication_session_connection_open(bridge, 1u, 7u));
    ASSERT_TRUE(break_replication_session_connection_open(bridge, 2u, 7u));
    ASSERT_TRUE(test_push_payload(bridge, 1u, 11u, 7u, "a1", 2u));
    ASSERT_TRUE(test_push_payload(bridge, 2u, 21u, 7u, "b1", 2u));
    ASSERT_TRUE(test_push_payload(bridge, 1u, 12u, 7u, "a2", 2u));
    ASSERT_TRUE(test_push_payload(bridge, 2u, 22u, 7u, "b2", 2u));
    ASSERT_EQ(break_replication_session_poll_completed(bridge, completions, 2u), 2u);
    break_replication_session_completion_release(&completions[0]);
    break_replication_session_completion_release(&completions[1]);
    ASSERT_TRUE(test_push_payload(bridge, 1u, 13u, 7u, "a3", 2u));
    ASSERT_TRUE(test_push_payload(bridge, 2u, 23u, 7u, "b3", 2u));
    break_replication_session_bridge_stats(bridge, &stats);
    ASSERT_EQ(stats.completion_count, 4u);
    ASSERT_EQ(stats.completion_bytes, 8u);
    ASSERT_TRUE(break_replication_session_connection_close(bridge, 2u));
    break_replication_session_bridge_stats(bridge, &stats);
    ASSERT_EQ(stats.completion_count, 2u);
    ASSERT_EQ(stats.completion_bytes, 4u);
    ASSERT_EQ(stats.dropped_completions, 2u);
    ASSERT_TRUE(test_push_payload(bridge, 1u, 14u, 7u, "a4", 2u));
    ASSERT_EQ(break_replication_session_poll_completed(bridge, completions, 4u), 3u);
    for (i = 0u; i < 3u; ++i) {
        char expected[3] = {'a', (char)('2' + i), '\0'};
        ASSERT_EQ(completions[i].connection, 1u);
        ASSERT_EQ(completions[i].delta_id, 12u + i);
        ASSERT_EQ(completions[i].payload_size, 2u);
        ASSERT_TRUE(memcmp(completions[i].payload, expected, 2u) == 0);
        break_replication_session_completion_release(&completions[i]);
    }
    break_replication_session_bridge_stats(bridge, &stats);
    ASSERT_EQ(stats.completion_count, 0u);
    ASSERT_EQ(stats.completion_bytes, 0u);
    break_replication_session_bridge_destroy(bridge);
}

typedef struct TestReactorFixture {
    BreakNetReactor *reactor;
    SnowAcceptor *acceptor;
} TestReactorFixture;

static bool test_reactor_start(TestReactorFixture *fixture)
{
    BreakNetReactorConfig config = {BREAK_NET_DRIVE_STEP, 0, 4u, 1000, 1000u, 1u, false};
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

typedef struct TestSessionSocketFixture {
    TestReactorFixture transport;
    BreakSessionManager *manager;
    BreakReplicationSessionBridge *bridge;
    BreakConnectionKey connection;
    size_t auth_calls;
    uint32_t sequence;
    uint64_t now;
    int client_fd;
} TestSessionSocketFixture;

static bool test_session_socket_auth_handler(BreakConnectionKey connection,
                                             const BreakNetOwnedMessage *message,
                                             void *user_data)
{
    TestSessionSocketFixture *fixture = (TestSessionSocketFixture *)user_data;
    if (message == NULL || message->message_id != BREAK_NET_MESSAGE_ID_AUTH) return false;
    fixture->connection = connection;
    fixture->auth_calls++;
    return true;
}

static bool test_session_socket_write_all(int fd, const void *data, size_t size)
{
    const uint8_t *bytes = (const uint8_t *)data;
    size_t offset = 0u;
    while (offset < size) {
        ssize_t written = write(fd, bytes + offset, size - offset);
        if (written <= 0) return false;
        offset += (size_t)written;
    }
    return true;
}

static void test_session_socket_store_u16(uint8_t *out, uint16_t value)
{
    out[0] = (uint8_t)value;
    out[1] = (uint8_t)(value >> 8u);
}

static void test_session_socket_store_u32(uint8_t *out, uint32_t value)
{
    out[0] = (uint8_t)value;
    out[1] = (uint8_t)(value >> 8u);
    out[2] = (uint8_t)(value >> 16u);
    out[3] = (uint8_t)(value >> 24u);
}

static bool test_session_socket_write_frame(TestSessionSocketFixture *fixture,
                                            uint16_t message_id, uint32_t sequence,
                                            const void *payload, size_t payload_size)
{
    uint8_t wire[BREAK_NET_ENVELOPE_HEADER_SIZE + 128u];
    if (payload_size > 128u || (payload_size != 0u && payload == NULL)) return false;
    test_session_socket_store_u32(wire, BREAK_NET_ENVELOPE_MAGIC);
    test_session_socket_store_u16(wire + 4u, BREAK_NET_PROTOCOL_VERSION);
    test_session_socket_store_u16(wire + 6u, message_id);
    test_session_socket_store_u16(wire + 8u, 0u);
    test_session_socket_store_u32(wire + 10u, sequence);
    test_session_socket_store_u32(wire + 14u, (uint32_t)payload_size);
    if (payload_size != 0u) memcpy(wire + BREAK_NET_ENVELOPE_HEADER_SIZE, payload, payload_size);
    return test_session_socket_write_all(fixture->client_fd, wire,
                                         BREAK_NET_ENVELOPE_HEADER_SIZE + payload_size);
}

static bool test_session_socket_write_brfg(TestSessionSocketFixture *fixture,
                                           const uint8_t *wire, size_t wire_size)
{
    fixture->sequence++;
    return test_session_socket_write_frame(
        fixture, BREAK_NET_MESSAGE_ID_REPLICATION_FRAGMENT, fixture->sequence,
        wire, wire_size);
}

static bool test_session_socket_write_fragment(TestSessionSocketFixture *fixture,
                                               const BreakReplicationFragment *fragment)
{
    uint8_t wire[128];
    size_t wire_size = 0u;
    if (break_replication_wire_encode(fragment, wire, sizeof(wire), &wire_size) !=
        BREAK_REPLICATION_FRAGMENT_OK) {
        return false;
    }
    return test_session_socket_write_brfg(fixture, wire, wire_size);
}

static bool test_session_socket_pump(TestSessionSocketFixture *fixture)
{
    bool stepped = break_net_reactor_step(fixture->transport.reactor, 1);
    (void)break_session_manager_poll_adapter(fixture->manager, 64u);
    return stepped;
}

static void test_session_socket_destroy(TestSessionSocketFixture *fixture)
{
    size_t i;
    if (fixture->client_fd >= 0) {
        close(fixture->client_fd);
        fixture->client_fd = -1;
    }
    if (fixture->manager != NULL && fixture->transport.reactor != NULL &&
        fixture->connection != 0u) {
        for (i = 0u; i < 5000u &&
             break_session_manager_state(fixture->manager, fixture->connection) !=
                 BREAK_SESSION_CLOSED; ++i) {
            if (!test_session_socket_pump(fixture)) break;
            usleep(1000u);
        }
        (void)break_session_manager_poll(fixture->manager, 64u);
    }
    if (fixture->bridge != NULL && fixture->connection != 0u) {
        (void)break_replication_session_connection_close(fixture->bridge,
                                                         fixture->connection);
    }
    break_replication_session_bridge_destroy(fixture->bridge);
    break_session_manager_destroy(fixture->manager);
    test_reactor_destroy(&fixture->transport);
    memset(fixture, 0, sizeof(*fixture));
    fixture->client_fd = -1;
}

static bool test_session_socket_start(TestSessionSocketFixture *fixture)
{
    BreakSessionConfig session_config = {0};
    BreakReplicationSessionBridgeConfig bridge_config;
    memset(fixture, 0, sizeof(*fixture));
    fixture->client_fd = -1;
    if (!test_reactor_start(&fixture->transport)) return false;
    fixture->manager = break_session_manager_create(&session_config);
    bridge_config = test_bridge_config(&fixture->now);
    bridge_config.reactor = fixture->transport.reactor;
    bridge_config.max_connections = 1u;
    bridge_config.max_total_pending_bytes = 64u;
    fixture->bridge = break_replication_session_bridge_create(&bridge_config);
    if (fixture->manager == NULL || fixture->bridge == NULL ||
        !break_session_manager_attach_reactor(fixture->manager,
                                              fixture->transport.reactor) ||
        !break_session_manager_set_message_handler(
            fixture->manager, BREAK_NET_MESSAGE_ID_AUTH,
            test_session_socket_auth_handler, fixture) ||
        !break_session_manager_set_message_handler(
            fixture->manager, BREAK_NET_MESSAGE_ID_REPLICATION_FRAGMENT,
            break_replication_session_handle_message, fixture->bridge)) {
        test_session_socket_destroy(fixture);
        return false;
    }
    return true;
}

static bool test_session_socket_connect(TestSessionSocketFixture *fixture)
{
    const SnowEndpoint *bound = SnowAcceptorEndpoint(fixture->transport.acceptor);
    struct sockaddr_in address = {0};
    fixture->client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fixture->client_fd < 0) return false;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    address.sin_port = htons((uint16_t)SnowEndpointPort(bound));
    if (connect(fixture->client_fd, (const struct sockaddr *)&address,
                sizeof(address)) != 0) {
        close(fixture->client_fd);
        fixture->client_fd = -1;
        return false;
    }
    return true;
}

static bool test_session_socket_authenticate(TestSessionSocketFixture *fixture,
                                             uint64_t expected_base_id)
{
    static const uint8_t auth_payload[] = {'a', 'u', 't', 'h'};
    size_t previous_calls = fixture->auth_calls;
    size_t i;
    if (!test_session_socket_connect(fixture)) return false;
    fixture->connection = 0u;
    fixture->sequence = 1u;
    if (!test_session_socket_write_frame(fixture, BREAK_NET_MESSAGE_ID_AUTH,
                                         fixture->sequence, auth_payload,
                                         sizeof(auth_payload))) {
        return false;
    }
    for (i = 0u; i < 5000u; ++i) {
        if (fixture->auth_calls == previous_calls + 1u && fixture->connection != 0u &&
            break_session_manager_state(fixture->manager, fixture->connection) ==
                BREAK_SESSION_AUTHENTICATED) {
            return break_replication_session_connection_open(
                fixture->bridge, fixture->connection, expected_base_id);
        }
        if (!test_session_socket_pump(fixture)) return false;
        usleep(1000u);
    }
    return false;
}

static bool test_session_socket_wait_stats(TestSessionSocketFixture *fixture,
                                           uint64_t completed_packets,
                                           uint64_t rejected_fragments)
{
    size_t i;
    for (i = 0u; i < 5000u; ++i) {
        BreakReplicationSessionBridgeStats stats;
        break_replication_session_bridge_stats(fixture->bridge, &stats);
        if (stats.completed_packets >= completed_packets &&
            stats.rejected_fragments >= rejected_fragments) {
            return true;
        }
        if (!test_session_socket_pump(fixture)) return false;
        usleep(1000u);
    }
    return false;
}

static bool test_session_socket_disconnect(TestSessionSocketFixture *fixture)
{
    size_t i;
    close(fixture->client_fd);
    fixture->client_fd = -1;
    for (i = 0u; i < 5000u; ++i) {
        if (break_session_manager_state(fixture->manager, fixture->connection) ==
            BREAK_SESSION_CLOSED) {
            return true;
        }
        if (!test_session_socket_pump(fixture)) return false;
        usleep(1000u);
    }
    return false;
}

static void test_session_socket_consume_polled_completion(
    BreakReplicationSessionCompletion *completion)
{
    break_test_replication_consumer_count++;
    break_replication_session_completion_release(completion);
}

typedef struct TestSessionSocketLoopbackCase {
    TestSessionSocketFixture fixture;
    BreakReplicationFragment *first;
    BreakReplicationFragment *second;
    size_t first_count;
    size_t second_count;
    BreakReplicationSessionCompletion completions[2];
} TestSessionSocketLoopbackCase;

static void test_session_socket_loopback_cleanup(TestSessionSocketLoopbackCase *test)
{
    size_t i;
    for (i = 0u; i < 2u; ++i)
        break_replication_session_completion_release(&test->completions[i]);
    break_replication_fragments_free(test->first, test->first_count);
    break_replication_fragments_free(test->second, test->second_count);
    test_session_socket_destroy(&test->fixture);
}

static void test_session_socket_loopback_run(TestSessionSocketLoopbackCase *test)
{
    static const uint8_t first_payload[] = "abcdefghij";
    static const uint8_t second_payload[] = "KLMNOPQR";
    static const uint64_t expected_base_id = 77u;
    BreakReplicationFragment wrong_base;
    BreakReplicationSessionBridgeStats stats;
    BreakSessionApplyStats session_stats;
    uint8_t duplicate[128];
    size_t duplicate_size = 0u;

    ASSERT_TRUE(test_session_socket_start(&test->fixture));
    ASSERT_TRUE(test_session_socket_authenticate(&test->fixture, expected_base_id));
    ASSERT_EQ(break_replication_fragment_payload(
                  100u, expected_base_id, first_payload, sizeof(first_payload) - 1u,
                  4u, &test->first, &test->first_count), BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(break_replication_fragment_payload(
                  200u, expected_base_id, second_payload, sizeof(second_payload) - 1u,
                  4u, &test->second, &test->second_count), BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(test->first_count, 3u);
    ASSERT_EQ(test->second_count, 2u);

    wrong_base = test->first[2];
    wrong_base.base_id = expected_base_id + 1u;
    ASSERT_TRUE(test_session_socket_write_fragment(&test->fixture, &wrong_base));
    ASSERT_TRUE(test_session_socket_wait_stats(&test->fixture, 0u, 1u));
    ASSERT_EQ(break_session_manager_state(test->fixture.manager, test->fixture.connection),
              BREAK_SESSION_AUTHENTICATED);
    break_session_manager_apply_stats(test->fixture.manager, &session_stats);
    ASSERT_EQ(session_stats.handler_failed, 1u);

    ASSERT_EQ(break_replication_wire_encode(&test->first[2], duplicate, sizeof(duplicate),
                                             &duplicate_size),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_TRUE(test_session_socket_write_brfg(&test->fixture, duplicate, duplicate_size));
    ASSERT_TRUE(test_session_socket_write_brfg(&test->fixture, duplicate, duplicate_size));
    ASSERT_EQ(break_replication_wire_encode(&test->second[1], duplicate, sizeof(duplicate),
                                             &duplicate_size),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_TRUE(test_session_socket_write_brfg(&test->fixture, duplicate, duplicate_size));
    ASSERT_TRUE(test_session_socket_write_brfg(&test->fixture, duplicate, duplicate_size));
    ASSERT_TRUE(test_session_socket_write_fragment(&test->fixture, &test->first[0]));
    ASSERT_TRUE(test_session_socket_write_fragment(&test->fixture, &test->second[0]));
    ASSERT_TRUE(test_session_socket_write_fragment(&test->fixture, &test->first[1]));
    ASSERT_TRUE(test_session_socket_wait_stats(&test->fixture, 2u, 1u));

    break_replication_session_bridge_stats(test->fixture.bridge, &stats);
    ASSERT_EQ(stats.connections, 1u);
    ASSERT_EQ(stats.pending_bytes, 0u);
    ASSERT_EQ(stats.completion_count, 2u);
    ASSERT_EQ(stats.completion_bytes, 18u);
    ASSERT_EQ(stats.rejected_fragments, 1u);
    ASSERT_EQ(stats.duplicate_fragments, 2u);
    ASSERT_EQ(stats.completed_packets, 2u);
    ASSERT_EQ(stats.dropped_completions, 0u);
    ASSERT_EQ(break_test_replication_consumer_count, 0u);

    ASSERT_EQ(break_replication_session_poll_completed(
                  test->fixture.bridge, test->completions, 2u), 2u);
    ASSERT_EQ(test->completions[0].connection, test->fixture.connection);
    ASSERT_EQ(test->completions[0].delta_id, 200u);
    ASSERT_EQ(test->completions[0].payload_size, sizeof(second_payload) - 1u);
    ASSERT_TRUE(memcmp(test->completions[0].payload, second_payload,
                       sizeof(second_payload) - 1u) == 0);
    ASSERT_EQ(test->completions[1].connection, test->fixture.connection);
    ASSERT_EQ(test->completions[1].delta_id, 100u);
    ASSERT_EQ(test->completions[1].payload_size, sizeof(first_payload) - 1u);
    ASSERT_TRUE(memcmp(test->completions[1].payload, first_payload,
                       sizeof(first_payload) - 1u) == 0);
    test_session_socket_consume_polled_completion(&test->completions[0]);
    test_session_socket_consume_polled_completion(&test->completions[1]);
    ASSERT_EQ(break_test_replication_consumer_count, 2u);
    break_replication_session_bridge_stats(test->fixture.bridge, &stats);
    ASSERT_EQ(stats.completion_count, 0u);
    ASSERT_EQ(stats.completion_bytes, 0u);
}

TEST(bridge_socket_loopback_reassembles_interleaved_duplicates_in_fifo)
{
    TestSessionSocketLoopbackCase test = {0};
    break_test_replication_consumer_count = 0u;
    test_session_socket_loopback_run(&test);
    test_session_socket_loopback_cleanup(&test);
}

typedef struct TestSessionSocketReconnectCase {
    TestSessionSocketFixture fixture;
    BreakReplicationFragment *old;
    BreakReplicationFragment *fresh;
    size_t old_count;
    size_t fresh_count;
    BreakReplicationSessionCompletion completion;
    BreakConnectionKey original_connection;
} TestSessionSocketReconnectCase;

static void test_session_socket_reconnect_cleanup(TestSessionSocketReconnectCase *test)
{
    break_replication_session_completion_release(&test->completion);
    break_replication_fragments_free(test->old, test->old_count);
    break_replication_fragments_free(test->fresh, test->fresh_count);
    test_session_socket_destroy(&test->fixture);
}

static void test_session_socket_reconnect_run(TestSessionSocketReconnectCase *test)
{
    static const uint8_t old_payload[] = "old";
    static const uint8_t fresh_payload[] = "fresh";
    static const uint64_t expected_base_id = 88u;
    BreakReplicationSessionBridgeStats stats;

    ASSERT_TRUE(test_session_socket_start(&test->fixture));
    ASSERT_TRUE(test_session_socket_authenticate(&test->fixture, expected_base_id));
    test->original_connection = test->fixture.connection;
    ASSERT_EQ(break_replication_fragment_payload(
                  40u, expected_base_id, old_payload, sizeof(old_payload) - 1u,
                  3u, &test->old, &test->old_count), BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(break_replication_fragment_payload(
                  1u, expected_base_id, fresh_payload, sizeof(fresh_payload) - 1u,
                  3u, &test->fresh, &test->fresh_count), BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(test->old_count, 1u);
    ASSERT_EQ(test->fresh_count, 2u);
    ASSERT_TRUE(test_session_socket_write_fragment(&test->fixture, &test->old[0]));
    ASSERT_TRUE(test_session_socket_wait_stats(&test->fixture, 1u, 0u));
    ASSERT_EQ(break_test_replication_consumer_count, 0u);
    ASSERT_EQ(break_replication_session_poll_completed(
                  test->fixture.bridge, &test->completion, 1u), 1u);
    ASSERT_EQ(test->completion.connection, test->original_connection);
    ASSERT_EQ(test->completion.delta_id, 40u);
    ASSERT_EQ(test->completion.payload_size, sizeof(old_payload) - 1u);
    ASSERT_TRUE(memcmp(test->completion.payload, old_payload,
                       sizeof(old_payload) - 1u) == 0);
    test_session_socket_consume_polled_completion(&test->completion);

    ASSERT_TRUE(test_session_socket_disconnect(&test->fixture));
    ASSERT_TRUE(break_replication_session_connection_close(
        test->fixture.bridge, test->original_connection));
    break_replication_session_bridge_stats(test->fixture.bridge, &stats);
    ASSERT_EQ(stats.connections, 0u);
    ASSERT_EQ(stats.pending_bytes, 0u);
    ASSERT_EQ(stats.completion_count, 0u);

    ASSERT_TRUE(test_session_socket_authenticate(&test->fixture, expected_base_id));
    ASSERT_EQ(test->fixture.connection, test->original_connection);
    break_test_replication_consumer_count = 0u;
    ASSERT_TRUE(test_session_socket_write_fragment(&test->fixture, &test->fresh[1]));
    ASSERT_TRUE(test_session_socket_write_fragment(&test->fixture, &test->fresh[0]));
    ASSERT_TRUE(test_session_socket_wait_stats(&test->fixture, 2u, 0u));
    break_replication_session_bridge_stats(test->fixture.bridge, &stats);
    ASSERT_EQ(stats.connections, 1u);
    ASSERT_EQ(stats.completion_count, 1u);
    ASSERT_EQ(stats.rejected_fragments, 0u);
    ASSERT_EQ(break_test_replication_consumer_count, 0u);
    ASSERT_EQ(break_replication_session_poll_completed(
                  test->fixture.bridge, &test->completion, 1u), 1u);
    ASSERT_EQ(test->completion.connection, test->original_connection);
    ASSERT_EQ(test->completion.delta_id, 1u);
    ASSERT_EQ(test->completion.payload_size, sizeof(fresh_payload) - 1u);
    ASSERT_TRUE(memcmp(test->completion.payload, fresh_payload,
                       sizeof(fresh_payload) - 1u) == 0);
    test_session_socket_consume_polled_completion(&test->completion);
    ASSERT_EQ(break_test_replication_consumer_count, 1u);
}

TEST(bridge_socket_reconnect_same_key_resets_completed_high_water)
{
    TestSessionSocketReconnectCase test = {0};
    break_test_replication_consumer_count = 0u;
    test_session_socket_reconnect_run(&test);
    test_session_socket_reconnect_cleanup(&test);
}

static BreakReplicationFragment test_outbound_fragment(void)
{
    static const uint8_t data[] = {0xaau, 0xbbu, 0xccu, 0xddu};
    BreakReplicationFragment fragment = {
        1u, 2u, 0u, 1u, 0x11223344u, data, sizeof(data)
    };
    return fragment;
}

static uint32_t test_outbound_checksum(const uint8_t *data, size_t size)
{
    uint32_t hash = 2166136261u;
    for (size_t i = 0u; i < size; ++i) {
        hash ^= data[i];
        hash *= 16777619u;
    }
    return hash;
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
    BreakReplicationSessionCompletion completion;
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

    config.message_id = 0x4100u;
    fragment.checksum = test_outbound_checksum(fragment.data, fragment.size);
    bridge = break_replication_session_bridge_create(&config);
    ASSERT_NOT_NULL(bridge);
    ASSERT_TRUE(break_replication_session_connection_open(bridge, 0x123u, 2u));
    ASSERT_EQ(break_replication_session_send_fragment(bridge, 0x123u, &fragment),
              BREAK_NET_SEND_OK);
    ASSERT_EQ(break_net_reactor_poll_outbound_for_test(
                  fixture.reactor, &outbound_connection, &outbound),
              BREAK_NET_EVENT_OK);
    ASSERT_EQ(outbound.message_id, 0x4100u);
    ASSERT_TRUE(break_replication_session_handle_message(0x123u, &outbound, bridge));
    outbound.message_id = BREAK_NET_MESSAGE_ID_REPLICATION_FRAGMENT;
    ASSERT_FALSE(break_replication_session_handle_message(0x123u, &outbound, bridge));
    outbound.message_id = 0x4100u;
    ASSERT_EQ(break_replication_session_poll_completed(bridge, &completion, 1u), 1u);
    ASSERT_EQ(completion.connection, 0x123u);
    ASSERT_EQ(completion.payload_size, 4u);
    break_replication_session_completion_release(&completion);
    break_net_message_release(&outbound);
    break_replication_session_bridge_destroy(bridge);
    test_reactor_destroy(&fixture);
}

TEST(bridge_send_propagates_reactor_closed_overload_and_caller_retry)
{
    uint64_t now = 0u;
    BreakReplicationSessionBridgeConfig config = test_bridge_config(&now);
    BreakNetReactorConfig reactor_config = {BREAK_NET_DRIVE_STEP, 0, 4u, 0, 0u, 0u, false};
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


TEST(bridge_selective_poll_wraps_ring_and_preserves_survivor_order)
{
    uint64_t now = 0u;
    BreakReplicationSessionBridgeConfig config = test_bridge_config(&now);
    BreakReplicationSessionBridge *bridge =
        break_replication_session_bridge_create(&config);
    BreakReplicationSessionCompletion selected[2];
    BreakReplicationSessionCompletion rest[3];
    BreakReplicationSessionBridgeStats stats;
    ASSERT_NOT_NULL(bridge);
    ASSERT_TRUE(break_replication_session_connection_open(bridge, 1u, 7u));
    ASSERT_TRUE(break_replication_session_connection_open(bridge, 2u, 7u));
    ASSERT_TRUE(test_push_payload(bridge, 1u, 11u, 7u, "a1", 2u));
    ASSERT_TRUE(test_push_payload(bridge, 2u, 21u, 7u, "b1", 2u));
    ASSERT_TRUE(test_push_payload(bridge, 1u, 12u, 7u, "a2", 2u));
    ASSERT_TRUE(test_push_payload(bridge, 2u, 22u, 7u, "b2", 2u));
    ASSERT_EQ(break_replication_session_poll_completed_for_connection(
                  bridge, 1u, selected, 2u),
              2u);
    ASSERT_EQ(selected[0].delta_id, 11u);
    ASSERT_EQ(selected[1].delta_id, 12u);
    ASSERT_TRUE(memcmp(selected[0].payload, "a1", 2u) == 0);
    ASSERT_TRUE(memcmp(selected[1].payload, "a2", 2u) == 0);
    break_replication_session_completion_release(&selected[0]);
    break_replication_session_completion_release(&selected[1]);
    break_replication_session_bridge_stats(bridge, &stats);
    ASSERT_EQ(stats.completion_count, 2u);
    ASSERT_EQ(stats.completion_bytes, 4u);
    ASSERT_TRUE(test_push_payload(bridge, 1u, 13u, 7u, "a3", 2u));
    ASSERT_TRUE(test_push_payload(bridge, 2u, 23u, 7u, "b3", 2u));
    ASSERT_EQ(break_replication_session_poll_completed_for_connection(
                  bridge, 2u, selected, 2u),
              2u);
    ASSERT_EQ(selected[0].delta_id, 21u);
    ASSERT_EQ(selected[1].delta_id, 22u);
    ASSERT_TRUE(memcmp(selected[0].payload, "b1", 2u) == 0);
    ASSERT_TRUE(memcmp(selected[1].payload, "b2", 2u) == 0);
    break_replication_session_completion_release(&selected[0]);
    break_replication_session_completion_release(&selected[1]);
    break_replication_session_bridge_stats(bridge, &stats);
    ASSERT_EQ(stats.completion_count, 2u);
    ASSERT_EQ(stats.completion_bytes, 4u);
    ASSERT_TRUE(test_push_payload(bridge, 1u, 14u, 7u, "a4", 2u));
    ASSERT_EQ(break_replication_session_poll_completed(bridge, rest, 3u), 3u);
    ASSERT_EQ(rest[0].delta_id, 13u);
    ASSERT_EQ(rest[1].delta_id, 23u);
    ASSERT_EQ(rest[2].delta_id, 14u);
    ASSERT_TRUE(memcmp(rest[0].payload, "a3", 2u) == 0);
    ASSERT_TRUE(memcmp(rest[1].payload, "b3", 2u) == 0);
    ASSERT_TRUE(memcmp(rest[2].payload, "a4", 2u) == 0);
    for (size_t i = 0u; i < 3u; ++i)
        break_replication_session_completion_release(&rest[i]);
    break_replication_session_bridge_stats(bridge, &stats);
    ASSERT_EQ(stats.completion_count, 0u);
    ASSERT_EQ(stats.completion_bytes, 0u);
    break_replication_session_bridge_destroy(bridge);
}

TEST(bridge_rebaseline_preserves_keys_and_drops_old_completions)
{
    static const char pending_payload[] = "abcdefgh";
    static const char new_payload[] = "new-data";
    uint64_t now = 100u;
    BreakReplicationSessionBridgeConfig config = test_bridge_config(&now);
    BreakNetReactorConfig reactor_config = {BREAK_NET_DRIVE_STEP, 0, 4u, 0, 0u, 0u, false};
    BreakNetReactor *reactor = break_net_reactor_create(&reactor_config);
    BreakReplicationSessionBridge *bridge;
    BreakReplicationFragment *pending = NULL;
    BreakReplicationFragment *fresh = NULL;
    size_t pending_count = 0u;
    size_t fresh_count = 0u;
    BreakReplicationSessionCompletion completions[2];
    BreakReplicationSessionBridgeStats stats;
    size_t i;

    ASSERT_NOT_NULL(reactor);
    config.reactor = reactor;
    bridge = break_replication_session_bridge_create(&config);
    ASSERT_NOT_NULL(bridge);
    ASSERT_TRUE(break_replication_session_connection_open(bridge, 11u, 7u));
    ASSERT_TRUE(break_replication_session_connection_open(bridge, 22u, 7u));
    ASSERT_EQ(break_replication_fragment_payload(
                  70u, 7u, pending_payload, sizeof(pending_payload) - 1u, 4u,
                  &pending, &pending_count),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(break_replication_fragment_payload(
                  1u, 8u, new_payload, sizeof(new_payload) - 1u, 4u,
                  &fresh, &fresh_count),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(pending_count, 2u);
    ASSERT_EQ(fresh_count, 2u);

    ASSERT_TRUE(test_push_fragment(bridge, 11u, &pending[0]));
    ASSERT_TRUE(test_push_fragment(bridge, 22u, &pending[0]));
    ASSERT_TRUE(test_push_payload(bridge, 11u, 80u, 7u, "old-a", 5u));
    ASSERT_TRUE(test_push_payload(bridge, 22u, 81u, 7u, "old-b", 5u));
    break_replication_session_bridge_stats(bridge, &stats);
    ASSERT_EQ(stats.connections, 2u);
    ASSERT_EQ(stats.pending_bytes, 8u);
    ASSERT_EQ(stats.completion_count, 2u);
    ASSERT_EQ(stats.completion_bytes, 10u);
    ASSERT_EQ(stats.dropped_completions, 0u);

    break_replication_session_rebaseline(NULL, 8u);
    break_replication_session_rebaseline(bridge, 8u);
    break_replication_session_bridge_stats(bridge, &stats);
    ASSERT_EQ(stats.connections, 2u);
    ASSERT_EQ(stats.pending_bytes, 0u);
    ASSERT_EQ(stats.completion_count, 0u);
    ASSERT_EQ(stats.completion_bytes, 0u);
    ASSERT_EQ(stats.dropped_completions, 2u);

    ASSERT_FALSE(test_push_payload(bridge, 11u, 1u, 7u, "old", 3u));
    ASSERT_EQ(break_replication_session_send_fragment(bridge, 11u, &pending[0]),
              BREAK_NET_SEND_INVALID);
    ASSERT_EQ(break_replication_session_send_fragment(bridge, 11u, &fresh[0]),
              BREAK_NET_SEND_CLOSED);

    ASSERT_TRUE(test_push_fragment(bridge, 11u, &fresh[0]));
    ASSERT_TRUE(test_push_fragment(bridge, 22u, &fresh[0]));
    ASSERT_TRUE(test_push_fragment(bridge, 11u, &fresh[1]));
    ASSERT_TRUE(test_push_fragment(bridge, 22u, &fresh[1]));
    ASSERT_EQ(break_replication_session_poll_completed(bridge, completions, 2u), 2u);
    for (i = 0u; i < 2u; ++i) {
        ASSERT_EQ(completions[i].connection, i == 0u ? 11u : 22u);
        ASSERT_EQ(completions[i].delta_id, 1u);
        ASSERT_EQ(completions[i].payload_size, sizeof(new_payload) - 1u);
        ASSERT_TRUE(memcmp(completions[i].payload, new_payload,
                           sizeof(new_payload) - 1u) == 0);
        break_replication_session_completion_release(&completions[i]);
    }
    break_replication_session_bridge_stats(bridge, &stats);
    ASSERT_EQ(stats.connections, 2u);
    ASSERT_EQ(stats.pending_bytes, 0u);
    ASSERT_EQ(stats.completion_count, 0u);
    ASSERT_EQ(stats.completion_bytes, 0u);
    ASSERT_EQ(stats.rejected_fragments, 1u);
    ASSERT_EQ(stats.completed_packets, 4u);
    ASSERT_EQ(stats.dropped_completions, 2u);

    break_replication_fragments_free(fresh, fresh_count);
    break_replication_fragments_free(pending, pending_count);
    break_replication_session_bridge_destroy(bridge);
    break_net_reactor_destroy(reactor);
}

TEST(bridge_rebaseline_clears_nonzero_head_wrapped_completions)
{
    uint64_t now = 100u;
    BreakReplicationSessionBridgeConfig config = test_bridge_config(&now);
    BreakReplicationSessionBridge *bridge =
        break_replication_session_bridge_create(&config);
    BreakReplicationSessionCompletion completions[4];
    BreakReplicationSessionBridgeStats stats;
    size_t i;

    ASSERT_NOT_NULL(bridge);
    ASSERT_TRUE(break_replication_session_connection_open(bridge, 11u, 7u));
    ASSERT_TRUE(break_replication_session_connection_open(bridge, 22u, 7u));
    ASSERT_TRUE(test_push_payload(bridge, 11u, 60u, 7u, "aa", 2u));
    ASSERT_TRUE(test_push_payload(bridge, 22u, 61u, 7u, "bb", 2u));
    ASSERT_EQ(break_replication_session_poll_completed(bridge, completions, 2u), 2u);
    for (i = 0u; i < 2u; ++i) {
        ASSERT_EQ(completions[i].delta_id, 60u + i);
        break_replication_session_completion_release(&completions[i]);
    }
    ASSERT_EQ(break_replication_session_completion_head_for_test(bridge), 2u);

    ASSERT_TRUE(test_push_payload(bridge, 11u, 70u, 7u, "old-a", 5u));
    ASSERT_TRUE(test_push_payload(bridge, 22u, 71u, 7u, "old-b", 5u));
    ASSERT_TRUE(test_push_payload(bridge, 11u, 72u, 7u, "old-c", 5u));
    break_replication_session_bridge_stats(bridge, &stats);
    ASSERT_EQ(stats.completion_count, 3u);
    ASSERT_EQ(stats.completion_bytes, 15u);
    ASSERT_EQ(stats.completed_packets, 5u);
    ASSERT_EQ(stats.dropped_completions, 0u);
    ASSERT_EQ(break_replication_session_completion_head_for_test(bridge), 2u);

    break_replication_session_rebaseline(bridge, 8u);
    break_replication_session_bridge_stats(bridge, &stats);
    ASSERT_EQ(stats.connections, 2u);
    ASSERT_EQ(stats.pending_bytes, 0u);
    ASSERT_EQ(stats.completion_count, 0u);
    ASSERT_EQ(stats.completion_bytes, 0u);
    ASSERT_EQ(stats.dropped_completions, 3u);
    ASSERT_EQ(break_replication_session_completion_head_for_test(bridge), 0u);

    ASSERT_FALSE(test_push_payload(bridge, 11u, 1u, 7u, "old", 3u));
    ASSERT_TRUE(test_push_payload(bridge, 11u, 1u, 8u, "new-a", 5u));
    ASSERT_TRUE(test_push_payload(bridge, 22u, 1u, 8u, "new-b", 5u));
    ASSERT_EQ(break_replication_session_poll_completed(bridge, completions, 4u), 2u);
    for (i = 0u; i < 2u; ++i) {
        ASSERT_EQ(completions[i].connection, i == 0u ? 11u : 22u);
        ASSERT_EQ(completions[i].delta_id, 1u);
        ASSERT_EQ(completions[i].payload_size, 5u);
        ASSERT_TRUE(memcmp(completions[i].payload, i == 0u ? "new-a" : "new-b", 5u) == 0);
        break_replication_session_completion_release(&completions[i]);
    }
    ASSERT_EQ(break_replication_session_poll_completed(bridge, completions, 4u), 0u);
    break_replication_session_bridge_stats(bridge, &stats);
    ASSERT_EQ(stats.connections, 2u);
    ASSERT_EQ(stats.completion_count, 0u);
    ASSERT_EQ(stats.completion_bytes, 0u);
    ASSERT_EQ(stats.rejected_fragments, 1u);
    ASSERT_EQ(stats.completed_packets, 7u);
    ASSERT_EQ(stats.dropped_completions, 3u);
    break_replication_session_bridge_destroy(bridge);
}

TEST(bridge_metadata_budget_rejects_large_counts_before_allocation)
{
    const size_t unit = sizeof(BreakReplicationFragment) + sizeof(uint8_t *) +
                        sizeof(uint8_t);
    uint64_t now = 10u;
    BreakReplicationSessionBridgeConfig config = test_bridge_config(&now);
    BreakReplicationSessionBridge *bridge;
    BreakReplicationSessionBridgeStats stats;
    BreakReplicationFragment *fragments = NULL;
    BreakReplicationFragment fragment;
    size_t count = 0u;
    const uint8_t payload = 0x5au;

    config.stream_capacity = 64u;
    config.max_metadata_bytes_per_connection = 4u * unit;
    config.max_total_metadata_bytes = 8u * unit;
    config.max_fragment_count = 250000u;
    bridge = break_replication_session_bridge_create(&config);
    ASSERT_NOT_NULL(bridge);
    ASSERT_TRUE(break_replication_session_connection_open(bridge, 1u, 5u));
    ASSERT_EQ(break_replication_fragment_payload(
                  1u, 5u, &payload, 1u, 1u, &fragments, &count),
              BREAK_REPLICATION_FRAGMENT_OK);
    fragment = fragments[0];

    fragment.fragment_count = 250000u;
    ASSERT_FALSE(test_push_fragment(bridge, 1u, &fragment));
    break_replication_session_bridge_stats(bridge, &stats);
    ASSERT_EQ(stats.rejected_fragments, 1u);
    ASSERT_EQ(stats.pending_bytes, 0u);
    ASSERT_EQ(stats.pending_metadata_bytes, 0u);

    fragment.fragment_count = 4u;
    ASSERT_TRUE(test_push_fragment(bridge, 1u, &fragment));
    break_replication_session_bridge_stats(bridge, &stats);
    ASSERT_EQ(stats.pending_bytes, 1u);
    ASSERT_EQ(stats.pending_metadata_bytes, 4u * unit);
    ASSERT_TRUE(test_push_fragment(bridge, 1u, &fragment));
    break_replication_session_bridge_stats(bridge, &stats);
    ASSERT_EQ(stats.pending_metadata_bytes, 4u * unit);

    fragment.delta_id = 2u;
    ASSERT_FALSE(test_push_fragment(bridge, 1u, &fragment));
    break_replication_session_bridge_stats(bridge, &stats);
    ASSERT_EQ(stats.pending_bytes, 1u);
    ASSERT_EQ(stats.pending_metadata_bytes, 4u * unit);
    ASSERT_TRUE(break_replication_session_connection_close(bridge, 1u));
    break_replication_session_bridge_stats(bridge, &stats);
    ASSERT_EQ(stats.pending_bytes, 0u);
    ASSERT_EQ(stats.pending_metadata_bytes, 0u);

    break_replication_fragments_free(fragments, count);
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
    RUN_TEST(bridge_inbound_fragment_expiration_is_counted_without_owner_tick);
    RUN_TEST(bridge_wrapped_fifo_close_compaction_preserves_survivor_order);
    RUN_TEST(bridge_selective_poll_wraps_ring_and_preserves_survivor_order);
    RUN_TEST(bridge_socket_loopback_reassembles_interleaved_duplicates_in_fifo);
    RUN_TEST(bridge_socket_reconnect_same_key_resets_completed_high_water);
    RUN_TEST(bridge_send_validates_and_encodes_through_real_reactor);
    RUN_TEST(bridge_send_propagates_reactor_closed_overload_and_caller_retry);
    RUN_TEST(bridge_tick_expires_every_connection_without_traffic_and_honors_disable);
    RUN_TEST(bridge_non_auth_handler_failure_keeps_session_authenticated);
    RUN_TEST(bridge_rebaseline_preserves_keys_and_drops_old_completions);
    RUN_TEST(bridge_rebaseline_clears_nonzero_head_wrapped_completions);
    RUN_TEST(bridge_metadata_budget_rejects_large_counts_before_allocation);
TEST_MAIN_END()
