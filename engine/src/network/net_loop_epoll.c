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
    NetLoopSlot *slots;
    u32          slot_count;
    u32          slot_cap;
    struct epoll_event *wait_events;
    u32          wait_cap;
};

static u32 ep_find_slot(const NetLoop *loop, NetSocket *socket)
{
    for (u32 i = 0; i < loop->slot_count; i++) {
        if (loop->slots[i].used && loop->slots[i].socket == socket) return i;
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
        if (loop->slot_count == loop->slot_cap) {
            u32 new_cap = loop->slot_cap ? loop->slot_cap * 2u : 16u;
            NetLoopSlot *ns = realloc(loop->slots, new_cap * sizeof(*ns));
            if (!ns) return false;
            memset(ns + loop->slot_cap, 0,
                   (new_cap - loop->slot_cap) * sizeof(*ns));
            loop->slots = ns;
            loop->slot_cap = new_cap;
            /* realloc moved the slots; re-MOD every live registration so
             * epoll's data.ptr tracks the new addresses. */
            for (u32 i = 0; i < loop->slot_count; i++) {
                if (!loop->slots[i].used) continue;
                struct epoll_event rev;
                memset(&rev, 0, sizeof(rev));
                rev.events = ep_native_events(loop->slots[i].events);
                rev.data.ptr = &loop->slots[i];
                intptr_t rfd = net_socket_native_handle(loop->slots[i].socket);
                if (rfd >= 0) {
                    (void)epoll_ctl(loop->epfd, EPOLL_CTL_MOD, (int)rfd, &rev);
                }
            }
        }
        idx = loop->slot_count++;
        loop->slots[idx].used = false;
    } else {
        op = EPOLL_CTL_MOD;
    }
    loop->slots[idx].socket = socket;
    loop->slots[idx].tag = tag;
    loop->slots[idx].events = events;
    loop->slots[idx].used = true;

    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.events = ep_native_events(events);
    ev.data.ptr = &loop->slots[idx];
    if (epoll_ctl(loop->epfd, op, (int)fd, &ev) < 0) return false;
    return true;
}

bool net_loop_modify(NetLoop *loop, NetSocket *socket, u32 events)
{
    if (!loop || !socket || !net_loop_interest_valid(events)) return false;
    u32 idx = ep_find_slot(loop, socket);
    if (idx == UINT32_MAX) return false;
    loop->slots[idx].events = events;
    intptr_t fd = net_socket_native_handle(socket);
    if (fd < 0) return false;
    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.events = ep_native_events(events);
    ev.data.ptr = &loop->slots[idx];
    return epoll_ctl(loop->epfd, EPOLL_CTL_MOD, (int)fd, &ev) == 0;
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
        ok = epoll_ctl(loop->epfd, EPOLL_CTL_DEL, (int)fd, NULL) == 0;
    }
    loop->slots[idx].used = false;
    loop->slots[idx].socket = NULL;
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
