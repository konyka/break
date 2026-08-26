#include "re_internal.h"
#include "backward_machine.h"

re_status_t re_query_create_bounded(re_engine_t *engine, re_facts_t *facts, re_string_t goal,
                                    const re_query_options_t *options, re_query_t **out_query) {
    return re_backward_machine_run(engine, facts, goal, options, out_query);
}
