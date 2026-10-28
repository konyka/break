#include "network/break_net_protocol.h"

#include <limits.h>
#include <string.h>

static uint16_t break_net_read_u16(const uint8_t *buffer)
{
    return (uint16_t)(((uint16_t)buffer[0] << 8u) | buffer[1]);
}

static uint32_t break_net_read_u32(const uint8_t *buffer)
{
    return ((uint32_t)buffer[0] << 24u) |
           ((uint32_t)buffer[1] << 16u) |
           ((uint32_t)buffer[2] << 8u) |
           (uint32_t)buffer[3];
}

void break_net_protocol_context_init(BreakNetProtocolContext *context,
                                     uint32_t max_sequence_jump)
{
    if (context == NULL) {
        return;
    }
    context->last_sequence = 0u;
    context->max_sequence_jump = max_sequence_jump;
    context->has_sequence = false;
}

BreakNetValidationResult break_net_protocol_validate(
    BreakNetProtocolContext *context,
    const uint8_t *buffer,
    size_t buffer_size,
    BreakNetMessageView *view)
{
    uint16_t version;
    uint16_t message_id;
    uint32_t sequence;
    uint32_t payload_size;
    size_t payload_size_as_size_t;
    size_t expected_size;

    if (view != NULL) {
        memset(view, 0, sizeof(*view));
    }
    if (context == NULL || buffer == NULL || view == NULL) {
        return BREAK_NET_VALIDATION_INVALID_LENGTH;
    }
    if (buffer_size < (size_t)BREAK_NET_PROTOCOL_HEADER_SIZE) {
        return BREAK_NET_VALIDATION_INVALID_LENGTH;
    }

    version = break_net_read_u16(buffer);
    message_id = break_net_read_u16(buffer + 2u);
    sequence = break_net_read_u32(buffer + 4u);
    payload_size = break_net_read_u32(buffer + 8u);
    payload_size_as_size_t = (size_t)payload_size;

    if (version != (uint16_t)BREAK_NET_PROTOCOL_VERSION) {
        return BREAK_NET_VALIDATION_UNSUPPORTED_VERSION;
    }
    if (message_id == 0u) {
        return BREAK_NET_VALIDATION_UNKNOWN_MESSAGE;
    }
    if (payload_size_as_size_t > (size_t)BREAK_NET_PROTOCOL_MAX_MESSAGE_SIZE) {
        return BREAK_NET_VALIDATION_OVER_LIMIT;
    }
    if (payload_size_as_size_t > SIZE_MAX - (size_t)BREAK_NET_PROTOCOL_HEADER_SIZE) {
        return BREAK_NET_VALIDATION_INVALID_LENGTH;
    }
    expected_size = (size_t)BREAK_NET_PROTOCOL_HEADER_SIZE + payload_size_as_size_t;
    if (buffer_size != expected_size) {
        return BREAK_NET_VALIDATION_INVALID_LENGTH;
    }
    if (context->has_sequence) {
        uint32_t jump;
        if (sequence <= context->last_sequence) {
            return BREAK_NET_VALIDATION_INVALID_SEQUENCE;
        }
        jump = sequence - context->last_sequence;
        if (jump > context->max_sequence_jump) {
            return BREAK_NET_VALIDATION_INVALID_SEQUENCE;
        }
    }

    view->message_id = message_id;
    view->protocol_version = version;
    view->sequence = sequence;
    view->data = buffer + BREAK_NET_PROTOCOL_HEADER_SIZE;
    view->size = payload_size_as_size_t;
    context->last_sequence = sequence;
    context->has_sequence = true;
    return BREAK_NET_VALIDATION_OK;
}
