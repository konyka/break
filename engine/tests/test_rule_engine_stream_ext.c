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
        RE_STREAM_WINDOW_SLIDING, policy, 1000u, 8u, 1024u, allowed_lateness_ms, 0u};
    if (re_stream_window_create_v1(engine, &options, &window) != RE_STATUS_OK) return NULL;
    return window;
}

TEST(stream_min_max_over_filtered_events) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_window_t *window = make_sliding_window(engine, RE_LATE_EVENT_DROP, 0u);
    re_stream_filter_options_t filter = {sizeof(filter), RE_STREAM_WINDOW_ABI_VERSION,
        text("T"), (re_string_t){NULL, 0u}, 0.0};
    re_stream_aggregate_result_t result = {sizeof(result), 0u, 0.0, 0.0, 0.0, 0.0,
        {RE_VALUE_NONE, {0}}, {RE_VALUE_NONE, {0}}, 0.0, 0.0};
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
        (re_string_t){NULL, 0u}, (re_string_t){NULL, 0u}, 0.0};
    re_stream_aggregate_result_t result = {sizeof(result), 0u, 0.0, 0.0, 0.0, 0.0,
        {RE_VALUE_NONE, {0}}, {RE_VALUE_NONE, {0}}, 0.0, 0.0};
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
        text("absent"), (re_string_t){NULL, 0u}, 0.0};
    re_stream_aggregate_result_t result = {sizeof(result), 0u, 0.0, 0.0, 0.0, 0.0,
        {RE_VALUE_NONE, {0}}, {RE_VALUE_NONE, {0}}, 0.0, 0.0};
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
        text("T"), (re_string_t){NULL, 0u}, 0.0};
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
        (re_string_t){NULL, 0u}, (re_string_t){NULL, 0u}, 0.0};
    re_stream_aggregate_result_t result = {sizeof(result), 0u, 0.0, 0.0, 0.0, 0.0,
        {RE_VALUE_NONE, {0}}, {RE_VALUE_NONE, {0}}, 0.0, 0.0};
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
        text("T"), (re_string_t){NULL, 0u}, 0.0};
    re_stream_aggregate_result_t result = {sizeof(result), 0u, 0.0, 0.0, 0.0, 0.0,
        {RE_VALUE_NONE, {0}}, {RE_VALUE_NONE, {0}}, 0.0, 0.0};
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
 * Stream aggregate kinds (Task C1): COUNT_DISTINCT/STDDEV/PERCENTILE over the
 * retained, type/key-filtered event set, mirroring upstream rust-rule-engine
 * v1.21.4 AggregationType (f80a541 src/streaming/aggregator.rs:12).
 *
 * - COUNT_DISTINCT counts distinct typed values: same type tag and equal
 *   payload (int64 by value, double bitwise, string by content, bool by
 *   value, null=null). The distinct count lands in result.count. Upstream
 *   counts distinct debug-strings (aggregator.rs CountDistinct arm), which
 *   would equate 1 and 1.0 - a documented divergence. Any value type is
 *   accepted.
 * - STDDEV is the population standard deviation (variance =
 *   sum((v-mean)^2)/N, aggregator.rs:233) and requires >= 2 numeric values,
 *   else RE_STATUS_NOT_FOUND (upstream None).
 * - PERCENTILE sorts ascending and picks nearest-rank index
 *   round(p/100*(n-1)) (aggregator.rs:253); p rides in the tail-appended
 *   filter percentile field (0-100, else RE_STATUS_INVALID_ARGUMENT).
 * - STDDEV/PERCENTILE reject a non-numeric filtered event exactly like
 *   SUM/AVERAGE; an empty filtered set is RE_STATUS_NOT_FOUND for all three.
 * - re_stream_aggregate_result_t and re_stream_filter_options_t grew by tail
 *   append only; pre-C1 struct_size values leave the appended fields
 *   untouched (and only PERCENTILE requires the new filter field).
 */

TEST(stream_stddev_population_known_values) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_window_t *window = make_sliding_window(engine, RE_LATE_EVENT_DROP, 0u);
    re_stream_filter_options_t filter = {sizeof(filter), RE_STREAM_WINDOW_ABI_VERSION,
        text("T"), (re_string_t){NULL, 0u}, 0.0};
    re_stream_aggregate_result_t result = {sizeof(result), 0u, 0.0, 0.0, 0.0, 0.0,
        {RE_VALUE_NONE, {0}}, {RE_VALUE_NONE, {0}}, 0.0, 0.0};
    /* Population stddev of {2,4,4,4,5,5,7,9} is exactly 2: mean 5, squared
     * deviations sum to 32, variance 32/8 = 4 (aggregator.rs:233). */
    const int64_t numbers[8] = {2, 4, 4, 4, 5, 5, 7, 9};
    size_t index;
    ASSERT_NOT_NULL(window);
    for (index = 0u; index < 8u; ++index) {
        re_value_t value = {RE_VALUE_INT64, {.int64_value = numbers[index]}};
        ASSERT_EQ(re_stream_window_record_v1(window, (uint64_t)(index + 1u) * 10u,
                                             text("T"), &value), RE_STATUS_OK);
    }
    ASSERT_EQ(re_stream_window_aggregate_v1(window, &filter, RE_STREAM_AGGREGATE_STDDEV,
                                            &result), RE_STATUS_OK);
    ASSERT_EQ(result.count, 8u);
    ASSERT_FLOAT_EQ(result.sum, 40.0, 0.0001);
    ASSERT_FLOAT_EQ(result.average, 5.0, 0.0001);
    ASSERT_FLOAT_EQ(result.stddev, 2.0, 0.0001);
    re_stream_window_destroy(window);
    re_engine_destroy(engine);
}

TEST(stream_stddev_single_value_not_found) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_window_t *window = make_sliding_window(engine, RE_LATE_EVENT_DROP, 0u);
    re_stream_filter_options_t filter = {sizeof(filter), RE_STREAM_WINDOW_ABI_VERSION,
        text("T"), (re_string_t){NULL, 0u}, 0.0};
    re_stream_aggregate_result_t result = {sizeof(result), 0u, 0.0, 0.0, 0.0, 0.0,
        {RE_VALUE_NONE, {0}}, {RE_VALUE_NONE, {0}}, 0.0, 0.0};
    re_value_t five = {RE_VALUE_INT64, {.int64_value = 5}};
    ASSERT_NOT_NULL(window);
    ASSERT_EQ(re_stream_window_record_v1(window, 10u, text("T"), &five), RE_STATUS_OK);
    /* Upstream requires >= 2 values and returns None otherwise; NOT_FOUND
     * returns before out_result is touched. */
    result.stddev = -12345.0;
    ASSERT_EQ(re_stream_window_aggregate_v1(window, &filter, RE_STREAM_AGGREGATE_STDDEV,
                                            &result), RE_STATUS_NOT_FOUND);
    ASSERT_FLOAT_EQ(result.stddev, -12345.0, 0.0001);
    re_stream_window_destroy(window);
    re_engine_destroy(engine);
}

TEST(stream_percentile_nearest_rank) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_window_t *window = make_sliding_window(engine, RE_LATE_EVENT_DROP, 0u);
    re_stream_filter_options_t filter = {sizeof(filter), RE_STREAM_WINDOW_ABI_VERSION,
        text("T"), (re_string_t){NULL, 0u}, 50.0};
    re_stream_aggregate_result_t result = {sizeof(result), 0u, 0.0, 0.0, 0.0, 0.0,
        {RE_VALUE_NONE, {0}}, {RE_VALUE_NONE, {0}}, 0.0, 0.0};
    re_value_t four = {RE_VALUE_DOUBLE, {.double_value = 4.0}};
    re_value_t one = {RE_VALUE_INT64, {.int64_value = 1}};
    re_value_t three = {RE_VALUE_DOUBLE, {.double_value = 3.0}};
    re_value_t two = {RE_VALUE_INT64, {.int64_value = 2}};
    re_value_t distractor = {RE_VALUE_DOUBLE, {.double_value = 100.0}};
    ASSERT_NOT_NULL(window);
    /* Unsorted insert: sorted ascending the filtered set is {1,2,3,4}. */
    ASSERT_EQ(re_stream_window_record_v1(window, 10u, text("T"), &four), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 20u, text("T"), &one), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 30u, text("T"), &three), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 40u, text("T"), &two), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 50u, text("U"), &distractor), RE_STATUS_OK);
    /* n = 4, index = round(p/100 * 3): p50 -> 2, p0 -> 0, p100 -> 3. */
    ASSERT_EQ(re_stream_window_aggregate_v1(window, &filter, RE_STREAM_AGGREGATE_PERCENTILE,
                                            &result), RE_STATUS_OK);
    ASSERT_EQ(result.count, 4u);
    ASSERT_FLOAT_EQ(result.percentile, 3.0, 0.0001);
    filter.percentile = 0.0;
    ASSERT_EQ(re_stream_window_aggregate_v1(window, &filter, RE_STREAM_AGGREGATE_PERCENTILE,
                                            &result), RE_STATUS_OK);
    ASSERT_FLOAT_EQ(result.percentile, 1.0, 0.0001);
    filter.percentile = 100.0;
    ASSERT_EQ(re_stream_window_aggregate_v1(window, &filter, RE_STREAM_AGGREGATE_PERCENTILE,
                                            &result), RE_STATUS_OK);
    ASSERT_FLOAT_EQ(result.percentile, 4.0, 0.0001);
    /* Nearest-rank rounding: round(0.25 * 3) = round(0.75) = 1 -> 2.0. */
    filter.percentile = 25.0;
    ASSERT_EQ(re_stream_window_aggregate_v1(window, &filter, RE_STREAM_AGGREGATE_PERCENTILE,
                                            &result), RE_STATUS_OK);
    ASSERT_FLOAT_EQ(result.percentile, 2.0, 0.0001);
    re_stream_window_destroy(window);
    re_engine_destroy(engine);
}

TEST(stream_percentile_parameter_validation) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_window_t *window = make_sliding_window(engine, RE_LATE_EVENT_DROP, 0u);
    re_stream_filter_options_t filter = {sizeof(filter), RE_STREAM_WINDOW_ABI_VERSION,
        text("T"), (re_string_t){NULL, 0u}, 50.0};
    re_stream_aggregate_result_t result = {sizeof(result), 0u, 0.0, 0.0, 0.0, 0.0,
        {RE_VALUE_NONE, {0}}, {RE_VALUE_NONE, {0}}, 0.0, 0.0};
    re_value_t five = {RE_VALUE_INT64, {.int64_value = 5}};
    ASSERT_NOT_NULL(window);
    ASSERT_EQ(re_stream_window_record_v1(window, 10u, text("T"), &five), RE_STATUS_OK);
    filter.percentile = -0.5;
    ASSERT_EQ(re_stream_window_aggregate_v1(window, &filter, RE_STREAM_AGGREGATE_PERCENTILE,
                                            &result), RE_STATUS_INVALID_ARGUMENT);
    filter.percentile = 100.5;
    ASSERT_EQ(re_stream_window_aggregate_v1(window, &filter, RE_STREAM_AGGREGATE_PERCENTILE,
                                            &result), RE_STATUS_INVALID_ARGUMENT);
    /* A pre-C1 caller passes the old filter size: PERCENTILE cannot be
     * serviced (the parameter was never supplied), every other kind keeps
     * working - the Task-16 gating idiom mirrored on the filter side. */
    filter.struct_size = (uint32_t)offsetof(re_stream_filter_options_t, percentile);
    ASSERT_EQ(re_stream_window_aggregate_v1(window, &filter, RE_STREAM_AGGREGATE_PERCENTILE,
                                            &result), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_stream_window_aggregate_v1(window, &filter, RE_STREAM_AGGREGATE_SUM,
                                            &result), RE_STATUS_OK);
    ASSERT_FLOAT_EQ(result.sum, 5.0, 0.0001);
    re_stream_window_destroy(window);
    re_engine_destroy(engine);
}

