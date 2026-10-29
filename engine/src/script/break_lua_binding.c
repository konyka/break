#include <script/break_lua.h>

#include <script/break_lua_internal.h>
#include <script/break_lua_test_hooks.h>

#include <core/platform_thread.h>

#include <lua/lauxlib.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Host bindings and module sandbox (Task 4). Full contract: break_lua.h
 * HOST BINDINGS AND SANDBOX section.
 *
 * OWNERSHIP: the ECS batch is a pure C, host-owned bounded FIFO (this TU
 * defines the opaque struct); the runtime only BORROWS it. The config store
 * is a pure C, runtime-owned, lazily allocated array. No host pointer is
 * ever pushed into the Lua state: the script-visible closures reach the
 * runtime through lua_getextraspace (set at bootstrap, allocation-free),
 * exactly like the Task 3 budget hook callback, so the batch pointer is
 * structurally unreachable from Lua.
 *
 * pcall DISCIPLINE: the public binding APIs (bind/drain/create/destroy)
 * never touch the Lua state, so they need no pcall of their own. Every new
 * Lua entry point introduced here — the break.ecs/break.config closures and
 * the read-only __newindex guard — only ever runs from module code, i.e.
 * inside an existing pcall shell of the shared dispatch (chunk staging,
 * module calls, per-hook pcalls, on_unload): their string pushes can
 * longjmp on LUA_ERRMEM and land safely in those shells. The sandbox
 * structures are built inside the create bootstrap pcall and the staging
 * op's pcall (see break_lua_runtime.c / break_lua_module.c).
 *
 * SANDBOX SHAPE: the whitelist table, the os-subset table, the break impl
 * tables and every read-through proxy are built ONCE per runtime and held
 * by the registry (runtime->sandbox_ref anchors the whole graph: sandbox
 * fields hold proxies; proxy metatables hold their impl tables). Module
 * environments resolve globals through this whitelist; the raw-access and
 * metatable-mutating base functions are deliberately excluded from it, so a
 * script has no path around a proxy's __newindex guard and cannot shadow a
 * sibling module's stdlib view. */

struct BreakLuaEcsBatch {
    PlatformThreadId owner;      /* captured at create */
    BreakLuaRuntime *runtime;    /* bound back-pointer (NULL until bound) */
    BreakLuaEcsRecord *records;  /* owned ring storage, capacity entries */
    usize capacity;
    usize head;                  /* index of the oldest live record */
    usize count;                 /* live records (<= capacity) */
};

#if defined(BREAK_LUA_TESTING)

/* Test-build live-batch registry: mirrors the runtime registry in
 * break_lua_runtime.c (lookup BY VALUE before any dereference, exactly-once
 * semantics, spinlock for TSan cleanliness). */
#define BREAK_LUA_BATCH_REGISTRY_CAPACITY 256u

static atomic_flag g_batch_registry_lock = ATOMIC_FLAG_INIT;
static const void *g_batch_registry[BREAK_LUA_BATCH_REGISTRY_CAPACITY];
static u32 g_batch_registry_count;

static void batch_registry_lock(void)
{
    while (atomic_flag_test_and_set_explicit(&g_batch_registry_lock,
                                             memory_order_acquire)) {
        platform_thread_yield();
    }
}

static void batch_registry_unlock(void)
{
    atomic_flag_clear_explicit(&g_batch_registry_lock, memory_order_release);
}

static void batch_registry_add(const void *batch)
{
    bool added = false;
    batch_registry_lock();
    if (g_batch_registry_count < BREAK_LUA_BATCH_REGISTRY_CAPACITY) {
        g_batch_registry[g_batch_registry_count] = batch;
        g_batch_registry_count++;
        added = true;
    }
    batch_registry_unlock();
    if (!added) {
        fprintf(stderr,
                "break_lua_ecs_batch_create: test registry exhausted (%u "
                "live batches)\n",
                BREAK_LUA_BATCH_REGISTRY_CAPACITY);
        abort();
    }
}

