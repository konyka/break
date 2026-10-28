#include "test_framework.h"
#include <script/break_lua.h>
#include <script/break_lua_test_hooks.h>
#include <core/platform_thread.h>

#include <lua/lua.h>

#include <math.h>
#include <stdint.h>
#include <string.h>

#if !defined(_WIN32)
#include <sys/types.h>
#include <sys/wait.h>
#endif

/* Focused contract tests for the Stage 3 break_lua host bindings and module
 * sandbox (Task 4). Links the test-only break_lua_test variant
 * (BREAK_LUA_TESTING=1) for the allocation budget hook, the type-erased VM
 * state accessor (stack-balance assertions), and the frame-error record
 * probes; production break_lua stays hook-free. */

static usize chunk_len(const char *chunk)
{
    return strlen(chunk);
}

static lua_State *test_state(BreakLuaRuntime *rt)
{
    return (lua_State *)break_lua_test_lua_state(rt);
}

static void assert_stack_balanced(BreakLuaRuntime *rt)
{
    ASSERT_EQ(lua_gettop(test_state(rt)), 0);
}

/* ---------------------------------------------------------------------- */
/* Lua chunks under test.                                                  */

/* Enqueue two spawns around one set; per-call ok flags land in state. */
static const char kChunkEnqueue[] =
    "function enqueue_batch()\n"
    "    local o1 = brk.ecs.spawn()\n"
    "    local o2 = brk.ecs.set('pos', 'x', 42.5)\n"
    "    local o3 = brk.ecs.spawn()\n"
    "    state.ok1 = o1 and 1 or 0\n"
    "    state.ok2 = o2 and 1 or 0\n"
    "    state.ok3 = o3 and 1 or 0\n"
    "end\n";

/* Overload probe: 4 spawn attempts against a capacity-2 batch. */
static const char kChunkOverload[] =
    "function fill()\n"
    "    for i = 1, 4 do\n"
    "        local ok, err = brk.ecs.spawn()\n"
    "        state['ok' .. i] = ok and 1 or 0\n"
    "        if not ok then state.err_len = #(err or '') end\n"
    "    end\n"
    "end\n"
    "function one_more()\n"
    "    local ok = brk.ecs.spawn()\n"
    "    state.ok5 = ok and 1 or 0\n"
    "end\n";

/* One SET record per value kind. */
static const char kChunkSetKinds[] =
    "function do_sets()\n"
    "    brk.ecs.set('pos', 'x', 42.5)\n"
    "    brk.ecs.set('gfx', 'visible', true)\n"
    "    brk.ecs.set('name', 'label', 'hero')\n"
    "end\n";

/* Every malformed set shape: none may enqueue, all fail bounded. */
static const char kChunkSetInvalid[] =
    "function bad_sets()\n"
    "    local a = brk.ecs.set(123, 'x', 1)\n"
    "    local b = brk.ecs.set('', 'x', 1)\n"
    "    local c = brk.ecs.set(string.rep('c', 80), 'x', 1)\n"
    "    local d = brk.ecs.set('pos', 'x', {})\n"
    "    local e = brk.ecs.set('pos', 'x', string.rep('v', 80))\n"
    "    local f = brk.ecs.set('pos', string.rep('f', 80), 1)\n"
    "    state.a = a and 1 or 0\n"
    "    state.b = b and 1 or 0\n"
    "    state.c = c and 1 or 0\n"
    "    state.d = d and 1 or 0\n"
    "    state.e = e and 1 or 0\n"
    "    state.f = f and 1 or 0\n"
    "end\n";

/* spawn/set without a bound batch fail bounded (never block, never raise). */
static const char kChunkNoBatch[] =
    "function try_spawn()\n"
    "    local ok, err = brk.ecs.spawn()\n"
    "    state.ok = ok and 1 or 0\n"
    "    state.err_len = #(err or '')\n"
    "end\n";

/* Sandbox census: the dangerous globals must be ABSENT, the whitelist
 * present. State flag captured at chunk-load time proves the load-time
 * environment is already sandboxed. */
static const char kChunkSandbox[] =
    "if coroutine == nil then\n"
    "    state.co_absent_at_load = 1\n"
    "else\n"
    "    state.co_absent_at_load = 0\n"
    "end\n"
    "function absent()\n"
    "    return io == nil, os.execute == nil, os.remove == nil,\n"
    "           os.exit == nil, os.getenv == nil, os.rename == nil,\n"
    "           os.setlocale == nil, os.tmpname == nil,\n"
    "           debug == nil, package == nil, require == nil,\n"
    "           coroutine == nil, load == nil, loadfile == nil,\n"
    "           dofile == nil, loadstring == nil, collectgarbage == nil,\n"
    "           rawset == nil, rawget == nil, rawequal == nil,\n"
    "           rawlen == nil, setmetatable == nil, getmetatable == nil,\n"
    "           next == nil, warn == nil, unpack == nil\n"
    "end\n"
    "function present()\n"
    "    return type(os) == 'table', type(os.clock) == 'function',\n"
    "           type(os.time) == 'function', type(os.date) == 'function',\n"
    "           type(string) == 'table', type(table) == 'table',\n"
    "           type(math) == 'table', type(utf8) == 'table',\n"
    "           type(pcall) == 'function', type(xpcall) == 'function',\n"
    "           type(type) == 'function', type(tostring) == 'function',\n"
    "           type(tonumber) == 'function', type(select) == 'function',\n"
    "           type(ipairs) == 'function', type(pairs) == 'function',\n"
    "           type(error) == 'function', type(assert) == 'function',\n"
    "           type(print) == 'function', type(_VERSION) == 'string',\n"
    "           type(_G['break']) == 'table',\n"
    "           type(_G['break'].ecs) == 'table',\n"
    "           type(_G['break'].config) == 'table',\n"
    "           type(_G['break'].ecs.spawn) == 'function',\n"
    "           type(_G['break'].ecs.set) == 'function',\n"
    "           type(_G['break'].config.get) == 'function',\n"
    "           _G['break'] == brk\n"
    "end\n";

/* Calling the absent functions fails bounded (pcall catches), never touches
 * the host. */
static const char kChunkDangerCalls[] =
    "function try_danger()\n"
    "    local ok1 = pcall(os.execute, 'true')\n"
    "    local ok2 = pcall(function() return io.open('x') end)\n"
    "    return ok1 == false, ok2 == false\n"
    "end\n";

/* break.* (and the shared stdlib proxies) reject mutation from scripts. */
static const char kChunkReadonly[] =
    "function try_mutate()\n"
    "    local ok1 = pcall(function() brk.ecs.spawn = function() return true end end)\n"
    "    local ok2 = pcall(function() brk.hacked = 1 end)\n"
    "    local ok3 = pcall(function() brk.ecs = nil end)\n"
    "    local ok4 = pcall(function() brk.config.get = nil end)\n"
    "    local ok5 = pcall(function() string.rep = nil end)\n"
    "    local ok6 = pcall(function() os.clock = nil end)\n"
    "    state.m1 = ok1 and 1 or 0\n"
    "    state.m2 = ok2 and 1 or 0\n"
    "    state.m3 = ok3 and 1 or 0\n"
    "    state.m4 = ok4 and 1 or 0\n"
    "    state.m5 = ok5 and 1 or 0\n"
    "    state.m6 = ok6 and 1 or 0\n"
    "end\n"
    "function still_works()\n"
    "    local ok1, rep = pcall(string.rep, 'ab', 2)\n"
    "    local ok2, r = pcall(brk.ecs.spawn)\n"
    "    state.rep_ok = (ok1 and rep == 'abab') and 1 or 0\n"
    "    state.spawn_ok = (ok2 and r) and 1 or 0\n"
    "end\n";

/* Enumeration of the script-visible break chain finds nothing (proxies are
 * raw-empty); no reachable value is userdata. */
static const char kChunkNoPtr[] =
    "function scan_break()\n"
    "    local enumerated = 0\n"
    "    local userdata_found = 0\n"
    "    for k, v in pairs(_G['break']) do enumerated = enumerated + 1 end\n"
    "    for k, v in pairs(brk.ecs) do enumerated = enumerated + 1 end\n"
    "    for k, v in pairs(brk.config) do enumerated = enumerated + 1 end\n"
    "    if type(_G['break']) == 'userdata' then userdata_found = userdata_found + 1 end\n"
    "    if type(brk) == 'userdata' then userdata_found = userdata_found + 1 end\n"
    "    if type(brk.ecs) == 'userdata' then userdata_found = userdata_found + 1 end\n"
    "    if type(brk.ecs.spawn) == 'userdata' then userdata_found = userdata_found + 1 end\n"
    "    if brk._batch ~= nil then userdata_found = userdata_found + 1 end\n"
    "    if brk.batch ~= nil then userdata_found = userdata_found + 1 end\n"
    "    state.enumerated = enumerated\n"
    "    state.userdata_found = userdata_found\n"
    "end\n";

