#include "test_framework.h"

#include <myui/mycompose/my_compose_internal.h>
#include <myui/mycompose/my_compose_store.h>

#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define LOG_CAPACITY 256u
#define INTENT_NO_EFFECT 1u
#define INTENT_ONE_EFFECT 2u
#define INTENT_MANY_EFFECTS 3u
#define INTENT_FAIL 4u
#define INTENT_NINE_EFFECTS 5u
#define INTENT_COMPLETION 6u

typedef struct TestState {
    uint32_t count;
} TestState;

typedef struct Fixture {
    MyComposeStore *store;
    MyComposeStatus clone_status;
    MyComposeStatus reducer_status;
    MyComposeStatus executor_status;
    bool executor_pending_once;
    uint32_t clone_calls;
    uint32_t reducer_calls;
    uint32_t executor_calls;
    uint32_t dispose_calls;
    uint32_t dispose_at_last_clone;
    uint32_t intent_types[LOG_CAPACITY];
    uint32_t intent_results[LOG_CAPACITY];
    uint32_t intent_values[LOG_CAPACITY];
    uint8_t intent_payload_bytes[LOG_CAPACITY];
    MyComposeEffect effects[LOG_CAPACITY];
    uint8_t effect_payloads[LOG_CAPACITY][MY_COMPOSE_MESSAGE_BYTES];
    MyComposeStatus ninth_status;
    uint32_t ninth_count;
    bool ninth_preserved;
} Fixture;

static MyComposeNodeHandle no_owner(void) {
    MyComposeNodeHandle owner = {0u, 0u};
    return owner;
}

static MyComposeNodeHandle owner(uint32_t index, uint32_t generation) {
    MyComposeNodeHandle handle = {index, generation};
    return handle;
}

static MyComposeStatus clone_state(void *context, const void *source,
    uint32_t source_size, void *destination, uint32_t destination_size,
    uint32_t *out_size) {
    Fixture *fixture = context;
    fixture->clone_calls++;
    fixture->dispose_at_last_clone = fixture->dispose_calls;
    if (fixture->clone_status != MY_COMPOSE_OK) return fixture->clone_status;
    if (source_size != sizeof(TestState) || destination_size < sizeof(TestState)) {
        return MY_COMPOSE_INVALID;
    }
    memcpy(destination, source, sizeof(TestState));
    *out_size = sizeof(TestState);
    return MY_COMPOSE_OK;
}

static void dispose_state(void *context, void *state, uint32_t size) {
    Fixture *fixture = context;
    (void)state;
    (void)size;
    fixture->dispose_calls++;
}

static MyComposeStatus append_effect(MyComposeEffectBatch *batch,
    uint32_t value) {
    uint8_t payload[4];
    payload[0] = (uint8_t)value;
    payload[1] = (uint8_t)(value >> 8);
    payload[2] = (uint8_t)(value >> 16);
    payload[3] = (uint8_t)(value >> 24);
    return my_compose_effect_batch_append(batch, 700u, payload,
        (uint32_t)sizeof(payload));
}

static MyComposeStatus reduce_intent(void *context, const MyComposeIntent *intent,
    const void *current, uint32_t current_size, void *candidate,
    uint32_t *candidate_size, MyComposeEffectBatch *batch) {
    Fixture *fixture = context;
    const TestState *state = current;
    TestState *next = candidate;
    uint32_t value = 0u;
    uint32_t slot = fixture->reducer_calls;
    (void)current_size;
    if (slot < LOG_CAPACITY) {
        fixture->intent_types[slot] = intent->type;
        fixture->intent_results[slot] = intent->result;
        if (intent->payload_size > 0u) {
            fixture->intent_payload_bytes[slot] = intent->payload[0];
        }
        if (intent->payload_size == sizeof(uint32_t)) {
            memcpy(&value, intent->payload, sizeof(value));
            fixture->intent_values[slot] = value;
        }
    }
    fixture->reducer_calls++;
    if (*candidate_size != sizeof(TestState)) return MY_COMPOSE_INVALID;
    *next = *state;
    if (intent->type == INTENT_NO_EFFECT || intent->type == INTENT_ONE_EFFECT) {
        next->count += value;
    }
    if (intent->type == INTENT_FAIL) {
        next->count = 999u;
        (void)append_effect(batch, 999u);
        return fixture->reducer_status;
    }
    if (intent->type == INTENT_ONE_EFFECT) {
        (void)append_effect(batch, value);
    } else if (intent->type == INTENT_MANY_EFFECTS) {
        for (uint32_t i = 0u; i < value; ++i) {
            (void)append_effect(batch, i);
        }
    } else if (intent->type == INTENT_NINE_EFFECTS) {
        MyComposeEffectBatch before;
        for (uint32_t i = 0u; i < 8u; ++i) {
            (void)append_effect(batch, i + 1u);
        }
        before = *batch;
        fixture->ninth_status = append_effect(batch, 9u);
        fixture->ninth_count = batch->count;
        fixture->ninth_preserved =
            memcmp(batch->effects, before.effects, sizeof(before.effects)) == 0 &&
            memcmp(batch->payload_storage, before.payload_storage,
                sizeof(before.payload_storage)) == 0;
        fixture->ninth_preserved = fixture->ninth_preserved &&
            my_compose_effect_batch_append(batch, 701u, NULL, 0u) ==
                MY_COMPOSE_OVERLOAD;
    }
    return MY_COMPOSE_OK;
}

