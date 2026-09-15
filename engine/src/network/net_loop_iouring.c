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
    u64                 request_sequence;
    bool                wake_polled;
    u32                 poll_requests;
    u32                 timeout_requests;
    u32                 control_requests;
    /* Timeout SQE target; must outlive the wait (stack lifetime is too short
     * if the completion is reaped by a later wait call). */
    struct __kernel_timespec timeout_ts;
    bool                timeout_active;
    u64                 timeout_token;
    bool                aborted;
#if defined(ENGINE_NET_LOOP_TESTING)
    bool                fail_next_submit;
    bool                fail_next_timeout_cancel;
#endif
};

#define URING_REQUEST_MARKER (1ull << 63)
#define URING_CONTROL_TOKEN 1u
#define URING_TIMEOUT_TOKEN 2u

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

static bool uring_submit_one(NetLoop *loop)
{
    int rc;
#if defined(ENGINE_NET_LOOP_TESTING)
    if (loop->fail_next_submit) {
        loop->fail_next_submit = false;
        errno = EIO;
        return false;
    }
#endif
    do {
        rc = uring_enter(loop->ring_fd, 1, 0, 0);
    } while (rc < 0 && errno == EINTR);
    return rc == 1;
}

static int uring_enter_wait(NetLoop *loop, unsigned to_submit,
                            unsigned min_complete, unsigned flags)
{
#if defined(ENGINE_NET_LOOP_TESTING)
    if (loop->fail_next_submit) {
        loop->fail_next_submit = false;
        errno = EIO;
        return -1;
    }
#endif
    return uring_enter(loop->ring_fd, to_submit, min_complete, flags);
}

#if defined(ENGINE_NET_LOOP_TESTING)
void net_loop_iouring_test_fail_next_submit(NetLoop *loop)
{
    if (loop) loop->fail_next_submit = true;
}

void net_loop_iouring_test_fail_next_timeout_cancel(NetLoop *loop)
{
    if (loop) loop->fail_next_timeout_cancel = true;
}
#endif

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

/* A failed enter does not consume the SQE, so return the reservation to the
 * userspace ring before another request can be prepared. */
static void uring_discard_last_sqe(NetLoop *loop)
{
    struct iouring_ring *r = &loop->ring;
    unsigned tail = *r->tail;
    if (tail == *r->head) return;
    memset(&r->sqes[(tail - 1u) & *r->ring_mask], 0,
           sizeof(r->sqes[0]));
    __atomic_store_n(r->tail, tail - 1u, __ATOMIC_RELEASE);
}

static u64 uring_next_request_token(NetLoop *loop, u32 kind)
{
    u64 sequence = loop->request_sequence++;
    if (sequence == 0u) sequence = loop->request_sequence++;
    return URING_REQUEST_MARKER | (sequence << 2) | (u64)kind;
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
    sqe->user_data = uring_next_request_token(loop, URING_CONTROL_TOKEN);
    if (!uring_submit_one(loop)) {
        uring_discard_last_sqe(loop);
        return false;
    }
    loop->control_requests++;
    return true;
}

static bool uring_cancel_target(NetLoop *loop, u64 target)
{
    struct io_uring_sqe *sqe = uring_get_sqe(loop);
    if (!sqe) return false;
    sqe->opcode = IORING_OP_POLL_REMOVE;
    sqe->addr = target;
    sqe->user_data = uring_next_request_token(loop, URING_CONTROL_TOKEN);
    if (!uring_submit_one(loop)) {
        uring_discard_last_sqe(loop);
        return false;
    }
    loop->control_requests++;
    return true;
}

static bool uring_cancel_timeout(NetLoop *loop)
{
    struct io_uring_sqe *sqe;
    if (!loop->timeout_active) return true;
    sqe = uring_get_sqe(loop);
    if (!sqe) return false;
#if defined(ENGINE_NET_LOOP_TESTING)
    if (loop->fail_next_timeout_cancel) {
        loop->fail_next_timeout_cancel = false;
        uring_discard_last_sqe(loop);
        return false;
    }
#endif
    sqe->opcode = IORING_OP_TIMEOUT_REMOVE;
    sqe->addr = loop->timeout_token;
    sqe->user_data = uring_next_request_token(loop, URING_CONTROL_TOKEN);
    if (!uring_submit_one(loop)) {
        uring_discard_last_sqe(loop);
        return false;
    }
    loop->timeout_active = false;
    loop->control_requests++;
    return true;
}

static bool uring_cancel_wakeup(NetLoop *loop)
{
    if (!loop->wake_polled) return true;
    if (!uring_cancel_target(loop, 0u)) return false;
    loop->wake_polled = false;
    return true;
}

