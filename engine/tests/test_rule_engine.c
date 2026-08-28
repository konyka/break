#include "test_framework.h"
#include <rule_engine/rule_engine.h>
#include "../src/rule_engine/re_internal.h"
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
                               const re_rule_event_t *event, void *context);

typedef struct function_state_t {
    size_t calls;
    size_t releases;
    int reenter_status;
} function_state_t;

static re_status_t add_function(re_engine_t *engine, re_facts_t *facts,
                                const re_value_t *arguments, size_t count,
                                re_value_t *out, void *context) {
    function_state_t *state = context;
    (void)engine;
    (void)facts;
    state->calls++;
    if (count != 2u || arguments[0].type != RE_VALUE_INT64 ||
        arguments[1].type != RE_VALUE_INT64) return RE_STATUS_INVALID_ARGUMENT;
    out->type = RE_VALUE_INT64;
    out->as.int64_value = arguments[0].as.int64_value + arguments[1].as.int64_value;
    return RE_STATUS_OK;
}

TEST(private_rete_two_condition_join_lifecycle) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_rete_network_t *network = NULL;
    re_rete_activation_t activation;
    re_rete_network_t *engine_network = NULL;
    re_fact_id_t left_id;
    re_fact_id_t right_id;
    re_value_t left = {RE_VALUE_INT64, {.int64_value = 7}};
    re_value_t right = {RE_VALUE_STRING, {.string = {"ready", 5u}}};
    re_value_t updated = {RE_VALUE_STRING, {.string = {"blocked", 7u}}};
    re_rete_condition_t conditions[2] = {
        {{"Order.total", 11u}, RE_COMPARE_GT, {RE_VALUE_INT64, {.int64_value = 5}}},
        {{"Order.state", 11u}, RE_COMPARE_EQ, {RE_VALUE_STRING, {.string = {"ready", 5u}}}}
    };
    re_program_t *program = NULL;
    action_state_t state = {0u};
    re_callbacks_t callbacks = {count_event, &state};
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_rete_network_create(facts, conditions, NULL, &network), RE_STATUS_OK);
    ASSERT_EQ(re_rete_activation_count(network), 0u);
    ASSERT_EQ(re_facts_insert(facts, (re_string_t){"Order.total", 11u}, &left, &left_id), RE_STATUS_OK);
    ASSERT_EQ(re_rete_activation_count(network), 0u);
    ASSERT_EQ(re_facts_insert(facts, (re_string_t){"Order.state", 11u}, &right, &right_id), RE_STATUS_OK);
    ASSERT_EQ(re_rete_activation_count(network), 1u);
    ASSERT_EQ(re_rete_activation_get(network, 0u, &activation), RE_STATUS_OK);
    ASSERT_EQ(activation.left.slot, left_id.slot);
    ASSERT_EQ(activation.left.generation, left_id.generation);
    ASSERT_EQ(activation.right.slot, right_id.slot);
    ASSERT_EQ(activation.right.generation, right_id.generation);
    ASSERT_EQ(activation.sequence, 1u);
    ASSERT_EQ(re_program_load(NULL, text("rule \"Join\" { when Order.total > 5 and Order.state == \"ready\" then Result = 1; }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, &callbacks), RE_STATUS_OK);
    ASSERT_EQ(state.count, 1u);
    ASSERT_EQ(re_engine_rete_network(engine, &engine_network), RE_STATUS_NOT_SUPPORTED);
    ASSERT_TRUE(engine_network == NULL);
    ASSERT_EQ(re_rete_activation_get(network, 0u, &activation), RE_STATUS_OK);
    ASSERT_EQ(activation.left.slot, left_id.slot);
    ASSERT_EQ(activation.left.generation, left_id.generation);
    ASSERT_EQ(activation.right.slot, right_id.slot);
    ASSERT_EQ(activation.right.generation, right_id.generation);
    ASSERT_EQ(activation.sequence, 1u);
    ASSERT_EQ(re_facts_update(facts, right_id, &updated), RE_STATUS_OK);
    ASSERT_EQ(re_rete_activation_count(network), 0u);
    ASSERT_EQ(re_facts_update(facts, right_id, &right), RE_STATUS_OK);
    ASSERT_EQ(re_rete_activation_count(network), 1u);
    ASSERT_EQ(re_facts_retract(facts, left_id), RE_STATUS_OK);
    ASSERT_EQ(re_rete_activation_count(network), 0u);
    re_engine_destroy(engine);
    re_facts_destroy(facts);
}

static re_status_t failing_function(re_engine_t *engine, re_facts_t *facts,
                                    const re_value_t *arguments, size_t count,
                                    re_value_t *out, void *context) {
    function_state_t *state = context;
    (void)engine; (void)facts; (void)arguments; (void)count; (void)out;
    state->calls++;
    return RE_STATUS_ERROR;
}

static void release_function(void *context) {
    function_state_t *state = context;
    state->releases++;
}

static re_status_t count_event(re_engine_t *engine, re_facts_t *facts,
                               const re_rule_event_t *event, void *context) {
    action_state_t *state = context;
    (void)engine;
    (void)facts;
    (void)event;
    state->count++;
    return RE_STATUS_OK;
}

static re_status_t failing_action_callback(re_engine_t *engine, re_facts_t *facts,
                                            const re_rule_event_t *event, void *context) {
    (void)engine;
    (void)facts;
    (void)event;
    (void)context;
    return RE_STATUS_ERROR;
}

TEST(forward_multi_action_failure_rolls_back_earlier_action) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_value_t output = {RE_VALUE_NONE, {0}};
    re_function_t *function = NULL;
    function_state_t function_state = {0u, 0u, 0};
    re_function_descriptor_t descriptor = {sizeof(descriptor), RE_ABI_VERSION_MAJOR,
        {"fail", 4u}, failing_function, NULL, &function_state};
    ASSERT_EQ(re_engine_register_function(engine, &descriptor, &function), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text("rule \"Fail\" { when true then First = 1; Result = fail(); }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_ERROR);
    ASSERT_EQ(re_facts_get(facts, text("First"), &output), RE_STATUS_NOT_FOUND);
    re_function_unregister(function);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(forward_multi_action_success_commits_all_actions) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_value_t output = {RE_VALUE_NONE, {0}};
    ASSERT_EQ(re_program_load(NULL, text("rule \"Set\" { when true then First = 1; Second = 2; }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("First"), &output), RE_STATUS_OK);
    ASSERT_EQ(output.as.int64_value, 1);
    ASSERT_EQ(re_facts_get(facts, text("Second"), &output), RE_STATUS_OK);
    ASSERT_EQ(output.as.int64_value, 2);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(forward_callback_failure_rolls_back_action_mutations) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_value_t output = {RE_VALUE_NONE, {0}};
    re_callbacks_t callbacks = {failing_action_callback, NULL};
    ASSERT_EQ(re_program_load(NULL, text("rule \"Fail\" { when true then First = 1; }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, &callbacks), RE_STATUS_ERROR);
    ASSERT_EQ(re_facts_get(facts, text("First"), &output), RE_STATUS_NOT_FOUND);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
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

TEST(custom_function_is_registered_and_invoked_in_condition) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_function_t *function = NULL;
    function_state_t state = {0u, 0u, 0};
    re_function_descriptor_t descriptor = {sizeof(descriptor), RE_ABI_VERSION_MAJOR,
        {"add", 3u}, add_function, release_function, &state};
    re_value_t output = {RE_VALUE_NONE, {0}};
    ASSERT_EQ(re_engine_register_function(engine, &descriptor, &function), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"Computed\" { when add(1, 2) == 3 then Result = add(4, 5); }", NULL);
    ASSERT_EQ(state.calls, 2u);
    ASSERT_EQ(re_facts_get(facts, text("Result"), &output), RE_STATUS_OK);
    ASSERT_EQ(output.as.int64_value, 9);
    re_function_unregister(function);
    ASSERT_EQ(state.releases, 1u);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(custom_function_errors_propagate_from_action) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_function_t *function = NULL;
    function_state_t state = {0u, 0u, 0};
    re_function_descriptor_t descriptor = {sizeof(descriptor), RE_ABI_VERSION_MAJOR,
        {"fail", 4u}, failing_function, release_function, &state};
    ASSERT_EQ(re_engine_register_function(engine, &descriptor, &function), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text("rule \"Fail\" { when true then Result = fail(); }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_ERROR);
    ASSERT_EQ(state.calls, 1u);
    re_function_unregister(function);
    ASSERT_EQ(state.releases, 1u);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(custom_function_registration_validates_descriptor_and_reentrancy) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_function_t *function = NULL;
    re_capabilities_v2_t capabilities = 0u;
    re_extension_info_t info = {sizeof(info), 0u, 0u, 0u, 0u, 0u, 0u};
    re_function_descriptor_t invalid = {sizeof(invalid), RE_ABI_VERSION_MAJOR,
        {"bad", 3u}, NULL, NULL, NULL};
    ASSERT_EQ(re_engine_register_function(engine, &invalid, &function), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_engine_capabilities_v2(engine, RE_ABI_VERSION_MAJOR, NULL), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_engine_capabilities_v2(engine, RE_ABI_VERSION_MAJOR, &capabilities), RE_STATUS_OK);
    ASSERT_TRUE((capabilities & RE_CAP2_CUSTOM_FUNCTIONS) != 0u);
    ASSERT_EQ(re_engine_extension_info(engine, RE_EXTENSION_CUSTOM_FUNCTIONS, 1u, &info), RE_STATUS_OK);
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

TEST(structured_values_support_nested_objects_and_arrays) {
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_handle_t *customer = NULL;
    re_value_handle_t *address = NULL;
    re_value_handle_t *tags = NULL;
    re_value_t city = {RE_VALUE_STRING, {.string = {"Paris", 5u}}};
    re_value_t tag = {RE_VALUE_STRING, {.string = {"vip", 3u}}};
    re_value_t output = {RE_VALUE_NONE, {0}};
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_value_create_object(facts, &customer), RE_STATUS_OK);
    ASSERT_EQ(re_value_create_object(facts, &address), RE_STATUS_OK);
    ASSERT_EQ(re_value_create_array(facts, &tags), RE_STATUS_OK);
    ASSERT_EQ(re_value_object_set(address, text("City"), &city), RE_STATUS_OK);
    ASSERT_EQ(re_value_array_append(tags, &tag), RE_STATUS_OK);
    ASSERT_EQ(re_value_object_set_value(customer, text("Address"), address), RE_STATUS_OK);
    ASSERT_EQ(re_value_object_set_value(customer, text("Tags"), tags), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set_value(facts, text("Customer"), customer), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get_path(facts, text("Customer.Address.City"), &output), RE_STATUS_OK);
    ASSERT_EQ(output.type, RE_VALUE_STRING);
    ASSERT_TRUE(memcmp(output.as.string.data, "Paris", 5u) == 0);
    re_value_destroy(tags);
    re_value_destroy(address);
    re_value_destroy(customer);
    re_facts_destroy(facts);
}

TEST(null_missing_and_unknown_are_distinct) {
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t null_value = {RE_VALUE_NULL, {0}};
    re_value_t unknown_value = {RE_VALUE_UNKNOWN, {0}};
    re_value_t output = {RE_VALUE_NONE, {0}};
    ASSERT_EQ(re_facts_set(facts, text("Null"), &null_value), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("Unknown"), &unknown_value), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("Null"), &output), RE_STATUS_OK);
    ASSERT_EQ(output.type, RE_VALUE_NULL);
    ASSERT_EQ(re_facts_get(facts, text("Unknown"), &output), RE_STATUS_OK);
    ASSERT_EQ(output.type, RE_VALUE_UNKNOWN);
    ASSERT_EQ(re_facts_get(facts, text("Missing"), &output), RE_STATUS_NOT_FOUND);
    re_facts_destroy(facts);
}

TEST(fact_lifecycle_ids_are_generation_safe_and_notify) {
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_fact_id_t first = {0u, 0u};
    re_fact_id_t second = {0u, 0u};
    re_value_t one = {RE_VALUE_INT64, {.int64_value = 1}};
    re_value_t two = {RE_VALUE_INT64, {.int64_value = 2}};
    ASSERT_EQ(re_facts_insert(facts, text("Score"), &one, &first), RE_STATUS_OK);
    ASSERT_EQ(re_facts_update(facts, first, &two), RE_STATUS_OK);
    ASSERT_EQ(re_facts_retract(facts, first), RE_STATUS_OK);
    ASSERT_EQ(re_facts_insert(facts, text("Score"), &one, &second), RE_STATUS_OK);
    ASSERT_TRUE(second.generation != first.generation || second.slot != first.slot);
    ASSERT_EQ(re_facts_update(facts, first, &two), RE_STATUS_NOT_FOUND);
    re_facts_destroy(facts);
}

typedef struct fact_event_state_t {
    size_t count;
    re_fact_change_kind_t last_kind;
    re_fact_id_t last_id;
    size_t last_name_size;
    const char *last_value_data;
    size_t last_value_size;
} fact_event_state_t;

static re_status_t record_fact_event(re_facts_t *facts, const re_fact_event_t *event, void *context) {
    fact_event_state_t *state = context;
    (void)facts;
    state->count++;
    state->last_kind = event->kind;
    state->last_id = event->id;
    state->last_name_size = event->name.size;
    if (event->value.type == RE_VALUE_STRING) {
        state->last_value_data = event->value.as.string.data;
        state->last_value_size = event->value.as.string.size;
    }
    return RE_STATUS_OK;
}

TEST(fact_lifecycle_notifications_provide_change_snapshots) {
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_subscription_t *subscription = NULL;
    fact_event_state_t state = {0u, 0, {0u, 0u}, 0u, NULL, 0u};
    re_fact_id_t id = {0u, 0u};
    re_value_t value = {RE_VALUE_INT64, {.int64_value = 1}};
    ASSERT_EQ(re_facts_subscribe(facts, record_fact_event, &state, &subscription), RE_STATUS_OK);
    ASSERT_EQ(re_facts_insert(facts, text("Score"), &value, &id), RE_STATUS_OK);
    ASSERT_EQ(state.count, 1u);
    ASSERT_EQ(state.last_kind, RE_FACT_INSERT);
    ASSERT_EQ(state.last_id.generation, id.generation);
    ASSERT_EQ(re_facts_update(facts, id, &value), RE_STATUS_OK);
    ASSERT_EQ(re_facts_retract(facts, id), RE_STATUS_OK);
    ASSERT_EQ(state.count, 3u);
    ASSERT_EQ(state.last_kind, RE_FACT_RETRACT);
    ASSERT_EQ(state.last_name_size, 5u);
    re_subscription_destroy(subscription);
    re_facts_destroy(facts);
}

TEST(run_limits_have_independent_inclusive_boundaries) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    action_state_t state = {0u};
    re_callbacks_t callbacks = {count_event, &state};
    re_limits_t agenda_limit = {0u, 0u, 0u, 1u, 0u, 0u};
    re_limits_t firing_limit = {0u, 0u, 0u, 0u, 1u, 0u};
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
    re_limits_t limits = {0u, 1u, 1u, 0u, 0u, 0u};
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

TEST(compound_conditions_and_multiple_actions_execute_in_order) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t score = {RE_VALUE_INT64, {.int64_value = 7}};
    re_value_t output = {RE_VALUE_NONE, {0}};
    ASSERT_EQ(re_facts_set(facts, text("Score"), &score), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"Compound\" { when (Score > 5 and not false) or Score == 0 "
        "then First = 1; Second = \"ok\"; }", NULL);
    ASSERT_EQ(re_facts_get(facts, text("First"), &output), RE_STATUS_OK);
    ASSERT_EQ(output.as.int64_value, 1);
    ASSERT_EQ(re_facts_get(facts, text("Second"), &output), RE_STATUS_OK);
    ASSERT_EQ(output.as.string.size, 2u);
    ASSERT_TRUE(memcmp(output.as.string.data, "ok", 2u) == 0);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(escaped_strings_are_unescaped) {
    re_program_t *program = NULL;
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t output = {RE_VALUE_NONE, {0}};
    ASSERT_EQ(re_program_load(NULL, text("rule \"Escaped\" { when true then Message = \"a\\\"b\\\\c\"; }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("Message"), &output), RE_STATUS_OK);
    ASSERT_EQ(output.as.string.size, 5u);
    ASSERT_TRUE(memcmp(output.as.string.data, "a\"b\\c", 5u) == 0);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(unknown_and_duplicate_attributes_fail_atomically) {
    re_program_t *program = NULL;
    ASSERT_EQ(re_program_load(NULL, text("rule \"Bad\" { unknown true; when true then X = 1; }"), NULL, &program), RE_STATUS_PARSE_ERROR);
    ASSERT_TRUE(program == NULL);
    ASSERT_EQ(re_program_load(NULL, text("rule \"Bad\" { salience 1; salience 2; when true then X = 1; }"), NULL, &program), RE_STATUS_PARSE_ERROR);
    ASSERT_TRUE(program == NULL);
}

TEST(private_modules_reject_cycles_and_resolve_exports) {
    re_program_t *program = NULL;
    ASSERT_EQ(re_program_load(NULL, text("defmodule A { export: all; import: B; } defmodule B { export: all; import: A; } rule \"R\" { when true then X = 1; }"), NULL, &program), RE_STATUS_PARSE_ERROR);
    ASSERT_TRUE(program == NULL);
    ASSERT_EQ(re_program_load(NULL, text("defmodule A { export: none; } defmodule B { import: A; } rule \"R\" { when true then X = 1; }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_program_set_module_focus(program, text("B")), RE_STATUS_OK);
    re_program_destroy(program);
}

TEST(private_accumulators_have_explicit_empty_and_numeric_rules) {
    re_value_t values[] = {{RE_VALUE_INT64, {.int64_value = 2}}, {RE_VALUE_DOUBLE, {.double_value = 4.0}}, {RE_VALUE_STRING, {.string = {"x", 1u}}}};
    re_value_t output = {RE_VALUE_NONE, {0}};
    ASSERT_EQ(re_accumulator_evaluate(RE_ACCUM_COUNT, values, 3u, &output), RE_STATUS_OK);
    ASSERT_EQ(output.type, RE_VALUE_INT64);
    ASSERT_EQ(output.as.int64_value, 3);
    ASSERT_EQ(re_accumulator_evaluate(RE_ACCUM_SUM, values, 3u, &output), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_accumulator_evaluate(RE_ACCUM_AVERAGE, NULL, 0u, &output), RE_STATUS_NOT_FOUND);
    ASSERT_EQ(re_accumulator_evaluate(RE_ACCUM_MIN, values, 2u, &output), RE_STATUS_OK);
    ASSERT_EQ(output.as.double_value, 2.0);
}

TEST(public_two_condition_join_uses_rete_network) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_rete_network_t *network = NULL;
    re_value_t total = {RE_VALUE_INT64, {.int64_value = 7}};
    re_value_t state_value = {RE_VALUE_STRING, {.string = {"ready", 5u}}};
    action_state_t state = {0u};
    re_callbacks_t callbacks = {count_event, &state};

    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_facts_set(facts, text("Order.total"), &total), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("Order.state"), &state_value), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text("rule \"Join\" { when Order.total > 5 and Order.state == \"ready\" then Result = 1; }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, &callbacks), RE_STATUS_OK);
    ASSERT_EQ(state.count, 1u);
    ASSERT_EQ(re_engine_rete_network(engine, &network), RE_STATUS_OK);
    re_engine_destroy(engine);
    re_facts_destroy(facts);
}

TEST(public_rete_supports_bounded_boolean_expression_and_nested_fact) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_rete_network_t *network = NULL;
    re_value_t total = {RE_VALUE_INT64, {.int64_value = 7}};
    re_value_t state_value = {RE_VALUE_STRING, {.string = {"ready", 5u}}};
    re_value_t city_value = {RE_VALUE_STRING, {.string = {"Paris", 5u}}};
    action_state_t state = {0u};
    re_callbacks_t callbacks = {count_event, &state};
    ASSERT_EQ(re_facts_set(facts, text("Order.total"), &total), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("Order.state"), &state_value), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("Customer.Address.City"), &city_value), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text("rule \"Complex\" { when (Order.total > 5 and Order.state == \"ready\") and not Customer.Address.City == \"Rome\" then Result = 1; }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, &callbacks), RE_STATUS_OK);
    ASSERT_EQ(state.count, 1u);
    ASSERT_EQ(re_engine_rete_network(engine, &network), RE_STATUS_NOT_SUPPORTED);
    ASSERT_TRUE(network == NULL);
    re_engine_destroy(engine);
    re_facts_destroy(facts);
}

TEST(fact_retract_notification_keeps_string_snapshot_alive) {
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_subscription_t *subscription = NULL;
    fact_event_state_t state = {0u, 0, {0u, 0u}, 0u, NULL, 0u};
    re_fact_id_t id = {0u, 0u};
    re_value_t value = {RE_VALUE_STRING, {.string = {"ready", 5u}}};
    ASSERT_EQ(re_facts_subscribe(facts, record_fact_event, &state, &subscription), RE_STATUS_OK);
    ASSERT_EQ(re_facts_insert(facts, text("State"), &value, &id), RE_STATUS_OK);
    ASSERT_EQ(re_facts_retract(facts, id), RE_STATUS_OK);
    ASSERT_EQ(state.last_kind, RE_FACT_RETRACT);
    ASSERT_EQ(state.last_value_size, 5u);
    ASSERT_TRUE(memcmp(state.last_value_data, "ready", 5u) == 0);
    re_subscription_destroy(subscription);
    re_facts_destroy(facts);
}

TEST(private_accumulators_preserve_mixed_numeric_precision) {
    re_value_t values[] = {{RE_VALUE_INT64, {.int64_value = 2}}, {RE_VALUE_DOUBLE, {.double_value = 0.5}}};
    re_value_t output = {RE_VALUE_NONE, {0}};
    ASSERT_EQ(re_accumulator_evaluate(RE_ACCUM_SUM, values, 2u, &output), RE_STATUS_OK);
    ASSERT_EQ(output.type, RE_VALUE_DOUBLE);
    ASSERT_EQ(output.as.double_value, 2.5);
    ASSERT_EQ(re_accumulator_evaluate(RE_ACCUM_AVERAGE, values, 2u, &output), RE_STATUS_OK);
    ASSERT_EQ(output.as.double_value, 1.25);
    ASSERT_EQ(re_accumulator_evaluate(RE_ACCUM_MAX, values, 2u, &output), RE_STATUS_OK);
    ASSERT_EQ(output.as.double_value, 2.0);
}

TEST(private_accumulators_reject_empty_and_non_numeric_values) {
    re_value_t text_value = {RE_VALUE_STRING, {.string = {"x", 1u}}};
    re_value_t output = {RE_VALUE_NONE, {0}};
    ASSERT_EQ(re_accumulator_evaluate(RE_ACCUM_SUM, NULL, 0u, &output), RE_STATUS_NOT_FOUND);
    ASSERT_EQ(re_accumulator_evaluate(RE_ACCUM_MIN, &text_value, 1u, &output), RE_STATUS_INVALID_ARGUMENT);
}

TEST(private_utc_rule_bounds_use_injected_clock) {
    re_program_t *program = NULL;
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t output = {RE_VALUE_NONE, {0}};
    ASSERT_EQ(re_program_load(NULL, text("rule \"Window\" { date-effective \"2025-01-01T00:00:00Z\"; date-expires \"2025-02-01T00:00:00Z\"; when true then X = 1; }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_program_set_clock(program, 1737000000), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("X"), &output), RE_STATUS_OK);
    ASSERT_EQ(output.as.int64_value, 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
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
    re_limits_t limits = {(size_t)-1, 0u, 0u, 0u, 0u, 0u};
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

TEST(array_literal_membership_matches_numeric_and_string_values) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_value_t value = {RE_VALUE_INT64, {.int64_value = 2}};
    re_value_t result = {RE_VALUE_NONE, {0}};
    ASSERT_EQ(re_facts_set(facts, text("Value"), &value), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text("rule \"In\" { when Value in [1, 2, \"two\"] then Result = 1; }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("Result"), &result), RE_STATUS_OK);
    ASSERT_EQ(result.as.int64_value, 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(array_membership_covers_positive_negative_and_mixed_scalar_types) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t number = {RE_VALUE_DOUBLE, {.double_value = 2.5}};
    re_value_t result = {RE_VALUE_NONE, {0}};
    ASSERT_EQ(re_facts_set(facts, text("Number"), &number), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"Double\" { when Number in [1, 2.5, true, \"2.5\"] then DoubleHit = true; }"
        "rule \"Wrong\" { when Number in [2, false, \"no\"] then WrongHit = true; }", NULL);
    ASSERT_EQ(re_facts_get(facts, text("DoubleHit"), &result), RE_STATUS_OK);
    ASSERT_EQ(result.type, RE_VALUE_BOOL);
    ASSERT_EQ(result.as.boolean, 1);
    ASSERT_EQ(re_facts_get(facts, text("WrongHit"), &result), RE_STATUS_NOT_FOUND);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(array_literal_membership_rejects_non_match_and_malformed_arrays) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_value_t value = {RE_VALUE_STRING, {.string = {"no", 2u}}};
    ASSERT_EQ(re_facts_set(facts, text("Value"), &value), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text("rule \"Out\" { when Value in [\"yes\"] then Result = 1; }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("Result"), &value), RE_STATUS_NOT_FOUND);
    ASSERT_EQ(re_program_load(NULL, text("rule \"Empty\" { when Value in [] then Result = 1; }"), NULL, &program), RE_STATUS_PARSE_ERROR);
    re_program_destroy(program);
    ASSERT_EQ(re_program_load(NULL, text("rule \"Bad\" { when Value in 1 then Result = 1; }"), NULL, &program), RE_STATUS_PARSE_ERROR);
    re_program_destroy(program);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(array_membership_uses_typed_equality_without_integer_precision_loss) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_value_t value = {RE_VALUE_INT64, {.int64_value = INT64_C(9007199254740993)}};
    re_value_t result = {RE_VALUE_NONE, {0}};
    ASSERT_EQ(re_facts_set(facts, text("Value"), &value), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text("rule \"Exact\" { when Value in [9007199254740992] then Result = 1; }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("Result"), &result), RE_STATUS_NOT_FOUND);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(array_membership_rejects_numeric_cross_type_equality) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t integer = {RE_VALUE_INT64, {.int64_value = 1}};
    re_value_t result = {RE_VALUE_NONE, {0}};
    ASSERT_EQ(re_facts_set(facts, text("Value"), &integer), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"WrongType\" { when Value in [1.0] then Result = true; }", NULL);
    ASSERT_EQ(re_facts_get(facts, text("Result"), &result), RE_STATUS_NOT_FOUND);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(structured_array_membership_uses_owned_copy) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_handle_t *tags = NULL;
    re_program_t *program = NULL;
    re_value_t tag = {RE_VALUE_STRING, {.string = {"vip", 3u}}};
    re_value_t result = {RE_VALUE_NONE, {0}};
    ASSERT_EQ(re_value_create_array(facts, &tags), RE_STATUS_OK);
    ASSERT_EQ(re_value_array_append(tags, &tag), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set_value(facts, text("Tags"), tags), RE_STATUS_OK);
    re_value_destroy(tags);
    ASSERT_EQ(re_program_load(NULL, text("rule \"StructuredIn\" { when \"vip\" in Tags then Result = 1; }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("Result"), &result), RE_STATUS_OK);
    ASSERT_EQ(result.as.int64_value, 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(array_membership_rejects_structured_non_array_and_nested_elements) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_handle_t *object = NULL;
    re_value_handle_t *array = NULL;
    re_value_handle_t *nested = NULL;
    re_program_t *program = NULL;
    ASSERT_EQ(re_value_create_object(facts, &object), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set_value(facts, text("NotArray"), object), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL,
        text("rule \"NotArray\" { when \"vip\" in NotArray then Result = 1; }"),
        NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_value_create_array(facts, &array), RE_STATUS_OK);
    ASSERT_EQ(re_value_create_array(facts, &nested), RE_STATUS_OK);
    ASSERT_EQ(re_value_array_append_value(array, nested), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set_value(facts, text("Nested"), array), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL,
        text("rule \"Nested\" { when \"vip\" in Nested then Result = 1; }"),
        NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    re_value_destroy(nested);
    re_value_destroy(array);
    re_value_destroy(object);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(array_membership_literals_reject_non_scalar_elements_and_bound_count) {
    re_program_t *program = NULL;
    char source[1024];
    char oversized[1024];
    size_t used = 0u;
    size_t oversized_used = 0u;
    size_t index;
    ASSERT_EQ(re_program_load(NULL,
        text("rule \"Bad\" { when 1 in [[1]] then Result = 1; }"), NULL, &program),
        RE_STATUS_PARSE_ERROR);
    ASSERT_TRUE(program == NULL);
    used += (size_t)snprintf(source + used, sizeof(source) - used,
                             "rule \"Limit\" { when 1 in [");
    for (index = 0u; index < 64u; ++index)
        used += (size_t)snprintf(source + used, sizeof(source) - used, "%s1",
                                 index == 0u ? "" : ",");
    used += (size_t)snprintf(source + used, sizeof(source) - used,
                             "] then Result = 1; }");
    ASSERT_TRUE(used < sizeof(source));
    ASSERT_EQ(re_program_load(NULL, text(source), NULL, &program), RE_STATUS_OK);
    re_program_destroy(program);
    program = NULL;
    oversized_used += (size_t)snprintf(oversized + oversized_used,
        sizeof(oversized) - oversized_used, "rule \"Limit\" { when 1 in [");
    for (index = 0u; index < 65u; ++index)
        oversized_used += (size_t)snprintf(oversized + oversized_used,
            sizeof(oversized) - oversized_used, "%s1", index == 0u ? "" : ",");
    oversized_used += (size_t)snprintf(oversized + oversized_used,
        sizeof(oversized) - oversized_used, "] then Result = 1; }");
    ASSERT_EQ(re_program_load(NULL, text(oversized), NULL, &program), RE_STATUS_LIMIT);
    ASSERT_TRUE(program == NULL);
}

TEST(array_membership_array_copy_failure_leaves_facts_unchanged) {
    allocator_state_t state = {0u, 0u, 0u};
    re_allocator_t allocator = {&state, test_alloc, test_realloc, test_free};
    re_facts_t *facts = re_facts_create(&allocator, NULL);
    re_value_handle_t *array = NULL;
    re_value_t member = {RE_VALUE_INT64, {.int64_value = 7}};
    re_value_t output = {RE_VALUE_NONE, {0}};
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_value_create_array(facts, &array), RE_STATUS_OK);
    ASSERT_EQ(re_value_array_append(array, &member), RE_STATUS_OK);
    state.fail_at = state.calls + 1u;
    ASSERT_EQ(re_facts_set_value(facts, text("Numbers"), array), RE_STATUS_OUT_OF_MEMORY);
    ASSERT_EQ(re_facts_get(facts, text("Numbers"), &output), RE_STATUS_NOT_FOUND);
    state.fail_at = 0u;
    re_value_destroy(array);
    re_facts_destroy(facts);
    ASSERT_EQ(state.calls, state.frees + 1u);
}

TEST(grl_string_operators_match_in_forward_ir) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t value = {RE_VALUE_STRING, {.string = {"admin@example.com", 17u}}};
    re_value_t output = {RE_VALUE_NONE, {0}};
    ASSERT_EQ(re_facts_set(facts, text("Email"), &value), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"Strings\" { when Email contains \"admin\" then Matched = true; }", NULL);
    ASSERT_EQ(re_facts_get(facts, text("Matched"), &output), RE_STATUS_OK);
    ASSERT_EQ(output.type, RE_VALUE_BOOL);
    ASSERT_EQ(output.as.boolean, 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(grl_append_action_preserves_action_order) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t output = {RE_VALUE_NONE, {0}};
    run_program(engine, facts, "rule \"Append\" { when true then Items += 1; Items += 2; }", NULL);
    ASSERT_EQ(re_facts_get_path(facts, text("Items.0"), &output), RE_STATUS_OK);
    ASSERT_EQ(output.as.int64_value, 1);
    ASSERT_EQ(re_facts_get_path(facts, text("Items.1"), &output), RE_STATUS_OK);
    ASSERT_EQ(output.as.int64_value, 2);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(grl_arithmetic_precedence_is_observable) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t score = {RE_VALUE_INT64, {.int64_value = 3}};
    re_value_t output = {RE_VALUE_NONE, {0}};
    ASSERT_EQ(re_facts_set(facts, text("Score"), &score), RE_STATUS_OK);
    run_program(engine, facts, "rule \"Arithmetic\" { when Score + 2 * 4 == 11 then Result = Score + 2 * 4; }", NULL);
    ASSERT_EQ(re_facts_get(facts, text("Result"), &output), RE_STATUS_OK);
    ASSERT_EQ(output.type, RE_VALUE_INT64);
    ASSERT_EQ(output.as.int64_value, 11);
    re_facts_destroy(facts); re_engine_destroy(engine);
}

TEST(grl_arithmetic_supports_subtraction_and_division) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t output = {RE_VALUE_NONE, {0}};
    run_program(engine, facts,
        "rule \"Arithmetic\" { when (20 - 8) / 3 == 4 then Result = (20 - 8) / 3; }", NULL);
    ASSERT_EQ(re_facts_get(facts, text("Result"), &output), RE_STATUS_OK);
    ASSERT_EQ(output.type, RE_VALUE_INT64);
    ASSERT_EQ(output.as.int64_value, 4);
    re_facts_destroy(facts); re_engine_destroy(engine);
}

TEST(grl_arithmetic_supports_negative_integer_multiplication) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t output = {RE_VALUE_NONE, {0}};
    run_program(engine, facts,
        "rule \"Arithmetic\" { when 2 * -3 == -6 then Result = 2 * -3; }", NULL);
    ASSERT_EQ(re_facts_get(facts, text("Result"), &output), RE_STATUS_OK);
    ASSERT_EQ(output.type, RE_VALUE_INT64);
    ASSERT_EQ(output.as.int64_value, -6);
    re_facts_destroy(facts); re_engine_destroy(engine);
}

TEST(grl_arithmetic_mixes_int_and_double_as_double) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t output = {RE_VALUE_NONE, {0}};
    run_program(engine, facts,
        "rule \"Arithmetic\" { when 5 / 2.0 == 2.5 then Result = 5 / 2.0; }", NULL);
    ASSERT_EQ(re_facts_get(facts, text("Result"), &output), RE_STATUS_OK);
    ASSERT_EQ(output.type, RE_VALUE_DOUBLE);
    ASSERT_TRUE(output.as.double_value == 2.5);
    re_facts_destroy(facts); re_engine_destroy(engine);
}

TEST(grl_arithmetic_rejects_malformed_and_zero_division) {
    re_program_t *program = NULL;
    ASSERT_EQ(re_program_load(NULL, text("rule \"Bad\" { when 1 + * 2 == 3 then X = 1; }"), NULL, &program), RE_STATUS_PARSE_ERROR);
    ASSERT_TRUE(program == NULL);
    ASSERT_EQ(re_program_load(NULL, text("rule \"Bad\" { when 1 / 0 == 0 then X = 1; }"), NULL, &program), RE_STATUS_ERROR);
    ASSERT_TRUE(program == NULL);
}

TEST(grl_in_supports_array_literals_and_structured_arrays) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t role = {RE_VALUE_STRING, {.string = {"admin", 5u}}};
    re_value_t output = {RE_VALUE_NONE, {0}};
    re_value_handle_t *tags = NULL;
    ASSERT_EQ(re_facts_set(facts, text("Role"), &role), RE_STATUS_OK);
    run_program(engine, facts, "rule \"Membership\" { when Role in [\"admin\", \"user\"] then Result = true; }", NULL);
    ASSERT_EQ(re_facts_get(facts, text("Result"), &output), RE_STATUS_OK);
    ASSERT_EQ(output.as.boolean, 1);
    ASSERT_EQ(re_value_create_array(facts, &tags), RE_STATUS_OK);
    ASSERT_EQ(re_value_array_append(tags, &role), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set_value(facts, text("Tags"), tags), RE_STATUS_OK);
    run_program(engine, facts, "rule \"StructuredMembership\" { when \"admin\" in Tags then Structured = true; }", NULL);
    ASSERT_EQ(re_facts_get(facts, text("Structured"), &output), RE_STATUS_OK);
    ASSERT_EQ(output.as.boolean, 1);
    re_value_destroy(tags); re_facts_destroy(facts); re_engine_destroy(engine);
}

TEST(grl_matches_uses_wildcards) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t email = {RE_VALUE_STRING, {.string = {"admin@example.com", 17u}}};
    re_value_t output = {RE_VALUE_NONE, {0}};
    ASSERT_EQ(re_facts_set(facts, text("Email"), &email), RE_STATUS_OK);
    run_program(engine, facts, "rule \"Pattern\" { when Email matches \"admin*@*.com\" then Result = true; }", NULL);
    ASSERT_EQ(re_facts_get(facts, text("Result"), &output), RE_STATUS_OK);
    ASSERT_EQ(output.as.boolean, 1);
    re_facts_destroy(facts); re_engine_destroy(engine);
}

TEST(grl_matches_supports_question_mark_and_empty_strings) {
    re_value_t value = {RE_VALUE_STRING, {.string = {"ab", 2u}}};
    re_value_t question = {RE_VALUE_STRING, {.string = {"a?", 2u}}};
    re_value_t empty = {RE_VALUE_STRING, {.string = {"", 0u}}};
    re_value_t star = {RE_VALUE_STRING, {.string = {"*", 1u}}};
    ASSERT_TRUE(re_value_compare(&value, &question, RE_COMPARE_MATCHES));
    ASSERT_TRUE(!re_value_compare(&value, &empty, RE_COMPARE_MATCHES));
    ASSERT_TRUE(re_value_compare(&empty, &star, RE_COMPARE_MATCHES));
}

TEST(grl_matches_rejects_nonmatching_wildcard_patterns) {
    re_value_t value = {RE_VALUE_STRING, {.string = {"admin@example.com", 17u}}};
    re_value_t pattern = {RE_VALUE_STRING, {.string = {"user?*@*.net", 12u}}};
    ASSERT_TRUE(!re_value_compare(&value, &pattern, RE_COMPARE_MATCHES));
}

TEST(grl_matches_is_anchored_and_supports_zero_or_more_bytes) {
    re_value_t value = {RE_VALUE_STRING, {.string = {"admin@example.com", 17u}}};
    re_value_t prefix = {RE_VALUE_STRING, {.string = {"admin", 5u}}};
    re_value_t suffix = {RE_VALUE_STRING, {.string = {"*.com", 5u}}};
    re_value_t inner = {RE_VALUE_STRING, {.string = {"example", 7u}}};
    re_value_t any = {RE_VALUE_STRING, {.string = {"*", 1u}}};
    ASSERT_FALSE(re_value_compare(&value, &prefix, RE_COMPARE_MATCHES));
    ASSERT_TRUE(re_value_compare(&value, &suffix, RE_COMPARE_MATCHES));
    ASSERT_TRUE(re_value_compare(&value, &inner, RE_COMPARE_MATCHES) == 0);
    ASSERT_TRUE(re_value_compare(&value, &any, RE_COMPARE_MATCHES));
}

TEST(grl_matches_question_mark_consumes_one_byte) {
    re_value_t two_bytes = {RE_VALUE_STRING, {.string = {"ab", 2u}}};
    re_value_t one_byte = {RE_VALUE_STRING, {.string = {"a", 1u}}};
    re_value_t one_question = {RE_VALUE_STRING, {.string = {"?", 1u}}};
    re_value_t two_questions = {RE_VALUE_STRING, {.string = {"??", 2u}}};
    ASSERT_TRUE(re_value_compare(&two_bytes, &two_questions, RE_COMPARE_MATCHES));
    ASSERT_FALSE(re_value_compare(&two_bytes, &one_question, RE_COMPARE_MATCHES));
    ASSERT_TRUE(re_value_compare(&one_byte, &one_question, RE_COMPARE_MATCHES));
}

TEST(grl_matches_rejects_oversized_and_overflowing_patterns_without_dereference) {
    re_value_t value = {RE_VALUE_STRING, {.string = {"x", 1u}}};
    re_value_t oversized_pattern = {RE_VALUE_STRING, {.string = {(const char *)1, SIZE_MAX}}};
    re_value_t overflowing_pattern = {RE_VALUE_STRING, {.string = {(const char *)1, SIZE_MAX - 1u}}};
    re_value_t empty = {RE_VALUE_STRING, {.string = {"", 0u}}};
    ASSERT_FALSE(re_value_compare(&value, &oversized_pattern, RE_COMPARE_MATCHES));
    ASSERT_FALSE(re_value_compare(&value, &overflowing_pattern, RE_COMPARE_MATCHES));
    ASSERT_TRUE(re_value_compare(&empty, &empty, RE_COMPARE_MATCHES));
}

TEST(malformed_action_requires_semicolon) {
    re_program_t *program = NULL;
    ASSERT_EQ(re_program_load(NULL, text("rule \"Bad\" { when true then Result = 1 }"), NULL, &program), RE_STATUS_PARSE_ERROR);
    ASSERT_TRUE(program == NULL);
}

TEST(malformed_action_rejects_trailing_tokens_transactionally) {
    re_program_t *program = NULL;
    ASSERT_EQ(re_program_load(NULL, text("rule \"Bad\" { when true then Result = 1; garbage }"), NULL, &program), RE_STATUS_PARSE_ERROR);
    ASSERT_TRUE(program == NULL);
    ASSERT_EQ(re_program_load(NULL, text("rule \"Bad\" { when true then Result = 1; Result = 2 }"), NULL, &program), RE_STATUS_PARSE_ERROR);
    ASSERT_TRUE(program == NULL);
}

typedef struct provider_test_state_t {
    size_t calls;
    re_value_t value;
    uint64_t ttl;
    re_status_t failure;
} provider_test_state_t;

static re_status_t provider_get(re_state_provider_t *provider, re_string_t key,
                                re_value_t *out, void *context) {
    provider_test_state_t *state = context;
    (void)provider; (void)key; state->calls++;
    if (state->failure != RE_STATUS_OK) return state->failure;
    *out = state->value; return RE_STATUS_OK;
}
static re_status_t provider_put(re_state_provider_t *provider, re_string_t key,
                                const re_value_t *value, uint64_t ttl, void *context) {
    provider_test_state_t *state = context;
    (void)provider; (void)key; state->calls++;
    if (state->failure != RE_STATUS_OK) return state->failure;
    state->value = *value; state->ttl = ttl; return RE_STATUS_OK;
}
static re_status_t provider_delete(re_state_provider_t *provider, re_string_t key, void *context) {
    provider_test_state_t *state = context;
    (void)provider; (void)key; state->calls++;
    return state->failure;
}
static re_status_t provider_ttl(re_state_provider_t *provider, re_string_t key,
                                uint64_t *out, void *context) {
    provider_test_state_t *state = context;
    (void)provider; (void)key; state->calls++;
    if (state->failure != RE_STATUS_OK) return state->failure;
    *out = state->ttl; return RE_STATUS_OK;
}

TEST(sliding_window_records_eviction_lateness_limits_and_snapshot_restore) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_window_t *window = NULL;
    re_stream_window_t *restored = NULL;
    re_stream_window_options_t options = {sizeof(options), RE_STREAM_WINDOW_ABI_VERSION,
        RE_STREAM_WINDOW_SLIDING, RE_LATE_EVENT_DROP, 100u, 3u, 30u, 10u};
    re_value_t value = {RE_VALUE_STRING, { .string = {"x", 1u} }};
    re_snapshot_t first = {sizeof(first), 0u, NULL, 0u, NULL, NULL};
    re_snapshot_t second = {sizeof(second), 0u, NULL, 0u, NULL, NULL};
    ASSERT_EQ(re_stream_window_create_v1(engine, &options, &window), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 100u, text("a"), &value), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 200u, text("b"), &value), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 190u, text("late"), &value), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 189u, text("drop"), &value), RE_STATUS_NOT_FOUND);
    ASSERT_EQ(re_stream_window_record_v1(window, 300u, text("c"), &value), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_snapshot(window, &first), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_create_v1(engine, &options, &restored), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_restore(restored, &first), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_snapshot(restored, &second), RE_STATUS_OK);
    ASSERT_EQ(first.size, second.size);
    ASSERT_TRUE(memcmp(first.data, second.data, first.size) == 0);
    if (first.release) first.release(first.release_context, first.data, first.size);
    if (second.release) second.release(second.release_context, second.data, second.size);
    re_stream_window_destroy(restored); re_stream_window_destroy(window); re_engine_destroy(engine);
}

static uint64_t window_snapshot_count(const re_snapshot_t *snapshot) {
    uint64_t count = 0u;
    if (snapshot->data == NULL || snapshot->size < 16u) return UINT64_MAX;
    memcpy(&count, snapshot->data + 8u, sizeof(count));
    return count;
}

TEST(tumbling_window_uses_half_open_event_time_buckets) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_window_t *window = NULL;
    re_snapshot_t snapshot = {sizeof(snapshot), 0u, NULL, 0u, NULL, NULL};
    re_stream_window_options_t options = {sizeof(options), RE_STREAM_WINDOW_ABI_VERSION,
        RE_STREAM_WINDOW_TUMBLING, RE_LATE_EVENT_DROP, 100u, 8u, 1024u, 0u};
    re_value_t value = {RE_VALUE_INT64, {.int64_value = 1}};
    ASSERT_EQ(re_stream_window_create_v1(engine, &options, &window), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 99u, text("before"), &value), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 100u, text("boundary"), &value), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_snapshot(window, &snapshot), RE_STATUS_OK);
    ASSERT_EQ(window_snapshot_count(&snapshot), 1u);
    snapshot.release(snapshot.release_context, snapshot.data, snapshot.size);
    re_stream_window_destroy(window);
    re_engine_destroy(engine);
}

TEST(session_window_creates_extends_and_times_out_deterministically) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_window_t *window = NULL;
    re_snapshot_t snapshot = {sizeof(snapshot), 0u, NULL, 0u, NULL, NULL};
    re_stream_window_options_t options = {sizeof(options), RE_STREAM_WINDOW_ABI_VERSION,
        RE_STREAM_WINDOW_SESSION, RE_LATE_EVENT_DROP, 50u, 8u, 1024u, 0u};
    re_value_t value = {RE_VALUE_BOOL, {.boolean = 1}};
    ASSERT_EQ(re_stream_window_create_v1(engine, &options, &window), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 100u, text("a"), &value), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 150u, text("extend"), &value), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 201u, text("timeout"), &value), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_snapshot(window, &snapshot), RE_STATUS_OK);
    ASSERT_EQ(window_snapshot_count(&snapshot), 1u);
    snapshot.release(snapshot.release_context, snapshot.data, snapshot.size);
    re_stream_window_destroy(window);
    re_engine_destroy(engine);
}

TEST(tumbling_window_applies_late_policy_limits_and_empty_snapshot) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_window_t *window = NULL;
    re_snapshot_t snapshot = {sizeof(snapshot), 0u, NULL, 0u, NULL, NULL};
    re_stream_window_options_t options = {sizeof(options), RE_STREAM_WINDOW_ABI_VERSION,
        RE_STREAM_WINDOW_TUMBLING, RE_LATE_EVENT_ERROR, 100u, 2u, 32u, 10u};
    re_value_t value = {RE_VALUE_STRING, {.string = {"payload", 7u}}};
    ASSERT_EQ(re_stream_window_create_v1(engine, &options, &window), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 100u, text("first"), &value), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 200u, text("second"), &value), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 180u, text("late"), &value), RE_STATUS_ERROR);
    ASSERT_EQ(re_stream_window_snapshot(window, &snapshot), RE_STATUS_OK);
    ASSERT_EQ(window_snapshot_count(&snapshot), 1u);
    snapshot.release(snapshot.release_context, snapshot.data, snapshot.size);
    re_stream_window_destroy(window);
    ASSERT_EQ(re_stream_window_create_v1(engine, &options, &window), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_snapshot(window, &snapshot), RE_STATUS_OK);
    ASSERT_EQ(window_snapshot_count(&snapshot), 0u);
    snapshot.release(snapshot.release_context, snapshot.data, snapshot.size);
    re_stream_window_destroy(window);
    re_engine_destroy(engine);
}

TEST(callback_state_provider_put_get_delete_ttl_and_errors_propagate) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_state_provider_t *provider = NULL;
    provider_test_state_t state = {0u, {RE_VALUE_NONE, {0}}, 0u, RE_STATUS_OK};
    re_state_provider_options_t options = {sizeof(options), RE_STATE_PROVIDER_ABI_VERSION,
        RE_STATE_PROVIDER_CALLBACK, 0u, 100u};
    re_state_provider_descriptor_t descriptor = {sizeof(descriptor), RE_STATE_PROVIDER_ABI_VERSION,
        provider_get, NULL, NULL, &state, provider_put, provider_delete, provider_ttl};
    re_value_t value = {RE_VALUE_INT64, {.int64_value = 7}};
    re_value_t output = {RE_VALUE_NONE, {0}};
    uint64_t ttl = 0u;
    ASSERT_EQ(re_engine_set_state_provider_v1(engine, &options, &descriptor, &provider), RE_STATUS_OK);
    ASSERT_EQ(re_state_provider_put(provider, text("k"), &value, 50u), RE_STATUS_OK);
    ASSERT_EQ(re_state_provider_get(provider, text("k"), &output), RE_STATUS_OK);
    ASSERT_EQ(output.as.int64_value, 7);
    ASSERT_EQ(re_state_provider_ttl(provider, text("k"), &ttl), RE_STATUS_OK);
    ASSERT_EQ(ttl, 50u);
    ASSERT_EQ(re_state_provider_delete(provider, text("k")), RE_STATUS_OK);
    state.failure = RE_STATUS_ERROR;
    ASSERT_EQ(re_state_provider_get(provider, text("k"), &output), RE_STATUS_ERROR);
    re_state_provider_destroy(provider); re_engine_destroy(engine);
}

static uint64_t provider_test_clock(void *context) { return *(uint64_t *)context; }

TEST(memory_state_provider_is_bounded_ttl_atomic_and_snapshot_deterministic) {
    uint64_t now = 1000u;
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_state_provider_t *provider = NULL;
    re_state_provider_t *restored = NULL;
    re_memory_provider_options_t options = {sizeof(options), 1u, 2u, 8u, 32u,
        provider_test_clock, &now};
    re_snapshot_t first = {sizeof(first), 0u, NULL, 0u, NULL, NULL};
    re_snapshot_t second = {sizeof(second), 0u, NULL, 0u, NULL, NULL};
    re_value_t one = {RE_VALUE_STRING, {.string = {"one", 3u}}};
    re_value_t two = {RE_VALUE_STRING, {.string = {"two", 3u}}};
    re_value_t output = {RE_VALUE_NONE, {0}};
    uint64_t ttl = 0u;
    ASSERT_EQ(re_state_provider_create_memory(engine, &options, &provider), RE_STATUS_OK);
    ASSERT_EQ(re_state_provider_put(provider, text("a"), &one, 50u), RE_STATUS_OK);
    ASSERT_EQ(re_state_provider_update(provider, text("a"), &two, 50u), RE_STATUS_OK);
    ASSERT_EQ(re_state_provider_get(provider, text("a"), &output), RE_STATUS_OK);
    ASSERT_TRUE(memcmp(output.as.string.data, "two", 3u) == 0);
    ASSERT_EQ(re_state_provider_ttl(provider, text("a"), &ttl), RE_STATUS_OK);
    ASSERT_EQ(ttl, 50u);
    ASSERT_EQ(re_state_provider_snapshot(provider, &first), RE_STATUS_OK);
    ASSERT_EQ(re_state_provider_create_memory(engine, &options, &restored), RE_STATUS_OK);
    ASSERT_EQ(re_state_provider_restore(restored, &first), RE_STATUS_OK);
    ASSERT_EQ(re_state_provider_snapshot(restored, &second), RE_STATUS_OK);
    ASSERT_EQ(first.size, second.size);
    ASSERT_TRUE(memcmp(first.data, second.data, first.size) == 0);
    now += 50u;
    ASSERT_EQ(re_state_provider_get(provider, text("a"), &output), RE_STATUS_NOT_FOUND);
    ASSERT_EQ(re_state_provider_ttl(provider, text("a"), &ttl), RE_STATUS_NOT_FOUND);
    first.release(first.release_context, first.data, first.size);
    second.release(second.release_context, second.data, second.size);
    re_state_provider_destroy(restored); re_state_provider_destroy(provider);
    re_engine_destroy(engine);
}

TEST(memory_state_provider_rejects_bounds_corruption_and_redis) {
    uint64_t now = 0u;
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_state_provider_t *provider = NULL;
    re_memory_provider_options_t options = {sizeof(options), 1u, 1u, 2u, 2u,
        provider_test_clock, &now};
    re_value_t value = {RE_VALUE_STRING, {.string = {"ok", 2u}}};
    re_value_t too_long = {RE_VALUE_STRING, {.string = {"bad", 3u}}};
    re_snapshot_t bad = {sizeof(bad), 99u, (const uint8_t *)"x", 1u, NULL, NULL};
    re_state_provider_options_t redis = {sizeof(redis), 1u, RE_STATE_PROVIDER_REDIS, 0u, 0u};
    re_state_provider_descriptor_t descriptor = {sizeof(descriptor), 1u, provider_get,
        NULL, NULL, NULL, NULL, NULL, NULL};
    ASSERT_EQ(re_state_provider_create_memory(engine, &options, &provider), RE_STATUS_OK);
    ASSERT_EQ(re_state_provider_put(provider, text("a"), &value, 0u), RE_STATUS_OK);
    ASSERT_EQ(re_state_provider_put(provider, text("a"), &too_long, 0u), RE_STATUS_LIMIT);
    ASSERT_EQ(re_state_provider_put(provider, text("bb"), &value, 0u), RE_STATUS_LIMIT);
    ASSERT_EQ(re_state_provider_restore(provider, &bad), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_engine_set_state_provider_v1(engine, &redis, &descriptor, &provider), RE_STATUS_NOT_SUPPORTED);
    re_state_provider_destroy(provider); re_engine_destroy(engine);
}

typedef struct order_state_t {
    const char *names[4];
    size_t count;
} order_state_t;

static re_status_t record_order(re_engine_t *engine, re_facts_t *facts,
                                const re_rule_event_t *event, void *context) {
    order_state_t *state = context;
    (void)engine;
    (void)facts;
    if (state->count < 4u) state->names[state->count] = event->rule_name.data;
    state->count++;
    return RE_STATUS_OK;
}

TEST(salience_orders_matching_activations_deterministically) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    order_state_t state = {{NULL, NULL, NULL, NULL}, 0u};
    re_callbacks_t callbacks = {record_order, &state};
    {
        re_program_t *program = NULL;
        ASSERT_EQ(re_program_load(NULL, text(
            "rule \"Low\" { salience 1; when true then Low = 1; } "
            "rule \"High\" { salience 10; when true then High = 1; }"), NULL, &program), RE_STATUS_OK);
        ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    }
    ASSERT_EQ(re_engine_run(engine, facts, NULL, &callbacks), RE_STATUS_OK);
    ASSERT_EQ(state.count, 2u);
    ASSERT_TRUE(memcmp(state.names[0], "High", 4u) == 0);
    ASSERT_TRUE(memcmp(state.names[1], "Low", 3u) == 0);
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

TEST(stream_window_filters_and_aggregates_bounded_contents) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_window_t *window = NULL;
    re_stream_filter_options_t filter = {sizeof(filter), RE_STREAM_WINDOW_ABI_VERSION,
        text("purchase"), (re_string_t){NULL, 0u}};
    re_stream_aggregate_result_t result = {sizeof(result), 0u, 0.0, 0.0};
    re_value_t first = {RE_VALUE_DOUBLE, {.double_value = 2.5}};
    re_value_t second = {RE_VALUE_DOUBLE, {.double_value = 7.5}};
    re_value_t other = {RE_VALUE_DOUBLE, {.double_value = 100.0}};
    re_stream_window_options_t options = {sizeof(options), RE_STREAM_WINDOW_ABI_VERSION,
        RE_STREAM_WINDOW_SLIDING, RE_LATE_EVENT_DROP, 1000u, 8u, 1024u, 0u};
    ASSERT_EQ(re_stream_window_create_v1(engine, &options, &window), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 10u, text("purchase"), &first), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 20u, text("purchase"), &second), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 30u, text("refund"), &other), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_aggregate_v1(window, &filter, RE_STREAM_AGGREGATE_COUNT, &result), RE_STATUS_OK);
    ASSERT_EQ(result.count, 2u);
    ASSERT_EQ(re_stream_window_aggregate_v1(window, &filter, RE_STREAM_AGGREGATE_SUM, &result), RE_STATUS_OK);
    ASSERT_FLOAT_EQ(result.sum, 10.0, 0.0001);
    ASSERT_EQ(re_stream_window_aggregate_v1(window, &filter, RE_STREAM_AGGREGATE_AVERAGE, &result), RE_STATUS_OK);
    ASSERT_FLOAT_EQ(result.average, 5.0, 0.0001);
    re_stream_window_destroy(window); re_engine_destroy(engine);
}

TEST(stream_window_correlates_matching_types_keys_and_timeout_deterministically) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_window_t *window = NULL;
    re_stream_correlation_options_t correlation = {sizeof(correlation), RE_STREAM_WINDOW_ABI_VERSION,
        text("login"), text("purchase"), text("acct-7"), 50u};
    re_value_t key = {RE_VALUE_STRING, {.string = {"acct-7", 6u}}};
    re_value_t other = {RE_VALUE_STRING, {.string = {"acct-8", 6u}}};
    uint64_t matches = 0u;
    re_stream_window_options_t options = {sizeof(options), RE_STREAM_WINDOW_ABI_VERSION,
        RE_STREAM_WINDOW_SLIDING, RE_LATE_EVENT_DROP, 1000u, 8u, 1024u, 0u};
    ASSERT_EQ(re_stream_window_create_v1(engine, &options, &window), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 100u, text("login"), &key), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 130u, text("purchase"), &key), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 140u, text("purchase"), &other), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 200u, text("purchase"), &key), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_correlate_v1(window, &correlation, &matches), RE_STATUS_OK);
    ASSERT_EQ(matches, 1u);
    re_stream_window_destroy(window); re_engine_destroy(engine);
}

