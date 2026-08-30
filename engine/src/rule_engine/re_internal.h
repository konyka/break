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

/* B2 (upstream proof_graph.rs justification shape): one fact read observed
 * during a backward run - the path, whether it resolved, and a typed
 * fingerprint of the observed value (re_value_fingerprint). A cached
 * entry's premise set is the local analog of an upstream node's
 * justification premise keys: the entry survives a facts mutation exactly
 * when every premise still holds, so mutating a fact the derivation never
 * read no longer invalidates. Overflow of RE_PROOF_GRAPH_MAX_PREMISES or
 * an untracked read (a user function ran mid-proof) flips opaque, pinning
 * the entry to the coarse generation check. */
#define RE_PROOF_GRAPH_MAX_PREMISES 32u

typedef struct re_proof_graph_premise_t {
    char *path; /* owned */
    size_t path_size;
    uint64_t fingerprint; /* value fingerprint at read time; 0 when absent */
    int present;
} re_proof_graph_premise_t;

typedef struct re_premise_set_t {
    re_proof_graph_premise_t *items; /* owned, deduped by path (first read wins) */
    size_t count;
    int opaque;
} re_premise_set_t;

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
    /* Borrowed premise capture installed by re_backward_machine_dispatch
     * for the duration of one shared backward query (saved/restored across
     * the NOT recursion); NULL whenever no capturing query runs. The fact
     * reads in backward.c record the run's premise set here so the proof
     * graph can store it with the cached entry. */
    re_premise_set_t *premise_capture;
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
    RE_ARITH_ADD, RE_ARITH_SUBTRACT, RE_ARITH_MULTIPLY, RE_ARITH_DIVIDE,
    RE_ARITH_MODULO
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
    RE_COMPARE_IN, RE_COMPARE_NOT_CONTAINS } re_compare_t;
/* A5 multifield condition ops (upstream grl.rs L115-155): RE_MULTIFIELD_COUNT
 * uses expr->compare and expr->right (a numeric literal); the bare predicates
 * carry no comparison and leave the right operand zeroed. */
typedef enum re_multifield_op_t { RE_MULTIFIELD_NONE, RE_MULTIFIELD_COUNT,
    RE_MULTIFIELD_FIRST, RE_MULTIFIELD_LAST, RE_MULTIFIELD_EMPTY,
    RE_MULTIFIELD_NOT_EMPTY, RE_MULTIFIELD_COLLECT } re_multifield_op_t;
