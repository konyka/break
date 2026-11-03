#include "test_framework.h"
#include <script/break_lua_debug.h>

#include <string.h>

static const char kChunk[] =
    "function inner(value)\n"
    "    local doubled = value * 2\n"
    "    return doubled\n"
    "end\n"
    "function outer(value)\n"
    "    local offset = 3\n"
    "    local result = inner(value)\n"
    "    return result + offset\n"
    "end\n"
    "function sandbox_closed()\n"
    "    return debug == nil and package == nil and require == nil and coroutine == nil and load == nil\n"
    "end\n"
    "function spin()\n"
    "    for i = 1, 1000000 do end\n"
    "end\n";

typedef struct DebugProbe {
    u32 hits;
    u32 breakpoint_hits;
    u32 step_hits;
    u32 depths[8];
    u32 lines[8];
    BreakLuaDebugStep action;
    bool inspect;
    BreakLuaError stack_error;
    BreakLuaError stack_small_error;
    BreakLuaError locals_error;
    BreakLuaError locals_small_error;
    usize stack_count;
    usize locals_count;
    char top_function[64];
    u32 caller_defined_line;
    double local_value;
    bool found_local;
} DebugProbe;

static BreakLuaDebugStep pause_callback(BreakLuaDebug *debug,
                                        const BreakLuaDebugPause *pause,
                                        void *user)
{
    DebugProbe *probe = (DebugProbe *)user;
    BreakLuaDebugFrame frames[BREAK_LUA_DEBUG_MAX_FRAMES];
    usize count = 0u;
    u32 index = probe->hits++;
    (void)pause;
    if (index < 8u) {
        probe->lines[index] = pause->line;
        probe->stack_error = break_lua_debug_stack(
            debug, frames, BREAK_LUA_DEBUG_MAX_FRAMES, &count);
        probe->depths[index] = probe->stack_error == BREAK_LUA_OK ? (u32)count : 0u;
    }
    if (pause->reason == BREAK_LUA_DEBUG_PAUSE_STEP) {
        probe->step_hits++;
        return BREAK_LUA_DEBUG_STEP_NONE;
    }
    probe->breakpoint_hits++;
    if (probe->inspect) {
        BreakLuaDebugLocal locals[16];
        usize i;
        probe->stack_count = count;
        if (count >= 2u) {
            memcpy(probe->top_function, frames[0].function,
                   sizeof(probe->top_function));
            probe->caller_defined_line = frames[1].defined_line;
        }
        probe->stack_small_error = break_lua_debug_stack(debug, NULL, 0u, &count);
        probe->locals_error = break_lua_debug_locals(debug, 0u, locals, 16u,
                                                      &probe->locals_count);
        probe->locals_small_error = break_lua_debug_locals(debug, 0u, NULL, 0u,
                                                            &count);
        if (probe->locals_error == BREAK_LUA_OK) {
            for (i = 0u; i < probe->locals_count; i++) {
                if (strcmp(locals[i].name, "value") == 0 &&
                    locals[i].value.type == BREAK_LUA_DEBUG_VALUE_NUMBER) {
                    probe->local_value = locals[i].value.as.n;
                    probe->found_local = true;
                }
            }
        }
    }
    return probe->action;
}

static BreakLuaValue number_value(double number)
{
    BreakLuaValue value;
    memset(&value, 0, sizeof(value));
    value.type = BREAK_LUA_VALUE_NUMBER;
    value.as.n = number;
    return value;
}

static BreakLuaError call_outer(BreakLuaRuntime *runtime, BreakLuaValue *result)
{
    BreakLuaValue argument = number_value(5.0);
    return break_lua_runtime_call(runtime, "debuggee", "outer", &argument, 1u,
                                  result, 1u);
}

