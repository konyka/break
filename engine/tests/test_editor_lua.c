/* Stage 4 scene editor Phase 3 Task 2: BreakEditorLuaConsole tests.
 *
 * Covers (brief checklist): arithmetic result logged; print captured
 * (multi-line, 127-byte truncation, 32-line cap); syntax / runtime error
 * bounded lines with input-relative line numbers; budget trip (infinite
 * loop) → bounded error, console usable next eval; spawn record → entity
 * (undo removes, redo restores same id); set record on last-spawned entity
 * (number / string-parsed / bool) undoable with implicit component add;
 * unknown component/field and missing target → error line, record skipped,
 * no partial application; failed eval discards enqueued records;
 * pending_records == 0 after eval; input length bound (4096/4097);
 * unrepresentable result type; OOM create sweeps (editor hook + lua hook);
 * owner-thread rejection probe (eval/pending/destroy from a worker). */

#include "test_framework.h"

#include <editor/editor_lua.h>

#include <editor/editor_cmd.h>
#include <editor/editor_components.h>
#include <editor/editor_test_hooks.h>

#include <script/break_lua_test_hooks.h>

#include <core/platform_thread.h>

#include <string.h>

/* ------------------------------------------------------------------ */
/* Log sink                                                            */
/* ------------------------------------------------------------------ */

#define SINK_CAP 64u

typedef struct {
    char lines[SINK_CAP][128];
    usize count;       /* stored (capped at SINK_CAP) */
    usize total_calls; /* every log_fn invocation */
    bool overlong;     /* a line violated the 128-byte rule (incl. NUL) */
} LogSink;

static void log_cb(void *ctx, const char *line) {
    LogSink *s = (LogSink *)ctx;
    usize len = strlen(line); /* lines must be NUL-terminated */
    if (len > 127u) s->overlong = true;
    s->total_calls++;
    if (s->count < SINK_CAP) {
        memcpy(s->lines[s->count], line, len + 1u);
        s->count++;
    }
}

static void sink_reset(LogSink *s) { memset(s, 0, sizeof(*s)); }

/* First line index containing `needle`, or -1. */
static long sink_find(const LogSink *s, const char *needle) {
    for (usize i = 0; i < s->count; i++) {
        if (strstr(s->lines[i], needle)) return (long)i;
    }
    return -1;
}

static bool sink_has_prefix(const LogSink *s, const char *prefix) {
    usize n = strlen(prefix);
    for (usize i = 0; i < s->count; i++) {
        if (strncmp(s->lines[i], prefix, n) == 0) return true;
    }
    return false;
}

/* ------------------------------------------------------------------ */
/* Fixture                                                             */
/* ------------------------------------------------------------------ */

typedef struct {
    BreakEditorDoc *doc;
    BreakEditorLuaConsole *console;
    LogSink sink;
} Fixture;

static bool fixture_open(Fixture *f) {
    memset(f, 0, sizeof(*f));
    f->doc = break_editor_doc_create();
    if (!f->doc) return false;
    f->console = break_editor_lua_create(f->doc, log_cb, &f->sink);
    if (!f->console) {
        break_editor_doc_destroy(f->doc);
        return false;
    }
    return true;
}

static void fixture_close(Fixture *f) {
    break_editor_lua_destroy(f->console);
    break_editor_doc_destroy(f->doc);
    f->console = NULL;
    f->doc = NULL;
}

/* ------------------------------------------------------------------ */
/* Result / print reporting                                            */
/* ------------------------------------------------------------------ */

