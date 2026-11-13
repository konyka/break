#include "test_framework.h"
#include <game/break_game_lua.h>

#include <string.h>

static const char kBadActor[] =
    "function on_actor_tick(actor, dt)\n"
    "    error('bad actor')\n"
    "end\n";

static const char kGoodActor[] =
    "function on_actor_tick(actor, dt)\n"
    "    state.count = (state.count or 0) + 1\n"
    "    state.actor = actor\n"
    "    state.dt = dt\n"
    "end\n"
    "function get_count()\n"
    "    return state.count\n"
    "end\n"
    "function get_actor()\n"
    "    return state.actor\n"
    "end\n"
    "function get_dt()\n"
    "    return state.dt\n"
    "end\n";

static World *make_world(void)
{
    World *world = world_create();
    if (world) {
        world_register_component(world, BREAK_GAME_POSITION_COMPONENT,
                                 sizeof(Vec3));
    }
    return world;
}

static u32 register_class(BreakGame *game, const char *name,
                          const char *module)
{
    BreakGameClassDesc desc;
    u32 id = 0u;
    memset(&desc, 0, sizeof(desc));
    desc.name = name;
    desc.lua_module = module;
    if (break_game_register_class(game, &desc, &id) != BREAK_GAME_OK) {
        return 0u;
    }
    return id;
}

static Entity spawn_actor(BreakGame *game, u32 class_id)
{
    BreakGameSpawn spawn;
    Entity entity = ENTITY_NULL;
    memset(&spawn, 0, sizeof(spawn));
    spawn.class_id = class_id;
    if (break_game_spawn(game, &spawn, &entity) != BREAK_GAME_OK) {
        return ENTITY_NULL;
    }
    return entity;
}

static BreakLuaValue call_value(BreakLuaRuntime *runtime, const char *module,
                                const char *function)
{
    BreakLuaValue result;
    memset(&result, 0, sizeof(result));
    if (break_lua_runtime_call(runtime, module, function, NULL, 0u,
                               &result, 1u) != BREAK_LUA_OK) {
        memset(&result, 0, sizeof(result));
    }
    return result;
}

