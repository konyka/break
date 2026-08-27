#include "re_internal.h"
#include "ir.h"
#include <string.h>

static int wildcard_match(re_string_t input, re_string_t pattern) {
    size_t input_at = 0u;
    size_t pattern_at = 0u;
    size_t star_pattern = SIZE_MAX;
    size_t star_input = 0u;
    size_t steps = 0u;
    size_t step_limit;
    if (pattern.size == SIZE_MAX || input.size > SIZE_MAX / (pattern.size + 1u)) return 0;
    step_limit = input.size * (pattern.size + 1u);
    if (step_limit == SIZE_MAX) return 0;
    ++step_limit;
    while (input_at < input.size || pattern_at < pattern.size) {
        if (++steps > step_limit) return 0;
        if (input_at < input.size && pattern_at < pattern.size &&
            (pattern.data[pattern_at] == '?' ||
             pattern.data[pattern_at] == input.data[input_at])) {
            ++input_at;
            ++pattern_at;
        } else if (pattern_at < pattern.size && pattern.data[pattern_at] == '*') {
            star_pattern = pattern_at++;
            star_input = input_at;
        } else if (star_pattern != SIZE_MAX) {
            pattern_at = star_pattern + 1u;
            input_at = ++star_input;
        } else {
            return 0;
        }
    }
    while (pattern_at < pattern.size && pattern.data[pattern_at] == '*') ++pattern_at;
    return pattern_at == pattern.size;
}

static re_status_t resolve_operand(const re_facts_t *facts, const re_operand_t *operand, re_value_t *value) {
    if (operand->kind == RE_OPERAND_LITERAL) { *value = operand->value; return RE_STATUS_OK; }
    return re_facts_get_path(facts, (re_string_t){operand->fact_name, operand->fact_name_size}, value);
}
int re_condition_is_pure(const re_expr_t *expr) {
    if (expr == NULL) return 0;
    if (expr->kind == RE_EXPR_COMPARE) {
        return expr->left.kind != RE_OPERAND_FUNCTION && expr->right.kind != RE_OPERAND_FUNCTION;
    }
    if (expr->kind == RE_EXPR_TRUE || expr->kind == RE_EXPR_FALSE) return 1;
    return re_condition_is_pure(expr->first) &&
           (expr->kind == RE_EXPR_NOT || re_condition_is_pure(expr->second));
}
re_status_t re_engine_match_rule(const re_engine_t *engine, const re_facts_t *facts,
                                 const re_rule_t *rule, int *matched) {
    size_t index;
    if (engine == NULL || engine->program == NULL || rule == NULL) return RE_STATUS_INVALID_ARGUMENT;
    for (index = 0u; index < engine->program->rule_count; ++index)
        if (&engine->program->rules[index] == rule) break;
    if (index == engine->program->rule_count) return RE_STATUS_INVALID_ARGUMENT;
    return re_ir_match_rule(engine, (re_facts_t *)facts, engine->program->ir, index, matched);
}

re_status_t re_operand_resolve(re_engine_t *engine, re_facts_t *facts,
                               const re_operand_t *operand, re_value_t *value) {
    size_t i;
    re_value_t *arguments;
    re_function_t *function;
    re_status_t status;
    if (operand->kind != RE_OPERAND_FUNCTION) return resolve_operand(facts, operand, value);
    for (function = engine->functions; function != NULL; function = function->next)
        if (!function->unregistered && function->name_size == operand->function_name_size &&
            memcmp(function->name, operand->function_name, function->name_size) == 0) break;
    if (function == NULL) return RE_STATUS_NOT_FOUND;
    arguments = operand->argument_count == 0u ? NULL : re_alloc(&engine->allocator, operand->argument_count * sizeof(*arguments));
    if (operand->argument_count != 0u && arguments == NULL) return RE_STATUS_OUT_OF_MEMORY;
    for (i = 0u; i < operand->argument_count; ++i) {
        status = re_operand_resolve(engine, facts, &operand->arguments[i], &arguments[i]);
        if (status != RE_STATUS_OK) { re_free(&engine->allocator, arguments); return status; }
    }
    function->active_calls++;
    status = function->call(engine, facts, arguments, operand->argument_count, value, function->context);
    function->active_calls--;
    re_free(&engine->allocator, arguments);
    return status;
}

