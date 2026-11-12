#include <myui/mycompose/my_compose_internal.h>
#include <myui/mycompose/my_compose_store.h>

#include <limits.h>
#include <stdatomic.h>
#include <stdlib.h>
#include <string.h>

typedef struct MyComposeAsyncBridge {
    atomic_uint references;
    atomic_bool closed;
    MyComposeAsyncBridgeOps ops;
} MyComposeAsyncBridge;

typedef struct MyComposeCompletionPool {
    atomic_uint references;
    MyComposeCompletionContext *contexts;
} MyComposeCompletionPool;

struct MyComposeCompletionContext {
    atomic_uint references;
    atomic_int state;
    atomic_int delivery;
    MyComposeCompletionPool *pool;
    MyComposeAsyncBridge *bridge;
    MyComposeCompletion completion;
    uint8_t payload[MY_COMPOSE_MESSAGE_BYTES];
};

static bool atomic_retain(atomic_uint *references) {
    unsigned int current = atomic_load_explicit(references, memory_order_relaxed);
    for (;;) {
        if (current == 0u || current == UINT_MAX) return false;
        if (atomic_compare_exchange_weak_explicit(references, &current,
                current + 1u, memory_order_relaxed, memory_order_relaxed)) {
            return true;
        }
    }
}

static bool atomic_release(atomic_uint *references) {
    unsigned int current = atomic_load_explicit(references, memory_order_acquire);
    for (;;) {
        if (current == 0u || current == UINT_MAX) return false;
        if (atomic_compare_exchange_weak_explicit(references, &current,
                current - 1u, memory_order_acq_rel, memory_order_acquire)) {
            return current == 1u;
        }
    }
}

static void bridge_unref(MyComposeAsyncBridge *bridge) {
    if (bridge == NULL || !atomic_release(&bridge->references)) return;
    bridge->ops.destroy(bridge->ops.context);
    free(bridge);
}

static bool bridge_ref(MyComposeAsyncBridge *bridge) {
    return bridge == NULL || atomic_retain(&bridge->references);
}

static void bridge_close(MyComposeAsyncBridge *bridge) {
    if (bridge == NULL || atomic_exchange_explicit(&bridge->closed, true,
            memory_order_acq_rel)) {
        return;
    }
    bridge->ops.close(bridge->ops.context);
}

static void pool_unref(MyComposeCompletionPool *pool) {
    if (pool == NULL || !atomic_release(&pool->references)) return;
    free(pool->contexts);
    free(pool);
}

static bool pool_ref(MyComposeCompletionPool *pool) {
    return pool != NULL && atomic_retain(&pool->references);
}

static MyComposeCompletionState completion_state_from_delivery(int delivery) {
    switch (delivery) {
        case MY_COMPOSE_OK: return MY_COMPOSE_COMPLETION_ACCEPTED;
        case MY_COMPOSE_PENDING: return MY_COMPOSE_COMPLETION_PENDING;
        case MY_COMPOSE_CANCELLED:
        case MY_COMPOSE_FAILED: return MY_COMPOSE_COMPLETION_CANCELLED;
        case MY_COMPOSE_STALE: return MY_COMPOSE_COMPLETION_STALE;
        default: return MY_COMPOSE_COMPLETION_RETRY;
    }
}

static MyComposeStatus completion_delivery_from_state(
    MyComposeCompletionState state) {
    switch (state) {
        case MY_COMPOSE_COMPLETION_ACCEPTED: return MY_COMPOSE_OK;
        case MY_COMPOSE_COMPLETION_PENDING: return MY_COMPOSE_PENDING;
        case MY_COMPOSE_COMPLETION_CANCELLED: return MY_COMPOSE_CANCELLED;
        case MY_COMPOSE_COMPLETION_STALE: return MY_COMPOSE_STALE;
        default: return MY_COMPOSE_OVERLOAD;
    }
}

static void completion_transition(MyComposeCompletionContext *completion,
    MyComposeCompletionState target) {
    int current_delivery;
    MyComposeStatus target_delivery = completion_delivery_from_state(target);
    if (completion == NULL) return;
    current_delivery = atomic_load_explicit(&completion->delivery,
        memory_order_acquire);
    for (;;) {
        MyComposeCompletionState current =
            completion_state_from_delivery(current_delivery);
        if (current == MY_COMPOSE_COMPLETION_ACCEPTED ||
            current == MY_COMPOSE_COMPLETION_CANCELLED ||
            current == MY_COMPOSE_COMPLETION_STALE ||
            (target == MY_COMPOSE_COMPLETION_RETRY &&
                current == MY_COMPOSE_COMPLETION_RETRY)) {
            return;
        }
        if (atomic_compare_exchange_weak_explicit(&completion->delivery,
                &current_delivery, target_delivery, memory_order_acq_rel,
                memory_order_acquire)) {
            atomic_store_explicit(&completion->state, target, memory_order_release);
            return;
        }
    }
}

MyComposeCompletionContext *my_compose_completion_ref(
    MyComposeCompletionContext *completion) {
    if (completion == NULL || !atomic_retain(&completion->references)) return NULL;
    return completion;
}

void my_compose_completion_unref(MyComposeCompletionContext *completion) {
    MyComposeCompletionPool *pool;
    MyComposeAsyncBridge *bridge;
    if (completion == NULL) return;
    pool = completion->pool;
    bridge = completion->bridge;
    if (!atomic_release(&completion->references)) return;
    bridge_unref(bridge);
    pool_unref(pool);
}