static bool batch_registry_remove(const void *batch)
{
    u32 i;
    bool found = false;
    batch_registry_lock();
    for (i = 0u; i < g_batch_registry_count; i++) {
        if (g_batch_registry[i] == batch) {
            g_batch_registry[i] = g_batch_registry[g_batch_registry_count - 1u];
            g_batch_registry_count--;
            found = true;
            break;
        }
    }
    batch_registry_unlock();
    return found;
}

#endif /* BREAK_LUA_TESTING */

/* ---------------------------------------------------------------------- */
/* Batch lifecycle and drain (public, pure C — no Lua state touched).      */

BreakLuaEcsBatch *break_lua_ecs_batch_create(usize capacity)
{
    BreakLuaEcsBatch *batch;
    if (capacity == 0u) {
        capacity = BREAK_LUA_ECS_BATCH_DEFAULT_CAPACITY;
    }
    /* Fail-closed validation, no arithmetic on the untrusted value before
     * this gate: hard ceiling, then the checked multiply. */
    if (capacity > BREAK_LUA_ECS_BATCH_MAX_CAPACITY ||
        capacity > SIZE_MAX / sizeof(BreakLuaEcsRecord)) {
        return NULL;
    }
    batch = (BreakLuaEcsBatch *)break_lua_test_calloc(sizeof(*batch));
    if (!batch) {
        return NULL;
    }
    batch->records = (BreakLuaEcsRecord *)break_lua_test_calloc(
        capacity * sizeof(BreakLuaEcsRecord));
    if (!batch->records) {
        free(batch);
        return NULL;
    }
    batch->capacity = capacity;
    batch->owner = platform_thread_current_id();
#if defined(BREAK_LUA_TESTING)
    batch_registry_add(batch);
#endif
    return batch;
}

void break_lua_ecs_batch_destroy(BreakLuaEcsBatch *batch)
{
    if (!batch) {
        return;
    }
#if defined(BREAK_LUA_TESTING)
    /* Lookup BY VALUE before any dereference: a double destroy or foreign
     * pointer aborts here without reading freed memory (the runtime destroy
     * precedent in break_lua_runtime.c). */
    if (!batch_registry_remove(batch)) {
        fprintf(stderr,
                "break_lua_ecs_batch_destroy: double destroy or foreign "
                "batch %p\n",
                (void *)batch);
        abort();
    }
#endif
    if (!platform_thread_id_equal(platform_thread_current_id(),
                                  batch->owner)) {
#if defined(BREAK_LUA_TESTING)
        fprintf(stderr,
                "break_lua_ecs_batch_destroy: non-owner thread (contract "
                "violation)\n");
        abort();
#else
        return; /* documented no-op in production builds */
#endif
    }
    /* Release the borrow first: a runtime that outlives its batch answers
     * scripts with "no batch bound" and never touches freed memory. */
    if (batch->runtime) {
        batch->runtime->batch = NULL;
        batch->runtime = NULL;
    }
    free(batch->records);
    free(batch);
}

usize break_lua_ecs_batch_drain(BreakLuaEcsBatch *batch,
                                BreakLuaEcsRecord *out_records,
                                usize capacity)
{
    usize n;
    usize i;
    if (!batch) {
        return 0u;
    }
    if (!platform_thread_id_equal(platform_thread_current_id(),
                                  batch->owner)) {
        return 0u; /* bounded no-op from a non-owner thread */
    }
    if (!out_records || capacity == 0u) {
        return 0u;
    }
    n = (batch->count < capacity) ? batch->count : capacity;
    /* head < capacity and n <= capacity, so head + i < 2 * MAX_CAPACITY:
     * no overflow is possible. */
    for (i = 0u; i < n; i++) {
        out_records[i] = batch->records[(batch->head + i) % batch->capacity];
    }
    batch->head = (batch->head + n) % batch->capacity;
    batch->count -= n;
    return n;
}

/* Ring push; false when full (never blocks, never grows). */
static bool break_lua_batch_enqueue(BreakLuaEcsBatch *batch,
                                    const BreakLuaEcsRecord *rec)
{
    usize idx;
    if (batch->count >= batch->capacity) {
        return false;
    }
    idx = (batch->head + batch->count) % batch->capacity;
    batch->records[idx] = *rec;
    batch->count++;
    return true;
}

