#ifndef BREAK_RE_INTERNAL_H
#define BREAK_RE_INTERNAL_H

#include "rule_engine/rule_engine.h"
#include <stddef.h>

typedef struct re_allocator_impl_t {
    re_allocator_t api;
} re_allocator_impl_t;
typedef struct re_ir_program_t re_ir_program_t;

typedef struct re_fact_entry_t {
    char *name;
    size_t name_size;
    re_value_t value;
    char *string_data;
    re_value_handle_t *structured;
    uint64_t generation;
    int active;
    int logical;
} re_fact_entry_t;

typedef struct re_tms_justification_t {
    re_fact_id_t derived;
    char *producer_rule;
    size_t producer_rule_size;
    re_fact_id_t *premises;
    size_t premise_count;
} re_tms_justification_t;

typedef struct re_tms_t {
    re_allocator_impl_t allocator;
    re_tms_justification_t *items;
    size_t count;
    size_t capacity;
} re_tms_t;

struct re_facts_t {
    re_allocator_impl_t allocator;
    re_limits_t limits;
    re_fact_entry_t *entries;
    size_t count;
    size_t capacity;
    uint64_t mutation_serial;
    /* Process-unique identity nonce, assigned in re_facts_create; the shared
     * proof graph keys entries on (pointer, nonce) so a new facts object
     * reusing a destroyed one's address cannot alias a stale entry (ABA).
     * The staged transaction clone copies it (same logical facts). */
    uint64_t nonce;
    int running;
    int destroy_requested;
    int notifying;
    /* Transactions opened by the engine run while facts->running is set. */
    int run_transaction_allowed;
    struct re_subscription_t *subscriptions;
    struct re_subscription_t *retired_subscriptions;
    struct re_fact_txn_t *transaction;
    struct re_fact_txn_t *retired_transaction;
    struct re_rete_network_t *rete_network;
    re_tms_t *tms;
};

struct re_fact_txn_t {
    re_facts_t *facts;
    re_facts_t *original;
    re_facts_t *staged;
    int inactive;
    uint64_t generation;
    struct re_fact_txn_t *next_retired;
};

typedef struct re_value_member_t {
    char *key;
    size_t key_size;
    re_value_t scalar;
    re_value_handle_t *child;
} re_value_member_t;

struct re_value_handle_t {
    re_allocator_impl_t allocator;
    int kind;
    re_value_member_t *members;
    size_t count;
    size_t capacity;
};

struct re_subscription_t {
    re_facts_t *facts;
    re_fact_event_fn_t callback;
    void *context;
    struct re_subscription_t *next;
    int active;
};

typedef enum re_operand_kind_t {
    RE_OPERAND_LITERAL, RE_OPERAND_FACT, RE_OPERAND_FUNCTION,
    RE_OPERAND_VARIABLE, RE_OPERAND_ANONYMOUS, RE_OPERAND_GOAL_CALL,
    RE_OPERAND_ARITHMETIC, RE_OPERAND_ARRAY
} re_operand_kind_t;
typedef enum re_arithmetic_operator_t {
    RE_ARITH_ADD, RE_ARITH_SUBTRACT, RE_ARITH_MULTIPLY, RE_ARITH_DIVIDE
} re_arithmetic_operator_t;
typedef struct re_operand_t {
    re_operand_kind_t kind;
    re_value_t value;
    char *fact_name;
    size_t fact_name_size;
    char *function_name;
    size_t function_name_size;
    char *goal_name;
    size_t goal_name_size;
    struct re_operand_t *arguments;
    size_t argument_count;
    re_arithmetic_operator_t arithmetic_operator;
} re_operand_t;

typedef enum re_compare_t { RE_COMPARE_TRUE, RE_COMPARE_EQ, RE_COMPARE_NE, RE_COMPARE_GT,
    RE_COMPARE_GE, RE_COMPARE_LT, RE_COMPARE_LE, RE_COMPARE_CONTAINS,
    RE_COMPARE_STARTS_WITH, RE_COMPARE_ENDS_WITH, RE_COMPARE_MATCHES,
    RE_COMPARE_IN } re_compare_t;
