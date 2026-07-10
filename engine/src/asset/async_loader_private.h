#pragma once

/* ---- Shared platform threading primitives for async_loader and decode_pipeline ---- */

#if defined(ENGINE_PLATFORM_WINDOWS) || defined(_WIN32)
    #define ASYNC_PLATFORM_WIN32 1
    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif
    #include <windows.h>

    typedef HANDLE              AsyncThread;
    typedef CRITICAL_SECTION    AsyncMutex;
    typedef CONDITION_VARIABLE  AsyncCond;

    typedef DWORD (WINAPI *AsyncThreadFn)(LPVOID);

    static inline void async_mutex_init(AsyncMutex *m) { InitializeCriticalSection(m); }
    static inline void async_mutex_destroy(AsyncMutex *m) { DeleteCriticalSection(m); }
    static inline void async_mutex_lock(AsyncMutex *m) { EnterCriticalSection(m); }
    static inline void async_mutex_unlock(AsyncMutex *m) { LeaveCriticalSection(m); }
    static inline void async_cond_init(AsyncCond *c) { InitializeConditionVariable(c); }
    static inline void async_cond_destroy(AsyncCond *c) { (void)c; }
    static inline void async_cond_wait(AsyncCond *c, AsyncMutex *m) { SleepConditionVariableCS(c, m, INFINITE); }
    static inline void async_cond_broadcast(AsyncCond *c) { WakeAllConditionVariable(c); }

    static inline bool async_thread_create(AsyncThread *t, AsyncThreadFn fn, void *arg) {
        *t = CreateThread(NULL, 0, fn, arg, 0, NULL);
        return *t != NULL;
    }
    static inline void async_thread_join(AsyncThread t) {
        if (!t) return;
        WaitForSingleObject(t, INFINITE);
        CloseHandle(t);
    }
#else
    #define ASYNC_PLATFORM_POSIX 1
    #include <pthread.h>

    typedef pthread_t       AsyncThread;
    typedef pthread_mutex_t AsyncMutex;
    typedef pthread_cond_t  AsyncCond;

    typedef void *(*AsyncThreadFn)(void *);

    static inline void async_mutex_init(AsyncMutex *m) { pthread_mutex_init(m, NULL); }
    static inline void async_mutex_destroy(AsyncMutex *m) { pthread_mutex_destroy(m); }
    static inline void async_mutex_lock(AsyncMutex *m) { pthread_mutex_lock(m); }
    static inline void async_mutex_unlock(AsyncMutex *m) { pthread_mutex_unlock(m); }
    static inline void async_cond_init(AsyncCond *c) { pthread_cond_init(c, NULL); }
    static inline void async_cond_destroy(AsyncCond *c) { pthread_cond_destroy(c); }
    static inline void async_cond_wait(AsyncCond *c, AsyncMutex *m) { pthread_cond_wait(c, m); }
    static inline void async_cond_broadcast(AsyncCond *c) { pthread_cond_broadcast(c); }

    static inline bool async_thread_create(AsyncThread *t, AsyncThreadFn fn, void *arg) {
        return pthread_create(t, NULL, fn, arg) == 0;
    }
    static inline void async_thread_join(AsyncThread t) { pthread_join(t, NULL); }
#endif
