/* Incremental recompute: skipping the re-match of a rule whose read facts did
 * not change must give exactly the run of the full re-match. Random programs
 * over a small set of facts are run twice, with the skip off and on, and the
 * callback trace (rule order and activation sequence), the run status and the
 * final fact values must match. */
#include "test_framework.h"
#include <rule_engine/rule_engine.h>
#include "../src/rule_engine/re_internal.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char text[16384];
    size_t size;
} Trace;

static re_status_t record(re_engine_t *engine, re_facts_t *facts, const re_rule_event_t *event,
                          void *context) {
    (void)engine;
    (void)facts;
    Trace *t = (Trace *)context;
    int wrote = snprintf(t->text + t->size, sizeof(t->text) - t->size, "%.*s@%llu;",
                         (int)event->rule_name.size, event->rule_name.data,
                         (unsigned long long)event->activation_sequence);
    if (wrote > 0 && (size_t)wrote < sizeof(t->text) - t->size) t->size += (size_t)wrote;
    return RE_STATUS_OK;
}

static uint64_t g_seed;
static uint32_t rnd(uint32_t n) {
    g_seed = g_seed * 6364136223846793005ull + 1442695040888963407ull;
    return (uint32_t)((g_seed >> 33) % n);
}

/* The first INITIAL names exist before the run; the rest are created by
 * actions, so conditions that read them start as failed reads (not in the
 * read-set) and only match once the fact appears. */
static const char *const k_names[] = {"A", "B", "C", "D", "Obj.x", "Obj.y", "Cnt", "Flag",
                                      "E", "F", "G", "H", "New", "Late"};
enum { NAME_COUNT = 14, INITIAL = 12 };

/* One random condition: a comparison, a conjunction, a negation or (rarely)
 * an exists over the Obj prefix, so quantifier candidates are exercised. */
static size_t condition(char *out, size_t cap) {
    uint32_t kind = rnd(10);
    const char *a = k_names[rnd(NAME_COUNT)];
    const char *b = k_names[rnd(NAME_COUNT)];
    static const char *const ops[] = {"==", "!=", ">", "<", ">="};
    const char *op = ops[rnd(5)];
    int v = (int)rnd(4);
    int w = (int)rnd(4);
    if (kind < 5) return (size_t)snprintf(out, cap, "%s %s %d", a, op, v);
    if (kind < 8) return (size_t)snprintf(out, cap, "%s %s %d and %s < %d", a, op, v, b, w + 1);
    if (kind < 9) {
        /* sometimes read every initial fact, more than the read-set holds,
         * with the deciding comparison last */
        if (rnd(3) == 0) {
            size_t used = 0u;
            for (uint32_t i = 0; i < INITIAL; i++)
                used += (size_t)snprintf(out + used, cap - used, "%s >= 0 and ", k_names[i]);
            return used + (size_t)snprintf(out + used, cap - used, "%s < %d", k_names[8u + rnd(4)], v + 1);
        }
        return (size_t)snprintf(out, cap, "!(%s == %d)", a, v);
    }
    return (size_t)snprintf(out, cap, "exists(Obj.x > %d)", v);
}

static size_t action(char *out, size_t cap) {
    uint32_t kind = rnd(6);
    if (kind == 4) return (size_t)snprintf(out, cap, "retract($Obj);");
    if (kind == 5) return (size_t)snprintf(out, cap, "%s = %d;", rnd(2) ? "New" : "Late", (int)rnd(4));
    const char *t = k_names[rnd(NAME_COUNT)];
    if (kind == 0) return (size_t)snprintf(out, cap, "%s = %d;", t, (int)rnd(4));
    if (kind == 1) return (size_t)snprintf(out, cap, "%s = %s + 1;", t, t);
    if (kind == 2) return (size_t)snprintf(out, cap, "Cnt = Cnt + 1;");
    return (size_t)snprintf(out, cap, "%s = 1;", t);
}

