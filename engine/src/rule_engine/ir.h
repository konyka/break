#ifndef BREAK_RULE_ENGINE_IR_H
#define BREAK_RULE_ENGINE_IR_H

#include "re_internal.h"

typedef uint64_t re_ir_id_t;
typedef struct re_ir_span_t { size_t start; size_t end; } re_ir_span_t;
typedef enum re_ir_term_kind_t {
    RE_IR_TERM_NONE, RE_IR_TERM_BOOL, RE_IR_TERM_INT64, RE_IR_TERM_DOUBLE,
    RE_IR_TERM_STRING, RE_IR_TERM_FACT, RE_IR_TERM_FUNCTION, RE_IR_TERM_GOAL,
    RE_IR_TERM_ARITHMETIC, RE_IR_TERM_ARRAY
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
} re_ir_expr_t;
typedef struct re_ir_action_t {
    re_ir_id_t id;
    size_t target;
    size_t value;
    int append;
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
    re_ir_span_t span;
} re_ir_rule_t;
typedef struct re_ir_module_t {
    re_ir_id_t id;
    size_t name;
    size_t first_import;
    size_t import_count;
    int export_all;
} re_ir_module_t;
typedef struct re_ir_program_t {
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
    re_ir_span_t *spans;
    size_t span_count;
} re_ir_program_t;

re_status_t re_ir_compile(const re_program_t *program, re_ir_program_t **out);
re_status_t re_ir_validate(const re_ir_program_t *ir);
void re_ir_destroy(re_ir_program_t *ir);

#endif
