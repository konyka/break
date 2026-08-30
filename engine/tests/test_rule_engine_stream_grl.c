#include "test_framework.h"
#include "../src/rule_engine/re_internal.h"
#include "../src/rule_engine/ir.h"
#include <stdio.h>
#include <string.h>

/*
 * GRL stream syntax (Sub-project C Task C3, upstream rust-rule-engine
 * v1.21.4 f80a541 src/parser/grl/stream_syntax.rs): the
 * `var: EventType from stream("name") [over window(<n> <unit>, kind)]`
 * condition form. This task lands parse + IR + honest evaluation gates;
 * evaluation wiring lands in C5, so every evaluation surface reports
 * RE_STATUS_NOT_SUPPORTED.
 *
 * Locked local decisions (see task-c3-report.md):
 * - The local when-grammar composes conditions with and/or (upstream spells
 *   them &&/||; the bare && token stays a parse error here as before). An
 *   AND whose BOTH immediate operands are stream-pattern CEs is the
 *   rejected upstream stream-join form (stream_syntax.rs:429 - the grammar
 *   exists but join_conditions is always empty and nothing consumes
 *   StreamJoinPattern).
 * - `session` is accepted as a LOCAL EXTENSION: upstream's GRL window-type
 *   parser rejects it (WindowType::Session exists in the Rust enum but is
 *   unreachable from GRL); the window duration doubles as the session
 *   timeout.
 * - Duration overflow (digits > u64, or the unit multiplication
 *   overflowing) is a parse error, matching the parser's integer-literal
 *   idiom (int32_literal); upstream's release-mode `value * 3600` wraps.
 */

static re_string_t text(const char *value) {
    re_string_t result = {value, strlen(value)};
    return result;
}

static re_status_t load(const char *source, re_program_t **out) {
    *out = NULL;
    return re_program_load(NULL, text(source), NULL, out);
}

static void assert_parse_error(const char *source) {
    re_program_t *program = NULL;
    ASSERT_EQ(load(source, &program), RE_STATUS_PARSE_ERROR);
    ASSERT_TRUE(program == NULL);
}

/* The root condition expression of the first rule (a lone stream pattern). */
static const re_ir_expr_t *root_condition(const re_program_t *program) {
    return &program->ir->exprs[program->ir->rules[0].condition];
}

TEST(stream_pattern_full_form_ir_round_trip) {
    re_program_t *program = NULL;
    const re_ir_expr_t *expr;
    ASSERT_EQ(load("rule \"S\" { when event: LoginEvent from stream(\"logins\") "
                   "over window(5 min, sliding) then R = 1; }", &program), RE_STATUS_OK);
    ASSERT_NOT_NULL(program);
    ASSERT_EQ(re_ir_validate(program->ir), RE_STATUS_OK);
    expr = root_condition(program);
    ASSERT_EQ(expr->kind, RE_EXPR_STREAM_PATTERN);
    ASSERT_EQ(expr->stream_var_size, 5u);
    ASSERT_TRUE(memcmp(expr->stream_var, "event", 5u) == 0);
    ASSERT_EQ(expr->stream_has_event_type, 1);
    ASSERT_EQ(expr->stream_event_type_size, 10u);
    ASSERT_TRUE(memcmp(expr->stream_event_type, "LoginEvent", 10u) == 0);
    ASSERT_EQ(expr->stream_name_size, 6u);
    ASSERT_TRUE(memcmp(expr->stream_name, "logins", 6u) == 0);
    ASSERT_EQ(expr->stream_has_window, 1);
    ASSERT_EQ(expr->stream_window_duration_ms, 300000u);
    ASSERT_EQ(expr->stream_window_kind, RE_STREAM_WINDOW_SLIDING);
    re_program_destroy(program);
}

