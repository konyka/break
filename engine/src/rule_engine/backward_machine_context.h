#ifndef BREAK_BACKWARD_MACHINE_CONTEXT_H
#define BREAK_BACKWARD_MACHINE_CONTEXT_H

#include "re_internal.h"

typedef enum re_backward_machine_frame_state_t {
    RE_BACKWARD_FRAME_GOAL_SELECT,
    RE_BACKWARD_FRAME_RULE_ALTERNATIVE,
    RE_BACKWARD_FRAME_BIND_ARGS,
    RE_BACKWARD_FRAME_CONDITION_ENTER,
    RE_BACKWARD_FRAME_CONDITION_CONTINUE,
    RE_BACKWARD_FRAME_OPERAND_ENTER,
    RE_BACKWARD_FRAME_OPERAND_CONTINUE,
    RE_BACKWARD_FRAME_FUNCTION_ARG,
    RE_BACKWARD_FRAME_RETURN
} re_backward_machine_frame_state_t;

typedef enum re_backward_machine_frame_ownership_t {
    RE_BACKWARD_FRAME_BORROWED,
    RE_BACKWARD_FRAME_OWNS_ENVIRONMENT
} re_backward_machine_frame_ownership_t;

typedef struct re_backward_machine_environment_t {
    struct re_backward_machine_binding_t *items;
    size_t count;
    size_t capacity;
} re_backward_machine_environment_t;

typedef struct re_backward_machine_binding_t {
    re_string_t name;
    re_value_t value;
    char *name_data;
    char *string_data;
} re_backward_machine_binding_t;

typedef size_t re_backward_machine_frame_id_t;

typedef enum re_backward_machine_result_kind_t {
    RE_BACKWARD_MACHINE_RESULT_PENDING,
    RE_BACKWARD_MACHINE_RESULT_TRUE,
    RE_BACKWARD_MACHINE_RESULT_FALSE,
    RE_BACKWARD_MACHINE_RESULT_NOT_SUPPORTED
} re_backward_machine_result_kind_t;

typedef struct re_backward_machine_result_t {
    re_backward_machine_result_kind_t kind;
    re_backward_machine_frame_id_t parent_id;
} re_backward_machine_result_t;

typedef struct re_backward_machine_frame_t {
    re_backward_machine_frame_id_t id;
    re_backward_machine_frame_id_t parent_id;
    re_backward_machine_frame_state_t state;
    re_backward_machine_frame_ownership_t ownership;
    re_string_t goal;
    re_operand_t *arguments;
    size_t argument_count;
    const re_expr_t *condition;
    const re_operand_t *operand;
    re_backward_machine_environment_t environment;
    size_t continuation;
    size_t depth;
    size_t trace_start;
    size_t trace_index;
    struct re_backward_machine_result_t result;
} re_backward_machine_frame_t;

typedef struct re_backward_machine_trace_t {
    re_string_t *names;
    size_t count;
    size_t capacity;
} re_backward_machine_trace_t;

typedef struct re_backward_machine_context_t {
    const re_allocator_impl_t *allocator;
    re_backward_machine_frame_t *frames;
    size_t frame_count;
    size_t frame_capacity;
    re_backward_machine_frame_id_t next_id;
    re_backward_machine_trace_t trace;
} re_backward_machine_context_t;

#define RE_BACKWARD_MACHINE_FRAME_ID_INVALID ((re_backward_machine_frame_id_t)-1)

re_status_t re_backward_machine_context_init(re_backward_machine_context_t *context,
                                              const re_allocator_impl_t *allocator);
void re_backward_machine_context_reset(re_backward_machine_context_t *context);
void re_backward_machine_context_destroy(re_backward_machine_context_t *context);
void re_backward_machine_frame_init(re_backward_machine_frame_t *frame,
                                    re_backward_machine_frame_state_t state,
                                    re_backward_machine_frame_id_t parent_id,
                                    re_backward_machine_frame_ownership_t ownership);
re_status_t re_backward_machine_context_push(re_backward_machine_context_t *context,
                                              re_backward_machine_frame_state_t state,
                                              re_backward_machine_frame_id_t parent_id,
                                              re_backward_machine_frame_ownership_t ownership,
                                              re_backward_machine_frame_id_t *out_id);
re_backward_machine_frame_t *re_backward_machine_context_frame(
    re_backward_machine_context_t *context, re_backward_machine_frame_id_t id);
void re_backward_machine_frame_reset(re_backward_machine_frame_t *frame);
re_status_t re_backward_machine_environment_transfer(
    re_backward_machine_environment_t *destination,
    re_backward_machine_environment_t *source);
void re_backward_machine_environment_reset(re_backward_machine_environment_t *environment);
size_t re_backward_machine_trace_checkpoint(const re_backward_machine_context_t *context);
void re_backward_machine_trace_cleanup(re_backward_machine_context_t *context, size_t checkpoint);

#endif
