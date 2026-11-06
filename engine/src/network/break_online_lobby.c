#include <network/break_online_lobby.h>

#include <core/platform_thread.h>

#include <stdlib.h>
#include <string.h>

typedef struct LobbyMember {
    bool used;
    u32 generation;
    u64 session_key;
    u64 join_order;
    BreakOnlineIdentity identity;
} LobbyMember;

typedef struct LobbyRoom {
    bool used;
    u32 generation;
    char name[BREAK_LOBBY_NAME_CAP];
    u16 region;
    u16 mode;
    u16 max_members;
    bool listed;
    u32 member_count;
    u32 host_slot;
    u64 host_epoch;
    u64 next_join_order;
} LobbyRoom;

struct BreakLobby {
    PlatformThreadId owner;
    u32 max_rooms;
    u32 max_members;
    u32 room_count;
    LobbyRoom *rooms;
    LobbyMember *members;
};

static bool lobby_owner(const BreakLobby *lobby)
{
    return lobby && platform_thread_id_equal(lobby->owner,
                                              platform_thread_current_id());
}

static u32 next_generation(u32 generation)
{
    return generation == 0u ? 1u : generation;
}

static u32 retired_generation(u32 generation)
{
    return generation == UINT32_MAX ? generation : generation + 1u;
}

static LobbyMember *member_at(BreakLobby *lobby, u32 room_index, u32 slot)
{
    return &lobby->members[(usize)room_index * lobby->max_members + slot];
}

static const LobbyMember *member_at_const(const BreakLobby *lobby,
                                          u32 room_index, u32 slot)
{
    return &lobby->members[(usize)room_index * lobby->max_members + slot];
}

static BreakRuntimeError authenticate(const BreakLobbyAuth *auth,
                                      BreakOnlineIdentity *out)
{
    BreakOnlineIdentity identity = {0u, 0u};
    if (!auth || !out || !auth->session || !auth->source.authenticate) {
        return BREAK_RUNTIME_INVALID;
    }
    if (!auth->source.authenticate(auth->source.user, auth->session, &identity) ||
        !identity.session_id || !identity.player_id) {
        return BREAK_RUNTIME_REJECTED;
    }
    *out = identity;
    return BREAK_RUNTIME_OK;
}

static BreakRuntimeError find_room(BreakLobby *lobby, BreakOnlineHandle handle,
                                   u32 *out_index, LobbyRoom **out_room)
{
    LobbyRoom *room;
    if (!break_online_handle_valid(handle) || handle.index >= lobby->max_rooms) {
        return BREAK_RUNTIME_INVALID;
    }
    room = &lobby->rooms[handle.index];
    if (!room->used || room->generation != handle.generation) {
        return BREAK_RUNTIME_STALE;
    }
    if (out_index) *out_index = handle.index;
    if (out_room) *out_room = room;
    return BREAK_RUNTIME_OK;
}

static BreakRuntimeError find_member(BreakLobby *lobby,
                                     BreakOnlineMemberHandle handle,
                                     u32 *out_room_index, LobbyRoom **out_room,
                                     u32 *out_slot, LobbyMember **out_member)
{
    BreakRuntimeError result;
    u32 room_index;
    LobbyRoom *room;
    LobbyMember *member;
    result = find_room(lobby, handle.room, &room_index, &room);
    if (result != BREAK_RUNTIME_OK) return result;
    if (!break_online_handle_valid(handle.member) ||
        handle.member.index >= lobby->max_members) {
        return BREAK_RUNTIME_INVALID;
    }
    member = member_at(lobby, room_index, handle.member.index);
    if (!member->used || member->generation != handle.member.generation) {
        return BREAK_RUNTIME_STALE;
    }
    if (out_room_index) *out_room_index = room_index;
    if (out_room) *out_room = room;
    if (out_slot) *out_slot = handle.member.index;
    if (out_member) *out_member = member;
    return BREAK_RUNTIME_OK;
}

