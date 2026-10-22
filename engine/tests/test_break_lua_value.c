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

/* Focused contract tests for the Stage 3 break_lua value marshalling, module
 * calls, and frame lifecycle (Task 3). Links the test-only break_lua_test
 * variant (BREAK_LUA_TESTING=1) for the allocation budget hook, the type-
 * erased VM state accessor (stack-balance assertions), the frame-error
 * record probes, the hooks-disabled probe, and the mid-frame reload binding;
 * production break_lua stays hook-free. */

static usize chunk_len(const char *chunk)
{
    return strlen(chunk);
}

static BreakLuaValue value_bool(bool b)
{
    BreakLuaValue v;
    memset(&v, 0, sizeof(v));
    v.type = BREAK_LUA_VALUE_BOOL;
    v.as.b = b;
    return v;
}

static BreakLuaValue value_number(f64 n)
{
    BreakLuaValue v;
    memset(&v, 0, sizeof(v));
    v.type = BREAK_LUA_VALUE_NUMBER;
    v.as.n = n;
    return v;
}

/* len is derived from the C string; callers needing an explicit len use
 * value_string_len. */
static BreakLuaValue value_string(const char *s)
{
    BreakLuaValue v;
    usize len = strlen(s);
    memset(&v, 0, sizeof(v));
    v.type = BREAK_LUA_VALUE_STRING;
    memcpy(v.as.s.data, s, len + 1u);
    v.as.s.len = (u32)len;
    return v;
}

static BreakLuaValue value_string_len(const char *s, u32 len)
{
    BreakLuaValue v;
    memset(&v, 0, sizeof(v));
    v.type = BREAK_LUA_VALUE_STRING;
    memcpy(v.as.s.data, s, strlen(s) + 1u);
    v.as.s.len = len;
    return v;
}

static const char kChunkMix[] =
    "function mix(a, b, n, s)\n"
    "    return a == nil, b, n * 2, (s or '') .. '!'\n"
    "end\n";

static const char kChunkEcho[] =
    "function echo(s)\n"
    "    return s\n"
    "end\n";

static const char kChunkThree[] =
    "function three()\n"
    "    return 1, 'two', 3.5\n"
    "end\n"
    "function none()\n"
    "end\n";

static const char kChunkBoom[] =
    "function boom()\n"
    "    error('call boom')\n"
    "end\n";

static const char kChunkTable[] =
    "function tab()\n"
    "    return {}\n"
    "end\n";

static const char kChunkLongStr[] =
    "function longstr()\n"
    "    return string.rep('z', 300)\n"
    "end\n";

static const char kChunkWide[] =
    "local t = {}\n"
    "for i = 1, 64 do t[i] = i end\n"
    "function count_args(...)\n"
    "    return select('#', ...)\n"
    "end\n"
    "function many()\n"
    "    return table.unpack(t, 1, 64)\n"
    "end\n";

static const char kChunkFields[] =
    "marker = 7\n";

static const char kChunkHooks[] =
    "function on_frame_begin(dt)\n"
    "    state.begin_count = (state.begin_count or 0) + 1\n"
    "    state.dt_sum = (state.dt_sum or 0) + dt\n"
    "end\n"
    "function on_frame_end()\n"
    "    state.end_count = (state.end_count or 0) + 1\n"
    "end\n";

static const char kChunkNoHooks[] =
    "marker = 1\n";

static const char kChunkHookBoom[] =
    "function on_frame_begin(dt)\n"
    "    error('begin boom')\n"
    "end\n";

static const char kChunkHookLongErr[] =
    "function on_frame_begin(dt)\n"
    "    error(string.rep('y', 300))\n"
    "end\n";

static const char kChunkSpin[] =
    "function on_frame_begin(dt)\n"
    "    local x = 0\n"
    "    for i = 1, 100000000 do x = x + i end\n"
    "    state.spun = (state.spun or 0) + 1\n"
    "end\n";

static const char kChunkSpinFast[] =
    "function on_frame_begin(dt)\n"
    "    state.spun = (state.spun or 0) + 1\n"
    "end\n";

static const char kChunkLoop[] =
    "function on_frame_begin(dt)\n"
    "    local x = 0\n"
    "    for i = 1, 2000 do x = x + i end\n"
    "    state.looped = (state.looped or 0) + 1\n"
    "end\n";

static const char kChunkFrameV1[] =
    "function on_frame_begin(dt)\n"
    "    state.begin_marker = 1\n"
    "end\n"
    "function on_frame_end()\n"
    "    state.end_marker = 1\n"
    "end\n";

static const char kChunkFrameV2[] =
    "function on_frame_begin(dt)\n"
    "    state.begin_marker = 2\n"
    "end\n"
    "function on_frame_end()\n"
    "    state.end_marker = 2\n"
    "end\n";

/* Module A reloads module B from inside its own on_frame_begin hook via the
 * test-only _test_reload_now binding. Module B's two versions differ only in
 * the chunk-global marker their hooks copy into the shared state table. */
static const char kChunkReloaderA[] =
    "function on_frame_begin(dt)\n"
    "    state.fired = (state.fired or 0) + 1\n"
    "    if state.fired == 1 then _test_reload_now() end\n"
    "end\n";

static const char kChunkBV1[] =
    "marker = 1\n"
    "function on_frame_begin(dt)\n"
    "    state.seen_marker = marker\n"
    "end\n";

static const char kChunkBV2[] =
    "marker = 2\n"
    "function on_frame_begin(dt)\n"
    "    state.seen_marker = marker\n"
    "end\n";

static lua_State *test_state(BreakLuaRuntime *rt)
{
    return (lua_State *)break_lua_test_lua_state(rt);
}

static void assert_stack_balanced(BreakLuaRuntime *rt)
{
    ASSERT_EQ(lua_gettop(test_state(rt)), 0);
}

