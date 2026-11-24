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
    const size_t expected_pending_bytes[9] = {4u, 8u, 12u, 16u, 20u, 24u, 16u, 8u, 0u};
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
        ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool),
                  expected_pending_bytes[i]);
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

    completed_id = UINT64_MAX;
    assembled = &sentinel;
    assembled_size = 99u;
    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments11[0], 109u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_CONFLICT);
    ASSERT_EQ(completed_id, 0u);
    ASSERT_EQ(assembled, NULL);
    ASSERT_EQ(assembled_size, 0u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 1u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 2u);

    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments12[1], 110u, &completed_id, &assembled, &assembled_size),
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

TEST(reassembly_pool_expires_each_stream_and_keeps_retirement_high_water)
{
    const uint8_t payload30[] = {'3', '0', 'a', 'b'};
    const uint8_t payload31[] = {'3', '1', 'a', 'b'};
    const uint8_t payload32[] = {'3', '2', 'a', 'b'};
    const uint8_t payload33[] = {'3', '3', 'a', 'b'};
    const uint8_t payload34[] = {'3', '4', 'a', 'b'};
    BreakReplicationFragment *fragments30 = NULL;
    BreakReplicationFragment *fragments31 = NULL;
    BreakReplicationFragment *fragments32 = NULL;
    BreakReplicationFragment *fragments33 = NULL;
    BreakReplicationFragment *fragments34 = NULL;
    size_t count30 = 0u;
    size_t count31 = 0u;
    size_t count32 = 0u;
    size_t count33 = 0u;
    size_t count34 = 0u;
    BreakReplicationReassemblyPool *pool;
    BreakReplicationFragment changed;
    uint64_t completed_id = 0u;
    uint8_t sentinel = 0u;
    uint8_t *assembled = NULL;
    size_t assembled_size = 0u;

    ASSERT_EQ(break_replication_fragment_payload(
                  30u, 7u, payload30, sizeof(payload30), 2u,
                  &fragments30, &count30),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(break_replication_fragment_payload(
                  31u, 7u, payload31, sizeof(payload31), 2u,
                  &fragments31, &count31),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(break_replication_fragment_payload(
                  32u, 7u, payload32, sizeof(payload32), 2u,
                  &fragments32, &count32),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(break_replication_fragment_payload(
                  33u, 7u, payload33, sizeof(payload33), 2u,
                  &fragments33, &count33),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(break_replication_fragment_payload(
                  34u, 7u, payload34, sizeof(payload34), 2u,
                  &fragments34, &count34),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(count30, 2u);
    ASSERT_EQ(count31, 2u);
    ASSERT_EQ(count32, 2u);
    ASSERT_EQ(count33, 2u);
    ASSERT_EQ(count34, 2u);
    pool = break_replication_reassembly_pool_create(7u, 3u, 64u);
    ASSERT_NOT_NULL(pool);

    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments30[0], 100u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments31[0], 106u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments32[0], 112u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 3u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 6u);

    ASSERT_EQ(break_replication_reassembly_pool_expire(pool, 115u, 10u), 1u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 2u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 4u);

    changed = fragments30[0];
    changed.delta_id = 29u;
    completed_id = UINT64_MAX;
    assembled = &sentinel;
    assembled_size = 99u;
    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &changed, 115u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_CONFLICT);
    ASSERT_EQ(completed_id, 0u);
    ASSERT_EQ(assembled, NULL);
    ASSERT_EQ(assembled_size, 0u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 2u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 4u);

    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments30[1], 116u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 3u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 6u);

    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments30[1], 130u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_DUPLICATE);
    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments32[0], 130u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_DUPLICATE);
    ASSERT_EQ(break_replication_reassembly_pool_expire(pool, 130u, 10u), 1u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 2u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 4u);

    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments30[0], 131u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_COMPLETE);
    ASSERT_EQ(completed_id, 30u);
    ASSERT_EQ(assembled_size, sizeof(payload30));
    ASSERT_NOT_NULL(assembled);
    ASSERT_TRUE(memcmp(assembled, payload30, sizeof(payload30)) == 0);
    break_replication_reassembly_free(assembled);
    assembled = NULL;
    assembled_size = 0u;
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 1u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 2u);

    changed = fragments32[0];
    changed.checksum++;
    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &changed, 132u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_CHECKSUM_MISMATCH);
    changed = fragments32[0];
    changed.base_id++;
    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &changed, 133u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_BASE_MISMATCH);
    changed = fragments32[0];
    changed.data = fragments32[1].data;
    changed.checksum = fragments32[1].checksum;
    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &changed, 134u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_CONFLICT);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 1u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 2u);

    ASSERT_EQ(break_replication_reassembly_pool_expire(pool, 50u, 10u), 0u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 1u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 2u);
    ASSERT_EQ(break_replication_reassembly_pool_expire(pool, 140u, 10u), 1u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 0u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 0u);

    completed_id = UINT64_MAX;
    assembled = &sentinel;
    assembled_size = 99u;
    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments31[0], 141u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_CONFLICT);
    ASSERT_EQ(completed_id, 0u);
    ASSERT_EQ(assembled, NULL);
    ASSERT_EQ(assembled_size, 0u);

    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments32[1], 200u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments33[0], 201u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments34[0], 202u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 3u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 6u);
    ASSERT_EQ(break_replication_reassembly_pool_expire(pool, 202u, 0u), 3u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 0u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 0u);

    break_replication_reassembly_pool_destroy(pool);
    break_replication_fragments_free(fragments34, count34);
    break_replication_fragments_free(fragments33, count33);
    break_replication_fragments_free(fragments32, count32);
    break_replication_fragments_free(fragments31, count31);
    break_replication_fragments_free(fragments30, count30);
}

