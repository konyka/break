#include "test_framework.h"
#include <rule_engine/rule_engine.h>
#include <stddef.h>
#include <string.h>

/*
 * Stream window aggregate extensions (Task 16): MIN/MAX/FIRST/LAST over the
 * retained, type/key-filtered event set, sharing the count/sum filter.
 *
 * - MIN/MAX fold numeric event values; a non-numeric event in the filtered
 *   set is RE_STATUS_INVALID_ARGUMENT, mirroring the SUM/AVERAGE tolerance.
 * - FIRST/LAST copy the value of the earliest/latest retained event by
 *   timestamp; insertion order breaks timestamp ties.
 * - An empty filtered set reports RE_STATUS_NOT_FOUND for MIN/MAX/FIRST/LAST
 *   (COUNT keeps its 0/OK behavior).
 * - re_stream_aggregate_result_t grew by tail append only; callers passing
 *   the pre-Task-16 struct_size get the old fields with the new fields
 *   untouched.
 */

static re_string_t text(const char *value) {
    re_string_t result = {value, strlen(value)};
    return result;
}

static re_stream_window_t *make_sliding_window(re_engine_t *engine,
                                               re_late_event_policy_t policy,
                                               uint64_t allowed_lateness_ms) {
    re_stream_window_t *window = NULL;
    re_stream_window_options_t options = {sizeof(options), RE_STREAM_WINDOW_ABI_VERSION,
        RE_STREAM_WINDOW_SLIDING, policy, 1000u, 8u, 1024u, allowed_lateness_ms};
    if (re_stream_window_create_v1(engine, &options, &window) != RE_STATUS_OK) return NULL;
    return window;
}

TEST(stream_min_max_over_filtered_events) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_window_t *window = make_sliding_window(engine, RE_LATE_EVENT_DROP, 0u);
    re_stream_filter_options_t filter = {sizeof(filter), RE_STREAM_WINDOW_ABI_VERSION,
        text("T"), (re_string_t){NULL, 0u}};
    re_stream_aggregate_result_t result = {sizeof(result), 0u, 0.0, 0.0, 0.0, 0.0,
        {RE_VALUE_NONE, {0}}, {RE_VALUE_NONE, {0}}};
    re_value_t five = {RE_VALUE_INT64, {.int64_value = 5}};
    re_value_t two = {RE_VALUE_DOUBLE, {.double_value = 2.0}};
    re_value_t nine = {RE_VALUE_INT64, {.int64_value = 9}};
    re_value_t distractor = {RE_VALUE_DOUBLE, {.double_value = 100.0}};
    ASSERT_NOT_NULL(window);
    ASSERT_EQ(re_stream_window_record_v1(window, 10u, text("T"), &five), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 20u, text("T"), &two), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 30u, text("T"), &nine), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 40u, text("U"), &distractor), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_aggregate_v1(window, &filter, RE_STREAM_AGGREGATE_MIN, &result), RE_STATUS_OK);
    ASSERT_EQ(result.count, 3u);
    ASSERT_FLOAT_EQ(result.sum, 16.0, 0.0001);
    ASSERT_FLOAT_EQ(result.average, 16.0 / 3.0, 0.0001);
    ASSERT_FLOAT_EQ(result.minimum, 2.0, 0.0001);
    ASSERT_EQ(re_stream_window_aggregate_v1(window, &filter, RE_STREAM_AGGREGATE_MAX, &result), RE_STATUS_OK);
    ASSERT_EQ(result.count, 3u);
    ASSERT_FLOAT_EQ(result.sum, 16.0, 0.0001);
    ASSERT_FLOAT_EQ(result.maximum, 9.0, 0.0001);
    re_stream_window_destroy(window);
    re_engine_destroy(engine);
}

