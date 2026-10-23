/* BreakEditorLuaConsole — implementation. The full contract (owner thread,
 * eval pipeline, injection-safe dual-probe shape, budget arming, record
 * application, bounds) is documented in editor_lua.h. */

#include <editor/editor_lua.h>

#include <editor/editor_cmd.h>
#include <editor/editor_components.h>
#include <editor/editor_test_hooks.h>

#include <script/break_lua.h>

#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

/* Two runtimes (fix round 1): the CONSOLE runtime owns the batch binding and
 * stages only probe-verified harness chunks (user code on it runs solely
 * inside the budgeted frame dispatch); the PROBE runtime has NO batch bound,
 * so even a crafted escape that reaches probe staging cannot enqueue ECS
 * records — its worst side effect is a bounded stdout print. Module names
 * are fixed; each eval is a committed reload of the touched modules, so
 * evals share no environment state. */
#define CONSOLE_MODULE "console"
#define PROBE_R_MODULE "probe_r"
#define PROBE_L_MODULE "probe_l"

/* Chunk size bound: prefixes/suffixes are fixed small strings; the body is
 * "return " (7) + input (<= 4096). */
#define CONSOLE_CHUNK_CAPACITY 5632u

/* Dual compile probes (fix round 1, C1): a single wrapper context is never
 * escape-proof — in an EXPRESSION context (`return function() <B> end`) the
 * body can close the function early and continue the expression
 * (`end .. (function() ... end)() .. function() return 0`); in a STATEMENT
 * context (`local __p = function() <B> end`) it can close early and continue
 * with statements (`end while true do` swallows the trailing `end`). A body
 * passing BOTH probes is a syntactically complete block: probe R kills every
 * statement continuation (nothing may follow a return), probe L kills every
 * expression continuation (a statement cannot start with an operator), and
 * the two continuation token classes are disjoint — so an escape can pass at
 * most one. Since break_lua arms the instruction budget over staging too
 * (same fix round), even a hypothetical payload defeating both probes would
 * run bounded at staging. The body starts on probe line 2 in both. */
#define PROBE_R_PREFIX "return function()\n"
#define PROBE_L_PREFIX "local __p = function()\n"
#define PROBE_PREFIX_LINES 1u
#define PROBE_SUFFIX "\nend\n"

/* The console harness: print capture (32 lines x 127 visible bytes), the
 * probe-verified body as __body, on_frame_begin running it under the armed
 * count hook inside a pcall (runtime errors AND the budget trip are caught
 * and stored — the module is never marked hooks-disabled), and three raw
 * env getters the host calls afterwards. The body starts on line 15.
 * The epilogue clears on_unload/on_frame_end (fix round 1, I1/M3): the user
 * body may raw-set them; clearing runs after the pcall on every path, so
 * the live console env never carries an on_unload veto into the next eval's
 * reload, and a body-defined on_frame_end never dispatches (the console is
 * eval-based, not a frame loop). */
#define HARNESS_PREFIX                                              \
    "local __L={}\n"                                                \
    "local __R=nil\n"                                               \
    "local __E='console internal: eval dispatch did not run'\n"     \
    "print=function(...)\n"                                         \
    "  local n=select('#',...)\n"                                   \
    "  if #__L<32 then\n"                                           \
    "    local p={}\n"                                              \
    "    for i=1,n do p[i]=tostring(select(i,...)) end\n"           \
    "    local s=table.concat(p,'\\t')\n"                           \
    "    if #s>127 then s=s:sub(1,127) end\n"                       \
    "    __L[#__L+1]=s\n"                                           \
    "  end\n"                                                       \
    "end\n"                                                         \
    "local function __body()\n"
#define HARNESS_SUFFIX                                              \
    "\nend\n"                                                       \
    "function on_frame_begin(dt)\n"                                 \
    "  __E=nil\n"                                                   \
    "  local ok,r=pcall(__body)\n"                                  \
    "  if ok then\n"                                                \
    "    if type(r)=='string' and #r>127 then r=r:sub(1,127) end\n" \
    "    __R=r\n"                                                   \
    "  else\n"                                                      \
    "    local e=tostring(r)\n"                                     \
    "    if #e>120 then e=e:sub(1,120) end\n"                       \
    "    __E=e\n"                                                   \
    "  end\n"                                                       \
    "  on_unload=nil\n"                                             \
    "  on_frame_end=nil\n"                                          \
    "end\n"                                                         \
    "function __console_err() return __E end\n"                     \
    "function __console_lines() return table.unpack(__L) end\n"     \
    "function __console_result() return __R end\n"

