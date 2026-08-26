#include "re_internal.h"
#include <string.h>
#include <stdint.h>

static re_status_t unsupported(void) {
    return RE_STATUS_NOT_SUPPORTED;
}

typedef struct snapshot_release_context_t {
    re_allocator_impl_t allocator;
} snapshot_release_context_t;

static void snapshot_release(void *context, const uint8_t *data, size_t size) {
    snapshot_release_context_t *release_context = context;
    (void)size;
    re_free(&release_context->allocator, (void *)data);
    re_free(&release_context->allocator, release_context);
}

static void stream_event_destroy(re_stream_window_t *window, re_stream_event_impl_t *event) {
    re_free(&window->allocator, event->name);
    re_free(&window->allocator, event->value_data);
    memset(event, 0, sizeof(*event));
}

static size_t stream_event_bytes(const re_stream_event_impl_t *event) {
    return event->name_size + (event->value.type == RE_VALUE_STRING ? event->value.as.string.size : sizeof(re_value_t));
}

static size_t stream_total_bytes(const re_stream_window_t *window) {
    size_t index, bytes = 0u;
    for (index = 0u; index < window->count; ++index) bytes += stream_event_bytes(&window->events[index]);
    return bytes;
}

static void stream_evict(re_stream_window_t *window) {
    size_t index;
    uint64_t cutoff = window->watermark > window->options.retention_ms
        ? window->watermark - window->options.retention_ms : 0u;
    while (window->count != 0u && window->events[0].timestamp < cutoff) {
        stream_event_destroy(window, &window->events[0]);
        for (index = 1u; index < window->count; ++index) window->events[index - 1u] = window->events[index];
        --window->count;
    }
    while (window->count > window->options.max_events) {
        stream_event_destroy(window, &window->events[0]);
        for (index = 1u; index < window->count; ++index) window->events[index - 1u] = window->events[index];
        --window->count;
    }
    while (window->count != 0u) {
        if (stream_total_bytes(window) <= window->options.max_bytes) break;
        stream_event_destroy(window, &window->events[0]);
        for (index = 1u; index < window->count; ++index) window->events[index - 1u] = window->events[index];
        --window->count;
    }
}

static re_status_t stream_copy_value(re_stream_window_t *window, const re_value_t *source,
                                     re_value_t *target, char **data) {
    *target = *source; *data = NULL;
    if (source->type != RE_VALUE_STRING) return RE_STATUS_OK;
    *data = re_alloc(&window->allocator, source->as.string.size + 1u);
    if (*data == NULL) return RE_STATUS_OUT_OF_MEMORY;
    memcpy(*data, source->as.string.data, source->as.string.size);
    (*data)[source->as.string.size] = '\0';
    target->as.string.data = *data;
    return RE_STATUS_OK;
}

