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
    uint64_t last_activity;
    bool timed;
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
    reassembler->timed = false;
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

static bool validate_reassembly_fragment(
    uint64_t expected_base_id, const BreakReplicationFragment *fragment,
    BreakReplicationReassemblyResult *error)
{
    if (!fragment || !fragment->data || !fragment->size ||
        !fragment->fragment_count || fragment->fragment_count > FRAGMENT_MAX_COUNT ||
        fragment->fragment_index >= fragment->fragment_count ||
        fragment->size > BREAK_NET_MAX_PAYLOAD_SIZE) {
        *error = BREAK_REPLICATION_REASSEMBLY_INVALID;
        return false;
    }
    if (fragment->base_id != expected_base_id) {
        *error = BREAK_REPLICATION_REASSEMBLY_BASE_MISMATCH;
        return false;
    }
    if (checksum_bytes(fragment->data, fragment->size) != fragment->checksum) {
        *error = BREAK_REPLICATION_REASSEMBLY_CHECKSUM_MISMATCH;
        return false;
    }
    return true;
}

BreakReplicationReassemblyResult break_replication_reassembler_push(
    BreakReplicationReassembler *reassembler, const BreakReplicationFragment *fragment,
    uint8_t **payload, size_t *payload_size)
{
    BreakReplicationReassemblyResult validation;
    BreakReplicationFragment *copy;
    if (payload) *payload = NULL;
    if (payload_size) *payload_size = 0u;
    if (!reassembler) return BREAK_REPLICATION_REASSEMBLY_INVALID;
    if (!validate_reassembly_fragment(reassembler->expected_base_id, fragment, &validation))
        return validation;
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

BreakReplicationReassemblyResult break_replication_reassembler_push_at(
    BreakReplicationReassembler *reassembler, const BreakReplicationFragment *fragment,
    uint64_t now, uint8_t **payload, size_t *payload_size)
{
    const uint64_t delta_before = reassembler ? reassembler->delta_id : 0u;
    const bool pending_before = reassembler && reassembler->fragments;
    const BreakReplicationReassemblyResult result =
        break_replication_reassembler_push(reassembler, fragment, payload, payload_size);
    if (reassembler && reassembler->fragments &&
        (!pending_before || reassembler->delta_id != delta_before || reassembler->timed) &&
        (result == BREAK_REPLICATION_REASSEMBLY_INCOMPLETE ||
         result == BREAK_REPLICATION_REASSEMBLY_DUPLICATE)) {
        reassembler->last_activity = now;
        reassembler->timed = true;
    }
    return result;
}

bool break_replication_reassembler_expire(BreakReplicationReassembler *reassembler,
                                          uint64_t now, uint64_t max_idle)
{
    uint64_t idle;
    if (!reassembler || !reassembler->fragments || !reassembler->timed) return false;
    idle = now > reassembler->last_activity ? now - reassembler->last_activity : 0u;
    if (idle < max_idle) return false;
    clear_reassembly(reassembler);
    return true;
}

size_t break_replication_reassembler_pending_bytes(
    const BreakReplicationReassembler *reassembler)
{
    return reassembler ? reassembler->total_size : 0u;
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

typedef struct BreakReplicationReassemblyPoolSlot {
    BreakReplicationReassembler reassembler;
    uint64_t delta_id;
    bool active;
} BreakReplicationReassemblyPoolSlot;

struct BreakReplicationReassemblyPool {
    BreakReplicationReassemblyPoolSlot *slots;
    size_t stream_capacity;
    size_t max_pending_bytes;
    size_t pending_bytes;
    uint64_t expected_base_id;
    uint64_t retired_delta_id;
    bool retired_valid;
    uint64_t expiry_interval;
    uint64_t expiry_max_idle;
    uint64_t last_tick;
    bool expiry_enabled;
    bool tick_initialized;
};

BreakReplicationReassemblyPool *break_replication_reassembly_pool_create(
    uint64_t expected_base_id, size_t stream_capacity, size_t max_pending_bytes)
{
    BreakReplicationReassemblyPool *pool;
    size_t i;
    if (!stream_capacity || stream_capacity > BREAK_REPLICATION_REASSEMBLY_POOL_MAX_STREAMS ||
        !max_pending_bytes || max_pending_bytes > BREAK_REPLICATION_MAX_REASSEMBLY_SIZE)
        return NULL;
    pool = (BreakReplicationReassemblyPool *)calloc(1u, sizeof(*pool));
    if (!pool) return NULL;
    pool->slots = (BreakReplicationReassemblyPoolSlot *)calloc(
        stream_capacity, sizeof(*pool->slots));
    if (!pool->slots) {
        free(pool);
        return NULL;
    }
    pool->stream_capacity = stream_capacity;
    pool->max_pending_bytes = max_pending_bytes;
    pool->expected_base_id = expected_base_id;
    for (i = 0u; i < stream_capacity; ++i)
        pool->slots[i].reassembler.expected_base_id = expected_base_id;
    return pool;
}

void break_replication_reassembly_pool_destroy(BreakReplicationReassemblyPool *pool)
{
    size_t i;
    if (!pool) return;
    for (i = 0u; i < pool->stream_capacity; ++i)
        clear_reassembly(&pool->slots[i].reassembler);
    free(pool->slots);
    free(pool);
}

BreakReplicationReassemblyResult break_replication_reassembly_pool_push_at(
    BreakReplicationReassemblyPool *pool, const BreakReplicationFragment *fragment,
    uint64_t now, uint64_t *completed_delta_id,
    uint8_t **payload, size_t *payload_size)
{
    BreakReplicationReassemblyPoolSlot *slot = NULL;
    BreakReplicationReassemblyPoolSlot *empty = NULL;
    BreakReplicationReassemblyResult validation;
    BreakReplicationReassemblyResult result;
    size_t slot_pending_before = 0u;
    size_t i;
    bool starting = false;
    if (completed_delta_id) *completed_delta_id = 0u;
    if (payload) *payload = NULL;
    if (payload_size) *payload_size = 0u;
    if (!pool) return BREAK_REPLICATION_REASSEMBLY_INVALID;
    (void)break_replication_reassembly_pool_tick(pool, now);
    if (!validate_reassembly_fragment(pool->expected_base_id, fragment, &validation))
        return validation;
    for (i = 0u; i < pool->stream_capacity; ++i) {
        if (pool->slots[i].active && pool->slots[i].delta_id == fragment->delta_id) {
            slot = &pool->slots[i];
            break;
        }
        if (!pool->slots[i].active && !empty) empty = &pool->slots[i];
    }
    if (!slot) {
        if (pool->retired_valid && fragment->delta_id < pool->retired_delta_id)
            return BREAK_REPLICATION_REASSEMBLY_CONFLICT;
        if (!empty) return BREAK_REPLICATION_REASSEMBLY_OVER_LIMIT;
        if (fragment->size > pool->max_pending_bytes - pool->pending_bytes)
            return BREAK_REPLICATION_REASSEMBLY_OVER_LIMIT;
        slot = empty;
        break_replication_reassembler_reset(&slot->reassembler);
        slot->delta_id = fragment->delta_id;
        slot->active = true;
        starting = true;
    } else {
        slot_pending_before = slot->reassembler.total_size;
        if (fragment->fragment_count == slot->reassembler.fragment_count &&
            !slot->reassembler.received[fragment->fragment_index] &&
            fragment->size > pool->max_pending_bytes - pool->pending_bytes) {
            return BREAK_REPLICATION_REASSEMBLY_OVER_LIMIT;
        }
    }
    result = break_replication_reassembler_push_at(
        &slot->reassembler, fragment, now, payload, payload_size);
    pool->pending_bytes = pool->pending_bytes - slot_pending_before +
                          break_replication_reassembler_pending_bytes(&slot->reassembler);
    if (result == BREAK_REPLICATION_REASSEMBLY_COMPLETE) {
        if (completed_delta_id) *completed_delta_id = slot->delta_id;
        if (!pool->retired_valid || pool->retired_delta_id < slot->delta_id) {
            pool->retired_delta_id = slot->delta_id;
            pool->retired_valid = true;
        }
        slot->active = false;
    } else if (starting && result != BREAK_REPLICATION_REASSEMBLY_INCOMPLETE) {
        slot->active = false;
    }
    return result;
}

size_t break_replication_reassembly_pool_expire(
    BreakReplicationReassemblyPool *pool, uint64_t now, uint64_t max_idle)
{
    size_t expired = 0u;
    size_t i;
    if (!pool) return 0u;
    for (i = 0u; i < pool->stream_capacity; ++i) {
        BreakReplicationReassemblyPoolSlot *slot = &pool->slots[i];
        const size_t slot_pending =
            break_replication_reassembler_pending_bytes(&slot->reassembler);
        if (!break_replication_reassembler_expire(&slot->reassembler, now, max_idle))
            continue;
        pool->pending_bytes -= slot_pending;
        slot->active = false;
        if (!pool->retired_valid || pool->retired_delta_id < slot->delta_id) {
            pool->retired_delta_id = slot->delta_id;
            pool->retired_valid = true;
        }
        expired++;
    }
    return expired;
}

void break_replication_reassembly_pool_set_expiry_schedule(
    BreakReplicationReassemblyPool *pool, uint64_t interval, uint64_t max_idle)
{
    if (!pool) return;
    pool->expiry_enabled = true;
    pool->expiry_interval = interval;
    pool->expiry_max_idle = max_idle;
    pool->last_tick = 0u;
    pool->tick_initialized = false;
}

void break_replication_reassembly_pool_disable_expiry_schedule(
    BreakReplicationReassemblyPool *pool)
{
    if (!pool) return;
    pool->expiry_enabled = false;
    pool->last_tick = 0u;
    pool->tick_initialized = false;
}

size_t break_replication_reassembly_pool_tick(
    BreakReplicationReassemblyPool *pool, uint64_t now)
{
    if (!pool || !pool->expiry_enabled) return 0u;
    if (!pool->tick_initialized) {
        pool->last_tick = now;
        pool->tick_initialized = true;
        return break_replication_reassembly_pool_expire(pool, now, pool->expiry_max_idle);
    }
    if (now < pool->last_tick || now - pool->last_tick < pool->expiry_interval)
        return 0u;
    pool->last_tick = now;
    return break_replication_reassembly_pool_expire(pool, now, pool->expiry_max_idle);
}

size_t break_replication_reassembly_pool_pending_streams(
    const BreakReplicationReassemblyPool *pool)
{
    size_t count = 0u;
    size_t i;
    if (!pool) return 0u;
    for (i = 0u; i < pool->stream_capacity; ++i) {
        if (pool->slots[i].active) count++;
    }
    return count;
}

size_t break_replication_reassembly_pool_pending_bytes(
    const BreakReplicationReassemblyPool *pool)
{
    return pool ? pool->pending_bytes : 0u;
}

void break_replication_reassembly_pool_reset(BreakReplicationReassemblyPool *pool)
{
    size_t i;
    if (!pool) return;
    for (i = 0u; i < pool->stream_capacity; ++i) {
        break_replication_reassembler_reset(&pool->slots[i].reassembler);
        pool->slots[i].delta_id = 0u;
        pool->slots[i].active = false;
    }
    pool->pending_bytes = 0u;
    pool->retired_delta_id = 0u;
    pool->retired_valid = false;
    pool->last_tick = 0u;
    pool->tick_initialized = false;
}
