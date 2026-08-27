#include "ir.h"
#include <string.h>

static re_ir_id_t id_for(size_t kind, size_t index, const char *name, size_t size) {
    re_ir_id_t hash = UINT64_C(1469598103934665603);
    size_t i;
    hash ^= (re_ir_id_t)kind; hash *= UINT64_C(1099511628211);
    hash ^= (re_ir_id_t)index; hash *= UINT64_C(1099511628211);
    for (i = 0u; i < size; ++i) { hash ^= (unsigned char)name[i]; hash *= UINT64_C(1099511628211); }
    return hash;
}
static re_status_t grow(const re_allocator_impl_t *a, void **memory, size_t count,
                        size_t size) {
    void *grown;
    if (count == 0u || size > (size_t)-1 / count) return RE_STATUS_LIMIT;
    grown = re_realloc(a, *memory, count * size);
    if (grown == NULL) return RE_STATUS_OUT_OF_MEMORY;
    *memory = grown; return RE_STATUS_OK;
}
static re_status_t add_term_node(re_ir_program_t *ir, const re_operand_t *operand,
                                 size_t *out) {
    re_ir_term_t *term;
    size_t index = ir->term_count;
    if (index == (size_t)-1) return RE_STATUS_LIMIT;
    {
        re_status_t status = grow(&ir->allocator, (void **)&ir->terms, index + 1u, sizeof(*term));
        if (status != RE_STATUS_OK) return status;
    }
    term = &ir->terms[index]; memset(term, 0, sizeof(*term));
    ++ir->term_count;
    term->id = id_for(1u, index, operand->fact_name != NULL ? operand->fact_name : "", operand->fact_name_size);
    term->span.end = ir->source_size; term->kind = RE_IR_TERM_NONE;
    term->value = operand->value;
    if (term->value.type == RE_VALUE_STRING) {
        re_string_t source_string = term->value.as.string;
        term->value.as.string.data = NULL;
        if (re_copy_string(&ir->allocator, source_string,
                           (char **)&term->value.as.string.data) != RE_STATUS_OK)
            return RE_STATUS_OUT_OF_MEMORY;
    }
    if (operand->fact_name != NULL) {
        re_status_t status = re_copy_string(&ir->allocator,
            (re_string_t){operand->fact_name, operand->fact_name_size}, &term->name);
        if (status != RE_STATUS_OK) return status;
    } else if (operand->function_name != NULL) {
        re_status_t status = re_copy_string(&ir->allocator,
            (re_string_t){operand->function_name, operand->function_name_size}, &term->name);
        if (status != RE_STATUS_OK) return status;
    }
    term->name_size = operand->fact_name != NULL ? operand->fact_name_size : operand->function_name_size;
    if (operand->kind == RE_OPERAND_FACT || operand->kind == RE_OPERAND_VARIABLE) term->kind = RE_IR_TERM_FACT;
    if (operand->kind == RE_OPERAND_FUNCTION) term->kind = RE_IR_TERM_FUNCTION;
    if (operand->kind == RE_OPERAND_ARITHMETIC) term->kind = RE_IR_TERM_ARITHMETIC;
    if (operand->kind == RE_OPERAND_ARRAY) term->kind = RE_IR_TERM_ARRAY;
    if (operand->kind == RE_OPERAND_LITERAL) {
        term->kind = operand->value.type == RE_VALUE_BOOL ? RE_IR_TERM_BOOL :
            operand->value.type == RE_VALUE_INT64 ? RE_IR_TERM_INT64 :
            operand->value.type == RE_VALUE_DOUBLE ? RE_IR_TERM_DOUBLE :
            operand->value.type == RE_VALUE_STRING ? RE_IR_TERM_STRING : RE_IR_TERM_NONE;
        term->name = NULL; term->name_size = 0u;
    }
    if (operand->kind == RE_OPERAND_GOAL_CALL) {
        re_free(&ir->allocator, term->name); term->name = NULL;
        {
            re_status_t status = re_copy_string(&ir->allocator,
                (re_string_t){operand->goal_name, operand->goal_name_size}, &term->name);
            if (status != RE_STATUS_OK) return status;
        }
        term->name_size = operand->goal_name_size; term->kind = RE_IR_TERM_GOAL;
    }
    term->first_argument = operand->argument_count == 0u ? SIZE_MAX : ir->term_count;
    term->argument_count = operand->argument_count;
    if (operand->argument_count != 0u) {
        if (operand->argument_count > (size_t)-1 / sizeof(*term->argument_indices)) return RE_STATUS_LIMIT;
        term->argument_indices = re_alloc(&ir->allocator, operand->argument_count * sizeof(*term->argument_indices));
        if (term->argument_indices == NULL) return RE_STATUS_OUT_OF_MEMORY;
    }
    term->arithmetic_operator = operand->arithmetic_operator;
    *out = index;
    return RE_STATUS_OK;
}
typedef struct term_frame_t {
    const re_operand_t *operand;
    size_t term_index;
    size_t next_argument;
} term_frame_t;
static re_status_t add_term(re_ir_program_t *ir, const re_operand_t *operand,
                            size_t *out) {
    term_frame_t *frames = NULL;
    size_t count = 0u, capacity = 0u;
    re_status_t status = RE_STATUS_OK;
    size_t root;
    status = add_term_node(ir, operand, &root);
    if (status != RE_STATUS_OK) return status;
    for (;;) {
        term_frame_t *frame;
        if (count == 0u || frames[count - 1u].next_argument < frames[count - 1u].operand->argument_count) {
            const re_operand_t *child;
            size_t child_index;
            if (count == 0u) {
                child = operand;
                child_index = root;
            } else {
                frame = &frames[count - 1u];
                child = &frame->operand->arguments[frame->next_argument];
                status = add_term_node(ir, child, &child_index);
                if (status != RE_STATUS_OK) break;
                ir->terms[frame->term_index].argument_indices[frame->next_argument++] = child_index;
            }
            if (child->argument_count == 0u) {
                if (count == 0u) break;
                continue;
            }
            if (count == capacity) {
                size_t next = capacity == 0u ? 8u : capacity * 2u;
                term_frame_t *grown;
                if (next < capacity || next > (size_t)-1 / sizeof(*grown)) { status = RE_STATUS_LIMIT; break; }
                grown = re_realloc(&ir->allocator, frames, next * sizeof(*grown));
                if (grown == NULL) { status = RE_STATUS_OUT_OF_MEMORY; break; }
                frames = grown; capacity = next;
            }
            frames[count].operand = child;
            frames[count].term_index = child_index;
            frames[count].next_argument = 0u;
            ++count;
            continue;
        }
        --count;
        if (count == 0u) break;
    }
    re_free(&ir->allocator, frames);
    if (status == RE_STATUS_OK) *out = root;
    return status;
}
typedef struct expr_frame_t {
    const re_expr_t *expr;
    size_t index;
    size_t child;
    unsigned phase;
} expr_frame_t;