TEST(call_round_trips_mixed_args_and_returns)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    BreakLuaValue args[4];
    BreakLuaValue rets[4];
    ASSERT_NOT_NULL(rt);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "mixmod", kChunkMix,
                                            chunk_len(kChunkMix)),
              BREAK_LUA_OK);

    memset(rets, 0xFF, sizeof(rets));
    args[0].type = BREAK_LUA_VALUE_NIL; /* rest zeroed by value_* helpers */
    memset(&args[0], 0, sizeof(args[0]));
    args[0].type = BREAK_LUA_VALUE_NIL;
    args[1] = value_bool(true);
    args[2] = value_number(21.0);
    args[3] = value_string("hi");

    ASSERT_EQ(break_lua_runtime_call(rt, "mixmod", "mix", args, 4u,
                                     rets, 4u),
              BREAK_LUA_OK);
    ASSERT_EQ(rets[0].type, BREAK_LUA_VALUE_BOOL);
    ASSERT_TRUE(rets[0].as.b); /* a == nil */
    ASSERT_EQ(rets[1].type, BREAK_LUA_VALUE_BOOL);
    ASSERT_TRUE(rets[1].as.b);
    ASSERT_EQ(rets[2].type, BREAK_LUA_VALUE_NUMBER);
    ASSERT_FLOAT_EQ(rets[2].as.n, 42.0, 1e-12);
    ASSERT_EQ(rets[3].type, BREAK_LUA_VALUE_STRING);
    ASSERT_EQ(rets[3].as.s.len, 3u);
    ASSERT_STR_EQ(rets[3].as.s.data, "hi!");
    /* Produced strings are always NUL-terminated at data[len]. */
    ASSERT_EQ(rets[3].as.s.data[3], '\0');

    assert_stack_balanced(rt);
    break_lua_runtime_destroy(rt);
}

TEST(call_return_nil_padding_and_extra_discard)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    BreakLuaValue rets[5];
    ASSERT_NOT_NULL(rt);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "t", kChunkThree,
                                            chunk_len(kChunkThree)),
              BREAK_LUA_OK);

    /* Capacity above the actual count: Lua nil-pads, marshalled as NIL. */
    ASSERT_EQ(break_lua_runtime_call(rt, "t", "three", NULL, 0u, rets, 5u),
              BREAK_LUA_OK);
    ASSERT_EQ(rets[0].type, BREAK_LUA_VALUE_NUMBER);
    ASSERT_FLOAT_EQ(rets[0].as.n, 1.0, 1e-12);
    ASSERT_EQ(rets[1].type, BREAK_LUA_VALUE_STRING);
    ASSERT_STR_EQ(rets[1].as.s.data, "two");
    ASSERT_EQ(rets[1].as.s.len, 3u);
    ASSERT_EQ(rets[2].type, BREAK_LUA_VALUE_NUMBER);
    ASSERT_FLOAT_EQ(rets[2].as.n, 3.5, 1e-12);
    ASSERT_EQ(rets[3].type, BREAK_LUA_VALUE_NIL);
    ASSERT_EQ(rets[4].type, BREAK_LUA_VALUE_NIL);

    /* Capacity below the actual count: extra Lua results are discarded. */
    memset(rets, 0, sizeof(rets));
    ASSERT_EQ(break_lua_runtime_call(rt, "t", "three", NULL, 0u, rets, 1u),
              BREAK_LUA_OK);
    ASSERT_EQ(rets[0].type, BREAK_LUA_VALUE_NUMBER);
    ASSERT_FLOAT_EQ(rets[0].as.n, 1.0, 1e-12);

    /* A function returning nothing nil-pads the whole capacity. */
    memset(rets, 0xFF, sizeof(rets));
    ASSERT_EQ(break_lua_runtime_call(rt, "t", "none", NULL, 0u, rets, 2u),
              BREAK_LUA_OK);
    ASSERT_EQ(rets[0].type, BREAK_LUA_VALUE_NIL);
    ASSERT_EQ(rets[1].type, BREAK_LUA_VALUE_NIL);

    assert_stack_balanced(rt);
    break_lua_runtime_destroy(rt);
}

TEST(call_zero_return_capacity_needs_no_buffer)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    ASSERT_NOT_NULL(rt);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "t", kChunkThree,
                                            chunk_len(kChunkThree)),
              BREAK_LUA_OK);
    /* returns may be NULL exactly when return_capacity is 0. */
    ASSERT_EQ(break_lua_runtime_call(rt, "t", "three", NULL, 0u, NULL, 0u),
              BREAK_LUA_OK);
    assert_stack_balanced(rt);
    break_lua_runtime_destroy(rt);
}

TEST(call_string_round_trip_and_nul_termination)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    BreakLuaValue arg;
    BreakLuaValue ret;
    ASSERT_NOT_NULL(rt);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "e", kChunkEcho,
                                            chunk_len(kChunkEcho)),
              BREAK_LUA_OK);

    /* 127 bytes: exactly at the bounded-copy ceiling, still accepted. */
    {
        char buf[128];
        usize i;
        for (i = 0u; i < 127u; i++) {
            buf[i] = (char)('a' + (int)(i % 26u));
        }
        buf[127] = '\0';
        arg = value_string(buf); /* len 127 */
    }
    ASSERT_EQ(arg.as.s.len, 127u);
    ASSERT_EQ(break_lua_runtime_call(rt, "e", "echo", &arg, 1u, &ret, 1u),
              BREAK_LUA_OK);
    ASSERT_EQ(ret.type, BREAK_LUA_VALUE_STRING);
    ASSERT_EQ(ret.as.s.len, 127u);
    ASSERT_EQ(ret.as.s.data[127], '\0');
    ASSERT_STR_EQ(ret.as.s.data, arg.as.s.data);

    /* Empty string round-trips with len 0. */
    arg = value_string("");
    ASSERT_EQ(break_lua_runtime_call(rt, "e", "echo", &arg, 1u, &ret, 1u),
              BREAK_LUA_OK);
    ASSERT_EQ(ret.type, BREAK_LUA_VALUE_STRING);
    ASSERT_EQ(ret.as.s.len, 0u);
    ASSERT_EQ(ret.as.s.data[0], '\0');

    assert_stack_balanced(rt);
    break_lua_runtime_destroy(rt);
}

