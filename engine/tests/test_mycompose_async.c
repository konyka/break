#include "test_framework.h"

#include <stdatomic.h>
#if defined(_WIN32)
#include <threads.h>
#else
#include <pthread.h>
#endif

#include "mypal/dummy/my_pal_dummy.h"
#include "myui/my_window.h"
#include "myui/my_window_manager.h"
#include "myui/mycompose/my_compose_internal.h"
#include "myui/mycompose/my_compose_runtime.h"
#include "myui/mycompose_myui/my_compose_myui.h"
#include "myui/mycompose_myui/my_compose_myui_internal.h"

#define EFFECT_INTENT 2u
#define COMPLETION_INTENT 900u

typedef struct TestState {
    uint32_t count;
} TestState;

typedef struct Fixture {
    my_pal_t *pal;
    my_pal_main_loop_t *loop;
    my_window_manager_t *wm;
    my_window_t *win;
    MyComposeStore *store;
    MyComposeTreeBuilder *builder;
    MyComposeMyui *adapter;
    MyComposeRuntime *runtime;
    MyComposeEffect effect;
    MyComposeCompletionContext *retained_completion;
    uint8_t effect_payload[MY_COMPOSE_MESSAGE_BYTES];
    bool retain_completion;
    uint32_t reducer_calls;
    uint32_t executor_calls;
    uint32_t completed_result;
    uint32_t view_failures;
    MyComposeNodeHandle button;
} Fixture;

typedef struct PostWorker {
    MyComposeCompletionContext *completion;
    atomic_uint result;
    atomic_int post_status;
    atomic_int final_state;
    atomic_bool posted;
} PostWorker;

typedef struct DirectWorker {
    MyComposeStore *store;
    MyComposeCompletion completion;
    atomic_int status;
} DirectWorker;

typedef struct TestThread {
#if defined(_WIN32)
    thrd_t handle;
#else
    pthread_t handle;
    int (*entry)(void *);
    void *argument;
#endif
} TestThread;

#if !defined(_WIN32)
static void *test_thread_trampoline(void *argument) {
    TestThread *thread = argument;
    thread->entry(thread->argument);
    return NULL;
}
#endif

static int test_thread_create(TestThread *thread, int (*entry)(void *),
    void *argument) {
#if defined(_WIN32)
    return thrd_create(&thread->handle, entry, argument);
#else
    thread->entry = entry;
    thread->argument = argument;
    return pthread_create(&thread->handle, NULL, test_thread_trampoline, thread);
#endif
}

static void test_thread_join(TestThread *thread) {
#if defined(_WIN32)
    (void)thrd_join(thread->handle, NULL);
#else
    (void)pthread_join(thread->handle, NULL);
#endif
}

static MyComposeStatus reduce_intent(void *context, const MyComposeIntent *intent,
    const void *current, uint32_t current_size, void *candidate,
    uint32_t *candidate_size, MyComposeEffectBatch *batch) {
    Fixture *fixture = context;
    const TestState *state = current;
    TestState *next = candidate;
    uint32_t value = 0u;
    (void)current_size;
    fixture->reducer_calls++;
    *next = *state;
    *candidate_size = sizeof(*next);
    if (intent->type != 1u && intent->type != EFFECT_INTENT) {
        fixture->completed_result = intent->result;
        return MY_COMPOSE_OK;
    }
    if (intent->payload_size == sizeof(value)) {
        memcpy(&value, intent->payload, sizeof(value));
    }
    next->count += value;
    if (intent->type == EFFECT_INTENT) {
        return my_compose_effect_batch_append(batch, 500u + value, &value,
            (uint32_t)sizeof(value));
    }
    return MY_COMPOSE_OK;
}

static MyComposeStatus execute_effect(void *context,
    const MyComposeEffect *effect) {
    Fixture *fixture = context;
    fixture->effect = *effect;
    memcpy(fixture->effect_payload, effect->payload, effect->payload_size);
    fixture->effect.payload = fixture->effect_payload;
    if (fixture->retain_completion) {
        fixture->retained_completion = my_compose_completion_ref(effect->completion);
    }
    fixture->executor_calls++;
    return MY_COMPOSE_OK;
}

