/**
 * @file rule_engine.h
 * @brief Minimal C99 public ABI for the rule engine.
 *
 * This header defines the boundary for the next TDD phase only. It does not
 * promise a parser, streaming runtime, or any behavior
 * not covered by the conformance manifests and future tests.
 */
#ifndef BREAK_RULE_ENGINE_H
#define BREAK_RULE_ENGINE_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct re_engine_t re_engine_t;
typedef struct re_facts_t re_facts_t;
typedef struct re_program_t re_program_t;
typedef enum re_accumulator_kind_t {
  RE_ACCUM_COUNT = 1,
  RE_ACCUM_SUM = 2,
  RE_ACCUM_AVERAGE = 3,
  RE_ACCUM_MIN = 4,
  RE_ACCUM_MAX = 5,
  /* Appended in Task 12: query-time first/last selectors (append-only ABI). */
  RE_ACCUM_FIRST = 6,
  RE_ACCUM_LAST = 7
} re_accumulator_kind_t;

typedef enum re_status_t {
  RE_STATUS_OK = 0,
  RE_STATUS_ERROR = -1,
  RE_STATUS_OUT_OF_MEMORY = -2,
  RE_STATUS_INVALID_ARGUMENT = -3,
  RE_STATUS_NOT_FOUND = -4,
  RE_STATUS_NOT_SUPPORTED = -5,
  RE_STATUS_PARSE_ERROR = -6,
  RE_STATUS_LIMIT = -7,
  RE_STATUS_CANCELLED = -8,
  RE_STATUS_BUSY = -9
} re_status_t;

typedef enum re_query_result_t {
  RE_QUERY_PROVED = 1,
  RE_QUERY_DISPROVED = 2,
  RE_QUERY_UNKNOWN = 3,
  RE_QUERY_LIMIT = 4
} re_query_result_t;

typedef struct re_query_options_t {
  uint32_t struct_size;
  size_t max_depth;
  size_t max_solutions;
  /* Appended in Task 13 (append-only ABI): query search strategy, one of
   * RE_QUERY_STRATEGY_*. Readers must gate this field on
   * struct_size >= offsetof(re_query_options_t, disable_shared_proof_graph);
   * an absent field means RE_QUERY_STRATEGY_DEPTH_FIRST. */
  uint32_t strategy;
  /* Appended in Task 13, consumed in Task 14: per-query opt-out of the
   * shared proof graph. 0 or absent keeps sharing ON, 1 bypasses the
   * cache (no lookup, no store, no stats movement). Readers must gate
   * this field on struct_size >= sizeof(re_query_options_t). */
  uint32_t disable_shared_proof_graph;
} re_query_options_t;

/* Search strategies for re_query_options_t.strategy (Task 13).
 * DEPTH_FIRST is the default single-pass DFS. BREADTH_FIRST and ITERATIVE are
 * the same iterative-deepening wrapper (ITERATIVE is a documented alias): the
 * goal is re-proven with max_depth = 1, 2, 4, 8, ... doubling up to the
 * configured max_depth (default 64), and the first capped pass yielding at
 * least one solution supplies the result proofs. Backward queries execute no
 * actions, so re-probing is side-effect free. More than 32 doublings reports
 * RE_STATUS_LIMIT. Values outside [0, 2] are RE_STATUS_INVALID_ARGUMENT. */
enum {
  RE_QUERY_STRATEGY_DEPTH_FIRST = 0u,
  RE_QUERY_STRATEGY_BREADTH_FIRST = 1u,
  RE_QUERY_STRATEGY_ITERATIVE = 2u
};

typedef enum re_value_type_t {
  RE_VALUE_NONE = 0,
  RE_VALUE_BOOL,
  RE_VALUE_INT64,
  RE_VALUE_DOUBLE,
  RE_VALUE_STRING,
  RE_VALUE_NULL,
  RE_VALUE_UNKNOWN
} re_value_type_t;

typedef uint32_t re_capabilities_t;

#define RE_CAP_CORE_GRL           ((re_capabilities_t)1u << 0)
#define RE_CAP_FACTS              ((re_capabilities_t)1u << 1)
#define RE_CAP_FORWARD_EXECUTION  ((re_capabilities_t)1u << 2)

/* Extension identifiers and capability bits are append-only. */
typedef uint32_t re_extension_id_t;
typedef uint64_t re_capabilities_v2_t;

enum {
  RE_EXTENSION_CUSTOM_FUNCTIONS = 1u,
  RE_EXTENSION_STRUCTURED_VALUES = 2u,
  RE_EXTENSION_FACT_LIFECYCLE = 3u,
  RE_EXTENSION_AGENDA_RETE = 4u,
  RE_EXTENSION_BACKWARD_PROOFS = 5u,
  RE_EXTENSION_STREAMING_WINDOWS = 6u,
  RE_EXTENSION_STATE_PROVIDER = 7u,
  RE_EXTENSION_CONCURRENCY = 8u
};

#define RE_CAP2_CUSTOM_FUNCTIONS  ((re_capabilities_v2_t)1ull << 0)
#define RE_CAP2_STRUCTURED_VALUES ((re_capabilities_v2_t)1ull << 1)
#define RE_CAP2_FACT_LIFECYCLE    ((re_capabilities_v2_t)1ull << 2)
#define RE_CAP2_AGENDA_RETE       ((re_capabilities_v2_t)1ull << 3)
#define RE_CAP2_BACKWARD_PROOFS   ((re_capabilities_v2_t)1ull << 4)
#define RE_CAP2_STREAMING_WINDOWS ((re_capabilities_v2_t)1ull << 5)
#define RE_CAP2_STATE_PROVIDER    ((re_capabilities_v2_t)1ull << 6)
#define RE_CAP2_CONCURRENCY       ((re_capabilities_v2_t)1ull << 7)

#define RE_ABI_VERSION_MAJOR 1u
/* Bumped 3u -> 4u in sub-project C Task C1, the first API-adding task of the
 * streaming completion plan (the minor bumps once for sub-project C):
 * docs/superpowers/plans/2026-08-30-rule-engine-full-parity-c-streaming.md */
#define RE_ABI_VERSION_MINOR 4u

typedef struct re_extension_info_t {
  uint32_t struct_size;
  uint32_t abi_major;
  uint32_t abi_minor;
  uint32_t extension_id;
  uint32_t extension_version;
  uint32_t reserved;
  re_capabilities_v2_t capability_bit;
} re_extension_info_t;

typedef enum re_provider_error_t {
  RE_PROVIDER_ERROR_UNAVAILABLE = 1,
  RE_PROVIDER_ERROR_TIMEOUT = 2,
  RE_PROVIDER_ERROR_SERIALIZATION = 3,
  RE_PROVIDER_ERROR_CONFLICT = 4
} re_provider_error_t;

typedef struct re_string_t {
  const char *data;
  size_t size;
} re_string_t;

typedef struct re_provider_error_info_t {
  uint32_t struct_size;
  re_provider_error_t kind;
  re_string_t message;
} re_provider_error_info_t;

typedef struct re_value_t {
  re_value_type_t type;
  union re_value_payload_t {
    int boolean;
    int64_t int64_value;
    double double_value;
    re_string_t string;
  } as;
} re_value_t;

typedef struct re_query_binding_t {
  re_string_t name;
  re_value_t value;
} re_query_binding_t;

/* Proof graph records are append-only ABI values. Callers set struct_size
 * before each get operation so older consumers can remain source-compatible. */
typedef struct re_proof_node_t {
  uint32_t struct_size;
  re_string_t rule_name;
} re_proof_node_t;

typedef struct re_proof_edge_t {
  uint32_t struct_size;
  size_t parent_index;
  size_t child_index;
} re_proof_edge_t;


typedef void *(*re_alloc_fn_t)(void *context, size_t size);
typedef void *(*re_realloc_fn_t)(void *context, void *memory, size_t size);
typedef void (*re_free_fn_t)(void *context, void *memory);

typedef struct re_allocator_t {
  void *context;
  re_alloc_fn_t alloc;
  re_realloc_fn_t realloc;
  re_free_fn_t free;
} re_allocator_t;

typedef struct re_limits_t {
  size_t max_source_bytes;
  size_t max_rules;
  size_t max_facts;
  size_t max_agenda_activations;
  size_t max_firings;
  /* Caps total agenda entries (pending + fired refraction keys) tracked; with
   * a persistent agenda (re_engine_set_agenda_persistent) the count is
   * cumulative across runs rather than per run. 0 selects the default of
   * 1024. Appended in Task 7: this struct has
   * no struct_size field, so the append is source-compatible only - existing
   * positional initializers keep compiling and zero-init keeps prior
   * behavior; code compiled against the old layout must be recompiled. */
  size_t max_activations_tracked;
} re_limits_t;

