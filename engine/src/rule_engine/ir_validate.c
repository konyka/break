#include "ir.h"
static int index_ok(size_t index, size_t count) { return index < count; }
re_status_t re_ir_validate(const re_ir_program_t *ir) {
    size_t i;
    if (ir == NULL || ir->span_count != ir->rule_count ||
        (ir->rule_count != 0u && ir->rules == NULL) ||
        (ir->expr_count != 0u && ir->exprs == NULL) ||
        (ir->term_count != 0u && ir->terms == NULL) ||
        (ir->action_count != 0u && ir->actions == NULL) ||
        (ir->span_count != 0u && ir->spans == NULL) ||
        (ir->deffacts_set_count != 0u && ir->deffacts_sets == NULL) ||
        (ir->deffacts_entry_count != 0u && ir->deffacts_entries == NULL) ||
        (ir->query_count != 0u && ir->queries == NULL) ||
        (ir->query_action_count != 0u && ir->query_actions == NULL)) return RE_STATUS_INVALID_ARGUMENT;
    for (i = 0u; i < ir->rule_count; ++i) {
        const re_ir_rule_t *rule = &ir->rules[i];
        if (!index_ok(rule->name, ir->term_count) || ir->terms[rule->name].name == NULL ||
            !index_ok(rule->condition, ir->expr_count) || rule->first_action > ir->action_count || rule->action_count > ir->action_count - rule->first_action || (rule->module != SIZE_MAX && !index_ok(rule->module, ir->module_count))) return RE_STATUS_INVALID_ARGUMENT;
    }
    for (i = 0u; i < ir->expr_count; ++i) {
        const re_ir_expr_t *expr = &ir->exprs[i];
        if (expr->kind < RE_EXPR_COMPARE || expr->kind > RE_EXPR_TYPED ||
            (expr->kind == RE_EXPR_COMPARE && (expr->compare < RE_COMPARE_TRUE || expr->compare > RE_COMPARE_NOT_CONTAINS))) return RE_STATUS_INVALID_ARGUMENT;
        if (expr->multifield < RE_MULTIFIELD_NONE || expr->multifield > RE_MULTIFIELD_COLLECT ||
            (expr->kind != RE_EXPR_MULTIFIELD && expr->multifield != RE_MULTIFIELD_NONE) ||
            (expr->kind == RE_EXPR_MULTIFIELD && expr->multifield == RE_MULTIFIELD_NONE)) return RE_STATUS_INVALID_ARGUMENT;
        if (expr->kind == RE_EXPR_MULTIFIELD) {
            /* A5 multifield predicate: the array path must be a fact term;
             * count additionally carries an eq/relational operator and a
             * numeric literal right term, the bare predicates none. */
            if (!index_ok(expr->left, ir->term_count) ||
                ir->terms[expr->left].kind != RE_IR_TERM_FACT) return RE_STATUS_INVALID_ARGUMENT;
            if (expr->multifield == RE_MULTIFIELD_COUNT) {
                if (expr->compare < RE_COMPARE_EQ || expr->compare > RE_COMPARE_LE ||
                    !index_ok(expr->right, ir->term_count) ||
                    (ir->terms[expr->right].kind != RE_IR_TERM_INT64 &&
                     ir->terms[expr->right].kind != RE_IR_TERM_DOUBLE)) return RE_STATUS_INVALID_ARGUMENT;
            } else if (expr->right != SIZE_MAX) return RE_STATUS_INVALID_ARGUMENT;
        }
        if (expr->nested != 0 &&
            (expr->nested != 1 || (expr->kind != RE_EXPR_EXISTS && expr->kind != RE_EXPR_FORALL)))
            return RE_STATUS_INVALID_ARGUMENT;
        if (expr->nested != 0) {
            /* Parenthesized quantifier form: the operand is the inner
             * expression at `first`; left/right carry no terms. */
            if (!index_ok(expr->first, ir->expr_count)) return RE_STATUS_INVALID_ARGUMENT;
            continue;
        }
        if (expr->kind == RE_EXPR_ACCUMULATE) {
            /* A6: the payload must be complete and the fold a known GRL
             * accumulate function (RE_ACCUM_COUNT..RE_ACCUM_MAX; FIRST/LAST
             * exist only in the query aggregation API). The node carries no
             * term or expression children. */
            if (expr->accumulate_type == NULL || expr->accumulate_func_name == NULL ||
                expr->accumulate_func < RE_ACCUM_COUNT || expr->accumulate_func > RE_ACCUM_MAX ||
                (expr->accumulate_condition_count != 0u && expr->accumulate_conditions == NULL))
                return RE_STATUS_INVALID_ARGUMENT;
            continue;
        }
        if (expr->kind == RE_EXPR_TEST) {
            /* A9 test(f(args)): the operand is the function-call term; right
             * keeps the SIZE_MAX sentinel. */
            if (!index_ok(expr->left, ir->term_count) ||
                ir->terms[expr->left].kind != RE_IR_TERM_FUNCTION ||
                expr->right != SIZE_MAX) return RE_STATUS_INVALID_ARGUMENT;
            continue;
        }
        if (expr->kind == RE_EXPR_TYPED) {
            /* A9 typed form: the declared type name payload plus the inner
             * condition at `first`; left/right stay zeroed. */
            if (expr->typed_type == NULL || expr->typed_type_size == 0u ||
                !index_ok(expr->first, ir->expr_count)) return RE_STATUS_INVALID_ARGUMENT;
            continue;
        }
        if ((expr->kind == RE_EXPR_COMPARE || expr->kind == RE_EXPR_EXISTS || expr->kind == RE_EXPR_FORALL) &&
            (!index_ok(expr->left, ir->term_count) || !index_ok(expr->right, ir->term_count))) return RE_STATUS_INVALID_ARGUMENT;
        if (expr->kind == RE_EXPR_EXISTS &&
            (ir->terms[expr->left].kind != RE_IR_TERM_FACT ||
             (ir->terms[expr->right].kind != RE_IR_TERM_BOOL &&
              ir->terms[expr->right].kind != RE_IR_TERM_INT64 &&
              ir->terms[expr->right].kind != RE_IR_TERM_DOUBLE &&
             ir->terms[expr->right].kind != RE_IR_TERM_STRING))) return RE_STATUS_INVALID_ARGUMENT;
        if (expr->kind == RE_EXPR_FORALL &&
            (ir->terms[expr->left].kind != RE_IR_TERM_FACT ||
             (ir->terms[expr->right].kind != RE_IR_TERM_BOOL &&
              ir->terms[expr->right].kind != RE_IR_TERM_INT64 &&
              ir->terms[expr->right].kind != RE_IR_TERM_DOUBLE &&
              ir->terms[expr->right].kind != RE_IR_TERM_STRING))) return RE_STATUS_INVALID_ARGUMENT;
        if ((expr->kind == RE_EXPR_NOT || expr->kind == RE_EXPR_AND || expr->kind == RE_EXPR_OR) && !index_ok(expr->first, ir->expr_count)) return RE_STATUS_INVALID_ARGUMENT;
        if ((expr->kind == RE_EXPR_AND || expr->kind == RE_EXPR_OR) && !index_ok(expr->second, ir->expr_count)) return RE_STATUS_INVALID_ARGUMENT;
    }
    for (i = 0u; i < ir->term_count; ++i) {
        const re_ir_term_t *term = &ir->terms[i];
        size_t j;
        if (term->kind < RE_IR_TERM_NONE || term->kind > RE_IR_TERM_NULL) return RE_STATUS_INVALID_ARGUMENT;
        if (term->kind == RE_IR_TERM_NONE ||
            ((term->kind == RE_IR_TERM_FACT || term->kind == RE_IR_TERM_FUNCTION || term->kind == RE_IR_TERM_GOAL ||
              term->kind == RE_IR_TERM_METHOD_CALL) &&
            term->name == NULL)) return RE_STATUS_INVALID_ARGUMENT;
        if ((term->kind == RE_IR_TERM_BOOL && term->value.type != RE_VALUE_BOOL) ||
            (term->kind == RE_IR_TERM_INT64 && term->value.type != RE_VALUE_INT64) ||
            (term->kind == RE_IR_TERM_DOUBLE && term->value.type != RE_VALUE_DOUBLE) ||
            (term->kind == RE_IR_TERM_STRING && term->value.type != RE_VALUE_STRING) ||
            (term->kind == RE_IR_TERM_NULL && term->value.type != RE_VALUE_NULL) ||
            (term->kind == RE_IR_TERM_ARITHMETIC && (term->arithmetic_operator < RE_ARITH_ADD || term->arithmetic_operator > RE_ARITH_MODULO))) return RE_STATUS_INVALID_ARGUMENT;
        if (term->kind == RE_IR_TERM_ARITHMETIC && term->argument_count != 2u) return RE_STATUS_INVALID_ARGUMENT;
        if (term->kind == RE_IR_TERM_ARRAY && term->argument_count == 0u) return RE_STATUS_INVALID_ARGUMENT;
        if (term->kind == RE_IR_TERM_METHOD_CALL && term->argument_count > 8u) return RE_STATUS_INVALID_ARGUMENT;
        if (term->argument_count != 0u && term->argument_indices == NULL) return RE_STATUS_INVALID_ARGUMENT;
        for (j = 0u; j < term->argument_count; ++j)
            if (!index_ok(term->argument_indices[j], ir->term_count) ||
                (term->kind == RE_IR_TERM_ARRAY &&
                 (ir->terms[term->argument_indices[j]].kind != RE_IR_TERM_BOOL &&
                  ir->terms[term->argument_indices[j]].kind != RE_IR_TERM_INT64 &&
                  ir->terms[term->argument_indices[j]].kind != RE_IR_TERM_DOUBLE &&
                  ir->terms[term->argument_indices[j]].kind != RE_IR_TERM_STRING))) return RE_STATUS_INVALID_ARGUMENT;
    }
    for (i = 0u; i < ir->action_count; ++i) {
        const re_ir_action_t *action = &ir->actions[i];
        if (action->kind < RE_IR_ACTION_ASSIGN || action->kind > RE_IR_ACTION_BUILTIN_CALL ||
            !index_ok(action->target, ir->term_count)) return RE_STATUS_INVALID_ARGUMENT;
        if (action->kind == RE_IR_ACTION_BUILTIN_CALL) {
            /* A8: the target is the FUNCTION term carrying name and args; the
             * name must be one of the six whitelisted action builtins. */
            const re_ir_term_t *call = &ir->terms[action->target];
            if (action->value != SIZE_MAX || call->kind != RE_IR_TERM_FUNCTION ||
                call->name == NULL || !re_builtin_action_is(call->name, call->name_size))
                return RE_STATUS_INVALID_ARGUMENT;
            continue;
        }
        if (ir->terms[action->target].kind != RE_IR_TERM_FACT ||
            !index_ok(action->value, ir->term_count)) return RE_STATUS_INVALID_ARGUMENT;
        if (action->kind == RE_IR_ACTION_METHOD_CALL &&
            (action->method_name == NULL || action->method_name_size == 0u ||
             ir->terms[action->value].kind != RE_IR_TERM_METHOD_CALL))
            return RE_STATUS_INVALID_ARGUMENT;
    }
    for (i = 0u; i < ir->expr_count; ++i)
        if (ir->exprs[i].kind == RE_EXPR_COMPARE && ir->exprs[i].compare == RE_COMPARE_IN &&
            ir->terms[ir->exprs[i].right].kind != RE_IR_TERM_ARRAY &&
            ir->terms[ir->exprs[i].right].kind != RE_IR_TERM_FACT) return RE_STATUS_INVALID_ARGUMENT;
    for (i = 0u; i < ir->deffacts_set_count; ++i) {
        const re_ir_deffacts_set_t *set = &ir->deffacts_sets[i];
        if (!index_ok(set->name, ir->term_count) || ir->terms[set->name].name == NULL ||
            set->first_entry > ir->deffacts_entry_count ||
            set->entry_count > ir->deffacts_entry_count - set->first_entry) return RE_STATUS_INVALID_ARGUMENT;
    }
    for (i = 0u; i < ir->deffacts_entry_count; ++i) {
        const re_ir_deffacts_entry_t *entry = &ir->deffacts_entries[i];
        const re_ir_term_t *path;
        const re_ir_term_t *value;
        if (!index_ok(entry->path, ir->term_count) || !index_ok(entry->value, ir->term_count)) return RE_STATUS_INVALID_ARGUMENT;
        path = &ir->terms[entry->path];
        value = &ir->terms[entry->value];
        if (path->kind != RE_IR_TERM_FACT || path->name == NULL || path->name_size == 0u) return RE_STATUS_INVALID_ARGUMENT;
        if (value->kind != RE_IR_TERM_BOOL && value->kind != RE_IR_TERM_INT64 &&
            value->kind != RE_IR_TERM_DOUBLE && value->kind != RE_IR_TERM_STRING &&
            value->kind != RE_IR_TERM_ARRAY) return RE_STATUS_INVALID_ARGUMENT;
    }
    for (i = 0u; i < ir->query_count; ++i) {
        const re_ir_query_t *query = &ir->queries[i];
        size_t block;
        if (!index_ok(query->name, ir->term_count) || ir->terms[query->name].name == NULL ||
            !index_ok(query->goal, ir->term_count) ||
            ir->terms[query->goal].kind != RE_IR_TERM_STRING ||
            query->strategy < (int)RE_QUERY_STRATEGY_DEPTH_FIRST ||
            query->strategy > (int)RE_QUERY_STRATEGY_ITERATIVE) return RE_STATUS_INVALID_ARGUMENT;
        if (query->when != SIZE_MAX && !index_ok(query->when, ir->expr_count)) return RE_STATUS_INVALID_ARGUMENT;
        for (block = 0u; block < RE_QUERY_BLOCK_COUNT; ++block)
            if (query->first_action[block] > ir->query_action_count ||
                query->action_count[block] > ir->query_action_count - query->first_action[block]) return RE_STATUS_INVALID_ARGUMENT;
    }
    for (i = 0u; i < ir->query_action_count; ++i) {
        const re_ir_query_action_t *action = &ir->query_actions[i];
        if (action->is_call != 0 && action->is_call != 1) return RE_STATUS_INVALID_ARGUMENT;
        if (!index_ok(action->name, ir->term_count) || ir->terms[action->name].name == NULL ||
            ir->terms[action->name].name_size == 0u) return RE_STATUS_INVALID_ARGUMENT;
        if (action->is_call) {
            if (action->value != SIZE_MAX || !index_ok(action->args, ir->term_count) ||
                ir->terms[action->args].kind != RE_IR_TERM_STRING ||
                ir->terms[action->name].kind != RE_IR_TERM_FUNCTION) return RE_STATUS_INVALID_ARGUMENT;
        } else {
            re_ir_term_kind_t value_kind;
            if (action->args != SIZE_MAX || !index_ok(action->value, ir->term_count) ||
                ir->terms[action->name].kind != RE_IR_TERM_FACT) return RE_STATUS_INVALID_ARGUMENT;
            value_kind = ir->terms[action->value].kind;
            if (value_kind != RE_IR_TERM_BOOL && value_kind != RE_IR_TERM_INT64 &&
                value_kind != RE_IR_TERM_DOUBLE && value_kind != RE_IR_TERM_STRING) return RE_STATUS_INVALID_ARGUMENT;
        }
    }
    return RE_STATUS_OK;
}