static bool room_matches(const LobbyRoom *room, const BreakLobbyMatchQuery *query)
{
    if (!room->used || !room->listed) return false;
    if (query && query->filter_region && query->region != room->region) return false;
    if (query && query->filter_mode && query->mode != room->mode) return false;
    return true;
}

static bool room_has_player(const BreakLobby *lobby, u32 room_index, u64 player_id)
{
    u32 slot;
    for (slot = 0u; slot < lobby->max_members; ++slot) {
        const LobbyMember *member = member_at_const(lobby, room_index, slot);
        if (member->used && member->identity.player_id == player_id) return true;
    }
    return false;
}

static bool valid_name(const char *name, usize *out_size)
{
    usize size = 0u;
    if (!name) return false;
    while (size < BREAK_LOBBY_NAME_CAP && name[size] != '\0') ++size;
    if (size == 0u || size == BREAK_LOBBY_NAME_CAP) return false;
    *out_size = size;
    return true;
}

static BreakOnlineHandle room_handle(u32 index, const LobbyRoom *room)
{
    BreakOnlineHandle handle = {index, room->generation};
    return handle;
}

static u64 room_order_key(u32 index, const LobbyRoom *room)
{
    return ((u64)room->generation << 32u) | index;
}

BreakRuntimeError break_lobby_create(const BreakLobbyConfig *config,
                                     BreakLobby **out_lobby)
{
    BreakLobby *lobby;
    u32 max_rooms = BREAK_LOBBY_DEFAULT_MAX_ROOMS;
    u32 max_members = BREAK_LOBBY_DEFAULT_MAX_MEMBERS;
    usize member_slots;
    if (!out_lobby) return BREAK_RUNTIME_INVALID;
    *out_lobby = NULL;
    if (config) {
        max_rooms = config->max_rooms;
        max_members = config->max_members_per_room;
    }
    if (!max_rooms || !max_members ||
        max_rooms > BREAK_LOBBY_HARD_MAX_ROOMS ||
        max_members > BREAK_LOBBY_HARD_MAX_MEMBERS) {
        return BREAK_RUNTIME_INVALID;
    }
    member_slots = (usize)max_rooms * max_members;
    if (member_slots > SIZE_MAX / sizeof(LobbyMember)) return BREAK_RUNTIME_INVALID;
    lobby = (BreakLobby *)calloc(1u, sizeof(*lobby));
    if (!lobby) return BREAK_RUNTIME_OOM;
    lobby->rooms = (LobbyRoom *)calloc(max_rooms, sizeof(*lobby->rooms));
    lobby->members = (LobbyMember *)calloc(member_slots, sizeof(*lobby->members));
    if (!lobby->rooms || !lobby->members) {
        free(lobby->members);
        free(lobby->rooms);
        free(lobby);
        return BREAK_RUNTIME_OOM;
    }
    lobby->owner = platform_thread_current_id();
    lobby->max_rooms = max_rooms;
    lobby->max_members = max_members;
    *out_lobby = lobby;
    return BREAK_RUNTIME_OK;
}

void break_lobby_destroy(BreakLobby *lobby)
{
    if (!lobby || !lobby_owner(lobby)) return;
    free(lobby->members);
    free(lobby->rooms);
    free(lobby);
}

u32 break_lobby_room_count(const BreakLobby *lobby)
{
    return lobby_owner(lobby) ? lobby->room_count : 0u;
}

