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
    uint64_t highest_delta_id;
    bool highest_valid;
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

static BreakReplicationFragmentResult fragment_plan(
    const void *payload, size_t payload_size, size_t fragment_payload_size,
    uint32_t *out_count)
{
    size_t numerator;
    size_t count;
    if (!out_count || !fragment_payload_size ||
        (payload_size && !payload) || payload_size == 0u)
        return BREAK_REPLICATION_FRAGMENT_INVALID;
    if (payload_size > BREAK_REPLICATION_MAX_REASSEMBLY_SIZE ||
        fragment_payload_size > BREAK_NET_MAX_PAYLOAD_SIZE)
        return BREAK_REPLICATION_FRAGMENT_OVER_LIMIT;
    if (!checked_add_size(payload_size, fragment_payload_size - 1u, &numerator))
        return BREAK_REPLICATION_FRAGMENT_OVER_LIMIT;
    count = numerator / fragment_payload_size;
    if (!count || count > UINT32_MAX || count > FRAGMENT_MAX_COUNT)
        return BREAK_REPLICATION_FRAGMENT_OVER_LIMIT;
    *out_count = (uint32_t)count;
    return BREAK_REPLICATION_FRAGMENT_OK;
}

static void fragment_fill(uint64_t delta_id, uint64_t base_id,
                          const void *payload, size_t payload_size,
                          size_t fragment_payload_size,
                          BreakReplicationFragment *out, uint32_t count)
{
    const uint8_t *bytes = (const uint8_t *)payload;
    uint32_t i;
    for (i = 0u; i < count; ++i) {
        size_t offset = (size_t)i * fragment_payload_size;
        size_t size = payload_size - offset;
        if (size > fragment_payload_size) size = fragment_payload_size;
        out[i].delta_id = delta_id;
        out[i].base_id = base_id;
        out[i].fragment_index = i;
        out[i].fragment_count = count;
        out[i].data = bytes + offset;
        out[i].size = size;
        out[i].checksum = checksum_bytes(out[i].data, size);
    }
}

BreakReplicationFragmentResult break_replication_fragment_payload(
    uint64_t delta_id, uint64_t base_id, const void *payload, size_t payload_size,
    size_t fragment_payload_size, BreakReplicationFragment **fragments, size_t *fragment_count)
{
    BreakReplicationFragment *result;
    BreakReplicationFragmentResult plan;
    uint32_t count;
    size_t result_bytes;
    if (!fragments || !fragment_count) return BREAK_REPLICATION_FRAGMENT_INVALID;
    plan = fragment_plan(payload, payload_size, fragment_payload_size, &count);
    if (plan != BREAK_REPLICATION_FRAGMENT_OK) return plan;
    if (!checked_mul_size((size_t)count, sizeof(*result), &result_bytes))
        return BREAK_REPLICATION_FRAGMENT_OVER_LIMIT;
    result = (BreakReplicationFragment *)calloc(1u, result_bytes);
    if (!result) return BREAK_REPLICATION_FRAGMENT_OUT_OF_MEMORY;
    fragment_fill(delta_id, base_id, payload, payload_size, fragment_payload_size,
                  result, count);
    *fragments = result;
    *fragment_count = count;
    return BREAK_REPLICATION_FRAGMENT_OK;
}