re_status_t re_engine_agenda(const re_engine_t *engine, re_agenda_t **out_agenda) {
    (void)engine;
    (void)out_agenda;
    return unsupported();
}
void re_agenda_destroy(re_agenda_t *agenda) {
    (void)agenda;
}
re_status_t re_engine_rete_network(const re_engine_t *engine,
                                    re_rete_network_t **out_network) {
    if (engine == NULL || out_network == NULL) return RE_STATUS_INVALID_ARGUMENT;
    *out_network = engine->rete_network;
    return *out_network == NULL ? RE_STATUS_NOT_SUPPORTED : RE_STATUS_OK;
}
void re_rete_network_destroy(re_rete_network_t *network) {
    re_rete_network_destroy_internal(network);
}
re_status_t re_engine_query(re_engine_t *engine, re_facts_t *facts,
                             re_string_t goal, re_query_t **out_query) {
    return re_query_create_bounded(engine, facts, goal, NULL, out_query);
}
re_status_t re_engine_query_bounded(re_engine_t *engine, re_facts_t *facts,
                                    re_string_t goal, const re_query_options_t *options,
                                    re_query_t **out_query) {
    return re_query_create_bounded(engine, facts, goal, options, out_query);
}
re_status_t re_query_next(re_query_t *query, re_proof_t **out_proof) {
    if (query == NULL || out_proof == NULL) return RE_STATUS_INVALID_ARGUMENT;
    *out_proof = NULL;
    if (query->invalidated) return RE_STATUS_NOT_FOUND;
    if (query->next_proof >= query->proof_count) return RE_STATUS_NOT_FOUND;
    *out_proof = query->proofs[query->next_proof];
    query->proofs[query->next_proof] = NULL;
    query->next_proof++;
    return RE_STATUS_OK;
}
re_query_result_t re_query_result(const re_query_t *query) {
    return query == NULL ? RE_QUERY_UNKNOWN : query->result;
}
size_t re_query_solution_count(const re_query_t *query) {
    return query == NULL ? 0u : query->proof_count;
}
size_t re_proof_binding_count(const re_proof_t *proof) {
    return proof == NULL ? 0u : proof->binding_count;
}
re_status_t re_proof_binding_get(const re_proof_t *proof, size_t index,
                                 re_query_binding_t *out_binding) {
    if (proof == NULL || out_binding == NULL) return RE_STATUS_INVALID_ARGUMENT;
    if (index >= proof->binding_count) return RE_STATUS_NOT_FOUND;
    out_binding->name.data = proof->bindings[index].name;
    out_binding->name.size = proof->bindings[index].name_size;
    out_binding->value = proof->bindings[index].value;
    return RE_STATUS_OK;
}
size_t re_proof_trace_count(const re_proof_t *proof) {
    return proof == NULL ? 0u : proof->trace_count;
}
re_status_t re_proof_trace_get(const re_proof_t *proof, size_t index,
                               re_string_t *out_rule_name) {
    if (proof == NULL || out_rule_name == NULL) return RE_STATUS_INVALID_ARGUMENT;
    if (index >= proof->trace_count) return RE_STATUS_NOT_FOUND;
    out_rule_name->data = proof->trace_names[index];
    out_rule_name->size = strlen(proof->trace_names[index]);
    return RE_STATUS_OK;
}
size_t re_proof_node_count(const re_proof_t *proof) {
    return proof == NULL ? 0u : proof->node_count;
}
re_status_t re_proof_node_get(const re_proof_t *proof, size_t index,
                              re_proof_node_t *out_node) {
    if (proof == NULL || out_node == NULL || out_node->struct_size < sizeof(*out_node))
        return RE_STATUS_INVALID_ARGUMENT;
    if (index >= proof->node_count) return RE_STATUS_NOT_FOUND;
    out_node->rule_name.data = proof->nodes[index].rule_name;
    out_node->rule_name.size = proof->nodes[index].rule_name_size;
    return RE_STATUS_OK;
}
size_t re_proof_edge_count(const re_proof_t *proof) {
    return proof == NULL ? 0u : proof->edge_count;
}
re_status_t re_proof_edge_get(const re_proof_t *proof, size_t index,
                              re_proof_edge_t *out_edge) {
    if (proof == NULL || out_edge == NULL || out_edge->struct_size < sizeof(*out_edge))
        return RE_STATUS_INVALID_ARGUMENT;
    if (index >= proof->edge_count) return RE_STATUS_NOT_FOUND;
    out_edge->parent_index = proof->edges[index].parent_index;
    out_edge->child_index = proof->edges[index].child_index;
    return RE_STATUS_OK;
}
void re_query_destroy(re_query_t *query) {
    size_t index;
    if (query == NULL) return;
    re_subscription_destroy(query->subscription);
    for (index = 0u; index < query->proof_count; ++index) re_proof_destroy(query->proofs[index]);
    re_free(&query->allocator, query->proofs);
    re_free(&query->allocator, query);
}
void re_proof_destroy(re_proof_t *proof) {
    size_t index;
    if (proof == NULL) return;
    for (index = 0u; index < proof->binding_count; ++index) {
        re_free(&proof->allocator, proof->bindings[index].name);
        re_free(&proof->allocator, proof->bindings[index].string_data);
    }
    for (index = 0u; index < proof->trace_count; ++index) re_free(&proof->allocator, proof->trace_names[index]);
    for (index = 0u; index < proof->node_count; ++index)
        re_free(&proof->allocator, proof->nodes[index].rule_name);
    re_free(&proof->allocator, proof->edges);
    re_free(&proof->allocator, proof->nodes);
    re_free(&proof->allocator, proof->trace_names);
    re_free(&proof->allocator, proof->bindings);
    re_free(&proof->allocator, proof);
}
re_status_t re_stream_window_create(re_engine_t *engine, re_stream_window_t **out_window) {
    (void)engine;
    (void)out_window;
    return unsupported();
}
re_status_t re_stream_window_record(re_stream_window_t *window,
                                    uint64_t timestamp_ms,
                                    re_string_t event_name,
                                    const re_value_t *value) {
    (void)window; (void)timestamp_ms; (void)event_name; (void)value;
    return unsupported();
}
void re_stream_window_destroy(re_stream_window_t *window) {
    size_t index;
    if (window == NULL) return;
    for (index = 0u; index < window->count; ++index) stream_event_destroy(window, &window->events[index]);
    re_free(&window->allocator, window->events); re_free(&window->allocator, window);
}
re_status_t re_stream_window_create_v1(re_engine_t *engine, const re_stream_window_options_t *options,
                                       re_stream_window_t **out_window) {
    re_stream_window_t *window;
    if (engine == NULL || options == NULL || out_window == NULL || options->struct_size < sizeof(*options) ||
        options->abi_version != RE_STREAM_WINDOW_ABI_VERSION ||
        (options->kind != RE_STREAM_WINDOW_SLIDING && options->kind != RE_STREAM_WINDOW_TUMBLING &&
         options->kind != RE_STREAM_WINDOW_SESSION) ||
         options->retention_ms == 0u || options->max_events == 0u || options->max_bytes == 0u ||
         (options->late_event_policy != RE_LATE_EVENT_DROP && options->late_event_policy != RE_LATE_EVENT_ACCEPT &&
          options->late_event_policy != RE_LATE_EVENT_ERROR)) return RE_STATUS_INVALID_ARGUMENT;
    if (options->kind != RE_STREAM_WINDOW_SLIDING) return re_stream_window_create_bounded(engine, options, out_window);
    *out_window = NULL;
    window = re_alloc(&engine->allocator, sizeof(*window));
    if (window == NULL) return RE_STATUS_OUT_OF_MEMORY;
    memset(window, 0, sizeof(*window)); window->allocator = engine->allocator; window->options = *options;
    *out_window = window; return RE_STATUS_OK;
}
re_status_t re_stream_window_record_v1(re_stream_window_t *window, uint64_t timestamp_ms,
                                       re_string_t event_name, const re_value_t *value) {
    re_stream_event_impl_t event;
    size_t index;
    if (window != NULL && window->options.kind != RE_STREAM_WINDOW_SLIDING)
        return re_stream_window_record_bounded(window, timestamp_ms, event_name, value);
    if (window == NULL || value == NULL || event_name.data == NULL || event_name.size == 0u) return RE_STATUS_INVALID_ARGUMENT;
    if (timestamp_ms < window->watermark && window->watermark - timestamp_ms > window->options.allowed_lateness_ms) {
        return window->options.late_event_policy == RE_LATE_EVENT_DROP ? RE_STATUS_NOT_FOUND :
               window->options.late_event_policy == RE_LATE_EVENT_ERROR ? RE_STATUS_ERROR : RE_STATUS_OK;
    }
    memset(&event, 0, sizeof(event)); event.timestamp = timestamp_ms; event.name_size = event_name.size;
    event.name = re_alloc(&window->allocator, event_name.size + 1u);
    if (event.name == NULL) return RE_STATUS_OUT_OF_MEMORY;
    memcpy(event.name, event_name.data, event_name.size); event.name[event_name.size] = '\0';
    if (stream_copy_value(window, value, &event.value, &event.value_data) != RE_STATUS_OK) {
        stream_event_destroy(window, &event); return RE_STATUS_OUT_OF_MEMORY;
    }
    if (window->count == window->capacity) {
        size_t capacity = window->capacity == 0u ? 8u : window->capacity * 2u;
        if (capacity < window->capacity || capacity > SIZE_MAX / sizeof(*window->events)) {
            stream_event_destroy(window, &event); return RE_STATUS_LIMIT;
        }
        re_stream_event_impl_t *events = re_realloc(&window->allocator, window->events, capacity * sizeof(*events));
        if (events == NULL) { stream_event_destroy(window, &event); return RE_STATUS_OUT_OF_MEMORY; }
        window->events = events; window->capacity = capacity;
    }
    index = window->count;
    while (index != 0u && window->events[index - 1u].timestamp > timestamp_ms) {
        window->events[index] = window->events[index - 1u]; --index;
    }
    window->events[index] = event; ++window->count;
    if (timestamp_ms > window->watermark) window->watermark = timestamp_ms;
    stream_evict(window); return RE_STATUS_OK;
}
re_status_t re_stream_window_snapshot(const re_stream_window_t *window, re_snapshot_t *out_snapshot) {
    size_t index, size = sizeof(uint64_t) * 2u;
    uint8_t *data;
    if (window == NULL || out_snapshot == NULL || out_snapshot->struct_size < sizeof(*out_snapshot)) return RE_STATUS_INVALID_ARGUMENT;
    for (index = 0u; index < window->count; ++index) {
        size_t item = sizeof(uint64_t) * 3u + sizeof(uint32_t) + window->events[index].name_size +
            (window->events[index].value.type == RE_VALUE_STRING ? window->events[index].value.as.string.size : sizeof(re_value_t));
        if (item > SIZE_MAX - size) return RE_STATUS_LIMIT;
        size += item;
    }
    data = re_alloc(&window->allocator, size); if (data == NULL) return RE_STATUS_OUT_OF_MEMORY;
    memcpy(data, &window->watermark, 8u); memcpy(data + 8u, &window->count, 8u); index = 16u;
    for (size_t event_index = 0u; event_index < window->count; ++event_index) {
        const re_stream_event_impl_t *event = &window->events[event_index];
        uint64_t value_size = event->value.type == RE_VALUE_STRING ? event->value.as.string.size : sizeof(re_value_t);
        memcpy(data + index, &event->timestamp, 8u); index += 8u; memcpy(data + index, &event->name_size, 8u); index += 8u;
        memcpy(data + index, &value_size, 8u); index += 8u; memcpy(data + index, &event->value.type, 4u); index += 4u;
        memcpy(data + index, event->name, event->name_size); index += event->name_size;
        if (event->value.type == RE_VALUE_STRING) memcpy(data + index, event->value.as.string.data, value_size);
        else memcpy(data + index, &event->value, value_size);
        index += value_size;
    }
    {
        snapshot_release_context_t *release_context = re_alloc(&window->allocator, sizeof(*release_context));
        if (release_context == NULL) { re_free(&window->allocator, data); return RE_STATUS_OUT_OF_MEMORY; }
        release_context->allocator = window->allocator;
        memset(out_snapshot, 0, sizeof(*out_snapshot)); out_snapshot->struct_size = sizeof(*out_snapshot); out_snapshot->format_version = 1u;
        out_snapshot->data = data; out_snapshot->size = size; out_snapshot->release = snapshot_release; out_snapshot->release_context = release_context;
    }
    return RE_STATUS_OK;
}
re_status_t re_stream_window_restore(re_stream_window_t *window, const re_snapshot_t *snapshot) {
    size_t index = 16u, event_index;
    uint64_t watermark, count;
    if (window == NULL || snapshot == NULL || snapshot->format_version != 1u || snapshot->data == NULL || snapshot->size < 16u) return RE_STATUS_INVALID_ARGUMENT;
    memcpy(&watermark, snapshot->data, 8u); memcpy(&count, snapshot->data + 8u, 8u);
    re_stream_window_t staged;
    if (count > window->options.max_events) return RE_STATUS_LIMIT;
    memset(&staged, 0, sizeof(staged)); staged.allocator = window->allocator; staged.options = window->options;
    for (event_index = 0u; event_index < count; ++event_index) {
        uint64_t timestamp, name_size, value_size;
        re_value_t value;
        if (snapshot->size - index < 28u) goto invalid;
        memcpy(&timestamp, snapshot->data + index, 8u); index += 8u; memcpy(&name_size, snapshot->data + index, 8u); index += 8u; memcpy(&value_size, snapshot->data + index, 8u); index += 8u;
        memcpy(&value.type, snapshot->data + index, 4u); index += 4u;
        if (name_size == 0u || name_size > snapshot->size - index || value_size > snapshot->size - index - name_size) goto invalid;
        index += name_size;
        if (value.type == RE_VALUE_STRING) value.as.string = (re_string_t){(const char *)snapshot->data + index, (size_t)value_size};
        else { if (value_size != sizeof(value) || (value.type != RE_VALUE_BOOL && value.type != RE_VALUE_INT64 && value.type != RE_VALUE_DOUBLE && value.type != RE_VALUE_NULL && value.type != RE_VALUE_UNKNOWN)) goto invalid; memcpy(&value, snapshot->data + index, sizeof(value)); }
        if (re_stream_window_record_v1(&staged, timestamp, (re_string_t){(const char *)snapshot->data + index - name_size, (size_t)name_size}, &value) != RE_STATUS_OK) goto invalid;
        index += value_size;
    }
    if (index != snapshot->size) goto invalid;
    for (event_index = 0u; event_index < window->count; ++event_index) stream_event_destroy(window, &window->events[event_index]);
    re_free(&window->allocator, window->events); window->events = staged.events; window->count = staged.count;
    window->capacity = staged.capacity; window->watermark = watermark; return RE_STATUS_OK;
invalid:
    for (event_index = 0u; event_index < staged.count; ++event_index) stream_event_destroy(&staged, &staged.events[event_index]);
    re_free(&staged.allocator, staged.events); return RE_STATUS_INVALID_ARGUMENT;
}
re_status_t re_engine_set_state_provider(re_engine_t *engine,
                                         const re_state_provider_descriptor_t *descriptor,
                                         re_state_provider_t **out_provider) {
    (void)engine;
    (void)descriptor;
    (void)out_provider;
    return unsupported();
}
re_status_t re_engine_set_state_provider_v1(re_engine_t *engine, const re_state_provider_options_t *options,
                                            const re_state_provider_descriptor_t *descriptor,
                                            re_state_provider_t **out_provider) {
    re_state_provider_t *provider;
    if (options != NULL && options->kind == RE_STATE_PROVIDER_REDIS) return RE_STATUS_NOT_SUPPORTED;
    if (engine == NULL || options == NULL || descriptor == NULL || out_provider == NULL ||
        options->struct_size < sizeof(*options) || options->abi_version != RE_STATE_PROVIDER_ABI_VERSION ||
        options->kind != RE_STATE_PROVIDER_CALLBACK || descriptor->struct_size < sizeof(*descriptor) ||
        descriptor->abi_version != RE_STATE_PROVIDER_ABI_VERSION || descriptor->get == NULL) return RE_STATUS_INVALID_ARGUMENT;
    provider = re_alloc(&engine->allocator, sizeof(*provider)); if (provider == NULL) return RE_STATUS_OUT_OF_MEMORY;
    memset(provider, 0, sizeof(*provider)); provider->allocator = engine->allocator; provider->descriptor = *descriptor;
    *out_provider = provider; return RE_STATUS_OK;
}
re_status_t re_state_provider_get(re_state_provider_t *provider, re_string_t key, re_value_t *out_value) {
    if (provider == NULL || out_value == NULL || provider->descriptor.get == NULL) return RE_STATUS_INVALID_ARGUMENT;
    return provider->descriptor.get(provider, key, out_value, provider->descriptor.context);
}
re_status_t re_state_provider_put(re_state_provider_t *provider, re_string_t key, const re_value_t *value, uint64_t ttl_ms) {
    if (provider == NULL || value == NULL || provider->descriptor.put == NULL) return RE_STATUS_INVALID_ARGUMENT;
    return provider->descriptor.put(provider, key, value, ttl_ms, provider->descriptor.context);
}
re_status_t re_state_provider_delete(re_state_provider_t *provider, re_string_t key) {
    if (provider == NULL || provider->descriptor.delete_key == NULL) return RE_STATUS_INVALID_ARGUMENT;
    return provider->descriptor.delete_key(provider, key, provider->descriptor.context);
}
re_status_t re_state_provider_ttl(re_state_provider_t *provider, re_string_t key, uint64_t *out_ttl_ms) {
    if (provider == NULL || out_ttl_ms == NULL || provider->descriptor.ttl == NULL) return RE_STATUS_INVALID_ARGUMENT;
    return provider->descriptor.ttl(provider, key, out_ttl_ms, provider->descriptor.context);
}
re_status_t re_state_provider_last_error(const re_state_provider_t *provider,
                                         re_provider_error_info_t *out_error) {
    if (provider == NULL || out_error == NULL || out_error->struct_size < sizeof(*out_error)) return RE_STATUS_INVALID_ARGUMENT;
    *out_error = provider->last_error;
    out_error->struct_size = sizeof(*out_error);
    return RE_STATUS_OK;
}
void re_state_provider_destroy(re_state_provider_t *provider) {
    if (provider == NULL) return;
    if (provider->descriptor.release != NULL) provider->descriptor.release(provider->descriptor.context);
    re_free(&provider->allocator, provider);
}
re_status_t re_engine_executor_create(re_engine_t *engine,
                                      const re_concurrency_options_t *options,
                                      re_executor_t **out_executor) {
#if defined(RE_ENABLE_C11_PARALLEL)
    return re_executor_create_impl(engine, options, out_executor);
#else
    (void)engine; (void)options; (void)out_executor;
    return unsupported();
#endif
}
void re_executor_destroy(re_executor_t *executor) {
#if defined(RE_ENABLE_C11_PARALLEL)
    re_executor_destroy_impl(executor);
#else
    (void)executor;
#endif
}