TEST(stream_pattern_untyped_and_windowless) {
    re_program_t *program = NULL;
    const re_ir_expr_t *expr;
    /* A leading `from` is not consumed as the event type (upstream
     * stream_syntax.rs:216 checkpoint rewind). */
    ASSERT_EQ(load("rule \"S\" { when e: from stream(\"events\") then R = 1; }", &program),
              RE_STATUS_OK);
    expr = root_condition(program);
    ASSERT_EQ(expr->kind, RE_EXPR_STREAM_PATTERN);
    ASSERT_EQ(expr->stream_var_size, 1u);
    ASSERT_TRUE(memcmp(expr->stream_var, "e", 1u) == 0);
    ASSERT_EQ(expr->stream_has_event_type, 0);
    ASSERT_TRUE(expr->stream_event_type == NULL);
    ASSERT_EQ(expr->stream_name_size, 6u);
    ASSERT_TRUE(memcmp(expr->stream_name, "events", 6u) == 0);
    ASSERT_EQ(expr->stream_has_window, 0);
    re_program_destroy(program);
}

TEST(stream_pattern_typed_windowless) {
    re_program_t *program = NULL;
    const re_ir_expr_t *expr;
    ASSERT_EQ(load("rule \"S\" { when reading: TempReading from stream(\"sensors\") then R = 1; }",
                   &program), RE_STATUS_OK);
    expr = root_condition(program);
    ASSERT_EQ(expr->kind, RE_EXPR_STREAM_PATTERN);
    ASSERT_EQ(expr->stream_has_event_type, 1);
    ASSERT_EQ(expr->stream_event_type_size, 11u);
    ASSERT_TRUE(memcmp(expr->stream_event_type, "TempReading", 11u) == 0);
    ASSERT_EQ(expr->stream_has_window, 0);
    re_program_destroy(program);
}

TEST(stream_pattern_every_unit_spelling) {
    static const struct { const char *spelling; uint64_t expected_ms; } cases[] = {
        {"5 ms", 5u}, {"5 millisecond", 5u}, {"5 milliseconds", 5u},
        {"5 sec", 5000u}, {"5 second", 5000u}, {"5 seconds", 5000u},
        {"5 min", 300000u}, {"5 minute", 300000u}, {"5 minutes", 300000u},
        {"5 hour", 18000000u}, {"5 hours", 18000000u}
    };
    size_t i;
    for (i = 0u; i < sizeof(cases) / sizeof(cases[0]); ++i) {
        char source[160];
        re_program_t *program = NULL;
        const re_ir_expr_t *expr;
        snprintf(source, sizeof(source),
                 "rule \"S\" { when e: from stream(\"s\") over window(%s, tumbling) then R = 1; }",
                 cases[i].spelling);
        ASSERT_EQ(load(source, &program), RE_STATUS_OK);
        expr = root_condition(program);
        ASSERT_EQ(expr->kind, RE_EXPR_STREAM_PATTERN);
        ASSERT_EQ(expr->stream_has_window, 1);
        ASSERT_EQ(expr->stream_window_duration_ms, cases[i].expected_ms);
        ASSERT_EQ(expr->stream_window_kind, RE_STREAM_WINDOW_TUMBLING);
        re_program_destroy(program);
    }
}

TEST(stream_pattern_bad_unit_is_a_parse_error) {
    /* Units are exactly upstream's case-sensitive set (stream_syntax.rs
     * :166-179); anything else is a parse error. */
    assert_parse_error("rule \"S\" { when e: from stream(\"s\") over window(5 parsecs, sliding) then R = 1; }");
    assert_parse_error("rule \"S\" { when e: from stream(\"s\") over window(5 MIN, sliding) then R = 1; }");
    assert_parse_error("rule \"S\" { when e: from stream(\"s\") over window(5 Min, sliding) then R = 1; }");
    assert_parse_error("rule \"S\" { when e: from stream(\"s\") over window(5 hr, sliding) then R = 1; }");
    assert_parse_error("rule \"S\" { when e: from stream(\"s\") over window(5, sliding) then R = 1; }");
    /* Upstream requires multispace1 between the digits and the unit. */
    assert_parse_error("rule \"S\" { when e: from stream(\"s\") over window(5min, sliding) then R = 1; }");
}

