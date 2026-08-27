#include "test_framework.h"
#include "../src/rule_engine/re_internal.h"
#include "../src/rule_engine/ir.h"

static re_string_t text(const char *value) {
    re_string_t result = {value, strlen(value)};
    return result;
}

static re_status_t run_source(const char *source, const char *fact_name,
                              re_value_t *value) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_status_t status;
    if (engine == NULL || facts == NULL) {
        re_facts_destroy(facts);
        re_engine_destroy(engine);
        return RE_STATUS_OUT_OF_MEMORY;
    }
    status = re_program_load(NULL, text(source), NULL, &program);
    if (status == RE_STATUS_OK) status = re_engine_install(engine, program);
    if (status == RE_STATUS_OK) status = re_engine_run(engine, facts, NULL, NULL);
    if (status == RE_STATUS_OK && value != NULL)
        status = re_facts_get(facts, text(fact_name), value);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
    return status;
}

static re_status_t run_exists(const char *source, int set_fact, int fact_value,
                              re_value_t *result) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_value_t active = {RE_VALUE_BOOL, {.boolean = fact_value}};
    re_status_t status;
    if (engine == NULL || facts == NULL) {
        re_facts_destroy(facts);
        re_engine_destroy(engine);
        return RE_STATUS_OUT_OF_MEMORY;
    }
    if (set_fact) status = re_facts_set(facts, text("Customer.Active"), &active);
    else status = RE_STATUS_OK;
    if (status == RE_STATUS_OK) status = re_program_load(NULL, text(source), NULL, &program);
    if (status == RE_STATUS_OK) status = re_engine_install(engine, program);
    if (status == RE_STATUS_OK) status = re_engine_run(engine, facts, NULL, NULL);
    if (status == RE_STATUS_OK && result != NULL)
        status = re_facts_get(facts, text("Result"), result);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
    return status;
}

TEST(exists_matches_present_flat_fact) {
    re_value_t result = {RE_VALUE_NONE, {0}};
    ASSERT_EQ(run_exists("rule \"Exists\" { when exists Customer.Active == true then Result = 1; }",
                        1, 1, &result), RE_STATUS_OK);
    ASSERT_EQ(result.type, RE_VALUE_INT64);
    ASSERT_EQ(result.as.int64_value, 1);
}

TEST(exists_absent_fact_does_not_fire) {
    re_value_t result = {RE_VALUE_NONE, {0}};
    ASSERT_EQ(run_exists("rule \"Exists\" { when exists Customer.Active == true then Result = 1; }",
                        0, 0, &result), RE_STATUS_NOT_FOUND);
}

TEST(exists_nonmatching_fact_does_not_fire) {
    re_value_t result = {RE_VALUE_NONE, {0}};
    ASSERT_EQ(run_exists("rule \"Exists\" { when exists Customer.Active == true then Result = 1; }",
                        1, 0, &result), RE_STATUS_NOT_FOUND);
}

TEST(exists_rejects_malformed_and_compound_shapes) {
    re_program_t *program = NULL;
    ASSERT_EQ(re_program_load(NULL,
        text("rule \"Bad\" { when exists Customer.Active then Result = 1; }"),
        NULL, &program), RE_STATUS_PARSE_ERROR);
    ASSERT_EQ(re_program_load(NULL,
        text("rule \"Bad\" { when exists (Customer.Active == true and Ready == true) then Result = 1; }"),
        NULL, &program), RE_STATUS_NOT_SUPPORTED);
}

TEST(forall_matches_all_scalar_array_members) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_handle_t *array = NULL;
    re_program_t *program = NULL;
    re_value_t item = {RE_VALUE_INT64, {.int64_value = 3}};
    re_value_t result = {RE_VALUE_NONE, {0}};
    ASSERT_EQ(re_value_create_array(facts, &array), RE_STATUS_OK);
    ASSERT_EQ(re_value_array_append(array, &item), RE_STATUS_OK);
    item.as.int64_value = 5;
    ASSERT_EQ(re_value_array_append(array, &item), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set_value(facts, text("Values"), array), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text("rule \"All\" { when forall Values >= 3 then Result = 1; }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    program = NULL;
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("Result"), &result), RE_STATUS_OK);
    ASSERT_EQ(result.as.int64_value, 1);
    re_value_destroy(array); re_facts_destroy(facts); re_engine_destroy(engine);
}

