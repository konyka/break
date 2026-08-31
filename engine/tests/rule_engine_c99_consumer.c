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
    re_fact_txn_t *transaction = NULL;
    re_function_descriptor_t function = {sizeof(function), RE_ABI_VERSION_MAJOR,
                                         (re_string_t){"f", 1u}, NULL, NULL, NULL};
    re_stream_window_options_t window_options = {
        sizeof(window_options), RE_STREAM_WINDOW_ABI_VERSION,
        RE_STREAM_WINDOW_SLIDING, RE_LATE_EVENT_DROP, 1000u, 10u, 4096u, 25u, 0u};
    re_state_provider_options_t provider_options = {
        sizeof(provider_options), RE_STATE_PROVIDER_ABI_VERSION,
        RE_STATE_PROVIDER_CALLBACK, 0u, 100u};
    re_snapshot_t snapshot = {sizeof(snapshot), 1u, NULL, 0u, NULL, NULL};
    re_stream_filter_options_t filter = {sizeof(filter), RE_STREAM_WINDOW_ABI_VERSION,
                                          (re_string_t){"x", 1u}, (re_string_t){NULL, 0u}, 0.0};
    re_proof_node_t proof_node = {sizeof(proof_node), (re_string_t){NULL, 0u}};
    re_proof_edge_t proof_edge = {sizeof(proof_edge), 0u, 0u};

    return options.limits == &limits && callbacks.action != NULL &&
                   re_facts_begin(NULL, &transaction) == RE_STATUS_INVALID_ARGUMENT && transaction == NULL &&
                   value.type == RE_VALUE_INT64 && function.abi_version == RE_ABI_VERSION_MAJOR &&
                   window_options.kind == RE_STREAM_WINDOW_SLIDING &&
                   provider_options.kind == RE_STATE_PROVIDER_CALLBACK &&
                   snapshot.format_version == 1u
                   && filter.event_type.size == 1u && proof_node.struct_size == sizeof(proof_node)
                   && proof_edge.child_index == 0u
               ? 0
               : 1;
}