TEST(call_string_arg_over_capacity_is_bounded_overload)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    BreakLuaValue arg;
    BreakLuaValue ret;
    ASSERT_NOT_NULL(rt);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "e", kChunkEcho,
                                            chunk_len(kChunkEcho)),
              BREAK_LUA_OK);

    /* len >= 128 claims more bytes than the bounded buffer can hold:
     * bounded OVERLOAD, never an over-read. */
    arg = value_string_len("abc", 128u);
    memset(&ret, 0xFF, sizeof(ret));
    ASSERT_EQ(break_lua_runtime_call(rt, "e", "echo", &arg, 1u, &ret, 1u),
              BREAK_LUA_OVERLOAD);
    /* Post-admission failure leaves the returns slots NIL-written. */
    ASSERT_EQ(ret.type, BREAK_LUA_VALUE_NIL);

    arg = value_string_len("abc", 1000u);
    ASSERT_EQ(break_lua_runtime_call(rt, "e", "echo", &arg, 1u, &ret, 1u),
              BREAK_LUA_OVERLOAD);

    /* The module still serves afterwards: the failure is bounded. */
    arg = value_string("ok");
    ASSERT_EQ(break_lua_runtime_call(rt, "e", "echo", &arg, 1u, &ret, 1u),
              BREAK_LUA_OK);
    ASSERT_STR_EQ(ret.as.s.data, "ok");

    assert_stack_balanced(rt);
    break_lua_runtime_destroy(rt);
}

TEST(call_return_string_over_capacity_is_bounded_overload)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    BreakLuaValue ret;
    ASSERT_NOT_NULL(rt);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "l", kChunkLongStr,
                                            chunk_len(kChunkLongStr)),
              BREAK_LUA_OK);

    /* A 300-byte Lua string cannot fit the 128-byte bounded copy: bounded
     * OVERLOAD, no overflow, slot stays NIL. */
    memset(&ret, 0xFF, sizeof(ret));
    ASSERT_EQ(break_lua_runtime_call(rt, "l", "longstr", NULL, 0u, &ret, 1u),
              BREAK_LUA_OVERLOAD);
    ASSERT_EQ(ret.type, BREAK_LUA_VALUE_NIL);

    assert_stack_balanced(rt);
    break_lua_runtime_destroy(rt);
}

TEST(call_unrepresentable_return_is_failed)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    BreakLuaValue ret;
    ASSERT_NOT_NULL(rt);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "tab", kChunkTable,
                                            chunk_len(kChunkTable)),
              BREAK_LUA_OK);

    /* BreakLuaValue covers nil/bool/number/string only: a table return is a
     * bounded FAILED, not a silent NIL. */
    memset(&ret, 0xFF, sizeof(ret));
    ASSERT_EQ(break_lua_runtime_call(rt, "tab", "tab", NULL, 0u, &ret, 1u),
              BREAK_LUA_FAILED);
    ASSERT_EQ(ret.type, BREAK_LUA_VALUE_NIL);

    assert_stack_balanced(rt);
    break_lua_runtime_destroy(rt);
}

TEST(call_lua_error_is_failed_and_stack_stays_balanced)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    BreakLuaValue ret;
    ASSERT_NOT_NULL(rt);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "b", kChunkBoom,
                                            chunk_len(kChunkBoom)),
              BREAK_LUA_OK);
    memset(&ret, 0xFF, sizeof(ret));
    ASSERT_EQ(break_lua_runtime_call(rt, "b", "boom", NULL, 0u, &ret, 1u),
              BREAK_LUA_FAILED);
    ASSERT_EQ(ret.type, BREAK_LUA_VALUE_NIL);
    assert_stack_balanced(rt);

    /* The module keeps serving after a failed call. */
    ASSERT_EQ(break_lua_runtime_load_module(rt, "e", kChunkEcho,
                                            chunk_len(kChunkEcho)),
              BREAK_LUA_OK);
    {
        BreakLuaValue arg = value_string("alive");
        ASSERT_EQ(break_lua_runtime_call(rt, "e", "echo", &arg, 1u, &ret, 1u),
                  BREAK_LUA_OK);
        ASSERT_STR_EQ(ret.as.s.data, "alive");
    }
    assert_stack_balanced(rt);
    break_lua_runtime_destroy(rt);
}

TEST(call_at_max_values_boundary_round_trip)
{
    /* Exactly-at-cap calls (default max_values 64) push 64 args and read 64
     * results — far past the Lua state's initial stack capacity, pinning the
     * checked-stack reservation in the call path. */
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    BreakLuaValue args[BREAK_LUA_MAX_VALUES];
    BreakLuaValue rets[BREAK_LUA_MAX_VALUES];
    usize i;
    ASSERT_NOT_NULL(rt);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "w", kChunkWide,
                                            chunk_len(kChunkWide)),
              BREAK_LUA_OK);

    memset(args, 0, sizeof(args)); /* 64 NIL args */
    ASSERT_EQ(break_lua_runtime_call(rt, "w", "count_args", args,
                                     BREAK_LUA_MAX_VALUES, rets, 1u),
              BREAK_LUA_OK);
    ASSERT_EQ(rets[0].type, BREAK_LUA_VALUE_NUMBER);
    ASSERT_FLOAT_EQ(rets[0].as.n, 64.0, 1e-12);

    for (i = 0u; i < BREAK_LUA_MAX_VALUES; i++) {
        args[i] = value_number((f64)i);
    }
    ASSERT_EQ(break_lua_runtime_call(rt, "w", "many", args, 0u, rets,
                                     BREAK_LUA_MAX_VALUES),
              BREAK_LUA_OK);
    for (i = 0u; i < BREAK_LUA_MAX_VALUES; i++) {
        ASSERT_EQ(rets[i].type, BREAK_LUA_VALUE_NUMBER);
        ASSERT_FLOAT_EQ(rets[i].as.n, (f64)(i + 1u), 1e-12);
    }

    assert_stack_balanced(rt);
    break_lua_runtime_destroy(rt);
}

