/* BreakEditorLuaConsole — implementation. The full contract (owner thread,
 * eval pipeline, injection-safety layers, budget arming, outcome channel
 * integrity, record application, bounds) is documented in editor_lua.h. */

#include <editor/editor_lua.h>

#include <editor/editor_cmd.h>
#include <editor/editor_components.h>
#include <editor/editor_test_hooks.h>

#include <core/platform_thread.h>
#include <script/break_lua.h>

#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

/* Two runtimes (fix round 1): the CONSOLE runtime owns the batch binding and
 * stages only probe-verified harness chunks (user code on it runs solely
 * inside the budgeted frame dispatch); the PROBE runtime has NO batch bound,
 * so even a crafted escape that reaches probe staging cannot enqueue ECS
 * records — its worst side effect is a bounded stdout print. Both runtimes
 * are lazily recreated when lost (fix round 3 — symmetric recovery paths;
 * see editor_lua.h). Each eval is a committed reload of the touched
 * modules, so evals share no environment state. */
#define CONSOLE_MODULE "console"
#define PROBE_MODULE "probe_r"

/* Chunk size bound: prefixes/suffixes are fixed small strings; the body is
 * "return " (7) + input (<= 4096). */
#define CONSOLE_CHUNK_CAPACITY 5632u

/* INJECTION SAFETY — the REAL layers (fix round 2, N1; the round-1
 * "dual-probe disjointness" claim was false and probe L was dropped: a
 * `local p = function() <B> end` wrapper is expression context too and adds
 * nothing over the harness's own compile):
 *   - The harness embeds the body in a STATEMENT context
 *     (`local function __body() <B> end`). A body that closes the function
 *     early must continue with either a STATEMENT (e.g. `end while true
 *     do`) or an EXPRESSION continuation (e.g. the review's C1 payload
 *     `end .. (function() while true do end end)() .. function() return
 *     0`); the harness compile itself rejects every expression continuation
 *     (a statement cannot start with an operator), so those bodies fail the
 *     console-module reload with a plain syntax error before anything runs.
 *   - The probe answers the remaining question — could the body escape as
 *     a STATEMENT sequence? — by compiling `return function() <B> end` on
 *     the probe runtime: nothing may follow a return, so statement
 *     continuations fail the probe compile. Together: a body passing the
 *     probe AND embedding cleanly in the harness is a syntactically
 *     complete block; the console runtime never stages user code.
 *   - A body that escapes ONLY the probe (expression continuation) is
 *     staged once on the probe runtime — budgeted (break_lua arms the count
 *     hook over staging since fix round 1) and batch-free, so it can neither
 *     hang nor touch the doc — and is then rejected by the harness compile.
 *   - Both runtimes carry the 1e6 staging budget as defense in depth.
 * The body starts on probe line 2. */
#define PROBE_PREFIX "return function()\n"
#define PROBE_PREFIX_LINES 1u
#define PROBE_SUFFIX "\nend\n"

/* The console harness (fix round 3: LEXICAL ISOLATION). __body is the only
 * chunk-top local, so the body — lexically nested inside __body's own
 * definition — sees NOTHING of the harness: every harness local lives in
 * the `do ... end` block that FOLLOWS __body's definition, a scope the body
 * is lexically outside of. Body assignments like `__tostring = ...` or
 * `__DONE = true` therefore create/overwrite ENV fields, never the harness
 * locals (fix round 1/2's shared-chunk-scope upvalue channel — NEW-C1/C2 —
 * is closed). The body's ONLY visible harness upvalue is __body itself;
 * overwriting it mid-run is harmless (the running call is unaffected and
 * the harness never references it again after the pcall invocation).
 *
 * Inside the block: stdlib captured as locals at staging time (before the
 * body runs — env shadowing cannot reach them, fix round 2), print capture
 * (32 lines x 127 visible bytes), on_frame_begin running __body under the
 * armed count hook inside __pcall, the epilogue clearing on_unload /
 * on_frame_end on every path (veto wedge impossible; a body-defined
 * on_frame_end never dispatches), and the outcome markers: __DONE is false
 * at chunk top and set true only as the hook's LAST statement; __E holds a
 * sentinel until the hook's first statement clears it and is then set only
 * from the body pcall's failure. eval_ok = (__DONE && __E empty) — a
 * harness that dies anywhere leaves __DONE false and the eval fails CLOSED
 * (records discarded), never a false success (N2).
 *
 * BUDGET-TRIP TRANSPARENCY (fix round 4, NEW-C4): since fix round 4 the
 * sandboxed pcall RE-RAISES the trip sentinel instead of returning it —
 * the harness's __pcall is that wrapper, so a trip is NOT caught in Lua:
 * on_frame_begin dies, the per-hook pcall in the frame dispatch catches
 * the sentinel, the module is marked hooks-disabled (Stage 3 runaway
 * policy — cleared by the next eval's committed reload, which is why the
 * console survives), and the C side recognizes the trip via the
 * break_lua_runtime_budget_trip_count delta across the dispatch. The
 * epilogue does NOT run on a trip, so a body that set on_unload before
 * looping would wedge the NEXT reload — closed by the pinned
 * __console_cleanup called pre-reload every eval (below).
 *
 * The getter functions ARE env fields (runtime visibility), but the host
 * never calls them by name after the body ran: their function VALUES are
 * pinned via break_lua_runtime_ref_function after the reload commits and
 * BEFORE the dispatch (the body cannot have run yet), and invoked through
 * break_lua_runtime_call_ref — a body overwrite of the env fields
 * substitutes nothing (NEW-C3 closed). __console_cleanup is pinned the
 * same way and kept ACROSS evals: each eval calls the PREVIOUS env's
 * pinned cleanup (clearing on_unload/on_frame_end there) before its
 * reload, so even a trip that skipped the epilogue cannot carry a veto
 * into the next commit; the console-runtime health check + recreate stays
 * as the backstop. */
