#include "re_internal.h"
#include "backward_machine.h"
#include "backward_machine_goal.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct binding_t {
    char *name;
    size_t name_size;
    re_value_t value;
    char *string_data;
} binding_t;

typedef struct environment_t {
    binding_t *items;
    size_t count;
} environment_t;

typedef struct trace_state_t {
    re_query_t *query;
    re_string_t *names;
    size_t count;
    size_t capacity;
} trace_state_t;

typedef struct call_frame_t {
    re_string_t name;
    const environment_t *environment;
} call_frame_t;

typedef struct goal_work_stack_t {
    re_string_t *items;
    size_t count;
    size_t capacity;
} goal_work_stack_t;

typedef struct condition_frame_t {
    const re_expr_t *expr;
    int phase;
    int result;
} condition_frame_t;

typedef struct condition_stack_t {
    condition_frame_t *items;
    size_t count;
    size_t capacity;
} condition_stack_t;

typedef struct operand_frame_t {
    const re_operand_t *operand;
    size_t parent;
    size_t argument_index;
    re_value_t *arguments;
    size_t argument_count;
    size_t result_slot;
    re_value_t result;
    int waiting;
} operand_frame_t;

typedef struct operand_stack_t {
    operand_frame_t *items;
    size_t count;
    size_t capacity;
} operand_stack_t;

static int equal_text(re_string_t left, re_string_t right);
static re_status_t make_proof(re_query_t *query, const environment_t *environment,
                              const trace_state_t *trace);
static re_status_t push_trace(trace_state_t *trace, re_string_t name);
static void goal_work_stack_destroy(const re_allocator_impl_t *allocator, goal_work_stack_t *stack);
static void environment_destroy(const re_allocator_impl_t *allocator, environment_t *environment);

typedef struct machine_callback_context_t {
    re_query_t *query;
    trace_state_t *trace;
} machine_callback_context_t;

static re_status_t machine_make_proof(void *context) {
    machine_callback_context_t *callbacks = (machine_callback_context_t *)context;
    environment_t environment = {NULL, 0u};
    re_status_t status = make_proof(callbacks->query, &environment, callbacks->trace);
    environment_destroy(&callbacks->query->allocator, &environment);
    return status;
}

static re_status_t machine_push_trace(void *context, re_string_t name) {
    return push_trace(((machine_callback_context_t *)context)->trace, name);
}

static void machine_reset_trace(void *context, size_t count) {
    trace_state_t *trace = ((machine_callback_context_t *)context)->trace;
    trace->count = count;
}

static void condition_stack_destroy(const re_allocator_impl_t *allocator, condition_stack_t *stack) {
    re_free(allocator, stack->items);
    memset(stack, 0, sizeof(*stack));
}

static re_status_t condition_stack_push(const re_allocator_impl_t *allocator,
                                        condition_stack_t *stack, const re_expr_t *expr) {
    size_t capacity;
    condition_frame_t *grown;
    if (stack->count == stack->capacity) {
        capacity = stack->capacity == 0u ? 8u : stack->capacity;
        if (capacity > (size_t)-1 / 2u) return RE_STATUS_LIMIT;
        capacity *= 2u;
        if (capacity > (size_t)-1 / sizeof(*grown)) return RE_STATUS_LIMIT;
        grown = re_realloc(allocator, stack->items, capacity * sizeof(*grown));
        if (grown == NULL) return RE_STATUS_OUT_OF_MEMORY;
        stack->items = grown;
        stack->capacity = capacity;
    }
    stack->items[stack->count].expr = expr;
    stack->items[stack->count].phase = 0;
    stack->items[stack->count].result = 0;
    ++stack->count;
    return RE_STATUS_OK;
}

static re_status_t invalidate(re_facts_t *facts, const re_fact_event_t *event, void *context) {
    re_query_t *query = (re_query_t *)context;
    (void)facts;
    (void)event;
    query->invalidated = 1;
    return RE_STATUS_OK;
}

static int equal_text(re_string_t left, re_string_t right) {
    return left.size == right.size && (left.size == 0u || memcmp(left.data, right.data, left.size) == 0);
}

static int parse_int64_slice(re_string_t input, int64_t *out) {
    size_t index = 0u;
    int negative = 0;
    uint64_t magnitude = 0u;
    uint64_t limit;
    if (input.data == NULL || input.size == 0u || out == NULL) return 0;
    if (input.data[0] == '-' || input.data[0] == '+') {
        negative = input.data[0] == '-';
        if (++index == input.size) return 0;
    }
    limit = negative ? (uint64_t)INT64_MAX + 1u : (uint64_t)INT64_MAX;
    for (; index < input.size; ++index) {
        unsigned int digit;
        if (input.data[index] < '0' || input.data[index] > '9') return 0;
        digit = (unsigned int)(input.data[index] - '0');
        if (magnitude > (limit - digit) / 10u) return 0;
        magnitude = magnitude * 10u + digit;
    }
    if (negative && magnitude == (uint64_t)INT64_MAX + 1u) *out = INT64_MIN;
    else if (negative) *out = -(int64_t)magnitude;
    else *out = (int64_t)magnitude;
    return 1;
}

