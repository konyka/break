#include "test_framework.h"
#include "../src/rule_engine/re_internal.h"
#include <stdlib.h>

static re_string_t text(const char *value) { return (re_string_t){value, strlen(value)}; }

typedef struct alloc_state_t { size_t calls; size_t fail_at; } alloc_state_t;
static void *test_alloc(void *context, size_t size) { alloc_state_t *state = context; ++state->calls; return state->fail_at == state->calls ? NULL : malloc(size); }
static void *test_realloc(void *context, void *memory, size_t size) { alloc_state_t *state = context; ++state->calls; return state->fail_at == state->calls ? NULL : realloc(memory, size); }
static void test_free(void *context, void *memory) { (void)context; free(memory); }
static re_status_t count_action(re_engine_t *engine, re_facts_t *facts, const re_rule_event_t *event, void *context) { (void)engine; (void)facts; (void)event; ++*(size_t *)context; return RE_STATUS_OK; }
static re_status_t failing_fact_callback(re_facts_t *facts, const re_fact_event_t *event, void *context) { (void)facts; (void)event; (void)context; return RE_STATUS_ERROR; }
typedef struct event_state_t { size_t count; re_fact_change_kind_t kinds[8]; } event_state_t;
static re_status_t record_fact_event(re_facts_t *facts, const re_fact_event_t *event, void *context) {
    event_state_t *state = (event_state_t *)context;
    (void)facts;
    if (state->count < sizeof(state->kinds) / sizeof(state->kinds[0])) state->kinds[state->count] = event->kind;
    ++state->count;
    return RE_STATUS_OK;
}

static re_status_t make_network(re_facts_t *facts, re_rete_network_t **network) {
    re_rete_condition_t conditions[2] = {
        {{"A", 1u}, RE_COMPARE_GT, {RE_VALUE_INT64, {.int64_value = 0}}},
        {{"B", 1u}, RE_COMPARE_EQ, {RE_VALUE_INT64, {.int64_value = 2}}}
    };
    return re_rete_network_create(facts, conditions, NULL, network);
}