TEST(stream_count_distinct_typed_values) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_window_t *window = make_sliding_window(engine, RE_LATE_EVENT_DROP, 0u);
    re_stream_filter_options_t filter = {sizeof(filter), RE_STREAM_WINDOW_ABI_VERSION,
        text("T"), (re_string_t){NULL, 0u}, 0.0};
    re_stream_aggregate_result_t result = {sizeof(result), 0u, 0.0, 0.0, 0.0, 0.0,
        {RE_VALUE_NONE, {0}}, {RE_VALUE_NONE, {0}}, 0.0, 0.0};
    re_value_t int_one = {RE_VALUE_INT64, {.int64_value = 1}};
    re_value_t double_one = {RE_VALUE_DOUBLE, {.double_value = 1.0}};
    re_value_t string_one = {RE_VALUE_STRING, {.string = {"1", 1u}}};
    re_value_t truth = {RE_VALUE_BOOL, {.boolean = 1}};
    re_value_t nothing = {RE_VALUE_NULL, {0}};
    ASSERT_NOT_NULL(window);
    /* 1, 1.0 and "1" are distinct under typed equality (upstream's
     * debug-string equality would merge the first two). */
    ASSERT_EQ(re_stream_window_record_v1(window, 10u, text("T"), &int_one), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 20u, text("T"), &double_one), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 30u, text("T"), &string_one), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 40u, text("T"), &int_one), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 50u, text("T"), &truth), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 60u, text("T"), &truth), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 70u, text("T"), &nothing), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 80u, text("T"), &nothing), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_aggregate_v1(window, &filter, RE_STREAM_AGGREGATE_COUNT_DISTINCT,
                                            &result), RE_STATUS_OK);
    /* 8 matching events, 5 distinct: 1, 1.0, "1", true, null. */
    ASSERT_EQ(result.count, 5u);
    /* COUNT_DISTINCT folds no numbers; sum/average stay zeroed. */
    ASSERT_FLOAT_EQ(result.sum, 0.0, 0.0001);
    re_stream_window_destroy(window);
    re_engine_destroy(engine);
}

TEST(stream_c1_kinds_empty_window_not_found) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_window_t *window = make_sliding_window(engine, RE_LATE_EVENT_DROP, 0u);
    re_stream_filter_options_t filter = {sizeof(filter), RE_STREAM_WINDOW_ABI_VERSION,
        text("absent"), (re_string_t){NULL, 0u}, 50.0};
    re_stream_aggregate_result_t result = {sizeof(result), 0u, 0.0, 0.0, 0.0, 0.0,
        {RE_VALUE_NONE, {0}}, {RE_VALUE_NONE, {0}}, 0.0, 0.0};
    re_value_t value = {RE_VALUE_INT64, {.int64_value = 1}};
    ASSERT_NOT_NULL(window);
    ASSERT_EQ(re_stream_window_record_v1(window, 10u, text("present"), &value), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_aggregate_v1(window, &filter, RE_STREAM_AGGREGATE_COUNT_DISTINCT,
                                            &result), RE_STATUS_NOT_FOUND);
    ASSERT_EQ(re_stream_window_aggregate_v1(window, &filter, RE_STREAM_AGGREGATE_STDDEV,
                                            &result), RE_STATUS_NOT_FOUND);
    ASSERT_EQ(re_stream_window_aggregate_v1(window, &filter, RE_STREAM_AGGREGATE_PERCENTILE,
                                            &result), RE_STATUS_NOT_FOUND);
    re_stream_window_destroy(window);
    re_engine_destroy(engine);
}

TEST(stream_c1_numeric_kinds_reject_non_numeric) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_window_t *window = make_sliding_window(engine, RE_LATE_EVENT_DROP, 0u);
    re_stream_filter_options_t filter = {sizeof(filter), RE_STREAM_WINDOW_ABI_VERSION,
        text("T"), (re_string_t){NULL, 0u}, 50.0};
    re_stream_aggregate_result_t result = {sizeof(result), 0u, 0.0, 0.0, 0.0, 0.0,
        {RE_VALUE_NONE, {0}}, {RE_VALUE_NONE, {0}}, 0.0, 0.0};
    re_value_t number = {RE_VALUE_INT64, {.int64_value = 5}};
    re_value_t word = {RE_VALUE_STRING, {.string = {"oops", 4u}}};
    ASSERT_NOT_NULL(window);
    ASSERT_EQ(re_stream_window_record_v1(window, 10u, text("T"), &number), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 20u, text("T"), &word), RE_STATUS_OK);
    /* STDDEV/PERCENTILE mirror the SUM/AVERAGE rejection; COUNT_DISTINCT
     * accepts any value type. */
    ASSERT_EQ(re_stream_window_aggregate_v1(window, &filter, RE_STREAM_AGGREGATE_STDDEV,
                                            &result), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_stream_window_aggregate_v1(window, &filter, RE_STREAM_AGGREGATE_PERCENTILE,
                                            &result), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_stream_window_aggregate_v1(window, &filter, RE_STREAM_AGGREGATE_COUNT_DISTINCT,
                                            &result), RE_STATUS_OK);
    ASSERT_EQ(result.count, 2u);
    re_stream_window_destroy(window);
    re_engine_destroy(engine);
}

TEST(stream_c1_result_struct_size_compat) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_window_t *window = make_sliding_window(engine, RE_LATE_EVENT_DROP, 0u);
    re_stream_filter_options_t filter = {sizeof(filter), RE_STREAM_WINDOW_ABI_VERSION,
        text("T"), (re_string_t){NULL, 0u}, 50.0};
    re_stream_aggregate_result_t result;
    re_value_t five = {RE_VALUE_INT64, {.int64_value = 5}};
    re_value_t seven = {RE_VALUE_INT64, {.int64_value = 7}};
    ASSERT_NOT_NULL(window);
    ASSERT_EQ(re_stream_window_record_v1(window, 10u, text("T"), &five), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 20u, text("T"), &seven), RE_STATUS_OK);
    /* A caller compiled against the pre-C1 struct passes the old full size;
     * the appended stddev/percentile stay untouched while the pre-C1 fields
     * (including Task-16's minimum..last) fill in. */
    memset(&result, 0, sizeof(result));
    result.struct_size = (uint32_t)offsetof(re_stream_aggregate_result_t, stddev);
    result.stddev = -12345.0;
    result.percentile = -12345.0;
    ASSERT_EQ(re_stream_window_aggregate_v1(window, &filter, RE_STREAM_AGGREGATE_STDDEV,
                                            &result), RE_STATUS_OK);
    ASSERT_EQ(result.count, 2u);
    ASSERT_FLOAT_EQ(result.sum, 12.0, 0.0001);
    ASSERT_FLOAT_EQ(result.minimum, 5.0, 0.0001);
    ASSERT_FLOAT_EQ(result.maximum, 7.0, 0.0001);
    ASSERT_EQ(result.first.as.int64_value, 5);
    ASSERT_EQ(result.last.as.int64_value, 7);
    ASSERT_FLOAT_EQ(result.stddev, -12345.0, 0.0001);
    ASSERT_FLOAT_EQ(result.percentile, -12345.0, 0.0001);
    /* The pre-Task-16 size still rejects nothing: only bytes beyond
     * struct_size are off-limits. */
    result.struct_size = (uint32_t)offsetof(re_stream_aggregate_result_t, minimum);
    result.minimum = -12345.0;
    ASSERT_EQ(re_stream_window_aggregate_v1(window, &filter, RE_STREAM_AGGREGATE_PERCENTILE,
                                            &result), RE_STATUS_OK);
    ASSERT_EQ(result.count, 2u);
    ASSERT_FLOAT_EQ(result.sum, 12.0, 0.0001);
    ASSERT_FLOAT_EQ(result.minimum, -12345.0, 0.0001);
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
        (re_string_t){NULL, 0u}, (re_string_t){NULL, 0u}, 0.0};
    re_stream_aggregate_result_t result = {sizeof(result), 0u, 0.0, 0.0, 0.0, 0.0,
        {RE_VALUE_NONE, {0}}, {RE_VALUE_NONE, {0}}, 0.0, 0.0};
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

/*
 * Stream analytics (sub-project C Task C2): the TTL aggregation cache and the
 * multi-window statistics, mirroring upstream StreamAnalytics
 * (rust-rule-engine v1.21.4 f80a541 src/streaming/aggregator.rs:285). The
 * host supplies the clock as current_time_ms; upstream anchors are cited per
 * test. Local "field" = event name over numeric scalars.
 */

/* Builds count single-"T"-event windows; returns the number built. */
static size_t build_value_windows(re_engine_t *engine, const double *values, size_t count,
                                  re_stream_window_t **out_windows, size_t out_capacity) {
    size_t index;
    for (index = 0u; index < count && index < out_capacity; ++index) {
        re_value_t value = {RE_VALUE_DOUBLE, {.double_value = values[index]}};
        out_windows[index] = make_sliding_window(engine, RE_LATE_EVENT_DROP, 0u);
        if (out_windows[index] == NULL) return index;
        if (re_stream_window_record_v1(out_windows[index], 10u + (uint64_t)index,
                                       text("T"), &value) != RE_STATUS_OK) return index;
    }
    return index;
}

static void destroy_windows(re_stream_window_t **windows, size_t count) {
    size_t index;
    for (index = 0u; index < count; ++index)
        if (windows[index] != NULL) re_stream_window_destroy(windows[index]);
}

/* Builds one window holding count events named name with the same value. */
static re_stream_window_t *make_events_window(re_engine_t *engine, const char *name,
                                              double value, uint64_t first_ts, size_t count) {
    size_t index;
    re_stream_window_t *window = make_sliding_window(engine, RE_LATE_EVENT_DROP, 0u);
    if (window == NULL) return NULL;
    for (index = 0u; index < count; ++index) {
        re_value_t v = {RE_VALUE_DOUBLE, {.double_value = value}};
        if (re_stream_window_record_v1(window, first_ts + (uint64_t)index,
                                       text(name), &v) != RE_STATUS_OK) {
            re_stream_window_destroy(window);
            return NULL;
        }
    }
    return window;
}

TEST(stream_analytics_cache_hit_miss_ttl_identity) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_analytics_t *analytics = NULL;
    re_stream_window_t *window = make_sliding_window(engine, RE_LATE_EVENT_DROP, 0u);
    re_stream_filter_options_t filter_t = {sizeof(filter_t), RE_STREAM_WINDOW_ABI_VERSION,
        text("T"), (re_string_t){NULL, 0u}, 0.0};
    re_stream_filter_options_t filter_u = {sizeof(filter_u), RE_STREAM_WINDOW_ABI_VERSION,
        text("U"), (re_string_t){NULL, 0u}, 0.0};
    re_stream_aggregate_result_t result = {sizeof(result), 0u, 0.0, 0.0, 0.0, 0.0,
        {RE_VALUE_NONE, {0}}, {RE_VALUE_NONE, {0}}, 0.0, 0.0};
    re_value_t five = {RE_VALUE_INT64, {.int64_value = 5}};
    re_value_t nine = {RE_VALUE_INT64, {.int64_value = 9}};
    re_value_t six = {RE_VALUE_INT64, {.int64_value = 6}};
    re_value_t ten = {RE_VALUE_INT64, {.int64_value = 10}};
    ASSERT_NOT_NULL(engine);
    ASSERT_NOT_NULL(window);
    ASSERT_EQ(re_stream_analytics_create(NULL, 1000u, &analytics), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_stream_analytics_create(engine, 1000u, NULL), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_stream_analytics_create(engine, 1000u, &analytics), RE_STATUS_OK);
    ASSERT_NOT_NULL(analytics);
    re_stream_analytics_destroy(NULL); /* NULL destroy is an accepted no-op. */
    ASSERT_EQ(re_stream_analytics_aggregate_cached(analytics, (re_string_t){NULL, 0u},
        window, &filter_t, RE_STREAM_AGGREGATE_SUM, 100u, &result),
        RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_stream_window_record_v1(window, 10u, text("T"), &five), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 20u, text("T"), &nine), RE_STATUS_OK);
    /* t=100: miss computes sum 14 and caches it. */
    ASSERT_EQ(re_stream_analytics_aggregate_cached(analytics, text("k"),
        window, &filter_t, RE_STREAM_AGGREGATE_SUM, 100u, &result), RE_STATUS_OK);
    ASSERT_EQ(result.count, 2u);
    ASSERT_FLOAT_EQ(result.sum, 14.0, 0.0001);
    /* The window changes under the cached entry. */
    ASSERT_EQ(re_stream_window_record_v1(window, 30u, text("T"), &six), RE_STATUS_OK);
    /* t=500 (delta 400 < ttl 1000): hit returns the STALE 14
     * (f80a541 src/streaming/aggregator.rs:311). */
    ASSERT_EQ(re_stream_analytics_aggregate_cached(analytics, text("k"),
        window, &filter_t, RE_STREAM_AGGREGATE_SUM, 500u, &result), RE_STATUS_OK);
    ASSERT_FLOAT_EQ(result.sum, 14.0, 0.0001);
    /* t=1100 (delta 1000, NOT < ttl): miss recomputes 20 and refreshes. */
    ASSERT_EQ(re_stream_analytics_aggregate_cached(analytics, text("k"),
        window, &filter_t, RE_STREAM_AGGREGATE_SUM, 1100u, &result), RE_STATUS_OK);
    ASSERT_FLOAT_EQ(result.sum, 20.0, 0.0001);
    /* A different kind under the same key is a different entry (identity
     * hardening over upstream's string-only key) and does not clobber SUM. */
    ASSERT_EQ(re_stream_analytics_aggregate_cached(analytics, text("k"),
        window, &filter_t, RE_STREAM_AGGREGATE_COUNT, 1110u, &result), RE_STATUS_OK);
    ASSERT_EQ(result.count, 3u);
    ASSERT_EQ(re_stream_analytics_aggregate_cached(analytics, text("k"),
        window, &filter_t, RE_STREAM_AGGREGATE_SUM, 1120u, &result), RE_STATUS_OK);
    ASSERT_FLOAT_EQ(result.sum, 20.0, 0.0001);
    /* A different filter event_type under the same key+kind misses too, and
     * does not clobber the "T" entry. */
    ASSERT_EQ(re_stream_analytics_aggregate_cached(analytics, text("k"),
        window, &filter_u, RE_STREAM_AGGREGATE_COUNT, 1130u, &result), RE_STATUS_OK);
    ASSERT_EQ(result.count, 0u);
    ASSERT_EQ(re_stream_analytics_aggregate_cached(analytics, text("k"),
        window, &filter_t, RE_STREAM_AGGREGATE_COUNT, 1140u, &result), RE_STATUS_OK);
    ASSERT_EQ(result.count, 3u);
    /* Past the TTL the SUM entry recomputes against the mutated window. */
    ASSERT_EQ(re_stream_window_record_v1(window, 40u, text("T"), &ten), RE_STATUS_OK);
    ASSERT_EQ(re_stream_analytics_aggregate_cached(analytics, text("k"),
        window, &filter_t, RE_STREAM_AGGREGATE_SUM, 2121u, &result), RE_STATUS_OK);
    ASSERT_FLOAT_EQ(result.sum, 30.0, 0.0001);
    re_stream_window_destroy(window);
    re_stream_analytics_destroy(analytics);
    re_engine_destroy(engine);
}

