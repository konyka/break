/* ==========================================================================
 *  test_script_lua.c — real Lua 5.4 scripting + engine bindings.
 * ========================================================================== */

#include "test_framework.h"
#include <script/script_lua.h>
#include <ecs/ecs.h>
#include <physics/physics.h>
#include <math.h>
#include <stdio.h>
#if defined(_WIN32)
#include <direct.h>
#else
#include <sys/stat.h>
#include <unistd.h>
#endif

/* ----------------------------------------------------------------------- */

TEST(init_shutdown)
{
    LuaScript ls;
    ASSERT_TRUE(lua_script_init(&ls));
    ASSERT_NOT_NULL(ls.L);
    ASSERT_TRUE(!ls.loaded);
    lua_script_shutdown(&ls);
    ASSERT_TRUE(ls.L == NULL);
}

TEST(run_string_sets_global)
{
    LuaScript ls;
    ASSERT_TRUE(lua_script_init(&ls));
    ASSERT_TRUE(lua_script_load_string(&ls, "health = 42\nspeed = 3.5", "t"));
    ASSERT_TRUE(fabs(lua_script_get_number(&ls, "health", -1) - 42.0) < 1e-9);
    ASSERT_TRUE(fabs(lua_script_get_number(&ls, "speed", -1) - 3.5) < 1e-9);
    ASSERT_TRUE(fabs(lua_script_get_number(&ls, "missing", 7.0) - 7.0) < 1e-9);
    lua_script_shutdown(&ls);
}

TEST(host_set_get_number)
{
    LuaScript ls;
    ASSERT_TRUE(lua_script_init(&ls));
    lua_script_set_number(&ls, "gravity", -9.81);
    /* Script can read a host-provided global. */
    ASSERT_TRUE(lua_script_load_string(&ls, "g2 = gravity * 2", "t"));
    ASSERT_TRUE(fabs(lua_script_get_number(&ls, "g2", 0) - (-19.62)) < 1e-6);
    lua_script_shutdown(&ls);
}

TEST(syntax_error_reports_false)
{
    LuaScript ls;
    ASSERT_TRUE(lua_script_init(&ls));
    /* Malformed chunk must fail gracefully (no crash, returns false). */
    ASSERT_TRUE(!lua_script_load_string(&ls, "function bad( = end", "bad"));
    ASSERT_TRUE(!ls.loaded);
    lua_script_shutdown(&ls);
}

TEST(runtime_error_reports_false)
{
    LuaScript ls;
    ASSERT_TRUE(lua_script_init(&ls));
    ASSERT_TRUE(!lua_script_load_string(&ls, "error('boom')", "boom"));
    lua_script_shutdown(&ls);
}

TEST(hooks_detected)
{
    LuaScript ls;
    ASSERT_TRUE(lua_script_init(&ls));
    ASSERT_TRUE(lua_script_load_string(&ls,
        "function on_start() end\n"
        "function on_update(dt) end\n", "t"));
    ASSERT_TRUE(ls.has_start);
    ASSERT_TRUE(ls.has_update);
    ASSERT_TRUE(!ls.has_spawn);
    lua_script_shutdown(&ls);
}

TEST(on_update_receives_dt)
{
    LuaScript ls;
    ASSERT_TRUE(lua_script_init(&ls));
    ASSERT_TRUE(lua_script_load_string(&ls,
        "acc = 0\nfunction on_update(dt) acc = acc + dt end", "t"));
    lua_script_call_update(&ls, 0.5f);
    lua_script_call_update(&ls, 0.25f);
    ASSERT_TRUE(fabs(lua_script_get_number(&ls, "acc", 0) - 0.75) < 1e-6);
    lua_script_shutdown(&ls);
}

TEST(call_void_missing_is_safe)
{
    LuaScript ls;
    ASSERT_TRUE(lua_script_init(&ls));
    ASSERT_TRUE(lua_script_load_string(&ls, "x = 1", "t"));
    ASSERT_TRUE(!lua_script_call_void(&ls, "no_such_fn"));
    lua_script_shutdown(&ls);
}