static size_t program_text(char *out, size_t cap, uint32_t rules) {
    size_t used = 0u;
    for (uint32_t r = 0; r < rules && used < cap; r++) {
        char cond[512], act[128];
        condition(cond, sizeof(cond));
        action(act, sizeof(act));
        int salience = (int)rnd(3);
        const char *no_loop = rnd(4) == 0 ? " no-loop true;" : "";
        used += (size_t)snprintf(out + used, cap - used, "rule \"R%u\" salience %d {%s when %s then %s }\n",
                                 r, salience, no_loop, cond, act);
    }
    return used;
}

typedef struct {
    re_status_t load;
    re_status_t run;
    Trace trace;
    re_value_t values[NAME_COUNT];
    re_status_t got[NAME_COUNT];
} Outcome;

static void run_once(const char *src, size_t size, int skip, Outcome *out) {
    memset(out, 0, sizeof(*out));
    re_limits_t limits = {65536u, 1024u, 1024u, 1024u, 200u, 4096u};
    re_engine_t *engine = re_engine_create(NULL, &limits);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_engine_set_skip_unchanged(engine, skip);
    out->load = re_program_load(NULL, (re_string_t){src, size}, NULL, &program);
    if (out->load == RE_STATUS_OK) {
        for (uint32_t i = 0; i < INITIAL; i++) {
            re_value_t v = {RE_VALUE_INT64, {.int64_value = (int64_t)rnd(3)}};
            re_facts_set(facts, (re_string_t){k_names[i], strlen(k_names[i])}, &v);
        }
        if (re_engine_install(engine, program) != RE_STATUS_OK) re_program_destroy(program);
        re_callbacks_t callbacks = {record, &out->trace};
        out->run = re_engine_run(engine, facts, NULL, &callbacks);
        for (uint32_t i = 0; i < NAME_COUNT; i++)
            out->got[i] = re_facts_get(facts, (re_string_t){k_names[i], strlen(k_names[i])}, &out->values[i]);
    }
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

static bool same(const Outcome *a, const Outcome *b) {
    if (a->load != b->load || a->run != b->run) return false;
    if (a->trace.size != b->trace.size || memcmp(a->trace.text, b->trace.text, a->trace.size) != 0) return false;
    for (uint32_t i = 0; i < NAME_COUNT; i++) {
        if (a->got[i] != b->got[i]) return false;
        if (a->got[i] == RE_STATUS_OK && memcmp(&a->values[i], &b->values[i], sizeof(re_value_t)) != 0 &&
            !(a->values[i].type == b->values[i].type && a->values[i].type == RE_VALUE_INT64 &&
              a->values[i].as.int64_value == b->values[i].as.int64_value))
            return false;
    }
    return true;
}

TEST(skip_matches_full_rematch_on_random_programs) {
    static char src[32768];
    static Outcome off, on;
    uint32_t fired_runs = 0u;
    for (uint32_t seed = 1u; seed <= 400u; seed++) {
        g_seed = seed;
        size_t size = program_text(src, sizeof(src), 4u + rnd(20));
        uint64_t facts_seed = g_seed;
        g_seed = facts_seed;
        run_once(src, size, 0, &off);
        g_seed = facts_seed;
        run_once(src, size, 1, &on);
        if (!same(&off, &on)) {
            printf("seed %u differs\n--- program ---\n%s--- off: %d %.*s\n--- on:  %d %.*s\n", seed, src,
                   (int)off.run, (int)off.trace.size, off.trace.text, (int)on.run, (int)on.trace.size,
                   on.trace.text);
        }
        ASSERT_TRUE(same(&off, &on));
        if (off.trace.size > 0u) fired_runs++;
        if (off.load != RE_STATUS_OK) printf("seed %u load %d\n%s", seed, (int)off.load, src);
        ASSERT_EQ(off.load, RE_STATUS_OK);
    }
    /* the generator must actually exercise firing chains */
    ASSERT_TRUE(fired_runs > 200u);
}

/* The skip actually skips: on a large independent rule set, far fewer rule
 * matches run with the skip on. */
TEST(skip_reduces_rematches_on_independent_rules) {
    static char src[65536];
    size_t used = 0u;
    for (uint32_t i = 0; i < 200u; i++)
        used += (size_t)snprintf(src + used, sizeof(src) - used,
                                 "rule \"R%u\" { when Score > %u then F%u = 1; }\n", i, i, i % 20u);
    uint64_t matches[2];
    for (int skip = 0; skip < 2; skip++) {
        re_engine_t *engine = re_engine_create(NULL, NULL);
        re_facts_t *facts = re_facts_create(NULL, NULL);
        re_program_t *program = NULL;
        re_engine_set_skip_unchanged(engine, skip);
        ASSERT_EQ(re_program_load(NULL, (re_string_t){src, used}, NULL, &program), RE_STATUS_OK);
        ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
        re_value_t score = {RE_VALUE_INT64, {.int64_value = 100}};
        ASSERT_EQ(re_facts_set(facts, (re_string_t){"Score", 5u}, &score), RE_STATUS_OK);
        ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
        matches[skip] = re_engine_match_count(engine);
        re_facts_destroy(facts);
        re_engine_destroy(engine);
    }
    ASSERT_TRUE(matches[1] * 10u < matches[0]);
}

static uint32_t run_trace(const char *src, int skip, const char *preset, Trace *trace) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    memset(trace, 0, sizeof(*trace));
    re_engine_set_skip_unchanged(engine, skip);
    if (re_program_load(NULL, (re_string_t){src, strlen(src)}, NULL, &program) != RE_STATUS_OK) return 0u;
    if (re_engine_install(engine, program) != RE_STATUS_OK) return 0u;
    if (preset != NULL) {
        re_value_t one = {RE_VALUE_INT64, {.int64_value = 1}};
        static const char *const extra[] = {"Obj.x", "A", "B", "C", "D", "E", "F", "G", "H"};
        re_facts_set(facts, (re_string_t){preset, strlen(preset)}, &one);
        for (size_t k = 0; k < sizeof(extra) / sizeof(extra[0]); k++) {
            re_value_t zero = {RE_VALUE_INT64, {.int64_value = 0}};
            re_facts_set(facts, (re_string_t){extra[k], strlen(extra[k])}, &zero);
        }
    }
    re_callbacks_t callbacks = {record, trace};
    re_status_t status = re_engine_run(engine, facts, NULL, &callbacks);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
    return status == RE_STATUS_OK ? 1u : 0u;
}

