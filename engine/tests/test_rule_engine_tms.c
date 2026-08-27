#include "test_framework.h"
#include <rule_engine/rule_engine.h>
#include <string.h>

static re_string_t text(const char *value) { return (re_string_t){value, strlen(value)}; }
static re_value_t number(int64_t value) { return (re_value_t){RE_VALUE_INT64, {.int64_value = value}}; }

static void insert_explicit(re_facts_t *facts, const char *name, re_fact_id_t *out) {
    re_value_t value = number(1);
    ASSERT_EQ(re_facts_insert(facts, text(name), &value, out), RE_STATUS_OK);
}

TEST(engine_rete_activation_derives_logical_fact_with_exact_lineage) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_value_t one = number(1), two = number(2), result;
    re_fact_id_t first, second;
    re_fact_provenance_t provenance = {sizeof(provenance), 0u, {NULL, 0u}, 0u, NULL};

    ASSERT_EQ(re_program_load(NULL, text("rule \"Join\" { when A > 0 and B == 2 then Derived = 7; }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_facts_insert(facts, text("A"), &one, &first), RE_STATUS_OK);
    ASSERT_EQ(re_facts_insert(facts, text("B"), &two, &second), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("Derived"), &result), RE_STATUS_OK);
    ASSERT_EQ(result.as.int64_value, 7);
    ASSERT_TRUE(re_facts_is_logical(facts, (re_fact_id_t){2u, 1u}));
    ASSERT_EQ(re_facts_provenance_get(facts, (re_fact_id_t){2u, 1u}, &provenance), RE_STATUS_OK);
    ASSERT_EQ(provenance.producer_rule.size, 4u);
    ASSERT_EQ(provenance.premise_count, 2u);
    ASSERT_EQ(provenance.premises[0].slot, first.slot);
    ASSERT_EQ(provenance.premises[1].slot, second.slot);
    ASSERT_EQ(re_facts_retract(facts, first), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("Derived"), &result), RE_STATUS_NOT_FOUND);
    re_engine_destroy(engine);
    re_facts_destroy(facts);
}

TEST(tms_distinguishes_explicit_and_logical_facts) {
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_fact_id_t premise, derived;
    re_value_t value = number(2);
    re_fact_provenance_t provenance = {sizeof(provenance), 0u, {NULL, 0u}, 0u, NULL};
    insert_explicit(facts, "premise", &premise);
    ASSERT_EQ(re_facts_insert_logical(facts, text("derived"), &value, text("R"), &premise, 1u, &derived), RE_STATUS_OK);
    ASSERT_FALSE(re_facts_is_logical(facts, premise));
    ASSERT_TRUE(re_facts_is_logical(facts, derived));
    ASSERT_EQ(re_facts_provenance_get(facts, derived, &provenance), RE_STATUS_OK);
    ASSERT_EQ(provenance.premise_count, 1u);
    ASSERT_EQ(provenance.producer_rule.size, 1u);
    re_facts_destroy(facts);
}

TEST(tms_one_justification_keeps_fact_alive) {
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_fact_id_t premise, derived;
    re_value_t value = number(2);
    insert_explicit(facts, "premise", &premise);
    ASSERT_EQ(re_facts_insert_logical(facts, text("derived"), &value, text("R"), &premise, 1u, &derived), RE_STATUS_OK);
    ASSERT_EQ(re_facts_justification_count(facts, derived), 1u);
    ASSERT_EQ(re_facts_justification_remove(facts, derived, text("R"), &premise, 1u), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("derived"), &(re_value_t){0}), RE_STATUS_NOT_FOUND);
    re_facts_destroy(facts);
}

