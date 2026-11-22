#if !defined(_WIN32) && !defined(__APPLE__)
#define _POSIX_C_SOURCE 200809L
#endif

#include "test_framework.h"
#include "test_fork.h"

#include "core_app_diagnostics.h"

#include <crash/break_crash.h>
#include <platform/platform_fs.h>

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if !defined(_WIN32)
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#endif

#ifndef __has_feature
#define __has_feature(x) 0
#endif
#if defined(__SANITIZE_ADDRESS__) || __has_feature(address_sanitizer)
const char *__asan_default_options(void) {
    return "allow_user_segv_handler=1";
}
#endif

static const char EXPECTED_BLOB[] =
    "[rhi]\n"
    "backend=vulkan\n"
    "gpu=Device_Name\n"
    "[net]\n"
    "live=true\n"
    "seen=7\n"
    "dropped=2\n"
    "[input]\n"
    "tick=4\n"
    "keys=1\n"
    "pads=2\n"
    "touches=3\n"
    "gestures=4\n"
    "touch_status=5\n"
    "haptic_status=6\n";

#define RECORD_BLOB_TEXT \
    "[rhi]\n" \
    "backend=record\n" \
    "gpu=none\n" \
    "[net]\n" \
    "live=false\n" \
    "seen=0\n" \
    "dropped=0\n" \
    "[input]\n" \
    "tick=4\n" \
    "keys=1\n" \
    "pads=0\n" \
    "touches=0\n" \
    "gestures=0\n" \
    "touch_status=0\n" \
    "haptic_status=0\n"

static const char NUL_SUFFIX_BLOB[] =
    RECORD_BLOB_TEXT "\0[extra]\nvalue=1\n";
static const char EXTRA_SECTION_BLOB[] =
    RECORD_BLOB_TEXT "[extra]\nvalue=1\n";

static CoreAppDiagnosticsSnapshot sample_snapshot(void) {
    CoreAppDiagnosticsSnapshot snapshot;
    memset(&snapshot, 0, sizeof(snapshot));
    snapshot.tick = 4u;
    snapshot.rhi_backend = "vulkan";
    snapshot.gpu_name = "Device/Name";
    snapshot.network_live = true;
    snapshot.network_events_seen = 7u;
    snapshot.network_events_dropped = 2u;
    snapshot.key_down_count = 1u;
    snapshot.pad_connected_count = 2u;
    snapshot.touch_count = 3u;
    snapshot.gesture_count = 4u;
    snapshot.touch_status = 5u;
    snapshot.haptic_status = 6u;
    return snapshot;
}

static CoreAppDiagnosticsSnapshot record_snapshot(void) {
    CoreAppDiagnosticsSnapshot snapshot;
    memset(&snapshot, 0, sizeof(snapshot));
    snapshot.tick = 4u;
    snapshot.rhi_backend = "record";
    snapshot.gpu_name = "none";
    snapshot.key_down_count = 1u;
    return snapshot;
}

static void join_path(char *out, usize cap, const char *a, const char *b) {
    int n = snprintf(out, cap, "%s/%s", a, b);
    if (n < 0 || (usize)n >= cap) abort();
}

static void remove_spool(const char *root) {
    static const char *const subdirs[] = {"pending", "sent", "discarded"};
    char dir[1100];
    char path[1200];
    usize i;
    for (i = 0; i < sizeof(subdirs) / sizeof(subdirs[0]); ++i) {
        PlatformDirEntry entries[64];
        u32 count = 0;
        u32 j;
        join_path(dir, sizeof(dir), root, subdirs[i]);
        if (platform_list_dir(dir, entries, 64, &count)) {
            for (j = 0; j < count && j < 64; ++j) {
                if (!entries[j].is_dir) {
                    join_path(path, sizeof(path), dir, entries[j].name);
                    (void)remove(path);
                }
            }
        }
        (void)TEST_RMDIR(dir);
    }
    join_path(path, sizeof(path), root, "crash.inbox");
    (void)remove(path);
    (void)TEST_RMDIR(root);
}