TEST(actor_lua_tick_isolates_failure_and_uses_stable_stale_checked_identity)
{
    World *world = make_world();
    BreakGame *game = break_game_create(world, NULL);
    BreakLuaRuntime *runtime = break_lua_runtime_create(NULL);
    BreakGameLuaAdapter *adapter;
    u32 bad_class;
    u32 good_class;
    Entity bad;
    Entity good;
    Entity replacement;
    BreakLuaValue value;
    BreakLuaHostHandle handle;
    BreakLuaHostHandle replacement_handle;
    BreakGameLuaFault fault;
    u64 token = 0u;
    ASSERT_NOT_NULL(world);
    ASSERT_NOT_NULL(game);
    ASSERT_NOT_NULL(runtime);
    ASSERT_EQ(break_lua_runtime_load_module(runtime, "bad_actor", kBadActor,
                                            strlen(kBadActor)),
              BREAK_LUA_OK);
    ASSERT_EQ(break_lua_runtime_load_module(runtime, "good_actor", kGoodActor,
                                            strlen(kGoodActor)),
              BREAK_LUA_OK);
    bad_class = register_class(game, "bad", "bad_actor");
    good_class = register_class(game, "good", "good_actor");
    ASSERT_TRUE(bad_class != 0u && good_class != 0u);
    adapter = break_game_lua_create(game, runtime);
    ASSERT_NOT_NULL(adapter);
    bad = spawn_actor(game, bad_class);
    good = spawn_actor(game, good_class);
    ASSERT_TRUE(entity_valid(bad) && entity_valid(good));

    break_game_tick(game, 0.25f);
    value = call_value(runtime, "good_actor", "get_actor");
    ASSERT_EQ(value.type, BREAK_LUA_VALUE_HOST_HANDLE);
    handle = value.as.handle;
    break_game_tick(game, 0.25f);
    value = call_value(runtime, "good_actor", "get_actor");
    ASSERT_EQ(value.type, BREAK_LUA_VALUE_HOST_HANDLE);
    ASSERT_EQ(value.as.handle.slot, handle.slot);
    ASSERT_EQ(value.as.handle.generation, handle.generation);
    value = call_value(runtime, "good_actor", "get_count");
    ASSERT_EQ(value.type, BREAK_LUA_VALUE_NUMBER);
    ASSERT_FLOAT_EQ(value.as.n, 2.0, 1e-12);
    fault = break_game_lua_last_fault(adapter);
    ASSERT_TRUE(fault.valid);
    ASSERT_EQ(fault.total, 2u);
    ASSERT_EQ(fault.entity.index, bad.index);
    ASSERT_EQ(fault.entity.generation, bad.generation);
    ASSERT_EQ(fault.error, BREAK_LUA_FAILED);
    ASSERT_STR_EQ(fault.module, "bad_actor");

    value = call_value(runtime, "good_actor", "get_actor");
    ASSERT_EQ(value.type, BREAK_LUA_VALUE_HOST_HANDLE);
    handle = value.as.handle;
    ASSERT_EQ(break_lua_host_handle_resolve(runtime, handle, &token),
              BREAK_LUA_OK);
    ASSERT_EQ((u32)(token & UINT64_C(0xffffffff)), good.index);
    ASSERT_EQ((u32)(token >> 32), good.generation);
    value = call_value(runtime, "good_actor", "get_dt");
    ASSERT_FLOAT_EQ(value.as.n, 0.25, 1e-6);

    ASSERT_EQ(break_game_despawn(game, good), BREAK_GAME_OK);
    ASSERT_EQ(break_lua_host_handle_resolve(runtime, handle, &token),
              BREAK_LUA_STALE);
    replacement = spawn_actor(game, good_class);
    ASSERT_TRUE(entity_valid(replacement));
    ASSERT_EQ(replacement.index, good.index);
    ASSERT_TRUE(replacement.generation != good.generation);
    break_game_tick(game, 0.5f);
    value = call_value(runtime, "good_actor", "get_actor");
    replacement_handle = value.as.handle;
    ASSERT_EQ(value.type, BREAK_LUA_VALUE_HOST_HANDLE);
    ASSERT_TRUE(replacement_handle.generation != handle.generation);
    ASSERT_EQ(break_lua_host_handle_resolve(runtime, handle, &token),
              BREAK_LUA_STALE);
    ASSERT_EQ(break_lua_host_handle_resolve(runtime, replacement_handle, &token),
              BREAK_LUA_OK);
    ASSERT_EQ((u32)(token >> 32), replacement.generation);

    break_game_lua_destroy(adapter);
    break_lua_runtime_destroy(runtime);
    break_game_destroy(game);
    world_destroy(world);
}

TEST(actor_missing_hook_is_a_local_fault_and_does_not_block_sibling)
{
    static const char empty_module[] = "marker = 1\n";
    World *world = make_world();
    BreakGame *game = break_game_create(world, NULL);
    BreakLuaRuntime *runtime = break_lua_runtime_create(NULL);
    BreakGameLuaAdapter *adapter;
    u32 missing_class;
    u32 good_class;
    Entity missing;
    Entity good;
    BreakLuaValue value;
    BreakGameLuaFault fault;
    ASSERT_NOT_NULL(world);
    ASSERT_NOT_NULL(game);
    ASSERT_NOT_NULL(runtime);
    ASSERT_EQ(break_lua_runtime_load_module(runtime, "missing_hook",
                                            empty_module, strlen(empty_module)),
              BREAK_LUA_OK);
    ASSERT_EQ(break_lua_runtime_load_module(runtime, "good_actor", kGoodActor,
                                            strlen(kGoodActor)),
              BREAK_LUA_OK);
    missing_class = register_class(game, "missing", "missing_hook");
    good_class = register_class(game, "good", "good_actor");
    adapter = break_game_lua_create(game, runtime);
    ASSERT_NOT_NULL(adapter);
    missing = spawn_actor(game, missing_class);
    good = spawn_actor(game, good_class);
    ASSERT_TRUE(entity_valid(missing) && entity_valid(good));
    break_game_tick(game, 0.25f);
    value = call_value(runtime, "good_actor", "get_count");
    ASSERT_FLOAT_EQ(value.as.n, 1.0, 1e-12);
    fault = break_game_lua_last_fault(adapter);
    ASSERT_EQ(fault.total, 1u);
    ASSERT_EQ(fault.entity.index, missing.index);
    ASSERT_EQ(fault.error, BREAK_LUA_INVALID);
    ASSERT_STR_EQ(fault.module, "missing_hook");
    break_game_lua_destroy(adapter);
    break_lua_runtime_destroy(runtime);
    break_game_destroy(game);
    world_destroy(world);
}