TEST(stream_analytics_cache_evict_all_on_miss) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_analytics_t *analytics = NULL;
    re_stream_window_t *window = make_sliding_window(engine, RE_LATE_EVENT_DROP, 0u);
    re_stream_filter_options_t filter = {sizeof(filter), RE_STREAM_WINDOW_ABI_VERSION,
        text("T"), (re_string_t){NULL, 0u}, 0.0};
    re_stream_aggregate_result_t result = {sizeof(result), 0u, 0.0, 0.0, 0.0, 0.0,
        {RE_VALUE_NONE, {0}}, {RE_VALUE_NONE, {0}}, 0.0, 0.0};
    re_value_t five = {RE_VALUE_INT64, {.int64_value = 5}};
    re_value_t ten = {RE_VALUE_INT64, {.int64_value = 10}};
    re_value_t twenty = {RE_VALUE_INT64, {.int64_value = 20}};
    ASSERT_NOT_NULL(window);
    ASSERT_EQ(re_stream_analytics_create(engine, 1000u, &analytics), RE_STATUS_OK);
    /* Upstream evicts ALL past-TTL entries on every miss (the retain at
     * f80a541 src/streaming/aggregator.rs:323). The retain pass itself is
     * unobservable through the public contract - a past-TTL entry misses on
     * lookup regardless - so this pins the multi-key timeline around the
     * miss: distinct keys keep independent timestamps, a miss refreshes only
     * its own entry, and no stale hit survives the TTL. */
    ASSERT_EQ(re_stream_window_record_v1(window, 10u, text("T"), &five), RE_STATUS_OK);
    ASSERT_EQ(re_stream_analytics_aggregate_cached(analytics, text("A"),
        window, &filter, RE_STREAM_AGGREGATE_SUM, 0u, &result), RE_STATUS_OK);
    ASSERT_FLOAT_EQ(result.sum, 5.0, 0.0001);
    ASSERT_EQ(re_stream_window_record_v1(window, 20u, text("T"), &five), RE_STATUS_OK);
    ASSERT_EQ(re_stream_analytics_aggregate_cached(analytics, text("B"),
        window, &filter, RE_STREAM_AGGREGATE_SUM, 500u, &result), RE_STATUS_OK);
    ASSERT_FLOAT_EQ(result.sum, 10.0, 0.0001);
    /* A survives B's miss (delta 500 < ttl) and still hits with the stale 5. */
    ASSERT_EQ(re_stream_window_record_v1(window, 30u, text("T"), &ten), RE_STATUS_OK);
    ASSERT_EQ(re_stream_analytics_aggregate_cached(analytics, text("A"),
        window, &filter, RE_STREAM_AGGREGATE_SUM, 900u, &result), RE_STATUS_OK);
    ASSERT_FLOAT_EQ(result.sum, 5.0, 0.0001);
    /* C's miss at t=1500 evicts A (delta 1500) and B (delta 1000). */
    ASSERT_EQ(re_stream_analytics_aggregate_cached(analytics, text("C"),
        window, &filter, RE_STREAM_AGGREGATE_SUM, 1500u, &result), RE_STATUS_OK);
    ASSERT_FLOAT_EQ(result.sum, 20.0, 0.0001);
    ASSERT_EQ(re_stream_window_record_v1(window, 40u, text("T"), &twenty), RE_STATUS_OK);
    /* A and B recompute against the mutated window instead of serving the
     * stale 5/10, and the refreshed A entry hits afterwards. */
    ASSERT_EQ(re_stream_analytics_aggregate_cached(analytics, text("A"),
        window, &filter, RE_STREAM_AGGREGATE_SUM, 1501u, &result), RE_STATUS_OK);
    ASSERT_FLOAT_EQ(result.sum, 40.0, 0.0001);
    ASSERT_EQ(re_stream_analytics_aggregate_cached(analytics, text("B"),
        window, &filter, RE_STREAM_AGGREGATE_SUM, 1502u, &result), RE_STATUS_OK);
    ASSERT_FLOAT_EQ(result.sum, 40.0, 0.0001);
    ASSERT_EQ(re_stream_analytics_aggregate_cached(analytics, text("A"),
        window, &filter, RE_STREAM_AGGREGATE_SUM, 2000u, &result), RE_STATUS_OK);
    ASSERT_FLOAT_EQ(result.sum, 40.0, 0.0001);
    re_stream_window_destroy(window);
    re_stream_analytics_destroy(analytics);
    re_engine_destroy(engine);
}

TEST(stream_analytics_moving_average_global_not_of_averages) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_analytics_t *analytics = NULL;
    re_stream_window_t *w1 = make_sliding_window(engine, RE_LATE_EVENT_DROP, 0u);
    re_stream_window_t *w2 = make_sliding_window(engine, RE_LATE_EVENT_DROP, 0u);
    re_stream_window_t *w3 = make_sliding_window(engine, RE_LATE_EVENT_DROP, 0u);
    const re_stream_window_t *windows[3];
    double out = 0.0;
    re_value_t hundred = {RE_VALUE_DOUBLE, {.double_value = 100.0}};
    re_value_t two = {RE_VALUE_DOUBLE, {.double_value = 2.0}};
    re_value_t four = {RE_VALUE_INT64, {.int64_value = 4}};
    re_value_t six = {RE_VALUE_DOUBLE, {.double_value = 6.0}};
    re_value_t fifty = {RE_VALUE_DOUBLE, {.double_value = 50.0}};
    re_value_t distractor = {RE_VALUE_DOUBLE, {.double_value = 1000.0}};
    re_value_t text_value = {RE_VALUE_STRING, {.string = {"s", 1u}}};
    ASSERT_NOT_NULL(w1); ASSERT_NOT_NULL(w2); ASSERT_NOT_NULL(w3);
    ASSERT_EQ(re_stream_analytics_create(engine, 0u, &analytics), RE_STATUS_OK);
    /* Unequal window sizes pin the global average: upstream divides the total
     * sum by the total event count, NOT an average of per-window averages
     * (f80a541 src/streaming/aggregator.rs:339-345). */
    ASSERT_EQ(re_stream_window_record_v1(w1, 10u, text("T"), &hundred), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(w2, 10u, text("T"), &two), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(w2, 20u, text("T"), &four), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(w2, 30u, text("T"), &six), RE_STATUS_OK);
    /* Other-name events and non-numeric same-name events are skipped. */
    ASSERT_EQ(re_stream_window_record_v1(w2, 40u, text("U"), &distractor), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(w2, 50u, text("T"), &text_value), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(w3, 10u, text("T"), &fifty), RE_STATUS_OK);
    windows[0] = w1; windows[1] = w2; windows[2] = w3;
    /* last_n=2 selects w2+w3: (2+4+6+50)/4 = 15.5; an average of the
     * per-window averages (4 and 50) would be 27. */
    ASSERT_EQ(re_stream_analytics_moving_average(analytics, windows, 3u,
        text("T"), 2u, &out), RE_STATUS_OK);
    ASSERT_FLOAT_EQ(out, 15.5, 0.0001);
    /* last_n beyond the array clamps to every window: 162/5 = 32.4. */
    ASSERT_EQ(re_stream_analytics_moving_average(analytics, windows, 3u,
        text("T"), 100u, &out), RE_STATUS_OK);
    ASSERT_FLOAT_EQ(out, 32.4, 0.0001);
    ASSERT_EQ(re_stream_analytics_moving_average(analytics, windows, 3u,
        text("T"), 1u, &out), RE_STATUS_OK);
    ASSERT_FLOAT_EQ(out, 50.0, 0.0001);
    /* Empty selections and empty matches are upstream's None. */
    ASSERT_EQ(re_stream_analytics_moving_average(analytics, windows, 0u,
        text("T"), 2u, &out), RE_STATUS_NOT_FOUND);
    ASSERT_EQ(re_stream_analytics_moving_average(analytics, windows, 3u,
        text("T"), 0u, &out), RE_STATUS_NOT_FOUND);
    ASSERT_EQ(re_stream_analytics_moving_average(analytics, windows, 3u,
        text("absent"), 2u, &out), RE_STATUS_NOT_FOUND);
    ASSERT_EQ(re_stream_analytics_moving_average(analytics, windows, 3u,
        (re_string_t){NULL, 0u}, 2u, &out), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_stream_analytics_moving_average(analytics, NULL, 3u,
        text("T"), 2u, &out), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_stream_analytics_moving_average(analytics, windows, 3u,
        text("T"), 2u, NULL), RE_STATUS_INVALID_ARGUMENT);
    re_stream_window_destroy(w1);
    re_stream_window_destroy(w2);
    re_stream_window_destroy(w3);
    re_stream_analytics_destroy(analytics);
    re_engine_destroy(engine);
}

TEST(stream_analytics_detect_anomalies_window_and_history_minimums) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_analytics_t *analytics = NULL;
    re_stream_window_t *w1 = make_events_window(engine, "T", 10.0, 1u, 5u);
    re_stream_window_t *w2 = make_events_window(engine, "T", 10.0, 1u, 5u);
    re_stream_window_t *s1 = make_events_window(engine, "T", 10.0, 1u, 4u);
    re_stream_window_t *s2 = make_events_window(engine, "T", 10.0, 1u, 4u);
    re_stream_window_t *last = make_events_window(engine, "T", 10.0, 100u, 1u);
    const re_stream_window_t *two[2];
    const re_stream_window_t *thin[3];
    uint64_t out_ts[4];
    size_t out_count = 99u;
    ASSERT_NOT_NULL(w1); ASSERT_NOT_NULL(w2); ASSERT_NOT_NULL(last);
    ASSERT_NOT_NULL(s1); ASSERT_NOT_NULL(s2);
    ASSERT_EQ(re_stream_analytics_create(engine, 0u, &analytics), RE_STATUS_OK);
    two[0] = w1; two[1] = w2;
    thin[0] = s1; thin[1] = s2; thin[2] = last;
    /* Fewer than 3 windows is INVALID_ARGUMENT (upstream silently returns no
     * anomalies - documented divergence, aggregator.rs:359). */
    ASSERT_EQ(re_stream_analytics_detect_anomalies(analytics, two, 2u,
        text("T"), 2.0, out_ts, 4u, &out_count), RE_STATUS_INVALID_ARGUMENT);
    /* Fewer than 10 historical values is NOT_FOUND (upstream: no anomalies,
     * aggregator.rs:371). */
    ASSERT_EQ(re_stream_analytics_detect_anomalies(analytics, thin, 3u,
        text("T"), 2.0, out_ts, 4u, &out_count), RE_STATUS_NOT_FOUND);
    ASSERT_EQ(re_stream_analytics_detect_anomalies(analytics, thin, 3u,
        text("T"), 2.0, out_ts, 4u, NULL), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_stream_analytics_detect_anomalies(analytics, thin, 3u,
        text("T"), 2.0, NULL, 4u, &out_count), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_stream_analytics_detect_anomalies(analytics, thin, 3u,
        (re_string_t){NULL, 0u}, 2.0, out_ts, 4u, &out_count),
        RE_STATUS_INVALID_ARGUMENT);
    destroy_windows((re_stream_window_t **)two, 2u);
    destroy_windows((re_stream_window_t **)thin, 3u);
    re_stream_analytics_destroy(analytics);
    re_engine_destroy(engine);
}