static MyComposeStatus execute_effect(void *context,
    const MyComposeEffect *effect) {
    Fixture *fixture = context;
    uint32_t slot = fixture->executor_calls;
    fixture->executor_calls++;
    if (slot < LOG_CAPACITY) {
        fixture->effects[slot] = *effect;
        if (effect->payload_size > MY_COMPOSE_MESSAGE_BYTES) {
            return MY_COMPOSE_INVALID;
        }
        memcpy(fixture->effect_payloads[slot], effect->payload,
            effect->payload_size);
        fixture->effects[slot].payload = fixture->effect_payloads[slot];
    }
    if (fixture->executor_pending_once) {
        fixture->executor_pending_once = false;
        return MY_COMPOSE_PENDING;
    }
    return fixture->executor_status;
}

static bool fixture_init(Fixture *fixture) {
    TestState initial = {0u};
    MyComposeStateOps ops;
    memset(fixture, 0, sizeof(*fixture));
    memset(&ops, 0, sizeof(ops));
    fixture->clone_status = MY_COMPOSE_OK;
    fixture->reducer_status = MY_COMPOSE_CONFLICT;
    fixture->executor_status = MY_COMPOSE_OK;
    ops.context = fixture;
    ops.clone = clone_state;
    ops.dispose = dispose_state;
    fixture->store = my_compose_store_create(&initial, (uint32_t)sizeof(initial),
        &ops, fixture, reduce_intent, fixture, execute_effect);
    return fixture->store != NULL;
}

static void fixture_destroy(Fixture *fixture) {
    my_compose_store_destroy(fixture->store);
    fixture->store = NULL;
}

static MyComposeIntent make_intent(uint32_t type, uint32_t value,
    MyComposeNodeHandle owner_handle) {
    MyComposeIntent intent;
    static uint32_t payload;
    memset(&intent, 0, sizeof(intent));
    payload = value;
    intent.type = type;
    intent.payload_size = (uint32_t)sizeof(payload);
    intent.payload = (const uint8_t *)&payload;
    intent.owner = owner_handle;
    intent.result = MY_COMPOSE_OK;
    return intent;
}

static MyComposeStatus dispatch_value(Fixture *fixture, uint32_t type,
    uint32_t value, MyComposeNodeHandle owner_handle) {
    uint32_t payload = value;
    MyComposeIntent intent;
    memset(&intent, 0, sizeof(intent));
    intent.type = type;
    intent.payload_size = (uint32_t)sizeof(payload);
    intent.payload = (const uint8_t *)&payload;
    intent.owner = owner_handle;
    intent.result = MY_COMPOSE_OK;
    return my_compose_store_dispatch(fixture->store, &intent);
}

static uint32_t state_count(const Fixture *fixture) {
    const void *state = NULL;
    uint32_t size = 0u;
    if (my_compose_store_state(fixture->store, &state, &size) != MY_COMPOSE_OK ||
        size != sizeof(TestState)) {
        return UINT32_MAX;
    }
    return ((const TestState *)state)->count;
}

static const MyComposeDiagnostics *diagnostics(const Fixture *fixture) {
    return my_compose_store_diagnostics(fixture->store);
}

static MyComposeStatus produce_effects(Fixture *fixture, uint32_t count,
    MyComposeNodeHandle owner_handle) {
    MyComposeStatus status = dispatch_value(fixture, INTENT_MANY_EFFECTS, count,
        owner_handle);
    if (status != MY_COMPOSE_OK) return status;
    status = my_compose_store_reduce(fixture->store);
    if (status != MY_COMPOSE_OK) return status;
    return my_compose_store_dispatch_effects(fixture->store);
}

static MyComposeCompletion completion_for(const MyComposeEffect *effect,
    uint32_t result, const void *payload, uint32_t payload_size) {
    MyComposeCompletion completion;
    memset(&completion, 0, sizeof(completion));
    completion.request_id = effect->request_id;
    completion.store_generation = effect->store_generation;
    completion.owner = effect->owner;
    completion.type = INTENT_COMPLETION;
    completion.result = result;
    completion.payload = payload;
    completion.payload_size = payload_size;
    completion.delivery = MY_COMPOSE_OK;
    return completion;
}

static void seed_outstanding_for_full_completion(Fixture *fixture) {
    MyComposeRequest *request = &fixture->store->requests[0];
    memset(request, 0, sizeof(*request));
    request->used = true;
    request->location = MY_COMPOSE_REQUEST_OUTSTANDING;
    request->effect.type = INTENT_COMPLETION;
    request->effect.store_generation = fixture->store->generation;
    request->effect.request_id = 1000u;
    request->effect.owner = no_owner();
    request->effect.payload = request->payload;
    fixture->store->request_count = 1u;
    fixture->store->outstanding_count = 1u;
}

TEST(fifo_reduces_cloned_state_and_copies_intent_payload) {
    Fixture fixture;
    ASSERT_TRUE(fixture_init(&fixture));
    uint8_t first_payload[sizeof(uint32_t)];
    uint8_t second_payload[sizeof(uint32_t)];
    uint32_t first = 1u;
    uint32_t second = 10u;
    memcpy(first_payload, &first, sizeof(first));
    memcpy(second_payload, &second, sizeof(second));
    MyComposeIntent a = make_intent(INTENT_NO_EFFECT, 0u, no_owner());
    MyComposeIntent b = make_intent(INTENT_NO_EFFECT, 0u, no_owner());
    a.payload = first_payload;
    b.payload = second_payload;
    ASSERT_EQ(my_compose_store_dispatch(fixture.store, &a), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_store_dispatch(fixture.store, &b), MY_COMPOSE_OK);
    memset(first_payload, 99u, sizeof(first_payload));
    memset(second_payload, 88u, sizeof(second_payload));
    ASSERT_EQ(state_count(&fixture), 0u);
    ASSERT_EQ(my_compose_store_reduce(fixture.store), MY_COMPOSE_OK);
    ASSERT_EQ(state_count(&fixture), 11u);
    ASSERT_EQ(fixture.reducer_calls, 2u);
    ASSERT_EQ(fixture.intent_values[0], 1u);
    ASSERT_EQ(fixture.intent_values[1], 10u);
    ASSERT_EQ(diagnostics(&fixture)->pending_intents, 0u);
    fixture_destroy(&fixture);
}