TEST(call_unknown_module_is_stale)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    BreakLuaValue ret;
    ASSERT_NOT_NULL(rt);

    /* Consistent with reload: a name that names no live module is STALE. */
    ASSERT_EQ(break_lua_runtime_call(rt, "ghost", "f", NULL, 0u, &ret, 1u),
              BREAK_LUA_STALE);
    ASSERT_EQ(break_lua_runtime_call(rt, "ghost", "f", NULL, 0u, NULL, 0u),
              BREAK_LUA_STALE);

    assert_stack_balanced(rt);
    break_lua_runtime_destroy(rt);
}

TEST(call_unknown_or_non_function_field_is_invalid)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    ASSERT_NOT_NULL(rt);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "f", kChunkFields,
                                            chunk_len(kChunkFields)),
              BREAK_LUA_OK);

    /* No such field in the module environment. */
    ASSERT_EQ(break_lua_runtime_call(rt, "f", "ghost", NULL, 0u, NULL, 0u),
              BREAK_LUA_INVALID);
    /* The field exists but is a number, not a function. */
    ASSERT_EQ(break_lua_runtime_call(rt, "f", "marker", NULL, 0u, NULL, 0u),
              BREAK_LUA_INVALID);
    /* Only chunk-defined fields are callable: stdlib globals reachable via
     * the environment metatable (e.g. tostring) do NOT resolve. */
    ASSERT_EQ(break_lua_runtime_call(rt, "f", "tostring", NULL, 0u, NULL, 0u),
              BREAK_LUA_INVALID);

    assert_stack_balanced(rt);
    break_lua_runtime_destroy(rt);
}

TEST(call_value_counts_over_max_values_are_overload)
{
    BreakLuaRuntimeConfig cfg;
    BreakLuaRuntime *rt;
    BreakLuaValue vals[5];
    BreakLuaValue rets[5];

    memset(&cfg, 0, sizeof(cfg));
    cfg.max_values = 4u;
    rt = break_lua_runtime_create(&cfg);
    ASSERT_NOT_NULL(rt);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "t", kChunkThree,
                                            chunk_len(kChunkThree)),
              BREAK_LUA_OK);

    memset(vals, 0, sizeof(vals));
    memset(rets, 0, sizeof(rets));
    /* arg_count above the configured per-call cap. */
    ASSERT_EQ(break_lua_runtime_call(rt, "t", "three", vals, 5u, NULL, 0u),
              BREAK_LUA_OVERLOAD);
    /* return_capacity above the cap. */
    ASSERT_EQ(break_lua_runtime_call(rt, "t", "three", NULL, 0u, rets, 5u),
              BREAK_LUA_OVERLOAD);
    /* Exactly at the cap is admitted. */
    ASSERT_EQ(break_lua_runtime_call(rt, "t", "three", NULL, 0u, rets, 4u),
              BREAK_LUA_OK);
    ASSERT_EQ(rets[0].type, BREAK_LUA_VALUE_NUMBER);

    assert_stack_balanced(rt);
    break_lua_runtime_destroy(rt);
}

TEST(call_invalid_args)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    BreakLuaValue arg = value_string("x");
    BreakLuaValue ret;
    char long_name[BREAK_LUA_MAX_MODULE_NAME_BYTES + 1u];
    usize i;
    ASSERT_NOT_NULL(rt);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "e", kChunkEcho,
                                            chunk_len(kChunkEcho)),
              BREAK_LUA_OK);

    for (i = 0u; i < BREAK_LUA_MAX_MODULE_NAME_BYTES; i++) {
        long_name[i] = 'n';
    }
    long_name[BREAK_LUA_MAX_MODULE_NAME_BYTES] = '\0';

    ASSERT_EQ(break_lua_runtime_call(NULL, "e", "echo", &arg, 1u, &ret, 1u),
              BREAK_LUA_INVALID);
    ASSERT_EQ(break_lua_runtime_call(rt, NULL, "echo", &arg, 1u, &ret, 1u),
              BREAK_LUA_INVALID);
    ASSERT_EQ(break_lua_runtime_call(rt, "", "echo", &arg, 1u, &ret, 1u),
              BREAK_LUA_INVALID);
    ASSERT_EQ(break_lua_runtime_call(rt, long_name, "echo", &arg, 1u, &ret, 1u),
              BREAK_LUA_INVALID);
    ASSERT_EQ(break_lua_runtime_call(rt, "e", NULL, &arg, 1u, &ret, 1u),
              BREAK_LUA_INVALID);
    ASSERT_EQ(break_lua_runtime_call(rt, "e", "", &arg, 1u, &ret, 1u),
              BREAK_LUA_INVALID);
    ASSERT_EQ(break_lua_runtime_call(rt, "e", long_name, &arg, 1u, &ret, 1u),
              BREAK_LUA_INVALID);
    /* NULL args with arg_count > 0 and NULL returns with capacity > 0 are
     * malformed. */
    ASSERT_EQ(break_lua_runtime_call(rt, "e", "echo", NULL, 1u, &ret, 1u),
              BREAK_LUA_INVALID);
    ASSERT_EQ(break_lua_runtime_call(rt, "e", "echo", &arg, 1u, NULL, 1u),
              BREAK_LUA_INVALID);

    /* Malformed calls never touch the Lua stack. */
    assert_stack_balanced(rt);
    break_lua_runtime_destroy(rt);
}

