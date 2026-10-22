#include "test_framework.h"
#include <script/break_lua.h>
#include <script/break_lua_test_hooks.h>
#include <core/platform_thread.h>

#include <lua/lua.h>

#include <string.h>

/* Focused contract tests for the Stage 3 break_lua module registry
 * (Task 2: module load + versioned reload with old-version retention).
 * Links the test-only break_lua_test variant (BREAK_LUA_TESTING=1) for the
 * allocation budget hook and the module probe hooks; production break_lua
 * stays hook-free. No break_lua_runtime_call exists yet (Task 3): "old
 * version still serving" is asserted through the test-only registry probes
 * (live version/hash, module environment globals, persistent state table),
 * plus a successful later reload. */

/* Independent FNV-1a-64 so the tests cross-check the implementation's
 * hashes instead of trusting them. */
static u64 test_fnv1a64(const void *data, usize size)
{
    const unsigned char *p = (const unsigned char *)data;
    u64 h = UINT64_C(14695981039346656037);
    usize i;
    for (i = 0; i < size; i++) {
        h ^= (u64)p[i];
        h *= UINT64_C(1099511628211);
    }
    return h;
}

static usize chunk_len(const char *chunk)
{
    return strlen(chunk);
}

static const char kChunkV1[] =
    "marker = 1\n"                                             /* line 1 */
    "only_in_v1 = 100\n"                                       /* line 2 */
    "state.counter = (state.counter or 0) + 41\n"              /* line 3 */
    "function on_unload()\n"                                   /* line 4 */
    "    state.unload_count = (state.unload_count or 0) + 1\n" /* line 5 */
    "    state.unload_saw_marker = marker\n"                   /* line 6 */
    "end\n";                                                   /* line 7 */

static const char kChunkV2[] =
    "marker = 2\n"                                /* line 1 */
    "state.counter = (state.counter or 0) + 1\n"; /* line 2 */

static const char kChunkV3[] = "marker = 3\n";

static const char kChunkHookFails[] =
    "marker = 1\n"                 /* line 1 */
    "function on_unload()\n"       /* line 2 */
    "    error('unwilling')\n"     /* line 3 */
    "end\n";                       /* line 4 */

static const char kChunkSyntaxErr[] =
    "marker = 99\n"          /* line 1 */
    "this is broken (((\n";  /* line 2: syntax error here */

static const char kChunkRuntimeErr[] = "error('staged boom')\n";

static const char kChunkPartial[] =
    "state.counter = 99\n"      /* line 1: staged write happens */
    "error('late boom')\n";     /* line 2: then staging fails */

static const char kChunkLongErr[] = "error(string.rep('y', 300))\n";

static void assert_report_zeroed(const BreakLuaReloadReport *rep)
{
    ASSERT_EQ(rep->old_version, 0u);
    ASSERT_EQ(rep->new_version, 0u);
    ASSERT_EQ(rep->old_hash, UINT64_C(0));
    ASSERT_EQ(rep->new_hash, UINT64_C(0));
    ASSERT_FALSE(rep->committed);
    ASSERT_EQ(rep->error_line, 0u);
    ASSERT_EQ(rep->error[0], '\0');
}

TEST(load_basic_runs_in_module_env_with_persistent_state)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    lua_State *L;
    BreakLuaTestModuleStat st;
    double value = 0.0;
    ASSERT_NOT_NULL(rt);
    L = (lua_State *)break_lua_test_lua_state(rt);

    ASSERT_EQ(break_lua_runtime_load_module(rt, "mod", kChunkV1,
                                            chunk_len(kChunkV1)),
              BREAK_LUA_OK);

    st = break_lua_test_module_stat(rt, "mod");
    ASSERT_TRUE(st.loaded);
    ASSERT_EQ(st.version, 1u); /* first load starts at version 1 */
    ASSERT_EQ(st.hash, test_fnv1a64(kChunkV1, chunk_len(kChunkV1)));
    ASSERT_EQ(break_lua_test_module_count(rt), 1u);

    /* Chunk globals live in the per-module environment. */
    ASSERT_TRUE(break_lua_test_module_env_number(rt, "mod", "marker", &value));
    ASSERT_EQ(value, 1.0);
    /* The state table exists separately from the chunk and was populated. */
    ASSERT_TRUE(break_lua_test_module_state_number(rt, "mod", "counter", &value));
    ASSERT_EQ(value, 41.0);
    /* Unknown module probes fail closed. */
    ASSERT_FALSE(break_lua_test_module_stat(rt, "ghost").loaded);
    ASSERT_FALSE(break_lua_test_module_env_number(rt, "ghost", "marker", &value));

    ASSERT_EQ(lua_gettop(L), 0); /* every exit path left the stack balanced */
    break_lua_runtime_destroy(rt);
}

