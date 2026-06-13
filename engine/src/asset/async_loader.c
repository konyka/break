#include <asset/async_loader.h>
#include <asset/vfs.h>
#include <core/log.h>

#include <stb_image.h>

#include <limits.h>
#include <stdatomic.h>
#include <stdlib.h>
#include <string.h>

/* ---- Platform threading abstraction ---- */
#if defined(ENGINE_PLATFORM_WINDOWS) || defined(_WIN32)
    #define ASYNC_PLATFORM_WIN32 1
    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif
    #include <windows.h>
    typedef HANDLE              AsyncThread;
    typedef CRITICAL_SECTION    AsyncMutex;
    typedef CONDITION_VARIABLE  AsyncCond;

    static void async_mutex_init(AsyncMutex *m) { InitializeCriticalSection(m); }
    static void async_mutex_destroy(AsyncMutex *m) { DeleteCriticalSection(m); }
    static void async_mutex_lock(AsyncMutex *m) { EnterCriticalSection(m); }
    static void async_mutex_unlock(AsyncMutex *m) { LeaveCriticalSection(m); }
    static void async_cond_init(AsyncCond *c) { InitializeConditionVariable(c); }
    static void async_cond_destroy(AsyncCond *c) { (void)c; }
    static void async_cond_wait(AsyncCond *c, AsyncMutex *m) { SleepConditionVariableCS(c, m, INFINITE); }
    static void async_cond_broadcast(AsyncCond *c) { WakeAllConditionVariable(c); }

    static DWORD WINAPI io_worker_win32(LPVOID arg);
    static void async_thread_create(AsyncThread *t, void *arg) {
        *t = CreateThread(NULL, 0, io_worker_win32, arg, 0, NULL);
    }
    static void async_thread_join(AsyncThread t) {
        WaitForSingleObject(t, INFINITE);
        CloseHandle(t);
    }
#else
    #define ASYNC_PLATFORM_POSIX 1
    #include <pthread.h>
    typedef pthread_t       AsyncThread;
    typedef pthread_mutex_t AsyncMutex;
    typedef pthread_cond_t  AsyncCond;

    static void async_mutex_init(AsyncMutex *m) { pthread_mutex_init(m, NULL); }
    static void async_mutex_destroy(AsyncMutex *m) { pthread_mutex_destroy(m); }
    static void async_mutex_lock(AsyncMutex *m) { pthread_mutex_lock(m); }
    static void async_mutex_unlock(AsyncMutex *m) { pthread_mutex_unlock(m); }
    static void async_cond_init(AsyncCond *c) { pthread_cond_init(c, NULL); }
    static void async_cond_destroy(AsyncCond *c) { pthread_cond_destroy(c); }
    static void async_cond_wait(AsyncCond *c, AsyncMutex *m) { pthread_cond_wait(c, m); }
    static void async_cond_broadcast(AsyncCond *c) { pthread_cond_broadcast(c); }

    static void *io_worker_posix(void *arg);
    static void async_thread_create(AsyncThread *t, void *arg) {
        pthread_create(t, NULL, io_worker_posix, arg);
    }
    static void async_thread_join(AsyncThread t) { pthread_join(t, NULL); }
#endif

/* ---- Constants ---- */
#define ASYNC_QUEUE_SIZE    256   /* Must be power of 2 */
#define ASYNC_QUEUE_MASK    (ASYNC_QUEUE_SIZE - 1)
#define ASYNC_MAX_REQUESTS  1024
#define ASYNC_SLOT_BITS     10    /* log2(1024) */
#define ASYNC_SLOT_MASK     (ASYNC_MAX_REQUESTS - 1)

/* ---- Internal types ---- */
typedef struct {
    char              path[256];
    AsyncLoadCallback callback;
    void             *user_data;
    void             *data;
    u32               size;
    _Atomic u32       state;  /* AssetState cast to u32 for atomic ops */
    u64               id;
    /* Chunked loading support */
    usize             range_offset;  /* byte offset for partial reads (0 = from start) */
    usize             range_length;  /* bytes to read (0 = entire file) */
    /* Priority (lower = higher priority) */
    i32               priority;
    bool              decode_texture; /* run stbi on worker after full read */
} AsyncRequest;