static BreakLuaRuntime *g_probe_rt;
static BreakLuaError g_probe_call_result;

static PLATFORM_THREAD_RET call_probe_worker(PLATFORM_THREAD_ARG arg)
{
    (void)arg;
    g_probe_call_result =
        break_lua_runtime_call(g_probe_rt, "e", "echo", NULL, 0u, NULL, 0u);
    return PLATFORM_THREAD_RETURN;
}

TEST(call_rejects_non_owner_thread)
{
    PlatformThread t;
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    ASSERT_NOT_NULL(rt);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "e", kChunkEcho,
                                            chunk_len(kChunkEcho)),
              BREAK_LUA_OK);

    g_probe_rt = rt;
    g_probe_call_result = BREAK_LUA_OK;
    ASSERT_TRUE(platform_thread_create(&t, call_probe_worker, NULL));
    platform_thread_join(t);
    ASSERT_EQ(g_probe_call_result, BREAK_LUA_REJECTED);

    break_lua_runtime_destroy(rt);
    g_probe_rt = NULL;
}

TEST(frame_hooks_receive_dt_and_run_per_module)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    double v = 0.0;
    ASSERT_NOT_NULL(rt);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "a", kChunkHooks,
                                            chunk_len(kChunkHooks)),
              BREAK_LUA_OK);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "b", kChunkHooks,
                                            chunk_len(kChunkHooks)),
              BREAK_LUA_OK);
    /* A module without hooks is simply skipped, not an error. */
    ASSERT_EQ(break_lua_runtime_load_module(rt, "c", kChunkNoHooks,
                                            chunk_len(kChunkNoHooks)),
              BREAK_LUA_OK);

    break_lua_runtime_begin_frame(rt, 0.25);
    break_lua_runtime_end_frame(rt);
    break_lua_runtime_begin_frame(rt, 0.25);
    break_lua_runtime_end_frame(rt);

    ASSERT_TRUE(break_lua_test_module_state_number(rt, "a", "begin_count", &v));
    ASSERT_FLOAT_EQ(v, 2.0, 1e-12);
    ASSERT_TRUE(break_lua_test_module_state_number(rt, "a", "dt_sum", &v));
    ASSERT_FLOAT_EQ(v, 0.5, 1e-12);
    ASSERT_TRUE(break_lua_test_module_state_number(rt, "a", "end_count", &v));
    ASSERT_FLOAT_EQ(v, 2.0, 1e-12);
    /* Per-module state: b accumulated independently. */
    ASSERT_TRUE(break_lua_test_module_state_number(rt, "b", "begin_count", &v));
    ASSERT_FLOAT_EQ(v, 2.0, 1e-12);

    /* No hook errors were recorded. */
    {
        BreakLuaTestFrameError fe = break_lua_test_last_frame_error(rt);
        ASSERT_FALSE(fe.valid);
        ASSERT_EQ(fe.total, UINT64_C(0));
    }

    assert_stack_balanced(rt);
    break_lua_runtime_destroy(rt);
}

TEST(frame_hook_error_is_recorded_and_other_modules_continue)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    double v = 0.0;
    BreakLuaTestFrameError fe;
    ASSERT_NOT_NULL(rt);
    /* Registration order puts the failing module first on purpose. */
    ASSERT_EQ(break_lua_runtime_load_module(rt, "bad", kChunkHookBoom,
                                            chunk_len(kChunkHookBoom)),
              BREAK_LUA_OK);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "good", kChunkHooks,
                                            chunk_len(kChunkHooks)),
              BREAK_LUA_OK);

    break_lua_runtime_begin_frame(rt, 0.5);
    break_lua_runtime_end_frame(rt);

    /* The good module still ran both hooks. */
    ASSERT_TRUE(break_lua_test_module_state_number(rt, "good", "begin_count", &v));
    ASSERT_FLOAT_EQ(v, 1.0, 1e-12);
    ASSERT_TRUE(break_lua_test_module_state_number(rt, "good", "end_count", &v));
    ASSERT_FLOAT_EQ(v, 1.0, 1e-12);

    /* Bounded error record: module, hook, truncated message, sequence. */
    fe = break_lua_test_last_frame_error(rt);
    ASSERT_TRUE(fe.valid);
    ASSERT_EQ(fe.total, UINT64_C(1));
    ASSERT_EQ(fe.frame_seq, UINT64_C(1));
    ASSERT_FALSE(fe.budget);
    ASSERT_FALSE(fe.dispatch_failure);
    ASSERT_STR_EQ(fe.module, "bad");
    ASSERT_STR_EQ(fe.hook, "on_frame_begin");
    ASSERT_TRUE(strstr(fe.message, "begin boom") != NULL);

    /* An ordinary hook error does NOT disable the module: it runs (and
     * fails) again next frame, bumping the lifetime counter. */
    break_lua_runtime_begin_frame(rt, 0.5);
    fe = break_lua_test_last_frame_error(rt);
    ASSERT_EQ(fe.total, UINT64_C(2));
    ASSERT_EQ(fe.frame_seq, UINT64_C(2));
    ASSERT_FALSE(break_lua_test_module_hooks_disabled(rt, "bad"));
    ASSERT_TRUE(break_lua_test_module_state_number(rt, "good", "begin_count", &v));
    ASSERT_FLOAT_EQ(v, 2.0, 1e-12);

    assert_stack_balanced(rt);
    break_lua_runtime_destroy(rt);
}

