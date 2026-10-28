/* Runtime backend selection (docs/design/rhi_runtime_backend.md). Pure chain
 * logic over RHIRuntimeBackendDesc; the multi-backend build wires the real
 * Vulkan/OpenGL factories in rhi_runtime_backends.c. */
#include "rhi/rhi_runtime.h"

#include <stdlib.h>
#include <string.h>

#include "core/log.h"
#include "rhi/rhi_rollout.h"

static const char *g_active_name = "none";
static const RHIApi *g_active_api;
static const char *g_selection_reason = "none";

static void deactivate(void);

const char *rhi_runtime_active_backend(void) { return g_active_name; }
const char *rhi_runtime_selection_reason(void) { return g_selection_reason; }

void rhi_runtime_reset_for_test(void) {
    deactivate();
    g_selection_reason = "none";
    rhi_rollout_set_runtime_selection(NULL, NULL);
}

static const char *runtime_getenv(const RHIRuntimeConfig *cfg, const char *n) {
    return cfg->getenv_fn != NULL ? cfg->getenv_fn(n) : getenv(n);
}

static bool env_flag(const RHIRuntimeConfig *cfg, const char *name) {
    const char *v = runtime_getenv(cfg, name);
    return v != NULL && v[0] != '\0' && strcmp(v, "0") != 0;
}

static void emit(const char *event, const char *backend, const char *reason,
                 const char *result) {
    RHIRolloutEvent ev = {
        .event = event,
        .backend = backend,
        .reason = reason,
        .config_version = ENGINE_RHI_ROLLOUT_CONFIG_VERSION,
        .result = result,
    };
    rhi_rollout_emit(&ev);
}

static bool config_valid(const RHIRuntimeConfig *cfg) {
    u32 i;
    if (cfg == NULL || cfg->backends == NULL || cfg->backend_count == 0u)
        return false;
    for (i = 0; i < cfg->backend_count; i++) {
        const RHIRuntimeBackendDesc *b = &cfg->backends[i];
        if (b->name == NULL || b->api == NULL || b->create == NULL) return false;
    }
    return true;
}

static void install(const RHIApi *api, const char *name) {
    rhi_dispatch_set_api(api);
    g_active_api = api;
    g_active_name = name;
}

static void deactivate(void) { install(NULL, "none"); }

static void record_selection(const RHIRuntimeBackendDesc *b, const char *reason) {
    g_selection_reason = reason;
    rhi_rollout_set_runtime_selection(b->name, reason);
}

/* Calls the backend factory with its table already installed: backend
 * create paths call other public rhi_* functions (they resolve to the
 * namespaced symbols directly inside the backend TU, but core helpers such
 * as rhi_device_create_ex go through the forwarders). On failure the
 * previously installed table (the stub, or the backend of a device that is
 * still alive) comes back, so nothing routes to a half-made backend and a
 * live device keeps working. */
static RHIDevice *try_create(const RHIRuntimeBackendDesc *b, void *window_native,
                             void *surface_native, void *display_native,
                             u32 w, u32 h) {
    const RHIApi *prev_api = g_active_api;
    const char *prev_name = g_active_name;
    RHIDevice *dev;
    install(b->api, b->name);
    dev = b->create(b->use_surface_native ? surface_native : window_native,
                    display_native, w, h);
    if (dev == NULL) install(prev_api, prev_name);
    return dev;
}

RHIDevice *rhi_runtime_create_chain(const RHIRuntimeConfig *cfg,
                                    void *window_native, void *surface_native,
                                    void *display_native, u32 w, u32 h) {
    const char *only;
    const char *reason = "platform-default";
    bool no_fallback, fail_vulkan;
    u32 i, tried = 0u;
    if (!config_valid(cfg)) return NULL;

    only = runtime_getenv(cfg, "BREAK_RHI_BACKEND");
    if (only != NULL && only[0] != '\0') {
        bool known = false;
        for (i = 0; i < cfg->backend_count; i++)
            if (strcmp(cfg->backends[i].name, only) == 0) known = true;
        if (known) {
            reason = "explicit-env";
        } else {
            LOG_WARN("BREAK_RHI_BACKEND=%s is not a linked backend; using the "
                     "default chain", only);
            only = NULL;
        }
    } else {
        only = NULL;
    }
    no_fallback = env_flag(cfg, "BREAK_RHI_NO_FALLBACK");
    fail_vulkan = env_flag(cfg, "BREAK_RHI_FAIL_VULKAN");

    for (i = 0; i < cfg->backend_count; i++) {
        const RHIRuntimeBackendDesc *b = &cfg->backends[i];
        RHIDevice *dev = NULL;
        if (only != NULL && strcmp(b->name, only) != 0) continue;
        if (no_fallback && tried > 0u) break;
        tried++;
        if (fail_vulkan && b->backend == RHI_BACKEND_VULKAN) {
            LOG_WARN("BREAK_RHI_FAIL_VULKAN=1: skipping the vulkan device (test hook)");
        } else {
            dev = try_create(b, window_native, surface_native, display_native,
                             w, h);
        }
        if (dev != NULL) {
            record_selection(b, tried > 1u ? "config-fallback" : reason);
            emit("backend_selected", b->name, g_selection_reason, "OK");
            return dev;
        }
        emit("fallback", b->name, reason, "ERROR");
        reason = "config-fallback";
    }
    return NULL;
}

RHIDevice *rhi_runtime_create_explicit(const RHIRuntimeConfig *cfg,
                                       RHIBackend backend, void *window_native,
                                       void *display_native, u32 w, u32 h) {
    u32 i;
    if (!config_valid(cfg)) return NULL;
    for (i = 0; i < cfg->backend_count; i++) {
        const RHIRuntimeBackendDesc *b = &cfg->backends[i];
        RHIDevice *dev;
        if (b->backend != backend) continue;
        /* explicit: the caller already passed the handle this backend wants */
        dev = try_create(b, window_native, window_native, display_native, w, h);
        if (dev != NULL) {
            record_selection(b, "platform-default");
            emit("backend_selected", b->name, g_selection_reason, "OK");
        }
        return dev;
    }
    return NULL;
}