TEST(load_duplicate_rejected_without_reload)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    BreakLuaTestModuleStat st;
    ASSERT_NOT_NULL(rt);

    ASSERT_EQ(break_lua_runtime_load_module(rt, "mod", kChunkV1,
                                            chunk_len(kChunkV1)),
              BREAK_LUA_OK);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "mod", kChunkV2,
                                            chunk_len(kChunkV2)),
              BREAK_LUA_REJECTED);

    /* The rejected load changed nothing. */
    st = break_lua_test_module_stat(rt, "mod");
    ASSERT_EQ(st.version, 1u);
    ASSERT_EQ(st.hash, test_fnv1a64(kChunkV1, chunk_len(kChunkV1)));
    ASSERT_EQ(break_lua_test_module_count(rt), 1u);
    {
        double value = 0.0;
        ASSERT_TRUE(break_lua_test_module_env_number(rt, "mod", "marker", &value));
        ASSERT_EQ(value, 1.0);
    }
    break_lua_runtime_destroy(rt);
}

TEST(load_oversize_source_bounded_overload)
{
    BreakLuaRuntimeConfig cfg;
    BreakLuaRuntime *rt;
    char big[128];
    char exact[64];

    memset(&cfg, 0, sizeof(cfg));
    cfg.max_module_bytes = 64u;
    rt = break_lua_runtime_create(&cfg);
    ASSERT_NOT_NULL(rt);

    memset(big, 'x', sizeof(big)); /* contents never reach the parser */
    ASSERT_EQ(break_lua_runtime_load_module(rt, "big", big, sizeof(big)),
              BREAK_LUA_OVERLOAD);
    ASSERT_EQ(break_lua_test_module_count(rt), 0u);
    ASSERT_FALSE(break_lua_test_module_stat(rt, "big").loaded);

    /* Exactly at the byte cap is admitted (the cap is inclusive). */
    memcpy(exact, "state.x=1 --", 12);
    memset(exact + 12, 'x', sizeof(exact) - 12u);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "exact", exact, sizeof(exact)),
              BREAK_LUA_OK);
    {
        double value = 0.0;
        ASSERT_TRUE(break_lua_test_module_state_number(rt, "exact", "x", &value));
        ASSERT_EQ(value, 1.0);
    }
    break_lua_runtime_destroy(rt);
}

TEST(load_module_count_cap_overload)
{
    BreakLuaRuntimeConfig cfg;
    BreakLuaRuntime *rt;
    static const char tiny[] = "marker=1\n";

    memset(&cfg, 0, sizeof(cfg));
    cfg.max_modules = 2u;
    rt = break_lua_runtime_create(&cfg);
    ASSERT_NOT_NULL(rt);

    ASSERT_EQ(break_lua_runtime_load_module(rt, "a", tiny, chunk_len(tiny)),
              BREAK_LUA_OK);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "b", tiny, chunk_len(tiny)),
              BREAK_LUA_OK);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "c", tiny, chunk_len(tiny)),
              BREAK_LUA_OVERLOAD);
    ASSERT_EQ(break_lua_test_module_count(rt), 2u);

    /* A duplicate name is REJECTED even when the registry is full: the
     * duplicate check wins over the count check (reload is the escape). */
    ASSERT_EQ(break_lua_runtime_load_module(rt, "a", tiny, chunk_len(tiny)),
              BREAK_LUA_REJECTED);
    break_lua_runtime_destroy(rt);
}