/* Targeted cases for each way a rule's answer can change without a write to
 * a fact it read: a fact it failed to read is created later in the run, a
 * retract flag appears on a root it read, and a condition reads more facts
 * than the read-set holds. The skip must fire the same rules in the same
 * order as the full re-match. */
TEST(skip_handles_created_facts_retract_flags_and_overflow) {
    static const char *const programs[] = {
        /* Waits fails on the missing Later; Make creates it afterwards. */
        "rule \"Waits\" salience 1 { when Later == 1 then Seen = 1; }\n"
        "rule \"Make\" { when Go == 1 then Later = 1; }\n",
        /* Reads matches first; Kill then retracts Obj, which must hide it. */
        /* Reads first fails (Obj.x == 0) and is cached; Set makes it match,
         * then Kill retracts Obj, which must hide it from the later pass. */
        "rule \"Kill\" salience 9 { when Go == 2 then retract($Obj); Go = 3; }\n"
        "rule \"Reads\" salience 5 { when Obj.x == 1 then Hit = 1; }\n"
        "rule \"Set\" { when Go == 1 then Obj.x = 1; Go = 2; }\n",
        /* Wide reads nine facts; Step changes the ninth, past the cap. */
        "rule \"Wide\" salience 5 { when A >= 0 and B >= 0 and C >= 0 and D >= 0 and E >= 0 and F >= 0 and "
        "G >= 0 and H >= 0 and Go == 2 then Seen = 1; }\n"
        "rule \"Step\" { when Go == 1 then Go = 2; }\n",
    };
    static const char *const presets[] = {"Go", "Go", "Go"};
    Trace off, on;
    for (uint32_t i = 0; i < sizeof(programs) / sizeof(programs[0]); i++) {
        char src[1024];
        snprintf(src, sizeof(src), "%s", programs[i]);
        uint32_t a = run_trace(src, 0, presets[i], &off);
        uint32_t b = run_trace(src, 1, presets[i], &on);
        if (off.size != on.size || memcmp(off.text, on.text, off.size) != 0)
            printf("case %u off %.*s on %.*s\n", i, (int)off.size, off.text, (int)on.size, on.text);
        ASSERT_EQ(a, 1u);
        ASSERT_EQ(b, 1u);
        ASSERT_EQ(off.size, on.size);
        ASSERT_EQ(memcmp(off.text, on.text, off.size), 0);
        ASSERT_TRUE(off.size > 0u);
        /* the rule each case is about must actually fire */
        static const char *const must[] = {"Waits@", "Kill@", "Wide@"};
        if (strstr(off.text, must[i]) == NULL) printf("case %u trace %.*s\n", i, (int)off.size, off.text);
        ASSERT_TRUE(strstr(off.text, must[i]) != NULL);
        /* after the retract, Reads must not fire */
        if (i == 1u) ASSERT_TRUE(strstr(off.text, "Reads@") == NULL);
    }
}

