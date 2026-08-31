#include "test_framework.h"
#include "../src/rule_engine/re_internal.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

/*
 * Stream rule evaluation (Sub-project C Task C5, upstream rust-rule-engine
 * v1.21.4 f80a541 src/streaming/engine.rs): the engine's stream registry,
 * the window-fact injection run (re_engine_stream_run), and the GRL
 * stream-pattern CE evaluation wired in ir_eval.c.
 *
 * Locked local decisions (see task-c5-report.md):
 * - The registry is name-keyed borrowed window handles, capped at 16;
 *   re-registering a name REPLACES the binding; unregister is a no-op for
 *   unknown names and never destroys the window; re_engine_destroy releases
 *   only the registry's name copies.
 * - Injection writes the four Window* facts always (upstream
 *   engine.rs:347-353) plus "<name>Sum/Average/Min/Max" per event name with
 *   at least one numeric retained value (the local "field" is the event
 *   name); every write goes through re_facts_set and therefore bumps
 *   facts->mutation_serial.
 * - The stream-pattern CE has exists semantics over the registered window's
 *   filtered retained events; the type filter matches the event NAME and
 *   `var` denotes the event's scalar value. An UNREGISTERED stream reports
 *   RE_STATUS_NOT_SUPPORTED (the C3 gate pinned by
 *   test_rule_engine_stream_grl.c), NOT the brief's NOT_FOUND - the forward
 *   run loop swallows NOT_FOUND as an ordinary non-match, which would
 *   silently flip that pinned behavior.
 * - Backward chaining on stream CEs stays RE_STATUS_NOT_SUPPORTED (the C3
 *   ARITHMETIC-operand sentinel on the AST node is kept).
 */

static re_string_t text(const char *value) {
    re_string_t result = {value, strlen(value)};
    return result;
}

static re_status_t load(const char *source, re_program_t **out) {
    *out = NULL;
    return re_program_load(NULL, text(source), NULL, out);
}

static re_stream_window_t *make_window(re_engine_t *engine, re_stream_window_kind_t kind,
                                       uint64_t retention_ms) {
    re_stream_window_t *window = NULL;
    re_stream_window_options_t options = {sizeof(options), RE_STREAM_WINDOW_ABI_VERSION,
        kind, RE_LATE_EVENT_DROP, retention_ms, 64u, 65536u, 0u, 0u};
    if (re_stream_window_create_v1(engine, &options, &window) != RE_STATUS_OK) return NULL;
    return window;
}

static re_value_t int_value(int64_t value) {
    re_value_t result = {RE_VALUE_INT64, {.int64_value = value}};
    return result;
}

static re_value_t double_value(double value) {
    re_value_t result = {RE_VALUE_DOUBLE, {.double_value = value}};
    return result;
}

static re_value_t string_value(const char *value) {
    re_value_t result = {RE_VALUE_STRING, {.string = {value, strlen(value)}}};
    return result;
}

/* Registers window, installs a one-rule program whose condition reads
 * WindowEventCount, runs re_engine_stream_run and reports Fired == 1. */
