#ifndef BREAK_NET_EVENTS_H
#define BREAK_NET_EVENTS_H

#include <stddef.h>
#include <stdint.h>
#include "network/break_net_message.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef uint64_t BreakNetConnectionKey;

typedef enum BreakNetEventType {
    BREAK_NET_EVENT_CONNECTION_OPENED = 0,
    BREAK_NET_EVENT_MESSAGE_RECEIVED,
    BREAK_NET_EVENT_SEND_DRAINED,
    BREAK_NET_EVENT_CONNECTION_CLOSED,
    BREAK_NET_EVENT_TRANSPORT_ERROR
} BreakNetEventType;

typedef struct BreakNetEvent {
    BreakNetEventType type;
    BreakNetConnectionKey connection_key;
    uint32_t reason;
    BreakNetOwnedMessage message;
} BreakNetEvent;

void break_net_event_release(BreakNetEvent *event);

#ifdef __cplusplus
}
#endif
#endif
