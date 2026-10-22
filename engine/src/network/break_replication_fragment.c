#include "network/break_replication_fragment.h"

#include <limits.h>
#include <stdlib.h>
#include <string.h>

#define FRAGMENT_MAX_COUNT 1048576u


static bool checked_add_size(size_t left, size_t right, size_t *out)
{
    if (!out || right > SIZE_MAX - left) return false;
    *out = left + right;
    return true;
}

static bool checked_mul_size(size_t left, size_t right, size_t *out)
{
    if (!out || (left && right > SIZE_MAX / left)) return false;
    *out = left * right;
    return true;
}

struct BreakReplicationReassembler {
    uint64_t expected_base_id;
    uint64_t delta_id;
    uint32_t fragment_count;
    uint32_t received_count;
    size_t total_size;
    BreakReplicationFragment *fragments;
    uint8_t **owned_data;
    uint8_t *received;
};

static uint32_t checksum_bytes(const uint8_t *data, size_t size)
{
    uint32_t hash = 2166136261u;
    size_t i;
    for (i = 0u; i < size; ++i) {
        hash ^= data[i];
        hash *= 16777619u;
    }
    return hash;
}

BreakReplicationFragmentResult break_replication_fragment_payload(
    uint64_t delta_id, uint64_t base_id, const void *payload, size_t payload_size,
    size_t fragment_payload_size, BreakReplicationFragment **fragments, size_t *fragment_count)
{
    BreakReplicationFragment *result;
    uint32_t count;
    size_t i;
    const uint8_t *bytes = (const uint8_t *)payload;
    size_t numerator;
    size_t result_bytes;
    if (!fragments || !fragment_count || !fragment_payload_size ||
        (payload_size && !payload) || payload_size == 0u) return BREAK_REPLICATION_FRAGMENT_INVALID;
    if (payload_size > BREAK_REPLICATION_MAX_REASSEMBLY_SIZE)
        return BREAK_REPLICATION_FRAGMENT_OVER_LIMIT;
    if (fragment_payload_size > BREAK_NET_MAX_PAYLOAD_SIZE)
        return BREAK_REPLICATION_FRAGMENT_OVER_LIMIT;
    if (!checked_add_size(payload_size, fragment_payload_size - 1u, &numerator))
        return BREAK_REPLICATION_FRAGMENT_OVER_LIMIT;
    if (numerator / fragment_payload_size > UINT32_MAX) return BREAK_REPLICATION_FRAGMENT_OVER_LIMIT;
    count = (uint32_t)(numerator / fragment_payload_size);
    if (!count || count > FRAGMENT_MAX_COUNT ||
        !checked_mul_size((size_t)count, sizeof(*result), &result_bytes))
        return BREAK_REPLICATION_FRAGMENT_OVER_LIMIT;
    result = (BreakReplicationFragment *)calloc(1u, result_bytes);
    if (!result) return BREAK_REPLICATION_FRAGMENT_OUT_OF_MEMORY;
    for (i = 0u; i < count; ++i) {
        size_t offset = i * fragment_payload_size;
        size_t size = payload_size - offset;
        if (size > fragment_payload_size) size = fragment_payload_size;
        result[i].delta_id = delta_id;
        result[i].base_id = base_id;
        result[i].fragment_index = (uint32_t)i;
        result[i].fragment_count = count;
        result[i].data = bytes + offset;
        result[i].size = size;
        result[i].checksum = checksum_bytes(result[i].data, size);
    }
    *fragments = result;
    *fragment_count = count;
    return BREAK_REPLICATION_FRAGMENT_OK;
}

void break_replication_fragments_free(BreakReplicationFragment *fragments, size_t fragment_count)
{
    (void)fragment_count;
    free(fragments);
}

BreakReplicationReassembler *break_replication_reassembler_create(uint64_t expected_base_id)
{
    BreakReplicationReassembler *result = (BreakReplicationReassembler *)calloc(1u, sizeof(*result));
    if (result) result->expected_base_id = expected_base_id;
    return result;
}

static void clear_reassembly(BreakReplicationReassembler *reassembler)
{
    size_t i;
    if (!reassembler) return;
    if (reassembler->fragments) {
        for (i = 0u; i < reassembler->fragment_count; ++i)
            free(reassembler->owned_data[i]);
    }
    free(reassembler->fragments);
    free(reassembler->owned_data);
    free(reassembler->received);
    reassembler->owned_data = NULL;
    reassembler->fragments = NULL;
    reassembler->received = NULL;
    reassembler->fragment_count = 0u;
    reassembler->received_count = 0u;
    reassembler->total_size = 0u;
}

void break_replication_reassembler_destroy(BreakReplicationReassembler *reassembler)
{
    if (!reassembler) return;
    clear_reassembly(reassembler);
    free(reassembler);
}

static BreakReplicationReassemblyResult assemble_if_complete(
    BreakReplicationReassembler *reassembler, uint8_t **payload, size_t *payload_size)
{
    uint8_t *result;
    size_t i;
    size_t offset = 0u;
    if (reassembler->received_count != reassembler->fragment_count)
        return BREAK_REPLICATION_REASSEMBLY_INCOMPLETE;
    result = (uint8_t *)malloc(reassembler->total_size);
    if (!result) return BREAK_REPLICATION_REASSEMBLY_OUT_OF_MEMORY;
    for (i = 0u; i < reassembler->fragment_count; ++i) {
        memcpy(result + offset, reassembler->fragments[i].data, reassembler->fragments[i].size);
        offset += reassembler->fragments[i].size;
    }
    if (payload) *payload = result; else free(result);
    if (payload_size) *payload_size = reassembler->total_size;
    clear_reassembly(reassembler);
    return BREAK_REPLICATION_REASSEMBLY_COMPLETE;
}