TEST(load_invalid_args)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    char longname[200];
    static const char tiny[] = "marker=1\n";
    ASSERT_NOT_NULL(rt);

    memset(longname, 'a', sizeof(longname) - 1u);
    longname[sizeof(longname) - 1u] = '\0';

    ASSERT_EQ(break_lua_runtime_load_module(NULL, "m", tiny, chunk_len(tiny)),
              BREAK_LUA_INVALID);
    ASSERT_EQ(break_lua_runtime_load_module(rt, NULL, tiny, chunk_len(tiny)),
              BREAK_LUA_INVALID);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "", tiny, chunk_len(tiny)),
              BREAK_LUA_INVALID);
    ASSERT_EQ(break_lua_runtime_load_module(rt, longname, tiny, chunk_len(tiny)),
              BREAK_LUA_INVALID);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "m", NULL, chunk_len(tiny)),
              BREAK_LUA_INVALID);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "m", tiny, 0u),
              BREAK_LUA_INVALID);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "m", NULL, 0u),
              BREAK_LUA_INVALID);
    ASSERT_EQ(break_lua_test_module_count(rt), 0u);
    break_lua_runtime_destroy(rt);
}

TEST(load_syntax_error_fails_closed)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    lua_State *L;
    ASSERT_NOT_NULL(rt);
    L = (lua_State *)break_lua_test_lua_state(rt);

    ASSERT_EQ(break_lua_runtime_load_module(rt, "bad", kChunkSyntaxErr,
                                            chunk_len(kChunkSyntaxErr)),
              BREAK_LUA_FAILED);
    ASSERT_EQ(break_lua_test_module_count(rt), 0u);
    ASSERT_FALSE(break_lua_test_module_stat(rt, "bad").loaded);
    ASSERT_EQ(lua_gettop(L), 0);
    break_lua_runtime_destroy(rt);
}

TEST(load_staging_runtime_error_fails_closed)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    lua_State *L;
    ASSERT_NOT_NULL(rt);
    L = (lua_State *)break_lua_test_lua_state(rt);

    ASSERT_EQ(break_lua_runtime_load_module(rt, "bad", kChunkRuntimeErr,
                                            chunk_len(kChunkRuntimeErr)),
              BREAK_LUA_FAILED);
    ASSERT_EQ(break_lua_test_module_count(rt), 0u);
    ASSERT_FALSE(break_lua_test_module_stat(rt, "bad").loaded);
    ASSERT_EQ(lua_gettop(L), 0);
    break_lua_runtime_destroy(rt);
}

TEST(reload_success_commits_version_hash_and_preserved_state)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    lua_State *L;
    BreakLuaReloadReport rep;
    BreakLuaTestModuleStat st;
    double value = 0.0;
    ASSERT_NOT_NULL(rt);
    L = (lua_State *)break_lua_test_lua_state(rt);

    ASSERT_EQ(break_lua_runtime_load_module(rt, "mod", kChunkV1,
                                            chunk_len(kChunkV1)),
              BREAK_LUA_OK);

    memset(&rep, 0xFF, sizeof(rep));
    ASSERT_EQ(break_lua_runtime_reload_module(rt, "mod", kChunkV2,
                                              chunk_len(kChunkV2), &rep),
              BREAK_LUA_OK);

    /* Report fully populated on the success path. */
    ASSERT_TRUE(rep.committed);
    ASSERT_EQ(rep.old_version, 1u);
    ASSERT_EQ(rep.new_version, 2u);
    ASSERT_EQ(rep.old_hash, test_fnv1a64(kChunkV1, chunk_len(kChunkV1)));
    ASSERT_EQ(rep.new_hash, test_fnv1a64(kChunkV2, chunk_len(kChunkV2)));
    ASSERT_EQ(rep.error_line, 0u);
    ASSERT_EQ(rep.error[0], '\0');

    /* Registry now serves version 2. */
    st = break_lua_test_module_stat(rt, "mod");
    ASSERT_TRUE(st.loaded);
    ASSERT_EQ(st.version, 2u);
    ASSERT_EQ(st.hash, test_fnv1a64(kChunkV2, chunk_len(kChunkV2)));
    ASSERT_EQ(break_lua_test_module_count(rt), 1u);

    /* New environment committed: new marker, old chunk's globals gone. */
    ASSERT_TRUE(break_lua_test_module_env_number(rt, "mod", "marker", &value));
    ASSERT_EQ(value, 2.0);
    ASSERT_FALSE(break_lua_test_module_env_number(rt, "mod", "only_in_v1", &value));

    /* State table survived the reload by identity: v1 stored 41, the staged
     * v2 chunk observed the preserved value and added 1. */
    ASSERT_TRUE(break_lua_test_module_state_number(rt, "mod", "counter", &value));
    ASSERT_EQ(value, 42.0);

    /* The old module's on_unload ran before commit: it still saw the OLD
     * environment (marker == 1) and ran exactly once. */
    ASSERT_TRUE(break_lua_test_module_state_number(rt, "mod", "unload_count", &value));
    ASSERT_EQ(value, 1.0);
    ASSERT_TRUE(break_lua_test_module_state_number(rt, "mod", "unload_saw_marker", &value));
    ASSERT_EQ(value, 1.0);

    /* Second reload: version is monotonic; v2 defines no on_unload, so the
     * hook is optional and simply does not run. */
    memset(&rep, 0, sizeof(rep));
    ASSERT_EQ(break_lua_runtime_reload_module(rt, "mod", kChunkV3,
                                              chunk_len(kChunkV3), &rep),
              BREAK_LUA_OK);
    ASSERT_TRUE(rep.committed);
    ASSERT_EQ(rep.old_version, 2u);
    ASSERT_EQ(rep.new_version, 3u);
    st = break_lua_test_module_stat(rt, "mod");
    ASSERT_EQ(st.version, 3u);
    ASSERT_TRUE(break_lua_test_module_env_number(rt, "mod", "marker", &value));
    ASSERT_EQ(value, 3.0);
    ASSERT_TRUE(break_lua_test_module_state_number(rt, "mod", "counter", &value));
    ASSERT_EQ(value, 42.0); /* v3 does not touch state: v2's value persists */
    ASSERT_TRUE(break_lua_test_module_state_number(rt, "mod", "unload_count", &value));
    ASSERT_EQ(value, 1.0); /* no hook on v2: count unchanged */

    ASSERT_EQ(lua_gettop(L), 0);
    break_lua_runtime_destroy(rt);
}