TEST(clone_failure_preserves_state_fifo_and_candidate_lifecycle) {
    Fixture fixture;
    ASSERT_TRUE(fixture_init(&fixture));
    ASSERT_EQ(dispatch_value(&fixture, INTENT_NO_EFFECT, 1u, no_owner()),
        MY_COMPOSE_OK);
    fixture.clone_status = MY_COMPOSE_FAILED;
    uint32_t reducer_before = fixture.reducer_calls;
    ASSERT_EQ(my_compose_store_reduce(fixture.store), MY_COMPOSE_FAILED);
    ASSERT_EQ(state_count(&fixture), 0u);
    ASSERT_EQ(fixture.reducer_calls, reducer_before);
    ASSERT_EQ(fixture.dispose_calls, 0u);
    ASSERT_EQ(diagnostics(&fixture)->pending_intents, 1u);
    ASSERT_EQ(diagnostics(&fixture)->outbox_effects, 0u);
    ASSERT_EQ(diagnostics(&fixture)->outstanding_effects, 0u);
    fixture.clone_status = MY_COMPOSE_OK;
    ASSERT_EQ(my_compose_store_reduce(fixture.store), MY_COMPOSE_OK);
    ASSERT_EQ(state_count(&fixture), 1u);
    fixture_destroy(&fixture);
}

TEST(reducer_failure_disposes_candidate_without_commit) {
    Fixture fixture;
    ASSERT_TRUE(fixture_init(&fixture));
    ASSERT_EQ(dispatch_value(&fixture, INTENT_FAIL, 1u, no_owner()),
        MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_store_reduce(fixture.store), MY_COMPOSE_CONFLICT);
    ASSERT_EQ(state_count(&fixture), 0u);
    ASSERT_EQ(fixture.dispose_calls,
        fixture.dispose_at_last_clone + 1u);
    ASSERT_EQ(diagnostics(&fixture)->pending_intents, 1u);
    ASSERT_EQ(diagnostics(&fixture)->outbox_effects, 0u);
    ASSERT_EQ(diagnostics(&fixture)->outstanding_effects, 0u);
    ASSERT_EQ(fixture.executor_calls, 0u);
    ASSERT_EQ(diagnostics(&fixture)->reducer_failures, 1u);
    fixture_destroy(&fixture);
}

TEST(ninth_effect_is_real_sticky_overload_and_atomic) {
    Fixture fixture;
    ASSERT_TRUE(fixture_init(&fixture));
    ASSERT_EQ(dispatch_value(&fixture, INTENT_NINE_EFFECTS, 0u, no_owner()),
        MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_store_reduce(fixture.store), MY_COMPOSE_OVERLOAD);
    ASSERT_EQ(fixture.ninth_status, MY_COMPOSE_OVERLOAD);
    ASSERT_EQ(fixture.ninth_count, 8u);
    ASSERT_TRUE(fixture.ninth_preserved);
    ASSERT_EQ(state_count(&fixture), 0u);
    ASSERT_EQ(fixture.dispose_calls,
        fixture.dispose_at_last_clone + 1u);
    ASSERT_EQ(diagnostics(&fixture)->pending_intents, 1u);
    ASSERT_EQ(diagnostics(&fixture)->outbox_effects, 0u);
    ASSERT_EQ(diagnostics(&fixture)->outstanding_effects, 0u);
    ASSERT_EQ(fixture.executor_calls, 0u);
    ASSERT_EQ(diagnostics(&fixture)->effect_overloads, 1u);
    fixture_destroy(&fixture);
}

TEST(shared_request_capacity_is_checked_after_reducer_before_publish) {
    Fixture fixture;
    ASSERT_TRUE(fixture_init(&fixture));
    for (uint32_t batch = 0u; batch < 4u; ++batch) {
        ASSERT_EQ(produce_effects(&fixture, 8u, no_owner()), MY_COMPOSE_OK);
    }
    ASSERT_EQ(diagnostics(&fixture)->outbox_effects, 0u);
    ASSERT_EQ(diagnostics(&fixture)->outstanding_effects, 32u);
    ASSERT_EQ(dispatch_value(&fixture, INTENT_NO_EFFECT, 10u, no_owner()),
        MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_store_reduce(fixture.store), MY_COMPOSE_OK);
    ASSERT_EQ(state_count(&fixture), 10u);
    ASSERT_EQ(diagnostics(&fixture)->outstanding_effects, 32u);

    ASSERT_EQ(dispatch_value(&fixture, INTENT_MANY_EFFECTS, 1u, no_owner()),
        MY_COMPOSE_OK);
    uint32_t reducer_before = fixture.reducer_calls;
    uint32_t executor_before = fixture.executor_calls;
    ASSERT_EQ(my_compose_store_reduce(fixture.store), MY_COMPOSE_OVERLOAD);
    ASSERT_EQ(fixture.reducer_calls, reducer_before + 1u);
    ASSERT_EQ(state_count(&fixture), 10u);
    ASSERT_EQ(fixture.dispose_calls,
        fixture.dispose_at_last_clone + 1u);
    ASSERT_EQ(diagnostics(&fixture)->pending_intents, 1u);
    ASSERT_EQ(diagnostics(&fixture)->outbox_effects, 0u);
    ASSERT_EQ(diagnostics(&fixture)->outstanding_effects, 32u);
    ASSERT_EQ(fixture.executor_calls, executor_before);
    fixture_destroy(&fixture);
}