static MyComposeStatus declare_view(void *context, MyComposeTreeBuilder *builder,
    const void *state, uint32_t state_size) {
    Fixture *fixture = context;
    const TestState *count = state;
    MyComposeNodeHandle root;
    MyComposeNodeDesc desc;
    (void)state_size;
    if (fixture->view_failures > 0u) {
        fixture->view_failures--;
        return MY_COMPOSE_FAILED;
    }
    memset(&desc, 0, sizeof(desc));
    desc.type = "@root";
    if (my_compose_tree_builder_node(builder, &desc, &root) != MY_COMPOSE_OK) {
        return MY_COMPOSE_FAILED;
    }
    if (count->count != 0u) return MY_COMPOSE_OK;
    desc.parent = root;
    desc.key = "button";
    desc.type = "button";
    if (my_compose_tree_builder_node(builder, &desc, &fixture->button) !=
        MY_COMPOSE_OK) {
        return MY_COMPOSE_FAILED;
    }
    {
        const char *names[] = {"x", "y", "w", "h"};
        int32_t values[] = {0, 0, 100, 30};
        for (uint32_t i = 0u; i < 4u; ++i) {
            MyComposeValue value;
            memset(&value, 0, sizeof(value));
            value.type = MY_COMPOSE_VALUE_INT32;
            value.as.int32_value = values[i];
            if (my_compose_tree_builder_property(builder, fixture->button,
                    names[i], &value) != MY_COMPOSE_OK) {
                return MY_COMPOSE_FAILED;
            }
        }
    }
    {
        MyComposeIntent intent;
        uint32_t payload = 1u;
        memset(&intent, 0, sizeof(intent));
        intent.type = EFFECT_INTENT;
        intent.payload = (const uint8_t *)&payload;
        intent.payload_size = sizeof(payload);
        if (my_compose_tree_builder_event(builder, fixture->button, "click",
                &intent) != MY_COMPOSE_OK) {
            return MY_COMPOSE_FAILED;
        }
    }
    return MY_COMPOSE_OK;
}

static bool fixture_init(Fixture *fixture) {
    TestState initial = {0u};
    MyComposeRuntimeConfig config;
    memset(fixture, 0, sizeof(*fixture));
    fixture->pal = my_pal_dummy_create(NULL);
    fixture->loop = my_pal_main_loop_create(fixture->pal);
    fixture->wm = my_window_manager_create(NULL, fixture->pal, fixture->loop);
    fixture->win = my_window_create(NULL, fixture->pal, 160u, 120u, "async");
    fixture->store = my_compose_store_create(&initial, (uint32_t)sizeof(initial),
        NULL, fixture, reduce_intent, fixture, execute_effect);
    fixture->builder = my_compose_tree_builder_create();
    if (fixture->pal == NULL || fixture->loop == NULL || fixture->wm == NULL ||
        fixture->win == NULL || fixture->store == NULL ||
        fixture->builder == NULL ||
        my_window_manager_open(fixture->wm, fixture->win) != MY_RET_OK) {
        return false;
    }
    fixture->adapter = my_compose_myui_create(fixture->win, fixture->builder,
        fixture->store);
    if (fixture->adapter == NULL) return false;
    memset(&config, 0, sizeof(config));
    config.store = fixture->store;
    config.view = declare_view;
    config.view_context = fixture;
    config.sink = my_compose_myui_sink(fixture->adapter);
    fixture->runtime = my_compose_runtime_create(fixture->builder, &config);
    return fixture->runtime != NULL;
}

static void fixture_destroy(Fixture *fixture) {
    my_compose_completion_unref(fixture->retained_completion);
    fixture->retained_completion = NULL;
    my_compose_runtime_destroy(fixture->runtime);
    my_compose_myui_destroy(fixture->adapter);
    my_compose_tree_builder_destroy(fixture->builder);
    my_compose_store_destroy(fixture->store);
    my_window_manager_destroy(fixture->wm);
    my_widget_unref((my_widget_t *)fixture->win);
    my_pal_main_loop_destroy(fixture->loop);
    my_pal_destroy(fixture->pal);
    memset(fixture, 0, sizeof(*fixture));
}

static MyComposeStatus dispatch_intent(Fixture *fixture, uint32_t type,
    uint32_t value) {
    MyComposeIntent intent;
    memset(&intent, 0, sizeof(intent));
    intent.type = type;
    intent.payload = (const uint8_t *)&value;
    intent.payload_size = (uint32_t)sizeof(value);
    return my_compose_store_dispatch(fixture->store, &intent);
}