TEST(stream_first_last_by_timestamp) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_window_t *window = make_sliding_window(engine, RE_LATE_EVENT_ACCEPT, 1000u);
    re_stream_filter_options_t filter = {sizeof(filter), RE_STREAM_WINDOW_ABI_VERSION,
        (re_string_t){NULL, 0u}, (re_string_t){NULL, 0u}};
    re_stream_aggregate_result_t result = {sizeof(result), 0u, 0.0, 0.0, 0.0, 0.0,
        {RE_VALUE_NONE, {0}}, {RE_VALUE_NONE, {0}}};
    re_value_t a = {RE_VALUE_STRING, {.string = {"a", 1u}}};
    re_value_t b = {RE_VALUE_STRING, {.string = {"b", 1u}}};
    ASSERT_NOT_NULL(window);
    /* Out-of-order insert: "a" has the later timestamp but is recorded first. */
    ASSERT_EQ(re_stream_window_record_v1(window, 100u, text("tick"), &a), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 50u, text("tick"), &b), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_aggregate_v1(window, &filter, RE_STREAM_AGGREGATE_FIRST, &result), RE_STATUS_OK);
    ASSERT_EQ(result.count, 2u);
    ASSERT_EQ(result.first.type, RE_VALUE_STRING);
    ASSERT_TRUE(result.first.as.string.size == 1u && result.first.as.string.data[0] == 'b');
    ASSERT_EQ(re_stream_window_aggregate_v1(window, &filter, RE_STREAM_AGGREGATE_LAST, &result), RE_STATUS_OK);
    ASSERT_EQ(result.last.type, RE_VALUE_STRING);
    ASSERT_TRUE(result.last.as.string.size == 1u && result.last.as.string.data[0] == 'a');
    re_stream_window_destroy(window);
    re_engine_destroy(engine);
}

TEST(stream_new_kinds_empty_window_not_found) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_window_t *window = make_sliding_window(engine, RE_LATE_EVENT_DROP, 0u);
    re_stream_filter_options_t filter = {sizeof(filter), RE_STREAM_WINDOW_ABI_VERSION,
        text("absent"), (re_string_t){NULL, 0u}};
    re_stream_aggregate_result_t result = {sizeof(result), 0u, 0.0, 0.0, 0.0, 0.0,
        {RE_VALUE_NONE, {0}}, {RE_VALUE_NONE, {0}}};
    re_value_t value = {RE_VALUE_INT64, {.int64_value = 1}};
    ASSERT_NOT_NULL(window);
    ASSERT_EQ(re_stream_window_record_v1(window, 10u, text("present"), &value), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_aggregate_v1(window, &filter, RE_STREAM_AGGREGATE_COUNT, &result), RE_STATUS_OK);
    ASSERT_EQ(result.count, 0u);
    ASSERT_EQ(re_stream_window_aggregate_v1(window, &filter, RE_STREAM_AGGREGATE_MIN, &result), RE_STATUS_NOT_FOUND);
    ASSERT_EQ(re_stream_window_aggregate_v1(window, &filter, RE_STREAM_AGGREGATE_MAX, &result), RE_STATUS_NOT_FOUND);
    ASSERT_EQ(re_stream_window_aggregate_v1(window, &filter, RE_STREAM_AGGREGATE_FIRST, &result), RE_STATUS_NOT_FOUND);
    ASSERT_EQ(re_stream_window_aggregate_v1(window, &filter, RE_STREAM_AGGREGATE_LAST, &result), RE_STATUS_NOT_FOUND);
    re_stream_window_destroy(window);
    re_engine_destroy(engine);
}

