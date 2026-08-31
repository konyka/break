#include "test_framework.h"
#include <rule_engine/rule_engine.h>
#include <rule_engine/re_internal.h>
#include <stdlib.h>
#include <string.h>

/*
 * Plugin boundary parity (Task D1, upstream rust-rule-engine f80a541
 * src/plugins/): the PURE plugin function helpers as engine built-ins -
 * concat/repeat/substring/replace (string_utils.rs), sqrt (math_utils.rs),
 * first/last/reverse/slice/keys/values (collection_utils.rs), and
 * isEmail/isPhone/isUrl/isNumeric/inRange (validation.rs). Upstream attaches
 * them via engine.load_plugin; here they dispatch behind re_builtin_call, so
 * a registered host function still overrides them. The date_utils family is
 * deliberately absent (clock-dependent), and the upstream metadata-declared
 * but never-registered names stay unregistered (vapor). Array results
 * surface as debug strings (the split idiom: the scalar function ABI cannot
 * return an array); object keys/values follow the local store's insertion
 * order, pinned below. re_internal.h is included for the classifier pins
 * (re_builtin_is / re_builtin_is_predicate / re_condition_is_pure).
 */

static re_string_t text(const char *value) { return (re_string_t){value, strlen(value)}; }
static re_value_t integer(int64_t value) { return (re_value_t){RE_VALUE_INT64, {.int64_value = value}}; }
static re_value_t string(const char *value) { return (re_value_t){RE_VALUE_STRING, {.string = {value, strlen(value)}}}; }

