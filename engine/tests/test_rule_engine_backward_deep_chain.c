#include "test_framework.h"
#include "../src/rule_engine/rule_engine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static re_string_t text(const char *value) {
    re_string_t result = {value, strlen(value)};
    return result;
}

TEST(machine_path_proves_deep_generated_chain) {
    enum { chain_length = 1023, source_capacity = chain_length * 80 };
    char *source = (char *)malloc(source_capacity);
    size_t used = 0u;
    int index;
    re_engine_t *engine;
    re_facts_t *facts;
    re_program_t *program = NULL;
    re_query_t *query = NULL;
    re_proof_t *proof = NULL;
    re_query_options_t options = {sizeof(options), (size_t)chain_length + 1u, 1u, 0u, 0u};

    ASSERT_TRUE(source != NULL);
    for (index = chain_length - 1; index >= 0; --index) {
        int written;
        if (index == chain_length - 1)
            written = snprintf(source + used, source_capacity - used,
                               "rule \"G%d\" { when true then D = true; }", index);
        else
            written = snprintf(source + used, source_capacity - used,
                               "rule \"G%d\" { when goal(\"G%d\") then D = true; }",
                               index, index + 1);
        ASSERT_TRUE(written > 0 && (size_t)written < source_capacity - used);
        used += (size_t)written;
    }

    engine = re_engine_create(NULL, NULL);
    facts = re_facts_create(NULL, NULL);
    ASSERT_TRUE(engine != NULL && facts != NULL);
    ASSERT_EQ(re_program_load(NULL, text(source), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("G0"), &options, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    ASSERT_EQ(re_query_solution_count(query), 1u);
    ASSERT_EQ(re_query_next(query, &proof), RE_STATUS_OK);
    ASSERT_EQ(re_proof_trace_count(proof), (size_t)chain_length);

    re_proof_destroy(proof);
    re_query_destroy(query);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
    free(source);
}

TEST_MAIN_BEGIN()
    RUN_TEST(machine_path_proves_deep_generated_chain);
TEST_MAIN_END()