/* ---- engine.* bindings against real host systems ---------------------- */

TEST(engine_body_count_and_spawn)
{
    PhysicsWorld *pw = physics_world_create(64);
    /* C indices 0/1 → Lua ids 1/2; spawn returns 1-based id. */
    physics_body_create(pw, vec3(0, -1, 0), vec3(10, 1, 10), 0.0f, true, 0);
    physics_body_create(pw, vec3(0, 5, 0), vec3(0.5f, 0.5f, 0.5f), 1.0f, false, 0);

    LuaScript ls;
    ASSERT_TRUE(lua_script_init(&ls));
    lua_script_bind_host(&ls, NULL, pw, NULL);

    ASSERT_TRUE(lua_script_load_string(&ls,
        "function on_start()\n"
        "  before = engine.body_count()\n"
        "  new_id = engine.spawn(1, 10, 1, 2.0)\n"
        "  after = engine.body_count()\n"
        "end", "t"));
    lua_script_call_start(&ls);

    ASSERT_TRUE(fabs(lua_script_get_number(&ls, "before", -1) - 2.0) < 1e-9);
    ASSERT_TRUE(fabs(lua_script_get_number(&ls, "after", -1) - 3.0) < 1e-9);
    /* R354: C id 2 → Lua id 3 */
    ASSERT_TRUE(fabs(lua_script_get_number(&ls, "new_id", -1) - 3.0) < 1e-9);
    ASSERT_EQ(pw->count, 3u);

    lua_script_shutdown(&ls);
    physics_world_destroy(pw);
}

TEST(engine_spawn_first_body_is_lua_id_1)
{
    /* R354: first spawn must return 1 and address bodies[0]. */
    PhysicsWorld *pw = physics_world_create(64);
    LuaScript ls;
    ASSERT_TRUE(lua_script_init(&ls));
    lua_script_bind_host(&ls, NULL, pw, NULL);

    ASSERT_TRUE(lua_script_load_string(&ls,
        "id = engine.spawn(1, 2, 3, 1.0)\n"
        "px, py, pz = engine.get_pos(id)\n", "t"));
    ASSERT_TRUE(fabs(lua_script_get_number(&ls, "id", -1) - 1.0) < 1e-9);
    ASSERT_TRUE(fabs(lua_script_get_number(&ls, "px", 0) - 1.0) < 1e-5);
    ASSERT_TRUE(fabs(lua_script_get_number(&ls, "py", 0) - 2.0) < 1e-5);
    ASSERT_TRUE(fabs(pw->bodies[0].position.e[1] - 2.0f) < 1e-5f);

    lua_script_shutdown(&ls);
    physics_world_destroy(pw);
}

/* R409: Lua body id 0 is invalid (floor/none sentinel); must not touch bodies[0]. */
TEST(engine_id_zero_is_invalid)
{
    PhysicsWorld *pw = physics_world_create(64);
    physics_body_create(pw, vec3(1, 2, 3), vec3(0.5f, 0.5f, 0.5f), 1.0f, false, 0);

    LuaScript ls;
    ASSERT_TRUE(lua_script_init(&ls));
    lua_script_bind_host(&ls, NULL, pw, NULL);

    ASSERT_TRUE(lua_script_load_string(&ls,
        "engine.set_pos(0, 9, 9, 9)\n"
        "n = engine.get_pos(0)\n"
        "px, py, pz = engine.get_pos(1)\n", "t"));

    ASSERT_TRUE(fabs(lua_script_get_number(&ls, "px", -99) - 1.0) < 1e-5);
    ASSERT_TRUE(fabs(lua_script_get_number(&ls, "py", -99) - 2.0) < 1e-5);
    ASSERT_TRUE(fabs(lua_script_get_number(&ls, "pz", -99) - 3.0) < 1e-5);
    ASSERT_TRUE(fabs(pw->bodies[0].position.e[0] - 1.0f) < 1e-5f);
    ASSERT_TRUE(fabs(pw->bodies[0].position.e[1] - 2.0f) < 1e-5f);

    lua_script_shutdown(&ls);
    physics_world_destroy(pw);
}

