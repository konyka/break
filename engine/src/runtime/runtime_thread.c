#include <runtime/runtime_thread.h>

#include <core/platform_thread.h>
#include <runtime/runtime_test_hooks.h>

#include <stdlib.h>
#include <string.h>

#if defined(PLATFORM_THREAD_POSIX)
#include <errno.h>
#include <time.h>
#endif

/* Formal thread facade over platform_thread.h. The platform handle and the
 * native trampoline live entirely inside this translation unit; the public
 * header exposes only the opaque BreakRuntimeThread.
 *
 * The bounded stop wait follows the established break_net_adapter.c pattern
 * (pthread_cond_timedwait / SleepConditionVariableCS against a TIME_UTC
 * deadline): platform_thread.h deliberately stays untouched — it still has
 * no portable timed-wait wrapper (a parked Task 4 minor), so the timed wait
 * is implemented here, not leaked into the public header. */

struct BreakRuntimeThread {
    PlatformMutex mutex;
    PlatformCond exit_cond; /* signalled (broadcast) by the worker at exit */
    PlatformThread handle;
    BreakRuntimeThreadFn fn;
    void *arg;
    char name[BREAK_RUNTIME_THREAD_NAME_CAPACITY];
    BreakRuntimeThreadState state;
    bool stop_requested;
    bool exited;
};

static PLATFORM_THREAD_RET break_runtime_thread_trampoline(
    PLATFORM_THREAD_ARG arg)
{
    BreakRuntimeThread *thread = (BreakRuntimeThread *)arg;
    thread->fn(thread->arg);
    platform_mutex_lock(&thread->mutex);
    thread->exited = true;
    platform_cond_broadcast(&thread->exit_cond);
    platform_mutex_unlock(&thread->mutex);
    return PLATFORM_THREAD_RETURN;
}

/* Caller holds thread->mutex. Bounded wait for worker exit. */
static bool break_runtime_thread_wait_exited_locked(
    BreakRuntimeThread *thread, u32 timeout_ms)
{
#if defined(PLATFORM_THREAD_POSIX)
    struct timespec deadline;
    if (timespec_get(&deadline, TIME_UTC) != TIME_UTC) {
        return thread->exited;
    }
    deadline.tv_sec += (time_t)(timeout_ms / 1000u);
    deadline.tv_nsec += (long)(timeout_ms % 1000u) * 1000000L;
    if (deadline.tv_nsec >= 1000000000L) {
        deadline.tv_sec++;
        deadline.tv_nsec -= 1000000000L;
    }
    while (!thread->exited) {
        int result = pthread_cond_timedwait(&thread->exit_cond,
                                            &thread->mutex, &deadline);
        if (result == ETIMEDOUT) {
            break;
        }
        if (result != 0) {
            break;
        }
    }
    return thread->exited;
#else
    ULONGLONG deadline = GetTickCount64() + (ULONGLONG)timeout_ms;
    while (!thread->exited) {
        ULONGLONG now = GetTickCount64();
        DWORD remaining = now >= deadline ? 0u : (DWORD)(deadline - now);
        if (!SleepConditionVariableCS(&thread->exit_cond, &thread->mutex,
                                      remaining)) {
            if (GetLastError() == ERROR_TIMEOUT) {
                break;
            }
            break;
        }
    }
    return thread->exited;
#endif
}

BreakRuntimeError break_runtime_thread_create(
    const BreakRuntimeThreadConfig *config,
    BreakRuntimeThread **out_thread)
{
    BreakRuntimeThread *thread;
    usize name_len;

    if (!out_thread) {
        return BREAK_RUNTIME_INVALID;
    }
    *out_thread = NULL;
    if (!config || !config->fn) {
        return BREAK_RUNTIME_INVALID;
    }

    thread = break_runtime_test_calloc(sizeof(*thread));
    if (!thread) {
        return BREAK_RUNTIME_OOM;
    }
    platform_mutex_init(&thread->mutex);
    platform_cond_init(&thread->exit_cond);
    thread->fn = config->fn;
    thread->arg = config->arg;
    if (config->name) {
        name_len = strlen(config->name);
        if (name_len >= (usize)BREAK_RUNTIME_THREAD_NAME_CAPACITY) {
            name_len = (usize)BREAK_RUNTIME_THREAD_NAME_CAPACITY - 1u;
        }
        memcpy(thread->name, config->name, name_len);
        thread->name[name_len] = '\0';
    }
    thread->state = BREAK_RUNTIME_THREAD_CREATED;
    *out_thread = thread;
    return BREAK_RUNTIME_OK;
}