TEST(stream_eval_injection_facts_and_rule_fires) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_stream_window_t *window = make_window(engine, RE_STREAM_WINDOW_SLIDING, 100000u);
    re_program_t *program = NULL;
    re_value_t probe;
    int64_t i;
    ASSERT_NOT_NULL(window);
    for (i = 1u; i <= 6u; ++i) {
        re_value_t value = int_value(i);
        ASSERT_EQ(re_stream_window_record_v1(window, (uint64_t)i * 1000u, text("T"), &value),
                  RE_STATUS_OK);
    }
    /* Upstream parity usage (f80a541 src/streaming/engine.rs:478-481). */
    ASSERT_EQ(load("rule \"S\" { when WindowEventCount > 5 then Fired = 1; }", &program),
              RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_stream_run(engine, facts, window), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("WindowEventCount"), &probe), RE_STATUS_OK);
    ASSERT_EQ(probe.type, RE_VALUE_DOUBLE);
    ASSERT_FLOAT_EQ(probe.as.double_value, 6.0, 0.0001);
    ASSERT_EQ(re_facts_get(facts, text("WindowStartTime"), &probe), RE_STATUS_OK);
    ASSERT_EQ(probe.type, RE_VALUE_INT64);
    ASSERT_EQ(probe.as.int64_value, 1000);
    ASSERT_EQ(re_facts_get(facts, text("WindowEndTime"), &probe), RE_STATUS_OK);
    ASSERT_EQ(probe.as.int64_value, 6000);
    ASSERT_EQ(re_facts_get(facts, text("WindowDurationMs"), &probe), RE_STATUS_OK);
    ASSERT_EQ(probe.as.int64_value, 5000);
    ASSERT_EQ(re_facts_get(facts, text("TSum"), &probe), RE_STATUS_OK);
    ASSERT_EQ(probe.type, RE_VALUE_DOUBLE);
    ASSERT_FLOAT_EQ(probe.as.double_value, 21.0, 0.0001);
    ASSERT_EQ(re_facts_get(facts, text("TAverage"), &probe), RE_STATUS_OK);
    ASSERT_FLOAT_EQ(probe.as.double_value, 3.5, 0.0001);
    ASSERT_EQ(re_facts_get(facts, text("TMin"), &probe), RE_STATUS_OK);
    ASSERT_FLOAT_EQ(probe.as.double_value, 1.0, 0.0001);
    ASSERT_EQ(re_facts_get(facts, text("TMax"), &probe), RE_STATUS_OK);
    ASSERT_FLOAT_EQ(probe.as.double_value, 6.0, 0.0001);
    ASSERT_EQ(re_facts_get(facts, text("Fired"), &probe), RE_STATUS_OK);
    ASSERT_EQ(probe.as.int64_value, 1);
    re_stream_window_destroy(window);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(stream_eval_injection_per_name_aggregates_exclude_non_numeric) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_stream_window_t *window = make_window(engine, RE_STREAM_WINDOW_SLIDING, 100000u);
    re_value_t probe;
    re_value_t five = int_value(5);
    re_value_t two = double_value(2.0);
    re_value_t nine = int_value(9);
    re_value_t x = string_value("x");
    re_value_t y = string_value("y");
    ASSERT_NOT_NULL(window);
    ASSERT_EQ(re_stream_window_record_v1(window, 10u, text("num"), &five), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 20u, text("num"), &two), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 30u, text("num"), &nine), RE_STATUS_OK);
    /* A non-numeric value under a numeric name is excluded from that name's
     * fold but still counts toward WindowEventCount. */
    ASSERT_EQ(re_stream_window_record_v1(window, 40u, text("num"), &x), RE_STATUS_OK);
    /* A name with only non-numeric events gets NO aggregate facts. */
    ASSERT_EQ(re_stream_window_record_v1(window, 50u, text("txt"), &y), RE_STATUS_OK);
    ASSERT_EQ(re_engine_stream_run(engine, facts, window), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("WindowEventCount"), &probe), RE_STATUS_OK);
    ASSERT_FLOAT_EQ(probe.as.double_value, 5.0, 0.0001);
    ASSERT_EQ(re_facts_get(facts, text("numSum"), &probe), RE_STATUS_OK);
    ASSERT_FLOAT_EQ(probe.as.double_value, 16.0, 0.0001);
    ASSERT_EQ(re_facts_get(facts, text("numAverage"), &probe), RE_STATUS_OK);
    ASSERT_FLOAT_EQ(probe.as.double_value, 16.0 / 3.0, 0.0001);
    ASSERT_EQ(re_facts_get(facts, text("numMin"), &probe), RE_STATUS_OK);
    ASSERT_FLOAT_EQ(probe.as.double_value, 2.0, 0.0001);
    ASSERT_EQ(re_facts_get(facts, text("numMax"), &probe), RE_STATUS_OK);
    ASSERT_FLOAT_EQ(probe.as.double_value, 9.0, 0.0001);
    ASSERT_EQ(re_facts_get(facts, text("txtSum"), &probe), RE_STATUS_NOT_FOUND);
    ASSERT_EQ(re_facts_get(facts, text("txtAverage"), &probe), RE_STATUS_NOT_FOUND);
    ASSERT_EQ(re_facts_get(facts, text("txtMin"), &probe), RE_STATUS_NOT_FOUND);
    ASSERT_EQ(re_facts_get(facts, text("txtMax"), &probe), RE_STATUS_NOT_FOUND);
    re_stream_window_destroy(window);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(stream_eval_injection_empty_window) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_stream_window_t *window = make_window(engine, RE_STREAM_WINDOW_SLIDING, 100000u);
    re_program_t *program = NULL;
    re_value_t probe;
    ASSERT_NOT_NULL(window);
    ASSERT_EQ(load("rule \"E\" { when WindowEventCount < 1 then Empty = 1; }", &program),
              RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_stream_run(engine, facts, window), RE_STATUS_OK);
    /* All four Window* facts exist even when 0 (upstream always injects). */
    ASSERT_EQ(re_facts_get(facts, text("WindowEventCount"), &probe), RE_STATUS_OK);
    ASSERT_EQ(probe.type, RE_VALUE_DOUBLE);
    ASSERT_FLOAT_EQ(probe.as.double_value, 0.0, 0.0001);
    ASSERT_EQ(re_facts_get(facts, text("WindowStartTime"), &probe), RE_STATUS_OK);
    ASSERT_EQ(probe.as.int64_value, 0);
    ASSERT_EQ(re_facts_get(facts, text("WindowEndTime"), &probe), RE_STATUS_OK);
    ASSERT_EQ(probe.as.int64_value, 0);
    ASSERT_EQ(re_facts_get(facts, text("WindowDurationMs"), &probe), RE_STATUS_OK);
    ASSERT_EQ(probe.as.int64_value, 0);
    ASSERT_EQ(re_facts_get(facts, text("Empty"), &probe), RE_STATUS_OK);
    ASSERT_EQ(probe.as.int64_value, 1);
    re_stream_window_destroy(window);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(stream_eval_injection_overwrites_stale_facts) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_stream_window_t *window = make_window(engine, RE_STREAM_WINDOW_SLIDING, 100000u);
    re_value_t probe;
    re_value_t stale = int_value(999);
    re_value_t seven = int_value(7);
    re_value_t one = int_value(1);
    re_value_t two = int_value(2);
    ASSERT_NOT_NULL(window);
    ASSERT_EQ(re_facts_set(facts, text("WindowEventCount"), &stale), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("TSum"), &stale), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("Extra"), &seven), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 10u, text("T"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 20u, text("T"), &two), RE_STATUS_OK);
    ASSERT_EQ(re_engine_stream_run(engine, facts, window), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("WindowEventCount"), &probe), RE_STATUS_OK);
    ASSERT_EQ(probe.type, RE_VALUE_DOUBLE);
    ASSERT_FLOAT_EQ(probe.as.double_value, 2.0, 0.0001);
    ASSERT_EQ(re_facts_get(facts, text("TSum"), &probe), RE_STATUS_OK);
    ASSERT_EQ(probe.type, RE_VALUE_DOUBLE);
    ASSERT_FLOAT_EQ(probe.as.double_value, 3.0, 0.0001);
    /* Unrelated facts are untouched. */
    ASSERT_EQ(re_facts_get(facts, text("Extra"), &probe), RE_STATUS_OK);
    ASSERT_EQ(probe.as.int64_value, 7);
    re_stream_window_destroy(window);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(stream_eval_injection_bumps_mutation_serial) {
    /* B2 coherence pin: every injection write is a re_facts_set, so the
     * facts mutation serial moves and the shared proof graph can never serve
     * a stale backward result across two stream runs. No program is
     * installed, so ONLY the injection writes move the serial: 4 Window*
     * facts + 4 aggregate facts for the single numeric name. */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_stream_window_t *window = make_window(engine, RE_STREAM_WINDOW_SLIDING, 100000u);
    re_value_t one = int_value(1);
    re_value_t two = int_value(2);
    uint64_t serial_before;
    ASSERT_NOT_NULL(window);
    ASSERT_EQ(re_stream_window_record_v1(window, 10u, text("T"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 20u, text("T"), &two), RE_STATUS_OK);
    serial_before = facts->mutation_serial;
    ASSERT_EQ(re_engine_stream_run(engine, facts, window), RE_STATUS_OK);
    ASSERT_EQ(facts->mutation_serial, serial_before + 8u);
    re_stream_window_destroy(window);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(stream_eval_injection_tumbling_bucket_bounds) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_stream_window_t *window = make_window(engine, RE_STREAM_WINDOW_TUMBLING, 1000u);
    re_value_t probe;
    re_value_t five = int_value(5);
    ASSERT_NOT_NULL(window);
    /* ts 1500 lands in bucket 1: the bounds are [1000, 2000). */
    ASSERT_EQ(re_stream_window_record_v1(window, 1500u, text("E"), &five), RE_STATUS_OK);
    ASSERT_EQ(re_engine_stream_run(engine, facts, window), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("WindowEventCount"), &probe), RE_STATUS_OK);
    ASSERT_FLOAT_EQ(probe.as.double_value, 1.0, 0.0001);
    ASSERT_EQ(re_facts_get(facts, text("WindowStartTime"), &probe), RE_STATUS_OK);
    ASSERT_EQ(probe.as.int64_value, 1000);
    ASSERT_EQ(re_facts_get(facts, text("WindowEndTime"), &probe), RE_STATUS_OK);
    ASSERT_EQ(probe.as.int64_value, 2000);
    ASSERT_EQ(re_facts_get(facts, text("WindowDurationMs"), &probe), RE_STATUS_OK);
    ASSERT_EQ(probe.as.int64_value, 1000);
    ASSERT_EQ(re_facts_get(facts, text("ESum"), &probe), RE_STATUS_OK);
    ASSERT_FLOAT_EQ(probe.as.double_value, 5.0, 0.0001);
    re_stream_window_destroy(window);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(stream_eval_injection_empty_tumbling_reports_bucket_zero_span) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_stream_window_t *window = make_window(engine, RE_STREAM_WINDOW_TUMBLING, 1000u);
    re_value_t probe;
    ASSERT_NOT_NULL(window);
    /* A tumbling window reports its current bucket's span even while it holds
     * no events (documented on re_engine_stream_run): the untouched bucket 0
     * is [0, retention). */
    ASSERT_EQ(re_engine_stream_run(engine, facts, window), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("WindowEventCount"), &probe), RE_STATUS_OK);
    ASSERT_EQ(probe.type, RE_VALUE_DOUBLE);
    ASSERT_FLOAT_EQ(probe.as.double_value, 0.0, 0.0001);
    ASSERT_EQ(re_facts_get(facts, text("WindowStartTime"), &probe), RE_STATUS_OK);
    ASSERT_EQ(probe.as.int64_value, 0);
    ASSERT_EQ(re_facts_get(facts, text("WindowEndTime"), &probe), RE_STATUS_OK);
    ASSERT_EQ(probe.as.int64_value, 1000);
    ASSERT_EQ(re_facts_get(facts, text("WindowDurationMs"), &probe), RE_STATUS_OK);
    ASSERT_EQ(probe.as.int64_value, 1000);
    re_stream_window_destroy(window);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(stream_eval_injection_session_span) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_stream_window_t *window = make_window(engine, RE_STREAM_WINDOW_SESSION, 10000u);
    re_value_t probe;
    re_value_t one = int_value(1);
    re_value_t three = int_value(3);
    ASSERT_NOT_NULL(window);
    /* One session (gap 1000 <= the 10000 timeout): the injected span is
     * [session start, session_end) = [first retained event ts, last event ts
     * + timeout) (stream_eval.c stream_window_bounds). */
    ASSERT_EQ(re_stream_window_record_v1(window, 1000u, text("A"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 2000u, text("A"), &three), RE_STATUS_OK);
    ASSERT_EQ(re_engine_stream_run(engine, facts, window), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("WindowEventCount"), &probe), RE_STATUS_OK);
    ASSERT_FLOAT_EQ(probe.as.double_value, 2.0, 0.0001);
    ASSERT_EQ(re_facts_get(facts, text("WindowStartTime"), &probe), RE_STATUS_OK);
    ASSERT_EQ(probe.as.int64_value, 1000);
    ASSERT_EQ(re_facts_get(facts, text("WindowEndTime"), &probe), RE_STATUS_OK);
    ASSERT_EQ(probe.as.int64_value, 12000);
    ASSERT_EQ(re_facts_get(facts, text("WindowDurationMs"), &probe), RE_STATUS_OK);
    ASSERT_EQ(probe.as.int64_value, 11000);
    ASSERT_EQ(re_facts_get(facts, text("ASum"), &probe), RE_STATUS_OK);
    ASSERT_FLOAT_EQ(probe.as.double_value, 4.0, 0.0001);
    re_stream_window_destroy(window);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(stream_eval_registry_register_replace_unregister) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_window_t *first = make_window(engine, RE_STREAM_WINDOW_SLIDING, 1000u);
    re_stream_window_t *second = make_window(engine, RE_STREAM_WINDOW_SLIDING, 1000u);
    re_value_t one = int_value(1);
    ASSERT_NOT_NULL(first);
    ASSERT_NOT_NULL(second);
    ASSERT_EQ(re_engine_stream_register(engine, text("s"), first), RE_STATUS_OK);
    ASSERT_TRUE(re_engine_stream_lookup(engine, "s", 1u) == first);
    /* Re-registering the same name REPLACES the binding. */
    ASSERT_EQ(re_engine_stream_register(engine, text("s"), second), RE_STATUS_OK);
    ASSERT_TRUE(re_engine_stream_lookup(engine, "s", 1u) == second);
    ASSERT_EQ(re_engine_stream_unregister(engine, text("s")), RE_STATUS_OK);
    ASSERT_TRUE(re_engine_stream_lookup(engine, "s", 1u) == NULL);
    /* Unregister is a documented no-op for unknown names and never destroys
     * the window. */
    ASSERT_EQ(re_engine_stream_unregister(engine, text("s")), RE_STATUS_OK);
    ASSERT_EQ(re_engine_stream_unregister(engine, text("never-registered")), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(second, 10u, text("T"), &one), RE_STATUS_OK);
    re_stream_window_destroy(first);
    re_stream_window_destroy(second);
    re_engine_destroy(engine);
}