/* Plan checkbox (Task 3 review): a module trying coroutine.wrap inside a
 * budgeted hook must find the global absent (or trip the same budget). */
static const char kChunkCoHook[] =
    "function on_frame_begin(dt)\n"
    "    local w = coroutine.wrap(function() end)\n"
    "end\n";

/* Companion: a guarded hook observes the absence cleanly under the budget. */
static const char kChunkCoGuard[] =
    "function on_frame_begin(dt)\n"
    "    if coroutine == nil then\n"
    "        state.co_guard = 1\n"
    "        return\n"
    "    end\n"
    "    state.co_guard = 0\n"
    "end\n";

/* Cross-module stdlib integrity: module A's mutation attempts (trapped by
 * the read-only proxies) must not affect module B. */
static const char kChunkPoisonA[] =
    "function poison()\n"
    "    pcall(function() string.rep = nil end)\n"
    "    pcall(function() os.clock = nil end)\n"
    "    pcall(function() table.insert = function() end end)\n"
    "    return 1\n"
    "end\n";

static const char kChunkCheckB[] =
    "function check()\n"
    "    local rep = string.rep('q', 3)\n"
    "    local clock_ok = os.clock() >= 0\n"
    "    return rep, clock_ok\n"
    "end\n";

/* Config reads land in state for the numeric probes. */
static const char kChunkConfig[] =
    "function read_config()\n"
    "    state.fps = brk.config.get('fps')\n"
    "    state.volume = brk.config.get('volume')\n"
    "    state.bias = brk.config.get('bias')\n"
    "    local v, err = brk.config.get('nope')\n"
    "    state.unknown_nil = (v == nil) and 1 or 0\n"
    "    state.unknown_err_len = #(err or '')\n"
    "    local w = brk.config.get()\n"
    "    state.noarg_nil = (w == nil) and 1 or 0\n"
    "    local x = brk.config.get(42)\n"
    "    state.badarg_nil = (x == nil) and 1 or 0\n"
    "end\n";

/* Frame-hook enqueue path: one SET + one SPAWN per begin_frame. */
static const char kChunkFrameEnqueue[] =
    "function on_frame_begin(dt)\n"
    "    brk.ecs.set('motion', 'dt', dt)\n"
    "    brk.ecs.spawn()\n"
    "end\n";

static void assert_state_number(BreakLuaRuntime *rt, const char *module,
                                const char *key, double expected)
{
    double got = 0.0;
    ASSERT_TRUE(break_lua_test_module_state_number(rt, module, key, &got));
    ASSERT_FLOAT_EQ(got, expected, 1e-12);
}

/* ---------------------------------------------------------------------- */
/* Host-side batch lifecycle.                                              */

TEST(batch_create_capacity_validation)
{
    BreakLuaEcsBatch *def = break_lua_ecs_batch_create(0u); /* 0 => default */
    BreakLuaEcsBatch *max = break_lua_ecs_batch_create(
        BREAK_LUA_ECS_BATCH_MAX_CAPACITY);
    BreakLuaEcsRecord recs[4];
    ASSERT_NOT_NULL(def);
    ASSERT_NOT_NULL(max);
    /* Above the hard ceiling: fail-closed NULL (INVALID class). */
    ASSERT_EQ(break_lua_ecs_batch_create(BREAK_LUA_ECS_BATCH_MAX_CAPACITY + 1u),
              NULL);
    /* Checked multiply: a capacity that would wrap size_t fails closed. */
    ASSERT_EQ(break_lua_ecs_batch_create(SIZE_MAX), NULL);
    /* Empty batches drain nothing. */
    ASSERT_EQ(break_lua_ecs_batch_drain(def, recs, 4u), 0u);
    /* NULL batch / NULL out / zero capacity are bounded no-ops. */
    ASSERT_EQ(break_lua_ecs_batch_drain(NULL, recs, 4u), 0u);
    ASSERT_EQ(break_lua_ecs_batch_drain(def, NULL, 4u), 0u);
    ASSERT_EQ(break_lua_ecs_batch_drain(def, recs, 0u), 0u);
    break_lua_ecs_batch_destroy(def);
    break_lua_ecs_batch_destroy(max);
    break_lua_ecs_batch_destroy(NULL); /* NULL destroy is a no-op */
}

TEST(batch_double_destroy_aborts_in_test_builds)
{
#if !defined(_WIN32)
    pid_t pid = fork();
    if (pid == 0) {
        BreakLuaEcsBatch *b = break_lua_ecs_batch_create(8u);
        if (!b) {
            _exit(2); /* create itself failed: not the path under test */
        }
        break_lua_ecs_batch_destroy(b);
        break_lua_ecs_batch_destroy(b); /* contract violation: must abort */
        _exit(0); /* reached only if double destroy was NOT rejected */
    }
    ASSERT_TRUE(pid > 0);
    {
        int status = 0;
        ASSERT_EQ(waitpid(pid, &status, 0), pid);
        ASSERT_TRUE(WIFSIGNALED(status));
    }
    /* The parent registry is unaffected: normal lifecycle still works. */
    {
        BreakLuaEcsBatch *b = break_lua_ecs_batch_create(8u);
        ASSERT_NOT_NULL(b);
        break_lua_ecs_batch_destroy(b);
    }
#endif
}

TEST(batch_allocation_failure_injection_is_bounded)
{
    break_lua_test_set_alloc_budget(0u);
    ASSERT_EQ(break_lua_ecs_batch_create(8u), NULL);
    /* A failing records allocation frees the batch shell (ASan lane). */
    break_lua_test_set_alloc_budget(1u);
    ASSERT_EQ(break_lua_ecs_batch_create(8u), NULL);
    break_lua_test_set_alloc_budget(BREAK_LUA_TEST_ALLOC_DISABLED);
    {
        BreakLuaEcsBatch *b = break_lua_ecs_batch_create(8u);
        ASSERT_NOT_NULL(b);
        break_lua_ecs_batch_destroy(b);
    }
}

/* ---------------------------------------------------------------------- */
/* Binding registration.                                                   */

TEST(bind_ecs_batch_validation)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    BreakLuaRuntime *rt2 = break_lua_runtime_create(NULL);
    BreakLuaEcsBatch *batch = break_lua_ecs_batch_create(4u);
    BreakLuaEcsBatch *batch2 = break_lua_ecs_batch_create(4u);
    ASSERT_NOT_NULL(rt);
    ASSERT_NOT_NULL(rt2);
    ASSERT_NOT_NULL(batch);
    ASSERT_NOT_NULL(batch2);

    ASSERT_EQ(break_lua_runtime_bind_ecs_batch(NULL, batch),
              BREAK_LUA_INVALID);
    ASSERT_EQ(break_lua_runtime_bind_ecs_batch(rt, NULL), BREAK_LUA_INVALID);

    ASSERT_EQ(break_lua_runtime_bind_ecs_batch(rt, batch), BREAK_LUA_OK);
    /* One batch per runtime: a second bind is rejected. */
    ASSERT_EQ(break_lua_runtime_bind_ecs_batch(rt, batch2),
              BREAK_LUA_REJECTED);
    /* One runtime per batch: a bound batch cannot rebind elsewhere. */
    ASSERT_EQ(break_lua_runtime_bind_ecs_batch(rt2, batch),
              BREAK_LUA_REJECTED);
    /* An unbound batch binds fine on another runtime. */
    ASSERT_EQ(break_lua_runtime_bind_ecs_batch(rt2, batch2), BREAK_LUA_OK);

    assert_stack_balanced(rt);
    assert_stack_balanced(rt2);
    break_lua_runtime_destroy(rt);
    break_lua_runtime_destroy(rt2);
    break_lua_ecs_batch_destroy(batch);
    break_lua_ecs_batch_destroy(batch2);
}

static BreakLuaRuntime *g_probe_rt;
static BreakLuaEcsBatch *g_probe_batch;
static BreakLuaError g_probe_bind_result;
static BreakLuaError g_probe_config_result;
static usize g_probe_drain_result;

static PLATFORM_THREAD_RET binding_probe_worker(PLATFORM_THREAD_ARG arg)
{
    BreakLuaEcsRecord recs[4];
    BreakLuaConfigBinding entry = { "k", 0.0, 1.0, 0.5 };
    (void)arg;
    g_probe_bind_result =
        break_lua_runtime_bind_ecs_batch(g_probe_rt, g_probe_batch);
    g_probe_config_result =
        break_lua_runtime_bind_config(g_probe_rt, &entry, 1u);
    g_probe_drain_result =
        break_lua_ecs_batch_drain(g_probe_batch, recs, 4u);
    return PLATFORM_THREAD_RETURN;
}