TEST(stream_analytics_detect_anomalies_flags_exact_outliers) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_analytics_t *analytics = NULL;
    re_stream_window_t *w1 = make_events_window(engine, "T", 10.0, 1u, 5u);
    re_stream_window_t *w2 = make_events_window(engine, "T", 12.0, 1u, 5u);
    re_stream_window_t *last = make_sliding_window(engine, RE_LATE_EVENT_DROP, 0u);
    const re_stream_window_t *windows[3];
    uint64_t out_ts[4] = {0u, 0u, 0u, 0u};
    size_t out_count = 0u;
    re_value_t in_line = {RE_VALUE_DOUBLE, {.double_value = 11.0}};
    re_value_t high = {RE_VALUE_DOUBLE, {.double_value = 14.0}};
    re_value_t low = {RE_VALUE_DOUBLE, {.double_value = 7.0}};
    ASSERT_NOT_NULL(w1); ASSERT_NOT_NULL(w2); ASSERT_NOT_NULL(last);
    ASSERT_EQ(re_stream_analytics_create(engine, 0u, &analytics), RE_STATUS_OK);
    /* Historical: five 10s and five 12s -> population mean 11, stddev 1. */
    ASSERT_EQ(re_stream_window_record_v1(last, 100u, text("T"), &in_line), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(last, 200u, text("T"), &high), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(last, 300u, text("T"), &low), RE_STATUS_OK);
    windows[0] = w1; windows[1] = w2; windows[2] = last;
    /* z-scores 0, +3, -4: threshold 2 flags exactly the two outliers and
     * reports their timestamps in window order (the local identity -
     * upstream returns event IDs, aggregator.rs:383-391). */
    ASSERT_EQ(re_stream_analytics_detect_anomalies(analytics, windows, 3u,
        text("T"), 2.0, out_ts, 4u, &out_count), RE_STATUS_OK);
    ASSERT_EQ(out_count, 2u);
    ASSERT_EQ(out_ts[0], 200u);
    ASSERT_EQ(out_ts[1], 300u);
    /* The comparison is strict: threshold 3 lets z == +3 pass. */
    ASSERT_EQ(re_stream_analytics_detect_anomalies(analytics, windows, 3u,
        text("T"), 3.0, out_ts, 4u, &out_count), RE_STATUS_OK);
    ASSERT_EQ(out_count, 1u);
    ASSERT_EQ(out_ts[0], 300u);
    /* Population-vs-sample discrimination (aggregator.rs:375-376 divides by
     * N): the SAMPLE stddev (N-1 divisor) would give z-scores ~2.85/~3.80, so
     * a 2.9 threshold would flag only ts 300; the population z-scores +3/-4
     * flag both. */
    ASSERT_EQ(re_stream_analytics_detect_anomalies(analytics, windows, 3u,
        text("T"), 2.9, out_ts, 4u, &out_count), RE_STATUS_OK);
    ASSERT_EQ(out_count, 2u);
    ASSERT_EQ(out_ts[0], 200u);
    ASSERT_EQ(out_ts[1], 300u);
    /* Capacity overflow reports the total and fills what fits
     * (the codebase's RE_STATUS_LIMIT buffer idiom). */
    out_ts[0] = 0u;
    ASSERT_EQ(re_stream_analytics_detect_anomalies(analytics, windows, 3u,
        text("T"), 2.0, out_ts, 1u, &out_count), RE_STATUS_LIMIT);
    ASSERT_EQ(out_count, 2u);
    ASSERT_EQ(out_ts[0], 200u);
    /* capacity 0 with a NULL array is the sizing query: LIMIT plus the
     * required capacity (the re_rule_template_instantiate idiom). */
    ASSERT_EQ(re_stream_analytics_detect_anomalies(analytics, windows, 3u,
        text("T"), 2.0, NULL, 0u, &out_count), RE_STATUS_LIMIT);
    ASSERT_EQ(out_count, 2u);
    destroy_windows((re_stream_window_t **)windows, 3u);
    re_stream_analytics_destroy(analytics);
    re_engine_destroy(engine);
}

TEST(stream_analytics_detect_anomalies_zero_stddev_flags_nothing) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_analytics_t *analytics = NULL;
    re_stream_window_t *w1 = make_events_window(engine, "T", 5.0, 1u, 5u);
    re_stream_window_t *w2 = make_events_window(engine, "T", 5.0, 1u, 5u);
    re_stream_window_t *last = make_sliding_window(engine, RE_LATE_EVENT_DROP, 0u);
    const re_stream_window_t *windows[3];
    uint64_t out_ts[4];
    size_t out_count = 99u;
    re_value_t in_line = {RE_VALUE_DOUBLE, {.double_value = 5.0}};
    re_value_t outlier = {RE_VALUE_DOUBLE, {.double_value = 999.0}};
    ASSERT_NOT_NULL(w1); ASSERT_NOT_NULL(w2); ASSERT_NOT_NULL(last);
    ASSERT_EQ(re_stream_analytics_create(engine, 0u, &analytics), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(last, 1u, text("T"), &in_line), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(last, 2u, text("T"), &outlier), RE_STATUS_OK);
    windows[0] = w1; windows[1] = w2; windows[2] = last;
    /* Zero historical stddev flags nothing (documented guard: upstream
     * divides by zero - 5 gets a NaN z-score and passes, 999 gets +inf and
     * is flagged; local reports none). */
    ASSERT_EQ(re_stream_analytics_detect_anomalies(analytics, windows, 3u,
        text("T"), 1.0, out_ts, 4u, &out_count), RE_STATUS_OK);
    ASSERT_EQ(out_count, 0u);
    destroy_windows((re_stream_window_t **)windows, 3u);
    re_stream_analytics_destroy(analytics);
    re_engine_destroy(engine);
}

TEST(stream_analytics_trend_direction_boundaries) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_analytics_t *analytics = NULL;
    re_stream_window_t *w[4] = {NULL, NULL, NULL, NULL};
    re_stream_trend_t trend = RE_STREAM_TREND_STABLE;
    static const double increasing[4] = {100.0, 100.0, 106.0, 106.0};
    static const double increasing_edge[4] = {100.0, 100.0, 105.0, 105.0};
    static const double decreasing[4] = {100.0, 100.0, 94.0, 94.0};
    static const double decreasing_edge[4] = {100.0, 100.0, 95.0, 95.0};
    ASSERT_NOT_NULL(engine);
    ASSERT_EQ(re_stream_analytics_create(engine, 0u, &analytics), RE_STATUS_OK);
    /* change_percent > +5 is Increasing (aggregator.rs:416-418). */
    ASSERT_EQ(build_value_windows(engine, increasing, 4u, w, 4u), 4u);
    ASSERT_EQ(re_stream_analytics_calculate_trend(analytics,
        (const re_stream_window_t *const *)w, 4u, text("T"), &trend), RE_STATUS_OK);
    ASSERT_EQ(trend, RE_STREAM_TREND_INCREASING);
    destroy_windows(w, 4u);
    /* Exactly +5 is the boundary: Stable. */
    ASSERT_EQ(build_value_windows(engine, increasing_edge, 4u, w, 4u), 4u);
    ASSERT_EQ(re_stream_analytics_calculate_trend(analytics,
        (const re_stream_window_t *const *)w, 4u, text("T"), &trend), RE_STATUS_OK);
    ASSERT_EQ(trend, RE_STREAM_TREND_STABLE);
    destroy_windows(w, 4u);
    /* change_percent < -5 is Decreasing. */
    ASSERT_EQ(build_value_windows(engine, decreasing, 4u, w, 4u), 4u);
    ASSERT_EQ(re_stream_analytics_calculate_trend(analytics,
        (const re_stream_window_t *const *)w, 4u, text("T"), &trend), RE_STATUS_OK);
    ASSERT_EQ(trend, RE_STREAM_TREND_DECREASING);
    destroy_windows(w, 4u);
    /* Exactly -5 is Stable. */
    ASSERT_EQ(build_value_windows(engine, decreasing_edge, 4u, w, 4u), 4u);
    ASSERT_EQ(re_stream_analytics_calculate_trend(analytics,
        (const re_stream_window_t *const *)w, 4u, text("T"), &trend), RE_STATUS_OK);
    ASSERT_EQ(trend, RE_STREAM_TREND_STABLE);
    destroy_windows(w, 4u);
    /* One window is INVALID_ARGUMENT (upstream returns Stable - documented
     * divergence, aggregator.rs:402). */
    ASSERT_EQ(build_value_windows(engine, increasing, 1u, w, 4u), 1u);
    ASSERT_EQ(re_stream_analytics_calculate_trend(analytics,
        (const re_stream_window_t *const *)w, 1u, text("T"), &trend),
        RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_stream_analytics_calculate_trend(analytics,
        (const re_stream_window_t *const *)w, 1u, (re_string_t){NULL, 0u}, &trend),
        RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_stream_analytics_calculate_trend(analytics,
        (const re_stream_window_t *const *)w, 1u, text("T"), NULL),
        RE_STATUS_INVALID_ARGUMENT);
    destroy_windows(w, 1u);
    re_stream_analytics_destroy(analytics);
    re_engine_destroy(engine);
}

TEST(stream_analytics_trend_odd_count_split_second_half_takes_extra) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_analytics_t *analytics = NULL;
    re_stream_window_t *w[4] = {NULL, NULL, NULL, NULL};
    re_stream_trend_t trend = RE_STREAM_TREND_STABLE;
    static const double split_probe[3] = {100.0, 200.0, 100.0};
    ASSERT_NOT_NULL(engine);
    ASSERT_EQ(re_stream_analytics_create(engine, 0u, &analytics), RE_STATUS_OK);
    /* used == 3 splits half = used/2 = 1 (aggregator.rs:411,
     * &averages[..len/2] / &averages[len/2..]): the SECOND half takes the odd
     * extra, so first_avg = 100 and second_avg = (200 + 100) / 2 = 150 ->
     * +50% Increasing. The other convention (first half takes the extra)
     * would give first_avg = 150, second_avg = 100 -> -33% Decreasing. */
    ASSERT_EQ(build_value_windows(engine, split_probe, 3u, w, 4u), 3u);
    ASSERT_EQ(re_stream_analytics_calculate_trend(analytics,
        (const re_stream_window_t *const *)w, 3u, text("T"), &trend), RE_STATUS_OK);
    ASSERT_EQ(trend, RE_STREAM_TREND_INCREASING);
    destroy_windows(w, 3u);
    re_stream_analytics_destroy(analytics);
    re_engine_destroy(engine);
}