#define HARNESS_PREFIX                                              \
    "local function __body()\n"
#define HARNESS_SUFFIX                                              \
    "\nend\n"                                                       \
    "do\n"                                                          \
    "  local __pcall=pcall\n"                                       \
    "  local __tostring=tostring\n"                                 \
    "  local __type=type\n"                                         \
    "  local __select=select\n"                                     \
    "  local __concat=table.concat\n"                               \
    "  local __unpack=table.unpack\n"                               \
    "  local __L={}\n"                                              \
    "  local __R=nil\n"                                             \
    "  local __E='console internal: eval dispatch did not run'\n"   \
    "  local __DONE=false\n"                                        \
    "  print=function(...)\n"                                       \
    "    local n=__select('#',...)\n"                               \
    "    if #__L<32 then\n"                                         \
    "      local p={}\n"                                            \
    "      for i=1,n do p[i]=__tostring(__select(i,...)) end\n"     \
    "      local s=__concat(p,'\\t')\n"                             \
    "      if #s>127 then s=s:sub(1,127) end\n"                     \
    "      __L[#__L+1]=s\n"                                         \
    "    end\n"                                                     \
    "  end\n"                                                       \
    "  function on_frame_begin(dt)\n"                               \
    "    __E=nil\n"                                                 \
    "    local ok,r=__pcall(__body)\n"                              \
    "    if ok then\n"                                              \
    "      if __type(r)=='string' and #r>127 then r=r:sub(1,127) end\n" \
    "      __R=r\n"                                                 \
    "    else\n"                                                    \
    "      local e=__tostring(r)\n"                                 \
    "      if #e>120 then e=e:sub(1,120) end\n"                     \
    "      __E=e\n"                                                 \
    "    end\n"                                                     \
    "    on_unload=nil\n"                                           \
    "    on_frame_end=nil\n"                                        \
    "    __DONE=true\n"                                             \
    "  end\n"                                                       \
    "  function __console_err() return __DONE, __E end\n"           \
    "  function __console_lines() return __unpack(__L) end\n"       \
    "  function __console_result() return __R end\n"                \
    "  function __console_cleanup() on_unload=nil on_frame_end=nil end\n" \
    "end\n"

struct BreakEditorLuaConsole {
    BreakEditorDoc *doc; /* borrowed; must outlive the console */
    BreakEditorLuaLogFn log_fn;
    void *log_ctx;
    PlatformThreadId owner;         /* creating thread; runtime-liveness-
                                     * independent (survives a lost runtime) */
    BreakLuaRuntime *runtime;       /* owned; owns the batch binding; NULL
                                     * after an unrecoverable loss (lazy
                                     * re-init on next eval) */
    BreakLuaRuntime *probe_runtime; /* owned; NO batch bound (probe-only);
                                     * same lazy re-init policy */
    BreakLuaEcsBatch *batch;        /* owned (bound to runtime) */
    /* Pinned __console_cleanup of the LIVE console env (called pre-reload
     * every eval to clear any body-set on_unload/on_frame_end there — the
     * trip path skips the harness epilogue, fix round 4). UINT32_MAX when
     * none (pin died with a destroyed runtime). */
    u32 cleanup_ref;
    /* Fixed scratch for the post-eval drain; the batch default capacity is
     * 256, so one drain empties it. Keeping it here means eval allocates
     * nothing (the struct is the single editor-owned allocation). */
    BreakLuaEcsRecord drain[BREAK_LUA_ECS_BATCH_DEFAULT_CAPACITY];
};