TEST(full_outbox_rejects_effect_without_moving_existing_fifo) {
    Fixture fixture;
    ASSERT_TRUE(fixture_init(&fixture));
    for (uint32_t batch = 0u; batch < 4u; ++batch) {
        ASSERT_EQ(dispatch_value(&fixture, INTENT_MANY_EFFECTS, 8u, no_owner()),
            MY_COMPOSE_OK);
        ASSERT_EQ(my_compose_store_reduce(fixture.store), MY_COMPOSE_OK);
    }
    ASSERT_EQ(diagnostics(&fixture)->outbox_effects, 32u);
    ASSERT_EQ(diagnostics(&fixture)->outstanding_effects, 0u);
    ASSERT_EQ(dispatch_value(&fixture, INTENT_NO_EFFECT, 10u, no_owner()),
        MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_store_reduce(fixture.store), MY_COMPOSE_OK);
    ASSERT_EQ(state_count(&fixture), 10u);
    ASSERT_EQ(dispatch_value(&fixture, INTENT_MANY_EFFECTS, 1u, no_owner()),
        MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_store_reduce(fixture.store), MY_COMPOSE_OVERLOAD);
    ASSERT_EQ(state_count(&fixture), 10u);
    ASSERT_EQ(diagnostics(&fixture)->pending_intents, 1u);
    ASSERT_EQ(diagnostics(&fixture)->outbox_effects, 32u);
    ASSERT_EQ(diagnostics(&fixture)->outstanding_effects, 0u);
    ASSERT_EQ(fixture.executor_calls, 0u);
    ASSERT_EQ(fixture.dispose_calls,
        fixture.dispose_at_last_clone + 1u);
    fixture_destroy(&fixture);
}

TEST(completion_derived_intents_share_the_64_intent_budget) {
    Fixture fixture;
    ASSERT_TRUE(fixture_init(&fixture));
    for (uint32_t batch = 0u; batch < 4u; ++batch) {
        ASSERT_EQ(produce_effects(&fixture, 8u, no_owner()), MY_COMPOSE_OK);
    }
    for (uint32_t i = 0u; i < 32u; ++i) {
        MyComposeCompletion completion = completion_for(&fixture.effects[i],
            200u + i, NULL, 0u);
        ASSERT_EQ(my_compose_store_complete(fixture.store, &completion),
            MY_COMPOSE_OK);
    }
    for (uint32_t i = 0u; i < 64u; ++i) {
        ASSERT_EQ(dispatch_value(&fixture, INTENT_NO_EFFECT, 1u, no_owner()),
            MY_COMPOSE_OK);
    }
    uint32_t reducer_base = fixture.reducer_calls;
    ASSERT_EQ(my_compose_store_reduce(fixture.store), MY_COMPOSE_PENDING);
    ASSERT_EQ(state_count(&fixture), 64u);
    ASSERT_EQ(fixture.reducer_calls, reducer_base + 64u);
    ASSERT_EQ(diagnostics(&fixture)->pending_intents, 32u);
    ASSERT_EQ(diagnostics(&fixture)->queued_completions, 0u);
    ASSERT_EQ(my_compose_store_reduce(fixture.store), MY_COMPOSE_OK);
    ASSERT_EQ(fixture.reducer_calls, reducer_base + 96u);
    ASSERT_EQ(diagnostics(&fixture)->pending_intents, 0u);
    for (uint32_t i = 0u; i < 32u; ++i) {
        ASSERT_EQ(fixture.intent_results[reducer_base + 64u + i], 200u + i);
    }
    fixture_destroy(&fixture);
}

TEST(executor_pending_preserves_outbox_front_until_retry) {
    Fixture fixture;
    ASSERT_TRUE(fixture_init(&fixture));
    ASSERT_EQ(dispatch_value(&fixture, INTENT_MANY_EFFECTS, 2u, no_owner()),
        MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_store_reduce(fixture.store), MY_COMPOSE_OK);
    fixture.executor_pending_once = true;
    ASSERT_EQ(my_compose_store_dispatch_effects(fixture.store),
        MY_COMPOSE_PENDING);
    ASSERT_EQ(diagnostics(&fixture)->outbox_effects, 2u);
    ASSERT_EQ(diagnostics(&fixture)->outstanding_effects, 0u);
    ASSERT_EQ(fixture.executor_calls, 1u);
    uint64_t first_request = fixture.effects[0].request_id;
    ASSERT_EQ(my_compose_store_dispatch_effects(fixture.store), MY_COMPOSE_OK);
    ASSERT_EQ(diagnostics(&fixture)->outbox_effects, 0u);
    ASSERT_EQ(diagnostics(&fixture)->outstanding_effects, 2u);
    ASSERT_EQ(fixture.executor_calls, 3u);
    ASSERT_EQ(fixture.effects[1].request_id, first_request);
    ASSERT_EQ(fixture.effects[0].payload[0], 0u);
    ASSERT_EQ(fixture.effects[2].payload[0], 1u);
    fixture_destroy(&fixture);
}

