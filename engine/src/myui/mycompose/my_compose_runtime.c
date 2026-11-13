#include <myui/mycompose/my_compose_internal.h>
#include <myui/mycompose/my_compose_runtime.h>

#include <stdlib.h>

struct MyComposeRuntime {
    MyComposeTreeBuilder *builder;
    MyComposeRuntimeConfig config;
    bool pending_view;
    bool pumping;
};

static MyComposeStatus pump_result(MyComposeRuntime *runtime,
    MyComposeStatus status) {
    runtime->pumping = false;
    return status;
}

static MyComposeStatus reconcile_failure(MyComposeRuntime *runtime,
    MyComposeStatus status, bool rollback) {
    runtime->pending_view = true;
    runtime->config.store->diagnostics.reconcile_failures++;
    if (rollback) {
        runtime->config.store->diagnostics.rollbacks++;
        runtime->config.sink.rollback(runtime->config.sink.context);
    }
    return status;
}

static MyComposeStatus render_current(MyComposeRuntime *runtime) {
    const void *state = NULL;
    uint32_t state_size = 0u;
    MyComposeStore *store = runtime->config.store;
    MyComposeStatus status = my_compose_store_state(store, &state, &state_size);
    if (status != MY_COMPOSE_OK) return reconcile_failure(runtime, status, false);
    status = my_compose_tree_builder_begin(runtime->builder);
    if (status != MY_COMPOSE_OK) return reconcile_failure(runtime, status, false);
    status = runtime->config.view(runtime->config.view_context, runtime->builder,
        state, state_size);
    if (status != MY_COMPOSE_OK) return reconcile_failure(runtime, status, false);
    status = my_compose_tree_builder_end(runtime->builder);
    if (status != MY_COMPOSE_OK) return reconcile_failure(runtime, status, false);
    status = runtime->config.sink.stage(runtime->config.sink.context,
        my_compose_tree_builder_diff(runtime->builder));
    if (status != MY_COMPOSE_OK) return reconcile_failure(runtime, status, true);
    status = my_compose_tree_builder_finalize(runtime->builder);
    if (status != MY_COMPOSE_OK) return reconcile_failure(runtime, status, true);
    runtime->config.sink.commit(runtime->config.sink.context);
    runtime->pending_view = false;
    return MY_COMPOSE_OK;
}

MyComposeRuntime *my_compose_runtime_create(MyComposeTreeBuilder *builder,
    const MyComposeRuntimeConfig *config) {
    MyComposeRuntime *runtime;
    if (builder == NULL || config == NULL || config->store == NULL ||
        config->view == NULL || config->sink.store != config->store ||
        config->sink.stage == NULL || config->sink.commit == NULL ||
        config->sink.rollback == NULL ||
        !platform_thread_id_equal(platform_thread_current_id(),
            config->store->owner_thread)) {
        return NULL;
    }
    runtime = calloc(1u, sizeof(*runtime));
    if (runtime == NULL) return NULL;
    runtime->builder = builder;
    runtime->config = *config;
    runtime->pending_view = true;
    return runtime;
}

void my_compose_runtime_destroy(MyComposeRuntime *runtime) {
    if (runtime == NULL) return;
    my_compose_store_close(runtime->config.store);
    my_compose_store_reap(runtime->config.store);
    free(runtime);
}

MyComposeStatus my_compose_runtime_pump(MyComposeRuntime *runtime) {
    uint32_t processed = 0u;
    uint32_t converted = 0u;
    MyComposeStore *store;
    if (runtime == NULL) return MY_COMPOSE_INVALID;
    if (!platform_thread_id_equal(platform_thread_current_id(),
            runtime->config.store->owner_thread) ||
        runtime->pumping || runtime->config.store->event_callback_depth != 0u) {
        return MY_COMPOSE_CONFLICT;
    }
    runtime->pumping = true;
    store = runtime->config.store;
    my_compose_store_reap(store);
    if (store->closed) return pump_result(runtime, MY_COMPOSE_CANCELLED);
    if (runtime->pending_view) {
        MyComposeStatus status = render_current(runtime);
        if (status != MY_COMPOSE_OK) return pump_result(runtime, status);
        return pump_result(runtime, my_compose_store_dispatch_effects(store));
    }
    while (processed < MY_COMPOSE_INTENT_CAPACITY) {
        bool reduced = false;
        MyComposeStatus status = my_compose_store_reduce_one(store, &converted,
            &reduced);
        if (status != MY_COMPOSE_OK) return pump_result(runtime, status);
        if (!reduced) break;
        processed++;
        status = render_current(runtime);
        if (status != MY_COMPOSE_OK) return pump_result(runtime, status);
        status = my_compose_store_dispatch_effects(store);
        if (status != MY_COMPOSE_OK) return pump_result(runtime, status);
    }
    if (store->intent_count > 0u || store->completion_count > 0u) {
        return pump_result(runtime, MY_COMPOSE_PENDING);
    }
    return pump_result(runtime, my_compose_store_dispatch_effects(store));
}

MyComposeStatus my_compose_runtime_restart(MyComposeRuntime *runtime) {
    MyComposeStatus status;
    if (runtime == NULL) return MY_COMPOSE_INVALID;
    if (!platform_thread_id_equal(platform_thread_current_id(),
            runtime->config.store->owner_thread) ||
        runtime->pumping || runtime->config.store->event_callback_depth != 0u) {
        return MY_COMPOSE_CONFLICT;
    }
    status = my_compose_store_restart(runtime->config.store);
    my_compose_store_reap(runtime->config.store);
    return status;
}

bool my_compose_runtime_internal_matches(const MyComposeRuntime *runtime,
    const MyComposeStore *store, const void *sink_context) {
    return runtime != NULL && runtime->config.store == store &&
        runtime->config.sink.context == sink_context;
}
