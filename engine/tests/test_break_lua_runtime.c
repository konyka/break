#include "test_framework.h"
#include <script/break_lua.h>
#include <script/break_lua_test_hooks.h>
#include <core/platform_thread.h>

#include <lua/lua.h>

#include <string.h>

#if !defined(_WIN32)
#include <sys/types.h>
#include <sys/wait.h>
#endif

/* Focused contract tests for the Stage 3 formal optional Lua runtime facade
 * (Task 1: VM ownership and lifecycle). Links the test-only break_lua_test
 * variant (BREAK_LUA_TESTING=1) for allocation failure injection, the
 * double-destroy fail-stop registry, and the type-erased VM state accessor;
 * the production break_lua target stays hook-free. */

TEST(create_with_null_config_uses_documented_defaults)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    BreakLuaRuntimeConfig cfg;
    ASSERT_NOT_NULL(rt);

    memset(&cfg, 0xFF, sizeof(cfg));
    ASSERT_EQ(break_lua_runtime_effective_config(rt, &cfg), BREAK_LUA_OK);
    ASSERT_EQ(cfg.max_modules, BREAK_LUA_DEFAULT_MAX_MODULES);
    ASSERT_EQ(cfg.max_values, BREAK_LUA_MAX_VALUES);
    ASSERT_EQ(cfg.max_module_bytes, (usize)BREAK_LUA_MAX_MODULE_BYTES);
    ASSERT_EQ(cfg.instruction_budget, 0u);

    /* NULL out argument is malformed, not a policy violation. */
    ASSERT_EQ(break_lua_runtime_effective_config(rt, NULL), BREAK_LUA_INVALID);

    break_lua_runtime_destroy(rt);
    break_lua_runtime_destroy(NULL); /* documented no-op */
}

TEST(create_explicit_config_within_caps_is_kept)
{
    BreakLuaRuntimeConfig cfg;
    BreakLuaRuntimeConfig out;
    BreakLuaRuntime *rt;

    memset(&cfg, 0, sizeof(cfg));
    cfg.max_modules = 8u;
    cfg.max_values = 16u;
    cfg.max_module_bytes = 4096u;
    cfg.instruction_budget = 50000u;

    rt = break_lua_runtime_create(&cfg);
    ASSERT_NOT_NULL(rt);
    memset(&out, 0, sizeof(out));
    ASSERT_EQ(break_lua_runtime_effective_config(rt, &out), BREAK_LUA_OK);
    ASSERT_EQ(out.max_modules, 8u);
    ASSERT_EQ(out.max_values, 16u);
    ASSERT_EQ(out.max_module_bytes, (usize)4096u);
    ASSERT_EQ(out.instruction_budget, 50000u);
    break_lua_runtime_destroy(rt);
}

TEST(config_over_hard_cap_fails_closed)
{
    BreakLuaRuntimeConfig cfg;
    memset(&cfg, 0, sizeof(cfg));

    /* Oversized caps are rejected (documented fail-closed), never clamped. */
    cfg.max_modules = BREAK_LUA_MAX_MODULES + 1u;
    ASSERT_TRUE(break_lua_runtime_create(&cfg) == NULL);

    cfg.max_modules = 0u;
    cfg.max_values = BREAK_LUA_MAX_VALUES + 1u;
    ASSERT_TRUE(break_lua_runtime_create(&cfg) == NULL);

    cfg.max_values = 0u;
    cfg.max_module_bytes = (usize)BREAK_LUA_MAX_MODULE_BYTES + 1u;
    ASSERT_TRUE(break_lua_runtime_create(&cfg) == NULL);

    /* Values exactly at the hard caps still succeed. */
    cfg.max_modules = BREAK_LUA_MAX_MODULES;
    cfg.max_values = BREAK_LUA_MAX_VALUES;
    cfg.max_module_bytes = (usize)BREAK_LUA_MAX_MODULE_BYTES;
    {
        BreakLuaRuntime *rt = break_lua_runtime_create(&cfg);
        ASSERT_NOT_NULL(rt);
        break_lua_runtime_destroy(rt);
    }
}

TEST(vm_state_created_with_base_libraries_open)
{
    /* The runtime owns exactly one lua_State with the standard libraries
     * opened at create. Sandbox hardening of per-module environments
     * (removing io/os.execute etc. from module chunks) is Task 4 scope; here
     * the base libraries must simply be present on the owned state. The hook
     * returns the state type-erased; the public API never exposes it. */
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    lua_State *L;
    ASSERT_NOT_NULL(rt);
    L = (lua_State *)break_lua_test_lua_state(rt);
    ASSERT_NOT_NULL(L);

    lua_getglobal(L, "string");
    ASSERT_EQ(lua_type(L, -1), LUA_TTABLE);
    lua_pop(L, 1);
    lua_getglobal(L, "math");
    ASSERT_EQ(lua_type(L, -1), LUA_TTABLE);
    lua_pop(L, 1);
    lua_getglobal(L, "table");
    ASSERT_EQ(lua_type(L, -1), LUA_TTABLE);
    lua_pop(L, 1);
    lua_getglobal(L, "os");
    ASSERT_EQ(lua_type(L, -1), LUA_TTABLE);
    lua_pop(L, 1);
    lua_getglobal(L, "io");
    ASSERT_EQ(lua_type(L, -1), LUA_TTABLE);
    lua_pop(L, 1);

    /* The probes above must leave the Lua stack balanced. */
    ASSERT_EQ(lua_gettop(L), 0);
    break_lua_runtime_destroy(rt);
}