TEST(binding_apis_reject_non_owner_thread)
{
    PlatformThread t;
    g_probe_rt = break_lua_runtime_create(NULL);
    g_probe_batch = break_lua_ecs_batch_create(4u);
    ASSERT_NOT_NULL(g_probe_rt);
    ASSERT_NOT_NULL(g_probe_batch);

    g_probe_bind_result = BREAK_LUA_OK;
    g_probe_config_result = BREAK_LUA_OK;
    g_probe_drain_result = 99u;
    ASSERT_TRUE(platform_thread_create(&t, binding_probe_worker, NULL));
    platform_thread_join(t);
    ASSERT_EQ(g_probe_bind_result, BREAK_LUA_REJECTED);
    ASSERT_EQ(g_probe_config_result, BREAK_LUA_REJECTED);
    /* Cross-thread drain is a bounded no-op (0 records, batch untouched). */
    ASSERT_EQ(g_probe_drain_result, 0u);

    /* The owner thread still binds normally afterwards. */
    ASSERT_EQ(break_lua_runtime_bind_ecs_batch(g_probe_rt, g_probe_batch),
              BREAK_LUA_OK);

    break_lua_runtime_destroy(g_probe_rt);
    break_lua_ecs_batch_destroy(g_probe_batch);
    g_probe_rt = NULL;
    g_probe_batch = NULL;
}

/* ---------------------------------------------------------------------- */
/* Script-driven enqueue and host drain.                                   */

TEST(script_enqueue_and_host_drain_fifo)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    BreakLuaEcsBatch *batch = break_lua_ecs_batch_create(8u);
    BreakLuaEcsRecord recs[8];
    ASSERT_NOT_NULL(rt);
    ASSERT_NOT_NULL(batch);
    ASSERT_EQ(break_lua_runtime_bind_ecs_batch(rt, batch), BREAK_LUA_OK);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "ecs_mod", kChunkEnqueue,
                                            chunk_len(kChunkEnqueue)),
              BREAK_LUA_OK);
    ASSERT_EQ(break_lua_runtime_call(rt, "ecs_mod", "enqueue_batch", NULL, 0u,
                                     NULL, 0u),
              BREAK_LUA_OK);
    assert_stack_balanced(rt);

    assert_state_number(rt, "ecs_mod", "ok1", 1.0);
    assert_state_number(rt, "ecs_mod", "ok2", 1.0);
    assert_state_number(rt, "ecs_mod", "ok3", 1.0);

    /* Host drain sees exactly the enqueued commands in FIFO order. */
    memset(recs, 0xFF, sizeof(recs));
    ASSERT_EQ(break_lua_ecs_batch_drain(batch, recs, 8u), 3u);
    ASSERT_EQ(recs[0].kind, BREAK_LUA_ECS_RECORD_SPAWN);
    ASSERT_EQ(recs[1].kind, BREAK_LUA_ECS_RECORD_SET);
    ASSERT_EQ(recs[2].kind, BREAK_LUA_ECS_RECORD_SPAWN);
    ASSERT_STR_EQ(recs[1].component, "pos");
    ASSERT_STR_EQ(recs[1].field, "x");
    ASSERT_EQ(recs[1].value_type, BREAK_LUA_ECS_VALUE_NUMBER);
    ASSERT_FLOAT_EQ(recs[1].value.n, 42.5, 1e-12);
    /* SPAWN records carry no payload. */
    ASSERT_EQ(recs[0].value_type, BREAK_LUA_ECS_VALUE_NONE);
    ASSERT_EQ(recs[0].component[0], '\0');
    ASSERT_EQ(recs[0].field[0], '\0');
    /* The batch is now empty; the facade never applied anything itself —
     * records are inert data the host chose to drain (no World exists in
     * break_lua). */
    ASSERT_EQ(break_lua_ecs_batch_drain(batch, recs, 8u), 0u);

    break_lua_runtime_destroy(rt);
    break_lua_ecs_batch_destroy(batch);
}

TEST(batch_full_surfaces_bounded_failure_to_script)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    BreakLuaEcsBatch *batch = break_lua_ecs_batch_create(2u);
    BreakLuaEcsRecord recs[4];
    ASSERT_NOT_NULL(rt);
    ASSERT_NOT_NULL(batch);
    ASSERT_EQ(break_lua_runtime_bind_ecs_batch(rt, batch), BREAK_LUA_OK);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "ovl", kChunkOverload,
                                            chunk_len(kChunkOverload)),
              BREAK_LUA_OK);
    ASSERT_EQ(break_lua_runtime_call(rt, "ovl", "fill", NULL, 0u, NULL, 0u),
              BREAK_LUA_OK);
    assert_stack_balanced(rt);

    /* First two enqueues succeed; the full batch answers (false, message). */
    assert_state_number(rt, "ovl", "ok1", 1.0);
    assert_state_number(rt, "ovl", "ok2", 1.0);
    assert_state_number(rt, "ovl", "ok3", 0.0);
    assert_state_number(rt, "ovl", "ok4", 0.0);
    {
        double err_len = 0.0;
        ASSERT_TRUE(break_lua_test_module_state_number(rt, "ovl", "err_len",
                                                       &err_len));
        ASSERT_TRUE(err_len > 0.0);
    }

    /* Drain frees capacity; the next enqueue succeeds (never blocks). */
    ASSERT_EQ(break_lua_ecs_batch_drain(batch, recs, 4u), 2u);
    ASSERT_EQ(recs[0].kind, BREAK_LUA_ECS_RECORD_SPAWN);
    ASSERT_EQ(recs[1].kind, BREAK_LUA_ECS_RECORD_SPAWN);
    ASSERT_EQ(break_lua_runtime_call(rt, "ovl", "one_more", NULL, 0u, NULL, 0u),
              BREAK_LUA_OK);
    assert_state_number(rt, "ovl", "ok5", 1.0);
    ASSERT_EQ(break_lua_ecs_batch_drain(batch, recs, 4u), 1u);

    break_lua_runtime_destroy(rt);
    break_lua_ecs_batch_destroy(batch);
}

TEST(ecs_set_record_format_all_value_kinds)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    BreakLuaEcsBatch *batch = break_lua_ecs_batch_create(8u);
    BreakLuaEcsRecord recs[3];
    ASSERT_NOT_NULL(rt);
    ASSERT_NOT_NULL(batch);
    ASSERT_EQ(break_lua_runtime_bind_ecs_batch(rt, batch), BREAK_LUA_OK);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "sets", kChunkSetKinds,
                                            chunk_len(kChunkSetKinds)),
              BREAK_LUA_OK);
    ASSERT_EQ(break_lua_runtime_call(rt, "sets", "do_sets", NULL, 0u, NULL, 0u),
              BREAK_LUA_OK);
    assert_stack_balanced(rt);

    ASSERT_EQ(break_lua_ecs_batch_drain(batch, recs, 3u), 3u);

    ASSERT_EQ(recs[0].kind, BREAK_LUA_ECS_RECORD_SET);
    ASSERT_STR_EQ(recs[0].component, "pos");
    ASSERT_STR_EQ(recs[0].field, "x");
    ASSERT_EQ(recs[0].component[3], '\0'); /* bounded copy is NUL-terminated */
    ASSERT_EQ(recs[0].value_type, BREAK_LUA_ECS_VALUE_NUMBER);
    ASSERT_FLOAT_EQ(recs[0].value.n, 42.5, 1e-12);

    ASSERT_EQ(recs[1].kind, BREAK_LUA_ECS_RECORD_SET);
    ASSERT_STR_EQ(recs[1].component, "gfx");
    ASSERT_STR_EQ(recs[1].field, "visible");
    ASSERT_EQ(recs[1].value_type, BREAK_LUA_ECS_VALUE_BOOL);
    ASSERT_TRUE(recs[1].value.b);

    ASSERT_EQ(recs[2].kind, BREAK_LUA_ECS_RECORD_SET);
    ASSERT_STR_EQ(recs[2].component, "name");
    ASSERT_STR_EQ(recs[2].field, "label");
    ASSERT_EQ(recs[2].value_type, BREAK_LUA_ECS_VALUE_STRING);
    ASSERT_EQ(recs[2].value.s.len, 4u);
    ASSERT_STR_EQ(recs[2].value.s.data, "hero");
    ASSERT_EQ(recs[2].value.s.data[4], '\0');

    break_lua_runtime_destroy(rt);
    break_lua_ecs_batch_destroy(batch);
}

TEST(ecs_set_argument_validation_is_bounded_failure)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    BreakLuaEcsBatch *batch = break_lua_ecs_batch_create(8u);
    BreakLuaEcsRecord recs[8];
    ASSERT_NOT_NULL(rt);
    ASSERT_NOT_NULL(batch);
    ASSERT_EQ(break_lua_runtime_bind_ecs_batch(rt, batch), BREAK_LUA_OK);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "bad", kChunkSetInvalid,
                                            chunk_len(kChunkSetInvalid)),
              BREAK_LUA_OK);
    /* Malformed calls fail bounded (false + message); the module function
     * itself completes OK. */
    ASSERT_EQ(break_lua_runtime_call(rt, "bad", "bad_sets", NULL, 0u, NULL, 0u),
              BREAK_LUA_OK);
    assert_stack_balanced(rt);

    assert_state_number(rt, "bad", "a", 0.0); /* component not a string */
    assert_state_number(rt, "bad", "b", 0.0); /* empty component */
    assert_state_number(rt, "bad", "c", 0.0); /* component over 63 bytes */
    assert_state_number(rt, "bad", "d", 0.0); /* unsupported value type */
    assert_state_number(rt, "bad", "e", 0.0); /* string value over 63 bytes */
    assert_state_number(rt, "bad", "f", 0.0); /* field over 63 bytes */

    /* Nothing was enqueued. */
    ASSERT_EQ(break_lua_ecs_batch_drain(batch, recs, 8u), 0u);

    break_lua_runtime_destroy(rt);
    break_lua_ecs_batch_destroy(batch);
}

