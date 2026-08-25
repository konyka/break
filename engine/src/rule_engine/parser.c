#include "re_internal.h"
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct parser_t { const char *text; size_t size; size_t at; const re_allocator_impl_t *allocator; } parser_t;
static void skip_space(parser_t *p) { while (p->at < p->size && isspace((unsigned char)p->text[p->at])) ++p->at; }
static int take(parser_t *p, char c) { skip_space(p); if (p->at < p->size && p->text[p->at] == c) { ++p->at; return 1; } return 0; }
static int word(parser_t *p, const char *word) {
    size_t n = strlen(word); skip_space(p);
    if (n <= p->size - p->at && memcmp(p->text + p->at, word, n) == 0 &&
        (n == p->size - p->at || !isalnum((unsigned char)p->text[p->at + n]))) { p->at += n; return 1; }
    return 0;
}
static re_status_t quoted(parser_t *p, char **out, size_t *out_size) {
    size_t start; if (!take(p, '"')) return RE_STATUS_PARSE_ERROR; start = p->at;
    while (p->at < p->size && p->text[p->at] != '"') ++p->at;
    if (p->at == p->size) return RE_STATUS_PARSE_ERROR;
    *out_size = p->at - start;
    { re_status_t status = re_copy_string(p->allocator, (re_string_t){p->text + start, *out_size}, out);
      if (status != RE_STATUS_OK) return status; }
    ++p->at; return RE_STATUS_OK;
}
static re_status_t operand(parser_t *p, re_operand_t *out) {
    size_t start; char *end; double number; int negative = 0; int has_dot = 0;
    memset(out, 0, sizeof(*out)); skip_space(p);
    if (p->at >= p->size) return RE_STATUS_PARSE_ERROR;
    if (p->text[p->at] == '"') {
        out->kind = RE_OPERAND_LITERAL; out->value.type = RE_VALUE_STRING;
        return quoted(p, (char **)&out->value.as.string.data, &out->value.as.string.size);
    }
    if (word(p, "true")) {
        out->kind = RE_OPERAND_LITERAL; out->value.type = RE_VALUE_BOOL;
        out->value.as.boolean = 1; return RE_STATUS_OK;
    }
    if (word(p, "false")) {
        out->kind = RE_OPERAND_LITERAL; out->value.type = RE_VALUE_BOOL;
        out->value.as.boolean = 0; return RE_STATUS_OK;
    }
    start = p->at; if (p->text[p->at] == '-') { negative = 1; ++p->at; }
    while (p->at < p->size && (isdigit((unsigned char)p->text[p->at]) || p->text[p->at] == '.')) {
        if (p->text[p->at] == '.') has_dot = 1;
        ++p->at;
    }
    if (p->at > start + (negative ? 1u : 0u)) {
        errno = 0;
        if (has_dot) {
            number = strtod(p->text + start, &end);
            if (errno == ERANGE || !isfinite(number) || (size_t)(end - p->text) != p->at)
                return RE_STATUS_PARSE_ERROR;
            out->kind = RE_OPERAND_LITERAL; out->value.type = RE_VALUE_DOUBLE;
            out->value.as.double_value = number;
        } else {
            long long integer = strtoll(p->text + start, &end, 10);
            if (errno == ERANGE || (size_t)(end - p->text) != p->at)
                return RE_STATUS_PARSE_ERROR;
            out->kind = RE_OPERAND_LITERAL; out->value.type = RE_VALUE_INT64;
            out->value.as.int64_value = (int64_t)integer;
        }
        return RE_STATUS_OK;
    }
    p->at = start; while (p->at < p->size && (isalnum((unsigned char)p->text[p->at]) || p->text[p->at] == '.' || p->text[p->at] == '_')) ++p->at;
    if (p->at == start) return RE_STATUS_PARSE_ERROR;
    out->kind = RE_OPERAND_FACT; out->fact_name_size = p->at - start;
    return re_copy_string(p->allocator, (re_string_t){p->text + start, out->fact_name_size}, &out->fact_name);
}
static re_status_t comparison(parser_t *p, re_compare_t *out) {
    skip_space(p);
    if (p->at + 1u < p->size && p->text[p->at] == '=' && p->text[p->at + 1u] == '=') { p->at += 2u; *out = RE_COMPARE_EQ; return RE_STATUS_OK; }
    if (p->at + 1u < p->size && p->text[p->at] == '!' && p->text[p->at + 1u] == '=') { p->at += 2u; *out = RE_COMPARE_NE; return RE_STATUS_OK; }
    if (p->at + 1u < p->size && p->text[p->at + 1u] == '=') { if (p->text[p->at] == '>') *out = RE_COMPARE_GE; else if (p->text[p->at] == '<') *out = RE_COMPARE_LE; else return RE_STATUS_PARSE_ERROR; p->at += 2u; return RE_STATUS_OK; }
    if (p->at >= p->size) return RE_STATUS_PARSE_ERROR;
    if (p->text[p->at] == '>') { ++p->at; *out = RE_COMPARE_GT; return RE_STATUS_OK; }
    if (p->text[p->at] == '<') { ++p->at; *out = RE_COMPARE_LT; return RE_STATUS_OK; }
    return RE_STATUS_PARSE_ERROR;
}
static void rule_destroy(const re_allocator_impl_t *a, re_rule_t *r) { re_free(a, r->name); re_free(a, r->action_name); re_operand_destroy(a, &r->left); re_operand_destroy(a, &r->right); re_operand_destroy(a, &r->action_value); }