/* Changes that reach a rule through a structured member and a fact created
 * by an action. Obj is an object fact; Watch reads Obj.x and must
 * fire after Bump updates the member; Gone reads Tmp, which does not exist
 * until Back creates it. Each change happens inside an action, i.e. in a
 * transaction that is committed before the next pass. */
static uint32_t run_structured(int skip, Trace *trace) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_value_handle_t *obj = NULL;
    re_value_t zero = {RE_VALUE_INT64, {.int64_value = 0}};
    re_value_t one = {RE_VALUE_INT64, {.int64_value = 1}};
    static const char src[] =
        /* The watchers carry the higher salience so the first pass matches
         * them (false) before the writers fire; the writers' changes are then
         * only seen through a later pass, where the skip applies. */
        "rule \"Watch\" salience 9 { when Obj.x == 5 then Seen = 1; }\n"
        "rule \"Gone\" salience 8 { when Tmp == 1 then Hit = Hit + 1; }\n"
        "rule \"Bump\" salience 2 { when Go == 1 then Obj.x = 5; Go = 2; }\n"
        "rule \"Back\" salience 1 { when Go == 2 then Tmp = 1; Go = 3; }\n";
    memset(trace, 0, sizeof(*trace));
    re_engine_set_skip_unchanged(engine, skip);
    if (re_value_create_object(facts, &obj) != RE_STATUS_OK) return 0u;
    re_value_object_set(obj, (re_string_t){"x", 1u}, &zero);
    re_facts_set_value(facts, (re_string_t){"Obj", 3u}, obj);
    re_value_destroy(obj);
    re_facts_set(facts, (re_string_t){"Go", 2u}, &one);
    re_facts_set(facts, (re_string_t){"Hit", 3u}, &zero);
    if (re_program_load(NULL, (re_string_t){src, sizeof(src) - 1u}, NULL, &program) != RE_STATUS_OK) return 0u;
    if (re_engine_install(engine, program) != RE_STATUS_OK) return 0u;
    re_callbacks_t callbacks = {record, trace};
    re_status_t status = re_engine_run(engine, facts, NULL, &callbacks);
    re_value_t seen;
    uint32_t ok = status == RE_STATUS_OK &&
                  re_facts_get(facts, (re_string_t){"Seen", 4u}, &seen) == RE_STATUS_OK;
    re_facts_destroy(facts);
    re_engine_destroy(engine);
    return ok ? 1u : 0u;
}

