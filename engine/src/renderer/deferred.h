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

typedef enum {
    RENDER_PATH_FORWARD  = 0,
    RENDER_PATH_DEFERRED = 1,
} RenderPath;

#define DEFERRED_MAX_POINT_LIGHTS 8u

/* R580: capacity of the per-layer MR factor table consumed by the
 * texture-array G-Buffer variant (gbuffer_arr*). Must equal
 * MAT_ARR_MAX_LAYERS (main.c) — main.c static-asserts this. */
#define DEFERRED_MR_FACTOR_MAX_LAYERS 64u

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
    /* R560: skinned G-Buffer variant -- same MRT outputs as gbuffer_pipeline
     * but with the 64B skinned vertex layout and per-joint current/previous
     * pose texel fetch (per-object velocity for skinned geometry). */
    RHIPipeline gbuffer_skinned_pipeline;
    RHIPipeline lighting_pipeline;    /* Full-screen quad: G-Buffer -> shaded. */
    /* R442: texture-array G-Buffer variant (gbuffer_arr*) for the
     * material-indirect single-execute mega draw. Invalid handle disables
     * that path (the caller falls back to the per-group loop). */
    RHIPipeline gbuffer_arr_pipeline;

    u32  width;
    u32  height;
    bool initialized;

    /* ---- Internal fields (do not touch from application code). ---- */
    RHIMRTFBO       _mrt_fbo;     /* single MRT with 3 color + shared depth  */
    RHISampler      _gbuf_sampler;
    RHISampler      _linear_sampler; /* LINEAR/CLAMP for shadow cubemaps on GL */

    /* Cached G-Buffer pass uniform locations (-1 if absent). */
    i32 _loc_gbuf_model;
    i32 _loc_gbuf_view;
    i32 _loc_gbuf_proj;
    i32 _loc_gbuf_prev_mvp;

    /* R442: cached uniform locations of gbuffer_arr_pipeline (-1 if absent). */
    i32 _loc_gbuf_arr_model;
    i32 _loc_gbuf_arr_view;
    i32 _loc_gbuf_arr_proj;
    i32 _loc_gbuf_arr_prev_mvp;

    /* R560: cached uniform locations of gbuffer_skinned_pipeline (-1 if absent). */
    i32 _loc_gbuf_skinned_model;
    i32 _loc_gbuf_skinned_view;
    i32 _loc_gbuf_skinned_proj;
    i32 _loc_gbuf_skinned_prev_mvp;

    /* R580: per-material glTF metallic/roughness factor channel for the
     * G-Buffer pass. The gbuffer vertex stage already fills all 256B of
     * push-constant space (R204-A), so factors ride the backend's auxiliary
     * uniform buffer instead (GL binding 0 / VK aux UBO set). Double-buffered
     * single-factor UBO serves the base/skinned pipelines (rebound per
     * material); the fixed-capacity vec4-strided array UBO serves the
     * gbuffer_arr single-execute path (indexed by v_layer). */
    RHIBuffer _mr_factor_buf[2];
    RHIBuffer _mr_factor_arr_buf;
    f32       _mr_factor_arr[DEFERRED_MR_FACTOR_MAX_LAYERS][4];
    bool      _mr_factor_arr_dirty;

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
    i32 _loc_point_shadow_far_planes;
} DeferredSystem;

void deferred_init(DeferredSystem *sys, RHIDevice *dev, u32 width, u32 height);
void deferred_destroy(DeferredSystem *sys, RHIDevice *dev);
void deferred_resize(DeferredSystem *sys, RHIDevice *dev, u32 width, u32 height);

/* G-Buffer pass: bind FBO, clear, then caller renders opaque geometry
 * using `gbuffer_pipeline`. The caller must pass the active command buffer
 * obtained from `rhi_frame_begin`. */
void deferred_begin_gbuffer(DeferredSystem *sys, RHIDevice *dev, RHICmdBuffer *cmd);
void deferred_end_gbuffer(DeferredSystem *sys, RHIDevice *dev, RHICmdBuffer *cmd);

/* R580: G-Buffer metallic/roughness factor channel — the deferred
 * counterpart of R579's forward u_mr_factor (glTF composes texture x
 * factor). Backed by the auxiliary uniform buffer, never push constants.
 *
 * deferred_bind_gbuffer_mr_factor(): call after bind_material, before each
 * draw group of the G-Buffer pass; pass (1,1) for fallback/textureless
 * materials. The single-factor UBO is double-buffered by frame index.
 *
 * deferred_set_gbuffer_mr_factor_array(): CPU-side stage of the per-layer
 * factor table for the texture-array (mega single-execute) path — xy pairs,
 * count clamped to DEFERRED_MR_FACTOR_MAX_LAYERS, layer 0 = fallback (1,1).
 * deferred_bind_gbuffer_mr_factor_array(): uploads when dirty, then binds;
 * call once before the arr execute. All entries are safe no-ops when the
 * deferred system is uninitialized or the buffers are absent. */
void deferred_bind_gbuffer_mr_factor(DeferredSystem *sys, RHIDevice *dev, RHICmdBuffer *cmd,
                                     f32 metallic_factor, f32 roughness_factor);
void deferred_set_gbuffer_mr_factor_array(DeferredSystem *sys, const f32 *mr_factors_xy, u32 count);
void deferred_bind_gbuffer_mr_factor_array(DeferredSystem *sys, RHICmdBuffer *cmd);

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
                            u32 psc_count, const RHITexture *psc_tex, const f32 *psc_far_planes,
                            f32 near_plane, f32 far_plane, f32 shadow_bias,
                            const f32 *view_mat, const f32 *camera_data,
                            RHITexture ssao_tex);

#endif /* DEFERRED_H */