static void environment_destroy(const re_allocator_impl_t *allocator, environment_t *environment) {
    size_t index;
    if (environment == NULL) return;
    for (index = 0u; index < environment->count; ++index) {
        re_free(allocator, environment->items[index].name);
        re_free(allocator, environment->items[index].string_data);
    }
    re_free(allocator, environment->items);
    memset(environment, 0, sizeof(*environment));
}

static re_status_t copy_value(const re_allocator_impl_t *allocator, const re_value_t *source,
                              re_value_t *target, char **string_data) {
    *target = *source;
    *string_data = NULL;
    if (source->type != RE_VALUE_STRING) return RE_STATUS_OK;
    if (re_copy_string(allocator, source->as.string, string_data) != RE_STATUS_OK)
        return RE_STATUS_OUT_OF_MEMORY;
    target->as.string.data = *string_data;
    return RE_STATUS_OK;
}

static re_status_t environment_copy(const re_allocator_impl_t *allocator,
                                     const environment_t *source, environment_t *target) {
    size_t index;
    memset(target, 0, sizeof(*target));
    if (source->count == 0u) return RE_STATUS_OK;
    target->items = re_alloc(allocator, source->count * sizeof(*target->items));
    if (target->items == NULL) return RE_STATUS_OUT_OF_MEMORY;
    for (index = 0u; index < source->count; ++index) {
        binding_t *destination = &target->items[index];
        const binding_t *origin = &source->items[index];
        memset(destination, 0, sizeof(*destination));
        destination->name_size = origin->name_size;
        if (re_copy_string(allocator, (re_string_t){origin->name, origin->name_size},
                           &destination->name) != RE_STATUS_OK) {
            target->count = index;
            environment_destroy(allocator, target);
            return RE_STATUS_OUT_OF_MEMORY;
        }
        if (copy_value(allocator, &origin->value, &destination->value,
                       &destination->string_data) != RE_STATUS_OK) {
            target->count = index + 1u;
            environment_destroy(allocator, target);
            return RE_STATUS_OUT_OF_MEMORY;
        }
        target->count = index + 1u;
    }
    return RE_STATUS_OK;
}

static binding_t *find_binding(environment_t *environment, re_string_t name) {
    size_t index;
    for (index = 0u; index < environment->count; ++index)
        if (equal_text(name, (re_string_t){environment->items[index].name,
                                           environment->items[index].name_size}))
            return &environment->items[index];
    return NULL;
}

static const binding_t *find_const_binding(const environment_t *environment, re_string_t name) {
    return find_binding((environment_t *)environment, name);
}

static re_status_t bind_value(const re_allocator_impl_t *allocator, environment_t *environment,
                              re_string_t name, const re_value_t *value) {
    binding_t *binding = find_binding(environment, name);
    if (binding != NULL) {
        return re_value_compare(&binding->value, value, RE_COMPARE_EQ) ? RE_STATUS_OK : RE_STATUS_NOT_FOUND;
    }
    {
        binding_t *grown = re_realloc(allocator, environment->items,
                                      (environment->count + 1u) * sizeof(*grown));
        if (grown == NULL) return RE_STATUS_OUT_OF_MEMORY;
        environment->items = grown;
        binding = &environment->items[environment->count];
        memset(binding, 0, sizeof(*binding));
        binding->name_size = name.size;
        if (re_copy_string(allocator, name, &binding->name) != RE_STATUS_OK) return RE_STATUS_OUT_OF_MEMORY;
        if (copy_value(allocator, value, &binding->value, &binding->string_data) != RE_STATUS_OK) {
            re_free(allocator, binding->name);
            memset(binding, 0, sizeof(*binding));
            return RE_STATUS_OUT_OF_MEMORY;
        }
        ++environment->count;
    }
    return RE_STATUS_OK;
}

static re_status_t push_trace(trace_state_t *trace, re_string_t name) {
    re_string_t *grown;
    size_t capacity;
    if (trace->count == trace->capacity) {
        capacity = trace->capacity == 0u ? 4u : trace->capacity * 2u;
        grown = re_realloc(&trace->query->allocator, trace->names, capacity * sizeof(*grown));
        if (grown == NULL) return RE_STATUS_OUT_OF_MEMORY;
        trace->names = grown;
        trace->capacity = capacity;
    }
    trace->names[trace->count++] = name;
    return RE_STATUS_OK;
}

static void goal_work_stack_destroy(const re_allocator_impl_t *allocator, goal_work_stack_t *stack) {
    re_free(allocator, stack->items);
    memset(stack, 0, sizeof(*stack));
}

static re_status_t goal_work_push(const re_allocator_impl_t *allocator,
                                  goal_work_stack_t *stack, re_string_t name) {
    size_t capacity;
    re_string_t *grown;
    if (stack->count == stack->capacity) {
        capacity = stack->capacity == 0u ? 8u : stack->capacity;
        if (capacity > (size_t)-1 / 2u) return RE_STATUS_LIMIT;
        capacity *= 2u;
        if (capacity > (size_t)-1 / sizeof(*grown)) return RE_STATUS_LIMIT;
        grown = re_realloc(allocator, stack->items, capacity * sizeof(*grown));
        if (grown == NULL) return RE_STATUS_OUT_OF_MEMORY;
        stack->items = grown;
        stack->capacity = capacity;
    }
    stack->items[stack->count++] = name;
    return RE_STATUS_OK;
}

