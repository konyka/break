#include <asset/decode_pipeline.h>
#include <asset/async_loader.h>
#include "async_loader_private.h"
#include <core/log.h>

#include <stb_image.h>

#include <stdlib.h>
#include <string.h>
#include <stdatomic.h>

/* ---- Configuration ---- */
#define DECODE_WORKER_COUNT 2
#define DECODE_INPUT_CAP    256

/* ---- Job queue (input) ---- */
typedef struct DecodeJob {
    struct DecodeJob *next;
    void             *raw_data;  /* owned by decode pipeline */
    u32               raw_size;
    u64               slot;
    u64               request_id;
    i32               priority;
} DecodeJob;

typedef struct {
    DecodeJob *head;
    DecodeJob *tail;
    u32        count;
    AsyncMutex mutex;
    AsyncCond  cond;
} DecodeInputQueue;

/* ---- Ready queue (completed results) ---- */
typedef struct DecodeResultNode {
    struct DecodeResultNode *next;
    DecodeResult             result;
} DecodeResultNode;

typedef struct {
    DecodeResultNode *head;
    DecodeResultNode *tail;
    AsyncMutex        mutex;
} DecodeReadyQueue;

typedef struct {
    AsyncThread threads[DECODE_WORKER_COUNT];
    _Atomic bool running;

    DecodeInputQueue input;
    DecodeReadyQueue ready;

} DecodePipelineState;

static DecodePipelineState g_decode;

/* ---- Mipmap generation ---- */

static u8 *downsample_rgba8_box(const u8 *src, u32 src_w, u32 src_h,
                                u32 *out_w, u32 *out_h) {
    u32 dst_w = src_w > 1 ? src_w / 2 : 1;
    u32 dst_h = src_h > 1 ? src_h / 2 : 1;

    u8 *dst = (u8 *)malloc((usize)dst_w * dst_h * 4u);
    if (!dst) return NULL;

    for (u32 y = 0; y < dst_h; y++) {
        for (u32 x = 0; x < dst_w; x++) {
            u32 r = 0, g = 0, b = 0, a = 0;
            u32 samples = 0;

            for (u32 sy = 0; sy < 2; sy++) {
                u32 py = y * 2 + sy;
                if (py >= src_h) continue;
                for (u32 sx = 0; sx < 2; sx++) {
                    u32 px = x * 2 + sx;
                    if (px >= src_w) continue;
                    const u8 *p = src + ((usize)py * src_w + px) * 4u;
                    r += p[0]; g += p[1]; b += p[2]; a += p[3];
                    samples++;
                }
            }

            u8 *out = dst + ((usize)y * dst_w + x) * 4u;
            if (samples > 0) {
                out[0] = (u8)(r / samples);
                out[1] = (u8)(g / samples);
                out[2] = (u8)(b / samples);
                out[3] = (u8)(a / samples);
            } else {
                out[0] = out[1] = out[2] = out[3] = 0;
            }
        }
    }

    *out_w = dst_w;
    *out_h = dst_h;
    return dst;
}

