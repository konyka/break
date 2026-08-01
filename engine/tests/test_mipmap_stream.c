/* ==========================================================================
 *  test_mipmap_stream.c — mipmap streaming residency, GPU-upload hook and
 *  eviction, driven against the real async loader + VFS over a temp file.
 * ========================================================================== */

#include "test_framework.h"
#include <asset/mipmap_stream.h>
#include <asset/async_loader.h>
#include <asset/vfs.h>
#include <platform/time.h>
#include <stdio.h>
#include <stdlib.h>

#define TMP_PATH "test_mipmap_tmp.bin"

#define TEX_W   16u
#define TEX_H   16u
#define TEX_BPP 4u
#define TEX_MIPS 5u   /* 16,8,4,2,1 */

static u32 level_w(u32 l) { u32 w = TEX_W >> l; return w ? w : 1u; }
static u32 level_h(u32 l) { u32 h = TEX_H >> l; return h ? h : 1u; }
static u32 level_bytes(u32 l) { return level_w(l) * level_h(l) * TEX_BPP; }

/* Write a file containing the raw mip chain; each level filled with byte=level. */
static bool write_mip_file(void) {
    FILE *f = fopen(TMP_PATH, "wb");
    if (!f) return false;
    for (u32 l = 0; l < TEX_MIPS; l++) {
        u32 n = level_bytes(l);
        u8 *buf = malloc(n);
        if (!buf) { fclose(f); return false; }
        memset(buf, (int)l, n);
        fwrite(buf, 1, n, f);
        free(buf);
    }
    fclose(f);
    return true;
}

/* R395: level 0 for 16×16 RGBA8 is 1024 bytes; write half to exercise the R394
 * async range truncation + mipmap size-mismatch rejection end-to-end. */
static bool write_truncated_level0_mip_file(void) {
    FILE *f = fopen(TMP_PATH, "wb");
    if (!f) return false;
    u8 half[level_bytes(0) / 2u];
    memset(half, 0xAA, sizeof(half));
    if (fwrite(half, 1, sizeof(half), f) != sizeof(half)) {
        fclose(f);
        return false;
    }
    fclose(f);
    return true;
}

/* Upload hook bookkeeping */
static u32 g_upload_calls = 0;
static u32 g_last_upload_level = 0xFFFF;
static u32 g_last_upload_w = 0, g_last_upload_h = 0;
static u8  g_last_upload_first = 0xFF;

static void test_upload(void *ctx, i32 tex, u32 level, u32 w, u32 h,
                        const void *data, u32 size) {
    (void)ctx; (void)tex; (void)size;
    g_upload_calls++;
    g_last_upload_level = level;
    g_last_upload_w = w;
    g_last_upload_h = h;
    if (data && size > 0) g_last_upload_first = ((const u8 *)data)[0];
}

/* Pump the loader + streaming manager until `predicate` holds or we time out. */
static bool pump_until(MipmapStreamManager *mgr, bool (*pred)(MipmapStreamManager *)) {
    for (u32 i = 0; i < 2000; i++) {
        async_loader_tick();
        mipmap_stream_update(mgr);
        if (pred(mgr)) return true;
        time_sleep_us(500);
    }
    return false;
}

static bool level0_resident(MipmapStreamManager *mgr) {
    return mipmap_stream_get_level(mgr, 0, 0) != NULL;
}

/* ----------------------------------------------------------------------- */

