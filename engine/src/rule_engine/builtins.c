#include "re_internal.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Engine built-in functions for `when` conditions and action RHS, matching
 * upstream rust-rule-engine f80a541: the A3 condition family from
 * condition_evaluator.rs and the A4 action/RHS utility table from engine.rs
 * execute_function_call (L1410).
 *
 * A3 condition family:
 *
 *   len/length/size(x)      String -> byte length; Array -> element count;
 *                           any other type makes the condition false. The
 *                           result is RE_VALUE_INT64 where upstream returns
 *                           Number (f64): under the D4 strictly-typed equality
 *                           an INT64 result keeps len(x) == 4 true while
 *                           len(x) == 4.0 is false (documented divergence).
 *   isEmpty/is_empty(x)     String/Array empty -> true; Null -> true; any
 *                           other type -> false.
 *   contains(x, y)          x String contains substring y, or x Array
 *                           contains y by typed equality; else false.
 *   exists(p)               fact-path presence: flat key, scalar nested
 *                           member, or structured (array/object) root/member;
 *                           p is a quoted string or a bare fact path.
 *   notExists/not_exists(p) negated presence.
 *
 * A4 action/RHS utility family (upstream execute_function_call). All are
 * semantically pure except random and the stdout side effect of
 * log/print/println, so they evaluate in conditions as well. The purity here
 * is semantic only: re_condition_is_pure (engine.c) classifies EVERY
 * function-call condition as impure and the run loop disables parallel
 * matching when any condition is impure - do not "optimize" that
 * classification for these built-ins, or random()/log() in a condition
 * becomes a data race:
 *
 *   log/print/println(...)  join the display forms of the arguments with " "
 *                           and return the message string; also writes it
 *                           (plus a newline) to stdout. The engine has no
 *                           log/output callback (re_callbacks_t carries only
 *                           the action hook), so plain stdio is the
 *                           documented local logging convention (upstream
 *                           logs through its info! logger).
 *   now/timestamp()         unix seconds as a decimal string.
 *   random([max])           deterministic xorshift64 over the per-engine
 *                           random_state, seeded with RE_BUILTIN_RANDOM_SEED
 *                           at engine creation (no public setter by design):
 *                           every engine produces the same sequence, which
 *                           keeps tests stable. 0-99 without arguments,
 *                           0..max-1 with a positive integer/double max
 *                           (doubles truncate); a missing argument means 100,
 *                           extra arguments are ignored, and max < 1, a
 *                           non-numeric max, or a double at/above 2^64 is
 *                           RE_STATUS_INVALID_ARGUMENT. (Upstream hashes the
 *                           current time - effectively nondeterministic -
 *                           and panics on max == 0; bug replication is not
 *                           the goal. The result is a typed INT64 where
 *                           upstream returns a decimal string.)
 *   format/sprintf(fmt, ..) bounded substitution: %d, %s, %f and %% consume
 *                           the following arguments in order (%d prints an
 *                           integer, truncating a double in the int64 range;
 *                           %f prints a double with C %f; anything else under
 *                           %d/%f, and everything under %s, prints the
 *                           display form; exhausted values leave the
 *                           directive verbatim; unknown directives pass
 *                           through unchanged). Afterwards upstream's
 *                           {0}/{1}/... placeholder replacement applies to
 *                           the remaining text (upstream has only the brace
 *                           form; the %-directives are the documented local
 *                           extension pinned by the task). Zero arguments
 *                           yield the empty string.
 *   length/size/count(x)    aliases of the A3 len semantics (shared code
 *                           path), NOT upstream's stringly action-table
 *                           length handler (documented divergence: a wrong
 *                           type is false here, not "1").
 *   sum/add, max, min       numeric folds; non-numeric arguments are skipped
 *                           (upstream's fold ignores them). Task 12 INT64
 *                           preservation: all-integer folds return INT64
 *                           (integer-overflow promotes the sum to DOUBLE),
 *                           any DOUBLE argument makes the result DOUBLE. With
 *                           no numeric arguments sum is Integer 0, max is
 *                           -inf and min is +inf (DOUBLE; upstream's fold
 *                           seeds translated to typed values). The upstream
 *                           maximum aliases max (engine.rs:1427).
 *   avg/average(...)        DOUBLE mean over the numeric arguments; none
 *                           numeric -> 0.0.
 *   round/floor/ceil/abs(x) DOUBLE math on a double argument; an INT64
 *                           argument passes round/floor/ceil through
 *                           unchanged (upstream's i.to_string()) and keeps
 *                           abs typed (abs(INT64_MIN) -> RE_STATUS_LIMIT,
 *                           matching the arithmetic overflow idiom). A
 *                           missing or non-numeric first argument is
 *                           RE_STATUS_INVALID_ARGUMENT (upstream's Err);
 *                           extra arguments are ignored. The upstream
 *                           ceiling aliases ceil (engine.rs:1432).
 *   contains/includes(x, y) same as the A3 contains (shared code path).
 *   startswith/endswith(x, y) typed STRING/STRING predicates (bool); wrong
 *                           arity or non-string arguments are false, matching
 *                           the condition operators they alias (upstream
 *                           coerces both sides through to_string and errors
 *                           below 2 arguments; documented divergence). The
 *                           upstream begins_with aliases startswith
 *                           (engine.rs:1435).
 *   lowercase/uppercase/trim(x) string transforms over the display form of
 *                           the first argument (upstream's to_string
 *                           leniency, so trim(5) is "5"); ASCII case mapping,
 *                           isspace trimming; zero arguments is
 *                           RE_STATUS_INVALID_ARGUMENT (upstream's Err). The
 *                           upstream strip aliases trim (engine.rs:1439).
 *   split(text, delim)      upstream returns format!("{:?}", parts) - a
 *                           Rust-debug string, not an array - so the scalar
 *                           function ABI needs no extension: the result is
 *                           the same ["a", "b"] debug string (escaping ", \,
 *                           \n, \r, \t). An empty delimiter is
 *                           RE_STATUS_INVALID_ARGUMENT (upstream char-splits;
 *                           documented deviation).
 *   join(delim, parts...)   delimiter FIRST, display forms of the rest
 *                           joined (upstream argument order); fewer than 2
 *                           arguments is RE_STATUS_INVALID_ARGUMENT.
 *
 * D1 plugin-parity family (upstream f80a541 src/plugins/; upstream attaches
 * them via engine.load_plugin - here they are name-dispatched built-ins, so
 * a registered host function still overrides them: ir_eval.c consults the
 * registry first). All are semantically PURE (deterministic from their
 * arguments; no clock, RNG, or stdout) and stay under the blanket-impure
 * condition classification of re_condition_is_pure like every function call.
 * Upstream's CamelCase fact-mutating ACTION forms (ToUpperCase, ArrayPush,
 * ObjectKeys, ...) are NOT replicated: these expression functions plus plain
 * assignment cover them (the D4 conformance row documents the mapping).
 * Array/object arguments arrive as bare fact paths (an RE_VALUE_NONE
 * placeholder plus its captured path, resolved through
 * re_facts_get_structured_path); GRL array literals are not function
 * arguments (an ARRAY term is NOT_SUPPORTED in that position).
 *
 *   concat(a, b, ...)       string_utils.rs:148 - display forms joined with
 *                           no separator; fewer than 2 arguments is
 *                           RE_STATUS_INVALID_ARGUMENT (upstream's Err).
 *                           Upstream's value_to_string errors on Null/Array/
 *                           Object; here they stringify through the A4
 *                           display form ("null"/"[Array]"/"[Object]") -
 *                           documented divergence (consistency with
 *                           log/format beats novelty).
 *   repeat(text, n)         string_utils.rs:163 - n must be an Integer
 *                           (anything else is INVALID_ARGUMENT); n < 0 or
 *                           n > 1000 is RE_STATUS_LIMIT (upstream's
 *                           "Repeat count too large" error; a negative i64
 *                           wraps to a huge usize upstream and hits the same
 *                           cap).
 *   substring(text, start[, len]) string_utils.rs:190 - BYTE-based over the
 *                           UTF-8 bytes (byte-vs-char documented: upstream
 *                           slices bytes as well and PANICS on a
 *                           non-codepoint boundary; the byte slice is
 *                           returned as-is here). start < 0 wraps huge
 *                           upstream (`*i as usize`) so it yields "" like an
 *                           out-of-range start; len clamps to the text end
 *                           (upstream min(start + len, len)); a negative len
 *                           (a usize-wrap/panic corner upstream) is
 *                           INVALID_ARGUMENT instead of replicated.
 *   replace(text, from, to) string_utils.rs:129 StringReplace body
 *                           (text.replace) as a function - ALL
 *                           non-overlapping occurrences, left to right; an
 *                           empty `from` inserts `to` at every byte boundary
 *                           (upstream-exact). Wrong arity is
 *                           INVALID_ARGUMENT.
 *   sqrt(x)                 math_utils.rs:170 - DOUBLE result; x is a number
 *                           or a fully-parsing numeric string (upstream
 *                           value_to_number); a negative x is
 *                           RE_STATUS_INVALID_ARGUMENT (upstream's Err).
 *   first(x) / last(x)      collection_utils.rs:286/:308 - array fact: the
 *                           first/last element (a nested structured element
 *                           surfaces as its "[Array]"/"[Object]" display
 *                           placeholder; scalar strings borrow fact storage
 *                           like trim); a string: the first/last UTF-8
 *                           codepoint (upstream chars()); an EMPTY array or
 *                           string, an object, or any other scalar yields
 *                           Null (upstream's unwrap_or(Value::Null) and
 *                           `_ => Value::Null`) - NOT an error.
 *   reverse(x)              collection_utils.rs:330 - array fact: the
 *                           reversed elements as a debug string (the scalar
 *                           function ABI cannot return an array; the split
 *                           idiom: ["a", "b"] with strings quoted/escaped,
 *                           other scalars in display form); a string:
 *                           codepoint-reversed (upstream chars().rev());
 *                           anything else: the argument unchanged (upstream
 *                           `_ => args[0].clone()`; a structured object
 *                           surfaces as "[Object]").
 *   slice(arr, start[, end]) collection_utils.rs:372 - array only (anything
 *                           else is INVALID_ARGUMENT, upstream's Err);
 *                           start/end go through value_to_number then Rust's
 *                           SATURATING f64 -> usize cast (NaN/negative -> 0),
 *                           both clamped to the length; start > end yields
 *                           the empty array. The result is the debug string
 *                           form (split idiom).
 *   keys(obj) / values(obj) collection_utils.rs:404/:421 - object fact: the
 *                           member keys/values as a debug string in the local
 *                           store's INSERTION order (upstream iterates a
 *                           HashMap whose order is deliberately unspecified;
 *                           the local order is pinned by test); a non-object
 *                           yields "[]" (upstream's Ok(vec![])).
 *   isEmail(x)              validation.rs:179 - hand-rolled equivalent of
 *                           the upstream regex
 *                           ^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$
 *                           (no regex engine is linked): exactly one '@', a
 *                           1+ char local part in the first class, and a
 *                           domain in the second class whose LAST dot is
 *                           preceded by 1+ class chars and followed by 2+
 *                           ASCII letters (the last-dot split is
 *                           match-equivalent to the backtracking regex).
 *   isPhone(x)              validation.rs:191 exact: 10-15 ASCII digits
 *                           after stripping every non-digit.
 *   isUrl(x)                validation.rs:203 exact: starts_with "http://",
 *                           "https://", or "ftp://".
 *   isNumeric(x)            validation.rs:215 - whole-string Rust f64
 *                           FromStr grammar (optional sign; case-insensitive
 *                           inf/infinity/nan; a mantissa with an optional dot
 *                           and an optional [eE] exponent; no whitespace, hex,
 *                           or underscore forms).
 *   inRange(v, min, max)    validation.rs:246 - inclusive bounds over
 *                           value_to_number arguments (numbers or fully-
 *                           parsing numeric strings; anything else is
 *                           INVALID_ARGUMENT, upstream's Err).
 *   The validation five are predicate built-ins (bare whole-condition use
 *   means fn(...) == true); their argument stringifies through the A4
 *   display form (upstream value_to_string leniency).
 *
 * Semantics notes (all families):
 * - Display forms follow upstream types.rs Display for Value: strings raw,
 *   integers decimal, booleans true/false, null "null", structured values
 *   [Array]/[Object] (an RE_VALUE_NONE argument with a captured fact path is
 *   re-queried for its structured kind). Doubles print via %g (6 significant
 *   digits) - a documented approximation of Rust's shortest-round-trip
 *   Display.
 * - Wrong arity and wrong argument types yield false for the A3 predicates
 *   (upstream's Ok(false)), never an error status, so a bad call makes the
 *   rule not match instead of failing the run; the A4 family follows the
 *   per-function upstream behavior documented above (error for the math and
 *   string functions with unusable arguments, false for the predicates).
 * - A bare fact-path argument that fails to resolve (absent fact) makes the
 *   built-in yield re_builtin_arg_miss_result() - false everywhere except
 *   the negated presence probes; ir_eval.c absorbs that NOT_FOUND into the
 *   built-in's result. Upstream instead degrades an unresolvable argument
 *   to its text as a String; the task pins the saner
 *   resolution-failure-is-false rule (documented divergence).
 * - Arrays exist only as structured handles, so a fact-path argument whose
 *   scalar value is RE_VALUE_NONE is re-queried through
 *   re_facts_get_structured_path via the argument's captured fact path.
 * - Resolution order: the user function registry is consulted first
 *   (ir_eval.c FUNCTION term path); built-ins are only the fallback, so a
 *   registered function of the same name overrides the built-in.
 * - Result strings produced by the string-returning built-ins are owned by
 *   the evaluation scratch (re_eval_scratch_t) handed in by ir_eval.c, which
 *   the caller releases; fact writes deep-copy them.
 */

static int name_is(re_string_t name, const char *literal) {
    size_t size = strlen(literal);
    return name.size == size && memcmp(name.data, literal, size) == 0;
}
static int is_negated_presence(re_string_t name) {
    return name_is(name, "notExists") || name_is(name, "not_exists");
}
int re_builtin_is(const char *name, size_t size) {
    re_string_t key = {name, size};
    return name_is(key, "len") || name_is(key, "length") || name_is(key, "size") ||
           name_is(key, "count") || name_is(key, "isEmpty") || name_is(key, "is_empty") ||
           name_is(key, "contains") || name_is(key, "includes") ||
           name_is(key, "startswith") || name_is(key, "begins_with") || name_is(key, "endswith") ||
           name_is(key, "exists") || is_negated_presence(key) ||
           name_is(key, "log") || name_is(key, "print") || name_is(key, "println") ||
           name_is(key, "now") || name_is(key, "timestamp") || name_is(key, "random") ||
           name_is(key, "format") || name_is(key, "sprintf") ||
           name_is(key, "sum") || name_is(key, "add") ||
           name_is(key, "max") || name_is(key, "maximum") || name_is(key, "min") ||
           name_is(key, "avg") || name_is(key, "average") ||
           name_is(key, "round") || name_is(key, "floor") || name_is(key, "ceil") ||
           name_is(key, "ceiling") ||
           name_is(key, "abs") || name_is(key, "lowercase") || name_is(key, "uppercase") ||
           name_is(key, "trim") || name_is(key, "strip") || name_is(key, "split") || name_is(key, "join") ||
           name_is(key, "concat") || name_is(key, "repeat") || name_is(key, "substring") ||
           name_is(key, "replace") || name_is(key, "sqrt") ||
           name_is(key, "first") || name_is(key, "last") || name_is(key, "reverse") ||
           name_is(key, "slice") || name_is(key, "keys") || name_is(key, "values") ||
           name_is(key, "isEmail") || name_is(key, "isPhone") || name_is(key, "isUrl") ||
           name_is(key, "isNumeric") || name_is(key, "inRange");
}
/* Predicate built-ins return booleans; the parser lets them appear bare as a
 * whole condition, meaning fn(...) == true. */
int re_builtin_is_predicate(const char *name, size_t size) {
    re_string_t key = {name, size};
    return name_is(key, "isEmpty") || name_is(key, "is_empty") || name_is(key, "contains") ||
           name_is(key, "includes") || name_is(key, "startswith") || name_is(key, "begins_with") ||
           name_is(key, "endswith") ||
           name_is(key, "exists") || is_negated_presence(key) ||
           name_is(key, "isEmail") || name_is(key, "isPhone") || name_is(key, "isUrl") ||
           name_is(key, "isNumeric") || name_is(key, "inRange");
}
/* A8 bare `name(args)` then-statement actions (upstream grl.rs action
 * builtins), case-sensitive upstream spellings. retract/log/
 * ActivateAgendaGroup are executed internally; the workflow/scheduler trio
 * dispatches to a registered function of the same name (D5). */
int re_builtin_action_is(const char *name, size_t size) {
    re_string_t key = {name, size};
    return name_is(key, "retract") || name_is(key, "log") ||
           name_is(key, "ActivateAgendaGroup") || name_is(key, "ScheduleRule") ||
           name_is(key, "CompleteWorkflow") || name_is(key, "SetWorkflowData");
}
int re_builtin_arg_miss_result(const char *name, size_t size) {
    return is_negated_presence((re_string_t){name, size});
}
static re_status_t bool_result(re_value_t *out, int value) {
    out->type = RE_VALUE_BOOL;
    out->as.boolean = value != 0;
    return RE_STATUS_OK;
}
static re_status_t false_result(re_value_t *out) { return bool_result(out, 0); }
static re_string_t arg_path(const re_string_t *arg_fact_paths, size_t index) {
    if (arg_fact_paths == NULL) {
        re_string_t empty = {NULL, 0u};
        return empty;
    }
    return arg_fact_paths[index];
}
/* Element count of the array held at a fact path. The path comes from a bare
 * fact-path argument whose scalar value is RE_VALUE_NONE (structured-backed
 * fact). Returns 0 (not an array) for objects, scalar facts, and lookup
 * failures; the caller then yields false, matching upstream's
 * String/Array-only rule. */
static int array_element_count(const re_facts_t *facts, re_string_t path, size_t *out) {
    const re_value_handle_t *value = NULL;
    if (path.data == NULL || path.size == 0u) return 0;
    if (re_facts_get_structured_path(facts, path, &value) != RE_STATUS_OK) return 0;
    if (value->kind != 2) return 0;
    *out = value->count;
    return 1;
}

/* ---- A4: growable string buffer and display forms -------------------- */

typedef struct re_strbuf_t {
    const re_allocator_impl_t *allocator;
    char *data;      /* NUL-terminated while non-NULL */
    size_t size;
    size_t capacity; /* allocated bytes, always > size when data != NULL */
    re_status_t status; /* sticky failure; appends become no-ops */
} re_strbuf_t;

static void sb_init(re_strbuf_t *sb, const re_allocator_impl_t *allocator) {
    sb->allocator = allocator;
    sb->data = NULL;
    sb->size = 0u;
    sb->capacity = 0u;
    sb->status = RE_STATUS_OK;
}
static void sb_append(re_strbuf_t *sb, const char *data, size_t size) {
    size_t need;
    size_t capacity;
    char *grown;
    if (sb->status != RE_STATUS_OK || size == 0u) return;
    if (sb->size > SIZE_MAX - size - 1u) { sb->status = RE_STATUS_LIMIT; return; }
    need = sb->size + size + 1u;
    if (need > sb->capacity) {
        capacity = sb->capacity == 0u ? 32u : sb->capacity;
        while (capacity < need) {
            if (capacity > SIZE_MAX / 2u) { capacity = need; break; }
            capacity *= 2u;
        }
        if (capacity < need) { sb->status = RE_STATUS_LIMIT; return; }
        grown = re_realloc(sb->allocator, sb->data, capacity);
        if (grown == NULL) { sb->status = RE_STATUS_OUT_OF_MEMORY; return; }
        sb->data = grown;
        sb->capacity = capacity;
    }
    memcpy(sb->data + sb->size, data, size);
    sb->size += size;
    sb->data[sb->size] = '\0';
}
static void sb_append_char(re_strbuf_t *sb, char c) { sb_append(sb, &c, 1u); }
static void sb_append_cstr(re_strbuf_t *sb, const char *text) { sb_append(sb, text, strlen(text)); }
/* Appends an snprintf result. The snprintf return value is the WOULD-BE
 * length, which exceeds the buffer when the output was truncated (a %f of
 * 1e300 is 308 bytes in a 64-byte buffer), so the appended length is clamped
 * to what actually fits - snprintf always NUL-terminates within buf_size.
 * Callers pass sizeof(buf) so the bound is explicit at every site. */
static void sb_append_snprintf(re_strbuf_t *sb, const char *buf, size_t buf_size, int n) {
    size_t len;
    if (n <= 0) return;
    len = (size_t)n;
    if (len > buf_size - 1u) len = buf_size - 1u;
    sb_append(sb, buf, len);
}
/* Hands the buffer to the evaluation scratch and yields it as the string
 * result; an empty buffer yields a borrowed "" with no allocation. On
 * failure the buffer is released and the status returned. */
static re_status_t sb_finish(re_strbuf_t *sb, const re_engine_t *engine,
                             re_eval_scratch_t *scratch, re_value_t *out) {
    re_status_t status;
    if (sb->status != RE_STATUS_OK) {
        status = sb->status;
        re_free(sb->allocator, sb->data);
        return status;
    }
    if (sb->size == 0u) {
        re_free(sb->allocator, sb->data);
        out->type = RE_VALUE_STRING;
        out->as.string.data = "";
        out->as.string.size = 0u;
        return RE_STATUS_OK;
    }
    status = re_eval_scratch_own(engine, scratch, sb->data);
    if (status != RE_STATUS_OK) {
        re_free(sb->allocator, sb->data);
        return status;
    }
    out->type = RE_VALUE_STRING;
    out->as.string.data = sb->data;
    out->as.string.size = sb->size;
    return RE_STATUS_OK;
}
/* Appends the display form of a value (upstream types.rs Display for Value).
 * An RE_VALUE_NONE argument (structured-backed fact placeholder) prints as
 * [Array]/[Object] when its captured fact path resolves to a structured
 * value, else "null". */
static void sb_append_value(re_strbuf_t *sb, const re_facts_t *facts,
                            const re_value_t *value, re_string_t path) {
    char buf[40];
    int n;
    const re_value_handle_t *structured;
    switch (value->type) {
    case RE_VALUE_BOOL:
        sb_append_cstr(sb, value->as.boolean ? "true" : "false");
        break;
    case RE_VALUE_INT64:
        /* %lld needs at most 20 chars; the clamp keeps the bound explicit. */
        n = snprintf(buf, sizeof(buf), "%lld", (long long)value->as.int64_value);
        sb_append_snprintf(sb, buf, sizeof(buf), n);
        break;
    case RE_VALUE_DOUBLE:
        /* %g approximates Rust's shortest-round-trip Display (documented);
         * 40 bytes always suffice for %g, and the clamp keeps that bound
         * explicit. */
        n = snprintf(buf, sizeof(buf), "%g", value->as.double_value);
        sb_append_snprintf(sb, buf, sizeof(buf), n);
        break;
    case RE_VALUE_STRING:
        sb_append(sb, value->as.string.data, value->as.string.size);
        break;
    case RE_VALUE_NONE:
        structured = NULL;
        if (path.data != NULL && path.size != 0u &&
            re_facts_get_structured_path(facts, path, &structured) == RE_STATUS_OK &&
            structured != NULL)
            sb_append_cstr(sb, structured->kind == 2 ? "[Array]" : "[Object]");
        else
            sb_append_cstr(sb, "null");
        break;
    case RE_VALUE_NULL:
        sb_append_cstr(sb, "null");
        break;
    default:
        sb_append_cstr(sb, "unknown");
        break;
    }
}
/* The display form of a value as a string: borrowed when the value already
 * is a string, scratch-owned otherwise. */
static re_status_t value_to_string(const re_engine_t *engine, const re_facts_t *facts,
                                   const re_value_t *value, re_string_t path,
                                   re_eval_scratch_t *scratch, re_string_t *out) {
    re_strbuf_t sb;
    re_status_t status;
    if (value->type == RE_VALUE_STRING) {
        *out = value->as.string;
        return RE_STATUS_OK;
    }
    sb_init(&sb, &engine->allocator);
    sb_append_value(&sb, facts, value, path);
    if (sb.status != RE_STATUS_OK) {
        status = sb.status;
        re_free(&engine->allocator, sb.data);
        return status;
    }
    status = re_eval_scratch_own(engine, scratch, sb.data);
    if (status != RE_STATUS_OK) {
        re_free(&engine->allocator, sb.data);
        return status;
    }
    out->data = sb.data;
    out->size = sb.size;
    return RE_STATUS_OK;
}

/* ---- A3 condition family --------------------------------------------- */

static re_status_t call_len(const re_facts_t *facts, const re_value_t *args,
                            const re_string_t *arg_fact_paths, size_t argc, re_value_t *out) {
    size_t count;
    if (argc != 1u) return false_result(out);
    if (args[0].type == RE_VALUE_STRING) {
        out->type = RE_VALUE_INT64;
        out->as.int64_value = (int64_t)args[0].as.string.size;
        return RE_STATUS_OK;
    }
    if (args[0].type == RE_VALUE_NONE &&
        array_element_count(facts, arg_path(arg_fact_paths, 0u), &count)) {
        out->type = RE_VALUE_INT64;
        out->as.int64_value = (int64_t)count;
        return RE_STATUS_OK;
    }
    return false_result(out);
}
static re_status_t call_is_empty(const re_facts_t *facts, const re_value_t *args,
                                 const re_string_t *arg_fact_paths, size_t argc, re_value_t *out) {
    size_t count;
    if (argc != 1u) return false_result(out);
    if (args[0].type == RE_VALUE_STRING) return bool_result(out, args[0].as.string.size == 0u);
    if (args[0].type == RE_VALUE_NULL) return bool_result(out, 1);
    if (args[0].type == RE_VALUE_NONE &&
        array_element_count(facts, arg_path(arg_fact_paths, 0u), &count))
        return bool_result(out, count == 0u);
    return false_result(out);
}
static re_status_t call_contains(const re_facts_t *facts, const re_value_t *args,
                                 const re_string_t *arg_fact_paths, size_t argc, re_value_t *out) {
    int matched;
    re_status_t status;
    if (argc != 2u) return false_result(out);
    if (args[0].type == RE_VALUE_STRING && args[1].type == RE_VALUE_STRING)
        return bool_result(out, re_value_compare(&args[0], &args[1], RE_COMPARE_CONTAINS));
    if (args[0].type == RE_VALUE_NONE && arg_path(arg_fact_paths, 0u).data != NULL) {
        status = re_facts_contains_value(facts, arg_path(arg_fact_paths, 0u), &args[1], &matched);
        /* Not an array fact (or no such fact): false, not a run error. */
        if (status == RE_STATUS_INVALID_ARGUMENT) return false_result(out);
        if (status != RE_STATUS_OK) return status;
        return bool_result(out, matched);
    }
    return false_result(out);
}
static re_status_t call_exists(const re_facts_t *facts, const re_value_t *args,
                               const re_string_t *arg_fact_paths, size_t argc,
                               int negate, re_value_t *out) {
    re_string_t path = {NULL, 0u};
    re_value_t probe;
    const re_value_handle_t *structured = NULL;
    int present;
    if (argc != 1u) return false_result(out);
    /* A bare fact-path argument names the path to probe (its resolved value
     * is irrelevant); a quoted string argument carries the path text. */
    if (arg_path(arg_fact_paths, 0u).data != NULL) path = arg_path(arg_fact_paths, 0u);
    else if (args[0].type == RE_VALUE_STRING) path = args[0].as.string;
    else return false_result(out);
    present = re_facts_get_path(facts, path, &probe) == RE_STATUS_OK ||
              re_facts_get_structured_path(facts, path, &structured) == RE_STATUS_OK;
    return bool_result(out, negate ? !present : present);
}

/* ---- A4 action/RHS utility family ------------------------------------ */

static re_status_t call_log(re_engine_t *engine, re_facts_t *facts, const re_value_t *args,
                            const re_string_t *arg_fact_paths, size_t argc,
                            re_eval_scratch_t *scratch, re_value_t *out) {
    re_strbuf_t sb;
    re_string_t piece;
    re_status_t status;
    size_t i;
    sb_init(&sb, &engine->allocator);
    for (i = 0u; i < argc; ++i) {
        if (i != 0u) sb_append_char(&sb, ' ');
        status = value_to_string(engine, facts, &args[i], arg_path(arg_fact_paths, i), scratch, &piece);
        if (status != RE_STATUS_OK) {
            re_free(&engine->allocator, sb.data);
            return status;
        }
        sb_append(&sb, piece.data, piece.size);
    }
    status = sb_finish(&sb, engine, scratch, out);
    if (status != RE_STATUS_OK) return status;
    /* No log callback exists in the public API; stdout is the documented
     * local logging convention. */
    fwrite(out->as.string.data, 1u, out->as.string.size, stdout);
    fputc('\n', stdout);
    return RE_STATUS_OK;
}
static re_status_t call_now(re_engine_t *engine, re_eval_scratch_t *scratch, re_value_t *out) {
    char buf[24];
    char *copy;
    re_status_t status;
    int n = snprintf(buf, sizeof(buf), "%lld", (long long)time(NULL));
    if (n <= 0 || (size_t)n >= sizeof(buf)) return RE_STATUS_ERROR;
    copy = re_alloc(&engine->allocator, (size_t)n + 1u);
    if (copy == NULL) return RE_STATUS_OUT_OF_MEMORY;
    memcpy(copy, buf, (size_t)n + 1u);
    status = re_eval_scratch_own(engine, scratch, copy);
    if (status != RE_STATUS_OK) {
        re_free(&engine->allocator, copy);
        return status;
    }
    out->type = RE_VALUE_STRING;
    out->as.string.data = copy;
    out->as.string.size = (size_t)n;
    return RE_STATUS_OK;
}
/* xorshift64 (Marsaglia): the per-engine state advances on every call, so a
 * run sees a deterministic sequence and two engines produce the same one. */
static uint64_t rng_next(uint64_t *state) {
    uint64_t x = *state;
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    *state = x;
    return x;
}
static re_status_t call_random(re_engine_t *engine, const re_value_t *args, size_t argc,
                               re_value_t *out) {
    uint64_t limit = 100u;
    if (argc != 0u) {
        if (args[0].type == RE_VALUE_INT64) {
            if (args[0].as.int64_value < 1) return RE_STATUS_INVALID_ARGUMENT;
            limit = (uint64_t)args[0].as.int64_value;
        } else if (args[0].type == RE_VALUE_DOUBLE) {
            if (!(args[0].as.double_value >= 1.0) ||
                args[0].as.double_value >= 18446744073709551616.0)
                return RE_STATUS_INVALID_ARGUMENT;
            limit = (uint64_t)args[0].as.double_value;
        } else {
            return RE_STATUS_INVALID_ARGUMENT;
        }
    }
    out->type = RE_VALUE_INT64;
    out->as.int64_value = (int64_t)(rng_next(&engine->random_state) % limit);
    return RE_STATUS_OK;
}
static re_status_t call_format(re_engine_t *engine, re_facts_t *facts, const re_value_t *args,
                               const re_string_t *arg_fact_paths, size_t argc,
                               re_eval_scratch_t *scratch, re_value_t *out) {
    re_strbuf_t sb;
    re_string_t fmt;
    re_string_t piece;
    re_status_t status;
    size_t i;
    size_t cursor;
    char buf[64];
    int n;
    if (argc == 0u) {
        out->type = RE_VALUE_STRING;
        out->as.string.data = "";
        out->as.string.size = 0u;
        return RE_STATUS_OK;
    }
    status = value_to_string(engine, facts, &args[0], arg_path(arg_fact_paths, 0u), scratch, &fmt);
    if (status != RE_STATUS_OK) return status;
    sb_init(&sb, &engine->allocator);
    cursor = 1u; /* next argument consumed by a % directive */
    i = 0u;
    while (i < fmt.size && sb.status == RE_STATUS_OK) {
        char c = fmt.data[i];
        if (c == '%' && i + 1u < fmt.size) {
            char d = fmt.data[i + 1u];
            if (d == '%') {
                sb_append_char(&sb, '%');
                i += 2u;
                continue;
            }
            if (d == 'd' || d == 's' || d == 'f') {
                if (cursor < argc) {
                    const re_value_t *v = &args[cursor++];
                    if (d == 'd' && v->type == RE_VALUE_INT64) {
                        n = snprintf(buf, sizeof(buf), "%lld", (long long)v->as.int64_value);
                        sb_append_snprintf(&sb, buf, sizeof(buf), n);
                    } else if (d == 'd' && v->type == RE_VALUE_DOUBLE &&
                               v->as.double_value >= -9223372036854775808.0 &&
                               v->as.double_value < 9223372036854775808.0) {
                        n = snprintf(buf, sizeof(buf), "%lld", (long long)v->as.double_value);
                        sb_append_snprintf(&sb, buf, sizeof(buf), n);
                    } else if (d == 'f' &&
                               (v->type == RE_VALUE_DOUBLE || v->type == RE_VALUE_INT64)) {
                        double dv = v->type == RE_VALUE_DOUBLE ? v->as.double_value
                                                               : (double)v->as.int64_value;
                        /* %f of a huge magnitude legitimately truncates
                         * (1e300 would be 308 bytes); append only what the
                         * buffer holds - the would-be length is NOT the
                         * content length. */
                        n = snprintf(buf, sizeof(buf), "%f", dv);
                        sb_append_snprintf(&sb, buf, sizeof(buf), n);
                    } else {
                        status = value_to_string(engine, facts, v, arg_path(arg_fact_paths, cursor - 1u),
                                                 scratch, &piece);
                        if (status != RE_STATUS_OK) {
                            re_free(&engine->allocator, sb.data);
                            return status;
                        }
                        sb_append(&sb, piece.data, piece.size);
                    }
                } else {
                    /* Values exhausted: the directive passes through verbatim. */
                    sb_append_char(&sb, '%');
                    sb_append_char(&sb, d);
                }
                i += 2u;
                continue;
            }
            /* Unknown directive: copy the '%'; the next byte is handled on
             * the following pass. */
            sb_append_char(&sb, '%');
            ++i;
            continue;
        }
        if (c == '{') {
            /* Upstream's {0}/{1}/... placeholder: values[index] is
             * args[1 + index]; an out-of-range index stays verbatim. */
            size_t j = i + 1u;
            size_t index = 0u;
            while (j < fmt.size && fmt.data[j] >= '0' && fmt.data[j] <= '9') {
                if (index > (SIZE_MAX - 9u) / 10u) { j = fmt.size; break; }
                index = index * 10u + (size_t)(fmt.data[j] - '0');
                ++j;
            }
            if (j > i + 1u && j < fmt.size && fmt.data[j] == '}' && index < argc - 1u) {
                status = value_to_string(engine, facts, &args[1u + index],
                                         arg_path(arg_fact_paths, 1u + index), scratch, &piece);
                if (status != RE_STATUS_OK) {
                    re_free(&engine->allocator, sb.data);
                    return status;
                }
                sb_append(&sb, piece.data, piece.size);
                i = j + 1u;
                continue;
            }
        }
        sb_append_char(&sb, c);
        ++i;
    }
    return sb_finish(&sb, engine, scratch, out);
}

/* Numeric fold state: the double accumulator always runs (it is the result
 * once any double participates or the integer sum overflows); the int64
 * accumulator runs while the fold stays all-integer and overflow-free. */
typedef struct re_num_fold_t {
    int64_t integer;
    double real;
    size_t count;
    int all_integer;
    int overflowed;
} re_num_fold_t;
static void num_fold_init(re_num_fold_t *fold) {
    memset(fold, 0, sizeof(*fold));
    fold->all_integer = 1;
}
static void num_fold_add(re_num_fold_t *fold, const re_value_t *value) {
    if (value->type == RE_VALUE_INT64) {
        int64_t v = value->as.int64_value;
        fold->real += (double)v;
        ++fold->count;
        if (!fold->overflowed) {
            if ((v > 0 && fold->integer > INT64_MAX - v) ||
                (v < 0 && fold->integer < INT64_MIN - v))
                fold->overflowed = 1;
            else
                fold->integer += v;
        }
    } else if (value->type == RE_VALUE_DOUBLE) {
        fold->real += value->as.double_value;
        ++fold->count;
        fold->all_integer = 0;
    }
    /* Non-numeric arguments are skipped (upstream's fold ignores them). */
}
static re_status_t call_sum(const re_value_t *args, size_t argc, re_value_t *out) {
    re_num_fold_t fold;
    size_t i;
    num_fold_init(&fold);
    for (i = 0u; i < argc; ++i) num_fold_add(&fold, &args[i]);
    if (fold.all_integer && !fold.overflowed) {
        out->type = RE_VALUE_INT64;
        out->as.int64_value = fold.integer;
    } else {
        out->type = RE_VALUE_DOUBLE;
        out->as.double_value = fold.real;
    }
    return RE_STATUS_OK;
}
static re_status_t call_max_min(const re_value_t *args, size_t argc, int is_max, re_value_t *out) {
    size_t i;
    size_t count = 0u;
    int all_integer = 1;
    int64_t best_int = 0;
    double best_real = 0.0;
    for (i = 0u; i < argc; ++i) {
        const re_value_t *v = &args[i];
        double d;
        if (v->type != RE_VALUE_INT64 && v->type != RE_VALUE_DOUBLE) continue;
        d = v->type == RE_VALUE_DOUBLE ? v->as.double_value : (double)v->as.int64_value;
        if (v->type == RE_VALUE_DOUBLE) all_integer = 0;
        if (count != 0u) {
            if (all_integer && v->type == RE_VALUE_INT64 &&
                (is_max ? v->as.int64_value > best_int : v->as.int64_value < best_int))
                best_int = v->as.int64_value;
            if (is_max ? d > best_real : d < best_real) best_real = d;
        } else {
            best_real = d;
            if (v->type == RE_VALUE_INT64) best_int = v->as.int64_value;
        }
        ++count;
    }
    if (count == 0u) {
        /* Upstream's fold seeds (-inf/+inf) translated to typed values. */
        out->type = RE_VALUE_DOUBLE;
        out->as.double_value = is_max ? -HUGE_VAL : HUGE_VAL;
        return RE_STATUS_OK;
    }
    if (all_integer) {
        out->type = RE_VALUE_INT64;
        out->as.int64_value = best_int;
    } else {
        out->type = RE_VALUE_DOUBLE;
        out->as.double_value = best_real;
    }
    return RE_STATUS_OK;
}
static re_status_t call_avg(const re_value_t *args, size_t argc, re_value_t *out) {
    re_num_fold_t fold;
    size_t i;
    num_fold_init(&fold);
    for (i = 0u; i < argc; ++i) num_fold_add(&fold, &args[i]);
    out->type = RE_VALUE_DOUBLE;
    out->as.double_value = fold.count == 0u ? 0.0 : fold.real / (double)fold.count;
    return RE_STATUS_OK;
}
static re_status_t call_math1(const re_value_t *args, size_t argc, int kind, re_value_t *out) {
    const re_value_t *v;
    if (argc == 0u) return RE_STATUS_INVALID_ARGUMENT;
    v = &args[0];
    if (v->type == RE_VALUE_INT64) {
        if (kind == 3) {
            if (v->as.int64_value == INT64_MIN) return RE_STATUS_LIMIT;
            out->type = RE_VALUE_INT64;
            out->as.int64_value = v->as.int64_value < 0 ? -v->as.int64_value : v->as.int64_value;
        } else {
            /* Integer input passes round/floor/ceil through unchanged
             * (upstream's i.to_string()). */
            *out = *v;
        }
        return RE_STATUS_OK;
    }
    if (v->type == RE_VALUE_DOUBLE) {
        double d = v->as.double_value;
        out->type = RE_VALUE_DOUBLE;
        out->as.double_value = kind == 0 ? round(d) : kind == 1 ? floor(d) :
                               kind == 2 ? ceil(d) : fabs(d);
        return RE_STATUS_OK;
    }
    return RE_STATUS_INVALID_ARGUMENT;
}
static re_status_t call_starts_ends_with(const re_value_t *args, size_t argc, int starts,
                                         re_value_t *out) {
    if (argc != 2u || args[0].type != RE_VALUE_STRING || args[1].type != RE_VALUE_STRING)
        return false_result(out);
    return bool_result(out, re_value_compare(&args[0], &args[1],
        starts ? RE_COMPARE_STARTS_WITH : RE_COMPARE_ENDS_WITH));
}
static re_status_t call_case_map(re_engine_t *engine, re_facts_t *facts, const re_value_t *args,
                                 const re_string_t *arg_fact_paths, size_t argc,
                                 int upper, re_eval_scratch_t *scratch, re_value_t *out) {
    re_string_t s;
    re_strbuf_t sb;
    re_status_t status;
    size_t i;
    if (argc == 0u) return RE_STATUS_INVALID_ARGUMENT;
    status = value_to_string(engine, facts, &args[0], arg_path(arg_fact_paths, 0u), scratch, &s);
    if (status != RE_STATUS_OK) return status;
    sb_init(&sb, &engine->allocator);
    for (i = 0u; i < s.size; ++i)
        sb_append_char(&sb, (char)(upper ? toupper((unsigned char)s.data[i])
                                         : tolower((unsigned char)s.data[i])));
    return sb_finish(&sb, engine, scratch, out);
}
static re_status_t call_trim(re_engine_t *engine, re_facts_t *facts, const re_value_t *args,
                             const re_string_t *arg_fact_paths, size_t argc,
                             re_eval_scratch_t *scratch, re_value_t *out) {
    re_string_t s;
    re_status_t status;
    size_t start = 0u;
    size_t end;
    if (argc == 0u) return RE_STATUS_INVALID_ARGUMENT;
    status = value_to_string(engine, facts, &args[0], arg_path(arg_fact_paths, 0u), scratch, &s);
    if (status != RE_STATUS_OK) return status;
    end = s.size;
    while (start < end && isspace((unsigned char)s.data[start])) ++start;
    while (end > start && isspace((unsigned char)s.data[end - 1u])) --end;
    /* The result borrows the (borrowed or scratch-owned) argument text. */
    out->type = RE_VALUE_STRING;
    out->as.string.data = s.data + start;
    out->as.string.size = end - start;
    return RE_STATUS_OK;
}
static re_status_t call_split(re_engine_t *engine, re_facts_t *facts, const re_value_t *args,
                              const re_string_t *arg_fact_paths, size_t argc,
                              re_eval_scratch_t *scratch, re_value_t *out) {
    re_string_t text_str;
    re_string_t delim;
    re_strbuf_t sb;
    re_status_t status;
    size_t pos = 0u;
    int first = 1;
    if (argc < 2u) return RE_STATUS_INVALID_ARGUMENT;
    status = value_to_string(engine, facts, &args[0], arg_path(arg_fact_paths, 0u), scratch, &text_str);
    if (status != RE_STATUS_OK) return status;
    status = value_to_string(engine, facts, &args[1], arg_path(arg_fact_paths, 1u), scratch, &delim);
    if (status != RE_STATUS_OK) return status;
    /* An empty delimiter char-splits upstream (str::split("")); locally that
     * corner is rejected instead (documented deviation). */
    if (delim.size == 0u) return RE_STATUS_INVALID_ARGUMENT;
    sb_init(&sb, &engine->allocator);
    sb_append_char(&sb, '[');
    for (;;) {
        size_t hit = text_str.size;
        size_t i;
        if (sb.status != RE_STATUS_OK) break;
        if (!first) sb_append_cstr(&sb, ", ");
        first = 0;
        for (i = pos; i + delim.size <= text_str.size; ++i) {
            if (memcmp(text_str.data + i, delim.data, delim.size) == 0) {
                hit = i;
                break;
            }
        }
        sb_append_char(&sb, '"');
        for (i = pos; i < hit; ++i) {
            char c = text_str.data[i];
            if (c == '"' || c == '\\') {
                sb_append_char(&sb, '\\');
                sb_append_char(&sb, c);
            } else if (c == '\n') {
                sb_append_cstr(&sb, "\\n");
            } else if (c == '\r') {
                sb_append_cstr(&sb, "\\r");
            } else if (c == '\t') {
                sb_append_cstr(&sb, "\\t");
            } else {
                sb_append_char(&sb, c);
            }
        }
        sb_append_char(&sb, '"');
        if (hit == text_str.size) break;
        pos = hit + delim.size;
    }
    sb_append_char(&sb, ']');
    return sb_finish(&sb, engine, scratch, out);
}
static re_status_t call_join(re_engine_t *engine, re_facts_t *facts, const re_value_t *args,
                             const re_string_t *arg_fact_paths, size_t argc,
                             re_eval_scratch_t *scratch, re_value_t *out) {
    re_string_t delim;
    re_string_t piece;
    re_strbuf_t sb;
    re_status_t status;
    size_t i;
    if (argc < 2u) return RE_STATUS_INVALID_ARGUMENT;
    status = value_to_string(engine, facts, &args[0], arg_path(arg_fact_paths, 0u), scratch, &delim);
    if (status != RE_STATUS_OK) return status;
    sb_init(&sb, &engine->allocator);
    for (i = 1u; i < argc; ++i) {
        if (i != 1u) sb_append(&sb, delim.data, delim.size);
        status = value_to_string(engine, facts, &args[i], arg_path(arg_fact_paths, i), scratch, &piece);
        if (status != RE_STATUS_OK) {
            re_free(&engine->allocator, sb.data);
            return status;
        }
        sb_append(&sb, piece.data, piece.size);
    }
    return sb_finish(&sb, engine, scratch, out);
}

/* ---- D1 plugin-parity family ------------------------------------------ */

/* Quoted string with the Rust-debug escaping of call_split (", \, \n, \r,
 * \t); used by the array-result debug strings below. */
static void sb_append_debug_string(re_strbuf_t *sb, const char *data, size_t size) {
    size_t i;
    sb_append_char(sb, '"');
    for (i = 0u; i < size; ++i) {
        char c = data[i];
        if (c == '"' || c == '\\') {
            sb_append_char(sb, '\\');
            sb_append_char(sb, c);
        } else if (c == '\n') {
            sb_append_cstr(sb, "\\n");
        } else if (c == '\r') {
            sb_append_cstr(sb, "\\r");
        } else if (c == '\t') {
            sb_append_cstr(sb, "\\t");
        } else {
            sb_append_char(sb, c);
        }
    }
    sb_append_char(sb, '"');
}
/* Element rendering for the array-result debug strings (the split idiom):
 * strings quoted/escaped, other scalars in display form, nested structured
 * members as [Array]/[Object]. */
static void sb_append_debug_value(re_strbuf_t *sb, const re_facts_t *facts,
                                  const re_value_t *value, const re_value_handle_t *child) {
    re_string_t no_path = {NULL, 0u};
    if (child != NULL) {
        sb_append_cstr(sb, child->kind == 2 ? "[Array]" : "[Object]");
        return;
    }
    if (value->type == RE_VALUE_STRING) {
        sb_append_debug_string(sb, value->as.string.data, value->as.string.size);
        return;
    }
    sb_append_value(sb, facts, value, no_path);
}
/* Resolves a bare fact-path argument (an RE_VALUE_NONE placeholder with a
 * captured path) to its structured handle; returns 1 on success. */
static int structured_arg(const re_facts_t *facts, const re_value_t *arg, re_string_t path,
                          const re_value_handle_t **out) {
    if (arg->type != RE_VALUE_NONE || path.data == NULL || path.size == 0u) return 0;
    return re_facts_get_structured_path(facts, path, out) == RE_STATUS_OK;
}
/* UTF-8 codepoint byte length from the lead byte; continuation and invalid
 * lead bytes count as 1 so malformed input still terminates. The string arms
 * of first/last/reverse are codepoint-based like upstream's chars(); the
 * continuation bytes themselves are never validated (documented). */
static size_t utf8_cp_len(unsigned char lead) {
    if (lead < 0x80u) return 1u;
    if (lead < 0xC0u) return 1u;
    if (lead < 0xE0u) return 2u;
    if (lead < 0xF0u) return 3u;
    if (lead < 0xF8u) return 4u;
    return 1u;
}
static int ci_word_match(const char *data, size_t size, const char *word) {
    size_t i;
    if (strlen(word) != size) return 0;
    for (i = 0u; i < size; ++i)
        if (tolower((unsigned char)data[i]) != word[i]) return 0;
    return 1;
}
/* Whole-string Rust f64 FromStr grammar (upstream validation.rs:215
 * text.parse::<f64>() and the plugins' value_to_number string arm): an
 * optional sign, then case-insensitive inf/infinity/nan or a decimal
 * mantissa (Digit+ | Digit+ "." Digit* | "." Digit+) with an optional
 * [eE][sign]Digit+ exponent; no whitespace, hex, or underscore forms.
 * RE_STATUS_OK when the WHOLE text matches (*out receives the value when
 * non-NULL; overflow to +-inf is a successful parse, matching Rust),
 * RE_STATUS_INVALID_ARGUMENT when it does not. */
static re_status_t rust_f64_parse(const re_allocator_impl_t *allocator, re_string_t text,
                                  double *out) {
    size_t i = 0u;
    size_t mantissa_digits = 0u;
    int negative = 0;
    int valid;
    if (text.size == 0u) return RE_STATUS_INVALID_ARGUMENT;
    if (text.data[0] == '+' || text.data[0] == '-') {
        negative = text.data[0] == '-';
        i = 1u;
    }
    if (ci_word_match(text.data + i, text.size - i, "nan")) {
        if (out != NULL) *out = NAN; /* the sign of a NaN is unobservable here */
        return RE_STATUS_OK;
    }
    if (ci_word_match(text.data + i, text.size - i, "inf") ||
        ci_word_match(text.data + i, text.size - i, "infinity")) {
        if (out != NULL) *out = negative ? -HUGE_VAL : HUGE_VAL;
        return RE_STATUS_OK;
    }
    while (i < text.size && isdigit((unsigned char)text.data[i])) { ++i; ++mantissa_digits; }
    if (i < text.size && text.data[i] == '.') {
        ++i;
        while (i < text.size && isdigit((unsigned char)text.data[i])) { ++i; ++mantissa_digits; }
    }
    valid = mantissa_digits != 0u;
    if (valid && i < text.size && (text.data[i] == 'e' || text.data[i] == 'E')) {
        size_t exponent_digits = 0u;
        ++i;
        if (i < text.size && (text.data[i] == '+' || text.data[i] == '-')) ++i;
        while (i < text.size && isdigit((unsigned char)text.data[i])) { ++i; ++exponent_digits; }
        valid = exponent_digits != 0u;
    }
    if (!valid || i != text.size) return RE_STATUS_INVALID_ARGUMENT;
    if (out == NULL) return RE_STATUS_OK;
    /* strtod needs a NUL-terminated copy. */
    {
        char stack_buf[64];
        char *buf = stack_buf;
        double parsed;
        if (text.size >= sizeof(stack_buf)) {
            buf = re_alloc(allocator, text.size + 1u);
            if (buf == NULL) return RE_STATUS_OUT_OF_MEMORY;
        }
        memcpy(buf, text.data, text.size);
        buf[text.size] = '\0';
        parsed = strtod(buf, NULL);
        if (buf != stack_buf) re_free(allocator, buf);
        *out = parsed;
    }
    return RE_STATUS_OK;
}
/* The plugins' value_to_number arm set (f80a541 math_utils.rs /
 * validation.rs helpers): Number/Integer directly, a String through the
 * Rust f64 grammar, anything else is upstream's Err. */
static re_status_t plugin_number(const re_allocator_impl_t *allocator, const re_value_t *value,
                                 double *out) {
    if (value->type == RE_VALUE_DOUBLE) {
        *out = value->as.double_value;
        return RE_STATUS_OK;
    }
    if (value->type == RE_VALUE_INT64) {
        *out = (double)value->as.int64_value;
        return RE_STATUS_OK;
    }
    if (value->type == RE_VALUE_STRING)
        return rust_f64_parse(allocator, value->as.string, out);
    return RE_STATUS_INVALID_ARGUMENT;
}

static re_status_t call_concat(re_engine_t *engine, re_facts_t *facts, const re_value_t *args,
                               const re_string_t *arg_fact_paths, size_t argc,
                               re_eval_scratch_t *scratch, re_value_t *out) {
    re_strbuf_t sb;
    re_string_t piece;
    re_status_t status;
    size_t i;
    if (argc < 2u) return RE_STATUS_INVALID_ARGUMENT;
    sb_init(&sb, &engine->allocator);
    for (i = 0u; i < argc; ++i) {
        status = value_to_string(engine, facts, &args[i], arg_path(arg_fact_paths, i), scratch, &piece);
        if (status != RE_STATUS_OK) {
            re_free(&engine->allocator, sb.data);
            return status;
        }
        sb_append(&sb, piece.data, piece.size);
    }
    return sb_finish(&sb, engine, scratch, out);
}
static re_status_t call_repeat(re_engine_t *engine, re_facts_t *facts, const re_value_t *args,
                               const re_string_t *arg_fact_paths, size_t argc,
                               re_eval_scratch_t *scratch, re_value_t *out) {
    re_string_t text_str;
    re_strbuf_t sb;
    re_status_t status;
    int64_t count;
    int64_t i;
    if (argc != 2u) return RE_STATUS_INVALID_ARGUMENT;
    status = value_to_string(engine, facts, &args[0], arg_path(arg_fact_paths, 0u), scratch, &text_str);
    if (status != RE_STATUS_OK) return status;
    if (args[1].type != RE_VALUE_INT64) return RE_STATUS_INVALID_ARGUMENT;
    count = args[1].as.int64_value;
    if (count < 0 || count > 1000) return RE_STATUS_LIMIT;
    sb_init(&sb, &engine->allocator);
    for (i = 0; i < count; ++i) sb_append(&sb, text_str.data, text_str.size);
    return sb_finish(&sb, engine, scratch, out);
}
static re_status_t call_substring(re_engine_t *engine, re_facts_t *facts, const re_value_t *args,
                                  const re_string_t *arg_fact_paths, size_t argc,
                                  re_eval_scratch_t *scratch, re_value_t *out) {
    re_string_t text_str;
    re_status_t status;
    size_t start;
    size_t end;
    if (argc < 2u || argc > 3u) return RE_STATUS_INVALID_ARGUMENT;
    status = value_to_string(engine, facts, &args[0], arg_path(arg_fact_paths, 0u), scratch, &text_str);
    if (status != RE_STATUS_OK) return status;
    if (args[1].type != RE_VALUE_INT64) return RE_STATUS_INVALID_ARGUMENT;
    /* Upstream start = *i as usize: a negative start wraps huge, so it lands
     * on the same start >= text.len() early-out as an out-of-range start. */
    if (args[1].as.int64_value < 0 || (uint64_t)args[1].as.int64_value >= text_str.size) {
        out->type = RE_VALUE_STRING;
        out->as.string.data = "";
        out->as.string.size = 0u;
        return RE_STATUS_OK;
    }
    start = (size_t)args[1].as.int64_value;
    if (argc == 3u) {
        if (args[2].type != RE_VALUE_INT64) return RE_STATUS_INVALID_ARGUMENT;
        /* Upstream end = min(start + (*i as usize), len): a negative length
         * wraps into a usize-overflow/panic corner; rejected instead of
         * replicated (documented). */
        if (args[2].as.int64_value < 0) return RE_STATUS_INVALID_ARGUMENT;
        end = (uint64_t)args[2].as.int64_value > text_str.size - start
                  ? text_str.size
                  : start + (size_t)args[2].as.int64_value;
    } else {
        end = text_str.size;
    }
    /* The result borrows the (borrowed or scratch-owned) argument text. */
    out->type = RE_VALUE_STRING;
    out->as.string.data = text_str.data + start;
    out->as.string.size = end - start;
    return RE_STATUS_OK;
}
static re_status_t call_replace(re_engine_t *engine, re_facts_t *facts, const re_value_t *args,
                                const re_string_t *arg_fact_paths, size_t argc,
                                re_eval_scratch_t *scratch, re_value_t *out) {
    re_string_t text_str;
    re_string_t from;
    re_string_t to;
    re_strbuf_t sb;
    re_status_t status;
    size_t pos = 0u;
    size_t i;
    if (argc != 3u) return RE_STATUS_INVALID_ARGUMENT;
    status = value_to_string(engine, facts, &args[0], arg_path(arg_fact_paths, 0u), scratch, &text_str);
    if (status != RE_STATUS_OK) return status;
    status = value_to_string(engine, facts, &args[1], arg_path(arg_fact_paths, 1u), scratch, &from);
    if (status != RE_STATUS_OK) return status;
    status = value_to_string(engine, facts, &args[2], arg_path(arg_fact_paths, 2u), scratch, &to);
    if (status != RE_STATUS_OK) return status;
    sb_init(&sb, &engine->allocator);
    if (from.size == 0u) {
        /* Rust str::replace with an empty pattern matches at every character
         * boundary: "ab".replace("", "-") is "-a-b-", and a multi-byte
         * codepoint is never split (upstream-exact). */
        i = 0u;
        while (i < text_str.size) {
            size_t len = utf8_cp_len((unsigned char)text_str.data[i]);
            if (len > text_str.size - i) len = text_str.size - i;
            sb_append(&sb, to.data, to.size);
            sb_append(&sb, text_str.data + i, len);
            i += len;
        }
        sb_append(&sb, to.data, to.size);
    } else {
        for (i = 0u; i + from.size <= text_str.size;) {
            if (memcmp(text_str.data + i, from.data, from.size) == 0) {
                sb_append(&sb, text_str.data + pos, i - pos);
                sb_append(&sb, to.data, to.size);
                i += from.size;
                pos = i;
            } else {
                ++i;
            }
        }
        sb_append(&sb, text_str.data + pos, text_str.size - pos);
    }
    return sb_finish(&sb, engine, scratch, out);
}
static re_status_t call_sqrt(re_engine_t *engine, const re_value_t *args, size_t argc,
                             re_value_t *out) {
    double v;
    re_status_t status;
    if (argc != 1u) return RE_STATUS_INVALID_ARGUMENT;
    status = plugin_number(&engine->allocator, &args[0], &v);
    if (status != RE_STATUS_OK) return status;
    /* math_utils.rs:170: a negative input is upstream's EvaluationError. */
    if (v < 0.0) return RE_STATUS_INVALID_ARGUMENT;
    out->type = RE_VALUE_DOUBLE;
    out->as.double_value = sqrt(v);
    return RE_STATUS_OK;
}
static re_status_t call_first_last(const re_facts_t *facts, const re_value_t *args,
                                   const re_string_t *arg_fact_paths, size_t argc,
                                   int last, re_value_t *out) {
    const re_value_handle_t *structured = NULL;
    if (argc != 1u) return RE_STATUS_INVALID_ARGUMENT;
    if (structured_arg(facts, &args[0], arg_path(arg_fact_paths, 0u), &structured)) {
        const re_value_member_t *member;
        /* Objects (and unresolvable paths below) fall to the Null rule. */
        if (structured->kind != 2 || structured->count == 0u) {
            out->type = RE_VALUE_NULL;
            return RE_STATUS_OK;
        }
        member = &structured->members[last ? structured->count - 1u : 0u];
        if (member->child != NULL) {
            /* A nested structured element has no scalar surface: the display
             * placeholder stands in (documented). */
            const char *placeholder = member->child->kind == 2 ? "[Array]" : "[Object]";
            out->type = RE_VALUE_STRING;
            out->as.string.data = placeholder;
            out->as.string.size = strlen(placeholder);
            return RE_STATUS_OK;
        }
        *out = member->scalar; /* borrows fact-owned strings, like call_trim */
        return RE_STATUS_OK;
    }
    if (args[0].type == RE_VALUE_STRING && args[0].as.string.size != 0u) {
        re_string_t s = args[0].as.string;
        if (!last) {
            size_t len = utf8_cp_len((unsigned char)s.data[0]);
            if (len > s.size) len = s.size;
            out->type = RE_VALUE_STRING;
            out->as.string.data = s.data;
            out->as.string.size = len;
        } else {
            size_t i = 0u;
            size_t start = 0u;
            size_t len = 1u;
            while (i < s.size) {
                len = utf8_cp_len((unsigned char)s.data[i]);
                if (len > s.size - i) len = s.size - i;
                start = i;
                i += len;
            }
            out->type = RE_VALUE_STRING;
            out->as.string.data = s.data + start;
            out->as.string.size = len;
        }
        return RE_STATUS_OK;
    }
    /* collection_utils.rs:286/:308 `_ => Value::Null` (and the empty cases). */
    out->type = RE_VALUE_NULL;
    return RE_STATUS_OK;
}
static re_status_t call_reverse(re_engine_t *engine, re_facts_t *facts, const re_value_t *args,
                                const re_string_t *arg_fact_paths, size_t argc,
                                re_eval_scratch_t *scratch, re_value_t *out) {
    const re_value_handle_t *structured = NULL;
    re_strbuf_t sb;
    size_t i;
    if (argc != 1u) return RE_STATUS_INVALID_ARGUMENT;
    if (structured_arg(facts, &args[0], arg_path(arg_fact_paths, 0u), &structured)) {
        if (structured->kind != 2) {
            /* Upstream's identity arm would return the object itself; the
             * display placeholder stands in (documented). */
            out->type = RE_VALUE_STRING;
            out->as.string.data = "[Object]";
            out->as.string.size = 8u;
            return RE_STATUS_OK;
        }
        sb_init(&sb, &engine->allocator);
        sb_append_char(&sb, '[');
        for (i = structured->count; i != 0u; --i) {
            const re_value_member_t *member = &structured->members[i - 1u];
            if (i != structured->count) sb_append_cstr(&sb, ", ");
            sb_append_debug_value(&sb, facts, &member->scalar, member->child);
        }
        sb_append_char(&sb, ']');
        return sb_finish(&sb, engine, scratch, out);
    }
    if (args[0].type == RE_VALUE_STRING) {
        /* chars().rev(): reverse whole codepoint byte sequences (a lead byte
         * is found by walking back over 10xxxxxx continuation bytes, bounded
         * at 4, so malformed input still terminates). */
        re_string_t s = args[0].as.string;
        sb_init(&sb, &engine->allocator);
        i = s.size;
        while (i != 0u) {
            size_t start = i - 1u;
            while (start != 0u && ((unsigned char)s.data[start] & 0xC0u) == 0x80u &&
                   i - start < 4u)
                --start;
            sb_append(&sb, s.data + start, i - start);
            i = start;
        }
        return sb_finish(&sb, engine, scratch, out);
    }
    /* collection_utils.rs:330 `_ => args[0].clone()`: scalar identity. */
    *out = args[0];
    return RE_STATUS_OK;
}
/* f64 -> index with Rust's saturating `as usize` cast
 * (collection_utils.rs:372 value_to_number(...) as usize) folded with the
 * upstream .min(arr.len()): NaN and negatives become 0, anything at/above
 * the length becomes the length, and in-range values truncate. */
static size_t rust_sat_index(double d, size_t count) {
    if (!(d > 0.0)) return 0u;
    if (d >= (double)count) return count;
    return (size_t)d;
}
static re_status_t call_slice(re_engine_t *engine, re_facts_t *facts, const re_value_t *args,
                              const re_string_t *arg_fact_paths, size_t argc,
                              re_eval_scratch_t *scratch, re_value_t *out) {
    const re_value_handle_t *array = NULL;
    re_strbuf_t sb;
    re_status_t status;
    double d;
    size_t start;
    size_t end;
    size_t i;
    if (argc < 2u || argc > 3u) return RE_STATUS_INVALID_ARGUMENT;
    /* Upstream errors unless the first argument is an array. */
    if (!structured_arg(facts, &args[0], arg_path(arg_fact_paths, 0u), &array) ||
        array->kind != 2)
        return RE_STATUS_INVALID_ARGUMENT;
    status = plugin_number(&engine->allocator, &args[1], &d);
    if (status != RE_STATUS_OK) return status;
    start = rust_sat_index(d, array->count);
    if (argc == 3u) {
        status = plugin_number(&engine->allocator, &args[2], &d);
        if (status != RE_STATUS_OK) return status;
        end = rust_sat_index(d, array->count);
    } else {
        end = array->count;
    }
    sb_init(&sb, &engine->allocator);
    sb_append_char(&sb, '[');
    if (start <= end) /* start > end yields the empty array upstream */
        for (i = start; i < end; ++i) {
            if (i != start) sb_append_cstr(&sb, ", ");
            sb_append_debug_value(&sb, facts, &array->members[i].scalar, array->members[i].child);
        }
    sb_append_char(&sb, ']');
    return sb_finish(&sb, engine, scratch, out);
}
static re_status_t call_keys_values(re_engine_t *engine, re_facts_t *facts, const re_value_t *args,
                                    const re_string_t *arg_fact_paths, size_t argc,
                                    int want_values, re_eval_scratch_t *scratch, re_value_t *out) {
    const re_value_handle_t *structured = NULL;
    re_strbuf_t sb;
    size_t i;
    int is_object;
    if (argc != 1u) return RE_STATUS_INVALID_ARGUMENT;
    is_object = structured_arg(facts, &args[0], arg_path(arg_fact_paths, 0u), &structured) &&
                structured->kind == 1;
    sb_init(&sb, &engine->allocator);
    sb_append_char(&sb, '[');
    /* Member (insertion) order; a non-object yields "[]" (upstream's
     * Ok(Value::Array(vec![])) for keys/values on anything but an Object). */
    if (is_object)
        for (i = 0u; i < structured->count; ++i) {
            const re_value_member_t *member = &structured->members[i];
            if (i != 0u) sb_append_cstr(&sb, ", ");
            if (want_values)
                sb_append_debug_value(&sb, facts, &member->scalar, member->child);
            else
                sb_append_debug_string(&sb, member->key, member->key_size);
        }
    sb_append_char(&sb, ']');
    return sb_finish(&sb, engine, scratch, out);
}

static int email_local_char(char c) {
    return isalnum((unsigned char)c) || c == '.' || c == '_' || c == '%' || c == '+' || c == '-';
}
static int email_domain_char(char c) {
    return isalnum((unsigned char)c) || c == '.' || c == '-';
}
/* Hand-rolled equivalent of the f80a541 email regex (validation.rs:179 via
 * the :11-13 pattern ^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$): the
 * last-dot split is match-equivalent to the backtracking regex because '.'
 * is itself in the domain class and the TLD must be all-alpha. */
static int is_valid_email_local(re_string_t s) {
    size_t i;
    size_t at = s.size;
    size_t last_dot = s.size;
    for (i = 0u; i < s.size; ++i)
        if (s.data[i] == '@') {
            if (at != s.size) return 0;
            at = i;
        }
    if (at == s.size || at == 0u || at + 1u >= s.size) return 0;
    for (i = 0u; i < at; ++i)
        if (!email_local_char(s.data[i])) return 0;
    for (i = at + 1u; i < s.size; ++i) {
        if (!email_domain_char(s.data[i])) return 0;
        if (s.data[i] == '.') last_dot = i;
    }
    if (last_dot == s.size) return 0;      /* no dot in the domain */
    if (last_dot == at + 1u) return 0;     /* the class+ before the dot is empty */
    if (s.size - last_dot - 1u < 2u) return 0; /* the TLD is shorter than 2 */
    for (i = last_dot + 1u; i < s.size; ++i)
        if (!isalpha((unsigned char)s.data[i])) return 0;
    return 1;
}
/* validation.rs:191 is_valid_phone exact. */
static int is_valid_phone_local(re_string_t s) {
    size_t i;
    size_t digits = 0u;
    for (i = 0u; i < s.size; ++i)
        if (isdigit((unsigned char)s.data[i])) ++digits;
    return digits >= 10u && digits <= 15u;
}
/* validation.rs:203 is_valid_url exact. */
static int is_valid_url_local(re_string_t s) {
    return (s.size >= 7u && memcmp(s.data, "http://", 7u) == 0) ||
           (s.size >= 8u && memcmp(s.data, "https://", 8u) == 0) ||
           (s.size >= 6u && memcmp(s.data, "ftp://", 6u) == 0);
}
static re_status_t call_validation_pred(re_engine_t *engine, re_facts_t *facts,
                                        const re_value_t *args,
                                        const re_string_t *arg_fact_paths, size_t argc, int kind,
                                        re_eval_scratch_t *scratch, re_value_t *out) {
    re_string_t s;
    re_status_t status;
    int valid;
    if (argc != 1u) return RE_STATUS_INVALID_ARGUMENT;
    status = value_to_string(engine, facts, &args[0], arg_path(arg_fact_paths, 0u), scratch, &s);
    if (status != RE_STATUS_OK) return status;
    if (kind == 0) valid = is_valid_email_local(s);
    else if (kind == 1) valid = is_valid_phone_local(s);
    else if (kind == 2) valid = is_valid_url_local(s);
    else valid = rust_f64_parse(&engine->allocator, s, NULL) == RE_STATUS_OK;
    return bool_result(out, valid);
}
static re_status_t call_in_range(re_engine_t *engine, const re_value_t *args, size_t argc,
                                 re_value_t *out) {
    double v;
    double lo;
    double hi;
    re_status_t status;
    if (argc != 3u) return RE_STATUS_INVALID_ARGUMENT;
    status = plugin_number(&engine->allocator, &args[0], &v);
    if (status != RE_STATUS_OK) return status;
    status = plugin_number(&engine->allocator, &args[1], &lo);
    if (status != RE_STATUS_OK) return status;
    status = plugin_number(&engine->allocator, &args[2], &hi);
    if (status != RE_STATUS_OK) return status;
    /* validation.rs:246: value >= min && value <= max (inclusive). */
    return bool_result(out, v >= lo && v <= hi);
}

re_status_t re_builtin_call(re_engine_t *engine, re_facts_t *facts, re_string_t name,
                            const re_value_t *args, const re_string_t *arg_fact_paths,
                            size_t argc, re_value_t *out, re_eval_scratch_t *scratch) {
    if (engine == NULL || facts == NULL || name.data == NULL || out == NULL || scratch == NULL ||
        (argc != 0u && args == NULL))
        return RE_STATUS_INVALID_ARGUMENT;
    /* A3 condition family. */
    if (name_is(name, "len") || name_is(name, "length") || name_is(name, "size") ||
        name_is(name, "count"))
        return call_len(facts, args, arg_fact_paths, argc, out);
    if (name_is(name, "isEmpty") || name_is(name, "is_empty"))
        return call_is_empty(facts, args, arg_fact_paths, argc, out);
    if (name_is(name, "contains") || name_is(name, "includes"))
        return call_contains(facts, args, arg_fact_paths, argc, out);
    if (name_is(name, "exists"))
        return call_exists(facts, args, arg_fact_paths, argc, 0, out);
    if (is_negated_presence(name))
        return call_exists(facts, args, arg_fact_paths, argc, 1, out);
    /* A4 action/RHS utility family. */
    if (name_is(name, "log") || name_is(name, "print") || name_is(name, "println"))
        return call_log(engine, facts, args, arg_fact_paths, argc, scratch, out);
    if (name_is(name, "now") || name_is(name, "timestamp"))
        return call_now(engine, scratch, out);
    if (name_is(name, "random"))
        return call_random(engine, args, argc, out);
    if (name_is(name, "format") || name_is(name, "sprintf"))
        return call_format(engine, facts, args, arg_fact_paths, argc, scratch, out);
    if (name_is(name, "sum") || name_is(name, "add"))
        return call_sum(args, argc, out);
    if (name_is(name, "max") || name_is(name, "maximum"))
        return call_max_min(args, argc, 1, out);
    if (name_is(name, "min"))
        return call_max_min(args, argc, 0, out);
    if (name_is(name, "avg") || name_is(name, "average"))
        return call_avg(args, argc, out);
    if (name_is(name, "round"))
        return call_math1(args, argc, 0, out);
    if (name_is(name, "floor"))
        return call_math1(args, argc, 1, out);
    if (name_is(name, "ceil") || name_is(name, "ceiling"))
        return call_math1(args, argc, 2, out);
    if (name_is(name, "abs"))
        return call_math1(args, argc, 3, out);
    if (name_is(name, "startswith") || name_is(name, "begins_with"))
        return call_starts_ends_with(args, argc, 1, out);
    if (name_is(name, "endswith"))
        return call_starts_ends_with(args, argc, 0, out);
    if (name_is(name, "lowercase"))
        return call_case_map(engine, facts, args, arg_fact_paths, argc, 0, scratch, out);
    if (name_is(name, "uppercase"))
        return call_case_map(engine, facts, args, arg_fact_paths, argc, 1, scratch, out);
    if (name_is(name, "trim") || name_is(name, "strip"))
        return call_trim(engine, facts, args, arg_fact_paths, argc, scratch, out);
    if (name_is(name, "split"))
        return call_split(engine, facts, args, arg_fact_paths, argc, scratch, out);
    if (name_is(name, "join"))
        return call_join(engine, facts, args, arg_fact_paths, argc, scratch, out);
    /* D1 plugin-parity family. */
    if (name_is(name, "concat"))
        return call_concat(engine, facts, args, arg_fact_paths, argc, scratch, out);
    if (name_is(name, "repeat"))
        return call_repeat(engine, facts, args, arg_fact_paths, argc, scratch, out);
    if (name_is(name, "substring"))
        return call_substring(engine, facts, args, arg_fact_paths, argc, scratch, out);
    if (name_is(name, "replace"))
        return call_replace(engine, facts, args, arg_fact_paths, argc, scratch, out);
    if (name_is(name, "sqrt"))
        return call_sqrt(engine, args, argc, out);
    if (name_is(name, "first"))
        return call_first_last(facts, args, arg_fact_paths, argc, 0, out);
    if (name_is(name, "last"))
        return call_first_last(facts, args, arg_fact_paths, argc, 1, out);
    if (name_is(name, "reverse"))
        return call_reverse(engine, facts, args, arg_fact_paths, argc, scratch, out);
    if (name_is(name, "slice"))
        return call_slice(engine, facts, args, arg_fact_paths, argc, scratch, out);
    if (name_is(name, "keys"))
        return call_keys_values(engine, facts, args, arg_fact_paths, argc, 0, scratch, out);
    if (name_is(name, "values"))
        return call_keys_values(engine, facts, args, arg_fact_paths, argc, 1, scratch, out);
    if (name_is(name, "isEmail"))
        return call_validation_pred(engine, facts, args, arg_fact_paths, argc, 0, scratch, out);
    if (name_is(name, "isPhone"))
        return call_validation_pred(engine, facts, args, arg_fact_paths, argc, 1, scratch, out);
    if (name_is(name, "isUrl"))
        return call_validation_pred(engine, facts, args, arg_fact_paths, argc, 2, scratch, out);
    if (name_is(name, "isNumeric"))
        return call_validation_pred(engine, facts, args, arg_fact_paths, argc, 3, scratch, out);
    if (name_is(name, "inRange"))
        return call_in_range(engine, args, argc, out);
    /* D1 Step 5: the upstream date_utils plugin family (functions now/today/
     * dayOfWeek/year/month/day; actions CurrentDate/CurrentTime/FormatDate/
     * AddDays/IsWeekend - f80a541 src/plugins/date_utils.rs) is deliberately
     * NOT implemented: every member reads the environment clock
     * (Local::now(), :61-62), and the A4 now/timestamp pair is the bounded
     * local equivalent. Upstream plugin metadata also declares items that are
     * NEVER registered (vapor, not implemented here either):
     * StringSplit/StringJoin/padLeft/padRight (string_utils metadata),
     * Modulo/Power/Ceil/Floor/random (math_utils metadata), ArrayMap
     * (collection_utils metadata), ParseDate/AddHours/DateDiff/dayOfYear
     * (date_utils metadata), ValidateNumeric (validation metadata). The A4
     * stringly table's update/refresh pair (f80a541 engine.rs:1421,
     * handle_update_function) stays unimplemented too: upstream's body is a
     * no-op message stub ("Updated: {arg}"/"Updated") - the fact-refresh
     * notification the names promise is the RETE-UL engine update machinery,
     * documented upstream-degenerate vapor (the conformance file's
     * update-all-facts-of-type row), so there is no honest local target to
     * dispatch to. Unknown names keep falling through to NOT_FOUND, so a rule
     * calling them is skipped like any unknown function. */
    return RE_STATUS_NOT_FOUND;
}
