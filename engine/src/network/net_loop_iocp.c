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
#include <stddef.h>

#define IOCP_WAKEUP_KEY 0u

typedef struct {
    /* Overlapped structs must outlive the operation; read and write need
     * separate ones since both may be in flight concurrently. The read
     * struct comes first so its address identifies the slot on completion. */
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
    NetLoopSlot *slots;
    u32          slot_count;
    u32          slot_cap;
};

static u32 iocp_find_slot(const NetLoop *loop, NetSocket *socket)
{
    for (u32 i = 0; i < loop->slot_count; i++) {
        if (loop->slots[i].used && loop->slots[i].socket == socket) return i;
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
    if (!loop) return;
    if (loop->iocp) CloseHandle(loop->iocp);
    free(loop->slots);
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
            NetLoopSlot *ns = realloc(loop->slots, new_cap * sizeof(*ns));
            if (!ns) return false;
            memset(ns + loop->slot_cap, 0,
                   (new_cap - loop->slot_cap) * sizeof(*ns));
            loop->slots = ns;
            loop->slot_cap = new_cap;
        }
        idx = loop->slot_count++;
        memset(&loop->slots[idx], 0, sizeof(loop->slots[idx]));
        /* Associate the socket with the completion port; the key is the slot
         * index (stable across realloc, unlike the slot address). */
        if (!CreateIoCompletionPort((HANDLE)s, loop->iocp,
                                    (ULONG_PTR)idx, 0)) {
            loop->slot_count--;
            return false;
        }
    }
    loop->slots[idx].socket = socket;
    loop->slots[idx].tag = tag;
    loop->slots[idx].events = events;
    loop->slots[idx].used = true;
    loop->slots[idx].removed = false;

    bool ok = true;
    if (events & NET_LOOP_READ)  ok = iocp_arm_read(&loop->slots[idx]) && ok;
    if (events & NET_LOOP_WRITE) ok = iocp_arm_write(&loop->slots[idx]) && ok;
    return ok;
}

bool net_loop_modify(NetLoop *loop, NetSocket *socket, u32 events)
{
    if (!loop || !socket || !net_loop_interest_valid(events)) return false;
    u32 idx = iocp_find_slot(loop, socket);
    if (idx == UINT32_MAX) return false;
    NetLoopSlot *slot = &loop->slots[idx];
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
    NetLoopSlot *slot = &loop->slots[idx];
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
    if (!loop || !out || max == 0u) return NET_ERROR;

    OVERLAPPED_ENTRY *entries =
        (OVERLAPPED_ENTRY *)calloc(max, sizeof(*entries));
    if (!entries) return NET_ERROR;

    ULONG got = 0;
    DWORD ms = timeout_ms < 0 ? INFINITE : (DWORD)timeout_ms;
    if (!GetQueuedCompletionStatusEx(loop->iocp, entries, (ULONG)max, &got,
                                     ms, FALSE)) {
        free(entries);
        DWORD err = GetLastError();
        if (err == WAIT_TIMEOUT) return 0;
        return NET_ERROR;
    }

    i32 count = 0;
    for (ULONG i = 0; i < got; i++) {
        if (entries[i].lpCompletionKey == IOCP_WAKEUP_KEY) continue;
        if (!entries[i].lpOverlapped) continue;
        WSAOVERLAPPED *ovl = entries[i].lpOverlapped;
        /* read_ovl is the first member, so a read completion's overlapped
         * pointer IS the slot address; a write completion needs the offset. */
        NetLoopSlot *slot = (NetLoopSlot *)
            ((char *)ovl - offsetof(NetLoopSlot, read_ovl));
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
    free(entries);
    return count;
}

void net_loop_wakeup(NetLoop *loop)
{
    if (!loop || !loop->iocp) return;
    (void)PostQueuedCompletionStatus(loop->iocp, 0, IOCP_WAKEUP_KEY, NULL);
}

#endif /* ENGINE_PLATFORM_WINDOWS */