TEST(reassembly_pool_reset_matches_a_fresh_pool)
{
    const uint8_t payload39[] = {'3', '9', 'a', 'b'};
    const uint8_t payload40[] = {'4', '0', 'a', 'b'};
    const uint8_t payload41[] = {'4', '1', 'a', 'b'};
    const uint8_t payload42[] = {'4', '2', 'a', 'b'};
    BreakReplicationFragment *fragments39 = NULL;
    BreakReplicationFragment *fragments40 = NULL;
    BreakReplicationFragment *fragments41 = NULL;
    BreakReplicationFragment *fragments42 = NULL;
    size_t count39 = 0u;
    size_t count40 = 0u;
    size_t count41 = 0u;
    size_t count42 = 0u;
    BreakReplicationReassemblyPool *reset_pool;
    BreakReplicationReassemblyPool *fresh_pool;
    const BreakReplicationFragment *order[6];
    const BreakReplicationReassemblyResult expected_results[6] = {
        BREAK_REPLICATION_REASSEMBLY_INCOMPLETE,
        BREAK_REPLICATION_REASSEMBLY_INCOMPLETE,
        BREAK_REPLICATION_REASSEMBLY_INCOMPLETE,
        BREAK_REPLICATION_REASSEMBLY_COMPLETE,
        BREAK_REPLICATION_REASSEMBLY_COMPLETE,
        BREAK_REPLICATION_REASSEMBLY_COMPLETE
    };
    const uint64_t expected_completed[6] = {0u, 0u, 0u, 39u, 42u, 41u};
    const size_t expected_pending[6] = {1u, 2u, 3u, 2u, 1u, 0u};
    const size_t expected_bytes[6] = {2u, 4u, 6u, 4u, 2u, 0u};
    const uint8_t *expected_payloads[6] = {
        NULL, NULL, NULL, payload39, payload42, payload41
    };
    uint64_t completed_id = 0u;
    uint8_t *assembled = NULL;
    size_t assembled_size = 0u;
    size_t i;

    ASSERT_EQ(break_replication_fragment_payload(
                  39u, 7u, payload39, sizeof(payload39), 2u,
                  &fragments39, &count39),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(break_replication_fragment_payload(
                  40u, 7u, payload40, sizeof(payload40), 2u,
                  &fragments40, &count40),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(break_replication_fragment_payload(
                  41u, 7u, payload41, sizeof(payload41), 2u,
                  &fragments41, &count41),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(break_replication_fragment_payload(
                  42u, 7u, payload42, sizeof(payload42), 2u,
                  &fragments42, &count42),
              BREAK_REPLICATION_FRAGMENT_OK);
    reset_pool = break_replication_reassembly_pool_create(7u, 3u, 8u);
    fresh_pool = break_replication_reassembly_pool_create(7u, 3u, 8u);
    ASSERT_NOT_NULL(reset_pool);
    ASSERT_NOT_NULL(fresh_pool);

    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  reset_pool, &fragments40[0], 10u,
                  &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  reset_pool, &fragments40[1], 11u,
                  &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_COMPLETE);
    ASSERT_EQ(completed_id, 40u);
    ASSERT_EQ(assembled_size, sizeof(payload40));
    ASSERT_NOT_NULL(assembled);
    ASSERT_TRUE(memcmp(assembled, payload40, sizeof(payload40)) == 0);
    break_replication_reassembly_free(assembled);
    assembled = NULL;
    assembled_size = 0u;
    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  reset_pool, &fragments41[0], 12u,
                  &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  reset_pool, &fragments42[0], 13u,
                  &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(reset_pool), 2u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(reset_pool), 4u);
    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  reset_pool, &fragments39[0], 14u,
                  &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_CONFLICT);

    break_replication_reassembly_pool_reset(reset_pool);
    break_replication_reassembly_pool_reset(NULL);
    ASSERT_EQ(break_replication_reassembly_pool_expire(NULL, 20u, 0u), 0u);
    ASSERT_EQ(break_replication_reassembly_pool_expire(reset_pool, 20u, 0u), 0u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(reset_pool), 0u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(reset_pool), 0u);

    order[0] = &fragments39[0];
    order[1] = &fragments42[1];
    order[2] = &fragments41[1];
    order[3] = &fragments39[1];
    order[4] = &fragments42[0];
    order[5] = &fragments41[0];
    for (i = 0u; i < 6u; ++i) {
        uint64_t reset_completed = UINT64_MAX;
        uint64_t fresh_completed = UINT64_MAX;
        uint8_t *reset_assembled = NULL;
        uint8_t *fresh_assembled = NULL;
        size_t reset_size = 0u;
        size_t fresh_size = 0u;
        BreakReplicationReassemblyResult reset_result;
        BreakReplicationReassemblyResult fresh_result;

        reset_result = break_replication_reassembly_pool_push_at(
            reset_pool, order[i], 100u + i,
            &reset_completed, &reset_assembled, &reset_size);
        fresh_result = break_replication_reassembly_pool_push_at(
            fresh_pool, order[i], 100u + i,
            &fresh_completed, &fresh_assembled, &fresh_size);
        ASSERT_EQ(reset_result, expected_results[i]);
        ASSERT_EQ(fresh_result, expected_results[i]);
        ASSERT_EQ(reset_result, fresh_result);
        ASSERT_EQ(reset_completed, expected_completed[i]);
        ASSERT_EQ(fresh_completed, expected_completed[i]);
        ASSERT_EQ(reset_size, fresh_size);
        if (expected_results[i] == BREAK_REPLICATION_REASSEMBLY_COMPLETE) {
            ASSERT_EQ(reset_size, sizeof(payload39));
            ASSERT_NOT_NULL(reset_assembled);
            ASSERT_NOT_NULL(fresh_assembled);
            ASSERT_TRUE(memcmp(reset_assembled, expected_payloads[i], reset_size) == 0);
            ASSERT_TRUE(memcmp(reset_assembled, fresh_assembled, reset_size) == 0);
        } else {
            ASSERT_EQ(reset_completed, 0u);
            ASSERT_EQ(fresh_completed, 0u);
            ASSERT_EQ(reset_assembled, NULL);
            ASSERT_EQ(fresh_assembled, NULL);
            ASSERT_EQ(reset_size, 0u);
            ASSERT_EQ(fresh_size, 0u);
        }
        ASSERT_EQ(break_replication_reassembly_pool_pending_streams(reset_pool),
                  expected_pending[i]);
        ASSERT_EQ(break_replication_reassembly_pool_pending_streams(fresh_pool),
                  expected_pending[i]);
        ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(reset_pool),
                  expected_bytes[i]);
        ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(fresh_pool),
                  expected_bytes[i]);
        break_replication_reassembly_free(reset_assembled);
        break_replication_reassembly_free(fresh_assembled);
    }

    break_replication_reassembly_pool_destroy(fresh_pool);
    break_replication_reassembly_pool_destroy(reset_pool);
    break_replication_fragments_free(fragments42, count42);
    break_replication_fragments_free(fragments41, count41);
    break_replication_fragments_free(fragments40, count40);
    break_replication_fragments_free(fragments39, count39);
}