/* ---------------------------------------------------------------------- */
/* Binding registration (public, pure C — no Lua state touched).           */

BreakLuaError break_lua_runtime_bind_ecs_batch(BreakLuaRuntime *runtime,
                                               BreakLuaEcsBatch *batch)
{
    BreakLuaError owner = break_lua_runtime_check_owner(runtime);
    if (owner != BREAK_LUA_OK) {
        return owner; /* INVALID for NULL runtime, REJECTED cross-thread */
    }
    if (!batch) {
        return BREAK_LUA_INVALID;
    }
    if (!platform_thread_id_equal(platform_thread_current_id(),
                                  batch->owner)) {
        return BREAK_LUA_REJECTED;
    }
    /* One-to-one, one-shot for the runtime's lifetime. */
    if (runtime->batch || batch->runtime) {
        return BREAK_LUA_REJECTED;
    }
    runtime->batch = batch;
    batch->runtime = runtime;
    return BREAK_LUA_OK;
}

/* Bounded key scan + shape validation for one entry. All-or-nothing: every
 * entry is validated before anything is stored. */
static BreakLuaError break_lua_config_entry_validate(
    const BreakLuaConfigBinding *entry)
{
    usize key_len;
    if (!entry->key) {
        return BREAK_LUA_INVALID;
    }
    key_len = break_lua_name_len(entry->key, BREAK_LUA_MAX_CONFIG_KEY_BYTES);
    if (key_len == 0u || key_len >= BREAK_LUA_MAX_CONFIG_KEY_BYTES) {
        return BREAK_LUA_INVALID;
    }
    if (isnan(entry->min_value) || isnan(entry->max_value) ||
        isnan(entry->initial_value)) {
        return BREAK_LUA_INVALID;
    }
    if (entry->min_value > entry->max_value) {
        return BREAK_LUA_INVALID;
    }
    return BREAK_LUA_OK;
}

BreakLuaError break_lua_runtime_bind_config(BreakLuaRuntime *runtime,
                                            const BreakLuaConfigBinding *entries,
                                            usize entry_count)
{
    BreakLuaError owner = break_lua_runtime_check_owner(runtime);
    usize i;
    usize j;
    if (owner != BREAK_LUA_OK) {
        return owner;
    }
    if (entry_count == 0u) {
        return BREAK_LUA_OK; /* documented no-op; entries may be NULL */
    }
    if (!entries) {
        return BREAK_LUA_INVALID;
    }
    if (entry_count > BREAK_LUA_MAX_CONFIG_BINDINGS) {
        return BREAK_LUA_OVERLOAD;
    }
    /* Phase 1: validate shapes (nothing is stored yet). */
    for (i = 0u; i < entry_count; i++) {
        BreakLuaError err = break_lua_config_entry_validate(&entries[i]);
        if (err != BREAK_LUA_OK) {
            return err;
        }
    }
    /* Phase 2: duplicate keys within the call and against the store. Keys
     * passed phase 1, so they are NUL-terminated within the scan cap. */
    for (i = 0u; i < entry_count; i++) {
        for (j = i + 1u; j < entry_count; j++) {
            if (strcmp(entries[i].key, entries[j].key) == 0) {
                return BREAK_LUA_REJECTED;
            }
        }
        for (j = 0u; j < runtime->config_count; j++) {
            if (strcmp(entries[i].key, runtime->configs[j].key) == 0) {
                return BREAK_LUA_REJECTED;
            }
        }
    }
    /* Phase 3: cumulative count cap. Both addends are <= the 256 ceiling,
     * so the sum cannot overflow. */
    if (entry_count > BREAK_LUA_MAX_CONFIG_BINDINGS - runtime->config_count) {
        return BREAK_LUA_OVERLOAD;
    }
    /* Phase 4: store (lazily allocated, fixed capacity). */
    if (!runtime->configs) {
        runtime->configs = (BreakLuaConfigSlot *)break_lua_test_calloc(
            (usize)BREAK_LUA_MAX_CONFIG_BINDINGS * sizeof(BreakLuaConfigSlot));
        if (!runtime->configs) {
            return BREAK_LUA_OOM;
        }
    }
    for (i = 0u; i < entry_count; i++) {
        BreakLuaConfigSlot *slot = &runtime->configs[runtime->config_count + i];
        double value = entries[i].initial_value;
        usize key_len =
            break_lua_name_len(entries[i].key, BREAK_LUA_MAX_CONFIG_KEY_BYTES);
        memcpy(slot->key, entries[i].key, key_len);
        slot->key[key_len] = '\0';
        slot->min_value = entries[i].min_value;
        slot->max_value = entries[i].max_value;
        /* Clamp at bind time: script reads always observe an in-range value. */
        if (value < slot->min_value) {
            value = slot->min_value;
        }
        if (value > slot->max_value) {
            value = slot->max_value;
        }
        slot->value = value;
    }
    runtime->config_count += (u32)entry_count;
    return BREAK_LUA_OK;
}

