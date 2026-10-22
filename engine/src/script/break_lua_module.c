#include <script/break_lua.h>

#include <script/break_lua_internal.h>
#include <script/break_lua_test_hooks.h>

#include <lua/lauxlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Module load / versioned reload (Task 2). Full contract: break_lua.h
 * MODULES section. This TU also owns the shared protected op dispatch used
 * by every Lua-touching facade operation (module ops, calls, frame hooks).
 *
 * pcall DISCIPLINE: every Lua C API sequence that can allocate (and so can
 * longjmp on LUA_ERRMEM) runs inside the dispatch closure invoked through
 * lua_pcall by break_lua_op_run(). The closure itself is fetched from the
 * registry with lua_rawgeti and its context pushed as a lightuserdata —
 * neither can allocate — so no Lua entry point on any facade path ever runs
 * unprotected. Inside a staged operation, chunk execution errors
 * deliberately propagate to that pcall: no registry reference is taken
 * until staging has fully succeeded, so unwinding is complete cleanup. The
 * one exception is the old module's on_unload hook, which runs under its
 * own lua_pcall inside the commit operation because a hook failure must
 * discard the staged environment (unref) rather than unwind past it.
 *
 * STACK DISCIPLINE: every operation restores lua_settop(base) on every exit
 * it controls; the wrapper's pcall unwinds anything it does not. The tests
 * assert lua_gettop == 0 across load/reload/call/frame/failure mixes. */

static u64 break_lua_fnv1a64(const void *data, usize size)
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

usize break_lua_name_len(const char *name, usize cap)
{
    usize n = 0u;
    while (n < cap && name[n] != '\0') {
        n++;
    }
    return n;
}

/* Parses the source line out of a Lua loader/runtime message of the form
 * "name:LINE: text". The module name prefix is matched exactly when present
 * (robust against ':' inside messages); otherwise falls back to the first
 * ':' (covers Lua-truncated chunk ids for very long names). 0 when the
 * message carries no position. */
static u32 break_lua_error_line(const char *msg, const char *module_name)
{
    const char *p = msg;
    u32 line = 0u;
    u32 digits = 0u;
    if (module_name) {
        usize nlen = strlen(module_name);
        if (strncmp(msg, module_name, nlen) == 0 && msg[nlen] == ':') {
            p = msg + nlen + 1u;
        } else {
            const char *colon = strchr(msg, ':');
            if (!colon) {
                return 0u;
            }
            p = colon + 1;
        }
    } else {
        const char *colon = strchr(msg, ':');
        if (!colon) {
            return 0u;
        }
        p = colon + 1;
    }
    while (*p >= '0' && *p <= '9' && digits < 9u) {
        line = line * 10u + (u32)(*p - '0');
        p++;
        digits++;
    }
    return (*p == ':') ? line : 0u;
}

void break_lua_op_take_error(lua_State *L, char *out, usize out_cap)
{
    const char *msg;
    usize len;
    int type = lua_type(L, -1);
    if (out_cap == 0u) {
        lua_pop(L, 1);
        return;
    }
    if (type == LUA_TNUMBER) {
        int written = snprintf(out, out_cap, "%.14g", lua_tonumber(L, -1));
        (void)written;
        out[out_cap - 1u] = '\0';
        lua_pop(L, 1);
        return;
    }
    msg = (type == LUA_TSTRING) ? lua_tostring(L, -1)
                                : "non-string Lua error object";
    len = strlen(msg);
    if (len >= out_cap) {
        len = out_cap - 1u;
    }
    memcpy(out, msg, len);
    out[len] = '\0';
    lua_pop(L, 1);
}

/* Module-op error capture: bounded copy plus the source-line parse (the
 * module name prefix match needs ctx->module_name). */
