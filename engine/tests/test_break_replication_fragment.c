#include "test_framework.h"
#include <network/break_replication_fragment.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

TEST(fragment_round_trip_reordered_and_checksum)
{
    const uint8_t payload[] = "abcdefghijklmnopqrstuvwxyz";
    BreakReplicationFragment *fragments = NULL;
    size_t count = 0u;
    BreakReplicationReassembler *reassembler;
    uint8_t *assembled = NULL;
    size_t assembled_size = 0u;

    ASSERT_EQ(break_replication_fragment_payload(7u, 3u, payload, sizeof(payload) - 1u,
                                                 5u, &fragments, &count),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(count, 6u);
    ASSERT_EQ(fragments[0].delta_id, 7u);
    ASSERT_EQ(fragments[0].base_id, 3u);
    ASSERT_EQ(fragments[0].fragment_count, 6u);
    ASSERT_EQ(fragments[0].fragment_index, 0u);
    reassembler = break_replication_reassembler_create(3u);
    ASSERT_NOT_NULL(reassembler);
    ASSERT_EQ(break_replication_reassembler_push(reassembler, &fragments[4], &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(break_replication_reassembler_push(reassembler, &fragments[0], &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(break_replication_reassembler_push(reassembler, &fragments[5], &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(break_replication_reassembler_push(reassembler, &fragments[2], &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(break_replication_reassembler_push(reassembler, &fragments[1], &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(break_replication_reassembler_push(reassembler, &fragments[3], &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_COMPLETE);
    ASSERT_EQ(assembled_size, sizeof(payload) - 1u);
    ASSERT_TRUE(memcmp(assembled, payload, assembled_size) == 0);
    break_replication_reassembly_free(assembled);
    break_replication_reassembler_destroy(reassembler);
    break_replication_fragments_free(fragments, count);
}

TEST(fragment_rejects_duplicates_conflicts_loss_and_base_mismatch)
{
    const uint8_t payload[] = "0123456789";
    BreakReplicationFragment *fragments = NULL;
    size_t count = 0u;
    BreakReplicationReassembler *reassembler;
    uint8_t *assembled = NULL;
    size_t assembled_size = 0u;

    ASSERT_EQ(break_replication_fragment_payload(11u, 9u, payload, sizeof(payload) - 1u,
                                                 4u, &fragments, &count),
              BREAK_REPLICATION_FRAGMENT_OK);
    reassembler = break_replication_reassembler_create(9u);
    ASSERT_EQ(break_replication_reassembler_push(reassembler, &fragments[0], NULL, NULL),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(break_replication_reassembler_push(reassembler, &fragments[0], NULL, NULL),
              BREAK_REPLICATION_REASSEMBLY_DUPLICATE);
    fragments[0].base_id++;
    ASSERT_EQ(break_replication_reassembler_push(reassembler, &fragments[0], NULL, NULL),
              BREAK_REPLICATION_REASSEMBLY_BASE_MISMATCH);
    fragments[0].base_id--;
    fragments[1].checksum++;
    ASSERT_EQ(break_replication_reassembler_push(reassembler, &fragments[1], NULL, NULL),
              BREAK_REPLICATION_REASSEMBLY_CHECKSUM_MISMATCH);
    fragments[1].checksum--;
    {
        BreakReplicationFragment conflict = fragments[0];
        conflict.delta_id = 10u;
        conflict.data = fragments[0].data;
        conflict.size = fragments[0].size;
        conflict.checksum = fragments[0].checksum;
        ASSERT_EQ(break_replication_reassembler_push(reassembler, &conflict, NULL, NULL),
                  BREAK_REPLICATION_REASSEMBLY_CONFLICT);
    }
    ASSERT_EQ(break_replication_reassembler_push(reassembler, &fragments[2], &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(assembled, NULL);
    ASSERT_EQ(assembled_size, 0u);
    break_replication_reassembler_destroy(reassembler);
    break_replication_fragments_free(fragments, count);
}

TEST(fragment_validation_rejects_invalid_shape_and_checksum)
{
    const uint8_t payload[] = {1u, 2u, 3u};
    BreakReplicationFragment fragment = {0};
    BreakReplicationReassembler *reassembler = break_replication_reassembler_create(1u);
    uint8_t *assembled = NULL;
    size_t assembled_size = 0u;

    ASSERT_NOT_NULL(reassembler);
    ASSERT_EQ(break_replication_reassembler_push(reassembler, &fragment, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INVALID);
    ASSERT_EQ(break_replication_fragment_payload(1u, 1u, payload, sizeof(payload), 0u, NULL, NULL),
              BREAK_REPLICATION_FRAGMENT_INVALID);
    break_replication_reassembler_destroy(reassembler);
}

TEST(fragment_boundary_rejects_empty_oversized_and_transport_limit)
{
    const uint8_t payload[] = {1u, 2u, 3u};
    BreakReplicationFragment *fragments = NULL;
    size_t count = 0u;

    ASSERT_EQ(break_replication_fragment_payload(1u, 1u, payload, sizeof(payload),
                                                 BREAK_NET_MAX_PAYLOAD_SIZE + 1u,
                                                 &fragments, &count),
              BREAK_REPLICATION_FRAGMENT_OVER_LIMIT);
    ASSERT_EQ(break_replication_fragment_payload(1u, 1u, payload, sizeof(payload),
                                                 sizeof(payload), &fragments, &count),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(count, 1u);
    ASSERT_EQ(fragments[0].size, sizeof(payload));
    break_replication_fragments_free(fragments, count);
    ASSERT_EQ(break_replication_fragment_payload(1u, 1u, NULL, 0u, 1u,
                                                 &fragments, &count),
              BREAK_REPLICATION_FRAGMENT_INVALID);
}

TEST(reassembler_rejects_oversized_fragment_and_reset_is_recoverable)
{
    const uint8_t payload[] = {1u};
    BreakReplicationFragment fragment = {11u, 7u, 0u, 1u, 0u, payload, sizeof(payload)};
    BreakReplicationReassembler *reassembler = break_replication_reassembler_create(7u);
    uint8_t *assembled = NULL;
    size_t assembled_size = 0u;

    ASSERT_NOT_NULL(reassembler);
    fragment.checksum = 0u;
    fragment.size = BREAK_NET_MAX_PAYLOAD_SIZE + 1u;
    ASSERT_EQ(break_replication_reassembler_push(reassembler, &fragment, NULL, NULL),
              BREAK_REPLICATION_REASSEMBLY_INVALID);
    fragment.size = sizeof(payload);
    fragment.checksum = 2166136261u ^ payload[0];
    fragment.checksum *= 16777619u;
    ASSERT_EQ(break_replication_reassembler_push(reassembler, &fragment, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_COMPLETE);
    ASSERT_EQ(assembled_size, sizeof(payload));
    break_replication_reassembly_free(assembled);
    break_replication_reassembler_reset(reassembler);
    ASSERT_EQ(break_replication_reassembler_push(reassembler, &fragment, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_COMPLETE);
    break_replication_reassembly_free(assembled);
    break_replication_reassembler_destroy(reassembler);
}

TEST(fragment_and_reassembler_reject_payload_budget)
{
    uint8_t *payload = (uint8_t *)malloc(BREAK_REPLICATION_MAX_REASSEMBLY_SIZE + 1u);
    BreakReplicationFragment *fragments = NULL;
    size_t count = 0u;
    BreakReplicationReassembler *reassembler;
    BreakReplicationFragment fragment = {0};
    uint8_t one = 0x5au;
    size_t i;

    ASSERT_NOT_NULL(payload);
    ASSERT_EQ(break_replication_fragment_payload(1u, 1u, payload,
                                                 BREAK_REPLICATION_MAX_REASSEMBLY_SIZE + 1u,
                                                 BREAK_NET_MAX_PAYLOAD_SIZE,
                                                 &fragments, &count),
              BREAK_REPLICATION_FRAGMENT_OVER_LIMIT);
    reassembler = break_replication_reassembler_create(1u);
    ASSERT_NOT_NULL(reassembler);
    fragment.delta_id = 2u;
    fragment.base_id = 1u;
    fragment.fragment_count = (uint32_t)(BREAK_REPLICATION_MAX_REASSEMBLY_SIZE /
                                         BREAK_NET_MAX_PAYLOAD_SIZE + 1u);
    fragment.size = BREAK_NET_MAX_PAYLOAD_SIZE;
    fragment.data = payload;
    fragment.checksum = 0u;
    for (i = 0u; i < fragment.fragment_count - 1u; ++i) {
        fragment.fragment_index = (uint32_t)i;
        fragment.checksum = 2166136261u;
        {
            size_t j;
            for (j = 0u; j < fragment.size; ++j) {
                fragment.checksum ^= fragment.data[j];
                fragment.checksum *= 16777619u;
            }
        }
        ASSERT_EQ(break_replication_reassembler_push(reassembler, &fragment, NULL, NULL),
                  BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    }
    fragment.fragment_index = 0u;
    fragment.checksum = 2166136261u;
    for (i = 0u; i < fragment.size; ++i) {
        fragment.checksum ^= fragment.data[i];
        fragment.checksum *= 16777619u;
    }
    ASSERT_EQ(break_replication_reassembler_push(reassembler, &fragment, NULL, NULL),
              BREAK_REPLICATION_REASSEMBLY_DUPLICATE);
    payload[0] ^= 1u;
    fragment.checksum = 2166136261u;
    for (i = 0u; i < fragment.size; ++i) {
        fragment.checksum ^= fragment.data[i];
        fragment.checksum *= 16777619u;
    }
    ASSERT_EQ(break_replication_reassembler_push(reassembler, &fragment, NULL, NULL),
              BREAK_REPLICATION_REASSEMBLY_CONFLICT);
    payload[0] ^= 1u;
    fragment.fragment_index = fragment.fragment_count - 1u;
    fragment.size = 1u;
    fragment.data = &one;
    fragment.checksum = 2166136261u ^ one;
    fragment.checksum *= 16777619u;
    ASSERT_EQ(break_replication_reassembler_push(reassembler, &fragment, NULL, NULL),
              BREAK_REPLICATION_REASSEMBLY_OVER_LIMIT);
    break_replication_reassembler_destroy(reassembler);
    free(payload);
}

TEST(reassembler_repeated_fragment_after_complete_starts_new_state)
{
    const uint8_t payload[] = "retry";
    BreakReplicationFragment *fragments = NULL;
    size_t count = 0u;
    BreakReplicationReassembler *reassembler;
    uint8_t *assembled = NULL;
    size_t assembled_size = 0u;

    ASSERT_EQ(break_replication_fragment_payload(21u, 8u, payload, sizeof(payload) - 1u,
                                                 2u, &fragments, &count),
              BREAK_REPLICATION_FRAGMENT_OK);
    reassembler = break_replication_reassembler_create(8u);
    ASSERT_NOT_NULL(reassembler);
    ASSERT_EQ(break_replication_reassembler_push(reassembler, &fragments[0], NULL, NULL),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(break_replication_reassembler_push(reassembler, &fragments[0], NULL, NULL),
              BREAK_REPLICATION_REASSEMBLY_DUPLICATE);
    ASSERT_EQ(break_replication_reassembler_push(reassembler, &fragments[1], &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(break_replication_reassembler_push(reassembler, &fragments[2], &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_COMPLETE);
    ASSERT_EQ(assembled_size, sizeof(payload) - 1u);
    break_replication_reassembly_free(assembled);
    assembled = NULL;
    assembled_size = 0u;
    ASSERT_EQ(break_replication_reassembler_push(reassembler, &fragments[2], &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(assembled, NULL);
    ASSERT_EQ(assembled_size, 0u);
    break_replication_reassembler_destroy(reassembler);
    break_replication_fragments_free(fragments, count);
}

TEST(fragment_into_caller_storage_matches_allocating_api_and_reassembles)
{
    const uint8_t payload[] = {0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u};
    BreakReplicationFragment expected[3];
    BreakReplicationFragment *allocated = NULL;
    size_t allocated_count = 0u;
    size_t count = 0u;
    size_t i;
    BreakReplicationReassembler *reassembler;
    uint8_t *assembled = NULL;
    size_t assembled_size = 0u;

    ASSERT_EQ(break_replication_fragment_payload(41u, 9u, payload, sizeof(payload),
                                                 4u, &allocated, &allocated_count),
              BREAK_REPLICATION_FRAGMENT_OK);
    memcpy(expected, allocated, sizeof(expected));
    ASSERT_EQ(break_replication_fragment_payload_into(
                  41u, 9u, payload, sizeof(payload), 4u,
                  expected, 3u, &count),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(count, 3u);
    for (i = 0u; i < 3u; ++i) {
        ASSERT_EQ(expected[i].delta_id, allocated[i].delta_id);
        ASSERT_EQ(expected[i].base_id, allocated[i].base_id);
        ASSERT_EQ(expected[i].fragment_index, i);
        ASSERT_EQ(expected[i].fragment_count, 3u);
        ASSERT_EQ(expected[i].checksum, allocated[i].checksum);
        ASSERT_EQ(expected[i].size, allocated[i].size);
        ASSERT_TRUE(memcmp(expected[i].data, allocated[i].data,
                           allocated[i].size) == 0);
    }
    ASSERT_EQ(expected[0].size, 4u);
    ASSERT_EQ(expected[1].size, 4u);
    ASSERT_EQ(expected[2].size, 2u);
    reassembler = break_replication_reassembler_create(9u);
    ASSERT_NOT_NULL(reassembler);
    ASSERT_EQ(break_replication_reassembler_push(reassembler, &expected[2],
                                                 &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(break_replication_reassembler_push(reassembler, &expected[1],
                                                 &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(break_replication_reassembler_push(reassembler, &expected[0],
                                                 &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_COMPLETE);
    ASSERT_EQ(assembled_size, sizeof(payload));
    ASSERT_TRUE(memcmp(assembled, payload, sizeof(payload)) == 0);
    break_replication_reassembly_free(assembled);
    break_replication_reassembler_destroy(reassembler);
    break_replication_fragments_free(allocated, allocated_count);
}

TEST(fragment_into_rejects_short_capacity_before_writing)
{
    const uint8_t payload[] = {0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u};
    BreakReplicationFragment fragments[2];
    size_t count = 99u;
    memset(fragments, 0x5a, sizeof(fragments));
    fragments[0].delta_id = UINT64_C(0x12345678);
    ASSERT_EQ(break_replication_fragment_payload_into(
                  1u, 1u, payload, sizeof(payload), 4u,
                  fragments, 0u, &count),
              BREAK_REPLICATION_FRAGMENT_OVER_LIMIT);
    ASSERT_EQ(count, 0u);
    count = 99u;
    ASSERT_EQ(break_replication_fragment_payload_into(
                  1u, 1u, payload, sizeof(payload), 4u,
                  fragments, 2u, &count),
              BREAK_REPLICATION_FRAGMENT_OVER_LIMIT);
    ASSERT_EQ(count, 0u);
    ASSERT_EQ(fragments[0].delta_id, UINT64_C(0x12345678));
}

TEST(reassembler_newer_delta_supersedes_incomplete_and_rejects_old)
{
    const uint8_t old_payload[] = {'o', 'l', 'd'};
    const uint8_t new_payload[] = {'n', 'e', 'w', 'e', 'r'};
    BreakReplicationFragment *old_fragments = NULL;
    BreakReplicationFragment *new_fragments = NULL;
    size_t old_count = 0u;
    size_t new_count = 0u;
    BreakReplicationReassembler *reassembler = break_replication_reassembler_create(4u);
    uint8_t *assembled = NULL;
    size_t assembled_size = 0u;

    ASSERT_EQ(break_replication_fragment_payload(10u, 4u, old_payload,
        sizeof(old_payload), 2u, &old_fragments, &old_count), BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(break_replication_fragment_payload(11u, 4u, new_payload,
        sizeof(new_payload), 2u, &new_fragments, &new_count), BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(break_replication_reassembler_push(reassembler, &old_fragments[0],
                                                 &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(break_replication_reassembler_push(reassembler, &new_fragments[0],
                                                 &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(break_replication_reassembler_push(reassembler, &old_fragments[1],
                                                 &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_CONFLICT);
    ASSERT_EQ(break_replication_reassembler_push(reassembler, &new_fragments[1],
                                                 &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(break_replication_reassembler_push(reassembler, &new_fragments[2],
                                                 &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_COMPLETE);
    ASSERT_EQ(assembled_size, sizeof(new_payload));
    ASSERT_TRUE(memcmp(assembled, new_payload, sizeof(new_payload)) == 0);
    break_replication_reassembly_free(assembled);
    break_replication_reassembler_destroy(reassembler);
    break_replication_fragments_free(new_fragments, new_count);
    break_replication_fragments_free(old_fragments, old_count);
}

TEST(reassembler_completed_high_water_rejects_older_restart)
{
    const uint8_t payload[] = {'x', 'y'};
    BreakReplicationFragment *old_fragments = NULL;
    BreakReplicationFragment *new_fragments = NULL;
    size_t old_count = 0u;
    size_t new_count = 0u;
    BreakReplicationReassembler *reassembler = break_replication_reassembler_create(1u);
    uint8_t *assembled = NULL;
    size_t assembled_size = 0u;

    ASSERT_EQ(break_replication_fragment_payload(10u, 1u, payload, sizeof(payload),
        1u, &old_fragments, &old_count), BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(break_replication_fragment_payload(11u, 1u, payload, sizeof(payload),
        1u, &new_fragments, &new_count), BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(break_replication_reassembler_push(reassembler, &old_fragments[0],
                                                 &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(break_replication_reassembler_push(reassembler, &old_fragments[1],
                                                 &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_COMPLETE);
    break_replication_reassembly_free(assembled);
    assembled = NULL;
    assembled_size = 0u;
    ASSERT_EQ(break_replication_reassembler_push(reassembler, &new_fragments[0],
                                                 &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(break_replication_reassembler_push(reassembler, &new_fragments[1],
                                                 &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_COMPLETE);
    break_replication_reassembly_free(assembled);
    assembled = NULL;
    assembled_size = 0u;
    ASSERT_EQ(break_replication_reassembler_push(reassembler, &old_fragments[0],
                                                 &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_CONFLICT);
    break_replication_reassembly_free(assembled);
    break_replication_reassembler_destroy(reassembler);
    break_replication_fragments_free(new_fragments, new_count);
    break_replication_fragments_free(old_fragments, old_count);
}

TEST(reassembler_failed_supersession_preserves_old_stream)
{
    const uint8_t old_payload[] = {'o', 'l', 'd', '!'};
    const uint8_t new_payload[] = {'n'};
    BreakReplicationFragment *old_fragments = NULL;
    BreakReplicationFragment *new_fragments = NULL;
    size_t old_count = 0u;
    size_t new_count = 0u;
    BreakReplicationReassembler *reassembler = break_replication_reassembler_create(1u);
    BreakReplicationFragment oversized;
    uint8_t *assembled = NULL;
    size_t assembled_size = 0u;

    ASSERT_EQ(break_replication_fragment_payload(10u, 1u, old_payload,
        sizeof(old_payload), 2u, &old_fragments, &old_count), BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(break_replication_fragment_payload(11u, 1u, new_payload,
        sizeof(new_payload), 1u, &new_fragments, &new_count), BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(break_replication_reassembler_push(reassembler, &old_fragments[0],
                                                 &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    oversized = new_fragments[0];
    oversized.fragment_count = 1048576u;
    ASSERT_EQ(break_replication_reassembler_push(reassembler, &oversized,
                                                 &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_OVER_LIMIT);
    ASSERT_EQ(break_replication_reassembler_push(reassembler, &old_fragments[1],
                                                 &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_COMPLETE);
    ASSERT_EQ(assembled_size, sizeof(old_payload));
    ASSERT_TRUE(memcmp(assembled, old_payload, sizeof(old_payload)) == 0);
    break_replication_reassembly_free(assembled);
    break_replication_reassembler_destroy(reassembler);
    break_replication_fragments_free(new_fragments, new_count);
    break_replication_fragments_free(old_fragments, old_count);
}

TEST(reassembler_expires_an_idle_incomplete_stream)
{
    const uint8_t old_payload[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    const uint8_t new_payload[] = {'n', 'e', 'w', '!'};
    BreakReplicationFragment *old_fragments = NULL;
    BreakReplicationFragment *new_fragments = NULL;
    size_t old_count = 0u;
    size_t new_count = 0u;
    BreakReplicationReassembler *reassembler = break_replication_reassembler_create(1u);
    uint8_t *assembled = NULL;
    size_t assembled_size = 0u;

    ASSERT_NOT_NULL(reassembler);
    ASSERT_EQ(break_replication_fragment_payload(20u, 1u, old_payload,
        sizeof(old_payload), 2u, &old_fragments, &old_count), BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(old_count, 3u);
    ASSERT_EQ(break_replication_fragment_payload(21u, 1u, new_payload,
        sizeof(new_payload), 2u, &new_fragments, &new_count), BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_FALSE(break_replication_reassembler_expire(NULL, 100u, 10u));
    ASSERT_EQ(break_replication_reassembler_pending_bytes(NULL), 0u);
    ASSERT_FALSE(break_replication_reassembler_expire(reassembler, 1000u, 10u));
    ASSERT_EQ(break_replication_reassembler_pending_bytes(reassembler), 0u);

    ASSERT_EQ(break_replication_reassembler_push_at(reassembler, &old_fragments[0], 100u,
                                                    &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(break_replication_reassembler_pending_bytes(reassembler), 2u);
    ASSERT_EQ(break_replication_reassembler_push_at(reassembler, &old_fragments[1], 105u,
                                                    &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(break_replication_reassembler_pending_bytes(reassembler), 4u);
    /* idle is measured from the last accepted fragment, and a duplicate counts */
    ASSERT_FALSE(break_replication_reassembler_expire(reassembler, 114u, 10u));
    ASSERT_EQ(break_replication_reassembler_push_at(reassembler, &old_fragments[1], 112u,
                                                    &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_DUPLICATE);
    ASSERT_FALSE(break_replication_reassembler_expire(reassembler, 121u, 10u));
    /* a clock that went backwards is no idle time */
    ASSERT_FALSE(break_replication_reassembler_expire(reassembler, 50u, 10u));
    ASSERT_EQ(break_replication_reassembler_pending_bytes(reassembler), 4u);
    ASSERT_TRUE(break_replication_reassembler_expire(reassembler, 122u, 10u));
    ASSERT_EQ(break_replication_reassembler_pending_bytes(reassembler), 0u);
    ASSERT_FALSE(break_replication_reassembler_expire(reassembler, 500u, 10u));
    {
        BreakReplicationFragment older = old_fragments[0];
        older.delta_id = 19u;
        ASSERT_EQ(break_replication_reassembler_push_at(reassembler, &older, 125u,
                                                        &assembled, &assembled_size),
                  BREAK_REPLICATION_REASSEMBLY_CONFLICT);
    }

    /* a late fragment of the expired delta starts it over, as after a
     * completion; an older delta stays behind the high-water */
    ASSERT_EQ(break_replication_reassembler_push_at(reassembler, &old_fragments[2], 130u,
                                                    &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(break_replication_reassembler_pending_bytes(reassembler), 2u);
    ASSERT_EQ(break_replication_reassembler_push_at(reassembler, &new_fragments[1], 131u,
                                                    &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(break_replication_reassembler_push_at(reassembler, &new_fragments[0], 132u,
                                                    &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_COMPLETE);
    ASSERT_EQ(assembled_size, sizeof(new_payload));
    ASSERT_TRUE(memcmp(assembled, new_payload, sizeof(new_payload)) == 0);
    break_replication_reassembly_free(assembled);
    assembled = NULL;
    /* nothing is pending after completion, so nothing expires */
    ASSERT_EQ(break_replication_reassembler_pending_bytes(reassembler), 0u);
    ASSERT_FALSE(break_replication_reassembler_expire(reassembler, 10000u, 1u));
    /* a zero idle limit expires a pending stream at once */
    break_replication_reassembler_reset(reassembler);
    ASSERT_EQ(break_replication_reassembler_push_at(reassembler, &old_fragments[0], 200u,
                                                    &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_TRUE(break_replication_reassembler_expire(reassembler, 200u, 0u));
    break_replication_reassembler_destroy(reassembler);
    break_replication_fragments_free(new_fragments, new_count);
    break_replication_fragments_free(old_fragments, old_count);
}

TEST(timed_push_matches_untimed_push)
{
    const uint8_t payload[] = "the quick brown fox";
    BreakReplicationFragment *fragments = NULL;
    size_t count = 0u;
    BreakReplicationReassembler *timed = break_replication_reassembler_create(4u);
    BreakReplicationReassembler *untimed = break_replication_reassembler_create(4u);
    ASSERT_NOT_NULL(timed);
    ASSERT_NOT_NULL(untimed);
    ASSERT_EQ(break_replication_fragment_payload(9u, 4u, payload, sizeof(payload) - 1u, 4u,
                                                 &fragments, &count),
              BREAK_REPLICATION_FRAGMENT_OK);
    const size_t order[] = {3u, 0u, 3u, 4u, 1u, 2u};
    for (size_t i = 0u; i < sizeof(order) / sizeof(order[0]); ++i) {
        uint8_t *a = NULL, *b = NULL;
        size_t a_size = 0u, b_size = 0u;
        const BreakReplicationReassemblyResult ra =
            break_replication_reassembler_push_at(timed, &fragments[order[i]], (uint64_t)i,
                                                  &a, &a_size);
        const BreakReplicationReassemblyResult rb =
            break_replication_reassembler_push(untimed, &fragments[order[i]], &b, &b_size);
        ASSERT_EQ(ra, rb);
        ASSERT_EQ(a_size, b_size);
        ASSERT_EQ(break_replication_reassembler_pending_bytes(timed),
                  break_replication_reassembler_pending_bytes(untimed));
        if (a || b) {
            ASSERT_NOT_NULL(a);
            ASSERT_NOT_NULL(b);
            ASSERT_TRUE(memcmp(a, b, a_size) == 0);
        }
        break_replication_reassembly_free(a);
        break_replication_reassembly_free(b);
    }
    break_replication_reassembler_destroy(timed);
    break_replication_reassembler_destroy(untimed);
    break_replication_fragments_free(fragments, count);
}

TEST(rejected_fragments_do_not_refresh_and_plain_push_stays_untimed)
{
    const uint8_t payload[] = {'r', 'e', 'j', 'e', 'c', 't'};
    BreakReplicationFragment *fragments = NULL;
    size_t count = 0u;
    BreakReplicationReassembler *reassembler = break_replication_reassembler_create(2u);
    uint8_t *assembled = NULL;
    size_t assembled_size = 0u;
    uint8_t other[2] = {'x', 'y'};

    ASSERT_NOT_NULL(reassembler);
    ASSERT_EQ(break_replication_fragment_payload(30u, 2u, payload, sizeof(payload), 2u,
                                                 &fragments, &count),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(break_replication_reassembler_push_at(reassembler, &fragments[0], 100u,
                                                    &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    {
        BreakReplicationFragment conflict = fragments[0];
        conflict.data = other;
        conflict.size = sizeof(other);
        conflict.checksum = fragments[1].checksum;
        ASSERT_EQ(break_replication_reassembler_push_at(reassembler, &conflict, 150u,
                                                        &assembled, &assembled_size),
                  BREAK_REPLICATION_REASSEMBLY_CHECKSUM_MISMATCH);
        BreakReplicationFragment changed = fragments[0];
        changed.data = other;
        changed.size = sizeof(other);
        changed.checksum = 0u;
        {
            uint32_t hash = 2166136261u;
            for (size_t i = 0u; i < sizeof(other); ++i) {
                hash ^= other[i];
                hash *= 16777619u;
            }
            changed.checksum = hash;
        }
        ASSERT_EQ(break_replication_reassembler_push_at(reassembler, &changed, 160u,
                                                        &assembled, &assembled_size),
                  BREAK_REPLICATION_REASSEMBLY_CONFLICT);
        BreakReplicationFragment wrong_base = fragments[1];
        wrong_base.base_id = 3u;
        ASSERT_EQ(break_replication_reassembler_push_at(reassembler, &wrong_base, 170u,
                                                        &assembled, &assembled_size),
                  BREAK_REPLICATION_REASSEMBLY_BASE_MISMATCH);
    }
    /* only the accepted fragment at 100 counts */
    ASSERT_TRUE(break_replication_reassembler_expire(reassembler, 110u, 10u));

    /* a stream started by plain push is untimed and is never expired */
    ASSERT_EQ(break_replication_reassembler_push(reassembler, &fragments[0],
                                                 &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_FALSE(break_replication_reassembler_expire(reassembler, 100000u, 1u));
    /* nor does a timed push of the same stream start its clock */
    ASSERT_EQ(break_replication_reassembler_push_at(reassembler, &fragments[0], 200u,
                                                    &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_DUPLICATE);
    ASSERT_FALSE(break_replication_reassembler_expire(reassembler, 100000u, 1u));
    ASSERT_EQ(break_replication_reassembler_pending_bytes(reassembler), 2u);
    /* a newer delta through push_at supersedes the untimed stream and is timed */
    {
        BreakReplicationFragment newer = fragments[0];
        newer.delta_id = 31u;
        ASSERT_EQ(break_replication_reassembler_push_at(reassembler, &newer, 300u,
                                                        &assembled, &assembled_size),
                  BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    }
    ASSERT_FALSE(break_replication_reassembler_expire(reassembler, 309u, 10u));
    ASSERT_TRUE(break_replication_reassembler_expire(reassembler, 310u, 10u));
    break_replication_reassembler_destroy(reassembler);
    break_replication_fragments_free(fragments, count);
}

TEST(reassembly_pool_validates_configuration_and_null_calls)
{
    BreakReplicationReassemblyPool *pool;
    uint64_t completed_id = 99u;
    uint8_t sentinel = 0u;
    uint8_t *assembled = &sentinel;
    size_t assembled_size = 99u;

    ASSERT_EQ(break_replication_reassembly_pool_create(1u, 0u, 1u), NULL);
    ASSERT_EQ(break_replication_reassembly_pool_create(
                  1u, BREAK_REPLICATION_REASSEMBLY_POOL_MAX_STREAMS + 1u, 1u),
              NULL);
    ASSERT_EQ(break_replication_reassembly_pool_create(1u, 1u, 0u), NULL);
    ASSERT_EQ(break_replication_reassembly_pool_create(
                  1u, 1u, BREAK_REPLICATION_MAX_REASSEMBLY_SIZE + 1u),
              NULL);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(NULL), 0u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(NULL), 0u);
    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  NULL, NULL, 100u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INVALID);
    ASSERT_EQ(completed_id, 0u);
    ASSERT_EQ(assembled, NULL);
    ASSERT_EQ(assembled_size, 0u);
    break_replication_reassembly_pool_destroy(NULL);

    pool = break_replication_reassembly_pool_create(1u, 3u, 128u);
    ASSERT_NOT_NULL(pool);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 0u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 0u);
    break_replication_reassembly_pool_destroy(pool);
}

TEST(reassembly_pool_reassembles_three_interleaved_deltas)
{
    const uint8_t payload10[] = "delta-10xx";
    const uint8_t payload11[] = "delta-11yyy";
    const uint8_t payload12[] = "delta-12zzzz";
    BreakReplicationFragment *fragments10 = NULL;
    BreakReplicationFragment *fragments11 = NULL;
    BreakReplicationFragment *fragments12 = NULL;
    size_t count10 = 0u;
    size_t count11 = 0u;
    size_t count12 = 0u;
    BreakReplicationReassemblyPool *pool;
    const BreakReplicationFragment *order[9];
    const BreakReplicationReassemblyResult expected_results[9] = {
        BREAK_REPLICATION_REASSEMBLY_INCOMPLETE,
        BREAK_REPLICATION_REASSEMBLY_INCOMPLETE,
        BREAK_REPLICATION_REASSEMBLY_INCOMPLETE,
        BREAK_REPLICATION_REASSEMBLY_INCOMPLETE,
        BREAK_REPLICATION_REASSEMBLY_INCOMPLETE,
        BREAK_REPLICATION_REASSEMBLY_INCOMPLETE,
        BREAK_REPLICATION_REASSEMBLY_COMPLETE,
        BREAK_REPLICATION_REASSEMBLY_COMPLETE,
        BREAK_REPLICATION_REASSEMBLY_COMPLETE
    };
    const uint64_t expected_completed[9] = {0u, 0u, 0u, 0u, 0u, 0u, 12u, 10u, 11u};
    const size_t expected_pending[9] = {1u, 2u, 3u, 3u, 3u, 3u, 2u, 1u, 0u};
    const uint8_t *expected_payloads[9] = {
        NULL, NULL, NULL, NULL, NULL, NULL, payload12, payload10, payload11
    };
    const size_t expected_sizes[9] = {
        0u, 0u, 0u, 0u, 0u, 0u,
        sizeof(payload12) - 1u, sizeof(payload10) - 1u, sizeof(payload11) - 1u
    };
    size_t i;

    ASSERT_EQ(break_replication_fragment_payload(
                  10u, 7u, payload10, sizeof(payload10) - 1u, 4u,
                  &fragments10, &count10),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(break_replication_fragment_payload(
                  11u, 7u, payload11, sizeof(payload11) - 1u, 4u,
                  &fragments11, &count11),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(break_replication_fragment_payload(
                  12u, 7u, payload12, sizeof(payload12) - 1u, 4u,
                  &fragments12, &count12),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(count10, 3u);
    ASSERT_EQ(count11, 3u);
    ASSERT_EQ(count12, 3u);
    pool = break_replication_reassembly_pool_create(7u, 3u, 128u);
    ASSERT_NOT_NULL(pool);

    order[0] = &fragments10[0];
    order[1] = &fragments11[0];
    order[2] = &fragments12[0];
    order[3] = &fragments11[1];
    order[4] = &fragments10[1];
    order[5] = &fragments12[1];
    order[6] = &fragments12[2];
    order[7] = &fragments10[2];
    order[8] = &fragments11[2];
    for (i = 0u; i < 9u; ++i) {
        uint64_t completed_id = UINT64_MAX;
        uint8_t *assembled = NULL;
        size_t assembled_size = 0u;
        ASSERT_EQ(break_replication_reassembly_pool_push_at(
                      pool, order[i], 100u + i, &completed_id, &assembled, &assembled_size),
                  expected_results[i]);
        ASSERT_EQ(completed_id, expected_completed[i]);
        ASSERT_EQ(assembled_size, expected_sizes[i]);
        if (expected_results[i] == BREAK_REPLICATION_REASSEMBLY_COMPLETE) {
            ASSERT_NOT_NULL(assembled);
            ASSERT_TRUE(memcmp(assembled, expected_payloads[i], expected_sizes[i]) == 0);
            break_replication_reassembly_free(assembled);
        } else {
            ASSERT_EQ(assembled, NULL);
        }
        ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool),
                  expected_pending[i]);
    }
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 0u);
    break_replication_reassembly_pool_destroy(pool);
    break_replication_fragments_free(fragments12, count12);
    break_replication_fragments_free(fragments11, count11);
    break_replication_fragments_free(fragments10, count10);
}

TEST(reassembly_pool_capacity_rejection_preserves_active_streams)
{
    const uint8_t payload10[] = {'1', '0', 'x', 'y'};
    const uint8_t payload11[] = {'1', '1', 'x', 'y'};
    const uint8_t payload12[] = {'1', '2', 'x', 'y'};
    BreakReplicationFragment *fragments10 = NULL;
    BreakReplicationFragment *fragments11 = NULL;
    BreakReplicationFragment *fragments12 = NULL;
    size_t count10 = 0u;
    size_t count11 = 0u;
    size_t count12 = 0u;
    BreakReplicationReassemblyPool *pool;
    uint64_t completed_id = 0u;
    uint8_t sentinel = 0u;
    uint8_t *assembled = NULL;
    size_t assembled_size = 0u;

    ASSERT_EQ(break_replication_fragment_payload(
                  10u, 7u, payload10, sizeof(payload10), 2u,
                  &fragments10, &count10),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(break_replication_fragment_payload(
                  11u, 7u, payload11, sizeof(payload11), 2u,
                  &fragments11, &count11),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(break_replication_fragment_payload(
                  12u, 7u, payload12, sizeof(payload12), 2u,
                  &fragments12, &count12),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(count10, 2u);
    ASSERT_EQ(count11, 2u);
    ASSERT_EQ(count12, 2u);
    pool = break_replication_reassembly_pool_create(7u, 2u, 64u);
    ASSERT_NOT_NULL(pool);

    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments10[0], 100u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(completed_id, 0u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 1u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 2u);
    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments11[0], 101u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(completed_id, 0u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 2u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 4u);

    completed_id = UINT64_MAX;
    assembled = &sentinel;
    assembled_size = 99u;
    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments12[0], 102u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_OVER_LIMIT);
    ASSERT_EQ(completed_id, 0u);
    ASSERT_EQ(assembled, NULL);
    ASSERT_EQ(assembled_size, 0u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 2u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 4u);

    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments10[1], 103u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_COMPLETE);
    ASSERT_EQ(completed_id, 10u);
    ASSERT_EQ(assembled_size, sizeof(payload10));
    ASSERT_NOT_NULL(assembled);
    ASSERT_TRUE(memcmp(assembled, payload10, sizeof(payload10)) == 0);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 1u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 2u);
    break_replication_reassembly_free(assembled);
    assembled = NULL;
    assembled_size = 0u;

    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments12[0], 104u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(completed_id, 0u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 2u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 4u);
    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments12[1], 105u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_COMPLETE);
    ASSERT_EQ(completed_id, 12u);
    ASSERT_EQ(assembled_size, sizeof(payload12));
    ASSERT_NOT_NULL(assembled);
    ASSERT_TRUE(memcmp(assembled, payload12, sizeof(payload12)) == 0);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 1u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 2u);
    break_replication_reassembly_free(assembled);
    assembled = NULL;
    assembled_size = 0u;

    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments12[0], 106u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(completed_id, 0u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 2u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 4u);

    completed_id = UINT64_MAX;
    assembled = &sentinel;
    assembled_size = 99u;
    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments10[0], 107u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_CONFLICT);
    ASSERT_EQ(completed_id, 0u);
    ASSERT_EQ(assembled, NULL);
    ASSERT_EQ(assembled_size, 0u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 2u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 4u);

    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments11[1], 108u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_COMPLETE);
    ASSERT_EQ(completed_id, 11u);
    ASSERT_EQ(assembled_size, sizeof(payload11));
    ASSERT_NOT_NULL(assembled);
    ASSERT_TRUE(memcmp(assembled, payload11, sizeof(payload11)) == 0);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 1u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 2u);
    break_replication_reassembly_free(assembled);
    assembled = NULL;
    assembled_size = 0u;

    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments12[1], 109u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_COMPLETE);
    ASSERT_EQ(completed_id, 12u);
    ASSERT_EQ(assembled_size, sizeof(payload12));
    ASSERT_NOT_NULL(assembled);
    ASSERT_TRUE(memcmp(assembled, payload12, sizeof(payload12)) == 0);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 0u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 0u);
    break_replication_reassembly_free(assembled);

    break_replication_reassembly_pool_destroy(pool);
    break_replication_fragments_free(fragments12, count12);
    break_replication_fragments_free(fragments11, count11);
    break_replication_fragments_free(fragments10, count10);
}

TEST(reassembly_pool_enforces_one_shared_payload_budget)
{
    const uint8_t payload20[] = {'2', '0', 'a', 'b', 'c', 'd', 'e', 'f'};
    const uint8_t payload21[] = {'2', '1'};
    const uint8_t payload22[] = {'2', '2', 'z', '!'};
    BreakReplicationFragment *fragments20 = NULL;
    BreakReplicationFragment *fragments21 = NULL;
    BreakReplicationFragment *fragments22 = NULL;
    size_t count20 = 0u;
    size_t count21 = 0u;
    size_t count22 = 0u;
    BreakReplicationReassemblyPool *pool;
    BreakReplicationFragment conflict;
    uint64_t completed_id = 0u;
    uint8_t sentinel = 0u;
    uint8_t *assembled = NULL;
    size_t assembled_size = 0u;

    ASSERT_EQ(break_replication_fragment_payload(
                  20u, 7u, payload20, sizeof(payload20), 4u,
                  &fragments20, &count20),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(break_replication_fragment_payload(
                  21u, 7u, payload21, sizeof(payload21), 1u,
                  &fragments21, &count21),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(break_replication_fragment_payload(
                  22u, 7u, payload22, sizeof(payload22), 4u,
                  &fragments22, &count22),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(count20, 2u);
    ASSERT_EQ(count21, 2u);
    ASSERT_EQ(count22, 1u);
    pool = break_replication_reassembly_pool_create(7u, 3u, 8u);
    ASSERT_NOT_NULL(pool);

    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments20[0], 200u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 1u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 4u);
    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments21[0], 201u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 2u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 5u);

    completed_id = UINT64_MAX;
    assembled = &sentinel;
    assembled_size = 99u;
    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments20[0], 202u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_DUPLICATE);
    ASSERT_EQ(completed_id, 0u);
    ASSERT_EQ(assembled, NULL);
    ASSERT_EQ(assembled_size, 0u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 2u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 5u);

    conflict = fragments20[1];
    conflict.fragment_count++;
    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &conflict, 203u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_CONFLICT);
    ASSERT_EQ(completed_id, 0u);
    ASSERT_EQ(assembled, NULL);
    ASSERT_EQ(assembled_size, 0u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 5u);

    conflict = fragments20[0];
    conflict.data = fragments20[1].data;
    conflict.checksum = fragments20[1].checksum;
    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &conflict, 204u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_CONFLICT);
    ASSERT_EQ(completed_id, 0u);
    ASSERT_EQ(assembled, NULL);
    ASSERT_EQ(assembled_size, 0u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 2u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 5u);

    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments22[0], 205u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_OVER_LIMIT);
    ASSERT_EQ(completed_id, 0u);
    ASSERT_EQ(assembled, NULL);
    ASSERT_EQ(assembled_size, 0u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 2u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 5u);

    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments20[1], 206u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_OVER_LIMIT);
    ASSERT_EQ(completed_id, 0u);
    ASSERT_EQ(assembled, NULL);
    ASSERT_EQ(assembled_size, 0u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 2u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 5u);

    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments21[1], 207u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_COMPLETE);
    ASSERT_EQ(completed_id, 21u);
    ASSERT_EQ(assembled_size, sizeof(payload21));
    ASSERT_NOT_NULL(assembled);
    ASSERT_TRUE(memcmp(assembled, payload21, sizeof(payload21)) == 0);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 1u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 4u);
    break_replication_reassembly_free(assembled);
    assembled = NULL;
    assembled_size = 0u;

    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments22[0], 208u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_COMPLETE);
    ASSERT_EQ(completed_id, 22u);
    ASSERT_EQ(assembled_size, sizeof(payload22));
    ASSERT_NOT_NULL(assembled);
    ASSERT_TRUE(memcmp(assembled, payload22, sizeof(payload22)) == 0);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 1u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 4u);
    break_replication_reassembly_free(assembled);
    assembled = NULL;
    assembled_size = 0u;

    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments20[1], 209u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_COMPLETE);
    ASSERT_EQ(completed_id, 20u);
    ASSERT_EQ(assembled_size, sizeof(payload20));
    ASSERT_NOT_NULL(assembled);
    ASSERT_TRUE(memcmp(assembled, payload20, sizeof(payload20)) == 0);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 0u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 0u);
    break_replication_reassembly_free(assembled);

    break_replication_reassembly_pool_destroy(pool);
    break_replication_fragments_free(fragments22, count22);
    break_replication_fragments_free(fragments21, count21);
    break_replication_fragments_free(fragments20, count20);
}

TEST_MAIN_BEGIN()
    RUN_TEST(fragment_round_trip_reordered_and_checksum);
    RUN_TEST(fragment_rejects_duplicates_conflicts_loss_and_base_mismatch);
    RUN_TEST(fragment_validation_rejects_invalid_shape_and_checksum);
    RUN_TEST(fragment_boundary_rejects_empty_oversized_and_transport_limit);
    RUN_TEST(reassembler_rejects_oversized_fragment_and_reset_is_recoverable);
    RUN_TEST(fragment_and_reassembler_reject_payload_budget);
    RUN_TEST(reassembler_repeated_fragment_after_complete_starts_new_state);
    RUN_TEST(fragment_into_caller_storage_matches_allocating_api_and_reassembles);
    RUN_TEST(fragment_into_rejects_short_capacity_before_writing);
    RUN_TEST(reassembler_newer_delta_supersedes_incomplete_and_rejects_old);
    RUN_TEST(reassembler_completed_high_water_rejects_older_restart);
    RUN_TEST(reassembler_failed_supersession_preserves_old_stream);
    RUN_TEST(reassembler_expires_an_idle_incomplete_stream);
    RUN_TEST(timed_push_matches_untimed_push);
    RUN_TEST(rejected_fragments_do_not_refresh_and_plain_push_stays_untimed);
    RUN_TEST(reassembly_pool_validates_configuration_and_null_calls);
    RUN_TEST(reassembly_pool_reassembles_three_interleaved_deltas);
    RUN_TEST(reassembly_pool_capacity_rejection_preserves_active_streams);
    RUN_TEST(reassembly_pool_enforces_one_shared_payload_budget);
TEST_MAIN_END()