TEST(reassembly_pool_destroy_releases_pending_streams)
{
    const uint8_t payload50[] = {'5', '0', 'a', 'b'};
    const uint8_t payload51[] = {'5', '1', 'a', 'b'};
    BreakReplicationFragment *fragments50 = NULL;
    BreakReplicationFragment *fragments51 = NULL;
    size_t count50 = 0u;
    size_t count51 = 0u;
    BreakReplicationReassemblyPool *pool;

    ASSERT_EQ(break_replication_fragment_payload(
                  50u, 7u, payload50, sizeof(payload50), 2u,
                  &fragments50, &count50),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(break_replication_fragment_payload(
                  51u, 7u, payload51, sizeof(payload51), 2u,
                  &fragments51, &count51),
              BREAK_REPLICATION_FRAGMENT_OK);
    pool = break_replication_reassembly_pool_create(7u, 2u, 8u);
    ASSERT_NOT_NULL(pool);
    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments50[0], 100u, NULL, NULL, NULL),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments51[0], 101u, NULL, NULL, NULL),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 2u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 4u);
    break_replication_reassembly_pool_destroy(pool);
    break_replication_fragments_free(fragments51, count51);
    break_replication_fragments_free(fragments50, count50);
}

TEST(reassembly_pool_expire_releases_shared_budget_for_retry)
{
    const uint8_t payload59[] = {'5', '9', 'a', 'b'};
    const uint8_t payload60[] = {'6', '0', 'a', 'b', 'c', 'd', 'e', 'f'};
    const uint8_t payload61[] = {'6', '1', 'a', 'b'};
    BreakReplicationFragment *fragments59 = NULL;
    BreakReplicationFragment *fragments60 = NULL;
    BreakReplicationFragment *fragments61 = NULL;
    size_t count59 = 0u;
    size_t count60 = 0u;
    size_t count61 = 0u;
    BreakReplicationReassemblyPool *pool;
    BreakReplicationFragment rejected;
    uint64_t completed_id = 0u;
    uint8_t sentinel = 0u;
    uint8_t *assembled = NULL;
    size_t assembled_size = 0u;

    ASSERT_EQ(break_replication_fragment_payload(
                  59u, 7u, payload59, sizeof(payload59), 2u,
                  &fragments59, &count59),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(break_replication_fragment_payload(
                  60u, 7u, payload60, sizeof(payload60), 4u,
                  &fragments60, &count60),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(break_replication_fragment_payload(
                  61u, 7u, payload61, sizeof(payload61), 4u,
                  &fragments61, &count61),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(count59, 2u);
    ASSERT_EQ(count60, 2u);
    ASSERT_EQ(count61, 1u);
    pool = break_replication_reassembly_pool_create(7u, 3u, 8u);
    ASSERT_NOT_NULL(pool);

    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments59[0], 100u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 2u);
    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments60[0], 101u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 2u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 6u);

    completed_id = UINT64_MAX;
    assembled = &sentinel;
    assembled_size = 99u;
    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments61[0], 102u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_OVER_LIMIT);
    ASSERT_EQ(completed_id, 0u);
    ASSERT_EQ(assembled, NULL);
    ASSERT_EQ(assembled_size, 0u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 2u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 6u);

    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments59[0], 105u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_DUPLICATE);
    ASSERT_EQ(break_replication_reassembly_pool_expire(pool, 111u, 10u), 1u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 1u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 2u);

    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments61[0], 112u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_COMPLETE);
    ASSERT_EQ(completed_id, 61u);
    ASSERT_EQ(assembled_size, sizeof(payload61));
    ASSERT_NOT_NULL(assembled);
    ASSERT_TRUE(memcmp(assembled, payload61, sizeof(payload61)) == 0);
    break_replication_reassembly_free(assembled);
    assembled = NULL;
    assembled_size = 0u;
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 1u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 2u);

    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments59[1], 113u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_COMPLETE);
    ASSERT_EQ(completed_id, 59u);
    ASSERT_EQ(assembled_size, sizeof(payload59));
    ASSERT_NOT_NULL(assembled);
    ASSERT_TRUE(memcmp(assembled, payload59, sizeof(payload59)) == 0);
    break_replication_reassembly_free(assembled);
    assembled = NULL;
    assembled_size = 0u;
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 0u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 0u);

    rejected = fragments60[0];
    completed_id = UINT64_MAX;
    assembled = &sentinel;
    assembled_size = 99u;
    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &rejected, 114u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_CONFLICT);
    ASSERT_EQ(completed_id, 0u);
    ASSERT_EQ(assembled, NULL);
    ASSERT_EQ(assembled_size, 0u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 0u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 0u);

    break_replication_reassembly_pool_destroy(pool);
    break_replication_fragments_free(fragments61, count61);
    break_replication_fragments_free(fragments60, count60);
    break_replication_fragments_free(fragments59, count59);
}

