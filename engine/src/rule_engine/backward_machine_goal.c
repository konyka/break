#include "backward_machine_goal.h"
#include "backward_machine_context.h"
#include <stdio.h>
#include <string.h>

static int same_text(re_string_t left, re_string_t right) {
    return left.size == right.size &&
           (left.size == 0u || memcmp(left.data, right.data, left.size) == 0);
}

static const re_rule_t *rule_at(const re_engine_t *engine, size_t index) {
    return &engine->program->rules[index];
}

static int simple_condition(const re_expr_t *condition, re_string_t *child) {
    const re_operand_t *operand;
    while (condition->kind == RE_EXPR_AND && condition->second != NULL &&
           condition->second->kind == RE_EXPR_TRUE)
        condition = condition->first;
    if (condition->kind == RE_EXPR_TRUE) return 1;
    if (condition->kind != RE_EXPR_COMPARE ||
        (condition->compare != RE_COMPARE_TRUE && condition->compare != RE_COMPARE_EQ) ||
        (condition->left.kind != RE_OPERAND_GOAL_CALL &&
         condition->left.kind != RE_OPERAND_FUNCTION) ||
        (condition->left.kind == RE_OPERAND_GOAL_CALL && condition->left.argument_count != 0u) ||
        (condition->left.kind == RE_OPERAND_FUNCTION &&
         (condition->left.function_name_size != 4u ||
          memcmp(condition->left.function_name, "goal", 4u) != 0 ||
          condition->left.argument_count != 1u ||
          condition->left.arguments[0].kind != RE_OPERAND_LITERAL ||
          condition->left.arguments[0].value.type != RE_VALUE_STRING))) return 0;
    if (condition->compare == RE_COMPARE_EQ &&
        (condition->right.kind != RE_OPERAND_LITERAL ||
         condition->right.value.type != RE_VALUE_BOOL ||
         !condition->right.value.as.boolean)) return 0;
    operand = &condition->left;
    if (operand->kind == RE_OPERAND_GOAL_CALL) {
        child->data = operand->goal_name;
        child->size = operand->goal_name_size;
    } else {
        child->data = operand->arguments[0].value.as.string.data;
        child->size = operand->arguments[0].value.as.string.size;
    }
    return 2;
}

re_status_t re_backward_machine_goal_supported(const re_engine_t *engine, re_string_t goal) {
    re_string_t *pending;
    size_t pending_count = 0u;
    size_t pending_index = 0u;
    if (engine == NULL || engine->program == NULL || goal.data == NULL || goal.size == 0u)
        return RE_STATUS_NOT_SUPPORTED;
    if (engine->program->rule_count == 0u) return RE_STATUS_OK;
    if (engine->program->rule_count == (size_t)-1 ||
        engine->program->rule_count + 1u > (size_t)-1 / sizeof(*pending)) return RE_STATUS_LIMIT;
    pending = re_alloc(&engine->program->allocator,
                       (engine->program->rule_count + 1u) * sizeof(*pending));
    if (pending == NULL) return RE_STATUS_OUT_OF_MEMORY;
    pending[pending_count++] = goal;
    while (pending_index < pending_count) {
        size_t rule_index;
        int found = 0;
        re_string_t current = pending[pending_index++];
        for (rule_index = 0u; rule_index < engine->program->rule_count; ++rule_index) {
            const re_rule_t *rule = rule_at(engine, rule_index);
            re_string_t child = {NULL, 0u};
            size_t seen_index;
            int kind;
            if (!same_text((re_string_t){rule->name, rule->name_size}, current)) continue;
            found = 1;
            kind = simple_condition(rule->condition, &child);
            if (rule->formal_parameter_count != 0u || kind == 0) {
                re_free(&engine->program->allocator, pending);
                return RE_STATUS_NOT_SUPPORTED;
            }
            if (kind != 2) continue;
            for (seen_index = 0u; seen_index < pending_count; ++seen_index)
                if (same_text(pending[seen_index], child)) break;
            if (seen_index == pending_count) {
                if (pending_count == engine->program->rule_count + 1u) {
                    re_free(&engine->program->allocator, pending);
                    return RE_STATUS_NOT_SUPPORTED;
                }
                pending[pending_count++] = child;
            }
        }
        if (!found) {
            re_free(&engine->program->allocator, pending);
            return RE_STATUS_NOT_SUPPORTED;
        }
    }
    re_free(&engine->program->allocator, pending);
    return RE_STATUS_OK;
}

static int active_parent(const re_backward_machine_context_t *context,
                         re_backward_machine_frame_id_t id, re_string_t goal) {
    re_backward_machine_frame_t *frame;
    while (id != RE_BACKWARD_MACHINE_FRAME_ID_INVALID) {
        frame = re_backward_machine_context_frame((re_backward_machine_context_t *)context, id);
        if (frame == NULL) return 0;
        if (same_text(frame->goal, goal)) return 1;
        id = frame->parent_id;
    }
    return 0;
}