TEST(mipmap_residency_and_upload)
{
    ASSERT_TRUE(write_mip_file());

    VFS *vfs = vfs_create();
    vfs_mount_dir(vfs, ".");
    async_loader_init(1, vfs);

    MipmapStreamManager mgr;
    ASSERT_TRUE(mipmap_stream_init(&mgr, 1u << 20)); /* 1 MB budget */
    mipmap_stream_set_upload(&mgr, test_upload, NULL);

    i32 idx = mipmap_stream_register(&mgr, TMP_PATH, TEX_W, TEX_H, TEX_MIPS, TEX_BPP);
    ASSERT_TRUE(idx >= 0);

    g_upload_calls = 0;
    /* Fully visible -> desired level 0 (full res). */
    mipmap_stream_update_visibility(&mgr, idx, 1.0f, 1);
    mipmap_stream_update(&mgr);

    ASSERT_TRUE(pump_until(&mgr, level0_resident));

    /* Level 0 bytes are resident and carry the expected fill value. */
    u8 *data0 = (u8 *)mipmap_stream_get_level(&mgr, idx, 0);
    ASSERT_NOT_NULL(data0);
    ASSERT_EQ(data0[0], (u8)0);
    ASSERT_EQ(mipmap_stream_resident_level(&mgr, idx), 0u);

    /* The GPU upload hook fired for level 0 with the right dimensions. */
    ASSERT_TRUE(g_upload_calls >= 1u);
    ASSERT_EQ(g_last_upload_level, 0u);
    ASSERT_EQ(g_last_upload_w, TEX_W);
    ASSERT_EQ(g_last_upload_h, TEX_H);
    ASSERT_EQ(g_last_upload_first, (u8)0);
    ASSERT_TRUE(mipmap_stream_uploads(&mgr) >= 1u);

    mipmap_stream_shutdown(&mgr);
    async_loader_shutdown();
    vfs_destroy(vfs);
    remove(TMP_PATH);
}

static bool level0_evicted(MipmapStreamManager *mgr) {
    return mipmap_stream_get_level(mgr, 0, 0) == NULL;
}
static bool level_high_resident(MipmapStreamManager *mgr) {
    return mipmap_stream_get_level(mgr, 0, TEX_MIPS - 1) != NULL;
}

TEST(mipmap_eviction_under_budget)
{
    ASSERT_TRUE(write_mip_file());

    VFS *vfs = vfs_create();
    vfs_mount_dir(vfs, ".");
    async_loader_init(1, vfs);

    MipmapStreamManager mgr;
    ASSERT_TRUE(mipmap_stream_init(&mgr, 1u << 20));

    i32 idx = mipmap_stream_register(&mgr, TMP_PATH, TEX_W, TEX_H, TEX_MIPS, TEX_BPP);
    ASSERT_TRUE(idx >= 0);

    /* Load full-res level 0 first. */
    mipmap_stream_update_visibility(&mgr, idx, 1.0f, 1);
    mipmap_stream_update(&mgr);
    ASSERT_TRUE(pump_until(&mgr, level0_resident));
    ASSERT_TRUE(mipmap_stream_resident_bytes(&mgr) >= level_bytes(0));

    /* Shrink the budget below level-0 size and mark the texture as distant so
     * the desired level becomes the coarsest mip. The finer resident level
     * must then be evicted. */
    mgr.memory_budget = 100; /* < level_bytes(0) = 1024 */
    mipmap_stream_update_visibility(&mgr, idx, 0.0001f, 2);
    mipmap_stream_update(&mgr);

    ASSERT_TRUE(level0_evicted(&mgr));
    ASSERT_TRUE(mipmap_stream_evictions(&mgr) >= 1u);

    /* After freeing room, the coarse level can stream in. */
    ASSERT_TRUE(pump_until(&mgr, level_high_resident));
    u8 *hi = (u8 *)mipmap_stream_get_level(&mgr, idx, TEX_MIPS - 1);
    ASSERT_NOT_NULL(hi);
    ASSERT_EQ(hi[0], (u8)(TEX_MIPS - 1));

    mipmap_stream_shutdown(&mgr);
    async_loader_shutdown();
    vfs_destroy(vfs);
    remove(TMP_PATH);
}

TEST(mipmap_invalidate_clears_residency)
{
    ASSERT_TRUE(write_mip_file());

    VFS *vfs = vfs_create();
    vfs_mount_dir(vfs, ".");
    async_loader_init(1, vfs);

    MipmapStreamManager mgr;
    ASSERT_TRUE(mipmap_stream_init(&mgr, 1u << 20));
    mipmap_stream_set_upload(&mgr, test_upload, NULL);

    i32 idx = mipmap_stream_register(&mgr, TMP_PATH, TEX_W, TEX_H, TEX_MIPS, TEX_BPP);
    ASSERT_TRUE(idx >= 0);

    mipmap_stream_update_visibility(&mgr, idx, 1.0f, 1);
    mipmap_stream_update(&mgr);
    ASSERT_TRUE(pump_until(&mgr, level0_resident));
    ASSERT_TRUE(mipmap_stream_resident_bytes(&mgr) > 0);

    mipmap_stream_invalidate(&mgr, idx);
    ASSERT_EQ(mipmap_stream_resident_bytes(&mgr), (usize)0);
    ASSERT_TRUE(mipmap_stream_get_level(&mgr, idx, 0) == NULL);

    mipmap_stream_shutdown(&mgr);
    async_loader_shutdown();
    vfs_destroy(vfs);
    remove(TMP_PATH);
}