typedef int (*re_cancel_fn_t)(void *context);

typedef struct re_run_options_t {
  const re_limits_t *limits;
  re_cancel_fn_t is_cancelled;
  void *cancel_context;
} re_run_options_t;

typedef struct re_rule_event_t {
  re_string_t rule_name;
  int32_t salience;
  uint64_t activation_sequence;
} re_rule_event_t;

typedef re_status_t (*re_action_fn_t)(re_engine_t *engine,
                                      re_facts_t *facts,
                                      const re_rule_event_t *event,
                                      void *context);

typedef struct re_callbacks_t {
  re_action_fn_t action;
  void *context;
} re_callbacks_t;

/* Future extension objects are opaque and never expose private node layouts. */
typedef struct re_function_t re_function_t;
typedef struct re_value_handle_t re_value_handle_t;
typedef struct re_fact_txn_t re_fact_txn_t;
typedef struct re_subscription_t re_subscription_t;
typedef struct re_agenda_t re_agenda_t;
typedef struct re_rete_network_t re_rete_network_t;
typedef struct re_query_t re_query_t;
typedef struct re_proof_t re_proof_t;
typedef struct re_stream_window_t re_stream_window_t;
typedef struct re_stream_analytics_t re_stream_analytics_t;
typedef struct re_stream_join_t re_stream_join_t;
typedef struct re_state_provider_t re_state_provider_t;
typedef struct re_executor_t re_executor_t;

/* Streaming/state extension ABI versions are independent of the core ABI. */
#define RE_STREAM_WINDOW_ABI_VERSION 1u
#define RE_STATE_PROVIDER_ABI_VERSION 1u

typedef uint64_t re_event_timestamp_ms_t;

typedef enum re_stream_window_kind_t {
  RE_STREAM_WINDOW_TUMBLING = 1,
  RE_STREAM_WINDOW_SLIDING = 2,
  RE_STREAM_WINDOW_SESSION = 3
} re_stream_window_kind_t;

typedef enum re_late_event_policy_t {
  RE_LATE_EVENT_DROP = 1,
  RE_LATE_EVENT_ACCEPT = 2,
  RE_LATE_EVENT_ERROR = 3
} re_late_event_policy_t;

typedef struct re_stream_window_options_t {
  uint32_t struct_size;
  uint32_t abi_version;
  re_stream_window_kind_t kind;
  re_late_event_policy_t late_event_policy;
  uint64_t retention_ms;
  size_t max_events;
  size_t max_bytes;
  uint64_t allowed_lateness_ms;
  /* Appended in sub-project C Task C4 (append-only ABI): when non-zero, the
   * window's own watermark closes tumbling buckets and sessions - a
   * documented local composition (upstream watermarks only gate recording,
   * never drive closure, f80a541 src/streaming/watermark.rs:340). A tumbling
   * bucket is CLOSED once watermark >= bucket_end + allowed_lateness_ms; a
   * record's session is CLOSED once watermark >= (record_ts + retention_ms)
   * + allowed_lateness_ms. Records targeting a closed bucket/session get the
   * late_event_policy treatment (DROP -> RE_STATUS_NOT_FOUND, ERROR ->
   * RE_STATUS_ERROR, ACCEPT -> recorded only when the target is still
   * retained, otherwise RE_STATUS_NOT_FOUND). Sliding windows have no
   * discrete buckets, so the flag changes nothing for them (record-gate
   * only). It is read only when struct_size covers it; callers passing the
   * pre-C4 size (offsetof(re_stream_window_options_t, watermark_drives_closure))
   * get the default 0, which is byte-identical to the pre-C4 behavior. */
  uint32_t watermark_drives_closure;
} re_stream_window_options_t;

typedef struct re_stream_filter_options_t {
  uint32_t struct_size;
  uint32_t abi_version;
  re_string_t event_type;
  re_string_t key;
  /* Appended in sub-project C Task C1 (append-only ABI): percentile on the
   * 0-100 scale. It is read only for RE_STREAM_AGGREGATE_PERCENTILE and only
   * when struct_size covers it; older callers keep passing the pre-C1 size
   * (offsetof(re_stream_filter_options_t, percentile)) and every other kind
   * keeps working. */
  double percentile;
} re_stream_filter_options_t;

typedef enum re_stream_aggregate_kind_t {
  RE_STREAM_AGGREGATE_COUNT = 1,
  RE_STREAM_AGGREGATE_SUM = 2,
  RE_STREAM_AGGREGATE_AVERAGE = 3,
  /* Appended in Task 16 (append-only ABI): MIN/MAX fold numeric event values;
   * FIRST/LAST select the earliest/latest retained event by timestamp. */
  RE_STREAM_AGGREGATE_MIN = 4,
  RE_STREAM_AGGREGATE_MAX = 5,
  RE_STREAM_AGGREGATE_FIRST = 6,
  RE_STREAM_AGGREGATE_LAST = 7,
  /* Appended in sub-project C Task C1 (append-only ABI), mirroring upstream
   * AggregationType CountDistinct/StdDev/Percentile (rust-rule-engine
   * v1.21.4 f80a541 src/streaming/aggregator.rs:12). */
  RE_STREAM_AGGREGATE_COUNT_DISTINCT = 8,
  RE_STREAM_AGGREGATE_STDDEV = 9,
  RE_STREAM_AGGREGATE_PERCENTILE = 10
} re_stream_aggregate_kind_t;

/* Callers set struct_size before each call so older consumers remain
 * source-compatible. Implementations must gate each appended field on
 * struct_size: fields before minimum require only the pre-Task-16 size
 * (offsetof(re_stream_aggregate_result_t, minimum)); minimum/maximum/first/last
 * are written only when struct_size covers them, and bytes beyond struct_size
 * are never touched. first/last copy the retained event value; STRING data is
 * borrowed from the window and stays valid until the next window mutation or
 * destroy (the same borrow re_facts_get documents). stddev/percentile were
 * appended in sub-project C Task C1 and follow the same gating. For
 * RE_STREAM_AGGREGATE_COUNT_DISTINCT the distinct-value count lands in
 * count. */
typedef struct re_stream_aggregate_result_t {
  uint32_t struct_size;
  uint64_t count;
  double sum;
  double average;
  /* Appended in Task 16 (append-only ABI). */
  double minimum;
  double maximum;
  re_value_t first;
  re_value_t last;
  /* Appended in sub-project C Task C1 (append-only ABI). */
  double stddev;
  double percentile;
} re_stream_aggregate_result_t;

typedef struct re_stream_correlation_options_t {
  uint32_t struct_size;
  uint32_t abi_version;
  re_string_t first_event_type;
  re_string_t second_event_type;
  re_string_t key;
  uint64_t timeout_ms;
} re_stream_correlation_options_t;

/* Appended in sub-project C Task C2 (append-only ABI), mirroring upstream
 * TrendDirection (rust-rule-engine v1.21.4 f80a541
 * src/streaming/aggregator.rs:430). */
typedef enum re_stream_trend_t {
  RE_STREAM_TREND_INCREASING = 1,
  RE_STREAM_TREND_DECREASING = 2,
  RE_STREAM_TREND_STABLE = 3
} re_stream_trend_t;

typedef void (*re_snapshot_release_fn_t)(void *context,
                                         const uint8_t *data,
                                         size_t size);

typedef struct re_snapshot_t {
  uint32_t struct_size;
  uint32_t format_version;
  const uint8_t *data;
  size_t size;
  re_snapshot_release_fn_t release;
  void *release_context;
} re_snapshot_t;

typedef enum re_state_provider_kind_t {
  RE_STATE_PROVIDER_CALLBACK = 1,
  /* Native Redis provider. Available only when the library was built with
   * RULE_ENGINE_ENABLE_REDIS=ON and hiredis was found (RE_HAS_HIREDIS);
   * otherwise re_engine_set_state_provider_v1 returns
   * RE_STATUS_NOT_SUPPORTED. The v1 options carry no connection field,
   * so the native adapter connects via the RE_REDIS_URL environment
   * variable (default redis://127.0.0.1:6379) with key prefix "re". */
  RE_STATE_PROVIDER_REDIS = 2
} re_state_provider_kind_t;