static BreakLuaRuntime *g_probe_rt;
static BreakLuaError g_probe_config_result;
static BreakLuaError g_probe_owner_result;

static PLATFORM_THREAD_RET owner_probe_worker(PLATFORM_THREAD_ARG arg)
{
    BreakLuaRuntimeConfig out;
    (void)arg;
    g_probe_config_result = break_lua_runtime_effective_config(g_probe_rt, &out);
    g_probe_owner_result = break_lua_runtime_check_owner(g_probe_rt);
    return PLATFORM_THREAD_RETURN;
}

TEST(owner_thread_enforcement_probe)
{
    PlatformThread t;
    BreakLuaRuntimeConfig out;

    g_probe_rt = break_lua_runtime_create(NULL);
    ASSERT_NOT_NULL(g_probe_rt);

    /* The creating thread is the owner. */
    ASSERT_EQ(break_lua_runtime_check_owner(g_probe_rt), BREAK_LUA_OK);
    ASSERT_EQ(break_lua_runtime_effective_config(g_probe_rt, &out), BREAK_LUA_OK);

    /* A documented owner-only API called from another thread is rejected. */
    g_probe_config_result = BREAK_LUA_OK;
    g_probe_owner_result = BREAK_LUA_OK;
    ASSERT_TRUE(platform_thread_create(&t, owner_probe_worker, NULL));
    platform_thread_join(t);
    ASSERT_EQ(g_probe_config_result, BREAK_LUA_REJECTED);
    ASSERT_EQ(g_probe_owner_result, BREAK_LUA_REJECTED);

    break_lua_runtime_destroy(g_probe_rt);
    g_probe_rt = NULL;

    /* NULL runtime is malformed (INVALID), not a policy rejection. */
    ASSERT_EQ(break_lua_runtime_check_owner(NULL), BREAK_LUA_INVALID);
    ASSERT_EQ(break_lua_runtime_effective_config(NULL, &out), BREAK_LUA_INVALID);
}

TEST(double_destroy_aborts_in_test_builds)
{
#if !defined(_WIN32)
    pid_t pid = fork();
    if (pid == 0) {
        BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
        if (!rt) {
            _exit(2); /* create itself failed: not the path under test */
        }
        break_lua_runtime_destroy(rt);
        break_lua_runtime_destroy(rt); /* contract violation: must abort */
        _exit(0); /* reached only if double destroy was NOT rejected */
    }
    ASSERT_TRUE(pid > 0);
    {
        int status = 0;
        ASSERT_EQ(waitpid(pid, &status, 0), pid);
        /* abort() terminates by signal; a clean exit means the double
         * destroy slipped through. */
        ASSERT_TRUE(WIFSIGNALED(status));
    }
    /* The parent registry is unaffected: normal lifecycle still works. */
    {
        BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
        ASSERT_NOT_NULL(rt);
        break_lua_runtime_destroy(rt);
    }
#endif
}

TEST(create_allocation_failure_injection)
{
    u64 budget;

    /* Small budgets must fail: create needs the runtime struct allocation
     * plus the Lua allocator requests behind lua_newstate/luaL_openlibs. */
    for (budget = 0u; budget <= 7u; budget++) {
        break_lua_test_set_alloc_budget(budget);
        ASSERT_TRUE(break_lua_runtime_create(NULL) == NULL);
    }

    /* Doubling probe: a sufficiently large budget succeeds, and every
     * successful create along the way stays fully usable (and is destroyed,
     * so the ASan lane proves the partial-init cleanup leak-free). */
    budget = 8u;
    for (;;) {
        BreakLuaRuntime *rt;
        break_lua_test_set_alloc_budget(budget);
        rt = break_lua_runtime_create(NULL);
        if (rt) {
            ASSERT_EQ(break_lua_runtime_check_owner(rt), BREAK_LUA_OK);
            break_lua_runtime_destroy(rt);
            break;
        }
        ASSERT_TRUE(budget <= (1u << 20));
        budget *= 2u;
    }

    /* Hook disabled: the plain path works again. */
    break_lua_test_set_alloc_budget(BREAK_LUA_TEST_ALLOC_DISABLED);
    {
        BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
        ASSERT_NOT_NULL(rt);
        break_lua_runtime_destroy(rt);
    }
}