static int find_rule(const re_engine_t *engine, re_string_t name, size_t *index) {
    size_t i;
    if (engine->program == NULL) return 0;
    for (i = 0u; i < engine->program->rule_count; ++i) {
        const re_rule_t *rule = &engine->program->rules[i];
        if (equal_text((re_string_t){rule->name, rule->name_size}, name)) {
            *index = i;
            return 1;
        }
    }
    return 0;
}

static int environment_equal(const environment_t *left, const environment_t *right) {
    size_t index;
    if (left->count != right->count) return 0;
    for (index = 0u; index < left->count; ++index) {
        const binding_t *binding = find_const_binding(right,
            (re_string_t){left->items[index].name, left->items[index].name_size});
        if (binding == NULL || !re_value_compare(&left->items[index].value, &binding->value, RE_COMPARE_EQ))
            return 0;
    }
    return 1;
}

static int active_frame(const call_frame_t *frames, size_t count, re_string_t name,
                        const environment_t *environment) {
    size_t index;
    for (index = 0u; index < count; ++index)
        if (equal_text(frames[index].name, name) && environment_equal(frames[index].environment, environment))
            return 1;
    return 0;
}

static re_status_t make_proof(re_query_t *query, const environment_t *environment,
                              const trace_state_t *trace) {
    re_proof_t *proof = re_alloc(&query->allocator, sizeof(*proof));
    re_proof_t **grown_proofs;
    size_t index;
    if (proof == NULL) return RE_STATUS_OUT_OF_MEMORY;
    memset(proof, 0, sizeof(*proof));
    proof->allocator = query->allocator;
    if (environment->count != 0u) {
        proof->bindings = re_alloc(&proof->allocator, environment->count * sizeof(*proof->bindings));
        if (proof->bindings == NULL) { re_proof_destroy(proof); return RE_STATUS_OUT_OF_MEMORY; }
    }
    for (index = 0u; index < environment->count; ++index) {
        re_query_binding_impl_t *binding = &proof->bindings[index];
        const binding_t *source = &environment->items[index];
        binding->name_size = source->name_size;
        if (re_copy_string(&proof->allocator, (re_string_t){source->name, source->name_size},
                           &binding->name) != RE_STATUS_OK) { re_proof_destroy(proof); return RE_STATUS_OUT_OF_MEMORY; }
        if (copy_value(&proof->allocator, &source->value, &binding->value,
                       &binding->string_data) != RE_STATUS_OK) { re_proof_destroy(proof); return RE_STATUS_OUT_OF_MEMORY; }
    }
    proof->binding_count = environment->count;
    if (trace->count != 0u) {
        proof->trace_names = re_alloc(&proof->allocator, trace->count * sizeof(*proof->trace_names));
        if (proof->trace_names == NULL) { re_proof_destroy(proof); return RE_STATUS_OUT_OF_MEMORY; }
    }
    for (index = 0u; index < trace->count; ++index) {
        if (re_copy_string(&proof->allocator, trace->names[index], &proof->trace_names[index]) != RE_STATUS_OK) {
            re_proof_destroy(proof); return RE_STATUS_OUT_OF_MEMORY;
        }
        proof->trace_count = index + 1u;
    }
    if (trace->count != 0u) {
        proof->nodes = re_alloc(&proof->allocator, trace->count * sizeof(*proof->nodes));
        if (proof->nodes == NULL) { re_proof_destroy(proof); return RE_STATUS_OUT_OF_MEMORY; }
    }
    if (trace->count > 1u) {
        proof->edges = re_alloc(&proof->allocator, (trace->count - 1u) * sizeof(*proof->edges));
        if (proof->edges == NULL) { re_proof_destroy(proof); return RE_STATUS_OUT_OF_MEMORY; }
    }
    for (index = 0u; index < trace->count; ++index) {
        proof->nodes[index].rule_name_size = trace->names[index].size;
        if (re_copy_string(&proof->allocator, trace->names[index], &proof->nodes[index].rule_name) != RE_STATUS_OK) {
            re_proof_destroy(proof); return RE_STATUS_OUT_OF_MEMORY;
        }
        proof->node_count = index + 1u;
        if (index != 0u) {
            proof->edges[index - 1u].parent_index = index - 1u;
            proof->edges[index - 1u].child_index = index;
        }
    }
    proof->edge_count = trace->count > 1u ? trace->count - 1u : 0u;
    grown_proofs = re_realloc(&query->allocator, query->proofs,
                              (query->proof_count + 1u) * sizeof(*query->proofs));
    if (grown_proofs == NULL) { re_proof_destroy(proof); return RE_STATUS_OUT_OF_MEMORY; }
    query->proofs = grown_proofs;
    query->proofs[query->proof_count++] = proof;
    return RE_STATUS_OK;
}

static re_status_t machine_operand_value(re_query_t *query, const re_operand_t *operand,
                                 environment_t *environment, size_t depth,
                                 call_frame_t *frames, size_t frame_count,
                                 trace_state_t *trace, re_value_t *value);

