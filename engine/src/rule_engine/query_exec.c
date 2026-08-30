#include "re_internal.h"
#include "ir.h"
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * A7 GRL query blocks (upstream rust-rule-engine v1.21.4 grl_query.rs
 * L692-742, binding): the executor for the top-level `query "Name" { ... }`
 * form parsed into re_ir_program_t queries. Execution per query:
 *
 * - when-gate: the optional `when:` expression is a normal condition
 *   evaluated by the same machinery as rule conditions (re_ir_match_expr);
 *   false - or RE_STATUS_NOT_FOUND from a referenced fact that does not
 *   resolve - skips the query silently with RE_STATUS_OK.
 * - goal: split TEXTUALLY per upstream. When the goal contains both && and
 *   ||, one matching outer paren pair is stripped, the text splits on || and
 *   each part (outer parens stripped again) splits on &&; || alone is an OR
 *   of subgoals, && alone an AND, anything else a single subgoal. A subgoal
 *   containing != is evaluated directly against working memory (no rule
 *   derivation); any other subgoal runs through re_engine_query_bounded with
 *   the block's strategy, max-depth and max-solutions. enable-memoization
 *   maps to the shared proof graph (false sets disable_shared_proof_graph);
 *   enable-optimization is accepted and ignored (no local optimization
 *   passes - documented no-op). Compound evaluation short-circuits (D1-style;
 *   upstream evaluates every branch to merge solutions we do not expose).
 * - dispatch: a proved goal runs on-success, anything else (DISPROVED,
 *   UNKNOWN, LIMIT) runs on-failure. Upstream fires on-missing when the
 *   result carries missing facts; our backward machine does not track a
 *   missing_facts list, so on-missing is parsed but never fires - it folds
 *   into on-failure (documented divergence).
 * - actions: `Name = true|false|<number>|"string"` writes a flat scalar fact
 *   via re_facts_set; LogMessage/Request/Print print to stdout, Debug to
 *   stderr, with upstream's exact prefixes; an unknown call warns on stderr
 *   without failing (upstream execute_function_call).
 *
 * Queries run only through these two entry points, never inside
 * re_engine_run. Both report RE_STATUS_INVALID_ARGUMENT when no program is
 * installed; re_engine_run_query reports RE_STATUS_NOT_FOUND for an unknown
 * name; an installed program without query blocks makes re_engine_run_queries
 * an OK no-op.
 */

typedef struct query_exec_t {
    re_engine_t *engine;
    re_facts_t *facts;
    const re_ir_program_t *ir;
    const re_ir_query_t *query;
} query_exec_t;

static re_string_t query_trim(const char *data, size_t size) {
    re_string_t out;
    while (size != 0u && isspace((unsigned char)*data)) { ++data; --size; }
    while (size != 0u && isspace((unsigned char)data[size - 1u])) --size;
    out.data = data; out.size = size;
    return out;
}

static int query_contains(re_string_t text, const char *needle) {
    size_t n = strlen(needle);
    size_t i;
    if (n == 0u || n > text.size) return 0;
    for (i = 0u; i + n <= text.size; ++i)
        if (memcmp(text.data + i, needle, n) == 0) return 1;
    return 0;
}

/* Upstream strip_outer_parens: one outer pair is removed only when it wraps
 * the whole (trimmed) text. */
static re_string_t query_strip_parens(re_string_t text) {
    size_t i;
    size_t depth = 0u;
    if (text.size < 2u || text.data[0] != '(' || text.data[text.size - 1u] != ')') return text;
    for (i = 1u; i + 1u < text.size; ++i) {
        if (text.data[i] == '(') ++depth;
        else if (text.data[i] == ')') {
            if (depth == 0u) return text; /* closes before the end: not outer */
            --depth;
        }
    }
    if (depth != 0u) return text;
    return query_trim(text.data + 1u, text.size - 2u);
}

/* Iterates delimiter-separated parts of text without copying. *cursor is an
 * in/out offset; returns 1 and sets *part while parts remain, including a
 * final empty part after a trailing delimiter. */
static int query_next_part(re_string_t text, const char *delim, size_t *cursor, re_string_t *part) {
    size_t delim_size = strlen(delim);
    size_t start = *cursor;
    size_t i;
    if (start > text.size) return 0;
    for (i = start; i + delim_size <= text.size; ++i)
        if (memcmp(text.data + i, delim, delim_size) == 0) {
            *part = query_trim(text.data + start, i - start);
            *cursor = i + delim_size;
            return 1;
        }
    *part = query_trim(text.data + start, text.size - start);
    *cursor = text.size + 1u;
    return 1;
}

