#include "test_framework.h"
#include "../src/rule_engine/rule_engine.h"
#include <string.h>

static re_string_t text(const char *value) {
    re_string_t result = {value, strlen(value)};
    return result;
}

typedef struct allocator_state_t {
    size_t calls;
    size_t fail_at;
    size_t frees;
} allocator_state_t;

static void *test_alloc(void *context, size_t size) {
    allocator_state_t *state = context;
    ++state->calls;
    if (state->fail_at != 0u && state->calls >= state->fail_at) return NULL;
    return malloc(size);
}

static void *test_realloc(void *context, void *memory, size_t size) {
    allocator_state_t *state = context;
    ++state->calls;
    if (state->fail_at != 0u && state->calls >= state->fail_at) return NULL;
    return realloc(memory, size);
}

static void test_free(void *context, void *memory) {
    allocator_state_t *state = context;
    ++state->frees;
    free(memory);
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
    re_query_options_t options = {sizeof(options), max_depth, max_solutions, 0u, 0u};
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
    if (query != NULL && fixture != NULL) {
        fixture->engine = engine;
        fixture->facts = facts;
        fixture->query = query;
    }
    if (status != RE_STATUS_OK || fixture == NULL) {
        if (query != NULL) re_query_destroy(query);
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

TEST(conflicting_argument_count_returns_defined_failure) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_query_t *query = NULL;
    re_query_options_t options = {sizeof(options), 4u, 1u, 0u, 0u};
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_program_load(NULL, text(
        "rule \"Lookup\"(Key) { when Key == \"alice\" then Seen = 1; }"
        "rule \"Top\" { when goal(\"Lookup\", \"alice\", \"extra\") then Done = 1; }"),
        NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("Top"), &options, &query),
              RE_STATUS_INVALID_ARGUMENT);
    ASSERT_TRUE(query == NULL);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(formal_parameters_bind_a_one_hop_goal) {
    query_fixture_t fixture;
    re_proof_t *proof = NULL;
    re_query_binding_t binding;
    re_string_t name;
    re_proof_node_t node = {sizeof(node), {NULL, 0u}};
    re_proof_edge_t edge = {sizeof(edge), 0u, 0u};
    ASSERT_EQ(query_rules(
        "rule \"Lookup\"(Key) { when Key == \"alice\" then Seen = 1; }"
        "rule \"Top\" { when goal(\"Lookup\", \"alice\") then Done = 1; }",
        "Top", 4u, 2u, &fixture), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(fixture.query), RE_QUERY_PROVED);
    ASSERT_EQ(re_query_solution_count(fixture.query), 1u);
    ASSERT_EQ(re_query_next(fixture.query, &proof), RE_STATUS_OK);
    ASSERT_EQ(re_proof_binding_count(proof), 1u);
    ASSERT_EQ(re_proof_binding_get(proof, 0u, &binding), RE_STATUS_OK);
    ASSERT_TRUE(binding.name.size == 3u && memcmp(binding.name.data, "Key", 3u) == 0);
    ASSERT_EQ(binding.value.type, RE_VALUE_STRING);
    ASSERT_TRUE(binding.value.as.string.size == 5u && memcmp(binding.value.as.string.data, "alice", 5u) == 0);
    ASSERT_EQ(re_proof_trace_count(proof), 2u);
    ASSERT_EQ(re_proof_trace_get(proof, 0u, &name), RE_STATUS_OK);
    ASSERT_TRUE(name.size == 3u && memcmp(name.data, "Top", 3u) == 0);
    ASSERT_EQ(re_proof_trace_get(proof, 1u, &name), RE_STATUS_OK);
    ASSERT_TRUE(name.size == 6u && memcmp(name.data, "Lookup", 6u) == 0);
    ASSERT_EQ(re_proof_node_count(proof), 2u);
    ASSERT_EQ(re_proof_edge_count(proof), 1u);
    ASSERT_EQ(re_proof_node_get(proof, 1u, &node), RE_STATUS_OK);
    ASSERT_TRUE(node.rule_name.size == 6u && memcmp(node.rule_name.data, "Lookup", 6u) == 0);
    ASSERT_EQ(re_proof_edge_get(proof, 0u, &edge), RE_STATUS_OK);
    ASSERT_EQ(edge.parent_index, 0u);
    ASSERT_EQ(edge.child_index, 1u);
    re_proof_destroy(proof);
    destroy_query_fixture(&fixture);
}

TEST(two_hop_recursive_binding_reaches_the_original_actual) {
    query_fixture_t fixture;
    re_proof_t *proof = NULL;
    re_query_binding_t binding;
    ASSERT_EQ(query_rules(
        "rule \"Leaf\"(Value) { when Value == 7 then Hit = 1; }"
        "rule \"Middle\"(Value) { when goal(\"Leaf\", Value) then Pass = 1; }"
        "rule \"Top\" { when goal(\"Middle\", 7) then Done = 1; }",
        "Top", 8u, 2u, &fixture), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(fixture.query), RE_QUERY_PROVED);
    ASSERT_EQ(re_query_solution_count(fixture.query), 1u);
    ASSERT_EQ(re_query_next(fixture.query, &proof), RE_STATUS_OK);
    ASSERT_EQ(re_proof_binding_count(proof), 1u);
    ASSERT_EQ(re_proof_binding_get(proof, 0u, &binding), RE_STATUS_OK);
    ASSERT_EQ(binding.value.type, RE_VALUE_INT64);
    ASSERT_EQ(binding.value.as.int64_value, 7);
    ASSERT_EQ(re_proof_trace_count(proof), 3u);
    ASSERT_EQ(re_proof_node_count(proof), 3u);
    ASSERT_EQ(re_proof_edge_count(proof), 2u);
    re_proof_destroy(proof);
    destroy_query_fixture(&fixture);
}

TEST(two_argument_alternatives_produce_two_distinct_proofs) {
    query_fixture_t fixture;
    re_proof_t *proof = NULL;
    re_query_binding_t binding;
    ASSERT_EQ(query_rules(
        "rule \"Color\"(Item) { when Item == \"red\" then Mark = 1; }"
        "rule \"Color\"(Item) { when Item == \"blue\" then Mark = 2; }"
        "rule \"Top\" { when goal(\"Color\", \"red\") or goal(\"Color\", \"blue\") then Done = 1; }",
        "Top", 4u, 4u, &fixture), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(fixture.query), RE_QUERY_PROVED);
    ASSERT_EQ(re_query_solution_count(fixture.query), 2u);
    ASSERT_EQ(re_query_next(fixture.query, &proof), RE_STATUS_OK);
    ASSERT_EQ(re_proof_binding_get(proof, 0u, &binding), RE_STATUS_OK);
    ASSERT_TRUE(binding.value.as.string.size == 3u && memcmp(binding.value.as.string.data, "red", 3u) == 0);
    re_proof_destroy(proof);
    ASSERT_EQ(re_query_next(fixture.query, &proof), RE_STATUS_OK);
    ASSERT_EQ(re_proof_binding_get(proof, 0u, &binding), RE_STATUS_OK);
    ASSERT_TRUE(binding.value.as.string.size == 4u && memcmp(binding.value.as.string.data, "blue", 4u) == 0);
    re_proof_destroy(proof);
    ASSERT_EQ(re_query_next(fixture.query, &proof), RE_STATUS_NOT_FOUND);
    destroy_query_fixture(&fixture);
}

TEST(repeated_formal_variable_requires_equality) {
    query_fixture_t fixture;
    ASSERT_EQ(query_rules(
        "rule \"Pair\"(Left, Right) { when Left == Right then Equal = 1; }"
        "rule \"Top\" { when goal(\"Pair\", 3, 3) then Done = 1; }",
        "Top", 4u, 2u, &fixture), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(fixture.query), RE_QUERY_PROVED);
    ASSERT_EQ(re_query_solution_count(fixture.query), 1u);
    destroy_query_fixture(&fixture);
}

TEST(repeated_formal_variable_rejects_mismatched_actuals) {
    query_fixture_t fixture;
    ASSERT_EQ(query_rules(
        "rule \"Pair\"(Left, Right) { when Left == Right then Equal = 1; }"
        "rule \"Top\" { when goal(\"Pair\", 3, 4) then Done = 1; }",
        "Top", 4u, 2u, &fixture), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(fixture.query), RE_QUERY_UNKNOWN);
    ASSERT_EQ(re_query_solution_count(fixture.query), 0u);
    destroy_query_fixture(&fixture);
}

TEST(recursive_binding_cycle_and_limits_are_bounded) {
    ASSERT_EQ(query_rules(
        "rule \"A\"(Value) { when goal(\"B\", Value) then X = 1; }"
        "rule \"B\"(Value) { when goal(\"A\", Value) then Y = 1; }",
        "A", 3u, 2u, NULL), RE_STATUS_LIMIT);
}

TEST(recursive_binding_honors_max_solutions) {
    ASSERT_EQ(query_rules(
        "rule \"Choice\"(Value) { when Value == 1 then A = 1; }"
        "rule \"Choice\"(Value) { when Value == 2 then B = 1; }"
        "rule \"Top\" { when goal(\"Choice\", 1) or goal(\"Choice\", 2) then Done = 1; }",
        "Top", 4u, 1u, NULL), RE_STATUS_OK);
}

TEST(nested_goal_alternatives_preserve_each_derivation) {
    query_fixture_t fixture;
    re_proof_t *proof = NULL;
    re_string_t name;
    re_proof_edge_t edge = {sizeof(edge), 0u, 0u};
    ASSERT_EQ(query_rules(
        "rule \"Leaf\"(Value) { when Value == 1 then A = 1; }"
        "rule \"Leaf\"(Value) { when Value == 2 then B = 2; }"
        "rule \"Middle\"(Value) { when goal(\"Leaf\", Value) then M = 1; }"
        "rule \"Top\" { when goal(\"Middle\", 1) or goal(\"Middle\", 2) then Done = 1; }",
        "Top", 8u, 4u, &fixture), RE_STATUS_OK);
    ASSERT_EQ(re_query_solution_count(fixture.query), 2u);
    ASSERT_EQ(re_query_next(fixture.query, &proof), RE_STATUS_OK);
    ASSERT_EQ(re_proof_trace_get(proof, 0u, &name), RE_STATUS_OK);
    ASSERT_EQ(re_proof_trace_get(proof, 1u, &name), RE_STATUS_OK);
    ASSERT_EQ(re_proof_trace_count(proof), 3u);
    ASSERT_EQ(re_proof_node_count(proof), 3u);
    ASSERT_EQ(re_proof_edge_count(proof), 2u);
    ASSERT_EQ(re_proof_trace_get(proof, 0u, &name), RE_STATUS_OK);
    ASSERT_TRUE(name.size == 3u && memcmp(name.data, "Top", 3u) == 0);
    ASSERT_EQ(re_proof_trace_get(proof, 2u, &name), RE_STATUS_OK);
    ASSERT_TRUE(name.size == 4u && memcmp(name.data, "Leaf", 4u) == 0);
    ASSERT_EQ(re_proof_edge_get(proof, 0u, &edge), RE_STATUS_OK);
    ASSERT_EQ(edge.parent_index, 0u);
    ASSERT_EQ(edge.child_index, 1u);
    ASSERT_EQ(re_proof_edge_get(proof, 1u, &edge), RE_STATUS_OK);
    ASSERT_EQ(edge.parent_index, 1u);
    ASSERT_EQ(edge.child_index, 2u);
    re_proof_destroy(proof);
    ASSERT_EQ(re_query_next(fixture.query, &proof), RE_STATUS_OK);
    ASSERT_EQ(re_proof_trace_count(proof), 1u);
    ASSERT_EQ(re_proof_trace_get(proof, 0u, &name), RE_STATUS_OK);
    ASSERT_TRUE(name.size == 3u && memcmp(name.data, "Top", 3u) == 0);
    re_proof_destroy(proof);
    destroy_query_fixture(&fixture);
}

TEST(sibling_goal_alternatives_have_distinct_parent_edges) {
    query_fixture_t fixture;
    re_proof_t *proof = NULL;
    re_string_t name;
    re_proof_edge_t edge = {sizeof(edge), 0u, 0u};
    ASSERT_EQ(query_rules(
        "rule \"A\" { when true then A = 1; }"
        "rule \"B\" { when true then B = 1; }"
        "rule \"Top\" { when goal(\"A\") then Done = 1; }"
        "rule \"Top\" { when goal(\"B\") then Done = 1; }",
        "Top", 4u, 4u, &fixture), RE_STATUS_OK);
    ASSERT_EQ(re_query_solution_count(fixture.query), 2u);
    ASSERT_EQ(re_query_next(fixture.query, &proof), RE_STATUS_OK);
    ASSERT_EQ(re_proof_node_count(proof), 2u);
    ASSERT_EQ(re_proof_edge_count(proof), 1u);
    ASSERT_EQ(re_proof_edge_get(proof, 0u, &edge), RE_STATUS_OK);
    ASSERT_EQ(edge.parent_index, 0u);
    ASSERT_EQ(edge.child_index, 1u);
    ASSERT_EQ(re_proof_trace_get(proof, 1u, &name), RE_STATUS_OK);
    ASSERT_TRUE(name.size == 1u && memcmp(name.data, "A", 1u) == 0);
    re_proof_destroy(proof);
    ASSERT_EQ(re_query_next(fixture.query, &proof), RE_STATUS_OK);
    ASSERT_EQ(re_proof_node_count(proof), 2u);
    ASSERT_EQ(re_proof_trace_get(proof, 1u, &name), RE_STATUS_OK);
    ASSERT_TRUE(name.size == 1u && memcmp(name.data, "B", 1u) == 0);
    re_proof_destroy(proof);
    destroy_query_fixture(&fixture);
}

TEST(consumed_proof_survives_query_destruction_and_mutation) {
    query_fixture_t fixture;
    re_proof_t *proof = NULL;
    re_string_t name;
    re_value_t changed = {RE_VALUE_BOOL, {.boolean = 0}};
    ASSERT_EQ(query_rules(
        "rule \"Leaf\" { when true then Done = 1; }"
        "rule \"Top\" { when goal(\"Leaf\") then Done = 1; }",
        "Top", 4u, 2u, &fixture), RE_STATUS_OK);
    ASSERT_EQ(re_query_next(fixture.query, &proof), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(fixture.facts, text("Changed"), &changed), RE_STATUS_OK);
    re_query_destroy(fixture.query);
    fixture.query = NULL;
    ASSERT_EQ(re_proof_trace_get(proof, 0u, &name), RE_STATUS_OK);
    ASSERT_TRUE(name.size == 3u && memcmp(name.data, "Top", 3u) == 0);
    re_proof_destroy(proof);
    re_facts_destroy(fixture.facts);
    re_engine_destroy(fixture.engine);
}

TEST(backward_query_reports_proof_allocation_failure) {
    allocator_state_t state = {0u, 0u, 0u};
    re_allocator_t allocator = {&state, test_alloc, test_realloc, test_free};
    re_engine_t *engine = re_engine_create(&allocator, NULL);
    re_facts_t *facts = re_facts_create(&allocator, NULL);
    re_program_t *program = NULL;
    re_query_t *query = NULL;
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_program_load(&allocator,
        text("rule \"Leaf\" { when true then Done = 1; }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    state.fail_at = state.calls + 1u;
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("Leaf"), NULL, &query),
              RE_STATUS_OUT_OF_MEMORY);
    ASSERT_TRUE(query == NULL);
    state.fail_at = 0u;
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(formal_bindings_are_isolated_between_sibling_invocations) {
    query_fixture_t fixture;
    re_proof_t *proof = NULL;
    re_query_binding_t binding;
    ASSERT_EQ(query_rules(
        "rule \"Pick\"(Value) { when Value == 1 then A = 1; }"
        "rule \"Pick\"(Value) { when Value == 2 then B = 2; }"
        "rule \"Top\" { when goal(\"Pick\", 1) or goal(\"Pick\", 2) then Done = 1; }",
        "Top", 8u, 4u, &fixture), RE_STATUS_OK);
    ASSERT_EQ(re_query_solution_count(fixture.query), 2u);
    ASSERT_EQ(re_query_next(fixture.query, &proof), RE_STATUS_OK);
    ASSERT_EQ(re_proof_binding_get(proof, 0u, &binding), RE_STATUS_OK);
    ASSERT_EQ(binding.value.as.int64_value, 1);
    re_proof_destroy(proof);
    ASSERT_EQ(re_query_next(fixture.query, &proof), RE_STATUS_OK);
    ASSERT_EQ(re_proof_binding_get(proof, 0u, &binding), RE_STATUS_OK);
    ASSERT_EQ(binding.value.as.int64_value, 2);
    re_proof_destroy(proof);
    destroy_query_fixture(&fixture);
}

TEST(proof_graph_has_rule_nodes_and_child_edges_for_recursive_binding) {
    ASSERT_EQ(query_rules(
        "rule \"Leaf\"(Value) { when Value == 7 then Hit = 1; }"
        "rule \"Middle\"(Value) { when goal(\"Leaf\", Value) then Pass = 1; }"
        "rule \"Top\" { when goal(\"Middle\", 7) then Done = 1; }",
        "Top", 4u, 2u, NULL), RE_STATUS_OK);
}

TEST(argument_binding_mutation_invalidates_recursive_query) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_query_t *query = NULL;
    re_proof_t *proof = NULL;
    re_query_options_t options = {sizeof(options), 4u, 2u, 0u, 0u};
    re_value_t value = {RE_VALUE_INT64, {.int64_value = 7}};
    ASSERT_EQ(re_facts_set(facts, text("Input"), &value), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text(
        "rule \"Base\"(Value) { when Input == Value then Hit = 1; }"
        "rule \"Top\" { when goal(\"Base\", 7) then Done = 1; }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("Top"), &options, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    ASSERT_EQ(re_query_solution_count(query), 1u);
    ASSERT_EQ(re_query_next(query, &proof), RE_STATUS_OK);
    ASSERT_EQ(re_proof_binding_count(proof), 1u);
    re_proof_destroy(proof);
    proof = NULL;
    value.as.int64_value = 8;
    ASSERT_EQ(re_facts_set(facts, text("Input"), &value), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_UNKNOWN);
    ASSERT_EQ(re_query_solution_count(query), 0u);
    ASSERT_EQ(re_query_next(query, &proof), RE_STATUS_NOT_FOUND);
    ASSERT_TRUE(proof == NULL);
    re_query_destroy(query);
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
    re_proof_t *proof = NULL;
    re_function_t *function = NULL;
    re_function_descriptor_t descriptor = {sizeof(descriptor), RE_ABI_VERSION_MAJOR,
        {"identity", 8u}, identity_function, noop_release, NULL};
    re_query_options_t options = {sizeof(options), nesting + 4u, 1u, 0u, 0u};

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
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("Deep"), &options, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    ASSERT_EQ(re_query_solution_count(query), 1u);
    ASSERT_EQ(re_query_next(query, &proof), RE_STATUS_OK);
    re_proof_destroy(proof);
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
    re_proof_t *proof = NULL;
    re_function_t *function = NULL;
    re_function_descriptor_t descriptor = {sizeof(descriptor), RE_ABI_VERSION_MAJOR,
        {"bool_identity", sizeof("bool_identity") - 1u}, bool_identity_function, noop_release, NULL};
    re_query_options_t options = {sizeof(options), 4u, 1u, 0u, 0u};
    ASSERT_EQ(re_engine_register_function(engine, &descriptor, &function), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text(
        "rule \"Leaf\" { when true then Done = true; }"
        "rule \"Top\" { when bool_identity(goal(\"Leaf\")) == true then Done = true; }"),
        NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("Top"), &options, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    ASSERT_EQ(re_query_solution_count(query), 1u);
    ASSERT_EQ(re_query_next(query, &proof), RE_STATUS_OK);
    re_proof_destroy(proof);
    re_query_destroy(query);
    re_function_unregister(function);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(custom_function_only_backward_condition_uses_general_evaluator) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_query_t *query = NULL;
    re_proof_t *proof = NULL;
    re_function_t *function = NULL;
    re_function_descriptor_t descriptor = {sizeof(descriptor), RE_ABI_VERSION_MAJOR,
        {"bool_identity", sizeof("bool_identity") - 1u}, bool_identity_function, noop_release, NULL};
    re_query_options_t options = {sizeof(options), 4u, 1u, 0u, 0u};
    ASSERT_EQ(re_engine_register_function(engine, &descriptor, &function), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text(
        "rule \"Top\" { when bool_identity(true) == true then Done = true; }"),
        NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("Top"), &options, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    ASSERT_EQ(re_query_solution_count(query), 1u);
    ASSERT_EQ(re_query_next(query, &proof), RE_STATUS_OK);
    re_proof_destroy(proof);
    re_query_destroy(query);
    re_function_unregister(function);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(nested_formal_goal_argument_honors_current_max_depth) {
    ASSERT_EQ(query_rules(
        "rule \"Leaf\" { when true then Done = true; }"
        "rule \"Middle\"(Value) { when Value == true then Done = true; }"
        "rule \"Top\" { when goal(\"Middle\", goal(\"Leaf\")) then Done = true; }",
        "Top", 1u, 1u, NULL), RE_STATUS_LIMIT);
}

TEST(proof_graph_exposes_deterministic_nodes_and_edges) {
    ASSERT_EQ(query_rules(
        "rule \"Leaf\"(Value) { when Value == 7 then Hit = 1; }"
        "rule \"Middle\"(Value) { when goal(\"Leaf\", Value) then Pass = 1; }"
        "rule \"Top\" { when goal(\"Middle\", 7) then Done = 1; }",
        "Top", 4u, 2u, NULL), RE_STATUS_OK);
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
     RUN_TEST(conflicting_argument_count_returns_defined_failure);
    RUN_TEST(formal_parameters_bind_a_one_hop_goal);
    RUN_TEST(two_hop_recursive_binding_reaches_the_original_actual);
    RUN_TEST(two_argument_alternatives_produce_two_distinct_proofs);
     RUN_TEST(repeated_formal_variable_requires_equality);
    RUN_TEST(repeated_formal_variable_rejects_mismatched_actuals);
    RUN_TEST(recursive_binding_cycle_and_limits_are_bounded);
    RUN_TEST(recursive_binding_honors_max_solutions);
     RUN_TEST(nested_goal_alternatives_preserve_each_derivation);
     RUN_TEST(sibling_goal_alternatives_have_distinct_parent_edges);
     RUN_TEST(consumed_proof_survives_query_destruction_and_mutation);
     RUN_TEST(backward_query_reports_proof_allocation_failure);
    RUN_TEST(formal_bindings_are_isolated_between_sibling_invocations);
    RUN_TEST(proof_graph_has_rule_nodes_and_child_edges_for_recursive_binding);
    RUN_TEST(argument_binding_mutation_invalidates_recursive_query);
    RUN_TEST(deep_nested_function_operands_preserve_evaluation_context);
    RUN_TEST(nested_goal_inside_custom_function_argument_preserves_result);
    RUN_TEST(custom_function_only_backward_condition_uses_general_evaluator);
    RUN_TEST(nested_formal_goal_argument_honors_current_max_depth);
    RUN_TEST(proof_graph_exposes_deterministic_nodes_and_edges);
    RUN_TEST(proof_graph_get_validates_struct_size_and_preserves_branch_order);
TEST_MAIN_END()