static void wait_for_flag(atomic_bool *flag) {
    while (!atomic_load_explicit(flag, memory_order_acquire)) thrd_yield();
}

static int post_worker_main(void *argument) {
    PostWorker *worker = argument;
    MyComposeCompletionState state;
    atomic_store_explicit(&worker->post_status,
        my_compose_completion_post(worker->completion, worker->result),
        memory_order_release);
    atomic_store_explicit(&worker->posted, true, memory_order_release);
    do {
        state = my_compose_completion_state(worker->completion);
        if (state == MY_COMPOSE_COMPLETION_PENDING) thrd_yield();
    } while (state == MY_COMPOSE_COMPLETION_PENDING);
    atomic_store_explicit(&worker->final_state, state, memory_order_release);
    my_compose_completion_unref(worker->completion);
    return 0;
}

static void start_post_worker(Fixture *fixture, PostWorker *worker,
    TestThread *thread, uint32_t result) {
    memset(worker, 0, sizeof(*worker));
    atomic_init(&worker->post_status, MY_COMPOSE_PENDING);
    atomic_init(&worker->final_state, MY_COMPOSE_COMPLETION_PENDING);
    worker->result = result;
    if (fixture->retained_completion != NULL) {
        worker->completion = fixture->retained_completion;
        fixture->retained_completion = NULL;
    } else {
        worker->completion = my_compose_completion_ref(fixture->effect.completion);
    }
    (void)test_thread_create(thread, post_worker_main, worker);
}

static int direct_worker_main(void *argument) {
    DirectWorker *worker = argument;
    atomic_store_explicit(&worker->status,
        my_compose_store_complete(worker->store, &worker->completion),
        memory_order_release);
    return 0;
}

TEST(completion_roundtrip_enters_store_only_from_ui_command) {
    Fixture fixture;
    PostWorker worker;
    TestThread thread;
    ASSERT_TRUE(fixture_init(&fixture));
    ASSERT_EQ(my_compose_runtime_pump(fixture.runtime), MY_COMPOSE_OK);
    ASSERT_EQ(dispatch_intent(&fixture, EFFECT_INTENT, 3u), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_runtime_pump(fixture.runtime), MY_COMPOSE_OK);
    ASSERT_EQ(fixture.executor_calls, 1u);
    ASSERT_NOT_NULL(fixture.effect.completion);
    start_post_worker(&fixture, &worker, &thread, 77u);
    wait_for_flag(&worker.posted);
    ASSERT_EQ(atomic_load(&worker.post_status), MY_COMPOSE_OK);
    ASSERT_EQ(my_pal_main_loop_pump_n(fixture.loop, 1u), 1u);
    test_thread_join(&thread);
    ASSERT_EQ(atomic_load(&worker.final_state), MY_COMPOSE_COMPLETION_ACCEPTED);
    ASSERT_EQ(my_compose_store_diagnostics(fixture.store)->queued_completions, 1u);
    ASSERT_EQ(my_compose_runtime_pump(fixture.runtime), MY_COMPOSE_OK);
    ASSERT_EQ(fixture.completed_result, 77u);
    ASSERT_EQ(my_compose_store_diagnostics(fixture.store)->request_count, 0u);
    fixture_destroy(&fixture);
}

TEST(worker_direct_store_complete_is_rejected_by_owner_thread_guard) {
    Fixture fixture;
    DirectWorker worker;
    TestThread thread;
    ASSERT_TRUE(fixture_init(&fixture));
    ASSERT_EQ(my_compose_runtime_pump(fixture.runtime), MY_COMPOSE_OK);
    ASSERT_EQ(dispatch_intent(&fixture, EFFECT_INTENT, 4u), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_runtime_pump(fixture.runtime), MY_COMPOSE_OK);
    memset(&worker, 0, sizeof(worker));
    worker.store = fixture.store;
    worker.completion.request_id = fixture.effect.request_id;
    worker.completion.store_generation = fixture.effect.store_generation;
    worker.completion.owner = fixture.effect.owner;
    worker.completion.type = COMPLETION_INTENT;
    worker.completion.result = 88u;
    worker.completion.delivery = MY_COMPOSE_OK;
    atomic_init(&worker.status, MY_COMPOSE_PENDING);
    (void)test_thread_create(&thread, direct_worker_main, &worker);
    test_thread_join(&thread);
    ASSERT_EQ(atomic_load(&worker.status), MY_COMPOSE_CONFLICT);
    ASSERT_EQ(my_compose_store_diagnostics(fixture.store)->queued_completions, 0u);
    ASSERT_EQ(my_compose_store_diagnostics(fixture.store)->outstanding_effects, 1u);
    ASSERT_EQ(my_compose_runtime_restart(fixture.runtime), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_store_diagnostics(fixture.store)->request_count, 0u);
    fixture_destroy(&fixture);
}

