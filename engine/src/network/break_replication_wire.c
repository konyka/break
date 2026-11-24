#include "network/break_replication_wire.h"

#include <string.h>

static void put16(uint8_t *p, uint16_t v)
{
    p[0] = (uint8_t)v;
    p[1] = (uint8_t)(v >> 8u);
}

static void put32(uint8_t *p, uint32_t v)
{
    p[0] = (uint8_t)v;
    p[1] = (uint8_t)(v >> 8u);
    p[2] = (uint8_t)(v >> 16u);
    p[3] = (uint8_t)(v >> 24u);
}

static void put64(uint8_t *p, uint64_t v)
{
    put32(p, (uint32_t)v);
    put32(p + 4u, (uint32_t)(v >> 32u));
}

static uint16_t get16(const uint8_t *p)
{
    return (uint16_t)p[0] | ((uint16_t)p[1] << 8u);
}

static uint32_t get32(const uint8_t *p)
{
    return (uint32_t)p[0] | ((uint32_t)p[1] << 8u) |
           ((uint32_t)p[2] << 16u) | ((uint32_t)p[3] << 24u);
}

static uint64_t get64(const uint8_t *p)
{
    return (uint64_t)get32(p) | ((uint64_t)get32(p + 4u) << 32u);
}

static BreakReplicationFragmentResult validate_fragment(
    const BreakReplicationFragment *fragment)
{
    if (!fragment || !fragment->data || fragment->size == 0u ||
        fragment->delta_id == 0u || fragment->fragment_count == 0u ||
        fragment->fragment_index >= fragment->fragment_count) {
        return BREAK_REPLICATION_FRAGMENT_INVALID;
    }
    if (fragment->fragment_count > BREAK_REPLICATION_WIRE_MAX_FRAGMENT_COUNT ||
        fragment->size > BREAK_REPLICATION_WIRE_MAX_FRAGMENT_DATA_SIZE) {
        return BREAK_REPLICATION_FRAGMENT_OVER_LIMIT;
    }
    return BREAK_REPLICATION_FRAGMENT_OK;
}

BreakReplicationFragmentResult break_replication_wire_encoded_size(
    const BreakReplicationFragment *fragment, size_t *out_size)
{
    BreakReplicationFragmentResult result;
    if (out_size) *out_size = 0u;
    if (!out_size) return BREAK_REPLICATION_FRAGMENT_INVALID;
    result = validate_fragment(fragment);
    if (result != BREAK_REPLICATION_FRAGMENT_OK) return result;
    *out_size = BREAK_REPLICATION_WIRE_HEADER_SIZE + fragment->size;
    return BREAK_REPLICATION_FRAGMENT_OK;
}

BreakReplicationFragmentResult break_replication_wire_encode(
    const BreakReplicationFragment *fragment,
    uint8_t *out, size_t capacity, size_t *out_size)
{
    BreakReplicationFragmentResult result;
    size_t total;
    if (out_size) *out_size = 0u;
    if (!out || !out_size) return BREAK_REPLICATION_FRAGMENT_INVALID;
    result = validate_fragment(fragment);
    if (result != BREAK_REPLICATION_FRAGMENT_OK) return result;
    total = BREAK_REPLICATION_WIRE_HEADER_SIZE + fragment->size;
    if (capacity < total) return BREAK_REPLICATION_FRAGMENT_OVER_LIMIT;
    memcpy(out, "BRFG", 4u);
    put16(out + 4u, BREAK_REPLICATION_WIRE_VERSION);
    put16(out + 6u, BREAK_REPLICATION_WIRE_HEADER_SIZE);
    put64(out + 8u, fragment->delta_id);
    put64(out + 16u, fragment->base_id);
    put32(out + 24u, fragment->fragment_index);
    put32(out + 28u, fragment->fragment_count);
    put32(out + 32u, fragment->checksum);
    put32(out + 36u, (uint32_t)fragment->size);
    memcpy(out + BREAK_REPLICATION_WIRE_HEADER_SIZE,
           fragment->data, fragment->size);
    *out_size = total;
    return BREAK_REPLICATION_FRAGMENT_OK;
}

BreakReplicationFragmentResult break_replication_wire_decode(
    const void *data, size_t size, BreakReplicationFragment *out_fragment)
{
    const uint8_t *bytes;
    BreakReplicationFragment decoded;
    BreakReplicationFragmentResult result;
    uint32_t fragment_size;
    if (out_fragment) memset(out_fragment, 0, sizeof(*out_fragment));
    if (!data || !out_fragment) return BREAK_REPLICATION_FRAGMENT_INVALID;
    if (size > BREAK_NET_MAX_PAYLOAD_SIZE) return BREAK_REPLICATION_FRAGMENT_OVER_LIMIT;
    if (size < BREAK_REPLICATION_WIRE_HEADER_SIZE) {
        return BREAK_REPLICATION_FRAGMENT_INVALID;
    }
    bytes = (const uint8_t *)data;
    if (memcmp(bytes, "BRFG", 4u) != 0 ||
        get16(bytes + 4u) != BREAK_REPLICATION_WIRE_VERSION ||
        get16(bytes + 6u) != BREAK_REPLICATION_WIRE_HEADER_SIZE) {
        return BREAK_REPLICATION_FRAGMENT_INVALID;
    }
    fragment_size = get32(bytes + 36u);
    if (fragment_size > BREAK_REPLICATION_WIRE_MAX_FRAGMENT_DATA_SIZE) {
        return BREAK_REPLICATION_FRAGMENT_OVER_LIMIT;
    }
    if (size != BREAK_REPLICATION_WIRE_HEADER_SIZE + (size_t)fragment_size) {
        return BREAK_REPLICATION_FRAGMENT_INVALID;
    }
    memset(&decoded, 0, sizeof(decoded));
    decoded.delta_id = get64(bytes + 8u);
    decoded.base_id = get64(bytes + 16u);
    decoded.fragment_index = get32(bytes + 24u);
    decoded.fragment_count = get32(bytes + 28u);
    decoded.checksum = get32(bytes + 32u);
    decoded.data = bytes + BREAK_REPLICATION_WIRE_HEADER_SIZE;
    decoded.size = (size_t)fragment_size;
    result = validate_fragment(&decoded);
    if (result != BREAK_REPLICATION_FRAGMENT_OK) return result;
    *out_fragment = decoded;
    return BREAK_REPLICATION_FRAGMENT_OK;
}