void break_lua_binding_shutdown(BreakLuaRuntime *runtime)
{
    /* Pure C teardown: release the borrow (the batch stays host-owned and
     * must not hold a dangling back-pointer) and free the config store. */
    if (runtime->batch) {
        runtime->batch->runtime = NULL;
        runtime->batch = NULL;
    }
    free(runtime->configs);
    runtime->configs = NULL;
    runtime->config_count = 0u;
}

/* ---------------------------------------------------------------------- */
/* Script-visible closures. Each reaches the runtime through the extraspace
 * (set at bootstrap); no pointer ever travels as Lua userdata. Every
 * failure is (false/nil, message) — these closures never raise. They run
 * only from module code, i.e. inside an existing dispatch pcall shell.   */

static int break_lua_ecs_spawn_cb(lua_State *L)
{
    BreakLuaRuntime *runtime = *(BreakLuaRuntime **)lua_getextraspace(L);
    BreakLuaEcsBatch *batch = runtime ? runtime->batch : NULL;
    BreakLuaEcsRecord rec;
    if (!batch) {
        lua_pushboolean(L, 0);
        lua_pushstring(L, "break.ecs: no batch bound");
        return 2;
    }
    memset(&rec, 0, sizeof(rec));
    rec.kind = (u16)BREAK_LUA_ECS_RECORD_SPAWN;
    rec.value_type = (u16)BREAK_LUA_ECS_VALUE_NONE;
    if (!break_lua_batch_enqueue(batch, &rec)) {
        lua_pushboolean(L, 0);
        lua_pushstring(L, "break.ecs: batch full");
        return 2;
    }
    lua_pushboolean(L, 1);
    return 1;
}

/* Reads a bounded name argument (component/field). Returns NULL (with a
 * Lua-visible failure pair pushed) when the shape is invalid. */
static const char *break_lua_read_name_arg(lua_State *L, int index,
                                           char *out, usize out_cap,
                                           usize *out_len)
{
    const char *s;
    size_t len = 0u;
    if (lua_type(L, index) != LUA_TSTRING) {
        return NULL;
    }
    s = lua_tolstring(L, index, &len);
    if (len == 0u || len >= out_cap) {
        return NULL;
    }
    memcpy(out, s, len);
    out[len] = '\0';
    *out_len = (usize)len;
    return s;
}

