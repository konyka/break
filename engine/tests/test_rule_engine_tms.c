#include "test_framework.h"
#include <rule_engine/rule_engine.h>
#include "../src/rule_engine/re_internal.h"
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

TEST(tms_multi_justification_survives_single_premise_retraction) {
    /* Upstream tms.rs/tms_test.rs test_multiple_justifications: a fact with
     * two logical justifications is retracted only when ALL are invalid. */
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_fact_id_t p1, p2, derived;
    re_value_t value = number(2), result = {RE_VALUE_NONE, {0}};
    insert_explicit(facts, "p1", &p1);
    insert_explicit(facts, "p2", &p2);
    ASSERT_EQ(re_facts_insert_logical(facts, text("d"), &value, text("Rule1"), &p1, 1u, &derived), RE_STATUS_OK);
    ASSERT_EQ(re_facts_justification_add(facts, derived, text("Rule2"), &p2, 1u), RE_STATUS_OK);
    ASSERT_EQ(re_facts_justification_count(facts, derived), 2u);
    /* Adding a justification never re-derives the value (upstream parity). */
    ASSERT_EQ(re_facts_get(facts, text("d"), &result), RE_STATUS_OK);
    ASSERT_EQ(result.as.int64_value, 2);
    ASSERT_EQ(re_facts_retract(facts, p1), RE_STATUS_OK);
    /* One valid justification remains: the fact survives. */
    ASSERT_EQ(re_facts_get(facts, text("d"), &result), RE_STATUS_OK);
    ASSERT_EQ(re_facts_justification_count(facts, derived), 1u);
    ASSERT_EQ(re_facts_retract(facts, p2), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("d"), &result), RE_STATUS_NOT_FOUND);
    re_facts_destroy(facts);
}

TEST(tms_diamond_dependency_cascades_fully) {
    /* Upstream tms_test.rs test_diamond_dependency: A -> B, A -> C, B+C -> D;
     * retracting A cascades through both branches down to D. */
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_fact_id_t a, b, c, d;
    re_fact_id_t bc[2];
    re_value_t value = number(1);
    insert_explicit(facts, "A", &a);
    ASSERT_EQ(re_facts_insert_logical(facts, text("B"), &value, text("RuleAtoB"), &a, 1u, &b), RE_STATUS_OK);
    ASSERT_EQ(re_facts_insert_logical(facts, text("C"), &value, text("RuleAtoC"), &a, 1u, &c), RE_STATUS_OK);
    bc[0] = b; bc[1] = c;
    ASSERT_EQ(re_facts_insert_logical(facts, text("D"), &value, text("RuleBCtoD"), bc, 2u, &d), RE_STATUS_OK);
    ASSERT_EQ(re_facts_justification_count(facts, d), 1u);
    ASSERT_EQ(re_facts_retract(facts, a), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("B"), &(re_value_t){0}), RE_STATUS_NOT_FOUND);
    ASSERT_EQ(re_facts_get(facts, text("C"), &(re_value_t){0}), RE_STATUS_NOT_FOUND);
    ASSERT_EQ(re_facts_get(facts, text("D"), &(re_value_t){0}), RE_STATUS_NOT_FOUND);
    re_facts_destroy(facts);
}

TEST(tms_explicit_insert_coexists_with_logical_support) {
    /* Upstream tms.rs keeps BOTH justification lists: a fact with an explicit
     * assertion and logical justifications survives premise retraction,
     * because explicit support is unconditionally valid (explicit beats
     * logical). Before B1 the local cascade retracted such facts. */
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_fact_id_t premise, derived, asserted;
    re_value_t value = number(2), host = number(9), result = {RE_VALUE_NONE, {0}};
    insert_explicit(facts, "p", &premise);
    ASSERT_EQ(re_facts_insert_logical(facts, text("d"), &value, text("R"), &premise, 1u, &derived), RE_STATUS_OK);
    /* Host re-asserts the derived fact: both supports now coexist. The
     * explicit assertion keeps the identity and the logical provenance. */
    ASSERT_EQ(re_facts_insert(facts, text("d"), &host, &asserted), RE_STATUS_OK);
    ASSERT_EQ(asserted.slot, derived.slot);
    ASSERT_EQ(asserted.generation, derived.generation);
    ASSERT_TRUE(re_facts_is_logical(facts, derived));
    ASSERT_EQ(re_facts_justification_count(facts, derived), 1u);
    ASSERT_EQ(re_facts_retract(facts, premise), RE_STATUS_OK);
    /* Explicit support survives; the logical justification is gone. The fact
     * stays logical (upstream keeps its logical_facts membership until the
     * fact itself is retracted) but has no rule provenance left. */
    ASSERT_EQ(re_facts_get(facts, text("d"), &result), RE_STATUS_OK);
    ASSERT_EQ(result.as.int64_value, 9);
    ASSERT_TRUE(re_facts_is_logical(facts, derived));
    ASSERT_EQ(re_facts_justification_count(facts, derived), 0u);
    ASSERT_EQ(re_facts_provenance_get(facts, derived,
        &(re_fact_provenance_t){sizeof(re_fact_provenance_t), 0u, {NULL, 0u}, 0u, NULL}),
        RE_STATUS_NOT_FOUND);
    re_facts_destroy(facts);
}

