#include "re_internal.h"
#include "ir.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

static int wildcard_match(re_string_t input, re_string_t pattern) {
    size_t input_at = 0u;
    size_t pattern_at = 0u;
    size_t star_pattern = SIZE_MAX;
    size_t star_input = 0u;
    size_t steps = 0u;
    size_t step_limit;
    if (pattern.size == SIZE_MAX || input.size > SIZE_MAX / (pattern.size + 1u)) return 0;
    step_limit = input.size * (pattern.size + 1u);
    if (step_limit == SIZE_MAX) return 0;
    ++step_limit;
    while (input_at < input.size || pattern_at < pattern.size) {
        if (++steps > step_limit) return 0;
        if (input_at < input.size && pattern_at < pattern.size &&
            (pattern.data[pattern_at] == '?' ||
             pattern.data[pattern_at] == input.data[input_at])) {
            ++input_at;
            ++pattern_at;
        } else if (pattern_at < pattern.size && pattern.data[pattern_at] == '*') {
            star_pattern = pattern_at++;
            star_input = input_at;
        } else if (star_pattern != SIZE_MAX) {
            pattern_at = star_pattern + 1u;
            input_at = ++star_input;
        } else {
            return 0;
        }
    }
    while (pattern_at < pattern.size && pattern.data[pattern_at] == '*') ++pattern_at;
    return pattern_at == pattern.size;
}

static re_status_t resolve_operand(const re_facts_t *facts, const re_operand_t *operand, re_value_t *value) {
    if (operand->kind == RE_OPERAND_LITERAL) { *value = operand->value; return RE_STATUS_OK; }
    return re_facts_get_path(facts, (re_string_t){operand->fact_name, operand->fact_name_size}, value);
}
int re_condition_is_pure(const re_expr_t *expr) {
    if (expr == NULL) return 0;
    if (expr->kind == RE_EXPR_COMPARE) {
        return expr->left.kind != RE_OPERAND_FUNCTION && expr->right.kind != RE_OPERAND_FUNCTION;
    }
    /* A5: multifield predicates are pure read-only array probes (a fact
     * path plus, for count, a numeric literal) - they re-evaluate on
     * every pass like plain comparisons. */
    if (expr->kind == RE_EXPR_MULTIFIELD) return 1;
    /* A6: accumulate WRITES the injected "<Type>.<func>" fact while matching,
     * so it is never pure: it stays off executor workers and evaluates only
     * at the first-pass position, like function-calling conditions. */
    if (expr->kind == RE_EXPR_ACCUMULATE) return 0;
    /* A9: test() wraps a function call - impure like every
     * function-call condition (first-pass-only evaluation, never on
     * executor workers). */
    if (expr->kind == RE_EXPR_TEST) return 0;
    /* A9: the typed form evaluates its inner condition per candidate -
     * pure iff the inner is pure (like the parenthesized quantifiers). */
    if (expr->kind == RE_EXPR_TYPED) return re_condition_is_pure(expr->first);
    if (expr->kind == RE_EXPR_TRUE || expr->kind == RE_EXPR_FALSE) return 1;
    /* Parenthesized quantifier forms (inner expression at `first`) are pure
     * iff their inner expression is pure. The restricted fact/literal form
     * (first == NULL) keeps its historical impure classification. */
    if ((expr->kind == RE_EXPR_EXISTS || expr->kind == RE_EXPR_FORALL) && expr->first != NULL)
        return re_condition_is_pure(expr->first);
    return re_condition_is_pure(expr->first) &&
           (expr->kind == RE_EXPR_NOT || re_condition_is_pure(expr->second));
}
re_status_t re_engine_match_rule(const re_engine_t *engine, const re_facts_t *facts,
                                 const re_rule_t *rule, int *matched) {
    size_t index;
    if (engine == NULL || engine->program == NULL || rule == NULL) return RE_STATUS_INVALID_ARGUMENT;
    for (index = 0u; index < engine->program->rule_count; ++index)
        if (&engine->program->rules[index] == rule) break;
    if (index == engine->program->rule_count) return RE_STATUS_INVALID_ARGUMENT;
    return re_ir_match_rule(engine, (re_facts_t *)facts, engine->program->ir, index, matched);
}

re_status_t re_operand_resolve(re_engine_t *engine, re_facts_t *facts,
                               const re_operand_t *operand, re_value_t *value) {
    size_t i;
    re_value_t *arguments;
    re_function_t *function;
    re_status_t status;
    if (operand->kind != RE_OPERAND_FUNCTION) return resolve_operand(facts, operand, value);
    for (function = engine->functions; function != NULL; function = function->next)
        if (!function->unregistered && function->name_size == operand->function_name_size &&
            memcmp(function->name, operand->function_name, function->name_size) == 0) break;
    if (function == NULL) return RE_STATUS_NOT_FOUND;
    arguments = operand->argument_count == 0u ? NULL : re_alloc(&engine->allocator, operand->argument_count * sizeof(*arguments));
    if (operand->argument_count != 0u && arguments == NULL) return RE_STATUS_OUT_OF_MEMORY;
    for (i = 0u; i < operand->argument_count; ++i) {
        status = re_operand_resolve(engine, facts, &operand->arguments[i], &arguments[i]);
        if (status != RE_STATUS_OK) { re_free(&engine->allocator, arguments); return status; }
    }
    function->active_calls++;
    status = function->call(engine, facts, arguments, operand->argument_count, value, function->context);
    function->active_calls--;
    re_free(&engine->allocator, arguments);
    return status;
}

static re_status_t finish_run(re_engine_t *engine, re_facts_t *facts, re_status_t status) {
    int destroy_engine;
    int destroy_facts;
    destroy_engine = engine->destroy_requested;
    destroy_facts = facts->destroy_requested;
    engine->running = 0;
    facts->running = 0;
    /* Non-persistent agenda mode: every run exit clears pending activations
     * and refraction keys. Persistent mode keeps both, so unfired
     * activations and the fired (refraction) history carry into the next
     * run, including on RE_STATUS_LIMIT / RE_STATUS_CANCELLED exits. */
    if (engine->agenda == NULL || !engine->agenda->persistent)
        re_agenda_reset(engine->agenda);
    if (destroy_facts) re_facts_destroy(facts);
    if (destroy_engine) re_engine_destroy(engine);
    return status;
}

/* Relational coercion per upstream to_number(): Integer/Number as-is,
 * numeric strings parse (the full string must be a number), and bool, array,
 * object or null operands fail, making the comparison false. The string is
 * copied into a bounded buffer first: re_value_t strings are not guaranteed
 * NUL-terminated. */
static int value_to_number(const re_value_t *value, double *out) {
    char buffer[256];
    char *end;
    if (value->type == RE_VALUE_INT64) { *out = (double)value->as.int64_value; return 1; }
    if (value->type == RE_VALUE_DOUBLE) { *out = value->as.double_value; return 1; }
    if (value->type != RE_VALUE_STRING || value->as.string.size == 0u ||
        value->as.string.size >= sizeof(buffer)) return 0;
    if (isspace((unsigned char)value->as.string.data[0])) return 0;
    memcpy(buffer, value->as.string.data, value->as.string.size);
    buffer[value->as.string.size] = '\0';
    *out = strtod(buffer, &end);
    return end == buffer + value->as.string.size;
}

int re_value_compare(const re_value_t *left, const re_value_t *right, re_compare_t compare) {
    if (compare == RE_COMPARE_TRUE) return 1;
    if (compare == RE_COMPARE_CONTAINS || compare == RE_COMPARE_NOT_CONTAINS ||
        compare == RE_COMPARE_STARTS_WITH || compare == RE_COMPARE_ENDS_WITH ||
        compare == RE_COMPARE_MATCHES) {
        /* String operators require two strings; against anything else they
         * are false (not_contains, the logical negation, is then true). */
        if (left->type == RE_VALUE_STRING && right->type == RE_VALUE_STRING) {
            size_t i;
            int found;
            if (compare == RE_COMPARE_STARTS_WITH)
                return right->as.string.size <= left->as.string.size &&
                       memcmp(left->as.string.data, right->as.string.data, right->as.string.size) == 0;
            if (compare == RE_COMPARE_ENDS_WITH)
                return right->as.string.size <= left->as.string.size &&
                       memcmp(left->as.string.data + left->as.string.size - right->as.string.size,
                              right->as.string.data, right->as.string.size) == 0;
            if (compare == RE_COMPARE_MATCHES)
                return wildcard_match(left->as.string, right->as.string);
            found = right->as.string.size == 0u;
            for (i = 0u; !found && i + right->as.string.size <= left->as.string.size; ++i)
                if (memcmp(left->as.string.data + i, right->as.string.data,
                           right->as.string.size) == 0) found = 1;
            return compare == RE_COMPARE_CONTAINS ? found : !found;
        }
        return compare == RE_COMPARE_NOT_CONTAINS ? 1 : 0;
    }
    if (compare == RE_COMPARE_EQ || compare == RE_COMPARE_NE) {
        /* D4: equality is strictly typed, matching upstream PartialEq -
         * Integer(1) == Number(1.0) is FALSE. */
        int equal = re_value_equal_typed(left, right);
        return compare == RE_COMPARE_EQ ? equal : !equal;
    }
    if (compare == RE_COMPARE_GT || compare == RE_COMPARE_GE ||
        compare == RE_COMPARE_LT || compare == RE_COMPARE_LE) {
        double l;
        double r;
        if (left->type == RE_VALUE_INT64 && right->type == RE_VALUE_INT64) {
            /* Exact integer comparison, no f64 precision loss. */
            if (compare == RE_COMPARE_GT) return left->as.int64_value > right->as.int64_value;
            if (compare == RE_COMPARE_GE) return left->as.int64_value >= right->as.int64_value;
            if (compare == RE_COMPARE_LT) return left->as.int64_value < right->as.int64_value;
            return left->as.int64_value <= right->as.int64_value;
        }
        if (!value_to_number(left, &l) || !value_to_number(right, &r)) return 0;
        if (compare == RE_COMPARE_GT) return l > r;
        if (compare == RE_COMPARE_GE) return l >= r;
        if (compare == RE_COMPARE_LT) return l < r;
        return l <= r;
    }
    return 0;
}