TEST(skip_sees_structured_member_writes_and_new_facts) {
    Trace off, on;
    ASSERT_EQ(run_structured(0, &off), 1u);
    ASSERT_EQ(run_structured(1, &on), 1u);
    if (off.size != on.size || memcmp(off.text, on.text, off.size) != 0)
        printf("off %.*s\non  %.*s\n", (int)off.size, off.text, (int)on.size, on.text);
    ASSERT_EQ(off.size, on.size);
    ASSERT_EQ(memcmp(off.text, on.text, off.size), 0);
    ASSERT_TRUE(strstr(off.text, "Watch@") != NULL);
    ASSERT_TRUE(strstr(off.text, "Gone@") != NULL);
}

/* ---- Counterexamples found in review ----
 * Each case runs a program with the skip off and on and compares the
 * callback traces. They cover: an activation dropped at pop time by an
 * agenda-focus change (must be re-pushed after focus returns), `X in Arr`
 * (array operand not in the read-set), members and array items created on
 * an existing structured root, function calls nested in arithmetic, and
 * goal() conditions that reach another rule's quantifier or function call. */
typedef struct { char text[8192]; size_t size; } ProbeTrace;
static re_status_t probe_record(re_engine_t *e, re_facts_t *f, const re_rule_event_t *ev, void *ctx) {
    (void)e; (void)f; ProbeTrace *t = ctx;
    int w = snprintf(t->text + t->size, sizeof(t->text) - t->size, "%.*s@%llu;",
                     (int)ev->rule_name.size, ev->rule_name.data, (unsigned long long)ev->activation_sequence);
    if (w > 0) t->size += (size_t)w;
    return RE_STATUS_OK;
}

static int64_t g_tick;
static re_status_t tick(re_engine_t *e, re_facts_t *f, const re_value_t *a, size_t n, re_value_t *out, void *c) {
    (void)e; (void)f; (void)a; (void)n; (void)c;
    out->type = RE_VALUE_INT64; out->as.int64_value = ++g_tick; return RE_STATUS_OK;
}
typedef void (*setup_fn)(re_facts_t *, re_program_t *);

static re_status_t probe_run(const char *src, int skip, setup_fn setup, ProbeTrace *t, uint64_t *matches) {
    re_engine_t *e = re_engine_create(NULL, NULL);
    re_facts_t *f = re_facts_create(NULL, NULL);
    re_program_t *p = NULL;
    memset(t, 0, sizeof(*t));
    re_engine_set_skip_unchanged(e, skip);
    re_status_t s = re_program_load(NULL, (re_string_t){src, strlen(src)}, NULL, &p);
    if (s != RE_STATUS_OK) { printf("load %d\n", (int)s); return s; }
    if (setup) setup(f, p);
    s = re_engine_install(e, p);
    if (s != RE_STATUS_OK) { printf("install %d\n", (int)s); return s; }
    { re_function_descriptor_t d = {sizeof(d), RE_ABI_VERSION_MAJOR, {"Tick",4}, tick, NULL, NULL}; re_function_t *fn; re_engine_register_function(e, &d, &fn); }
    re_callbacks_t cb = {probe_record, t};
    s = re_engine_run(e, f, NULL, &cb);
    *matches = re_engine_match_count(e);
    re_facts_destroy(f); re_engine_destroy(e);
    return s;
}

static int check(const char *name, const char *src, setup_fn setup) {
    ProbeTrace off, on; uint64_t m0, m1;
    re_status_t a = probe_run(src, 0, setup, &off, &m0);
    re_status_t b = probe_run(src, 1, setup, &on, &m1);
    int same = a == b && off.size == on.size && memcmp(off.text, on.text, off.size) == 0;
    if (!same) printf("[DIFF] %s\n  off(%d, %llu matches): %.*s\n  on (%d, %llu matches): %.*s\n", name,
           (int)a, (unsigned long long)m0, (int)off.size, off.text, (int)b, (unsigned long long)m1, (int)on.size, on.text);
    return !same;
}

static void set_int(re_facts_t *f, const char *n, int64_t v) {
    re_value_t x = {RE_VALUE_INT64, {.int64_value = v}};
    re_facts_set(f, (re_string_t){n, strlen(n)}, &x);
}