MyComposeCompletionState my_compose_completion_state(
    const MyComposeCompletionContext *completion) {
    if (completion == NULL) return MY_COMPOSE_COMPLETION_STALE;
    return completion_state_from_delivery(atomic_load_explicit(
        (atomic_int *)&completion->delivery, memory_order_acquire));
}

MyComposeStatus my_compose_completion_delivery(
    const MyComposeCompletionContext *completion) {
    if (completion == NULL) return MY_COMPOSE_STALE;
    return (MyComposeStatus)atomic_load_explicit(
        (atomic_int *)&completion->delivery, memory_order_acquire);
}

void my_compose_completion_abandon(MyComposeCompletionContext *completion,
    MyComposeStatus status) {
    if (status == MY_COMPOSE_STALE) {
        completion_transition(completion, MY_COMPOSE_COMPLETION_STALE);
    } else if (status == MY_COMPOSE_CANCELLED || status == MY_COMPOSE_FAILED) {
        completion_transition(completion, MY_COMPOSE_COMPLETION_CANCELLED);
    }
}

static void update_high_water(uint32_t *high_water, uint32_t value) {
    if (value > *high_water) *high_water = value;
}

static void sync_diagnostics(MyComposeStore *store) {
    store->diagnostics.pending_intents = store->intent_count;
    store->diagnostics.outbox_effects = store->outbox_count;
    store->diagnostics.outstanding_effects = store->outstanding_count;
    store->diagnostics.queued_completions = store->completion_count;
    store->diagnostics.request_count = store->request_count;
}

static bool owner_is_zero(MyComposeNodeHandle owner) {
    return owner.index == 0u && owner.generation == 0u;
}

static bool owner_matches(MyComposeNodeHandle a, MyComposeNodeHandle b) {
    return a.index == b.index && a.generation == b.generation;
}

static MyComposeStatus owner_status(const MyComposeStore *store,
    MyComposeNodeHandle owner) {
    const MyComposeOwner *entry;
    if (owner_is_zero(owner)) return MY_COMPOSE_OK;
    if (owner.index >= MY_COMPOSE_MAX_NODES || owner.generation == 0u) {
        return MY_COMPOSE_INVALID;
    }
    entry = &store->owners[owner.index];
    if (entry->retired || !entry->active || entry->generation != owner.generation) {
        return MY_COMPOSE_STALE;
    }
    return MY_COMPOSE_OK;
}

static void dispose_state_slot(MyComposeStore *store, uint32_t slot) {
    if (!store->state_engaged[slot]) return;
    if (store->state_ops.dispose != NULL) {
        store->state_ops.dispose(store->state_ops.context,
            store->state_slots[slot].bytes, store->state_sizes[slot]);
    }
    store->state_engaged[slot] = false;
    store->state_sizes[slot] = 0u;
}

static MyComposeStatus clone_state(MyComposeStore *store, const void *source,
    uint32_t source_size, uint32_t destination) {
    MyComposeStatus status;
    uint32_t output_size = 0u;
    dispose_state_slot(store, destination);
    if (store->state_ops.clone != NULL) {
        status = store->state_ops.clone(store->state_ops.context, source,
            source_size, store->state_slots[destination].bytes,
            MY_COMPOSE_STATE_BYTES, &output_size);
    } else {
        if (source_size > MY_COMPOSE_STATE_BYTES) return MY_COMPOSE_OVERLOAD;
        memcpy(store->state_slots[destination].bytes, source, source_size);
        output_size = source_size;
        status = MY_COMPOSE_OK;
    }
    if (status != MY_COMPOSE_OK) return status;
    store->state_engaged[destination] = true;
    store->state_sizes[destination] = output_size;
    if (output_size == 0u) {
        dispose_state_slot(store, destination);
        return MY_COMPOSE_INVALID;
    }
    if (output_size > MY_COMPOSE_STATE_BYTES) {
        dispose_state_slot(store, destination);
        return MY_COMPOSE_OVERLOAD;
    }
    return MY_COMPOSE_OK;
}

static void release_request(MyComposeStore *store, uint32_t slot) {
    MyComposeRequest *request = &store->requests[slot];
    MyComposeCompletionContext *completion;
    if (!request->used) return;
    if (request->location == MY_COMPOSE_REQUEST_OUTSTANDING) {
        store->outstanding_count--;
    }
    completion = request->completion;
    request->completion = NULL;
    request->effect.completion = NULL;
    request->used = false;
    request->terminal = MY_COMPOSE_OK;
    store->request_count--;
    my_compose_completion_unref(completion);
}

