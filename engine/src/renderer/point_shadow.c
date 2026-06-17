#include <renderer/point_shadow.h>
#include <core/log.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#define PS_DEG2RAD ((f32)(M_PI / 180.0))

/* ------------------------------------------------------------------- */
/* Internal helpers                                                    */
/* ------------------------------------------------------------------- */

static char *ps_read_file(const char *path, usize *out_len) {
    FILE *f = fopen(path, "rb");
    if (!f) return NULL;
    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    if (sz < 0) { fclose(f); return NULL; }
    fseek(f, 0, SEEK_SET);
    char *buf = (char *)malloc((usize)sz + 1u);
    if (!buf) { fclose(f); return NULL; }
    usize rd = fread(buf, 1u, (usize)sz, f);
    buf[rd] = '\0';
    fclose(f);
    if (out_len) *out_len = rd;
    return buf;
}

static RHIPipeline ps_create_pipeline(RHIDevice *dev,
                                      const char *vert_path,
                                      const char *frag_path) {
    usize vs_len = 0, fs_len = 0;
    char *vs_src = ps_read_file(vert_path, &vs_len);
    char *fs_src = ps_read_file(frag_path, &fs_len);
    if (!vs_src || !fs_src) {
        LOG_WARN("PointShadow: shader sources not found (%s, %s)",
                 vert_path, frag_path);
        free(vs_src);
        free(fs_src);
        return RHI_HANDLE_NULL;
    }

    RHIShader vs = rhi_shader_create(dev, vs_src, vs_len, false);
    RHIShader fs = rhi_shader_create(dev, fs_src, fs_len, true);
    free(vs_src);
    free(fs_src);

    if (!rhi_handle_valid(vs) || !rhi_handle_valid(fs)) {
        LOG_WARN("PointShadow: shader compile failed");
        if (rhi_handle_valid(vs)) rhi_shader_destroy(dev, vs);
        if (rhi_handle_valid(fs)) rhi_shader_destroy(dev, fs);
        return RHI_HANDLE_NULL;
    }

    RHIPipelineDesc desc = {
        .vert = vs,
        .frag = fs,
        .depth_write_disable = false,
        .is_shadow_depth = true,
    };
    RHIPipeline pipe = rhi_pipeline_create(dev, &desc);
    rhi_shader_destroy(dev, vs);
    rhi_shader_destroy(dev, fs);
    return pipe;
}

/* Build the 6 view-projection matrices for an omnidirectional shadow camera.
 * Analytical construction: cubemap face directions are axis-aligned, so the
 * combined VP = proj × view matrices have at most 2 non-zero rows with ≤4
 * non-zero entries each. Eliminates 6× mat4_lookat (12 normalize + 24 cross)
 * and 6× mat4_mul (384 muls + 384 adds) → 6× memset + 24 assignments. */