/* SPMC request queue (single producer = main thread, multiple consumers = workers) */
typedef struct {
    _Atomic u64 head;  /* written by producer */
    _Atomic u64 tail;  /* CAS'd by consumers */
    u64         indices[ASYNC_QUEUE_SIZE];
} RequestQueue;

/* MPSC completion queue (multiple producers = workers, single consumer = main thread) */
typedef struct {
    _Atomic u64 head;  /* fetch_add by producers */
    _Atomic u64 tail;  /* read by consumer (main thread only) */
    u64         indices[ASYNC_QUEUE_SIZE];
} CompletionQueue;

typedef struct {
    AsyncThread     threads[8];
    u32             thread_count;
    _Atomic bool    running;

    AsyncRequest    requests[ASYNC_MAX_REQUESTS];
    _Atomic u64     next_id;
    _Atomic u32     next_slot;
    _Atomic u32     pending_count;

    RequestQueue    request_queue;
    CompletionQueue completion_queue;

    AsyncMutex      wake_mutex;
    AsyncCond       wake_cond;
    AsyncMutex      queue_mutex; /* serializes priority dequeue */

    VFS            *vfs;
} AsyncLoaderState;

static AsyncLoaderState g_loader;

/* Dequeue the highest-priority pending slot (lowest priority value).
 * Must be called with queue_mutex held. Returns false if queue empty. */
static bool async_dequeue_highest_priority(u64 *out_slot_idx) {
    u64 head = atomic_load_explicit(&g_loader.request_queue.head, memory_order_acquire);
    u64 tail = atomic_load_explicit(&g_loader.request_queue.tail, memory_order_acquire);
    if (tail >= head) return false;

    u64 pick = tail;
    i32 best_pri = g_loader.requests[g_loader.request_queue.indices[tail & ASYNC_QUEUE_MASK]].priority;

    for (u64 t = tail + 1; t < head; t++) {
        u64 idx = g_loader.request_queue.indices[t & ASYNC_QUEUE_MASK];
        i32 pri = g_loader.requests[idx].priority;
        if (pri < best_pri) {
            best_pri = pri;
            pick = t;
        }
    }

    if (pick != tail) {
        u64 a = g_loader.request_queue.indices[tail & ASYNC_QUEUE_MASK];
        u64 b = g_loader.request_queue.indices[pick & ASYNC_QUEUE_MASK];
        g_loader.request_queue.indices[tail & ASYNC_QUEUE_MASK] = b;
        g_loader.request_queue.indices[pick & ASYNC_QUEUE_MASK] = a;
    }

    *out_slot_idx = g_loader.request_queue.indices[tail & ASYNC_QUEUE_MASK];
    atomic_store_explicit(&g_loader.request_queue.tail, tail + 1, memory_order_release);
    return true;
}

static bool async_try_decode_texture(AsyncRequest *req) {
    if (!req->decode_texture || !req->data || req->size == 0) return true;

    int w = 0, h = 0, ch = 0;
    u8 *raw = (u8 *)req->data;
    u32 raw_size = req->size;
    u8 *pixels = stbi_load_from_memory(raw, (int)raw_size, &w, &h, &ch, 4);
    free(raw);
    req->data = NULL;
    req->size = 0;

    if (!pixels || w <= 0 || h <= 0) return false;

    usize hdr_sz = sizeof(AsyncTextureHeader);
    usize pix_sz = (usize)w * (usize)h * 4u;
    u8 *packed = (u8 *)malloc(hdr_sz + pix_sz);
    if (!packed) {
        stbi_image_free(pixels);
        return false;
    }

    AsyncTextureHeader *hdr = (AsyncTextureHeader *)packed;
    hdr->width = (u32)w;
    hdr->height = (u32)h;
    hdr->pixel_bytes = 4u;
    memcpy(packed + hdr_sz, pixels, pix_sz);
    stbi_image_free(pixels);

    req->data = packed;
    req->size = (u32)(hdr_sz + pix_sz);
    return true;
}

