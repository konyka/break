#pragma once

/* Internal to the break_lua library: shared by break_lua_runtime.c,
 * break_lua_module.c, and break_lua_value.c. NOT public ABI — never
 * installed for consumers, never included by public headers. The public
 * surface stays break_lua.h alone. */

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
    BreakLuaFrameError last_frame_error;
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
#if defined(BREAK_LUA_TESTING)
#define BREAK_LUA_OP_TEST_RELOADER 5
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

/* break_lua_value.c implementations consumed by the dispatch closure. */
void break_lua_call_impl(lua_State *L, BreakLuaCallOpCtx *ctx);
void break_lua_frame_impl(lua_State *L, BreakLuaRuntime *runtime,
                          BreakLuaFrameOpCtx *ctx);
#if defined(BREAK_LUA_TESTING)
void break_lua_test_reloader_impl(lua_State *L,
                                  BreakLuaTestReloaderOpCtx *ctx);
#endif
