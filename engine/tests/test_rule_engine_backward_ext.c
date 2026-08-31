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

TEST(member_write_bumps_mutation_serial) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_query_t *query = NULL;
    re_program_t *program = NULL;
    re_value_handle_t *car = NULL;
    re_value_t speed = {RE_VALUE_INT64, {.int64_value = 80}};
    re_value_t ninety = {RE_VALUE_INT64, {.int64_value = 90}};
    re_value_t x = {RE_VALUE_INT64, {.int64_value = 1}};
    uint64_t serial;
    re_proof_graph_stats_t stats;
    ASSERT_EQ(re_value_create_object(facts, &car), RE_STATUS_OK);
    ASSERT_EQ(re_value_object_set(car, text("speed"), &speed), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set_value(facts, text("Car"), car), RE_STATUS_OK);
    re_value_destroy(car);
    ASSERT_EQ(re_facts_set(facts, text("X"), &x), RE_STATUS_OK);
    /* Cache a proof over flat fact X... */
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("X == 1"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    re_query_destroy(query);
    query = NULL;
    assert_graph_stats(engine, 0u, 1u);
    /* ...then a host member write on the unrelated Car fact still bumps the
     * serial (values.c), but since Task B2 the serial bump is only the fast
     * path: the cached entry's premises (X alone) are re-validated and the
     * entry SURVIVES, so the re-query hits. */
    serial = facts->mutation_serial;
    ASSERT_EQ(re_facts_set_path(facts, text("Car.speed"), &ninety), RE_STATUS_OK);
    ASSERT_TRUE(facts->mutation_serial > serial);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("X == 1"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    re_query_destroy(query);
    query = NULL;
    assert_graph_stats(engine, 1u, 1u);
    /* Installing a program bumps the config serial, so the next query misses
     * on the key (not on invalidation) and caches a fresh entry. */
    ASSERT_EQ(re_program_load(NULL,
        text("rule \"up\" { when Car.speed == 90 then Car.speed = 80; }"),
        NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("X == 1"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    re_query_destroy(query);
    query = NULL;
    assert_graph_stats(engine, 1u, 2u);
    /* A rule-fired member write goes through the firing transaction: the
     * staged serial bump propagates on commit, but X's value is untouched, so
     * the premise fingerprint still matches and the entry survives again. */
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    {
        /* Prove the rule actually fired through its transaction. */
        re_value_t after;
        ASSERT_EQ(re_facts_get_path(facts, text("Car.speed"), &after), RE_STATUS_OK);
        ASSERT_EQ(after.as.int64_value, 80);
    }
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("X == 1"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    re_query_destroy(query);
    assert_graph_stats(engine, 2u, 2u);
    memset(&stats, 0, sizeof(stats));
    stats.struct_size = (uint32_t)sizeof(stats);
    ASSERT_EQ(re_engine_proof_graph_stats_v2(engine, &stats), RE_STATUS_OK);
    ASSERT_EQ(stats.invalidations, 0u);
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

/*
 * Facts-identity nonce (final hardening): the proof graph key is the facts
 * pointer plus a per-object nonce assigned in re_facts_create, so destroying
 * a facts object and allocating the next one at the same address (reaching
 * the same mutation serial) can no longer alias a stale cache entry. The
 * reuse allocator below makes the address alignment deterministic: free
 * pushes blocks onto a LIFO stack and alloc pops an exact-size match, so the
 * re-created facts object always lands on the destroyed one's address. Sizes
 * ride in a per-allocation header so realloc can copy without the old size.
 */
typedef struct reuse_block_t {
    void *memory;
    size_t size;
} reuse_block_t;

typedef struct reuse_allocator_t {
    reuse_block_t blocks[32];
    size_t count;
} reuse_allocator_t;

static void *reuse_alloc(void *context, size_t size) {
    reuse_allocator_t *state = (reuse_allocator_t *)context;
    unsigned char *raw;
    if (state->count != 0u && state->blocks[state->count - 1u].size == size)
        return state->blocks[--state->count].memory;
    if (size > (size_t)-1 - sizeof(size_t)) return NULL;
    raw = (unsigned char *)malloc(size + sizeof(size_t));
    if (raw == NULL) return NULL;
    memcpy(raw, &size, sizeof(size_t));
    return raw + sizeof(size_t);
}

static void reuse_free(void *context, void *memory) {
    reuse_allocator_t *state = (reuse_allocator_t *)context;
    size_t size;
    if (memory == NULL) return;
    memcpy(&size, (const unsigned char *)memory - sizeof(size_t), sizeof(size_t));
    if (state->count < 32u) {
        state->blocks[state->count].memory = memory;
        state->blocks[state->count].size = size;
        ++state->count;
        return;
    }
    free((unsigned char *)memory - sizeof(size_t));
}

static void *reuse_realloc(void *context, void *memory, size_t size) {
    size_t old_size;
    void *grown;
    if (memory == NULL) return reuse_alloc(context, size);
    memcpy(&old_size, (const unsigned char *)memory - sizeof(size_t), sizeof(size_t));
    grown = reuse_alloc(context, size);
    if (grown == NULL) return NULL;
    memcpy(grown, memory, old_size < size ? old_size : size);
    reuse_free(context, memory);
    return grown;
}

/* Really free every block still parked on the reuse stack. */
static void reuse_drain(reuse_allocator_t *state) {
    while (state->count != 0u) {
        --state->count;
        free((unsigned char *)state->blocks[state->count].memory - sizeof(size_t));
    }
}

TEST(facts_nonce_blocks_aba_stale_hit) {
    reuse_allocator_t reuse;
    re_allocator_t allocator;
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts_a;
    re_facts_t *facts_b;
    re_query_t *query = NULL;
    re_value_t one = {RE_VALUE_INT64, {.int64_value = 1}};
    re_value_t two = {RE_VALUE_INT64, {.int64_value = 2}};
    uint64_t nonce_a;
    memset(&reuse, 0, sizeof(reuse));
    allocator.context = &reuse;
    allocator.alloc = reuse_alloc;
    allocator.realloc = reuse_realloc;
    allocator.free = reuse_free;
    ASSERT_NOT_NULL(engine);
    facts_a = re_facts_create(&allocator, NULL);
    ASSERT_NOT_NULL(facts_a);
    nonce_a = facts_a->nonce;
    /* Cache a PROVED result for "X == 1" against facts A (serial 1). */
    ASSERT_EQ(re_facts_set(facts_a, text("X"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts_a, text("X == 1"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    re_query_destroy(query);
    query = NULL;
    assert_graph_stats(engine, 0u, 1u);
    /* Destroy A and re-create through the reuse allocator: B lands on A's
     * address, and one identically shaped set gives it the same mutation
     * serial - the exact ABA alignment the pointer+serial key could not
     * tell apart. */
    re_facts_destroy(facts_a);
    facts_b = re_facts_create(&allocator, NULL);
    ASSERT_NOT_NULL(facts_b);
    ASSERT_TRUE((void *)facts_b == (void *)facts_a);
    ASSERT_TRUE(facts_b->nonce != nonce_a);
    /* B carries X == 2: a stale hit would serve A's PROVED; the fresh run
     * must miss and report DISPROVED. */
    ASSERT_EQ(re_facts_set(facts_b, text("X"), &two), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts_b, text("X == 1"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_DISPROVED);
    re_query_destroy(query);
    query = NULL;
    assert_graph_stats(engine, 0u, 2u);
    /* The fresh DISPROVED is cached under B's own identity and then hits. */
    ASSERT_EQ(re_engine_query_bounded(engine, facts_b, text("X == 1"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_DISPROVED);
    re_query_destroy(query);
    assert_graph_stats(engine, 1u, 2u);
    re_facts_destroy(facts_b);
    reuse_drain(&reuse);
    re_engine_destroy(engine);
}

/*
 * Deepening-probe boundary (final hardening): the BFS/ITERATIVE wrapper
 * re-proves with max_depth = 1, 2, 4, ... doubling up to the configured
 * max_depth. The documented 32-doubling budget is unreachable in practice -
 * reaching it needs max_depth > 2^32, and each probe allocates max_depth + 1
 * call frames - so the reachable bound is the configured max_depth itself:
 * the probe loop returns the last probe's LIMIT once the cap reaches it, and
 * a probe that completes without hitting its cap (0 proofs, no depth
 * exhaustion) terminates the loop immediately with that authoritative result.
 */
TEST(bfs_deepening_limits_at_configured_max_depth) {
    /* 5-rule chain: proving "C5" needs depth 5 (C5 at depth 0 down to C1 at
     * depth 4), so max_depth = 3 exhausts every probe and max_depth = 8
     * proves at the cap = 8 probe. */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_query_t *query = NULL;
    re_query_options_t options;
    re_value_t x = {RE_VALUE_INT64, {.int64_value = 2}};
    aggregate_install(engine,
        "rule \"C1\" { when true then B1 = 1; }"
        "rule \"C2\" { when goal(\"C1\") then B2 = 1; }"
        "rule \"C3\" { when goal(\"C2\") then B3 = 1; }"
        "rule \"C4\" { when goal(\"C3\") then B4 = 1; }"
        "rule \"C5\" { when goal(\"C4\") then B5 = 1; }");
    memset(&options, 0, sizeof(options));
    options.struct_size = (uint32_t)sizeof(options);
    options.max_solutions = 4u;
    options.strategy = RE_QUERY_STRATEGY_BREADTH_FIRST;
    /* Every probe (caps 1, 2, 3) hits its depth cap without a proof: the last
     * probe's LIMIT is returned unchanged, exactly like a plain DFS run. */
    options.max_depth = 3u;
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("C5"), &options, &query), RE_STATUS_LIMIT);
    ASSERT_EQ(re_query_result(query), RE_QUERY_LIMIT);
    ASSERT_EQ(re_query_solution_count(query), 0u);
    re_query_destroy(query);
    query = NULL;
    /* Caps 1, 2, 4 still exhaust; the cap = 8 probe reaches depth 5. */
    options.max_depth = 8u;
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("C5"), &options, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    ASSERT_EQ(re_query_solution_count(query), 1u);
    re_query_destroy(query);
    query = NULL;
    /* A goal with no derivation completes the first probe without touching
     * its depth cap: 0 proofs with RE_STATUS_OK is authoritative for every
     * deeper cap, so the loop returns it immediately (no LIMIT). */
    options.max_depth = 3u;
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("Missing"), &options, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_UNKNOWN);
    re_query_destroy(query);
    query = NULL;
    /* Same early exit through the direct fact-comparison slice: DISPROVED at
     * the first probe, never LIMIT. */
    ASSERT_EQ(re_facts_set(facts, text("X"), &x), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("X == 1"), &options, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_DISPROVED);
    re_query_destroy(query);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

/*
 * Aggregate solution cap (final hardening): re_engine_query_aggregate runs
 * its internal query with max_solutions = 1024 (RE_AGGREGATE_MAX_SOLUTIONS),
 * and reaching the cap reports RE_STATUS_LIMIT because an exact fit cannot be
 * told apart from a truncated set. The goal rules multiply solutions by
 * cross-product: an AND of two parenthesized OR chains of parameterized goal
 * calls yields left*right solution branches (condition_collect_branches),
 * so 31 x 33 / 32 x 32 / 32 x 33 alternatives need only 5 rules and shallow
 * (~35-deep) expression trees - a flat 1025-alternative OR chain is deep
 * enough to overflow the ASan-inflated stack in the recursive branch
 * collector.
 */
static char aggregate_cap_source[8192];

static void append_goal_alternatives(size_t *used, const char *rule, size_t count) {
    size_t i;
    for (i = 0u; i < count; ++i) {
        int written = snprintf(aggregate_cap_source + *used,
                               sizeof(aggregate_cap_source) - *used,
                               i + 1u < count ? "goal(\"%s\", %d) or " : "goal(\"%s\", %d)",
                               rule, (int)(i + 1u));
        ASSERT_TRUE(written > 0 && (size_t)written < sizeof(aggregate_cap_source) - *used);
        *used += (size_t)written;
    }
}

static void append_wrapped_or(size_t *used, const char *rule, size_t count) {
    int written = snprintf(aggregate_cap_source + *used,
                           sizeof(aggregate_cap_source) - *used, "(");
    ASSERT_TRUE(written > 0 && (size_t)written < sizeof(aggregate_cap_source) - *used);
    *used += (size_t)written;
    append_goal_alternatives(used, rule, count);
    written = snprintf(aggregate_cap_source + *used,
                       sizeof(aggregate_cap_source) - *used, ")");
    ASSERT_TRUE(written > 0 && (size_t)written < sizeof(aggregate_cap_source) - *used);
    *used += (size_t)written;
}

static void build_aggregate_cap_source(void) {
    size_t used = 0u;
    int written = snprintf(aggregate_cap_source, sizeof(aggregate_cap_source),
        "rule \"Left\"(X) { when X > 0 then L = 1; }"
        "rule \"Right\"(Y) { when Y > 0 then R = 1; }"
        "rule \"Wide\" { when ");
    ASSERT_TRUE(written > 0);
    used += (size_t)written;
    append_wrapped_or(&used, "Left", 32u);
    written = snprintf(aggregate_cap_source + used, sizeof(aggregate_cap_source) - used,
                       " and ");
    ASSERT_TRUE(written > 0 && (size_t)written < sizeof(aggregate_cap_source) - used);
    used += (size_t)written;
    append_wrapped_or(&used, "Right", 33u);
    written = snprintf(aggregate_cap_source + used, sizeof(aggregate_cap_source) - used,
                       " then Done = 1; }"
                       "rule \"Exact\" { when ");
    ASSERT_TRUE(written > 0 && (size_t)written < sizeof(aggregate_cap_source) - used);
    used += (size_t)written;
    append_wrapped_or(&used, "Left", 32u);
    written = snprintf(aggregate_cap_source + used, sizeof(aggregate_cap_source) - used,
                       " and ");
    ASSERT_TRUE(written > 0 && (size_t)written < sizeof(aggregate_cap_source) - used);
    used += (size_t)written;
    append_wrapped_or(&used, "Right", 32u);
    written = snprintf(aggregate_cap_source + used, sizeof(aggregate_cap_source) - used,
                       " then Done = 1; }"
                       "rule \"Under\" { when ");
    ASSERT_TRUE(written > 0 && (size_t)written < sizeof(aggregate_cap_source) - used);
    used += (size_t)written;
    append_wrapped_or(&used, "Left", 31u);
    written = snprintf(aggregate_cap_source + used, sizeof(aggregate_cap_source) - used,
                       " and ");
    ASSERT_TRUE(written > 0 && (size_t)written < sizeof(aggregate_cap_source) - used);
    used += (size_t)written;
    append_wrapped_or(&used, "Right", 33u);
    written = snprintf(aggregate_cap_source + used, sizeof(aggregate_cap_source) - used,
                       " then Done = 1; }");
    ASSERT_TRUE(written > 0 && (size_t)written < sizeof(aggregate_cap_source) - used);
}

TEST(aggregate_reports_limit_at_solution_cap) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t out;
    re_string_t no_field = {NULL, 0u};
    build_aggregate_cap_source();
    aggregate_install(engine, aggregate_cap_source);
    /* 32 x 33 = 1056 alternatives: the internal query stops at the
     * 1024-solution cap and the fold reports RE_STATUS_LIMIT rather than a
     * partial count. */
    ASSERT_EQ(re_engine_query_aggregate(engine, facts, RE_ACCUM_COUNT, no_field,
                                        text("Wide"), &out), RE_STATUS_LIMIT);
    /* 32 x 32 = 1024 solutions is the same LIMIT: an exact fit cannot be told
     * apart from truncation at the cap. */
    ASSERT_EQ(re_engine_query_aggregate(engine, facts, RE_ACCUM_COUNT, no_field,
                                        text("Exact"), &out), RE_STATUS_LIMIT);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(aggregate_below_solution_cap_succeeds) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t out;
    re_string_t no_field = {NULL, 0u};
    build_aggregate_cap_source();
    aggregate_install(engine, aggregate_cap_source);
    /* 31 x 33 = 1023 solutions, one below the cap, folds normally: the LIMIT
     * boundary is exactly 1024, not "approaching" it. */
    ASSERT_EQ(re_engine_query_aggregate(engine, facts, RE_ACCUM_COUNT, no_field,
                                        text("Under"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.type, RE_VALUE_INT64);
    ASSERT_EQ(out.as.int64_value, 1023);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

/* I1 (Task A2 review): a rule whose condition uses the parenthesized
 * quantifier form must not be provable through backward chaining — the
 * compatibility evaluator previously fell into the legacy operand comparison
 * with zeroed operands, and RE_COMPARE_TRUE over them answers true
 * unconditionally, so the query silently PROVED. Now every
 * condition-evaluation entry rejects the nested node honestly. */
TEST(query_rule_with_forall_paren_condition_fails_not_supported) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_query_t *query = NULL;
    re_value_handle_t *alert = NULL;
    re_value_t level = {RE_VALUE_STRING, {.string = {"low", 3u}}};
    /* A low Alert exists, so forall(Alert.level == "high") is false; even a
     * vacuous-true case (no Alert facts at all) must not prove Goal. */
    ASSERT_EQ(re_value_create_object(facts, &alert), RE_STATUS_OK);
    ASSERT_EQ(re_value_object_set(alert, text("level"), &level), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set_value(facts, text("Alert1"), alert), RE_STATUS_OK);
    re_value_destroy(alert);
    ASSERT_EQ(re_program_load(NULL, text(
        "rule \"Derive\" { when forall(Alert.level == \"high\") then Goal = 1; }"),
        NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("goal(\"Derive\")"), NULL, &query),
              RE_STATUS_NOT_SUPPORTED);
    ASSERT_TRUE(query == NULL);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(query_rule_with_exists_paren_condition_fails_not_supported) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_query_t *query = NULL;
    re_value_handle_t *alert = NULL;
    re_value_t level = {RE_VALUE_STRING, {.string = {"high", 4u}}};
    /* The quantifier is satisfiable here; the point is that backward chaining
     * must still refuse rather than prove it through the legacy path. */
    ASSERT_EQ(re_value_create_object(facts, &alert), RE_STATUS_OK);
    ASSERT_EQ(re_value_object_set(alert, text("level"), &level), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set_value(facts, text("Alert1"), alert), RE_STATUS_OK);
    re_value_destroy(alert);
    ASSERT_EQ(re_program_load(NULL, text(
        "rule \"Derive\" { when exists(Alert.level == \"high\") then Goal = 1; }"),
        NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("goal(\"Derive\")"), NULL, &query),
              RE_STATUS_NOT_SUPPORTED);
    ASSERT_TRUE(query == NULL);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

/*
 * Task B2 per-premise invalidation (upstream proof_graph.rs mapped onto the
 * local result-cache shape): cached entries record the fact reads (premises)
 * their derivation observed, and a facts mutation invalidates an entry only
 * when one of its premises actually flipped (presence or value fingerprint).
 * The upstream proof-graph integration cases map locally as: basic
 * store/lookup -> shared_graph_second_query_hits_cache (Task 14); the
 * invalidation chain and dependent propagation ->
 * proof_graph_invalidation_chain_retracts_dependents; multiple justifications
 * -> proof_graph_multiple_justifications_survive; hit/miss stats ->
 * proof_graph_stats_v2_reports_full_counters; FactKey parsing ->
 * proof_graph_goal_text_is_the_cache_key; clear-all eviction accounting ->
 * proof_graph_evictions_counted_on_clear_all; plus the headline behavioral
 * upgrade, proof_graph_unrelated_mutation_preserves_entry.
 */
TEST(proof_graph_unrelated_mutation_preserves_entry) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_query_t *query = NULL;
    re_value_t a = {RE_VALUE_INT64, {.int64_value = 1}};
    re_value_t b = {RE_VALUE_INT64, {.int64_value = 1}};
    re_proof_graph_stats_t stats;
    ASSERT_EQ(re_facts_set(facts, text("A"), &a), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("B"), &b), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("A == 1"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    re_query_destroy(query);
    query = NULL;
    assert_graph_stats(engine, 0u, 1u);
    /* The derivation read only A, so mutating the unrelated fact B leaves the
     * cached entry valid and the re-query HITS - pre-B2 coarse invalidation
     * dropped the entry here. */
    b.as.int64_value = 2;
    ASSERT_EQ(re_facts_set(facts, text("B"), &b), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("A == 1"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    re_query_destroy(query);
    query = NULL;
    assert_graph_stats(engine, 1u, 1u);
    memset(&stats, 0, sizeof(stats));
    stats.struct_size = (uint32_t)sizeof(stats);
    ASSERT_EQ(re_engine_proof_graph_stats_v2(engine, &stats), RE_STATUS_OK);
    ASSERT_EQ(stats.invalidations, 0u);
    ASSERT_EQ(stats.stores, 1u);
    /* Mutating the premise fact itself invalidates the entry: the re-query
     * misses and runs fresh against the new value. */
    a.as.int64_value = 2;
    ASSERT_EQ(re_facts_set(facts, text("A"), &a), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("A == 1"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_DISPROVED);
    re_query_destroy(query);
    query = NULL;
    assert_graph_stats(engine, 1u, 2u);
    ASSERT_EQ(re_engine_proof_graph_stats_v2(engine, &stats), RE_STATUS_OK);
    ASSERT_EQ(stats.invalidations, 1u);
    ASSERT_EQ(stats.stores, 2u);
    /* The fresh DISPROVED entry is itself cached and survives a later
     * unrelated mutation. */
    b.as.int64_value = 3;
    ASSERT_EQ(re_facts_set(facts, text("B"), &b), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("A == 1"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_DISPROVED);
    re_query_destroy(query);
    assert_graph_stats(engine, 2u, 2u);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(proof_graph_invalidation_chain_retracts_dependents) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_query_t *query = NULL;
    re_fact_id_t id_a;
    re_fact_id_t id_b;
    re_fact_id_t id_c;
    re_value_t out;
    re_value_t one = {RE_VALUE_INT64, {.int64_value = 1}};
    /* A -> B -> C: each logical insertion lists the previous fact as its
     * premise (what rule derivation does through re_facts_insert_logical), so
     * retracting A cascades through B into C. */
    ASSERT_EQ(re_facts_insert(facts, text("A"), &one, &id_a), RE_STATUS_OK);
    ASSERT_EQ(re_facts_insert_logical(facts, text("B"), &one, text("R1"), &id_a, 1u, &id_b),
              RE_STATUS_OK);
    ASSERT_EQ(re_facts_insert_logical(facts, text("C"), &one, text("R2"), &id_b, 1u, &id_c),
              RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("C == 1"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    re_query_destroy(query);
    query = NULL;
    assert_graph_stats(engine, 0u, 1u);
    /* The cached entry's premise set names C. The cascade removes C without
     * any direct mutation of it - dependent propagation through the TMS - and
     * the entry invalidates transitively: miss plus fresh UNKNOWN. */
    ASSERT_EQ(re_facts_retract(facts, id_a), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("B"), &out), RE_STATUS_NOT_FOUND);
    ASSERT_EQ(re_facts_get(facts, text("C"), &out), RE_STATUS_NOT_FOUND);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("C == 1"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_UNKNOWN);
    re_query_destroy(query);
    assert_graph_stats(engine, 0u, 2u);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(proof_graph_multiple_justifications_survive) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_query_t *query = NULL;
    re_value_t one = {RE_VALUE_INT64, {.int64_value = 1}};
    re_value_t two = {RE_VALUE_INT64, {.int64_value = 2}};
    /* Two rules named G: the goal has two independent derivations
     * (justifications), one reading X and one reading Y. */
    ASSERT_EQ(re_program_load(NULL, text(
        "rule \"G\" { when X == 1 then GA = 1; }"
        "rule \"G\" { when Y == 1 then GB = 1; }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("X"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("Y"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("G"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    ASSERT_EQ(re_query_solution_count(query), 1u);
    re_query_destroy(query);
    query = NULL;
    assert_graph_stats(engine, 0u, 1u);
    /* max_solutions=1 stopped at the first justification (reading X), so a
     * mutation of the ALTERNATIVE justification's premise leaves the cached
     * node valid - the local form of a node surviving on its remaining
     * justification. */
    ASSERT_EQ(re_facts_set(facts, text("Y"), &two), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("G"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    re_query_destroy(query);
    query = NULL;
    assert_graph_stats(engine, 1u, 1u);
    /* The stored node record names the proving rule (the trace root). */
    ASSERT_NOT_NULL(engine->proof_graph);
    ASSERT_EQ(engine->proof_graph->count, 1u);
    ASSERT_EQ(engine->proof_graph->entries[0].node_count, 1u);
    ASSERT_EQ(engine->proof_graph->entries[0].nodes[0].rule_name_size, 1u);
    ASSERT_TRUE(memcmp(engine->proof_graph->entries[0].nodes[0].rule_name, "G", 1u) == 0);
    ASSERT_EQ(engine->proof_graph->entries[0].nodes[0].valid, 1);
    /* Invalidate the used justification: the entry is unlinked, the re-query
     * misses, and the fresh run proves the goal through the remaining
     * justification (Y restored, X flipped) - re-derivation keeps the node. */
    ASSERT_EQ(re_facts_set(facts, text("Y"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("X"), &two), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("G"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    ASSERT_EQ(re_query_solution_count(query), 1u);
    re_query_destroy(query);
    query = NULL;
    assert_graph_stats(engine, 1u, 2u);
    /* The re-derived entry is cached and serves the next query. */
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("G"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    re_query_destroy(query);
    assert_graph_stats(engine, 2u, 2u);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(proof_graph_stats_v2_reports_full_counters) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_query_t *query = NULL;
    re_value_t x = {RE_VALUE_INT64, {.int64_value = 1}};
    re_proof_graph_stats_t stats;
    memset(&stats, 0, sizeof(stats));
    ASSERT_EQ(re_engine_proof_graph_stats_v2(NULL, &stats), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_engine_proof_graph_stats_v2(engine, NULL), RE_STATUS_INVALID_ARGUMENT);
    stats.struct_size = (uint32_t)sizeof(stats) - 1u;
    ASSERT_EQ(re_engine_proof_graph_stats_v2(engine, &stats), RE_STATUS_INVALID_ARGUMENT);
    /* The graph is lazy: an engine that never cached reports zeroes. */
    stats.struct_size = (uint32_t)sizeof(stats);
    ASSERT_EQ(re_engine_proof_graph_stats_v2(engine, &stats), RE_STATUS_OK);
    ASSERT_EQ(stats.hits, 0u);
    ASSERT_EQ(stats.misses, 0u);
    ASSERT_EQ(stats.invalidations, 0u);
    ASSERT_EQ(stats.stores, 0u);
    ASSERT_EQ(stats.evictions, 0u);
    ASSERT_EQ(re_facts_set(facts, text("X"), &x), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("X == 1"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    re_query_destroy(query);
    query = NULL;
    ASSERT_EQ(re_engine_proof_graph_stats_v2(engine, &stats), RE_STATUS_OK);
    ASSERT_EQ(stats.misses, 1u);
    ASSERT_EQ(stats.stores, 1u);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("X == 1"), NULL, &query), RE_STATUS_OK);
    re_query_destroy(query);
    query = NULL;
    ASSERT_EQ(re_engine_proof_graph_stats_v2(engine, &stats), RE_STATUS_OK);
    ASSERT_EQ(stats.hits, 1u);
    ASSERT_EQ(stats.misses, 1u);
    /* A premise flip counts one invalidation; the fresh result stores again. */
    x.as.int64_value = 2;
    ASSERT_EQ(re_facts_set(facts, text("X"), &x), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("X == 1"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_DISPROVED);
    re_query_destroy(query);
    query = NULL;
    ASSERT_EQ(re_engine_proof_graph_stats_v2(engine, &stats), RE_STATUS_OK);
    ASSERT_EQ(stats.hits, 1u);
    ASSERT_EQ(stats.misses, 2u);
    ASSERT_EQ(stats.invalidations, 1u);
    ASSERT_EQ(stats.stores, 2u);
    ASSERT_EQ(stats.evictions, 0u);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(proof_graph_evictions_counted_on_clear_all) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_query_t *query = NULL;
    re_value_t x = {RE_VALUE_INT64, {.int64_value = 1}};
    re_proof_graph_stats_t stats;
    char goal[32];
    size_t i;
    ASSERT_EQ(re_facts_set(facts, text("X"), &x), RE_STATUS_OK);
    /* One more goal than the table holds: the 65th store flushes the table,
     * counting every dropped entry as an eviction. */
    for (i = 0u; i <= (size_t)RE_PROOF_GRAPH_CAPACITY; ++i) {
        snprintf(goal, sizeof(goal), "X == %u", (unsigned int)i);
        ASSERT_EQ(re_engine_query_bounded(engine, facts, text(goal), NULL, &query), RE_STATUS_OK);
        re_query_destroy(query);
        query = NULL;
    }
    ASSERT_NOT_NULL(engine->proof_graph);
    ASSERT_EQ(engine->proof_graph->count, 1u);
    memset(&stats, 0, sizeof(stats));
    stats.struct_size = (uint32_t)sizeof(stats);
    ASSERT_EQ(re_engine_proof_graph_stats_v2(engine, &stats), RE_STATUS_OK);
    ASSERT_EQ(stats.stores, (uint64_t)RE_PROOF_GRAPH_CAPACITY + 1u);
    ASSERT_EQ(stats.evictions, (uint64_t)RE_PROOF_GRAPH_CAPACITY);
    ASSERT_EQ(stats.invalidations, 0u);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(proof_graph_goal_text_is_the_cache_key) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_query_t *query = NULL;
    re_value_t x = {RE_VALUE_INT64, {.int64_value = 1}};
    ASSERT_EQ(re_facts_set(facts, text("X"), &x), RE_STATUS_OK);
    /* Upstream parses a FactKey{type, field, pattern} out of the goal text;
     * the local cache key is the exact normalized goal text - strictly finer,
     * so textual variants of the same condition are independent entries that
     * never alias. Both variants prove, each through its own key. */
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("X == 1"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    re_query_destroy(query);
    query = NULL;
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("X==1"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    re_query_destroy(query);
    query = NULL;
    assert_graph_stats(engine, 0u, 2u);
    ASSERT_EQ(engine->proof_graph->count, 2u);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("X == 1"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    re_query_destroy(query);
    query = NULL;
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("X==1"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    re_query_destroy(query);
    query = NULL;
    assert_graph_stats(engine, 2u, 2u);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

/*
 * B3 `?var` unification in backward query goal strings (upstream
 * unification.rs case table, bounded). A `?name` token in a query goal is a
 * per-query-run variable whose bindings surface through re_proof_binding_get
 * under its verbatim `?`-prefixed name (upstream keeps the prefix:
 * Expression::Variable(format!("?{}", name))).
 *
 * - `Fact == ?s` (or `?s == Fact`) binds `?s` to the fact value per solution;
 *   an absent fact is unresolvable and reports UNKNOWN exactly like the
 *   literal-comparison path.
 * - `?x == ?y` with both sides unbound has no match (upstream binds nothing
 *   it cannot resolve and never defers); the goal reads no facts, so the
 *   failure is definitive: RE_QUERY_DISPROVED.
 * - `goal("Rule", actual, ?var, ...)` query strings flow through the
 *   formals/actuals machinery: an unbound `?var` actual leaves the formal an
 *   unbound placeholder and rides as an alias, so the formal's eventual
 *   concrete bind claims the `?var` too. Binding is sticky-consistent: the
 *   same `?var` rebound to a different value fails that proof branch, never
 *   the engine.
 */
static const char QVAR_CHAIN_RULES[] =
    "rule \"Leaf\"(V) { when User.Score == V and User.Score >= 80 then A = 1; }"
    "rule \"Mid\"(V) { when goal(\"Leaf\", V) then B = 1; }";

static const char QVAR_PICK_RULES[] =
    "rule \"Pick\"(V) { when User.A == V then A = 1; }"
    "rule \"Pick\"(V) { when User.B == V then B = 1; }";

static const char QVAR_PAIR_RULES[] =
    "rule \"Pair\"(L, R) { when User.A == L and User.B == R then Hit = 1; }";

static const char GOAL_STRING_RULES[] =
    "rule \"Pick\"(V) { when User.Name == V then Chosen = 1; }";

static int proof_binding_named(re_proof_t *proof, const char *name, re_query_binding_t *out) {
    size_t count = re_proof_binding_count(proof);
    size_t index;
    size_t name_size = strlen(name);
    for (index = 0u; index < count; ++index) {
        if (re_proof_binding_get(proof, index, out) != RE_STATUS_OK) return 0;
        if (out->name.size == name_size && memcmp(out->name.data, name, name_size) == 0) return 1;
    }
    return 0;
}

TEST(qvar_binds_from_fact) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_query_t *query = NULL;
    re_proof_t *proof = NULL;
    re_query_binding_t binding;
    re_value_t score = {RE_VALUE_INT64, {.int64_value = 85}};
    ASSERT_EQ(re_facts_set(facts, text("User.Score"), &score), RE_STATUS_OK);
    /* Fact on the left: `?s` claims the fact value. */
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("User.Score == ?s"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    ASSERT_EQ(re_query_solution_count(query), 1u);
    ASSERT_EQ(re_query_next(query, &proof), RE_STATUS_OK);
    memset(&binding, 0, sizeof(binding));
    ASSERT_TRUE(proof_binding_named(proof, "?s", &binding));
    ASSERT_EQ(binding.value.type, RE_VALUE_INT64);
    ASSERT_EQ(binding.value.as.int64_value, 85);
    re_proof_destroy(proof);
    re_query_destroy(query);
    query = NULL;
    proof = NULL;
    /* Variable on the left: the unify case table is symmetric. */
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("?s == User.Score"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    ASSERT_EQ(re_query_solution_count(query), 1u);
    ASSERT_EQ(re_query_next(query, &proof), RE_STATUS_OK);
    memset(&binding, 0, sizeof(binding));
    ASSERT_TRUE(proof_binding_named(proof, "?s", &binding));
    ASSERT_EQ(binding.value.as.int64_value, 85);
    re_proof_destroy(proof);
    re_query_destroy(query);
    query = NULL;
    proof = NULL;
    /* A literal is resolvable, so the variable binds it directly. */
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("?x == 42"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    ASSERT_EQ(re_query_next(query, &proof), RE_STATUS_OK);
    memset(&binding, 0, sizeof(binding));
    ASSERT_TRUE(proof_binding_named(proof, "?x", &binding));
    ASSERT_EQ(binding.value.type, RE_VALUE_INT64);
    ASSERT_EQ(binding.value.as.int64_value, 42);
    re_proof_destroy(proof);
    re_query_destroy(query);
    query = NULL;
    proof = NULL;
    /* An absent fact is unresolvable: UNKNOWN, like the literal path. */
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("?n == Missing.Fact"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_UNKNOWN);
    ASSERT_EQ(re_query_solution_count(query), 0u);
    re_query_destroy(query);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(qvar_binds_through_rule_goal_chain) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_query_t *query = NULL;
    re_proof_t *proof = NULL;
    re_query_binding_t binding;
    re_value_t score = {RE_VALUE_INT64, {.int64_value = 85}};
    aggregate_install(engine, QVAR_CHAIN_RULES);
    ASSERT_EQ(re_facts_set(facts, text("User.Score"), &score), RE_STATUS_OK);
    /* The unbound `?s` actual leaves Mid's formal V unbound; the Leaf goal
     * call carries the same placeholder down, and the condition's fact read
     * claims it - the alias then points `?s` at the derived value. */
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("goal(\"Mid\", ?s)"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    ASSERT_EQ(re_query_solution_count(query), 1u);
    ASSERT_EQ(re_query_next(query, &proof), RE_STATUS_OK);
    memset(&binding, 0, sizeof(binding));
    ASSERT_TRUE(proof_binding_named(proof, "?s", &binding));
    ASSERT_EQ(binding.value.type, RE_VALUE_INT64);
    ASSERT_EQ(binding.value.as.int64_value, 85);
    memset(&binding, 0, sizeof(binding));
    ASSERT_TRUE(proof_binding_named(proof, "V", &binding));
    ASSERT_EQ(binding.value.as.int64_value, 85);
    re_proof_destroy(proof);
    re_query_destroy(query);
    query = NULL;
    proof = NULL;
    /* Without the fact the chain cannot drive the proof: UNKNOWN. (Inside a
     * rule condition an absent fact operand resolves to false through the
     * pre-existing rule-goal fallback in backward_operand_goal, so the ==
     * side binds V = false; the >= 80 gate then rejects the branch. The
     * direct query path has no such fallback and reports UNKNOWN on the
     * absent read itself, as qvar_binds_from_fact shows.) */
    re_facts_destroy(facts);
    facts = re_facts_create(NULL, NULL);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("goal(\"Mid\", ?s)"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_UNKNOWN);
    ASSERT_EQ(re_query_solution_count(query), 0u);
    re_query_destroy(query);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(qvar_sticky_consistency_conflict_fails_branch) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_query_t *query = NULL;
    re_proof_t *proof = NULL;
    re_query_binding_t binding;
    re_value_t a = {RE_VALUE_INT64, {.int64_value = 1}};
    re_value_t b = {RE_VALUE_INT64, {.int64_value = 2}};
    aggregate_install(engine, QVAR_PAIR_RULES);
    ASSERT_EQ(re_facts_set(facts, text("User.A"), &a), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("User.B"), &b), RE_STATUS_OK);
    /* Both formals alias the same `?x`: L claims 1 from User.A, then R's
     * claim of 2 from User.B conflicts with the sticky `?x` binding - the
     * branch fails (UNKNOWN, zero solutions), it is not an engine error. */
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("goal(\"Pair\", ?x, ?x)"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_UNKNOWN);
    ASSERT_EQ(re_query_solution_count(query), 0u);
    re_query_destroy(query);
    query = NULL;
    /* Same value on both reads unifies: the branch proves with ?x = 1. */
    b.as.int64_value = 1;
    ASSERT_EQ(re_facts_set(facts, text("User.B"), &b), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("goal(\"Pair\", ?x, ?x)"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    ASSERT_EQ(re_query_solution_count(query), 1u);
    ASSERT_EQ(re_query_next(query, &proof), RE_STATUS_OK);
    memset(&binding, 0, sizeof(binding));
    ASSERT_TRUE(proof_binding_named(proof, "?x", &binding));
    ASSERT_EQ(binding.value.type, RE_VALUE_INT64);
    ASSERT_EQ(binding.value.as.int64_value, 1);
    re_proof_destroy(proof);
    re_query_destroy(query);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(qvar_two_unbound_variables_no_match) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_query_t *query = NULL;
    /* Neither side can produce a value and nothing defers: no match. No fact
     * is read, so the failure is definitive (DISPROVED, not UNKNOWN). */
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("?x == ?y"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_DISPROVED);
    ASSERT_EQ(re_query_solution_count(query), 0u);
    re_query_destroy(query);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(qvar_aggregation_over_bindings) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t a = {RE_VALUE_INT64, {.int64_value = 10}};
    re_value_t b = {RE_VALUE_INT64, {.int64_value = 20}};
    re_value_t out;
    aggregate_install(engine, QVAR_PICK_RULES);
    ASSERT_EQ(re_facts_set(facts, text("User.A"), &a), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("User.B"), &b), RE_STATUS_OK);
    /* The aggregation field names the `?s` binding verbatim, prefix included. */
    ASSERT_EQ(re_engine_query_aggregate(engine, facts, RE_ACCUM_SUM, text("?s"),
                                        text("goal(\"Pick\", ?s)"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.type, RE_VALUE_INT64);
    ASSERT_EQ(out.as.int64_value, 30);
    ASSERT_EQ(re_engine_query_aggregate(engine, facts, RE_ACCUM_COUNT, text("?s"),
                                        text("goal(\"Pick\", ?s)"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.type, RE_VALUE_INT64);
    ASSERT_EQ(out.as.int64_value, 2);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(qvar_multi_solution_enumeration_under_max_solutions) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_query_t *query = NULL;
    re_proof_t *proof = NULL;
    re_query_binding_t binding;
    re_value_t a = {RE_VALUE_INT64, {.int64_value = 10}};
    re_value_t b = {RE_VALUE_INT64, {.int64_value = 20}};
    re_query_options_t options = {sizeof(options), 64u, 2u, 0u, 0u};
    aggregate_install(engine, QVAR_PICK_RULES);
    ASSERT_EQ(re_facts_set(facts, text("User.A"), &a), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("User.B"), &b), RE_STATUS_OK);
    /* Each rule alternative is its own proof branch with its own `?s`. */
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("goal(\"Pick\", ?s)"), &options, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    ASSERT_EQ(re_query_solution_count(query), 2u);
    ASSERT_EQ(re_query_next(query, &proof), RE_STATUS_OK);
    memset(&binding, 0, sizeof(binding));
    ASSERT_TRUE(proof_binding_named(proof, "?s", &binding));
    ASSERT_EQ(binding.value.as.int64_value, 10);
    re_proof_destroy(proof);
    ASSERT_EQ(re_query_next(query, &proof), RE_STATUS_OK);
    memset(&binding, 0, sizeof(binding));
    ASSERT_TRUE(proof_binding_named(proof, "?s", &binding));
    ASSERT_EQ(binding.value.as.int64_value, 20);
    re_proof_destroy(proof);
    re_query_destroy(query);
    query = NULL;
    proof = NULL;
    /* A single-solution budget stops after the first alternative. */
    options.max_solutions = 1u;
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("goal(\"Pick\", ?s)"), &options, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    ASSERT_EQ(re_query_solution_count(query), 1u);
    ASSERT_EQ(re_query_next(query, &proof), RE_STATUS_OK);
    memset(&binding, 0, sizeof(binding));
    ASSERT_TRUE(proof_binding_named(proof, "?s", &binding));
    ASSERT_EQ(binding.value.as.int64_value, 10);
    re_proof_destroy(proof);
    ASSERT_EQ(re_query_next(query, &proof), RE_STATUS_NOT_FOUND);
    re_query_destroy(query);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

/* Final whole-branch review regression: the legacy zero-arg goal("...") unwrap
 * in dispatch_once must fire only for the single-quoted-name form. An
 * argument-bearing call whose last actual is a string literal also starts with
 * `goal("` and ends with `")`, so the old guard mangled it to `Pick", "alice`
 * before parse_goal_call ever saw it and the query reported UNKNOWN with zero
 * solutions for a provable goal. */
TEST(goal_call_trailing_string_actual_proves) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_query_t *query = NULL;
    re_proof_t *proof = NULL;
    re_query_binding_t binding;
    re_value_t name = {RE_VALUE_STRING, {.string = {"alice", 5u}}};
    aggregate_install(engine, GOAL_STRING_RULES);
    ASSERT_EQ(re_facts_set(facts, text("User.Name"), &name), RE_STATUS_OK);
    /* The trailing string actual must reach parse_goal_call intact: the formal
     * V binds "alice" and the condition matches the fact. */
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("goal(\"Pick\", \"alice\")"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    ASSERT_EQ(re_query_solution_count(query), 1u);
    ASSERT_EQ(re_query_next(query, &proof), RE_STATUS_OK);
    memset(&binding, 0, sizeof(binding));
    ASSERT_TRUE(proof_binding_named(proof, "V", &binding));
    ASSERT_EQ(binding.value.type, RE_VALUE_STRING);
    ASSERT_TRUE(binding.value.as.string.size == 5u &&
                memcmp(binding.value.as.string.data, "alice", 5u) == 0);
    re_proof_destroy(proof);
    re_query_destroy(query);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(goal_call_zero_arg_name_still_unwraps) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_query_t *query = NULL;
    re_value_t flag = {RE_VALUE_INT64, {.int64_value = 1}};
    aggregate_install(engine,
                      "rule \"Derive\" { when Flag == 1 then Derived = 1; }");
    ASSERT_EQ(re_facts_set(facts, text("Flag"), &flag), RE_STATUS_OK);
    /* The single-quoted-name form carries no interior quote, so the legacy
     * unwrap still applies and the bare rule goal proves. */
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("goal(\"Derive\")"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    ASSERT_EQ(re_query_solution_count(query), 1u);
    re_query_destroy(query);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(query_not_goal_call_string_actual_inverts) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_query_t *query = NULL;
    re_value_t name = {RE_VALUE_STRING, {.string = {"alice", 5u}}};
    aggregate_install(engine, GOAL_STRING_RULES);
    /* Fact absent: the string-actual subgoal cannot prove, so NOT proves. */
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("NOT goal(\"Pick\", \"alice\")"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    ASSERT_EQ(re_query_solution_count(query), 1u);
    re_query_destroy(query);
    query = NULL;
    /* Fact present: the subgoal proves, so the negated goal is disproved. */
    ASSERT_EQ(re_facts_set(facts, text("User.Name"), &name), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("NOT goal(\"Pick\", \"alice\")"), NULL, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_DISPROVED);
    ASSERT_EQ(re_query_solution_count(query), 0u);
    re_query_destroy(query);
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
    RUN_TEST(member_write_bumps_mutation_serial);
    RUN_TEST(disable_flag_bypasses_cache);
    RUN_TEST(different_facts_objects_do_not_share);
    RUN_TEST(not_absent_fact_cache_stays_fresh);
    RUN_TEST(shared_graph_full_clears_all);
    RUN_TEST(proof_graph_stats_arguments);
    RUN_TEST(retract_invalidates_cached_proof);
    RUN_TEST(tms_cascade_invalidates_cached_proof);
    RUN_TEST(retract_only_transaction_invalidates_cache);
    RUN_TEST(facts_nonce_blocks_aba_stale_hit);
    RUN_TEST(bfs_deepening_limits_at_configured_max_depth);
    RUN_TEST(aggregate_reports_limit_at_solution_cap);
    RUN_TEST(aggregate_below_solution_cap_succeeds);
    RUN_TEST(query_rule_with_forall_paren_condition_fails_not_supported);
    RUN_TEST(query_rule_with_exists_paren_condition_fails_not_supported);
    RUN_TEST(proof_graph_unrelated_mutation_preserves_entry);
    RUN_TEST(proof_graph_invalidation_chain_retracts_dependents);
    RUN_TEST(proof_graph_multiple_justifications_survive);
    RUN_TEST(proof_graph_stats_v2_reports_full_counters);
    RUN_TEST(proof_graph_evictions_counted_on_clear_all);
    RUN_TEST(proof_graph_goal_text_is_the_cache_key);
    RUN_TEST(qvar_binds_from_fact);
    RUN_TEST(qvar_binds_through_rule_goal_chain);
    RUN_TEST(qvar_sticky_consistency_conflict_fails_branch);
    RUN_TEST(qvar_two_unbound_variables_no_match);
    RUN_TEST(qvar_aggregation_over_bindings);
    RUN_TEST(qvar_multi_solution_enumeration_under_max_solutions);
    RUN_TEST(goal_call_trailing_string_actual_proves);
    RUN_TEST(goal_call_zero_arg_name_still_unwraps);
    RUN_TEST(query_not_goal_call_string_actual_inverts);
TEST_MAIN_END()
