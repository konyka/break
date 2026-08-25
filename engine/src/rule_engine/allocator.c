#include "re_internal.h"
#include <stdlib.h>
#include <string.h>

static void *default_alloc(void *context, size_t size) { (void)context; return malloc(size); }
static void *default_realloc(void *context, void *memory, size_t size) {
    (void)context; return realloc(memory, size);
}
static void default_free(void *context, void *memory) { (void)context; free(memory); }

void *re_alloc(const re_allocator_impl_t *allocator, size_t size) {
    return allocator->api.alloc(allocator->api.context, size);
}
void *re_realloc(const re_allocator_impl_t *allocator, void *memory, size_t size) {
    return allocator->api.realloc(allocator->api.context, memory, size);
}
void re_free(const re_allocator_impl_t *allocator, void *memory) {
    if (memory != NULL) allocator->api.free(allocator->api.context, memory);
}

re_limits_t re_default_limits(void) {
    re_limits_t limits = {65536u, 1024u, 1024u, 1024u, 1024u};
    return limits;
}

re_status_t re_copy_string(const re_allocator_impl_t *allocator, re_string_t input, char **out) {
    char *copy;
    if (out == NULL || (input.size != 0u && input.data == NULL)) return RE_STATUS_INVALID_ARGUMENT;
    if (input.size > (size_t)-2) return RE_STATUS_INVALID_ARGUMENT;
    copy = re_alloc(allocator, input.size + 1u);
    if (copy == NULL) return RE_STATUS_OUT_OF_MEMORY;
    if (input.size != 0u) memcpy(copy, input.data, input.size);
    copy[input.size] = '\0';
    *out = copy;
    return RE_STATUS_OK;
}

void re_operand_destroy(const re_allocator_impl_t *allocator, re_operand_t *operand) {
    if (operand == NULL) return;
    re_free(allocator, operand->fact_name);
    if (operand->kind == RE_OPERAND_LITERAL && operand->value.type == RE_VALUE_STRING)
        re_free(allocator, (void *)operand->value.as.string.data);
    memset(operand, 0, sizeof(*operand));
}

re_status_t re_operand_copy(const re_allocator_impl_t *allocator, const re_operand_t *source,
                            re_operand_t *target) {
    memset(target, 0, sizeof(*target));
    target->kind = source->kind;
    target->value = source->value;
    if (source->kind == RE_OPERAND_FACT)
        return re_copy_string(allocator, (re_string_t){source->fact_name, source->fact_name_size},
                              &target->fact_name);
    if (source->value.type == RE_VALUE_STRING) {
        char *copy = NULL;
        re_status_t status = re_copy_string(allocator, source->value.as.string, &copy);
        if (status != RE_STATUS_OK) return status;
        target->value.as.string.data = copy;
    }
    return RE_STATUS_OK;
}

void re_allocator_init(re_allocator_impl_t *target, const re_allocator_t *source) {
    if (source == NULL) {
        target->api.context = NULL; target->api.alloc = default_alloc;
        target->api.realloc = default_realloc; target->api.free = default_free;
    } else target->api = *source;
}