TEST(frame_error_message_is_truncated_to_bounds)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    BreakLuaTestFrameError fe;
    ASSERT_NOT_NULL(rt);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "chatty", kChunkHookLongErr,
                                            chunk_len(kChunkHookLongErr)),
              BREAK_LUA_OK);

    break_lua_runtime_begin_frame(rt, 0.0);

    fe = break_lua_test_last_frame_error(rt);
    ASSERT_TRUE(fe.valid);
    ASSERT_EQ(fe.total, UINT64_C(1));
    /* The 300-byte error text is truncated into the bounded record. */
    ASSERT_EQ(strlen(fe.message), 127u);
    ASSERT_EQ(fe.message[127], '\0');

    assert_stack_balanced(rt);
    break_lua_runtime_destroy(rt);
}

static PLATFORM_THREAD_RET frame_begin_probe_worker(PLATFORM_THREAD_ARG arg)
{
    (void)arg;
    break_lua_runtime_begin_frame(g_probe_rt, 0.1);
    return PLATFORM_THREAD_RETURN;
}

TEST(frame_dispatch_rejects_non_owner_thread_with_abort)
{
#if !defined(_WIN32)
    pid_t pid = fork();
    if (pid == 0) {
        /* begin_frame/end_frame return void: a non-owner call is a contract
         * violation that fail-stops in test builds (destroy precedent). */
        BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
        PlatformThread t;
        if (!rt) {
            _exit(2);
        }
        g_probe_rt = rt;
        if (platform_thread_create(&t, frame_begin_probe_worker, NULL)) {
            platform_thread_join(t);
        }
        _exit(0); /* reached only when the violation was NOT fail-stopped */
    }
    ASSERT_TRUE(pid > 0);
    {
        int status = 0;
        ASSERT_EQ(waitpid(pid, &status, 0), pid);
        ASSERT_TRUE(WIFSIGNALED(status));
    }
    /* Parent-side normal usage is unaffected. */
    {
        BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
        ASSERT_NOT_NULL(rt);
        break_lua_runtime_begin_frame(rt, 0.1);
        break_lua_runtime_end_frame(rt);
        break_lua_runtime_destroy(rt);
    }
#endif
}

TEST(frame_snapshot_with_many_modules_reserves_stack)
{
    /* 48 occupied modules pin 48 environments on the Lua stack at dispatch
     * start — past the state's initial 40-slot capacity — pinning the
     * checked-stack reservation in the snapshot path. */
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    char names[48][8];
    int k;
    double v = 0.0;
    ASSERT_NOT_NULL(rt);
    for (k = 0; k < 48; k++) {
        snprintf(names[k], sizeof(names[k]), "m%d", k);
        ASSERT_EQ(break_lua_runtime_load_module(rt, names[k], kChunkHooks,
                                                chunk_len(kChunkHooks)),
                  BREAK_LUA_OK);
    }
    break_lua_runtime_begin_frame(rt, 0.5);
    break_lua_runtime_end_frame(rt);
    for (k = 0; k < 48; k++) {
        ASSERT_TRUE(break_lua_test_module_state_number(rt, names[k],
                                                       "begin_count", &v));
        ASSERT_FLOAT_EQ(v, 1.0, 1e-12);
        ASSERT_TRUE(break_lua_test_module_state_number(rt, names[k],
                                                       "end_count", &v));
        ASSERT_FLOAT_EQ(v, 1.0, 1e-12);
    }
    {
        BreakLuaTestFrameError fe = break_lua_test_last_frame_error(rt);
        ASSERT_FALSE(fe.valid);
    }
    assert_stack_balanced(rt);
    break_lua_runtime_destroy(rt);
}

TEST(frame_reload_between_dispatches_serves_new_environment)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    double v = 0.0;
    ASSERT_NOT_NULL(rt);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "m", kChunkFrameV1,
                                            chunk_len(kChunkFrameV1)),
              BREAK_LUA_OK);

    break_lua_runtime_begin_frame(rt, 0.1);
    ASSERT_TRUE(break_lua_test_module_state_number(rt, "m", "begin_marker", &v));
    ASSERT_FLOAT_EQ(v, 1.0, 1e-12);

    /* Reload between the begin and end dispatches: each dispatch snapshots
     * independently, so end_frame serves the committed v2 environment. */
    ASSERT_EQ(break_lua_runtime_reload_module(rt, "m", kChunkFrameV2,
                                              chunk_len(kChunkFrameV2), NULL),
              BREAK_LUA_OK);
    break_lua_runtime_end_frame(rt);
    ASSERT_TRUE(break_lua_test_module_state_number(rt, "m", "end_marker", &v));
    ASSERT_FLOAT_EQ(v, 2.0, 1e-12);

    break_lua_runtime_begin_frame(rt, 0.1);
    ASSERT_TRUE(break_lua_test_module_state_number(rt, "m", "begin_marker", &v));
    ASSERT_FLOAT_EQ(v, 2.0, 1e-12);

    assert_stack_balanced(rt);
    break_lua_runtime_destroy(rt);
}

TEST(frame_mid_dispatch_reload_serves_pinned_old_environment)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    double v = 0.0;
    ASSERT_NOT_NULL(rt);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "a", kChunkReloaderA,
                                            chunk_len(kChunkReloaderA)),
              BREAK_LUA_OK);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "b", kChunkBV1,
                                            chunk_len(kChunkBV1)),
              BREAK_LUA_OK);
    /* Test-only binding: a's hook reloads b mid-dispatch (simulating the
     * Task 4 script-triggered reload path). */
    ASSERT_EQ(break_lua_test_install_reloader(rt, "a", "b", kChunkBV2,
                                              chunk_len(kChunkBV2)),
              BREAK_LUA_OK);

    /* Frame 1: a fires the reload; b was snapshotted with its v1 env, and
     * the pin keeps that env alive, so v1's hook still runs this frame. */
    break_lua_runtime_begin_frame(rt, 0.1);
    ASSERT_TRUE(break_lua_test_module_state_number(rt, "b", "seen_marker", &v));
    ASSERT_FLOAT_EQ(v, 1.0, 1e-12);
    {
        BreakLuaTestModuleStat st = break_lua_test_module_stat(rt, "b");
        ASSERT_TRUE(st.loaded);
        ASSERT_EQ(st.version, 2u); /* the reload did commit mid-frame */
    }

    /* Frame 2: a fresh snapshot serves b's v2 environment. */
    break_lua_runtime_begin_frame(rt, 0.1);
    ASSERT_TRUE(break_lua_test_module_state_number(rt, "b", "seen_marker", &v));
    ASSERT_FLOAT_EQ(v, 2.0, 1e-12);

    assert_stack_balanced(rt);
    break_lua_runtime_destroy(rt);
}

