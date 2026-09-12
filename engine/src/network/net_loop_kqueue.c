/*
 * net_loop_kqueue.c — macOS/BSD backend for net_loop, built on kqueue.
 *
 * Throughput choices:
 *   - Registration changes are staged as a changelist and committed with one
 *     kevent() syscall (add/modify/remove of several sockets = 1 syscall).
 *   - EV_CLEAR gives edge-triggered semantics: an event is reported once per
 *     readiness transition; callers drain sockets fully, which is the optimal
 *     high-throughput pattern (one wakeup -> one batch of recvfrom).
 *   - EVFILT_USER implements cross-thread wakeup with zero extra fds.
 */

typedef int net_loop_kqueue_translation_unit;

#if defined(ENGINE_PLATFORM_MACOS) || defined(ENGINE_PLATFORM_IOS) || defined(__APPLE__)

#include "net_loop.h"

#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NET_LOOP_WAKEUP_IDENT 1u

typedef struct {
    NetSocket *socket;
    void      *tag;
    u32        events;   /* interest set */
    bool       used;
    bool       read_registered;   /* kernel currently watches EVFILT_READ */
    bool       write_registered;  /* kernel currently watches EVFILT_WRITE */
} NetLoopSlot;

struct NetLoop {
    int          kq;
    NetLoopSlot *slots;
    u32          slot_count;
    u32          slot_cap;
    /* Staged registration changes, committed on the next wait or explicitly
     * by flush(). Keeps add/modify/remove syscall-free when they batch. */
    struct kevent *pending;
    u32            pending_count;
    u32            pending_cap;
    struct kevent *wait_events;
    u32            wait_cap;
};

static u32 kq_find_slot(const NetLoop *loop, NetSocket *socket)
{
    for (u32 i = 0; i < loop->slot_count; i++) {
        if (loop->slots[i].used && loop->slots[i].socket == socket) return i;
    }
    return UINT32_MAX;
}

static bool kq_stage(NetLoop *loop, u64 ident, u16 filter, u16 flags,
                     const void *udata)
{
    if (loop->pending_count == loop->pending_cap) {
        u32 new_cap = loop->pending_cap ? loop->pending_cap * 2u : 16u;
        struct kevent *np = realloc(loop->pending, new_cap * sizeof(*np));
        if (!np) return false;
        loop->pending = np;
        loop->pending_cap = new_cap;
    }
    struct kevent *kev = &loop->pending[loop->pending_count++];
    EV_SET(kev, ident, filter, flags, 0, 0, (void *)udata);
    return true;
}

static bool kq_flush(NetLoop *loop)
{
    if (loop->pending_count == 0u) return true;
    int rc = kevent(loop->kq, loop->pending, (int)loop->pending_count,
                    NULL, 0, NULL);
    loop->pending_count = 0u;
    return rc >= 0;
}

NetLoop *net_loop_create(void)
{
    NetLoop *loop = (NetLoop *)calloc(1, sizeof(*loop));
    if (!loop) return NULL;
    loop->kq = kqueue();
    if (loop->kq < 0) {
        free(loop);
        return NULL;
    }
    /* Wakeup channel: user filter, no fd cost. */
    if (!kq_stage(loop, NET_LOOP_WAKEUP_IDENT, EVFILT_USER, EV_ADD, NULL) ||
        !kq_flush(loop)) {
        close(loop->kq);
        free(loop);
        return NULL;
    }
    return loop;
}

void net_loop_destroy(NetLoop *loop)
{
    if (!loop) return;
    if (loop->kq >= 0) close(loop->kq);
    free(loop->slots);
    free(loop->pending);
    free(loop->wait_events);
    free(loop);
}

/* Stage the kqueue changelist entries that make the kernel interest set equal
 * slot->events for slot->socket: EV_ADD enables, EV_DELETE disables per
 * filter. Only deltas are staged — EV_DELETE on a never-registered filter
 * fails the whole changelist with ENOENT. */
static bool kq_sync_filters(NetLoop *loop, NetLoopSlot *slot)
{
    intptr_t fd = net_socket_native_handle(slot->socket);
    if (fd < 0) return false;
    bool ok = true;
    bool want_read  = (slot->events & NET_LOOP_READ) != 0u;
    bool want_write = (slot->events & NET_LOOP_WRITE) != 0u;

    if (want_read && !slot->read_registered) {
        ok &= kq_stage(loop, (u64)fd, EVFILT_READ, EV_ADD | EV_CLEAR, slot);
        slot->read_registered = true;
    } else if (!want_read && slot->read_registered) {
        ok &= kq_stage(loop, (u64)fd, EVFILT_READ, EV_DELETE, NULL);
        slot->read_registered = false;
    } else if (want_read) {
        /* Re-EV_ADD to refresh udata (slot may have moved after realloc). */
        ok &= kq_stage(loop, (u64)fd, EVFILT_READ, EV_ADD | EV_CLEAR, slot);
    }
    if (want_write && !slot->write_registered) {
        ok &= kq_stage(loop, (u64)fd, EVFILT_WRITE, EV_ADD | EV_CLEAR, slot);
        slot->write_registered = true;
    } else if (!want_write && slot->write_registered) {
        ok &= kq_stage(loop, (u64)fd, EVFILT_WRITE, EV_DELETE, NULL);
        slot->write_registered = false;
    } else if (want_write) {
        ok &= kq_stage(loop, (u64)fd, EVFILT_WRITE, EV_ADD | EV_CLEAR, slot);
    }
    return ok;
}