TEST(reload_syntax_error_keeps_old_version_serving)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    BreakLuaReloadReport rep;
    BreakLuaTestModuleStat st;
    double value = 0.0;
    ASSERT_NOT_NULL(rt);

    ASSERT_EQ(break_lua_runtime_load_module(rt, "mod", kChunkV1,
                                            chunk_len(kChunkV1)),
              BREAK_LUA_OK);

    memset(&rep, 0xFF, sizeof(rep));
    ASSERT_EQ(break_lua_runtime_reload_module(rt, "mod", kChunkSyntaxErr,
                                              chunk_len(kChunkSyntaxErr), &rep),
              BREAK_LUA_FAILED);

    /* Report fully populated on the failure path. */
    ASSERT_FALSE(rep.committed);
    ASSERT_EQ(rep.old_version, 1u);
    ASSERT_EQ(rep.new_version, 1u); /* no version consumed by a failed reload */
    ASSERT_EQ(rep.old_hash, test_fnv1a64(kChunkV1, chunk_len(kChunkV1)));
    ASSERT_EQ(rep.new_hash,
              test_fnv1a64(kChunkSyntaxErr, chunk_len(kChunkSyntaxErr)));
    ASSERT_EQ(rep.error_line, 2u); /* the syntax error is on line 2 */
    ASSERT_TRUE(rep.error[0] != '\0');
    ASSERT_TRUE(strlen(rep.error) < sizeof(rep.error));

    /* The old version is fully intact and still serving. */
    st = break_lua_test_module_stat(rt, "mod");
    ASSERT_EQ(st.version, 1u);
    ASSERT_EQ(st.hash, test_fnv1a64(kChunkV1, chunk_len(kChunkV1)));
    ASSERT_TRUE(break_lua_test_module_env_number(rt, "mod", "marker", &value));
    ASSERT_EQ(value, 1.0);
    ASSERT_TRUE(break_lua_test_module_state_number(rt, "mod", "counter", &value));
    ASSERT_EQ(value, 41.0); /* the broken chunk never executed */

    /* And a later well-formed reload still commits. */
    ASSERT_EQ(break_lua_runtime_reload_module(rt, "mod", kChunkV2,
                                              chunk_len(kChunkV2), &rep),
              BREAK_LUA_OK);
    ASSERT_TRUE(rep.committed);
    ASSERT_EQ(rep.new_version, 2u);
    break_lua_runtime_destroy(rt);
}

