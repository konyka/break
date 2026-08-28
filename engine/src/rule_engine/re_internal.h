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
    int running;
    int mutation_allowed;
    int read_allowed;
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
re_status_t re_ir_resolve_term(re_engine_t *engine, re_facts_t *facts,
                               const re_ir_program_t *ir, size_t term_index,
                               re_value_t *value);
re_status_t re_program_set_module_focus(re_program_t *program, re_string_t module);
re_status_t re_program_set_agenda_focus(re_program_t *program, re_string_t group);
re_status_t re_program_set_clock(re_program_t *program, int64_t epoch_seconds);
int re_parse_date(const char *text, int64_t *out);
int re_rule_active(const re_rule_t *rule, int64_t now);

struct re_engine_t {
    re_allocator_impl_t allocator;
    re_limits_t limits;
    re_program_t *program;
    int running;
    int destroy_requested;
    struct re_function_t *functions;
    re_executor_t *executor;
    re_rete_network_t *rete_network;
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
/* No-op until the Phase 2 agenda lands; then clears pending agenda state. */
void re_engine_clear_agenda(re_engine_t *engine);
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
void re_rete_network_destroy_internal(re_rete_network_t *network);
void re_rete_network_detach_facts(re_rete_network_t *network);
size_t re_rete_activation_count(const re_rete_network_t *network);
re_status_t re_rete_activation_get(const re_rete_network_t *network,
                                    size_t index, re_rete_activation_t *out);
int re_rete_conditions_from_rule(const re_rule_t *rule,
                                 re_rete_condition_t conditions[2]);

#endif