static int find_staged_fact(const re_facts_t *facts, re_string_t name,
                            re_fact_id_t *out_id) {
    size_t i;
    for (i = 0u; i < facts->count; ++i)
        if (facts->entries[i].active && facts->entries[i].name_size == name.size &&
            memcmp(facts->entries[i].name, name.data, name.size) == 0) {
            out_id->slot = (uint64_t)i;
            out_id->generation = facts->entries[i].generation;
            return 1;
        }
    return 0;
}

/* Resolves a condition read path to the id of the fact entry backing it: the
 * exact flat key when one exists (flat wins, exactly like re_facts_get_path),
 * otherwise the entry of the dotted root. */
static int resolve_read_premise(const re_facts_t *facts, re_string_t path,
                                re_fact_id_t *out_id) {
    size_t dot = 0u;
    if (find_staged_fact(facts, path, out_id)) return 1;
    while (dot < path.size && path.data[dot] != '.') ++dot;
    if (dot == 0u || dot == path.size) return 0;
    return find_staged_fact(facts, (re_string_t){path.data, dot}, out_id);
}

/* Defined in values.c; internal cross-unit helper for setXxx method calls. */
re_status_t re_facts_set_member(re_facts_t *facts, re_string_t name,
                                re_string_t key, const re_value_t *value);

static re_status_t call_registered_method(re_engine_t *engine, re_facts_t *facts,
                                          const char *name, size_t name_size,
                                          const re_value_t *arguments, size_t argument_count,
                                          re_value_t *out) {
    re_function_t *function;
    re_status_t status;
    for (function = engine->functions; function != NULL; function = function->next)
        if (!function->unregistered && function->name_size == name_size &&
            memcmp(function->name, name, name_size) == 0) break;
    if (function == NULL) return RE_STATUS_NOT_FOUND;
    function->active_calls++;
    status = function->call(engine, facts, arguments, argument_count, out, function->context);
    function->active_calls--;
    return status;
}

/* Builds "<receiver>.<Property>" where Property is method+3 with the first
 * character uppercased as-is (setSpeed -> "Speed"); members are case-sensitive. */
static re_status_t method_property_path(const re_allocator_impl_t *allocator,
                                        re_string_t receiver, re_string_t method,
                                        char **out_path, size_t *out_path_size) {
    size_t property_size = method.size - 3u;
    size_t path_size;
    char *path;
    if (property_size > (size_t)-2 || receiver.size > (size_t)-2 - property_size)
        return RE_STATUS_LIMIT;
    path_size = receiver.size + 1u + property_size;
    path = re_alloc(allocator, path_size + 1u);
    if (path == NULL) return RE_STATUS_OUT_OF_MEMORY;
    memcpy(path, receiver.data, receiver.size);
    path[receiver.size] = '.';
    path[receiver.size + 1u] = (char)toupper((unsigned char)method.data[3]);
    if (property_size > 1u)
        memcpy(path + receiver.size + 2u, method.data + 4u, property_size - 1u);
    path[path_size] = '\0';
    *out_path = path;
    *out_path_size = path_size;
    return RE_STATUS_OK;
}

/* Executes a $Receiver.method(...) call. With out == NULL (then-statement
 * form) any produced value is discarded; in operand position only getXxx and
 * registered functions yield a value. All fact writes go through the active
 * transaction exactly like ordinary actions. */
static re_status_t execute_method_call(re_engine_t *engine, re_facts_t *facts,
                                       const re_ir_program_t *ir,
                                       re_string_t receiver, re_string_t method,
                                       const re_ir_term_t *arguments_term,
                                       re_value_t *out, re_eval_scratch_t *scratch) {
    re_value_t *arguments = NULL;
    re_value_t result;
    re_status_t status;
    size_t i;
    if (arguments_term->argument_count != 0u) {
        if (arguments_term->argument_count > SIZE_MAX / sizeof(*arguments))
            return RE_STATUS_LIMIT;
        arguments = re_alloc(&engine->allocator,
                             arguments_term->argument_count * sizeof(*arguments));
        if (arguments == NULL) return RE_STATUS_OUT_OF_MEMORY;
        for (i = 0u; i < arguments_term->argument_count; ++i) {
            status = re_ir_resolve_term(engine, facts, ir,
                                        arguments_term->argument_indices[i], &arguments[i], scratch);
            if (status != RE_STATUS_OK) {
                re_free(&engine->allocator, arguments);
                return status;
            }
        }
    }
    result.type = RE_VALUE_NONE; result.as.int64_value = 0;
    if (method.size > 3u && memcmp(method.data, "set", 3u) == 0) {
        char *path; size_t path_size;
        if (arguments_term->argument_count != 1u) status = RE_STATUS_INVALID_ARGUMENT;
        else if (out != NULL) status = RE_STATUS_NOT_SUPPORTED;
        else {
            status = method_property_path(&engine->allocator, receiver, method, &path, &path_size);
            if (status == RE_STATUS_OK) {
                status = re_facts_set_path(facts, (re_string_t){path, path_size}, &arguments[0]);
                if (status == RE_STATUS_NOT_FOUND)
                    status = re_facts_set_member(facts, receiver,
                        (re_string_t){path + receiver.size + 1u, method.size - 3u}, &arguments[0]);
                re_free(&engine->allocator, path);
            }
        }
    } else if (method.size > 3u && memcmp(method.data, "get", 3u) == 0) {
        char *path; size_t path_size;
        if (arguments_term->argument_count != 0u) status = RE_STATUS_INVALID_ARGUMENT;
        else {
            status = method_property_path(&engine->allocator, receiver, method, &path, &path_size);
            if (status == RE_STATUS_OK) {
                status = re_facts_get_path(facts, (re_string_t){path, path_size}, &result);
                re_free(&engine->allocator, path);
            }
        }
    } else if (method.size == 5u && memcmp(method.data, "reset", 5u) == 0) {
        if (out != NULL) status = RE_STATUS_NOT_SUPPORTED;
        else {
            const re_value_handle_t *structured = NULL;
            status = re_facts_get_structured_path(facts, receiver, &structured);
            if (status == RE_STATUS_OK) {
                re_value_handle_t *empty = NULL;
                status = re_value_create_object(facts, &empty);
                if (status == RE_STATUS_OK) {
                    status = re_facts_set_value(facts, receiver, empty);
                    re_value_destroy(empty);
                }
            }
        }
    } else if (method.size == 6u && memcmp(method.data, "update", 6u) == 0) {
        status = out != NULL ? RE_STATUS_NOT_SUPPORTED : RE_STATUS_OK;
    } else {
        char *dotted;
        size_t dotted_size;
        if (method.size > (size_t)-2 || receiver.size > (size_t)-2 - method.size) {
            status = RE_STATUS_LIMIT;
        } else {
            dotted_size = receiver.size + 1u + method.size;
            dotted = re_alloc(&engine->allocator, dotted_size + 1u);
            if (dotted == NULL) status = RE_STATUS_OUT_OF_MEMORY;
            else {
                memcpy(dotted, receiver.data, receiver.size);
                dotted[receiver.size] = '.';
                memcpy(dotted + receiver.size + 1u, method.data, method.size);
                dotted[dotted_size] = '\0';
                status = call_registered_method(engine, facts, dotted, dotted_size,
                                                arguments, arguments_term->argument_count, &result);
                if (status == RE_STATUS_NOT_FOUND)
                    status = call_registered_method(engine, facts, method.data, method.size,
                                                    arguments, arguments_term->argument_count, &result);
                re_free(&engine->allocator, dotted);
                if (status == RE_STATUS_NOT_FOUND) status = RE_STATUS_NOT_SUPPORTED;
            }
        }
    }
    re_free(&engine->allocator, arguments);
    if (status == RE_STATUS_OK && out != NULL) *out = result;
    return status;
}

