#include "test_framework.h"
#include "../src/rule_engine/re_internal.h"
#include <stdlib.h>

static re_string_t text(const char *value) {
    return (re_string_t){value, strlen(value)};
}

typedef struct alloc_state_t {
    size_t calls;
    size_t fail_at;
} alloc_state_t;

static void *test_alloc(void *context, size_t size) {
    alloc_state_t *state = (alloc_state_t *)context;
    ++state->calls;
    return state->calls == state->fail_at ? NULL : malloc(size);
}

static void *test_realloc(void *context, void *memory, size_t size) {
    alloc_state_t *state = (alloc_state_t *)context;
    ++state->calls;
    return state->calls == state->fail_at ? NULL : realloc(memory, size);
}

static void test_free(void *context, void *memory) {
    (void)context;
    free(memory);
}

TEST(forall_mixed_array_does_not_match) {
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_value_handle_t *array = NULL;
    re_program_t *program = NULL;
    re_value_t item = {RE_VALUE_INT64, {.int64_value = 4}};
    re_value_t result = {RE_VALUE_NONE, {0}};

    ASSERT_EQ(re_value_create_array(facts, &array), RE_STATUS_OK);
    ASSERT_EQ(re_value_array_append(array, &item), RE_STATUS_OK);
    item.as.int64_value = 2;
    ASSERT_EQ(re_value_array_append(array, &item), RE_STATUS_OK);
    item.as.int64_value = 4;
    ASSERT_EQ(re_value_array_append(array, &item), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set_value(facts, text("Values"), array), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text("rule \"Mixed\" { when forall Values >= 3 then Result = 1; }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    program = NULL;
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("Result"), &result), RE_STATUS_NOT_FOUND);
    re_value_destroy(array); re_facts_destroy(facts); re_engine_destroy(engine);
}

TEST(forall_absent_path_does_not_match) {
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_program_t *program = NULL;
    re_value_t result = {RE_VALUE_NONE, {0}};

    ASSERT_EQ(re_program_load(NULL, text("rule \"Absent\" { when forall Missing.Values >= 3 then Result = 1; }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    program = NULL;
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("Result"), &result), RE_STATUS_NOT_FOUND);
    re_facts_destroy(facts); re_engine_destroy(engine);
}

TEST(forall_element_limit_is_enforced) {
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_handle_t *array = NULL;
    re_value_t item = {RE_VALUE_INT64, {.int64_value = 3}};
    re_value_t result = {RE_VALUE_NONE, {0}};
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_program_t *program = NULL;
    size_t index;

    ASSERT_NOT_NULL(facts);
    ASSERT_NOT_NULL(engine);
    ASSERT_EQ(re_value_create_array(facts, &array), RE_STATUS_OK);
    for (index = 0u; index < 1024u; ++index)
        ASSERT_EQ(re_value_array_append(array, &item), RE_STATUS_OK);
    ASSERT_EQ(re_value_array_append(array, &item), RE_STATUS_LIMIT);
    ASSERT_EQ(re_facts_set_value(facts, text("Values"), array), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL,
        text("rule \"All\" { when forall Values >= 3 then Result = 1; }"),
        NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    program = NULL;
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("Result"), &result), RE_STATUS_OK);
    ASSERT_EQ(result.as.int64_value, 1);
    re_value_destroy(array);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(forall_depth_limit_is_enforced_before_evaluation) {
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_handle_t *nested = NULL;
    re_value_handle_t *parent = NULL;
    size_t depth;

    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_value_create_array(facts, &nested), RE_STATUS_OK);
    for (depth = 0u; depth < 64u; ++depth) {
        ASSERT_EQ(re_value_create_array(facts, &parent), RE_STATUS_OK);
        ASSERT_EQ(re_value_array_append_value(parent, nested), RE_STATUS_OK);
        re_value_destroy(nested);
        nested = parent;
        parent = NULL;
    }
    ASSERT_EQ(re_value_create_array(facts, &parent), RE_STATUS_OK);
    ASSERT_EQ(re_value_array_append_value(parent, nested), RE_STATUS_LIMIT);
    re_value_destroy(parent);
    re_value_destroy(nested);
    re_facts_destroy(facts);
}

TEST(forall_evaluator_reports_allocator_failure) {
    alloc_state_t state = {0u, 0u};
    re_allocator_t allocator = {&state, test_alloc, test_realloc, test_free};
    re_engine_t *engine = re_engine_create(&allocator, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_handle_t *array = NULL;
    re_value_t item = {RE_VALUE_INT64, {.int64_value = 3}};
    re_program_t *program = NULL;
    int matched = 0;

    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_value_create_array(facts, &array), RE_STATUS_OK);
    ASSERT_EQ(re_value_array_append(array, &item), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set_value(facts, text("Values"), array), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL,
        text("rule \"All\" { when forall Values >= 3 then Result = 1; }"),
        NULL, &program), RE_STATUS_OK);
    state.fail_at = state.calls + 1u;
    ASSERT_EQ(re_ir_match_rule(engine, facts, program->ir, 0u, &matched),
              RE_STATUS_OUT_OF_MEMORY);
    state.fail_at = 0u;
    ASSERT_EQ(re_ir_match_rule(engine, facts, program->ir, 0u, &matched),
              RE_STATUS_OK);
    ASSERT_TRUE(matched);
    re_program_destroy(program);
    re_value_destroy(array);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST_MAIN_BEGIN()
    RUN_TEST(forall_mixed_array_does_not_match);
    RUN_TEST(forall_absent_path_does_not_match);
    RUN_TEST(forall_element_limit_is_enforced);
    RUN_TEST(forall_depth_limit_is_enforced_before_evaluation);
    RUN_TEST(forall_evaluator_reports_allocator_failure);
TEST_MAIN_END()