typedef struct re_state_provider_options_t {
  uint32_t struct_size;
  uint32_t abi_version;
  re_state_provider_kind_t kind;
  uint32_t flags;
  uint64_t operation_timeout_ms;
} re_state_provider_options_t;

typedef re_status_t (*re_function_call_fn_t)(re_engine_t *engine,
                                             re_facts_t *facts,
                                             const re_value_t *arguments,
                                             size_t argument_count,
                                             re_value_t *out_value,
                                             void *context);
typedef void (*re_function_release_fn_t)(void *context);

typedef struct re_fact_id_t {
  uint64_t slot;
  uint64_t generation;
} re_fact_id_t;

typedef struct re_fact_provenance_t {
  uint32_t struct_size;
  uint32_t flags;
  re_string_t producer_rule;
  size_t premise_count;
  const re_fact_id_t *premises;
} re_fact_provenance_t;

typedef enum re_fact_change_kind_t {
  RE_FACT_INSERT = 1,
  RE_FACT_UPDATE = 2,
  RE_FACT_RETRACT = 3
} re_fact_change_kind_t;

typedef struct re_fact_event_t {
  uint32_t struct_size;
  re_fact_change_kind_t kind;
  re_fact_id_t id;
  re_string_t name;
  re_value_t value;
} re_fact_event_t;

typedef struct re_function_descriptor_t {
  uint32_t struct_size;
  uint32_t abi_version;
  re_string_t name;
  re_function_call_fn_t call;
  re_function_release_fn_t release;
  void *context;
} re_function_descriptor_t;

typedef re_status_t (*re_fact_event_fn_t)(re_facts_t *facts,
                                          const re_fact_event_t *event,
                                          void *context);
typedef re_status_t (*re_state_get_fn_t)(re_state_provider_t *provider,
                                         re_string_t key,
                                         re_value_t *out_value,
                                         void *context);
typedef re_status_t (*re_state_set_fn_t)(re_state_provider_t *provider,
                                          re_string_t key,
                                          const re_value_t *value,
                                          void *context);
typedef re_status_t (*re_state_put_fn_t)(re_state_provider_t *provider,
                                          re_string_t key,
                                          const re_value_t *value,
                                          uint64_t ttl_ms, void *context);
typedef re_status_t (*re_state_delete_fn_t)(re_state_provider_t *provider,
                                             re_string_t key, void *context);
typedef re_status_t (*re_state_ttl_fn_t)(re_state_provider_t *provider,
                                          re_string_t key,
                                          uint64_t *out_ttl_ms, void *context);
typedef void (*re_state_release_fn_t)(void *context);

typedef struct re_state_provider_descriptor_t {
  uint32_t struct_size;
  uint32_t abi_version;
  re_state_get_fn_t get;
  re_state_set_fn_t set;
  re_state_release_fn_t release;
  void *context;
  re_state_put_fn_t put;
  re_state_delete_fn_t delete_key;
  re_state_ttl_fn_t ttl;
} re_state_provider_descriptor_t;

typedef uint64_t (*re_state_clock_fn_t)(void *context);
typedef struct re_memory_provider_options_t {
  uint32_t struct_size;
  uint32_t abi_version;
  size_t max_keys;
  size_t max_key_bytes;
  size_t max_value_bytes;
  re_state_clock_fn_t clock;
  void *clock_context;
} re_memory_provider_options_t;

typedef struct re_concurrency_options_t {
  uint32_t struct_size;
  uint32_t abi_version;
  uint32_t worker_count;
  uint32_t flags;
} re_concurrency_options_t;

/* Threading contract: engine, facts, windows and providers are
 * single-threaded handles - callers must externally synchronize every
 * operation on the same handle, and callbacks execute on the calling thread.
 * While re_engine_run is active the engine and facts handles are busy:
 * re-entering the run, opening a user transaction, or resetting working
 * memory returns RE_STATUS_BUSY. A firing and its action callback share one
 * fact transaction, so fact writes from the callback are staged and committed
 * with the firing rather than rejected. Allocator callbacks (alloc/realloc/
 * free) execute inside whichever operation triggered them and must not call
 * back into any rule-engine API on a handle involved in that in-flight
 * operation. The optional C11 executor evaluates read-only conditions in
 * private workers and merges matches back on the engine thread. */
/* The returned engine owns a copy of config and remains valid until destroy. */
re_engine_t *re_engine_create(const re_allocator_t *allocator,
                              const re_limits_t *limits);
/* Destroys engine and any program owned by it. NULL is accepted. */
void re_engine_destroy(re_engine_t *engine);
/* Returns locally implemented capabilities; zero is valid for NULL. */
re_capabilities_t re_engine_capabilities(const re_engine_t *engine);
/* Unsupported ABI versions return RE_STATUS_NOT_SUPPORTED. */
re_status_t re_engine_capabilities_v2(const re_engine_t *engine,
                                      uint32_t requested_abi_version,
                                      re_capabilities_v2_t *out_capabilities);
re_status_t re_engine_extension_info(const re_engine_t *engine,
                                     re_extension_id_t extension_id,
                                     uint32_t requested_version,
                                     re_extension_info_t *out_info);

/* Extension registration is transactional; descriptor memory is borrowed only
 * for the call, while context/release remain owned by the registered function. */
re_status_t re_engine_register_function(re_engine_t *engine,
                                        const re_function_descriptor_t *descriptor,
                                        re_function_t **out_function);
void re_function_unregister(re_function_t *function);

/* These declarations define ownership seams only; no extension is implied by
 * their presence. Redis remains RE_STATUS_NOT_SUPPORTED unless the build
 * explicitly enables a detected native client adapter. */
re_status_t re_value_create_struct(re_facts_t *facts, re_value_handle_t **out_value);
re_status_t re_value_create_object(re_facts_t *facts, re_value_handle_t **out_value);
re_status_t re_value_create_array(re_facts_t *facts, re_value_handle_t **out_value);
re_status_t re_value_object_set(re_value_handle_t *object, re_string_t key,
                                const re_value_t *value);
re_status_t re_value_object_set_value(re_value_handle_t *object, re_string_t key,
                                      const re_value_handle_t *value);
re_status_t re_value_array_append(re_value_handle_t *array, const re_value_t *value);
re_status_t re_value_array_append_value(re_value_handle_t *array,
                                        const re_value_handle_t *value);
re_status_t re_facts_set_value(re_facts_t *facts, re_string_t name,
                               const re_value_handle_t *value);
re_status_t re_facts_get_path(const re_facts_t *facts, re_string_t path,
                              re_value_t *out_value);
re_status_t re_facts_set_path(re_facts_t *facts, re_string_t path,
                              const re_value_t *value);
void re_value_destroy(re_value_handle_t *value);
re_status_t re_facts_begin(re_facts_t *facts, re_fact_txn_t **out_transaction);
re_status_t re_facts_commit(re_fact_txn_t *transaction);
void re_facts_rollback(re_fact_txn_t *transaction);
re_status_t re_facts_txn_set(re_fact_txn_t *transaction, re_string_t name,
                             const re_value_t *value);
re_status_t re_facts_txn_insert(re_fact_txn_t *transaction, re_string_t name,
                                const re_value_t *value, re_fact_id_t *out_id);
re_status_t re_facts_txn_update(re_fact_txn_t *transaction, re_fact_id_t id,
                                const re_value_t *value);
re_status_t re_facts_txn_retract(re_fact_txn_t *transaction, re_fact_id_t id);
re_status_t re_facts_txn_get(const re_fact_txn_t *transaction, re_string_t name,
                             re_value_t *out_value);
/* re_facts_insert is the explicit-assertion API (upstream engine.insert).
 * Asserting over a logically-derived fact keeps its logical justifications
 * AND records explicit support: the fact then survives premise retraction
 * (upstream tms.rs keeps both justification lists; explicit support is
 * unconditionally valid). re_facts_set/re_facts_update are plain value
 * writes and never change TMS support. */
re_status_t re_facts_insert(re_facts_t *facts, re_string_t name,
                            const re_value_t *value, re_fact_id_t *out_id);
re_status_t re_facts_update(re_facts_t *facts, re_fact_id_t id,
                            const re_value_t *value);
re_status_t re_facts_retract(re_facts_t *facts, re_fact_id_t id);
/* Deriving a fact the host already asserted explicitly keeps both supports:
 * the logical justification is recorded alongside the explicit one (the fact
 * becomes logical as well), so retracting a premise later leaves the fact
 * alive. Deriving a fresh or already-logical fact adds a justification; the
 * fact is auto-retracted when its last logical justification disappears and
 * no explicit support was ever recorded. */