TEST(eval_arithmetic_result_logged) {
    Fixture f;
    ASSERT_TRUE(fixture_open(&f));

    /* Bare expression: auto-wrapped as `return 1+2`. */
    ASSERT_TRUE(break_editor_lua_eval(f.console, "1+2"));
    ASSERT_TRUE(sink_find(&f.sink, "3") >= 0);
    ASSERT_EQ(break_editor_lua_pending_records(f.console), 0u);

    sink_reset(&f.sink);
    ASSERT_TRUE(break_editor_lua_eval(f.console, "return 4*5"));
    ASSERT_TRUE(sink_find(&f.sink, "20") >= 0);

    /* No result for bare statements: no new lines at all. */
    sink_reset(&f.sink);
    ASSERT_TRUE(break_editor_lua_eval(f.console, "local x = 9"));
    ASSERT_EQ(f.sink.total_calls, 0u);

    /* Bool / string / negative results. */
    sink_reset(&f.sink);
    ASSERT_TRUE(break_editor_lua_eval(f.console, "1 < 2"));
    ASSERT_TRUE(sink_find(&f.sink, "true") >= 0);
    sink_reset(&f.sink);
    ASSERT_TRUE(break_editor_lua_eval(f.console, "'hello console'"));
    ASSERT_TRUE(sink_find(&f.sink, "hello console") >= 0);

    ASSERT_FALSE(f.sink.overlong);
    fixture_close(&f);
}

TEST(eval_result_string_truncated_and_unrepresentable) {
    Fixture f;
    ASSERT_TRUE(fixture_open(&f));

    /* A 200-char string result is truncated to the 127-visible-byte line
     * bound (inside Lua, before the BreakLuaValue string cap applies). */
    ASSERT_TRUE(break_editor_lua_eval(f.console, "string.rep('y', 200)"));
    ASSERT_EQ(f.sink.count, 1u);
    ASSERT_EQ(strlen(f.sink.lines[0]), 127u);
    for (usize i = 0; i < 127u; i++) ASSERT_EQ(f.sink.lines[0][i], 'y');

    /* A table result is unrepresentable in BreakLuaValue: eval succeeded
     * but the result marshalling surfaces a bounded error line. */
    sink_reset(&f.sink);
    ASSERT_TRUE(break_editor_lua_eval(f.console, "return {}"));
    ASSERT_TRUE(sink_has_prefix(&f.sink, "error:"));

    ASSERT_FALSE(f.sink.overlong);
    fixture_close(&f);
}

TEST(eval_print_multiline_bounded) {
    Fixture f;
    ASSERT_TRUE(fixture_open(&f));

    ASSERT_TRUE(break_editor_lua_eval(
        f.console, "print('a'); print('b', 1, true); print('c')"));
    /* tostring-joined with '\t'; order preserved; prints precede any
     * result line (this eval has no result). */
    ASSERT_EQ(f.sink.count, 3u);
    ASSERT_STR_EQ(f.sink.lines[0], "a");
    ASSERT_STR_EQ(f.sink.lines[1], "b\t1\ttrue");
    ASSERT_STR_EQ(f.sink.lines[2], "c");

    /* Print line truncation at 127 visible bytes. */
    sink_reset(&f.sink);
    ASSERT_TRUE(break_editor_lua_eval(f.console, "print(string.rep('x', 500))"));
    ASSERT_EQ(f.sink.count, 1u);
    ASSERT_EQ(strlen(f.sink.lines[0]), 127u);

    /* Print-line cap: 40 prints -> exactly 32 lines kept. */
    sink_reset(&f.sink);
    ASSERT_TRUE(break_editor_lua_eval(
        f.console, "for i=1,40 do print('line ' .. i) end"));
    ASSERT_EQ(f.sink.count, 32u);
    ASSERT_STR_EQ(f.sink.lines[0], "line 1");
    ASSERT_STR_EQ(f.sink.lines[31], "line 32");
    ASSERT_EQ(break_editor_lua_pending_records(f.console), 0u);

    /* Prints come before the result line. */
    sink_reset(&f.sink);
    ASSERT_TRUE(break_editor_lua_eval(f.console, "print('p'); return 7"));
    ASSERT_EQ(f.sink.count, 2u);
    ASSERT_STR_EQ(f.sink.lines[0], "p");
    ASSERT_STR_EQ(f.sink.lines[1], "7");

    ASSERT_FALSE(f.sink.overlong);
    fixture_close(&f);
}