TEST(instruction_budget_trip_marks_module_until_reload)
{
    BreakLuaRuntimeConfig cfg;
    BreakLuaRuntime *rt;
    BreakLuaTestFrameError fe;
    double v = 0.0;

    memset(&cfg, 0, sizeof(cfg));
    cfg.instruction_budget = 200u;
    rt = break_lua_runtime_create(&cfg);
    ASSERT_NOT_NULL(rt);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "spin", kChunkSpin,
                                            chunk_len(kChunkSpin)),
              BREAK_LUA_OK);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "good", kChunkHooks,
                                            chunk_len(kChunkHooks)),
              BREAK_LUA_OK);

    /* Frame 1: spin's hook blows the budget; the abort is a bounded error
     * record and the other module still runs. */
    break_lua_runtime_begin_frame(rt, 0.1);
    fe = break_lua_test_last_frame_error(rt);
    ASSERT_TRUE(fe.valid);
    ASSERT_TRUE(fe.budget);
    ASSERT_FALSE(fe.dispatch_failure);
    ASSERT_STR_EQ(fe.module, "spin");
    ASSERT_STR_EQ(fe.hook, "on_frame_begin");
    ASSERT_TRUE(strstr(fe.message, "instruction budget exceeded") != NULL);
    ASSERT_TRUE(break_lua_test_module_hooks_disabled(rt, "spin"));
    ASSERT_TRUE(break_lua_test_module_state_number(rt, "good", "begin_count", &v));
    ASSERT_FLOAT_EQ(v, 1.0, 1e-12);
    /* The spin hook aborted before completing its state write. */
    ASSERT_FALSE(break_lua_test_module_state_number(rt, "spin", "spun", &v));

    /* Frame 2: the tripped module's hooks are skipped (sticky mark), the
     * healthy module keeps running. */
    break_lua_runtime_begin_frame(rt, 0.1);
    ASSERT_FALSE(break_lua_test_module_state_number(rt, "spin", "spun", &v));
    ASSERT_TRUE(break_lua_test_module_state_number(rt, "good", "begin_count", &v));
    ASSERT_FLOAT_EQ(v, 2.0, 1e-12);
    ASSERT_TRUE(break_lua_test_module_hooks_disabled(rt, "spin"));

    /* A committed reload clears the mark: the new version serves again. */
    ASSERT_EQ(break_lua_runtime_reload_module(rt, "spin", kChunkSpinFast,
                                              chunk_len(kChunkSpinFast), NULL),
              BREAK_LUA_OK);
    ASSERT_FALSE(break_lua_test_module_hooks_disabled(rt, "spin"));
    break_lua_runtime_begin_frame(rt, 0.1);
    ASSERT_TRUE(break_lua_test_module_state_number(rt, "spin", "spun", &v));
    ASSERT_FLOAT_EQ(v, 1.0, 1e-12);

    assert_stack_balanced(rt);
    break_lua_runtime_destroy(rt);
}

TEST(instruction_budget_is_per_hook_invocation_not_cumulative)
{
    BreakLuaRuntimeConfig cfg;
    BreakLuaRuntime *rt;
    double v = 0.0;

    memset(&cfg, 0, sizeof(cfg));
    /* Each module's hook burns ~8-9k VM instructions (2000-iteration loop);
     * the cumulative frame burn (~18k) exceeds the 15k budget, so a
     * cumulative accounting would trip the second module. Per-invocation
     * accounting lets both run. */
    cfg.instruction_budget = 15000u;
    rt = break_lua_runtime_create(&cfg);
    ASSERT_NOT_NULL(rt);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "l1", kChunkLoop,
                                            chunk_len(kChunkLoop)),
              BREAK_LUA_OK);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "l2", kChunkLoop,
                                            chunk_len(kChunkLoop)),
              BREAK_LUA_OK);

    break_lua_runtime_begin_frame(rt, 0.1);
    ASSERT_TRUE(break_lua_test_module_state_number(rt, "l1", "looped", &v));
    ASSERT_FLOAT_EQ(v, 1.0, 1e-12);
    ASSERT_TRUE(break_lua_test_module_state_number(rt, "l2", "looped", &v));
    ASSERT_FLOAT_EQ(v, 1.0, 1e-12);
    {
        BreakLuaTestFrameError fe = break_lua_test_last_frame_error(rt);
        ASSERT_FALSE(fe.valid);
    }

    break_lua_runtime_destroy(rt);
}

TEST(instruction_budget_disabled_by_default_runs_long_hook)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    double v = 0.0;
    ASSERT_NOT_NULL(rt);
    /* Default config has instruction_budget 0 (disabled): a hook burning
     * ~8-9k VM instructions runs to completion — no phantom budget. */
    ASSERT_EQ(break_lua_runtime_load_module(rt, "spin", kChunkLoop,
                                            chunk_len(kChunkLoop)),
              BREAK_LUA_OK);
    break_lua_runtime_begin_frame(rt, 0.1);
    ASSERT_TRUE(break_lua_test_module_state_number(rt, "spin", "looped", &v));
    ASSERT_FLOAT_EQ(v, 1.0, 1e-12);
    ASSERT_FALSE(break_lua_test_module_hooks_disabled(rt, "spin"));
    break_lua_runtime_destroy(rt);
}