re_status_t re_facts_insert_logical(re_facts_t *facts, re_string_t name,
                                    const re_value_t *value,
                                    re_string_t producer_rule,
                                    const re_fact_id_t *premises,
                                    size_t premise_count, re_fact_id_t *out_id);
int re_facts_is_logical(const re_facts_t *facts, re_fact_id_t id);
re_status_t re_facts_provenance_get(const re_facts_t *facts, re_fact_id_t id,
                                    re_fact_provenance_t *out_provenance);
/* Counts logical (rule-produced) justifications only; explicit support
 * recorded via re_facts_insert is unconditionally valid and not counted. */
size_t re_facts_justification_count(const re_facts_t *facts, re_fact_id_t id);
re_status_t re_facts_justification_add(re_facts_t *facts, re_fact_id_t derived,
                                       re_string_t producer_rule,
                                       const re_fact_id_t *premises,
                                       size_t premise_count);
re_status_t re_facts_justification_remove(re_facts_t *facts, re_fact_id_t derived,
                                          re_string_t producer_rule,
                                          const re_fact_id_t *premises,
                                          size_t premise_count);
re_status_t re_facts_subscribe(re_facts_t *facts, re_fact_event_fn_t callback,
                               void *context,
                               re_subscription_t **out_subscription);
void re_subscription_destroy(re_subscription_t *subscription);
/* Returns the engine-owned agenda, creating it on first use. The instance is
 * released by re_engine_destroy; re_agenda_destroy is a documented no-op for
 * engine-owned instances. */
re_status_t re_engine_agenda(re_engine_t *engine, re_agenda_t **out_agenda);
void re_agenda_destroy(re_agenda_t *agenda);
/* With persistence enabled, pending activations and the fired refraction
 * history survive re_engine_run, including RE_STATUS_LIMIT and
 * RE_STATUS_CANCELLED exits; the default non-persistent mode fully resets the
 * agenda on every run exit. RE_STATUS_BUSY while the engine is running. */
re_status_t re_engine_set_agenda_persistent(re_engine_t *engine, int enabled);
/* Public snapshot of one pending agenda activation. rule_name is borrowed
 * from the engine's program and stays valid until the program is replaced or
 * the engine is destroyed. premises are the true fact ids (real generations,
 * condition order) the activation was asserted with; the first premise_count
 * entries are valid. */
typedef struct re_agenda_entry_t {
  uint32_t struct_size;
  re_string_t rule_name;
  int32_t salience;
  uint64_t activation_sequence;
  size_t premise_count;
  re_fact_id_t premises[8];
} re_agenda_entry_t;
/* Number of pending (unfired) activations; NULL yields 0. */
size_t re_agenda_count(const re_agenda_t *agenda);
/* Reads the pending activation at index in pop order (salience descending,
 * then activation sequence ascending); RE_STATUS_NOT_FOUND past the end.
 * out_entry->struct_size must be at least sizeof(re_agenda_entry_t). */
re_status_t re_agenda_peek(const re_agenda_t *agenda, size_t index, re_agenda_entry_t *out_entry);
re_status_t re_engine_rete_network(const re_engine_t *engine,
                                    re_rete_network_t **out_network);
/* Destroys a caller-owned network; engine-owned networks are released by the engine. */
void re_rete_network_destroy(re_rete_network_t *network);
/* Backward query goal strings. Forms: a bare rule name or goal("Rule") for a
 * zero-argument rule goal; a direct comparison `Fact == literal` or
 * `Fact == Variable` (binds Variable to the fact value); a `NOT ` prefix
 * (negation as failure); and, since Task B3, `?var` unification and
 * argument-bearing goal calls:
 *
 * - `Fact == ?s` / `?s == Fact` / `?s == literal` bind `?s` per solution;
 *   bindings surface via re_proof_binding_get under the verbatim `?`-prefixed
 *   name (upstream unification.rs keeps the prefix). An absent fact is
 *   unresolvable and reports RE_QUERY_UNKNOWN like the literal path; `?x == ?y`
 *   with both sides unbound has no match and reports RE_QUERY_DISPROVED (no
 *   deferral, no occurs check - upstream parity).
 * - goal("Rule", a1, ..., an) invokes a parameterized rule with literal,
 *   fact-path, or `?var` actuals. A concrete-bound `?var` passes its value to
 *   the formal; an unbound `?var` leaves the formal unbound and claims the
 *   value the formal derives for that solution (sticky-consistent: a
 *   conflicting rebind fails the proof branch, never the engine). Equality
 *   over structured values is whole-value typed equality only - arrays never
 *   unify element-wise. */
re_status_t re_engine_query(re_engine_t *engine, re_facts_t *facts,
                             re_string_t goal, re_query_t **out_query);
re_status_t re_engine_query_bounded(re_engine_t *engine, re_facts_t *facts,
                                    re_string_t goal,
                                    const re_query_options_t *options,
                                    re_query_t **out_query);
re_status_t re_query_next(re_query_t *query, re_proof_t **out_proof);
re_query_result_t re_query_result(const re_query_t *query);
size_t re_query_solution_count(const re_query_t *query);
size_t re_proof_binding_count(const re_proof_t *proof);
re_status_t re_proof_binding_get(const re_proof_t *proof, size_t index,
                                 re_query_binding_t *out_binding);
size_t re_proof_trace_count(const re_proof_t *proof);
re_status_t re_proof_trace_get(const re_proof_t *proof, size_t index,
                                 re_string_t *out_rule_name);
size_t re_proof_node_count(const re_proof_t *proof);
re_status_t re_proof_node_get(const re_proof_t *proof, size_t index,
                              re_proof_node_t *out_node);
size_t re_proof_edge_count(const re_proof_t *proof);
re_status_t re_proof_edge_get(const re_proof_t *proof, size_t index,
                              re_proof_edge_t *out_edge);
void re_query_destroy(re_query_t *query);
void re_proof_destroy(re_proof_t *proof);
/* Runs pattern (an ordinary query goal string, e.g. "Score == S" or the B3
 * `?var` forms - "User.Score == ?s" or goal("Pick", ?s)) through an
 * internal bounded query - max_depth 64 (the re_engine_query default) and a
 * documented max_solutions cap of 1024 - and folds the binding named field
 * over the solutions in DFS order. field names a binding verbatim, so a
 * `?var` field keeps its prefix ("?s"). The internal query is destroyed before
 * returning, so invalidation/mutation semantics match a caller-run query and
 * no fact subscription survives. Reaching the 1024-solution cap reports
 * RE_STATUS_LIMIT (an exact fit cannot be told apart from a truncated set),
 * as does a depth-limited internal search.
 *
 * field.data == NULL is accepted for RE_ACCUM_COUNT only; COUNT counts every
 * solution and ignores field. Every other kind skips solutions whose proof
 * does not bind field, and reports RE_STATUS_NOT_FOUND when no solution binds
 * it. Empty solution set: COUNT yields int64 0 with RE_STATUS_OK, all other
 * kinds report RE_STATUS_NOT_FOUND.
 *
 * SUM/AVERAGE/MIN/MAX accept only INT64/DOUBLE bindings; any other type is
 * RE_STATUS_INVALID_ARGUMENT (the same rejection re_accumulator_evaluate
 * applies). Result typing: COUNT -> RE_VALUE_INT64; AVERAGE ->
 * RE_VALUE_DOUBLE; SUM/MIN/MAX -> RE_VALUE_INT64 when every folded value was
 * INT64, else RE_VALUE_DOUBLE - a deliberate divergence from
 * re_accumulator_evaluate's always-DOUBLE result. The INT64 fold accumulates
 * with unchecked addition, so extreme sums overflow (wrap) without a status.
 * FIRST/LAST copy the binding value of the first/last solution carrying
 * field; a STRING result reports RE_STATUS_NOT_SUPPORTED because proof string
 * storage is freed with the internal query. kind outside [1, 7] and NULL
 * engine/facts/out_value/pattern are RE_STATUS_INVALID_ARGUMENT. */
re_status_t re_engine_query_aggregate(re_engine_t *engine, re_facts_t *facts,
                                      re_accumulator_kind_t kind, re_string_t field,
                                      re_string_t pattern, re_value_t *out_value);
