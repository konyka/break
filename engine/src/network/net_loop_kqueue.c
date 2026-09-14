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

#if defined(ENGINE_PLATFORM_MACOS) || defined(ENGINE_PLATFORM_IOS) || defined(__APPLE__)

#include "net_loop.h"

#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NET_LOOP_WAKEUP_IDENT 1u

typedef struct {
    NetSocket *socket;
    void      *tag;
    u32        events;   /* interest set */
    bool       used;     /* desired registration */
    void       *active_tag;
    u32        active_events;
    bool       active_used;
    bool       read_registered;   /* kernel currently watches EVFILT_READ */
    bool       write_registered;  /* kernel currently watches EVFILT_WRITE */
    bool       staged_read_registered;
    bool       staged_write_registered;
} NetLoopSlot;

struct NetLoop {
    int          kq;
    NetLoopSlot **slots;
    u32          slot_count;
    u32          slot_cap;
    /* Staged registration changes, committed on the next wait or explicitly
     * by flush(). Keeps add/modify/remove syscall-free when they batch. */
    struct kevent *pending;
    u32            pending_count;
    u32            pending_cap;
    struct kevent *wait_events;
    u32            wait_cap;
#if defined(ENGINE_NET_LOOP_TESTING)
    u32            fail_stage_countdown;
    bool           fail_next_flush;
#endif
};

static u32 kq_find_slot(const NetLoop *loop, NetSocket *socket)
{
    for (u32 i = 0; i < loop->slot_count; i++) {
        if (loop->slots[i] && loop->slots[i]->used &&
            loop->slots[i]->socket == socket) return i;
    }
    return UINT32_MAX;
}

static u32 kq_find_free_slot(const NetLoop *loop)
{
    for (u32 i = 0; i < loop->slot_count; i++) {
        if (loop->slots[i] && !loop->slots[i]->used) return i;
    }
    return UINT32_MAX;
}

static bool kq_next_capacity(u32 current, u32 required, size_t element_size,
                             u32 *next)
{
    if (!next || element_size == 0u) return false;
    u32 capacity = current ? current : 16u;
    while (capacity < required) {
        if (capacity > UINT32_MAX / 2u) return false;
        capacity *= 2u;
    }
    size_t bytes = (size_t)capacity * element_size;
    if (bytes / element_size != (size_t)capacity) {
        return false;
    }
    *next = capacity;
    return true;
}

static bool kq_ensure_capacity(NetLoop *loop, u32 required)
{
    if (required <= loop->slot_cap) return true;

    u32 new_cap;
    if (!kq_next_capacity(loop->slot_cap, required, sizeof(*loop->slots),
                          &new_cap)) return false;
    NetLoopSlot **slots = (NetLoopSlot **)realloc(
        loop->slots, (size_t)new_cap * sizeof(*slots));
    if (!slots) return false;
    memset(slots + loop->slot_cap, 0,
           (size_t)(new_cap - loop->slot_cap) * sizeof(*slots));
    loop->slots = slots;
    loop->slot_cap = new_cap;
    return true;
}

static bool kq_stage(NetLoop *loop, u64 ident, u16 filter, u16 flags,
                     const void *udata)
{
#if defined(ENGINE_NET_LOOP_TESTING)
    if (loop->fail_stage_countdown > 0u) {
        loop->fail_stage_countdown--;
        if (loop->fail_stage_countdown == 0u) return false;
    }
#endif
    if (loop->pending_count == loop->pending_cap) {
        if (loop->pending_count == UINT32_MAX) return false;
        u32 new_cap;
        if (!kq_next_capacity(loop->pending_cap, loop->pending_count + 1u,
                              sizeof(*loop->pending), &new_cap)) return false;
        struct kevent *np = realloc(loop->pending,
                                    (size_t)new_cap * sizeof(*np));
        if (!np) return false;
        loop->pending = np;
        loop->pending_cap = new_cap;
    }
    struct kevent *kev = &loop->pending[loop->pending_count++];
    EV_SET(kev, ident, filter, flags | EV_RECEIPT, 0, 0, (void *)udata);
    return true;
}

static void kq_restore_active(NetLoop *loop)
{
    for (u32 i = 0; i < loop->slot_count; i++) {
        NetLoopSlot *slot = loop->slots[i];
        if (!slot) continue;
        slot->tag = slot->active_tag;
        slot->events = slot->active_events;
        slot->used = slot->active_used;
        if (!slot->active_used) slot->socket = NULL;
        slot->staged_read_registered = slot->read_registered;
        slot->staged_write_registered = slot->write_registered;
    }
}

static bool kq_ensure_wait_capacity(NetLoop *loop, u32 required)
{
    if (required <= loop->wait_cap) return true;

    u32 new_cap;
    if (!kq_next_capacity(loop->wait_cap, required, sizeof(*loop->wait_events),
                          &new_cap)) return false;
    struct kevent *events = (struct kevent *)realloc(
        loop->wait_events, (size_t)new_cap * sizeof(*events));
    if (!events) return false;
    loop->wait_events = events;
    loop->wait_cap = new_cap;
    return true;
}