typedef enum re_expr_kind_t { RE_EXPR_COMPARE, RE_EXPR_EXISTS, RE_EXPR_FORALL, RE_EXPR_AND, RE_EXPR_OR, RE_EXPR_NOT, RE_EXPR_TRUE, RE_EXPR_FALSE } re_expr_kind_t;
typedef struct re_expr_t {
    re_expr_kind_t kind;
    re_compare_t compare;
    re_operand_t left;
    re_operand_t right;
    struct re_expr_t *first;
    struct re_expr_t *second;
} re_expr_t;
typedef struct re_action_t {
    char *name;
    size_t name_size;
    re_operand_t value;
    int append;
} re_action_t;
typedef struct re_rule_t {
    char *name;
    size_t name_size;
    int32_t salience;
    re_compare_t compare;
    re_operand_t left;
    re_operand_t right;
    char *action_name;
    size_t action_name_size;
    re_operand_t action_value;
    re_expr_t *condition;
    re_action_t *actions;
    size_t action_count;
    int no_loop;
    int lock_on_active;
    char *agenda_group;
    char *activation_group;
    char *effective_date;
    char *expiry_date;
    size_t source_order;
    size_t module_index;
    char **formal_parameters;
    size_t formal_parameter_count;
} re_rule_t;

typedef struct re_module_t {
    char *name;
    size_t name_size;
    int export_all;
    char **imports;
    size_t import_count;
} re_module_t;

typedef struct re_deffacts_entry_t {
    char *path;
    size_t path_size;
    re_operand_t value;
} re_deffacts_entry_t;

typedef struct re_deffacts_set_t {
    char *name;
    size_t name_size;
    re_deffacts_entry_t *entries;
    size_t entry_count;
} re_deffacts_set_t;

struct re_program_t {
    re_allocator_impl_t allocator;
    re_limits_t limits;
    char *source;
    size_t source_size;
    re_rule_t *rules;
    size_t rule_count;
    char *module_focus;
    char *agenda_focus;
    int64_t clock_epoch;
    int has_clock;
    re_module_t *modules;
    size_t module_count;
    re_deffacts_set_t *deffacts_sets;
    size_t deffacts_set_count;
    re_ir_program_t *ir;
};

re_status_t re_accumulator_evaluate(re_accumulator_kind_t kind, const re_value_t *values, size_t count, re_value_t *out);
re_status_t re_ir_match_rule(const re_engine_t *engine, re_facts_t *facts,
                             const re_ir_program_t *ir, size_t rule_index, int *matched);
/* Bounded condition read-set: every fact path whose re_facts_get_path (or
 * structured-path) hit contributed to a condition match, deduped and capped
 * at RE_IR_MAX_READ_PATHS; overflow silently stops recording, so conditions
 * reading more distinct fact paths get first-N provenance only. Paths borrow
 * IR term strings; the IR program outlives the evaluation. */
#define RE_IR_MAX_READ_PATHS 8u
typedef struct re_ir_read_set_t {
    re_string_t paths[RE_IR_MAX_READ_PATHS];
    size_t count;
} re_ir_read_set_t;
/* Like re_ir_match_rule, but also reports the condition read-set. Recording
 * applies only to condition evaluation; action-RHS resolution
 * (re_ir_resolve_term) never records. */
re_status_t re_ir_match_rule_readset(const re_engine_t *engine, re_facts_t *facts,
                                     const re_ir_program_t *ir, size_t rule_index,
                                     int *matched, re_ir_read_set_t *reads);
re_status_t re_ir_resolve_term(re_engine_t *engine, re_facts_t *facts,
                               const re_ir_program_t *ir, size_t term_index,
                               re_value_t *value);
re_status_t re_program_set_module_focus(re_program_t *program, re_string_t module);
re_status_t re_program_set_agenda_focus(re_program_t *program, re_string_t group);
re_status_t re_program_set_clock(re_program_t *program, int64_t epoch_seconds);
int re_parse_date(const char *text, int64_t *out);
int re_rule_active(const re_rule_t *rule, int64_t now);

