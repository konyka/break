#include <asset/async_loader.h>
#include <asset/vfs.h>
#include <asset/decode_pipeline.h>
#include "async_loader_private.h"
#include <core/log.h>

#include <limits.h>
#include <stdatomic.h>
#include <stdlib.h>
#include <string.h>

/* ---- Constants ---- */
#define ASYNC_HEAP_SIZE        256   /* Pending request heap capacity */
/* R165-A: Queue capacity must match max requests to prevent MPSC ring-buffer
 * overflow. With ASYNC_QUEUE_SIZE=256 and ASYNC_MAX_REQUESTS=1024, if more than
 * 256 completions are enqueued before the consumer drains them, older entries
 * are silently overwritten by newer producers, causing stale/corrupted data. */
#define ASYNC_QUEUE_SIZE       1024  /* Completion queue capacity; power of 2 */
#define ASYNC_QUEUE_MASK       (ASYNC_QUEUE_SIZE - 1)
#define ASYNC_MAX_REQUESTS     1024
#define ASYNC_SLOT_BITS        10    /* log2(1024) */
#define ASYNC_SLOT_MASK        (ASYNC_MAX_REQUESTS - 1)

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
    bool              decode_texture; /* run stbi on a decode worker after full read */
} AsyncRequest;

/* Priority-ordered binary min-heap. Protected by queue_mutex. */
typedef struct {
    u64 slot;
    i32 priority;
    u64 seq;  /* insertion sequence for FIFO tie-breaking within same priority */
} HeapItem;

typedef struct {
    HeapItem items[ASYNC_HEAP_SIZE];
    u32      count;
} RequestHeap;

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

    RequestHeap     request_heap;
    CompletionQueue completion_queue;
    _Atomic u64     next_seq;

    AsyncMutex      queue_mutex; /* protects request_heap and wake_cond */
    AsyncCond       wake_cond;

    VFS            *vfs;
} AsyncLoaderState;

static AsyncLoaderState g_loader;

/* ---- Heap helpers ---- */

static bool heap_item_higher(const HeapItem *a, const HeapItem *b) {
    if (a->priority != b->priority) return a->priority < b->priority;
    return a->seq < b->seq;
}

static void heap_sift_up(RequestHeap *heap, u32 idx) {
    while (idx > 0) {
        u32 parent = (idx - 1) / 2;
        if (heap_item_higher(&heap->items[idx], &heap->items[parent])) {
            HeapItem tmp = heap->items[idx];
            heap->items[idx] = heap->items[parent];
            heap->items[parent] = tmp;
            idx = parent;
        } else {
            break;
        }
    }
}

static void heap_sift_down(RequestHeap *heap, u32 idx) {
    while (true) {
        u32 left  = 2 * idx + 1;
        u32 right = 2 * idx + 2;
        u32 smallest = idx;

        if (left < heap->count &&
            heap_item_higher(&heap->items[left], &heap->items[smallest])) {
            smallest = left;
        }
        if (right < heap->count &&
            heap_item_higher(&heap->items[right], &heap->items[smallest])) {
            smallest = right;
        }
        if (smallest == idx) break;

        HeapItem tmp = heap->items[idx];
        heap->items[idx] = heap->items[smallest];
        heap->items[smallest] = tmp;
        idx = smallest;
    }
}

static bool heap_push(RequestHeap *heap, u64 slot, i32 priority, u64 seq) {
    if (heap->count >= ASYNC_HEAP_SIZE) return false;
    u32 idx = heap->count++;
    heap->items[idx].slot = slot;
    heap->items[idx].priority = priority;
    heap->items[idx].seq = seq;
    heap_sift_up(heap, idx);
    return true;
}

static bool heap_pop(RequestHeap *heap, u64 *out_slot) {
    if (heap->count == 0) return false;
    *out_slot = heap->items[0].slot;
    heap->items[0] = heap->items[--heap->count];
    if (heap->count > 0) heap_sift_down(heap, 0);
    return true;
}

