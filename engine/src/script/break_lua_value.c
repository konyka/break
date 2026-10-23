#include <script/break_lua.h>

#include <script/break_lua_internal.h>
#include <script/break_lua_test_hooks.h>

#include <lua/lauxlib.h>

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Value marshalling, module calls, and frame lifecycle (Task 3). Full
 * contract: break_lua.h VALUES AND CALLS / FRAME LIFECYCLE sections.
 *
 * All Lua interaction runs inside the shared dispatch closure under
 * break_lua_op_run()'s lua_pcall (see break_lua_module.c): pushes, string
 * interning, and stack growth can all longjmp on LUA_ERRMEM, and the
 * wrapper turns that into a bounded BREAK_LUA_OOM with the stack unwound.
 * Per-hook lua_pcall calls nest inside that wrapper without issue.
 *
 * STACK DISCIPLINE: both impls restore lua_settop(base) on every exit they
 * control; the wrapper's pcall unwinds anything they do not. The tests
 * assert lua_gettop == 0 after calls and frame dispatches alike. */

/* Pushes one argument value. Allocation (string interning) is safe here:
 * the impl runs under the dispatch pcall. STRING values with an over-cap
 * len fail bounded (OVERLOAD) before any byte is read from data; unknown
 * tags are malformed (INVALID). */
static BreakLuaError break_lua_push_value(lua_State *L,
                                          const BreakLuaValue *value)
{
    switch (value->type) {
    case BREAK_LUA_VALUE_NIL:
        lua_pushnil(L);
        return BREAK_LUA_OK;
    case BREAK_LUA_VALUE_BOOL:
        lua_pushboolean(L, value->as.b ? 1 : 0);
        return BREAK_LUA_OK;
    case BREAK_LUA_VALUE_NUMBER:
        lua_pushnumber(L, (lua_Number)value->as.n);
        return BREAK_LUA_OK;
    case BREAK_LUA_VALUE_STRING:
        if (value->as.s.len >= BREAK_LUA_VALUE_STRING_CAPACITY) {
            return BREAK_LUA_OVERLOAD;
        }
        lua_pushlstring(L, value->as.s.data, (size_t)value->as.s.len);
        return BREAK_LUA_OK;
    default:
        return BREAK_LUA_INVALID;
    }
}

/* Marshals the Lua value at stack index `idx` into `out`. `out` is zeroed
 * first, so any failure leaves it NIL. Over-long strings are a bounded
 * OVERLOAD (no copy is attempted); types outside the value model are
 * FAILED, never silently coerced. */
static BreakLuaError break_lua_take_value(lua_State *L, int idx,
                                          BreakLuaValue *out)
{
    memset(out, 0, sizeof(*out));
    switch (lua_type(L, idx)) {
    case LUA_TNIL:
        out->type = BREAK_LUA_VALUE_NIL;
        return BREAK_LUA_OK;
    case LUA_TBOOLEAN:
        out->type = BREAK_LUA_VALUE_BOOL;
        out->as.b = lua_toboolean(L, idx) != 0;
        return BREAK_LUA_OK;
    case LUA_TNUMBER:
        out->type = BREAK_LUA_VALUE_NUMBER;
        out->as.n = (f64)lua_tonumber(L, idx);
        return BREAK_LUA_OK;
    case LUA_TSTRING: {
        size_t len = 0u;
        const char *s = lua_tolstring(L, idx, &len);
        if (len >= (size_t)BREAK_LUA_VALUE_STRING_CAPACITY) {
            return BREAK_LUA_OVERLOAD;
        }
        memcpy(out->as.s.data, s, len);
        out->as.s.data[len] = '\0';
        out->as.s.len = (u32)len;
        out->type = BREAK_LUA_VALUE_STRING;
        return BREAK_LUA_OK;
    }
    default:
        return BREAK_LUA_FAILED;
    }
}