static void break_lua_module_capture_error(lua_State *L,
                                           BreakLuaModuleOpCtx *ctx)
{
    break_lua_op_take_error(L, ctx->hdr.error, sizeof(ctx->hdr.error));
    ctx->hdr.error_line =
        break_lua_error_line(ctx->hdr.error, ctx->module_name);
}

/* STAGE: build a fresh module environment wired to the preserved state
 * table, compile the candidate source as a text chunk, and execute it.
 * Errors from luaL_loadbufferx are returned, not thrown; chunk execution
 * errors propagate to the wrapper pcall (see file header). On success the
 * only registry reference (the staged environment) is taken last. The
 * environment's globals resolve to the Task 4 whitelist sandbox (never the
 * base global table): see break_lua_binding.c. */
static void break_lua_stage_impl(lua_State *L, BreakLuaRuntime *runtime,
                                 BreakLuaModuleOpCtx *ctx)
{
    int base = lua_gettop(L);
    int load_status;

    /* The state table persists by identity: reuse the old environment's
     * `state` when it is still a table; otherwise (fresh load, or a chunk
     * that nil'ed its own state global) start a fresh empty table. */
    if (ctx->old_env_ref != LUA_NOREF) {
        lua_rawgeti(L, LUA_REGISTRYINDEX, ctx->old_env_ref); /* [oldenv] */
        lua_pushliteral(L, "state");
        lua_rawget(L, -2);                                 /* [oldenv state?] */
        if (!lua_istable(L, -1)) {
            lua_pop(L, 1);
            lua_newtable(L);                               /* [oldenv state] */
        }
        lua_remove(L, -2);                                 /* [state] */
    } else {
        lua_newtable(L);                                   /* [state] */
    }

    lua_newtable(L);                                       /* [state env] */
    break_lua_sandbox_wire_env(L, runtime);                /* [state env] */
    lua_pushliteral(L, "state");
    lua_pushvalue(L, -3);                            /* [state env "state" state] */
    lua_rawset(L, -3);                                     /* [state env] */

    /* Text mode only: binary/bytecode chunks are rejected by the loader. */
    load_status = luaL_loadbufferx(L, (const char *)ctx->source,
                                   ctx->source_size, ctx->chunkname, "t");
    if (load_status != LUA_OK) {                     /* [state env errmsg] */
        ctx->hdr.status = (load_status == LUA_ERRMEM) ? BREAK_LUA_OOM
                                                      : BREAK_LUA_FAILED;
        break_lua_module_capture_error(L, ctx);
        lua_settop(L, base);
        return;
    }                                                    /* [state env chunk] */
    lua_pushvalue(L, -2);                          /* [state env chunk env] */
    if (lua_setupvalue(L, -2, 1) == NULL) {              /* sets _ENV */
        /* A text main chunk always carries _ENV; defensive only. */
        lua_settop(L, base);
        ctx->hdr.status = BREAK_LUA_FAILED;
        memcpy(ctx->hdr.error, "chunk has no _ENV upvalue",
               sizeof("chunk has no _ENV upvalue"));
        ctx->hdr.error_line = 0u;
        return;
    }                                                    /* [state env chunk] */
    lua_call(L, 0, 0);               /* chunk error: propagate to the pcall */
    /* [state env] */
    ctx->new_env_ref = luaL_ref(L, LUA_REGISTRYINDEX);     /* [state] */
    ctx->hdr.status = BREAK_LUA_OK;
    lua_settop(L, base);
}

/* COMMIT: run the old environment's optional on_unload hook, then retire
 * the old environment. On hook failure the staged environment is discarded
 * and the old one stays referenced (old version keeps serving). The hook
 * runs under its own pcall so its error lands here instead of unwinding
 * past the unref. */