/* Splits the dotted "Receiver.method" name of a RE_IR_TERM_METHOD_CALL term. */
static re_status_t resolve_method_term(re_engine_t *engine, re_facts_t *facts,
                                       const re_ir_program_t *ir,
                                       const re_ir_term_t *term, re_value_t *out,
                                       re_eval_scratch_t *scratch) {
    size_t dot = 0u;
    while (dot < term->name_size && term->name[dot] != '.') ++dot;
    if (dot == 0u || dot + 1u >= term->name_size) return RE_STATUS_INVALID_ARGUMENT;
    return execute_method_call(engine, facts, ir,
        (re_string_t){term->name, dot},
        (re_string_t){term->name + dot + 1u, term->name_size - dot - 1u},
        term, out, scratch);
}

/* A8 bare `name(args)` action statement (RE_IR_ACTION_BUILTIN_CALL; upstream
 * grl.rs action builtins). Dispatches on the whitelisted name:
 *
 * - retract($Obj) sets the flag fact `_retracted_<root>` = true, <root> being
 *   the leftmost dotted segment of the single fact-reference argument. The
 *   flag is an ordinary fact (readable via re_facts_get, staged in the
 *   activation's transaction); ir_eval.c gates condition reads on it, and
 *   re-asserting the object does NOT clear it (upstream engine.rs
 *   L964-975/L1240-1247 parity).
 * - log(...) joins and prints its arguments to stdout through the A4 log
 *   built-in (shared machinery; stdout is the documented local logging
 *   convention - no log callback exists in the public API).
 * - ActivateAgendaGroup("g") switches the program's agenda focus for the
 *   remainder of the run (and later runs, exactly like a
 *   re_program_set_agenda_focus pre-set), pushing the previous focus on the
 *   B4 focus stack: when the new group's activations are exhausted the
 *   previous focus pops back (upstream AdvancedAgenda). The focus and its
 *   stack are program state, not facts, so they are not rolled back with
 *   the activation's transaction.
 * - ScheduleRule/CompleteWorkflow/SetWorkflowData (D5) dispatch to a
 *   registered function of the bare action name with the resolved arguments;
 *   unhandled -> RE_STATUS_NOT_SUPPORTED.
 */
static re_status_t execute_builtin_action(re_engine_t *engine, re_facts_t *facts,
                                          const re_ir_program_t *ir,
                                          const re_ir_term_t *call,
                                          re_eval_scratch_t *scratch) {
    re_string_t name = {call->name, call->name_size};
    re_value_t *arguments = NULL;
    re_string_t *arg_paths = NULL;
    re_value_t result;
    re_status_t status = RE_STATUS_OK;
    size_t i;
    if (name.size == 7u && memcmp(name.data, "retract", 7u) == 0) {
        /* Name-only: the argument is the object reference itself, never its
         * resolved value (the object root may not exist as a flat fact). */
        static const char prefix[] = "_retracted_";
        const re_ir_term_t *object;
        re_value_t flag;
        char *flag_name;
        size_t root = 0u;
        size_t flag_size;
        if (call->argument_count != 1u) return RE_STATUS_INVALID_ARGUMENT;
        object = &ir->terms[call->argument_indices[0]];
        if (object->kind != RE_IR_TERM_FACT || object->name == NULL)
            return RE_STATUS_INVALID_ARGUMENT;
        while (root < object->name_size && object->name[root] != '.') ++root;
        if (root == 0u || root > SIZE_MAX - sizeof(prefix)) return RE_STATUS_LIMIT;
        flag_size = sizeof(prefix) - 1u + root;
        flag_name = re_alloc(&engine->allocator, flag_size + 1u);
        if (flag_name == NULL) return RE_STATUS_OUT_OF_MEMORY;
        memcpy(flag_name, prefix, sizeof(prefix) - 1u);
        memcpy(flag_name + sizeof(prefix) - 1u, object->name, root);
        flag_name[flag_size] = '\0';
        flag.type = RE_VALUE_BOOL; flag.as.boolean = 1;
        status = re_facts_set(facts, (re_string_t){flag_name, flag_size}, &flag);
        re_free(&engine->allocator, flag_name);
        return status;
    }
    if (call->argument_count != 0u) {
        if (call->argument_count > SIZE_MAX / sizeof(*arguments) ||
            call->argument_count > SIZE_MAX / sizeof(*arg_paths))
            return RE_STATUS_LIMIT;
        arguments = re_alloc(&engine->allocator,
                             call->argument_count * sizeof(*arguments));
        arg_paths = re_alloc(&engine->allocator,
                             call->argument_count * sizeof(*arg_paths));
        if (arguments == NULL || arg_paths == NULL) {
            re_free(&engine->allocator, arguments);
            re_free(&engine->allocator, arg_paths);
            return RE_STATUS_OUT_OF_MEMORY;
        }
        memset(arg_paths, 0, call->argument_count * sizeof(*arg_paths));
        for (i = 0u; i < call->argument_count; ++i) {
            const re_ir_term_t *argument = &ir->terms[call->argument_indices[i]];
            if (argument->kind == RE_IR_TERM_FACT)
                arg_paths[i] = (re_string_t){argument->name, argument->name_size};
            status = re_ir_resolve_term(engine, facts, ir,
                                        call->argument_indices[i], &arguments[i], scratch);
            if (status != RE_STATUS_OK) goto done;
        }
    }
    result.type = RE_VALUE_NONE; result.as.int64_value = 0;
    if (name.size == 3u && memcmp(name.data, "log", 3u) == 0) {
        /* Shares the A4 log/print/println join-and-print machinery. */
        status = re_builtin_call(engine, facts, name, arguments, arg_paths,
                                 call->argument_count, &result, scratch);
    } else if (name.size == 19u && memcmp(name.data, "ActivateAgendaGroup", 19u) == 0) {
        if (call->argument_count != 1u || arguments[0].type != RE_VALUE_STRING)
            status = RE_STATUS_INVALID_ARGUMENT;
        else
            status = re_program_push_agenda_focus(engine->program,
                                                  arguments[0].as.string);
    } else {
        /* D5 trio: registered custom action handler under the bare action
         * name (same registry the method-call fallback uses). */
        status = call_registered_method(engine, facts, name.data, name.size,
                                        arguments, call->argument_count, &result);
        if (status == RE_STATUS_NOT_FOUND) status = RE_STATUS_NOT_SUPPORTED;
    }
done:
    re_free(&engine->allocator, arguments);
    re_free(&engine->allocator, arg_paths);
    return status;
}

/* Run-scoped state for the recognize-act loop in re_engine_run. The
 * no-loop / lock-on-active / activation-group bookkeeping lives here exactly
 * like it did in the single-pass loop; indices stay sorted by salience
 * (descending) with source-order ties. */
typedef struct re_run_state_t {
    size_t *indices;
    unsigned char *fired_no_loop;
    char **activation_groups;
    size_t activation_group_count;
    char **locked_groups;
    size_t locked_group_count;
    unsigned char *parallel_matches;
    unsigned char *pure_conditions;
    size_t next_rule;          /* first-pass cursor into indices */
    size_t agenda_activations; /* new activations pushed this run */
    size_t firings;
} re_run_state_t;

/* Fires one agenda activation inside its own transaction: runs the rule's
 * actions in order, then the action callback, then commits; any failure
 * rolls the transaction back and aborts the run with that status. The given
 * premises (the true token lineage re-resolved at fire time, or the linear
 * read-set ids captured at match time) feed logical insertion and
 * justification, exactly like the old single-pass firing block. */
