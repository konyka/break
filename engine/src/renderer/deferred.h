#ifndef DEFERRED_H
#define DEFERRED_H

/* ----------------------------------------------------------------------------
 * Deferred rendering path.
 *
 * Provides an optional G-Buffer + screen-space lighting pipeline that mirrors
 * the existing forward `pbr_clustered` path. The forward path remains the
 * default: nothing here is invoked unless the application explicitly switches
 * RenderPath to RENDER_PATH_DEFERRED and drives the begin/lighting helpers.
 *
 * G-Buffer layout:
 *   RT0  R8G8B8A8_UNORM        rgb = albedo,        a = metallic
 *   RT1  R16G16B16A16_SFLOAT   rg  = octahedron-encoded normal (b/a spare)
 *   RT2  R8G8B8A8_UNORM        r   = roughness,     g = ao,
 *                              b   = emissive flag, a = spare
 *   RT3  R16G16B16A16_SFLOAT   rg  = screen-space velocity (NDC delta)
 *   D    D32_FLOAT             scene depth (re-used for position reconstruction)
 *
 * The G-Buffer is backed by a single MRT (Multiple Render Targets) FBO
 * that writes all three color attachments in one geometry pass, plus a
 * shared depth attachment used for position reconstruction.
 * -------------------------------------------------------------------------- */

#include "../rhi/rhi.h"
#include "../core/types.h"
#include "point_shadow.h"

typedef enum {
    RENDER_PATH_FORWARD  = 0,
    RENDER_PATH_DEFERRED = 1,
} RenderPath;

#define DEFERRED_MAX_POINT_LIGHTS 8u

typedef struct {
    /* G-Buffer textures (publicly readable, used as inputs by lighting pass). */
    RHITexture gbuf_albedo_metallic;  /* RGBA8: rgb=albedo, a=metallic         */
    RHITexture gbuf_normal;           /* RG16F-equivalent: oct-encoded normal  */
    RHITexture gbuf_roughness_ao;     /* RGBA8: r=roughness g=ao b=emissive    */
    RHITexture gbuf_velocity;         /* RG16F-equivalent: NDC motion vector    */
    RHITexture gbuf_depth;            /* D32F: shared with depth attachment    */

    /* Primary G-Buffer MRT handle. */
    RHIFramebuffer gbuf_fbo;

    /* Pipelines. */
    RHIPipeline gbuffer_pipeline;     /* G-Buffer write (geometry pass).       */
    RHIPipeline lighting_pipeline;    /* Full-screen quad: G-Buffer -> shaded. */

    u32  width;
    u32  height;
    bool initialized;

    /* ---- Internal fields (do not touch from application code). ---- */
    RHIMRTFBO       _mrt_fbo;     /* single MRT with 3 color + shared depth  */
    RHISampler      _gbuf_sampler;

    /* Cached G-Buffer pass uniform locations (-1 if absent). */
    i32 _loc_gbuf_model;
    i32 _loc_gbuf_view;
    i32 _loc_gbuf_proj;
    i32 _loc_gbuf_prev_vp;

    /* Cached lighting-pass uniform locations (-1 if absent). */
    i32 _loc_inv_vp;
    i32 _loc_view;
    i32 _loc_camera_pos;
    i32 _loc_screen_w;
    i32 _loc_screen_h;
    i32 _loc_near;
    i32 _loc_far;
    i32 _loc_shadow_bias;
    i32 _loc_point_count;
    i32 _loc_dir_count;
    i32 _loc_point_shadow_count;
    i32 _loc_point_shadow_light_0;
    i32 _loc_point_shadow_light_1;
    i32 _loc_point_shadow_light_2;
    i32 _loc_point_shadow_light_3;
} DeferredSystem;

void deferred_init(DeferredSystem *sys, RHIDevice *dev, u32 width, u32 height);
void deferred_destroy(DeferredSystem *sys, RHIDevice *dev);
void deferred_resize(DeferredSystem *sys, RHIDevice *dev, u32 width, u32 height);

/* G-Buffer pass: bind FBO, clear, then caller renders opaque geometry
 * using `gbuffer_pipeline`. The caller must pass the active command buffer
 * obtained from `rhi_frame_begin`. */
void deferred_begin_gbuffer(DeferredSystem *sys, RHIDevice *dev, RHICmdBuffer *cmd);
void deferred_end_gbuffer(DeferredSystem *sys, RHIDevice *dev, RHICmdBuffer *cmd);

/* Deferred lighting pass: full-screen triangle that decodes the G-Buffer
 * and runs the same Cook-Torrance + clustered-lighting evaluation as the
 * forward path. `light_data` is the LightSystem-side packed buffer (may
 * be NULL when the engine drives its own light upload), `shadow_map` is
 * the cascaded shadow texture, and `camera_data` provides camera UBO
 * bytes (inv_vp + camera position) -- pass NULL to leave the previously
 * uploaded values intact. */
void deferred_lighting_pass(DeferredSystem *sys, RHIDevice *dev, RHICmdBuffer *cmd,
                            RHIBuffer light_data_buf, RHIBuffer light_grid_buf,
                            u32 point_count, u32 dir_count,
                            RHITexture shadow_map,
                            RHITexture brdf_lut, RHICubemap irradiance, RHICubemap prefilter,
                            const PointShadowSystem *pt_shadows,
                            f32 near_plane, f32 far_plane, f32 shadow_bias,
                            const f32 *view_mat, const f32 *camera_data);

#endif /* DEFERRED_H */