TEST(reload_staging_runtime_error_keeps_old_version_serving)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    BreakLuaReloadReport rep;
    BreakLuaTestModuleStat st;
    double value = 0.0;
    ASSERT_NOT_NULL(rt);

    ASSERT_EQ(break_lua_runtime_load_module(rt, "mod", kChunkV1,
                                            chunk_len(kChunkV1)),
              BREAK_LUA_OK);

    memset(&rep, 0, sizeof(rep));
    ASSERT_EQ(break_lua_runtime_reload_module(rt, "mod", kChunkRuntimeErr,
                                              chunk_len(kChunkRuntimeErr), &rep),
              BREAK_LUA_FAILED);
    ASSERT_FALSE(rep.committed);
    ASSERT_EQ(rep.old_version, 1u);
    ASSERT_EQ(rep.new_version, 1u);
    ASSERT_EQ(rep.error_line, 1u); /* error() on line 1 carries its position */
    ASSERT_TRUE(strstr(rep.error, "staged boom") != NULL);

    st = break_lua_test_module_stat(rt, "mod");
    ASSERT_EQ(st.version, 1u);
    ASSERT_TRUE(break_lua_test_module_env_number(rt, "mod", "marker", &value));
    ASSERT_EQ(value, 1.0);
    ASSERT_TRUE(break_lua_test_module_state_number(rt, "mod", "counter", &value));
    ASSERT_EQ(value, 41.0); /* error() fired before any state write */
    break_lua_runtime_destroy(rt);
}

TEST(reload_staging_error_partial_state_writes_are_not_rolled_back)
{
    /* Documented semantics: only the environment/version commit is atomic.
     * The state table is the module's own data; a staged chunk that writes
     * to state and THEN fails leaves its partial writes behind. */
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    BreakLuaReloadReport rep;
    double value = 0.0;
    ASSERT_NOT_NULL(rt);

    ASSERT_EQ(break_lua_runtime_load_module(rt, "mod", kChunkV1,
                                            chunk_len(kChunkV1)),
              BREAK_LUA_OK);
    ASSERT_EQ(break_lua_runtime_reload_module(rt, "mod", kChunkPartial,
                                              chunk_len(kChunkPartial), &rep),
              BREAK_LUA_FAILED);
    ASSERT_FALSE(rep.committed);

    /* Old environment still serves (marker 1), but the staged chunk's state
     * write is visible: state is shared, never rolled back. */
    ASSERT_TRUE(break_lua_test_module_env_number(rt, "mod", "marker", &value));
    ASSERT_EQ(value, 1.0);
    ASSERT_TRUE(break_lua_test_module_state_number(rt, "mod", "counter", &value));
    ASSERT_EQ(value, 99.0);

    /* The next successful reload observes even that partial state. */
    ASSERT_EQ(break_lua_runtime_reload_module(rt, "mod", kChunkV2,
                                              chunk_len(kChunkV2), &rep),
              BREAK_LUA_OK);
    ASSERT_TRUE(rep.committed);
    ASSERT_TRUE(break_lua_test_module_state_number(rt, "mod", "counter", &value));
    ASSERT_EQ(value, 100.0); /* 99 (partial write) + 1 (v2 chunk) */
    break_lua_runtime_destroy(rt);
}

TEST(reload_unload_hook_error_keeps_old_version_serving)
{
    /* A failing on_unload vetoes the reload: the commit never happens, the
     * old environment/version stay live. (A module whose hook always errors
     * wedges itself at its current version by its own choice.) */
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    BreakLuaReloadReport rep;
    BreakLuaTestModuleStat st;
    double value = 0.0;
    ASSERT_NOT_NULL(rt);

    ASSERT_EQ(break_lua_runtime_load_module(rt, "mod", kChunkHookFails,
                                            chunk_len(kChunkHookFails)),
              BREAK_LUA_OK);

    memset(&rep, 0, sizeof(rep));
    ASSERT_EQ(break_lua_runtime_reload_module(rt, "mod", kChunkV2,
                                              chunk_len(kChunkV2), &rep),
              BREAK_LUA_FAILED);
    ASSERT_FALSE(rep.committed);
    ASSERT_EQ(rep.old_version, 1u);
    ASSERT_EQ(rep.new_version, 1u);
    ASSERT_EQ(rep.error_line, 3u); /* error() inside on_unload at line 3 */
    ASSERT_TRUE(strstr(rep.error, "unwilling") != NULL);

    st = break_lua_test_module_stat(rt, "mod");
    ASSERT_EQ(st.version, 1u);
    ASSERT_EQ(st.hash, test_fnv1a64(kChunkHookFails, chunk_len(kChunkHookFails)));
    ASSERT_TRUE(break_lua_test_module_env_number(rt, "mod", "marker", &value));
    ASSERT_EQ(value, 1.0);
    ASSERT_EQ(break_lua_test_module_count(rt), 1u);

    /* The hook still vetoes a different candidate, too. */
    ASSERT_EQ(break_lua_runtime_reload_module(rt, "mod", kChunkV3,
                                              chunk_len(kChunkV3), &rep),
              BREAK_LUA_FAILED);
    ASSERT_FALSE(rep.committed);
    st = break_lua_test_module_stat(rt, "mod");
    ASSERT_EQ(st.version, 1u);
    break_lua_runtime_destroy(rt);
}