static re_status_t add_expr_node(re_ir_program_t *ir, const re_expr_t *expr,
                                 size_t *out) {
    re_ir_expr_t *item;
    size_t index = ir->expr_count;
    re_status_t status;
    if (index == (size_t)-1) return RE_STATUS_LIMIT;
    status = grow(&ir->allocator, (void **)&ir->exprs, index + 1u, sizeof(*item));
    if (status != RE_STATUS_OK) return status;
    item = &ir->exprs[index];
    memset(item, 0, sizeof(*item));
    item->id = id_for(2u, index, "", 0u);
    item->kind = expr->kind;
    item->compare = expr->compare;
    item->span.end = ir->source_size;
    ++ir->expr_count;
    *out = index;
    return RE_STATUS_OK;
}

static re_status_t add_expr(re_ir_program_t *ir, const re_expr_t *expr, size_t *out) {
    expr_frame_t *frames = NULL;
    size_t count = 0u;
    size_t capacity = 0u;
    size_t result = SIZE_MAX;
    re_status_t status;
    if (expr == NULL || out == NULL) return RE_STATUS_INVALID_ARGUMENT;
    status = add_expr_node(ir, expr, &result);
    if (status != RE_STATUS_OK) return status;
    for (;;) {
        expr_frame_t *frame;
        if (count == 0u) {
            if (capacity == 0u) {
                capacity = 8u;
                frames = re_alloc(&ir->allocator, capacity * sizeof(*frames));
                if (frames == NULL) return RE_STATUS_OUT_OF_MEMORY;
            }
            frames[count++] = (expr_frame_t){expr, result, SIZE_MAX, 0u};
        }
        frame = &frames[count - 1u];
        if (frame->phase == 0u) {
            if (frame->expr->kind == RE_EXPR_COMPARE) {
                status = add_term(ir, &frame->expr->left, &ir->exprs[frame->index].left);
                if (status == RE_STATUS_OK)
                    status = add_term(ir, &frame->expr->right, &ir->exprs[frame->index].right);
                if (status != RE_STATUS_OK) break;
                frame->phase = 3u;
            } else if (frame->expr->kind == RE_EXPR_TRUE || frame->expr->kind == RE_EXPR_FALSE) {
                frame->phase = 3u;
            } else {
                const re_expr_t *current_expr = frame->expr;
                size_t child_index;
                frame->phase = 1u;
                if (count == capacity) {
                    size_t next = capacity > (size_t)-1 / 2u ? 0u : capacity * 2u;
                    expr_frame_t *grown;
                    if (next == 0u || next > (size_t)-1 / sizeof(*grown)) { status = RE_STATUS_LIMIT; break; }
                    grown = re_realloc(&ir->allocator, frames, next * sizeof(*grown));
                    if (grown == NULL) { status = RE_STATUS_OUT_OF_MEMORY; break; }
                    frames = grown;
                    capacity = next;
                }
                status = add_expr_node(ir, current_expr->first, &child_index);
                if (status != RE_STATUS_OK) break;
                frames[count - 1u].child = child_index;
                frames[count++] = (expr_frame_t){current_expr->first, child_index, SIZE_MAX, 0u};
                continue;
            }
        }
        if (frame->phase == 1u) {
            const re_expr_t *current_expr = frame->expr;
            ir->exprs[frame->index].first = frame->child;
            if (current_expr->kind == RE_EXPR_NOT) {
                frame->phase = 3u;
            } else {
                size_t child_index;
                frame->phase = 2u;
                if (count == capacity) {
                    size_t next = capacity > (size_t)-1 / 2u ? 0u : capacity * 2u;
                    expr_frame_t *grown;
                    if (next == 0u || next > (size_t)-1 / sizeof(*grown)) { status = RE_STATUS_LIMIT; break; }
                    grown = re_realloc(&ir->allocator, frames, next * sizeof(*grown));
                    if (grown == NULL) { status = RE_STATUS_OUT_OF_MEMORY; break; }
                    frames = grown;
                    capacity = next;
                }
                status = add_expr_node(ir, current_expr->second, &child_index);
                if (status != RE_STATUS_OK) break;
                frames[count - 1u].child = child_index;
                frames[count++] = (expr_frame_t){current_expr->second, child_index, SIZE_MAX, 0u};
                continue;
            }
        }
        if (frame->phase == 2u) ir->exprs[frame->index].second = frame->child;
        result = frame->index;
        --count;
        if (count == 0u) break;
        frame = &frames[count - 1u];
        frame->child = result;
        if (frame->phase == 1u) continue;
        if (frame->phase == 2u) continue;
    }
    re_free(&ir->allocator, frames);
    if (status != RE_STATUS_OK) return status;
    *out = result;
    return RE_STATUS_OK;
}
re_status_t re_ir_compile(const re_program_t *program, re_ir_program_t **out) {
    re_ir_program_t *ir; size_t i, j;
    re_status_t status = RE_STATUS_OK;
    if (program == NULL || out == NULL) return RE_STATUS_INVALID_ARGUMENT; *out = NULL;
    ir = re_alloc(&program->allocator, sizeof(*ir)); if (ir == NULL) return RE_STATUS_OUT_OF_MEMORY;
    memset(ir, 0, sizeof(*ir)); ir->allocator = program->allocator; ir->source_size = program->source_size;
    for (i = 0u; i < program->module_count; ++i) {
        re_ir_module_t *module; status = grow(&ir->allocator, (void **)&ir->modules, ir->module_count + 1u, sizeof(*module)); if (status != RE_STATUS_OK) goto fail;
        module = &ir->modules[ir->module_count]; memset(module, 0, sizeof(*module)); module->id = id_for(3u, i, program->modules[i].name, program->modules[i].name_size); module->name = i; module->import_count = program->modules[i].import_count; module->export_all = program->modules[i].export_all; ++ir->module_count;
    }
    for (i = 0u; i < program->rule_count; ++i) {
        re_ir_rule_t *rule; const re_rule_t *source = &program->rules[i];
        re_operand_t rule_name;
        status = grow(&ir->allocator, (void **)&ir->rules, ir->rule_count + 1u, sizeof(*rule)); if (status != RE_STATUS_OK) goto fail;
        rule = &ir->rules[ir->rule_count]; memset(rule, 0, sizeof(*rule)); rule->id = id_for(4u, i, source->name, source->name_size); rule->salience = source->salience; rule->module = source->module_index < program->module_count ? source->module_index : SIZE_MAX; rule->first_action = ir->action_count; ++ir->rule_count;
        status = add_expr(ir, source->condition, &rule->condition); if (status != RE_STATUS_OK) goto fail;
        memset(&rule_name, 0, sizeof(rule_name)); rule_name.kind = RE_OPERAND_FACT; rule_name.fact_name = source->name; rule_name.fact_name_size = source->name_size;
        status = add_term(ir, &rule_name, &rule->name); if (status != RE_STATUS_OK) goto fail;
        for (j = 0u; j < source->action_count; ++j) { re_ir_action_t *action; re_operand_t target; memset(&target, 0, sizeof(target)); target.kind = RE_OPERAND_FACT; target.fact_name = source->actions[j].name; target.fact_name_size = source->actions[j].name_size; status = grow(&ir->allocator, (void **)&ir->actions, ir->action_count + 1u, sizeof(*action)); if (status != RE_STATUS_OK) goto fail; action = &ir->actions[ir->action_count]; memset(action, 0, sizeof(*action)); action->id = id_for(5u, ir->action_count, source->actions[j].name, source->actions[j].name_size); action->append = source->actions[j].append; status = add_term(ir, &target, &action->target); if (status != RE_STATUS_OK) goto fail; status = add_term(ir, &source->actions[j].value, &action->value); if (status != RE_STATUS_OK) goto fail; ++ir->action_count; }
        rule->action_count = source->action_count;
    }
    if (ir->rule_count != 0u) { if (ir->rule_count > (size_t)-1 / sizeof(*ir->spans)) { status = RE_STATUS_LIMIT; goto fail; } ir->spans = re_alloc(&ir->allocator, ir->rule_count * sizeof(*ir->spans)); if (ir->spans == NULL) { status = RE_STATUS_OUT_OF_MEMORY; goto fail; } ir->span_count = ir->rule_count; for (i = 0u; i < ir->span_count; ++i) ir->spans[i] = (re_ir_span_t){0u, program->source_size}; }
    *out = ir; return RE_STATUS_OK;
fail: re_ir_destroy(ir); return status;
}
void re_ir_destroy(re_ir_program_t *ir) { size_t i; if (ir == NULL) return; for (i = 0u; i < ir->term_count; ++i) { re_free(&ir->allocator, ir->terms[i].name); re_free(&ir->allocator, ir->terms[i].argument_indices); if (ir->terms[i].value.type == RE_VALUE_STRING) re_free(&ir->allocator, (void *)ir->terms[i].value.as.string.data); } re_free(&ir->allocator, ir->strings); re_free(&ir->allocator, ir->spans); re_free(&ir->allocator, ir->actions); re_free(&ir->allocator, ir->rules); re_free(&ir->allocator, ir->modules); re_free(&ir->allocator, ir->exprs); re_free(&ir->allocator, ir->terms); re_free(&ir->allocator, ir); }