TEST(stream_analytics_trend_first_avg_zero_guard) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_analytics_t *analytics = NULL;
    re_stream_window_t *w[4] = {NULL, NULL, NULL, NULL};
    re_stream_trend_t trend = RE_STREAM_TREND_INCREASING;
    static const double zero_to_ten[4] = {0.0, 0.0, 10.0, 10.0};
    static const double zero_to_zero[4] = {0.0, 0.0, 0.0, 0.0};
    ASSERT_NOT_NULL(engine);
    ASSERT_EQ(re_stream_analytics_create(engine, 0u, &analytics), RE_STATUS_OK);
    /* first_avg == 0 reports STABLE (documented division guard: upstream's
     * f64 division would compute +inf here and say Increasing). */
    ASSERT_EQ(build_value_windows(engine, zero_to_ten, 4u, w, 4u), 4u);
    ASSERT_EQ(re_stream_analytics_calculate_trend(analytics,
        (const re_stream_window_t *const *)w, 4u, text("T"), &trend), RE_STATUS_OK);
    ASSERT_EQ(trend, RE_STREAM_TREND_STABLE);
    destroy_windows(w, 4u);
    /* 0 -> 0 is STABLE under both (upstream NaN also lands on Stable). */
    ASSERT_EQ(build_value_windows(engine, zero_to_zero, 4u, w, 4u), 4u);
    ASSERT_EQ(re_stream_analytics_calculate_trend(analytics,
        (const re_stream_window_t *const *)w, 4u, text("T"), &trend), RE_STATUS_OK);
    ASSERT_EQ(trend, RE_STREAM_TREND_STABLE);
    destroy_windows(w, 4u);
    re_stream_analytics_destroy(analytics);
    re_engine_destroy(engine);
}

/*
 * Sub-project C Task C4: watermark-driven window closure (a documented local
 * composition - upstream watermarks only gate recording, f80a541
 * src/streaming/watermark.rs:340) and the cross-stream join API (upstream
 * StreamJoinNode, src/rete/stream_join_node.rs). Closure default OFF keeps
 * the pre-C4 behavior byte-identical; the join mirrors the upstream
 * semantics with the documented local composition (matched pairs once at
 * record time, unmatched outer sides once at watermark pass).
 */

static re_stream_window_t *make_bounded_window(re_engine_t *engine,
                                               re_stream_window_kind_t kind,
                                               re_late_event_policy_t policy,
                                               uint64_t retention_ms,
                                               uint64_t allowed_lateness_ms,
                                               uint32_t closure_flag) {
    re_stream_window_t *window = NULL;
    re_stream_window_options_t options = {sizeof(options), RE_STREAM_WINDOW_ABI_VERSION,
        kind, policy, retention_ms, 8u, 1024u, allowed_lateness_ms, closure_flag};
    if (re_stream_window_create_v1(engine, &options, &window) != RE_STATUS_OK) return NULL;
    return window;
}

/* COUNT over the catch-all filter (COUNT keeps its 0/OK behavior). */
static uint64_t bounded_window_count(re_stream_window_t *window) {
    re_stream_filter_options_t filter = {sizeof(filter), RE_STREAM_WINDOW_ABI_VERSION,
        (re_string_t){NULL, 0u}, (re_string_t){NULL, 0u}, 0.0};
    re_stream_aggregate_result_t result = {sizeof(result), 0u, 0.0, 0.0, 0.0, 0.0,
        {RE_VALUE_NONE, {0}}, {RE_VALUE_NONE, {0}}, 0.0, 0.0};
    if (re_stream_window_aggregate_v1(window, &filter, RE_STREAM_AGGREGATE_COUNT,
                                      &result) != RE_STATUS_OK) return 0u;
    return result.count;
}

static re_stream_join_t *make_join(re_engine_t *engine, re_stream_join_type_t type,
                                   re_stream_join_strategy_t strategy) {
    re_stream_join_t *join = NULL;
    if (re_stream_join_create(engine, text("L"), text("R"), type, strategy,
                              &join) != RE_STATUS_OK) return NULL;
    return join;
}

static int join_match_eq(const re_stream_join_match_t *match, const char *key,
                         uint64_t left_ts, uint64_t right_ts, uint64_t join_ts) {
    return match->key.size == strlen(key) &&
        memcmp(match->key.data, key, match->key.size) == 0 &&
        match->left_timestamp_ms == left_ts && match->right_timestamp_ms == right_ts &&
        match->join_timestamp_ms == join_ts;
}

TEST(stream_closure_flag_off_preserves_tumbling_behavior) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_window_t *window = make_bounded_window(engine, RE_STREAM_WINDOW_TUMBLING,
        RE_LATE_EVENT_DROP, 1000u, 1000u, 0u);
    re_stream_window_t *accept = make_bounded_window(engine, RE_STREAM_WINDOW_TUMBLING,
        RE_LATE_EVENT_ACCEPT, 1000u, 100u, 0u);
    re_value_t v = {RE_VALUE_INT64, {.int64_value = 1}};
    ASSERT_NOT_NULL(window);
    ASSERT_NOT_NULL(accept);
    /* Pre-C4 regression switch: a late-but-tolerated bucket record rewinds. */
    ASSERT_EQ(re_stream_window_record_v1(window, 2500u, text("a"), &v), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 1600u, text("b"), &v), RE_STATUS_OK);
    ASSERT_EQ(bounded_window_count(window), 1u);
    /* Past the allowed lateness the DROP policy still reports NOT_FOUND. */
    ASSERT_EQ(re_stream_window_record_v1(window, 500u, text("c"), &v), RE_STATUS_NOT_FOUND);
    /* ACCEPT flag-off: a late record is silently accepted, not recorded. */
    ASSERT_EQ(re_stream_window_record_v1(accept, 500u, text("a"), &v), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(accept, 1600u, text("b"), &v), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(accept, 550u, text("c"), &v), RE_STATUS_OK);
    ASSERT_EQ(bounded_window_count(accept), 1u);
    re_stream_window_destroy(window);
    re_stream_window_destroy(accept);
    re_engine_destroy(engine);
}

TEST(stream_closure_flag_off_preserves_session_behavior) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_window_t *window = make_bounded_window(engine, RE_STREAM_WINDOW_SESSION,
        RE_LATE_EVENT_ACCEPT, 50u, 50u, 0u);
    re_value_t v = {RE_VALUE_INT64, {.int64_value = 1}};
    ASSERT_NOT_NULL(window);
    ASSERT_EQ(re_stream_window_record_v1(window, 100u, text("a"), &v), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 140u, text("b"), &v), RE_STATUS_OK);
    /* Late ACCEPT: silent OK, not recorded. */
    ASSERT_EQ(re_stream_window_record_v1(window, 10u, text("c"), &v), RE_STATUS_OK);
    ASSERT_EQ(bounded_window_count(window), 2u);
    /* Past session_end a new session starts and the old events are dropped. */
    ASSERT_EQ(re_stream_window_record_v1(window, 191u, text("d"), &v), RE_STATUS_OK);
    ASSERT_EQ(bounded_window_count(window), 1u);
    re_stream_window_destroy(window);
    re_engine_destroy(engine);
}

TEST(stream_closure_tumbling_closes_at_boundary_plus_lateness) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_window_t *window = make_bounded_window(engine, RE_STREAM_WINDOW_TUMBLING,
        RE_LATE_EVENT_DROP, 1000u, 600u, 1u);
    re_value_t v = {RE_VALUE_INT64, {.int64_value = 1}};
    ASSERT_NOT_NULL(window);
    ASSERT_EQ(re_stream_window_record_v1(window, 1500u, text("a"), &v), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 2599u, text("b"), &v), RE_STATUS_OK);
    /* watermark 2599 < bucket_end 2000 + lateness 600: bucket 1 still open. */
    ASSERT_EQ(re_stream_window_record_v1(window, 1999u, text("c"), &v), RE_STATUS_OK);
    /* watermark 2600 closes bucket 1 exactly at the >= boundary. */
    ASSERT_EQ(re_stream_window_record_v1(window, 2600u, text("d"), &v), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 1999u, text("e"), &v), RE_STATUS_NOT_FOUND);
    ASSERT_EQ(re_stream_window_record_v1(window, 1500u, text("f"), &v), RE_STATUS_NOT_FOUND);
    /* The current bucket is never closed by its own watermark. */
    ASSERT_EQ(re_stream_window_record_v1(window, 2000u, text("g"), &v), RE_STATUS_OK);
    ASSERT_EQ(bounded_window_count(window), 2u);
    re_stream_window_destroy(window);
    re_engine_destroy(engine);
}

TEST(stream_closure_tumbling_accept_closed_not_retained_rejected) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_window_t *window = make_bounded_window(engine, RE_STREAM_WINDOW_TUMBLING,
        RE_LATE_EVENT_ACCEPT, 1000u, 100u, 1u);
    re_value_t v = {RE_VALUE_INT64, {.int64_value = 1}};
    ASSERT_NOT_NULL(window);
    ASSERT_EQ(re_stream_window_record_v1(window, 500u, text("a"), &v), RE_STATUS_OK);
    /* The watermark advance to 1600 closes bucket 0 (>= 1000 + 100) as a side
     * effect; bucket 0's events are dropped by the usual bucket switch. */
    ASSERT_EQ(re_stream_window_record_v1(window, 1600u, text("b"), &v), RE_STATUS_OK);
    /* ACCEPT on a closed, no-longer-retained bucket: NOT_FOUND (flag-off
     * behavior was the silent OK pinned above). */
    ASSERT_EQ(re_stream_window_record_v1(window, 550u, text("c"), &v), RE_STATUS_NOT_FOUND);
    /* An open current-bucket record within lateness still records. */
    ASSERT_EQ(re_stream_window_record_v1(window, 1550u, text("d"), &v), RE_STATUS_OK);
    ASSERT_EQ(bounded_window_count(window), 2u);
    re_stream_window_destroy(window);
    re_engine_destroy(engine);
}

TEST(stream_closure_tumbling_error_policy_reports_error) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_window_t *window = make_bounded_window(engine, RE_STREAM_WINDOW_TUMBLING,
        RE_LATE_EVENT_ERROR, 1000u, 0u, 1u);
    re_value_t v = {RE_VALUE_INT64, {.int64_value = 1}};
    ASSERT_NOT_NULL(window);
    ASSERT_EQ(re_stream_window_record_v1(window, 500u, text("a"), &v), RE_STATUS_OK);
    /* watermark 1000 closes bucket 0 exactly (>= 1000 + 0). */
    ASSERT_EQ(re_stream_window_record_v1(window, 1000u, text("b"), &v), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 999u, text("c"), &v), RE_STATUS_ERROR);
    ASSERT_EQ(re_stream_window_record_v1(window, 1000u, text("d"), &v), RE_STATUS_OK);
    ASSERT_EQ(bounded_window_count(window), 2u);
    re_stream_window_destroy(window);
    re_engine_destroy(engine);
}

TEST(stream_closure_session_drop_boundary) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_window_t *window = make_bounded_window(engine, RE_STREAM_WINDOW_SESSION,
        RE_LATE_EVENT_DROP, 1000u, 100u, 1u);
    re_value_t v = {RE_VALUE_INT64, {.int64_value = 1}};
    ASSERT_NOT_NULL(window);
    ASSERT_EQ(re_stream_window_record_v1(window, 1000u, text("a"), &v), RE_STATUS_OK);
    /* Accepted just before: extends the open session (end 2500). */
    ASSERT_EQ(re_stream_window_record_v1(window, 1500u, text("b"), &v), RE_STATUS_OK);
    /* The new session at 2600 advances the watermark past the old session's
     * end + lateness (2500 + 100): the old session closes as a side effect. */
    ASSERT_EQ(re_stream_window_record_v1(window, 2600u, text("c"), &v), RE_STATUS_OK);
    /* Records targeting the closed session are rejected per the DROP policy;
     * for DROP the closure outcome equals the late gate's (documented). */
    ASSERT_EQ(re_stream_window_record_v1(window, 2400u, text("d"), &v), RE_STATUS_NOT_FOUND);
    ASSERT_EQ(re_stream_window_record_v1(window, 400u, text("e"), &v), RE_STATUS_NOT_FOUND);
    ASSERT_EQ(bounded_window_count(window), 1u);
    re_stream_window_destroy(window);
    re_engine_destroy(engine);
}