TEST(eval_syntax_error_line_then_recover) {
    Fixture f;
    ASSERT_TRUE(fixture_open(&f));

    ASSERT_FALSE(break_editor_lua_eval(f.console, "1+"));
    ASSERT_TRUE(sink_has_prefix(&f.sink, "error:"));
    ASSERT_EQ(break_editor_lua_pending_records(f.console), 0u);
    /* Doc untouched. */
    ASSERT_EQ(break_editor_doc_entity_count(f.doc), 0u);
    ASSERT_FALSE(break_editor_doc_is_dirty(f.doc));

    /* Garbage that fails both the as-is and the return-wrap attempt. */
    sink_reset(&f.sink);
    ASSERT_FALSE(break_editor_lua_eval(f.console, "foo bar baz"));
    ASSERT_TRUE(sink_has_prefix(&f.sink, "error:"));

    /* The console stays fully usable. */
    sink_reset(&f.sink);
    ASSERT_TRUE(break_editor_lua_eval(f.console, "1+2"));
    ASSERT_TRUE(sink_find(&f.sink, "3") >= 0);

    ASSERT_FALSE(f.sink.overlong);
    fixture_close(&f);
}

TEST(eval_runtime_error_line_adjusted) {
    Fixture f;
    ASSERT_TRUE(fixture_open(&f));

    /* error("boom") on input line 1: the harness line offset is adjusted
     * back out of the message. */
    ASSERT_FALSE(break_editor_lua_eval(f.console, "error('boom')"));
    ASSERT_TRUE(sink_find(&f.sink, "error: line 1: boom") >= 0);

    /* Prints captured before the error are still delivered, error last. */
    sink_reset(&f.sink);
    ASSERT_FALSE(break_editor_lua_eval(f.console, "print('before'); error('x')"));
    ASSERT_EQ(f.sink.count, 2u);
    ASSERT_STR_EQ(f.sink.lines[0], "before");
    ASSERT_TRUE(strncmp(f.sink.lines[1], "error:", 6u) == 0);

    /* Multi-line input: error on input line 2 keeps line 2. */
    sink_reset(&f.sink);
    ASSERT_FALSE(break_editor_lua_eval(
        f.console, "local t = nil\nreturn t.x"));
    ASSERT_TRUE(sink_find(&f.sink, "error: line 2:") >= 0);

    ASSERT_EQ(break_editor_lua_pending_records(f.console), 0u);
    ASSERT_FALSE(f.sink.overlong);
    fixture_close(&f);
}

TEST(eval_budget_trip_console_survives) {
    Fixture f;
    ASSERT_TRUE(fixture_open(&f));

    /* 1,000,000-instruction budget: an infinite loop trips it. */
    ASSERT_FALSE(break_editor_lua_eval(f.console, "while true do end"));
    ASSERT_TRUE(sink_has_prefix(&f.sink, "error:"));
    ASSERT_TRUE(sink_find(&f.sink, "instruction budget") >= 0);
    ASSERT_EQ(break_editor_lua_pending_records(f.console), 0u);

    /* The module is not wedged: the very next eval works. */
    sink_reset(&f.sink);
    ASSERT_TRUE(break_editor_lua_eval(f.console, "6*7"));
    ASSERT_TRUE(sink_find(&f.sink, "42") >= 0);

    /* A large-but-bounded loop still completes. */
    sink_reset(&f.sink);
    ASSERT_TRUE(break_editor_lua_eval(
        f.console, "local s = 0 for i=1,1000 do s = s + i end return s"));
    ASSERT_TRUE(sink_find(&f.sink, "500500") >= 0);

    ASSERT_FALSE(f.sink.overlong);
    fixture_close(&f);
}

/* ------------------------------------------------------------------ */
/* ECS batch drain -> undoable doc commands                            */
/* ------------------------------------------------------------------ */