TEST(reload_unknown_module_is_stale)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    BreakLuaReloadReport rep;
    ASSERT_NOT_NULL(rt);

    memset(&rep, 0xFF, sizeof(rep));
    /* Contract: reload of a name that was never loaded is BREAK_LUA_STALE
     * (the name names no live object), never an implicit load. */
    ASSERT_EQ(break_lua_runtime_reload_module(rt, "ghost", kChunkV1,
                                              chunk_len(kChunkV1), &rep),
              BREAK_LUA_STALE);
    assert_report_zeroed(&rep);
    ASSERT_EQ(break_lua_test_module_count(rt), 0u);
    break_lua_runtime_destroy(rt);
}

TEST(reload_oversize_overload_leaves_report_populated)
{
    BreakLuaRuntimeConfig cfg;
    BreakLuaRuntime *rt;
    BreakLuaReloadReport rep;
    char big[128];
    char exact[64];

    memset(&cfg, 0, sizeof(cfg));
    cfg.max_module_bytes = 64u;
    rt = break_lua_runtime_create(&cfg);
    ASSERT_NOT_NULL(rt);

    memcpy(exact, "state.x=1 --", 12);
    memset(exact + 12, 'x', sizeof(exact) - 12u);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "mod", exact, sizeof(exact)),
              BREAK_LUA_OK);

    memset(big, 'y', sizeof(big));
    memset(&rep, 0xFF, sizeof(rep));
    ASSERT_EQ(break_lua_runtime_reload_module(rt, "mod", big, sizeof(big), &rep),
              BREAK_LUA_OVERLOAD);
    ASSERT_FALSE(rep.committed);
    ASSERT_EQ(rep.old_version, 1u);
    ASSERT_EQ(rep.new_version, 1u);
    ASSERT_EQ(rep.old_hash, test_fnv1a64(exact, sizeof(exact)));
    ASSERT_EQ(rep.new_hash, UINT64_C(0)); /* rejected before hashing */
    ASSERT_EQ(rep.error_line, 0u);        /* not a Lua loader/runtime error */
    ASSERT_EQ(rep.error[0], '\0');

    /* Old version untouched. */
    {
        BreakLuaTestModuleStat st = break_lua_test_module_stat(rt, "mod");
        double value = 0.0;
        ASSERT_EQ(st.version, 1u);
        ASSERT_TRUE(break_lua_test_module_state_number(rt, "mod", "x", &value));
        ASSERT_EQ(value, 1.0);
    }
    break_lua_runtime_destroy(rt);
}

TEST(reload_report_null_is_allowed)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    BreakLuaTestModuleStat st;
    ASSERT_NOT_NULL(rt);

    ASSERT_EQ(break_lua_runtime_load_module(rt, "mod", kChunkV1,
                                            chunk_len(kChunkV1)),
              BREAK_LUA_OK);
    /* The report is optional: NULL means "no details wanted". */
    ASSERT_EQ(break_lua_runtime_reload_module(rt, "mod", kChunkV2,
                                              chunk_len(kChunkV2), NULL),
              BREAK_LUA_OK);
    st = break_lua_test_module_stat(rt, "mod");
    ASSERT_EQ(st.version, 2u);
    break_lua_runtime_destroy(rt);
}