typedef struct DispatchWorker {
    MyComposeStore *store;
    MyComposeIntent intent;
    atomic_int status;
} DispatchWorker;

static int dispatch_worker_main(void *argument) {
    DispatchWorker *worker = argument;
    atomic_store_explicit(&worker->status,
        my_compose_store_dispatch(worker->store, &worker->intent),
        memory_order_release);
    return 0;
}

TEST(worker_direct_store_dispatch_is_rejected_by_owner_thread_guard) {
    Fixture fixture;
    DispatchWorker worker;
    TestThread thread;
    ASSERT_TRUE(fixture_init(&fixture));
    ASSERT_EQ(my_compose_runtime_pump(fixture.runtime), MY_COMPOSE_OK);
    memset(&worker, 0, sizeof(worker));
    worker.store = fixture.store;
    worker.intent.type = 1u;
    atomic_init(&worker.status, MY_COMPOSE_PENDING);
    (void)test_thread_create(&thread, dispatch_worker_main, &worker);
    test_thread_join(&thread);
    ASSERT_EQ(atomic_load(&worker.status), MY_COMPOSE_CONFLICT);
    ASSERT_EQ(my_compose_store_diagnostics(fixture.store)->pending_intents, 0u);
    fixture_destroy(&fixture);
}

typedef struct RetryWorker {
    MyComposeCompletionContext *completion;
    atomic_int first_status;
    atomic_int retry_status;
    atomic_int final_state;
    atomic_bool posted;
    atomic_bool callback_done;
    atomic_bool retry;
} RetryWorker;

static int retry_worker_main(void *argument) {
    RetryWorker *worker = argument;
    MyComposeCompletionState state;
    atomic_store_explicit(&worker->first_status,
        my_compose_completion_post(worker->completion, 99u), memory_order_release);
    atomic_store_explicit(&worker->posted, true, memory_order_release);
    do {
        state = my_compose_completion_state(worker->completion);
        if (state == MY_COMPOSE_COMPLETION_PENDING) thrd_yield();
    } while (state == MY_COMPOSE_COMPLETION_PENDING);
    atomic_store_explicit(&worker->callback_done, true, memory_order_release);
    while (!atomic_load_explicit(&worker->retry, memory_order_acquire)) thrd_yield();
    atomic_store_explicit(&worker->retry_status,
        my_compose_completion_post(worker->completion, 99u), memory_order_release);
    atomic_store_explicit(&worker->final_state,
        my_compose_completion_state(worker->completion), memory_order_release);
    my_compose_completion_unref(worker->completion);
    return 0;
}

static void seed_full_completions(Fixture *fixture) {
    for (uint32_t i = 0u; i < MY_COMPOSE_COMPLETION_CAPACITY; ++i) {
        MyComposeStoredCompletion *stored = &fixture->store->completions[i];
        memset(stored, 0, sizeof(*stored));
        stored->completion.type = COMPLETION_INTENT;
        stored->completion.store_generation = fixture->store->generation;
        stored->completion.delivery = MY_COMPOSE_OK;
    }
    fixture->store->completion_head = 0u;
    fixture->store->completion_count = MY_COMPOSE_COMPLETION_CAPACITY;
    (void)my_compose_store_diagnostics(fixture->store);
}

static void destroy_frontend(Fixture *fixture) {
    my_compose_runtime_destroy(fixture->runtime);
    fixture->runtime = NULL;
    my_compose_myui_destroy(fixture->adapter);
    fixture->adapter = NULL;
    my_compose_tree_builder_destroy(fixture->builder);
    fixture->builder = NULL;
    my_compose_store_destroy(fixture->store);
    fixture->store = NULL;
}