static int query_text_is(const char *data, size_t size, const char *word) {
    size_t n = strlen(word);
    size_t i;
    if (size != n) return 0;
    for (i = 0u; i < n; ++i)
        if (tolower((unsigned char)data[i]) != tolower((unsigned char)word[i])) return 0;
    return 1;
}

/* Pure-integer spelling (optional sign, digits only) -> INT64 with overflow
 * rejection; anything else returns 0 so the caller can try DOUBLE. */
static int query_int64(re_string_t text, int64_t *out) {
    size_t i = 0u;
    uint64_t magnitude = 0u;
    int negative = 0;
    if (i < text.size && (text.data[i] == '-' || text.data[i] == '+')) { negative = text.data[i] == '-'; ++i; }
    if (i == text.size) return 0;
    for (; i < text.size; ++i) {
        uint32_t digit;
        if (!isdigit((unsigned char)text.data[i])) return 0;
        digit = (uint32_t)(text.data[i] - '0');
        if (magnitude > ((uint64_t)INT64_MAX + 1u - digit) / 10u) return 0;
        magnitude = magnitude * 10u + digit;
    }
    if (!negative && magnitude > (uint64_t)INT64_MAX) return 0;
    if (negative && magnitude == (uint64_t)INT64_MAX + 1u) *out = INT64_MIN;
    else *out = negative ? -(int64_t)magnitude : (int64_t)magnitude;
    return 1;
}

/* Resolves one side of a != subgoal: a "quoted" string (inner text verbatim,
 * borrowed from the IR goal text), a case-insensitive true/false literal, a
 * number (integer spelling stays INT64, anything else with a full strtod
 * parse is DOUBLE - matching the engine's literal typing), else a fact path
 * read straight from working memory. */
static re_status_t query_side_value(re_facts_t *facts, re_string_t side, re_value_t *out) {
    side = query_trim(side.data, side.size);
    if (side.size >= 2u && side.data[0] == '"' && side.data[side.size - 1u] == '"') {
        out->type = RE_VALUE_STRING;
        out->as.string.data = side.data + 1u;
        out->as.string.size = side.size - 2u;
        return RE_STATUS_OK;
    }
    if (query_text_is(side.data, side.size, "true")) {
        out->type = RE_VALUE_BOOL; out->as.boolean = 1;
        return RE_STATUS_OK;
    }
    if (query_text_is(side.data, side.size, "false")) {
        out->type = RE_VALUE_BOOL; out->as.boolean = 0;
        return RE_STATUS_OK;
    }
    if (side.size != 0u && side.size < 256u) {
        if (query_int64(side, &out->as.int64_value)) { out->type = RE_VALUE_INT64; return RE_STATUS_OK; }
        {
            char buffer[256];
            char *end;
            double number;
            memcpy(buffer, side.data, side.size);
            buffer[side.size] = '\0';
            number = strtod(buffer, &end);
            if (end == buffer + side.size && end != buffer) {
                out->type = RE_VALUE_DOUBLE; out->as.double_value = number;
                return RE_STATUS_OK;
            }
        }
    }
    return re_facts_get_path(facts, side, out);
}

/* Direct != evaluation against working memory (no rule derivation), per
 * upstream: the expression splits at the first !=, both sides resolve as
 * literal-or-fact-path, and the comparison is the strictly-typed RE_COMPARE_NE
 * (D4: Integer(1) != Number(1.0) is true). A side that does not resolve
 * (missing fact) makes the subgoal unsatisfied, not an error. */
static re_status_t query_eval_not_equal(re_facts_t *facts, re_string_t subgoal, int *proved) {
    size_t i;
    re_string_t left;
    re_string_t right;
    re_value_t left_value;
    re_value_t right_value;
    re_status_t status;
    *proved = 0;
    for (i = 0u; i + 1u < subgoal.size; ++i)
        if (subgoal.data[i] == '!' && subgoal.data[i + 1u] == '=') break;
    if (i + 1u >= subgoal.size) return RE_STATUS_PARSE_ERROR;
    left = query_trim(subgoal.data, i);
    right = query_trim(subgoal.data + i + 2u, subgoal.size - i - 2u);
    if (left.size == 0u || right.size == 0u) return RE_STATUS_PARSE_ERROR;
    status = query_side_value(facts, left, &left_value);
    if (status == RE_STATUS_NOT_FOUND) return RE_STATUS_OK;
    if (status != RE_STATUS_OK) return status;
    status = query_side_value(facts, right, &right_value);
    if (status == RE_STATUS_NOT_FOUND) return RE_STATUS_OK;
    if (status != RE_STATUS_OK) return status;
    *proved = re_value_compare(&left_value, &right_value, RE_COMPARE_NE);
    return RE_STATUS_OK;
}

