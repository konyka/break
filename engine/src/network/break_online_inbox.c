#include <network/break_online_inbox.h>

#include <core/platform_thread.h>

#include <stdlib.h>
#include <string.h>

struct BreakOnlineInbox {
    PlatformThreadId owner;
    PlatformMutex mutex;
    BreakOnlineDatagram *slots;
    u32 capacity;
    u32 head;
    u32 count;
    bool closed;
    BreakOnlineInboxStats stats;
};

BreakRuntimeError break_online_inbox_create(u32 capacity,
                                            BreakOnlineInbox **out_inbox)
{
    BreakOnlineInbox *inbox;
    if (!out_inbox || !capacity || capacity > BREAK_ONLINE_INBOX_HARD_MAX) {
        return BREAK_RUNTIME_INVALID;
    }
    *out_inbox = NULL;
    inbox = (BreakOnlineInbox *)calloc(1u, sizeof(*inbox));
    if (!inbox) return BREAK_RUNTIME_OOM;
    inbox->slots = (BreakOnlineDatagram *)calloc(capacity, sizeof(*inbox->slots));
    if (!inbox->slots) {
        free(inbox);
        return BREAK_RUNTIME_OOM;
    }
    inbox->owner = platform_thread_current_id();
    inbox->capacity = capacity;
    platform_mutex_init(&inbox->mutex);
    *out_inbox = inbox;
    return BREAK_RUNTIME_OK;
}

void break_online_inbox_destroy(BreakOnlineInbox *inbox)
{
    if (!inbox || !platform_thread_id_equal(inbox->owner,
                                             platform_thread_current_id())) return;
    platform_mutex_destroy(&inbox->mutex);
    free(inbox->slots);
    free(inbox);
}

void break_online_inbox_close(BreakOnlineInbox *inbox)
{
    if (!inbox) return;
    platform_mutex_lock(&inbox->mutex);
    inbox->closed = true;
    platform_mutex_unlock(&inbox->mutex);
}

BreakRuntimeError break_online_inbox_push(BreakOnlineInbox *inbox,
                                          const NetAddress *source,
                                          const void *data, u32 size)
{
    BreakOnlineDatagram *slot;
    BreakRuntimeError result = BREAK_RUNTIME_OK;
    if (!inbox || !source || !data || !size || size > BREAK_ONLINE_MAX_DATAGRAM) {
        if (inbox) {
            platform_mutex_lock(&inbox->mutex);
            inbox->stats.invalid_rejects++;
            platform_mutex_unlock(&inbox->mutex);
        }
        return BREAK_RUNTIME_INVALID;
    }
    platform_mutex_lock(&inbox->mutex);
    if (inbox->closed) {
        inbox->stats.closed_rejects++;
        result = BREAK_RUNTIME_CLOSED;
    } else if (inbox->count == inbox->capacity) {
        inbox->stats.overload_rejects++;
        result = BREAK_RUNTIME_OVERLOAD;
    } else {
        slot = &inbox->slots[(inbox->head + inbox->count) % inbox->capacity];
        memset(slot, 0, sizeof(*slot));
        slot->source = *source;
        slot->size = (u16)size;
        memcpy(slot->bytes, data, size);
        inbox->count++;
        inbox->stats.accepted++;
        if (inbox->count > inbox->stats.high_water) {
            inbox->stats.high_water = inbox->count;
        }
    }
    platform_mutex_unlock(&inbox->mutex);
    return result;
}

BreakRuntimeError break_online_inbox_poll(BreakOnlineInbox *inbox,
                                          BreakOnlineDatagram *out,
                                          bool *out_ready)
{
    BreakRuntimeError result = BREAK_RUNTIME_OK;
    if (!inbox || !out || !out_ready) return BREAK_RUNTIME_INVALID;
    *out_ready = false;
    if (!platform_thread_id_equal(inbox->owner, platform_thread_current_id())) {
        return BREAK_RUNTIME_REJECTED;
    }
    platform_mutex_lock(&inbox->mutex);
    if (!inbox->count) {
        result = inbox->closed ? BREAK_RUNTIME_CLOSED : BREAK_RUNTIME_OK;
    } else {
        *out = inbox->slots[inbox->head];
        inbox->head = (inbox->head + 1u) % inbox->capacity;
        inbox->count--;
        inbox->stats.polled++;
        *out_ready = true;
    }
    platform_mutex_unlock(&inbox->mutex);
    return result;
}

BreakRuntimeError break_online_inbox_stats(BreakOnlineInbox *inbox,
                                           BreakOnlineInboxStats *out)
{
    if (!inbox || !out) return BREAK_RUNTIME_INVALID;
    platform_mutex_lock(&inbox->mutex);
    *out = inbox->stats;
    platform_mutex_unlock(&inbox->mutex);
    return BREAK_RUNTIME_OK;
}