TEST(stream_pattern_bad_window_type_is_a_parse_error) {
    assert_parse_error("rule \"S\" { when e: from stream(\"s\") over window(5 min, hopping) then R = 1; }");
    assert_parse_error("rule \"S\" { when e: from stream(\"s\") over window(5 min, Sliding) then R = 1; }");
    assert_parse_error("rule \"S\" { when e: from stream(\"s\") over window(5 min, sliding) then R = 1; } extra");
    assert_parse_error("rule \"S\" { when e: from stream(\"s\") over window(5 min sliding) then R = 1; }");
    assert_parse_error("rule \"S\" { when e: from stream(\"s\") over window(, sliding) then R = 1; }");
}

TEST(stream_pattern_empty_name_and_unterminated_quote_are_parse_errors) {
    /* The name is the chars up to the next '"' (take_while1(c != '"')):
     * empty fails the one-or-more rule, an unterminated quote runs out. */
    assert_parse_error("rule \"S\" { when e: from stream(\"\") then R = 1; }");
    assert_parse_error("rule \"S\" { when e: from stream(\"events) then R = 1; }");
    assert_parse_error("rule \"S\" { when e: from stream(\"events\" then R = 1; }");
    assert_parse_error("rule \"S\" { when e: from stream(events) then R = 1; }");
}

TEST(stream_pattern_session_kind_is_a_locked_local_extension) {
    re_program_t *program = NULL;
    const re_ir_expr_t *expr;
    /* Upstream GRL rejects `session` (parse_window_type accepts only
     * sliding|tumbling); locally it maps to RE_STREAM_WINDOW_SESSION with
     * the duration doubling as the session timeout. */
    ASSERT_EQ(load("rule \"S\" { when act: UserAction from stream(\"user-activity\") "
                   "over window(10 min, session) then R = 1; }", &program), RE_STATUS_OK);
    expr = root_condition(program);
    ASSERT_EQ(expr->kind, RE_EXPR_STREAM_PATTERN);
    ASSERT_EQ(expr->stream_has_window, 1);
    ASSERT_EQ(expr->stream_window_kind, RE_STREAM_WINDOW_SESSION);
    ASSERT_EQ(expr->stream_window_duration_ms, 600000u);
    re_program_destroy(program);
}

TEST(stream_pattern_zero_duration_is_allowed) {
    re_program_t *program = NULL;
    const re_ir_expr_t *expr;
    /* Upstream digit1 accepts 0; the has_window flag (not the duration)
     * carries the clause's presence. */
    ASSERT_EQ(load("rule \"S\" { when e: from stream(\"s\") over window(0 ms, sliding) then R = 1; }",
                   &program), RE_STATUS_OK);
    expr = root_condition(program);
    ASSERT_EQ(expr->stream_has_window, 1);
    ASSERT_EQ(expr->stream_window_duration_ms, 0u);
    re_program_destroy(program);
}

TEST(stream_pattern_duration_overflow_is_a_parse_error) {
    re_program_t *program = NULL;
    const re_ir_expr_t *expr;
    /* The parser's integer-literal idiom (int32_literal) rejects overflow:
     * digits beyond u64, and a unit multiplication that would overflow.
     * Upstream's release-mode `value * 3600` wraps silently. */
    assert_parse_error("rule \"S\" { when e: from stream(\"s\") over window(99999999999999999999 ms, sliding) then R = 1; }");
    assert_parse_error("rule \"S\" { when e: from stream(\"s\") over window(9999999999999999999 hour, sliding) then R = 1; }");
    /* u64 max in milliseconds still fits: digits == UINT64_MAX, factor 1. */
    ASSERT_EQ(load("rule \"S\" { when e: from stream(\"s\") over window(18446744073709551615 ms, sliding) then R = 1; }",
                   &program), RE_STATUS_OK);
    expr = root_condition(program);
    ASSERT_EQ(expr->stream_window_duration_ms, UINT64_MAX);
    re_program_destroy(program);
}