re_status_t re_program_load(const re_allocator_t *allocator, re_string_t source, const re_limits_t *limits, re_program_t **out_program) {
    re_allocator_impl_t a; re_program_t *program; parser_t p; size_t capacity = 0u;
    if (out_program == NULL || source.data == NULL) return RE_STATUS_INVALID_ARGUMENT; *out_program = NULL;
    re_allocator_init(&a, allocator); if (a.api.alloc == NULL || a.api.realloc == NULL || a.api.free == NULL) return RE_STATUS_INVALID_ARGUMENT;
    program = re_alloc(&a, sizeof(*program)); if (program == NULL) return RE_STATUS_OUT_OF_MEMORY;
    memset(program, 0, sizeof(*program)); program->allocator = a; program->limits = limits != NULL ? *limits : re_default_limits();
    if (program->limits.max_source_bytes != 0u && source.size > program->limits.max_source_bytes) { re_free(&a, program); return RE_STATUS_LIMIT; }
    { re_status_t status = re_copy_string(&a, source, &program->source);
      if (status != RE_STATUS_OK) { re_free(&a, program); return status; } }
    program->source_size = source.size;
    p.text = program->source; p.size = program->source_size; p.at = 0u; p.allocator = &a;
    while (p.at < p.size) {
        re_rule_t rule; re_operand_t action_target; memset(&rule, 0, sizeof(rule)); memset(&action_target, 0, sizeof(action_target)); rule.source_order = program->rule_count;
        if (program->limits.max_rules != 0u && program->rule_count >= program->limits.max_rules) { re_program_destroy(program); return RE_STATUS_LIMIT; }
        { re_status_t status = RE_STATUS_OK;
          if (!word(&p, "rule")) status = RE_STATUS_PARSE_ERROR;
          if (status == RE_STATUS_OK) status = quoted(&p, &rule.name, &rule.name_size);
          if (status == RE_STATUS_OK && !take(&p, '{')) status = RE_STATUS_PARSE_ERROR;
          if (status == RE_STATUS_OK && !word(&p, "when")) status = RE_STATUS_PARSE_ERROR;
          if (status != RE_STATUS_OK) { rule_destroy(&a, &rule); re_program_destroy(program); return status; } }
        if (word(&p, "true")) { rule.compare = RE_COMPARE_TRUE; memset(&rule.left, 0, sizeof(rule.left)); }
        else { re_status_t status = operand(&p, &rule.left);
          if (status == RE_STATUS_OK) status = comparison(&p, &rule.compare);
          if (status == RE_STATUS_OK) status = operand(&p, &rule.right);
          if (status != RE_STATUS_OK) { rule_destroy(&a, &rule); re_program_destroy(program); return status; } }
        { re_status_t status = RE_STATUS_OK;
          if (!word(&p, "then")) status = RE_STATUS_PARSE_ERROR;
          if (status == RE_STATUS_OK) status = operand(&p, &action_target);
          if (status == RE_STATUS_OK && action_target.kind != RE_OPERAND_FACT) status = RE_STATUS_PARSE_ERROR;
          if (status == RE_STATUS_OK && !take(&p, '=')) status = RE_STATUS_PARSE_ERROR;
          if (status == RE_STATUS_OK) status = operand(&p, &rule.action_value);
          if (status != RE_STATUS_OK) { re_operand_destroy(&a, &action_target); rule_destroy(&a, &rule); re_program_destroy(program); return status; } }
        rule.action_name = action_target.fact_name; rule.action_name_size = action_target.fact_name_size; memset(&action_target, 0, sizeof(action_target));
        if (!take(&p, ';') || !take(&p, '}')) { re_operand_destroy(&a, &action_target); rule_destroy(&a, &rule); re_program_destroy(program); return RE_STATUS_PARSE_ERROR; }
        if (program->rule_count == capacity) { size_t next;
            if (capacity != 0u && capacity > (size_t)-1 / 2u) { rule_destroy(&a, &rule); re_program_destroy(program); return RE_STATUS_LIMIT; }
            next = capacity == 0u ? 4u : capacity * 2u;
            if (next > (size_t)-1 / sizeof(*program->rules)) { rule_destroy(&a, &rule); re_program_destroy(program); return RE_STATUS_LIMIT; }
            { re_rule_t *grown = re_realloc(&a, program->rules, next * sizeof(*grown)); if (grown == NULL) { rule_destroy(&a, &rule); re_program_destroy(program); return RE_STATUS_OUT_OF_MEMORY; } program->rules = grown; capacity = next; } }
        program->rules[program->rule_count++] = rule; skip_space(&p);
    }
    *out_program = program; return RE_STATUS_OK;
}

void re_program_destroy(re_program_t *program) { size_t i; if (program == NULL) return; for (i = 0u; i < program->rule_count; ++i) rule_destroy(&program->allocator, &program->rules[i]); re_free(&program->allocator, program->rules); re_free(&program->allocator, program->source); re_free(&program->allocator, program); }
