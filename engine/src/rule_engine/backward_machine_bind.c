#include "backward_machine_bind.h"
#include <string.h>

static int text_equal(re_string_t left, re_string_t right) {
    return left.size == right.size && (left.size == 0u || memcmp(left.data, right.data, left.size) == 0);
}

static int value_equal(const re_value_t *left, const re_value_t *right) {
    if (left->type != right->type) return 0;
    switch (left->type) {
    case RE_VALUE_BOOL: return left->as.boolean == right->as.boolean;
    case RE_VALUE_INT64: return left->as.int64_value == right->as.int64_value;
    case RE_VALUE_DOUBLE: return left->as.double_value == right->as.double_value;
    case RE_VALUE_STRING: return text_equal(left->as.string, right->as.string);
    case RE_VALUE_NONE: case RE_VALUE_NULL: case RE_VALUE_UNKNOWN: return 1;
    }
    return 0;
}

static int literal_operand(const re_operand_t *operand, re_value_t *value) {
    if (operand->kind != RE_OPERAND_LITERAL) return 0;
    *value = operand->value;
    return 1;
}

static int operand_shape_supported(const re_operand_t *operand) {
    size_t index;
    if (operand == NULL) return 0;
    if (operand->kind == RE_OPERAND_FUNCTION) return 0;
    if (operand->kind != RE_OPERAND_LITERAL && operand->kind != RE_OPERAND_FACT &&
        operand->kind != RE_OPERAND_VARIABLE && operand->kind != RE_OPERAND_ANONYMOUS &&
        operand->kind != RE_OPERAND_GOAL_CALL) return 0;
    for (index = 0u; index < operand->argument_count; ++index)
        if (!operand_shape_supported(&operand->arguments[index])) return 0;
    return 1;
}

static int condition_shape_supported(const re_expr_t *condition) {
    if (condition == NULL) return 0;
    if (condition->kind == RE_EXPR_TRUE || condition->kind == RE_EXPR_FALSE) return 1;
    if (condition->kind == RE_EXPR_NOT || condition->kind == RE_EXPR_AND ||
        condition->kind == RE_EXPR_OR)
        return condition_shape_supported(condition->first) &&
               condition_shape_supported(condition->second);
    /* Parenthesized quantifier nodes (Task A2) carry an inner expression in
     * `first` and zeroed operands; the explicit machine cannot evaluate them,
     * so mark them unsupported (the caller answers RE_STATUS_NOT_SUPPORTED)
     * instead of letting the vacuous operand check pass. */
    if ((condition->kind == RE_EXPR_EXISTS || condition->kind == RE_EXPR_FORALL) &&
        condition->first != NULL) return 0;
    /* A5 multifield predicates need the forward evaluator's structured-path
     * probe; the bare forms' zeroed right operand would otherwise pass the
     * operand-shape check as a literal. */
    if (condition->kind == RE_EXPR_MULTIFIELD) return 0;
    /* A6 accumulate nodes write the injected result fact during matching;
     * the backward machine cannot host them. */
    if (condition->kind == RE_EXPR_ACCUMULATE) return 0;
    /* A9: test() wraps a function call (already rejected operand-side) and
     * the typed form iterates candidates; neither is a supported shape. The
     * typed node's zeroed operands would otherwise pass as literals. */
    if (condition->kind == RE_EXPR_TEST || condition->kind == RE_EXPR_TYPED) return 0;
    return operand_shape_supported(&condition->left) &&
           operand_shape_supported(&condition->right);
}

static int terminal_matches(const re_rule_t *rule, const re_operand_t *actuals,
                            size_t actual_count) {
    size_t index;
    re_value_t value;
    if (rule->formal_parameter_count != actual_count || rule->condition == NULL ||
        rule->condition->kind != RE_EXPR_TRUE) return 0;
    for (index = 0u; index < actual_count; ++index) {
        size_t previous;
        if (!literal_operand(&actuals[index], &value)) return 0;
        for (previous = 0u; previous < index; ++previous)
            if (text_equal((re_string_t){rule->formal_parameters[index],
                                         strlen(rule->formal_parameters[index])},
                           (re_string_t){rule->formal_parameters[previous],
                                         strlen(rule->formal_parameters[previous])}) &&
                !value_equal(&value, &actuals[previous].value)) return 0;
    }
    return 1;
}

re_status_t re_backward_machine_bind_run(re_query_t *query, re_string_t goal,
                                          const re_operand_t *arguments,
                                          size_t argument_count,
                                          re_backward_machine_bind_result_t *out) {
    re_backward_machine_context_t context;
    re_backward_machine_frame_id_t root_id;
    size_t index;
    re_status_t status;
    if (query == NULL || query->engine == NULL || query->engine->program == NULL ||
        out == NULL || goal.data == NULL || (argument_count != 0u && arguments == NULL))
        return RE_STATUS_INVALID_ARGUMENT;
    out->solution_count = 0u;
    out->last_parent_id = RE_BACKWARD_MACHINE_FRAME_ID_INVALID;
    status = re_backward_machine_context_init(&context, &query->allocator);
    if (status != RE_STATUS_OK) return status;
    status = re_backward_machine_context_push(&context, RE_BACKWARD_FRAME_GOAL_SELECT,
        RE_BACKWARD_MACHINE_FRAME_ID_INVALID, RE_BACKWARD_FRAME_BORROWED, &root_id);
    if (status != RE_STATUS_OK) { re_backward_machine_context_destroy(&context); return status; }
    context.frames[0].goal = goal;
    context.frames[0].argument_count = argument_count;
    if (argument_count != 0u) {
        context.frames[0].arguments = re_alloc(context.allocator, argument_count * sizeof(*arguments));
        if (context.frames[0].arguments == NULL) { re_backward_machine_context_destroy(&context); return RE_STATUS_OUT_OF_MEMORY; }
        memset(context.frames[0].arguments, 0, argument_count * sizeof(*arguments));
        for (index = 0u; index < argument_count; ++index) {
            status = re_operand_copy(context.allocator, &arguments[index], &context.frames[0].arguments[index]);
            if (status != RE_STATUS_OK) {
                context.frames[0].argument_count = index;
                re_backward_machine_context_destroy(&context);
                return status;
            }
        }
    }
    for (index = 0u; index < query->engine->program->rule_count; ++index) {
        const re_rule_t *rule = &query->engine->program->rules[index];
        if (!text_equal((re_string_t){rule->name, rule->name_size}, goal)) continue;
        if (!re_rule_active(rule, query->engine->program->has_clock ?
                            query->engine->program->clock_epoch : 0)) continue;
        if (!condition_shape_supported(rule->condition)) {
            status = RE_STATUS_NOT_SUPPORTED;
            break;
        }
        if (rule->formal_parameter_count != argument_count) continue;
        if (terminal_matches(rule, context.frames[0].arguments, argument_count)) {
            ++out->solution_count;
            out->last_parent_id = root_id;
            if (out->solution_count >= query->max_solutions) break;
        }
    }
    re_backward_machine_context_destroy(&context);
    return status;
}