TEST(stream_aggregate_result_struct_size_compat) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_window_t *window = make_sliding_window(engine, RE_LATE_EVENT_DROP, 0u);
    re_stream_filter_options_t filter = {sizeof(filter), RE_STREAM_WINDOW_ABI_VERSION,
        text("T"), (re_string_t){NULL, 0u}};
    re_stream_aggregate_result_t result;
    re_value_t five = {RE_VALUE_INT64, {.int64_value = 5}};
    ASSERT_NOT_NULL(window);
    ASSERT_EQ(re_stream_window_record_v1(window, 10u, text("T"), &five), RE_STATUS_OK);
    /* A caller compiled against the pre-Task-16 struct passes the old size;
     * the appended fields must stay untouched while the old fields fill in. */
    memset(&result, 0, sizeof(result));
    result.struct_size = (uint32_t)offsetof(re_stream_aggregate_result_t, minimum);
    result.minimum = -12345.0;
    result.maximum = -12345.0;
    result.first.type = RE_VALUE_UNKNOWN;
    result.last.type = RE_VALUE_UNKNOWN;
    ASSERT_EQ(re_stream_window_aggregate_v1(window, &filter, RE_STREAM_AGGREGATE_SUM, &result), RE_STATUS_OK);
    ASSERT_EQ(result.count, 1u);
    ASSERT_FLOAT_EQ(result.sum, 5.0, 0.0001);
    ASSERT_FLOAT_EQ(result.average, 5.0, 0.0001);
    ASSERT_FLOAT_EQ(result.minimum, -12345.0, 0.0001);
    ASSERT_FLOAT_EQ(result.maximum, -12345.0, 0.0001);
    ASSERT_EQ(result.first.type, RE_VALUE_UNKNOWN);
    ASSERT_EQ(result.last.type, RE_VALUE_UNKNOWN);
    result.struct_size = (uint32_t)offsetof(re_stream_aggregate_result_t, minimum) - 1u;
    ASSERT_EQ(re_stream_window_aggregate_v1(window, &filter, RE_STREAM_AGGREGATE_SUM, &result),
              RE_STATUS_INVALID_ARGUMENT);
    re_stream_window_destroy(window);
    re_engine_destroy(engine);
}

TEST(stream_first_last_equal_timestamps_insertion_order) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_window_t *window = make_sliding_window(engine, RE_LATE_EVENT_DROP, 0u);
    re_stream_filter_options_t filter = {sizeof(filter), RE_STREAM_WINDOW_ABI_VERSION,
        (re_string_t){NULL, 0u}, (re_string_t){NULL, 0u}};
    re_stream_aggregate_result_t result = {sizeof(result), 0u, 0.0, 0.0, 0.0, 0.0,
        {RE_VALUE_NONE, {0}}, {RE_VALUE_NONE, {0}}};
    re_value_t early = {RE_VALUE_INT64, {.int64_value = 1}};
    re_value_t first_tied = {RE_VALUE_INT64, {.int64_value = 2}};
    re_value_t second_tied = {RE_VALUE_INT64, {.int64_value = 3}};
    ASSERT_NOT_NULL(window);
    ASSERT_EQ(re_stream_window_record_v1(window, 10u, text("t"), &early), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 20u, text("t"), &first_tied), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 20u, text("t"), &second_tied), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_aggregate_v1(window, &filter, RE_STREAM_AGGREGATE_FIRST, &result), RE_STATUS_OK);
    ASSERT_EQ(result.first.type, RE_VALUE_INT64);
    ASSERT_EQ(result.first.as.int64_value, 1);
    ASSERT_EQ(re_stream_window_aggregate_v1(window, &filter, RE_STREAM_AGGREGATE_LAST, &result), RE_STATUS_OK);
    ASSERT_EQ(result.last.type, RE_VALUE_INT64);
    ASSERT_EQ(result.last.as.int64_value, 3);
    /* Tie between the two ts=20 events: FIRST over the tied pair picks the
     * earlier insertion. Verify via a fresh window holding only the pair. */
    {
        re_stream_window_t *tied = make_sliding_window(engine, RE_LATE_EVENT_DROP, 0u);
        ASSERT_NOT_NULL(tied);
        ASSERT_EQ(re_stream_window_record_v1(tied, 20u, text("t"), &first_tied), RE_STATUS_OK);
        ASSERT_EQ(re_stream_window_record_v1(tied, 20u, text("t"), &second_tied), RE_STATUS_OK);
        ASSERT_EQ(re_stream_window_aggregate_v1(tied, &filter, RE_STREAM_AGGREGATE_FIRST, &result), RE_STATUS_OK);
        ASSERT_EQ(result.first.as.int64_value, 2);
        ASSERT_EQ(re_stream_window_aggregate_v1(tied, &filter, RE_STREAM_AGGREGATE_LAST, &result), RE_STATUS_OK);
        ASSERT_EQ(result.last.as.int64_value, 3);
        re_stream_window_destroy(tied);
    }
    re_stream_window_destroy(window);
    re_engine_destroy(engine);
}