TEST(tms_justification_remove_rejects_empty_rule_and_keeps_explicit_support) {
    /* Regression for review finding I1: justification_remove mirrors the
     * add-side validation, so an empty rule cannot match and delete an
     * explicit-support marker (same_text equates size 0 with the marker's
     * empty rule); explicit support is unconditionally valid and is only
     * removed by retracting the fact itself. */
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_fact_id_t premise, derived, dependent;
    re_value_t value = number(2), host = number(9), result = {RE_VALUE_NONE, {0}};
    insert_explicit(facts, "p", &premise);
    ASSERT_EQ(re_facts_insert_logical(facts, text("d"), &value, text("R"), &premise, 1u, &derived), RE_STATUS_OK);
    ASSERT_EQ(re_facts_insert(facts, text("d"), &host, &derived), RE_STATUS_OK);
    ASSERT_EQ(re_facts_justification_remove(facts, derived, (re_string_t){NULL, 0u}, NULL, 0u),
        RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_facts_justification_remove(facts, derived, text(""), NULL, 0u),
        RE_STATUS_INVALID_ARGUMENT);
    /* The marker survived: explicit support still holds the fact after the
     * logical justification cascades away. */
    ASSERT_EQ(re_facts_retract(facts, premise), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("d"), &result), RE_STATUS_OK);
    ASSERT_EQ(result.as.int64_value, 9);
    ASSERT_TRUE(re_facts_is_logical(facts, derived));
    /* Directly retracting a marker-only survivor cleans the marker and
     * cascades to dependents of the explicitly-held fact. */
    ASSERT_EQ(re_facts_insert_logical(facts, text("e"), &value, text("RE"), &derived, 1u, &dependent), RE_STATUS_OK);
    ASSERT_EQ(re_facts_retract(facts, derived), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("d"), &result), RE_STATUS_NOT_FOUND);
    ASSERT_EQ(re_facts_get(facts, text("e"), &result), RE_STATUS_NOT_FOUND);
    re_facts_destroy(facts);
}

TEST(tms_logical_derivation_on_explicit_fact_keeps_both_supports) {
    /* Upstream parity for the reverse order: insert_logical on a
     * host-asserted fact records the logical justification AND keeps the
     * explicit support (before B1 the justification was silently dropped). */
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_fact_id_t premise, tier;
    re_value_t host = number(1), derived_value = number(7), result = {RE_VALUE_NONE, {0}};
    re_fact_provenance_t provenance = {sizeof(provenance), 0u, {NULL, 0u}, 0u, NULL};
    insert_explicit(facts, "spent", &premise);
    ASSERT_EQ(re_facts_insert(facts, text("tier"), &host, &tier), RE_STATUS_OK);
    ASSERT_EQ(re_facts_insert_logical(facts, text("tier"), &derived_value,
        text("InferPremium"), &premise, 1u, &tier), RE_STATUS_OK);
    ASSERT_TRUE(re_facts_is_logical(facts, tier));
    ASSERT_EQ(re_facts_justification_count(facts, tier), 1u);
    ASSERT_EQ(re_facts_provenance_get(facts, tier, &provenance), RE_STATUS_OK);
    ASSERT_EQ(provenance.producer_rule.size, 12u);
    ASSERT_EQ(provenance.premise_count, 1u);
    ASSERT_EQ(provenance.premises[0].slot, premise.slot);
    /* The explicit support keeps the fact (and the derived value) alive. */
    ASSERT_EQ(re_facts_retract(facts, premise), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("tier"), &result), RE_STATUS_OK);
    ASSERT_EQ(result.as.int64_value, 7);
    ASSERT_EQ(re_facts_justification_count(facts, tier), 0u);
    re_facts_destroy(facts);
}

TEST(tms_explicit_support_survives_transaction_commit) {
    /* Explicit support rides the TMS clone, so a premise retracted inside a
     * transaction cascades in the staged store exactly like outside it. */
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_fact_txn_t *txn = NULL;
    re_fact_id_t premise, derived;
    re_value_t value = number(2), host = number(9);
    insert_explicit(facts, "p", &premise);
    ASSERT_EQ(re_facts_insert_logical(facts, text("d"), &value, text("R"), &premise, 1u, &derived), RE_STATUS_OK);
    ASSERT_EQ(re_facts_insert(facts, text("d"), &host, &derived), RE_STATUS_OK);
    ASSERT_EQ(re_facts_begin(facts, &txn), RE_STATUS_OK);
    ASSERT_EQ(re_facts_retract(facts, premise), RE_STATUS_OK);
    ASSERT_EQ(re_facts_commit(txn), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("d"), &(re_value_t){0}), RE_STATUS_OK);
    ASSERT_EQ(re_facts_justification_count(facts, derived), 0u);
    re_facts_destroy(facts);
}

