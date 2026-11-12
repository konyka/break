#include <myui/mycompose/my_compose_internal.h>
#include <myui/mycompose/my_compose_store.h>

#include <limits.h>
#include <stdlib.h>
#include <string.h>

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
    if (!request->used) return;
    if (request->location == MY_COMPOSE_REQUEST_OUTSTANDING) {
        store->outstanding_count--;
    }
    request->used = false;
    request->terminal = MY_COMPOSE_OK;
    store->request_count--;
}

static void reap_requests(MyComposeStore *store) {
    uint32_t old_outbox_count = store->outbox_count;
    uint32_t old_head = store->outbox_head;
    uint32_t kept[MY_COMPOSE_EFFECT_CAPACITY];
    uint32_t kept_count = 0u;
    for (uint32_t i = 0u; i < MY_COMPOSE_EFFECT_CAPACITY; ++i) {
        MyComposeRequest *request = &store->requests[i];
        if (request->used && request->terminal != MY_COMPOSE_OK &&
            request->terminal != MY_COMPOSE_PENDING) {
            release_request(store, i);
            store->diagnostics.recycled_requests++;
        }
    }
    for (uint32_t i = 0u; i < old_outbox_count; ++i) {
        uint32_t slot = store->outbox[(old_head + i) % MY_COMPOSE_EFFECT_CAPACITY];
        MyComposeRequest *request = &store->requests[slot];
        if (request->used && request->location == MY_COMPOSE_REQUEST_OUTBOX &&
            request->terminal == MY_COMPOSE_OK) {
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
    if (batch.status != MY_COMPOSE_OK) {
        return fail_candidate(store, candidate, batch.status);
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
    if (state_ops != NULL) store->state_ops = *state_ops;
    store->reducer_context = reducer_context;
    store->reducer = reducer;
    store->executor_context = executor_context;
    store->executor = executor;
    store->generation = 1u;
    store->next_request_id = 1u;
    status = clone_state(store, initial_state, initial_state_size, 0u);
    if (status != MY_COMPOSE_OK) {
        free(store);
        return NULL;
    }
    store->current_state = 0u;
    sync_diagnostics(store);
    return store;
}

void my_compose_store_destroy(MyComposeStore *store) {
    if (store == NULL) return;
    my_compose_store_close(store);
    reap_requests(store);
    dispose_state_slot(store, 0u);
    dispose_state_slot(store, 1u);
    free(store);
}

MyComposeStatus my_compose_store_dispatch(MyComposeStore *store,
    const MyComposeIntent *intent) {
    MyComposeStoredIntent *stored;
    MyComposeStatus status;
    if (store == NULL || intent == NULL) return MY_COMPOSE_INVALID;
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

MyComposeStatus my_compose_store_reduce(MyComposeStore *store) {
    uint32_t processed = 0u;
    uint32_t converted = 0u;
    if (store == NULL) return MY_COMPOSE_INVALID;
    reap_requests(store);
    if (store->closed) return MY_COMPOSE_CANCELLED;
    if (store->generation == UINT32_MAX) return MY_COMPOSE_OVERLOAD;
    while (processed < 64u) {
        MyComposeStatus status;
        while (converted < MY_COMPOSE_COMPLETION_CAPACITY &&
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
            converted++;
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
        if (store->intent_count == 0u) break;
        status = reduce_one(store);
        if (status != MY_COMPOSE_OK) {
            sync_diagnostics(store);
            return status;
        }
        store->intent_head = (store->intent_head + 1u) %
            MY_COMPOSE_INTENT_CAPACITY;
        store->intent_count--;
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

void my_compose_store_close(MyComposeStore *store) {
    if (store == NULL || store->closed) return;
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
