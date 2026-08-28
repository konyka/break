#include "test_framework.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/rule_engine/backward_machine_bind.h"
#include "../src/rule_engine/re_internal.h"

TEST(machine_source_has_no_legacy_evaluator_symbols) {
    const char *paths[] = {
        TEST_SOURCE_ROOT "/src/rule_engine/backward_machine_goal.c",
        TEST_SOURCE_ROOT "/src/rule_engine/backward_machine_goal.h",
        TEST_SOURCE_ROOT "/src/rule_engine/backward.c",
        TEST_SOURCE_ROOT "/src/rule_engine/query.c"
    };
    size_t index;
    for (index = 0u; index < sizeof(paths) / sizeof(paths[0]); ++index) {
        FILE *source = fopen(paths[index], "rb");
        char *buffer;
        size_t count;
        long length;
        ASSERT_NOT_NULL(source);
        ASSERT_EQ(fseek(source, 0L, SEEK_END), 0);
        length = ftell(source);
        ASSERT_TRUE(length >= 0L);
        ASSERT_EQ(fseek(source, 0L, SEEK_SET), 0);
        buffer = (char *)malloc((size_t)length + 1u);
        ASSERT_NOT_NULL(buffer);
        count = fread(buffer, 1u, (size_t)length, source);
        buffer[count] = '\0';
        fclose(source);
        ASSERT_TRUE(strstr(buffer, "legacy_operand_value") == NULL);
        ASSERT_TRUE(strstr(buffer, "legacy_condition_matches") == NULL);
        ASSERT_TRUE(strstr(buffer, "re_operand_resolve") == NULL);
        ASSERT_TRUE(strstr(buffer, "machine_prove_goal") == NULL);
        ASSERT_TRUE(strstr(buffer, "general_machine_goal_run") == NULL);
        ASSERT_TRUE(strstr(buffer, "backward_goal_step") == NULL);
        if (strstr(paths[index], "backward.c") != NULL) {
            ASSERT_TRUE(strstr(buffer, "machine_operand_goal") == NULL);
            ASSERT_TRUE(strstr(buffer, "machine_goal_executor(query") == NULL);
        }
        free(buffer);
    }
}

TEST(production_query_path_routes_through_unified_machine) {
    FILE *source = fopen(TEST_SOURCE_ROOT "/src/rule_engine/query.c", "rb");
    char buffer[4096];
    size_t count;
    ASSERT_NOT_NULL(source);
    count = fread(buffer, 1u, sizeof(buffer) - 1u, source);
    buffer[count] = '\0';
    fclose(source);
    ASSERT_TRUE(strstr(buffer, "re_backward_machine_run") != NULL);
}

TEST(production_parameterized_query_routes_through_machine) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_query_t *query = NULL;
    re_query_options_t options = {sizeof(options), 4u, 1u, 0u, 0u};
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_program_load(NULL, (re_string_t){
        "rule \"Lookup\"(Key) { when Key == \"alice\" then Seen = 1; }"
        "rule \"Top\" { when goal(\"Lookup\", \"alice\") then Done = 1; }",
        sizeof("rule \"Lookup\"(Key) { when Key == \"alice\" then Seen = 1; }"
               "rule \"Top\" { when goal(\"Lookup\", \"alice\") then Done = 1; }") - 1u},
        NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, (re_string_t){"Top", 3u},
                                       &options, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    ASSERT_EQ(re_query_solution_count(query), 1u);
    re_query_destroy(query);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(direct_parameter_machine_enumerates_terminal_alternatives) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_query_t *query = NULL;
    re_backward_machine_bind_result_t result;
    re_query_options_t options = {sizeof(options), 4u, 4u, 0u, 0u};
    re_operand_t argument;
    const char *source = "rule \"Pick\"(Value) { when true then A = 1; }"
                         "rule \"Pick\"(Value) { when true then B = 2; }";
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_program_load(NULL, (re_string_t){source, strlen(source)}, NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    query = (re_query_t *)calloc(1u, sizeof(*query));
    ASSERT_NOT_NULL(query);
    query->allocator = engine->allocator;
    query->engine = engine;
    query->facts = facts;
    query->max_depth = options.max_depth;
    query->max_solutions = options.max_solutions;
    memset(&argument, 0, sizeof(argument));
    argument.kind = RE_OPERAND_LITERAL;
    argument.value.type = RE_VALUE_INT64;
    argument.value.as.int64_value = 7;
    ASSERT_EQ(re_backward_machine_bind_run(query, (re_string_t){"Pick", 4u},
                                           &argument, 1u, &result), RE_STATUS_OK);
    ASSERT_EQ(result.solution_count, 2u);
    ASSERT_EQ(result.last_parent_id, 0u);
    re_free(&query->allocator, query);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST_MAIN_BEGIN()
    RUN_TEST(machine_source_has_no_legacy_evaluator_symbols);
    RUN_TEST(production_query_path_routes_through_unified_machine);
    RUN_TEST(production_parameterized_query_routes_through_machine);
    RUN_TEST(direct_parameter_machine_enumerates_terminal_alternatives);
TEST_MAIN_END()
