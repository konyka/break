#include "ir.h"
static int index_ok(size_t index, size_t count) { return index < count; }
re_status_t re_ir_validate(const re_ir_program_t *ir) {
    size_t i;
    if (ir == NULL || ir->span_count != ir->rule_count ||
        (ir->rule_count != 0u && ir->rules == NULL) ||
        (ir->expr_count != 0u && ir->exprs == NULL) ||
        (ir->term_count != 0u && ir->terms == NULL) ||
        (ir->action_count != 0u && ir->actions == NULL) ||
        (ir->span_count != 0u && ir->spans == NULL)) return RE_STATUS_INVALID_ARGUMENT;
    for (i = 0u; i < ir->rule_count; ++i) {
        const re_ir_rule_t *rule = &ir->rules[i];
        if (!index_ok(rule->name, ir->term_count) || ir->terms[rule->name].name == NULL ||
            !index_ok(rule->condition, ir->expr_count) || rule->first_action > ir->action_count || rule->action_count > ir->action_count - rule->first_action || (rule->module != SIZE_MAX && !index_ok(rule->module, ir->module_count))) return RE_STATUS_INVALID_ARGUMENT;
    }
    for (i = 0u; i < ir->expr_count; ++i) {
        const re_ir_expr_t *expr = &ir->exprs[i];
        if (expr->kind < RE_EXPR_COMPARE || expr->kind > RE_EXPR_FALSE ||
            (expr->kind == RE_EXPR_COMPARE && (expr->compare < RE_COMPARE_TRUE || expr->compare > RE_COMPARE_IN))) return RE_STATUS_INVALID_ARGUMENT;
        if (expr->kind == RE_EXPR_COMPARE && (!index_ok(expr->left, ir->term_count) || !index_ok(expr->right, ir->term_count))) return RE_STATUS_INVALID_ARGUMENT;
        if ((expr->kind == RE_EXPR_NOT || expr->kind == RE_EXPR_AND || expr->kind == RE_EXPR_OR) && !index_ok(expr->first, ir->expr_count)) return RE_STATUS_INVALID_ARGUMENT;
        if ((expr->kind == RE_EXPR_AND || expr->kind == RE_EXPR_OR) && !index_ok(expr->second, ir->expr_count)) return RE_STATUS_INVALID_ARGUMENT;
    }
    for (i = 0u; i < ir->term_count; ++i) {
        const re_ir_term_t *term = &ir->terms[i];
        size_t j;
        if (term->kind < RE_IR_TERM_NONE || term->kind > RE_IR_TERM_ARRAY) return RE_STATUS_INVALID_ARGUMENT;
        if (term->kind == RE_IR_TERM_NONE ||
            ((term->kind == RE_IR_TERM_FACT || term->kind == RE_IR_TERM_FUNCTION || term->kind == RE_IR_TERM_GOAL) &&
            term->name == NULL)) return RE_STATUS_INVALID_ARGUMENT;
        if ((term->kind == RE_IR_TERM_BOOL && term->value.type != RE_VALUE_BOOL) ||
            (term->kind == RE_IR_TERM_INT64 && term->value.type != RE_VALUE_INT64) ||
            (term->kind == RE_IR_TERM_DOUBLE && term->value.type != RE_VALUE_DOUBLE) ||
            (term->kind == RE_IR_TERM_STRING && term->value.type != RE_VALUE_STRING) ||
            (term->kind == RE_IR_TERM_ARITHMETIC && (term->arithmetic_operator < RE_ARITH_ADD || term->arithmetic_operator > RE_ARITH_DIVIDE))) return RE_STATUS_INVALID_ARGUMENT;
        if (term->kind == RE_IR_TERM_ARITHMETIC && term->argument_count != 2u) return RE_STATUS_INVALID_ARGUMENT;
        if (term->kind == RE_IR_TERM_ARRAY && term->argument_count == 0u) return RE_STATUS_INVALID_ARGUMENT;
        if (term->argument_count != 0u && term->argument_indices == NULL) return RE_STATUS_INVALID_ARGUMENT;
        for (j = 0u; j < term->argument_count; ++j)
            if (!index_ok(term->argument_indices[j], ir->term_count) ||
                (term->kind == RE_IR_TERM_ARRAY &&
                 (ir->terms[term->argument_indices[j]].kind != RE_IR_TERM_BOOL &&
                  ir->terms[term->argument_indices[j]].kind != RE_IR_TERM_INT64 &&
                  ir->terms[term->argument_indices[j]].kind != RE_IR_TERM_DOUBLE &&
                  ir->terms[term->argument_indices[j]].kind != RE_IR_TERM_STRING))) return RE_STATUS_INVALID_ARGUMENT;
    }
    for (i = 0u; i < ir->action_count; ++i)
        if (!index_ok(ir->actions[i].target, ir->term_count) ||
            ir->terms[ir->actions[i].target].kind != RE_IR_TERM_FACT ||
            !index_ok(ir->actions[i].value, ir->term_count)) return RE_STATUS_INVALID_ARGUMENT;
    for (i = 0u; i < ir->expr_count; ++i)
        if (ir->exprs[i].kind == RE_EXPR_COMPARE && ir->exprs[i].compare == RE_COMPARE_IN &&
            ir->terms[ir->exprs[i].right].kind != RE_IR_TERM_ARRAY &&
            ir->terms[ir->exprs[i].right].kind != RE_IR_TERM_FACT) return RE_STATUS_INVALID_ARGUMENT;
    return RE_STATUS_OK;
}
