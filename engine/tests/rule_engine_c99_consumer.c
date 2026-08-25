#include <rule_engine/rule_engine.h>

static re_status_t consume_action(re_engine_t *engine, re_facts_t *facts,
                                  const re_rule_event_t *event, void *context)
{
    (void)engine;
    (void)facts;
    (void)event;
    (void)context;
    return RE_STATUS_OK;
}

int rule_engine_c99_consumer(void)
{
    re_limits_t limits = {0};
    re_run_options_t options = {&limits, NULL, NULL};
    re_callbacks_t callbacks = {consume_action, NULL};
    re_value_t value = {RE_VALUE_INT64, {.int64_value = 1}};

    return options.limits == &limits && callbacks.action != NULL &&
                   value.type == RE_VALUE_INT64
               ? 0
               : 1;
}
