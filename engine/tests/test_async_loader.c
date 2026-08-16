#include "test_framework.h"
#include <asset/async_loader.h>
#include <asset/decode_pipeline.h>
#include <asset/vfs.h>
#include <stdatomic.h>
#include <stdio.h>

/* ---- Init/Shutdown ---- */

TEST(async_loader_init_shutdown) {
    VFS *vfs = vfs_create();
    ASSERT_NOT_NULL(vfs);

    async_loader_init(2, vfs);
    async_loader_shutdown();
    vfs_destroy(vfs);
}

/* ---- Pending count starts at zero ---- */

TEST(async_loader_pending_zero) {
    VFS *vfs = vfs_create();
    ASSERT_NOT_NULL(vfs);

    async_loader_init(2, vfs);
    ASSERT_EQ(async_loader_pending_count(), 0u);
    async_loader_shutdown();
    vfs_destroy(vfs);
}

/* ---- Load nonexistent file returns FAILED ---- */

static _Atomic int g_callback_called;
static _Atomic int g_callback_data_null;

static void test_load_callback(void *user_data, void *data, u32 size) {
    (void)user_data;
    (void)size;
    atomic_store(&g_callback_called, 1);
    if (data == NULL) {
        atomic_store(&g_callback_data_null, 1);
    }
}

TEST(async_loader_load_nonexistent) {
    VFS *vfs = vfs_create();
    ASSERT_NOT_NULL(vfs);
    /* Mount a valid directory so VFS is functional */
    vfs_mount_dir(vfs, test_tmp_root());

    async_loader_init(2, vfs);
    atomic_store(&g_callback_called, 0);
    atomic_store(&g_callback_data_null, 0);

    u64 id = async_loader_request("nonexistent_file_xyz_12345.bin",
                                   test_load_callback, NULL);
    ASSERT_NEQ(id, (u64)0);

    /* Wait for completion - poll a few times */
    for (int i = 0; i < 100; i++) {
        async_loader_tick();
        AssetState st = async_loader_status(id);
        if (st == ASSET_FAILED || st == ASSET_READY || st == ASSET_UNLOADED) {
            break;
        }
        /* Small sleep equivalent: busy loop */
        for (volatile int j = 0; j < 100000; j++) { (void)j; }
    }

    async_loader_tick(); /* ensure callback is dispatched */
    ASSERT_EQ(atomic_load(&g_callback_called), 1);
    ASSERT_EQ(atomic_load(&g_callback_data_null), 1);

    async_loader_shutdown();
    vfs_destroy(vfs);
}

/* ---- Status query ---- */

TEST(async_loader_status_loading) {
    VFS *vfs = vfs_create();
    ASSERT_NOT_NULL(vfs);
    vfs_mount_dir(vfs, test_tmp_root());

    async_loader_init(1, vfs);

    u64 id = async_loader_request("another_nonexistent_abc.bin",
                                   test_load_callback, NULL);
    /* Immediately after submission, status should be LOADING (or already processed) */
    AssetState st = async_loader_status(id);
    ASSERT_TRUE(st == ASSET_LOADING || st == ASSET_FAILED || st == ASSET_READY);

    /* Wait for completion */
    for (int i = 0; i < 100; i++) {
        async_loader_tick();
        st = async_loader_status(id);
        if (st != ASSET_LOADING) break;
        for (volatile int j = 0; j < 100000; j++) { (void)j; }
    }

    async_loader_shutdown();
    vfs_destroy(vfs);
}

/* ---- Cancel request ---- */

TEST(async_loader_cancel_request) {
    VFS *vfs = vfs_create();
    ASSERT_NOT_NULL(vfs);

    async_loader_init(1, vfs);

    /* Submit request - cancel might succeed or not depending on timing */
    u64 id = async_loader_request("cancel_test_file.bin",
                                   test_load_callback, NULL);
    /* Try to cancel - we just verify it doesn't crash */
    (void)async_loader_cancel(id);

    /* Drain any pending callbacks */
    for (int i = 0; i < 50; i++) {
        async_loader_tick();
        for (volatile int j = 0; j < 10000; j++) { (void)j; }
    }

    async_loader_shutdown();
    vfs_destroy(vfs);
}

