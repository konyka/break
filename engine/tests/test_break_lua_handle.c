#include "test_framework.h"
#include <script/break_lua.h>
#include <script/break_lua_test_hooks.h>

#include <lua/lua.h>

#include <string.h>

static const char kEcho[] =
    "function echo(value)\n"
    "    return value\n"
    "end\n"
    "function describe(value)\n"
    "    print(value)\n"
    "    return tostring(value), debug == nil and package == nil\n"
    "end\n";

static const char kSpin[] =
    "function spin()\n"
    "    for i = 1, 1000000 do end\n"
    "end\n";

TEST(host_handle_release_and_slot_reuse_reject_stale_generation)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    BreakLuaHostHandle handles[BREAK_LUA_MAX_HOST_HANDLES];
    BreakLuaHostHandle extra = {0u, 0u};
    BreakLuaHostHandle old;
    u64 token = 0u;
    u32 i;
    ASSERT_NOT_NULL(rt);
    ASSERT_EQ(break_lua_host_handle_acquire(NULL, 1u, &handles[0]),
              BREAK_LUA_INVALID);
    for (i = 0u; i < BREAK_LUA_MAX_HOST_HANDLES; i++) {
        ASSERT_EQ(break_lua_host_handle_acquire(rt, 1000u + i, &handles[i]),
                  BREAK_LUA_OK);
        ASSERT_EQ(handles[i].generation, 1u);
        ASSERT_EQ(break_lua_host_handle_resolve(rt, handles[i], &token),
                  BREAK_LUA_OK);
        ASSERT_EQ(token, 1000u + i);
    }
    ASSERT_EQ(break_lua_host_handle_acquire(rt, 9999u, &extra),
              BREAK_LUA_OVERLOAD);

    old = handles[0];
    ASSERT_EQ(break_lua_host_handle_release(rt, old), BREAK_LUA_OK);
    ASSERT_EQ(break_lua_host_handle_resolve(rt, old, &token), BREAK_LUA_STALE);
    ASSERT_EQ(break_lua_host_handle_release(rt, old), BREAK_LUA_STALE);
    ASSERT_EQ(break_lua_host_handle_acquire(rt, 7777u, &extra), BREAK_LUA_OK);
    ASSERT_EQ(extra.slot, old.slot);
    ASSERT_EQ(extra.generation, old.generation + 1u);
    ASSERT_EQ(break_lua_host_handle_resolve(rt, old, &token), BREAK_LUA_STALE);
    ASSERT_EQ(break_lua_host_handle_resolve(rt, extra, &token), BREAK_LUA_OK);
    ASSERT_EQ(token, 7777u);

    ASSERT_EQ(break_lua_host_handle_release(rt, extra), BREAK_LUA_OK);
    for (i = 1u; i < BREAK_LUA_MAX_HOST_HANDLES; i++) {
        ASSERT_EQ(break_lua_host_handle_release(rt, handles[i]), BREAK_LUA_OK);
    }
    break_lua_runtime_destroy(rt);
}

TEST(host_handle_round_trips_through_lua_without_exposing_a_pointer)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    BreakLuaHostHandle handle = {0u, 0u};
    BreakLuaValue arg;
    BreakLuaValue ret;
    ASSERT_NOT_NULL(rt);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "handles", kEcho, strlen(kEcho)),
              BREAK_LUA_OK);
    ASSERT_EQ(break_lua_host_handle_acquire(rt, 0x12345678u, &handle),
              BREAK_LUA_OK);
    memset(&arg, 0, sizeof(arg));
    arg.type = BREAK_LUA_VALUE_HOST_HANDLE;
    arg.as.handle = handle;
    ASSERT_EQ(break_lua_runtime_call(rt, "handles", "echo", &arg, 1u,
                                     &ret, 1u),
              BREAK_LUA_OK);
    ASSERT_EQ(ret.type, BREAK_LUA_VALUE_HOST_HANDLE);
    ASSERT_EQ(ret.as.handle.slot, handle.slot);
    ASSERT_EQ(ret.as.handle.generation, handle.generation);
    ASSERT_EQ(lua_gettop((lua_State *)break_lua_test_lua_state(rt)), 0);

    ASSERT_EQ(break_lua_host_handle_release(rt, handle), BREAK_LUA_OK);
    ASSERT_EQ(break_lua_runtime_call(rt, "handles", "echo", &arg, 1u,
                                     &ret, 1u),
              BREAK_LUA_STALE);
    ASSERT_EQ(ret.type, BREAK_LUA_VALUE_NIL);
    ASSERT_EQ(lua_gettop((lua_State *)break_lua_test_lua_state(rt)), 0);
    break_lua_runtime_destroy(rt);
}

