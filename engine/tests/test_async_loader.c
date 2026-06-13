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

static void pri_cb_a(void *user, void *data, u32 size) {
    (void)user; (void)data; (void)size;
    int i = atomic_fetch_add(&g_pri_order_count, 1);
    if (i < 4) g_pri_order[i] = 1;
    if (data) free(data);
}

static void pri_cb_b(void *user, void *data, u32 size) {
    (void)user; (void)data; (void)size;
    int i = atomic_fetch_add(&g_pri_order_count, 1);
    if (i < 4) g_pri_order[i] = 0;
    if (data) free(data);
}

TEST(async_loader_priority_ordering) {
    VFS *vfs = vfs_create();
    ASSERT_NOT_NULL(vfs);
    vfs_mount_dir(vfs, ".");

    FILE *fa = fopen("async_pri_low.bin", "wb");
    FILE *fb = fopen("async_pri_high.bin", "wb");
    ASSERT_NOT_NULL(fa);
    ASSERT_NOT_NULL(fb);
    u8 big[65536];
    memset(big, 0xAB, sizeof(big));
    fwrite(big, 1, sizeof(big), fa);
    u8 small[64];
    memset(small, 0xCD, sizeof(small));
    fwrite(small, 1, sizeof(small), fb);
    fclose(fa);
    fclose(fb);

    async_loader_init(1, vfs);
    atomic_store(&g_pri_order_count, 0);

    u64 id_low = async_loader_request_priority("async_pri_low.bin", pri_cb_a, NULL, 100);
    u64 id_high = async_loader_request_priority("async_pri_high.bin", pri_cb_b, NULL, 0);
    ASSERT_NEQ(id_low, (u64)0);
    ASSERT_NEQ(id_high, (u64)0);

    for (int i = 0; i < 500; i++) {
        async_loader_tick();
        if (atomic_load(&g_pri_order_count) >= 2) break;
        for (volatile int j = 0; j < 50000; j++) { (void)j; }
    }

    ASSERT_EQ(atomic_load(&g_pri_order_count), 2);
    ASSERT_EQ(g_pri_order[0], 0); /* high priority first */

    async_loader_shutdown();
    vfs_destroy(vfs);
    remove("async_pri_low.bin");
    remove("async_pri_high.bin");
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
TEST_MAIN_END()
