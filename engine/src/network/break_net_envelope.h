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
/* Optional correlation extension: when the codec-owned flag
 * BREAK_NET_ENVELOPE_FLAG_CORRELATED is set on the wire, an 8-byte
 * little-endian non-zero correlation ID follows the 18-byte header, before
 * the payload. The length field at offset 14 then counts extension +
 * payload, so length-only framers still find frame boundaries. Frames with
 * correlation_id == 0 are byte-identical to the base layout; older decoders
 * reject the flag (INVALID_FLAGS) instead of misreading the payload. */
#define BREAK_NET_ENVELOPE_CORRELATION_SIZE 8u
#define BREAK_NET_ENVELOPE_MAX_BODY_SIZE \
    (BREAK_NET_ENVELOPE_CORRELATION_SIZE + BREAK_NET_ENVELOPE_MAX_PAYLOAD_SIZE)
#define BREAK_NET_ENVELOPE_MAX_SIZE (BREAK_NET_ENVELOPE_HEADER_SIZE + BREAK_NET_ENVELOPE_MAX_BODY_SIZE)
/* Caller-visible flag bits. */
#define BREAK_NET_ENVELOPE_FLAGS_MASK 0x000fu
/* Codec-owned wire bit; callers set correlation_id instead. Passing it in
 * `flags` to encode is INVALID_FLAGS; decode strips it from `flags`. */
#define BREAK_NET_ENVELOPE_FLAG_CORRELATED 0x0010u

typedef struct BreakNetEnvelope {
    uint16_t protocol_version;
    uint16_t message_id;
    uint16_t flags;
    uint32_t sequence;
    uint64_t correlation_id; /* 0 = uncorrelated (no wire extension) */
    const void *payload;
    size_t payload_size; /* payload only; never includes the extension */
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