void break_lua_call_impl(lua_State *L, BreakLuaCallOpCtx *ctx)
{
    int base = lua_gettop(L);
    usize i;
    int status;

    lua_rawgeti(L, LUA_REGISTRYINDEX, ctx->env_ref);       /* [env] */
    lua_pushstring(L, ctx->function_name);
    lua_rawget(L, -2);                                   /* [env fn?] */
    /* Raw lookup only: names that would resolve through the environment
     * metatable's _G fallback (stdlib globals) are deliberately not
     * callable through this facade. */
    if (!lua_isfunction(L, -1)) {
        ctx->hdr.status = BREAK_LUA_INVALID;
        lua_settop(L, base);
        return;
    }
    /* Raw lua_push* does NOT auto-grow the stack (api_incr_top only
     * asserts): reserve the whole arg/result shape up front. A growth
     * failure raises (stack overflow / LUA_ERRMEM) into the wrapper pcall
     * — bounded, unwound, no overflow. */
    luaL_checkstack(L, (int)(ctx->arg_count + ctx->return_capacity + 8u),
                    "break_lua call");
    for (i = 0u; i < ctx->arg_count; i++) {
        BreakLuaError push_err = break_lua_push_value(L, &ctx->args[i]);
        if (push_err != BREAK_LUA_OK) {
            ctx->hdr.status = push_err;
            lua_settop(L, base);
            return;
        }
    }
    /* Exactly return_capacity wanted results: Lua nil-pads shortfalls and
     * discards extras, so the buffer is always fully written and the stack
     * shape stays deterministic. */
    status = lua_pcall(L, (int)ctx->arg_count, (int)ctx->return_capacity, 0);
    if (status != LUA_OK) {
        ctx->hdr.status = (status == LUA_ERRMEM) ? BREAK_LUA_OOM
                                                 : BREAK_LUA_FAILED;
        lua_pop(L, 1); /* error object; no report surface on calls */
        lua_settop(L, base);
        return;
    }
    /* [env r1..rk] — result i sits at base + 2 + i. */
    for (i = 0u; i < ctx->return_capacity; i++) {
        BreakLuaError take_err =
            break_lua_take_value(L, base + 2 + (int)i, &ctx->returns[i]);
        if (take_err != BREAK_LUA_OK) {
            ctx->hdr.status = take_err;
            lua_settop(L, base);
            return;
        }
    }
    ctx->hdr.status = BREAK_LUA_OK;
    lua_settop(L, base);
}

BreakLuaError break_lua_runtime_call(BreakLuaRuntime *runtime,
                                     const char *module_name,
                                     const char *function_name,
                                     const BreakLuaValue *args,
                                     usize arg_count,
                                     BreakLuaValue *returns,
                                     usize return_capacity)
{
    BreakLuaCallOpCtx ctx;
    BreakLuaModule *m;
    BreakLuaError owner = break_lua_runtime_check_owner(runtime);
    usize name_len;
    usize fn_len;

    /* Owner check first (INVALID for NULL runtime, REJECTED cross-thread),
     * then shape checks: nothing untrusted is inspected before validation. */
    if (owner != BREAK_LUA_OK) {
        return owner;
    }
    if (!module_name) {
        return BREAK_LUA_INVALID;
    }
    name_len = break_lua_name_len(module_name,
                                  BREAK_LUA_MAX_MODULE_NAME_BYTES);
    if (name_len == 0u || name_len >= BREAK_LUA_MAX_MODULE_NAME_BYTES) {
        return BREAK_LUA_INVALID;
    }
    if (!function_name) {
        return BREAK_LUA_INVALID;
    }
    fn_len = break_lua_name_len(function_name,
                                BREAK_LUA_MAX_MODULE_NAME_BYTES);
    if (fn_len == 0u || fn_len >= BREAK_LUA_MAX_MODULE_NAME_BYTES) {
        return BREAK_LUA_INVALID;
    }
    if (arg_count > 0u && !args) {
        return BREAK_LUA_INVALID;
    }
    if (return_capacity > 0u && !returns) {
        return BREAK_LUA_INVALID;
    }
    if (arg_count > (usize)runtime->max_values ||
        return_capacity > (usize)runtime->max_values) {
        return BREAK_LUA_OVERLOAD;
    }
    m = break_lua_module_find(runtime, module_name);
    if (!m) {
        /* Same contract as reload: the name names no live module. */
        return BREAK_LUA_STALE;
    }

    /* NIL-prefill: any post-admission failure leaves the buffer fully
     * written with NIL slots (documented). */
    if (return_capacity > 0u) {
        memset(returns, 0, return_capacity * sizeof(*returns));
    }

    memset(&ctx, 0, sizeof(ctx));
    ctx.hdr.op = BREAK_LUA_OP_CALL;
    ctx.env_ref = m->env_ref;
    ctx.function_name = function_name;
    ctx.args = args;
    ctx.arg_count = arg_count;
    ctx.returns = returns;
    ctx.return_capacity = return_capacity;
    return break_lua_op_run(runtime, &ctx.hdr);
}

