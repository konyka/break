#include <runtime/runtime_mainloop_platform.h>

#include <platform/platform.h>

#include <string.h>

bool break_runtime_mainloop_platform_facts(Platform *platform, u64 frame, bool close_requested,
                                           BreakRuntimeMainLoopFacts *out) {
    PlatformWsiSurface wsi;
    if (!platform || !out) return false;
    memset(out, 0, sizeof(*out));
    out->frame = frame;
    out->close_requested = close_requested;
    platform_get_drawable_size(platform, &out->drawable_width, &out->drawable_height);
    out->content_scale = platform_get_content_scale(platform);
    out->wsi_state = platform_wsi_surface_query(platform, &wsi) ? (u32)wsi.state
                                                                : (u32)PLATFORM_WSI_UNAVAILABLE;
    return true;
}
