/*
 * net_loop_iouring.c — experimental io_uring backend for net_loop (Linux).
 *
 * Enabled only with -DENGINE_NET_IOURING=ON. Uses raw syscalls (no liburing
 * dependency) and IORING_OP_POLL_ADD multishot polls to deliver readiness
 * completions, so the net_loop readiness semantics are preserved while event
 * retrieval rides the io_uring CQ ring (no per-event syscall, batched reap).
 *
 * Wakeup: an eventfd is registered with its own multishot poll; writing to it
 * wakes a blocked io_uring_enter(GETEVENTS).
 *
 * NOTE: cannot be compile-verified on macOS. Targets the io_uring ABI as
 * documented in <linux/io_uring.h> (kernel >= 5.6 for multishot poll).
 */

#if defined(ENGINE_PLATFORM_LINUX) && defined(ENGINE_NET_IOURING)

#include "net_loop.h"

#include <linux/io_uring.h>
#include <sys/eventfd.h>
#include <sys/mman.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <poll.h>

#ifndef SYS_io_uring_setup
#  define SYS_io_uring_setup __NR_io_uring_setup
#endif

/* Strict POSIX feature macros hide the variadic syscall declaration. */
extern long syscall(long number, ...);

struct iouring_ring {
    unsigned *head, *tail, *ring_mask, *ring_entries, *flags, *array;
    struct io_uring_sqe *sqes;
    unsigned *cq_head, *cq_tail, *cq_ring_mask, *cq_ring_entries;
    struct io_uring_cqe *cqes;
    void *sq_ptr, *cq_ptr;
    size_t sq_sz, cq_sz;
    size_t sqes_sz;
};

typedef struct {
    NetSocket *socket;
    void      *tag;
    u32        events;
    u32        generation;
    bool       used;
    bool       polled;   /* multishot poll currently armed */
} NetLoopSlot;

struct NetLoop {
    int                 ring_fd;
    int                 wake_fd;
    struct iouring_ring ring;
    NetLoopSlot        *slots;
    u32                 slot_count;
    u32                 slot_cap;
    /* Timeout SQE target; must outlive the wait (stack lifetime is too short
     * if the completion is reaped by a later wait call). */
    struct __kernel_timespec timeout_ts;
};

/* ---- raw io_uring plumbing ---- */

static int uring_setup(unsigned entries, struct io_uring_params *p)
{
    return (int)syscall(SYS_io_uring_setup, entries, p);
}

static int uring_enter(int ring_fd, unsigned to_submit, unsigned min_complete,
                       unsigned flags)
{
    return (int)syscall(__NR_io_uring_enter, ring_fd, to_submit, min_complete,
                        flags, NULL, (size_t)0);
}