static re_status_t finish_run(re_engine_t *engine, re_facts_t *facts, re_status_t status) {
    int destroy_engine;
    int destroy_facts;
    destroy_engine = engine->destroy_requested;
    destroy_facts = facts->destroy_requested;
    engine->running = 0;
    facts->running = 0;
    facts->mutation_allowed = 0;
    facts->read_allowed = 0;
    if (destroy_facts) re_facts_destroy(facts);
    if (destroy_engine) re_engine_destroy(engine);
    return status;
}

int re_value_compare(const re_value_t *left, const re_value_t *right, re_compare_t compare) {
    double l; double r;
    if (compare == RE_COMPARE_TRUE) return 1;
    if (left->type == RE_VALUE_STRING && right->type == RE_VALUE_STRING &&
        (compare == RE_COMPARE_CONTAINS || compare == RE_COMPARE_STARTS_WITH ||
         compare == RE_COMPARE_ENDS_WITH || compare == RE_COMPARE_MATCHES)) {
        size_t i;
        if (compare == RE_COMPARE_STARTS_WITH)
            return right->as.string.size <= left->as.string.size &&
                   memcmp(left->as.string.data, right->as.string.data, right->as.string.size) == 0;
        if (compare == RE_COMPARE_ENDS_WITH)
            return right->as.string.size <= left->as.string.size &&
                   memcmp(left->as.string.data + left->as.string.size - right->as.string.size,
                          right->as.string.data, right->as.string.size) == 0;
        if (compare == RE_COMPARE_MATCHES)
            return wildcard_match(left->as.string, right->as.string);
        if (right->as.string.size == 0u) return 1;
        for (i = 0u; i + right->as.string.size <= left->as.string.size; ++i)
            if (memcmp(left->as.string.data + i, right->as.string.data,
                       right->as.string.size) == 0) return 1;
        return 0;
    }
    if (left->type == RE_VALUE_INT64 && right->type == RE_VALUE_INT64) {
        if (compare == RE_COMPARE_EQ) return left->as.int64_value == right->as.int64_value;
        if (compare == RE_COMPARE_NE) return left->as.int64_value != right->as.int64_value;
        if (compare == RE_COMPARE_GT) return left->as.int64_value > right->as.int64_value;
        if (compare == RE_COMPARE_GE) return left->as.int64_value >= right->as.int64_value;
        if (compare == RE_COMPARE_LT) return left->as.int64_value < right->as.int64_value;
        if (compare == RE_COMPARE_LE) return left->as.int64_value <= right->as.int64_value;
        return 0;
    }
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

int re_value_equal_typed(const re_value_t *left, const re_value_t *right) {
    if (left == NULL || right == NULL || left->type != right->type) return 0;
    switch (left->type) {
    case RE_VALUE_BOOL: return left->as.boolean == right->as.boolean;
    case RE_VALUE_INT64: return left->as.int64_value == right->as.int64_value;
    case RE_VALUE_DOUBLE: return left->as.double_value == right->as.double_value;
    case RE_VALUE_STRING:
        return left->as.string.size == right->as.string.size &&
            (left->as.string.size == 0u || memcmp(left->as.string.data,
                                                    right->as.string.data,
                                                    left->as.string.size) == 0);
    case RE_VALUE_NULL: case RE_VALUE_UNKNOWN: case RE_VALUE_NONE: return 1;
    default: return 0;
    }
}

re_engine_t *re_engine_create(const re_allocator_t *allocator, const re_limits_t *limits) {
    re_allocator_impl_t a; re_engine_t *engine; re_allocator_init(&a, allocator);
    if (a.api.alloc == NULL || a.api.realloc == NULL || a.api.free == NULL) return NULL;
    engine = re_alloc(&a, sizeof(*engine)); if (engine == NULL) return NULL;
    engine->allocator = a; engine->limits = limits != NULL ? *limits : re_default_limits(); engine->program = NULL; engine->running = 0; engine->destroy_requested = 0; engine->functions = NULL; engine->executor = NULL; engine->rete_network = NULL; return engine;
}

static void sort_activation_indices(const re_program_t *program, size_t *indices) {
    size_t i;
    for (i = 1u; i < program->rule_count; ++i) {
        size_t current = indices[i];
        size_t j = i;
        while (j != 0u) {
            const re_rule_t *left = &program->rules[indices[j - 1u]];
            const re_rule_t *right = &program->rules[current];
            if (left->salience > right->salience ||
                (left->salience == right->salience && left->source_order < right->source_order)) break;
            indices[j] = indices[j - 1u];
            --j;
        }
        indices[j] = current;
    }
}
static void free_agenda_state(const re_allocator_impl_t *allocator, size_t *indices,
                              unsigned char *fired_no_loop, char **activation_groups,
                              char **locked_groups) {
    re_free(allocator, locked_groups); re_free(allocator, activation_groups);
    re_free(allocator, fired_no_loop); re_free(allocator, indices);
}
void re_engine_destroy(re_engine_t *engine) {
    if (engine == NULL) return;
    if (engine->running) { engine->destroy_requested = 1; return; }
    re_executor_destroy(engine->executor);
    if (engine->rete_network != NULL && engine->rete_network->engine_owned)
        re_rete_network_destroy_internal(engine->rete_network);
    engine->rete_network = NULL;
    while (engine->functions != NULL) { re_function_t *function = engine->functions; engine->functions = function->next; if (function->release != NULL) function->release(function->context); re_free(&engine->allocator, function->name); re_free(&engine->allocator, function); }
    re_program_destroy(engine->program); re_free(&engine->allocator, engine);
}
re_capabilities_t re_engine_capabilities(const re_engine_t *engine) { return engine == NULL ? 0u : RE_CAP_CORE_GRL | RE_CAP_FACTS | RE_CAP_FORWARD_EXECUTION; }

re_status_t re_engine_capabilities_v2(const re_engine_t *engine, uint32_t version, re_capabilities_v2_t *out) {
    if (engine == NULL || out == NULL) return RE_STATUS_INVALID_ARGUMENT;
    if (version != RE_ABI_VERSION_MAJOR) return RE_STATUS_NOT_SUPPORTED;
    *out = RE_CAP2_CUSTOM_FUNCTIONS | RE_CAP2_STRUCTURED_VALUES | RE_CAP2_FACT_LIFECYCLE |
           RE_CAP2_STREAMING_WINDOWS | RE_CAP2_STATE_PROVIDER;
    if (engine->rete_network != NULL) *out |= RE_CAP2_AGENDA_RETE;
#if defined(RE_ENABLE_C11_PARALLEL)
    *out |= RE_CAP2_CONCURRENCY;
#endif
    return RE_STATUS_OK;
}
re_status_t re_engine_extension_info(const re_engine_t *engine, re_extension_id_t id, uint32_t version, re_extension_info_t *out) {
    if (engine == NULL || out == NULL) return RE_STATUS_INVALID_ARGUMENT;
    if ((id != RE_EXTENSION_CUSTOM_FUNCTIONS && id != RE_EXTENSION_STRUCTURED_VALUES && id != RE_EXTENSION_FACT_LIFECYCLE &&
         id != RE_EXTENSION_AGENDA_RETE &&
         id != RE_EXTENSION_STREAMING_WINDOWS && id != RE_EXTENSION_STATE_PROVIDER
#if defined(RE_ENABLE_C11_PARALLEL)
         && id != RE_EXTENSION_CONCURRENCY
#endif
         ) || version != 1u || out->struct_size < sizeof(*out)) return RE_STATUS_NOT_SUPPORTED;
    out->abi_major = RE_ABI_VERSION_MAJOR; out->abi_minor = RE_ABI_VERSION_MINOR; out->extension_id = id; out->extension_version = 1u; out->reserved = 0u;
    if (id == RE_EXTENSION_AGENDA_RETE && engine->rete_network == NULL) return RE_STATUS_NOT_SUPPORTED;
    out->capability_bit = id == RE_EXTENSION_CUSTOM_FUNCTIONS ? RE_CAP2_CUSTOM_FUNCTIONS :
        id == RE_EXTENSION_STRUCTURED_VALUES ? RE_CAP2_STRUCTURED_VALUES :
        id == RE_EXTENSION_FACT_LIFECYCLE ? RE_CAP2_FACT_LIFECYCLE :
        id == RE_EXTENSION_AGENDA_RETE ? RE_CAP2_AGENDA_RETE :
        id == RE_EXTENSION_STREAMING_WINDOWS ? RE_CAP2_STREAMING_WINDOWS :
        id == RE_EXTENSION_STATE_PROVIDER ? RE_CAP2_STATE_PROVIDER : RE_CAP2_CONCURRENCY;
    return RE_STATUS_OK;
}
re_status_t re_engine_register_function(re_engine_t *engine, const re_function_descriptor_t *descriptor, re_function_t **out) {
    re_function_t *function;
    if (engine == NULL || descriptor == NULL || out == NULL || descriptor->struct_size < sizeof(*descriptor) || descriptor->abi_version != RE_ABI_VERSION_MAJOR || descriptor->name.data == NULL || descriptor->name.size == 0u || descriptor->call == NULL) return RE_STATUS_INVALID_ARGUMENT;
    if (engine->running) return RE_STATUS_BUSY;
    *out = NULL; function = re_alloc(&engine->allocator, sizeof(*function)); if (function == NULL) return RE_STATUS_OUT_OF_MEMORY; memset(function, 0, sizeof(*function));
    if (re_copy_string(&engine->allocator, descriptor->name, &function->name) != RE_STATUS_OK) { re_free(&engine->allocator, function); return RE_STATUS_OUT_OF_MEMORY; }
    function->engine = engine; function->name_size = descriptor->name.size; function->call = descriptor->call; function->release = descriptor->release; function->context = descriptor->context; function->next = engine->functions; engine->functions = function; *out = function; return RE_STATUS_OK;
}
void re_function_unregister(re_function_t *function) {
    re_function_t **link;
    if (function == NULL || function->unregistered) return;
    if (function->active_calls != 0u) return;
    link = &function->engine->functions; while (*link != NULL && *link != function) link = &(*link)->next;
    if (*link == function) *link = function->next;
    function->unregistered = 1; if (function->release != NULL) function->release(function->context); re_free(&function->engine->allocator, function->name); re_free(&function->engine->allocator, function);
}
re_status_t re_engine_install(re_engine_t *engine, re_program_t *program) {
    re_program_t *old; if (engine == NULL || program == NULL) return RE_STATUS_INVALID_ARGUMENT;
    if (re_ir_validate(program->ir) != RE_STATUS_OK) return RE_STATUS_INVALID_ARGUMENT;
    if (program->rule_count > engine->limits.max_rules && engine->limits.max_rules != 0u) return RE_STATUS_LIMIT;
    if (engine->running) return RE_STATUS_BUSY;
    re_rete_network_destroy_internal(engine->rete_network); engine->rete_network = NULL;
    old = engine->program; engine->program = program; re_program_destroy(old);
    return RE_STATUS_OK;
}

re_status_t re_engine_run(re_engine_t *engine, re_facts_t *facts, const re_run_options_t *options, const re_callbacks_t *callbacks) {
    size_t i; size_t firings = 0u; size_t agenda_activations = 0u; size_t *indices = NULL;
    unsigned char *fired_no_loop = NULL; char **activation_groups = NULL; size_t activation_group_count = 0u;
    char **locked_groups = NULL; size_t locked_group_count = 0u;
    re_limits_t limits; int explicit_limits; unsigned char *parallel_matches = NULL;
    re_status_t status;
    if (engine == NULL || facts == NULL) return RE_STATUS_INVALID_ARGUMENT;
    if (engine->running) return RE_STATUS_BUSY;
    engine->running = 1;
    if (facts->running) { engine->running = 0; return RE_STATUS_BUSY; }
    facts->running = 1;
    facts->read_allowed = 1;
    explicit_limits = options != NULL && options->limits != NULL;
    limits = explicit_limits ? *options->limits : engine->limits;
    if (limits.max_source_bytes == 0u) limits.max_source_bytes = engine->limits.max_source_bytes;
    if (limits.max_rules == 0u) limits.max_rules = engine->limits.max_rules;
    if (limits.max_facts == 0u) limits.max_facts = engine->limits.max_facts;
    if (limits.max_agenda_activations == 0u) limits.max_agenda_activations = engine->limits.max_agenda_activations;
    if (limits.max_firings == 0u) limits.max_firings = engine->limits.max_firings;
    if (engine->program == NULL) return finish_run(engine, facts, RE_STATUS_OK);
    if (engine->rete_network != NULL && (engine->rete_network->facts != facts || engine->rete_network->invalid)) {
        re_rete_network_destroy_internal(engine->rete_network);
        engine->rete_network = NULL;
    }
    if (engine->program->rule_count == 1u && engine->rete_network == NULL) {
        status = re_rete_network_create_rule(facts, &engine->program->rules[0], &engine->allocator.api, &engine->rete_network);
        if (status == RE_STATUS_BUSY && facts->rete_network != NULL) {
            engine->rete_network = facts->rete_network;
            status = RE_STATUS_OK;
        }
        if (status == RE_STATUS_OUT_OF_MEMORY || status == RE_STATUS_LIMIT) return finish_run(engine, facts, status);
        if (engine->rete_network != NULL) {
            engine->rete_network->program = engine->program;
            engine->rete_network->owner_engine = engine;
            engine->rete_network->engine_owned = 1;
        }
    }
    if (engine->program->rule_count != 0u) {
        indices = re_alloc(&engine->allocator, engine->program->rule_count * sizeof(*indices));
        if (indices == NULL) return finish_run(engine, facts, RE_STATUS_OUT_OF_MEMORY);
        fired_no_loop = re_alloc(&engine->allocator, engine->program->rule_count);
        if (fired_no_loop == NULL) { re_free(&engine->allocator, indices); return finish_run(engine, facts, RE_STATUS_OUT_OF_MEMORY); }
        memset(fired_no_loop, 0, engine->program->rule_count);
        activation_groups = re_alloc(&engine->allocator, engine->program->rule_count * sizeof(*activation_groups));
        locked_groups = re_alloc(&engine->allocator, engine->program->rule_count * sizeof(*locked_groups));
        if (activation_groups == NULL || locked_groups == NULL) {
            re_free(&engine->allocator, locked_groups); re_free(&engine->allocator, activation_groups);
            re_free(&engine->allocator, fired_no_loop); re_free(&engine->allocator, indices);
            return finish_run(engine, facts, RE_STATUS_OUT_OF_MEMORY);
        }
        for (i = 0u; i < engine->program->rule_count; ++i) indices[i] = i;
        sort_activation_indices(engine->program, indices);
    }
    if (engine->executor != NULL) {
        int pure = 1;
        for (i = 0u; i < engine->program->rule_count; ++i)
            if (!re_condition_is_pure(engine->program->rules[i].condition)) pure = 0;
        if (pure) {
            parallel_matches = re_alloc(&engine->allocator, engine->program->rule_count);
            if (parallel_matches == NULL) { free_agenda_state(&engine->allocator, indices, fired_no_loop, activation_groups, locked_groups); return finish_run(engine, facts, RE_STATUS_OUT_OF_MEMORY); }
            status = re_executor_match(engine->executor, engine, facts, engine->program, parallel_matches);
            if (status != RE_STATUS_OK) { re_free(&engine->allocator, parallel_matches); free_agenda_state(&engine->allocator, indices, fired_no_loop, activation_groups, locked_groups); return finish_run(engine, facts, status); }
        }
    }
    for (i = 0u; i < engine->program->rule_count; ++i) {
        re_rule_t *rule = &engine->program->rules[indices[i]]; re_rule_event_t event;
        if (engine->program->module_focus != NULL) { size_t focus_index, import_index; int visible = 0; for (focus_index = 0u; focus_index < engine->program->module_count; ++focus_index) if (engine->program->modules[focus_index].name_size == strlen(engine->program->module_focus) && memcmp(engine->program->modules[focus_index].name, engine->program->module_focus, engine->program->modules[focus_index].name_size) == 0) break; if (focus_index == engine->program->module_count) continue; if (rule->module_index == focus_index) visible = 1; for (import_index = 0u; !visible && import_index < engine->program->modules[focus_index].import_count; ++import_index) if (engine->program->modules[focus_index].imports[import_index] != NULL && engine->program->modules[focus_index].imports[import_index][0] == engine->program->modules[rule->module_index].name[0] && strcmp(engine->program->modules[focus_index].imports[import_index], engine->program->modules[rule->module_index].name) == 0 && engine->program->modules[rule->module_index].export_all) visible = 1; if (!visible) continue; }
        if (!re_rule_active(rule, engine->program->has_clock ? engine->program->clock_epoch : 0)) continue;
        if (engine->program->agenda_focus == NULL) {
            if (rule->agenda_group != NULL) continue;
        } else if (rule->agenda_group == NULL || strcmp(rule->agenda_group, engine->program->agenda_focus) != 0) continue;
        if (rule->no_loop && fired_no_loop[indices[i]]) continue;
        if (rule->lock_on_active && rule->agenda_group != NULL) {
            size_t group_index;
            for (group_index = 0u; group_index < locked_group_count; ++group_index)
                if (strcmp(locked_groups[group_index], rule->agenda_group) == 0) break;
            if (group_index != locked_group_count) continue;
        }
        if (rule->activation_group != NULL) {
            size_t group_index;
            for (group_index = 0u; group_index < activation_group_count; ++group_index)
                if (strcmp(activation_groups[group_index], rule->activation_group) == 0) break;
            if (group_index != activation_group_count) continue;
        }
        if (options != NULL && options->is_cancelled != NULL && options->is_cancelled(options->cancel_context) != 0) { free_agenda_state(&engine->allocator, indices, fired_no_loop, activation_groups, locked_groups); return finish_run(engine, facts, RE_STATUS_CANCELLED); }
         { int matched = 0; status = parallel_matches != NULL ? RE_STATUS_OK : re_ir_match_rule(engine, facts, engine->program->ir, indices[i], &matched); if (parallel_matches != NULL) matched = parallel_matches[indices[i]] != 0u; if (status == RE_STATUS_NOT_FOUND) continue; if (status != RE_STATUS_OK) { re_free(&engine->allocator, parallel_matches); free_agenda_state(&engine->allocator, indices, fired_no_loop, activation_groups, locked_groups); return finish_run(engine, facts, status); } if (!matched) continue; }
        if (limits.max_agenda_activations != 0u && agenda_activations >= limits.max_agenda_activations) { free_agenda_state(&engine->allocator, indices, fired_no_loop, activation_groups, locked_groups); return finish_run(engine, facts, RE_STATUS_LIMIT); }
        ++agenda_activations;
        event.rule_name.data = rule->name; event.rule_name.size = rule->name_size; event.salience = rule->salience;
        /* The IR matcher does not expose the selected RETE token, so keep
         * firing metadata local instead of associating a rule with token 0. */
        event.activation_sequence = (uint64_t)firings + 1u;
        if (rule->activation_group != NULL) {
            activation_groups[activation_group_count] = rule->activation_group;
            ++activation_group_count;
        }
        if (rule->no_loop) fired_no_loop[indices[i]] = 1u;
        if (rule->lock_on_active && rule->agenda_group != NULL) {
            locked_groups[locked_group_count] = rule->agenda_group;
            ++locked_group_count;
        }
        facts->mutation_allowed = 1;
        {
            re_fact_txn_t *transaction = NULL;
            size_t action_index;
            const re_ir_rule_t *ir_rule = &engine->program->ir->rules[indices[i]];
            status = re_facts_begin_for_run(facts, &transaction);
            if (status == RE_STATUS_OK) {
                for (action_index = 0u; action_index < ir_rule->action_count; ++action_index) {
                    re_value_t value;
                    const re_ir_action_t *action = &engine->program->ir->actions[ir_rule->first_action + action_index];
                    const re_ir_term_t *target = &engine->program->ir->terms[action->target];
                    status = re_ir_resolve_term(engine, facts, engine->program->ir, action->value, &value);
                    if (status != RE_STATUS_OK) break;
                    status = action->append ? re_facts_append_value(facts, (re_string_t){target->name, target->name_size}, &value) : re_facts_set(facts, (re_string_t){target->name, target->name_size}, &value);
                    if (status != RE_STATUS_OK) break;
                }
            }
            if (status == RE_STATUS_OK && callbacks != NULL && callbacks->action != NULL)
                status = callbacks->action(engine, facts, &event, callbacks->context);
            if (status == RE_STATUS_OK) status = re_facts_commit(transaction);
            else re_facts_rollback(transaction);
            if (status != RE_STATUS_OK) {
                free_agenda_state(&engine->allocator, indices, fired_no_loop, activation_groups, locked_groups);
                return finish_run(engine, facts, status);
            }
        }
        facts->mutation_allowed = 0;
        ++firings; if (limits.max_firings != 0u && firings >= limits.max_firings) { free_agenda_state(&engine->allocator, indices, fired_no_loop, activation_groups, locked_groups); return finish_run(engine, facts, RE_STATUS_LIMIT); }
    }
    re_free(&engine->allocator, parallel_matches);
    free_agenda_state(&engine->allocator, indices, fired_no_loop, activation_groups, locked_groups);
    return finish_run(engine, facts, RE_STATUS_OK);
}