struct BreakEditorLuaConsole {
    BreakEditorDoc *doc; /* borrowed; must outlive the console */
    BreakEditorLuaLogFn log_fn;
    void *log_ctx;
    BreakLuaRuntime *runtime;       /* owned; owns the batch binding */
    BreakLuaRuntime *probe_runtime; /* owned; NO batch bound (probe-only) */
    BreakLuaEcsBatch *batch;        /* owned (bound to runtime) */
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

/* Logs a Lua error message as "error: line M: <rest>" when it carries the
 * standard "<chunkname>:N: " position prefix and N is past the host-side
 * wrapper (offset = wrapper lines before the body, so M is the
 * input-relative line); otherwise "error: <raw>" — the raw fallback covers
 * position-less messages such as the count-hook trip text. Bounded by
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

/* The probe runtime + both seed modules. On any failure the partial state
 * is torn down and probe_runtime is NULL. */
static bool console_probe_runtime_init(BreakEditorLuaConsole *c) {
    static const char k_probe_r_seed[] = "return function() end\n";
    static const char k_probe_l_seed[] = "local __p = function() end\n";
    BreakLuaRuntimeConfig cfg;
    memset(&cfg, 0, sizeof(cfg));
    cfg.max_modules = 4u;
    cfg.instruction_budget = BREAK_EDITOR_LUA_INSTRUCTION_BUDGET;
    c->probe_runtime = break_lua_runtime_create(&cfg);
    if (!c->probe_runtime) {
        return false;
    }
    if (break_lua_runtime_load_module(c->probe_runtime, PROBE_R_MODULE,
                                      k_probe_r_seed,
                                      sizeof(k_probe_r_seed) - 1u) !=
            BREAK_LUA_OK ||
        break_lua_runtime_load_module(c->probe_runtime, PROBE_L_MODULE,
                                      k_probe_l_seed,
                                      sizeof(k_probe_l_seed) - 1u) !=
            BREAK_LUA_OK) {
        break_lua_runtime_destroy(c->probe_runtime);
        c->probe_runtime = NULL;
        return false;
    }
    return true;
}

/* Health check after a failed eval: a crafted escape that ran at probe
 * staging could have raw-set a vetoing on_unload on a probe module's env
 * (I1's wedge class, one level down). A trivial known-good reload answers
 * the question; on veto the whole probe runtime is recreated (it holds no
 * valuable state — two scratch modules), so a wedged probe can never
 * permanently kill the console. */
static void console_probe_runtime_reset_if_wedged(BreakEditorLuaConsole *c) {
    static const char k_trivial[] = "return function() end\n";
    if (!c->probe_runtime) {
        return;
    }
    if (break_lua_runtime_reload_module(c->probe_runtime, PROBE_R_MODULE,
                                        k_trivial, sizeof(k_trivial) - 1u,
                                        NULL) == BREAK_LUA_OK) {
        return;
    }
    break_lua_runtime_destroy(c->probe_runtime);
    c->probe_runtime = NULL;
    (void)console_probe_runtime_init(c);
}

/* Compiles one body form ("ret" is "" or "return ") through BOTH probes on
 * the probe runtime. BREAK_LUA_FAILED = syntax/escape rejection (or a
 * budgeted staging trip for a payload that slipped one probe's compile);
 * `report` carries the first failing probe's diagnostics. */
static BreakLuaError console_probe_form(BreakEditorLuaConsole *c,
                                        const char *ret, const char *body,
                                        BreakLuaReloadReport *report) {
    char chunk[CONSOLE_CHUNK_CAPACITY];
    BreakLuaError err;
    if (!console_build_chunk(chunk, sizeof(chunk), PROBE_R_PREFIX, ret, body,
                             PROBE_SUFFIX)) {
        return BREAK_LUA_FAILED;
    }
    err = break_lua_runtime_reload_module(c->probe_runtime, PROBE_R_MODULE,
                                          chunk, strlen(chunk), report);
    if (err != BREAK_LUA_OK) {
        return err;
    }
    if (!console_build_chunk(chunk, sizeof(chunk), PROBE_L_PREFIX, ret, body,
                             PROBE_SUFFIX)) {
        return BREAK_LUA_FAILED;
    }
    return break_lua_runtime_reload_module(c->probe_runtime, PROBE_L_MODULE,
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

/* ---------------------------------------------------------------------- */
/* Record application (successful evals only).                             */

static void console_apply_set(BreakEditorLuaConsole *c,
                              const BreakLuaEcsRecord *rec,
                              BreakEditorEntityId target) {
    BreakEditorComponentInfo info;
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
    static const char k_console_seed[] =
        HARNESS_PREFIX "\n" HARNESS_SUFFIX;
    BreakLuaRuntimeConfig cfg;
    BreakEditorLuaConsole *c;
    if (!doc || !log_fn) {
        return NULL;
    }
    memset(&cfg, 0, sizeof(cfg));
    cfg.max_modules = 8u;
    cfg.instruction_budget = BREAK_EDITOR_LUA_INSTRUCTION_BUDGET;

    /* The struct is the only editor-owned allocation; the runtimes, batch,
     * and seed compiles are break_lua-owned (BREAK_LUA_TESTING hooks). */
    c = (BreakEditorLuaConsole *)break_editor_test_calloc(sizeof(*c));
    if (!c) {
        return NULL;
    }
    c->doc = doc;
    c->log_fn = log_fn;
    c->log_ctx = log_ctx;
    c->runtime = break_lua_runtime_create(&cfg);
    if (!c->runtime) {
        free(c);
        return NULL;
    }
    c->batch = break_lua_ecs_batch_create(0u); /* 256 default */
    if (!c->batch) {
        break_lua_runtime_destroy(c->runtime);
        free(c);
        return NULL;
    }
    if (break_lua_runtime_bind_ecs_batch(c->runtime, c->batch) !=
        BREAK_LUA_OK) {
        break_lua_ecs_batch_destroy(c->batch);
        break_lua_runtime_destroy(c->runtime);
        free(c);
        return NULL;
    }
    /* Seed the console module so every eval is a reload with full
     * diagnostics. The seed compiles trivially; failure means Lua-side
     * OOM. */
    if (break_lua_runtime_load_module(c->runtime, CONSOLE_MODULE,
                                      k_console_seed,
                                      sizeof(k_console_seed) - 1u) !=
        BREAK_LUA_OK) {
        break_lua_ecs_batch_destroy(c->batch);
        break_lua_runtime_destroy(c->runtime);
        free(c);
        return NULL;
    }
    /* The probe runtime: no batch is ever bound to it. */
    if (!console_probe_runtime_init(c)) {
        break_lua_ecs_batch_destroy(c->batch);
        break_lua_runtime_destroy(c->runtime);
        free(c);
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
     * the probe coverage through the owner-thread rejection test). */
    if (break_lua_runtime_check_owner(console->runtime) != BREAK_LUA_OK) {
        return;
    }
    if (console->probe_runtime) {
        break_lua_runtime_destroy(console->probe_runtime);
    }
    break_lua_ecs_batch_destroy(console->batch);
    break_lua_runtime_destroy(console->runtime);
    free(console);
}

bool break_editor_lua_eval(BreakEditorLuaConsole *console, const char *input) {
    static const char k_return_wrap[] = "return ";
    char chunk[CONSOLE_CHUNK_CAPACITY];
    const char *ret = k_return_wrap;
    BreakLuaReloadReport report;
    BreakLuaError err;
    BreakLuaValue v[BREAK_EDITOR_LUA_MAX_PRINT_LINES];
    BreakLuaValue single;
    char eval_err[BREAK_LUA_VALUE_STRING_CAPACITY];
    bool eval_ok = true;
    usize drained = 0u;
    usize i;
    u32 harness_offset;

    if (!console || !input) {
        return false;
    }
    if (break_lua_runtime_check_owner(console->runtime) != BREAK_LUA_OK) {
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
    if (!console->probe_runtime) {
        console_log(console, "error: console: probe runtime unavailable");
        return false;
    }

    /* 1. Compile `return <input>` FIRST (the lua.c REPL order): a bare
     *    call like `string.rep('x',2)` parses fine as a STATEMENT, so
     *    as-is-first would never produce its value; return-first makes
     *    every bare expression auto-return, and genuine statements fail the
     *    wrap (return must be last) and fall through to the as-is attempt.
     *    Each form must pass BOTH compile probes — a form that passes is a
     *    syntactically complete block (see the dual-probe comment above):
     *    the console runtime never stages user code. */
    err = console_probe_form(console, ret, input, &report);
    if (err != BREAK_LUA_OK) {
        err = console_probe_form(console, "", input, &report);
        ret = ""; /* statement input: staged as-is */
    }
    if (err != BREAK_LUA_OK) {
        /* Report the AS-IS attempt's first probe failure (same convention
         * as the standalone lua REPL of reporting the plain-form error):
         * its line numbers match the typed input exactly — the wrap is
         * inline, shifting columns, not lines. */
        console_log_lua_error(console, report.error, PROBE_PREFIX_LINES);
        console_probe_runtime_reset_if_wedged(console);
        return false;
    }

    /* 2. Embed the verified body in the console harness and reload. The
     *    harness top level is host-controlled definitions only, so console
     *    staging never runs user code either (and is budget-armed at the
     *    break_lua layer regardless — defense in depth). */
    if (!console_build_chunk(chunk, sizeof(chunk), HARNESS_PREFIX, ret, input,
                             HARNESS_SUFFIX)) {
        console_log(console, "error: console: chunk assembly overflow");
        return false;
    }
    err = break_lua_runtime_reload_module(console->runtime, CONSOLE_MODULE,
                                          chunk, strlen(chunk), &report);
    if (err != BREAK_LUA_OK) {
        /* Probe-verified bodies cannot syntax-fail here; a failure is
         * harness-internal, a staging budget trip on a probe-defeating
         * payload, or OOM. */
        if (report.error[0] != '\0') {
            console_log_lua_error(console, report.error,
                                  console_count_lines(HARNESS_PREFIX));
        } else {
            console_log(console, "error: console: stage failed (%s)",
                        break_lua_error_name(err));
        }
        return false;
    }

    /* 3. Dispatch on_frame_begin: the Stage 3 count hook arms the console
     *    instruction budget over exactly this invocation (main coroutine).
     *    The harness pcall catches runtime errors and the budget trip; the
     *    epilogue then clears on_unload/on_frame_end (I1/M3). */
    break_lua_runtime_begin_frame(console->runtime, 0.0);
    break_lua_runtime_end_frame(console->runtime);

    /* 4. Collect the stored error, the captured print lines, and the
     *    result — via raw env getters (bounded BreakLuaValue marshalling). */
    eval_err[0] = '\0';
    err = break_lua_runtime_call(console->runtime, CONSOLE_MODULE,
                                 "__console_err", NULL, 0u, &single, 1u);
    if (err != BREAK_LUA_OK) {
        console_log(console, "error: console: eval status unavailable (%s)",
                    break_lua_error_name(err));
        eval_ok = false;
    } else if (single.type == BREAK_LUA_VALUE_STRING && single.as.s.len > 0u) {
        memcpy(eval_err, single.as.s.data, single.as.s.len + 1u);
        eval_ok = false;
    }

    err = break_lua_runtime_call(console->runtime, CONSOLE_MODULE,
                                 "__console_lines", NULL, 0u, v,
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

    if (!eval_ok) {
        if (eval_err[0] != '\0') {
            harness_offset = console_count_lines(HARNESS_PREFIX);
            console_log_lua_error(console, eval_err, harness_offset);
        }
    } else {
        err = break_lua_runtime_call(console->runtime, CONSOLE_MODULE,
                                     "__console_result", NULL, 0u, &single,
                                     1u);
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

    /* 5. Drain the batch AFTER every eval: applied only when the chunk ran
     *    clean; a failed eval discards its records (never half-applied).
     *    Early returns above cannot leave residue: probe staging runs on
     *    the batch-free probe runtime and harness staging runs no user
     *    code, so only the dispatch enqueues. */
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
    if (break_lua_runtime_check_owner(console->runtime) != BREAK_LUA_OK) {
        return 0u;
    }
    /* The batch has no count query; a bounded drain-and-discard loop is the
     * documented test-probe semantics (0 after any eval). */
    while (break_lua_ecs_batch_drain(console->batch, &rec, 1u) != 0u) {
        total++;
    }
    return total;
}