/* ---- Edge Cases ---- */

TEST(async_loader_status_invalid_id) {
    VFS *vfs = vfs_create();
    ASSERT_NOT_NULL(vfs);

    async_loader_init(2, vfs);

    /* Query status for invalid ID - should return a safe state */
    AssetState st = async_loader_status(0);
    ASSERT_TRUE(st == ASSET_UNLOADED || st == ASSET_FAILED || st == ASSET_LOADING || st == ASSET_READY);

    st = async_loader_status(0xFFFFFFFFFFFFFFFFULL);
    ASSERT_TRUE(st == ASSET_UNLOADED || st == ASSET_FAILED || st == ASSET_LOADING || st == ASSET_READY);

    async_loader_shutdown();
    vfs_destroy(vfs);
}

TEST(async_loader_multiple_requests) {
    VFS *vfs = vfs_create();
    ASSERT_NOT_NULL(vfs);
    vfs_mount_dir(vfs, test_tmp_root());

    async_loader_init(2, vfs);
    atomic_store(&g_callback_called, 0);

    /* Submit multiple requests */
    u64 id1 = async_loader_request("multi_test_1.bin", test_load_callback, NULL);
    u64 id2 = async_loader_request("multi_test_2.bin", test_load_callback, NULL);
    u64 id3 = async_loader_request("multi_test_3.bin", test_load_callback, NULL);

    ASSERT_NEQ(id1, (u64)0);
    ASSERT_NEQ(id2, (u64)0);
    ASSERT_NEQ(id3, (u64)0);

    /* All IDs should be unique */
    ASSERT_TRUE(id1 != id2 && id2 != id3 && id1 != id3);

    /* Wait for completion */
    for (int i = 0; i < 100; i++) {
        async_loader_tick();
        for (volatile int j = 0; j < 100000; j++) { (void)j; }
    }

    async_loader_shutdown();
    vfs_destroy(vfs);
}

TEST(async_loader_cancel_invalid_id) {
    VFS *vfs = vfs_create();
    ASSERT_NOT_NULL(vfs);

    async_loader_init(2, vfs);

    /* Cancel with invalid ID - should not crash */
    (void)async_loader_cancel(0);
    (void)async_loader_cancel(0xFFFFFFFFFFFFFFFFULL);

    async_loader_shutdown();
    vfs_destroy(vfs);
}

/* R470: every public request entry stores its path in AsyncRequest.path[256].
 * Accepting a longer string used to queue an I/O request for its truncation. */
TEST(async_loader_rejects_path_truncation) {
    VFS *vfs = vfs_create();
    ASSERT_NOT_NULL(vfs);
    async_loader_init(1, vfs);

    char path[257];
    memset(path, 'x', sizeof(path) - 1u);
    path[sizeof(path) - 1u] = '\0';

    ASSERT_EQ(async_loader_request(path, test_load_callback, NULL), (u64)0);
    ASSERT_EQ(async_loader_pending_count(), 0u);

    async_loader_shutdown();
    vfs_destroy(vfs);
}

/* High-priority requests should complete before lower-priority ones queued earlier. */
static _Atomic int g_pri_order[4];
static _Atomic int g_pri_order_count;

static void pri_cb_low(void *user, void *data, u32 size) {
    (void)user; (void)data; (void)size;
    int i = atomic_fetch_add(&g_pri_order_count, 1);
    if (i < 4) g_pri_order[i] = 1;
    if (data) free(data);
}

static void pri_cb_high(void *user, void *data, u32 size) {
    (void)user; (void)data; (void)size;
    int i = atomic_fetch_add(&g_pri_order_count, 1);
    if (i < 4) g_pri_order[i] = 0;
    if (data) free(data);
}

