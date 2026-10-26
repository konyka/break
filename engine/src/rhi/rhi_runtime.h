#ifndef RHI_RUNTIME_H
#define RHI_RUNTIME_H
/* Runtime backend selection for multi-backend builds
 * (docs/design/rhi_runtime_backend.md). The selection logic is pure: real
 * backends and tests both plug in through RHIRuntimeBackendDesc, so the chain
 * rules are unit-testable without a GPU. */
#include <rhi/rhi.h>
#include <stdbool.h>

#include "rhi/dispatch/rhi_api.h"

typedef RHIDevice *(*RHIRuntimeCreateFn)(void *window_native,
                                         void *display_native, u32 w, u32 h);

typedef struct RHIRuntimeBackendDesc {
    RHIBackend backend;
    const char *name;          /* "vulkan" | "opengl" (RHIEVT backend field) */
    const RHIApi *api;         /* table installed when this backend wins */
    RHIRuntimeCreateFn create; /* backend-local rhi_device_create */
    bool use_surface_native;   /* VK consumes surface_native, GL window_native */
} RHIRuntimeBackendDesc;

/* Environment knobs, read through an injectable getter (NULL = getenv). */
typedef const char *(*RHIRuntimeGetenvFn)(const char *name);

typedef struct RHIRuntimeConfig {
    const RHIRuntimeBackendDesc *backends; /* chain order: primary first */
    u32 backend_count;
    RHIRuntimeGetenvFn getenv_fn;
} RHIRuntimeConfig;

/* Chain entry (rhi_device_create_compiled semantics). Tries each allowed
 * backend in order; on success installs its table and returns the device.
 * BREAK_RHI_BACKEND=<name> restricts the chain to that backend,
 * BREAK_RHI_NO_FALLBACK=1 keeps only the first entry, BREAK_RHI_FAIL_VULKAN=1
 * fails the vulkan entry before it touches the driver (test hook). Emits
 * RHIEVT fallback per failed entry and backend_selected on success. */
RHIDevice *rhi_runtime_create_chain(const RHIRuntimeConfig *cfg,
                                    void *window_native, void *surface_native,
                                    void *display_native, u32 w, u32 h);

/* Explicit entry (rhi_device_create semantics): exactly the requested
 * backend, no fallback, unknown/unlinked backend fails. */
RHIDevice *rhi_runtime_create_explicit(const RHIRuntimeConfig *cfg,
                                       RHIBackend backend, void *window_native,
                                       void *display_native, u32 w, u32 h);

/* Backend name of the active table: "vulkan", "opengl", or "none". */
const char *rhi_runtime_active_backend(void);

/* Test reset: back to the pre-device stub table and "none". */
void rhi_runtime_reset_for_test(void);

#endif