TEST(engine_out_of_range_body_id_is_invalid)
{
    /* R465: Lua integers are wider than u32 on supported hosts. A body id of
     * 2^32+1 used to truncate to 1 before the 1-based conversion, mutating
     * body 0 through every body binding. */
    PhysicsWorld *pw = physics_world_create(64);
    physics_body_create(pw, vec3(1, 2, 3), vec3(0.5f, 0.5f, 0.5f), 1.0f, false, 0);
    pw->bodies[0].velocity = vec3(4, 5, 6);
    pw->bodies[0].ccd = false;

    LuaScript ls;
    ASSERT_TRUE(lua_script_init(&ls));
    lua_script_bind_host(&ls, NULL, pw, NULL);
    ASSERT_TRUE(lua_script_load_string(&ls,
        "bad = 4294967297\n"
        "engine.set_pos(bad, 9, 9, 9)\n"
        "engine.set_vel(bad, 8, 8, 8)\n"
        "engine.apply_impulse(bad, 7, 7, 7)\n"
        "engine.body_set_ccd(bad, true)\n"
        "n = engine.get_pos(bad)\n", "t"));

    ASSERT_TRUE(fabsf(pw->bodies[0].position.e[0] - 1.0f) < 1e-5f);
    ASSERT_TRUE(fabsf(pw->bodies[0].velocity.e[0] - 4.0f) < 1e-5f);
    ASSERT_FALSE(pw->bodies[0].ccd);
    /* Invalid get_pos returns no Lua values, so assignment leaves n as nil. */
    ASSERT_TRUE(fabs(lua_script_get_number(&ls, "n", -1.0) - (-1.0)) < 1e-9);

    lua_script_shutdown(&ls);
    physics_world_destroy(pw);
}

TEST(engine_pos_vel_impulse)
{
    PhysicsWorld *pw = physics_world_create(64);
    physics_body_create(pw, vec3(0, -1, 0), vec3(10, 1, 10), 0.0f, true, 0); /* Lua 1 */
    physics_body_create(pw, vec3(0, 5, 0), vec3(0.5f, 0.5f, 0.5f), 2.0f, false, 0); /* Lua 2 */

    LuaScript ls;
    ASSERT_TRUE(lua_script_init(&ls));
    lua_script_bind_host(&ls, NULL, pw, NULL);

    ASSERT_TRUE(lua_script_load_string(&ls,
        "engine.set_pos(2, 3, 4, 5)\n"
        "px, py, pz = engine.get_pos(2)\n"
        "engine.apply_impulse(2, 0, 20, 0)\n"   /* mass 2 -> +10 vel.y */
        "vx, vy, vz = engine.get_vel(2)\n", "t"));

    ASSERT_TRUE(fabs(lua_script_get_number(&ls, "px", 0) - 3.0) < 1e-5);
    ASSERT_TRUE(fabs(lua_script_get_number(&ls, "py", 0) - 4.0) < 1e-5);
    ASSERT_TRUE(fabs(lua_script_get_number(&ls, "pz", 0) - 5.0) < 1e-5);
    ASSERT_TRUE(fabs(lua_script_get_number(&ls, "vy", 0) - 10.0) < 1e-4);

    /* Confirm the C-side body actually moved. */
    ASSERT_TRUE(fabs(pw->bodies[1].position.e[0] - 3.0f) < 1e-5f);
    ASSERT_TRUE(fabs(pw->bodies[1].velocity.e[1] - 10.0f) < 1e-4f);

    lua_script_shutdown(&ls);
    physics_world_destroy(pw);
}