static int break_lua_ecs_set_cb(lua_State *L)
{
    BreakLuaRuntime *runtime = *(BreakLuaRuntime **)lua_getextraspace(L);
    BreakLuaEcsBatch *batch = runtime ? runtime->batch : NULL;
    BreakLuaEcsRecord rec;
    usize name_len = 0u;
    const char *msg = NULL;
    memset(&rec, 0, sizeof(rec));
    rec.kind = (u16)BREAK_LUA_ECS_RECORD_SET;

    /* Shape validation first (documented): identical errors whether or not
     * a batch is bound. */
    if (!break_lua_read_name_arg(L, 1, rec.component, sizeof(rec.component),
                                 &name_len)) {
        msg = "break.ecs.set: invalid component";
        goto fail;
    }
    if (!break_lua_read_name_arg(L, 2, rec.field, sizeof(rec.field),
                                 &name_len)) {
        msg = "break.ecs.set: invalid field";
        goto fail;
    }
    switch (lua_type(L, 3)) {
    case LUA_TNUMBER:
        rec.value_type = (u16)BREAK_LUA_ECS_VALUE_NUMBER;
        rec.value.n = (f64)lua_tonumber(L, 3);
        break;
    case LUA_TBOOLEAN:
        rec.value_type = (u16)BREAK_LUA_ECS_VALUE_BOOL;
        rec.value.b = lua_toboolean(L, 3) != 0;
        break;
    case LUA_TSTRING: {
        const char *s;
        size_t len = 0u;
        s = lua_tolstring(L, 3, &len);
        if (len >= (size_t)BREAK_LUA_ECS_VALUE_STRING_CAPACITY) {
            msg = "break.ecs.set: value string too long";
            goto fail;
        }
        memcpy(rec.value.s.data, s, len);
        rec.value.s.data[len] = '\0';
        rec.value.s.len = (u32)len;
        rec.value_type = (u16)BREAK_LUA_ECS_VALUE_STRING;
        break;
    }
    default:
        msg = "break.ecs.set: unsupported value type";
        goto fail;
    }

    if (!batch) {
        msg = "break.ecs: no batch bound";
        goto fail;
    }
    if (!break_lua_batch_enqueue(batch, &rec)) {
        msg = "break.ecs: batch full";
        goto fail;
    }
    lua_pushboolean(L, 1);
    return 1;

fail:
    lua_pushboolean(L, 0);
    lua_pushstring(L, msg);
    return 2;
}

BreakLuaError break_lua_runtime_set_config(BreakLuaRuntime *runtime,
                                           const char *key, double value)
{
    BreakLuaError owner = break_lua_runtime_check_owner(runtime);
    usize key_len;
    u32 i;
    if (owner != BREAK_LUA_OK) {
        return owner;
    }
    if (!key || isnan(value)) {
        return BREAK_LUA_INVALID;
    }
    key_len = break_lua_name_len(key, BREAK_LUA_MAX_CONFIG_KEY_BYTES);
    if (key_len == 0u || key_len >= BREAK_LUA_MAX_CONFIG_KEY_BYTES) {
        return BREAK_LUA_INVALID;
    }
    for (i = 0u; runtime->configs && i < runtime->config_count; i++) {
        BreakLuaConfigSlot *slot = &runtime->configs[i];
        if (strcmp(slot->key, key) == 0) {
            if (value < slot->min_value) {
                value = slot->min_value;
            }
            if (value > slot->max_value) {
                value = slot->max_value;
            }
            slot->value = value;
            return BREAK_LUA_OK;
        }
    }
    return BREAK_LUA_STALE;
}

static int break_lua_config_get_cb(lua_State *L)
{
    BreakLuaRuntime *runtime = *(BreakLuaRuntime **)lua_getextraspace(L);
    const char *key;
    if (lua_type(L, 1) != LUA_TSTRING) {
        lua_pushnil(L);
        lua_pushstring(L, "break.config.get: invalid key");
        return 2;
    }
    key = lua_tostring(L, 1);
    if (runtime && runtime->configs) {
        u32 i;
        for (i = 0u; i < runtime->config_count; i++) {
            if (strcmp(runtime->configs[i].key, key) == 0) {
                lua_pushnumber(L, (lua_Number)runtime->configs[i].value);
                return 1;
            }
        }
    }
    lua_pushnil(L);
    lua_pushstring(L, "break.config.get: unknown key");
    return 2;
}

/* Shared __newindex guard for every script-visible read-only table. Raises
 * a bounded Lua error; scripts cannot bypass it (rawset/setmetatable are
 * absent from the whitelist). */
static int break_lua_readonly_newindex(lua_State *L)
{
    return luaL_error(L, "break_lua: attempted to mutate a read-only table");
}