static re_status_t machine_condition_matches(re_query_t *query, const re_expr_t *expr,
                                     environment_t *environment, size_t depth,
                                     call_frame_t *frames, size_t frame_count,
                                     trace_state_t *trace, int *matched) {
    condition_stack_t stack = {NULL, 0u, 0u};
    int final_result = 0;
    re_status_t status = condition_stack_push(&query->allocator, &stack, expr);
    if (status != RE_STATUS_OK) return status;
    while (stack.count != 0u) {
        condition_frame_t *frame = &stack.items[stack.count - 1u];
        const re_expr_t *current = frame->expr;
        re_value_t left;
        re_value_t right;
        if (frame->phase == 0) {
            if (current->kind == RE_EXPR_TRUE || current->kind == RE_EXPR_FALSE) {
                frame->result = current->kind == RE_EXPR_TRUE;
                final_result = frame->result;
                --stack.count;
            } else if (current->kind == RE_EXPR_NOT || current->kind == RE_EXPR_AND || current->kind == RE_EXPR_OR) {
                frame->phase = 1;
                status = condition_stack_push(&query->allocator, &stack, current->first);
                if (status != RE_STATUS_OK) break;
                continue;
            } else {
                status = machine_operand_value(query, &current->left, environment, depth, frames, frame_count, trace, &left);
                if (status != RE_STATUS_OK) break;
                status = machine_operand_value(query, &current->right, environment, depth, frames, frame_count, trace, &right);
                if (status != RE_STATUS_OK) break;
                frame->result = re_value_compare(&left, &right, current->compare);
                final_result = frame->result;
                --stack.count;
            }
            if (stack.count != 0u) stack.items[stack.count - 1u].result = final_result;
            continue;
        }
        if (frame->phase == 1) {
            int child_result = frame->result;
            if (current->kind == RE_EXPR_NOT) {
                frame->result = !child_result;
                final_result = frame->result;
                --stack.count;
            } else if ((current->kind == RE_EXPR_AND && !child_result) ||
                       (current->kind == RE_EXPR_OR && child_result)) {
                final_result = frame->result;
                --stack.count;
            } else {
                frame->phase = 2;
                status = condition_stack_push(&query->allocator, &stack, current->second);
                if (status != RE_STATUS_OK) break;
                continue;
            }
            if (stack.count != 0u) stack.items[stack.count - 1u].result = final_result;
            continue;
        }
        --stack.count;
        final_result = frame->result;
        if (stack.count != 0u) stack.items[stack.count - 1u].result = final_result;
    }
    if (status == RE_STATUS_OK) *matched = final_result;
    condition_stack_destroy(&query->allocator, &stack);
    return status;
}

static re_status_t backward_goal_step(re_query_t *query, re_string_t name, const re_operand_t *arguments,
                              size_t argument_count, environment_t *environment,
                              size_t depth, call_frame_t *frames, size_t frame_count,
                              trace_state_t *trace, int root, int *proved_out);

static re_status_t backward_operand_goal(re_query_t *query, const re_operand_t *operand,
                                        environment_t *environment, size_t depth,
                                        call_frame_t *frames, size_t frame_count,
                                        trace_state_t *trace, re_value_t *value) {
    re_string_t name;
    int proved = 0;
    if (depth >= query->max_depth) return RE_STATUS_LIMIT;
    if (operand->kind == RE_OPERAND_GOAL_CALL) {
        name = (re_string_t){operand->goal_name, operand->goal_name_size};
        re_status_t status = backward_goal_step(query, name, operand->arguments,
            operand->argument_count, environment, depth + 1u, frames, frame_count,
            trace, 0, &proved);
        value->type = RE_VALUE_BOOL;
        value->as.boolean = proved;
        return status;
    }
    if (operand->kind == RE_OPERAND_FUNCTION && operand->argument_count == 1u &&
        operand->arguments[0].kind == RE_OPERAND_LITERAL &&
        operand->arguments[0].value.type == RE_VALUE_STRING) {
        name = operand->arguments[0].value.as.string;
        re_status_t status = backward_goal_step(query, name, NULL, 0u, environment,
            depth + 1u, frames, frame_count, trace, 0, &proved);
        value->type = RE_VALUE_BOOL;
        value->as.boolean = proved;
        return status;
    }
    if (operand->kind == RE_OPERAND_FACT) {
        re_status_t status = re_facts_get(query->facts,
            (re_string_t){operand->fact_name, operand->fact_name_size}, value);
        if (status != RE_STATUS_NOT_FOUND) return status;
        name = (re_string_t){operand->fact_name, operand->fact_name_size};
        status = backward_goal_step(query, name, NULL, 0u, environment, depth + 1u,
                                    frames, frame_count, trace, 0, &proved);
        value->type = RE_VALUE_BOOL;
        value->as.boolean = proved;
        return status;
    }
    return RE_STATUS_NOT_SUPPORTED;
}