static void uring_abort_destroy(NetLoop *loop)
{
    if (loop->ring_fd >= 0) close(loop->ring_fd);
    loop->ring_fd = -1;
    loop->poll_requests = 0u;
    loop->timeout_requests = 0u;
    loop->control_requests = 0u;
    loop->wake_polled = false;
    loop->timeout_active = false;
    loop->timeout_token = 0;
    loop->aborted = true;
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
    if (!uring_submit_one(loop)) {
        uring_discard_last_sqe(loop);
        return false;
    }
    loop->poll_requests++;
    return true;
}

static bool uring_arm_wakeup(NetLoop *loop)
{
    struct io_uring_sqe *sqe = uring_get_sqe(loop);
    if (!sqe) return false;
    sqe->opcode = IORING_OP_POLL_ADD;
    sqe->fd = loop->wake_fd;
    sqe->poll32_events = POLLIN;
    sqe->user_data = 0;
    sqe->len = IORING_POLL_ADD_MULTI;
    if (!uring_submit_one(loop)) {
        uring_discard_last_sqe(loop);
        return false;
    }
    loop->wake_polled = true;
    loop->poll_requests++;
    return true;
}

static void uring_reap_cqes(NetLoop *loop, NetLoopEvent *out, u32 max,
                            i32 *count, u64 timeout_token,
                            bool *timeout_completed, bool *other_completion)
{
    struct iouring_ring *r = &loop->ring;
    unsigned head = __atomic_load_n(r->cq_head, __ATOMIC_ACQUIRE);
    unsigned tail = __atomic_load_n(r->cq_tail, __ATOMIC_ACQUIRE);
    while (head != tail) {
        struct io_uring_cqe *cqe = &r->cqes[head & *r->cq_ring_mask];
        u64 ud = cqe->user_data;
        bool more = (cqe->flags & IORING_CQE_F_MORE) != 0u;
        head++;
        if ((ud & URING_REQUEST_MARKER) != 0u) {
            u32 kind = (u32)(ud & 3u);
            if (kind == URING_CONTROL_TOKEN && loop->control_requests != 0u)
                loop->control_requests--;
            else if (kind == URING_TIMEOUT_TOKEN &&
                     loop->timeout_requests != 0u)
                loop->timeout_requests--;
            if (ud == timeout_token) {
                *timeout_completed = true;
                loop->timeout_active = false;
                loop->timeout_token = 0;
            }
            continue;
        }
        if (!more && loop->poll_requests != 0u) loop->poll_requests--;
        if (ud == 0u) {
            *other_completion = true;
            u64 discard;
            while (read(loop->wake_fd, &discard, sizeof(discard)) ==
                   (ssize_t)sizeof(discard)) {}
            continue;
        }
        u32 encoded_index = (u32)ud;
        u32 generation = (u32)(ud >> 32);
        if (encoded_index < 3u) continue;
        u32 index = encoded_index - 3u;
        if (index >= loop->slot_count) continue;
        NetLoopSlot *slot = &loop->slots[index];
        if (!slot->used || slot->generation != generation) continue;
        *other_completion = true;
        if ((u32)*count >= max) continue;
        u32 events = 0;
        if (cqe->res >= 0) {
            u32 mask = (u32)cqe->res;
            if (mask & POLLIN) events |= NET_LOOP_READ;
            if (mask & POLLOUT) events |= NET_LOOP_WRITE;
            if (mask & (POLLERR | POLLHUP)) events |= NET_LOOP_ERROR;
        } else {
            events |= NET_LOOP_ERROR;
        }
        out[*count].socket = slot->socket;
        out[*count].events = events;
        out[*count].tag = slot->tag;
        (*count)++;
    }
    __atomic_store_n(r->cq_head, head, __ATOMIC_RELEASE);
}

static bool ur_next_capacity(u32 current, u32 required, u32 *next)
{
    u32 capacity = current ? current : 16u;
    while (capacity < required) {
        if (capacity > UINT32_MAX / 2u) return false;
        capacity *= 2u;
    }
    size_t bytes = (size_t)capacity * sizeof(*((NetLoop *)0)->slots);
    if (bytes / sizeof(*((NetLoop *)0)->slots) != (size_t)capacity)
        return false;
    *next = capacity;
    return true;
}