TEST(async_loader_priority_ordering) {
    VFS *vfs = vfs_create();
    ASSERT_NOT_NULL(vfs);
    vfs_mount_dir(vfs, test_tmp_root());

    /* Queue one low-priority file before the high-priority file, then another
     * low after it. This makes the completion order deterministic with a
     * single I/O worker: the worker can finish low_a before high is enqueued,
     * but it cannot also finish low_b before low_b is enqueued. */
    /* R444: per-pid paths — same-tree parallel ctest shared the cwd-relative files. */
    char pa[128], pb[128], pc[128];
    test_tmp(pa, sizeof pa, "async_pri_low_a.bin");
    test_tmp(pb, sizeof pb, "async_pri_low_b.bin");
    test_tmp(pc, sizeof pc, "async_pri_high.bin");
    FILE *fa = fopen(pa, "wb");
    FILE *fb = fopen(pb, "wb");
    FILE *fc = fopen(pc, "wb");
    ASSERT_NOT_NULL(fa);
    ASSERT_NOT_NULL(fb);
    ASSERT_NOT_NULL(fc);
    u8 data[64];
    memset(data, 0xAB, sizeof(data));
    fwrite(data, 1, sizeof(data), fa);
    fwrite(data, 1, sizeof(data), fb);
    memset(data, 0xCD, sizeof(data));
    fwrite(data, 1, sizeof(data), fc);
    fclose(fa);
    fclose(fb);
    fclose(fc);

    /* Use a single I/O worker so the priority guarantee is deterministic:
     * at most one low-priority request can be in flight at any moment, so the
     * other low remains queued when the high-priority request arrives, and the
     * heap serves the high-priority one before that still-queued low. With 2+
     * workers both lows could be grabbed before the high is even enqueued,
     * which is an inherent scheduling race rather than a priority-heap bug. */
    async_loader_init(1, vfs);
    atomic_store(&g_pri_order_count, 0);

    /* Basenames: the /tmp mount resolves them to the per-pid files above. */
    u64 id_low_a = async_loader_request_priority(strrchr(pa, '/') + 1, pri_cb_low, NULL, 100);
    u64 id_high  = async_loader_request_priority(strrchr(pc, '/') + 1, pri_cb_high, NULL, 0);
    u64 id_low_b = async_loader_request_priority(strrchr(pb, '/') + 1, pri_cb_low, NULL, 100);
    ASSERT_NEQ(id_low_a, (u64)0);
    ASSERT_NEQ(id_low_b, (u64)0);
    ASSERT_NEQ(id_high, (u64)0);

    for (int i = 0; i < 500; i++) {
        async_loader_tick();
        if (atomic_load(&g_pri_order_count) >= 3) break;
        for (volatile int j = 0; j < 50000; j++) { (void)j; }
    }

    ASSERT_EQ(atomic_load(&g_pri_order_count), 3);

    /* The high-priority request must complete before at least one of the
     * lower-priority requests that were submitted before it. */
    bool high_before_a_low = false;
    bool saw_high = false;
    for (int i = 0; i < 3; i++) {
        if (g_pri_order[i] == 0) saw_high = true;
        if (saw_high && g_pri_order[i] == 1) {
            high_before_a_low = true;
            break;
        }
    }
    ASSERT_TRUE(high_before_a_low);

    async_loader_shutdown();
    vfs_destroy(vfs);
    remove(pa);
    remove(pb);
    remove(pc);
}

/* Texture decode should happen off the main thread; the main thread must stay responsive. */
static _Atomic int g_decode_cb_called;
static _Atomic int g_decode_success;
static _Atomic int g_decode_mip_count;

static void decode_cb(void *user, void *data, u32 size) {
    (void)user;
    atomic_store(&g_decode_cb_called, 1);
    if (data && size >= sizeof(AsyncTextureHeader)) {
        AsyncTextureHeader *hdr = (AsyncTextureHeader *)data;
        if (hdr->width == 2 && hdr->height == 2 && hdr->pixel_bytes == 4 && hdr->mip_count >= 1) {
            atomic_store(&g_decode_success, 1);
        }
        atomic_store(&g_decode_mip_count, (int)hdr->mip_count);
    }
    if (data) free(data);
}