BreakReplicationFragmentResult break_replication_fragment_payload_into(
    uint64_t delta_id, uint64_t base_id, const void *payload, size_t payload_size,
    size_t fragment_payload_size, BreakReplicationFragment *out_fragments,
    size_t fragment_capacity, size_t *out_fragment_count)
{
    BreakReplicationFragmentResult plan;
    uint32_t count;
    if (!out_fragment_count) return BREAK_REPLICATION_FRAGMENT_INVALID;
    *out_fragment_count = 0u;
    if (!out_fragments) return BREAK_REPLICATION_FRAGMENT_INVALID;
    plan = fragment_plan(payload, payload_size, fragment_payload_size, &count);
    if (plan != BREAK_REPLICATION_FRAGMENT_OK) return plan;
    if (fragment_capacity < count) return BREAK_REPLICATION_FRAGMENT_OVER_LIMIT;
    fragment_fill(delta_id, base_id, payload, payload_size, fragment_payload_size,
                  out_fragments, count);
    *out_fragment_count = count;
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

static BreakReplicationReassemblyResult start_stream(
    BreakReplicationReassembler *reassembler,
    const BreakReplicationFragment *fragment, uint8_t **payload, size_t *payload_size)
{
    size_t array_bytes;
    size_t pointer_bytes;
    size_t bitmap_bytes;
    size_t metadata_bytes;
    BreakReplicationFragment *new_fragments = NULL;
    uint8_t **new_owned = NULL;
    uint8_t *new_received = NULL;
    uint8_t *new_data = NULL;
    uint8_t *complete = NULL;
    if (reassembler->highest_valid && fragment->delta_id < reassembler->highest_delta_id) {
        return BREAK_REPLICATION_REASSEMBLY_CONFLICT;
    }
    if (!checked_mul_size((size_t)fragment->fragment_count, sizeof(*new_fragments), &array_bytes) ||
        !checked_mul_size((size_t)fragment->fragment_count, sizeof(*new_owned), &pointer_bytes) ||
        !checked_mul_size((size_t)fragment->fragment_count, sizeof(*new_received), &bitmap_bytes) ||
        !checked_add_size(array_bytes, pointer_bytes, &metadata_bytes) ||
        !checked_add_size(metadata_bytes, bitmap_bytes, &metadata_bytes) ||
        metadata_bytes > BREAK_REPLICATION_MAX_REASSEMBLY_SIZE) {
        return BREAK_REPLICATION_REASSEMBLY_OVER_LIMIT;
    }
    new_fragments = (BreakReplicationFragment *)calloc(1u, array_bytes);
    new_owned = (uint8_t **)calloc(1u, pointer_bytes);
    new_received = (uint8_t *)calloc(1u, bitmap_bytes);
    if (!new_fragments || !new_owned || !new_received) goto oom;
    new_data = (uint8_t *)malloc(fragment->size);
    if (!new_data) goto oom;
    memcpy(new_data, fragment->data, fragment->size);
    if (fragment->fragment_count == 1u) {
        complete = (uint8_t *)malloc(fragment->size);
        if (!complete) goto oom;
        memcpy(complete, fragment->data, fragment->size);
    }
    clear_reassembly(reassembler);
    reassembler->fragments = new_fragments;
    reassembler->owned_data = new_owned;
    reassembler->received = new_received;
    reassembler->delta_id = fragment->delta_id;
    reassembler->fragment_count = fragment->fragment_count;
    reassembler->fragments[fragment->fragment_index] = *fragment;
    reassembler->fragments[fragment->fragment_index].data = new_data;
    new_owned[fragment->fragment_index] = new_data;
    new_received[fragment->fragment_index] = 1u;
    reassembler->received_count = 1u;
    reassembler->total_size = fragment->size;
    reassembler->highest_delta_id = fragment->delta_id;
    reassembler->highest_valid = true;
    if (fragment->fragment_count > 1u) return BREAK_REPLICATION_REASSEMBLY_INCOMPLETE;
    if (payload) *payload = complete; else free(complete);
    if (payload_size) *payload_size = fragment->size;
    clear_reassembly(reassembler);
    return BREAK_REPLICATION_REASSEMBLY_COMPLETE;
oom:
    free(complete);
    free(new_data);
    free(new_received);
    free(new_owned);
    free(new_fragments);
    return BREAK_REPLICATION_REASSEMBLY_OUT_OF_MEMORY;
}

BreakReplicationReassemblyResult break_replication_reassembler_push(
    BreakReplicationReassembler *reassembler, const BreakReplicationFragment *fragment,
    uint8_t **payload, size_t *payload_size)
{
    BreakReplicationFragment *copy;
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
    if (!reassembler->fragments || fragment->delta_id > reassembler->delta_id) {
        return start_stream(reassembler, fragment, payload, payload_size);
    }
    if (fragment->delta_id != reassembler->delta_id ||
        fragment->fragment_count != reassembler->fragment_count) {
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
    if (reassembler) {
        clear_reassembly(reassembler);
        reassembler->highest_delta_id = 0u;
        reassembler->highest_valid = false;
    }
}
