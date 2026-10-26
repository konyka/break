/* Multi-backend shape only (ENGINE_RHI_MULTI_BACKEND): owns the public
 * rhi_device_create / rhi_device_create_compiled symbols and wires the real
 * Vulkan and OpenGL backends into the runtime chain
 * (docs/design/rhi_runtime_backend.md §4). Each backend's own factory is
 * reached through its RHIApi table, which binds the namespaced
 * rhi_vk_rhi_device_create / rhi_gl_rhi_device_create symbols. */
#include "rhi/rhi_runtime.h"

#ifndef ENGINE_RHI_MULTI_BACKEND
#error "rhi_runtime_backends.c is only compiled in the multi-backend shape"
#endif

static RHIDevice *vk_create(void *window_native, void *display_native, u32 w,
                            u32 h) {
    return rhi_api_backend_vk()->rhi_device_create(
        RHI_BACKEND_VULKAN, window_native, display_native, w, h);
}

static RHIDevice *gl_create(void *window_native, void *display_native, u32 w,
                            u32 h) {
    return rhi_api_backend_gl()->rhi_device_create(
        RHI_BACKEND_OPENGL, window_native, display_native, w, h);
}

static const RHIRuntimeConfig *runtime_config(void) {
    static RHIRuntimeBackendDesc backends[2];
    static RHIRuntimeConfig cfg;
    if (cfg.backends == NULL) {
        backends[0] = (RHIRuntimeBackendDesc){
            RHI_BACKEND_VULKAN, "vulkan", rhi_api_backend_vk(), vk_create, true};
        backends[1] = (RHIRuntimeBackendDesc){
            RHI_BACKEND_OPENGL, "opengl", rhi_api_backend_gl(), gl_create, false};
        cfg.backends = backends;
        cfg.backend_count = 2u;
        cfg.getenv_fn = NULL;
    }
    return &cfg;
}

RHIDevice *rhi_device_create_compiled(void *window_native, void *surface_native,
                                      void *display_native, u32 w, u32 h) {
    return rhi_runtime_create_chain(runtime_config(), window_native,
                                    surface_native, display_native, w, h);
}

RHIDevice *rhi_device_create(RHIBackend backend, void *window_native,
                             void *display_native, u32 w, u32 h) {
    return rhi_runtime_create_explicit(runtime_config(), backend, window_native,
                                       display_native, w, h);
}
