#include "re_internal.h"

#if defined(RE_ENABLE_C11_PARALLEL)
#include <stdatomic.h>
#include <threads.h>

struct re_executor_t {
    re_allocator_impl_t allocator;
    re_engine_t *engine;
    uint32_t worker_count;
    int running;
};

typedef struct re_match_job_t {
    const re_engine_t *engine;
    const re_facts_t *facts;
    const re_program_t *program;
    unsigned char *matches;
    atomic_size_t next;
    atomic_int failure;
} re_match_job_t;

static int match_worker(void *argument) {
    re_match_job_t *job = argument;
    size_t index;
    while (atomic_load(&job->failure) == RE_STATUS_OK &&
           (index = atomic_fetch_add(&job->next, 1u)) < job->program->rule_count) {
        int matched = 0;
        re_status_t status = re_engine_match_rule(job->engine, job->facts,
                                                   &job->program->rules[index], &matched);
        if (status != RE_STATUS_OK && status != RE_STATUS_NOT_FOUND) {
            int expected = RE_STATUS_OK;
            atomic_compare_exchange_strong(&job->failure, &expected, status);
        }
        job->matches[index] = (unsigned char)(status == RE_STATUS_OK && matched);
    }
    return 0;
}

re_status_t re_executor_match(re_executor_t *executor, const re_engine_t *engine,
                              const re_facts_t *facts, const re_program_t *program,
                              unsigned char *matches) {
    re_match_job_t job;
    thrd_t *workers;
    uint32_t index, started = 0u;
    if (executor->running) return RE_STATUS_BUSY;
    executor->running = 1;
    job.engine = engine; job.facts = facts; job.program = program; job.matches = matches;
    atomic_init(&job.next, 0u); atomic_init(&job.failure, RE_STATUS_OK);
    workers = re_alloc(&executor->allocator, executor->worker_count * sizeof(*workers));
    if (workers == NULL) { executor->running = 0; return RE_STATUS_OUT_OF_MEMORY; }
    for (index = 0u; index < executor->worker_count; ++index) {
        if (thrd_create(&workers[index], match_worker, &job) != thrd_success) break;
        ++started;
    }
    while (started != 0u) thrd_join(workers[--started], NULL);
    re_free(&executor->allocator, workers);
    executor->running = 0;
    return atomic_load(&job.failure);
}

re_status_t re_executor_create_impl(re_engine_t *engine, const re_concurrency_options_t *options,
                                    re_executor_t **out_executor) {
    re_executor_t *executor;
    if (engine == NULL || options == NULL || out_executor == NULL ||
        options->struct_size < sizeof(*options) || options->abi_version != RE_ABI_VERSION_MAJOR ||
        options->worker_count == 0u || engine->executor != NULL) return RE_STATUS_INVALID_ARGUMENT;
    if (engine->running) return RE_STATUS_BUSY;
    *out_executor = NULL;
    executor = re_alloc(&engine->allocator, sizeof(*executor));
    if (executor == NULL) return RE_STATUS_OUT_OF_MEMORY;
    executor->allocator = engine->allocator; executor->engine = engine;
    executor->worker_count = options->worker_count; executor->running = 0;
    engine->executor = executor; *out_executor = executor; return RE_STATUS_OK;
}

void re_executor_destroy_impl(re_executor_t *executor) {
    if (executor == NULL || executor->running) return;
    if (executor->engine != NULL && executor->engine->executor == executor)
        executor->engine->executor = NULL;
    re_free(&executor->allocator, executor);
}
#else
struct re_executor_t { int unused; };
re_status_t re_executor_match(re_executor_t *executor, const re_engine_t *engine,
                              const re_facts_t *facts, const re_program_t *program,
                              unsigned char *matches) {
    (void)executor; (void)engine; (void)facts; (void)program; (void)matches;
    return RE_STATUS_NOT_SUPPORTED;
}
re_status_t re_executor_create_impl(re_engine_t *engine, const re_concurrency_options_t *options,
                                    re_executor_t **out_executor) {
    (void)engine; (void)options; (void)out_executor;
    return RE_STATUS_NOT_SUPPORTED;
}
void re_executor_destroy_impl(re_executor_t *executor) { (void)executor; }
#endif