TEST(stream_min_max_reject_non_numeric_event) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_window_t *window = make_sliding_window(engine, RE_LATE_EVENT_DROP, 0u);
    re_stream_filter_options_t filter = {sizeof(filter), RE_STREAM_WINDOW_ABI_VERSION,
        text("T"), (re_string_t){NULL, 0u}};
    re_stream_aggregate_result_t result = {sizeof(result), 0u, 0.0, 0.0, 0.0, 0.0,
        {RE_VALUE_NONE, {0}}, {RE_VALUE_NONE, {0}}};
    re_value_t number = {RE_VALUE_INT64, {.int64_value = 5}};
    re_value_t word = {RE_VALUE_STRING, {.string = {"oops", 4u}}};
    ASSERT_NOT_NULL(window);
    ASSERT_EQ(re_stream_window_record_v1(window, 10u, text("T"), &number), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 20u, text("T"), &word), RE_STATUS_OK);
    /* SUM/AVERAGE already reject a non-numeric filtered event; MIN/MAX mirror
     * that tolerance exactly. FIRST/LAST accept any value type. */
    ASSERT_EQ(re_stream_window_aggregate_v1(window, &filter, RE_STREAM_AGGREGATE_SUM, &result),
              RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_stream_window_aggregate_v1(window, &filter, RE_STREAM_AGGREGATE_MIN, &result),
              RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_stream_window_aggregate_v1(window, &filter, RE_STREAM_AGGREGATE_MAX, &result),
              RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_stream_window_aggregate_v1(window, &filter, RE_STREAM_AGGREGATE_FIRST, &result), RE_STATUS_OK);
    ASSERT_EQ(result.first.as.int64_value, 5);
    ASSERT_EQ(re_stream_window_aggregate_v1(window, &filter, RE_STREAM_AGGREGATE_LAST, &result), RE_STATUS_OK);
    ASSERT_EQ(result.last.type, RE_VALUE_STRING);
    re_stream_window_destroy(window);
    re_engine_destroy(engine);
}

/*
 * Redis state provider boundary (Task 17): RE_STATE_PROVIDER_REDIS is the one
 * provider kind whose availability is decided when the library is built. When
 * the native adapter is not compiled in (hiredis missing at configure time),
 * the kind stays RE_STATUS_NOT_SUPPORTED and nothing else changes. When the
 * adapter is compiled in (RE_HAS_HIREDIS reaches this file via the same CMake
 * condition that wires redis_provider.c into rule_engine_core), a create
 * against an unreachable address must surface RE_STATUS_ERROR without
 * producing a provider, and a live service allows a full roundtrip.
 */

#if defined(RE_HAS_HIREDIS)
#if !defined(_WIN32)
/* Strict -std=c99 hides the POSIX prototypes; declare them explicitly. */
extern int setenv(const char *name, const char *value, int overwrite);
extern int unsetenv(const char *name);
#endif
static void redis_test_set_url(const char *url) {
#if defined(_WIN32)
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "RE_REDIS_URL=%s", url);
    _putenv(buffer);
#else
    setenv("RE_REDIS_URL", url, 1);
#endif
}
static void redis_test_clear_url(void) {
#if defined(_WIN32)
    _putenv("RE_REDIS_URL=");
#else
    unsetenv("RE_REDIS_URL");
#endif
}
#endif

TEST(redis_kind_disabled_without_native_client) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_state_provider_t *provider = NULL;
    re_state_provider_options_t options = {sizeof(options), RE_STATE_PROVIDER_ABI_VERSION,
        RE_STATE_PROVIDER_REDIS, 0u, 100u};
#if defined(RE_HAS_HIREDIS)
    {
        const char *saved = getenv("RE_REDIS_URL");
        char saved_copy[256];
        saved_copy[0] = '\0';
        if (saved != NULL) {
            strncpy(saved_copy, saved, sizeof(saved_copy) - 1u);
            saved_copy[sizeof(saved_copy) - 1u] = '\0';
        }
        /* Nothing answers on 127.0.0.1:6390; the connect failure must surface
         * as RE_STATUS_ERROR (no provider instance exists to carry
         * last_error) and must not crash or fabricate a provider. */
        redis_test_set_url("redis://127.0.0.1:6390");
        ASSERT_EQ(re_engine_set_state_provider_v1(engine, &options, NULL, &provider),
                  RE_STATUS_ERROR);
        ASSERT_TRUE(provider == NULL);
        if (saved != NULL) redis_test_set_url(saved_copy);
        else redis_test_clear_url();
    }