TEST(forall_nonmatching_and_empty_arrays_do_not_fire) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_handle_t *array = NULL;
    re_program_t *program = NULL;
    re_value_t item = {RE_VALUE_INT64, {.int64_value = 2}};
    re_value_t result = {RE_VALUE_NONE, {0}};
    ASSERT_EQ(re_value_create_array(facts, &array), RE_STATUS_OK);
    ASSERT_EQ(re_value_array_append(array, &item), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set_value(facts, text("Values"), array), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text("rule \"All\" { when forall Values >= 3 then Result = 1; }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("Result"), &result), RE_STATUS_NOT_FOUND);
    re_value_destroy(array); array = NULL;
    ASSERT_EQ(re_value_create_array(facts, &array), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set_value(facts, text("Values"), array), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text("rule \"Empty\" { when forall Values >= 3 then EmptyResult = 1; }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    program = NULL;
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("EmptyResult"), &result), RE_STATUS_OK);
    re_value_destroy(array); re_facts_destroy(facts); re_engine_destroy(engine);
}

TEST(forall_rejects_malformed_and_non_array_values) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_value_t scalar = {RE_VALUE_INT64, {.int64_value = 3}};
    ASSERT_EQ(re_program_load(NULL, text("rule \"Bad\" { when forall Values >= 3 then Result = 1; }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    program = NULL;
    ASSERT_EQ(re_facts_set(facts, text("Values"), &scalar), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_INVALID_ARGUMENT);
    program = NULL;
    ASSERT_EQ(re_program_load(NULL, text("rule \"Bad\" { when forall (Values >= 3) then Result = 1; }"), NULL, &program), RE_STATUS_NOT_SUPPORTED);
    re_facts_destroy(facts); re_engine_destroy(engine);
}

TEST(forall_resolves_nested_array_path_and_rejects_nested_members) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_handle_t *customer = NULL;
    re_value_handle_t *values = NULL;
    re_value_handle_t *nested = NULL;
    re_value_handle_t *bad_customer = NULL;
    re_value_t item = {RE_VALUE_INT64, {.int64_value = 4}};
    re_value_t result = {RE_VALUE_NONE, {0}};
    re_program_t *program = NULL;
    ASSERT_EQ(re_value_create_object(facts, &customer), RE_STATUS_OK);
    ASSERT_EQ(re_value_create_array(facts, &values), RE_STATUS_OK);
    ASSERT_EQ(re_value_array_append(values, &item), RE_STATUS_OK);
    ASSERT_EQ(re_value_object_set_value(customer, text("Values"), values), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set_value(facts, text("Customer"), customer), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text("rule \"Nested\" { when forall Customer.Values >= 4 then Result = 1; }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    program = NULL;
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("Result"), &result), RE_STATUS_OK);
    ASSERT_EQ(re_value_create_array(facts, &nested), RE_STATUS_OK);
    ASSERT_EQ(re_value_array_append_value(values, nested), RE_STATUS_OK);
    ASSERT_EQ(re_value_create_object(facts, &bad_customer), RE_STATUS_OK);
    ASSERT_EQ(re_value_object_set_value(bad_customer, text("Values"), values), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set_value(facts, text("Customer"), bad_customer), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_INVALID_ARGUMENT);
    re_value_destroy(bad_customer); re_value_destroy(nested); re_value_destroy(values); re_value_destroy(customer);
    re_facts_destroy(facts); re_engine_destroy(engine);
}

TEST(compilation_is_deterministic_and_retains_typed_terms) {
    const char *source = "defmodule Sales { export: all; } rule \"Sales::VIP\"(customer) salience 7 { when customer.Total > 10 and Ready == true then Discount = 1; }";
    re_program_t *first = NULL;
    re_program_t *second = NULL;
    ASSERT_EQ(re_program_load(NULL, text(source), NULL, &first), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text(source), NULL, &second), RE_STATUS_OK);
    ASSERT_NOT_NULL(first->ir);
    ASSERT_EQ(re_ir_validate(first->ir), RE_STATUS_OK);
    ASSERT_EQ(first->ir->rule_count, 1u);
    ASSERT_EQ(first->ir->module_count, 1u);
    ASSERT_EQ(first->ir->rules[0].id, second->ir->rules[0].id);
    ASSERT_EQ(first->ir->rules[0].condition, 0u);
    ASSERT_EQ(first->ir->terms[0].kind, RE_IR_TERM_FACT);
    ASSERT_EQ(first->ir->terms[1].kind, RE_IR_TERM_INT64);
    ASSERT_EQ(first->ir->terms[2].kind, RE_IR_TERM_FACT);
    ASSERT_EQ(first->ir->terms[3].kind, RE_IR_TERM_BOOL);
    ASSERT_TRUE(first->ir->actions[0].target < first->ir->term_count);
    ASSERT_TRUE(first->ir->source_size == strlen(source));
    ASSERT_TRUE(first->ir->spans[0].start < first->ir->spans[0].end);
    re_program_destroy(first);
    re_program_destroy(second);
}

TEST(validation_rejects_bad_indices_and_truncated_tables) {
    re_program_t *program = NULL;
    ASSERT_EQ(re_program_load(NULL, text("rule \"R\" { when true then X = 1; }"), NULL, &program), RE_STATUS_OK);
    program->ir->rules[0].condition = program->ir->expr_count + 1u;
    ASSERT_EQ(re_ir_validate(program->ir), RE_STATUS_INVALID_ARGUMENT);
    re_program_destroy(program);
}

TEST(validation_rejects_unknown_ir_kinds) {
    re_program_t *program = NULL;
    ASSERT_EQ(re_program_load(NULL, text("rule \"R\" { when true then X = 1; }"), NULL, &program), RE_STATUS_OK);
    program->ir->exprs[0].kind = (re_expr_kind_t)99;
    ASSERT_EQ(re_ir_validate(program->ir), RE_STATUS_INVALID_ARGUMENT);
    program->ir->exprs[0].kind = RE_EXPR_TRUE;
    program->ir->terms[0].kind = (re_ir_term_kind_t)99;
    ASSERT_EQ(re_ir_validate(program->ir), RE_STATUS_INVALID_ARGUMENT);
    re_program_destroy(program);
}

TEST(install_rejects_invalid_ir_without_replacing_existing_program) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_program_t *good = NULL;
    re_program_t *bad = NULL;
    ASSERT_EQ(re_program_load(NULL, text("rule \"Good\" { when true then X = 1; }"), NULL, &good), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, good), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text("rule \"Bad\" { when true then X = 1; }"), NULL, &bad), RE_STATUS_OK);
    bad->ir->rules[0].condition = bad->ir->term_count + 1u;
    ASSERT_EQ(re_engine_install(engine, bad), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_engine_run(engine, NULL, NULL, NULL), RE_STATUS_INVALID_ARGUMENT);
    re_program_destroy(bad);
    re_engine_destroy(engine);
}