TEST(wrapped_outbox_reaper_preserves_request_fifo) {
    Fixture fixture;
    ASSERT_TRUE(fixture_init(&fixture));
    ASSERT_EQ(produce_effects(&fixture, 8u, no_owner()), MY_COMPOSE_OK);
    ASSERT_EQ(produce_effects(&fixture, 8u, no_owner()), MY_COMPOSE_OK);
    ASSERT_EQ(produce_effects(&fixture, 8u, no_owner()), MY_COMPOSE_OK);
    ASSERT_EQ(produce_effects(&fixture, 6u, no_owner()), MY_COMPOSE_OK);
    for (uint32_t i = 0u; i < 30u; ++i) {
        MyComposeCompletion completion = completion_for(&fixture.effects[i],
            MY_COMPOSE_OK, NULL, 0u);
        ASSERT_EQ(my_compose_store_complete(fixture.store, &completion),
            MY_COMPOSE_OK);
    }
    ASSERT_EQ(my_compose_store_reduce(fixture.store), MY_COMPOSE_OK);
    ASSERT_EQ(dispatch_value(&fixture, INTENT_MANY_EFFECTS, 4u, no_owner()),
        MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_store_reduce(fixture.store), MY_COMPOSE_OK);
    ASSERT_EQ(diagnostics(&fixture)->outbox_effects, 4u);
    uint32_t request_slots[4];
    for (uint32_t i = 0u; i < 4u; ++i) request_slots[i] =
        fixture.store->outbox[i];
    fixture.store->outbox[30] = request_slots[0];
    fixture.store->outbox[31] = request_slots[1];
    fixture.store->outbox[0] = request_slots[2];
    fixture.store->outbox[1] = request_slots[3];
    fixture.store->outbox_head = 30u;
    ASSERT_EQ(my_compose_store_dispatch_effects(fixture.store), MY_COMPOSE_OK);
    ASSERT_EQ(fixture.executor_calls, 34u);
    ASSERT_EQ(diagnostics(&fixture)->outbox_effects, 0u);
    ASSERT_EQ(diagnostics(&fixture)->outstanding_effects, 4u);
    for (uint32_t i = 0u; i < 4u; ++i) {
        ASSERT_EQ(fixture.effects[30u + i].request_id, 31u + i);
        ASSERT_EQ(fixture.effects[30u + i].payload[0], i);
    }
    fixture_destroy(&fixture);
}

TEST(owner_is_checked_at_enqueue_reduce_and_completion) {
    Fixture fixture;
    ASSERT_TRUE(fixture_init(&fixture));
    MyComposeNodeHandle first = owner(1u, 1u);
    ASSERT_EQ(my_compose_store_register_owner(fixture.store, first),
        MY_COMPOSE_OK);
    ASSERT_EQ(dispatch_value(&fixture, INTENT_ONE_EFFECT, 1u, first),
        MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_store_reduce(fixture.store), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_store_dispatch_effects(fixture.store), MY_COMPOSE_OK);
    ASSERT_EQ(fixture.effects[0].request_id, 1u);
    ASSERT_EQ(fixture.effects[0].owner.index, 1u);
    ASSERT_EQ(fixture.effects[0].owner.generation, 1u);
    MyComposeCompletion old = completion_for(&fixture.effects[0], 55u, NULL, 0u);
    ASSERT_EQ(my_compose_store_restart(fixture.store), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_store_complete(fixture.store, &old), MY_COMPOSE_STALE);
    ASSERT_EQ(state_count(&fixture), 1u);

    ASSERT_EQ(dispatch_value(&fixture, INTENT_ONE_EFFECT, 2u, first),
        MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_store_reduce(fixture.store), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_store_dispatch_effects(fixture.store), MY_COMPOSE_OK);
    MyComposeCompletion invalidated = completion_for(&fixture.effects[1], 56u,
        NULL, 0u);
    ASSERT_EQ(my_compose_store_invalidate_owner(fixture.store, first),
        MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_store_complete(fixture.store, &invalidated),
        MY_COMPOSE_STALE);
    ASSERT_EQ(dispatch_value(&fixture, INTENT_NO_EFFECT, 4u, first),
        MY_COMPOSE_STALE);

    MyComposeNodeHandle second = owner(1u, 2u);
    ASSERT_EQ(my_compose_store_register_owner(fixture.store, second),
        MY_COMPOSE_OK);
    ASSERT_EQ(dispatch_value(&fixture, INTENT_NO_EFFECT, 4u, second),
        MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_store_invalidate_owner(fixture.store, second),
        MY_COMPOSE_OK);
    uint32_t reducer_before = fixture.reducer_calls;
    ASSERT_EQ(my_compose_store_reduce(fixture.store), MY_COMPOSE_STALE);
    ASSERT_EQ(fixture.reducer_calls, reducer_before);
    ASSERT_EQ(state_count(&fixture), 3u);
    ASSERT_EQ(diagnostics(&fixture)->pending_intents, 0u);
    fixture_destroy(&fixture);
}

