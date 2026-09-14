/*
 * net_loop_epoll.c — Linux backend for net_loop, built on epoll.
 *
 * Throughput choices:
 *   - EPOLLET edge-triggered readiness: an event is reported once per
 *     transition; callers drain sockets fully, the optimal batch pattern.
 *   - epoll_wait returns a batch of events in one syscall.
 *   - eventfd implements cross-thread wakeup with a single fd.
 *
 * NOTE: this file is written on macOS without Linux headers; it has not been
 * compile-verified locally. It targets the epoll(7) interface documented in
 * Linux man pages (epoll_create1/epoll_ctl/epoll_wait/eventfd).
 */

#if (defined(ENGINE_PLATFORM_LINUX) || defined(ENGINE_PLATFORM_ANDROID) || \
     defined(ENGINE_PLATFORM_HARMONYOS)) && !defined(ENGINE_NET_IOURING)

#include "net_loop.h"

#include <sys/epoll.h>
#include <sys/eventfd.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

typedef struct {
    NetSocket *socket;
    void      *tag;
    u32        events;
    bool       used;
} NetLoopSlot;

struct NetLoop {
    int          epfd;
    int          wake_fd;
    NetLoopSlot **slots;
    u32          slot_count;
    u32          slot_cap;
    struct epoll_event *wait_events;
    u32          wait_cap;
#if defined(ENGINE_NET_LOOP_TESTING)
    bool         fail_next_ctl;
#endif
};

static u32 ep_find_slot(const NetLoop *loop, NetSocket *socket)
{
    for (u32 i = 0; i < loop->slot_count; i++) {
        if (loop->slots[i]->used && loop->slots[i]->socket == socket) return i;
    }
    return UINT32_MAX;
}

static u32 ep_native_events(u32 events)
{
    u32 e = EPOLLET;
    if (events & NET_LOOP_READ)  e |= EPOLLIN;
    if (events & NET_LOOP_WRITE) e |= EPOLLOUT;
    return e;
}

static bool ep_next_capacity(u32 current, u32 required, u32 *next)
{
    u32 capacity = current ? current : 16u;
    while (capacity < required) {
        if (capacity > UINT32_MAX / 2u) return false;
        capacity *= 2u;
    }
    size_t bytes = (size_t)capacity * sizeof(*((NetLoop *)0)->slots);
    if (bytes / sizeof(*((NetLoop *)0)->slots) != (size_t)capacity) {
        return false;
    }
    *next = capacity;
    return true;
}

static bool ep_ensure_capacity(NetLoop *loop, u32 required)
{
    if (required <= loop->slot_cap) return true;

    u32 new_cap;
    if (!ep_next_capacity(loop->slot_cap, required, &new_cap)) return false;
    NetLoopSlot **slots = (NetLoopSlot **)realloc(
        loop->slots, (size_t)new_cap * sizeof(*slots));
    if (!slots) return false;
    memset(slots + loop->slot_cap, 0,
           (size_t)(new_cap - loop->slot_cap) * sizeof(*slots));
    loop->slots = slots;
    loop->slot_cap = new_cap;
    return true;
}

static int ep_ctl(NetLoop *loop, int op, int fd, struct epoll_event *event)
{
#if defined(ENGINE_NET_LOOP_TESTING)
    if (loop->fail_next_ctl) {
        loop->fail_next_ctl = false;
        errno = EIO;
        return -1;
    }
#endif
    return epoll_ctl(loop->epfd, op, fd, event);
}

#if defined(ENGINE_NET_LOOP_TESTING)
void net_loop_epoll_test_fail_next_ctl(NetLoop *loop)
{
    if (loop) loop->fail_next_ctl = true;
}

bool net_loop_epoll_test_next_capacity(u32 current, u32 required, u32 *next)
{
    return next && ep_next_capacity(current, required, next);
}
#endif

NetLoop *net_loop_create(void)
{
    NetLoop *loop = (NetLoop *)calloc(1, sizeof(*loop));
    if (!loop) return NULL;
    loop->epfd = epoll_create1(EPOLL_CLOEXEC);
    if (loop->epfd < 0) {
        free(loop);
        return NULL;
    }
    loop->wake_fd = eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
    if (loop->wake_fd < 0) {
        close(loop->epfd);
        free(loop);
        return NULL;
    }
    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.events = EPOLLIN;
    ev.data.ptr = NULL; /* distinguishes wakeup from socket events */
    if (epoll_ctl(loop->epfd, EPOLL_CTL_ADD, loop->wake_fd, &ev) < 0) {
        close(loop->wake_fd);
        close(loop->epfd);
        free(loop);
        return NULL;
    }
    return loop;
}