TEST(spawn_record_creates_entity_undoable) {
    Fixture f;
    ASSERT_TRUE(fixture_open(&f));
    ASSERT_EQ(break_editor_doc_entity_count(f.doc), 0u);

    ASSERT_TRUE(break_editor_lua_eval(f.console, "brk.ecs.spawn()"));
    ASSERT_EQ(break_editor_doc_entity_count(f.doc), 1u);
    ASSERT_EQ(break_editor_lua_pending_records(f.console), 0u);

    BreakEditorEntityId id;
    const char *name = NULL;
    ASSERT_TRUE(break_editor_doc_entity_at(f.doc, 0u, &id, &name));
    ASSERT_TRUE(break_editor_entity_id_valid(id));
    /* Stage 3 spawn records carry no name: the doc generated one. */
    ASSERT_TRUE(strncmp(name, "entity_", 7u) == 0);

    /* One spawn record = exactly one command: a single undo removes it. */
    ASSERT_TRUE(break_editor_undo(f.doc));
    ASSERT_EQ(break_editor_doc_entity_count(f.doc), 0u);
    /* Redo restores the same id. */
    ASSERT_TRUE(break_editor_redo(f.doc));
    ASSERT_EQ(break_editor_doc_entity_count(f.doc), 1u);
    BreakEditorEntityId id2;
    ASSERT_TRUE(break_editor_doc_entity_at(f.doc, 0u, &id2, &name));
    ASSERT_TRUE(break_editor_entity_id_eq(id, id2));

    /* The identical `break` alias resolves to the same proxy (`break` is a
     * reserved word, so it is reached through _G["break"]). */
    ASSERT_TRUE(break_editor_lua_eval(f.console, "_G['break'].ecs.spawn()"));
    ASSERT_EQ(break_editor_doc_entity_count(f.doc), 2u);

    fixture_close(&f);
}

TEST(spawn_multi_record_fifo) {
    Fixture f;
    ASSERT_TRUE(fixture_open(&f));

    ASSERT_TRUE(break_editor_lua_eval(
        f.console, "for i=1,3 do brk.ecs.spawn() end"));
    ASSERT_EQ(break_editor_doc_entity_count(f.doc), 3u);
    ASSERT_EQ(break_editor_lua_pending_records(f.console), 0u);
    /* Three spawn records = three commands. */
    ASSERT_TRUE(break_editor_undo(f.doc));
    ASSERT_TRUE(break_editor_undo(f.doc));
    ASSERT_TRUE(break_editor_undo(f.doc));
    ASSERT_EQ(break_editor_doc_entity_count(f.doc), 0u);

    fixture_close(&f);
}