TEST(direct_module_call_obeys_instruction_budget_and_recovers)
{
    BreakLuaRuntimeConfig config;
    BreakLuaRuntime *rt;
    BreakLuaValue value;
    BreakLuaValue result;
    memset(&config, 0, sizeof(config));
    config.instruction_budget = 1000u;
    rt = break_lua_runtime_create(&config);
    ASSERT_NOT_NULL(rt);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "spin", kSpin, strlen(kSpin)),
              BREAK_LUA_OK);
    ASSERT_EQ(break_lua_runtime_call(rt, "spin", "spin", NULL, 0u, NULL, 0u),
              BREAK_LUA_FAILED);
    ASSERT_EQ(break_lua_runtime_budget_trip_count(rt), 1u);
    ASSERT_EQ(lua_gettop((lua_State *)break_lua_test_lua_state(rt)), 0);

    ASSERT_EQ(break_lua_runtime_load_module(rt, "echo", kEcho, strlen(kEcho)),
              BREAK_LUA_OK);
    memset(&value, 0, sizeof(value));
    value.type = BREAK_LUA_VALUE_NUMBER;
    value.as.n = 19.0;
    ASSERT_EQ(break_lua_runtime_call(rt, "echo", "echo", &value, 1u,
                                     &result, 1u),
              BREAK_LUA_OK);
    ASSERT_EQ(result.type, BREAK_LUA_VALUE_NUMBER);
    ASSERT_FLOAT_EQ(result.as.n, 19.0, 1e-12);
    ASSERT_EQ(break_lua_runtime_budget_trip_count(rt), 1u);
    break_lua_runtime_destroy(rt);
}

TEST(host_handle_tostring_and_print_do_not_expose_an_address)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    BreakLuaHostHandle handle = {0u, 0u};
    BreakLuaValue arg;
    BreakLuaValue ret[2];
    ASSERT_NOT_NULL(rt);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "handles", kEcho, strlen(kEcho)),
              BREAK_LUA_OK);
    ASSERT_EQ(break_lua_host_handle_acquire(rt, 55u, &handle), BREAK_LUA_OK);
    memset(&arg, 0, sizeof(arg));
    arg.type = BREAK_LUA_VALUE_HOST_HANDLE;
    arg.as.handle = handle;
    ASSERT_EQ(break_lua_runtime_call(rt, "handles", "describe", &arg, 1u,
                                     ret, 2u),
              BREAK_LUA_OK);
    ASSERT_EQ(ret[0].type, BREAK_LUA_VALUE_STRING);
    ASSERT_STR_EQ(ret[0].as.s.data, "break_lua.host_handle");
    ASSERT_EQ(ret[1].type, BREAK_LUA_VALUE_BOOL);
    ASSERT_TRUE(ret[1].as.b);
    ASSERT_EQ(break_lua_host_handle_release(rt, handle), BREAK_LUA_OK);
    break_lua_runtime_destroy(rt);
}

TEST_MAIN_BEGIN()
    RUN_TEST(host_handle_release_and_slot_reuse_reject_stale_generation);
    RUN_TEST(host_handle_round_trips_through_lua_without_exposing_a_pointer);
    RUN_TEST(direct_module_call_obeys_instruction_budget_and_recovers);
    RUN_TEST(host_handle_tostring_and_print_do_not_expose_an_address);
TEST_MAIN_END()