TEST(close_rejects_input_and_late_completion_without_double_reap) {
    Fixture fixture;
    ASSERT_TRUE(fixture_init(&fixture));
    ASSERT_EQ(produce_effects(&fixture, 1u, no_owner()), MY_COMPOSE_OK);
    MyComposeCompletion completion = completion_for(&fixture.effects[0], 9u,
        NULL, 0u);
    my_compose_store_close(fixture.store);
    my_compose_store_close(fixture.store);
    ASSERT_EQ(dispatch_value(&fixture, INTENT_NO_EFFECT, 1u, no_owner()),
        MY_COMPOSE_CANCELLED);
    ASSERT_EQ(my_compose_store_complete(fixture.store, &completion),
        MY_COMPOSE_STALE);
    ASSERT_EQ(my_compose_store_reduce(fixture.store), MY_COMPOSE_CANCELLED);
    ASSERT_EQ(diagnostics(&fixture)->request_count, 0u);
    uint64_t recycled = diagnostics(&fixture)->recycled_requests;
    ASSERT_EQ(my_compose_store_complete(fixture.store, &completion),
        MY_COMPOSE_STALE);
    ASSERT_EQ(diagnostics(&fixture)->recycled_requests, recycled);
    ASSERT_EQ(state_count(&fixture), 0u);
    fixture_destroy(&fixture);
}

TEST(completion_overload_preserves_outstanding_and_retry_drains_33_in_fifo) {
    Fixture fixture;
    ASSERT_TRUE(fixture_init(&fixture));
    for (uint32_t batch = 0u; batch < 4u; ++batch) {
        ASSERT_EQ(produce_effects(&fixture, 8u, no_owner()), MY_COMPOSE_OK);
    }
    for (uint32_t i = 0u; i < 32u; ++i) {
        uint8_t payload = (uint8_t)i;
        MyComposeCompletion completion = completion_for(&fixture.effects[i],
            100u + i, &payload, 1u);
        ASSERT_EQ(my_compose_store_complete(fixture.store, &completion),
            MY_COMPOSE_OK);
        payload = 255u;
    }
    ASSERT_EQ(diagnostics(&fixture)->queued_completions, 32u);
    ASSERT_EQ(diagnostics(&fixture)->outstanding_effects, 0u);
    seed_outstanding_for_full_completion(&fixture);
    MyComposeEffect extra;
    memset(&extra, 0, sizeof(extra));
    extra.request_id = 1000u;
    extra.store_generation = fixture.store->generation;
    extra.owner = no_owner();
    uint8_t extra_payload = 32u;
    MyComposeCompletion completion = completion_for(&extra, 132u,
        &extra_payload, 1u);
    ASSERT_EQ(my_compose_store_complete(fixture.store, &completion),
        MY_COMPOSE_OVERLOAD);
    ASSERT_EQ(diagnostics(&fixture)->queued_completions, 32u);
    ASSERT_EQ(diagnostics(&fixture)->outstanding_effects, 1u);

    uint32_t reducer_base = fixture.reducer_calls;
    ASSERT_EQ(my_compose_store_reduce(fixture.store), MY_COMPOSE_OK);
    ASSERT_EQ(diagnostics(&fixture)->queued_completions, 0u);
    ASSERT_EQ(diagnostics(&fixture)->outstanding_effects, 1u);
    ASSERT_EQ(fixture.reducer_calls, reducer_base + 32u);
    for (uint32_t i = 0u; i < 32u; ++i) {
        ASSERT_EQ(fixture.intent_results[reducer_base + i], 100u + i);
        ASSERT_EQ(fixture.intent_payload_bytes[reducer_base + i], i);
    }
    ASSERT_EQ(my_compose_store_complete(fixture.store, &completion),
        MY_COMPOSE_OK);
    ASSERT_EQ(diagnostics(&fixture)->outstanding_effects, 0u);
    ASSERT_EQ(my_compose_store_reduce(fixture.store), MY_COMPOSE_OK);
    ASSERT_EQ(fixture.intent_results[reducer_base + 32u], 132u);
    ASSERT_EQ(fixture.intent_payload_bytes[reducer_base + 32u], 32u);
    fixture_destroy(&fixture);
}

TEST(transient_completion_retry_does_not_consume_or_reap_request) {
    Fixture fixture;
    ASSERT_TRUE(fixture_init(&fixture));
    ASSERT_EQ(produce_effects(&fixture, 1u, no_owner()), MY_COMPOSE_OK);
    MyComposeCompletion completion = completion_for(&fixture.effects[0], 8u,
        NULL, 0u);
    completion.delivery = MY_COMPOSE_PENDING;
    ASSERT_EQ(my_compose_store_complete(fixture.store, &completion),
        MY_COMPOSE_PENDING);
    ASSERT_EQ(diagnostics(&fixture)->outstanding_effects, 1u);
    ASSERT_EQ(diagnostics(&fixture)->queued_completions, 0u);
    ASSERT_EQ(my_compose_store_complete(fixture.store, &completion),
        MY_COMPOSE_PENDING);
    ASSERT_EQ(diagnostics(&fixture)->outstanding_effects, 1u);
    ASSERT_EQ(diagnostics(&fixture)->queued_completions, 0u);
    ASSERT_EQ(my_compose_store_reduce(fixture.store), MY_COMPOSE_OK);
    ASSERT_EQ(diagnostics(&fixture)->outstanding_effects, 1u);
    completion.delivery = MY_COMPOSE_OK;
    ASSERT_EQ(my_compose_store_complete(fixture.store, &completion),
        MY_COMPOSE_OK);
    ASSERT_EQ(diagnostics(&fixture)->outstanding_effects, 0u);
    ASSERT_EQ(diagnostics(&fixture)->queued_completions, 1u);
    fixture_destroy(&fixture);
}

