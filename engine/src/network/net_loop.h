#ifndef NET_LOOP_H
#define NET_LOOP_H

/*
 * net_loop.h — Platform-optimal high-throughput event notification.
 *
 * Replaces net_poll()-style scanning with the OS's native readiness /
 * completion mechanism, selected at compile time (no function pointers):
 *
 *   macOS    kqueue   (net_loop_kqueue.c)   — EV_CLEAR edge semantics,
 *                                             batched changelist registration
 *   Linux    epoll    (net_loop_epoll.c)    — EPOLLET edge-triggered,
 *                                             batched epoll_wait
 *   Linux    io_uring (net_loop_iouring.c)  — optional, ENGINE_NET_IOURING=ON
 *   Windows  IOCP     (net_loop_iocp.c)     — overlapped zero-byte peek recv
 *                                             mapped to readiness
 *
 * All backends expose readiness semantics: NET_LOOP_READ means a non-blocking
 * recvfrom/recv will not return EWOULDBLOCK right now; NET_LOOP_WRITE means a
 * non-blocking send will proceed. Edge-triggered backends (kqueue EV_CLEAR,
 * epoll EPOLLET) require the caller to drain the socket fully on each event —
 * which is also the high-throughput pattern (one wakeup, one batch drain).
 *
 * Batching: net_loop_wait fills a caller-provided array, so a single syscall
 * returns many events; add/modify/remove on the kqueue backend are staged
 * into one kevent() call when possible.
 */

#include "../core/types.h"
#include "network.h"

#define NET_LOOP_READ  1u
#define NET_LOOP_WRITE 2u
#define NET_LOOP_ERROR 4u
#define NET_LOOP_INTEREST_MASK (NET_LOOP_READ | NET_LOOP_WRITE)
#define NET_LOOP_MAX_EVENTS 65536u

static inline bool net_loop_interest_valid(u32 events)
{
    return events != 0u && (events & ~NET_LOOP_INTEREST_MASK) == 0u;
}

static inline bool net_loop_wait_count_valid(u32 max)
{
    return max != 0u && max <= NET_LOOP_MAX_EVENTS;
}

typedef struct NetLoop NetLoop;

typedef struct {
    NetSocket *socket;
    u32        events;   /* fired events, bitmask of NET_LOOP_* */
    void      *tag;      /* opaque user pointer supplied to net_loop_add */
} NetLoopEvent;

NetLoop *net_loop_create(void);
void     net_loop_destroy(NetLoop *loop);

/* Register/unregister. Interest masks must contain at least READ or WRITE and
 * no output-only flags such as ERROR; invalid masks are rejected without
 * changing an existing registration. tag is echoed back in NetLoopEvent; the loop does not
 * own the socket — callers must remove it before closing. add() on an
 * already-registered socket acts like modify(). */
bool net_loop_add(NetLoop *loop, NetSocket *socket, u32 events, void *tag);
bool net_loop_modify(NetLoop *loop, NetSocket *socket, u32 events);
bool net_loop_remove(NetLoop *loop, NetSocket *socket);

/* Wait for events; fills out[0..max) and returns the event count, 0 on
 * timeout or wakeup-with-no-events, NET_ERROR on failure. */
i32 net_loop_wait(NetLoop *loop, NetLoopEvent *out, u32 max, i32 timeout_ms);

/* Wake another thread blocked in net_loop_wait (thread-safe, signal-safe
 * on POSIX backends). */
void net_loop_wakeup(NetLoop *loop);

#endif /* NET_LOOP_H */
