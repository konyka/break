#include "test_framework.h"
#include <runtime/runtime_reload.h>
#include <runtime/runtime_profiler.h>
#include <runtime/runtime_thread.h>
#include <runtime/runtime_test_hooks.h>
#include <core/platform_thread.h>
#include <core/profiler.h>
#include <asset/vfs.h>
#include <stdatomic.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#if !defined(_WIN32)
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#endif

/* Focused contract tests for the Runtime Core reload coordinator and the
 * profiler bridge (Task 6). Links the test-only runtime_core_test variant
 * (BREAK_RUNTIME_TESTING=1) for allocation failure injection and the
 * deterministic reload worker gates; vfs.c, profiler.c and time.c are
 * compiled beside the test (borrowed VFS + borrowed profiler singleton
 * resolve at this final link, mirroring test_runtime_io). The compatibility
 * filewatch.c/hotreload.c are NOT compiled here and stay unchanged: the only
 * seams under test are break_runtime_reload_notify_file_event() and the
 * owner-thread commit hook. */

/* ------------------------------------------------------------------ */
/* helpers + fixture                                                   */
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

#define RELOAD_TEST_FILE_BYTES 4096u

static u8 g_expected_bytes[RELOAD_TEST_FILE_BYTES];
static u8 g_expected_hash;

static char g_reload_dir[512];

typedef struct ReloadProbe {
    _Atomic u32 validate_calls;
    _Atomic u32 commit_calls;
    _Atomic u32 commit_on_owner; /* commit observed on the creating thread */
    _Atomic u32 commit_fail;     /* force the commit hook to fail */
    _Atomic u32 commit_block;    /* park the commit hook until released */
    _Atomic u32 commit_entered;
    _Atomic u32 commit_release;
    PlatformThreadId owner;      /* set by the fixture (main thread) */
    u32 live_version;            /* "old data": only the owner thread touches it */
    u8 last_hash;                /* xor of committed bytes (owner thread only) */
} ReloadProbe;

static ReloadProbe g_probe;

static BreakRuntimeError probe_validate(const char *path, const void *bytes,
                                        usize size, void *user)
{
    ReloadProbe *probe = (ReloadProbe *)user;
    (void)bytes;
    (void)size;
    atomic_fetch_add_explicit(&probe->validate_calls, 1u, memory_order_acq_rel);
    if (strstr(path, "bad") != NULL) {
        return BREAK_RUNTIME_FAILED;
    }
    return BREAK_RUNTIME_OK;
}

static BreakRuntimeError probe_commit(const char *path, const void *bytes,
                                      usize size, void *user)
{
    ReloadProbe *probe = (ReloadProbe *)user;
    const u8 *data = (const u8 *)bytes;
    u8 hash = 0u;
    usize i;
    (void)path;
    atomic_fetch_add_explicit(&probe->commit_calls, 1u, memory_order_acq_rel);
    if (platform_thread_id_equal(probe->owner, platform_thread_current_id())) {
        atomic_store_explicit(&probe->commit_on_owner, 1u, memory_order_release);
    }
    if (atomic_load_explicit(&probe->commit_block, memory_order_acquire) != 0u) {
        u32 guard = 0u;
        atomic_store_explicit(&probe->commit_entered, 1u, memory_order_release);
        while (atomic_load_explicit(&probe->commit_release,
                                    memory_order_acquire) == 0u &&
               guard++ < 4000000u) {
            platform_thread_yield();
        }
    }
    if (atomic_load_explicit(&probe->commit_fail, memory_order_acquire) != 0u) {
        return BREAK_RUNTIME_FAILED; /* old version preserved */
    }
    for (i = 0; i < size; i++) {
        hash ^= data[i];
    }
    probe->last_hash = hash;
    probe->live_version++;
    return BREAK_RUNTIME_OK;
}

/* Creates the per-process fixture once: tmp dir with good.bin / good2.bin /
 * bad.bin and a VFS with the dir mounted. */
static VFS *fixture_setup(void)
{
    VFS *vfs;
    FILE *fp;
    usize i;
    u8 hash = 0u;
    char file_path[640];

    for (i = 0; i < (usize)RELOAD_TEST_FILE_BYTES; i++) {
        g_expected_bytes[i] = (u8)((i * 31u + 7u) & 0xFFu);
        hash ^= g_expected_bytes[i];
    }
    g_expected_hash = hash;

    test_tmp(g_reload_dir, sizeof(g_reload_dir), "rtreload");
    TEST_MKDIR(g_reload_dir);
    for (i = 0; i < 7u; i++) {
        static const char *names[7] = {"good.bin", "good2.bin", "bad.bin",
                                       "ovl0.bin", "ovl1.bin", "ovl2.bin",
                                       "ovl3.bin"};
        snprintf(file_path, sizeof(file_path), "%s/%s", g_reload_dir, names[i]);
        fp = fopen(file_path, "wb");
        if (!fp) {
            return NULL;
        }
        if (fwrite(g_expected_bytes, 1, RELOAD_TEST_FILE_BYTES, fp) !=
            RELOAD_TEST_FILE_BYTES) {
            fclose(fp);
            return NULL;
        }
        fclose(fp);
    }

    vfs = vfs_create();
    if (!vfs) {
        return NULL;
    }
    if (!vfs_mount_dir(vfs, g_reload_dir)) {
        vfs_destroy(vfs);
        return NULL;
    }
    return vfs;
}

static void probe_reset(void)
{
    memset(&g_probe, 0, sizeof(g_probe));
    g_probe.owner = platform_thread_current_id();
}

/* Default config over the fixture VFS with the probe hooks. */
static BreakRuntimeReloadConfig probe_config(VFS *vfs)
{
    BreakRuntimeReloadConfig config;
    memset(&config, 0, sizeof(config));
    config.vfs = vfs;
    config.hooks.validate = probe_validate;
    config.hooks.commit = probe_commit;
    config.hooks.user = &g_probe;
    return config;
}

/* Polls until the request reaches a terminal state (consuming it exactly
 * once) or the guard expires. Returns the last poll result. */
static BreakRuntimeError wait_terminal(BreakRuntimeReload *reload,
                                       BreakRuntimeReloadRequest request,
                                       BreakRuntimeReloadState *out_state)
{
    u32 guard = 0u;
    for (;;) {
        BreakRuntimeError err = break_runtime_reload_poll(reload, request,
                                                          out_state);
        if (err != BREAK_RUNTIME_OK) {
            return err;
        }
        if ((u32)*out_state >= (u32)BREAK_RUNTIME_RELOAD_COMMITTED) {
            return BREAK_RUNTIME_OK;
        }
        if (guard++ > 20000u) {
            return BREAK_RUNTIME_TIMEOUT;
        }
        test_sleep_ms(1);
    }
}

/* Polls (non-consuming) until the request shows `wanted` or the guard
 * expires. */
static BreakRuntimeError wait_state(BreakRuntimeReload *reload,
                                    BreakRuntimeReloadRequest request,
                                    BreakRuntimeReloadState wanted)
{
    u32 guard = 0u;
    for (;;) {
        BreakRuntimeReloadState state = BREAK_RUNTIME_RELOAD_LOADING;
        BreakRuntimeError err = break_runtime_reload_poll(reload, request,
                                                          &state);
        if (err != BREAK_RUNTIME_OK) {
            return err;
        }
        if (state == wanted) {
            return BREAK_RUNTIME_OK;
        }
        if (guard++ > 20000u) {
            return BREAK_RUNTIME_TIMEOUT;
        }
        test_sleep_ms(1);
    }
}

static void spin_until_u64(_Atomic u64 *flag, u64 value)
{
    u32 guard = 0u;
    while (atomic_load_explicit(flag, memory_order_acquire) != value &&
           guard++ < 4000000u) {
        platform_thread_yield();
    }
}

/* Spins until the stats snapshot satisfies the predicate (or the guard
 * expires, which the caller's assertions then catch). */
static void spin_until_stats(BreakRuntimeReload *reload,
                             int (*pred)(const BreakRuntimeReloadStats *,
                                         void *),
                             void *ctx,
                             BreakRuntimeReloadStats *out_stats)
{
    u32 guard = 0u;
    for (;;) {
        BreakRuntimeReloadStats stats;
        if (break_runtime_reload_stats(reload, &stats) == BREAK_RUNTIME_OK &&
            pred(&stats, ctx)) {
            if (out_stats) {
                *out_stats = stats;
            }
            return;
        }
        if (guard++ > 4000000u) {
            if (out_stats) {
                (void)break_runtime_reload_stats(reload, out_stats);
            }
            return;
        }
        platform_thread_yield();
    }
}

typedef struct U64PredCtx {
    u64 target;
} U64PredCtx;

static int stats_stale_drops_eq(const BreakRuntimeReloadStats *s, void *ctx)
{
    return s->stale_drops == ((U64PredCtx *)ctx)->target;
}

static int stats_commit_overloads_eq(const BreakRuntimeReloadStats *s,
                                     void *ctx)
{
    return s->commit_overloads == ((U64PredCtx *)ctx)->target;
}

/* ------------------------------------------------------------------ */
/* reload: create/validation/OOM                                       */
/* ------------------------------------------------------------------ */

