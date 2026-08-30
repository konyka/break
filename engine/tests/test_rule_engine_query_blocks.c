#include "test_framework.h"
#include <rule_engine/rule_engine.h>
#include <string.h>

/*
 * GRL query blocks (Task A7, upstream rust-rule-engine v1.21.4 grl_query.rs):
 * the top-level `query "Name" { goal: ...; ... }` form, executed through
 * re_engine_run_query / re_engine_run_queries on top of the Phase-3 bounded
 * backward machine. Covered: the full field surface and defaults, the when
 * gate, on-success/on-failure dispatch (on-missing folds into on-failure -
 * our machine does not track upstream's missing_facts list), textual
 * &&/||/parenthesized goal splitting, direct != evaluation against working
 * memory, strategy/max-depth pass-through, the memoization toggle mapping
 * onto the shared proof graph, and coexistence with forward rules.
 */

static re_string_t text(const char *value) { return (re_string_t){value, strlen(value)}; }
static re_value_t integer(int64_t value) { return (re_value_t){RE_VALUE_INT64, {.int64_value = value}}; }
static re_value_t boolean(int value) { return (re_value_t){RE_VALUE_BOOL, {.boolean = value}}; }
static re_value_t string(const char *value) { return (re_value_t){RE_VALUE_STRING, {.string = {value, strlen(value)}}}; }