BreakRuntimeError break_lobby_room_create(BreakLobby *lobby,
                                          const BreakLobbyAuth *auth,
                                          const BreakLobbyRoomDesc *desc,
                                          BreakOnlineHandle *out_room,
                                          BreakOnlineMemberHandle *out_member)
{
    BreakOnlineIdentity identity;
    BreakRuntimeError result;
    usize name_size;
    u32 room_index;
    u32 slot;
    LobbyRoom *room = NULL;
    LobbyMember *member;
    BreakOnlineHandle new_room;
    BreakOnlineMemberHandle new_member;
    if (!lobby_owner(lobby)) return BREAK_RUNTIME_REJECTED;
    if (!desc || !out_room || !out_member || !desc->max_members ||
        desc->max_members > lobby->max_members ||
        !valid_name(desc->name, &name_size)) {
        return BREAK_RUNTIME_INVALID;
    }
    result = authenticate(auth, &identity);
    if (result != BREAK_RUNTIME_OK) return result;
    if (lobby->room_count == lobby->max_rooms) return BREAK_RUNTIME_OVERLOAD;
    for (room_index = 0u; room_index < lobby->max_rooms; ++room_index) {
        if (!lobby->rooms[room_index].used &&
            lobby->rooms[room_index].generation != UINT32_MAX) {
            room = &lobby->rooms[room_index];
            break;
        }
    }
    if (!room) return BREAK_RUNTIME_OVERLOAD;
    {
        u32 generation = next_generation(room->generation);
        memset(room, 0, sizeof(*room));
        room->generation = generation;
    }
    for (slot = 0u; slot < lobby->max_members; ++slot) {
        member = member_at(lobby, room_index, slot);
        memset(member, 0, sizeof(*member));
        member->generation = 1u;
    }
    memcpy(room->name, desc->name, name_size + 1u);
    room->region = desc->region;
    room->mode = desc->mode;
    room->max_members = desc->max_members;
    room->listed = desc->listed;
    room->used = true;
    room->member_count = 1u;
    room->host_slot = 0u;
    room->host_epoch = 1u;
    room->next_join_order = 2u;
    member = member_at(lobby, room_index, 0u);
    member->used = true;
    member->session_key = auth->session;
    member->identity = identity;
    member->join_order = 1u;
    lobby->room_count++;
    new_room = room_handle(room_index, room);
    new_member.room = new_room;
    new_member.member.index = 0u;
    new_member.member.generation = member->generation;
    *out_room = new_room;
    *out_member = new_member;
    return BREAK_RUNTIME_OK;
}