#else
    /* Boundary lock: without the native client the kind is rejected before any
     * descriptor validation, byte-identical to the pre-Task-17 behavior. */
    ASSERT_EQ(re_engine_set_state_provider_v1(engine, &options, NULL, &provider),
              RE_STATUS_NOT_SUPPORTED);
    ASSERT_TRUE(provider == NULL);
#endif
    re_engine_destroy(engine);
}

TEST(redis_roundtrip_when_service_available) {
#if defined(RE_HAS_HIREDIS)
    const char *url = getenv("RE_TEST_REDIS_URL");
    re_engine_t *engine;
    re_state_provider_t *provider = NULL;
    re_state_provider_options_t options = {sizeof(options), RE_STATE_PROVIDER_ABI_VERSION,
        RE_STATE_PROVIDER_REDIS, 0u, 1000u};
    re_value_t stored = {RE_VALUE_STRING, {.string = {"v1", 2u}}};
    re_value_t number = {RE_VALUE_INT64, {.int64_value = 42}};
    re_value_t out;
    uint64_t ttl = 0u;
    if (url == NULL) {
        printf("SKIP: RE_TEST_REDIS_URL unset (no integration service)\n");
        return;
    }
    redis_test_set_url(url);
    engine = re_engine_create(NULL, NULL);
    ASSERT_NOT_NULL(engine);
    ASSERT_EQ(re_engine_set_state_provider_v1(engine, &options, NULL, &provider), RE_STATUS_OK);
    ASSERT_NOT_NULL(provider);
    /* String set/get/delete roundtrip. */
    ASSERT_EQ(re_state_provider_put(provider, text("rt_string"), &stored, 0u), RE_STATUS_OK);
    ASSERT_EQ(re_state_provider_get(provider, text("rt_string"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.type, RE_VALUE_STRING);
    ASSERT_TRUE(out.as.string.size == 2u && memcmp(out.as.string.data, "v1", 2u) == 0);
    /* The PSETEX path accepts a TTL and the value is present immediately;
     * expiry timing itself is the server's job - no sleeping here. */
    ASSERT_EQ(re_state_provider_put(provider, text("rt_ttl"), &number, 60000u), RE_STATUS_OK);
    ASSERT_EQ(re_state_provider_get(provider, text("rt_ttl"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.type, RE_VALUE_INT64);
    ASSERT_EQ(out.as.int64_value, 42);
    ASSERT_EQ(re_state_provider_ttl(provider, text("rt_ttl"), &ttl), RE_STATUS_OK);
    ASSERT_TRUE(ttl != 0u);
    ASSERT_EQ(re_state_provider_delete(provider, text("rt_string")), RE_STATUS_OK);
    ASSERT_EQ(re_state_provider_get(provider, text("rt_string"), &out), RE_STATUS_NOT_FOUND);
    ASSERT_EQ(re_state_provider_delete(provider, text("rt_ttl")), RE_STATUS_OK);
    re_state_provider_destroy(provider);
    re_engine_destroy(engine);
#else
    printf("SKIP: native Redis adapter not compiled (RE_HAS_HIREDIS undefined)\n");
    return;
#endif
}

/*
 * Concurrency boundary (Task 18): the single-threaded handle contract and its
 * busy guards. The guard audit found no missing in-use flags on windows or
 * providers (see below), so these tests lock the EXISTING guard behavior:
 *
 * - While re_engine_run is active, re-entering the run, opening a user
 *   transaction, or resetting working memory is RE_STATUS_BUSY (engine
 *   running flag / facts running+run_transaction_allowed flags). Plain
 *   re_facts_set from the action callback is NOT busy by design: the firing
 *   and its callback share one fact transaction, so the write is staged and
 *   committed with the firing (documented in Rule_Engine_Architecture.md).
 * - During fact notification (re_facts_notify), mutations are RE_STATUS_BUSY
 *   (facts notifying flag) while reads stay allowed.
 * - Windows invoke no user code on any path (record/aggregate/correlate/
 *   snapshot/restore), so single-thread reentrancy cannot interleave; a
 *   snapshot owns a deep copy of the events, so restoring a window's own
 *   snapshot back into the same window cannot alias live state.
 * - Provider wrappers (re_state_provider_get/put/delete/ttl) are
 *   single-return-expression dispatch over the descriptor: a descriptor
 *   callback re-entering the same wrapper cannot corrupt wrapper state,
 *   because the wrapper touches no provider state after the callback returns.
 */

typedef struct busy_probe_t {
    re_engine_t *engine;
    re_facts_t *facts;
    re_status_t run_reentry;
    re_status_t txn_begin;
    re_status_t reset;
    int fired;
} busy_probe_t;

static re_status_t busy_action(re_engine_t *engine, re_facts_t *facts,
                               const re_rule_event_t *event, void *context) {
    busy_probe_t *probe = context;
    re_fact_txn_t *txn = NULL;
    (void)event;
    probe->fired = 1;
    /* All three attempts execute on the engine thread from inside the action
     * callback, so no data race is possible. */
    probe->run_reentry = re_engine_run(engine, facts, NULL, NULL);
    probe->txn_begin = re_facts_begin(facts, &txn);
    if (probe->txn_begin == RE_STATUS_OK) re_facts_rollback(txn);
    probe->reset = re_engine_reset_with_deffacts(engine, facts);
    return RE_STATUS_OK;
}

TEST(run_reentry_conflicting_mutation_returns_busy) {
    const char *source = "rule \"A\" { when Ready == true then A = 1; }";
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_program_t *program = NULL;
    re_value_t ready = {RE_VALUE_BOOL, {.boolean = 1}};
    busy_probe_t probe;
    re_callbacks_t callbacks;
    probe.engine = engine; probe.facts = facts; probe.fired = 0;
    probe.run_reentry = RE_STATUS_OK; probe.txn_begin = RE_STATUS_OK;
    probe.reset = RE_STATUS_OK;
    callbacks.action = busy_action; callbacks.context = &probe;
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(facts);
    ASSERT_EQ(re_program_load(NULL, text(source), NULL, &program), RE_STATUS_OK);
    ASSERT_EQ(re_engine_install(engine, program), RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("Ready"), &ready), RE_STATUS_OK);
    ASSERT_EQ(re_engine_run(engine, facts, NULL, &callbacks), RE_STATUS_OK);
    ASSERT_EQ(probe.fired, 1);
    ASSERT_EQ(probe.run_reentry, RE_STATUS_BUSY);
    ASSERT_EQ(probe.txn_begin, RE_STATUS_BUSY);
    ASSERT_EQ(probe.reset, RE_STATUS_BUSY);
    /* The busy flags release with the run: the handles are usable again. */
    ASSERT_EQ(re_engine_run(engine, facts, NULL, NULL), RE_STATUS_OK);
    {
        re_fact_txn_t *txn = NULL;
        ASSERT_EQ(re_facts_begin(facts, &txn), RE_STATUS_OK);
        re_facts_rollback(txn);
    }
    re_facts_destroy(facts);
    re_engine_destroy(engine);
}

typedef struct notify_probe_t {
    re_facts_t *facts;
    re_status_t set_during_notify;
    re_status_t insert_during_notify;
    re_status_t begin_during_notify;
    re_status_t get_during_notify;
} notify_probe_t;

static re_status_t notify_reentry(re_facts_t *facts, const re_fact_event_t *event,
                                  void *context) {
    notify_probe_t *probe = context;
    re_value_t v = {RE_VALUE_INT64, {.int64_value = 1}};
    re_fact_id_t id;
    re_fact_txn_t *txn = NULL;
    re_value_t out;
    (void)event;
    probe->set_during_notify = re_facts_set(facts, text("other"), &v);
    probe->insert_during_notify = re_facts_insert(facts, text("other"), &v, &id);
    probe->begin_during_notify = re_facts_begin(facts, &txn);
    if (probe->begin_during_notify == RE_STATUS_OK) re_facts_rollback(txn);
    probe->get_during_notify = re_facts_get(facts, text("watched"), &out);
    return RE_STATUS_OK;
}

TEST(notify_reentry_mutation_returns_busy_read_allowed) {
    re_facts_t *facts = re_facts_create(NULL, NULL);
    re_subscription_t *subscription = NULL;
    notify_probe_t probe;
    re_value_t v = {RE_VALUE_INT64, {.int64_value = 1}};
    re_value_t v2 = {RE_VALUE_INT64, {.int64_value = 2}};
    probe.facts = facts;
    probe.set_during_notify = RE_STATUS_OK;
    probe.insert_during_notify = RE_STATUS_OK;
    probe.begin_during_notify = RE_STATUS_OK;
    probe.get_during_notify = RE_STATUS_OK;
    ASSERT_NOT_NULL(facts);
    /* re_facts_set only notifies for an already-known name, so seed first. */
    ASSERT_EQ(re_facts_set(facts, text("watched"), &v), RE_STATUS_OK);
    ASSERT_EQ(re_facts_subscribe(facts, notify_reentry, &probe, &subscription),
              RE_STATUS_OK);
    ASSERT_EQ(re_facts_set(facts, text("watched"), &v2), RE_STATUS_OK);
    ASSERT_EQ(probe.set_during_notify, RE_STATUS_BUSY);
    ASSERT_EQ(probe.insert_during_notify, RE_STATUS_BUSY);
    ASSERT_EQ(probe.begin_during_notify, RE_STATUS_BUSY);
    ASSERT_EQ(probe.get_during_notify, RE_STATUS_OK);
    re_subscription_destroy(subscription);
    re_facts_destroy(facts);
}

TEST(window_snapshot_restore_into_self_no_aliasing) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_window_t *window = make_sliding_window(engine, RE_LATE_EVENT_DROP, 0u);
    re_stream_filter_options_t filter = {sizeof(filter), RE_STREAM_WINDOW_ABI_VERSION,
        (re_string_t){NULL, 0u}, (re_string_t){NULL, 0u}};
    re_stream_aggregate_result_t result = {sizeof(result), 0u, 0.0, 0.0, 0.0, 0.0,
        {RE_VALUE_NONE, {0}}, {RE_VALUE_NONE, {0}}};
    re_snapshot_t snapshot;
    re_value_t five = {RE_VALUE_INT64, {.int64_value = 5}};
    re_value_t nine = {RE_VALUE_INT64, {.int64_value = 9}};
    ASSERT_NOT_NULL(window);
    ASSERT_EQ(re_stream_window_record_v1(window, 10u, text("T"), &five), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 20u, text("T"), &nine), RE_STATUS_OK);
    memset(&snapshot, 0, sizeof(snapshot));
    snapshot.struct_size = sizeof(snapshot);
    ASSERT_EQ(re_stream_window_snapshot(window, &snapshot), RE_STATUS_OK);
    /* Restore the window's own snapshot back into the same window: the
     * snapshot owns a deep copy, so freeing the old event storage during the
     * staged swap cannot invalidate the parse source. */
    ASSERT_EQ(re_stream_window_restore(window, &snapshot), RE_STATUS_OK);
    snapshot.release(snapshot.release_context, snapshot.data, snapshot.size);
    ASSERT_EQ(re_stream_window_aggregate_v1(window, &filter, RE_STREAM_AGGREGATE_SUM,
                                            &result), RE_STATUS_OK);
    ASSERT_EQ(result.count, 2u);
    ASSERT_FLOAT_EQ(result.sum, 14.0, 0.0001);
    ASSERT_EQ(re_stream_window_aggregate_v1(window, &filter, RE_STREAM_AGGREGATE_LAST,
                                            &result), RE_STATUS_OK);
    ASSERT_EQ(result.last.as.int64_value, 9);
    re_stream_window_destroy(window);
    re_engine_destroy(engine);
}

typedef struct reentrant_provider_t {
    re_state_provider_t *provider;
    int depth;
    re_status_t inner_put;
    re_status_t inner_get;
    re_status_t inner_delete;
} reentrant_provider_t;

static re_status_t reentrant_get(re_state_provider_t *provider, re_string_t key,
                                 re_value_t *out_value, void *context) {
    reentrant_provider_t *state = context;
    if (state->depth == 0 && key.size == 7u && memcmp(key.data, "reenter", 7u) == 0) {
        re_value_t inner = {RE_VALUE_INT64, {.int64_value = 3}};
        re_value_t out;
        state->depth = 1;
        /* Re-enter the same provider through the public wrappers from inside
         * a descriptor callback. The wrapper reads the descriptor before the
         * call and touches no provider state after it, so this cannot corrupt
         * the outer frame. */
        state->inner_put = re_state_provider_put(provider, text("inner"), &inner, 0u);
        state->inner_get = re_state_provider_get(provider, text("inner"), &out);
        state->inner_delete = re_state_provider_delete(provider, text("inner"));
        state->depth = 0;
        out_value->type = RE_VALUE_INT64;
        out_value->as.int64_value = 1;
        return RE_STATUS_OK;
    }
    if (key.size == 5u && memcmp(key.data, "inner", 5u) == 0) {
        out_value->type = RE_VALUE_INT64;
        out_value->as.int64_value = 3;
        return RE_STATUS_OK;
    }
    return RE_STATUS_NOT_FOUND;
}

static re_status_t reentrant_put(re_state_provider_t *provider, re_string_t key,
                                 const re_value_t *value, uint64_t ttl_ms, void *context) {
    (void)provider; (void)key; (void)value; (void)ttl_ms; (void)context;
    return RE_STATUS_OK;
}

static re_status_t reentrant_delete(re_state_provider_t *provider, re_string_t key,
                                    void *context) {
    (void)provider; (void)key; (void)context;
    return RE_STATUS_OK;
}

TEST(provider_callback_reentry_safe_by_construction) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_state_provider_t *provider = NULL;
    re_state_provider_options_t options = {sizeof(options), RE_STATE_PROVIDER_ABI_VERSION,
        RE_STATE_PROVIDER_CALLBACK, 0u, 0u};
    reentrant_provider_t state;
    re_state_provider_descriptor_t descriptor;
    re_value_t out;
    state.provider = NULL; state.depth = 0;
    state.inner_put = RE_STATUS_OK; state.inner_get = RE_STATUS_OK;
    state.inner_delete = RE_STATUS_OK;
    memset(&descriptor, 0, sizeof(descriptor));
    descriptor.struct_size = sizeof(descriptor);
    descriptor.abi_version = RE_STATE_PROVIDER_ABI_VERSION;
    descriptor.get = reentrant_get;
    descriptor.put = reentrant_put;
    descriptor.delete_key = reentrant_delete;
    descriptor.context = &state;
    ASSERT_NOT_NULL(engine);
    ASSERT_EQ(re_engine_set_state_provider_v1(engine, &options, &descriptor, &provider),
              RE_STATUS_OK);
    ASSERT_NOT_NULL(provider);
    state.provider = provider;
    ASSERT_EQ(re_state_provider_get(provider, text("reenter"), &out), RE_STATUS_OK);
    ASSERT_EQ(out.type, RE_VALUE_INT64);
    ASSERT_EQ(out.as.int64_value, 1);
    ASSERT_EQ(state.inner_put, RE_STATUS_OK);
    ASSERT_EQ(state.inner_get, RE_STATUS_OK);
    ASSERT_EQ(state.inner_delete, RE_STATUS_OK);
    re_state_provider_destroy(provider);
    re_engine_destroy(engine);
}

TEST_MAIN_BEGIN()
    RUN_TEST(stream_min_max_over_filtered_events);
    RUN_TEST(stream_first_last_by_timestamp);
    RUN_TEST(stream_new_kinds_empty_window_not_found);
    RUN_TEST(stream_aggregate_result_struct_size_compat);
    RUN_TEST(stream_first_last_equal_timestamps_insertion_order);
    RUN_TEST(stream_min_max_reject_non_numeric_event);
    RUN_TEST(redis_kind_disabled_without_native_client);
    RUN_TEST(redis_roundtrip_when_service_available);
    RUN_TEST(run_reentry_conflicting_mutation_returns_busy);
    RUN_TEST(notify_reentry_mutation_returns_busy_read_allowed);
    RUN_TEST(window_snapshot_restore_into_self_no_aliasing);
    RUN_TEST(provider_callback_reentry_safe_by_construction);
TEST_MAIN_END()