/* Case 1: agenda-focus change drops a pending activation at pop time without
 * marking it fired; when focus pops back, the full re-match re-pushes it. */
static void setup_focus(re_facts_t *f, re_program_t *p) {
    set_int(f, "Go", 1);
    re_program_set_agenda_focus(p, (re_string_t){"main", 4});
}
static const char focus_src[] =
    "rule \"M1\" salience 10 { agenda-group \"main\"; when Go == 1 then ActivateAgendaGroup(\"g\"); }\n"
    "rule \"M2\" salience 5 { agenda-group \"main\"; when Go == 1 then M2Hit = 1; }\n"
    "rule \"G1\" { agenda-group \"g\"; when Go == 1 then G1Hit = 1; }\n";

/* Case 2: `X in Arr` - the right-hand array fact is not recorded in the
 * read-set, so an append to Arr does not invalidate the cache. */
static void setup_in(re_facts_t *f, re_program_t *p) {
    (void)p;
    set_int(f, "X", 3); set_int(f, "Go", 1);
    re_value_handle_t *arr = NULL;
    re_value_create_array(f, &arr);
    re_value_t one = {RE_VALUE_INT64, {.int64_value = 1}};
    re_value_array_append(arr, &one);
    re_facts_set_value(f, (re_string_t){"Arr", 3}, arr);
    re_value_destroy(arr);
}
static const char in_src[] =
    "rule \"Watch\" salience 5 { when X in Arr then Hit = 1; }\n"
    "rule \"Add\" { when Go == 1 then Arr += 3; Go = 2; }\n";

/* Case 3: pop-time stale drop due to value toggle A->B->A. Reader pending
 * with V==1, a higher-salience rule sets V=2 (stale at pop), then V=1 again.
 * Full re-match re-pushes the original key (not fired) -> fires. */
static void setup_toggle(re_facts_t *f, re_program_t *p) { (void)p; set_int(f, "V", 1); set_int(f, "S", 0); }
static const char toggle_src[] =
    "rule \"Reader\" salience 1 { when V == 1 then Seen = 1; }\n"
    "rule \"Flip\" salience 9 { when S == 0 then V = 2; S = 1; }\n"
    "rule \"Back\" salience 8 { when S == 1 then V = 1; S = 2; }\n";

/* Case 5: retract flag cleared/set to false: structure bump covers it. Re-assert. */
static void setup_retract(re_facts_t *f, re_program_t *p) { (void)p; set_int(f, "Obj.x", 1); set_int(f, "Go", 1); }
static const char retract_src[] =
    "rule \"Reads\" salience 1 { when Obj.x == 1 then Hit = Hit + 1; }\n"
    "rule \"Kill\" salience 9 { when Go == 1 then retract($Obj); Go = 2; }\n"
    "rule \"Revive\" salience 8 { when Go == 2 then _retracted_Obj = false; Go = 3; }\n";

static const char focus2_src[] =
    "rule \"M1\" salience 10 { agenda-group \"main\"; when Trig == 1 then ActivateAgendaGroup(\"g\"); }\n"
    "rule \"M2\" salience 5 { agenda-group \"main\"; when Trig == 1 then M2Hit = 1; }\n"
    "rule \"G1\" { agenda-group \"g\"; when Go == 1 then G1Hit = 1; }\n"
    "rule \"Z\" salience -10 { agenda-group \"main\"; when Go == 1 then Trig = 1; }\n";

/* Member creation on an existing structured root: the failed read of Obj.y
 * leaves nothing in the read-set and set_member does not bump structure. */
static void setup_member(re_facts_t *f, re_program_t *p) {
    (void)p;
    re_value_handle_t *obj = NULL;
    re_value_t zero = {RE_VALUE_INT64, {.int64_value = 0}};
    re_value_create_object(f, &obj);
    re_value_object_set(obj, (re_string_t){"x", 1}, &zero);
    re_facts_set_value(f, (re_string_t){"Obj", 3}, obj);
    re_value_destroy(obj);
    set_int(f, "Go", 1);
}
static const char member_src[] =
    "rule \"Watch\" salience 5 { when Obj.y == 5 then Seen = 1; }\n"
    "rule \"Add\" { when Go == 1 then Obj.y = 5; Go = 2; }\n";
