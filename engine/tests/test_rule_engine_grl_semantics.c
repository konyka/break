#include "test_framework.h"
#include <rule_engine/rule_engine.h>
#include <string.h>

static re_string_t text(const char *value) { return (re_string_t){value, strlen(value)}; }
static re_value_t number(int64_t value) { return (re_value_t){RE_VALUE_INT64, {.int64_value = value}}; }

/* Builds structured fact Car { speed: <speed> } via the structured-value API,
 * mirroring the builders in engine/tests/test_rule_engine.c. */
static void set_structured_car(re_facts_t *facts, int64_t speed) {
    re_value_handle_t *car = NULL;
    re_value_t member = number(speed);
    ASSERT_EQ(re_value_create_object(facts, &car), RE_STATUS_OK);
    ASSERT_EQ(re_value_object_set(car, text("speed"), &member), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set_value(facts, text("Car"), car), RE_STATUS_OK);
    re_value_destroy(car);
}

/* Same builder with a caller-chosen member name: method-call tests need the
 * capitalized members (Speed) that setXxx/getXxx derive from the method name. */
static void set_named_car(re_facts_t *facts, const char *key, int64_t speed) {
    re_value_handle_t *car = NULL;
    re_value_t member = number(speed);
    ASSERT_EQ(re_value_create_object(facts, &car), RE_STATUS_OK);
    ASSERT_EQ(re_value_object_set(car, text(key), &member), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set_value(facts, text("Car"), car), RE_STATUS_OK);
    re_value_destroy(car);
}

typedef struct honk_state_t {
    size_t calls;
    size_t last_arg_count;
    int64_t first_arg;
} honk_state_t;

static re_status_t honk_function(re_engine_t *engine, re_facts_t *facts,
                                 const re_value_t *arguments, size_t count,
                                 re_value_t *out, void *context) {
    honk_state_t *state = context;
    (void)engine; (void)facts;
    state->calls++;
    state->last_arg_count = count;
    if (count != 0u) state->first_arg = arguments[0].as.int64_value;
    out->type = RE_VALUE_INT64;
    out->as.int64_value = 0;
    return RE_STATUS_OK;
}