static re_status_t fire_activation(re_engine_t *engine, re_facts_t *facts,
                                   size_t rule_index,
                                   const re_fact_id_t *premises, size_t premise_count,
                                   uint64_t activation_sequence,
                                   const re_callbacks_t *callbacks) {
    re_rule_t *rule = &engine->program->rules[rule_index];
    const re_ir_rule_t *ir_rule = &engine->program->ir->rules[rule_index];
    re_rule_event_t event;
    re_fact_txn_t *transaction = NULL;
    re_status_t status;
    size_t action_index;
    re_eval_scratch_t scratch = {NULL, 0u, 0u};
    event.rule_name.data = rule->name;
    event.rule_name.size = rule->name_size;
    event.salience = rule->salience;
    event.activation_sequence = activation_sequence;
    status = re_facts_begin_for_run(facts, &transaction);
    if (status == RE_STATUS_OK) {
        for (action_index = 0u; action_index < ir_rule->action_count; ++action_index) {
            re_value_t value;
            re_fact_id_t target_id;
            const re_ir_action_t *action = &engine->program->ir->actions[ir_rule->first_action + action_index];
            const re_ir_term_t *target = &engine->program->ir->terms[action->target];
            /* BUILTIN_CALL carries no value term (SIZE_MAX): form the pointer
             * lazily so the out-of-range index never enters an arithmetic. */
            const re_ir_term_t *action_value = action->kind == RE_IR_ACTION_BUILTIN_CALL
                ? NULL : &engine->program->ir->terms[action->value];
            re_eval_scratch_destroy(engine, &scratch);
            if (action->kind == RE_IR_ACTION_METHOD_CALL) {
                status = execute_method_call(engine, facts, engine->program->ir,
                    (re_string_t){target->name, target->name_size},
                    (re_string_t){action->method_name, action->method_name_size},
                    action_value, NULL, &scratch);
                if (status != RE_STATUS_OK) break;
                continue;
            }
            if (action->kind == RE_IR_ACTION_BUILTIN_CALL) {
                /* A8: target is the FUNCTION term holding name and args. */
                status = execute_builtin_action(engine, facts, engine->program->ir,
                                                target, &scratch);
                if (status != RE_STATUS_OK) break;
                continue;
            }
            status = action_value->kind == RE_IR_TERM_METHOD_CALL
                ? resolve_method_term(engine, facts, engine->program->ir, action_value, &value, &scratch)
                : re_ir_resolve_term(engine, facts, engine->program->ir, action->value, &value, &scratch);
            if (status != RE_STATUS_OK) break;
            /* Dotted action target with premises: when the root resolves to an
             * existing STRUCTURED fact (and no exact flat key shadows the full
             * name), this is a nested member write, not a new flat "Root.key"
             * shadow fact. The justification anchors on the ROOT fact id
             * (producer rule + premises). Bounded semantics: TMS cascade
             * retraction of a premise then retracts the whole root fact, not
             * just the member - heavier but honest. A rule that reads and
             * writes the same root would self-justify (a TMS self-cycle), so
             * that justification is skipped. Targets whose root is missing or
             * not structured keep the flat-fact behavior below. */
            if (!action->append && premise_count != 0u) {
                re_string_t target_name = {target->name, target->name_size};
                re_fact_id_t root_id;
                size_t dot = 0u;
                while (dot < target_name.size && target_name.data[dot] != '.') ++dot;
                if (dot != 0u && dot + 1u < target_name.size &&
                    !find_staged_fact(transaction->staged, target_name, &target_id) &&
                    find_staged_fact(transaction->staged, (re_string_t){target_name.data, dot}, &root_id) &&
                    transaction->staged->entries[root_id.slot].structured != NULL &&
                    transaction->staged->entries[root_id.slot].structured->kind == 1) {
                    status = re_facts_set_path(facts, target_name, &value);
                    if (status == RE_STATUS_NOT_FOUND &&
                        memchr(target_name.data + dot + 1u, '.', target_name.size - dot - 1u) == NULL)
                        status = re_facts_set_member(facts, (re_string_t){target_name.data, dot},
                            (re_string_t){target_name.data + dot + 1u, target_name.size - dot - 1u}, &value);
                    if (status == RE_STATUS_OK) {
                        size_t p;
                        for (p = 0u; p < premise_count; ++p)
                            if (premises[p].slot == root_id.slot &&
                                premises[p].generation == root_id.generation) break;
                        if (p == premise_count)
                            status = re_facts_justification_add(facts, root_id,
                                (re_string_t){rule->name, rule->name_size}, premises, premise_count);
                        if (status != RE_STATUS_OK) break;
                        continue;
                    }
                    if (status != RE_STATUS_NOT_FOUND) break;
                    /* Unresolvable member path: fall through to flat behavior. */
                    status = RE_STATUS_OK;
                }
            }
            if (!action->append && premise_count != 0u &&
                !find_staged_fact(transaction->staged, (re_string_t){target->name, target->name_size}, &target_id))
                status = re_facts_insert_logical(facts, (re_string_t){target->name, target->name_size}, &value,
                    (re_string_t){rule->name, rule->name_size}, premises, premise_count, &target_id);
            else {
                status = action->append ? re_facts_append_value(facts, (re_string_t){target->name, target->name_size}, &value) : re_facts_set_path(facts, (re_string_t){target->name, target->name_size}, &value);
                if (!action->append && status == RE_STATUS_NOT_FOUND)
                    status = re_facts_set(facts, (re_string_t){target->name, target->name_size}, &value);
                if (status == RE_STATUS_OK && !action->append && premise_count != 0u &&
                    find_staged_fact(transaction->staged, (re_string_t){target->name, target->name_size}, &target_id) &&
                    transaction->staged->entries[target_id.slot].logical)
                    status = re_facts_justification_add(facts, target_id,
                        (re_string_t){rule->name, rule->name_size}, premises, premise_count);
            }
            if (status != RE_STATUS_OK) break;
        }
    }
    re_eval_scratch_destroy(engine, &scratch);
    if (status == RE_STATUS_OK && callbacks != NULL && callbacks->action != NULL)
        status = callbacks->action(engine, facts, &event, callbacks->context);
    if (status == RE_STATUS_OK) status = re_facts_commit(transaction);
    else re_facts_rollback(transaction);
    return status;
}

/* FNV-1a over raw bytes, used for activation fingerprints. */
static uint64_t fnv_mix(uint64_t hash, const void *data, size_t size) {
    const unsigned char *bytes = (const unsigned char *)data;
    size_t i;
    for (i = 0u; i < size; ++i) {
        hash ^= bytes[i];
        hash *= 1099511628211ull;
    }
    return hash;
}

/* Facts keep (slot, generation) stable across value updates, so a bare
 * slot/generation refraction key can never observe a changed premise value.
 * The fingerprint mixes the current scalar value into what becomes the
 * generation field of the pushed refraction key: a value-changing write
 * re-activates the rule, while a no-op write or an unrelated change does
 * not. True lineage ids are recovered from the network at fire time, so the
 * fingerprint never reaches TMS justifications.
 * bounded: NULL/UNKNOWN/NONE and structured values mix only their type tag,
 * so content changes invisible to the scalar tag never re-activate a rule
 * (a missed refire); doubles hash their raw bits, and a hash collision would
 * suppress a legitimate re-activation. */
static uint64_t activation_fingerprint(const re_facts_t *facts, re_fact_id_t id) {
    uint64_t hash = 1469598103934665603ull;
    hash = fnv_mix(hash, &id.slot, sizeof(id.slot));
    hash = fnv_mix(hash, &id.generation, sizeof(id.generation));
    if (id.slot < facts->count) {
        const re_value_t *value = &facts->entries[id.slot].value;
        hash = fnv_mix(hash, &value->type, sizeof(value->type));
        if (value->type == RE_VALUE_BOOL)
            hash = fnv_mix(hash, &value->as.boolean, sizeof(value->as.boolean));
        else if (value->type == RE_VALUE_INT64)
            hash = fnv_mix(hash, &value->as.int64_value, sizeof(value->as.int64_value));
        else if (value->type == RE_VALUE_DOUBLE)
            hash = fnv_mix(hash, &value->as.double_value, sizeof(value->as.double_value));
        else if (value->type == RE_VALUE_STRING)
            hash = fnv_mix(hash, value->as.string.data, value->as.string.size);
    }
    return hash;
}

/* Recovers the true lineage ids (real generations, condition order) behind
 * an agenda entry: entry premises carry activation fingerprints instead of
 * generations, so logical insertion and TMS justifications re-resolve the
 * matching network token by its slot multiset. Also surfaces the token's
 * sequence, which is what the rule event reports for RETE-attached rules
 * (linear rules report the global firing counter). Returns 0 when the token
 * is gone: the stale activation is then discarded at pop time without being
 * marked fired, so a later cycle may legitimately re-create it. */
static size_t resolve_true_premises(const re_engine_t *engine, size_t rule_index,
                                    const re_agenda_entry_internal_t *entry,
                                    re_fact_id_t *premises, uint64_t *out_sequence) {
    const re_rete_network_t *network =
        engine->rete_networks != NULL ? engine->rete_networks[rule_index] : NULL;
    size_t i;
    if (network == NULL || entry->premise_count == 0u) return 0u;
    for (i = 0u; i < network->activation_count; ++i) {
        const re_rete_activation_t *activation = &network->activations[i];
        size_t j;
        if (activation->lineage_count != entry->premise_count) continue;
        for (j = 0u; j < activation->lineage_count; ++j) {
            size_t k;
            for (k = 0u; k < entry->premise_count; ++k)
                if (entry->premises[k].slot == activation->lineage[j].slot) break;
            if (k == entry->premise_count) break;
        }
        if (j != activation->lineage_count) continue;
        memcpy(premises, activation->lineage, activation->lineage_count * sizeof(*premises));
        if (out_sequence != NULL) *out_sequence = activation->sequence;
        return activation->lineage_count;
    }
    return 0u;
}

/* Recognize phase for one rule: applies the run-scoped visibility gates
 * (module focus, dates, agenda group, no-loop, lock-on-active,
 * activation-group), evaluates the match, and pushes every resulting
 * activation into the agenda. re_agenda_push dedups against pending and
 * fired entries, which is where refraction lives. */
