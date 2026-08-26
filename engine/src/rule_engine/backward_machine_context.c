#include "backward_machine_context.h"
#include <string.h>

static re_status_t grow(void **items, size_t *capacity, size_t item_size,
                        const re_allocator_impl_t *allocator) {
    size_t next = *capacity == 0u ? 8u : *capacity;
    void *grown;
    if (item_size == 0u) return RE_STATUS_INVALID_ARGUMENT;
    if (*capacity != 0u) {
        if (next > (size_t)-1 / 2u) return RE_STATUS_LIMIT;
        next *= 2u;
    }
    if (next > (size_t)-1 / item_size) return RE_STATUS_LIMIT;
    grown = re_realloc(allocator, *items, next * item_size);
    if (grown == NULL) return RE_STATUS_OUT_OF_MEMORY;
    *items = grown;
    *capacity = next;
    return RE_STATUS_OK;
}

void re_backward_machine_environment_reset(re_backward_machine_environment_t *environment) {
    if (environment == NULL) return;
    environment->items = NULL;
    environment->count = 0u;
    environment->capacity = 0u;
}

re_status_t re_backward_machine_environment_transfer(
    re_backward_machine_environment_t *destination,
    re_backward_machine_environment_t *source) {
    if (destination == NULL || source == NULL || destination == source)
        return RE_STATUS_INVALID_ARGUMENT;
    *destination = *source;
    re_backward_machine_environment_reset(source);
    return RE_STATUS_OK;
}

static void frame_release(const re_allocator_impl_t *allocator, re_backward_machine_frame_t *frame) {
    if (frame->ownership == RE_BACKWARD_FRAME_OWNS_ENVIRONMENT)
        re_free(allocator, frame->environment.items);
    re_backward_machine_frame_reset(frame);
}

void re_backward_machine_frame_reset(re_backward_machine_frame_t *frame) {
    if (frame == NULL) return;
    memset(frame, 0, sizeof(*frame));
    frame->id = RE_BACKWARD_MACHINE_FRAME_ID_INVALID;
    frame->parent_id = RE_BACKWARD_MACHINE_FRAME_ID_INVALID;
}

void re_backward_machine_frame_init(re_backward_machine_frame_t *frame,
                                    re_backward_machine_frame_state_t state,
                                    re_backward_machine_frame_id_t parent_id,
                                    re_backward_machine_frame_ownership_t ownership) {
    if (frame == NULL) return;
    re_backward_machine_frame_reset(frame);
    frame->state = state;
    frame->parent_id = parent_id;
    frame->ownership = ownership;
}

re_status_t re_backward_machine_context_init(re_backward_machine_context_t *context,
                                              const re_allocator_impl_t *allocator) {
    if (context == NULL || allocator == NULL) return RE_STATUS_INVALID_ARGUMENT;
    memset(context, 0, sizeof(*context));
    context->allocator = allocator;
    context->next_id = 0u;
    return RE_STATUS_OK;
}

void re_backward_machine_context_reset(re_backward_machine_context_t *context) {
    size_t index;
    if (context == NULL) return;
    for (index = 0u; index < context->frame_count; ++index)
        frame_release(context->allocator, &context->frames[index]);
    context->frame_count = 0u;
    context->next_id = 0u;
    re_backward_machine_trace_cleanup(context, 0u);
}

void re_backward_machine_context_destroy(re_backward_machine_context_t *context) {
    if (context == NULL) return;
    re_backward_machine_context_reset(context);
    re_free(context->allocator, context->frames);
    re_free(context->allocator, context->trace.names);
    memset(context, 0, sizeof(*context));
}

re_status_t re_backward_machine_context_push(re_backward_machine_context_t *context,
                                              re_backward_machine_frame_state_t state,
                                              re_backward_machine_frame_id_t parent_id,
                                              re_backward_machine_frame_ownership_t ownership,
                                              re_backward_machine_frame_id_t *out_id) {
    re_backward_machine_frame_t *frame;
    re_status_t status;
    if (context == NULL || context->allocator == NULL || out_id == NULL)
        return RE_STATUS_INVALID_ARGUMENT;
    if (context->next_id == RE_BACKWARD_MACHINE_FRAME_ID_INVALID) return RE_STATUS_LIMIT;
    if (context->frame_count == context->frame_capacity) {
        status = grow((void **)&context->frames, &context->frame_capacity,
                      sizeof(*context->frames), context->allocator);
        if (status != RE_STATUS_OK) return status;
    }
    frame = &context->frames[context->frame_count++];
    re_backward_machine_frame_init(frame, state, parent_id, ownership);
    frame->id = context->next_id++;
    *out_id = frame->id;
    return RE_STATUS_OK;
}

re_backward_machine_frame_t *re_backward_machine_context_frame(
    re_backward_machine_context_t *context, re_backward_machine_frame_id_t id) {
    size_t index;
    if (context == NULL) return NULL;
    for (index = 0u; index < context->frame_count; ++index)
        if (context->frames[index].id == id) return &context->frames[index];
    return NULL;
}

size_t re_backward_machine_trace_checkpoint(const re_backward_machine_context_t *context) {
    return context == NULL ? 0u : context->trace.count;
}

void re_backward_machine_trace_cleanup(re_backward_machine_context_t *context, size_t checkpoint) {
    if (context == NULL) return;
    if (checkpoint > context->trace.count) checkpoint = context->trace.count;
    context->trace.count = checkpoint;
}