static void reap_requests(MyComposeStore *store) {
    uint32_t old_outbox_count = store->outbox_count;
    uint32_t old_head = store->outbox_head;
    uint32_t kept[MY_COMPOSE_EFFECT_CAPACITY];
    uint32_t kept_count = 0u;
    for (uint32_t i = 0u; i < MY_COMPOSE_EFFECT_CAPACITY; ++i) {
        MyComposeRequest *request = &store->requests[i];
        MyComposeCompletionState state;
        if (!request->used) continue;
        state = request->completion != NULL ?
            my_compose_completion_state(request->completion) :
            MY_COMPOSE_COMPLETION_PENDING;
        if (request->terminal == MY_COMPOSE_OK ||
            request->terminal == MY_COMPOSE_PENDING) {
            if (state == MY_COMPOSE_COMPLETION_CANCELLED) {
                request->terminal = MY_COMPOSE_CANCELLED;
            } else if (state == MY_COMPOSE_COMPLETION_STALE) {
                request->terminal = MY_COMPOSE_STALE;
            }
        }
        if (request->terminal != MY_COMPOSE_OK &&
            request->terminal != MY_COMPOSE_PENDING &&
            (request->location == MY_COMPOSE_REQUEST_OUTSTANDING ||
                request->terminal != MY_COMPOSE_STALE)) {
            release_request(store, i);
            store->diagnostics.recycled_requests++;
        }
    }
    for (uint32_t i = 0u; i < old_outbox_count; ++i) {
        uint32_t slot = store->outbox[(old_head + i) % MY_COMPOSE_EFFECT_CAPACITY];
        MyComposeRequest *request = &store->requests[slot];
        if (request->used && request->location == MY_COMPOSE_REQUEST_OUTBOX &&
            (request->terminal == MY_COMPOSE_OK ||
                request->terminal == MY_COMPOSE_STALE)) {
            kept[kept_count++] = slot;
        }
    }
    if (kept_count > 0u) {
        memcpy(store->outbox, kept, kept_count * sizeof(kept[0]));
    }
    store->outbox_head = 0u;
    store->outbox_count = kept_count;
    sync_diagnostics(store);
}

static void cancel_requests(MyComposeStore *store) {
    for (uint32_t i = 0u; i < MY_COMPOSE_EFFECT_CAPACITY; ++i) {
        if (store->requests[i].used) {
            store->requests[i].terminal = MY_COMPOSE_CANCELLED;
            completion_transition(store->requests[i].completion,
                MY_COMPOSE_COMPLETION_CANCELLED);
        }
    }
}

static void clear_pending(MyComposeStore *store) {
    store->intent_head = 0u;
    store->intent_count = 0u;
    store->completion_head = 0u;
    store->completion_count = 0u;
}

static uint32_t find_request(MyComposeStore *store, uint64_t request_id) {
    if (request_id == 0u) return MY_COMPOSE_NO_INDEX;
    for (uint32_t i = 0u; i < MY_COMPOSE_EFFECT_CAPACITY; ++i) {
        if (store->requests[i].used &&
            store->requests[i].effect.request_id == request_id) {
            return i;
        }
    }
    return MY_COMPOSE_NO_INDEX;
}

static MyComposeStatus prepare_completion(MyComposeStore *store,
    MyComposeRequest *request) {
    MyComposeCompletionPool *pool = store->completion_pool;
    if (pool == NULL) return MY_COMPOSE_FAILED;
    for (uint32_t i = 0u; i < MY_COMPOSE_EFFECT_CAPACITY; ++i) {
        MyComposeCompletionContext *completion = &pool->contexts[i];
        unsigned int expected = 0u;
        if (!atomic_compare_exchange_strong_explicit(&completion->references,
                &expected, 1u, memory_order_acq_rel, memory_order_acquire)) {
            continue;
        }
        if (!pool_ref(pool) || !bridge_ref(store->async_bridge)) {
            completion->pool = pool;
            completion->bridge = NULL;
            atomic_store_explicit(&completion->references, 0u,
                memory_order_release);
            pool_unref(pool);
            return MY_COMPOSE_FAILED;
        }
        completion->pool = pool;
        completion->bridge = store->async_bridge;
        memset(&completion->completion, 0, sizeof(completion->completion));
        completion->completion.type = request->effect.type;
        completion->completion.payload_size = request->effect.payload_size;
        completion->completion.owner = request->effect.owner;
        completion->completion.store_generation = request->effect.store_generation;
        completion->completion.request_id = request->effect.request_id;
        completion->completion.delivery = MY_COMPOSE_OK;
        if (request->effect.payload_size > 0u) {
            memcpy(completion->payload, request->effect.payload,
                request->effect.payload_size);
        }
        completion->completion.payload = completion->payload;
        atomic_store_explicit(&completion->delivery, MY_COMPOSE_PENDING,
            memory_order_release);
        atomic_store_explicit(&completion->state, MY_COMPOSE_COMPLETION_PENDING,
            memory_order_release);
        if (request->terminal == MY_COMPOSE_STALE) {
            completion_transition(completion, MY_COMPOSE_COMPLETION_STALE);
        } else if (request->terminal == MY_COMPOSE_CANCELLED) {
            completion_transition(completion, MY_COMPOSE_COMPLETION_CANCELLED);
        }
        request->completion = completion;
        request->effect.completion = completion;
        return MY_COMPOSE_OK;
    }
    return MY_COMPOSE_OVERLOAD;
}

static void async_deliver(void *opaque,
    MyComposeCompletionContext *completion, uint32_t result) {
    MyComposeStore *store = opaque;
    MyComposeCompletion delivered;
    MyComposeStatus status;
    uint32_t slot;
    if (store == NULL || store->closed) {
        completion_transition(completion, MY_COMPOSE_COMPLETION_CANCELLED);
        return;
    }
    slot = find_request(store, completion->completion.request_id);
    if (slot == MY_COMPOSE_NO_INDEX ||
        store->requests[slot].completion != completion) {
        completion_transition(completion, MY_COMPOSE_COMPLETION_STALE);
        return;
    }
    delivered = completion->completion;
    delivered.result = result;
    delivered.delivery = MY_COMPOSE_OK;
    status = my_compose_store_complete(store, &delivered);
    if (status == MY_COMPOSE_OK) {
        completion_transition(completion, MY_COMPOSE_COMPLETION_ACCEPTED);
    } else if (status == MY_COMPOSE_OVERLOAD || status == MY_COMPOSE_PENDING) {
        completion_transition(completion, MY_COMPOSE_COMPLETION_RETRY);
    } else if (status == MY_COMPOSE_STALE) {
        completion_transition(completion, MY_COMPOSE_COMPLETION_STALE);
    } else {
        completion_transition(completion, MY_COMPOSE_COMPLETION_CANCELLED);
    }
}

