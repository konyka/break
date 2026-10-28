/*
 * net_loop_poll.c — QNX Neutrino backend for net_loop, built on POSIX poll().
 *
 * QNX Neutrino has neither epoll nor kqueue; poll() is the native readiness
 * mechanism, so throughput work goes where poll allows it:
 *   - The interest set lives in userspace slots; the pollfd array is rebuilt
 *     only after a registration change (dirty flag), so a steady-state wait()
 *     performs exactly one poll() syscall with no array reconstruction.
 *   - poll() returns a batch of ready descriptors in one syscall.
 *   - A non-blocking pipe implements cross-thread wakeup; wakeup() is a single
 *     write(), safe to call from signal handlers on POSIX targets.
 *
 * Semantics are level-triggered (inherent to poll): every wait reports every
 * currently-ready socket. Callers that drain sockets fully per wakeup — the
 * documented high-throughput pattern for the edge-triggered backends — are
 * optimal here as well.
 */

#if defined(ENGINE_PLATFORM_QNX)

#include "net_loop.h"

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <poll.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    NetSocket *socket;
    void      *tag;
    intptr_t   fd;
    u32        events;
    bool       used;
} NetLoopSlot;

struct NetLoop {
    int           wake_read;
    int           wake_write;
    NetLoopSlot **slots;
    u32           slot_count;
    u32           slot_cap;
    struct pollfd *pfds;        /* [0] = wake pipe, [1..] = live slots */
    NetLoopSlot  **pfd_slots;   /* pfd_slots[i] owns pfds[i], [0] = NULL */
    u32           pfd_count;    /* 1 + live slots at last rebuild */
    u32           pfd_cap;
    bool          dirty;
#if defined(ENGINE_NET_LOOP_TESTING)
    bool          fail_next_poll;
#endif
};

static u32 po_find_slot(const NetLoop *loop, NetSocket *socket)
{
    for (u32 i = 0; i < loop->slot_count; i++) {
        if (loop->slots[i]->used && loop->slots[i]->socket == socket) return i;
    }
    return UINT32_MAX;
}

static u32 po_next_capacity(u32 current, u32 required, u32 *next)
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

static bool po_ensure_slot_capacity(NetLoop *loop, u32 required)
{
    if (required <= loop->slot_cap) return true;

    u32 new_cap;
    if (!po_next_capacity(loop->slot_cap, required, &new_cap)) return false;
    NetLoopSlot **slots = (NetLoopSlot **)realloc(
        loop->slots, (size_t)new_cap * sizeof(*slots));
    if (!slots) return false;
    memset(slots + loop->slot_cap, 0,
           (size_t)(new_cap - loop->slot_cap) * sizeof(*slots));
    loop->slots = slots;
    loop->slot_cap = new_cap;
    return true;
}

static bool po_ensure_pfd_capacity(NetLoop *loop, u32 required)
{
    if (required <= loop->pfd_cap) return true;

    u32 new_cap;
    if (!po_next_capacity(loop->pfd_cap, required, &new_cap)) return false;
    struct pollfd *pfds = (struct pollfd *)realloc(
        loop->pfds, (size_t)new_cap * sizeof(*pfds));
    if (!pfds) return false;
    loop->pfds = pfds;
    NetLoopSlot **pfd_slots = (NetLoopSlot **)realloc(
        loop->pfd_slots, (size_t)new_cap * sizeof(*pfd_slots));
    if (!pfd_slots) return false;
    loop->pfd_slots = pfd_slots;
    loop->pfd_cap = new_cap;
    return true;
}

/* Rebuild the pollfd array from live slots. Wait is loop-thread-affine with
 * add/modify/remove, so the slot <-> pfd mapping stays valid until the next
 * registration change re-marks the loop dirty. */
static bool po_rebuild(NetLoop *loop)
{
    u32 live = 0;
    for (u32 i = 0; i < loop->slot_count; i++) {
        if (loop->slots[i]->used) live++;
    }
    if (!po_ensure_pfd_capacity(loop, live + 1u)) return false;

    loop->pfds[0].fd = loop->wake_read;
    loop->pfds[0].events = POLLIN;
    loop->pfds[0].revents = 0;
    loop->pfd_slots[0] = NULL;
    u32 n = 1;
    for (u32 i = 0; i < loop->slot_count; i++) {
        NetLoopSlot *slot = loop->slots[i];
        if (!slot->used) continue;
        short ev = 0;
        if (slot->events & NET_LOOP_READ)  ev |= POLLIN;
        if (slot->events & NET_LOOP_WRITE) ev |= POLLOUT;
        loop->pfds[n].fd = (int)slot->fd;
        loop->pfds[n].events = ev;
        loop->pfds[n].revents = 0;
        loop->pfd_slots[n] = slot;
        n++;
    }
    loop->pfd_count = n;
    loop->dirty = false;
    return true;
}

static bool po_set_nonblocking(int fd)
{
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags < 0) return false;
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK) == 0;
}

#if defined(ENGINE_NET_LOOP_TESTING)
void net_loop_poll_test_fail_next_poll(NetLoop *loop)
{
    if (loop) loop->fail_next_poll = true;
}

bool net_loop_poll_test_next_capacity(u32 current, u32 required, u32 *next)
{
    return next && po_next_capacity(current, required, next);
}
#endif

