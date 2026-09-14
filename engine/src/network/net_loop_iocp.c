/*
 * net_loop_iocp.c — Windows backend for net_loop, built on I/O Completion
 * Ports.
 *
 * IOCP is completion-based while net_loop exposes readiness semantics, so
 * each registered socket runs a persistent overlapped WSARecv with a
 * zero-length buffer and MSG_PEEK: the operation completes (without consuming
 * data) exactly when the socket becomes readable, which maps a completion
 * port to readiness notification. IOCP does not arm NET_LOOP_WRITE because a
 * zero-length WSASend would complete immediately and spin.
 *
 * Throughput: GetQueuedCompletionStatusEx reaps a batch of completions in one
 * syscall, matching the kqueue/epoll batched-wait pattern.
 *
 * NOTE: cannot be compile-verified on macOS. Targets the documented Winsock2
 * overlapped API (mswsock.h / winsock2.h).
 */

#if defined(ENGINE_PLATFORM_WINDOWS)

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <winsock2.h>
#include <ws2tcpip.h>
#include <mswsock.h>

#include "net_loop.h"
#include <stdlib.h>
#include <string.h>

#define IOCP_WAKEUP_KEY 0u

typedef struct NetLoopSlot NetLoopSlot;
typedef struct {
    WSAOVERLAPPED ovl;
    NetLoopSlot  *slot;
    u64           generation;
    bool          cancelled;
} NetLoopOperation;

struct NetLoopSlot {
    NetSocket    *socket;
    SOCKET        native_socket;
    void         *tag;
    u32           events;
    bool          used;
    bool          removed;
    u64           generation;
    NetLoopOperation *read_op;
    u32           active_ops;
};

struct NetLoop {
    HANDLE       iocp;
    NetLoopSlot **slots;
    u32          slot_count;
    u32          slot_cap;
    OVERLAPPED_ENTRY *wait_events;
    u32          wait_cap;
};

static u32 iocp_find_slot(const NetLoop *loop, NetSocket *socket)
{
    for (u32 i = 0; i < loop->slot_count; i++) {
        if (loop->slots[i] != NULL &&
            loop->slots[i]->socket == socket) return i;
    }
    return UINT32_MAX;
}

/* Post the zero-byte peek recv that turns "readable" into a completion. */
static bool iocp_arm_read(NetLoopSlot *slot)
{
    SOCKET s = slot->native_socket;
    if (s == INVALID_SOCKET) return false;
    NetLoopOperation *op = (NetLoopOperation *)calloc(1, sizeof(*op));
    if (!op) return false;
    op->slot = slot;
    op->generation = slot->generation;
    WSABUF buf = { 0, NULL }; /* zero-length: consumes nothing */
    DWORD flags = MSG_PEEK;
    DWORD recvd = 0;
    int rc = WSARecv(s, &buf, 1, &recvd, &flags, &op->ovl, NULL);
    if (rc == 0 || WSAGetLastError() == WSA_IO_PENDING) {
        slot->read_op = op;
        slot->active_ops++;
        return true;
    }
    free(op);
    return false;
}

static bool iocp_cancel_read(NetLoopSlot *slot)
{
    if (!slot->read_op) return true;
    slot->read_op->cancelled = true;
    if (CancelIoEx((HANDLE)slot->native_socket, &slot->read_op->ovl)) return true;
    return GetLastError() == ERROR_NOT_FOUND;
}

static void iocp_cancel_slots(NetLoop *loop)
{
    u32 i;
    for (i = 0; i < loop->slot_count; ++i) {
        NetLoopSlot *slot = loop->slots[i];
        if (!slot || slot->native_socket == INVALID_SOCKET) continue;
        (void)iocp_cancel_read(slot);
    }
}