TEST(stream_pattern_join_of_two_patterns_is_a_parse_error) {
    re_program_t *program = NULL;
    /* The && stream join is vapor upstream (stream_syntax.rs:429); locally
     * an AND whose both immediate operands are stream patterns rejects at
     * parse, and the bare && token was never when-clause grammar. */
    assert_parse_error("rule \"S\" { when a: from stream(\"x\") and b: from stream(\"y\") then R = 1; }");
    assert_parse_error("rule \"S\" { when a: A from stream(\"x\") over window(5 min, sliding) and "
                       "b: B from stream(\"y\") over window(5 min, sliding) then R = 1; }");
    assert_parse_error("rule \"S\" { when a: from stream(\"x\") && b: from stream(\"y\") then R = 1; }");
    /* Disambiguation: a stream pattern composed with an ORDINARY condition
     * stays valid (evaluation is gated, not the parse). */
    ASSERT_EQ(load("rule \"S\" { when e: from stream(\"s\") and X == 1 then R = 1; }", &program),
              RE_STATUS_OK);
    re_program_destroy(program);
    ASSERT_EQ(load("rule \"S\" { when X == 1 and e: from stream(\"s\") then R = 1; }", &program),
              RE_STATUS_OK);
    re_program_destroy(program);
    /* ... and so is an OR of two stream patterns (only the && join is the
     * vapor form upstream). */
    ASSERT_EQ(load("rule \"S\" { when a: from stream(\"x\") or b: from stream(\"y\") then R = 1; }",
                   &program), RE_STATUS_OK);
    re_program_destroy(program);
}

TEST(stream_pattern_duplicate_var_in_one_rule_is_a_validation_error) {
    re_program_t *program = NULL;
    /* Var naming follows the existing binding idiom (alnum/underscore);
     * repeating a stream-pattern variable in one rule is a validation
     * error at parse time. */
    assert_parse_error("rule \"S\" { when e: from stream(\"a\") or e: from stream(\"b\") then R = 1; }");
    assert_parse_error("rule \"S\" { when e: A from stream(\"a\") or e: B from stream(\"b\") then R = 1; }");
    /* Distinct variables in one rule parse fine. */
    ASSERT_EQ(load("rule \"S\" { when e: from stream(\"a\") or f: from stream(\"b\") then R = 1; }",
                   &program), RE_STATUS_OK);
    re_program_destroy(program);
}

TEST(stream_pattern_dollar_prefix_is_not_the_stream_form) {
    /* The A9 typed form owns the `$var: Type(` shape; `$e: from ...` fails
     * there (no `(` after the "type") and never reaches the stream form. */
    assert_parse_error("rule \"S\" { when $e: from stream(\"s\") then R = 1; }");
    assert_parse_error("rule \"S\" { when $e: Event from stream(\"s\") then R = 1; }");
}

TEST(stream_pattern_from_keyword_case_rewind) {
    re_program_t *program = NULL;
    const re_ir_expr_t *expr;
    /* Only exactly "from" (case-sensitive) is the source keyword: "From"
     * is consumed as the event type and the missing keyword then fails. */
    assert_parse_error("rule \"S\" { when x: From stream(\"s\") then R = 1; }");
    /* A type that merely starts with "from" is a type, not the keyword. */
    ASSERT_EQ(load("rule \"S\" { when x: fromage from stream(\"s\") then R = 1; }", &program),
              RE_STATUS_OK);
    expr = root_condition(program);
    ASSERT_EQ(expr->stream_has_event_type, 1);
    ASSERT_EQ(expr->stream_event_type_size, 7u);
    ASSERT_TRUE(memcmp(expr->stream_event_type, "fromage", 7u) == 0);
    re_program_destroy(program);
}