TEST(stream_eval_registry_invalid_arguments) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_stream_window_t *window = make_window(engine, RE_STREAM_WINDOW_SLIDING, 1000u);
    ASSERT_NOT_NULL(window);
    ASSERT_EQ(re_engine_stream_register(NULL, text("s"), window), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_engine_stream_register(engine, text("s"), NULL), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_engine_stream_register(engine, (re_string_t){NULL, 0u}, window),
              RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_engine_stream_register(engine, text(""), window), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_engine_stream_unregister(NULL, text("s")), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_engine_stream_unregister(engine, (re_string_t){NULL, 0u}),
              RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_engine_stream_run(NULL, facts, window), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_engine_stream_run(engine, NULL, window), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_engine_stream_run(engine, facts, NULL), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(engine->stream_registry_count, 0u);
    re_stream_window_destroy(window);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(stream_eval_registry_cap_is_16) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_window_t *window = make_window(engine, RE_STREAM_WINDOW_SLIDING, 1000u);
    char name[8];
    size_t i;
    ASSERT_NOT_NULL(window);
    for (i = 0u; i < RE_STREAM_REGISTRY_CAP; ++i) {
        snprintf(name, sizeof(name), "s%lu", (unsigned long)i);
        ASSERT_EQ(re_engine_stream_register(engine, text(name), window), RE_STATUS_OK);
    }
    ASSERT_EQ(engine->stream_registry_count, RE_STREAM_REGISTRY_CAP);
    ASSERT_EQ(re_engine_stream_register(engine, text("s-overflow"), window), RE_STATUS_LIMIT);
    /* Unregistering one entry frees a slot again. */
    ASSERT_EQ(re_engine_stream_unregister(engine, text("s3")), RE_STATUS_OK);
    ASSERT_EQ(re_engine_stream_register(engine, text("s-overflow"), window), RE_STATUS_OK);
    re_stream_window_destroy(window);
    re_engine_destroy(engine);
}

