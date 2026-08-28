#include "re_internal.h"
#include <ctype.h>
#include <string.h>

/* Rule templates (see rule_engine.h): plain byte substitution of
 * {{identifier}} placeholders into a fixed GRL rule shape. The module keeps
 * no engine state; the host feeds the emitted text to re_program_load. */

typedef struct re_template_default_t {
    char *name;
    size_t name_size;
    char *value;
    size_t value_size;
} re_template_default_t;

struct re_rule_template_t {
    re_allocator_impl_t allocator;
    char *name;
    size_t name_size;
    char *condition;
    size_t condition_size;
    char *action;
    size_t action_size;
    int32_t salience;
    re_template_default_t *defaults;
    size_t default_count;
};

static int re_template_ident_start(char c) {
    return isalpha((unsigned char)c) || c == '_';
}

static int re_template_ident_char(char c) {
    return isalnum((unsigned char)c) || c == '_';
}

/* When text at `at` opens a {{identifier}} placeholder, stores the borrowed
 * identifier and the full placeholder length and returns 1; otherwise the
 * text is literal and 0 is returned. */
static int re_template_placeholder_at(const char *text, size_t size, size_t at,
                                      re_string_t *name, size_t *length) {
    size_t start;
    size_t end;
    if (at + 1u >= size || text[at] != '{' || text[at + 1u] != '{') return 0;
    start = at + 2u;
    if (start >= size || !re_template_ident_start(text[start])) return 0;
    end = start + 1u;
    while (end < size && re_template_ident_char(text[end])) ++end;
    if (end + 1u >= size || text[end] != '}' || text[end + 1u] != '}') return 0;
    name->data = text + start;
    name->size = end - start;
    *length = end + 2u - at;
    return 1;
}

/* Supplied params win over defaults; an unresolved placeholder is invalid. */
static re_status_t re_template_resolve(const re_rule_template_t *t,
                                       const re_template_param_t *params, size_t param_count,
                                       re_string_t name, re_string_t *out_value) {
    size_t i;
    for (i = 0u; i < param_count; ++i) {
        if (params[i].name.size == name.size &&
            memcmp(params[i].name.data, name.data, name.size) == 0) {
            *out_value = params[i].value;
            return RE_STATUS_OK;
        }
    }
    for (i = 0u; i < t->default_count; ++i) {
        if (t->defaults[i].name_size == name.size &&
            memcmp(t->defaults[i].name, name.data, name.size) == 0) {
            out_value->data = t->defaults[i].value;
            out_value->size = t->defaults[i].value_size;
            return RE_STATUS_OK;
        }
    }
    return RE_STATUS_INVALID_ARGUMENT;
}

static int re_template_has_placeholder(const char *text, size_t size, re_string_t name) {
    size_t at = 0u;
    while (at < size) {
        re_string_t found;
        size_t length;
        if (text[at] == '{' && re_template_placeholder_at(text, size, at, &found, &length)) {
            if (found.size == name.size && memcmp(found.data, name.data, name.size) == 0) return 1;
            at += length;
        } else {
            ++at;
        }
    }
    return 0;
}

typedef struct re_template_emit_t {
    char *out;
    size_t at;
    int overflow;
} re_template_emit_t;

static void re_template_emit_bytes(re_template_emit_t *e, const char *data, size_t size) {
    if (size > (size_t)-1 - e->at) {
        e->overflow = 1;
        return;
    }
    if (e->out != NULL && size != 0u) memcpy(e->out + e->at, data, size);
    e->at += size;
}

static void re_template_emit_text(re_template_emit_t *e, const char *text) {
    re_template_emit_bytes(e, text, strlen(text));
}