/* Pinned-function call (Stage 4 Phase 3): identical marshalling to
 * break_lua_call_impl, but the function is fetched by its registry pin —
 * the module environment is never consulted, so a chunk that overwrote the
 * env field between capture and call cannot substitute anything. */
void break_lua_call_ref_impl(lua_State *L, BreakLuaCallRefOpCtx *ctx)
{
    int base = lua_gettop(L);
    usize i;
    int status;

    lua_rawgeti(L, LUA_REGISTRYINDEX, ctx->lua_ref);       /* [fn] */
    luaL_checkstack(L, (int)(ctx->arg_count + ctx->return_capacity + 8u),
                    "break_lua call_ref");
    for (i = 0u; i < ctx->arg_count; i++) {
        BreakLuaError push_err = break_lua_push_value(L, &ctx->args[i]);
        if (push_err != BREAK_LUA_OK) {
            ctx->hdr.status = push_err;
            lua_settop(L, base);
            return;
        }
    }
    /* Exactly return_capacity wanted results: Lua nil-pads shortfalls and
     * discards extras, so the buffer is always fully written and the stack
     * shape stays deterministic. */
    status = lua_pcall(L, (int)ctx->arg_count, (int)ctx->return_capacity, 0);
    if (status != LUA_OK) {
        ctx->hdr.status = (status == LUA_ERRMEM) ? BREAK_LUA_OOM
                                                 : BREAK_LUA_FAILED;
        lua_pop(L, 1); /* error object; no report surface on calls */
        lua_settop(L, base);
        return;
    }
    /* [fn r1..rk] — result i sits at base + 1 + i. */
    for (i = 0u; i < ctx->return_capacity; i++) {
        BreakLuaError take_err =
            break_lua_take_value(L, base + 1 + (int)i, &ctx->returns[i]);
        if (take_err != BREAK_LUA_OK) {
            ctx->hdr.status = take_err;
            lua_settop(L, base);
            return;
        }
    }
    ctx->hdr.status = BREAK_LUA_OK;
    lua_settop(L, base);
}

BreakLuaError break_lua_runtime_call_ref(BreakLuaRuntime *runtime, u32 ref,
                                         const BreakLuaValue *args,
                                         usize arg_count,
                                         BreakLuaValue *returns,
                                         usize return_capacity)
{
    BreakLuaCallRefOpCtx ctx;
    BreakLuaError owner = break_lua_runtime_check_owner(runtime);

    /* Owner check first, then handle/shape/cap validation (nothing is read
     * from the handle's slot before the handle is validated). */
    if (owner != BREAK_LUA_OK) {
        return owner;
    }
    if (ref >= BREAK_LUA_MAX_FN_REFS || !runtime->fn_ref_used[ref]) {
        return BREAK_LUA_INVALID;
    }
    if (arg_count > 0u && !args) {
        return BREAK_LUA_INVALID;
    }
    if (return_capacity > 0u && !returns) {
        return BREAK_LUA_INVALID;
    }
    if (arg_count > (usize)runtime->max_values ||
        return_capacity > (usize)runtime->max_values) {
        return BREAK_LUA_OVERLOAD;
    }

    /* NIL-prefill: any post-admission failure leaves the buffer fully
     * written with NIL slots (same documented shape as runtime_call). */
    if (return_capacity > 0u) {
        memset(returns, 0, return_capacity * sizeof(*returns));
    }

    memset(&ctx, 0, sizeof(ctx));
    ctx.hdr.op = BREAK_LUA_OP_CALL_REF;
    ctx.lua_ref = runtime->fn_refs[ref];
    ctx.args = args;
    ctx.arg_count = arg_count;
    ctx.returns = returns;
    ctx.return_capacity = return_capacity;
    return break_lua_op_run(runtime, &ctx.hdr);
}

/* ---------------------------------------------------------------------- */
/* Frame lifecycle.                                                        */

/* Writes one bounded diagnostic record; pure C, fixed storage, safe to run
 * after any Lua failure (including OOM). */
