#include "ir.h"
#include <limits.h>
#include <math.h>
#include <string.h>

typedef enum re_eval_frame_kind_t { RE_FRAME_TERM, RE_FRAME_EXPR } re_eval_frame_kind_t;
typedef struct re_eval_frame_t {
    re_eval_frame_kind_t kind;
    size_t index;
    unsigned stage;
    size_t parent;
    unsigned slot;
    re_value_t left;
    re_value_t right;
    re_value_t result;
    int matched;
    size_t position;
    size_t rule_position;
    int saw_limit;
    int pushed_rule;
    re_function_t *function;
    re_value_t *arguments;
} re_eval_frame_t;
typedef struct re_ir_eval_state_t {
    size_t *rules;
    size_t rule_count;
    size_t rule_capacity;
    size_t steps;
    size_t step_limit;
    re_eval_frame_t *frames;
    size_t frame_count;
    size_t frame_capacity;
} re_ir_eval_state_t;

static re_status_t eval_step(re_ir_eval_state_t *state) {
    if (state->steps == state->step_limit) return RE_STATUS_LIMIT;
    ++state->steps;
    return RE_STATUS_OK;
}
static int active_rule(const re_ir_eval_state_t *state, size_t index) {
    size_t i;
    for (i = 0u; i < state->rule_count; ++i) if (state->rules[i] == index) return 1;
    return 0;
}
static re_status_t push_rule(const re_engine_t *engine, re_ir_eval_state_t *state, size_t index) {
    size_t capacity;
    size_t *rules;
    if (active_rule(state, index)) return RE_STATUS_LIMIT;
    if (state->rule_count == state->rule_capacity) {
        capacity = state->rule_capacity == 0u ? 8u : state->rule_capacity * 2u;
        if (capacity < state->rule_capacity || capacity > SIZE_MAX / sizeof(*rules)) return RE_STATUS_LIMIT;
        rules = re_alloc(&engine->allocator, capacity * sizeof(*rules));
        if (rules == NULL) return RE_STATUS_OUT_OF_MEMORY;
        if (state->rules != NULL) {
            memcpy(rules, state->rules, state->rule_count * sizeof(*rules));
            re_free(&engine->allocator, state->rules);
        }
        state->rules = rules;
        state->rule_capacity = capacity;
    }
    state->rules[state->rule_count++] = index;
    return RE_STATUS_OK;
}
static void pop_rule(re_ir_eval_state_t *state) { --state->rule_count; }

static re_status_t frame_push(const re_engine_t *engine, re_ir_eval_state_t *state,
                              re_eval_frame_kind_t kind, size_t index, size_t parent,
                              unsigned slot) {
    size_t capacity;
    re_eval_frame_t *frames;
    if (state->frame_count == state->frame_capacity) {
        capacity = state->frame_capacity == 0u ? 16u : state->frame_capacity * 2u;
        if (capacity < state->frame_capacity || capacity > SIZE_MAX / sizeof(*frames)) return RE_STATUS_LIMIT;
        frames = re_realloc(&engine->allocator, state->frames, capacity * sizeof(*frames));
        if (frames == NULL) return RE_STATUS_OUT_OF_MEMORY;
        state->frames = frames;
        state->frame_capacity = capacity;
    }
    memset(&state->frames[state->frame_count], 0, sizeof(state->frames[0]));
    state->frames[state->frame_count].kind = kind;
    state->frames[state->frame_count].index = index;
    state->frames[state->frame_count].parent = parent;
    state->frames[state->frame_count].slot = slot;
    ++state->frame_count;
    return RE_STATUS_OK;
}
static void frame_cleanup(const re_engine_t *engine, re_ir_eval_state_t *state, re_eval_frame_t *frame) {
    if (frame->pushed_rule) pop_rule(state);
    re_free(&engine->allocator, frame->arguments);
    frame->arguments = NULL;
}