static bool uring_map(struct NetLoop *loop, unsigned entries)
{
    struct io_uring_params p;
    memset(&p, 0, sizeof(p));
    int fd = uring_setup(entries, &p);
    if (fd < 0) return false;
    loop->ring_fd = fd;

    struct iouring_ring *r = &loop->ring;
    r->sq_sz = p.sq_off.array + p.sq_entries * sizeof(unsigned);
    r->cq_sz = p.cq_off.cqes + p.cq_entries * sizeof(struct io_uring_cqe);
    if (p.features & IORING_FEAT_SINGLE_MMAP) {
        if (r->cq_sz > r->sq_sz) r->sq_sz = r->cq_sz;
        r->cq_sz = r->sq_sz;
    }
    r->sq_ptr = mmap(0, r->sq_sz, PROT_READ | PROT_WRITE,
                     MAP_SHARED | MAP_POPULATE, fd, IORING_OFF_SQ_RING);
    if (r->sq_ptr == MAP_FAILED) {
        r->sq_ptr = NULL;
        close(fd);
        loop->ring_fd = -1;
        return false;
    }
    if (p.features & IORING_FEAT_SINGLE_MMAP) {
        r->cq_ptr = r->sq_ptr;
    } else {
        r->cq_ptr = mmap(0, r->cq_sz, PROT_READ | PROT_WRITE,
                         MAP_SHARED | MAP_POPULATE, fd, IORING_OFF_CQ_RING);
        if (r->cq_ptr == MAP_FAILED) {
            r->cq_ptr = NULL;
            munmap(r->sq_ptr, r->sq_sz);
            r->sq_ptr = NULL;
            close(fd);
            loop->ring_fd = -1;
            return false;
        }
    }
    r->sqes_sz = p.sq_entries * sizeof(struct io_uring_sqe);
    r->sqes = mmap(0, r->sqes_sz,
                   PROT_READ | PROT_WRITE, MAP_SHARED | MAP_POPULATE,
                   fd, IORING_OFF_SQES);
    if (r->sqes == MAP_FAILED) {
        r->sqes = NULL;
        if (r->cq_ptr && r->cq_ptr != r->sq_ptr) {
            munmap(r->cq_ptr, r->cq_sz);
            r->cq_ptr = NULL;
        }
        munmap(r->sq_ptr, r->sq_sz);
        r->sq_ptr = NULL;
        close(fd);
        loop->ring_fd = -1;
        return false;
    }

    r->head         = (unsigned *)((char *)r->sq_ptr + p.sq_off.head);
    r->tail         = (unsigned *)((char *)r->sq_ptr + p.sq_off.tail);
    r->ring_mask    = (unsigned *)((char *)r->sq_ptr + p.sq_off.ring_mask);
    r->ring_entries = (unsigned *)((char *)r->sq_ptr + p.sq_off.ring_entries);
    r->flags        = (unsigned *)((char *)r->sq_ptr + p.sq_off.flags);
    r->array        = (unsigned *)((char *)r->sq_ptr + p.sq_off.array);
    r->cq_head         = (unsigned *)((char *)r->cq_ptr + p.cq_off.head);
    r->cq_tail         = (unsigned *)((char *)r->cq_ptr + p.cq_off.tail);
    r->cq_ring_mask    = (unsigned *)((char *)r->cq_ptr + p.cq_off.ring_mask);
    r->cq_ring_entries = (unsigned *)((char *)r->cq_ptr + p.cq_off.ring_entries);
    r->cqes = (struct io_uring_cqe *)((char *)r->cq_ptr + p.cq_off.cqes);
    return true;
}

static struct io_uring_sqe *uring_get_sqe(struct NetLoop *loop)
{
    struct iouring_ring *r = &loop->ring;
    unsigned tail = *r->tail;
    unsigned next = tail + 1u;
    if (next - *r->head > *r->ring_entries) return NULL; /* SQ full */
    struct io_uring_sqe *sqe = &r->sqes[tail & *r->ring_mask];
    memset(sqe, 0, sizeof(*sqe));
    r->array[tail & *r->ring_mask] = tail & *r->ring_mask;
    __atomic_store_n(r->tail, next, __ATOMIC_RELEASE);
    return sqe;
}

static u32 poll_mask_for(u32 events)
{
    u32 m = 0;
    if (events & NET_LOOP_READ)  m |= POLLIN;
    if (events & NET_LOOP_WRITE) m |= POLLOUT;
    return m;
}

static u64 uring_slot_token(u32 index, u32 generation)
{
    return ((u64)generation << 32) | (u64)(index + 3u);
}

static bool uring_cancel_poll(NetLoop *loop, u32 index, u32 generation)
{
    struct io_uring_sqe *sqe = uring_get_sqe(loop);
    if (!sqe) return false;
    sqe->opcode = IORING_OP_POLL_REMOVE;
    sqe->addr = uring_slot_token(index, generation);
    sqe->user_data = 1u; /* control op, never surfaced */
    return uring_enter(loop->ring_fd, 1, 0, 0) >= 0;
}

static bool uring_arm_poll(NetLoop *loop, NetLoopSlot *slot, u32 index,
                           intptr_t fd)
{
    struct io_uring_sqe *sqe = uring_get_sqe(loop);
    if (!sqe) return false;
    sqe->opcode = IORING_OP_POLL_ADD;
    sqe->fd = (int)fd;
    sqe->poll32_events = poll_mask_for(slot->events);
    sqe->user_data = uring_slot_token(index, slot->generation);
    /* IORING_POLL_ADD_MULTI for multishot (stays armed after each event). */
    sqe->len = IORING_POLL_ADD_MULTI;
    return uring_enter(loop->ring_fd, 1, 0, 0) >= 0;
}

