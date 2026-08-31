#include "test_framework.h"
#include <rule_engine/rule_engine.h>
#include <stdlib.h>
#include <string.h>

/*
 * Example-family coverage (Task D2, upstream rust-rule-engine v1.21.4
 * f80a5419847436f8095be6a9953c69b38a6ae052, Cargo.toml [[example]] list -
 * 29 examples in seven family directories, re-verified against the pinned
 * manifest 2026-08-30). Coverage means a local behavioral equivalent
 * exercised by the named test; no local Rust examples exist. Each new smoke
 * below names the upstream example(s) it covers. Families whose machinery is
 * already exercised end-to-end by an existing suite are mapped there with a
 * representative test instead of gaining a duplicated smoke; families with
 * no local machinery get a documented not_applicable, never a fake test.
 *
 * FAMILY MAPPING TABLE
 *
 * 01-getting-started: grule_demo, fraud_detection, expression_demo,
 *     method_calls_demo, in_operator_demo, string_methods_demo
 *   -> THIS SUITE ex01_fraud_detection_forward_chain_smoke (the
 *      fraud_detection/grule_demo end-to-end shape: salience-ordered rules
 *      over structured facts chaining through derived facts in one run).
 *   -> expression_demo: test_rule_engine_grl_surface.c
 *      (word_alias_relational_operators; the operator/alias/coercion surface).
 *   -> method_calls_demo: test_rule_engine_grl_semantics.c
 *      (method_dispatches_registered_function).
 *   -> in_operator_demo: test_rule_engine.c
 *      (array_membership_covers_positive_negative_and_mixed_scalar_types).
 *   -> string_methods_demo: test_rule_engine_grl_surface.c
 *      (word_alias_starts_with_ends_with) plus the string built-ins and the
 *      D1 plugin-helper pins in test_rule_engine_plugin_parity.c.
 *
 * 02-rete-engine: rete_demo, rete_grl_demo, rete_typed_facts_demo,
 *     rete_deffacts_demo, tms_demo
 *   -> GRL-into-RETE: re_engine_install compiles eligible GRL rules into
 *      per-rule RETE networks; pinned by test_rule_engine.c
 *      (public_two_condition_join_uses_rete_network) and
 *      (public_rete_supports_bounded_boolean_expression_and_nested_fact).
 *      No new smoke: one would duplicate those pins.
 *   -> incremental RETE: test_rule_engine_rete_incremental.c
 *      (unrelated_updates_preserve_memories_and_related_changes_propagate).
 *   -> rete_deffacts_demo: test_rule_engine_grl_semantics.c
 *      (deffacts_load_seeds_facts_and_rules_fire).
 *   -> tms_demo: test_rule_engine_tms.c
 *      (tms_distinguishes_explicit_and_logical_facts).
 *
 * 03-advanced-features: accumulate_grl_demo, conflict_resolution_demo,
 *     grl_no_loop_demo, action_handlers_grl_demo, rule_templates_demo,
 *     streaming_with_rules_demo
 *   -> accumulate_grl_demo: test_rule_engine_grl_surface.c A6 accumulate CE
 *      tests (accumulate_sum_over_instances_with_condition_filter).
 *   -> conflict_resolution_demo: bounded salience + activation groups,
 *      test_rule_engine_agenda.c (salience_order_preserved_across_cycles).
 *   -> grl_no_loop_demo: test_rule_engine.c
 *      (no_loop_and_lock_on_active_are_enforced).
 *   -> action_handlers_grl_demo: THIS SUITE
 *      ex03_action_handlers_registered_function_smoke. Upstream's arbitrary
 *      bare `then ActionName(...)` spelling is locally a locked parse error
 *      for non-whitelisted names (test_rule_engine_grl_surface.c
 *      unknown_bare_action_call_stays_a_parse_error); the whitelisted-trio
 *      dispatch is pinned by workflow_actions_dispatch_to_registered_function,
 *      and the general host-handler equivalent is the
 *      re_engine_register_function expression dispatch exercised below.
 *   -> rule_templates_demo: test_rule_engine_grl_semantics.c
 *      (template_generated_rule_parses_and_fires) - instantiate, parse,
 *      install, run already end-to-end; no new smoke (no duplication).
 *   -> streaming_with_rules_demo: test_rule_engine_stream_eval.c
 *      (stream_eval_injection_facts_and_rule_fires) - the pinned
 *      WindowEventCount > 5 parity usage (upstream src/streaming/engine.rs
 *      :478-481) over re_engine_stream_run, plus the registered-stream CE
 *      path (stream_eval_grl_typed_and_untyped_binding_fires). No new smoke:
 *      the brief's suggested WindowEventCount test is that pin verbatim.
 *
 * 04-streaming: NOT PRESENT at f80a541 as an example family. No
 *     examples/04-* directory exists upstream. session_window_demo DOES
 *     exist at f80a541 as examples/session_window_demo.rs (6382 bytes) at
 *     the examples/ root - an auto-discovered example target (no
 *     autoexamples = false in Cargo.toml) that is simply absent from the
 *     pinned 29-entry [[example]] manifest; the task-brief 04-* mention
 *     does not exist upstream. The streaming machinery lives under 03's
 *     streaming_with_rules_demo above and the C-phase suites
 *     (test_rule_engine_stream_ext.c, test_rule_engine_stream_grl.c,
 *     test_rule_engine_stream_eval.c). Session windows are a locked local
 *     extension (stream_pattern_session_kind_is_a_locked_local_extension).
 *     not_applicable as a family; no fake tests.
 *
 * 05-performance: quick_engine_comparison, parallel_engine_demo,
 *     memory_usage_comparison
 *   -> not_applicable as a ctest: quick_engine_comparison /
 *      memory_usage_comparison map to the deterministic local bench baseline
 *      (engine/tools/rule_engine_bench.c gated by
 *      engine/scripts/rule_engine_bench_regression.cmake) - a baseline
 *      regression, not a correctness test.
 *   -> parallel_engine_demo: not_applicable - upstream's parallel engine is
 *      sub-project-B-documented vapor (no live upstream parallel execution
 *      path); the optional local C11 executor (read-only condition
 *      evaluation) is covered by test_rule_engine_executor_stress.c when
 *      RULE_ENGINE_ENABLE_C11_PARALLEL is on.
 *
 * 07-advanced-rete: rete_p3_incremental, rete_ul_drools_style
 *   -> rete_p3_incremental: test_rule_engine_rete_incremental.c
 *      (compiled_network_persists_across_runs).
 *   -> rete_ul_drools_style: not_applicable - full RETE-UL shared alpha/beta
 *      machinery is upstream vapor (docs/rule_engine_upstream.yml
 *      rete-ul-tms-persistent-agenda row: no shared alpha/beta machinery in
 *      any upstream execution path).
 *
 * 09-backward-chaining: simple_query_demo, ecommerce_approval_demo,
 *     medical_diagnosis_demo, grl_query_demo, proof_graph_cache_demo
 *   -> simple_query_demo: test_rule_engine_backward.c
 *      (base_rule_proves_from_fact).
 *   -> ecommerce_approval_demo / grl_query_demo: THIS SUITE
 *      ex09_grl_query_backward_smoke (a GRL query block driving the bounded
 *      backward machine over chained derivation rules, approval-decision
 *      shape); the dispatch machinery is pinned in
 *      test_rule_engine_query_blocks.c.
 *   -> medical_diagnosis_demo: chained derivation and negation-as-failure,
 *      test_rule_engine.c
 *      (backward_query_recurses_through_rule_name_conditions) and
 *      test_rule_engine_backward_ext.c
 *      (query_not_succeeds_when_subgoal_unprovable).
 *   -> proof_graph_cache_demo: test_rule_engine_backward_ext.c
 *      (shared_graph_second_query_hits_cache,
 *      mutation_invalidates_cached_proof).
 *
 * 10-module-system: smart_home_modules, phase3_demo
 *   -> covered_bounded (the brief's "no local module system" premise is
 *      corrected with evidence): a bounded single-source module system
 *      EXISTS - `defmodule` blocks with export all/none and import,
 *      cycle/unknown-import rejection (engine/src/rule_engine/parser.c
 *      :1819-1823), dotted Module::Rule association, and
 *      re_program_set_module_focus with runtime visibility gating
 *      (engine/src/rule_engine/engine.c:721). Representative:
 *      test_rule_engine.c private_modules_control_qualified_rule_visibility
 *      (imported-export visibility at run and query time) and
 *      private_modules_reject_cycles_and_resolve_exports. No new smoke: a
 *      family-shaped test would duplicate those pins.
 *   -> residual not_applicable: upstream's example-level module packaging
 *      beyond the bounded single-source visibility semantics
 *      (smart_home_modules / phase3_demo extras) is not replicated; the
 *      conformance row lands in D4.
 *
 * The new-smoke count (3) sits below the brief's ~5-8 expectation because the
 * RETE (02), streaming (03/04), templates, no-loop, accumulate, and module
 * (10) shapes already carry the end-to-end pins named above, and the brief
 * forbids duplicating pinned behavior.
 */