static int check_recovered_blob(const char *root) {
    BreakCrashSpool *spool = NULL;
    BreakCrashRecord *record = NULL;
    u8 *bytes = NULL;
    u64 byte_count = 0;
    const u8 *blob = NULL;
    usize blob_size = 0;
    int result = 1;

    spool = break_crash_spool_open(root);
    if (!spool) goto done;
    result = 2;
    if (break_crash_spool_count(spool, 0) != 1u ||
        break_crash_spool_count(spool, 1) != 0u ||
        break_crash_spool_count(spool, 2) != 0u) goto done;
    result = 3;
    if (!break_crash_spool_read_pending(spool, 0, &bytes, &byte_count)) goto done;
    if (byte_count == 0u || byte_count > BREAK_CRASH_RECORD_MAX) goto done;
    result = 4;
    record = break_crash_record_parse(bytes, (usize)byte_count);
    if (!record) goto done;
    result = 5;
    if (break_crash_record_signo(record) != SIGSEGV) goto done;
    blob_size = break_crash_record_context_blob(record, &blob);
    if (blob_size != strlen(EXPECTED_BLOB) || !blob) goto done;
    result = 6;
    if (memcmp(blob, EXPECTED_BLOB, blob_size) != 0) goto done;
    result = 0;

done:
    break_crash_record_destroy(record);
    free(bytes);
    break_crash_spool_destroy(spool);
    return result;
}

#if !defined(_WIN32)
static void crash_child(const char *root, const CoreAppDiagnosticsSnapshot *snapshot,
                        bool publish_null) {
    if (!core_app_diagnostics_start(root)) _exit(41);
    core_app_diagnostics_publish(NULL, snapshot);
    if (publish_null) core_app_diagnostics_publish(NULL, NULL);
    (void)raise(SIGSEGV);
    _exit(42);
}

static pid_t spawn_crash(const char *root, const CoreAppDiagnosticsSnapshot *snapshot,
                         bool publish_null) {
    pid_t pid = fork();
    if (pid == 0) crash_child(root, snapshot, publish_null);
    return pid;
}

static pid_t spawn_raw_blob_crash(const char *root, const void *blob, usize size) {
    pid_t pid = fork();
    if (pid == 0) {
        BreakCrashConfig config = {root};
        if (!break_crash_install(&config)) _exit(51);
        break_crash_set_context_blob(blob, size);
        (void)raise(SIGSEGV);
        _exit(52);
    }
    return pid;
}

static int wait_for_segv(pid_t pid) {
    int status = 0;
    if (test_waitpid_deadline(pid, &status, 30000u) != pid) return 0;
    return WIFSIGNALED(status) && WTERMSIG(status) == SIGSEGV;
}

static int run_record_verifier(const char *root, const char *tick) {
    pid_t pid = fork();
    int status = 0;
    if (pid == 0) {
        if (tick) {
            execl(CORE_APP_CRASH_RECORD_PATH, CORE_APP_CRASH_RECORD_PATH,
                  root, tick, (char *)NULL);
        } else {
            execl(CORE_APP_CRASH_RECORD_PATH, CORE_APP_CRASH_RECORD_PATH,
                  (char *)NULL);
        }
        _exit(90);
    }
    if (pid < 0) return -1;
    if (test_waitpid_deadline(pid, &status, 30000u) != pid) return -1;
    if (!WIFEXITED(status)) return -1;
    return WEXITSTATUS(status);
}

static int write_invalid_pending(const char *root) {
    char path[1200];
    static const char invalid[] = "not a crash record\n";
    FILE *file;
    int ok;
    join_path(path, sizeof(path), root, "pending/1.bcr");
    file = fopen(path, "wb");
    if (!file) return 0;
    ok = fwrite(invalid, 1, sizeof(invalid) - 1u, file) == sizeof(invalid) - 1u;
    if (fclose(file) != 0) ok = 0;
    return ok;
}
#endif

TEST(start_validates_root_and_stop_uninstalls) {
    char root[512];
    bool null_rejected;
    bool empty_rejected;
    bool started;
    bool installed;
    bool stopped;
    test_tmp(root, sizeof(root), "core_app_diag_start");
    null_rejected = !core_app_diagnostics_start(NULL);
    empty_rejected = !core_app_diagnostics_start("");
    started = core_app_diagnostics_start(root);
    installed = break_crash_is_installed();
#if defined(_WIN32)
    core_app_diagnostics_stop();
    stopped = !break_crash_is_installed();
    remove_spool(root);
    ASSERT_FALSE(started);
    ASSERT_FALSE(installed);
#else
    {
        bool second = started ? core_app_diagnostics_start(root) : true;
        core_app_diagnostics_stop();
        stopped = !break_crash_is_installed();
        remove_spool(root);
        ASSERT_TRUE(started);
        ASSERT_TRUE(installed);
        ASSERT_FALSE(second);
    }
#endif
    ASSERT_TRUE(null_rejected);
    ASSERT_TRUE(empty_rejected);
    ASSERT_TRUE(stopped);
}

