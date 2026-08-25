#include <rule_engine/rule_engine.h>

#include <stdio.h>
#include <string.h>
#include <time.h>

enum {
    COLD_LOAD_RUNS = 100,
    WARM_EVAL_RUNS = 10000
};

typedef struct fact_spec_t {
    const char *name;
    re_value_t value;
} fact_spec_t;

typedef struct bench_case_t {
    const char *name;
    const char *source;
    const fact_spec_t *facts;
    size_t fact_count;
} bench_case_t;

typedef struct callback_state_t {
    size_t fired;
} callback_state_t;

static const char *SPARSE_SOURCE =
    "rule \"SparseMatch\" { when Customer.Active == true then Customer.Flag = 1; }\n"
    "rule \"SparseMissing\" { when Customer.Missing > 100 then Customer.Flag = 2; }";

static const char *DENSE_SOURCE =
    "rule \"DenseA\" { when Customer.Active == true then Customer.FlagA = 1; }\n"
    "rule \"DenseB\" { when Customer.Active != false then Customer.FlagB = 1; }\n"
    "rule \"DenseC\" { when Customer.Active == true then Customer.FlagC = 1; }\n"
    "rule \"DenseD\" { when Customer.Missing == true then Customer.FlagD = 1; }\n"
    "rule \"DenseE\" { when Customer.Active == true then Customer.FlagE = 1; }";

static const fact_spec_t SPARSE_FACTS[] = {
    {"Customer.Active", {RE_VALUE_BOOL, {.boolean = 1}}}
};

static const fact_spec_t DENSE_FACTS[] = {
    {"Customer.Active", {RE_VALUE_BOOL, {.boolean = 1}}},
    {"Customer.RegionActive", {RE_VALUE_BOOL, {.boolean = 1}}},
    {"Customer.FeatureActive", {RE_VALUE_BOOL, {.boolean = 1}}},
    {"Customer.AnotherActive", {RE_VALUE_BOOL, {.boolean = 1}}}
};

static re_status_t count_action(re_engine_t *engine, re_facts_t *facts,
                                const re_rule_event_t *event, void *context) {
    callback_state_t *state = (callback_state_t *)context;
    (void)engine;
    (void)facts;
    (void)event;
    state->fired++;
    return RE_STATUS_OK;
}

static double elapsed_seconds(clock_t start, clock_t end) {
    return (double)(end - start) / (double)CLOCKS_PER_SEC;
}

static int run_cold_case(const bench_case_t *test_case) {
    size_t run;
    clock_t start = clock();
    for (run = 0u; run < COLD_LOAD_RUNS; ++run) {
        re_program_t *program = NULL;
        re_status_t status = re_program_load(NULL,
            (re_string_t){test_case->source, strlen(test_case->source)}, NULL, &program);
        if (status != RE_STATUS_OK || program == NULL) {
            fprintf(stderr, "%s cold load failed: %d\n", test_case->name, (int)status);
            re_program_destroy(program);
            return 0;
        }
        re_program_destroy(program);
    }
    printf("%s cold_load elapsed_seconds=%.9f run_count=%u source_bytes=%zu\n",
           test_case->name, elapsed_seconds(start, clock()), COLD_LOAD_RUNS,
           strlen(test_case->source));
    return 1;
}

static int run_warm_case(const bench_case_t *test_case) {
    size_t index;
    size_t run;
    callback_state_t state = {0u};
    re_callbacks_t callbacks = {count_action, &state};
    re_program_t *program = NULL;
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    clock_t start;

    if (engine == NULL || facts == NULL ||
        re_program_load(NULL, (re_string_t){test_case->source, strlen(test_case->source)},
                        NULL, &program) != RE_STATUS_OK || program == NULL) {
        fprintf(stderr, "%s warm setup failed\n", test_case->name);
        re_program_destroy(program);
        re_facts_destroy(facts);
        re_engine_destroy(engine);
        return 0;
    }
    if (re_engine_install(engine, program) != RE_STATUS_OK) {
        fprintf(stderr, "%s warm install failed\n", test_case->name);
        re_program_destroy(program);
        re_facts_destroy(facts);
        re_engine_destroy(engine);
        return 0;
    }
    for (index = 0u; index < test_case->fact_count; ++index) {
        if (re_facts_set(facts, (re_string_t){test_case->facts[index].name,
                                              strlen(test_case->facts[index].name)},
                         &test_case->facts[index].value) != RE_STATUS_OK) {
            fprintf(stderr, "%s fact setup failed\n", test_case->name);
            re_facts_destroy(facts);
            re_engine_destroy(engine);
            return 0;
        }
    }

    start = clock();
    for (run = 0u; run < WARM_EVAL_RUNS; ++run) {
        if (re_engine_run(engine, facts, NULL, &callbacks) != RE_STATUS_OK) {
            fprintf(stderr, "%s warm evaluation failed\n", test_case->name);
            re_facts_destroy(facts);
            re_engine_destroy(engine);
            return 0;
        }
    }
    printf("%s warm_eval elapsed_seconds=%.9f run_count=%u fired_count=%zu fact_count=%zu\n",
           test_case->name, elapsed_seconds(start, clock()), WARM_EVAL_RUNS,
           state.fired, test_case->fact_count);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
    return 1;
}

int main(void) {
    const bench_case_t cases[] = {
        {"sparse", SPARSE_SOURCE, SPARSE_FACTS, sizeof(SPARSE_FACTS) / sizeof(SPARSE_FACTS[0])},
        {"dense", DENSE_SOURCE, DENSE_FACTS, sizeof(DENSE_FACTS) / sizeof(DENSE_FACTS[0])}
    };
    size_t index;
    int success = 1;

    puts("rule_engine_bench baseline; clock() CPU elapsed time; compiler/build context is external");
    for (index = 0u; index < sizeof(cases) / sizeof(cases[0]); ++index) {
        success = run_cold_case(&cases[index]) && success;
        success = run_warm_case(&cases[index]) && success;
    }
    return success ? 0 : 1;
}
