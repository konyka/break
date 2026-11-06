#pragma once

#include <network/break_online_types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BREAK_LOBBY_NAME_CAP 64u
#define BREAK_LOBBY_DEFAULT_MAX_ROOMS 64u
#define BREAK_LOBBY_DEFAULT_MAX_MEMBERS 16u
#define BREAK_LOBBY_HARD_MAX_ROOMS 1024u
#define BREAK_LOBBY_HARD_MAX_MEMBERS 256u

typedef struct BreakLobby BreakLobby;

typedef struct BreakLobbyConfig {
    u32 max_rooms;
    u32 max_members_per_room;
} BreakLobbyConfig;

typedef struct BreakLobbyAuth {
    u64 session;
    BreakOnlineAuthSource source;
} BreakLobbyAuth;

typedef struct BreakLobbyRoomDesc {
    const char *name;
    u16 region;
    u16 mode;
    u16 max_members;
    bool listed;
} BreakLobbyRoomDesc;

typedef struct BreakLobbyMatchQuery {
    u16 region;
    u16 mode;
    bool filter_region;
    bool filter_mode;
} BreakLobbyMatchQuery;

typedef struct BreakLobbyRoomInfo {
    BreakOnlineHandle room;
    char name[BREAK_LOBBY_NAME_CAP];
    u16 region;
    u16 mode;
    u16 max_members;
    bool listed;
    u32 member_count;
    BreakOnlineIdentity host;
    u64 host_epoch;
} BreakLobbyRoomInfo;

BreakRuntimeError break_lobby_create(const BreakLobbyConfig *config,
                                     BreakLobby **out_lobby);
void break_lobby_destroy(BreakLobby *lobby);
u32 break_lobby_room_count(const BreakLobby *lobby);

BreakRuntimeError break_lobby_room_create(BreakLobby *lobby,
                                          const BreakLobbyAuth *auth,
                                          const BreakLobbyRoomDesc *desc,
                                          BreakOnlineHandle *out_room,
                                          BreakOnlineMemberHandle *out_member);
BreakRuntimeError break_lobby_join(BreakLobby *lobby,
                                   const BreakLobbyAuth *auth,
                                   BreakOnlineHandle room,
                                   BreakOnlineMemberHandle *out_member);
BreakRuntimeError break_lobby_leave(BreakLobby *lobby,
                                    const BreakLobbyAuth *auth,
                                    BreakOnlineMemberHandle member);
BreakRuntimeError break_lobby_disconnect(BreakLobby *lobby, u64 session);
BreakRuntimeError break_lobby_match(BreakLobby *lobby,
                                    const BreakLobbyAuth *auth,
                                    const BreakLobbyMatchQuery *query,
                                    BreakOnlineHandle *out_room,
                                    BreakOnlineMemberHandle *out_member);
BreakRuntimeError break_lobby_list(const BreakLobby *lobby,
                                   const BreakLobbyMatchQuery *query,
                                   u32 offset, BreakLobbyRoomInfo *out,
                                   u32 capacity, u32 *out_count,
                                   u32 *out_next_offset);
BreakRuntimeError break_lobby_room_info(const BreakLobby *lobby,
                                        BreakOnlineHandle room,
                                        BreakLobbyRoomInfo *out);

#ifdef __cplusplus
}
#endif