typedef enum re_expr_kind_t { RE_EXPR_COMPARE, RE_EXPR_EXISTS, RE_EXPR_FORALL, RE_EXPR_AND, RE_EXPR_OR, RE_EXPR_NOT, RE_EXPR_TRUE, RE_EXPR_FALSE, RE_EXPR_MULTIFIELD, RE_EXPR_ACCUMULATE, RE_EXPR_TEST, RE_EXPR_TYPED, RE_EXPR_STREAM_PATTERN } re_expr_kind_t;
typedef struct re_expr_t {
    re_expr_kind_t kind;
    re_compare_t compare;
    re_operand_t left;
    re_operand_t right;
    struct re_expr_t *first;
    struct re_expr_t *second;
    int multifield;
    /* A6 accumulate payload (kind == RE_EXPR_ACCUMULATE only; all owned):
     * type is the source pattern ("Order"), field the $var-extracted field
     * (NULL for the $var-less form), conditions the raw mini-condition
     * strings, func a re_accumulator_kind_t, and func_name the source
     * spelling (the injected fact key is "<type>.<func_name>"). */
    char *accumulate_type;
    size_t accumulate_type_size;
    char *accumulate_field;
    size_t accumulate_field_size;
    char **accumulate_conditions;
    size_t accumulate_condition_count;
    char *accumulate_func_name;
    size_t accumulate_func_name_size;
    int accumulate_func;
    /* A9 typed-form payload (kind == RE_EXPR_TYPED only; owned): the declared
     * type name, used as the candidate-iteration prefix at evaluation. The
     * inner condition tree rides `first`; left/right stay zeroed. */
    char *typed_type;
    size_t typed_type_size;
    /* C3 stream-pattern CE payload (kind == RE_EXPR_STREAM_PATTERN only; all
     * owned): `var: EventType from stream("name") over window(<n> <unit>,
     * sliding|tumbling|session)` (upstream rust-rule-engine v1.21.4 f80a541
     * src/parser/grl/stream_syntax.rs parse_stream_pattern). event_type is
     * NULL when the pattern omits it (`e: from stream("events")`); the window
     * clause is optional (stream_has_window). The kind carries
     * re_stream_window_kind_t (rule_engine.h); `session` is a LOCAL
     * EXTENSION - upstream's GRL window-type parser accepts only
     * sliding|tumbling (stream_syntax.rs parse_window_type) even though
     * WindowType::Session exists in the Rust enum, and the duration maps to
     * the session timeout (window(10 min, session)). C5 wired FORWARD
     * evaluation (ir_eval.c): the CE consults the engine's stream registry
     * (re_engine_stream_lookup); an UNREGISTERED stream keeps the C3 gate's
     * RE_STATUS_NOT_SUPPORTED (pinned by test_rule_engine_stream_grl.c - the
     * brief's NOT_FOUND mapping would let re_engine_run swallow the error as
     * an ordinary non-match, breaking that pin). Backward chaining stays
     * honestly NOT_SUPPORTED via the node's `left` operand, which carries
     * kind RE_OPERAND_ARITHMETIC as a sentinel: the backward compatibility
     * evaluator (backward.c machine_condition_matches) and the bind machine's
     * shape probe (backward_machine_bind.c condition_shape_supported) reject
     * arithmetic-shaped condition operands with RE_STATUS_NOT_SUPPORTED/0, so
     * the zeroed operand pair can never masquerade as a vacuously-true
     * RE_COMPARE_TRUE literal pair the way it would if left zeroed
     * (re_value_compare(_, _, RE_COMPARE_TRUE) is unconditional). The sentinel
     * is kept (not replaced with explicit backward branches) because those
     * files are outside C5's change scope and the sentinel already gates them
     * exactly. */
    char *stream_var;
    size_t stream_var_size;
    char *stream_event_type;
    size_t stream_event_type_size;
    char *stream_name;
    size_t stream_name_size;
    uint64_t stream_window_duration_ms;
    int stream_window_kind; /* re_stream_window_kind_t when stream_has_window */
    int stream_has_event_type;
    int stream_has_window;
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
    /* B4 (upstream rusty-rule-engine v1.21.4 rete/agenda.rs
     * Activation.auto_focus): with an agenda_group, a genuinely new
     * activation switches the agenda focus to the rule's group (focus-stack
     * push semantics, see re_program_push_agenda_focus). Without an
     * agenda_group the flag is a documented no-op: upstream allows the
     * combination and nothing ever switches. */
    int auto_focus;
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

/* A7 GRL query blocks (upstream rust-rule-engine v1.21.4 grl_query.rs): the
 * top-level `query "Name" { goal: <text>; ... }` form. The goal stays raw
 * text (the executor splits &&/|| textually per upstream); `when` is a parsed
 * condition expression (NULL when absent). Action statements are either flat
 * scalar assignments `Name = true|false|<number>|"string"` or calls
 * `Name(<raw args>)` keeping the raw argument text; anything else is a parse
 * error at load (bounded divergence from upstream's lenient fallback). */
typedef struct re_query_action_stmt_t {
    char *name;              /* assignment target path or call name */
    size_t name_size;
    int is_call;
    re_operand_t value;      /* assignment: RE_OPERAND_LITERAL scalar; zeroed for calls */
    char *args;              /* call: raw argument text between the parens ("" when empty) */
    size_t args_size;
} re_query_action_stmt_t;

/* Action block slots: 0 = on-success, 1 = on-failure, 2 = on-missing. */
#define RE_QUERY_BLOCK_SUCCESS 0u
#define RE_QUERY_BLOCK_FAILURE 1u
#define RE_QUERY_BLOCK_MISSING 2u
#define RE_QUERY_BLOCK_COUNT 3u

typedef struct re_query_block_t {
    char *name;
    size_t name_size;
    char *goal;
    size_t goal_size;
    int strategy;            /* RE_QUERY_STRATEGY_* */
    size_t max_depth;
    size_t max_solutions;
    int enable_memoization;
    int enable_optimization; /* parsed, documented no-op */
    re_expr_t *when;
    re_query_action_stmt_t *actions[RE_QUERY_BLOCK_COUNT];
    size_t action_counts[RE_QUERY_BLOCK_COUNT];
} re_query_block_t;

struct re_program_t {
    re_allocator_impl_t allocator;
    re_limits_t limits;
    char *source;
    size_t source_size;
    re_rule_t *rules;
    size_t rule_count;
    char *module_focus;
    char *agenda_focus;
    /* B4 agenda focus stack (upstream rete/agenda.rs AdvancedAgenda
     * focus_stack): saved previous focuses, top of stack last. Program
     * state exactly like agenda_focus - it survives run exits (persistent
     * agenda runs included) and dies with the program. Only real group
     * names are stacked; the no-focus (NULL) state is never saved, so the
     * static pre-set focus is the bottom of stack the pops return to.
     * Bounded by RE_AGENDA_FOCUS_STACK_MAX. */
    char **agenda_focus_stack;
    size_t agenda_focus_stack_count;
    int64_t clock_epoch;
    int has_clock;
    re_module_t *modules;
    size_t module_count;
    re_deffacts_set_t *deffacts_sets;
    size_t deffacts_set_count;
    re_query_block_t *queries;
    size_t query_count;
    re_ir_program_t *ir;
};

re_status_t re_accumulator_evaluate(re_accumulator_kind_t kind, const re_value_t *values, size_t count, re_value_t *out);
re_status_t re_ir_match_rule(const re_engine_t *engine, re_facts_t *facts,
                             const re_ir_program_t *ir, size_t rule_index, int *matched);
/* A7: evaluates an arbitrary IR condition expression against current facts
 * (the query-block when-gate). RE_STATUS_NOT_FOUND reports a referenced fact
 * that does not resolve; callers treat it as not-matched, mirroring
 * re_ir_match_rule's contract with engine.c. */
re_status_t re_ir_match_expr(const re_engine_t *engine, re_facts_t *facts,
                             const re_ir_program_t *ir, size_t expr_index, int *matched);
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
/* Scratch storage owning the strings produced by `+` concatenation during
 * term resolution. The caller passes a zero-initialized scratch to
 * re_ir_resolve_term, consumes the resolved value (fact writes deep-copy
 * strings), then releases the scratch. Condition matching frees its own
 * scratch internally; only values escaping through re_ir_resolve_term need
 * the caller-owned form. */
typedef struct re_eval_scratch_t {
    char **items;
    size_t count;
    size_t capacity;
} re_eval_scratch_t;
void re_eval_scratch_destroy(const re_engine_t *engine, re_eval_scratch_t *scratch);
/* Takes ownership of an owned string produced during evaluation (concat or a
 * string-producing built-in result). On a non-OK return the caller keeps
 * ownership. */
re_status_t re_eval_scratch_own(const re_engine_t *engine, re_eval_scratch_t *scratch, char *owned);
re_status_t re_ir_resolve_term(re_engine_t *engine, re_facts_t *facts,
                               const re_ir_program_t *ir, size_t term_index,
                               re_value_t *value, re_eval_scratch_t *scratch);
re_status_t re_program_set_module_focus(re_program_t *program, re_string_t module);
re_status_t re_program_set_agenda_focus(re_program_t *program, re_string_t group);
/* B4 focus stack bound: pushes past the cap discard the saved previous
 * focus (the focus switch itself still happens), mirroring the codebase's
 * silent-truncation bounds (RE_IR_MAX_READ_PATHS). */
#define RE_AGENDA_FOCUS_STACK_MAX 32u
/* Upstream AdvancedAgenda::set_focus: switches program->agenda_focus to
 * group, saving the current focus on the stack (a no-op when group already
 * is the focus). The no-focus (NULL) state is never stacked. */
re_status_t re_program_push_agenda_focus(re_program_t *program, re_string_t group);
/* Upstream AdvancedAgenda::get_next_activation stack pop: restores the most
 * recent saved focus. Returns 1 on a restore, 0 when the stack is empty -
 * the focus then stays on the exhausted group, exactly like upstream's
 * `self.focus = self.focus_stack.pop()?` leaves it. */
int re_program_pop_agenda_focus(re_program_t *program);
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

/* Shared proof graph (Tasks 14 + B2): an engine-owned cache of final
 * backward-query results, consulted in re_backward_machine_dispatch AFTER
 * option normalization, keyed on the exact goal text, the facts identity,
 * the normalized search options (max_depth, max_solutions, strategy), the
 * engine config serial, and the facts mutation generation - so cached
 * results equal the final strategy/NOT-resolved results. Only
 * RE_QUERY_PROVED and RE_QUERY_DISPROVED results are stored; LIMIT and
 * UNKNOWN are never cached. The facts identity is pointer plus nonce, so
 * a new facts object reusing a destroyed one's address never aliases a
 * live entry (ABA). When the table is full the store path clears every
 * entry (documented clear-all eviction).
 *
 * B2 gives the cache the upstream proof graph's node shape
 * (proof_graph.rs): an entry is keyed by the exact goal text - the local
 * FactKey (upstream parses Type.field; the whole normalized goal is a
 * strictly finer key, so textual variants simply cache separately) - and
 * carries one node record per cached proof (the derivation's trace root
 * as its rule name) plus the producing run's premise set as the
 * justification's premise keys. The generation check stays the fast
 * path; on a serial mismatch the entry is re-validated per premise
 * (presence plus value fingerprint re-resolved against the live facts),
 * so a mutation of facts the derivation never read leaves the entry VALID
 * and its generation is refreshed onto the fast path. A premise flip
 * unlinks the entry (upstream lookup_by_key filters invalid nodes; the
 * local cache unlinks them) and counts an invalidation. Dependent
 * propagation is the validation scan itself: entries naming a retracted
 * derived fact in their premises find it absent - TMS cascades route
 * through re_facts_retract, so cascade removals are covered. Entries
 * marked opaque (a user function ran mid-proof, or the premise cap
 * overflowed) keep the pre-B2 coarse semantics: any serial move
 * invalidates them. */
#define RE_PROOF_GRAPH_CAPACITY 64u

/* One cached derivation of the goal (parallel to the entry's proofs). */
typedef struct re_proof_graph_node_t {
    char *rule_name; /* owned: trace root of the derivation (the node key) */
    size_t rule_name_size;
    int valid; /* entries are unlinked on invalidation; live nodes read 1 */
} re_proof_graph_node_t;

typedef struct re_proof_graph_entry_t {
    char *goal;
    size_t goal_size;
    re_facts_t *facts; /* identity only, not owned */
    uint64_t facts_nonce; /* facts->nonce at store time (ABA guard) */
    uint64_t generation; /* facts->mutation_serial at store/last validation */
    uint64_t config_serial; /* engine->config_serial at store time */
    size_t max_depth;
    size_t max_solutions;
    uint32_t strategy;
    re_query_result_t result;
    re_proof_t **proofs; /* cloned, owned */
    size_t proof_count;
    re_proof_graph_node_t *nodes; /* owned, parallel to proofs */
    size_t node_count;
    re_premise_set_t premises; /* the entry's justification premise keys */
} re_proof_graph_entry_t;

typedef struct re_proof_graph_t {
    re_allocator_impl_t allocator;
    re_proof_graph_entry_t entries[RE_PROOF_GRAPH_CAPACITY];
    size_t count;
    uint64_t hits;
    uint64_t misses;
    uint64_t invalidations; /* entries unlinked by per-premise invalidation */
    uint64_t stores; /* successful re_proof_graph_store calls */
    uint64_t evictions; /* entries dropped by the clear-all-on-full flush */
} re_proof_graph_t;

/* Fixed xorshift64 seed for the random() built-in (A4): nonzero by
 * construction; re_engine_create loads it into engine->random_state. */
#define RE_BUILTIN_RANDOM_SEED 0x9E3779B97F4A7C15ull

/* Sub-project C Task C5: the engine's stream registry (upstream
 * rust-rule-engine v1.21.4 f80a541 src/streaming/engine.rs StreamRuleEngine
 * window manager keyed by stream name). Name-keyed BORROWED window handles:
 * registration copies the name but never takes ownership of the window, and
 * re_engine_destroy releases the name copies only - destroying a registered
 * window stays the host's job (unregister first, or destroy it after the
 * engine). Bounded like every other engine roster (RE_PROOF_GRAPH_CAPACITY,
 * RE_AGENDA_FOCUS_STACK_MAX): registrations past the cap report
 * RE_STATUS_LIMIT. */
#define RE_STREAM_REGISTRY_CAP 16u

typedef struct re_stream_registry_entry_t {
    char *name; /* owned copy */
    size_t name_size;
    re_stream_window_t *window; /* borrowed; NOT destroyed with the engine */
} re_stream_registry_entry_t;

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
    /* A4: deterministic random() built-in state (xorshift64), seeded to
     * RE_BUILTIN_RANDOM_SEED at creation - every engine produces the same
     * sequence, so tests are stable; no public setter by design. Mutated
     * through a const cast in the built-in dispatch, under the same
     * single-threaded-handles contract as the rest of the engine. */
    uint64_t random_state;
    /* C5 stream registry: stream_registry_count leading entries of the fixed
     * array are live. Consulted by the stream-pattern CE evaluation
     * (ir_eval.c) and re_engine_stream_register/unregister (stream_eval.c). */
    re_stream_registry_entry_t stream_registry[RE_STREAM_REGISTRY_CAP];
    size_t stream_registry_count;
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

/* C5: looks up a registered stream by exact name; NULL when unregistered
 * (the caller maps that to the honest evaluation error). Implemented in
 * stream_eval.c; consumed by the stream-pattern CE evaluation in ir_eval.c. */
re_stream_window_t *re_engine_stream_lookup(const re_engine_t *engine,
                                            const char *name, size_t name_size);

/* Sub-project C Task C2: StreamAnalytics cache entry (upstream
 * HashMap<String, (u64, AggregationResult)>, f80a541
 * src/streaming/aggregator.rs:287). key/event_type are owned copies;
 * first_data/last_data back STRING values in the cached result's first/last
 * (deep-copied on insert so a cached result survives window mutation).
 * percentile is identity-relevant only for RE_STREAM_AGGREGATE_PERCENTILE. */
typedef struct re_stream_analytics_entry_t {
    char *key;
    size_t key_size;
    char *event_type;
    size_t event_type_size;
    char *first_data;
    char *last_data;
    uint64_t timestamp_ms;
    re_stream_aggregate_kind_t kind;
    double percentile;
    re_stream_aggregate_result_t result;
} re_stream_analytics_entry_t;

struct re_stream_analytics_t {
    re_allocator_impl_t allocator;
    uint64_t cache_ttl_ms;
    re_stream_analytics_entry_t *entries;
    size_t count;
    size_t capacity;
};

/* Sub-project C Task C4: cross-stream join internals (upstream
 * HashMap<String, VecDeque<StreamEvent>> per side, f80a541
 * src/rete/stream_join_node.rs:60-63). Bounds follow the codebase's
 * bounded-everything rule (documented on re_stream_join_record). */
#define RE_STREAM_JOIN_MAX_KEYS 256u
#define RE_STREAM_JOIN_PER_KEY_CAP 64u
#define RE_STREAM_JOIN_MATCH_CAP 256u

/* A buffered event: timestamp plus the matched flag that suppresses
 * outer-join unmatched emission (upstream's left_matched/right_matched id
 * maps, :65-68, mapped to per-event flags). Event payloads are not retained
 * (documented on re_stream_join_record). */
typedef struct re_stream_join_event_t {
    uint64_t timestamp_ms;
    int matched;
} re_stream_join_event_t;

typedef struct re_stream_join_key_entry_t {
    char *key; /* owned; also backs the key borrow of every queued match */
    size_t key_size;
    re_stream_join_event_t *events;
    size_t count;
    size_t capacity;
} re_stream_join_key_entry_t;

typedef struct re_stream_join_match_entry_t {
    const char *key; /* borrowed from the owning key entry (stable until destroy) */
    size_t key_size;
    uint64_t left_timestamp_ms; /* 0 when absent */
    uint64_t right_timestamp_ms; /* 0 when absent */
    uint64_t join_timestamp_ms;
} re_stream_join_match_entry_t;

struct re_stream_join_t {
    re_allocator_impl_t allocator;
    char *left_name; /* owned copies (upstream left_stream/right_stream, :51-54) */
    size_t left_name_size;
    char *right_name;
    size_t right_name_size;
    re_stream_join_type_t join_type;
    re_stream_join_strategy_t strategy;
    re_stream_join_key_entry_t *keys[2]; /* indexed by side - 1 */
    size_t key_count[2];
    size_t key_capacity[2];
    uint64_t watermark; /* single node watermark (upstream :69), monotonic */
    re_stream_join_match_entry_t *matches; /* FIFO drain queue, bounded */
    size_t match_count;
    size_t match_capacity;
    uint64_t dropped; /* silent drop-oldest counter (buffers + match queue) */
};

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
/* Records a premise-less, unconditionally-valid explicit support item for a
 * fact that also carries logical justifications (upstream tms.rs
 * JustificationType::Explicit). Idempotent. */
re_status_t re_tms_explicit_support_ensure(re_facts_t *facts, re_fact_id_t derived);
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
/* Built-in functions (builtins.c): the A3 condition family (upstream
 * condition_evaluator.rs): len/length/size, isEmpty/is_empty, contains,
 * exists/notExists/not_exists - and the A4 action/RHS utility family
 * (upstream engine.rs execute_function_call): log/print/println,
 * now/timestamp, random, format/sprintf, count, sum/add, max, min,
 * avg/average, round, floor, ceil, abs, includes, startswith, endswith,
 * lowercase, uppercase, trim, split, join. ir_eval.c consults them only
 * after the user function registry misses, so a registered function of the
 * same name overrides the built-in. */
int re_builtin_is(const char *name, size_t size);
/* Predicate built-ins (bool-returning) may appear bare as a whole condition,
 * meaning fn(...) == true (parser.c). */
int re_builtin_is_predicate(const char *name, size_t size);
/* The value a built-in yields when a bare fact-path argument fails to
 * resolve (absent fact): false, except the negated presence probes
 * (notExists/not_exists) whose missing path is their truth. */
int re_builtin_arg_miss_result(const char *name, size_t size);
/* A8 bare `name(args)` then-statement actions (retract/log/
 * ActivateAgendaGroup/ScheduleRule/CompleteWorkflow/SetWorkflowData);
 * consulted by parser.c, ir_validate.c and engine.c. */
int re_builtin_action_is(const char *name, size_t size);
/* arg_fact_paths[i] holds the binding-rewritten path of bare fact-path
 * arguments ({NULL, 0} otherwise); may be NULL when argc is 0. scratch owns
 * the result strings produced by the string-returning built-ins (the caller
 * releases it). Returns RE_STATUS_NOT_FOUND when name is not a built-in. */
re_status_t re_builtin_call(re_engine_t *engine, re_facts_t *facts, re_string_t name,
                            const re_value_t *args, const re_string_t *arg_fact_paths,
                            size_t argc, re_value_t *out, re_eval_scratch_t *scratch);
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
 * live entry (clone its proofs before storing anything else). A serial
 * mismatch triggers per-premise re-validation: entries whose premises all
 * still hold survive with their generation refreshed; the rest are
 * unlinked and counted as a miss plus an invalidation. */
re_status_t re_proof_graph_lookup(re_proof_graph_t *graph, re_facts_t *facts,
                                   re_string_t goal, const re_query_options_t *options,
                                   uint64_t config_serial,
                                   const re_proof_graph_entry_t **out_entry);
/* Clones the proofs, their node records, and the premise set into a new
 * entry; clears all entries when full. premises may be NULL (empty set). */
re_status_t re_proof_graph_store(re_proof_graph_t *graph, re_facts_t *facts,
                                  re_string_t goal, const re_query_options_t *options,
                                  uint64_t config_serial, re_query_result_t result,
                                  re_proof_t *const *proofs, size_t proof_count,
                                  const re_premise_set_t *premises);

/* B2 premise-set plumbing (proof_graph.c): a typed value fingerprint for
 * premise equality, plus record (deduped, capped), merge, and destroy for
 * the bounded premise sets captured during backward runs. */
uint64_t re_value_fingerprint(const re_value_t *value);
void re_premise_set_destroy(const re_allocator_impl_t *allocator, re_premise_set_t *set);
re_status_t re_premise_set_record(const re_allocator_impl_t *allocator, re_premise_set_t *set,
                                  re_string_t path, int present, uint64_t fingerprint);
re_status_t re_premise_set_merge(const re_allocator_impl_t *allocator, re_premise_set_t *target,
                                 const re_premise_set_t *source);

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