TEST(engine_entity_count_binding)
{
    World *w = world_create();
    world_register_component(w, 1, sizeof(float));
    Entity e1 = world_create_entity(w);
    Entity e2 = world_create_entity(w);
    world_add_component(w, e1, 1);
    world_add_component(w, e2, 1);

    LuaScript ls;
    ASSERT_TRUE(lua_script_init(&ls));
    lua_script_bind_host(&ls, w, NULL, NULL);
    ASSERT_TRUE(lua_script_load_string(&ls, "n = engine.entity_count()", "t"));
    ASSERT_TRUE(lua_script_get_number(&ls, "n", -1) >= 2.0);

    lua_script_shutdown(&ls);
    world_destroy(w);
}

TEST(engine_bindings_null_host_safe)
{
    /* No host bound: every engine.* call must be a safe no-op / default. */
    LuaScript ls;
    ASSERT_TRUE(lua_script_init(&ls));
    ASSERT_TRUE(lua_script_load_string(&ls,
        "bc = engine.body_count()\n"
        "ec = engine.entity_count()\n"
        "engine.set_pos(1, 1, 2, 3)\n"            /* no-op */
        "engine.apply_impulse(1, 0, 1, 0)\n"      /* no-op */
        "kd = engine.key_down(65)\n"
        "sid = engine.spawn(0, 0, 0)\n", "t"));
    ASSERT_TRUE(fabs(lua_script_get_number(&ls, "bc", -1)) < 1e-9);
    ASSERT_TRUE(fabs(lua_script_get_number(&ls, "ec", -1)) < 1e-9);
    ASSERT_TRUE(fabs(lua_script_get_number(&ls, "sid", -1)) < 1e-9);
    lua_script_shutdown(&ls);
}

/* ---- hot reload ------------------------------------------------------- */

TEST(hot_reload_runs_new_chunk)
{
    char path[64]; test_tmp(path, sizeof path, "test_break_reload.lua"); /* R444: per-pid path — parallel ctest trees raced on the fixed name */
    FILE *f = fopen(path, "w");
    ASSERT_NOT_NULL(f);
    fprintf(f, "version = 1\nfunction on_update(dt) result = 10 end\n");
    fclose(f);

    LuaScript ls;
    ASSERT_TRUE(lua_script_init(&ls));
    ASSERT_TRUE(lua_script_load(&ls, path));
    ASSERT_TRUE(fabs(lua_script_get_number(&ls, "version", -1) - 1.0) < 1e-9);
    lua_script_call_update(&ls, 0.0f);
    ASSERT_TRUE(fabs(lua_script_get_number(&ls, "result", -1) - 10.0) < 1e-9);

    /* Rewrite the file with new behavior, then force a reload (mtime may share
     * the same second as the initial load, so reset the tracker). */
    f = fopen(path, "w");
    ASSERT_NOT_NULL(f);
    fprintf(f, "version = 2\nfunction on_update(dt) result = 20 end\n");
    fclose(f);
    ls.last_mtime = 0;
    lua_script_reload_if_changed(&ls);

    ASSERT_TRUE(fabs(lua_script_get_number(&ls, "version", -1) - 2.0) < 1e-9);
    lua_script_call_update(&ls, 0.0f);
    ASSERT_TRUE(fabs(lua_script_get_number(&ls, "result", -1) - 20.0) < 1e-9);

    lua_script_shutdown(&ls);
}

TEST(hot_reload_no_change_no_run)
{
    char path[64]; test_tmp(path, sizeof path, "test_break_noreload.lua"); /* R444: per-pid path — parallel ctest trees raced on the fixed name */
    FILE *f = fopen(path, "w");
    ASSERT_NOT_NULL(f);
    fprintf(f, "counter = (counter or 0) + 1\n");
    fclose(f);

    LuaScript ls;
    ASSERT_TRUE(lua_script_init(&ls));
    ASSERT_TRUE(lua_script_load(&ls, path));
    ASSERT_TRUE(fabs(lua_script_get_number(&ls, "counter", -1) - 1.0) < 1e-9);

    /* mtime unchanged -> chunk must NOT re-run, counter stays 1. */
    lua_script_reload_if_changed(&ls);
    ASSERT_TRUE(fabs(lua_script_get_number(&ls, "counter", -1) - 1.0) < 1e-9);

    lua_script_shutdown(&ls);
}