static re_status_t arithmetic(const re_ir_term_t *term, const re_value_t *left,
                              const re_value_t *right, re_value_t *value) {
    int use_double = left->type == RE_VALUE_DOUBLE || right->type == RE_VALUE_DOUBLE;
    if ((left->type != RE_VALUE_INT64 && left->type != RE_VALUE_DOUBLE) ||
        (right->type != RE_VALUE_INT64 && right->type != RE_VALUE_DOUBLE)) return RE_STATUS_INVALID_ARGUMENT;
    if (!use_double && term->arithmetic_operator == RE_ARITH_DIVIDE) {
        if (right->as.int64_value == 0) return RE_STATUS_ERROR;
        if (left->as.int64_value == INT64_MIN && right->as.int64_value == -1) return RE_STATUS_LIMIT;
        value->type = RE_VALUE_INT64;
        value->as.int64_value = left->as.int64_value / right->as.int64_value;
        return RE_STATUS_OK;
    }
    if (!use_double) {
        int64_t l = left->as.int64_value;
        int64_t r = right->as.int64_value;
        if ((term->arithmetic_operator == RE_ARITH_ADD && ((r > 0 && l > INT64_MAX - r) || (r < 0 && l < INT64_MIN - r))) ||
            (term->arithmetic_operator == RE_ARITH_SUBTRACT && ((r < 0 && l > INT64_MAX + r) || (r > 0 && l < INT64_MIN + r))) ||
            (term->arithmetic_operator == RE_ARITH_MULTIPLY && r != 0 &&
             ((r == -1 && l == INT64_MIN) ||
              (r > 0 && (l > INT64_MAX / r || l < INT64_MIN / r)) ||
              (r < 0 && r != -1 && (l < INT64_MAX / r || l > INT64_MIN / r))))) return RE_STATUS_LIMIT;
        value->type = RE_VALUE_INT64;
        value->as.int64_value = term->arithmetic_operator == RE_ARITH_ADD ? l + r :
            term->arithmetic_operator == RE_ARITH_SUBTRACT ? l - r : l * r;
        return RE_STATUS_OK;
    }
    {
        double l = left->type == RE_VALUE_DOUBLE ? left->as.double_value : (double)left->as.int64_value;
        double r = right->type == RE_VALUE_DOUBLE ? right->as.double_value : (double)right->as.int64_value;
        double result = term->arithmetic_operator == RE_ARITH_ADD ? l + r :
            term->arithmetic_operator == RE_ARITH_SUBTRACT ? l - r :
            term->arithmetic_operator == RE_ARITH_MULTIPLY ? l * r : l / r;
        if (!isfinite(result)) return RE_STATUS_ERROR;
        value->type = RE_VALUE_DOUBLE;
        value->as.double_value = result;
    }
    return RE_STATUS_OK;
}

