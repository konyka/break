#pragma once

/* Internal to the break_lua library: shared by break_lua_runtime.c,
 * break_lua_module.c, break_lua_value.c, and break_lua_binding.c. NOT
 * public ABI — never installed for consumers, never included by public
 * headers. The public surface stays break_lua.h alone. */

#include <script/break_lua.h>

#include <core/platform_thread.h>

#include <lua/lua.h>

/* One registry slot per module. The environment table (holding the chunk's
 * globals and the `state` field) is the only Lua-side reference a slot
 * needs: the persistent state table stays reachable through the live
 * environment, so no second registry ref exists to leak. hooks_disabled is
 * the Task 3 runaway-module mark: set when a frame hook trips the
 * instruction budget, cleared by the next committed reload. */
typedef struct BreakLuaModule {
    char *name;    /* owned copy (bounded by BREAK_LUA_MAX_MODULE_NAME_BYTES) */
    u32 version;   /* 1 at first load; +1 per committed reload */
    u64 hash;      /* FNV-1a-64 of the live source bytes */
    int env_ref;   /* LUA_REGISTRYINDEX reference to the module environment */
    bool occupied;
    bool hooks_disabled;
} BreakLuaModule;

/* Bounded diagnostic for the most recent frame-hook fault (Task 3). Fixed
 * storage: the message copy truncates to fit, never allocates. */
typedef struct BreakLuaFrameError {
    bool valid;            /* at least one fault has been recorded */
    u64 frame_seq;         /* begin_frame sequence number of the last fault */
    bool budget;           /* last fault was an instruction-budget trip */
    bool dispatch_failure; /* last fault was dispatch-level (e.g. OOM inside
                            * the snapshot/dispatch itself), not a module hook */
    char module[BREAK_LUA_MAX_MODULE_NAME_BYTES];
    char hook[16];         /* "on_frame_begin" / "on_frame_end" */
    char message[128];     /* truncated Lua error text */
} BreakLuaFrameError;

/* One bound config entry (Task 4). The value is clamped to
 * [min_value, max_value] at bind time; scripts read `value` verbatim. */
typedef struct BreakLuaConfigSlot {
    char key[BREAK_LUA_MAX_CONFIG_KEY_BYTES]; /* NUL-terminated */
    double min_value;
    double max_value;
    double value; /* clamped initial */
} BreakLuaConfigSlot;

struct BreakLuaRuntime {
    lua_State *L;
    PlatformThreadId owner;
    u32 max_modules;
    u32 max_values;
    usize max_module_bytes;
    u64 instruction_budget;
    BreakLuaModule *modules; /* owned array of max_modules slots */
    u32 module_count;
    int op_ref;              /* registry ref to the protected op dispatch
                              * closure (set at create bootstrap) */
    u64 frame_seq;           /* begin_frame counter (diagnostics) */
    u64 frame_error_total;   /* lifetime count of frame hook faults */
    bool budget_tripped;     /* set by the budget hook callback while armed */
    u64 budget_trip_total;   /* lifetime count of budget trips (public
                              * diagnostic via
                              * break_lua_runtime_budget_trip_count) */
    /* Budget-trip sentinel identity: the error VALUE raised by the count
     * hook is a lightuserdata naming THIS FIELD'S ADDRESS (host-owned,
     * per-runtime). Scripts cannot construct, obtain, or compare it — no
     * lightuserdata-producing API exists in the sandbox, and the sandboxed
     * pcall/xpcall re-raise it uninspected (break_lua_binding.c), so a trip
     * always propagates to the host-side catcher (fix round 4, NEW-C4:
     * script pcall used to catch the plain-string trip, and
     * resethookcount re-armed the countdown — self-catching evasion). */
    u32 budget_sentinel;
    BreakLuaFrameError last_frame_error;
    /* Task 4: host bindings and sandbox. sandbox_ref names the per-runtime
     * whitelist table (registry-held, never script-reachable); batch is a
     * BORROWED host object (never owned, never pushed into Lua); configs is
     * a lazily allocated owned array of BREAK_LUA_MAX_CONFIG_BINDINGS slots. */
    int sandbox_ref;
    BreakLuaEcsBatch *batch;      /* borrowed; NULL until bound */
    BreakLuaConfigSlot *configs;  /* owned; NULL until first bind_config */
    u32 config_count;
    /* Function-reference handles (Stage 4 Phase 3): fixed slot table; a used
     * slot pins its function value in the Lua registry (fn_refs[i] >= 0,
     * a luaL_ref). calloc zeroes fn_ref_used; lua_close releases every pin
     * wholesale. */
    int fn_refs[BREAK_LUA_MAX_FN_REFS];
    bool fn_ref_used[BREAK_LUA_MAX_FN_REFS];
};