TEST(spawn_without_bound_batch_fails_bounded)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    ASSERT_NOT_NULL(rt);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "nobatch", kChunkNoBatch,
                                            chunk_len(kChunkNoBatch)),
              BREAK_LUA_OK);
    ASSERT_EQ(break_lua_runtime_call(rt, "nobatch", "try_spawn", NULL, 0u,
                                     NULL, 0u),
              BREAK_LUA_OK);
    assert_stack_balanced(rt);
    assert_state_number(rt, "nobatch", "ok", 0.0);
    {
        double err_len = 0.0;
        ASSERT_TRUE(break_lua_test_module_state_number(rt, "nobatch",
                                                       "err_len", &err_len));
        ASSERT_TRUE(err_len > 0.0);
    }
    break_lua_runtime_destroy(rt);
}

TEST(batch_destroy_before_runtime_releases_borrow)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    BreakLuaEcsBatch *batch = break_lua_ecs_batch_create(4u);
    ASSERT_NOT_NULL(rt);
    ASSERT_NOT_NULL(batch);
    ASSERT_EQ(break_lua_runtime_bind_ecs_batch(rt, batch), BREAK_LUA_OK);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "nobatch", kChunkNoBatch,
                                            chunk_len(kChunkNoBatch)),
              BREAK_LUA_OK);
    /* Destroying a still-bound batch releases the borrow: the surviving
     * runtime answers scripts with the bounded "no batch bound" failure and
     * never touches the freed batch. */
    break_lua_ecs_batch_destroy(batch);
    ASSERT_EQ(break_lua_runtime_call(rt, "nobatch", "try_spawn", NULL, 0u,
                                     NULL, 0u),
              BREAK_LUA_OK);
    assert_state_number(rt, "nobatch", "ok", 0.0);
    assert_stack_balanced(rt);
    break_lua_runtime_destroy(rt);
}

TEST(frame_hook_enqueue_drains_fifo)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    BreakLuaEcsBatch *batch = break_lua_ecs_batch_create(8u);
    BreakLuaEcsRecord recs[4];
    ASSERT_NOT_NULL(rt);
    ASSERT_NOT_NULL(batch);
    ASSERT_EQ(break_lua_runtime_bind_ecs_batch(rt, batch), BREAK_LUA_OK);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "fr", kChunkFrameEnqueue,
                                            chunk_len(kChunkFrameEnqueue)),
              BREAK_LUA_OK);
    break_lua_runtime_begin_frame(rt, 0.016);
    assert_stack_balanced(rt);

    ASSERT_EQ(break_lua_ecs_batch_drain(batch, recs, 4u), 2u);
    ASSERT_EQ(recs[0].kind, BREAK_LUA_ECS_RECORD_SET);
    ASSERT_STR_EQ(recs[0].component, "motion");
    ASSERT_STR_EQ(recs[0].field, "dt");
    ASSERT_EQ(recs[0].value_type, BREAK_LUA_ECS_VALUE_NUMBER);
    ASSERT_FLOAT_EQ(recs[0].value.n, 0.016, 1e-12);
    ASSERT_EQ(recs[1].kind, BREAK_LUA_ECS_RECORD_SPAWN);

    break_lua_runtime_destroy(rt);
    break_lua_ecs_batch_destroy(batch);
}

/* ---------------------------------------------------------------------- */
/* Sandbox.                                                                */

TEST(sandbox_dangerous_globals_absent_whitelist_present)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    BreakLuaValue rets[27];
    usize i;
    ASSERT_NOT_NULL(rt);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "sand", kChunkSandbox,
                                            chunk_len(kChunkSandbox)),
              BREAK_LUA_OK);
    /* The load-time environment is already sandboxed. */
    assert_state_number(rt, "sand", "co_absent_at_load", 1.0);

    memset(rets, 0, sizeof(rets));
    ASSERT_EQ(break_lua_runtime_call(rt, "sand", "absent", NULL, 0u, rets, 26u),
              BREAK_LUA_OK);
    for (i = 0u; i < 26u; i++) {
        ASSERT_EQ(rets[i].type, BREAK_LUA_VALUE_BOOL);
        ASSERT_TRUE(rets[i].as.b);
    }

    memset(rets, 0, sizeof(rets));
    ASSERT_EQ(break_lua_runtime_call(rt, "sand", "present", NULL, 0u, rets,
                                     27u),
              BREAK_LUA_OK);
    for (i = 0u; i < 27u; i++) {
        ASSERT_EQ(rets[i].type, BREAK_LUA_VALUE_BOOL);
        ASSERT_TRUE(rets[i].as.b);
    }
    assert_stack_balanced(rt);
    break_lua_runtime_destroy(rt);
}

TEST(sandbox_os_execute_and_io_open_calls_fail)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    BreakLuaValue rets[2];
    ASSERT_NOT_NULL(rt);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "danger", kChunkDangerCalls,
                                            chunk_len(kChunkDangerCalls)),
              BREAK_LUA_OK);
    ASSERT_EQ(break_lua_runtime_call(rt, "danger", "try_danger", NULL, 0u,
                                     rets, 2u),
              BREAK_LUA_OK);
    /* Both pcalls returned false: the functions are absent, not blocked. */
    ASSERT_EQ(rets[0].type, BREAK_LUA_VALUE_BOOL);
    ASSERT_TRUE(rets[0].as.b);
    ASSERT_EQ(rets[1].type, BREAK_LUA_VALUE_BOOL);
    ASSERT_TRUE(rets[1].as.b);
    assert_stack_balanced(rt);
    break_lua_runtime_destroy(rt);
}

TEST(break_table_and_stdlib_proxies_are_read_only)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    BreakLuaEcsBatch *batch = break_lua_ecs_batch_create(4u);
    BreakLuaEcsRecord recs[4];
    ASSERT_NOT_NULL(rt);
    ASSERT_NOT_NULL(batch);
    ASSERT_EQ(break_lua_runtime_bind_ecs_batch(rt, batch), BREAK_LUA_OK);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "ro", kChunkReadonly,
                                            chunk_len(kChunkReadonly)),
              BREAK_LUA_OK);
    ASSERT_EQ(break_lua_runtime_call(rt, "ro", "try_mutate", NULL, 0u, NULL,
                                     0u),
              BREAK_LUA_OK);
    /* Every mutation attempt raised and was trapped by the script's pcall. */
    assert_state_number(rt, "ro", "m1", 0.0);
    assert_state_number(rt, "ro", "m2", 0.0);
    assert_state_number(rt, "ro", "m3", 0.0);
    assert_state_number(rt, "ro", "m4", 0.0);
    assert_state_number(rt, "ro", "m5", 0.0);
    assert_state_number(rt, "ro", "m6", 0.0);

    /* The mutations did not take: stdlib and the binding still work. */
    ASSERT_EQ(break_lua_runtime_call(rt, "ro", "still_works", NULL, 0u, NULL,
                                     0u),
              BREAK_LUA_OK);
    assert_state_number(rt, "ro", "rep_ok", 1.0);
    assert_state_number(rt, "ro", "spawn_ok", 1.0);
    ASSERT_EQ(break_lua_ecs_batch_drain(batch, recs, 4u), 1u);
    ASSERT_EQ(recs[0].kind, BREAK_LUA_ECS_RECORD_SPAWN);

    assert_stack_balanced(rt);
    break_lua_runtime_destroy(rt);
    break_lua_ecs_batch_destroy(batch);
}

TEST(batch_pointer_never_reachable_from_lua)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    BreakLuaEcsBatch *batch = break_lua_ecs_batch_create(4u);
    ASSERT_NOT_NULL(rt);
    ASSERT_NOT_NULL(batch);
    ASSERT_EQ(break_lua_runtime_bind_ecs_batch(rt, batch), BREAK_LUA_OK);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "scan", kChunkNoPtr,
                                            chunk_len(kChunkNoPtr)),
              BREAK_LUA_OK);
    ASSERT_EQ(break_lua_runtime_call(rt, "scan", "scan_break", NULL, 0u, NULL,
                                     0u),
              BREAK_LUA_OK);
    assert_stack_balanced(rt);
    /* Enumeration over the break chain yields zero entries (read-through
     * proxies carry no raw fields) and finds no userdata anywhere. */
    assert_state_number(rt, "scan", "enumerated", 0.0);
    assert_state_number(rt, "scan", "userdata_found", 0.0);
    break_lua_runtime_destroy(rt);
    break_lua_ecs_batch_destroy(batch);
}

