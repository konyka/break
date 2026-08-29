#include "test_framework.h"
#include "../src/rule_engine/re_internal.h"
#include <stdlib.h>

static re_fact_id_t fact_id(uint64_t slot, uint64_t generation) {
    re_fact_id_t id = {slot, generation};
    return id;
}

static re_string_t text(const char *value) {
    return (re_string_t){value, strlen(value)};
}

TEST(agenda_create_destroy) {
    re_agenda_t *agenda = NULL;

    ASSERT_EQ(re_agenda_create_internal(NULL, NULL), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_agenda_create_internal(NULL, &agenda), RE_STATUS_OK);
    ASSERT_NOT_NULL(agenda);
    ASSERT_EQ(agenda->pending_count, 0u);
    ASSERT_EQ(agenda->fired_count, 0u);
    ASSERT_EQ(agenda->next_sequence, 0u);
    re_agenda_destroy_internal(agenda);
    re_agenda_destroy_internal(NULL);
}

TEST(agenda_push_dedups_pending_order_insensitive) {
    re_agenda_t *agenda = NULL;
    re_fact_id_t premises[2] = {fact_id(3u, 1u), fact_id(1u, 2u)};
    re_fact_id_t reversed[2] = {fact_id(1u, 2u), fact_id(3u, 1u)};

    ASSERT_EQ(re_agenda_create_internal(NULL, &agenda), RE_STATUS_OK);
    ASSERT_EQ(re_agenda_push(agenda, 2u, 5, premises, 2u), RE_STATUS_OK);
    ASSERT_EQ(re_agenda_push(agenda, 2u, 5, reversed, 2u), RE_STATUS_OK);
    ASSERT_EQ(agenda->pending_count, 1u);
    /* Same rule with a different premise set is a distinct activation. */
    ASSERT_EQ(re_agenda_push(agenda, 2u, 5, premises, 1u), RE_STATUS_OK);
    ASSERT_EQ(agenda->pending_count, 2u);
    /* Same premises under another rule is a distinct activation. */
    ASSERT_EQ(re_agenda_push(agenda, 3u, 5, premises, 2u), RE_STATUS_OK);
    ASSERT_EQ(agenda->pending_count, 3u);
    re_agenda_destroy_internal(agenda);
}

TEST(agenda_pop_orders_by_salience_then_sequence) {
    re_agenda_t *agenda = NULL;
    re_fact_id_t premise = fact_id(0u, 1u);
    re_agenda_entry_internal_t out;

    ASSERT_EQ(re_agenda_create_internal(NULL, &agenda), RE_STATUS_OK);
    ASSERT_EQ(re_agenda_pop_highest(agenda, &out), 0);
    ASSERT_EQ(re_agenda_push(agenda, 0u, 1, &premise, 1u), RE_STATUS_OK);
    ASSERT_EQ(re_agenda_push(agenda, 1u, 5, &premise, 1u), RE_STATUS_OK);
    ASSERT_EQ(re_agenda_push(agenda, 2u, 5, &premise, 1u), RE_STATUS_OK);

    ASSERT_EQ(re_agenda_pop_highest(agenda, &out), 1);
    ASSERT_EQ(out.rule_index, 1u);
    ASSERT_EQ(out.salience, 5);
    ASSERT_EQ(re_agenda_pop_highest(agenda, &out), 1);
    ASSERT_EQ(out.rule_index, 2u);
    ASSERT_EQ(re_agenda_pop_highest(agenda, &out), 1);
    ASSERT_EQ(out.rule_index, 0u);
    ASSERT_EQ(out.salience, 1);
    ASSERT_EQ(re_agenda_pop_highest(agenda, &out), 0);
    ASSERT_EQ(agenda->pending_count, 0u);
    re_agenda_destroy_internal(agenda);
}

TEST(agenda_mark_fired_refracts_and_dedups) {
    re_agenda_t *agenda = NULL;
    re_fact_id_t premises[2] = {fact_id(3u, 1u), fact_id(1u, 2u)};
    re_fact_id_t reversed[2] = {fact_id(1u, 2u), fact_id(3u, 1u)};
    re_fact_id_t reasserted[2] = {fact_id(3u, 2u), fact_id(1u, 2u)};
    re_agenda_entry_internal_t out;

    ASSERT_EQ(re_agenda_create_internal(NULL, &agenda), RE_STATUS_OK);
    ASSERT_FALSE(re_agenda_refracted(agenda, 2u, premises, 2u));
    ASSERT_EQ(re_agenda_push(agenda, 2u, 0, premises, 2u), RE_STATUS_OK);
    ASSERT_EQ(re_agenda_pop_highest(agenda, &out), 1);
    ASSERT_EQ(re_agenda_mark_fired(agenda, &out), RE_STATUS_OK);
    /* Refraction key ignores premise order. */
    ASSERT_TRUE(re_agenda_refracted(agenda, 2u, reversed, 2u));
    ASSERT_FALSE(re_agenda_refracted(agenda, 3u, premises, 2u));
    /* Re-firing the same key is deduped against the fired list. */
    ASSERT_EQ(re_agenda_push(agenda, 2u, 0, premises, 2u), RE_STATUS_OK);
    ASSERT_EQ(agenda->pending_count, 0u);
    /* A re-asserted premise (new generation) re-activates the rule. */
    ASSERT_FALSE(re_agenda_refracted(agenda, 2u, reasserted, 2u));
    ASSERT_EQ(re_agenda_push(agenda, 2u, 0, reasserted, 2u), RE_STATUS_OK);
    ASSERT_EQ(agenda->pending_count, 1u);
    re_agenda_destroy_internal(agenda);
}

TEST(agenda_clear_pending_keeps_fired_reset_clears_both) {
    re_agenda_t *agenda = NULL;
    re_fact_id_t premise = fact_id(0u, 1u);
    re_agenda_entry_internal_t out;

    ASSERT_EQ(re_agenda_create_internal(NULL, &agenda), RE_STATUS_OK);
    ASSERT_EQ(re_agenda_push(agenda, 0u, 0, &premise, 1u), RE_STATUS_OK);
    ASSERT_EQ(re_agenda_pop_highest(agenda, &out), 1);
    ASSERT_EQ(re_agenda_mark_fired(agenda, &out), RE_STATUS_OK);
    ASSERT_EQ(re_agenda_push(agenda, 1u, 0, &premise, 1u), RE_STATUS_OK);

    re_agenda_clear_pending(agenda);
    ASSERT_EQ(agenda->pending_count, 0u);
    ASSERT_EQ(agenda->fired_count, 1u);
    ASSERT_TRUE(re_agenda_refracted(agenda, 0u, &premise, 1u));

    re_agenda_reset(agenda);
    ASSERT_EQ(agenda->fired_count, 0u);
    ASSERT_FALSE(re_agenda_refracted(agenda, 0u, &premise, 1u));
    re_agenda_clear_pending(NULL);
    re_agenda_reset(NULL);
    re_agenda_destroy_internal(agenda);
}

TEST(agenda_push_validates_arguments) {
    re_agenda_t *agenda = NULL;
    re_fact_id_t premise = fact_id(0u, 1u);
    re_fact_id_t too_many[RE_AGENDA_MAX_PREMISES + 1u];

    memset(too_many, 0, sizeof(too_many));
    ASSERT_EQ(re_agenda_create_internal(NULL, &agenda), RE_STATUS_OK);
    ASSERT_EQ(re_agenda_push(NULL, 0u, 0, &premise, 1u), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_agenda_push(agenda, 0u, 0, NULL, 1u), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_agenda_push(agenda, 0u, 0, too_many, RE_AGENDA_MAX_PREMISES + 1u),
              RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_agenda_push(agenda, 0u, 0, NULL, 0u), RE_STATUS_OK);
    ASSERT_EQ(agenda->pending_count, 1u);
    re_agenda_destroy_internal(agenda);
}

TEST(agenda_grows_beyond_initial_capacity) {
    re_agenda_t *agenda = NULL;
    re_fact_id_t premise = fact_id(0u, 1u);
    re_agenda_entry_internal_t out;
    size_t i;

    ASSERT_EQ(re_agenda_create_internal(NULL, &agenda), RE_STATUS_OK);
    for (i = 0u; i < 20u; ++i)
        ASSERT_EQ(re_agenda_push(agenda, i, (int32_t)i, &premise, 1u), RE_STATUS_OK);
    ASSERT_EQ(agenda->pending_count, 20u);
    for (i = 20u; i-- != 0u;) {
        ASSERT_EQ(re_agenda_pop_highest(agenda, &out), 1);
        ASSERT_EQ(out.rule_index, i);
    }
    re_agenda_destroy_internal(agenda);
}