MyComposeStatus my_compose_completion_post(
    MyComposeCompletionContext *completion, uint32_t result) {
    MyComposeAsyncBridge *bridge;
    MyComposeCompletionState state;
    MyComposeStatus status;
    if (completion == NULL) return MY_COMPOSE_INVALID;
    state = my_compose_completion_state(completion);
    if (state == MY_COMPOSE_COMPLETION_ACCEPTED) return MY_COMPOSE_STALE;
    if (state == MY_COMPOSE_COMPLETION_STALE) return MY_COMPOSE_STALE;
    if (state == MY_COMPOSE_COMPLETION_CANCELLED) return MY_COMPOSE_CANCELLED;
    bridge = completion->bridge;
    if (bridge == NULL || bridge->ops.post == NULL) {
        completion_transition(completion, MY_COMPOSE_COMPLETION_RETRY);
        return MY_COMPOSE_NOT_SUPPORTED;
    }
    if (atomic_load_explicit(&bridge->closed, memory_order_acquire)) {
        completion_transition(completion, MY_COMPOSE_COMPLETION_CANCELLED);
        return MY_COMPOSE_CANCELLED;
    }
    if (my_compose_completion_ref(completion) == NULL) return MY_COMPOSE_STALE;
    status = bridge->ops.post(bridge->ops.context, async_deliver, completion,
        result, my_compose_completion_unref);
    if (status != MY_COMPOSE_OK) {
        if (status == MY_COMPOSE_STALE) {
            completion_transition(completion, MY_COMPOSE_COMPLETION_STALE);
        } else if (status == MY_COMPOSE_CANCELLED) {
            completion_transition(completion, MY_COMPOSE_COMPLETION_CANCELLED);
        } else {
            completion_transition(completion, MY_COMPOSE_COMPLETION_RETRY);
        }
    }
    return status;
}

static void mark_owner_requests(MyComposeStore *store,
    MyComposeNodeHandle owner, bool previous_generations) {
    for (uint32_t i = 0u; i < MY_COMPOSE_EFFECT_CAPACITY; ++i) {
        MyComposeRequest *request = &store->requests[i];
        if (!request->used || request->effect.owner.index != owner.index) continue;
        if ((previous_generations &&
                request->effect.owner.generation < owner.generation) ||
            (!previous_generations &&
                owner_matches(request->effect.owner, owner))) {
            request->terminal = MY_COMPOSE_STALE;
            completion_transition(request->completion,
                MY_COMPOSE_COMPLETION_STALE);
        }
    }
}

static MyComposeStatus reject_intent(MyComposeStore *store,
    MyComposeStatus status) {
    store->diagnostics.rejected_intents++;
    sync_diagnostics(store);
    return status;
}

static MyComposeStatus fail_candidate(MyComposeStore *store,
    uint32_t candidate, MyComposeStatus status) {
    dispose_state_slot(store, candidate);
    store->diagnostics.rejected_intents++;
    if (status == MY_COMPOSE_OVERLOAD) store->diagnostics.effect_overloads++;
    sync_diagnostics(store);
    return status;
}