static void break_lua_commit_impl(lua_State *L, BreakLuaModuleOpCtx *ctx)
{
    int base = lua_gettop(L);
    int hook_status;

    ctx->committed = false;
    lua_rawgeti(L, LUA_REGISTRYINDEX, ctx->old_env_ref);     /* [env] */
    lua_pushliteral(L, "on_unload");
    lua_rawget(L, -2);                                     /* [env hook?] */
    if (lua_isfunction(L, -1)) {
        hook_status = lua_pcall(L, 0, 0, 0);       /* [env] or [env errmsg] */
        if (hook_status != LUA_OK) {
            ctx->hdr.status = (hook_status == LUA_ERRMEM) ? BREAK_LUA_OOM
                                                          : BREAK_LUA_FAILED;
            break_lua_module_capture_error(L, ctx);
            luaL_unref(L, LUA_REGISTRYINDEX, ctx->new_env_ref);
            ctx->new_env_ref = LUA_NOREF;
            lua_settop(L, base);
            return; /* old env_ref untouched: old version still live */
        }
    }
    lua_settop(L, base);
    luaL_unref(L, LUA_REGISTRYINDEX, ctx->old_env_ref);
    ctx->committed = true;
    ctx->hdr.status = BREAK_LUA_OK;
}

/* Single dispatch entry for every protected facade op. The runtime arrives
 * as the closure's sole upvalue (set at bootstrap); the op ctx is argument
 * 1 (lightuserdata). Both fetches are allocation-free. */
static int break_lua_op_dispatch(lua_State *L)
{
    BreakLuaRuntime *runtime =
        (BreakLuaRuntime *)lua_touserdata(L, lua_upvalueindex(1));
    BreakLuaOpHeader *hdr = (BreakLuaOpHeader *)lua_touserdata(L, 1);
    if (!hdr) {
        return 0;
    }
    switch (hdr->op) {
    case BREAK_LUA_OP_STAGE:
        break_lua_stage_impl(L, runtime, (BreakLuaModuleOpCtx *)hdr);
        break;
    case BREAK_LUA_OP_COMMIT:
        break_lua_commit_impl(L, (BreakLuaModuleOpCtx *)hdr);
        break;
    case BREAK_LUA_OP_CALL:
        break_lua_call_impl(L, (BreakLuaCallOpCtx *)hdr);
        break;
    case BREAK_LUA_OP_FRAME:
        break_lua_frame_impl(L, runtime, (BreakLuaFrameOpCtx *)hdr);
        break;
#if defined(BREAK_LUA_TESTING)
    case BREAK_LUA_OP_TEST_RELOADER:
        break_lua_test_reloader_impl(L, (BreakLuaTestReloaderOpCtx *)hdr);
        break;
#endif
    default:
        break;
    }
    return 0;
}

void break_lua_op_bootstrap(lua_State *L, BreakLuaRuntime *runtime)
{
    /* Extraspace gives the budget hook callback an allocation-free path
     * back to the runtime (a hook receives only the lua_State). */
    *(void **)lua_getextraspace(L) = (void *)runtime;
    lua_pushlightuserdata(L, runtime);
    lua_pushcclosure(L, break_lua_op_dispatch, 1);
    runtime->op_ref = luaL_ref(L, LUA_REGISTRYINDEX);
}

BreakLuaError break_lua_op_run(BreakLuaRuntime *runtime,
                               BreakLuaOpHeader *hdr)
{
    lua_State *L = runtime->L;
    int status;
    hdr->status = BREAK_LUA_FAILED;
    hdr->error[0] = '\0';
    hdr->error_line = 0u;
    lua_rawgeti(L, LUA_REGISTRYINDEX, runtime->op_ref);
    lua_pushlightuserdata(L, hdr);
    status = lua_pcall(L, 1, 0, 0);
    if (status != LUA_OK) {
        hdr->status = (status == LUA_ERRMEM) ? BREAK_LUA_OOM
                                             : BREAK_LUA_FAILED;
        break_lua_op_take_error(L, hdr->error, sizeof(hdr->error));
    }
    return hdr->status;
}