TEST(stream_closure_session_accept_records_closed_retained) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_window_t *window = make_bounded_window(engine, RE_STREAM_WINDOW_SESSION,
        RE_LATE_EVENT_ACCEPT, 1000u, 0u, 1u);
    re_stream_window_t *control = make_bounded_window(engine, RE_STREAM_WINDOW_SESSION,
        RE_LATE_EVENT_ACCEPT, 1000u, 0u, 0u);
    re_value_t v = {RE_VALUE_INT64, {.int64_value = 1}};
    ASSERT_NOT_NULL(window);
    ASSERT_NOT_NULL(control);
    ASSERT_EQ(re_stream_window_record_v1(window, 1000u, text("a"), &v), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 2500u, text("b"), &v), RE_STATUS_OK);
    /* The record's own session (end 1400 + 1000) is closed at watermark 2500,
     * but it lands in the retained open session, so ACCEPT records it - the
     * brief's "recorded only if still retained" acceptance semantics. */
    ASSERT_EQ(re_stream_window_record_v1(window, 1400u, text("c"), &v), RE_STATUS_OK);
    ASSERT_EQ(bounded_window_count(window), 2u);
    /* The flag-off control silently accepts without recording. */
    ASSERT_EQ(re_stream_window_record_v1(control, 1000u, text("a"), &v), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(control, 2500u, text("b"), &v), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(control, 1400u, text("c"), &v), RE_STATUS_OK);
    ASSERT_EQ(bounded_window_count(control), 1u);
    re_stream_window_destroy(window);
    re_stream_window_destroy(control);
    re_engine_destroy(engine);
}

TEST(stream_closure_sliding_flag_inert) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_window_t *drop = make_bounded_window(engine, RE_STREAM_WINDOW_SLIDING,
        RE_LATE_EVENT_DROP, 1000u, 0u, 1u);
    re_stream_window_t *accept = make_bounded_window(engine, RE_STREAM_WINDOW_SLIDING,
        RE_LATE_EVENT_ACCEPT, 1000u, 0u, 1u);
    re_value_t v = {RE_VALUE_INT64, {.int64_value = 1}};
    ASSERT_NOT_NULL(drop);
    ASSERT_NOT_NULL(accept);
    /* Sliding windows have no discrete buckets: the flag changes nothing and
     * the record gate behaves exactly as pre-C4. */
    ASSERT_EQ(re_stream_window_record_v1(drop, 100u, text("a"), &v), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(drop, 50u, text("b"), &v), RE_STATUS_NOT_FOUND);
    ASSERT_EQ(re_stream_window_record_v1(drop, 150u, text("c"), &v), RE_STATUS_OK);
    ASSERT_EQ(bounded_window_count(drop), 2u);
    ASSERT_EQ(re_stream_window_record_v1(accept, 100u, text("a"), &v), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(accept, 50u, text("b"), &v), RE_STATUS_OK);
    ASSERT_EQ(bounded_window_count(accept), 1u);
    re_stream_window_destroy(drop);
    re_stream_window_destroy(accept);
    re_engine_destroy(engine);
}

TEST(stream_window_options_pre_c4_struct_size_defaults_off) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_window_t *window = NULL;
    re_stream_window_options_t options = {sizeof(options), RE_STREAM_WINDOW_ABI_VERSION,
        RE_STREAM_WINDOW_TUMBLING, RE_LATE_EVENT_ACCEPT, 1000u, 8u, 1024u, 100u, 1u};
    re_value_t v = {RE_VALUE_INT64, {.int64_value = 1}};
    /* A pre-C4 caller passes only the pre-C4 fields: the flag defaults to 0. */
    options.struct_size = (uint32_t)offsetof(re_stream_window_options_t, watermark_drives_closure);
    ASSERT_EQ(re_stream_window_create_v1(engine, &options, &window), RE_STATUS_OK);
    ASSERT_NOT_NULL(window);
    ASSERT_EQ(re_stream_window_record_v1(window, 500u, text("a"), &v), RE_STATUS_OK);
    ASSERT_EQ(re_stream_window_record_v1(window, 1600u, text("b"), &v), RE_STATUS_OK);
    /* With the default the ACCEPT late record stays a silent OK (no closure). */
    ASSERT_EQ(re_stream_window_record_v1(window, 550u, text("c"), &v), RE_STATUS_OK);
    ASSERT_EQ(bounded_window_count(window), 1u);
    re_stream_window_destroy(window);
    /* Anything smaller than the pre-C4 size is still rejected. */
    options.struct_size = (uint32_t)offsetof(re_stream_window_options_t, watermark_drives_closure) - 1u;
    ASSERT_EQ(re_stream_window_create_v1(engine, &options, &window), RE_STATUS_INVALID_ARGUMENT);
    re_engine_destroy(engine);
}

TEST(stream_join_inner_time_window) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_join_strategy_t strategy = {RE_STREAM_JOIN_TIME_WINDOW, 10u, 0u, 0u};
    re_stream_join_t *join = make_join(engine, RE_STREAM_JOIN_INNER, strategy);
    re_stream_join_match_t matches[8];
    size_t count = 99u;
    re_value_t v = {RE_VALUE_INT64, {.int64_value = 1}};
    ASSERT_NOT_NULL(join);
    ASSERT_EQ(re_stream_join_record(join, RE_STREAM_JOIN_LEFT, text("k"), 1000u, &v), RE_STATUS_OK);
    ASSERT_EQ(re_stream_join_drain(join, matches, 8u, &count), RE_STATUS_OK);
    ASSERT_EQ(count, 0u);
    /* |1005 - 1000| <= 10: one match, join_timestamp is the later one
     * (upstream stream_join_node.rs:35). */
    ASSERT_EQ(re_stream_join_record(join, RE_STREAM_JOIN_RIGHT, text("k"), 1005u, &v), RE_STATUS_OK);
    ASSERT_EQ(re_stream_join_drain(join, matches, 8u, &count), RE_STATUS_OK);
    ASSERT_EQ(count, 1u);
    ASSERT_TRUE(join_match_eq(&matches[0], "k", 1000u, 1005u, 1005u));
    /* Outside the duration: no match. */
    ASSERT_EQ(re_stream_join_record(join, RE_STREAM_JOIN_RIGHT, text("k"), 2000u, &v), RE_STATUS_OK);
    ASSERT_EQ(re_stream_join_drain(join, matches, 8u, &count), RE_STATUS_OK);
    ASSERT_EQ(count, 0u);
    /* |2005 - 2000| = 5 matches; |2005 - 1005| does not. */
    ASSERT_EQ(re_stream_join_record(join, RE_STREAM_JOIN_LEFT, text("k"), 2005u, &v), RE_STATUS_OK);
    ASSERT_EQ(re_stream_join_drain(join, matches, 8u, &count), RE_STATUS_OK);
    ASSERT_EQ(count, 1u);
    ASSERT_TRUE(join_match_eq(&matches[0], "k", 2005u, 2000u, 2005u));
    /* Keys partition the buffers (upstream test_partition_by_key). */
    ASSERT_EQ(re_stream_join_record(join, RE_STREAM_JOIN_RIGHT, text("other"), 2006u, &v), RE_STATUS_OK);
    ASSERT_EQ(re_stream_join_drain(join, matches, 8u, &count), RE_STATUS_OK);
    ASSERT_EQ(count, 0u);
    /* The duration boundary itself is inclusive. */
    ASSERT_EQ(re_stream_join_record(join, RE_STREAM_JOIN_LEFT, text("b"), 100u, &v), RE_STATUS_OK);
    ASSERT_EQ(re_stream_join_record(join, RE_STREAM_JOIN_RIGHT, text("b"), 110u, &v), RE_STATUS_OK);
    ASSERT_EQ(re_stream_join_drain(join, matches, 8u, &count), RE_STATUS_OK);
    ASSERT_EQ(count, 1u);
    ASSERT_TRUE(join_match_eq(&matches[0], "b", 100u, 110u, 110u));
    re_stream_join_destroy(join);
    re_engine_destroy(engine);
}

TEST(stream_join_count_window_pairing_and_cap) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_join_strategy_t strategy = {RE_STREAM_JOIN_COUNT_WINDOW, 0u, 2u, 0u};
    re_stream_join_t *join = make_join(engine, RE_STREAM_JOIN_INNER, strategy);
    re_stream_join_match_t matches[8];
    size_t count = 0u;
    re_value_t v = {RE_VALUE_INT64, {.int64_value = 1}};
    ASSERT_NOT_NULL(join);
    /* The per-key buffer keeps the most recent count events; the third
     * record drops the oldest (drop-oldest + counter). */
    ASSERT_EQ(re_stream_join_record(join, RE_STREAM_JOIN_LEFT, text("k"), 100u, &v), RE_STATUS_OK);
    ASSERT_EQ(re_stream_join_record(join, RE_STREAM_JOIN_LEFT, text("k"), 200u, &v), RE_STATUS_OK);
    ASSERT_EQ(re_stream_join_record(join, RE_STREAM_JOIN_LEFT, text("k"), 300u, &v), RE_STATUS_OK);
    ASSERT_EQ(re_stream_join_dropped(join), 1u);
    /* Count windows match same-key pairs at any distance (upstream
     * is_within_window returns true, stream_join_node.rs:231). */
    ASSERT_EQ(re_stream_join_record(join, RE_STREAM_JOIN_RIGHT, text("k"), 10000u, &v), RE_STATUS_OK);
    ASSERT_EQ(re_stream_join_drain(join, matches, 8u, &count), RE_STATUS_OK);
    ASSERT_EQ(count, 2u);
    ASSERT_TRUE(join_match_eq(&matches[0], "k", 200u, 10000u, 10000u));
    ASSERT_TRUE(join_match_eq(&matches[1], "k", 300u, 10000u, 10000u));
    ASSERT_EQ(re_stream_join_record(join, RE_STREAM_JOIN_LEFT, text("k"), 400u, &v), RE_STATUS_OK);
    ASSERT_EQ(re_stream_join_drain(join, matches, 8u, &count), RE_STATUS_OK);
    ASSERT_EQ(count, 1u);
    ASSERT_TRUE(join_match_eq(&matches[0], "k", 400u, 10000u, 10000u));
    re_stream_join_destroy(join);
    re_engine_destroy(engine);
}

TEST(stream_join_session_gap) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_join_strategy_t strategy = {RE_STREAM_JOIN_SESSION_WINDOW, 0u, 0u, 500u};
    re_stream_join_t *join = make_join(engine, RE_STREAM_JOIN_INNER, strategy);
    re_stream_join_match_t matches[8];
    size_t count = 0u;
    re_value_t v = {RE_VALUE_INT64, {.int64_value = 1}};
    ASSERT_NOT_NULL(join);
    ASSERT_EQ(re_stream_join_record(join, RE_STREAM_JOIN_LEFT, text("k"), 1000u, &v), RE_STATUS_OK);
    /* |1200 - 1000| <= 500 matches. */
    ASSERT_EQ(re_stream_join_record(join, RE_STREAM_JOIN_RIGHT, text("k"), 1200u, &v), RE_STATUS_OK);
    ASSERT_EQ(re_stream_join_drain(join, matches, 8u, &count), RE_STATUS_OK);
    ASSERT_EQ(count, 1u);
    ASSERT_TRUE(join_match_eq(&matches[0], "k", 1000u, 1200u, 1200u));
    /* |1601 - 1200| <= 500 matches the buffered right event. */
    ASSERT_EQ(re_stream_join_record(join, RE_STREAM_JOIN_LEFT, text("k"), 1601u, &v), RE_STATUS_OK);
    ASSERT_EQ(re_stream_join_drain(join, matches, 8u, &count), RE_STATUS_OK);
    ASSERT_EQ(count, 1u);
    ASSERT_TRUE(join_match_eq(&matches[0], "k", 1601u, 1200u, 1601u));
    /* Beyond the gap on both buffered lefts: no match. */
    ASSERT_EQ(re_stream_join_record(join, RE_STREAM_JOIN_RIGHT, text("k"), 3000u, &v), RE_STATUS_OK);
    ASSERT_EQ(re_stream_join_drain(join, matches, 8u, &count), RE_STATUS_OK);
    ASSERT_EQ(count, 0u);
    re_stream_join_destroy(join);
    re_engine_destroy(engine);
}