TEST(reload_invalid_args_write_zeroed_report)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    BreakLuaReloadReport rep;
    static const char tiny[] = "marker=1\n";
    ASSERT_NOT_NULL(rt);

    memset(&rep, 0xFF, sizeof(rep));
    ASSERT_EQ(break_lua_runtime_reload_module(NULL, "m", tiny, chunk_len(tiny), &rep),
              BREAK_LUA_INVALID);
    assert_report_zeroed(&rep);

    memset(&rep, 0xFF, sizeof(rep));
    ASSERT_EQ(break_lua_runtime_reload_module(rt, NULL, tiny, chunk_len(tiny), &rep),
              BREAK_LUA_INVALID);
    assert_report_zeroed(&rep);

    memset(&rep, 0xFF, sizeof(rep));
    ASSERT_EQ(break_lua_runtime_reload_module(rt, "m", NULL, chunk_len(tiny), &rep),
              BREAK_LUA_INVALID);
    assert_report_zeroed(&rep);

    memset(&rep, 0xFF, sizeof(rep));
    ASSERT_EQ(break_lua_runtime_reload_module(rt, "m", tiny, 0u, &rep),
              BREAK_LUA_INVALID);
    assert_report_zeroed(&rep);

    memset(&rep, 0xFF, sizeof(rep));
    ASSERT_EQ(break_lua_runtime_reload_module(rt, "", tiny, chunk_len(tiny), &rep),
              BREAK_LUA_INVALID);
    assert_report_zeroed(&rep);

    ASSERT_EQ(break_lua_test_module_count(rt), 0u);
    break_lua_runtime_destroy(rt);
}

TEST(reload_error_string_truncated_to_report_bounds)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    BreakLuaReloadReport rep;
    ASSERT_NOT_NULL(rt);

    ASSERT_EQ(break_lua_runtime_load_module(rt, "mod", kChunkV1,
                                            chunk_len(kChunkV1)),
              BREAK_LUA_OK);
    memset(&rep, 0, sizeof(rep));
    ASSERT_EQ(break_lua_runtime_reload_module(rt, "mod", kChunkLongErr,
                                              chunk_len(kChunkLongErr), &rep),
              BREAK_LUA_FAILED);
    ASSERT_FALSE(rep.committed);
    /* 300+ byte Lua error message truncated into the 128-byte field. */
    ASSERT_TRUE(strlen(rep.error) > 100u);
    ASSERT_TRUE(strlen(rep.error) <= sizeof(rep.error) - 1u);
    ASSERT_TRUE(strstr(rep.error, "yyy") != NULL);
    break_lua_runtime_destroy(rt);
}

static BreakLuaRuntime *g_owner_rt;
static BreakLuaError g_owner_load_result;
static BreakLuaError g_owner_reload_result;
static BreakLuaReloadReport g_owner_report;

static PLATFORM_THREAD_RET module_owner_probe_worker(PLATFORM_THREAD_ARG arg)
{
    static const char tiny[] = "marker=1\n";
    (void)arg;
    memset(&g_owner_report, 0xFF, sizeof(g_owner_report));
    g_owner_load_result = break_lua_runtime_load_module(
        g_owner_rt, "m", tiny, chunk_len(tiny));
    g_owner_reload_result = break_lua_runtime_reload_module(
        g_owner_rt, "m", tiny, chunk_len(tiny), &g_owner_report);
    return PLATFORM_THREAD_RETURN;
}

TEST(module_apis_reject_non_owner_threads)
{
    PlatformThread t;
    BreakLuaTestModuleStat st;

    g_owner_rt = break_lua_runtime_create(NULL);
    ASSERT_NOT_NULL(g_owner_rt);

    ASSERT_TRUE(platform_thread_create(&t, module_owner_probe_worker, NULL));
    platform_thread_join(t);
    ASSERT_EQ(g_owner_load_result, BREAK_LUA_REJECTED);
    ASSERT_EQ(g_owner_reload_result, BREAK_LUA_REJECTED);
    assert_report_zeroed(&g_owner_report);
    ASSERT_EQ(break_lua_test_module_count(g_owner_rt), 0u);

    /* The owner thread itself is unaffected. */
    ASSERT_EQ(break_lua_runtime_load_module(g_owner_rt, "m", kChunkV1,
                                            chunk_len(kChunkV1)),
              BREAK_LUA_OK);
    st = break_lua_test_module_stat(g_owner_rt, "m");
    ASSERT_EQ(st.version, 1u);

    break_lua_runtime_destroy(g_owner_rt);
    g_owner_rt = NULL;
}