void break_runtime_thread_destroy(BreakRuntimeThread *thread)
{
    if (!thread) {
        return;
    }
    /* Contract: only CREATED (never started or start-failed) or STOPPED.
     * Destroying a live thread is a contract violation, mirroring the queue
     * destroy-with-concurrent-users rule. */
    platform_cond_destroy(&thread->exit_cond);
    platform_mutex_destroy(&thread->mutex);
    free(thread);
}

BreakRuntimeError break_runtime_thread_start(
    BreakRuntimeThread *thread)
{
    bool spawned;

    if (!thread) {
        return BREAK_RUNTIME_INVALID;
    }
    platform_mutex_lock(&thread->mutex);
    if (thread->state != BREAK_RUNTIME_THREAD_CREATED) {
        platform_mutex_unlock(&thread->mutex);
        return BREAK_RUNTIME_REJECTED;
    }
    platform_mutex_unlock(&thread->mutex);

    /* Spawn outside the lock: the trampoline only touches the mutex, and the
     * state is published before any concurrent owner call could observe a
     * half-spawned object (lifecycle is owner-thread-only). */
    spawned = platform_thread_create(&thread->handle,
                                     break_runtime_thread_trampoline,
                                     thread);
    if (!spawned) {
        return BREAK_RUNTIME_FAILED; /* nothing live; stays CREATED */
    }
    platform_mutex_lock(&thread->mutex);
    thread->state = BREAK_RUNTIME_THREAD_RUNNING;
    platform_mutex_unlock(&thread->mutex);
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_runtime_thread_stop(
    BreakRuntimeThread *thread, u32 timeout_ms)
{
    bool exited;

    if (!thread) {
        return BREAK_RUNTIME_INVALID;
    }
    platform_mutex_lock(&thread->mutex);
    if (thread->state == BREAK_RUNTIME_THREAD_CREATED) {
        platform_mutex_unlock(&thread->mutex);
        return BREAK_RUNTIME_INVALID;
    }
    if (thread->state == BREAK_RUNTIME_THREAD_STOPPED) {
        platform_mutex_unlock(&thread->mutex);
        return BREAK_RUNTIME_OK; /* idempotent */
    }
    /* Publish the completion condition, then bounded-wait for exit. */
    thread->stop_requested = true;
    thread->state = BREAK_RUNTIME_THREAD_STOP_REQUESTED;
    exited = break_runtime_thread_wait_exited_locked(thread, timeout_ms);
    platform_mutex_unlock(&thread->mutex);

    if (!exited) {
        /* TIMEOUT retains live ownership: nothing is joined or freed, and a
         * later stop() resumes at the wait. */
        return BREAK_RUNTIME_TIMEOUT;
    }

    /* Join ownership: exactly once, here, on the owner thread calling
     * stop(). After join the platform handle is never touched again. */
    platform_thread_join(thread->handle);

    platform_mutex_lock(&thread->mutex);
    thread->state = BREAK_RUNTIME_THREAD_STOPPED;
    platform_mutex_unlock(&thread->mutex);
    return BREAK_RUNTIME_OK;
}

bool break_runtime_thread_stop_requested(BreakRuntimeThread *thread)
{
    bool requested;
    if (!thread) {
        return false;
    }
    platform_mutex_lock(&thread->mutex);
    requested = thread->stop_requested;
    platform_mutex_unlock(&thread->mutex);
    return requested;
}

BreakRuntimeThreadState break_runtime_thread_state(
    BreakRuntimeThread *thread)
{
    BreakRuntimeThreadState state;
    if (!thread) {
        return BREAK_RUNTIME_THREAD_CREATED;
    }
    platform_mutex_lock(&thread->mutex);
    state = thread->state;
    platform_mutex_unlock(&thread->mutex);
    return state;
}