static void queue_full_retry_is_safe_across_destroy(bool window_close) {
    Fixture fixture;
    RetryWorker worker;
    TestThread thread;
    MyComposeCompletionState final_state;
    ASSERT_TRUE(fixture_init(&fixture));
    ASSERT_EQ(my_compose_runtime_pump(fixture.runtime), MY_COMPOSE_OK);
    ASSERT_EQ(dispatch_intent(&fixture, EFFECT_INTENT, 5u), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_runtime_pump(fixture.runtime), MY_COMPOSE_OK);
    seed_full_completions(&fixture);
    memset(&worker, 0, sizeof(worker));
    atomic_init(&worker.first_status, MY_COMPOSE_PENDING);
    atomic_init(&worker.retry_status, MY_COMPOSE_PENDING);
    worker.completion = my_compose_completion_ref(fixture.effect.completion);
    (void)test_thread_create(&thread, retry_worker_main, &worker);
    wait_for_flag(&worker.posted);
    ASSERT_EQ(my_pal_main_loop_pump_n(fixture.loop, 1u), 1u);
    wait_for_flag(&worker.callback_done);
    ASSERT_EQ(atomic_load(&worker.first_status), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_completion_state(worker.completion),
        MY_COMPOSE_COMPLETION_RETRY);
    ASSERT_EQ(my_compose_completion_delivery(worker.completion), MY_COMPOSE_OVERLOAD);
    ASSERT_EQ(my_compose_store_diagnostics(fixture.store)->outstanding_effects, 1u);
    if (window_close) {
        ASSERT_EQ(my_window_manager_close(fixture.wm, fixture.win), MY_RET_OK);
        ASSERT_EQ(my_compose_store_diagnostics(fixture.store)->request_count, 0u);
    }
    destroy_frontend(&fixture);
    atomic_store_explicit(&worker.retry, true, memory_order_release);
    test_thread_join(&thread);
    final_state = atomic_load(&worker.final_state);
    ASSERT_TRUE(atomic_load(&worker.retry_status) == MY_COMPOSE_STALE ||
        atomic_load(&worker.retry_status) == MY_COMPOSE_CANCELLED);
    ASSERT_TRUE(final_state == MY_COMPOSE_COMPLETION_STALE ||
        final_state == MY_COMPOSE_COMPLETION_CANCELLED);
    fixture_destroy(&fixture);
}

TEST(queue_full_retry_after_plain_runtime_destroy_is_not_accepted) {
    queue_full_retry_is_safe_across_destroy(false);
}

TEST(queue_full_retry_after_window_close_is_not_accepted) {
    queue_full_retry_is_safe_across_destroy(true);
}

TEST(post_failure_abandon_reaps_once_even_with_pending_view) {
    Fixture fixture;
    PostWorker worker;
    TestThread thread;
    ASSERT_TRUE(fixture_init(&fixture));
    ASSERT_EQ(my_compose_runtime_pump(fixture.runtime), MY_COMPOSE_OK);
    ASSERT_EQ(dispatch_intent(&fixture, EFFECT_INTENT, 6u), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_runtime_pump(fixture.runtime), MY_COMPOSE_OK);
    ASSERT_EQ(dispatch_intent(&fixture, 1u, 1u), MY_COMPOSE_OK);
    fixture.view_failures = 1u;
    ASSERT_EQ(my_compose_runtime_pump(fixture.runtime), MY_COMPOSE_FAILED);
    ASSERT_EQ(my_compose_store_diagnostics(fixture.store)->outstanding_effects, 1u);
    my_compose_myui_internal_fail_async_posts(fixture.adapter, 1u);
    start_post_worker(&fixture, &worker, &thread, 100u);
    wait_for_flag(&worker.posted);
    test_thread_join(&thread);
    ASSERT_EQ(atomic_load(&worker.post_status), MY_COMPOSE_OVERLOAD);
    ASSERT_EQ(atomic_load(&worker.final_state), MY_COMPOSE_COMPLETION_RETRY);
    ASSERT_EQ(my_compose_store_diagnostics(fixture.store)->outstanding_effects, 1u);
    my_compose_completion_abandon(fixture.effect.completion, MY_COMPOSE_CANCELLED);
    ASSERT_EQ(my_compose_runtime_pump(fixture.runtime), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_store_diagnostics(fixture.store)->request_count, 0u);
    ASSERT_EQ(my_compose_store_diagnostics(fixture.store)->recycled_requests, 1u);
    ASSERT_EQ(fixture.reducer_calls, 2u);
    my_compose_store_reap(fixture.store);
    ASSERT_EQ(my_compose_store_diagnostics(fixture.store)->recycled_requests, 1u);
    fixture_destroy(&fixture);
}