static void kq_abort_pending(NetLoop *loop)
{
    loop->pending_count = 0u;
    kq_restore_active(loop);
}

static bool kq_flush(NetLoop *loop)
{
    if (loop->pending_count == 0u) return true;
#if defined(ENGINE_NET_LOOP_TESTING)
    if (loop->fail_next_flush) {
        loop->fail_next_flush = false;
        kq_abort_pending(loop);
        return false;
    }
#endif
    if (loop->pending_count > (u32)INT_MAX ||
        !kq_ensure_wait_capacity(loop, loop->pending_count)) {
        kq_abort_pending(loop);
        return false;
    }
    int rc = kevent(loop->kq, loop->pending, (int)loop->pending_count,
                    loop->wait_events, (int)loop->pending_count, NULL);
    bool failed = rc < 0 || (u32)rc != loop->pending_count;
    if (!failed) {
        for (u32 i = 0; i < loop->pending_count; i++) {
            if ((loop->wait_events[i].flags & EV_ERROR) == 0u ||
                loop->wait_events[i].data != 0) {
                failed = true;
                break;
            }
        }
    }
    if (failed) {
        if (rc > 0) {
            u32 rollback_count = 0u;
            u32 receipt_count = (u32)rc;
            if (receipt_count > loop->pending_count) {
                receipt_count = loop->pending_count;
            }
            for (u32 i = receipt_count; i > 0u; i--) {
                u32 source = i - 1u;
                if ((loop->wait_events[source].flags & EV_ERROR) != 0u &&
                    loop->wait_events[source].data == 0) {
                    struct kevent *change = &loop->wait_events[rollback_count++];
                    const struct kevent *original = &loop->pending[source];
                    u16 flags = (original->flags & EV_DELETE) != 0u
                              ? (EV_ADD | EV_CLEAR) : EV_DELETE;
                    void *udata = original->udata;
                    if ((original->flags & EV_DELETE) != 0u) {
                        for (u32 slot_index = 0;
                             slot_index < loop->slot_count; slot_index++) {
                            NetLoopSlot *slot = loop->slots[slot_index];
                            if (slot && (u64)net_socket_native_handle(slot->socket) ==
                                original->ident) {
                                udata = slot;
                                break;
                            }
                        }
                    }
                    EV_SET(change, original->ident, original->filter,
                           flags | EV_RECEIPT,
                           0, 0, udata);
                }
            }
            if (rollback_count > 0u) {
                int rollback_rc = kevent(loop->kq, loop->wait_events,
                                         (int)rollback_count, loop->pending,
                                         (int)rollback_count, NULL);
                bool rollback_failed = rollback_rc < 0 ||
                                       rollback_rc != (int)rollback_count;
                if (!rollback_failed) {
                    for (u32 i = 0; i < rollback_count; i++) {
                        if ((loop->pending[i].flags & EV_ERROR) == 0u ||
                            loop->pending[i].data != 0) {
                            rollback_failed = true;
                            break;
                        }
                    }
                }
                if (rollback_failed) {
                    /* The kernel state is no longer knowable, so do not claim
                     * that the previous registration remains active. */
                    kq_abort_pending(loop);
                    return false;
                }
            }
        }
        kq_abort_pending(loop);
        return false;
    }
    loop->pending_count = 0u;
    for (u32 i = 0; i < loop->slot_count; i++) {
        NetLoopSlot *slot = loop->slots[i];
        if (!slot) continue;
        slot->active_tag = slot->tag;
        slot->active_events = slot->events;
        slot->active_used = slot->used;
        slot->read_registered = slot->staged_read_registered;
        slot->write_registered = slot->staged_write_registered;
    }
    return true;
}

#if defined(ENGINE_NET_LOOP_TESTING)
void net_loop_kqueue_test_fail_stage_after(NetLoop *loop,
                                           u32 successful_stages)
{
    if (loop && successful_stages < UINT32_MAX) {
        loop->fail_stage_countdown = successful_stages + 1u;
    }
}

void net_loop_kqueue_test_fail_next_flush(NetLoop *loop)
{
    if (loop) loop->fail_next_flush = true;
}