TEST(stream_pattern_forward_run_is_not_supported) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    ASSERT_EQ(load("rule \"S\" { when e: from stream(\"events\") then R = 1; }", &program),
              RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    /* The parsed-but-not-yet-evaluable form reports the honest A2/A9 gate;
     * the wiring lands in C5. */
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_NOT_SUPPORTED);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(stream_pattern_mixed_with_ordinary_condition_is_not_supported) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_value_t one = {RE_VALUE_INT64, {.int64_value = 1}};
    ASSERT_EQ(re_facts_set(facts, text("X"), &one), RE_STATUS_OK);
    ASSERT_EQ(load("rule \"S\" { when X == 1 and e: LoginEvent from stream(\"s\") "
                   "over window(5 min, sliding) then R = 1; }", &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_NOT_SUPPORTED);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(stream_pattern_rules_stay_off_rete) {
    /* collect() only admits ANDs of fact/literal comparisons, so a stream
     * pattern keeps the rule RETE-ineligible (the honest NOT_SUPPORTED
     * eligibility gate); the engine reports no primary network. */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_facts_t *rete_facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_rete_network_t *network = NULL;
    ASSERT_EQ(load("rule \"S\" { when e: from stream(\"s\") then R = 1; }", &program),
              RE_STATUS_OK);
    ASSERT_EQ(re_rete_network_create_rule(rete_facts, &program->rules[0], NULL, &network),
              RE_STATUS_NOT_SUPPORTED);
    ASSERT_TRUE(network == NULL);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_NOT_SUPPORTED);
    ASSERT_EQ(re_engine_rete_network(engine, &network), RE_STATUS_NOT_SUPPORTED);
    ASSERT_TRUE(network == NULL);
    re_facts_destroy(rete_facts);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(stream_pattern_backward_query_is_not_supported) {
    /* The backward boundary refuses the stream pattern honestly, via both
     * the goal("...") spelling and the bare rule-name goal. */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_query_t *query = NULL;
    ASSERT_EQ(load("rule \"Derive\" { when e: from stream(\"events\") then Goal = 1; }",
                   &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("goal(\"Derive\")"), NULL, &query),
              RE_STATUS_NOT_SUPPORTED);
    ASSERT_TRUE(query == NULL);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("Derive"), NULL, &query),
              RE_STATUS_NOT_SUPPORTED);
    ASSERT_TRUE(query == NULL);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(stream_pattern_query_when_gate_is_not_supported) {
    /* The A7 query-block when-gate evaluates through the same IR matcher,
     * so it reports the same honest gate. */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    ASSERT_EQ(load("query \"Q\" { goal: X == 1; when: e: from stream(\"events\"); "
                   "on-success: { S = 1; } }", &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run_query(engine, facts, text("Q")), RE_STATUS_NOT_SUPPORTED);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST_MAIN_BEGIN()
    RUN_TEST(stream_pattern_full_form_ir_round_trip);
    RUN_TEST(stream_pattern_untyped_and_windowless);
    RUN_TEST(stream_pattern_typed_windowless);
    RUN_TEST(stream_pattern_every_unit_spelling);
    RUN_TEST(stream_pattern_bad_unit_is_a_parse_error);
    RUN_TEST(stream_pattern_bad_window_type_is_a_parse_error);
    RUN_TEST(stream_pattern_empty_name_and_unterminated_quote_are_parse_errors);
    RUN_TEST(stream_pattern_session_kind_is_a_locked_local_extension);
    RUN_TEST(stream_pattern_zero_duration_is_allowed);
    RUN_TEST(stream_pattern_duration_overflow_is_a_parse_error);
    RUN_TEST(stream_pattern_join_of_two_patterns_is_a_parse_error);
    RUN_TEST(stream_pattern_duplicate_var_in_one_rule_is_a_validation_error);
    RUN_TEST(stream_pattern_dollar_prefix_is_not_the_stream_form);
    RUN_TEST(stream_pattern_from_keyword_case_rewind);
    RUN_TEST(stream_pattern_forward_run_is_not_supported);
    RUN_TEST(stream_pattern_mixed_with_ordinary_condition_is_not_supported);
    RUN_TEST(stream_pattern_rules_stay_off_rete);
    RUN_TEST(stream_pattern_backward_query_is_not_supported);
    RUN_TEST(stream_pattern_query_when_gate_is_not_supported);
TEST_MAIN_END()