TEST(compiled_network_persists_across_runs) {
    re_engine_t *engine = re_engine_create(NULL, NULL); re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL; re_rete_network_t *first = NULL; re_rete_network_t *second = NULL;
    re_value_t one = {RE_VALUE_INT64, {.int64_value = 1}}, two = {RE_VALUE_INT64, {.int64_value = 2}}; size_t calls = 0u;
    re_callbacks_t callbacks = {count_action, &calls};
    ASSERT_EQ(re_program_load(NULL, text("rule \"Join\" { when A > 0 and B == 2 then Result = 1; }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK); ASSERT_EQ(re_facts_set(facts, text("A"), &one), RE_STATUS_OK); ASSERT_EQ(re_facts_set(facts, text("B"), &two), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, &callbacks), RE_STATUS_OK); ASSERT_EQ(re_engine_rete_network(engine, &first), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, &callbacks), RE_STATUS_OK); ASSERT_EQ(re_engine_rete_network(engine, &second), RE_STATUS_OK); ASSERT_TRUE(first == second); ASSERT_EQ(calls, 2u);
    re_engine_destroy(engine); re_facts_destroy(facts);
}

TEST(structured_fact_changes_emit_owned_lifecycle_events) {
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_handle_t *array = NULL;
    re_value_t one = {RE_VALUE_INT64, {.int64_value = 1}};
    event_state_t events = {0};
    re_subscription_t *subscription = NULL;
    ASSERT_EQ(re_facts_subscribe(facts, record_fact_event, &events, &subscription), RE_STATUS_OK);
    ASSERT_EQ(re_value_create_array(facts, &array), RE_STATUS_OK);
    ASSERT_EQ(re_value_array_append(array, &one), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set_value(facts, text("Tags"), array), RE_STATUS_OK);
    ASSERT_EQ(events.count, 1u);
    ASSERT_EQ(events.kinds[0], RE_FACT_INSERT);
    ASSERT_EQ(re_facts_append_value(facts, text("Tags"), &one), RE_STATUS_OK);
    ASSERT_EQ(events.count, 2u);
    ASSERT_EQ(events.kinds[1], RE_FACT_UPDATE);
    re_subscription_destroy(subscription);
    re_value_destroy(array);
    re_facts_destroy(facts);
}

TEST(engine_destroy_clears_rete_owner) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_rete_network_t *network = NULL;
    re_value_t one = {RE_VALUE_INT64, {.int64_value = 1}};
    re_value_t two = {RE_VALUE_INT64, {.int64_value = 2}};
    size_t calls = 0u;
    re_callbacks_t callbacks = {count_action, &calls};
    ASSERT_EQ(re_program_load(NULL, text("rule \"Join\" { when A > 0 and B == 2 then Result = 1; }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("A"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("B"), &two), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, &callbacks), RE_STATUS_OK);
    ASSERT_EQ(re_engine_rete_network(engine, &network), RE_STATUS_OK);
    re_rete_network_destroy_internal(network);
    ASSERT_EQ(re_engine_rete_network(engine, &network), RE_STATUS_NOT_SUPPORTED);
    re_engine_destroy(engine);
    re_facts_destroy(facts);
}

TEST(external_network_survives_engine_run_and_install) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_rete_network_t *network = NULL;
    size_t calls = 0u;
    re_callbacks_t callbacks = {count_action, &calls};
    ASSERT_EQ(make_network(facts, &network), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("A"), &(re_value_t){RE_VALUE_INT64, {.int64_value = 1}}), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("B"), &(re_value_t){RE_VALUE_INT64, {.int64_value = 2}}), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text("rule \"Join\" { when A > 0 and B == 2 then Result = 1; }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, &callbacks), RE_STATUS_OK);
    ASSERT_EQ(calls, 1u);
    ASSERT_TRUE(facts->rete_network == network);
    ASSERT_TRUE(network->owner_engine == NULL);
    {
        re_program_t *replacement = NULL;
        ASSERT_EQ(re_program_load(NULL, text("rule \"Other\" { when A > 0 and B == 2 then Result = 2; }"), NULL, &replacement), RE_STATUS_OK);
        ASSERT_EQ(re_engine_install(engine, replacement), RE_STATUS_OK);
    }
    ASSERT_TRUE(facts->rete_network == network);
    re_rete_network_destroy(network);
    re_engine_destroy(engine);
    re_facts_destroy(facts);
}

TEST(external_network_survives_engine_destruction) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_rete_network_t *network = NULL;
    ASSERT_EQ(make_network(facts, &network), RE_STATUS_OK);
    re_engine_destroy(engine);
    ASSERT_TRUE(facts->rete_network == network);
    ASSERT_TRUE(network->facts == facts);
    ASSERT_EQ(re_rete_activation_count(network), 0u);
    re_rete_network_destroy(network);
    re_facts_destroy(facts);
}

TEST(facts_destroy_detaches_external_network_without_freeing_it) {
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_rete_network_t *network = NULL;
    ASSERT_EQ(make_network(facts, &network), RE_STATUS_OK);
    re_facts_destroy(facts);
    ASSERT_TRUE(network->facts == NULL);
    ASSERT_TRUE(network->subscription == NULL);
    ASSERT_EQ(re_rete_activation_count(network), 0u);
    re_rete_network_destroy(network);
}

TEST(unrelated_updates_preserve_memories_and_related_changes_propagate) {
    re_facts_t *facts = re_facts_create(NULL, NULL); re_rete_network_t *network = NULL;
    re_fact_id_t a, b, other; re_value_t one = {RE_VALUE_INT64, {.int64_value = 1}}, two = {RE_VALUE_INT64, {.int64_value = 2}}, zero = {RE_VALUE_INT64, {.int64_value = 0}};
    re_rete_alpha_memory_t *alpha;
    ASSERT_EQ(make_network(facts, &network), RE_STATUS_OK); alpha = network->alpha_memories;
    ASSERT_EQ(re_facts_insert(facts, text("A"), &one, &a), RE_STATUS_OK); ASSERT_EQ(re_facts_insert(facts, text("B"), &two, &b), RE_STATUS_OK); ASSERT_EQ(re_rete_activation_count(network), 1u);
    ASSERT_EQ(re_facts_insert(facts, text("Other"), &one, &other), RE_STATUS_OK); ASSERT_TRUE(alpha == network->alpha_memories); ASSERT_EQ(re_rete_activation_count(network), 1u);
    ASSERT_EQ(re_facts_update(facts, a, &zero), RE_STATUS_OK); ASSERT_EQ(re_rete_activation_count(network), 0u); ASSERT_EQ(re_facts_update(facts, a, &one), RE_STATUS_OK); ASSERT_EQ(re_rete_activation_count(network), 1u);
    ASSERT_EQ(re_facts_retract(facts, b), RE_STATUS_OK); ASSERT_EQ(re_rete_activation_count(network), 0u); ASSERT_EQ(re_facts_update(facts, b, &two), RE_STATUS_NOT_FOUND);
    re_rete_network_destroy_internal(network); re_facts_destroy(facts);
}

TEST(unchanged_lineage_preserves_activation_sequence_across_unrelated_events) {
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_rete_network_t *network = NULL;
    re_fact_id_t a, b, other, replacement;
    re_rete_activation_t first, current;
    re_value_t one = {RE_VALUE_INT64, {.int64_value = 1}};
    re_value_t two = {RE_VALUE_INT64, {.int64_value = 2}};
    ASSERT_EQ(make_network(facts, &network), RE_STATUS_OK);
    ASSERT_EQ(re_facts_insert(facts, text("A"), &one, &a), RE_STATUS_OK);
    ASSERT_EQ(re_facts_insert(facts, text("B"), &two, &b), RE_STATUS_OK);
    ASSERT_EQ(re_rete_activation_get(network, 0u, &first), RE_STATUS_OK);
    ASSERT_EQ(re_facts_insert(facts, text("Other"), &one, &other), RE_STATUS_OK);
    ASSERT_EQ(re_rete_activation_get(network, 0u, &current), RE_STATUS_OK);
    ASSERT_EQ(current.sequence, first.sequence);
    ASSERT_EQ(current.lineage[0].generation, first.lineage[0].generation);
    ASSERT_EQ(current.lineage[1].generation, first.lineage[1].generation);
    ASSERT_EQ(re_facts_retract(facts, b), RE_STATUS_OK);
    ASSERT_EQ(re_facts_insert(facts, text("B"), &two, &replacement), RE_STATUS_OK);
    ASSERT_EQ(re_rete_activation_get(network, 0u, &current), RE_STATUS_OK);
    ASSERT_NEQ(current.sequence, first.sequence);
    re_rete_network_destroy_internal(network); re_facts_destroy(facts);
}

TEST(token_provenance_and_transaction_effective_change) {
    re_facts_t *facts = re_facts_create(NULL, NULL); re_rete_network_t *network = NULL; re_fact_txn_t *txn = NULL;
    re_fact_id_t a, b; re_rete_activation_t activation; re_value_t one = {RE_VALUE_INT64, {.int64_value = 1}}, two = {RE_VALUE_INT64, {.int64_value = 2}};
    ASSERT_EQ(make_network(facts, &network), RE_STATUS_OK); network->producer_rule = text("Join"); ASSERT_EQ(re_facts_begin(facts, &txn), RE_STATUS_OK); ASSERT_EQ(re_facts_txn_insert(txn, text("A"), &one, &a), RE_STATUS_OK); ASSERT_EQ(re_facts_txn_insert(txn, text("B"), &two, &b), RE_STATUS_OK); ASSERT_EQ(re_facts_commit(txn), RE_STATUS_OK);
    ASSERT_EQ(re_rete_activation_count(network), 1u); ASSERT_EQ(re_rete_activation_get(network, 0u, &activation), RE_STATUS_OK); ASSERT_EQ(activation.lineage_count, 2u); ASSERT_EQ(activation.lineage[0].slot, a.slot); ASSERT_EQ(activation.lineage[1].slot, b.slot); ASSERT_EQ(activation.producer_rule.size, 4u);
    re_rete_network_destroy_internal(network); re_facts_destroy(facts);
}

TEST(allocation_failure_leaves_existing_network_consistent) {
    alloc_state_t state = {0u, 0u}; re_allocator_t allocator = {&state, test_alloc, test_realloc, test_free}; re_facts_t *facts = re_facts_create(NULL, NULL);
    re_rete_condition_t conditions[2] = {{{"A", 1u}, RE_COMPARE_GT, {RE_VALUE_INT64, {.int64_value = 0}}}, {{"B", 1u}, RE_COMPARE_GT, {RE_VALUE_INT64, {.int64_value = 0}}}}; re_rete_network_t *network = NULL;
    ASSERT_EQ(re_rete_network_create(facts, conditions, &allocator, &network), RE_STATUS_OK); state.fail_at = state.calls + 1u;
    { re_fact_id_t id; re_value_t one = {RE_VALUE_INT64, {.int64_value = 1}}; ASSERT_EQ(re_facts_insert(facts, text("A"), &one, &id), RE_STATUS_OUT_OF_MEMORY); }
    ASSERT_EQ(re_rete_activation_count(network), 0u); state.fail_at = 0u; re_rete_network_destroy_internal(network); re_facts_destroy(facts);
}

TEST(fact_callback_failure_propagates_without_stale_notification_state) {
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_subscription_t *subscription = NULL;
    re_fact_id_t id;
    re_value_t value = {RE_VALUE_INT64, {.int64_value = 1}};
    ASSERT_EQ(re_facts_subscribe(facts, failing_fact_callback, NULL, &subscription), RE_STATUS_OK);
    ASSERT_EQ(re_facts_insert(facts, text("A"), &value, &id), RE_STATUS_ERROR);
    ASSERT_FALSE(facts->notifying);
    ASSERT_EQ(re_facts_retract(facts, id), RE_STATUS_ERROR);
    re_subscription_destroy(subscription);
    re_facts_destroy(facts);
}

TEST(transaction_notification_failure_propagates_and_invalidates_rete_state) {
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_rete_network_t *network = NULL;
    re_fact_txn_t *transaction = NULL;
    re_subscription_t *subscription = NULL;
    re_value_t value = {RE_VALUE_INT64, {.int64_value = 1}};
    re_rete_condition_t conditions[2] = {
        {{"A", 1u}, RE_COMPARE_GT, {RE_VALUE_INT64, {.int64_value = 0}}},
        {{"B", 1u}, RE_COMPARE_EQ, {RE_VALUE_INT64, {.int64_value = 2}}}
    };
    ASSERT_EQ(re_rete_network_create(facts, conditions, NULL, &network), RE_STATUS_OK);
    ASSERT_EQ(re_facts_subscribe(facts, failing_fact_callback, NULL, &subscription), RE_STATUS_OK);
    ASSERT_EQ(re_facts_begin(facts, &transaction), RE_STATUS_OK);
    ASSERT_EQ(re_facts_txn_set(transaction, text("A"), &value), RE_STATUS_OK);
    ASSERT_EQ(re_facts_commit(transaction), RE_STATUS_ERROR);
    ASSERT_FALSE(facts->notifying);
    ASSERT_EQ(re_rete_activation_count(network), 0u);
    ASSERT_EQ(re_facts_get(facts, text("A"), &value), RE_STATUS_OK);
    ASSERT_EQ(value.as.int64_value, 1);
    re_subscription_destroy(subscription);
    re_rete_network_destroy_internal(network);
    re_facts_destroy(facts);
}

TEST(facts_destroy_detaches_engine_owned_rete_network) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_rete_network_t *network = NULL;
    re_value_t one = {RE_VALUE_INT64, {.int64_value = 1}};
    re_value_t two = {RE_VALUE_INT64, {.int64_value = 2}};
    ASSERT_EQ(re_program_load(NULL, text("rule \"Join\" { when A > 0 and B == 2 then Result = 1; }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("A"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("B"), &two), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_engine_rete_network(engine, &network), RE_STATUS_OK);
    ASSERT_TRUE(facts->rete_network == network);
    re_facts_destroy(facts);
    ASSERT_TRUE(engine->rete_network == NULL);
    re_engine_destroy(engine);
}

TEST(deep_condition_token_enumeration_is_complete) {
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_rete_network_t *network = NULL;
    re_rete_condition_t conditions[8];
    size_t i;
    ASSERT_NOT_NULL(facts);
    for (i = 0u; i < 8u; ++i) {
        static const char names[] = "ABCDEFGH";
        conditions[i] = (re_rete_condition_t){{&names[i], 1u}, RE_COMPARE_GT,
            {RE_VALUE_INT64, {.int64_value = 0}}};
    }
    ASSERT_EQ(re_rete_network_create_conditions(facts, conditions, 8u, NULL, &network), RE_STATUS_OK);
    for (i = 0u; i < 8u; ++i) {
        re_fact_id_t id;
        re_value_t value = {RE_VALUE_INT64, {.int64_value = 1}};
        char name[2] = {(char)('A' + i), '\0'};
        ASSERT_EQ(re_facts_insert(facts, text(name), &value, &id), RE_STATUS_OK);
        ASSERT_EQ(re_facts_insert(facts, text(name), &value, &id), RE_STATUS_OK);
    }
    ASSERT_TRUE(re_rete_activation_count(network) > 0u);
    re_rete_network_destroy_internal(network);
    re_facts_destroy(facts);
}

TEST(repeated_condition_network_creation_replaces_owner_safely) {
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_rete_network_t *first = NULL;
    re_rete_network_t *second = NULL;
    ASSERT_EQ(make_network(facts, &first), RE_STATUS_OK);
    ASSERT_EQ(make_network(facts, &second), RE_STATUS_BUSY);
    ASSERT_TRUE(facts->rete_network == first);
    ASSERT_EQ(re_facts_set(facts, text("A"), &(re_value_t){RE_VALUE_INT64, {.int64_value = 1}}), RE_STATUS_OK);
    ASSERT_EQ(re_rete_activation_count(second), 0u);
    re_rete_network_destroy_internal(second);
    re_facts_destroy(facts);
}

TEST(retained_network_handle_survives_owner_replacement) {
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_rete_network_t *first = NULL;
    re_rete_network_t *second = NULL;
    re_fact_id_t a, b;
    re_value_t one = {RE_VALUE_INT64, {.int64_value = 1}};
    re_value_t two = {RE_VALUE_INT64, {.int64_value = 2}};
    ASSERT_EQ(make_network(facts, &first), RE_STATUS_OK);
    ASSERT_EQ(re_facts_insert(facts, text("A"), &one, &a), RE_STATUS_OK);
    ASSERT_EQ(re_facts_insert(facts, text("B"), &two, &b), RE_STATUS_OK);
    ASSERT_EQ(make_network(facts, &second), RE_STATUS_BUSY);
    ASSERT_EQ(re_rete_activation_get(first, 0u, &(re_rete_activation_t){0}), RE_STATUS_OK);
    re_rete_network_destroy_internal(first);
    re_facts_destroy(facts);
}

TEST(insert_existing_name_emits_only_update) {
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_subscription_t *subscription = NULL;
    event_state_t events = {0u, {0}};
    re_fact_id_t id;
    re_value_t value = {RE_VALUE_INT64, {.int64_value = 1}};
    ASSERT_EQ(re_facts_subscribe(facts, record_fact_event, &events, &subscription), RE_STATUS_OK);
    ASSERT_EQ(re_facts_insert(facts, text("A"), &value, &id), RE_STATUS_OK);
    ASSERT_EQ(re_facts_insert(facts, text("A"), &value, &id), RE_STATUS_OK);
    ASSERT_EQ(events.count, 2u);
    ASSERT_EQ(events.kinds[0], RE_FACT_INSERT);
    ASSERT_EQ(events.kinds[1], RE_FACT_UPDATE);
    re_subscription_destroy(subscription);
    re_facts_destroy(facts);
}

TEST(structured_value_copy_enforces_depth_bound) {
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_handle_t *nested = NULL;
    re_value_handle_t *parent = NULL;
    size_t depth;
    ASSERT_EQ(re_value_create_array(facts, &nested), RE_STATUS_OK);
    for (depth = 0u; depth < 64u; ++depth) {
        ASSERT_EQ(re_value_create_array(facts, &parent), RE_STATUS_OK);
        ASSERT_EQ(re_value_array_append_value(parent, nested), RE_STATUS_OK);
        re_value_destroy(nested);
        nested = parent;
        parent = NULL;
    }
    ASSERT_EQ(re_value_create_array(facts, &parent), RE_STATUS_OK);
    ASSERT_EQ(re_value_array_append_value(parent, nested), RE_STATUS_LIMIT);
    re_value_destroy(parent);
    re_value_destroy(nested);
    re_facts_destroy(facts);
}

TEST_MAIN_BEGIN()
    RUN_TEST(compiled_network_persists_across_runs);
    RUN_TEST(structured_fact_changes_emit_owned_lifecycle_events);
    RUN_TEST(engine_destroy_clears_rete_owner);
    RUN_TEST(external_network_survives_engine_run_and_install);
    RUN_TEST(external_network_survives_engine_destruction);
    RUN_TEST(facts_destroy_detaches_external_network_without_freeing_it);
    RUN_TEST(unrelated_updates_preserve_memories_and_related_changes_propagate);
    RUN_TEST(unchanged_lineage_preserves_activation_sequence_across_unrelated_events);
    RUN_TEST(token_provenance_and_transaction_effective_change);
    RUN_TEST(allocation_failure_leaves_existing_network_consistent);
    RUN_TEST(fact_callback_failure_propagates_without_stale_notification_state);
    RUN_TEST(transaction_notification_failure_propagates_and_invalidates_rete_state);
    RUN_TEST(facts_destroy_detaches_engine_owned_rete_network);
    RUN_TEST(deep_condition_token_enumeration_is_complete);
    RUN_TEST(repeated_condition_network_creation_replaces_owner_safely);
    RUN_TEST(retained_network_handle_survives_owner_replacement);
    RUN_TEST(insert_existing_name_emits_only_update);
    RUN_TEST(structured_value_copy_enforces_depth_bound);
TEST_MAIN_END()