TEST(coroutine_absent_in_budgeted_hook_plan_checkbox)
{
    BreakLuaRuntimeConfig cfg;
    BreakLuaRuntime *rt;
    memset(&cfg, 0, sizeof(cfg));
    cfg.instruction_budget = 100000u;
    rt = break_lua_runtime_create(&cfg);
    ASSERT_NOT_NULL(rt);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "co", kChunkCoHook,
                                            chunk_len(kChunkCoHook)),
              BREAK_LUA_OK);
    break_lua_runtime_begin_frame(rt, 0.016);
    assert_stack_balanced(rt);
    {
        BreakLuaTestFrameError rec = break_lua_test_last_frame_error(rt);
        /* The hook failed because `coroutine` is ABSENT (indexing nil) —
         * a bounded ordinary hook error, explicitly NOT a budget trip and
         * NOT a module-disabling event. */
        ASSERT_TRUE(rec.valid);
        ASSERT_FALSE(rec.budget);
        ASSERT_FALSE(rec.dispatch_failure);
        ASSERT_STR_EQ(rec.module, "co");
        ASSERT_STR_EQ(rec.hook, "on_frame_begin");
        ASSERT_TRUE(strstr(rec.message, "coroutine") != NULL);
        ASSERT_FALSE(break_lua_test_module_hooks_disabled(rt, "co"));
    }
    break_lua_runtime_destroy(rt);
}

TEST(coroutine_guarded_hook_runs_clean_under_budget)
{
    BreakLuaRuntimeConfig cfg;
    BreakLuaRuntime *rt;
    memset(&cfg, 0, sizeof(cfg));
    cfg.instruction_budget = 100000u;
    rt = break_lua_runtime_create(&cfg);
    ASSERT_NOT_NULL(rt);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "guard", kChunkCoGuard,
                                            chunk_len(kChunkCoGuard)),
              BREAK_LUA_OK);
    break_lua_runtime_begin_frame(rt, 0.016);
    break_lua_runtime_end_frame(rt);
    assert_stack_balanced(rt);
    assert_state_number(rt, "guard", "co_guard", 1.0);
    /* No fault was recorded: the absence is observable, not fatal. */
    ASSERT_EQ(break_lua_test_last_frame_error(rt).valid, 0);
    break_lua_runtime_destroy(rt);
}

TEST(stdlib_proxies_keep_modules_isolated)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    BreakLuaValue rets[2];
    ASSERT_NOT_NULL(rt);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "modA", kChunkPoisonA,
                                            chunk_len(kChunkPoisonA)),
              BREAK_LUA_OK);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "modB", kChunkCheckB,
                                            chunk_len(kChunkCheckB)),
              BREAK_LUA_OK);
    ASSERT_EQ(break_lua_runtime_call(rt, "modA", "poison", NULL, 0u, NULL, 0u),
              BREAK_LUA_OK);
    /* Module B still sees intact stdlib tables. */
    ASSERT_EQ(break_lua_runtime_call(rt, "modB", "check", NULL, 0u, rets, 2u),
              BREAK_LUA_OK);
    ASSERT_EQ(rets[0].type, BREAK_LUA_VALUE_STRING);
    ASSERT_STR_EQ(rets[0].as.s.data, "qqq");
    ASSERT_EQ(rets[1].type, BREAK_LUA_VALUE_BOOL);
    ASSERT_TRUE(rets[1].as.b);
    assert_stack_balanced(rt);
    break_lua_runtime_destroy(rt);
}

/* ---------------------------------------------------------------------- */
/* Config binding.                                                         */

TEST(bind_config_validation)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    BreakLuaConfigBinding ok_entries[2] = {
        { "fps", 0.0, 240.0, 60.0 },
        { "volume", 0.0, 1.0, 0.5 },
    };
    BreakLuaConfigBinding bad_key_null[1] = { { NULL, 0.0, 1.0, 0.5 } };
    BreakLuaConfigBinding bad_key_empty[1] = { { "", 0.0, 1.0, 0.5 } };
    BreakLuaConfigBinding bad_range[1] = { { "x", 2.0, 1.0, 1.5 } };
    BreakLuaConfigBinding bad_nan_min[1] = {
        { "x", NAN, 1.0, 0.5 }
    };
    BreakLuaConfigBinding bad_nan_initial[1] = {
        { "x", 0.0, 1.0, NAN }
    };
    BreakLuaConfigBinding dup[2] = {
        { "fps", 0.0, 1.0, 0.5 },
        { "fps", 0.0, 2.0, 0.25 },
    };
    BreakLuaConfigBinding dup_existing[1] = { { "fps", 0.0, 1.0, 0.5 } };
    static BreakLuaConfigBinding over_cap[BREAK_LUA_MAX_CONFIG_BINDINGS + 1u];
    char long_key[BREAK_LUA_MAX_CONFIG_KEY_BYTES + 4u];
    BreakLuaConfigBinding bad_key_long[1];
    usize i;
    ASSERT_NOT_NULL(rt);

    ASSERT_EQ(break_lua_runtime_bind_config(NULL, ok_entries, 2u),
              BREAK_LUA_INVALID);
    ASSERT_EQ(break_lua_runtime_bind_config(rt, NULL, 2u), BREAK_LUA_INVALID);
    /* Zero entries is a no-op, even with NULL entries. */
    ASSERT_EQ(break_lua_runtime_bind_config(rt, NULL, 0u), BREAK_LUA_OK);

    ASSERT_EQ(break_lua_runtime_bind_config(rt, bad_key_null, 1u),
              BREAK_LUA_INVALID);
    ASSERT_EQ(break_lua_runtime_bind_config(rt, bad_key_empty, 1u),
              BREAK_LUA_INVALID);
    memset(long_key, 'k', sizeof(long_key));
    long_key[sizeof(long_key) - 1u] = '\0';
    bad_key_long[0].key = long_key;
    bad_key_long[0].min_value = 0.0;
    bad_key_long[0].max_value = 1.0;
    bad_key_long[0].initial_value = 0.5;
    ASSERT_EQ(break_lua_runtime_bind_config(rt, bad_key_long, 1u),
              BREAK_LUA_INVALID);
    ASSERT_EQ(break_lua_runtime_bind_config(rt, bad_range, 1u),
              BREAK_LUA_INVALID);
    ASSERT_EQ(break_lua_runtime_bind_config(rt, bad_nan_min, 1u),
              BREAK_LUA_INVALID);
    ASSERT_EQ(break_lua_runtime_bind_config(rt, bad_nan_initial, 1u),
              BREAK_LUA_INVALID);
    /* Duplicate keys within one call are rejected. */
    ASSERT_EQ(break_lua_runtime_bind_config(rt, dup, 2u), BREAK_LUA_REJECTED);
    /* Over the hard binding count ceiling. */
    for (i = 0u; i < BREAK_LUA_MAX_CONFIG_BINDINGS + 1u; i++) {
        over_cap[i].key = "k";
        over_cap[i].min_value = 0.0;
        over_cap[i].max_value = 1.0;
        over_cap[i].initial_value = 0.5;
    }
    ASSERT_EQ(break_lua_runtime_bind_config(
                  rt, over_cap, BREAK_LUA_MAX_CONFIG_BINDINGS + 1u),
              BREAK_LUA_OVERLOAD);

    /* None of the failures above registered anything. */
    ASSERT_EQ(break_lua_runtime_bind_config(rt, ok_entries, 2u), BREAK_LUA_OK);
    /* A key already bound cannot bind again. */
    ASSERT_EQ(break_lua_runtime_bind_config(rt, dup_existing, 1u),
              BREAK_LUA_REJECTED);

    /* Accumulation over the store ceiling: 2 bound + 255 new > 256. */
    {
        static BreakLuaConfigBinding rest[BREAK_LUA_MAX_CONFIG_BINDINGS - 1u];
        static char keys[BREAK_LUA_MAX_CONFIG_BINDINGS - 1u][16];
        for (i = 0u; i < BREAK_LUA_MAX_CONFIG_BINDINGS - 1u; i++) {
            snprintf(keys[i], sizeof(keys[i]), "key%04u", (unsigned)i);
            rest[i].key = keys[i];
            rest[i].min_value = 0.0;
            rest[i].max_value = 1.0;
            rest[i].initial_value = 0.5;
        }
        ASSERT_EQ(break_lua_runtime_bind_config(
                      rt, rest, BREAK_LUA_MAX_CONFIG_BINDINGS - 1u),
                  BREAK_LUA_OVERLOAD);
    }

    assert_stack_balanced(rt);
    break_lua_runtime_destroy(rt);
}

