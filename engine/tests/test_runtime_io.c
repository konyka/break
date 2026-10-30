#include "test_framework.h"
#include <runtime/runtime_thread.h>
#include <runtime/runtime_io.h>
#include <runtime/runtime_test_hooks.h>
#include <core/platform_thread.h>
#include <asset/vfs.h>
#include <stdatomic.h>
#include <string.h>
#include <stdio.h>

#if !defined(_WIN32)
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#endif

/* Focused contract tests for the Runtime Core formal thread facade and the
 * formal IO/VFS facade (Task 5). Links the test-only runtime_core_test
 * variant (BREAK_RUNTIME_TESTING=1) for allocation failure injection, the
 * request double-release registry, and the deterministic IO worker gates;
 * vfs.c is compiled beside the test (the facade reads through a borrowed
 * VFS, mirroring how consumers link the VFS themselves). The compatibility
 * async loader is not exercised here and stays unchanged. */

/* ------------------------------------------------------------------ */
/* helpers                                                             */
/* ------------------------------------------------------------------ */

static void test_sleep_ms(long ms)
{
#if defined(_WIN32)
    Sleep((unsigned long)ms);
#else
    struct timespec ts;
    ts.tv_sec = ms / 1000;
    ts.tv_nsec = (ms % 1000) * 1000000L;
    nanosleep(&ts, NULL);
#endif
}

#define IO_TEST_FILE_BYTES 4096u

static u8 g_expected_bytes[IO_TEST_FILE_BYTES];

static char g_io_dir[512];

/* Creates a per-process temp dir with one known-content file and a VFS with
 * that dir mounted. The fixture is shared across IO tests (each test runs
 * its own init/shutdown lifecycle on the same borrowed VFS). */
static VFS *fixture_setup(void)
{
    VFS *vfs;
    FILE *fp;
    usize i;
    char file_path[640];

    for (i = 0; i < (usize)IO_TEST_FILE_BYTES; i++) {
        g_expected_bytes[i] = (u8)((i * 31u + 7u) & 0xFFu);
    }
    test_tmp(g_io_dir, sizeof(g_io_dir), "rtio");
    TEST_MKDIR(g_io_dir);
    snprintf(file_path, sizeof(file_path), "%s/payload.bin", g_io_dir);
    fp = fopen(file_path, "wb");
    if (!fp) {
        return NULL;
    }
    if (fwrite(g_expected_bytes, 1, IO_TEST_FILE_BYTES, fp) !=
        IO_TEST_FILE_BYTES) {
        fclose(fp);
        return NULL;
    }
    fclose(fp);

    vfs = vfs_create();
    if (!vfs) {
        return NULL;
    }
    if (!vfs_mount_dir(vfs, g_io_dir)) {
        vfs_destroy(vfs);
        return NULL;
    }
    return vfs;
}

static BreakRuntimeError parse_completion(
    const BreakRuntimeOwnedMessage *msg,
    BreakRuntimeIoCompletion *out)
{
    return break_runtime_io_completion_view(msg, out);
}

/* ------------------------------------------------------------------ */
/* thread facade                                                       */
/* ------------------------------------------------------------------ */

typedef struct ThreadProbeCtx {
    BreakRuntimeThread *thread;
    _Atomic u32 ran;
    _Atomic u32 observed_stop_request;
    _Atomic u32 test_release; /* uncooperative-worker release flag */
} ThreadProbeCtx;

static void cooperative_worker(void *arg)
{
    ThreadProbeCtx *ctx = (ThreadProbeCtx *)arg;
    u32 guard = 0u;
    atomic_store_explicit(&ctx->ran, 1u, memory_order_release);
    /* Completion condition: poll the formal stop request. */
    while (guard++ < 200000u) {
        if (break_runtime_thread_stop_requested(ctx->thread)) {
            atomic_store_explicit(&ctx->observed_stop_request, 1u,
                                  memory_order_release);
            return;
        }
        platform_thread_yield();
    }
}

static void uncooperative_worker(void *arg)
{
    ThreadProbeCtx *ctx = (ThreadProbeCtx *)arg;
    u32 guard = 0u;
    atomic_store_explicit(&ctx->ran, 1u, memory_order_release);
    /* Deliberately ignores the stop request; only the test flag frees it. */
    while (guard++ < 5000u &&
           atomic_load_explicit(&ctx->test_release, memory_order_acquire) == 0u) {
        test_sleep_ms(1);
    }
}

static void quick_exit_worker(void *arg)
{
    ThreadProbeCtx *ctx = (ThreadProbeCtx *)arg;
    atomic_store_explicit(&ctx->ran, 1u, memory_order_release);
}

static void spin_until(_Atomic u32 *flag, u32 value)
{
    u32 guard = 0u;
    while (atomic_load_explicit(flag, memory_order_acquire) != value &&
           guard++ < 2000000u) {
        platform_thread_yield();
    }
}

static void spin_until_u64(_Atomic u64 *flag, u64 value)
{
    u32 guard = 0u;
    while (atomic_load_explicit(flag, memory_order_acquire) != value &&
           guard++ < 2000000u) {
        platform_thread_yield();
    }
}