TEST(async_loader_decode_non_blocking) {
    VFS *vfs = vfs_create();
    ASSERT_NOT_NULL(vfs);
    vfs_mount_dir(vfs, test_tmp_root());

    /* Write a minimal 2x2 32-bit uncompressed TGA file. */
    char pt[128]; /* R444: per-pid path */
    test_tmp(pt, sizeof pt, "async_decode_test.tga");
    FILE *f = fopen(pt, "wb");
    ASSERT_NOT_NULL(f);
    u8 header[18] = {0};
    header[2] = 2;      /* uncompressed true-color */
    header[12] = 2;     /* width = 2 */
    header[14] = 2;     /* height = 2 */
    header[16] = 32;    /* bits per pixel */
    header[17] = 0x28;  /* 8 alpha bits, top-left origin */
    fwrite(header, 1, 18, f);
    /* BGRA pixels */
    u8 pixels[16] = {
        0x00, 0x00, 0xFF, 0xFF,  /* red */
        0x00, 0xFF, 0x00, 0xFF,  /* green */
        0xFF, 0x00, 0x00, 0xFF,  /* blue */
        0xFF, 0xFF, 0xFF, 0xFF   /* white */
    };
    fwrite(pixels, 1, 16, f);
    fclose(f);

    async_loader_init(1, vfs);
    atomic_store(&g_decode_cb_called, 0);
    atomic_store(&g_decode_success, 0);
    atomic_store(&g_decode_mip_count, 0);

    u64 id = async_loader_request_texture(strrchr(pt, '/') + 1, decode_cb, NULL, 0);
    ASSERT_NEQ(id, (u64)0);

    /* Main thread pumps ticks without blocking on decode. */
    int ticks = 0;
    for (int i = 0; i < 500; i++) {
        async_loader_tick();
        ticks++;
        if (atomic_load(&g_decode_cb_called)) break;
        for (volatile int j = 0; j < 50000; j++) { (void)j; }
    }

    ASSERT_TRUE(ticks > 0);
    ASSERT_EQ(atomic_load(&g_decode_cb_called), 1);
    ASSERT_EQ(atomic_load(&g_decode_success), 1);
    ASSERT_TRUE(atomic_load(&g_decode_mip_count) >= 1);

    async_loader_shutdown();
    vfs_destroy(vfs);
    remove(pt);
}

/* R394: range reads used to succeed with to_read < range_length, feeding short
 * buffers into mipmap_stream. A 64-byte file requested as 256 bytes must fail. */
static _Atomic int g_range_cb_called;
static _Atomic int g_range_cb_null;

static void range_trunc_cb(void *user, void *data, u32 size) {
    (void)user; (void)size;
    atomic_store(&g_range_cb_called, 1);
    if (!data) atomic_store(&g_range_cb_null, 1);
    if (data) free(data);
}

TEST(async_loader_range_truncated_fails)
{
    VFS *vfs = vfs_create();
    ASSERT_NOT_NULL(vfs);
    vfs_mount_dir(vfs, test_tmp_root());

    char pr[128]; /* R444: per-pid path */
    test_tmp(pr, sizeof pr, "async_range_short.bin");
    FILE *f = fopen(pr, "wb");
    ASSERT_NOT_NULL(f);
    u8 blob[64];
    memset(blob, 0xAB, sizeof(blob));
    fwrite(blob, 1, sizeof(blob), f);
    fclose(f);

    async_loader_init(1, vfs);
    atomic_store(&g_range_cb_called, 0);
    atomic_store(&g_range_cb_null, 0);

    u64 id = async_loader_request_range(strrchr(pr, '/') + 1, 0, 256,
                                        range_trunc_cb, NULL);
    ASSERT_NEQ(id, (u64)0);

    for (int i = 0; i < 200; i++) {
        async_loader_tick();
        if (atomic_load(&g_range_cb_called)) break;
        for (volatile int j = 0; j < 50000; j++) { (void)j; }
    }

    ASSERT_EQ(atomic_load(&g_range_cb_called), 1);
    ASSERT_EQ(atomic_load(&g_range_cb_null), 1);

    async_loader_shutdown();
    vfs_destroy(vfs);
    remove(pr);
}