TEST(config_get_returns_clamped_values)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    /* Initial values outside [min, max] clamp at bind time. */
    BreakLuaConfigBinding entries[3] = {
        { "fps", 0.0, 240.0, 999.0 },
        { "volume", 0.0, 1.0, 0.5 },
        { "bias", -10.0, 10.0, -20.0 },
    };
    ASSERT_NOT_NULL(rt);
    ASSERT_EQ(break_lua_runtime_bind_config(rt, entries, 3u), BREAK_LUA_OK);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "cfg", kChunkConfig,
                                            chunk_len(kChunkConfig)),
              BREAK_LUA_OK);
    ASSERT_EQ(break_lua_runtime_call(rt, "cfg", "read_config", NULL, 0u, NULL,
                                     0u),
              BREAK_LUA_OK);
    assert_stack_balanced(rt);

    assert_state_number(rt, "cfg", "fps", 240.0);    /* clamped to max */
    assert_state_number(rt, "cfg", "volume", 0.5);   /* in range: verbatim */
    assert_state_number(rt, "cfg", "bias", -10.0);   /* clamped to min */
    /* Unknown key and malformed key read back nil + a message. */
    assert_state_number(rt, "cfg", "unknown_nil", 1.0);
    {
        double err_len = 0.0;
        ASSERT_TRUE(break_lua_test_module_state_number(rt, "cfg",
                                                       "unknown_err_len",
                                                       &err_len));
        ASSERT_TRUE(err_len > 0.0);
    }
    assert_state_number(rt, "cfg", "noarg_nil", 1.0);
    assert_state_number(rt, "cfg", "badarg_nil", 1.0);

    break_lua_runtime_destroy(rt);
}

TEST(bind_config_allocation_failure_is_bounded)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    BreakLuaConfigBinding entry[1] = { { "fps", 0.0, 240.0, 60.0 } };
    ASSERT_NOT_NULL(rt);
    /* The config store allocation fails: bounded OOM, nothing registered. */
    break_lua_test_set_alloc_budget(0u);
    ASSERT_EQ(break_lua_runtime_bind_config(rt, entry, 1u), BREAK_LUA_OOM);
    break_lua_test_set_alloc_budget(BREAK_LUA_TEST_ALLOC_DISABLED);
    /* The runtime recovered: the same bind now succeeds. */
    ASSERT_EQ(break_lua_runtime_bind_config(rt, entry, 1u), BREAK_LUA_OK);
    break_lua_runtime_destroy(rt);
}

/* ------------------------------------------------------------------ */
/* NEW-C4 (fix round 4): the instruction-budget trip raises a           */
/* host-owned sentinel value; the sandboxed pcall/xpcall are            */
/* budget-TRANSPARENT wrappers that re-raise it uninspected, so a trip  */
/* propagates through any script pcall nesting to the host catcher.     */
/* ------------------------------------------------------------------ */

static const char kChunkPcallOrdinary[] =
    "local ok, err = pcall(function() error('ordinary') end)\n"
    "if not ok then state.caught = 1 end\n"
    "local ok2 = pcall(function() return 5 end)\n"
    "if ok2 then state.clean = 1 end\n";

static const char kChunkXpcallOrdinary[] =
    "local ok, err = xpcall(function() error('x') end,\n"
    "                       function(m) return 'handled' end)\n"
    "if not ok and err == 'handled' then state.handled = 1 end\n";

/* The hook's pcall wraps an infinite loop: the trip must NOT be returned
 * to the script (state.caught never set); it propagates to the per-hook
 * pcall — budget fault record + module marked, per the Stage 3 runaway
 * policy. */
static const char kChunkPcallTrip[] =
    "function on_frame_begin(dt)\n"
    "    local ok, err = pcall(function() while true do end end)\n"
    "    state.caught = 1\n"  /* never reached: the trip is uncatchable */
    "end\n";

/* The reviewer's third live payload shape at hook level: five sequential
 * pcall-wrapped loops must NOT survive — the FIRST trip terminates the
 * hook. */
static const char kChunkPcallTripLoop[] =
    "function on_frame_begin(dt)\n"
    "    for i=1,5 do pcall(function() while true do end end) end\n"
    "    state.survived = 1\n"  /* never reached */
    "end\n";

/* Depth-3 pcall nesting with the trip at the bottom. */
static const char kChunkNestedTrip[] =
    "function on_frame_begin(dt)\n"
    "    pcall(function()\n"
    "        return pcall(function()\n"
    "            return pcall(function() while true do end end)\n"
    "        end)\n"
    "    end)\n"
    "    state.survived = 1\n"  /* never reached */
    "end\n";

/* The xpcall handler must never receive the sentinel (it would make the
 * value script-observable). */
static const char kChunkXpcallTrip[] =
    "function on_frame_begin(dt)\n"
    "    local ok = xpcall(function() while true do end end,\n"
    "                      function(m) state.handler_saw = 1 return m end)\n"
    "    state.caught = 1\n"  /* never reached */
    "end\n";

static const char kChunkSpinHook[] =
    "function on_frame_begin(dt)\n"
    "    while true do end\n"
    "end\n";

static const char kChunkCleanHook[] =
    "function on_frame_begin(dt)\n"
    "    state.ran = (state.ran or 0) + 1\n"
    "end\n";

TEST(sandbox_pcall_still_catches_ordinary_errors)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    double v = 0.0;
    ASSERT_NOT_NULL(rt);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "m", kChunkPcallOrdinary,
                                            chunk_len(kChunkPcallOrdinary)),
              BREAK_LUA_OK);
    ASSERT_TRUE(break_lua_test_module_state_number(rt, "m", "caught", &v));
    ASSERT_EQ(v, 1.0);
    ASSERT_TRUE(break_lua_test_module_state_number(rt, "m", "clean", &v));
    ASSERT_EQ(v, 1.0);
    break_lua_runtime_destroy(rt);
}

TEST(sandbox_xpcall_handler_runs_for_ordinary_errors)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    double v = 0.0;
    ASSERT_NOT_NULL(rt);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "m", kChunkXpcallOrdinary,
                                            chunk_len(kChunkXpcallOrdinary)),
              BREAK_LUA_OK);
    /* The wrapper invokes the script handler itself (post-unwind — safe:
     * the debug library is absent from the sandbox) and returns its
     * result. */
    ASSERT_TRUE(break_lua_test_module_state_number(rt, "m", "handled", &v));
    ASSERT_EQ(v, 1.0);
    break_lua_runtime_destroy(rt);
}

TEST(budget_trip_is_uncatchable_by_script_pcall_in_hooks)
{
    BreakLuaRuntimeConfig cfg;
    BreakLuaRuntime *rt;
    BreakLuaTestFrameError rec;
    double v = 0.0;
    memset(&cfg, 0, sizeof(cfg));
    cfg.instruction_budget = 100000u;
    rt = break_lua_runtime_create(&cfg);
    ASSERT_NOT_NULL(rt);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "a", kChunkPcallTrip,
                                            chunk_len(kChunkPcallTrip)),
              BREAK_LUA_OK);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "b", kChunkPcallTripLoop,
                                            chunk_len(kChunkPcallTripLoop)),
              BREAK_LUA_OK);

    break_lua_runtime_begin_frame(rt, 0.016);
    assert_stack_balanced(rt);

    /* Both hooks tripped and were marked; neither script caught anything. */
    ASSERT_FALSE(break_lua_test_module_state_number(rt, "a", "caught", &v));
    ASSERT_FALSE(break_lua_test_module_state_number(rt, "b", "survived", &v));
    ASSERT_TRUE(break_lua_test_module_hooks_disabled(rt, "a"));
    ASSERT_TRUE(break_lua_test_module_hooks_disabled(rt, "b"));
    rec = break_lua_test_last_frame_error(rt);
    ASSERT_TRUE(rec.valid);
    ASSERT_TRUE(rec.budget);
    ASSERT_TRUE(strstr(rec.message, "instruction budget exceeded") != NULL);
    /* One trip per hook invocation; two armed invocations tripped. */
    ASSERT_EQ(break_lua_runtime_budget_trip_count(rt), 2u);

    break_lua_runtime_destroy(rt);
}

TEST(budget_trip_propagates_through_nested_pcall_depth3)
{
    BreakLuaRuntimeConfig cfg;
    BreakLuaRuntime *rt;
    double v = 0.0;
    memset(&cfg, 0, sizeof(cfg));
    cfg.instruction_budget = 100000u;
    rt = break_lua_runtime_create(&cfg);
    ASSERT_NOT_NULL(rt);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "n", kChunkNestedTrip,
                                            chunk_len(kChunkNestedTrip)),
              BREAK_LUA_OK);
    break_lua_runtime_begin_frame(rt, 0.016);
    assert_stack_balanced(rt);
    ASSERT_FALSE(break_lua_test_module_state_number(rt, "n", "survived", &v));
    ASSERT_TRUE(break_lua_test_module_hooks_disabled(rt, "n"));
    ASSERT_TRUE(break_lua_test_last_frame_error(rt).budget);
    break_lua_runtime_destroy(rt);
}