TEST(forward_execution_uses_immutable_ir_after_parser_data_mutation) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_value_t enabled = {RE_VALUE_BOOL, {.boolean = 1}};
    re_value_t result = {RE_VALUE_NONE, {0}};

    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_facts_set(facts, text("Enabled"), &enabled), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text("rule \"Immutable\" { when Enabled == true then Result = 42; }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);

    program->rules[0].condition->left.fact_name[0] = 'X';
    program->rules[0].actions[0].name[0] = 'X';
    re_free(&program->allocator, program->rules[0].actions[0].value.fact_name);
    program->rules[0].actions[0].value.fact_name = NULL;
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("Result"), &result), RE_STATUS_OK);
    ASSERT_EQ(result.type, RE_VALUE_INT64);
    ASSERT_EQ(result.as.int64_value, 42);

    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(forward_self_recursive_goal_returns_limit) {
    ASSERT_EQ(run_source("rule \"Self\" { when goal(\"Self\") then Result = 1; }",
                        "Result", NULL), RE_STATUS_LIMIT);
}

TEST(forward_mutually_recursive_goal_returns_limit) {
    ASSERT_EQ(run_source(
        "rule \"A\" { when goal(\"B\") then Result = 1; }"
        "rule \"B\" { when goal(\"A\") then Other = 1; }",
        "Result", NULL), RE_STATUS_LIMIT);
}

TEST(forward_goal_chain_is_bounded) {
    ASSERT_EQ(run_source(
        "rule \"C\" { when true then Base = 1; }"
        "rule \"B\" { when goal(\"C\") then Other = 1; }"
        "rule \"A\" { when goal(\"B\") then Result = 1; }",
        "Result", NULL), RE_STATUS_OK);
}

TEST(forward_goal_considers_later_same_name_rule) {
    re_value_t value = {RE_VALUE_NONE, {0}};
    ASSERT_EQ(run_source(
        "rule \"Base\" { when false then First = 1; }"
        "rule \"Base\" { when true then Second = 2; }"
        "rule \"Top\" { when goal(\"Base\") then Result = 3; }",
        "Result", &value), RE_STATUS_OK);
    ASSERT_EQ(value.type, RE_VALUE_INT64);
    ASSERT_EQ(value.as.int64_value, 3);
}

