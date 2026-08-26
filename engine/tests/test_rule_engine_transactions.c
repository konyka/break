#include "test_framework.h"
#include <rule_engine/rule_engine.h>
#include "../src/rule_engine/re_internal.h"
#include <string.h>

static re_string_t text(const char *value) { return (re_string_t){value, strlen(value)}; }

typedef struct event_state_t { size_t count; re_fact_change_kind_t kinds[8]; } event_state_t;

typedef struct callback_state_t {
    re_fact_txn_t *transaction;
    re_subscription_t *subscription;
    size_t calls;
    re_status_t begin_status;
    int destroy_facts;
} callback_state_t;

typedef struct allocator_state_t {
    size_t calls;
    size_t fail_at;
    size_t frees;
} allocator_state_t;

typedef struct snapshot_state_t {
    size_t calls;
    int64_t value;
    size_t name_size;
} snapshot_state_t;

static void *test_alloc(void *context, size_t size) {
    allocator_state_t *state = context;
    state->calls++;
    if (state->fail_at != 0u && state->calls >= state->fail_at) return NULL;
    return malloc(size);
}

static void *test_realloc(void *context, void *memory, size_t size) {
    allocator_state_t *state = context;
    state->calls++;
    if (state->fail_at != 0u && state->calls >= state->fail_at) return NULL;
    return realloc(memory, size);
}

static void test_free(void *context, void *memory) {
    allocator_state_t *state = context;
    state->frees++;
    free(memory);
}

static re_status_t record_event(re_facts_t *facts, const re_fact_event_t *event, void *context) {
    event_state_t *state = context;
    (void)facts;
    state->kinds[state->count++] = event->kind;
    return RE_STATUS_OK;
}

static re_status_t snapshot_event(re_facts_t *facts, const re_fact_event_t *event, void *context) {
    snapshot_state_t *state = context;
    re_value_t replacement = {RE_VALUE_INT64, {.int64_value = 99}};
    (void)re_facts_set(facts, text("Other"), &replacement);
    state->calls++;
    state->name_size = event->name.size;
    state->value = event->value.as.int64_value;
    return RE_STATUS_OK;
}

static re_status_t reentrant_event(re_facts_t *facts, const re_fact_event_t *event, void *context) {
    callback_state_t *state = context;
    (void)event;
    state->calls++;
    state->begin_status = re_facts_begin(facts, &state->transaction);
    re_subscription_destroy(state->subscription);
    if (state->destroy_facts) re_facts_destroy(facts);
    return RE_STATUS_OK;
}

TEST(transaction_begin_isolated_and_commit_notifies_in_order) {
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_fact_txn_t *transaction = NULL;
    re_subscription_t *subscription = NULL;
    event_state_t events = {0};
    re_fact_id_t id = {0, 0};
    re_value_t one = {RE_VALUE_INT64, {.int64_value = 1}};
    re_value_t two = {RE_VALUE_INT64, {.int64_value = 2}};
    re_value_t output = {RE_VALUE_NONE, {0}};
    ASSERT_EQ(re_facts_subscribe(facts, record_event, &events, &subscription), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("Score"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_facts_begin(facts, &transaction), RE_STATUS_OK);
    ASSERT_EQ(re_facts_txn_insert(transaction, text("Extra"), &one, &id), RE_STATUS_OK);
    ASSERT_EQ(re_facts_txn_update(transaction, id, &two), RE_STATUS_OK);
    ASSERT_EQ(re_facts_txn_get(transaction, text("Extra"), &output), RE_STATUS_OK);
    ASSERT_EQ(output.as.int64_value, 2);
    ASSERT_EQ(re_facts_get(facts, text("Extra"), &output), RE_STATUS_NOT_FOUND);
    ASSERT_EQ(events.count, 0u);
    ASSERT_EQ(re_facts_commit(transaction), RE_STATUS_OK);
    ASSERT_EQ(events.count, 1u);
    ASSERT_EQ(events.kinds[0], RE_FACT_INSERT);
    ASSERT_EQ(re_facts_get(facts, text("Extra"), &output), RE_STATUS_OK);
    ASSERT_EQ(output.as.int64_value, 2);
    re_subscription_destroy(subscription);
    re_facts_destroy(facts);
}

TEST(transaction_rollback_discards_mutations_and_busy_statuses_are_stable) {
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_fact_txn_t *transaction = NULL;
    re_fact_txn_t *nested = NULL;
    re_value_t value = {RE_VALUE_INT64, {.int64_value = 7}};
    ASSERT_EQ(re_facts_commit(NULL), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_facts_begin(facts, &transaction), RE_STATUS_OK);
    ASSERT_EQ(re_facts_begin(facts, &nested), RE_STATUS_BUSY);
    ASSERT_EQ(re_facts_txn_set(transaction, text("Temp"), &value), RE_STATUS_OK);
    re_facts_rollback(transaction);
    ASSERT_EQ(re_facts_get(facts, text("Temp"), &value), RE_STATUS_NOT_FOUND);
    re_facts_rollback(NULL);
    re_facts_destroy(facts);
}

TEST(transaction_retract_is_staged_and_generation_remains_safe) {
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_fact_txn_t *transaction = NULL;
    re_fact_id_t id = {0, 0};
    re_value_t value = {RE_VALUE_INT64, {.int64_value = 1}};
    ASSERT_EQ(re_facts_insert(facts, text("Score"), &value, &id), RE_STATUS_OK);
    ASSERT_EQ(re_facts_begin(facts, &transaction), RE_STATUS_OK);
    ASSERT_EQ(re_facts_txn_retract(transaction, id), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("Score"), &value), RE_STATUS_OK);
    re_facts_rollback(transaction);
    ASSERT_EQ(re_facts_update(facts, id, &value), RE_STATUS_OK);
    re_facts_destroy(facts);
}

