#include <renderer/render_features.h>

RenderFeatureSelection render_features_select(
    const RenderFeatureCapabilities *capabilities,
    bool request_ray_tracing,
    RenderUpscaler requested_upscaler) {
    RenderFeatureSelection selection = {
        RENDER_PATH_RASTER,
        RENDER_UPSCALER_DIRECT,
        RENDER_FALLBACK_NONE,
    };

    if (capabilities == NULL) {
        return selection;
    }

    if (request_ray_tracing && capabilities->ray_tracing) {
        selection.path = RENDER_PATH_RAY_TRACING;
    } else if (request_ray_tracing) {
        selection.fallback = RENDER_FALLBACK_RAY_TRACING_UNSUPPORTED;
    }

    if (requested_upscaler == RENDER_UPSCALER_TSR) {
        selection.upscaler = RENDER_UPSCALER_TSR;
    } else if (requested_upscaler == RENDER_UPSCALER_DLSS) {
        if (!capabilities->dlss) {
            selection.fallback = RENDER_FALLBACK_DLSS_UNSUPPORTED;
        } else if (!capabilities->api_supports_dlss) {
            selection.fallback = RENDER_FALLBACK_DLSS_API_UNSUPPORTED;
        } else if (!capabilities->dlss_runtime) {
            selection.fallback = RENDER_FALLBACK_DLSS_RUNTIME_UNAVAILABLE;
        } else {
            selection.upscaler = RENDER_UPSCALER_DLSS;
        }
    }

    return selection;
}