TEST(memory_budget_caps_vm_allocation_and_fails_closed)
{
    BreakLuaRuntimeConfig cfg;
    BreakLuaRuntimeConfig out;
    BreakLuaRuntime *rt;
    BreakLuaValue ret;
    static const char hog[] =
        "function grow(n)\n"
        "  local t = {}\n"
        "  for i = 1, n do t[i] = string.rep('x', 64) .. i end\n"
        "  return #t\n"
        "end\n";

    /* default: unlimited, reported as 0 */
    rt = break_lua_runtime_create(NULL);
    ASSERT_NOT_NULL(rt);
    ASSERT_EQ(break_lua_runtime_effective_config(rt, &out), BREAK_LUA_OK);
    ASSERT_EQ(out.memory_budget, (usize)0u);
    ASSERT_TRUE(break_lua_runtime_memory_in_use(rt) > 0u);
    break_lua_runtime_destroy(rt);

    /* too small to even open the libraries: create fails closed */
    memset(&cfg, 0, sizeof(cfg));
    cfg.memory_budget = 1024u;
    ASSERT_TRUE(break_lua_runtime_create(&cfg) == NULL);

    cfg.memory_budget = 1024u * 1024u;
    rt = break_lua_runtime_create(&cfg);
    ASSERT_NOT_NULL(rt);
    ASSERT_EQ(break_lua_runtime_effective_config(rt, &out), BREAK_LUA_OK);
    ASSERT_EQ(out.memory_budget, (usize)(1024u * 1024u));
    ASSERT_TRUE(break_lua_runtime_memory_in_use(rt) <= cfg.memory_budget);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "hog", hog, sizeof(hog) - 1u),
              BREAK_LUA_OK);

    /* a small request fits */
    memset(&ret, 0, sizeof(ret));
    {
        BreakLuaValue arg;
        memset(&arg, 0, sizeof(arg));
        arg.type = BREAK_LUA_VALUE_NUMBER;
        arg.as.n = 100.0;
        ASSERT_EQ(break_lua_runtime_call(rt, "hog", "grow", &arg, 1u, &ret, 1u),
                  BREAK_LUA_OK);
        ASSERT_EQ(ret.as.n, 100.0);
        /* one that needs far more than the budget fails as OOM, not abort */
        arg.as.n = 100000.0;
        ASSERT_EQ(break_lua_runtime_call(rt, "hog", "grow", &arg, 1u, &ret, 1u),
                  BREAK_LUA_OOM);
        ASSERT_TRUE(break_lua_runtime_memory_in_use(rt) <= cfg.memory_budget);
        /* the VM stays usable after the garbage is collected */
        arg.as.n = 100.0;
        ASSERT_EQ(break_lua_runtime_call(rt, "hog", "grow", &arg, 1u, &ret, 1u),
                  BREAK_LUA_OK);
    }
    ASSERT_EQ(break_lua_runtime_memory_in_use(NULL), (usize)0u);
    break_lua_runtime_destroy(rt);
}

TEST(error_name_strings)
{
    ASSERT_STR_EQ(break_lua_error_name(BREAK_LUA_OK), "OK");
    ASSERT_STR_EQ(break_lua_error_name(BREAK_LUA_INVALID), "INVALID");
    ASSERT_STR_EQ(break_lua_error_name(BREAK_LUA_CLOSED), "CLOSED");
    ASSERT_STR_EQ(break_lua_error_name(BREAK_LUA_OVERLOAD), "OVERLOAD");
    ASSERT_STR_EQ(break_lua_error_name(BREAK_LUA_OOM), "OOM");
    ASSERT_STR_EQ(break_lua_error_name(BREAK_LUA_TIMEOUT), "TIMEOUT");
    ASSERT_STR_EQ(break_lua_error_name(BREAK_LUA_STALE), "STALE");
    ASSERT_STR_EQ(break_lua_error_name(BREAK_LUA_REJECTED), "REJECTED");
    ASSERT_STR_EQ(break_lua_error_name(BREAK_LUA_FAILED), "FAILED");
    ASSERT_STR_EQ(break_lua_error_name((BreakLuaError)999), "UNKNOWN");
}

TEST_MAIN_BEGIN()
    RUN_TEST(create_with_null_config_uses_documented_defaults);
    RUN_TEST(create_explicit_config_within_caps_is_kept);
    RUN_TEST(config_over_hard_cap_fails_closed);
    RUN_TEST(vm_state_created_with_base_libraries_open);
    RUN_TEST(owner_thread_enforcement_probe);
    RUN_TEST(double_destroy_aborts_in_test_builds);
    RUN_TEST(create_allocation_failure_injection);
    RUN_TEST(memory_budget_caps_vm_allocation_and_fails_closed);
    RUN_TEST(error_name_strings);
TEST_MAIN_END()