/* ---- Worker thread implementation ---- */
static void io_worker_run(void) {
    while (atomic_load_explicit(&g_loader.running, memory_order_acquire)) {
        u64 slot_idx = 0;
        bool have_work = false;

        async_mutex_lock(&g_loader.queue_mutex);
        u64 head = atomic_load_explicit(&g_loader.request_queue.head, memory_order_acquire);
        u64 tail = atomic_load_explicit(&g_loader.request_queue.tail, memory_order_acquire);
        if (tail < head) {
            have_work = async_dequeue_highest_priority(&slot_idx);
        }
        if (!have_work) {
            async_mutex_lock(&g_loader.wake_mutex);
            head = atomic_load_explicit(&g_loader.request_queue.head, memory_order_acquire);
            tail = atomic_load_explicit(&g_loader.request_queue.tail, memory_order_acquire);
            if (tail >= head && atomic_load_explicit(&g_loader.running, memory_order_acquire)) {
                async_mutex_unlock(&g_loader.queue_mutex);
                async_cond_wait(&g_loader.wake_cond, &g_loader.wake_mutex);
                async_mutex_unlock(&g_loader.wake_mutex);
                async_mutex_lock(&g_loader.queue_mutex);
                head = atomic_load_explicit(&g_loader.request_queue.head, memory_order_acquire);
                tail = atomic_load_explicit(&g_loader.request_queue.tail, memory_order_acquire);
                if (tail < head) {
                    have_work = async_dequeue_highest_priority(&slot_idx);
                }
            } else {
                async_mutex_unlock(&g_loader.wake_mutex);
            }
        }
        async_mutex_unlock(&g_loader.queue_mutex);

        if (!have_work) continue;

        AsyncRequest *req = &g_loader.requests[slot_idx];

        /* Check if cancelled before we start I/O */
        u32 expected = (u32)ASSET_LOADING;
        if (!atomic_compare_exchange_strong_explicit(
                &req->state, &expected, (u32)ASSET_LOADING,
                memory_order_acq_rel, memory_order_acquire)) {
            /* State changed (cancelled), skip */
            atomic_fetch_sub_explicit(&g_loader.pending_count, 1, memory_order_relaxed);
            continue;
        }

        /* Perform the actual file read through VFS */
        if (req->range_length > 0) {
            /* Range-based read (streaming mipmap levels, etc.) */
            VFSFile *f = vfs_open(g_loader.vfs, req->path);
            if (f && f->size > req->range_offset) {
                usize avail = f->size - req->range_offset;
                usize to_read = req->range_length < avail ? req->range_length : avail;
                u8 *data = malloc(to_read);
                if (data) {
                    /* VFS data is a contiguous in-memory buffer — direct memcpy */
                    memcpy(data, f->data + req->range_offset, to_read);
                    req->data = data;
                    req->size = (u32)to_read;
                    atomic_store_explicit(&req->state, (u32)ASSET_READY, memory_order_release);
                } else {
                    req->data = NULL;
                    req->size = 0;
                    atomic_store_explicit(&req->state, (u32)ASSET_FAILED, memory_order_release);
                }
                vfs_close(f);
            } else {
                req->data = NULL;
                req->size = 0;
                atomic_store_explicit(&req->state, (u32)ASSET_FAILED, memory_order_release);
                if (f) vfs_close(f);
                LOG_WARN("Async range load failed: %s (offset=%zu)", req->path, req->range_offset);
            }
        } else {
            /* Full file read */
            usize file_size = 0;
            u8 *data = vfs_read_all(g_loader.vfs, req->path, &file_size);

            if (data && file_size > 0) {
                req->data = data;
                req->size = (u32)file_size;
                if (!async_try_decode_texture(req)) {
                    if (req->data) free(req->data);
                    req->data = NULL;
                    req->size = 0;
                    atomic_store_explicit(&req->state, (u32)ASSET_FAILED, memory_order_release);
                } else {
                    atomic_store_explicit(&req->state, (u32)ASSET_READY, memory_order_release);
                }
            } else {
                req->data = NULL;
                req->size = 0;
                atomic_store_explicit(&req->state, (u32)ASSET_FAILED, memory_order_release);
                LOG_WARN("Async load failed: %s", req->path);
            }
        }

        /* Enqueue into completion queue */
        u64 comp_slot = atomic_fetch_add_explicit(
            &g_loader.completion_queue.head, 1, memory_order_acq_rel);
        g_loader.completion_queue.indices[comp_slot & ASYNC_QUEUE_MASK] = slot_idx;

        atomic_fetch_sub_explicit(&g_loader.pending_count, 1, memory_order_relaxed);
    }
}