static const char member_method_src[] =
    "rule \"Watch\" salience 5 { when Obj.y == 5 then Seen = 1; }\n"
    "rule \"Add\" { when Go == 1 then $Obj.setY(5); Go = 2; }\n";

/* goal(): reads of the goal rule's condition */
static void setup_goal(re_facts_t *f, re_program_t *p) { (void)p; set_int(f, "Go", 1); set_int(f, "K", 0); }
static const char goal_src[] =
    "rule \"Leaf\" salience -50 { when K == 1 then Nop = 1; }\n"
    "rule \"Top\" salience 5 { when goal(\"Leaf\") then Done = 1; }\n"
    "rule \"Set\" { when Go == 1 then K = 1; Go = 2; }\n";

static void setup_focus3(re_facts_t *f, re_program_t *p) {
    set_int(f, "Go", 1); set_int(f, "G1Hit", 0);
    re_program_set_agenda_focus(p, (re_string_t){"main", 4});
}
static const char focus3_src[] =
    "rule \"M2\" salience 20 { agenda-group \"main\"; when Go == 1 then M2Hit = 1; }\n"
    "rule \"M1\" salience 10 { agenda-group \"main\"; when Go == 1 then ActivateAgendaGroup(\"g\"); }\n"
    "rule \"G1\" { agenda-group \"g\"; when Go == 1 then G1Hit = 1; }\n";
/* M2 must be pending (pushed, not fired) when focus switches: give M1 higher
 * salience but have M2 pushed first in the same pass. */
static const char focus4_src[] =
    "rule \"M1\" salience 10 { agenda-group \"main\"; when Go == 1 then ActivateAgendaGroup(\"g\"); }\n"
    "rule \"M2\" salience 5 { agenda-group \"main\"; when Trig == 1 then M2Hit = 1; }\n"
    "rule \"G1\" { agenda-group \"g\"; when Go == 1 then G1Hit = 1; }\n"
    "rule \"Z\" salience 20 { agenda-group \"main\"; when Go == 1 then Trig = 1; }\n";

static void setup_arr(re_facts_t *f, re_program_t *p) { setup_in(f, p); }
static const char arr_idx_src[] =
    "rule \"Watch\" salience 5 { when Arr.1 == 3 then Hit = 1; }\n"
    "rule \"Add\" { when Go == 1 then Arr += 3; Go = 2; }\n";
static const char reset_src[] =
    "rule \"Watch\" salience 5 { when Obj.x == 0 then Hit = 1; }\n"
    "rule \"Add\" { when Go == 1 then Obj.x = 7; Go = 2; }\n";
static void setup_tick(re_facts_t *f, re_program_t *p) { (void)p; g_tick = 0; set_int(f, "Go", 1); set_int(f, "N", 0); }
static const char tick_src[] =
    "rule \"Late\" salience 5 { when 0 + Tick() >= 3 then Hit = 1; }\n"
    "rule \"Spin\" { when N < 4 then N = N + 1; }\n";
static const char rnd_src[] =
    "rule \"Lucky\" salience 5 { when 0 + random(4) == 3 then Hit = 1; }\n"
    "rule \"Spin\" { when N < 6 then N = N + 1; }\n";

static void setup_two_obj(re_facts_t *f, re_program_t *p) {
    (void)p;
    re_value_t zero = {RE_VALUE_INT64, {.int64_value = 0}};
    const char *names[] = {"Obj", "ObjB"};
    for (int i = 0; i < 2; i++) {
        re_value_handle_t *obj = NULL;
        re_value_create_object(f, &obj);
        re_value_object_set(obj, (re_string_t){"x", 1}, &zero);
        re_facts_set_value(f, (re_string_t){names[i], strlen(names[i])}, obj);
        re_value_destroy(obj);
    }
    set_int(f, "Go", 1);
}
static const char goal_exists_src[] =
    "rule \"Leaf\" salience -50 { when exists(Obj.x > 1) then Nop = 1; }\n"
    "rule \"Top\" salience 5 { when goal(\"Leaf\") then Done = 1; }\n"
    "rule \"Set\" { when Go == 1 then ObjB.x = 5; Go = 2; }\n";