static void iocp_drain_slots(NetLoop *loop)
{
    OVERLAPPED_ENTRY entries[32];
    u32 pending = 0;
    u32 i;
    for (i = 0; i < loop->slot_count; ++i) {
        NetLoopSlot *slot = loop->slots[i];
        if (!slot) continue;
        pending += slot->active_ops;
    }
    while (pending != 0u) {
        ULONG got = 0;
        ULONG j;
        if (!GetQueuedCompletionStatusEx(loop->iocp, entries, 32u, &got,
                                         INFINITE, FALSE)) {
            continue;
        }
        for (j = 0; j < got; ++j) {
            ULONG_PTR key = entries[j].lpCompletionKey;
            NetLoopSlot *slot;
            WSAOVERLAPPED *ovl;
            if (key == IOCP_WAKEUP_KEY || entries[j].lpOverlapped == NULL) continue;
            slot = (NetLoopSlot *)key;
            if (!slot) continue;
            ovl = entries[j].lpOverlapped;
            NetLoopOperation *op = CONTAINING_RECORD(ovl, NetLoopOperation, ovl);
            if (op->slot != slot) continue;
            if (slot->read_op == op) {
                slot->read_op = NULL;
            }
            if (slot->active_ops != 0u) {
                slot->active_ops--;
                pending--;
            }
            free(op);
        }
    }
}

NetLoop *net_loop_create(void)
{
    NetLoop *loop = (NetLoop *)calloc(1, sizeof(*loop));
    if (!loop) return NULL;
    /* 0 = unlimited concurrency; the caller paces with its own threads. */
    loop->iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
    if (!loop->iocp) {
        free(loop);
        return NULL;
    }
    return loop;
}

void net_loop_destroy(NetLoop *loop)
{
    u32 i;
    if (!loop) return;
    iocp_cancel_slots(loop);
    iocp_drain_slots(loop);
    if (loop->iocp) CloseHandle(loop->iocp);
    for (i = 0; i < loop->slot_count; ++i) free(loop->slots[i]);
    free(loop->slots);
    free(loop->wait_events);
    free(loop);
}

bool net_loop_add(NetLoop *loop, NetSocket *socket, u32 events, void *tag)
{
    if (!loop || !socket || !net_loop_interest_valid(events)) return false;
    if ((events & NET_LOOP_WRITE) != 0u) return false;
    SOCKET s = (SOCKET)net_socket_native_handle(socket);
    if (s == INVALID_SOCKET) return false;

    u32 idx = iocp_find_slot(loop, socket);
    bool was_removed = false;
    if (idx == UINT32_MAX) {
        if (loop->slot_count == loop->slot_cap) {
            u32 new_cap;
            if (loop->slot_cap == 0u) new_cap = 16u;
            else if (loop->slot_cap > UINT32_MAX / 2u) return false;
            else new_cap = loop->slot_cap * 2u;
            if ((size_t)new_cap > (size_t)-1 / sizeof(*loop->slots)) return false;
            NetLoopSlot **ns = realloc(loop->slots, new_cap * sizeof(*ns));
            if (!ns) return false;
            memset(ns + loop->slot_cap, 0,
                   (new_cap - loop->slot_cap) * sizeof(*ns));
            loop->slots = ns;
            loop->slot_cap = new_cap;
        }
        idx = loop->slot_count;
        loop->slots[idx] = calloc(1, sizeof(*loop->slots[idx]));
        if (!loop->slots[idx]) return false;
        loop->slots[idx]->native_socket = INVALID_SOCKET;
        loop->slot_count++;
        /* Associate the socket with the completion port; the key is the slot
         * pointer. Zero is reserved for explicit wakeups. */
        if (!CreateIoCompletionPort((HANDLE)s, loop->iocp,
                                     (ULONG_PTR)loop->slots[idx], 0)) {
            free(loop->slots[idx]);
            loop->slots[idx] = NULL;
            loop->slot_count--;
            return false;
        }
    }
    NetLoopSlot *slot = loop->slots[idx];
    was_removed = slot->removed;
    slot->socket = socket;
    slot->native_socket = s;
    slot->tag = tag;
    slot->events = events;
    slot->used = true;
    slot->removed = false;
    if (was_removed) slot->generation++;

    bool ok = true;
    if ((events & NET_LOOP_READ) && !slot->read_op)
        ok = iocp_arm_read(slot) && ok;
    if (!(events & NET_LOOP_READ) && slot->read_op) {
        ok = iocp_cancel_read(slot) && ok;
    }
    return ok;
}

bool net_loop_modify(NetLoop *loop, NetSocket *socket, u32 events)
{
    if (!loop || !socket || !net_loop_interest_valid(events)) return false;
    if ((events & NET_LOOP_WRITE) != 0u) return false;
    u32 idx = iocp_find_slot(loop, socket);
    if (idx == UINT32_MAX) return false;
    NetLoopSlot *slot = loop->slots[idx];
    slot->events = events;
    /* Arm whatever newly-requested interests are not armed; IOCP has no
     * unarm — CancelIoEx cancels the pending op when an interest is dropped. */
    bool ok = true;
    if ((events & NET_LOOP_READ) && !slot->read_op)
        ok = iocp_arm_read(slot) && ok;
    if (!(events & NET_LOOP_READ) && slot->read_op) {
        ok = iocp_cancel_read(slot) && ok;
    }
    return ok;
}