TEST(reassembly_pool_complete_with_null_outputs_discards_and_recycles)
{
    const uint8_t payload70[] = {'7', '0', 'a', 'b'};
    const uint8_t payload71[] = {'7', '1', 'a', 'b'};
    BreakReplicationFragment *fragments70 = NULL;
    BreakReplicationFragment *fragments71 = NULL;
    size_t count70 = 0u;
    size_t count71 = 0u;
    BreakReplicationReassemblyPool *pool;
    BreakReplicationFragment older;

    ASSERT_EQ(break_replication_fragment_payload(
                  70u, 7u, payload70, sizeof(payload70), 4u,
                  &fragments70, &count70),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(break_replication_fragment_payload(
                  71u, 7u, payload71, sizeof(payload71), 4u,
                  &fragments71, &count71),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(count70, 1u);
    ASSERT_EQ(count71, 1u);
    pool = break_replication_reassembly_pool_create(7u, 1u, 8u);
    ASSERT_NOT_NULL(pool);

    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments70[0], 100u, NULL, NULL, NULL),
              BREAK_REPLICATION_REASSEMBLY_COMPLETE);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 0u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 0u);

    older = fragments70[0];
    older.delta_id = 69u;
    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &older, 101u, NULL, NULL, NULL),
              BREAK_REPLICATION_REASSEMBLY_CONFLICT);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 0u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 0u);

    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments71[0], 102u, NULL, NULL, NULL),
              BREAK_REPLICATION_REASSEMBLY_COMPLETE);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 0u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 0u);

    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments70[0], 103u, NULL, NULL, NULL),
              BREAK_REPLICATION_REASSEMBLY_CONFLICT);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 0u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 0u);

    break_replication_reassembly_pool_destroy(pool);
    break_replication_fragments_free(fragments71, count71);
    break_replication_fragments_free(fragments70, count70);
}