void point_shadow_compute_face_vp(Vec3 light_pos, f32 radius,
                                  Mat4 out_vp[POINT_SHADOW_FACES]) {
    f32 far_plane = (radius > 0.1f) ? radius : 0.1f;
    f32 near_val = 0.1f;
    f32 fn = far_plane - near_val;
    f32 pzz = -(far_plane + near_val) / fn;
    f32 pwz = -(2.0f * far_plane * near_val) / fn;
    f32 px = light_pos.e[0], py = light_pos.e[1], pz = light_pos.e[2];

    /* +X: right=(0,0,1), up=(0,1,0), fwd=(1,0,0)
     * NOTE: Uses right-handed convention (right = cross(f,up)), which differs from
     * camera_view / mat4_lookat left-handed convention (right = -cross(f,up)).
     * Self-consistent since same VP used for rendering + sampling; depth computed
     * via length() in shader, not VP decomposition. */
    memset(&out_vp[0], 0, sizeof(Mat4));
    out_vp[0].e[1][1] = 1.0f;   out_vp[0].e[1][3] = -py;
    out_vp[0].e[2][0] = -pzz;  out_vp[0].e[2][3] = pzz * px - pwz;

    /* -X: right=(0,0,-1), up=(0,1,0), fwd=(-1,0,0) */
    memset(&out_vp[1], 0, sizeof(Mat4));
    out_vp[1].e[1][1] = 1.0f;   out_vp[1].e[1][3] = -py;
    out_vp[1].e[2][0] = pzz;   out_vp[1].e[2][3] = -pzz * px - pwz;

    /* +Y: right=(1,0,0), up=(0,0,-1), fwd=(0,1,0) */
    memset(&out_vp[2], 0, sizeof(Mat4));
    out_vp[2].e[0][0] = 1.0f;   out_vp[2].e[0][3] = -px;
    out_vp[2].e[2][1] = -pzz;  out_vp[2].e[2][3] = pzz * py - pwz;

    /* -Y: right=(1,0,0), up=(0,0,1), fwd=(0,-1,0) */
    memset(&out_vp[3], 0, sizeof(Mat4));
    out_vp[3].e[0][0] = 1.0f;   out_vp[3].e[0][3] = -px;
    out_vp[3].e[2][1] = pzz;   out_vp[3].e[2][3] = -pzz * py - pwz;

    /* +Z: right=(1,0,0), up=(0,1,0), fwd=(0,0,1) */
    memset(&out_vp[4], 0, sizeof(Mat4));
    out_vp[4].e[0][0] = 1.0f;   out_vp[4].e[0][3] = -px;
    out_vp[4].e[2][2] = -pzz;  out_vp[4].e[2][3] = pzz * pz - pwz;

    /* -Z: right=(-1,0,0), up=(0,1,0), fwd=(0,0,-1) */
    memset(&out_vp[5], 0, sizeof(Mat4));
    out_vp[5].e[0][0] = -1.0f;  out_vp[5].e[0][3] = px;
    out_vp[5].e[2][2] = pzz;   out_vp[5].e[2][3] = -pzz * pz - pwz;
}

/* ------------------------------------------------------------------- */
/* Lifecycle                                                           */
/* ------------------------------------------------------------------- */

void point_shadow_init(PointShadowSystem *sys, RHIDevice *dev, u32 resolution) {
    if (!sys || !dev) return;
    memset(sys, 0, sizeof(*sys));
    sys->device = dev;
    sys->resolution = (resolution == 0u) ? POINT_SHADOW_DEFAULT_RES : resolution;

    for (u32 i = 0u; i < POINT_SHADOW_MAX_LIGHTS; ++i) {
        sys->lights[i].shadow_index = 0xFFu;
        sys->far_planes[i] = 25.0f;
    }

    /* Allocate one depth cubemap FBO per light (6 faces each). */
    for (u32 i = 0u; i < POINT_SHADOW_MAX_LIGHTS; ++i) {
        sys->cubemap_fbos[i] = rhi_cubemap_depth_fbo_create(dev, sys->resolution);
    }

    /* Depth-only pipeline: linear distance is written by the fragment shader. */
#ifdef ENGINE_VULKAN
    sys->depth_pipeline = ps_create_pipeline(dev,
        "shaders/point_shadow_depth_vk.vert",
        "shaders/point_shadow_depth_vk.frag");
#else
    sys->depth_pipeline = ps_create_pipeline(dev,
        "shaders/point_shadow_depth.vert",
        "shaders/point_shadow_depth.frag");
#endif

    if (rhi_handle_valid(sys->depth_pipeline)) {
        sys->loc_model      = rhi_pipeline_get_uniform_location(dev, sys->depth_pipeline, "u_model");
        sys->loc_mvp        = rhi_pipeline_get_uniform_location(dev, sys->depth_pipeline, "u_mvp");
        sys->loc_light_pos  = rhi_pipeline_get_uniform_location(dev, sys->depth_pipeline, "u_light_pos");
        sys->loc_far_plane  = rhi_pipeline_get_uniform_location(dev, sys->depth_pipeline, "u_far_plane");
    } else {
        sys->loc_model = sys->loc_mvp = sys->loc_light_pos = sys->loc_far_plane = -1;
        LOG_WARN("PointShadow: depth pipeline creation failed (shaders missing?)");
    }

    /* Sampler for cubemap-style sampling (clamped, linear). */
    RHISamplerDesc sd = {
        .min_filter = RHI_FILTER_LINEAR,
        .mag_filter = RHI_FILTER_LINEAR,
        .wrap_u = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_v = RHI_WRAP_CLAMP_TO_EDGE,
        .wrap_w = RHI_WRAP_CLAMP_TO_EDGE,
    };
    sys->sampler = rhi_sampler_create(dev, &sd);

    sys->ready = true;
    LOG_INFO("PointShadow: initialized (%u lights x 6 faces @ %ux%u)",
             POINT_SHADOW_MAX_LIGHTS, sys->resolution, sys->resolution);
}