/* The public range API documents length=0 as "read to end". The old wrapper
 * rejected that request before it reached a worker. */
static _Atomic int g_range_to_end_called;
static _Atomic int g_range_to_end_size;

static void range_to_end_cb(void *user, void *data, u32 size) {
    (void)user;
    atomic_store(&g_range_to_end_called, 1);
    atomic_store(&g_range_to_end_size, (int)size);
    if (data) free(data);
}

TEST(async_loader_range_zero_reads_to_end)
{
    VFS *vfs = vfs_create();
    ASSERT_NOT_NULL(vfs);
    vfs_mount_dir(vfs, test_tmp_root());

    char path[128];
    test_tmp(path, sizeof path, "async_range_to_end.bin");
    FILE *f = fopen(path, "wb");
    ASSERT_NOT_NULL(f);
    const u8 payload[] = { 1, 2, 3, 4, 5, 6 };
    ASSERT_EQ(fwrite(payload, 1, sizeof payload, f), sizeof payload);
    ASSERT_EQ(fclose(f), 0);

    async_loader_init(1, vfs);
    atomic_store(&g_range_to_end_called, 0);
    atomic_store(&g_range_to_end_size, 0);
    u64 id = async_loader_request_range(strrchr(path, '/') + 1, 2, 0,
                                        range_to_end_cb, NULL);
    ASSERT_NEQ(id, (u64)0);
    for (int i = 0; i < 200; i++) {
        async_loader_tick();
        if (atomic_load(&g_range_to_end_called)) break;
        for (volatile int j = 0; j < 50000; j++) { (void)j; }
    }
    ASSERT_EQ(atomic_load(&g_range_to_end_called), 1);
    ASSERT_EQ(atomic_load(&g_range_to_end_size), 4);

    async_loader_shutdown();
    vfs_destroy(vfs);
    remove(path);
}

/* R402: completion ring must not overwrite when main thread drains slowly. */
static _Atomic int g_burst_cb_count;

static void burst_cb(void *user, void *data, u32 size) {
    (void)user; (void)size;
    atomic_fetch_add(&g_burst_cb_count, 1);
    if (data) free(data);
}

TEST(async_loader_completion_burst)
{
    VFS *vfs = vfs_create();
    ASSERT_NOT_NULL(vfs);
    vfs_mount_dir(vfs, test_tmp_root());

    async_loader_init(8, vfs);
    atomic_store(&g_burst_cb_count, 0);

    const int N = 1200;
    char path[64];
    for (int i = 0; i < N; i++) {
        snprintf(path, sizeof(path), "async_burst_%d.bin", i);
        while (async_loader_request(path, burst_cb, NULL) == 0) {
            async_loader_tick();
            for (volatile int j = 0; j < 1000; j++) { (void)j; }
        }
        if ((i & 31) == 0) async_loader_tick();
    }

    for (int i = 0; i < 200000; i++) {
        async_loader_tick();
        if (atomic_load(&g_burst_cb_count) >= N &&
            async_loader_pending_count() == 0)
            break;
        for (volatile int j = 0; j < 5000; j++) { (void)j; }
    }

    ASSERT_EQ(atomic_load(&g_burst_cb_count), N);

    async_loader_shutdown();
    vfs_destroy(vfs);
}

/* R431: shutdown used to drop requests still sitting in the request heap
 * (state LOADING, never picked up by a worker) without firing their
 * callback, leaking their user_data. Shutdown must notify them with
 * (NULL, 0), exactly like async_loader_cancel. */
static _Atomic int g_sd_cb_count;
static _Atomic int g_sd_cb_null;
static _Atomic int g_sd_cb_data;

static void shutdown_pending_cb(void *user, void *data, u32 size) {
    (void)user; (void)size;
    atomic_fetch_add(&g_sd_cb_count, 1);
    if (!data) atomic_fetch_add(&g_sd_cb_null, 1);
    if (data) {
        atomic_fetch_add(&g_sd_cb_data, 1);
        free(data);
    }
}