TEST(reassembly_pool_expiry_schedule_honors_interval_and_activity)
{
    const uint8_t payload[] = {'a', 'b', 'c', 'd'};
    BreakReplicationFragment *fragments = NULL;
    size_t count = 0u;
    BreakReplicationReassemblyPool *pool;
    uint64_t completed_id = 0u;
    uint8_t *assembled = NULL;
    size_t assembled_size = 0u;

    ASSERT_EQ(break_replication_fragment_payload(
                  1u, 7u, payload, sizeof(payload), 2u, &fragments, &count),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(count, 2u);
    pool = break_replication_reassembly_pool_create(7u, 2u, 64u);
    ASSERT_NOT_NULL(pool);
    break_replication_reassembly_pool_set_expiry_schedule(pool, 10u, 5u);

    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments[0], 100u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments[0], 104u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_DUPLICATE);
    ASSERT_EQ(break_replication_reassembly_pool_tick(pool, 109u), 0u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 1u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 2u);
    ASSERT_EQ(break_replication_reassembly_pool_tick(pool, 110u), 1u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 0u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 0u);

    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments[0], 111u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(break_replication_reassembly_pool_expire(pool, 115u, 0u), 1u);
    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments[0], 116u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(break_replication_reassembly_pool_tick(pool, 120u), 0u);
    ASSERT_EQ(break_replication_reassembly_pool_tick(pool, 125u), 0u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 1u);

    break_replication_reassembly_pool_destroy(pool);
    break_replication_fragments_free(fragments, count);
}

