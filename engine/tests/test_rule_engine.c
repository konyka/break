#include "test_framework.h"
#include <rule_engine/rule_engine.h>
#include <string.h>

static re_string_t text(const char *value) {
    re_string_t result = {value, strlen(value)};
    return result;
}

typedef struct allocator_state_t {
    size_t calls;
    size_t fail_at;
    size_t frees;
} allocator_state_t;

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

static void require_implementation(void) {
}

TEST(c99_header_contract) {
    /* Given the public header, when compiled as C99, then its types are usable. */
    re_value_t value = {RE_VALUE_INT64, {.int64_value = 42}};
    re_limits_t limits = {0};
    re_run_options_t options = {&limits, NULL, NULL};
    re_callbacks_t callbacks = {NULL, NULL};

    ASSERT_EQ(value.type, RE_VALUE_INT64);
    ASSERT_EQ(value.as.int64_value, 42);
    ASSERT_TRUE(options.limits == &limits);
    ASSERT_TRUE(callbacks.action == NULL);
}

TEST(facts_copy_and_get_semantics) {
    /* Given caller-owned fact buffers, when they are mutated after set, then get returns copies. */
    require_implementation();
    re_facts_t *facts = re_facts_create(NULL, NULL);
    ASSERT_NOT_NULL(facts);

    char name_storage[] = "Customer.Name";
    char value_storage[] = "Ada";
    re_value_t input = {RE_VALUE_STRING, {.string = {value_storage, 3}}};
    ASSERT_EQ(re_facts_set(facts, (re_string_t){name_storage, 13}, &input), RE_STATUS_OK);

    name_storage[0] = 'X';
    value_storage[0] = 'Z';
    re_value_t output = {RE_VALUE_NONE, {0}};
    ASSERT_EQ(re_facts_get(facts, text("Customer.Name"), &output), RE_STATUS_OK);
    ASSERT_EQ(output.type, RE_VALUE_STRING);
    ASSERT_EQ(output.as.string.size, 3u);
    ASSERT_TRUE(memcmp(output.as.string.data, "Ada", 3) == 0);
    ASSERT_EQ(re_facts_get(facts, text("missing"), &output), RE_STATUS_NOT_FOUND);
    re_facts_destroy(facts);
}

