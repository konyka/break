#include "test_framework.h"

#include <myui/mycompose/my_compose_internal.h>
#include <myui/mycompose/my_compose_runtime.h>

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define EFFECT_INTENT 2u
#define COMPLETION_INTENT 900u
#define LOG_CAPACITY 16384u

typedef struct TestState {
    uint32_t count;
} TestState;

typedef struct Fixture {
    MyComposeStore *store;
    MyComposeTreeBuilder *builder;
    MyComposeRuntime *runtime;
    MyComposeRuntimeConfig config;
    char log[LOG_CAPACITY];
    uint32_t log_size;
    uint32_t reducer_calls;
    uint32_t view_calls;
    uint32_t stage_calls;
    uint32_t commit_calls;
    uint32_t rollback_calls;
    uint32_t executor_calls;
    uint32_t view_failures;
    uint32_t stage_failures;
    uint32_t view_states[256];
    uint32_t intent_results[256];
    MyComposeEffect effects[256];
    uint8_t effect_payloads[256][MY_COMPOSE_MESSAGE_BYTES];
    bool executor_pending_once;
} Fixture;

static void record(Fixture *fixture, char event) {
    if (fixture->log_size < LOG_CAPACITY) {
        fixture->log[fixture->log_size++] = event;
    }
}

static MyComposeStatus reduce_intent(void *context, const MyComposeIntent *intent,
    const void *current, uint32_t current_size, void *candidate,
    uint32_t *candidate_size, MyComposeEffectBatch *batch) {
    Fixture *fixture = context;
    const TestState *state = current;
    TestState *next = candidate;
    uint32_t value = 0u;
    (void)current_size;
    record(fixture, 'R');
    fixture->intent_results[fixture->reducer_calls] = intent->result;
    fixture->reducer_calls++;
    if (intent->payload_size == sizeof(value)) {
        memcpy(&value, intent->payload, sizeof(value));
    }
    *next = *state;
    *candidate_size = sizeof(*next);
    if (intent->type == COMPLETION_INTENT) return MY_COMPOSE_OK;
    next->count += value;
    if (intent->type == EFFECT_INTENT) {
        return my_compose_effect_batch_append(batch, 500u + value, &value,
            (uint32_t)sizeof(value));
    }
    return MY_COMPOSE_OK;
}

static MyComposeStatus execute_effect(void *context,
    const MyComposeEffect *effect) {
    Fixture *fixture = context;
    uint32_t slot = fixture->executor_calls;
    record(fixture, 'D');
    fixture->effects[slot] = *effect;
    memcpy(fixture->effect_payloads[slot], effect->payload, effect->payload_size);
    fixture->effects[slot].payload = fixture->effect_payloads[slot];
    fixture->executor_calls++;
    if (fixture->executor_pending_once) {
        fixture->executor_pending_once = false;
        return MY_COMPOSE_PENDING;
    }
    return MY_COMPOSE_OK;
}

static MyComposeStatus declare_view(void *context, MyComposeTreeBuilder *builder,
    const void *state, uint32_t state_size) {
    Fixture *fixture = context;
    const TestState *count = state;
    MyComposeNodeHandle root;
    MyComposeNodeHandle child;
    MyComposeNodeDesc desc;
    (void)state_size;
    record(fixture, 'V');
    fixture->view_states[fixture->view_calls] = count->count;
    fixture->view_calls++;
    if (fixture->view_failures > 0u) {
        fixture->view_failures--;
        return MY_COMPOSE_FAILED;
    }
    memset(&desc, 0, sizeof(desc));
    desc.type = "@root";
    if (my_compose_tree_builder_node(builder, &desc, &root) != MY_COMPOSE_OK) {
        return MY_COMPOSE_FAILED;
    }
    desc.parent = root;
    desc.key = "counter";
    desc.type = "label";
    if (my_compose_tree_builder_node(builder, &desc, &child) != MY_COMPOSE_OK) {
        return MY_COMPOSE_FAILED;
    }
    return MY_COMPOSE_OK;
}

static MyComposeStatus sink_stage(void *context, const MyComposeDiff *diff) {
    Fixture *fixture = context;
    (void)diff;
    record(fixture, 'S');
    fixture->stage_calls++;
    if (fixture->builder->state != MY_COMPOSE_BUILD_ENDED) {
        return MY_COMPOSE_CONFLICT;
    }
    if (fixture->stage_failures > 0u) {
        fixture->stage_failures--;
        return MY_COMPOSE_FAILED;
    }
    return MY_COMPOSE_OK;
}