static re_status_t query_run_subgoal(const query_exec_t *exec, re_string_t subgoal, int *proved) {
    re_query_options_t options;
    re_query_t *result_query = NULL;
    re_status_t status;
    *proved = 0;
    subgoal = query_trim(subgoal.data, subgoal.size);
    if (subgoal.size == 0u) return RE_STATUS_PARSE_ERROR;
    if (query_contains(subgoal, "!=")) return query_eval_not_equal(exec->facts, subgoal, proved);
    memset(&options, 0, sizeof(options));
    options.struct_size = (uint32_t)sizeof(options);
    options.max_depth = exec->query->max_depth;
    options.max_solutions = exec->query->max_solutions;
    options.strategy = (uint32_t)exec->query->strategy;
    options.disable_shared_proof_graph = exec->query->enable_memoization ? 0u : 1u;
    status = re_engine_query_bounded(exec->engine, exec->facts, subgoal, &options, &result_query);
    /* A depth-exhausted search still returns a query object whose result is
     * RE_QUERY_LIMIT; that is a not-proved outcome, not an executor error. */
    if (status != RE_STATUS_OK && status != RE_STATUS_LIMIT) return status;
    if (result_query != NULL) {
        *proved = re_query_result(result_query) == RE_QUERY_PROVED;
        re_query_destroy(result_query);
    }
    return RE_STATUS_OK;
}

static re_status_t query_run_and(const query_exec_t *exec, re_string_t text, int *proved) {
    size_t cursor = 0u;
    re_string_t part;
    int sub = 0;
    *proved = 1;
    while (query_next_part(text, "&&", &cursor, &part)) {
        re_status_t status = query_run_subgoal(exec, part, &sub);
        if (status != RE_STATUS_OK) return status;
        if (!sub) { *proved = 0; return RE_STATUS_OK; }
    }
    return RE_STATUS_OK;
}

static re_status_t query_run_or(const query_exec_t *exec, re_string_t text, int *proved) {
    size_t cursor = 0u;
    re_string_t part;
    int sub = 0;
    *proved = 0;
    while (query_next_part(text, "||", &cursor, &part)) {
        re_status_t status = query_run_subgoal(exec, part, &sub);
        if (status != RE_STATUS_OK) return status;
        if (sub) { *proved = 1; return RE_STATUS_OK; }
    }
    return RE_STATUS_OK;
}

/* Both operators present (upstream execute_complex_goal): strip one outer
 * paren pair, split on ||, and each part is either an && conjunction or a
 * single subgoal - AND binds tighter than OR. */
static re_status_t query_run_complex(const query_exec_t *exec, re_string_t text, int *proved) {
    size_t cursor = 0u;
    re_string_t part;
    *proved = 0;
    text = query_strip_parens(query_trim(text.data, text.size));
    while (query_next_part(text, "||", &cursor, &part)) {
        re_string_t cleaned = query_strip_parens(part);
        re_status_t status;
        int sub = 0;
        if (query_contains(cleaned, "&&")) status = query_run_and(exec, cleaned, &sub);
        else status = query_run_subgoal(exec, cleaned, &sub);
        if (status != RE_STATUS_OK) return status;
        if (sub) { *proved = 1; return RE_STATUS_OK; }
    }
    return RE_STATUS_OK;
}

static re_status_t query_execute_goal(const query_exec_t *exec, int *proved) {
    const re_ir_term_t *goal_term = &exec->ir->terms[exec->query->goal];
    re_string_t goal = query_trim(goal_term->value.as.string.data, goal_term->value.as.string.size);
    int has_and = query_contains(goal, "&&");
    int has_or = query_contains(goal, "||");
    if (has_and && has_or) return query_run_complex(exec, goal, proved);
    if (has_or) return query_run_or(exec, goal, proved);
    if (has_and) return query_run_and(exec, goal, proved);
    return query_run_subgoal(exec, goal, proved);
}

/* Upstream trim_matches('"') then trim_matches('\''): every leading and
 * trailing quote char of each kind is stripped. */
static re_string_t query_strip_quotes(re_string_t text) {
    while (text.size != 0u && text.data[0] == '"') { ++text.data; --text.size; }
    while (text.size != 0u && text.data[text.size - 1u] == '"') --text.size;
    while (text.size != 0u && text.data[0] == '\'') { ++text.data; --text.size; }
    while (text.size != 0u && text.data[text.size - 1u] == '\'') --text.size;
    return text;
}

