#pragma once
#include <rhi/rhi.h>

/* FS3: size-dependent post-process render targets. Each system describes its
 * targets once; init and *_resize both go through post_targets_replace, so a
 * resize recreates only textures/FBOs and never touches pipelines, bindings,
 * samplers or uniform locations.
 *
 * Create before destroy (main.c R362): every replacement is created first; if
 * any of them fails, the new ones are destroyed and the live targets are left
 * untouched, so a failed resize keeps the previous, still valid, targets. */

#define POST_TARGETS_MAX 4u

typedef struct {
    RHIOffscreenFBO *slot;
    u32              width;
    u32              height;
    /* RHI_FORMAT_UNDEFINED selects rhi_offscreen_fbo_create (the backend's
     * default colour format), every other value rhi_offscreen_fbo_create_fmt. */
    RHIFormat        format;
} PostTargetSpec;

static inline u32 post_targets_half(u32 v) {
    u32 h = v / 2u;
    return h < 1u ? 1u : h;
}

static inline bool post_targets_replace(RHIDevice *dev, const PostTargetSpec *specs,
                                        u32 count) {
    RHIOffscreenFBO fresh[POST_TARGETS_MAX];
    u32 i;
    if (dev == NULL || specs == NULL || count == 0u || count > POST_TARGETS_MAX)
        return false;
    for (i = 0u; i < count; ++i) {
        fresh[i] = specs[i].format == RHI_FORMAT_UNDEFINED
            ? rhi_offscreen_fbo_create(dev, specs[i].width, specs[i].height)
            : rhi_offscreen_fbo_create_fmt(dev, specs[i].width, specs[i].height,
                                           specs[i].format);
        if (!rhi_handle_valid(fresh[i].fb)) {
            while (i-- > 0u) rhi_offscreen_fbo_destroy(dev, &fresh[i]);
            return false;
        }
    }
    for (i = 0u; i < count; ++i) {
        if (rhi_handle_valid(specs[i].slot->fb))
            rhi_offscreen_fbo_destroy(dev, specs[i].slot);
        *specs[i].slot = fresh[i];
    }
    return true;
}