TEST(oom_injection_on_load_and_reload_is_bounded)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    BreakLuaTestModuleStat st;
    u64 budget;
    ASSERT_NOT_NULL(rt);

    /* Every under-budget load fails OOM (Lua allocator or C-side copy) and
     * registers nothing; the ASan lane proves the cleanup leak-free. */
    for (budget = 0u; budget <= 7u; budget++) {
        break_lua_test_set_alloc_budget(budget);
        ASSERT_EQ(break_lua_runtime_load_module(rt, "oom_mod", kChunkV1,
                                                chunk_len(kChunkV1)),
                  BREAK_LUA_OOM);
        ASSERT_EQ(break_lua_test_module_count(rt), 0u);
    }
    budget = 8u;
    for (;;) {
        BreakLuaError err;
        break_lua_test_set_alloc_budget(budget);
        err = break_lua_runtime_load_module(rt, "oom_mod", kChunkV1,
                                            chunk_len(kChunkV1));
        if (err == BREAK_LUA_OK) {
            break;
        }
        ASSERT_EQ(err, BREAK_LUA_OOM);
        ASSERT_EQ(break_lua_test_module_count(rt), 0u);
        ASSERT_TRUE(budget <= (u64)(1u << 20));
        budget *= 2u;
    }
    break_lua_test_set_alloc_budget(BREAK_LUA_TEST_ALLOC_DISABLED);
    ASSERT_EQ(break_lua_test_module_count(rt), 1u);

    /* Reload with an exhausted budget: bounded OOM, old version retained. */
    ASSERT_EQ(break_lua_runtime_load_module(rt, "mod", kChunkV1,
                                            chunk_len(kChunkV1)),
              BREAK_LUA_OK);
    break_lua_test_set_alloc_budget(0u);
    {
        BreakLuaReloadReport rep;
        memset(&rep, 0xFF, sizeof(rep));
        ASSERT_EQ(break_lua_runtime_reload_module(rt, "mod", kChunkV2,
                                                  chunk_len(kChunkV2), &rep),
                  BREAK_LUA_OOM);
        ASSERT_FALSE(rep.committed);
        ASSERT_EQ(rep.old_version, 1u);
        ASSERT_EQ(rep.new_version, 1u);
        ASSERT_EQ(rep.old_hash, test_fnv1a64(kChunkV1, chunk_len(kChunkV1)));
        ASSERT_EQ(rep.new_hash, test_fnv1a64(kChunkV2, chunk_len(kChunkV2)));
    }
    st = break_lua_test_module_stat(rt, "mod");
    ASSERT_EQ(st.version, 1u);
    {
        double value = 0.0;
        ASSERT_TRUE(break_lua_test_module_env_number(rt, "mod", "marker", &value));
        ASSERT_EQ(value, 1.0);
    }

    /* Budget lifted: the same reload commits. */
    break_lua_test_set_alloc_budget(BREAK_LUA_TEST_ALLOC_DISABLED);
    {
        BreakLuaReloadReport rep;
        ASSERT_EQ(break_lua_runtime_reload_module(rt, "mod", kChunkV2,
                                                  chunk_len(kChunkV2), &rep),
                  BREAK_LUA_OK);
        ASSERT_TRUE(rep.committed);
        ASSERT_EQ(rep.new_version, 2u);
    }
    break_lua_runtime_destroy(rt);
}

TEST_MAIN_BEGIN()
    RUN_TEST(load_basic_runs_in_module_env_with_persistent_state);
    RUN_TEST(load_duplicate_rejected_without_reload);
    RUN_TEST(load_oversize_source_bounded_overload);
    RUN_TEST(load_module_count_cap_overload);
    RUN_TEST(load_invalid_args);
    RUN_TEST(load_syntax_error_fails_closed);
    RUN_TEST(load_staging_runtime_error_fails_closed);
    RUN_TEST(reload_success_commits_version_hash_and_preserved_state);
    RUN_TEST(reload_syntax_error_keeps_old_version_serving);
    RUN_TEST(reload_staging_runtime_error_keeps_old_version_serving);
    RUN_TEST(reload_staging_error_partial_state_writes_are_not_rolled_back);
    RUN_TEST(reload_unload_hook_error_keeps_old_version_serving);
    RUN_TEST(reload_unknown_module_is_stale);
    RUN_TEST(reload_oversize_overload_leaves_report_populated);
    RUN_TEST(reload_report_null_is_allowed);
    RUN_TEST(reload_invalid_args_write_zeroed_report);
    RUN_TEST(reload_error_string_truncated_to_report_bounds);
    RUN_TEST(module_apis_reject_non_owner_threads);
    RUN_TEST(oom_injection_on_load_and_reload_is_bounded);
TEST_MAIN_END()