TEST(reassembly_pool_expiry_schedule_runs_before_admission_and_survives_reset)
{
    const uint8_t payload10[] = {'1', '0', 'a', 'b'};
    const uint8_t payload11[] = {'1', '1'};
    BreakReplicationFragment *fragments10 = NULL;
    BreakReplicationFragment *fragments11 = NULL;
    size_t count10 = 0u;
    size_t count11 = 0u;
    BreakReplicationFragment delta12;
    BreakReplicationReassemblyPool *pool;
    uint64_t completed_id = 0u;
    uint8_t *assembled = NULL;
    size_t assembled_size = 0u;

    ASSERT_EQ(break_replication_fragment_payload(
                  10u, 7u, payload10, sizeof(payload10), 2u, &fragments10, &count10),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(break_replication_fragment_payload(
                  11u, 7u, payload11, sizeof(payload11), sizeof(payload11),
                  &fragments11, &count11),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(count10, 2u);
    ASSERT_EQ(count11, 1u);
    delta12 = fragments10[0];
    delta12.delta_id = 12u;
    pool = break_replication_reassembly_pool_create(7u, 1u, 64u);
    ASSERT_NOT_NULL(pool);
    break_replication_reassembly_pool_set_expiry_schedule(pool, 10u, 5u);

    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments10[0], 100u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments11[0], 105u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_OVER_LIMIT);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 1u);
    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments11[0], 110u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_COMPLETE);
    ASSERT_EQ(completed_id, 11u);
    ASSERT_EQ(assembled_size, sizeof(payload11));
    ASSERT_NOT_NULL(assembled);
    ASSERT_TRUE(memcmp(assembled, payload11, sizeof(payload11)) == 0);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 0u);
    break_replication_reassembly_free(assembled);
    assembled = NULL;
    assembled_size = 0u;

    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &delta12, 111u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 1u);
    break_replication_reassembly_pool_reset(pool);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 0u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 0u);

    ASSERT_EQ(break_replication_reassembly_pool_tick(pool, 100u), 0u);
    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &delta12, 100u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(break_replication_reassembly_pool_tick(pool, 110u), 1u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 0u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 0u);

    break_replication_reassembly_pool_destroy(pool);
    break_replication_fragments_free(fragments11, count11);
    break_replication_fragments_free(fragments10, count10);
}