TEST(stream_join_left_outer_unmatched_once_after_watermark) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_join_strategy_t strategy = {RE_STREAM_JOIN_TIME_WINDOW, 10u, 0u, 0u};
    re_stream_join_t *join = make_join(engine, RE_STREAM_JOIN_LEFT_OUTER, strategy);
    re_stream_join_match_t matches[8];
    size_t count = 99u;
    re_value_t v = {RE_VALUE_INT64, {.int64_value = 1}};
    ASSERT_NOT_NULL(join);
    ASSERT_EQ(re_stream_join_record(join, RE_STREAM_JOIN_LEFT, text("k"), 1000u, &v), RE_STATUS_OK);
    /* No eager emission at record time (documented composition; upstream
     * emits eagerly, local defers to the watermark pass). */
    ASSERT_EQ(re_stream_join_drain(join, matches, 8u, &count), RE_STATUS_OK);
    ASSERT_EQ(count, 0u);
    /* Expiry is strict: watermark - ts > window (upstream :267). */
    ASSERT_EQ(re_stream_join_update_watermark(join, RE_STREAM_JOIN_LEFT, 1010u), RE_STATUS_OK);
    ASSERT_EQ(re_stream_join_drain(join, matches, 8u, &count), RE_STATUS_OK);
    ASSERT_EQ(count, 0u);
    /* The watermark pass emits the unmatched left exactly once
     * (upstream join_manager LeftOuter parity). */
    ASSERT_EQ(re_stream_join_update_watermark(join, RE_STREAM_JOIN_LEFT, 1011u), RE_STATUS_OK);
    ASSERT_EQ(re_stream_join_drain(join, matches, 8u, &count), RE_STATUS_OK);
    ASSERT_EQ(count, 1u);
    ASSERT_TRUE(join_match_eq(&matches[0], "k", 1000u, 0u, 1000u));
    ASSERT_EQ(re_stream_join_update_watermark(join, RE_STREAM_JOIN_LEFT, 5000u), RE_STATUS_OK);
    ASSERT_EQ(re_stream_join_drain(join, matches, 8u, &count), RE_STATUS_OK);
    ASSERT_EQ(count, 0u);
    /* A matched left is never emitted as unmatched. */
    ASSERT_EQ(re_stream_join_record(join, RE_STREAM_JOIN_LEFT, text("m"), 10000u, &v), RE_STATUS_OK);
    ASSERT_EQ(re_stream_join_record(join, RE_STREAM_JOIN_RIGHT, text("m"), 10005u, &v), RE_STATUS_OK);
    ASSERT_EQ(re_stream_join_drain(join, matches, 8u, &count), RE_STATUS_OK);
    ASSERT_EQ(count, 1u);
    ASSERT_EQ(re_stream_join_update_watermark(join, RE_STREAM_JOIN_LEFT, 20000u), RE_STATUS_OK);
    ASSERT_EQ(re_stream_join_drain(join, matches, 8u, &count), RE_STATUS_OK);
    ASSERT_EQ(count, 0u);
    re_stream_join_destroy(join);
    re_engine_destroy(engine);
}

TEST(stream_join_left_outer_session_window_unmatched_once) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_join_strategy_t strategy = {RE_STREAM_JOIN_SESSION_WINDOW, 0u, 0u, 500u};
    re_stream_join_t *join = make_join(engine, RE_STREAM_JOIN_LEFT_OUTER, strategy);
    re_stream_join_match_t matches[8];
    size_t count = 99u;
    re_value_t v = {RE_VALUE_INT64, {.int64_value = 1}};
    ASSERT_NOT_NULL(join);
    ASSERT_EQ(re_stream_join_record(join, RE_STREAM_JOIN_LEFT, text("k"), 1000u, &v), RE_STATUS_OK);
    /* SESSION_WINDOW expires on the gap (join_window_size -> gap_ms): the
     * same strict watermark - ts > gap boundary as the time-window pin. */
    ASSERT_EQ(re_stream_join_update_watermark(join, RE_STREAM_JOIN_LEFT, 1500u), RE_STATUS_OK);
    ASSERT_EQ(re_stream_join_drain(join, matches, 8u, &count), RE_STATUS_OK);
    ASSERT_EQ(count, 0u);
    /* The watermark pass emits the unmatched left exactly once... */
    ASSERT_EQ(re_stream_join_update_watermark(join, RE_STREAM_JOIN_LEFT, 1501u), RE_STATUS_OK);
    ASSERT_EQ(re_stream_join_drain(join, matches, 8u, &count), RE_STATUS_OK);
    ASSERT_EQ(count, 1u);
    ASSERT_TRUE(join_match_eq(&matches[0], "k", 1000u, 0u, 1000u));
    /* ...and evicts it: no re-emission on later updates. */
    ASSERT_EQ(re_stream_join_update_watermark(join, RE_STREAM_JOIN_LEFT, 9000u), RE_STATUS_OK);
    ASSERT_EQ(re_stream_join_drain(join, matches, 8u, &count), RE_STATUS_OK);
    ASSERT_EQ(count, 0u);
    re_stream_join_destroy(join);
    re_engine_destroy(engine);
}

TEST(stream_join_record_already_expired_buffers_then_emits_once) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_join_strategy_t strategy = {RE_STREAM_JOIN_TIME_WINDOW, 10u, 0u, 0u};
    re_stream_join_t *join = make_join(engine, RE_STREAM_JOIN_LEFT_OUTER, strategy);
    re_stream_join_match_t matches[8];
    size_t count = 99u;
    re_value_t v = {RE_VALUE_INT64, {.int64_value = 1}};
    ASSERT_NOT_NULL(join);
    ASSERT_EQ(re_stream_join_update_watermark(join, RE_STREAM_JOIN_LEFT, 1000u), RE_STATUS_OK);
    /* The record path has no watermark gate: an event already expired under
     * the current watermark (1000 - 900 > 10) is BUFFERED, not rejected, and
     * emits nothing at record time. */
    ASSERT_EQ(re_stream_join_record(join, RE_STREAM_JOIN_LEFT, text("late"), 900u, &v), RE_STATUS_OK);
    ASSERT_EQ(re_stream_join_drain(join, matches, 8u, &count), RE_STATUS_OK);
    ASSERT_EQ(count, 0u);
    /* A non-advancing update is an accepted no-op - no emission. */
    ASSERT_EQ(re_stream_join_update_watermark(join, RE_STREAM_JOIN_LEFT, 1000u), RE_STATUS_OK);
    ASSERT_EQ(re_stream_join_drain(join, matches, 8u, &count), RE_STATUS_OK);
    ASSERT_EQ(count, 0u);
    /* The next ADVANCING update emits the buffered straggler exactly once... */
    ASSERT_EQ(re_stream_join_update_watermark(join, RE_STREAM_JOIN_LEFT, 1001u), RE_STATUS_OK);
    ASSERT_EQ(re_stream_join_drain(join, matches, 8u, &count), RE_STATUS_OK);
    ASSERT_EQ(count, 1u);
    ASSERT_TRUE(join_match_eq(&matches[0], "late", 900u, 0u, 900u));
    /* ...and evicts it: no re-emission afterwards. */
    ASSERT_EQ(re_stream_join_update_watermark(join, RE_STREAM_JOIN_LEFT, 2000u), RE_STATUS_OK);
    ASSERT_EQ(re_stream_join_drain(join, matches, 8u, &count), RE_STATUS_OK);
    ASSERT_EQ(count, 0u);
    re_stream_join_destroy(join);
    re_engine_destroy(engine);
}

TEST(stream_join_right_outer_and_full_outer_unmatched) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_join_strategy_t strategy = {RE_STREAM_JOIN_TIME_WINDOW, 10u, 0u, 0u};
    re_stream_join_t *right = make_join(engine, RE_STREAM_JOIN_RIGHT_OUTER, strategy);
    re_stream_join_t *full = make_join(engine, RE_STREAM_JOIN_FULL_OUTER, strategy);
    re_stream_join_t *inner = make_join(engine, RE_STREAM_JOIN_INNER, strategy);
    re_stream_join_match_t matches[8];
    size_t count = 99u;
    re_value_t v = {RE_VALUE_INT64, {.int64_value = 1}};
    ASSERT_NOT_NULL(right);
    ASSERT_NOT_NULL(full);
    ASSERT_NOT_NULL(inner);
    ASSERT_EQ(re_stream_join_record(right, RE_STREAM_JOIN_RIGHT, text("k"), 1000u, &v), RE_STATUS_OK);
    ASSERT_EQ(re_stream_join_update_watermark(right, RE_STREAM_JOIN_RIGHT, 2000u), RE_STATUS_OK);
    ASSERT_EQ(re_stream_join_drain(right, matches, 8u, &count), RE_STATUS_OK);
    ASSERT_EQ(count, 1u);
    ASSERT_TRUE(join_match_eq(&matches[0], "k", 0u, 1000u, 1000u));
    ASSERT_EQ(re_stream_join_update_watermark(right, RE_STREAM_JOIN_RIGHT, 3000u), RE_STATUS_OK);
    ASSERT_EQ(re_stream_join_drain(right, matches, 8u, &count), RE_STATUS_OK);
    ASSERT_EQ(count, 0u);
    /* Full outer emits both unmatched sides, left first. */
    ASSERT_EQ(re_stream_join_record(full, RE_STREAM_JOIN_LEFT, text("a"), 1000u, &v), RE_STATUS_OK);
    ASSERT_EQ(re_stream_join_record(full, RE_STREAM_JOIN_RIGHT, text("b"), 2000u, &v), RE_STATUS_OK);
    ASSERT_EQ(re_stream_join_update_watermark(full, RE_STREAM_JOIN_LEFT, 5000u), RE_STATUS_OK);
    ASSERT_EQ(re_stream_join_drain(full, matches, 8u, &count), RE_STATUS_OK);
    ASSERT_EQ(count, 2u);
    ASSERT_TRUE(join_match_eq(&matches[0], "a", 1000u, 0u, 1000u));
    ASSERT_TRUE(join_match_eq(&matches[1], "b", 0u, 2000u, 2000u));
    /* A matched pair suppresses both unmatched emissions. */
    ASSERT_EQ(re_stream_join_record(full, RE_STREAM_JOIN_LEFT, text("c"), 10000u, &v), RE_STATUS_OK);
    ASSERT_EQ(re_stream_join_record(full, RE_STREAM_JOIN_RIGHT, text("c"), 10005u, &v), RE_STATUS_OK);
    ASSERT_EQ(re_stream_join_drain(full, matches, 8u, &count), RE_STATUS_OK);
    ASSERT_EQ(count, 1u);
    ASSERT_EQ(re_stream_join_update_watermark(full, RE_STREAM_JOIN_RIGHT, 50000u), RE_STATUS_OK);
    ASSERT_EQ(re_stream_join_drain(full, matches, 8u, &count), RE_STATUS_OK);
    ASSERT_EQ(count, 0u);
    /* Inner never emits unmatched events at the watermark. */
    ASSERT_EQ(re_stream_join_record(inner, RE_STREAM_JOIN_LEFT, text("k"), 1000u, &v), RE_STATUS_OK);
    ASSERT_EQ(re_stream_join_update_watermark(inner, RE_STREAM_JOIN_LEFT, 5000u), RE_STATUS_OK);
    ASSERT_EQ(re_stream_join_drain(inner, matches, 8u, &count), RE_STATUS_OK);
    ASSERT_EQ(count, 0u);
    re_stream_join_destroy(right);
    re_stream_join_destroy(full);
    re_stream_join_destroy(inner);
    re_engine_destroy(engine);
}

TEST(stream_join_drain_capacity_limit) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_join_strategy_t strategy = {RE_STREAM_JOIN_TIME_WINDOW, 100u, 0u, 0u};
    re_stream_join_t *join = make_join(engine, RE_STREAM_JOIN_INNER, strategy);
    re_stream_join_match_t matches[8];
    size_t count = 0u;
    re_value_t v = {RE_VALUE_INT64, {.int64_value = 1}};
    ASSERT_NOT_NULL(join);
    ASSERT_EQ(re_stream_join_record(join, RE_STREAM_JOIN_LEFT, text("k"), 1000u, &v), RE_STATUS_OK);
    ASSERT_EQ(re_stream_join_record(join, RE_STREAM_JOIN_LEFT, text("k"), 1001u, &v), RE_STATUS_OK);
    ASSERT_EQ(re_stream_join_record(join, RE_STREAM_JOIN_RIGHT, text("k"), 1000u, &v), RE_STATUS_OK);
    /* Two queued matches, capacity 1: LIMIT + total, the first one drains
     * (the codebase's buffer-capacity idiom, re_rule_template_instantiate). */
    ASSERT_EQ(re_stream_join_drain(join, matches, 1u, &count), RE_STATUS_LIMIT);
    ASSERT_EQ(count, 2u);
    ASSERT_TRUE(join_match_eq(&matches[0], "k", 1000u, 1000u, 1000u));
    /* capacity 0 with a NULL array is the sizing query. */
    ASSERT_EQ(re_stream_join_drain(join, NULL, 0u, &count), RE_STATUS_LIMIT);
    ASSERT_EQ(count, 1u);
    ASSERT_EQ(re_stream_join_drain(join, matches, 8u, &count), RE_STATUS_OK);
    ASSERT_EQ(count, 1u);
    ASSERT_TRUE(join_match_eq(&matches[0], "k", 1001u, 1000u, 1001u));
    ASSERT_EQ(re_stream_join_drain(join, matches, 8u, &count), RE_STATUS_OK);
    ASSERT_EQ(count, 0u);
    ASSERT_EQ(re_stream_join_drain(join, matches, 8u, NULL), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_stream_join_drain(join, NULL, 1u, &count), RE_STATUS_INVALID_ARGUMENT);
    re_stream_join_destroy(join);
    re_engine_destroy(engine);
}