/* ---------------------------------------------------------------------- */
/* Budget-transparent pcall/xpcall (fix round 4, NEW-C4). The base         */
/* functions would return the budget-trip error to the SCRIPT as an        */
/* ordinary (false, err) result — and since the count hook resets its      */
/* countdown before firing (Lua 5.4 resethookcount), each trip was         */
/* self-catching and self-resetting: unbounded budget evasion. The trip    */
/* now raises a host-owned sentinel VALUE (break_lua_budget_hook), and     */
/* these wrappers re-raise it uninspected; every OTHER error behaves       */
/* exactly like the base functions. The sentinel is never observable from  */
/* scripts: it is never returned and never passed to an xpcall handler.    */
/* Both reach the runtime through the extraspace like the other closures.  */
/* ---------------------------------------------------------------------- */

static int break_lua_sandbox_pcall(lua_State *L)
{
    BreakLuaRuntime *runtime = *(BreakLuaRuntime **)lua_getextraspace(L);
    int status;
    (void)runtime;
    luaL_checkany(L, 1);
    status = lua_pcallk(L, lua_gettop(L) - 1, LUA_MULTRET, 0, 0, NULL);
    /* [results...] or [errobj] */
    if (status != LUA_OK) {
        if (break_lua_is_budget_trip_error(L, -1)) {
            return lua_error(L); /* re-raise the sentinel: uncatchable */
        }
        lua_pushboolean(L, 0);
        lua_insert(L, -2); /* [false, errobj] */
        return 2;
    }
    lua_pushboolean(L, 1);
    lua_insert(L, 1); /* [true, results...] */
    return lua_gettop(L);
}

static int break_lua_sandbox_xpcall(lua_State *L)
{
    BreakLuaRuntime *runtime = *(BreakLuaRuntime **)lua_getextraspace(L);
    int n = lua_gettop(L);
    int status;
    (void)runtime;
    /* Same shape check as base xpcall — and NOTHING else: base checks only
     * the handler argument, so xpcall() with zero arguments reports
     * "bad argument #2 (function expected, got no value)", never #1. */
    luaL_checktype(L, 2, LUA_TFUNCTION);
    /* [f, handler, args...] -> [f, handler, f, args...]: the callee+args go
     * on top (the base function's rotate, minus its pre-pushed status).
     * Call with NO VM-registered handler: the base errfunc would receive
     * the sentinel (pre-unwind), making it script-observable. The script
     * handler below is invoked by US after the pcall returns, and only for
     * ordinary errors. Running the handler post-unwind (base: pre-unwind)
     * is an accepted, documented difference: the sandbox's only
     * stack-relative operation is error(msg, level)'s position prefix (the
     * debug library is absent). Levels resolving at or above the handler
     * frame — and its immediate caller, a C frame on BOTH sides (base sees
     * the triggering error() C frame, the wrapper sees its own) — are
     * identical; the first frame that DIFFERS is one level deeper, where
     * base walks the not-yet-unwound error chain (the callee's error line)
     * and the wrapper walks the xpcall call site. The residue is
     * position-prefix content only: message text, result values, and
     * catchability are bit-identical to base. One further accepted
     * difference: base reaches LUA_ERRERR by re-entering the handler
     * recursively until the C call depth caps out (observed: 216
     * invocations), while this wrapper invokes an erroring handler
     * exactly once; results and catchability still match, and the
     * wrapper direction is strictly more bounded. */
    lua_pushvalue(L, 1);      /* [f, handler, args..., f] */
    lua_rotate(L, 3, 1);      /* [f, handler, f, args...] */
    status = lua_pcallk(L, n - 2, LUA_MULTRET, 0, 0, NULL);
    /* [f, handler, results...] or [f, handler, errobj] */
    if (status != LUA_OK) {
        if (break_lua_is_budget_trip_error(L, -1)) {
            return lua_error(L); /* re-raise: handler never sees it */
        }
        lua_pushvalue(L, 2);  /* [.. errobj handler] */
        lua_insert(L, -2);    /* [.. handler errobj] */
        status = lua_pcall(L, 1, 1, 0); /* handler(errobj), protected */
        if (status != LUA_OK) {
            /* [.. herr]: an ordinary handler error is absorbed by xpcall
             * itself, exactly like base (LUA_ERRERR maps to the literal
             * below in luaD_seterrorobj); a looping handler trips the armed
             * count hook again, and THAT error is the sentinel — re-raised,
             * never absorbed (the round-4 property). */
            if (break_lua_is_budget_trip_error(L, -1)) {
                return lua_error(L); /* re-raise: trips stay uncatchable */
            }
            lua_pop(L, 1);    /* discard the handler's error object */
            lua_pushliteral(L, "error in error handling");
        }
        /* [.. result] */
        lua_pushboolean(L, 0);
        lua_insert(L, -2);    /* [.. false result] */
        return 2;
    }
    lua_pushboolean(L, 1);
    lua_insert(L, 3);         /* [f, handler, true, results...] */
    return lua_gettop(L) - 2; /* skip f and handler */
}

