#include <rule_engine/rule_engine.h>

#include <stdio.h>
#include <string.h>

enum { STRESS_ITERATIONS = 64 };

static re_string_t text(const char *data) {
    re_string_t result = {data, strlen(data)};
    return result;
}

typedef struct busy_probe_t {
    re_status_t run_reentry;
    re_status_t txn_begin;
    re_status_t reset;
    int fired;
} busy_probe_t;

static re_status_t busy_action(re_engine_t *engine, re_facts_t *facts,
                               const re_rule_event_t *event, void *context) {
    busy_probe_t *probe = context;
    re_fact_txn_t *txn = NULL;
    (void)event;
    probe->fired++;
    probe->run_reentry = re_engine_run(engine, facts, NULL, NULL);
    probe->txn_begin = re_facts_begin(facts, &txn);
    if (probe->txn_begin == RE_STATUS_OK) re_facts_rollback(txn);
    probe->reset = re_engine_reset_with_deffacts(engine, facts);
    return RE_STATUS_OK;
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
    /* Busy boundary with workers installed: while re_engine_run is active
     * (observed from the action callback, which the engine invokes on the
     * engine thread after the read-only worker matching has joined), a
     * conflicting host mutation attempt must report RE_STATUS_BUSY. The
     * attempts are made FROM the callback itself, so everything happens on
     * the engine thread and no data race is possible. */
    for (iteration = 0u; iteration < STRESS_ITERATIONS; ++iteration) {
        re_engine_t *engine = re_engine_create(NULL, NULL);
        re_facts_t *facts = re_facts_create(NULL, NULL);
        re_program_t *program = NULL;
        re_executor_t *executor = NULL;
        busy_probe_t probe;
        re_callbacks_t callbacks;
        probe.fired = 0;
        probe.run_reentry = RE_STATUS_OK;
        probe.txn_begin = RE_STATUS_OK;
        probe.reset = RE_STATUS_OK;
        callbacks.action = busy_action;
        callbacks.context = &probe;
        if (engine == NULL || facts == NULL ||
            re_program_load(NULL, text(source), NULL, &program) != RE_STATUS_OK ||
            re_engine_install(engine, program) != RE_STATUS_OK ||
            re_facts_set(facts, text("Ready"), &ready) != RE_STATUS_OK ||
            re_engine_executor_create(engine, &options, &executor) != RE_STATUS_OK ||
            re_engine_run(engine, facts, NULL, &callbacks) != RE_STATUS_OK ||
            probe.fired != 3 ||
            probe.run_reentry != RE_STATUS_BUSY ||
            probe.txn_begin != RE_STATUS_BUSY ||
            probe.reset != RE_STATUS_BUSY ||
            /* The busy flags release with the run; the handles stay usable. */
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
    puts("executor stress: 64 busy-boundary iterations passed");
    return 0;
}
