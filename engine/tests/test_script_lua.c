/* ==========================================================================
 *  test_script_lua.c — real Lua 5.4 scripting + engine bindings.
 * ========================================================================== */

#include "test_framework.h"
#include <script/script_lua.h>
#include <ecs/ecs.h>
#include <physics/physics.h>
#include <math.h>
#include <stdio.h>

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
    const char *path = "/tmp/test_break_reload.lua";
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
    const char *path = "/tmp/test_break_noreload.lua";
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

TEST(load_nonexistent_file)
{
    LuaScript ls;
    ASSERT_TRUE(lua_script_init(&ls));
    ASSERT_TRUE(!lua_script_load(&ls, "/tmp/no_such_break_script_xyz.lua"));
    ASSERT_TRUE(!ls.loaded);
    lua_script_shutdown(&ls);
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
    RUN_TEST(engine_pos_vel_impulse);
    RUN_TEST(engine_entity_count_binding);
    RUN_TEST(engine_bindings_null_host_safe);
    RUN_TEST(hot_reload_runs_new_chunk);
    RUN_TEST(hot_reload_no_change_no_run);
    RUN_TEST(load_nonexistent_file);
TEST_MAIN_END()
