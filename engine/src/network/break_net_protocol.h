#ifndef BREAK_NET_PROTOCOL_H
#define BREAK_NET_PROTOCOL_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef BREAK_NET_PROTOCOL_VERSION
#define BREAK_NET_PROTOCOL_VERSION 1u
#endif

#ifndef BREAK_NET_PROTOCOL_HEADER_SIZE
#define BREAK_NET_PROTOCOL_HEADER_SIZE 12u
#endif

#ifndef BREAK_NET_PROTOCOL_MAX_MESSAGE_SIZE
#define BREAK_NET_PROTOCOL_MAX_MESSAGE_SIZE (64u * 1024u)
#endif

#include "network/break_net_message.h"

typedef enum BreakNetValidationResult {
    BREAK_NET_VALIDATION_OK = 0,
    BREAK_NET_VALIDATION_INVALID_LENGTH,
    BREAK_NET_VALIDATION_UNSUPPORTED_VERSION,
    BREAK_NET_VALIDATION_UNKNOWN_MESSAGE,
    BREAK_NET_VALIDATION_INVALID_SEQUENCE,
    BREAK_NET_VALIDATION_OVER_LIMIT
} BreakNetValidationResult;

typedef struct BreakNetProtocolContext {
    uint32_t last_sequence;
    uint32_t max_sequence_jump;
    bool has_sequence;
} BreakNetProtocolContext;

void break_net_protocol_context_init(BreakNetProtocolContext *context,
                                     uint32_t max_sequence_jump);

BreakNetValidationResult break_net_protocol_validate(
    BreakNetProtocolContext *context,
    const uint8_t *buffer,
    size_t buffer_size,
    BreakNetMessageView *view);

#ifdef __cplusplus
}
#endif

#endif /* BREAK_NET_PROTOCOL_H */