TEST(real_child_crash_recovers_exact_sanitized_blob) {
#if defined(_WIN32)
    ASSERT_TRUE(1);
#else
    char root[512];
    CoreAppDiagnosticsSnapshot snapshot = sample_snapshot();
    pid_t pid;
    int signal_ok = 0;
    int recovered = -1;
    test_tmp(root, sizeof(root), "core_app_diag_segv");
    pid = spawn_crash(root, &snapshot, true);
    if (pid > 0) {
        signal_ok = wait_for_segv(pid);
        if (signal_ok) recovered = check_recovered_blob(root);
    }
    remove_spool(root);
    ASSERT_TRUE(pid > 0);
    ASSERT_TRUE(signal_ok);
    ASSERT_EQ(recovered, 0);
#endif
}

TEST(record_verifier_checks_real_record_and_error_codes) {
#if defined(_WIN32)
    ASSERT_TRUE(1);
#else
    char root[512];
    char empty_root[512];
    char nul_root[512];
    char extra_root[512];
    CoreAppDiagnosticsSnapshot snapshot = record_snapshot();
    pid_t pid;
    pid_t nul_pid;
    pid_t extra_pid;
    int signal_ok = 0;
    int nul_signal_ok = 0;
    int extra_signal_ok = 0;
    int valid = -1;
    int wrong_tick = -1;
    int usage = -1;
    int recovery = -1;
    int parse = -1;
    int nul_contract = -1;
    int extra_contract = -1;
    int planted;
    test_tmp(root, sizeof(root), "core_app_diag_verify");
    test_tmp(empty_root, sizeof(empty_root), "core_app_diag_verify_empty");
    test_tmp(nul_root, sizeof(nul_root), "core_app_diag_verify_nul");
    test_tmp(extra_root, sizeof(extra_root), "core_app_diag_verify_extra");
    pid = spawn_crash(root, &snapshot, false);
    if (pid > 0) signal_ok = wait_for_segv(pid);
    if (signal_ok) {
        valid = run_record_verifier(root, "4");
        wrong_tick = run_record_verifier(root, "5");
    }
    usage = run_record_verifier(root, NULL);
    recovery = run_record_verifier(empty_root, "4");
    planted = write_invalid_pending(empty_root);
    if (planted) parse = run_record_verifier(empty_root, "4");
    nul_pid = spawn_raw_blob_crash(nul_root, NUL_SUFFIX_BLOB,
                                   sizeof(NUL_SUFFIX_BLOB) - 1u);
    if (nul_pid > 0) nul_signal_ok = wait_for_segv(nul_pid);
    if (nul_signal_ok) nul_contract = run_record_verifier(nul_root, "4");
    extra_pid = spawn_raw_blob_crash(extra_root, EXTRA_SECTION_BLOB,
                                     sizeof(EXTRA_SECTION_BLOB) - 1u);
    if (extra_pid > 0) extra_signal_ok = wait_for_segv(extra_pid);
    if (extra_signal_ok) extra_contract = run_record_verifier(extra_root, "4");
    remove_spool(root);
    remove_spool(empty_root);
    remove_spool(nul_root);
    remove_spool(extra_root);
    if (nul_contract != 5 || extra_contract != 5) {
        printf("  raw blob verifier exits: nul=%d extra=%d\n",
               nul_contract, extra_contract);
    }
    ASSERT_TRUE(pid > 0);
    ASSERT_TRUE(signal_ok);
    ASSERT_EQ(valid, 0);
    ASSERT_EQ(wrong_tick, 5);
    ASSERT_EQ(usage, 2);
    ASSERT_EQ(recovery, 3);
    ASSERT_TRUE(planted);
    ASSERT_EQ(parse, 4);
    ASSERT_TRUE(nul_pid > 0);
    ASSERT_TRUE(nul_signal_ok);
    ASSERT_TRUE(extra_pid > 0);
    ASSERT_TRUE(extra_signal_ok);
    ASSERT_EQ(extra_contract, 5);
    ASSERT_EQ(nul_contract, 5);
#endif
}

TEST_MAIN_BEGIN()
    RUN_TEST(start_validates_root_and_stop_uninstalls);
    RUN_TEST(real_child_crash_recovers_exact_sanitized_blob);
    RUN_TEST(record_verifier_checks_real_record_and_error_codes);
TEST_MAIN_END()