static re_status_t evaluate_iterative(const re_engine_t *engine, re_facts_t *facts,
                                      const re_ir_program_t *ir, re_eval_frame_kind_t kind,
                                      size_t index, int *matched, re_value_t *value,
                                      re_ir_eval_state_t *state) {
    re_status_t status = frame_push(engine, state, kind, index, SIZE_MAX, 0u);
    if (status != RE_STATUS_OK) return status;
    while (state->frame_count != 0u) {
        re_eval_frame_t *frame = &state->frames[state->frame_count - 1u];
        const re_ir_term_t *term;
        const re_ir_expr_t *expr;
        status = eval_step(state);
        if (status != RE_STATUS_OK) break;
        if (frame->kind == RE_FRAME_TERM) {
            term = &ir->terms[frame->index];
            if (frame->stage == 0u) {
                if (term->kind == RE_IR_TERM_BOOL || term->kind == RE_IR_TERM_INT64 || term->kind == RE_IR_TERM_DOUBLE || term->kind == RE_IR_TERM_STRING) {
                    frame->result = term->value; frame->stage = 99u;
                } else if (term->kind == RE_IR_TERM_FACT) {
                    status = re_facts_get_path(facts, (re_string_t){term->name, term->name_size}, &frame->result); frame->stage = 99u;
                } else if (term->kind == RE_IR_TERM_ARITHMETIC) {
                    if (term->argument_count != 2u || term->argument_indices == NULL) status = RE_STATUS_INVALID_ARGUMENT;
                    else { frame->stage = 1u; status = frame_push(engine, state, RE_FRAME_TERM, term->argument_indices[0], state->frame_count - 1u, 0u); }
                } else if (term->kind == RE_IR_TERM_GOAL) {
                    frame->stage = 10u;
                } else if (term->kind == RE_IR_TERM_FUNCTION) {
                    for (frame->function = engine->functions; frame->function != NULL; frame->function = frame->function->next)
                        if (!frame->function->unregistered && frame->function->name_size == term->name_size && memcmp(frame->function->name, term->name, term->name_size) == 0) break;
                    if (frame->function == NULL) status = RE_STATUS_NOT_FOUND;
                    else {
                        frame->arguments = term->argument_count == 0u ? NULL :
                            term->argument_count > SIZE_MAX / sizeof(*frame->arguments) ? NULL :
                            re_alloc(&engine->allocator, term->argument_count * sizeof(*frame->arguments));
                        if (term->argument_count != 0u && frame->arguments == NULL) status = RE_STATUS_OUT_OF_MEMORY;
                        else if (term->argument_count == 0u) frame->stage = 20u;
                        else { frame->stage = 21u; status = frame_push(engine, state, RE_FRAME_TERM, term->argument_indices[0], state->frame_count - 1u, 0u); }
                    }
                } else status = RE_STATUS_NOT_SUPPORTED;
            } else if (frame->stage == 1u) {
                frame->stage = 2u; status = frame_push(engine, state, RE_FRAME_TERM, term->argument_indices[1], state->frame_count - 1u, 1u);
            } else if (frame->stage == 2u) {
                status = arithmetic(term, &frame->left, &frame->right, &frame->result); frame->stage = 99u;
            } else if (frame->stage == 21u) {
                frame->arguments[frame->position++] = frame->left;
                if (frame->position < term->argument_count) status = frame_push(engine, state, RE_FRAME_TERM, term->argument_indices[frame->position], state->frame_count - 1u, 0u);
                else frame->stage = 20u;
            } else if (frame->stage == 20u) {
                frame->function->active_calls++; status = frame->function->call((re_engine_t *)engine, facts, frame->arguments, term->argument_count, &frame->result, frame->function->context); frame->function->active_calls--; frame->stage = 99u;
            } else if (frame->stage == 10u) {
                int found = 0;
                while (frame->rule_position < ir->rule_count) {
                    size_t rule_index = frame->rule_position++;
                    const re_ir_rule_t *rule = &ir->rules[rule_index];
                    const re_ir_term_t *name = &ir->terms[rule->name];
                    if (name->name_size != term->name_size || memcmp(name->name, term->name, term->name_size) != 0) continue;
                    status = push_rule(engine, state, rule_index);
                    if (status == RE_STATUS_LIMIT) { frame->saw_limit = 1; status = RE_STATUS_OK; continue; }
                    if (status != RE_STATUS_OK) break;
                    frame->pushed_rule = 1; frame->stage = 11u;
                    status = frame_push(engine, state, RE_FRAME_EXPR, rule->condition, state->frame_count - 1u, 0u);
                    found = 1; break;
                }
                if (!found && status == RE_STATUS_OK) { if (frame->saw_limit) status = RE_STATUS_LIMIT; else { frame->result.type = RE_VALUE_BOOL; frame->result.as.boolean = 0; frame->stage = 99u; } }
            } else if (frame->stage == 11u) {
                pop_rule(state); frame->pushed_rule = 0;
                if (frame->matched) { frame->result.type = RE_VALUE_BOOL; frame->result.as.boolean = 1; frame->stage = 99u; }
                else { frame->stage = 10u; }
            }
        } else {
            expr = &ir->exprs[frame->index];
            if (frame->stage == 0u) {
                if (expr->kind == RE_EXPR_TRUE || expr->kind == RE_EXPR_FALSE) { frame->matched = expr->kind == RE_EXPR_TRUE; frame->stage = 99u; }
                else if (expr->kind == RE_EXPR_NOT || expr->kind == RE_EXPR_AND || expr->kind == RE_EXPR_OR) { frame->stage = 1u; status = frame_push(engine, state, RE_FRAME_EXPR, expr->first, state->frame_count - 1u, 0u); }
                else if (expr->kind == RE_EXPR_COMPARE) { frame->stage = 2u; status = frame_push(engine, state, RE_FRAME_TERM, expr->left, state->frame_count - 1u, 0u); }
                else status = RE_STATUS_NOT_SUPPORTED;
            } else if (frame->stage == 1u) {
                if (expr->kind == RE_EXPR_NOT) { frame->matched = !frame->matched; frame->stage = 99u; }
                else if ((expr->kind == RE_EXPR_AND && !frame->matched) || (expr->kind == RE_EXPR_OR && frame->matched)) frame->stage = 99u;
                else { frame->stage = 3u; status = frame_push(engine, state, RE_FRAME_EXPR, expr->second, state->frame_count - 1u, 1u); }
            } else if (frame->stage == 2u) {
                if (expr->compare == RE_COMPARE_IN && ir->terms[expr->right].kind == RE_IR_TERM_ARRAY) { frame->position = 0u; frame->matched = 0; frame->stage = 4u; }
                else if (expr->compare == RE_COMPARE_IN) { frame->stage = 99u; status = re_facts_contains_value(facts, (re_string_t){ir->terms[expr->right].name, ir->terms[expr->right].name_size}, &frame->left, &frame->matched); }
                else { frame->stage = 5u; status = frame_push(engine, state, RE_FRAME_TERM, expr->right, state->frame_count - 1u, 1u); }
            } else if (frame->stage == 3u) { frame->matched = re_value_compare(&frame->left, &frame->right, expr->compare); frame->stage = 99u; }
            else if (frame->stage == 5u) { frame->matched = re_value_compare(&frame->left, &frame->right, expr->compare); frame->stage = 99u; }
            else if (frame->stage == 4u) { const re_ir_term_t *array = &ir->terms[expr->right]; if (frame->position == array->argument_count) frame->stage = 99u; else { frame->stage = 6u; status = frame_push(engine, state, RE_FRAME_TERM, array->argument_indices[frame->position], state->frame_count - 1u, 1u); } }
            else if (frame->stage == 6u) { if (re_value_equal_typed(&frame->left, &frame->right)) frame->matched = 1; ++frame->position; frame->stage = frame->matched ? 99u : 4u; }
        }
        if (status != RE_STATUS_OK) break;
        if (state->frame_count != 0u && state->frames[state->frame_count - 1u].stage == 99u) {
            re_eval_frame_t completed = state->frames[state->frame_count - 1u];
            frame_cleanup(engine, state, &state->frames[state->frame_count - 1u]);
            --state->frame_count;
            if (completed.parent == SIZE_MAX) { if (matched != NULL) *matched = completed.matched; if (value != NULL) *value = completed.result; }
            else if (completed.slot == 0u) { state->frames[completed.parent].left = completed.result; state->frames[completed.parent].matched = completed.matched; }
            else { state->frames[completed.parent].right = completed.result; state->frames[completed.parent].matched = completed.matched; }
        }
    }
    while (state->frame_count != 0u) { frame_cleanup(engine, state, &state->frames[state->frame_count - 1u]); --state->frame_count; }
    return status;
}