/* Shared proof graph counters (Task 14). The engine-owned graph caches
 * final backward-query results (PROVED/DISPROVED only; LIMIT/UNKNOWN are
 * never cached), keyed on the goal text, facts identity, normalized search
 * options, and the engine config, and stamped with the facts mutation
 * generation. Since Task B2 the generation check is only the fast path: a
 * serial mismatch re-validates the entry's recorded premise reads (presence
 * plus value fingerprint per fact the derivation observed), so mutating a
 * fact the derivation never read leaves the entry valid; only a premise
 * flip (or an opaque entry - a user function ran mid-proof) invalidates.
 * The graph is created lazily on the first shared query, holds at most 64
 * entries, and clears every entry when full. A NULL engine or NULL counter
 * is RE_STATUS_INVALID_ARGUMENT; an engine that has not cached yet reports
 * zeroes with RE_STATUS_OK. */
re_status_t re_engine_proof_graph_stats(const re_engine_t *engine,
                                        uint64_t *out_hits, uint64_t *out_misses);
/* Extended shared proof graph counters (Task B2), same graph as
 * re_engine_proof_graph_stats: invalidations counts entries unlinked by
 * per-premise re-validation, stores counts successful cache stores, and
 * evictions counts entries dropped by the clear-all flush when the 64-entry
 * table fills. Callers set struct_size to sizeof(re_proof_graph_stats_t);
 * a smaller value, a NULL engine, or a NULL output is
 * RE_STATUS_INVALID_ARGUMENT. An engine that has not cached yet reports
 * zeroes with RE_STATUS_OK. */
typedef struct re_proof_graph_stats_t {
  uint32_t struct_size;
  uint64_t hits;
  uint64_t misses;
  uint64_t invalidations;
  uint64_t stores;
  uint64_t evictions;
} re_proof_graph_stats_t;
re_status_t re_engine_proof_graph_stats_v2(const re_engine_t *engine,
                                           re_proof_graph_stats_t *out_stats);
/* GRL query blocks (Task A7, upstream rust-rule-engine v1.21.4 grl_query.rs):
 * runs the `query "Name" { ... }` blocks installed with the program. A query
 * block carries a required raw goal text plus optional strategy
 * (depth-first|breadth-first|iterative, default depth-first), max-depth
 * (default 10), max-solutions (default 1), enable-memoization (default true;
 * false maps to re_query_options_t.disable_shared_proof_graph),
 * enable-optimization (accepted and ignored - there are no local optimization
 * passes), a `when:` gate, and on-success/on-failure/on-missing action
 * blocks.
 *
 * Execution: a false `when:` condition (a normal rule-condition expression;
 * one referencing a missing fact counts as false) skips the query silently.
 * Otherwise the goal text is split textually - one wrapping paren pair
 * stripped, `||` split before `&&` when both appear - and each subgoal either
 * evaluates directly against working memory (subgoals containing `!=`) or
 * runs through re_engine_query_bounded with the block's strategy and limits.
 * A proved goal runs the on-success statements; any other outcome runs
 * on-failure. on-missing never fires: the backward machine does not track
 * upstream's missing_facts list, so missing-fact outcomes fold into
 * on-failure (documented divergence). Statements are flat scalar assignments
 * `Name = true|false|<number>|"string"` written with re_facts_set, or calls
 * LogMessage/Request/Print (stdout) and Debug (stderr); an unknown call name
 * warns on stderr without failing.
 *
 * Queries never run inside re_engine_run - only through these two functions.
 * Both report RE_STATUS_INVALID_ARGUMENT for NULL arguments or when no
 * program is installed; re_engine_run_query reports RE_STATUS_NOT_FOUND for
 * an unknown name; an installed program without query blocks makes
 * re_engine_run_queries an OK no-op. A successful dispatch reports
 * RE_STATUS_OK regardless of whether the goal proved. A HARD goal error
 * (anything re_engine_query_bounded propagates other than RE_STATUS_LIMIT,
 * e.g. RE_STATUS_NOT_SUPPORTED from the nested-quantifier backward boundary)
 * propagates to the caller WITHOUT running either action block - on-failure
 * dispatches only on a completed not-proved evaluation. When several blocks
 * share a name, re_engine_run_query runs the first match in source order. */
re_status_t re_engine_run_queries(re_engine_t *engine, re_facts_t *facts);
re_status_t re_engine_run_query(re_engine_t *engine, re_facts_t *facts,
                                re_string_t name);
re_status_t re_stream_window_create(re_engine_t *engine,
                                    re_stream_window_t **out_window);
re_status_t re_stream_window_record(re_stream_window_t *window,
                                    re_event_timestamp_ms_t timestamp_ms,
                                    re_string_t event_name,
                                     const re_value_t *value);
void re_stream_window_destroy(re_stream_window_t *window);
/* Versioned contract seam; implementations remain disabled until advertised. */
re_status_t re_stream_window_create_v1(
    re_engine_t *engine, const re_stream_window_options_t *options,
    re_stream_window_t **out_window);
re_status_t re_stream_window_record_v1(re_stream_window_t *window,
                                       re_event_timestamp_ms_t timestamp_ms,
                                       re_string_t event_name,
                                       const re_value_t *value);
re_status_t re_stream_window_snapshot(const re_stream_window_t *window,
                                      re_snapshot_t *out_snapshot);
re_status_t re_stream_window_restore(re_stream_window_t *window,
                                      const re_snapshot_t *snapshot);
/* Aggregates the retained events matching filter (empty event_type/key match
 * everything, the same filter count/sum already use). SUM/AVERAGE/MIN/MAX fold
 * numeric values only - a non-numeric matching event is
 * RE_STATUS_INVALID_ARGUMENT for all four; STDDEV/PERCENTILE (sub-project C
 * Task C1, upstream AggregationType f80a541 src/streaming/aggregator.rs:12)
 * fold the same numeric set with the same rejection. STDDEV is the population
 * standard deviation (variance = sum((v-mean)^2)/N, aggregator.rs:233) and
 * needs >= 2 matching values. PERCENTILE sorts ascending and picks
 * nearest-rank index round(p/100*(n-1)) (aggregator.rs:253); p comes from the
 * tail-appended filter percentile field (0-100, and a pre-C1 filter
 * struct_size cannot service the kind at all - both are
 * RE_STATUS_INVALID_ARGUMENT). COUNT_DISTINCT counts distinct typed values
 * over the matching set (same type tag and equal payload: int64 by value,
 * double bitwise, string by content, bool by value, null=null), accepts any
 * value type, and reports the distinct count in out_result->count; upstream
 * counts distinct debug-strings, which would equate 1 and 1.0 - a documented
 * divergence. FIRST/LAST copy the value of the earliest/latest matching event
 * by timestamp (insertion order breaks ties) and accept any value type. An
 * empty filtered set reports RE_STATUS_NOT_FOUND for every kind except COUNT,
 * which keeps its 0/OK behavior; STDDEV with a single matching value is
 * RE_STATUS_NOT_FOUND as well (upstream None).
 * RE_STATUS_NOT_FOUND returns before out_result is touched.
 * out_result->struct_size must cover at least the pre-Task-16 fields
 * (offsetof(re_stream_aggregate_result_t, minimum)); appended fields are
 * written only when struct_size covers them, and first/last fold over every
 * matching event regardless of kind. filter->struct_size must cover at least
 * the pre-C1 fields (offsetof(re_stream_filter_options_t, percentile)). */
re_status_t re_stream_window_aggregate_v1(
    const re_stream_window_t *window,
    const re_stream_filter_options_t *filter,
    re_stream_aggregate_kind_t kind,
    re_stream_aggregate_result_t *out_result);
re_status_t re_stream_window_correlate_v1(
    const re_stream_window_t *window,
    const re_stream_correlation_options_t *options,
    uint64_t *out_matches);

/* Stream analytics (sub-project C Task C2): the local analog of upstream
 * StreamAnalytics (rust-rule-engine v1.21.4 f80a541
 * src/streaming/aggregator.rs:285) - a TTL aggregation cache plus the
 * multi-window statistics. An analytics handle is single-threaded like every
 * other handle (the threading contract above) and holds no clock: the host
 * supplies current_time_ms to re_stream_analytics_aggregate_cached. Upstream
 * aggregates a "field" out of each event's data map; local events are a name
 * plus a typed scalar, so the local field mapping is the event name and the
 * folded value is the event's numeric scalar (INT64/DOUBLE) - a non-numeric
 * event carrying the name is skipped, the same tolerance upstream's
 * get_numeric filter_map applies. Every windows array is a caller-owned array
 * of borrowed window handles in chronological order (NULL handles are
 * RE_STATUS_INVALID_ARGUMENT); nothing takes ownership. */
