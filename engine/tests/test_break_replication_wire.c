#include "test_framework.h"
#include <network/break_replication_wire.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static const uint8_t canonical_data[] = {0xaau, 0xbbu, 0xccu, 0xddu};
static const uint8_t canonical_wire[] = {
    0x42u, 0x52u, 0x46u, 0x47u, 0x01u, 0x00u, 0x28u, 0x00u,
    0x01u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x02u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x03u, 0x00u, 0x00u, 0x00u, 0x04u, 0x00u, 0x00u, 0x00u,
    0x44u, 0x33u, 0x22u, 0x11u, 0x04u, 0x00u, 0x00u, 0x00u,
    0xaau, 0xbbu, 0xccu, 0xddu
};

static bool bytes_are(const uint8_t *bytes, size_t size, uint8_t value)
{
    size_t i;
    for (i = 0u; i < size; ++i) {
        if (bytes[i] != value) return false;
    }
    return true;
}

static bool fragment_is_zero(const BreakReplicationFragment *fragment)
{
    BreakReplicationFragment zero;
    memset(&zero, 0, sizeof(zero));
    return memcmp(fragment, &zero, sizeof(zero)) == 0;
}

static void check_encode_rejection(const BreakReplicationFragment *fragment,
                                   BreakReplicationFragmentResult expected)
{
    uint8_t out[64];
    size_t size = 99u;
    memset(out, 0xa5, sizeof(out));
    ASSERT_EQ(break_replication_wire_encoded_size(fragment, &size), expected);
    ASSERT_EQ(size, 0u);
    size = 99u;
    ASSERT_EQ(break_replication_wire_encode(fragment, out, sizeof(out), &size), expected);
    ASSERT_EQ(size, 0u);
    ASSERT_TRUE(bytes_are(out, sizeof(out), 0xa5u));
}

static void check_decode_rejection(const void *data, size_t size,
                                   BreakReplicationFragmentResult expected)
{
    BreakReplicationFragment fragment;
    memset(&fragment, 0xa5, sizeof(fragment));
    ASSERT_EQ(break_replication_wire_decode(data, size, &fragment), expected);
    ASSERT_TRUE(fragment_is_zero(&fragment));
}

