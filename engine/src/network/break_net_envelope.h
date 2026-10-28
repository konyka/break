#ifndef BREAK_NET_ENVELOPE_H
#define BREAK_NET_ENVELOPE_H

#include <stddef.h>
#include <stdint.h>

#include "network/break_net_message_registry.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BREAK_NET_ENVELOPE_MAGIC 0x42524b31u
#define BREAK_NET_ENVELOPE_HEADER_SIZE 18u
#define BREAK_NET_ENVELOPE_MAX_PAYLOAD_SIZE BREAK_NET_MAX_PAYLOAD_SIZE
#define BREAK_NET_ENVELOPE_MAX_SIZE (BREAK_NET_ENVELOPE_HEADER_SIZE + BREAK_NET_ENVELOPE_MAX_PAYLOAD_SIZE)
#define BREAK_NET_ENVELOPE_FLAGS_MASK 0x000fu

typedef struct BreakNetEnvelope {
    uint16_t protocol_version;
    uint16_t message_id;
    uint16_t flags;
    uint32_t sequence;
    const void *payload;
    size_t payload_size;
} BreakNetEnvelope;

typedef struct BreakNetEnvelopeContext {
    uint32_t last_sequence;
    int has_sequence;
} BreakNetEnvelopeContext;

typedef enum BreakNetEnvelopeResult {
    BREAK_NET_ENVELOPE_OK = 0,
    BREAK_NET_ENVELOPE_INVALID_ARGUMENT,
    BREAK_NET_ENVELOPE_INVALID_LENGTH,
    BREAK_NET_ENVELOPE_BAD_MAGIC,
    BREAK_NET_ENVELOPE_INVALID_FLAGS,
    BREAK_NET_ENVELOPE_UNSUPPORTED_VERSION,
    BREAK_NET_ENVELOPE_UNKNOWN_MESSAGE,
    BREAK_NET_ENVELOPE_OVER_LIMIT,
    BREAK_NET_ENVELOPE_INVALID_SEQUENCE,
    BREAK_NET_ENVELOPE_BUFFER_TOO_SMALL
} BreakNetEnvelopeResult;

BreakNetEnvelopeResult break_net_envelope_encode(const BreakNetEnvelope *envelope,
                                                  uint8_t *buffer, size_t buffer_size,
                                                  size_t *encoded_size);
BreakNetEnvelopeResult break_net_envelope_decode(const uint8_t *buffer, size_t buffer_size,
                                                  BreakNetEnvelope *envelope);
BreakNetEnvelopeResult break_net_envelope_decode_with_context(
    BreakNetEnvelopeContext *context, const uint8_t *buffer, size_t buffer_size,
    BreakNetEnvelope *envelope);

#ifdef __cplusplus
}
#endif

#endif
