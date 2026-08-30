#include "ir.h"
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
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
    int pushed_binding;
    re_function_t *function;
    re_value_t *arguments;
    /* Built-in calls only (function == NULL): per-argument binding-rewritten
     * fact path for bare fact-path arguments, {NULL, 0} for anything else.
     * Lets a built-in tell an array fact from its RE_VALUE_NONE scalar
     * placeholder and lets exists() probe the path instead of the value. */
    re_string_t *arg_paths;
} re_eval_frame_t;
/* Prefix rebinding for the parenthesized exists()/forall() forms (D7): while a
 * quantifier frame iterates candidates, fact paths rooted at `prefix` resolve
 * against the bound candidate instead (term "Score.value" under {"Score" ->
 * "Score1"} reads "Score1.value"). The candidate name is owned by the state so
 * a fact-mutating custom function cannot invalidate it mid-evaluation; the
 * prefix borrows the IR term name. */
typedef struct re_eval_binding_t {
    const char *prefix;
    size_t prefix_size;
    char *name;
    size_t name_size;
} re_eval_binding_t;
typedef struct re_ir_eval_state_t {
    size_t *rules;
    size_t rule_count;
    size_t rule_capacity;
    size_t steps;
    size_t step_limit;
    re_eval_frame_t *frames;
    size_t frame_count;
    size_t frame_capacity;
    re_eval_binding_t *bindings;
    size_t binding_count;
    size_t binding_capacity;
    /* Bounded condition read-set (dedup, cap RE_IR_MAX_READ_PATHS, silent
     * stop on overflow); recorded only when record_reads is set, i.e. during
     * condition matching - action-RHS term resolution leaves it off so
     * writes' reads never pollute rule premises. Paths borrow IR term
     * strings, which outlive the evaluation. */
    re_string_t read_paths[RE_IR_MAX_READ_PATHS];
    size_t read_count;
    int record_reads;
    /* A8 retract gating (upstream engine.rs L964-975/L1240-1247): set for
     * condition evaluation (match paths), clear for action-RHS resolution
     * (re_ir_resolve_term), so only conditions observe the flag. */
    int gate_retracts;
    /* Owned strings produced by `+` concatenation and by string-producing
     * built-in calls (A4); values elsewhere borrow. re_ir_resolve_term moves
     * the list out to the caller's scratch so the resolved value stays valid
     * after the state is destroyed. */
    re_eval_scratch_t scratch;
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

static void record_read(re_ir_eval_state_t *state, const char *name, size_t name_size) {
    size_t i;
    if (!state->record_reads) return;
    for (i = 0u; i < state->read_count; ++i)
        if (state->read_paths[i].size == name_size &&
            memcmp(state->read_paths[i].data, name, name_size) == 0) return;
    if (state->read_count == RE_IR_MAX_READ_PATHS) return;
    state->read_paths[state->read_count].data = name;
    state->read_paths[state->read_count].size = name_size;
    ++state->read_count;
}

re_status_t re_eval_scratch_own(const re_engine_t *engine, re_eval_scratch_t *scratch, char *owned) {
    size_t capacity;
    char **grown;
    if (scratch->count == scratch->capacity) {
        capacity = scratch->capacity == 0u ? 4u : scratch->capacity * 2u;
        if (capacity < scratch->capacity || capacity > SIZE_MAX / sizeof(*grown)) return RE_STATUS_LIMIT;
        grown = re_realloc(&engine->allocator, scratch->items, capacity * sizeof(*grown));
        if (grown == NULL) return RE_STATUS_OUT_OF_MEMORY;
        scratch->items = grown;
        scratch->capacity = capacity;
    }
    scratch->items[scratch->count++] = owned;
    return RE_STATUS_OK;
}
static re_status_t scratch_push(const re_engine_t *engine, re_ir_eval_state_t *state, char *owned) {
    return re_eval_scratch_own(engine, &state->scratch, owned);
}
void re_eval_scratch_destroy(const re_engine_t *engine, re_eval_scratch_t *scratch) {
    size_t i;
    if (engine == NULL || scratch == NULL) return;
    for (i = 0u; i < scratch->count; ++i) re_free(&engine->allocator, scratch->items[i]);
    re_free(&engine->allocator, scratch->items);
    scratch->items = NULL; scratch->count = 0u; scratch->capacity = 0u;
}
/* Appends the state's owned concat strings to the caller's scratch. On
 * failure the strings stay in the state (state_destroy frees them) so a
 * non-OK status always means the resolved value must not be used. */
static re_status_t scratch_move(const re_engine_t *engine, re_eval_scratch_t *dst,
                                re_ir_eval_state_t *src) {
    size_t need;
    if (src->scratch.count == 0u) return RE_STATUS_OK;
    if (src->scratch.count > SIZE_MAX - dst->count) return RE_STATUS_LIMIT;
    need = dst->count + src->scratch.count;
    if (need > SIZE_MAX / sizeof(*dst->items)) return RE_STATUS_LIMIT;
    if (need > dst->capacity) {
        size_t capacity = dst->capacity == 0u ? 4u : dst->capacity;
        char **grown;
        while (capacity < need) {
            if (capacity > SIZE_MAX / 2u) { capacity = need; break; }
            capacity *= 2u;
        }
        if (capacity < need) return RE_STATUS_LIMIT;
        grown = re_realloc(&engine->allocator, dst->items, capacity * sizeof(*grown));
        if (grown == NULL) return RE_STATUS_OUT_OF_MEMORY;
        dst->items = grown; dst->capacity = capacity;
    }
    memcpy(dst->items + dst->count, src->scratch.items, src->scratch.count * sizeof(*dst->items));
    dst->count = need;
    re_free(&engine->allocator, src->scratch.items);
    src->scratch.items = NULL; src->scratch.count = 0u; src->scratch.capacity = 0u;
    return RE_STATUS_OK;
}

static re_status_t binding_push(const re_engine_t *engine, re_ir_eval_state_t *state,
                                const char *prefix, size_t prefix_size,
                                const char *name, size_t name_size) {
    re_eval_binding_t *binding;
    char *copy;
    if (state->binding_count == state->binding_capacity) {
        size_t capacity = state->binding_capacity == 0u ? 4u : state->binding_capacity * 2u;
        re_eval_binding_t *grown;
        if (capacity < state->binding_capacity || capacity > SIZE_MAX / sizeof(*grown)) return RE_STATUS_LIMIT;
        grown = re_realloc(&engine->allocator, state->bindings, capacity * sizeof(*grown));
        if (grown == NULL) return RE_STATUS_OUT_OF_MEMORY;
        state->bindings = grown;
        state->binding_capacity = capacity;
    }
    copy = re_alloc(&engine->allocator, name_size + 1u);
    if (copy == NULL) return RE_STATUS_OUT_OF_MEMORY;
    memcpy(copy, name, name_size);
    copy[name_size] = '\0';
    binding = &state->bindings[state->binding_count++];
    binding->prefix = prefix;
    binding->prefix_size = prefix_size;
    binding->name = copy;
    binding->name_size = name_size;
    return RE_STATUS_OK;
}
static void binding_pop(const re_engine_t *engine, re_ir_eval_state_t *state) {
    if (state->binding_count == 0u) return;
    re_free(&engine->allocator, state->bindings[--state->binding_count].name);
}
/* Resolves a fact path through the active bindings, innermost first. A path
 * equal to a bound prefix or starting with "<prefix>." is rewritten onto the
 * bound candidate name; anything else passes through unchanged. The rewritten
 * path is scratch-owned so the borrowed-value convention is preserved. */
static re_status_t bound_fact_path(const re_engine_t *engine, re_ir_eval_state_t *state,
                                   const char *name, size_t name_size, re_string_t *out) {
    size_t i = state->binding_count;
    while (i != 0u) {
        const re_eval_binding_t *binding = &state->bindings[--i];
        int match = name_size == binding->prefix_size ||
                    (name_size > binding->prefix_size && name[binding->prefix_size] == '.');
        if (match && memcmp(name, binding->prefix, binding->prefix_size) == 0) {
            size_t suffix_size = name_size - binding->prefix_size;
            char *rebound;
            re_status_t status;
            if (binding->name_size > SIZE_MAX - suffix_size - 1u) return RE_STATUS_LIMIT;
            rebound = re_alloc(&engine->allocator, binding->name_size + suffix_size + 1u);
            if (rebound == NULL) return RE_STATUS_OUT_OF_MEMORY;
            memcpy(rebound, binding->name, binding->name_size);
            memcpy(rebound + binding->name_size, name + binding->prefix_size, suffix_size);
            rebound[binding->name_size + suffix_size] = '\0';
            status = scratch_push(engine, state, rebound);
            if (status != RE_STATUS_OK) { re_free(&engine->allocator, rebound); return status; }
            out->data = rebound;
            out->size = binding->name_size + suffix_size;
            return RE_STATUS_OK;
        }
    }
    out->data = name;
    out->size = name_size;
    return RE_STATUS_OK;
}
/* Active facts whose name equals the prefix or starts with it (upstream
 * pattern_matcher.rs candidate heuristic), scanned in entry order from
 * *position; *position advances past the returned candidate. */
static const re_fact_entry_t *next_candidate(const re_facts_t *facts, const char *prefix,
                                             size_t prefix_size, size_t *position) {
    const re_facts_t *view = facts->transaction != NULL ? facts->transaction->staged : facts;
    while (*position < view->count) {
        const re_fact_entry_t *entry = &view->entries[(*position)++];
        if (!entry->active) continue;
        if (entry->name_size >= prefix_size && memcmp(entry->name, prefix, prefix_size) == 0)
            return entry;
    }
    return NULL;
}
/* A8 retract gating: nonzero when the flag fact `_retracted_<root>` (root =
 * the text before the first '.' of the path, or the whole path) exists and
 * holds BOOL true. The flag facts are ordinary facts (visible to
 * re_facts_get); gating applies only to condition reads, whose callers set
 * state->gate_retracts. Scans the (transaction-staged) entries directly so no
 * flag-name string is ever built. */
static int retracted_root(const re_facts_t *facts, const char *path, size_t path_size) {
    static const char prefix[] = "_retracted_";
    const re_facts_t *view = facts->transaction != NULL ? facts->transaction->staged : facts;
    size_t root = 0u;
    size_t i;
    while (root < path_size && path[root] != '.') ++root;
    for (i = 0u; i < view->count; ++i) {
        const re_fact_entry_t *entry = &view->entries[i];
        if (!entry->active) continue;
        if (entry->name_size != sizeof(prefix) - 1u + root) continue;
        if (memcmp(entry->name, prefix, sizeof(prefix) - 1u) != 0) continue;
        if (memcmp(entry->name + sizeof(prefix) - 1u, path, root) != 0) continue;
        return entry->value.type == RE_VALUE_BOOL && entry->value.as.boolean;
    }
    return 0;
}
typedef struct re_scan_item_t { size_t index; int is_term; } re_scan_item_t;
static int scan_push(const re_engine_t *engine, re_scan_item_t **stack, size_t *count,
                     size_t *capacity, size_t index, int is_term) {
    if (*count == *capacity) {
        size_t next = *capacity == 0u ? 8u : *capacity * 2u;
        re_scan_item_t *grown;
        if (next < *capacity || next > SIZE_MAX / sizeof(*grown)) return 0;
        grown = re_realloc(&engine->allocator, *stack, next * sizeof(*grown));
        if (grown == NULL) return 0;
        *stack = grown;
        *capacity = next;
    }
    (*stack)[*count].index = index;
    (*stack)[*count].is_term = is_term;
    ++*count;
    return 1;
}
/* Leftmost (source-order) RE_IR_TERM_FACT reachable from an expression:
 * expressions descend first-then-second, terms descend arguments in order.
 * Iterative with a heap stack so pathologically deep IR cannot overflow the
 * C stack. Returns NULL on allocation failure as well as when no fact
 * reference exists; both collapse to the caller's no-prefix fallback. */
static const re_ir_term_t *leftmost_fact_term(const re_engine_t *engine,
                                              const re_ir_program_t *ir, size_t expr_index) {
    re_scan_item_t *stack = NULL;
    size_t count = 0u, capacity = 0u;
    const re_ir_term_t *found = NULL;
    size_t i;
    if (!scan_push(engine, &stack, &count, &capacity, expr_index, 0)) return NULL;
    while (count != 0u) {
        re_scan_item_t item = stack[--count];
        if (item.is_term) {
            const re_ir_term_t *term = &ir->terms[item.index];
            if (term->kind == RE_IR_TERM_FACT) { found = term; break; }
            /* Reverse-order pushes keep the traversal pre-order. */
            for (i = term->argument_count; i != 0u; --i)
                if (!scan_push(engine, &stack, &count, &capacity, term->argument_indices[i - 1u], 1)) goto done;
        } else {
            const re_ir_expr_t *expr = &ir->exprs[item.index];
            if (expr->kind == RE_EXPR_TRUE || expr->kind == RE_EXPR_FALSE ||
                expr->kind == RE_EXPR_ACCUMULATE) {
                /* No fact reference: A6 accumulate carries its source pattern
                 * as payload strings, not terms. */
                continue;
            } else if (expr->kind == RE_EXPR_AND || expr->kind == RE_EXPR_OR) {
                if (!scan_push(engine, &stack, &count, &capacity, expr->second, 0)) goto done;
                if (!scan_push(engine, &stack, &count, &capacity, expr->first, 0)) goto done;
            } else if (expr->kind == RE_EXPR_NOT || expr->kind == RE_EXPR_TYPED ||
                       ((expr->kind == RE_EXPR_EXISTS || expr->kind == RE_EXPR_FORALL) && expr->nested)) {
                /* A9: the typed form's inner expression rides `first` too. */
                if (!scan_push(engine, &stack, &count, &capacity, expr->first, 0)) goto done;
            } else if (expr->kind == RE_EXPR_MULTIFIELD) {
                /* A5: the array path term is the only fact reference (count's
                 * right operand is a numeric literal). */
                if (!scan_push(engine, &stack, &count, &capacity, expr->left, 1)) goto done;
            } else if (expr->kind == RE_EXPR_TEST) {
                /* A9: the call term; its arguments may hold fact paths. */
                if (!scan_push(engine, &stack, &count, &capacity, expr->left, 1)) goto done;
            } else {
                /* COMPARE, or the restricted quantifier form: left term
                 * precedes right term. */
                if (!scan_push(engine, &stack, &count, &capacity, expr->right, 1)) goto done;
                if (!scan_push(engine, &stack, &count, &capacity, expr->left, 1)) goto done;
            }
        }
    }
done:
    re_free(&engine->allocator, stack);
    return found;
}
/* Extracts the quantifier target prefix: the text before the first '.' of the
 * leftmost field reference in the inner expression (D7). Returns 0 when no
 * dotted fact reference exists (upstream's plain-store fallback). */
static int quantifier_prefix(const re_engine_t *engine, const re_ir_program_t *ir,
                             size_t inner, const char **prefix, size_t *prefix_size) {
    const re_ir_term_t *target = leftmost_fact_term(engine, ir, inner);
    const char *dot;
    if (target == NULL || target->name == NULL) return 0;
    dot = memchr(target->name, '.', target->name_size);
    if (dot == NULL || dot == target->name) return 0;
    *prefix = target->name;
    *prefix_size = (size_t)(dot - target->name);
    return 1;
}

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
    if (frame->pushed_binding) binding_pop(engine, state);
    re_free(&engine->allocator, frame->arguments);
    frame->arguments = NULL;
    /* The path strings themselves are scratch-owned; only the array is. */
    re_free(&engine->allocator, frame->arg_paths);
    frame->arg_paths = NULL;
}
/* Candidate-iteration error absorption (upstream pattern_matcher.rs scores a
 * failing candidate false and continues): a RE_STATUS_NOT_FOUND raised while
 * evaluating a quantifier's inner expression against the current candidate —
 * typically a rebound read on a non-conforming lookalike fact (prefix "Score"
 * also matches "Scoreboard", which may lack the member) — unwinds the frame
 * stack to the innermost iterating quantifier frame and scores that candidate
 * false; its stage-12 continuation pops the binding and advances. Only
 * NOT_FOUND is absorbed; OOM/LIMIT/NOT_SUPPORTED/INVALID_ARGUMENT propagate,
 * and the plain-store fallback (stage 13u, no pushed binding) never absorbs. */