/* Every line the console emits flows through here: the 128-byte rule is
 * enforced by the bounded vsnprintf (truncation at 127 visible bytes). */
static void console_log(const BreakEditorLuaConsole *c, const char *fmt, ...) {
    char line[128];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(line, sizeof(line), fmt, ap);
    va_end(ap);
    line[sizeof(line) - 1u] = '\0'; /* defensive; vsnprintf terminates */
    c->log_fn(c->log_ctx, line);
}

static bool console_is_owner(const BreakEditorLuaConsole *c) {
    return platform_thread_id_equal(platform_thread_current_id(), c->owner);
}

/* Logs a Lua error message as "error: line M: <rest>" when it carries the
 * standard "<chunkname>:N: " position prefix and N is past the host-side
 * wrapper (offset = wrapper lines before the body, so M is the
 * input-relative line); otherwise "error: <raw>" — the raw fallback covers
 * position-less messages such as the budget-trip canonical text (the
 * sentinel value is raised bare via lua_error, fix round 4). Bounded by
 * console_log. */
static void console_log_lua_error(const BreakEditorLuaConsole *c,
                                  const char *raw, u32 line_offset) {
    const char *colon = strchr(raw, ':');
    if (colon) {
        const char *p = colon + 1;
        u32 line = 0u;
        bool digits = false;
        while (*p >= '0' && *p <= '9') {
            u32 d = (u32)(*p - '0');
            if (line > (1000000000u - d) / 10u) { /* u32 overflow guard */
                digits = false;
                break;
            }
            line = line * 10u + d;
            digits = true;
            p++;
        }
        if (digits && line > line_offset && p[0] == ':' && p[1] == ' ') {
            console_log(c, "error: line %u: %s", line - line_offset, p + 2);
            return;
        }
    }
    console_log(c, "error: %s", raw);
}

/* Bounded chunk assembly; false when the pieces would not fit (impossible
 * with the input cap and fixed wrappers — fail-closed regardless). */
static bool console_build_chunk(char *out, usize cap, const char *prefix,
                                const char *ret, const char *body,
                                const char *suffix) {
    int n = snprintf(out, cap, "%s%s%s%s", prefix, ret, body, suffix);
    return n >= 0 && (usize)n < cap;
}

/* ---------------------------------------------------------------------- */
/* Runtime lifecycle (create / lazy re-init / wedge recovery).            */

static const char k_console_seed[] = HARNESS_PREFIX "\n" HARNESS_SUFFIX;

/* Creates the console runtime, binds the (existing, host-owned) batch, and
 * seeds the console module. c->runtime must be NULL on entry and stays NULL
 * on failure (fully torn down). */
static bool console_main_runtime_init(BreakEditorLuaConsole *c) {
    BreakLuaRuntimeConfig cfg;
    memset(&cfg, 0, sizeof(cfg));
    cfg.max_modules = 8u;
    cfg.instruction_budget = BREAK_EDITOR_LUA_INSTRUCTION_BUDGET;
    cfg.memory_budget = BREAK_EDITOR_LUA_MEMORY_BUDGET;
    c->runtime = break_lua_runtime_create(&cfg);
    if (!c->runtime) {
        return false;
    }
    if (break_lua_runtime_bind_ecs_batch(c->runtime, c->batch) !=
            BREAK_LUA_OK ||
        break_lua_runtime_load_module(c->runtime, CONSOLE_MODULE,
                                      k_console_seed,
                                      sizeof(k_console_seed) - 1u) !=
            BREAK_LUA_OK) {
        break_lua_runtime_destroy(c->runtime);
        c->runtime = NULL;
        return false;
    }
    return true;
}

/* Creates the probe runtime (no batch is ever bound to it) and seeds the
 * probe module. Same NULL-on-failure discipline. */
static bool console_probe_runtime_init(BreakEditorLuaConsole *c) {
    static const char k_probe_seed[] = "return function() end\n";
    BreakLuaRuntimeConfig cfg;
    memset(&cfg, 0, sizeof(cfg));
    cfg.max_modules = 4u;
    cfg.instruction_budget = BREAK_EDITOR_LUA_INSTRUCTION_BUDGET;
    cfg.memory_budget = BREAK_EDITOR_LUA_MEMORY_BUDGET;
    c->probe_runtime = break_lua_runtime_create(&cfg);
    if (!c->probe_runtime) {
        return false;
    }
    if (break_lua_runtime_load_module(c->probe_runtime, PROBE_MODULE,
                                      k_probe_seed,
                                      sizeof(k_probe_seed) - 1u) !=
        BREAK_LUA_OK) {
        break_lua_runtime_destroy(c->probe_runtime);
        c->probe_runtime = NULL;
        return false;
    }
    return true;
}