re_status_t re_backward_machine_goal_run(re_query_t *query, re_string_t goal,
                                         const re_goal_machine_callbacks_t *callbacks) {
    re_backward_machine_context_t context;
    re_backward_machine_frame_id_t root_id;
    re_status_t status;
    if (query == NULL || callbacks == NULL || callbacks->make_proof == NULL ||
        callbacks->push_trace == NULL || callbacks->reset_trace == NULL)
        return RE_STATUS_INVALID_ARGUMENT;
    status = re_backward_machine_goal_supported(query->engine, goal);
    if (status != RE_STATUS_OK) return status == RE_STATUS_NOT_SUPPORTED ? RE_STATUS_NOT_FOUND : status;
    status = re_backward_machine_context_init(&context, &query->allocator);
    if (status != RE_STATUS_OK) return status;
    status = re_backward_machine_context_push(&context, RE_BACKWARD_FRAME_GOAL_SELECT,
                                              RE_BACKWARD_MACHINE_FRAME_ID_INVALID,
                                              RE_BACKWARD_FRAME_BORROWED, &root_id);
    if (status != RE_STATUS_OK) { re_backward_machine_context_destroy(&context); return status; }
    re_backward_machine_context_frame(&context, root_id)->goal = goal;
    while (context.frame_count != 0u && status == RE_STATUS_OK) {
        re_backward_machine_frame_t *frame = &context.frames[context.frame_count - 1u];
        if (frame->depth > query->max_depth) { status = RE_STATUS_LIMIT; break; }
        if (frame->state == RE_BACKWARD_FRAME_RETURN) {
            if (frame->result.kind == RE_BACKWARD_MACHINE_RESULT_TRUE && frame->parent_id == RE_BACKWARD_MACHINE_FRAME_ID_INVALID) {
                if (query->proof_count < query->max_solutions)
                    status = callbacks->make_proof(callbacks->context);
                callbacks->reset_trace(callbacks->context, frame->trace_start);
                if (status != RE_STATUS_OK || query->proof_count >= query->max_solutions) break;
                frame->state = RE_BACKWARD_FRAME_GOAL_SELECT;
            } else {
                re_backward_machine_frame_id_t parent_id = frame->parent_id;
                re_backward_machine_result_kind_t result = frame->result.kind;
                size_t trace_start = frame->trace_start;
                context.frame_count--;
                frame = re_backward_machine_context_frame(&context, parent_id);
                if (frame == NULL) { status = RE_STATUS_ERROR; break; }
                if (result == RE_BACKWARD_MACHINE_RESULT_TRUE) {
                    frame->result.kind = RE_BACKWARD_MACHINE_RESULT_TRUE;
                    frame->state = RE_BACKWARD_FRAME_RETURN;
                } else {
                    callbacks->reset_trace(callbacks->context, trace_start);
                    frame->state = RE_BACKWARD_FRAME_GOAL_SELECT;
                }
            }
            continue;
        }
        if (frame->state == RE_BACKWARD_FRAME_GOAL_SELECT ||
            frame->state == RE_BACKWARD_FRAME_RULE_ALTERNATIVE) {
            int selected = 0;
            while (frame->continuation < query->engine->program->rule_count) {
                const re_rule_t *rule = rule_at(query->engine, frame->continuation++);
                re_string_t child = {NULL, 0u};
                int kind;
                if (!same_text((re_string_t){rule->name, rule->name_size}, frame->goal) ||
                    !re_rule_active(rule, query->engine->program->has_clock ?
                                    query->engine->program->clock_epoch : 0)) continue;
                kind = simple_condition(rule->condition, &child);
                if (kind == 0) { status = RE_STATUS_NOT_FOUND; break; }
                frame->trace_start = re_backward_machine_trace_checkpoint(&context);
                if (callbacks->push_trace_parent != NULL) {
                    size_t trace_index = (size_t)-1;
                    status = callbacks->push_trace_parent(callbacks->context, frame->goal,
                                                   frame->parent_id == RE_BACKWARD_MACHINE_FRAME_ID_INVALID
                                                       ? (size_t)-1
                                                       : re_backward_machine_context_frame(&context,
                                                           frame->parent_id)->trace_index,
                                                   &trace_index);
                    frame->trace_index = trace_index;
                } else status = callbacks->push_trace(callbacks->context, frame->goal);
                if (status != RE_STATUS_OK) break;
                selected = 1;
                if (kind == 1) {
                    frame->result.kind = RE_BACKWARD_MACHINE_RESULT_TRUE;
                    frame->state = RE_BACKWARD_FRAME_RETURN;
                } else if (active_parent(&context, frame->parent_id, child)) {
                    callbacks->reset_trace(callbacks->context, frame->trace_start);
                    continue;
                } else {
                    re_backward_machine_frame_id_t child_id;
                    re_backward_machine_frame_id_t parent_id = frame->id;
                    size_t child_depth = frame->depth + 1u;
                    frame->state = RE_BACKWARD_FRAME_RULE_ALTERNATIVE;
                    status = re_backward_machine_context_push(
                        &context, RE_BACKWARD_FRAME_GOAL_SELECT, parent_id,
                        RE_BACKWARD_FRAME_BORROWED, &child_id);
                    if (status == RE_STATUS_OK) {
                        re_backward_machine_frame_t *child_frame =
                            re_backward_machine_context_frame(&context, child_id);
                        child_frame->goal = child;
                        child_frame->depth = child_depth;
                        child_frame->trace_start = re_backward_machine_trace_checkpoint(&context);
                    }
                }
                break;
            }
            if (status != RE_STATUS_OK) break;
            if (!selected) {
                callbacks->reset_trace(callbacks->context, frame->trace_start);
                if (frame->parent_id == RE_BACKWARD_MACHINE_FRAME_ID_INVALID) {
                    context.frame_count--;
                    continue;
                }
                frame->result.kind = RE_BACKWARD_MACHINE_RESULT_FALSE;
                frame->state = RE_BACKWARD_FRAME_RETURN;
            }
        }
    }
    re_backward_machine_context_destroy(&context);
    return status;
}