static int absorb_candidate_miss(const re_engine_t *engine, const re_ir_program_t *ir,
                                 re_ir_eval_state_t *state) {
    size_t i;
    const re_eval_frame_t *top;
    /* Only a failed fact-path read (a rebound candidate miss) is absorbable.
     * Function lookup also reports unknown functions as NOT_FOUND, and those
     * must stay hard errors, so the failing frame has to be a FACT term. */
    if (state->frame_count == 0u) return 0;
    top = &state->frames[state->frame_count - 1u];
    if (top->kind != RE_FRAME_TERM || ir->terms[top->index].kind != RE_IR_TERM_FACT) return 0;
    i = state->frame_count;
    while (i != 0u) {
        re_eval_frame_t *frame = &state->frames[i - 1u];
        if (frame->kind == RE_FRAME_EXPR) {
            const re_ir_expr_t *expr = &ir->exprs[frame->index];
            if (((expr->kind == RE_EXPR_EXISTS || expr->kind == RE_EXPR_FORALL) &&
                 expr->nested && frame->pushed_binding) ||
                /* A9: the typed form iterates candidates identically (its
                 * prefix is the declared type, so no `nested` flag). */
                (expr->kind == RE_EXPR_TYPED && frame->pushed_binding)) {
                while (state->frame_count > i) {
                    frame_cleanup(engine, state, &state->frames[state->frame_count - 1u]);
                    --state->frame_count;
                }
                /* Stage is already 12u (set before the inner frame was
                 * pushed); the missed candidate scores false. */
                state->frames[state->frame_count - 1u].matched = 0;
                return 1;
            }
        }
        --i;
    }
    return 0;
}