void point_shadow_destroy(PointShadowSystem *sys, RHIDevice *dev) {
    if (!sys || !dev) return;

    for (u32 i = 0u; i < POINT_SHADOW_MAX_LIGHTS; ++i) {
        if (rhi_handle_valid(sys->cubemap_fbos[i].fb)) {
            rhi_cubemap_depth_fbo_destroy(dev, &sys->cubemap_fbos[i]);
        }
    }
    if (rhi_handle_valid(sys->sampler))         rhi_sampler_destroy(dev, sys->sampler);
    if (rhi_handle_valid(sys->depth_pipeline))  rhi_pipeline_destroy(dev, sys->depth_pipeline);

    memset(sys, 0, sizeof(*sys));
}

/* ------------------------------------------------------------------- */
/* Per-frame light selection                                           */
/* ------------------------------------------------------------------- */

typedef struct {
    u32 src_index;
    f32 priority;   /* lower is better (distance to camera) */
} PSCandidate;

void point_shadow_update(PointShadowSystem *sys,
                         const Vec3 *positions, const f32 *radii,
                         u32 light_count, Vec3 camera_pos) {
    if (!sys || !sys->ready) return;

    /* Reset stale state. */
    for (u32 i = 0u; i < POINT_SHADOW_MAX_LIGHTS; ++i) {
        sys->lights[i].shadow_index = 0xFFu;
        sys->lights[i].src_index    = 0xFFu;
    }
    sys->active_count = 0u;
    if (light_count == 0u || !positions || !radii) return;

    /* Score by squared distance to camera and pick the closest N.
     * Use inline partial insertion sort instead of qsort: for k=8 from n≤256,
     * this avoids function-pointer overhead and only sorts what we need. */
    static PSCandidate cand[256];
    u32 cap = (u32)(sizeof(cand) / sizeof(cand[0]));
    u32 n = (light_count < cap) ? light_count : cap;
    for (u32 i = 0u; i < n; ++i) {
        Vec3 d = vec3_sub(positions[i], camera_pos);
        cand[i].src_index = i;
        cand[i].priority  = vec3_dot(d, d);
    }

    u32 take = (n < POINT_SHADOW_MAX_LIGHTS) ? n : POINT_SHADOW_MAX_LIGHTS;

    if (n <= POINT_SHADOW_MAX_LIGHTS) {
        /* Full insertion sort on small array (n ≤ 8) — faster than qsort */
        for (u32 i = 1u; i < n; ++i) {
            PSCandidate key = cand[i];
            u32 j = i;
            while (j > 0u && cand[j - 1u].priority > key.priority) {
                cand[j] = cand[j - 1u];
                --j;
            }
            cand[j] = key;
        }
    } else {
        /* Partial insertion sort: maintain sorted top-take from n candidates */
        for (u32 i = 1u; i < take; ++i) {
            PSCandidate key = cand[i];
            u32 j = i;
            while (j > 0u && cand[j - 1u].priority > key.priority) {
                cand[j] = cand[j - 1u];
                --j;
            }
            cand[j] = key;
        }
        for (u32 i = take; i < n; ++i) {
            if (cand[i].priority >= cand[take - 1u].priority) continue;
            PSCandidate key = cand[i];
            u32 j = take - 1u;
            while (j > 0u && cand[j - 1u].priority > key.priority) {
                cand[j] = cand[j - 1u];
                --j;
            }
            cand[j] = key;
        }
    }

    sys->active_count = take;

    for (u32 slot = 0u; slot < take; ++slot) {
        u32 si = cand[slot].src_index;
        f32 r  = (radii[si] > 0.1f) ? radii[si] : 25.0f;
        Vec3 p = positions[si];

        sys->lights[slot].position     = p;
        sys->lights[slot].radius       = r;
        sys->lights[slot].shadow_index = slot;
        sys->lights[slot].src_index    = si;
        sys->far_planes[slot]          = r;

        static Mat4 face_vp[POINT_SHADOW_FACES];
        point_shadow_compute_face_vp(p, r, face_vp);
        for (u32 f = 0u; f < POINT_SHADOW_FACES; ++f) {
            sys->light_vp[slot * POINT_SHADOW_FACES + f] = face_vp[f];
        }
    }
}