/* ---------------------------------------------------------------------- */
/* Sandbox construction (bootstrap) and module environment wiring.         */

/* Pushes a fresh read-through proxy for the impl table at the given index:
 * an empty table whose metatable __index names the impl, whose __newindex
 * raises, and whose metatable is locked. The proxy's metatable keeps the
 * impl alive, so the impl itself needs no other anchor. */
static void break_lua_push_readonly_proxy(lua_State *L, int impl_index)
{
    impl_index = lua_absindex(L, impl_index);
    lua_newtable(L);                        /* proxy */
    lua_newtable(L);                        /* proxy mt */
    lua_pushvalue(L, impl_index);           /* proxy mt impl */
    lua_setfield(L, -2, "__index");         /* proxy mt */
    lua_pushcfunction(L, break_lua_readonly_newindex);
    lua_setfield(L, -2, "__newindex");      /* proxy mt */
    lua_pushboolean(L, 0);
    lua_setfield(L, -2, "__metatable");     /* locked */
    lua_setmetatable(L, -2);                /* proxy */
}

/* Copies base global `name` into the sandbox table under the same key. */
static void break_lua_sandbox_copy(lua_State *L, int global_index,
                                   int sandbox_index, const char *name)
{
    lua_getfield(L, global_index, name);
    lua_setfield(L, sandbox_index, name);
}

/* Installs a read-through proxy of the base global table `name` into the
 * sandbox table under the same key. */
static void break_lua_sandbox_proxy_of_global(lua_State *L, int global_index,
                                              int sandbox_index,
                                              const char *name)
{
    lua_getfield(L, global_index, name);    /* real table */
    break_lua_push_readonly_proxy(L, -1);   /* real proxy */
    lua_setfield(L, sandbox_index, name);   /* real */
    lua_pop(L, 1);
}

