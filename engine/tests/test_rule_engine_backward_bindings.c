#include "test_framework.h"
#include "../src/rule_engine/rule_engine.h"
#include <string.h>

static re_string_t text(const char *value) {
    re_string_t result = {value, strlen(value)};
    return result;
}

typedef struct query_fixture_t {
    re_engine_t *engine;
    re_facts_t *facts;
    re_query_t *query;
} query_fixture_t;

static re_status_t identity_function(re_engine_t *engine, re_facts_t *facts,
                                     const re_value_t *arguments, size_t argument_count,
                                     re_value_t *out_value, void *context) {
    (void)engine;
    (void)facts;
    (void)context;
    if (argument_count != 1u) return RE_STATUS_INVALID_ARGUMENT;
    *out_value = arguments[0];
    return RE_STATUS_OK;
}

static re_status_t bool_identity_function(re_engine_t *engine, re_facts_t *facts,
                                           const re_value_t *arguments, size_t argument_count,
                                           re_value_t *out_value, void *context) {
    (void)engine;
    (void)facts;
    (void)context;
    if (argument_count != 1u || arguments[0].type != RE_VALUE_BOOL) return RE_STATUS_INVALID_ARGUMENT;
    *out_value = arguments[0];
    return RE_STATUS_OK;
}

static void noop_release(void *context) {
    (void)context;
}

static re_status_t query_rules(const char *source, const char *name,
                               size_t max_depth, size_t max_solutions,
                               query_fixture_t *fixture) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_query_t *query = NULL;
    re_query_options_t options = {sizeof(options), max_depth, max_solutions};
    re_status_t status;
    int installed = 0;
    if (engine == NULL || facts == NULL) return RE_STATUS_OUT_OF_MEMORY;
    status = re_program_load(NULL, text(source), NULL, &program);
    if (status == RE_STATUS_OK) {
        status = re_engine_install(engine, program);
        installed = status == RE_STATUS_OK;
    }
    if (status == RE_STATUS_OK)
        status = re_engine_query_bounded(engine, facts, text(name), &options, &query);
    if (query != NULL) {
        fixture->engine = engine;
        fixture->facts = facts;
        fixture->query = query;
    }
    if (status != RE_STATUS_OK) {
        if (!installed) re_program_destroy(program);
        re_facts_destroy(facts);
        re_engine_destroy(engine);
        return status;
    }
    return RE_STATUS_OK;
}

static void destroy_query_fixture(query_fixture_t *fixture) {
    re_query_destroy(fixture->query);
    re_facts_destroy(fixture->facts);
    re_engine_destroy(fixture->engine);
}

TEST(unsupported_formal_binding_returns_without_query) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_query_t *query = NULL;
    re_query_options_t options = {sizeof(options), 4u, 1u};
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_program_load(NULL, text(
        "rule \"Lookup\"(Key) { when Key == \"alice\" then Seen = 1; }"
        "rule \"Top\" { when goal(\"Lookup\", \"alice\") then Done = 1; }"),
        NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("Top"), &options, &query),
              RE_STATUS_NOT_SUPPORTED);
    ASSERT_TRUE(query == NULL);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(formal_parameters_bind_a_one_hop_goal) {
    ASSERT_EQ(query_rules(
        "rule \"Lookup\"(Key) { when Key == \"alice\" then Seen = 1; }"
        "rule \"Top\" { when goal(\"Lookup\", \"alice\") then Done = 1; }",
        "Top", 4u, 2u, NULL), RE_STATUS_NOT_SUPPORTED);
}

TEST(two_hop_recursive_binding_reaches_the_original_actual) {
    ASSERT_EQ(query_rules(
        "rule \"Leaf\"(Value) { when Value == 7 then Hit = 1; }"
        "rule \"Middle\"(Value) { when goal(\"Leaf\", Value) then Pass = 1; }"
        "rule \"Top\" { when goal(\"Middle\", 7) then Done = 1; }",
        "Top", 8u, 2u, NULL), RE_STATUS_NOT_SUPPORTED);
}

TEST(two_argument_alternatives_produce_two_distinct_proofs) {
    ASSERT_EQ(query_rules(
        "rule \"Color\"(Item) { when Item == \"red\" then Mark = 1; }"
        "rule \"Color\"(Item) { when Item == \"blue\" then Mark = 2; }"
        "rule \"Top\" { when goal(\"Color\", \"red\") or goal(\"Color\", \"blue\") then Done = 1; }",
        "Top", 4u, 4u, NULL), RE_STATUS_NOT_SUPPORTED);
}