static BreakLuaRuntime *make_runtime(u64 budget)
{
    BreakLuaRuntimeConfig config;
    BreakLuaRuntime *runtime;
    memset(&config, 0, sizeof(config));
    config.instruction_budget = budget;
    runtime = break_lua_runtime_create(&config);
    if (runtime) {
        if (break_lua_runtime_load_module(runtime, "debuggee", kChunk,
                                          strlen(kChunk)) != BREAK_LUA_OK) {
            break_lua_runtime_destroy(runtime);
            return NULL;
        }
    }
    return runtime;
}

TEST(debug_is_default_off_then_breakpoint_exposes_stack_and_locals)
{
    BreakLuaRuntime *runtime = make_runtime(0u);
    BreakLuaDebug *debug;
    DebugProbe probe;
    BreakLuaValue result;
    BreakLuaDebugFrame frame;
    BreakLuaDebugLocal local;
    usize count = 0u;
    u32 id = 0u;
    ASSERT_NOT_NULL(runtime);
    memset(&probe, 0, sizeof(probe));
    probe.inspect = true;
    debug = break_lua_debug_create(runtime, pause_callback, &probe);
    ASSERT_NOT_NULL(debug);
    ASSERT_EQ(break_lua_debug_breakpoint_set(debug, "debuggee", 2u, &id),
              BREAK_LUA_OK);
    ASSERT_EQ(call_outer(runtime, &result), BREAK_LUA_OK);
    ASSERT_EQ(probe.hits, 0u);
    ASSERT_EQ(break_lua_debug_set_enabled(debug, true), BREAK_LUA_OK);
    ASSERT_EQ(call_outer(runtime, &result), BREAK_LUA_OK);
    ASSERT_FLOAT_EQ(result.as.n, 13.0, 1e-12);
    ASSERT_EQ(probe.breakpoint_hits, 1u);
    ASSERT_EQ(probe.lines[0], 2u);
    ASSERT_EQ(probe.stack_error, BREAK_LUA_OK);
    ASSERT_TRUE(probe.stack_count >= 2u);
    ASSERT_STR_EQ(probe.top_function, "inner");
    ASSERT_EQ(probe.caller_defined_line, 5u);
    ASSERT_EQ(probe.locals_error, BREAK_LUA_OK);
    ASSERT_TRUE(probe.found_local);
    ASSERT_FLOAT_EQ(probe.local_value, 5.0, 1e-12);
    ASSERT_EQ(probe.stack_small_error, BREAK_LUA_OVERLOAD);
    ASSERT_EQ(probe.locals_small_error, BREAK_LUA_OVERLOAD);
    ASSERT_EQ(break_lua_debug_stack(debug, &frame, 1u, &count),
              BREAK_LUA_REJECTED);
    ASSERT_EQ(break_lua_debug_locals(debug, 0u, &local, 1u, &count),
              BREAK_LUA_REJECTED);

    ASSERT_EQ(break_lua_debug_breakpoint_clear(debug, id), BREAK_LUA_OK);
    ASSERT_EQ(break_lua_debug_breakpoint_clear(debug, id), BREAK_LUA_STALE);
    ASSERT_EQ(call_outer(runtime, &result), BREAK_LUA_OK);
    ASSERT_EQ(probe.hits, 1u);
    break_lua_debug_destroy(debug);
    break_lua_runtime_destroy(runtime);
}