static void sink_commit(void *context) {
    Fixture *fixture = context;
    if (fixture->builder->state == MY_COMPOSE_BUILD_IDLE) record(fixture, 'F');
    record(fixture, 'C');
    fixture->commit_calls++;
}

static void sink_rollback(void *context) {
    Fixture *fixture = context;
    record(fixture, 'B');
    fixture->rollback_calls++;
}

static MyComposeSinkOps make_sink(Fixture *fixture, MyComposeStore *store) {
    MyComposeSinkOps sink;
    memset(&sink, 0, sizeof(sink));
    sink.context = fixture;
    sink.store = store;
    sink.stage = sink_stage;
    sink.commit = sink_commit;
    sink.rollback = sink_rollback;
    return sink;
}

static bool fixture_init(Fixture *fixture) {
    TestState initial = {0u};
    memset(fixture, 0, sizeof(*fixture));
    fixture->store = my_compose_store_create(&initial, (uint32_t)sizeof(initial),
        NULL, fixture, reduce_intent, fixture, execute_effect);
    fixture->builder = my_compose_tree_builder_create();
    if (fixture->store == NULL || fixture->builder == NULL) return false;
    memset(&fixture->config, 0, sizeof(fixture->config));
    fixture->config.store = fixture->store;
    fixture->config.view = declare_view;
    fixture->config.view_context = fixture;
    fixture->config.sink = make_sink(fixture, fixture->store);
    fixture->runtime = my_compose_runtime_create(fixture->builder,
        &fixture->config);
    return fixture->runtime != NULL;
}

static void fixture_destroy(Fixture *fixture) {
    my_compose_runtime_destroy(fixture->runtime);
    my_compose_tree_builder_destroy(fixture->builder);
    my_compose_store_destroy(fixture->store);
    memset(fixture, 0, sizeof(*fixture));
}

static MyComposeStatus dispatch_intent(Fixture *fixture, uint32_t type,
    uint32_t value) {
    MyComposeIntent intent;
    memset(&intent, 0, sizeof(intent));
    intent.type = type;
    intent.payload = (const uint8_t *)&value;
    intent.payload_size = (uint32_t)sizeof(value);
    return my_compose_store_dispatch(fixture->store, &intent);
}

static bool log_is(const Fixture *fixture, const char *expected) {
    return fixture->log_size == strlen(expected) &&
        memcmp(fixture->log, expected, fixture->log_size) == 0;
}

static void clear_log(Fixture *fixture) {
    fixture->log_size = 0u;
}

TEST(runtime_orders_each_state_revision_through_finalize_before_effects) {
    Fixture fixture;
    ASSERT_TRUE(fixture_init(&fixture));
    ASSERT_EQ(my_compose_runtime_pump(fixture.runtime), MY_COMPOSE_OK);
    ASSERT_TRUE(log_is(&fixture, "VSFC"));
    clear_log(&fixture);
    ASSERT_EQ(dispatch_intent(&fixture, EFFECT_INTENT, 3u), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_runtime_pump(fixture.runtime), MY_COMPOSE_OK);
    ASSERT_TRUE(log_is(&fixture, "RVSFCD"));
    ASSERT_EQ(fixture.reducer_calls, 1u);
    ASSERT_EQ(fixture.view_calls, 2u);
    ASSERT_EQ(fixture.executor_calls, 1u);
    ASSERT_EQ(fixture.effects[0].request_id, 1u);
    fixture_destroy(&fixture);
}