TEST(streaming_boundaries_overflow_and_restore_are_atomic) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_window_t *window = NULL;
    re_stream_window_options_t options = {sizeof(options), RE_STREAM_WINDOW_ABI_VERSION,
        RE_STREAM_WINDOW_SESSION, RE_LATE_EVENT_ACCEPT, 50u, 8u, 1024u, 50u};
    re_value_t value = {RE_VALUE_INT64, {.int64_value = 1}};
    re_snapshot_t before = {sizeof(before), 0u, NULL, 0u, NULL, NULL};
    re_snapshot_t after = {sizeof(after), 0u, NULL, 0u, NULL, NULL};
    uint8_t corrupt[17] = {0};
    re_snapshot_t bad = {sizeof(bad), 1u, corrupt, sizeof(corrupt), NULL, NULL};
    ASSERT_EQ(re_stream_window_create_v1(engine, &options, &window), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 100u, text("a"), &value), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 150u, text("boundary"), &value), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 120u, text("late"), &value), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 180u, text("still-session"), &value), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, UINT64_MAX, text("overflow"), &value), RE_STATUS_LIMIT);
    ASSERT_EQ(re_stream_window_snapshot(window, &before), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_restore(window, &bad), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_stream_window_snapshot(window, &after), RE_STATUS_OK);
    ASSERT_EQ(before.size, after.size);
    ASSERT_TRUE(memcmp(before.data, after.data, before.size) == 0);
    before.release(before.release_context, before.data, before.size);
    after.release(after.release_context, after.data, after.size);
    re_stream_window_destroy(window); re_engine_destroy(engine);
}