static re_status_t re_template_emit_substituted(re_template_emit_t *e, const re_rule_template_t *t,
                                                const re_template_param_t *params, size_t param_count,
                                                const char *text, size_t size) {
    size_t run = 0u;
    size_t at = 0u;
    while (at < size) {
        re_string_t name;
        re_string_t value;
        size_t length;
        if (text[at] == '{' && re_template_placeholder_at(text, size, at, &name, &length)) {
            re_status_t status;
            re_template_emit_bytes(e, text + run, at - run);
            status = re_template_resolve(t, params, param_count, name, &value);
            if (status != RE_STATUS_OK) return status;
            re_template_emit_bytes(e, value.data, value.size);
            at += length;
            run = at;
        } else {
            ++at;
        }
    }
    re_template_emit_bytes(e, text + run, at - run);
    return RE_STATUS_OK;
}

/* Writes the decimal form of salience into out; returns the length. */
static size_t re_template_format_salience(int32_t salience, char out[16]) {
    char reversed[16];
    size_t count = 0u;
    size_t length = 0u;
    uint32_t magnitude;
    if (salience < 0) {
        out[length++] = '-';
        magnitude = (uint32_t)(-(int64_t)salience);
    } else {
        magnitude = (uint32_t)salience;
    }
    do {
        reversed[count++] = (char)('0' + (int)(magnitude % 10u));
        magnitude /= 10u;
    } while (magnitude != 0u);
    while (count != 0u) out[length++] = reversed[--count];
    return length;
}

static re_status_t re_template_emit_rule(re_template_emit_t *e, const re_rule_template_t *t,
                                         re_string_t rule_name,
                                         const re_template_param_t *params, size_t param_count) {
    re_status_t status;
    re_template_emit_text(e, "rule \"");
    re_template_emit_bytes(e, rule_name.data, rule_name.size);
    re_template_emit_text(e, "\"");
    if (t->salience != 0) {
        char digits[16];
        size_t length = re_template_format_salience(t->salience, digits);
        re_template_emit_text(e, " salience ");
        re_template_emit_bytes(e, digits, length);
    }
    re_template_emit_text(e, " {\nwhen\n");
    status = re_template_emit_substituted(e, t, params, param_count,
                                          t->condition, t->condition_size);
    if (status != RE_STATUS_OK) return status;
    re_template_emit_text(e, "\nthen\n");
    status = re_template_emit_substituted(e, t, params, param_count,
                                          t->action, t->action_size);
    if (status != RE_STATUS_OK) return status;
    re_template_emit_text(e, ";\n}");
    return RE_STATUS_OK;
}

re_status_t re_rule_template_create(re_string_t name, re_string_t condition_template,
                                    re_string_t action_template, int32_t salience,
                                    re_rule_template_t **out_template) {
    re_allocator_impl_t allocator;
    re_rule_template_t *t;
    re_status_t status;
    if (out_template == NULL) return RE_STATUS_INVALID_ARGUMENT;
    *out_template = NULL;
    /* The ABI fixes this signature without an allocator argument, so
     * templates use the default allocator through the engine helpers. */
    re_allocator_init(&allocator, NULL);
    t = re_alloc(&allocator, sizeof(*t));
    if (t == NULL) return RE_STATUS_OUT_OF_MEMORY;
    memset(t, 0, sizeof(*t));
    t->allocator = allocator;
    t->salience = salience;
    status = re_copy_string(&allocator, name, &t->name);
    if (status == RE_STATUS_OK) status = re_copy_string(&allocator, condition_template, &t->condition);
    if (status == RE_STATUS_OK) status = re_copy_string(&allocator, action_template, &t->action);
    if (status != RE_STATUS_OK) {
        re_rule_template_destroy(t);
        return status;
    }
    t->name_size = name.size;
    t->condition_size = condition_template.size;
    t->action_size = action_template.size;
    *out_template = t;
    return RE_STATUS_OK;
}