static bool ur_ensure_capacity(NetLoop *loop, u32 required)
{
    if (required <= loop->slot_cap) return true;
    u32 new_cap;
    if (!ur_next_capacity(loop->slot_cap, required, &new_cap)) return false;
    NetLoopSlot *slots = (NetLoopSlot *)realloc(
        loop->slots, (size_t)new_cap * sizeof(*slots));
    if (!slots) return false;
    memset(slots + loop->slot_cap, 0,
           (size_t)(new_cap - loop->slot_cap) * sizeof(*slots));
    loop->slots = slots;
    loop->slot_cap = new_cap;
    return true;
}

#if defined(ENGINE_NET_LOOP_TESTING)
bool net_loop_iouring_test_next_capacity(u32 current, u32 required, u32 *next)
{
    return next && ur_next_capacity(current, required, next);
}

u32 net_loop_iouring_test_pending_sqes(const NetLoop *loop)
{
    if (!loop || !loop->ring.tail || !loop->ring.head) return 0u;
    return *loop->ring.tail - *loop->ring.head;
}
#endif

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
    if (!uring_arm_wakeup(loop)) {
        net_loop_destroy(loop);
        return NULL;
    }
    return loop;
}

void net_loop_destroy(NetLoop *loop)
{
    if (!loop) return;
    struct iouring_ring *r = &loop->ring;
    if (loop->ring_fd >= 0) {
        bool teardown_ok = true;
        for (u32 i = 0; i < loop->slot_count; ++i) {
            if (loop->slots[i].polled) {
                if (!uring_cancel_poll(loop, i, loop->slots[i].generation)) {
                    teardown_ok = false;
                    break;
                }
                loop->slots[i].polled = false;
            }
        }
        if (teardown_ok && !uring_cancel_wakeup(loop)) teardown_ok = false;
        if (teardown_ok && !uring_cancel_timeout(loop)) teardown_ok = false;
        if (!teardown_ok) uring_abort_destroy(loop);
        while (loop->ring_fd >= 0 &&
               (loop->poll_requests != 0u || loop->timeout_requests != 0u ||
               loop->control_requests != 0u)) {
            if (uring_enter(loop->ring_fd, 0, 1, IORING_ENTER_GETEVENTS) < 0) {
                if (errno == EINTR) continue;
                uring_abort_destroy(loop);
                break;
            }
            unsigned head = __atomic_load_n(r->cq_head, __ATOMIC_ACQUIRE);
            unsigned tail = __atomic_load_n(r->cq_tail, __ATOMIC_ACQUIRE);
            while (head != tail) {
                struct io_uring_cqe *cqe =
                    &r->cqes[head & *r->cq_ring_mask];
                u64 ud = cqe->user_data;
                bool more = (cqe->flags & IORING_CQE_F_MORE) != 0u;
                head++;
                if ((ud & URING_REQUEST_MARKER) != 0u) {
                    if ((ud & 3u) == URING_CONTROL_TOKEN &&
                        loop->control_requests != 0u) {
                        loop->control_requests--;
                    } else if ((ud & 3u) == URING_TIMEOUT_TOKEN &&
                               loop->timeout_requests != 0u) {
                        loop->timeout_requests--;
                    }
                } else if (!more) {
                    if (ud == 0u) {
                        loop->wake_polled = false;
                    }
                    if (loop->poll_requests != 0u) loop->poll_requests--;
                }
            }
            __atomic_store_n(r->cq_head, head, __ATOMIC_RELEASE);
        }
    }
    if (loop->ring_fd >= 0) close(loop->ring_fd);
    if (loop->wake_fd >= 0) close(loop->wake_fd);
    if (r->sq_ptr && r->sq_ptr != MAP_FAILED) munmap(r->sq_ptr, r->sq_sz);
    if (r->cq_ptr && r->cq_ptr != MAP_FAILED && r->cq_ptr != r->sq_ptr)
        munmap(r->cq_ptr, r->cq_sz);
    if (r->sqes && r->sqes != MAP_FAILED)
        munmap(r->sqes, r->sqes_sz);
    free(loop->slots);
    free(loop);
}