/* R486: a failed reload must not consume the new mtime; otherwise fixing the
 * same file later leaves the previous hooks active until another edit occurs. */
TEST(hot_reload_retries_after_failed_candidate)
{
    char path[64]; test_tmp(path, sizeof path, "test_break_retry.lua");
    FILE *f = fopen(path, "w");
    ASSERT_NOT_NULL(f);
    fprintf(f, "version = 1\nfunction on_update(dt) result = 10 end\n");
    fclose(f);

    LuaScript ls;
    ASSERT_TRUE(lua_script_init(&ls));
    ASSERT_TRUE(lua_script_load(&ls, path));
    ls.last_mtime = 0u;  /* Force a reload without relying on timestamp granularity. */

    f = fopen(path, "w");
    ASSERT_NOT_NULL(f);
    fprintf(f, "function broken( = end\n");
    fclose(f);
    lua_script_reload_if_changed(&ls);
    ASSERT_EQ(ls.last_mtime, 0u);
    lua_script_call_update(&ls, 0.0f);
    ASSERT_TRUE(fabs(lua_script_get_number(&ls, "result", -1) - 10.0) < 1e-9);

    f = fopen(path, "w");
    ASSERT_NOT_NULL(f);
    fprintf(f, "version = 2\nfunction on_update(dt) result = 20 end\n");
    fclose(f);
    lua_script_reload_if_changed(&ls);
    ASSERT_TRUE(fabs(lua_script_get_number(&ls, "version", -1) - 2.0) < 1e-9);
    lua_script_call_update(&ls, 0.0f);
    ASSERT_TRUE(fabs(lua_script_get_number(&ls, "result", -1) - 20.0) < 1e-9);

    lua_script_shutdown(&ls);
    remove(path);
}

/* A candidate can assign globals before it reports a runtime error. Its
 * partial hook replacement must not escape into the running script. */
TEST(hot_reload_runtime_failure_preserves_previous_hooks)
{
    char path[64]; test_tmp(path, sizeof path, "test_break_atomic_reload.lua");
    FILE *f = fopen(path, "w");
    ASSERT_NOT_NULL(f);
    fprintf(f, "version = 1\nfunction on_update(dt) result = 10 end\n");
    fclose(f);

    LuaScript ls;
    ASSERT_TRUE(lua_script_init(&ls));
    ASSERT_TRUE(lua_script_load(&ls, path));
    ls.last_mtime = 0u;

    f = fopen(path, "w");
    ASSERT_NOT_NULL(f);
    fprintf(f, "version = 2\ncandidate_only = 99\nfunction on_update(dt) result = 20 end\nerror('boom')\n");
    fclose(f);
    lua_script_reload_if_changed(&ls);

    ASSERT_EQ(ls.last_mtime, 0u);
    ASSERT_TRUE(fabs(lua_script_get_number(&ls, "version", -1) - 1.0) < 1e-9);
    ASSERT_TRUE(fabs(lua_script_get_number(&ls, "candidate_only", -1) - (-1.0)) < 1e-9);
    lua_script_call_update(&ls, 0.0f);
    ASSERT_TRUE(fabs(lua_script_get_number(&ls, "result", -1) - 10.0) < 1e-9);

    lua_script_shutdown(&ls);
    remove(path);
}

/* An explicit replacement that reaches a runtime error must leave the last
 * successfully loaded file as the hot-reload identity. */