TEST(forward_goal_skips_cyclic_candidate_before_later_success) {
    re_value_t value = {RE_VALUE_NONE, {0}};
    ASSERT_EQ(run_source(
        "rule \"Base\" { when goal(\"Base\") then Recursive = 1; }"
        "rule \"Base\" { when true then Ready = 1; }"
        "rule \"Top\" { when goal(\"Base\") then Result = 3; }",
        "Result", &value), RE_STATUS_OK);
    ASSERT_EQ(value.type, RE_VALUE_INT64);
    ASSERT_EQ(value.as.int64_value, 3);
}

TEST(compilation_retains_array_terms_and_validates_membership_operands) {
    re_program_t *program = NULL;
    ASSERT_EQ(re_program_load(NULL,
        text("rule \"In\" { when Value in [1, \"one\", true] then Result = 1; }"),
        NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(program->ir->terms[1].kind, RE_IR_TERM_ARRAY);
    ASSERT_EQ(program->ir->terms[1].argument_count, 3u);
    ASSERT_EQ(re_ir_validate(program->ir), RE_STATUS_OK);
    program->ir->terms[1].argument_indices[0] = program->ir->term_count;
    ASSERT_EQ(re_ir_validate(program->ir), RE_STATUS_INVALID_ARGUMENT);
    re_program_destroy(program);
}

TEST(ir_validation_rejects_malformed_array_membership_and_actions) {
    re_program_t *program = NULL;
    re_ir_expr_t *expr;
    re_ir_term_t *array;
    ASSERT_EQ(re_program_load(NULL, text("rule \"R\" { when Value in [1] then Result = 1; }"), NULL, &program), RE_STATUS_OK);
    expr = &program->ir->exprs[0];
    array = &program->ir->terms[expr->right];
    array->argument_count = 0u;
    ASSERT_EQ(re_ir_validate(program->ir), RE_STATUS_INVALID_ARGUMENT);
    array->argument_count = 1u;
    program->ir->terms[array->argument_indices[0]].kind = RE_IR_TERM_FACT;
    ASSERT_EQ(re_ir_validate(program->ir), RE_STATUS_INVALID_ARGUMENT);
    program->ir->terms[array->argument_indices[0]].kind = RE_IR_TERM_INT64;
    expr->right = program->ir->actions[0].value;
    ASSERT_EQ(re_ir_validate(program->ir), RE_STATUS_INVALID_ARGUMENT);
    expr->right = (size_t)(array - program->ir->terms);
    program->ir->actions[0].target = expr->right;
    ASSERT_EQ(re_ir_validate(program->ir), RE_STATUS_INVALID_ARGUMENT);
    re_program_destroy(program);
}

TEST_MAIN_BEGIN()
    RUN_TEST(exists_matches_present_flat_fact);
    RUN_TEST(exists_absent_fact_does_not_fire);
    RUN_TEST(exists_nonmatching_fact_does_not_fire);
    RUN_TEST(exists_rejects_malformed_and_compound_shapes);
    RUN_TEST(forall_matches_all_scalar_array_members);
    RUN_TEST(forall_nonmatching_and_empty_arrays_do_not_fire);
    RUN_TEST(forall_rejects_malformed_and_non_array_values);
    RUN_TEST(forall_resolves_nested_array_path_and_rejects_nested_members);
    RUN_TEST(compilation_is_deterministic_and_retains_typed_terms);
    RUN_TEST(validation_rejects_bad_indices_and_truncated_tables);
    RUN_TEST(validation_rejects_unknown_ir_kinds);
    RUN_TEST(install_rejects_invalid_ir_without_replacing_existing_program);
    RUN_TEST(forward_execution_uses_immutable_ir_after_parser_data_mutation);
    RUN_TEST(forward_self_recursive_goal_returns_limit);
    RUN_TEST(forward_mutually_recursive_goal_returns_limit);
    RUN_TEST(forward_goal_chain_is_bounded);
    RUN_TEST(forward_goal_considers_later_same_name_rule);
    RUN_TEST(forward_goal_skips_cyclic_candidate_before_later_success);
    RUN_TEST(compilation_retains_array_terms_and_validates_membership_operands);
    RUN_TEST(ir_validation_rejects_malformed_array_membership_and_actions);
TEST_MAIN_END()