static re_status_t machine_operand_value(re_query_t *query, const re_operand_t *operand,
                                 environment_t *environment, size_t depth,
                                 call_frame_t *frames, size_t frame_count,
                                  trace_state_t *trace, re_value_t *value) {
    operand_stack_t stack = {NULL, 0u, 0u};
    re_status_t status = RE_STATUS_OK;
    size_t result_index = 0u;
    size_t i;
    if (operand == NULL || value == NULL) return RE_STATUS_INVALID_ARGUMENT;
    for (;;) {
        operand_frame_t *frame;
        const binding_t *binding;
        if (stack.count == 0u) {
            size_t capacity = 8u;
            if (capacity > (size_t)-1 / sizeof(*stack.items)) return RE_STATUS_LIMIT;
            stack.items = re_alloc(&query->allocator, capacity * sizeof(*stack.items));
            if (stack.items == NULL) return RE_STATUS_OUT_OF_MEMORY;
            stack.capacity = capacity;
            memset(&stack.items[0], 0, sizeof(stack.items[0]));
            stack.items[0].operand = operand;
            stack.items[0].parent = (size_t)-1;
            stack.count = 1u;
        }
        frame = &stack.items[stack.count - 1u];
        if (frame->waiting) {
            re_function_t *function;
            function = query->engine->functions;
            while (function != NULL && (function->unregistered ||
                   function->name_size != frame->operand->function_name_size ||
                   memcmp(function->name, frame->operand->function_name, function->name_size) != 0))
                function = function->next;
            if (function == NULL) { status = RE_STATUS_NOT_FOUND; break; }
            function->active_calls++;
            status = function->call(query->engine, query->facts, frame->arguments,
                                    frame->argument_count, &frame->result, function->context);
            function->active_calls--;
            if (status != RE_STATUS_OK) break;
            re_free(&query->allocator, frame->arguments);
            frame->arguments = NULL;
            frame->waiting = 0;
        } else if (frame->operand->kind == RE_OPERAND_FUNCTION &&
                   !(frame->operand->function_name_size == 4u &&
                     memcmp(frame->operand->function_name, "goal", 4u) == 0)) {
            if (frame->argument_count == 0u && frame->operand->argument_count != 0u) {
                frame->argument_count = frame->operand->argument_count;
                if (frame->argument_count > (size_t)-1 / sizeof(*frame->arguments)) { status = RE_STATUS_LIMIT; break; }
                frame->arguments = re_alloc(&query->allocator, frame->argument_count * sizeof(*frame->arguments));
                if (frame->arguments == NULL) { status = RE_STATUS_OUT_OF_MEMORY; break; }
            }
            if (frame->argument_index < frame->argument_count) {
                size_t child = frame->argument_index++;
                size_t next_count = stack.count + 1u;
                const re_operand_t *child_operand = &frame->operand->arguments[child];
                if (next_count > stack.capacity) {
                    size_t capacity = stack.capacity > (size_t)-1 / 2u ? 0u : stack.capacity * 2u;
                    operand_frame_t *grown;
                    if (capacity == 0u || capacity > (size_t)-1 / sizeof(*grown)) { status = RE_STATUS_LIMIT; break; }
                    grown = re_realloc(&query->allocator, stack.items, capacity * sizeof(*grown));
                    if (grown == NULL) { status = RE_STATUS_OUT_OF_MEMORY; break; }
                    stack.items = grown;
                    stack.capacity = capacity;
                }
                memset(&stack.items[stack.count], 0, sizeof(stack.items[stack.count]));
                stack.items[stack.count].operand = child_operand;
                stack.items[stack.count].parent = stack.count - 1u;
                stack.items[stack.count].result_slot = child;
                ++stack.count;
                continue;
            }
            frame->waiting = 1;
            continue;
        } else if (frame->operand->kind == RE_OPERAND_VARIABLE) {
            binding = find_const_binding(environment, (re_string_t){frame->operand->fact_name, frame->operand->fact_name_size});
            if (binding == NULL) { status = RE_STATUS_NOT_FOUND; break; }
            frame->result = binding->value;
        } else if (frame->operand->kind == RE_OPERAND_ANONYMOUS) {
            frame->result.type = RE_VALUE_UNKNOWN;
        } else if (frame->operand->kind == RE_OPERAND_LITERAL) {
            frame->result = frame->operand->value;
        } else if (frame->operand->kind == RE_OPERAND_GOAL_CALL || frame->operand->kind == RE_OPERAND_FACT ||
                   (frame->operand->kind == RE_OPERAND_FUNCTION && frame->operand->function_name_size == 4u &&
                    memcmp(frame->operand->function_name, "goal", 4u) == 0)) {
            status = backward_operand_goal(query, frame->operand, environment, depth,
                                          frames, frame_count, trace, &frame->result);
            if (status != RE_STATUS_OK) break;
        } else {
            status = RE_STATUS_NOT_SUPPORTED;
            break;
        }
        result_index = stack.count - 1u;
        if (result_index == 0u) { *value = stack.items[0].result; break; }
        stack.items[stack.items[result_index].parent].arguments[stack.items[result_index].result_slot] =
            stack.items[result_index].result;
        --stack.count;
    }
    for (i = 0u; i < stack.count; ++i) re_free(&query->allocator, stack.items[i].arguments);
    re_free(&query->allocator, stack.items);
    return status;
}