typedef struct busy_probe_t {
    re_stream_window_t *window;
    re_status_t register_status;
    re_status_t unregister_status;
    int ran;
} busy_probe_t;

static re_status_t busy_probe(re_engine_t *engine, re_facts_t *facts,
                              const re_rule_event_t *event, void *context) {
    busy_probe_t *probe = context;
    (void)facts;
    (void)event;
    probe->ran = 1;
    probe->register_status = re_engine_stream_register(engine, text("mid"), probe->window);
    probe->unregister_status = re_engine_stream_unregister(engine, text("mid"));
    return RE_STATUS_OK;
}

TEST(stream_eval_registry_is_busy_while_running) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_stream_window_t *window = make_window(engine, RE_STREAM_WINDOW_SLIDING, 1000u);
    re_program_t *program = NULL;
    busy_probe_t probe;
    re_callbacks_t callbacks;
    re_value_t one = int_value(1);
    ASSERT_NOT_NULL(window);
    probe.window = window;
    probe.register_status = RE_STATUS_OK;
    probe.unregister_status = RE_STATUS_OK;
    probe.ran = 0;
    callbacks.action = busy_probe;
    callbacks.context = &probe;
    ASSERT_EQ(load("rule \"R\" { when X == 1 then Y = 2; }", &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("X"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, &callbacks), RE_STATUS_OK);
    ASSERT_EQ(probe.ran, 1);
    ASSERT_EQ(probe.register_status, RE_STATUS_BUSY);
    ASSERT_EQ(probe.unregister_status, RE_STATUS_BUSY);
    ASSERT_EQ(engine->stream_registry_count, 0u);
    re_stream_window_destroy(window);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(stream_eval_engine_destroy_keeps_registered_window) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_window_t *window = make_window(engine, RE_STREAM_WINDOW_SLIDING, 1000u);
    re_value_t one = int_value(1);
    ASSERT_NOT_NULL(window);
    ASSERT_EQ(re_engine_stream_register(engine, text("s"), window), RE_STATUS_OK);
    re_engine_destroy(engine);
    /* The registered window is borrowed: it stays usable after the engine
     * is gone. */
    ASSERT_EQ(re_stream_window_record_v1(window, 10u, text("T"), &one), RE_STATUS_OK);
    re_stream_window_destroy(window);
}