TEST(reload_create_validation_and_oom)
{
    VFS *vfs = fixture_setup();
    BreakRuntimeReload *reload = NULL;
    BreakRuntimeReloadConfig config;
    u32 budget;
    u32 first_success = 0xFFFFFFFFu;
    ASSERT_NOT_NULL(vfs);

    probe_reset();
    config = probe_config(vfs);

    ASSERT_EQ(break_runtime_reload_create(NULL, &reload), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_reload_create(&config, NULL), BREAK_RUNTIME_INVALID);

    {
        BreakRuntimeReloadConfig bad = config;
        bad.vfs = NULL;
        ASSERT_EQ(break_runtime_reload_create(&bad, &reload),
                  BREAK_RUNTIME_INVALID);
        ASSERT_EQ(reload, NULL);
    }
    {
        BreakRuntimeReloadConfig bad = config;
        bad.hooks.commit = NULL;
        ASSERT_EQ(break_runtime_reload_create(&bad, &reload),
                  BREAK_RUNTIME_INVALID);
    }
    {
        BreakRuntimeReloadConfig bad = config;
        bad.worker_count = BREAK_RUNTIME_RELOAD_MAX_WORKERS + 1u;
        ASSERT_EQ(break_runtime_reload_create(&bad, &reload),
                  BREAK_RUNTIME_INVALID);
    }
    {
        BreakRuntimeReloadConfig bad = config;
        bad.request_capacity = BREAK_RUNTIME_RELOAD_MAX_REQUEST_CAPACITY + 1u;
        ASSERT_EQ(break_runtime_reload_create(&bad, &reload),
                  BREAK_RUNTIME_INVALID);
    }
    {
        BreakRuntimeReloadConfig bad = config;
        bad.event_capacity = BREAK_RUNTIME_RELOAD_MAX_EVENT_CAPACITY + 1u;
        ASSERT_EQ(break_runtime_reload_create(&bad, &reload),
                  BREAK_RUNTIME_INVALID);
    }
    {
        BreakRuntimeReloadConfig bad = config;
        bad.commit_capacity = BREAK_RUNTIME_RELOAD_MAX_COMMIT_CAPACITY + 1u;
        ASSERT_EQ(break_runtime_reload_create(&bad, &reload),
                  BREAK_RUNTIME_INVALID);
    }

    /* Allocation failure injection on EVERY create alloc path: every budget
     * below the requirement fails cleanly (out==NULL), and the first
     * sufficient budget succeeds. */
    for (budget = 0u; budget < 64u; budget++) {
        break_runtime_test_set_alloc_budget(budget);
        if (break_runtime_reload_create(&config, &reload) == BREAK_RUNTIME_OK) {
            first_success = budget;
            break_runtime_test_set_alloc_budget(
                BREAK_RUNTIME_TEST_ALLOC_DISABLED);
            break;
        }
        ASSERT_EQ(reload, NULL);
    }
    break_runtime_test_set_alloc_budget(BREAK_RUNTIME_TEST_ALLOC_DISABLED);
    ASSERT_TRUE(first_success != 0xFFFFFFFFu);
    ASSERT_TRUE(first_success > 0u); /* at least one allocation is required */

    ASSERT_EQ(break_runtime_reload_shutdown(reload, 2000u), BREAK_RUNTIME_OK);
    break_runtime_reload_destroy(reload);
    vfs_destroy(vfs);
}

