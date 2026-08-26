#ifndef BREAK_BACKWARD_MACHINE_H
#define BREAK_BACKWARD_MACHINE_H

#include "re_internal.h"

typedef enum re_backward_machine_state_t {
    RE_BACKWARD_GOAL_SELECT,
    RE_BACKWARD_RULE_ALTERNATIVE,
    RE_BACKWARD_BIND_ARGS,
    RE_BACKWARD_CONDITION_ENTER,
    RE_BACKWARD_CONDITION_CONTINUE,
    RE_BACKWARD_OPERAND_ENTER,
    RE_BACKWARD_OPERAND_CONTINUE,
    RE_BACKWARD_FUNCTION_ARG,
    RE_BACKWARD_RETURN
} re_backward_machine_state_t;

re_status_t re_backward_machine_run(re_engine_t *engine, re_facts_t *facts,
                                    re_string_t goal, const re_query_options_t *options,
                                    re_query_t **out_query);

#endif