/* Pins the live console env's __console_cleanup (fix round 4: called
 * pre-reload every eval to clear any body-set on_unload/on_frame_end there
 * — the budget-trip path skips the harness epilogue). A pin failure leaves
 * cleanup_ref UINT32_MAX: the epilogue clear plus the health-check recreate
 * remain as backstops, so a pin failure degrades, never wedges. The caller
 * guarantees any previous pin belongs to the CURRENT c->runtime. */
static void console_pin_cleanup(BreakEditorLuaConsole *c) {
    if (c->cleanup_ref != UINT32_MAX) {
        (void)break_lua_runtime_unref_function(c->runtime, c->cleanup_ref);
        c->cleanup_ref = UINT32_MAX;
    }
    (void)break_lua_runtime_ref_function(c->runtime, CONSOLE_MODULE,
                                         "__console_cleanup", &c->cleanup_ref);
}

/* Console-runtime recovery (fix round 3, symmetric with the probe side): a
 * vetoing on_unload on the live console env would fail every reload; a
 * Lua-side OOM can lose the runtime outright. Health check = reloading the
 * seed harness (trivial, host-controlled); on failure the runtime is
 * destroyed (releasing the batch binding and every pin — the batch stays
 * host-owned) and recreated+rebound+reseeded. A recreation failure leaves
 * runtime NULL: the next eval re-tries the init at admission and, until
 * then, fails bounded with a "console runtime unavailable" line. */
static void console_main_runtime_reset_if_unhealthy(BreakEditorLuaConsole *c) {
    if (!c->runtime) {
        if (console_main_runtime_init(c)) {
            console_pin_cleanup(c);
        }
        return;
    }
    if (break_lua_runtime_reload_module(c->runtime, CONSOLE_MODULE,
                                        k_console_seed,
                                        sizeof(k_console_seed) - 1u,
                                        NULL) == BREAK_LUA_OK) {
        /* Healthy: the seed reload REPLACED the console env, so the cleanup
         * pin (captured from an older env) is stale — re-pin from the live
         * seed env. The old pin is still valid (pins survive reloads). */
        console_pin_cleanup(c);
        return;
    }
    break_lua_runtime_destroy(c->runtime); /* every pin dies with it */
    c->runtime = NULL;
    c->cleanup_ref = UINT32_MAX;
    if (console_main_runtime_init(c)) {
        console_pin_cleanup(c);
    }
}

/* Probe-runtime recovery: a crafted escape that ran at probe staging could
 * have raw-set a vetoing on_unload on the probe module's env (the wedge
 * class, one level down). A trivial known-good reload answers the question;
 * on veto the whole probe runtime is recreated (it holds no valuable
 * state), so a wedged probe never permanently kills the console. */
static void console_probe_runtime_reset_if_wedged(BreakEditorLuaConsole *c) {
    static const char k_trivial[] = "return function() end\n";
    if (!c->probe_runtime) {
        (void)console_probe_runtime_init(c);
        return;
    }
    if (break_lua_runtime_reload_module(c->probe_runtime, PROBE_MODULE,
                                        k_trivial, sizeof(k_trivial) - 1u,
                                        NULL) == BREAK_LUA_OK) {
        return;
    }
    break_lua_runtime_destroy(c->probe_runtime);
    c->probe_runtime = NULL;
    (void)console_probe_runtime_init(c);
}

/* Compiles one body form ("ret" is "" or "return ") through the probe on
 * the probe runtime. BREAK_LUA_FAILED = syntax/statement-escape rejection;
 * other codes = staging budget trip / OOM / policy. `report` carries the
 * diagnostics. */
static BreakLuaError console_probe_form(BreakEditorLuaConsole *c,
                                        const char *ret, const char *body,
                                        BreakLuaReloadReport *report) {
    char chunk[CONSOLE_CHUNK_CAPACITY];
    if (!console_build_chunk(chunk, sizeof(chunk), PROBE_PREFIX, ret, body,
                             PROBE_SUFFIX)) {
        return BREAK_LUA_FAILED;
    }
    return break_lua_runtime_reload_module(c->probe_runtime, PROBE_MODULE,
                                           chunk, strlen(chunk), report);
}

/* Counts '\n' in a wrapper to derive the body's first line offset. */
static u32 console_count_lines(const char *s) {
    u32 n = 0u;
    for (; *s; s++) {
        if (*s == '\n') n++;
    }
    return n;
}

/* Releases up to three captured function refs (UINT32_MAX = not captured).
 * Owner-thread context; failures are impossible for live captured refs and
 * ignored otherwise (UINT32_MAX is simply invalid). */