bool net_loop_remove(NetLoop *loop, NetSocket *socket)
{
    if (!loop || !socket) return false;
    u32 idx = iocp_find_slot(loop, socket);
    if (idx == UINT32_MAX) return false;
    NetLoopSlot *slot = loop->slots[idx];
    /* Cancel in-flight ops; their completions may still arrive after the slot
     * is detached and are dropped by the operation generation check. */
    bool ok = iocp_cancel_read(slot);
    slot->read_op = NULL;
    slot->removed = true;
    slot->used = false;
    slot->generation++;
    /* The cancellation request owns the outstanding operations; do not retain
     * a handle that the caller may close and the kernel may subsequently reuse. */
    slot->native_socket = INVALID_SOCKET;
    return ok;
}

i32 net_loop_wait(NetLoop *loop, NetLoopEvent *out, u32 max, i32 timeout_ms)
{
    if (!loop || !out || !net_loop_wait_count_valid(max)) return NET_ERROR;
    if (max > loop->wait_cap) {
        OVERLAPPED_ENTRY *entries = (OVERLAPPED_ENTRY *)realloc(
            loop->wait_events, (size_t)max * sizeof(*entries));
        if (!entries) return NET_ERROR;
        loop->wait_events = entries;
        loop->wait_cap = max;
    }

    ULONG got = 0;
    DWORD ms = timeout_ms < 0 ? INFINITE : (DWORD)timeout_ms;
    if (!GetQueuedCompletionStatusEx(loop->iocp, loop->wait_events, (ULONG)max, &got,
                                     ms, FALSE)) {
        DWORD err = GetLastError();
        if (err == WAIT_TIMEOUT) return 0;
        return NET_ERROR;
    }

    i32 count = 0;
    for (ULONG i = 0; i < got; i++) {
        ULONG_PTR key = loop->wait_events[i].lpCompletionKey;
        if (key == IOCP_WAKEUP_KEY) continue;
        if (!loop->wait_events[i].lpOverlapped) continue;
        NetLoopSlot *slot = (NetLoopSlot *)key;
        if (!slot) continue;
        WSAOVERLAPPED *ovl = loop->wait_events[i].lpOverlapped;
        NetLoopOperation *op = CONTAINING_RECORD(ovl, NetLoopOperation, ovl);
        if (op->slot != slot) continue;
        bool current = slot->read_op == op;
        bool valid = current && op->generation == slot->generation &&
                     slot->used && !slot->removed && !op->cancelled;
        if (current) {
            slot->read_op = NULL;
        }
        if (slot->active_ops != 0u) slot->active_ops--;
        if (!valid) {
            if (current && slot->used && !slot->removed &&
                (slot->events & NET_LOOP_READ))
                (void)iocp_arm_read(slot);
            free(op);
            continue;
        }
        if (!(slot->events & NET_LOOP_READ))
        {
            free(op);
            continue;
        }

        u32 events = 0;
        DWORD bytes = 0, flags = 0;
        BOOL ok = WSAGetOverlappedResult(
            (SOCKET)net_socket_native_handle(slot->socket),
            ovl, &bytes, FALSE, &flags);
        if (ok) {
            events |= NET_LOOP_READ;
        } else {
            events |= NET_LOOP_ERROR;
        }
        /* Re-arm after consuming this completion so readiness remains
         * persistent, but never re-arm removed, canceled, or stale work. */
        if (slot->used && !slot->removed &&
            (slot->events & NET_LOOP_READ))
            (void)iocp_arm_read(slot);
        free(op);
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
    if (!loop || !loop->iocp) return;
    (void)PostQueuedCompletionStatus(loop->iocp, 0, IOCP_WAKEUP_KEY, NULL);
}

#endif /* ENGINE_PLATFORM_WINDOWS */

/* Keep a declaration in non-Windows editor/LSP preprocessing contexts. */
#if !defined(ENGINE_PLATFORM_WINDOWS)
typedef int net_loop_iocp_translation_unit;
#endif