TEST(tms_multiple_justifications_and_duplicate_coalescing) {
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_fact_id_t a, b, derived;
    re_value_t value = number(2);
    insert_explicit(facts, "a", &a); insert_explicit(facts, "b", &b);
    ASSERT_EQ(re_facts_insert_logical(facts, text("d"), &value, text("R"), &a, 1u, &derived), RE_STATUS_OK);
    ASSERT_EQ(re_facts_insert_logical(facts, text("d"), &value, text("R"), &a, 1u, &derived), RE_STATUS_OK);
    ASSERT_EQ(re_facts_justification_add(facts, derived, text("R2"), &b, 1u), RE_STATUS_OK);
    ASSERT_EQ(re_facts_justification_count(facts, derived), 2u);
    ASSERT_EQ(re_facts_justification_remove(facts, derived, text("R"), &a, 1u), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("d"), &(re_value_t){0}), RE_STATUS_OK);
    ASSERT_EQ(re_facts_justification_remove(facts, derived, text("R2"), &b, 1u), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("d"), &(re_value_t){0}), RE_STATUS_NOT_FOUND);
    re_facts_destroy(facts);
}

TEST(tms_indirect_cycles_are_rejected) {
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_fact_id_t premise, first, second;
    re_value_t value = number(2);
    insert_explicit(facts, "p", &premise);
    ASSERT_EQ(re_facts_insert_logical(facts, text("one"), &value, text("R1"), &premise, 1u, &first), RE_STATUS_OK);
    ASSERT_EQ(re_facts_insert_logical(facts, text("two"), &value, text("R2"), &first, 1u, &second), RE_STATUS_OK);
    ASSERT_EQ(re_facts_justification_add(facts, first, text("R3"), &second, 1u), RE_STATUS_LIMIT);
    re_facts_destroy(facts);
}

TEST(tms_cascades_and_rejects_stale_premises_and_cycles) {
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_fact_id_t premise, first, second, stale, old_premise;
    re_value_t one = number(1), two = number(2), three = number(3), four = number(4);
    insert_explicit(facts, "p", &premise);
    ASSERT_EQ(re_facts_insert_logical(facts, text("one"), &one, text("R1"), &premise, 1u, &first), RE_STATUS_OK);
    ASSERT_EQ(re_facts_insert_logical(facts, text("two"), &two, text("R2"), &first, 1u, &second), RE_STATUS_OK);
    ASSERT_EQ(re_facts_retract(facts, premise), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("one"), &(re_value_t){0}), RE_STATUS_NOT_FOUND);
    ASSERT_EQ(re_facts_get(facts, text("two"), &(re_value_t){0}), RE_STATUS_NOT_FOUND);
    ASSERT_EQ(re_facts_insert(facts, text("p"), &three, &stale), RE_STATUS_OK);
    old_premise = premise;
    ASSERT_EQ(re_facts_justification_add(facts, second, text("bad"), &old_premise, 1u), RE_STATUS_NOT_FOUND);
    ASSERT_EQ(re_facts_insert_logical(facts, text("cycle"), &four, text("R"), &stale, 1u, &first), RE_STATUS_OK);
    ASSERT_EQ(re_facts_justification_add(facts, first, text("cycle"), &first, 1u), RE_STATUS_LIMIT);
    re_facts_destroy(facts);
}

TEST(tms_reinserted_fact_is_explicit_after_logical_retraction) {
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_fact_id_t premise, derived, replacement;
    re_value_t value = number(2);

    insert_explicit(facts, "premise", &premise);
    ASSERT_EQ(re_facts_insert_logical(facts, text("derived"), &value, text("R"),
        &premise, 1u, &derived), RE_STATUS_OK);
    ASSERT_EQ(re_facts_retract(facts, premise), RE_STATUS_OK);
    ASSERT_EQ(re_facts_insert(facts, text("derived"), &value, &replacement), RE_STATUS_OK);
    ASSERT_FALSE(re_facts_is_logical(facts, replacement));
    ASSERT_EQ(re_facts_justification_count(facts, replacement), 0u);
    re_facts_destroy(facts);
}

TEST(tms_direct_logical_retraction_drops_its_justifications) {
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_fact_id_t premise, derived;
    re_value_t value = number(2);

    insert_explicit(facts, "premise", &premise);
    ASSERT_EQ(re_facts_insert_logical(facts, text("derived"), &value, text("R"),
        &premise, 1u, &derived), RE_STATUS_OK);
    ASSERT_EQ(re_facts_retract(facts, derived), RE_STATUS_OK);
    ASSERT_EQ(re_facts_justification_count(facts, derived), 0u);
    ASSERT_EQ(re_facts_insert(facts, text("derived"), &value, &derived), RE_STATUS_OK);
    ASSERT_FALSE(re_facts_is_logical(facts, derived));
    ASSERT_EQ(re_facts_provenance_get(facts, derived,
        &(re_fact_provenance_t){sizeof(re_fact_provenance_t), 0u, {NULL, 0u}, 0u, NULL}),
        RE_STATUS_NOT_FOUND);
    re_facts_destroy(facts);
}