static MyComposeStatus reduce_one(MyComposeStore *store) {
    MyComposeStoredIntent *stored = &store->intents[store->intent_head];
    const MyComposeIntent *intent = &stored->intent;
    uint32_t candidate = 1u - store->current_state;
    uint32_t current = store->current_state;
    uint32_t candidate_size;
    uint32_t request_slots[MY_COMPOSE_MAX_EFFECTS_PER_INTENT];
    uint32_t found = 0u;
    MyComposeEffectBatch batch;
    MyComposeStatus status = owner_status(store, intent->owner);
    if (status != MY_COMPOSE_OK) {
        store->intent_head = (store->intent_head + 1u) %
            MY_COMPOSE_INTENT_CAPACITY;
        store->intent_count--;
        return reject_intent(store, status);
    }
    status = clone_state(store, store->state_slots[current].bytes,
        store->state_sizes[current], candidate);
    if (status != MY_COMPOSE_OK) return reject_intent(store, status);
    candidate_size = store->state_sizes[candidate];
    memset(&batch, 0, sizeof(batch));
    status = store->reducer(store->reducer_context, intent,
        store->state_slots[current].bytes, store->state_sizes[current],
        store->state_slots[candidate].bytes, &candidate_size, &batch);
    if (status != MY_COMPOSE_OK) {
        dispose_state_slot(store, candidate);
        store->diagnostics.reducer_failures++;
        return reject_intent(store, status);
    }
    if (candidate_size == 0u) return fail_candidate(store, candidate,
        MY_COMPOSE_INVALID);
    if (candidate_size > MY_COMPOSE_STATE_BYTES) {
        return fail_candidate(store, candidate, MY_COMPOSE_OVERLOAD);
    }
    store->state_sizes[candidate] = candidate_size;
    if (batch.status != MY_COMPOSE_OK) {
        return fail_candidate(store, candidate, batch.status);
    }
    if (batch.count > MY_COMPOSE_MAX_EFFECTS_PER_INTENT) {
        return fail_candidate(store, candidate, MY_COMPOSE_OVERLOAD);
    }
    for (uint32_t i = 0u; i < batch.count; ++i) {
        if (batch.effects[i].payload_size > MY_COMPOSE_MESSAGE_BYTES) {
            return fail_candidate(store, candidate, MY_COMPOSE_OVERLOAD);
        }
    }
    if (batch.count > MY_COMPOSE_EFFECT_CAPACITY - store->request_count) {
        return fail_candidate(store, candidate, MY_COMPOSE_OVERLOAD);
    }
    if (batch.count > 0u &&
        (store->generation == UINT32_MAX ||
            store->next_request_id == UINT64_MAX ||
            (uint64_t)batch.count > UINT64_MAX - store->next_request_id)) {
        return fail_candidate(store, candidate, MY_COMPOSE_OVERLOAD);
    }
    for (uint32_t i = 0u;
         i < MY_COMPOSE_EFFECT_CAPACITY && found < batch.count; ++i) {
        if (!store->requests[i].used) request_slots[found++] = i;
    }
    if (found != batch.count) {
        return fail_candidate(store, candidate, MY_COMPOSE_OVERLOAD);
    }

    store->state_sizes[candidate] = candidate_size;
    store->current_state = candidate;
    for (uint32_t i = 0u; i < batch.count; ++i) {
        uint32_t slot = request_slots[i];
        MyComposeRequest *request = &store->requests[slot];
        memset(request, 0, sizeof(*request));
        request->used = true;
        request->location = MY_COMPOSE_REQUEST_OUTBOX;
        request->terminal = MY_COMPOSE_OK;
        request->effect = batch.effects[i];
        memcpy(request->payload, batch.payload_storage[i],
            request->effect.payload_size);
        request->effect.payload = request->payload;
        request->effect.owner = intent->owner;
        request->effect.store_generation = store->generation;
        request->effect.request_id = store->next_request_id++;
        store->outbox[(store->outbox_head + store->outbox_count) %
            MY_COMPOSE_EFFECT_CAPACITY] = slot;
        store->outbox_count++;
        store->request_count++;
    }
    update_high_water(&store->diagnostics.effect_high_water,
        store->request_count);
    sync_diagnostics(store);
    return MY_COMPOSE_OK;
}

MyComposeStore *my_compose_store_create(const void *initial_state,
    uint32_t initial_state_size, const MyComposeStateOps *state_ops,
    void *reducer_context, MyComposeReducer reducer, void *executor_context,
    MyComposeExecutor executor) {
    MyComposeStore *store;
    MyComposeStatus status;
    if (initial_state == NULL || initial_state_size == 0u ||
        initial_state_size > MY_COMPOSE_STATE_BYTES || reducer == NULL) {
        return NULL;
    }
    store = calloc(1u, sizeof(*store));
    if (store == NULL) return NULL;
    store->completion_pool = calloc(1u, sizeof(*store->completion_pool));
    if (store->completion_pool == NULL) {
        free(store);
        return NULL;
    }
    store->completion_pool->contexts = calloc(MY_COMPOSE_EFFECT_CAPACITY,
        sizeof(*store->completion_pool->contexts));
    if (store->completion_pool->contexts == NULL) {
        free(store->completion_pool);
        free(store);
        return NULL;
    }
    atomic_init(&store->completion_pool->references, 1u);
    if (state_ops != NULL) store->state_ops = *state_ops;
    store->reducer_context = reducer_context;
    store->reducer = reducer;
    store->executor_context = executor_context;
    store->executor = executor;
    store->owner_thread = thrd_current();
    store->generation = 1u;
    store->next_request_id = 1u;
    status = clone_state(store, initial_state, initial_state_size, 0u);
    if (status != MY_COMPOSE_OK) {
        pool_unref(store->completion_pool);
        free(store);
        return NULL;
    }
    store->current_state = 0u;
    sync_diagnostics(store);
    return store;
}

MyComposeStatus my_compose_store_set_async_bridge(MyComposeStore *store,
    const MyComposeAsyncBridgeOps *ops) {
    MyComposeAsyncBridge *bridge;
    if (store == NULL || ops == NULL || ops->post == NULL ||
        ops->close == NULL || ops->destroy == NULL) {
        return MY_COMPOSE_INVALID;
    }
    if (store->closed) return MY_COMPOSE_CANCELLED;
    if (store->async_bridge != NULL) return MY_COMPOSE_CONFLICT;
    bridge = calloc(1u, sizeof(*bridge));
    if (bridge == NULL) return MY_COMPOSE_OVERLOAD;
    atomic_init(&bridge->references, 1u);
    atomic_init(&bridge->closed, false);
    bridge->ops = *ops;
    store->async_bridge = bridge;
    return MY_COMPOSE_OK;
}

void my_compose_store_destroy(MyComposeStore *store) {
    if (store == NULL) return;
    my_compose_store_close(store);
    reap_requests(store);
    bridge_unref(store->async_bridge);
    store->async_bridge = NULL;
    pool_unref(store->completion_pool);
    store->completion_pool = NULL;
    dispose_state_slot(store, 0u);
    dispose_state_slot(store, 1u);
    free(store);
}