static re_string_t text(const char *value) { return (re_string_t){value, strlen(value)}; }
static re_value_t integer(int64_t value) { return (re_value_t){RE_VALUE_INT64, {.int64_value = value}}; }
static re_value_t string(const char *value) { return (re_value_t){RE_VALUE_STRING, {.string = {value, strlen(value)}}}; }

static void install_source(re_engine_t *engine, const char *source) {
    re_program_t *program = NULL;
    ASSERT_EQ(re_program_load(NULL, text(source), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
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

static void assert_int_fact(re_facts_t *facts, const char *name, int64_t expected) {
    re_value_t out = {RE_VALUE_NONE, {0}};
    ASSERT_EQ(re_facts_get(facts, text(name), &out), RE_STATUS_OK);
    ASSERT_EQ(out.type, RE_VALUE_INT64);
    ASSERT_EQ(out.as.int64_value, expected);
}
static void assert_string_fact(re_facts_t *facts, const char *name, const char *expected) {
    re_value_t out = {RE_VALUE_NONE, {0}};
    ASSERT_EQ(re_facts_get(facts, text(name), &out), RE_STATUS_OK);
    ASSERT_EQ(out.type, RE_VALUE_STRING);
    ASSERT_EQ(out.as.string.size, strlen(expected));
    ASSERT_TRUE(memcmp(out.as.string.data, expected, out.as.string.size) == 0);
}

/* Covers upstream examples/01-getting-started/fraud_detection.rs (and the
 * grule_demo load/run basics): a salience-ordered rule set scores a
 * transaction and a critical-score rule blocks it. Upstream builds the rules
 * programmatically; the local equivalent machinery is one GRL program over
 * structured facts chaining through derived facts inside a single run. The
 * scoring writes are idempotent (separate score facts), so the outcome is
 * independent of refraction details. */
TEST(ex01_fraud_detection_forward_chain_smoke) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    const char *const tx_keys[2] = {"Amount", "Location"};
    const char *const acct_keys[2] = {"DailyLimit", "LastLoginLocation"};
    re_value_t tx_vals[2];
    re_value_t acct_vals[2];
    re_value_t zero = integer(0);
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    tx_vals[0] = integer(5000);
    tx_vals[1] = string("FOREIGN");
    acct_vals[0] = integer(3000);
    acct_vals[1] = string("DOMESTIC");
    set_object_fact(facts, "Transaction", tx_keys, tx_vals, 2u);
    set_object_fact(facts, "Account", acct_keys, acct_vals, 2u);
    ASSERT_EQ(re_facts_set(facts, text("FraudScore"), &zero), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("LocationScore"), &zero), RE_STATUS_OK);
    install_source(engine,
        "rule \"HighAmountAlert\" salience 10 {"
        " when Transaction.Amount > Account.DailyLimit then FraudScore = 50; }"
        "rule \"ForeignLocationAlert\" salience 8 {"
        " when Transaction.Location == \"FOREIGN\" and Account.LastLoginLocation == \"DOMESTIC\""
        " then LocationScore = 30; }"
        "rule \"CriticalFraudAlert\" salience 15 {"
        " when FraudScore + LocationScore >= 70 then Status = \"BLOCKED\"; }");
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    /* Both scoring rules fired, and the derived scores activated the
     * critical rule mid-run (recognize-act chaining). */
    assert_int_fact(facts, "FraudScore", 50);
    assert_int_fact(facts, "LocationScore", 30);
    assert_string_fact(facts, "Status", "BLOCKED");
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

/* ---- action_handlers_grl_demo machinery -------------------------------- */

typedef struct payment_log_t {
    unsigned calls;
    double amount;
    char method[32];
    size_t method_size;
} payment_log_t;

/* The host action handler (the demo's ProcessPayment shape): resolved fact
 * arguments in, a computed value out, side effects recorded in the context. */
static re_status_t process_payment(re_engine_t *engine, re_facts_t *facts,
                                   const re_value_t *arguments, size_t argument_count,
                                   re_value_t *out_value, void *context) {
    payment_log_t *log = context;
    double amount = 0.0;
    (void)engine;
    (void)facts;
    if (argument_count != 2u) return RE_STATUS_INVALID_ARGUMENT;
    if (arguments[0].type == RE_VALUE_INT64) amount = (double)arguments[0].as.int64_value;
    else if (arguments[0].type == RE_VALUE_DOUBLE) amount = arguments[0].as.double_value;
    else return RE_STATUS_INVALID_ARGUMENT;
    if (arguments[1].type != RE_VALUE_STRING) return RE_STATUS_INVALID_ARGUMENT;
    log->calls++;
    log->amount = amount;
    log->method_size = arguments[1].as.string.size < sizeof(log->method)
        ? arguments[1].as.string.size : sizeof(log->method);
    memcpy(log->method, arguments[1].as.string.data, log->method_size);
    /* 2.9% processing fee, net amount returned (the demo's business logic). */
    out_value->type = RE_VALUE_DOUBLE;
    out_value->as.double_value = amount * (1.0 - 0.029);
    return RE_STATUS_OK;
}

/* Covers upstream examples/03-advanced-features/action_handlers_grl_demo.rs:
 * host-registered handlers invoked from rule actions over structured facts.
 * Local mapping: arbitrary bare action names stay a parse error, so the
 * handler rides re_engine_register_function as an action expression call;
 * its result chains into a follow-up rule in the same run. */
TEST(ex03_action_handlers_registered_function_smoke) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_function_t *function = NULL;
    payment_log_t log;
    const char *const pay_keys[3] = {"status", "amount", "method"};
    re_value_t pay_vals[3];
    re_function_descriptor_t descriptor = {sizeof(descriptor), RE_ABI_VERSION_MAJOR,
        {"ProcessPayment", 14u}, process_payment, NULL, &log};
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    memset(&log, 0, sizeof(log));
    pay_vals[0] = string("verified");
    pay_vals[1] = integer(3500);
    pay_vals[2] = string("credit_card");
    set_object_fact(facts, "Payment", pay_keys, pay_vals, 3u);
    ASSERT_EQ(re_engine_register_function(engine, &descriptor, &function), RE_STATUS_OK);
    install_source(engine,
        "rule \"SettlePayment\" {"
        " when Payment.status == \"verified\""
        " then Receipt = ProcessPayment(Payment.amount, Payment.method); }"
        "rule \"HighValueReceipt\" {"
        " when Receipt > 1000 then Settled = 1; }");
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    /* The handler ran once with the resolved fact arguments... */
    ASSERT_EQ(log.calls, 1u);
    ASSERT_FLOAT_EQ(log.amount, 3500.0, 1e-9);
    ASSERT_EQ(log.method_size, 11u);
    ASSERT_TRUE(memcmp(log.method, "credit_card", 11u) == 0);
    /* ...its returned net amount (3500 * 0.971) landed as a fact and drove
     * the follow-up rule. */
    {
        re_value_t out = {RE_VALUE_NONE, {0}};
        ASSERT_EQ(re_facts_get(facts, text("Receipt"), &out), RE_STATUS_OK);
        ASSERT_EQ(out.type, RE_VALUE_DOUBLE);
        ASSERT_FLOAT_EQ(out.as.double_value, 3398.5, 1e-9);
    }
    assert_int_fact(facts, "Settled", 1);
    re_function_unregister(function);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

/* Covers upstream examples/09-backward-chaining/grl_query_demo.rs and
 * ecommerce_approval_demo.rs: a GRL query block drives the bounded backward
 * machine over chained derivation rules and records the outcome through the
 * on-success/on-failure action blocks. A rule name referenced as a fact in a
 * condition recurses the proof (the
 * backward_query_recurses_through_rule_name_conditions idiom). Bounded local
 * shape: the backward condition matcher reads FLAT fact names only
 * (backward.c backward_operand_goal goes through re_facts_get, not the
 * forward matcher's object traversal), so the demo's dotted names are flat
 * keys here. */
TEST(ex09_grl_query_backward_smoke) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_value_t score = integer(720);
    re_value_t total = integer(300);
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    install_source(engine,
        "rule \"Creditworthy\" { when Customer.score >= 700 then CreditOk = true; }"
        "rule \"OrderApproved\" {"
        " when Creditworthy == true and Order.total <= 500 then Approved = true; }"
        "query \"CheckOrder\" {"
        " goal: OrderApproved;"
        " max-depth: 8;"
        " on-success: { Decision = 1; }"
        " on-failure: { Decision = 0; } }");
    /* Approved path: score 720 proves Creditworthy, total 300 fits. */
    ASSERT_EQ(re_facts_set(facts, text("Customer.score"), &score), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("Order.total"), &total), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run_query(engine, facts, text("CheckOrder")), RE_STATUS_OK);
    assert_int_fact(facts, "Decision", 1);
    /* Declined path on a fresh fact set (a distinct facts identity can never
     * serve a stale shared-graph hit): score 650 disproves the chain. */
    re_facts_destroy(facts);
    facts = re_facts_create(NULL, NULL);
    ASSERT_NOT_NULL(facts);
    score = integer(650);
    ASSERT_EQ(re_facts_set(facts, text("Customer.score"), &score), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("Order.total"), &total), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run_query(engine, facts, text("CheckOrder")), RE_STATUS_OK);
    assert_int_fact(facts, "Decision", 0);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST_MAIN_BEGIN()
    RUN_TEST(ex01_fraud_detection_forward_chain_smoke);
    RUN_TEST(ex03_action_handlers_registered_function_smoke);
    RUN_TEST(ex09_grl_query_backward_smoke);
TEST_MAIN_END()