static void state_destroy(const re_engine_t *engine, re_ir_eval_state_t *state) {
    re_free(&engine->allocator, state->frames); re_free(&engine->allocator, state->rules);
}
re_status_t re_ir_match_rule(const re_engine_t *engine, re_facts_t *facts, const re_ir_program_t *ir, size_t rule_index, int *matched) {
    re_ir_eval_state_t state; re_status_t status;
    if (engine == NULL || facts == NULL || ir == NULL || rule_index >= ir->rule_count || matched == NULL) return RE_STATUS_INVALID_ARGUMENT;
    memset(&state, 0, sizeof(state));
    state.step_limit = ir->expr_count > SIZE_MAX - ir->term_count ? SIZE_MAX : ir->expr_count + ir->term_count;
    state.step_limit = state.step_limit > (SIZE_MAX - 1u) / 1024u ? SIZE_MAX : state.step_limit * 1024u + 1u;
    status = push_rule(engine, &state, rule_index);
    if (status == RE_STATUS_OK) { status = evaluate_iterative(engine, facts, ir, RE_FRAME_EXPR, ir->rules[rule_index].condition, matched, NULL, &state); pop_rule(&state); }
    state_destroy(engine, &state); return status;
}
re_status_t re_ir_resolve_term(re_engine_t *engine, re_facts_t *facts, const re_ir_program_t *ir, size_t term_index, re_value_t *value) {
    re_ir_eval_state_t state; re_status_t status;
    if (engine == NULL || facts == NULL || ir == NULL || value == NULL || term_index >= ir->term_count) return RE_STATUS_INVALID_ARGUMENT;
    memset(&state, 0, sizeof(state));
    state.step_limit = ir->expr_count > SIZE_MAX - ir->term_count ? SIZE_MAX : ir->expr_count + ir->term_count;
    state.step_limit = state.step_limit > (SIZE_MAX - 1u) / 1024u ? SIZE_MAX : state.step_limit * 1024u + 1u;
    status = evaluate_iterative(engine, facts, ir, RE_FRAME_TERM, term_index, NULL, value, &state); state_destroy(engine, &state); return status;
}