static void run_step_case(BreakLuaDebugStep action, u32 expected_second_depth,
                          bool second_depth_exact)
{
    BreakLuaRuntime *runtime = make_runtime(0u);
    BreakLuaDebug *debug;
    DebugProbe probe;
    BreakLuaValue result;
    u32 id = 0u;
    ASSERT_NOT_NULL(runtime);
    memset(&probe, 0, sizeof(probe));
    probe.action = action;
    debug = break_lua_debug_create(runtime, pause_callback, &probe);
    ASSERT_NOT_NULL(debug);
    ASSERT_EQ(break_lua_debug_breakpoint_set(debug, "debuggee", 2u, &id),
              BREAK_LUA_OK);
    ASSERT_EQ(break_lua_debug_set_enabled(debug, true), BREAK_LUA_OK);
    ASSERT_EQ(call_outer(runtime, &result), BREAK_LUA_OK);
    ASSERT_EQ(probe.breakpoint_hits, 1u);
    ASSERT_EQ(probe.step_hits, 1u);
    ASSERT_EQ(probe.hits, 2u);
    if (second_depth_exact) {
        ASSERT_EQ(probe.depths[1], expected_second_depth);
    } else if (action == BREAK_LUA_DEBUG_STEP_OVER) {
        ASSERT_TRUE(probe.depths[1] <= probe.depths[0]);
    } else if (action == BREAK_LUA_DEBUG_STEP_OUT) {
        ASSERT_TRUE(probe.depths[1] < probe.depths[0]);
    }
    break_lua_debug_destroy(debug);
    break_lua_runtime_destroy(runtime);
}

TEST(debug_step_into_pauses_on_next_line)
{
    run_step_case(BREAK_LUA_DEBUG_STEP_INTO, 0u, false);
}

TEST(debug_step_over_does_not_enter_a_deeper_frame)
{
    run_step_case(BREAK_LUA_DEBUG_STEP_OVER, 0u, false);
}

TEST(debug_step_out_pauses_in_the_caller)
{
    run_step_case(BREAK_LUA_DEBUG_STEP_OUT, 0u, false);
}

static void run_cross_call_step_case(BreakLuaDebugStep action,
                                     u32 expected_line)
{
    BreakLuaRuntime *runtime = make_runtime(0u);
    BreakLuaDebug *debug;
    DebugProbe probe;
    BreakLuaValue result;
    u32 id = 0u;
    ASSERT_NOT_NULL(runtime);
    memset(&probe, 0, sizeof(probe));
    probe.action = action;
    debug = break_lua_debug_create(runtime, pause_callback, &probe);
    ASSERT_NOT_NULL(debug);
    ASSERT_EQ(break_lua_debug_breakpoint_set(debug, "debuggee", 7u, &id),
              BREAK_LUA_OK);
    ASSERT_EQ(break_lua_debug_set_enabled(debug, true), BREAK_LUA_OK);
    ASSERT_EQ(call_outer(runtime, &result), BREAK_LUA_OK);
    ASSERT_EQ(probe.breakpoint_hits, 1u);
    ASSERT_EQ(probe.step_hits, 1u);
    ASSERT_EQ(probe.hits, 2u);
    ASSERT_EQ(probe.lines[0], 7u);
    ASSERT_EQ(probe.lines[1], expected_line);
    if (action == BREAK_LUA_DEBUG_STEP_INTO) {
        ASSERT_TRUE(probe.depths[1] > probe.depths[0]);
    } else {
        ASSERT_EQ(probe.depths[1], probe.depths[0]);
    }
    break_lua_debug_destroy(debug);
    break_lua_runtime_destroy(runtime);
}

TEST(debug_step_into_crosses_from_outer_call_into_inner)
{
    run_cross_call_step_case(BREAK_LUA_DEBUG_STEP_INTO, 2u);
}

TEST(debug_step_over_skips_inner_and_stops_at_outer_next_line)
{
    run_cross_call_step_case(BREAK_LUA_DEBUG_STEP_OVER, 8u);
}

