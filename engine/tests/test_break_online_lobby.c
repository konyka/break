#include "test_framework.h"
#include <network/break_online_lobby.h>
#include <core/platform_thread.h>

#include <stdint.h>
#include <string.h>

typedef struct FakeAuth {
    u64 session;
    bool authenticated;
    u64 session_id;
    u64 player_id;
    u32 calls;
} FakeAuth;

static bool fake_authenticate(void *user, u64 session, BreakOnlineIdentity *out)
{
    FakeAuth *auth = (FakeAuth *)user;
    auth->calls++;
    if (!auth->authenticated || auth->session != session) return false;
    out->session_id = auth->session_id;
    out->player_id = auth->player_id;
    return true;
}

static FakeAuth make_fake(u64 session, bool authenticated, u64 player_id)
{
    FakeAuth auth;
    memset(&auth, 0, sizeof(auth));
    auth.session = session;
    auth.authenticated = authenticated;
    auth.session_id = player_id + 1000u;
    auth.player_id = player_id;
    return auth;
}

static BreakLobbyAuth make_auth(FakeAuth *auth)
{
    BreakLobbyAuth result;
    result.session = auth->session;
    result.source.user = auth;
    result.source.authenticate = fake_authenticate;
    result.source.session_key = NULL;
    return result;
}

static BreakLobbyRoomDesc make_desc(const char *name, u16 region, u16 mode,
                                    u16 max_members)
{
    BreakLobbyRoomDesc desc;
    memset(&desc, 0, sizeof(desc));
    desc.name = name;
    desc.region = region;
    desc.mode = mode;
    desc.max_members = max_members;
    desc.listed = true;
    return desc;
}

static BreakLobbyMatchQuery make_query(u16 region, u16 mode)
{
    BreakLobbyMatchQuery query;
    memset(&query, 0, sizeof(query));
    query.region = region;
    query.mode = mode;
    query.filter_region = true;
    query.filter_mode = true;
    return query;
}

static BreakLobby *make_lobby(u32 max_rooms, u32 max_members)
{
    BreakLobbyConfig config;
    BreakLobby *lobby = NULL;
    memset(&config, 0, sizeof(config));
    config.max_rooms = max_rooms;
    config.max_members_per_room = max_members;
    if (break_lobby_create(&config, &lobby) != BREAK_RUNTIME_OK) return NULL;
    return lobby;
}

static BreakOnlineHandle create_room(BreakLobby *lobby, FakeAuth *fake,
                                     const BreakLobbyRoomDesc *desc,
                                     BreakOnlineMemberHandle *member)
{
    BreakOnlineHandle room = {UINT32_MAX, UINT32_MAX};
    BreakLobbyAuth auth = make_auth(fake);
    if (break_lobby_room_create(lobby, &auth, desc, &room, member) != BREAK_RUNTIME_OK) {
        room.index = UINT32_MAX;
    }
    return room;
}

TEST(lobby_rejects_unauthenticated_identity_without_creating_room)
{
    BreakLobby *lobby = make_lobby(2u, 2u);
    FakeAuth fake = make_fake(11u, false, 101u);
    BreakLobbyAuth auth = make_auth(&fake);
    BreakLobbyRoomDesc desc = make_desc("one", 7u, 3u, 2u);
    BreakOnlineHandle room = {99u, 99u};
    BreakOnlineMemberHandle member = {{99u, 99u}, {99u, 99u}};
    ASSERT_NOT_NULL(lobby);
    ASSERT_EQ(break_lobby_room_create(lobby, &auth, &desc, &room, &member),
              BREAK_RUNTIME_REJECTED);
    ASSERT_EQ(room.index, 99u);
    ASSERT_EQ(member.member.index, 99u);
    ASSERT_EQ(break_lobby_room_count(lobby), 0u);
    ASSERT_EQ(fake.calls, 1u);
    break_lobby_destroy(lobby);
}

