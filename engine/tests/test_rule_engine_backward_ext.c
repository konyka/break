#include "test_framework.h"
#include "../src/rule_engine/re_internal.h"
#include <stdlib.h>
#include <string.h>

/*
 * Query-level negation-as-failure: a goal string with the prefix `NOT `
 * (case-sensitive, immediately followed by whitespace) wraps the remainder as
 * a subgoal run through the existing bounded machine with max_solutions=1.
 *
 * - Subgoal provable (at least one solution) -> RE_QUERY_DISPROVED with zero
 *   solutions.
 * - Subgoal unprovable -> RE_QUERY_PROVED with exactly one solution carrying
 *   empty bindings; the proof trace names the full negated goal text.
 * - A subgoal that exhausts its depth budget reports RE_QUERY_LIMIT instead of
 *   being silently inverted into a success: inverting a limited search would
 *   be unsound, so the limit propagates unchanged.
 * - Only the prefix form is supported (`!(...)` is not a query goal) and there
 *   is no stratification; nested `NOT NOT` prefixes unwrap one level each.
 * - An explicit `goal("RuleName")` query string names the same zero-argument
 *   rule goal the condition-level form does, so it can appear under `NOT `.
 */

static re_string_t text(const char *value) {
    re_string_t result = {value, strlen(value)};
    return result;
}