/* R395: truncated mip file must not become resident or reach the GPU upload hook. */
TEST(mipmap_rejects_truncated_level_file)
{
    ASSERT_TRUE(write_truncated_level0_mip_file());

    VFS *vfs = vfs_create();
    vfs_mount_dir(vfs, ".");
    async_loader_init(1, vfs);

    MipmapStreamManager mgr;
    ASSERT_TRUE(mipmap_stream_init(&mgr, 1u << 20));
    mipmap_stream_set_upload(&mgr, test_upload, NULL);

    i32 idx = mipmap_stream_register(&mgr, TMP_PATH, TEX_W, TEX_H, TEX_MIPS, TEX_BPP);
    ASSERT_TRUE(idx >= 0);

    g_upload_calls = 0;
    mipmap_stream_update_visibility(&mgr, idx, 1.0f, 1);
    mipmap_stream_update(&mgr);

    /* Truncated range loads fail async; streaming may retry — must never upload. */
    bool attempted = false;
    for (u32 i = 0; i < 2000; i++) {
        async_loader_tick();
        mipmap_stream_update(&mgr);
        if (mipmap_stream_load_requests(&mgr) > 0) attempted = true;
        if (attempted && g_upload_calls > 0) break;
        time_sleep_us(500);
    }
    ASSERT_TRUE(attempted);
    ASSERT_EQ(g_upload_calls, 0u);
    ASSERT_TRUE(mipmap_stream_get_level(&mgr, idx, 0) == NULL);

    mipmap_stream_invalidate(&mgr, idx);
    async_loader_tick();
    ASSERT_EQ(mipmap_stream_resident_bytes(&mgr), (usize)0);

    mipmap_stream_shutdown(&mgr);
    async_loader_shutdown();
    vfs_destroy(vfs);
    remove(TMP_PATH);
}

/* R405: mip chains larger than VFS_MAX_FILE_BYTES must fail at register. */
TEST(mipmap_register_rejects_chain_over_vfs_cap)
{
    MipmapStreamManager mgr;
    ASSERT_TRUE(mipmap_stream_init(&mgr, 1u << 20));
    /* Level 0 alone is 8192²×4 = 256 MiB > VFS_MAX_FILE_BYTES (128 MiB). */
    i32 idx = mipmap_stream_register(&mgr, TMP_PATH, 8192u, 8192u, 4u, 4u);
    ASSERT_EQ(idx, -1);
    mipmap_stream_shutdown(&mgr);
}

/* R408: golden values from Round11 R325 audit (IEEE754 exponent fast path). */
TEST(coverage_to_level_known_values)
{
    const u32 mips = 5u;
    ASSERT_EQ(mipmap_stream_coverage_to_level(1.0f, mips, 16u, 16u), 0u);
    ASSERT_EQ(mipmap_stream_coverage_to_level(0.25f, mips, 16u, 16u), 1u);
    ASSERT_EQ(mipmap_stream_coverage_to_level(0.0625f, mips, 16u, 16u), 2u);
    ASSERT_EQ(mipmap_stream_coverage_to_level(0.0f, mips, 16u, 16u), mips - 1u);
}

/* R415: the request pool was a one-shot bump allocator — after
 * MIPMAP_STREAM_REQ_POOL_SIZE (64) requests every allocation fell back to
 * malloc forever. With the free list, repeated force_level + invalidate
 * cycles keep reusing pool slots and the pool never exhausts. */
