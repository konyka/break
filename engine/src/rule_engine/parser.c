#include "re_internal.h"
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct parser_t { const char *text; size_t size; size_t at; const re_allocator_impl_t *allocator; } parser_t;
void re_expr_destroy(const re_allocator_impl_t *a, re_expr_t *expr) { if (expr == NULL) return; re_operand_destroy(a, &expr->left); re_operand_destroy(a, &expr->right); re_expr_destroy(a, expr->first); re_expr_destroy(a, expr->second); re_free(a, expr); }
static void skip_space(parser_t *p) { while (p->at < p->size && isspace((unsigned char)p->text[p->at])) ++p->at; }
static int take(parser_t *p, char c) { skip_space(p); if (p->at < p->size && p->text[p->at] == c) { ++p->at; return 1; } return 0; }
static int word(parser_t *p, const char *word) {
    size_t n = strlen(word); skip_space(p);
    if (n <= p->size - p->at && memcmp(p->text + p->at, word, n) == 0 &&
        (n == p->size - p->at || !isalnum((unsigned char)p->text[p->at + n]))) { p->at += n; return 1; }
    return 0;
}

static re_status_t int32_literal(parser_t *p, int32_t *out) {
    uint64_t magnitude = 0u;
    size_t digits = 0u;
    int negative = 0;

    skip_space(p);
    if (p->at < p->size && p->text[p->at] == '-') {
        negative = 1;
        ++p->at;
    } else if (p->at < p->size && p->text[p->at] == '+') {
        ++p->at;
    }
    while (p->at < p->size && isdigit((unsigned char)p->text[p->at])) {
        uint32_t digit = (uint32_t)(p->text[p->at] - '0');
        if (magnitude > (UINT64_MAX - digit) / 10u) {
            return RE_STATUS_PARSE_ERROR;
        }
        magnitude = magnitude * 10u + digit;
        ++p->at;
        ++digits;
    }
    if (digits == 0u || (p->at < p->size &&
                         (isalnum((unsigned char)p->text[p->at]) ||
                          p->text[p->at] == '_'))) {
        return RE_STATUS_PARSE_ERROR;
    }
    if ((!negative && magnitude > (uint64_t)INT32_MAX) ||
        (negative && magnitude > (uint64_t)INT32_MAX + 1u)) {
        return RE_STATUS_PARSE_ERROR;
    }
    if (out != NULL) {
        if (negative && magnitude == (uint64_t)INT32_MAX + 1u) {
            *out = INT32_MIN;
        } else {
            *out = negative ? -(int32_t)magnitude : (int32_t)magnitude;
        }
    }
    return RE_STATUS_OK;
}
static re_status_t quoted(parser_t *p, char **out, size_t *out_size) {
    size_t start; size_t length = 0u; char *copy;
    if (!take(p, '"')) return RE_STATUS_PARSE_ERROR; start = p->at;
    while (p->at < p->size && p->text[p->at] != '"') {
        if (p->text[p->at] == '\\' && p->at + 1u < p->size) p->at += 2u;
        else ++p->at;
        ++length;
    }
    if (p->at == p->size) return RE_STATUS_PARSE_ERROR;
    copy = re_alloc(p->allocator, length + 1u); if (copy == NULL) return RE_STATUS_OUT_OF_MEMORY;
    { size_t i = start, j = 0u; while (i < p->at) { if (p->text[i] == '\\' && i + 1u < p->at) ++i; copy[j++] = p->text[i++]; } copy[j] = '\0'; }
    *out = copy; *out_size = length;
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
    if (p->at < p->size && p->text[p->at] == '(') {
        size_t capacity = 0u;
        out->kind = RE_OPERAND_FUNCTION;
        out->function_name_size = p->at - start;
        if (re_copy_string(p->allocator, (re_string_t){p->text + start, out->function_name_size}, &out->function_name) != RE_STATUS_OK)
            return RE_STATUS_OUT_OF_MEMORY;
        ++p->at;
        skip_space(p);
        while (p->at < p->size && p->text[p->at] != ')') {
            re_operand_t argument;
            re_status_t status = operand(p, &argument);
            if (status != RE_STATUS_OK) { re_operand_destroy(p->allocator, out); return status; }
            if (out->argument_count == capacity) {
                size_t next = capacity == 0u ? 2u : capacity * 2u;
                re_operand_t *grown = re_realloc(p->allocator, out->arguments, next * sizeof(*grown));
                if (grown == NULL) { re_operand_destroy(p->allocator, &argument); re_operand_destroy(p->allocator, out); return RE_STATUS_OUT_OF_MEMORY; }
                out->arguments = grown; capacity = next;
            }
            out->arguments[out->argument_count++] = argument;
            if (!take(p, ',')) break;
        }
        if (!take(p, ')')) { re_operand_destroy(p->allocator, out); return RE_STATUS_PARSE_ERROR; }
        return RE_STATUS_OK;
    }
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
static re_status_t expression(parser_t *p, re_expr_t **out);
static re_status_t primary(parser_t *p, re_expr_t **out) {
    re_expr_t *expr = re_alloc(p->allocator, sizeof(*expr)); if (expr == NULL) return RE_STATUS_OUT_OF_MEMORY; memset(expr, 0, sizeof(*expr));
    if (take(p, '(')) { re_status_t s = expression(p, &expr->first); if (s == RE_STATUS_OK && !take(p, ')')) s = RE_STATUS_PARSE_ERROR; if (s != RE_STATUS_OK) { re_expr_destroy(p->allocator, expr); return s; } *out = expr->first; re_free(p->allocator, expr); return RE_STATUS_OK; }
    if (word(p, "true")) { expr->kind = RE_EXPR_TRUE; *out = expr; return RE_STATUS_OK; }
    if (word(p, "false")) { expr->kind = RE_EXPR_FALSE; *out = expr; return RE_STATUS_OK; }
    if (word(p, "not")) { expr->kind = RE_EXPR_NOT; if (primary(p, &expr->first) != RE_STATUS_OK) { re_expr_destroy(p->allocator, expr); return RE_STATUS_PARSE_ERROR; } *out = expr; return RE_STATUS_OK; }
    expr->kind = RE_EXPR_COMPARE; if (operand(p, &expr->left) != RE_STATUS_OK || comparison(p, &expr->compare) != RE_STATUS_OK || operand(p, &expr->right) != RE_STATUS_OK) { re_expr_destroy(p->allocator, expr); return RE_STATUS_PARSE_ERROR; } *out = expr; return RE_STATUS_OK;
}
static re_status_t expression(parser_t *p, re_expr_t **out) {
    re_expr_t *left; if (primary(p, &left) != RE_STATUS_OK) return RE_STATUS_PARSE_ERROR;
    for (;;) { int is_and = word(p, "and"); int is_or = !is_and && word(p, "or"); re_expr_t *right; re_expr_t *joined;
        if (!is_and && !is_or) break; if (primary(p, &right) != RE_STATUS_OK) { re_expr_destroy(p->allocator, left); return RE_STATUS_PARSE_ERROR; }
        joined = re_alloc(p->allocator, sizeof(*joined)); if (joined == NULL) { re_expr_destroy(p->allocator, left); re_expr_destroy(p->allocator, right); return RE_STATUS_OUT_OF_MEMORY; } memset(joined, 0, sizeof(*joined)); joined->kind = is_and ? RE_EXPR_AND : RE_EXPR_OR; joined->first = left; joined->second = right; left = joined;
    } *out = left; return RE_STATUS_OK;
}
static re_status_t rule_attributes(parser_t *p, re_rule_t *rule) {
    int seen_salience = 0;
    int seen_agenda = 0;
    int seen_activation = 0;
    int seen_no_loop = 0;
    int seen_lock = 0;
    for (;;) {
        if (word(p, "date-effective") || word(p, "date-expires")) {
            int expiry = p->at >= 7u && memcmp(p->text + p->at - 7u, "expires", 6u) == 0;
            char **target = expiry ? &rule->expiry_date : &rule->effective_date;
            size_t ignored_size = 0u;
            int64_t parsed_date;
            if (*target != NULL || quoted(p, target, &ignored_size) != RE_STATUS_OK ||
                !re_parse_date(*target, &parsed_date)) return RE_STATUS_PARSE_ERROR;
        } else
        if (word(p, "salience")) {
            re_operand_t value;
            memset(&value, 0, sizeof(value));
            if (seen_salience || operand(p, &value) != RE_STATUS_OK ||
                value.kind != RE_OPERAND_LITERAL || value.value.type != RE_VALUE_INT64) {
                re_operand_destroy(p->allocator, &value);
                return RE_STATUS_PARSE_ERROR;
            }
            rule->salience = (int32_t)value.value.as.int64_value;
            seen_salience = 1;
        } else if (word(p, "agenda-group")) {
            size_t ignored_size = 0u;
            if (seen_agenda || quoted(p, &rule->agenda_group, &ignored_size) != RE_STATUS_OK) return RE_STATUS_PARSE_ERROR;
            seen_agenda = 1;
        } else if (word(p, "activation-group")) {
            size_t ignored_size = 0u;
            if (seen_activation || quoted(p, &rule->activation_group, &ignored_size) != RE_STATUS_OK) return RE_STATUS_PARSE_ERROR;
            seen_activation = 1;
        } else if (word(p, "no-loop")) {
            if (seen_no_loop) return RE_STATUS_PARSE_ERROR;
            if (word(p, "true")) rule->no_loop = 1;
            else if (!word(p, "false")) return RE_STATUS_PARSE_ERROR;
            seen_no_loop = 1;
        } else if (word(p, "lock-on-active")) {
            if (seen_lock) return RE_STATUS_PARSE_ERROR;
            if (word(p, "true")) rule->lock_on_active = 1;
            else if (!word(p, "false")) return RE_STATUS_PARSE_ERROR;
            seen_lock = 1;
        } else {
            return RE_STATUS_OK;
        }
        if (!take(p, ';')) return RE_STATUS_PARSE_ERROR;
    }
}
static void rule_destroy(const re_allocator_impl_t *a, re_rule_t *r) { size_t i; re_free(a, r->name); re_free(a, r->agenda_group); re_free(a, r->activation_group); re_free(a, r->effective_date); re_free(a, r->expiry_date); re_operand_destroy(a, &r->left); re_operand_destroy(a, &r->right); re_operand_destroy(a, &r->action_value); re_expr_destroy(a, r->condition); for (i = 0u; i < r->action_count; ++i) { re_free(a, r->actions[i].name); re_operand_destroy(a, &r->actions[i].value); } re_free(a, r->actions); }
static void modules_destroy(const re_allocator_impl_t *a, re_program_t *p) { size_t i, j; for (i = 0u; i < p->module_count; ++i) { re_free(a, p->modules[i].name); for (j = 0u; j < p->modules[i].import_count; ++j) re_free(a, p->modules[i].imports[j]); re_free(a, p->modules[i].imports); } re_free(a, p->modules); }
static int find_module(const re_program_t *p, re_string_t name, size_t *index) { size_t i; for (i = 0u; i < p->module_count; ++i) if (p->modules[i].name_size == name.size && memcmp(p->modules[i].name, name.data, name.size) == 0) { *index = i; return 1; } return 0; }
static re_status_t add_module(const re_allocator_impl_t *a, re_program_t *p, re_string_t name, size_t *index) { re_module_t *grown; if (find_module(p, name, index)) return RE_STATUS_PARSE_ERROR; grown = re_realloc(a, p->modules, (p->module_count + 1u) * sizeof(*grown)); if (grown == NULL) return RE_STATUS_OUT_OF_MEMORY; p->modules = grown; memset(&p->modules[p->module_count], 0, sizeof(*grown)); if (re_copy_string(a, name, &p->modules[p->module_count].name) != RE_STATUS_OK) return RE_STATUS_OUT_OF_MEMORY; p->modules[p->module_count].name_size = name.size; *index = p->module_count++; return RE_STATUS_OK; }
static re_status_t add_import(const re_allocator_impl_t *a, re_module_t *m, re_string_t name) { char **grown = re_realloc(a, m->imports, (m->import_count + 1u) * sizeof(*grown)); if (grown == NULL) return RE_STATUS_OUT_OF_MEMORY; m->imports = grown; if (re_copy_string(a, name, &m->imports[m->import_count]) != RE_STATUS_OK) return RE_STATUS_OUT_OF_MEMORY; ++m->import_count; return RE_STATUS_OK; }
static int module_cycle(const re_program_t *p, size_t current, size_t target, unsigned char *path) { size_t i, next; if (current == target) return 1; if (path[current]) return 0; path[current] = 1u; for (i = 0u; i < p->modules[current].import_count; ++i) { re_string_t name = {p->modules[current].imports[i], strlen(p->modules[current].imports[i])}; if (find_module(p, name, &next) && module_cycle(p, next, target, path)) return 1; } path[current] = 0u; return 0; }
static re_status_t validate_modules(const re_allocator_impl_t *a, re_program_t *p) { size_t i, j, imported; unsigned char *path; path = p->module_count == 0u ? NULL : re_alloc(a, p->module_count); if (p->module_count != 0u && path == NULL) return RE_STATUS_OUT_OF_MEMORY; for (i = 0u; i < p->module_count; ++i) for (j = 0u; j < p->modules[i].import_count; ++j) { re_string_t name = {p->modules[i].imports[j], strlen(p->modules[i].imports[j])}; if (!find_module(p, name, &imported)) { re_free(a, path); return RE_STATUS_PARSE_ERROR; } } for (i = 0u; i < p->module_count; ++i) for (j = 0u; j < p->modules[i].import_count; ++j) { re_string_t name = {p->modules[i].imports[j], strlen(p->modules[i].imports[j])}; (void)find_module(p, name, &imported); memset(path, 0, p->module_count); if (module_cycle(p, imported, i, path) && imported != i) { re_free(a, path); return RE_STATUS_PARSE_ERROR; } } re_free(a, path); return RE_STATUS_OK; }

re_status_t re_program_load(const re_allocator_t *allocator, re_string_t source, const re_limits_t *limits, re_program_t **out_program) {
    re_allocator_impl_t a; re_program_t *program; parser_t p; size_t capacity = 0u;
    if (out_program == NULL || source.data == NULL) return RE_STATUS_INVALID_ARGUMENT;
    *out_program = NULL;
    re_allocator_init(&a, allocator); if (a.api.alloc == NULL || a.api.realloc == NULL || a.api.free == NULL) return RE_STATUS_INVALID_ARGUMENT;
    program = re_alloc(&a, sizeof(*program)); if (program == NULL) return RE_STATUS_OUT_OF_MEMORY;
    memset(program, 0, sizeof(*program)); program->allocator = a; program->limits = limits != NULL ? *limits : re_default_limits();
    if (program->limits.max_source_bytes != 0u && source.size > program->limits.max_source_bytes) { re_free(&a, program); return RE_STATUS_LIMIT; }
    { re_status_t status = re_copy_string(&a, source, &program->source);
      if (status != RE_STATUS_OK) { re_free(&a, program); return status; } }
    program->source_size = source.size;
    p.text = program->source; p.size = program->source_size; p.at = 0u; p.allocator = &a;
    while (p.at < p.size) {
        if (word(&p, "defmodule")) {
            size_t start; char *module_name = NULL; size_t module_size = 0u;
            skip_space(&p); start = p.at; while (p.at < p.size && (isalnum((unsigned char)p.text[p.at]) || p.text[p.at] == '_')) ++p.at;
            module_size = p.at - start;
            if (module_size == 0u || re_copy_string(&a, (re_string_t){p.text + start, module_size}, &module_name) != RE_STATUS_OK || !take(&p, '{')) { re_free(&a, module_name); re_program_destroy(program); return RE_STATUS_PARSE_ERROR; }
            { size_t module_index; re_status_t status = add_module(&a, program, (re_string_t){p.text + start, module_size}, &module_index); if (status != RE_STATUS_OK) { re_free(&a, module_name); re_program_destroy(program); return status; }
              re_free(&a, module_name);
              while (p.at < p.size && !take(&p, '}')) {
                  if (word(&p, "export")) { if (!take(&p, ':') || word(&p, "none") == 0) { if (!word(&p, "all")) { re_program_destroy(program); return RE_STATUS_PARSE_ERROR; } program->modules[module_index].export_all = 1; } if (!take(&p, ';')) { re_program_destroy(program); return RE_STATUS_PARSE_ERROR; } }
                  else if (word(&p, "import")) { size_t import_start; if (!take(&p, ':')) { re_program_destroy(program); return RE_STATUS_PARSE_ERROR; } skip_space(&p); import_start = p.at; while (p.at < p.size && (isalnum((unsigned char)p.text[p.at]) || p.text[p.at] == '_')) ++p.at; if (import_start == p.at || !take(&p, ';') || add_import(&a, &program->modules[module_index], (re_string_t){p.text + import_start, p.at - import_start - 1u}) != RE_STATUS_OK) { re_program_destroy(program); return RE_STATUS_PARSE_ERROR; } }
                  else { re_program_destroy(program); return RE_STATUS_PARSE_ERROR; }
              }
              if (p.at == p.size && (p.size == 0u || p.text[p.size - 1u] != '}')) { re_program_destroy(program); return RE_STATUS_PARSE_ERROR; }
            }
            continue;
        }
        re_rule_t rule; re_operand_t action_target; memset(&rule, 0, sizeof(rule)); memset(&action_target, 0, sizeof(action_target)); rule.source_order = program->rule_count;
        if (program->limits.max_rules != 0u && program->rule_count >= program->limits.max_rules) { re_program_destroy(program); return RE_STATUS_LIMIT; }
        { re_status_t status = RE_STATUS_OK;
          if (!word(&p, "rule")) status = RE_STATUS_PARSE_ERROR;
          if (status == RE_STATUS_OK) status = quoted(&p, &rule.name, &rule.name_size);
          if (status == RE_STATUS_OK && word(&p, "salience")) {
              status = int32_literal(&p, &rule.salience);
          }
          if (status == RE_STATUS_OK && !take(&p, '{')) status = RE_STATUS_PARSE_ERROR;
          if (status == RE_STATUS_OK) status = rule_attributes(&p, &rule);
          if (status == RE_STATUS_OK && !word(&p, "when")) status = RE_STATUS_PARSE_ERROR;
          if (status != RE_STATUS_OK) { rule_destroy(&a, &rule); re_program_destroy(program); return status; } }
          { re_status_t status = expression(&p, &rule.condition); if (status != RE_STATUS_OK) { rule_destroy(&a, &rule); re_program_destroy(program); return status; } }
         { re_status_t status = RE_STATUS_OK;
           if (!word(&p, "then")) status = RE_STATUS_PARSE_ERROR;
            while (status == RE_STATUS_OK) {
             re_action_t action; memset(&action, 0, sizeof(action));
             status = operand(&p, &action_target);
             if (status == RE_STATUS_OK && action_target.kind != RE_OPERAND_FACT) status = RE_STATUS_PARSE_ERROR;
             if (status == RE_STATUS_OK && !take(&p, '=')) status = RE_STATUS_PARSE_ERROR;
             if (status == RE_STATUS_OK) status = operand(&p, &action.value);
             if (status != RE_STATUS_OK) { re_operand_destroy(&a, &action_target); re_operand_destroy(&a, &action.value); break; }
             action.name = action_target.fact_name; action.name_size = action_target.fact_name_size; memset(&action_target, 0, sizeof(action_target));
             { size_t count = rule.action_count; re_action_t *grown = re_realloc(&a, rule.actions, (count + 1u) * sizeof(*grown)); if (grown == NULL) { re_free(&a, action.name); re_operand_destroy(&a, &action.value); status = RE_STATUS_OUT_OF_MEMORY; break; } rule.actions = grown; rule.actions[count] = action; rule.action_count = count + 1u; }
             if (!take(&p, ';')) break;
             skip_space(&p); if (p.at < p.size && p.text[p.at] == '}') break;
           }
            if (status == RE_STATUS_OK && rule.action_count == 0u) status = RE_STATUS_PARSE_ERROR;
           if (status != RE_STATUS_OK) { re_operand_destroy(&a, &action_target); rule_destroy(&a, &rule); re_program_destroy(program); return status; } }
          rule.compare = RE_COMPARE_TRUE;
         if (!take(&p, '}')) { re_operand_destroy(&a, &action_target); rule_destroy(&a, &rule); re_program_destroy(program); return RE_STATUS_PARSE_ERROR; }
        if (program->rule_count == capacity) { size_t next;
            if (capacity != 0u && capacity > (size_t)-1 / 2u) { rule_destroy(&a, &rule); re_program_destroy(program); return RE_STATUS_LIMIT; }
            next = capacity == 0u ? 4u : capacity * 2u;
            if (next > (size_t)-1 / sizeof(*program->rules)) { rule_destroy(&a, &rule); re_program_destroy(program); return RE_STATUS_LIMIT; }
            { re_rule_t *grown = re_realloc(&a, program->rules, next * sizeof(*grown)); if (grown == NULL) { rule_destroy(&a, &rule); re_program_destroy(program); return RE_STATUS_OUT_OF_MEMORY; } program->rules = grown; capacity = next; } }
        {
            size_t insert_at = program->rule_count;
            while (insert_at > 0u &&
                   program->rules[insert_at - 1u].salience < rule.salience) {
                program->rules[insert_at] = program->rules[insert_at - 1u];
                --insert_at;
            }
            program->rules[insert_at] = rule;
            ++program->rule_count;
        }
        skip_space(&p);
        {
            const char *separator = strstr(rule.name, "::");
            if (separator != NULL) {
                re_string_t module = {rule.name, (size_t)(separator - rule.name)};
                size_t index;
                if (find_module(program, module, &index)) rule.module_index = index;
                else { rule_destroy(&a, &rule); re_program_destroy(program); return RE_STATUS_PARSE_ERROR; }
            } else rule.module_index = SIZE_MAX;
        }
    }
     { re_status_t status = validate_modules(&a, program); if (status != RE_STATUS_OK) { re_program_destroy(program); return status; } }
     *out_program = program; return RE_STATUS_OK;
}

void re_program_destroy(re_program_t *program) { size_t i; if (program == NULL) return; for (i = 0u; i < program->rule_count; ++i) rule_destroy(&program->allocator, &program->rules[i]); modules_destroy(&program->allocator, program); re_free(&program->allocator, program->module_focus); re_free(&program->allocator, program->agenda_focus); re_free(&program->allocator, program->rules); re_free(&program->allocator, program->source); re_free(&program->allocator, program); }

re_status_t re_program_set_module_focus(re_program_t *program, re_string_t module) {
    char *copy;
    if (program == NULL || module.data == NULL || module.size == 0u) return RE_STATUS_INVALID_ARGUMENT;
    { size_t index; if (!find_module(program, module, &index)) return RE_STATUS_NOT_FOUND; }
    if (re_copy_string(&program->allocator, module, &copy) != RE_STATUS_OK) return RE_STATUS_OUT_OF_MEMORY;
    re_free(&program->allocator, program->module_focus); program->module_focus = copy; return RE_STATUS_OK;
}

re_status_t re_program_set_clock(re_program_t *program, int64_t epoch_seconds) {
    if (program == NULL) return RE_STATUS_INVALID_ARGUMENT;
    program->clock_epoch = epoch_seconds; program->has_clock = 1; return RE_STATUS_OK;
}
re_status_t re_program_set_agenda_focus(re_program_t *program, re_string_t group) {
    char *copy;
    if (program == NULL || group.data == NULL || group.size == 0u) return RE_STATUS_INVALID_ARGUMENT;
    if (re_copy_string(&program->allocator, group, &copy) != RE_STATUS_OK) return RE_STATUS_OUT_OF_MEMORY;
    re_free(&program->allocator, program->agenda_focus); program->agenda_focus = copy; return RE_STATUS_OK;
}