static re_status_t bind_arguments(re_query_t *query, const re_rule_t *rule,
                                   const re_operand_t *arguments, size_t argument_count,
                                   environment_t *environment, size_t depth,
                                   call_frame_t *frames, size_t frame_count,
                                   trace_state_t *trace) {
    size_t index;
    re_value_t value;
    re_status_t status;
    if (argument_count == 0u)
        return rule->formal_parameter_count == 0u ? RE_STATUS_OK : RE_STATUS_NOT_FOUND;
    if (rule->formal_parameter_count != argument_count) return RE_STATUS_NOT_FOUND;
    for (index = 0u; index < argument_count; ++index) {
        const re_operand_t *argument = &arguments[index];
        if (argument->kind == RE_OPERAND_VARIABLE) {
            const binding_t *binding = find_const_binding(environment,
                (re_string_t){argument->fact_name, argument->fact_name_size});
            if (binding == NULL) return RE_STATUS_NOT_FOUND;
            value = binding->value;
        } else {
            status = machine_operand_value(query, argument, environment, depth, frames, frame_count, trace, &value);
            if (status != RE_STATUS_OK) return status;
        }
        status = bind_value(&query->allocator, environment,
                            (re_string_t){rule->formal_parameters[index], strlen(rule->formal_parameters[index])}, &value);
        if (status != RE_STATUS_OK) return status;
    }
    return RE_STATUS_OK;
}

static re_status_t machine_goal_step(re_query_t *query, re_string_t name, const re_operand_t *arguments,
                              size_t argument_count, environment_t *environment,
                              size_t depth, call_frame_t *frames, size_t frame_count,
                              trace_state_t *trace, int root, int *proved_out) {
    size_t rule_index;
    re_status_t status = RE_STATUS_OK;
    if (depth > query->max_depth) return RE_STATUS_LIMIT;
    if (proved_out != NULL) *proved_out = 0;
    if (!find_rule(query->engine, name, &rule_index)) return RE_STATUS_OK;
    if (frames != NULL && active_frame(frames, frame_count, name, environment)) return RE_STATUS_OK;
    if (trace != NULL && push_trace(trace, name) != RE_STATUS_OK) return RE_STATUS_OUT_OF_MEMORY;
    if (frames != NULL) { frames[frame_count].name = name; frames[frame_count].environment = environment; }
    for (rule_index = 0u; rule_index < query->engine->program->rule_count; ++rule_index) {
        const re_rule_t *rule = &query->engine->program->rules[rule_index];
        environment_t branch;
        int matched = 0;
        size_t alternative_count = 1u;
        size_t alternative_index;
        size_t trace_start = trace == NULL ? 0u : trace->count;
        if (!equal_text((re_string_t){rule->name, rule->name_size}, name)) continue;
        if (!re_rule_active(rule, query->engine->program->has_clock ? query->engine->program->clock_epoch : 0)) continue;
        status = environment_copy(&query->allocator, environment, &branch);
        if (status != RE_STATUS_OK) break;
        status = bind_arguments(query, rule, arguments, argument_count, &branch, depth,
                                frames, frame_count, trace);
        if (status == RE_STATUS_NOT_FOUND) { environment_destroy(&query->allocator, &branch); continue; }
        if (status != RE_STATUS_OK) break;
        if (root && rule->condition->kind == RE_EXPR_OR) alternative_count = 2u;
        for (alternative_index = 0u; alternative_index < alternative_count; ++alternative_index) {
            const re_expr_t *condition = rule->condition;
            environment_t alternative;
            if (alternative_count == 2u)
                condition = alternative_index == 0u ? rule->condition->first : rule->condition->second;
            status = environment_copy(&query->allocator, &branch, &alternative);
            if (status != RE_STATUS_OK) break;
            matched = 0;
            status = machine_condition_matches(query, condition, &alternative, depth, frames,
                                       frame_count + 1u, trace, &matched);
            if (status == RE_STATUS_NOT_FOUND) status = RE_STATUS_OK;
            if (status == RE_STATUS_OK && matched && root && query->proof_count < query->max_solutions)
                status = make_proof(query, &alternative, trace);
            if (status == RE_STATUS_OK && matched && !root) {
                environment_destroy(&query->allocator, environment);
                *environment = alternative;
                memset(&alternative, 0, sizeof(alternative));
                if (proved_out != NULL) *proved_out = 1;
            }
            environment_destroy(&query->allocator, &alternative);
            if (status != RE_STATUS_OK || (matched && !root) || query->proof_count >= query->max_solutions)
                break;
            if (trace != NULL) trace->count = trace_start;
        }
        environment_destroy(&query->allocator, &branch);
        if (trace != NULL && !(matched && !root)) trace->count = trace_start;
        if (status != RE_STATUS_OK || (matched && !root) || query->proof_count >= query->max_solutions) break;
    }
    if (trace != NULL && (root || (proved_out != NULL && !*proved_out)) && trace->count != 0u) --trace->count;
    if (status == RE_STATUS_NOT_FOUND) status = RE_STATUS_OK;
    return status;
}

static int simple_goal_successor(const re_expr_t *condition, re_string_t *successor) {
    const re_operand_t *operand;
    if (condition->kind == RE_EXPR_TRUE) return 1;
    if (condition->kind != RE_EXPR_COMPARE || condition->compare != RE_COMPARE_TRUE) return 0;
    operand = &condition->left;
    if (operand->kind != RE_OPERAND_GOAL_CALL || operand->argument_count != 0u) return 0;
    successor->data = operand->goal_name;
    successor->size = operand->goal_name_size;
    return 2;
}