TEST(mipmap_request_pool_reuse_after_free)
{
    ASSERT_TRUE(write_mip_file());

    VFS *vfs = vfs_create();
    vfs_mount_dir(vfs, ".");
    async_loader_init(1, vfs);

    MipmapStreamManager mgr;
    ASSERT_TRUE(mipmap_stream_init(&mgr, 1u << 20));

    i32 idx = mipmap_stream_register(&mgr, TMP_PATH, TEX_W, TEX_H, TEX_MIPS, TEX_BPP);
    ASSERT_TRUE(idx >= 0);

    /* Far more requests than the 64-slot pool: with the old bump allocator
     * req_pool_next would have pinned at the pool size and every request past
     * the 64th silently fell back to malloc. */
    u32 cycles = MIPMAP_STREAM_REQ_POOL_SIZE * 3u;
    for (u32 i = 0; i < cycles; i++) {
        ASSERT_TRUE(mipmap_stream_force_level(&mgr, idx, 0));
        mipmap_stream_invalidate(&mgr, idx);
    }
    ASSERT_EQ(mipmap_stream_load_requests(&mgr), cycles);
    /* A free slot was available for every single request (head never empty). */
    ASSERT_NEQ(mgr.req_pool_next, 0xFFFFFFFFu);
    ASSERT_TRUE(mgr.req_pool_next < MIPMAP_STREAM_REQ_POOL_SIZE);

    mipmap_stream_shutdown(&mgr);
    async_loader_shutdown();
    vfs_destroy(vfs);
    remove(TMP_PATH);
}

/* R426: a permanently failing load used to finish as MIPMAP_LEVEL_UNLOADED,
 * so the next mipmap_stream_update re-issued the async request — one failing
 * request per frame forever. The per-level failure latch stops the retry loop
 * until mipmap_stream_invalidate re-arms it. */
TEST(mipmap_failed_load_not_rerequested)
{
    VFS *vfs = vfs_create();
    vfs_mount_dir(vfs, ".");
    async_loader_init(1, vfs);

    MipmapStreamManager mgr;
    ASSERT_TRUE(mipmap_stream_init(&mgr, 1u << 20));

    /* Nonexistent path: every load fails asynchronously. */
    i32 idx = mipmap_stream_register(&mgr, "test_mipmap_missing.bin",
                                     TEX_W, TEX_H, TEX_MIPS, TEX_BPP);
    ASSERT_TRUE(idx >= 0);

    mipmap_stream_update_visibility(&mgr, idx, 1.0f, 1);
    mipmap_stream_update(&mgr);
    ASSERT_EQ(mipmap_stream_load_requests(&mgr), 1u);

    /* Pump until the async failure lands in the callback. */
    bool failed = false;
    for (u32 i = 0; i < 2000; i++) {
        async_loader_tick();
        if (mgr.textures[idx].level_failed[0]) { failed = true; break; }
        time_sleep_us(500);
    }
    ASSERT_TRUE(failed);

    /* Further updates must not re-issue the request. */
    for (u32 i = 0; i < 8; i++) {
        async_loader_tick();
        mipmap_stream_update(&mgr);
    }
    ASSERT_EQ(mipmap_stream_load_requests(&mgr), 1u);
    ASSERT_TRUE(mipmap_stream_get_level(&mgr, idx, 0) == NULL);

    /* invalidate clears the latch: the next update retries exactly once. */
    mipmap_stream_invalidate(&mgr, idx);
    ASSERT_TRUE(!mgr.textures[idx].level_failed[0]);
    mipmap_stream_update(&mgr);
    ASSERT_EQ(mipmap_stream_load_requests(&mgr), 2u);

    mipmap_stream_shutdown(&mgr);
    async_loader_shutdown();
    vfs_destroy(vfs);
}

TEST_MAIN_BEGIN()
    RUN_TEST(mipmap_residency_and_upload);
    RUN_TEST(mipmap_eviction_under_budget);
    RUN_TEST(mipmap_invalidate_clears_residency);
    RUN_TEST(mipmap_rejects_truncated_level_file);
    RUN_TEST(mipmap_register_rejects_chain_over_vfs_cap);
    RUN_TEST(coverage_to_level_known_values);
    RUN_TEST(mipmap_request_pool_reuse_after_free);
    RUN_TEST(mipmap_failed_load_not_rerequested);
TEST_MAIN_END()