/* ---- net_loop API ---- */

static u32 ur_find_slot(const NetLoop *loop, NetSocket *socket)
{
    for (u32 i = 0; i < loop->slot_count; i++) {
        if (loop->slots[i].used && loop->slots[i].socket == socket) return i;
    }
    return UINT32_MAX;
}

NetLoop *net_loop_create(void)
{
    NetLoop *loop = (NetLoop *)calloc(1, sizeof(*loop));
    if (!loop) return NULL;
    loop->ring_fd = -1;
    loop->wake_fd = -1;
    if (!uring_map(loop, 64u)) {
        free(loop);
        return NULL;
    }
    loop->wake_fd = eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
    if (loop->wake_fd < 0) {
        net_loop_destroy(loop);
        return NULL;
    }
    /* Multishot poll on the wakeup eventfd; user_data == 0 marks wakeup. */
    struct io_uring_sqe *sqe = uring_get_sqe(loop);
    if (!sqe) {
        net_loop_destroy(loop);
        return NULL;
    }
    sqe->opcode = IORING_OP_POLL_ADD;
    sqe->fd = loop->wake_fd;
    sqe->poll32_events = POLLIN;
    sqe->user_data = 0;
    sqe->len = IORING_POLL_ADD_MULTI;
    if (uring_enter(loop->ring_fd, 1, 0, 0) < 0) {
        net_loop_destroy(loop);
        return NULL;
    }
    return loop;
}

void net_loop_destroy(NetLoop *loop)
{
    if (!loop) return;
    struct iouring_ring *r = &loop->ring;
    if (r->sq_ptr && r->sq_ptr != MAP_FAILED) munmap(r->sq_ptr, r->sq_sz);
    if (r->cq_ptr && r->cq_ptr != MAP_FAILED && r->cq_ptr != r->sq_ptr)
        munmap(r->cq_ptr, r->cq_sz);
    if (r->sqes && r->sqes != MAP_FAILED)
        munmap(r->sqes, r->sqes_sz);
    if (loop->wake_fd >= 0) close(loop->wake_fd);
    if (loop->ring_fd >= 0) close(loop->ring_fd);
    free(loop->slots);
    free(loop);
}

bool net_loop_add(NetLoop *loop, NetSocket *socket, u32 events, void *tag)
{
    if (!loop || !socket || !net_loop_interest_valid(events)) return false;
    intptr_t fd = net_socket_native_handle(socket);
    if (fd < 0) return false;

    u32 idx = ur_find_slot(loop, socket);
    if (idx == UINT32_MAX) {
        if (loop->slot_count == loop->slot_cap) {
            u32 new_cap = loop->slot_cap ? loop->slot_cap * 2u : 16u;
            NetLoopSlot *ns = realloc(loop->slots, new_cap * sizeof(*ns));
            if (!ns) return false;
            memset(ns + loop->slot_cap, 0,
                   (new_cap - loop->slot_cap) * sizeof(*ns));
            loop->slots = ns;
            loop->slot_cap = new_cap;
        }
        idx = loop->slot_count++;
        loop->slots[idx].used = false;
        loop->slots[idx].polled = false;
        loop->slots[idx].generation = 1u;
    }
    loop->slots[idx].socket = socket;
    loop->slots[idx].tag = tag;
    loop->slots[idx].events = events;
    loop->slots[idx].used = true;
    if (loop->slots[idx].polled) {
        /* Re-arm with the new mask. */
        if (!uring_cancel_poll(loop, idx, loop->slots[idx].generation))
            return false;
        loop->slots[idx].polled = false;
        loop->slots[idx].generation++;
        if (loop->slots[idx].generation == 0u) loop->slots[idx].generation = 1u;
    }
    if (!uring_arm_poll(loop, &loop->slots[idx], idx, fd)) return false;
    loop->slots[idx].polled = true;
    return true;
}

bool net_loop_modify(NetLoop *loop, NetSocket *socket, u32 events)
{
    if (!loop || !socket || !net_loop_interest_valid(events)) return false;
    u32 idx = ur_find_slot(loop, socket);
    if (idx == UINT32_MAX) return false;
    /* Reuse the re-arm path: modify == add on an existing socket. */
    return net_loop_add(loop, socket, events, loop->slots[idx].tag);
}