static void break_lua_record_frame_error(BreakLuaRuntime *runtime,
                                         const char *module_name,
                                         const char *hook_name,
                                         const char *message,
                                         bool budget,
                                         bool dispatch_failure)
{
    BreakLuaFrameError *rec = &runtime->last_frame_error;
    usize n;
    runtime->frame_error_total++;
    rec->valid = true;
    rec->frame_seq = runtime->frame_seq;
    rec->budget = budget;
    rec->dispatch_failure = dispatch_failure;
    n = break_lua_name_len(module_name, sizeof(rec->module));
    if (n >= sizeof(rec->module)) {
        n = sizeof(rec->module) - 1u;
    }
    memcpy(rec->module, module_name, n);
    rec->module[n] = '\0';
    n = break_lua_name_len(hook_name, sizeof(rec->hook));
    if (n >= sizeof(rec->hook)) {
        n = sizeof(rec->hook) - 1u;
    }
    memcpy(rec->hook, hook_name, n);
    rec->hook[n] = '\0';
    n = break_lua_name_len(message, sizeof(rec->message));
    if (n >= sizeof(rec->message)) {
        n = sizeof(rec->message) - 1u;
    }
    memcpy(rec->message, message, n);
    rec->message[n] = '\0';
}

/* Count-hook callback armed while a frame hook runs under an instruction
 * budget, and (Phase 3 Task 2 review fix) while module code runs outside
 * frame dispatch — the staging chunk execution of load/reload and the
 * commit-path on_unload hook. Raising an error from a hook is legal in Lua
 * 5.4 and lands in the nearest pcall (the per-hook lua_pcall for frames,
 * the staging/commit lua_pcall for module ops). lua_getextraspace reaches
 * the runtime without allocating (the pointer was stored at bootstrap). */
void break_lua_budget_hook(lua_State *L, lua_Debug *ar)
{
    BreakLuaRuntime *runtime;
    (void)ar;
    runtime = *(BreakLuaRuntime **)lua_getextraspace(L);
    if (runtime) {
        runtime->budget_tripped = true;
    }
    luaL_error(L, "break_lua: instruction budget exceeded");
}

void break_lua_frame_impl(lua_State *L, BreakLuaRuntime *runtime,
                          BreakLuaFrameOpCtx *ctx)
{
    int base = lua_gettop(L);
    const char *hook_name = (ctx->phase == BREAK_LUA_FRAME_PHASE_BEGIN)
                                ? "on_frame_begin"
                                : "on_frame_end";
    const bool budget_enabled = runtime->instruction_budget != 0u;
    /* lua_sethook takes an int count; budgets above INT_MAX are clamped
     * (documented in break_lua.h). */
    const int budget_count =
        (runtime->instruction_budget > (u64)INT_MAX)
            ? INT_MAX
            : (int)runtime->instruction_budget;
    /* Snapshot storage. max_modules is validated <= BREAK_LUA_MAX_MODULES
     * at create, so these fixed arrays bound every registry shape. */
    u32 slot_index[BREAK_LUA_MAX_MODULES];
    bool disabled[BREAK_LUA_MAX_MODULES];
    u32 count = 0u;
    u32 n = 0u;
    u32 i;

    /* Snapshot phase: pin every occupied module's live environment with a
     * Lua stack reference (ref-based, never a registry-slot pointer) and
     * capture the slot index plus the hooks-disabled flag as of dispatch
     * start. The pins double as GC anchors: a module reloaded mid-dispatch
     * keeps its retired environment alive for the rest of this dispatch.
     * Raw pushes do not auto-grow the stack, so reserve count + slack up
     * front; a growth failure raises into the wrapper pcall (bounded
     * dispatch-level failure, stack unwound). */
    for (i = 0u; i < runtime->max_modules; i++) {
        if (runtime->modules[i].occupied) {
            count++;
        }
    }
    if (count == 0u) {
        ctx->hdr.status = BREAK_LUA_OK;
        return;
    }
    luaL_checkstack(L, (int)count + 8, "break_lua frame dispatch");
    n = 0u;
    for (i = 0u; i < runtime->max_modules; i++) {
        const BreakLuaModule *m = &runtime->modules[i];
        if (m->occupied) {
            slot_index[n] = i;
            disabled[n] = m->hooks_disabled;
            lua_rawgeti(L, LUA_REGISTRYINDEX, m->env_ref); /* pinned */
            n++;
        }
    }
    /* Dispatch phase: serve exactly the snapshot. env n sits at the stable
     * absolute index base + 1 + n; per-hook pushes/pops happen above it. */
    for (i = 0u; i < count; i++) {
        BreakLuaModule *m = &runtime->modules[slot_index[i]];
        int env_index = base + 1 + (int)i;
        int hook_status;
        bool tripped;
        if (disabled[i]) {
            continue; /* disabled at capture: skipped the whole dispatch */
        }
        lua_pushstring(L, hook_name);
        lua_rawget(L, env_index);                        /* [.. hook?] */
        if (!lua_isfunction(L, -1)) {
            lua_pop(L, 1);
            continue; /* a module without the hook is skipped, not an error */
        }
        if (ctx->phase == BREAK_LUA_FRAME_PHASE_BEGIN) {
            lua_pushnumber(L, (lua_Number)ctx->delta_seconds);
        }
        if (budget_enabled) {
            runtime->budget_tripped = false;
            lua_sethook(L, break_lua_budget_hook, LUA_MASKCOUNT,
                        budget_count);
        }
        hook_status = lua_pcall(
            L, ctx->phase == BREAK_LUA_FRAME_PHASE_BEGIN ? 1 : 0, 0, 0);
        if (budget_enabled) {
            lua_sethook(L, NULL, 0, 0);
        }
        if (hook_status == LUA_OK) {
            continue;
        }
        /* Bounded error record; other modules still run (continue). */
        tripped = budget_enabled && runtime->budget_tripped;
        {
            char message[128];
            break_lua_op_take_error(L, message, sizeof(message));
            break_lua_record_frame_error(runtime, m->name, hook_name,
                                         message, tripped, false);
        }
        if (tripped) {
            /* Runaway-module policy: a budget trip marks the module; its
             * hooks are skipped on later dispatches until the next
             * committed reload clears the mark. */
            m->hooks_disabled = true;
        }
    }
    ctx->hdr.status = BREAK_LUA_OK;
    lua_settop(L, base);
}