#if defined(ASYNC_PLATFORM_WIN32)
static DWORD WINAPI io_worker_win32(LPVOID arg) {
    (void)arg;
    io_worker_run();
    return 0;
}
#else
static void *io_worker_posix(void *arg) {
    (void)arg;
    io_worker_run();
    return NULL;
}
#endif

/* ---- Public API ---- */

void async_loader_init(u32 io_thread_count, VFS *vfs) {
    memset(&g_loader, 0, sizeof(g_loader));

    g_loader.vfs = vfs;
    atomic_store(&g_loader.running, true);
    atomic_store(&g_loader.next_id, 1);
    atomic_store(&g_loader.next_slot, 0);
    atomic_store(&g_loader.pending_count, 0);
    atomic_store(&g_loader.request_queue.head, 0);
    atomic_store(&g_loader.request_queue.tail, 0);
    atomic_store(&g_loader.completion_queue.head, 0);
    atomic_store(&g_loader.completion_queue.tail, 0);

    /* Initialize all request states */
    for (u32 i = 0; i < ASYNC_MAX_REQUESTS; i++) {
        atomic_store(&g_loader.requests[i].state, (u32)ASSET_UNLOADED);
    }

    async_mutex_init(&g_loader.wake_mutex);
    async_cond_init(&g_loader.wake_cond);
    async_mutex_init(&g_loader.queue_mutex);

    /* Clamp thread count */
    if (io_thread_count == 0) io_thread_count = 2;
    if (io_thread_count > 8) io_thread_count = 8;
    g_loader.thread_count = io_thread_count;

    for (u32 i = 0; i < io_thread_count; i++) {
        async_thread_create(&g_loader.threads[i], NULL);
    }

    LOG_INFO("Async loader initialized: %u I/O threads", io_thread_count);
}

void async_loader_shutdown(void) {
    atomic_store_explicit(&g_loader.running, false, memory_order_release);

    /* Wake all threads so they can exit */
    async_mutex_lock(&g_loader.wake_mutex);
    async_cond_broadcast(&g_loader.wake_cond);
    async_mutex_unlock(&g_loader.wake_mutex);

    for (u32 i = 0; i < g_loader.thread_count; i++) {
        async_thread_join(g_loader.threads[i]);
    }

    async_mutex_destroy(&g_loader.wake_mutex);
    async_cond_destroy(&g_loader.wake_cond);
    async_mutex_destroy(&g_loader.queue_mutex);

    /* Free any undelivered loaded data */
    for (u32 i = 0; i < ASYNC_MAX_REQUESTS; i++) {
        u32 st = atomic_load(&g_loader.requests[i].state);
        if (st == (u32)ASSET_READY && g_loader.requests[i].data) {
            free(g_loader.requests[i].data);
            g_loader.requests[i].data = NULL;
        }
    }

    LOG_INFO("Async loader shut down");
}

static u64 async_submit_request(const char *path, AsyncLoadCallback callback, void *user_data,
                                 usize range_offset, usize range_length,
                                 i32 priority, bool decode_texture) {
    if (!path || !callback) return 0;
    if (range_length == 0 && decode_texture == false && range_offset > 0) return 0;

    u32 slot = atomic_fetch_add_explicit(&g_loader.next_slot, 1, memory_order_relaxed)
               % ASYNC_MAX_REQUESTS;

    u32 st = atomic_load(&g_loader.requests[slot].state);
    if (st == (u32)ASSET_LOADING) {
        LOG_ERROR("Async loader: queue full, request dropped: %s", path);
        return 0;
    }

    AsyncRequest *req = &g_loader.requests[slot];
    u64 counter = atomic_fetch_add_explicit(&g_loader.next_id, 1, memory_order_relaxed);
    u64 id = (counter << ASYNC_SLOT_BITS) | (u64)slot;

    strncpy(req->path, path, sizeof(req->path) - 1);
    req->path[sizeof(req->path) - 1] = '\0';
    req->callback = callback;
    req->user_data = user_data;
    req->data = NULL;
    req->size = 0;
    req->id = id;
    req->range_offset = range_offset;
    req->range_length = range_length;
    req->priority = priority;
    req->decode_texture = decode_texture;
    atomic_store_explicit(&req->state, (u32)ASSET_LOADING, memory_order_release);

    async_mutex_lock(&g_loader.queue_mutex);
    u64 head = atomic_fetch_add_explicit(&g_loader.request_queue.head, 1, memory_order_acq_rel);
    g_loader.request_queue.indices[head & ASYNC_QUEUE_MASK] = slot;
    async_mutex_unlock(&g_loader.queue_mutex);

    atomic_fetch_add_explicit(&g_loader.pending_count, 1, memory_order_relaxed);

    async_mutex_lock(&g_loader.wake_mutex);
    async_cond_broadcast(&g_loader.wake_cond);
    async_mutex_unlock(&g_loader.wake_mutex);

    return id;
}

