#include "core_app_diagnostics.h"

#include <crash/break_crash.h>

#include <stdio.h>

static void core_app_diagnostics_set_u64(BreakCrashSummary *summary,
                                         const char *section, const char *key,
                                         u64 value) {
    char text[32];
    (void)snprintf(text, sizeof(text), "%llu", (unsigned long long)value);
    (void)break_crash_summary_set(summary, section, key, text);
}

bool core_app_diagnostics_start(const char *spool_root) {
    BreakCrashConfig config;
    if (!spool_root || !spool_root[0]) return false;
    config.spool_root = spool_root;
    return break_crash_install(&config);
}

void core_app_diagnostics_stop(void) {
    break_crash_set_context_blob(NULL, 0u);
    break_crash_uninstall();
}

void core_app_diagnostics_publish(
    void *user, const CoreAppDiagnosticsSnapshot *snapshot) {
    BreakCrashSummary summary;
    char blob[BREAK_CRASH_CONTEXT_BLOB_MAX + 1u];
    usize size;
    (void)user;
    if (!snapshot) return;

    break_crash_summary_init(&summary);
    (void)break_crash_summary_set(&summary, "rhi", "backend", snapshot->rhi_backend);
    (void)break_crash_summary_set(&summary, "rhi", "gpu", snapshot->gpu_name);
    (void)break_crash_summary_set(&summary, "net", "live",
                                  snapshot->network_live ? "true" : "false");
    core_app_diagnostics_set_u64(&summary, "net", "seen",
                                 snapshot->network_events_seen);
    core_app_diagnostics_set_u64(&summary, "net", "dropped",
                                 snapshot->network_events_dropped);
    core_app_diagnostics_set_u64(&summary, "input", "tick", snapshot->tick);
    core_app_diagnostics_set_u64(&summary, "input", "keys", snapshot->key_down_count);
    core_app_diagnostics_set_u64(&summary, "input", "pads", snapshot->pad_connected_count);
    core_app_diagnostics_set_u64(&summary, "input", "touches", snapshot->touch_count);
    core_app_diagnostics_set_u64(&summary, "input", "gestures", snapshot->gesture_count);
    core_app_diagnostics_set_u64(&summary, "input", "touch_status", snapshot->touch_status);
    core_app_diagnostics_set_u64(&summary, "input", "haptic_status", snapshot->haptic_status);
    size = break_crash_summary_format(&summary, blob, sizeof(blob));
    break_crash_set_context_blob(blob, size);
}