TEST(thread_create_validation_and_oom)
{
    BreakRuntimeThread *thread = NULL;
    BreakRuntimeThreadConfig cfg;

    memset(&cfg, 0, sizeof(cfg));
    cfg.name = "validation";
    cfg.fn = quick_exit_worker;
    cfg.arg = NULL;

    ASSERT_EQ(break_runtime_thread_create(NULL, &thread),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(thread, NULL);
    ASSERT_EQ(break_runtime_thread_create(&cfg, NULL),
              BREAK_RUNTIME_INVALID);
    cfg.fn = NULL;
    ASSERT_EQ(break_runtime_thread_create(&cfg, &thread),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(thread, NULL);

    /* stop() from CREATED has no such transition. */
    cfg.fn = quick_exit_worker;
    ASSERT_EQ(break_runtime_thread_create(&cfg, &thread), BREAK_RUNTIME_OK);
    ASSERT_NOT_NULL(thread);
    ASSERT_EQ(break_runtime_thread_state(thread),
              BREAK_RUNTIME_THREAD_CREATED);
    ASSERT_EQ(break_runtime_thread_stop(thread, 0u), BREAK_RUNTIME_INVALID);
    break_runtime_thread_destroy(thread);
    break_runtime_thread_destroy(NULL); /* NULL destroy is a no-op */
    thread = NULL;

    /* Allocation failure injection at create. */
    break_runtime_test_set_alloc_budget(0u);
    ASSERT_EQ(break_runtime_thread_create(&cfg, &thread), BREAK_RUNTIME_OOM);
    ASSERT_EQ(thread, NULL);
    break_runtime_test_set_alloc_budget(BREAK_RUNTIME_TEST_ALLOC_DISABLED);

    ASSERT_EQ(break_runtime_thread_create(&cfg, &thread), BREAK_RUNTIME_OK);
    ASSERT_NOT_NULL(thread);
    break_runtime_thread_destroy(thread);
}

TEST(thread_start_runs_and_owner_stops)
{
    BreakRuntimeThread *thread = NULL;
    BreakRuntimeThreadConfig cfg;
    ThreadProbeCtx ctx;

    memset(&ctx, 0, sizeof(ctx));
    memset(&cfg, 0, sizeof(cfg));
    cfg.name = "cooperative";
    cfg.fn = cooperative_worker;
    cfg.arg = &ctx;

    ASSERT_EQ(break_runtime_thread_create(&cfg, &thread), BREAK_RUNTIME_OK);
    ctx.thread = thread;

    ASSERT_EQ(break_runtime_thread_start(thread), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_thread_state(thread),
              BREAK_RUNTIME_THREAD_RUNNING);
    /* Double start is rejected. */
    ASSERT_EQ(break_runtime_thread_start(thread), BREAK_RUNTIME_REJECTED);

    spin_until(&ctx.ran, 1u);
    ASSERT_EQ(atomic_load_explicit(&ctx.ran, memory_order_acquire), 1u);

    /* Owner stop: publishes the completion condition, bounded wait, joins. */
    ASSERT_EQ(break_runtime_thread_stop(thread, 5000u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_thread_state(thread),
              BREAK_RUNTIME_THREAD_STOPPED);
    /* The worker observed the formal stop request before exiting. */
    ASSERT_EQ(atomic_load_explicit(&ctx.observed_stop_request,
                                   memory_order_acquire), 1u);
    ASSERT_TRUE(break_runtime_thread_stop_requested(thread));

    /* stop() on STOPPED is an idempotent no-op. */
    ASSERT_EQ(break_runtime_thread_stop(thread, 0u), BREAK_RUNTIME_OK);

    break_runtime_thread_destroy(thread);
}

TEST(thread_self_exit_owner_completion)
{
    /* The worker exits on its own; the owner still owns the completion:
     * stop() observes the exit and joins exactly once. */
    BreakRuntimeThread *thread = NULL;
    BreakRuntimeThreadConfig cfg;
    ThreadProbeCtx ctx;

    memset(&ctx, 0, sizeof(ctx));
    memset(&cfg, 0, sizeof(cfg));
    cfg.name = "selfexit";
    cfg.fn = quick_exit_worker;
    cfg.arg = &ctx;

    ASSERT_EQ(break_runtime_thread_create(&cfg, &thread), BREAK_RUNTIME_OK);
    ctx.thread = thread;
    ASSERT_EQ(break_runtime_thread_start(thread), BREAK_RUNTIME_OK);
    spin_until(&ctx.ran, 1u);
    test_sleep_ms(30); /* give the worker the window to fully return */

    ASSERT_EQ(break_runtime_thread_stop(thread, 2000u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_thread_state(thread),
              BREAK_RUNTIME_THREAD_STOPPED);
    break_runtime_thread_destroy(thread);
}

TEST(thread_stop_timeout_retains_live_ownership)
{
    BreakRuntimeThread *thread = NULL;
    BreakRuntimeThreadConfig cfg;
    ThreadProbeCtx ctx;

    memset(&ctx, 0, sizeof(ctx));
    memset(&cfg, 0, sizeof(cfg));
    cfg.name = "uncooperative";
    cfg.fn = uncooperative_worker;
    cfg.arg = &ctx;

    ASSERT_EQ(break_runtime_thread_create(&cfg, &thread), BREAK_RUNTIME_OK);
    ctx.thread = thread;
    ASSERT_EQ(break_runtime_thread_start(thread), BREAK_RUNTIME_OK);
    spin_until(&ctx.ran, 1u);
    ASSERT_EQ(atomic_load_explicit(&ctx.ran, memory_order_acquire), 1u);

    /* Bounded wait expires: TIMEOUT, live ownership retained, nothing
     * freed, no force-kill. */
    ASSERT_EQ(break_runtime_thread_stop(thread, 30u), BREAK_RUNTIME_TIMEOUT);
    ASSERT_EQ(break_runtime_thread_state(thread),
              BREAK_RUNTIME_THREAD_STOP_REQUESTED);
    ASSERT_TRUE(break_runtime_thread_stop_requested(thread));

    /* Still uncooperative: a retry times out again (and does not corrupt). */
    ASSERT_EQ(break_runtime_thread_stop(thread, 30u), BREAK_RUNTIME_TIMEOUT);
    ASSERT_EQ(break_runtime_thread_state(thread),
              BREAK_RUNTIME_THREAD_STOP_REQUESTED);

    /* Once the worker exits, the same object completes the stop. */
    atomic_store_explicit(&ctx.test_release, 1u, memory_order_release);
    ASSERT_EQ(break_runtime_thread_stop(thread, 5000u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_thread_state(thread),
              BREAK_RUNTIME_THREAD_STOPPED);
    break_runtime_thread_destroy(thread);
}

/* ------------------------------------------------------------------ */
/* IO facade                                                           */
/* ------------------------------------------------------------------ */

TEST(io_submit_validation)
{
    VFS *vfs = fixture_setup();
    BreakRuntimeIoConfig cfg;
    BreakRuntimeIoRequest *req = NULL;
    BreakRuntimeIoStats stats;
    char long_path[BREAK_RUNTIME_IO_MAX_PATH + 16u];

    ASSERT_NOT_NULL(vfs);

    /* Submit before init: admission not open. */
    ASSERT_EQ(break_runtime_io_submit(&req, "payload.bin", 0u, 0u),
              BREAK_RUNTIME_REJECTED);
    ASSERT_EQ(req, NULL);
    ASSERT_EQ(break_runtime_io_stats(&stats), BREAK_RUNTIME_INVALID);

    memset(&cfg, 0, sizeof(cfg));
    cfg.vfs = vfs;
    cfg.worker_count = 1u;
    cfg.request_capacity = 4u;

    /* Malformed configs fail closed before any lifecycle exists. */
    {
        BreakRuntimeIoConfig bad = cfg;
        bad.vfs = NULL;
        ASSERT_EQ(break_runtime_io_init(&bad), BREAK_RUNTIME_INVALID);
        bad = cfg;
        bad.worker_count = BREAK_RUNTIME_IO_MAX_WORKERS + 1u;
        ASSERT_EQ(break_runtime_io_init(&bad), BREAK_RUNTIME_INVALID);
        bad = cfg;
        bad.request_capacity = BREAK_RUNTIME_IO_MAX_REQUEST_CAPACITY + 1u;
        ASSERT_EQ(break_runtime_io_init(&bad), BREAK_RUNTIME_INVALID);
    }

    ASSERT_EQ(break_runtime_io_init(&cfg), BREAK_RUNTIME_OK);
    /* init while RUNNING is rejected. */
    ASSERT_EQ(break_runtime_io_init(&cfg), BREAK_RUNTIME_REJECTED);

    /* Malformed submissions. */
    ASSERT_EQ(break_runtime_io_submit(NULL, "payload.bin", 0u, 0u),
              BREAK_RUNTIME_INVALID);
    req = NULL;
    ASSERT_EQ(break_runtime_io_submit(&req, NULL, 0u, 0u),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(req, NULL);
    ASSERT_EQ(break_runtime_io_submit(&req, "", 0u, 0u),
              BREAK_RUNTIME_INVALID);
    memset(long_path, 'a', sizeof(long_path) - 1u);
    long_path[sizeof(long_path) - 1u] = '\0';
    ASSERT_EQ(break_runtime_io_submit(&req, long_path, 0u, 0u),
              BREAK_RUNTIME_INVALID);
    /* No flags are defined yet: fail-closed. */
    ASSERT_EQ(break_runtime_io_submit(&req, "payload.bin", 1u, 0u),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(req, NULL);
    ASSERT_EQ(break_runtime_io_cancel(NULL), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_io_poll_completion(NULL, NULL),
              BREAK_RUNTIME_INVALID);
    break_runtime_io_request_release(NULL); /* NULL release is a no-op */

    ASSERT_EQ(break_runtime_io_stats(&stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.submitted, 0u);
    ASSERT_EQ(stats.active, 0u);

    ASSERT_EQ(break_runtime_io_shutdown(1000u), BREAK_RUNTIME_OK);
    /* Submit after shutdown: admission closed. */
    req = NULL;
    ASSERT_EQ(break_runtime_io_submit(&req, "payload.bin", 0u, 0u),
              BREAK_RUNTIME_CLOSED);
    ASSERT_EQ(req, NULL);
    /* Shutdown is idempotent once STOPPED. */
    ASSERT_EQ(break_runtime_io_shutdown(1000u), BREAK_RUNTIME_OK);
    /* Stats stay queryable after shutdown. */
    ASSERT_EQ(break_runtime_io_stats(&stats), BREAK_RUNTIME_OK);

    vfs_destroy(vfs);
}

TEST(io_read_completion_owned_bytes)
{
    VFS *vfs = fixture_setup();
    BreakRuntimeIoConfig cfg;
    BreakRuntimeIoRequest *req = NULL;
    BreakRuntimeOwnedMessage *msg = NULL;
    BreakRuntimeIoCompletion completion;
    BreakRuntimeIoStats stats;
    BreakRuntimeMessageView view;

    ASSERT_NOT_NULL(vfs);
    memset(&cfg, 0, sizeof(cfg));
    cfg.vfs = vfs;
    cfg.worker_count = 1u;
    cfg.request_capacity = 4u;
    ASSERT_EQ(break_runtime_io_init(&cfg), BREAK_RUNTIME_OK);

    ASSERT_EQ(break_runtime_io_submit(&req, "payload.bin", 0u, 0u),
              BREAK_RUNTIME_OK);
    ASSERT_NOT_NULL(req);

    ASSERT_EQ(break_runtime_io_wait_completion(req, 5000u, &msg),
              BREAK_RUNTIME_OK);
    ASSERT_NOT_NULL(msg);
    ASSERT_EQ(parse_completion(msg, &completion), BREAK_RUNTIME_OK);
    ASSERT_EQ(completion.state, BREAK_RUNTIME_IO_COMPLETED);
    ASSERT_EQ(completion.error, BREAK_RUNTIME_OK);
    ASSERT_EQ(completion.byte_size, (u64)IO_TEST_FILE_BYTES);
    ASSERT_NOT_NULL(completion.bytes);
    ASSERT_EQ(memcmp(completion.bytes, g_expected_bytes,
                     IO_TEST_FILE_BYTES), 0);
    ASSERT_NEQ(completion.request_id, 0u);

    /* Exactly once: the consumed completion is not delivered again. */
    {
        BreakRuntimeOwnedMessage *again = NULL;
        ASSERT_EQ(break_runtime_io_poll_completion(req, &again),
                  BREAK_RUNTIME_OK);
        ASSERT_EQ(again, NULL);
    }

    /* Ownership transferred to the caller: releasing the REQUEST first must
     * not disturb the completion message. */
    break_runtime_io_request_release(req);
    ASSERT_EQ(break_runtime_message_view(msg, &view), BREAK_RUNTIME_OK);
    ASSERT_EQ(view.kind, BREAK_RUNTIME_IO_COMPLETION_KIND);
    break_runtime_message_release(msg);

    ASSERT_EQ(break_runtime_io_stats(&stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.submitted, 1u);
    ASSERT_EQ(stats.completed, 1u);
    ASSERT_EQ(stats.bytes_published, (u64)IO_TEST_FILE_BYTES);
    ASSERT_EQ(stats.active, 0u);

    ASSERT_EQ(break_runtime_io_shutdown(2000u), BREAK_RUNTIME_OK);
    vfs_destroy(vfs);
}

TEST(io_missing_file_failed_completion)
{
    VFS *vfs = fixture_setup();
    BreakRuntimeIoConfig cfg;
    BreakRuntimeIoRequest *req = NULL;
    BreakRuntimeOwnedMessage *msg = NULL;
    BreakRuntimeIoCompletion completion;
    BreakRuntimeIoStats stats;

    ASSERT_NOT_NULL(vfs);
    memset(&cfg, 0, sizeof(cfg));
    cfg.vfs = vfs;
    cfg.worker_count = 1u;
    cfg.request_capacity = 4u;
    ASSERT_EQ(break_runtime_io_init(&cfg), BREAK_RUNTIME_OK);

    ASSERT_EQ(break_runtime_io_submit(&req, "no_such_file.bin", 0u, 0u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_io_wait_completion(req, 5000u, &msg),
              BREAK_RUNTIME_OK);
    ASSERT_NOT_NULL(msg);
    ASSERT_EQ(parse_completion(msg, &completion), BREAK_RUNTIME_OK);
    ASSERT_EQ(completion.state, BREAK_RUNTIME_IO_FAILED);
    ASSERT_EQ(completion.error, BREAK_RUNTIME_FAILED);
    ASSERT_EQ(completion.byte_size, 0u);
    ASSERT_EQ(completion.bytes, NULL);
    break_runtime_message_release(msg);
    break_runtime_io_request_release(req);

    ASSERT_EQ(break_runtime_io_stats(&stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.failed, 1u);
    ASSERT_EQ(stats.completed, 0u);

    ASSERT_EQ(break_runtime_io_shutdown(2000u), BREAK_RUNTIME_OK);
    vfs_destroy(vfs);
}

TEST(io_deadline_timeout_completion)
{
    VFS *vfs = fixture_setup();
    BreakRuntimeIoConfig cfg;
    BreakRuntimeIoRequest *req = NULL;
    BreakRuntimeOwnedMessage *msg = NULL;
    BreakRuntimeIoCompletion completion;
    BreakRuntimeIoStats stats;

    ASSERT_NOT_NULL(vfs);
    memset(&cfg, 0, sizeof(cfg));
    cfg.vfs = vfs;
    cfg.worker_count = 1u;
    cfg.request_capacity = 4u;
    ASSERT_EQ(break_runtime_io_init(&cfg), BREAK_RUNTIME_OK);

    /* deadline_ns is an absolute TIME_UTC nanosecond deadline; 1 is long
     * past, so the request finalizes TIMED_OUT without touching the VFS. */
    ASSERT_EQ(break_runtime_io_submit(&req, "payload.bin", 0u, 1u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_io_wait_completion(req, 5000u, &msg),
              BREAK_RUNTIME_OK);
    ASSERT_NOT_NULL(msg);
    ASSERT_EQ(parse_completion(msg, &completion), BREAK_RUNTIME_OK);
    ASSERT_EQ(completion.state, BREAK_RUNTIME_IO_TIMED_OUT);
    ASSERT_EQ(completion.error, BREAK_RUNTIME_TIMEOUT);
    ASSERT_EQ(completion.byte_size, 0u);
    break_runtime_message_release(msg);
    break_runtime_io_request_release(req);

    ASSERT_EQ(break_runtime_io_stats(&stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.timed_out, 1u);
    ASSERT_EQ(stats.completed, 0u);
    ASSERT_EQ(stats.bytes_published, 0u);

    ASSERT_EQ(break_runtime_io_shutdown(2000u), BREAK_RUNTIME_OK);
    vfs_destroy(vfs);
}

TEST(io_cancel_before_start)
{
    VFS *vfs = fixture_setup();
    BreakRuntimeIoConfig cfg;
    BreakRuntimeIoRequest *req = NULL;
    BreakRuntimeOwnedMessage *msg = NULL;
    BreakRuntimeIoCompletion completion;
    BreakRuntimeIoStats stats;

    ASSERT_NOT_NULL(vfs);
    /* Gate the workers BEFORE they can claim from the pending ring: the
     * request stays QUEUED and the read never starts. */
    break_runtime_test_io_set_gates(1u, 0u);

    memset(&cfg, 0, sizeof(cfg));
    cfg.vfs = vfs;
    cfg.worker_count = 1u;
    cfg.request_capacity = 4u;
    ASSERT_EQ(break_runtime_io_init(&cfg), BREAK_RUNTIME_OK);

    {
        u64 baseline = atomic_load_explicit(&g_break_runtime_test_io_popped,
                                            memory_order_acquire);
        ASSERT_EQ(break_runtime_io_submit(&req, "payload.bin", 0u, 0u),
                  BREAK_RUNTIME_OK);
        test_sleep_ms(30);
        /* The worker is provably parked before the claim. */
        ASSERT_EQ(atomic_load_explicit(&g_break_runtime_test_io_popped,
                                       memory_order_acquire), baseline);

        ASSERT_EQ(break_runtime_io_cancel(req), BREAK_RUNTIME_OK);
        /* cancel() published the CANCELLED completion itself. */
        ASSERT_EQ(break_runtime_io_poll_completion(req, &msg),
                  BREAK_RUNTIME_OK);
        ASSERT_NOT_NULL(msg);
        ASSERT_EQ(parse_completion(msg, &completion), BREAK_RUNTIME_OK);
        ASSERT_EQ(completion.state, BREAK_RUNTIME_IO_CANCELLED);
        ASSERT_EQ(completion.byte_size, 0u);
        break_runtime_message_release(msg);

        /* Idempotent cancel on an already-cancelled request. */
        ASSERT_EQ(break_runtime_io_cancel(req), BREAK_RUNTIME_OK);

        break_runtime_test_io_set_gates(0u, 0u);
        ASSERT_EQ(break_runtime_io_shutdown(2000u), BREAK_RUNTIME_OK);

        ASSERT_EQ(break_runtime_io_stats(&stats), BREAK_RUNTIME_OK);
        ASSERT_EQ(stats.cancelled, 1u);
        ASSERT_EQ(stats.stale_drops, 0u);
        ASSERT_EQ(stats.bytes_published, 0u);
        /* The read never started: still no claim beyond the baseline. */
        ASSERT_EQ(atomic_load_explicit(&g_break_runtime_test_io_popped,
                                       memory_order_acquire), baseline);
    }

    break_runtime_io_request_release(req);
    vfs_destroy(vfs);
}

TEST(io_stale_generation_dropped)
{
    VFS *vfs = fixture_setup();
    BreakRuntimeIoConfig cfg;
    BreakRuntimeIoRequest *req = NULL;
    BreakRuntimeOwnedMessage *msg = NULL;
    BreakRuntimeIoCompletion completion;
    BreakRuntimeIoStats stats;

    ASSERT_NOT_NULL(vfs);
    memset(&cfg, 0, sizeof(cfg));
    cfg.vfs = vfs;
    cfg.worker_count = 1u;
    cfg.request_capacity = 4u;
    ASSERT_EQ(break_runtime_io_init(&cfg), BREAK_RUNTIME_OK);

    /* Gate the worker AFTER the claim (state READING) and BEFORE the read. */
    break_runtime_test_io_set_gates(0u, 1u);
    {
        u64 baseline = atomic_load_explicit(&g_break_runtime_test_io_popped,
                                            memory_order_acquire);
        ASSERT_EQ(break_runtime_io_submit(&req, "payload.bin", 0u, 0u),
                  BREAK_RUNTIME_OK);
        spin_until_u64(&g_break_runtime_test_io_popped, baseline + 1u);
        ASSERT_EQ(atomic_load_explicit(&g_break_runtime_test_io_popped,
                                       memory_order_acquire), baseline + 1u);
    }

    /* Cancel lands while the worker is parked: generation bumps, the
     * CANCELLED completion is published by cancel itself. */
    ASSERT_EQ(break_runtime_io_cancel(req), BREAK_RUNTIME_OK);

    /* The worker now performs the read, but its late result is STALE: it
     * must release its own bytes and never publish a second completion. */
    break_runtime_test_io_set_gates(0u, 0u);

    ASSERT_EQ(break_runtime_io_wait_completion(req, 5000u, &msg),
              BREAK_RUNTIME_OK);
    ASSERT_NOT_NULL(msg);
    ASSERT_EQ(parse_completion(msg, &completion), BREAK_RUNTIME_OK);
    ASSERT_EQ(completion.state, BREAK_RUNTIME_IO_CANCELLED);
    break_runtime_message_release(msg);

    /* shutdown joins the worker, so the stale drop has certainly run. */
    ASSERT_EQ(break_runtime_io_shutdown(2000u), BREAK_RUNTIME_OK);

    {
        BreakRuntimeOwnedMessage *again = NULL;
        ASSERT_EQ(break_runtime_io_poll_completion(req, &again),
                  BREAK_RUNTIME_OK);
        ASSERT_EQ(again, NULL); /* exactly one completion, always */
    }

    ASSERT_EQ(break_runtime_io_stats(&stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.cancelled, 1u);
    ASSERT_EQ(stats.stale_drops, 1u);
    ASSERT_EQ(stats.completed, 0u);
    ASSERT_EQ(stats.bytes_published, 0u);

    break_runtime_io_request_release(req);
    vfs_destroy(vfs);
}

TEST(io_queue_overload_never_waits)
{
    VFS *vfs = fixture_setup();
    BreakRuntimeIoConfig cfg;
    BreakRuntimeIoRequest *reqs[8];
    BreakRuntimeIoRequest *extra = NULL;
    BreakRuntimeIoStats stats;
    int i;

    ASSERT_NOT_NULL(vfs);
    /* Worker parked before the claim: every submit lands in the bounded
     * pending ring and stays there. */
    break_runtime_test_io_set_gates(1u, 0u);

    memset(&cfg, 0, sizeof(cfg));
    cfg.vfs = vfs;
    cfg.worker_count = 1u;
    cfg.request_capacity = 8u;
    ASSERT_EQ(break_runtime_io_init(&cfg), BREAK_RUNTIME_OK);

    memset(reqs, 0, sizeof(reqs));
    for (i = 0; i < 8; i++) {
        ASSERT_EQ(break_runtime_io_submit(&reqs[i], "payload.bin", 0u, 0u),
                  BREAK_RUNTIME_OK);
        ASSERT_NOT_NULL(reqs[i]);
    }
    /* Capacity reached: non-blocking OVERLOAD, never a wait. */
    ASSERT_EQ(break_runtime_io_submit(&extra, "payload.bin", 0u, 0u),
              BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(extra, NULL);

    ASSERT_EQ(break_runtime_io_stats(&stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.submitted, 8u);
    ASSERT_EQ(stats.overload_rejects, 1u);
    ASSERT_EQ(stats.active, 8u);
    ASSERT_EQ(stats.high_water, 8u);

    for (i = 0; i < 8; i++) {
        BreakRuntimeOwnedMessage *msg = NULL;
        BreakRuntimeIoCompletion completion;
        ASSERT_EQ(break_runtime_io_cancel(reqs[i]), BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_io_poll_completion(reqs[i], &msg),
                  BREAK_RUNTIME_OK);
        ASSERT_NOT_NULL(msg);
        ASSERT_EQ(parse_completion(msg, &completion), BREAK_RUNTIME_OK);
        ASSERT_EQ(completion.state, BREAK_RUNTIME_IO_CANCELLED);
        break_runtime_message_release(msg);
    }

    break_runtime_test_io_set_gates(0u, 0u);
    ASSERT_EQ(break_runtime_io_shutdown(2000u), BREAK_RUNTIME_OK);

    for (i = 0; i < 8; i++) {
        break_runtime_io_request_release(reqs[i]);
    }
    ASSERT_EQ(break_runtime_io_stats(&stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.cancelled, 8u);
    ASSERT_EQ(stats.active, 0u);

    vfs_destroy(vfs);
}

TEST(io_release_queued_at_full_ring_keeps_integrity)
{
    /* Regression (review Critical 1): releasing a still-QUEUED request
     * decrements the live-request count but NOT the ring occupancy — the
     * slot is reclaimed only at claim/drain. Submitting into that window
     * must be rejected by the physical ring gate (OVERLOAD); without it the
     * push slot (head + ring_count) % capacity overwrites a live entry. */
    VFS *vfs = fixture_setup();
    BreakRuntimeIoConfig cfg;
    BreakRuntimeIoRequest *req_a = NULL;
    BreakRuntimeIoRequest *req_b = NULL;
    BreakRuntimeIoRequest *req_c = NULL;
    BreakRuntimeOwnedMessage *msg = NULL;
    BreakRuntimeIoCompletion completion;
    BreakRuntimeIoStats stats;

    ASSERT_NOT_NULL(vfs);
    /* Worker parked before the claim: both submits occupy the ring. */
    break_runtime_test_io_set_gates(1u, 0u);

    memset(&cfg, 0, sizeof(cfg));
    cfg.vfs = vfs;
    cfg.worker_count = 1u;
    cfg.request_capacity = 2u;
    ASSERT_EQ(break_runtime_io_init(&cfg), BREAK_RUNTIME_OK);

    ASSERT_EQ(break_runtime_io_submit(&req_a, "payload.bin", 0u, 0u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_io_submit(&req_b, "payload.bin", 0u, 0u),
              BREAK_RUNTIME_OK);
    /* Ring full AND live count full: OVERLOAD via the live-count gate. */
    ASSERT_EQ(break_runtime_io_submit(&req_c, "payload.bin", 0u, 0u),
              BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(req_c, NULL);

    /* Release the still-QUEUED A: live count drops, ring slot stays. */
    break_runtime_io_request_release(req_a);
    ASSERT_EQ(break_runtime_io_stats(&stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.active, 1u);

    /* The ring is still physically full: the ring gate must reject. */
    ASSERT_EQ(break_runtime_io_submit(&req_c, "payload.bin", 0u, 0u),
              BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(req_c, NULL);
    ASSERT_EQ(break_runtime_io_stats(&stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.overload_rejects, 2u);

    /* B is cancelled while queued; A is processed normally after the gate
     * opens (its completion is abandoned with the released request). */
    ASSERT_EQ(break_runtime_io_cancel(req_b), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_io_poll_completion(req_b, &msg),
              BREAK_RUNTIME_OK);
    ASSERT_NOT_NULL(msg);
    ASSERT_EQ(parse_completion(msg, &completion), BREAK_RUNTIME_OK);
    ASSERT_EQ(completion.state, BREAK_RUNTIME_IO_CANCELLED);
    break_runtime_message_release(msg);

    /* Ungate and let the worker CLAIM A (QUEUED -> READING) before the
     * shutdown drain can cancel it: this exercises the released-but-in-
     * flight path — the read completes, publishes into the released
     * request, and the facade-reference drop frees it. The popped counter
     * makes the claim deterministic. */
    {
        u64 baseline = atomic_load_explicit(&g_break_runtime_test_io_popped,
                                            memory_order_acquire);
        break_runtime_test_io_set_gates(0u, 0u);
        spin_until_u64(&g_break_runtime_test_io_popped, baseline + 1u);
    }
    ASSERT_EQ(break_runtime_io_shutdown(2000u), BREAK_RUNTIME_OK);

    break_runtime_io_request_release(req_b);
    ASSERT_EQ(break_runtime_io_stats(&stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.submitted, 2u);
    ASSERT_EQ(stats.overload_rejects, 2u);
    ASSERT_EQ(stats.completed, 1u); /* A's read completed before release-free */
    ASSERT_EQ(stats.cancelled, 1u);
    ASSERT_EQ(stats.stale_drops, 0u);
    ASSERT_EQ(stats.active, 0u);

    vfs_destroy(vfs);
}

TEST(io_cancel_completion_oom_keeps_completion_promise)
{
    /* Regression (review Important 2): a cancel whose completion build OOMs
     * must leave the request completely untouched (no state change, no
     * generation bump) — "exactly one completion per request, always" must
     * survive the OOM path for both QUEUED and READING requests. */
    VFS *vfs = fixture_setup();
    BreakRuntimeIoConfig cfg;
    BreakRuntimeIoRequest *req_q = NULL;
    BreakRuntimeIoRequest *req_r = NULL;
    BreakRuntimeOwnedMessage *msg = NULL;
    BreakRuntimeIoCompletion completion;
    BreakRuntimeIoStats stats;
    u64 baseline;

    ASSERT_NOT_NULL(vfs);
    /* Phase 1 (QUEUED): the pop gate must be armed BEFORE init so the
     * worker hits it at loop top — a worker already parked in the
     * empty-ring wait would be woken by submit's signal past the gate
     * (the gate is only checked at loop top). */
    break_runtime_test_io_set_gates(1u, 0u);

    memset(&cfg, 0, sizeof(cfg));
    cfg.vfs = vfs;
    cfg.worker_count = 1u;
    cfg.request_capacity = 4u;
    ASSERT_EQ(break_runtime_io_init(&cfg), BREAK_RUNTIME_OK);

    /* Cancel OOM first, then a successful cancel retry. */
    ASSERT_EQ(break_runtime_io_submit(&req_q, "payload.bin", 0u, 0u),
              BREAK_RUNTIME_OK);
    break_runtime_test_set_alloc_budget(0u);
    ASSERT_EQ(break_runtime_io_cancel(req_q), BREAK_RUNTIME_OOM);
    break_runtime_test_set_alloc_budget(BREAK_RUNTIME_TEST_ALLOC_DISABLED);
    /* Untouched: no completion was published by the failed cancel. */
    ASSERT_EQ(break_runtime_io_poll_completion(req_q, &msg),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(msg, NULL);
    /* Retry succeeds and publishes exactly one CANCELLED completion. */
    ASSERT_EQ(break_runtime_io_cancel(req_q), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_io_poll_completion(req_q, &msg),
              BREAK_RUNTIME_OK);
    ASSERT_NOT_NULL(msg);
    ASSERT_EQ(parse_completion(msg, &completion), BREAK_RUNTIME_OK);
    ASSERT_EQ(completion.state, BREAK_RUNTIME_IO_CANCELLED);
    break_runtime_message_release(msg);

    /* Phase 2 (READING): the worker claims the request and parks before the
     * read; cancel OOM must not strand it. */
    break_runtime_test_io_set_gates(0u, 1u);
    baseline = atomic_load_explicit(&g_break_runtime_test_io_popped,
                                    memory_order_acquire);
    ASSERT_EQ(break_runtime_io_submit(&req_r, "payload.bin", 0u, 0u),
              BREAK_RUNTIME_OK);
    spin_until_u64(&g_break_runtime_test_io_popped, baseline + 1u);

    break_runtime_test_set_alloc_budget(0u);
    ASSERT_EQ(break_runtime_io_cancel(req_r), BREAK_RUNTIME_OOM);
    break_runtime_test_set_alloc_budget(BREAK_RUNTIME_TEST_ALLOC_DISABLED);

    /* Ungated without a cancel: the in-flight read is NOT stale (the OOM
     * cancel never bumped the generation), so it publishes READY. */
    break_runtime_test_io_set_gates(0u, 0u);
    ASSERT_EQ(break_runtime_io_wait_completion(req_r, 5000u, &msg),
              BREAK_RUNTIME_OK);
    ASSERT_NOT_NULL(msg);
    ASSERT_EQ(parse_completion(msg, &completion), BREAK_RUNTIME_OK);
    ASSERT_EQ(completion.state, BREAK_RUNTIME_IO_COMPLETED);
    ASSERT_EQ(completion.byte_size, (u64)IO_TEST_FILE_BYTES);
    ASSERT_EQ(memcmp(completion.bytes, g_expected_bytes,
                     IO_TEST_FILE_BYTES), 0);
    break_runtime_message_release(msg);

    /* Exactly one completion; cancel after completion is REJECTED. */
    ASSERT_EQ(break_runtime_io_poll_completion(req_r, &msg),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(msg, NULL);
    ASSERT_EQ(break_runtime_io_cancel(req_r), BREAK_RUNTIME_REJECTED);

    break_runtime_io_request_release(req_q);
    break_runtime_io_request_release(req_r);
    ASSERT_EQ(break_runtime_io_shutdown(2000u), BREAK_RUNTIME_OK);

    ASSERT_EQ(break_runtime_io_stats(&stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.submitted, 2u);
    ASSERT_EQ(stats.cancelled, 1u);
    ASSERT_EQ(stats.completed, 1u);
    ASSERT_EQ(stats.stale_drops, 0u);
    ASSERT_EQ(stats.active, 0u);

    vfs_destroy(vfs);
}

/* ------------------------------------------------------------------ */
/* shutdown interruption of completion waits                           */
/* ------------------------------------------------------------------ */

typedef struct IoWaiterCtx {
    BreakRuntimeIoRequest *request;
    _Atomic u32 stage;
    BreakRuntimeError first_result;  /* short wait: expect TIMEOUT */
    BreakRuntimeError second_result; /* long wait: expect CLOSED */
    BreakRuntimeOwnedMessage *msg;
} IoWaiterCtx;

static PLATFORM_THREAD_RET io_waiter_main(PLATFORM_THREAD_ARG arg)
{
    IoWaiterCtx *w = (IoWaiterCtx *)arg;
    /* Deadline-interruptible: a short budget expires while the completion
     * is not published; the completion is NOT consumed (retry allowed). */
    atomic_store_explicit(&w->stage, 1u, memory_order_release);
    w->first_result =
        break_runtime_io_wait_completion(w->request, 30u, &w->msg);
    /* Shutdown-interruptible: the long wait is released by shutdown. */
    atomic_store_explicit(&w->stage, 2u, memory_order_release);
    w->second_result =
        break_runtime_io_wait_completion(w->request, 30000u, &w->msg);
    atomic_store_explicit(&w->stage, 3u, memory_order_release);
    return PLATFORM_THREAD_RETURN;
}

TEST(io_completion_wait_deadline_and_shutdown_interruption)
{
    VFS *vfs = fixture_setup();
    BreakRuntimeIoConfig cfg;
    BreakRuntimeIoRequest *req = NULL;
    BreakRuntimeOwnedMessage *msg = NULL;
    BreakRuntimeIoCompletion completion;
    IoWaiterCtx waiter;
    PlatformThread waiter_thread;
    BreakRuntimeIoStats stats;

    ASSERT_NOT_NULL(vfs);
    memset(&cfg, 0, sizeof(cfg));
    cfg.vfs = vfs;
    cfg.worker_count = 1u;
    cfg.request_capacity = 4u;
    ASSERT_EQ(break_runtime_io_init(&cfg), BREAK_RUNTIME_OK);

    /* The worker claims the request (READING) then parks before the read:
     * no completion will be published until the gate is released. */
    break_runtime_test_io_set_gates(0u, 1u);
    {
        u64 baseline = atomic_load_explicit(&g_break_runtime_test_io_popped,
                                            memory_order_acquire);
        ASSERT_EQ(break_runtime_io_submit(&req, "payload.bin", 0u, 0u),
                  BREAK_RUNTIME_OK);
        spin_until_u64(&g_break_runtime_test_io_popped, baseline + 1u);
    }

    memset(&waiter, 0, sizeof(waiter));
    waiter.request = req;
    ASSERT_TRUE(platform_thread_create(&waiter_thread, io_waiter_main,
                                       &waiter));
    spin_until(&waiter.stage, 2u);
    test_sleep_ms(30); /* the waiter is inside the long wait now */

    /* Shutdown: admission closes and every blocked completion wait wakes
     * with CLOSED. The gated worker cannot exit within 50ms, so shutdown
     * itself returns TIMEOUT and RETAINS live ownership. */
    ASSERT_EQ(break_runtime_io_shutdown(50u), BREAK_RUNTIME_TIMEOUT);

    spin_until(&waiter.stage, 3u);
    platform_thread_join(waiter_thread);
    ASSERT_EQ(waiter.first_result, BREAK_RUNTIME_TIMEOUT);
    ASSERT_EQ(waiter.second_result, BREAK_RUNTIME_CLOSED);
    ASSERT_EQ(waiter.msg, NULL); /* interrupted wait consumed nothing */

    /* Submit stays CLOSED while STOPPING. */
    {
        BreakRuntimeIoRequest *late = NULL;
        ASSERT_EQ(break_runtime_io_submit(&late, "payload.bin", 0u, 0u),
                  BREAK_RUNTIME_CLOSED);
        ASSERT_EQ(late, NULL);
    }

    /* Release the gate: the worker completes the read and publishes the
     * READY completion even while the facade is STOPPING; the per-request
     * completion belongs to the request, not to the lifecycle. */
    break_runtime_test_io_set_gates(0u, 0u);

    /* Retry resumes the timed-out stop: the worker is joined now. */
    ASSERT_EQ(break_runtime_io_shutdown(5000u), BREAK_RUNTIME_OK);

    /* The completion published mid-shutdown is still pollable. */
    ASSERT_EQ(break_runtime_io_poll_completion(req, &msg), BREAK_RUNTIME_OK);
    ASSERT_NOT_NULL(msg);
    ASSERT_EQ(parse_completion(msg, &completion), BREAK_RUNTIME_OK);
    ASSERT_EQ(completion.state, BREAK_RUNTIME_IO_COMPLETED);
    ASSERT_EQ(completion.byte_size, (u64)IO_TEST_FILE_BYTES);
    ASSERT_EQ(memcmp(completion.bytes, g_expected_bytes,
                     IO_TEST_FILE_BYTES), 0);
    break_runtime_message_release(msg);
    break_runtime_io_request_release(req);

    ASSERT_EQ(break_runtime_io_stats(&stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.completed, 1u);
    ASSERT_EQ(stats.active, 0u);

    vfs_destroy(vfs);
}

TEST(io_request_double_release_aborts)
{
#if !defined(_WIN32)
    pid_t pid = fork();
    if (pid == 0) {
        VFS *vfs = fixture_setup();
        BreakRuntimeIoConfig cfg;
        BreakRuntimeIoRequest *req = NULL;
        if (!vfs) {
            _exit(2); /* fixture failure: not the path under test */
        }
        memset(&cfg, 0, sizeof(cfg));
        cfg.vfs = vfs;
        cfg.worker_count = 1u;
        cfg.request_capacity = 4u;
        if (break_runtime_io_init(&cfg) != BREAK_RUNTIME_OK) {
            _exit(2);
        }
        if (break_runtime_io_submit(&req, "payload.bin", 0u, 0u) !=
                BREAK_RUNTIME_OK ||
            break_runtime_io_cancel(req) != BREAK_RUNTIME_OK ||
            break_runtime_io_shutdown(2000u) != BREAK_RUNTIME_OK) {
            _exit(2); /* setup failed: not the path under test */
        }
        break_runtime_io_request_release(req);
        break_runtime_io_request_release(req); /* violation: must abort */
        _exit(0); /* reached only if double release was NOT rejected */
    }
    ASSERT_TRUE(pid > 0);
    {
        int status = 0;
        ASSERT_EQ(waitpid(pid, &status, 0), pid);
        if (WIFEXITED(status)) {
            /* 2 = the child's setup failed before the path under test (e.g.
             * shutdown timed out on a loaded runner); 0 = the double release
             * was NOT rejected. Print which, so CI failures are diagnosable. */
            printf("    child exited %d (%s)\n", WEXITSTATUS(status),
                   WEXITSTATUS(status) == 0 ? "double release not rejected"
                                            : "setup failed before the test path");
        }
        ASSERT_TRUE(WIFSIGNALED(status));
    }
#endif
}

TEST(io_facade_alloc_failure_injection)
{
    VFS *vfs = fixture_setup();
    BreakRuntimeIoConfig cfg;
    BreakRuntimeIoRequest *req = NULL;
    BreakRuntimeOwnedMessage *msg = NULL;

    ASSERT_NOT_NULL(vfs);
    /* Park the worker before it can claim: the request must stay QUEUED so the
     * cancel below cannot race a read that has already completed (cancel then
     * correctly answers REJECTED). */
    break_runtime_test_io_set_gates(1u, 0u);

    memset(&cfg, 0, sizeof(cfg));
    cfg.vfs = vfs;
    cfg.worker_count = 1u;
    cfg.request_capacity = 4u;

    break_runtime_test_set_alloc_budget(0u);
    ASSERT_EQ(break_runtime_io_init(&cfg), BREAK_RUNTIME_OOM);
    break_runtime_test_set_alloc_budget(BREAK_RUNTIME_TEST_ALLOC_DISABLED);

    ASSERT_EQ(break_runtime_io_init(&cfg), BREAK_RUNTIME_OK);

    /* Submit OOM: out_request stays NULL, nothing is retained. */
    break_runtime_test_set_alloc_budget(0u);
    ASSERT_EQ(break_runtime_io_submit(&req, "payload.bin", 0u, 0u),
              BREAK_RUNTIME_OOM);
    ASSERT_EQ(req, NULL);
    break_runtime_test_set_alloc_budget(BREAK_RUNTIME_TEST_ALLOC_DISABLED);

    /* The facade is fully functional after the injected failure. */
    ASSERT_EQ(break_runtime_io_submit(&req, "payload.bin", 0u, 0u),
              BREAK_RUNTIME_OK);
    ASSERT_NOT_NULL(req);
    ASSERT_EQ(break_runtime_io_cancel(req), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_io_poll_completion(req, &msg), BREAK_RUNTIME_OK);
    ASSERT_NOT_NULL(msg);
    break_runtime_message_release(msg);
    break_runtime_io_request_release(req);

    break_runtime_test_io_set_gates(0u, 0u);
    ASSERT_EQ(break_runtime_io_shutdown(2000u), BREAK_RUNTIME_OK);
    vfs_destroy(vfs);
}

TEST_MAIN_BEGIN()
    RUN_TEST(thread_create_validation_and_oom);
    RUN_TEST(thread_start_runs_and_owner_stops);
    RUN_TEST(thread_self_exit_owner_completion);
    RUN_TEST(thread_stop_timeout_retains_live_ownership);
    RUN_TEST(io_submit_validation);
    RUN_TEST(io_read_completion_owned_bytes);
    RUN_TEST(io_missing_file_failed_completion);
    RUN_TEST(io_deadline_timeout_completion);
    RUN_TEST(io_cancel_before_start);
    RUN_TEST(io_stale_generation_dropped);
    RUN_TEST(io_queue_overload_never_waits);
    RUN_TEST(io_release_queued_at_full_ring_keeps_integrity);
    RUN_TEST(io_cancel_completion_oom_keeps_completion_promise);
    RUN_TEST(io_completion_wait_deadline_and_shutdown_interruption);
    RUN_TEST(io_request_double_release_aborts);
    RUN_TEST(io_facade_alloc_failure_injection);
TEST_MAIN_END()