TEST(query_not_succeeds_when_subgoal_unprovable) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_query_t *query = NULL;
    re_proof_t *proof = NULL;
    re_string_t name;
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("NOT Banned == true"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    ASSERT_EQ(re_query_solution_count(query), 1u);
    ASSERT_EQ(re_query_next(query, &proof), RE_STATUS_OK);
    ASSERT_EQ(re_proof_binding_count(proof), 0u);
    ASSERT_EQ(re_proof_trace_count(proof), 1u);
    ASSERT_EQ(re_proof_trace_get(proof, 0u, &name), RE_STATUS_OK);
    ASSERT_TRUE(name.size == 18u && memcmp(name.data, "NOT Banned == true", 18u) == 0);
    re_proof_destroy(proof);
    re_query_destroy(query);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(query_not_fails_when_subgoal_provable) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_query_t *query = NULL;
    re_proof_t *proof = NULL;
    re_value_t banned = {RE_VALUE_BOOL, {.boolean = 1}};
    ASSERT_EQ(re_facts_set(facts, text("Banned"), &banned), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("NOT Banned == true"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_DISPROVED);
    ASSERT_EQ(re_query_solution_count(query), 0u);
    ASSERT_EQ(re_query_next(query, &proof), RE_STATUS_NOT_FOUND);
    re_query_destroy(query);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(query_not_succeeds_when_subgoal_disproved) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_query_t *query = NULL;
    re_value_t banned = {RE_VALUE_BOOL, {.boolean = 1}};
    ASSERT_EQ(re_facts_set(facts, text("Banned"), &banned), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("NOT Banned == false"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    ASSERT_EQ(re_query_solution_count(query), 1u);
    re_query_destroy(query);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(query_not_with_rule_goal) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_query_t *query = NULL;
    re_value_t flag = {RE_VALUE_INT64, {.int64_value = 1}};
    ASSERT_EQ(re_program_load(NULL, text(
        "rule \"Derive\" { when Flag == 1 then Derived = 1; }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    /* Flag absent: no derivation path exists, so the negated goal proves. */
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("NOT goal(\"Derive\")"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    ASSERT_EQ(re_query_solution_count(query), 1u);
    re_query_destroy(query);
    query = NULL;
    /* Flag == 1: the subgoal proves, so the negated goal is disproved. */
    ASSERT_EQ(re_facts_set(facts, text("Flag"), &flag), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("NOT goal(\"Derive\")"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_DISPROVED);
    ASSERT_EQ(re_query_solution_count(query), 0u);
    re_query_destroy(query);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(query_not_nested_double_prefix) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_query_t *query = NULL;
    re_proof_t *proof = NULL;
    re_string_t name;
    re_value_t banned = {RE_VALUE_BOOL, {.boolean = 1}};
    /* Inner NOT of an unprovable goal proves, so the outer NOT is disproved. */
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("NOT NOT Banned == true"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_DISPROVED);
    ASSERT_EQ(re_query_solution_count(query), 0u);
    re_query_destroy(query);
    query = NULL;
    /* Inner NOT of a provable goal is disproved, so the outer NOT proves. */
    ASSERT_EQ(re_facts_set(facts, text("Banned"), &banned), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("NOT NOT Banned == true"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    ASSERT_EQ(re_query_solution_count(query), 1u);
    ASSERT_EQ(re_query_next(query, &proof), RE_STATUS_OK);
    ASSERT_EQ(re_proof_binding_count(proof), 0u);
    ASSERT_EQ(re_proof_trace_get(proof, 0u, &name), RE_STATUS_OK);
    ASSERT_TRUE(name.size == 22u && memcmp(name.data, "NOT NOT Banned == true", 22u) == 0);
    re_proof_destroy(proof);
    re_query_destroy(query);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(query_not_reports_limit_when_subgoal_is_limited) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_query_t *query = NULL;
    re_query_options_t options = {sizeof(options), 1u, 2u, 0u, 0u};
    ASSERT_EQ(re_program_load(NULL, text(
        "rule \"Base\" { when true then X = 1; }"
        "rule \"Middle\" { when goal(\"Base\") then Y = 1; }"
        "rule \"Top\" { when goal(\"Middle\") then Z = 1; }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("NOT Top"), &options, &query), RE_STATUS_LIMIT);
    ASSERT_EQ(re_query_result(query), RE_QUERY_LIMIT);
    ASSERT_EQ(re_query_solution_count(query), 0u);
    re_query_destroy(query);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(query_not_rejects_empty_remainder) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_query_t *query = NULL;
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("NOT "), NULL, &query), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_TRUE(query == NULL);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("NOT   "), NULL, &query), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_TRUE(query == NULL);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(query_not_prefix_is_case_sensitive) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_query_t *query = NULL;
    re_value_t banned = {RE_VALUE_BOOL, {.boolean = 1}};
    ASSERT_EQ(re_facts_set(facts, text("Banned"), &banned), RE_STATUS_OK);
    /* Lowercase "not" is an ordinary fact-name character, so this stays a fact query. */
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("not Banned == true"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_UNKNOWN);
    ASSERT_EQ(re_query_solution_count(query), 0u);
    re_query_destroy(query);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(query_not_invalidated_by_fact_mutation) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_query_t *query = NULL;
    re_proof_t *proof = NULL;
    /* Only updates to an existing fact notify subscribers (facts.c), so the
     * fact is seeded false first and flipped to true after the query. */
    re_value_t banned = {RE_VALUE_BOOL, {.boolean = 0}};
    ASSERT_EQ(re_facts_set(facts, text("Banned"), &banned), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("NOT Banned == true"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    ASSERT_EQ(re_query_solution_count(query), 1u);
    ASSERT_EQ(re_query_next(query, &proof), RE_STATUS_OK);
    re_proof_destroy(proof);
    proof = NULL;
    banned.as.boolean = 1;
    ASSERT_EQ(re_facts_set(facts, text("Banned"), &banned), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_UNKNOWN);
    ASSERT_EQ(re_query_solution_count(query), 0u);
    ASSERT_EQ(re_query_next(query, &proof), RE_STATUS_NOT_FOUND);
    re_query_destroy(query);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

/*
 * Query aggregation (Task 12): re_engine_query_aggregate runs `pattern` as an
 * ordinary bounded query (max_depth 64, max_solutions capped at 1024) and
 * folds the binding named `field` over the solutions in DFS order. The
 * internal query is destroyed before returning, so no subscription survives.
 *
 * - Empty solution set: COUNT -> int64 0 with RE_STATUS_OK; every other kind
 *   -> RE_STATUS_NOT_FOUND.
 * - A solution whose proof does not bind `field` is skipped by every kind but
 *   COUNT; when no solution binds it the result is RE_STATUS_NOT_FOUND.
 * - SUM/AVERAGE/MIN/MAX reject non-numeric bindings with
 *   RE_STATUS_INVALID_ARGUMENT. Typing: COUNT -> INT64; AVERAGE -> DOUBLE;
 *   SUM/MIN/MAX -> INT64 when every folded value was INT64, else DOUBLE.
 * - FIRST/LAST copy the binding value of the first/last carrier; STRING
 *   results report RE_STATUS_NOT_SUPPORTED because proof string storage is
 *   freed with the internal query.
 */
static const char AGGREGATE_SCORE_RULES[] =
    "rule \"Score\"(S) { when S == 10 then M1 = 1; }"
    "rule \"Score\"(S) { when S == 20 then M2 = 1; }"
    "rule \"Score\"(S) { when S == 30 then M3 = 1; }"
    "rule \"Top\" { when goal(\"Score\", 10) or goal(\"Score\", 20) or goal(\"Score\", 30) then Done = 1; }";

static const char AGGREGATE_COLOR_RULES[] =
    "rule \"Color\"(Item) { when Item == \"red\" then Mark = 1; }"
    "rule \"Color\"(Item) { when Item == \"blue\" then Tone = 1; }"
    "rule \"Top\" { when goal(\"Color\", \"red\") or goal(\"Color\", \"blue\") then Done = 1; }";

static const char AGGREGATE_MIXED_RULES[] =
    "rule \"Measure\"(V) { when V == 10 then A = 1; }"
    "rule \"Measure\"(V) { when V == 2.5 then B = 1; }"
    "rule \"Top\" { when goal(\"Measure\", 10) or goal(\"Measure\", 2.5) then Done = 1; }";

static void aggregate_install(re_engine_t *engine, const char *source) {
    re_program_t *program = NULL;
    ASSERT_EQ(re_program_load(NULL, text(source), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
}

TEST(aggregate_count_counts_solutions) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t out;
    re_string_t no_field = {NULL, 0u};
    aggregate_install(engine, AGGREGATE_SCORE_RULES);
    ASSERT_EQ(re_engine_query_aggregate(engine, facts, RE_ACCUM_COUNT, no_field,
                                        text("Top"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.type, RE_VALUE_INT64);
    ASSERT_EQ(out.as.int64_value, 3);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(aggregate_sum_and_average) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t out;
    aggregate_install(engine, AGGREGATE_SCORE_RULES);
    ASSERT_EQ(re_engine_query_aggregate(engine, facts, RE_ACCUM_SUM, text("S"),
                                        text("Top"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.type, RE_VALUE_INT64);
    ASSERT_EQ(out.as.int64_value, 60);
    ASSERT_EQ(re_engine_query_aggregate(engine, facts, RE_ACCUM_AVERAGE, text("S"),
                                        text("Top"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.type, RE_VALUE_DOUBLE);
    ASSERT_FLOAT_EQ(out.as.double_value, 20.0, 1e-9);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(aggregate_min_max_first_last) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t out;
    aggregate_install(engine, AGGREGATE_SCORE_RULES);
    ASSERT_EQ(re_engine_query_aggregate(engine, facts, RE_ACCUM_MIN, text("S"),
                                        text("Top"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.type, RE_VALUE_INT64);
    ASSERT_EQ(out.as.int64_value, 10);
    ASSERT_EQ(re_engine_query_aggregate(engine, facts, RE_ACCUM_MAX, text("S"),
                                        text("Top"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.type, RE_VALUE_INT64);
    ASSERT_EQ(out.as.int64_value, 30);
    /* DFS solution order: S binds 10, 20, 30 across the three alternatives. */
    ASSERT_EQ(re_engine_query_aggregate(engine, facts, RE_ACCUM_FIRST, text("S"),
                                        text("Top"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.type, RE_VALUE_INT64);
    ASSERT_EQ(out.as.int64_value, 10);
    ASSERT_EQ(re_engine_query_aggregate(engine, facts, RE_ACCUM_LAST, text("S"),
                                        text("Top"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.type, RE_VALUE_INT64);
    ASSERT_EQ(out.as.int64_value, 30);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(aggregate_empty_set_semantics) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t out;
    re_string_t no_field = {NULL, 0u};
    aggregate_install(engine, AGGREGATE_SCORE_RULES);
    ASSERT_EQ(re_engine_query_aggregate(engine, facts, RE_ACCUM_COUNT, no_field,
                                        text("Missing"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.type, RE_VALUE_INT64);
    ASSERT_EQ(out.as.int64_value, 0);
    ASSERT_EQ(re_engine_query_aggregate(engine, facts, RE_ACCUM_SUM, text("S"),
                                        text("Missing"), &out), RE_STATUS_NOT_FOUND);
    ASSERT_EQ(re_engine_query_aggregate(engine, facts, RE_ACCUM_FIRST, text("S"),
                                        text("Missing"), &out), RE_STATUS_NOT_FOUND);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(aggregate_non_numeric_rejected) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t out;
    aggregate_install(engine, AGGREGATE_COLOR_RULES);
    ASSERT_EQ(re_engine_query_aggregate(engine, facts, RE_ACCUM_SUM, text("Item"),
                                        text("Top"), &out), RE_STATUS_INVALID_ARGUMENT);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(aggregate_first_last_string_not_supported) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t out;
    aggregate_install(engine, AGGREGATE_COLOR_RULES);
    ASSERT_EQ(re_engine_query_aggregate(engine, facts, RE_ACCUM_FIRST, text("Item"),
                                        text("Top"), &out), RE_STATUS_NOT_SUPPORTED);
    ASSERT_EQ(re_engine_query_aggregate(engine, facts, RE_ACCUM_LAST, text("Item"),
                                        text("Top"), &out), RE_STATUS_NOT_SUPPORTED);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(aggregate_sum_promotes_to_double) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t out;
    aggregate_install(engine, AGGREGATE_MIXED_RULES);
    ASSERT_EQ(re_engine_query_aggregate(engine, facts, RE_ACCUM_SUM, text("V"),
                                        text("Top"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.type, RE_VALUE_DOUBLE);
    ASSERT_FLOAT_EQ(out.as.double_value, 12.5, 1e-9);
    ASSERT_EQ(re_engine_query_aggregate(engine, facts, RE_ACCUM_AVERAGE, text("V"),
                                        text("Top"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.type, RE_VALUE_DOUBLE);
    ASSERT_FLOAT_EQ(out.as.double_value, 6.25, 1e-9);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(aggregate_rejects_invalid_arguments) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t out;
    re_string_t no_field = {NULL, 0u};
    re_string_t no_pattern = {NULL, 0u};
    aggregate_install(engine, AGGREGATE_SCORE_RULES);
    ASSERT_EQ(re_engine_query_aggregate(engine, facts, (re_accumulator_kind_t)0,
                                        text("S"), text("Top"), &out), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_engine_query_aggregate(engine, facts, (re_accumulator_kind_t)8,
                                        text("S"), text("Top"), &out), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_engine_query_aggregate(engine, facts, RE_ACCUM_SUM, no_field,
                                        text("Top"), &out), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_engine_query_aggregate(engine, facts, RE_ACCUM_SUM, text("S"),
                                        text("Top"), NULL), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_engine_query_aggregate(engine, facts, RE_ACCUM_COUNT, no_field,
                                        no_pattern, &out), RE_STATUS_INVALID_ARGUMENT);
    /* A field no solution binds folds nothing: NOT_FOUND, never a zero. */
    ASSERT_EQ(re_engine_query_aggregate(engine, facts, RE_ACCUM_SUM, text("Nope"),
                                        text("Top"), &out), RE_STATUS_NOT_FOUND);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

/*
 * Search strategies (Task 13): re_query_options_t appends `strategy` (and
 * `disable_shared_proof_graph`, reserved for Task 14) behind the struct_size
 * gate - a struct_size that stops before `strategy` selects the pre-Task-13
 * behavior exactly (single-pass depth-first). RE_QUERY_STRATEGY_BREADTH_FIRST
 * and RE_QUERY_STRATEGY_ITERATIVE are the same iterative-deepening wrapper:
 * the goal is re-proven with max_depth = 1, 2, 4, 8, ... doubling up to the
 * configured max_depth, and the first capped pass that yields at least one
 * solution supplies the result proofs.
 *
 * The two programs below differ only in rule source order: "Target" is
 * provable in one step (`when true`) and via the three-step chain
 * Target -> Mid -> Base. DFS reports proofs in source order, while the
 * deepening wrapper reports the first depth cap that proves anything.
 */
static const char STRATEGY_SHALLOW_FIRST_RULES[] =
    "rule \"Target\" { when true then Shallow = 1; }"
    "rule \"Target\" { when goal(\"Mid\") then Deep = 1; }"
    "rule \"Mid\" { when goal(\"Base\") then M = 1; }"
    "rule \"Base\" { when true then B = 1; }";

static const char STRATEGY_DEEP_FIRST_RULES[] =
    "rule \"Target\" { when goal(\"Mid\") then Deep = 1; }"
    "rule \"Target\" { when true then Shallow = 1; }"
    "rule \"Mid\" { when goal(\"Base\") then M = 1; }"
    "rule \"Base\" { when true then B = 1; }";

static re_status_t strategy_query(re_engine_t *engine, re_facts_t *facts,
                                  const char *goal, uint32_t strategy,
                                  re_query_t **out_query) {
    re_query_options_t options;
    memset(&options, 0, sizeof(options));
    options.struct_size = (uint32_t)sizeof(options);
    options.max_depth = 64u;
    options.max_solutions = 8u;
    options.strategy = strategy;
    return re_engine_query_bounded(engine, facts, text(goal), &options, out_query);
}

TEST(bfs_finds_shallowest_proof_first) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_query_t *query = NULL;
    re_proof_t *proof = NULL;
    re_string_t name;
    /* Shallow rule first in source: the first deepening cap (max_depth 1)
     * already proves "Target", so BFS returns exactly the 1-step proof and
     * never deepens to the chain. */
    aggregate_install(engine, STRATEGY_SHALLOW_FIRST_RULES);
    ASSERT_EQ(strategy_query(engine, facts, "Target",
                             RE_QUERY_STRATEGY_BREADTH_FIRST, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    ASSERT_EQ(re_query_solution_count(query), 1u);
    ASSERT_EQ(re_query_next(query, &proof), RE_STATUS_OK);
    ASSERT_EQ(re_proof_trace_count(proof), 1u);
    ASSERT_EQ(re_proof_trace_get(proof, 0u, &name), RE_STATUS_OK);
    ASSERT_TRUE(name.size == 6u && memcmp(name.data, "Target", 6u) == 0);
    re_proof_destroy(proof);
    re_query_destroy(query);
    query = NULL;
    re_facts_destroy(facts);
    re_engine_destroy(engine);
    /* Deep chain rule first in source: default DFS dives deep, so with the
     * default single-solution budget the 3-step trace comes first. */
    engine = re_engine_create(NULL, NULL);
    facts = re_facts_create(NULL, NULL);
    aggregate_install(engine, STRATEGY_DEEP_FIRST_RULES);
    ASSERT_EQ(re_engine_query(engine, facts, text("Target"), &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    ASSERT_EQ(re_query_solution_count(query), 1u);
    ASSERT_EQ(re_query_next(query, &proof), RE_STATUS_OK);
    ASSERT_EQ(re_proof_trace_count(proof), 3u);
    ASSERT_EQ(re_proof_trace_get(proof, 0u, &name), RE_STATUS_OK);
    ASSERT_TRUE(name.size == 6u && memcmp(name.data, "Target", 6u) == 0);
    ASSERT_EQ(re_proof_trace_get(proof, 2u, &name), RE_STATUS_OK);
    ASSERT_TRUE(name.size == 4u && memcmp(name.data, "Base", 4u) == 0);
    re_proof_destroy(proof);
    re_query_destroy(query);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(default_strategy_is_dfs_unchanged) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_query_t *query = NULL;
    re_proof_t *proof = NULL;
    re_query_options_t options;
    memset(&options, 0, sizeof(options));
    /* Simulate a caller compiled against the pre-Task-13 struct: struct_size
     * stops before `strategy`, and the out-of-range tail is poisoned to prove
     * the reader never looks past struct_size. */
    options.struct_size = (uint32_t)offsetof(re_query_options_t, strategy);
    options.max_depth = 64u;
    options.max_solutions = 8u;
    options.strategy = 99u;
    options.disable_shared_proof_graph = 1u;
    aggregate_install(engine, STRATEGY_DEEP_FIRST_RULES);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("Target"), &options, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    ASSERT_EQ(re_query_solution_count(query), 2u);
    /* DFS reports both proofs in source order: 3-step chain, then 1-step. */
    ASSERT_EQ(re_query_next(query, &proof), RE_STATUS_OK);
    ASSERT_EQ(re_proof_trace_count(proof), 3u);
    re_proof_destroy(proof);
    ASSERT_EQ(re_query_next(query, &proof), RE_STATUS_OK);
    ASSERT_EQ(re_proof_trace_count(proof), 1u);
    re_proof_destroy(proof);
    re_query_destroy(query);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(invalid_strategy_rejected) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_query_t *query = NULL;
    aggregate_install(engine, STRATEGY_DEEP_FIRST_RULES);
    ASSERT_EQ(strategy_query(engine, facts, "Target", 99u, &query), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_TRUE(query == NULL);
    /* Validation happens before NOT handling, so a negated goal rejects too. */
    ASSERT_EQ(strategy_query(engine, facts, "NOT Target", 99u, &query), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_TRUE(query == NULL);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(iterative_strategy_matches_bfs) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_query_t *bfs = NULL;
    re_query_t *iterative = NULL;
    re_proof_t *proof = NULL;
    aggregate_install(engine, STRATEGY_SHALLOW_FIRST_RULES);
    ASSERT_EQ(strategy_query(engine, facts, "Target",
                             RE_QUERY_STRATEGY_BREADTH_FIRST, &bfs), RE_STATUS_OK);
    ASSERT_EQ(strategy_query(engine, facts, "Target",
                             RE_QUERY_STRATEGY_ITERATIVE, &iterative), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(bfs), re_query_result(iterative));
    ASSERT_EQ(re_query_solution_count(bfs), re_query_solution_count(iterative));
    ASSERT_EQ(re_query_next(bfs, &proof), RE_STATUS_OK);
    ASSERT_EQ(re_proof_trace_count(proof), 1u);
    re_proof_destroy(proof);
    ASSERT_EQ(re_query_next(iterative, &proof), RE_STATUS_OK);
    ASSERT_EQ(re_proof_trace_count(proof), 1u);
    re_proof_destroy(proof);
    re_query_destroy(bfs);
    re_query_destroy(iterative);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(not_query_composes_with_bfs) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_query_t *query = NULL;
    re_proof_t *proof = NULL;
    re_string_t name;
    aggregate_install(engine, STRATEGY_DEEP_FIRST_RULES);
    /* The negated subgoal is a deep chain: BFS probes find it at a deeper
     * cap, and the NOT inversion applies to that strategy-selected result. */
    ASSERT_EQ(strategy_query(engine, facts, "NOT goal(\"Target\")",
                             RE_QUERY_STRATEGY_BREADTH_FIRST, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_DISPROVED);
    ASSERT_EQ(re_query_solution_count(query), 0u);
    re_query_destroy(query);
    query = NULL;
    /* An unprovable subgoal still proves under negation with BFS. */
    ASSERT_EQ(strategy_query(engine, facts, "NOT Missing",
                             RE_QUERY_STRATEGY_BREADTH_FIRST, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    ASSERT_EQ(re_query_solution_count(query), 1u);
    ASSERT_EQ(re_query_next(query, &proof), RE_STATUS_OK);
    ASSERT_EQ(re_proof_trace_count(proof), 1u);
    ASSERT_EQ(re_proof_trace_get(proof, 0u, &name), RE_STATUS_OK);
    ASSERT_TRUE(name.size == 11u && memcmp(name.data, "NOT Missing", 11u) == 0);
    re_proof_destroy(proof);
    re_query_destroy(query);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

/*
 * Shared proof graph (Task 14): the engine owns a 64-entry cache of final
 * backward-query results (PROVED/DISPROVED only - LIMIT and UNKNOWN are never
 * cached), consulted in re_backward_machine_dispatch after option
 * normalization, so cached results equal the final strategy/NOT-resolved
 * results. Entries key on the exact goal text, the facts identity, and the
 * normalized search options, and are stamped with the facts mutation
 * generation and the engine config serial. The generation bump in
 * re_facts_set_impl is unconditional - it covers the first assert of a
 * previously absent fact even though subscribers are not notified for it -
 * so generation stamping alone keeps cached `NOT`-over-absent-fact successes
 * fresh. A full table clears every entry. Hits serve fresh query objects with
 * cloned proofs and their own invalidation subscription.
 */
static void assert_graph_stats(re_engine_t *engine, uint64_t hits, uint64_t misses) {
    uint64_t actual_hits = 999u;
    uint64_t actual_misses = 999u;
    ASSERT_EQ(re_engine_proof_graph_stats(engine, &actual_hits, &actual_misses), RE_STATUS_OK);
    ASSERT_EQ(actual_hits, hits);
    ASSERT_EQ(actual_misses, misses);
}

TEST(shared_graph_second_query_hits_cache) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_query_t *query = NULL;
    re_proof_t *proof = NULL;
    re_query_binding_t binding;
    re_string_t name;
    re_value_t score = {RE_VALUE_INT64, {.int64_value = 42}};
    ASSERT_EQ(re_facts_set(facts, text("Score"), &score), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("Score == S"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    ASSERT_EQ(re_query_next(query, &proof), RE_STATUS_OK);
    ASSERT_EQ(re_proof_binding_count(proof), 1u);
    memset(&binding, 0, sizeof(binding));
    ASSERT_EQ(re_proof_binding_get(proof, 0u, &binding), RE_STATUS_OK);
    ASSERT_TRUE(binding.name.size == 1u && memcmp(binding.name.data, "S", 1u) == 0);
    ASSERT_EQ(binding.value.type, RE_VALUE_INT64);
    ASSERT_EQ(binding.value.as.int64_value, 42);
    re_proof_destroy(proof);
    re_query_destroy(query);
    query = NULL;
    proof = NULL;
    assert_graph_stats(engine, 0u, 1u);
    /* The identical query is served from the graph with the same bindings and
     * trace, and the miss/hit counters move accordingly. */
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("Score == S"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    ASSERT_EQ(re_query_solution_count(query), 1u);
    ASSERT_EQ(re_query_next(query, &proof), RE_STATUS_OK);
    ASSERT_EQ(re_proof_binding_count(proof), 1u);
    memset(&binding, 0, sizeof(binding));
    ASSERT_EQ(re_proof_binding_get(proof, 0u, &binding), RE_STATUS_OK);
    ASSERT_TRUE(binding.name.size == 1u && memcmp(binding.name.data, "S", 1u) == 0);
    ASSERT_EQ(binding.value.as.int64_value, 42);
    ASSERT_EQ(re_proof_trace_count(proof), 1u);
    ASSERT_EQ(re_proof_trace_get(proof, 0u, &name), RE_STATUS_OK);
    ASSERT_TRUE(name.size == 5u && memcmp(name.data, "Score", 5u) == 0);
    re_proof_destroy(proof);
    re_query_destroy(query);
    assert_graph_stats(engine, 1u, 1u);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(mutation_invalidates_cached_proof) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_query_t *query = NULL;
    re_value_t x = {RE_VALUE_INT64, {.int64_value = 1}};
    ASSERT_EQ(re_facts_set(facts, text("X"), &x), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("X == 1"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    re_query_destroy(query);
    query = NULL;
    assert_graph_stats(engine, 0u, 1u);
    /* The mutation moves the generation, so the cached proof is stale: the
     * re-query misses and runs fresh against the new fact value. */
    x.as.int64_value = 2;
    ASSERT_EQ(re_facts_set(facts, text("X"), &x), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("X == 1"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_DISPROVED);
    ASSERT_EQ(re_query_solution_count(query), 0u);
    re_query_destroy(query);
    query = NULL;
    assert_graph_stats(engine, 0u, 2u);
    /* The fresh DISPROVED result is itself cached at the new generation. */
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("X == 1"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_DISPROVED);
    re_query_destroy(query);
    assert_graph_stats(engine, 1u, 2u);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(disable_flag_bypasses_cache) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_query_t *query = NULL;
    re_query_options_t options;
    re_value_t x = {RE_VALUE_INT64, {.int64_value = 1}};
    memset(&options, 0, sizeof(options));
    options.struct_size = (uint32_t)sizeof(options);
    options.max_depth = 64u;
    options.max_solutions = 1u;
    options.disable_shared_proof_graph = 1u;
    ASSERT_EQ(re_facts_set(facts, text("X"), &x), RE_STATUS_OK);
    /* Two disabled runs bypass the cache entirely: no lookup, no store, and
     * the stats do not move. */
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("X == 1"), &options, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    re_query_destroy(query);
    query = NULL;
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("X == 1"), &options, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    re_query_destroy(query);
    query = NULL;
    assert_graph_stats(engine, 0u, 0u);
    /* Nothing was stored, so a shared query runs fresh (miss), after which
     * sharing resumes normally (hit). */
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("X == 1"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    re_query_destroy(query);
    query = NULL;
    assert_graph_stats(engine, 0u, 1u);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("X == 1"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    re_query_destroy(query);
    assert_graph_stats(engine, 1u, 1u);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(different_facts_objects_do_not_share) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts_a = re_facts_create(NULL, NULL);
    re_facts_t *facts_b = re_facts_create(NULL, NULL);
    re_query_t *query = NULL;
    re_value_t x = {RE_VALUE_INT64, {.int64_value = 1}};
    ASSERT_EQ(re_facts_set(facts_a, text("X"), &x), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts_b, text("X"), &x), RE_STATUS_OK);
    /* The facts identity is part of the cache key: the same goal against a
     * second fact set misses even though the result would be identical. */
    ASSERT_EQ(re_engine_query_bounded(engine, facts_a, text("X == 1"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    re_query_destroy(query);
    query = NULL;
    assert_graph_stats(engine, 0u, 1u);
    ASSERT_EQ(re_engine_query_bounded(engine, facts_b, text("X == 1"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    re_query_destroy(query);
    query = NULL;
    assert_graph_stats(engine, 0u, 2u);
    ASSERT_EQ(re_engine_query_bounded(engine, facts_a, text("X == 1"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    re_query_destroy(query);
    assert_graph_stats(engine, 1u, 2u);
    re_facts_destroy(facts_a);
    re_facts_destroy(facts_b);
    re_engine_destroy(engine);
}

TEST(not_absent_fact_cache_stays_fresh) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_query_t *query = NULL;
    re_proof_t *proof = NULL;
    re_string_t name;
    re_value_t banned = {RE_VALUE_BOOL, {.boolean = 1}};
    /* Banned is absent: the negated goal proves and the success is cached.
     * Stats count every consult, including the NOT recursion's subgoal
     * lookup, so one fresh NOT run records two misses (outer goal, subgoal). */
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("NOT Banned == true"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    ASSERT_EQ(re_query_solution_count(query), 1u);
    re_query_destroy(query);
    query = NULL;
    assert_graph_stats(engine, 0u, 2u);
    /* A repeat is served from the graph with the same empty-bindings proof;
     * the outer hit short-circuits before the subgoal is consulted. */
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("NOT Banned == true"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    ASSERT_EQ(re_query_next(query, &proof), RE_STATUS_OK);
    ASSERT_EQ(re_proof_binding_count(proof), 0u);
    ASSERT_EQ(re_proof_trace_get(proof, 0u, &name), RE_STATUS_OK);
    ASSERT_TRUE(name.size == 18u && memcmp(name.data, "NOT Banned == true", 18u) == 0);
    re_proof_destroy(proof);
    re_query_destroy(query);
    query = NULL;
    assert_graph_stats(engine, 1u, 2u);
    /* First assert of the previously absent fact: re_facts_set_impl bumps the
     * mutation generation on inserts too (subscribers are just not notified),
     * so the cached NOT success is stale and the re-query misses - outer
     * consult plus subgoal consult. */
    ASSERT_EQ(re_facts_set(facts, text("Banned"), &banned), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("NOT Banned == true"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_DISPROVED);
    ASSERT_EQ(re_query_solution_count(query), 0u);
    re_query_destroy(query);
    assert_graph_stats(engine, 1u, 4u);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(shared_graph_full_clears_all) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_query_t *query = NULL;
    re_value_t x = {RE_VALUE_INT64, {.int64_value = 1}};
    char goal[32];
    size_t i;
    ASSERT_EQ(re_facts_set(facts, text("X"), &x), RE_STATUS_OK);
    /* One more goal than the table holds: the 65th store finds the table full
     * and clears every entry before inserting, leaving exactly one entry. */
    for (i = 0u; i <= (size_t)RE_PROOF_GRAPH_CAPACITY; ++i) {
        snprintf(goal, sizeof(goal), "X == %u", (unsigned int)i);
        ASSERT_EQ(re_engine_query_bounded(engine, facts, text(goal), NULL, &query), RE_STATUS_OK);
        ASSERT_EQ(re_query_result(query), i == 1u ? RE_QUERY_PROVED : RE_QUERY_DISPROVED);
        re_query_destroy(query);
        query = NULL;
    }
    ASSERT_NOT_NULL(engine->proof_graph);
    ASSERT_EQ(engine->proof_graph->count, 1u);
    assert_graph_stats(engine, 0u, (uint64_t)RE_PROOF_GRAPH_CAPACITY + 1u);
    /* The first goal was evicted by the clear-all; the last one survived. */
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("X == 0"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_DISPROVED);
    re_query_destroy(query);
    query = NULL;
    assert_graph_stats(engine, 0u, (uint64_t)RE_PROOF_GRAPH_CAPACITY + 2u);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("X == 64"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_DISPROVED);
    re_query_destroy(query);
    assert_graph_stats(engine, 1u, (uint64_t)RE_PROOF_GRAPH_CAPACITY + 2u);
    ASSERT_EQ(engine->proof_graph->count, 2u);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(proof_graph_stats_arguments) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    uint64_t hits = 7u;
    uint64_t misses = 7u;
    ASSERT_EQ(re_engine_proof_graph_stats(NULL, &hits, &misses), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_engine_proof_graph_stats(engine, NULL, &misses), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_engine_proof_graph_stats(engine, &hits, NULL), RE_STATUS_INVALID_ARGUMENT);
    /* The graph is lazy: no cacheable query yet reports zeroes, not an error. */
    ASSERT_EQ(re_engine_proof_graph_stats(engine, &hits, &misses), RE_STATUS_OK);
    ASSERT_EQ(hits, 0u);
    ASSERT_EQ(misses, 0u);
    re_engine_destroy(engine);
}

TEST(retract_invalidates_cached_proof) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_query_t *query = NULL;
    re_fact_id_t id;
    re_value_t x = {RE_VALUE_INT64, {.int64_value = 1}};
    ASSERT_EQ(re_facts_insert(facts, text("X"), &x, &id), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("X == 1"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    re_query_destroy(query);
    query = NULL;
    assert_graph_stats(engine, 0u, 1u);
    /* Retraction bumps the mutation serial (facts.c), so the cached PROVED
     * entry is stale: the re-query misses and runs fresh against the now
     * absent fact, reporting UNKNOWN instead of serving the stale proof. */
    ASSERT_EQ(re_facts_retract(facts, id), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("X == 1"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_UNKNOWN);
    ASSERT_EQ(re_query_solution_count(query), 0u);
    re_query_destroy(query);
    assert_graph_stats(engine, 0u, 2u);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(tms_cascade_invalidates_cached_proof) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_query_t *query = NULL;
    re_fact_id_t premise;
    re_fact_id_t derived;
    re_value_t out;
    re_value_t one = {RE_VALUE_INT64, {.int64_value = 1}};
    re_value_t two = {RE_VALUE_INT64, {.int64_value = 2}};
    ASSERT_EQ(re_facts_insert(facts, text("P"), &one, &premise), RE_STATUS_OK);
    ASSERT_EQ(re_facts_insert_logical(facts, text("D"), &two, text("R"), &premise, 1u, &derived), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("D == 2"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    re_query_destroy(query);
    query = NULL;
    assert_graph_stats(engine, 0u, 1u);
    /* Retracting the premise cascades through re_facts_retract (tms.c), and
     * each retract bumps the serial: the cached derived-fact proof is stale. */
    ASSERT_EQ(re_facts_retract(facts, premise), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("D"), &out), RE_STATUS_NOT_FOUND);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("D == 2"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_UNKNOWN);
    ASSERT_EQ(re_query_solution_count(query), 0u);
    re_query_destroy(query);
    assert_graph_stats(engine, 0u, 2u);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(retract_only_transaction_invalidates_cache) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_query_t *query = NULL;
    re_fact_txn_t *txn = NULL;
    re_fact_id_t id;
    re_value_t x = {RE_VALUE_INT64, {.int64_value = 1}};
    ASSERT_EQ(re_facts_insert(facts, text("X"), &x, &id), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("X == 1"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    re_query_destroy(query);
    query = NULL;
    assert_graph_stats(engine, 0u, 1u);
    /* The staged retract bumps the staged serial through the re_facts_retract
     * recursion, and the commit propagates it to the parent (transactions.c),
     * so the cached entry is stale after a retract-only commit. */
    ASSERT_EQ(re_facts_begin(facts, &txn), RE_STATUS_OK);
    ASSERT_EQ(re_facts_txn_retract(txn, id), RE_STATUS_OK);
    ASSERT_EQ(re_facts_commit(txn), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("X == 1"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_UNKNOWN);
    ASSERT_EQ(re_query_solution_count(query), 0u);
    re_query_destroy(query);
    assert_graph_stats(engine, 0u, 2u);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST_MAIN_BEGIN()
    RUN_TEST(query_not_succeeds_when_subgoal_unprovable);
    RUN_TEST(query_not_fails_when_subgoal_provable);
    RUN_TEST(query_not_succeeds_when_subgoal_disproved);
    RUN_TEST(query_not_with_rule_goal);
    RUN_TEST(query_not_nested_double_prefix);
    RUN_TEST(query_not_reports_limit_when_subgoal_is_limited);
    RUN_TEST(query_not_rejects_empty_remainder);
    RUN_TEST(query_not_prefix_is_case_sensitive);
    RUN_TEST(query_not_invalidated_by_fact_mutation);
    RUN_TEST(aggregate_count_counts_solutions);
    RUN_TEST(aggregate_sum_and_average);
    RUN_TEST(aggregate_min_max_first_last);
    RUN_TEST(aggregate_empty_set_semantics);
    RUN_TEST(aggregate_non_numeric_rejected);
    RUN_TEST(aggregate_first_last_string_not_supported);
    RUN_TEST(aggregate_sum_promotes_to_double);
    RUN_TEST(aggregate_rejects_invalid_arguments);
    RUN_TEST(bfs_finds_shallowest_proof_first);
    RUN_TEST(default_strategy_is_dfs_unchanged);
    RUN_TEST(invalid_strategy_rejected);
    RUN_TEST(iterative_strategy_matches_bfs);
    RUN_TEST(not_query_composes_with_bfs);
    RUN_TEST(shared_graph_second_query_hits_cache);
    RUN_TEST(mutation_invalidates_cached_proof);
    RUN_TEST(disable_flag_bypasses_cache);
    RUN_TEST(different_facts_objects_do_not_share);
    RUN_TEST(not_absent_fact_cache_stays_fresh);
    RUN_TEST(shared_graph_full_clears_all);
    RUN_TEST(proof_graph_stats_arguments);
    RUN_TEST(retract_invalidates_cached_proof);
    RUN_TEST(tms_cascade_invalidates_cached_proof);
    RUN_TEST(retract_only_transaction_invalidates_cache);
TEST_MAIN_END()