TEST(queued_command_close_has_cancelled_final_delivery) {
    Fixture fixture;
    PostWorker worker;
    TestThread thread;
    ASSERT_TRUE(fixture_init(&fixture));
    ASSERT_EQ(my_compose_runtime_pump(fixture.runtime), MY_COMPOSE_OK);
    ASSERT_EQ(dispatch_intent(&fixture, EFFECT_INTENT, 7u), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_runtime_pump(fixture.runtime), MY_COMPOSE_OK);
    start_post_worker(&fixture, &worker, &thread, 101u);
    wait_for_flag(&worker.posted);
    ASSERT_EQ(atomic_load(&worker.post_status), MY_COMPOSE_OK);
    my_compose_runtime_destroy(fixture.runtime);
    fixture.runtime = NULL;
    ASSERT_EQ(my_compose_store_diagnostics(fixture.store)->request_count, 0u);
    ASSERT_EQ(my_pal_main_loop_pump_n(fixture.loop, 1u), 1u);
    test_thread_join(&thread);
    ASSERT_EQ(atomic_load(&worker.final_state), MY_COMPOSE_COMPLETION_CANCELLED);
    ASSERT_EQ(my_compose_store_diagnostics(fixture.store)->queued_completions, 0u);
    fixture_destroy(&fixture);
}

TEST(restart_cancels_retained_completion_before_worker_retry) {
    Fixture fixture;
    MyComposeCompletionContext *completion;
    ASSERT_TRUE(fixture_init(&fixture));
    ASSERT_EQ(my_compose_runtime_pump(fixture.runtime), MY_COMPOSE_OK);
    ASSERT_EQ(dispatch_intent(&fixture, EFFECT_INTENT, 8u), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_runtime_pump(fixture.runtime), MY_COMPOSE_OK);
    completion = my_compose_completion_ref(fixture.effect.completion);
    ASSERT_NOT_NULL(completion);
    ASSERT_EQ(my_compose_runtime_restart(fixture.runtime), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_completion_post(completion, 102u), MY_COMPOSE_CANCELLED);
    ASSERT_EQ(my_compose_completion_state(completion),
        MY_COMPOSE_COMPLETION_CANCELLED);
    ASSERT_EQ(my_compose_store_diagnostics(fixture.store)->request_count, 0u);
    ASSERT_EQ(my_compose_store_diagnostics(fixture.store)->queued_completions, 0u);
    my_compose_completion_unref(completion);
    fixture_destroy(&fixture);
}

TEST(owner_invalidate_makes_retained_completion_stale_and_recycles_once) {
    Fixture fixture;
    MyComposeCompletionContext *completion;
    MyComposeIntent intent;
    MyComposeNodeHandle owner = {2u, 1u};
    uint32_t value = 9u;
    ASSERT_TRUE(fixture_init(&fixture));
    ASSERT_EQ(my_compose_runtime_pump(fixture.runtime), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_store_register_owner(fixture.store, owner), MY_COMPOSE_OK);
    memset(&intent, 0, sizeof(intent));
    intent.type = EFFECT_INTENT;
    intent.owner = owner;
    intent.payload = (const uint8_t *)&value;
    intent.payload_size = sizeof(value);
    ASSERT_EQ(my_compose_store_dispatch(fixture.store, &intent), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_runtime_pump(fixture.runtime), MY_COMPOSE_OK);
    completion = my_compose_completion_ref(fixture.effect.completion);
    ASSERT_NOT_NULL(completion);
    ASSERT_EQ(my_compose_store_invalidate_owner(fixture.store, owner),
        MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_completion_post(completion, 103u), MY_COMPOSE_STALE);
    ASSERT_EQ(my_compose_completion_state(completion), MY_COMPOSE_COMPLETION_STALE);
    ASSERT_EQ(my_compose_runtime_pump(fixture.runtime), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_store_diagnostics(fixture.store)->request_count, 0u);
    ASSERT_EQ(my_compose_store_diagnostics(fixture.store)->recycled_requests, 1u);
    my_compose_completion_unref(completion);
    fixture_destroy(&fixture);
}