BreakReplicationReassemblyResult break_replication_reassembler_push(
    BreakReplicationReassembler *reassembler, const BreakReplicationFragment *fragment,
    uint8_t **payload, size_t *payload_size)
{
    BreakReplicationFragment *copy;
    uint8_t *received;
    if (payload) *payload = NULL;
    if (payload_size) *payload_size = 0u;
    if (!reassembler || !fragment || !fragment->data || !fragment->size ||
        !fragment->fragment_count || fragment->fragment_count > FRAGMENT_MAX_COUNT ||
        fragment->fragment_index >= fragment->fragment_count)
        return BREAK_REPLICATION_REASSEMBLY_INVALID;
    if (fragment->size > BREAK_NET_MAX_PAYLOAD_SIZE)
        return BREAK_REPLICATION_REASSEMBLY_INVALID;
    if (fragment->base_id != reassembler->expected_base_id)
        return BREAK_REPLICATION_REASSEMBLY_BASE_MISMATCH;
    if (checksum_bytes(fragment->data, fragment->size) != fragment->checksum)
        return BREAK_REPLICATION_REASSEMBLY_CHECKSUM_MISMATCH;
    if (!reassembler->fragments) {
        size_t array_bytes;
        size_t pointer_bytes;
        size_t bitmap_bytes;
        size_t metadata_bytes;
        if (!checked_mul_size((size_t)fragment->fragment_count, sizeof(*copy), &array_bytes) ||
            !checked_mul_size((size_t)fragment->fragment_count, sizeof(*reassembler->owned_data), &pointer_bytes) ||
            !checked_mul_size((size_t)fragment->fragment_count, sizeof(*reassembler->received), &bitmap_bytes) ||
            !checked_add_size(array_bytes, pointer_bytes, &metadata_bytes) ||
            !checked_add_size(metadata_bytes, bitmap_bytes, &metadata_bytes) ||
            metadata_bytes > BREAK_REPLICATION_MAX_REASSEMBLY_SIZE)
            return BREAK_REPLICATION_REASSEMBLY_OVER_LIMIT;
        reassembler->delta_id = fragment->delta_id;
        reassembler->fragment_count = fragment->fragment_count;
        copy = (BreakReplicationFragment *)calloc(1u, array_bytes);
        if (!checked_mul_size((size_t)fragment->fragment_count, sizeof(*reassembler->owned_data), &array_bytes)) {
            free(copy);
            return BREAK_REPLICATION_REASSEMBLY_OUT_OF_MEMORY;
        }
        reassembler->owned_data = (uint8_t **)calloc(1u, pointer_bytes);
        received = (uint8_t *)calloc(1u, bitmap_bytes);
        if (!copy || !reassembler->owned_data || !received) {
            free(copy);
            free(reassembler->owned_data);
            free(received);
            reassembler->fragments = NULL;
            reassembler->owned_data = NULL;
            reassembler->received = NULL;
            reassembler->fragment_count = 0u;
            reassembler->received_count = 0u;
            reassembler->total_size = 0u;
            return BREAK_REPLICATION_REASSEMBLY_OUT_OF_MEMORY;
        }
        reassembler->fragments = copy;
        reassembler->received = received;
    } else if (fragment->delta_id != reassembler->delta_id || fragment->fragment_count != reassembler->fragment_count) {
        return BREAK_REPLICATION_REASSEMBLY_CONFLICT;
    }
    if (reassembler->received[fragment->fragment_index]) {
        const BreakReplicationFragment *old = &reassembler->fragments[fragment->fragment_index];
        if (old->size == fragment->size && old->checksum == fragment->checksum &&
            memcmp(old->data, fragment->data, fragment->size) == 0) {
            if (reassembler->received_count == reassembler->fragment_count)
                return assemble_if_complete(reassembler, payload, payload_size);
            return BREAK_REPLICATION_REASSEMBLY_DUPLICATE;
        }
        return BREAK_REPLICATION_REASSEMBLY_CONFLICT;
    }
    if (fragment->size > BREAK_REPLICATION_MAX_REASSEMBLY_SIZE ||
        reassembler->total_size > BREAK_REPLICATION_MAX_REASSEMBLY_SIZE - fragment->size)
        return BREAK_REPLICATION_REASSEMBLY_OVER_LIMIT;
    copy = &reassembler->fragments[fragment->fragment_index];
    *copy = *fragment;
    {
        uint8_t *owned_data = (uint8_t *)malloc(fragment->size);
        if (!owned_data) return BREAK_REPLICATION_REASSEMBLY_OUT_OF_MEMORY;
        memcpy(owned_data, fragment->data, fragment->size);
        copy->data = owned_data;
        reassembler->owned_data[fragment->fragment_index] = owned_data;
    }
    if (!checked_add_size(reassembler->total_size, fragment->size, &reassembler->total_size)) {
        free(reassembler->owned_data[fragment->fragment_index]);
        reassembler->owned_data[fragment->fragment_index] = NULL;
        copy->data = NULL;
        return BREAK_REPLICATION_REASSEMBLY_OUT_OF_MEMORY;
    }
    reassembler->received[fragment->fragment_index] = 1u;
    reassembler->received_count++;
    if (reassembler->received_count != reassembler->fragment_count)
        return BREAK_REPLICATION_REASSEMBLY_INCOMPLETE;
    return assemble_if_complete(reassembler, payload, payload_size);
}

void break_replication_reassembly_free(void *payload)
{
    free(payload);
}

void break_replication_reassembler_reset(BreakReplicationReassembler *reassembler)
{
    if (reassembler) clear_reassembly(reassembler);
}