TEST(budget_trip_sentinel_never_observable_via_xpcall_handler)
{
    BreakLuaRuntimeConfig cfg;
    BreakLuaRuntime *rt;
    double v = 0.0;
    memset(&cfg, 0, sizeof(cfg));
    cfg.instruction_budget = 100000u;
    rt = break_lua_runtime_create(&cfg);
    ASSERT_NOT_NULL(rt);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "x", kChunkXpcallTrip,
                                            chunk_len(kChunkXpcallTrip)),
              BREAK_LUA_OK);
    break_lua_runtime_begin_frame(rt, 0.016);
    assert_stack_balanced(rt);
    /* The handler never ran (the sentinel is never script-observable), and
     * the trip propagated out anyway. */
    ASSERT_FALSE(break_lua_test_module_state_number(rt, "x", "handler_saw",
                                                    &v));
    ASSERT_FALSE(break_lua_test_module_state_number(rt, "x", "caught", &v));
    ASSERT_TRUE(break_lua_test_module_hooks_disabled(rt, "x"));
    break_lua_runtime_destroy(rt);
}

/* ------------------------------------------------------------------ */
/* Fix round 5 (review of 121733c8): xpcall base-semantics parity.     */
/* I1: an ORDINARY error raised by the xpcall handler is absorbed by   */
/* xpcall itself exactly like base Lua 5.4 (LUA_ERRERR): the call      */
/* returns (false, "error in error handling") and the code after the   */
/* xpcall KEEPS RUNNING (pre-fix the handler error escaped the call    */
/* point and killed the enclosing chunk/function). A handler that      */
/* trips the budget still re-raises the sentinel — a trip is never     */
/* absorbed (round-4 property kept). M3: with zero arguments the       */
/* argument error names #2 like base (the wrapper no longer            */
/* pre-checks #1). M2: error(msg, level>=2) is the sandbox's only      */
/* stack-relative operation; a level resolving to the frames BELOW the */
/* handler hits the wrapper's C frame (post-unwind) instead of the     */
/* not-yet-unwound callee frame (base) — a position-prefix-only        */
/* difference, pinned below as documented expected behavior.           */
/* ------------------------------------------------------------------ */

static const char kChunkXpcallHandlerError[] =
    "function raised_handler()\n"
    "    local a, b = xpcall(function() error('inner') end,\n"
    "                        function(m) error('probe', 0) end)\n"
    "    state.continued = 1\n" /* reached: base absorbs the handler error */
    "    return a, b\n"
    "end\n"
    "function raised_handler_nested()\n"
    "    local ok, tag, a, b = pcall(function()\n"
    "        local x, y = xpcall(function() error('inner') end,\n"
    "                            function(m) error('probe', 0) end)\n"
    "        return 'continued', x, y\n"
    "    end)\n"
    "    return ok, tag, a, b\n"
    "end\n";

/* The HANDLER-side trip variant of the round-4 uncatchability pins: a
 * handler that burns the budget trips the armed count hook inside the
 * wrapper's (nested, protected) handler call; the sentinel is re-raised
 * through the script's outer pcall to the host catcher. */
static const char kChunkXpcallHandlerTrip[] =
    "function on_frame_begin(dt)\n"
    "    local ok = pcall(function()\n"
    "        return xpcall(function() error('inner') end,\n"
    "                      function(m) while true do end end)\n"
    "    end)\n"
    "    state.caught = 1\n" /* never reached: the handler trip is uncatchable */
    "end\n";

/* M3 shapes. The module name ("arg") is the chunk name, so the position
 * prefix is deterministic; the pcall'd anonymous function sits on line 2. */
static const char kChunkXpcallArgShapes[] =
    "function zero_arg()\n"
    "    local ok, e = pcall(function() return xpcall() end)\n"
    "    return ok, e\n"
    "end\n"
    "function nil_first()\n"
    "    local ok, xf, xm = pcall(function()\n"
    "        return xpcall(nil, function(m) return m end)\n"
    "    end)\n"
    "    return ok, xf, xm\n"
    "end\n";

/* M2 pins. raise_lvl2: a handler raising error(msg, 2) is absorbed to the
 * LUA_ERRERR result exactly like base (the level-2 prefix is discarded in
 * both). observe_lvl4/observe_lvl5 pin the documented post-unwind residue:
 * error levels are the sandbox's only stack-relative operation. Levels
 * resolving at or above the handler frame (and its immediate caller — a C
 * frame on BOTH sides: base sees the triggering error() C frame, the
 * wrapper sees its own) resolve identically modulo the host-chosen chunk
 * name; the first frame that DIFFERS is one level deeper, where base
 * walks the not-yet-unwound error chain (the callee's error line) and the
 * wrapper walks the xpcall call site. Position-prefix content only;
 * message text, values, and catchability are bit-identical. */
static const char kChunkXpcallHandlerLevel[] =
    "function raise_lvl2()\n"
    "    local a, b = xpcall(function() error('inner') end,\n"
    "                        function(m) error('probe', 2) end)\n"
    "    state.continued_lvl2 = 1\n"
    "    return a, b\n"
    "end\n"
    "\n"
    "function observe_lvl4()\n"
    "    local f = function() error('inner') end\n"
    "    local ok, e = xpcall(f,\n"
    "        function(m)\n"
    "            local _, obs = pcall(function() error('obs', 4) end)\n"
    "            return obs\n"
    "        end)\n"
    "    return e\n"
    "end\n"
    "\n"
    "function observe_lvl5()\n"
    "    local f = function() error('inner') end\n"
    "    local ok, e = xpcall(f,\n"
    "        function(m)\n"
    "            local _, obs = pcall(function() error('obs', 5) end)\n"
    "            return obs\n"
    "        end)\n"
    "    return e\n"
    "end\n";

TEST(sandbox_xpcall_absorbs_ordinary_handler_error_like_base)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    BreakLuaValue rets[4];
    double v = 0.0;
    ASSERT_NOT_NULL(rt);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "m", kChunkXpcallHandlerError,
                                            chunk_len(kChunkXpcallHandlerError)),
              BREAK_LUA_OK);

    /* Base shape 1: xpcall itself returns (false, "error in error
     * handling") and the statement after it runs. */
    memset(rets, 0xFF, sizeof(rets));
    ASSERT_EQ(break_lua_runtime_call(rt, "m", "raised_handler", NULL, 0u,
                                     rets, 4u),
              BREAK_LUA_OK);
    ASSERT_EQ(rets[0].type, BREAK_LUA_VALUE_BOOL);
    ASSERT_FALSE(rets[0].as.b);
    ASSERT_EQ(rets[1].type, BREAK_LUA_VALUE_STRING);
    ASSERT_STR_EQ(rets[1].as.s.data, "error in error handling");
    ASSERT_TRUE(break_lua_test_module_state_number(rt, "m", "continued", &v));
    ASSERT_EQ(v, 1.0);

    /* Base shape 2: an outer pcall sees the xpcall RETURN normally. */
    memset(rets, 0xFF, sizeof(rets));
    ASSERT_EQ(break_lua_runtime_call(rt, "m", "raised_handler_nested", NULL,
                                     0u, rets, 4u),
              BREAK_LUA_OK);
    ASSERT_EQ(rets[0].type, BREAK_LUA_VALUE_BOOL);
    ASSERT_TRUE(rets[0].as.b);
    ASSERT_EQ(rets[1].type, BREAK_LUA_VALUE_STRING);
    ASSERT_STR_EQ(rets[1].as.s.data, "continued");
    ASSERT_EQ(rets[2].type, BREAK_LUA_VALUE_BOOL);
    ASSERT_FALSE(rets[2].as.b);
    ASSERT_EQ(rets[3].type, BREAK_LUA_VALUE_STRING);
    ASSERT_STR_EQ(rets[3].as.s.data, "error in error handling");

    assert_stack_balanced(rt);
    break_lua_runtime_destroy(rt);
}

TEST(budget_trip_inside_xpcall_handler_is_uncatchable)
{
    BreakLuaRuntimeConfig cfg;
    BreakLuaRuntime *rt;
    BreakLuaTestFrameError rec;
    double v = 0.0;
    memset(&cfg, 0, sizeof(cfg));
    cfg.instruction_budget = 100000u;
    rt = break_lua_runtime_create(&cfg);
    ASSERT_NOT_NULL(rt);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "h", kChunkXpcallHandlerTrip,
                                            chunk_len(kChunkXpcallHandlerTrip)),
              BREAK_LUA_OK);

    break_lua_runtime_begin_frame(rt, 0.016);
    assert_stack_balanced(rt);

    /* Neither the wrapper's nested handler pcall nor the script's outer
     * pcall absorbed the trip: the hook died, the module is marked, and
     * exactly one trip was recorded. */
    ASSERT_FALSE(break_lua_test_module_state_number(rt, "h", "caught", &v));
    ASSERT_TRUE(break_lua_test_module_hooks_disabled(rt, "h"));
    rec = break_lua_test_last_frame_error(rt);
    ASSERT_TRUE(rec.valid);
    ASSERT_TRUE(rec.budget);
    ASSERT_TRUE(strstr(rec.message, "instruction budget exceeded") != NULL);
    ASSERT_EQ(break_lua_runtime_budget_trip_count(rt), 1u);

    break_lua_runtime_destroy(rt);
}