/* Built-in argument-miss absorption (A3; upstream condition_evaluator.rs
 * scores a condition false when a function argument cannot be resolved): a
 * RE_STATUS_NOT_FOUND raised while resolving a bare fact-path argument of a
 * built-in function (typically an absent fact) unwinds the frame stack to the
 * innermost built-in FUNCTION frame and makes it yield
 * re_builtin_arg_miss_result() - false for every built-in except the negated
 * presence probes notExists/not_exists, whose missing path is their truth.
 * This turns the miss into an ordinary false instead of skipping the whole
 * rule, so sibling OR branches still evaluate. Only NOT_FOUND from a FACT
 * term is absorbable; a user-function frame or a goal boundary between the
 * miss and the built-in keeps the error propagating, and unknown-function
 * lookups (the failing frame is the FUNCTION term itself) are untouched.
 * Runs after absorb_candidate_miss: inside an iterating quantifier the
 * candidate-false scoring wins. */
static int absorb_builtin_arg_miss(const re_engine_t *engine, const re_ir_program_t *ir,
                                   re_ir_eval_state_t *state) {
    size_t i;
    const re_eval_frame_t *top;
    if (state->frame_count == 0u) return 0;
    top = &state->frames[state->frame_count - 1u];
    if (top->kind != RE_FRAME_TERM || ir->terms[top->index].kind != RE_IR_TERM_FACT) return 0;
    i = state->frame_count;
    while (i != 0u) {
        re_eval_frame_t *frame = &state->frames[i - 1u];
        if (frame->kind == RE_FRAME_TERM &&
            (ir->terms[frame->index].kind == RE_IR_TERM_FUNCTION ||
             ir->terms[frame->index].kind == RE_IR_TERM_GOAL)) {
            const re_ir_term_t *function = &ir->terms[frame->index];
            if (function->kind != RE_IR_TERM_FUNCTION || frame->function != NULL ||
                !re_builtin_is(function->name, function->name_size)) return 0;
            while (state->frame_count > i) {
                frame_cleanup(engine, state, &state->frames[state->frame_count - 1u]);
                --state->frame_count;
            }
            frame = &state->frames[state->frame_count - 1u];
            frame->result.type = RE_VALUE_BOOL;
            frame->result.as.boolean = re_builtin_arg_miss_result(function->name, function->name_size);
            frame->stage = 99u;
            return 1;
        }
        --i;
    }
    return 0;
}

