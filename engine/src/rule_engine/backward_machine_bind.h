#ifndef BREAK_BACKWARD_MACHINE_BIND_H
#define BREAK_BACKWARD_MACHINE_BIND_H

#include "backward_machine_context.h"

typedef struct re_backward_machine_bind_result_t {
    size_t solution_count;
    re_backward_machine_frame_id_t last_parent_id;
} re_backward_machine_bind_result_t;

re_status_t re_backward_machine_bind_run(re_query_t *query, re_string_t goal,
                                          const re_operand_t *arguments,
                                          size_t argument_count,
                                          re_backward_machine_bind_result_t *out);

#endif