MyComposeStatus my_compose_store_dispatch(MyComposeStore *store,
    const MyComposeIntent *intent) {
    MyComposeStoredIntent *stored;
    MyComposeStatus status;
    if (store == NULL || intent == NULL) return MY_COMPOSE_INVALID;
    if (!thrd_equal(thrd_current(), store->owner_thread)) {
        return MY_COMPOSE_CONFLICT;
    }
    if (store->closed) return reject_intent(store, MY_COMPOSE_CANCELLED);
    if (store->generation == UINT32_MAX) {
        return reject_intent(store, MY_COMPOSE_OVERLOAD);
    }
    if (intent->payload_size > MY_COMPOSE_MESSAGE_BYTES) {
        return reject_intent(store, MY_COMPOSE_OVERLOAD);
    }
    if (intent->payload_size > 0u && intent->payload == NULL) {
        return reject_intent(store, MY_COMPOSE_INVALID);
    }
    status = owner_status(store, intent->owner);
    if (status != MY_COMPOSE_OK) return reject_intent(store, status);
    if (store->intent_count == MY_COMPOSE_INTENT_CAPACITY) {
        return reject_intent(store, MY_COMPOSE_OVERLOAD);
    }
    stored = &store->intents[(store->intent_head + store->intent_count) %
        MY_COMPOSE_INTENT_CAPACITY];
    memset(stored, 0, sizeof(*stored));
    stored->intent = *intent;
    if (intent->payload_size > 0u) {
        memcpy(stored->payload, intent->payload, intent->payload_size);
    }
    stored->intent.payload = stored->payload;
    store->intent_count++;
    store->diagnostics.accepted_intents++;
    update_high_water(&store->diagnostics.intent_high_water,
        store->intent_count);
    sync_diagnostics(store);
    return MY_COMPOSE_OK;
}

MyComposeStatus my_compose_store_complete(MyComposeStore *store,
    const MyComposeCompletion *completion) {
    MyComposeRequest *request;
    MyComposeStoredCompletion *stored;
    uint32_t slot;
    if (store == NULL || completion == NULL) return MY_COMPOSE_INVALID;
    if (!thrd_equal(thrd_current(), store->owner_thread)) {
        return MY_COMPOSE_CONFLICT;
    }
    if (store->closed) {
        store->diagnostics.stale_completions++;
        return MY_COMPOSE_STALE;
    }
    if (completion->payload_size > MY_COMPOSE_MESSAGE_BYTES) {
        return MY_COMPOSE_OVERLOAD;
    }
    if (completion->payload_size > 0u && completion->payload == NULL) {
        return MY_COMPOSE_INVALID;
    }
    slot = find_request(store, completion->request_id);
    if (slot == MY_COMPOSE_NO_INDEX) {
        store->diagnostics.stale_completions++;
        return MY_COMPOSE_STALE;
    }
    request = &store->requests[slot];
    if (request->location != MY_COMPOSE_REQUEST_OUTSTANDING ||
        (request->terminal != MY_COMPOSE_OK &&
            request->terminal != MY_COMPOSE_PENDING)) {
        store->diagnostics.stale_completions++;
        return MY_COMPOSE_STALE;
    }
    if (completion->store_generation != store->generation ||
        request->effect.store_generation != store->generation ||
        completion->store_generation != request->effect.store_generation ||
        !owner_matches(completion->owner, request->effect.owner) ||
        owner_status(store, request->effect.owner) != MY_COMPOSE_OK) {
        request->terminal = MY_COMPOSE_STALE;
        store->diagnostics.stale_completions++;
        return MY_COMPOSE_STALE;
    }
    if (completion->delivery == MY_COMPOSE_PENDING ||
        completion->delivery == MY_COMPOSE_OVERLOAD) {
        request->terminal = MY_COMPOSE_PENDING;
        return (MyComposeStatus)completion->delivery;
    }
    if (completion->delivery == MY_COMPOSE_STALE ||
        completion->delivery == MY_COMPOSE_CANCELLED ||
        completion->delivery == MY_COMPOSE_FAILED) {
        request->terminal = (MyComposeStatus)completion->delivery;
        if (completion->delivery == MY_COMPOSE_STALE) {
            store->diagnostics.stale_completions++;
        }
        return (MyComposeStatus)completion->delivery;
    }
    if (completion->delivery != MY_COMPOSE_OK) return MY_COMPOSE_INVALID;
    if (store->completion_count == MY_COMPOSE_COMPLETION_CAPACITY) {
        sync_diagnostics(store);
        return MY_COMPOSE_OVERLOAD;
    }
    stored = &store->completions[(store->completion_head +
        store->completion_count) % MY_COMPOSE_COMPLETION_CAPACITY];
    memset(stored, 0, sizeof(*stored));
    stored->completion = *completion;
    stored->completion.store_generation = request->effect.store_generation;
    stored->completion.owner = request->effect.owner;
    stored->completion.request_id = request->effect.request_id;
    if (completion->payload_size > 0u) {
        memcpy(stored->payload, completion->payload, completion->payload_size);
    }
    stored->completion.payload = stored->payload;
    release_request(store, slot);
    store->completion_count++;
    update_high_water(&store->diagnostics.completion_high_water,
        store->completion_count);
    sync_diagnostics(store);
    return MY_COMPOSE_OK;
}