static re_status_t arithmetic(const re_engine_t *engine, re_ir_eval_state_t *state,
                              const re_ir_term_t *term, const re_value_t *left,
                              const re_value_t *right, re_value_t *value) {
    int use_double = left->type == RE_VALUE_DOUBLE || right->type == RE_VALUE_DOUBLE;
    if (term->arithmetic_operator == RE_ARITH_ADD &&
        ((left->type != RE_VALUE_INT64 && left->type != RE_VALUE_DOUBLE) ||
         (right->type != RE_VALUE_INT64 && right->type != RE_VALUE_DOUBLE))) {
        /* Upstream apply_operator: `+` on a non-numeric operand concatenates,
         * but only String+String; anything else is an error ("Only strings
         * can be concatenated"). The joined string is scratch-owned so the
         * frame machine's borrowed-value convention is preserved. */
        char *joined;
        size_t size;
        re_status_t status;
        if (left->type != RE_VALUE_STRING || right->type != RE_VALUE_STRING)
            return RE_STATUS_INVALID_ARGUMENT;
        if (left->as.string.size > SIZE_MAX - right->as.string.size - 1u) return RE_STATUS_LIMIT;
        size = left->as.string.size + right->as.string.size;
        joined = re_alloc(&engine->allocator, size + 1u);
        if (joined == NULL) return RE_STATUS_OUT_OF_MEMORY;
        memcpy(joined, left->as.string.data, left->as.string.size);
        memcpy(joined + left->as.string.size, right->as.string.data, right->as.string.size);
        joined[size] = '\0';
        status = scratch_push(engine, state, joined);
        if (status != RE_STATUS_OK) { re_free(&engine->allocator, joined); return status; }
        value->type = RE_VALUE_STRING;
        value->as.string.data = joined;
        value->as.string.size = size;
        return RE_STATUS_OK;
    }
    if ((left->type != RE_VALUE_INT64 && left->type != RE_VALUE_DOUBLE) ||
        (right->type != RE_VALUE_INT64 && right->type != RE_VALUE_DOUBLE)) return RE_STATUS_INVALID_ARGUMENT;
    if (term->arithmetic_operator == RE_ARITH_MODULO) {
        /* f64 % (fmod), matching the division-by-zero error idiom; the result
         * is Integer iff both operands are Integer and the fmod result is
         * integral (always the case for integer inputs), per upstream
         * apply_operator. */
        double l = left->type == RE_VALUE_DOUBLE ? left->as.double_value : (double)left->as.int64_value;
        double r = right->type == RE_VALUE_DOUBLE ? right->as.double_value : (double)right->as.int64_value;
        double result;
        if (r == 0.0) return RE_STATUS_ERROR;
        result = fmod(l, r);
        if (!isfinite(result)) return RE_STATUS_ERROR;
        if (left->type == RE_VALUE_INT64 && right->type == RE_VALUE_INT64 && result == floor(result) &&
            result >= -9223372036854775808.0 && result < 9223372036854775808.0) {
            value->type = RE_VALUE_INT64;
            value->as.int64_value = (int64_t)result;
        } else {
            value->type = RE_VALUE_DOUBLE;
            value->as.double_value = result;
        }
        return RE_STATUS_OK;
    }
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

/* A6 accumulate evaluation (upstream engine.rs L701-830 evaluate_accumulate).
 * The source scan works on the staged-or-live view like next_candidate; the
 * result write goes through re_facts_set, which lands in the staged
 * transaction view when one is active. */
typedef struct re_accum_instance_t { re_string_t segment; int bare; } re_accum_instance_t;
/* Exact flat-key lookup on the view (the upstream instance map is built from
 * flat keys only; no structured-path fallback). */
static const re_value_t *accumulate_field_value(const re_facts_t *view,
                                                const char *path, size_t path_size) {
    size_t i;
    for (i = 0u; i < view->count; ++i)
        if (view->entries[i].active && view->entries[i].name_size == path_size &&
            memcmp(view->entries[i].name, path, path_size) == 0)
            return &view->entries[i].value;
    return NULL;
}
/* Splits a mini-condition string ("field <op> literal") at its operator:
 * scanned longest-first (==, !=, >=, <=, then >, <), first occurrence of each
 * operator wins (upstream's per-operator find() order). The binding decision
 * fixes the reported upstream hazard where a bare >/< could win over >=/<=;
 * the pinned f80a541 array order already matches this scan. */
static int accumulate_condition_split(const char *cond, size_t size,
                                      size_t *op_at, size_t *op_size, re_compare_t *op) {
    static const struct { char text[2]; size_t size; re_compare_t compare; } ops[] = {
        {{'=', '='}, 2u, RE_COMPARE_EQ}, {{'!', '='}, 2u, RE_COMPARE_NE},
        {{'>', '='}, 2u, RE_COMPARE_GE}, {{'<', '='}, 2u, RE_COMPARE_LE},
        {{'>', '\0'}, 1u, RE_COMPARE_GT}, {{'<', '\0'}, 1u, RE_COMPARE_LT}
    };
    size_t k;
    for (k = 0u; k < sizeof(ops) / sizeof(ops[0]); ++k) {
        size_t i;
        for (i = 0u; i + ops[k].size <= size; ++i)
            if (memcmp(cond + i, ops[k].text, ops[k].size) == 0) {
                *op_at = i; *op_size = ops[k].size; *op = ops[k].compare;
                return 1;
            }
    }
    return 0;
}
/* Evaluates one mini-condition against one instance: the field resolves to
 * the flat key "<base><field>"; a missing field, an unparseable literal, or a
 * type the operator does not support scores false (upstream
 * compare_values). The typed compare reuses re_value_compare: String only
 * ==/!=, Integer/Number numeric, Boolean ==/!= (relationals fail to coerce).
 * Documented D4-aligned divergence: Number == is strict (no f64 epsilon). */
static re_status_t accumulate_condition_holds(const re_engine_t *engine, const re_facts_t *view,
                                              const char *base, size_t base_size,
                                              const char *cond, size_t cond_size, int *holds) {
    size_t op_at, op_size, field_start = 0u, field_end, value_start, value_end;
    re_compare_t compare;
    const re_value_t *field_value;
    re_value_t rhs;
    char *path;
    char buffer[64];
    char *end;
    size_t value_size;
    *holds = 0;
    if (!accumulate_condition_split(cond, cond_size, &op_at, &op_size, &compare)) return RE_STATUS_OK;
    field_end = op_at;
    while (field_start < field_end && isspace((unsigned char)cond[field_start])) ++field_start;
    while (field_end > field_start && isspace((unsigned char)cond[field_end - 1u])) --field_end;
    if (field_end == field_start) return RE_STATUS_OK;
    value_start = op_at + op_size; value_end = cond_size;
    while (value_start < value_end && isspace((unsigned char)cond[value_start])) ++value_start;
    while (value_end > value_start && isspace((unsigned char)cond[value_end - 1u])) --value_end;
    /* Upstream trim_matches: every leading/trailing '"' is stripped, then
     * every leading/trailing '\''. */
    while (value_start < value_end && cond[value_start] == '"') ++value_start;
    while (value_end > value_start && cond[value_end - 1u] == '"') --value_end;
    while (value_start < value_end && cond[value_start] == '\'') ++value_start;
    while (value_end > value_start && cond[value_end - 1u] == '\'') --value_end;
    value_size = value_end - value_start;
    if (base_size > SIZE_MAX - (field_end - field_start) - 1u) return RE_STATUS_LIMIT;
    path = re_alloc(&engine->allocator, base_size + (field_end - field_start) + 1u);
    if (path == NULL) return RE_STATUS_OUT_OF_MEMORY;
    memcpy(path, base, base_size);
    memcpy(path + base_size, cond + field_start, field_end - field_start);
    path[base_size + (field_end - field_start)] = '\0';
    field_value = accumulate_field_value(view, path, base_size + (field_end - field_start));
    re_free(&engine->allocator, path);
    if (field_value == NULL) return RE_STATUS_OK;
    if (field_value->type == RE_VALUE_STRING) {
        if (compare != RE_COMPARE_EQ && compare != RE_COMPARE_NE) return RE_STATUS_OK;
        rhs.type = RE_VALUE_STRING;
        rhs.as.string.data = cond + value_start;
        rhs.as.string.size = value_size;
        *holds = re_value_compare(field_value, &rhs, compare);
        return RE_STATUS_OK;
    }
    if (field_value->type == RE_VALUE_INT64) {
        long long parsed;
        if (value_size == 0u || value_size >= sizeof(buffer)) return RE_STATUS_OK;
        memcpy(buffer, cond + value_start, value_size);
        buffer[value_size] = '\0';
        errno = 0;
        parsed = strtoll(buffer, &end, 10);
        if (errno == ERANGE || end != buffer + value_size) return RE_STATUS_OK;
        rhs.type = RE_VALUE_INT64;
        rhs.as.int64_value = (int64_t)parsed;
        *holds = re_value_compare(field_value, &rhs, compare);
        return RE_STATUS_OK;
    }
    if (field_value->type == RE_VALUE_DOUBLE) {
        double parsed;
        if (value_size == 0u || value_size >= sizeof(buffer)) return RE_STATUS_OK;
        memcpy(buffer, cond + value_start, value_size);
        buffer[value_size] = '\0';
        parsed = strtod(buffer, &end);
        if (end != buffer + value_size) return RE_STATUS_OK;
        rhs.type = RE_VALUE_DOUBLE;
        rhs.as.double_value = parsed;
        *holds = re_value_compare(field_value, &rhs, compare);
        return RE_STATUS_OK;
    }
    if (field_value->type == RE_VALUE_BOOL) {
        if (value_size == 4u && memcmp(cond + value_start, "true", 4u) == 0) {
            rhs.type = RE_VALUE_BOOL; rhs.as.boolean = 1;
        } else if (value_size == 5u && memcmp(cond + value_start, "false", 5u) == 0) {
            rhs.type = RE_VALUE_BOOL; rhs.as.boolean = 0;
        } else return RE_STATUS_OK;
        *holds = re_value_compare(field_value, &rhs, compare);
        return RE_STATUS_OK;
    }
    return RE_STATUS_OK;
}
static re_status_t accumulate_inject(const re_engine_t *engine, re_facts_t *facts,
                                     const re_ir_expr_t *expr) {
    const re_facts_t *view = facts->transaction != NULL ? facts->transaction->staged : facts;
    re_accum_instance_t *instances = NULL;
    size_t instance_count = 0u, instance_cap = 0u;
    re_value_t *values = NULL;
    size_t value_count = 0u, value_cap = 0u;
    size_t matching = 0u;
    size_t i, j;
    re_value_t result;
    re_status_t status = RE_STATUS_OK;
    /* Flat-scan the "<type>." keys and collect the distinct instance
     * segments: the text up to the next '.' (or "default" for a bare
     * "<type>.<field>" key). Upstream merges a literally-"default" instance
     * with the bare-key default; locally they stay distinct (bounded
     * divergence in a degenerate naming case). */
    for (i = 0u; i < view->count; ++i) {
        const re_fact_entry_t *entry = &view->entries[i];
        const char *rest;
        const char *dot;
        re_accum_instance_t instance;
        if (!entry->active || entry->name_size <= expr->accumulate_type_size + 1u ||
            memcmp(entry->name, expr->accumulate_type, expr->accumulate_type_size) != 0 ||
            entry->name[expr->accumulate_type_size] != '.') continue;
        rest = entry->name + expr->accumulate_type_size + 1u;
        dot = memchr(rest, '.', entry->name_size - expr->accumulate_type_size - 1u);
        instance.bare = dot == NULL;
        instance.segment.data = dot != NULL ? rest : "default";
        instance.segment.size = dot != NULL ? (size_t)(dot - rest) : 7u;
        for (j = 0u; j < instance_count; ++j)
            if (instances[j].bare == instance.bare &&
                instances[j].segment.size == instance.segment.size &&
                memcmp(instances[j].segment.data, instance.segment.data, instance.segment.size) == 0) break;
        if (j != instance_count) continue;
        if (instance_count == instance_cap) {
            size_t next = instance_cap == 0u ? 8u : instance_cap * 2u;
            re_accum_instance_t *grown;
            if (next < instance_cap || next > SIZE_MAX / sizeof(*grown)) { status = RE_STATUS_LIMIT; goto done; }
            grown = re_realloc(&engine->allocator, instances, next * sizeof(*grown));
            if (grown == NULL) { status = RE_STATUS_OUT_OF_MEMORY; goto done; }
            instances = grown; instance_cap = next;
        }
        instances[instance_count++] = instance;
    }
    /* Per instance: every source condition must hold; matching instances
     * contribute their extract-field value (when one is present). */
    for (i = 0u; i < instance_count && status == RE_STATUS_OK; ++i) {
        char *base;
        size_t base_size;
        size_t seg = instances[i].bare ? 0u : instances[i].segment.size + 1u;
        int matches = 1;
        if (expr->accumulate_type_size > SIZE_MAX - seg - 2u) { status = RE_STATUS_LIMIT; break; }
        base_size = expr->accumulate_type_size + 1u + seg;
        base = re_alloc(&engine->allocator, base_size + 1u);
        if (base == NULL) { status = RE_STATUS_OUT_OF_MEMORY; break; }
        memcpy(base, expr->accumulate_type, expr->accumulate_type_size);
        base[expr->accumulate_type_size] = '.';
        if (!instances[i].bare) {
            memcpy(base + expr->accumulate_type_size + 1u,
                   instances[i].segment.data, instances[i].segment.size);
            base[expr->accumulate_type_size + 1u + instances[i].segment.size] = '.';
        }
        base[base_size] = '\0';
        for (j = 0u; matches && j < expr->accumulate_condition_count; ++j) {
            status = accumulate_condition_holds(engine, view, base, base_size,
                                                expr->accumulate_conditions[j],
                                                strlen(expr->accumulate_conditions[j]), &matches);
            if (status != RE_STATUS_OK) break;
        }
        if (status == RE_STATUS_OK && matches) {
            ++matching;
            if (expr->accumulate_field != NULL) {
                char *path;
                const re_value_t *extracted;
                if (base_size > SIZE_MAX - expr->accumulate_field_size - 1u) status = RE_STATUS_LIMIT;
                else {
                    path = re_alloc(&engine->allocator, base_size + expr->accumulate_field_size + 1u);
                    if (path == NULL) status = RE_STATUS_OUT_OF_MEMORY;
                    else {
                        memcpy(path, base, base_size);
                        memcpy(path + base_size, expr->accumulate_field, expr->accumulate_field_size);
                        path[base_size + expr->accumulate_field_size] = '\0';
                        extracted = accumulate_field_value(view, path, base_size + expr->accumulate_field_size);
                        re_free(&engine->allocator, path);
                        if (extracted != NULL) {
                            if (value_count == value_cap) {
                                size_t next = value_cap == 0u ? 8u : value_cap * 2u;
                                re_value_t *grown;
                                if (next < value_cap || next > SIZE_MAX / sizeof(*grown)) status = RE_STATUS_LIMIT;
                                else {
                                    grown = re_realloc(&engine->allocator, values, next * sizeof(*grown));
                                    if (grown == NULL) status = RE_STATUS_OUT_OF_MEMORY;
                                    else { values = grown; value_cap = next; }
                                }
                            }
                            if (status == RE_STATUS_OK) values[value_count++] = *extracted;
                        }
                    }
                }
            }
        }
        re_free(&engine->allocator, base);
    }
    /* Fold. count is the i64 count of extracted values - or, for the
     * $var-less form, of matching instances (local divergence: upstream
     * extracts nothing then and counts 0). The numeric folds ignore
     * non-numeric values and yield DOUBLE 0.0 on an empty set (upstream's
     * Float(0.0)); re_accumulator_evaluate is reused for the non-empty fold
     * after pre-filtering, since it errors on non-numeric input instead. */
    if (status == RE_STATUS_OK) {
        if (expr->accumulate_func == RE_ACCUM_COUNT) {
            result.type = RE_VALUE_INT64;
            result.as.int64_value = (int64_t)(expr->accumulate_field != NULL ? value_count : matching);
        } else {
            size_t numeric = 0u;
            for (i = 0u; i < value_count; ++i)
                if (values[i].type == RE_VALUE_INT64 || values[i].type == RE_VALUE_DOUBLE)
                    values[numeric++] = values[i];
            if (numeric == 0u) {
                result.type = RE_VALUE_DOUBLE;
                result.as.double_value = 0.0;
            } else {
                status = re_accumulator_evaluate((re_accumulator_kind_t)expr->accumulate_func,
                                                 values, numeric, &result);
            }
        }
    }
    /* Inject "<type>.<func_name>" (the function keeps its source spelling,
     * e.g. avg vs average). */
    if (status == RE_STATUS_OK) {
        char *key;
        size_t key_size;
        if (expr->accumulate_type_size > SIZE_MAX - expr->accumulate_func_name_size - 2u) {
            status = RE_STATUS_LIMIT;
            goto done;
        }
        key_size = expr->accumulate_type_size + 1u + expr->accumulate_func_name_size;
        key = re_alloc(&engine->allocator, key_size + 1u);
        if (key == NULL) { status = RE_STATUS_OUT_OF_MEMORY; goto done; }
        memcpy(key, expr->accumulate_type, expr->accumulate_type_size);
        key[expr->accumulate_type_size] = '.';
        memcpy(key + expr->accumulate_type_size + 1u,
               expr->accumulate_func_name, expr->accumulate_func_name_size);
        key[key_size] = '\0';
        status = re_facts_set(facts, (re_string_t){key, key_size}, &result);
        re_free(&engine->allocator, key);
    }
done:
    re_free(&engine->allocator, values);
    re_free(&engine->allocator, instances);
    return status;
}

/* C5 stream-pattern CE evaluation (upstream rust-rule-engine v1.21.4
 * f80a541 src/parser/grl/stream_syntax.rs parse_stream_pattern; rule_engine.h
 * documents the semantics and the bounded divergences). The CE consults the
 * engine's stream registry: an UNREGISTERED stream reports
 * RE_STATUS_NOT_SUPPORTED, the honest gate C3 pinned (the brief's NOT_FOUND
 * mapping is deliberately NOT used - compute_rule_activations swallows
 * NOT_FOUND as an ordinary non-match, which would silently flip the pinned
 * C3 behavior). Event-time filtering uses the CLAUSE's duration against the
 * registered window's watermark; the type filter matches the event NAME and
 * `var` denotes the event's scalar value (local events carry a name plus one
 * scalar; upstream matches event_type against its event type field). The
 * result is exists semantics: matched is set on the first qualifying event
 * (timestamp order, the nominal per-activation binding; nothing downstream
 * consumes the binding locally). */
static int stream_scope_contains(const re_stream_window_t *window,
                                 const re_ir_expr_t *expr, uint64_t session_start,
                                 uint64_t timestamp) {
    uint64_t duration = expr->stream_window_duration_ms;
    if (!expr->stream_has_window) return 1; /* no clause: all retained events */
    if (expr->stream_window_kind == RE_STREAM_WINDOW_SLIDING) {
        /* [watermark - duration, watermark], saturating sub. */
        uint64_t lo = duration > window->watermark ? 0u : window->watermark - duration;
        return timestamp >= lo && timestamp <= window->watermark;
    }
    if (expr->stream_window_kind == RE_STREAM_WINDOW_TUMBLING) {
        /* The current bucket (upstream window.rs: ts / window_ms); a zero
         * duration is rejected by the caller (bucket size 0 is undefined). */
        return timestamp / duration == window->watermark / duration;
    }
    /* session: the current open session (tumbling_session.c semantics). */
    return timestamp >= session_start;
}

/* Start timestamp of the current open session: the newest retained event
 * and its backward chain with consecutive gaps <= duration. The events
 * array is only append-ordered for bounded windows (late ACCEPT records can
 * land out of order), so the timestamps are sorted into a scratch copy
 * first. */
static re_status_t session_scope_start(const re_engine_t *engine,
                                       const re_stream_window_t *window,
                                       uint64_t duration, uint64_t *out_start) {
    uint64_t *timestamps;
    uint64_t last;
    size_t i;
    if (window->count == 0u) { *out_start = 0u; return RE_STATUS_OK; }
    if (window->count > SIZE_MAX / sizeof(*timestamps)) return RE_STATUS_LIMIT;
    timestamps = re_alloc(&engine->allocator, window->count * sizeof(*timestamps));
    if (timestamps == NULL) return RE_STATUS_OUT_OF_MEMORY;
    for (i = 0u; i < window->count; ++i) timestamps[i] = window->events[i].timestamp;
    /* Insertion sort ascending (bounded by the window's own max_events). */
    for (i = 1u; i < window->count; ++i) {
        uint64_t current = timestamps[i];
        size_t j = i;
        while (j != 0u && timestamps[j - 1u] > current) {
            timestamps[j] = timestamps[j - 1u];
            --j;
        }
        timestamps[j] = current;
    }
    last = timestamps[window->count - 1u];
    i = window->count - 1u;
    while (i != 0u && last - timestamps[i - 1u] <= duration) {
        last = timestamps[i - 1u];
        --i;
    }
    *out_start = timestamps[i];
    re_free(&engine->allocator, timestamps);
    return RE_STATUS_OK;
}

static re_status_t stream_pattern_match(const re_engine_t *engine,
                                        const re_ir_expr_t *expr, int *matched) {
    const re_stream_window_t *window;
    uint64_t session_start = 0u;
    size_t index;
    re_status_t status = RE_STATUS_OK;
    *matched = 0;
    window = re_engine_stream_lookup(engine, expr->stream_name, expr->stream_name_size);
    if (window == NULL) return RE_STATUS_NOT_SUPPORTED; /* the pinned C3 gate */
    if (expr->stream_has_window && expr->stream_window_kind == RE_STREAM_WINDOW_TUMBLING &&
        expr->stream_window_duration_ms == 0u)
        return RE_STATUS_INVALID_ARGUMENT; /* bucket size 0 is undefined */
    if (expr->stream_has_window && expr->stream_window_kind == RE_STREAM_WINDOW_SESSION) {
        status = session_scope_start(engine, window, expr->stream_window_duration_ms,
                                     &session_start);
        if (status != RE_STATUS_OK) return status;
    }
    for (index = 0u; index < window->count; ++index) {
        const re_stream_event_impl_t *event = &window->events[index];
        if (expr->stream_has_event_type &&
            (event->name_size != expr->stream_event_type_size ||
             memcmp(event->name, expr->stream_event_type, expr->stream_event_type_size) != 0))
            continue;
        if (!stream_scope_contains(window, expr, session_start, event->timestamp)) continue;
        *matched = 1;
        break;
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
                if (term->kind == RE_IR_TERM_BOOL || term->kind == RE_IR_TERM_INT64 || term->kind == RE_IR_TERM_DOUBLE || term->kind == RE_IR_TERM_STRING || term->kind == RE_IR_TERM_NULL) {
                    frame->result = term->value; frame->stage = 99u;
                } else if (term->kind == RE_IR_TERM_FACT) {
                    re_string_t path;
                    status = bound_fact_path(engine, state, term->name, term->name_size, &path);
                    if (status == RE_STATUS_OK) {
                        /* A8: a condition read whose root carries the
                         * _retracted_ flag misses exactly like an absent
                         * fact (quantifier/builtin absorbers score it false;
                         * a plain comparison propagates NOT_FOUND, which the
                         * run loop already treats as a non-match). */
                        if (state->gate_retracts && retracted_root(facts, path.data, path.size))
                            status = RE_STATUS_NOT_FOUND;
                        else
                            status = re_facts_get_path(facts, path, &frame->result);
                        if (status == RE_STATUS_OK) record_read(state, term->name, term->name_size);
                    }
                    frame->stage = 99u;
                } else if (term->kind == RE_IR_TERM_ARITHMETIC) {
                    if (term->argument_count != 2u || term->argument_indices == NULL) status = RE_STATUS_INVALID_ARGUMENT;
                    else { frame->stage = 1u; status = frame_push(engine, state, RE_FRAME_TERM, term->argument_indices[0], state->frame_count - 1u, 0u); }
                } else if (term->kind == RE_IR_TERM_GOAL) {
                    frame->stage = 10u;
                } else if (term->kind == RE_IR_TERM_FUNCTION) {
                    for (frame->function = engine->functions; frame->function != NULL; frame->function = frame->function->next)
                        if (!frame->function->unregistered && frame->function->name_size == term->name_size && memcmp(frame->function->name, term->name, term->name_size) == 0) break;
                    /* A3: the user registry wins; the built-in functions
                     * (builtins.c) are the fallback when no registered
                     * function matches, and a miss on both stays NOT_FOUND.
                     * Built-in frames are marked by function == NULL. */
                    if (frame->function == NULL && !re_builtin_is(term->name, term->name_size)) status = RE_STATUS_NOT_FOUND;
                    else {
                        frame->arguments = term->argument_count == 0u ? NULL :
                            term->argument_count > SIZE_MAX / sizeof(*frame->arguments) ? NULL :
                            re_alloc(&engine->allocator, term->argument_count * sizeof(*frame->arguments));
                        if (term->argument_count != 0u && frame->arguments == NULL) status = RE_STATUS_OUT_OF_MEMORY;
                        else {
                            if (frame->function == NULL && term->argument_count != 0u) {
                                size_t arg_index;
                                frame->arg_paths = term->argument_count > SIZE_MAX / sizeof(*frame->arg_paths) ? NULL :
                                    re_alloc(&engine->allocator, term->argument_count * sizeof(*frame->arg_paths));
                                if (frame->arg_paths == NULL) status = RE_STATUS_OUT_OF_MEMORY;
                                else {
                                    memset(frame->arg_paths, 0, term->argument_count * sizeof(*frame->arg_paths));
                                    for (arg_index = 0u; status == RE_STATUS_OK && arg_index < term->argument_count; ++arg_index) {
                                        const re_ir_term_t *argument = &ir->terms[term->argument_indices[arg_index]];
                                        if (argument->kind != RE_IR_TERM_FACT) continue;
                                        status = bound_fact_path(engine, state, argument->name, argument->name_size,
                                                                 &frame->arg_paths[arg_index]);
                                    }
                                }
                            }
                            if (status == RE_STATUS_OK) {
                                if (term->argument_count == 0u) frame->stage = 20u;
                                else { frame->stage = 21u; status = frame_push(engine, state, RE_FRAME_TERM, term->argument_indices[0], state->frame_count - 1u, 0u); }
                            }
                        }
                    }
                } else status = RE_STATUS_NOT_SUPPORTED;
            } else if (frame->stage == 1u) {
                frame->stage = 2u; status = frame_push(engine, state, RE_FRAME_TERM, term->argument_indices[1], state->frame_count - 1u, 1u);
            } else if (frame->stage == 2u) {
                status = arithmetic(engine, state, term, &frame->left, &frame->right, &frame->result); frame->stage = 99u;
            } else if (frame->stage == 21u) {
                frame->arguments[frame->position++] = frame->left;
                if (frame->position < term->argument_count) status = frame_push(engine, state, RE_FRAME_TERM, term->argument_indices[frame->position], state->frame_count - 1u, 0u);
                else frame->stage = 20u;
            } else if (frame->stage == 20u) {
                if (frame->function != NULL) {
                    frame->function->active_calls++; status = frame->function->call((re_engine_t *)engine, facts, frame->arguments, term->argument_count, &frame->result, frame->function->context); frame->function->active_calls--;
                } else {
                    /* Built-in fallback (A3/A4): the registry missed, dispatch
                     * by name. The const cast hands the built-in the engine
                     * for its allocator and the deterministic random() state
                     * (mutated under the single-threaded-handles contract);
                     * produced strings are owned by the state's scratch. */
                    status = re_builtin_call((re_engine_t *)engine, facts,
                                             (re_string_t){term->name, term->name_size},
                                             frame->arguments, frame->arg_paths, term->argument_count,
                                             &frame->result, &state->scratch);
                }
                frame->stage = 99u;
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
                else if ((expr->kind == RE_EXPR_EXISTS || expr->kind == RE_EXPR_FORALL) && expr->nested) {
                    /* Parenthesized quantifier: iterate the prefix-matched
                     * candidate facts, evaluating the inner expression with
                     * the prefix rebound to each candidate (D7). Without an
                     * extractable target type the inner is evaluated once
                     * against the plain fact store (upstream fallback). */
                    const char *prefix;
                    size_t prefix_size;
                    if (!quantifier_prefix(engine, ir, expr->first, &prefix, &prefix_size)) {
                        frame->stage = 13u;
                        status = frame_push(engine, state, RE_FRAME_EXPR, expr->first,
                                            state->frame_count - 1u, 0u);
                    } else {
                        const re_fact_entry_t *candidate;
                        frame->position = 0u;
                        candidate = next_candidate(facts, prefix, prefix_size, &frame->position);
                        if (candidate == NULL) {
                            /* D6: forall over an empty candidate set is
                             * vacuously true; exists is false. */
                            frame->matched = expr->kind == RE_EXPR_FORALL;
                            frame->stage = 99u;
                        } else {
                            status = binding_push(engine, state, prefix, prefix_size,
                                                  candidate->name, candidate->name_size);
                            if (status == RE_STATUS_OK) {
                                frame->pushed_binding = 1;
                                frame->stage = 12u;
                                status = frame_push(engine, state, RE_FRAME_EXPR, expr->first,
                                                    state->frame_count - 1u, 0u);
                            }
                        }
                    }
                }
                else if (expr->kind == RE_EXPR_EXISTS) {
                    re_string_t path;
                    status = bound_fact_path(engine, state, ir->terms[expr->left].name,
                                             ir->terms[expr->left].name_size, &path);
                    if (status == RE_STATUS_OK && state->gate_retracts &&
                        retracted_root(facts, path.data, path.size))
                        status = RE_STATUS_NOT_FOUND; /* A8: retracted reads as absent. */
                    if (status == RE_STATUS_OK)
                        status = re_facts_get_path(facts, path, &frame->left);
                    if (status == RE_STATUS_OK) record_read(state, ir->terms[expr->left].name, ir->terms[expr->left].name_size);
                    if (status == RE_STATUS_NOT_FOUND) {
                        status = RE_STATUS_OK;
                        frame->matched = 0;
                        frame->stage = 99u;
                    } else if (status == RE_STATUS_OK) {
                        frame->stage = 7u;
                        status = frame_push(engine, state, RE_FRAME_TERM, expr->right,
                                            state->frame_count - 1u, 1u);
                    }
                }
                else if (expr->kind == RE_EXPR_FORALL) {
                    const re_value_handle_t *array = NULL;
                    re_string_t path;
                    status = bound_fact_path(engine, state, ir->terms[expr->left].name,
                                             ir->terms[expr->left].name_size, &path);
                    if (status == RE_STATUS_OK && state->gate_retracts &&
                        retracted_root(facts, path.data, path.size))
                        status = RE_STATUS_NOT_FOUND; /* A8: retracted reads as absent. */
                    if (status == RE_STATUS_OK)
                        status = re_facts_get_structured_path(facts, path, &array);
                    if (status == RE_STATUS_OK) record_read(state, ir->terms[expr->left].name, ir->terms[expr->left].name_size);
                    if (status == RE_STATUS_OK) {
                        if (array->kind != 2) status = RE_STATUS_INVALID_ARGUMENT;
                        else {
                            frame->position = 0u;
                            frame->stage = 8u;
                            status = frame_push(engine, state, RE_FRAME_TERM, expr->right,
                                                state->frame_count - 1u, 1u);
                        }
                    }
                }
                else if (expr->kind == RE_EXPR_MULTIFIELD) {
                    /* A5 multifield array-shape predicate (upstream engine.rs
                     * L1115-1164): probe the (binding-rewritten) path once.
                     * present = the field resolves at all (flat or structured
                     * read, mirroring the exists() built-in); is_array =
                     * structured kind 2. Missing field -> count 0, empty true,
                     * not_empty/first/last false; a present non-array field
                     * counts 1 and is neither empty nor first/last-able. A
                     * resolved path joins the read-set exactly like the
                     * EXISTS/FORALL reads above. Flat-vs-structured conflict
                     * corner: presence follows re_facts_get_path (an exact
                     * flat key wins) while is_array/elements come from the
                     * structured read alone, so a flat scalar shadowing a
                     * same-path structured array member still counts the
                     * member's elements. */
                    const re_ir_term_t *target = &ir->terms[expr->left];
                    const re_value_handle_t *structured = NULL;
                    re_string_t path;
                    re_value_t probe;
                    size_t elements = 0u;
                    int present = 0;
                    int is_array = 0;
                    status = bound_fact_path(engine, state, target->name, target->name_size, &path);
                    if (status == RE_STATUS_OK) {
                        /* A8: a retracted root probes as absent (count 0,
                         * empty true, first/last/not_empty false). */
                        int retracted = state->gate_retracts &&
                            retracted_root(facts, path.data, path.size);
                        if (!retracted && re_facts_get_path(facts, path, &probe) == RE_STATUS_OK) present = 1;
                        if (!retracted && re_facts_get_structured_path(facts, path, &structured) == RE_STATUS_OK) {
                            present = 1;
                            is_array = structured->kind == 2;
                            if (is_array) elements = structured->count;
                        }
                        if (present) record_read(state, target->name, target->name_size);
                        if (expr->multifield == RE_MULTIFIELD_COUNT) {
                            /* The count value rides frame->left; the literal
                             * right term resolves into frame->right and the
                             * shared stage 5u applies expr->compare. */
                            frame->left.type = RE_VALUE_INT64;
                            frame->left.as.int64_value = !present ? 0 : is_array ? (int64_t)elements : 1;
                            frame->stage = 5u;
                            status = frame_push(engine, state, RE_FRAME_TERM, expr->right,
                                                state->frame_count - 1u, 1u);
                        } else {
                            frame->matched =
                                expr->multifield == RE_MULTIFIELD_EMPTY ? (!present || (is_array && elements == 0u)) :
                                expr->multifield == RE_MULTIFIELD_COLLECT ? present :
                                /* FIRST, LAST and NOT_EMPTY share "non-empty
                                 * array" (first/last carry no binding). */
                                (is_array && elements != 0u);
                            frame->stage = 99u;
                        }
                    }
                }
                else if (expr->kind == RE_EXPR_ACCUMULATE) {
                    /* A6: evaluate the fold and inject "<Type>.<func>" as a
                     * fact; the condition itself always matches (upstream
                     * engine.rs L671-691). The write is why
                     * re_condition_is_pure classifies the node impure. */
                    status = accumulate_inject(engine, facts, expr);
                    if (status == RE_STATUS_OK) { frame->matched = 1; frame->stage = 99u; }
                }
                else if (expr->kind == RE_EXPR_TEST) {
                    /* A9 test(f(args)) CE (upstream grl.rs L75-80): evaluate
                     * the call term; stage 14u truthiness-tests the result. */
                    frame->stage = 14u;
                    status = frame_push(engine, state, RE_FRAME_TERM, expr->left,
                                        state->frame_count - 1u, 0u);
                }
                else if (expr->kind == RE_EXPR_TYPED) {
                    /* A9 typed form $x: Type(conds), bounded to
                     * exists-semantics: iterate the declared type's prefix
                     * candidates (the A2 machinery; the quantifiers' derived
                     * prefix is replaced by the explicit type name) and stop
                     * at the first candidate whose inner condition matches.
                     * No candidates -> false. */
                    const re_fact_entry_t *candidate;
                    frame->position = 0u;
                    candidate = next_candidate(facts, expr->typed_type, expr->typed_type_size,
                                               &frame->position);
                    if (candidate == NULL) {
                        frame->matched = 0;
                        frame->stage = 99u;
                    } else {
                        status = binding_push(engine, state, expr->typed_type,
                                              expr->typed_type_size,
                                              candidate->name, candidate->name_size);
                        if (status == RE_STATUS_OK) {
                            frame->pushed_binding = 1;
                            frame->stage = 12u;
                            status = frame_push(engine, state, RE_FRAME_EXPR, expr->first,
                                                state->frame_count - 1u, 0u);
                        }
                    }
                }
                else if (expr->kind == RE_EXPR_STREAM_PATTERN) {
                    /* C5: the stream-pattern CE evaluates against the
                     * engine's stream registry (exists semantics over the
                     * filtered retained events). */
                    status = stream_pattern_match(engine, expr, &frame->matched);
                    if (status == RE_STATUS_OK) frame->stage = 99u;
                }
                else status = RE_STATUS_NOT_SUPPORTED;
            } else if (frame->stage == 1u) {
                if (expr->kind == RE_EXPR_NOT) { frame->matched = !frame->matched; frame->stage = 99u; }
                else if ((expr->kind == RE_EXPR_AND && !frame->matched) || (expr->kind == RE_EXPR_OR && frame->matched)) frame->stage = 99u;
                else { frame->stage = 3u; status = frame_push(engine, state, RE_FRAME_EXPR, expr->second, state->frame_count - 1u, 1u); }
            } else if (frame->stage == 2u) {
                if (expr->compare == RE_COMPARE_IN && ir->terms[expr->right].kind == RE_IR_TERM_ARRAY) { frame->position = 0u; frame->matched = 0; frame->stage = 4u; }
                else if (expr->compare == RE_COMPARE_IN) {
                    re_string_t path;
                    status = bound_fact_path(engine, state, ir->terms[expr->right].name,
                                             ir->terms[expr->right].name_size, &path);
                    frame->stage = 99u;
                    if (status == RE_STATUS_OK && state->gate_retracts &&
                        retracted_root(facts, path.data, path.size))
                        status = RE_STATUS_NOT_FOUND; /* A8: retracted reads as absent. */
                    if (status == RE_STATUS_OK)
                        status = re_facts_contains_value(facts, path, &frame->left, &frame->matched);
                }
                else { frame->stage = 5u; status = frame_push(engine, state, RE_FRAME_TERM, expr->right, state->frame_count - 1u, 1u); }
            } else if (frame->stage == 3u) {
                /* Reached only from the AND/OR path above, after the second
                 * child completed; the completion handler already copied the
                 * child's matched into this frame. AND/OR exprs carry no
                 * compare operator (the parser zero-fills it, i.e.
                 * RE_COMPARE_TRUE, which re_value_compare answers 1 for
                 * unconditionally), so re-evaluating the frame as a
                 * comparison here forced every "A and B" to match whenever A
                 * was true (B ignored) and every "A or B" to match whenever A
                 * was false. Keep the child's result instead. */
                frame->stage = 99u;
            }
            else if (frame->stage == 5u) { frame->matched = re_value_compare(&frame->left, &frame->right, expr->compare); frame->stage = 99u; }
            else if (frame->stage == 7u) {
                frame->matched = re_value_compare(&frame->left, &frame->right, expr->compare);
                frame->stage = 99u;
            } else if (frame->stage == 8u) {
                const re_value_handle_t *array = NULL;
                re_string_t path;
                status = bound_fact_path(engine, state, ir->terms[expr->left].name,
                                         ir->terms[expr->left].name_size, &path);
                if (status == RE_STATUS_OK)
                    status = re_facts_get_structured_path(facts, path, &array);
                if (status == RE_STATUS_OK) {
                    if (array->kind != 2) status = RE_STATUS_INVALID_ARGUMENT;
                    else if (frame->position == array->count) { frame->matched = 1; frame->stage = 99u; }
                    else if (array->members[frame->position].child != NULL) status = RE_STATUS_INVALID_ARGUMENT;
                    else {
                        frame->matched = re_value_compare(&array->members[frame->position].scalar,
                                                          &frame->right, expr->compare);
                        ++frame->position;
                        if (!frame->matched) frame->stage = 99u;
                    }
                }
            }
            else if (frame->stage == 13u) {
                /* Plain-store fallback: the completed inner evaluation result
                 * (already copied into frame->matched) is the quantifier's
                 * result. */
                frame->stage = 99u;
            }
            else if (frame->stage == 12u) {
                /* One candidate's inner evaluation completed (result already
                 * copied into frame->matched). exists (and the A9 typed form,
                 * which shares its semantics) stops at the first match,
                 * forall at the first miss; otherwise rebind the prefix to
                 * the next candidate and re-evaluate. */
                int child_matched = frame->matched;
                if (frame->pushed_binding) { binding_pop(engine, state); frame->pushed_binding = 0; }
                if (((expr->kind == RE_EXPR_EXISTS || expr->kind == RE_EXPR_TYPED) && child_matched) ||
                    (expr->kind == RE_EXPR_FORALL && !child_matched)) {
                    frame->matched = child_matched;
                    frame->stage = 99u;
                } else {
                    const char *prefix;
                    size_t prefix_size;
                    const re_fact_entry_t *candidate = NULL;
                    /* A9: the typed form's prefix is the declared type, not
                     * the leftmost-fact-term derivation. */
                    if (expr->kind == RE_EXPR_TYPED) {
                        prefix = expr->typed_type;
                        prefix_size = expr->typed_type_size;
                        candidate = next_candidate(facts, prefix, prefix_size, &frame->position);
                    } else if (quantifier_prefix(engine, ir, expr->first, &prefix, &prefix_size)) {
                        candidate = next_candidate(facts, prefix, prefix_size, &frame->position);
                    }
                    if (candidate == NULL) {
                        /* D6: forall over an exhausted candidate set is
                         * vacuously true; exists and the typed form (exists
                         * semantics) are false. */
                        frame->matched = expr->kind == RE_EXPR_FORALL;
                        frame->stage = 99u;
                    } else {
                        status = binding_push(engine, state, prefix, prefix_size,
                                              candidate->name, candidate->name_size);
                        if (status == RE_STATUS_OK) {
                            frame->pushed_binding = 1;
                            status = frame_push(engine, state, RE_FRAME_EXPR, expr->first,
                                                state->frame_count - 1u, 0u);
                        }
                    }
                }
            }
            else if (frame->stage == 14u) {
                /* A9 test() truthiness (types.rs L106 to_bool): Bool as-is;
                 * String non-empty; Number != 0.0; Integer != 0; Null - and
                 * the local NONE/UNKNOWN sentinels - false. Function results
                 * are scalar re_value_t, so the Array/Object rows of to_bool
                 * are unreachable here. */
                const re_value_t *probe = &frame->left;
                frame->matched = probe->type == RE_VALUE_BOOL ? probe->as.boolean != 0 :
                    probe->type == RE_VALUE_INT64 ? probe->as.int64_value != 0 :
                    probe->type == RE_VALUE_DOUBLE ? probe->as.double_value != 0.0 :
                    probe->type == RE_VALUE_STRING ? probe->as.string.size != 0u : 0;
                frame->stage = 99u;
            }
            else if (frame->stage == 4u) { const re_ir_term_t *array = &ir->terms[expr->right]; if (frame->position == array->argument_count) frame->stage = 99u; else { frame->stage = 6u; status = frame_push(engine, state, RE_FRAME_TERM, array->argument_indices[frame->position], state->frame_count - 1u, 1u); } }
            else if (frame->stage == 6u) { if (re_value_equal_typed(&frame->left, &frame->right)) frame->matched = 1; ++frame->position; frame->stage = frame->matched ? 99u : 4u; }
        }
        if (status == RE_STATUS_NOT_FOUND && absorb_candidate_miss(engine, ir, state)) status = RE_STATUS_OK;
        if (status == RE_STATUS_NOT_FOUND && absorb_builtin_arg_miss(engine, ir, state)) status = RE_STATUS_OK;
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
    size_t i;
    for (i = 0u; i < state->scratch.count; ++i) re_free(&engine->allocator, state->scratch.items[i]);
    re_free(&engine->allocator, state->scratch.items);
    while (state->binding_count != 0u) binding_pop(engine, state);
    re_free(&engine->allocator, state->bindings);
    re_free(&engine->allocator, state->frames); re_free(&engine->allocator, state->rules);
}
static re_status_t match_rule_impl(const re_engine_t *engine, re_facts_t *facts, const re_ir_program_t *ir, size_t rule_index, int *matched, re_ir_read_set_t *reads) {
    re_ir_eval_state_t state; re_status_t status;
    if (engine == NULL || facts == NULL || ir == NULL || rule_index >= ir->rule_count || matched == NULL) return RE_STATUS_INVALID_ARGUMENT;
    memset(&state, 0, sizeof(state));
    state.record_reads = reads != NULL;
    state.gate_retracts = 1;
    state.step_limit = ir->expr_count > SIZE_MAX - ir->term_count ? SIZE_MAX : ir->expr_count + ir->term_count;
    state.step_limit = state.step_limit > (SIZE_MAX - 1u) / 1024u ? SIZE_MAX : state.step_limit * 1024u + 1u;
    status = push_rule(engine, &state, rule_index);
    if (status == RE_STATUS_OK) { status = evaluate_iterative(engine, facts, ir, RE_FRAME_EXPR, ir->rules[rule_index].condition, matched, NULL, &state); pop_rule(&state); }
    if (reads != NULL) {
        reads->count = state.read_count;
        if (state.read_count != 0u)
            memcpy(reads->paths, state.read_paths, state.read_count * sizeof(*reads->paths));
    }
    state_destroy(engine, &state); return status;
}
re_status_t re_ir_match_rule(const re_engine_t *engine, re_facts_t *facts, const re_ir_program_t *ir, size_t rule_index, int *matched) {
    return match_rule_impl(engine, facts, ir, rule_index, matched, NULL);
}
re_status_t re_ir_match_rule_readset(const re_engine_t *engine, re_facts_t *facts, const re_ir_program_t *ir, size_t rule_index, int *matched, re_ir_read_set_t *reads) {
    if (reads == NULL) return RE_STATUS_INVALID_ARGUMENT;
    reads->count = 0u;
    return match_rule_impl(engine, facts, ir, rule_index, matched, reads);
}
re_status_t re_ir_match_expr(const re_engine_t *engine, re_facts_t *facts, const re_ir_program_t *ir, size_t expr_index, int *matched) {
    re_ir_eval_state_t state; re_status_t status;
    if (engine == NULL || facts == NULL || ir == NULL || expr_index >= ir->expr_count || matched == NULL) return RE_STATUS_INVALID_ARGUMENT;
    memset(&state, 0, sizeof(state));
    state.gate_retracts = 1;
    state.step_limit = ir->expr_count > SIZE_MAX - ir->term_count ? SIZE_MAX : ir->expr_count + ir->term_count;
    state.step_limit = state.step_limit > (SIZE_MAX - 1u) / 1024u ? SIZE_MAX : state.step_limit * 1024u + 1u;
    status = evaluate_iterative(engine, facts, ir, RE_FRAME_EXPR, expr_index, matched, NULL, &state);
    state_destroy(engine, &state); return status;
}
re_status_t re_ir_resolve_term(re_engine_t *engine, re_facts_t *facts, const re_ir_program_t *ir, size_t term_index, re_value_t *value, re_eval_scratch_t *scratch) {
    re_ir_eval_state_t state; re_status_t status;
    if (engine == NULL || facts == NULL || ir == NULL || value == NULL || scratch == NULL || term_index >= ir->term_count) return RE_STATUS_INVALID_ARGUMENT;
    memset(&state, 0, sizeof(state));
    state.step_limit = ir->expr_count > SIZE_MAX - ir->term_count ? SIZE_MAX : ir->expr_count + ir->term_count;
    state.step_limit = state.step_limit > (SIZE_MAX - 1u) / 1024u ? SIZE_MAX : state.step_limit * 1024u + 1u;
    status = evaluate_iterative(engine, facts, ir, RE_FRAME_TERM, term_index, NULL, value, &state);
    {
        re_status_t move_status = scratch_move(engine, scratch, &state);
        if (status == RE_STATUS_OK) status = move_status;
    }
    state_destroy(engine, &state); return status;
}