TEST(thirty_two_async_abandons_recover_request_capacity_exactly_once) {
    Fixture fixture;
    ASSERT_TRUE(fixture_init(&fixture));
    ASSERT_EQ(my_compose_runtime_pump(fixture.runtime), MY_COMPOSE_OK);
    for (uint32_t i = 0u; i < 32u; ++i) {
        ASSERT_EQ(dispatch_intent(&fixture, EFFECT_INTENT, i + 1u), MY_COMPOSE_OK);
        ASSERT_EQ(my_compose_runtime_pump(fixture.runtime), MY_COMPOSE_OK);
        ASSERT_EQ(my_compose_store_diagnostics(fixture.store)->outstanding_effects, 1u);
        my_compose_completion_abandon(fixture.effect.completion,
            MY_COMPOSE_CANCELLED);
        ASSERT_EQ(my_compose_runtime_pump(fixture.runtime), MY_COMPOSE_OK);
        ASSERT_EQ(my_compose_store_diagnostics(fixture.store)->request_count, 0u);
        ASSERT_EQ(my_compose_store_diagnostics(fixture.store)->recycled_requests,
            (uint64_t)i + 1u);
    }
    ASSERT_EQ(dispatch_intent(&fixture, EFFECT_INTENT, 33u), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_runtime_pump(fixture.runtime), MY_COMPOSE_OK);
    ASSERT_EQ(fixture.executor_calls, 33u);
    ASSERT_EQ(my_compose_store_diagnostics(fixture.store)->recycled_requests, 32u);
    fixture_destroy(&fixture);
}

typedef struct RuntimeWorker {
    MyComposeRuntime *runtime;
    atomic_int status;
} RuntimeWorker;

static int runtime_worker_main(void *argument) {
    RuntimeWorker *worker = argument;
    atomic_store_explicit(&worker->status,
        my_compose_runtime_pump(worker->runtime), memory_order_release);
    return 0;
}

TEST(runtime_pump_rejects_non_owner_thread) {
    Fixture fixture;
    RuntimeWorker worker;
    TestThread thread;
    ASSERT_TRUE(fixture_init(&fixture));
    ASSERT_EQ(my_compose_runtime_pump(fixture.runtime), MY_COMPOSE_OK);
    worker.runtime = fixture.runtime;
    atomic_init(&worker.status, MY_COMPOSE_PENDING);
    (void)test_thread_create(&thread, runtime_worker_main, &worker);
    test_thread_join(&thread);
    ASSERT_EQ(atomic_load(&worker.status), MY_COMPOSE_CONFLICT);
    ASSERT_EQ(fixture.reducer_calls, 0u);
    fixture_destroy(&fixture);
}

static void dispatch_real_click(Fixture *fixture) {
    my_event_t event = my_event_init(MY_EVENT_POINTER_DOWN);
    event.u.pointer.x = 10;
    event.u.pointer.y = 10;
    event.u.pointer.button = 1;
    (void)my_window_manager_dispatch_surface_event(fixture->wm, &event);
    event.type = MY_EVENT_POINTER_UP;
    (void)my_window_manager_dispatch_surface_event(fixture->wm, &event);
}

TEST(myui_pump_uses_independent_adapter_contexts) {
    Fixture first;
    Fixture second;
    ASSERT_TRUE(fixture_init(&first));
    ASSERT_TRUE(fixture_init(&second));
    ASSERT_TRUE(my_compose_myui_sink(first.adapter).context == first.adapter);
    ASSERT_TRUE(my_compose_myui_sink(second.adapter).context == second.adapter);
    ASSERT_EQ(my_compose_myui_pump(first.adapter, first.runtime), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_myui_pump(second.adapter, second.runtime), MY_COMPOSE_OK);
    ASSERT_EQ(dispatch_intent(&first, EFFECT_INTENT, 11u), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_myui_pump(first.adapter, first.runtime), MY_COMPOSE_OK);
    ASSERT_EQ(first.executor_calls, 1u);
    ASSERT_EQ(second.executor_calls, 0u);
    ASSERT_EQ(my_compose_myui_pump(second.adapter, second.runtime), MY_COMPOSE_OK);
    ASSERT_EQ(second.executor_calls, 0u);
    fixture_destroy(&first);
    fixture_destroy(&second);
}