TEST(load_runtime_failure_preserves_previous_reload_identity)
{
    char old_path[64], bad_path[64];
    test_tmp(old_path, sizeof old_path, "test_break_old_identity.lua");
    test_tmp(bad_path, sizeof bad_path, "test_break_bad_identity.lua");
    FILE *f = fopen(old_path, "w");
    ASSERT_NOT_NULL(f);
    fprintf(f, "version = 1\nfunction on_update(dt) result = 10 end\n");
    fclose(f);
    f = fopen(bad_path, "w");
    ASSERT_NOT_NULL(f);
    fprintf(f, "version = 2\nerror('boom')\n");
    fclose(f);

    LuaScript ls;
    ASSERT_TRUE(lua_script_init(&ls));
    ASSERT_TRUE(lua_script_load(&ls, old_path));
    u32 old_mtime = ls.last_mtime;
    ASSERT_FALSE(lua_script_load(&ls, bad_path));
    ASSERT_STR_EQ(ls.path, old_path);
    ASSERT_EQ(ls.last_mtime, old_mtime);
    lua_script_call_update(&ls, 0.0f);
    ASSERT_TRUE(fabs(lua_script_get_number(&ls, "result", -1) - 10.0) < 1e-9);

    lua_script_shutdown(&ls);
    remove(old_path);
    remove(bad_path);
}

TEST(load_nonexistent_file)
{
    LuaScript ls;
    ASSERT_TRUE(lua_script_init(&ls));
    char path[128];
    test_tmp(path, sizeof path, "no_such_break_script_xyz.lua");
    ASSERT_TRUE(!lua_script_load(&ls, path));
    ASSERT_TRUE(!ls.loaded);
    lua_script_shutdown(&ls);
}

/* R469: LuaScript keeps the hot-reload identity in a 256-byte path field.
 * A file whose full path is exactly that size used to load once, then retain a
 * truncated path for future reloads. Reject it before executing the chunk. */
TEST(lua_load_rejects_path_truncation)
{
    char dir[220];
    char base[64];
    test_tmp(base, sizeof base, "lua_long");
    for (char *c = base; *c; c++) if (*c == '\\') *c = '/';
    int n = snprintf(dir, sizeof(dir), "%s_", base);
    ASSERT_TRUE(n > 0 && (usize)n < sizeof(dir));
    memset(dir + n, 'd', 180u - (usize)n);
    ASSERT_TRUE(n < 180);
    dir[180] = '\0';
    ASSERT_TRUE(TEST_MKDIR(dir) == 0);

    char name[76];
    memset(name, 's', sizeof(name) - 5u);
    memcpy(name + sizeof(name) - 5u, ".lua", 5u);

    char path[257];
    n = snprintf(path, sizeof(path), "%s/%s", dir, name);
    ASSERT_EQ(n, 256);
    FILE *f = fopen(path, "w");
    ASSERT_NOT_NULL(f);
    fputs("loaded = true\n", f);
    fclose(f);

    LuaScript ls;
    ASSERT_TRUE(lua_script_init(&ls));
    ASSERT_TRUE(!lua_script_load(&ls, path));
    ASSERT_TRUE(!ls.loaded);
    ASSERT_EQ(ls.path[0], '\0');
    lua_script_shutdown(&ls);

    remove(path);
    TEST_RMDIR(dir);
}

/* R395: luaL_loadfile reads the whole file; cap size before calling it. */
TEST(lua_load_rejects_oversized_file)
{
    char path[64]; test_tmp(path, sizeof path, "test_lua_huge.lua"); /* R444: per-pid path — parallel ctest trees raced on the fixed name */
    FILE *f = fopen(path, "wb");
    ASSERT_NOT_NULL(f);
#if defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE >= 200112L
    ASSERT_TRUE(ftruncate(fileno(f), (off_t)LUA_SCRIPT_MAX_FILE_BYTES + 1) == 0);
#else
    if (fseek(f, (long)LUA_SCRIPT_MAX_FILE_BYTES, SEEK_SET) == 0) fputc('x', f);
#endif
    fclose(f);

    LuaScript ls;
    ASSERT_TRUE(lua_script_init(&ls));
    ASSERT_TRUE(!lua_script_load(&ls, path));
    ASSERT_TRUE(!ls.loaded);
    lua_script_shutdown(&ls);
    remove(path);
}