static bool decode_generate_mipchain(const u8 *raw, u32 raw_size, DecodeResult *out) {
    int w = 0, h = 0, ch = 0;
    u8 *base = stbi_load_from_memory(raw, (int)raw_size, &w, &h, &ch, 4);
    if (!base || w <= 0 || h <= 0) return false;

    u32 base_w = (u32)w;
    u32 base_h = (u32)h;

    /* Count mipmap levels. */
    u32 mip_count = 1;
    u32 tw = base_w, th = base_h;
    while (tw > 1 || th > 1) {
        tw = tw > 1 ? tw / 2 : 1;
        th = th > 1 ? th / 2 : 1;
        mip_count++;
    }

    /* Compute level offsets/sizes. */
    u32 widths[16];
    u32 heights[16];
    u32 offsets[16];
    usize total_pix = 0;

    tw = base_w; th = base_h;
    for (u32 i = 0; i < mip_count; i++) {
        widths[i] = tw;
        heights[i] = th;
        offsets[i] = (u32)total_pix;
        total_pix += (usize)tw * th * 4u;
        tw = tw > 1 ? tw / 2 : 1;
        th = th > 1 ? th / 2 : 1;
    }

    usize hdr_sz = sizeof(AsyncTextureHeader);
    u8 *packed = (u8 *)malloc(hdr_sz + total_pix);
    if (!packed) {
        stbi_image_free(base);
        return false;
    }

    AsyncTextureHeader *hdr = (AsyncTextureHeader *)packed;
    hdr->width = base_w;
    hdr->height = base_h;
    hdr->pixel_bytes = 4u;
    hdr->mip_count = mip_count;

    memcpy(packed + hdr_sz + offsets[0], base, (usize)base_w * base_h * 4u);
    stbi_image_free(base);

    for (u32 i = 1; i < mip_count; i++) {
        u32 next_w, next_h;
        u8 *next = downsample_rgba8_box(packed + hdr_sz + offsets[i - 1],
                                        widths[i - 1], heights[i - 1],
                                        &next_w, &next_h);
        if (!next) {
            free(packed);
            return false;
        }
        memcpy(packed + hdr_sz + offsets[i], next, (usize)next_w * next_h * 4u);
        free(next);
    }

    out->data = packed;
    out->size = (u32)(hdr_sz + total_pix);
    out->success = true;
    return true;
}

/* ---- Queue helpers ---- */

static void input_queue_push(DecodeJob *job) {
    async_mutex_lock(&g_decode.input.mutex);
    job->next = NULL;
    if (g_decode.input.tail) {
        g_decode.input.tail->next = job;
    } else {
        g_decode.input.head = job;
    }
    g_decode.input.tail = job;
    g_decode.input.count++;
    async_cond_broadcast(&g_decode.input.cond);
    async_mutex_unlock(&g_decode.input.mutex);
}

static DecodeJob *input_queue_pop(void) {
    async_mutex_lock(&g_decode.input.mutex);
    while (!g_decode.input.head && atomic_load_explicit(&g_decode.running, memory_order_acquire)) {
        async_cond_wait(&g_decode.input.cond, &g_decode.input.mutex);
    }
    DecodeJob *job = g_decode.input.head;
    if (job) {
        g_decode.input.head = job->next;
        if (!g_decode.input.head) g_decode.input.tail = NULL;
        g_decode.input.count--;
    }
    async_mutex_unlock(&g_decode.input.mutex);
    return job;
}

static void ready_queue_push(DecodeResultNode *node) {
    async_mutex_lock(&g_decode.ready.mutex);
    node->next = NULL;
    if (g_decode.ready.tail) {
        g_decode.ready.tail->next = node;
    } else {
        g_decode.ready.head = node;
    }
    g_decode.ready.tail = node;
    async_mutex_unlock(&g_decode.ready.mutex);
}

/* ---- Worker thread ---- */

static void decode_worker_run(void) {
    while (atomic_load_explicit(&g_decode.running, memory_order_acquire)) {
        DecodeJob *job = input_queue_pop();
        if (!job) continue;

        DecodeResultNode *node = (DecodeResultNode *)malloc(sizeof(DecodeResultNode));
        if (!node) {
            free(job->raw_data);
            free(job);
            continue;
        }

        node->result.slot = job->slot;
        node->result.request_id = job->request_id;

        if (!decode_generate_mipchain((u8 *)job->raw_data, job->raw_size, &node->result)) {
            node->result.data = NULL;
            node->result.size = 0;
            node->result.success = false;
        }

        free(job->raw_data);
        free(job);

        ready_queue_push(node);
    }
}

#if defined(ASYNC_PLATFORM_WIN32)
static DWORD WINAPI decode_worker_win32(LPVOID arg) {
    (void)arg;
    decode_worker_run();
    return 0;
}
#else
static void *decode_worker_posix(void *arg) {
    (void)arg;
    decode_worker_run();
    return NULL;
}
#endif

