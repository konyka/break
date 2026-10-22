#include "network/break_net_message.h"

#include <stdlib.h>
#include <string.h>

BreakNetMessageResult break_net_message_view_init(
    BreakNetMessageView *view,
    uint16_t message_id,
    uint16_t protocol_version,
    uint32_t sequence,
    const void *data,
    size_t size)
{
    if (view == NULL) {
        return BREAK_NET_MESSAGE_INVALID;
    }
    if (size > BREAK_NET_MAX_PAYLOAD_SIZE) {
        return BREAK_NET_MESSAGE_OVER_LIMIT;
    }
    if (size != 0u && data == NULL) {
        return BREAK_NET_MESSAGE_INVALID;
    }
    view->message_id = message_id;
    view->protocol_version = protocol_version;
    view->sequence = sequence;
    view->data = data;
    view->size = size;
    return BREAK_NET_MESSAGE_OK;
}

BreakNetMessageResult break_net_message_copy(
    BreakNetOwnedMessage *owned,
    const BreakNetMessageView *view)
{
    void *copy;

    if (owned == NULL || view == NULL) {
        return BREAK_NET_MESSAGE_INVALID;
    }
    if (view->size > BREAK_NET_MAX_PAYLOAD_SIZE) {
        return BREAK_NET_MESSAGE_OVER_LIMIT;
    }
    if (view->size != 0u && view->data == NULL) {
        return BREAK_NET_MESSAGE_INVALID;
    }
    if (owned->data != NULL || owned->size != 0u) {
        return BREAK_NET_MESSAGE_INVALID;
    }

    copy = NULL;
    if (view->size != 0u) {
        copy = malloc(view->size);
        if (copy == NULL) {
            return BREAK_NET_MESSAGE_OUT_OF_MEMORY;
        }
        memcpy(copy, view->data, view->size);
    }

    owned->message_id = view->message_id;
    owned->protocol_version = view->protocol_version;
    owned->sequence = view->sequence;
    owned->data = copy;
    owned->size = view->size;
    return BREAK_NET_MESSAGE_OK;
}

void break_net_message_release(BreakNetOwnedMessage *owned)
{
    if (owned == NULL) {
        return;
    }
    free(owned->data);
    owned->message_id = 0u;
    owned->protocol_version = 0u;
    owned->sequence = 0u;
    owned->data = NULL;
    owned->size = 0u;
}