TEST(pending_view_reaps_and_retries_without_reducing_or_dispatching) {
    Fixture fixture;
    const TestState *state;
    uint32_t state_size;
    ASSERT_TRUE(fixture_init(&fixture));
    ASSERT_EQ(my_compose_runtime_pump(fixture.runtime), MY_COMPOSE_OK);
    ASSERT_EQ(dispatch_intent(&fixture, EFFECT_INTENT, 1u), MY_COMPOSE_OK);
    ASSERT_EQ(dispatch_intent(&fixture, EFFECT_INTENT, 10u), MY_COMPOSE_OK);
    fixture.view_failures = 1u;
    clear_log(&fixture);
    ASSERT_EQ(my_compose_runtime_pump(fixture.runtime), MY_COMPOSE_FAILED);
    ASSERT_TRUE(log_is(&fixture, "RV"));
    ASSERT_EQ(fixture.reducer_calls, 1u);
    ASSERT_EQ(fixture.executor_calls, 0u);
    ASSERT_EQ(my_compose_store_state(fixture.store, (const void **)&state,
        &state_size), MY_COMPOSE_OK);
    ASSERT_EQ(state->count, 1u);
    ASSERT_EQ(my_compose_store_diagnostics(fixture.store)->pending_intents, 1u);
    clear_log(&fixture);
    ASSERT_EQ(my_compose_runtime_pump(fixture.runtime), MY_COMPOSE_OK);
    ASSERT_TRUE(log_is(&fixture, "VSFCD"));
    ASSERT_EQ(fixture.reducer_calls, 1u);
    ASSERT_EQ(fixture.view_states[fixture.view_calls - 1u], 1u);
    ASSERT_EQ(fixture.executor_calls, 1u);
    ASSERT_EQ(my_compose_store_diagnostics(fixture.store)->pending_intents, 1u);
    clear_log(&fixture);
    ASSERT_EQ(my_compose_runtime_pump(fixture.runtime), MY_COMPOSE_OK);
    ASSERT_TRUE(log_is(&fixture, "RVSFCD"));
    ASSERT_EQ(fixture.reducer_calls, 2u);
    ASSERT_EQ(fixture.executor_calls, 2u);
    fixture_destroy(&fixture);
}

TEST(stage_failure_keeps_state_and_rebuilds_before_dispatch) {
    Fixture fixture;
    ASSERT_TRUE(fixture_init(&fixture));
    ASSERT_EQ(my_compose_runtime_pump(fixture.runtime), MY_COMPOSE_OK);
    ASSERT_EQ(dispatch_intent(&fixture, EFFECT_INTENT, 7u), MY_COMPOSE_OK);
    fixture.stage_failures = 1u;
    clear_log(&fixture);
    ASSERT_EQ(my_compose_runtime_pump(fixture.runtime), MY_COMPOSE_FAILED);
    ASSERT_TRUE(log_is(&fixture, "RVSB"));
    ASSERT_EQ(fixture.executor_calls, 0u);
    clear_log(&fixture);
    ASSERT_EQ(my_compose_runtime_pump(fixture.runtime), MY_COMPOSE_OK);
    ASSERT_TRUE(log_is(&fixture, "VSFCD"));
    ASSERT_EQ(fixture.reducer_calls, 1u);
    ASSERT_EQ(fixture.rollback_calls, 1u);
    ASSERT_EQ(fixture.executor_calls, 1u);
    fixture_destroy(&fixture);
}

TEST(runtime_rejects_sink_from_another_store) {
    Fixture fixture;
    TestState initial = {0u};
    MyComposeStore *other;
    MyComposeRuntimeConfig config;
    ASSERT_TRUE(fixture_init(&fixture));
    other = my_compose_store_create(&initial, (uint32_t)sizeof(initial), NULL,
        &fixture, reduce_intent, &fixture, execute_effect);
    ASSERT_NOT_NULL(other);
    config = fixture.config;
    config.sink.store = other;
    ASSERT_TRUE(my_compose_runtime_create(fixture.builder, &config) == NULL);
    my_compose_store_destroy(other);
    fixture_destroy(&fixture);
}

TEST(runtime_preserves_store_budget_without_repeating_reducer) {
    Fixture fixture;
    ASSERT_TRUE(fixture_init(&fixture));
    ASSERT_EQ(my_compose_runtime_pump(fixture.runtime), MY_COMPOSE_OK);
    for (uint32_t i = 0u; i < 65u; ++i) {
        ASSERT_EQ(dispatch_intent(&fixture, 1u, 1u), i < 64u ?
            MY_COMPOSE_OK : MY_COMPOSE_OVERLOAD);
    }
    ASSERT_EQ(my_compose_runtime_pump(fixture.runtime), MY_COMPOSE_OK);
    ASSERT_EQ(fixture.reducer_calls, 64u);
    ASSERT_EQ(fixture.view_calls, 65u);
    ASSERT_EQ(dispatch_intent(&fixture, 1u, 1u), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_runtime_pump(fixture.runtime), MY_COMPOSE_OK);
    ASSERT_EQ(fixture.reducer_calls, 65u);
    ASSERT_EQ(fixture.view_calls, 66u);
    fixture_destroy(&fixture);
}