static int query_name_is(const re_ir_term_t *term, const char *name) {
    size_t n = strlen(name);
    return term->name_size == n && memcmp(term->name, name, n) == 0;
}

static re_status_t query_run_actions(const query_exec_t *exec, size_t first, size_t count) {
    size_t i;
    for (i = 0u; i < count; ++i) {
        const re_ir_query_action_t *action = &exec->ir->query_actions[first + i];
        const re_ir_term_t *name = &exec->ir->terms[action->name];
        if (!action->is_call) {
            re_string_t target = {name->name, name->name_size};
            re_status_t status = re_facts_set(exec->facts, target, &exec->ir->terms[action->value].value);
            if (status != RE_STATUS_OK) return status;
            continue;
        }
        {
            const re_ir_term_t *args = &exec->ir->terms[action->args];
            re_string_t raw = {args->value.as.string.data, args->value.as.string.size};
            re_string_t message = query_strip_quotes(query_trim(raw.data, raw.size));
            if (query_name_is(name, "LogMessage"))
                printf("[LOG] %.*s\n", (int)message.size, message.data);
            else if (query_name_is(name, "Request"))
                printf("[REQUEST] %.*s\n", (int)message.size, message.data);
            else if (query_name_is(name, "Print"))
                printf("%.*s\n", (int)message.size, message.data);
            else if (query_name_is(name, "Debug"))
                fprintf(stderr, "[DEBUG] %.*s\n", (int)message.size, message.data);
            else
                fprintf(stderr, "[WARNING] Unknown function call in query action: %.*s(%.*s)\n",
                        (int)name->name_size, name->name, (int)raw.size, raw.data);
        }
    }
    return RE_STATUS_OK;
}

static re_status_t query_run_one(re_engine_t *engine, re_facts_t *facts,
                                 const re_ir_program_t *ir, const re_ir_query_t *query) {
    query_exec_t exec;
    re_status_t status;
    int proved = 0;
    exec.engine = engine; exec.facts = facts; exec.ir = ir; exec.query = query;
    if (query->when != SIZE_MAX) {
        int gate = 0;
        status = re_ir_match_expr(engine, facts, ir, query->when, &gate);
        /* A gate referencing a missing fact is not satisfied (the rule-match
         * contract); the query is skipped silently. */
        if (status == RE_STATUS_NOT_FOUND) return RE_STATUS_OK;
        if (status != RE_STATUS_OK) return status;
        if (!gate) return RE_STATUS_OK;
    }
    status = query_execute_goal(&exec, &proved);
    if (status != RE_STATUS_OK) return status;
    return query_run_actions(&exec,
                             query->first_action[proved ? RE_QUERY_BLOCK_SUCCESS : RE_QUERY_BLOCK_FAILURE],
                             query->action_count[proved ? RE_QUERY_BLOCK_SUCCESS : RE_QUERY_BLOCK_FAILURE]);
}

re_status_t re_engine_run_query(re_engine_t *engine, re_facts_t *facts, re_string_t name) {
    const re_ir_program_t *ir;
    size_t i;
    if (engine == NULL || facts == NULL || name.data == NULL) return RE_STATUS_INVALID_ARGUMENT;
    if (engine->program == NULL || engine->program->ir == NULL) return RE_STATUS_INVALID_ARGUMENT;
    ir = engine->program->ir;
    for (i = 0u; i < ir->query_count; ++i) {
        const re_ir_term_t *term = &ir->terms[ir->queries[i].name];
        if (term->name_size == name.size &&
            (name.size == 0u || memcmp(term->name, name.data, name.size) == 0))
            return query_run_one(engine, facts, ir, &ir->queries[i]);
    }
    return RE_STATUS_NOT_FOUND;
}

re_status_t re_engine_run_queries(re_engine_t *engine, re_facts_t *facts) {
    const re_ir_program_t *ir;
    size_t i;
    if (engine == NULL || facts == NULL) return RE_STATUS_INVALID_ARGUMENT;
    if (engine->program == NULL || engine->program->ir == NULL) return RE_STATUS_INVALID_ARGUMENT;
    ir = engine->program->ir;
    for (i = 0u; i < ir->query_count; ++i) {
        re_status_t status = query_run_one(engine, facts, ir, &ir->queries[i]);
        if (status != RE_STATUS_OK) return status;
    }
    return RE_STATUS_OK;
}