BreakLuaModule *break_lua_module_find(BreakLuaRuntime *runtime,
                                      const char *name)
{
    u32 i;
    for (i = 0u; i < runtime->max_modules; i++) {
        BreakLuaModule *m = &runtime->modules[i];
        if (m->occupied && strcmp(m->name, name) == 0) {
            return m;
        }
    }
    return NULL;
}

static BreakLuaModule *break_lua_module_free_slot(BreakLuaRuntime *runtime)
{
    u32 i;
    for (i = 0u; i < runtime->max_modules; i++) {
        if (!runtime->modules[i].occupied) {
            return &runtime->modules[i];
        }
    }
    return NULL;
}

/* Shared admission gate: owner thread, name shape, source shape, byte cap.
 * Fills name_len for the caller. The checks are ordered so no arithmetic on
 * untrusted values happens before validation. */
static BreakLuaError break_lua_module_admit(BreakLuaRuntime *runtime,
                                            const char *module_name,
                                            const void *source,
                                            usize source_size,
                                            usize *out_name_len)
{
    BreakLuaError owner = break_lua_runtime_check_owner(runtime);
    usize name_len;
    if (owner != BREAK_LUA_OK) {
        return owner; /* INVALID for NULL runtime, REJECTED cross-thread */
    }
    if (!module_name) {
        return BREAK_LUA_INVALID;
    }
    name_len = break_lua_name_len(module_name,
                                  BREAK_LUA_MAX_MODULE_NAME_BYTES);
    if (name_len == 0u || name_len >= BREAK_LUA_MAX_MODULE_NAME_BYTES) {
        return BREAK_LUA_INVALID;
    }
    if (!source || source_size == 0u) {
        return BREAK_LUA_INVALID;
    }
    if (source_size > runtime->max_module_bytes) {
        return BREAK_LUA_OVERLOAD;
    }
    *out_name_len = name_len;
    return BREAK_LUA_OK;
}

BreakLuaError break_lua_runtime_load_module(BreakLuaRuntime *runtime,
                                            const char *module_name,
                                            const void *source,
                                            usize source_size)
{
    BreakLuaModuleOpCtx ctx;
    BreakLuaModule *slot;
    BreakLuaError err;
    usize name_len = 0u;
    char *name_copy;

    err = break_lua_module_admit(runtime, module_name, source, source_size,
                                 &name_len);
    if (err != BREAK_LUA_OK) {
        return err;
    }
    /* Duplicate names are rejected before the count check: a full registry
     * must still answer "already loaded" correctly. */
    if (break_lua_module_find(runtime, module_name)) {
        return BREAK_LUA_REJECTED;
    }
    if (runtime->module_count >= runtime->max_modules) {
        return BREAK_LUA_OVERLOAD;
    }

    name_copy = (char *)break_lua_test_calloc(name_len + 1u);
    if (!name_copy) {
        return BREAK_LUA_OOM;
    }
    memcpy(name_copy, module_name, name_len);

    memset(&ctx, 0, sizeof(ctx));
    ctx.hdr.op = BREAK_LUA_OP_STAGE;
    ctx.module_name = module_name;
    ctx.source = source;
    ctx.source_size = source_size;
    ctx.old_env_ref = LUA_NOREF;
    ctx.new_env_ref = LUA_NOREF;
    ctx.chunkname[0] = '@';
    memcpy(ctx.chunkname + 1u, module_name, name_len);
    ctx.chunkname[1u + name_len] = '\0';

    err = break_lua_op_run(runtime, &ctx.hdr);
    if (err != BREAK_LUA_OK) {
        free(name_copy);
        return err;
    }

    /* Staging succeeded; everything below is infallible. */
    slot = break_lua_module_free_slot(runtime);
    if (!slot) {
        /* Unreachable: count < max_modules implies a free slot. Defensive:
         * discard the staged env rather than leak it. */
        luaL_unref(runtime->L, LUA_REGISTRYINDEX, ctx.new_env_ref);
        free(name_copy);
        return BREAK_LUA_OVERLOAD;
    }
    slot->occupied = true;
    slot->name = name_copy;
    slot->version = 1u;
    slot->hash = break_lua_fnv1a64(source, source_size);
    slot->env_ref = ctx.new_env_ref;
    slot->hooks_disabled = false;
    runtime->module_count++;
    return BREAK_LUA_OK;
}