/* ------------------------------------------------------------------- */
/* Depth render passes                                                 */
/* ------------------------------------------------------------------- */

void point_shadow_render_begin(PointShadowSystem *sys, RHICmdBuffer *cmd,
                               u32 light_index, u32 face) {
    if (!sys || !sys->ready || !cmd) return;
    if (light_index >= sys->active_count || face >= POINT_SHADOW_FACES) return;
    if (!rhi_handle_valid(sys->depth_pipeline)) return;

    RHICubemapDepthFBO *cfbo = &sys->cubemap_fbos[light_index];
    if (!rhi_handle_valid(cfbo->fb)) return;

    rhi_cubemap_depth_fbo_bind_face(cmd, cfbo, face);
    rhi_cmd_bind_pipeline(cmd, sys->depth_pipeline);

    u32 idx = light_index * POINT_SHADOW_FACES + face;

    /* Default model = identity. The caller may override per draw. */
    static const Mat4 identity = { .e = {
        {1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1}
    }};
    if (sys->loc_model >= 0)
        rhi_cmd_set_uniform_mat4(cmd, sys->loc_model, &identity.e[0][0]);
    if (sys->loc_mvp >= 0)
        rhi_cmd_set_uniform_mat4(cmd, sys->loc_mvp,
                                 &sys->light_vp[idx].e[0][0]);
    if (sys->loc_light_pos >= 0) {
        Vec3 lp = sys->lights[light_index].position;
        rhi_cmd_set_uniform_vec3(cmd, sys->loc_light_pos,
                                 lp.e[0], lp.e[1], lp.e[2]);
    }
    if (sys->loc_far_plane >= 0)
        rhi_cmd_set_uniform_f32(cmd, sys->loc_far_plane,
                                sys->far_planes[light_index]);
}

void point_shadow_render_end(PointShadowSystem *sys, RHICmdBuffer *cmd,
                             u32 screen_w, u32 screen_h) {
    if (!sys || !cmd) return;
    rhi_cubemap_depth_fbo_unbind(cmd, screen_w, screen_h);
}

/* ------------------------------------------------------------------- */
/* Sampling-time binding                                               */
/* ------------------------------------------------------------------- */

void point_shadow_bind(PointShadowSystem *sys, RHICmdBuffer *cmd, u32 slot) {
    if (!sys || !sys->ready || !cmd) return;
    if (!rhi_handle_valid(sys->sampler)) return;

    /* Bind each active light's depth cubemap as a single texture.
     * The PBR shader samples the cubemap directly using the light-to-fragment
     * direction vector instead of 6 individual 2D face textures. */
    u32 unit = slot;
    for (u32 li = 0u; li < sys->active_count; ++li) {
        RHICubemapDepthFBO *cfbo = &sys->cubemap_fbos[li];
        if (!rhi_handle_valid(cfbo->depth_tex)) continue;
        rhi_cmd_bind_texture(cmd, cfbo->depth_tex, sys->sampler, unit++);
    }
}
