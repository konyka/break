#pragma once

#include <core/types.h>

typedef enum {
    RENDER_UPSCALER_DIRECT,
    RENDER_UPSCALER_TSR,
    RENDER_UPSCALER_DLSS,
} RenderUpscaler;

typedef enum {
    RENDER_PATH_RASTER,
    RENDER_PATH_RAY_TRACING,
} RenderPath;

typedef enum {
    RENDER_FALLBACK_NONE,
    RENDER_FALLBACK_RAY_TRACING_UNSUPPORTED,
    RENDER_FALLBACK_DLSS_UNSUPPORTED,
    RENDER_FALLBACK_DLSS_API_UNSUPPORTED,
    RENDER_FALLBACK_DLSS_RUNTIME_UNAVAILABLE,
} RenderFallbackReason;

typedef struct {
    bool ray_tracing;
    bool dlss;
    bool dlss_runtime;
    bool api_supports_dlss;
} RenderFeatureCapabilities;

typedef struct {
    RenderPath path;
    RenderUpscaler upscaler;
    RenderFallbackReason fallback;
} RenderFeatureSelection;

RenderFeatureSelection render_features_select(
    const RenderFeatureCapabilities *capabilities,
    bool request_ray_tracing,
    RenderUpscaler requested_upscaler);