TEST(debug_hook_preserves_budget_and_restores_line_hook)
{
    BreakLuaRuntime *runtime = make_runtime(10000u);
    BreakLuaDebug *debug;
    DebugProbe probe;
    u32 inner_id = 0u;
    BreakLuaValue result;
    ASSERT_NOT_NULL(runtime);
    memset(&probe, 0, sizeof(probe));
    debug = break_lua_debug_create(runtime, pause_callback, &probe);
    ASSERT_NOT_NULL(debug);
    ASSERT_EQ(break_lua_debug_breakpoint_set(debug, "debuggee", 2u, &inner_id),
              BREAK_LUA_OK);
    ASSERT_EQ(break_lua_debug_set_enabled(debug, true), BREAK_LUA_OK);
    ASSERT_EQ(call_outer(runtime, &result), BREAK_LUA_OK);
    ASSERT_EQ(probe.breakpoint_hits, 1u);
    ASSERT_EQ(break_lua_runtime_budget_trip_count(runtime), 0u);

    ASSERT_EQ(break_lua_runtime_call(runtime, "debuggee", "spin",
                                     NULL, 0u, NULL, 0u),
              BREAK_LUA_FAILED);
    ASSERT_EQ(probe.breakpoint_hits, 1u);
    ASSERT_EQ(break_lua_runtime_budget_trip_count(runtime), 1u);

    ASSERT_EQ(call_outer(runtime, &result), BREAK_LUA_OK);
    ASSERT_EQ(probe.breakpoint_hits, 2u);
    ASSERT_EQ(break_lua_runtime_budget_trip_count(runtime), 1u);
    break_lua_debug_destroy(debug);
    break_lua_runtime_destroy(runtime);
}

TEST(enabling_debug_does_not_open_sandbox_libraries)
{
    BreakLuaRuntime *runtime = make_runtime(0u);
    BreakLuaDebug *debug;
    DebugProbe probe;
    BreakLuaValue result;
    ASSERT_NOT_NULL(runtime);
    memset(&probe, 0, sizeof(probe));
    debug = break_lua_debug_create(runtime, pause_callback, &probe);
    ASSERT_NOT_NULL(debug);
    ASSERT_EQ(break_lua_debug_set_enabled(debug, true), BREAK_LUA_OK);
    ASSERT_EQ(break_lua_runtime_call(runtime, "debuggee", "sandbox_closed",
                                     NULL, 0u, &result, 1u),
              BREAK_LUA_OK);
    ASSERT_EQ(result.type, BREAK_LUA_VALUE_BOOL);
    ASSERT_TRUE(result.as.b);
    break_lua_debug_destroy(debug);
    break_lua_runtime_destroy(runtime);
}

TEST(debug_host_can_request_step_into_without_a_breakpoint)
{
    BreakLuaRuntime *runtime = make_runtime(0u);
    BreakLuaDebug *debug;
    DebugProbe probe;
    BreakLuaValue result;
    ASSERT_NOT_NULL(runtime);
    memset(&probe, 0, sizeof(probe));
    debug = break_lua_debug_create(runtime, pause_callback, &probe);
    ASSERT_NOT_NULL(debug);
    ASSERT_EQ(break_lua_debug_set_enabled(debug, true), BREAK_LUA_OK);
    ASSERT_EQ(break_lua_debug_step(debug, BREAK_LUA_DEBUG_STEP_INTO),
              BREAK_LUA_OK);
    ASSERT_EQ(call_outer(runtime, &result), BREAK_LUA_OK);
    ASSERT_FLOAT_EQ(result.as.n, 13.0, 1e-12);
    ASSERT_EQ(probe.hits, 1u);
    ASSERT_EQ(probe.step_hits, 1u);
    ASSERT_EQ(probe.breakpoint_hits, 0u);
    break_lua_debug_destroy(debug);
    break_lua_runtime_destroy(runtime);
}

TEST_MAIN_BEGIN()
    RUN_TEST(debug_is_default_off_then_breakpoint_exposes_stack_and_locals);
    RUN_TEST(debug_step_into_pauses_on_next_line);
    RUN_TEST(debug_step_over_does_not_enter_a_deeper_frame);
    RUN_TEST(debug_step_out_pauses_in_the_caller);
    RUN_TEST(debug_step_into_crosses_from_outer_call_into_inner);
    RUN_TEST(debug_step_over_skips_inner_and_stops_at_outer_next_line);
    RUN_TEST(debug_hook_preserves_budget_and_restores_line_hook);
    RUN_TEST(enabling_debug_does_not_open_sandbox_libraries);
    RUN_TEST(debug_host_can_request_step_into_without_a_breakpoint);
TEST_MAIN_END()