TEST(empty_strings_compare_and_copy) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_value_t empty = {RE_VALUE_STRING, {.string = {NULL, 0u}}};
    re_value_t output = {RE_VALUE_NONE, {0}};
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_facts_set(facts, text("Empty"), &empty), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("Empty"), &output), RE_STATUS_OK);
    ASSERT_EQ(output.type, RE_VALUE_STRING);
    ASSERT_EQ(output.as.string.size, 0u);
    ASSERT_NOT_NULL(output.as.string.data);
    ASSERT_EQ(re_program_load(NULL, text("rule \"Empty\" { when Empty == \"\" then Result = 1; }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

typedef struct action_state_t {
    size_t count;
} action_state_t;

static re_status_t count_event(re_engine_t *engine, re_facts_t *facts,
                               const re_rule_event_t *event, void *context) {
    action_state_t *state = context;
    (void)engine;
    (void)facts;
    (void)event;
    state->count++;
    return RE_STATUS_OK;
}

static void run_program(re_engine_t *engine, re_facts_t *facts, const char *source,
                        const re_callbacks_t *callbacks) {
    re_program_t *program = NULL;
    ASSERT_EQ(re_program_load(NULL, text(source), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, callbacks), RE_STATUS_OK);
}

TEST(then_literal_assignment_updates_facts_and_callback) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t output = {RE_VALUE_NONE, {0}};
    action_state_t state = {0u};
    re_callbacks_t callbacks = {count_event, &state};
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    run_program(engine, facts, "rule \"Set\" { when true then User.firstName = \"Ada\"; }", &callbacks);
    ASSERT_EQ(state.count, 1u);
    ASSERT_EQ(re_facts_get(facts, text("User.firstName"), &output), RE_STATUS_OK);
    ASSERT_EQ(output.type, RE_VALUE_STRING);
    ASSERT_EQ(output.as.string.size, 3u);
    ASSERT_TRUE(memcmp(output.as.string.data, "Ada", 3u) == 0);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(then_fact_reference_assignment_updates_facts_and_callback) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t input = {RE_VALUE_STRING, {.string = {"Ada", 3u}}};
    re_value_t output = {RE_VALUE_NONE, {0}};
    action_state_t state = {0u};
    re_callbacks_t callbacks = {count_event, &state};
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_facts_set(facts, text("User.firstName"), &input), RE_STATUS_OK);
    run_program(engine, facts, "rule \"Copy\" { when true then User.firstNameAgain = User.firstName; }", &callbacks);
    ASSERT_EQ(state.count, 1u);
    ASSERT_EQ(re_facts_get(facts, text("User.firstNameAgain"), &output), RE_STATUS_OK);
    ASSERT_EQ(output.type, RE_VALUE_STRING);
    ASSERT_EQ(output.as.string.size, 3u);
    ASSERT_TRUE(memcmp(output.as.string.data, "Ada", 3u) == 0);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(dotted_fact_lookup_prefers_exact_flat_key) {
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t flat = {RE_VALUE_INT64, {.int64_value = 7}};
    re_value_t parent = {RE_VALUE_INT64, {.int64_value = 3}};
    re_value_t output = {RE_VALUE_NONE, {0}};
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_facts_set(facts, text("User.firstName"), &flat), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("User"), &parent), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("User.firstName"), &output), RE_STATUS_OK);
    ASSERT_EQ(output.as.int64_value, 7);
    re_facts_destroy(facts);
}

TEST(run_limits_have_independent_inclusive_boundaries) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    action_state_t state = {0u};
    re_callbacks_t callbacks = {count_event, &state};
    re_limits_t agenda_limit = {0u, 0u, 0u, 1u, 0u};
    re_limits_t firing_limit = {0u, 0u, 0u, 0u, 1u};
    re_run_options_t options = {&agenda_limit, NULL, NULL};
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_program_load(NULL, text("rule \"One\" { when true then One = 1; } rule \"Two\" { when true then Two = 2; }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, &options, &callbacks), RE_STATUS_LIMIT);
    ASSERT_EQ(state.count, 1u);
    state.count = 0u;
    options.limits = &firing_limit;
    ASSERT_EQ(re_engine_run(engine, facts, &options, &callbacks), RE_STATUS_LIMIT);
    ASSERT_EQ(state.count, 1u);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(boolean_values_are_normalized) {
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t input = {RE_VALUE_BOOL, {.boolean = 7}};
    re_value_t output = {RE_VALUE_NONE, {0}};
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_facts_set(facts, text("Flag"), &input), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("Flag"), &output), RE_STATUS_OK);
    ASSERT_EQ(output.type, RE_VALUE_BOOL);
    ASSERT_EQ(output.as.boolean, 1);
    input.as.boolean = -4;
    ASSERT_EQ(re_facts_set(facts, text("Flag"), &input), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("Flag"), &output), RE_STATUS_OK);
    ASSERT_EQ(output.as.boolean, 1);
    re_facts_destroy(facts);
}

TEST(exact_independent_limits_are_inclusive) {
    re_limits_t limits = {0u, 1u, 1u, 0u, 0u};
    re_facts_t *facts = re_facts_create(NULL, &limits);
    re_program_t *program = NULL;
    re_value_t value = {RE_VALUE_INT64, {.int64_value = 1}};
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_facts_set(facts, text("One"), &value), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("Two"), &value), RE_STATUS_LIMIT);
    ASSERT_EQ(re_program_load(NULL, text("rule \"One\" { when true then One = 1; }"), &limits, &program), RE_STATUS_OK);
    ASSERT_NOT_NULL(program);
    re_program_destroy(program);
    program = NULL;
    ASSERT_EQ(re_program_load(NULL, text("rule \"One\" { when true then One = 1; } rule \"Two\" { when true then Two = 2; }"), &limits, &program), RE_STATUS_LIMIT);
    ASSERT_TRUE(program == NULL);
    re_facts_destroy(facts);
}

