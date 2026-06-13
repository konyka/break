#ifndef POINT_SHADOW_H
#define POINT_SHADOW_H

#include <rhi/rhi.h>
#include <math/math.h>
#include <core/types.h>

#define POINT_SHADOW_MAX_LIGHTS  8u
#define POINT_SHADOW_DEFAULT_RES 512u
#define POINT_SHADOW_FACES       6u

typedef struct {
    Vec3 position;
    f32  radius;        /* light range, used as far plane */
    u32  shadow_index;  /* cubemap slot (0xFF = no shadow) */
    u32  src_index;     /* index in LightSystem point light array */
} PointLightShadow;

typedef struct {
    /* RHI resources --------------------------------------------------------
     * Each active light owns a depth cubemap FBO (6-face depth texture).
     * The old per-face 2D shadow map fallback has been replaced by native
     * RHICubemapDepthFBO which the RHI now exposes. */
    RHICubemapDepthFBO cubemap_fbos[POINT_SHADOW_MAX_LIGHTS];
    RHIPipeline  depth_pipeline;
    RHISampler   sampler;

    /* Configuration / state */
    u32 resolution;
    u32 active_count;

    PointLightShadow lights[POINT_SHADOW_MAX_LIGHTS];
    Mat4 light_vp[POINT_SHADOW_MAX_LIGHTS * POINT_SHADOW_FACES]; /* 6 VP per light */
    f32  far_planes[POINT_SHADOW_MAX_LIGHTS];

    /* Cached uniform locations for the depth pipeline */
    i32 loc_model;
    i32 loc_mvp;
    i32 loc_light_pos;
    i32 loc_far_plane;

    RHIDevice *device;
    bool       ready;
} PointShadowSystem;

/* Lifecycle */
void point_shadow_init(PointShadowSystem *sys, RHIDevice *dev, u32 resolution);
void point_shadow_destroy(PointShadowSystem *sys, RHIDevice *dev);

/* Update list of active shadow-casting point lights (selects the closest to camera).
 * positions/radii are arrays of size `light_count`. Computes 6 VP matrices per
 * selected light and stores them in `sys->light_vp`. */
void point_shadow_update(PointShadowSystem *sys,
                         const Vec3 *positions, const f32 *radii,
                         u32 light_count, Vec3 camera_pos);

/* Per-light per-face depth pass. Binds the matching cubemap face attachment
 * and viewport, uploads the per-face VP matrix and the light position /
 * far plane uniforms. `light_index` in [0, active_count), `face` in [0, 6). */
void point_shadow_render_begin(PointShadowSystem *sys, RHICmdBuffer *cmd,
                               u32 light_index, u32 face);
void point_shadow_render_end(PointShadowSystem *sys, RHICmdBuffer *cmd,
                             u32 screen_w, u32 screen_h);

/* Push the cubemap depth textures + sampler to the requested unit base.
 * `slot` is the starting texture unit; up to active_count units are consumed. */
void point_shadow_bind(PointShadowSystem *sys, RHICmdBuffer *cmd, u32 slot);

/* Helpers (also used by point_shadow_update internally). */
void point_shadow_compute_face_vp(Vec3 light_pos, f32 radius,
                                  Mat4 out_vp[POINT_SHADOW_FACES]);

#endif /* POINT_SHADOW_H */