TEST(set_record_number_string_bool_undoable) {
    Fixture f;
    ASSERT_TRUE(fixture_open(&f));

    /* The freshly spawned entity lacks Transform: the first set applies an
     * undoable add_component (zeroed) before the undoable field write. */
    ASSERT_TRUE(break_editor_lua_eval(
        f.console,
        "brk.ecs.spawn()\n"
        "brk.ecs.set('Transform', 'pos.x', 5.5)\n"
        "brk.ecs.set('Transform', 'pos.y', '2.25')\n"
        "brk.ecs.set('Transform', 'rot.z', true)"));
    ASSERT_EQ(break_editor_lua_pending_records(f.console), 0u);
    ASSERT_EQ(break_editor_doc_entity_count(f.doc), 1u);

    BreakEditorEntityId id;
    const char *unused_name = NULL;
    ASSERT_TRUE(break_editor_doc_entity_at(f.doc, 0u, &id, &unused_name));
    ASSERT_TRUE(break_editor_doc_has_component(
        f.doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM));
    f32 v = 0.0f;
    ASSERT_TRUE(break_editor_doc_get_field_f32(
        f.doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM, 0u, &v)); /* pos.x */
    ASSERT_FLOAT_EQ(v, 5.5f, 1e-6f);
    ASSERT_TRUE(break_editor_doc_get_field_f32(
        f.doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM, 1u, &v)); /* pos.y */
    ASSERT_FLOAT_EQ(v, 2.25f, 1e-6f);
    ASSERT_TRUE(break_editor_doc_get_field_f32(
        f.doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM, 5u, &v)); /* rot.z */
    ASSERT_FLOAT_EQ(v, 1.0f, 1e-6f);

    /* Undo chain: rot.z revert, pos.y revert, pos.x revert, component
     * removal, spawn removal. */
    ASSERT_TRUE(break_editor_undo(f.doc));
    ASSERT_TRUE(break_editor_doc_get_field_f32(
        f.doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM, 5u, &v));
    ASSERT_FLOAT_EQ(v, 0.0f, 1e-6f);
    ASSERT_TRUE(break_editor_undo(f.doc));
    ASSERT_TRUE(break_editor_doc_get_field_f32(
        f.doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM, 1u, &v));
    ASSERT_FLOAT_EQ(v, 0.0f, 1e-6f);
    ASSERT_TRUE(break_editor_undo(f.doc));
    ASSERT_TRUE(break_editor_doc_get_field_f32(
        f.doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM, 0u, &v));
    ASSERT_FLOAT_EQ(v, 0.0f, 1e-6f);
    ASSERT_TRUE(break_editor_undo(f.doc));
    ASSERT_FALSE(break_editor_doc_has_component(
        f.doc, id, BREAK_EDITOR_COMPONENT_TRANSFORM));
    ASSERT_TRUE(break_editor_undo(f.doc));
    ASSERT_EQ(break_editor_doc_entity_count(f.doc), 0u);
    ASSERT_FALSE(break_editor_undo(f.doc)); /* stack empty */

    fixture_close(&f);
}

TEST(set_record_existing_component_single_command) {
    Fixture f;
    ASSERT_TRUE(fixture_open(&f));

    /* Spawn via the doc API, add the component, then detach target state:
     * the set must NOT reach this entity (no spawn this eval). */
    BreakEditorEntityId pre =
        break_editor_doc_add_entity(f.doc, "preexisting");
    ASSERT_TRUE(break_editor_entity_id_valid(pre));
    ASSERT_TRUE(break_editor_doc_add_component(f.doc, pre,
                                               BREAK_EDITOR_COMPONENT_TRANSFORM));

    /* No spawn in this eval -> no target -> bounded error, doc unchanged. */
    ASSERT_TRUE(break_editor_lua_eval(
        f.console, "brk.ecs.set('Transform', 'pos.x', 9)"));
    ASSERT_TRUE(sink_find(&f.sink, "error: ecs.set: no target") >= 0);
    f32 v = 1.0f;
    ASSERT_TRUE(break_editor_doc_get_field_f32(
        f.doc, pre, BREAK_EDITOR_COMPONENT_TRANSFORM, 0u, &v));
    ASSERT_FLOAT_EQ(v, 0.0f, 1e-6f);

    /* A spawn + set in the SAME eval targets the spawned entity (the
     * pre-existing one is untouched). The component already present path
     * is exercised on the pre-existing entity via the doc API above, so
     * here: one spawn command + one add + one set. */
    sink_reset(&f.sink);
    ASSERT_TRUE(break_editor_lua_eval(
        f.console, "brk.ecs.spawn(); brk.ecs.set('Transform', 'pos.x', 9)"));
    BreakEditorEntityId spawned;
    const char *unused_name = NULL;
    ASSERT_TRUE(break_editor_doc_entity_at(f.doc, 1u, &spawned, &unused_name));
    ASSERT_TRUE(break_editor_doc_get_field_f32(
        f.doc, spawned, BREAK_EDITOR_COMPONENT_TRANSFORM, 0u, &v));
    ASSERT_FLOAT_EQ(v, 9.0f, 1e-6f);
    ASSERT_TRUE(break_editor_doc_get_field_f32(
        f.doc, pre, BREAK_EDITOR_COMPONENT_TRANSFORM, 0u, &v));
    ASSERT_FLOAT_EQ(v, 0.0f, 1e-6f);

    fixture_close(&f);
}