TEST(completions_keep_fifo_and_result_across_runtime_pumps) {
    Fixture fixture;
    ASSERT_TRUE(fixture_init(&fixture));
    ASSERT_EQ(my_compose_runtime_pump(fixture.runtime), MY_COMPOSE_OK);
    for (uint32_t i = 0u; i < 33u; ++i) {
        MyComposeCompletion completion;
        ASSERT_EQ(dispatch_intent(&fixture, EFFECT_INTENT, i + 1u),
            MY_COMPOSE_OK);
        ASSERT_EQ(my_compose_runtime_pump(fixture.runtime), MY_COMPOSE_OK);
        memset(&completion, 0, sizeof(completion));
        completion.request_id = fixture.effects[i].request_id;
        completion.store_id = fixture.effects[i].store_id;
        completion.store_generation = fixture.effects[i].store_generation;
        completion.owner = fixture.effects[i].owner;
        completion.type = COMPLETION_INTENT;
        completion.result = 100u + i;
        completion.delivery = MY_COMPOSE_OK;
        ASSERT_EQ(my_compose_store_complete(fixture.store, &completion),
            MY_COMPOSE_OK);
        ASSERT_EQ(my_compose_runtime_pump(fixture.runtime), MY_COMPOSE_OK);
    }
    ASSERT_EQ(fixture.reducer_calls, 66u);
    ASSERT_EQ(fixture.executor_calls, 33u);
    for (uint32_t i = 0u; i < 33u; ++i) {
        ASSERT_EQ(fixture.intent_results[1u + 2u * i], 100u + i);
    }
    fixture_destroy(&fixture);
}

TEST(executor_pending_retries_same_request_without_reducing) {
    Fixture fixture;
    ASSERT_TRUE(fixture_init(&fixture));
    ASSERT_EQ(my_compose_runtime_pump(fixture.runtime), MY_COMPOSE_OK);
    fixture.executor_pending_once = true;
    ASSERT_EQ(dispatch_intent(&fixture, EFFECT_INTENT, 9u), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_runtime_pump(fixture.runtime), MY_COMPOSE_PENDING);
    ASSERT_EQ(fixture.reducer_calls, 1u);
    ASSERT_EQ(fixture.executor_calls, 1u);
    ASSERT_EQ(my_compose_store_diagnostics(fixture.store)->outbox_effects, 1u);
    ASSERT_EQ(my_compose_runtime_pump(fixture.runtime), MY_COMPOSE_OK);
    ASSERT_EQ(fixture.reducer_calls, 1u);
    ASSERT_EQ(fixture.executor_calls, 2u);
    ASSERT_EQ(fixture.effects[0].request_id, fixture.effects[1].request_id);
    ASSERT_EQ(my_compose_store_diagnostics(fixture.store)->outstanding_effects, 1u);
    fixture_destroy(&fixture);
}

TEST(restart_recycles_outstanding_and_rejects_old_completion) {
    Fixture fixture;
    MyComposeCompletion completion;
    ASSERT_TRUE(fixture_init(&fixture));
    ASSERT_EQ(my_compose_runtime_pump(fixture.runtime), MY_COMPOSE_OK);
    ASSERT_EQ(dispatch_intent(&fixture, EFFECT_INTENT, 4u), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_runtime_pump(fixture.runtime), MY_COMPOSE_OK);
    memset(&completion, 0, sizeof(completion));
    completion.request_id = fixture.effects[0].request_id;
    completion.store_id = fixture.effects[0].store_id;
    completion.store_generation = fixture.effects[0].store_generation;
    completion.owner = fixture.effects[0].owner;
    completion.delivery = MY_COMPOSE_OK;
    ASSERT_EQ(my_compose_runtime_restart(fixture.runtime), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_store_diagnostics(fixture.store)->request_count, 0u);
    ASSERT_EQ(my_compose_store_complete(fixture.store, &completion),
        MY_COMPOSE_STALE);
    fixture_destroy(&fixture);
}

TEST_MAIN_BEGIN()
RUN_TEST(runtime_orders_each_state_revision_through_finalize_before_effects);
RUN_TEST(pending_view_reaps_and_retries_without_reducing_or_dispatching);
RUN_TEST(stage_failure_keeps_state_and_rebuilds_before_dispatch);
RUN_TEST(runtime_rejects_sink_from_another_store);
RUN_TEST(runtime_preserves_store_budget_without_repeating_reducer);
RUN_TEST(completions_keep_fifo_and_result_across_runtime_pumps);
RUN_TEST(executor_pending_retries_same_request_without_reducing);
RUN_TEST(restart_recycles_outstanding_and_rejects_old_completion);
TEST_MAIN_END()