TEST(stream_eval_grl_typed_and_untyped_binding_fires) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_stream_window_t *window = make_window(engine, RE_STREAM_WINDOW_SLIDING, 100000u);
    re_program_t *program = NULL;
    re_value_t probe;
    re_value_t forty_two = int_value(42);
    re_value_t one = int_value(1);
    ASSERT_NOT_NULL(window);
    ASSERT_EQ(load("rule \"T\" { when e: TempReading from stream(\"sensors\") then FiredT = 1; }"
                   "rule \"U\" { when e: from stream(\"sensors\") then FiredU = 1; }"
                   "rule \"M\" { when X == 1 and e: TempReading from stream(\"sensors\") then FiredM = 1; }",
                   &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_stream_register(engine, text("sensors"), window), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("X"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 10u, text("TempReading"), &forty_two),
              RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("FiredT"), &probe), RE_STATUS_OK);
    ASSERT_EQ(probe.as.int64_value, 1);
    ASSERT_EQ(re_facts_get(facts, text("FiredU"), &probe), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("FiredM"), &probe), RE_STATUS_OK);
    /* A second run over the same registered window re-fires (the agenda
     * resets between runs): the CE re-reads live window state. */
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    re_stream_window_destroy(window);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(stream_eval_grl_type_filter_excludes_other_names) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_stream_window_t *window = make_window(engine, RE_STREAM_WINDOW_SLIDING, 100000u);
    re_program_t *program = NULL;
    re_value_t probe;
    re_value_t one = int_value(1);
    ASSERT_NOT_NULL(window);
    ASSERT_EQ(load("rule \"T\" { when e: TempReading from stream(\"sensors\") then FiredT = 1; }"
                   "rule \"U\" { when e: from stream(\"sensors\") then FiredU = 1; }",
                   &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_stream_register(engine, text("sensors"), window), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 10u, text("Other"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    /* The typed CE matches the event NAME: no TempReading event, no fire. */
    ASSERT_EQ(re_facts_get(facts, text("FiredT"), &probe), RE_STATUS_NOT_FOUND);
    ASSERT_EQ(re_facts_get(facts, text("FiredU"), &probe), RE_STATUS_OK);
    ASSERT_EQ(probe.as.int64_value, 1);
    re_stream_window_destroy(window);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(stream_eval_grl_sliding_clause_filters_old_events) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    /* ACCEPT + 5s lateness so the in-span event recorded after the watermark
     * moved still lands (the late-record path stays out of this test). */
    re_stream_window_options_t options = {sizeof(options), RE_STREAM_WINDOW_ABI_VERSION,
        RE_STREAM_WINDOW_SLIDING, RE_LATE_EVENT_ACCEPT, 200000u, 64u, 65536u, 5000u, 0u};
    re_stream_window_t *window = NULL;
    re_program_t *program = NULL;
    re_value_t probe;
    re_value_t one = int_value(1);
    ASSERT_EQ(re_stream_window_create_v1(engine, &options, &window), RE_STATUS_OK);
    ASSERT_EQ(load("rule \"W\" { when e: E from stream(\"s\") over window(5 sec, sliding) then FiredW = 1; }"
                   "rule \"A\" { when e: E from stream(\"s\") then FiredA = 1; }",
                   &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_stream_register(engine, text("s"), window), RE_STATUS_OK);
    /* Watermark 100000: the sliding clause scans [95000, 100000]; the only
     * E event sits at ts 10. */
    ASSERT_EQ(re_stream_window_record_v1(window, 10u, text("E"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 100000u, text("X"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("FiredW"), &probe), RE_STATUS_NOT_FOUND);
    /* Without a window clause every retained event qualifies. */
    ASSERT_EQ(re_facts_get(facts, text("FiredA"), &probe), RE_STATUS_OK);
    ASSERT_EQ(probe.as.int64_value, 1);
    /* An E event inside the clause's span flips the windowed rule too. */
    ASSERT_EQ(re_stream_window_record_v1(window, 99000u, text("E"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("FiredW"), &probe), RE_STATUS_OK);
    ASSERT_EQ(probe.as.int64_value, 1);
    re_stream_window_destroy(window);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(stream_eval_grl_sliding_clause_lower_bound_is_closed) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_stream_window_t *window = make_window(engine, RE_STREAM_WINDOW_SLIDING, 200000u);
    re_program_t *program = NULL;
    re_value_t probe;
    re_value_t one = int_value(1);
    ASSERT_NOT_NULL(window);
    ASSERT_EQ(load("rule \"B\" { when e: Edge from stream(\"s\") over window(5 sec, sliding) then FiredB = 1; }"
                   "rule \"O\" { when e: Out from stream(\"s\") over window(5 sec, sliding) then FiredO = 1; }",
                   &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_stream_register(engine, text("s"), window), RE_STATUS_OK);
    /* Watermark 100000: the clause span is [95000, 100000] - an event exactly
     * at watermark - duration IS included (the closed lower bound,
     * stream_scope_contains' >=), one 1ms below it is not. */
    ASSERT_EQ(re_stream_window_record_v1(window, 94999u, text("Out"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 95000u, text("Edge"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 100000u, text("X"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("FiredB"), &probe), RE_STATUS_OK);
    ASSERT_EQ(probe.as.int64_value, 1);
    ASSERT_EQ(re_facts_get(facts, text("FiredO"), &probe), RE_STATUS_NOT_FOUND);
    re_stream_window_destroy(window);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(stream_eval_grl_tumbling_zero_duration_is_invalid_argument) {
    /* Bucket size 0 is undefined: over a REGISTERED stream the CE reports the
     * honest RE_STATUS_INVALID_ARGUMENT (stream_pattern_match rejects before
     * scanning) - the disclosed divergence from upstream's modulo-by-zero
     * corner, previously unpinned. */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_stream_window_t *window = make_window(engine, RE_STREAM_WINDOW_SLIDING, 100000u);
    re_program_t *program = NULL;
    re_value_t one = int_value(1);
    ASSERT_NOT_NULL(window);
    ASSERT_EQ(load("rule \"Z\" { when e: E from stream(\"s\") over window(0 ms, tumbling) then FiredZ = 1; }",
                   &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_stream_register(engine, text("s"), window), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 10u, text("E"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_INVALID_ARGUMENT);
    re_stream_window_destroy(window);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(stream_eval_grl_tumbling_clause_current_bucket) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_stream_window_t *window = make_window(engine, RE_STREAM_WINDOW_SLIDING, 100000u);
    re_program_t *program = NULL;
    re_value_t probe;
    re_value_t one = int_value(1);
    ASSERT_NOT_NULL(window);
    ASSERT_EQ(load("rule \"OT\" { when e: Old from stream(\"s\") over window(1 sec, tumbling) then FiredOT = 1; }"
                   "rule \"OA\" { when e: Old from stream(\"s\") then FiredOA = 1; }"
                   "rule \"NT\" { when e: New from stream(\"s\") over window(1 sec, tumbling) then FiredNT = 1; }",
                   &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_stream_register(engine, text("s"), window), RE_STATUS_OK);
    /* Watermark 1500: the current 1-second bucket is [1000, 2000); the Old
     * event sits in bucket 0. */
    ASSERT_EQ(re_stream_window_record_v1(window, 500u, text("Old"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 1500u, text("New"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("FiredOT"), &probe), RE_STATUS_NOT_FOUND);
    ASSERT_EQ(re_facts_get(facts, text("FiredOA"), &probe), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("FiredNT"), &probe), RE_STATUS_OK);
    ASSERT_EQ(probe.as.int64_value, 1);
    re_stream_window_destroy(window);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(stream_eval_grl_session_clause_end_to_end) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_stream_window_t *window = make_window(engine, RE_STREAM_WINDOW_SESSION, 10000u);
    re_program_t *program = NULL;
    re_value_t probe;
    re_value_t one = int_value(1);
    re_value_t two = int_value(2);
    re_value_t three = int_value(3);
    ASSERT_NOT_NULL(window);
    /* `session` is the locked local extension (C3): the clause duration is
     * the session timeout. */
    ASSERT_EQ(load("rule \"SU\" { when a: UserAction from stream(\"act\") over window(10 sec, session) then FiredU = 1; }"
                   "rule \"SA\" { when a: from stream(\"act\") over window(10 sec, session) then FiredA = 1; }",
                   &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_stream_register(engine, text("act"), window), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 1000u, text("UserAction"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 2000u, text("UserAction"), &two), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("FiredU"), &probe), RE_STATUS_OK);
    ASSERT_EQ(probe.as.int64_value, 1);
    ASSERT_EQ(re_facts_get(facts, text("FiredA"), &probe), RE_STATUS_OK);
    /* A record past the session end (2000 + 10000) opens a new session and
     * drops the old one: the UserAction events are gone. */
    ASSERT_EQ(re_stream_window_record_v1(window, 50000u, text("Other"), &three), RE_STATUS_OK);
    re_facts_destroy(facts);
    facts = re_facts_create(NULL, NULL);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    ASSERT_EQ(re_facts_get(facts, text("FiredU"), &probe), RE_STATUS_NOT_FOUND);
    ASSERT_EQ(re_facts_get(facts, text("FiredA"), &probe), RE_STATUS_OK);
    ASSERT_EQ(probe.as.int64_value, 1);
    re_stream_window_destroy(window);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(stream_eval_grl_unregistered_stream_is_not_supported) {
    /* The pinned C3 gate (test_rule_engine_stream_grl.c) stays: an
     * unregistered stream is the honest NOT_SUPPORTED evaluation error. */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    ASSERT_EQ(load("rule \"S\" { when e: from stream(\"events\") then R = 1; }", &program),
              RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_NOT_SUPPORTED);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST(stream_eval_backward_on_stream_ce_stays_not_supported) {
    /* Backward chaining never consults the registry: the ARITHMETIC-operand
     * sentinel on the AST node gates both goal spellings honestly, even when
     * the stream is registered and would match forward. */
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_stream_window_t *window = make_window(engine, RE_STREAM_WINDOW_SLIDING, 100000u);
    re_program_t *program = NULL;
    re_query_t *query = NULL;
    re_value_t one = int_value(1);
    ASSERT_NOT_NULL(window);
    ASSERT_EQ(load("rule \"Derive\" { when e: from stream(\"events\") then Goal = 1; }",
                   &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_stream_register(engine, text("events"), window), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 10u, text("E"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("goal(\"Derive\")"), NULL, &query),
              RE_STATUS_NOT_SUPPORTED);
    ASSERT_TRUE(query == NULL);
    ASSERT_EQ(re_engine_query_bounded(engine, facts, text("Derive"), NULL, &query),
              RE_STATUS_NOT_SUPPORTED);
    ASSERT_TRUE(query == NULL);
    re_stream_window_destroy(window);
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

TEST_MAIN_BEGIN()
    RUN_TEST(stream_eval_injection_facts_and_rule_fires);
    RUN_TEST(stream_eval_injection_per_name_aggregates_exclude_non_numeric);
    RUN_TEST(stream_eval_injection_empty_window);
    RUN_TEST(stream_eval_injection_overwrites_stale_facts);
    RUN_TEST(stream_eval_injection_bumps_mutation_serial);
    RUN_TEST(stream_eval_injection_tumbling_bucket_bounds);
    RUN_TEST(stream_eval_injection_empty_tumbling_reports_bucket_zero_span);
    RUN_TEST(stream_eval_injection_session_span);
    RUN_TEST(stream_eval_registry_register_replace_unregister);
    RUN_TEST(stream_eval_registry_invalid_arguments);
    RUN_TEST(stream_eval_registry_cap_is_16);
    RUN_TEST(stream_eval_registry_is_busy_while_running);
    RUN_TEST(stream_eval_engine_destroy_keeps_registered_window);
    RUN_TEST(stream_eval_grl_typed_and_untyped_binding_fires);
    RUN_TEST(stream_eval_grl_type_filter_excludes_other_names);
    RUN_TEST(stream_eval_grl_sliding_clause_filters_old_events);
    RUN_TEST(stream_eval_grl_sliding_clause_lower_bound_is_closed);
    RUN_TEST(stream_eval_grl_tumbling_zero_duration_is_invalid_argument);
    RUN_TEST(stream_eval_grl_tumbling_clause_current_bucket);
    RUN_TEST(stream_eval_grl_session_clause_end_to_end);
    RUN_TEST(stream_eval_grl_unregistered_stream_is_not_supported);
    RUN_TEST(stream_eval_backward_on_stream_ce_stays_not_supported);
TEST_MAIN_END()