static int simple_goal_rule(const re_engine_t *engine, re_string_t name,
                            size_t *rule_index, re_string_t *successor) {
    size_t index;
    size_t matches = 0u;
    for (index = 0u; index < engine->program->rule_count; ++index) {
        const re_rule_t *rule = &engine->program->rules[index];
        if (!equal_text((re_string_t){rule->name, rule->name_size}, name)) continue;
        ++matches;
        *rule_index = index;
        if (simple_goal_successor(rule->condition, successor) == 0) return 0;
    }
    return matches == 1u;
}

static re_status_t prove_simple_goal_chain(re_query_t *query, re_string_t name,
                                           environment_t *environment, size_t depth,
                                           trace_state_t *trace, int root, int *proved_out) {
    size_t step;
    re_string_t current = name;
    (void)environment;
    if (proved_out != NULL) *proved_out = 0;
    for (step = 0u; step <= query->max_depth; ++step) {
        size_t rule_index;
        re_string_t successor = {NULL, 0u};
        int kind;
        if (depth + step > query->max_depth) return RE_STATUS_LIMIT;
        if (!find_rule(query->engine, current, &rule_index)) {
            if (trace != NULL && trace->count != 0u) --trace->count;
            return RE_STATUS_OK;
        }
        if (!simple_goal_rule(query->engine, current, &rule_index, &successor)) return RE_STATUS_NOT_FOUND;
        kind = simple_goal_successor(query->engine->program->rules[rule_index].condition, &successor);
        if (trace != NULL && push_trace(trace, current) != RE_STATUS_OK) return RE_STATUS_OUT_OF_MEMORY;
        if (kind == 1) {
            if (root && query->proof_count < query->max_solutions) {
                re_status_t status = make_proof(query, environment, trace);
                if (status != RE_STATUS_OK) return status;
            }
            if (proved_out != NULL) *proved_out = 1;
            if (trace != NULL && trace->count != 0u) --trace->count;
            return RE_STATUS_OK;
        }
        current = successor;
    }
    return RE_STATUS_LIMIT;
}

static re_status_t backward_goal_step(re_query_t *query, re_string_t name, const re_operand_t *arguments,
                              size_t argument_count, environment_t *environment,
                              size_t depth, call_frame_t *frames, size_t frame_count,
                              trace_state_t *trace, int root, int *proved_out) {
    goal_work_stack_t stack = {NULL, 0u, 0u};
    re_status_t status;
    status = goal_work_push(&query->allocator, &stack, name);
    if (status != RE_STATUS_OK) {
        return status;
    }
    if (root) {
        status = prove_simple_goal_chain(query, name, environment, depth, trace, root, proved_out);
        if (status != RE_STATUS_NOT_FOUND) {
            goal_work_stack_destroy(&query->allocator, &stack);
            return status;
        }
        trace->count = 0u;
    }
    status = machine_goal_step(query, stack.items[0], arguments, argument_count,
                                  environment, depth, frames, frame_count, trace,
                                  root, proved_out);
    goal_work_stack_destroy(&query->allocator, &stack);
    return status;
}