TEST(memory_provider_ttl_overflow_cleanup_and_restore_atomicity) {
    uint64_t now = UINT64_MAX - 5u;
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_state_provider_t *provider = NULL;
    re_memory_provider_options_t options = {sizeof(options), 1u, 1u, 8u, 32u,
        provider_test_clock, &now};
    re_value_t value = {RE_VALUE_INT64, {.int64_value = 7}};
    re_value_t output = {RE_VALUE_NONE, {0}};
    uint8_t corrupt[17] = {0};
    re_snapshot_t bad = {sizeof(bad), 1u, corrupt, sizeof(corrupt), NULL, NULL};
    ASSERT_EQ(re_state_provider_create_memory(engine, &options, &provider), RE_STATUS_OK);
    ASSERT_EQ(re_state_provider_put(provider, text("a"), &value, 10u), RE_STATUS_LIMIT);
    ASSERT_EQ(re_state_provider_put(provider, text("a"), &value, 0u), RE_STATUS_OK);
    ASSERT_EQ(re_state_provider_delete(provider, text("a")), RE_STATUS_OK);
    ASSERT_EQ(re_state_provider_put(provider, text("b"), &value, 0u), RE_STATUS_OK);
    ASSERT_EQ(re_state_provider_restore(provider, &bad), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_state_provider_get(provider, text("b"), &output), RE_STATUS_OK);
    ASSERT_EQ(output.as.int64_value, 7);
    re_state_provider_destroy(provider); re_engine_destroy(engine);
}