TEST(tms_transaction_rollback_leaves_store_unchanged) {
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_fact_txn_t *txn = NULL;
    re_fact_id_t premise, derived;
    re_value_t value = number(1);
    insert_explicit(facts, "p", &premise);
    ASSERT_EQ(re_facts_begin(facts, &txn), RE_STATUS_OK);
    {
        re_status_t status = re_facts_insert_logical(facts, text("d"), &value, text("R"), &premise, 1u, &derived);
        ASSERT_EQ(status, RE_STATUS_OK);
    }
    re_facts_rollback(txn);
    ASSERT_EQ(re_facts_get(facts, text("d"), &(re_value_t){0}), RE_STATUS_NOT_FOUND);
    ASSERT_EQ(re_facts_justification_count(facts, derived), 0u);
    re_facts_destroy(facts);
}

TEST(tms_transaction_updates_logical_target_in_staged_store) {
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_fact_txn_t *txn = NULL;
    re_fact_id_t premise, derived;
    re_value_t value = number(1), replacement = number(2);
    insert_explicit(facts, "p", &premise);
    ASSERT_EQ(re_facts_insert_logical(facts, text("d"), &value, text("R"), &premise, 1u, &derived), RE_STATUS_OK);
    ASSERT_EQ(re_facts_begin(facts, &txn), RE_STATUS_OK);
    ASSERT_EQ(re_facts_update(facts, derived, &replacement), RE_STATUS_OK);
    ASSERT_EQ(re_facts_justification_add(facts, derived, text("R2"), &premise, 1u), RE_STATUS_OK);
    ASSERT_EQ(re_facts_justification_count(facts, derived), 2u);
    re_facts_rollback(txn);
    ASSERT_EQ(re_facts_justification_count(facts, derived), 1u);
    re_facts_destroy(facts);
}

TEST(tms_transaction_commit_preserves_live_justifications) {
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_fact_txn_t *txn = NULL;
    re_fact_id_t premise, derived;
    re_value_t value = number(1);

    insert_explicit(facts, "premise", &premise);
    ASSERT_EQ(re_facts_insert_logical(facts, text("derived"), &value, text("R"),
        &premise, 1u, &derived), RE_STATUS_OK);
    ASSERT_EQ(re_facts_begin(facts, &txn), RE_STATUS_OK);
    ASSERT_EQ(re_facts_commit(txn), RE_STATUS_OK);
    ASSERT_EQ(re_facts_justification_count(facts, derived), 1u);
    ASSERT_EQ(re_facts_retract(facts, premise), RE_STATUS_OK);
    ASSERT_EQ(re_facts_justification_count(facts, derived), 0u);
    ASSERT_EQ(re_facts_get(facts, text("derived"), &(re_value_t){0}), RE_STATUS_NOT_FOUND);
    re_facts_destroy(facts);
}

TEST_MAIN_BEGIN()
    RUN_TEST(engine_rete_activation_derives_logical_fact_with_exact_lineage);
    RUN_TEST(tms_distinguishes_explicit_and_logical_facts);
    RUN_TEST(tms_one_justification_keeps_fact_alive);
    RUN_TEST(tms_multiple_justifications_and_duplicate_coalescing);
    RUN_TEST(tms_cascades_and_rejects_stale_premises_and_cycles);
    RUN_TEST(tms_reinserted_fact_is_explicit_after_logical_retraction);
    RUN_TEST(tms_direct_logical_retraction_drops_its_justifications);
    RUN_TEST(tms_indirect_cycles_are_rejected);
    RUN_TEST(tms_transaction_rollback_leaves_store_unchanged);
    RUN_TEST(tms_transaction_updates_logical_target_in_staged_store);
    RUN_TEST(tms_transaction_commit_preserves_live_justifications);
TEST_MAIN_END()
