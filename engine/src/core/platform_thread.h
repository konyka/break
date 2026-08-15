#pragma once
/*
 * Shared cross-platform threading primitives.
 *
 * Performance notes:
 *   - On Windows, a CRITICAL_SECTION is a lightweight user-mode lock (faster
 *     than a Win32 Mutex) and CONDITION_VARIABLE uses the OS futex-like
 *     WaitOnAddress primitive; both avoid kernel transitions in the
 *     uncontended fast path.
 *   - On POSIX, pthread mutex/cond map to the same futex-based fast path.
 *   - The wrapper is header-only and inline, so the hot paths compile to the
 *     native calls directly (no function-pointer indirection).
 *
 * Consumers should keep the native calling-convention signature when they
 * define a thread entry: DWORD WINAPI fn(LPVOID) on Win32,
 * void *fn(void *) on POSIX. See async_loader.c for the established pattern.
 */

#if defined(ENGINE_PLATFORM_WINDOWS) || defined(_WIN32)
    #define PLATFORM_THREAD_WIN32 1
    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif
    #include <windows.h>

    typedef HANDLE              PlatformThread;
    typedef CRITICAL_SECTION    PlatformMutex;
    typedef CONDITION_VARIABLE  PlatformCond;

    typedef DWORD (WINAPI *PlatformThreadFn)(LPVOID);

    #define PLATFORM_THREAD_RET    DWORD WINAPI
    #define PLATFORM_THREAD_ARG    LPVOID
    #define PLATFORM_THREAD_RETURN 0

    static inline void platform_mutex_init(PlatformMutex *m) { InitializeCriticalSection(m); }
    static inline void platform_mutex_destroy(PlatformMutex *m) { DeleteCriticalSection(m); }
    static inline void platform_mutex_lock(PlatformMutex *m) { EnterCriticalSection(m); }
    static inline void platform_mutex_unlock(PlatformMutex *m) { LeaveCriticalSection(m); }
    static inline void platform_cond_init(PlatformCond *c) { InitializeConditionVariable(c); }
    static inline void platform_cond_destroy(PlatformCond *c) { (void)c; }
    static inline void platform_cond_wait(PlatformCond *c, PlatformMutex *m) {
        SleepConditionVariableCS(c, m, INFINITE);
    }
    static inline void platform_cond_signal(PlatformCond *c) { WakeConditionVariable(c); }
    static inline void platform_cond_broadcast(PlatformCond *c) { WakeAllConditionVariable(c); }

    static inline bool platform_thread_create(PlatformThread *t, PlatformThreadFn fn, void *arg) {
        *t = CreateThread(NULL, 0, fn, arg, 0, NULL);
        return *t != NULL;
    }
    static inline void platform_thread_join(PlatformThread t) {
        if (!t) return;
        WaitForSingleObject(t, INFINITE);
        CloseHandle(t);
    }
#else
    #define PLATFORM_THREAD_POSIX 1
    #include <pthread.h>

    typedef pthread_t       PlatformThread;
    typedef pthread_mutex_t PlatformMutex;
    typedef pthread_cond_t  PlatformCond;

    typedef void *(*PlatformThreadFn)(void *);

    #define PLATFORM_THREAD_RET    void *
    #define PLATFORM_THREAD_ARG    void *
    #define PLATFORM_THREAD_RETURN NULL

    static inline void platform_mutex_init(PlatformMutex *m) { pthread_mutex_init(m, NULL); }
    static inline void platform_mutex_destroy(PlatformMutex *m) { pthread_mutex_destroy(m); }
    static inline void platform_mutex_lock(PlatformMutex *m) { pthread_mutex_lock(m); }
    static inline void platform_mutex_unlock(PlatformMutex *m) { pthread_mutex_unlock(m); }
    static inline void platform_cond_init(PlatformCond *c) { pthread_cond_init(c, NULL); }
    static inline void platform_cond_destroy(PlatformCond *c) { pthread_cond_destroy(c); }
    static inline void platform_cond_wait(PlatformCond *c, PlatformMutex *m) {
        pthread_cond_wait(c, m);
    }
    static inline void platform_cond_signal(PlatformCond *c) { pthread_cond_signal(c); }
    static inline void platform_cond_broadcast(PlatformCond *c) { pthread_cond_broadcast(c); }

    static inline bool platform_thread_create(PlatformThread *t, PlatformThreadFn fn, void *arg) {
        return pthread_create(t, NULL, fn, arg) == 0;
    }
    static inline void platform_thread_join(PlatformThread t) { pthread_join(t, NULL); }
#endif