static re_status_t mutate_fact(re_engine_t *engine, re_facts_t *facts,
                               const re_rule_event_t *event, void *context) {
    re_value_t value = {RE_VALUE_INT64, {.int64_value = 99}};
    (void)engine;
    (void)event;
    (void)context;
    return re_facts_set(facts, text("Mutated"), &value);
}

TEST(callback_can_mutate_facts) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_value_t output = {RE_VALUE_NONE, {0}};
    re_callbacks_t callbacks = {mutate_fact, NULL};
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_program_load(NULL, text("rule \"Mutate\" { when true then Target = 1; }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, &callbacks), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("Mutated"), &output), RE_STATUS_OK);
    ASSERT_EQ(output.as.int64_value, 99);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(string_copy_is_freed_when_fact_capacity_growth_fails) {
    allocator_state_t state = {0u, 5u, 0u};
    re_allocator_t allocator = {&state, test_alloc, test_realloc, test_free};
    re_facts_t *facts = re_facts_create(&allocator, NULL);
    re_value_t number = {RE_VALUE_INT64, {.int64_value = 1}};
    re_value_t string = {RE_VALUE_STRING, {.string = {"value", 5u}}};
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_facts_set(facts, text("First"), &number), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("Second"), &string), RE_STATUS_OUT_OF_MEMORY);
    ASSERT_EQ(state.frees, 1u);
    re_facts_destroy(facts);
}

TEST(bounded_source_and_numeric_range) {
    re_program_t *program = NULL;
    char source[] = "rule \"N\" { when true then N = 1; }tail";
    size_t valid_size = strlen("rule \"N\" { when true then N = 1; }");
    ASSERT_EQ(re_program_load(NULL, (re_string_t){source, valid_size}, NULL, &program), RE_STATUS_OK);
    ASSERT_NOT_NULL(program);
    re_program_destroy(program);
    program = NULL;
    ASSERT_EQ(re_program_load(NULL, (re_string_t){source, strlen(source)}, NULL, &program), RE_STATUS_PARSE_ERROR);
    ASSERT_TRUE(program == NULL);
}

TEST(allocator_failure_status_propagates) {
    allocator_state_t state = {0u, 2u, 0u};
    re_allocator_t allocator = {&state, test_alloc, test_realloc, test_free};
    re_program_t *program = NULL;
    ASSERT_EQ(re_program_load(&allocator, text("rule \"N\" { when true then N = 1; }"), NULL, &program), RE_STATUS_OUT_OF_MEMORY);
    ASSERT_TRUE(program == NULL);
}

