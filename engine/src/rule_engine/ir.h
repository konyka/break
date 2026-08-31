#ifndef BREAK_RULE_ENGINE_IR_H
#define BREAK_RULE_ENGINE_IR_H

#include "re_internal.h"

typedef uint64_t re_ir_id_t;
typedef struct re_ir_span_t { size_t start; size_t end; } re_ir_span_t;
typedef enum re_ir_term_kind_t {
    RE_IR_TERM_NONE, RE_IR_TERM_BOOL, RE_IR_TERM_INT64, RE_IR_TERM_DOUBLE,
    RE_IR_TERM_STRING, RE_IR_TERM_FACT, RE_IR_TERM_FUNCTION, RE_IR_TERM_GOAL,
    RE_IR_TERM_ARITHMETIC, RE_IR_TERM_ARRAY, RE_IR_TERM_METHOD_CALL,
    RE_IR_TERM_NULL
} re_ir_term_kind_t;
typedef struct re_ir_term_t {
    re_ir_id_t id;
    re_ir_term_kind_t kind;
    re_value_t value;
    char *name;
    size_t name_size;
    size_t first_argument;
    size_t argument_count;
    re_arithmetic_operator_t arithmetic_operator;
    size_t *argument_indices;
    re_ir_span_t span;
} re_ir_term_t;
typedef struct re_ir_expr_t {
    re_ir_id_t id;
    re_expr_kind_t kind;
    re_compare_t compare;
    size_t left;
    size_t right;
    size_t first;
    size_t second;
    re_ir_span_t span;
    /* Nonzero only on RE_EXPR_EXISTS/RE_EXPR_FORALL compiled from the
     * parenthesized form (exists( <expr> )): `first` is the inner expression
     * index and left/right are unused. Zero keeps the restricted
     * term-operand form (left/right term indices). */
    int nested;
    /* A5 multifield op (re_multifield_op_t): RE_MULTIFIELD_NONE on every
     * other kind. On RE_EXPR_MULTIFIELD, COUNT carries the comparison in
     * `compare` and the numeric literal term in `right`; the bare predicates
     * (first/last/empty/not_empty/collect) keep right == SIZE_MAX. */
    int multifield;
    /* A6 accumulate payload (RE_EXPR_ACCUMULATE only; owned copies of the
     * re_expr_t fields, freed by re_ir_destroy). func is a
     * re_accumulator_kind_t; the injected fact key is
     * "<accumulate_type>.<accumulate_func_name>". */
    char *accumulate_type;
    size_t accumulate_type_size;
    char *accumulate_field;
    size_t accumulate_field_size;
    char **accumulate_conditions;
    size_t accumulate_condition_count;
    char *accumulate_func_name;
    size_t accumulate_func_name_size;
    int accumulate_func;
    /* A9 typed-form payload (RE_EXPR_TYPED only; owned copy freed by
     * re_ir_destroy): the declared type name, used as the candidate-iteration
     * prefix. The inner condition is `first`; left/right stay zeroed. */
    char *typed_type;
    size_t typed_type_size;
    /* C3 stream-pattern CE payload (RE_EXPR_STREAM_PATTERN only; owned
     * copies freed by re_ir_destroy): the bound variable, the optional event
     * type (NULL when absent), the stream name, and the optional window
     * {duration_ms, re_stream_window_kind_t} with presence flags. `session`
     * is a documented local extension over upstream f80a541
     * stream_syntax.rs parse_window_type (sliding|tumbling only there); the
     * window duration doubles as the session timeout. left/right/first stay
     * zeroed - the node has no term or expression children. */
    char *stream_var;
    size_t stream_var_size;
    char *stream_event_type;
    size_t stream_event_type_size;
    char *stream_name;
    size_t stream_name_size;
    uint64_t stream_window_duration_ms;
    int stream_window_kind;
    int stream_has_event_type;
    int stream_has_window;
} re_ir_expr_t;
/* re_action_t.append carries this parser signal for a `$Fact.method(...)`
 * then-statement; re_ir_compile lowers it to RE_IR_ACTION_METHOD_CALL.
 * RE_ACTION_BUILTIN_CALL does the same for a bare whitelisted
 * `name(args)` action statement (A8: retract/log/ActivateAgendaGroup and the
 * D5 workflow trio), lowered to RE_IR_ACTION_BUILTIN_CALL. */