re_status_t re_stream_analytics_create(re_engine_t *engine,
                                       uint64_t cache_ttl_ms,
                                       re_stream_analytics_t **out_analytics);
/* Releases the cache and every owned string. NULL is accepted. */
void re_stream_analytics_destroy(re_stream_analytics_t *analytics);
/* Cached aggregation (upstream aggregate_cached, f80a541
 * src/streaming/aggregator.rs:305). The cache entry identity is the caller
 * key string PLUS the aggregation identity (kind, the filter event_type, and
 * the filter percentile for RE_STREAM_AGGREGATE_PERCENTILE); upstream keys on
 * the string alone, so two aggregations sharing one key alias upstream but
 * miss here (documented hardening). A matching entry is a hit iff
 * current_time_ms - entry_ts < the cache TTL (:311), and a hit neither
 * refreshes the entry timestamp nor evicts anything. A current_time_ms behind
 * the entry timestamp is always a miss (upstream's wrapping subtraction never
 * hits on one either). On a miss the aggregation recomputes via
 * re_stream_window_aggregate_v1 over the caller-supplied window, then EVERY
 * entry past the TTL is evicted and the fresh entry inserted (upstream's
 * evict-all retain, :323 - it runs after the insert and so also drops the
 * fresh entry when the TTL is 0; the local order keeps the fresh entry so the
 * returned first/last borrow stays valid, which is unobservable because a
 * TTL-0 entry can never be a hit). Only successful aggregations are cached -
 * an error status (for example RE_STATUS_NOT_FOUND from an empty filtered
 * set) propagates with the cache untouched, where upstream caches its
 * AggregationResult::None (documented divergence). first/last STRING data is
 * deep-copied into the cache on insert and, on a hit, borrowed until the next
 * analytics mutation or destroy. filter and out_result are validated exactly
 * as re_stream_window_aggregate_v1 validates them (so a hit cannot sneak an
 * uncovered struct_size past the gate); analytics/window NULL or key.data
 * NULL is RE_STATUS_INVALID_ARGUMENT. */
re_status_t re_stream_analytics_aggregate_cached(
    re_stream_analytics_t *analytics, re_string_t key,
    const re_stream_window_t *window, const re_stream_filter_options_t *filter,
    re_stream_aggregate_kind_t kind, uint64_t current_time_ms,
    re_stream_aggregate_result_t *out_result);
/* Moving average over the trailing windows of the caller's array (upstream
 * moving_average, f80a541 src/streaming/aggregator.rs:329): only the last
 * last_n handles of windows[0..window_count) participate (all of them when
 * last_n >= window_count), and the result is the global
 * sum-of-values / event-count over every numeric event named event_name
 * across those windows - NOT an average of per-window averages. Upstream's
 * denominator is each window's total event count (TimeWindow::count counts
 * events without the field too); the local denominator counts only numeric
 * events named event_name, the documented name+scalar mapping.
 * window_count == 0, last_n == 0, or no matching numeric events report
 * RE_STATUS_NOT_FOUND (upstream None). event_name must be non-empty and
 * out_value non-NULL (RE_STATUS_INVALID_ARGUMENT). */
re_status_t re_stream_analytics_moving_average(
    const re_stream_analytics_t *analytics,
    const re_stream_window_t *const *windows, size_t window_count,
    re_string_t event_name, size_t last_n, double *out_value);
/* Z-score anomaly detection (upstream detect_anomalies, f80a541
 * src/streaming/aggregator.rs:357). window_count < 3 is
 * RE_STATUS_INVALID_ARGUMENT (upstream silently returns no anomalies - a
 * documented divergence). Historical values are the numeric events named
 * event_name in every window except the last; fewer than 10 is
 * RE_STATUS_NOT_FOUND (upstream: no anomalies). Mean and standard deviation
 * are population statistics over the historical values (variance divides by
 * N, the same formula RE_STREAM_AGGREGATE_STDDEV documents). Events in the
 * LAST window named event_name with fabs((value - mean) / stddev) > threshold
 * are flagged and their timestamps reported in window order - upstream
 * returns event IDs and local events have no IDs, so the timestamp is the
 * local identity (documented mapping; duplicate timestamps repeat). A zero
 * historical stddev flags nothing (documented guard: upstream divides by
 * zero, so a value equal to the mean gets a NaN z-score and passes while any
 * unequal value gets +/-inf and is flagged - local reports none). A NaN
 * threshold flags nothing (every comparison is false), as upstream. When the
 * flagged total exceeds capacity, out_timestamps receives the first capacity
 * timestamps, *out_count receives the TOTAL flagged count, and the return is
 * RE_STATUS_LIMIT (the codebase's buffer-capacity idiom,
 * re_rule_template_instantiate; an exact fit reports RE_STATUS_OK).
 * out_timestamps may be NULL only when capacity is 0 (a sizing query: it
 * reports RE_STATUS_LIMIT with the required capacity in *out_count whenever
 * any event is flagged, RE_STATUS_OK when none is). */
re_status_t re_stream_analytics_detect_anomalies(
    const re_stream_analytics_t *analytics,
    const re_stream_window_t *const *windows, size_t window_count,
    re_string_t event_name, double threshold,
    uint64_t *out_timestamps, size_t capacity, size_t *out_count);
/* Trend direction (upstream calculate_trend, f80a541
 * src/streaming/aggregator.rs:399). window_count < 2 is
 * RE_STATUS_INVALID_ARGUMENT (upstream returns Stable - a documented
 * divergence). Each window contributes the average of its numeric events
 * named event_name; windows with no such events contribute nothing
 * (upstream's filter_map), and fewer than 2 contributing windows reports
 * RE_STREAM_TREND_STABLE with RE_STATUS_OK (upstream Stable). The averages
 * split in half (the second half takes the odd extra) and
 * change_percent = (second_avg - first_avg) / first_avg * 100: > +5 is
 * RE_STREAM_TREND_INCREASING, < -5 is RE_STREAM_TREND_DECREASING, anything
 * else is RE_STREAM_TREND_STABLE (:416 - the +/-5 boundary itself is Stable).
 * first_avg == 0 reports STABLE (documented division guard: upstream's f64
 * division yields +inf/-inf - Increasing/Decreasing by the sign of
 * second_avg - or NaN - Stable - when both averages are 0). */
re_status_t re_stream_analytics_calculate_trend(
    const re_stream_analytics_t *analytics,
    const re_stream_window_t *const *windows, size_t window_count,
    re_string_t event_name, re_stream_trend_t *out_trend);

/* Cross-stream joins (sub-project C Task C4): the local analog of upstream
 * StreamJoinNode (rust-rule-engine v1.21.4 f80a541 src/rete/stream_join_node.rs)
 * - per-key event buffers for two named streams, strategy-bounded pair
 * matching, and watermark-driven outer-join completion. A join handle is
 * single-threaded like every other handle (the threading contract above) and
 * is NOT registered on the engine; upstream's StreamJoinManager routing by
 * event.metadata.source is replaced by the explicit side argument. Upstream
 * emits unmatched outer-join events eagerly at process time and re-scans
 * buffered pairs at update_watermark (:204); the local composition emits
 * matched pairs exactly once at record time and unmatched outer sides exactly
 * once when the watermark passes them (the observable outcome upstream's
 * join_manager tests pin), and never re-emits - documented composition. */

typedef enum re_stream_join_type_t {
  RE_STREAM_JOIN_INNER = 1,
  RE_STREAM_JOIN_LEFT_OUTER = 2,
  RE_STREAM_JOIN_RIGHT_OUTER = 3,
  RE_STREAM_JOIN_FULL_OUTER = 4
} re_stream_join_type_t;

typedef enum re_stream_join_side_t {
  RE_STREAM_JOIN_LEFT = 1,
  RE_STREAM_JOIN_RIGHT = 2
} re_stream_join_side_t;

typedef enum re_stream_join_strategy_kind_t {
  RE_STREAM_JOIN_TIME_WINDOW = 1,
  RE_STREAM_JOIN_COUNT_WINDOW = 2,
  RE_STREAM_JOIN_SESSION_WINDOW = 3
} re_stream_join_strategy_kind_t;