TEST(sixty_five_intents_respect_capacity_fifo_and_recover) {
    Fixture fixture;
    ASSERT_TRUE(fixture_init(&fixture));
    for (uint32_t i = 0u; i < MY_COMPOSE_INTENT_CAPACITY; ++i) {
        ASSERT_EQ(dispatch_value(&fixture, INTENT_NO_EFFECT, 1u, no_owner()),
            MY_COMPOSE_OK);
    }
    ASSERT_EQ(dispatch_value(&fixture, INTENT_NO_EFFECT, 1u, no_owner()),
        MY_COMPOSE_OVERLOAD);
    ASSERT_EQ(diagnostics(&fixture)->pending_intents, 64u);
    ASSERT_EQ(my_compose_store_reduce(fixture.store), MY_COMPOSE_OK);
    ASSERT_EQ(state_count(&fixture), 64u);
    ASSERT_EQ(fixture.reducer_calls, 64u);
    ASSERT_EQ(diagnostics(&fixture)->pending_intents, 0u);
    ASSERT_EQ(dispatch_value(&fixture, INTENT_NO_EFFECT, 1u, no_owner()),
        MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_store_reduce(fixture.store), MY_COMPOSE_OK);
    ASSERT_EQ(state_count(&fixture), 65u);
    ASSERT_EQ(fixture.reducer_calls, 65u);
    fixture_destroy(&fixture);
}

TEST(thirty_two_terminal_requests_reap_once_then_effect_can_commit) {
    Fixture fixture;
    ASSERT_TRUE(fixture_init(&fixture));
    for (uint32_t batch = 0u; batch < 4u; ++batch) {
        ASSERT_EQ(produce_effects(&fixture, 8u, no_owner()), MY_COMPOSE_OK);
    }
    for (uint32_t i = 0u; i < 32u; ++i) {
        MyComposeCompletion completion = completion_for(&fixture.effects[i], 0u,
            NULL, 0u);
        completion.delivery = (i % 2u == 0u) ? MY_COMPOSE_STALE :
            MY_COMPOSE_FAILED;
        MyComposeStatus expected = (i % 2u == 0u) ? MY_COMPOSE_STALE :
            MY_COMPOSE_FAILED;
        ASSERT_EQ(my_compose_store_complete(fixture.store, &completion), expected);
    }
    ASSERT_EQ(diagnostics(&fixture)->outstanding_effects, 32u);
    ASSERT_EQ(diagnostics(&fixture)->queued_completions, 0u);
    ASSERT_EQ(my_compose_store_reduce(fixture.store), MY_COMPOSE_OK);
    ASSERT_EQ(diagnostics(&fixture)->outstanding_effects, 0u);
    ASSERT_EQ(diagnostics(&fixture)->request_count, 0u);
    ASSERT_EQ(diagnostics(&fixture)->recycled_requests, 32u);
    ASSERT_EQ(produce_effects(&fixture, 1u, no_owner()), MY_COMPOSE_OK);
    ASSERT_EQ(diagnostics(&fixture)->outstanding_effects, 1u);
    ASSERT_EQ(my_compose_store_reduce(fixture.store), MY_COMPOSE_OK);
    ASSERT_EQ(diagnostics(&fixture)->recycled_requests, 32u);
    fixture_destroy(&fixture);
}

TEST(request_id_near_overflow_never_wraps_and_failure_is_atomic) {
    Fixture fixture;
    ASSERT_TRUE(fixture_init(&fixture));
    ASSERT_EQ(my_compose_store_internal_seed_request(fixture.store,
        UINT64_MAX - 1u), MY_COMPOSE_OK);
    ASSERT_EQ(produce_effects(&fixture, 1u, no_owner()), MY_COMPOSE_OK);
    ASSERT_EQ(fixture.effects[0].request_id, UINT64_MAX - 1u);
    ASSERT_EQ(dispatch_value(&fixture, INTENT_ONE_EFFECT, 7u, no_owner()),
        MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_store_reduce(fixture.store), MY_COMPOSE_OVERLOAD);
    ASSERT_EQ(state_count(&fixture), 0u);
    ASSERT_EQ(diagnostics(&fixture)->pending_intents, 1u);
    ASSERT_EQ(diagnostics(&fixture)->outstanding_effects, 1u);
    ASSERT_EQ(fixture.store->next_request_id, UINT64_MAX);
    ASSERT_EQ(fixture.dispose_calls,
        fixture.dispose_at_last_clone + 1u);
    fixture_destroy(&fixture);
}

TEST(store_generation_near_overflow_retires_without_wrap) {
    Fixture fixture;
    ASSERT_TRUE(fixture_init(&fixture));
    ASSERT_EQ(my_compose_store_internal_seed_generation(fixture.store,
        UINT32_MAX - 1u), MY_COMPOSE_OK);
    ASSERT_EQ(produce_effects(&fixture, 1u, no_owner()), MY_COMPOSE_OK);
    MyComposeCompletion completion = completion_for(&fixture.effects[0], 0u,
        NULL, 0u);
    ASSERT_EQ(my_compose_store_restart(fixture.store), MY_COMPOSE_OK);
    ASSERT_EQ(fixture.store->generation, UINT32_MAX);
    ASSERT_EQ(my_compose_store_complete(fixture.store, &completion),
        MY_COMPOSE_STALE);
    ASSERT_EQ(dispatch_value(&fixture, INTENT_NO_EFFECT, 1u, no_owner()),
        MY_COMPOSE_OVERLOAD);
    ASSERT_EQ(my_compose_store_restart(fixture.store), MY_COMPOSE_OVERLOAD);
    ASSERT_EQ(fixture.store->generation, UINT32_MAX);
    ASSERT_EQ(my_compose_store_reduce(fixture.store), MY_COMPOSE_OVERLOAD);
    ASSERT_EQ(diagnostics(&fixture)->request_count, 0u);
    fixture_destroy(&fixture);
}