TEST(reassembly_pool_expiry_schedule_zero_disable_and_reenable)
{
    const uint8_t payload[] = {'z', 'e', 'r', 'o'};
    BreakReplicationFragment *fragments = NULL;
    size_t count = 0u;
    BreakReplicationReassemblyPool *pool;
    uint64_t completed_id = 0u;
    uint8_t *assembled = NULL;
    size_t assembled_size = 0u;

    ASSERT_EQ(break_replication_fragment_payload(
                  20u, 7u, payload, sizeof(payload), 2u, &fragments, &count),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(count, 2u);
    pool = break_replication_reassembly_pool_create(7u, 1u, 64u);
    ASSERT_NOT_NULL(pool);
    break_replication_reassembly_pool_set_expiry_schedule(NULL, 0u, 0u);
    break_replication_reassembly_pool_disable_expiry_schedule(NULL);
    ASSERT_EQ(break_replication_reassembly_pool_tick(NULL, 100u), 0u);

    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments[0], 10u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(break_replication_reassembly_pool_tick(pool, 1000u), 0u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 1u);
    break_replication_reassembly_pool_reset(pool);

    break_replication_reassembly_pool_set_expiry_schedule(pool, 0u, 0u);
    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments[0], 100u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(break_replication_reassembly_pool_tick(pool, 100u), 1u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 0u);

    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments[0], 100u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    break_replication_reassembly_pool_disable_expiry_schedule(pool);
    ASSERT_EQ(break_replication_reassembly_pool_tick(pool, 10000u), 0u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 1u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 2u);

    break_replication_reassembly_pool_set_expiry_schedule(pool, 100u, 5u);
    ASSERT_EQ(break_replication_reassembly_pool_tick(pool, 110u), 1u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 0u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 0u);

    break_replication_reassembly_pool_destroy(pool);
    break_replication_fragments_free(fragments, count);
}

TEST(reassembly_pool_expiry_schedule_clock_rollback_and_single_pass)
{
    const uint8_t payload[] = {'t', 'i', 'm', 'e'};
    BreakReplicationFragment *fragments = NULL;
    size_t count = 0u;
    BreakReplicationFragment second;
    BreakReplicationFragment third;
    BreakReplicationReassemblyPool *pool;
    uint64_t completed_id = 0u;
    uint8_t *assembled = NULL;
    size_t assembled_size = 0u;

    ASSERT_EQ(break_replication_fragment_payload(
                  30u, 7u, payload, sizeof(payload), 2u, &fragments, &count),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(count, 2u);
    second = fragments[0];
    second.delta_id = 31u;
    third = fragments[0];
    third.delta_id = 32u;
    pool = break_replication_reassembly_pool_create(7u, 4u, 64u);
    ASSERT_NOT_NULL(pool);
    break_replication_reassembly_pool_set_expiry_schedule(pool, 10u, 5u);

    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments[0], 100u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &second, 100u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(break_replication_reassembly_pool_tick(pool, 50u), 0u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 2u);
    ASSERT_EQ(break_replication_reassembly_pool_tick(pool, 109u), 0u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 2u);
    ASSERT_EQ(break_replication_reassembly_pool_tick(pool, 110u), 2u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 0u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 0u);

    break_replication_reassembly_pool_reset(pool);
    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments[0], 200u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &second, 200u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &fragments[0], 204u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_DUPLICATE);
    ASSERT_EQ(break_replication_reassembly_pool_tick(pool, 255u), 2u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 0u);
    ASSERT_EQ(break_replication_reassembly_pool_push_at(
                  pool, &third, 255u, &completed_id, &assembled, &assembled_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    ASSERT_EQ(break_replication_reassembly_pool_tick(pool, 260u), 0u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 1u);
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 2u);

    break_replication_reassembly_pool_destroy(pool);
    break_replication_fragments_free(fragments, count);
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
    RUN_TEST(reassembly_pool_expires_each_stream_and_keeps_retirement_high_water);
    RUN_TEST(reassembly_pool_reset_matches_a_fresh_pool);
    RUN_TEST(reassembly_pool_destroy_releases_pending_streams);
    RUN_TEST(reassembly_pool_expire_releases_shared_budget_for_retry);
    RUN_TEST(reassembly_pool_complete_with_null_outputs_discards_and_recycles);
    RUN_TEST(reassembly_pool_expiry_schedule_honors_interval_and_activity);
    RUN_TEST(reassembly_pool_expiry_schedule_runs_before_admission_and_survives_reset);
    RUN_TEST(reassembly_pool_expiry_schedule_zero_disable_and_reenable);
    RUN_TEST(reassembly_pool_expiry_schedule_clock_rollback_and_single_pass);
TEST_MAIN_END()
