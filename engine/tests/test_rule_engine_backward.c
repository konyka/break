#include "test_framework.h"
#include "../src/rule_engine/rule_engine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Backward-contract coverage for the bounded query seam:
 *
 * - Formal parameters, argument-bearing goal calls, and custom-function
 *   conditions are covered by the bounded compatibility evaluator; the
 *   explicit machine remains reserved for simple zero-argument chains.
 * - Alternatives are visited in source order. max_solutions caps returned
 *   proofs, while max_depth yields RE_QUERY_LIMIT rather than hanging. A
 *   cycle without a proof is RE_QUERY_UNKNOWN when within the depth bound.
 * - A proof has one node per selected rule invocation. The existing trace API
 *   is the test-private graph projection for Wave 1: trace[i] is a node and
 *   trace[i] -> trace[i + 1] is its child edge in depth-first order.
 * - Fact mutation invalidates an already-created query and prevents stale
 *   proofs from being returned.
 *
 * The tests below use distinct expected values so they test selection and
 * binding semantics rather than reproducing a presumed implementation.
 */

static re_string_t text(const char *value) {
    re_string_t result = {value, strlen(value)};
    return result;
}

typedef struct query_fixture_t {
    re_engine_t *engine;
    re_facts_t *facts;
    re_query_t *query;
} query_fixture_t;

typedef struct query_case_t {
    const char *source;
    const char *name;
    size_t max_depth;
    size_t max_solutions;
} query_case_t;

static re_status_t query_rules(const query_case_t *test_case,
                               query_fixture_t *fixture) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_query_t *query = NULL;
    re_query_options_t options = {
        sizeof(options), test_case->max_depth, test_case->max_solutions, 0u, 0u
    };
    re_status_t status;
    if (engine == NULL || facts == NULL) {
        re_facts_destroy(facts);
        re_engine_destroy(engine);
        return RE_STATUS_OUT_OF_MEMORY;
    }
    status = re_program_load(NULL, text(test_case->source), NULL, &program);
    if (status == RE_STATUS_OK) status = re_engine_install(engine, program);
    if (status == RE_STATUS_OK)
        status = re_engine_query_bounded(engine, facts, text(test_case->name),
                                         &options, &query);
    if (status != RE_STATUS_OK) {
        re_program_destroy(program);
        re_facts_destroy(facts);
        re_engine_destroy(engine);
        return status;
    }
    fixture->engine = engine;
    fixture->facts = facts;
    fixture->query = query;
    return RE_STATUS_OK;
}

static void destroy_query_fixture(query_fixture_t *fixture) {
    re_query_destroy(fixture->query);
    re_facts_destroy(fixture->facts);
    re_engine_destroy(fixture->engine);
}