/* Flat tagged strategy mirroring upstream JoinStrategy (:24): kind selects
 * the active field (TIME_WINDOW -> duration_ms, COUNT_WINDOW -> count,
 * SESSION_WINDOW -> gap_ms); the inactive fields are ignored. The active
 * field must be non-zero (RE_STATUS_INVALID_ARGUMENT), mirroring the
 * retention_ms == 0 window validation. TIME_WINDOW and SESSION_WINDOW match a
 * left/right pair when |left_ts - right_ts| <= duration_ms / gap_ms
 * (upstream is_within_window :221 - upstream compares in whole seconds to
 * match its test conventions; local timestamps and parameters are uniformly
 * milliseconds). COUNT_WINDOW matches every same-key pair regardless of
 * distance (upstream returns true, :231) and bounds each per-key buffer to
 * the most recent min(count, 64) events (upstream buffers unboundedly and
 * never evicts for count windows - a documented divergence under the
 * codebase's bounded-everything rule). */
typedef struct re_stream_join_strategy_t {
  uint32_t kind; /* re_stream_join_strategy_kind_t */
  uint64_t duration_ms;
  uint64_t count;
  uint64_t gap_ms;
} re_stream_join_strategy_t;

/* One drained join result. key borrows the join's owned key storage and
 * stays valid until re_stream_join_destroy. A 0 left_timestamp_ms /
 * right_timestamp_ms marks the absent side of an outer-join emission (the
 * brief's absent-marker convention; a genuine event at timestamp 0 is
 * indistinguishable from absent, as documented). join_timestamp_ms is the
 * later of the two matched timestamps, or the single event's own timestamp
 * for an unmatched emission (upstream JoinedEvent join_timestamp, :35). */
typedef struct re_stream_join_match_t {
  re_string_t key;
  uint64_t left_timestamp_ms;
  uint64_t right_timestamp_ms;
  uint64_t join_timestamp_ms;
} re_stream_join_match_t;

/* Creates a join between two named streams; names must be non-empty and are
 * copied. join_type/strategy are validated as documented above. */
re_status_t re_stream_join_create(re_engine_t *engine,
                                  re_string_t left_name, re_string_t right_name,
                                  re_stream_join_type_t join_type,
                                  re_stream_join_strategy_t strategy,
                                  re_stream_join_t **out_join);
/* Releases the join, every buffered event, every queued match, and both
 * names. NULL is accepted. */
void re_stream_join_destroy(re_stream_join_t *join);
/* Buffers the event under key on side and emits one queued match per
 * strategy-satisfying same-key pair with the opposite side's buffered events
 * (any join type, upstream process_left/process_right :104/:140). key must be
 * non-empty (upstream silently skips keyless events, :108 - a documented
 * divergence; the local strictness mirrors the window record validation).
 * value must be non-NULL but is NOT retained: no join output surfaces event
 * payloads (the match struct carries timestamps only), so buffering them
 * would cost memory for nothing observable - documented. Buffers are
 * bounded: per side at most 256 distinct keys (a new key beyond that is
 * RE_STATUS_LIMIT and is not recorded) and per key at most 64 events
 * (COUNT_WINDOW: min(count, 64)); per-key overflow silently drops the OLDEST
 * event and bumps the re_stream_join_dropped counter (drop-oldest). The
 * queued-match list is likewise capped at 256 with drop-oldest + counter. */
re_status_t re_stream_join_record(re_stream_join_t *join,
                                  re_stream_join_side_t side,
                                  re_string_t key, uint64_t timestamp_ms,
                                  const re_value_t *value);
/* Advances the join watermark (upstream update_watermark, :204). Upstream's
 * node holds a single watermark fed from whichever stream's watermark
 * arrives; the local mapping keeps one watermark and validates but does not
 * partition by side. A non-advancing update is an accepted no-op
 * (RE_STATUS_OK), mirroring the window record path's watermark advance. An
 * advancing update emits, for each outer-join side of join_type, every
 * buffered event with watermark - ts > window_size that never matched
 * (window_size = duration_ms / gap_ms; the comparison is strict, upstream
 * :267), then evicts every expired event from both sides. Emitted events are
 * evicted, so an event is emitted as unmatched at most once across all
 * updates. COUNT_WINDOW never expires (upstream i64::MAX window, :259), so
 * count-window outer joins emit no unmatched events - documented upstream
 * parity. */
re_status_t re_stream_join_update_watermark(re_stream_join_t *join,
                                            re_stream_join_side_t side,
                                            uint64_t watermark_ms);
/* Drains queued matches oldest-first. *out_count always receives the TOTAL
 * number of queued matches before this call; the first min(capacity, total)
 * are copied out and removed. When the total exceeds capacity the return is
 * RE_STATUS_LIMIT (the codebase's buffer-capacity idiom,
 * re_rule_template_instantiate; an exact fit reports RE_STATUS_OK).
 * out_matches may be NULL only when capacity is 0 (a sizing query: it reports
 * RE_STATUS_LIMIT with the required capacity in *out_count whenever any match
 * is queued, RE_STATUS_OK when none is). */
re_status_t re_stream_join_drain(re_stream_join_t *join,
                                 re_stream_join_match_t *out_matches,
                                 size_t capacity, size_t *out_count);
/* Total silent drops since creation: per-key buffer overflow drop-oldest
 * plus queued-match overflow drop-oldest (both documented on
 * re_stream_join_record). Watermark evictions and drained matches are not
 * drops. */
uint64_t re_stream_join_dropped(const re_stream_join_t *join);

/* Stream rule evaluation (sub-project C Task C5): the local wiring of
 * upstream StreamRuleEngine (rust-rule-engine v1.21.4 f80a541
 * src/streaming/engine.rs) - a name-keyed stream registry on the engine plus
 * window-fact injection before an ordinary rule run.
 *
 * re_engine_stream_register binds a stream name to a BORROWED window handle
 * (upstream's WindowManager registry, engine.rs:183-262 - the local engine
 * stays single-threaded per the threading contract above, so the tokio
 * channel topology is not applicable). The name is copied; the window is
 * not owned: re_engine_destroy never destroys registered windows, and the
 * host must keep a registered window alive until it is unregistered or the
 * engine is destroyed. name must be non-empty. Re-registering an existing
 * name REPLACES the previous binding (documented choice over an error: the
 * host can swap a stream's window without an unregister round-trip). The
 * registry is capped at 16 streams; a 17th distinct name reports
 * RE_STATUS_LIMIT. Both register and unregister report RE_STATUS_BUSY while
 * the engine is running (a stream-pattern CE reads the registry during
 * matching, so mid-run mutation is rejected like re_engine_install).
 * re_engine_stream_unregister never destroys the window and is a documented
 * no-op (RE_STATUS_OK) for an unregistered name.
 *
 * GRL stream-pattern CEs (`var: Type from stream("name") [over window(...)]`)
 * evaluate against the registered window during re_engine_run: an event
 * matches when its NAME equals the optional event type (local mapping: local
 * events carry a name plus a scalar value, so the type filter applies to the
 * event name and `var` denotes the event's scalar VALUE; upstream matches
 * event_type against its event type field) and its timestamp passes the
 * window clause (sliding: [watermark - duration, watermark], saturating;
 * tumbling: the current bucket ts/duration == watermark/duration; session:
 * the current open session, the newest retained event and its backward chain
 * with consecutive gaps <= duration; no clause: all retained events). The CE
 * has exists semantics - it matches when at least one retained event
 * qualifies, scanning in timestamp order - and binds one activation per rule
 * match under the engine's standard refraction (bounded divergence: upstream
 * never evaluates stream-pattern CEs at all - its StreamRuleEngine runs the
 * whole rule base per window through fact injection, and the &&
 * stream-join grammar is vapor - so there is no per-event activation
 * multiplicity to mirror). A CE naming an UNREGISTERED stream reports
 * RE_STATUS_NOT_SUPPORTED, the honest gate C3 pinned. Stream-pattern CEs are
 * not RETE-eligible (the collect() constraint admits only fact/literal
 * comparisons) and are classified impure, so they evaluate once at their
 * first-pass position on the linear path like the A6/A8/A9 ineligible forms;
 * backward chaining on them stays RE_STATUS_NOT_SUPPORTED. */
re_status_t re_engine_stream_register(re_engine_t *engine, re_string_t name,
                                      re_stream_window_t *window);
