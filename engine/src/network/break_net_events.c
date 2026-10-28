#include "network/break_net_events.h"

void break_net_event_release(BreakNetEvent *event)
{
    if (event == NULL) return;
    break_net_message_release(&event->message);
    event->type = BREAK_NET_EVENT_CONNECTION_OPENED;
    event->connection_key = 0u;
    event->reason = 0u;
}