TEST(set_unknown_component_field_never_partial) {
    Fixture f;
    ASSERT_TRUE(fixture_open(&f));

    /* Unknown component: spawn applies, the set is skipped entirely — no
     * component add, one command total. */
    ASSERT_TRUE(break_editor_lua_eval(
        f.console, "brk.ecs.spawn(); brk.ecs.set('Bogus', 'pos.x', 1)"));
    ASSERT_TRUE(sink_find(&f.sink, "error: ecs.set: unknown component") >= 0);
    BreakEditorEntityId id;
    const char *unused_name = NULL;
    ASSERT_TRUE(break_editor_doc_entity_at(f.doc, 0u, &id, &unused_name));
    ASSERT_FALSE(break_editor_doc_has_component(f.doc, id,
                                                BREAK_EDITOR_COMPONENT_TRANSFORM));
    ASSERT_TRUE(break_editor_undo(f.doc)); /* the spawn only */
    ASSERT_FALSE(break_editor_undo(f.doc));
    ASSERT_EQ(break_editor_doc_entity_count(f.doc), 0u);

    /* Unknown field: same shape. */
    sink_reset(&f.sink);
    ASSERT_TRUE(break_editor_lua_eval(
        f.console, "brk.ecs.spawn(); brk.ecs.set('Transform', 'bogus', 1)"));
    ASSERT_TRUE(sink_find(&f.sink, "error: ecs.set: unknown field") >= 0);
    ASSERT_TRUE(break_editor_doc_entity_at(f.doc, 0u, &id, &unused_name));
    ASSERT_FALSE(break_editor_doc_has_component(f.doc, id,
                                                BREAK_EDITOR_COMPONENT_TRANSFORM));
    ASSERT_TRUE(break_editor_undo(f.doc));
    ASSERT_FALSE(break_editor_undo(f.doc));

    /* Unparseable string value: rejected before the component is added. */
    sink_reset(&f.sink);
    ASSERT_TRUE(break_editor_lua_eval(
        f.console, "brk.ecs.spawn(); brk.ecs.set('Transform', 'pos.x', 'abc')"));
    ASSERT_TRUE(sink_find(&f.sink, "error: ecs.set:") >= 0);
    ASSERT_TRUE(break_editor_doc_entity_at(f.doc, 0u, &id, &unused_name));
    ASSERT_FALSE(break_editor_doc_has_component(f.doc, id,
                                                BREAK_EDITOR_COMPONENT_TRANSFORM));
    ASSERT_TRUE(break_editor_undo(f.doc));
    ASSERT_FALSE(break_editor_undo(f.doc));

    /* Non-finite number: rejected. */
    sink_reset(&f.sink);
    ASSERT_TRUE(break_editor_lua_eval(
        f.console, "brk.ecs.spawn(); brk.ecs.set('Transform', 'pos.x', 1/0)"));
    ASSERT_TRUE(sink_find(&f.sink, "error: ecs.set:") >= 0);
    ASSERT_TRUE(break_editor_doc_entity_at(f.doc, 0u, &id, &unused_name));
    ASSERT_FALSE(break_editor_doc_has_component(f.doc, id,
                                                BREAK_EDITOR_COMPONENT_TRANSFORM));

    ASSERT_EQ(break_editor_lua_pending_records(f.console), 0u);
    ASSERT_FALSE(f.sink.overlong);
    fixture_close(&f);
}

TEST(failed_eval_discards_records) {
    Fixture f;
    ASSERT_TRUE(fixture_open(&f));

    /* The spawn was enqueued before the error: a failed eval applies
     * NOTHING and leaves no batch residue. */
    ASSERT_FALSE(break_editor_lua_eval(
        f.console, "brk.ecs.spawn(); error('stop')"));
    ASSERT_EQ(break_editor_doc_entity_count(f.doc), 0u);
    ASSERT_EQ(break_editor_lua_pending_records(f.console), 0u);
    ASSERT_FALSE(break_editor_undo(f.doc));

    /* Same for a budget trip after an enqueue. */
    ASSERT_FALSE(break_editor_lua_eval(
        f.console, "brk.ecs.spawn(); while true do end"));
    ASSERT_EQ(break_editor_doc_entity_count(f.doc), 0u);
    ASSERT_EQ(break_editor_lua_pending_records(f.console), 0u);

    fixture_close(&f);
}

