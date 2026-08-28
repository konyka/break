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
    size_t *parents;
    size_t count;
    size_t capacity;
    int depth_exhausted;
} trace_state_t;

typedef struct call_frame_t {
    re_string_t name;
    const environment_t *environment;
    size_t trace_index;
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

typedef struct condition_branch_list_t {
    environment_t *items;
    size_t count;
    size_t capacity;
} condition_branch_list_t;

static int equal_text(re_string_t left, re_string_t right);
static re_status_t make_proof(re_query_t *query, const environment_t *environment,
                              const trace_state_t *trace);
static re_status_t push_trace(trace_state_t *trace, re_string_t name);
static re_status_t push_trace_parent(trace_state_t *trace, re_string_t name, size_t parent);
static void goal_work_stack_destroy(const re_allocator_impl_t *allocator, goal_work_stack_t *stack);
static void environment_destroy(const re_allocator_impl_t *allocator, environment_t *environment);

typedef struct machine_callback_context_t {
    re_query_t *query;
    trace_state_t *trace;
    size_t last_trace_index;
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

static re_status_t machine_push_trace_parent(void *context, re_string_t name, size_t parent_index,
                                             size_t *out_index) {
    machine_callback_context_t *callbacks = (machine_callback_context_t *)context;
    re_status_t status = push_trace_parent(callbacks->trace, name, parent_index);
    if (status == RE_STATUS_OK) {
        callbacks->last_trace_index = callbacks->trace->count - 1u;
        if (out_index != NULL) *out_index = callbacks->last_trace_index;
    }
    return status;
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
    size_t index;
    (void)facts;
    (void)event;
    for (index = 0u; index < query->proof_count; ++index) {
        re_proof_destroy(query->proofs[index]);
        query->proofs[index] = NULL;
    }
    query->proof_count = 0u;
    query->next_proof = 0u;
    query->result = RE_QUERY_UNKNOWN;
    query->invalidated = 1;
    return RE_STATUS_OK;
}

static int equal_text(re_string_t left, re_string_t right) {
    return left.size == right.size && (left.size == 0u || memcmp(left.data, right.data, left.size) == 0);
}

static int goal_space(char c) {
    return c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\v' || c == '\f';
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
        if (binding->value.type == RE_VALUE_UNKNOWN && value->type == RE_VALUE_UNKNOWN)
            return RE_STATUS_OK;
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
    return push_trace_parent(trace, name, (size_t)-1);
}

static re_status_t push_trace_parent(trace_state_t *trace, re_string_t name, size_t parent) {
    re_string_t *grown;
    size_t *grown_parents;
    size_t capacity;
    if (trace->count == trace->capacity) {
        capacity = trace->capacity == 0u ? 4u : trace->capacity * 2u;
        if (capacity < trace->capacity || capacity > (size_t)-1 / sizeof(*grown) ||
            capacity > (size_t)-1 / sizeof(*grown_parents)) return RE_STATUS_LIMIT;
        grown = re_alloc(&trace->query->allocator, capacity * sizeof(*grown));
        if (grown == NULL) return RE_STATUS_OUT_OF_MEMORY;
        grown_parents = re_alloc(&trace->query->allocator, capacity * sizeof(*grown_parents));
        if (grown_parents == NULL) {
            re_free(&trace->query->allocator, grown);
            return RE_STATUS_OUT_OF_MEMORY;
        }
        if (trace->count != 0u) {
            memcpy(grown, trace->names, trace->count * sizeof(*grown));
            memcpy(grown_parents, trace->parents, trace->count * sizeof(*grown_parents));
        }
        re_free(&trace->query->allocator, trace->names);
        re_free(&trace->query->allocator, trace->parents);
        trace->names = grown;
        trace->parents = grown_parents;
        trace->capacity = capacity;
    }
    trace->names[trace->count++] = name;
    trace->parents[trace->count - 1u] = parent;
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

static int active_frame(const call_frame_t *frames, size_t count, re_string_t name,
                        size_t argument_count,
                        const environment_t *environment) {
    size_t index;
    (void)environment;
    if (argument_count != 0u) return 0;
    for (index = 0u; index < count; ++index)
        if (equal_text(frames[index].name, name))
            return 1;
    return 0;
}

static re_status_t make_proof(re_query_t *query, const environment_t *environment,
                              const trace_state_t *trace) {
    re_proof_t *proof = re_alloc(&query->allocator, sizeof(*proof));
    re_proof_t **grown_proofs;
    size_t index;
    size_t edge_count = 0u;
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
        proof->binding_count = index + 1u;
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
    for (index = 0u; index < trace->count; ++index)
        if (trace->parents[index] != (size_t)-1) ++edge_count;
    if (edge_count != 0u) {
        proof->edges = re_alloc(&proof->allocator, edge_count * sizeof(*proof->edges));
        if (proof->edges == NULL) { re_proof_destroy(proof); return RE_STATUS_OUT_OF_MEMORY; }
    }
    edge_count = 0u;
    for (index = 0u; index < trace->count; ++index) {
        proof->nodes[index].rule_name_size = trace->names[index].size;
        if (re_copy_string(&proof->allocator, trace->names[index], &proof->nodes[index].rule_name) != RE_STATUS_OK) {
            re_proof_destroy(proof); return RE_STATUS_OUT_OF_MEMORY;
        }
        proof->node_count = index + 1u;
        if (trace->parents[index] != (size_t)-1) {
            proof->edges[edge_count].parent_index = trace->parents[index];
            proof->edges[edge_count].child_index = index;
            ++edge_count;
        }
    }
    proof->edge_count = edge_count;
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

static int condition_has_or(const re_allocator_impl_t *allocator, const re_expr_t *expr) {
    const re_expr_t **stack = NULL;
    size_t count = 0u;
    size_t capacity = 0u;
    int found = 0;
    if (expr == NULL) return 0;
    for (;;) {
        const re_expr_t *current;
        if (expr != NULL) {
            if (count == capacity) {
                size_t next = capacity == 0u ? 8u : capacity * 2u;
                const re_expr_t **grown;
                if (next < capacity || next > (size_t)-1 / sizeof(*grown)) break;
                grown = re_realloc(allocator, stack, next * sizeof(*grown));
                if (grown == NULL) break;
                stack = grown;
                capacity = next;
            }
            stack[count++] = expr;
            expr = NULL;
        }
        if (count == 0u) break;
        current = stack[--count];
        if (current->kind == RE_EXPR_OR) {
            found = 1;
            break;
        }
        if (current->kind == RE_EXPR_AND || current->kind == RE_EXPR_NOT) {
            expr = current->second;
            if (current->first != NULL) {
                if (count == capacity) {
                    size_t next = capacity == 0u ? 8u : capacity * 2u;
                    const re_expr_t **grown;
                    if (next < capacity || next > (size_t)-1 / sizeof(*grown)) break;
                    grown = re_realloc(allocator, stack, next * sizeof(*grown));
                    if (grown == NULL) break;
                    stack = grown;
                    capacity = next;
                }
                stack[count++] = current->first;
            }
        }
    }
    re_free(allocator, stack);
    return found;
}

static void condition_branch_list_destroy(const re_allocator_impl_t *allocator,
                                          condition_branch_list_t *branches) {
    size_t index;
    for (index = 0u; index < branches->count; ++index)
        environment_destroy(allocator, &branches->items[index]);
    re_free(allocator, branches->items);
    memset(branches, 0, sizeof(*branches));
}

static re_status_t condition_branch_list_append(const re_allocator_impl_t *allocator,
                                                condition_branch_list_t *branches,
                                                environment_t *environment) {
    size_t capacity;
    environment_t *grown;
    if (branches->count == branches->capacity) {
        capacity = branches->capacity == 0u ? 4u : branches->capacity * 2u;
        if (capacity < branches->capacity || capacity > (size_t)-1 / sizeof(*grown))
            return RE_STATUS_LIMIT;
        grown = re_realloc(allocator, branches->items, capacity * sizeof(*grown));
        if (grown == NULL) return RE_STATUS_OUT_OF_MEMORY;
        branches->items = grown;
        branches->capacity = capacity;
    }
    branches->items[branches->count++] = *environment;
    memset(environment, 0, sizeof(*environment));
    return RE_STATUS_OK;
}

static re_status_t condition_collect_branches(re_query_t *query, const re_expr_t *expr,
                                              const environment_t *input, size_t depth,
                                              call_frame_t *frames, size_t frame_count,
                                              trace_state_t *trace,
                                              condition_branch_list_t *out) {
    condition_branch_list_t left = {NULL, 0u, 0u};
    condition_branch_list_t right = {NULL, 0u, 0u};
    environment_t candidate;
    size_t index;
    re_status_t status;
    if (expr->kind == RE_EXPR_OR) {
        size_t checkpoint = trace == NULL ? 0u : trace->count;
        status = condition_collect_branches(query, expr->first, input, depth, frames,
                                            frame_count, trace, out);
        if (trace != NULL) trace->count = checkpoint;
        if (status == RE_STATUS_OK)
            status = condition_collect_branches(query, expr->second, input, depth, frames,
                                                frame_count, trace, out);
        return status;
    }
    if (expr->kind != RE_EXPR_AND) {
        int matched = 0;
        status = environment_copy(&query->allocator, input, &candidate);
        if (status != RE_STATUS_OK) return status;
        status = machine_condition_matches(query, expr, &candidate, depth, frames,
                                            frame_count, trace, &matched);
            if (status == RE_STATUS_NOT_FOUND && (trace == NULL || !trace->depth_exhausted)) status = RE_STATUS_OK;
        if (status == RE_STATUS_OK && matched)
            status = condition_branch_list_append(&query->allocator, out, &candidate);
        environment_destroy(&query->allocator, &candidate);
        return status;
    }
    status = condition_collect_branches(query, expr->first, input, depth, frames,
                                        frame_count, trace, &left);
    if (status == RE_STATUS_OK) {
        for (index = 0u; index < left.count && status == RE_STATUS_OK; ++index)
            status = condition_collect_branches(query, expr->second, &left.items[index],
                                                depth, frames, frame_count, trace, &right);
    }
    condition_branch_list_destroy(&query->allocator, &left);
    if (status == RE_STATUS_OK) {
        for (index = 0u; index < right.count; ++index)
            status = condition_branch_list_append(&query->allocator, out, &right.items[index]);
    }
    condition_branch_list_destroy(&query->allocator, &right);
    return status;
}

static re_status_t parameter_goal_execute(re_query_t *query, re_string_t name, const re_operand_t *arguments,
                              size_t argument_count, environment_t *environment,
                              size_t depth, call_frame_t *frames, size_t frame_count,
                              trace_state_t *trace, int root, int *proved_out);

static re_status_t backward_operand_goal(re_query_t *query, const re_operand_t *operand,
                                        environment_t *environment, size_t depth,
                                        call_frame_t *frames, size_t frame_count,
                                        trace_state_t *trace, re_value_t *value) {
    re_string_t name;
    int proved = 0;
    if (depth >= query->max_depth) {
        if (trace != NULL) trace->depth_exhausted = 1;
        return RE_STATUS_LIMIT;
    }
    if (operand->kind == RE_OPERAND_GOAL_CALL) {
        name = (re_string_t){operand->goal_name, operand->goal_name_size};
        if (operand->argument_count != 0u && depth + 1u >= query->max_depth) {
            if (trace != NULL) trace->depth_exhausted = 1;
            return RE_STATUS_LIMIT;
        }
        if (trace != NULL && operand->argument_count == 0u) {
            size_t trace_index;
            for (trace_index = 0u; trace_index < trace->count; ++trace_index)
                if (equal_text(trace->names[trace_index], name))
                    return RE_STATUS_NOT_FOUND;
        }
        {
            size_t rule_index;
            int found = 0;
            for (rule_index = 0u; rule_index < query->engine->program->rule_count; ++rule_index) {
                const re_rule_t *rule = &query->engine->program->rules[rule_index];
                if (equal_text((re_string_t){rule->name, rule->name_size}, name)) {
                    found = 1;
                    if (rule->formal_parameter_count == operand->argument_count) break;
                }
            }
            if (found && rule_index == query->engine->program->rule_count)
                return RE_STATUS_INVALID_ARGUMENT;
        }
        re_status_t status = parameter_goal_execute(query, name, operand->arguments,
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
        re_status_t status = parameter_goal_execute(query, name, NULL, 0u, environment,
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
        status = parameter_goal_execute(query, name, NULL, 0u, environment, depth + 1u,
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
    if (argument_count == 0u) {
        if (rule->formal_parameter_count == 0u) return RE_STATUS_OK;
        if (depth != 0u) return RE_STATUS_NOT_FOUND;
        value.type = RE_VALUE_UNKNOWN;
        for (index = 0u; index < rule->formal_parameter_count; ++index) {
            status = bind_value(&query->allocator, environment,
                (re_string_t){rule->formal_parameters[index],
                              strlen(rule->formal_parameters[index])}, &value);
            if (status != RE_STATUS_OK) return status;
        }
        return RE_STATUS_OK;
    }
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
    if (depth >= query->max_depth) {
        if (trace != NULL) trace->depth_exhausted = 1;
        return RE_STATUS_LIMIT;
    }
    if (proved_out != NULL) *proved_out = 0;
    if (!find_rule(query->engine, name, &rule_index)) return RE_STATUS_OK;
    if (frames != NULL && active_frame(frames, frame_count, name, argument_count, environment)) {
        if (argument_count == 0u) return RE_STATUS_NOT_FOUND;
        if (trace != NULL) trace->depth_exhausted = 1;
        return RE_STATUS_LIMIT;
    }
    if (trace != NULL) {
        size_t parent = frames == NULL || frame_count == 0u
            ? (size_t)-1 : frames[frame_count - 1u].trace_index;
        if (push_trace_parent(trace, name, parent) != RE_STATUS_OK) return RE_STATUS_OUT_OF_MEMORY;
        if (frames != NULL) frames[frame_count].trace_index = trace->count - 1u;
    }
    if (frames != NULL) { frames[frame_count].name = name; frames[frame_count].environment = environment; }
    for (rule_index = 0u; rule_index < query->engine->program->rule_count; ++rule_index) {
        const re_rule_t *rule = &query->engine->program->rules[rule_index];
        environment_t branch;
        int matched = 0;
        condition_branch_list_t alternatives = {NULL, 0u, 0u};
        size_t alternative_index;
        size_t trace_start = trace == NULL ? 0u : trace->count;
        if (!equal_text((re_string_t){rule->name, rule->name_size}, name)) continue;
        if (!re_rule_active(rule, query->engine->program->has_clock ? query->engine->program->clock_epoch : 0)) continue;
        status = environment_copy(&query->allocator, environment, &branch);
        if (status != RE_STATUS_OK) break;
        {
        status = bind_arguments(query, rule, arguments, argument_count, &branch, depth,
                                frames, frame_count, trace);
        if (status == RE_STATUS_NOT_FOUND) {
            environment_destroy(&query->allocator, &branch);
            continue;
        }
        if (status == RE_STATUS_OK && frames != NULL && arguments != NULL &&
            depth + 1u >= query->max_depth) {
            if (trace != NULL) trace->depth_exhausted = 1;
            status = RE_STATUS_LIMIT;
        }
        if (status != RE_STATUS_OK) {
            environment_destroy(&query->allocator, &branch);
            break;
        }
        if (condition_has_or(&query->allocator, rule->condition)) {
            status = condition_collect_branches(query, rule->condition, &branch, depth,
                                                frames, frame_count + 1u, trace, &alternatives);
            if (status != RE_STATUS_OK) {
                condition_branch_list_destroy(&query->allocator, &alternatives);
                environment_destroy(&query->allocator, &branch);
                break;
            }
        } else {
            environment_t alternative;
            int branch_matched = 0;
            status = environment_copy(&query->allocator, &branch, &alternative);
            if (status == RE_STATUS_OK)
                status = machine_condition_matches(query, rule->condition, &alternative, depth,
                                                   frames, frame_count + 1u, trace,
                                                   &branch_matched);
            if (status == RE_STATUS_NOT_FOUND && (trace == NULL || !trace->depth_exhausted)) status = RE_STATUS_OK;
            if (status == RE_STATUS_OK && branch_matched)
                status = condition_branch_list_append(&query->allocator, &alternatives, &alternative);
            environment_destroy(&query->allocator, &alternative);
        }
        for (alternative_index = 0u; alternative_index < alternatives.count; ++alternative_index) {
            environment_t alternative;
            alternative = alternatives.items[alternative_index];
            memset(&alternatives.items[alternative_index], 0, sizeof(alternative));
            matched = 1;
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
        condition_branch_list_destroy(&query->allocator, &alternatives);
        environment_destroy(&query->allocator, &branch);
        }
        if (trace != NULL && !(matched && !root)) trace->count = trace_start;
        if (status != RE_STATUS_OK || (matched && !root) || query->proof_count >= query->max_solutions) break;
    }
    if (trace != NULL && (root || (proved_out != NULL && !*proved_out)) && trace->count != 0u) --trace->count;
    return status;
}

static re_status_t parameter_goal_execute(re_query_t *query, re_string_t name, const re_operand_t *arguments,
                              size_t argument_count, environment_t *environment,
                              size_t depth, call_frame_t *frames, size_t frame_count,
                              trace_state_t *trace, int root, int *proved_out) {
    goal_work_stack_t stack = {NULL, 0u, 0u};
    re_status_t status;
    status = goal_work_push(&query->allocator, &stack, name);
    if (status != RE_STATUS_OK) return status;
    status = machine_goal_step(query, stack.items[0], arguments, argument_count,
                               environment, depth, frames, frame_count, trace,
                               root, proved_out);
    goal_work_stack_destroy(&query->allocator, &stack);
    return status;
}

/* One capped depth-first pass over the goal: the goal("...") unwrap, the
 * direct `Fact == value` comparison, the zero-argument frame-machine slice,
 * and the plain DFS machine. re_backward_machine_dispatch owns argument and
 * option normalization (including the struct_size versioning and the
 * max_depth == 0 limit), so this always sees a full local options struct
 * with max_depth >= 1 and max_solutions >= 1. */
static re_status_t dispatch_once(re_engine_t *engine, re_facts_t *facts, re_string_t goal,
                                 const re_query_options_t *options, re_query_t **out_query) {
    re_query_t *query;
    environment_t environment;
    trace_state_t trace;
    call_frame_t *frames;
    re_status_t status;
    const char *equals;
    machine_callback_context_t machine_callbacks;
    *out_query = NULL;
    query = re_alloc(&engine->allocator, sizeof(*query));
    if (query == NULL) return RE_STATUS_OUT_OF_MEMORY;
    memset(query, 0, sizeof(*query));
    query->allocator = engine->allocator;
    query->engine = engine;
    query->facts = facts;
    query->max_depth = options->max_depth;
    query->max_solutions = options->max_solutions;
    /* An explicit goal("RuleName") query string names the same zero-argument
     * rule goal the condition-level form does; unwrap it so the paths below
     * see the bare rule name. Argument-bearing goal calls are not query goals. */
    if (goal.size >= 8u && memcmp(goal.data, "goal(\"", 6u) == 0 &&
        goal.data[goal.size - 1u] == ')' && goal.data[goal.size - 2u] == '"') {
        goal.data += 6u;
        goal.size -= 8u;
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
                trace_state_t direct_trace = {query, NULL, NULL, 0u, 0u, 0};
                environment_t direct_environment;
                memset(&direct_environment, 0, sizeof(direct_environment));
                if (bind_value(&query->allocator, &direct_environment, right, &actual) != RE_STATUS_OK ||
                    push_trace(&direct_trace, left) != RE_STATUS_OK ||
                    make_proof(query, &direct_environment, &direct_trace) != RE_STATUS_OK) {
                    environment_destroy(&query->allocator, &direct_environment);
                 re_free(&query->allocator, direct_trace.names);
                 re_free(&query->allocator, direct_trace.parents);
                    re_query_destroy(query);
                    return RE_STATUS_OUT_OF_MEMORY;
                }
                environment_destroy(&query->allocator, &direct_environment);
                re_free(&query->allocator, direct_trace.names);
                re_free(&query->allocator, direct_trace.parents);
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
    machine_callbacks.last_trace_index = (size_t)-1;
    status = re_backward_machine_goal_supported(engine, goal);
    if (status == RE_STATUS_OK) {
            re_goal_machine_callbacks_t callbacks = {
            &machine_callbacks, machine_make_proof, machine_push_trace, machine_reset_trace,
            machine_push_trace_parent
        };
        status = re_backward_machine_goal_run(query, goal, &callbacks);
        environment_destroy(&query->allocator, &environment);
        re_free(&query->allocator, trace.names);
        re_free(&query->allocator, trace.parents);
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
        environment_destroy(&query->allocator, &environment);
        re_free(&query->allocator, trace.names);
        re_free(&query->allocator, trace.parents);
        re_free(&query->allocator, query);
        return RE_STATUS_LIMIT;
    }
    frames = re_alloc(&query->allocator, (query->max_depth + 1u) * sizeof(*frames));
    if (frames == NULL) {
        environment_destroy(&query->allocator, &environment);
        re_free(&query->allocator, trace.names);
        re_free(&query->allocator, trace.parents);
        re_free(&query->allocator, query);
        return RE_STATUS_OUT_OF_MEMORY;
    }
    status = parameter_goal_execute(query, goal, NULL, 0u, &environment, 0u, frames, 0u,
                                      &trace, 1, NULL);
    if ((status == RE_STATUS_OK || status == RE_STATUS_NOT_FOUND) && trace.depth_exhausted)
        status = RE_STATUS_LIMIT;
    environment_destroy(&query->allocator, &environment);
    re_free(&query->allocator, frames);
    re_free(&query->allocator, trace.names);
    re_free(&query->allocator, trace.parents);
    if (status == RE_STATUS_LIMIT) query->result = RE_QUERY_LIMIT;
    else if (status != RE_STATUS_OK) { re_query_destroy(query); return status; }
    else query->result = query->proof_count != 0u ? RE_QUERY_PROVED : RE_QUERY_UNKNOWN;
    if (re_facts_subscribe(facts, invalidate, query, &query->subscription) != RE_STATUS_OK) {
        re_query_destroy(query); return RE_STATUS_OUT_OF_MEMORY;
    }
    *out_query = query;
    return query->result == RE_QUERY_LIMIT ? RE_STATUS_LIMIT : RE_STATUS_OK;
}

/* Shared proof graph glue (Task 14); the graph itself lives in proof_graph.c
 * and the design notes with the struct in re_internal.h. */

/* Builds the query object for a cache hit: clones of the entry's proofs plus
 * the same invalidation subscription the fresh paths wire, so a served query
 * self-invalidates on mutation exactly like a fresh one. */
static re_status_t graph_serve(re_engine_t *engine, re_facts_t *facts,
                               const re_query_options_t *options,
                               const re_proof_graph_entry_t *entry,
                               re_query_t **out_query) {
    re_query_t *query = re_alloc(&engine->allocator, sizeof(*query));
    size_t index;
    if (query == NULL) return RE_STATUS_OUT_OF_MEMORY;
    memset(query, 0, sizeof(*query));
    query->allocator = engine->allocator;
    query->engine = engine;
    query->facts = facts;
    query->max_depth = options->max_depth;
    query->max_solutions = options->max_solutions;
    query->result = entry->result;
    if (entry->proof_count != 0u) {
        query->proofs = re_alloc(&query->allocator, entry->proof_count * sizeof(*query->proofs));
        if (query->proofs == NULL) { re_free(&query->allocator, query); return RE_STATUS_OUT_OF_MEMORY; }
        memset(query->proofs, 0, entry->proof_count * sizeof(*query->proofs));
    }
    for (index = 0u; index < entry->proof_count; ++index) {
        if (re_proof_clone(&query->allocator, entry->proofs[index],
                           &query->proofs[index]) != RE_STATUS_OK) {
            re_query_destroy(query);
            return RE_STATUS_OUT_OF_MEMORY;
        }
        query->proof_count = index + 1u;
    }
    if (re_facts_subscribe(facts, invalidate, query, &query->subscription) != RE_STATUS_OK) {
        re_query_destroy(query);
        return RE_STATUS_OUT_OF_MEMORY;
    }
    *out_query = query;
    return RE_STATUS_OK;
}

/* Consults the cache for the normalized options: RE_STATUS_OK with a served
 * query on a hit, RE_STATUS_NOT_FOUND on a miss (stats counted in the graph).
 * The disable flag skips the consult entirely - no lookup, no stats. A NULL
 * graph after ensure means OOM; the query then runs uncached. */
static re_status_t graph_consult(re_engine_t *engine, re_facts_t *facts, re_string_t goal,
                                 const re_query_options_t *options, int sharing_disabled,
                                 re_query_t **out_query) {
    const re_proof_graph_entry_t *entry = NULL;
    if (sharing_disabled) return RE_STATUS_NOT_FOUND;
    re_proof_graph_ensure(engine);
    if (engine->proof_graph == NULL) return RE_STATUS_NOT_FOUND;
    if (re_proof_graph_lookup(engine->proof_graph, facts, goal, options,
                              engine->config_serial, &entry) != RE_STATUS_OK)
        return RE_STATUS_NOT_FOUND;
    return graph_serve(engine, facts, options, entry, out_query);
}

/* Stores a final result; LIMIT/UNKNOWN are never cached, and caching never
 * fails the query - an allocation failure just skips the store. */
static void graph_maybe_store(re_engine_t *engine, re_facts_t *facts, re_string_t goal,
                              const re_query_options_t *options, int sharing_disabled,
                              const re_query_t *query) {
    if (sharing_disabled) return;
    if (query->result != RE_QUERY_PROVED && query->result != RE_QUERY_DISPROVED) return;
    re_proof_graph_ensure(engine);
    if (engine->proof_graph == NULL) return;
    (void)re_proof_graph_store(engine->proof_graph, facts, goal, options,
                               engine->config_serial, query->result, query->proofs,
                               query->proof_count);
}

/* Dispatch layering (Task 13):
 *
 *   re_backward_machine_dispatch - argument/option normalization (including
 *       the struct_size versioning), the NOT prefix inversion, and strategy
 *       selection (this function)
 *   dispatch_once                - one full capped DFS pass over the goal
 *
 * The NOT prefix is handled BEFORE strategy selection so the inversion always
 * applies to the strategy-selected result of the subgoal: the nested call
 * re-enters this dispatcher with the caller's strategy and max_solutions=1.
 * Iterating a NOT query itself would be unsound - a shallow probe that cannot
 * yet prove the subgoal would invert to a false success.
 *
 * RE_QUERY_STRATEGY_BREADTH_FIRST / RE_QUERY_STRATEGY_ITERATIVE run
 * dispatch_once with max_depth = 1, 2, 4, 8, ... doubling up to the
 * configured max_depth; the first probe with at least one proof wins and its
 * query (proofs plus invalidation subscription) is returned, while earlier
 * probes are destroyed. Each probe is a fresh full run and backward queries
 * execute no actions, so re-probing is side-effect free. A winning probe that
 * cut deeper branches still reports RE_QUERY_PROVED: the cap is the
 * strategy's own mechanism, not a search failure. A probe that completes
 * without hitting its depth cap is authoritative for every deeper cap and is
 * returned as-is. Exhausting the configured max_depth or the 32-doubling
 * budget without a solution returns the last probe unchanged, reporting
 * RE_QUERY_LIMIT exactly as a plain DFS run at that depth would. */
re_status_t re_backward_machine_dispatch(re_engine_t *engine, re_facts_t *facts, re_string_t goal,
                                     const re_query_options_t *options, re_query_t **out_query) {
    re_query_t *query;
    re_status_t status;
    re_query_options_t normalized;
    uint32_t strategy = RE_QUERY_STRATEGY_DEPTH_FIRST;
    int sharing_disabled = 0;
    if (engine == NULL || facts == NULL || out_query == NULL || goal.data == NULL || goal.size == 0u) return RE_STATUS_INVALID_ARGUMENT;
    *out_query = NULL;
    /* Versioned-struct gate, mirroring the engine's other struct_size checks:
     * a caller compiled against the pre-Task-13 layout passes the smaller
     * struct_size and gets the defaults (DFS, shared proof graph ON); the
     * appended tail is read only when struct_size covers it. */
    if (options != NULL && options->struct_size < (uint32_t)offsetof(re_query_options_t, strategy))
        return RE_STATUS_INVALID_ARGUMENT;
    if (options != NULL && options->struct_size >= (uint32_t)offsetof(re_query_options_t, disable_shared_proof_graph))
        strategy = options->strategy;
    if (strategy > (uint32_t)RE_QUERY_STRATEGY_ITERATIVE) return RE_STATUS_INVALID_ARGUMENT;
    /* Task 14 opt-out, gated on the full appended tail (absent/0 = shared
     * proof graph ON, 1 = OFF). */
    if (options != NULL && options->struct_size >= (uint32_t)sizeof(re_query_options_t) &&
        options->disable_shared_proof_graph != 0u)
        sharing_disabled = 1;
    normalized.struct_size = (uint32_t)sizeof(normalized);
    normalized.max_depth = options != NULL && options->max_depth != 0u ? options->max_depth : 64u;
    normalized.max_solutions = options != NULL && options->max_solutions != 0u ? options->max_solutions : 1u;
    normalized.strategy = strategy;
    normalized.disable_shared_proof_graph = (uint32_t)sharing_disabled;
    if (options != NULL && options->max_depth == 0u) {
        query = re_alloc(&engine->allocator, sizeof(*query));
        if (query == NULL) return RE_STATUS_OUT_OF_MEMORY;
        memset(query, 0, sizeof(*query));
        query->allocator = engine->allocator;
        query->engine = engine;
        query->facts = facts;
        query->max_depth = normalized.max_depth;
        query->max_solutions = normalized.max_solutions;
        query->result = RE_QUERY_LIMIT;
        *out_query = query;
        return RE_STATUS_LIMIT;
    }
    /* Shared proof graph (Task 14): consulted here - after the struct_size
     * versioning and BEFORE the NOT/strategy work - because this is the layer
     * where the final result is known. The NOT recursion below re-enters this
     * dispatcher, so a cached entry always holds the strategy-selected,
     * negation-resolved result for its exact goal text; the subgoal
     * participates under its own key (its normalized options match a direct
     * query's, so "NOT X" and a later direct "X" share the "X" entry, and
     * double negation caches "X", "NOT X", "NOT NOT X" as independent final
     * results - none can poison another). A hit is served as a fresh query
     * object with cloned proofs and its own invalidation subscription, so it
     * self-invalidates on mutation exactly like a fresh run. */
    status = graph_consult(engine, facts, goal, &normalized, sharing_disabled, &query);
    if (status == RE_STATUS_OK) { *out_query = query; return RE_STATUS_OK; }
    if (status != RE_STATUS_NOT_FOUND) return status;
    /* Query-level negation-as-failure: a leading "NOT" followed by whitespace
     * wraps the remainder as a subgoal run through this same dispatch with
     * max_solutions=1. Only the prefix form exists (`!(...)` is not a query
     * goal) and there is no stratification; nested "NOT NOT" unwraps one level
     * per recursion. A subgoal that exhausts its budget reports RE_QUERY_LIMIT
     * unchanged: inverting a limited search into a success would be unsound. */
    if (goal.size > 3u && memcmp(goal.data, "NOT", 3u) == 0 && goal_space(goal.data[3])) {
        re_string_t subgoal = {goal.data + 3u, goal.size - 3u};
        re_query_options_t nested;
        const re_query_options_t *nested_options = options;
        re_query_t *subquery = NULL;
        while (subgoal.size != 0u && goal_space(subgoal.data[0])) { ++subgoal.data; --subgoal.size; }
        if (subgoal.size == 0u) return RE_STATUS_INVALID_ARGUMENT;
        query = re_alloc(&engine->allocator, sizeof(*query));
        if (query == NULL) return RE_STATUS_OUT_OF_MEMORY;
        memset(query, 0, sizeof(*query));
        query->allocator = engine->allocator;
        query->engine = engine;
        query->facts = facts;
        query->max_depth = normalized.max_depth;
        query->max_solutions = normalized.max_solutions;
        if (options != NULL) {
            /* The caller's struct may be the smaller pre-Task-13 layout, so
             * copy the normalized values instead of `*options`; the subgoal
             * keeps the caller's strategy so the inversion below applies to
             * the strategy-selected result. */
            nested = normalized;
            nested.max_solutions = 1u;
            nested_options = &nested;
        }
        status = re_backward_machine_dispatch(engine, facts, subgoal, nested_options, &subquery);
        if (status != RE_STATUS_OK && status != RE_STATUS_LIMIT) {
            re_free(&query->allocator, query);
            return status;
        }
        if (subquery->result == RE_QUERY_LIMIT) {
            query->result = RE_QUERY_LIMIT;
        } else if (subquery->result == RE_QUERY_PROVED) {
            query->result = RE_QUERY_DISPROVED;
        } else {
            trace_state_t not_trace = {query, NULL, NULL, 0u, 0u, 0};
            environment_t not_environment = {NULL, 0u};
            if (push_trace(&not_trace, goal) != RE_STATUS_OK ||
                make_proof(query, &not_environment, &not_trace) != RE_STATUS_OK) {
                re_free(&query->allocator, not_trace.names);
                re_free(&query->allocator, not_trace.parents);
                re_query_destroy(subquery);
                re_query_destroy(query);
                return RE_STATUS_OUT_OF_MEMORY;
            }
            re_free(&query->allocator, not_trace.names);
            re_free(&query->allocator, not_trace.parents);
            query->result = RE_QUERY_PROVED;
        }
        re_query_destroy(subquery);
        graph_maybe_store(engine, facts, goal, &normalized, sharing_disabled, query);
        if (re_facts_subscribe(facts, invalidate, query, &query->subscription) != RE_STATUS_OK) {
            re_query_destroy(query); return RE_STATUS_OUT_OF_MEMORY;
        }
        *out_query = query;
        return query->result == RE_QUERY_LIMIT ? RE_STATUS_LIMIT : RE_STATUS_OK;
    }
    if (strategy == RE_QUERY_STRATEGY_DEPTH_FIRST) {
        status = dispatch_once(engine, facts, goal, &normalized, out_query);
        if (status == RE_STATUS_OK && *out_query != NULL)
            graph_maybe_store(engine, facts, goal, &normalized, sharing_disabled, *out_query);
        return status;
    }
    {
        re_query_options_t probe_options = normalized;
        size_t cap = 1u;
        size_t doublings = 0u;
        for (;;) {
            re_query_t *probe = NULL;
            re_status_t probe_status;
            probe_options.max_depth = cap;
            probe_status = dispatch_once(engine, facts, goal, &probe_options, &probe);
            if (probe == NULL) return probe_status;
            if (probe->proof_count != 0u) {
                if (probe->result == RE_QUERY_LIMIT) probe->result = RE_QUERY_PROVED;
                graph_maybe_store(engine, facts, goal, &normalized, sharing_disabled, probe);
                *out_query = probe;
                return RE_STATUS_OK;
            }
            if (probe_status == RE_STATUS_OK || cap >= normalized.max_depth) {
                *out_query = probe;
                return probe_status;
            }
            if (doublings == 32u) {
                probe->result = RE_QUERY_LIMIT;
                *out_query = probe;
                return RE_STATUS_LIMIT;
            }
            re_query_destroy(probe);
            ++doublings;
            if (cap > normalized.max_depth / 2u) cap = normalized.max_depth;
            else cap *= 2u;
        }
    }
}

re_status_t re_backward_query_create(re_engine_t *engine, re_facts_t *facts, re_string_t goal,
                                     const re_query_options_t *options, re_query_t **out_query) {
    return re_backward_machine_run(engine, facts, goal, options, out_query);
}

/* Documented cap for the internal bounded query run by
 * re_engine_query_aggregate (rule_engine.h). */
#define RE_AGGREGATE_MAX_SOLUTIONS 1024u

/* Query aggregation lives here (not query.c/extensions.c) because backward.c
 * owns query semantics; the function itself only composes the public query
 * API. The fold reuses re_accumulator_evaluate's coercion rules: INT64 and
 * DOUBLE are numeric, anything else is rejected; the result stays INT64 only
 * when every folded value was INT64. FIRST/LAST copy the binding value of the
 * first/last carrier; proof strings are freed with the internal query, so a
 * STRING result reports RE_STATUS_NOT_SUPPORTED instead of dangling. */
re_status_t re_engine_query_aggregate(re_engine_t *engine, re_facts_t *facts,
                                      re_accumulator_kind_t kind, re_string_t field,
                                      re_string_t pattern, re_value_t *out_value) {
    re_query_options_t options;
    re_query_t *query = NULL;
    re_status_t status;
    size_t solutions = 0u;
    size_t folded = 0u;
    int all_int64 = 1;
    int64_t int_accumulator = 0;
    double double_accumulator = 0.0;
    re_value_t carried;
    if (engine == NULL || facts == NULL || out_value == NULL ||
        pattern.data == NULL || pattern.size == 0u) return RE_STATUS_INVALID_ARGUMENT;
    if (kind < RE_ACCUM_COUNT || kind > RE_ACCUM_LAST) return RE_STATUS_INVALID_ARGUMENT;
    if (kind != RE_ACCUM_COUNT && field.data == NULL) return RE_STATUS_INVALID_ARGUMENT;
    carried.type = RE_VALUE_NONE;
    carried.as.int64_value = 0;
    options.struct_size = sizeof(options);
    options.max_depth = 64u;
    options.max_solutions = RE_AGGREGATE_MAX_SOLUTIONS;
    options.strategy = RE_QUERY_STRATEGY_DEPTH_FIRST;
    options.disable_shared_proof_graph = 0u;
    status = re_engine_query_bounded(engine, facts, pattern, &options, &query);
    if (status != RE_STATUS_OK) {
        /* A depth-exhausted search reports RE_STATUS_LIMIT with the query still
         * caller-owned; propagating beats folding a partial solution set. */
        if (query != NULL) re_query_destroy(query);
        return status;
    }
    for (;;) {
        re_proof_t *proof = NULL;
        re_query_binding_t binding;
        size_t index;
        size_t binding_count;
        int found = 0;
        status = re_query_next(query, &proof);
        if (status == RE_STATUS_NOT_FOUND) break;
        if (status != RE_STATUS_OK) { re_query_destroy(query); return status; }
        ++solutions;
        memset(&binding, 0, sizeof(binding));
        if (kind != RE_ACCUM_COUNT) {
            binding_count = re_proof_binding_count(proof);
            for (index = 0u; index < binding_count; ++index) {
                if (re_proof_binding_get(proof, index, &binding) != RE_STATUS_OK) break;
                if (binding.name.size == field.size &&
                    (field.size == 0u || memcmp(binding.name.data, field.data, field.size) == 0)) {
                    found = 1;
                    break;
                }
            }
        }
        if (found) {
            ++folded;
            if (kind == RE_ACCUM_FIRST) {
                if (folded == 1u) carried = binding.value;
            } else if (kind == RE_ACCUM_LAST) {
                carried = binding.value;
            } else {
                double value;
                if (binding.value.type == RE_VALUE_INT64) value = (double)binding.value.as.int64_value;
                else if (binding.value.type == RE_VALUE_DOUBLE) value = binding.value.as.double_value;
                else {
                    re_proof_destroy(proof);
                    re_query_destroy(query);
                    return RE_STATUS_INVALID_ARGUMENT;
                }
                if (binding.value.type != RE_VALUE_INT64) all_int64 = 0;
                if (folded == 1u) {
                    if (binding.value.type == RE_VALUE_INT64)
                        int_accumulator = binding.value.as.int64_value;
                    double_accumulator = value;
                } else if (kind == RE_ACCUM_SUM || kind == RE_ACCUM_AVERAGE) {
                    if (binding.value.type == RE_VALUE_INT64)
                        int_accumulator += binding.value.as.int64_value;
                    double_accumulator += value;
                } else if (kind == RE_ACCUM_MIN) {
                    if (binding.value.type == RE_VALUE_INT64 &&
                        binding.value.as.int64_value < int_accumulator)
                        int_accumulator = binding.value.as.int64_value;
                    if (value < double_accumulator) double_accumulator = value;
                } else {
                    if (binding.value.type == RE_VALUE_INT64 &&
                        binding.value.as.int64_value > int_accumulator)
                        int_accumulator = binding.value.as.int64_value;
                    if (value > double_accumulator) double_accumulator = value;
                }
            }
        }
        re_proof_destroy(proof);
    }
    re_query_destroy(query);
    /* Reaching the cap cannot be told apart from a truncated solution set, so
     * it reports RE_STATUS_LIMIT instead of a silently partial fold. */
    if (solutions == RE_AGGREGATE_MAX_SOLUTIONS) return RE_STATUS_LIMIT;
    if (kind == RE_ACCUM_COUNT) {
        out_value->type = RE_VALUE_INT64;
        out_value->as.int64_value = (int64_t)solutions;
        return RE_STATUS_OK;
    }
    if (folded == 0u) return RE_STATUS_NOT_FOUND;
    if (kind == RE_ACCUM_FIRST || kind == RE_ACCUM_LAST) {
        if (carried.type == RE_VALUE_STRING) return RE_STATUS_NOT_SUPPORTED;
        *out_value = carried;
        return RE_STATUS_OK;
    }
    if (kind == RE_ACCUM_AVERAGE) {
        out_value->type = RE_VALUE_DOUBLE;
        out_value->as.double_value = double_accumulator / (double)folded;
        return RE_STATUS_OK;
    }
    if (all_int64) {
        out_value->type = RE_VALUE_INT64;
        out_value->as.int64_value = int_accumulator;
    } else {
        out_value->type = RE_VALUE_DOUBLE;
        out_value->as.double_value = double_accumulator;
    }
    return RE_STATUS_OK;
}