TEST(actor_stats_count_ticks_and_failures_per_actor)
{
    World *world = make_world();
    BreakGame *game = break_game_create(world, NULL);
    BreakLuaRuntime *runtime = break_lua_runtime_create(NULL);
    BreakGameLuaAdapter *adapter;
    BreakGameLuaActorStats stats;
    u32 bad_class;
    u32 good_class;
    Entity bad;
    Entity good;
    Entity replacement;
    u32 i;
    ASSERT_NOT_NULL(world);
    ASSERT_NOT_NULL(game);
    ASSERT_NOT_NULL(runtime);
    ASSERT_EQ(break_lua_runtime_load_module(runtime, "bad_actor", kBadActor,
                                            strlen(kBadActor)),
              BREAK_LUA_OK);
    ASSERT_EQ(break_lua_runtime_load_module(runtime, "good_actor", kGoodActor,
                                            strlen(kGoodActor)),
              BREAK_LUA_OK);
    bad_class = register_class(game, "bad", "bad_actor");
    good_class = register_class(game, "good", "good_actor");
    adapter = break_game_lua_create(game, runtime);
    ASSERT_NOT_NULL(adapter);
    bad = spawn_actor(game, bad_class);
    good = spawn_actor(game, good_class);
    ASSERT_TRUE(entity_valid(bad) && entity_valid(good));
    for (i = 0u; i < 60u; i++) {
        break_game_tick(game, 1.0f / 60.0f);
    }
    ASSERT_EQ(break_game_lua_actor_stats(adapter, good, &stats), BREAK_LUA_OK);
    ASSERT_EQ(stats.ticks, 60u);
    ASSERT_EQ(stats.failures, 0u);
    ASSERT_EQ(stats.skipped, 0u);
    ASSERT_FALSE(stats.disabled);
    ASSERT_EQ(break_game_lua_actor_stats(adapter, bad, &stats), BREAK_LUA_OK);
    ASSERT_EQ(stats.ticks, 0u);
    ASSERT_EQ(stats.failures, 60u);
    ASSERT_EQ(stats.last_error, BREAK_LUA_FAILED);
    ASSERT_FALSE(stats.disabled);

    ASSERT_EQ(break_game_despawn(game, good), BREAK_GAME_OK);
    ASSERT_EQ(break_game_lua_actor_stats(adapter, good, &stats), BREAK_LUA_STALE);
    ASSERT_EQ(stats.ticks, 0u);
    replacement = spawn_actor(game, good_class);
    ASSERT_EQ(replacement.index, good.index);
    ASSERT_EQ(break_game_lua_actor_stats(adapter, replacement, &stats), BREAK_LUA_OK);
    ASSERT_EQ(stats.ticks, 0u);
    break_game_tick(game, 1.0f / 60.0f);
    ASSERT_EQ(break_game_lua_actor_stats(adapter, replacement, &stats), BREAK_LUA_OK);
    ASSERT_EQ(stats.ticks, 1u);
    ASSERT_EQ(break_game_lua_actor_stats(adapter, good, &stats), BREAK_LUA_STALE);
    ASSERT_EQ(break_game_lua_actor_stats(NULL, good, &stats), BREAK_LUA_INVALID);
    ASSERT_EQ(break_game_lua_actor_stats(adapter, good, NULL), BREAK_LUA_INVALID);

    break_game_lua_destroy(adapter);
    break_lua_runtime_destroy(runtime);
    break_game_destroy(game);
    world_destroy(world);
}