TEST(frame_end_without_begin_is_an_independent_dispatch)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    double v = 0.0;
    ASSERT_NOT_NULL(rt);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "a", kChunkHooks,
                                            chunk_len(kChunkHooks)),
              BREAK_LUA_OK);
    /* Pairing is the host's responsibility; end_frame alone still dispatches
     * on_frame_end. */
    break_lua_runtime_end_frame(rt);
    ASSERT_TRUE(break_lua_test_module_state_number(rt, "a", "end_count", &v));
    ASSERT_FLOAT_EQ(v, 1.0, 1e-12);
    ASSERT_FALSE(break_lua_test_module_state_number(rt, "a", "begin_count", &v));
    break_lua_runtime_destroy(rt);
}

TEST(oom_injection_on_call_and_frame_is_bounded)
{
    BreakLuaRuntime *rt = break_lua_runtime_create(NULL);
    BreakLuaValue arg = value_string("probe");
    BreakLuaValue ret;
    BreakLuaError err;
    u64 budget;
    double v = 0.0;
    ASSERT_NOT_NULL(rt);
    break_lua_test_set_alloc_budget(BREAK_LUA_TEST_ALLOC_DISABLED);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "e", kChunkEcho,
                                            chunk_len(kChunkEcho)),
              BREAK_LUA_OK);
    ASSERT_EQ(break_lua_runtime_load_module(rt, "a", kChunkHooks,
                                            chunk_len(kChunkHooks)),
              BREAK_LUA_OK);

    /* Small budgets must fail the call with OOM, never crash or corrupt.
     * Only budget 0 is pinned exactly: with a slightly larger budget the
     * bounded pushes may succeed (short strings can already be interned),
     * which the doubling probe below covers. */
    break_lua_test_set_alloc_budget(0u);
    err = break_lua_runtime_call(rt, "e", "echo", &arg, 1u, &ret, 1u);
    ASSERT_EQ(err, BREAK_LUA_OOM);
    assert_stack_balanced(rt);

    /* Doubling probe: every failure is a bounded OOM, and enough budget
     * succeeds again — the module is intact throughout. */
    budget = 1u;
    for (;;) {
        break_lua_test_set_alloc_budget(budget);
        err = break_lua_runtime_call(rt, "e", "echo", &arg, 1u, &ret, 1u);
        if (err == BREAK_LUA_OK) {
            ASSERT_STR_EQ(ret.as.s.data, "probe");
            break;
        }
        ASSERT_EQ(err, BREAK_LUA_OOM);
        ASSERT_TRUE(budget <= (1u << 20));
        budget *= 2u;
    }

    /* Frame dispatch under injection: bounded failure (a dispatch-level
     * error record may be produced), stack stays balanced, no crash. */
    for (budget = 0u; budget <= 3u; budget++) {
        break_lua_test_set_alloc_budget(budget);
        break_lua_runtime_begin_frame(rt, 0.1);
        break_lua_runtime_end_frame(rt);
        assert_stack_balanced(rt);
    }
    break_lua_test_set_alloc_budget(BREAK_LUA_TEST_ALLOC_DISABLED);
    break_lua_runtime_begin_frame(rt, 0.1);
    assert_stack_balanced(rt);
    /* The hook ran once the budget was lifted (it may also have run during
     * some injected frames; only the final state matters). */
    ASSERT_TRUE(break_lua_test_module_state_number(rt, "a", "begin_count", &v));
    ASSERT_TRUE(v >= 1.0);

    break_lua_test_set_alloc_budget(BREAK_LUA_TEST_ALLOC_DISABLED);
    break_lua_runtime_destroy(rt);
}

TEST_MAIN_BEGIN()
    RUN_TEST(call_round_trips_mixed_args_and_returns);
    RUN_TEST(call_return_nil_padding_and_extra_discard);
    RUN_TEST(call_zero_return_capacity_needs_no_buffer);
    RUN_TEST(call_string_round_trip_and_nul_termination);
    RUN_TEST(call_string_arg_over_capacity_is_bounded_overload);
    RUN_TEST(call_return_string_over_capacity_is_bounded_overload);
    RUN_TEST(call_unrepresentable_return_is_failed);
    RUN_TEST(call_lua_error_is_failed_and_stack_stays_balanced);
    RUN_TEST(call_unknown_module_is_stale);
    RUN_TEST(call_unknown_or_non_function_field_is_invalid);
    RUN_TEST(call_value_counts_over_max_values_are_overload);
    RUN_TEST(call_at_max_values_boundary_round_trip);
    RUN_TEST(call_invalid_args);
    RUN_TEST(call_rejects_non_owner_thread);
    RUN_TEST(frame_hooks_receive_dt_and_run_per_module);
    RUN_TEST(frame_hook_error_is_recorded_and_other_modules_continue);
    RUN_TEST(frame_error_message_is_truncated_to_bounds);
    RUN_TEST(frame_dispatch_rejects_non_owner_thread_with_abort);
    RUN_TEST(frame_snapshot_with_many_modules_reserves_stack);
    RUN_TEST(frame_reload_between_dispatches_serves_new_environment);
    RUN_TEST(frame_mid_dispatch_reload_serves_pinned_old_environment);
    RUN_TEST(instruction_budget_trip_marks_module_until_reload);
    RUN_TEST(instruction_budget_is_per_hook_invocation_not_cumulative);
    RUN_TEST(instruction_budget_disabled_by_default_runs_long_hook);
    RUN_TEST(frame_end_without_begin_is_an_independent_dispatch);
    RUN_TEST(oom_injection_on_call_and_frame_is_bounded);
TEST_MAIN_END()