bool net_loop_kqueue_test_next_capacity(u32 current, u32 required, u32 *next)
{
    return next && kq_next_capacity(current, required,
                                    sizeof(*((NetLoop *)0)->slots), next);
}
#endif

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
    for (u32 i = 0; i < loop->slot_count; i++) free(loop->slots[i]);
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
    u32 pending_before = loop->pending_count;
    bool old_read = slot->staged_read_registered;
    bool old_write = slot->staged_write_registered;
    bool want_read  = slot->used && (slot->events & NET_LOOP_READ) != 0u;
    bool want_write = slot->used && (slot->events & NET_LOOP_WRITE) != 0u;

    if (want_read && !slot->staged_read_registered) {
        if (!kq_stage(loop, (u64)fd, EVFILT_READ, EV_ADD | EV_CLEAR, slot)) {
            ok = false;
        } else {
            slot->staged_read_registered = true;
        }
    } else if (!want_read && slot->staged_read_registered) {
        if (!kq_stage(loop, (u64)fd, EVFILT_READ, EV_DELETE, NULL)) {
            ok = false;
        } else {
            slot->staged_read_registered = false;
        }
    } else if (want_read) {
        /* Slot addresses are stable, so unchanged filters need no restage. */
    }
    if (ok && want_write && !slot->staged_write_registered) {
        if (!kq_stage(loop, (u64)fd, EVFILT_WRITE, EV_ADD | EV_CLEAR, slot)) {
            ok = false;
        } else {
            slot->staged_write_registered = true;
        }
    } else if (ok && !want_write && slot->staged_write_registered) {
        if (!kq_stage(loop, (u64)fd, EVFILT_WRITE, EV_DELETE, NULL)) {
            ok = false;
        } else {
            slot->staged_write_registered = false;
        }
    } else if (want_write) {
        /* Slot addresses are stable, so unchanged filters need no restage. */
    }
    if (!ok) {
        loop->pending_count = pending_before;
        slot->staged_read_registered = old_read;
        slot->staged_write_registered = old_write;
    }
    return ok;
}

bool net_loop_add(NetLoop *loop, NetSocket *socket, u32 events, void *tag)
{
    if (!loop || !socket || !net_loop_interest_valid(events)) return false;

    u32 idx = kq_find_slot(loop, socket);
    bool new_slot = false;
    if (idx == UINT32_MAX) {
        idx = kq_find_free_slot(loop);
        if (idx == UINT32_MAX) {
            if (loop->slot_count == UINT32_MAX ||
                !kq_ensure_capacity(loop, loop->slot_count + 1u)) return false;
            idx = loop->slot_count;
            loop->slots[idx] =
                (NetLoopSlot *)calloc(1, sizeof(*loop->slots[idx]));
            if (!loop->slots[idx]) return false;
            loop->slot_count++;
            new_slot = true;
        }
    }
    NetLoopSlot *slot = loop->slots[idx];
    void *old_tag = slot->tag;
    u32 old_events = slot->events;
    bool old_used = slot->used;
    slot->socket = socket;
    if (new_slot) {
        slot->active_tag = NULL;
        slot->active_events = 0u;
        slot->active_used = false;
        slot->staged_read_registered = false;
        slot->staged_write_registered = false;
    }
    slot->tag = tag;
    slot->events = events;
    slot->used = true;
    /* kqueue udata carries the slot so wait() needs no lookup. */
    if (kq_sync_filters(loop, slot)) {
        if (loop->pending_count == 0u) {
            slot->active_tag = slot->tag;
            slot->active_events = slot->events;
            slot->active_used = slot->used;
        }
        return true;
    }
    slot->tag = old_tag;
    slot->events = old_events;
    slot->used = old_used;
    if (new_slot) {
        free(slot);
        loop->slots[idx] = NULL;
        loop->slot_count--;
    }
    return false;
}

bool net_loop_modify(NetLoop *loop, NetSocket *socket, u32 events)
{
    if (!loop || !socket || !net_loop_interest_valid(events)) return false;
    u32 idx = kq_find_slot(loop, socket);
    if (idx == UINT32_MAX) return false;
    NetLoopSlot *slot = loop->slots[idx];
    u32 old_events = slot->events;
    slot->events = events;
    if (kq_sync_filters(loop, slot)) {
        if (loop->pending_count == 0u) {
            slot->active_events = slot->events;
        }
        return true;
    }
    slot->events = old_events;
    return false;
}

bool net_loop_remove(NetLoop *loop, NetSocket *socket)
{
    if (!loop || !socket) return false;
    u32 idx = kq_find_slot(loop, socket);
    if (idx == UINT32_MAX) return false;
    NetLoopSlot *slot = loop->slots[idx];
    u32 old_events = slot->events;
    bool old_used = slot->used;
    slot->events = 0u;
    slot->used = false;
    bool ok = kq_sync_filters(loop, slot);
    if (!ok) {
        slot->events = old_events;
        slot->used = old_used;
        return false;
    }
    /* Commit the deletes before the slot dies so no kernel-queued event can
     * reference it; events already delivered to userspace are dropped in
     * wait() via the used flag. */
    ok = kq_flush(loop) && ok;
    if (!ok) return false;
    slot->socket = NULL;
    slot->read_registered = false;
    slot->write_registered = false;
    return true;
}

i32 net_loop_wait(NetLoop *loop, NetLoopEvent *out, u32 max, i32 timeout_ms)
{
    if (!loop || !out || !net_loop_wait_count_valid(max)) return NET_ERROR;
    if (!kq_flush(loop)) return NET_ERROR;

    if (!kq_ensure_wait_capacity(loop, max)) return NET_ERROR;

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

#if !defined(ENGINE_PLATFORM_MACOS) && !defined(ENGINE_PLATFORM_IOS) && !defined(__APPLE__)
typedef int net_loop_kqueue_translation_unit;
#endif