TEST(agenda_engine_lazy_create_and_destroy) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;

    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    ASSERT_TRUE(engine->agenda == NULL);
    /* A run without a program does not need an agenda. */
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_TRUE(engine->agenda == NULL);
    ASSERT_EQ(re_program_load(NULL,
        text("rule \"R\" { when A == 1 then B = 2; }"), NULL, &program),
        RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    program = NULL;
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_NOT_NULL(engine->agenda);
    /* reset_with_deffacts routes through re_engine_clear_agenda. */
    ASSERT_EQ(re_engine_reset_with_deffacts(engine, facts), RE_STATUS_OK);
    ASSERT_NOT_NULL(engine->agenda);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

/* ---- Task 7: recognize–act cycle behavior tests (public API only) ---- */

static re_status_t count_action(re_engine_t *engine, re_facts_t *facts,
                                const re_rule_event_t *event, void *context) {
    (void)engine; (void)facts; (void)event;
    ++*(size_t *)context;
    return RE_STATUS_OK;
}

typedef struct name_log_t {
    char names[8][16];
    size_t count;
} name_log_t;

static re_status_t record_name(re_engine_t *engine, re_facts_t *facts,
                               const re_rule_event_t *event, void *context) {
    name_log_t *log = context;
    (void)engine; (void)facts;
    if (log->count < 8u && event->rule_name.size < sizeof(log->names[0])) {
        memcpy(log->names[log->count], event->rule_name.data, event->rule_name.size);
        log->names[log->count][event->rule_name.size] = '\0';
    }
    ++log->count;
    return RE_STATUS_OK;
}

TEST(chained_rules_reactivate_within_one_run) {
    /* "B" sorts ahead of "A" (equal salience, earlier source order), so the
     * old single-pass loop evaluated B before A created Y and Z stayed
     * absent; the recognize–act loop re-evaluates B after A's firing. */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_value_t one = {RE_VALUE_INT64, {.int64_value = 1}};
    re_value_t out = {RE_VALUE_NONE, {0}};
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_facts_set(facts, text("X"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text(
        "rule \"B\" { when Y == 1 then Z = 1; } "
        "rule \"A\" { when X == 1 then Y = 1; }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("Z"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.as.int64_value, 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(refraction_prevents_self_refire) {
    /* A no-op self write (C = C + 0) leaves the condition true; refraction
     * must keep the rule from firing again within the same run. */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_value_t one = {RE_VALUE_INT64, {.int64_value = 1}};
    re_value_t out = {RE_VALUE_NONE, {0}};
    size_t calls = 0u;
    re_callbacks_t callbacks = {count_action, &calls};
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_facts_set(facts, text("C"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text(
        "rule \"S\" salience 5 { when C > 0 then C = C + 0; }"), NULL, &program),
        RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, &callbacks), RE_STATUS_OK);
    ASSERT_EQ(calls, 1u);
    ASSERT_EQ(re_facts_get(facts, text("C"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.as.int64_value, 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(changed_premise_reactivates_same_rule) {
    /* "D" joins N and M; "Bump" rewrites N's value (slot and generation stay
     * stable across updates; what changes is the value fingerprint mixed
     * into the refraction key). D must fire again within the same run. */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_value_t one = {RE_VALUE_INT64, {.int64_value = 1}};
    re_value_t zero = {RE_VALUE_INT64, {.int64_value = 0}};
    re_value_t out = {RE_VALUE_NONE, {0}};
    name_log_t log = {{{0}}, 0u};
    re_callbacks_t callbacks = {record_name, &log};
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_facts_set(facts, text("N"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("M"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("Trigger"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("Seen"), &zero), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text(
        "rule \"D\" salience 10 { when N > 0 and M > 0 then Seen = Seen + 1; } "
        "rule \"Bump\" { when Trigger == 1 then N = N + 1; }"), NULL, &program),
        RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, &callbacks), RE_STATUS_OK);
    ASSERT_EQ(log.count, 3u);
    ASSERT_STR_EQ(log.names[0], "D");
    ASSERT_STR_EQ(log.names[1], "Bump");
    ASSERT_STR_EQ(log.names[2], "D");
    ASSERT_EQ(re_facts_get(facts, text("Seen"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.as.int64_value, 2);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(max_firings_limit_still_bounds_loop) {
    /* Each firing bumps N's generation, producing a fresh activation every
     * cycle; only max_firings bounds the loop. */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_value_t one = {RE_VALUE_INT64, {.int64_value = 1}};
    re_value_t out = {RE_VALUE_NONE, {0}};
    size_t calls = 0u;
    re_callbacks_t callbacks = {count_action, &calls};
    re_limits_t limits;
    re_run_options_t options = {NULL, NULL, NULL};
    memset(&limits, 0, sizeof(limits));
    limits.max_firings = 10u;
    options.limits = &limits;
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_facts_set(facts, text("N"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("Go"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text(
        "rule \"L\" { when N > 0 and Go == 1 then N = N + 1; }"), NULL, &program),
        RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, &options, &callbacks), RE_STATUS_LIMIT);
    ASSERT_EQ(calls, 10u);
    ASSERT_EQ(re_facts_get(facts, text("N"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.as.int64_value, 11);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(salience_order_preserved_across_cycles) {
    /* Scenario A: S10 and S5 are initially active and S10's action activates
     * S7; the newly activated S7 (salience 7) fires before S5. */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_value_t one = {RE_VALUE_INT64, {.int64_value = 1}};
    name_log_t log = {{{0}}, 0u};
    re_callbacks_t callbacks = {record_name, &log};
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_facts_set(facts, text("Ready"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text(
        "rule \"S5\" salience 5 { when Ready == 1 then Low = 1; } "
        "rule \"S10\" salience 10 { when Ready == 1 then Mid = 1; } "
        "rule \"S7\" salience 7 { when Mid == 1 then High = 1; }"), NULL, &program),
        RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, &callbacks), RE_STATUS_OK);
    ASSERT_EQ(log.count, 3u);
    ASSERT_STR_EQ(log.names[0], "S10");
    ASSERT_STR_EQ(log.names[1], "S7");
    ASSERT_STR_EQ(log.names[2], "S5");
    re_facts_destroy(facts);
    re_engine_destroy(engine);

    /* Scenario B: the activator (S5) sorts after the dormant S7, so the old
     * single pass never revisited S7; the recognize–act loop fires it once
     * it becomes active. */
    engine = re_engine_create(NULL, NULL);
    facts = re_facts_create(NULL, NULL);
    program = NULL;
    memset(&log, 0, sizeof(log));
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_facts_set(facts, text("Ready"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text(
        "rule \"S10\" salience 10 { when Ready == 1 then High = 1; } "
        "rule \"S7\" salience 7 { when Mid == 1 then MidSeen = 1; } "
        "rule \"S5\" salience 5 { when Ready == 1 then Mid = 1; }"), NULL, &program),
        RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, &callbacks), RE_STATUS_OK);
    ASSERT_EQ(log.count, 3u);
    ASSERT_STR_EQ(log.names[0], "S10");
    ASSERT_STR_EQ(log.names[1], "S5");
    ASSERT_STR_EQ(log.names[2], "S7");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

typedef struct sequence_log_t {
    uint64_t first_sequence; /* linear rule "First": global firing counter */
    uint64_t join_sequence;  /* RETE rule "Join": network token sequence */
    size_t join_calls;
} sequence_log_t;

static re_status_t record_sequences(re_engine_t *engine, re_facts_t *facts,
                                    const re_rule_event_t *event, void *context) {
    sequence_log_t *log = context;
    (void)engine; (void)facts;
    if (event->rule_name.size == 4u && memcmp(event->rule_name.data, "Join", 4u) == 0) {
        log->join_sequence = event->activation_sequence;
        ++log->join_calls;
    } else if (event->rule_name.size == 5u && memcmp(event->rule_name.data, "First", 5u) == 0) {
        log->first_sequence = event->activation_sequence;
    }
    return RE_STATUS_OK;
}

TEST(rete_activation_event_carries_token_sequence) {
    /* A RETE-attached rule reports its network token's sequence in the rule
     * event, not the global firing counter (pre-Task-7 semantics); a linear
     * rule keeps the firing counter. "First" (salience 10) fires first, so
     * Join's firing counter would be 2 while its token sequence is 1. */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_value_t one = {RE_VALUE_INT64, {.int64_value = 1}};
    re_value_t two = {RE_VALUE_INT64, {.int64_value = 2}};
    sequence_log_t log = {0u, 0u, 0u};
    re_callbacks_t callbacks = {record_sequences, &log};
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_facts_set(facts, text("A"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("B"), &two), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text(
        "rule \"First\" salience 10 { when A > 0 then Fired = 1; } "
        "rule \"Join\" { when A > 0 and B == 2 then Result = 1; }"), NULL, &program),
        RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, &callbacks), RE_STATUS_OK);
    ASSERT_EQ(log.join_calls, 1u);
    ASSERT_EQ(log.first_sequence, 1u);
    ASSERT_EQ(log.join_sequence, 1u);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(stale_pending_activation_is_discarded) {
    /* Seed (lowest salience, evaluated last in the first pass) enables both
     * Killer and Victim. The next sweep pushes both; Killer (higher
     * salience) pops first and falsifies Victim's condition, so Victim's
     * pending activation is stale at pop time and must be discarded without
     * being marked fired. */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_value_t one = {RE_VALUE_INT64, {.int64_value = 1}};
    re_value_t out = {RE_VALUE_NONE, {0}};
    name_log_t log = {{{0}}, 0u};
    re_callbacks_t callbacks = {record_name, &log};
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_facts_set(facts, text("Start"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text(
        "rule \"Victim\" salience 5 { when X == 1 then V = 1; } "
        "rule \"Seed\" salience 0 { when Start == 1 then X = 1; Go = 1; } "
        "rule \"Killer\" salience 10 { when Go == 1 then X = 0; }"), NULL, &program),
        RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, &callbacks), RE_STATUS_OK);
    ASSERT_EQ(log.count, 2u);
    ASSERT_STR_EQ(log.names[0], "Seed");
    ASSERT_STR_EQ(log.names[1], "Killer");
    ASSERT_EQ(re_facts_get(facts, text("V"), &out), RE_STATUS_NOT_FOUND);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

/* ---- Task 8: persistent agenda + public inspection API (public API) ---- */

static int name_is(re_string_t name, const char *expected) {
    size_t size = strlen(expected);
    return name.size == size && memcmp(name.data, expected, size) == 0;
}

TEST(agenda_api_replaces_not_supported_stub) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_agenda_t *agenda = NULL;
    re_agenda_t *again = NULL;
    re_agenda_entry_t entry;
    ASSERT_NOT_NULL(engine);
    ASSERT_EQ(re_engine_agenda(NULL, &agenda), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_engine_agenda(engine, NULL), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_engine_agenda(engine, &agenda), RE_STATUS_OK);
    ASSERT_NOT_NULL(agenda);
    /* Repeated calls return the same engine-owned, lazily created instance. */
    ASSERT_EQ(re_engine_agenda(engine, &again), RE_STATUS_OK);
    ASSERT_TRUE(again == agenda);
    ASSERT_EQ(re_agenda_count(agenda), 0u);
    ASSERT_EQ(re_agenda_count(NULL), 0u);
    memset(&entry, 0, sizeof(entry));
    ASSERT_EQ(re_agenda_peek(NULL, 0u, &entry), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_agenda_peek(agenda, 0u, NULL), RE_STATUS_INVALID_ARGUMENT);
    /* A zero struct_size is rejected before any state exists. */
    ASSERT_EQ(re_agenda_peek(agenda, 0u, &entry), RE_STATUS_INVALID_ARGUMENT);
    entry.struct_size = sizeof(entry);
    ASSERT_EQ(re_agenda_peek(agenda, 0u, &entry), RE_STATUS_NOT_FOUND);
    ASSERT_EQ(re_engine_set_agenda_persistent(NULL, 1), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_engine_set_agenda_persistent(engine, 1), RE_STATUS_OK);
    ASSERT_EQ(re_engine_set_agenda_persistent(engine, 0), RE_STATUS_OK);
    /* Documented no-op for the engine-owned instance; the engine frees it. */
    re_agenda_destroy(agenda);
    re_agenda_destroy(NULL);
    re_engine_destroy(engine);
}

TEST(persistent_agenda_refires_only_on_premise_change) {
    /* Brief mechanics adjusted: "P" carries a second condition because only
     * RETE-attached rules (two or more fact-versus-literal comparisons) push
     * premise keys with value fingerprints; a single-condition rule would be
     * linear and premise-less, so a value change could not re-activate it.
     * With persistence on, the fired refraction key survives across runs:
     * run 2 changes nothing and does not refire; the N update changes the
     * fingerprint, so run 3 refires. */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_agenda_t *agenda = NULL;
    re_value_t one = {RE_VALUE_INT64, {.int64_value = 1}};
    re_value_t two = {RE_VALUE_INT64, {.int64_value = 2}};
    re_value_t zero = {RE_VALUE_INT64, {.int64_value = 0}};
    re_value_t out = {RE_VALUE_NONE, {0}};
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_facts_set(facts, text("N"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("Go"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("Hits"), &zero), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text(
        "rule \"P\" { when N > 0 and Go == 1 then Hits = Hits + 1; }"), NULL, &program),
        RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_set_agenda_persistent(engine, 1), RE_STATUS_OK);
    ASSERT_EQ(re_engine_agenda(engine, &agenda), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("Hits"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.as.int64_value, 1);
    /* Refraction survives the run boundary: nothing changed, no refire. */
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("Hits"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.as.int64_value, 1);
    /* A premise value change re-activates the rule. */
    ASSERT_EQ(re_facts_set(facts, text("N"), &two), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("Hits"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.as.int64_value, 2);
    ASSERT_EQ(re_agenda_count(agenda), 0u);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(agenda_peek_reports_pending_in_salience_order) {
    /* Brief mechanics adjusted (max_firings=2 instead of 1): the
     * recognize-act loop computes one new rule per iteration and breaks the
     * moment max_firings is reached, so a LIMIT-ended run can only leave
     * pending activations that a single firing's recompute sweep produced.
     * Seed's firing flips Gate and activates High/Mid/Low in one sweep;
     * max_firings=2 fires Seed and High, leaving Mid and Low pending.
     * Persistent mode keeps them across the LIMIT exit.
     * The gating comparison must come first: the committed IR evaluator
     * (ir_eval.c, out of scope here) short-circuits AND on the first
     * condition only, so "Gate == 1 and X == 1" gates on Gate while the
     * brief's "X == 1 and Gate == 1" ordering would match regardless. */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_agenda_t *agenda = NULL;
    re_fact_id_t start_id = {0u, 0u};
    re_fact_id_t x_id = {0u, 0u};
    re_fact_id_t gate_id = {0u, 0u};
    re_value_t one = {RE_VALUE_INT64, {.int64_value = 1}};
    re_value_t zero = {RE_VALUE_INT64, {.int64_value = 0}};
    re_agenda_entry_t entry;
    re_limits_t limits;
    re_run_options_t options = {NULL, NULL, NULL};
    memset(&limits, 0, sizeof(limits));
    limits.max_firings = 2u;
    options.limits = &limits;
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_facts_insert(facts, text("Start"), &one, &start_id), RE_STATUS_OK);
    ASSERT_EQ(re_facts_insert(facts, text("X"), &one, &x_id), RE_STATUS_OK);
    ASSERT_EQ(re_facts_insert(facts, text("Gate"), &zero, &gate_id), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text(
        "rule \"Seed\" salience 0 { when Start == 1 then Gate = 1; } "
        "rule \"High\" salience 10 { when Gate == 1 and X == 1 then H = 1; } "
        "rule \"Mid\" salience 7 { when Gate == 1 and X == 1 then M = 1; } "
        "rule \"Low\" salience 5 { when Gate == 1 and X == 1 then L = 1; }"), NULL, &program),
        RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_set_agenda_persistent(engine, 1), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, &options, NULL), RE_STATUS_LIMIT);
    ASSERT_EQ(re_engine_agenda(engine, &agenda), RE_STATUS_OK);
    /* High fired; Mid and Low survived the LIMIT exit, peeked in pop order. */
    ASSERT_EQ(re_agenda_count(agenda), 2u);
    memset(&entry, 0, sizeof(entry));
    entry.struct_size = sizeof(entry);
    ASSERT_EQ(re_agenda_peek(agenda, 0u, &entry), RE_STATUS_OK);
    ASSERT_TRUE(name_is(entry.rule_name, "Mid"));
    ASSERT_EQ(entry.salience, 7);
    ASSERT_EQ(entry.premise_count, 2u);
    /* True premise ids (real generations, condition order: Gate then X),
     * not the fingerprint-mangled refraction key. */
    ASSERT_EQ(entry.premises[0].slot, gate_id.slot);
    ASSERT_EQ(entry.premises[0].generation, gate_id.generation);
    ASSERT_EQ(entry.premises[1].slot, x_id.slot);
    ASSERT_EQ(entry.premises[1].generation, x_id.generation);
    memset(&entry, 0, sizeof(entry));
    entry.struct_size = sizeof(entry);
    ASSERT_EQ(re_agenda_peek(agenda, 1u, &entry), RE_STATUS_OK);
    ASSERT_TRUE(name_is(entry.rule_name, "Low"));
    ASSERT_EQ(entry.salience, 5);
    ASSERT_EQ(entry.premise_count, 2u);
    ASSERT_EQ(re_agenda_peek(agenda, 2u, &entry), RE_STATUS_NOT_FOUND);
    /* A following unbounded run drains the surviving activations. */
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_agenda_count(agenda), 0u);
    {
        re_value_t out = {RE_VALUE_NONE, {0}};
        ASSERT_EQ(re_facts_get(facts, text("M"), &out), RE_STATUS_OK);
        ASSERT_EQ(out.as.int64_value, 1);
        ASSERT_EQ(re_facts_get(facts, text("L"), &out), RE_STATUS_OK);
        ASSERT_EQ(out.as.int64_value, 1);
    }
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(tms_retraction_cancels_pending_activation) {
    /* Brief mechanics substituted: instead of a hook inside
     * re_tms_remove_premise, cancellation rides on pop-time revalidation in
     * the next run - a pending activation whose premise token is gone is
     * discarded without firing. Derive fires first and logically inserts
     * Derived (premises [Gate, Base]); Distract outranks Use in the final
     * sweep so max_firings=3 leaves Use pending across the LIMIT exit.
     * Retracting Base between runs cascades Derived away; the next run drops
     * Use's surviving activation without firing it.
     * The gating comparison must come first: the committed IR evaluator
     * (ir_eval.c, out of scope here) short-circuits AND on the first
     * condition only, so Gate-first conditions keep every rule dormant until
     * Seed flips Gate. */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_agenda_t *agenda = NULL;
    re_fact_id_t start_id = {0u, 0u};
    re_fact_id_t base_id = {0u, 0u};
    re_fact_id_t gate_id = {0u, 0u};
    re_value_t one = {RE_VALUE_INT64, {.int64_value = 1}};
    re_value_t zero = {RE_VALUE_INT64, {.int64_value = 0}};
    re_value_t out = {RE_VALUE_NONE, {0}};
    name_log_t log = {{{0}}, 0u};
    re_callbacks_t callbacks = {record_name, &log};
    re_agenda_entry_t entry;
    re_limits_t limits;
    re_run_options_t options = {NULL, NULL, NULL};
    memset(&limits, 0, sizeof(limits));
    limits.max_firings = 3u;
    options.limits = &limits;
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_facts_insert(facts, text("Start"), &one, &start_id), RE_STATUS_OK);
    ASSERT_EQ(re_facts_insert(facts, text("Base"), &one, &base_id), RE_STATUS_OK);
    ASSERT_EQ(re_facts_insert(facts, text("Gate"), &zero, &gate_id), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text(
        "rule \"Derive\" salience 10 { when Gate == 1 and Base == 1 then Derived = 1; } "
        "rule \"Distract\" salience 7 { when Gate == 1 and Base == 1 then Noise = 1; } "
        "rule \"Use\" salience 5 { when Gate == 1 and Derived == 1 then Out = 1; } "
        "rule \"Seed\" salience 0 { when Start == 1 then Gate = 1; }"), NULL, &program),
        RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_set_agenda_persistent(engine, 1), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, &options, &callbacks), RE_STATUS_LIMIT);
    ASSERT_EQ(log.count, 3u);
    ASSERT_STR_EQ(log.names[0], "Seed");
    ASSERT_STR_EQ(log.names[1], "Derive");
    ASSERT_STR_EQ(log.names[2], "Distract");
    ASSERT_EQ(re_facts_get(facts, text("Derived"), &out), RE_STATUS_OK);
    /* Use's activation survived the LIMIT exit. */
    ASSERT_EQ(re_engine_agenda(engine, &agenda), RE_STATUS_OK);
    ASSERT_EQ(re_agenda_count(agenda), 1u);
    memset(&entry, 0, sizeof(entry));
    entry.struct_size = sizeof(entry);
    ASSERT_EQ(re_agenda_peek(agenda, 0u, &entry), RE_STATUS_OK);
    ASSERT_TRUE(name_is(entry.rule_name, "Use"));
    /* Retracting Base cascades: Derived (and Noise) lose their only
     * justification and are retracted between runs. */
    ASSERT_EQ(re_facts_retract(facts, base_id), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("Derived"), &out), RE_STATUS_NOT_FOUND);
    /* The next run discards the stale pending activation at pop time without
     * firing it; nothing else matches, so the run ends clean. */
    ASSERT_EQ(re_engine_run(engine, facts, NULL, &callbacks), RE_STATUS_OK);
    ASSERT_EQ(re_agenda_count(agenda), 0u);
    ASSERT_EQ(log.count, 3u);
    ASSERT_EQ(re_facts_get(facts, text("Out"), &out), RE_STATUS_NOT_FOUND);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(non_persistent_default_unchanged) {
    /* Default (non-persistent) mode fully resets the agenda on every run
     * exit: each run fires the rule exactly once. */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_value_t one = {RE_VALUE_INT64, {.int64_value = 1}};
    re_value_t zero = {RE_VALUE_INT64, {.int64_value = 0}};
    re_value_t out = {RE_VALUE_NONE, {0}};
    size_t calls = 0u;
    re_callbacks_t callbacks = {count_action, &calls};
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_facts_set(facts, text("N"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("Go"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("Hits"), &zero), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text(
        "rule \"P\" { when N > 0 and Go == 1 then Hits = Hits + 1; }"), NULL, &program),
        RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, &callbacks), RE_STATUS_OK);
    ASSERT_EQ(calls, 1u);
    calls = 0u;
    ASSERT_EQ(re_engine_run(engine, facts, NULL, &callbacks), RE_STATUS_OK);
    ASSERT_EQ(calls, 1u);
    ASSERT_EQ(re_facts_get(facts, text("Hits"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.as.int64_value, 2);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(agenda_rete_capability_reported_with_attached_networks) {
    /* test_rule_engine.c locks RE_CAP2_AGENDA_RETE OFF for an engine without
     * an attached RETE network, so the bit stays network-gated; running a
     * RETE-eligible rule attaches the per-rule networks and turns it on. */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_capabilities_v2_t capabilities = 0u;
    re_extension_info_t info = {sizeof(info), 0u, 0u, 0u, 0u, 0u, 0u};
    re_value_t one = {RE_VALUE_INT64, {.int64_value = 1}};
    re_value_t two = {RE_VALUE_INT64, {.int64_value = 2}};
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(RE_ABI_VERSION_MINOR, 3u);
    ASSERT_EQ(re_facts_set(facts, text("A"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("B"), &two), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text(
        "rule \"J\" { when A == 1 and B == 2 then C = 1; }"), NULL, &program),
        RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_engine_capabilities_v2(engine, RE_ABI_VERSION_MAJOR, &capabilities),
              RE_STATUS_OK);
    ASSERT_TRUE((capabilities & RE_CAP2_AGENDA_RETE) != 0u);
    ASSERT_EQ(re_engine_extension_info(engine, RE_EXTENSION_AGENDA_RETE, 1u, &info),
              RE_STATUS_OK);
    ASSERT_EQ(info.capability_bit, RE_CAP2_AGENDA_RETE);
    ASSERT_EQ(info.abi_major, RE_ABI_VERSION_MAJOR);
    ASSERT_EQ(info.abi_minor, RE_ABI_VERSION_MINOR);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

/* ---- Task 9: AND/OR evaluator fix, dotted-target provenance, read-set ---- */

TEST(and_second_condition_gates_linear_path) {
    /* Arithmetic in the first condition makes the rule RETE-ineligible, so
     * the linear evaluator decides matching. Pre-fix, stage 3 of an AND frame
     * re-evaluated it as a comparison with the parser-zeroed compare op
     * (RE_COMPARE_TRUE), forcing a match whenever the first child was true:
     * "A + B > 1 and C == 0" fired with C == 1. */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_value_t one = {RE_VALUE_INT64, {.int64_value = 1}};
    re_value_t zero = {RE_VALUE_INT64, {.int64_value = 0}};
    re_value_t out = {RE_VALUE_NONE, {0}};
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_facts_set(facts, text("A"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("B"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("C"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text(
        "rule \"Arith\" { when A + B > 1 and C == 0 then Hit = 1; } "
        "rule \"Other\" { when A + B > 5 then Extra = 1; }"), NULL, &program),
        RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("Hit"), &out), RE_STATUS_NOT_FOUND);
    re_facts_destroy(facts);
    re_engine_destroy(engine);

    /* Both true: the rule must fire through the same linear path. */
    engine = re_engine_create(NULL, NULL);
    facts = re_facts_create(NULL, NULL);
    program = NULL;
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_facts_set(facts, text("A"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("B"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("C"), &zero), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text(
        "rule \"Arith\" { when A + B > 1 and C == 0 then Hit = 1; } "
        "rule \"Other\" { when A + B > 5 then Extra = 1; }"), NULL, &program),
        RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("Hit"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.as.int64_value, 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(or_requires_one_true_side) {
    /* Pre-fix, "A or B" matched whenever A was false (the stage-3 clobber
     * forced the second child's frame to true), so both-false fired. */
    re_engine_t *engine;
    re_facts_t *facts;
    re_program_t *program;
    re_value_t zero = {RE_VALUE_INT64, {.int64_value = 0}};
    re_value_t nine = {RE_VALUE_INT64, {.int64_value = 9}};
    re_value_t out = {RE_VALUE_NONE, {0}};
    size_t scenario;
    for (scenario = 0u; scenario < 3u; ++scenario) {
        re_value_t x = scenario == 2u ? nine : zero;
        re_value_t y = scenario == 1u ? nine : zero;
        engine = re_engine_create(NULL, NULL);
        facts = re_facts_create(NULL, NULL);
        program = NULL;
        ASSERT_NOT_NULL(engine);
        ASSERT_NOT_NULL(facts);
        ASSERT_EQ(re_facts_set(facts, text("X"), &x), RE_STATUS_OK);
        ASSERT_EQ(re_facts_set(facts, text("Y"), &y), RE_STATUS_OK);
        ASSERT_EQ(re_program_load(NULL, text(
            "rule \"Or\" { when X == 9 or Y == 9 then Hit = 1; }"), NULL, &program),
            RE_STATUS_OK);
        ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
        ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
        if (scenario == 0u) {
            /* Both false: must not fire. */
            ASSERT_EQ(re_facts_get(facts, text("Hit"), &out), RE_STATUS_NOT_FOUND);
        } else {
            /* A false B true, and A true B false: must fire. */
            ASSERT_EQ(re_facts_get(facts, text("Hit"), &out), RE_STATUS_OK);
            ASSERT_EQ(out.as.int64_value, 1);
        }
        re_facts_destroy(facts);
        re_engine_destroy(engine);
    }
}

TEST(and_gate_agrees_with_rete_network) {
    /* Same shapes locked through a single-rule RETE-attached program: the
     * matcher gate (re_ir_match_rule) runs even for network-attached rules,
     * so the AND fix decides here too; behavior must agree with the linear
     * path. Pre-fix the true/false shape fired via the zero-token
     * premise-less fallback behind the buggy gate. */
    re_engine_t *engine;
    re_facts_t *facts;
    re_program_t *program;
    re_value_t one = {RE_VALUE_INT64, {.int64_value = 1}};
    re_value_t zero = {RE_VALUE_INT64, {.int64_value = 0}};
    re_value_t out = {RE_VALUE_NONE, {0}};
    size_t scenario;
    for (scenario = 0u; scenario < 2u; ++scenario) {
        re_value_t y = scenario == 0u ? zero : one;
        engine = re_engine_create(NULL, NULL);
        facts = re_facts_create(NULL, NULL);
        program = NULL;
        ASSERT_NOT_NULL(engine);
        ASSERT_NOT_NULL(facts);
        ASSERT_EQ(re_facts_set(facts, text("X"), &one), RE_STATUS_OK);
        ASSERT_EQ(re_facts_set(facts, text("Y"), &y), RE_STATUS_OK);
        ASSERT_EQ(re_program_load(NULL, text(
            "rule \"J\" { when X == 1 and Y == 0 then Hit = 1; }"), NULL, &program),
            RE_STATUS_OK);
        ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
        ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
        if (scenario == 0u) {
            ASSERT_EQ(re_facts_get(facts, text("Hit"), &out), RE_STATUS_OK);
            ASSERT_EQ(out.as.int64_value, 1);
        } else {
            ASSERT_EQ(re_facts_get(facts, text("Hit"), &out), RE_STATUS_NOT_FOUND);
        }
        re_facts_destroy(facts);
        re_engine_destroy(engine);
    }
}

/* Builds structured fact Car as an empty object, or with a speed member when
 * with_speed is set; mirrors set_structured_car in the GRL suite. */
static void set_car_object(re_facts_t *facts, int with_speed) {
    re_value_handle_t *car = NULL;
    re_value_t member = {RE_VALUE_INT64, {.int64_value = 80}};
    ASSERT_EQ(re_value_create_object(facts, &car), RE_STATUS_OK);
    if (with_speed)
        ASSERT_EQ(re_value_object_set(car, text("speed"), &member), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set_value(facts, text("Car"), car), RE_STATUS_OK);
    re_value_destroy(car);
}

TEST(dotted_target_writes_member_with_root_provenance) {
    /* RETE-eligible rule, dotted target on a structured root: the firing must
     * update the member (no flat "Car.speed" shadow), and the justification
     * anchors on the ROOT fact id with producer + premises. Bounded
     * semantics: retracting a premise then cascades to the whole root fact,
     * not just the member. */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_fact_id_t car_id = {0u, 0u};
    re_fact_id_t a_id = {0u, 0u};
    re_fact_id_t b_id = {0u, 0u};
    re_value_t one = {RE_VALUE_INT64, {.int64_value = 1}};
    re_value_t two = {RE_VALUE_INT64, {.int64_value = 2}};
    re_value_t out = {RE_VALUE_NONE, {0}};
    re_fact_provenance_t provenance = {sizeof(provenance), 0u, {NULL, 0u}, 0u, NULL};
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    /* Car is inserted first: slot 0, generation 0. */
    set_car_object(facts, 1);
    ASSERT_EQ(re_facts_insert(facts, text("A"), &one, &a_id), RE_STATUS_OK);
    ASSERT_EQ(re_facts_insert(facts, text("B"), &two, &b_id), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text(
        "rule \"Speed\" { when A > 0 and B == 2 then Car.speed = 120; }"), NULL, &program),
        RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    /* The member was updated; no flat shadow fact exists. */
    ASSERT_EQ(re_facts_get_path(facts, text("Car.speed"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.as.int64_value, 120);
    ASSERT_EQ(re_facts_get(facts, text("Car.speed"), &out), RE_STATUS_NOT_FOUND);
    /* Provenance sits on the root fact and names the producer + premises. */
    ASSERT_EQ(re_facts_provenance_get(facts, car_id, &provenance), RE_STATUS_OK);
    ASSERT_EQ(provenance.producer_rule.size, 5u);
    ASSERT_TRUE(memcmp(provenance.producer_rule.data, "Speed", 5u) == 0);
    ASSERT_EQ(provenance.premise_count, 2u);
    ASSERT_EQ(provenance.premises[0].slot, a_id.slot);
    ASSERT_EQ(provenance.premises[0].generation, a_id.generation);
    ASSERT_EQ(provenance.premises[1].slot, b_id.slot);
    ASSERT_EQ(provenance.premises[1].generation, b_id.generation);
    /* Documented bound: premise retraction cascades to the ROOT fact. */
    ASSERT_EQ(re_facts_retract(facts, a_id), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get_path(facts, text("Car.speed"), &out), RE_STATUS_NOT_FOUND);
    ASSERT_EQ(re_facts_get(facts, text("Car"), &out), RE_STATUS_NOT_FOUND);
    re_engine_destroy(engine);
    re_facts_destroy(facts);
}

TEST(dotted_target_creates_member_on_structured_root) {
    /* Same path, but the member does not exist yet: set_path reports
     * NOT_FOUND and re_facts_set_member creates it on the structured root;
     * the justification still anchors on the root. */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_fact_id_t car_id = {0u, 0u};
    re_value_t one = {RE_VALUE_INT64, {.int64_value = 1}};
    re_value_t two = {RE_VALUE_INT64, {.int64_value = 2}};
    re_value_t out = {RE_VALUE_NONE, {0}};
    re_fact_provenance_t provenance = {sizeof(provenance), 0u, {NULL, 0u}, 0u, NULL};
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    set_car_object(facts, 0);
    ASSERT_EQ(re_facts_set(facts, text("A"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("B"), &two), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text(
        "rule \"Speed\" { when A > 0 and B == 2 then Car.speed = 120; }"), NULL, &program),
        RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get_path(facts, text("Car.speed"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.as.int64_value, 120);
    ASSERT_EQ(re_facts_get(facts, text("Car.speed"), &out), RE_STATUS_NOT_FOUND);
    ASSERT_EQ(re_facts_provenance_get(facts, car_id, &provenance), RE_STATUS_OK);
    ASSERT_EQ(provenance.premise_count, 2u);
    re_engine_destroy(engine);
    re_facts_destroy(facts);
}

TEST(dotted_target_without_structured_root_keeps_flat_shadow) {
    /* A dotted target whose root is not an existing structured fact keeps the
     * historical behavior: a flat "New.speed" fact is logically inserted with
     * the producer + premises recorded. */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_fact_id_t shadow_id = {2u, 1u}; /* A, B inserted first */
    re_value_t one = {RE_VALUE_INT64, {.int64_value = 1}};
    re_value_t two = {RE_VALUE_INT64, {.int64_value = 2}};
    re_value_t out = {RE_VALUE_NONE, {0}};
    re_fact_provenance_t provenance = {sizeof(provenance), 0u, {NULL, 0u}, 0u, NULL};
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_facts_insert(facts, text("A"), &one, &shadow_id), RE_STATUS_OK);
    ASSERT_EQ(re_facts_insert(facts, text("B"), &two, &shadow_id), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text(
        "rule \"Flat\" { when A > 0 and B == 2 then New.speed = 5; }"), NULL, &program),
        RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("New.speed"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.as.int64_value, 5);
    shadow_id.slot = 2u;
    shadow_id.generation = 1u;
    ASSERT_TRUE(re_facts_is_logical(facts, shadow_id));
    ASSERT_EQ(re_facts_provenance_get(facts, shadow_id, &provenance), RE_STATUS_OK);
    ASSERT_EQ(provenance.producer_rule.size, 4u);
    ASSERT_EQ(provenance.premise_count, 2u);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(linear_path_derivation_records_provenance) {
    /* Linear evaluator path (arithmetic condition, RETE-ineligible): the
     * derived fact now carries producer + premises resolved from the
     * condition read-set. Two rules keep the brief's multi-rule shape, though
     * RETE attach is per-rule now and "Arith" is ineligible on its own. */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_fact_id_t a_id = {0u, 0u};
    re_fact_id_t b_id = {0u, 0u};
    re_fact_id_t d_id = {2u, 1u}; /* A, B inserted first; D derived third */
    re_value_t one = {RE_VALUE_INT64, {.int64_value = 1}};
    re_value_t out = {RE_VALUE_NONE, {0}};
    re_fact_provenance_t provenance = {sizeof(provenance), 0u, {NULL, 0u}, 0u, NULL};
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_facts_insert(facts, text("A"), &one, &a_id), RE_STATUS_OK);
    ASSERT_EQ(re_facts_insert(facts, text("B"), &one, &b_id), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text(
        "rule \"Arith\" { when A + B > 1 then D = 9; } "
        "rule \"Idle\" { when A + B > 5 then E = 1; }"), NULL, &program),
        RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("D"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.as.int64_value, 9);
    ASSERT_TRUE(re_facts_is_logical(facts, d_id));
    ASSERT_EQ(re_facts_provenance_get(facts, d_id, &provenance), RE_STATUS_OK);
    ASSERT_EQ(provenance.producer_rule.size, 5u);
    ASSERT_TRUE(memcmp(provenance.producer_rule.data, "Arith", 5u) == 0);
    /* Premises are the read-set in read order: A then B. */
    ASSERT_EQ(provenance.premise_count, 2u);
    ASSERT_EQ(provenance.premises[0].slot, a_id.slot);
    ASSERT_EQ(provenance.premises[0].generation, a_id.generation);
    ASSERT_EQ(provenance.premises[1].slot, b_id.slot);
    ASSERT_EQ(provenance.premises[1].generation, b_id.generation);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(provenance_cascade_retracts_linear_derived) {
    /* Same setup; retracting premise A must auto-retract the linear-derived
     * D through its TMS justification. */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_fact_id_t a_id = {0u, 0u};
    re_fact_id_t b_id = {0u, 0u};
    re_value_t one = {RE_VALUE_INT64, {.int64_value = 1}};
    re_value_t out = {RE_VALUE_NONE, {0}};
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_facts_insert(facts, text("A"), &one, &a_id), RE_STATUS_OK);
    ASSERT_EQ(re_facts_insert(facts, text("B"), &one, &b_id), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text(
        "rule \"Arith\" { when A + B > 1 then D = 9; } "
        "rule \"Idle\" { when A + B > 5 then E = 1; }"), NULL, &program),
        RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("D"), &out), RE_STATUS_OK);
    ASSERT_EQ(re_facts_retract(facts, a_id), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("D"), &out), RE_STATUS_NOT_FOUND);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(multi_producer_justifications_accumulate) {
    /* Two linear rules both derive D from different premises; both
     * justifications accumulate on D. */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_fact_id_t d_id = {3u, 1u}; /* A, B, C inserted first; D derived fourth */
    re_value_t one = {RE_VALUE_INT64, {.int64_value = 1}};
    re_value_t out = {RE_VALUE_NONE, {0}};
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_facts_set(facts, text("A"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("B"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("C"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text(
        "rule \"R1\" { when A + B > 1 then D = 9; } "
        "rule \"R2\" { when C + 0 > 0 then D = 7; }"), NULL, &program),
        RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("D"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.as.int64_value, 7);
    ASSERT_EQ(re_facts_justification_count(facts, d_id), 2u);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(linear_rule_reactivates_on_premise_value_change_within_run) {
    /* All-linear program (arithmetic or single-comparison conditions):
     * Track's read-set premise is N; Bump's firing rewrites N, whose value
     * fingerprint change must re-activate Track within the same run -
     * symmetric with RETE rules. Pre-fix, premise-less linear activations
     * fired at most once per run, so Hits stayed 1. */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_value_t one = {RE_VALUE_INT64, {.int64_value = 1}};
    re_value_t zero = {RE_VALUE_INT64, {.int64_value = 0}};
    re_value_t out = {RE_VALUE_NONE, {0}};
    name_log_t log = {{{0}}, 0u};
    re_callbacks_t callbacks = {record_name, &log};
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_facts_set(facts, text("N"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("T"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("Hits"), &zero), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text(
        "rule \"Track\" { when N + 0 > 0 then Hits = Hits + 1; } "
        "rule \"Bump\" { when T == 1 then N = N + 1; }"), NULL, &program),
        RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, &callbacks), RE_STATUS_OK);
    ASSERT_EQ(log.count, 3u);
    ASSERT_STR_EQ(log.names[0], "Track");
    ASSERT_STR_EQ(log.names[1], "Bump");
    ASSERT_STR_EQ(log.names[2], "Track");
    ASSERT_EQ(re_facts_get(facts, text("Hits"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.as.int64_value, 2);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(linear_rule_refraction_persistent_across_runs) {
    /* Persistent agenda: the fired refraction key (value fingerprint of the
     * read-set premise) survives the run boundary. Run 2 changes nothing and
     * does not refire; the N update changes the fingerprint, so run 3
     * refires. Pre-fix, the premise-less key could not observe the change. */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_value_t one = {RE_VALUE_INT64, {.int64_value = 1}};
    re_value_t two = {RE_VALUE_INT64, {.int64_value = 2}};
    re_value_t zero = {RE_VALUE_INT64, {.int64_value = 0}};
    re_value_t out = {RE_VALUE_NONE, {0}};
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_facts_set(facts, text("N"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("Hits"), &zero), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text(
        "rule \"Track\" { when N + 0 > 0 then Hits = Hits + 1; }"), NULL, &program),
        RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_set_agenda_persistent(engine, 1), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("Hits"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.as.int64_value, 1);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("Hits"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.as.int64_value, 1);
    ASSERT_EQ(re_facts_set(facts, text("N"), &two), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("Hits"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.as.int64_value, 2);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(agenda_peek_shows_linear_true_premises) {
    /* A pending LINEAR activation now reports its read-set premise (real
     * generation) through re_agenda_peek, exactly like token lineage. The
     * recognize-act loop pops one activation per iteration, so a LIMIT exit
     * can only leave pending what a single firing's recompute sweep produced
     * (same construction as the Task 8 peek test): Seed flips Gate, the sweep
     * pushes First and Second, First fires, and Second survives. */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_agenda_t *agenda = NULL;
    re_fact_id_t start_id = {0u, 0u};
    re_fact_id_t gate_id = {0u, 0u};
    re_value_t one = {RE_VALUE_INT64, {.int64_value = 1}};
    re_value_t zero = {RE_VALUE_INT64, {.int64_value = 0}};
    re_agenda_entry_t entry;
    re_limits_t limits;
    re_run_options_t options = {NULL, NULL, NULL};
    memset(&limits, 0, sizeof(limits));
    limits.max_firings = 2u;
    options.limits = &limits;
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_facts_insert(facts, text("Start"), &one, &start_id), RE_STATUS_OK);
    ASSERT_EQ(re_facts_insert(facts, text("Gate"), &zero, &gate_id), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text(
        "rule \"First\" salience 10 { when Gate + 0 > 0 then X = 1; } "
        "rule \"Second\" salience 5 { when Gate + 0 > 0 then Y = 1; } "
        "rule \"Seed\" salience 0 { when Start == 1 then Gate = 1; }"), NULL, &program),
        RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_set_agenda_persistent(engine, 1), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, &options, NULL), RE_STATUS_LIMIT);
    ASSERT_EQ(re_engine_agenda(engine, &agenda), RE_STATUS_OK);
    ASSERT_EQ(re_agenda_count(agenda), 1u);
    memset(&entry, 0, sizeof(entry));
    entry.struct_size = sizeof(entry);
    ASSERT_EQ(re_agenda_peek(agenda, 0u, &entry), RE_STATUS_OK);
    ASSERT_TRUE(name_is(entry.rule_name, "Second"));
    ASSERT_EQ(entry.salience, 5);
    /* Linear activations carry their read-set premise with the real
     * generation, not a premise-less or fingerprint-mangled entry. */
    ASSERT_EQ(entry.premise_count, 1u);
    ASSERT_EQ(entry.premises[0].slot, gate_id.slot);
    ASSERT_EQ(entry.premises[0].generation, gate_id.generation);
    /* The surviving linear activation still fires on the draining run. */
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_agenda_count(agenda), 0u);
    {
        re_value_t out = {RE_VALUE_NONE, {0}};
        ASSERT_EQ(re_facts_get(facts, text("Y"), &out), RE_STATUS_OK);
        ASSERT_EQ(out.as.int64_value, 1);
    }
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

/* ---- Final hardening: CANCELLED-exit persistence + quantifier provenance ---- */

/* Cancel gate driven by firings observed through the action callback, so the
 * test does not depend on recognize-act iteration bookkeeping. */
typedef struct cancel_after_fire_t {
    size_t fired;
    size_t trip_after;
} cancel_after_fire_t;

static re_status_t count_fire(re_engine_t *engine, re_facts_t *facts,
                              const re_rule_event_t *event, void *context) {
    (void)engine; (void)facts; (void)event;
    ++((cancel_after_fire_t *)context)->fired;
    return RE_STATUS_OK;
}

static int cancel_after_fire(void *context) {
    const cancel_after_fire_t *cancel = (const cancel_after_fire_t *)context;
    return cancel->fired > cancel->trip_after;
}

TEST(persistent_agenda_survives_cancelled_exit) {
    /* Same construction as agenda_peek_reports_pending_in_salience_order, but
     * the run ends on the cancellation check instead of max_firings: the gate
     * trips once Seed and High have fired, leaving Mid and Low pending.
     * Persistent mode keeps the pending activations and the fired refraction
     * keys across the CANCELLED exit, and the next uncancelled run fires only
     * the survivors. */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_agenda_t *agenda = NULL;
    re_fact_id_t start_id = {0u, 0u};
    re_fact_id_t gate_id = {0u, 0u};
    re_fact_id_t x_id = {0u, 0u};
    re_value_t one = {RE_VALUE_INT64, {.int64_value = 1}};
    re_value_t zero = {RE_VALUE_INT64, {.int64_value = 0}};
    re_value_t out = {RE_VALUE_NONE, {0}};
    cancel_after_fire_t cancel = {0u, 1u};
    re_run_options_t options = {NULL, cancel_after_fire, &cancel};
    re_callbacks_t callbacks = {count_fire, &cancel};
    name_log_t log = {{{0}}, 0u};
    re_callbacks_t log_callbacks = {record_name, &log};
    re_agenda_entry_t entry;
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_facts_insert(facts, text("Start"), &one, &start_id), RE_STATUS_OK);
    ASSERT_EQ(re_facts_insert(facts, text("X"), &one, &x_id), RE_STATUS_OK);
    ASSERT_EQ(re_facts_insert(facts, text("Gate"), &zero, &gate_id), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text(
        "rule \"Seed\" salience 0 { when Start == 1 then Gate = 1; } "
        "rule \"High\" salience 10 { when Gate == 1 and X == 1 then H = 1; } "
        "rule \"Mid\" salience 7 { when Gate == 1 and X == 1 then M = 1; } "
        "rule \"Low\" salience 5 { when Gate == 1 and X == 1 then L = 1; }"), NULL, &program),
        RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_set_agenda_persistent(engine, 1), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, &options, &callbacks), RE_STATUS_CANCELLED);
    /* Seed and High fired before the gate tripped. */
    ASSERT_EQ(cancel.fired, 2u);
    ASSERT_EQ(re_facts_get(facts, text("H"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.as.int64_value, 1);
    /* Mid and Low survived the CANCELLED exit, peeked in pop order. */
    ASSERT_EQ(re_engine_agenda(engine, &agenda), RE_STATUS_OK);
    ASSERT_EQ(re_agenda_count(agenda), 2u);
    memset(&entry, 0, sizeof(entry));
    entry.struct_size = sizeof(entry);
    ASSERT_EQ(re_agenda_peek(agenda, 0u, &entry), RE_STATUS_OK);
    ASSERT_TRUE(name_is(entry.rule_name, "Mid"));
    ASSERT_EQ(entry.salience, 7);
    ASSERT_EQ(entry.premise_count, 2u);
    ASSERT_EQ(entry.premises[0].slot, gate_id.slot);
    ASSERT_EQ(entry.premises[0].generation, gate_id.generation);
    ASSERT_EQ(entry.premises[1].slot, x_id.slot);
    ASSERT_EQ(entry.premises[1].generation, x_id.generation);
    memset(&entry, 0, sizeof(entry));
    entry.struct_size = sizeof(entry);
    ASSERT_EQ(re_agenda_peek(agenda, 1u, &entry), RE_STATUS_OK);
    ASSERT_TRUE(name_is(entry.rule_name, "Low"));
    /* The next uncancelled run drains the survivors and respects the
     * persisted refraction keys: Seed and High do not refire. */
    ASSERT_EQ(re_engine_run(engine, facts, NULL, &log_callbacks), RE_STATUS_OK);
    ASSERT_EQ(log.count, 2u);
    ASSERT_STR_EQ(log.names[0], "Mid");
    ASSERT_STR_EQ(log.names[1], "Low");
    ASSERT_EQ(re_agenda_count(agenda), 0u);
    ASSERT_EQ(re_facts_get(facts, text("M"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.as.int64_value, 1);
    ASSERT_EQ(re_facts_get(facts, text("L"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.as.int64_value, 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(exists_condition_records_read_premise) {
    /* EXISTS takes the linear evaluator path (quantified conditions are
     * RETE-ineligible) and records the quantified fact path in the condition
     * read-set, so the derived fact's justification names the read fact. */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_fact_id_t flag_id = {0u, 0u};
    re_fact_id_t d_id = {1u, 1u}; /* Flag inserted first; D derived second */
    re_value_t one = {RE_VALUE_INT64, {.int64_value = 1}};
    re_value_t out = {RE_VALUE_NONE, {0}};
    re_fact_provenance_t provenance = {sizeof(provenance), 0u, {NULL, 0u}, 0u, NULL};
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_facts_insert(facts, text("Flag"), &one, &flag_id), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text(
        "rule \"Ex\" { when exists Flag == 1 then D = 1; }"), NULL, &program),
        RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("D"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.as.int64_value, 1);
    ASSERT_TRUE(re_facts_is_logical(facts, d_id));
    ASSERT_EQ(re_facts_provenance_get(facts, d_id, &provenance), RE_STATUS_OK);
    ASSERT_TRUE(name_is(provenance.producer_rule, "Ex"));
    ASSERT_EQ(provenance.premise_count, 1u);
    ASSERT_EQ(provenance.premises[0].slot, flag_id.slot);
    ASSERT_EQ(provenance.premises[0].generation, flag_id.generation);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(forall_condition_records_read_premise) {
    /* Same read-set provenance through FORALL: the quantified array fact is
     * the derived fact's recorded premise. Values is set (not inserted) first,
     * so its id is slot 0 generation 0; D derives at slot 1 generation 1. */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_handle_t *array = NULL;
    re_program_t *program = NULL;
    re_fact_id_t d_id = {1u, 1u};
    re_value_t item = {RE_VALUE_INT64, {.int64_value = 3}};
    re_value_t out = {RE_VALUE_NONE, {0}};
    re_fact_provenance_t provenance = {sizeof(provenance), 0u, {NULL, 0u}, 0u, NULL};
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_value_create_array(facts, &array), RE_STATUS_OK);
    ASSERT_EQ(re_value_array_append(array, &item), RE_STATUS_OK);
    item.as.int64_value = 5;
    ASSERT_EQ(re_value_array_append(array, &item), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set_value(facts, text("Values"), array), RE_STATUS_OK);
    re_value_destroy(array);
    ASSERT_EQ(re_program_load(NULL, text(
        "rule \"All\" { when forall Values >= 3 then D = 1; }"), NULL, &program),
        RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("D"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.as.int64_value, 1);
    ASSERT_TRUE(re_facts_is_logical(facts, d_id));
    ASSERT_EQ(re_facts_provenance_get(facts, d_id, &provenance), RE_STATUS_OK);
    ASSERT_TRUE(name_is(provenance.producer_rule, "All"));
    ASSERT_EQ(provenance.premise_count, 1u);
    ASSERT_EQ(provenance.premises[0].slot, 0u);
    ASSERT_EQ(provenance.premises[0].generation, 0u);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(read_set_cap_truncates_provenance_not_derivation) {
    /* Nine distinct fact reads exceed RE_IR_MAX_READ_PATHS (8): recording
     * stops silently at the cap, so the justification carries the first eight
     * premises in read order while the derivation itself is unaffected. */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_fact_id_t ids[9];
    re_fact_id_t d_id = {9u, 1u}; /* F1..F9 inserted first; D derived tenth */
    re_value_t one = {RE_VALUE_INT64, {.int64_value = 1}};
    re_value_t out = {RE_VALUE_NONE, {0}};
    re_fact_provenance_t provenance = {sizeof(provenance), 0u, {NULL, 0u}, 0u, NULL};
    size_t i;
    char name[3];
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    for (i = 0u; i < 9u; ++i) {
        name[0] = 'F';
        name[1] = (char)('1' + i);
        name[2] = '\0';
        ASSERT_EQ(re_facts_insert(facts, text(name), &one, &ids[i]), RE_STATUS_OK);
    }
    ASSERT_EQ(re_program_load(NULL, text(
        "rule \"Wide\" { when F1 + F2 + F3 + F4 + F5 + F6 + F7 + F8 + F9 > 8 then D = 1; }"),
        NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    /* The ninth read is dropped from the provenance record, not from the
     * condition: the rule still derives D from the full 9-fact sum. */
    ASSERT_EQ(re_facts_get(facts, text("D"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.as.int64_value, 1);
    ASSERT_TRUE(re_facts_is_logical(facts, d_id));
    ASSERT_EQ(re_facts_provenance_get(facts, d_id, &provenance), RE_STATUS_OK);
    ASSERT_TRUE(name_is(provenance.producer_rule, "Wide"));
    ASSERT_EQ(provenance.premise_count, 8u);
    for (i = 0u; i < 8u; ++i) {
        ASSERT_EQ(provenance.premises[i].slot, ids[i].slot);
        ASSERT_EQ(provenance.premises[i].generation, ids[i].generation);
    }
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST_MAIN_BEGIN()
    RUN_TEST(agenda_create_destroy);
    RUN_TEST(agenda_push_dedups_pending_order_insensitive);
    RUN_TEST(agenda_pop_orders_by_salience_then_sequence);
    RUN_TEST(agenda_mark_fired_refracts_and_dedups);
    RUN_TEST(agenda_clear_pending_keeps_fired_reset_clears_both);
    RUN_TEST(agenda_push_validates_arguments);
    RUN_TEST(agenda_grows_beyond_initial_capacity);
    RUN_TEST(agenda_engine_lazy_create_and_destroy);
    RUN_TEST(chained_rules_reactivate_within_one_run);
    RUN_TEST(refraction_prevents_self_refire);
    RUN_TEST(changed_premise_reactivates_same_rule);
    RUN_TEST(max_firings_limit_still_bounds_loop);
    RUN_TEST(salience_order_preserved_across_cycles);
    RUN_TEST(rete_activation_event_carries_token_sequence);
    RUN_TEST(stale_pending_activation_is_discarded);
    RUN_TEST(agenda_api_replaces_not_supported_stub);
    RUN_TEST(persistent_agenda_refires_only_on_premise_change);
    RUN_TEST(agenda_peek_reports_pending_in_salience_order);
    RUN_TEST(tms_retraction_cancels_pending_activation);
    RUN_TEST(non_persistent_default_unchanged);
    RUN_TEST(agenda_rete_capability_reported_with_attached_networks);
    RUN_TEST(and_second_condition_gates_linear_path);
    RUN_TEST(or_requires_one_true_side);
    RUN_TEST(and_gate_agrees_with_rete_network);
    RUN_TEST(dotted_target_writes_member_with_root_provenance);
    RUN_TEST(dotted_target_creates_member_on_structured_root);
    RUN_TEST(dotted_target_without_structured_root_keeps_flat_shadow);
    RUN_TEST(linear_path_derivation_records_provenance);
    RUN_TEST(provenance_cascade_retracts_linear_derived);
    RUN_TEST(multi_producer_justifications_accumulate);
    RUN_TEST(linear_rule_reactivates_on_premise_value_change_within_run);
    RUN_TEST(linear_rule_refraction_persistent_across_runs);
    RUN_TEST(agenda_peek_shows_linear_true_premises);
    RUN_TEST(persistent_agenda_survives_cancelled_exit);
    RUN_TEST(exists_condition_records_read_premise);
    RUN_TEST(forall_condition_records_read_premise);
    RUN_TEST(read_set_cap_truncates_provenance_not_derivation);
TEST_MAIN_END()
