#include <rule_engine/rule_engine.h>

#include <stdio.h>
#include <string.h>

enum { STRESS_ITERATIONS = 64 };

static re_string_t text(const char *data) {
    re_string_t result = {data, strlen(data)};
    return result;
}

int main(void) {
    const char *source =
        "rule \"A\" { when Ready == true then A = 1; }"
        "rule \"B\" { when Ready == true then B = 1; }"
        "rule \"C\" { when Ready == true then C = 1; }";
    re_value_t ready = {RE_VALUE_BOOL, {.boolean = 1}};
    re_concurrency_options_t options = {
        sizeof(options), RE_ABI_VERSION_MAJOR, 4u, 0u};
    unsigned int iteration;
    for (iteration = 0u; iteration < STRESS_ITERATIONS; ++iteration) {
        re_engine_t *engine = re_engine_create(NULL, NULL);
        re_facts_t *facts = re_facts_create(NULL, NULL);
        re_program_t *program = NULL;
        re_executor_t *executor = NULL;
        if (engine == NULL || facts == NULL ||
            re_program_load(NULL, text(source), NULL, &program) != RE_STATUS_OK ||
            re_engine_install(engine, program) != RE_STATUS_OK ||
            re_facts_set(facts, text("Ready"), &ready) != RE_STATUS_OK ||
            re_engine_executor_create(engine, &options, &executor) != RE_STATUS_OK ||
            re_engine_run(engine, facts, NULL, NULL) != RE_STATUS_OK) {
            re_executor_destroy(executor);
            re_facts_destroy(facts);
            re_engine_destroy(engine);
            return 1;
        }
        re_executor_destroy(executor);
        re_facts_destroy(facts);
        re_engine_destroy(engine);
    }
    puts("executor stress: 64 bounded iterations passed");
    return 0;
}