static re_status_t compute_rule_activations(re_engine_t *engine, re_facts_t *facts,
                                            const re_limits_t *limits, size_t tracked_cap,
                                            re_run_state_t *state, size_t rule_index,
                                            int first_pass) {
    re_rule_t *rule = &engine->program->rules[rule_index];
    re_rete_network_t *network = engine->rete_networks != NULL ? engine->rete_networks[rule_index] : NULL;
    size_t activation_index;
    size_t activation_count;
    re_status_t status;
    re_ir_read_set_t reads;
    /* Function-calling (impure) conditions are evaluated only at their
     * historical first-pass position: the engine cannot observe when an
     * external function's answer changes, and recomputing would repeat
     * observable calls the single-pass loop made exactly once per run. */
    if (!first_pass && state->pure_conditions != NULL && !state->pure_conditions[rule_index])
        return RE_STATUS_OK;
    if (engine->program->module_focus != NULL) { size_t focus_index, import_index; int visible = 0; for (focus_index = 0u; focus_index < engine->program->module_count; ++focus_index) if (engine->program->modules[focus_index].name_size == strlen(engine->program->module_focus) && memcmp(engine->program->modules[focus_index].name, engine->program->module_focus, engine->program->modules[focus_index].name_size) == 0) break; if (focus_index == engine->program->module_count) return RE_STATUS_OK; if (rule->module_index == focus_index) visible = 1; for (import_index = 0u; !visible && import_index < engine->program->modules[focus_index].import_count; ++import_index) if (engine->program->modules[focus_index].imports[import_index] != NULL && engine->program->modules[focus_index].imports[import_index][0] == engine->program->modules[rule->module_index].name[0] && strcmp(engine->program->modules[focus_index].imports[import_index], engine->program->modules[rule->module_index].name) == 0 && engine->program->modules[rule->module_index].export_all) visible = 1; if (!visible) return RE_STATUS_OK; }
    if (!re_rule_active(rule, engine->program->has_clock ? engine->program->clock_epoch : 0)) return RE_STATUS_OK;
    /* B4: a rule with auto-focus AND an agenda-group is evaluated even when
     * its group is not the current focus (upstream evaluates rules
     * group-agnostically and lets the agenda see every activation); a
     * genuinely new activation then switches the focus below. auto-focus on
     * a group-less rule never bypasses the gate (documented no-op). */
    if (engine->program->agenda_focus == NULL) {
        if (rule->agenda_group != NULL && !rule->auto_focus) return RE_STATUS_OK;
    } else if (rule->agenda_group == NULL ||
               (strcmp(rule->agenda_group, engine->program->agenda_focus) != 0 &&
                !rule->auto_focus)) return RE_STATUS_OK;
    if (rule->no_loop && state->fired_no_loop[rule_index]) return RE_STATUS_OK;
    if (rule->lock_on_active && rule->agenda_group != NULL) {
        size_t group_index;
        for (group_index = 0u; group_index < state->locked_group_count; ++group_index)
            if (strcmp(state->locked_groups[group_index], rule->agenda_group) == 0) break;
        if (group_index != state->locked_group_count) return RE_STATUS_OK;
    }
    if (rule->activation_group != NULL) {
        size_t group_index;
        for (group_index = 0u; group_index < state->activation_group_count; ++group_index)
            if (strcmp(state->activation_groups[group_index], rule->activation_group) == 0) break;
        if (group_index != state->activation_group_count) return RE_STATUS_OK;
    }
    {
        int matched = 0;
        /* The read-set is captured at match time and attached to every pushed
         * activation below. The executor's parallel-match path observes no
         * read-set, so linear rules stay premise-less (once per run) there. */
        reads.count = 0u;
        status = state->parallel_matches != NULL ? RE_STATUS_OK
            : re_ir_match_rule_readset(engine, facts, engine->program->ir, rule_index, &matched, &reads);
        if (state->parallel_matches != NULL) matched = state->parallel_matches[rule_index] != 0u;
        if (status == RE_STATUS_NOT_FOUND) return RE_STATUS_OK;
        if (status != RE_STATUS_OK) return status;
        if (!matched) return RE_STATUS_OK;
    }
    /* A rule with an attached network contributes one activation per token.
     * Any other matched rule - a linear rule, or a network-attached rule
     * whose zero-token push is the RETE/linear divergence fallback (the
     * flat-name alpha memory cannot see structured member paths, so such a
     * rule linear-matches without any token) - contributes exactly one
     * activation keyed by the condition read-set, never a premise-less one;
     * only zero-read (constant-true) conditions stay premise-less. */
    activation_count = network != NULL && network->activation_count != 0u ? network->activation_count : 1u;
    for (activation_index = 0u; activation_index < activation_count; ++activation_index) {
        re_fact_id_t premises[RE_AGENDA_MAX_PREMISES];
        re_fact_id_t read_ids[RE_AGENDA_MAX_PREMISES];
        const re_fact_id_t *true_premises = NULL;
        size_t premise_count = 0u;
        size_t pending_before = engine->agenda->pending_count;
        if (network != NULL && activation_index < network->activation_count) {
            const re_rete_activation_t *activation = &network->activations[activation_index];
            size_t j;
            for (j = 0u; j < activation->lineage_count; ++j) {
                premises[j].slot = activation->lineage[j].slot;
                premises[j].generation = activation_fingerprint(facts, activation->lineage[j]);
            }
            /* True ids (real generations, condition order) ride alongside the
             * fingerprint key so re_agenda_peek can report honest premises. */
            true_premises = activation->lineage;
            premise_count = activation->lineage_count;
        } else {
            /* Linear path: the condition read-set becomes the premise set
             * (deduped by slot - the same fact read via several paths counts
             * once - capped at RE_AGENDA_MAX_PREMISES). The true ids (real
             * generations, read order) ride alongside the fingerprint key
             * exactly like token lineage does for network rules. */
            size_t j;
            for (j = 0u; j < reads.count && premise_count < RE_AGENDA_MAX_PREMISES; ++j) {
                re_fact_id_t id;
                size_t k;
                if (!resolve_read_premise(facts, reads.paths[j], &id)) continue;
                for (k = 0u; k < premise_count; ++k)
                    if (read_ids[k].slot == id.slot) break;
                if (k != premise_count) continue;
                read_ids[premise_count] = id;
                premises[premise_count].slot = id.slot;
                premises[premise_count].generation = activation_fingerprint(facts, id);
                ++premise_count;
            }
            true_premises = premise_count != 0u ? read_ids : NULL;
        }
        /* Refraction keys persist for the entire run. The generation fields
         * hold value fingerprints, so a value-changing write to any premise
         * re-activates the rule - for RETE rules and, since the read-set
         * provenance work, for linear rules alike. Only premise-less
         * activations (constant-true conditions, or the parallel-match path)
         * still refract for the whole run and fire at most once. And a
         * premise value toggled A->B->A re-creates the original key, which
         * stays refracted  -  timestep-free refraction, which keeps the loop
         * terminating. */
        status = re_agenda_push_full(engine->agenda, rule_index, rule->salience, premises, premise_count, true_premises);
        if (status != RE_STATUS_OK) return status;
        if (engine->agenda->pending_count != pending_before) {
            /* Only genuinely new activations count against the run limits;
             * deduped re-evaluations are recognize-phase no-ops. */
            if (limits->max_agenda_activations != 0u &&
                state->agenda_activations >= limits->max_agenda_activations) return RE_STATUS_LIMIT;
            ++state->agenda_activations;
            if (engine->agenda->fired_count + engine->agenda->pending_count > tracked_cap)
                return RE_STATUS_LIMIT;
            /* B4 auto-focus (upstream AdvancedAgenda::add_activation): a
             * genuinely new activation of an auto-focus rule switches the
             * focus to the rule's group (focus-stack push semantics; a
             * dedup/refraction hit adds nothing and never re-switches). The
             * push is a no-op when the group already is the focus. */
            if (rule->auto_focus && rule->agenda_group != NULL) {
                status = re_program_push_agenda_focus(engine->program,
                    (re_string_t){rule->agenda_group, strlen(rule->agenda_group)});
                if (status != RE_STATUS_OK) return status;
            }
        }
    }
    return RE_STATUS_OK;
}

int re_value_equal_typed(const re_value_t *left, const re_value_t *right) {
    if (left == NULL || right == NULL || left->type != right->type) return 0;
    switch (left->type) {
    case RE_VALUE_BOOL: return left->as.boolean == right->as.boolean;
    case RE_VALUE_INT64: return left->as.int64_value == right->as.int64_value;
    case RE_VALUE_DOUBLE: return left->as.double_value == right->as.double_value;
    case RE_VALUE_STRING:
        return left->as.string.size == right->as.string.size &&
            (left->as.string.size == 0u || memcmp(left->as.string.data,
                                                    right->as.string.data,
                                                    left->as.string.size) == 0);
    case RE_VALUE_NULL: case RE_VALUE_UNKNOWN: case RE_VALUE_NONE: return 1;
    default: return 0;
    }
}

re_engine_t *re_engine_create(const re_allocator_t *allocator, const re_limits_t *limits) {
    re_allocator_impl_t a; re_engine_t *engine; re_allocator_init(&a, allocator);
    if (a.api.alloc == NULL || a.api.realloc == NULL || a.api.free == NULL) return NULL;
    engine = re_alloc(&a, sizeof(*engine)); if (engine == NULL) return NULL;
    engine->allocator = a; engine->limits = limits != NULL ? *limits : re_default_limits(); engine->program = NULL; engine->running = 0; engine->destroy_requested = 0; engine->functions = NULL; engine->executor = NULL; engine->rete_network = NULL; engine->rete_networks = NULL; engine->rete_network_count = 0u; engine->agenda = NULL; engine->proof_graph = NULL; engine->config_serial = 0u; engine->random_state = RE_BUILTIN_RANDOM_SEED; return engine;
}