re_status_t re_engine_stream_unregister(re_engine_t *engine, re_string_t name);
/* Window-fact injection + run (upstream execute_rules, f80a541
 * src/streaming/engine.rs:341-378). Injects into the CALLER's facts
 * (upstream injects into a fresh Facts per window - a documented mapping;
 * upstream's per-window rule-base fan-out is a host loop over this call):
 * - WindowEventCount: retained event count as a DOUBLE (upstream :347-353
 *   injects the count as f64), WindowStartTime / WindowEndTime /
 *   WindowDurationMs: the window bounds as INT64 ms (clamped at INT64_MAX),
 *   always injected - even 0. Bounds: tumbling = the current bucket
 *   [bucket_start*retention, +retention), saturating (a tumbling window
 *   reports its current bucket's span even while it holds no events); sliding = [oldest retained
 *   event ts, watermark]; session = [session start, session_end);
 *   sliding/session with no retained events report 0 bounds and count 0.
 *   WindowDurationMs is WindowEndTime - WindowStartTime.
 * - per numeric event NAME (the local "field" - upstream scans each event's
 *   data map for numeric fields, detect_numeric_fields :383; local events
 *   carry one scalar value, so the event name is the field): "<name>Sum",
 *   "<name>Average", "<name>Min", "<name>Max" as DOUBLEs (name verbatim plus
 *   the capitalized suffix, :364-376). Non-numeric values are excluded from
 *   their name's fold; a name whose retained events are all non-numeric gets
 *   NO aggregate facts.
 * Every injection is a host-visible re_facts_set write (so each one bumps
 * the facts mutation serial and stale same-named facts are overwritten).
 * Then runs re_engine_run(engine, facts, NULL, NULL) and reports its status;
 * the pinned parity usage is a rule matching `WindowEventCount > 5`
 * (upstream engine.rs:478-481). */
re_status_t re_engine_stream_run(re_engine_t *engine, re_facts_t *facts,
                                 re_stream_window_t *window);

re_status_t re_engine_set_state_provider(re_engine_t *engine,
                                         const re_state_provider_descriptor_t *descriptor,
                                         re_state_provider_t **out_provider);
void re_state_provider_destroy(re_state_provider_t *provider);
re_status_t re_engine_set_state_provider_v1(
    re_engine_t *engine, const re_state_provider_options_t *options,
    const re_state_provider_descriptor_t *descriptor,
    re_state_provider_t **out_provider);
re_status_t re_state_provider_last_error(
    const re_state_provider_t *provider, re_provider_error_info_t *out_error);
re_status_t re_state_provider_get(re_state_provider_t *provider,
                                  re_string_t key, re_value_t *out_value);
re_status_t re_state_provider_put(re_state_provider_t *provider,
                                  re_string_t key, const re_value_t *value,
                                  uint64_t ttl_ms);
re_status_t re_state_provider_delete(re_state_provider_t *provider,
                                     re_string_t key);
re_status_t re_state_provider_ttl(re_state_provider_t *provider,
                                   re_string_t key, uint64_t *out_ttl_ms);
re_status_t re_state_provider_create_memory(
    re_engine_t *engine, const re_memory_provider_options_t *options,
    re_state_provider_t **out_provider);
re_status_t re_state_provider_update(re_state_provider_t *provider,
                                     re_string_t key, const re_value_t *value,
                                     uint64_t ttl_ms);
re_status_t re_state_provider_snapshot(re_state_provider_t *provider,
                                       re_snapshot_t *out_snapshot);
re_status_t re_state_provider_restore(re_state_provider_t *provider,
                                       const re_snapshot_t *snapshot);
re_status_t re_engine_executor_create(re_engine_t *engine,
                                      const re_concurrency_options_t *options,
                                      re_executor_t **out_executor);
void re_executor_destroy(re_executor_t *executor);

/* Creates an empty fact set owned by the caller; destroy it exactly once. */
re_facts_t *re_facts_create(const re_allocator_t *allocator,
                            const re_limits_t *limits);
/* Releases facts and all copied names/values. NULL is accepted. */
void re_facts_destroy(re_facts_t *facts);
/* Copies name and value into facts; caller retains ownership of both inputs. */
re_status_t re_facts_set(re_facts_t *facts, re_string_t name,
                         const re_value_t *value);
/* Copies the fact into out_value; string data is borrowed until next mutation. */
re_status_t re_facts_get(const re_facts_t *facts, re_string_t name,
                         re_value_t *out_value);

/*
 * Parses source into a candidate program. The candidate owns a copy of source
 * and is independent of source and engine. Destroy it with re_program_destroy.
 */
re_status_t re_program_load(const re_allocator_t *allocator,
                            re_string_t source, const re_limits_t *limits,
                            re_program_t **out_program);
/* Releases a candidate program. NULL is accepted. */
void re_program_destroy(re_program_t *program);
/* Atomically installs program; on failure engine and program remain unchanged. */
re_status_t re_engine_install(re_engine_t *engine, re_program_t *program);

/*
 * Runs the installed program against facts. Matching then assignments are
 * staged in one transaction per firing before the optional callback. The
 * transaction commits its assignments only when the callback succeeds. Fact
 * notification failures are reported after the committed state is visible;
 * they do not compensate with rollback notifications.
 * Run-option limit fields use the engine defaults when zero; a non-zero limit
 * permits exactly that many activations or firings before the next one returns
 * RE_STATUS_LIMIT.
 */
re_status_t re_engine_run(re_engine_t *engine, re_facts_t *facts,
                          const re_run_options_t *options,
                          const re_callbacks_t *callbacks);

/*
 * Asserts the named deffacts set (all sets when name_or_null is NULL) as
 * plain non-logical facts. Dotted paths update existing structured members
 * via re_facts_set_path and otherwise become flat facts; array literals become
 * structured array facts. Unknown name -> RE_STATUS_NOT_FOUND; no program
 * installed -> RE_STATUS_INVALID_ARGUMENT.
 */
re_status_t re_engine_load_deffacts(re_engine_t *engine, re_facts_t *facts,
                                    const char *name_or_null);
/*
 * Clears working memory (all facts, TMS justifications, and pending agenda
 * state once the Phase 2 agenda exists), then loads every deffacts set of the
 * installed program. With no deffacts the call only clears.
 */
re_status_t re_engine_reset_with_deffacts(re_engine_t *engine, re_facts_t *facts);

/* Rule templates produce GRL source text by plain byte substitution of
 * {{identifier}} placeholders in the condition and action templates; the host
 * parses the emitted text via re_program_load and installs it as usual.
 * Bounded exclusions: no JSON round-trip, no CLIPS-deftemplate schema
 * validator, and no engine-side template registry.
 *
 * A placeholder has the exact shape {{identifier}} with no inner spaces; text
 * such as "{{" or "{{ a }}" that does not match that shape is copied through
 * unchanged (no escaping, no type checks). A placeholder with neither a
 * supplied param nor a default fails with RE_STATUS_INVALID_ARGUMENT, as does
 * a supplied param that matches no placeholder in either template. */
typedef struct re_rule_template_t re_rule_template_t;
typedef struct re_template_param_t { re_string_t name; re_string_t value; } re_template_param_t;
/* Copies all four inputs; destroy the result with re_rule_template_destroy. */
re_status_t re_rule_template_create(re_string_t name, re_string_t condition_template,
                                    re_string_t action_template, int32_t salience,
                                    re_rule_template_t **out_template);
/* Sets or replaces the default used when instantiate supplies no value for
 * param; param must be non-empty. */
re_status_t re_rule_template_param_default(re_rule_template_t *t, re_string_t param,
                                           re_string_t default_value);
/* Emits exactly `rule "<rule_name>" [salience N] {\nwhen\n<cond>\nthen\n<action>;\n}`
 * into out_text, omitting " salience N" when the template salience is 0;
 * rule_name is emitted unescaped between the quotes.
 * *inout_text_size carries the buffer capacity in and receives the required
 * size (including the terminating NUL) out; a too-small or NULL buffer yields
 * RE_STATUS_LIMIT after the required size is set. RE_STATUS_INVALID_ARGUMENT
 * (null or malformed inputs, an unresolved placeholder, or a supplied param
 * matching no placeholder) leaves *inout_text_size unchanged. */
re_status_t re_rule_template_instantiate(const re_rule_template_t *t, re_string_t rule_name,
                                         const re_template_param_t *params, size_t param_count,
                                         char *out_text, size_t *inout_text_size);
/* Releases the template and all copied strings. NULL is accepted. */
void re_rule_template_destroy(re_rule_template_t *t);

#ifdef __cplusplus
}
#endif

#endif /* BREAK_RULE_ENGINE_H */