/* Protected op dispatch (shared by module load/reload, calls, and frame
 * hooks). Every op ctx struct EMBEDS BreakLuaOpHeader first; the dispatch
 * closure switches on hdr.op. All ctx storage is caller stack: the
 * lightuserdata push cannot allocate, so nothing on the dispatch path runs
 * outside the wrapper's lua_pcall. */
#define BREAK_LUA_OP_STAGE 1
#define BREAK_LUA_OP_COMMIT 2
#define BREAK_LUA_OP_CALL 3
#define BREAK_LUA_OP_FRAME 4
#define BREAK_LUA_OP_REF_FN 5
#define BREAK_LUA_OP_UNREF_FN 6
#define BREAK_LUA_OP_CALL_REF 7
#if defined(BREAK_LUA_TESTING)
#define BREAK_LUA_OP_TEST_RELOADER 8
#endif

#define BREAK_LUA_FRAME_PHASE_BEGIN 1
#define BREAK_LUA_FRAME_PHASE_END 2

typedef struct BreakLuaOpHeader {
    int op;                /* BREAK_LUA_OP_* */
    BreakLuaError status;  /* out: operation result */
    u32 error_line;        /* out: source line parsed from the error text
                            * (module ops; 0 for the other ops) */
    char error[128];       /* out: truncated propagated Lua error text */
} BreakLuaOpHeader;

typedef struct BreakLuaModuleOpCtx {
    BreakLuaOpHeader hdr;
    const char *module_name; /* borrowed, validated caller name */
    const void *source;
    usize source_size;
    char chunkname[BREAK_LUA_MAX_MODULE_NAME_BYTES + 2u]; /* "@name" */
    int old_env_ref;       /* in: live env to reuse state/hook from */
    int new_env_ref;       /* out: staged env (STAGE) / in: discard or keep
                            * (COMMIT); LUA_NOREF until taken */
    bool committed;        /* out: COMMIT swapped the live environment */
} BreakLuaModuleOpCtx;

typedef struct BreakLuaCallOpCtx {
    BreakLuaOpHeader hdr;
    int env_ref;               /* in: live module env */
    const char *function_name; /* borrowed, validated */
    const BreakLuaValue *args; /* borrowed */
    usize arg_count;
    BreakLuaValue *returns;    /* borrowed caller buffer, NIL-prefilled */
    usize return_capacity;
} BreakLuaCallOpCtx;

typedef struct BreakLuaFrameOpCtx {
    BreakLuaOpHeader hdr;
    int phase;              /* BREAK_LUA_FRAME_PHASE_* */
    double delta_seconds;   /* begin phase only */
} BreakLuaFrameOpCtx;

/* REF_FN: pin a chunk-defined raw env function field into the registry
 * (env_ref/function_name in; lua_ref out). UNREF_FN: release a registry pin
 * (lua_ref in). Both run under the shared op pcall: luaL_ref may allocate. */
typedef struct BreakLuaFnRefOpCtx {
    BreakLuaOpHeader hdr;
    int env_ref;               /* in: live module env (REF_FN) */
    const char *function_name; /* in: borrowed, validated (REF_FN) */
    int lua_ref;               /* out (REF_FN) / in (UNREF_FN) */
} BreakLuaFnRefOpCtx;

/* CALL_REF: invoke a pinned function by its registry ref with the same
 * marshalling contract as BreakLuaCallOpCtx. */
typedef struct BreakLuaCallRefOpCtx {
    BreakLuaOpHeader hdr;
    int lua_ref;               /* in: pinned function's registry ref */
    const BreakLuaValue *args; /* borrowed */
    usize arg_count;
    BreakLuaValue *returns;    /* borrowed caller buffer, NIL-prefilled */
    usize return_capacity;
} BreakLuaCallRefOpCtx;

#if defined(BREAK_LUA_TESTING)
typedef struct BreakLuaTestReloaderOpCtx {
    BreakLuaOpHeader hdr;
    int env_ref;           /* in: module env to receive the binding */
    BreakLuaRuntime *runtime;
    const char *target_module; /* borrowed */
    const void *source;        /* borrowed */
    usize source_size;
} BreakLuaTestReloaderOpCtx;
#endif

/* break_lua_module.c internals consumed by the other library TUs. */

/* Registers the protected op dispatch closure in the Lua registry and
 * stores the runtime pointer in the state's extraspace (so the budget hook
 * callback can reach it allocation-free). Called from the create bootstrap
 * wrapper, i.e. already under lua_pcall: the cclosure allocation here can
 * longjmp safely. */
