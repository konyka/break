/* BreakEditorLuaConsole — implementation. The full contract (owner thread,
 * eval pipeline, injection-safe probe shape, budget arming through the
 * Stage 3 frame-hook dispatch, record application, bounds) is documented in
 * editor_lua.h. */

#include <editor/editor_lua.h>

#include <editor/editor_cmd.h>
#include <editor/editor_components.h>
#include <editor/editor_test_hooks.h>

#include <script/break_lua.h>

#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

/* Module names are fixed; each eval is a committed reload of both, so evals
 * share no environment state (the probe is only ever a closure constructor,
 * the console harness re-creates its capture tables per reload). */
#define CONSOLE_MODULE "console"
#define PROBE_MODULE "console_probe"

/* Chunk size bound: harness prefix+suffix are fixed few-hundred-byte
 * strings; the body is "return " (7) + input (<= 4096). */
#define CONSOLE_CHUNK_CAPACITY 5632u

/* The probe chunk proves the body is a syntactically complete block that
 * fills exactly one function body — anything that would escape a wrapper
 * (unbalanced `end`, trailing garbage) is a syntax error here, and staging
 * this chunk only CONSTRUCTS the closure (never calls it), so unbudgeted
 * staging time never runs user code. The body starts on probe line 2. */
#define PROBE_PREFIX "return function()\n"
#define PROBE_PREFIX_LINES 1u
#define PROBE_SUFFIX "\nend\n"

/* The console harness: print capture (32 lines x 127 visible bytes), the
 * probe-verified body as __body, on_frame_begin running it under the armed
 * count hook inside a pcall (runtime errors AND the budget trip are caught
 * and stored — the module is never marked hooks-disabled), and three raw
 * env getters the host calls afterwards. The body starts on line 15. */
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
    "end\n"                                                         \
    "function __console_err() return __E end\n"                     \
    "function __console_lines() return table.unpack(__L) end\n"     \
    "function __console_result() return __R end\n"

struct BreakEditorLuaConsole {
    BreakEditorDoc *doc; /* borrowed; must outlive the console */
    BreakEditorLuaLogFn log_fn;
    void *log_ctx;
    BreakLuaRuntime *runtime; /* owned */
    BreakLuaEcsBatch *batch;  /* owned (bound to the runtime) */
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
 * input-relative line); otherwise "error: <raw>". Bounded by console_log. */
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

/* Compiles `chunk` as (or as a replacement of) the module `name`. The probe
 * and console modules are pre-loaded at create, so every eval is a reload
 * and gets the full BreakLuaReloadReport diagnostics. */
static BreakLuaError console_restage(BreakEditorLuaConsole *c,
                                     const char *name, const char *chunk,
                                     BreakLuaReloadReport *report) {
    return break_lua_runtime_reload_module(c->runtime, name, chunk,
                                           strlen(chunk), report);
}

/* Validates the body through the probe module. `ret` is "" (as-is) or
 * "return " (expression wrap). Returns BREAK_LUA_OK when the body compiled;
 * BREAK_LUA_FAILED means a syntax error (the probe's top level only
 * constructs the closure, so staging cannot otherwise fail short of OOM,
 * which maps to BREAK_LUA_OOM). */
static BreakLuaError console_probe(BreakEditorLuaConsole *c, const char *ret,
                                   const char *body,
                                   BreakLuaReloadReport *report) {
    char chunk[CONSOLE_CHUNK_CAPACITY];
    if (!console_build_chunk(chunk, sizeof(chunk), PROBE_PREFIX, ret, body,
                             PROBE_SUFFIX)) {
        return BREAK_LUA_FAILED;
    }
    return console_restage(c, PROBE_MODULE, chunk, report);
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
    static const char k_probe_seed[] = "return function() end\n";
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

    /* The struct is the only editor-owned allocation; the runtime, batch,
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
    /* Seed both modules so every eval is a reload with full diagnostics.
     * The seeds compile trivially; failure here means Lua-side OOM. */
    if (break_lua_runtime_load_module(c->runtime, PROBE_MODULE, k_probe_seed,
                                      sizeof(k_probe_seed) - 1u) !=
            BREAK_LUA_OK ||
        break_lua_runtime_load_module(c->runtime, CONSOLE_MODULE,
                                      k_console_seed,
                                      sizeof(k_console_seed) - 1u) !=
            BREAK_LUA_OK) {
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

    /* 1. Compile `return <input>` FIRST (the lua.c REPL order): a bare
     *    call like `string.rep('x',2)` parses fine as a STATEMENT, so
     *    as-is-first would never produce its value; return-first makes
     *    every bare expression auto-return, and genuine statements fail the
     *    wrap (return must be last) and fall through to the as-is attempt.
     *    The probe proves the body cannot escape the harness wrapper (see
     *    editor_lua.h EVAL PIPELINE). */
    err = console_probe(console, ret, input, &report);
    if (err == BREAK_LUA_FAILED) {
        err = console_probe(console, "", input, &report);
        if (err == BREAK_LUA_FAILED) {
            /* Report the AS-IS attempt (same convention as the standalone
             * lua REPL): its line numbers match the typed input exactly —
             * the wrap is inline, shifting columns, not lines. */
            console_log_lua_error(console, report.error, PROBE_PREFIX_LINES);
            return false;
        }
        ret = ""; /* statement input: staged as-is */
    }
    if (err != BREAK_LUA_OK) {
        console_log(console, "error: console: probe stage failed (%s)",
                    break_lua_error_name(err));
        return false;
    }

    /* 2. Embed the verified body in the console harness and reload. */
    if (!console_build_chunk(chunk, sizeof(chunk), HARNESS_PREFIX, ret, input,
                             HARNESS_SUFFIX)) {
        console_log(console, "error: console: chunk assembly overflow");
        return false;
    }
    err = console_restage(console, CONSOLE_MODULE, chunk, &report);
    if (err != BREAK_LUA_OK) {
        /* Probe-verified bodies cannot syntax-fail here; a failure is
         * harness-internal or OOM. */
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
     *    The harness pcall catches runtime errors and the budget trip. */
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
     *    clean; a failed eval discards its records (never half-applied). */
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