static void console_release_refs(BreakEditorLuaConsole *c, u32 *refs,
                                 usize count) {
    usize i;
    for (i = 0u; i < count; i++) {
        if (refs[i] != UINT32_MAX) {
            (void)break_lua_runtime_unref_function(c->runtime, refs[i]);
            refs[i] = UINT32_MAX;
        }
    }
}

/* ---------------------------------------------------------------------- */
/* Record application (successful evals only).                             */

static void console_apply_set(BreakEditorLuaConsole *c,
                              const BreakLuaEcsRecord *rec,
                              BreakEditorEntityId target) {
    BreakEditorComponentInfo info = {0};
    bool found = false;
    u32 field_index = 0u;
    usize count = break_editor_doc_component_count(c->doc);
    usize i;
    u32 k;
    f32 value = 0.0f;
    bool added = false;

    /* Component by registry display name (byte-wise, case-sensitive). */
    for (i = 0u; i < count; i++) {
        if (!break_editor_doc_component_info(c->doc, i, &info)) {
            continue;
        }
        if (strcmp(info.display_name, rec->component) == 0) {
            found = true;
            break;
        }
    }
    if (!found) {
        console_log(c, "error: ecs.set: unknown component '%s'",
                    rec->component);
        return;
    }
    for (k = 0u; k < info.field_count; k++) {
        if (strcmp(info.fields[k].name, rec->field) == 0) {
            field_index = k;
            break;
        }
    }
    if (k >= info.field_count) {
        console_log(c, "error: ecs.set: unknown field '%s' on '%s'",
                    rec->field, rec->component);
        return;
    }
    if (!break_editor_entity_id_valid(target)) {
        console_log(c, "error: ecs.set: no target entity (no spawn this eval)");
        return;
    }
    /* Value conversion BEFORE any mutation: a rejected value leaves the
     * record (and the doc) untouched. */
    switch ((BreakLuaEcsValueKind)rec->value_type) {
    case BREAK_LUA_ECS_VALUE_NUMBER:
        if (!isfinite(rec->value.n)) {
            console_log(c, "error: ecs.set: non-finite value");
            return;
        }
        value = (f32)rec->value.n;
        break;
    case BREAK_LUA_ECS_VALUE_BOOL:
        value = rec->value.b ? 1.0f : 0.0f;
        break;
    case BREAK_LUA_ECS_VALUE_STRING:
        if (!break_editor_parse_f32(rec->value.s.data, &value)) {
            console_log(c, "error: ecs.set: value '%s' is not an f32",
                        rec->value.s.data);
            return;
        }
        break;
    default:
        console_log(c, "error: ecs.set: missing or unsupported value");
        return;
    }
    /* Implicit component add (undoable) so spawn+set is the natural pair. */
    if (!break_editor_doc_has_component(c->doc, target, info.component_id)) {
        if (!break_editor_doc_add_component(c->doc, target,
                                            info.component_id)) {
            console_log(c, "error: ecs.set: cannot add component '%s'",
                        rec->component);
            return;
        }
        added = true;
    }
    if (!break_editor_doc_set_field_f32(c->doc, target, info.component_id,
                                        field_index, value)) {
        /* Never half-apply a record: roll back our own component add. */
        if (added) {
            (void)break_editor_undo(c->doc);
        }
        console_log(c, "error: ecs.set: write rejected");
        return;
    }
}

static void console_apply_records(BreakEditorLuaConsole *c, usize n) {
    BreakEditorEntityId last_spawned = BREAK_EDITOR_ENTITY_NULL;
    usize i;
    for (i = 0u; i < n; i++) {
        const BreakLuaEcsRecord *rec = &c->drain[i];
        switch ((BreakLuaEcsRecordKind)rec->kind) {
        case BREAK_LUA_ECS_RECORD_SPAWN: {
            /* The Stage 3 spawn record carries no name (zeroed payload), so
             * the doc generates one. Exactly one undoable command. */
            BreakEditorEntityId id = break_editor_doc_add_entity(c->doc, NULL);
            if (!break_editor_entity_id_valid(id)) {
                console_log(c, "error: ecs.spawn: rejected (entity cap or OOM)");
            } else {
                last_spawned = id;
            }
            break;
        }
        case BREAK_LUA_ECS_RECORD_SET:
            console_apply_set(c, rec, last_spawned);
            break;
        default:
            console_log(c, "error: ecs record: unknown kind %u",
                        (unsigned)rec->kind);
            break;
        }
    }
}

/* ---------------------------------------------------------------------- */
/* Public surface                                                          */