void net_loop_destroy(NetLoop *loop)
{
    if (!loop) return;
    if (loop->wake_fd >= 0) close(loop->wake_fd);
    if (loop->epfd >= 0) close(loop->epfd);
    for (u32 i = 0; i < loop->slot_count; i++) free(loop->slots[i]);
    free(loop->slots);
    free(loop->wait_events);
    free(loop);
}

bool net_loop_add(NetLoop *loop, NetSocket *socket, u32 events, void *tag)
{
    if (!loop || !socket || !net_loop_interest_valid(events)) return false;
    intptr_t fd = net_socket_native_handle(socket);
    if (fd < 0) return false;

    u32 idx = ep_find_slot(loop, socket);
    int op = EPOLL_CTL_ADD;
    if (idx == UINT32_MAX) {
        if (loop->slot_count == UINT32_MAX ||
            !ep_ensure_capacity(loop, loop->slot_count + 1u)) return false;
        NetLoopSlot *slot = (NetLoopSlot *)calloc(1, sizeof(*slot));
        if (!slot) return false;
        idx = loop->slot_count;
        loop->slots[idx] = slot;
    } else {
        op = EPOLL_CTL_MOD;
    }
    NetLoopSlot *slot = loop->slots[idx];

    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.events = ep_native_events(events);
    ev.data.ptr = slot;
    if (ep_ctl(loop, op, (int)fd, &ev) < 0) {
        if (op == EPOLL_CTL_ADD) {
            free(slot);
            loop->slots[idx] = NULL;
        }
        return false;
    }
    slot->socket = socket;
    slot->tag = tag;
    slot->events = events;
    slot->used = true;
    if (op == EPOLL_CTL_ADD) loop->slot_count++;
    return true;
}

bool net_loop_modify(NetLoop *loop, NetSocket *socket, u32 events)
{
    if (!loop || !socket || !net_loop_interest_valid(events)) return false;
    u32 idx = ep_find_slot(loop, socket);
    if (idx == UINT32_MAX) return false;
    intptr_t fd = net_socket_native_handle(socket);
    if (fd < 0) return false;
    NetLoopSlot *slot = loop->slots[idx];
    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.events = ep_native_events(events);
    ev.data.ptr = slot;
    if (ep_ctl(loop, EPOLL_CTL_MOD, (int)fd, &ev) < 0) return false;
    slot->events = events;
    return true;
}

bool net_loop_remove(NetLoop *loop, NetSocket *socket)
{
    if (!loop || !socket) return false;
    u32 idx = ep_find_slot(loop, socket);
    if (idx == UINT32_MAX) return false;
    intptr_t fd = net_socket_native_handle(socket);
    bool ok = true;
    if (fd >= 0) {
        /* Linux >= 2.6.9 allows a NULL event pointer for EPOLL_CTL_DEL. */
        ok = ep_ctl(loop, EPOLL_CTL_DEL, (int)fd, NULL) == 0;
    }
    loop->slots[idx]->used = false;
    loop->slots[idx]->socket = NULL;
    return ok;
}

i32 net_loop_wait(NetLoop *loop, NetLoopEvent *out, u32 max, i32 timeout_ms)
{
    if (!loop || !out || !net_loop_wait_count_valid(max)) return NET_ERROR;
    if (max > loop->wait_cap) {
        struct epoll_event *events = (struct epoll_event *)realloc(
            loop->wait_events, (size_t)max * sizeof(*events));
        if (!events) return NET_ERROR;
        loop->wait_events = events;
        loop->wait_cap = max;
    }

    int n;
    do {
        n = epoll_wait(loop->epfd, loop->wait_events, (int)max, timeout_ms);
    } while (n < 0 && errno == EINTR);
    if (n < 0) return NET_ERROR;

    i32 count = 0;
    for (int i = 0; i < n; i++) {
        NetLoopSlot *slot = (NetLoopSlot *)loop->wait_events[i].data.ptr;
        if (!slot) {
            /* Wakeup: drain the eventfd counter (edge cases: repeated wakes). */
            u64 discard;
            while (read(loop->wake_fd, &discard, sizeof(discard)) ==
                   (ssize_t)sizeof(discard)) {}
            continue;
        }
        if (!slot->used) continue; /* removed since the event queued */
        u32 events = 0;
        if (loop->wait_events[i].events & EPOLLIN)                 events |= NET_LOOP_READ;
        if (loop->wait_events[i].events & EPOLLOUT)                events |= NET_LOOP_WRITE;
        if (loop->wait_events[i].events & (EPOLLERR | EPOLLHUP))   events |= NET_LOOP_ERROR;
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
    if (!loop || loop->wake_fd < 0) return;
    u64 one = 1;
    (void)!write(loop->wake_fd, &one, sizeof(one)); /* EAGAIN on full counter is fine */
}

#endif /* ENGINE_PLATFORM_LINUX && !ENGINE_NET_IOURING */