static void enqueue_completion(u64 slot_idx) {
    u64 comp_slot = atomic_fetch_add_explicit(
        &g_loader.completion_queue.head, 1, memory_order_acq_rel);
    g_loader.completion_queue.indices[comp_slot & ASYNC_QUEUE_MASK] = slot_idx;
}

/* R165-C: Atomically transition request from ASSET_LOADING to a final state.
 * If the request was cancelled (state changed to ASSET_CANCELLED by the main
 * thread while the worker was doing I/O), free any allocated data and skip
 * completion enqueue. This prevents the worker from overwriting ASSET_CANCELLED
 * with ASSET_READY, which would cause the callback to fire even though the
 * caller believes the request was cancelled.
 *
 * Returns true if the state was set successfully, false if cancelled. */
static bool async_finalize(u32 slot_idx, AssetState final_state) {
    AsyncRequest *req = &g_loader.requests[slot_idx];
    u32 expected = (u32)ASSET_LOADING;
    if (!atomic_compare_exchange_strong_explicit(
            &req->state, &expected, (u32)final_state,
            memory_order_acq_rel, memory_order_acquire)) {
        /* State was changed to ASSET_CANCELLED — free data and release slot.
         * R168-A: Must return to UNLOADED so the slot can be safely reused;
         * leaving CANCELLED allowed submit to overwrite an in-flight worker. */
        if (req->data) {
            free(req->data);
            req->data = NULL;
        }
        atomic_store_explicit(&req->state, (u32)ASSET_UNLOADED, memory_order_release);
        atomic_fetch_sub_explicit(&g_loader.pending_count, 1, memory_order_relaxed);
        return false;
    }
    enqueue_completion(slot_idx);
    atomic_fetch_sub_explicit(&g_loader.pending_count, 1, memory_order_relaxed);
    return true;
}

/* ---- Worker thread implementation ---- */