TEST(redis_provider_failure_does_not_create_or_fallback_to_memory) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_state_provider_t *provider = NULL;
    re_state_provider_options_t options = {sizeof(options), RE_STATE_PROVIDER_ABI_VERSION,
        RE_STATE_PROVIDER_REDIS, 0u, 100u};
    re_state_provider_descriptor_t descriptor = {sizeof(descriptor), RE_STATE_PROVIDER_ABI_VERSION,
        provider_get, NULL, NULL, NULL, NULL, NULL, NULL};
    ASSERT_EQ(re_engine_set_state_provider_v1(engine, &options, &descriptor, &provider),
              RE_STATUS_NOT_SUPPORTED);
    ASSERT_TRUE(provider == NULL);
    re_engine_destroy(engine);
}

TEST(streaming_and_state_capabilities_match_tested_extensions) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_capabilities_v2_t capabilities = 0u;
    re_extension_info_t info = {sizeof(info), 0u, 0u, 0u, 0u, 0u, 0u};
    ASSERT_EQ(re_engine_capabilities_v2(engine, RE_ABI_VERSION_MAJOR, &capabilities), RE_STATUS_OK);
    ASSERT_TRUE((capabilities & RE_CAP2_STREAMING_WINDOWS) != 0u);
    ASSERT_TRUE((capabilities & RE_CAP2_STATE_PROVIDER) != 0u);
    ASSERT_TRUE((capabilities & RE_CAP2_AGENDA_RETE) == 0u);
    ASSERT_EQ(re_engine_extension_info(engine, RE_EXTENSION_STREAMING_WINDOWS, 1u, &info), RE_STATUS_OK);
    ASSERT_EQ(info.capability_bit, RE_CAP2_STREAMING_WINDOWS);
    info.struct_size = sizeof(info);
    ASSERT_EQ(re_engine_extension_info(engine, RE_EXTENSION_STATE_PROVIDER, 1u, &info), RE_STATUS_OK);
    ASSERT_EQ(info.capability_bit, RE_CAP2_STATE_PROVIDER);
    re_engine_destroy(engine);
}