TEST(tms_stats_local_equivalent_counts) {
    /* Upstream tms_test.rs test_tms_stats reads a global stats struct
     * {total, logical, explicit, retracted}; the local surface exposes no
     * such aggregate, so this pins the per-fact equivalents: 4 explicit
     * asserts carry no logical justification and are not logical, 2 logical
     * derivations carry exactly one each. */
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_fact_id_t ids[4];
    re_fact_id_t l1, l2;
    re_value_t value = number(1);
    const char *names[4] = {"e0", "e1", "e2", "base"};
    size_t i;
    for (i = 0u; i < 4u; ++i) insert_explicit(facts, names[i], &ids[i]);
    ASSERT_EQ(re_facts_insert_logical(facts, text("l0"), &value, text("Rule0"), &ids[3], 1u, &l1), RE_STATUS_OK);
    ASSERT_EQ(re_facts_insert_logical(facts, text("l1"), &value, text("Rule1"), &ids[3], 1u, &l2), RE_STATUS_OK);
    for (i = 0u; i < 4u; ++i) {
        ASSERT_FALSE(re_facts_is_logical(facts, ids[i]));
        ASSERT_EQ(re_facts_justification_count(facts, ids[i]), 0u);
    }
    ASSERT_TRUE(re_facts_is_logical(facts, l1));
    ASSERT_TRUE(re_facts_is_logical(facts, l2));
    ASSERT_EQ(re_facts_justification_count(facts, l1), 1u);
    ASSERT_EQ(re_facts_justification_count(facts, l2), 1u);
    re_facts_destroy(facts);
}

TEST(tms_cascade_cycle_terminates) {
    /* Upstream tms.rs permits cyclic justifications in the map and terminates
     * retract_with_cascade via the retracted-set guard. The local public API
     * is stricter — it rejects cycles at insertion (RE_STATUS_LIMIT, see
     * tms_indirect_cycles_are_rejected) — so this test attaches the back edge
     * whitebox, as upstream's map would hold it, and pins that the local
     * eager-removal cascade terminates and settles identically. */
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_fact_id_t external, a, b;
    re_value_t value = number(2);
    re_tms_justification_t *item;
    insert_explicit(facts, "p", &external);
    ASSERT_EQ(re_facts_insert_logical(facts, text("a"), &value, text("RP"), &external, 1u, &a), RE_STATUS_OK);
    ASSERT_EQ(re_facts_insert_logical(facts, text("b"), &value, text("RA"), &a, 1u, &b), RE_STATUS_OK);
    /* The public guard rejects exactly this edge... */
    ASSERT_EQ(re_facts_justification_add(facts, a, text("RB"), &b, 1u), RE_STATUS_LIMIT);
    /* ...so attach a <- b directly, mirroring upstream's permissive map. */
    ASSERT_NOT_NULL(facts->tms);
    ASSERT_TRUE(facts->tms->count < facts->tms->capacity);
    item = &facts->tms->items[facts->tms->count++];
    memset(item, 0, sizeof(*item));
    item->derived = a;
    item->producer_rule_size = 2u;
    item->producer_rule = re_alloc(&facts->tms->allocator, 3u);
    ASSERT_NOT_NULL(item->producer_rule);
    memcpy(item->producer_rule, "RB", 3u);
    item->premise_count = 1u;
    item->premises = re_alloc(&facts->tms->allocator, sizeof(*item->premises));
    ASSERT_NOT_NULL(item->premises);
    item->premises[0] = b;
    ASSERT_EQ(re_facts_justification_count(facts, a), 2u);
    /* External premise retracted: a keeps its cyclic support from b, exactly
     * as upstream's is_valid rules (no premise of either is retracted). */
    ASSERT_EQ(re_facts_retract(facts, external), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("a"), &(re_value_t){0}), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("b"), &(re_value_t){0}), RE_STATUS_OK);
    /* Directly retracting a drains the cycle: b's only justification named
     * a. Eager item removal is the local termination guarantee. */
    ASSERT_EQ(re_facts_retract(facts, a), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("a"), &(re_value_t){0}), RE_STATUS_NOT_FOUND);
    ASSERT_EQ(re_facts_get(facts, text("b"), &(re_value_t){0}), RE_STATUS_NOT_FOUND);
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
    RUN_TEST(tms_multi_justification_survives_single_premise_retraction);
    RUN_TEST(tms_diamond_dependency_cascades_fully);
    RUN_TEST(tms_explicit_insert_coexists_with_logical_support);
    RUN_TEST(tms_logical_derivation_on_explicit_fact_keeps_both_supports);
    RUN_TEST(tms_explicit_support_survives_transaction_commit);
    RUN_TEST(tms_stats_local_equivalent_counts);
    RUN_TEST(tms_cascade_cycle_terminates);
    RUN_TEST(tms_justification_remove_rejects_empty_rule_and_keeps_explicit_support);
TEST_MAIN_END()