TEST(set_path_updates_nested_structured_member) {
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t update = number(120);
    re_value_t out;
    ASSERT_NOT_NULL(facts);
    set_structured_car(facts, 80);
    ASSERT_EQ(re_facts_set_path(facts, text("Car.speed"), &update), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get_path(facts, text("Car.speed"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.as.int64_value, 120);
    re_facts_destroy(facts);
}

TEST(set_path_flat_key_shadows_nested_walk) {
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t flat = number(5);
    re_value_t update = number(9);
    re_value_t out;
    re_fact_id_t flat_id;
    ASSERT_NOT_NULL(facts);
    set_structured_car(facts, 80);
    /* Facts hold BOTH flat key "Car.speed"=5 and structured Car{speed:80}. */
    ASSERT_EQ(re_facts_insert(facts, text("Car.speed"), &flat, &flat_id), RE_STATUS_OK);
    /* set_path must update the flat key only. */
    ASSERT_EQ(re_facts_set_path(facts, text("Car.speed"), &update), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("Car.speed"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.as.int64_value, 9);
    /* Retracting the flat shadow reveals the nested member was left alone. */
    ASSERT_EQ(re_facts_retract(facts, flat_id), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get_path(facts, text("Car.speed"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.as.int64_value, 80);
    re_facts_destroy(facts);
}

TEST(set_path_missing_intermediate_returns_not_found) {
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t hp = number(200);
    re_value_t out;
    ASSERT_NOT_NULL(facts);
    set_structured_car(facts, 80);
    /* Missing intermediate member. */
    ASSERT_EQ(re_facts_set_path(facts, text("Car.engine.hp"), &hp), RE_STATUS_NOT_FOUND);
    /* A scalar intermediate is not an object either. */
    ASSERT_EQ(re_facts_set_path(facts, text("Car.speed.hp"), &hp), RE_STATUS_NOT_FOUND);
    /* Nothing was created or modified. */
    ASSERT_EQ(re_facts_get_path(facts, text("Car.engine.hp"), &out), RE_STATUS_NOT_FOUND);
    ASSERT_EQ(re_facts_get_path(facts, text("Car.speed"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.as.int64_value, 80);
    re_facts_destroy(facts);
}

TEST(set_path_rejects_unknown_value_type) {
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t unknown = {RE_VALUE_UNKNOWN, {0}};
    re_value_t fresh = number(1);
    ASSERT_NOT_NULL(facts);
    set_structured_car(facts, 80);
    /* Scalar values only: no object replacement via RE_VALUE_UNKNOWN. */
    ASSERT_EQ(re_facts_set_path(facts, text("Car.speed"), &unknown), RE_STATUS_INVALID_ARGUMENT);
    /* A dotless path for a missing key is never created by set_path. */
    ASSERT_EQ(re_facts_set_path(facts, text("Plain"), &fresh), RE_STATUS_NOT_FOUND);
    re_facts_destroy(facts);
}

TEST(rule_action_writes_nested_member) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_value_t out;
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    set_structured_car(facts, 80);
    ASSERT_EQ(re_program_load(NULL,
        text("rule \"R\" { when Car.speed > 0 then Car.speed = 120; }"),
        NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get_path(facts, text("Car.speed"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.as.int64_value, 120);
    /* The write reached the nested member; no flat shadow fact was created. */
    ASSERT_EQ(re_facts_get(facts, text("Car.speed"), &out), RE_STATUS_NOT_FOUND);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(method_set_updates_structured_member) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_value_t out;
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    set_named_car(facts, "Speed", 0);
    ASSERT_EQ(re_program_load(NULL,
        text("rule \"R\" { when Car.Speed == 0 then $Car.setSpeed(120); }"),
        NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get_path(facts, text("Car.Speed"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.as.int64_value, 120);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(method_set_creates_missing_member) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_value_t out;
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    set_named_car(facts, "Speed", 0);
    /* Car has no "Gear" member; setXxx inserts it into the object map. */
    ASSERT_EQ(re_program_load(NULL,
        text("rule \"R\" { when Car.Speed == 0 then $Car.setGear(3); }"),
        NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get_path(facts, text("Car.Gear"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.as.int64_value, 3);
    ASSERT_EQ(re_facts_get_path(facts, text("Car.Speed"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.as.int64_value, 0);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(method_get_operand_reads_member) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_value_t out;
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    set_named_car(facts, "Speed", 80);
    ASSERT_EQ(re_program_load(NULL,
        text("rule \"R\" { when Car.Speed > 0 then Top = $Car.getSpeed(); }"),
        NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("Top"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.as.int64_value, 80);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(method_reset_clears_members) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_value_t out;
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    set_named_car(facts, "Speed", 0);
    ASSERT_EQ(re_program_load(NULL,
        text("rule \"R\" { when Car.Speed == 0 then $Car.reset(); }"),
        NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get_path(facts, text("Car.Speed"), &out), RE_STATUS_NOT_FOUND);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(method_unknown_without_handler_not_supported) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_program_load(NULL,
        text("rule \"R\" { when true then $Car.fly(1); }"),
        NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_NOT_SUPPORTED);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(method_dispatches_registered_function) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_function_t *function = NULL;
    honk_state_t state = {0u, 0u, 0};
    re_function_descriptor_t descriptor = {sizeof(descriptor), RE_ABI_VERSION_MAJOR,
        {"honk", 4u}, honk_function, NULL, &state};
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_engine_register_function(engine, &descriptor, &function), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL,
        text("rule \"R\" { when true then $Car.honk(7); }"),
        NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(state.calls, 1u);
    ASSERT_EQ(state.last_arg_count, 1u);
    ASSERT_EQ(state.first_arg, 7);
    re_function_unregister(function);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(dollar_outside_method_context_parse_error) {
    re_program_t *program = NULL;
    ASSERT_EQ(re_program_load(NULL,
        text("rule \"R\" { when $Car.Speed == 0 then Top = 1; }"),
        NULL, &program), RE_STATUS_PARSE_ERROR);
    ASSERT_EQ(re_program_load(NULL,
        text("rule \"R\" { when $Car.getSpeed() == 0 then Top = 1; }"),
        NULL, &program), RE_STATUS_PARSE_ERROR);
    ASSERT_EQ(re_program_load(NULL,
        text("rule \"R\" { when true then $Car; }"),
        NULL, &program), RE_STATUS_PARSE_ERROR);
}

TEST(deffacts_load_seeds_facts_and_rules_fire) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_value_t out;
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_program_load(NULL,
        text("deffacts \"base\" { A = 1; B = 2; } "
             "rule \"R\" { when A == 1 and B == 2 then C = 3; }"),
        NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_load_deffacts(engine, facts, "base"), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("C"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.as.int64_value, 3);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(deffacts_null_name_loads_all) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_value_t out;
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_program_load(NULL,
        text("deffacts \"one\" { A = 1; } "
             "deffacts \"two\" { Items = [1, 2, 3]; } "
             "rule \"R\" { when 2 in Items then Found = 1; }"),
        NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_load_deffacts(engine, facts, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("A"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.as.int64_value, 1);
    /* The array literal became a structured array fact usable by `in`. */
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("Found"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.as.int64_value, 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(deffacts_unknown_name_not_found) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    /* No program installed yet. */
    ASSERT_EQ(re_engine_load_deffacts(engine, facts, NULL), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_program_load(NULL,
        text("deffacts \"base\" { A = 1; }"),
        NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_load_deffacts(engine, facts, "nope"), RE_STATUS_NOT_FOUND);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(deffacts_duplicate_block_parse_error) {
    re_program_t *program = NULL;
    ASSERT_EQ(re_program_load(NULL,
        text("deffacts \"x\" { A = 1; } deffacts \"x\" { B = 2; }"),
        NULL, &program), RE_STATUS_PARSE_ERROR);
}

TEST(deffacts_dotted_path_seeds_nested_member) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_value_t out;
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    set_structured_car(facts, 80);
    ASSERT_EQ(re_program_load(NULL,
        text("deffacts \"base\" { Car.speed = 120; }"),
        NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_load_deffacts(engine, facts, "base"), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get_path(facts, text("Car.speed"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.as.int64_value, 120);
    /* The write reached the nested member; no flat shadow fact was created. */
    ASSERT_EQ(re_facts_get(facts, text("Car.speed"), &out), RE_STATUS_NOT_FOUND);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(reset_with_deffacts_clears_and_reseeds) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_value_t out;
    re_value_t extra = number(9);
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_program_load(NULL,
        text("deffacts \"base\" { A = 1; B = 2; } "
             "rule \"R\" { when A == 1 and B == 2 then D = 4; }"),
        NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_load_deffacts(engine, facts, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("D"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.as.int64_value, 4);
    ASSERT_EQ(re_facts_set(facts, text("Extra"), &extra), RE_STATUS_OK);
    ASSERT_EQ(re_engine_reset_with_deffacts(engine, facts), RE_STATUS_OK);
    /* Working memory was cleared: manual and TMS-derived facts are gone. */
    ASSERT_EQ(re_facts_get(facts, text("Extra"), &out), RE_STATUS_NOT_FOUND);
    ASSERT_EQ(re_facts_get(facts, text("D"), &out), RE_STATUS_NOT_FOUND);
    ASSERT_EQ(re_facts_get(facts, text("A"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.as.int64_value, 1);
    ASSERT_EQ(re_facts_get(facts, text("B"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.as.int64_value, 2);
    /* Rules fire again from the reseeded state. */
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("D"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.as.int64_value, 4);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(template_substitutes_params_and_defaults) {
    re_rule_template_t *t = NULL;
    re_template_param_t params[1];
    char buffer[256];
    size_t size;
    ASSERT_EQ(re_rule_template_create(text("speed-rule"),
        text("Speed > {{limit}}"), text("Alert = 1"), 0, &t), RE_STATUS_OK);
    ASSERT_NOT_NULL(t);
    ASSERT_EQ(re_rule_template_param_default(t, text("limit"), text("50")), RE_STATUS_OK);
    /* No params supplied: the default fills the placeholder. */
    size = sizeof(buffer);
    ASSERT_EQ(re_rule_template_instantiate(t, text("R"), NULL, 0u, buffer, &size), RE_STATUS_OK);
    ASSERT_TRUE(strstr(buffer, "Speed > 50") != NULL);
    /* Salience 0 omits the salience part. */
    ASSERT_TRUE(strstr(buffer, "salience") == NULL);
    ASSERT_EQ(size, strlen(buffer) + 1u);
    /* A supplied param wins over the default. */
    params[0].name = text("limit");
    params[0].value = text("80");
    size = sizeof(buffer);
    ASSERT_EQ(re_rule_template_instantiate(t, text("R"), params, 1u, buffer, &size), RE_STATUS_OK);
    ASSERT_TRUE(strstr(buffer, "Speed > 80") != NULL);
    re_rule_template_destroy(t);
}

TEST(template_missing_required_param_invalid) {
    re_rule_template_t *t = NULL;
    char buffer[256];
    size_t size = sizeof(buffer);
    ASSERT_EQ(re_rule_template_create(text("t"),
        text("Speed > {{limit}}"), text("Alert = 1"), 0, &t), RE_STATUS_OK);
    ASSERT_NOT_NULL(t);
    /* {{limit}} has no default and nothing is supplied. */
    ASSERT_EQ(re_rule_template_instantiate(t, text("R"), NULL, 0u, buffer, &size),
              RE_STATUS_INVALID_ARGUMENT);
    re_rule_template_destroy(t);
}

TEST(template_unknown_supplied_param_invalid) {
    re_rule_template_t *t = NULL;
    re_template_param_t params[1];
    char buffer[256];
    size_t size = sizeof(buffer);
    ASSERT_EQ(re_rule_template_create(text("t"),
        text("Speed > {{limit}}"), text("Alert = 1"), 0, &t), RE_STATUS_OK);
    ASSERT_NOT_NULL(t);
    ASSERT_EQ(re_rule_template_param_default(t, text("limit"), text("50")), RE_STATUS_OK);
    /* No {{zzz}} placeholder exists in either template. */
    params[0].name = text("zzz");
    params[0].value = text("1");
    ASSERT_EQ(re_rule_template_instantiate(t, text("R"), params, 1u, buffer, &size),
              RE_STATUS_INVALID_ARGUMENT);
    re_rule_template_destroy(t);
}

TEST(template_generated_rule_parses_and_fires) {
    re_rule_template_t *t = NULL;
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_template_param_t params[1];
    re_value_t speed = number(90);
    re_value_t out;
    char buffer[256];
    size_t size;
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_rule_template_create(text("speed"),
        text("Speed > {{limit}}"), text("Alert = 1"), 10, &t), RE_STATUS_OK);
    ASSERT_NOT_NULL(t);
    params[0].name = text("limit");
    params[0].value = text("80");
    size = sizeof(buffer);
    ASSERT_EQ(re_rule_template_instantiate(t, text("fast"), params, 1u, buffer, &size), RE_STATUS_OK);
    /* The emitted text has the exact documented shape, salience included. */
    ASSERT_STR_EQ(buffer, "rule \"fast\" salience 10 {\nwhen\nSpeed > 80\nthen\nAlert = 1;\n}");
    ASSERT_EQ(re_program_load(NULL, text(buffer), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("Speed"), &speed), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("Alert"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.as.int64_value, 1);
    re_rule_template_destroy(t);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(template_buffer_too_small_reports_required_size) {
    re_rule_template_t *t = NULL;
    char small[8];
    char exact[64];
    size_t size;
    size_t required;
    ASSERT_EQ(re_rule_template_create(text("t"),
        text("Speed > {{limit}}"), text("Alert = 1"), 0, &t), RE_STATUS_OK);
    ASSERT_NOT_NULL(t);
    ASSERT_EQ(re_rule_template_param_default(t, text("limit"), text("50")), RE_STATUS_OK);
    /* Size query: NULL buffer with zero capacity reports the required size. */
    size = 0u;
    ASSERT_EQ(re_rule_template_instantiate(t, text("R"), NULL, 0u, NULL, &size), RE_STATUS_LIMIT);
    required = size;
    ASSERT_TRUE(required > sizeof(small));
    /* A too-small buffer reports the same required size. */
    size = sizeof(small);
    ASSERT_EQ(re_rule_template_instantiate(t, text("R"), NULL, 0u, small, &size), RE_STATUS_LIMIT);
    ASSERT_EQ(size, required);
    /* Exactly the reported size succeeds. */
    size = required;
    ASSERT_EQ(re_rule_template_instantiate(t, text("R"), NULL, 0u, exact, &size), RE_STATUS_OK);
    ASSERT_EQ(size, required);
    ASSERT_EQ(strlen(exact) + 1u, required);
    re_rule_template_destroy(t);
}

TEST(member_string_write_survives_source_mutation) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_fact_id_t id;
    re_value_t msg = {RE_VALUE_STRING, {0}};
    re_value_t out;
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    set_structured_car(facts, 80);
    msg.as.string = text("hello");
    ASSERT_EQ(re_facts_insert(facts, text("Msg"), &msg, &id), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL,
        text("rule \"copy\" { when Msg == \"hello\" then Car.note = Msg; }"),
        NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get_path(facts, text("Car.note"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.type, RE_VALUE_STRING);
    ASSERT_TRUE(out.as.string.size == 5u && memcmp(out.as.string.data, "hello", 5u) == 0);
    /* Mutating Msg frees the old "hello" fact storage; the member owns its
     * own copy, so it must still read back the original string. */
    msg.as.string = text("world!!");
    ASSERT_EQ(re_facts_set(facts, text("Msg"), &msg), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get_path(facts, text("Car.note"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.type, RE_VALUE_STRING);
    ASSERT_TRUE(out.as.string.size == 5u && memcmp(out.as.string.data, "hello", 5u) == 0);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(member_method_string_write_survives_source_mutation) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_fact_id_t id;
    re_value_t msg = {RE_VALUE_STRING, {0}};
    re_value_t out;
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    set_structured_car(facts, 80);
    msg.as.string = text("hello");
    ASSERT_EQ(re_facts_insert(facts, text("Msg"), &msg, &id), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL,
        text("rule \"copy\" { when Msg == \"hello\" then $Car.setNote(Msg); }"),
        NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    /* setNote derives the member name "Note". */
    ASSERT_EQ(re_facts_get_path(facts, text("Car.Note"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.type, RE_VALUE_STRING);
    ASSERT_TRUE(out.as.string.size == 5u && memcmp(out.as.string.data, "hello", 5u) == 0);
    /* Same ownership guarantee through the method-call write path. */
    msg.as.string = text("world!!");
    ASSERT_EQ(re_facts_set(facts, text("Msg"), &msg), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get_path(facts, text("Car.Note"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.type, RE_VALUE_STRING);
    ASSERT_TRUE(out.as.string.size == 5u && memcmp(out.as.string.data, "hello", 5u) == 0);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(structured_string_member_roundtrip_owns_storage) {
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_handle_t *car = NULL;
    re_value_t name = {RE_VALUE_STRING, {0}};
    re_value_t out;
    ASSERT_NOT_NULL(facts);
    name.as.string = text("alpha");
    ASSERT_EQ(re_value_create_object(facts, &car), RE_STATUS_OK);
    ASSERT_EQ(re_value_object_set(car, text("name"), &name), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set_value(facts, text("Car"), car), RE_STATUS_OK);
    /* Every store deep-copies: the builder handle, the stored fact, and the
     * caller's value are independent, so destroying the handle cannot disturb
     * the fact and later overwrites free only the member's own payload. */
    re_value_destroy(car);
    ASSERT_EQ(re_facts_get_path(facts, text("Car.name"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.type, RE_VALUE_STRING);
    ASSERT_TRUE(out.as.string.size == 5u && memcmp(out.as.string.data, "alpha", 5u) == 0);
    name.as.string = text("beta-longer");
    ASSERT_EQ(re_facts_set_path(facts, text("Car.name"), &name), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get_path(facts, text("Car.name"), &out), RE_STATUS_OK);
    ASSERT_TRUE(out.as.string.size == 11u && memcmp(out.as.string.data, "beta-longer", 11u) == 0);
    re_facts_destroy(facts);
}

TEST_MAIN_BEGIN()
    RUN_TEST(set_path_updates_nested_structured_member);
    RUN_TEST(set_path_flat_key_shadows_nested_walk);
    RUN_TEST(set_path_missing_intermediate_returns_not_found);
    RUN_TEST(set_path_rejects_unknown_value_type);
    RUN_TEST(rule_action_writes_nested_member);
    RUN_TEST(method_set_updates_structured_member);
    RUN_TEST(method_set_creates_missing_member);
    RUN_TEST(method_get_operand_reads_member);
    RUN_TEST(method_reset_clears_members);
    RUN_TEST(method_unknown_without_handler_not_supported);
    RUN_TEST(method_dispatches_registered_function);
    RUN_TEST(dollar_outside_method_context_parse_error);
    RUN_TEST(deffacts_load_seeds_facts_and_rules_fire);
    RUN_TEST(deffacts_null_name_loads_all);
    RUN_TEST(deffacts_unknown_name_not_found);
    RUN_TEST(deffacts_duplicate_block_parse_error);
    RUN_TEST(deffacts_dotted_path_seeds_nested_member);
    RUN_TEST(reset_with_deffacts_clears_and_reseeds);
    RUN_TEST(template_substitutes_params_and_defaults);
    RUN_TEST(template_missing_required_param_invalid);
    RUN_TEST(template_unknown_supplied_param_invalid);
    RUN_TEST(template_generated_rule_parses_and_fires);
    RUN_TEST(template_buffer_too_small_reports_required_size);
    RUN_TEST(member_string_write_survives_source_mutation);
    RUN_TEST(member_method_string_write_survives_source_mutation);
    RUN_TEST(structured_string_member_roundtrip_owns_storage);
TEST_MAIN_END()
