#include "re_internal.h"
#include <string.h>

static re_status_t resolve_operand(const re_facts_t *facts, const re_operand_t *operand, re_value_t *value) {
    if (operand->kind == RE_OPERAND_LITERAL) { *value = operand->value; return RE_STATUS_OK; }
    return re_facts_resolve(facts, (re_string_t){operand->fact_name, operand->fact_name_size}, value);
}

static re_status_t apply_action(re_facts_t *facts, const re_rule_t *rule) {
    re_value_t value;
    re_status_t status = resolve_operand(facts, &rule->action_value, &value);
    if (status != RE_STATUS_OK) return status;
    return re_facts_set(facts, (re_string_t){rule->action_name, rule->action_name_size}, &value);
}

static re_status_t finish_run(re_engine_t *engine, re_facts_t *facts, re_status_t status) {
    int destroy_engine;
    int destroy_facts;
    destroy_engine = engine->destroy_requested;
    destroy_facts = facts->destroy_requested;
    engine->running = 0;
    facts->running = 0;
    if (destroy_facts) re_facts_destroy(facts);
    if (destroy_engine) re_engine_destroy(engine);
    return status;
}

int re_value_compare(const re_value_t *left, const re_value_t *right, re_compare_t compare) {
    double l; double r;
    if (compare == RE_COMPARE_TRUE) return 1;
    if (left->type == RE_VALUE_INT64 && right->type == RE_VALUE_INT64) { l = (double)left->as.int64_value; r = (double)right->as.int64_value; }
    else if (left->type == RE_VALUE_DOUBLE && right->type == RE_VALUE_DOUBLE) { l = left->as.double_value; r = right->as.double_value; }
    else if (left->type == RE_VALUE_INT64 && right->type == RE_VALUE_DOUBLE) { l = (double)left->as.int64_value; r = right->as.double_value; }
    else if (left->type == RE_VALUE_DOUBLE && right->type == RE_VALUE_INT64) { l = left->as.double_value; r = (double)right->as.int64_value; }
    else if (left->type == RE_VALUE_BOOL && right->type == RE_VALUE_BOOL) { l = (double)left->as.boolean; r = (double)right->as.boolean; }
    else if (left->type == RE_VALUE_STRING && right->type == RE_VALUE_STRING) {
        size_t n = left->as.string.size < right->as.string.size ? left->as.string.size : right->as.string.size; int c = n == 0u ? 0 : memcmp(left->as.string.data, right->as.string.data, n);
        if (c == 0) c = left->as.string.size < right->as.string.size ? -1 : left->as.string.size > right->as.string.size;
        l = (double)c; r = 0.0;
    } else return 0;
    if (compare == RE_COMPARE_EQ) return l == r;
    if (compare == RE_COMPARE_NE) return l != r;
    if (compare == RE_COMPARE_GT) return l > r;
    if (compare == RE_COMPARE_GE) return l >= r;
    if (compare == RE_COMPARE_LT) return l < r;
    return l <= r;
}

re_engine_t *re_engine_create(const re_allocator_t *allocator, const re_limits_t *limits) {
    re_allocator_impl_t a; re_engine_t *engine; re_allocator_init(&a, allocator);
    if (a.api.alloc == NULL || a.api.realloc == NULL || a.api.free == NULL) return NULL;
    engine = re_alloc(&a, sizeof(*engine)); if (engine == NULL) return NULL;
    engine->allocator = a; engine->limits = limits != NULL ? *limits : re_default_limits(); engine->program = NULL; engine->running = 0; engine->destroy_requested = 0; return engine;
}
void re_engine_destroy(re_engine_t *engine) {
    if (engine == NULL) return;
    if (engine->running) { engine->destroy_requested = 1; return; }
    re_program_destroy(engine->program); re_free(&engine->allocator, engine);
}
re_capabilities_t re_engine_capabilities(const re_engine_t *engine) { return engine == NULL ? 0u : RE_CAP_CORE_GRL | RE_CAP_FACTS | RE_CAP_FORWARD_EXECUTION; }
re_status_t re_engine_install(re_engine_t *engine, re_program_t *program) {
    re_program_t *old; if (engine == NULL || program == NULL) return RE_STATUS_INVALID_ARGUMENT;
    if (program->rule_count > engine->limits.max_rules && engine->limits.max_rules != 0u) return RE_STATUS_LIMIT;
    if (engine->running) return RE_STATUS_BUSY;
    old = engine->program; engine->program = program; re_program_destroy(old); return RE_STATUS_OK;
}

re_status_t re_engine_run(re_engine_t *engine, re_facts_t *facts, const re_run_options_t *options, const re_callbacks_t *callbacks) {
    size_t i; size_t firings = 0u; size_t agenda_activations = 0u; re_limits_t limits; int explicit_limits;
    if (engine == NULL || facts == NULL) return RE_STATUS_INVALID_ARGUMENT;
    if (engine->running) return RE_STATUS_BUSY;
    engine->running = 1;
    if (facts->running) { engine->running = 0; return RE_STATUS_BUSY; }
    facts->running = 1;
    explicit_limits = options != NULL && options->limits != NULL;
    limits = explicit_limits ? *options->limits : engine->limits;
    if (limits.max_source_bytes == 0u) limits.max_source_bytes = engine->limits.max_source_bytes;
    if (limits.max_rules == 0u) limits.max_rules = engine->limits.max_rules;
    if (limits.max_facts == 0u) limits.max_facts = engine->limits.max_facts;
    if (limits.max_agenda_activations == 0u) limits.max_agenda_activations = engine->limits.max_agenda_activations;
    if (limits.max_firings == 0u) limits.max_firings = engine->limits.max_firings;
    if (engine->program == NULL) return finish_run(engine, facts, RE_STATUS_OK);
    for (i = 0u; i < engine->program->rule_count; ++i) {
        re_rule_t *rule = &engine->program->rules[i]; re_value_t left; re_value_t right; re_rule_event_t event; re_status_t status;
        if (options != NULL && options->is_cancelled != NULL && options->is_cancelled(options->cancel_context) != 0) return finish_run(engine, facts, RE_STATUS_CANCELLED);
        status = resolve_operand(facts, &rule->left, &left); if (status == RE_STATUS_NOT_FOUND) continue; if (status != RE_STATUS_OK) return finish_run(engine, facts, status);
        if (rule->compare != RE_COMPARE_TRUE) { status = resolve_operand(facts, &rule->right, &right); if (status == RE_STATUS_NOT_FOUND) continue; if (status != RE_STATUS_OK || !re_value_compare(&left, &right, rule->compare)) continue; }
        if (limits.max_agenda_activations != 0u && agenda_activations >= limits.max_agenda_activations) return finish_run(engine, facts, RE_STATUS_LIMIT);
        ++agenda_activations;
        event.rule_name.data = rule->name; event.rule_name.size = rule->name_size; event.salience = rule->salience; event.activation_sequence = (uint64_t)firings + 1u;
        status = apply_action(facts, rule); if (status != RE_STATUS_OK) return finish_run(engine, facts, status);
        if (callbacks != NULL && callbacks->action != NULL) { status = callbacks->action(engine, facts, &event, callbacks->context); if (status != RE_STATUS_OK) return finish_run(engine, facts, status); }
        ++firings; if (limits.max_firings != 0u && firings >= limits.max_firings) return finish_run(engine, facts, RE_STATUS_LIMIT);
    }
    return finish_run(engine, facts, RE_STATUS_OK);
}