TEST(repeated_formal_variable_requires_equality) {
    ASSERT_EQ(query_rules(
        "rule \"Pair\"(Left, Right) { when Left == Right then Equal = 1; }"
        "rule \"Top\" { when goal(\"Pair\", 3, 3) then Done = 1; }",
        "Top", 4u, 2u, NULL), RE_STATUS_NOT_SUPPORTED);
}

TEST(recursive_binding_cycle_and_limits_are_bounded) {
    ASSERT_EQ(query_rules(
        "rule \"A\"(Value) { when goal(\"B\", Value) then X = 1; }"
        "rule \"B\"(Value) { when goal(\"A\", Value) then Y = 1; }",
        "A", 3u, 2u, NULL), RE_STATUS_NOT_SUPPORTED);
}

TEST(recursive_binding_honors_max_solutions) {
    ASSERT_EQ(query_rules(
        "rule \"Choice\"(Value) { when Value == 1 then A = 1; }"
        "rule \"Choice\"(Value) { when Value == 2 then B = 1; }"
        "rule \"Top\" { when goal(\"Choice\", 1) or goal(\"Choice\", 2) then Done = 1; }",
        "Top", 4u, 1u, NULL), RE_STATUS_NOT_SUPPORTED);
}

TEST(nested_goal_alternatives_preserve_each_derivation) {
    ASSERT_EQ(query_rules(
        "rule \"Leaf\"(Value) { when Value == 1 then A = 1; }"
        "rule \"Leaf\"(Value) { when Value == 2 then B = 2; }"
        "rule \"Middle\"(Value) { when goal(\"Leaf\", Value) then M = 1; }"
        "rule \"Top\" { when goal(\"Middle\", 1) or goal(\"Middle\", 2) then Done = 1; }",
        "Top", 8u, 4u, NULL), RE_STATUS_NOT_SUPPORTED);
}

TEST(formal_bindings_are_isolated_between_sibling_invocations) {
    ASSERT_EQ(query_rules(
        "rule \"Pick\"(Value) { when Value == 1 then A = 1; }"
        "rule \"Pick\"(Value) { when Value == 2 then B = 2; }"
        "rule \"Top\" { when goal(\"Pick\", 1) or goal(\"Pick\", 2) then Done = 1; }",
        "Top", 8u, 4u, NULL), RE_STATUS_NOT_SUPPORTED);
}

TEST(proof_graph_has_rule_nodes_and_child_edges_for_recursive_binding) {
    ASSERT_EQ(query_rules(
        "rule \"Leaf\"(Value) { when Value == 7 then Hit = 1; }"
        "rule \"Middle\"(Value) { when goal(\"Leaf\", Value) then Pass = 1; }"
        "rule \"Top\" { when goal(\"Middle\", 7) then Done = 1; }",
        "Top", 4u, 2u, NULL), RE_STATUS_NOT_SUPPORTED);
}

TEST(argument_binding_mutation_invalidates_recursive_query) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_query_t *query = NULL;
    re_query_options_t options = {sizeof(options), 4u, 2u};
    re_value_t value = {RE_VALUE_INT64, {.int64_value = 7}};
    ASSERT_EQ(re_facts_set(facts, text("Input"), &value), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text(
        "rule \"Base\"(Value) { when Input == Value then Hit = 1; }"
        "rule \"Top\" { when goal(\"Base\", 7) then Done = 1; }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("Top"), &options, &query), RE_STATUS_NOT_SUPPORTED);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(deep_nested_function_operands_preserve_evaluation_context) {
    enum { nesting = 600, source_capacity = nesting * 10 + 96 };
    char *source = (char *)malloc(source_capacity);
    size_t used = 0u;
    int index;
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_query_t *query = NULL;
    re_function_t *function = NULL;
    re_function_descriptor_t descriptor = {sizeof(descriptor), RE_ABI_VERSION_MAJOR,
        {"identity", 8u}, identity_function, noop_release, NULL};
    re_query_options_t options = {sizeof(options), nesting + 4u, 1u};

    ASSERT_NOT_NULL(source);
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    used += (size_t)snprintf(source + used, source_capacity - used,
                             "rule \"Deep\" { when ");
    for (index = 0; index < nesting; ++index)
        used += (size_t)snprintf(source + used, source_capacity - used, "identity(");
    used += (size_t)snprintf(source + used, source_capacity - used, "1");
    for (index = 0; index < nesting; ++index)
        used += (size_t)snprintf(source + used, source_capacity - used, ")");
    used += (size_t)snprintf(source + used, source_capacity - used,
                             " == 1 then Done = true; }");
    ASSERT_TRUE(used < source_capacity);
    ASSERT_EQ(re_engine_register_function(engine, &descriptor, &function), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text(source), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("Deep"), &options, &query), RE_STATUS_NOT_SUPPORTED);
    re_function_unregister(function);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
    free(source);
}