void break_lua_binding_bootstrap(lua_State *L, BreakLuaRuntime *runtime)
{
    /* pcall/xpcall are deliberately NOT copied by reference: the sandbox
     * installs the budget-transparent wrappers instead (NEW-C4). */
    static const char *const kBaseNames[] = {
        "assert", "error", "ipairs", "pairs", "select",
        "tonumber", "tostring", "type", "print", "_VERSION",
    };
    static const char *const kProxiedLibs[] = {
        "string", "table", "math", "utf8",
    };
    int base = lua_gettop(L);
    int global;
    int impl_os;
    int impl_break;
    int proxy_break;
    int sandbox;
    usize i;

    lua_pushglobaltable(L);
    global = lua_gettop(L);

    /* os subset: a fresh table carrying exactly clock/time/date from the
     * real os library (everything else — execute/exit/remove/rename/
     * getenv/setlocale/tmpname — is absent by construction). */
    lua_newtable(L);
    impl_os = lua_gettop(L);
    lua_getfield(L, global, "os");              /* real os */
    lua_getfield(L, -1, "clock");
    lua_setfield(L, impl_os, "clock");
    lua_getfield(L, -1, "time");
    lua_setfield(L, impl_os, "time");
    lua_getfield(L, -1, "date");
    lua_setfield(L, impl_os, "date");
    lua_pop(L, 1);                              /* real os */

    /* break impl chain: impl tables stay in Lua only through their proxies'
     * metatables (registry-anchored via the sandbox below); scripts meet
     * only the proxies. */
    lua_newtable(L);
    impl_break = lua_gettop(L);

    lua_newtable(L);                            /* impl ecs */
    lua_pushcfunction(L, break_lua_ecs_spawn_cb);
    lua_setfield(L, -2, "spawn");
    lua_pushcfunction(L, break_lua_ecs_set_cb);
    lua_setfield(L, -2, "set");
    break_lua_push_readonly_proxy(L, -1);       /* proxy ecs */
    lua_setfield(L, impl_break, "ecs");         /* impl ecs stays anchored */
    lua_pop(L, 1);                              /* drop impl ecs name */

    lua_newtable(L);                            /* impl config */
    lua_pushcfunction(L, break_lua_config_get_cb);
    lua_setfield(L, -2, "get");
    break_lua_push_readonly_proxy(L, -1);       /* proxy config */
    lua_setfield(L, impl_break, "config");
    lua_pop(L, 1);                              /* drop impl config name */

    break_lua_push_readonly_proxy(L, impl_break);
    proxy_break = lua_gettop(L);

    /* The whitelist table: base functions by reference (immutable values),
     * libraries as read-through proxies. Everything not copied here is
     * absent from module environments (see break_lua.h MODULE SANDBOX). */
    lua_newtable(L);
    sandbox = lua_gettop(L);
    for (i = 0u; i < sizeof(kBaseNames) / sizeof(kBaseNames[0]); i++) {
        break_lua_sandbox_copy(L, global, sandbox, kBaseNames[i]);
    }
    /* Budget-transparent pcall/xpcall wrappers (C closures; the runtime
     * reaches them via the extraspace like every other binding). */
    lua_pushcfunction(L, break_lua_sandbox_pcall);
    lua_setfield(L, sandbox, "pcall");
    lua_pushcfunction(L, break_lua_sandbox_xpcall);
    lua_setfield(L, sandbox, "xpcall");
    for (i = 0u; i < sizeof(kProxiedLibs) / sizeof(kProxiedLibs[0]); i++) {
        break_lua_sandbox_proxy_of_global(L, global, sandbox, kProxiedLibs[i]);
    }
    break_lua_push_readonly_proxy(L, impl_os);
    lua_setfield(L, sandbox, "os");
    lua_pushvalue(L, proxy_break);
    lua_setfield(L, sandbox, "break");
    /* `break` is a reserved Lua keyword, so the literal `break.ecs.spawn()`
     * from the design brief is not spellable Lua syntax; scripts reach the
     * identical proxy through the `brk` alias (or `_G["break"]`). */
    lua_pushvalue(L, proxy_break);
    lua_setfield(L, sandbox, "brk");

    /* The registry reference anchors the whole sandbox graph for the
     * runtime's lifetime; lua_close tears it down. */
    runtime->sandbox_ref = luaL_ref(L, LUA_REGISTRYINDEX);
    lua_settop(L, base);
}

void break_lua_sandbox_wire_env(lua_State *L, BreakLuaRuntime *runtime)
{
    /* Module environment on the top of the stack. Reads of whitelisted
     * names resolve through the metatable (they are deliberately NOT raw
     * env fields, keeping the Task 3 raw-field call rule intact); writes of
     * new globals land raw in the env (chunk-private, die with the env). */
    lua_newtable(L);                                         /* env mt */
    lua_rawgeti(L, LUA_REGISTRYINDEX, runtime->sandbox_ref); /* env mt wl */
    lua_setfield(L, -2, "__index");                          /* env mt */
    lua_setmetatable(L, -2);                                 /* env */
    /* _G names the module's own environment (sandbox idiom), never the
     * base global table. */
    lua_pushliteral(L, "_G");
    lua_pushvalue(L, -2);                                    /* env "_G" env */
    lua_rawset(L, -3);                                       /* env */
}