TEST(lobby_create_join_and_room_info_use_authenticated_identity)
{
    BreakLobby *lobby = make_lobby(2u, 3u);
    FakeAuth host = make_fake(1u, true, 100u);
    FakeAuth guest = make_fake(2u, true, 200u);
    BreakOnlineMemberHandle host_member;
    BreakOnlineMemberHandle guest_member;
    BreakLobbyRoomDesc desc = make_desc("room", 4u, 9u, 3u);
    BreakLobbyRoomInfo info;
    BreakOnlineHandle room;
    ASSERT_NOT_NULL(lobby);
    room = create_room(lobby, &host, &desc, &host_member);
    ASSERT_NEQ(room.index, UINT32_MAX);
    ASSERT_EQ(host_member.member.generation, 1u);
    ASSERT_EQ(break_lobby_join(lobby, &(BreakLobbyAuth){2u, {&guest, fake_authenticate, NULL}},
                               room, &guest_member), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_lobby_room_info(lobby, room, &info), BREAK_RUNTIME_OK);
    ASSERT_EQ(info.member_count, 2u);
    ASSERT_EQ(info.host.player_id, 100u);
    ASSERT_EQ(info.host.session_id, 1100u);
    ASSERT_EQ(info.host_epoch, 1u);
    ASSERT_STR_EQ(info.name, "room");
    ASSERT_EQ(info.region, 4u);
    ASSERT_EQ(info.mode, 9u);
    ASSERT_TRUE(info.listed);
    break_lobby_destroy(lobby);
}