static const char goal_tick_src[] =
    "rule \"Leaf\" salience -50 { when Tick() >= 3 then Nop = 1; }\n"
    "rule \"Top\" salience 5 { when goal(\"Leaf\") then Done = 1; }\n"
    "rule \"Spin\" { when N < 4 then N = N + 1; }\n";


/* Obj = {a: {z: 1}}: reading Obj.a fails (a holds an object); replacing it
 * with a scalar must make the reader match again. */
static void setup_nested(re_facts_t *f, re_program_t *p) {
    (void)p;
    re_value_handle_t *obj = NULL, *inner = NULL;
    re_value_t one = {RE_VALUE_INT64, {.int64_value = 1}};
    re_value_create_object(f, &obj);
    re_value_create_object(f, &inner);
    re_value_object_set(inner, (re_string_t){"z", 1}, &one);
    re_value_object_set_value(obj, (re_string_t){"a", 1}, inner);
    re_value_object_set_value(obj, (re_string_t){"A", 1}, inner);
    re_facts_set_value(f, (re_string_t){"Obj", 3}, obj);
    re_value_destroy(inner);
    re_value_destroy(obj);
    set_int(f, "Go", 1);
}
static const char nested_setter_src[] =
    "rule \"Watch\" salience 5 { when Obj.A == 5 then Seen = 1; }\n"
    "rule \"Add\" { when Go == 1 then $Obj.setA(5); Go = 2; }\n";
static const char nested_assign_src[] =
    "rule \"Watch\" salience 5 { when Obj.a == 5 then Seen = 1; }\n"
    "rule \"Add\" { when Go == 1 then Obj.a = 5; Go = 2; }\n";

TEST(review_counterexamples_match_the_full_rematch) {
    int bad = 0;
    bad += check("agenda focus pop-back", focus_src, setup_focus);
    bad += check("in-array RHS not in read-set", in_src, setup_in);
    bad += check("value toggle A->B->A stale pop", toggle_src, setup_toggle);
    bad += check("retract then clear flag", retract_src, setup_retract);
    bad += check("agenda focus pop-back v2", focus2_src, setup_focus);
    bad += check("member creation Obj.y =", member_src, setup_member);
    bad += check("member creation setY()", member_method_src, setup_member);
    bad += check("goal() read-set", goal_src, setup_goal);
    bad += check("agenda focus with preset fact", focus2_src, setup_focus3);
    bad += check("agenda focus v4", focus4_src, setup_focus3);
    bad += check("agenda focus v3", focus3_src, setup_focus3);
    bad += check("Arr.1 failed read, then append", arr_idx_src, setup_arr);
    bad += check("member write via dotted target", reset_src, setup_member);
    bad += check("host function nested in arithmetic", tick_src, setup_tick);
    bad += check("random() nested in arithmetic", rnd_src, setup_tick);
    bad += check("goal() into exists over candidates", goal_exists_src, setup_two_obj);
    bad += check("goal() into impure condition", goal_tick_src, setup_tick);
    bad += check("object member replaced by scalar (setter)", nested_setter_src, setup_nested);
    bad += check("object member replaced by scalar (assign)", nested_assign_src, setup_nested);
    ASSERT_EQ(bad, 0);
}

TEST_MAIN_BEGIN()
    RUN_TEST(skip_matches_full_rematch_on_random_programs);
    RUN_TEST(skip_reduces_rematches_on_independent_rules);
    RUN_TEST(skip_handles_created_facts_retract_flags_and_overflow);
    RUN_TEST(skip_sees_structured_member_writes_and_new_facts);
    RUN_TEST(review_counterexamples_match_the_full_rematch);
TEST_MAIN_END()
