#include "test_framework.h"
#include <asset/async_loader.h>
#include <asset/vfs.h>
#include <stdatomic.h>

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
    vfs_mount_dir(vfs, "/tmp");

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
    vfs_mount_dir(vfs, "/tmp");

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
    vfs_mount_dir(vfs, "/tmp");

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
    vfs_mount_dir(vfs, ".");

    /* Two low-priority files queued before a high-priority file. */
    FILE *fa = fopen("async_pri_low_a.bin", "wb");
    FILE *fb = fopen("async_pri_low_b.bin", "wb");
    FILE *fc = fopen("async_pri_high.bin", "wb");
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

    /* Use 2 I/O threads. Even if both lows start first, the heap will prefer
     * the high-priority request as soon as a worker becomes available. */
    async_loader_init(2, vfs);
    atomic_store(&g_pri_order_count, 0);

    u64 id_low_a = async_loader_request_priority("async_pri_low_a.bin", pri_cb_low, NULL, 100);
    u64 id_low_b = async_loader_request_priority("async_pri_low_b.bin", pri_cb_low, NULL, 100);
    u64 id_high  = async_loader_request_priority("async_pri_high.bin",  pri_cb_high, NULL, 0);
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
    remove("async_pri_low_a.bin");
    remove("async_pri_low_b.bin");
    remove("async_pri_high.bin");
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
    vfs_mount_dir(vfs, ".");

    /* Write a minimal 2x2 32-bit uncompressed TGA file. */
    FILE *f = fopen("async_decode_test.tga", "wb");
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

    u64 id = async_loader_request_texture("async_decode_test.tga", decode_cb, NULL, 0);
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
    remove("async_decode_test.tga");
}

TEST_MAIN_BEGIN()
    RUN_TEST(async_loader_init_shutdown);
    RUN_TEST(async_loader_pending_zero);
    RUN_TEST(async_loader_load_nonexistent);
    RUN_TEST(async_loader_status_loading);
    RUN_TEST(async_loader_cancel_request);
    /* Edge cases */
    RUN_TEST(async_loader_status_invalid_id);
    RUN_TEST(async_loader_multiple_requests);
    RUN_TEST(async_loader_cancel_invalid_id);
    RUN_TEST(async_loader_priority_ordering);
    RUN_TEST(async_loader_decode_non_blocking);
TEST_MAIN_END()
