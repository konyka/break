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
#define RE_ABI_VERSION_MINOR 3u

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
typedef struct re_fact_event_t re_fact_event_t;
typedef struct re_fact_txn_t re_fact_txn_t;
typedef struct re_subscription_t re_subscription_t;
typedef struct re_agenda_t re_agenda_t;
typedef struct re_rete_network_t re_rete_network_t;
typedef struct re_query_t re_query_t;
typedef struct re_proof_t re_proof_t;
typedef struct re_stream_window_t re_stream_window_t;
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
} re_stream_window_options_t;

typedef struct re_stream_filter_options_t {
  uint32_t struct_size;
  uint32_t abi_version;
  re_string_t event_type;
  re_string_t key;
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
  RE_STREAM_AGGREGATE_LAST = 7
} re_stream_aggregate_kind_t;

/* Callers set struct_size before each call so older consumers remain
 * source-compatible. Implementations must gate each appended field on
 * struct_size: fields before minimum require only the pre-Task-16 size
 * (offsetof(re_stream_aggregate_result_t, minimum)); minimum/maximum/first/last
 * are written only when struct_size covers them, and bytes beyond struct_size
 * are never touched. first/last copy the retained event value; STRING data is
 * borrowed from the window and stays valid until the next window mutation or
 * destroy (the same borrow re_facts_get documents). */
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
} re_stream_aggregate_result_t;

typedef struct re_stream_correlation_options_t {
  uint32_t struct_size;
  uint32_t abi_version;
  re_string_t first_event_type;
  re_string_t second_event_type;
  re_string_t key;
  uint64_t timeout_ms;
} re_stream_correlation_options_t;

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
re_status_t re_facts_insert(re_facts_t *facts, re_string_t name,
                            const re_value_t *value, re_fact_id_t *out_id);
re_status_t re_facts_update(re_facts_t *facts, re_fact_id_t id,
                            const re_value_t *value);
re_status_t re_facts_retract(re_facts_t *facts, re_fact_id_t id);
re_status_t re_facts_insert_logical(re_facts_t *facts, re_string_t name,
                                    const re_value_t *value,
                                    re_string_t producer_rule,
                                    const re_fact_id_t *premises,
                                    size_t premise_count, re_fact_id_t *out_id);
int re_facts_is_logical(const re_facts_t *facts, re_fact_id_t id);
re_status_t re_facts_provenance_get(const re_facts_t *facts, re_fact_id_t id,
                                    re_fact_provenance_t *out_provenance);
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
/* Runs pattern (an ordinary query goal string, e.g. "Score == S") through an
 * internal bounded query - max_depth 64 (the re_engine_query default) and a
 * documented max_solutions cap of 1024 - and folds the binding named field
 * over the solutions in DFS order. The internal query is destroyed before
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
 * generation - any mutation of the same fact set invalidates its entries,
 * including the first assert of a previously absent fact. The graph is
 * created lazily on the first shared query, holds at most 64 entries, and
 * clears every entry when full. A NULL engine or NULL counter is
 * RE_STATUS_INVALID_ARGUMENT; an engine that has not cached yet reports
 * zeroes with RE_STATUS_OK. */
re_status_t re_engine_proof_graph_stats(const re_engine_t *engine,
                                        uint64_t *out_hits, uint64_t *out_misses);
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
 * RE_STATUS_INVALID_ARGUMENT for all four. FIRST/LAST copy the value of the
 * earliest/latest matching event by timestamp (insertion order breaks ties)
 * and accept any value type. An empty filtered set reports
 * RE_STATUS_NOT_FOUND for MIN/MAX/FIRST/LAST; COUNT keeps its 0/OK behavior.
 * RE_STATUS_NOT_FOUND returns before out_result is touched.
 * out_result->struct_size must cover at least the pre-Task-16 fields
 * (offsetof(re_stream_aggregate_result_t, minimum)); appended fields are
 * written only when struct_size covers them, and first/last fold over every
 * matching event regardless of kind. */
re_status_t re_stream_window_aggregate_v1(
    const re_stream_window_t *window,
    const re_stream_filter_options_t *filter,
    re_stream_aggregate_kind_t kind,
    re_stream_aggregate_result_t *out_result);
re_status_t re_stream_window_correlate_v1(
    const re_stream_window_t *window,
    const re_stream_correlation_options_t *options,
    uint64_t *out_matches);
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