#define RE_ACTION_METHOD_CALL 2
#define RE_ACTION_BUILTIN_CALL 3
typedef enum re_ir_action_kind_t {
    RE_IR_ACTION_ASSIGN, RE_IR_ACTION_METHOD_CALL, RE_IR_ACTION_BUILTIN_CALL
} re_ir_action_kind_t;
typedef struct re_ir_action_t {
    re_ir_id_t id;
    /* ASSIGN/METHOD_CALL: the target FACT term. BUILTIN_CALL: the FUNCTION
     * term holding the action name and argument terms. */
    size_t target;
    /* SIZE_MAX on RE_IR_ACTION_BUILTIN_CALL. */
    size_t value;
    int append;
    re_ir_action_kind_t kind;
    char *method_name;
    size_t method_name_size;
    re_ir_span_t span;
} re_ir_action_t;
typedef struct re_ir_rule_t {
    re_ir_id_t id;
    size_t name;
    size_t condition;
    size_t first_action;
    size_t action_count;
    size_t module;
    int32_t salience;
    /* B4: mirror of re_rule_t.auto_focus (upstream Activation.auto_focus),
     * carried for IR consumers; the engine reads the re_rule_t flag. */
    int auto_focus;
    re_ir_span_t span;
} re_ir_rule_t;
typedef struct re_ir_module_t {
    re_ir_id_t id;
    size_t name;
    size_t first_import;
    size_t import_count;
    int export_all;
} re_ir_module_t;
typedef struct re_ir_deffacts_entry_t {
    re_ir_id_t id;
    size_t path;
    size_t value;
} re_ir_deffacts_entry_t;
typedef struct re_ir_deffacts_set_t {
    re_ir_id_t id;
    size_t name;
    size_t first_entry;
    size_t entry_count;
    re_ir_span_t span;
} re_ir_deffacts_set_t;
/* A7 query blocks (upstream grl_query.rs). name is a FACT-kind term holding
 * the query name; goal is a RE_IR_TERM_STRING term holding the raw goal text
 * (the executor splits &&/|| textually per upstream). when is an expr index
 * or SIZE_MAX. The three action blocks are ranges into query_actions,
 * appended in RE_QUERY_BLOCK_* order per query. */
typedef struct re_ir_query_action_t {
    re_ir_id_t id;
    /* Assignment: FACT term (target path); call: FUNCTION term (call name). */
    size_t name;
    /* Assignment: scalar literal term; SIZE_MAX for calls. */
    size_t value;
    /* Call: RE_IR_TERM_STRING term with the raw argument text; SIZE_MAX for
     * assignments. */
    size_t args;
    int is_call;
} re_ir_query_action_t;
typedef struct re_ir_query_t {
    re_ir_id_t id;
    size_t name;
    size_t goal;
    size_t when; /* expr index or SIZE_MAX */
    size_t first_action[RE_QUERY_BLOCK_COUNT];
    size_t action_count[RE_QUERY_BLOCK_COUNT];
    int strategy; /* RE_QUERY_STRATEGY_* */
    size_t max_depth;
    size_t max_solutions;
    int enable_memoization;
    int enable_optimization; /* accepted, documented no-op */
    re_ir_span_t span;
} re_ir_query_t;
struct re_ir_program_t {
    re_allocator_impl_t allocator;
    size_t source_size;
    char *strings;
    size_t string_size;
    re_ir_term_t *terms;
    size_t term_count;
    re_ir_expr_t *exprs;
    size_t expr_count;
    re_ir_action_t *actions;
    size_t action_count;
    re_ir_rule_t *rules;
    size_t rule_count;
    re_ir_module_t *modules;
    size_t module_count;
    re_ir_deffacts_set_t *deffacts_sets;
    size_t deffacts_set_count;
    re_ir_deffacts_entry_t *deffacts_entries;
    size_t deffacts_entry_count;
    re_ir_query_t *queries;
    size_t query_count;
    re_ir_query_action_t *query_actions;
    size_t query_action_count;
    re_ir_span_t *spans;
    size_t span_count;
};

re_status_t re_ir_compile(const re_program_t *program, re_ir_program_t **out);
re_status_t re_ir_validate(const re_ir_program_t *ir);
void re_ir_destroy(re_ir_program_t *ir);

#endif