#define RE_AGENDA_MAX_PREMISES 8u

typedef struct re_agenda_entry_internal_t {
    size_t rule_index;
    /* Refraction key, sorted by (slot, generation-as-fingerprint): the
     * generation fields hold value fingerprints, not real generations. */
    re_fact_id_t premises[RE_AGENDA_MAX_PREMISES];
    /* True premise ids (real generations, condition order) captured when the
     * activation was created; re_agenda_peek reports these. */
    re_fact_id_t true_premises[RE_AGENDA_MAX_PREMISES];
    size_t premise_count;
    int32_t salience;
    uint64_t sequence;
} re_agenda_entry_internal_t;

struct re_agenda_t {
    re_allocator_impl_t allocator;
    re_agenda_entry_internal_t *pending;
    size_t pending_count;
    size_t pending_cap;
    re_agenda_entry_internal_t *fired;
    size_t fired_count;
    size_t fired_cap; /* refraction keys */
    uint64_t next_sequence;
    /* Owning engine (NULL for standalone agendas); lets re_agenda_peek
     * resolve rule names through the installed program. */
    re_engine_t *engine;
    int persistent;
};

re_status_t re_agenda_create_internal(re_allocator_t *alloc, re_agenda_t **out);
void       re_agenda_destroy_internal(re_agenda_t *agenda);
void       re_agenda_clear_pending(re_agenda_t *agenda);
void       re_agenda_reset(re_agenda_t *agenda);
int        re_agenda_refracted(const re_agenda_t *agenda, size_t rule_index,
                               const re_fact_id_t *premises, size_t premise_count);
re_status_t re_agenda_push(re_agenda_t *agenda, size_t rule_index, int32_t salience,
                           const re_fact_id_t *premises, size_t premise_count);
/* Like re_agenda_push, but also records the true premise ids (unsorted, real
 * generations) for inspection; NULL true_premises records the key premises
 * as passed. */
re_status_t re_agenda_push_full(re_agenda_t *agenda, size_t rule_index, int32_t salience,
                                const re_fact_id_t *premises, size_t premise_count,
                                const re_fact_id_t *true_premises);
re_status_t re_agenda_mark_fired(re_agenda_t *agenda, const re_agenda_entry_internal_t *entry);
int        re_agenda_pop_highest(re_agenda_t *agenda, re_agenda_entry_internal_t *out);

/* Shared proof graph (Task 14): an engine-owned cache of final backward-query
 * results, consulted in re_backward_machine_dispatch AFTER option
 * normalization, keyed on the exact goal text, the facts identity, the
 * normalized search options (max_depth, max_solutions, strategy), the engine
 * config serial, and the facts mutation generation - so cached results equal
 * the final strategy/NOT-resolved results. Only RE_QUERY_PROVED and
 * RE_QUERY_DISPROVED results are stored; LIMIT and UNKNOWN are never cached.
 * An entry is stale when either serial moved and is dropped on lookup; the
 * generation check is coarse (any mutation of the same facts object
 * invalidates every entry bound to it). When the table is full the store
 * path clears every entry (documented clear-all eviction). The facts identity
 * is pointer plus nonce, so a new facts object reusing a destroyed one's
 * address never aliases a live entry (ABA). */
#define RE_PROOF_GRAPH_CAPACITY 64u

typedef struct re_proof_graph_entry_t {
    char *goal;
    size_t goal_size;
    re_facts_t *facts; /* identity only, not owned */
    uint64_t facts_nonce; /* facts->nonce at store time (ABA guard) */
    uint64_t generation; /* facts->mutation_serial at store time */
    uint64_t config_serial; /* engine->config_serial at store time */
    size_t max_depth;
    size_t max_solutions;
    uint32_t strategy;
    re_query_result_t result;
    re_proof_t **proofs; /* cloned, owned */
    size_t proof_count;
} re_proof_graph_entry_t;