/* rete_network mirrors the first attached per-rule network (lowest rule
 * index) so re_engine_rete_network() and the capability probes keep working
 * without knowing about the array. */
static void sync_rete_primary(re_engine_t *engine) {
    size_t i;
    engine->rete_network = NULL;
    for (i = 0u; i < engine->rete_network_count; ++i)
        if (engine->rete_networks[i] != NULL) {
            engine->rete_network = engine->rete_networks[i];
            break;
        }
}

/* Destroys every per-rule network (destroy_internal clears the array slots
 * itself, including slots freed indirectly through chain teardown) and
 * releases the parallel array. */
static void destroy_rete_networks(re_engine_t *engine) {
    size_t i;
    if (engine->rete_networks != NULL) {
        for (i = 0u; i < engine->rete_network_count; ++i)
            if (engine->rete_networks[i] != NULL)
                re_rete_network_destroy_internal(engine->rete_networks[i]);
        re_free(&engine->allocator, engine->rete_networks);
        engine->rete_networks = NULL;
        engine->rete_network_count = 0u;
    }
    engine->rete_network = NULL;
}

/* Lazily attaches one RETE network per eligible rule (an AND of at most
 * eight fact-versus-literal comparisons, the collect() constraint in
 * rete.c). Networks bound to another fact set or marked invalid are rebuilt;
 * ineligible rules keep a NULL slot and use plain IR matching. */
static re_status_t ensure_rete_networks(re_engine_t *engine, re_facts_t *facts) {
    size_t i;
    if (engine->rete_networks == NULL) {
        if (engine->program->rule_count == 0u) return RE_STATUS_OK;
        engine->rete_networks = re_alloc(&engine->allocator,
            engine->program->rule_count * sizeof(*engine->rete_networks));
        if (engine->rete_networks == NULL) return RE_STATUS_OUT_OF_MEMORY;
        memset(engine->rete_networks, 0,
               engine->program->rule_count * sizeof(*engine->rete_networks));
        engine->rete_network_count = engine->program->rule_count;
    }
    for (i = 0u; i < engine->rete_network_count; ++i) {
        re_rete_network_t *network = engine->rete_networks[i];
        if (network != NULL && (network->facts != facts || network->invalid)) {
            re_rete_network_destroy_internal(network);
            network = NULL;
        }
        if (network == NULL) {
            re_status_t status = re_rete_network_create_rule_chained(facts,
                &engine->program->rules[i], &engine->allocator.api, &engine->rete_networks[i]);
            if (status == RE_STATUS_OUT_OF_MEMORY || status == RE_STATUS_LIMIT) return status;
            if (engine->rete_networks[i] != NULL) {
                engine->rete_networks[i]->program = engine->program;
                engine->rete_networks[i]->owner_engine = engine;
                engine->rete_networks[i]->engine_owned = 1;
            }
        }
    }
    sync_rete_primary(engine);
    return RE_STATUS_OK;
}
static void sort_activation_indices(const re_program_t *program, size_t *indices) {
    size_t i;
    for (i = 1u; i < program->rule_count; ++i) {
        size_t current = indices[i];
        size_t j = i;
        while (j != 0u) {
            const re_rule_t *left = &program->rules[indices[j - 1u]];
            const re_rule_t *right = &program->rules[current];
            if (left->salience > right->salience ||
                (left->salience == right->salience && left->source_order < right->source_order)) break;
            indices[j] = indices[j - 1u];
            --j;
        }
        indices[j] = current;
    }
}
static void free_agenda_state(const re_allocator_impl_t *allocator, size_t *indices,
                              unsigned char *fired_no_loop, char **activation_groups,
                              char **locked_groups, unsigned char *parallel_matches,
                              unsigned char *pure_conditions) {
    re_free(allocator, pure_conditions); re_free(allocator, parallel_matches);
    re_free(allocator, locked_groups); re_free(allocator, activation_groups);
    re_free(allocator, fired_no_loop); re_free(allocator, indices);
}
void re_engine_destroy(re_engine_t *engine) {
    if (engine == NULL) return;
    if (engine->running) { engine->destroy_requested = 1; return; }
    re_executor_destroy(engine->executor);
    destroy_rete_networks(engine);
    re_agenda_destroy_internal(engine->agenda);
    engine->agenda = NULL;
    while (engine->functions != NULL) { re_function_t *function = engine->functions; engine->functions = function->next; if (function->release != NULL) function->release(function->context); re_free(&engine->allocator, function->name); re_free(&engine->allocator, function); }
    re_proof_graph_destroy(engine->proof_graph);
    engine->proof_graph = NULL;
    re_program_destroy(engine->program); re_free(&engine->allocator, engine);
}
re_capabilities_t re_engine_capabilities(const re_engine_t *engine) { return engine == NULL ? 0u : RE_CAP_CORE_GRL | RE_CAP_FACTS | RE_CAP_FORWARD_EXECUTION; }

re_status_t re_engine_capabilities_v2(const re_engine_t *engine, uint32_t version, re_capabilities_v2_t *out) {
    if (engine == NULL || out == NULL) return RE_STATUS_INVALID_ARGUMENT;
    if (version != RE_ABI_VERSION_MAJOR) return RE_STATUS_NOT_SUPPORTED;
    *out = RE_CAP2_CUSTOM_FUNCTIONS | RE_CAP2_STRUCTURED_VALUES | RE_CAP2_FACT_LIFECYCLE |
           RE_CAP2_STREAMING_WINDOWS | RE_CAP2_STATE_PROVIDER;
    if (engine->rete_network != NULL) *out |= RE_CAP2_AGENDA_RETE;
#if defined(RE_ENABLE_C11_PARALLEL)
    *out |= RE_CAP2_CONCURRENCY;
#endif
    return RE_STATUS_OK;
}
re_status_t re_engine_extension_info(const re_engine_t *engine, re_extension_id_t id, uint32_t version, re_extension_info_t *out) {
    if (engine == NULL || out == NULL) return RE_STATUS_INVALID_ARGUMENT;
    if ((id != RE_EXTENSION_CUSTOM_FUNCTIONS && id != RE_EXTENSION_STRUCTURED_VALUES && id != RE_EXTENSION_FACT_LIFECYCLE &&
         id != RE_EXTENSION_AGENDA_RETE &&
         id != RE_EXTENSION_STREAMING_WINDOWS && id != RE_EXTENSION_STATE_PROVIDER
#if defined(RE_ENABLE_C11_PARALLEL)
         && id != RE_EXTENSION_CONCURRENCY
#endif
         ) || version != 1u || out->struct_size < sizeof(*out)) return RE_STATUS_NOT_SUPPORTED;
    out->abi_major = RE_ABI_VERSION_MAJOR; out->abi_minor = RE_ABI_VERSION_MINOR; out->extension_id = id; out->extension_version = 1u; out->reserved = 0u;
    if (id == RE_EXTENSION_AGENDA_RETE && engine->rete_network == NULL) return RE_STATUS_NOT_SUPPORTED;
    out->capability_bit = id == RE_EXTENSION_CUSTOM_FUNCTIONS ? RE_CAP2_CUSTOM_FUNCTIONS :
        id == RE_EXTENSION_STRUCTURED_VALUES ? RE_CAP2_STRUCTURED_VALUES :
        id == RE_EXTENSION_FACT_LIFECYCLE ? RE_CAP2_FACT_LIFECYCLE :
        id == RE_EXTENSION_AGENDA_RETE ? RE_CAP2_AGENDA_RETE :
        id == RE_EXTENSION_STREAMING_WINDOWS ? RE_CAP2_STREAMING_WINDOWS :
        id == RE_EXTENSION_STATE_PROVIDER ? RE_CAP2_STATE_PROVIDER : RE_CAP2_CONCURRENCY;
    return RE_STATUS_OK;
}
re_status_t re_engine_register_function(re_engine_t *engine, const re_function_descriptor_t *descriptor, re_function_t **out) {
    re_function_t *function;
    if (engine == NULL || descriptor == NULL || out == NULL || descriptor->struct_size < sizeof(*descriptor) || descriptor->abi_version != RE_ABI_VERSION_MAJOR || descriptor->name.data == NULL || descriptor->name.size == 0u || descriptor->call == NULL) return RE_STATUS_INVALID_ARGUMENT;
    if (engine->running) return RE_STATUS_BUSY;
    *out = NULL; function = re_alloc(&engine->allocator, sizeof(*function)); if (function == NULL) return RE_STATUS_OUT_OF_MEMORY; memset(function, 0, sizeof(*function));
    if (re_copy_string(&engine->allocator, descriptor->name, &function->name) != RE_STATUS_OK) { re_free(&engine->allocator, function); return RE_STATUS_OUT_OF_MEMORY; }
    function->engine = engine; function->name_size = descriptor->name.size; function->call = descriptor->call; function->release = descriptor->release; function->context = descriptor->context; function->next = engine->functions; engine->functions = function; ++engine->config_serial; *out = function; return RE_STATUS_OK;
}
void re_function_unregister(re_function_t *function) {
    re_function_t **link;
    if (function == NULL || function->unregistered) return;
    if (function->active_calls != 0u) return;
    link = &function->engine->functions; while (*link != NULL && *link != function) link = &(*link)->next;
    if (*link == function) *link = function->next;
    function->unregistered = 1; ++function->engine->config_serial; if (function->release != NULL) function->release(function->context); re_free(&function->engine->allocator, function->name); re_free(&function->engine->allocator, function);
}
re_status_t re_engine_install(re_engine_t *engine, re_program_t *program) {
    re_program_t *old; if (engine == NULL || program == NULL) return RE_STATUS_INVALID_ARGUMENT;
    if (re_ir_validate(program->ir) != RE_STATUS_OK) return RE_STATUS_INVALID_ARGUMENT;
    if (program->rule_count > engine->limits.max_rules && engine->limits.max_rules != 0u) return RE_STATUS_LIMIT;
    if (engine->running) return RE_STATUS_BUSY;
    destroy_rete_networks(engine);
    /* Installing a new program invalidates any surviving agenda entries
     * (rule indices and refraction keys refer to the old rules), persistent
     * mode included. */
    re_agenda_reset(engine->agenda);
    old = engine->program; engine->program = program; re_program_destroy(old);
    /* Cached proof-graph entries key on config_serial; new rules move it. */
    ++engine->config_serial;
    return RE_STATUS_OK;
}