bool net_loop_add(NetLoop *loop, NetSocket *socket, u32 events, void *tag)
{
    if (!loop || loop->aborted || !socket || !net_loop_interest_valid(events))
        return false;
    intptr_t fd = net_socket_native_handle(socket);
    if (fd < 0) return false;

    u32 idx = ur_find_slot(loop, socket);
    bool new_slot = idx == UINT32_MAX;
    if (idx == UINT32_MAX) {
        if (loop->slot_count == UINT32_MAX ||
            !ur_ensure_capacity(loop, loop->slot_count + 1u)) return false;
        idx = loop->slot_count;
        loop->slots[idx].used = false;
        loop->slots[idx].polled = false;
        loop->slots[idx].generation = 1u;
    }
    NetLoopSlot previous = loop->slots[idx];
    if (loop->slots[idx].polled) {
        NetLoopSlot candidate = previous;
        candidate.tag = tag;
        candidate.events = events;
        candidate.generation++;
        if (candidate.generation == 0u) candidate.generation = 1u;
        candidate.polled = false;
        if (!uring_arm_poll(loop, &candidate, idx, fd)) return false;
        if (!uring_cancel_poll(loop, idx, previous.generation)) {
            (void)uring_cancel_poll(loop, idx, candidate.generation);
            return false;
        }
        candidate.used = true;
        candidate.polled = true;
        loop->slots[idx] = candidate;
        return true;
    }
    loop->slots[idx].socket = socket;
    loop->slots[idx].tag = tag;
    loop->slots[idx].events = events;
    loop->slots[idx].used = true;
    if (!uring_arm_poll(loop, &loop->slots[idx], idx, fd)) {
        loop->slots[idx] = previous;
        if (new_slot) {
            memset(&loop->slots[idx], 0, sizeof(loop->slots[idx]));
        }
        return false;
    }
    loop->slots[idx].polled = true;
    if (new_slot) loop->slot_count++;
    return true;
}

bool net_loop_modify(NetLoop *loop, NetSocket *socket, u32 events)
{
    if (!loop || loop->aborted || !socket || !net_loop_interest_valid(events))
        return false;
    u32 idx = ur_find_slot(loop, socket);
    if (idx == UINT32_MAX) return false;
    /* Reuse the re-arm path: modify == add on an existing socket. */
    return net_loop_add(loop, socket, events, loop->slots[idx].tag);
}

bool net_loop_remove(NetLoop *loop, NetSocket *socket)
{
    if (!loop || loop->aborted || !socket) return false;
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
    if (!loop || loop->aborted || !out || !net_loop_wait_count_valid(max))
        return NET_ERROR;

    /* Block until at least one completion. io_uring_enter takes no timeout;
     * a timeout SQE bounds the wait (see below). */
    unsigned flags = IORING_ENTER_GETEVENTS;
    unsigned to_submit = 0;
    u64 timeout_token = 0;
    if (timeout_ms >= 0) {
        /* io_uring_enter has no timeout argument; arming a timeout SQE is the
         * canonical way to bound the wait. The timespec lives in the loop so
         * it stays valid if the timeout completion is reaped later. */
        loop->timeout_ts.tv_sec = timeout_ms / 1000;
        loop->timeout_ts.tv_nsec = (long long)(timeout_ms % 1000) * 1000000LL;
        struct io_uring_sqe *to = uring_get_sqe(loop);
        if (!to) return NET_ERROR;
        to->opcode = IORING_OP_TIMEOUT;
        to->addr = (u64)(uintptr_t)&loop->timeout_ts;
        to->len = 1;
        timeout_token = uring_next_request_token(loop, URING_TIMEOUT_TOKEN);
        loop->timeout_token = timeout_token;
        to->user_data = timeout_token;
        loop->timeout_active = true;
        loop->timeout_requests++;
        to_submit = 1;
    }

    i32 count = 0;
    for (;;) {
        int rc = uring_enter_wait(loop, to_submit, 1, flags);
        if (to_submit != 0u && rc != (int)to_submit) {
            uring_discard_last_sqe(loop);
            if (to_submit != 0u) {
                loop->timeout_active = false;
                loop->timeout_token = 0;
                loop->timeout_requests--;
            }
            return NET_ERROR;
        }
        to_submit = 0;
        bool timeout_completed = false;
        bool other_completion = false;
        uring_reap_cqes(loop, out, max, &count, timeout_token,
                        &timeout_completed, &other_completion);
        if (count != 0 || timeout_completed || other_completion) {
            if (!timeout_completed && loop->timeout_active && other_completion &&
                !uring_cancel_timeout(loop)) {
                /* The old timeout is still live in the kernel. Closing the
                 * ring prevents a later wait from reusing its shared state. */
                uring_abort_destroy(loop);
                return NET_ERROR;
            }
            return count;
        }
    }
}

void net_loop_wakeup(NetLoop *loop)
{
    if (!loop || loop->aborted || loop->wake_fd < 0) return;
    u64 one = 1;
    (void)!write(loop->wake_fd, &one, sizeof(one));
}

#endif /* ENGINE_PLATFORM_LINUX && ENGINE_NET_IOURING */

#if !defined(ENGINE_PLATFORM_LINUX) || !defined(ENGINE_NET_IOURING)
typedef int net_loop_iouring_translation_unit;
#endif
