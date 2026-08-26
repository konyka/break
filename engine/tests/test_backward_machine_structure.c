#include "test_framework.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

TEST_MAIN_BEGIN()
    RUN_TEST(machine_source_has_no_legacy_evaluator_symbols);
    RUN_TEST(production_query_path_routes_through_unified_machine);
TEST_MAIN_END()