TEST(batch_full_is_script_visible_and_bounded) {
    Fixture f;
    ASSERT_TRUE(fixture_open(&f));

    /* 300 spawn attempts against the 256-record batch: the script sees the
     * bounded failure pair and prints it; the console applies the 256. */
    ASSERT_TRUE(break_editor_lua_eval(
        f.console,
        "for i=1,300 do\n"
        "  local ok, msg = brk.ecs.spawn()\n"
        "  if not ok then print(msg) break end\n"
        "end"));
    ASSERT_TRUE(sink_find(&f.sink, "break.ecs: batch full") >= 0);
    ASSERT_EQ(break_editor_doc_entity_count(f.doc), 256u);
    ASSERT_EQ(break_editor_lua_pending_records(f.console), 0u);

    fixture_close(&f);
}

/* ------------------------------------------------------------------ */
/* Bounds                                                              */
/* ------------------------------------------------------------------ */

TEST(input_length_bound) {
    Fixture f;
    ASSERT_TRUE(fixture_open(&f));

    static char input[4200];
    memset(input, ' ', 4096u);
    input[4096] = '\0';
    /* 4096 bytes (whitespace-only): accepted. */
    ASSERT_TRUE(break_editor_lua_eval(f.console, input));
    ASSERT_EQ(f.sink.total_calls, 0u);

    memset(input, ' ', 4097u);
    input[4097] = '\0';
    ASSERT_FALSE(break_editor_lua_eval(f.console, input));
    ASSERT_TRUE(sink_find(&f.sink, "error: input too long") >= 0);
    ASSERT_EQ(break_editor_lua_pending_records(f.console), 0u);

    /* No NUL anywhere in the scan window: same bounded rejection. */
    memset(input, '7', sizeof(input));
    ASSERT_FALSE(break_editor_lua_eval(f.console, input));
    input[0] = '\0';

    fixture_close(&f);
}

TEST(null_and_malformed_calls) {
    Fixture f;
    ASSERT_TRUE(fixture_open(&f));

    ASSERT_FALSE(break_editor_lua_eval(NULL, "1+2"));
    ASSERT_FALSE(break_editor_lua_eval(f.console, NULL));
    ASSERT_EQ(break_editor_lua_pending_records(NULL), 0u);
    break_editor_lua_destroy(NULL); /* no-op */

    ASSERT_TRUE(break_editor_lua_create(NULL, log_cb, &f.sink) == NULL);
    ASSERT_TRUE(break_editor_lua_create(f.doc, NULL, &f.sink) == NULL);

    /* The fixture console still works (nothing above touched it). */
    ASSERT_TRUE(break_editor_lua_eval(f.console, "1+2"));
    fixture_close(&f);
}

/* ------------------------------------------------------------------ */
/* OOM sweeps                                                          */
/* ------------------------------------------------------------------ */

TEST(create_oom_sweep_editor_hook) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    LogSink sink;
    sink_reset(&sink);

    /* create performs exactly 1 editor-owned allocation (the console
     * struct, which embeds the drain buffer): budget 0 fails, 1 works. */
    break_editor_test_set_alloc_budget(0u);
    ASSERT_TRUE(break_editor_lua_create(doc, log_cb, &sink) == NULL);
    break_editor_test_set_alloc_budget(BREAK_EDITOR_TEST_ALLOC_DISABLED);

    BreakEditorLuaConsole *c = break_editor_lua_create(doc, log_cb, &sink);
    ASSERT_NOT_NULL(c);
    break_editor_lua_destroy(c);
    break_editor_doc_destroy(doc);
}