static void run_program(re_engine_t *engine, re_facts_t *facts, const char *source) {
    re_program_t *program = NULL;
    ASSERT_EQ(re_program_load(NULL, text(source), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
}

/* Loads and runs a one-off source against a fresh engine/facts pair,
 * asserting the run's status (the A4 error-idiom tests). */
static void expect_run_status(const char *source, re_status_t expected) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    ASSERT_EQ(re_program_load(NULL, text(source), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), expected);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

static void assert_int_fact(re_facts_t *facts, const char *name, int64_t expected) {
    re_value_t out = {RE_VALUE_NONE, {0}};
    ASSERT_EQ(re_facts_get(facts, text(name), &out), RE_STATUS_OK);
    ASSERT_EQ(out.type, RE_VALUE_INT64);
    ASSERT_EQ(out.as.int64_value, expected);
}
static void assert_bool_fact(re_facts_t *facts, const char *name, int expected) {
    re_value_t out = {RE_VALUE_NONE, {0}};
    ASSERT_EQ(re_facts_get(facts, text(name), &out), RE_STATUS_OK);
    ASSERT_EQ(out.type, RE_VALUE_BOOL);
    ASSERT_EQ(out.as.boolean, expected);
}
static void assert_double_fact(re_facts_t *facts, const char *name, double expected) {
    re_value_t out = {RE_VALUE_NONE, {0}};
    ASSERT_EQ(re_facts_get(facts, text(name), &out), RE_STATUS_OK);
    ASSERT_EQ(out.type, RE_VALUE_DOUBLE);
    ASSERT_TRUE(out.as.double_value == expected);
}
static void assert_string_fact(re_facts_t *facts, const char *name, const char *expected) {
    re_value_t out = {RE_VALUE_NONE, {0}};
    ASSERT_EQ(re_facts_get(facts, text(name), &out), RE_STATUS_OK);
    ASSERT_EQ(out.type, RE_VALUE_STRING);
    ASSERT_EQ(out.as.string.size, strlen(expected));
    ASSERT_TRUE(memcmp(out.as.string.data, expected, out.as.string.size) == 0);
}
static void assert_string_bytes(re_facts_t *facts, const char *name, const char *expected, size_t size) {
    re_value_t out = {RE_VALUE_NONE, {0}};
    ASSERT_EQ(re_facts_get(facts, text(name), &out), RE_STATUS_OK);
    ASSERT_EQ(out.type, RE_VALUE_STRING);
    ASSERT_EQ(out.as.string.size, size);
    ASSERT_TRUE(memcmp(out.as.string.data, expected, size) == 0);
}
static void assert_null_fact(re_facts_t *facts, const char *name) {
    re_value_t out = {RE_VALUE_NONE, {0}};
    ASSERT_EQ(re_facts_get(facts, text(name), &out), RE_STATUS_OK);
    ASSERT_EQ(out.type, RE_VALUE_NULL);
}
static void assert_no_fact(re_facts_t *facts, const char *name) {
    re_value_t out = {RE_VALUE_NONE, {0}};
    ASSERT_EQ(re_facts_get(facts, text(name), &out), RE_STATUS_NOT_FOUND);
}

static void set_array_fact(re_facts_t *facts, const char *name, const re_value_t *items, size_t count) {
    re_value_handle_t *array = NULL;
    size_t i;
    ASSERT_EQ(re_value_create_array(facts, &array), RE_STATUS_OK);
    for (i = 0u; i < count; ++i) ASSERT_EQ(re_value_array_append(array, &items[i]), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set_value(facts, text(name), array), RE_STATUS_OK);
    re_value_destroy(array);
}
static void set_object_fact(re_facts_t *facts, const char *name, const char *const *keys,
                            const re_value_t *vals, size_t count) {
    re_value_handle_t *object = NULL;
    size_t i;
    ASSERT_EQ(re_value_create_object(facts, &object), RE_STATUS_OK);
    for (i = 0u; i < count; ++i) ASSERT_EQ(re_value_object_set(object, text(keys[i]), &vals[i]), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set_value(facts, text(name), object), RE_STATUS_OK);
    re_value_destroy(object);
}

/* ---- string helpers (string_utils.rs) ---------------------------------- */

TEST(plugin_concat_mixed_types) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    const char *const keys[1] = {"name"};
    re_value_t vals[1];
    vals[0] = string("Jo");
    set_object_fact(facts, "S", keys, vals, 1u);
    run_program(engine, facts,
        "rule \"R\" { when true then A = concat(\"a\", 1, true, 2.5);"
        " B = concat(S.name, \"!\"); C = concat(null, \"x\"); }");
    /* Display forms joined with no separator (concat at string_utils.rs:148). */
    assert_string_fact(facts, "A", "a1true2.5");
    assert_string_fact(facts, "B", "Jo!");
    /* Upstream's value_to_string errors on Null; the local display form
     * stringifies it (documented divergence). */
    assert_string_fact(facts, "C", "nullx");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(plugin_concat_arity_errors) {
    /* Upstream: "concat requires at least 2 arguments". */
    expect_run_status("rule \"R\" { when true then A = concat(\"a\"); }", RE_STATUS_INVALID_ARGUMENT);
    expect_run_status("rule \"R\" { when true then A = concat(); }", RE_STATUS_INVALID_ARGUMENT);
}

TEST(plugin_repeat_exact_zero_and_cap) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t out = {RE_VALUE_NONE, {0}};
    run_program(engine, facts,
        "rule \"R\" { when true then A = repeat(\"ab\", 3); B = repeat(\"x\", 0);"
        " C = repeat(7, 2); D = repeat(\"ab\", 1000); }");
    assert_string_fact(facts, "A", "ababab");
    assert_string_fact(facts, "B", "");
    /* The text argument stringifies (upstream value_to_string). */
    assert_string_fact(facts, "C", "77");
    /* The 1000 cap is inclusive (string_utils.rs:163 count > 1000 errors). */
    ASSERT_EQ(re_facts_get(facts, text("D"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.type, RE_VALUE_STRING);
    ASSERT_EQ(out.as.string.size, 2000u);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(plugin_repeat_over_cap_and_bad_count_error) {
    /* Over-cap is RE_STATUS_LIMIT (brief); a negative count wraps to a huge
     * usize upstream and hits the same cap error. */
    expect_run_status("rule \"R\" { when true then A = repeat(\"x\", 1001); }", RE_STATUS_LIMIT);
    expect_run_status("rule \"R\" { when true then A = repeat(\"x\", -1); }", RE_STATUS_LIMIT);
    /* The count must be an Integer upstream (a string count is its Err). */
    expect_run_status("rule \"R\" { when true then A = repeat(\"x\", \"2\"); }", RE_STATUS_INVALID_ARGUMENT);
    expect_run_status("rule \"R\" { when true then A = repeat(\"x\"); }", RE_STATUS_INVALID_ARGUMENT);
}

TEST(plugin_substring_bounds) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    run_program(engine, facts,
        "rule \"R\" { when true then A = substring(\"hello\", 1); B = substring(\"hello\", 1, 3);"
        " C = substring(\"hello\", 5); D = substring(\"hello\", 9); E = substring(\"hello\", -1);"
        " F = substring(\"hello\", 2, 99); G = substring(\"\", 0); H = substring(\"hello\", 0, 0); }");
    assert_string_fact(facts, "A", "ello");
    assert_string_fact(facts, "B", "ell");
    /* start >= len yields "" (string_utils.rs:190); a negative start wraps
     * huge upstream and lands on the same early-out. */
    assert_string_fact(facts, "C", "");
    assert_string_fact(facts, "D", "");
    assert_string_fact(facts, "E", "");
    /* The length clamps to the text end (upstream min(start + len, len)). */
    assert_string_fact(facts, "F", "llo");
    assert_string_fact(facts, "G", "");
    assert_string_fact(facts, "H", "");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(plugin_substring_is_byte_based_over_utf8) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    /* "h\xC3\xA9llo" ("hello" with a 2-byte e-acute): byte offsets, not
     * codepoints - upstream slices bytes too and PANICS on a non-boundary;
     * the byte slice is returned as-is here (documented divergence). */
    run_program(engine, facts,
        "rule \"R\" { when true then A = substring(\"h\xC3\xA9llo\", 1, 2);"
        " B = substring(\"h\xC3\xA9llo\", 2, 2); }");
    assert_string_bytes(facts, "A", "\xC3\xA9", 2u);
    assert_string_bytes(facts, "B", "\xA9l", 2u);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(plugin_substring_arity_and_type_errors) {
    expect_run_status("rule \"R\" { when true then A = substring(\"a\"); }", RE_STATUS_INVALID_ARGUMENT);
    expect_run_status("rule \"R\" { when true then A = substring(\"a\", 0, 1, 2); }", RE_STATUS_INVALID_ARGUMENT);
    /* Start/length must be Integer upstream. */
    expect_run_status("rule \"R\" { when true then A = substring(\"abc\", \"1\"); }", RE_STATUS_INVALID_ARGUMENT);
    expect_run_status("rule \"R\" { when true then A = substring(\"abc\", 0, \"1\"); }", RE_STATUS_INVALID_ARGUMENT);
    /* A negative length is a usize-wrap/panic corner upstream; rejected here. */
    expect_run_status("rule \"R\" { when true then A = substring(\"abc\", 0, -1); }", RE_STATUS_INVALID_ARGUMENT);
}

TEST(plugin_replace_all_occurrences) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    run_program(engine, facts,
        "rule \"R\" { when true then A = replace(\"aaa\", \"a\", \"b\");"
        " B = replace(\"hello world\", \"o\", \"0\"); C = replace(\"abc\", \"x\", \"y\");"
        " D = replace(\"aaaa\", \"aa\", \"b\"); E = replace(\"aXbXc\", \"X\", \"\"); }");
    /* Rust str::replace: ALL non-overlapping occurrences, left to right
     * (string_utils.rs:129 StringReplace body). */
    assert_string_fact(facts, "A", "bbb");
    assert_string_fact(facts, "B", "hell0 w0rld");
    assert_string_fact(facts, "C", "abc");
    assert_string_fact(facts, "D", "bb");
    assert_string_fact(facts, "E", "abc");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(plugin_replace_empty_from_inserts_at_boundaries) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    /* Rust: "ab".replace("", "-") is "-a-b-" (upstream-exact). */
    run_program(engine, facts,
        "rule \"R\" { when true then A = replace(\"ab\", \"\", \"-\"); B = replace(\"\", \"\", \"x\"); }");
    assert_string_fact(facts, "A", "-a-b-");
    assert_string_fact(facts, "B", "x");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(plugin_replace_empty_from_utf8_char_boundaries) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    /* Rust: "\xC3\xA9".replace("", "-") is "-\xC3\xA9-": the empty pattern
     * matches at every CHARACTER boundary, so the 2-byte codepoint stays
     * intact and the result is valid UTF-8 (upstream-exact). */
    run_program(engine, facts,
        "rule \"R\" { when true then A = replace(\"\xC3\xA9\", \"\", \"-\"); }");
    assert_string_bytes(facts, "A", "-\xC3\xA9-", 4u);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(plugin_replace_arity_errors) {
    expect_run_status("rule \"R\" { when true then A = replace(\"a\", \"b\"); }", RE_STATUS_INVALID_ARGUMENT);
}

/* ---- math helper (math_utils.rs) --------------------------------------- */

TEST(plugin_sqrt_values) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    run_program(engine, facts,
        "rule \"R\" { when true then A = sqrt(9); B = sqrt(2.25); C = sqrt(\"16\"); D = sqrt(0); }");
    /* Always a Number upstream (math_utils.rs:170); a numeric string parses
     * through upstream's value_to_number. */
    assert_double_fact(facts, "A", 3.0);
    assert_double_fact(facts, "B", 1.5);
    assert_double_fact(facts, "C", 4.0);
    assert_double_fact(facts, "D", 0.0);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(plugin_sqrt_negative_and_bad_args_error) {
    expect_run_status("rule \"R\" { when true then A = sqrt(-1); }", RE_STATUS_INVALID_ARGUMENT);
    expect_run_status("rule \"R\" { when true then A = sqrt(\"abc\"); }", RE_STATUS_INVALID_ARGUMENT);
    expect_run_status("rule \"R\" { when true then A = sqrt(); }", RE_STATUS_INVALID_ARGUMENT);
    expect_run_status("rule \"R\" { when true then A = sqrt(1, 2); }", RE_STATUS_INVALID_ARGUMENT);
}

/* ---- collection expression functions (collection_utils.rs) -------------- */

TEST(plugin_first_last_arrays) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t items[3];
    items[0] = integer(1); items[1] = string("two"); items[2] = integer(3);
    set_array_fact(facts, "Items", items, 3u);
    run_program(engine, facts,
        "rule \"R\" { when true then A = first(Items); B = last(Items); }"
        "rule \"W\" { when first(Items) == 1 and last(Items) == 3 then Hit = 1; }");
    assert_int_fact(facts, "A", 1);
    assert_int_fact(facts, "B", 3);
    assert_int_fact(facts, "Hit", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(plugin_first_last_empty_and_non_array_are_null) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t items[1];
    const char *const keys[1] = {"k"};
    re_value_t vals[1];
    items[0] = integer(1);
    vals[0] = integer(1);
    set_array_fact(facts, "Empty", items, 0u);
    set_object_fact(facts, "Obj", keys, vals, 1u);
    run_program(engine, facts,
        "rule \"R\" { when true then A = first(Empty); B = last(Empty);"
        " C = first(\"\"); D = first(Obj); E = last(5); F = first(null); }");
    /* collection_utils.rs:286/:308: unwrap_or(Value::Null) and
     * `_ => Value::Null` - an empty input is NOT an error. */
    assert_null_fact(facts, "A");
    assert_null_fact(facts, "B");
    assert_null_fact(facts, "C");
    assert_null_fact(facts, "D");
    assert_null_fact(facts, "E");
    assert_null_fact(facts, "F");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(plugin_first_last_strings_are_codepoint_based) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    /* Upstream chars().next()/chars().last(): codepoints, not bytes. */
    run_program(engine, facts,
        "rule \"R\" { when true then A = first(\"hello\"); B = last(\"hello\");"
        " C = first(\"\xC3\xA9lan\"); D = last(\"\xC3\xA9lan\"); E = first(\"a\xC3\xA9\"); }");
    assert_string_fact(facts, "A", "h");
    assert_string_fact(facts, "B", "o");
    assert_string_bytes(facts, "C", "\xC3\xA9", 2u);
    assert_string_fact(facts, "D", "n");
    assert_string_fact(facts, "E", "a");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(plugin_first_last_arity_errors) {
    /* Literal arguments: a bare absent fact path would be absorbed by the A3
     * arg-miss rule before the arity check ever runs. */
    expect_run_status("rule \"R\" { when true then A = first(); }", RE_STATUS_INVALID_ARGUMENT);
    expect_run_status("rule \"R\" { when true then A = last(\"ab\", 2); }", RE_STATUS_INVALID_ARGUMENT);
}

TEST(plugin_reverse_array_string_and_identity) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t nums[3];
    re_value_t words[2];
    const char *const keys[1] = {"k"};
    re_value_t vals[1];
    nums[0] = integer(1); nums[1] = integer(2); nums[2] = integer(3);
    words[0] = string("a"); words[1] = string("b");
    vals[0] = integer(1);
    set_array_fact(facts, "Nums", nums, 3u);
    set_array_fact(facts, "Words", words, 2u);
    set_object_fact(facts, "Obj", keys, vals, 1u);
    run_program(engine, facts,
        "rule \"R\" { when true then A = reverse(Nums); B = reverse(Words);"
        " C = reverse(\"abc\"); D = reverse(\"a\xC3\xA9\"); E = reverse(5); F = reverse(Obj); }");
    /* Array results are debug strings (the split idiom): strings quoted,
     * other scalars in display form (collection_utils.rs:330). */
    assert_string_fact(facts, "A", "[3, 2, 1]");
    assert_string_fact(facts, "B", "[\"b\", \"a\"]");
    /* chars().rev(): codepoint order reversed, bytes within one kept. */
    assert_string_fact(facts, "C", "cba");
    assert_string_bytes(facts, "D", "\xC3\xA9" "a", 3u);
    /* `_ => args[0].clone()`: scalar identity; a structured object surfaces
     * as its display placeholder. */
    assert_int_fact(facts, "E", 5);
    assert_string_fact(facts, "F", "[Object]");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(plugin_slice_clamps_and_empties) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t items[3];
    items[0] = integer(1); items[1] = integer(2); items[2] = integer(3);
    set_array_fact(facts, "Items", items, 3u);
    run_program(engine, facts,
        "rule \"R\" { when true then A = slice(Items, 1); B = slice(Items, 0, 2);"
        " C = slice(Items, 5); D = slice(Items, 2, 1); E = slice(Items, -1, 2);"
        " F = slice(Items, 1, 99); G = slice(Items, 0, 0); }");
    /* collection_utils.rs:372: f64 -> usize SATURATES (negative -> 0), both
     * bounds clamp to the length, start > end yields the empty array. */
    assert_string_fact(facts, "A", "[2, 3]");
    assert_string_fact(facts, "B", "[1, 2]");
    assert_string_fact(facts, "C", "[]");
    assert_string_fact(facts, "D", "[]");
    assert_string_fact(facts, "E", "[1, 2]");
    assert_string_fact(facts, "F", "[2, 3]");
    assert_string_fact(facts, "G", "[]");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(plugin_slice_requires_array_and_numeric_bounds) {
    /* Upstream errors unless the first argument is an array (a string is
     * NOT sliceable upstream, unlike first/last/reverse). Literal arguments:
     * a bare absent fact path would be absorbed by the A3 arg-miss rule. */
    expect_run_status("rule \"R\" { when true then A = slice(\"abc\", 1); }", RE_STATUS_INVALID_ARGUMENT);
    expect_run_status("rule \"R\" { when true then A = slice(5, 1); }", RE_STATUS_INVALID_ARGUMENT);
    expect_run_status("rule \"R\" { when true then A = slice(\"abc\"); }", RE_STATUS_INVALID_ARGUMENT);
}

TEST(plugin_keys_values_insertion_order) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    /* Deliberately unsorted: the pin is the local store's INSERTION order
     * (upstream iterates a HashMap whose order is unspecified). */
    const char *const keys[3] = {"b", "a", "c"};
    re_value_t vals[3];
    vals[0] = integer(2); vals[1] = string("x"); vals[2] = integer(3);
    set_object_fact(facts, "Obj", keys, vals, 3u);
    run_program(engine, facts,
        "rule \"R\" { when true then K = keys(Obj); V = values(Obj); }");
    assert_string_fact(facts, "K", "[\"b\", \"a\", \"c\"]");
    assert_string_fact(facts, "V", "[2, \"x\", 3]");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(plugin_keys_values_non_object_is_empty) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t items[1];
    items[0] = integer(1);
    set_array_fact(facts, "Arr", items, 1u);
    run_program(engine, facts,
        "rule \"R\" { when true then A = keys(Arr); B = values(Arr);"
        " C = keys(5); D = values(\"s\"); }");
    /* collection_utils.rs:404/:421: a non-object yields Ok(vec![]). */
    assert_string_fact(facts, "A", "[]");
    assert_string_fact(facts, "B", "[]");
    assert_string_fact(facts, "C", "[]");
    assert_string_fact(facts, "D", "[]");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

/* ---- validation helpers (validation.rs) --------------------------------- */

TEST(plugin_is_numeric_table) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    const char *const keys[1] = {"n"};
    re_value_t vals[1];
    vals[0] = string("42");
    set_object_fact(facts, "S", keys, vals, 1u);
    /* validation.rs:215: whole-string Rust f64 FromStr - signs, dots,
     * exponents, and the case-insensitive inf/infinity/nan words parse; the
     * bare-predicate form means fn(...) == true. */
    run_program(engine, facts,
        "rule \"Bare\" { when isNumeric(S.n) then HitBare = 1; }"
        "rule \"R\" { when true then"
        " T1 = isNumeric(\"123\"); T2 = isNumeric(\"-1.5\"); T3 = isNumeric(\"1e3\");"
        " T4 = isNumeric(\".5\"); T5 = isNumeric(\"5.\"); T6 = isNumeric(\"NaN\");"
        " T7 = isNumeric(\"inf\"); T8 = isNumeric(\"-Infinity\"); T9 = isNumeric(7);"
        " F1 = isNumeric(\"12a\"); F2 = isNumeric(\"\"); F3 = isNumeric(\" 1\");"
        " F4 = isNumeric(\"1 \"); F5 = isNumeric(\"0x10\"); F6 = isNumeric(\"+\");"
        " F7 = isNumeric(\"1.2.3\"); F8 = isNumeric(\"1e\"); F9 = isNumeric(true); }");
    assert_int_fact(facts, "HitBare", 1);
    assert_bool_fact(facts, "T1", 1); assert_bool_fact(facts, "T2", 1);
    assert_bool_fact(facts, "T3", 1); assert_bool_fact(facts, "T4", 1);
    assert_bool_fact(facts, "T5", 1); assert_bool_fact(facts, "T6", 1);
    assert_bool_fact(facts, "T7", 1); assert_bool_fact(facts, "T8", 1);
    assert_bool_fact(facts, "T9", 1);
    assert_bool_fact(facts, "F1", 0); assert_bool_fact(facts, "F2", 0);
    assert_bool_fact(facts, "F3", 0); assert_bool_fact(facts, "F4", 0);
    assert_bool_fact(facts, "F5", 0); assert_bool_fact(facts, "F6", 0);
    assert_bool_fact(facts, "F7", 0); assert_bool_fact(facts, "F8", 0);
    assert_bool_fact(facts, "F9", 0);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(plugin_is_url_prefixes) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    const char *const keys[1] = {"u"};
    re_value_t vals[1];
    vals[0] = string("example.com");
    set_object_fact(facts, "S", keys, vals, 1u);
    /* validation.rs:203 exact: http://, https://, or ftp:// prefixes. */
    run_program(engine, facts,
        "rule \"Bare\" { when isUrl(S.u) then HitBare = 1; }"
        "rule \"R\" { when true then A = isUrl(\"http://x\"); B = isUrl(\"https://x\");"
        " C = isUrl(\"ftp://x\"); D = isUrl(\"HTTP://x\"); E = isUrl(\"xhttp://y\");"
        " F = isUrl(\"\"); }");
    assert_no_fact(facts, "HitBare");
    assert_bool_fact(facts, "A", 1);
    assert_bool_fact(facts, "B", 1);
    assert_bool_fact(facts, "C", 1);
    assert_bool_fact(facts, "D", 0);
    assert_bool_fact(facts, "E", 0);
    assert_bool_fact(facts, "F", 0);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(plugin_is_email_handrolled_regex) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    /* Hand-rolled equivalent of validation.rs:179's
     * ^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$ (no regex engine). */
    run_program(engine, facts,
        "rule \"R\" { when true then"
        " T1 = isEmail(\"a@b.co\"); T2 = isEmail(\"john.doe+tag@example.com\");"
        " T3 = isEmail(\"a@b..com\");"
        " F1 = isEmail(\"a@b.c\"); F2 = isEmail(\"a@b\"); F3 = isEmail(\"@b.com\");"
        " F4 = isEmail(\"a@.com\"); F5 = isEmail(\"a b@c.com\"); F6 = isEmail(\"a@@b.com\");"
        " F7 = isEmail(\"a@b.c1\"); F8 = isEmail(\"\"); }");
    assert_bool_fact(facts, "T1", 1);
    assert_bool_fact(facts, "T2", 1);
    /* Regex-equivalence corner: the domain class includes '.', so the
     * backtracking regex accepts a doubled dot before the TLD. */
    assert_bool_fact(facts, "T3", 1);
    assert_bool_fact(facts, "F1", 0);
    assert_bool_fact(facts, "F2", 0);
    assert_bool_fact(facts, "F3", 0);
    assert_bool_fact(facts, "F4", 0);
    assert_bool_fact(facts, "F5", 0);
    assert_bool_fact(facts, "F6", 0);
    assert_bool_fact(facts, "F7", 0);
    assert_bool_fact(facts, "F8", 0);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(plugin_is_phone_digit_count) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    /* validation.rs:191 exact: 10-15 ASCII digits after stripping
     * non-digits. */
    run_program(engine, facts,
        "rule \"R\" { when true then T1 = isPhone(\"1234567890\");"
        " T2 = isPhone(\"+1 (555) 123-4567\"); T3 = isPhone(\"123456789012345\");"
        " F1 = isPhone(\"123456789\"); F2 = isPhone(\"1234567890123456\");"
        " F3 = isPhone(\"abcdefghij\"); F4 = isPhone(\"\"); }");
    assert_bool_fact(facts, "T1", 1);
    assert_bool_fact(facts, "T2", 1);
    assert_bool_fact(facts, "T3", 1);
    assert_bool_fact(facts, "F1", 0);
    assert_bool_fact(facts, "F2", 0);
    assert_bool_fact(facts, "F3", 0);
    assert_bool_fact(facts, "F4", 0);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(plugin_in_range_inclusive_bounds) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    const char *const keys[1] = {"v"};
    re_value_t vals[1];
    vals[0] = integer(5);
    set_object_fact(facts, "S", keys, vals, 1u);
    /* validation.rs:246: value >= min && value <= max over value_to_number
     * arguments (numeric strings parse). */
    run_program(engine, facts,
        "rule \"Bare\" { when inRange(S.v, 1, 10) then HitBare = 1; }"
        "rule \"R\" { when true then T1 = inRange(5, 1, 10); T2 = inRange(1, 1, 10);"
        " T3 = inRange(10, 1, 10); T4 = inRange(\"5\", \"1\", \"10\"); T5 = inRange(2.5, 1, 3);"
        " F1 = inRange(0, 1, 10); F2 = inRange(11, 1, 10); F3 = inRange(5, 10, 1); }");
    assert_int_fact(facts, "HitBare", 1);
    assert_bool_fact(facts, "T1", 1);
    assert_bool_fact(facts, "T2", 1);
    assert_bool_fact(facts, "T3", 1);
    assert_bool_fact(facts, "T4", 1);
    assert_bool_fact(facts, "T5", 1);
    assert_bool_fact(facts, "F1", 0);
    assert_bool_fact(facts, "F2", 0);
    /* Inverted bounds are simply false (no reordering upstream). */
    assert_bool_fact(facts, "F3", 0);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(plugin_validation_arity_and_type_errors) {
    /* Wrong arity and unparseable bounds are upstream's Err (INVALID_ARGUMENT);
     * a non-numeric VALUE argument errors too (value_to_number). */
    expect_run_status("rule \"R\" { when true then A = isEmail(); }", RE_STATUS_INVALID_ARGUMENT);
    expect_run_status("rule \"R\" { when true then A = isNumeric(\"1\", \"2\"); }", RE_STATUS_INVALID_ARGUMENT);
    expect_run_status("rule \"R\" { when true then A = inRange(5, 1); }", RE_STATUS_INVALID_ARGUMENT);
    expect_run_status("rule \"R\" { when true then A = inRange(\"abc\", 1, 10); }", RE_STATUS_INVALID_ARGUMENT);
    expect_run_status("rule \"R\" { when true then A = inRange(5, true, 10); }", RE_STATUS_INVALID_ARGUMENT);
}

/* ---- dispatch rules: override, arg-miss, vapor, classification ---------- */

static re_status_t override_concat_call(re_engine_t *engine, re_facts_t *facts,
                                        const re_value_t *arguments, size_t argument_count,
                                        re_value_t *out_value, void *context) {
    (void)engine; (void)facts; (void)arguments; (void)argument_count; (void)context;
    out_value->type = RE_VALUE_STRING;
    out_value->as.string.data = "OVERRIDE";
    out_value->as.string.size = 8u;
    return RE_STATUS_OK;
}
static re_status_t override_is_numeric_call(re_engine_t *engine, re_facts_t *facts,
                                            const re_value_t *arguments, size_t argument_count,
                                            re_value_t *out_value, void *context) {
    (void)engine; (void)facts; (void)arguments; (void)argument_count; (void)context;
    out_value->type = RE_VALUE_BOOL;
    out_value->as.boolean = 0;
    return RE_STATUS_OK;
}

TEST(plugin_host_override_wins_over_new_names) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_function_t *concat_fn = NULL;
    re_function_t *is_numeric_fn = NULL;
    re_function_descriptor_t concat_descriptor = {sizeof(concat_descriptor), RE_ABI_VERSION_MAJOR,
        {"concat", 6u}, override_concat_call, NULL, NULL};
    re_function_descriptor_t is_numeric_descriptor = {sizeof(is_numeric_descriptor), RE_ABI_VERSION_MAJOR,
        {"isNumeric", 9u}, override_is_numeric_call, NULL, NULL};
    ASSERT_EQ(re_engine_register_function(engine, &concat_descriptor, &concat_fn), RE_STATUS_OK);
    ASSERT_EQ(re_engine_register_function(engine, &is_numeric_descriptor, &is_numeric_fn), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"R\" { when true then A = concat(\"x\", \"y\"); B = repeat(\"z\", 2); }"
        "rule \"W\" { when isNumeric(\"5\") then Hit = 1; }");
    /* The registry wins over the new built-ins; the unregistered repeat
     * still dispatches to the built-in. */
    assert_string_fact(facts, "A", "OVERRIDE");
    assert_string_fact(facts, "B", "zz");
    assert_no_fact(facts, "Hit");
    re_function_unregister(concat_fn);
    re_function_unregister(is_numeric_fn);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(plugin_absent_fact_arg_miss_is_false) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    /* The A3 arg-miss absorption covers the new names: an unresolvable bare
     * fact-path argument makes the built-in yield false instead of skipping
     * the rule. */
    run_program(engine, facts,
        "rule \"M\" { when isNumeric(Missing) then HitM = 1; }"
        "rule \"C\" { when concat(Missing, \"x\") == \"x\" then HitC = 1; }"
        "rule \"K\" { when Other == 1 then HitK = 1; }");
    assert_no_fact(facts, "HitM");
    assert_no_fact(facts, "HitC");
    assert_no_fact(facts, "HitK");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(plugin_date_family_and_vapor_stay_unimplemented) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    /* date_utils (clock-dependent) and the metadata-vapor names are NOT
     * built-ins: unknown names keep the A3 rule-skip behavior. */
    run_program(engine, facts,
        "rule \"D1\" { when today() == 1 then HitD1 = 1; }"
        "rule \"D2\" { when dayOfWeek() == 1 then HitD2 = 1; }"
        "rule \"V1\" { when padLeft(\"a\", 1) == 1 then HitV1 = 1; }"
        "rule \"V2\" { when ArrayMap() == 1 then HitV2 = 1; }"
        "rule \"Ok\" { when true then HitOk = 1; }");
    assert_no_fact(facts, "HitD1");
    assert_no_fact(facts, "HitD2");
    assert_no_fact(facts, "HitV1");
    assert_no_fact(facts, "HitV2");
    assert_int_fact(facts, "HitOk", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(plugin_classification_pins) {
    static const char *const names[] = {"concat", "repeat", "substring", "replace", "sqrt",
        "first", "last", "reverse", "slice", "keys", "values",
        "isEmail", "isPhone", "isUrl", "isNumeric", "inRange"};
    static const char *const predicates[] = {"isEmail", "isPhone", "isUrl", "isNumeric", "inRange"};
    static const char *const absent[] = {"today", "dayOfWeek", "year", "month", "day",
        "padLeft", "padRight", "StringSplit", "StringJoin", "ArrayMap", "ParseDate", "ValidateNumeric"};
    size_t i;
    re_expr_t cond;
    for (i = 0u; i < sizeof(names) / sizeof(names[0]); ++i)
        ASSERT_TRUE(re_builtin_is(names[i], strlen(names[i])));
    for (i = 0u; i < sizeof(predicates) / sizeof(predicates[0]); ++i)
        ASSERT_TRUE(re_builtin_is_predicate(predicates[i], strlen(predicates[i])));
    for (i = 0u; i < sizeof(absent) / sizeof(absent[0]); ++i)
        ASSERT_FALSE(re_builtin_is(absent[i], strlen(absent[i])));
    /* Value-returning helpers are NOT bare-condition predicates. */
    ASSERT_FALSE(re_builtin_is_predicate("concat", 6u));
    ASSERT_FALSE(re_builtin_is_predicate("first", 5u));
    ASSERT_FALSE(re_builtin_is_predicate("keys", 4u));
    ASSERT_FALSE(re_builtin_is_predicate("sqrt", 4u));
    /* A4 purity rule unchanged: EVERY function-calling condition is impure
     * (first-pass-only, never on executor workers) even though all D1 names
     * are deterministic from their arguments; plain fact/literal compares
     * stay pure. */
    memset(&cond, 0, sizeof(cond));
    cond.kind = RE_EXPR_COMPARE;
    cond.left.kind = RE_OPERAND_FUNCTION;
    cond.right.kind = RE_OPERAND_LITERAL;
    ASSERT_FALSE(re_condition_is_pure(&cond));
    cond.left.kind = RE_OPERAND_FACT;
    ASSERT_TRUE(re_condition_is_pure(&cond));
}

TEST(plugin_non_predicate_bare_condition_is_a_parse_error) {
    re_program_t *program = NULL;
    /* first() returns a value, not a bool: the bare whole-condition form is
     * reserved for predicate built-ins (parser.c re_builtin_is_predicate). */
    ASSERT_EQ(re_program_load(NULL, text("rule \"R\" { when first(Items) then A = 1; }"),
                              NULL, &program), RE_STATUS_PARSE_ERROR);
}

TEST_MAIN_BEGIN()
    RUN_TEST(plugin_concat_mixed_types);
    RUN_TEST(plugin_concat_arity_errors);
    RUN_TEST(plugin_repeat_exact_zero_and_cap);
    RUN_TEST(plugin_repeat_over_cap_and_bad_count_error);
    RUN_TEST(plugin_substring_bounds);
    RUN_TEST(plugin_substring_is_byte_based_over_utf8);
    RUN_TEST(plugin_substring_arity_and_type_errors);
    RUN_TEST(plugin_replace_all_occurrences);
    RUN_TEST(plugin_replace_empty_from_inserts_at_boundaries);
    RUN_TEST(plugin_replace_empty_from_utf8_char_boundaries);
    RUN_TEST(plugin_replace_arity_errors);
    RUN_TEST(plugin_sqrt_values);
    RUN_TEST(plugin_sqrt_negative_and_bad_args_error);
    RUN_TEST(plugin_first_last_arrays);
    RUN_TEST(plugin_first_last_empty_and_non_array_are_null);
    RUN_TEST(plugin_first_last_strings_are_codepoint_based);
    RUN_TEST(plugin_first_last_arity_errors);
    RUN_TEST(plugin_reverse_array_string_and_identity);
    RUN_TEST(plugin_slice_clamps_and_empties);
    RUN_TEST(plugin_slice_requires_array_and_numeric_bounds);
    RUN_TEST(plugin_keys_values_insertion_order);
    RUN_TEST(plugin_keys_values_non_object_is_empty);
    RUN_TEST(plugin_is_numeric_table);
    RUN_TEST(plugin_is_url_prefixes);
    RUN_TEST(plugin_is_email_handrolled_regex);
    RUN_TEST(plugin_is_phone_digit_count);
    RUN_TEST(plugin_in_range_inclusive_bounds);
    RUN_TEST(plugin_validation_arity_and_type_errors);
    RUN_TEST(plugin_host_override_wins_over_new_names);
    RUN_TEST(plugin_absent_fact_arg_miss_is_false);
    RUN_TEST(plugin_date_family_and_vapor_stay_unimplemented);
    RUN_TEST(plugin_classification_pins);
    RUN_TEST(plugin_non_predicate_bare_condition_is_a_parse_error);
TEST_MAIN_END()