static AsyncThreadFn decode_worker_fn(void) {
#if defined(ASYNC_PLATFORM_WIN32)
    return decode_worker_win32;
#else
    return decode_worker_posix;
#endif
}

/* ---- Public API ---- */

bool decode_pipeline_init(void) {
    memset(&g_decode, 0, sizeof(g_decode));
    atomic_store(&g_decode.running, true);

    async_mutex_init(&g_decode.input.mutex);
    async_cond_init(&g_decode.input.cond);
    async_mutex_init(&g_decode.ready.mutex);

    AsyncThreadFn fn = decode_worker_fn();
    for (u32 i = 0; i < DECODE_WORKER_COUNT; i++) {
        async_thread_create(&g_decode.threads[i], fn, NULL);
    }

    LOG_INFO("Decode pipeline initialized: %u workers", DECODE_WORKER_COUNT);
    return true;
}

void decode_pipeline_shutdown(void) {
    atomic_store_explicit(&g_decode.running, false, memory_order_release);

    async_mutex_lock(&g_decode.input.mutex);
    async_cond_broadcast(&g_decode.input.cond);
    async_mutex_unlock(&g_decode.input.mutex);

    for (u32 i = 0; i < DECODE_WORKER_COUNT; i++) {
        async_thread_join(g_decode.threads[i]);
    }

    /* Free any jobs that were still waiting. */
    async_mutex_lock(&g_decode.input.mutex);
    DecodeJob *job = g_decode.input.head;
    while (job) {
        DecodeJob *next = job->next;
        free(job->raw_data);
        free(job);
        job = next;
    }
    g_decode.input.head = NULL;
    g_decode.input.tail = NULL;
    g_decode.input.count = 0;
    async_mutex_unlock(&g_decode.input.mutex);

    /* Free any completed results that were not polled. */
    async_mutex_lock(&g_decode.ready.mutex);
    DecodeResultNode *node = g_decode.ready.head;
    while (node) {
        DecodeResultNode *next = node->next;
        if (node->result.data) free(node->result.data);
        free(node);
        node = next;
    }
    g_decode.ready.head = NULL;
    g_decode.ready.tail = NULL;
    async_mutex_unlock(&g_decode.ready.mutex);

    async_mutex_destroy(&g_decode.input.mutex);
    async_cond_destroy(&g_decode.input.cond);
    async_mutex_destroy(&g_decode.ready.mutex);

    LOG_INFO("Decode pipeline shut down");
}

bool decode_pipeline_submit(void *raw_data, u32 raw_size, u64 slot, u64 request_id, i32 priority) {
    if (!raw_data || raw_size == 0) return false;
    if (!atomic_load_explicit(&g_decode.running, memory_order_acquire)) return false;

    DecodeJob *job = (DecodeJob *)malloc(sizeof(DecodeJob));
    if (!job) return false;

    job->raw_data = raw_data;
    job->raw_size = raw_size;
    job->slot = slot;
    job->request_id = request_id;
    job->priority = priority;
    job->next = NULL;

    input_queue_push(job);
    return true;
}

bool decode_pipeline_poll(DecodeResult *out_result) {
    if (!out_result) return false;

    async_mutex_lock(&g_decode.ready.mutex);
    DecodeResultNode *node = g_decode.ready.head;
    if (node) {
        g_decode.ready.head = node->next;
        if (!g_decode.ready.head) g_decode.ready.tail = NULL;
        *out_result = node->result;
        free(node);
    }
    async_mutex_unlock(&g_decode.ready.mutex);

    return node != NULL;
}

u32 decode_pipeline_queue_count(void) {
    u32 count = 0;
    async_mutex_lock(&g_decode.input.mutex);
    count = g_decode.input.count;
    async_mutex_unlock(&g_decode.input.mutex);
    return count;
}