BreakLuaError break_lua_runtime_reload_module(BreakLuaRuntime *runtime,
                                              const char *module_name,
                                              const void *source,
                                              usize source_size,
                                              BreakLuaReloadReport *report)
{
    BreakLuaReloadReport local;
    BreakLuaModuleOpCtx ctx;
    BreakLuaModule *m;
    BreakLuaError err;
    usize name_len = 0u;

    memset(&local, 0, sizeof(local));
    if (report) {
        memset(report, 0, sizeof(*report));
    }

    if (!runtime) {
        err = BREAK_LUA_INVALID;
        goto out;
    }
    /* Owner check first, then shape checks (admit() without the byte cap:
     * the cap is a policy failure, not malformed input, and needs the live
     * module's old_* fields in the report). */
    {
        BreakLuaError owner = break_lua_runtime_check_owner(runtime);
        if (owner != BREAK_LUA_OK) {
            err = owner;
            goto out;
        }
    }
    if (!module_name) {
        err = BREAK_LUA_INVALID;
        goto out;
    }
    name_len = break_lua_name_len(module_name,
                                  BREAK_LUA_MAX_MODULE_NAME_BYTES);
    if (name_len == 0u || name_len >= BREAK_LUA_MAX_MODULE_NAME_BYTES) {
        err = BREAK_LUA_INVALID;
        goto out;
    }
    if (!source || source_size == 0u) {
        err = BREAK_LUA_INVALID;
        goto out;
    }

    m = break_lua_module_find(runtime, module_name);
    if (!m) {
        /* Contract: reload of a never-loaded name is STALE (the name names
         * no live object), never an implicit load. */
        err = BREAK_LUA_STALE;
        goto out;
    }
    local.old_version = m->version;
    local.new_version = m->version; /* a failed reload consumes no version */
    local.old_hash = m->hash;

    if (source_size > runtime->max_module_bytes) {
        err = BREAK_LUA_OVERLOAD; /* rejected before hashing: new_hash stays 0 */
        goto out;
    }
    local.new_hash = break_lua_fnv1a64(source, source_size);

    if (m->version == UINT32_MAX) {
        /* Checked version-space bound: no u32 wrap is ever committed. */
        err = BREAK_LUA_REJECTED;
        goto out;
    }

    memset(&ctx, 0, sizeof(ctx));
    ctx.module_name = module_name;
    ctx.source = source;
    ctx.source_size = source_size;
    ctx.old_env_ref = m->env_ref;
    ctx.new_env_ref = LUA_NOREF;
    ctx.chunkname[0] = '@';
    memcpy(ctx.chunkname + 1u, module_name, name_len);
    ctx.chunkname[1u + name_len] = '\0';

    ctx.hdr.op = BREAK_LUA_OP_STAGE;
    err = break_lua_op_run(runtime, &ctx.hdr);
    if (err != BREAK_LUA_OK) {
        /* A chunk error that propagated to the wrapper pcall carries no
         * parsed line yet; parse it here where the module name is known. */
        local.error_line = ctx.hdr.error_line;
        if (local.error_line == 0u && ctx.hdr.error[0] != '\0') {
            local.error_line =
                break_lua_error_line(ctx.hdr.error, module_name);
        }
        memcpy(local.error, ctx.hdr.error, sizeof(local.error));
        goto out; /* old registration untouched */
    }

    ctx.hdr.op = BREAK_LUA_OP_COMMIT;
    err = break_lua_op_run(runtime, &ctx.hdr);
    if (err != BREAK_LUA_OK) {
        local.error_line = ctx.hdr.error_line;
        if (local.error_line == 0u && ctx.hdr.error[0] != '\0') {
            local.error_line =
                break_lua_error_line(ctx.hdr.error, module_name);
        }
        memcpy(local.error, ctx.hdr.error, sizeof(local.error));
        goto out; /* staged env discarded by the commit op; old still live */
    }

    /* Committed: swap is infallible plain assignments. The new version
     * starts with its frame hooks enabled (a budget mark never survives a
     * committed reload). */
    m->env_ref = ctx.new_env_ref;
    m->version += 1u;
    m->hash = local.new_hash;
    m->hooks_disabled = false;
    local.committed = true;
    local.new_version = m->version;
    err = BREAK_LUA_OK;

out:
    if (report) {
        *report = local;
    }
    return err;
}

