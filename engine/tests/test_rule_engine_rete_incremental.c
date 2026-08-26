#include "test_framework.h"
#include "../src/rule_engine/re_internal.h"
#include <stdlib.h>

static re_string_t text(const char *value) { return (re_string_t){value, strlen(value)}; }

typedef struct alloc_state_t { size_t calls; size_t fail_at; } alloc_state_t;
static void *test_alloc(void *context, size_t size) { alloc_state_t *state = context; ++state->calls; return state->fail_at == state->calls ? NULL : malloc(size); }
static void *test_realloc(void *context, void *memory, size_t size) { alloc_state_t *state = context; ++state->calls; return state->fail_at == state->calls ? NULL : realloc(memory, size); }
static void test_free(void *context, void *memory) { (void)context; free(memory); }
static re_status_t count_action(re_engine_t *engine, re_facts_t *facts, const re_rule_event_t *event, void *context) { (void)engine; (void)facts; (void)event; ++*(size_t *)context; return RE_STATUS_OK; }

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
    { re_fact_id_t id; re_value_t one = {RE_VALUE_INT64, {.int64_value = 1}}; ASSERT_EQ(re_facts_insert(facts, text("A"), &one, &id), RE_STATUS_OK); }
    ASSERT_EQ(re_rete_activation_count(network), 0u); state.fail_at = 0u; re_rete_network_destroy_internal(network); re_facts_destroy(facts);
}

TEST_MAIN_BEGIN()
    RUN_TEST(compiled_network_persists_across_runs);
    RUN_TEST(unrelated_updates_preserve_memories_and_related_changes_propagate);
    RUN_TEST(token_provenance_and_transaction_effective_change);
    RUN_TEST(allocation_failure_leaves_existing_network_consistent);
TEST_MAIN_END()