typedef struct re_proof_graph_t {
    re_allocator_impl_t allocator;
    re_proof_graph_entry_t entries[RE_PROOF_GRAPH_CAPACITY];
    size_t count;
    uint64_t hits;
    uint64_t misses;
} re_proof_graph_t;

struct re_engine_t {
    re_allocator_impl_t allocator;
    re_limits_t limits;
    re_program_t *program;
    int running;
    int destroy_requested;
    struct re_function_t *functions;
    re_executor_t *executor;
    /* First attached per-rule network; kept in sync with rete_networks
     * for re_engine_rete_network() and the capability probes. */
    re_rete_network_t *rete_network;
    /* Per-rule RETE networks parallel to program->rules; NULL entries
     * mark rules that are not RETE-eligible (or not yet attached). */
    re_rete_network_t **rete_networks;
    size_t rete_network_count;
    re_agenda_t *agenda;
    /* Lazy-created on the first shared (non-disabled) backward query;
     * released by re_engine_destroy. config_serial bumps on program install
     * and function register/unregister so cached proofs never outlive the
     * rules or functions they were derived from. */
    re_proof_graph_t *proof_graph;
    uint64_t config_serial;
};

typedef struct re_stream_event_impl_t {
    uint64_t timestamp;
    char *name;
    size_t name_size;
    re_value_t value;
    char *value_data;
} re_stream_event_impl_t;

struct re_stream_window_t {
    re_allocator_impl_t allocator;
    re_stream_window_options_t options;
    re_stream_event_impl_t *events;
    size_t count;
    size_t capacity;
    uint64_t watermark;
    uint64_t bucket_start;
    uint64_t session_end;
};

re_status_t re_stream_window_create_bounded(re_engine_t *engine,
                                            const re_stream_window_options_t *options,
                                            re_stream_window_t **out_window);
re_status_t re_stream_window_record_bounded(re_stream_window_t *window,
                                            uint64_t timestamp_ms,
                                            re_string_t event_name,
                                            const re_value_t *value);

struct re_state_provider_t {
    re_allocator_impl_t allocator;
    re_state_provider_descriptor_t descriptor;
    re_provider_error_info_t last_error;
    void *implementation;
};

re_status_t re_memory_provider_init(re_engine_t *engine,
                                    const re_memory_provider_options_t *options,
                                    re_state_provider_t **out_provider);

typedef struct re_rete_condition_t {
    re_string_t fact_name;
    re_compare_t compare;
    re_value_t value;
} re_rete_condition_t;

typedef struct re_rete_activation_t {
    re_fact_id_t left;
    re_fact_id_t right;
    uint64_t sequence;
    re_fact_id_t lineage[8];
    size_t lineage_count;
    re_string_t producer_rule;
} re_rete_activation_t;

typedef struct re_rete_alpha_memory_t {
    re_fact_id_t *facts;
    size_t count;
    size_t capacity;
} re_rete_alpha_memory_t;

typedef struct re_rete_token_t {
    re_fact_id_t lineage[8];
    size_t lineage_count;
    uint64_t sequence;
} re_rete_token_t;

struct re_rete_network_t {
    re_allocator_impl_t allocator;
    re_facts_t *facts;
    /* Chains every network attached to the same fact set; head is
     * facts->rete_network. Engine per-rule networks append here so
     * several rule networks can share one fact set. */
    struct re_rete_network_t *next_on_facts;
    re_engine_t *owner_engine;
    int engine_owned;
    const re_program_t *program;
    re_rete_condition_t *conditions;
    size_t condition_count;
    re_rete_activation_t *activations;
    size_t activation_count;
    size_t activation_capacity;
    re_rete_alpha_memory_t *alpha_memories;
    re_rete_token_t *tokens;
    size_t token_count;
    size_t token_capacity;
    re_fact_id_t lineage_scratch[8];
    uint64_t next_sequence;
    re_string_t producer_rule;
    struct re_subscription_t *subscription;
    int invalid;
};

struct re_function_t {
    re_engine_t *engine;
    char *name;
    size_t name_size;
    re_function_call_fn_t call;
    re_function_release_fn_t release;
    void *context;
    size_t active_calls;
    int unregistered;
    struct re_function_t *next;
};