/* Shared begin/end driver: one independent snapshot dispatch per call.
 * Owner-thread enforcement for a void API mirrors the double-destroy
 * convention: test builds fail-stop with a diagnostic abort; production
 * builds ignore the call. NULL runtime is a no-op. */
static void break_lua_frame_dispatch(BreakLuaRuntime *runtime, int phase,
                                     double delta_seconds,
                                     const char *hook_name)
{
    BreakLuaFrameOpCtx ctx;
    if (!runtime) {
        return;
    }
#if defined(BREAK_LUA_TESTING)
    if (break_lua_runtime_check_owner(runtime) != BREAK_LUA_OK) {
        fprintf(stderr,
                "break_lua_runtime_%s_frame: non-owner thread (contract "
                "violation)\n",
                phase == BREAK_LUA_FRAME_PHASE_BEGIN ? "begin" : "end");
        abort();
    }
#else
    if (break_lua_runtime_check_owner(runtime) != BREAK_LUA_OK) {
        return; /* documented no-op in production builds */
    }
#endif
    memset(&ctx, 0, sizeof(ctx));
    ctx.hdr.op = BREAK_LUA_OP_FRAME;
    ctx.phase = phase;
    ctx.delta_seconds = delta_seconds;
    if (phase == BREAK_LUA_FRAME_PHASE_BEGIN) {
        runtime->frame_seq++;
    }
    if (break_lua_op_run(runtime, &ctx.hdr) != BREAK_LUA_OK) {
        /* Dispatch-level failure (e.g. OOM inside the snapshot): bounded
         * record with an empty module field. */
        break_lua_record_frame_error(
            runtime, "", hook_name,
            ctx.hdr.error[0] != '\0' ? ctx.hdr.error : "frame dispatch failed",
            false, true);
    }
}

void break_lua_runtime_begin_frame(BreakLuaRuntime *runtime,
                                   double delta_seconds)
{
    break_lua_frame_dispatch(runtime, BREAK_LUA_FRAME_PHASE_BEGIN,
                             delta_seconds, "on_frame_begin");
}

void break_lua_runtime_end_frame(BreakLuaRuntime *runtime)
{
    break_lua_frame_dispatch(runtime, BREAK_LUA_FRAME_PHASE_END, 0.0,
                             "on_frame_end");
}

#if defined(BREAK_LUA_TESTING)

BreakLuaTestFrameError break_lua_test_last_frame_error(BreakLuaRuntime *runtime)
{
    BreakLuaTestFrameError out;
    const BreakLuaFrameError *rec;
    memset(&out, 0, sizeof(out));
    if (!runtime) {
        return out;
    }
    rec = &runtime->last_frame_error;
    out.valid = rec->valid;
    out.frame_seq = rec->frame_seq;
    out.total = runtime->frame_error_total;
    out.budget = rec->budget;
    out.dispatch_failure = rec->dispatch_failure;
    memcpy(out.module, rec->module, sizeof(out.module));
    memcpy(out.hook, rec->hook, sizeof(out.hook));
    memcpy(out.message, rec->message, sizeof(out.message));
    return out;
}

