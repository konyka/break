#include "test_framework.h"
#include <rule_engine/rule_engine.h>
#include <stdlib.h>
#include <string.h>

/*
 * GRL surface parity (Task A1, upstream rust-rule-engine v1.21.4 semantics):
 * word aliases eq/ne/gt/gte/lt/lte/not_contains, case-insensitive bool/null
 * literals, the % modulo operator (f64 fmod semantics; Integer result iff
 * both operands are Integer and the result is integral), string `+`
 * concatenation, and the D4 comparison audit: equality is strictly typed
 * (Integer(1) != Number(1.0)) while relational operators coerce operands via
 * to_number (numeric strings coerce; anything else makes the comparison
 * false).
 */

static re_string_t text(const char *value) { return (re_string_t){value, strlen(value)}; }
static re_value_t integer(int64_t value) { return (re_value_t){RE_VALUE_INT64, {.int64_value = value}}; }
static re_value_t real(double value) { return (re_value_t){RE_VALUE_DOUBLE, {.double_value = value}}; }
static re_value_t boolean(int value) { return (re_value_t){RE_VALUE_BOOL, {.boolean = value}}; }
static re_value_t string(const char *value) { return (re_value_t){RE_VALUE_STRING, {.string = {value, strlen(value)}}}; }

static void run_program(re_engine_t *engine, re_facts_t *facts, const char *source) {
    re_program_t *program = NULL;
    ASSERT_EQ(re_program_load(NULL, text(source), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
}

static void assert_int_fact(re_facts_t *facts, const char *name, int64_t expected) {
    re_value_t out = {RE_VALUE_NONE, {0}};
    ASSERT_EQ(re_facts_get(facts, text(name), &out), RE_STATUS_OK);
    ASSERT_EQ(out.type, RE_VALUE_INT64);
    ASSERT_EQ(out.as.int64_value, expected);
}

static void assert_no_fact(re_facts_t *facts, const char *name) {
    re_value_t out = {RE_VALUE_NONE, {0}};
    ASSERT_EQ(re_facts_get(facts, text(name), &out), RE_STATUS_NOT_FOUND);
}

static void set_object_member(re_facts_t *facts, const char *name, const char *key,
                              re_value_t member) {
    re_value_handle_t *object = NULL;
    ASSERT_EQ(re_value_create_object(facts, &object), RE_STATUS_OK);
    ASSERT_EQ(re_value_object_set(object, text(key), &member), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set_value(facts, text(name), object), RE_STATUS_OK);
    re_value_destroy(object);
}

TEST(word_alias_eq_matches_and_ne_rejects) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t a = integer(1);
    ASSERT_EQ(re_facts_set(facts, text("A"), &a), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"Eq\" { when A eq 1 then HitEq = 1; }"
        "rule \"Ne\" { when A ne 1 then HitNe = 1; }");
    assert_int_fact(facts, "HitEq", 1);
    assert_no_fact(facts, "HitNe");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(word_alias_ne_matches_on_difference) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t a = integer(2);
    ASSERT_EQ(re_facts_set(facts, text("A"), &a), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"Eq\" { when A eq 1 then HitEq = 1; }"
        "rule \"Ne\" { when A ne 1 then HitNe = 1; }");
    assert_no_fact(facts, "HitEq");
    assert_int_fact(facts, "HitNe", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(word_alias_relational_operators) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t a = integer(5);
    ASSERT_EQ(re_facts_set(facts, text("A"), &a), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"Gt\" { when A gt 5 then HitGt = 1; }"
        "rule \"Gte\" { when A gte 5 then HitGte = 1; }"
        "rule \"Lt\" { when A lt 5 then HitLt = 1; }"
        "rule \"Lte\" { when A lte 5 then HitLte = 1; }");
    assert_no_fact(facts, "HitGt");
    assert_int_fact(facts, "HitGte", 1);
    assert_no_fact(facts, "HitLt");
    assert_int_fact(facts, "HitLte", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(word_alias_gt_lt_strict_sides) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t a = integer(7);
    ASSERT_EQ(re_facts_set(facts, text("A"), &a), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"Gt\" { when A gt 5 then HitGt = 1; }"
        "rule \"Lt\" { when A lt 5 then HitLt = 1; }");
    assert_int_fact(facts, "HitGt", 1);
    assert_no_fact(facts, "HitLt");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(word_alias_not_contains) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t s = string("hello");
    ASSERT_EQ(re_facts_set(facts, text("S"), &s), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"Nc\" { when S not_contains \"x\" then HitNc = 1; }"
        "rule \"Co\" { when S contains \"ell\" then HitCo = 1; }");
    assert_int_fact(facts, "HitNc", 1);
    assert_int_fact(facts, "HitCo", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(word_alias_not_contains_rejects_substring) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t s = string("hex");
    ASSERT_EQ(re_facts_set(facts, text("S"), &s), RE_STATUS_OK);
    run_program(engine, facts, "rule \"Nc\" { when S not_contains \"x\" then HitNc = 1; }");
    assert_no_fact(facts, "HitNc");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(word_alias_starts_with_ends_with) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t s = string("hello world");
    ASSERT_EQ(re_facts_set(facts, text("S"), &s), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"Sw\" { when S starts_with \"hello\" then HitSw = 1; }"
        "rule \"Ew\" { when S ends_with \"world\" then HitEw = 1; }"
        "rule \"SwNo\" { when S starts_with \"world\" then HitSwNo = 1; }");
    assert_int_fact(facts, "HitSw", 1);
    assert_int_fact(facts, "HitEw", 1);
    assert_no_fact(facts, "HitSwNo");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(bool_literals_are_case_insensitive) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t on = boolean(1);
    re_value_t off = boolean(0);
    ASSERT_EQ(re_facts_set(facts, text("On"), &on), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("Off"), &off), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"T\" { when On == TRUE then HitT = 1; }"
        "rule \"F\" { when On == False then HitF = 1; }"
        "rule \"F2\" { when Off == False then HitF2 = 1; }"
        "rule \"Bare\" { when TRUE then HitBare = 1; }");
    assert_int_fact(facts, "HitT", 1);
    assert_no_fact(facts, "HitF");
    assert_int_fact(facts, "HitF2", 1);
    assert_int_fact(facts, "HitBare", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(null_literal_is_case_insensitive_and_compares_strictly) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t s = string("x");
    ASSERT_EQ(re_facts_set(facts, text("S"), &s), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"Eq\" { when null == NULL then HitNullEq = 1; }"
        "rule \"SEq\" { when S == NULL then HitSEq = 1; }"
        "rule \"SNe\" { when S != null then HitSNe = 1; }");
    assert_int_fact(facts, "HitNullEq", 1);
    assert_no_fact(facts, "HitSEq");
    assert_int_fact(facts, "HitSNe", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(modulo_condition_and_result_typing) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t n = integer(9);
    re_value_t d = real(7.5);
    re_value_t out = {RE_VALUE_NONE, {0}};
    ASSERT_EQ(re_facts_set(facts, text("N"), &n), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("D"), &d), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"Mod\" { when N % 3 == 0 then HitMod = 1; }"
        "rule \"Int\" { when true then R = N % 4; }"
        "rule \"Real\" { when true then Q = D % 2; }");
    assert_int_fact(facts, "HitMod", 1);
    /* Both operands Integer and fmod result integral -> Integer result. */
    assert_int_fact(facts, "R", 1);
    /* One operand Number -> Number result (7.5 % 2 = 1.5). */
    ASSERT_EQ(re_facts_get(facts, text("Q"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.type, RE_VALUE_DOUBLE);
    ASSERT_FLOAT_EQ(out.as.double_value, 1.5, 1e-9);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(modulo_non_match) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t n = integer(10);
    ASSERT_EQ(re_facts_set(facts, text("N"), &n), RE_STATUS_OK);
    run_program(engine, facts, "rule \"Mod\" { when N % 3 == 0 then HitMod = 1; }");
    assert_no_fact(facts, "HitMod");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(modulo_by_literal_zero_fails_parse_like_division) {
    re_program_t *program = NULL;
    ASSERT_EQ(re_program_load(NULL, text("rule \"Z\" { when N % 0 == 0 then R = 1; }"), NULL, &program),
              RE_STATUS_ERROR);
}

TEST(modulo_by_zero_fact_errors_the_run) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_value_t n = integer(10);
    re_value_t z = integer(0);
    ASSERT_EQ(re_facts_set(facts, text("N"), &n), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("Z"), &z), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text("rule \"M\" { when N % Z == 0 then R = 1; }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_ERROR);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(string_concat_in_action_rhs) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t out = {RE_VALUE_NONE, {0}};
    run_program(engine, facts,
        "rule \"C\" { when true then G = \"Hello, \" + \"World\"; }"
        "rule \"Chain\" { when true then H = \"a\" + \"b\" + \"c\"; }");
    ASSERT_EQ(re_facts_get(facts, text("G"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.type, RE_VALUE_STRING);
    ASSERT_TRUE(out.as.string.size == 12u && memcmp(out.as.string.data, "Hello, World", 12u) == 0);
    ASSERT_EQ(re_facts_get(facts, text("H"), &out), RE_STATUS_OK);
    ASSERT_TRUE(out.as.string.size == 3u && memcmp(out.as.string.data, "abc", 3u) == 0);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(string_concat_uses_fact_values) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t prefix = string("hi");
    re_value_t out = {RE_VALUE_NONE, {0}};
    ASSERT_EQ(re_facts_set(facts, text("Prefix"), &prefix), RE_STATUS_OK);
    run_program(engine, facts, "rule \"C\" { when true then G = Prefix + \"!\"; }");
    ASSERT_EQ(re_facts_get(facts, text("G"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.type, RE_VALUE_STRING);
    ASSERT_TRUE(out.as.string.size == 3u && memcmp(out.as.string.data, "hi!", 3u) == 0);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(string_concat_in_condition) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    run_program(engine, facts,
        "rule \"C\" { when \"a\" + \"b\" == \"ab\" then Hit = 1; }"
        "rule \"CNo\" { when \"a\" + \"b\" == \"ac\" then HitNo = 1; }");
    assert_int_fact(facts, "Hit", 1);
    assert_no_fact(facts, "HitNo");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(string_concat_with_non_string_errors_the_run) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    ASSERT_EQ(re_program_load(NULL, text("rule \"Bad\" { when true then R = \"a\" + 5; }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_INVALID_ARGUMENT);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(equality_has_no_numeric_cross_coercion) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t d = real(1.0);
    re_value_t i = integer(1);
    ASSERT_EQ(re_facts_set(facts, text("D"), &d), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("I"), &i), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"MixEq\" { when D == 1 then HitMixEq = 1; }"
        "rule \"MixEq2\" { when I == 1.0 then HitMixEq2 = 1; }"
        "rule \"MixNe\" { when D != 1 then HitMixNe = 1; }"
        "rule \"SameEq\" { when D == 1.0 then HitSameEq = 1; }"
        "rule \"SameEq2\" { when I == 1 then HitSameEq2 = 1; }");
    /* D4: Integer(1) == Number(1.0) is FALSE upstream (strict PartialEq). */
    assert_no_fact(facts, "HitMixEq");
    assert_no_fact(facts, "HitMixEq2");
    assert_int_fact(facts, "HitMixNe", 1);
    assert_int_fact(facts, "HitSameEq", 1);
    assert_int_fact(facts, "HitSameEq2", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(relational_operators_coerce_numeric_strings) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t s = string("42");
    re_value_t d = real(1.5);
    ASSERT_EQ(re_facts_set(facts, text("S"), &s), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("D"), &d), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"Gt\" { when S > 5 then HitGt = 1; }"
        "rule \"Lt\" { when S < 100 then HitLt = 1; }"
        "rule \"Ge\" { when S >= 42.0 then HitGe = 1; }"
        "rule \"Mix\" { when D > 1 then HitMix = 1; }");
    /* D4: relational ops coerce via to_number, so "42" > 5 is TRUE. */
    assert_int_fact(facts, "HitGt", 1);
    assert_int_fact(facts, "HitLt", 1);
    assert_int_fact(facts, "HitGe", 1);
    assert_int_fact(facts, "HitMix", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(relational_operators_reject_non_numeric_strings) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t s = string("abc");
    ASSERT_EQ(re_facts_set(facts, text("S"), &s), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"Gt\" { when S > 5 then HitGt = 1; }"
        "rule \"Le\" { when S <= 5 then HitLe = 1; }");
    /* D4: "abc" > 5 is FALSE (to_number fails), and so is every other
     * relational operator against it. */
    assert_no_fact(facts, "HitGt");
    assert_no_fact(facts, "HitLe");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(word_alias_not_contains_non_string_operands_are_true) {
    /* A1 lock: the string operators require two strings; against anything
     * else contains is false and not_contains - the logical negation - is
     * true (re_value_compare). */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t n = integer(5);
    re_value_t s = string("hello");
    ASSERT_EQ(re_facts_set(facts, text("N"), &n), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("S"), &s), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"Ln\" { when N not_contains \"x\" then HitLn = 1; }"
        "rule \"Rn\" { when S not_contains 5 then HitRn = 1; }"
        "rule \"Co\" { when N contains \"x\" then HitCo = 1; }");
    assert_int_fact(facts, "HitLn", 1);
    assert_int_fact(facts, "HitRn", 1);
    assert_no_fact(facts, "HitCo");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(relational_operators_reject_bool_and_null_operands) {
    /* A1 lock (D4): relational coercion runs through to_number - bool and
     * null operands never coerce, so every relational comparison against
     * them is false (never an error, never true). A LEADING true/false
     * literal stays the whole-condition literal form (parser special case),
     * so the bool side is locked through a fact and through RHS literals. */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t b = boolean(1);
    re_value_t n = integer(5);
    ASSERT_EQ(re_facts_set(facts, text("B"), &b), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("N"), &n), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"BoolL\" { when B > 1 then HitBoolL = 1; }"
        "rule \"BoolR\" { when N > true then HitBoolR = 1; }"
        "rule \"NullL\" { when null > 1 then HitNullL = 1; }"
        "rule \"NullR\" { when N > null then HitNullR = 1; }"
        "rule \"NullLe\" { when null <= 1 then HitNullLe = 1; }");
    assert_no_fact(facts, "HitBoolL");
    assert_no_fact(facts, "HitBoolR");
    assert_no_fact(facts, "HitNullL");
    assert_no_fact(facts, "HitNullR");
    assert_no_fact(facts, "HitNullLe");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

/* Task A2: full `!( <expr> )`, `exists( <expr> )`, `forall( <expr> )` where the
 * inner is any boolean expression. Quantifier candidate selection follows D7:
 * the target type is the text before the first `.` of the leftmost field
 * reference in the inner expression; candidates are all active facts whose
 * name equals or starts with that prefix; the inner is evaluated per candidate
 * with the prefix rebound to the candidate. Empty candidate set: exists is
 * false, forall is vacuously true (D6). With no dotted field reference the
 * inner is evaluated once against the plain fact store (upstream fallback). */

TEST(not_paren_negates_condition) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t a = integer(1);
    re_value_t b = integer(5);
    ASSERT_EQ(re_facts_set(facts, text("A"), &a), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("B"), &b), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"NotHit\" { when !(A == 1) then HitNot = 1; }"
        "rule \"NotMiss\" { when !(A == 2) then HitNot2 = 1; }"
        "rule \"Combo\" { when !(A == 2) and B == 5 then HitCombo = 1; }"
        "rule \"Nested\" { when !(A == 1 or B == 5) then HitNested = 1; }"
        "rule \"Keyword\" { when not (A == 1) then HitKeyword = 1; }");
    assert_no_fact(facts, "HitNot");
    assert_int_fact(facts, "HitNot2", 1);
    assert_int_fact(facts, "HitCombo", 1);
    assert_no_fact(facts, "HitNested");
    assert_no_fact(facts, "HitKeyword");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(not_paren_does_not_swallow_not_equal) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t a = integer(1);
    ASSERT_EQ(re_facts_set(facts, text("A"), &a), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"Ne\" { when A != 2 then HitNe = 1; }"
        "rule \"NotNe\" { when !(A != 2) then HitNotNe = 1; }");
    assert_int_fact(facts, "HitNe", 1);
    assert_no_fact(facts, "HitNotNe");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(exists_paren_rebinds_prefix_over_candidates) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    set_object_member(facts, "Score1", "value", integer(40));
    set_object_member(facts, "Score2", "value", integer(95));
    run_program(engine, facts,
        "rule \"Any\" { when exists(Score.value > 90) then HitAny = 1; }");
    assert_int_fact(facts, "HitAny", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(exists_paren_without_matching_candidate_does_not_fire) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    set_object_member(facts, "Score1", "value", integer(40));
    set_object_member(facts, "Score2", "value", integer(50));
    run_program(engine, facts,
        "rule \"Any\" { when exists(Score.value > 90) then HitAny = 1; }"
        "rule \"None\" { when exists(Missing.value > 1) then HitNone = 1; }");
    assert_no_fact(facts, "HitAny");
    assert_no_fact(facts, "HitNone");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(exists_paren_evaluates_compound_inner_per_candidate) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_handle_t *score = NULL;
    re_value_t member = integer(95);
    /* Score1 passes the threshold but lacks the flag; Score2 passes both. */
    ASSERT_EQ(re_value_create_object(facts, &score), RE_STATUS_OK);
    ASSERT_EQ(re_value_object_set(score, text("value"), &member), RE_STATUS_OK);
    member = boolean(0);
    ASSERT_EQ(re_value_object_set(score, text("bonus"), &member), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set_value(facts, text("Score1"), score), RE_STATUS_OK);
    re_value_destroy(score); score = NULL;
    member = integer(95);
    ASSERT_EQ(re_value_create_object(facts, &score), RE_STATUS_OK);
    ASSERT_EQ(re_value_object_set(score, text("value"), &member), RE_STATUS_OK);
    member = boolean(1);
    ASSERT_EQ(re_value_object_set(score, text("bonus"), &member), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set_value(facts, text("Score2"), score), RE_STATUS_OK);
    re_value_destroy(score);
    run_program(engine, facts,
        "rule \"Both\" { when exists(Score.value > 90 and Score.bonus == true) then HitBoth = 1; }"
        "rule \"Either\" { when exists(Score.value > 90 or Score.bonus == true) then HitEither = 1; }");
    assert_int_fact(facts, "HitBoth", 1);
    assert_int_fact(facts, "HitEither", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(exists_paren_plain_store_fallback_without_dotted_reference) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t a = integer(1);
    re_value_t b = integer(2);
    ASSERT_EQ(re_facts_set(facts, text("A"), &a), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("B"), &b), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"And\" { when exists(A == 1 and B == 2) then HitAnd = 1; }"
        "rule \"AndNo\" { when exists(A == 1 and B == 3) then HitAndNo = 1; }");
    assert_int_fact(facts, "HitAnd", 1);
    assert_no_fact(facts, "HitAndNo");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(forall_paren_requires_every_candidate) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    set_object_member(facts, "Alert1", "level", string("low"));
    set_object_member(facts, "Alert2", "level", string("low"));
    run_program(engine, facts,
        "rule \"AllLow\" { when forall(Alert.level == \"low\") then HitAllLow = 1; }");
    assert_int_fact(facts, "HitAllLow", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(forall_paren_fails_on_one_bad_candidate) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    set_object_member(facts, "Alert1", "level", string("low"));
    set_object_member(facts, "Alert2", "level", string("high"));
    run_program(engine, facts,
        "rule \"AllLow\" { when forall(Alert.level == \"low\") then HitAllLow = 1; }");
    assert_no_fact(facts, "HitAllLow");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(forall_paren_empty_candidate_set_is_vacuously_true) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    run_program(engine, facts,
        "rule \"Vacuous\" { when forall(Alert.level == \"low\") then HitVacuous = 1; }"
        "rule \"VacuousNot\" { when !(forall(Alert.level == \"low\")) then HitVacuousNot = 1; }");
    assert_int_fact(facts, "HitVacuous", 1);
    assert_no_fact(facts, "HitVacuousNot");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(not_exists_paren_nested_negation) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    set_object_member(facts, "Score1", "value", integer(40));
    run_program(engine, facts,
        "rule \"NoHigh\" { when !exists(Score.value > 90) then HitNoHigh = 1; }"
        "rule \"HasHigh\" { when exists(Score.value > 90) then HitHasHigh = 1; }");
    assert_int_fact(facts, "HitNoHigh", 1);
    assert_no_fact(facts, "HitHasHigh");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(quantifier_paren_forms_compose_with_and_or) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t ready = boolean(1);
    set_object_member(facts, "Score1", "value", integer(95));
    set_object_member(facts, "Alert1", "level", string("low"));
    ASSERT_EQ(re_facts_set(facts, text("Ready"), &ready), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"Mix\" { when exists(Score.value > 90) and forall(Alert.level == \"low\") and Ready == true then HitMix = 1; }"
        "rule \"OrMix\" { when exists(Score.value > 900) or forall(Alert.level == \"low\") then HitOrMix = 1; }");
    assert_int_fact(facts, "HitMix", 1);
    assert_int_fact(facts, "HitOrMix", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(quantifier_paren_rejects_empty_inner) {
    re_program_t *program = NULL;
    ASSERT_EQ(re_program_load(NULL, text("rule \"Bad\" { when exists() then R = 1; }"), NULL, &program),
              RE_STATUS_PARSE_ERROR);
    ASSERT_EQ(re_program_load(NULL, text("rule \"Bad\" { when !(A == 1 then R = 1; }"), NULL, &program),
              RE_STATUS_PARSE_ERROR);
}

/* I2: a non-conforming lookalike candidate (prefix "Score" also matches
 * "Scoreboard") scores false for that candidate instead of aborting the
 * rule's evaluation. Scoreboard is inserted first so the scan hits it before
 * the conforming Score2. */
TEST(exists_paren_skips_nonconforming_lookalike_candidate) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    set_object_member(facts, "Scoreboard", "name", string("board"));
    set_object_member(facts, "Score2", "value", integer(95));
    run_program(engine, facts,
        "rule \"Any\" { when exists(Score.value > 90) then HitAny = 1; }");
    assert_int_fact(facts, "HitAny", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

/* I2: forall must NOT fire when a candidate fails outright (missing member),
 * not just when it compares false. */
TEST(forall_paren_nonconforming_candidate_fails) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    set_object_member(facts, "Alert1", "level", string("low"));
    set_object_member(facts, "Alert2", "note", string("no level member"));
    run_program(engine, facts,
        "rule \"AllLow\" { when forall(Alert.level == \"low\") then HitAllLow = 1; }");
    assert_no_fact(facts, "HitAllLow");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

/* I2: only a candidate's failed fact read absorbs into candidate-false; a
 * genuinely broken inner (an unknown function also reports NOT_FOUND) must
 * propagate out of the quantifier. Propagation skips the whole rule — so the
 * matching OR-branch must NOT fire. */
TEST(exists_paren_unknown_function_still_errors) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_value_t fallback = boolean(1);
    set_object_member(facts, "Score1", "value", integer(95));
    ASSERT_EQ(re_facts_set(facts, text("Fallback"), &fallback), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text("rule \"Bad\" { when exists(Score.value > missing_fn()) or Fallback == true then R = 1; }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    /* The engine maps a condition's NOT_FOUND to a skipped rule; the run
     * itself succeeds. */
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    assert_no_fact(facts, "R");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

/* M1: the operator-stack grow used to restart the parse loop after growth,
 * dropping the just-consumed token; with 16 pending operators (the initial
 * capacity) the 17th negation was silently lost, flipping parity. Odd stacks
 * must negate, even stacks must not, deep parens must survive. */
TEST(operator_stack_growth_keeps_stacked_prefixes) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t a = integer(1);
    char source[768];
    size_t at;
    int i;
    ASSERT_EQ(re_facts_set(facts, text("A"), &a), RE_STATUS_OK);
    strcpy(source, "rule \"Odd\" { when ");
    at = strlen(source);
    for (i = 0; i < 17; ++i) source[at++] = '!';
    strcpy(source + at, "(A == 1) then HitOdd = 1; }");
    strcat(source, "rule \"Even\" { when ");
    at = strlen(source);
    for (i = 0; i < 18; ++i) { strcpy(source + at, "not "); at += 4u; }
    strcpy(source + at, "A == 1 then HitEven = 1; }");
    strcat(source, "rule \"Paren\" { when ");
    at = strlen(source);
    for (i = 0; i < 17; ++i) source[at++] = '(';
    strcpy(source + at, "A == 1");
    at = strlen(source);
    for (i = 0; i < 17; ++i) source[at++] = ')';
    strcpy(source + at, " then HitParen = 1; }");
    run_program(engine, facts, source);
    assert_no_fact(facts, "HitOdd");
    assert_int_fact(facts, "HitEven", 1);
    assert_int_fact(facts, "HitParen", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

/* Task A3: engine built-in functions in `when` conditions (and action RHS),
 * matching upstream condition_evaluator.rs (rust-rule-engine f80a541):
 * len/length/size (String byte length, Array element count, any other type
 * makes the condition false), isEmpty/is_empty (String/Array empty, Null ->
 * true, else false), contains(x, y) (substring, or array membership by typed
 * equality), exists/notExists/not_exists (fact-path presence). Built-ins are
 * consulted only after the user function registry misses, so a registered
 * function of the same name wins. A bare predicate built-in used as a whole
 * condition means fn(...) == true; exists(...) keeps its quantifier meaning
 * whenever the paren content carries a top-level comparison/logical operator.
 * A built-in argument that fails to resolve (absent fact) makes the built-in
 * yield false (true for the negated probes) instead of skipping the rule. */

static void set_array_fact(re_facts_t *facts, const char *name, const re_value_t *items, size_t count) {
    re_value_handle_t *array = NULL;
    size_t i;
    ASSERT_EQ(re_value_create_array(facts, &array), RE_STATUS_OK);
    for (i = 0u; i < count; ++i) ASSERT_EQ(re_value_array_append(array, &items[i]), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set_value(facts, text(name), array), RE_STATUS_OK);
    re_value_destroy(array);
}

static void assert_bool_fact(re_facts_t *facts, const char *name, int expected) {
    re_value_t out = {RE_VALUE_NONE, {0}};
    ASSERT_EQ(re_facts_get(facts, text(name), &out), RE_STATUS_OK);
    ASSERT_EQ(out.type, RE_VALUE_BOOL);
    ASSERT_EQ(out.as.boolean, expected);
}

static void assert_string_fact(re_facts_t *facts, const char *name, const char *expected) {
    re_value_t out = {RE_VALUE_NONE, {0}};
    ASSERT_EQ(re_facts_get(facts, text(name), &out), RE_STATUS_OK);
    ASSERT_EQ(out.type, RE_VALUE_STRING);
    ASSERT_EQ(out.as.string.size, strlen(expected));
    ASSERT_TRUE(memcmp(out.as.string.data, expected, out.as.string.size) == 0);
}

static void assert_double_fact(re_facts_t *facts, const char *name, double expected) {
    re_value_t out = {RE_VALUE_NONE, {0}};
    ASSERT_EQ(re_facts_get(facts, text(name), &out), RE_STATUS_OK);
    ASSERT_EQ(out.type, RE_VALUE_DOUBLE);
    ASSERT_TRUE(out.as.double_value == expected);
}

TEST(builtin_len_string_member_comparison_and_aliases) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    set_object_member(facts, "S", "name", string("John"));
    run_program(engine, facts,
        "rule \"Len\" { when len(S.name) > 3 then HitLen = 1; }"
        "rule \"LenNo\" { when len(S.name) > 4 then HitLenNo = 1; }"
        "rule \"LenEq\" { when length(S.name) == 4 then HitLenEq = 1; }"
        "rule \"Size\" { when size(S.name) == 4 then HitSize = 1; }");
    assert_int_fact(facts, "HitLen", 1);
    assert_no_fact(facts, "HitLenNo");
    /* len yields INT64, so strictly-typed D4 equality with an int literal
     * holds (upstream returns Number; len(x) == 4.0 would be false here). */
    assert_int_fact(facts, "HitLenEq", 1);
    assert_int_fact(facts, "HitSize", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(builtin_len_counts_array_fact_elements) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t items[3];
    items[0] = integer(7); items[1] = integer(8); items[2] = integer(9);
    set_array_fact(facts, "Arr", items, 3u);
    run_program(engine, facts,
        "rule \"ArrLen\" { when len(Arr) == 3 then HitArrLen = 1; }"
        "rule \"ArrLenNo\" { when len(Arr) == 4 then HitArrLenNo = 1; }");
    assert_int_fact(facts, "HitArrLen", 1);
    assert_no_fact(facts, "HitArrLenNo");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(builtin_len_wrong_type_and_arity_are_false) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t n = integer(5);
    ASSERT_EQ(re_facts_set(facts, text("N"), &n), RE_STATUS_OK);
    set_object_member(facts, "Obj", "x", integer(1));
    run_program(engine, facts,
        "rule \"NumLen\" { when len(N) > 0 then HitNumLen = 1; }"
        "rule \"ObjLen\" { when len(Obj) > 0 then HitObjLen = 1; }"
        "rule \"TwoArgs\" { when len(N, N) > 0 then HitTwoArgs = 1; }");
    /* Numbers, structured objects and wrong arity are all condition-false
     * (upstream: String/Array only, else Ok(false)) - never a run error. */
    assert_no_fact(facts, "HitNumLen");
    assert_no_fact(facts, "HitObjLen");
    assert_no_fact(facts, "HitTwoArgs");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(builtin_is_empty_string_null_and_array) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t empty = string("");
    re_value_t non_empty = string("x");
    re_value_t null_value = {RE_VALUE_NULL, {0}};
    re_value_t n = integer(5);
    re_value_t items[2];
    items[0] = integer(1); items[1] = integer(2);
    ASSERT_EQ(re_facts_set(facts, text("E"), &empty), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("S"), &non_empty), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("Nul"), &null_value), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("N"), &n), RE_STATUS_OK);
    set_array_fact(facts, "EmptyArr", items, 0u);
    set_array_fact(facts, "Arr", items, 2u);
    run_program(engine, facts,
        "rule \"EmptyStr\" { when isEmpty(E) then HitEmptyStr = 1; }"
        "rule \"NonEmpty\" { when isEmpty(S) then HitNonEmpty = 1; }"
        "rule \"Null\" { when is_empty(Nul) then HitNull = 1; }"
        "rule \"EmptyArr\" { when isEmpty(EmptyArr) then HitEmptyArr = 1; }"
        "rule \"Arr\" { when isEmpty(Arr) then HitArr = 1; }"
        "rule \"Num\" { when isEmpty(N) then HitNum = 1; }"
        "rule \"Neg\" { when isEmpty(S) == false then HitNeg = 1; }");
    assert_int_fact(facts, "HitEmptyStr", 1);
    assert_no_fact(facts, "HitNonEmpty");
    assert_int_fact(facts, "HitNull", 1);
    assert_int_fact(facts, "HitEmptyArr", 1);
    assert_no_fact(facts, "HitArr");
    assert_no_fact(facts, "HitNum");
    assert_int_fact(facts, "HitNeg", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(builtin_arg_resolution_failure_is_false_not_skip) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t a = integer(1);
    ASSERT_EQ(re_facts_set(facts, text("A"), &a), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"Miss\" { when isEmpty(Missing) == true then HitMiss = 1; }"
        "rule \"MissFalse\" { when isEmpty(Missing) == false then HitMissFalse = 1; }"
        "rule \"LenMiss\" { when len(Missing) > 0 then HitLenMiss = 1; }"
        "rule \"Or\" { when len(Missing) > 0 or A == 1 then HitOr = 1; }");
    assert_no_fact(facts, "HitMiss");
    /* The absorbed miss yields a real false value, so == false matches... */
    assert_int_fact(facts, "HitMissFalse", 1);
    assert_no_fact(facts, "HitLenMiss");
    /* ...and the rule is NOT skipped: the sibling OR branch still evaluates
     * (a skip would suppress HitOr even though A == 1 holds). */
    assert_int_fact(facts, "HitOr", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(builtin_contains_string_substring_and_array_membership) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t items[3];
    items[0] = integer(7); items[1] = integer(8); items[2] = integer(9);
    set_object_member(facts, "S", "name", string("John"));
    set_array_fact(facts, "Arr", items, 3u);
    run_program(engine, facts,
        "rule \"Sub\" { when contains(S.name, \"oh\") then HitSub = 1; }"
        "rule \"SubNo\" { when contains(S.name, \"xy\") then HitSubNo = 1; }"
        "rule \"ArrHas\" { when contains(Arr, 8) == true then HitArrHas = 1; }"
        "rule \"ArrNo\" { when contains(Arr, 10) == true then HitArrNo = 1; }"
        "rule \"ArrType\" { when contains(Arr, 8.0) == true then HitArrType = 1; }"
        "rule \"StrType\" { when contains(S.name, 1) == true then HitStrType = 1; }"
        "rule \"OneArg\" { when contains(S.name) == true then HitOneArg = 1; }");
    assert_int_fact(facts, "HitSub", 1);
    assert_no_fact(facts, "HitSubNo");
    assert_int_fact(facts, "HitArrHas", 1);
    assert_no_fact(facts, "HitArrNo");
    /* Array membership is typed equality: Integer(8) != Number(8.0). */
    assert_no_fact(facts, "HitArrType");
    /* (String, Integer) is a type mismatch -> false; wrong arity -> false. */
    assert_no_fact(facts, "HitStrType");
    assert_no_fact(facts, "HitOneArg");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(builtin_exists_not_exists_quoted_paths) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_handle_t *a = NULL;
    re_value_handle_t *items = NULL;
    re_value_t member = integer(5);
    re_value_t elem = integer(1);
    re_value_t plain = integer(1);
    ASSERT_EQ(re_value_create_object(facts, &a), RE_STATUS_OK);
    ASSERT_EQ(re_value_object_set(a, text("b"), &member), RE_STATUS_OK);
    ASSERT_EQ(re_value_create_array(facts, &items), RE_STATUS_OK);
    ASSERT_EQ(re_value_array_append(items, &elem), RE_STATUS_OK);
    ASSERT_EQ(re_value_object_set_value(a, text("items"), items), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set_value(facts, text("A"), a), RE_STATUS_OK);
    re_value_destroy(items);
    re_value_destroy(a);
    ASSERT_EQ(re_facts_set(facts, text("Plain"), &plain), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"Ex\" { when exists(\"A.b\") then HitEx = 1; }"
        "rule \"ExArr\" { when exists(\"A.items\") then HitExArr = 1; }"
        "rule \"ExMiss\" { when exists(\"A.missing\") then HitExMiss = 1; }"
        "rule \"NotEx\" { when notExists(\"A.missing\") then HitNotEx = 1; }"
        "rule \"NotEx2\" { when not_exists(\"A.b\") then HitNotEx2 = 1; }"
        "rule \"ExFlat\" { when exists(\"Plain\") == true then HitExFlat = 1; }"
        "rule \"ExFlatMiss\" { when exists(\"Nope\") == false then HitExFlatMiss = 1; }");
    assert_int_fact(facts, "HitEx", 1);
    /* Array members count as present (structured-path probe). */
    assert_int_fact(facts, "HitExArr", 1);
    assert_no_fact(facts, "HitExMiss");
    assert_int_fact(facts, "HitNotEx", 1);
    assert_no_fact(facts, "HitNotEx2");
    assert_int_fact(facts, "HitExFlat", 1);
    assert_int_fact(facts, "HitExFlatMiss", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(builtin_exists_bare_path_form_and_negation) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    /* The member value is 0 on purpose: presence, not truthiness. */
    set_object_member(facts, "A", "b", integer(0));
    run_program(engine, facts,
        "rule \"BareEx\" { when exists(A.b) then HitBareEx = 1; }"
        "rule \"BareMiss\" { when exists(A.nope) then HitBareMiss = 1; }"
        "rule \"BareNotMiss\" { when notExists(A.nope) then HitBareNotMiss = 1; }"
        "rule \"BareNotPresent\" { when notExists(A.b) then HitBareNotPresent = 1; }");
    assert_int_fact(facts, "HitBareEx", 1);
    assert_no_fact(facts, "HitBareMiss");
    /* A missing bare path makes the negated probe true, not a skipped rule. */
    assert_int_fact(facts, "HitBareNotMiss", 1);
    assert_no_fact(facts, "HitBareNotPresent");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(exists_quantifier_vs_function_form_coexist) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    set_object_member(facts, "Score1", "value", integer(95));
    run_program(engine, facts,
        "rule \"Quant\" { when exists(Score.value > 90) then HitQuant = 1; }"
        "rule \"QuantNo\" { when exists(Score.value > 900) then HitQuantNo = 1; }"
        "rule \"Fn\" { when exists(\"Score1.value\") == true then HitFn = 1; }"
        "rule \"FnNo\" { when exists(\"Score2.value\") == true then HitFnNo = 1; }");
    /* Top-level comparison inside the parens -> quantifier (A2 behavior). */
    assert_int_fact(facts, "HitQuant", 1);
    assert_no_fact(facts, "HitQuantNo");
    /* A lone operand inside the parens -> field-presence function. */
    assert_int_fact(facts, "HitFn", 1);
    assert_no_fact(facts, "HitFnNo");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

static re_status_t override_len_call(re_engine_t *engine, re_facts_t *facts,
                                     const re_value_t *arguments, size_t argument_count,
                                     re_value_t *out_value, void *context) {
    (void)engine; (void)facts; (void)arguments; (void)argument_count; (void)context;
    out_value->type = RE_VALUE_INT64;
    out_value->as.int64_value = 100;
    return RE_STATUS_OK;
}
static re_status_t override_exists_call(re_engine_t *engine, re_facts_t *facts,
                                        const re_value_t *arguments, size_t argument_count,
                                        re_value_t *out_value, void *context) {
    (void)engine; (void)facts; (void)arguments; (void)argument_count; (void)context;
    out_value->type = RE_VALUE_BOOL;
    out_value->as.boolean = 0;
    return RE_STATUS_OK;
}

TEST(builtin_user_registered_function_overrides) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_function_t *len_fn = NULL;
    re_function_t *exists_fn = NULL;
    re_function_descriptor_t len_descriptor = {sizeof(len_descriptor), RE_ABI_VERSION_MAJOR,
        {"len", 3u}, override_len_call, NULL, NULL};
    re_function_descriptor_t exists_descriptor = {sizeof(exists_descriptor), RE_ABI_VERSION_MAJOR,
        {"exists", 6u}, override_exists_call, NULL, NULL};
    set_object_member(facts, "A", "b", integer(5));
    ASSERT_EQ(re_engine_register_function(engine, &len_descriptor, &len_fn), RE_STATUS_OK);
    ASSERT_EQ(re_engine_register_function(engine, &exists_descriptor, &exists_fn), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"Ov\" { when len(A.b) > 50 then HitOv = 1; }"
        "rule \"Ov2\" { when length(A.b) > 50 then HitOv2 = 1; }"
        "rule \"Ov3\" { when exists(\"A.b\") then HitOv3 = 1; }");
    /* The registered len wins over the built-in (100 > 50 fires; the
     * built-in len would be false on a number anyway) ... */
    assert_int_fact(facts, "HitOv", 1);
    /* ... while length is untouched and falls back to the built-in: a
     * numeric argument is condition-false. */
    assert_no_fact(facts, "HitOv2");
    /* The registered exists wins too: it returns false for a present path
     * the built-in would report as existing. */
    assert_no_fact(facts, "HitOv3");
    re_function_unregister(exists_fn);
    re_function_unregister(len_fn);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(builtin_functions_in_action_rhs) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    set_object_member(facts, "S", "name", string("John"));
    run_program(engine, facts,
        "rule \"Rhs\" { when true then L = len(S.name); E = exists(\"S.name\"); M = exists(\"S.nope\"); }");
    assert_int_fact(facts, "L", 4);
    assert_bool_fact(facts, "E", 1);
    assert_bool_fact(facts, "M", 0);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(unknown_function_still_skips_the_rule) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t a = integer(1);
    ASSERT_EQ(re_facts_set(facts, text("A"), &a), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"Unk\" { when missing_fn() == 1 or A == 1 then HitUnk = 1; }"
        "rule \"Known\" { when A == 1 then HitKnown = 1; }");
    /* Unknown functions are unchanged: NOT_FOUND skips the whole rule (the
     * OR sibling does not save it) - only built-ins absorb arg misses. */
    assert_no_fact(facts, "HitUnk");
    assert_int_fact(facts, "HitKnown", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

/*
 * Task A4: action/RHS utility built-ins (upstream engine.rs L1411
 * execute_function_call). Everything below is also callable in conditions
 * (the functions are semantically pure, except random/log whose purity the
 * caller controls). That purity is semantic only: re_condition_is_pure
 * classifies EVERY function-call condition as impure and parallel matching
 * is disabled for such rules - do not "optimize" the classification for
 * these built-ins, or random()/log() in a condition becomes a data race.
 * Where upstream's table is stringly typed, the local built-ins
 * return typed values (INT64-preserving folds per the Task 12 accumulator
 * rule); divergences are documented in builtins.c.
 */

TEST(builtin_log_returns_joined_message) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    /* log/print/println also write the message to stdout (the engine has no
     * log callback); the fact assertions pin the returned string. */
    run_program(engine, facts,
        "rule \"L\" { when true then M = log(\"a\", 1, true); P = print(\"x\"); N = println(); E = log(); }");
    assert_string_fact(facts, "M", "a 1 true");
    assert_string_fact(facts, "P", "x");
    assert_string_fact(facts, "N", "");
    assert_string_fact(facts, "E", "");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(builtin_now_timestamp_return_unix_seconds_string) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t out = {RE_VALUE_NONE, {0}};
    long long stamp;
    run_program(engine, facts,
        "rule \"T\" { when true then A = now(); B = timestamp(); }");
    ASSERT_EQ(re_facts_get(facts, text("A"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.type, RE_VALUE_STRING);
    stamp = strtoll(out.as.string.data, NULL, 10);
    /* Sanity window: after 2023-11-14, before 2100-01-01. */
    ASSERT_TRUE(stamp > 1700000000ll);
    ASSERT_TRUE(stamp < 4102444800ll);
    ASSERT_EQ(re_facts_get(facts, text("B"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.type, RE_VALUE_STRING);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(builtin_random_is_deterministic_per_engine_and_bounded) {
    const char *source =
        "rule \"R\" { when true then R1 = random(); R2 = random(); R3 = random(7); }";
    re_engine_t *engine_one = re_engine_create(NULL, NULL);
    re_engine_t *engine_two = re_engine_create(NULL, NULL);
    re_facts_t *facts_one = re_facts_create(NULL, NULL);
    re_facts_t *facts_two = re_facts_create(NULL, NULL);
    re_value_t one = {RE_VALUE_NONE, {0}};
    re_value_t two = {RE_VALUE_NONE, {0}};
    run_program(engine_one, facts_one, source);
    run_program(engine_two, facts_two, source);
    /* Two engines start from the same fixed seed, so they produce the same
     * sequence; the values are bounded by the modulus. */
    ASSERT_EQ(re_facts_get(facts_one, text("R1"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts_two, text("R2"), &two), RE_STATUS_OK);
    ASSERT_EQ(one.type, RE_VALUE_INT64);
    ASSERT_EQ(two.type, RE_VALUE_INT64);
    ASSERT_TRUE(one.as.int64_value >= 0 && one.as.int64_value < 100);
    ASSERT_TRUE(two.as.int64_value >= 0 && two.as.int64_value < 100);
    ASSERT_NEQ(one.as.int64_value, two.as.int64_value);
    ASSERT_EQ(re_facts_get(facts_one, text("R3"), &one), RE_STATUS_OK);
    ASSERT_EQ(one.type, RE_VALUE_INT64);
    ASSERT_TRUE(one.as.int64_value >= 0 && one.as.int64_value < 7);
    /* Same sequence from a fresh engine, element by element. */
    ASSERT_EQ(re_facts_get(facts_one, text("R1"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts_two, text("R1"), &two), RE_STATUS_OK);
    ASSERT_EQ(one.as.int64_value, two.as.int64_value);
    ASSERT_EQ(re_facts_get(facts_one, text("R2"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts_two, text("R2"), &two), RE_STATUS_OK);
    ASSERT_EQ(one.as.int64_value, two.as.int64_value);
    ASSERT_EQ(re_facts_get(facts_one, text("R3"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts_two, text("R3"), &two), RE_STATUS_OK);
    ASSERT_EQ(one.as.int64_value, two.as.int64_value);
    re_facts_destroy(facts_two);
    re_facts_destroy(facts_one);
    re_engine_destroy(engine_two);
    re_engine_destroy(engine_one);
}

TEST(builtin_random_rejects_bad_max) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    ASSERT_EQ(re_program_load(NULL, text("rule \"R\" { when true then R = random(0); }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_INVALID_ARGUMENT);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
    engine = re_engine_create(NULL, NULL);
    facts = re_facts_create(NULL, NULL);
    program = NULL;
    ASSERT_EQ(re_program_load(NULL, text("rule \"R\" { when true then R = random(\"x\"); }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_INVALID_ARGUMENT);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(builtin_format_percent_directives) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    run_program(engine, facts,
        "rule \"F\" { when true then A = format(\"%d-%s-%f\", 42, \"x\", 1.5);"
        " B = sprintf(\"100%%\"); C = format(\"%d %d\", 1); D = format();"
        " E = format(\"%s %s\", \"a\", true); }");
    assert_string_fact(facts, "A", "42-x-1.500000");
    assert_string_fact(facts, "B", "100%");
    /* Exhausted values leave the directive verbatim. */
    assert_string_fact(facts, "C", "1 %d");
    assert_string_fact(facts, "D", "");
    assert_string_fact(facts, "E", "a true");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(builtin_format_brace_placeholders) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    /* Upstream's {0}/{1}/... replacement is supported alongside %d/%s/%f. */
    run_program(engine, facts,
        "rule \"F\" { when true then A = format(\"{0}+{1}={2}\", 2, 3, 5);"
        " B = format(\"{1}{9}\", \"a\", \"b\"); }");
    assert_string_fact(facts, "A", "2+3=5");
    /* An out-of-range placeholder index stays verbatim (upstream behavior:
     * only existing values are replaced). */
    assert_string_fact(facts, "B", "b{9}");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(builtin_format_percent_f_huge_double_truncates_safely) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t big = real(1e300);
    re_value_t out = {RE_VALUE_NONE, {0}};
    size_t i;
    /* The lexer has no exponent literals, so 1e300 arrives via a fact. %f of
     * 1e300 would be 308 bytes; snprintf truncates to the 63-byte content of
     * the 64-byte stack buffer and returns the WOULD-BE length - the append
     * must clamp to what fit (pre-fix this was a stack-buffer-overflow read,
     * ASan-confirmed). The truncated content is all digits (the exact
     * decimal expansion of the stored double; the '.' sits past the cut). */
    ASSERT_EQ(re_facts_set(facts, text("Big"), &big), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"F\" { when true then A = format(\"%f\", Big); }");
    ASSERT_EQ(re_facts_get(facts, text("A"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.type, RE_VALUE_STRING);
    ASSERT_EQ(out.as.string.size, 63u);
    ASSERT_TRUE(out.as.string.data[0] == '1');
    for (i = 1u; i < 63u; ++i)
        ASSERT_TRUE(out.as.string.data[i] >= '0' && out.as.string.data[i] <= '9');
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(builtin_length_count_share_condition_len_semantics) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t items[2];
    items[0] = integer(1);
    items[1] = integer(2);
    set_object_member(facts, "S", "name", string("John"));
    set_array_fact(facts, "Arr", items, 2u);
    run_program(engine, facts,
        "rule \"R\" { when true then L = length(S.name); C = count(Arr); B = length(5); }");
    assert_int_fact(facts, "L", 4);
    assert_int_fact(facts, "C", 2);
    /* A3 semantics shared verbatim: a wrong-typed argument is false. */
    assert_bool_fact(facts, "B", 0);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(builtin_sum_max_min_preserve_int64) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    run_program(engine, facts,
        "rule \"R\" { when true then A = sum(1, 2, 3); B = add(4, 5);"
        " C = max(3, 9, 4); D = min(3, 9, 4); }");
    assert_int_fact(facts, "A", 6);
    assert_int_fact(facts, "B", 9);
    assert_int_fact(facts, "C", 9);
    assert_int_fact(facts, "D", 3);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(builtin_folds_go_double_on_mixed_types) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    run_program(engine, facts,
        "rule \"R\" { when true then A = sum(1, 2.5); B = max(1.5, 2); C = min(1, 0.5); }");
    assert_double_fact(facts, "A", 3.5);
    assert_double_fact(facts, "B", 2.0);
    assert_double_fact(facts, "C", 0.5);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(builtin_folds_skip_non_numeric_and_empty_args) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t out = {RE_VALUE_NONE, {0}};
    run_program(engine, facts,
        "rule \"R\" { when true then A = sum(); B = sum(\"a\", 2, true); C = avg();"
        " D = avg(2, 4); E = average(1, 2, 3); F = max(\"x\"); G = min(); }");
    /* No numeric args: sum -> Integer 0, avg -> 0, max -> -inf, min -> +inf
     * (upstream's fold seeds translated to typed values). */
    assert_int_fact(facts, "A", 0);
    assert_int_fact(facts, "B", 2);
    assert_double_fact(facts, "C", 0.0);
    assert_double_fact(facts, "D", 3.0);
    assert_double_fact(facts, "E", 2.0);
    ASSERT_EQ(re_facts_get(facts, text("F"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.type, RE_VALUE_DOUBLE);
    ASSERT_TRUE(out.as.double_value < -1e308);
    ASSERT_EQ(re_facts_get(facts, text("G"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.type, RE_VALUE_DOUBLE);
    ASSERT_TRUE(out.as.double_value > 1e308);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(builtin_round_floor_ceil_abs) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    run_program(engine, facts,
        "rule \"R\" { when true then A = round(2.5); B = round(-2.5); C = floor(2.7);"
        " D = ceil(2.1); E = abs(-3); F = abs(-2.5); G = round(7); H = floor(-2.1); }");
    /* Rust f64::round and C99 round both round half away from zero. */
    assert_double_fact(facts, "A", 3.0);
    assert_double_fact(facts, "B", -3.0);
    assert_double_fact(facts, "C", 2.0);
    assert_double_fact(facts, "D", 3.0);
    assert_int_fact(facts, "E", 3);
    assert_double_fact(facts, "F", 2.5);
    /* Integer input passes through unchanged (upstream i.to_string()). */
    assert_int_fact(facts, "G", 7);
    assert_double_fact(facts, "H", -3.0);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(builtin_math_wrong_type_or_arity_errors_the_run) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    ASSERT_EQ(re_program_load(NULL, text("rule \"R\" { when true then R = round(\"x\"); }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_INVALID_ARGUMENT);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
    engine = re_engine_create(NULL, NULL);
    facts = re_facts_create(NULL, NULL);
    program = NULL;
    ASSERT_EQ(re_program_load(NULL, text("rule \"R\" { when true then R = abs(); }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_INVALID_ARGUMENT);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(builtin_includes_aliases_contains) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t items[2];
    items[0] = integer(1);
    items[1] = integer(2);
    set_object_member(facts, "S", "name", string("John"));
    set_array_fact(facts, "Arr", items, 2u);
    run_program(engine, facts,
        "rule \"Sub\" { when includes(S.name, \"oh\") then HitSub = 1; }"
        "rule \"Arr\" { when includes(Arr, 2) then HitArr = 1; }"
        "rule \"No\" { when includes(S.name, \"zz\") then HitNo = 1; }"
        "rule \"Rhs\" { when true then R = includes(\"hello\", \"ell\"); }");
    /* Same typed A3 semantics under the action-table alias, including the
     * bare-predicate whole-condition form. */
    assert_int_fact(facts, "HitSub", 1);
    assert_int_fact(facts, "HitArr", 1);
    assert_no_fact(facts, "HitNo");
    assert_bool_fact(facts, "R", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(builtin_startswith_endswith) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    set_object_member(facts, "S", "name", string("John"));
    run_program(engine, facts,
        "rule \"Sw\" { when startswith(S.name, \"Jo\") then HitSw = 1; }"
        "rule \"Ew\" { when endswith(S.name, \"hn\") then HitEw = 1; }"
        "rule \"SwNo\" { when startswith(S.name, \"x\") then HitSwNo = 1; }"
        "rule \"Rhs\" { when true then A = startswith(\"abc\", \"ab\"); B = startswith(S.name, 5); }");
    assert_int_fact(facts, "HitSw", 1);
    assert_int_fact(facts, "HitEw", 1);
    assert_no_fact(facts, "HitSwNo");
    assert_bool_fact(facts, "A", 1);
    /* Wrong argument types are false, matching the condition operators. */
    assert_bool_fact(facts, "B", 0);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(builtin_lowercase_uppercase_trim) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    run_program(engine, facts,
        "rule \"R\" { when true then A = lowercase(\"AbC\"); B = uppercase(\"aBc\");"
        " C = trim(\"  x  \"); D = trim(5); E = uppercase(123); }");
    assert_string_fact(facts, "A", "abc");
    assert_string_fact(facts, "B", "ABC");
    assert_string_fact(facts, "C", "x");
    /* Non-string arguments are coerced through their display form (upstream
     * to_string leniency), so trim(5) is "5", not an error. */
    assert_string_fact(facts, "D", "5");
    assert_string_fact(facts, "E", "123");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(builtin_case_trim_require_an_argument) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    ASSERT_EQ(re_program_load(NULL, text("rule \"R\" { when true then R = lowercase(); }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_INVALID_ARGUMENT);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(builtin_split_returns_debug_string) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    /* Upstream returns format!("{:?}", parts) - a debug string, not an
     * array - so the scalar function ABI needs no extension. */
    run_program(engine, facts,
        "rule \"R\" { when true then A = split(\"a,b,c\", \",\"); B = split(\"\", \",\"); }");
    assert_string_fact(facts, "A", "[\"a\", \"b\", \"c\"]");
    assert_string_fact(facts, "B", "[\"\"]");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(builtin_split_requires_two_args_and_nonempty_delimiter) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    ASSERT_EQ(re_program_load(NULL, text("rule \"R\" { when true then R = split(\"a\"); }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_INVALID_ARGUMENT);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
    engine = re_engine_create(NULL, NULL);
    facts = re_facts_create(NULL, NULL);
    program = NULL;
    ASSERT_EQ(re_program_load(NULL, text("rule \"R\" { when true then R = split(\"a\", \"\"); }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_INVALID_ARGUMENT);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(builtin_join_delimiter_first) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    /* Upstream argument order: the delimiter is the FIRST argument. */
    run_program(engine, facts,
        "rule \"R\" { when true then A = join(\",\", \"a\", \"b\", \"c\"); B = join(\"-\", 1, 2); }");
    assert_string_fact(facts, "A", "a,b,c");
    assert_string_fact(facts, "B", "1-2");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(builtin_join_requires_two_args) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    ASSERT_EQ(re_program_load(NULL, text("rule \"R\" { when true then R = join(\",\"); }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_INVALID_ARGUMENT);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(builtin_functions_compose_in_rhs_and_method_args) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t out = {RE_VALUE_NONE, {0}};
    set_object_member(facts, "S", "Name", string("old"));
    run_program(engine, facts,
        "rule \"R\" { when true then X = max(1, sum(2, 3)); Y = uppercase(trim(\"  ab \"));"
        " $S.setName(uppercase(\"ab\")); }");
    assert_int_fact(facts, "X", 5);
    assert_string_fact(facts, "Y", "AB");
    /* $Fact.method(...) arguments resolve through the same term machinery,
     * so built-ins work there too (setName maps to the Name member). */
    ASSERT_EQ(re_facts_get_path(facts, text("S.Name"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.type, RE_VALUE_STRING);
    ASSERT_EQ(out.as.string.size, 2u);
    ASSERT_TRUE(memcmp(out.as.string.data, "AB", 2u) == 0);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(builtin_folds_work_in_conditions) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t a = integer(7);
    ASSERT_EQ(re_facts_set(facts, text("A"), &a), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"S\" { when sum(1, 2, 3) == 6 then HitS = 1; }"
        "rule \"M\" { when max(A, 3) > 4 then HitM = 1; }"
        "rule \"No\" { when avg(1, 2) == 1.5 then HitAvg = 1; }");
    assert_int_fact(facts, "HitS", 1);
    assert_int_fact(facts, "HitM", 1);
    assert_int_fact(facts, "HitAvg", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

static re_status_t override_sum_call(re_engine_t *engine, re_facts_t *facts,
                                     const re_value_t *arguments, size_t argument_count,
                                     re_value_t *out_value, void *context) {
    (void)engine; (void)facts; (void)arguments; (void)argument_count; (void)context;
    out_value->type = RE_VALUE_INT64;
    out_value->as.int64_value = 100;
    return RE_STATUS_OK;
}

TEST(builtin_user_override_covers_action_builtins) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_function_t *sum_fn = NULL;
    re_function_descriptor_t sum_descriptor = {sizeof(sum_descriptor), RE_ABI_VERSION_MAJOR,
        {"sum", 3u}, override_sum_call, NULL, NULL};
    ASSERT_EQ(re_engine_register_function(engine, &sum_descriptor, &sum_fn), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"R\" { when true then A = sum(1, 2, 3); B = max(1, 2); }");
    /* The registry still wins over the extended table; max is untouched. */
    assert_int_fact(facts, "A", 100);
    assert_int_fact(facts, "B", 2);
    re_function_unregister(sum_fn);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

/* Task A5: multifield condition ops on array fields (upstream grl.rs L115-155
 * anchored regexes, forward engine.rs L1115-1164 semantics). `F.arr count
 * <cmp> n` compares the element count (missing field -> 0, a present
 * non-array field -> 1); `first`/`last` are true iff the field is a non-empty
 * array (no binding); `empty` is true for an empty array OR a missing field;
 * `not_empty`/`notEmpty` is the inverse (missing -> false); `collect` is true
 * iff the field exists. The array field may be a flat dotted key or a
 * structured member (re_facts_get_structured_path reaches member arrays; a
 * path below a scalar member stays missing). Multifield conditions are pure
 * read-only predicates, never RETE-eligible (rete.c collect() only takes
 * plain comparisons), and a resolved array path joins the condition read-set
 * so derived facts anchor on the array's root fact. */

static void set_object_array_member(re_facts_t *facts, const char *name, const char *key,
                                    const re_value_t *items, size_t count) {
    re_value_handle_t *object = NULL;
    re_value_handle_t *array = NULL;
    size_t i;
    ASSERT_EQ(re_value_create_object(facts, &object), RE_STATUS_OK);
    ASSERT_EQ(re_value_create_array(facts, &array), RE_STATUS_OK);
    for (i = 0u; i < count; ++i) ASSERT_EQ(re_value_array_append(array, &items[i]), RE_STATUS_OK);
    ASSERT_EQ(re_value_object_set_value(object, text(key), array), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set_value(facts, text(name), object), RE_STATUS_OK);
    re_value_destroy(array);
    re_value_destroy(object);
}

TEST(multifield_count_compares_array_length) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t items[3];
    items[0] = integer(1); items[1] = integer(2); items[2] = integer(3);
    set_array_fact(facts, "Items", items, 3u);
    run_program(engine, facts,
        "rule \"Eq\" { when Items count == 3 then HitEq = 1; }"
        "rule \"Ne\" { when Items count == 4 then HitNe = 1; }");
    assert_int_fact(facts, "HitEq", 1);
    assert_no_fact(facts, "HitNe");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(multifield_count_supports_every_comparison) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t items[3];
    items[0] = integer(1); items[1] = integer(2); items[2] = integer(3);
    set_array_fact(facts, "Items", items, 3u);
    run_program(engine, facts,
        "rule \"Eq\" { when Items count == 3 then HitEq = 1; }"
        "rule \"Ne\" { when Items count != 3 then HitNe = 1; }"
        "rule \"Gt\" { when Items count > 2 then HitGt = 1; }"
        "rule \"Ge\" { when Items count >= 3 then HitGe = 1; }"
        "rule \"Lt\" { when Items count < 4 then HitLt = 1; }"
        "rule \"Le\" { when Items count <= 3 then HitLe = 1; }"
        "rule \"GtNo\" { when Items count > 3 then HitGtNo = 1; }"
        "rule \"LtNo\" { when Items count < 3 then HitLtNo = 1; }"
        /* Relational operators coerce the literal via to_number (D4). */
        "rule \"Double\" { when Items count >= 2.5 then HitDouble = 1; }");
    assert_int_fact(facts, "HitEq", 1);
    assert_no_fact(facts, "HitNe");
    assert_int_fact(facts, "HitGt", 1);
    assert_int_fact(facts, "HitGe", 1);
    assert_int_fact(facts, "HitLt", 1);
    assert_int_fact(facts, "HitLe", 1);
    assert_no_fact(facts, "HitGtNo");
    assert_no_fact(facts, "HitLtNo");
    assert_int_fact(facts, "HitDouble", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(multifield_count_strict_equality_rejects_double_literal) {
    /* D4 lock: the count value is INT64 and equality is strictly typed, so
     * an int64 3 does NOT equal the double literal 3.0 - while relational
     * operators still coerce (>= 3.0 matches, per the test above). */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t items[3];
    items[0] = integer(1); items[1] = integer(2); items[2] = integer(3);
    set_array_fact(facts, "Items", items, 3u);
    run_program(engine, facts,
        "rule \"EqInt\" { when Items count == 3 then HitEqInt = 1; }"
        "rule \"EqDbl\" { when Items count == 3.0 then HitEqDbl = 1; }"
        "rule \"NeDbl\" { when Items count != 3.0 then HitNeDbl = 1; }");
    assert_int_fact(facts, "HitEqInt", 1);
    assert_no_fact(facts, "HitEqDbl");
    assert_int_fact(facts, "HitNeDbl", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(multifield_count_missing_field_is_zero) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    set_object_member(facts, "Order", "total", integer(5));
    run_program(engine, facts,
        "rule \"G0\" { when Ghost.items count == 0 then HitG0 = 1; }"
        "rule \"G1\" { when Ghost.items count > 0 then HitG1 = 1; }"
        /* A missing MEMBER on a present object is missing too. */
        "rule \"M0\" { when Order.missing count == 0 then HitM0 = 1; }"
        "rule \"M1\" { when Order.missing count >= 1 then HitM1 = 1; }");
    assert_int_fact(facts, "HitG0", 1);
    assert_no_fact(facts, "HitG1");
    assert_int_fact(facts, "HitM0", 1);
    assert_no_fact(facts, "HitM1");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(multifield_count_non_array_field_counts_as_one) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t n = integer(5);
    ASSERT_EQ(re_facts_set(facts, text("N"), &n), RE_STATUS_OK);
    set_object_member(facts, "Obj", "x", integer(1));
    run_program(engine, facts,
        "rule \"N1\" { when N count == 1 then HitN1 = 1; }"
        "rule \"N5\" { when N count == 5 then HitN5 = 1; }"
        "rule \"O1\" { when Obj count == 1 then HitO1 = 1; }"
        "rule \"O2\" { when Obj count > 1 then HitO2 = 1; }"
        /* A scalar member of an object is a present non-array field too. */
        "rule \"X1\" { when Obj.x count == 1 then HitX1 = 1; }");
    assert_int_fact(facts, "HitN1", 1);
    assert_no_fact(facts, "HitN5");
    assert_int_fact(facts, "HitO1", 1);
    assert_no_fact(facts, "HitO2");
    assert_int_fact(facts, "HitX1", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(multifield_first_and_last_require_non_empty_array) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t items[2];
    re_value_t n = integer(5);
    items[0] = integer(1); items[1] = integer(2);
    set_array_fact(facts, "Items", items, 2u);
    set_array_fact(facts, "EmptyArr", items, 0u);
    ASSERT_EQ(re_facts_set(facts, text("N"), &n), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"First\" { when Items first then HitFirst = 1; }"
        "rule \"Last\" { when Items last then HitLast = 1; }"
        "rule \"EFirst\" { when EmptyArr first then HitEFirst = 1; }"
        "rule \"ELast\" { when EmptyArr last then HitELast = 1; }"
        "rule \"NFirst\" { when N first then HitNFirst = 1; }"
        "rule \"GFirst\" { when Ghost first then HitGFirst = 1; }"
        "rule \"GLast\" { when Ghost last then HitGLast = 1; }");
    assert_int_fact(facts, "HitFirst", 1);
    assert_int_fact(facts, "HitLast", 1);
    assert_no_fact(facts, "HitEFirst");
    assert_no_fact(facts, "HitELast");
    assert_no_fact(facts, "HitNFirst");
    assert_no_fact(facts, "HitGFirst");
    assert_no_fact(facts, "HitGLast");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(multifield_empty_true_for_empty_array_and_missing_field) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t items[2];
    re_value_t n = integer(5);
    items[0] = integer(1); items[1] = integer(2);
    set_array_fact(facts, "Items", items, 2u);
    set_array_fact(facts, "EmptyArr", items, 0u);
    ASSERT_EQ(re_facts_set(facts, text("N"), &n), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"EA\" { when EmptyArr empty then HitEA = 1; }"
        "rule \"G\" { when Ghost empty then HitG = 1; }"
        "rule \"A\" { when Items empty then HitA = 1; }"
        "rule \"N\" { when N empty then HitN = 1; }");
    assert_int_fact(facts, "HitEA", 1);
    assert_int_fact(facts, "HitG", 1);
    assert_no_fact(facts, "HitA");
    assert_no_fact(facts, "HitN");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(multifield_not_empty_aliases) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t items[1];
    items[0] = integer(1);
    set_array_fact(facts, "Items", items, 1u);
    set_array_fact(facts, "EmptyArr", items, 0u);
    run_program(engine, facts,
        "rule \"Ne\" { when Items not_empty then HitNe = 1; }"
        "rule \"NeC\" { when Items notEmpty then HitNeC = 1; }"
        "rule \"ENe\" { when EmptyArr not_empty then HitENe = 1; }"
        "rule \"GNe\" { when Ghost not_empty then HitGNe = 1; }"
        "rule \"GNeC\" { when Ghost notEmpty then HitGNeC = 1; }");
    assert_int_fact(facts, "HitNe", 1);
    assert_int_fact(facts, "HitNeC", 1);
    assert_no_fact(facts, "HitENe");
    assert_no_fact(facts, "HitGNe");
    assert_no_fact(facts, "HitGNeC");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(multifield_collect_true_iff_field_exists) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t items[1];
    re_value_t n = integer(5);
    items[0] = integer(1);
    set_array_fact(facts, "Items", items, 1u);
    set_array_fact(facts, "EmptyArr", items, 0u);
    ASSERT_EQ(re_facts_set(facts, text("N"), &n), RE_STATUS_OK);
    set_object_member(facts, "Obj", "x", integer(1));
    run_program(engine, facts,
        "rule \"A\" { when Items collect then HitA = 1; }"
        "rule \"EA\" { when EmptyArr collect then HitEA = 1; }"
        "rule \"N\" { when N collect then HitN = 1; }"
        "rule \"M\" { when Obj.x collect then HitM = 1; }"
        "rule \"G\" { when Ghost collect then HitG = 1; }"
        "rule \"GM\" { when Obj.missing collect then HitGM = 1; }");
    assert_int_fact(facts, "HitA", 1);
    assert_int_fact(facts, "HitEA", 1);
    assert_int_fact(facts, "HitN", 1);
    assert_int_fact(facts, "HitM", 1);
    assert_no_fact(facts, "HitG");
    assert_no_fact(facts, "HitGM");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(multifield_nested_member_array) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t items[2];
    items[0] = integer(10); items[1] = integer(20);
    set_object_array_member(facts, "Order", "items", items, 2u);
    run_program(engine, facts,
        "rule \"C\" { when Order.items count == 2 then HitC = 1; }"
        "rule \"F\" { when Order.items first then HitF = 1; }"
        "rule \"L\" { when Order.items last then HitL = 1; }"
        "rule \"Ne\" { when Order.items notEmpty then HitNe = 1; }"
        "rule \"E\" { when Order.items empty then HitE = 1; }"
        "rule \"Co\" { when Order.items collect then HitCo = 1; }");
    assert_int_fact(facts, "HitC", 1);
    assert_int_fact(facts, "HitF", 1);
    assert_int_fact(facts, "HitL", 1);
    assert_int_fact(facts, "HitNe", 1);
    assert_no_fact(facts, "HitE");
    assert_int_fact(facts, "HitCo", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(multifield_flat_dotted_key_wins) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t items[2];
    items[0] = integer(1); items[1] = integer(2);
    /* A fact literally named "Cart.items" (flat dotted key) is the array. */
    set_array_fact(facts, "Cart.items", items, 2u);
    run_program(engine, facts,
        "rule \"C\" { when Cart.items count == 2 then HitC = 1; }"
        "rule \"Ne\" { when Cart.items not_empty then HitNe = 1; }");
    assert_int_fact(facts, "HitC", 1);
    assert_int_fact(facts, "HitNe", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(multifield_compounds_with_logical_operators) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t items[2];
    re_value_t b = integer(2);
    items[0] = integer(1); items[1] = integer(2);
    set_array_fact(facts, "Cart", items, 2u);
    ASSERT_EQ(re_facts_set(facts, text("B"), &b), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"And\" { when Cart count > 1 and B == 2 then HitAnd = 1; }"
        "rule \"AndNo\" { when Cart count > 1 and B == 3 then HitAndNo = 1; }"
        "rule \"Or\" { when Cart count > 5 or B == 2 then HitOr = 1; }"
        "rule \"Not\" { when not Cart empty then HitNot = 1; }"
        "rule \"NotNo\" { when not Cart not_empty then HitNotNo = 1; }");
    assert_int_fact(facts, "HitAnd", 1);
    assert_no_fact(facts, "HitAndNo");
    assert_int_fact(facts, "HitOr", 1);
    assert_int_fact(facts, "HitNot", 1);
    assert_no_fact(facts, "HitNotNo");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(multifield_quantifier_interplay) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t two[2];
    re_value_t one[1];
    two[0] = integer(1); two[1] = integer(2);
    one[0] = integer(3);
    /* D7 prefix heuristic: candidates are the Score* facts; each candidate's
     * tags member array is probed through the rebound path. */
    set_object_array_member(facts, "Score1", "tags", two, 2u);
    set_object_array_member(facts, "Score2", "tags", one, 1u);
    run_program(engine, facts,
        "rule \"Ex\" { when exists(Score.tags count > 1) then HitEx = 1; }"
        "rule \"Fa\" { when forall(Score.tags count > 1) then HitFa = 1; }"
        "rule \"FaNe\" { when forall(Score.tags not_empty) then HitFaNe = 1; }");
    assert_int_fact(facts, "HitEx", 1);
    assert_no_fact(facts, "HitFa");
    assert_int_fact(facts, "HitFaNe", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(multifield_conditions_are_pure_and_reevaluated) {
    /* Watch is evaluated FIRST (source order), while Items is still missing;
     * only a pure classification re-evaluates it on the passes after Seed
     * fires and appends to Items. An impure classification would keep the
     * first-pass false and HitWatch would never appear. */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t a = integer(1);
    ASSERT_EQ(re_facts_set(facts, text("A"), &a), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"Watch\" { when Items not_empty then HitWatch = 1; }"
        "rule \"Seed\" { when A == 1 then Items += 7; }");
    assert_int_fact(facts, "HitWatch", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(multifield_rules_stay_off_rete) {
    /* rete.c collect() only takes plain comparisons, so a multifield
     * condition keeps the rule on the linear matcher (which still fires). */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_rete_network_t *network = NULL;
    re_value_t items[2];
    re_value_t b = integer(2);
    items[0] = integer(1); items[1] = integer(2);
    set_array_fact(facts, "Items", items, 2u);
    ASSERT_EQ(re_facts_set(facts, text("B"), &b), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"Mf\" { when Items count > 1 and B == 2 then HitMf = 1; }");
    assert_int_fact(facts, "HitMf", 1);
    ASSERT_EQ(re_engine_rete_network(engine, &network), RE_STATUS_NOT_SUPPORTED);
    ASSERT_TRUE(network == NULL);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(multifield_read_set_records_array_path_premise) {
    /* The resolved array path joins the condition read-set, so the derived
     * fact is logically inserted with the array's ROOT fact as premise
     * (resolve_read_premise maps Order.items -> Order) and a premise
     * retraction cascades to it. Order is inserted first: slot 0, gen 0. */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t items[2];
    re_fact_id_t order_id = {0u, 0u};
    re_fact_id_t hit_id = {1u, 1u};
    re_fact_provenance_t provenance = {sizeof(provenance), 0u, {NULL, 0u}, 0u, NULL};
    re_value_t out = {RE_VALUE_NONE, {0}};
    items[0] = integer(1); items[1] = integer(2);
    set_object_array_member(facts, "Order", "items", items, 2u);
    run_program(engine, facts,
        "rule \"Mf\" { when Order.items count > 1 then Hit = 1; }");
    assert_int_fact(facts, "Hit", 1);
    ASSERT_EQ(re_facts_provenance_get(facts, hit_id, &provenance), RE_STATUS_OK);
    ASSERT_EQ(provenance.premise_count, 1u);
    ASSERT_EQ(provenance.premises[0].slot, order_id.slot);
    ASSERT_EQ(provenance.premises[0].generation, order_id.generation);
    ASSERT_EQ(re_facts_retract(facts, order_id), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("Hit"), &out), RE_STATUS_NOT_FOUND);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(multifield_wrong_usage_parse_errors) {
    re_program_t *program = NULL;
    /* count without a comparison operator. */
    ASSERT_EQ(re_program_load(NULL, text("rule \"Bad\" { when Items count 2 then R = 1; }"), NULL, &program),
              RE_STATUS_PARSE_ERROR);
    /* count against a non-literal operand. */
    ASSERT_EQ(re_program_load(NULL, text("rule \"Bad\" { when Items count > Other then R = 1; }"), NULL, &program),
              RE_STATUS_PARSE_ERROR);
    /* count with nothing after it. */
    ASSERT_EQ(re_program_load(NULL, text("rule \"Bad\" { when Items count then R = 1; }"), NULL, &program),
              RE_STATUS_PARSE_ERROR);
    /* Bare predicates take no comparison. */
    ASSERT_EQ(re_program_load(NULL, text("rule \"Bad\" { when Items first == true then R = 1; }"), NULL, &program),
              RE_STATUS_PARSE_ERROR);
    /* count rejects non-comparison word operators. */
    ASSERT_EQ(re_program_load(NULL, text("rule \"Bad\" { when Items count contains 2 then R = 1; }"), NULL, &program),
              RE_STATUS_PARSE_ERROR);
}

/*
 * A6 accumulate(...) CE (upstream grl.rs L834-881 + engine.rs L701-830):
 * accumulate(Type($var: field, cond, ...), func(...)) flat-scans the
 * "Type.<instance>.<field>" keys (a bare "Type.<field>" key is the "default"
 * instance), keeps the instances where every mini-condition holds, folds the
 * extracted field values with sum/count/average/avg/min/max, injects the
 * result as the fact "Type.func", and the accumulate condition itself always
 * matches. Local divergences (documented): the mini-condition operator scan
 * is longest-first (>= before >), mini-condition equality reuses
 * re_value_compare (strict typed ==, no double epsilon), an unknown function
 * name is a parse error, and the $var-less count form counts matching
 * instances (upstream counts extracted values, which is 0 there).
 */

TEST(accumulate_sum_over_instances_with_condition_filter) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t v;
    v = integer(100); ASSERT_EQ(re_facts_set(facts, text("Order.1.amount"), &v), RE_STATUS_OK);
    v = string("ok"); ASSERT_EQ(re_facts_set(facts, text("Order.1.status"), &v), RE_STATUS_OK);
    v = integer(50); ASSERT_EQ(re_facts_set(facts, text("Order.2.amount"), &v), RE_STATUS_OK);
    v = string("pending"); ASSERT_EQ(re_facts_set(facts, text("Order.2.status"), &v), RE_STATUS_OK);
    v = integer(25); ASSERT_EQ(re_facts_set(facts, text("Order.3.amount"), &v), RE_STATUS_OK);
    v = string("ok"); ASSERT_EQ(re_facts_set(facts, text("Order.3.status"), &v), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"S\" { when accumulate(Order($o: amount, status == \"ok\"), sum($o)) then HitS = 1; }");
    assert_double_fact(facts, "Order.sum", 125.0);
    assert_int_fact(facts, "HitS", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(accumulate_result_gates_followup_condition) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_rete_network_t *network = NULL;
    re_value_t v;
    v = integer(100); ASSERT_EQ(re_facts_set(facts, text("Order.1.amount"), &v), RE_STATUS_OK);
    v = integer(50); ASSERT_EQ(re_facts_set(facts, text("Order.2.amount"), &v), RE_STATUS_OK);
    v = integer(25); ASSERT_EQ(re_facts_set(facts, text("Order.3.amount"), &v), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"Big\" { when accumulate(Order($o: amount), sum($o)) and Order.sum > 100 then HitBig = 1; }"
        "rule \"Small\" { when accumulate(Order($o: amount), sum($o)) and Order.sum > 1000 then HitSmall = 1; }");
    assert_double_fact(facts, "Order.sum", 175.0);
    assert_int_fact(facts, "HitBig", 1);
    assert_no_fact(facts, "HitSmall");
    /* An accumulate rule never collects into RETE conditions. */
    ASSERT_EQ(re_engine_rete_network(engine, &network), RE_STATUS_NOT_SUPPORTED);
    ASSERT_TRUE(network == NULL);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(accumulate_count_counts_extracted_values) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t v;
    v = integer(10); ASSERT_EQ(re_facts_set(facts, text("Order.1.amount"), &v), RE_STATUS_OK);
    v = integer(20); ASSERT_EQ(re_facts_set(facts, text("Order.2.amount"), &v), RE_STATUS_OK);
    /* Instance 3 matches no field: it lacks the extract field entirely. */
    v = string("x"); ASSERT_EQ(re_facts_set(facts, text("Order.3.note"), &v), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"C\" { when accumulate(Order($o: amount), count($o)) and Order.count == 2 then HitC = 1; }");
    assert_int_fact(facts, "Order.count", 2);
    assert_int_fact(facts, "HitC", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(accumulate_average_and_avg_spelling_keys) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t v;
    v = integer(10); ASSERT_EQ(re_facts_set(facts, text("Order.1.price"), &v), RE_STATUS_OK);
    v = integer(20); ASSERT_EQ(re_facts_set(facts, text("Order.2.price"), &v), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"A\" { when accumulate(Order($p: price), average($p)) then HitA = 1; }"
        "rule \"B\" { when accumulate(Order($p: price), avg($p)) then HitB = 1; }");
    /* The injected key keeps the source spelling of the function name. */
    assert_double_fact(facts, "Order.average", 15.0);
    assert_double_fact(facts, "Order.avg", 15.0);
    assert_int_fact(facts, "HitA", 1);
    assert_int_fact(facts, "HitB", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(accumulate_min_max) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t v;
    v = integer(5); ASSERT_EQ(re_facts_set(facts, text("Order.1.amount"), &v), RE_STATUS_OK);
    v = integer(42); ASSERT_EQ(re_facts_set(facts, text("Order.2.amount"), &v), RE_STATUS_OK);
    v = integer(17); ASSERT_EQ(re_facts_set(facts, text("Order.3.amount"), &v), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"Mn\" { when accumulate(Order($o: amount), min($o)) then HitMn = 1; }"
        "rule \"Mx\" { when accumulate(Order($o: amount), max($o)) then HitMx = 1; }");
    assert_double_fact(facts, "Order.min", 5.0);
    assert_double_fact(facts, "Order.max", 42.0);
    assert_int_fact(facts, "HitMn", 1);
    assert_int_fact(facts, "HitMx", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(accumulate_empty_set_injects_zero) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t v;
    v = integer(10); ASSERT_EQ(re_facts_set(facts, text("Order.1.amount"), &v), RE_STATUS_OK);
    v = string("ok"); ASSERT_EQ(re_facts_set(facts, text("Order.1.status"), &v), RE_STATUS_OK);
    /* Every instance is filtered out; the accumulate condition still matches
     * and every function injects its zero. */
    run_program(engine, facts,
        "rule \"S\" { when accumulate(Order($o: amount, status == \"shipped\"), sum($o)) then HitS = 1; }"
        "rule \"C\" { when accumulate(Order($o: amount, status == \"shipped\"), count($o)) then HitC = 1; }"
        "rule \"A\" { when accumulate(Order($o: amount, status == \"shipped\"), avg($o)) then HitA = 1; }"
        "rule \"Mn\" { when accumulate(Order($o: amount, status == \"shipped\"), min($o)) then HitMn = 1; }"
        "rule \"Mx\" { when accumulate(Order($o: amount, status == \"shipped\"), max($o)) then HitMx = 1; }");
    assert_double_fact(facts, "Order.sum", 0.0);
    assert_int_fact(facts, "Order.count", 0);
    assert_double_fact(facts, "Order.avg", 0.0);
    assert_double_fact(facts, "Order.min", 0.0);
    assert_double_fact(facts, "Order.max", 0.0);
    assert_int_fact(facts, "HitS", 1);
    assert_int_fact(facts, "HitC", 1);
    assert_int_fact(facts, "HitA", 1);
    assert_int_fact(facts, "HitMn", 1);
    assert_int_fact(facts, "HitMx", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(accumulate_unknown_type_injects_zero) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t v = integer(1);
    ASSERT_EQ(re_facts_set(facts, text("Unrelated"), &v), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"S\" { when accumulate(Order($o: amount), sum($o)) then HitS = 1; }"
        "rule \"C\" { when accumulate(Order($o: amount), count($o)) then HitC = 1; }");
    assert_double_fact(facts, "Order.sum", 0.0);
    assert_int_fact(facts, "Order.count", 0);
    assert_int_fact(facts, "HitS", 1);
    assert_int_fact(facts, "HitC", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(accumulate_varless_pattern_counts_matching_instances) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t v;
    v = string("ok"); ASSERT_EQ(re_facts_set(facts, text("Order.1.status"), &v), RE_STATUS_OK);
    v = integer(5); ASSERT_EQ(re_facts_set(facts, text("Order.1.amount"), &v), RE_STATUS_OK);
    v = string("no"); ASSERT_EQ(re_facts_set(facts, text("Order.2.status"), &v), RE_STATUS_OK);
    v = integer(7); ASSERT_EQ(re_facts_set(facts, text("Order.2.amount"), &v), RE_STATUS_OK);
    v = string("ok"); ASSERT_EQ(re_facts_set(facts, text("Order.3.status"), &v), RE_STATUS_OK);
    v = integer(9); ASSERT_EQ(re_facts_set(facts, text("Order.3.amount"), &v), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"C\" { when accumulate(Order(status == \"ok\"), count()) then HitC = 1; }"
        "rule \"S\" { when accumulate(Order(status == \"ok\"), sum()) then HitS = 1; }");
    /* Local divergence: without an extract field, count counts the matching
     * instances (upstream counts extracted values, i.e. 0). */
    assert_int_fact(facts, "Order.count", 2);
    assert_double_fact(facts, "Order.sum", 0.0);
    assert_int_fact(facts, "HitC", 1);
    assert_int_fact(facts, "HitS", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(accumulate_bare_type_key_is_default_instance) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t v;
    v = integer(7); ASSERT_EQ(re_facts_set(facts, text("Order.amount"), &v), RE_STATUS_OK);
    v = string("n"); ASSERT_EQ(re_facts_set(facts, text("Order.note"), &v), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"S\" { when accumulate(Order($o: amount), sum($o)) then HitS = 1; }"
        "rule \"C\" { when accumulate(Order($o: amount), count($o)) then HitC = 1; }");
    assert_double_fact(facts, "Order.sum", 7.0);
    assert_int_fact(facts, "Order.count", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(accumulate_non_numeric_extracted_values_ignored) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t v;
    v = integer(10); ASSERT_EQ(re_facts_set(facts, text("Order.1.amount"), &v), RE_STATUS_OK);
    v = string("lots"); ASSERT_EQ(re_facts_set(facts, text("Order.2.amount"), &v), RE_STATUS_OK);
    v = integer(5); ASSERT_EQ(re_facts_set(facts, text("Order.3.amount"), &v), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"S\" { when accumulate(Order($o: amount), sum($o)) then HitS = 1; }"
        "rule \"C\" { when accumulate(Order($o: amount), count($o)) then HitC = 1; }"
        "rule \"A\" { when accumulate(Order($o: amount), avg($o)) then HitA = 1; }");
    /* count counts every extracted value; sum/avg skip the string. */
    assert_double_fact(facts, "Order.sum", 15.0);
    assert_int_fact(facts, "Order.count", 3);
    assert_double_fact(facts, "Order.avg", 7.5);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(accumulate_condition_operators_scan_longest_first) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t v;
    v = integer(10); ASSERT_EQ(re_facts_set(facts, text("P.1.v"), &v), RE_STATUS_OK);
    v = integer(20); ASSERT_EQ(re_facts_set(facts, text("P.2.v"), &v), RE_STATUS_OK);
    v = integer(30); ASSERT_EQ(re_facts_set(facts, text("P.3.v"), &v), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"Ge\" { when accumulate(P($x: v, v >= 20), sum($x)) then HitGe = 1; }"
        "rule \"Ne\" { when accumulate(P($x: v, v != 20), count($x)) then HitNe = 1; }"
        "rule \"Le\" { when accumulate(P($x: v, v <= 20), min($x)) then HitLe = 1; }"
        "rule \"Gt\" { when accumulate(P($x: v, v > 20), max($x)) then HitGt = 1; }");
    /* >= / <= must not degrade into > / < with a bogus "=20" RHS. */
    assert_double_fact(facts, "P.sum", 50.0);
    assert_int_fact(facts, "P.count", 2);
    assert_double_fact(facts, "P.min", 10.0);
    assert_double_fact(facts, "P.max", 30.0);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(accumulate_unknown_function_and_malformed_forms_parse_error) {
    re_program_t *program = NULL;
    /* Unknown accumulate function. */
    ASSERT_EQ(re_program_load(NULL, text("rule \"Bad\" { when accumulate(Order($o: amount), median($o)) then R = 1; }"), NULL, &program),
              RE_STATUS_PARSE_ERROR);
    /* Missing the function part. */
    ASSERT_EQ(re_program_load(NULL, text("rule \"Bad\" { when accumulate(Order($o: amount)) then R = 1; }"), NULL, &program),
              RE_STATUS_PARSE_ERROR);
    /* Unclosed accumulate call. */
    ASSERT_EQ(re_program_load(NULL, text("rule \"Bad\" { when accumulate(Order($o: amount), sum($o) then R = 1; }"), NULL, &program),
              RE_STATUS_PARSE_ERROR);
    /* Empty source pattern. */
    ASSERT_EQ(re_program_load(NULL, text("rule \"Bad\" { when accumulate(($o: amount), sum($o)) then R = 1; }"), NULL, &program),
              RE_STATUS_PARSE_ERROR);
    /* No parentheses at all: not the accumulate form, still unparseable. */
    ASSERT_EQ(re_program_load(NULL, text("rule \"Bad\" { when accumulate Order then R = 1; }"), NULL, &program),
              RE_STATUS_PARSE_ERROR);
}

TEST(accumulate_injected_result_is_a_read_set_premise) {
    /* The follow-up condition's read of the injected Order.sum fact joins the
     * condition read-set, so the derived fact is logically inserted with
     * Order.sum as premise and a premise retraction cascades to it. Slots:
     * Order.1.amount is set first (slot 0), the match-time injection creates
     * Order.sum (slot 1, generation 0), Hit is logically inserted (slot 2,
     * generation 1). */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_fact_id_t sum_id = {1u, 0u};
    re_fact_id_t hit_id = {2u, 1u};
    re_fact_provenance_t provenance = {sizeof(provenance), 0u, {NULL, 0u}, 0u, NULL};
    re_value_t out = {RE_VALUE_NONE, {0}};
    re_value_t v = integer(150);
    ASSERT_EQ(re_facts_set(facts, text("Order.1.amount"), &v), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"Big\" { when accumulate(Order($o: amount), sum($o)) and Order.sum > 100 then Hit = 1; }");
    assert_int_fact(facts, "Hit", 1);
    assert_double_fact(facts, "Order.sum", 150.0);
    ASSERT_EQ(re_facts_provenance_get(facts, hit_id, &provenance), RE_STATUS_OK);
    ASSERT_EQ(provenance.premise_count, 1u);
    ASSERT_EQ(provenance.premises[0].slot, sum_id.slot);
    ASSERT_EQ(provenance.premises[0].generation, sum_id.generation);
    ASSERT_EQ(re_facts_retract(facts, sum_id), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("Hit"), &out), RE_STATUS_NOT_FOUND);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(accumulate_with_executor_attached_stays_correct) {
    /* A6 purity observability: with the optional C11 executor attached the
     * accumulate rule must behave exactly as on the serial path - the
     * injected fold and the gating condition are unchanged (impure
     * conditions never reach the workers; the run loop keeps them on the
     * engine thread). Where the backend is compiled out,
     * re_engine_executor_create reports RE_STATUS_NOT_SUPPORTED and the same
     * assertions lock the serial behavior. */
    re_concurrency_options_t options = {sizeof(options), RE_ABI_VERSION_MAJOR, 2u, 0u};
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_executor_t *executor = NULL;
    re_value_t v;
    v = integer(100); ASSERT_EQ(re_facts_set(facts, text("Order.1.amount"), &v), RE_STATUS_OK);
    v = integer(50); ASSERT_EQ(re_facts_set(facts, text("Order.2.amount"), &v), RE_STATUS_OK);
    if (re_engine_executor_create(engine, &options, &executor) == RE_STATUS_NOT_SUPPORTED)
        executor = NULL;
    run_program(engine, facts,
        "rule \"S\" { when accumulate(Order($o: amount), sum($o)) and Order.sum > 100 then HitS = 1; }");
    assert_double_fact(facts, "Order.sum", 150.0);
    assert_int_fact(facts, "HitS", 1);
    re_executor_destroy(executor);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(accumulate_recomputes_across_runs_without_drift) {
    /* A6 cross-run stability: the injected "Type.func" fact is recomputed
     * from the CURRENT facts on every run that reaches the node - the second
     * run overwrites 150 with 125 (Order.2.amount changed), proving the fold
     * neither drifts nor accumulates onto the stale value. */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_value_t v;
    v = integer(100); ASSERT_EQ(re_facts_set(facts, text("Order.1.amount"), &v), RE_STATUS_OK);
    v = integer(50); ASSERT_EQ(re_facts_set(facts, text("Order.2.amount"), &v), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text(
        "rule \"S\" { when accumulate(Order($o: amount), sum($o)) then HitS = 1; }"),
        NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    assert_double_fact(facts, "Order.sum", 150.0);
    v = integer(25); ASSERT_EQ(re_facts_set(facts, text("Order.2.amount"), &v), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    assert_double_fact(facts, "Order.sum", 125.0);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

/* ---- A8 action surface (upstream grl.rs action builtins): retract($Obj)
 * sets the `_retracted_<root>` flag fact and condition reads on that root
 * evaluate false; log(...) prints to stdout through the A4 log built-in;
 * ActivateAgendaGroup("g") replaces the agenda focus for the rest of the
 * run; ScheduleRule/CompleteWorkflow/SetWorkflowData dispatch to a
 * registered function of the action name (D5). */

TEST(retract_gates_subsequent_rules_in_same_run) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t x = integer(1);
    ASSERT_EQ(re_facts_set(facts, text("Obj.x"), &x), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"A\" salience 10 { when Obj.x == 1 then retract($Obj); }"
        "rule \"B\" salience 5 { when Obj.x == 1 then HitB = 1; }");
    /* A fires first and retracts $Obj; B's condition is gated by the flag. */
    assert_no_fact(facts, "HitB");
    /* The flag is an ordinary readable fact. */
    assert_bool_fact(facts, "_retracted_Obj", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(retract_flag_persists_across_runs_and_reassert_does_not_clear) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t x = integer(1);
    re_value_t two = integer(2);
    ASSERT_EQ(re_facts_set(facts, text("Obj.x"), &x), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"A\" { when Obj.x == 1 then retract($Obj); }");
    assert_bool_fact(facts, "_retracted_Obj", 1);
    /* Re-asserting the fact does NOT clear the flag (upstream parity): the
     * follow-up rule stays gated even on the new value. */
    ASSERT_EQ(re_facts_set(facts, text("Obj.x"), &two), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"C\" { when Obj.x == 2 then HitC = 1; }");
    assert_no_fact(facts, "HitC");
    assert_bool_fact(facts, "_retracted_Obj", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(retract_gates_quantifier_candidate_reads) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    set_object_member(facts, "Score1", "value", integer(95));
    run_program(engine, facts,
        "rule \"A\" salience 10 { when exists(Score.value > 90) then retract($Score1); }"
        "rule \"B\" salience 5 { when exists(Score.value > 90) then HitB = 1; }");
    /* The rebound candidate read is gated, so the quantifier scores the
     * retracted candidate false. */
    assert_no_fact(facts, "HitB");
    assert_bool_fact(facts, "_retracted_Score1", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(retract_rejects_non_fact_argument) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    ASSERT_EQ(re_program_load(NULL, text("rule \"R\" { when true then retract(1); }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    program = NULL;
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_program_load(NULL, text("rule \"R\" { when true then retract(); }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_INVALID_ARGUMENT);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(log_action_prints_joined_args_to_stdout) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t x = integer(42);
    ASSERT_EQ(re_facts_set(facts, text("Obj.x"), &x), RE_STATUS_OK);
    /* No capture: assert OK and no crash (the line lands on stdout like the
     * A4 log() built-in, whose machinery the action shares). */
    run_program(engine, facts,
        "rule \"L\" { when Obj.x == 42 then log(\"saw\", Obj.x, 7); }");
    assert_int_fact(facts, "Obj.x", 42);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(activate_agenda_group_switches_focus_mid_run) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    run_program(engine, facts,
        "rule \"Switch\" salience 10 { when true then ActivateAgendaGroup(\"g\"); }"
        "rule \"NoGroup\" salience 5 { when true then HitNoGroup = 1; }"
        "rule \"InG\" { agenda-group \"g\"; when true then HitG = 1; }");
    /* After the switch only group-g rules are visible. */
    assert_int_fact(facts, "HitG", 1);
    assert_no_fact(facts, "HitNoGroup");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(activate_agenda_group_requires_a_string_argument) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    ASSERT_EQ(re_program_load(NULL, text("rule \"A\" { when true then ActivateAgendaGroup(7); }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_INVALID_ARGUMENT);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(workflow_actions_unhandled_are_not_supported) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    /* D5: without a registered function of the action name the run fails
     * with RE_STATUS_NOT_SUPPORTED. */
    ASSERT_EQ(re_program_load(NULL, text("rule \"S\" { when true then ScheduleRule(1000, \"later\"); }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    program = NULL;
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_NOT_SUPPORTED);
    ASSERT_EQ(re_program_load(NULL, text("rule \"C\" { when true then CompleteWorkflow(\"w\"); }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    program = NULL;
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_NOT_SUPPORTED);
    ASSERT_EQ(re_program_load(NULL, text("rule \"D\" { when true then SetWorkflowData(\"k=v\"); }"), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_NOT_SUPPORTED);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

typedef struct schedule_record_t {
    size_t calls;
    int64_t delay;
    char rule[16];
    size_t rule_size;
} schedule_record_t;
static re_status_t record_schedule_call(re_engine_t *engine, re_facts_t *facts,
                                        const re_value_t *arguments, size_t argument_count,
                                        re_value_t *out_value, void *context) {
    schedule_record_t *record = context;
    (void)engine; (void)facts;
    ++record->calls;
    if (argument_count == 2u && arguments[0].type == RE_VALUE_INT64 &&
        arguments[1].type == RE_VALUE_STRING &&
        arguments[1].as.string.size < sizeof(record->rule)) {
        record->delay = arguments[0].as.int64_value;
        memcpy(record->rule, arguments[1].as.string.data, arguments[1].as.string.size);
        record->rule_size = arguments[1].as.string.size;
    }
    out_value->type = RE_VALUE_NONE;
    out_value->as.int64_value = 0;
    return RE_STATUS_OK;
}

TEST(workflow_actions_dispatch_to_registered_function) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_function_t *schedule_fn = NULL;
    schedule_record_t record;
    re_function_descriptor_t descriptor = {sizeof(descriptor), RE_ABI_VERSION_MAJOR,
        {"ScheduleRule", 12u}, record_schedule_call, NULL, &record};
    memset(&record, 0, sizeof(record));
    ASSERT_EQ(re_engine_register_function(engine, &descriptor, &schedule_fn), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"S\" { when true then ScheduleRule(250, \"later\"); }");
    ASSERT_EQ(record.calls, 1u);
    ASSERT_EQ(record.delay, 250);
    ASSERT_EQ(record.rule_size, 5u);
    ASSERT_TRUE(memcmp(record.rule, "later", 5u) == 0);
    re_function_unregister(schedule_fn);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(unknown_bare_action_call_stays_a_parse_error) {
    re_program_t *program = NULL;
    /* Only the six whitelisted action names parse as bare call statements. */
    ASSERT_EQ(re_program_load(NULL, text("rule \"Bad\" { when true then Frobnicate(1); }"), NULL, &program),
              RE_STATUS_PARSE_ERROR);
}

typedef struct firing_log_t {
    char names[512];
    size_t size;
} firing_log_t;
static re_status_t record_firing(re_engine_t *engine, re_facts_t *facts,
                                 const re_rule_event_t *event, void *context) {
    firing_log_t *log = context;
    (void)engine; (void)facts;
    if (log->size + event->rule_name.size + 1u <= sizeof(log->names)) {
        memcpy(log->names + log->size, event->rule_name.data, event->rule_name.size);
        log->size += event->rule_name.size;
        log->names[log->size++] = ';';
    }
    return RE_STATUS_OK;
}

TEST(retract_gates_pending_rete_token_activation) {
    /* A8 review I1: the retract flag matches no RETE pattern, so a victim
     * activation pushed BEFORE the retract keeps a live token; pop-time must
     * re-run the gated linear match, not just token liveness. Victim and
     * Retractor share Gate so the Gate=2 write activates both in the same
     * recompute cycle; Retractor's higher salience pops it first. */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    firing_log_t log;
    re_callbacks_t callbacks;
    re_value_t v;
    memset(&log, 0, sizeof(log));
    memset(&callbacks, 0, sizeof(callbacks));
    callbacks.action = record_firing;
    callbacks.context = &log;
    v = integer(1); ASSERT_EQ(re_facts_set(facts, text("A.x"), &v), RE_STATUS_OK);
    v = integer(2); ASSERT_EQ(re_facts_set(facts, text("B.y"), &v), RE_STATUS_OK);
    v = integer(1); ASSERT_EQ(re_facts_set(facts, text("Gate"), &v), RE_STATUS_OK);
    ASSERT_EQ(re_program_load(NULL, text(
        "rule \"VictimGate\" salience 1 { when Gate == 1 then Gate = 2; }"
        "rule \"Retractor\" salience 10 { when A.x == 1 and B.y == 2 and Gate == 2 then retract($A); }"
        "rule \"Victim\" salience 5 { when A.x == 1 and B.y == 2 and Gate == 2 then Victim.hit = 1; }"),
        NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, &callbacks), RE_STATUS_OK);
    /* Victim's pending token-backed activation must not fire after the
     * retract: only the enabler and Retractor are in the firing log. */
    ASSERT_TRUE(strstr(log.names, "VictimGate;") != NULL);
    ASSERT_TRUE(strstr(log.names, "Retractor;") != NULL);
    ASSERT_TRUE(strstr(log.names, "Victim;") == NULL);
    assert_no_fact(facts, "Victim.hit");
    assert_bool_fact(facts, "_retracted_A", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

/*
 * Task A9: the anchored test(f(args)) CE (upstream grl.rs L75-80) evaluates
 * the function call and truthiness-tests the result (to_bool, types.rs L106:
 * Bool as-is, String non-empty, Number != 0.0, Integer != 0, Null -> false;
 * the Array/Object rows are unreachable locally because function results are
 * scalar re_value_t). Arithmetic-LHS comparisons need no test() rewrite here:
 * the parser already handles arithmetic in conditions natively. The typed
 * form $x: Type(conds) (grl.rs L82-87 typed_test_condition_regex) is bounded
 * to exists-semantics over the A2 prefix-heuristic candidates: inside the
 * form's own conds $x rewrites to the Type-rooted path (so $x.amount reads
 * the candidate's amount member), and the whole form is true iff SOME
 * candidate satisfies conds. $x outside its own form stays a parse error -
 * no binding escapes the form (upstream's RETE loader binding is not
 * replicated). Both forms classify purity like their contents (test() is
 * impure like every function-call condition; typed is pure iff its inner is
 * pure), stay off RETE, and report honest NOT_SUPPORTED to backward queries.
 */

static re_status_t a9_probe_call(re_engine_t *engine, re_facts_t *facts,
                                 const re_value_t *arguments, size_t argument_count,
                                 re_value_t *out_value, void *context) {
    (void)engine; (void)facts; (void)context;
    if (argument_count != 1u || arguments[0].type != RE_VALUE_INT64)
        return RE_STATUS_INVALID_ARGUMENT;
    switch (arguments[0].as.int64_value) {
    case 1: out_value->type = RE_VALUE_BOOL; out_value->as.boolean = 1; break;
    case 2: out_value->type = RE_VALUE_BOOL; out_value->as.boolean = 0; break;
    case 3: out_value->type = RE_VALUE_INT64; out_value->as.int64_value = 5; break;
    case 4: out_value->type = RE_VALUE_INT64; out_value->as.int64_value = 0; break;
    case 5: out_value->type = RE_VALUE_DOUBLE; out_value->as.double_value = 2.5; break;
    case 6: out_value->type = RE_VALUE_DOUBLE; out_value->as.double_value = 0.0; break;
    case 7: out_value->type = RE_VALUE_STRING; out_value->as.string.data = "x"; out_value->as.string.size = 1u; break;
    case 8: out_value->type = RE_VALUE_STRING; out_value->as.string.data = ""; out_value->as.string.size = 0u; break;
    default: out_value->type = RE_VALUE_NULL; out_value->as.int64_value = 0; break;
    }
    return RE_STATUS_OK;
}
static re_status_t a9_true_call(re_engine_t *engine, re_facts_t *facts,
                                const re_value_t *arguments, size_t argument_count,
                                re_value_t *out_value, void *context) {
    (void)engine; (void)facts; (void)arguments; (void)argument_count; (void)context;
    out_value->type = RE_VALUE_BOOL;
    out_value->as.boolean = 1;
    return RE_STATUS_OK;
}
static re_status_t a9_three_call(re_engine_t *engine, re_facts_t *facts,
                                 const re_value_t *arguments, size_t argument_count,
                                 re_value_t *out_value, void *context) {
    (void)engine; (void)facts; (void)arguments; (void)argument_count; (void)context;
    out_value->type = RE_VALUE_INT64;
    out_value->as.int64_value = 3;
    return RE_STATUS_OK;
}
static re_status_t a9_gate_probe_call(re_engine_t *engine, re_facts_t *facts,
                                      const re_value_t *arguments, size_t argument_count,
                                      re_value_t *out_value, void *context) {
    re_value_t probe = {RE_VALUE_NONE, {0}};
    (void)engine; (void)arguments; (void)argument_count; (void)context;
    out_value->type = RE_VALUE_BOOL;
    out_value->as.boolean = re_facts_get(facts, text("Gate"), &probe) == RE_STATUS_OK;
    return RE_STATUS_OK;
}
static re_status_t a9_cut_call(re_engine_t *engine, re_facts_t *facts,
                               const re_value_t *arguments, size_t argument_count,
                               re_value_t *out_value, void *context) {
    (void)engine; (void)facts; (void)arguments; (void)argument_count; (void)context;
    out_value->type = RE_VALUE_INT64;
    out_value->as.int64_value = 100;
    return RE_STATUS_OK;
}
/* Order-shaped object fact: an amount member plus an optional status member. */
static void set_typed_order(re_facts_t *facts, const char *name, int64_t amount,
                            const char *status) {
    re_value_handle_t *object = NULL;
    re_value_t member;
    ASSERT_EQ(re_value_create_object(facts, &object), RE_STATUS_OK);
    member = integer(amount);
    ASSERT_EQ(re_value_object_set(object, text("amount"), &member), RE_STATUS_OK);
    if (status != NULL) {
        member = string(status);
        ASSERT_EQ(re_value_object_set(object, text("status"), &member), RE_STATUS_OK);
    }
    ASSERT_EQ(re_facts_set_value(facts, text(name), object), RE_STATUS_OK);
    re_value_destroy(object);
}

TEST(test_ce_truthiness_table) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_function_t *probe_fn = NULL;
    re_function_descriptor_t probe_descriptor = {sizeof(probe_descriptor), RE_ABI_VERSION_MAJOR,
        {"a9probe", 7u}, a9_probe_call, NULL, NULL};
    re_value_t a = integer(1);
    ASSERT_EQ(re_engine_register_function(engine, &probe_descriptor, &probe_fn), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("A"), &a), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"T1\" { when test(a9probe(1)) then HitT1 = 1; }"
        "rule \"T2\" { when test(a9probe(2)) then HitT2 = 1; }"
        "rule \"T3\" { when test(a9probe(3)) then HitT3 = 1; }"
        "rule \"T4\" { when test(a9probe(4)) then HitT4 = 1; }"
        "rule \"T5\" { when test(a9probe(5)) then HitT5 = 1; }"
        "rule \"T6\" { when test(a9probe(6)) then HitT6 = 1; }"
        "rule \"T7\" { when test(a9probe(7)) then HitT7 = 1; }"
        "rule \"T8\" { when test(a9probe(8)) then HitT8 = 1; }"
        "rule \"T9\" { when test(a9probe(9)) then HitT9 = 1; }"
        "rule \"TC\" { when A == 1 and test(a9probe(1)) then HitTC = 1; }"
        "rule \"TN\" { when not test(a9probe(2)) then HitTN = 1; }");
    assert_int_fact(facts, "HitT1", 1);   /* Bool true */
    assert_no_fact(facts, "HitT2");       /* Bool false */
    assert_int_fact(facts, "HitT3", 1);   /* Integer 5 */
    assert_no_fact(facts, "HitT4");       /* Integer 0 */
    assert_int_fact(facts, "HitT5", 1);   /* Number 2.5 */
    assert_no_fact(facts, "HitT6");       /* Number 0.0 */
    assert_int_fact(facts, "HitT7", 1);   /* String "x" */
    assert_no_fact(facts, "HitT8");       /* String "" */
    assert_no_fact(facts, "HitT9");       /* Null */
    /* The form composes with logical operators like any other CE. */
    assert_int_fact(facts, "HitTC", 1);
    assert_int_fact(facts, "HitTN", 1);
    re_function_unregister(probe_fn);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(test_ce_builtin_len_truthiness_and_arg_miss) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t items[2];
    items[0] = integer(1); items[1] = integer(2);
    set_array_fact(facts, "Items", items, 2u);
    set_array_fact(facts, "EmptyArr", items, 0u);
    run_program(engine, facts,
        "rule \"Len\" { when test(len(Items)) then HitLen = 1; }"
        "rule \"Empty\" { when test(len(EmptyArr)) then HitEmpty = 1; }"
        "rule \"Miss\" { when test(len(Missing)) then HitMiss = 1; }");
    assert_int_fact(facts, "HitLen", 1);   /* 2 elements: Integer != 0 */
    assert_no_fact(facts, "HitEmpty");     /* 0: falsy */
    /* A missing fact-path argument absorbs to the built-in's miss result
     * (false for len), so the truthiness test fails instead of skipping. */
    assert_no_fact(facts, "HitMiss");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(test_ce_registered_and_dotted_function) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_function_t *true_fn = NULL;
    re_function_t *ok_fn = NULL;
    re_function_descriptor_t true_descriptor = {sizeof(true_descriptor), RE_ABI_VERSION_MAJOR,
        {"a9true", 6u}, a9_true_call, NULL, NULL};
    re_function_descriptor_t ok_descriptor = {sizeof(ok_descriptor), RE_ABI_VERSION_MAJOR,
        {"Util.ok", 7u}, a9_three_call, NULL, NULL};
    ASSERT_EQ(re_engine_register_function(engine, &true_descriptor, &true_fn), RE_STATUS_OK);
    ASSERT_EQ(re_engine_register_function(engine, &ok_descriptor, &ok_fn), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"Reg\" { when test(a9true()) then HitReg = 1; }"
        "rule \"Dot\" { when test(Util.ok()) then HitDot = 1; }"
        "rule \"Ghost\" { when test(a9ghost()) then HitGhost = 1; }");
    assert_int_fact(facts, "HitReg", 1);
    assert_int_fact(facts, "HitDot", 1);   /* truthiness applies to any result type */
    /* An unknown function inside test() keeps the historical behavior: the
     * rule is skipped (NOT_FOUND), not a load or run error. */
    assert_no_fact(facts, "HitGhost");
    re_function_unregister(ok_fn);
    re_function_unregister(true_fn);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(test_ce_rejects_non_call_forms) {
    re_program_t *program = NULL;
    /* Upstream anchors test() to a lone function call (grl.rs L75-80); the
     * general expression form and a trailing comparison stay parse errors. */
    ASSERT_EQ(re_program_load(NULL, text("rule \"Bad\" { when test() then R = 1; }"), NULL, &program),
              RE_STATUS_PARSE_ERROR);
    ASSERT_EQ(re_program_load(NULL, text("rule \"Bad\" { when test(1) then R = 1; }"), NULL, &program),
              RE_STATUS_PARSE_ERROR);
    ASSERT_EQ(re_program_load(NULL, text("rule \"Bad\" { when test(\"x\") then R = 1; }"), NULL, &program),
              RE_STATUS_PARSE_ERROR);
    ASSERT_EQ(re_program_load(NULL, text("rule \"Bad\" { when test(A.b) then R = 1; }"), NULL, &program),
              RE_STATUS_PARSE_ERROR);
    ASSERT_EQ(re_program_load(NULL, text("rule \"Bad\" { when test(len(Items) > 0) then R = 1; }"), NULL, &program),
              RE_STATUS_PARSE_ERROR);
    ASSERT_EQ(re_program_load(NULL, text("rule \"Bad\" { when test(len(Items)) == true then R = 1; }"), NULL, &program),
              RE_STATUS_PARSE_ERROR);
}

TEST(test_ce_keyword_does_not_eat_identifiers) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t t = integer(1);
    re_value_t tv = integer(2);
    ASSERT_EQ(re_facts_set(facts, text("test"), &t), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("testValue"), &tv), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"Bare\" { when test == 1 then HitBare = 1; }"
        "rule \"Longer\" { when testValue == 2 then HitLonger = 1; }");
    assert_int_fact(facts, "HitBare", 1);
    assert_int_fact(facts, "HitLonger", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(test_ce_condition_is_impure_first_pass_only) {
    /* re_condition_is_pure classifies test() impure like every function-call
     * condition: first-pass-only evaluation. W runs while Gate is missing;
     * Seed creates it; the pure control C observes the later pass, W does
     * not. */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_function_t *probe_fn = NULL;
    re_function_descriptor_t probe_descriptor = {sizeof(probe_descriptor), RE_ABI_VERSION_MAJOR,
        {"a9gateprobe", 11u}, a9_gate_probe_call, NULL, NULL};
    re_value_t a = integer(1);
    ASSERT_EQ(re_engine_register_function(engine, &probe_descriptor, &probe_fn), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("A"), &a), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"W\" { when test(a9gateprobe()) then HitW = 1; }"
        "rule \"C\" { when Gate == 1 then HitC = 1; }"
        "rule \"Seed\" { when A == 1 then Gate = 1; }");
    assert_no_fact(facts, "HitW");
    assert_int_fact(facts, "HitC", 1);
    re_function_unregister(probe_fn);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(test_ce_rules_stay_off_rete) {
    /* rete.c collect() only takes plain comparisons, so a test() condition
     * keeps the rule on the linear matcher (which still fires). */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_rete_network_t *network = NULL;
    re_value_t items[2];
    re_value_t b = integer(2);
    items[0] = integer(1); items[1] = integer(2);
    set_array_fact(facts, "Items", items, 2u);
    ASSERT_EQ(re_facts_set(facts, text("B"), &b), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"T\" { when test(len(Items)) and B == 2 then HitT = 1; }");
    assert_int_fact(facts, "HitT", 1);
    ASSERT_EQ(re_engine_rete_network(engine, &network), RE_STATUS_NOT_SUPPORTED);
    ASSERT_TRUE(network == NULL);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(test_ce_backward_query_is_not_supported) {
    /* The A2 backward boundary (condition_shape_supported +
     * machine_condition_matches) refuses test() conditions honestly. */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_query_t *query = NULL;
    re_value_t items[1];
    items[0] = integer(1);
    set_array_fact(facts, "Items", items, 1u);
    ASSERT_EQ(re_program_load(NULL, text(
        "rule \"Derive\" { when test(len(Items)) then Goal = 1; }"),
        NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("goal(\"Derive\")"), NULL, &query),
              RE_STATUS_NOT_SUPPORTED);
    ASSERT_TRUE(query == NULL);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(typed_form_exists_semantics_over_candidates) {
    /* $o: Order(conds) is true iff SOME Order* candidate satisfies conds. */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    set_typed_order(facts, "Order1", 150, "ok");
    set_typed_order(facts, "Order2", 50, "ok");
    run_program(engine, facts,
        "rule \"Big\" { when $o: Order(amount > 100) then HitBig = 1; }"
        "rule \"Huge\" { when $o: Order(amount > 1000) then HitHuge = 1; }"
        "rule \"None\" { when $w: Widget(amount > 1) then HitNone = 1; }");
    assert_int_fact(facts, "HitBig", 1);   /* Order1 satisfies */
    assert_no_fact(facts, "HitHuge");      /* no candidate does */
    assert_no_fact(facts, "HitNone");      /* no candidates at all */
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(typed_form_compound_conds_use_var_paths) {
    /* $x.field in atom-LHS position inside the form's own conds resolves
     * against the candidate: the expression-level typed-form dispatch only
     * intercepts the `$var : Type(` declaration shape, so `$o.amount` atoms
     * reach the operand-path scope rewrite (fix round 1, C1). The Bare rule
     * pins the mixing of bare and $x.-prefixed spellings in one conds list. */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    set_typed_order(facts, "Order1", 150, "ok");
    set_typed_order(facts, "Order2", 200, "bad");
    run_program(engine, facts,
        "rule \"Ok\" { when $o: Order($o.amount > 100 and $o.status == \"ok\") then HitOk = 1; }"
        "rule \"Bad\" { when $o: Order($o.amount > 100 and $o.status == \"bad\") then HitBad = 1; }"
        "rule \"Miss\" { when $o: Order($o.amount > 100 and $o.status == \"missing\") then HitMiss = 1; }"
        "rule \"Bare\" { when $o: Order(amount > 100 and $o.status == \"ok\") then HitBare = 1; }");
    assert_int_fact(facts, "HitOk", 1);    /* Order1 */
    assert_int_fact(facts, "HitBad", 1);   /* Order2 */
    assert_no_fact(facts, "HitMiss");
    assert_int_fact(facts, "HitBare", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(typed_form_var_lhs_missing_member_scores_candidate_false) {
    /* $o.field LHS references are per-candidate reads: a candidate lacking
     * the member scores false (absorbed miss) instead of failing the parse
     * or aborting the rule. Order1 has no amount member; Order2 does. */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    set_object_member(facts, "Order1", "tag", string("x"));
    set_typed_order(facts, "Order2", 150, NULL);
    run_program(engine, facts,
        "rule \"Hit\" { when $o: Order($o.amount > 100) then HitVar = 1; }"
        "rule \"Miss\" { when $o: Order($o.missing == 1) then HitMiss = 1; }");
    assert_int_fact(facts, "HitVar", 1);   /* Order1 skipped, Order2 matches */
    assert_no_fact(facts, "HitMiss");      /* no candidate carries `missing` */
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(typed_form_composes_with_quantifiers_and_conditions) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t ready = boolean(1);
    set_typed_order(facts, "Order1", 150, "ok");
    set_object_member(facts, "Alert1", "level", string("low"));
    ASSERT_EQ(re_facts_set(facts, text("Ready"), &ready), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"AndQ\" { when $o: Order(amount > 100) and forall(Alert.level == \"low\") then HitAndQ = 1; }"
        "rule \"OrQ\" { when exists(Score.value > 90) or $o: Order(amount > 100) then HitOrQ = 1; }"
        "rule \"Plain\" { when Ready == true and $o: Order(amount > 100) then HitPlain = 1; }"
        "rule \"Two\" { when $o: Order(amount > 100) and $p: Order(status == \"ok\") then HitTwo = 1; }");
    assert_int_fact(facts, "HitAndQ", 1);
    assert_int_fact(facts, "HitOrQ", 1);
    assert_int_fact(facts, "HitPlain", 1);
    assert_int_fact(facts, "HitTwo", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(typed_form_var_outside_form_is_a_parse_error) {
    re_program_t *program = NULL;
    /* The declared variable is scoped to its own conds; $o anywhere else in
     * a when-clause keeps the historical parse error for '$'. */
    ASSERT_EQ(re_program_load(NULL, text("rule \"Bad\" { when $o: Order(amount > 100) and $o.amount < 500 then R = 1; }"), NULL, &program),
              RE_STATUS_PARSE_ERROR);
    ASSERT_EQ(re_program_load(NULL, text("rule \"Bad\" { when $o.amount > 100 then R = 1; }"), NULL, &program),
              RE_STATUS_PARSE_ERROR);
    ASSERT_EQ(re_program_load(NULL, text("rule \"Bad\" { when $o: Order then R = 1; }"), NULL, &program),
              RE_STATUS_PARSE_ERROR);
    ASSERT_EQ(re_program_load(NULL, text("rule \"Bad\" { when $o: Order() then R = 1; }"), NULL, &program),
              RE_STATUS_PARSE_ERROR);
    ASSERT_EQ(re_program_load(NULL, text("rule \"Bad\" { when $: Order(amount > 1) then R = 1; }"), NULL, &program),
              RE_STATUS_PARSE_ERROR);
    ASSERT_EQ(re_program_load(NULL, text("rule \"Bad\" { when $o Order(amount > 1) then R = 1; }"), NULL, &program),
              RE_STATUS_PARSE_ERROR);
    ASSERT_EQ(re_program_load(NULL, text("rule \"Bad\" { when $o: Order(amount > 100 then R = 1; }"), NULL, &program),
              RE_STATUS_PARSE_ERROR);
}

TEST(typed_form_skips_nonconforming_lookalike_candidate) {
    /* The A2 prefix heuristic also matches lookalikes ("OrderBook"); a
     * candidate whose rebound field read misses scores false instead of
     * aborting the rule. OrderBook is inserted first so the scan hits it
     * before the conforming Order2. */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    set_object_member(facts, "OrderBook", "name", string("board"));
    set_typed_order(facts, "Order2", 150, NULL);
    run_program(engine, facts,
        "rule \"Any\" { when $o: Order(amount > 100) then HitAny = 1; }");
    assert_int_fact(facts, "HitAny", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(typed_form_pure_inner_reevaluates_across_passes) {
    /* The typed form is pure iff its inner is pure: Watch's first pass runs
     * while Order1 has no amount member (candidate miss -> false); only a
     * pure classification re-evaluates it after Seed writes the member. */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t a = integer(1);
    set_object_member(facts, "Order1", "tag", string("x"));
    ASSERT_EQ(re_facts_set(facts, text("A"), &a), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"Watch\" { when $o: Order(amount > 100) then HitWatch = 1; }"
        "rule \"Seed\" { when A == 1 then Order1.amount = 200; }");
    assert_int_fact(facts, "HitWatch", 1);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(typed_form_impure_inner_is_first_pass_only) {
    /* A function call inside the conds makes the typed form impure: the
     * first-pass false (50 > 100) is kept even after Seed raises the amount,
     * while the pure control rule observes the later pass. */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_function_t *cut_fn = NULL;
    re_function_descriptor_t cut_descriptor = {sizeof(cut_descriptor), RE_ABI_VERSION_MAJOR,
        {"a9cut", 5u}, a9_cut_call, NULL, NULL};
    re_value_t a = integer(1);
    set_typed_order(facts, "Order1", 50, NULL);
    ASSERT_EQ(re_facts_set(facts, text("A"), &a), RE_STATUS_OK);
    ASSERT_EQ(re_engine_register_function(engine, &cut_descriptor, &cut_fn), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"Watch\" { when $o: Order(amount > a9cut()) then HitWatch = 1; }"
        "rule \"Seed\" { when A == 1 then Order1.amount = 200; }"
        "rule \"C\" { when Order1.amount == 200 then HitC = 1; }");
    assert_no_fact(facts, "HitWatch");
    assert_int_fact(facts, "HitC", 1);
    re_function_unregister(cut_fn);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(typed_form_rules_stay_off_rete) {
    /* Like every non-plain-comparison condition, a typed form keeps the rule
     * on the linear matcher (which still fires). */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_rete_network_t *network = NULL;
    re_value_t b = integer(2);
    set_typed_order(facts, "Order1", 150, NULL);
    ASSERT_EQ(re_facts_set(facts, text("B"), &b), RE_STATUS_OK);
    run_program(engine, facts,
        "rule \"T\" { when $o: Order(amount > 100) and B == 2 then HitT = 1; }");
    assert_int_fact(facts, "HitT", 1);
    ASSERT_EQ(re_engine_rete_network(engine, &network), RE_STATUS_NOT_SUPPORTED);
    ASSERT_TRUE(network == NULL);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(typed_form_backward_query_is_not_supported) {
    /* The A2 backward boundary (condition_shape_supported +
     * machine_condition_matches) refuses typed conditions honestly. */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_query_t *query = NULL;
    set_typed_order(facts, "Order1", 150, NULL);
    ASSERT_EQ(re_program_load(NULL, text(
        "rule \"Derive\" { when $o: Order(amount > 100) then Goal = 1; }"),
        NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("goal(\"Derive\")"), NULL, &query),
              RE_STATUS_NOT_SUPPORTED);
    ASSERT_TRUE(query == NULL);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

/* A10 syntax sweep (upstream GRL_SYNTAX.md, tag f80a541): the remaining
 * doc-claimed constructs that NEITHER upstream's parser nor ours implements
 * stay parse errors here. Upstream grl.rs strips only full //-prefixed lines
 * inside when-clauses (clean_text) and has no block-comment handling despite
 * the doc claim; `enabled` is a Rule struct field with no GRL attribute;
 * object literals {k: v} and index syntax a[0] appear in the doc's type and
 * nested-access sections without parser support (upstream's index/slice live
 * only in the RETE multifield Rust API, not the GRL grammar). */
TEST(syntax_sweep_unsupported_constructs_parse_error) {
    re_program_t *program = NULL;
    /* Block comments: doc-claimed, not implemented upstream or locally. */
    ASSERT_EQ(re_program_load(NULL, text("/* doc */ rule \"R\" { when true then X = 1; }"), NULL, &program),
              RE_STATUS_PARSE_ERROR);
    /* Line comments: no local comment stripper either. */
    ASSERT_EQ(re_program_load(NULL, text("// doc\nrule \"R\" { when true then X = 1; }"), NULL, &program),
              RE_STATUS_PARSE_ERROR);
    /* The `enabled` rule attribute is struct-only upstream. */
    ASSERT_EQ(re_program_load(NULL, text("rule \"R\" enabled true { when true then X = 1; }"), NULL, &program),
              RE_STATUS_PARSE_ERROR);
    /* Object literals have no parser support. */
    ASSERT_EQ(re_program_load(NULL, text("rule \"R\" { when true then X = {\"a\": 1}; }"), NULL, &program),
              RE_STATUS_PARSE_ERROR);
    /* Index syntax has no GRL parser support. */
    ASSERT_EQ(re_program_load(NULL, text("rule \"R\" { when Items[0] > 1 then X = 1; }"), NULL, &program),
              RE_STATUS_PARSE_ERROR);
    ASSERT_TRUE(program == NULL);
}

TEST_MAIN_BEGIN()
    RUN_TEST(word_alias_eq_matches_and_ne_rejects);
    RUN_TEST(word_alias_ne_matches_on_difference);
    RUN_TEST(word_alias_relational_operators);
    RUN_TEST(word_alias_gt_lt_strict_sides);
    RUN_TEST(word_alias_not_contains);
    RUN_TEST(word_alias_not_contains_rejects_substring);
    RUN_TEST(word_alias_starts_with_ends_with);
    RUN_TEST(bool_literals_are_case_insensitive);
    RUN_TEST(null_literal_is_case_insensitive_and_compares_strictly);
    RUN_TEST(modulo_condition_and_result_typing);
    RUN_TEST(modulo_non_match);
    RUN_TEST(modulo_by_literal_zero_fails_parse_like_division);
    RUN_TEST(modulo_by_zero_fact_errors_the_run);
    RUN_TEST(string_concat_in_action_rhs);
    RUN_TEST(string_concat_uses_fact_values);
    RUN_TEST(string_concat_in_condition);
    RUN_TEST(string_concat_with_non_string_errors_the_run);
    RUN_TEST(equality_has_no_numeric_cross_coercion);
    RUN_TEST(relational_operators_coerce_numeric_strings);
    RUN_TEST(relational_operators_reject_non_numeric_strings);
    RUN_TEST(word_alias_not_contains_non_string_operands_are_true);
    RUN_TEST(relational_operators_reject_bool_and_null_operands);
    RUN_TEST(not_paren_negates_condition);
    RUN_TEST(not_paren_does_not_swallow_not_equal);
    RUN_TEST(exists_paren_rebinds_prefix_over_candidates);
    RUN_TEST(exists_paren_without_matching_candidate_does_not_fire);
    RUN_TEST(exists_paren_evaluates_compound_inner_per_candidate);
    RUN_TEST(exists_paren_plain_store_fallback_without_dotted_reference);
    RUN_TEST(forall_paren_requires_every_candidate);
    RUN_TEST(forall_paren_fails_on_one_bad_candidate);
    RUN_TEST(forall_paren_empty_candidate_set_is_vacuously_true);
    RUN_TEST(not_exists_paren_nested_negation);
    RUN_TEST(quantifier_paren_forms_compose_with_and_or);
    RUN_TEST(quantifier_paren_rejects_empty_inner);
    RUN_TEST(exists_paren_skips_nonconforming_lookalike_candidate);
    RUN_TEST(forall_paren_nonconforming_candidate_fails);
    RUN_TEST(exists_paren_unknown_function_still_errors);
    RUN_TEST(operator_stack_growth_keeps_stacked_prefixes);
    RUN_TEST(builtin_len_string_member_comparison_and_aliases);
    RUN_TEST(builtin_len_counts_array_fact_elements);
    RUN_TEST(builtin_len_wrong_type_and_arity_are_false);
    RUN_TEST(builtin_is_empty_string_null_and_array);
    RUN_TEST(builtin_arg_resolution_failure_is_false_not_skip);
    RUN_TEST(builtin_contains_string_substring_and_array_membership);
    RUN_TEST(builtin_exists_not_exists_quoted_paths);
    RUN_TEST(builtin_exists_bare_path_form_and_negation);
    RUN_TEST(exists_quantifier_vs_function_form_coexist);
    RUN_TEST(builtin_user_registered_function_overrides);
    RUN_TEST(builtin_functions_in_action_rhs);
    RUN_TEST(unknown_function_still_skips_the_rule);
    RUN_TEST(builtin_log_returns_joined_message);
    RUN_TEST(builtin_now_timestamp_return_unix_seconds_string);
    RUN_TEST(builtin_random_is_deterministic_per_engine_and_bounded);
    RUN_TEST(builtin_random_rejects_bad_max);
    RUN_TEST(builtin_format_percent_directives);
    RUN_TEST(builtin_format_brace_placeholders);
    RUN_TEST(builtin_format_percent_f_huge_double_truncates_safely);
    RUN_TEST(builtin_length_count_share_condition_len_semantics);
    RUN_TEST(builtin_sum_max_min_preserve_int64);
    RUN_TEST(builtin_folds_go_double_on_mixed_types);
    RUN_TEST(builtin_folds_skip_non_numeric_and_empty_args);
    RUN_TEST(builtin_round_floor_ceil_abs);
    RUN_TEST(builtin_math_wrong_type_or_arity_errors_the_run);
    RUN_TEST(builtin_includes_aliases_contains);
    RUN_TEST(builtin_startswith_endswith);
    RUN_TEST(builtin_lowercase_uppercase_trim);
    RUN_TEST(builtin_case_trim_require_an_argument);
    RUN_TEST(builtin_split_returns_debug_string);
    RUN_TEST(builtin_split_requires_two_args_and_nonempty_delimiter);
    RUN_TEST(builtin_join_delimiter_first);
    RUN_TEST(builtin_join_requires_two_args);
    RUN_TEST(builtin_functions_compose_in_rhs_and_method_args);
    RUN_TEST(builtin_folds_work_in_conditions);
    RUN_TEST(builtin_user_override_covers_action_builtins);
    RUN_TEST(multifield_count_compares_array_length);
    RUN_TEST(multifield_count_supports_every_comparison);
    RUN_TEST(multifield_count_strict_equality_rejects_double_literal);
    RUN_TEST(multifield_count_missing_field_is_zero);
    RUN_TEST(multifield_count_non_array_field_counts_as_one);
    RUN_TEST(multifield_first_and_last_require_non_empty_array);
    RUN_TEST(multifield_empty_true_for_empty_array_and_missing_field);
    RUN_TEST(multifield_not_empty_aliases);
    RUN_TEST(multifield_collect_true_iff_field_exists);
    RUN_TEST(multifield_nested_member_array);
    RUN_TEST(multifield_flat_dotted_key_wins);
    RUN_TEST(multifield_compounds_with_logical_operators);
    RUN_TEST(multifield_quantifier_interplay);
    RUN_TEST(multifield_conditions_are_pure_and_reevaluated);
    RUN_TEST(multifield_rules_stay_off_rete);
    RUN_TEST(multifield_read_set_records_array_path_premise);
    RUN_TEST(multifield_wrong_usage_parse_errors);
    RUN_TEST(accumulate_sum_over_instances_with_condition_filter);
    RUN_TEST(accumulate_result_gates_followup_condition);
    RUN_TEST(accumulate_count_counts_extracted_values);
    RUN_TEST(accumulate_average_and_avg_spelling_keys);
    RUN_TEST(accumulate_min_max);
    RUN_TEST(accumulate_empty_set_injects_zero);
    RUN_TEST(accumulate_unknown_type_injects_zero);
    RUN_TEST(accumulate_varless_pattern_counts_matching_instances);
    RUN_TEST(accumulate_bare_type_key_is_default_instance);
    RUN_TEST(accumulate_non_numeric_extracted_values_ignored);
    RUN_TEST(accumulate_condition_operators_scan_longest_first);
    RUN_TEST(accumulate_unknown_function_and_malformed_forms_parse_error);
    RUN_TEST(accumulate_injected_result_is_a_read_set_premise);
    RUN_TEST(accumulate_with_executor_attached_stays_correct);
    RUN_TEST(accumulate_recomputes_across_runs_without_drift);
    RUN_TEST(retract_gates_subsequent_rules_in_same_run);
    RUN_TEST(retract_flag_persists_across_runs_and_reassert_does_not_clear);
    RUN_TEST(retract_gates_quantifier_candidate_reads);
    RUN_TEST(retract_rejects_non_fact_argument);
    RUN_TEST(log_action_prints_joined_args_to_stdout);
    RUN_TEST(activate_agenda_group_switches_focus_mid_run);
    RUN_TEST(activate_agenda_group_requires_a_string_argument);
    RUN_TEST(workflow_actions_unhandled_are_not_supported);
    RUN_TEST(workflow_actions_dispatch_to_registered_function);
    RUN_TEST(unknown_bare_action_call_stays_a_parse_error);
    RUN_TEST(retract_gates_pending_rete_token_activation);
    RUN_TEST(test_ce_truthiness_table);
    RUN_TEST(test_ce_builtin_len_truthiness_and_arg_miss);
    RUN_TEST(test_ce_registered_and_dotted_function);
    RUN_TEST(test_ce_rejects_non_call_forms);
    RUN_TEST(test_ce_keyword_does_not_eat_identifiers);
    RUN_TEST(test_ce_condition_is_impure_first_pass_only);
    RUN_TEST(test_ce_rules_stay_off_rete);
    RUN_TEST(test_ce_backward_query_is_not_supported);
    RUN_TEST(typed_form_exists_semantics_over_candidates);
    RUN_TEST(typed_form_compound_conds_use_var_paths);
    RUN_TEST(typed_form_var_lhs_missing_member_scores_candidate_false);
    RUN_TEST(typed_form_composes_with_quantifiers_and_conditions);
    RUN_TEST(typed_form_var_outside_form_is_a_parse_error);
    RUN_TEST(typed_form_skips_nonconforming_lookalike_candidate);
    RUN_TEST(typed_form_pure_inner_reevaluates_across_passes);
    RUN_TEST(typed_form_impure_inner_is_first_pass_only);
    RUN_TEST(typed_form_rules_stay_off_rete);
    RUN_TEST(typed_form_backward_query_is_not_supported);
    RUN_TEST(syntax_sweep_unsupported_constructs_parse_error);
TEST_MAIN_END()