MyComposeStatus my_compose_store_register_owner(MyComposeStore *store,
    MyComposeNodeHandle owner) {
    MyComposeOwner *entry;
    if (store == NULL || owner.index >= MY_COMPOSE_MAX_NODES ||
        owner.generation == 0u) {
        return MY_COMPOSE_INVALID;
    }
    if (store->closed) return MY_COMPOSE_CANCELLED;
    entry = &store->owners[owner.index];
    if (owner.generation == UINT32_MAX || entry->retired ||
        store->generation == UINT32_MAX) {
        return MY_COMPOSE_OVERLOAD;
    }
    if (entry->generation != 0u) {
        if (entry->active && entry->generation == owner.generation) {
            return MY_COMPOSE_OK;
        }
        if (owner.generation < entry->generation) return MY_COMPOSE_STALE;
    }
    mark_owner_requests(store, owner, true);
    entry->generation = owner.generation;
    entry->active = true;
    entry->retired = false;
    return MY_COMPOSE_OK;
}

MyComposeStatus my_compose_store_invalidate_owner(MyComposeStore *store,
    MyComposeNodeHandle owner) {
    MyComposeOwner *entry;
    if (store == NULL || owner.index >= MY_COMPOSE_MAX_NODES ||
        owner.generation == 0u) {
        return MY_COMPOSE_INVALID;
    }
    if (store->closed) return MY_COMPOSE_STALE;
    entry = &store->owners[owner.index];
    if (entry->retired || !entry->active || entry->generation != owner.generation) {
        return MY_COMPOSE_STALE;
    }
    mark_owner_requests(store, owner, false);
    entry->active = false;
    entry->generation++;
    if (entry->generation == UINT32_MAX) entry->retired = true;
    return MY_COMPOSE_OK;
}

static MyComposeStatus reduce_step(MyComposeStore *store,
    uint32_t *converted, bool *out_reduced) {
    MyComposeStatus status;
    *out_reduced = false;
    reap_requests(store);
    if (store->closed) return MY_COMPOSE_CANCELLED;
    if (store->generation == UINT32_MAX) return MY_COMPOSE_OVERLOAD;
    while (*converted < MY_COMPOSE_COMPLETION_CAPACITY &&
           store->completion_count > 0u &&
           store->intent_count < MY_COMPOSE_INTENT_CAPACITY) {
        MyComposeStoredCompletion completion =
            store->completions[store->completion_head];
        MyComposeStoredIntent *intent;
        store->completion_head = (store->completion_head + 1u) %
            MY_COMPOSE_COMPLETION_CAPACITY;
        store->completion_count--;
        if (completion.completion.store_generation != store->generation ||
            owner_status(store, completion.completion.owner) != MY_COMPOSE_OK) {
            store->diagnostics.stale_completions++;
            continue;
        }
        (*converted)++;
        intent = &store->intents[(store->intent_head + store->intent_count) %
            MY_COMPOSE_INTENT_CAPACITY];
        memset(intent, 0, sizeof(*intent));
        intent->intent.type = completion.completion.type;
        intent->intent.payload_size = completion.completion.payload_size;
        intent->intent.owner = completion.completion.owner;
        intent->intent.result = completion.completion.result;
        if (completion.completion.payload_size > 0u) {
            memcpy(intent->payload, completion.payload,
                completion.completion.payload_size);
        }
        intent->intent.payload = intent->payload;
        store->intent_count++;
        store->diagnostics.accepted_intents++;
        update_high_water(&store->diagnostics.intent_high_water,
            store->intent_count);
    }
    if (store->intent_count == 0u) {
        sync_diagnostics(store);
        return MY_COMPOSE_OK;
    }
    status = reduce_one(store);
    if (status != MY_COMPOSE_OK) {
        sync_diagnostics(store);
        return status;
    }
    store->intent_head = (store->intent_head + 1u) %
        MY_COMPOSE_INTENT_CAPACITY;
    store->intent_count--;
    *out_reduced = true;
    sync_diagnostics(store);
    return MY_COMPOSE_OK;
}

MyComposeStatus my_compose_store_reduce_one(MyComposeStore *store,
    uint32_t *completion_budget, bool *out_reduced) {
    if (store == NULL || completion_budget == NULL || out_reduced == NULL ||
        *completion_budget > MY_COMPOSE_COMPLETION_CAPACITY) {
        return MY_COMPOSE_INVALID;
    }
    return reduce_step(store, completion_budget, out_reduced);
}

MyComposeStatus my_compose_store_reduce(MyComposeStore *store) {
    uint32_t processed = 0u;
    uint32_t converted = 0u;
    if (store == NULL) return MY_COMPOSE_INVALID;
    while (processed < 64u) {
        bool reduced;
        MyComposeStatus status = reduce_step(store, &converted, &reduced);
        if (status != MY_COMPOSE_OK) return status;
        if (!reduced) break;
        processed++;
    }
    sync_diagnostics(store);
    if (store->intent_count > 0u || store->completion_count > 0u) {
        return MY_COMPOSE_PENDING;
    }
    return MY_COMPOSE_OK;
}