TEST(stream_join_buffer_overflow_drops_oldest) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_join_strategy_t strategy = {RE_STREAM_JOIN_TIME_WINDOW, 1000000u, 0u, 0u};
    re_stream_join_t *join = make_join(engine, RE_STREAM_JOIN_INNER, strategy);
    re_stream_join_t *keys = make_join(engine, RE_STREAM_JOIN_INNER, strategy);
    re_stream_join_match_t matches[256];
    size_t count = 0u;
    uint64_t index;
    char key_name[16];
    re_value_t v = {RE_VALUE_INT64, {.int64_value = 1}};
    ASSERT_NOT_NULL(join);
    ASSERT_NOT_NULL(keys);
    /* 65 events under one key overflow the 64-event per-key cap: the oldest
     * (timestamp 1) is dropped and counted. */
    for (index = 1u; index <= 65u; ++index)
        ASSERT_EQ(re_stream_join_record(join, RE_STREAM_JOIN_LEFT, text("k"), index, &v),
                  RE_STATUS_OK);
    ASSERT_EQ(re_stream_join_dropped(join), 1u);
    ASSERT_EQ(re_stream_join_record(join, RE_STREAM_JOIN_RIGHT, text("k"), 2u, &v), RE_STATUS_OK);
    ASSERT_EQ(re_stream_join_drain(join, matches, 256u, &count), RE_STATUS_OK);
    ASSERT_EQ(count, 64u);
    ASSERT_TRUE(join_match_eq(&matches[0], "k", 2u, 2u, 2u));
    ASSERT_TRUE(join_match_eq(&matches[63], "k", 65u, 2u, 65u));
    /* The queued-match cap is 256 with the same drop-oldest + counter rule:
     * four rights fill it exactly, the fifth drops 64 oldest. */
    ASSERT_EQ(re_stream_join_record(join, RE_STREAM_JOIN_RIGHT, text("k"), 3u, &v), RE_STATUS_OK);
    ASSERT_EQ(re_stream_join_record(join, RE_STREAM_JOIN_RIGHT, text("k"), 4u, &v), RE_STATUS_OK);
    ASSERT_EQ(re_stream_join_record(join, RE_STREAM_JOIN_RIGHT, text("k"), 5u, &v), RE_STATUS_OK);
    ASSERT_EQ(re_stream_join_record(join, RE_STREAM_JOIN_RIGHT, text("k"), 6u, &v), RE_STATUS_OK);
    ASSERT_EQ(re_stream_join_dropped(join), 1u);
    ASSERT_EQ(re_stream_join_record(join, RE_STREAM_JOIN_RIGHT, text("k"), 7u, &v), RE_STATUS_OK);
    ASSERT_EQ(re_stream_join_dropped(join), 65u);
    ASSERT_EQ(re_stream_join_drain(join, matches, 256u, &count), RE_STATUS_OK);
    ASSERT_EQ(count, 256u);
    /* 256 distinct keys per side are accepted; a 257th is RE_STATUS_LIMIT. */
    for (index = 0u; index < 256u; ++index) {
        snprintf(key_name, sizeof(key_name), "k%u", (unsigned)index);
        ASSERT_EQ(re_stream_join_record(keys, RE_STREAM_JOIN_LEFT, text(key_name), 1u, &v),
                  RE_STATUS_OK);
    }
    ASSERT_EQ(re_stream_join_record(keys, RE_STREAM_JOIN_LEFT, text("overflow"), 1u, &v),
              RE_STATUS_LIMIT);
    ASSERT_EQ(re_stream_join_record(keys, RE_STREAM_JOIN_LEFT, text("k0"), 2u, &v), RE_STATUS_OK);
    re_stream_join_destroy(join);
    re_stream_join_destroy(keys);
    re_engine_destroy(engine);
}

TEST(stream_join_validation) {
    re_engine_t *engine = re_engine_create(NULL, NULL);
    re_stream_join_strategy_t strategy = {RE_STREAM_JOIN_TIME_WINDOW, 10u, 0u, 0u};
    re_stream_join_strategy_t bad_strategy = {0u, 10u, 0u, 0u};
    re_stream_join_t *join = NULL;
    size_t count = 0u;
    re_value_t v = {RE_VALUE_INT64, {.int64_value = 1}};
    ASSERT_NOT_NULL(engine);
    ASSERT_EQ(re_stream_join_create(NULL, text("L"), text("R"), RE_STREAM_JOIN_INNER,
        strategy, &join), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_stream_join_create(engine, text("L"), text("R"), RE_STREAM_JOIN_INNER,
        strategy, NULL), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_stream_join_create(engine, (re_string_t){NULL, 0u}, text("R"),
        RE_STREAM_JOIN_INNER, strategy, &join), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_stream_join_create(engine, text(""), text("R"),
        RE_STREAM_JOIN_INNER, strategy, &join), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_stream_join_create(engine, text("L"), text("R"), (re_stream_join_type_t)0,
        strategy, &join), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_stream_join_create(engine, text("L"), text("R"), (re_stream_join_type_t)5,
        strategy, &join), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_stream_join_create(engine, text("L"), text("R"), RE_STREAM_JOIN_INNER,
        bad_strategy, &join), RE_STATUS_INVALID_ARGUMENT);
    bad_strategy.kind = 4u;
    ASSERT_EQ(re_stream_join_create(engine, text("L"), text("R"), RE_STREAM_JOIN_INNER,
        bad_strategy, &join), RE_STATUS_INVALID_ARGUMENT);
    /* The active strategy field must be non-zero per kind. */
    bad_strategy.kind = RE_STREAM_JOIN_TIME_WINDOW; bad_strategy.duration_ms = 0u;
    ASSERT_EQ(re_stream_join_create(engine, text("L"), text("R"), RE_STREAM_JOIN_INNER,
        bad_strategy, &join), RE_STATUS_INVALID_ARGUMENT);
    bad_strategy.kind = RE_STREAM_JOIN_COUNT_WINDOW; bad_strategy.count = 0u;
    ASSERT_EQ(re_stream_join_create(engine, text("L"), text("R"), RE_STREAM_JOIN_INNER,
        bad_strategy, &join), RE_STATUS_INVALID_ARGUMENT);
    bad_strategy.kind = RE_STREAM_JOIN_SESSION_WINDOW; bad_strategy.gap_ms = 0u;
    ASSERT_EQ(re_stream_join_create(engine, text("L"), text("R"), RE_STREAM_JOIN_INNER,
        bad_strategy, &join), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_stream_join_create(engine, text("L"), text("R"), RE_STREAM_JOIN_INNER,
        strategy, &join), RE_STATUS_OK);
    ASSERT_NOT_NULL(join);
    ASSERT_EQ(re_stream_join_record(NULL, RE_STREAM_JOIN_LEFT, text("k"), 1u, &v),
              RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_stream_join_record(join, (re_stream_join_side_t)0, text("k"), 1u, &v), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_stream_join_record(join, (re_stream_join_side_t)3, text("k"), 1u, &v), RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_stream_join_record(join, RE_STREAM_JOIN_LEFT, (re_string_t){NULL, 0u}, 1u, &v),
              RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_stream_join_record(join, RE_STREAM_JOIN_LEFT, text(""), 1u, &v),
              RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_stream_join_record(join, RE_STREAM_JOIN_LEFT, text("k"), 1u, NULL),
              RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_stream_join_update_watermark(NULL, RE_STREAM_JOIN_LEFT, 1u),
              RE_STATUS_INVALID_ARGUMENT);
    ASSERT_EQ(re_stream_join_update_watermark(join, (re_stream_join_side_t)0, 1u), RE_STATUS_INVALID_ARGUMENT);
    /* A non-advancing watermark update is an accepted no-op. */
    ASSERT_EQ(re_stream_join_update_watermark(join, RE_STREAM_JOIN_LEFT, 100u), RE_STATUS_OK);
    ASSERT_EQ(re_stream_join_update_watermark(join, RE_STREAM_JOIN_RIGHT, 50u), RE_STATUS_OK);
    ASSERT_EQ(re_stream_join_drain(join, NULL, 0u, &count), RE_STATUS_OK);
    ASSERT_EQ(count, 0u);
    ASSERT_EQ(re_stream_join_dropped(NULL), 0u);
    re_stream_join_destroy(join);
    re_stream_join_destroy(NULL); /* NULL destroy is an accepted no-op. */
    re_engine_destroy(engine);
}

TEST_MAIN_BEGIN()
    RUN_TEST(stream_min_max_over_filtered_events);
    RUN_TEST(stream_first_last_by_timestamp);
    RUN_TEST(stream_new_kinds_empty_window_not_found);
    RUN_TEST(stream_aggregate_result_struct_size_compat);
    RUN_TEST(stream_first_last_equal_timestamps_insertion_order);
    RUN_TEST(stream_min_max_reject_non_numeric_event);
    RUN_TEST(stream_stddev_population_known_values);
    RUN_TEST(stream_stddev_single_value_not_found);
    RUN_TEST(stream_percentile_nearest_rank);
    RUN_TEST(stream_percentile_parameter_validation);
    RUN_TEST(stream_count_distinct_typed_values);
    RUN_TEST(stream_c1_kinds_empty_window_not_found);
    RUN_TEST(stream_c1_numeric_kinds_reject_non_numeric);
    RUN_TEST(stream_c1_result_struct_size_compat);
    RUN_TEST(redis_kind_disabled_without_native_client);
    RUN_TEST(redis_roundtrip_when_service_available);
    RUN_TEST(run_reentry_conflicting_mutation_returns_busy);
    RUN_TEST(notify_reentry_mutation_returns_busy_read_allowed);
    RUN_TEST(window_snapshot_restore_into_self_no_aliasing);
    RUN_TEST(provider_callback_reentry_safe_by_construction);
    RUN_TEST(stream_analytics_cache_hit_miss_ttl_identity);
    RUN_TEST(stream_analytics_cache_evict_all_on_miss);
    RUN_TEST(stream_analytics_moving_average_global_not_of_averages);
    RUN_TEST(stream_analytics_detect_anomalies_window_and_history_minimums);
    RUN_TEST(stream_analytics_detect_anomalies_flags_exact_outliers);
    RUN_TEST(stream_analytics_detect_anomalies_zero_stddev_flags_nothing);
    RUN_TEST(stream_analytics_trend_direction_boundaries);
    RUN_TEST(stream_analytics_trend_odd_count_split_second_half_takes_extra);
    RUN_TEST(stream_analytics_trend_first_avg_zero_guard);
    RUN_TEST(stream_closure_flag_off_preserves_tumbling_behavior);
    RUN_TEST(stream_closure_flag_off_preserves_session_behavior);
    RUN_TEST(stream_closure_tumbling_closes_at_boundary_plus_lateness);
    RUN_TEST(stream_closure_tumbling_accept_closed_not_retained_rejected);
    RUN_TEST(stream_closure_tumbling_error_policy_reports_error);
    RUN_TEST(stream_closure_session_drop_boundary);
    RUN_TEST(stream_closure_session_accept_records_closed_retained);
    RUN_TEST(stream_closure_sliding_flag_inert);
    RUN_TEST(stream_window_options_pre_c4_struct_size_defaults_off);
    RUN_TEST(stream_join_inner_time_window);
    RUN_TEST(stream_join_count_window_pairing_and_cap);
    RUN_TEST(stream_join_session_gap);
    RUN_TEST(stream_join_left_outer_unmatched_once_after_watermark);
    RUN_TEST(stream_join_left_outer_session_window_unmatched_once);
    RUN_TEST(stream_join_record_already_expired_buffers_then_emits_once);
    RUN_TEST(stream_join_right_outer_and_full_outer_unmatched);
    RUN_TEST(stream_join_drain_capacity_limit);
    RUN_TEST(stream_join_buffer_overflow_drops_oldest);
    RUN_TEST(stream_join_validation);
TEST_MAIN_END()
