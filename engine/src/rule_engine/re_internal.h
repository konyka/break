#ifndef BREAK_RE_INTERNAL_H
#define BREAK_RE_INTERNAL_H

#include "rule_engine/rule_engine.h"
#include <stddef.h>

typedef struct re_allocator_impl_t {
    re_allocator_t api;
} re_allocator_impl_t;

typedef struct re_fact_entry_t {
    char *name;
    size_t name_size;
    re_value_t value;
    char *string_data;
} re_fact_entry_t;

struct re_facts_t {
    re_allocator_impl_t allocator;
    re_limits_t limits;
    re_fact_entry_t *entries;
    size_t count;
    size_t capacity;
    int running;
    int destroy_requested;
};

typedef enum re_operand_kind_t { RE_OPERAND_LITERAL, RE_OPERAND_FACT } re_operand_kind_t;
typedef struct re_operand_t {
    re_operand_kind_t kind;
    re_value_t value;
    char *fact_name;
    size_t fact_name_size;
} re_operand_t;

typedef enum re_compare_t { RE_COMPARE_TRUE, RE_COMPARE_EQ, RE_COMPARE_NE, RE_COMPARE_GT,
    RE_COMPARE_GE, RE_COMPARE_LT, RE_COMPARE_LE } re_compare_t;
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
    size_t source_order;
} re_rule_t;

struct re_program_t {
    re_allocator_impl_t allocator;
    re_limits_t limits;
    char *source;
    size_t source_size;
    re_rule_t *rules;
    size_t rule_count;
};

struct re_engine_t {
    re_allocator_impl_t allocator;
    re_limits_t limits;
    re_program_t *program;
    int running;
    int destroy_requested;
};

void *re_alloc(const re_allocator_impl_t *allocator, size_t size);
void *re_realloc(const re_allocator_impl_t *allocator, void *memory, size_t size);
void re_free(const re_allocator_impl_t *allocator, void *memory);
void re_allocator_init(re_allocator_impl_t *target, const re_allocator_t *source);
re_limits_t re_default_limits(void);
re_status_t re_copy_string(const re_allocator_impl_t *allocator, re_string_t input, char **out);
void re_operand_destroy(const re_allocator_impl_t *allocator, re_operand_t *operand);
re_status_t re_operand_copy(const re_allocator_impl_t *allocator, const re_operand_t *source,
                            re_operand_t *target);
re_status_t re_facts_resolve(const re_facts_t *facts, re_string_t name, re_value_t *out);
int re_value_compare(const re_value_t *left, const re_value_t *right, re_compare_t compare);

#endif