TEST(reload_request_validation)
{
    VFS *vfs = fixture_setup();
    BreakRuntimeReload *reload = NULL;
    BreakRuntimeReloadConfig config;
    BreakRuntimeReloadRequest request = 0u;
    BreakRuntimeReloadState state = BREAK_RUNTIME_RELOAD_COMMITTED;
    char long_path[320];
    ASSERT_NOT_NULL(vfs);

    probe_reset();
    break_runtime_test_reload_set_gates(1u, 0u); /* workers park pre-claim */
    config = probe_config(vfs);
    ASSERT_EQ(break_runtime_reload_create(&config, &reload), BREAK_RUNTIME_OK);

    ASSERT_EQ(break_runtime_reload_request(NULL, "good.bin", &request),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_reload_request(reload, NULL, &request),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_reload_request(reload, "", &request),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_reload_request(reload, "good.bin", NULL),
              BREAK_RUNTIME_INVALID);
    memset(long_path, 'a', sizeof(long_path) - 1u);
    long_path[sizeof(long_path) - 1u] = '\0';
    ASSERT_EQ(break_runtime_reload_request(reload, long_path, &request),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(request, 0u);

    /* Poll/cancel argument validation. */
    ASSERT_EQ(break_runtime_reload_poll(reload, 0u, &state),
              BREAK_RUNTIME_STALE);
    ASSERT_EQ(break_runtime_reload_poll(reload, 12345u, &state),
              BREAK_RUNTIME_STALE);
    ASSERT_EQ(break_runtime_reload_poll(reload, 0u, NULL),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_reload_cancel(reload, 0u), BREAK_RUNTIME_STALE);

    /* Non-terminal poll is non-consuming: the handle stays live. */
    ASSERT_EQ(break_runtime_reload_request(reload, "good.bin", &request),
              BREAK_RUNTIME_OK);
    ASSERT_NEQ(request, 0u);
    ASSERT_EQ(break_runtime_reload_poll(reload, request, &state),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(state, BREAK_RUNTIME_RELOAD_LOADING);
    ASSERT_EQ(break_runtime_reload_poll(reload, request, &state),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(state, BREAK_RUNTIME_RELOAD_LOADING);

    ASSERT_EQ(break_runtime_reload_cancel(reload, request), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_poll(reload, request, &state),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(state, BREAK_RUNTIME_RELOAD_CANCELLED);

    break_runtime_test_reload_set_gates(0u, 0u);
    ASSERT_EQ(break_runtime_reload_shutdown(reload, 2000u), BREAK_RUNTIME_OK);
    break_runtime_reload_destroy(reload);
    vfs_destroy(vfs);
}

TEST(reload_enum_ordinals_and_names)
{
    /* The brief's reload state enum is a verbatim contract: lock the
     * ordinals in place. */
    ASSERT_EQ((int)BREAK_RUNTIME_RELOAD_LOADING, 0);
    ASSERT_EQ((int)BREAK_RUNTIME_RELOAD_VALIDATING, 1);
    ASSERT_EQ((int)BREAK_RUNTIME_RELOAD_COMMITTED, 2);
    ASSERT_EQ((int)BREAK_RUNTIME_RELOAD_FAILED_KEEP_OLD, 3);
    ASSERT_EQ((int)BREAK_RUNTIME_RELOAD_CANCELLED, 4);
    ASSERT_EQ((int)BREAK_RUNTIME_RELOAD_TIMEOUT, 5);
    ASSERT_EQ((int)BREAK_RUNTIME_RELOAD_OOM, 6);
    ASSERT_STR_EQ(break_runtime_reload_state_name(BREAK_RUNTIME_RELOAD_LOADING),
                  "LOADING");
    ASSERT_STR_EQ(break_runtime_reload_state_name(BREAK_RUNTIME_RELOAD_OOM),
                  "OOM");
    ASSERT_STR_EQ(break_runtime_reload_state_name(
                      (BreakRuntimeReloadState)4242),
                  "UNKNOWN");
}

/* ------------------------------------------------------------------ */
/* reload: file event coalescing + overload                            */
/* ------------------------------------------------------------------ */

TEST(reload_file_event_coalescing)
{
    VFS *vfs = fixture_setup();
    BreakRuntimeReload *reload = NULL;
    BreakRuntimeReloadConfig config;
    BreakRuntimeReloadStats stats;
    BreakRuntimeReloadState state;
    u32 count = 0xFFFFFFFFu;
    u32 i;
    ASSERT_NOT_NULL(vfs);

    probe_reset();
    break_runtime_test_reload_set_gates(1u, 0u); /* nothing loads */
    config = probe_config(vfs);
    ASSERT_EQ(break_runtime_reload_create(&config, &reload), BREAK_RUNTIME_OK);

    /* A burst of hints for one asset coalesces into one pending event. */
    for (i = 0; i < 5u; i++) {
        ASSERT_EQ(break_runtime_reload_notify_file_event(reload, "good.bin"),
                  BREAK_RUNTIME_OK);
    }
    ASSERT_EQ(break_runtime_reload_stats(reload, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.events_notified, 1u);
    ASSERT_EQ(stats.events_coalesced, 4u);

    /* The owner pump converts the coalesced hint into exactly one request. */
    ASSERT_EQ(break_runtime_reload_pump_events(reload, 8u, &count),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(count, 1u);
    ASSERT_EQ(break_runtime_reload_stats(reload, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.requested, 1u);
    ASSERT_EQ(stats.active, 1u);

    /* The queue is drained: a second pump starts nothing. */
    ASSERT_EQ(break_runtime_reload_pump_events(reload, 8u, &count),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(count, 0u);

    /* Validation: empty/over-long event paths are rejected. */
    ASSERT_EQ(break_runtime_reload_notify_file_event(reload, NULL),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_reload_notify_file_event(reload, ""),
              BREAK_RUNTIME_INVALID);

    break_runtime_test_reload_set_gates(0u, 0u);
    ASSERT_EQ(break_runtime_reload_shutdown(reload, 2000u), BREAK_RUNTIME_OK);
    /* Shutdown finalized the pending request as CANCELLED; its handle stays
     * pollable across shutdown. We never kept the handle here (pump-owned),
     * so only stats are observable. */
    ASSERT_EQ(break_runtime_reload_stats(reload, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.cancelled, 1u);
    (void)state;
    break_runtime_reload_destroy(reload);
    vfs_destroy(vfs);
}

TEST(reload_file_event_queue_overload)
{
    VFS *vfs = fixture_setup();
    BreakRuntimeReload *reload = NULL;
    BreakRuntimeReloadConfig config;
    BreakRuntimeReloadStats stats;
    char path[32];
    u32 i;
    ASSERT_NOT_NULL(vfs);

    probe_reset();
    break_runtime_test_reload_set_gates(1u, 0u);
    config = probe_config(vfs);
    config.event_capacity = 4u;
    ASSERT_EQ(break_runtime_reload_create(&config, &reload), BREAK_RUNTIME_OK);

    for (i = 0u; i < 4u; i++) {
        snprintf(path, sizeof(path), "event%u.bin", i);
        ASSERT_EQ(break_runtime_reload_notify_file_event(reload, path),
                  BREAK_RUNTIME_OK);
    }
    /* A NEW path on a full queue is a bounded non-blocking OVERLOAD. */
    ASSERT_EQ(break_runtime_reload_notify_file_event(reload, "event5.bin"),
              BREAK_RUNTIME_OVERLOAD);
    /* A same-path hint still coalesces even when the queue is full. */
    ASSERT_EQ(break_runtime_reload_notify_file_event(reload, "event0.bin"),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_stats(reload, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.events_notified, 4u);
    ASSERT_EQ(stats.event_overloads, 1u);
    ASSERT_EQ(stats.events_coalesced, 1u);

    break_runtime_test_reload_set_gates(0u, 0u);
    ASSERT_EQ(break_runtime_reload_shutdown(reload, 2000u), BREAK_RUNTIME_OK);
    break_runtime_reload_destroy(reload);
    vfs_destroy(vfs);
}

/* ------------------------------------------------------------------ */
/* reload: commit flow + failure-preserves-old                         */
/* ------------------------------------------------------------------ */

TEST(reload_commit_success_owner_thread)
{
    VFS *vfs = fixture_setup();
    BreakRuntimeReload *reload = NULL;
    BreakRuntimeProfiler *profiler = NULL;
    BreakRuntimeReloadConfig config;
    BreakRuntimeReloadRequest request = 0u;
    BreakRuntimeReloadState state = BREAK_RUNTIME_RELOAD_LOADING;
    BreakRuntimeReloadStats stats;
    u32 count = 0u;
    ASSERT_NOT_NULL(vfs);

    probe_reset();
    ASSERT_EQ(break_runtime_profiler_create(NULL, &profiler), BREAK_RUNTIME_OK);
    config = probe_config(vfs);
    config.profiler = profiler;
    ASSERT_EQ(break_runtime_reload_create(&config, &reload), BREAK_RUNTIME_OK);

    ASSERT_EQ(break_runtime_reload_request(reload, "good.bin", &request),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(wait_state(reload, request, BREAK_RUNTIME_RELOAD_VALIDATING),
              BREAK_RUNTIME_OK);

    /* The commit hook runs ONLY via the owner-thread commit pump. */
    ASSERT_EQ(atomic_load_explicit(&g_probe.commit_calls,
                                   memory_order_acquire), 0u);
    ASSERT_EQ(break_runtime_reload_commit_owner(reload, 4u, &count),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(count, 1u);

    ASSERT_EQ(break_runtime_reload_poll(reload, request, &state),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(state, BREAK_RUNTIME_RELOAD_COMMITTED);
    /* Exactly once: the consumed terminal state is gone. */
    ASSERT_EQ(break_runtime_reload_poll(reload, request, &state),
              BREAK_RUNTIME_STALE);

    ASSERT_EQ(atomic_load_explicit(&g_probe.validate_calls,
                                   memory_order_acquire), 1u);
    ASSERT_EQ(atomic_load_explicit(&g_probe.commit_calls,
                                   memory_order_acquire), 1u);
    ASSERT_EQ(atomic_load_explicit(&g_probe.commit_on_owner,
                                   memory_order_acquire), 1u);
    ASSERT_EQ(g_probe.live_version, 1u);
    ASSERT_EQ(g_probe.last_hash, g_expected_hash);

    ASSERT_EQ(break_runtime_reload_stats(reload, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.committed, 1u);
    ASSERT_EQ(stats.active, 0u);

    /* Profiler bridge wiring: lifecycle instants flowed through the bridge
     * and are collectable on the owner thread. */
    {
        BreakRuntimeProfilerStats pstats;
        ProfilerMetaInstant meta[16];
        u32 meta_count = 0u;
        u32 i;
        int found_committed = 0;
        ASSERT_EQ(break_runtime_profiler_collect(profiler, 16u, &count),
                  BREAK_RUNTIME_OK);
        ASSERT_TRUE(count >= 1u);
        ASSERT_EQ(break_runtime_profiler_export_meta(profiler, meta, 16u,
                                                     &meta_count),
                  BREAK_RUNTIME_OK);
        ASSERT_EQ(meta_count, count);
        for (i = 0u; i < meta_count; i++) {
            if (strcmp(meta[i].key, "break.runtime.reload.committed") == 0) {
                found_committed = 1;
            }
        }
        ASSERT_TRUE(found_committed);
        ASSERT_EQ(break_runtime_profiler_stats(profiler, &pstats),
                  BREAK_RUNTIME_OK);
        ASSERT_EQ(pstats.overload_drops, 0u);
    }

    ASSERT_EQ(break_runtime_reload_shutdown(reload, 2000u), BREAK_RUNTIME_OK);
    break_runtime_reload_destroy(reload);
    break_runtime_profiler_destroy(profiler);
    vfs_destroy(vfs);
}

TEST(reload_load_failure_preserves_old_data)
{
    VFS *vfs = fixture_setup();
    BreakRuntimeReload *reload = NULL;
    BreakRuntimeReloadConfig config;
    BreakRuntimeReloadRequest request = 0u;
    BreakRuntimeReloadState state = BREAK_RUNTIME_RELOAD_LOADING;
    BreakRuntimeReloadStats stats;
    ASSERT_NOT_NULL(vfs);

    probe_reset();
    config = probe_config(vfs);
    ASSERT_EQ(break_runtime_reload_create(&config, &reload), BREAK_RUNTIME_OK);

    /* The file does not exist: staging fails, the old version stays live. */
    ASSERT_EQ(break_runtime_reload_request(reload, "missing.bin", &request),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(wait_terminal(reload, request, &state), BREAK_RUNTIME_OK);
    ASSERT_EQ(state, BREAK_RUNTIME_RELOAD_FAILED_KEEP_OLD);
    ASSERT_EQ(atomic_load_explicit(&g_probe.commit_calls,
                                   memory_order_acquire), 0u);
    ASSERT_EQ(g_probe.live_version, 0u);
    ASSERT_EQ(break_runtime_reload_stats(reload, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.failed_keep_old, 1u);

    ASSERT_EQ(break_runtime_reload_shutdown(reload, 2000u), BREAK_RUNTIME_OK);
    break_runtime_reload_destroy(reload);
    vfs_destroy(vfs);
}

TEST(reload_validate_failure_preserves_old_data)
{
    VFS *vfs = fixture_setup();
    BreakRuntimeReload *reload = NULL;
    BreakRuntimeReloadConfig config;
    BreakRuntimeReloadRequest request = 0u;
    BreakRuntimeReloadState state = BREAK_RUNTIME_RELOAD_LOADING;
    ASSERT_NOT_NULL(vfs);

    probe_reset();
    config = probe_config(vfs);
    ASSERT_EQ(break_runtime_reload_create(&config, &reload), BREAK_RUNTIME_OK);

    /* bad.bin loads fine but fails the validation hook: FAILED_KEEP_OLD and
     * the commit hook never runs. */
    ASSERT_EQ(break_runtime_reload_request(reload, "bad.bin", &request),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(wait_terminal(reload, request, &state), BREAK_RUNTIME_OK);
    ASSERT_EQ(state, BREAK_RUNTIME_RELOAD_FAILED_KEEP_OLD);
    ASSERT_EQ(atomic_load_explicit(&g_probe.validate_calls,
                                   memory_order_acquire), 1u);
    ASSERT_EQ(atomic_load_explicit(&g_probe.commit_calls,
                                   memory_order_acquire), 0u);
    ASSERT_EQ(g_probe.live_version, 0u);

    ASSERT_EQ(break_runtime_reload_shutdown(reload, 2000u), BREAK_RUNTIME_OK);
    break_runtime_reload_destroy(reload);
    vfs_destroy(vfs);
}

TEST(reload_commit_failure_preserves_old_data)
{
    VFS *vfs = fixture_setup();
    BreakRuntimeReload *reload = NULL;
    BreakRuntimeReloadConfig config;
    BreakRuntimeReloadRequest request = 0u;
    BreakRuntimeReloadState state = BREAK_RUNTIME_RELOAD_LOADING;
    u32 count = 0u;
    ASSERT_NOT_NULL(vfs);

    probe_reset();
    config = probe_config(vfs);
    ASSERT_EQ(break_runtime_reload_create(&config, &reload), BREAK_RUNTIME_OK);
    atomic_store_explicit(&g_probe.commit_fail, 1u, memory_order_release);

    ASSERT_EQ(break_runtime_reload_request(reload, "good.bin", &request),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(wait_state(reload, request, BREAK_RUNTIME_RELOAD_VALIDATING),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_commit_owner(reload, 4u, &count),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(count, 1u);
    ASSERT_EQ(wait_terminal(reload, request, &state), BREAK_RUNTIME_OK);
    ASSERT_EQ(state, BREAK_RUNTIME_RELOAD_FAILED_KEEP_OLD);
    ASSERT_EQ(atomic_load_explicit(&g_probe.commit_calls,
                                   memory_order_acquire), 1u);
    ASSERT_EQ(g_probe.live_version, 0u); /* old data preserved */

    ASSERT_EQ(break_runtime_reload_shutdown(reload, 2000u), BREAK_RUNTIME_OK);
    break_runtime_reload_destroy(reload);
    vfs_destroy(vfs);
}

/* ------------------------------------------------------------------ */
/* reload: stale generation / cancel / timeout / OOM                   */
/* ------------------------------------------------------------------ */

TEST(reload_stale_generation_rejected)
{
    VFS *vfs = fixture_setup();
    BreakRuntimeReload *reload = NULL;
    BreakRuntimeReloadConfig config;
    BreakRuntimeReloadRequest first = 0u;
    BreakRuntimeReloadRequest second = 0u;
    BreakRuntimeReloadState state = BREAK_RUNTIME_RELOAD_LOADING;
    u32 count = 0u;
    ASSERT_NOT_NULL(vfs);

    probe_reset();
    config = probe_config(vfs);
    config.request_capacity = 1u; /* force slot reuse */
    ASSERT_EQ(break_runtime_reload_create(&config, &reload), BREAK_RUNTIME_OK);

    ASSERT_EQ(break_runtime_reload_request(reload, "good.bin", &first),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(wait_state(reload, first, BREAK_RUNTIME_RELOAD_VALIDATING),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_commit_owner(reload, 4u, &count),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(wait_terminal(reload, first, &state), BREAK_RUNTIME_OK);
    ASSERT_EQ(state, BREAK_RUNTIME_RELOAD_COMMITTED);

    /* The consumed handle is stale for every later operation. */
    ASSERT_EQ(break_runtime_reload_poll(reload, first, &state),
              BREAK_RUNTIME_STALE);
    ASSERT_EQ(break_runtime_reload_cancel(reload, first),
              BREAK_RUNTIME_STALE);

    /* Slot reuse produces a fresh generation: the old handle stays stale. */
    ASSERT_EQ(break_runtime_reload_request(reload, "good.bin", &second),
              BREAK_RUNTIME_OK);
    ASSERT_NEQ(second, first);
    ASSERT_EQ(break_runtime_reload_poll(reload, first, &state),
              BREAK_RUNTIME_STALE);
    ASSERT_EQ(break_runtime_reload_cancel(reload, second), BREAK_RUNTIME_OK);
    ASSERT_EQ(wait_terminal(reload, second, &state), BREAK_RUNTIME_OK);
    ASSERT_EQ(state, BREAK_RUNTIME_RELOAD_CANCELLED);

    ASSERT_EQ(break_runtime_reload_shutdown(reload, 2000u), BREAK_RUNTIME_OK);
    break_runtime_reload_destroy(reload);
    vfs_destroy(vfs);
}

TEST(reload_cancel_queued_exactly_once)
{
    VFS *vfs = fixture_setup();
    BreakRuntimeReload *reload = NULL;
    BreakRuntimeReloadConfig config;
    BreakRuntimeReloadRequest request = 0u;
    BreakRuntimeReloadState state = BREAK_RUNTIME_RELOAD_LOADING;
    BreakRuntimeReloadStats stats;
    ASSERT_NOT_NULL(vfs);

    probe_reset();
    atomic_store_explicit(&g_break_runtime_test_reload_popped, 0u,
                          memory_order_release);
    break_runtime_test_reload_set_gates(1u, 0u); /* park workers pre-claim */
    config = probe_config(vfs);
    ASSERT_EQ(break_runtime_reload_create(&config, &reload), BREAK_RUNTIME_OK);

    ASSERT_EQ(break_runtime_reload_request(reload, "good.bin", &request),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_cancel(reload, request), BREAK_RUNTIME_OK);
    /* The terminal state is delivered exactly once. */
    ASSERT_EQ(break_runtime_reload_poll(reload, request, &state),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(state, BREAK_RUNTIME_RELOAD_CANCELLED);
    ASSERT_EQ(break_runtime_reload_poll(reload, request, &state),
              BREAK_RUNTIME_STALE);
    /* The gated worker never claimed the request. */
    ASSERT_EQ(atomic_load_explicit(&g_break_runtime_test_reload_popped,
                                   memory_order_acquire), 0u);
    ASSERT_EQ(atomic_load_explicit(&g_probe.validate_calls,
                                   memory_order_acquire), 0u);
    ASSERT_EQ(break_runtime_reload_stats(reload, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.cancelled, 1u);
    ASSERT_EQ(stats.stale_drops, 0u);

    break_runtime_test_reload_set_gates(0u, 0u);
    ASSERT_EQ(break_runtime_reload_shutdown(reload, 2000u), BREAK_RUNTIME_OK);
    break_runtime_reload_destroy(reload);
    vfs_destroy(vfs);
}

TEST(reload_cancel_inflight_stale_drop)
{
    VFS *vfs = fixture_setup();
    BreakRuntimeReload *reload = NULL;
    BreakRuntimeReloadConfig config;
    BreakRuntimeReloadRequest request = 0u;
    BreakRuntimeReloadState state = BREAK_RUNTIME_RELOAD_LOADING;
    BreakRuntimeReloadStats stats;
    U64PredCtx ctx;
    ASSERT_NOT_NULL(vfs);

    probe_reset();
    atomic_store_explicit(&g_break_runtime_test_reload_popped, 0u,
                          memory_order_release);
    break_runtime_test_reload_set_gates(0u, 1u); /* park after claim, pre-read */
    config = probe_config(vfs);
    ASSERT_EQ(break_runtime_reload_create(&config, &reload), BREAK_RUNTIME_OK);

    ASSERT_EQ(break_runtime_reload_request(reload, "good.bin", &request),
              BREAK_RUNTIME_OK);
    spin_until_u64(&g_break_runtime_test_reload_popped, 1u);
    ASSERT_EQ(atomic_load_explicit(&g_break_runtime_test_reload_popped,
                                   memory_order_acquire), 1u);

    /* Cancel mid-load: CANCELLED is published immediately. */
    ASSERT_EQ(break_runtime_reload_cancel(reload, request), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_poll(reload, request, &state),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(state, BREAK_RUNTIME_RELOAD_CANCELLED);

    /* The worker's late result is dropped on the stale epoch: it never
     * publishes a second completion and never commits. */
    break_runtime_test_reload_set_gates(0u, 0u);
    ctx.target = 1u;
    spin_until_stats(reload, stats_stale_drops_eq, &ctx, &stats);
    ASSERT_EQ(stats.stale_drops, 1u);
    ASSERT_EQ(stats.committed, 0u);
    ASSERT_EQ(atomic_load_explicit(&g_probe.commit_calls,
                                   memory_order_acquire), 0u);
    ASSERT_EQ(g_probe.live_version, 0u);

    ASSERT_EQ(break_runtime_reload_shutdown(reload, 2000u), BREAK_RUNTIME_OK);
    break_runtime_reload_destroy(reload);
    vfs_destroy(vfs);
}

typedef struct CancelDuringCommitCtx {
    BreakRuntimeReload *reload;
    BreakRuntimeReloadRequest request;
    _Atomic u32 cancel_result;
} CancelDuringCommitCtx;

static void cancel_during_commit_worker(void *arg)
{
    CancelDuringCommitCtx *ctx = (CancelDuringCommitCtx *)arg;
    u32 guard = 0u;
    while (atomic_load_explicit(&g_probe.commit_entered,
                                memory_order_acquire) == 0u &&
           guard++ < 4000000u) {
        platform_thread_yield();
    }
    atomic_store_explicit(
        &ctx->cancel_result,
        (u32)break_runtime_reload_cancel(ctx->reload, ctx->request),
        memory_order_release);
    atomic_store_explicit(&g_probe.commit_release, 1u, memory_order_release);
}

TEST(reload_cancel_idempotent_and_inflight_commit_rejected)
{
    VFS *vfs = fixture_setup();
    BreakRuntimeReload *reload = NULL;
    BreakRuntimeReloadConfig config;
    BreakRuntimeReloadRequest request = 0u;
    BreakRuntimeReloadState state = BREAK_RUNTIME_RELOAD_LOADING;
    u32 count = 0u;
    ASSERT_NOT_NULL(vfs);

    probe_reset();
    config = probe_config(vfs);
    ASSERT_EQ(break_runtime_reload_create(&config, &reload), BREAK_RUNTIME_OK);

    /* Phase 1: idempotent cancel on an already-cancelled request. */
    ASSERT_EQ(break_runtime_reload_request(reload, "good.bin", &request),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_cancel(reload, request), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_cancel(reload, request), BREAK_RUNTIME_OK);
    ASSERT_EQ(wait_terminal(reload, request, &state), BREAK_RUNTIME_OK);
    ASSERT_EQ(state, BREAK_RUNTIME_RELOAD_CANCELLED);
    /* Consumed: the handle is stale now. */
    ASSERT_EQ(break_runtime_reload_cancel(reload, request),
              BREAK_RUNTIME_STALE);

    /* Phase 2: cancel while the owner thread is inside the commit hook is
     * REJECTED (the commit is already in flight). */
    atomic_store_explicit(&g_probe.commit_block, 1u, memory_order_release);
    ASSERT_EQ(break_runtime_reload_request(reload, "good2.bin", &request),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(wait_state(reload, request, BREAK_RUNTIME_RELOAD_VALIDATING),
              BREAK_RUNTIME_OK);
    {
        CancelDuringCommitCtx ctx;
        BreakRuntimeThreadConfig thread_cfg;
        BreakRuntimeThread *thread = NULL;
        ctx.reload = reload;
        ctx.request = request;
        atomic_store_explicit(&ctx.cancel_result, 0xFFFFFFFFu,
                              memory_order_release);
        memset(&thread_cfg, 0, sizeof(thread_cfg));
        thread_cfg.name = "cancel-probe";
        thread_cfg.fn = cancel_during_commit_worker;
        thread_cfg.arg = &ctx;
        ASSERT_EQ(break_runtime_thread_create(&thread_cfg, &thread),
                  BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_thread_start(thread), BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_reload_commit_owner(reload, 4u, &count),
                  BREAK_RUNTIME_OK);
        ASSERT_EQ(count, 1u);
        ASSERT_EQ(break_runtime_thread_stop(thread, 2000u), BREAK_RUNTIME_OK);
        break_runtime_thread_destroy(thread);
        ASSERT_EQ(atomic_load_explicit(&ctx.cancel_result,
                                       memory_order_acquire),
                  (u32)BREAK_RUNTIME_REJECTED);
    }
    ASSERT_EQ(wait_terminal(reload, request, &state), BREAK_RUNTIME_OK);
    ASSERT_EQ(state, BREAK_RUNTIME_RELOAD_COMMITTED);
    ASSERT_EQ(g_probe.live_version, 1u);

    /* Phase 3: cancel with a published non-CANCELLED terminal state is
     * REJECTED. */
    ASSERT_EQ(break_runtime_reload_request(reload, "good.bin", &request),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(wait_state(reload, request, BREAK_RUNTIME_RELOAD_VALIDATING),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_commit_owner(reload, 4u, &count),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(count, 1u);
    ASSERT_EQ(break_runtime_reload_cancel(reload, request),
              BREAK_RUNTIME_REJECTED);
    ASSERT_EQ(wait_terminal(reload, request, &state), BREAK_RUNTIME_OK);
    ASSERT_EQ(state, BREAK_RUNTIME_RELOAD_COMMITTED);

    ASSERT_EQ(break_runtime_reload_shutdown(reload, 2000u), BREAK_RUNTIME_OK);
    break_runtime_reload_destroy(reload);
    vfs_destroy(vfs);
}

TEST(reload_timeout)
{
    VFS *vfs = fixture_setup();
    BreakRuntimeReload *reload = NULL;
    BreakRuntimeReloadConfig config;
    BreakRuntimeReloadRequest request = 0u;
    BreakRuntimeReloadState state = BREAK_RUNTIME_RELOAD_LOADING;
    BreakRuntimeReloadStats stats;
    ASSERT_NOT_NULL(vfs);

    probe_reset();
    atomic_store_explicit(&g_break_runtime_test_reload_popped, 0u,
                          memory_order_release);
    break_runtime_test_reload_set_gates(0u, 1u); /* park pre-read */
    config = probe_config(vfs);
    config.request_timeout_ms = 1u; /* expires while the worker is parked */
    ASSERT_EQ(break_runtime_reload_create(&config, &reload), BREAK_RUNTIME_OK);

    ASSERT_EQ(break_runtime_reload_request(reload, "good.bin", &request),
              BREAK_RUNTIME_OK);
    spin_until_u64(&g_break_runtime_test_reload_popped, 1u);
    ASSERT_EQ(atomic_load_explicit(&g_break_runtime_test_reload_popped,
                                   memory_order_acquire), 1u);
    test_sleep_ms(10); /* let the 1ms processing deadline pass */
    break_runtime_test_reload_set_gates(0u, 0u);

    ASSERT_EQ(wait_terminal(reload, request, &state), BREAK_RUNTIME_OK);
    ASSERT_EQ(state, BREAK_RUNTIME_RELOAD_TIMEOUT);
    ASSERT_EQ(atomic_load_explicit(&g_probe.commit_calls,
                                   memory_order_acquire), 0u);
    ASSERT_EQ(g_probe.live_version, 0u);
    ASSERT_EQ(break_runtime_reload_stats(reload, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.timed_out, 1u);

    ASSERT_EQ(break_runtime_reload_shutdown(reload, 2000u), BREAK_RUNTIME_OK);
    break_runtime_reload_destroy(reload);
    vfs_destroy(vfs);
}

TEST(reload_staging_oom_state)
{
    VFS *vfs = fixture_setup();
    BreakRuntimeReload *reload = NULL;
    BreakRuntimeReloadConfig config;
    BreakRuntimeReloadRequest request = 0u;
    BreakRuntimeReloadState state = BREAK_RUNTIME_RELOAD_LOADING;
    BreakRuntimeReloadStats stats;
    u32 count = 0u;
    ASSERT_NOT_NULL(vfs);

    probe_reset();
    config = probe_config(vfs);
    ASSERT_EQ(break_runtime_reload_create(&config, &reload), BREAK_RUNTIME_OK);

    /* The worker-side staging copy fails: the request reaches the OOM
     * terminal state and the old version stays live. */
    break_runtime_test_set_alloc_budget(0u);
    ASSERT_EQ(break_runtime_reload_request(reload, "good.bin", &request),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(wait_terminal(reload, request, &state), BREAK_RUNTIME_OK);
    ASSERT_EQ(state, BREAK_RUNTIME_RELOAD_OOM);
    break_runtime_test_set_alloc_budget(BREAK_RUNTIME_TEST_ALLOC_DISABLED);
    ASSERT_EQ(atomic_load_explicit(&g_probe.commit_calls,
                                   memory_order_acquire), 0u);
    ASSERT_EQ(g_probe.live_version, 0u);
    ASSERT_EQ(break_runtime_reload_stats(reload, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.oom, 1u);

    /* The facade is fully functional after the injected failure. */
    ASSERT_EQ(break_runtime_reload_request(reload, "good.bin", &request),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(wait_state(reload, request, BREAK_RUNTIME_RELOAD_VALIDATING),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_commit_owner(reload, 4u, &count),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(count, 1u);
    ASSERT_EQ(wait_terminal(reload, request, &state), BREAK_RUNTIME_OK);
    ASSERT_EQ(state, BREAK_RUNTIME_RELOAD_COMMITTED);
    ASSERT_EQ(g_probe.live_version, 1u);

    ASSERT_EQ(break_runtime_reload_shutdown(reload, 2000u), BREAK_RUNTIME_OK);
    break_runtime_reload_destroy(reload);
    vfs_destroy(vfs);
}

/* ------------------------------------------------------------------ */
/* reload: overload lanes                                              */
/* ------------------------------------------------------------------ */

TEST(reload_request_queue_overload)
{
    VFS *vfs = fixture_setup();
    BreakRuntimeReload *reload = NULL;
    BreakRuntimeReloadConfig config;
    BreakRuntimeReloadRequest requests[4] = {0u, 0u, 0u, 0u};
    BreakRuntimeReloadRequest extra = 0u;
    BreakRuntimeReloadRequest merged = 0u;
    BreakRuntimeReloadState state = BREAK_RUNTIME_RELOAD_LOADING;
    BreakRuntimeReloadStats stats;
    char path[32];
    u32 i;
    u32 count = 0u;
    ASSERT_NOT_NULL(vfs);

    probe_reset();
    break_runtime_test_reload_set_gates(1u, 0u); /* nothing drains */
    config = probe_config(vfs);
    config.request_capacity = 4u;
    ASSERT_EQ(break_runtime_reload_create(&config, &reload), BREAK_RUNTIME_OK);

    for (i = 0u; i < 4u; i++) {
        snprintf(path, sizeof(path), "ovl%u.bin", i);
        ASSERT_EQ(break_runtime_reload_request(reload, path, &requests[i]),
                  BREAK_RUNTIME_OK);
        ASSERT_NEQ(requests[i], 0u);
    }
    /* Live-count gate: a fifth distinct path is a non-blocking OVERLOAD. */
    ASSERT_EQ(break_runtime_reload_request(reload, "missing5.bin", &extra),
              BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(extra, 0u);
    /* A same-path request still merges (coalescing beats the full queue). */
    ASSERT_EQ(break_runtime_reload_request(reload, "ovl0.bin", &merged),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(merged, requests[0]);
    ASSERT_EQ(break_runtime_reload_stats(reload, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.request_overloads, 1u);
    ASSERT_EQ(stats.merged, 1u);
    ASSERT_EQ(stats.active, 4u);

    /* Physical-ring gate: cancelling one QUEUED request frees its live slot
     * (active drops) but its ring slot is reclaimed only at claim/drain, so a
     * new distinct request is STILL rejected (non-blocking OVERLOAD). */
    ASSERT_EQ(break_runtime_reload_cancel(reload, requests[3]),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_stats(reload, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.active, 3u);
    ASSERT_EQ(break_runtime_reload_request(reload, "missing5.bin", &extra),
              BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(break_runtime_reload_stats(reload, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.request_overloads, 2u);

    /* Ungate: the dead ring entry is skipped at claim, the three live
     * requests load and validate. */
    break_runtime_test_reload_set_gates(0u, 0u);
    for (i = 0u; i < 3u; i++) {
        ASSERT_EQ(wait_state(reload, requests[i],
                             BREAK_RUNTIME_RELOAD_VALIDATING),
                  BREAK_RUNTIME_OK);
    }
    ASSERT_EQ(break_runtime_reload_commit_owner(reload, 8u, &count),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(count, 3u);
    for (i = 0u; i < 3u; i++) {
        ASSERT_EQ(wait_terminal(reload, requests[i], &state),
                  BREAK_RUNTIME_OK);
        ASSERT_EQ(state, BREAK_RUNTIME_RELOAD_COMMITTED);
    }
    ASSERT_EQ(wait_terminal(reload, requests[3], &state), BREAK_RUNTIME_OK);
    ASSERT_EQ(state, BREAK_RUNTIME_RELOAD_CANCELLED);
    ASSERT_EQ(break_runtime_reload_stats(reload, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.active, 0u);
    ASSERT_EQ(stats.committed, 3u);

    ASSERT_EQ(break_runtime_reload_shutdown(reload, 2000u), BREAK_RUNTIME_OK);
    break_runtime_reload_destroy(reload);
    vfs_destroy(vfs);
}

TEST(reload_commit_queue_overload)
{
    VFS *vfs = fixture_setup();
    BreakRuntimeReload *reload = NULL;
    BreakRuntimeReloadConfig config;
    BreakRuntimeReloadRequest req_a = 0u;
    BreakRuntimeReloadRequest req_b = 0u;
    BreakRuntimeReloadState state_a = BREAK_RUNTIME_RELOAD_LOADING;
    BreakRuntimeReloadState state_b = BREAK_RUNTIME_RELOAD_LOADING;
    BreakRuntimeReloadStats stats;
    U64PredCtx ctx;
    u32 count = 0u;
    ASSERT_NOT_NULL(vfs);

    probe_reset();
    config = probe_config(vfs);
    config.request_capacity = 2u;
    config.worker_count = 2u;
    config.commit_capacity = 1u; /* only one staged commit fits */
    ASSERT_EQ(break_runtime_reload_create(&config, &reload), BREAK_RUNTIME_OK);

    ASSERT_EQ(break_runtime_reload_request(reload, "good.bin", &req_a),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_request(reload, "good2.bin", &req_b),
              BREAK_RUNTIME_OK);

    /* Both workers validate; exactly one commit command fits the bounded
     * queue. The loser finalizes FAILED_KEEP_OLD (old version preserved)
     * instead of blocking the worker or overwriting a live entry. */
    ctx.target = 1u;
    spin_until_stats(reload, stats_commit_overloads_eq, &ctx, &stats);
    ASSERT_EQ(stats.commit_overloads, 1u);

    ASSERT_EQ(break_runtime_reload_commit_owner(reload, 4u, &count),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(count, 1u);

    ASSERT_EQ(wait_terminal(reload, req_a, &state_a), BREAK_RUNTIME_OK);
    ASSERT_EQ(wait_terminal(reload, req_b, &state_b), BREAK_RUNTIME_OK);
    /* Exactly one committed; the other preserved the old data. */
    ASSERT_TRUE((state_a == BREAK_RUNTIME_RELOAD_COMMITTED &&
                 state_b == BREAK_RUNTIME_RELOAD_FAILED_KEEP_OLD) ||
                (state_b == BREAK_RUNTIME_RELOAD_COMMITTED &&
                 state_a == BREAK_RUNTIME_RELOAD_FAILED_KEEP_OLD));
    ASSERT_EQ(g_probe.live_version, 1u);
    ASSERT_EQ(break_runtime_reload_stats(reload, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.committed, 1u);
    ASSERT_EQ(stats.failed_keep_old, 1u);

    ASSERT_EQ(break_runtime_reload_shutdown(reload, 2000u), BREAK_RUNTIME_OK);
    break_runtime_reload_destroy(reload);
    vfs_destroy(vfs);
}

/* ------------------------------------------------------------------ */
/* reload: shutdown                                                    */
/* ------------------------------------------------------------------ */

TEST(reload_shutdown_cancels_pending_and_closes_admission)
{
    VFS *vfs = fixture_setup();
    BreakRuntimeReload *reload = NULL;
    BreakRuntimeReloadConfig config;
    BreakRuntimeReloadRequest req_a = 0u;
    BreakRuntimeReloadRequest req_b = 0u;
    BreakRuntimeReloadState state = BREAK_RUNTIME_RELOAD_LOADING;
    BreakRuntimeReloadStats stats;
    ASSERT_NOT_NULL(vfs);

    probe_reset();
    break_runtime_test_reload_set_gates(1u, 0u); /* park pre-claim */
    config = probe_config(vfs);
    ASSERT_EQ(break_runtime_reload_create(&config, &reload), BREAK_RUNTIME_OK);

    ASSERT_EQ(break_runtime_reload_request(reload, "good.bin", &req_a),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_request(reload, "good2.bin", &req_b),
              BREAK_RUNTIME_OK);

    /* The gate park loop observes the exit flag, so shutdown drains
     * deterministically even with the gate still armed. */
    ASSERT_EQ(break_runtime_reload_shutdown(reload, 2000u), BREAK_RUNTIME_OK);
    break_runtime_test_reload_set_gates(0u, 0u);

    /* Both pending requests were finalized CANCELLED and stay pollable. */
    ASSERT_EQ(break_runtime_reload_poll(reload, req_a, &state),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(state, BREAK_RUNTIME_RELOAD_CANCELLED);
    ASSERT_EQ(break_runtime_reload_poll(reload, req_b, &state),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(state, BREAK_RUNTIME_RELOAD_CANCELLED);
    ASSERT_EQ(break_runtime_reload_stats(reload, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.cancelled, 2u);

    /* Admission is closed; shutdown is idempotent. */
    ASSERT_EQ(break_runtime_reload_request(reload, "good.bin", &req_a),
              BREAK_RUNTIME_CLOSED);
    ASSERT_EQ(break_runtime_reload_notify_file_event(reload, "good.bin"),
              BREAK_RUNTIME_CLOSED);
    ASSERT_EQ(break_runtime_reload_shutdown(reload, 2000u), BREAK_RUNTIME_OK);
    break_runtime_reload_destroy(reload);
    vfs_destroy(vfs);
}

TEST(reload_shutdown_timeout_retains_live_ownership)
{
    VFS *vfs = fixture_setup();
    BreakRuntimeReload *reload = NULL;
    BreakRuntimeReloadConfig config;
    BreakRuntimeReloadRequest request = 0u;
    BreakRuntimeReloadState state = BREAK_RUNTIME_RELOAD_LOADING;
    BreakRuntimeReloadStats stats;
    U64PredCtx ctx;
    ASSERT_NOT_NULL(vfs);

    probe_reset();
    atomic_store_explicit(&g_break_runtime_test_reload_popped, 0u,
                          memory_order_release);
    break_runtime_test_reload_set_gates(0u, 1u); /* park pre-read, ignores exit */
    config = probe_config(vfs);
    ASSERT_EQ(break_runtime_reload_create(&config, &reload), BREAK_RUNTIME_OK);

    ASSERT_EQ(break_runtime_reload_request(reload, "good.bin", &request),
              BREAK_RUNTIME_OK);
    spin_until_u64(&g_break_runtime_test_reload_popped, 1u);
    ASSERT_EQ(atomic_load_explicit(&g_break_runtime_test_reload_popped,
                                   memory_order_acquire), 1u);

    /* The parked worker cannot exit: bounded shutdown times out and RETAINS
     * live ownership (nothing freed; the request was still finalized
     * CANCELLED by the drain). */
    ASSERT_EQ(break_runtime_reload_shutdown(reload, 100u),
              BREAK_RUNTIME_TIMEOUT);
    ASSERT_EQ(break_runtime_reload_poll(reload, request, &state),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(state, BREAK_RUNTIME_RELOAD_CANCELLED);
    ASSERT_EQ(break_runtime_reload_request(reload, "good2.bin", &request),
              BREAK_RUNTIME_CLOSED);

    /* Release the worker: its late result drops on the stale epoch, and a
     * retried shutdown resumes and completes. */
    break_runtime_test_reload_set_gates(0u, 0u);
    ctx.target = 1u;
    spin_until_stats(reload, stats_stale_drops_eq, &ctx, &stats);
    ASSERT_EQ(stats.stale_drops, 1u);
    ASSERT_EQ(break_runtime_reload_shutdown(reload, 2000u), BREAK_RUNTIME_OK);
    break_runtime_reload_destroy(reload);
    vfs_destroy(vfs);
}

TEST(reload_events_pump_defers_while_inflight)
{
    VFS *vfs = fixture_setup();
    BreakRuntimeReload *reload = NULL;
    BreakRuntimeReloadConfig config;
    BreakRuntimeReloadRequest first = 0u;
    BreakRuntimeReloadState state = BREAK_RUNTIME_RELOAD_LOADING;
    BreakRuntimeReloadStats stats;
    u32 count = 0xFFFFFFFFu;
    ASSERT_NOT_NULL(vfs);

    probe_reset();
    atomic_store_explicit(&g_break_runtime_test_reload_popped, 0u,
                          memory_order_release);
    break_runtime_test_reload_set_gates(0u, 1u); /* park pre-read */
    config = probe_config(vfs);
    ASSERT_EQ(break_runtime_reload_create(&config, &reload), BREAK_RUNTIME_OK);

    ASSERT_EQ(break_runtime_reload_request(reload, "good.bin", &first),
              BREAK_RUNTIME_OK);
    spin_until_u64(&g_break_runtime_test_reload_popped, 1u);

    /* A file event for the in-flight asset is kept, not dropped: the owner
     * pump defers it (a burst during LOADING produces a follow-up reload of
     * the latest content instead of writing new bytes into old staging). */
    ASSERT_EQ(break_runtime_reload_notify_file_event(reload, "good.bin"),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_reload_pump_events(reload, 4u, &count),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(count, 0u);
    ASSERT_EQ(break_runtime_reload_stats(reload, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.events_deferred, 1u);
    ASSERT_EQ(stats.requested, 1u);

    /* Finish the in-flight request (cancel), then the deferred hint starts a
     * fresh request on the next pump. */
    ASSERT_EQ(break_runtime_reload_cancel(reload, first), BREAK_RUNTIME_OK);
    ASSERT_EQ(wait_terminal(reload, first, &state), BREAK_RUNTIME_OK);
    ASSERT_EQ(state, BREAK_RUNTIME_RELOAD_CANCELLED);
    break_runtime_test_reload_set_gates(0u, 0u);

    ASSERT_EQ(break_runtime_reload_pump_events(reload, 4u, &count),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(count, 1u);
    ASSERT_EQ(break_runtime_reload_stats(reload, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.requested, 2u);

    /* The follow-up request completes the full pipeline. */
    {
        BreakRuntimeReloadRequest second = 0u;
        /* The pump owns the handle; find it via a fresh same-path merge is
         * impossible (the pump request is live). Request the same path to
         * obtain the merged handle. */
        ASSERT_EQ(break_runtime_reload_request(reload, "good.bin", &second),
                  BREAK_RUNTIME_OK);
        ASSERT_EQ(wait_state(reload, second, BREAK_RUNTIME_RELOAD_VALIDATING),
                  BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_reload_commit_owner(reload, 4u, &count),
                  BREAK_RUNTIME_OK);
        ASSERT_EQ(count, 1u);
        ASSERT_EQ(wait_terminal(reload, second, &state), BREAK_RUNTIME_OK);
        ASSERT_EQ(state, BREAK_RUNTIME_RELOAD_COMMITTED);
        ASSERT_EQ(g_probe.live_version, 1u);
    }

    ASSERT_EQ(break_runtime_reload_shutdown(reload, 2000u), BREAK_RUNTIME_OK);
    break_runtime_reload_destroy(reload);
    vfs_destroy(vfs);
}

typedef struct OwnerEnforceCtx {
    BreakRuntimeReload *reload;
    _Atomic u32 commit_result;
    _Atomic u32 pump_result;
} OwnerEnforceCtx;

static void owner_enforce_worker(void *arg)
{
    OwnerEnforceCtx *ctx = (OwnerEnforceCtx *)arg;
    u32 count = 0u;
    atomic_store_explicit(
        &ctx->commit_result,
        (u32)break_runtime_reload_commit_owner(ctx->reload, 4u, &count),
        memory_order_release);
    atomic_store_explicit(
        &ctx->pump_result,
        (u32)break_runtime_reload_pump_events(ctx->reload, 4u, &count),
        memory_order_release);
}

TEST(reload_owner_thread_enforced)
{
    VFS *vfs = fixture_setup();
    BreakRuntimeReload *reload = NULL;
    BreakRuntimeReloadConfig config;
    u32 count = 0u;
    ASSERT_NOT_NULL(vfs);

    probe_reset();
    config = probe_config(vfs);
    ASSERT_EQ(break_runtime_reload_create(&config, &reload), BREAK_RUNTIME_OK);

    /* A non-owner thread may not run the owner-only pumps. */
    {
        OwnerEnforceCtx ctx;
        BreakRuntimeThreadConfig thread_cfg;
        BreakRuntimeThread *thread = NULL;
        ctx.reload = reload;
        atomic_store_explicit(&ctx.commit_result, 0xFFFFFFFFu,
                              memory_order_release);
        atomic_store_explicit(&ctx.pump_result, 0xFFFFFFFFu,
                              memory_order_release);
        memset(&thread_cfg, 0, sizeof(thread_cfg));
        thread_cfg.name = "owner-probe";
        thread_cfg.fn = owner_enforce_worker;
        thread_cfg.arg = &ctx;
        ASSERT_EQ(break_runtime_thread_create(&thread_cfg, &thread),
                  BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_thread_start(thread), BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_thread_stop(thread, 2000u), BREAK_RUNTIME_OK);
        break_runtime_thread_destroy(thread);
        ASSERT_EQ(atomic_load_explicit(&ctx.commit_result,
                                       memory_order_acquire),
                  (u32)BREAK_RUNTIME_REJECTED);
        ASSERT_EQ(atomic_load_explicit(&ctx.pump_result,
                                       memory_order_acquire),
                  (u32)BREAK_RUNTIME_REJECTED);
    }

    /* The owner thread runs both pumps fine (nothing queued). */
    ASSERT_EQ(break_runtime_reload_commit_owner(reload, 4u, &count),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(count, 0u);
    ASSERT_EQ(break_runtime_reload_pump_events(reload, 4u, &count),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(count, 0u);

    ASSERT_EQ(break_runtime_reload_shutdown(reload, 2000u), BREAK_RUNTIME_OK);
    break_runtime_reload_destroy(reload);
    vfs_destroy(vfs);
}

#if !defined(_WIN32)
TEST(reload_destroy_requires_shutdown_aborts)
{
    VFS *vfs = fixture_setup();
    ASSERT_NOT_NULL(vfs);

    /* fork child: create a facade and destroy it WITHOUT shutdown — a
     * contract violation the test build fail-stops on. */
    fflush(stdout);
    {
        pid_t pid = fork();
        if (pid == 0) {
            BreakRuntimeReloadConfig config;
            BreakRuntimeReload *reload = NULL;
            probe_reset();
            config = probe_config(vfs);
            if (break_runtime_reload_create(&config, &reload) ==
                BREAK_RUNTIME_OK) {
                break_runtime_reload_destroy(reload); /* must abort */
            }
            _exit(42); /* reached only if the contract was NOT enforced */
        }
        {
            int status = 0;
            ASSERT_TRUE(pid > 0);
            ASSERT_EQ(waitpid(pid, &status, 0), pid);
            ASSERT_TRUE(WIFSIGNALED(status)); /* SIGABRT expected */
        }
    }
    vfs_destroy(vfs);
}
#endif

/* ------------------------------------------------------------------ */
/* profiler bridge                                                     */
/* ------------------------------------------------------------------ */

TEST(profiler_create_validation_and_oom)
{
    BreakRuntimeProfiler *profiler = NULL;
    BreakRuntimeProfilerConfig config;
    u32 budget;
    u32 first_success = 0xFFFFFFFFu;

    ASSERT_EQ(break_runtime_profiler_create(NULL, NULL), BREAK_RUNTIME_INVALID);
    memset(&config, 0, sizeof(config));
    config.event_capacity = BREAK_RUNTIME_PROFILER_MAX_EVENT_CAPACITY + 1u;
    ASSERT_EQ(break_runtime_profiler_create(&config, &profiler),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(profiler, NULL);
    memset(&config, 0, sizeof(config));
    config.window_capacity = BREAK_RUNTIME_PROFILER_MAX_WINDOW_CAPACITY + 1u;
    ASSERT_EQ(break_runtime_profiler_create(&config, &profiler),
              BREAK_RUNTIME_INVALID);

    /* Allocation failure injection on every create alloc path. */
    memset(&config, 0, sizeof(config));
    for (budget = 0u; budget < 64u; budget++) {
        break_runtime_test_set_alloc_budget(budget);
        if (break_runtime_profiler_create(&config, &profiler) ==
            BREAK_RUNTIME_OK) {
            first_success = budget;
            break_runtime_test_set_alloc_budget(
                BREAK_RUNTIME_TEST_ALLOC_DISABLED);
            break;
        }
        ASSERT_EQ(profiler, NULL);
    }
    break_runtime_test_set_alloc_budget(BREAK_RUNTIME_TEST_ALLOC_DISABLED);
    ASSERT_TRUE(first_success != 0xFFFFFFFFu);
    ASSERT_TRUE(first_success > 0u);
    break_runtime_profiler_destroy(profiler);
}

TEST(profiler_record_collect_export_roundtrip)
{
    BreakRuntimeProfiler *profiler = NULL;
    BreakRuntimeProfilerStats stats;
    ProfilerMetaInstant meta[8];
    u32 count = 0u;
    u32 meta_count = 0u;
    u32 i;
    char trace_path[640];
    FILE *fp;
    char content[8192];
    usize content_size;
    int found_alpha = 0;

    ASSERT_EQ(break_runtime_profiler_create(NULL, &profiler), BREAK_RUNTIME_OK);

    ASSERT_EQ(break_runtime_profiler_record(profiler, "alpha"),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_profiler_record(profiler, "beta"),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_profiler_record(profiler, "gamma"),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_profiler_stats(profiler, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.recorded, 3u);

    ASSERT_EQ(break_runtime_profiler_collect(profiler, 8u, &count),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(count, 3u);
    ASSERT_EQ(break_runtime_profiler_stats(profiler, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.collected, 3u);
    ASSERT_EQ(stats.window_count, 3u);

    ASSERT_EQ(break_runtime_profiler_export_meta(profiler, meta, 8u,
                                                 &meta_count),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(meta_count, 3u);
    for (i = 0u; i < meta_count; i++) {
        ASSERT_NOT_NULL(meta[i].key);
        ASSERT_NOT_NULL(meta[i].value);
        ASSERT_TRUE(strstr(meta[i].value, "tid=") != NULL);
        if (strcmp(meta[i].key, "alpha") == 0) {
            found_alpha = 1;
        }
    }
    ASSERT_TRUE(found_alpha);

    /* Collector handoff over the EXISTING profiler.c: record one real frame
     * through the legacy API and export the bridge's meta with it. */
    profiler_set_enabled(true);
    profiler_begin_frame();
    profiler_push("test.runtime.region");
    profiler_pop();
    profiler_end_frame();
    ASSERT_NOT_NULL(profiler_last_frame());
    snprintf(trace_path, sizeof(trace_path), "%s/runtime_profiler_trace.json",
             g_reload_dir[0] != '\0' ? g_reload_dir : ".");
    test_tmp(trace_path, sizeof(trace_path), "rtprof_trace");
    strcat(trace_path, ".json");
    ASSERT_TRUE(profiler_export_chrome_trace(trace_path,
                                             profiler_last_frame(), NULL, 0u,
                                             meta, meta_count));
    profiler_set_enabled(false);

    fp = fopen(trace_path, "rb");
    ASSERT_NOT_NULL(fp);
    content_size = fread(content, 1, sizeof(content) - 1u, fp);
    fclose(fp);
    ASSERT_TRUE(content_size > 0u);
    content[content_size] = '\0';
    ASSERT_TRUE(strstr(content, "\"alpha\"") != NULL);
    ASSERT_TRUE(strstr(content, "test.runtime.region") != NULL);
    remove(trace_path);

    break_runtime_profiler_close(profiler);
    break_runtime_profiler_destroy(profiler);
}

TEST(profiler_record_overload_never_blocks)
{
    BreakRuntimeProfiler *profiler = NULL;
    BreakRuntimeProfilerConfig config;
    BreakRuntimeProfilerStats stats;
    u32 count = 0u;
    u32 i;
    char name[16];

    memset(&config, 0, sizeof(config));
    config.event_capacity = 4u;
    ASSERT_EQ(break_runtime_profiler_create(&config, &profiler),
              BREAK_RUNTIME_OK);

    for (i = 0u; i < 4u; i++) {
        snprintf(name, sizeof(name), "event%u", i);
        ASSERT_EQ(break_runtime_profiler_record(profiler, name),
                  BREAK_RUNTIME_OK);
    }
    /* Full ring: bounded non-blocking OVERLOAD, counted, nothing queued. */
    ASSERT_EQ(break_runtime_profiler_record(profiler, "overflow"),
              BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(break_runtime_profiler_stats(profiler, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.recorded, 4u);
    ASSERT_EQ(stats.overload_drops, 1u);
    ASSERT_EQ(stats.high_water, 4u);

    ASSERT_EQ(break_runtime_profiler_collect(profiler, 8u, &count),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(count, 4u);

    break_runtime_profiler_close(profiler);
    break_runtime_profiler_destroy(profiler);
}

TEST(profiler_name_copied_owned)
{
    BreakRuntimeProfiler *profiler = NULL;
    ProfilerMetaInstant meta[4];
    u32 count = 0u;
    u32 meta_count = 0u;
    char name[64];
    char long_name[96];

    ASSERT_EQ(break_runtime_profiler_create(NULL, &profiler), BREAK_RUNTIME_OK);

    /* The record copies the name: mutating the caller's buffer afterwards
     * must not change the queued event. */
    snprintf(name, sizeof(name), "mutable_name");
    ASSERT_EQ(break_runtime_profiler_record(profiler, name), BREAK_RUNTIME_OK);
    snprintf(name, sizeof(name), "changed_after");

    ASSERT_EQ(break_runtime_profiler_collect(profiler, 4u, &count),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(count, 1u);
    ASSERT_EQ(break_runtime_profiler_export_meta(profiler, meta, 4u,
                                                 &meta_count),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(meta_count, 1u);
    ASSERT_STR_EQ(meta[0].key, "mutable_name");

    /* Over-long names are rejected, never truncated. */
    memset(long_name, 'n', sizeof(long_name) - 1u);
    long_name[sizeof(long_name) - 1u] = '\0';
    ASSERT_EQ(break_runtime_profiler_record(profiler, long_name),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_profiler_record(profiler, NULL),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_profiler_record(profiler, ""),
              BREAK_RUNTIME_INVALID);

    break_runtime_profiler_close(profiler);
    break_runtime_profiler_destroy(profiler);
}

typedef struct ProfilerProducerCtx {
    BreakRuntimeProfiler *profiler;
    _Atomic u32 record_failures;
    u32 events_per_thread;
} ProfilerProducerCtx;

static void profiler_producer_worker(void *arg)
{
    ProfilerProducerCtx *ctx = (ProfilerProducerCtx *)arg;
    u32 i;
    for (i = 0u; i < ctx->events_per_thread; i++) {
        if (break_runtime_profiler_record(ctx->profiler, "worker.event") !=
            BREAK_RUNTIME_OK) {
            atomic_fetch_add_explicit(&ctx->record_failures, 1u,
                                      memory_order_acq_rel);
        }
    }
}

TEST(profiler_multithreaded_handoff)
{
    BreakRuntimeProfiler *profiler = NULL;
    BreakRuntimeProfilerConfig config;
    BreakRuntimeProfilerStats stats;
    ProfilerProducerCtx ctx;
    BreakRuntimeThread *threads[4] = {NULL, NULL, NULL, NULL};
    u32 count = 0u;
    u32 total = 0u;
    u32 i;
    u32 distinct_tids = 0u;
    u32 tid_seen[64];
    u32 tid_seen_count = 0u;

    memset(&config, 0, sizeof(config));
    config.event_capacity = 4096u;
    config.window_capacity = 1024u;
    ASSERT_EQ(break_runtime_profiler_create(&config, &profiler),
              BREAK_RUNTIME_OK);

    memset(&ctx, 0, sizeof(ctx));
    ctx.profiler = profiler;
    ctx.events_per_thread = 250u;

    /* Four producer threads record concurrently; record() never blocks. */
    for (i = 0u; i < 4u; i++) {
        BreakRuntimeThreadConfig thread_cfg;
        char thread_name[BREAK_RUNTIME_THREAD_NAME_CAPACITY];
        snprintf(thread_name, sizeof(thread_name), "prof-prod-%u", i);
        memset(&thread_cfg, 0, sizeof(thread_cfg));
        thread_cfg.name = thread_name;
        thread_cfg.fn = profiler_producer_worker;
        thread_cfg.arg = &ctx;
        ASSERT_EQ(break_runtime_thread_create(&thread_cfg, &threads[i]),
                  BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_thread_start(threads[i]), BREAK_RUNTIME_OK);
    }
    for (i = 0u; i < 4u; i++) {
        ASSERT_EQ(break_runtime_thread_stop(threads[i], 5000u),
                  BREAK_RUNTIME_OK);
        break_runtime_thread_destroy(threads[i]);
    }
    ASSERT_EQ(atomic_load_explicit(&ctx.record_failures,
                                   memory_order_acquire), 0u);

    /* The collector drains all 1000 events on the owner thread. */
    ASSERT_EQ(break_runtime_profiler_collect(profiler, 2000u, &count),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(count, 1000u);
    ASSERT_EQ(break_runtime_profiler_stats(profiler, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.recorded, 1000u);
    ASSERT_EQ(stats.collected, 1000u);
    ASSERT_EQ(stats.window_drops, 0u);
    ASSERT_EQ(stats.window_count, 1000u);

    /* Per-thread identity was captured at record time: the four producers
     * show at least two distinct profiler tids (they never register
     * explicitly; profiler_current_tid() lazily assigns per thread). */
    {
        ProfilerMetaInstant *meta =
            (ProfilerMetaInstant *)malloc(1000u * sizeof(*meta));
        ASSERT_NOT_NULL(meta);
        ASSERT_EQ(break_runtime_profiler_export_meta(profiler, meta, 1000u,
                                                     &total),
                  BREAK_RUNTIME_OK);
        ASSERT_EQ(total, 1000u);
        memset(tid_seen, 0, sizeof(tid_seen));
        for (i = 0u; i < total; i++) {
            /* value format: "tid=N ts=US" */
            u32 tid = (u32)atoi(meta[i].value + 4u);
            u32 j;
            int seen = 0;
            for (j = 0u; j < tid_seen_count; j++) {
                if (tid_seen[j] == tid) {
                    seen = 1;
                    break;
                }
            }
            if (!seen && tid_seen_count < 64u) {
                tid_seen[tid_seen_count++] = tid;
            }
        }
        distinct_tids = tid_seen_count;
        free(meta);
    }
    ASSERT_TRUE(distinct_tids >= 2u);

    break_runtime_profiler_close(profiler);
    break_runtime_profiler_destroy(profiler);
}

TEST(profiler_close_drains_then_closed)
{
    BreakRuntimeProfiler *profiler = NULL;
    u32 count = 0u;

    ASSERT_EQ(break_runtime_profiler_create(NULL, &profiler), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_profiler_record(profiler, "one"), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_profiler_record(profiler, "two"), BREAK_RUNTIME_OK);

    break_runtime_profiler_close(profiler);
    break_runtime_profiler_close(profiler); /* idempotent */
    ASSERT_EQ(break_runtime_profiler_record(profiler, "three"),
              BREAK_RUNTIME_CLOSED);

    /* A closed bridge still drains the remainder... */
    ASSERT_EQ(break_runtime_profiler_collect(profiler, 8u, &count),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(count, 2u);
    /* ...and reports CLOSED once drained. */
    ASSERT_EQ(break_runtime_profiler_collect(profiler, 8u, &count),
              BREAK_RUNTIME_CLOSED);
    ASSERT_EQ(count, 0u);

    break_runtime_profiler_destroy(profiler);
}

TEST(profiler_window_bounded_drop)
{
    BreakRuntimeProfiler *profiler = NULL;
    BreakRuntimeProfilerConfig config;
    BreakRuntimeProfilerStats stats;
    u32 count = 0u;
    u32 i;
    char name[16];

    memset(&config, 0, sizeof(config));
    config.event_capacity = 8u;
    config.window_capacity = 2u;
    ASSERT_EQ(break_runtime_profiler_create(&config, &profiler),
              BREAK_RUNTIME_OK);

    for (i = 0u; i < 4u; i++) {
        snprintf(name, sizeof(name), "w%u", i);
        ASSERT_EQ(break_runtime_profiler_record(profiler, name),
                  BREAK_RUNTIME_OK);
    }
    /* The presentation window never overwrites a live entry: overflow is
     * dropped and counted. */
    ASSERT_EQ(break_runtime_profiler_collect(profiler, 8u, &count),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(count, 4u);
    ASSERT_EQ(break_runtime_profiler_stats(profiler, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.window_count, 2u);
    ASSERT_EQ(stats.window_drops, 2u);

    break_runtime_profiler_close(profiler);
    break_runtime_profiler_destroy(profiler);
}

typedef struct ProfilerEnforceArg {
    BreakRuntimeProfiler *profiler;
    _Atomic u32 *collect_result;
    _Atomic u32 *export_result;
} ProfilerEnforceArg;

static void profiler_enforce_worker(void *arg)
{
    ProfilerEnforceArg *enforce = (ProfilerEnforceArg *)arg;
    ProfilerMetaInstant meta[4];
    u32 count = 0u;
    u32 meta_count = 0u;
    atomic_store_explicit(
        enforce->collect_result,
        (u32)break_runtime_profiler_collect(enforce->profiler, 4u, &count),
        memory_order_release);
    atomic_store_explicit(
        enforce->export_result,
        (u32)break_runtime_profiler_export_meta(enforce->profiler, meta, 4u,
                                                &meta_count),
        memory_order_release);
}

TEST(profiler_collect_owner_enforced)
{
    BreakRuntimeProfiler *profiler = NULL;
    u32 count = 0u;

    ASSERT_EQ(break_runtime_profiler_create(NULL, &profiler), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_profiler_record(profiler, "evt"), BREAK_RUNTIME_OK);

    {
        BreakRuntimeThreadConfig thread_cfg;
        BreakRuntimeThread *thread = NULL;
        _Atomic u32 collect_result = 0xFFFFFFFFu;
        _Atomic u32 export_result = 0xFFFFFFFFu;
        ProfilerEnforceArg arg;
        arg.profiler = profiler;
        arg.collect_result = &collect_result;
        arg.export_result = &export_result;
        memset(&thread_cfg, 0, sizeof(thread_cfg));
        thread_cfg.name = "prof-owner-probe";
        thread_cfg.fn = profiler_enforce_worker;
        thread_cfg.arg = &arg;
        ASSERT_EQ(break_runtime_thread_create(&thread_cfg, &thread),
                  BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_thread_start(thread), BREAK_RUNTIME_OK);
        ASSERT_EQ(break_runtime_thread_stop(thread, 2000u), BREAK_RUNTIME_OK);
        break_runtime_thread_destroy(thread);
        ASSERT_EQ(atomic_load_explicit(&collect_result, memory_order_acquire),
                  (u32)BREAK_RUNTIME_REJECTED);
        ASSERT_EQ(atomic_load_explicit(&export_result, memory_order_acquire),
                  (u32)BREAK_RUNTIME_REJECTED);
    }

    /* The owner thread collects and exports fine. */
    ASSERT_EQ(break_runtime_profiler_collect(profiler, 4u, &count),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(count, 1u);

    break_runtime_profiler_close(profiler);
    break_runtime_profiler_destroy(profiler);
}

TEST_MAIN_BEGIN()
    RUN_TEST(reload_create_validation_and_oom);
    RUN_TEST(reload_request_validation);
    RUN_TEST(reload_enum_ordinals_and_names);
    RUN_TEST(reload_file_event_coalescing);
    RUN_TEST(reload_file_event_queue_overload);
    RUN_TEST(reload_commit_success_owner_thread);
    RUN_TEST(reload_load_failure_preserves_old_data);
    RUN_TEST(reload_validate_failure_preserves_old_data);
    RUN_TEST(reload_commit_failure_preserves_old_data);
    RUN_TEST(reload_stale_generation_rejected);
    RUN_TEST(reload_cancel_queued_exactly_once);
    RUN_TEST(reload_cancel_inflight_stale_drop);
    RUN_TEST(reload_cancel_idempotent_and_inflight_commit_rejected);
    RUN_TEST(reload_timeout);
    RUN_TEST(reload_staging_oom_state);
    RUN_TEST(reload_request_queue_overload);
    RUN_TEST(reload_commit_queue_overload);
    RUN_TEST(reload_shutdown_cancels_pending_and_closes_admission);
    RUN_TEST(reload_shutdown_timeout_retains_live_ownership);
    RUN_TEST(reload_events_pump_defers_while_inflight);
    RUN_TEST(reload_owner_thread_enforced);
#if !defined(_WIN32)
    RUN_TEST(reload_destroy_requires_shutdown_aborts);
#endif
    RUN_TEST(profiler_create_validation_and_oom);
    RUN_TEST(profiler_record_collect_export_roundtrip);
    RUN_TEST(profiler_record_overload_never_blocks);
    RUN_TEST(profiler_name_copied_owned);
    RUN_TEST(profiler_multithreaded_handoff);
    RUN_TEST(profiler_close_drains_then_closed);
    RUN_TEST(profiler_window_bounded_drop);
    RUN_TEST(profiler_collect_owner_enforced);
TEST_MAIN_END()