typedef struct re_query_binding_impl_t {
    char *name;
    size_t name_size;
    re_value_t value;
    char *string_data;
} re_query_binding_impl_t;

typedef struct re_proof_node_impl_t {
    char *rule_name;
    size_t rule_name_size;
} re_proof_node_impl_t;

typedef struct re_proof_edge_impl_t {
    size_t parent_index;
    size_t child_index;
} re_proof_edge_impl_t;

struct re_proof_t {
    re_allocator_impl_t allocator;
    re_query_binding_impl_t *bindings;
    size_t binding_count;
    char **trace_names;
    size_t trace_count;
    re_proof_node_impl_t *nodes;
    size_t node_count;
    re_proof_edge_impl_t *edges;
    size_t edge_count;
};

struct re_query_t {
    re_allocator_impl_t allocator;
    re_engine_t *engine;
    re_facts_t *facts;
    re_subscription_t *subscription;
    re_query_result_t result;
    re_proof_t **proofs;
    size_t proof_count;
    size_t next_proof;
    size_t max_depth;
    size_t max_solutions;
    int invalidated;
};

void *re_alloc(const re_allocator_impl_t *allocator, size_t size);
void *re_realloc(const re_allocator_impl_t *allocator, void *memory, size_t size);
void re_free(const re_allocator_impl_t *allocator, void *memory);
re_status_t re_facts_set_impl(re_facts_t *facts, re_string_t name,
                              const re_value_t *value, int emit_event);
re_status_t re_facts_notify(re_facts_t *facts, re_fact_change_kind_t kind, size_t index);
/* Wholesale working-memory reset: drops all fact entries and TMS justifications. */
re_status_t re_facts_clear_all(re_facts_t *facts);
/* Resets agenda state (pending activations and refraction keys) when an agenda exists. */
void re_engine_clear_agenda(re_engine_t *engine);
/* Lazily creates the engine-owned agenda and back-links it to the engine. */
re_status_t re_engine_ensure_agenda(re_engine_t *engine);
void re_allocator_init(re_allocator_impl_t *target, const re_allocator_t *source);
re_status_t re_tms_clone(const re_tms_t *source, const re_allocator_impl_t *allocator, re_tms_t **out);
re_status_t re_facts_get_structured_path(const re_facts_t *facts, re_string_t path,
                                         const re_value_handle_t **out);
void re_tms_destroy(re_tms_t *tms);
void re_tms_remove_derived(re_facts_t *facts, re_fact_id_t derived);
void re_tms_remove_premise(re_facts_t *facts, re_fact_id_t premise);
re_limits_t re_default_limits(void);
re_status_t re_copy_string(const re_allocator_impl_t *allocator, re_string_t input, char **out);
void re_operand_destroy(const re_allocator_impl_t *allocator, re_operand_t *operand);
void re_expr_destroy(const re_allocator_impl_t *allocator, re_expr_t *expr);
re_status_t re_operand_copy(const re_allocator_impl_t *allocator, const re_operand_t *source,
                             re_operand_t *target);
re_status_t re_operand_resolve(re_engine_t *engine, re_facts_t *facts,
                                const re_operand_t *operand, re_value_t *value);
re_status_t re_facts_resolve(const re_facts_t *facts, re_string_t name, re_value_t *out);
re_status_t re_facts_begin_for_run(re_facts_t *facts, re_fact_txn_t **out_transaction);
re_status_t re_facts_append_value(re_facts_t *facts, re_string_t name, const re_value_t *value);
re_status_t re_facts_contains_value(const re_facts_t *facts, re_string_t path,
                                    const re_value_t *needle, int *matched);
int re_value_compare(const re_value_t *left, const re_value_t *right, re_compare_t compare);
int re_value_equal_typed(const re_value_t *left, const re_value_t *right);
int re_program_uses_rete(const re_program_t *program, const re_facts_t *facts);
re_status_t re_engine_run_rete(re_engine_t *engine, re_facts_t *facts,
                               const re_run_options_t *options,
                                  const re_callbacks_t *callbacks);