TEST(lobby_rejects_duplicate_player_and_over_capacity_atomically)
{
    BreakLobby *lobby = make_lobby(1u, 2u);
    FakeAuth host = make_fake(1u, true, 100u);
    FakeAuth guest = make_fake(2u, true, 200u);
    FakeAuth duplicate = make_fake(3u, true, 200u);
    FakeAuth third = make_fake(4u, true, 300u);
    BreakOnlineMemberHandle member;
    BreakLobbyRoomDesc desc = make_desc("room", 1u, 1u, 2u);
    BreakOnlineHandle room = create_room(lobby, &host, &desc, &member);
    BreakLobbyRoomInfo before;
    BreakLobbyRoomInfo after;
    ASSERT_NEQ(room.index, UINT32_MAX);
    ASSERT_EQ(break_lobby_join(lobby, &(BreakLobbyAuth){2u, {&guest, fake_authenticate, NULL}},
                               room, &member), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_lobby_room_info(lobby, room, &before), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_lobby_join(lobby, &(BreakLobbyAuth){3u, {&duplicate, fake_authenticate, NULL}},
                               room, &member), BREAK_RUNTIME_REJECTED);
    ASSERT_EQ(break_lobby_join(lobby, &(BreakLobbyAuth){4u, {&third, fake_authenticate, NULL}},
                               room, &member), BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(break_lobby_room_info(lobby, room, &after), BREAK_RUNTIME_OK);
    ASSERT_EQ(after.member_count, before.member_count);
    ASSERT_EQ(after.host_epoch, before.host_epoch);
    ASSERT_EQ(break_lobby_room_create(lobby, &(BreakLobbyAuth){4u, {&third, fake_authenticate, NULL}},
                                      &desc, &room, &member), BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(break_lobby_room_count(lobby), 1u);
    break_lobby_destroy(lobby);
}

TEST(lobby_stale_member_and_room_handles_cannot_mutate_reused_slots)
{
    BreakLobby *lobby = make_lobby(1u, 2u);
    FakeAuth host = make_fake(1u, true, 100u);
    FakeAuth guest = make_fake(2u, true, 200u);
    FakeAuth replacement = make_fake(3u, true, 300u);
    BreakLobbyRoomDesc desc = make_desc("room", 1u, 1u, 2u);
    BreakOnlineMemberHandle host_member;
    BreakOnlineMemberHandle old_member;
    BreakOnlineMemberHandle new_member;
    BreakOnlineHandle room = create_room(lobby, &host, &desc, &host_member);
    BreakOnlineHandle old_room;
    ASSERT_EQ(break_lobby_join(lobby, &(BreakLobbyAuth){2u, {&guest, fake_authenticate, NULL}},
                               room, &old_member), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_lobby_leave(lobby, &(BreakLobbyAuth){2u, {&guest, fake_authenticate, NULL}},
                                old_member), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_lobby_join(lobby, &(BreakLobbyAuth){3u, {&replacement, fake_authenticate, NULL}},
                               room, &new_member), BREAK_RUNTIME_OK);
    ASSERT_EQ(old_member.member.index, new_member.member.index);
    ASSERT_NEQ(old_member.member.generation, new_member.member.generation);
    ASSERT_EQ(break_lobby_leave(lobby, &(BreakLobbyAuth){2u, {&guest, fake_authenticate, NULL}},
                                old_member), BREAK_RUNTIME_STALE);
    ASSERT_EQ(break_lobby_leave(lobby, &(BreakLobbyAuth){3u, {&replacement, fake_authenticate, NULL}},
                                new_member), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_lobby_leave(lobby, &(BreakLobbyAuth){1u, {&host, fake_authenticate, NULL}},
                                host_member), BREAK_RUNTIME_OK);
    old_room = room;
    room = create_room(lobby, &host, &desc, &host_member);
    ASSERT_EQ(old_room.index, room.index);
    ASSERT_NEQ(old_room.generation, room.generation);
    ASSERT_EQ(break_lobby_join(lobby, &(BreakLobbyAuth){2u, {&guest, fake_authenticate, NULL}},
                               old_room, &old_member), BREAK_RUNTIME_STALE);
    ASSERT_EQ(break_lobby_room_count(lobby), 1u);
    break_lobby_destroy(lobby);
}

TEST(lobby_host_leave_and_disconnect_migrate_to_oldest_member)
{
    BreakLobby *lobby = make_lobby(1u, 3u);
    FakeAuth host = make_fake(1u, true, 100u);
    FakeAuth second = make_fake(2u, true, 200u);
    FakeAuth third = make_fake(3u, true, 300u);
    BreakLobbyRoomDesc desc = make_desc("room", 1u, 1u, 3u);
    BreakOnlineMemberHandle host_member;
    BreakOnlineMemberHandle member;
    BreakOnlineHandle room = create_room(lobby, &host, &desc, &host_member);
    BreakLobbyRoomInfo info;
    ASSERT_EQ(break_lobby_join(lobby, &(BreakLobbyAuth){2u, {&second, fake_authenticate, NULL}},
                               room, &member), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_lobby_join(lobby, &(BreakLobbyAuth){3u, {&third, fake_authenticate, NULL}},
                               room, &member), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_lobby_leave(lobby, &(BreakLobbyAuth){1u, {&host, fake_authenticate, NULL}},
                                host_member), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_lobby_room_info(lobby, room, &info), BREAK_RUNTIME_OK);
    ASSERT_EQ(info.host.player_id, 200u);
    ASSERT_EQ(info.host_epoch, 2u);
    ASSERT_EQ(info.member_count, 2u);
    ASSERT_EQ(break_lobby_disconnect(lobby, 2u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_lobby_room_info(lobby, room, &info), BREAK_RUNTIME_OK);
    ASSERT_EQ(info.host.player_id, 300u);
    ASSERT_EQ(info.host_epoch, 3u);
    ASSERT_EQ(info.member_count, 1u);
    break_lobby_destroy(lobby);
}

TEST(lobby_disconnect_removes_every_session_membership)
{
    BreakLobby *lobby = make_lobby(2u, 2u);
    FakeAuth host = make_fake(1u, true, 100u);
    FakeAuth guest = make_fake(2u, true, 200u);
    BreakLobbyRoomDesc desc = make_desc("room", 1u, 1u, 2u);
    BreakOnlineMemberHandle member;
    BreakOnlineHandle first = create_room(lobby, &host, &desc, &member);
    BreakOnlineHandle second = create_room(lobby, &host, &desc, &member);
    BreakLobbyRoomInfo info;
    ASSERT_EQ(break_lobby_join(lobby, &(BreakLobbyAuth){2u, {&guest, fake_authenticate, NULL}},
                               second, &member), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_lobby_disconnect(lobby, 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_lobby_room_info(lobby, first, &info), BREAK_RUNTIME_STALE);
    ASSERT_EQ(break_lobby_room_info(lobby, second, &info), BREAK_RUNTIME_OK);
    ASSERT_EQ(info.host.player_id, 200u);
    ASSERT_EQ(info.member_count, 1u);
    ASSERT_EQ(break_lobby_disconnect(lobby, 1u), BREAK_RUNTIME_OK);
    break_lobby_destroy(lobby);
}

TEST(lobby_match_selects_fullest_then_lowest_generation_handle)
{
    BreakLobby *lobby = make_lobby(3u, 3u);
    FakeAuth host = make_fake(1u, true, 100u);
    FakeAuth guest = make_fake(2u, true, 200u);
    FakeAuth matcher = make_fake(3u, true, 300u);
    FakeAuth second_matcher = make_fake(4u, true, 400u);
    FakeAuth third_matcher = make_fake(5u, true, 500u);
    BreakLobbyRoomDesc desc = make_desc("room", 8u, 4u, 3u);
    BreakLobbyMatchQuery query = make_query(8u, 4u);
    BreakOnlineMemberHandle member;
    BreakOnlineHandle a = create_room(lobby, &host, &desc, &member);
    BreakOnlineHandle b = create_room(lobby, &host, &desc, &member);
    BreakOnlineHandle matched = {99u, 99u};
    BreakLobbyRoomInfo info;
    ASSERT_EQ(break_lobby_join(lobby, &(BreakLobbyAuth){2u, {&guest, fake_authenticate, NULL}},
                               b, &member), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_lobby_match(lobby, &(BreakLobbyAuth){3u, {&matcher, fake_authenticate, NULL}},
                                &query, &matched, &member), BREAK_RUNTIME_OK);
    ASSERT_EQ(matched.index, b.index);
    ASSERT_EQ(matched.generation, b.generation);
    ASSERT_EQ(break_lobby_room_info(lobby, b, &info), BREAK_RUNTIME_OK);
    ASSERT_EQ(info.member_count, 3u);
    ASSERT_EQ(break_lobby_match(lobby, &(BreakLobbyAuth){4u, {&second_matcher, fake_authenticate, NULL}},
                                &query, &matched, &member), BREAK_RUNTIME_OK);
    ASSERT_EQ(matched.index, a.index);
    query.mode = 99u;
    ASSERT_EQ(break_lobby_match(lobby, &(BreakLobbyAuth){5u, {&third_matcher, fake_authenticate, NULL}},
                                &query, &matched, &member), BREAK_RUNTIME_FAILED);
    break_lobby_destroy(lobby);
}

TEST(lobby_directory_filters_and_paginates_without_truncation)
{
    BreakLobby *lobby = make_lobby(3u, 2u);
    FakeAuth host = make_fake(1u, true, 100u);
    BreakOnlineMemberHandle member;
    BreakOnlineHandle first = create_room(lobby, &host,
        &(BreakLobbyRoomDesc){"first", 5u, 2u, 2u, true}, &member);
    BreakOnlineHandle second = create_room(lobby, &host,
        &(BreakLobbyRoomDesc){"second", 5u, 2u, 2u, true}, &member);
    BreakOnlineHandle third = create_room(lobby, &host,
        &(BreakLobbyRoomDesc){"third", 6u, 2u, 2u, true}, &member);
    BreakLobbyMatchQuery query = make_query(5u, 2u);
    BreakLobbyRoomInfo page[1];
    u32 count = 99u;
    u32 next = 99u;
    ASSERT_NEQ(third.index, UINT32_MAX);
    ASSERT_EQ(break_lobby_list(lobby, &query, 0u, page, 1u, &count, &next),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(count, 1u);
    ASSERT_EQ(next, 1u);
    ASSERT_EQ(page[0].room.index, first.index);
    ASSERT_EQ(break_lobby_list(lobby, &query, next, page, 1u, &count, &next),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(count, 1u);
    ASSERT_EQ(next, 0u);
    ASSERT_EQ(page[0].room.index, second.index);
    ASSERT_EQ(break_lobby_list(lobby, &query, 3u, page, 1u, &count, &next),
              BREAK_RUNTIME_INVALID);
    break_lobby_destroy(lobby);
}

typedef struct WrongOwnerContext {
    BreakLobby *lobby;
    FakeAuth *auth;
    BreakLobbyRoomDesc desc;
    BreakRuntimeError result;
} WrongOwnerContext;

static PLATFORM_THREAD_RET wrong_owner_create(PLATFORM_THREAD_ARG arg)
{
    WrongOwnerContext *ctx = (WrongOwnerContext *)arg;
    BreakOnlineHandle room = {0u, 0u};
    BreakOnlineMemberHandle member = {{0u, 0u}, {0u, 0u}};
    BreakLobbyAuth auth = make_auth(ctx->auth);
    ctx->result = break_lobby_room_create(ctx->lobby, &auth, &ctx->desc, &room, &member);
    return PLATFORM_THREAD_RETURN;
}

TEST(lobby_rejects_wrong_owner_without_calling_auth_or_mutating)
{
    BreakLobby *lobby = make_lobby(1u, 2u);
    FakeAuth auth = make_fake(1u, true, 100u);
    PlatformThread thread;
    WrongOwnerContext ctx;
    ASSERT_NOT_NULL(lobby);
    memset(&ctx, 0, sizeof(ctx));
    ctx.lobby = lobby;
    ctx.auth = &auth;
    ctx.desc = make_desc("wrong", 1u, 1u, 2u);
    ASSERT_TRUE(platform_thread_create(&thread, wrong_owner_create, &ctx));
    platform_thread_join(thread);
    ASSERT_EQ(ctx.result, BREAK_RUNTIME_REJECTED);
    ASSERT_EQ(auth.calls, 0u);
    ASSERT_EQ(break_lobby_room_count(lobby), 0u);
    break_lobby_destroy(lobby);
}

TEST(lobby_validates_create_arguments_without_outputs_or_slots)
{
    BreakLobbyConfig bad = {1u, 0u};
    BreakLobby *lobby = (BreakLobby *)(uintptr_t)1u;
    FakeAuth host = make_fake(1u, true, 100u);
    BreakOnlineHandle room = {8u, 8u};
    BreakOnlineMemberHandle member = {{8u, 8u}, {8u, 8u}};
    BreakLobbyRoomDesc desc = make_desc("", 1u, 1u, 2u);
    ASSERT_EQ(break_lobby_create(&bad, &lobby), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(lobby, NULL);
    lobby = make_lobby(1u, 2u);
    ASSERT_NOT_NULL(lobby);
    ASSERT_EQ(break_lobby_room_create(lobby, &(BreakLobbyAuth){1u, {&host, fake_authenticate, NULL}},
                                      &desc, &room, &member), BREAK_RUNTIME_INVALID);
    desc.name = "valid";
    desc.max_members = 3u;
    ASSERT_EQ(break_lobby_room_create(lobby, &(BreakLobbyAuth){1u, {&host, fake_authenticate, NULL}},
                                      &desc, &room, &member), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(room.index, 8u);
    ASSERT_EQ(member.member.index, 8u);
    ASSERT_EQ(break_lobby_room_count(lobby), 0u);
    break_lobby_destroy(lobby);
}

TEST_MAIN_BEGIN()
    RUN_TEST(lobby_rejects_unauthenticated_identity_without_creating_room);
    RUN_TEST(lobby_create_join_and_room_info_use_authenticated_identity);
    RUN_TEST(lobby_rejects_duplicate_player_and_over_capacity_atomically);
    RUN_TEST(lobby_stale_member_and_room_handles_cannot_mutate_reused_slots);
    RUN_TEST(lobby_host_leave_and_disconnect_migrate_to_oldest_member);
    RUN_TEST(lobby_disconnect_removes_every_session_membership);
    RUN_TEST(lobby_match_selects_fullest_then_lowest_generation_handle);
    RUN_TEST(lobby_directory_filters_and_paginates_without_truncation);
    RUN_TEST(lobby_rejects_wrong_owner_without_calling_auth_or_mutating);
    RUN_TEST(lobby_validates_create_arguments_without_outputs_or_slots);
TEST_MAIN_END()