TEST(async_loader_shutdown_fires_pending_callbacks)
{
    VFS *vfs = vfs_create();
    ASSERT_NOT_NULL(vfs);
    vfs_mount_dir(vfs, test_tmp_root());

    /* One shared 1 MiB file keeps the single worker busy long enough that
     * most requests are still queued when shutdown runs. */
    char ps[128]; /* R444: per-pid path */
    test_tmp(ps, sizeof ps, "async_shutdown_pending.bin");
    FILE *f = fopen(ps, "wb");
    ASSERT_NOT_NULL(f);
    u8 blob[4096];
    memset(blob, 0x5A, sizeof(blob));
    for (int i = 0; i < 256; i++) fwrite(blob, 1, sizeof(blob), f);
    fclose(f);

    async_loader_init(1, vfs);
    atomic_store(&g_sd_cb_count, 0);
    atomic_store(&g_sd_cb_null, 0);
    atomic_store(&g_sd_cb_data, 0);

    const int N = 64;
    int submitted = 0;
    for (int i = 0; i < N; i++) {
        if (async_loader_request(strrchr(ps, '/') + 1,
                                 shutdown_pending_cb, NULL) != 0)
            submitted++;
    }
    ASSERT_EQ(submitted, N);

    /* No tick: queued requests remain LOADING while an early request may
     * already be READY. Shutdown must notify every accepted request exactly
     * once, preserving data for READY entries and using NULL for LOADING. */
    async_loader_shutdown();

    ASSERT_EQ(atomic_load(&g_sd_cb_count), submitted);
    ASSERT_TRUE(atomic_load(&g_sd_cb_null) >= 1);
    ASSERT_EQ(atomic_load(&g_sd_cb_count),
              atomic_load(&g_sd_cb_null) + atomic_load(&g_sd_cb_data));

    vfs_destroy(vfs);
    remove(ps);
}

/* R449: shutdown must drain completions that reached READY/FAILED but were
 * not yet dispatched by the main-thread tick. Dropping these entries leaks
 * callback-owned user data and silently loses successful loads. */
static _Atomic int g_shutdown_ready_cb_count;
static _Atomic int g_shutdown_ready_cb_data;
static _Atomic int g_shutdown_ready_cb_size;

static void shutdown_ready_cb(void *user, void *data, u32 size)
{
    (void)user;
    atomic_fetch_add(&g_shutdown_ready_cb_count, 1);
    if (data) {
        atomic_store(&g_shutdown_ready_cb_data, 1);
        atomic_store(&g_shutdown_ready_cb_size, (int)size);
        free(data);
    }
}

TEST(async_loader_shutdown_drains_ready_completion)
{
    VFS *vfs = vfs_create();
    ASSERT_NOT_NULL(vfs);
    vfs_mount_dir(vfs, test_tmp_root());

    char path[128];
    test_tmp(path, sizeof path, "async_shutdown_ready.bin");
    FILE *f = fopen(path, "wb");
    ASSERT_NOT_NULL(f);
    const u8 payload[] = { 1, 2, 3, 4 };
    ASSERT_EQ(fwrite(payload, 1, sizeof(payload), f), sizeof(payload));
    fclose(f);

    async_loader_init(1, vfs);
    atomic_store(&g_shutdown_ready_cb_count, 0);
    atomic_store(&g_shutdown_ready_cb_data, 0);
    atomic_store(&g_shutdown_ready_cb_size, 0);

    u64 id = async_loader_request(strrchr(path, '/') + 1,
                                  shutdown_ready_cb, NULL);
    ASSERT_NEQ(id, (u64)0);

    /* Observe completion without draining the main-thread queue. */
    for (int i = 0; i < 200; i++) {
        if (async_loader_status(id) == ASSET_READY) break;
        for (volatile int j = 0; j < 50000; j++) { (void)j; }
    }
    ASSERT_EQ(async_loader_status(id), ASSET_READY);
    ASSERT_EQ(atomic_load(&g_shutdown_ready_cb_count), 0);

    async_loader_shutdown();

    ASSERT_EQ(atomic_load(&g_shutdown_ready_cb_count), 1);
    ASSERT_EQ(atomic_load(&g_shutdown_ready_cb_data), 1);
    ASSERT_EQ(atomic_load(&g_shutdown_ready_cb_size), (int)sizeof(payload));

    vfs_destroy(vfs);
    remove(path);
}