void break_lua_op_bootstrap(lua_State *L, BreakLuaRuntime *runtime);

/* Runs one op under pcall protection via the registered dispatch closure.
 * The rawgeti fetch and the lightuserdata push cannot allocate, so nothing
 * here is exposed to a Lua longjmp outside the pcall. An error that
 * propagated out of the op (chunk failure, LUA_ERRMEM) is mapped into
 * hdr->status and captured bounded into hdr->error. */
BreakLuaError break_lua_op_run(BreakLuaRuntime *runtime,
                               BreakLuaOpHeader *hdr);

/* Bounded copy of the Lua error object at the top of the stack into `out`
 * (NUL-terminated, truncated to out_cap), then pops it. Allocation-free on
 * the Lua side: strings are read in place, numbers are formatted with
 * snprintf, any other object type maps to a fixed fallback text. Safe to
 * run outside a pcall recovery point. */
void break_lua_op_take_error(lua_State *L, char *out, usize out_cap);

/* Bounded name scan: no libc strnlen (C11 strict), never reads past cap.
 * Returns cap when no NUL is found within cap bytes. */
usize break_lua_name_len(const char *name, usize cap);

/* Registry lookup by name; NULL when no live module has it. */
BreakLuaModule *break_lua_module_find(BreakLuaRuntime *runtime,
                                      const char *name);

/* Frees every owned module name and the registry array. Pure C: makes no
 * Lua API calls, so it is safe to run immediately before lua_close (which
 * then tears down every remaining registry reference at once). */
void break_lua_module_registry_destroy(BreakLuaRuntime *runtime);

/* Budget-trip sentinel helpers (fix round 4). The sentinel value is the
 * ADDRESS of the runtime's budget_sentinel field — host-owned, never
 * script-reachable. */
static inline void *break_lua_budget_sentinel_ptr(BreakLuaRuntime *runtime) {
    return (void *)&runtime->budget_sentinel;
}

/* Identity check for the budget-trip error value on the Lua stack. Reaches
 * the runtime through the extraspace (set at bootstrap; allocation-free). */
static inline bool break_lua_is_budget_trip_error(lua_State *L, int idx) {
    BreakLuaRuntime *runtime =
        *(BreakLuaRuntime **)lua_getextraspace(L);
    return runtime && lua_type(L, idx) == LUA_TLIGHTUSERDATA &&
           lua_touserdata(L, idx) == break_lua_budget_sentinel_ptr(runtime);
}

/* break_lua_value.c implementations consumed by the dispatch closure. */
void break_lua_call_impl(lua_State *L, BreakLuaCallOpCtx *ctx);
void break_lua_call_ref_impl(lua_State *L, BreakLuaCallRefOpCtx *ctx);
void break_lua_frame_impl(lua_State *L, BreakLuaRuntime *runtime,
                          BreakLuaFrameOpCtx *ctx);

/* Count-hook callback for the instruction budget (defined in
 * break_lua_value.c): raises "break_lua: instruction budget exceeded" into
 * the nearest pcall and sets runtime->budget_tripped. Shared by the frame
 * dispatch and the module staging / on_unload paths (break_lua_module.c).
 * Arm with lua_sethook(L, break_lua_budget_hook, LUA_MASKCOUNT, count) and
 * ALWAYS disarm after the protected call — the hook is per-coroutine
 * state that must not leak past the operation. */
void break_lua_budget_hook(lua_State *L, lua_Debug *ar);
#if defined(BREAK_LUA_TESTING)
void break_lua_test_reloader_impl(lua_State *L,
                                  BreakLuaTestReloaderOpCtx *ctx);
#endif

/* break_lua_binding.c internals consumed by the other library TUs (Task 4).
 */

/* Builds the registry-held binding/sandbox structures (os-subset table,
 * break impl tables, read-through proxies, whitelist table) and stores the
 * whitelist in runtime->sandbox_ref. Called from the create bootstrap
 * wrapper, i.e. already under lua_pcall: allocations here longjmp safely. */
void break_lua_binding_bootstrap(lua_State *L, BreakLuaRuntime *runtime);

/* Wires the fresh module environment on the top of the stack to the
 * sandbox: metatable __index -> whitelist table, plus `_G` naming the
 * environment itself. Runs inside the staging op (pcall-protected). */
void break_lua_sandbox_wire_env(lua_State *L, BreakLuaRuntime *runtime);

/* Pure C teardown (no Lua API): releases the borrowed batch binding (clears
 * the batch's back-pointer; the batch itself stays host-owned) and frees
 * the config store. Safe to run immediately before lua_close. */
void break_lua_binding_shutdown(BreakLuaRuntime *runtime);
