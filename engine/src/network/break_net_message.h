#ifndef BREAK_NET_MESSAGE_H
#define BREAK_NET_MESSAGE_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct BreakNetMessageView {
    uint16_t message_id;
    uint16_t protocol_version;
    uint32_t sequence;
    const void *data;
    size_t size;
} BreakNetMessageView;

#ifndef BREAK_NET_MAX_PAYLOAD_SIZE
#define BREAK_NET_MAX_PAYLOAD_SIZE (64u * 1024u)
#endif

typedef struct BreakNetOwnedMessage {
    uint16_t message_id;
    uint16_t protocol_version;
    uint32_t sequence;
    void *data;
    size_t size;
} BreakNetOwnedMessage;

typedef enum BreakNetMessageResult {
    BREAK_NET_MESSAGE_OK = 0,
    BREAK_NET_MESSAGE_INVALID,
    BREAK_NET_MESSAGE_OVER_LIMIT,
    BREAK_NET_MESSAGE_OUT_OF_MEMORY
} BreakNetMessageResult;

BreakNetMessageResult break_net_message_view_init(
    BreakNetMessageView *view,
    uint16_t message_id,
    uint16_t protocol_version,
    uint32_t sequence,
    const void *data,
    size_t size);

BreakNetMessageResult break_net_message_copy(
    BreakNetOwnedMessage *owned,
    const BreakNetMessageView *view);

void break_net_message_release(BreakNetOwnedMessage *owned);

#ifdef __cplusplus
}
#endif

#endif /* BREAK_NET_MESSAGE_H */