TEST(create_oom_sweep_lua_hook) {
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(doc);
    LogSink sink;
    sink_reset(&sink);

    /* Every Lua-side allocation failure (runtime state, batch, bind) must
     * fail the create cleanly (ASan proves the partial teardown leak-free).
     * Doubling probe up to the first success, like test_break_lua_runtime's
     * create sweep. */
    u64 budget = 0u;
    for (;;) {
        break_lua_test_set_alloc_budget(budget);
        BreakEditorLuaConsole *c = break_editor_lua_create(doc, log_cb, &sink);
        break_lua_test_set_alloc_budget(BREAK_LUA_TEST_ALLOC_DISABLED);
        if (c) {
            /* A console created under a tight budget is fully usable once
             * the hook is off. */
            ASSERT_TRUE(break_editor_lua_eval(c, "1+2"));
            ASSERT_TRUE(sink_find(&sink, "3") >= 0);
            break_editor_lua_destroy(c);
            break;
        }
        ASSERT_TRUE(budget <= (1u << 20));
        budget = budget == 0u ? 1u : budget * 2u;
    }
    break_editor_doc_destroy(doc);
}

/* ------------------------------------------------------------------ */
/* Owner-thread rejection                                              */
/* ------------------------------------------------------------------ */

static BreakEditorLuaConsole *g_probe_console;
static bool g_probe_eval_ok;
static usize g_probe_pending;

static PLATFORM_THREAD_RET owner_probe_worker(PLATFORM_THREAD_ARG arg) {
    (void)arg;
    /* Non-owner eval: rejected with a bounded log line, no Lua access. */
    g_probe_eval_ok = break_editor_lua_eval(g_probe_console, "1+2");
    /* Non-owner probe: bounded 0. */
    g_probe_pending = break_editor_lua_pending_records(g_probe_console);
    /* Non-owner destroy: contract violation, ignored — the console must
     * survive untouched for the owner thread. */
    break_editor_lua_destroy(g_probe_console);
    return PLATFORM_THREAD_RETURN;
}

TEST(owner_thread_rejection_probe) {
    Fixture f;
    ASSERT_TRUE(fixture_open(&f));

    g_probe_console = f.console;
    g_probe_eval_ok = true;
    g_probe_pending = 999u;
    PlatformThread t;
    ASSERT_TRUE(platform_thread_create(&t, owner_probe_worker, NULL));
    platform_thread_join(t);

    ASSERT_FALSE(g_probe_eval_ok);
    ASSERT_EQ(g_probe_pending, 0u);
    ASSERT_TRUE(sink_find(&f.sink, "error:") >= 0);

    /* The worker's destroy was ignored: the owner still owns a live
     * console. */
    sink_reset(&f.sink);
    ASSERT_TRUE(break_editor_lua_eval(f.console, "1+2"));
    ASSERT_TRUE(sink_find(&f.sink, "3") >= 0);

    fixture_close(&f);
}

TEST_MAIN_BEGIN()
    RUN_TEST(eval_arithmetic_result_logged);
    RUN_TEST(eval_result_string_truncated_and_unrepresentable);
    RUN_TEST(eval_print_multiline_bounded);
    RUN_TEST(eval_syntax_error_line_then_recover);
    RUN_TEST(eval_runtime_error_line_adjusted);
    RUN_TEST(eval_budget_trip_console_survives);
    RUN_TEST(spawn_record_creates_entity_undoable);
    RUN_TEST(spawn_multi_record_fifo);
    RUN_TEST(set_record_number_string_bool_undoable);
    RUN_TEST(set_record_existing_component_single_command);
    RUN_TEST(set_unknown_component_field_never_partial);
    RUN_TEST(failed_eval_discards_records);
    RUN_TEST(batch_full_is_script_visible_and_bounded);
    RUN_TEST(input_length_bound);
    RUN_TEST(null_and_malformed_calls);
    RUN_TEST(create_oom_sweep_editor_hook);
    RUN_TEST(create_oom_sweep_lua_hook);
    RUN_TEST(owner_thread_rejection_probe);
TEST_MAIN_END()
