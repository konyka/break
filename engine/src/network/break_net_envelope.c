#include "network/break_net_envelope.h"

#include <string.h>

static void put16(uint8_t *p, uint16_t v) { p[0] = (uint8_t)v; p[1] = (uint8_t)(v >> 8u); }
static void put32(uint8_t *p, uint32_t v)
{
    p[0] = (uint8_t)v; p[1] = (uint8_t)(v >> 8u);
    p[2] = (uint8_t)(v >> 16u); p[3] = (uint8_t)(v >> 24u);
}
static uint16_t get16(const uint8_t *p) { return (uint16_t)p[0] | ((uint16_t)p[1] << 8u); }
static uint32_t get32(const uint8_t *p)
{
    return (uint32_t)p[0] | ((uint32_t)p[1] << 8u) |
           ((uint32_t)p[2] << 16u) | ((uint32_t)p[3] << 24u);
}

static BreakNetEnvelopeResult validate_fields(uint16_t version, uint16_t id,
                                               uint16_t flags, size_t payload_size)
{
    const BreakNetMessageDefinition *definition =
        break_net_message_registry_lookup(break_net_message_registry_default(), id);
    if (definition == NULL) return BREAK_NET_ENVELOPE_UNKNOWN_MESSAGE;
    if (!break_net_message_definition_supports_version(definition, version))
        return BREAK_NET_ENVELOPE_UNSUPPORTED_VERSION;
    if ((flags & (uint16_t)~BREAK_NET_ENVELOPE_FLAGS_MASK) != 0u)
        return BREAK_NET_ENVELOPE_INVALID_FLAGS;
    if (payload_size > BREAK_NET_MAX_PAYLOAD_SIZE || payload_size > definition->payload_limit)
        return BREAK_NET_ENVELOPE_OVER_LIMIT;
    return BREAK_NET_ENVELOPE_OK;
}

BreakNetEnvelopeResult break_net_envelope_encode(const BreakNetEnvelope *e, uint8_t *b,
                                                  size_t n, size_t *out)
{
    size_t total;
    BreakNetEnvelopeResult result;
    if (out != NULL) *out = 0u;
    if (e == NULL || b == NULL || out == NULL ||
        (e->payload_size != 0u && e->payload == NULL))
        return BREAK_NET_ENVELOPE_INVALID_ARGUMENT;
    result = validate_fields(e->protocol_version, e->message_id, e->flags, e->payload_size);
    if (result != BREAK_NET_ENVELOPE_OK) return result;
    if (e->payload_size > SIZE_MAX - BREAK_NET_ENVELOPE_HEADER_SIZE)
        return BREAK_NET_ENVELOPE_INVALID_LENGTH;
    total = BREAK_NET_ENVELOPE_HEADER_SIZE + e->payload_size;
    if (n < total) return BREAK_NET_ENVELOPE_BUFFER_TOO_SMALL;
    put32(b, BREAK_NET_ENVELOPE_MAGIC); put16(b + 4u, e->protocol_version);
    put16(b + 6u, e->message_id); put16(b + 8u, e->flags);
    put32(b + 10u, e->sequence); put32(b + 14u, (uint32_t)e->payload_size);
    if (e->payload_size != 0u) memcpy(b + BREAK_NET_ENVELOPE_HEADER_SIZE, e->payload, e->payload_size);
    *out = total;
    return BREAK_NET_ENVELOPE_OK;
}

BreakNetEnvelopeResult break_net_envelope_decode_with_context(BreakNetEnvelopeContext *c,
    const uint8_t *b, size_t n, BreakNetEnvelope *e)
{
    uint32_t payload_size;
    size_t total;
    BreakNetEnvelopeResult result;
    if (e != NULL) memset(e, 0, sizeof(*e));
    if (b == NULL || e == NULL || n < BREAK_NET_ENVELOPE_HEADER_SIZE)
        return BREAK_NET_ENVELOPE_INVALID_LENGTH;
    if (get32(b) != BREAK_NET_ENVELOPE_MAGIC) return BREAK_NET_ENVELOPE_BAD_MAGIC;
    payload_size = get32(b + 14u);
    if ((size_t)payload_size > BREAK_NET_MAX_PAYLOAD_SIZE)
        return BREAK_NET_ENVELOPE_OVER_LIMIT;
    total = (size_t)BREAK_NET_ENVELOPE_HEADER_SIZE + (size_t)payload_size;
    if (n != total) return BREAK_NET_ENVELOPE_INVALID_LENGTH;
    result = validate_fields(get16(b + 4u), get16(b + 6u), get16(b + 8u), (size_t)payload_size);
    if (result != BREAK_NET_ENVELOPE_OK) return result;
    if (c != NULL && c->has_sequence && get32(b + 10u) <= c->last_sequence)
        return BREAK_NET_ENVELOPE_INVALID_SEQUENCE;
    e->protocol_version = get16(b + 4u); e->message_id = get16(b + 6u);
    e->flags = get16(b + 8u); e->sequence = get32(b + 10u);
    e->payload_size = (size_t)payload_size; e->payload = b + BREAK_NET_ENVELOPE_HEADER_SIZE;
    if (c != NULL) { c->last_sequence = e->sequence; c->has_sequence = 1; }
    return BREAK_NET_ENVELOPE_OK;
}

BreakNetEnvelopeResult break_net_envelope_decode(const uint8_t *b, size_t n, BreakNetEnvelope *e)
{
    return break_net_envelope_decode_with_context(NULL, b, n, e);
}