TEST(private_modules_control_qualified_rule_visibility) {
    re_program_t *program = NULL;
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_query_options_t options = {sizeof(options), 4u, 1u, 0u, 0u};
    re_query_t *query = NULL;
    ASSERT_EQ(re_program_load(NULL, text(
        "defmodule Shared { export: all; } "
        "defmodule Consumer { import: Shared; } "
        "rule \"Shared::Visible\" { when true then Visible = 1; } "
        "rule \"Shared::Hidden\" { when true then Hidden = 1; }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_program_set_module_focus(program, text("Consumer")), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    { re_value_t value = {RE_VALUE_NONE, {0}}; ASSERT_EQ(re_facts_get(facts, text("Visible"), &value), RE_STATUS_OK); ASSERT_EQ(value.as.int64_value, 1); }
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("Shared::Visible"), &options, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    re_query_destroy(query);
    re_engine_destroy(engine);
    re_facts_destroy(facts);
}

TEST(private_utc_rule_bounds_have_exact_boundaries) {
    const char *source = "rule \"Window\" { date-effective \"2025-01-01T00:00:00Z\"; date-expires \"2025-02-01T00:00:00Z\"; when true then X = 1; }";
    const int64_t clocks[] = {1735689599, 1735689600, 1738367999, 1738368000};
    const int expected[] = {0, 1, 1, 0};
    size_t i;
    for (i = 0u; i < 4u; ++i) {
        re_program_t *program = NULL;
        re_engine_t *engine = re_engine_create(NULL, NULL);
        re_facts_t *facts = re_facts_create(NULL, NULL);
        re_value_t output = {RE_VALUE_NONE, {0}};
        ASSERT_EQ(re_program_load(NULL, text(source), NULL, &program), RE_STATUS_OK);
        ASSERT_EQ(re_program_set_clock(program, clocks[i]), RE_STATUS_OK);
        ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
        ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
        ASSERT_EQ(re_facts_get(facts, text("X"), &output), expected[i] ? RE_STATUS_OK : RE_STATUS_NOT_FOUND);
        re_facts_destroy(facts);
        re_engine_destroy(engine);
    }
}

TEST(private_utc_rule_bounds_reject_malformed_dates) {
    re_program_t *program = NULL;
    ASSERT_EQ(re_program_load(NULL, text("rule \"Bad\" { date-effective \"2025-99-99T00:00:00Z\"; when true then X = 1; }"), NULL, &program), RE_STATUS_PARSE_ERROR);
    ASSERT_TRUE(program == NULL);
    ASSERT_EQ(re_program_load(NULL, text("rule \"Bad\" { date-expires \"2025-01-01\"; when true then X = 1; }"), NULL, &program), RE_STATUS_PARSE_ERROR);
    ASSERT_TRUE(program == NULL);
}

TEST(private_modules_reject_private_imports_and_unknown_imports) {
    re_program_t *program = NULL;
    ASSERT_EQ(re_program_load(NULL, text(
        "defmodule Shared { export: none; } defmodule Consumer { import: Shared; } "
        "rule \"Shared::Private\" { when true then X = 1; }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_program_set_module_focus(program, text("Consumer")), RE_STATUS_OK);
    re_program_destroy(program);
    ASSERT_EQ(re_program_load(NULL, text(
        "defmodule Consumer { import: Missing; } rule \"Consumer::R\" { when true then X = 1; }"), NULL, &program), RE_STATUS_PARSE_ERROR);
    ASSERT_TRUE(program == NULL);
}

TEST(agenda_group_focus_selects_only_focused_group) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    order_state_t state = {{NULL, NULL, NULL, NULL}, 0u};
    re_callbacks_t callbacks = {record_order, &state};
    ASSERT_EQ(re_program_load(NULL, text(
        "rule \"A\" { agenda-group \"A\"; when true then A = 1; } "
        "rule \"B\" { agenda-group \"B\"; when true then B = 1; }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_program_set_agenda_focus(program, text("B")), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, &callbacks), RE_STATUS_OK);
    ASSERT_EQ(state.count, 1u);
    ASSERT_TRUE(memcmp(state.names[0], "B", 1u) == 0);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(activation_group_fires_one_activation) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    order_state_t state = {{NULL, NULL, NULL, NULL}, 0u};
    re_callbacks_t callbacks = {record_order, &state};
    ASSERT_EQ(re_program_load(NULL, text(
        "rule \"First\" { activation-group \"one\"; salience 2; when true then A = 1; } "
        "rule \"Second\" { activation-group \"one\"; salience 1; when true then B = 1; }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, &callbacks), RE_STATUS_OK);
    ASSERT_EQ(state.count, 1u);
    ASSERT_TRUE(memcmp(state.names[0], "First", 5u) == 0);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(agenda_group_defaults_to_main_and_activation_groups_are_independent) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    order_state_t state = {{NULL, NULL, NULL, NULL}, 0u};
    re_callbacks_t callbacks = {record_order, &state};
    ASSERT_EQ(re_program_load(NULL, text(
        "rule \"Main\" { when true then Main = 1; } "
        "rule \"A1\" { agenda-group \"A\"; activation-group \"a\"; when true then A1 = 1; } "
        "rule \"A2\" { agenda-group \"A\"; activation-group \"a\"; when true then A2 = 1; } "
        "rule \"B1\" { agenda-group \"B\"; activation-group \"b\"; when true then B1 = 1; } "
        "rule \"B2\" { agenda-group \"B\"; activation-group \"b\"; when true then B2 = 1; }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, &callbacks), RE_STATUS_OK);
    ASSERT_EQ(state.count, 1u);
    ASSERT_TRUE(memcmp(state.names[0], "Main", 4u) == 0);
    state.count = 0u;
    ASSERT_EQ(re_program_set_agenda_focus(program, text("A")), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, &callbacks), RE_STATUS_OK);
    ASSERT_EQ(state.count, 1u);
    ASSERT_TRUE(memcmp(state.names[0], "A1", 2u) == 0);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(no_loop_and_lock_on_active_are_enforced) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    order_state_t state = {{NULL, NULL, NULL, NULL}, 0u};
    re_callbacks_t callbacks = {record_order, &state};
    re_value_t zero = {RE_VALUE_INT64, {.int64_value = 0}};
    ASSERT_EQ(re_facts_set(facts, text("X"), &zero), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text(
        "rule \"NoLoop\" { no-loop true; when X == 0 then X = 1; } "
        "rule \"Locked\" { agenda-group \"A\"; lock-on-active true; when X == 1 then Y = 1; }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, &callbacks), RE_STATUS_OK);
    ASSERT_EQ(state.count, 1u);
    ASSERT_EQ(re_program_set_agenda_focus(program, text("A")), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, &callbacks), RE_STATUS_OK);
    ASSERT_EQ(state.count, 2u);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
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

    re_limits_t limits = {0, 0, 0, 0, 1, 0};
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

typedef struct parallel_trace_t {
    char names[8][16];
    size_t count;
} parallel_trace_t;

static re_status_t record_parallel_trace(re_engine_t *engine, re_facts_t *facts,
                                         const re_rule_event_t *event, void *context) {
    parallel_trace_t *trace = context;
    (void)engine; (void)facts;
    if (trace->count >= 8u || event->rule_name.size >= sizeof(trace->names[0])) return RE_STATUS_LIMIT;
    memcpy(trace->names[trace->count], event->rule_name.data, event->rule_name.size);
    trace->names[trace->count][event->rule_name.size] = '\0';
    ++trace->count;
    return RE_STATUS_OK;
}

TEST(optional_parallel_match_preserves_serial_trace) {
    const char *source =
        "rule \"Low\" { salience 1; when Ready == true then Low = 1; }"
        "rule \"HighA\" { salience 10; when Ready == true then HighA = 1; }"
        "rule \"HighB\" { salience 10; when Ready == true then HighB = 1; }";
    re_engine_t *serial = re_engine_create(NULL, NULL);
    re_engine_t *parallel = re_engine_create(NULL, NULL);
    re_facts_t *serial_facts = re_facts_create(NULL, NULL);
    re_facts_t *parallel_facts = re_facts_create(NULL, NULL);
    re_program_t *serial_program = NULL, *parallel_program = NULL;
    re_executor_t *executor = NULL;
    re_concurrency_options_t options = {sizeof(options), RE_ABI_VERSION_MAJOR, 3u, 0u};
    re_value_t ready = {RE_VALUE_BOOL, {.boolean = 1}};
    parallel_trace_t serial_trace = {{{0}}, 0u}, parallel_trace = {{{0}}, 0u};
    re_callbacks_t callbacks = {record_parallel_trace, &serial_trace};
    ASSERT_EQ(re_program_load(NULL, text(source), NULL, &serial_program), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text(source), NULL, &parallel_program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(serial, serial_program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(parallel, parallel_program), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(serial_facts, text("Ready"), &ready), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(parallel_facts, text("Ready"), &ready), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(serial, serial_facts, NULL, &callbacks), RE_STATUS_OK);
    if (re_engine_executor_create(parallel, &options, &executor) == RE_STATUS_NOT_SUPPORTED) {
        re_facts_destroy(parallel_facts); re_facts_destroy(serial_facts);
        re_engine_destroy(parallel); re_engine_destroy(serial); return;
    }
    ASSERT_NOT_NULL(executor);
    callbacks.context = &parallel_trace;
    ASSERT_EQ(re_engine_run(parallel, parallel_facts, NULL, &callbacks), RE_STATUS_OK);
    ASSERT_EQ(parallel_trace.count, serial_trace.count);
    ASSERT_TRUE(memcmp(parallel_trace.names, serial_trace.names, sizeof(serial_trace.names)) == 0);
    re_executor_destroy(executor);
    re_facts_destroy(parallel_facts); re_facts_destroy(serial_facts);
    re_engine_destroy(parallel); re_engine_destroy(serial);
}

TEST(bounded_query_proves_fact_and_binds_variable) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_query_t *query = NULL;
    re_proof_t *proof = NULL;
    re_query_binding_t binding;
    re_query_options_t options = {sizeof(options), 8u, 4u, 0u, 0u};
    re_value_t value = {RE_VALUE_STRING, {.string = {"Ada", 3u}}};
    ASSERT_EQ(re_facts_set(facts, text("User"), &value), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("User == X"), &options, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    ASSERT_EQ(re_query_next(query, &proof), RE_STATUS_OK);
    ASSERT_EQ(re_proof_binding_count(proof), 1u);
    ASSERT_EQ(re_proof_binding_get(proof, 0u, &binding), RE_STATUS_OK);
    ASSERT_TRUE(binding.name.size == 1u && binding.name.data[0] == 'X');
    ASSERT_EQ(binding.value.type, RE_VALUE_STRING);
    ASSERT_TRUE(memcmp(binding.value.as.string.data, "Ada", 3u) == 0);
    ASSERT_EQ(re_query_next(query, &proof), RE_STATUS_NOT_FOUND);
    re_proof_destroy(proof);
    re_query_destroy(query);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(bounded_query_reports_disproof_unknown_and_limit) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_query_t *query = NULL;
    re_query_options_t options = {sizeof(options), 8u, 1u, 0u, 0u};
    re_value_t value = {RE_VALUE_BOOL, {.boolean = 1}};
    ASSERT_EQ(re_facts_set(facts, text("Ready"), &value), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("Ready == false"), &options, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_DISPROVED);
    re_query_destroy(query);
    query = NULL;
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("Missing == true"), &options, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_UNKNOWN);
    re_query_destroy(query);
    query = NULL;
    options.max_depth = 0u;
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("Ready == X"), &options, &query), RE_STATUS_LIMIT);
    ASSERT_EQ(re_query_result(query), RE_QUERY_LIMIT);
    re_query_destroy(query);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(query_proof_trace_is_deterministic_and_invalidated_by_mutation) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_query_t *query = NULL;
    re_proof_t *proof = NULL;
    re_string_t trace;
    re_value_t value = {RE_VALUE_BOOL, {.boolean = 1}};
    re_query_options_t options = {sizeof(options), 8u, 2u, 0u, 0u};
    ASSERT_EQ(re_facts_set(facts, text("Ready"), &value), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text("rule \"Approved\" { when Ready == true then Mark = 1; }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("Approved"), &options, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    ASSERT_EQ(re_query_next(query, &proof), RE_STATUS_OK);
    ASSERT_EQ(re_proof_trace_count(proof), 1u);
    ASSERT_EQ(re_proof_trace_get(proof, 0u, &trace), RE_STATUS_OK);
    ASSERT_TRUE(trace.size == 8u && memcmp(trace.data, "Approved", 8u) == 0);
    re_proof_destroy(proof);
    ASSERT_EQ(re_facts_set(facts, text("Ready"), &(re_value_t){RE_VALUE_BOOL, {.boolean = 0}}), RE_STATUS_OK);
    ASSERT_EQ(re_query_next(query, &proof), RE_STATUS_NOT_FOUND);
    re_query_destroy(query);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(backward_query_recurses_through_rule_name_conditions) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_query_t *query = NULL;
    re_proof_t *proof = NULL;
    re_string_t trace;
    re_query_options_t options = {sizeof(options), 8u, 4u, 0u, 0u};
    ASSERT_EQ(re_program_load(NULL, text("rule \"Base\" { when true then BaseValue = true; } rule \"Derived\" { when Base == true then DerivedValue = true; }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("Derived"), &options, &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    ASSERT_EQ(re_query_solution_count(query), 1u);
    ASSERT_EQ(re_query_next(query, &proof), RE_STATUS_OK);
    ASSERT_EQ(re_proof_trace_count(proof), 2u);
    ASSERT_EQ(re_proof_trace_get(proof, 0u, &trace), RE_STATUS_OK);
    ASSERT_TRUE(trace.size == 7u && memcmp(trace.data, "Derived", 7u) == 0);
    ASSERT_EQ(re_proof_trace_get(proof, 1u, &trace), RE_STATUS_OK);
    ASSERT_TRUE(trace.size == 4u && memcmp(trace.data, "Base", 4u) == 0);
    re_proof_destroy(proof);
    re_query_destroy(query);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(default_query_api_uses_unified_machine_path) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_query_t *query = NULL;
    re_proof_t *proof = NULL;
    re_string_t trace;
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_program_load(NULL, text(
        "rule \"Leaf\" { when true then Done = true; }"
        "rule \"Top\" { when goal(\"Leaf\") then Done = true; }"),
        NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query(engine, facts, text("Top"), &query), RE_STATUS_OK);
    ASSERT_EQ(re_query_result(query), RE_QUERY_PROVED);
    ASSERT_EQ(re_query_solution_count(query), 1u);
    ASSERT_EQ(re_query_next(query, &proof), RE_STATUS_OK);
    ASSERT_EQ(re_proof_trace_get(proof, 0u, &trace), RE_STATUS_OK);
    ASSERT_TRUE(trace.size == 3u && memcmp(trace.data, "Top", 3u) == 0);
    ASSERT_EQ(re_proof_trace_get(proof, 1u, &trace), RE_STATUS_OK);
    ASSERT_TRUE(trace.size == 4u && memcmp(trace.data, "Leaf", 4u) == 0);
    re_proof_destroy(proof);
    re_query_destroy(query);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST_MAIN_BEGIN()
    RUN_TEST(c99_header_contract);
    RUN_TEST(facts_copy_and_get_semantics);
    RUN_TEST(empty_strings_compare_and_copy);
    RUN_TEST(private_rete_two_condition_join_lifecycle);
    RUN_TEST(public_two_condition_join_uses_rete_network);
    RUN_TEST(public_rete_supports_bounded_boolean_expression_and_nested_fact);
    RUN_TEST(then_literal_assignment_updates_facts_and_callback);
    RUN_TEST(then_fact_reference_assignment_updates_facts_and_callback);
    RUN_TEST(forward_multi_action_failure_rolls_back_earlier_action);
    RUN_TEST(forward_multi_action_success_commits_all_actions);
    RUN_TEST(forward_callback_failure_rolls_back_action_mutations);
    RUN_TEST(grl_string_operators_match_in_forward_ir);
    RUN_TEST(grl_append_action_preserves_action_order);
    RUN_TEST(grl_arithmetic_precedence_is_observable);
    RUN_TEST(grl_arithmetic_supports_subtraction_and_division);
    RUN_TEST(grl_arithmetic_supports_negative_integer_multiplication);
    RUN_TEST(grl_arithmetic_mixes_int_and_double_as_double);
    RUN_TEST(grl_arithmetic_rejects_malformed_and_zero_division);
    RUN_TEST(grl_in_supports_array_literals_and_structured_arrays);
    RUN_TEST(grl_matches_uses_wildcards);
    RUN_TEST(grl_matches_supports_question_mark_and_empty_strings);
    RUN_TEST(grl_matches_rejects_nonmatching_wildcard_patterns);
    RUN_TEST(grl_matches_is_anchored_and_supports_zero_or_more_bytes);
    RUN_TEST(grl_matches_question_mark_consumes_one_byte);
    RUN_TEST(grl_matches_rejects_oversized_and_overflowing_patterns_without_dereference);
    RUN_TEST(malformed_action_requires_semicolon);
    RUN_TEST(malformed_action_rejects_trailing_tokens_transactionally);
    RUN_TEST(custom_function_is_registered_and_invoked_in_condition);
    RUN_TEST(custom_function_errors_propagate_from_action);
    RUN_TEST(custom_function_registration_validates_descriptor_and_reentrancy);
    RUN_TEST(dotted_fact_lookup_prefers_exact_flat_key);
    RUN_TEST(structured_values_support_nested_objects_and_arrays);
    RUN_TEST(array_literal_membership_matches_numeric_and_string_values);
    RUN_TEST(array_membership_covers_positive_negative_and_mixed_scalar_types);
    RUN_TEST(array_literal_membership_rejects_non_match_and_malformed_arrays);
    RUN_TEST(array_membership_uses_typed_equality_without_integer_precision_loss);
    RUN_TEST(array_membership_rejects_numeric_cross_type_equality);
    RUN_TEST(structured_array_membership_uses_owned_copy);
    RUN_TEST(array_membership_rejects_structured_non_array_and_nested_elements);
    RUN_TEST(array_membership_literals_reject_non_scalar_elements_and_bound_count);
    RUN_TEST(array_membership_array_copy_failure_leaves_facts_unchanged);
    RUN_TEST(null_missing_and_unknown_are_distinct);
    RUN_TEST(fact_lifecycle_ids_are_generation_safe_and_notify);
    RUN_TEST(fact_lifecycle_notifications_provide_change_snapshots);
    RUN_TEST(run_limits_have_independent_inclusive_boundaries);
    RUN_TEST(boolean_values_are_normalized);
    RUN_TEST(exact_independent_limits_are_inclusive);
    RUN_TEST(callback_can_mutate_facts);
    RUN_TEST(string_copy_is_freed_when_fact_capacity_growth_fails);
    RUN_TEST(bounded_source_and_numeric_range);
    RUN_TEST(compound_conditions_and_multiple_actions_execute_in_order);
    RUN_TEST(escaped_strings_are_unescaped);
    RUN_TEST(unknown_and_duplicate_attributes_fail_atomically);
    RUN_TEST(private_modules_reject_cycles_and_resolve_exports);
    RUN_TEST(private_modules_control_qualified_rule_visibility);
    RUN_TEST(private_modules_reject_private_imports_and_unknown_imports);
    RUN_TEST(private_accumulators_have_explicit_empty_and_numeric_rules);
    RUN_TEST(private_accumulators_preserve_mixed_numeric_precision);
    RUN_TEST(private_accumulators_reject_empty_and_non_numeric_values);
    RUN_TEST(private_utc_rule_bounds_use_injected_clock);
    RUN_TEST(private_utc_rule_bounds_have_exact_boundaries);
    RUN_TEST(private_utc_rule_bounds_reject_malformed_dates);
    RUN_TEST(fact_retract_notification_keeps_string_snapshot_alive);
    RUN_TEST(allocator_failure_status_propagates);
    RUN_TEST(overflow_length_is_rejected_before_allocator);
    RUN_TEST(sliding_window_records_eviction_lateness_limits_and_snapshot_restore);
    RUN_TEST(tumbling_window_uses_half_open_event_time_buckets);
    RUN_TEST(session_window_creates_extends_and_times_out_deterministically);
    RUN_TEST(tumbling_window_applies_late_policy_limits_and_empty_snapshot);
    RUN_TEST(stream_window_filters_and_aggregates_bounded_contents);
    RUN_TEST(stream_window_correlates_matching_types_keys_and_timeout_deterministically);
    RUN_TEST(callback_state_provider_put_get_delete_ttl_and_errors_propagate);
    RUN_TEST(memory_state_provider_is_bounded_ttl_atomic_and_snapshot_deterministic);
    RUN_TEST(memory_state_provider_rejects_bounds_corruption_and_redis);
    RUN_TEST(redis_provider_failure_does_not_create_or_fallback_to_memory);
    RUN_TEST(streaming_boundaries_overflow_and_restore_are_atomic);
    RUN_TEST(memory_provider_ttl_overflow_cleanup_and_restore_atomicity);
    RUN_TEST(streaming_and_state_capabilities_match_tested_extensions);
    RUN_TEST(callback_destroy_is_deferred);
    RUN_TEST(program_load_failure_is_transactional);
    RUN_TEST(successful_install_run_is_deterministic);
    RUN_TEST(salience_orders_activations_stably);
    RUN_TEST(salience_rejects_invalid_integer_ranges);
    RUN_TEST(salience_orders_matching_activations_deterministically);
    RUN_TEST(agenda_group_focus_selects_only_focused_group);
    RUN_TEST(agenda_group_defaults_to_main_and_activation_groups_are_independent);
    RUN_TEST(activation_group_fires_one_activation);
    RUN_TEST(no_loop_and_lock_on_active_are_enforced);
    RUN_TEST(run_honors_cancellation_and_limits);
    RUN_TEST(deferred_capabilities_are_explicitly_unsupported);
    RUN_TEST(optional_parallel_match_preserves_serial_trace);
    RUN_TEST(bounded_query_proves_fact_and_binds_variable);
    RUN_TEST(bounded_query_reports_disproof_unknown_and_limit);
    RUN_TEST(query_proof_trace_is_deterministic_and_invalidated_by_mutation);
    RUN_TEST(backward_query_recurses_through_rule_name_conditions);
    RUN_TEST(default_query_api_uses_unified_machine_path);
TEST_MAIN_END()