void break_lua_module_registry_destroy(BreakLuaRuntime *runtime)
{
    u32 i;
    if (!runtime->modules) {
        return;
    }
    for (i = 0u; i < runtime->max_modules; i++) {
        free(runtime->modules[i].name);
        runtime->modules[i].name = NULL;
    }
    free(runtime->modules);
    runtime->modules = NULL;
    runtime->module_count = 0u;
}

#if defined(BREAK_LUA_TESTING)

BreakLuaTestModuleStat break_lua_test_module_stat(BreakLuaRuntime *runtime,
                                                  const char *module_name)
{
    BreakLuaTestModuleStat stat;
    BreakLuaModule *m;
    memset(&stat, 0, sizeof(stat));
    if (!runtime || !module_name) {
        return stat;
    }
    m = break_lua_module_find(runtime, module_name);
    if (!m) {
        return stat;
    }
    stat.loaded = true;
    stat.version = m->version;
    stat.hash = m->hash;
    return stat;
}

u32 break_lua_test_module_count(BreakLuaRuntime *runtime)
{
    if (!runtime) {
        return 0u;
    }
    return runtime->module_count;
}

bool break_lua_test_module_env_number(BreakLuaRuntime *runtime,
                                      const char *module_name,
                                      const char *key, double *out_value)
{
    BreakLuaModule *m;
    lua_State *L;
    bool ok = false;
    if (!runtime || !module_name || !key || !out_value) {
        return false;
    }
    m = break_lua_module_find(runtime, module_name);
    if (!m) {
        return false;
    }
    L = runtime->L;
    lua_rawgeti(L, LUA_REGISTRYINDEX, m->env_ref); /* [env] */
    lua_pushstring(L, key);
    lua_rawget(L, -2);                             /* [env value] */
    if (lua_type(L, -1) == LUA_TNUMBER) {
        *out_value = (double)lua_tonumber(L, -1);
        ok = true;
    }
    lua_pop(L, 2);
    return ok;
}

bool break_lua_test_module_state_number(BreakLuaRuntime *runtime,
                                        const char *module_name,
                                        const char *key, double *out_value)
{
    BreakLuaModule *m;
    lua_State *L;
    bool ok = false;
    if (!runtime || !module_name || !key || !out_value) {
        return false;
    }
    m = break_lua_module_find(runtime, module_name);
    if (!m) {
        return false;
    }
    L = runtime->L;
    lua_rawgeti(L, LUA_REGISTRYINDEX, m->env_ref); /* [env] */
    lua_pushliteral(L, "state");
    lua_rawget(L, -2);                             /* [env state?] */
    if (lua_istable(L, -1)) {
        lua_pushstring(L, key);
        lua_rawget(L, -2);                         /* [env state value] */
        if (lua_type(L, -1) == LUA_TNUMBER) {
            *out_value = (double)lua_tonumber(L, -1);
            ok = true;
        }
        lua_pop(L, 1);                             /* [env state] */
    }
    lua_pop(L, 2);
    return ok;
}

#endif /* BREAK_LUA_TESTING */
