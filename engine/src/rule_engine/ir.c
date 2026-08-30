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
            operand->value.type == RE_VALUE_STRING ? RE_IR_TERM_STRING :
            operand->value.type == RE_VALUE_NULL ? RE_IR_TERM_NULL : RE_IR_TERM_NONE;
        term->name = NULL; term->name_size = 0u;
    }
    if (operand->kind == RE_OPERAND_FUNCTION && operand->fact_name != NULL) {
        /* $Receiver.method(...) operand: dotted "Receiver.method" term name. */
        char *dotted;
        size_t dotted_size;
        if (operand->function_name_size > (size_t)-3 ||
            operand->fact_name_size > (size_t)-3 - operand->function_name_size)
            return RE_STATUS_LIMIT;
        dotted_size = operand->fact_name_size + 1u + operand->function_name_size;
        dotted = re_alloc(&ir->allocator, dotted_size + 1u);
        if (dotted == NULL) return RE_STATUS_OUT_OF_MEMORY;
        memcpy(dotted, operand->fact_name, operand->fact_name_size);
        dotted[operand->fact_name_size] = '.';
        memcpy(dotted + operand->fact_name_size + 1u, operand->function_name,
               operand->function_name_size);
        dotted[dotted_size] = '\0';
        re_free(&ir->allocator, term->name);
        term->name = dotted;
        term->name_size = dotted_size;
        term->kind = RE_IR_TERM_METHOD_CALL;
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

/* A6: deep-copies the parser accumulate payload into the IR expr. The expr
 * was zeroed on creation and already counted, so a partial copy is released
 * by re_ir_destroy like any other expr payload. */
static re_status_t accumulate_copy_payload(re_ir_program_t *ir, const re_expr_t *expr,
                                           re_ir_expr_t *item) {
    size_t i;
    re_status_t status = re_copy_string(&ir->allocator,
        (re_string_t){expr->accumulate_type, expr->accumulate_type_size}, &item->accumulate_type);
    if (status != RE_STATUS_OK) return status;
    item->accumulate_type_size = expr->accumulate_type_size;
    if (expr->accumulate_field != NULL) {
        status = re_copy_string(&ir->allocator,
            (re_string_t){expr->accumulate_field, expr->accumulate_field_size}, &item->accumulate_field);
        if (status != RE_STATUS_OK) return status;
        item->accumulate_field_size = expr->accumulate_field_size;
    }
    status = re_copy_string(&ir->allocator,
        (re_string_t){expr->accumulate_func_name, expr->accumulate_func_name_size}, &item->accumulate_func_name);
    if (status != RE_STATUS_OK) return status;
    item->accumulate_func_name_size = expr->accumulate_func_name_size;
    if (expr->accumulate_condition_count != 0u) {
        if (expr->accumulate_condition_count > (size_t)-1 / sizeof(*item->accumulate_conditions)) return RE_STATUS_LIMIT;
        item->accumulate_conditions = re_alloc(&ir->allocator,
            expr->accumulate_condition_count * sizeof(*item->accumulate_conditions));
        if (item->accumulate_conditions == NULL) return RE_STATUS_OUT_OF_MEMORY;
        memset(item->accumulate_conditions, 0,
               expr->accumulate_condition_count * sizeof(*item->accumulate_conditions));
        for (i = 0u; i < expr->accumulate_condition_count; ++i) {
            status = re_copy_string(&ir->allocator,
                (re_string_t){expr->accumulate_conditions[i], strlen(expr->accumulate_conditions[i])},
                &item->accumulate_conditions[i]);
            if (status != RE_STATUS_OK) return status;
        }
    }
    item->accumulate_condition_count = expr->accumulate_condition_count;
    item->accumulate_func = expr->accumulate_func;
    return RE_STATUS_OK;
}

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
    item->multifield = expr->multifield;
    item->nested = (expr->first != NULL &&
                    (expr->kind == RE_EXPR_EXISTS || expr->kind == RE_EXPR_FORALL)) ? 1 : 0;
    ++ir->expr_count;
    if (expr->kind == RE_EXPR_ACCUMULATE) {
        status = accumulate_copy_payload(ir, expr, item);
        if (status != RE_STATUS_OK) return status;
    }
    if (expr->kind == RE_EXPR_TYPED) {
        /* A9: copy the declared type name; on error the partial copy is
         * released by re_ir_destroy like any other expr payload. */
        status = re_copy_string(&ir->allocator,
            (re_string_t){expr->typed_type, expr->typed_type_size}, &item->typed_type);
        if (status != RE_STATUS_OK) return status;
        item->typed_type_size = expr->typed_type_size;
    }
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
            if (frame->expr->kind == RE_EXPR_MULTIFIELD) {
                /* A5: the array path is always a term; only `count` carries a
                 * (numeric literal) right term - the bare predicates leave
                 * right at the SIZE_MAX sentinel. */
                status = add_term(ir, &frame->expr->left, &ir->exprs[frame->index].left);
                if (status == RE_STATUS_OK) {
                    if (frame->expr->multifield == RE_MULTIFIELD_COUNT)
                        status = add_term(ir, &frame->expr->right, &ir->exprs[frame->index].right);
                    else
                        ir->exprs[frame->index].right = SIZE_MAX;
                }
                if (status != RE_STATUS_OK) break;
                frame->phase = 3u;
            } else if (frame->expr->kind == RE_EXPR_TEST) {
                /* A9 test(f(args)): the function call is the only term; right
                 * keeps the SIZE_MAX sentinel like the bare multifield forms. */
                status = add_term(ir, &frame->expr->left, &ir->exprs[frame->index].left);
                if (status == RE_STATUS_OK) ir->exprs[frame->index].right = SIZE_MAX;
                if (status != RE_STATUS_OK) break;
                frame->phase = 3u;
            } else if (frame->expr->kind == RE_EXPR_COMPARE ||
                ((frame->expr->kind == RE_EXPR_EXISTS || frame->expr->kind == RE_EXPR_FORALL) &&
                 frame->expr->first == NULL)) {
                status = add_term(ir, &frame->expr->left, &ir->exprs[frame->index].left);
                if (status == RE_STATUS_OK)
                    status = add_term(ir, &frame->expr->right, &ir->exprs[frame->index].right);
                if (status != RE_STATUS_OK) break;
                frame->phase = 3u;
            } else if (frame->expr->kind == RE_EXPR_TRUE || frame->expr->kind == RE_EXPR_FALSE ||
                       frame->expr->kind == RE_EXPR_ACCUMULATE) {
                /* TRUE/FALSE and the A6 accumulate node carry no child
                 * expressions or terms (the payload was copied by
                 * add_expr_node). */
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
            if (current_expr->kind == RE_EXPR_NOT || current_expr->kind == RE_EXPR_EXISTS ||
                current_expr->kind == RE_EXPR_FORALL || current_expr->kind == RE_EXPR_TYPED) {
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
    if (program == NULL || out == NULL) return RE_STATUS_INVALID_ARGUMENT;
    *out = NULL;
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
        for (j = 0u; j < source->action_count; ++j) {
            re_ir_action_t *action; re_operand_t target;
            memset(&target, 0, sizeof(target));
            target.kind = RE_OPERAND_FACT; target.fact_name = source->actions[j].name; target.fact_name_size = source->actions[j].name_size;
            status = grow(&ir->allocator, (void **)&ir->actions, ir->action_count + 1u, sizeof(*action)); if (status != RE_STATUS_OK) goto fail;
            action = &ir->actions[ir->action_count]; memset(action, 0, sizeof(*action));
            action->id = id_for(5u, ir->action_count, source->actions[j].name, source->actions[j].name_size);
            action->append = source->actions[j].append;
            ++ir->action_count;
            if (source->actions[j].append == RE_ACTION_METHOD_CALL) {
                action->kind = RE_IR_ACTION_METHOD_CALL; action->append = 0;
                status = re_copy_string(&ir->allocator,
                    (re_string_t){source->actions[j].value.function_name,
                                  source->actions[j].value.function_name_size},
                    &action->method_name);
                if (status != RE_STATUS_OK) goto fail;
                action->method_name_size = source->actions[j].value.function_name_size;
            }
            if (source->actions[j].append == RE_ACTION_BUILTIN_CALL) {
                /* A8 bare `name(args)` action: the whole call (name plus
                 * argument terms) becomes the target FUNCTION term; value is
                 * unused. */
                action->kind = RE_IR_ACTION_BUILTIN_CALL; action->append = 0;
                status = add_term(ir, &source->actions[j].value, &action->target);
                if (status != RE_STATUS_OK) goto fail;
                action->value = SIZE_MAX;
                continue;
            }
            status = add_term(ir, &target, &action->target); if (status != RE_STATUS_OK) goto fail;
            status = add_term(ir, &source->actions[j].value, &action->value); if (status != RE_STATUS_OK) goto fail;
        }
        rule->action_count = source->action_count;
    }
    for (i = 0u; i < program->deffacts_set_count; ++i) {
        re_ir_deffacts_set_t *set; const re_deffacts_set_t *source = &program->deffacts_sets[i];
        re_operand_t set_name;
        status = grow(&ir->allocator, (void **)&ir->deffacts_sets, ir->deffacts_set_count + 1u, sizeof(*set)); if (status != RE_STATUS_OK) goto fail;
        set = &ir->deffacts_sets[ir->deffacts_set_count]; memset(set, 0, sizeof(*set));
        set->id = id_for(6u, i, source->name, source->name_size);
        set->first_entry = ir->deffacts_entry_count; set->span.end = ir->source_size; ++ir->deffacts_set_count;
        memset(&set_name, 0, sizeof(set_name)); set_name.kind = RE_OPERAND_FACT; set_name.fact_name = source->name; set_name.fact_name_size = source->name_size;
        status = add_term(ir, &set_name, &set->name); if (status != RE_STATUS_OK) goto fail;
        for (j = 0u; j < source->entry_count; ++j) {
            re_ir_deffacts_entry_t *entry; re_operand_t path;
            status = grow(&ir->allocator, (void **)&ir->deffacts_entries, ir->deffacts_entry_count + 1u, sizeof(*entry)); if (status != RE_STATUS_OK) goto fail;
            entry = &ir->deffacts_entries[ir->deffacts_entry_count]; memset(entry, 0, sizeof(*entry));
            entry->id = id_for(7u, ir->deffacts_entry_count, source->entries[j].path, source->entries[j].path_size);
            ++ir->deffacts_entry_count;
            memset(&path, 0, sizeof(path)); path.kind = RE_OPERAND_FACT; path.fact_name = source->entries[j].path; path.fact_name_size = source->entries[j].path_size;
            status = add_term(ir, &path, &entry->path); if (status != RE_STATUS_OK) goto fail;
            status = add_term(ir, &source->entries[j].value, &entry->value); if (status != RE_STATUS_OK) goto fail;
        }
        set->entry_count = source->entry_count;
    }
    for (i = 0u; i < program->query_count; ++i) {
        re_ir_query_t *query; const re_query_block_t *source = &program->queries[i];
        re_operand_t query_name; re_operand_t goal_text; size_t block;
        status = grow(&ir->allocator, (void **)&ir->queries, ir->query_count + 1u, sizeof(*query)); if (status != RE_STATUS_OK) goto fail;
        query = &ir->queries[ir->query_count]; memset(query, 0, sizeof(*query));
        query->id = id_for(8u, i, source->name, source->name_size);
        query->strategy = source->strategy; query->max_depth = source->max_depth;
        query->max_solutions = source->max_solutions;
        query->enable_memoization = source->enable_memoization;
        query->enable_optimization = source->enable_optimization;
        query->when = SIZE_MAX; query->span.end = ir->source_size; ++ir->query_count;
        memset(&query_name, 0, sizeof(query_name)); query_name.kind = RE_OPERAND_FACT; query_name.fact_name = source->name; query_name.fact_name_size = source->name_size;
        status = add_term(ir, &query_name, &query->name); if (status != RE_STATUS_OK) goto fail;
        memset(&goal_text, 0, sizeof(goal_text)); goal_text.kind = RE_OPERAND_LITERAL;
        goal_text.value.type = RE_VALUE_STRING; goal_text.value.as.string.data = source->goal; goal_text.value.as.string.size = source->goal_size;
        status = add_term(ir, &goal_text, &query->goal); if (status != RE_STATUS_OK) goto fail;
        if (source->when != NULL) { status = add_expr(ir, source->when, &query->when); if (status != RE_STATUS_OK) goto fail; }
        for (block = 0u; block < RE_QUERY_BLOCK_COUNT; ++block) {
            query->first_action[block] = ir->query_action_count;
            for (j = 0u; j < source->action_counts[block]; ++j) {
                const re_query_action_stmt_t *stmt = &source->actions[block][j];
                re_ir_query_action_t *action; re_operand_t name_op;
                status = grow(&ir->allocator, (void **)&ir->query_actions, ir->query_action_count + 1u, sizeof(*action)); if (status != RE_STATUS_OK) goto fail;
                action = &ir->query_actions[ir->query_action_count]; memset(action, 0, sizeof(*action));
                action->id = id_for(9u, ir->query_action_count, stmt->name, stmt->name_size);
                action->is_call = stmt->is_call; action->value = SIZE_MAX; action->args = SIZE_MAX;
                ++ir->query_action_count;
                memset(&name_op, 0, sizeof(name_op));
                if (stmt->is_call) { name_op.kind = RE_OPERAND_FUNCTION; name_op.function_name = stmt->name; name_op.function_name_size = stmt->name_size; }
                else { name_op.kind = RE_OPERAND_FACT; name_op.fact_name = stmt->name; name_op.fact_name_size = stmt->name_size; }
                status = add_term(ir, &name_op, &action->name); if (status != RE_STATUS_OK) goto fail;
                if (stmt->is_call) {
                    re_operand_t args_op;
                    memset(&args_op, 0, sizeof(args_op)); args_op.kind = RE_OPERAND_LITERAL;
                    args_op.value.type = RE_VALUE_STRING;
                    args_op.value.as.string.data = stmt->args != NULL ? stmt->args : "";
                    args_op.value.as.string.size = stmt->args_size;
                    status = add_term(ir, &args_op, &action->args); if (status != RE_STATUS_OK) goto fail;
                } else {
                    status = add_term(ir, &stmt->value, &action->value); if (status != RE_STATUS_OK) goto fail;
                }
            }
            query->action_count[block] = source->action_counts[block];
        }
    }
    if (ir->rule_count != 0u) { if (ir->rule_count > (size_t)-1 / sizeof(*ir->spans)) { status = RE_STATUS_LIMIT; goto fail; } ir->spans = re_alloc(&ir->allocator, ir->rule_count * sizeof(*ir->spans)); if (ir->spans == NULL) { status = RE_STATUS_OUT_OF_MEMORY; goto fail; } ir->span_count = ir->rule_count; for (i = 0u; i < ir->span_count; ++i) ir->spans[i] = (re_ir_span_t){0u, program->source_size}; }
    *out = ir; return RE_STATUS_OK;
fail: re_ir_destroy(ir); return status;
}
void re_ir_destroy(re_ir_program_t *ir) { size_t i; if (ir == NULL) return; for (i = 0u; i < ir->term_count; ++i) { re_free(&ir->allocator, ir->terms[i].name); re_free(&ir->allocator, ir->terms[i].argument_indices); if (ir->terms[i].value.type == RE_VALUE_STRING) re_free(&ir->allocator, (void *)ir->terms[i].value.as.string.data); } for (i = 0u; i < ir->expr_count; ++i) { size_t j; for (j = 0u; j < ir->exprs[i].accumulate_condition_count; ++j) re_free(&ir->allocator, ir->exprs[i].accumulate_conditions[j]); re_free(&ir->allocator, ir->exprs[i].accumulate_conditions); re_free(&ir->allocator, ir->exprs[i].accumulate_type); re_free(&ir->allocator, ir->exprs[i].accumulate_field); re_free(&ir->allocator, ir->exprs[i].accumulate_func_name); re_free(&ir->allocator, ir->exprs[i].typed_type); } for (i = 0u; i < ir->action_count; ++i) re_free(&ir->allocator, ir->actions[i].method_name); re_free(&ir->allocator, ir->strings); re_free(&ir->allocator, ir->spans); re_free(&ir->allocator, ir->queries); re_free(&ir->allocator, ir->query_actions); re_free(&ir->allocator, ir->deffacts_sets); re_free(&ir->allocator, ir->deffacts_entries); re_free(&ir->allocator, ir->actions); re_free(&ir->allocator, ir->rules); re_free(&ir->allocator, ir->modules); re_free(&ir->allocator, ir->exprs); re_free(&ir->allocator, ir->terms); re_free(&ir->allocator, ir); }