TEST(sandbox_xpcall_argument_errors_match_base_text)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    BreakLuaValue rets[3];
    ASSERT_NOT_NULL(rt);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "arg", kChunkXpcallArgShapes,
                                            chunk_len(kChunkXpcallArgShapes)),
              BREAK_LUA_OK);

    /* Zero arguments: base checks ONLY the handler argument, so the error
     * names #2 (never #1) with the caller's position prefix. */
    memset(rets, 0xFF, sizeof(rets));
    ASSERT_EQ(break_lua_runtime_call(rt, "arg", "zero_arg", NULL, 0u,
                                     rets, 3u),
              BREAK_LUA_OK);
    ASSERT_EQ(rets[0].type, BREAK_LUA_VALUE_BOOL);
    ASSERT_FALSE(rets[0].as.b);
    ASSERT_EQ(rets[1].type, BREAK_LUA_VALUE_STRING);
    ASSERT_STR_EQ(rets[1].as.s.data,
                  "arg:2: bad argument #2 to 'xpcall' (function expected, "
                  "got no value)");

    /* nil first argument: base reaches the call attempt, which fails and
     * routes through the handler (returned here) — wrapper identical. */
    memset(rets, 0xFF, sizeof(rets));
    ASSERT_EQ(break_lua_runtime_call(rt, "arg", "nil_first", NULL, 0u,
                                     rets, 3u),
              BREAK_LUA_OK);
    ASSERT_EQ(rets[0].type, BREAK_LUA_VALUE_BOOL);
    ASSERT_TRUE(rets[0].as.b);
    ASSERT_EQ(rets[1].type, BREAK_LUA_VALUE_BOOL);
    ASSERT_FALSE(rets[1].as.b);
    ASSERT_EQ(rets[2].type, BREAK_LUA_VALUE_STRING);
    ASSERT_STR_EQ(rets[2].as.s.data, "attempt to call a nil value");

    assert_stack_balanced(rt);
    break_lua_runtime_destroy(rt);
}

TEST(sandbox_xpcall_handler_error_levels_match_documented_behavior)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    BreakLuaValue rets[2];
    double v = 0.0;
    ASSERT_NOT_NULL(rt);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "lvl", kChunkXpcallHandlerLevel,
                                            chunk_len(kChunkXpcallHandlerLevel)),
              BREAK_LUA_OK);

    /* error(msg, 2) raised BY the handler: absorbed like base (LUA_ERRERR);
     * the differing level-2 prefix never surfaces because the handler
     * message is replaced by "error in error handling" in both. */
    memset(rets, 0xFF, sizeof(rets));
    ASSERT_EQ(break_lua_runtime_call(rt, "lvl", "raise_lvl2", NULL, 0u,
                                     rets, 2u),
              BREAK_LUA_OK);
    ASSERT_EQ(rets[0].type, BREAK_LUA_VALUE_BOOL);
    ASSERT_FALSE(rets[0].as.b);
    ASSERT_EQ(rets[1].type, BREAK_LUA_VALUE_STRING);
    ASSERT_STR_EQ(rets[1].as.s.data, "error in error handling");
    ASSERT_TRUE(break_lua_test_module_state_number(rt, "lvl",
                                                   "continued_lvl2", &v));
    ASSERT_EQ(v, 1.0);

    /* Level 4 (the frame below the handler): a C frame on BOTH sides —
     * base sees the triggering error() C frame, the wrapper sees its own —
     * so both resolve bare. Parity, pinned. */
    memset(rets, 0xFF, sizeof(rets));
    ASSERT_EQ(break_lua_runtime_call(rt, "lvl", "observe_lvl4", NULL, 0u,
                                     rets, 2u),
              BREAK_LUA_OK);
    ASSERT_EQ(rets[0].type, BREAK_LUA_VALUE_STRING);
    ASSERT_STR_EQ(rets[0].as.s.data, "obs");

    /* Level 5 — the first frame that DIFFERS (documented M2 residue): base
     * walks the not-yet-unwound error chain and names the callee's error
     * line ("lvl:19: obs"); the post-unwind wrapper names the xpcall call
     * site instead ("lvl:20: obs"). Position-prefix content only. */
    memset(rets, 0xFF, sizeof(rets));
    ASSERT_EQ(break_lua_runtime_call(rt, "lvl", "observe_lvl5", NULL, 0u,
                                     rets, 2u),
              BREAK_LUA_OK);
    ASSERT_EQ(rets[0].type, BREAK_LUA_VALUE_STRING);
    ASSERT_STR_EQ(rets[0].as.s.data, "lvl:20: obs");

    assert_stack_balanced(rt);
    break_lua_runtime_destroy(rt);
}

TEST(budget_trip_count_tracks_and_reload_recovers)
{
    BreakLuaRuntimeConfig cfg;
    BreakLuaRuntime *rt;
    double v = 0.0;
    memset(&cfg, 0, sizeof(cfg));
    cfg.instruction_budget = 100000u;
    rt = break_lua_runtime_create(&cfg);
    ASSERT_NOT_NULL(rt);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "s", kChunkSpinHook,
                                            chunk_len(kChunkSpinHook)),
              BREAK_LUA_OK);
    ASSERT_EQ(break_lua_runtime_budget_trip_count(rt), 0u);
    break_lua_runtime_begin_frame(rt, 0.016);
    ASSERT_EQ(break_lua_runtime_budget_trip_count(rt), 1u);
    ASSERT_TRUE(break_lua_test_module_hooks_disabled(rt, "s"));

    /* A committed reload clears the mark (Stage 3 contract); the counter
     * is a lifetime diagnostic and keeps counting. */
    ASSERT_EQ(break_lua_runtime_reload_module(rt, "s", kChunkCleanHook,
                                              chunk_len(kChunkCleanHook),
                                              NULL),
              BREAK_LUA_OK);
    ASSERT_FALSE(break_lua_test_module_hooks_disabled(rt, "s"));
    break_lua_runtime_begin_frame(rt, 0.016);
    ASSERT_TRUE(break_lua_test_module_state_number(rt, "s", "ran", &v));
    ASSERT_EQ(v, 1.0);
    ASSERT_EQ(break_lua_runtime_budget_trip_count(rt), 1u);

    break_lua_runtime_destroy(rt);
}

TEST_MAIN_BEGIN()
    RUN_TEST(batch_create_capacity_validation);
    RUN_TEST(batch_double_destroy_aborts_in_test_builds);
    RUN_TEST(batch_allocation_failure_injection_is_bounded);
    RUN_TEST(bind_ecs_batch_validation);
    RUN_TEST(binding_apis_reject_non_owner_thread);
    RUN_TEST(script_enqueue_and_host_drain_fifo);
    RUN_TEST(batch_full_surfaces_bounded_failure_to_script);
    RUN_TEST(ecs_set_record_format_all_value_kinds);
    RUN_TEST(ecs_set_argument_validation_is_bounded_failure);
    RUN_TEST(spawn_without_bound_batch_fails_bounded);
    RUN_TEST(batch_destroy_before_runtime_releases_borrow);
    RUN_TEST(frame_hook_enqueue_drains_fifo);
    RUN_TEST(sandbox_dangerous_globals_absent_whitelist_present);
    RUN_TEST(sandbox_os_execute_and_io_open_calls_fail);
    RUN_TEST(break_table_and_stdlib_proxies_are_read_only);
    RUN_TEST(batch_pointer_never_reachable_from_lua);
    RUN_TEST(coroutine_absent_in_budgeted_hook_plan_checkbox);
    RUN_TEST(coroutine_guarded_hook_runs_clean_under_budget);
    RUN_TEST(stdlib_proxies_keep_modules_isolated);
    RUN_TEST(bind_config_validation);
    RUN_TEST(config_get_returns_clamped_values);
    RUN_TEST(bind_config_allocation_failure_is_bounded);
    RUN_TEST(sandbox_pcall_still_catches_ordinary_errors);
    RUN_TEST(sandbox_xpcall_handler_runs_for_ordinary_errors);
    RUN_TEST(budget_trip_is_uncatchable_by_script_pcall_in_hooks);
    RUN_TEST(budget_trip_propagates_through_nested_pcall_depth3);
    RUN_TEST(budget_trip_sentinel_never_observable_via_xpcall_handler);
    RUN_TEST(sandbox_xpcall_absorbs_ordinary_handler_error_like_base);
    RUN_TEST(budget_trip_inside_xpcall_handler_is_uncatchable);
    RUN_TEST(sandbox_xpcall_argument_errors_match_base_text);
    RUN_TEST(sandbox_xpcall_handler_error_levels_match_documented_behavior);
    RUN_TEST(budget_trip_count_tracks_and_reload_recovers);
TEST_MAIN_END()