re_status_t re_rule_template_param_default(re_rule_template_t *t, re_string_t param,
                                           re_string_t default_value) {
    size_t i;
    char *name_copy = NULL;
    char *value_copy = NULL;
    re_status_t status;
    re_template_default_t *grown;
    if (t == NULL || param.size == 0u || param.data == NULL ||
        (default_value.size != 0u && default_value.data == NULL))
        return RE_STATUS_INVALID_ARGUMENT;
    for (i = 0u; i < t->default_count; ++i) {
        if (t->defaults[i].name_size == param.size &&
            memcmp(t->defaults[i].name, param.data, param.size) == 0) {
            status = re_copy_string(&t->allocator, default_value, &value_copy);
            if (status != RE_STATUS_OK) return status;
            re_free(&t->allocator, t->defaults[i].value);
            t->defaults[i].value = value_copy;
            t->defaults[i].value_size = default_value.size;
            return RE_STATUS_OK;
        }
    }
    status = re_copy_string(&t->allocator, param, &name_copy);
    if (status == RE_STATUS_OK) status = re_copy_string(&t->allocator, default_value, &value_copy);
    if (status != RE_STATUS_OK) {
        re_free(&t->allocator, name_copy);
        re_free(&t->allocator, value_copy);
        return status;
    }
    if (t->default_count >= (size_t)-1 / sizeof(*t->defaults)) {
        re_free(&t->allocator, name_copy);
        re_free(&t->allocator, value_copy);
        return RE_STATUS_LIMIT;
    }
    grown = re_realloc(&t->allocator, t->defaults, (t->default_count + 1u) * sizeof(*grown));
    if (grown == NULL) {
        re_free(&t->allocator, name_copy);
        re_free(&t->allocator, value_copy);
        return RE_STATUS_OUT_OF_MEMORY;
    }
    t->defaults = grown;
    t->defaults[t->default_count].name = name_copy;
    t->defaults[t->default_count].name_size = param.size;
    t->defaults[t->default_count].value = value_copy;
    t->defaults[t->default_count].value_size = default_value.size;
    ++t->default_count;
    return RE_STATUS_OK;
}

re_status_t re_rule_template_instantiate(const re_rule_template_t *t, re_string_t rule_name,
                                         const re_template_param_t *params, size_t param_count,
                                         char *out_text, size_t *inout_text_size) {
    re_template_emit_t emit;
    size_t capacity;
    size_t i;
    re_status_t status;
    if (t == NULL || inout_text_size == NULL ||
        (rule_name.size != 0u && rule_name.data == NULL) ||
        (params == NULL && param_count != 0u))
        return RE_STATUS_INVALID_ARGUMENT;
    capacity = *inout_text_size;
    for (i = 0u; i < param_count; ++i) {
        if ((params[i].name.size != 0u && params[i].name.data == NULL) ||
            (params[i].value.size != 0u && params[i].value.data == NULL))
            return RE_STATUS_INVALID_ARGUMENT;
        if (!re_template_has_placeholder(t->condition, t->condition_size, params[i].name) &&
            !re_template_has_placeholder(t->action, t->action_size, params[i].name))
            return RE_STATUS_INVALID_ARGUMENT;
    }
    /* First pass computes the required size; the second writes the text. */
    emit.out = NULL;
    emit.at = 0u;
    emit.overflow = 0;
    status = re_template_emit_rule(&emit, t, rule_name, params, param_count);
    if (status != RE_STATUS_OK) return status;
    if (emit.overflow != 0 || emit.at == (size_t)-1) return RE_STATUS_LIMIT;
    *inout_text_size = emit.at + 1u;
    if (out_text == NULL || capacity < emit.at + 1u) return RE_STATUS_LIMIT;
    emit.out = out_text;
    emit.at = 0u;
    emit.overflow = 0;
    status = re_template_emit_rule(&emit, t, rule_name, params, param_count);
    if (status != RE_STATUS_OK) return status;
    out_text[emit.at] = '\0';
    return RE_STATUS_OK;
}

void re_rule_template_destroy(re_rule_template_t *t) {
    size_t i;
    if (t == NULL) return;
    for (i = 0u; i < t->default_count; ++i) {
        re_free(&t->allocator, t->defaults[i].name);
        re_free(&t->allocator, t->defaults[i].value);
    }
    re_free(&t->allocator, t->defaults);
    re_free(&t->allocator, t->name);
    re_free(&t->allocator, t->condition);
    re_free(&t->allocator, t->action);
    re_free(&t->allocator, t);
}