bool break_lua_test_module_hooks_disabled(BreakLuaRuntime *runtime,
                                          const char *module_name)
{
    BreakLuaModule *m;
    if (!runtime || !module_name) {
        return false;
    }
    m = break_lua_module_find(runtime, module_name);
    if (!m) {
        return false;
    }
    return m->hooks_disabled;
}

/* Lua-side entry of the test-only reloader binding: reloads the target
 * module with the source captured at install time. Runs nested inside the
 * frame dispatch pcall and the per-hook pcall; reload's own op pcall nests
 * a third level without issue. Pushes a boolean result for the script. */
static int break_lua_test_reloader_cb(lua_State *L)
{
    BreakLuaRuntime *runtime =
        (BreakLuaRuntime *)lua_touserdata(L, lua_upvalueindex(1));
    const char *target = lua_tostring(L, lua_upvalueindex(2));
    size_t len = 0u;
    const char *source = lua_tolstring(L, lua_upvalueindex(3), &len);
    BreakLuaError err = BREAK_LUA_INVALID;
    if (runtime && target && source) {
        err = break_lua_runtime_reload_module(runtime, target, source,
                                              (usize)len, NULL);
    }
    lua_pushboolean(L, err == BREAK_LUA_OK);
    return 1;
}

void break_lua_test_reloader_impl(lua_State *L,
                                  BreakLuaTestReloaderOpCtx *ctx)
{
    int base = lua_gettop(L);
    lua_rawgeti(L, LUA_REGISTRYINDEX, ctx->env_ref);    /* [env] */
    lua_pushliteral(L, "_test_reload_now");
    lua_pushlightuserdata(L, ctx->runtime);
    lua_pushstring(L, ctx->target_module);
    lua_pushlstring(L, (const char *)ctx->source, ctx->source_size);
    lua_pushcclosure(L, break_lua_test_reloader_cb, 3);
    lua_rawset(L, -3);                                  /* [env] */
    lua_settop(L, base);
    ctx->hdr.status = BREAK_LUA_OK;
}

/* Test-only binding that simulates a script-triggered reload path (the
 * production `break.*` surface deliberately exposes no reload binding):
 * installs `_test_reload_now()` into the named module's environment. Pure
 * admission checks mirror load_module's; the install itself runs under the
 * shared protected op dispatch. */
BreakLuaError break_lua_test_install_reloader(BreakLuaRuntime *runtime,
                                              const char *module_name,
                                              const char *target_module,
                                              const void *source,
                                              usize source_size)
{
    BreakLuaTestReloaderOpCtx ctx;
    BreakLuaModule *m;
    BreakLuaError owner = break_lua_runtime_check_owner(runtime);
    usize name_len;
    usize target_len;
    if (owner != BREAK_LUA_OK) {
        return owner;
    }
    if (!module_name || !target_module) {
        return BREAK_LUA_INVALID;
    }
    name_len = break_lua_name_len(module_name,
                                  BREAK_LUA_MAX_MODULE_NAME_BYTES);
    target_len = break_lua_name_len(target_module,
                                    BREAK_LUA_MAX_MODULE_NAME_BYTES);
    if (name_len == 0u || name_len >= BREAK_LUA_MAX_MODULE_NAME_BYTES ||
        target_len == 0u || target_len >= BREAK_LUA_MAX_MODULE_NAME_BYTES) {
        return BREAK_LUA_INVALID;
    }
    if (!source || source_size == 0u) {
        return BREAK_LUA_INVALID;
    }
    if (source_size > runtime->max_module_bytes) {
        return BREAK_LUA_OVERLOAD;
    }
    m = break_lua_module_find(runtime, module_name);
    if (!m) {
        return BREAK_LUA_STALE;
    }
    memset(&ctx, 0, sizeof(ctx));
    ctx.hdr.op = BREAK_LUA_OP_TEST_RELOADER;
    ctx.env_ref = m->env_ref;
    ctx.runtime = runtime;
    ctx.target_module = target_module;
    ctx.source = source;
    ctx.source_size = source_size;
    return break_lua_op_run(runtime, &ctx.hdr);
}

#endif /* BREAK_LUA_TESTING */
