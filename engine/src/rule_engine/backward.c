#include "re_internal.h"
#include <stdlib.h>
#include <string.h>

static re_status_t invalidate(re_facts_t *facts, const re_fact_event_t *event, void *context) {
    re_query_t *query = (re_query_t *)context;
    (void)facts; (void)event; query->invalidated = 1; return RE_STATUS_OK;
}
static int trim(re_string_t *value) {
    while (value->size != 0u && value->data[0] == ' ') { ++value->data; --value->size; }
    while (value->size != 0u && value->data[value->size - 1u] == ' ') --value->size;
    return value->size != 0u;
}
static int equal_text(re_string_t left, re_string_t right) { return left.size == right.size && memcmp(left.data, right.data, left.size) == 0; }
static int parse_value(re_string_t input, re_value_t *out, int *variable) {
    char *end; size_t i; *variable = 0; if (!trim(&input)) return 0;
    if (input.size >= 2u && input.data[0] == '"' && input.data[input.size - 1u] == '"') { out->type = RE_VALUE_STRING; out->as.string.data = input.data + 1u; out->as.string.size = input.size - 2u; return 1; }
    if (equal_text(input, (re_string_t){"true", 4u}) || equal_text(input, (re_string_t){"false", 5u})) { out->type = RE_VALUE_BOOL; out->as.boolean = input.size == 4u; return 1; }
    for (i = 0u; i < input.size; ++i) if (input.data[i] < '0' || input.data[i] > '9') break;
    if (i == input.size && i != 0u) { out->type = RE_VALUE_INT64; out->as.int64_value = (int64_t)strtoll(input.data, &end, 10); return *end == '\0'; }
    *variable = 1; out->type = RE_VALUE_NONE; return 1;
}
static re_status_t make_proof(re_query_t *query, re_string_t variable, const re_value_t *value, re_string_t trace) {
    re_proof_t *proof; re_query_binding_impl_t *binding;
    proof = re_alloc(&query->allocator, sizeof(*proof)); if (proof == NULL) return RE_STATUS_OUT_OF_MEMORY;
    memset(proof, 0, sizeof(*proof)); proof->allocator = query->allocator;
    if (variable.size != 0u) {
        proof->bindings = re_alloc(&proof->allocator, sizeof(*proof->bindings));
        if (proof->bindings == NULL) { re_free(&proof->allocator, proof); return RE_STATUS_OUT_OF_MEMORY; }
        binding = &proof->bindings[0]; memset(binding, 0, sizeof(*binding));
        if (re_copy_string(&proof->allocator, variable, &binding->name) != RE_STATUS_OK) { re_proof_destroy(proof); return RE_STATUS_OUT_OF_MEMORY; }
        binding->name_size = variable.size; binding->value = *value;
        if (value->type == RE_VALUE_STRING) { if (re_copy_string(&proof->allocator, value->as.string, &binding->string_data) != RE_STATUS_OK) { re_proof_destroy(proof); return RE_STATUS_OUT_OF_MEMORY; } binding->value.as.string.data = binding->string_data; }
        proof->binding_count = 1u;
    }
    proof->trace_names = re_alloc(&proof->allocator, sizeof(*proof->trace_names));
    if (proof->trace_names == NULL) { re_proof_destroy(proof); return RE_STATUS_OUT_OF_MEMORY; }
    if (re_copy_string(&proof->allocator, trace, &proof->trace_names[0]) != RE_STATUS_OK) { re_proof_destroy(proof); return RE_STATUS_OUT_OF_MEMORY; }
    proof->trace_count = 1u;
    query->proofs = re_alloc(&query->allocator, sizeof(*query->proofs));
    if (query->proofs == NULL) { re_proof_destroy(proof); return RE_STATUS_OUT_OF_MEMORY; }
    query->proofs[0] = proof; query->proof_count = 1u; return RE_STATUS_OK;
}
static re_status_t condition_matches(re_engine_t *engine, re_facts_t *facts, const re_expr_t *expr, int *matched) {
    re_value_t left, right; re_status_t status;
    if (expr->kind == RE_EXPR_TRUE || expr->kind == RE_EXPR_FALSE) { *matched = expr->kind == RE_EXPR_TRUE; return RE_STATUS_OK; }
    if (expr->kind == RE_EXPR_NOT) { status = condition_matches(engine, facts, expr->first, matched); *matched = !*matched; return status; }
    if (expr->kind == RE_EXPR_AND || expr->kind == RE_EXPR_OR) { status = condition_matches(engine, facts, expr->first, matched); if (status != RE_STATUS_OK || (expr->kind == RE_EXPR_AND && !*matched) || (expr->kind == RE_EXPR_OR && *matched)) return status; return condition_matches(engine, facts, expr->second, matched); }
    status = re_operand_resolve(engine, facts, &expr->left, &left); if (status != RE_STATUS_OK) return status;
    status = re_operand_resolve(engine, facts, &expr->right, &right); if (status != RE_STATUS_OK) return status;
    *matched = re_value_compare(&left, &right, expr->compare); return RE_STATUS_OK;
}
re_status_t re_query_create_bounded(re_engine_t *engine, re_facts_t *facts, re_string_t goal, const re_query_options_t *options, re_query_t **out_query) {
    re_query_t *query; re_value_t expected, actual; re_string_t left, right; const char *equals; size_t index; int variable;
    if (engine == NULL || facts == NULL || out_query == NULL || goal.data == NULL || goal.size == 0u) return RE_STATUS_INVALID_ARGUMENT;
    *out_query = NULL; query = re_alloc(&engine->allocator, sizeof(*query)); if (query == NULL) return RE_STATUS_OUT_OF_MEMORY;
    memset(query, 0, sizeof(*query)); query->allocator = engine->allocator; query->engine = engine; query->facts = facts;
    if (options != NULL && options->struct_size < sizeof(*options)) { re_free(&query->allocator, query); return RE_STATUS_INVALID_ARGUMENT; }
    query->max_depth = options != NULL ? options->max_depth : 64u; query->max_solutions = options != NULL && options->max_solutions != 0u ? options->max_solutions : 1u;
    if (query->max_depth == 0u) { query->result = RE_QUERY_LIMIT; *out_query = query; return RE_STATUS_LIMIT; }
    query->result = RE_QUERY_UNKNOWN; equals = (const char *)memchr(goal.data, '=', goal.size);
    if (equals != NULL && equals + 1 < goal.data + goal.size && equals[1] == '=') {
        left = (re_string_t){goal.data, (size_t)(equals - goal.data)}; right = (re_string_t){equals + 2, (size_t)(goal.data + goal.size - equals - 2)};
        if (!trim(&left) || !parse_value(right, &expected, &variable)) { re_free(&query->allocator, query); return RE_STATUS_PARSE_ERROR; }
        if (re_facts_get(facts, left, &actual) != RE_STATUS_OK) query->result = RE_QUERY_UNKNOWN;
        else if (variable) { trim(&right); query->result = RE_QUERY_PROVED; if (make_proof(query, right, &actual, left) != RE_STATUS_OK) { re_free(&query->allocator, query); return RE_STATUS_OUT_OF_MEMORY; } }
        else query->result = re_value_compare(&actual, &expected, RE_COMPARE_EQ) ? RE_QUERY_PROVED : RE_QUERY_DISPROVED;
    } else {
        for (index = 0u; engine->program != NULL && index < engine->program->rule_count; ++index) { re_rule_t *rule = &engine->program->rules[index]; int matched = 0; re_status_t status;
            if (rule->name_size != goal.size || memcmp(rule->name, goal.data, goal.size) != 0) continue;
            status = condition_matches(engine, facts, rule->condition, &matched); if (status == RE_STATUS_NOT_FOUND) continue; if (status != RE_STATUS_OK) { re_free(&query->allocator, query); return status; } if (!matched) continue;
            query->result = RE_QUERY_PROVED; if (make_proof(query, (re_string_t){NULL, 0u}, &(re_value_t){RE_VALUE_NONE, {0}}, (re_string_t){rule->name, rule->name_size}) != RE_STATUS_OK) { re_free(&query->allocator, query); return RE_STATUS_OUT_OF_MEMORY; } break;
        }
    }
    if (re_facts_subscribe(facts, invalidate, query, &query->subscription) != RE_STATUS_OK) { re_query_destroy(query); return RE_STATUS_OUT_OF_MEMORY; }
    *out_query = query; return RE_STATUS_OK;
}