static void io_worker_run(void) {
    while (atomic_load_explicit(&g_loader.running, memory_order_acquire)) {
        u64 slot_idx = 0;
        bool have_work = false;

        async_mutex_lock(&g_loader.queue_mutex);
        while (!have_work &&
               atomic_load_explicit(&g_loader.running, memory_order_acquire) &&
               g_loader.request_heap.count == 0) {
            async_cond_wait(&g_loader.wake_cond, &g_loader.queue_mutex);
        }
        if (atomic_load_explicit(&g_loader.running, memory_order_acquire) &&
            g_loader.request_heap.count > 0) {
            have_work = heap_pop(&g_loader.request_heap, &slot_idx);
        }
        async_mutex_unlock(&g_loader.queue_mutex);

        if (!have_work) continue;

        AsyncRequest *req = &g_loader.requests[slot_idx];

        /* Check if cancelled before we start I/O */
        u32 expected = (u32)ASSET_LOADING;
        if (!atomic_compare_exchange_strong_explicit(
                &req->state, &expected, (u32)ASSET_LOADING,
                memory_order_acq_rel, memory_order_acquire)) {
            /* R168-A: Release CANCELLED (or other non-LOADING) slot to UNLOADED. */
            if (expected == (u32)ASSET_CANCELLED) {
                atomic_store_explicit(&req->state, (u32)ASSET_UNLOADED, memory_order_release);
            }
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
                if (to_read > (usize)UINT32_MAX) {
                    /* R140: Range too large for u32 size field — reject */
                    vfs_close(f);
                    req->data = NULL;
                    req->size = 0;
                    async_finalize(slot_idx, ASSET_FAILED);
                    LOG_WARN("Async range load: range too large (>%u bytes): %s", UINT32_MAX, req->path);
                    continue;
                }
                u8 *data = malloc(to_read);
                if (data) {
                    /* VFS data is a contiguous in-memory buffer — direct memcpy */
                    memcpy(data, f->data + req->range_offset, to_read);
                    req->data = data;
                    req->size = (u32)to_read;
                    vfs_close(f);
                    async_finalize(slot_idx, ASSET_READY);
                } else {
                    req->data = NULL;
                    req->size = 0;
                    vfs_close(f);
                    async_finalize(slot_idx, ASSET_FAILED);
                }
            } else {
                req->data = NULL;
                req->size = 0;
                if (f) vfs_close(f);
                async_finalize(slot_idx, ASSET_FAILED);
                LOG_WARN("Async range load failed: %s (offset=%zu)", req->path, req->range_offset);
            }
        } else {
            /* Full file read
             * R165-B: Same cancel-race protection as range load path (R165-C).
             * All state transitions use async_finalize() for atomic CAS. */
            usize file_size = 0;
            u8 *data = vfs_read_all(g_loader.vfs, req->path, &file_size);

            if (data && file_size > 0) {
                if (file_size > (usize)UINT32_MAX) {
                    /* R140: File too large for u32 size field — reject to prevent truncation */
                    free(data);
                    req->data = NULL;
                    req->size = 0;
                    async_finalize(slot_idx, ASSET_FAILED);
                    LOG_WARN("Async load: file too large (>%u bytes): %s", UINT32_MAX, req->path);
                } else if (req->decode_texture) {
                    /* Offload decode + mip-chain generation to the decode pipeline. */
                    if (decode_pipeline_submit(data, (u32)file_size, slot_idx,
                                               req->id, req->priority)) {
                        req->data = NULL;
                        req->size = 0;
                        /* pending_count is decremented when the decode result is polled. */
                    } else {
                        free(data);
                        req->data = NULL;
                        req->size = 0;
                        async_finalize(slot_idx, ASSET_FAILED);
                    }
                } else {
                    req->data = data;
                    req->size = (u32)file_size;
                    async_finalize(slot_idx, ASSET_READY);
                }
            } else {
                req->data = NULL;
                req->size = 0;
                async_finalize(slot_idx, ASSET_FAILED);
                LOG_WARN("Async load failed: %s", req->path);
            }
        }
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

static AsyncThreadFn io_worker_fn(void) {
#if defined(ASYNC_PLATFORM_WIN32)
    return io_worker_win32;
#else
    return io_worker_posix;
#endif
}

/* ---- Public API ---- */

void async_loader_init(u32 io_thread_count, VFS *vfs) {
    memset(&g_loader, 0, sizeof(g_loader));

    g_loader.vfs = vfs;
    atomic_store(&g_loader.running, true);
    atomic_store(&g_loader.next_id, 1);
    atomic_store(&g_loader.next_slot, 0);
    atomic_store(&g_loader.pending_count, 0);
    atomic_store(&g_loader.next_seq, 1);
    atomic_store(&g_loader.completion_queue.head, 0);
    atomic_store(&g_loader.completion_queue.tail, 0);

    /* Initialize all request states */
    for (u32 i = 0; i < ASYNC_MAX_REQUESTS; i++) {
        atomic_store(&g_loader.requests[i].state, (u32)ASSET_UNLOADED);
    }

    async_mutex_init(&g_loader.queue_mutex);
    async_cond_init(&g_loader.wake_cond);

    if (!decode_pipeline_init()) {
        LOG_ERROR("Async loader: failed to initialize decode pipeline");
    }

    /* Clamp thread count */
    if (io_thread_count == 0) io_thread_count = 2;
    if (io_thread_count > 8) io_thread_count = 8;
    g_loader.thread_count = io_thread_count;

    AsyncThreadFn fn = io_worker_fn();
    u32 started = 0;
    for (u32 i = 0; i < io_thread_count; i++) {
        if (!async_thread_create(&g_loader.threads[i], fn, NULL)) {
            LOG_ERROR("Async loader: failed to create I/O thread %u", i);
            break;
        }
        started++;
    }
    g_loader.thread_count = started;
    if (started == 0) {
        LOG_FATAL("Async loader: failed to create any I/O threads");
    }

    LOG_INFO("Async loader initialized: %u I/O threads", started);
}

void async_loader_shutdown(void) {
    atomic_store_explicit(&g_loader.running, false, memory_order_release);

    /* Wake all I/O threads so they can exit */
    async_mutex_lock(&g_loader.queue_mutex);
    async_cond_broadcast(&g_loader.wake_cond);
    async_mutex_unlock(&g_loader.queue_mutex);

    for (u32 i = 0; i < g_loader.thread_count; i++) {
        async_thread_join(g_loader.threads[i]);
    }

    /* Decode pipeline must shut down after I/O threads have stopped submitting. */
    decode_pipeline_shutdown();

    async_mutex_destroy(&g_loader.queue_mutex);
    async_cond_destroy(&g_loader.wake_cond);

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
    /* R168-A: Only UNLOADED slots are reusable. CANCELLED/READY/FAILED/LOADING
     * all mean an in-flight or unconsumed request still owns the slot — reusing
     * them lets a late worker write another request's file bytes into the new
     * owner's callback (data corruption after invalidate+reload). */
    if (st != (u32)ASSET_UNLOADED) {
        LOG_ERROR("Async loader: slot in use (state=%u), request dropped: %s", st, path);
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

    u64 seq = atomic_fetch_add_explicit(&g_loader.next_seq, 1, memory_order_relaxed);

    async_mutex_lock(&g_loader.queue_mutex);
    bool pushed = heap_push(&g_loader.request_heap, slot, priority, seq);
    if (pushed) async_cond_broadcast(&g_loader.wake_cond);
    async_mutex_unlock(&g_loader.queue_mutex);

    if (!pushed) {
        atomic_store_explicit(&req->state, (u32)ASSET_UNLOADED, memory_order_release);
        LOG_ERROR("Async loader: request heap full, request dropped: %s", path);
        return 0;
    }

    atomic_fetch_add_explicit(&g_loader.pending_count, 1, memory_order_relaxed);
    return id;
}

u64 async_loader_request(const char *path, AsyncLoadCallback callback, void *user_data) {
    return async_submit_request(path, callback, user_data, 0, 0,
                                ASYNC_PRIORITY_DEFAULT, false);
}

void async_loader_tick(void) {
    /* Drain decoded texture results from the decode pipeline and move them to
     * the completion queue. */
    DecodeResult result;
    while (decode_pipeline_poll(&result)) {
        u32 slot = (u32)(result.slot & ASYNC_SLOT_MASK);
        if (slot >= ASYNC_MAX_REQUESTS) {
            if (result.data) free(result.data);
            atomic_fetch_sub_explicit(&g_loader.pending_count, 1, memory_order_relaxed);
            continue;
        }

        AsyncRequest *req = &g_loader.requests[slot];
        u32 st = atomic_load_explicit(&req->state, memory_order_acquire);

        if (req->id != result.request_id || st == (u32)ASSET_CANCELLED) {
            if (result.data) free(result.data);
            if (st == (u32)ASSET_CANCELLED) {
                /* R167-D: Notify owner so user_data (e.g. MipLoadReq) is freed. */
                if (req->callback) {
                    req->callback(req->user_data, NULL, 0);
                    req->callback = NULL;
                    req->user_data = NULL;
                }
                atomic_store_explicit(&req->state, (u32)ASSET_UNLOADED, memory_order_release);
            }
            atomic_fetch_sub_explicit(&g_loader.pending_count, 1, memory_order_relaxed);
            continue;
        }

        req->data = result.data;
        req->size = result.size;
        atomic_store_explicit(&req->state,
                              result.success ? (u32)ASSET_READY : (u32)ASSET_FAILED,
                              memory_order_release);
        enqueue_completion(slot);
        atomic_fetch_sub_explicit(&g_loader.pending_count, 1, memory_order_relaxed);
    }

    /* Dispatch completion callbacks on the main thread. */
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
            /* R167-D: Immediately notify owner with NULL data so user_data can
             * be freed. Worker that finishes later will see CANCELLED and skip
             * enqueue (async_finalize) or free data without a second callback
             * (decode path clears callback here). */
            AsyncRequest *req = &g_loader.requests[slot];
            if (req->callback) {
                req->callback(req->user_data, NULL, 0);
                req->callback = NULL;
                req->user_data = NULL;
            }
            LOG_DEBUG("Async request cancelled: %s", req->path);
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
