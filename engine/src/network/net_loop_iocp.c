/*
 * net_loop_iocp.c — Windows backend for net_loop, built on I/O Completion
 * Ports.
 *
 * IOCP is completion-based while net_loop exposes readiness semantics, so
 * each registered socket runs a persistent overlapped WSARecv with a
 * zero-length buffer and MSG_PEEK: the operation completes (without consuming
 * data) exactly when the socket becomes readable, which maps a completion
 * port to readiness notification. Writes use WSAGetOverlappedResult-free
 * polling via a zero-length overlapped WSASend, which completes when the
 * socket is writable.
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

typedef struct {
    /* Overlapped structs must outlive the operation; read and write need
     * separate ones since both may be in flight concurrently. Slots are
     * individually allocated so their addresses remain stable while an
     * operation is in flight. */
    WSAOVERLAPPED read_ovl;
    WSAOVERLAPPED write_ovl;
    NetSocket    *socket;
    void         *tag;
    u32           events;
    bool          used;
    bool          read_armed;
    bool          write_armed;
    bool          removed;  /* completion in flight after remove() */
} NetLoopSlot;

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
        if (loop->slots[i] != NULL && loop->slots[i]->used &&
            loop->slots[i]->socket == socket) return i;
    }
    return UINT32_MAX;
}

/* Post the zero-byte peek recv that turns "readable" into a completion. */
static bool iocp_arm_read(NetLoopSlot *slot)
{
    SOCKET s = (SOCKET)net_socket_native_handle(slot->socket);
    if (s == INVALID_SOCKET) return false;
    memset(&slot->read_ovl, 0, sizeof(slot->read_ovl));
    WSABUF buf = { 0, NULL }; /* zero-length: consumes nothing */
    DWORD flags = MSG_PEEK;
    DWORD recvd = 0;
    int rc = WSARecv(s, &buf, 1, &recvd, &flags, &slot->read_ovl, NULL);
    if (rc == 0 || WSAGetLastError() == WSA_IO_PENDING) {
        slot->read_armed = true;
        return true;
    }
    return false;
}

static bool iocp_arm_write(NetLoopSlot *slot)
{
    SOCKET s = (SOCKET)net_socket_native_handle(slot->socket);
    if (s == INVALID_SOCKET) return false;
    memset(&slot->write_ovl, 0, sizeof(slot->write_ovl));
    WSABUF buf = { 0, NULL };
    DWORD sent = 0;
    int rc = WSASend(s, &buf, 1, &sent, 0, &slot->write_ovl, NULL);
    if (rc == 0 || WSAGetLastError() == WSA_IO_PENDING) {
        slot->write_armed = true;
        return true;
    }
    return false;
}

/* Re-arm after a completion fired (readiness is edge-like under IOCP). */
static void iocp_rearm(NetLoopSlot *slot)
{
    if (!slot->used || slot->removed) return;
    if (slot->read_armed) {
        slot->read_armed = false;
        if (slot->events & NET_LOOP_READ) (void)iocp_arm_read(slot);
    }
    if (slot->write_armed) {
        slot->write_armed = false;
        if (slot->events & NET_LOOP_WRITE) (void)iocp_arm_write(slot);
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
    if (loop->iocp) CloseHandle(loop->iocp);
    for (i = 0; i < loop->slot_count; ++i) free(loop->slots[i]);
    free(loop->slots);
    free(loop->wait_events);
    free(loop);
}

bool net_loop_add(NetLoop *loop, NetSocket *socket, u32 events, void *tag)
{
    if (!loop || !socket || !net_loop_interest_valid(events)) return false;
    SOCKET s = (SOCKET)net_socket_native_handle(socket);
    if (s == INVALID_SOCKET) return false;

    u32 idx = iocp_find_slot(loop, socket);
    if (idx == UINT32_MAX) {
        if (loop->slot_count == loop->slot_cap) {
            u32 new_cap = loop->slot_cap ? loop->slot_cap * 2u : 16u;
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
        loop->slot_count++;
        /* Associate the socket with the completion port; the key is the slot
         * index plus one. Zero is reserved for explicit wakeups. */
        if (!CreateIoCompletionPort((HANDLE)s, loop->iocp,
                                    (ULONG_PTR)(idx + 1u), 0)) {
            free(loop->slots[idx]);
            loop->slots[idx] = NULL;
            loop->slot_count--;
            return false;
        }
    }
    NetLoopSlot *slot = loop->slots[idx];
    slot->socket = socket;
    slot->tag = tag;
    slot->events = events;
    slot->used = true;
    slot->removed = false;

    bool ok = true;
    if (events & NET_LOOP_READ)  ok = iocp_arm_read(slot) && ok;
    if (events & NET_LOOP_WRITE) ok = iocp_arm_write(slot) && ok;
    return ok;
}

bool net_loop_modify(NetLoop *loop, NetSocket *socket, u32 events)
{
    if (!loop || !socket || !net_loop_interest_valid(events)) return false;
    u32 idx = iocp_find_slot(loop, socket);
    if (idx == UINT32_MAX) return false;
    NetLoopSlot *slot = loop->slots[idx];
    slot->events = events;
    /* Arm whatever newly-requested interests are not armed; IOCP has no
     * unarm — CancelIoEx cancels the pending op when an interest is dropped. */
    bool ok = true;
    if ((events & NET_LOOP_READ) && !slot->read_armed)
        ok = iocp_arm_read(slot) && ok;
    if ((events & NET_LOOP_WRITE) && !slot->write_armed)
        ok = iocp_arm_write(slot) && ok;
    if (!(events & NET_LOOP_READ) && slot->read_armed) {
        (void)CancelIoEx((HANDLE)net_socket_native_handle(socket),
                         &slot->read_ovl);
        slot->read_armed = false;
    }
    if (!(events & NET_LOOP_WRITE) && slot->write_armed) {
        (void)CancelIoEx((HANDLE)net_socket_native_handle(socket),
                         &slot->write_ovl);
        slot->write_armed = false;
    }
    return ok;
}

bool net_loop_remove(NetLoop *loop, NetSocket *socket)
{
    if (!loop || !socket) return false;
    u32 idx = iocp_find_slot(loop, socket);
    if (idx == UINT32_MAX) return false;
    NetLoopSlot *slot = loop->slots[idx];
    /* Cancel in-flight ops; their completions may still arrive and are
     * dropped in wait() via the removed flag. */
    HANDLE sh = (HANDLE)net_socket_native_handle(socket);
    if (slot->read_armed)  (void)CancelIoEx(sh, &slot->read_ovl);
    if (slot->write_armed) (void)CancelIoEx(sh, &slot->write_ovl);
    slot->removed = true;
    slot->used = false;
    slot->socket = NULL;
    slot->read_armed = false;
    slot->write_armed = false;
    return true;
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
        if (key - 1u >= loop->slot_count) continue;
        NetLoopSlot *slot = loop->slots[key - 1u];
        if (!slot) continue;
        WSAOVERLAPPED *ovl = loop->wait_events[i].lpOverlapped;
        bool was_write = (ovl == &slot->write_ovl);
        if (!slot->used || slot->removed) continue;

        u32 events = 0;
        DWORD bytes = 0, flags = 0;
        BOOL ok = WSAGetOverlappedResult(
            (SOCKET)net_socket_native_handle(slot->socket),
            ovl, &bytes, FALSE, &flags);
        if (ok) {
            events |= was_write ? NET_LOOP_WRITE : NET_LOOP_READ;
        } else {
            events |= NET_LOOP_ERROR;
        }
        /* Rearm before reporting so an immediate drain is observable. */
        iocp_rearm(slot);
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