TEST(engine_set_pos_wakes_resting_body)
{
    /* R423: set_pos teleports a body. It must reset rest_frames and mark the
     * BVH dirty — a resting body (rest_frames > 2) is skipped by the BVH
     * refit, so without the reset it keeps its stale AABB at the old location
     * and collisions at the new location are missed (mirrors R374/R375). */
    PhysicsWorld *pw = physics_world_create(64);
    physics_body_create(pw, vec3(0, -1, 0), vec3(10, 1, 10), 0.0f, true, 0);   /* Lua 1: ground, top y=0 */
    physics_body_create(pw, vec3(50, 5, 0), vec3(0.5f, 0.5f, 0.5f), 1.0f, false, 0); /* Lua 2: far away */

    /* Simulate a body that has gone to rest with a settled BVH (as after many
     * idle frames: rest_frames > 2 excludes it from the refit). */
    pw->bodies[1].rest_frames = 100u;
    pw->bodies[1].velocity = vec3(0, 0, 0);
    pw->bvh_dirty = false;

    LuaScript ls;
    ASSERT_TRUE(lua_script_init(&ls));
    lua_script_bind_host(&ls, NULL, pw, NULL);
    /* Teleport the resting body so it overlaps the ground. */
    ASSERT_TRUE(lua_script_load_string(&ls, "engine.set_pos(2, 0, 0.25, 0)", "t"));

    /* The teleport must wake the body and force a BVH refit. */
    ASSERT_TRUE(fabs(pw->bodies[1].position.e[1] - 0.25f) < 1e-5f);
    ASSERT_EQ(pw->bodies[1].rest_frames, 0u);
    ASSERT_TRUE(pw->bvh_dirty);

    /* With the refit forced, the overlap at the new location is detected. */
    u32 collided = 0u;
    for (int i = 0; i < 30 && !collided; i++) {
        physics_step(pw, 1.0f / 60.0f);
        collided = pw->collision_count;
    }
    ASSERT_TRUE(collided > 0u);

    lua_script_shutdown(&ls);
    physics_world_destroy(pw);
}

/* ----------------------------------------------------------------------- */

TEST_MAIN_BEGIN()
    RUN_TEST(init_shutdown);
    RUN_TEST(run_string_sets_global);
    RUN_TEST(host_set_get_number);
    RUN_TEST(syntax_error_reports_false);
    RUN_TEST(runtime_error_reports_false);
    RUN_TEST(hooks_detected);
    RUN_TEST(on_update_receives_dt);
    RUN_TEST(call_void_missing_is_safe);
    RUN_TEST(engine_body_count_and_spawn);
    RUN_TEST(engine_spawn_first_body_is_lua_id_1);
    RUN_TEST(engine_id_zero_is_invalid);
    RUN_TEST(engine_out_of_range_body_id_is_invalid);
    RUN_TEST(engine_pos_vel_impulse);
    RUN_TEST(engine_entity_count_binding);
    RUN_TEST(engine_bindings_null_host_safe);
    RUN_TEST(hot_reload_runs_new_chunk);
    RUN_TEST(hot_reload_no_change_no_run);
    RUN_TEST(hot_reload_retries_after_failed_candidate);
    RUN_TEST(hot_reload_runtime_failure_preserves_previous_hooks);
    RUN_TEST(load_runtime_failure_preserves_previous_reload_identity);
    RUN_TEST(load_nonexistent_file);
    RUN_TEST(lua_load_rejects_path_truncation);
    RUN_TEST(lua_load_rejects_oversized_file);
    RUN_TEST(engine_set_pos_wakes_resting_body);
TEST_MAIN_END()