TEST(base_rule_proves_from_fact) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_query_t *query = NULL;
    re_query_options_t options = {sizeof(options), 4u, 2u, 0u, 0u};
    re_value_t ready = {RE_VALUE_BOOL, {.boolean = 1}};
    ASSERT_EQ(re_facts_set(facts, text("Ready"), &ready), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text("rule \"Base\" { when Ready == true then X = 1; }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("Base"), &options, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    ASSERT_EQ(re_query_solution_count(query), 1u);
    re_query_destroy(query);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(derived_rule_calls_explicit_goal) {
    query_fixture_t fixture;
    query_case_t test_case = {
        "rule \"Base\" { when true then X = 1; }"
        "rule \"Derived\" { when goal(\"Base\") then Y = 1; }",
        "Derived", 4u, 2u
    };
    ASSERT_EQ(query_rules(&test_case, &fixture), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(fixture.query), RE_QUERY_PROVED);
    ASSERT_EQ(re_query_solution_count(fixture.query), 1u);
    destroy_query_fixture(&fixture);
}

TEST(alternative_base_rules_yield_two_solutions) {
    query_fixture_t fixture;
    query_case_t test_case = {
        "rule \"Base\" { when true then A = 1; }"
        "rule \"Base\" { when true then B = 1; }"
        "rule \"Derived\" { when goal(\"Base\") then C = 1; }",
        "Base", 4u, 4u
    };
    ASSERT_EQ(query_rules(&test_case, &fixture), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(fixture.query), RE_QUERY_PROVED);
    ASSERT_EQ(re_query_solution_count(fixture.query), 2u);
    destroy_query_fixture(&fixture);
}

TEST(recursive_cycle_returns_unknown_without_hanging) {
    query_fixture_t fixture;
    query_case_t test_case = {
        "rule \"A\" { when goal(\"B\") then X = 1; }"
        "rule \"B\" { when goal(\"A\") then Y = 1; }",
        "A", 8u, 2u
    };
    ASSERT_EQ(query_rules(&test_case, &fixture), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(fixture.query), RE_QUERY_UNKNOWN);
    ASSERT_EQ(re_query_solution_count(fixture.query), 0u);
    destroy_query_fixture(&fixture);
}

TEST(recursive_query_honors_max_depth) {
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
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("Top"), &options, &query), RE_STATUS_LIMIT);
    ASSERT_EQ(re_query_result(query), RE_QUERY_LIMIT);
    ASSERT_EQ(re_query_solution_count(query), 0u);
    re_query_destroy(query);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(proof_trace_follows_recursive_rule_path) {
    query_fixture_t fixture;
    query_case_t test_case = {
        "rule \"Base\" { when true then X = 1; }"
        "rule \"Middle\" { when goal(\"Base\") then Y = 1; }"
        "rule \"Top\" { when goal(\"Middle\") then Z = 1; }",
        "Top", 4u, 2u
    };
    re_proof_t *proof = NULL;
    re_string_t name;
    re_proof_node_t node = {sizeof(node), {NULL, 0u}};
    re_proof_edge_t edge = {sizeof(edge), 0u, 0u};
    ASSERT_EQ(query_rules(&test_case, &fixture), RE_STATUS_OK);
    ASSERT_EQ(re_query_next(fixture.query, &proof), RE_STATUS_OK);
    ASSERT_EQ(re_proof_trace_count(proof), 3u);
    ASSERT_EQ(re_proof_trace_get(proof, 0u, &name), RE_STATUS_OK);
    ASSERT_TRUE(name.size == 3u && memcmp(name.data, "Top", 3u) == 0);
    ASSERT_EQ(re_proof_trace_get(proof, 1u, &name), RE_STATUS_OK);
    ASSERT_TRUE(name.size == 6u && memcmp(name.data, "Middle", 6u) == 0);
    ASSERT_EQ(re_proof_trace_get(proof, 2u, &name), RE_STATUS_OK);
    ASSERT_TRUE(name.size == 4u && memcmp(name.data, "Base", 4u) == 0);
    ASSERT_EQ(re_proof_node_count(proof), 3u);
    ASSERT_EQ(re_proof_edge_count(proof), 2u);
    ASSERT_EQ(re_proof_node_get(proof, 0u, &node), RE_STATUS_OK);
    ASSERT_TRUE(node.rule_name.size == 3u && memcmp(node.rule_name.data, "Top", 3u) == 0);
    ASSERT_EQ(re_proof_edge_get(proof, 0u, &edge), RE_STATUS_OK);
    ASSERT_EQ(edge.parent_index, 0u);
    ASSERT_EQ(edge.child_index, 1u);
    ASSERT_EQ(re_proof_edge_get(proof, 1u, &edge), RE_STATUS_OK);
    ASSERT_EQ(edge.parent_index, 1u);
    ASSERT_EQ(edge.child_index, 2u);
    re_proof_destroy(proof);
    destroy_query_fixture(&fixture);
}

TEST(fact_mutation_invalidates_recursive_proofs) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_query_t *query = NULL;
    re_proof_t *proof = NULL;
    re_query_options_t options = {sizeof(options), 4u, 2u, 0u, 0u};
    re_value_t value = {RE_VALUE_BOOL, {.boolean = 1}};
    ASSERT_EQ(re_facts_set(facts, text("Ready"), &value), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text(
        "rule \"Base\" { when Ready == true then X = 1; }"
        "rule \"Derived\" { when goal(\"Base\") then Y = 1; }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("Derived"), &options, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    ASSERT_EQ(re_query_solution_count(query), 1u);
    ASSERT_EQ(re_query_next(query, &proof), RE_STATUS_OK);
    re_proof_destroy(proof);
    proof = NULL;
    value.as.boolean = 0;
    ASSERT_EQ(re_facts_set(facts, text("Ready"), &value), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_UNKNOWN);
    ASSERT_EQ(re_query_solution_count(query), 0u);
    ASSERT_EQ(re_query_next(query, &proof), RE_STATUS_NOT_FOUND);
    re_query_destroy(query);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(nested_or_enumerates_all_root_derivations) {
    query_fixture_t fixture;
    ASSERT_EQ(query_rules(&(query_case_t){
        "rule \"A\" { when true then A = 1; }"
        "rule \"B\" { when true then B = 2; }"
        "rule \"C\" { when true then C = 3; }"
        "rule \"Top\" { when goal(\"A\") or goal(\"B\") or goal(\"C\") then Done = 1; }",
        "Top", 8u, 4u}, &fixture), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(fixture.query), RE_QUERY_PROVED);
    ASSERT_EQ(re_query_solution_count(fixture.query), 3u);
    destroy_query_fixture(&fixture);
}

TEST(nested_or_under_and_preserves_all_branches) {
    query_fixture_t fixture;
    ASSERT_EQ(query_rules(&(query_case_t){
        "rule \"A\" { when true then A = 1; }"
        "rule \"B\" { when true then B = 2; }"
        "rule \"C\" { when true then C = 3; }"
        "rule \"Top\" { when true and (goal(\"A\") or goal(\"B\") or goal(\"C\")) then Done = 1; }",
        "Top", 8u, 4u}, &fixture), RE_STATUS_OK);
    ASSERT_EQ(re_query_solution_count(fixture.query), 3u);
    destroy_query_fixture(&fixture);
}

/*
 * Characterization for bounded deep goal traversal. The source is intentionally
 * bounded and the chain is finite, so this guards the traversal budget without
 * depending on a particular continuation representation.
 */
TEST(generated_deep_goal_chain_proves_with_bounded_source) {
    enum { chain_length = 600, source_capacity = chain_length * 96 };
    char *source = (char *)malloc(source_capacity);
    size_t used = 0u;
    query_fixture_t fixture;
    re_proof_t *proof = NULL;
    re_string_t name;
    int index;
    ASSERT_TRUE(source != NULL);
    for (index = chain_length - 1; index >= 0; --index) {
        int written;
        if (index == chain_length - 1)
            written = snprintf(source + used, source_capacity - used,
                               "rule \"Goal%d\" { when true then Done = true; }", index);
        else
            written = snprintf(source + used, source_capacity - used,
                               "rule \"Goal%d\" { when goal(\"Goal%d\") then Done = true; }",
                               index, index + 1);
        ASSERT_TRUE(written > 0 && (size_t)written < source_capacity - used);
        used += (size_t)written;
    }
    ASSERT_EQ(query_rules(&(query_case_t){source, "Goal0", chain_length + 1u, 1u}, &fixture), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(fixture.query), RE_QUERY_PROVED);
    ASSERT_EQ(re_query_solution_count(fixture.query), 1u);
    ASSERT_EQ(re_query_next(fixture.query, &proof), RE_STATUS_OK);
    ASSERT_EQ(re_proof_trace_count(proof), (size_t)chain_length);
    ASSERT_EQ(re_proof_trace_get(proof, 0u, &name), RE_STATUS_OK);
    ASSERT_TRUE(name.size == 5u && memcmp(name.data, "Goal0", 5u) == 0);
    ASSERT_EQ(re_proof_trace_get(proof, chain_length - 1u, &name), RE_STATUS_OK);
    ASSERT_TRUE(name.size == 7u && memcmp(name.data, "Goal599", 7u) == 0);
    re_proof_destroy(proof);
    destroy_query_fixture(&fixture);
    free(source);
}

TEST(generated_deep_goal_chain_with_conditions_proves) {
    enum { chain_length = 600, source_capacity = chain_length * 120 };
    char *source = (char *)malloc(source_capacity);
    size_t used = 0u;
    int index;
    query_fixture_t fixture;
    ASSERT_TRUE(source != NULL);
    for (index = chain_length - 1; index >= 0; --index) {
        int written;
        if (index == chain_length - 1)
            written = snprintf(source + used, source_capacity - used,
                               "rule \"Goal%d\" { when true and true then Done = true; }", index);
        else
            written = snprintf(source + used, source_capacity - used,
                               "rule \"Goal%d\" { when goal(\"Goal%d\") and true then Done = true; }",
                               index, index + 1);
        ASSERT_TRUE(written > 0 && (size_t)written < source_capacity - used);
        used += (size_t)written;
    }
    ASSERT_EQ(query_rules(&(query_case_t){source, "Goal0", chain_length + 1u, 1u}, &fixture), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(fixture.query), RE_QUERY_PROVED);
    ASSERT_EQ(re_query_solution_count(fixture.query), 1u);
    destroy_query_fixture(&fixture);
    free(source);
}

TEST(deep_boolean_condition_proves_without_recursive_condition_walk) {
    enum { clause_count = 1200, source_capacity = clause_count * 16 + 96 };
    char *source = (char *)malloc(source_capacity);
    size_t used = 0u;
    int index;
    query_fixture_t fixture;
    ASSERT_TRUE(source != NULL);
    used += (size_t)snprintf(source + used, source_capacity - used,
                             "rule \"Deep\" { when true");
    for (index = 1; index < clause_count; ++index)
        used += (size_t)snprintf(source + used, source_capacity - used, " and true");
    used += (size_t)snprintf(source + used, source_capacity - used, " then Done = 1; }");
    ASSERT_EQ(query_rules(&(query_case_t){source, "Deep", clause_count + 2u, 1u}, &fixture), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(fixture.query), RE_QUERY_PROVED);
    ASSERT_EQ(re_query_solution_count(fixture.query), 1u);
    destroy_query_fixture(&fixture);
    free(source);
}

TEST(failed_boolean_alternative_rolls_back_nested_goal_trace) {
    query_fixture_t fixture;
    re_proof_t *proof = NULL;
    re_string_t name;
    ASSERT_EQ(query_rules(&(query_case_t){
        "rule \"Bad\" { when true then Bad = 1; }"
        "rule \"Good\" { when true then Good = 1; }"
        "rule \"Top\" { when goal(\"Bad\") and false or goal(\"Good\") then Done = 1; }",
        "Top", 8u, 2u}, &fixture), RE_STATUS_OK);
    ASSERT_EQ(re_query_next(fixture.query, &proof), RE_STATUS_OK);
    ASSERT_EQ(re_proof_trace_count(proof), 2u);
    ASSERT_EQ(re_proof_trace_get(proof, 0u, &name), RE_STATUS_OK);
    ASSERT_TRUE(name.size == 3u && memcmp(name.data, "Top", 3u) == 0);
    ASSERT_EQ(re_proof_trace_get(proof, 1u, &name), RE_STATUS_OK);
    ASSERT_TRUE(name.size == 4u && memcmp(name.data, "Good", 4u) == 0);
    re_proof_destroy(proof);
    destroy_query_fixture(&fixture);
}


TEST_MAIN_BEGIN()
    RUN_TEST(base_rule_proves_from_fact);
    RUN_TEST(derived_rule_calls_explicit_goal);
    RUN_TEST(alternative_base_rules_yield_two_solutions);
    RUN_TEST(recursive_cycle_returns_unknown_without_hanging);
    RUN_TEST(recursive_query_honors_max_depth);
    RUN_TEST(proof_trace_follows_recursive_rule_path);
    RUN_TEST(fact_mutation_invalidates_recursive_proofs);
    RUN_TEST(nested_or_enumerates_all_root_derivations);
    RUN_TEST(nested_or_under_and_preserves_all_branches);
    RUN_TEST(generated_deep_goal_chain_proves_with_bounded_source);
    RUN_TEST(generated_deep_goal_chain_with_conditions_proves);
    RUN_TEST(deep_boolean_condition_proves_without_recursive_condition_walk);
    RUN_TEST(failed_boolean_alternative_rolls_back_nested_goal_trace);
TEST_MAIN_END()