static void install_source(re_engine_t *engine, const char *source) {
    re_program_t *program = NULL;
    ASSERT_EQ(re_program_load(NULL, text(source), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
}

static void assert_int_fact(re_facts_t *facts, const char *name, int64_t expected) {
    re_value_t out = {RE_VALUE_NONE, {0}};
    ASSERT_EQ(re_facts_get(facts, text(name), &out), RE_STATUS_OK);
    ASSERT_EQ(out.type, RE_VALUE_INT64);
    ASSERT_EQ(out.as.int64_value, expected);
}

static void assert_double_fact(re_facts_t *facts, const char *name, double expected) {
    re_value_t out = {RE_VALUE_NONE, {0}};
    ASSERT_EQ(re_facts_get(facts, text(name), &out), RE_STATUS_OK);
    ASSERT_EQ(out.type, RE_VALUE_DOUBLE);
    ASSERT_FLOAT_EQ(out.as.double_value, expected, 1e-9);
}

static void assert_bool_fact(re_facts_t *facts, const char *name, int expected) {
    re_value_t out = {RE_VALUE_NONE, {0}};
    ASSERT_EQ(re_facts_get(facts, text(name), &out), RE_STATUS_OK);
    ASSERT_EQ(out.type, RE_VALUE_BOOL);
    ASSERT_EQ(out.as.boolean, expected);
}

static void assert_string_fact(re_facts_t *facts, const char *name, const char *expected) {
    re_value_t out = {RE_VALUE_NONE, {0}};
    ASSERT_EQ(re_facts_get(facts, text(name), &out), RE_STATUS_OK);
    ASSERT_EQ(out.type, RE_VALUE_STRING);
    ASSERT_TRUE(out.as.string.size == strlen(expected) &&
                memcmp(out.as.string.data, expected, out.as.string.size) == 0);
}

static void assert_no_fact(re_facts_t *facts, const char *name) {
    re_value_t out = {RE_VALUE_NONE, {0}};
    ASSERT_EQ(re_facts_get(facts, text(name), &out), RE_STATUS_NOT_FOUND);
}

TEST(query_full_block_parses_and_installs) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    install_source(engine,
        "query \"CheckVIP\" {"
        " goal: User.IsVIP == true;"
        " strategy: breadth-first;"
        " max-depth: 8;"
        " max-solutions: 4;"
        " enable-memoization: false;"
        " enable-optimization: false;"
        " when: User.Age >= 18;"
        " on-success: { User.DiscountRate = 0.2; LogMessage(\"vip\"); }"
        " on-failure: { LogMessage(\"nope\"); }"
        " on-missing: { Debug(\"missing\"); }"
        "}");
    /* The full block runs end to end: when-gate passes, goal disproved. */
    { re_value_t age = integer(20);
      ASSERT_EQ(re_facts_set(facts, text("User.Age"), &age), RE_STATUS_OK); }
    ASSERT_EQ(re_engine_run_query(engine, facts, text("CheckVIP")), RE_STATUS_OK);
    assert_no_fact(facts, "User.DiscountRate"); /* goal did not prove */
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(query_defaults_minimal_block) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    install_source(engine,
        "query \"Q\" { goal: Missing == 1; on-success: { S = 1; } on-failure: { F = 1; } }");
    ASSERT_EQ(re_engine_run_queries(engine, facts), RE_STATUS_OK);
    assert_no_fact(facts, "S");
    assert_int_fact(facts, "F", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(query_parse_errors_are_atomic) {
    static const char *bad_sources[] = {
        "query \"Q\" { strategy: depth-first; }",                       /* goal is required */
        "query \"Q\" { goal: X == 1; strategy: sideways; }",            /* unknown strategy */
        "query \"Q\" { goal: X == 1; max-depth: -1; }",                 /* negative depth */
        "query \"Q\" { goal: X == 1; max-solutions: two; }",            /* non-numeric */
        "query \"Q\" { goal: X == 1; enable-memoization: yes; }",       /* non-boolean */
        "query \"Q\" { goal: X == 1; goal: Y == 2; }",                  /* duplicate field */
        "query \"Q\" { goal: X == 1; bogus: 1; }",                      /* unknown field */
        "query \"Q\" { goal: X == 1 }",                                 /* missing ';' */
        "query \"Q\" { goal: (X == 1; }",                               /* unbalanced parens */
        "query \"Q\" { goal: ; }",                                      /* empty goal */
        "query \"Q\" { goal: X == 1;",                                  /* unterminated block */
        "query \"Q\" { goal: X == 1; on-success: { A == 1; } }",        /* not an assignment */
        "query \"Q\" { goal: X == 1; on-success: { A = [1,2]; } }",     /* array value */
        "query \"Q\" { goal: X == 1; on-success: { Obj.M(); } }",       /* receiver call */
        "query \"Q\" { goal: X == 1; on-success: { A = 1 } }",          /* missing ';' in block */
        "query \"Q\" { goal: X == 1; when: A == 1; when: B == 2; }",    /* duplicate when */
    };
    size_t i;
    for (i = 0u; i < sizeof(bad_sources) / sizeof(bad_sources[0]); ++i) {
        re_program_t *program = NULL;
        ASSERT_EQ(re_program_load(NULL, text(bad_sources[i]), NULL, &program), RE_STATUS_PARSE_ERROR);
        ASSERT_TRUE(program == NULL);
    }
}

TEST(query_unknown_name_and_bad_arguments) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    install_source(engine, "query \"Q\" { goal: X == 1; }");
    ASSERT_EQ(re_engine_run_query(engine, facts, text("Nope")), RE_STATUS_NOT_FOUND);
    ASSERT_EQ(re_engine_run_query(engine, facts, text("Q")), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run_query(NULL, facts, text("Q")), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_engine_run_query(engine, NULL, text("Q")), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_engine_run_queries(NULL, facts), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_engine_run_queries(engine, NULL), RE_STATUS_INVALID_ARGUMENT);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
    /* No program installed at all. */
    engine = re_engine_create(NULL, NULL);
    facts = re_facts_create(NULL, NULL);
    ASSERT_EQ(re_engine_run_queries(engine, facts), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_engine_run_query(engine, facts, text("Q")), RE_STATUS_INVALID_ARGUMENT);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(query_empty_program_is_noop) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    install_source(engine, "rule \"R\" { when true then X = 1; }");
    ASSERT_EQ(re_engine_run_queries(engine, facts), RE_STATUS_OK);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(query_when_gate_true_runs) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t ready = boolean(1);
    ASSERT_EQ(re_facts_set(facts, text("Ready"), &ready), RE_STATUS_OK);
    install_source(engine,
        "rule \"Base\" { when true then X = 1; }"
        "query \"Q\" { goal: Base; when: Ready == true;"
        " on-success: { S = 1; } on-failure: { F = 1; } }");
    ASSERT_EQ(re_engine_run_query(engine, facts, text("Q")), RE_STATUS_OK);
    assert_int_fact(facts, "S", 1);
    assert_no_fact(facts, "F");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(query_when_gate_false_skips_everything) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t ready = boolean(0);
    ASSERT_EQ(re_facts_set(facts, text("Ready"), &ready), RE_STATUS_OK);
    install_source(engine,
        "rule \"Base\" { when true then X = 1; }"
        "query \"Q\" { goal: Base; when: Ready == true;"
        " on-success: { S = 1; } on-failure: { F = 1; } }");
    ASSERT_EQ(re_engine_run_query(engine, facts, text("Q")), RE_STATUS_OK);
    assert_no_fact(facts, "S");
    assert_no_fact(facts, "F");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(query_when_gate_missing_fact_skips) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    install_source(engine,
        "rule \"Base\" { when true then X = 1; }"
        "query \"Q\" { goal: Base; when: Missing.field == 1;"
        " on-success: { S = 1; } on-failure: { F = 1; } }");
    ASSERT_EQ(re_engine_run_query(engine, facts, text("Q")), RE_STATUS_OK);
    assert_no_fact(facts, "S");
    assert_no_fact(facts, "F");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(query_when_gate_compound_expression) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t age = integer(20);
    re_value_t active = boolean(1);
    ASSERT_EQ(re_facts_set(facts, text("Age"), &age), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("Active"), &active), RE_STATUS_OK);
    install_source(engine,
        "rule \"Base\" { when true then X = 1; }"
        "query \"Q\" { goal: Base; when: Age >= 18 and Active == true; on-success: { S = 1; } }");
    ASSERT_EQ(re_engine_run_query(engine, facts, text("Q")), RE_STATUS_OK);
    assert_int_fact(facts, "S", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(query_on_success_scalar_assignments) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    install_source(engine,
        "rule \"Base\" { when true then X = 1; }"
        "query \"Q\" { goal: Base;"
        " on-success: { Score = 95; Rate = 0.25; Flag = true; Label = \"vip\"; }"
        " on-failure: { F = 1; } }");
    ASSERT_EQ(re_engine_run_query(engine, facts, text("Q")), RE_STATUS_OK);
    assert_int_fact(facts, "Score", 95);
    assert_double_fact(facts, "Rate", 0.25);
    assert_bool_fact(facts, "Flag", 1);
    assert_string_fact(facts, "Label", "vip");
    assert_no_fact(facts, "F");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(query_on_failure_fires) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t z = integer(2);
    ASSERT_EQ(re_facts_set(facts, text("Z"), &z), RE_STATUS_OK);
    install_source(engine,
        "query \"Q\" { goal: Z == 1; on-success: { S = 1; } on-failure: { F = 1; } }");
    ASSERT_EQ(re_engine_run_query(engine, facts, text("Q")), RE_STATUS_OK);
    assert_no_fact(facts, "S");
    assert_int_fact(facts, "F", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(query_on_missing_folds_into_on_failure) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t z = integer(2);
    ASSERT_EQ(re_facts_set(facts, text("Z"), &z), RE_STATUS_OK);
    install_source(engine,
        "query \"Q\" { goal: Z == 1;"
        " on-success: { S = 1; } on-failure: { F = 1; } on-missing: { M = 1; } }");
    ASSERT_EQ(re_engine_run_query(engine, facts, text("Q")), RE_STATUS_OK);
    assert_no_fact(facts, "S");
    assert_int_fact(facts, "F", 1);
    assert_no_fact(facts, "M"); /* our machine tracks no missing_facts list */
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(query_or_goal_split) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t b = integer(2);
    ASSERT_EQ(re_facts_set(facts, text("B"), &b), RE_STATUS_OK);
    install_source(engine,
        "query \"AnyOk\" { goal: A == 1 || B == 2; on-success: { S1 = 1; } on-failure: { F1 = 1; } }"
        "query \"NoneOk\" { goal: A == 1 || B == 3; on-success: { S2 = 1; } on-failure: { F2 = 1; } }");
    ASSERT_EQ(re_engine_run_queries(engine, facts), RE_STATUS_OK);
    assert_int_fact(facts, "S1", 1);
    assert_no_fact(facts, "F1");
    assert_no_fact(facts, "S2");
    assert_int_fact(facts, "F2", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(query_and_goal_split) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t a = integer(1);
    re_value_t b = integer(2);
    ASSERT_EQ(re_facts_set(facts, text("A"), &a), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("B"), &b), RE_STATUS_OK);
    install_source(engine,
        "query \"BothOk\" { goal: A == 1 && B == 2; on-success: { S1 = 1; } on-failure: { F1 = 1; } }"
        "query \"OneBad\" { goal: A == 1 && B == 3; on-success: { S2 = 1; } on-failure: { F2 = 1; } }");
    ASSERT_EQ(re_engine_run_queries(engine, facts), RE_STATUS_OK);
    assert_int_fact(facts, "S1", 1);
    assert_no_fact(facts, "F1");
    assert_no_fact(facts, "S2");
    assert_int_fact(facts, "F2", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(query_complex_goal_precedence_and_parens) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    install_source(engine,
        "query \"OrRight\" { goal: A == 1 || B == 2 && C == 3; on-success: { S1 = 1; } on-failure: { F1 = 1; } }"
        "query \"OrLeft\" { goal: A == 1 || B == 2 && C == 3; on-success: { S2 = 1; } on-failure: { F2 = 1; } }"
        "query \"Wrapped\" { goal: (A == 1 || B == 2 && C == 3); on-success: { S3 = 1; } on-failure: { F3 = 1; } }"
        "query \"Neither\" { goal: A == 1 || B == 2 && C == 3; on-success: { S4 = 1; } on-failure: { F4 = 1; } }");
    /* B && C holds (A does not): the && part of the split carries the OR. */
    { re_value_t v = integer(2);
      ASSERT_EQ(re_facts_set(facts, text("A"), &v), RE_STATUS_OK);
      ASSERT_EQ(re_facts_set(facts, text("B"), &v), RE_STATUS_OK); }
    { re_value_t v = integer(3);
      ASSERT_EQ(re_facts_set(facts, text("C"), &v), RE_STATUS_OK); }
    ASSERT_EQ(re_engine_run_query(engine, facts, text("OrRight")), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run_query(engine, facts, text("Wrapped")), RE_STATUS_OK);
    assert_int_fact(facts, "S1", 1);
    assert_int_fact(facts, "S3", 1);
    /* Now A holds and the && branch fails: the left alternative carries it. */
    { re_value_t v1 = integer(1);
      re_value_t v4 = integer(4);
      ASSERT_EQ(re_facts_set(facts, text("A"), &v1), RE_STATUS_OK);
      ASSERT_EQ(re_facts_set(facts, text("C"), &v4), RE_STATUS_OK); }
    ASSERT_EQ(re_engine_run_query(engine, facts, text("OrLeft")), RE_STATUS_OK);
    assert_int_fact(facts, "S2", 1);
    /* Neither alternative holds. */
    { re_value_t v2 = integer(2);
      ASSERT_EQ(re_facts_set(facts, text("A"), &v2), RE_STATUS_OK); }
    ASSERT_EQ(re_engine_run_query(engine, facts, text("Neither")), RE_STATUS_OK);
    assert_no_fact(facts, "S4");
    assert_int_fact(facts, "F4", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(query_not_equal_evaluates_directly) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t status = string("banned");
    re_value_t level = integer(5);
    ASSERT_EQ(re_facts_set(facts, text("Status"), &status), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("Level"), &level), RE_STATUS_OK);
    /* The rule derives Status = "ok" if it fires, but != subgoals never run
     * rule derivation: the direct fact read decides. */
    install_source(engine,
        "rule \"Derive\" { when true then Status = \"ok\"; }"
        "query \"NeString\" { goal: Status != \"ok\"; on-success: { S1 = 1; } on-failure: { F1 = 1; } }"
        "query \"NeEqual\" { goal: Status != \"banned\"; on-success: { S2 = 1; } on-failure: { F2 = 1; } }"
        "query \"NeIntFalse\" { goal: Level != 5; on-success: { S3 = 1; } on-failure: { F3 = 1; } }"
        "query \"NeIntTrue\" { goal: Level != 6; on-success: { S4 = 1; } on-failure: { F4 = 1; } }"
        "query \"NeMissing\" { goal: Missing != 1; on-success: { S5 = 1; } on-failure: { F5 = 1; } }"
        "query \"NeSemicolon\" { goal: Status != \"a;b\"; on-success: { S6 = 1; } on-failure: { F6 = 1; } }");
    ASSERT_EQ(re_engine_run_queries(engine, facts), RE_STATUS_OK);
    assert_int_fact(facts, "S1", 1);  /* "banned" != "ok": direct read, no derivation */
    assert_no_fact(facts, "F1");
    assert_no_fact(facts, "S2");      /* equal values: != is false */
    assert_int_fact(facts, "F2", 1);
    assert_no_fact(facts, "S3");      /* 5 != 5 is false */
    assert_int_fact(facts, "F3", 1);
    assert_int_fact(facts, "S4", 1);  /* 5 != 6 */
    assert_no_fact(facts, "F4");
    assert_no_fact(facts, "S5");      /* missing fact: not satisfied */
    assert_int_fact(facts, "F5", 1);
    assert_int_fact(facts, "S6", 1);  /* the ';' inside the string did not split */
    assert_no_fact(facts, "F6");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

/* Strategy pass-through: all three spellings prove a chained goal, and the
 * strategy reaches the normalized search options - observable through the
 * shared proof graph, whose key includes the strategy. (A provability
 * difference between DFS and BFS is not observable through this API: the
 * machine abandons same-name alternatives after a depth-exhausted branch, so
 * both strategies report LIMIT in the same configurations.) */
TEST(query_strategy_all_strategies_prove) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    install_source(engine,
        "rule \"Target\" { when goal(\"Mid\") then Deep = 1; }"
        "rule \"Mid\" { when true then M = 1; }"
        "query \"Dfs\" { goal: Target; strategy: depth-first; max-depth: 8; on-success: { DfsOk = 1; } on-failure: { DfsNo = 1; } }"
        "query \"Bfs\" { goal: Target; strategy: breadth-first; max-depth: 8; on-success: { BfsOk = 1; } on-failure: { BfsNo = 1; } }"
        "query \"Iter\" { goal: Target; strategy: iterative; max-depth: 8; on-success: { IterOk = 1; } on-failure: { IterNo = 1; } }");
    ASSERT_EQ(re_engine_run_queries(engine, facts), RE_STATUS_OK);
    assert_int_fact(facts, "DfsOk", 1);
    assert_int_fact(facts, "BfsOk", 1);
    assert_int_fact(facts, "IterOk", 1);
    assert_no_fact(facts, "DfsNo");
    assert_no_fact(facts, "BfsNo");
    assert_no_fact(facts, "IterNo");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(query_strategy_keys_the_proof_graph) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    uint64_t hits = 0u;
    uint64_t misses = 0u;
    /* LogMessage actions leave working memory untouched so the cached entries
     * stay fresh between the two passes. */
    install_source(engine,
        "rule \"Base\" { when true then X = 1; }"
        "query \"Dfs\" { goal: Base; strategy: depth-first; on-success: { LogMessage(\"d\"); } }"
        "query \"Bfs\" { goal: Base; strategy: breadth-first; on-success: { LogMessage(\"b\"); } }"
        "query \"Iter\" { goal: Base; strategy: iterative; on-success: { LogMessage(\"i\"); } }");
    ASSERT_EQ(re_engine_run_queries(engine, facts), RE_STATUS_OK);
    ASSERT_EQ(re_engine_proof_graph_stats(engine, &hits, &misses), RE_STATUS_OK);
    /* Same goal text under three strategies: three distinct cache entries. A
     * strategy field that never reached the search options would collapse the
     * runs into one entry (1 miss + 2 hits). */
    ASSERT_EQ(hits, 0u);
    ASSERT_EQ(misses, 3u);
    ASSERT_EQ(re_engine_run_queries(engine, facts), RE_STATUS_OK);
    ASSERT_EQ(re_engine_proof_graph_stats(engine, &hits, &misses), RE_STATUS_OK);
    ASSERT_EQ(hits, 3u);
    ASSERT_EQ(misses, 3u);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(query_max_depth_honored) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    install_source(engine,
        "rule \"Top\" { when goal(\"Mid\") then T = 1; }"
        "rule \"Mid\" { when goal(\"Base\") then M = 1; }"
        "rule \"Base\" { when true then B = 1; }"
        "query \"ShallowCap\" { goal: Top; max-depth: 1;"
        " on-success: { S1 = 1; } on-failure: { F1 = 1; } }"
        "query \"DeepCap\" { goal: Top; max-depth: 8;"
        " on-success: { S2 = 1; } on-failure: { F2 = 1; } }");
    ASSERT_EQ(re_engine_run_queries(engine, facts), RE_STATUS_OK);
    assert_no_fact(facts, "S1");  /* the chain needs more than one step */
    assert_int_fact(facts, "F1", 1);
    assert_int_fact(facts, "S2", 1);
    assert_no_fact(facts, "F2");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(query_max_solutions_field_accepted) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    install_source(engine,
        "rule \"Target\" { when true then Shallow = 1; }"
        "rule \"Target\" { when true then Also = 1; }"
        "query \"Q\" { goal: Target; max-solutions: 3; on-success: { S = 1; } on-failure: { F = 1; } }");
    ASSERT_EQ(re_engine_run_query(engine, facts, text("Q")), RE_STATUS_OK);
    assert_int_fact(facts, "S", 1);
    assert_no_fact(facts, "F");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(query_memoization_toggle_uses_proof_graph) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    uint64_t hits = 0u;
    uint64_t misses = 0u;
    install_source(engine,
        "rule \"Base\" { when true then X = 1; }"
        "query \"Memo\" { goal: Base; }");
    ASSERT_EQ(re_engine_run_query(engine, facts, text("Memo")), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run_query(engine, facts, text("Memo")), RE_STATUS_OK);
    ASSERT_EQ(re_engine_proof_graph_stats(engine, &hits, &misses), RE_STATUS_OK);
    ASSERT_TRUE(hits >= 1u); /* the second run is served from the shared graph */
    re_facts_destroy(facts);
    re_engine_destroy(engine);
    /* enable-memoization: false bypasses the cache entirely (no stats move). */
    engine = re_engine_create(NULL, NULL);
    facts = re_facts_create(NULL, NULL);
    install_source(engine,
        "rule \"Base\" { when true then X = 1; }"
        "query \"NoMemo\" { goal: Base; enable-memoization: false; }");
    ASSERT_EQ(re_engine_run_query(engine, facts, text("NoMemo")), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run_query(engine, facts, text("NoMemo")), RE_STATUS_OK);
    ASSERT_EQ(re_engine_proof_graph_stats(engine, &hits, &misses), RE_STATUS_OK);
    ASSERT_EQ(hits, 0u);
    ASSERT_EQ(misses, 0u);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(query_unknown_action_call_warns_and_continues) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    install_source(engine,
        "rule \"Base\" { when true then X = 1; }"
        "query \"Q\" { goal: Base;"
        " on-success: { LogMessage(\"hi\"); Print(\"plain\"); Debug(\"dbg\"); Request(\"r\"); Something(\"x\"); S = 1; } }");
    ASSERT_EQ(re_engine_run_query(engine, facts, text("Q")), RE_STATUS_OK);
    assert_int_fact(facts, "S", 1); /* the unknown call warned without failing */
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(query_rules_and_queries_coexist) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t sales = integer(150);
    ASSERT_EQ(re_facts_set(facts, text("Sales"), &sales), RE_STATUS_OK);
    install_source(engine,
        "rule \"Bonus\" { when Sales gt 100 then Eligible = 1; }"
        "query \"Grant\" { goal: Eligible == 1; on-success: { Granted = 1; } on-failure: { Denied = 1; } }");
    /* Queries do not fire rules, and re_engine_run does not run queries. */
    ASSERT_EQ(re_engine_run_queries(engine, facts), RE_STATUS_OK);
    assert_no_fact(facts, "Eligible");
    assert_int_fact(facts, "Denied", 1);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    assert_int_fact(facts, "Eligible", 1);
    assert_no_fact(facts, "Granted"); /* no query ran inside re_engine_run */
    ASSERT_EQ(re_engine_run_query(engine, facts, text("Grant")), RE_STATUS_OK);
    assert_int_fact(facts, "Granted", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(query_hard_error_skips_action_dispatch) {
    /* A hard goal error - here the A2 backward boundary honestly rejecting a
     * rule whose condition is a nested parenthesized quantifier with
     * RE_STATUS_NOT_SUPPORTED - propagates WITHOUT running either action
     * block: on-failure dispatches only on a completed not-proved
     * evaluation, never on an executor error. */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    install_source(engine,
        "rule \"Derive\" { when forall(Alert.level == \"high\") then Goal = 1; }"
        "query \"Q\" { goal: goal(\"Derive\"); on-success: { S = 1; } on-failure: { F = 1; } }");
    ASSERT_EQ(re_engine_run_query(engine, facts, text("Q")), RE_STATUS_NOT_SUPPORTED);
    assert_no_fact(facts, "S");
    assert_no_fact(facts, "F");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(query_run_queries_follow_source_order) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    install_source(engine,
        "rule \"Base\" { when true then X = 1; }"
        "query \"First\" { goal: Base; on-success: { Step = 1; } }"
        "query \"Second\" { goal: Step == 1; on-success: { Reached = 1; } on-failure: { Failed = 1; } }");
    ASSERT_EQ(re_engine_run_queries(engine, facts), RE_STATUS_OK);
    assert_int_fact(facts, "Step", 1);
    assert_int_fact(facts, "Reached", 1); /* Second sees First's write */
    assert_no_fact(facts, "Failed");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
    /* Reverse order: Second runs before Step exists. */
    engine = re_engine_create(NULL, NULL);
    facts = re_facts_create(NULL, NULL);
    install_source(engine,
        "rule \"Base\" { when true then X = 1; }"
        "query \"Second\" { goal: Step == 1; on-success: { Reached = 1; } on-failure: { Failed = 1; } }"
        "query \"First\" { goal: Base; on-success: { Step = 1; } }");
    ASSERT_EQ(re_engine_run_queries(engine, facts), RE_STATUS_OK);
    assert_int_fact(facts, "Failed", 1);
    assert_no_fact(facts, "Reached");
    assert_int_fact(facts, "Step", 1); /* First still ran afterwards */
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST_MAIN_BEGIN()
    RUN_TEST(query_full_block_parses_and_installs);
    RUN_TEST(query_defaults_minimal_block);
    RUN_TEST(query_parse_errors_are_atomic);
    RUN_TEST(query_unknown_name_and_bad_arguments);
    RUN_TEST(query_empty_program_is_noop);
    RUN_TEST(query_when_gate_true_runs);
    RUN_TEST(query_when_gate_false_skips_everything);
    RUN_TEST(query_when_gate_missing_fact_skips);
    RUN_TEST(query_when_gate_compound_expression);
    RUN_TEST(query_on_success_scalar_assignments);
    RUN_TEST(query_on_failure_fires);
    RUN_TEST(query_on_missing_folds_into_on_failure);
    RUN_TEST(query_or_goal_split);
    RUN_TEST(query_and_goal_split);
    RUN_TEST(query_complex_goal_precedence_and_parens);
    RUN_TEST(query_not_equal_evaluates_directly);
    RUN_TEST(query_strategy_all_strategies_prove);
    RUN_TEST(query_strategy_keys_the_proof_graph);
    RUN_TEST(query_max_depth_honored);
    RUN_TEST(query_max_solutions_field_accepted);
    RUN_TEST(query_memoization_toggle_uses_proof_graph);
    RUN_TEST(query_unknown_action_call_warns_and_continues);
    RUN_TEST(query_rules_and_queries_coexist);
    RUN_TEST(query_hard_error_skips_action_dispatch);
    RUN_TEST(query_run_queries_follow_source_order);
TEST_MAIN_END()