static BreakRuntimeError join_resolved(BreakLobby *lobby, u32 room_index,
                                       LobbyRoom *room, u64 session_key,
                                       BreakOnlineIdentity identity,
                                       BreakOnlineMemberHandle *out_member)
{
    u32 slot;
    LobbyMember *member = NULL;
    BreakOnlineMemberHandle result;
    if (room_has_player(lobby, room_index, identity.player_id)) {
        return BREAK_RUNTIME_REJECTED;
    }
    if (room->member_count == room->max_members) return BREAK_RUNTIME_OVERLOAD;
    if (room->next_join_order == UINT64_MAX) return BREAK_RUNTIME_OVERLOAD;
    for (slot = 0u; slot < room->max_members; ++slot) {
        LobbyMember *candidate = member_at(lobby, room_index, slot);
        if (!candidate->used && candidate->generation != UINT32_MAX) {
            member = candidate;
            break;
        }
    }
    if (!member) return BREAK_RUNTIME_OVERLOAD;
    {
        u32 generation = next_generation(member->generation);
        memset(member, 0, sizeof(*member));
        member->generation = generation;
    }
    member->used = true;
    member->session_key = session_key;
    member->identity = identity;
    member->join_order = room->next_join_order++;
    room->member_count++;
    result.room = room_handle(room_index, room);
    result.member.index = slot;
    result.member.generation = member->generation;
    *out_member = result;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_lobby_join(BreakLobby *lobby,
                                   const BreakLobbyAuth *auth,
                                   BreakOnlineHandle room_handle_value,
                                   BreakOnlineMemberHandle *out_member)
{
    BreakOnlineIdentity identity;
    BreakRuntimeError result;
    u32 room_index;
    LobbyRoom *room;
    if (!lobby_owner(lobby)) return BREAK_RUNTIME_REJECTED;
    if (!out_member) return BREAK_RUNTIME_INVALID;
    result = authenticate(auth, &identity);
    if (result != BREAK_RUNTIME_OK) return result;
    result = find_room(lobby, room_handle_value, &room_index, &room);
    if (result != BREAK_RUNTIME_OK) return result;
    return join_resolved(lobby, room_index, room, auth->session, identity, out_member);
}

static u32 oldest_member(const BreakLobby *lobby, u32 room_index,
                         const LobbyRoom *room)
{
    u32 slot;
    u32 best = UINT32_MAX;
    u64 best_order = UINT64_MAX;
    for (slot = 0u; slot < room->max_members; ++slot) {
        const LobbyMember *member = member_at_const(lobby, room_index, slot);
        if (member->used && member->join_order < best_order) {
            best = slot;
            best_order = member->join_order;
        }
    }
    return best;
}

static void remove_member(BreakLobby *lobby, u32 room_index, LobbyRoom *room,
                          u32 slot)
{
    LobbyMember *member = member_at(lobby, room_index, slot);
    u32 generation = retired_generation(member->generation);
    bool was_host = room->host_slot == slot;
    memset(member, 0, sizeof(*member));
    member->generation = generation;
    room->member_count--;
    if (room->member_count == 0u) {
        room->used = false;
        room->generation = retired_generation(room->generation);
        lobby->room_count--;
    } else if (was_host) {
        room->host_slot = oldest_member(lobby, room_index, room);
        room->host_epoch++;
    }
}

BreakRuntimeError break_lobby_leave(BreakLobby *lobby,
                                    const BreakLobbyAuth *auth,
                                    BreakOnlineMemberHandle member_handle)
{
    BreakOnlineIdentity identity;
    BreakRuntimeError result;
    u32 room_index;
    u32 slot;
    LobbyRoom *room;
    LobbyMember *member;
    if (!lobby_owner(lobby)) return BREAK_RUNTIME_REJECTED;
    result = authenticate(auth, &identity);
    if (result != BREAK_RUNTIME_OK) return result;
    result = find_member(lobby, member_handle, &room_index, &room, &slot, &member);
    if (result != BREAK_RUNTIME_OK) return result;
    if (member->session_key != auth->session ||
        member->identity.session_id != identity.session_id ||
        member->identity.player_id != identity.player_id) {
        return BREAK_RUNTIME_REJECTED;
    }
    if (room->member_count > 1u && room->host_slot == slot &&
        room->host_epoch == UINT64_MAX) {
        return BREAK_RUNTIME_OVERLOAD;
    }
    remove_member(lobby, room_index, room, slot);
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_lobby_disconnect(BreakLobby *lobby, u64 session)
{
    u32 room_index;
    if (!lobby_owner(lobby)) return BREAK_RUNTIME_REJECTED;
    if (!session) return BREAK_RUNTIME_INVALID;
    for (room_index = 0u; room_index < lobby->max_rooms; ++room_index) {
        LobbyRoom *room = &lobby->rooms[room_index];
        u32 slot;
        if (!room->used || room->member_count <= 1u ||
            room->host_epoch != UINT64_MAX) {
            continue;
        }
        if (!member_at(lobby, room_index, room->host_slot)->used) continue;
        if (member_at(lobby, room_index, room->host_slot)->session_key != session) continue;
        for (slot = 0u; slot < room->max_members; ++slot) {
            if (member_at(lobby, room_index, slot)->used &&
                member_at(lobby, room_index, slot)->session_key == session) {
                break;
            }
        }
        if (slot == room->max_members) continue;
        if (room->host_epoch == UINT64_MAX) return BREAK_RUNTIME_OVERLOAD;
    }
    for (room_index = 0u; room_index < lobby->max_rooms; ++room_index) {
        LobbyRoom *room = &lobby->rooms[room_index];
        u32 slot = 0u;
        if (!room->used) continue;
        while (slot < room->max_members) {
            LobbyMember *member = member_at(lobby, room_index, slot);
            if (member->used && member->session_key == session) {
                remove_member(lobby, room_index, room, slot);
                if (!room->used) break;
            } else {
                ++slot;
            }
        }
    }
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_lobby_match(BreakLobby *lobby,
                                    const BreakLobbyAuth *auth,
                                    const BreakLobbyMatchQuery *query,
                                    BreakOnlineHandle *out_room,
                                    BreakOnlineMemberHandle *out_member)
{
    BreakOnlineIdentity identity;
    BreakRuntimeError result;
    u32 room_index;
    u32 best_index = UINT32_MAX;
    LobbyRoom *best = NULL;
    if (!lobby_owner(lobby)) return BREAK_RUNTIME_REJECTED;
    if (!out_room || !out_member) return BREAK_RUNTIME_INVALID;
    result = authenticate(auth, &identity);
    if (result != BREAK_RUNTIME_OK) return result;
    for (room_index = 0u; room_index < lobby->max_rooms; ++room_index) {
        LobbyRoom *room = &lobby->rooms[room_index];
        if (!room_matches(room, query) || room->member_count == room->max_members ||
            room_has_player(lobby, room_index, identity.player_id)) {
            continue;
        }
        if (!best || room->member_count > best->member_count ||
            (room->member_count == best->member_count &&
             room_order_key(room_index, room) < room_order_key(best_index, best))) {
            best = room;
            best_index = room_index;
        }
    }
    if (!best) return BREAK_RUNTIME_FAILED;
    result = join_resolved(lobby, best_index, best, auth->session, identity, out_member);
    if (result == BREAK_RUNTIME_OK) *out_room = room_handle(best_index, best);
    return result;
}

BreakRuntimeError break_lobby_list(const BreakLobby *lobby,
                                   const BreakLobbyMatchQuery *query,
                                   u32 offset, BreakLobbyRoomInfo *out,
                                   u32 capacity, u32 *out_count,
                                   u32 *out_next_offset)
{
    u32 room_index;
    u32 matching = 0u;
    u32 copied = 0u;
    if (!lobby_owner(lobby)) return BREAK_RUNTIME_REJECTED;
    if (!out || !capacity || !out_count || !out_next_offset) {
        return BREAK_RUNTIME_INVALID;
    }
    for (room_index = 0u; room_index < lobby->max_rooms; ++room_index) {
        if (room_matches(&lobby->rooms[room_index], query)) ++matching;
    }
    if (offset > matching) return BREAK_RUNTIME_INVALID;
    matching = 0u;
    for (room_index = 0u; room_index < lobby->max_rooms; ++room_index) {
        if (!room_matches(&lobby->rooms[room_index], query)) continue;
        if (matching >= offset && copied < capacity) {
            BreakRuntimeError result = break_lobby_room_info(
                lobby, room_handle(room_index, &lobby->rooms[room_index]), &out[copied]);
            if (result != BREAK_RUNTIME_OK) return result;
            ++copied;
        }
        ++matching;
    }
    *out_count = copied;
    *out_next_offset = offset + copied < matching ? offset + copied : 0u;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_lobby_room_info(const BreakLobby *lobby,
                                        BreakOnlineHandle handle,
                                        BreakLobbyRoomInfo *out)
{
    BreakRuntimeError result;
    LobbyRoom *room;
    const LobbyMember *host;
    BreakLobbyRoomInfo info;
    if (!lobby_owner(lobby)) return BREAK_RUNTIME_REJECTED;
    if (!out) return BREAK_RUNTIME_INVALID;
    result = find_room((BreakLobby *)lobby, handle, NULL, &room);
    if (result != BREAK_RUNTIME_OK) return result;
    host = member_at_const(lobby, handle.index, room->host_slot);
    if (!host->used) return BREAK_RUNTIME_FAILED;
    memset(&info, 0, sizeof(info));
    info.room = handle;
    memcpy(info.name, room->name, sizeof(info.name));
    info.region = room->region;
    info.mode = room->mode;
    info.max_members = room->max_members;
    info.listed = room->listed;
    info.member_count = room->member_count;
    info.host = host->identity;
    info.host_epoch = room->host_epoch;
    *out = info;
    return BREAK_RUNTIME_OK;
}
