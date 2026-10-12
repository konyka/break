#pragma once

#include <rhi/rhi.h>

/* Probe result for the optional NVIDIA Streamline DLSS runtime. */
typedef enum {
    SL_DLSS_UNAVAILABLE = 0,
    SL_DLSS_SUPPORTED,
    SL_DLSS_MISSING_RUNTIME,
    SL_DLSS_INIT_FAILED,
    SL_DLSS_FEATURE_UNSUPPORTED,
    SL_DLSS_INTERNAL_ERROR,
} SLDlssProbeResult;

typedef enum {
    SL_DLSS_API_UNAVAILABLE = 0,
    SL_DLSS_API_READY,
} SLDlssApiStatus;

const char *sl_dlss_probe_result_text(SLDlssProbeResult result);

/*
 * Load sl.interposer.dll (Windows only), initialize Streamline with a DLSS
 * feature request, and query feature support for the given native Vulkan
 * device. `native` may be NULL for a runtime-only probe.
 *
 * The loader search order is: $BREAK_SL_DIR, then
 * ../third_party/streamline-bin/<ver>/bin/x64 relative to the process working
 * directory, then the default loader path. Every failure mode returns false
 * with a classified result; no function here terminates the process.
 *
 * A successful probe keeps the library loaded; call sl_dlss_shutdown() once
 * before device teardown. On non-Windows builds the probe always reports
 * SL_DLSS_UNAVAILABLE.
 */
bool sl_dlss_probe(const RHINativeDevice *native, SLDlssProbeResult *out_result);
void sl_dlss_shutdown(void);
SLDlssApiStatus sl_dlss_api_status(void);