TEST(wire_canonical_layout_and_borrowed_decode)
{
    BreakReplicationFragment fragment = {
        1u, 2u, 3u, 4u, 0x11223344u, canonical_data, sizeof(canonical_data)
    };
    BreakReplicationFragment decoded;
    uint8_t out[sizeof(canonical_wire)];
    size_t size = 99u;

    ASSERT_EQ(break_replication_wire_encoded_size(&fragment, &size),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(size, sizeof(canonical_wire));
    size = 99u;
    memset(out, 0xa5, sizeof(out));
    ASSERT_EQ(break_replication_wire_encode(&fragment, out, sizeof(out), &size),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(size, sizeof(canonical_wire));
    ASSERT_TRUE(memcmp(out, canonical_wire, sizeof(canonical_wire)) == 0);
    memset(&decoded, 0xa5, sizeof(decoded));
    ASSERT_EQ(break_replication_wire_decode(out, size, &decoded),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(decoded.delta_id, 1u);
    ASSERT_EQ(decoded.base_id, 2u);
    ASSERT_EQ(decoded.fragment_index, 3u);
    ASSERT_EQ(decoded.fragment_count, 4u);
    ASSERT_EQ(decoded.checksum, 0x11223344u);
    ASSERT_EQ(decoded.size, sizeof(canonical_data));
    ASSERT_EQ(decoded.data, out + BREAK_REPLICATION_WIRE_HEADER_SIZE);
    ASSERT_TRUE(memcmp(decoded.data, canonical_data, sizeof(canonical_data)) == 0);
}

TEST(wire_wide_delta_and_base_canonical_round_trip)
{
    static const uint8_t expected[] = {
        0x42u, 0x52u, 0x46u, 0x47u, 0x01u, 0x00u, 0x28u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x01u, 0x00u, 0x00u, 0x00u,
        0x88u, 0x77u, 0x66u, 0x55u, 0x44u, 0x33u, 0x22u, 0x11u,
        0x03u, 0x00u, 0x00u, 0x00u, 0x04u, 0x00u, 0x00u, 0x00u,
        0x44u, 0x33u, 0x22u, 0x11u, 0x04u, 0x00u, 0x00u, 0x00u,
        0xaau, 0xbbu, 0xccu, 0xddu
    };
    BreakReplicationFragment fragment = {
        UINT64_C(0x0000000100000000), UINT64_C(0x1122334455667788),
        3u, 4u, 0x11223344u, canonical_data, sizeof(canonical_data)
    };
    BreakReplicationFragment decoded;
    uint8_t out[sizeof(expected)];
    size_t size = 99u;

    ASSERT_EQ(break_replication_wire_encoded_size(&fragment, &size),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(size, sizeof(expected));
    size = 99u;
    ASSERT_EQ(break_replication_wire_encode(&fragment, out, sizeof(out), &size),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(size, sizeof(expected));
    ASSERT_TRUE(memcmp(out, expected, sizeof(expected)) == 0);
    ASSERT_EQ(break_replication_wire_decode(out, size, &decoded),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(decoded.delta_id, UINT64_C(0x0000000100000000));
    ASSERT_EQ(decoded.base_id, UINT64_C(0x1122334455667788));
    ASSERT_EQ(decoded.fragment_index, 3u);
    ASSERT_EQ(decoded.fragment_count, 4u);
    ASSERT_EQ(decoded.checksum, 0x11223344u);
    ASSERT_EQ(decoded.size, sizeof(canonical_data));
    ASSERT_EQ(decoded.data, out + BREAK_REPLICATION_WIRE_HEADER_SIZE);
}

TEST(wire_max_fragment_count_round_trip)
{
    uint8_t data = 0x5au;
    BreakReplicationFragment fragment = {
        1u, 2u, BREAK_REPLICATION_WIRE_MAX_FRAGMENT_COUNT - 1u,
        BREAK_REPLICATION_WIRE_MAX_FRAGMENT_COUNT, 3u, &data, 1u
    };
    BreakReplicationFragment decoded;
    uint8_t out[BREAK_REPLICATION_WIRE_HEADER_SIZE + 1u];
    size_t size = 99u;

    ASSERT_EQ(break_replication_wire_encoded_size(&fragment, &size),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(size, sizeof(out));
    size = 99u;
    ASSERT_EQ(break_replication_wire_encode(&fragment, out, sizeof(out), &size),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(size, sizeof(out));
    ASSERT_EQ(out[24], 0xffu);
    ASSERT_EQ(out[25], 0xffu);
    ASSERT_EQ(out[26], 0x0fu);
    ASSERT_EQ(out[27], 0x00u);
    ASSERT_EQ(out[28], 0x00u);
    ASSERT_EQ(out[29], 0x00u);
    ASSERT_EQ(out[30], 0x10u);
    ASSERT_EQ(out[31], 0x00u);
    ASSERT_EQ(break_replication_wire_decode(out, size, &decoded),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(decoded.fragment_index, BREAK_REPLICATION_WIRE_MAX_FRAGMENT_COUNT - 1u);
    ASSERT_EQ(decoded.fragment_count, BREAK_REPLICATION_WIRE_MAX_FRAGMENT_COUNT);
    ASSERT_EQ(decoded.size, 1u);
    ASSERT_EQ(decoded.data, out + BREAK_REPLICATION_WIRE_HEADER_SIZE);
}

TEST(wire_fragmenter_pool_round_trip)
{
    const uint8_t payload[] = "abcdefghijklmnopqrstuvwxyz";
    const size_t order[] = {4u, 0u, 5u, 2u, 1u, 3u};
    BreakReplicationFragment *fragments = NULL;
    size_t count = 0u;
    BreakReplicationReassemblyPool *pool;
    size_t i;

    ASSERT_EQ(break_replication_fragment_payload(
                  77u, 11u, payload, sizeof(payload) - 1u, 5u,
                  &fragments, &count),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(count, 6u);
    pool = break_replication_reassembly_pool_create(11u, 2u, 64u);
    ASSERT_NOT_NULL(pool);
    for (i = 0u; i < count; ++i) {
        uint8_t wire[64];
        size_t wire_size = 0u;
        BreakReplicationFragment decoded;
        uint64_t completed_id = UINT64_MAX;
        uint8_t *assembled = NULL;
        size_t assembled_size = 0u;
        BreakReplicationReassemblyResult result;

        ASSERT_EQ(break_replication_wire_encode(
                      &fragments[order[i]], wire, sizeof(wire), &wire_size),
                  BREAK_REPLICATION_FRAGMENT_OK);
        ASSERT_EQ(break_replication_wire_decode(wire, wire_size, &decoded),
                  BREAK_REPLICATION_FRAGMENT_OK);
        ASSERT_EQ(decoded.data, wire + BREAK_REPLICATION_WIRE_HEADER_SIZE);
        result = break_replication_reassembly_pool_push_at(
            pool, &decoded, 100u + i, &completed_id, &assembled, &assembled_size);
        if (i + 1u == count) {
            ASSERT_EQ(result, BREAK_REPLICATION_REASSEMBLY_COMPLETE);
            ASSERT_EQ(completed_id, 77u);
            ASSERT_EQ(assembled_size, sizeof(payload) - 1u);
            ASSERT_NOT_NULL(assembled);
            ASSERT_TRUE(memcmp(assembled, payload, assembled_size) == 0);
            break_replication_reassembly_free(assembled);
        } else {
            ASSERT_EQ(result, BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
            ASSERT_EQ(completed_id, 0u);
            ASSERT_EQ(assembled, NULL);
            ASSERT_EQ(assembled_size, 0u);
        }
    }
    ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), 0u);
    break_replication_reassembly_pool_destroy(pool);
    break_replication_fragments_free(fragments, count);
}

TEST(wire_fragment_size_boundaries)
{
    uint8_t *data = (uint8_t *)malloc(BREAK_REPLICATION_WIRE_MAX_FRAGMENT_DATA_SIZE + 1u);
    uint8_t *wire = (uint8_t *)malloc(BREAK_NET_MAX_PAYLOAD_SIZE + 1u);
    BreakReplicationFragment fragment;
    BreakReplicationFragment decoded;
    size_t size = 99u;

    ASSERT_NOT_NULL(data);
    ASSERT_NOT_NULL(wire);
    memset(data, 0x5a, BREAK_REPLICATION_WIRE_MAX_FRAGMENT_DATA_SIZE + 1u);
    memset(wire, 0xcd, BREAK_NET_MAX_PAYLOAD_SIZE + 1u);
    fragment.delta_id = 1u;
    fragment.base_id = 0u;
    fragment.fragment_index = 0u;
    fragment.fragment_count = 1u;
    fragment.checksum = UINT32_MAX;
    fragment.data = data;
    fragment.size = BREAK_REPLICATION_WIRE_MAX_FRAGMENT_DATA_SIZE;
    ASSERT_EQ(fragment.size, 65496u);
    ASSERT_EQ(break_replication_wire_encoded_size(&fragment, &size),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(size, BREAK_NET_MAX_PAYLOAD_SIZE);
    size = 99u;
    ASSERT_EQ(break_replication_wire_encode(
                  &fragment, wire, BREAK_NET_MAX_PAYLOAD_SIZE, &size),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(size, BREAK_NET_MAX_PAYLOAD_SIZE);
    ASSERT_EQ(break_replication_wire_decode(wire, size, &decoded),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(decoded.size, fragment.size);
    ASSERT_EQ(decoded.data, wire + BREAK_REPLICATION_WIRE_HEADER_SIZE);
    ASSERT_TRUE(memcmp(decoded.data, data, data ? fragment.size : 0u) == 0);
    memset(&decoded, 0xa5, sizeof(decoded));
    ASSERT_EQ(break_replication_wire_decode(
                  wire, BREAK_NET_MAX_PAYLOAD_SIZE + 1u, &decoded),
              BREAK_REPLICATION_FRAGMENT_OVER_LIMIT);
    ASSERT_TRUE(fragment_is_zero(&decoded));

    fragment.size = BREAK_REPLICATION_WIRE_MAX_FRAGMENT_DATA_SIZE + 1u;
    ASSERT_EQ(fragment.size, 65497u);
    size = 99u;
    ASSERT_EQ(break_replication_wire_encoded_size(&fragment, &size),
              BREAK_REPLICATION_FRAGMENT_OVER_LIMIT);
    ASSERT_EQ(size, 0u);
    memset(wire, 0xcd, BREAK_NET_MAX_PAYLOAD_SIZE + 1u);
    size = 99u;
    ASSERT_EQ(break_replication_wire_encode(
                  &fragment, wire, BREAK_NET_MAX_PAYLOAD_SIZE + 1u, &size),
              BREAK_REPLICATION_FRAGMENT_OVER_LIMIT);
    ASSERT_EQ(size, 0u);
    ASSERT_TRUE(bytes_are(wire, BREAK_NET_MAX_PAYLOAD_SIZE + 1u, 0xcdu));
    free(wire);
    free(data);
}

TEST(wire_encode_validation_clears_outputs_and_preserves_buffer)
{
    uint8_t data = 0xaau;
    BreakReplicationFragment fragment = {1u, 2u, 0u, 1u, 3u, &data, 1u};
    uint8_t out[64];
    size_t size = 99u;

    check_encode_rejection(NULL, BREAK_REPLICATION_FRAGMENT_INVALID);
    ASSERT_EQ(break_replication_wire_encoded_size(&fragment, NULL),
              BREAK_REPLICATION_FRAGMENT_INVALID);
    memset(out, 0xa5, sizeof(out));
    ASSERT_EQ(break_replication_wire_encode(&fragment, NULL, sizeof(out), &size),
              BREAK_REPLICATION_FRAGMENT_INVALID);
    ASSERT_EQ(size, 0u);
    size = 99u;
    ASSERT_EQ(break_replication_wire_encode(&fragment, out, sizeof(out), NULL),
              BREAK_REPLICATION_FRAGMENT_INVALID);
    ASSERT_EQ(size, 99u);
    ASSERT_TRUE(bytes_are(out, sizeof(out), 0xa5u));

    fragment.data = NULL;
    check_encode_rejection(&fragment, BREAK_REPLICATION_FRAGMENT_INVALID);
    fragment.data = &data;
    fragment.size = 0u;
    check_encode_rejection(&fragment, BREAK_REPLICATION_FRAGMENT_INVALID);
    fragment.size = 1u;
    fragment.delta_id = 0u;
    check_encode_rejection(&fragment, BREAK_REPLICATION_FRAGMENT_INVALID);
    fragment.delta_id = 1u;
    fragment.fragment_count = 0u;
    check_encode_rejection(&fragment, BREAK_REPLICATION_FRAGMENT_INVALID);
    fragment.fragment_count = BREAK_REPLICATION_WIRE_MAX_FRAGMENT_COUNT + 1u;
    check_encode_rejection(&fragment, BREAK_REPLICATION_FRAGMENT_OVER_LIMIT);
    fragment.fragment_count = 1u;
    fragment.fragment_index = 1u;
    check_encode_rejection(&fragment, BREAK_REPLICATION_FRAGMENT_INVALID);
    fragment.fragment_index = 0u;

    ASSERT_EQ(break_replication_wire_encoded_size(&fragment, &size),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(size, BREAK_REPLICATION_WIRE_HEADER_SIZE + 1u);
    memset(out, 0xa5, sizeof(out));
    size = 99u;
    ASSERT_EQ(break_replication_wire_encode(
                  &fragment, out, BREAK_REPLICATION_WIRE_HEADER_SIZE, &size),
              BREAK_REPLICATION_FRAGMENT_OVER_LIMIT);
    ASSERT_EQ(size, 0u);
    ASSERT_TRUE(bytes_are(out, sizeof(out), 0xa5u));
}

TEST(wire_decode_rejects_every_truncation_and_clears_output)
{
    size_t size;
    for (size = 0u; size < sizeof(canonical_wire); ++size) {
        uint8_t *input = (uint8_t *)malloc(size ? size : 1u);
        ASSERT_NOT_NULL(input);
        if (size != 0u) memcpy(input, canonical_wire, size);
        check_decode_rejection(input, size, BREAK_REPLICATION_FRAGMENT_INVALID);
        free(input);
    }
    check_decode_rejection(NULL, sizeof(canonical_wire), BREAK_REPLICATION_FRAGMENT_INVALID);
    ASSERT_EQ(break_replication_wire_decode(canonical_wire, sizeof(canonical_wire), NULL),
              BREAK_REPLICATION_FRAGMENT_INVALID);
}

TEST(wire_decode_rejects_noncanonical_and_invalid_fields)
{
    uint8_t wire[sizeof(canonical_wire) + 1u];
    size_t offset;

    memcpy(wire, canonical_wire, sizeof(canonical_wire));
    wire[0] = 0x58u;
    check_decode_rejection(wire, sizeof(canonical_wire), BREAK_REPLICATION_FRAGMENT_INVALID);
    for (offset = 1u; offset < 4u; ++offset) {
        memcpy(wire, canonical_wire, sizeof(canonical_wire));
        wire[offset] ^= 1u;
        check_decode_rejection(wire, sizeof(canonical_wire),
                               BREAK_REPLICATION_FRAGMENT_INVALID);
    }
    memcpy(wire, canonical_wire, sizeof(canonical_wire));
    wire[4] = 0x02u;
    check_decode_rejection(wire, sizeof(canonical_wire), BREAK_REPLICATION_FRAGMENT_INVALID);
    memcpy(wire, canonical_wire, sizeof(canonical_wire));
    wire[5] = 0x01u;
    check_decode_rejection(wire, sizeof(canonical_wire), BREAK_REPLICATION_FRAGMENT_INVALID);
    memcpy(wire, canonical_wire, sizeof(canonical_wire));
    wire[6] = 0x27u;
    check_decode_rejection(wire, sizeof(canonical_wire), BREAK_REPLICATION_FRAGMENT_INVALID);
    memcpy(wire, canonical_wire, sizeof(canonical_wire));
    wire[7] = 0x01u;
    check_decode_rejection(wire, sizeof(canonical_wire), BREAK_REPLICATION_FRAGMENT_INVALID);
    memcpy(wire, canonical_wire, sizeof(canonical_wire));
    memset(wire + 36u, 0, 4u);
    check_decode_rejection(wire, BREAK_REPLICATION_WIRE_HEADER_SIZE,
                           BREAK_REPLICATION_FRAGMENT_INVALID);
    memcpy(wire, canonical_wire, sizeof(canonical_wire));
    wire[sizeof(canonical_wire)] = 0u;
    check_decode_rejection(wire, sizeof(wire), BREAK_REPLICATION_FRAGMENT_INVALID);
    memcpy(wire, canonical_wire, sizeof(canonical_wire));
    memset(wire + 8u, 0, 8u);
    check_decode_rejection(wire, sizeof(canonical_wire), BREAK_REPLICATION_FRAGMENT_INVALID);
    memcpy(wire, canonical_wire, sizeof(canonical_wire));
    memset(wire + 28u, 0, 4u);
    check_decode_rejection(wire, sizeof(canonical_wire), BREAK_REPLICATION_FRAGMENT_INVALID);
    memcpy(wire, canonical_wire, sizeof(canonical_wire));
    wire[28] = 0x01u;
    wire[29] = 0x00u;
    wire[30] = 0x10u;
    wire[31] = 0x00u;
    check_decode_rejection(wire, sizeof(canonical_wire), BREAK_REPLICATION_FRAGMENT_OVER_LIMIT);
    memcpy(wire, canonical_wire, sizeof(canonical_wire));
    wire[24] = 0x04u;
    check_decode_rejection(wire, sizeof(canonical_wire), BREAK_REPLICATION_FRAGMENT_INVALID);
    memcpy(wire, canonical_wire, sizeof(canonical_wire));
    wire[36] = 0x03u;
    check_decode_rejection(wire, sizeof(canonical_wire), BREAK_REPLICATION_FRAGMENT_INVALID);
    memcpy(wire, canonical_wire, sizeof(canonical_wire));
    wire[36] = 0x05u;
    check_decode_rejection(wire, sizeof(canonical_wire), BREAK_REPLICATION_FRAGMENT_INVALID);
    memcpy(wire, canonical_wire, sizeof(canonical_wire));
    wire[36] = 0xd9u;
    wire[37] = 0xffu;
    wire[38] = 0x00u;
    wire[39] = 0x00u;
    check_decode_rejection(wire, sizeof(canonical_wire), BREAK_REPLICATION_FRAGMENT_OVER_LIMIT);
    memcpy(wire, canonical_wire, sizeof(canonical_wire));
    wire[36] = 0x04u;
    wire[37] = 0x00u;
    wire[38] = 0x01u;
    wire[39] = 0x00u;
    check_decode_rejection(wire, sizeof(canonical_wire), BREAK_REPLICATION_FRAGMENT_OVER_LIMIT);
}

TEST(wire_decode_borrows_unaligned_data_without_fnv_validation)
{
    union {
        uint64_t alignment;
        uint8_t bytes[sizeof(canonical_wire) + 1u];
    } storage = {0};
    BreakReplicationFragment decoded;

    memcpy(storage.bytes + 1u, canonical_wire, sizeof(canonical_wire));
    memset(storage.bytes + 1u + 32u, 0, 4u);
    ASSERT_EQ(break_replication_wire_decode(
                  storage.bytes + 1u, sizeof(canonical_wire), &decoded),
              BREAK_REPLICATION_FRAGMENT_OK);
    ASSERT_EQ(decoded.delta_id, 1u);
    ASSERT_EQ(decoded.base_id, 2u);
    ASSERT_EQ(decoded.fragment_index, 3u);
    ASSERT_EQ(decoded.fragment_count, 4u);
    ASSERT_EQ(decoded.checksum, 0u);
    ASSERT_EQ(decoded.size, sizeof(canonical_data));
    ASSERT_EQ(decoded.data,
              storage.bytes + 1u + BREAK_REPLICATION_WIRE_HEADER_SIZE);
    ASSERT_TRUE(memcmp(decoded.data, canonical_data, sizeof(canonical_data)) == 0);
}

TEST_MAIN_BEGIN()
    RUN_TEST(wire_canonical_layout_and_borrowed_decode);
    RUN_TEST(wire_wide_delta_and_base_canonical_round_trip);
    RUN_TEST(wire_max_fragment_count_round_trip);
    RUN_TEST(wire_fragmenter_pool_round_trip);
    RUN_TEST(wire_fragment_size_boundaries);
    RUN_TEST(wire_encode_validation_clears_outputs_and_preserves_buffer);
    RUN_TEST(wire_decode_rejects_every_truncation_and_clears_output);
    RUN_TEST(wire_decode_rejects_noncanonical_and_invalid_fields);
    RUN_TEST(wire_decode_borrows_unaligned_data_without_fnv_validation);
TEST_MAIN_END()