/* R450: decoded textures use a second completion queue. A shutdown between
 * decode completion and async_loader_tick() must retain that result too. */
static _Atomic int g_shutdown_decode_cb_count;
static _Atomic int g_shutdown_decode_cb_valid;

static void shutdown_decode_cb(void *user, void *data, u32 size)
{
    (void)user;
    atomic_fetch_add(&g_shutdown_decode_cb_count, 1);
    if (data && size >= sizeof(AsyncTextureHeader)) {
        AsyncTextureHeader *hdr = (AsyncTextureHeader *)data;
        if (hdr->width == 2 && hdr->height == 2 && hdr->pixel_bytes == 4)
            atomic_store(&g_shutdown_decode_cb_valid, 1);
    }
    free(data);
}

TEST(async_loader_shutdown_drains_decoded_completion)
{
    VFS *vfs = vfs_create();
    ASSERT_NOT_NULL(vfs);
    vfs_mount_dir(vfs, test_tmp_root());

    char path[128];
    test_tmp(path, sizeof path, "async_shutdown_decode.tga");
    FILE *f = fopen(path, "wb");
    ASSERT_NOT_NULL(f);
    u8 header[18] = {0};
    header[2] = 2;
    header[12] = 2;
    header[14] = 2;
    header[16] = 32;
    header[17] = 0x28;
    const u8 pixels[16] = {
        0, 0, 255, 255, 0, 255, 0, 255,
        255, 0, 0, 255, 255, 255, 255, 255
    };
    fwrite(header, 1, sizeof(header), f);
    fwrite(pixels, 1, sizeof(pixels), f);
    fclose(f);

    async_loader_init(1, vfs);
    atomic_store(&g_shutdown_decode_cb_count, 0);
    atomic_store(&g_shutdown_decode_cb_valid, 0);
    u64 id = async_loader_request_texture(strrchr(path, '/') + 1,
                                          shutdown_decode_cb, NULL, 0);
    ASSERT_NEQ(id, (u64)0);

    for (int i = 0; i < 200; i++) {
        if (decode_pipeline_ready_count() > 0) break;
        for (volatile int j = 0; j < 50000; j++) { (void)j; }
    }
    ASSERT_TRUE(decode_pipeline_ready_count() > 0);
    ASSERT_EQ(atomic_load(&g_shutdown_decode_cb_count), 0);

    async_loader_shutdown();

    ASSERT_EQ(atomic_load(&g_shutdown_decode_cb_count), 1);
    ASSERT_EQ(atomic_load(&g_shutdown_decode_cb_valid), 1);
    vfs_destroy(vfs);
    remove(path);
}

TEST_MAIN_BEGIN()
    RUN_TEST(async_loader_init_shutdown);    RUN_TEST(async_loader_pending_zero);
    RUN_TEST(async_loader_load_nonexistent);
    RUN_TEST(async_loader_status_loading);
    RUN_TEST(async_loader_cancel_request);
    /* Edge cases */
    RUN_TEST(async_loader_status_invalid_id);
    RUN_TEST(async_loader_multiple_requests);
    RUN_TEST(async_loader_cancel_invalid_id);
    RUN_TEST(async_loader_rejects_path_truncation);
    RUN_TEST(async_loader_priority_ordering);
    RUN_TEST(async_loader_decode_non_blocking);
    RUN_TEST(async_loader_range_truncated_fails);
    RUN_TEST(async_loader_range_zero_reads_to_end);
    RUN_TEST(async_loader_completion_burst);
    RUN_TEST(async_loader_shutdown_fires_pending_callbacks);
    RUN_TEST(async_loader_shutdown_drains_ready_completion);
    RUN_TEST(async_loader_shutdown_drains_decoded_completion);
TEST_MAIN_END()