TEST(owner_generation_near_overflow_retires_without_wrap) {
    Fixture fixture;
    ASSERT_TRUE(fixture_init(&fixture));
    MyComposeNodeHandle old = owner(1u, UINT32_MAX - 1u);
    ASSERT_EQ(my_compose_store_register_owner(fixture.store, old), MY_COMPOSE_OK);
    ASSERT_EQ(dispatch_value(&fixture, INTENT_ONE_EFFECT, 1u, old),
        MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_store_reduce(fixture.store), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_store_dispatch_effects(fixture.store), MY_COMPOSE_OK);
    MyComposeCompletion completion = completion_for(&fixture.effects[0], 0u,
        NULL, 0u);
    ASSERT_EQ(my_compose_store_invalidate_owner(fixture.store, old),
        MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_store_register_owner(fixture.store,
        owner(1u, UINT32_MAX)), MY_COMPOSE_OVERLOAD);
    ASSERT_EQ(dispatch_value(&fixture, INTENT_NO_EFFECT, 1u, old),
        MY_COMPOSE_STALE);
    ASSERT_EQ(my_compose_store_complete(fixture.store, &completion),
        MY_COMPOSE_STALE);
    ASSERT_EQ(my_compose_store_reduce(fixture.store), MY_COMPOSE_OK);
    ASSERT_EQ(diagnostics(&fixture)->request_count, 0u);
    ASSERT_EQ(dispatch_value(&fixture, INTENT_NO_EFFECT, 1u, no_owner()),
        MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_store_reduce(fixture.store), MY_COMPOSE_OK);
    ASSERT_EQ(state_count(&fixture), 2u);
    fixture_destroy(&fixture);
}

TEST(dispose_is_exactly_once_for_reused_failed_and_live_slots) {
    Fixture fixture;
    ASSERT_TRUE(fixture_init(&fixture));
    ASSERT_EQ(dispatch_value(&fixture, INTENT_NO_EFFECT, 1u, no_owner()),
        MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_store_reduce(fixture.store), MY_COMPOSE_OK);
    ASSERT_EQ(dispatch_value(&fixture, INTENT_FAIL, 1u, no_owner()),
        MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_store_reduce(fixture.store), MY_COMPOSE_CONFLICT);
    ASSERT_EQ(fixture.dispose_calls, 2u);
    my_compose_store_close(fixture.store);
    my_compose_store_close(fixture.store);
    fixture_destroy(&fixture);
    ASSERT_EQ(fixture.dispose_calls, 3u);
}

TEST(oversize_payload_is_rejected_without_queue_change) {
    Fixture fixture;
    ASSERT_TRUE(fixture_init(&fixture));
    uint8_t payload[MY_COMPOSE_MESSAGE_BYTES + 1u];
    memset(payload, 0, sizeof(payload));
    MyComposeIntent intent = make_intent(INTENT_NO_EFFECT, 0u, no_owner());
    intent.payload = payload;
    intent.payload_size = (uint32_t)sizeof(payload);
    ASSERT_EQ(my_compose_store_dispatch(fixture.store, &intent),
        MY_COMPOSE_OVERLOAD);
    ASSERT_EQ(diagnostics(&fixture)->pending_intents, 0u);
    ASSERT_EQ(state_count(&fixture), 0u);
    fixture_destroy(&fixture);
}

TEST_MAIN_BEGIN()
    RUN_TEST(fifo_reduces_cloned_state_and_copies_intent_payload);
    RUN_TEST(clone_failure_preserves_state_fifo_and_candidate_lifecycle);
    RUN_TEST(reducer_failure_disposes_candidate_without_commit);
    RUN_TEST(ninth_effect_is_real_sticky_overload_and_atomic);
    RUN_TEST(shared_request_capacity_is_checked_after_reducer_before_publish);
    RUN_TEST(full_outbox_rejects_effect_without_moving_existing_fifo);
    RUN_TEST(completion_derived_intents_share_the_64_intent_budget);
    RUN_TEST(executor_pending_preserves_outbox_front_until_retry);
    RUN_TEST(wrapped_outbox_reaper_preserves_request_fifo);
    RUN_TEST(owner_is_checked_at_enqueue_reduce_and_completion);
    RUN_TEST(close_rejects_input_and_late_completion_without_double_reap);
    RUN_TEST(completion_overload_preserves_outstanding_and_retry_drains_33_in_fifo);
    RUN_TEST(transient_completion_retry_does_not_consume_or_reap_request);
    RUN_TEST(sixty_five_intents_respect_capacity_fifo_and_recover);
    RUN_TEST(thirty_two_terminal_requests_reap_once_then_effect_can_commit);
    RUN_TEST(request_id_near_overflow_never_wraps_and_failure_is_atomic);
    RUN_TEST(store_generation_near_overflow_retires_without_wrap);
    RUN_TEST(owner_generation_near_overflow_retires_without_wrap);
    RUN_TEST(dispose_is_exactly_once_for_reused_failed_and_live_slots);
    RUN_TEST(oversize_payload_is_rejected_without_queue_change);
TEST_MAIN_END()