BreakEditorLuaConsole *break_editor_lua_create(BreakEditorDoc *doc,
                                               BreakEditorLuaLogFn log_fn,
                                               void *log_ctx) {
    BreakEditorLuaConsole *c;
    if (!doc || !log_fn) {
        return NULL;
    }
    /* The struct is the only editor-owned allocation; the runtimes, batch,
     * and seed compiles are break_lua-owned (BREAK_LUA_TESTING hooks). */
    c = (BreakEditorLuaConsole *)break_editor_test_calloc(sizeof(*c));
    if (!c) {
        return NULL;
    }
    c->doc = doc;
    c->log_fn = log_fn;
    c->log_ctx = log_ctx;
    c->owner = platform_thread_current_id();
    c->cleanup_ref = UINT32_MAX;
    c->batch = break_lua_ecs_batch_create(0u); /* 256 default */
    if (!c->batch) {
        free(c);
        return NULL;
    }
    if (!console_main_runtime_init(c) || !console_probe_runtime_init(c)) {
        /* destroy tolerates the partial state (NULL runtimes, live batch,
         * owner already recorded). */
        break_editor_lua_destroy(c);
        return NULL;
    }
    /* Pin the seed harness's cleanup for the first eval's pre-reload call
     * (a pin failure here fails the create: Lua-side OOM under injection). */
    console_pin_cleanup(c);
    if (c->cleanup_ref == UINT32_MAX) {
        break_editor_lua_destroy(c);
        return NULL;
    }
    return c;
}

void break_editor_lua_destroy(BreakEditorLuaConsole *console) {
    if (!console) {
        return;
    }
    /* Owner-thread-only: a non-owner destroy is a contract violation and is
     * ignored (mirrors the break_lua production convention; test builds get
     * the probe coverage through the owner-thread rejection test). The
     * stored owner id keeps this exact even when a runtime was lost. */
    if (!console_is_owner(console)) {
        return;
    }
    if (console->probe_runtime) {
        break_lua_runtime_destroy(console->probe_runtime);
    }
    if (console->runtime) {
        break_lua_runtime_destroy(console->runtime);
    }
    break_lua_ecs_batch_destroy(console->batch);
    free(console);
}