TEST(overflow_length_is_rejected_before_allocator) {
    allocator_state_t state = {0u, 0u, 0u};
    re_allocator_t allocator = {&state, test_alloc, test_realloc, test_free};
    re_program_t *program = NULL;
    re_string_t oversized = {(const char *)1, (size_t)-1};
    re_limits_t limits = {(size_t)-1, 0u, 0u, 0u, 0u};
    ASSERT_EQ(re_program_load(&allocator, oversized, &limits, &program), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_TRUE(program == NULL);
    ASSERT_EQ(state.calls, 1u);
}

static re_status_t destroy_in_callback(re_engine_t *engine, re_facts_t *facts,
                                       const re_rule_event_t *event, void *context) {
    (void)event;
    (void)context;
    re_engine_destroy(engine);
    re_facts_destroy(facts);
    return RE_STATUS_OK;
}

TEST(callback_destroy_is_deferred) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_callbacks_t callbacks = {destroy_in_callback, NULL};
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_program_load(NULL, text("rule \"N\" { when true then N = 1; }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, &callbacks), RE_STATUS_OK);
}

TEST(program_load_failure_is_transactional) {
    /* Given an installed program, when malformed source is loaded, then the current program remains usable. */
    require_implementation();
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    re_program_t *good = NULL;
    ASSERT_EQ(re_program_load(NULL, text("rule \"Keep\" { when true then Customer.Count = 1; }"), NULL, &good), RE_STATUS_OK);
    ASSERT_NOT_NULL(good);
    ASSERT_EQ(re_engine_install(engine, good), RE_STATUS_OK);

    re_program_t *bad = NULL;
    ASSERT_EQ(re_program_load(NULL, text("rule { malformed"), NULL, &bad), RE_STATUS_PARSE_ERROR);
    ASSERT_TRUE(bad == NULL);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

typedef struct callback_state_t {
    size_t count;
    int32_t salience;
    uint64_t sequence;
} callback_state_t;

static re_status_t record_event(re_engine_t *engine, re_facts_t *facts,
                                const re_rule_event_t *event, void *context) {
    callback_state_t *state = context;
    (void)engine;
    (void)facts;
    state->count++;
    state->salience = event->salience;
    state->sequence = event->activation_sequence;
    if (event->rule_name.size != 3u || memcmp(event->rule_name.data, "VIP", 3) != 0)
        return RE_STATUS_ERROR;
    return RE_STATUS_OK;
}

TEST(successful_install_run_is_deterministic) {
    /* Given matching facts and an installed program, when run twice, then events are stable. */
    require_implementation();
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    re_program_t *program = NULL;
    ASSERT_EQ(re_program_load(NULL, text("rule \"VIP\" { when Customer.TotalSpent > 10000 then Customer.Count = 1; }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);

    re_value_t spent = {RE_VALUE_DOUBLE, {.double_value = 15000.0}};
    ASSERT_EQ(re_facts_set(facts, text("Customer.TotalSpent"), &spent), RE_STATUS_OK);
    callback_state_t first = {0};
    re_callbacks_t callbacks = {record_event, &first};
    ASSERT_EQ(re_engine_run(engine, facts, NULL, &callbacks), RE_STATUS_OK);
    ASSERT_EQ(first.count, 1u);
    ASSERT_EQ(first.salience, 0);
    ASSERT_EQ(first.sequence, 1u);

    callback_state_t second = {0};
    callbacks.context = &second;
    ASSERT_EQ(re_engine_run(engine, facts, NULL, &callbacks), RE_STATUS_OK);
    ASSERT_EQ(second.count, first.count);
    ASSERT_EQ(second.salience, first.salience);
    ASSERT_EQ(second.sequence, first.sequence);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

typedef struct rule_order_state_t {
    const char *names[4];
    size_t count;
} rule_order_state_t;

static re_status_t record_rule_order(re_engine_t *engine, re_facts_t *facts,
                                     const re_rule_event_t *event,
                                     void *context) {
    rule_order_state_t *state = (rule_order_state_t *)context;
    (void)engine;
    (void)facts;
    if (state->count >= sizeof(state->names) / sizeof(state->names[0])) {
        return RE_STATUS_ERROR;
    }
    state->names[state->count++] = event->rule_name.data;
    return RE_STATUS_OK;
}

TEST(salience_orders_activations_stably) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    rule_order_state_t state = {{0}, 0u};
    re_callbacks_t callbacks = {record_rule_order, &state};

    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_program_load(NULL,
        text("rule \"Low\" salience -5 { when true then Low = 1; }"
             "rule \"High\" salience 10 { when true then High = 1; }"
             "rule \"Tie\" salience 10 { when true then Tie = 1; }"),
        NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, &callbacks), RE_STATUS_OK);
    ASSERT_EQ(state.count, 3u);
    ASSERT_EQ(state.names[0][0], 'H');
    ASSERT_EQ(state.names[1][0], 'T');
    ASSERT_EQ(state.names[2][0], 'L');
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(salience_rejects_invalid_integer_ranges) {
    re_program_t *program = NULL;
    ASSERT_EQ(re_program_load(NULL,
        text("rule \"TooHigh\" salience 2147483648 { when true then A = 1; }"),
        NULL, &program), RE_STATUS_PARSE_ERROR);
    ASSERT_TRUE(program == NULL);
    ASSERT_EQ(re_program_load(NULL,
        text("rule \"TooLow\" salience -2147483649 { when true then A = 1; }"),
        NULL, &program), RE_STATUS_PARSE_ERROR);
    ASSERT_TRUE(program == NULL);
    ASSERT_EQ(re_program_load(NULL,
        text("rule \"Malformed\" salience 10x { when true then A = 1; }"),
        NULL, &program), RE_STATUS_PARSE_ERROR);
    ASSERT_TRUE(program == NULL);
}

static int cancel_now(void *context) {
    int *calls = context;
    (*calls)++;
    return 1;
}

TEST(run_honors_cancellation_and_limits) {
    /* Given cancellation and limit options, when execution starts, then it stops with their statuses. */
    require_implementation();
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    re_program_t *program = NULL;
    ASSERT_EQ(re_program_load(NULL, text("rule \"Loop\" { when true then Customer.Count = 1; }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);

    int cancel_calls = 0;
    re_run_options_t cancelled = {NULL, cancel_now, &cancel_calls};
    ASSERT_EQ(re_engine_run(engine, facts, &cancelled, NULL), RE_STATUS_CANCELLED);
    ASSERT_TRUE(cancel_calls > 0);

    re_limits_t limits = {0, 0, 0, 0, 1};
    re_run_options_t limited = {&limits, NULL, NULL};
    ASSERT_EQ(re_engine_run(engine, facts, &limited, NULL), RE_STATUS_LIMIT);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(deferred_capabilities_are_explicitly_unsupported) {
    /* Given a valid engine, when capabilities are queried, then only ABI-defined bits are reported. */
    require_implementation();
    ASSERT_EQ(re_engine_capabilities(NULL), 0u);
    re_engine_t *engine = re_engine_create(NULL, NULL);
    ASSERT_NOT_NULL(engine);
    ASSERT_FALSE((re_engine_capabilities(engine) & RE_CAP_FORWARD_EXECUTION) == 0u);
    ASSERT_TRUE((re_engine_capabilities(engine) & RE_CAP_CORE_GRL) != 0u);
    ASSERT_TRUE((re_engine_capabilities(engine) & RE_CAP_FACTS) != 0u);
    re_engine_destroy(engine);
}

TEST_MAIN_BEGIN()
    RUN_TEST(c99_header_contract);
    RUN_TEST(facts_copy_and_get_semantics);
    RUN_TEST(empty_strings_compare_and_copy);
    RUN_TEST(then_literal_assignment_updates_facts_and_callback);
    RUN_TEST(then_fact_reference_assignment_updates_facts_and_callback);
    RUN_TEST(dotted_fact_lookup_prefers_exact_flat_key);
    RUN_TEST(run_limits_have_independent_inclusive_boundaries);
    RUN_TEST(boolean_values_are_normalized);
    RUN_TEST(exact_independent_limits_are_inclusive);
    RUN_TEST(callback_can_mutate_facts);
    RUN_TEST(string_copy_is_freed_when_fact_capacity_growth_fails);
    RUN_TEST(bounded_source_and_numeric_range);
    RUN_TEST(allocator_failure_status_propagates);
    RUN_TEST(overflow_length_is_rejected_before_allocator);
    RUN_TEST(callback_destroy_is_deferred);
    RUN_TEST(program_load_failure_is_transactional);
    RUN_TEST(successful_install_run_is_deterministic);
    RUN_TEST(salience_orders_activations_stably);
    RUN_TEST(salience_rejects_invalid_integer_ranges);
    RUN_TEST(run_honors_cancellation_and_limits);
    RUN_TEST(deferred_capabilities_are_explicitly_unsupported);
TEST_MAIN_END()