bool net_loop_remove(NetLoop *loop, NetSocket *socket)
{
    if (!loop || !socket) return false;
    u32 idx = ur_find_slot(loop, socket);
    if (idx == UINT32_MAX) return false;
    bool ok = true;
    if (loop->slots[idx].polled) {
        ok = uring_cancel_poll(loop, idx, loop->slots[idx].generation);
    }
    loop->slots[idx].used = false;
    loop->slots[idx].socket = NULL;
    loop->slots[idx].polled = false;
    loop->slots[idx].generation++;
    if (loop->slots[idx].generation == 0u) loop->slots[idx].generation = 1u;
    return ok;
}

i32 net_loop_wait(NetLoop *loop, NetLoopEvent *out, u32 max, i32 timeout_ms)
{
    if (!loop || !out || max == 0u) return NET_ERROR;

    struct iouring_ring *r = &loop->ring;
    /* Block until at least one completion. io_uring_enter takes no timeout;
     * a timeout SQE bounds the wait (see below). */
    unsigned flags = IORING_ENTER_GETEVENTS;
    int rc;
    if (timeout_ms >= 0) {
        /* io_uring_enter has no timeout argument; arming a timeout SQE is the
         * canonical way to bound the wait. The timespec lives in the loop so
         * it stays valid if the timeout completion is reaped later. */
        loop->timeout_ts.tv_sec = timeout_ms / 1000;
        loop->timeout_ts.tv_nsec = (long long)(timeout_ms % 1000) * 1000000LL;
        struct io_uring_sqe *to = uring_get_sqe(loop);
        if (to) {
            to->opcode = IORING_OP_TIMEOUT;
            to->addr = (u64)(uintptr_t)&loop->timeout_ts;
            to->len = 1;
            to->user_data = 2u; /* control op */
        }
        rc = uring_enter(loop->ring_fd, 1, 1, flags);
    } else {
        rc = uring_enter(loop->ring_fd, 0, 1, flags);
    }
    if (rc < 0) return NET_ERROR;

    i32 count = 0;
    unsigned head = __atomic_load_n(r->cq_head, __ATOMIC_ACQUIRE);
    unsigned tail = __atomic_load_n(r->cq_tail, __ATOMIC_ACQUIRE);
    while (head != tail && (u32)count < max) {
        struct io_uring_cqe *cqe = &r->cqes[head & *r->cq_ring_mask];
        u64 ud = cqe->user_data;
        head++;
        if (ud == 0u) {
            /* Wakeup: drain the eventfd counter. */
            u64 discard;
            while (read(loop->wake_fd, &discard, sizeof(discard)) ==
                   (ssize_t)sizeof(discard)) {}
            continue;
        }
        if (ud == 1u || ud == 2u) continue; /* control ops */
        u32 encoded_index = (u32)ud;
        u32 generation = (u32)(ud >> 32);
        if (encoded_index < 3u) continue;
        u32 index = encoded_index - 3u;
        if (index >= loop->slot_count) continue;
        NetLoopSlot *slot = &loop->slots[index];
        if (!slot->used || slot->generation != generation) continue;
        u32 events = 0;
        if (cqe->res >= 0) {
            u32 mask = (u32)cqe->res;
            if (mask & POLLIN)                  events |= NET_LOOP_READ;
            if (mask & POLLOUT)                 events |= NET_LOOP_WRITE;
            if (mask & (POLLERR | POLLHUP))     events |= NET_LOOP_ERROR;
        } else {
            events |= NET_LOOP_ERROR;
        }
        out[count].socket = slot->socket;
        out[count].events = events;
        out[count].tag = slot->tag;
        count++;
    }
    __atomic_store_n(r->cq_head, head, __ATOMIC_RELEASE);
    return count;
}

void net_loop_wakeup(NetLoop *loop)
{
    if (!loop || loop->wake_fd < 0) return;
    u64 one = 1;
    (void)!write(loop->wake_fd, &one, sizeof(one));
}

#endif /* ENGINE_PLATFORM_LINUX && ENGINE_NET_IOURING */