/* Resets the lazily-created agenda (pending activations and refraction
 * keys); NULL-safe when no agenda exists yet. */
void re_engine_clear_agenda(re_engine_t *engine) {
    if (engine == NULL) return;
    re_agenda_reset(engine->agenda);
}

/* Lazily creates the engine-owned agenda; re_agenda_peek resolves rule names
 * through the owning engine, so the agenda is back-linked here. */
re_status_t re_engine_ensure_agenda(re_engine_t *engine) {
    re_status_t status;
    if (engine == NULL) return RE_STATUS_INVALID_ARGUMENT;
    if (engine->agenda != NULL) return RE_STATUS_OK;
    status = re_agenda_create_internal(&engine->allocator.api, &engine->agenda);
    if (status != RE_STATUS_OK) return status;
    engine->agenda->engine = engine;
    return RE_STATUS_OK;
}

static re_status_t load_deffacts_entry(re_facts_t *facts, const re_ir_program_t *ir,
                                       const re_ir_deffacts_entry_t *entry) {
    const re_ir_term_t *path = &ir->terms[entry->path];
    const re_ir_term_t *value = &ir->terms[entry->value];
    re_string_t name = {path->name, path->name_size};
    size_t i;
    re_status_t status;
    if (value->kind == RE_IR_TERM_ARRAY) {
        re_value_handle_t *array = NULL;
        status = re_value_create_array(facts, &array);
        for (i = 0u; status == RE_STATUS_OK && i < value->argument_count; ++i)
            status = re_value_array_append(array, &ir->terms[value->argument_indices[i]].value);
        if (status == RE_STATUS_OK) status = re_facts_set_value(facts, name, array);
        re_value_destroy(array);
        return status;
    }
    /* Dotted paths update an existing structured member (flat key wins);
     * anything unresolved becomes a plain flat fact. */
    status = re_facts_set_path(facts, name, &value->value);
    if (status == RE_STATUS_NOT_FOUND) status = re_facts_set(facts, name, &value->value);
    return status;
}

re_status_t re_engine_load_deffacts(re_engine_t *engine, re_facts_t *facts, const char *name_or_null) {
    const re_ir_program_t *ir;
    size_t i, j;
    int found = 0;
    if (engine == NULL || facts == NULL) return RE_STATUS_INVALID_ARGUMENT;
    if (engine->program == NULL) return RE_STATUS_INVALID_ARGUMENT;
    if (engine->running) return RE_STATUS_BUSY;
    ir = engine->program->ir;
    for (i = 0u; i < ir->deffacts_set_count; ++i) {
        const re_ir_deffacts_set_t *set = &ir->deffacts_sets[i];
        const re_ir_term_t *set_name = &ir->terms[set->name];
        if (name_or_null != NULL) {
            size_t name_size = strlen(name_or_null);
            if (set_name->name_size != name_size ||
                memcmp(set_name->name, name_or_null, name_size) != 0) continue;
        }
        found = 1;
        for (j = 0u; j < set->entry_count; ++j) {
            re_status_t status = load_deffacts_entry(facts, ir, &ir->deffacts_entries[set->first_entry + j]);
            if (status != RE_STATUS_OK) return status;
        }
    }
    return name_or_null != NULL && !found ? RE_STATUS_NOT_FOUND : RE_STATUS_OK;
}

re_status_t re_engine_reset_with_deffacts(re_engine_t *engine, re_facts_t *facts) {
    re_status_t status;
    if (engine == NULL || facts == NULL) return RE_STATUS_INVALID_ARGUMENT;
    if (engine->running) return RE_STATUS_BUSY;
    status = re_facts_clear_all(facts);
    if (status != RE_STATUS_OK) return status;
    re_engine_clear_agenda(engine);
    if (engine->program == NULL) return RE_STATUS_OK;
    return re_engine_load_deffacts(engine, facts, NULL);
}