bool net_loop_add(NetLoop *loop, NetSocket *socket, u32 events, void *tag)
{
    if (!loop || !socket || !net_loop_interest_valid(events)) return false;

    u32 idx = kq_find_slot(loop, socket);
    if (idx == UINT32_MAX) {
        if (loop->slot_count == loop->slot_cap) {
            u32 new_cap = loop->slot_cap ? loop->slot_cap * 2u : 16u;
            NetLoopSlot *ns = realloc(loop->slots, new_cap * sizeof(*ns));
            if (!ns) return false;
            memset(ns + loop->slot_cap, 0,
                   (new_cap - loop->slot_cap) * sizeof(*ns));
            loop->slots = ns;
            loop->slot_cap = new_cap;
            /* The realloc moved every slot; kernel udata still points at the
             * old block. Restage EV_ADD for all live registrations so their
             * udata is refreshed with the new addresses. */
            for (u32 i = 0; i < loop->slot_count; i++) {
                if (loop->slots[i].used &&
                    (loop->slots[i].read_registered ||
                     loop->slots[i].write_registered)) {
                    (void)kq_sync_filters(loop, &loop->slots[i]);
                }
            }
        }
        idx = loop->slot_count++;
    }
    loop->slots[idx].socket = socket;
    loop->slots[idx].tag = tag;
    loop->slots[idx].events = events;
    loop->slots[idx].used = true;
    /* kqueue udata carries the slot so wait() needs no lookup. */
    return kq_sync_filters(loop, &loop->slots[idx]);
}

bool net_loop_modify(NetLoop *loop, NetSocket *socket, u32 events)
{
    if (!loop || !socket || !net_loop_interest_valid(events)) return false;
    u32 idx = kq_find_slot(loop, socket);
    if (idx == UINT32_MAX) return false;
    loop->slots[idx].events = events;
    return kq_sync_filters(loop, &loop->slots[idx]);
}

bool net_loop_remove(NetLoop *loop, NetSocket *socket)
{
    if (!loop || !socket) return false;
    u32 idx = kq_find_slot(loop, socket);
    if (idx == UINT32_MAX) return false;
    loop->slots[idx].events = 0u;
    bool ok = kq_sync_filters(loop, &loop->slots[idx]);
    /* Commit the deletes before the slot dies so no kernel-queued event can
     * reference it; events already delivered to userspace are dropped in
     * wait() via the used flag. */
    ok = kq_flush(loop) && ok;
    loop->slots[idx].used = false;
    loop->slots[idx].socket = NULL;
    loop->slots[idx].read_registered = false;
    loop->slots[idx].write_registered = false;
    return ok;
}

i32 net_loop_wait(NetLoop *loop, NetLoopEvent *out, u32 max, i32 timeout_ms)
{
    if (!loop || !out || !net_loop_wait_count_valid(max)) return NET_ERROR;
    if (!kq_flush(loop)) return NET_ERROR;

    if (max > loop->wait_cap) {
        struct kevent *events = (struct kevent *)realloc(
            loop->wait_events, (size_t)max * sizeof(*events));
        if (!events) return NET_ERROR;
        loop->wait_events = events;
        loop->wait_cap = max;
    }

    struct timespec ts;
    struct timespec *tsp = NULL;
    if (timeout_ms >= 0) {
        ts.tv_sec  = timeout_ms / 1000;
        ts.tv_nsec = (long)(timeout_ms % 1000) * 1000000L;
        tsp = &ts;
    }

    int n = kevent(loop->kq, NULL, 0, loop->wait_events, (int)max, tsp);
    if (n < 0) return NET_ERROR;

    i32 count = 0;
    for (int i = 0; i < n; i++) {
        if (loop->wait_events[i].filter == EVFILT_USER) continue; /* wakeup: no socket event */
        NetLoopSlot *slot = (NetLoopSlot *)loop->wait_events[i].udata;
        if (!slot || !slot->used) continue; /* removed since the event queued */
        u32 events = 0;
        if (loop->wait_events[i].filter == EVFILT_READ)  events |= NET_LOOP_READ;
        if (loop->wait_events[i].filter == EVFILT_WRITE) events |= NET_LOOP_WRITE;
        if (loop->wait_events[i].flags & EV_ERROR)       events |= NET_LOOP_ERROR;
        out[count].socket = slot->socket;
        out[count].events = events;
        out[count].tag = slot->tag;
        count++;
        if ((u32)count == max) break;
    }
    return count;
}

void net_loop_wakeup(NetLoop *loop)
{
    if (!loop || loop->kq < 0) return;
    /* Do not touch staged registration state here: wakeup() is the only
     * operation permitted from a thread other than the loop owner. */
    struct kevent kev;
    EV_SET(&kev, NET_LOOP_WAKEUP_IDENT, EVFILT_USER, 0, NOTE_TRIGGER, 0, NULL);
    (void)kevent(loop->kq, &kev, 1, NULL, 0, NULL);
}

#endif /* ENGINE_PLATFORM_MACOS || ENGINE_PLATFORM_IOS */
