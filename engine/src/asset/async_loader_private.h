#pragma once

/* ---- Shared platform threading primitives for async_loader and decode_pipeline ---- */
/*
 * R458-WIN: threading primitives now live in core/platform_thread.h so
 * renderer/cmd_buffer.c can share the exact same native fast paths. The
 * Async* names below remain for the asset pipeline call sites.
 */
#include <core/platform_thread.h>

#if defined(PLATFORM_THREAD_WIN32)
    #define ASYNC_PLATFORM_WIN32 1
#elif defined(PLATFORM_THREAD_POSIX)
    #define ASYNC_PLATFORM_POSIX 1
#endif

typedef PlatformThread AsyncThread;
typedef PlatformMutex  AsyncMutex;
typedef PlatformCond   AsyncCond;
typedef PlatformThreadFn AsyncThreadFn;

static inline void async_mutex_init(AsyncMutex *m)      { platform_mutex_init(m); }
static inline void async_mutex_destroy(AsyncMutex *m)   { platform_mutex_destroy(m); }
static inline void async_mutex_lock(AsyncMutex *m)      { platform_mutex_lock(m); }
static inline void async_mutex_unlock(AsyncMutex *m)    { platform_mutex_unlock(m); }
static inline void async_cond_init(AsyncCond *c)        { platform_cond_init(c); }
static inline void async_cond_destroy(AsyncCond *c)     { platform_cond_destroy(c); }
static inline void async_cond_wait(AsyncCond *c, AsyncMutex *m) { platform_cond_wait(c, m); }
static inline void async_cond_signal(AsyncCond *c)      { platform_cond_signal(c); }
static inline void async_cond_broadcast(AsyncCond *c)   { platform_cond_broadcast(c); }
static inline bool async_thread_create(AsyncThread *t, AsyncThreadFn fn, void *arg) {
    return platform_thread_create(t, fn, arg);
}
static inline void async_thread_join(AsyncThread t)     { platform_thread_join(t); }