MyComposeStatus my_compose_store_dispatch_effects(MyComposeStore *store) {
    if (store == NULL) return MY_COMPOSE_INVALID;
    reap_requests(store);
    if (store->closed) return MY_COMPOSE_CANCELLED;
    while (store->outbox_count > 0u) {
        uint32_t slot = store->outbox[store->outbox_head];
        MyComposeRequest *request = &store->requests[slot];
        MyComposeStatus status;
        if (store->executor == NULL) return MY_COMPOSE_INVALID;
        if (request->completion == NULL) {
            status = prepare_completion(store, request);
            if (status != MY_COMPOSE_OK) {
                store->outbox_head = (store->outbox_head + 1u) %
                    MY_COMPOSE_EFFECT_CAPACITY;
                store->outbox_count--;
                release_request(store, slot);
                store->diagnostics.executor_failures++;
                sync_diagnostics(store);
                return status;
            }
        }
        status = store->executor(store->executor_context, &request->effect);
        if (status == MY_COMPOSE_PENDING) {
            sync_diagnostics(store);
            return MY_COMPOSE_PENDING;
        }
        store->outbox_head = (store->outbox_head + 1u) %
            MY_COMPOSE_EFFECT_CAPACITY;
        store->outbox_count--;
        if (status == MY_COMPOSE_OK) {
            request->location = MY_COMPOSE_REQUEST_OUTSTANDING;
            store->outstanding_count++;
            update_high_water(&store->diagnostics.outstanding_high_water,
                store->outstanding_count);
            continue;
        }
        release_request(store, slot);
        store->diagnostics.executor_failures++;
        sync_diagnostics(store);
        return status;
    }
    sync_diagnostics(store);
    return MY_COMPOSE_OK;
}

MyComposeStatus my_compose_store_restart(MyComposeStore *store) {
    if (store == NULL) return MY_COMPOSE_INVALID;
    if (store->closed) return MY_COMPOSE_CANCELLED;
    if (store->generation == UINT32_MAX) return MY_COMPOSE_OVERLOAD;
    clear_pending(store);
    cancel_requests(store);
    store->generation++;
    sync_diagnostics(store);
    return MY_COMPOSE_OK;
}

void my_compose_store_reap(MyComposeStore *store) {
    if (store == NULL) return;
    reap_requests(store);
}

void my_compose_store_close(MyComposeStore *store) {
    if (store == NULL) return;
    if (store->closed) {
        reap_requests(store);
        return;
    }
    bridge_close(store->async_bridge);
    clear_pending(store);
    cancel_requests(store);
    if (store->generation < UINT32_MAX) store->generation++;
    for (uint32_t i = 0u; i < MY_COMPOSE_MAX_NODES; ++i) {
        MyComposeOwner *entry = &store->owners[i];
        if (entry->generation > 0u && entry->generation < UINT32_MAX) {
            entry->generation++;
        }
        entry->active = false;
        if (entry->generation == UINT32_MAX) entry->retired = true;
    }
    store->closed = true;
    reap_requests(store);
    sync_diagnostics(store);
}

MyComposeStatus my_compose_store_state(const MyComposeStore *store,
    const void **out_state, uint32_t *out_size) {
    if (store == NULL || out_state == NULL || out_size == NULL) {
        return MY_COMPOSE_INVALID;
    }
    *out_state = store->state_slots[store->current_state].bytes;
    *out_size = store->state_sizes[store->current_state];
    return MY_COMPOSE_OK;
}

const MyComposeDiagnostics *my_compose_store_diagnostics(
    const MyComposeStore *store) {
    MyComposeStore *mutable_store = (MyComposeStore *)store;
    if (store == NULL) return NULL;
    sync_diagnostics(mutable_store);
    return &store->diagnostics;
}

MyComposeStatus my_compose_effect_batch_append(MyComposeEffectBatch *batch,
    uint32_t type, const void *payload, uint32_t payload_size) {
    MyComposeEffect *effect;
    uint32_t slot;
    if (batch == NULL) return MY_COMPOSE_INVALID;
    if (batch->status != MY_COMPOSE_OK) return batch->status;
    if (payload_size > MY_COMPOSE_MESSAGE_BYTES ||
        batch->count >= MY_COMPOSE_MAX_EFFECTS_PER_INTENT) {
        batch->status = MY_COMPOSE_OVERLOAD;
        return batch->status;
    }
    if (payload_size > 0u && payload == NULL) {
        batch->status = MY_COMPOSE_INVALID;
        return batch->status;
    }
    slot = batch->count;
    effect = &batch->effects[slot];
    memset(effect, 0, sizeof(*effect));
    effect->type = type;
    effect->payload_size = payload_size;
    effect->payload = batch->payload_storage[slot];
    if (payload_size > 0u) {
        memcpy(batch->payload_storage[slot], payload, payload_size);
    }
    batch->count++;
    return MY_COMPOSE_OK;
}

MyComposeStatus my_compose_store_internal_seed_generation(MyComposeStore *store,
    uint32_t generation) {
    if (store == NULL || generation == 0u) return MY_COMPOSE_INVALID;
    if (store->closed || store->request_count > 0u || store->intent_count > 0u ||
        store->completion_count > 0u) {
        return MY_COMPOSE_CONFLICT;
    }
    store->generation = generation;
    return MY_COMPOSE_OK;
}

MyComposeStatus my_compose_store_internal_seed_request(MyComposeStore *store,
    uint64_t next_request_id) {
    if (store == NULL || next_request_id == 0u) return MY_COMPOSE_INVALID;
    if (store->closed || store->request_count > 0u) return MY_COMPOSE_CONFLICT;
    store->next_request_id = next_request_id;
    return MY_COMPOSE_OK;
}
