#ifndef MY_COMPOSE_STORE_H
#define MY_COMPOSE_STORE_H

#include <myui/mycompose/my_compose.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MyComposeStore MyComposeStore;
typedef struct MyComposeEffectBatch MyComposeEffectBatch;
typedef struct MyComposeCompletionContext MyComposeCompletionContext;

typedef enum MyComposeCompletionState {
    MY_COMPOSE_COMPLETION_PENDING = 0,
    MY_COMPOSE_COMPLETION_ACCEPTED,
    MY_COMPOSE_COMPLETION_RETRY,
    MY_COMPOSE_COMPLETION_CANCELLED,
    MY_COMPOSE_COMPLETION_STALE
} MyComposeCompletionState;

typedef struct MyComposeEffect {
    uint32_t type;
    uint32_t payload_size;
    const uint8_t *payload;
    MyComposeNodeHandle owner;
    uint64_t store_id;
    uint32_t store_generation;
    uint64_t request_id;
    MyComposeCompletionContext *completion;
} MyComposeEffect;

struct MyComposeEffectBatch {
    MyComposeEffect effects[MY_COMPOSE_MAX_EFFECTS_PER_INTENT];
    uint8_t payload_storage[MY_COMPOSE_MAX_EFFECTS_PER_INTENT]
        [MY_COMPOSE_MESSAGE_BYTES];
    uint32_t count;
    MyComposeStatus status;
};

typedef struct MyComposeCompletion {
    uint64_t request_id;
    uint64_t store_id;
    uint32_t store_generation;
    MyComposeNodeHandle owner;
    uint32_t type;
    uint32_t payload_size;
    const uint8_t *payload;
    uint32_t result;
    uint32_t delivery;
} MyComposeCompletion;

typedef void (*MyComposeAsyncDeliver)(void *, MyComposeCompletionContext *,
    uint32_t);
typedef void (*MyComposeAsyncRelease)(MyComposeCompletionContext *);

typedef struct MyComposeAsyncBridgeOps {
    void *context;
    MyComposeStatus (*post)(void *, MyComposeAsyncDeliver,
        MyComposeCompletionContext *, uint32_t, MyComposeAsyncRelease);
    void (*close)(void *);
    void (*destroy)(void *);
} MyComposeAsyncBridgeOps;

MyComposeStatus my_compose_store_set_async_bridge(MyComposeStore *store,
    const MyComposeAsyncBridgeOps *ops);
MyComposeCompletionContext *my_compose_completion_ref(
    MyComposeCompletionContext *completion);
void my_compose_completion_unref(MyComposeCompletionContext *completion);
MyComposeStatus my_compose_completion_post(
    MyComposeCompletionContext *completion, uint32_t result);
MyComposeCompletionState my_compose_completion_state(
    const MyComposeCompletionContext *completion);
MyComposeStatus my_compose_completion_delivery(
    const MyComposeCompletionContext *completion);
void my_compose_completion_abandon(MyComposeCompletionContext *completion,
    MyComposeStatus status);

typedef struct MyComposeStateOps {
    void *context;
    MyComposeStatus (*clone)(void *, const void *, uint32_t, void *, uint32_t,
        uint32_t *);
    void (*dispose)(void *, void *, uint32_t);
} MyComposeStateOps;

typedef MyComposeStatus (*MyComposeReducer)(void *, const MyComposeIntent *,
    const void *, uint32_t, void *, uint32_t *, MyComposeEffectBatch *);
typedef MyComposeStatus (*MyComposeExecutor)(void *, const MyComposeEffect *);

typedef struct MyComposeDiagnostics {
    uint64_t accepted_intents;
    uint64_t rejected_intents;
    uint64_t reducer_failures;
    uint64_t effect_overloads;
    uint64_t stale_completions;
    uint64_t reconcile_failures;
    uint64_t rollbacks;
    uint64_t remember_disposes;
    uint64_t recycled_requests;
    uint64_t executor_failures;
    uint32_t intent_high_water;
    uint32_t effect_high_water;
    uint32_t completion_high_water;
    uint32_t outstanding_high_water;
    uint32_t pending_intents;
    uint32_t outbox_effects;
    uint32_t outstanding_effects;
    uint32_t queued_completions;
    uint32_t request_count;
} MyComposeDiagnostics;

MyComposeStore *my_compose_store_create(const void *initial_state,
    uint32_t initial_state_size, const MyComposeStateOps *state_ops,
    void *reducer_context, MyComposeReducer reducer, void *executor_context,
    MyComposeExecutor executor);
void my_compose_store_destroy(MyComposeStore *store);

MyComposeStatus my_compose_store_dispatch(MyComposeStore *store,
    const MyComposeIntent *intent);
MyComposeStatus my_compose_store_complete(MyComposeStore *store,
    const MyComposeCompletion *completion);
MyComposeStatus my_compose_store_register_owner(MyComposeStore *store,
    MyComposeNodeHandle owner);
MyComposeStatus my_compose_store_invalidate_owner(MyComposeStore *store,
    MyComposeNodeHandle owner);
MyComposeStatus my_compose_store_reduce(MyComposeStore *store);
MyComposeStatus my_compose_store_reduce_one(MyComposeStore *store,
    uint32_t *completion_budget, bool *out_reduced);
MyComposeStatus my_compose_store_dispatch_effects(MyComposeStore *store);
MyComposeStatus my_compose_store_restart(MyComposeStore *store);
void my_compose_store_reap(MyComposeStore *store);
void my_compose_store_close(MyComposeStore *store);

MyComposeStatus my_compose_store_state(const MyComposeStore *store,
    const void **out_state, uint32_t *out_size);
const MyComposeDiagnostics *my_compose_store_diagnostics(
    const MyComposeStore *store);
MyComposeStatus my_compose_effect_batch_append(MyComposeEffectBatch *batch,
    uint32_t type, const void *payload, uint32_t payload_size);

#ifdef __cplusplus
}
#endif

#endif