TEST(transaction_begin_after_retract_preserves_stale_slots) {
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_fact_txn_t *transaction = NULL;
    re_fact_id_t id = {0, 0};
    re_value_t value = {RE_VALUE_INT64, {.int64_value = 1}};
    ASSERT_EQ(re_facts_insert(facts, text("Score"), &value, &id), RE_STATUS_OK);
    ASSERT_EQ(re_facts_retract(facts, id), RE_STATUS_OK);
    ASSERT_EQ(re_facts_begin(facts, &transaction), RE_STATUS_OK);
    ASSERT_EQ(re_facts_txn_set(transaction, text("Other"), &value), RE_STATUS_OK);
    ASSERT_EQ(re_facts_commit(transaction), RE_STATUS_OK);
    ASSERT_EQ(re_facts_update(facts, id, &value), RE_STATUS_NOT_FOUND);
    re_facts_destroy(facts);
}

TEST(transaction_effective_lifecycle_is_ordered_and_reinsert_is_not_update) {
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_fact_txn_t *transaction = NULL;
    re_fact_id_t id = {0, 0};
    event_state_t events = {0};
    re_subscription_t *subscription = NULL;
    re_value_t value = {RE_VALUE_INT64, {.int64_value = 1}};
    ASSERT_EQ(re_facts_subscribe(facts, record_event, &events, &subscription), RE_STATUS_OK);
    ASSERT_EQ(re_facts_insert(facts, text("A"), &value, &id), RE_STATUS_OK);
    events.count = 0u;
    ASSERT_EQ(re_facts_begin(facts, &transaction), RE_STATUS_OK);
    ASSERT_EQ(re_facts_txn_retract(transaction, id), RE_STATUS_OK);
    ASSERT_EQ(re_facts_txn_insert(transaction, text("A"), &value, &id), RE_STATUS_OK);
    ASSERT_EQ(re_facts_commit(transaction), RE_STATUS_OK);
    ASSERT_EQ(events.count, 2u);
    ASSERT_EQ(events.kinds[0], RE_FACT_RETRACT);
    ASSERT_EQ(events.kinds[1], RE_FACT_INSERT);
    re_subscription_destroy(subscription);
    re_facts_destroy(facts);
}

TEST(transaction_structured_reads_use_staged_overlay_and_serial_is_swapped) {
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_fact_txn_t *transaction = NULL;
    re_value_handle_t *object = NULL;
    re_value_t value = {RE_VALUE_INT64, {.int64_value = 3}};
    re_value_t output = {RE_VALUE_NONE, {0}};
    ASSERT_EQ(re_value_create_object(facts, &object), RE_STATUS_OK);
    ASSERT_EQ(re_value_object_set(object, text("City"), &value), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set_value(facts, text("Address"), object), RE_STATUS_OK);
    ASSERT_EQ(re_facts_begin(facts, &transaction), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get_path(facts, text("Address.City"), &output), RE_STATUS_OK);
    ASSERT_EQ(output.as.int64_value, 3);
    ASSERT_EQ(re_facts_txn_set(transaction, text("Score"), &value), RE_STATUS_OK);
    ASSERT_EQ(re_facts_commit(transaction), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("After"), &value), RE_STATUS_OK);
    re_value_destroy(object);
    re_facts_destroy(facts);
}