bool break_editor_lua_eval(BreakEditorLuaConsole *console, const char *input) {
    static const char k_return_wrap[] = "return ";
    char chunk[CONSOLE_CHUNK_CAPACITY];
    const char *ret = k_return_wrap;
    u32 refs[3] = {UINT32_MAX, UINT32_MAX, UINT32_MAX};
    BreakLuaReloadReport report;
    BreakLuaError err;
    BreakLuaValue v[BREAK_EDITOR_LUA_MAX_PRINT_LINES];
    BreakLuaValue status[2];
    BreakLuaValue single;
    char eval_err[BREAK_LUA_VALUE_STRING_CAPACITY];
    bool eval_ok = false;
    bool done = false;
    bool tripped = false;
    usize drained = 0u;
    usize i;
    u32 harness_offset;

    if (!console || !input) {
        return false;
    }
    if (!console_is_owner(console)) {
        console_log(console, "error: console: non-owner thread call rejected");
        return false;
    }
    {
        const char *nul =
            memchr(input, '\0', BREAK_EDITOR_LUA_INPUT_MAX_BYTES + 1u);
        if (!nul) {
            console_log(console, "error: input too long (max %u bytes)",
                        (unsigned)BREAK_EDITOR_LUA_INPUT_MAX_BYTES);
            return false;
        }
    }
    /* Lazy re-init of a lost runtime (bounded degradation, never a
     * permanent kill). */
    if (!console->runtime && !console_main_runtime_init(console)) {
        console_log(console, "error: console: console runtime unavailable");
        return false;
    }
    if (!console->probe_runtime && !console_probe_runtime_init(console)) {
        console_log(console, "error: console: probe runtime unavailable");
        return false;
    }

    /* 1. Compile `return <input>` FIRST (the lua.c REPL order): a bare
     *    call like `string.rep('x',2)` parses fine as a STATEMENT, so
     *    as-is-first would never produce its value; return-first makes
     *    every bare expression auto-return, and genuine statements fail the
     *    wrap (return must be last) and fall through to the as-is attempt.
     *    The probe (see INJECTION SAFETY above) rejects exactly the
     *    statement-continuation escapes; expression continuations are
     *    rejected by the harness compile in step 2. */
    err = console_probe_form(console, ret, input, &report);
    if (err != BREAK_LUA_OK) {
        err = console_probe_form(console, "", input, &report);
        ret = ""; /* statement input: staged as-is */
    }
    if (err != BREAK_LUA_OK) {
        /* Report the AS-IS attempt's probe failure (same convention as the
         * standalone lua REPL of reporting the plain-form error): its line
         * numbers match the typed input exactly — the wrap is inline,
         * shifting columns, not lines. */
        console_log_lua_error(console, report.error, PROBE_PREFIX_LINES);
        console_probe_runtime_reset_if_wedged(console);
        return false;
    }

    /* 2. Pre-reload veto clear (fix round 4): the budget-trip path skips
     *    the harness epilogue (the trip is deliberately uncatchable — see
     *    NEW-C4 below), so a body that set on_unload before tripping would
     *    veto THIS reload's commit. Call the PREVIOUS env's pinned cleanup
     *    (captured before that env ever ran — overwrite-proof); failures
     *    are bounded and the health-check recreate stays as the backstop. */
    if (console->cleanup_ref != UINT32_MAX) {
        (void)break_lua_runtime_call_ref(console->runtime,
                                         console->cleanup_ref, NULL, 0u,
                                         NULL, 0u);
        (void)break_lua_runtime_unref_function(console->runtime,
                                               console->cleanup_ref);
        console->cleanup_ref = UINT32_MAX;
    }

    /* 3. Embed the probe-verified body in the console harness and reload.
     *    The harness top level is host-controlled definitions only and its
     *    `local function __body()` statement context rejects any expression
     *    continuation the probe could not see, so console staging never
     *    runs user code (and is budget-armed at the break_lua layer
     *    regardless — defense in depth). */
    if (!console_build_chunk(chunk, sizeof(chunk), HARNESS_PREFIX, ret, input,
                             HARNESS_SUFFIX)) {
        console_log(console, "error: console: chunk assembly overflow");
        return false;
    }
    err = break_lua_runtime_reload_module(console->runtime, CONSOLE_MODULE,
                                          chunk, strlen(chunk), &report);
    if (err != BREAK_LUA_OK) {
        /* Expected rejections: an expression-continuation escape that
         * passed the probe (its staging ran bounded and batch-free on the
         * probe runtime) fails this compile with a plain syntax error.
         * Anything else is harness-internal or OOM. */
        if (report.error[0] != '\0') {
            console_log_lua_error(console, report.error,
                                  console_count_lines(HARNESS_PREFIX));
        } else {
            console_log(console, "error: console: stage failed (%s)",
                        break_lua_error_name(err));
        }
        /* A payload reaching this path may have executed at probe staging
         * (the probe passes expression continuations) and could have
         * planted a vetoing on_unload on the probe module — health-check
         * it here too. The console runtime gets the symmetric check. */
        console_probe_runtime_reset_if_wedged(console);
        console_main_runtime_reset_if_unhealthy(console);
        return false;
    }

    /* 4. Capture the outcome getter function REFERENCES after the commit
     *    and BEFORE the dispatch (the body cannot have run yet); the
     *    outcome channel is read only through these pinned values, so body
     *    overwrites of the getter env fields substitute nothing (NEW-C3).
     *    The cleanup pin is kept in the console struct ACROSS evals (used
     *    by the next eval's pre-reload veto clear). */
    err = break_lua_runtime_ref_function(console->runtime, CONSOLE_MODULE,
                                         "__console_err", &refs[0]);
    if (err == BREAK_LUA_OK) {
        err = break_lua_runtime_ref_function(console->runtime, CONSOLE_MODULE,
                                             "__console_lines", &refs[1]);
    }
    if (err == BREAK_LUA_OK) {
        err = break_lua_runtime_ref_function(console->runtime, CONSOLE_MODULE,
                                             "__console_result", &refs[2]);
    }
    if (err != BREAK_LUA_OK) {
        console_log(console, "error: console: outcome channel capture failed (%s)",
                    break_lua_error_name(err));
        console_release_refs(console, refs, 3u);
        console_main_runtime_reset_if_unhealthy(console);
        return false;
    }
    console_pin_cleanup(console); /* cleanup_ref is UINT32_MAX here */

    /* 5. Dispatch on_frame_begin: the Stage 3 count hook arms the console
     *    instruction budget over exactly this invocation (main coroutine).
     *    NEW-C4 semantics: the sandboxed pcall is budget-TRANSPARENT — the
     *    harness's __pcall returns ordinary body errors (false, msg) but
     *    re-raises the trip sentinel, so a budget trip kills the hook
     *    (module marked hooks-disabled, cleared by the next eval's
     *    committed reload) and is recognized here via the trip-counter
     *    delta. Ordinary errors keep flowing through __E. */
    {
        u64 trips_before =
            break_lua_runtime_budget_trip_count(console->runtime);
        break_lua_runtime_begin_frame(console->runtime, 0.0);
        break_lua_runtime_end_frame(console->runtime);
        tripped =
            break_lua_runtime_budget_trip_count(console->runtime) !=
            trips_before;
    }

    /* 6. Read the host-trusted outcome markers, the captured print lines,
     *    and the result — via the pinned refs only. */
    eval_err[0] = '\0';
    err = break_lua_runtime_call_ref(console->runtime, refs[0], NULL, 0u,
                                     status, 2u);
    if (err != BREAK_LUA_OK) {
        console_log(console, "error: console: eval status unavailable (%s)",
                    break_lua_error_name(err));
    } else {
        done = status[0].type == BREAK_LUA_VALUE_BOOL && status[0].as.b;
        if (status[1].type == BREAK_LUA_VALUE_STRING &&
            status[1].as.s.len > 0u) {
            memcpy(eval_err, status[1].as.s.data, status[1].as.s.len + 1u);
        }
        if (!done && eval_err[0] == '\0') {
            if (tripped) {
                /* The trip is uncatchable by design (NEW-C4): the hook
                 * died, the module is marked (cleared by the next eval's
                 * reload), the records below are discarded. */
                memcpy(eval_err, "break_lua: instruction budget exceeded",
                       sizeof("break_lua: instruction budget exceeded"));
            } else {
                /* The hook died another way (unreachable via sandbox means
                 * since round 3; a dispatch-level Lua OOM lands here). */
                memcpy(eval_err, "console internal: eval dispatch did not run",
                       sizeof("console internal: eval dispatch did not run"));
            }
        }
    }
    eval_ok = done && eval_err[0] == '\0';

    err = break_lua_runtime_call_ref(console->runtime, refs[1], NULL, 0u, v,
                                     BREAK_EDITOR_LUA_MAX_PRINT_LINES);
    if (err == BREAK_LUA_OK) {
        for (i = 0u; i < BREAK_EDITOR_LUA_MAX_PRINT_LINES; i++) {
            if (v[i].type == BREAK_LUA_VALUE_STRING) {
                console_log(console, "%s", v[i].as.s.data);
            }
        }
    } else {
        console_log(console, "error: console: print capture unavailable (%s)",
                    break_lua_error_name(err));
    }

    if (eval_err[0] != '\0') {
        harness_offset = console_count_lines(HARNESS_PREFIX);
        console_log_lua_error(console, eval_err, harness_offset);
    } else if (eval_ok) {
        err = break_lua_runtime_call_ref(console->runtime, refs[2], NULL, 0u,
                                         &single, 1u);
        if (err == BREAK_LUA_FAILED) {
            /* Unrepresentable result type (table/function/...): the eval
             * itself succeeded; only the value cannot cross the boundary. */
            console_log(console, "error: console: result not representable");
        } else if (err != BREAK_LUA_OK) {
            console_log(console, "error: console: result unavailable (%s)",
                        break_lua_error_name(err));
        } else {
            switch (single.type) {
            case BREAK_LUA_VALUE_NIL:
                break; /* statement input: no result line */
            case BREAK_LUA_VALUE_BOOL:
                console_log(console, "%s", single.as.b ? "true" : "false");
                break;
            case BREAK_LUA_VALUE_NUMBER:
                console_log(console, "%.14g", (double)single.as.n);
                break;
            case BREAK_LUA_VALUE_STRING:
                console_log(console, "%s", single.as.s.data);
                break;
            }
        }
    }
    console_release_refs(console, refs, 3u);

    /* The outcome channel being unreadable (getter failure) or the hook
     * dying WITHOUT a budget trip means the console runtime is in an
     * unexpected state — health-check and recover it (ordinary body errors
     * and budget trips are healthy states and skip this). */
    if (!done && eval_err[0] == '\0') {
        console_main_runtime_reset_if_unhealthy(console);
    }

    /* 7. Drain the batch AFTER every eval: applied only when the host-
     *    trusted markers prove the chunk ran clean; a failed eval discards
     *    its records (never half-applied). Early returns above cannot leave
     *    residue: probe staging runs on the batch-free probe runtime and
     *    harness staging runs no user code, so only the dispatch
     *    enqueues. */
    for (;;) {
        usize k = break_lua_ecs_batch_drain(
            console->batch, console->drain + drained,
            BREAK_LUA_ECS_BATCH_DEFAULT_CAPACITY - drained);
        if (k == 0u) {
            break;
        }
        drained += k;
    }
    if (eval_ok && drained > 0u) {
        console_apply_records(console, drained);
    }
    return eval_ok;
}

usize break_editor_lua_pending_records(const BreakEditorLuaConsole *console) {
    BreakLuaEcsRecord rec;
    usize total = 0u;
    if (!console) {
        return 0u;
    }
    if (!console_is_owner(console)) {
        return 0u;
    }
    /* The batch has no count query; a bounded drain-and-discard loop is the
     * documented test-probe semantics (0 after any eval). The batch is
     * host-owned and stays valid even if a runtime was lost. */
    while (break_lua_ecs_batch_drain(console->batch, &rec, 1u) != 0u) {
        total++;
    }
    return total;
}