NetLoop *net_loop_create(void)
{
    NetLoop *loop = (NetLoop *)calloc(1, sizeof(*loop));
    if (!loop) return NULL;
    loop->wake_read = -1;
    loop->wake_write = -1;

    int fds[2];
    if (pipe(fds) != 0) {
        free(loop);
        return NULL;
    }
    if (!po_set_nonblocking(fds[0]) || !po_set_nonblocking(fds[1])) {
        close(fds[0]);
        close(fds[1]);
        free(loop);
        return NULL;
    }
    loop->wake_read = fds[0];
    loop->wake_write = fds[1];
    loop->dirty = true;
    return loop;
}

void net_loop_destroy(NetLoop *loop)
{
    if (!loop) return;
    if (loop->wake_read >= 0) close(loop->wake_read);
    if (loop->wake_write >= 0) close(loop->wake_write);
    for (u32 i = 0; i < loop->slot_count; i++) free(loop->slots[i]);
    free(loop->slots);
    free(loop->pfds);
    free(loop->pfd_slots);
    free(loop);
}

bool net_loop_add(NetLoop *loop, NetSocket *socket, u32 events, void *tag)
{
    if (!loop || !socket || !net_loop_interest_valid(events)) return false;
    intptr_t fd = net_socket_native_handle(socket);
    if (fd < 0) return false;

    u32 idx = po_find_slot(loop, socket);
    if (idx == UINT32_MAX) {
        if (loop->slot_count == UINT32_MAX ||
            !po_ensure_slot_capacity(loop, loop->slot_count + 1u)) return false;
        NetLoopSlot *slot = (NetLoopSlot *)calloc(1, sizeof(*slot));
        if (!slot) return false;
        idx = loop->slot_count;
        loop->slots[idx] = slot;
        loop->slot_count++;
        slot->socket = socket;
        slot->fd = fd;
    }
    NetLoopSlot *slot = loop->slots[idx];
    /* poll keeps no kernel registration: an add on a known socket is a plain
     * userspace interest/tag update (add aliases modify). */
    slot->tag = tag;
    slot->events = events;
    slot->used = true;
    loop->dirty = true;
    return true;
}

bool net_loop_modify(NetLoop *loop, NetSocket *socket, u32 events)
{
    if (!loop || !socket || !net_loop_interest_valid(events)) return false;
    u32 idx = po_find_slot(loop, socket);
    if (idx == UINT32_MAX) return false;
    loop->slots[idx]->events = events;
    loop->dirty = true;
    return true;
}

bool net_loop_remove(NetLoop *loop, NetSocket *socket)
{
    if (!loop || !socket) return false;
    u32 idx = po_find_slot(loop, socket);
    if (idx == UINT32_MAX) return false;
    NetLoopSlot *slot = loop->slots[idx];
    slot->used = false;
    slot->socket = NULL;
    slot->fd = -1;
    loop->dirty = true;
    return true;
}

i32 net_loop_wait(NetLoop *loop, NetLoopEvent *out, u32 max, i32 timeout_ms)
{
    if (!loop || !out || !net_loop_wait_count_valid(max)) return NET_ERROR;
    if (loop->dirty && !po_rebuild(loop)) return NET_ERROR;

    int n;
    do {
#if defined(ENGINE_NET_LOOP_TESTING)
        if (loop->fail_next_poll) {
            loop->fail_next_poll = false;
            n = -1;
            errno = EIO;
            break;
        }
#endif
        n = poll(loop->pfds, (nfds_t)loop->pfd_count, timeout_ms);
    } while (n < 0 && errno == EINTR);
    if (n < 0) return NET_ERROR;

    i32 count = 0;
    u32 scanned = 0;
    for (u32 i = 0; i < loop->pfd_count && scanned < (u32)n && count < (i32)max;
         i++) {
        short re = loop->pfds[i].revents;
        if (re == 0) continue;
        scanned++;
        if (i == 0) {
            /* Wakeup: drain the pipe (a full pipe still means one pending wake). */
            char discard[64];
            while (read(loop->wake_read, discard, sizeof(discard)) ==
                   (ssize_t)sizeof(discard)) {}
            continue;
        }
        NetLoopSlot *slot = loop->pfd_slots[i];
        /* The mapping is stable during wait (loop-thread affinity), but a slot
         * removed after the last rebuild can still linger in the stale array
         * until po_rebuild runs again — recheck liveness. */
        if (!slot || !slot->used) continue;
        u32 events = 0;
        if (re & POLLIN)  events |= NET_LOOP_READ;
        if (re & POLLOUT) events |= NET_LOOP_WRITE;
        if (re & (POLLERR | POLLHUP | POLLNVAL)) events |= NET_LOOP_ERROR;
        if (events == 0) continue;
        out[count].socket = slot->socket;
        out[count].events = events;
        out[count].tag = slot->tag;
        count++;
    }
    return count;
}

void net_loop_wakeup(NetLoop *loop)
{
    if (!loop || loop->wake_write < 0) return;
    u8 one = 1;
    /* EAGAIN on a full pipe is fine: a wake is already pending. */
    (void)!write(loop->wake_write, &one, sizeof(one));
}

#endif /* ENGINE_PLATFORM_QNX */
