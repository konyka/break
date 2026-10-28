#include <runtime/runtime_message.h>

#include <runtime/runtime_test_hooks.h>

#include <stdlib.h>
#include <string.h>

/* Owned messages: one allocation holds the metadata header and the payload
 * copy (flexible array member). The owned message never retains producer
 * pointers; only the copied bounded bytes. */

struct BreakRuntimeOwnedMessage {
    u16 kind;
    u16 version;
    u32 flags;
    u64 sequence;
    usize size;
    unsigned char data[];
};

#if defined(BREAK_RUNTIME_TESTING)

#include <core/platform_thread.h>
#include <stdio.h>

_Atomic u64 g_break_runtime_test_alloc_budget = BREAK_RUNTIME_TEST_ALLOC_DISABLED;

/* Test-build live-message registry: release() looks the pointer up BY VALUE
 * and never dereferences it first — a double release would otherwise read
 * freed memory before the check could fire. Exactly-once semantics: a
 * registered pointer is freed and removed; any unregistered pointer (double
 * release or foreign) aborts with a diagnostic, because release() has no
 * return channel. Registration is mandatory at copy; exhausting the bounded
 * table is a test bug and also aborts. The spinlock keeps the registry
 * TSan-clean when owned messages cross threads through the queue. */
#define RUNTIME_MESSAGE_REGISTRY_CAPACITY 4096u

static atomic_flag g_registry_lock = ATOMIC_FLAG_INIT;
static const void *g_registry[RUNTIME_MESSAGE_REGISTRY_CAPACITY];
static u32 g_registry_count;

static void registry_lock(void)
{
    while (atomic_flag_test_and_set_explicit(&g_registry_lock,
                                             memory_order_acquire)) {
        platform_thread_yield();
    }
}

static void registry_unlock(void)
{
    atomic_flag_clear_explicit(&g_registry_lock, memory_order_release);
}

static void registry_add(const void *message)
{
    bool added = false;
    registry_lock();
    if (g_registry_count < RUNTIME_MESSAGE_REGISTRY_CAPACITY) {
        g_registry[g_registry_count] = message;
        g_registry_count++;
        added = true;
    }
    registry_unlock();
    if (!added) {
        fprintf(stderr,
                "break_runtime_message_copy: test registry exhausted (%u live "
                "messages)\n",
                RUNTIME_MESSAGE_REGISTRY_CAPACITY);
        abort();
    }
}

static bool registry_remove(const void *message)
{
    u32 i;
    bool found = false;
    registry_lock();
    for (i = 0; i < g_registry_count; i++) {
        if (g_registry[i] == message) {
            g_registry[i] = g_registry[g_registry_count - 1u];
            g_registry_count--;
            found = true;
            break;
        }
    }
    registry_unlock();
    return found;
}

#endif /* BREAK_RUNTIME_TESTING */

BreakRuntimeError break_runtime_message_copy(
    const BreakRuntimeMessageView *view,
    BreakRuntimeOwnedMessage **out_message)
{
    BreakRuntimeOwnedMessage *message;
    usize bytes;

    if (!out_message) {
        return BREAK_RUNTIME_INVALID;
    }
    *out_message = NULL;
    if (!view) {
        return BREAK_RUNTIME_INVALID;
    }
    if (!view->data && view->size > 0u) {
        return BREAK_RUNTIME_INVALID;
    }
    if (view->size > (usize)BREAK_RUNTIME_MAX_MESSAGE_PAYLOAD) {
        return BREAK_RUNTIME_OVERLOAD;
    }
    /* Checked byte arithmetic before allocation; the payload cap above makes
     * this unreachable in practice, but the check is part of the contract. */
    if (view->size > SIZE_MAX - sizeof(struct BreakRuntimeOwnedMessage)) {
        return BREAK_RUNTIME_INVALID;
    }
    bytes = sizeof(struct BreakRuntimeOwnedMessage) + view->size;

    message = break_runtime_test_calloc(bytes);
    if (!message) {
        return BREAK_RUNTIME_OOM;
    }
    message->kind = view->kind;
    message->version = view->version;
    message->flags = view->flags;
    message->sequence = view->sequence;
    message->size = view->size;
    if (view->size > 0u) {
        memcpy(message->data, view->data, view->size);
    }
#if defined(BREAK_RUNTIME_TESTING)
    registry_add(message);
#endif
    *out_message = message;
    return BREAK_RUNTIME_OK;
}

void break_runtime_message_release(BreakRuntimeOwnedMessage *message)
{
    if (!message) {
        return;
    }
#if defined(BREAK_RUNTIME_TESTING)
    if (!registry_remove(message)) {
        fprintf(stderr,
                "break_runtime_message_release: double release or foreign "
                "owned message %p\n",
                (void *)message);
        abort();
    }
#endif
    free(message);
}

BreakRuntimeError break_runtime_message_view(
    const BreakRuntimeOwnedMessage *message,
    BreakRuntimeMessageView *out_view)
{
    if (!message || !out_view) {
        return BREAK_RUNTIME_INVALID;
    }
    out_view->kind = message->kind;
    out_view->version = message->version;
    out_view->flags = message->flags;
    out_view->sequence = message->sequence;
    out_view->data = message->size > 0u ? (const void *)message->data : NULL;
    out_view->size = message->size;
    return BREAK_RUNTIME_OK;
}