TEST(event_callback_direct_myui_pump_returns_conflict) {
    Fixture fixture;
    ASSERT_TRUE(fixture_init(&fixture));
    ASSERT_EQ(my_compose_myui_pump(fixture.adapter, fixture.runtime), MY_COMPOSE_OK);
    fixture.adapter->fault.event_pump = fixture.runtime;
    fixture.adapter->fault.event_pump_status = MY_COMPOSE_OK;
    dispatch_real_click(&fixture);
    ASSERT_EQ(fixture.adapter->fault.event_pump_status, MY_COMPOSE_CONFLICT);
    ASSERT_EQ(my_compose_runtime_restart(fixture.runtime), MY_COMPOSE_OK);
    fixture_destroy(&fixture);
}

TEST(click_effect_outliving_deleted_owner_is_stale_in_both_stores) {
    Fixture fixture;
    Fixture second;
    PostWorker worker;
    TestThread thread;
    MyComposeCompletion completion;
    ASSERT_TRUE(fixture_init(&fixture));
    ASSERT_EQ(my_compose_myui_pump(fixture.adapter, fixture.runtime), MY_COMPOSE_OK);
    dispatch_real_click(&fixture);
    ASSERT_EQ(my_compose_store_diagnostics(fixture.store)->accepted_intents, 1u);
    fixture.retain_completion = true;
    ASSERT_EQ(my_compose_myui_pump(fixture.adapter, fixture.runtime), MY_COMPOSE_OK);
    ASSERT_EQ(fixture.reducer_calls, 1u);
    ASSERT_EQ(fixture.executor_calls, 1u);
    ASSERT_TRUE(my_compose_myui_widget(fixture.adapter, fixture.button) == NULL);
    ASSERT_NOT_NULL(fixture.effect.completion);
    ASSERT_NOT_NULL(fixture.retained_completion);
    start_post_worker(&fixture, &worker, &thread, 104u);
    wait_for_flag(&worker.posted);
    test_thread_join(&thread);
    ASSERT_EQ(atomic_load(&worker.post_status), MY_COMPOSE_STALE);
    ASSERT_EQ(atomic_load(&worker.final_state), MY_COMPOSE_COMPLETION_STALE);
    ASSERT_TRUE(fixture_init(&second));
    ASSERT_EQ(my_compose_myui_pump(second.adapter, second.runtime), MY_COMPOSE_OK);
    memset(&completion, 0, sizeof(completion));
    completion.request_id = fixture.effect.request_id;
    completion.store_generation = fixture.effect.store_generation;
    completion.owner = fixture.effect.owner;
    completion.type = COMPLETION_INTENT;
    completion.result = 104u;
    completion.delivery = MY_COMPOSE_OK;
    ASSERT_EQ(my_compose_store_complete(second.store, &completion), MY_COMPOSE_STALE);
    ASSERT_EQ(my_compose_store_diagnostics(second.store)->queued_completions, 0u);
    ASSERT_EQ(my_compose_myui_pump(fixture.adapter, fixture.runtime), MY_COMPOSE_OK);
    ASSERT_EQ(my_compose_store_diagnostics(fixture.store)->request_count, 0u);
    fixture_destroy(&second);
    fixture_destroy(&fixture);
}

TEST_MAIN_BEGIN()
RUN_TEST(completion_roundtrip_enters_store_only_from_ui_command);
RUN_TEST(worker_direct_store_complete_is_rejected_by_owner_thread_guard);
RUN_TEST(worker_direct_store_dispatch_is_rejected_by_owner_thread_guard);
RUN_TEST(queue_full_retry_after_plain_runtime_destroy_is_not_accepted);
RUN_TEST(queue_full_retry_after_window_close_is_not_accepted);
RUN_TEST(post_failure_abandon_reaps_once_even_with_pending_view);
RUN_TEST(queued_command_close_has_cancelled_final_delivery);
RUN_TEST(restart_cancels_retained_completion_before_worker_retry);
RUN_TEST(owner_invalidate_makes_retained_completion_stale_and_recycles_once);
RUN_TEST(thirty_two_async_abandons_recover_request_capacity_exactly_once);
RUN_TEST(runtime_pump_rejects_non_owner_thread);
RUN_TEST(myui_pump_uses_independent_adapter_contexts);
RUN_TEST(event_callback_direct_myui_pump_returns_conflict);
RUN_TEST(click_effect_outliving_deleted_owner_is_stale_in_both_stores);
TEST_MAIN_END()