re_status_t re_engine_run(re_engine_t *engine, re_facts_t *facts, const re_run_options_t *options, const re_callbacks_t *callbacks) {
    size_t i;
    re_run_state_t state;
    re_limits_t limits; int explicit_limits;
    size_t tracked_cap;
    re_status_t status = RE_STATUS_OK;
    if (engine == NULL || facts == NULL) return RE_STATUS_INVALID_ARGUMENT;
    if (engine->running) return RE_STATUS_BUSY;
    engine->running = 1;
    if (facts->running) { engine->running = 0; return RE_STATUS_BUSY; }
    facts->running = 1;
    explicit_limits = options != NULL && options->limits != NULL;
    limits = explicit_limits ? *options->limits : engine->limits;
    if (limits.max_source_bytes == 0u) limits.max_source_bytes = engine->limits.max_source_bytes;
    if (limits.max_rules == 0u) limits.max_rules = engine->limits.max_rules;
    if (limits.max_facts == 0u) limits.max_facts = engine->limits.max_facts;
    if (limits.max_agenda_activations == 0u) limits.max_agenda_activations = engine->limits.max_agenda_activations;
    if (limits.max_firings == 0u) limits.max_firings = engine->limits.max_firings;
    if (limits.max_activations_tracked == 0u) limits.max_activations_tracked = engine->limits.max_activations_tracked;
    tracked_cap = limits.max_activations_tracked != 0u ? limits.max_activations_tracked : 1024u;
    if (engine->program == NULL) return finish_run(engine, facts, RE_STATUS_OK);
    status = re_engine_ensure_agenda(engine);
    if (status != RE_STATUS_OK) return finish_run(engine, facts, status);
    status = ensure_rete_networks(engine, facts);
    if (status != RE_STATUS_OK) return finish_run(engine, facts, status);
    memset(&state, 0, sizeof(state));
    if (engine->program->rule_count != 0u) {
        state.indices = re_alloc(&engine->allocator, engine->program->rule_count * sizeof(*state.indices));
        if (state.indices == NULL) return finish_run(engine, facts, RE_STATUS_OUT_OF_MEMORY);
        state.fired_no_loop = re_alloc(&engine->allocator, engine->program->rule_count);
        if (state.fired_no_loop == NULL) { re_free(&engine->allocator, state.indices); return finish_run(engine, facts, RE_STATUS_OUT_OF_MEMORY); }
        memset(state.fired_no_loop, 0, engine->program->rule_count);
        state.pure_conditions = re_alloc(&engine->allocator, engine->program->rule_count);
        if (state.pure_conditions == NULL) { re_free(&engine->allocator, state.fired_no_loop); re_free(&engine->allocator, state.indices); return finish_run(engine, facts, RE_STATUS_OUT_OF_MEMORY); }
        for (i = 0u; i < engine->program->rule_count; ++i)
            state.pure_conditions[i] = (unsigned char)re_condition_is_pure(engine->program->rules[i].condition);
        state.activation_groups = re_alloc(&engine->allocator, engine->program->rule_count * sizeof(*state.activation_groups));
        state.locked_groups = re_alloc(&engine->allocator, engine->program->rule_count * sizeof(*state.locked_groups));
        if (state.activation_groups == NULL || state.locked_groups == NULL) {
            re_free(&engine->allocator, state.locked_groups); re_free(&engine->allocator, state.activation_groups);
            re_free(&engine->allocator, state.pure_conditions);
            re_free(&engine->allocator, state.fired_no_loop); re_free(&engine->allocator, state.indices);
            return finish_run(engine, facts, RE_STATUS_OUT_OF_MEMORY);
        }
        for (i = 0u; i < engine->program->rule_count; ++i) state.indices[i] = i;
        sort_activation_indices(engine->program, state.indices);
    }
    if (engine->executor != NULL) {
        int pure = 1;
        for (i = 0u; i < engine->program->rule_count; ++i)
            if (!re_condition_is_pure(engine->program->rules[i].condition)) pure = 0;
        if (pure) {
            state.parallel_matches = re_alloc(&engine->allocator, engine->program->rule_count);
            if (state.parallel_matches == NULL) { free_agenda_state(&engine->allocator, state.indices, state.fired_no_loop, state.activation_groups, state.locked_groups, NULL, state.pure_conditions); return finish_run(engine, facts, RE_STATUS_OUT_OF_MEMORY); }
        }
    }
    /* Recognize-act cycle. The first pass evaluates one new rule per
     * iteration (sorted by salience, then source order) so firings
     * interleave with matching in the historical order; once every rule was
     * evaluated, each iteration recomputes all visible rules and the agenda
     * fires the highest-salience pending activation. Refraction (agenda
     * dedup against fired keys) is what makes the loop terminate. */
    for (;;) {
        re_agenda_entry_internal_t activation;
        re_rule_t *rule;
        if (options != NULL && options->is_cancelled != NULL && options->is_cancelled(options->cancel_context) != 0) { status = RE_STATUS_CANCELLED; break; }
        if (state.parallel_matches != NULL) {
            status = re_executor_match(engine->executor, engine, facts, engine->program, state.parallel_matches);
            if (status != RE_STATUS_OK) break;
        }
        if (state.next_rule < engine->program->rule_count) {
            status = compute_rule_activations(engine, facts, &limits, tracked_cap, &state, state.indices[state.next_rule], 1);
            ++state.next_rule;
            if (status != RE_STATUS_OK) break;
        }
        for (i = 0u; i < state.next_rule; ++i) {
            status = compute_rule_activations(engine, facts, &limits, tracked_cap, &state, state.indices[i], 0);
            if (status != RE_STATUS_OK) break;
        }
        if (status != RE_STATUS_OK) break;
        if (!re_agenda_pop_highest(engine->agenda, &activation)) {
            if (state.next_rule < engine->program->rule_count) continue;
            /* B4: the focus group's activations are exhausted (cross-group
             * entries are never pending: the compute gate only pushes the
             * focus group, and the pop-time gate below drains whatever went
             * stale). Pop the focus stack, exactly like upstream
             * AdvancedAgenda::get_next_activation; an empty stack ends the
             * run with the focus left on the exhausted group. */
            if (re_program_pop_agenda_focus(engine->program)) continue;
            break;
        }
        rule = &engine->program->rules[activation.rule_index];
        /* The agenda focus can have moved while the activation sat pending
         * (A8 ActivateAgendaGroup / B4 auto-focus); entries whose group no
         * longer matches the focus are dropped, exactly like the group-level
         * gates below. The B4 focus stack keeps this stale-activation
         * protection: a popped-back group's rules re-push through the compute
         * gate instead of reviving these entries. With only a static pre-set
         * focus this is a no-op: cross-group entries are never pushed in the
         * first place. */
        if (engine->program->agenda_focus == NULL) {
            if (rule->agenda_group != NULL) continue;
        } else if (rule->agenda_group == NULL ||
                   strcmp(rule->agenda_group, engine->program->agenda_focus) != 0) continue;
        /* Group-level gates can have closed while the activation sat
         * pending; such entries are dropped, exactly like the old pass
         * skipped those rules when it reached them. */
        if (rule->lock_on_active && rule->agenda_group != NULL) {
            size_t group_index;
            for (group_index = 0u; group_index < state.locked_group_count; ++group_index)
                if (strcmp(state.locked_groups[group_index], rule->agenda_group) == 0) break;
            if (group_index != state.locked_group_count) continue;
        }
        if (rule->activation_group != NULL) {
            size_t group_index;
            for (group_index = 0u; group_index < state.activation_group_count; ++group_index)
                if (strcmp(state.activation_groups[group_index], rule->activation_group) == 0) break;
            if (group_index != state.activation_group_count) continue;
        }
        {
            re_fact_id_t true_premises[RE_AGENDA_MAX_PREMISES];
            re_rete_network_t *network =
                engine->rete_networks != NULL ? engine->rete_networks[activation.rule_index] : NULL;
            size_t true_count = 0u;
            uint64_t sequence = (uint64_t)state.firings + 1u;
            /* Pop-time revalidation: facts may have moved on since the push.
             * A token-backed entry must still resolve to a live token. An
             * entry whose token is gone - or a linear read-set entry, which
             * never had one - falls back to the true premise ids riding on
             * the entry itself: it is stale (discarded without being marked
             * fired, so a later cycle may legitimately re-push it) when a
             * premise fact was retracted or re-asserted, or when a pure
             * non-constant condition no longer matches, re-running the same
             * match predicate used at compute time. A premise-less entry from
             * a linear rule with a real pure condition re-runs that predicate
             * as well (constant-true conditions and impure conditions are not
             * re-checked  -  the latter are not re-observable  -  and the
             * focus/date predicates are run-static). A live token alone is
             * not sufficient for a pure condition either (A8 review I1): the
             * retract($Obj) flag fact matches no network pattern, so a
             * same-run retract cannot kill the token the way an ordinary
             * premise write does - token-live pure entries therefore also
             * re-pass the retract-gated linear match below. */
            if (activation.premise_count != 0u) {
                if (network != NULL)
                    true_count = resolve_true_premises(engine, activation.rule_index,
                                                       &activation, true_premises, &sequence);
                if (true_count == 0u) {
                    size_t k;
                    for (k = 0u; k < activation.premise_count; ++k) {
                        re_fact_id_t id = activation.true_premises[k];
                        if (id.slot >= facts->count || !facts->entries[id.slot].active ||
                            facts->entries[id.slot].generation != id.generation) break;
                    }
                    if (k != activation.premise_count) continue;
                    if (rule->condition != NULL && rule->condition->kind != RE_EXPR_TRUE &&
                        state.pure_conditions != NULL &&
                        state.pure_conditions[activation.rule_index]) {
                        int matched = 0;
                        status = state.parallel_matches != NULL ? RE_STATUS_OK
                            : re_ir_match_rule(engine, facts, engine->program->ir, activation.rule_index, &matched);
                        if (state.parallel_matches != NULL) matched = state.parallel_matches[activation.rule_index] != 0u;
                        if (status == RE_STATUS_NOT_FOUND) continue;
                        if (status != RE_STATUS_OK) break;
                        if (!matched) continue;
                    }
                    memcpy(true_premises, activation.true_premises,
                           activation.premise_count * sizeof(*true_premises));
                    true_count = activation.premise_count;
                } else if (rule->condition != NULL &&
                           rule->condition->kind != RE_EXPR_TRUE &&
                           state.pure_conditions != NULL &&
                           state.pure_conditions[activation.rule_index]) {
                    /* Token-live pure entry: re-run the same gated linear
                     * match the compute phase used. The re-check records no
                     * read-set and runs on the same (transaction-free) view;
                     * on a pass the token lineage in true_premises flows into
                     * fire_activation unchanged. A dropped entry is not marked
                     * fired, so it may legitimately re-push if the flag clears.
                     * Impure conditions keep the historical first-pass-only
                     * evaluation: their answers are not re-observable. */
                    int matched = 0;
                    status = state.parallel_matches != NULL ? RE_STATUS_OK
                        : re_ir_match_rule(engine, facts, engine->program->ir, activation.rule_index, &matched);
                    if (state.parallel_matches != NULL) matched = state.parallel_matches[activation.rule_index] != 0u;
                    if (status == RE_STATUS_NOT_FOUND) continue;
                    if (status != RE_STATUS_OK) break;
                    if (!matched) continue;
                }
            } else if (network == NULL && rule->condition != NULL &&
                       rule->condition->kind != RE_EXPR_TRUE &&
                       state.pure_conditions != NULL &&
                       state.pure_conditions[activation.rule_index]) {
                int matched = 0;
                status = state.parallel_matches != NULL ? RE_STATUS_OK
                    : re_ir_match_rule(engine, facts, engine->program->ir, activation.rule_index, &matched);
                if (state.parallel_matches != NULL) matched = state.parallel_matches[activation.rule_index] != 0u;
                if (status == RE_STATUS_NOT_FOUND) continue;
                if (status != RE_STATUS_OK) break;
                if (!matched) continue;
            }
            status = fire_activation(engine, facts, activation.rule_index,
                                     true_premises, true_count, sequence, callbacks);
        }
        if (status != RE_STATUS_OK) break;
        status = re_agenda_mark_fired(engine->agenda, &activation);
        if (status != RE_STATUS_OK) break;
        if (rule->activation_group != NULL) {
            state.activation_groups[state.activation_group_count] = rule->activation_group;
            ++state.activation_group_count;
        }
        if (rule->no_loop) state.fired_no_loop[activation.rule_index] = 1u;
        if (rule->lock_on_active && rule->agenda_group != NULL) {
            state.locked_groups[state.locked_group_count] = rule->agenda_group;
            ++state.locked_group_count;
        }
        ++state.firings;
        if (limits.max_firings != 0u && state.firings >= limits.max_firings) { status = RE_STATUS_LIMIT; break; }
    }
    free_agenda_state(&engine->allocator, state.indices, state.fired_no_loop, state.activation_groups, state.locked_groups, state.parallel_matches, state.pure_conditions);
    return finish_run(engine, facts, status);
}