TEST(nested_goal_inside_custom_function_argument_preserves_result) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_query_t *query = NULL;
    re_function_t *function = NULL;
    re_function_descriptor_t descriptor = {sizeof(descriptor), RE_ABI_VERSION_MAJOR,
        {"bool_identity", sizeof("bool_identity") - 1u}, bool_identity_function, noop_release, NULL};
    re_query_options_t options = {sizeof(options), 4u, 1u};
    ASSERT_EQ(re_engine_register_function(engine, &descriptor, &function), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text(
        "rule \"Leaf\" { when true then Done = true; }"
        "rule \"Top\" { when bool_identity(goal(\"Leaf\")) == true then Done = true; }"),
        NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("Top"), &options, &query), RE_STATUS_NOT_SUPPORTED);
    re_function_unregister(function);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(nested_formal_goal_argument_honors_current_max_depth) {
    ASSERT_EQ(query_rules(
        "rule \"Leaf\" { when true then Done = true; }"
        "rule \"Middle\"(Value) { when Value == true then Done = true; }"
        "rule \"Top\" { when goal(\"Middle\", goal(\"Leaf\")) then Done = true; }",
        "Top", 1u, 1u, NULL), RE_STATUS_NOT_SUPPORTED);
}

TEST(proof_graph_exposes_deterministic_nodes_and_edges) {
    ASSERT_EQ(query_rules(
        "rule \"Leaf\"(Value) { when Value == 7 then Hit = 1; }"
        "rule \"Middle\"(Value) { when goal(\"Leaf\", Value) then Pass = 1; }"
        "rule \"Top\" { when goal(\"Middle\", 7) then Done = 1; }",
        "Top", 4u, 2u, NULL), RE_STATUS_NOT_SUPPORTED);
}

TEST(proof_graph_get_validates_struct_size_and_preserves_branch_order) {
    query_fixture_t fixture;
    re_proof_t *proof = NULL;
    re_proof_node_t node = {sizeof(node) - 1u, {NULL, 0u}};
    ASSERT_EQ(query_rules(
        "rule \"Choice\" { when true then A = 1; }"
        "rule \"Choice\" { when true then B = 2; }",
        "Choice", 4u, 2u, &fixture), RE_STATUS_OK);
    ASSERT_EQ(re_query_next(fixture.query, &proof), RE_STATUS_OK);
    ASSERT_EQ(re_proof_node_count(proof), 1u);
    ASSERT_EQ(re_proof_edge_count(proof), 0u);
    ASSERT_EQ(re_proof_node_get(proof, 0u, &node), RE_STATUS_INVALID_ARGUMENT);
    node.struct_size = sizeof(node);
    ASSERT_EQ(re_proof_node_get(proof, 0u, &node), RE_STATUS_OK);
    ASSERT_TRUE(node.rule_name.size == 6u && memcmp(node.rule_name.data, "Choice", 6u) == 0);
    re_proof_destroy(proof);
    ASSERT_EQ(re_query_next(fixture.query, &proof), RE_STATUS_OK);
    ASSERT_EQ(re_proof_node_count(proof), 1u);
    re_proof_destroy(proof);
    destroy_query_fixture(&fixture);
}

TEST_MAIN_BEGIN()
    RUN_TEST(unsupported_formal_binding_returns_without_query);
    RUN_TEST(formal_parameters_bind_a_one_hop_goal);
    RUN_TEST(two_hop_recursive_binding_reaches_the_original_actual);
    RUN_TEST(two_argument_alternatives_produce_two_distinct_proofs);
    RUN_TEST(repeated_formal_variable_requires_equality);
    RUN_TEST(recursive_binding_cycle_and_limits_are_bounded);
    RUN_TEST(recursive_binding_honors_max_solutions);
    RUN_TEST(nested_goal_alternatives_preserve_each_derivation);
    RUN_TEST(formal_bindings_are_isolated_between_sibling_invocations);
    RUN_TEST(proof_graph_has_rule_nodes_and_child_edges_for_recursive_binding);
    RUN_TEST(argument_binding_mutation_invalidates_recursive_query);
    RUN_TEST(deep_nested_function_operands_preserve_evaluation_context);
    RUN_TEST(nested_goal_inside_custom_function_argument_preserves_result);
    RUN_TEST(nested_formal_goal_argument_honors_current_max_depth);
    RUN_TEST(proof_graph_exposes_deterministic_nodes_and_edges);
    RUN_TEST(proof_graph_get_validates_struct_size_and_preserves_branch_order);
TEST_MAIN_END()