re_status_t re_backward_machine_dispatch(re_engine_t *engine, re_facts_t *facts, re_string_t goal,
                                     const re_query_options_t *options, re_query_t **out_query) {
    re_query_t *query;
    environment_t environment;
    trace_state_t trace;
    call_frame_t *frames;
    re_status_t status;
    const char *equals;
    machine_callback_context_t machine_callbacks;
    if (engine == NULL || facts == NULL || out_query == NULL || goal.data == NULL || goal.size == 0u) return RE_STATUS_INVALID_ARGUMENT;
    *out_query = NULL;
    query = re_alloc(&engine->allocator, sizeof(*query));
    if (query == NULL) return RE_STATUS_OUT_OF_MEMORY;
    memset(query, 0, sizeof(*query));
    query->allocator = engine->allocator;
    query->engine = engine;
    query->facts = facts;
    if (options != NULL && options->struct_size < sizeof(*options)) { re_free(&query->allocator, query); return RE_STATUS_INVALID_ARGUMENT; }
    query->max_depth = options != NULL && options->max_depth != 0u ? options->max_depth : 64u;
    query->max_solutions = options != NULL && options->max_solutions != 0u ? options->max_solutions : 1u;
    if (options != NULL && options->max_depth == 0u) {
        query->result = RE_QUERY_LIMIT;
        *out_query = query;
        return RE_STATUS_LIMIT;
    }
    equals = (const char *)memchr(goal.data, '=', goal.size);
    if (equals != NULL && equals + 1 < goal.data + goal.size && equals[1] == '=') {
        re_string_t left = {goal.data, (size_t)(equals - goal.data)};
        re_string_t right = {equals + 2, (size_t)(goal.data + goal.size - equals - 2)};
        re_value_t expected;
        re_value_t actual;
        int variable = 0;
        while (left.size != 0u && left.data[0] == ' ') { ++left.data; --left.size; }
        while (left.size != 0u && left.data[left.size - 1u] == ' ') --left.size;
        while (right.size != 0u && right.data[0] == ' ') { ++right.data; --right.size; }
        while (right.size != 0u && right.data[right.size - 1u] == ' ') --right.size;
        if (right.size != 0u && right.data[0] == '"' && right.data[right.size - 1u] == '"') {
            expected.type = RE_VALUE_STRING;
            expected.as.string.data = right.data + 1u;
            expected.as.string.size = right.size - 2u;
        } else {
            if (right.size == 4u && memcmp(right.data, "true", 4u) == 0) {
                expected.type = RE_VALUE_BOOL;
                expected.as.boolean = 1;
            } else if (right.size == 5u && memcmp(right.data, "false", 5u) == 0) {
                expected.type = RE_VALUE_BOOL;
                expected.as.boolean = 0;
            } else {
                expected.type = RE_VALUE_INT64;
                if (!parse_int64_slice(right, &expected.as.int64_value)) variable = 1;
            }
        }
        status = re_facts_get(facts, left, &actual);
        if (status == RE_STATUS_OK) {
            if (variable) {
                trace_state_t direct_trace = {query, NULL, 0u, 0u};
                environment_t direct_environment;
                memset(&direct_environment, 0, sizeof(direct_environment));
                if (bind_value(&query->allocator, &direct_environment, right, &actual) != RE_STATUS_OK ||
                    push_trace(&direct_trace, left) != RE_STATUS_OK ||
                    make_proof(query, &direct_environment, &direct_trace) != RE_STATUS_OK) {
                    environment_destroy(&query->allocator, &direct_environment);
                    re_free(&query->allocator, direct_trace.names);
                    re_query_destroy(query);
                    return RE_STATUS_OUT_OF_MEMORY;
                }
                environment_destroy(&query->allocator, &direct_environment);
                re_free(&query->allocator, direct_trace.names);
                query->result = RE_QUERY_PROVED;
            } else {
                query->result = re_value_compare(&actual, &expected, RE_COMPARE_EQ) ? RE_QUERY_PROVED : RE_QUERY_DISPROVED;
            }
        } else query->result = RE_QUERY_UNKNOWN;
        if (re_facts_subscribe(facts, invalidate, query, &query->subscription) != RE_STATUS_OK) {
            re_query_destroy(query); return RE_STATUS_OUT_OF_MEMORY;
        }
        *out_query = query;
        return RE_STATUS_OK;
    }
    memset(&environment, 0, sizeof(environment));
    memset(&trace, 0, sizeof(trace));
    trace.query = query;
    machine_callbacks.query = query;
    machine_callbacks.trace = &trace;
    status = re_backward_machine_goal_supported(engine, goal);
    if (status == RE_STATUS_OK) {
        re_goal_machine_callbacks_t callbacks = {
            &machine_callbacks, machine_make_proof, machine_push_trace, machine_reset_trace
        };
        status = re_backward_machine_goal_run(query, goal, &callbacks);
        environment_destroy(&query->allocator, &environment);
        re_free(&query->allocator, trace.names);
        if (status == RE_STATUS_LIMIT) query->result = RE_QUERY_LIMIT;
        else if (status != RE_STATUS_OK) { re_query_destroy(query); return status; }
        else query->result = query->proof_count != 0u ? RE_QUERY_PROVED : RE_QUERY_UNKNOWN;
        if (re_facts_subscribe(facts, invalidate, query, &query->subscription) != RE_STATUS_OK) {
            re_query_destroy(query); return RE_STATUS_OUT_OF_MEMORY;
        }
        *out_query = query;
        return query->result == RE_QUERY_LIMIT ? RE_STATUS_LIMIT : RE_STATUS_OK;
    }
    if (status != RE_STATUS_NOT_SUPPORTED) {
        re_free(&query->allocator, query);
        return status;
    }
    if (query->max_depth == (size_t)-1 ||
        query->max_depth + 1u > (size_t)-1 / sizeof(*frames)) {
        re_free(&query->allocator, query);
        return RE_STATUS_LIMIT;
    }
    frames = re_alloc(&query->allocator, (query->max_depth + 1u) * sizeof(*frames));
    if (frames == NULL) { re_free(&query->allocator, query); return RE_STATUS_OUT_OF_MEMORY; }
    status = backward_goal_step(query, goal, NULL, 0u, &environment, 0u, frames, 0u, &trace, 1, NULL);
    environment_destroy(&query->allocator, &environment);
    re_free(&query->allocator, frames);
    re_free(&query->allocator, trace.names);
    if (status == RE_STATUS_LIMIT) query->result = RE_QUERY_LIMIT;
    else if (status != RE_STATUS_OK) { re_query_destroy(query); return status; }
    else query->result = query->proof_count != 0u ? RE_QUERY_PROVED : RE_QUERY_UNKNOWN;
    if (re_facts_subscribe(facts, invalidate, query, &query->subscription) != RE_STATUS_OK) { re_query_destroy(query); return RE_STATUS_OUT_OF_MEMORY; }
    *out_query = query;
    return query->result == RE_QUERY_LIMIT ? RE_STATUS_LIMIT : RE_STATUS_OK;
}

re_status_t re_backward_query_create(re_engine_t *engine, re_facts_t *facts, re_string_t goal,
                                     const re_query_options_t *options, re_query_t **out_query) {
    return re_backward_machine_run(engine, facts, goal, options, out_query);
}
