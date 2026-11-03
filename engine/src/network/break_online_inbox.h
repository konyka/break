#pragma once

#include <network/network.h>
#include <runtime/runtime_types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BREAK_ONLINE_MAX_DATAGRAM 1280u
#define BREAK_ONLINE_INBOX_HARD_MAX 256u

typedef struct BreakOnlineInbox BreakOnlineInbox;

typedef struct BreakOnlineDatagram {
    NetAddress source;
    u16 size;
    u8 bytes[BREAK_ONLINE_MAX_DATAGRAM];
} BreakOnlineDatagram;

typedef struct BreakOnlineInboxStats {
    u64 accepted;
    u64 polled;
    u64 overload_rejects;
    u64 invalid_rejects;
    u64 closed_rejects;
    u64 high_water;
} BreakOnlineInboxStats;

BreakRuntimeError break_online_inbox_create(u32 capacity,
                                            BreakOnlineInbox **out_inbox);
void break_online_inbox_destroy(BreakOnlineInbox *inbox);
void break_online_inbox_close(BreakOnlineInbox *inbox);
BreakRuntimeError break_online_inbox_push(BreakOnlineInbox *inbox,
                                          const NetAddress *source,
                                          const void *data, u32 size);
BreakRuntimeError break_online_inbox_poll(BreakOnlineInbox *inbox,
                                          BreakOnlineDatagram *out,
                                          bool *out_ready);
BreakRuntimeError break_online_inbox_stats(BreakOnlineInbox *inbox,
                                           BreakOnlineInboxStats *out);

#ifdef __cplusplus
}
#endif
