#ifndef BREAK_BACKWARD_MACHINE_GOAL_H
#define BREAK_BACKWARD_MACHINE_GOAL_H

#include "re_internal.h"

typedef re_status_t (*re_goal_machine_proof_fn)(void *context);
typedef re_status_t (*re_goal_machine_trace_push_fn)(void *context, re_string_t name);
typedef re_status_t (*re_goal_machine_trace_push_parent_fn)(void *context, re_string_t name,
                                                            size_t parent_index,
                                                            size_t *out_index);
typedef void (*re_goal_machine_trace_reset_fn)(void *context, size_t count);

typedef struct re_goal_machine_callbacks_t {
    void *context;
    re_goal_machine_proof_fn make_proof;
    re_goal_machine_trace_push_fn push_trace;
    re_goal_machine_trace_reset_fn reset_trace;
    re_goal_machine_trace_push_parent_fn push_trace_parent;
} re_goal_machine_callbacks_t;

re_status_t re_backward_machine_goal_supported(const re_engine_t *engine, re_string_t goal);

/* Runs the explicit zero-argument frame-machine slice. */
re_status_t re_backward_machine_goal_run(re_query_t *query, re_string_t goal,
                                         const re_goal_machine_callbacks_t *callbacks);

#endif
