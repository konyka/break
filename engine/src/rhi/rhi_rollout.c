#include "rhi/rhi_rollout.h"
#include "core/log.h"
#include <stdio.h>
#include <string.h>

static int allowed(const char *value, const char *const *set) {
    int i;
    for (i = 0; set[i] != NULL; i++)
        if (strcmp(value, set[i]) == 0) return 1;
    return 0;
}

int rhi_rollout_format(char *buf, size_t cap, const RHIRolloutEvent *ev) {
    static const char *const events[] = {
        "backend_selected", "fallback", "device_lost",
        "present_failure", "shader_failure", NULL };
    static const char *const backends[] = {
        "vulkan", "metal", "d3d12", "opengl", NULL };
    static const char *const reasons[] = {
        "platform-default", "explicit-env", "compat-override",
        "config-fallback", "none", NULL };
    int n;
    if (buf == NULL || ev == NULL || ev->event == NULL || ev->backend == NULL ||
        ev->reason == NULL || ev->result == NULL) return -1;
    if (!allowed(ev->event, events) || !allowed(ev->backend, backends) ||
        !allowed(ev->reason, reasons)) return -1;
    n = snprintf(buf, cap,
        "RHIEVT {\"event\":\"%s\",\"backend\":\"%s\",\"reason\":\"%s\","
        "\"config_version\":%d,\"result\":\"%s\"}",
        ev->event, ev->backend, ev->reason, ev->config_version, ev->result);
    if (n < 0 || (size_t)n >= cap) return -1;
    return n;
}

void rhi_rollout_emit(const RHIRolloutEvent *ev) {
    char buf[512];
    if (rhi_rollout_format(buf, sizeof(buf), ev) > 0)
        LOG_INFO("%s", buf);
}

const char *rhi_result_name(RHIResult result) {
    switch (result) {
    case RHI_RESULT_OK: return "OK";
    case RHI_RESULT_ERROR: return "ERROR";
    case RHI_RESULT_INVALID_ARGUMENT: return "INVALID_ARGUMENT";
    case RHI_RESULT_UNAVAILABLE: return "UNAVAILABLE";
    case RHI_RESULT_UNSUPPORTED: return "UNSUPPORTED";
    case RHI_RESULT_BUSY: return "BUSY";
    case RHI_RESULT_OUT_OF_DATE: return "OUT_OF_DATE";
    case RHI_RESULT_SURFACE_LOST: return "SURFACE_LOST";
    case RHI_RESULT_DEVICE_LOST: return "DEVICE_LOST";
    case RHI_RESULT_SYNC_FAILED: return "SYNC_FAILED";
    }
    return "ERROR";
}

const char *rhi_rollout_compiled_backend(void) {
#if defined(ENGINE_RHI_BACKEND_VULKAN)
    return "vulkan";
#elif defined(ENGINE_RHI_BACKEND_METAL)
    return "metal";
#elif defined(ENGINE_RHI_BACKEND_D3D12)
    return "d3d12";
#else
    return "opengl";
#endif
}

const char *rhi_rollout_compiled_reason(void) {
#if defined(ENGINE_RHI_BACKEND_VULKAN) || defined(ENGINE_RHI_BACKEND_METAL) \
    || defined(ENGINE_RHI_BACKEND_D3D12)
    return "platform-default";
#else
    return "compat-override";
#endif
}