u64 async_loader_request(const char *path, AsyncLoadCallback callback, void *user_data) {
    return async_submit_request(path, callback, user_data, 0, 0,
                                ASYNC_PRIORITY_DEFAULT, false);
}

void async_loader_tick(void) {
    u64 tail = atomic_load_explicit(&g_loader.completion_queue.tail, memory_order_acquire);
    u64 head = atomic_load_explicit(&g_loader.completion_queue.head, memory_order_acquire);

    while (tail < head) {
        u64 idx = g_loader.completion_queue.indices[tail & ASYNC_QUEUE_MASK];
        AsyncRequest *req = &g_loader.requests[idx];

        u32 st = atomic_load_explicit(&req->state, memory_order_acquire);

        if (st == (u32)ASSET_READY || st == (u32)ASSET_FAILED) {
            if (req->callback) {
                req->callback(req->user_data, req->data, req->size);
            }
            /* Data ownership transferred to callback; clear slot */
            req->data = NULL;
            req->callback = NULL;
            atomic_store_explicit(&req->state, (u32)ASSET_UNLOADED, memory_order_release);
        }

        tail++;
    }

    atomic_store_explicit(&g_loader.completion_queue.tail, tail, memory_order_release);
}

AssetState async_loader_status(u64 request_id) {
    /* O(1): extract slot from encoded request ID */
    u32 slot = (u32)(request_id & ASYNC_SLOT_MASK);
    if (slot < ASYNC_MAX_REQUESTS && g_loader.requests[slot].id == request_id) {
        return (AssetState)atomic_load_explicit(&g_loader.requests[slot].state, memory_order_acquire);
    }
    return ASSET_UNLOADED;
}

bool async_loader_cancel(u64 request_id) {
    /* O(1): extract slot from encoded request ID */
    u32 slot = (u32)(request_id & ASYNC_SLOT_MASK);
    if (slot < ASYNC_MAX_REQUESTS && g_loader.requests[slot].id == request_id) {
        u32 expected = (u32)ASSET_LOADING;
        if (atomic_compare_exchange_strong_explicit(
                &g_loader.requests[slot].state, &expected, (u32)ASSET_CANCELLED,
                memory_order_acq_rel, memory_order_acquire)) {
            LOG_DEBUG("Async request cancelled: %s", g_loader.requests[slot].path);
            return true;
        }
        return false;
    }
    return false;
}

u32 async_loader_pending_count(void) {
    return atomic_load_explicit(&g_loader.pending_count, memory_order_relaxed);
}

u64 async_loader_request_range(const char *path, usize offset, usize length,
                                AsyncLoadCallback callback, void *user_data) {
    if (length == 0) return 0;
    return async_submit_request(path, callback, user_data, offset, length,
                                ASYNC_PRIORITY_DEFAULT, false);
}

u64 async_loader_request_range_priority(const char *path, usize offset, usize length,
                                         AsyncLoadCallback callback, void *user_data,
                                         i32 priority) {
    if (length == 0) return 0;
    return async_submit_request(path, callback, user_data, offset, length,
                                priority, false);
}

u64 async_loader_request_priority(const char *path, AsyncLoadCallback callback,
                                   void *user_data, i32 priority) {
    return async_submit_request(path, callback, user_data, 0, 0, priority, false);
}

u64 async_loader_request_texture(const char *path, AsyncLoadCallback callback,
                                  void *user_data, i32 priority) {
    return async_submit_request(path, callback, user_data, 0, 0, priority, true);
}