TEST(transaction_callbacks_are_busy_and_destroy_is_deferred) {
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_fact_txn_t *transaction = NULL;
    re_subscription_t *subscription = NULL;
    callback_state_t state = {0};
    re_value_t value = {RE_VALUE_INT64, {.int64_value = 1}};
    state.destroy_facts = 1;
    ASSERT_EQ(re_facts_subscribe(facts, reentrant_event, &state, &subscription), RE_STATUS_OK);
    state.subscription = subscription;
    ASSERT_EQ(re_facts_begin(facts, &transaction), RE_STATUS_OK);
    ASSERT_EQ(re_facts_txn_set(transaction, text("A"), &value), RE_STATUS_OK);
    ASSERT_EQ(re_facts_commit(transaction), RE_STATUS_OK);
    ASSERT_EQ(state.calls, 1u);
    ASSERT_EQ(state.begin_status, RE_STATUS_BUSY);
    ASSERT_EQ(re_facts_commit(transaction), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_facts_txn_set(transaction, text("B"), &value), RE_STATUS_INVALID_ARGUMENT);
}

TEST(transaction_begin_is_busy_while_facts_are_running) {
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_fact_txn_t *transaction = NULL;
    facts->running = 1;
    ASSERT_EQ(re_facts_begin(facts, &transaction), RE_STATUS_BUSY);
    facts->running = 0;
    re_facts_destroy(facts);
}

TEST(transaction_allocator_failures_leave_no_live_handle) {
    allocator_state_t state = {0};
    re_allocator_t allocator = {&state, test_alloc, test_realloc, test_free};
    re_facts_t *facts = re_facts_create(&allocator, NULL);
    re_fact_txn_t *transaction = NULL;
    re_value_t value = {RE_VALUE_INT64, {.int64_value = 1}};
    ASSERT_NOT_NULL(facts);
    state.fail_at = state.calls + 2u;
    ASSERT_EQ(re_facts_begin(facts, &transaction), RE_STATUS_OUT_OF_MEMORY);
    ASSERT_TRUE(transaction == NULL);
    state.fail_at = 0u;
    ASSERT_EQ(re_facts_begin(facts, &transaction), RE_STATUS_OK);
    state.fail_at = state.calls + 1u;
    ASSERT_EQ(re_facts_txn_set(transaction, text("A"), &value), RE_STATUS_OUT_OF_MEMORY);
    state.fail_at = 0u;
    re_facts_rollback(transaction);
    re_facts_destroy(facts);
}

TEST(transaction_noop_commit_emits_no_event_and_preserves_serial) {
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_fact_txn_t *transaction = NULL;
    re_subscription_t *subscription = NULL;
    event_state_t events = {0};
    re_value_t value = {RE_VALUE_INT64, {.int64_value = 1}};
    ASSERT_EQ(re_facts_subscribe(facts, record_event, &events, &subscription), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("A"), &value), RE_STATUS_OK);
    { uint64_t serial = facts->mutation_serial;
      ASSERT_EQ(re_facts_begin(facts, &transaction), RE_STATUS_OK);
      ASSERT_EQ(re_facts_commit(transaction), RE_STATUS_OK);
      ASSERT_EQ(facts->mutation_serial, serial); }
    ASSERT_EQ(events.count, 0u);
    re_subscription_destroy(subscription);
    re_facts_destroy(facts);
}

TEST(transaction_event_payload_is_owned_snapshot) {
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_fact_txn_t *transaction = NULL;
    re_subscription_t *subscription = NULL;
    snapshot_state_t state = {0};
    re_value_t value = {RE_VALUE_INT64, {.int64_value = 7}};
    ASSERT_EQ(re_facts_subscribe(facts, snapshot_event, &state, &subscription), RE_STATUS_OK);
    ASSERT_EQ(re_facts_begin(facts, &transaction), RE_STATUS_OK);
    ASSERT_EQ(re_facts_txn_set(transaction, text("A"), &value), RE_STATUS_OK);
    ASSERT_EQ(re_facts_commit(transaction), RE_STATUS_OK);
    ASSERT_EQ(state.calls, 1u);
    ASSERT_EQ(state.name_size, 1u);
    ASSERT_EQ(state.value, 7);
    re_subscription_destroy(subscription);
    re_facts_destroy(facts);
}

TEST_MAIN_BEGIN()
    RUN_TEST(transaction_begin_isolated_and_commit_notifies_in_order);
    RUN_TEST(transaction_rollback_discards_mutations_and_busy_statuses_are_stable);
    RUN_TEST(transaction_retract_is_staged_and_generation_remains_safe);
    RUN_TEST(transaction_begin_after_retract_preserves_stale_slots);
    RUN_TEST(transaction_effective_lifecycle_is_ordered_and_reinsert_is_not_update);
    RUN_TEST(transaction_structured_reads_use_staged_overlay_and_serial_is_swapped);
    RUN_TEST(transaction_callbacks_are_busy_and_destroy_is_deferred);
    RUN_TEST(transaction_begin_is_busy_while_facts_are_running);
    RUN_TEST(transaction_allocator_failures_leave_no_live_handle);
    RUN_TEST(transaction_noop_commit_emits_no_event_and_preserves_serial);
    RUN_TEST(transaction_event_payload_is_owned_snapshot);
TEST_MAIN_END()