int re_condition_is_pure(const re_expr_t *expr);
re_status_t re_engine_match_rule(const re_engine_t *engine, const re_facts_t *facts,
                                 const re_rule_t *rule, int *matched);
re_status_t re_executor_match(re_executor_t *executor, const re_engine_t *engine,
                              const re_facts_t *facts, const re_program_t *program,
                              unsigned char *matches);
void re_executor_attach(re_executor_t *executor, re_engine_t *engine);
re_status_t re_executor_create_impl(re_engine_t *engine, const re_concurrency_options_t *options,
                                    re_executor_t **out_executor);
void re_executor_destroy_impl(re_executor_t *executor);

re_status_t re_query_create_bounded(re_engine_t *engine, re_facts_t *facts,
                                     re_string_t goal, const re_query_options_t *options,
                                     re_query_t **out_query);
re_status_t re_backward_query_create(re_engine_t *engine, re_facts_t *facts,
                                      re_string_t goal, const re_query_options_t *options,
                                      re_query_t **out_query);
re_status_t re_backward_machine_dispatch(re_engine_t *engine, re_facts_t *facts,
                                          re_string_t goal, const re_query_options_t *options,
                                          re_query_t **out_query);

/* Lazily creates engine->proof_graph. Never fails the owning query: an
 * allocation failure leaves proof_graph NULL and the caller falls back to
 * an uncached run. */
void re_proof_graph_ensure(re_engine_t *engine);
void re_proof_graph_destroy(re_proof_graph_t *graph);
re_status_t re_proof_clone(const re_allocator_impl_t *allocator,
                            const re_proof_t *source, re_proof_t **out);
/* Counts a hit or miss and, on a hit, returns a borrowed pointer to the
 * live entry (clone its proofs before storing anything else). Stale
 * entries (serial mismatch) are dropped and counted as misses. */
re_status_t re_proof_graph_lookup(re_proof_graph_t *graph, re_facts_t *facts,
                                   re_string_t goal, const re_query_options_t *options,
                                   uint64_t config_serial,
                                   const re_proof_graph_entry_t **out_entry);
/* Clones the proofs into a new entry; clears all entries when full. */
re_status_t re_proof_graph_store(re_proof_graph_t *graph, re_facts_t *facts,
                                  re_string_t goal, const re_query_options_t *options,
                                  uint64_t config_serial, re_query_result_t result,
                                  re_proof_t *const *proofs, size_t proof_count);

re_status_t re_rete_network_create(re_facts_t *facts,
                                    const re_rete_condition_t conditions[2],
                                    const re_allocator_t *allocator,
                                    re_rete_network_t **out_network);
re_status_t re_rete_network_create_conditions(re_facts_t *facts,
                                               const re_rete_condition_t *conditions,
                                               size_t condition_count,
                                               const re_allocator_t *allocator,
                                               re_rete_network_t **out_network);
re_status_t re_rete_network_create_rule(re_facts_t *facts,
                                        const re_rule_t *rule,
                                        const re_allocator_t *allocator,
                                        re_rete_network_t **out_network);
/* Engine-owned per-rule variant: chains the network off
 * facts->rete_network instead of claiming it (never RE_STATUS_BUSY),
 * and returns RE_STATUS_NOT_SUPPORTED with *out_network NULL for
 * rules outside the collect() eligibility constraint. */
re_status_t re_rete_network_create_rule_chained(re_facts_t *facts,
                                        const re_rule_t *rule,
                                        const re_allocator_t *allocator,
                                        re_rete_network_t **out_network);
void re_rete_network_destroy_internal(re_rete_network_t *network);
void re_rete_network_detach_facts(re_rete_network_t *network);
size_t re_rete_activation_count(const re_rete_network_t *network);
re_status_t re_rete_activation_get(const re_rete_network_t *network,
                                    size_t index, re_rete_activation_t *out);
int re_rete_conditions_from_rule(const re_rule_t *rule,
                                 re_rete_condition_t conditions[2]);

#endif