TEST(actor_budget_trip_disables_only_that_module)
{
    static const char runaway[] =
        "function on_actor_tick(actor, dt)\n"
        "    while true do end\n"
        "end\n";
    BreakLuaRuntimeConfig config;
    World *world = make_world();
    BreakGame *game = break_game_create(world, NULL);
    BreakLuaRuntime *runtime;
    BreakGameLuaAdapter *adapter;
    BreakGameLuaActorStats stats;
    BreakLuaValue value;
    u32 runaway_class;
    u32 good_class;
    Entity first;
    Entity second;
    Entity good;
    u64 trips_before;
    memset(&config, 0, sizeof(config));
    config.instruction_budget = 10000u;
    runtime = break_lua_runtime_create(&config);
    ASSERT_NOT_NULL(world);
    ASSERT_NOT_NULL(game);
    ASSERT_NOT_NULL(runtime);
    ASSERT_EQ(break_lua_runtime_load_module(runtime, "runaway", runaway,
                                            strlen(runaway)),
              BREAK_LUA_OK);
    ASSERT_EQ(break_lua_runtime_load_module(runtime, "good_actor", kGoodActor,
                                            strlen(kGoodActor)),
              BREAK_LUA_OK);
    runaway_class = register_class(game, "runaway", "runaway");
    good_class = register_class(game, "good", "good_actor");
    adapter = break_game_lua_create(game, runtime);
    ASSERT_NOT_NULL(adapter);
    first = spawn_actor(game, runaway_class);
    second = spawn_actor(game, runaway_class);
    good = spawn_actor(game, good_class);
    ASSERT_TRUE(entity_valid(first) && entity_valid(second) && entity_valid(good));
    trips_before = break_lua_runtime_budget_trip_count(runtime);
    break_game_tick(game, 0.25f);
    break_game_tick(game, 0.25f);
    break_game_tick(game, 0.25f);
    ASSERT_EQ(break_lua_runtime_budget_trip_count(runtime) - trips_before, 1u);
    ASSERT_EQ(break_game_lua_actor_stats(adapter, first, &stats), BREAK_LUA_OK);
    ASSERT_EQ(stats.failures, 1u);
    ASSERT_EQ(stats.skipped, 2u);
    ASSERT_TRUE(stats.disabled);
    ASSERT_EQ(break_game_lua_actor_stats(adapter, second, &stats), BREAK_LUA_OK);
    ASSERT_EQ(stats.failures, 0u);
    ASSERT_EQ(stats.skipped, 3u);
    ASSERT_TRUE(stats.disabled);
    ASSERT_EQ(break_game_lua_actor_stats(adapter, good, &stats), BREAK_LUA_OK);
    ASSERT_EQ(stats.ticks, 3u);
    ASSERT_FALSE(stats.disabled);
    value = call_value(runtime, "good_actor", "get_count");
    ASSERT_FLOAT_EQ(value.as.n, 3.0, 1e-12);
    break_game_lua_destroy(adapter);
    break_lua_runtime_destroy(runtime);
    break_game_destroy(game);
    world_destroy(world);
}

TEST_MAIN_BEGIN()
    RUN_TEST(actor_lua_tick_isolates_failure_and_uses_stable_stale_checked_identity);
    RUN_TEST(actor_missing_hook_is_a_local_fault_and_does_not_block_sibling);
    RUN_TEST(actor_stats_count_ticks_and_failures_per_actor);
    RUN_TEST(actor_budget_trip_disables_only_that_module);
TEST_MAIN_END()
