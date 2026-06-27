#include <engine.h>
#include <rhi/rhi.h>
#include <renderer/camera.h>
#include <renderer/cull.h>
#include <renderer/frustum_cull.h>
#include <renderer/skybox.h>
#include <renderer/particles.h>
#include <renderer/terrain.h>
#include <renderer/water.h>
#include <renderer/lighting.h>
#include <renderer/post_process.h>
#include <renderer/ssao.h>
#include <renderer/taa.h>
#include <renderer/ssr.h>
#include <renderer/dof.h>
#include <renderer/volumetric.h>
#include <renderer/tonemap.h>
#include <renderer/deferred.h>
#include <renderer/point_shadow.h>
#include <renderer/fxaa.h>
#include <renderer/ssgi.h>
#include <renderer/lens_flare.h>
#include <renderer/sharpen.h>
#include <renderer/motion_blur.h>
#include <renderer/contact_shadow.h>
#include <renderer/sss.h>
#include <renderer/upscale.h>
#include <renderer/color_grade.h>
#include <renderer/god_rays.h>
#include <renderer/debug_viz.h>
#include <renderer/lens_effects.h>
#include <renderer/cinematic.h>
#include <renderer/lod.h>
#include <renderer/combined_post_process.h>
#include <renderer/forward_velocity.h>
#include <renderer/occlusion_cull.h>
#include <scene/scene_serial.h>
#include <renderer/indirect_draw.h>
#include <renderer/gpucull.h>
#include <asset/asset.h>
#include <asset/hotreload.h>
#include <asset/async_loader.h>
#include <asset/vfs.h>
#include <ecs/ecs.h>
#include <ecs/ecs_system.h>
#include <physics/physics.h>
#include <physics/character.h>
#include <task/task.h>
#include <audio/audio.h>
#include <audio/audio_stream.h>
#include <ui/debug_ui.h>
#include <ui/imgui.h>
#include <platform/input.h>
#include <platform/time.h>
#include <asset/mipmap_stream.h>
#include <core/alloc.h>
#include <script/script.h>
#include <script/script_lua.h>
#include <animation/skeleton.h>
#include <animation/animation.h>
#include <network/net_replication.h>
#include <network/network.h>
#include <core/log.h>
#include <core/profiler.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

/* Returns a newly-allocated copy of `src` with `#define <name> 1` inserted
 * immediately after the first line (the `#version` directive, which must remain
 * first).  Caller frees the result.  On allocation failure returns NULL. */
static char *shader_inject_define(const char *src, usize len, const char *name, usize *out_len) {
    if (!src || !name) return NULL;
    const char *nl = memchr(src, '\n', len);
    usize head = nl ? (usize)(nl - src) + 1u : len; /* include the newline */
    int def_raw = snprintf(NULL, 0, "#define %s 1\n", name);
    if (def_raw < 0) return NULL;
    usize def_len = (usize)def_raw;
    char *out = (char *)malloc(len + def_len + 1u);
    if (!out) return NULL;
    memcpy(out, src, head);
    int n = snprintf(out + head, def_len + 1u, "#define %s 1\n", name);
    if (n < 0) { free(out); return NULL; }
    memcpy(out + head + (usize)n, src + head, len - head);
    out[head + (usize)n + (len - head)] = '\0';
    if (out_len) *out_len = head + (usize)n + (len - head);
    return out;
}

static int cmp_f32(const void *a, const void *b) {
    f32 fa = *(const f32 *)a, fb = *(const f32 *)b;
    return (fa > fb) - (fa < fb);
}

static void save_bmp(const char *path, u32 w, u32 h, const u8 *rgb) {
    u32 row_sz = w * 3;
    u32 pad = (4 - (row_sz % 4)) % 4;
    u32 stride = row_sz + pad;
    u32 img_sz = stride * h;
    u8 hdr[54] = {0};
    hdr[0] = 'B'; hdr[1] = 'M';
    u32 fsize = 54 + img_sz;
    memcpy(hdr + 2, &fsize, 4);
    hdr[10] = 54; hdr[14] = 40;
    memcpy(hdr + 18, &w, 4);
    memcpy(hdr + 22, &h, 4);
    hdr[26] = 1; hdr[28] = 24;
    memcpy(hdr + 34, &img_sz, 4);
    memcpy(hdr + 38, &(u32){2835}, 4);
    memcpy(hdr + 42, &(u32){2835}, 4);
    FILE *f = fopen(path, "wb");
    if (!f) return;
    bool bmp_ok = fwrite(hdr, 1, 54, f) == 54;
    u8 padding[3] = {0};
    for (u32 y = 0; y < h && bmp_ok; y++) {
        const u8 *row = rgb + (h - 1 - y) * row_sz;
        bmp_ok = fwrite(row, 1, row_sz, f) == row_sz;
        if (bmp_ok && pad) bmp_ok = fwrite(padding, 1, pad, f) == (usize)pad;
    }
    fclose(f);
    if (!bmp_ok) LOG_WARN("BMP write: partial write failure for %s", path);
}

enum {
    COMP_TRANSFORM   = 1,
    COMP_RIGID_BODY  = 2,
    COMP_MESH_REF    = 3,
};

typedef struct { f32 pos[3]; } CTransform;
typedef struct { u32 physics_id; } CRigidBody;
typedef struct { u32 mesh_index; } CMeshRef;

/* ECS system: copy simulated rigid-body positions back into transforms and
 * respawn anything that fell out of the world. Each entity touches only its own
 * physics body (unique physics_id), so chunks dispatch safely across workers. */
static void sys_sync_transform_from_physics(EcsChunkView *v, void *user) {
    PhysicsWorld *physics = (PhysicsWorld *)user;
    CTransform *xs = (CTransform *)ecs_chunk_column(v, COMP_TRANSFORM);
    CRigidBody *rs = (CRigidBody *)ecs_chunk_column(v, COMP_RIGID_BODY);
    if (!xs || !rs) return;
    for (u32 i = 0; i < v->count; i++) {
        u32 pid = rs[i].physics_id;
        if (pid > 0 && pid < physics->count) {
            xs[i].pos[0] = physics->bodies[pid].position.e[0];
            xs[i].pos[1] = physics->bodies[pid].position.e[1];
            xs[i].pos[2] = physics->bodies[pid].position.e[2];
            if (xs[i].pos[1] < -20.0f) {
                xs[i].pos[0] = 0.0f; xs[i].pos[1] = 5.0f; xs[i].pos[2] = 0.0f;
                physics->bodies[pid].position = vec3(0.0f, 5.0f, 0.0f);
                physics->bodies[pid].velocity = vec3(0.0f, 0.0f, 0.0f);
            }
        }
    }
}

static char *file_read_full(const char *path, usize *out_len) {
    FILE *f = fopen(path, "rb");
    if (!f) return NULL;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return NULL; }
    long sz = ftell(f);
    if (sz < 0) { fclose(f); return NULL; }
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return NULL; }
    char *buf = malloc((usize)sz + 1);
    if (!buf) { fclose(f); return NULL; }
    usize read = fread(buf, 1, (usize)sz, f);
    buf[read] = '\0';
    fclose(f);
    if (out_len) *out_len = read;
    return buf;
}

#include <renderer/lighting.h>
#include <renderer/ibl.h>

typedef struct {
    RHIDevice    *device;
    RHIPipeline   pipeline;
    RHIPipeline   clustered_pipeline;
    RHIPipeline   instanced_pipeline;
    RHIPipeline   skinned_pipeline;
    RHIPipeline   wire_pipeline;
    RHIPipeline   wire_instanced_pipeline;
    RHIPipeline   wire_skinned_pipeline;
    RHIBuffer     instance_buf;
    RHISampler    sampler;
    RHISampler    nearest_sampler;
    RHITexture    fallback_tex;
    RHITexture    fallback_mr;
    RHITexture    fallback_normal;
    RHITexture    fallback_emissive;
    RHITexture    terrain_tex;
    RHIShadowMap  shadow_map;   /* 2048x2048 CSM atlas: 4 cascades in 2x2 quadrants */
    RHIPipeline   depth_pipeline;
    Mat4          cascade_vp[4];
    f32           cascade_splits[5];
    f32           cascade_scale[4];
    f32           cascade_offset[4];
    Skeleton      skeleton;
    AnimClip      anim_clip;
    RHIBuffer     skinned_vbo;
    RHIBuffer     skinned_ibo;
    u32           skinned_index_count;
    i32 loc_model, loc_view, loc_proj;
    i32 loc_light_dir, loc_light_color, loc_ambient, loc_camera_pos;
    i32 loc_albedo, loc_shadow_map, loc_light_vp;
    i32 cl_loc_model, cl_loc_view, cl_loc_proj, cl_loc_camera_pos;
    i32 cl_loc_ambient, cl_loc_screen_w, cl_loc_screen_h, cl_loc_near, cl_loc_far;
    i32 cl_loc_point_count, cl_loc_dir_count;
    i32 cl_loc_shadow_bias;
    i32 cl_loc_fog_color, cl_loc_fog_near, cl_loc_fog_far, cl_loc_underwater;
    i32 cl_loc_point_shadow_far_planes;
    i32 cl_loc_pom_enabled;
    i32 inst_loc_view, inst_loc_proj;
    i32 inst_loc_light_dir, inst_loc_light_color, inst_loc_ambient, inst_loc_camera_pos;
    i32 sk_loc_view, sk_loc_proj;
    i32 sk_loc_light_dir, sk_loc_light_color, sk_loc_ambient, sk_loc_camera_pos;
    i32 depth_loc_model, depth_loc_lvp;
    RHITexture     ssao_tex;
    DeferredSystem  deferred;
    RenderPath      render_path;
    IBLSystem       ibl;
} RenderState;

static bool render_init(RenderState *rs, Platform *platform) {
#ifdef ENGINE_VULKAN
    void *window = platform_surface_native(platform);
#else
    void *window = platform_window_native(platform);
#endif
    void *display = platform_display_native(platform);
    u32 w, h;
    platform_get_size(platform, &w, &h);

    rs->device = rhi_device_create(
#ifdef ENGINE_VULKAN
        RHI_BACKEND_VULKAN,
#else
        RHI_BACKEND_OPENGL,
#endif
        window, display, w, h);
    if (!rs->device) return false;

    usize vs_len = 0, fs_len = 0;
#ifdef ENGINE_VULKAN
    char *vs_src = file_read_full("shaders/blinn_phong_vk.vert", &vs_len);
    char *fs_src = file_read_full("shaders/blinn_phong_vk.frag", &fs_len);
#else
    char *vs_src = file_read_full("shaders/blinn_phong.vert", &vs_len);
    char *fs_src = file_read_full("shaders/blinn_phong.frag", &fs_len);
#endif
    if (!vs_src || !fs_src) {
        LOG_FATAL("Failed to load shaders");
        return false;
    }

    RHIShader vs = rhi_shader_create(rs->device, vs_src, vs_len, false);
    RHIShader fs = rhi_shader_create(rs->device, fs_src, fs_len, true);
    free(vs_src);
    free(fs_src);

    if (!rhi_handle_valid(vs) || !rhi_handle_valid(fs)) return false;

    /* Scene geometry renders into the HDR offscreen FBO (R16F); pipelines must
     * be created render-pass-compatible with that color format. */
    RHIPipelineDesc pdesc = {.vert = vs, .frag = fs, .uses_textures = true,
                             .color_format = RHI_FORMAT_R16G16B16A16_SFLOAT};
    rs->pipeline = rhi_pipeline_create(rs->device, &pdesc);
    pdesc.wireframe = true;
    rs->wire_pipeline = rhi_pipeline_create(rs->device, &pdesc);
    rhi_shader_destroy(rs->device, vs);
    rhi_shader_destroy(rs->device, fs);

    if (!rhi_handle_valid(rs->pipeline)) return false;

    rs->loc_model       = rhi_pipeline_get_uniform_location(rs->device, rs->pipeline, "u_model");
    rs->loc_view        = rhi_pipeline_get_uniform_location(rs->device, rs->pipeline, "u_view");
    rs->loc_proj        = rhi_pipeline_get_uniform_location(rs->device, rs->pipeline, "u_proj");
    rs->loc_light_dir   = rhi_pipeline_get_uniform_location(rs->device, rs->pipeline, "u_light_dir");
    rs->loc_light_color = rhi_pipeline_get_uniform_location(rs->device, rs->pipeline, "u_light_color");
    rs->loc_ambient     = rhi_pipeline_get_uniform_location(rs->device, rs->pipeline, "u_ambient");
    rs->loc_camera_pos  = rhi_pipeline_get_uniform_location(rs->device, rs->pipeline, "u_camera_pos");
    rs->loc_albedo      = rhi_pipeline_get_uniform_location(rs->device, rs->pipeline, "u_albedo");

    /* Clustered lighting pipeline */
    {
        usize cvl = 0, cfl = 0;
        char *cv = NULL, *cf = NULL;
#ifdef ENGINE_VULKAN
        cv = file_read_full("shaders/pbr_clustered_vk.vert", &cvl);
        cf = file_read_full("shaders/pbr_clustered_vk.frag", &cfl);
#else
        cv = file_read_full("shaders/pbr_clustered.vert", &cvl);
        cf = file_read_full("shaders/pbr_clustered.frag", &cfl);
#endif
        if (cv && cf) {
            /* Enable the split-sum IBL path and point-light shadows for the
             * clustered forward shader. The HAS_POINT_SHADOW path declares
             * samplerCube bindings but only samples when shadow_index >= 0. */
            usize cfl_ibl = 0;
            char *cf_ibl = shader_inject_define(cf, cfl, "HAS_IBL", &cfl_ibl);
            usize cfl_ps = 0;
            char *cf_ps = cf_ibl ? shader_inject_define(cf_ibl, cfl_ibl, "HAS_POINT_SHADOW", &cfl_ps)
                                 : shader_inject_define(cf, cfl, "HAS_POINT_SHADOW", &cfl_ps);
            RHIShader cvs = rhi_shader_create(rs->device, cv, cvl, false);
            RHIShader cfs = cf_ps ? rhi_shader_create(rs->device, cf_ps, cfl_ps, true)
                                  : rhi_shader_create(rs->device, cf, cfl, true);
            free(cv); free(cf); free(cf_ibl); free(cf_ps);
            if (rhi_handle_valid(cvs) && rhi_handle_valid(cfs)) {
                RHIPipelineDesc cpd = {.vert = cvs, .frag = cfs, .uses_textures = true, .uses_texel_buffer = true, .disable_culling = true,
                                       .color_format = RHI_FORMAT_R16G16B16A16_SFLOAT};
                rs->clustered_pipeline = rhi_pipeline_create(rs->device, &cpd);
                rhi_shader_destroy(rs->device, cvs);
                rhi_shader_destroy(rs->device, cfs);
            }
        } else { free(cv); free(cf); }
    }
    if (rhi_handle_valid(rs->clustered_pipeline)) {
        rs->cl_loc_model       = rhi_pipeline_get_uniform_location(rs->device, rs->clustered_pipeline, "u_model");
        rs->cl_loc_view        = rhi_pipeline_get_uniform_location(rs->device, rs->clustered_pipeline, "u_view");
        rs->cl_loc_proj        = rhi_pipeline_get_uniform_location(rs->device, rs->clustered_pipeline, "u_proj");
        rs->cl_loc_camera_pos  = rhi_pipeline_get_uniform_location(rs->device, rs->clustered_pipeline, "u_camera_pos");
        rs->cl_loc_ambient     = rhi_pipeline_get_uniform_location(rs->device, rs->clustered_pipeline, "u_ambient");
        rs->cl_loc_screen_w    = rhi_pipeline_get_uniform_location(rs->device, rs->clustered_pipeline, "u_screen_w");
        rs->cl_loc_screen_h    = rhi_pipeline_get_uniform_location(rs->device, rs->clustered_pipeline, "u_screen_h");
        rs->cl_loc_near        = rhi_pipeline_get_uniform_location(rs->device, rs->clustered_pipeline, "u_near");
        rs->cl_loc_far         = rhi_pipeline_get_uniform_location(rs->device, rs->clustered_pipeline, "u_far");
        rs->cl_loc_point_count = rhi_pipeline_get_uniform_location(rs->device, rs->clustered_pipeline, "u_point_count");
        rs->cl_loc_dir_count   = rhi_pipeline_get_uniform_location(rs->device, rs->clustered_pipeline, "u_dir_count");
        rs->cl_loc_shadow_bias = rhi_pipeline_get_uniform_location(rs->device, rs->clustered_pipeline, "u_shadow_bias");
    rs->cl_loc_fog_color  = rhi_pipeline_get_uniform_location(rs->device, rs->clustered_pipeline, "u_fog_color");
    rs->cl_loc_fog_near   = rhi_pipeline_get_uniform_location(rs->device, rs->clustered_pipeline, "u_fog_near");
    rs->cl_loc_fog_far    = rhi_pipeline_get_uniform_location(rs->device, rs->clustered_pipeline, "u_fog_far");
    rs->cl_loc_underwater = rhi_pipeline_get_uniform_location(rs->device, rs->clustered_pipeline, "u_underwater");
    rs->cl_loc_point_shadow_far_planes = rhi_pipeline_get_uniform_location(rs->device, rs->clustered_pipeline, "u_point_shadow_far_planes");
    rs->cl_loc_pom_enabled = rhi_pipeline_get_uniform_location(rs->device, rs->clustered_pipeline, "u_pom_enabled");
    }

    RHISamplerDesc sdesc = {
        .min_filter = RHI_FILTER_LINEAR,
        .mag_filter = RHI_FILTER_LINEAR,
        .wrap_u = RHI_WRAP_REPEAT,
        .wrap_v = RHI_WRAP_REPEAT,
        .wrap_w = RHI_WRAP_REPEAT,
    };
    rs->sampler = rhi_sampler_create(rs->device, &sdesc);
    sdesc.min_filter = RHI_FILTER_NEAREST;
    sdesc.mag_filter = RHI_FILTER_NEAREST;
    rs->nearest_sampler = rhi_sampler_create(rs->device, &sdesc);

    u8 white[] = {255, 255, 255, 255};
    RHITextureDesc tdesc = { .width = 1, .height = 1, .format = RHI_FORMAT_R8G8B8A8_UNORM, .mip_levels = 1, .data = white };
    rs->fallback_tex = rhi_texture_create(rs->device, &tdesc);

    u8 mr_default[] = {255, 128, 0, 255};
    RHITextureDesc mr_desc = { .width = 1, .height = 1, .format = RHI_FORMAT_R8G8B8A8_UNORM, .mip_levels = 1, .data = mr_default };
    rs->fallback_mr = rhi_texture_create(rs->device, &mr_desc);

    u8 flat_normal[] = {128, 128, 255, 255};
    RHITextureDesc nrm_desc = { .width = 1, .height = 1, .format = RHI_FORMAT_R8G8B8A8_UNORM, .mip_levels = 1, .data = flat_normal };
    rs->fallback_normal = rhi_texture_create(rs->device, &nrm_desc);

    u8 black[] = {0, 0, 0, 255};
    RHITextureDesc em_desc = { .width = 1, .height = 1, .format = RHI_FORMAT_R8G8B8A8_UNORM, .mip_levels = 1, .data = black };
    rs->fallback_emissive = rhi_texture_create(rs->device, &em_desc);

    u8 terrain_col[] = {140, 165, 100, 255};
    RHITextureDesc ttdesc = { .width = 1, .height = 1, .format = RHI_FORMAT_R8G8B8A8_UNORM, .mip_levels = 1, .data = terrain_col };
    rs->terrain_tex = rhi_texture_create(rs->device, &ttdesc);

    /* Single 2048x2048 depth atlas; the 4 CSM cascades render into its four
     * 1024x1024 quadrants (replacing 4 separate maps + 3 wasted shadow passes). */
    rs->shadow_map = rhi_shadow_map_create(rs->device, 2048, 2048);

    rs->cascade_splits[0] = 0.1f;
    {
        f32 zn = 0.1f, zf = 100.0f;
        f32 lambda = 0.75f;
        for (int i = 1; i <= 4; i++) {
            f32 p = (f32)i / 4.0f;
            f32 log_split = zn * powf(zf / zn, p);
            f32 uni_split = zn + (zf - zn) * p;
            rs->cascade_splits[i] = lambda * log_split + (1.0f - lambda) * uni_split;
        }
    }

    {
        usize dvl = 0, dfl = 0;
        char *dv = file_read_full("shaders/depth_only.vert", &dvl);
        char *df = file_read_full("shaders/depth_only.frag", &dfl);
        if (dv && df) {
            RHIShader dvs = rhi_shader_create(rs->device, dv, dvl, false);
            RHIShader dfs = rhi_shader_create(rs->device, df, dfl, true);
            free(dv); free(df);
            if (rhi_handle_valid(dvs) && rhi_handle_valid(dfs)) {
                RHIPipelineDesc dpd = {
                    .vert = dvs, .frag = dfs,
                    .depth_write_disable = false,
                    .is_shadow_depth = true,
                };
                rs->depth_pipeline = rhi_pipeline_create(rs->device, &dpd);
                rs->depth_loc_model = rhi_pipeline_get_uniform_location(rs->device, rs->depth_pipeline, "u_model");
                rs->depth_loc_lvp   = rhi_pipeline_get_uniform_location(rs->device, rs->depth_pipeline, "u_light_vp");
                rhi_shader_destroy(rs->device, dvs);
                rhi_shader_destroy(rs->device, dfs);
            }
        }
    }

    {
        usize ivl = 0, ifl = 0;
        char *iv = NULL, *ifl_src = NULL;
#ifdef ENGINE_VULKAN
        iv = file_read_full("shaders/instanced_vk.vert", &ivl);
        ifl_src = file_read_full("shaders/instanced_vk.frag", &ifl);
#else
        iv = file_read_full("shaders/instanced.vert", &ivl);
        ifl_src = file_read_full("shaders/instanced.frag", &ifl);
#endif
        if (iv && ifl_src) {
            RHIShader ivs = rhi_shader_create(rs->device, iv, ivl, false);
            RHIShader ifs = rhi_shader_create(rs->device, ifl_src, ifl, true);
            free(iv); free(ifl_src);
            if (rhi_handle_valid(ivs) && rhi_handle_valid(ifs)) {
                RHIPipelineDesc ipd = {
                    .vert = ivs, .frag = ifs,
                    .uses_textures = true,
                    .uses_texel_buffer = true,
                    .is_instanced = true,
                    .color_format = RHI_FORMAT_R16G16B16A16_SFLOAT,
                };
                rs->instanced_pipeline = rhi_pipeline_create(rs->device, &ipd);
                ipd.wireframe = true;
                rs->wire_instanced_pipeline = rhi_pipeline_create(rs->device, &ipd);
                rhi_shader_destroy(rs->device, ivs);
                rhi_shader_destroy(rs->device, ifs);
            }
        } else { free(iv); free(ifl_src); }
    }
    if (rhi_handle_valid(rs->instanced_pipeline)) {
        rs->inst_loc_view       = rhi_pipeline_get_uniform_location(rs->device, rs->instanced_pipeline, "u_view");
        rs->inst_loc_proj       = rhi_pipeline_get_uniform_location(rs->device, rs->instanced_pipeline, "u_proj");
        rs->inst_loc_light_dir  = rhi_pipeline_get_uniform_location(rs->device, rs->instanced_pipeline, "u_light_dir");
        rs->inst_loc_light_color = rhi_pipeline_get_uniform_location(rs->device, rs->instanced_pipeline, "u_light_color");
        rs->inst_loc_ambient    = rhi_pipeline_get_uniform_location(rs->device, rs->instanced_pipeline, "u_ambient");
        rs->inst_loc_camera_pos = rhi_pipeline_get_uniform_location(rs->device, rs->instanced_pipeline, "u_camera_pos");
    }

    {
        RHIBufferDesc bdesc = {0};
        bdesc.usage = RHI_BUFFER_USAGE_TEXEL;
        bdesc.size = 10000 * 4 * 4 * sizeof(f32);
        rs->instance_buf = rhi_buffer_create(rs->device, &bdesc);
    }

    {
        usize svl = 0, sfl = 0;
        char *sv = NULL, *sf = NULL;
#ifdef ENGINE_VULKAN
        sv = file_read_full("shaders/skinned_vk.vert", &svl);
        sf = file_read_full("shaders/skinned_vk.frag", &sfl);
#else
        sv = file_read_full("shaders/skinned.vert", &svl);
        sf = file_read_full("shaders/skinned.frag", &sfl);
#endif
        if (sv && sf) {
            RHIShader svs = rhi_shader_create(rs->device, sv, svl, false);
            RHIShader sfs = rhi_shader_create(rs->device, sf, sfl, true);
            free(sv); free(sf);
            if (rhi_handle_valid(svs) && rhi_handle_valid(sfs)) {
                RHIPipelineDesc spd = {
                    .vert = svs, .frag = sfs,
                    .uses_textures = true,
                    .uses_texel_buffer = true,
                    .skinned_vertex = true,
                    .is_instanced = true,
                    .color_format = RHI_FORMAT_R16G16B16A16_SFLOAT,
                };
                rs->skinned_pipeline = rhi_pipeline_create(rs->device, &spd);
                spd.wireframe = true;
                rs->wire_skinned_pipeline = rhi_pipeline_create(rs->device, &spd);
                rhi_shader_destroy(rs->device, svs);
                rhi_shader_destroy(rs->device, sfs);
            }
        } else { free(sv); free(sf); }
    }
    if (rhi_handle_valid(rs->skinned_pipeline)) {
        rs->sk_loc_view       = rhi_pipeline_get_uniform_location(rs->device, rs->skinned_pipeline, "u_view");
        rs->sk_loc_proj       = rhi_pipeline_get_uniform_location(rs->device, rs->skinned_pipeline, "u_proj");
        rs->sk_loc_light_dir  = rhi_pipeline_get_uniform_location(rs->device, rs->skinned_pipeline, "u_light_dir");
        rs->sk_loc_light_color = rhi_pipeline_get_uniform_location(rs->device, rs->skinned_pipeline, "u_light_color");
        rs->sk_loc_ambient    = rhi_pipeline_get_uniform_location(rs->device, rs->skinned_pipeline, "u_ambient");
        rs->sk_loc_camera_pos = rhi_pipeline_get_uniform_location(rs->device, rs->skinned_pipeline, "u_camera_pos");
    }

    {
        skeleton_init(&rs->skeleton, rs->device);
        u32 parents[] = {UINT32_MAX, 0};
        Mat4 inv_bind[] = {mat4_identity(), mat4_translation(0, 1, 0)};
        skeleton_set_joints(&rs->skeleton, 2, parents, inv_bind);

        anim_clip_init(&rs->anim_clip, 2.0f, true);
        f32 times[] = {0, 0.5f, 1.0f, 1.5f, 2.0f};
        f32 rot_values[][4] = {
            {0, 0, 0, 1},
            {0, 0, 0.383f, 0.924f},
            {0, 0, 0, 1},
            {0, 0, -0.383f, 0.924f},
            {0, 0, 0, 1},
        };
        anim_clip_add_channel(&rs->anim_clip, 1, ANIM_PATH_ROTATION, 5, times, &rot_values[0][0]);

        f32 box_pos[8][3] = {
            {-0.5f, 0, -0.5f}, {0.5f, 0, -0.5f}, {0.5f, 1, -0.5f}, {-0.5f, 1, -0.5f},
            {-0.5f, 0,  0.5f}, {0.5f, 0,  0.5f}, {0.5f, 1,  0.5f}, {-0.5f, 1,  0.5f},
        };
        f32 box_norm[6][3] = {{0,0,-1},{0,0,1},{-1,0,0},{1,0,0},{0,1,0},{0,-1,0}};
        u32 box_idx[] = {
            0,1,2, 0,2,3,  5,4,7, 5,7,6,
            4,0,3, 4,3,7,  1,5,6, 1,6,2,
            3,2,6, 3,6,7,  4,5,1, 4,1,0,
        };

        f32 box_uvs[8][2] = {{0,0},{1,0},{1,1},{0,1},{0,0},{1,0},{1,1},{0,1}};
        f32 box_weights[8][4] = {
            {1,0,0,0},{1,0,0,0},{0.5f,0.5f,0,0},{0.5f,0.5f,0,0},
            {1,0,0,0},{1,0,0,0},{0.5f,0.5f,0,0},{0.5f,0.5f,0,0},
        };

        u32 vcount = 24;
        u32 icount = 36;
        usize vb_bytes = (usize)vcount * 64;
        /* Single alloc: vdata (24*64B) + idata (36*4B) */
        u8 *geo_buf = (u8 *)calloc(1, vb_bytes + (usize)icount * 4);
        if (!geo_buf) return false;
        u8 *vdata   = geo_buf;
        u32 *idata  = (u32 *)(geo_buf + vb_bytes);
        u32 vi = 0;
        for (u32 fi = 0; fi < 6; fi++) {
            for (u32 fj = 0; fj < 4; fj++) {
                u32 oi = box_idx[fi * 6 + fj];
                f32 *vp = (f32 *)(vdata + vi * 64);
                memcpy(vp, box_pos[oi], 12);
                memcpy(vp + 3, box_norm[fi], 12);
                memcpy(vp + 6, box_uvs[fj], 8);
                u32 *joints = (u32 *)(vdata + vi * 64 + 32);
                joints[0] = oi < 4 ? 0 : 0;
                joints[1] = (oi >= 2 && oi <= 5) ? 1 : 0;
                joints[2] = 0; joints[3] = 0;
                f32 *w = (f32 *)(vdata + vi * 64 + 48);
                memcpy(w, box_weights[oi], 16);
                vi++;
            }
        }

        for (u32 i = 0; i < icount; i++) idata[i] = i;

        RHIBufferDesc vbdesc = {0};
        vbdesc.usage = RHI_BUFFER_USAGE_VERTEX;
        vbdesc.size = vcount * 64;
        vbdesc.initial_data = vdata;
        rs->skinned_vbo = rhi_buffer_create(rs->device, &vbdesc);

        RHIBufferDesc ibdesc = {0};
        ibdesc.usage = RHI_BUFFER_USAGE_INDEX;
        ibdesc.size = icount * 4;
        ibdesc.initial_data = idata;
        rs->skinned_ibo = rhi_buffer_create(rs->device, &ibdesc);
        free(geo_buf); /* single alloc: vdata + idata */
        rs->skinned_index_count = icount;
    }

    /* Deferred rendering path (off by default; forward is the engine's primary path). */
    rs->render_path = RENDER_PATH_FORWARD;
    deferred_init(&rs->deferred, rs->device, w, h);

    /* IBL precomputation system (BRDF LUT + irradiance + prefilter).
     * Capture the procedural sky into the environment cubemap using the demo's
     * default sun, then convolve it into real irradiance/prefilter maps so the
     * PBR HAS_IBL path samples a true environment instead of a per-pixel
     * approximation.  (The IBL is static; a moving sun won't re-converge.) */
    ibl_init(&rs->ibl, rs->device);
    {
        const f32 init_sun_az = 1.03f, init_sun_el = 0.93f;
        f32 sdir[3] = {
            cosf(init_sun_el) * sinf(init_sun_az),
            -sinf(init_sun_el),
            cosf(init_sun_el) * cosf(init_sun_az)
        };
        f32 sl = sqrtf(sdir[0]*sdir[0] + sdir[1]*sdir[1] + sdir[2]*sdir[2]);
        if (sl > 0.0f) { sdir[0] /= sl; sdir[1] /= sl; sdir[2] /= sl; }
        f32 st = fmaxf(0.0f, fminf(init_sun_el, 1.0f));
        f32 scol[3] = { 0.8f + 0.2f*st, 0.4f + 0.55f*st, 0.2f + 0.7f*st };
        ibl_capture_env_sky(&rs->ibl, rs->device, sdir, scol);
        ibl_generate(&rs->ibl, rs->device, rs->ibl.env_map);
    }

    return true;
}

static void render_shutdown(RenderState *rs) {
    ibl_destroy(&rs->ibl, rs->device);
    deferred_destroy(&rs->deferred, rs->device);
    rhi_shadow_map_destroy(rs->device, &rs->shadow_map);
    if (rhi_handle_valid(rs->depth_pipeline)) rhi_pipeline_destroy(rs->device, rs->depth_pipeline);
    if (rhi_handle_valid(rs->skinned_pipeline)) rhi_pipeline_destroy(rs->device, rs->skinned_pipeline);
    if (rhi_handle_valid(rs->wire_skinned_pipeline)) rhi_pipeline_destroy(rs->device, rs->wire_skinned_pipeline);
    if (rhi_handle_valid(rs->skinned_ibo)) rhi_buffer_destroy(rs->device, rs->skinned_ibo);
    if (rhi_handle_valid(rs->skinned_vbo)) rhi_buffer_destroy(rs->device, rs->skinned_vbo);
    skeleton_shutdown(&rs->skeleton);
    if (rhi_handle_valid(rs->instanced_pipeline)) rhi_pipeline_destroy(rs->device, rs->instanced_pipeline);
    if (rhi_handle_valid(rs->wire_instanced_pipeline)) rhi_pipeline_destroy(rs->device, rs->wire_instanced_pipeline);
    if (rhi_handle_valid(rs->instance_buf)) rhi_buffer_destroy(rs->device, rs->instance_buf);
    if (rhi_handle_valid(rs->clustered_pipeline)) rhi_pipeline_destroy(rs->device, rs->clustered_pipeline);
    if (rhi_handle_valid(rs->terrain_tex))  rhi_texture_destroy(rs->device, rs->terrain_tex);
    if (rhi_handle_valid(rs->fallback_tex)) rhi_texture_destroy(rs->device, rs->fallback_tex);
    if (rhi_handle_valid(rs->fallback_mr)) rhi_texture_destroy(rs->device, rs->fallback_mr);
    if (rhi_handle_valid(rs->fallback_normal)) rhi_texture_destroy(rs->device, rs->fallback_normal);
    if (rhi_handle_valid(rs->fallback_emissive)) rhi_texture_destroy(rs->device, rs->fallback_emissive);
    if (rhi_handle_valid(rs->sampler)) rhi_sampler_destroy(rs->device, rs->sampler);
    if (rhi_handle_valid(rs->nearest_sampler)) rhi_sampler_destroy(rs->device, rs->nearest_sampler);
    if (rhi_handle_valid(rs->pipeline)) rhi_pipeline_destroy(rs->device, rs->pipeline);
    if (rhi_handle_valid(rs->wire_pipeline)) rhi_pipeline_destroy(rs->device, rs->wire_pipeline);
    rhi_device_destroy(rs->device);
}

/* Frame-level point shadow cache — gathered once per frame, consumed by
 * bind_material, clustered_set_point_shadow_uniforms, and terrain. */
static struct { RHITexture tex[4]; f32 far_planes[4]; u32 count; } g_psc;

static u32 point_shadow_gather(const PointShadowSystem *pt, RHITexture *psc, f32 psc_far_planes[4]) {
    for (u32 i = 0u; i < 4u; i++) psc_far_planes[i] = 25.0f;
    if (!pt || !pt->ready || pt->active_count == 0u) return 0u;
    u32 psc_n = pt->active_count;
    if (psc_n > 4u) psc_n = 4u;
    for (u32 i = 0u; i < psc_n; i++) {
        if (psc && rhi_handle_valid(pt->cubemap_fbos[i].depth_tex))
            psc[i] = pt->cubemap_fbos[i].depth_tex;
        psc_far_planes[i] = pt->far_planes[i];
    }
    return psc_n;
}

static void bind_material(RHICmdBuffer *cmd, RenderState *rs, Material *mat, Scene *scene) {
    RHITexture alb = (mat && rhi_handle_valid(mat->albedo)) ? mat->albedo : rs->fallback_tex;
    RHITexture mr  = (mat && rhi_handle_valid(mat->metallic_roughness)) ? mat->metallic_roughness : rs->fallback_mr;
    RHITexture nrm = (mat && rhi_handle_valid(mat->normal_map)) ? mat->normal_map : rs->fallback_normal;
    RHITexture em  = (mat && rhi_handle_valid(mat->emissive)) ? mat->emissive : rs->fallback_emissive;
    RHITexture shadow = rs->shadow_map.depth_tex;
    /* The IBL cubemaps are always created in ibl_init (black until generated),
     * so bind them unconditionally: the HAS_IBL shader path declares
     * samplerCube at bindings 7/8 and must never receive a 2D fallback view. */
    RHITexture brdf_lut = rs->ibl.brdf_lut;
    RHICubemap irr_map  = rs->ibl.irradiance_map;
    RHICubemap pref_map = rs->ibl.prefilter_map;
    rhi_cmd_bind_material_textures_ibl(cmd, alb, mr, nrm, em, shadow, rs->ssao_tex, rs->sampler,
                                        brdf_lut, irr_map, pref_map,
                                        g_psc.count > 0u ? g_psc.tex : NULL, g_psc.count);
    if (rs->cl_loc_pom_enabled >= 0) rhi_cmd_set_uniform_f32(cmd, rs->cl_loc_pom_enabled, (mat && rhi_handle_valid(mat->normal_map)) ? 1.0f : 0.0f);
    (void)scene;
}

/* ---- Precomputed node bounding sphere ---- */
typedef struct { f32 cx, cy, cz, r; } NodeSphere;

/* ---- Task-parallel visibility culling ---- */
typedef struct {
    u8               *node_vis;
    const NodeSphere *spheres;
    u32               start;
    u32               end;
    Frustum           frustum;
    Vec3              cam_pos;
    const LODSystem  *lod;
} VisTaskCtx;

static void vis_task_fn(void *raw)
{
    VisTaskCtx *v = (VisTaskCtx *)raw;
    for (u32 ni = v->start; ni < v->end; ni++) {
        if (v->spheres[ni].r < 0.0f) continue;
        Vec3 ctr = {{ v->spheres[ni].cx, v->spheres[ni].cy, v->spheres[ni].cz }};
        if (!frustum_test_sphere(&v->frustum, ctr, v->spheres[ni].r)) continue;
        if (v->lod->count > 0 && ni < LOD_MAX_GROUPS) {
            u32 grp = v->lod->entity_to_group[ni];
            f32 cd  = v->lod->groups[grp].thresholds[0] * 2.0f;
            f32 dx  = ctr.e[0] - v->cam_pos.e[0];
            f32 dy  = ctr.e[1] - v->cam_pos.e[1];
            f32 dz  = ctr.e[2] - v->cam_pos.e[2];
            if (dx*dx + dy*dy + dz*dz > cd * cd) continue;
        }
        v->node_vis[ni] = 1;
    }
}

/* ---- Round 10: mipmap streaming demo plumbing ---- */
typedef struct { RHIDevice *dev; RHITexture tex; } MipUploadCtx;

/* Pushes a streamed mip level to the GPU (real upload via the RHI). */
static void demo_mip_upload(void *ctx, i32 tex_idx, u32 level, u32 w, u32 h,
                            const void *data, u32 size) {
    (void)tex_idx;
    MipUploadCtx *c = (MipUploadCtx *)ctx;
    if (!c || !rhi_handle_valid(c->tex)) return;
    rhi_texture_upload_mip(c->dev, c->tex, level, w, h, data, size);
}

/* Writes a procedural RGBA8 texture as a raw, sequential mip chain so the
 * streaming system has a real file to stream level ranges out of. Returns the
 * number of mip levels written, or 0 on failure. */
static u32 demo_write_stream_texture(const char *path, u32 size) {
    FILE *f = fopen(path, "wb");
    if (!f) return 0;
    u32 mips = 0;
    for (u32 s = size; s >= 1; s >>= 1) {
        u8 *buf = (u8 *)malloc((usize)s * s * 4u);
        if (!buf) { fclose(f); return 0; }
        for (u32 y = 0; y < s; y++) {
            for (u32 x = 0; x < s; x++) {
                u8 *p = &buf[(y * s + x) * 4u];
                /* checkerboard tinted per-mip so levels are visually distinct */
                u8 c = ((x ^ y) & 1u) ? 220 : 40;
                p[0] = (u8)(c);
                p[1] = (u8)(c / (mips + 1));
                p[2] = (u8)(60 + mips * 30);
                p[3] = 255;
            }
        }
        usize wbytes = (usize)s * s * 4u;
        if (fwrite(buf, 1, wbytes, f) != wbytes) {
            free(buf); fclose(f);
            LOG_WARN("Stream texture write: partial write failure for %s", path);
            return mips;
        }
        free(buf);
        mips++;
        if (s == 1) break;
    }
    fclose(f);
    return mips;
}

/* Writes a mono 16-bit PCM WAV containing a fading sine sweep so the demo has a
 * real file to stream and spatialize. Returns true on success. */
static bool demo_write_sine_wav(const char *path, u32 sample_rate, f32 seconds, f32 freq) {
    u32 channels = 1, bits = 16;
    u32 frames = (u32)(seconds * (f32)sample_rate);
    u32 data_bytes = frames * channels * (bits / 8);
    u32 byte_rate = sample_rate * channels * (bits / 8);
    u16 block_align = (u16)(channels * (bits / 8));

    FILE *f = fopen(path, "wb");
    if (!f) return false;

    /* RIFF/WAVE header */
    u32 riff = 36 + data_bytes, fmt_len = 16, sr = sample_rate, br = byte_rate;
    u16 fmt_tag = 1, ch = (u16)channels, bps = (u16)bits, ba = block_align;
    bool wav_ok = true;
    wav_ok &= fwrite("RIFF", 1, 4, f) == 4; wav_ok &= fwrite(&riff, 4, 1, f) == 1; wav_ok &= fwrite("WAVE", 1, 4, f) == 4;
    wav_ok &= fwrite("fmt ", 1, 4, f) == 4; wav_ok &= fwrite(&fmt_len, 4, 1, f) == 1;
    wav_ok &= fwrite(&fmt_tag, 2, 1, f) == 1; wav_ok &= fwrite(&ch, 2, 1, f) == 1; wav_ok &= fwrite(&sr, 4, 1, f) == 1;
    wav_ok &= fwrite(&br, 4, 1, f) == 1; wav_ok &= fwrite(&ba, 2, 1, f) == 1; wav_ok &= fwrite(&bps, 2, 1, f) == 1;
    wav_ok &= fwrite("data", 1, 4, f) == 4; wav_ok &= fwrite(&data_bytes, 4, 1, f) == 1;

    for (u32 i = 0; i < frames && wav_ok; i++) {
        f32 t = (f32)i / (f32)sample_rate;
        f32 env = 0.6f * (0.5f + 0.5f * sinf(t * 1.5f)); /* gentle tremolo */
        f32 s = env * sinf(6.2831853f * freq * t);
        i16 sample = (i16)(s * 32000.0f);
        wav_ok = fwrite(&sample, 2, 1, f) == 1;
    }
    fclose(f);
    if (!wav_ok) LOG_WARN("WAV write: partial write failure for %s", path);
    return true;
}

/* Occlusion: node map + helpers (file scope). */
#define OCC_NODE_MAP_INVALID 0xFFFFFFFFu
static u32 occ_idx_by_node[16384];
OcclusionCullSystem occ_sys = {0};
bool occ_cull_enabled = true;

/* Frame-level persistent visibility buffers — shared across shadow/forward/deferred
 * paths (executed sequentially within a frame, never concurrently).
 * Replaces 11 stack-allocated 16-64KB arrays to prevent stack overflow on
 * constrained stacks (WASM 256KB, worker threads 512KB). */
static u32 g_vis_flags[16384];   /* 64KB: used by mega_mat_groups_* and CPU cull */
static u32 g_draw_vis[16384];    /* 64KB: used by unified vis paths */
static u8  g_node_vis[16384];    /* 16KB: used by legacy node vis paths */
static f32 g_cull_positions[GPUCULL_MAX_OBJECTS * 3]; /* 48KB: gpucull positions */
static f32 g_cull_radii[GPUCULL_MAX_OBJECTS];         /* 16KB: gpucull radii */
static ObjectAABB g_occ_aabbs[OCCLUSION_MAX_OBJECTS]; /* 512KB: occlusion AABB upload */
static u32 g_occ_aabbs_count = 0;  /* R82-2: cached at init (scene data is static) */

static void occ_rebuild_node_map(const Scene *scene) {
    u32 n = scene->node_count < 16384u ? scene->node_count : 16384u;
    for (u32 i = 0; i < n; i++) occ_idx_by_node[i] = OCC_NODE_MAP_INVALID;
    u32 occ_idx = 0;
    for (u32 ni = 0; ni < n && occ_idx < OCCLUSION_MAX_OBJECTS; ni++) {
        const SceneNode *nd = &scene->nodes[ni];
        if (!nd->has_mesh || nd->skinned) continue;
        if (nd->mesh_index >= scene->mesh_count) continue;
        occ_idx_by_node[ni] = occ_idx++;
    }
}

static bool node_occ_visible(u32 ni) {
    if (!occ_cull_enabled || !occ_sys.enabled) return true;
    if (ni >= 16384u) return true;
    u32 oi = occ_idx_by_node[ni];
    if (oi == OCC_NODE_MAP_INVALID) return true;
    return occlusion_cull_is_visible(&occ_sys, oi);
}

/* Round 12: unified GPU cull + compact (single dispatch). */
#define MEGA_MAX_MAT_GROUPS 64

typedef struct {
    RHIBuffer vbo;
    RHIBuffer ibo;
    u32       draw_cmd_count;
    u32       total_index_count;
    bool      valid;

    IndirectDrawSystem mat_systems[MEGA_MAX_MAT_GROUPS];
    u32       mat_indices[MEGA_MAX_MAT_GROUPS];
    u32       mat_group_count;
    i32       cmd_mat_group[16384];
    u32       cmd_node_index[16384];
    NodeSphere node_spheres[16384];
    u32       sphere_count;
    /* R75-2: Pre-built inverse index — group→cmd list. Eliminates O(N×G)
     * linear scan in mega_mat_groups_draw/indirect (called 12-17×/frame). */
    u32       group_cmd_offsets[MEGA_MAX_MAT_GROUPS + 1]; /* prefix sums */
    u32       group_cmd_list[16384];                     /* sorted by group */
} MegaBuffer;

bool unified_cull_enabled = false;
bool unified_forward_enabled = false;
bool unified_deferred_enabled = false;
bool unified_shadow_enabled = false;
bool gpucull_enabled = false;

static bool mega_use_unified_shadow(const MegaBuffer *mb) {
    return unified_shadow_enabled && gpucull_enabled && mb && mb->valid &&
           mb->mat_group_count > 0u;
}

static bool mega_use_unified_vis(bool deferred_pass) {
    if (!gpucull_enabled) return false;
    if (deferred_pass)
        return unified_deferred_enabled || unified_forward_enabled;
    return unified_forward_enabled;
}

static bool mega_unified_cull_draw(GPUCullSystem *gc, RHIDevice *dev, RHICmdBuffer *cmd,
                                   const f32 *vp, u32 vis_count,
                                   OcclusionCullSystem *occ) {
    if (!gc->unified_ready || !unified_cull_enabled ||
        vis_count == 0 || vis_count > GPUCULL_MAX_OBJECTS) {
        return false;
    }
    RHITexture hi_z = RHI_HANDLE_NULL;
    u32 hz_w = 0u, hz_h = 0u;
    if (occ && occ->enabled && rhi_handle_valid(occ->hi_z_texture)) {
        hi_z = occ->hi_z_texture;
        hz_w = occ->hi_z_width;
        hz_h = occ->hi_z_height;
    }
    gpucull_dispatch_unified(gc, cmd, vp, NULL, hi_z, hz_w, hz_h, RHI_HANDLE_NULL);
    gpucull_execute_indirect_draws(gc, dev);
    return true;
}

static bool mega_unified_vis_flags(GPUCullSystem *gc, RHICmdBuffer *cmd,
                                   const f32 *vp, u32 vis_count,
                                   OcclusionCullSystem *occ, u32 *out_flags) {
    if (!gc->unified_ready || !unified_cull_enabled ||
        vis_count == 0 || vis_count > GPUCULL_MAX_OBJECTS || !out_flags) {
        return false;
    }
    RHITexture hi_z = RHI_HANDLE_NULL;
    u32 hz_w = 0u, hz_h = 0u;
    if (occ && occ->enabled && rhi_handle_valid(occ->hi_z_texture)) {
        hi_z = occ->hi_z_texture;
        hz_w = occ->hi_z_width;
        hz_h = occ->hi_z_height;
    }
    gpucull_dispatch_unified(gc, cmd, vp, NULL, hi_z, hz_w, hz_h, gc->visible_flags_ssbo);
    return gpucull_read_vis_flags(gc, vis_count, out_flags);
}

static u32 mega_mat_groups_indirect(RHICmdBuffer *cmd, RHIDevice *dev, MegaBuffer *mb,
                                    const u32 *draw_vis) {
    u32 calls = 0u;
    if (!mb || !mb->valid) return 0u;
    /* R76-3: Batch all compacts before a single barrier — reduces G barriers to 1. */
    for (u32 g = 0; g < mb->mat_group_count; g++) {
        u32 gcount = mb->mat_systems[g].current_draw_count;
        memset(g_vis_flags, 0, gcount * sizeof(u32));
        u32 start = mb->group_cmd_offsets[g];
        u32 end   = mb->group_cmd_offsets[g + 1];
        for (u32 gi = 0; gi < end - start; gi++) {
            u32 ci = mb->group_cmd_list[start + gi];
            g_vis_flags[gi] = draw_vis ? draw_vis[ci] : 1u;
        }
        indirect_draw_upload_visibility(&mb->mat_systems[g], dev, g_vis_flags, gcount);
        indirect_draw_compact_no_barrier(&mb->mat_systems[g], dev, cmd);
    }
    rhi_cmd_memory_barrier(cmd);
    for (u32 g = 0; g < mb->mat_group_count; g++) {
        indirect_draw_execute(&mb->mat_systems[g], dev);
        calls++;
    }
    return calls;
}

static u32 mega_mat_groups_draw(RHICmdBuffer *cmd, RenderState *render, Scene *scene,
                                MegaBuffer *mb,
                                const u32 *draw_vis) {
    u32 calls = 0u;
    if (!mb || !mb->valid) return 0u;
    /* R76-3: Batch all compacts before a single barrier — reduces G barriers to 1. */
    for (u32 g = 0; g < mb->mat_group_count; g++) {
        u32 gcount = mb->mat_systems[g].current_draw_count;
        memset(g_vis_flags, 0, gcount * sizeof(u32));
        u32 start = mb->group_cmd_offsets[g];
        u32 end   = mb->group_cmd_offsets[g + 1];
        for (u32 gi = 0; gi < end - start; gi++) {
            u32 ci = mb->group_cmd_list[start + gi];
            g_vis_flags[gi] = draw_vis ? draw_vis[ci] : 1u;
        }
        indirect_draw_upload_visibility(&mb->mat_systems[g], render->device, g_vis_flags, gcount);
        indirect_draw_compact_no_barrier(&mb->mat_systems[g], render->device, cmd);
    }
    rhi_cmd_memory_barrier(cmd);
    for (u32 g = 0; g < mb->mat_group_count; g++) {
        u32 mat_idx = mb->mat_indices[g];
        Material *mat = (mat_idx < scene->material_count) ? &scene->materials[mat_idx] : NULL;
        bind_material(cmd, render, mat, scene);
        indirect_draw_execute(&mb->mat_systems[g], render->device);
        calls++;
    }
    return calls;
}

static u32 mega_count_visible_draws(const MegaBuffer *mb, const u32 *draw_vis) {
    if (!mb || !mb->valid) return 0u;
    u32 n = mb->draw_cmd_count;
    if (!draw_vis) return n;
    u32 vis = 0u;
    for (u32 i = 0; i < n; i++)
        if (draw_vis[i]) vis++;
    return vis;
}

static u32 mega_count_visible_node_vis(const MegaBuffer *mb, const u8 *node_vis) {
    if (!mb || !mb->valid || !node_vis) return mega_count_visible_draws(mb, NULL);
    u32 vis = 0u;
    for (u32 ci = 0; ci < mb->draw_cmd_count; ci++) {
        u32 ni = mb->cmd_node_index[ci];
        if (node_vis[ni]) vis++;
    }
    return vis;
}

static u32 draw_bench_mega = 0u;
static u32 draw_bench_legacy_est = 0u;
static bool draw_bench_enabled = false;
static bool bench_frame_unified = false;
static bool bench_frame_legacy = false;
static f64 draw_bench_gpu_uni_sum = 0.0;
static f64 draw_bench_gpu_leg_sum = 0.0;
static u32 draw_bench_gpu_uni_frames = 0u;
static u32 draw_bench_gpu_leg_frames = 0u;

#define DRAW_BENCH_HIST 120u
typedef struct {
    u32 frame_id;
    u32 mega;
    u32 legacy_est;
    f64 gpu_ms;
    u8  unified;
    u8  legacy;
} DrawBenchSample;

static DrawBenchSample draw_bench_hist[DRAW_BENCH_HIST];
static u32 draw_bench_hist_count = 0u;
static u32 draw_bench_hist_wr = 0u;
static char draw_bench_csv_path[256] = "draw_bench.csv";

static void draw_bench_reset(void) {
    draw_bench_mega = 0u;
    draw_bench_legacy_est = 0u;
    bench_frame_unified = false;
    bench_frame_legacy = false;
}

static void draw_bench_mark_unified(void) {
    if (draw_bench_enabled) bench_frame_unified = true;
}

static void draw_bench_mark_legacy(void) {
    if (draw_bench_enabled) bench_frame_legacy = true;
}

static void draw_bench_add(u32 mega_calls, u32 legacy_est) {
    if (!draw_bench_enabled || mega_calls == 0u) return;
    draw_bench_mega += mega_calls;
    draw_bench_legacy_est += legacy_est;
}

static void draw_bench_sample_gpu(f64 mega_gpu_ms) {
    if (!draw_bench_enabled) return;
    if (bench_frame_unified) {
        draw_bench_gpu_uni_sum += mega_gpu_ms;
        draw_bench_gpu_uni_frames++;
    }
    if (bench_frame_legacy) {
        draw_bench_gpu_leg_sum += mega_gpu_ms;
        draw_bench_gpu_leg_frames++;
    }
}

static void draw_bench_record_frame(u32 frame_id, f64 gpu_ms) {
    if (!draw_bench_enabled) return;
    if (!bench_frame_unified && !bench_frame_legacy) return;
    DrawBenchSample *s = &draw_bench_hist[draw_bench_hist_wr % DRAW_BENCH_HIST];
    s->frame_id = frame_id;
    s->mega = draw_bench_mega;
    s->legacy_est = draw_bench_legacy_est;
    s->gpu_ms = gpu_ms;
    s->unified = bench_frame_unified ? 1u : 0u;
    s->legacy = bench_frame_legacy ? 1u : 0u;
    draw_bench_hist_wr++;
    if (draw_bench_hist_count < DRAW_BENCH_HIST) draw_bench_hist_count++;
}

static bool draw_bench_export_csv(const char *path) {
    if (!path || !draw_bench_enabled) return false;
    FILE *f = fopen(path, "w");
    if (!f) return false;

    fprintf(f, "frame,mega_draws,legacy_est,gpu_ms,unified,legacy\n");
    u32 n = draw_bench_hist_count;
    u32 start = (draw_bench_hist_wr >= n) ? (draw_bench_hist_wr - n) : 0u;
    for (u32 i = 0u; i < n; i++) {
        DrawBenchSample *s = &draw_bench_hist[(start + i) % DRAW_BENCH_HIST];
        fprintf(f, "%u,%u,%u,%.3f,%u,%u\n",
                s->frame_id, s->mega, s->legacy_est, s->gpu_ms, s->unified, s->legacy);
    }

    f64 avg_u = draw_bench_gpu_uni_frames > 0u ?
        draw_bench_gpu_uni_sum / (f64)draw_bench_gpu_uni_frames : 0.0;
    f64 avg_l = draw_bench_gpu_leg_frames > 0u ?
        draw_bench_gpu_leg_sum / (f64)draw_bench_gpu_leg_frames : 0.0;
    f32 ratio = draw_bench_mega > 0u ?
        (f32)draw_bench_legacy_est / (f32)draw_bench_mega : 0.0f;
    fprintf(f, "# summary mega=%u legacy=%u ratio=%.1f gpu_u=%.3f(%u) gpu_l=%.3f(%u)\n",
            draw_bench_mega, draw_bench_legacy_est, ratio,
            avg_u, draw_bench_gpu_uni_frames, avg_l, draw_bench_gpu_leg_frames);
    fclose(f);
    return true;
}

static void draw_bench_export_all(void) {
    if (!draw_bench_enabled) return;
    { const char *e = getenv("BREAK_DRAW_BENCH_EXPORT");
      if (e && e[0]) {
          strncpy(draw_bench_csv_path, e, sizeof(draw_bench_csv_path) - 1u);
          draw_bench_csv_path[sizeof(draw_bench_csv_path) - 1u] = '\0';
      } }
    if (draw_bench_export_csv(draw_bench_csv_path))
        LOG_INFO("DrawBench CSV: %s", draw_bench_csv_path);
}

static void mega_upload_unified_cull(GPUCullSystem *gc,
                                     const DrawIndexedIndirectCmd *cmds,
                                     const u32 *cmd_node_index,
                                     const NodeSphere *node_spheres,
                                     u32 mesh_cmd_count,
                                     GPUCullDrawCmd *udc_buf,
                                     GPUCullObject *uobj_buf) {
    if (!gc->unified_ready || !cmds || !cmd_node_index || !node_spheres || mesh_cmd_count == 0) return;
    if (!udc_buf || !uobj_buf) return;
    if (mesh_cmd_count > GPUCULL_MAX_OBJECTS) mesh_cmd_count = GPUCULL_MAX_OBJECTS;

    GPUCullDrawCmd *udc = udc_buf;
    GPUCullObject  *uobj = uobj_buf;

    for (u32 ci = 0; ci < mesh_cmd_count; ci++) {
        u32 ni = cmd_node_index[ci];
        udc[ci].index_count    = cmds[ci].index_count;
        udc[ci].instance_count = cmds[ci].instance_count;
        udc[ci].first_index    = cmds[ci].first_index;
        udc[ci].vertex_offset  = cmds[ci].vertex_offset;
        udc[ci].first_instance = cmds[ci].first_instance;
        uobj[ci].position[0] = node_spheres[ni].cx;
        uobj[ci].position[1] = node_spheres[ni].cy;
        uobj[ci].position[2] = node_spheres[ni].cz;
        uobj[ci].position[3] = node_spheres[ni].r;
    }

    gpucull_upload_draw_cmds(gc, udc, mesh_cmd_count);
    gpucull_upload_objects_unified(gc, uobj, mesh_cmd_count);
    unified_cull_enabled = true;
    LOG_INFO("UnifiedCull: uploaded %u draw cmds for mega-buffer", mesh_cmd_count);
}

static void export_profiler_chrome_trace(RHIGPUTimer *gpu_shadow, RHIGPUTimer *gpu_forward,
                                         RHIGPUTimer *gpu_scene, RHIGPUTimer *gpu_postfx,
                                         const char *path) {
    const ProfilerFrame *pf = profiler_last_frame();
    if (!pf || !path) return;
    ProfilerGpuRegion gpu[4];
    gpu[0] = (ProfilerGpuRegion){ "gpu_shadow", rhi_gpu_timer_elapsed_ms(gpu_shadow) };
    gpu[1] = (ProfilerGpuRegion){ "gpu_forward", rhi_gpu_timer_elapsed_ms(gpu_forward) };
    gpu[2] = (ProfilerGpuRegion){ "gpu_scene", rhi_gpu_timer_elapsed_ms(gpu_scene) };
    gpu[3] = (ProfilerGpuRegion){ "gpu_postfx", rhi_gpu_timer_elapsed_ms(gpu_postfx) };

    ProfilerMetaInstant meta[4];
    u32 meta_count = 0u;
    char meta_mega[32], meta_legacy[32], meta_gpu_u[32], meta_gpu_l[32];
    if (draw_bench_enabled) {
        f64 avg_u = draw_bench_gpu_uni_frames > 0u ?
            draw_bench_gpu_uni_sum / (f64)draw_bench_gpu_uni_frames : 0.0;
        f64 avg_l = draw_bench_gpu_leg_frames > 0u ?
            draw_bench_gpu_leg_sum / (f64)draw_bench_gpu_leg_frames : 0.0;
        snprintf(meta_mega, sizeof(meta_mega), "%u", draw_bench_mega);
        snprintf(meta_legacy, sizeof(meta_legacy), "%u", draw_bench_legacy_est);
        snprintf(meta_gpu_u, sizeof(meta_gpu_u), "%.2f", avg_u);
        snprintf(meta_gpu_l, sizeof(meta_gpu_l), "%.2f", avg_l);
        meta[meta_count++] = (ProfilerMetaInstant){ "draw_bench_mega", meta_mega };
        meta[meta_count++] = (ProfilerMetaInstant){ "draw_bench_legacy", meta_legacy };
        meta[meta_count++] = (ProfilerMetaInstant){ "draw_bench_gpu_u_ms", meta_gpu_u };
        meta[meta_count++] = (ProfilerMetaInstant){ "draw_bench_gpu_l_ms", meta_gpu_l };
    }

    if (profiler_export_chrome_trace(path, pf, gpu, 4, meta, meta_count))
        LOG_INFO("Profiler Chrome trace: %s", path);
    draw_bench_export_all();
}

int main(int argc, char **argv) {
    log_set_level(LOG_DEBUG);

    EngineConfig cfg = { .width = 1280, .height = 720, .title = "Pure C Engine - Phase 4", .target_fps = 60.0 };
    Engine engine = {0};
    if (!engine_init(&engine, &cfg)) { LOG_FATAL("Engine init failed"); return 1; }

    RenderState render = {0};
    if (!render_init(&render, engine.platform)) { LOG_FATAL("Render init failed"); engine_shutdown(&engine); return 1; }

    Skybox skybox = {0};
    skybox_init(&skybox, render.device);

    Terrain terrain = {0};
    terrain_init(&terrain, render.device, 64, 40.0f, 1.5f);

    WaterPlane water = {0};
    water_init(&water, render.device, -1.0f, 80.0f);

    LightSystem lights = {0};
    light_system_init(&lights, render.device);
    light_system_init_gpu_cull(&lights);

    PointShadowSystem pt_shadows = {0};
    point_shadow_init(&pt_shadows, render.device, POINT_SHADOW_DEFAULT_RES);

    ParticleSystem particles = {0};
    particles_init(&particles, render.device);

    DebugUI ui = {0};
    debug_ui_init(&ui);
    debug_ui_init_renderer(&ui, render.device);

    /* Immediate-mode settings panel (Round 10). Uses its own font renderer so
     * its quad batch never clobbers the debug-text batch in the same frame.
     * Toggle with the backtick (`) key; mouse-look is paused while it is open. */
    FontRenderer imui_font = {0};
    ImUI imui_ctx = {0};
    bool imui_font_ready = font_renderer_init(&imui_font, render.device,
                                              "assets/LiberationSans-Regular.ttf", 18.0f);
    if (imui_font_ready) imui_init(&imui_ctx, &imui_font);
    bool imui_visible = false;

    HotReloadPipeline hotreload = {0};
#ifdef ENGINE_VULKAN
    hotreload_pipeline_init(&hotreload, render.device,
                             "shaders/blinn_phong_vk.vert", "shaders/blinn_phong_vk.frag", NULL);
#else
    hotreload_pipeline_init(&hotreload, render.device,
                             "shaders/blinn_phong.vert", "shaders/blinn_phong.frag", NULL);
#endif

    HotReloadTexture hotreload_tex = {0};
    bool hotreload_tex_ready = false;
    { const char *e = getenv("BREAK_HOTRELOAD_TEX");
      if (e && e[0]) {
          hotreload_tex_ready = hotreload_texture_init(&hotreload_tex, render.device,
                                                        e, &render.fallback_tex);
          if (hotreload_tex_ready)
              LOG_INFO("Hot reload texture: watching %s (BREAK_HOTRELOAD_TEX)", e);
      } }

    NetReplicator net_rep = {0};
    NetAddress net_rep_dst = {0};
    bool netrep_enabled = false;
    bool netrep_apply = true;
    bool netrep_lerp = true;
    f32 netrep_ghost_target[3] = {0.0f, 5.0f, 0.0f};
    Entity netrep_ghost = {0};
    bool netrep_ghost_valid = false;
    u32 netrep_sent = 0, netrep_recv = 0, netrep_stale = 0, netrep_retries = 0;
    u32 netrep_reordered = 0, netrep_reord_dup = 0, netrep_last_count = 0;
    u32 netrep_hb_sent = 0, netrep_hb_recv = 0, netrep_hb_echo = 0;
    f32 netrep_hb_rtt_ms = 0.0f;
    f32 netrep_hb_rt_ms = 0.0f;
    bool netrep_heartbeat = true;
    NetTransformSnapshot netrep_last[NET_REPL_MAX_SNAPSHOTS];
    char netrep_peer_file[256] = {0};
    char netrep_peer_dir[256] = {0};
    { const char *e = getenv("BREAK_NETREP_APPLY");
      if (e && !atoi(e)) netrep_apply = false; }
    { const char *e = getenv("BREAK_NETREP_LERP");
      if (e && !atoi(e)) netrep_lerp = false; }
    net_rep.seq_dedup = true;
    { const char *e = getenv("BREAK_NETREP_DEDUP");
      if (e && !atoi(e)) net_rep.seq_dedup = false; }
    { const char *e = getenv("BREAK_NETREP_RELIABLE");
      if (e && atoi(e)) net_rep.reliable_retry = true; }
    { const char *e = getenv("BREAK_NETREP_ORDERED");
      if (e && atoi(e)) net_rep.ordered_layer = true; }
    { const char *e = getenv("BREAK_NETREP_RELIABLE_ORDERED");
      if (e && atoi(e)) { net_rep.reliable_retry = true; net_rep.ordered_layer = true; } }
    { const char *e = getenv("BREAK_NETREP_HEARTBEAT");
      if (e && !atoi(e)) netrep_heartbeat = false; }
    net_rep.hb_echo_reply = true;
    { const char *e = getenv("BREAK_NETREP_HB_ECHO");
      if (e && !atoi(e)) net_rep.hb_echo_reply = false; }
    { const char *e = getenv("BREAK_NETREP_PEER_TTL");
      if (e) {
          i32 ttl = atoi(e);
          net_rep.peer_evict_ms = ttl > 0 ? (u32)ttl : 0u;
      } }
    { const char *e = getenv("BREAK_NETREP");
      if (e && atoi(e)) {
          if (net_init() && net_replicator_init(&net_rep, 19900)) {
              net_set_nonblocking(net_rep.socket, true);
              if (net_address_resolve("127.0.0.1", 19900, &net_rep_dst)) {
                  netrep_enabled = true;
                  { const char *pf = getenv("BREAK_NETREP_PEER_FILE");
                    if (pf && pf[0]) {
                        strncpy(netrep_peer_file, pf, sizeof(netrep_peer_file) - 1u);
                        netrep_peer_file[sizeof(netrep_peer_file) - 1u] = '\0';
                        if (net_replicator_peer_load(&net_rep, netrep_peer_file))
                            LOG_INFO("NetRep peers loaded: %s (%u peers)",
                                     netrep_peer_file, net_replicator_peer_count(&net_rep));
                    }
                  }
                  { const char *pd = getenv("BREAK_NETREP_PEER_DIR");
                    if (pd && pd[0]) {
                        strncpy(netrep_peer_dir, pd, sizeof(netrep_peer_dir) - 1u);
                        netrep_peer_dir[sizeof(netrep_peer_dir) - 1u] = '\0';
                        if (net_replicator_peer_load_dir(&net_rep, netrep_peer_dir))
                            LOG_INFO("NetRep peers loaded: %s/ (%u peers)",
                                     netrep_peer_dir, net_replicator_peer_count(&net_rep));
                    }
                  }
                  LOG_INFO("Net replication: on (UDP :19900 loopback, BREAK_NETREP=1)");
              } else {
                  net_replicator_shutdown(&net_rep);
                  net_shutdown();
              }
          }
      } }

    ScriptEngine script = {0};
    script_engine_init(&script);
    script_load(&script, "assets/init.script");

    CharacterController character = character_create(vec3(0, 5, 5), 0.3f, 1.8f);

    AssetCtx asset = {0};
    asset_ctx_init(&asset, render.device);

    /* Virtual filesystem + async I/O loader (2 worker threads). */
    VFS *vfs = vfs_create();
    vfs_mount_dir(vfs, ".");
    async_loader_init(2, vfs);
    LOG_INFO("Async I/O loader ready (2 threads)");

    /* Round 10: visibility-driven mipmap streaming with real GPU uploads.
     * Generate a streamable texture file, create a GPU texture with a full mip
     * chain, and stream levels in/out based on the camera's distance. A small
     * budget keeps eviction exercised. */
    MipmapStreamManager mip_stream = {0};
    RHITexture mip_stream_tex = {0};
    MipUploadCtx mip_upload_ctx = {0};
    i32 mip_stream_idx = -1;
    const u32 MIP_STREAM_SIZE = 256;
    const char *mip_stream_path = "stream_texture.bin";
    u32 mip_stream_levels = demo_write_stream_texture(mip_stream_path, MIP_STREAM_SIZE);
    if (mip_stream_levels > 0) {
        RHITextureDesc mtd = {0};
        mtd.width = MIP_STREAM_SIZE;
        mtd.height = MIP_STREAM_SIZE;
        mtd.format = RHI_FORMAT_R8G8B8A8_UNORM;
        mtd.mip_levels = mip_stream_levels;
        mtd.data = NULL; /* levels are streamed in on demand */
        mip_stream_tex = rhi_texture_create(render.device, &mtd);
        mip_upload_ctx.dev = render.device;
        mip_upload_ctx.tex = mip_stream_tex;
        /* 96 KB budget: fits a few coarse levels, forces eviction of fine ones. */
        if (mipmap_stream_init(&mip_stream, 96 * 1024)) {
            mipmap_stream_set_upload(&mip_stream, demo_mip_upload, &mip_upload_ctx);
            mip_stream_idx = mipmap_stream_register(&mip_stream, mip_stream_path,
                MIP_STREAM_SIZE, MIP_STREAM_SIZE, mip_stream_levels, 4);
        }
        LOG_INFO("MipmapStream demo: %u levels, GPU tex %s",
                 mip_stream_levels, rhi_handle_valid(mip_stream_tex) ? "ok" : "FAILED");
    }

    Scene scene = {0};
    const char *model_path = (argc > 1) ? argv[1] : "assets/test.glb";
    if (!asset_load_gltf(&asset, model_path, &scene)) {
        LOG_WARN("No model loaded (%s)", model_path);
    }

    if (scene.joint_count > 0 && scene.anim_clip_count > 0) {
        skeleton_set_joints(&render.skeleton, scene.joint_count, scene.joint_parents, scene.inverse_bind);
        render.anim_clip = scene.anim_clips[0];
        LOG_INFO("Skeleton: %u joints, anim '%.1fs'", scene.joint_count, render.anim_clip.duration);
    }

    World *world = world_create();
    world_register_component(world, COMP_TRANSFORM, sizeof(CTransform));
    world_register_component(world, COMP_RIGID_BODY, sizeof(CRigidBody));
    world_register_component(world, COMP_MESH_REF, sizeof(CMeshRef));

    PhysicsWorld *physics = physics_world_create(256);
    u32 ground = physics_body_create(physics, vec3(0, -2, 0), vec3(20, 0.5f, 20), 0, true, 0);

    for (u32 i = 0; i < 10; i++) {
        Entity e = world_create_entity(world);
        CTransform *t = world_add_component(world, e, COMP_TRANSFORM);
        if (!t) {
            LOG_ERROR("Failed to add Transform to entity %u (gen=%u)", e.index, e.generation);
            continue;
        }
        t->pos[0] = (f32)(i % 5) * 2.0f - 4.0f;
        t->pos[1] = 8.0f + (f32)(i / 5) * 3.0f;
        t->pos[2] = 0.0f;

        CRigidBody *rb = world_add_component(world, e, COMP_RIGID_BODY);
        if (!rb) {
            LOG_ERROR("Failed to add RigidBody to entity %u", e.index);
            continue;
        }
        rb->physics_id = physics_body_create(physics, vec3(t->pos[0], t->pos[1], t->pos[2]),
                                              vec3(0.5f, 0.5f, 0.5f), 1.0f, false, 0);

        CMeshRef *mr = world_add_component(world, e, COMP_MESH_REF);
        if (mr) mr->mesh_index = 0;
        (void)ground;
    }

    if (netrep_enabled) {
        Entity ge = world_create_entity(world);
        CTransform *gt = world_add_component(world, ge, COMP_TRANSFORM);
        CMeshRef *gm = world_add_component(world, ge, COMP_MESH_REF);
        if (gt && gm) {
            gm->mesh_index = 0;
            gt->pos[0] = 0.0f;
            gt->pos[1] = 5.0f;
            gt->pos[2] = 0.0f;
            netrep_ghost_target[0] = gt->pos[0];
            netrep_ghost_target[1] = gt->pos[1];
            netrep_ghost_target[2] = gt->pos[2];
            netrep_ghost = ge;
            netrep_ghost_valid = true;
            LOG_INFO("Net replication ghost entity ready (entity_id=1)");
        }
    }

    /* Real Lua 5.4 scripting (Round 7): bind host systems, load assets/init.lua,
     * fire on_start once; on_update/reload run in the main loop below. */
    LuaScript lua_script;
    bool lua_ready = lua_script_init(&lua_script);
    if (lua_ready) {
        lua_script_bind_host(&lua_script, world, physics,
                             platform_input(engine.platform));
        if (lua_script_load(&lua_script, "assets/init.lua"))
            lua_script_call_start(&lua_script);
    }

    TaskSystem *tasks = task_system_create(2);
    /* Single alloc: instance_data (f32[]) + unified_udc_buf (GPUCullDrawCmd[]) + unified_uobj_buf (GPUCullObject[]) */
    #define INSTANCE_DATA_CAP 10000
    usize id_bytes = (usize)INSTANCE_DATA_CAP * 16 * sizeof(f32);
    usize udc_off  = (id_bytes + 3u) & ~(usize)3u;
    usize udc_bytes = (usize)GPUCULL_MAX_OBJECTS * sizeof(GPUCullDrawCmd);
    usize uobj_off  = (udc_off + udc_bytes + _Alignof(GPUCullObject) - 1) & ~(_Alignof(GPUCullObject) - 1);
    usize uobj_bytes = (usize)GPUCULL_MAX_OBJECTS * sizeof(GPUCullObject);
    u8 *render_buf   = (u8 *)malloc(uobj_off + uobj_bytes);
    if (!render_buf) { LOG_FATAL("OOM render_buf"); return 1; }
    f32              *instance_data    = (f32 *)render_buf;
    GPUCullDrawCmd   *unified_udc_buf  = (GPUCullDrawCmd *)(render_buf + udc_off);
    GPUCullObject    *unified_uobj_buf = (GPUCullObject *)(render_buf + uobj_off);
    /* Single alloc: cull_node_map + cull_aabbs + cull_visible */
    #define CULL_BUF_CAP 16384
    u32      *cull_node_map_buf;
    CullAABB *cull_aabbs_buf;
    u32      *cull_visible_buf;
    {
        usize nm_bytes = (usize)CULL_BUF_CAP * sizeof(u32);
        usize ab_off   = (nm_bytes + _Alignof(CullAABB) - 1) & ~(_Alignof(CullAABB) - 1);
        usize ab_bytes = (usize)CULL_BUF_CAP * sizeof(CullAABB);
        usize vb_off   = (ab_off + ab_bytes + 3u) & ~(usize)3u;
        usize vb_bytes = (usize)CULL_BUF_CAP * sizeof(u32);
        u8 *cull_block = (u8 *)malloc(vb_off + vb_bytes);
        if (!cull_block) { LOG_FATAL("OOM cull_block"); free(render_buf); return 1; }
        cull_node_map_buf = (u32 *)cull_block;
        cull_aabbs_buf    = (CullAABB *)(cull_block + ab_off);
        cull_visible_buf  = (u32 *)(cull_block + vb_off);
    }
    /* Round 14: persistent per-frame arena for temps. */
    #define FRAME_ARENA_SIZE (256 * 1024)
    static u8 frame_arena_mem[FRAME_ARENA_SIZE];
    Arena frame_arena;
    arena_init(&frame_arena, frame_arena_mem, FRAME_ARENA_SIZE);
    AudioSystem *audio = audio_system_create();

    /* Round 10: stream a procedurally generated 3D sound from disk so the demo
     * actually plays audio with real distance attenuation. */
    AudioStreamManager audio_stream_mgr = {0};
    i32 audio_stream_id = -1;
    const char *audio_stream_path = "stream_tone.wav";
    Vec3 audio_emitter_pos = vec3(8.0f, 1.5f, 0.0f);
    if (audio && demo_write_sine_wav(audio_stream_path, 44100, 4.0f, 220.0f)) {
        if (audio_stream_init(&audio_stream_mgr, audio)) {
            audio_stream_id = audio_stream_open_3d(&audio_stream_mgr, audio_stream_path,
                audio_emitter_pos, 1.0f, /*looping*/ true,
                /*min*/ 2.0f, /*max*/ 40.0f, /*rolloff*/ 1.0f);
            LOG_INFO("Audio stream demo: %s (id=%d)",
                     audio_stream_id >= 0 ? "playing 3D tone" : "open FAILED",
                     audio_stream_id);
        }
    }

    Camera camera = {0};
    u32 w, h;
    platform_get_size(engine.platform, &w, &h);
    /* R142: Guard against h==0 (window minimized) producing Inf/NaN aspect */
    camera_init(&camera, 1.047f, (f32)w / (f32)(h > 0 ? h : 1), 0.1f, 100.0f);

    LOG_INFO("Phase 4 running — ECS: %u entities, Physics: %u bodies, Script: %s",
             world->entity_count - 1, physics->count, script.loaded ? "yes" : "no");
    LOG_INFO("WASD+mouse | ESC quit | Tab UI | F1-F12 | Home/End | Ins/Del/[/]/;/',/./ 1-2 temp 3-4 tint 5 cg 6 lens 7 ca 8 vig | +/- exp | PgUp autoexp | Arrows sat/con");

    RHIGPUTimer *gpu_scene_timer = NULL;
    RHIGPUTimer *gpu_postfx_timer = NULL;
    RHIGPUTimer *gpu_shadow_timer = NULL;
    RHIGPUTimer *gpu_forward_timer = NULL;

    profiler_set_enabled(true);
    gpu_scene_timer = rhi_gpu_timer_create(render.device);
    gpu_postfx_timer = rhi_gpu_timer_create(render.device);
    gpu_shadow_timer = rhi_gpu_timer_create(render.device);
    gpu_forward_timer = rhi_gpu_timer_create(render.device);
    u32 frame_w = w, frame_h = h;
    f64 total_time = 0.0;
    u32 taa_frame = 0;
    Mat4 prev_view_proj = mat4_identity();
    RHIPipeline last_hr_pipeline = RHI_HANDLE_NULL;

    const f32 render_scale_options[] = { 0.3f, 0.5f, 0.75f, 1.0f };
    i32 render_scale_idx = 1;
    f32 render_scale = render_scale_options[render_scale_idx];
    u32 rw = (u32)(w * render_scale); if (rw < 1) rw = 1;
    u32 rh = (u32)(h * render_scale); if (rh < 1) rh = 1;

    RHIOffscreenFBO scene_fbo = rhi_offscreen_fbo_create_fmt(render.device, rw > 0 ? rw : 1, rh > 0 ? rh : 1, RHI_FORMAT_R16G16B16A16_SFLOAT);
    PostProcess postfx = {0};
    SSAOSystem ssao = {0};
    TAASystem taa = {0};
    SSRSystem ssr_sys = {0};
    DOFSystem dof_sys = {0};
    VolumetricSystem vol = {0};
    TonemapSystem tonemap = {0};
    FXAASystem fxaa_sys = {0};
    SSGISystem ssgi_sys = {0};
    LensFlareSystem lens_flare = {0};
    SharpenSystem sharpen_sys = {0};
    MotionBlurSystem motion_blur = {0};
    ContactShadowSystem contact_shadow = {0};
    SSSSystem sss_sys = {0};
    UpscaleSystem upscale_sys = {0};
ColorGradeSystem cg_sys = {0};
GodRaysSystem gr_sys = {0};
DebugVizSystem debug_viz = {0};
i32 debug_viz_mode = 0;
LensEffectsSystem lens_fx = {0};
CinematicSystem cine_sys = {0};
AnimBlendState anim_blend = {0};
bool anim_blend_ready = false;
u32 anim_blend_clip_idx = 0;
IKSystem anim_ik = {0};
bool anim_ik_ready = false;
CombinedAA combined_aa = {0};
CombinedColor combined_color = {0};
ForwardVelocitySystem forward_vel = {0};
bool forward_vel_enabled = false;
LODSystem lod_sys = {0};

MegaBuffer mega_buf = {0};
IndirectDrawSystem indirect_sys = {0};
GPUCullSystem gpucull_sys = {0};
bool gpu_indirect_enabled = false;
f32 cg_saturation = 1.1f;
f32 cg_contrast = 1.05f;
f32 cg_brightness = 1.0f;
f32 cg_temperature = 0.0f;
f32 cg_tint = 0.0f;
i32 fxaa_preset = 1;
i32 bloom_preset = 2;
i32 ssao_preset = 2;
f32 god_rays_intensity = 0.3f;
i32 gr_preset = 2;
bool taa_enabled = true;
bool fxaa_enabled = true;
bool mb_enabled = true;
bool dof_enabled = true;
bool ssr_enabled = true;
bool ssgi_enabled = true;
bool cs_enabled = true;
bool vol_enabled = true;
bool lf_enabled = true;
bool sharpen_enabled = true;
bool sss_enabled = true;
bool cg_enabled = true;
bool lensfx_enabled = true;
bool cine_enabled = false;
f32 lens_ca = 0.003f;
f32 lens_vignette = 0.45f;
f32 lens_grain = 0.015f;
i32 inspector_mode = 0;
i32 screenshot_id = 0;
i32 effect_preset = 0;
f32 sun_azimuth = 1.03f;
f32 sun_elevation = 0.93f;
bool wireframe_mode = false;
bool vsync_on = true;
bool nearest_filter = false;
bool show_help = false;
bool terrain_follow = false;
i32 layout_mode = 0;
bool fog_enabled = false;
f32 fog_near = 10.0f;
f32 fog_far = 50.0f;
f32 screen_shake = 0.0f;
u32 prev_collision_count = 0;
f32 brush_radius = 3.0f;
bool brush_flatten = false;
bool slow_motion = false;
bool top_down_view = false;
u32 selected_entity_id = 0;
u32 selected_entity_count = 0;
u32 selected_entity_idx = 0;
f32 fps_history[64] = {0};
u32 fps_history_idx = 0;
u32 terrain_preset = 0;
u32 time_preset = 0;
u32 particle_preset = 0;
bool third_person = false;
f32 third_person_dist = 5.0f;
bool gravity_enabled = true;
u32 water_color_preset = 0;
bool particle_trail = false;
bool tornado_mode = false;
f32 ambient_mult = 1.0f;
bool cam_height_lock = false;
f32 cam_locked_y = 0.0f;
bool velocity_damping = false;
bool gravity_well = false;
f32 camera_distance_traveled = 0.0f;
f32 camera_frame_dist = 0.0f;
Vec3 camera_prev_pos = {.e={0,0,0}};
Vec3 prev_com = {.e={0,0,0}};
f32 com_drift = 0.0f;
u32 brush_mode = 0;
#define ENTITY_SPAWN_CAP 64
Vec3 custom_gravity = {.e={0, -9.81f, 0}};
u32 physics_mode = 0;
f32 terrain_hmin = 0, terrain_hmax = 0, terrain_havg = 0, terrain_hstd = 0;
f32 terrain_hstd_delta = 0;
f32 terrain_water_pct = 0.0f;
f32 terrain_water_vol = 0.0f;
u32 terrain_shoreline = 0;
f32 terrain_water_depth_avg = 0.0f;
f32 terrain_water_depth_max = 0.0f;
f32 terrain_water_cx = 0.0f, terrain_water_cz = 0.0f;
u32 collision_peak = 0;
f32 collision_flash = 0.0f;
Vec3 last_collision_pos = {.e={0,0,0}};
u32 last_collision_frame = 0;
Vec3 prev_entity_pos = {.e={0,0,0}};
bool recording_path = false;
bool playing_path = false;
u32 path_count = 0;
u32 path_idx = 0;
#define MAX_PATH 600
struct { f32 px,py,pz, yaw,pitch; } cam_path[MAX_PATH];
/* FPS limit presets: 30, 60, 120, 144, 240, 0(unlimited) */
static f32 fps_limits[] = {60.0f, 30.0f, 120.0f, 144.0f, 240.0f, 0.0f};
static i32 fps_limit_idx = 0;
f32 bg_r = 0.05f, bg_g = 0.05f, bg_b = 0.1f;
i32 bg_preset = 0;
f32 shadow_bias = 0.002f;
bool tod_cycle = false;
f32 tod_speed = 0.3f;
i32 bench_frames = 0;
f64 bench_start = 0;
i32 bench_result_show = 0;
struct { bool taa,fxaa,mb,dof,ssr,ssgi,cs,vol,lf,bloom,gr,sss,sharpen,cg,lensfx; } bench_saved;

    post_process_init(&postfx, render.device, rw, rh);
    ssao_init(&ssao, render.device, rw, rh);
    taa_init(&taa, render.device, rw, rh);
    ssr_init(&ssr_sys, render.device, rw, rh);
    dof_init(&dof_sys, render.device, rw, rh);
    volumetric_init(&vol, render.device, rw, rh);
    tonemap_init(&tonemap, render.device);
    fxaa_init(&fxaa_sys, render.device, rw, rh);
    ssgi_init(&ssgi_sys, render.device, rw, rh);
    lens_flare_init(&lens_flare, render.device, rw, rh);
    sharpen_init(&sharpen_sys, render.device, rw, rh);
    motion_blur_init(&motion_blur, render.device, rw, rh);
    contact_shadow_init(&contact_shadow, render.device, rw, rh);
    sss_init(&sss_sys, render.device, rw, rh);
    upscale_init(&upscale_sys, render.device, rw, rh, w, h);
    color_grade_init(&cg_sys, render.device, rw, rh);
    god_rays_init(&gr_sys, render.device, rw, rh);
    debug_viz_init(&debug_viz, render.device, rw, rh);
    lens_effects_init(&lens_fx, render.device, rw, rh);
    cinematic_init(&cine_sys, render.device);
    combined_aa_init(&combined_aa, render.device, rw, rh);
    combined_color_init(&combined_color, render.device, rw, rh);
    forward_velocity_init(&forward_vel, render.device, rw, rh);
    { const char *e = getenv("BREAK_FORWARD_VEL");
      if (e && atoi(e)) {
          forward_vel_enabled = true;
          LOG_INFO("Forward velocity: on (BREAK_FORWARD_VEL=1, camera motion for TAA)");
      } }
    if (scene.joint_count > 0u && scene.anim_clip_count > 0u) {
        const char *blend_e = getenv("BREAK_ANIM_BLEND");
        const char *ik_e = getenv("BREAK_ANIM_IK");
        bool want_blend = blend_e && atoi(blend_e);
        bool want_ik = ik_e && atoi(ik_e);
        if (want_blend || want_ik) {
            anim_blend_state_init(&anim_blend, scene.joint_count);
            anim_layer_play(&anim_blend, 0, 0u, 1.0f, true);
            anim_blend_ready = true;
            if (want_blend)
                LOG_INFO("Anim blend: on (F12 crossfade, BREAK_ANIM_BLEND=1)");
        }
        if (want_ik && scene.joint_count >= 3u) {
            anim_ik_init(&anim_ik);
            Vec3 ik_pole = {{0.0f, 1.0f, 0.0f}};
            anim_ik_set_target(&anim_ik, 0, 0u, 1u, 2u, (Vec3){{0.0f, 1.5f, 2.0f}}, ik_pole);
            anim_ik_set_weight(&anim_ik, 0, 1.0f);
            anim_ik_ready = true;
            LOG_INFO("Anim IK: on (BREAK_ANIM_IK=1, chain 0-1-2)");
        }
    }
    lod_init(&lod_sys);
    occlusion_cull_init(&occ_sys, render.device, rw, rh);

    /* Register scene meshes as LOD groups for distance-based culling. */
    for (u32 ni = 0; ni < scene.node_count && ni < LOD_MAX_GROUPS; ni++) {
        SceneNode *nd = &scene.nodes[ni];
        if (!nd->has_mesh || nd->mesh_index >= scene.mesh_count) continue;
        Mesh *m = &scene.meshes[nd->mesh_index];
        LODGroup grp = {0};
        grp.meshes[0].vertex_buf = m->vertex_buf;
        grp.meshes[0].index_buf  = m->index_buf;
        grp.meshes[0].index_count = m->index_count;
        grp.meshes[0].vertex_count = 0;
        grp.level_count = 1;
        grp.thresholds[0] = 80.0f;
        Vec3 ext = vec3_sub(m->aabb_max, m->aabb_min);
        grp.bounding_radius = vec3_len(ext) * 0.5f;
        lod_register(&lod_sys, ni, &grp);
    }

    /* ---- Build mega-buffer: combine all scene mesh geometry ----
     * Vertices are pre-transformed to world space so that u_model=identity
     * can be used for shadow / forward passes.  Enables IndirectDraw to
     * issue all mesh draws in a single GPU call. */
    scene_compute_world_transforms(&scene);
    {
        typedef struct { f32 pos[3]; f32 nrm[3]; f32 uv[2]; } MegaVert;
        u32 total_verts = 0, total_idxs = 0, mesh_cmd_count = 0;

        for (u32 ni = 0; ni < scene.node_count; ni++) {
            SceneNode *nd = &scene.nodes[ni];
            if (!nd->has_mesh || nd->skinned || nd->mesh_index >= scene.mesh_count) continue;
            Mesh *m = &scene.meshes[nd->mesh_index];
            if (m->vertex_count == 0 || m->index_count == 0) continue;
            total_verts += m->vertex_count;
            total_idxs  += m->index_count;
            mesh_cmd_count++;
        }

        if (mesh_cmd_count > 0 && mesh_cmd_count <= 16384) {
            /* Single alloc: vdata + idata + cmds */
            usize v_bytes = (usize)total_verts * sizeof(MegaVert);
            usize i_off   = (v_bytes + 3u) & ~(usize)3u;
            usize i_bytes = (usize)total_idxs * sizeof(u32);
            usize c_off   = (i_off + i_bytes + 3u) & ~(usize)3u;
            usize c_bytes = (usize)mesh_cmd_count * sizeof(DrawIndexedIndirectCmd);
            u8 *mega_block = (u8 *)malloc(c_off + c_bytes);
            if (!mega_block) { LOG_FATAL("OOM mega_block"); return 1; }
            MegaVert *vdata = (MegaVert *)mega_block;
            u32      *idata = (u32 *)(mega_block + i_off);
            DrawIndexedIndirectCmd *cmds = (DrawIndexedIndirectCmd *)(mega_block + c_off);
            u32 voff = 0, ioff = 0, cidx = 0;

            for (u32 ni = 0; ni < scene.node_count; ni++) {
                SceneNode *nd = &scene.nodes[ni];
                if (!nd->has_mesh || nd->skinned || nd->mesh_index >= scene.mesh_count) continue;
                Mesh *m = &scene.meshes[nd->mesh_index];
                if (m->vertex_count == 0 || m->index_count == 0) continue;
                u32 vc = m->vertex_count;
                u32 vbase = voff;

                /* Map source VBO and transform vertices to world space */
                MegaVert *src_v = (MegaVert *)rhi_buffer_map(render.device, m->vertex_buf);
                if (src_v) {
                    Mat4 *wt = &nd->world_transform;
                    for (u32 vi = 0; vi < vc; vi++) {
                        f32 px = src_v[vi].pos[0], py = src_v[vi].pos[1], pz = src_v[vi].pos[2];
                        vdata[voff+vi].pos[0] = wt->e[0][0]*px + wt->e[1][0]*py + wt->e[2][0]*pz + wt->e[3][0];
                        vdata[voff+vi].pos[1] = wt->e[0][1]*px + wt->e[1][1]*py + wt->e[2][1]*pz + wt->e[3][1];
                        vdata[voff+vi].pos[2] = wt->e[0][2]*px + wt->e[1][2]*py + wt->e[2][2]*pz + wt->e[3][2];
                        f32 nx = src_v[vi].nrm[0], ny = src_v[vi].nrm[1], nz = src_v[vi].nrm[2];
                        vdata[voff+vi].nrm[0] = wt->e[0][0]*nx + wt->e[1][0]*ny + wt->e[2][0]*nz;
                        vdata[voff+vi].nrm[1] = wt->e[0][1]*nx + wt->e[1][1]*ny + wt->e[2][1]*nz;
                        vdata[voff+vi].nrm[2] = wt->e[0][2]*nx + wt->e[1][2]*ny + wt->e[2][2]*nz;
                        vdata[voff+vi].uv[0] = src_v[vi].uv[0];
                        vdata[voff+vi].uv[1] = src_v[vi].uv[1];
                    }
                    rhi_buffer_unmap(render.device, m->vertex_buf);
                }

                /* Map source IBO and remap indices with vertex offset */
                u32 *src_i = (u32 *)rhi_buffer_map(render.device, m->index_buf);
                if (src_i) {
                    for (u32 ii = 0; ii < m->index_count; ii++)
                        idata[ioff + ii] = src_i[ii] + vbase;
                    rhi_buffer_unmap(render.device, m->index_buf);
                }

                /* Build indirect draw command for this scene node */
                cmds[cidx].index_count    = m->index_count;
                cmds[cidx].instance_count = 1;
                cmds[cidx].first_index    = ioff;
                cmds[cidx].vertex_offset  = (i32)vbase;
                cmds[cidx].first_instance = 0;
                mega_buf.cmd_node_index[cidx] = ni;

                voff += vc;
                ioff += m->index_count;
                cidx++;
            }

            /* Create combined GPU buffers */
            RHIBufferDesc vd = { .usage = RHI_BUFFER_USAGE_VERTEX,
                                 .size  = total_verts * sizeof(MegaVert),
                                 .initial_data = vdata };
            mega_buf.vbo = rhi_buffer_create(render.device, &vd);

            RHIBufferDesc id = { .usage = RHI_BUFFER_USAGE_INDEX,
                                 .size  = total_idxs * sizeof(u32),
                                 .initial_data = idata };
            mega_buf.ibo = rhi_buffer_create(render.device, &id);

            /* Initialize indirect draw system */
            indirect_draw_init(&indirect_sys, render.device, mesh_cmd_count);
            indirect_draw_upload(&indirect_sys, render.device, cmds, mesh_cmd_count);

            /* Initialize GPU frustum culling */
            if (!gpucull_init(&gpucull_sys, render.device)) {
                LOG_WARN("GPUCull: init failed; GPU frustum cull toggle disabled");
            } else {
                gpucull_init_unified(&gpucull_sys, render.device);
            }

            mega_buf.draw_cmd_count    = mesh_cmd_count;
            mega_buf.total_index_count = total_idxs;
            mega_buf.valid = true;
            gpu_indirect_enabled = true;
            gpucull_enabled = true;

            /* Build per-material groups for G-Buffer/forward batched indirect draw */
            memset(mega_buf.cmd_mat_group, -1, sizeof(mega_buf.cmd_mat_group));
            mega_buf.mat_group_count = 0;
            {
                u32 gcmd = 0;
                for (u32 ni = 0; ni < scene.node_count; ni++) {
                    SceneNode *nd = &scene.nodes[ni];
                    if (!nd->has_mesh || nd->skinned || nd->mesh_index >= scene.mesh_count) continue;
                    Mesh *m = &scene.meshes[nd->mesh_index];
                    if (m->vertex_count == 0 || m->index_count == 0) continue;

                    u32 mat_idx = nd->material_idx;
                    /* Find existing group or create new one */
                    u32 g;
                    for (g = 0; g < mega_buf.mat_group_count; g++) {
                        if (mega_buf.mat_indices[g] == mat_idx) break;
                    }
                    if (g == mega_buf.mat_group_count && g < MEGA_MAX_MAT_GROUPS) {
                        mega_buf.mat_indices[g] = mat_idx;
                        mega_buf.mat_group_count++;
                    }
                    mega_buf.cmd_mat_group[gcmd] = (i32)g;
                    gcmd++;
                }

                /* R75-2: Build inverse index (group→cmd list) in O(N) — replaces
                 * O(N×G) linear scans in mega_mat_groups_draw/indirect and here.
                 * R76-1: Bounds-check group index — when >64 materials exist,
                 * cmd_mat_group[ci] can be >= mat_group_count (overflow cmds
                 * that couldn't create a new group). Skip those to avoid
                 * stack buffer overflow on group_counts/fill_pos. */
                {
                    u32 group_counts[MEGA_MAX_MAT_GROUPS] = {0};
                    for (u32 ci = 0; ci < gcmd; ci++) {
                        u32 g = (u32)mega_buf.cmd_mat_group[ci];
                        if (g < mega_buf.mat_group_count) group_counts[g]++;
                    }
                    mega_buf.group_cmd_offsets[0] = 0;
                    for (u32 g = 0; g < mega_buf.mat_group_count; g++)
                        mega_buf.group_cmd_offsets[g + 1] = mega_buf.group_cmd_offsets[g] + group_counts[g];
                    u32 fill_pos[MEGA_MAX_MAT_GROUPS] = {0};
                    for (u32 ci = 0; ci < gcmd; ci++) {
                        u32 g = (u32)mega_buf.cmd_mat_group[ci];
                        if (g >= mega_buf.mat_group_count) continue;
                        mega_buf.group_cmd_list[mega_buf.group_cmd_offsets[g] + fill_pos[g]++] = ci;
                    }
                }

                /* Create per-material IndirectDrawSystems (single pre-alloc scratch buffer) */
                DrawIndexedIndirectCmd *gcmds_scratch = malloc((usize)mesh_cmd_count * sizeof(DrawIndexedIndirectCmd));
                if (!gcmds_scratch) { LOG_FATAL("OOM gcmds_scratch"); free(mega_block); return 1; }
                for (u32 g = 0; g < mega_buf.mat_group_count; g++) {
                    u32 gcount = mega_buf.group_cmd_offsets[g + 1] - mega_buf.group_cmd_offsets[g];
                    if (gcount == 0) continue;

                    u32 gi = 0;
                    for (u32 ci = mega_buf.group_cmd_offsets[g]; ci < mega_buf.group_cmd_offsets[g + 1]; ci++)
                        gcmds_scratch[gi++] = cmds[mega_buf.group_cmd_list[ci]];
                    indirect_draw_init(&mega_buf.mat_systems[g], render.device, gcount);
                    indirect_draw_upload(&mega_buf.mat_systems[g], render.device, gcmds_scratch, gcount);
                }
                free(gcmds_scratch);

                LOG_INFO("MegaBuffer: %u material groups", mega_buf.mat_group_count);
            }

            /* Precompute per-node bounding sphere cache for fast visibility tests */
            mega_buf.sphere_count = 0;
            for (u32 ni = 0; ni < scene.node_count && ni < 16384; ni++) {
                SceneNode *nd = &scene.nodes[ni];
                if (!nd->has_mesh || nd->skinned || nd->mesh_index >= scene.mesh_count) {
                    mega_buf.node_spheres[ni].r = -1.0f;  /* invalid = skip */
                    continue;
                }
                Mesh *m = &scene.meshes[nd->mesh_index];
                if (m->vertex_count == 0 || m->index_count == 0) {
                    mega_buf.node_spheres[ni].r = -1.0f;
                    continue;
                }
                Vec3 ext = vec3_sub(m->aabb_max, m->aabb_min);
                mega_buf.node_spheres[ni].cx = nd->world_transform.e[3][0];
                mega_buf.node_spheres[ni].cy = nd->world_transform.e[3][1];
                mega_buf.node_spheres[ni].cz = nd->world_transform.e[3][2];
                mega_buf.node_spheres[ni].r = vec3_len(ext) * 0.5f;
                mega_buf.sphere_count++;
            }
            LOG_INFO("Sphere cache: %u valid nodes", mega_buf.sphere_count);

            /* R82-2/R82-4: Pre-compute occlusion AABBs + node map at init.
             * Scene data is static after load (local_transform never modified at runtime),
             * so world AABBs and node mapping are immutable. */
            g_occ_aabbs_count = 0;
            occ_rebuild_node_map(&scene);
            for (u32 ni = 0; ni < scene.node_count && g_occ_aabbs_count < OCCLUSION_MAX_OBJECTS; ni++) {
                SceneNode *nd = &scene.nodes[ni];
                if (!nd->has_mesh || nd->skinned) continue;
                if (nd->mesh_index >= scene.mesh_count) continue;
                Mesh *om = &scene.meshes[nd->mesh_index];
                Vec3 wmin = vec3(1e30f, 1e30f, 1e30f), wmax = vec3(-1e30f, -1e30f, -1e30f);
                for (int ci = 0; ci < 8; ci++) {
                    f32 lx = (ci & 1) ? om->aabb_max.e[0] : om->aabb_min.e[0];
                    f32 ly = (ci & 2) ? om->aabb_max.e[1] : om->aabb_min.e[1];
                    f32 lz = (ci & 4) ? om->aabb_max.e[2] : om->aabb_min.e[2];
                    f32 wx = nd->world_transform.e[0][0]*lx + nd->world_transform.e[1][0]*ly + nd->world_transform.e[2][0]*lz + nd->world_transform.e[3][0];
                    f32 wy = nd->world_transform.e[0][1]*lx + nd->world_transform.e[1][1]*ly + nd->world_transform.e[2][1]*lz + nd->world_transform.e[3][1];
                    f32 wz = nd->world_transform.e[0][2]*lx + nd->world_transform.e[1][2]*ly + nd->world_transform.e[2][2]*lz + nd->world_transform.e[3][2];
                    if (wx < wmin.e[0]) wmin.e[0] = wx;
                    if (wx > wmax.e[0]) wmax.e[0] = wx;
                    if (wy < wmin.e[1]) wmin.e[1] = wy;
                    if (wy > wmax.e[1]) wmax.e[1] = wy;
                    if (wz < wmin.e[2]) wmin.e[2] = wz;
                    if (wz > wmax.e[2]) wmax.e[2] = wz;
                }
                g_occ_aabbs[g_occ_aabbs_count].min = wmin;
                g_occ_aabbs[g_occ_aabbs_count].max = wmax;
                g_occ_aabbs_count++;
            }
            LOG_INFO("Occlusion: %u cached AABBs", g_occ_aabbs_count);
            /* R83-4: Upload AABBs once at init — data is static, no per-frame re-upload needed. */
            if (g_occ_aabbs_count > 0)
                occlusion_cull_upload_aabbs(&occ_sys, g_occ_aabbs, g_occ_aabbs_count);

            if (gpucull_sys.unified_ready)
                mega_upload_unified_cull(&gpucull_sys, cmds, mega_buf.cmd_node_index,
                                         mega_buf.node_spheres, mesh_cmd_count,
                                         unified_udc_buf, unified_uobj_buf);

            if (mega_buf.mat_group_count > 0u && gpucull_sys.unified_ready) {
                unified_shadow_enabled = true;
                unified_forward_enabled = true;
                unified_deferred_enabled = true;
            }

            LOG_INFO("MegaBuffer: %u verts, %u indices, %u draw cmds",
                     total_verts, total_idxs, mesh_cmd_count);

            free(mega_block); /* single free: vdata + idata + cmds */
        }
    }

    /* Headless / CI smoke-test hooks (no effect unless env vars are set):
     *   BREAK_FRAMES=N   auto-exit after N frames
     *   BREAK_GPUCULL=1  start with GPU frustom culling enabled */
    i64 auto_exit_frames = 0;
    { const char *e = getenv("BREAK_FRAMES");    if (e) auto_exit_frames = atoll(e); }
    { const char *e = getenv("BREAK_GPUCULL");   if (e && atoi(e)) gpucull_enabled = true; }
    { const char *e = getenv("BREAK_UNIFIED_FORWARD");
      if (e && !atoi(e)) unified_forward_enabled = false;
      else if (e && atoi(e)) unified_forward_enabled = true; }
    { const char *e = getenv("BREAK_UNIFIED_DEFERRED");
      if (e && !atoi(e)) unified_deferred_enabled = false;
      else if (e && atoi(e)) unified_deferred_enabled = true; }
    { const char *e = getenv("BREAK_UNIFIED_SHADOW");
      if (e && !atoi(e)) unified_shadow_enabled = false;
      else if (e && atoi(e)) unified_shadow_enabled = true; }
    { const char *e = getenv("BREAK_OCCLUSION"); if (e && !atoi(e)) occ_cull_enabled = false; }
    { const char *e = getenv("BREAK_DRAW_BENCH"); if (e && atoi(e)) draw_bench_enabled = true; }
    if (gpucull_enabled) LOG_INFO("GPU Frustum Cull: on (default with mega-buffer)");
    if (unified_cull_enabled) LOG_INFO("Unified GPU Cull+Compact: on (shadow/point-shadow)");
    if (unified_forward_enabled) {
        const char *fw = getenv("BREAK_UNIFIED_FORWARD");
        LOG_INFO("Unified forward draw: on (%s)", fw ? "BREAK_UNIFIED_FORWARD=1" : "default mega-buffer");
    }
    if (unified_deferred_enabled) {
        const char *df = getenv("BREAK_UNIFIED_DEFERRED");
        LOG_INFO("Unified deferred draw: on (%s)", df ? "BREAK_UNIFIED_DEFERRED=1" : "default mega-buffer");
    }
    if (unified_shadow_enabled) {
        const char *sh = getenv("BREAK_UNIFIED_SHADOW");
        LOG_INFO("Unified shadow draw: on (%s)", sh ? "BREAK_UNIFIED_SHADOW=1" : "default mega-buffer");
    }
    if (occ_cull_enabled) LOG_INFO("Hi-Z Occlusion Cull: on (1-frame latency, opt-out BREAK_OCCLUSION=0)");
    if (draw_bench_enabled) LOG_INFO("DrawBench: on (BREAK_DRAW_BENCH=1, mega vs legacy draw est)");

    /* Pre-compute orbit light base angles and static colors (avoids 64 trig + 96 int ops per frame). */
    f32 orbit_cos[32], orbit_sin[32];
    f32 orbit_r[32], orbit_g[32], orbit_b[32];
    for (u32 i = 0; i < 32; i++) {
        f32 base = (f32)i * 6.283185f / 32.0f;
        orbit_cos[i] = cosf(base) * 8.0f;
        orbit_sin[i] = sinf(base) * 8.0f;
        orbit_r[i] = (f32)((i * 7919) % 256) / 256.0f;
        orbit_g[i] = (f32)((i * 6271) % 256) / 256.0f;
        orbit_b[i] = (f32)((i * 4253) % 256) / 256.0f;
    }

    /* Cached sun direction: only recompute when elevation/azimuth change (avoids 4 trig/normalize per frame). */
    f32 cached_sun_az = 1e9f, cached_sun_el = 1e9f;
    Vec3 cached_sun_dir = {{0.0f, 1.0f, 0.0f}};

    while (engine_frame(&engine)) {
        arena_free_all(&frame_arena);
        if (auto_exit_frames > 0 && (i64)engine.frame_count >= auto_exit_frames) break;
        profiler_begin_frame();

        if (bench_frames > 0) {
            bench_start += engine.delta_time;
            bench_frames--;
            if (bench_frames == 0) {
                f64 avg_ms = bench_start / 120.0 * 1000.0;
                LOG_INFO("Benchmark: avg %.2f ms (%.0f FPS) with all effects OFF", avg_ms, avg_ms > 0.0 ? 1000.0 / avg_ms : 0.0);
                taa_enabled = bench_saved.taa; fxaa_enabled = bench_saved.fxaa;
                mb_enabled = bench_saved.mb; dof_enabled = bench_saved.dof;
                ssr_enabled = bench_saved.ssr; ssgi_enabled = bench_saved.ssgi;
                cs_enabled = bench_saved.cs; vol_enabled = bench_saved.vol;
                lf_enabled = bench_saved.lf;
                if (bench_saved.bloom) postfx.bloom_strength = 0.8f;
                if (bench_saved.gr) god_rays_intensity = 0.5f;
                sss_enabled = bench_saved.sss; sharpen_enabled = bench_saved.sharpen;
                cg_enabled = bench_saved.cg; lensfx_enabled = bench_saved.lensfx;
                bench_result_show = 180;
            }
        }
        if (bench_result_show > 0) bench_result_show--;

        platform_get_size(engine.platform, &w, &h);

        /* F1: cycle render scale */
        if (input_key_pressed(platform_input(engine.platform), 271)) {
            render_scale_idx = (render_scale_idx + 1) % 4;
            render_scale = render_scale_options[render_scale_idx];
            LOG_INFO("Render scale: %.0f%% (%.2fx)", render_scale * 100.0f, render_scale);
        }

        if (input_key_pressed(platform_input(engine.platform), 272)) {
            debug_viz_mode = (debug_viz_mode + 1) % 5;
            const char *names[] = { "off", "depth", "normals", "AO", "cascades" };
            LOG_INFO("Debug viz: %s", names[debug_viz_mode]);
        }

        if (input_key_pressed(platform_input(engine.platform), 273)) {
            inspector_mode = (inspector_mode + 1) % 11;
            static const char *insp_names[] = {
                "off", "scene_color", "scene_depth", "ssao_raw", "ssao_blur",
                "taa_out", "fxaa_out", "dof_out", "bloom", "godrays", "sharpen_out"
            };
            LOG_INFO("Inspector: %s", insp_names[inspector_mode]);
        }

        /* F4: cycle tonemap mode (0=ACES, 1=AgX, 2=Khronos) */
        if (input_key_pressed(platform_input(engine.platform), 274)) {
            tonemap.mode = (tonemap.mode + 1) % 3;
            const char *tm_names[] = { "ACES", "AgX", "Khronos" };
            LOG_INFO("Tonemap: %s", tm_names[tonemap.mode]);
        }

        /* F6: cycle FXAA quality (low/med/high) */
        if (input_key_pressed(platform_input(engine.platform), 276)) {
            fxaa_preset = (fxaa_preset + 1) % 3;
            const float thresholds[] = { 0.0832f, 0.0312f, 0.0125f };
            const char *qp_names[] = { "low", "medium", "high" };
            fxaa_sys.threshold = thresholds[fxaa_preset];
            LOG_INFO("FXAA quality: %s", qp_names[fxaa_preset]);
        }

        /* F7: cycle bloom intensity (off/low/med/high) */
        if (input_key_pressed(platform_input(engine.platform), 277)) {
            bloom_preset = (bloom_preset + 1) % 4;
            const float strengths[] = { 0.0f, 0.2f, 0.4f, 0.7f };
            const char *bl_names[] = { "off", "low", "medium", "high" };
            postfx.bloom_strength = strengths[bloom_preset];
            LOG_INFO("Bloom: %s (%.1f)", bl_names[bloom_preset], postfx.bloom_strength);
        }

        /* F8: cycle SSAO intensity (off/low/med/high) */
        if (input_key_pressed(platform_input(engine.platform), 278)) {
            ssao_preset = (ssao_preset + 1) % 4;
            const float radii[] = { 0.0f, 0.3f, 0.5f, 0.8f };
            const char *ao_names[] = { "off", "low", "medium", "high" };
            ssao.radius = radii[ssao_preset];
            LOG_INFO("SSAO: %s (radius %.1f)", ao_names[ssao_preset], ssao.radius);
        }

        /* F9: cycle god rays intensity (off/low/med/high) */
        if (input_key_pressed(platform_input(engine.platform), 279)) {
            gr_preset = (gr_preset + 1) % 4;
            const float gr_vals[] = { 0.0f, 0.15f, 0.3f, 0.6f };
            const char *gr_names[] = { "off", "low", "medium", "high" };
            god_rays_intensity = gr_vals[gr_preset];
            LOG_INFO("God rays: %s (%.2f)", gr_names[gr_preset], god_rays_intensity);
        }

        if (input_key_pressed(platform_input(engine.platform), 280)) {
            taa_enabled = !taa_enabled;
            LOG_INFO("TAA: %s", taa_enabled ? "on" : "off");
        }

        if (input_key_pressed(platform_input(engine.platform), 281)) {
            mb_enabled = !mb_enabled;
            LOG_INFO("Motion blur: %s", mb_enabled ? "on" : "off");
        }

        if (input_key_pressed(platform_input(engine.platform), 282)) {
            usize pix_bytes = (usize)w * (usize)h * 3u;
            u8 *pixels = (u8 *)arena_alloc(&frame_arena.base, pix_bytes, alignof(u8));
            if (pixels) {
                rhi_screenshot(render.device, 0, 0, w, h, pixels);
                char spath[64];
                snprintf(spath, sizeof(spath), "screenshot_%d.bmp", screenshot_id++);
                save_bmp(spath, w, h, pixels);
                LOG_INFO("Screenshot saved: %s (%ux%u)", spath, w, h);
            }
        }

        /* F11: export Chrome profiler trace (also set PROFILER_TRACE=1 on exit) */
        if (input_key_pressed(platform_input(engine.platform), 283)) {
            export_profiler_chrome_trace(gpu_shadow_timer, gpu_forward_timer,
                                         gpu_scene_timer, gpu_postfx_timer,
                                         "profile_trace.json");
        }

        if (input_key_pressed(platform_input(engine.platform), 284)) {
            cine_enabled = !cine_enabled;
            LOG_INFO("Cinematic: %s", cine_enabled ? "on" : "off");
        }

        if (anim_blend_ready && scene.anim_clip_count > 0u &&
            input_key_pressed(platform_input(engine.platform), 290)) {
            u32 next = (anim_blend_clip_idx + 1u) % scene.anim_clip_count;
            anim_crossfade(&anim_blend, 0, next, 0.35f);
            anim_blend_clip_idx = next;
            LOG_INFO("Anim crossfade -> clip %u (%.1fs)",
                     next, scene.anim_clips[next].duration);
        }

        if (input_key_pressed(platform_input(engine.platform), 286)) {
            gpu_indirect_enabled = !gpu_indirect_enabled;
            LOG_INFO("GPU Indirect Draw: %s", gpu_indirect_enabled ? "on" : "off");
        }

        if (input_key_pressed(platform_input(engine.platform), 287)) {
            gpucull_enabled = !gpucull_enabled;
            LOG_INFO("GPU Frustum Cull: %s", gpucull_enabled ? "on" : "off");
        }

        if (input_key_pressed(platform_input(engine.platform), 285)) {
            effect_preset = (effect_preset + 1) % 4;
            const char *pnames[] = { "full", "balanced", "performance", "minimal" };
            switch (effect_preset) {
            case 0:
                render_scale = render_scale_options[1];
                ssao.radius = 0.5f; ssao_preset = 2;
                god_rays_intensity = 0.3f; gr_preset = 2;
                postfx.bloom_strength = 0.4f; bloom_preset = 2;
                taa_enabled = true; mb_enabled = true;
                fxaa_sys.threshold = 0.0312f; fxaa_preset = 1;
                cg_saturation = 1.1f; cg_contrast = 1.05f;
            dof_enabled = true; ssr_enabled = true; ssgi_enabled = true;
            cs_enabled = true; vol_enabled = true; lf_enabled = true;
            sharpen_enabled = true; sss_enabled = true; cg_enabled = true;
                lensfx_enabled = true; lens_ca = 0.003f; lens_vignette = 0.45f;
            lensfx_enabled = true; lens_ca = 0.003f; lens_vignette = 0.45f; lens_grain = 0.015f;
                break;
            case 1:
                render_scale = render_scale_options[1];
                ssao.radius = 0.3f; ssao_preset = 1;
                god_rays_intensity = 0.15f; gr_preset = 1;
                postfx.bloom_strength = 0.2f; bloom_preset = 1;
                taa_enabled = true; mb_enabled = false;
                fxaa_sys.threshold = 0.0312f; fxaa_preset = 1;
                cg_saturation = 1.05f; cg_contrast = 1.0f;
                dof_enabled = false; ssr_enabled = false; ssgi_enabled = false;
                cs_enabled = false; vol_enabled = false; lf_enabled = false;
                sharpen_enabled = true; sss_enabled = false; cg_enabled = false;
                lensfx_enabled = false;
                break;
            case 2:
                render_scale = render_scale_options[2];
                ssao.radius = 0.0f; ssao_preset = 0;
                god_rays_intensity = 0.0f; gr_preset = 0;
                postfx.bloom_strength = 0.0f; bloom_preset = 0;
                taa_enabled = true; mb_enabled = false;
                fxaa_sys.threshold = 0.0832f; fxaa_preset = 0;
                cg_saturation = 1.0f; cg_contrast = 1.0f;
                dof_enabled = false; ssr_enabled = false; ssgi_enabled = false;
                cs_enabled = false; vol_enabled = false; lf_enabled = false;
                sharpen_enabled = false; sss_enabled = false; cg_enabled = false;
                lensfx_enabled = false;
                break;
            case 3:
                render_scale = render_scale_options[3];
                ssao.radius = 0.0f; ssao_preset = 0;
                god_rays_intensity = 0.0f; gr_preset = 0;
                postfx.bloom_strength = 0.0f; bloom_preset = 0;
                taa_enabled = false; mb_enabled = false;
                fxaa_sys.threshold = 0.0832f; fxaa_preset = 0;
                cg_saturation = 1.0f; cg_contrast = 1.0f;
                dof_enabled = false; ssr_enabled = false; ssgi_enabled = false;
                cs_enabled = false; vol_enabled = false; lf_enabled = false;
                sharpen_enabled = false; sss_enabled = false; cg_enabled = false;
                lensfx_enabled = false;
                break;
            }
            LOG_INFO("Preset: %s", pnames[effect_preset]);
        }

        if (input_key_pressed(platform_input(engine.platform), 286)) {
            effect_preset = 0;
            render_scale = render_scale_options[1]; render_scale_idx = 1;
            ssao.radius = 0.5f; ssao_preset = 2;
            god_rays_intensity = 0.3f; gr_preset = 2;
            postfx.bloom_strength = 0.4f; bloom_preset = 2;
            taa_enabled = true; mb_enabled = true;
            fxaa_sys.threshold = 0.0312f; fxaa_preset = 1;
            cg_saturation = 1.1f; cg_contrast = 1.05f;
            tonemap.exposure = 1.5f; tonemap.auto_exposure = true;
            debug_viz_mode = 0; tonemap.mode = 0;
            camera.move_speed = 3.0f; inspector_mode = 0; sun_azimuth = 1.03f; sun_elevation = 0.93f; wireframe_mode = false; fxaa_enabled = true; taa_enabled = true; shadow_bias = 0.002f; tod_cycle = false; terrain_follow = false;
            dof_enabled = true; ssr_enabled = true; ssgi_enabled = true;
            LOG_INFO("All effects reset to defaults");
        }

        if (input_key_pressed(platform_input(engine.platform), 287)) {
            dof_enabled = !dof_enabled;
            LOG_INFO("DOF: %s", dof_enabled ? "on" : "off");
        }
        if (input_key_pressed(platform_input(engine.platform), 288)) {
            ssr_enabled = !ssr_enabled;
            LOG_INFO("SSR: %s", ssr_enabled ? "on" : "off");
        }
        if (input_key_pressed(platform_input(engine.platform), 91)) {
            ssgi_enabled = !ssgi_enabled;
            LOG_INFO("SSGI: %s", ssgi_enabled ? "on" : "off");
        }
        if (input_key_pressed(platform_input(engine.platform), 93)) {
            vol_enabled = !vol_enabled;
            LOG_INFO("Volumetric: %s", vol_enabled ? "on" : "off");
        }
        if (input_key_pressed(platform_input(engine.platform), 59)) {
            cs_enabled = !cs_enabled;
            LOG_INFO("Contact shadow: %s", cs_enabled ? "on" : "off");
        }
        if (input_key_pressed(platform_input(engine.platform), 61)) {
            if (!water.enabled) {
                water.enabled = true;
                water.time_scale = 1.0f;
                LOG_INFO("Water: on");
            } else {
                static u32 ws = 0;
                ws = (ws + 1) % 4;
                if (ws == 3) { water.enabled = false; LOG_INFO("Water: off"); }
                else {
                    static const f32 speeds[] = {0.25f, 1.0f, 3.0f};
                    static const char *sn[] = {"slow", "normal", "fast"};
                    water.time_scale = speeds[ws];
                    LOG_INFO("Water waves: %s (%.1fx)", sn[ws], water.time_scale);
                }
            }
        }
        if (input_key_pressed(platform_input(engine.platform), (i32)'(')) {
            water.water_y -= 0.5f;
            LOG_INFO("Water level: %.1f", water.water_y);
        }
        if (input_key_pressed(platform_input(engine.platform), (i32)')')) {
            water.water_y += 0.5f;
            LOG_INFO("Water level: %.1f", water.water_y);
        }
        if (input_key_pressed(platform_input(engine.platform), 39)) {
            sss_enabled = !sss_enabled;
            LOG_INFO("SSS: %s", sss_enabled ? "on" : "off");
        }
        if (input_key_pressed(platform_input(engine.platform), 44)) {
            lf_enabled = !lf_enabled;
            LOG_INFO("Lens flare: %s", lf_enabled ? "on" : "off");
        }
        if (input_key_pressed(platform_input(engine.platform), 46)) {
            sharpen_enabled = !sharpen_enabled;
            LOG_INFO("Sharpen: %s", sharpen_enabled ? "on" : "off");
        }
        {
            InputState *inp = platform_input(engine.platform);
            if (input_key_pressed(inp, 49)) { cg_temperature -= 0.05f; LOG_INFO("Temperature: %.2f", cg_temperature); }
            if (input_key_pressed(inp, 50)) { cg_temperature += 0.05f; LOG_INFO("Temperature: %.2f", cg_temperature); }
            if (input_key_pressed(inp, 51)) { cg_tint -= 0.05f; LOG_INFO("Tint: %.2f", cg_tint); }
            if (input_key_pressed(inp, 52)) { cg_tint += 0.05f; LOG_INFO("Tint: %.2f", cg_tint); }
            if (input_key_pressed(inp, 53)) { cg_enabled = !cg_enabled; LOG_INFO("Color grade: %s", cg_enabled ? "on" : "off"); }
            if (input_key_pressed(inp, 54)) { lensfx_enabled = !lensfx_enabled; LOG_INFO("Lens effects: %s", lensfx_enabled ? "on" : "off"); }
            if (input_key_pressed(inp, 55)) {
                lens_ca = lens_ca > 0.001f ? 0.0f : lens_ca + 0.001f;
                LOG_INFO("CA strength: %.3f", lens_ca);
            }
            if (input_key_pressed(inp, 56)) {
                lens_vignette = lens_vignette > 0.1f ? 0.0f : lens_vignette + 0.15f;
                LOG_INFO("Vignette: %.2f", lens_vignette);
            }
        }

        {
            InputState *inp = platform_input(engine.platform);
            if (input_key_pressed(inp, '=')) tonemap.exposure = fminf(tonemap.exposure + 0.2f, 8.0f);
            if (input_key_pressed(inp, '-')) tonemap.exposure = fmaxf(tonemap.exposure - 0.2f, 0.1f);
            if (input_key_pressed(inp, 283)) { tonemap.auto_exposure = !tonemap.auto_exposure; LOG_INFO("Auto-exposure: %s", tonemap.auto_exposure ? "on" : "off"); }
        }

        bool need_rebuild = false;
        if (w != frame_w || h != frame_h) {
            rhi_device_resize(render.device, w, h);
            camera.aspect = (f32)w / (f32)(h > 0 ? h : 1); /* R142: guard h==0 */
            need_rebuild = true;
        }
        u32 new_rw = (u32)(w * render_scale); if (new_rw < 1) new_rw = 1;
        u32 new_rh = (u32)(h * render_scale); if (new_rh < 1) new_rh = 1;
        if (new_rw != rw || new_rh != rh) need_rebuild = true;

        if (need_rebuild) {
            rw = new_rw;
            rh = new_rh;
            if (rhi_handle_valid(scene_fbo.fb)) rhi_offscreen_fbo_destroy(render.device, &scene_fbo);
            scene_fbo = rhi_offscreen_fbo_create_fmt(render.device, rw, rh, RHI_FORMAT_R16G16B16A16_SFLOAT);
            post_process_shutdown(&postfx);
            ssao_shutdown(&ssao);
            taa_shutdown(&taa);
            ssr_shutdown(&ssr_sys);
            dof_shutdown(&dof_sys);
            volumetric_shutdown(&vol);
            tonemap_shutdown(&tonemap);
            fxaa_shutdown(&fxaa_sys);
            ssgi_shutdown(&ssgi_sys);
            lens_flare_shutdown(&lens_flare);
            sharpen_shutdown(&sharpen_sys);
            motion_blur_shutdown(&motion_blur);
            contact_shadow_shutdown(&contact_shadow);
            sss_shutdown(&sss_sys);
            upscale_shutdown(&upscale_sys);
            color_grade_shutdown(&cg_sys);
            god_rays_shutdown(&gr_sys);
            debug_viz_shutdown(&debug_viz);
            lens_effects_shutdown(&lens_fx);
            combined_aa_shutdown(&combined_aa);
            combined_color_shutdown(&combined_color);
            post_process_init(&postfx, render.device, rw, rh);
            ssao_init(&ssao, render.device, rw, rh);
            taa_init(&taa, render.device, rw, rh);
            ssr_init(&ssr_sys, render.device, rw, rh);
            dof_init(&dof_sys, render.device, rw, rh);
            volumetric_init(&vol, render.device, rw, rh);
            tonemap_init(&tonemap, render.device);
            fxaa_init(&fxaa_sys, render.device, rw, rh);
            ssgi_init(&ssgi_sys, render.device, rw, rh);
            lens_flare_init(&lens_flare, render.device, rw, rh);
            sharpen_init(&sharpen_sys, render.device, rw, rh);
            motion_blur_init(&motion_blur, render.device, rw, rh);
            contact_shadow_init(&contact_shadow, render.device, rw, rh);
            sss_init(&sss_sys, render.device, rw, rh);
            upscale_init(&upscale_sys, render.device, rw, rh, w, h);
            color_grade_init(&cg_sys, render.device, rw, rh);
            god_rays_init(&gr_sys, render.device, rw, rh);
            debug_viz_init(&debug_viz, render.device, rw, rh);
            lens_effects_init(&lens_fx, render.device, rw, rh);
            combined_aa_init(&combined_aa, render.device, rw, rh);
            combined_color_init(&combined_color, render.device, rw, rh);
            forward_velocity_shutdown(&forward_vel);
            forward_velocity_init(&forward_vel, render.device, rw, rh);
            occlusion_cull_resize(&occ_sys, rw, rh);
            deferred_resize(&render.deferred, render.device, rw, rh);
            frame_w = w;
            frame_h = h;
        }

u32 draw_calls = 0;
u32 tri_count = 0;
u32 culled_count = 0;
        draw_bench_reset();
        if (playing_path && path_count > 0) {
            camera.position.e[0] = cam_path[path_idx].px;
            camera.position.e[1] = cam_path[path_idx].py;
            camera.position.e[2] = cam_path[path_idx].pz;
            camera.yaw = cam_path[path_idx].yaw;
            camera.pitch = cam_path[path_idx].pitch;
            /* R60-fix: Update cached trig to match new yaw/pitch.
             * Without camera_update call, _cy/_sy/_cp/_sp would be stale. */
            camera._cy = cosf(camera.yaw); camera._sy = sinf(camera.yaw);
            camera._cp = cosf(camera.pitch); camera._sp = sinf(camera.pitch);
            path_idx = (path_idx + 1) % path_count;
        } else {
            if (!imui_visible)
                camera_update(&camera, platform_input(engine.platform), (f32)engine.delta_time);
            if (engine.frame_count > 1) {
                f32 cdist = vec3_len(vec3_sub(camera.position, camera_prev_pos));
                camera_distance_traveled += cdist;
                camera_frame_dist = cdist;
            }
            camera_prev_pos = camera.position;
        }
        if (recording_path && path_count < MAX_PATH) {
            cam_path[path_count].px = camera.position.e[0];
            cam_path[path_count].py = camera.position.e[1];
            cam_path[path_count].pz = camera.position.e[2];
            cam_path[path_count].yaw = camera.yaw;
            cam_path[path_count].pitch = camera.pitch;
            path_count++;
        }
        if (recording_path && path_count >= MAX_PATH) {
            recording_path = false;
            LOG_INFO("Path recording FULL (%u frames). Press , to playback.", path_count);
        }
        if (cam_height_lock) {
            camera.position.e[1] = cam_locked_y;
        }
        /* R52: Reuse trig cached by camera_update (avoids 4 redundant cosf/sinf per frame). */
        f32 cam_cy = camera._cy, cam_sy = camera._sy;
        f32 cam_cp = camera._cp, cam_sp = camera._sp;
        /* R60-fix: Forward direction MUST match camera_view/camera_update convention.
         * camera_view forward f = (cp*sy, sp, -cp*cy) — yaw=0 faces -Z (standard FPS).
         * Old formula (cy*cp, sp, sy*cp) was perpendicular to actual forward at pitch=0. */
        Vec3 cam_fwd = vec3(cam_cp * cam_sy, cam_sp, -cam_cp * cam_cy);
        /* R54: Static identity matrix — avoids 16 float stores per frame. */
        static const Mat4 frame_identity = {{{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}}};
        if (ui.visible) {
        {
            /* Throttle terrain stats to every 10 frames (debug UI only) */
            static u32 terrain_stats_frame = 0;
            if (engine.frame_count - terrain_stats_frame >= 10 || terrain_stats_frame == 0) {
                terrain_stats_frame = (u32)engine.frame_count;
                f32 hmin = 1e9f, hmax = -1e9f;
                f32 hsum = 0.0f, hsum2 = 0.0f;
                u32 n = terrain.grid_size;
                u32 nn = n * n;
                u32 underwater_count = 0;
                f32 water_depth_sum = 0.0f;
                f32 water_depth_max_l = 0.0f;
                f32 water_cx_sum = 0.0f, water_cz_sum = 0.0f;
                f32 max_slope_val = 0.0f;
                u32 max_slope_idx = 0;
                u32 shoreline = 0;
                f32 wy = water.water_y;
                for (u32 i = 0; i < nn; i++) {
                    f32 h = terrain.heightmap[i];
                    if (h < hmin) hmin = h;
                    if (h > hmax) hmax = h;
                    hsum += h;
                    hsum2 += h * h;
                    u32 gx = i % n, gz = i / n;
                    bool below = h < wy;
                    if (below) {
                        underwater_count++;
                        f32 wd = wy - h;
                        water_depth_sum += wd;
                        if (wd > water_depth_max_l) water_depth_max_l = wd;
                        water_cx_sum += (f32)gx * wd;
                        water_cz_sum += (f32)gz * wd;
                    }
                    if (gx > 0 && gx < n-1 && gz > 0 && gz < n-1) {
                        f32 sdx = terrain.heightmap[i+1] - terrain.heightmap[i-1];
                        f32 sdz = terrain.heightmap[(gz+1)*n + gx] - terrain.heightmap[(gz-1)*n + gx];
                        f32 sl = sdx*sdx + sdz*sdz;
                        if (sl > max_slope_val) { max_slope_val = sl; max_slope_idx = i; }
                    }
                    if (below) {
                        if (gx > 0 && terrain.heightmap[gz*n+gx-1] >= wy) shoreline++;
                        if (gx < n-1 && terrain.heightmap[gz*n+gx+1] >= wy) shoreline++;
                        if (gz > 0 && terrain.heightmap[(gz-1)*n+gx] >= wy) shoreline++;
                        if (gz < n-1 && terrain.heightmap[(gz+1)*n+gx] >= wy) shoreline++;
                    }
                }
                f32 havg = hsum / (f32)nn;
                f32 hvar = hsum2 / (f32)nn - havg * havg;
                terrain_hstd = sqrtf(hvar > 0.0f ? hvar : 0.0f);
                static f32 prev_hstd = 0.0f;
                terrain_hstd_delta = terrain_hstd - prev_hstd;
                prev_hstd = terrain_hstd;
                terrain_water_pct = (f32)underwater_count / (f32)nn * 100.0f;
                f32 cell_area = terrain.scale * terrain.scale / (f32)((n - 1) * (n - 1));
                terrain_water_vol = water_depth_sum * cell_area;
                terrain_water_depth_avg = underwater_count > 0 ? water_depth_sum / (f32)underwater_count : 0.0f;
                terrain_water_depth_max = water_depth_max_l;
                terrain_water_cx = water_depth_sum > 0.01f ? water_cx_sum / water_depth_sum / (f32)n * terrain.scale : 0.0f;
                terrain_water_cz = water_depth_sum > 0.01f ? water_cz_sum / water_depth_sum / (f32)n * terrain.scale : 0.0f;
                terrain_shoreline = shoreline;
                terrain_hmin = hmin; terrain_hmax = hmax; terrain_havg = havg;
                if (max_slope_val > 0.0f) {
                    f32 ms_gx = ((f32)(max_slope_idx % n) / (f32)(n-1) - 0.5f) * terrain.scale;
                    f32 ms_gz = ((f32)(max_slope_idx / n) / (f32)(n-1) - 0.5f) * terrain.scale;
                    f32 ms_deg = atanf(sqrtf(max_slope_val) * 0.5f) * 57.2958f;
                    if (ms_deg > 5.0f) {
                        debug_ui_text(&ui, "Terrain max slope: %.1f° at (%.0f, %.0f)", ms_deg, ms_gx, ms_gz);
                    }
                }
            }
        }
        } /* end terrain stats ui.visible gate */
        /* Cache camera terrain height once per frame (avoids 3+ redundant lookups at same xz). */
        f32 cam_terrain_h = terrain_get_height(&terrain, camera.position.e[0], camera.position.e[2]);
        if (terrain_follow) {
            camera.position.e[1] = cam_terrain_h + 1.7f;
        }
        {
            InputState *iscroll = platform_input(engine.platform);
            if (iscroll->scroll_dy != 0.0f) {
                camera.fov = fmaxf(20.0f, fminf(camera.fov - iscroll->scroll_dy * 5.0f, 120.0f));
            }
        }

        if (input_key_pressed(platform_input(engine.platform), 259)) {
            debug_ui_toggle(&ui);
        }

        /* Backtick (`) toggles the immediate-mode settings panel. */
        if (imui_font_ready && input_key_pressed(platform_input(engine.platform), 96)) {
            imui_visible = !imui_visible;
        }

        hotreload_pipeline_poll(&hotreload);
        if (hotreload_tex_ready) hotreload_texture_poll(&hotreload_tex);

        if (netrep_enabled) {
            u32 prev_hb = net_rep.hb_recv;
            u32 prev_hb_rt = net_rep.hb_roundtrip_recv;
            for (;;) {
                u32 hb_at_start = net_rep.hb_recv;
                u32 hb_rt_at_start = net_rep.hb_roundtrip_recv;
                u32 ord_pending = net_rep.ordered[NET_PKT_TRANSFORM_SNAPSHOT].reorder_pending;
                u32 recv_count = 0;
                NetAddress from = {0};
                i32 n = net_replicator_recv(&net_rep, netrep_last, NET_REPL_MAX_SNAPSHOTS,
                                            &recv_count, &from);
                if (n <= 0) break;
                if (recv_count == 0u && ord_pending == 0u &&
                    net_rep.hb_recv == hb_at_start &&
                    net_rep.hb_roundtrip_recv == hb_rt_at_start)
                    netrep_stale++;
                if (recv_count > 0) {
                    netrep_recv++;
                    netrep_last_count = recv_count;
                    if (netrep_apply && netrep_ghost_valid) {
                        for (u32 ri = 0; ri < recv_count; ri++) {
                            if (netrep_last[ri].entity_id != 1u) continue;
                            CTransform *gt = world_get_component(world, netrep_ghost, COMP_TRANSFORM);
                            if (!gt) break;
                            if (netrep_lerp) {
                                netrep_ghost_target[0] = netrep_last[ri].position[0];
                                netrep_ghost_target[1] = netrep_last[ri].position[1];
                                netrep_ghost_target[2] = netrep_last[ri].position[2];
                            } else {
                                gt->pos[0] = netrep_last[ri].position[0];
                                gt->pos[1] = netrep_last[ri].position[1];
                                gt->pos[2] = netrep_last[ri].position[2];
                            }
                            break;
                        }
                    }
                }
            }
            if (net_rep.hb_roundtrip_recv > prev_hb_rt) {
                netrep_hb_rt_ms = net_rep.hb_roundtrip_ms;
            } else if (net_rep.hb_recv > prev_hb) {
                netrep_hb_recv = net_rep.hb_recv;
                netrep_hb_rtt_ms = net_rep.hb_last_rtt_ms;
            }
            netrep_hb_echo = net_rep.hb_echo_sent;
            netrep_reordered = net_rep.ordered[NET_PKT_TRANSFORM_SNAPSHOT].reorder_delivered;
            netrep_reord_dup = net_rep.ordered[NET_PKT_TRANSFORM_SNAPSHOT].reorder_duplicate;
            if (engine.frame_count % 10u == 0u) {
                net_replicator_retry_pending(&net_rep);
                netrep_retries = net_rep.retry_count;
                Vec3 pos = character_get_position(&character);
                NetTransformSnapshot snap = {
                    .entity_id = 1u,
                    .position = { pos.e[0], pos.e[1], pos.e[2] },
                };
                if (net_replicator_broadcast(&net_rep, &snap, 1u, &net_rep_dst) > 0)
                    netrep_sent++;
            }
            if (netrep_heartbeat && engine.frame_count % 60u == 0u) {
                u32 now_ms = (u32)(time_microseconds() / 1000ull);
                net_replicator_peer_evict_stale(&net_rep, now_ms);
                if (netrep_peer_dir[0]) {
                    char delta_path[320];
                    snprintf(delta_path, sizeof(delta_path), "%s/delta.log", netrep_peer_dir);
                    net_replicator_peer_save_delta(&net_rep, delta_path);
                }
                if (net_replicator_send_heartbeat(&net_rep, &net_rep_dst, now_ms) > 0)
                    netrep_hb_sent = net_rep.hb_sent;
            }
        }

        if (netrep_enabled && netrep_apply && netrep_ghost_valid && netrep_lerp) {
            CTransform *gt = world_get_component(world, netrep_ghost, COMP_TRANSFORM);
            if (gt) {
                f32 t = fminf(1.0f, (f32)engine.delta_time * 12.0f);
                gt->pos[0] += (netrep_ghost_target[0] - gt->pos[0]) * t;
                gt->pos[1] += (netrep_ghost_target[1] - gt->pos[1]) * t;
                gt->pos[2] += (netrep_ghost_target[2] - gt->pos[2]) * t;
            }
        }

        async_loader_tick();

        /* Round 10: drive mipmap streaming from camera proximity to the origin.
         * Closer camera -> higher coverage -> finer mip streamed in; moving away
         * lowers coverage and lets the budget evict the fine levels. */
        if (mip_stream_idx >= 0) {
            f32 cam_dist = vec3_len(camera.position);
            f32 coverage = 12.0f / (cam_dist + 1.0f);
            if (coverage > 1.0f) coverage = 1.0f;
            mipmap_stream_update_visibility(&mip_stream, mip_stream_idx,
                                            coverage, engine.frame_count);
            mipmap_stream_update(&mip_stream);
        }

        script_reload_if_changed(&script, "assets/init.script");
        if (lua_ready) {
            lua_script_reload_if_changed(&lua_script);
            lua_script_call_update(&lua_script, (f32)engine.delta_time);
        }

        /* Update audio listener from camera orientation */
        {
            Vec3 up  = vec3(0, 1, 0);
            audio_system_update(audio, camera.position, cam_fwd, up);
            if (audio_stream_id >= 0) audio_stream_update(&audio_stream_mgr);
        }

        /* Use hot-reloaded pipeline as active pipeline when available */
        RHIPipeline active_pipeline = wireframe_mode && rhi_handle_valid(render.wire_pipeline) ? render.wire_pipeline : render.pipeline;
        if (hotreload.ready && rhi_handle_valid(hotreload.pipeline)) {
            active_pipeline = hotreload.pipeline;
            if (hotreload.pipeline.index != last_hr_pipeline.index ||
                hotreload.pipeline.generation != last_hr_pipeline.generation) {
                /* Pipeline changed — re-query uniform locations */
                render.loc_model       = rhi_pipeline_get_uniform_location(render.device, active_pipeline, "u_model");
                render.loc_view        = rhi_pipeline_get_uniform_location(render.device, active_pipeline, "u_view");
                render.loc_proj        = rhi_pipeline_get_uniform_location(render.device, active_pipeline, "u_proj");
                render.loc_light_dir   = rhi_pipeline_get_uniform_location(render.device, active_pipeline, "u_light_dir");
                render.loc_light_color = rhi_pipeline_get_uniform_location(render.device, active_pipeline, "u_light_color");
                render.loc_ambient     = rhi_pipeline_get_uniform_location(render.device, active_pipeline, "u_ambient");
                render.loc_camera_pos  = rhi_pipeline_get_uniform_location(render.device, active_pipeline, "u_camera_pos");
                render.loc_albedo      = rhi_pipeline_get_uniform_location(render.device, active_pipeline, "u_albedo");
                last_hr_pipeline = hotreload.pipeline;
            }
        }

        if (input_key_pressed(platform_input(engine.platform), 275)) {
            gravity_well = !gravity_well;
            LOG_INFO("Gravity well: %s", gravity_well ? "ON (attracts entities to camera)" : "OFF");
        }

        /* B: Save scene (BSCN binary)  N: Load scene  Shift+B: Export JSON */
        if (input_key_pressed(platform_input(engine.platform), (i32)'b')) {
            InputState *bs_inp = platform_input(engine.platform);
            bool shift_held = input_key_down(bs_inp, 340) || input_key_down(bs_inp, 344);
            if (shift_held) {
                /* Export as JSON for debugging / interoperability. */
                SerializeOptions opts = { .pretty_json = true };
                if (scene_save_json(world, &scene, "scene_export.json", &opts))
                    LOG_INFO("Scene exported to scene_export.json (JSON)");
                else
                    LOG_ERROR("JSON export failed");
            } else {
                /* Save BSCN binary (ECS entities + scene graph). */
                if (scene_save_binary(world, &scene, "scene_save.bscn", NULL))
                    LOG_INFO("Scene saved (BSCN binary)");
                else
                    LOG_ERROR("BSCN save failed");
                /* Companion state file for runtime data (camera, physics, rendering). */
                FILE *sf = fopen("scene_state.bin", "wb");
                if (sf) {
                    bool sv_ok = true;
                    u32 magic = 0x534E4547u;
                    sv_ok &= fwrite(&magic, 4, 1, sf) == 1;
                    sv_ok &= fwrite(&camera.position, sizeof(Camera), 1, sf) == 1;
                    sv_ok &= fwrite(&sun_azimuth, sizeof(f32), 1, sf) == 1;
                    sv_ok &= fwrite(&sun_elevation, sizeof(f32), 1, sf) == 1;
                    sv_ok &= fwrite(&tonemap.exposure, sizeof(f32), 1, sf) == 1;
                    sv_ok &= fwrite(&render_scale, sizeof(f32), 1, sf) == 1;
                    u32 pc = physics->count;
                    sv_ok &= fwrite(&pc, sizeof(u32), 1, sf) == 1;
                    for (u32 si = 0; si < pc && sv_ok; si++) {
                        sv_ok &= fwrite(&physics->bodies[si].position, sizeof(Vec3), 1, sf) == 1;
                        sv_ok &= fwrite(&physics->bodies[si].velocity, sizeof(Vec3), 1, sf) == 1;
                    }
                    sv_ok &= fwrite(&water.water_y, sizeof(f32), 1, sf) == 1;
                    sv_ok &= fwrite(&water.enabled, sizeof(bool), 1, sf) == 1;
                    fclose(sf);
                    if (!sv_ok) LOG_WARN("Scene state save: partial write failure");
                }
            }
        }
        if (input_key_pressed(platform_input(engine.platform), (i32)'n')) {
            /* Load BSCN binary (ECS entities + scene graph). */
            if (scene_load_binary(world, &scene, "scene_save.bscn"))
                LOG_INFO("Scene loaded (BSCN binary)");
            else
                LOG_WARN("BSCN load failed or file not found");
            /* Restore companion runtime state. */
            FILE *lf = fopen("scene_state.bin", "rb");
            if (lf) {
                u32 magic = 0;
                bool ld_ok = fread(&magic, 4, 1, lf) == 1;
                if (ld_ok && magic == 0x534E4547u) {
                    ld_ok &= fread(&camera.position, sizeof(Camera), 1, lf) == 1;
                    ld_ok &= fread(&sun_azimuth, sizeof(f32), 1, lf) == 1;
                    ld_ok &= fread(&sun_elevation, sizeof(f32), 1, lf) == 1;
                    ld_ok &= fread(&tonemap.exposure, sizeof(f32), 1, lf) == 1;
                    ld_ok &= fread(&render_scale, sizeof(f32), 1, lf) == 1;
                    u32 pc = 0;
                    ld_ok &= fread(&pc, sizeof(u32), 1, lf) == 1;
                    for (u32 si = 0; si < pc && si < physics->capacity && ld_ok; si++) {
                        if (si < physics->count) {
                            ld_ok &= fread(&physics->bodies[si].position, sizeof(Vec3), 1, lf) == 1;
                            ld_ok &= fread(&physics->bodies[si].velocity, sizeof(Vec3), 1, lf) == 1;
                        } else {
                            Vec3 skip;
                            ld_ok &= fread(&skip, sizeof(Vec3), 1, lf) == 1;
                            ld_ok &= fread(&skip, sizeof(Vec3), 1, lf) == 1;
                        }
                    }
                    if (ld_ok && !feof(lf)) {
                        ld_ok &= fread(&water.water_y, sizeof(f32), 1, lf) == 1;
                        ld_ok &= fread(&water.enabled, sizeof(bool), 1, lf) == 1;
                    }
                    if (!ld_ok) LOG_WARN("Scene state load: partial read failure");
                    LOG_INFO("Runtime state restored (%u bodies)", pc);
                }
                fclose(lf);
            }
        }

        profiler_push("physics");
        physics_step(physics, slow_motion ? (f32)engine.delta_time * 0.25f : (f32)engine.delta_time);
        if (physics->collision_count > prev_collision_count) {
            u32 new_cols = physics->collision_count - prev_collision_count;
            screen_shake += 0.15f * (f32)new_cols;
            if (screen_shake > 1.5f) screen_shake = 1.5f;
            if (new_cols > collision_peak) collision_peak = new_cols;
            collision_flash = 1.0f;
            last_collision_pos = physics->last_collision_pos;
            last_collision_frame = engine.frame_count;
        }
        prev_collision_count = physics->collision_count;
        if (collision_flash > 0.0f) collision_flash -= (f32)engine.delta_time * 3.0f;

        if (tornado_mode) {
            for (u32 ti = 0; ti < physics->count; ti++) {
                if (physics->bodies[ti].is_static) continue;
                Vec3 bp = physics->bodies[ti].position;
                f32 dx = bp.e[0], dz = bp.e[2];
                f32 d2 = dx*dx + dz*dz;
                if (d2 < 0.0001f) continue;  /* R51: compare dist² instead of dist */
                f32 inv_dist = fast_rsqrt(d2);
                f32 dist = d2 * inv_dist;
                f32 strength = 15.0f / (1.0f + dist * 0.3f);
                f32 idt = inv_dist * strength * (f32)engine.delta_time;
                physics->bodies[ti].velocity.e[0] += (-dz) * idt;
                physics->bodies[ti].velocity.e[2] += ( dx) * idt;
                physics->bodies[ti].velocity.e[1] += 2.0f * (f32)engine.delta_time;
            }
        }

        InputState *inp = platform_input(engine.platform);
        Vec3 move_input = vec3(0, 0, 0);
        if (input_key_down(inp, 97))  move_input.e[0] -= 1;
        if (input_key_down(inp, 100)) move_input.e[0] += 1;
        if (input_key_down(inp, 119)) move_input.e[2] -= 1;
        if (input_key_down(inp, 115)) move_input.e[2] += 1;
        character_update(&character, physics, (f32)engine.delta_time, move_input,
                          input_key_pressed(inp, 32));
        profiler_pop();

        profiler_pop();

        profiler_push("ecs_query");
        {
            /* Task-parallel ECS system: physics -> transform sync (Round 6). */
            ComponentType sync_types[] = { COMP_TRANSFORM, COMP_RIGID_BODY };
            ecs_parallel_for(world, tasks, sync_types, 2,
                             sys_sync_transform_from_physics, physics);
        }
        if (velocity_damping) {
            for (u32 bi = 1; bi < physics->count; bi++) {
                if (!physics->bodies[bi].is_static) {
                    physics->bodies[bi].velocity.e[0] *= 0.95f;
                    physics->bodies[bi].velocity.e[1] *= 0.95f;
                    physics->bodies[bi].velocity.e[2] *= 0.95f;
                }
            }
        }
        profiler_pop();

        Mat4 view = camera_view(&camera);
        if (third_person) {
            /* Third-person: move effective eye back by fwd*tp.
             * In row-major view matrix V = [R | t], translation is in e[i][3] (col 3).
             * New translation = t + R*fwd*tp. Since R*cam_fwd is the view-space offset,
             * modify translation column e[i][3] for i=0,1,2. */
            f32 tp = third_person_dist;
            f32 dx = cam_fwd.e[0], dy = cam_fwd.e[1], dz = cam_fwd.e[2];
            /* R*cam_fwd: row i of R dotted with cam_fwd */
            view.e[0][3] += (view.e[0][0]*dx + view.e[0][1]*dy + view.e[0][2]*dz) * tp;
            view.e[1][3] += (view.e[1][0]*dx + view.e[1][1]*dy + view.e[1][2]*dz) * tp;
            view.e[2][3] += (view.e[2][0]*dx + view.e[2][1]*dy + view.e[2][2]*dz) * tp;
        } else if (top_down_view) {
            /* top_down replaces view entirely; not combinable with third_person */
            view = mat4_lookat(
                vec3(camera.position.e[0], camera.position.e[1] + 30.0f, camera.position.e[2]),
                camera.position,
                vec3(0.0f, 0.0f, -1.0f)
            );
        }
        Mat4 proj = camera_projection(&camera);

        {
            /* R48: Precomputed Halton(2,3) jitter offsets for 16 TAA samples.
             * Eliminates 2 per-frame loops with variable iteration count. */
            static const f32 halton_jitter[16][2] = {
                {  0.000000f, -0.333333f}, { -0.500000f,  0.333333f},
                {  0.500000f, -0.777778f}, { -0.750000f, -0.111111f},
                {  0.250000f,  0.555556f}, { -0.250000f, -0.555556f},
                {  0.750000f,  0.111111f}, { -0.875000f,  0.777778f},
                {  0.125000f, -0.925926f}, { -0.375000f, -0.259259f},
                {  0.625000f,  0.407407f}, { -0.625000f, -0.703704f},
                {  0.375000f, -0.037037f}, { -0.125000f,  0.629630f},
                {  0.875000f, -0.481481f}, { -0.937500f,  0.185185f}
            };
            u32 idx = taa_frame % 16;
            proj.e[2][0] += halton_jitter[idx][0] / (f32)w;
            proj.e[2][1] += halton_jitter[idx][1] / (f32)h;
        }
        if (screen_shake > 0.001f) {
            /* R57-fix: Hash-based pseudo-random shake — avoids 2× sinf/cosf per frame.
             * Previous quadratic approx was wrong for large angles; hash gives good
             * randomness without any trig. Shake only affects proj.e[2][0..1] by ≤0.015. */
            u32 fc = engine.frame_count;
            u32 h = fc * 1103515245u + 12345u;          /* LCG hash */
            f32 shx = (f32)(h & 0xFFFF) * (1.0f / 65536.0f) - 0.5f;  /* [-0.5, 0.5] */
            f32 shy = (f32)((h >> 16) & 0xFFFF) * (1.0f / 65536.0f) - 0.5f;
            proj.e[2][0] += (shx * 0.02f) * screen_shake;
            proj.e[2][1] += (shy * 0.02f) * screen_shake;
            screen_shake *= 0.92f;
        } else {
            screen_shake = 0.0f;
        }
        Mat4 curr_view_proj = mat4_mul_proj_view(proj, view);
        Frustum frame_frustum = frustum_from_vp(&curr_view_proj);
        /* Pre-compute inverse projection once for skybox + all post-effects.
         * R47+R53-fix: Analytical inv(proj) includes TAA jitter / screen shake.
         * Only 3 divisions + 6 muls vs generic mat4_inverse (~120 muls + 1 div). */
        Mat4 frame_inv_proj = mat4_inv_perspective(proj);

        bool underwater = water.enabled && camera.position.e[1] < water.water_y;
        debug_ui_begin(&ui);
        fps_history[fps_history_idx % 64] = (f32)engine.delta_time * 1000.0f;
        fps_history_idx++;

        /* Compute dynamic-body CoM once per frame — used for both drift accumulation
         * (after the ui.visible gate) and display (inside the gate). */
        Vec3 frame_com = vec3(0,0,0);
        f32 frame_com_mass = 0.0f;
        if (physics->count > 1) {
            for (u32 bi = 1; bi < physics->count; bi++) {
                if (physics->bodies[bi].is_static) continue;
                frame_com.e[0] += physics->bodies[bi].mass * physics->bodies[bi].position.e[0];
                frame_com.e[1] += physics->bodies[bi].mass * physics->bodies[bi].position.e[1];
                frame_com.e[2] += physics->bodies[bi].mass * physics->bodies[bi].position.e[2];
                frame_com_mass += physics->bodies[bi].mass;
            }
            if (frame_com_mass > 0.01f)
                frame_com = vec3_scale(frame_com, 1.0f / frame_com_mass);
        }

        if (ui.visible) {
            debug_ui_text(&ui, "FPS: %.0f (%.2f ms)  Pos: (%.1f,%.1f,%.1f)  Speed: %.0f  Sun: %.1f/%.1f (%.0f°/%.0f°)  VSync: %s%s", engine.fps, engine.delta_time * 1000.0, camera.position.e[0], camera.position.e[1], camera.position.e[2], camera.move_speed, sun_azimuth, sun_elevation, sun_azimuth * 57.2958f, sun_elevation * 57.2958f, vsync_on ? "on" : "off", tod_cycle ? "  [TOD]" : "");
            {
                f32 tod_hours = fmodf(sun_azimuth / (2.0f * 3.14159265f) * 24.0f + 12.0f, 24.0f);
                u32 hh = (u32)tod_hours;
                u32 mm = (u32)((tod_hours - (f32)hh) * 60.0f);
                static const char *daynight[] = {"Night", "Dawn", "Morning", "Noon", "Afternoon", "Dusk", "Evening", "Night"};
                u32 dn = hh < 4 ? 7 : hh < 6 ? 1 : hh < 10 ? 2 : hh < 14 ? 3 : hh < 17 ? 4 : hh < 19 ? 5 : hh < 21 ? 6 : 7;
                debug_ui_text(&ui, "Time: %02u:%02u (%s)", hh, mm, daynight[dn]);
            }
            {
                static f32 fps_min = 9999.0f, fps_max = 0.0f;
                if (engine.frame_count > 30) {
                    f32 cur_fps = (f32)engine.fps;
                    if (cur_fps < fps_min) fps_min = cur_fps;
                    if (cur_fps > fps_max) fps_max = cur_fps;
                    if (fps_max > fps_min) debug_ui_text(&ui, "FPS range: %.0f - %.0f  %s", fps_min, fps_max, (fps_max - fps_min) > fps_min * 0.2f ? "[UNSTABLE]" : "[stable]");
                }
            }
            {
                debug_ui_text(&ui, "Terrain height: %.2f  Above: %.2f", cam_terrain_h, camera.position.e[1] - cam_terrain_h);
            }
            {
                f32 fwd_x = cam_fwd.e[0], fwd_y = cam_fwd.e[1], fwd_z = cam_fwd.e[2];
                f32 rx = camera.position.e[0], ry = camera.position.e[1], rz = camera.position.e[2];
                f32 step_sz = 0.5f;
                bool hit = false;
                f32 hit_h = 0.0f;
                for (i32 ri = 0; ri < 200; ri++) {
                    rx += fwd_x * step_sz; ry += fwd_y * step_sz; rz += fwd_z * step_sz;
                    if (rx < 0 || rz < 0 || rx >= (f32)terrain.grid_size * terrain.scale || rz >= (f32)terrain.grid_size * terrain.scale) break;
                    f32 rh = terrain_get_height(&terrain, rx, rz);
                    if (ry <= rh) { hit = true; hit_h = rh; break; }
                }
                if (hit) {
                    f32 rd2 = (rx - camera.position.e[0])*(rx - camera.position.e[0]) + (rz - camera.position.e[2])*(rz - camera.position.e[2]);
                    f32 rd = rd2 > 1e-12f ? rd2 * fast_rsqrt(rd2) : 0.0f;
                    debug_ui_text(&ui, "Look-at terrain: (%.1f,%.1f,%.1f) dist=%.1f", rx, hit_h, rz, rd);
                }
            }
        {
            static const char bars[] = " .:;+=xX#";
            char graph[68] = "Frame: [";
            u32 gi;
            for (gi = 0; gi < 56; gi++) {
                u32 hidx = (fps_history_idx + gi) % 64;
                f32 ms = fps_history[hidx];
                u32 lvl = ms > 33.3f ? 8 : ms > 16.7f ? (u32)(ms / 4.2f) : (u32)(ms / 2.1f);
                if (lvl > 8) lvl = 8;
                graph[8 + gi] = bars[lvl];
            }
            graph[8 + gi] = ']';
            graph[8 + gi + 1] = '\0';
            f32 avg_ms = 0.0f;
            for (u32 ai = 0; ai < 64; ai++) avg_ms += fps_history[ai];
            avg_ms /= 64.0f;
            debug_ui_text(&ui, "%s avg=%.1fms", graph, avg_ms);
        }
        if (bench_frames > 0)
            debug_ui_text(&ui, ">>> BENCHMARK: %d frames remaining <<<", bench_frames);
        if (bench_result_show > 0) {
            f64 bavg = bench_start / 120.0 * 1000.0;
            debug_ui_text(&ui, "BENCHMARK RESULT: %.2f ms avg (%.0f FPS bare)", bavg, 1000.0 / bavg);
        }
        debug_ui_text(&ui, "Render: %ux%u -> %ux%u (%.0f%%)", rw, rh, w, h, render_scale * 100.0f);
        debug_ui_text(&ui, "Shadow cascades: [%.2f, %.2f, %.2f, %.2f, %.2f]", render.cascade_splits[0], render.cascade_splits[1], render.cascade_splits[2], render.cascade_splits[3], render.cascade_splits[4]);
        debug_ui_text(&ui, "Entities: %u  Physics: %u/%u  Collisions: %u  Draws: %u  Tris: %u  Culled: %u%s%s",
                      world->entity_count - 1, physics->count, physics->capacity, physics->collision_count, draw_calls, tri_count, culled_count,
                      wireframe_mode ? "  [WIREFRAME]" : "",
                      !gravity_enabled ? "  [ZERO-G]" : velocity_damping ? "  [DAMPING]" : "",
                      physics_mode == 3 ? "  [CUSTOM-G]" : "");
        {
            Vec3 eff_grav = physics_mode == 0 ? vec3(0, -9.81f, 0) : physics_mode == 3 ? custom_gravity : vec3(0,0,0);
            debug_ui_text(&ui, "Gravity: (%.1f,%.1f,%.1f) mode=%u", eff_grav.e[0], eff_grav.e[1], eff_grav.e[2], physics_mode);
        }
        {
            /* Throttle physics debug stats to every 10 frames (7+ O(n) loops incl. one O(n²)). */
            static u32 phys_stats_frame = 0;
            if (engine.frame_count - phys_stats_frame >= 10 || phys_stats_frame == 0) {
            phys_stats_frame = (u32)engine.frame_count;
            f32 max_speed = 0.0f;
            u32 fastest_id = 0;
            static f32 speed_record = 0.0f;
            static f32 prev_total_ke = 0.0f;
            static f32 prev_total_energy = 0.0f;
            f32 max_accel = 0.0f;
            f32 max_vy_up = 0.0f, max_vy_down = 0.0f;
            u32 vy_b[4] = {0, 0, 0, 0};
            f32 max_ke = 0.0f;
            u32 max_ke_id = 0;
            f32 total_ke = 0.0f;
            f32 total_mass = 0.0f;
            f32 total_pe = 0.0f;
            f32 speed_sum = 0.0f;
            Vec3 vel_sum = vec3(0, 0, 0);
            f32 mass_speed_sum = 0.0f;
            f32 speed_sq_sum = 0.0f;
            f32 vx2 = 0.0f, vy2 = 0.0f, vz2 = 0.0f;
            u32 moving = 0;
            u32 static_count = 0;
            u32 falling_count = 0;
            u32 grounded_count = 0;
            u32 resting_count = 0;
            f32 rest_ke = 0.0f;
            f32 rest_mass = 0.0f;
            f32 max_displacement = 0.0f;
            u32 max_disp_id = 0;
            f32 avg_displacement = 0.0f;
            u32 hottest_body = 0;
            u32 hottest_cols = 0;
            u32 sb[4] = {0, 0, 0, 0};
            u32 kb[4] = {0, 0, 0, 0};
            u32 pb[4] = {0, 0, 0, 0};
            u32 agl_b[4] = {0, 0, 0, 0};
            f32 farthest_dist = 0.0f;
            u32 farthest_id = 0;
            f32 nearest_dist = 1e9f;
            u32 nearest_id = 0;
            u32 in_front = 0;
            f32 min_agl = 1e9f;
            u32 min_agl_id = 0;
            f32 avg_agl = 0.0f;
            u32 agl_count = 0;
            u32 dyn_count = 0;
            f32 age_sum = 0.0f;
            u32 age_young = 0, age_mid = 0, age_old = 0, age_ancient = 0;
            f32 min_y = 1e9f, max_y = -1e9f;
            for (u32 bi = 1; bi < physics->count; bi++) {
                if (physics->bodies[bi].is_static) { static_count++; continue; }
                f32 s = vec3_len(physics->bodies[bi].velocity);
                if (s > max_speed) { max_speed = s; fastest_id = bi; }
                if (s > speed_record) speed_record = s;
                f32 a = vec3_len(physics->bodies[bi].acceleration);
                if (a > max_accel) max_accel = a;
                if (physics->bodies[bi].velocity.e[1] > max_vy_up) max_vy_up = physics->bodies[bi].velocity.e[1];
                if (physics->bodies[bi].velocity.e[1] < max_vy_down) max_vy_down = physics->bodies[bi].velocity.e[1];
                f32 vy = physics->bodies[bi].velocity.e[1];
                if (vy < -5.0f) vy_b[0]++; else if (vy < 0.0f) vy_b[1]++; else if (vy < 5.0f) vy_b[2]++; else vy_b[3]++;
                f32 ke = 0.5f * physics->bodies[bi].mass * s * s;
                total_ke += ke;
                if (ke < 1.0f) kb[0]++; else if (ke < 10.0f) kb[1]++; else if (ke < 50.0f) kb[2]++; else kb[3]++;
                if (0.5f * physics->bodies[bi].mass * s * s > max_ke) { max_ke = 0.5f * physics->bodies[bi].mass * s * s; max_ke_id = bi; }
                f32 pe_body = physics->bodies[bi].mass * 9.81f * physics->bodies[bi].position.e[1];
                total_pe += pe_body;
                if (pe_body < 0.0f) pb[0]++; else if (pe_body < 10.0f) pb[1]++; else if (pe_body < 100.0f) pb[2]++; else pb[3]++;
                total_mass += physics->bodies[bi].mass;
                if (s > 0.1f) { speed_sum += s; moving++; vel_sum = vec3_add(vel_sum, physics->bodies[bi].velocity); }
                mass_speed_sum += physics->bodies[bi].mass * s;
                speed_sq_sum += s * s;
                vx2 += physics->bodies[bi].velocity.e[0] * physics->bodies[bi].velocity.e[0];
                vy2 += physics->bodies[bi].velocity.e[1] * physics->bodies[bi].velocity.e[1];
                vz2 += physics->bodies[bi].velocity.e[2] * physics->bodies[bi].velocity.e[2];
                if (physics->bodies[bi].velocity.e[1] < -1.0f) falling_count++;
                dyn_count++;
                age_sum += (f32)(engine.frame_count - physics->bodies[bi].spawn_frame) * engine.delta_time;
                f32 age_s = (f32)(engine.frame_count - physics->bodies[bi].spawn_frame) * engine.delta_time;
                if (age_s < 5.0f) age_young++; else if (age_s < 20.0f) age_mid++; else if (age_s < 60.0f) age_old++; else age_ancient++;
                if (physics->bodies[bi].position.e[1] < min_y) min_y = physics->bodies[bi].position.e[1];
                if (physics->bodies[bi].position.e[1] > max_y) max_y = physics->bodies[bi].position.e[1];
                if (s < 1.0f) sb[0]++; else if (s < 5.0f) sb[1]++; else if (s < 15.0f) sb[2]++; else sb[3]++;
                f32 cd = vec3_len(vec3_sub(physics->bodies[bi].position, camera.position));
                if (cd > farthest_dist) { farthest_dist = cd; farthest_id = bi; }
                if (cd < nearest_dist) { nearest_dist = cd; nearest_id = bi; }
                Vec3 to_body = vec3_sub(physics->bodies[bi].position, camera.position);
                if (vec3_dot(to_body, cam_fwd) > 0.0f) in_front++;
                f32 agl = physics->bodies[bi].position.e[1] - terrain_get_height(&terrain, physics->bodies[bi].position.e[0], physics->bodies[bi].position.e[2]);
                if (agl < min_agl) { min_agl = agl; min_agl_id = bi; }
                avg_agl += agl;
                agl_count++;
                if (agl < 0.5f) grounded_count++;
                if (agl < 1.0f) agl_b[0]++; else if (agl < 5.0f) agl_b[1]++; else if (agl < 15.0f) agl_b[2]++; else agl_b[3]++;
                if (physics->bodies[bi].rest_frames > 60) { resting_count++; rest_ke += 0.5f * physics->bodies[bi].mass * s * s; rest_mass += physics->bodies[bi].mass; }
                f32 disp = vec3_len(vec3_sub(physics->bodies[bi].position, physics->bodies[bi].spawn_pos));
                if (disp > max_displacement) { max_displacement = disp; max_disp_id = bi; }
                avg_displacement += disp;
                if (physics->bodies[bi].collision_count > hottest_cols) { hottest_cols = physics->bodies[bi].collision_count; hottest_body = bi; }
            }
                if (max_speed > 0.1f) debug_ui_text(&ui, "Speed: fastest #%u at %.1f m/s  record: %.1f  max accel: %.1f m/s²  vy: +%.1f/%.1f  vy hist: fast↓%u slow↓%u slow↑%u fast↑%u", fastest_id, max_speed, speed_record, max_accel, max_vy_up, max_vy_down, vy_b[0], vy_b[1], vy_b[2], vy_b[3]);
            if (total_ke > 0.01f || total_pe > 0.01f) {
                f32 pe_ref = total_pe - total_mass * 9.81f * min_y;
                f32 pe_ke = total_ke > 0.1f ? pe_ref / total_ke : 0.0f;
                const char *balance = pe_ke > 3.0f ? "PE-heavy" : pe_ke < 0.33f ? "KE-heavy" : "balanced";
                f32 total_energy = total_ke + pe_ref;
                const char *etrend = fabsf(total_energy - prev_total_energy) < 1.0f ? "→" : total_energy > prev_total_energy ? "↑" : "↓";
                debug_ui_text(&ui, "Energy: KE=%.1f PE=%.1f (ref: %.1f) Total=%.1fJ %s  PE/KE=%.1f [%s]  max KE: #%u (%.1fJ)  avg: %.2f J/body  %s", total_ke, pe_ref, min_y, total_energy, etrend, pe_ke, balance, max_ke_id, max_ke, total_ke / (f32)(physics->count - 1 - static_count), total_ke > prev_total_ke + 0.5f ? "↑" : total_ke < prev_total_ke - 0.5f ? "↓" : "→");
                prev_total_ke = total_ke;
                prev_total_energy = total_energy;
            }
            if (total_mass > 0.01f) debug_ui_text(&ui, "System mass: %.1f kg", total_mass);
            if (moving > 0) {
                debug_ui_text(&ui, "Avg speed: %.1f m/s  mass-wtd: %.1f m/s  v/a: %.1f (%u/%u moving)", speed_sum / (f32)moving, total_mass > 0.01f ? mass_speed_sum / total_mass : 0.0f, max_accel > 0.01f ? (speed_sum / (f32)moving) / max_accel : 0.0f, moving, physics->count - 1);
                Vec3 avg_vel = vec3_scale(vel_sum, 1.0f / (f32)moving);
                f32 bearing = atan2f(avg_vel.e[0], avg_vel.e[2]) * 57.2958f;
                if (bearing < 0) bearing += 360.0f;
                const char *compass = (bearing < 22.5f || bearing >= 337.5f) ? "N" : bearing < 67.5f ? "NE" : bearing < 112.5f ? "E" : bearing < 157.5f ? "SE" : bearing < 202.5f ? "S" : bearing < 247.5f ? "SW" : bearing < 292.5f ? "W" : "NW";
                debug_ui_text(&ui, "Avg direction: %.0f° (%s)", bearing, compass);
            }
            if (physics->count > 2) {
                f32 avg_spd = speed_sum / (f32)(physics->count - 1 - static_count);
                f32 spd_var = speed_sq_sum / (f32)(physics->count - 1 - static_count) - avg_spd * avg_spd;
                debug_ui_text(&ui, "Speed: <1m/s:%u <5:%u <15:%u 15+:%u  σ=%.1f", sb[0], sb[1], sb[2], sb[3], sqrtf(spd_var > 0 ? spd_var : 0));
                debug_ui_text(&ui, "KE: <1J:%u <10:%u <50:%u 50+:%u", kb[0], kb[1], kb[2], kb[3]);
                debug_ui_text(&ui, "PE: <0:%u <10:%u <100:%u 100+:%u", pb[0], pb[1], pb[2], pb[3]);
                const char *dominant = vx2 >= vy2 && vx2 >= vz2 ? "X" : vy2 >= vz2 ? "Y" : "Z";
                debug_ui_text(&ui, "Velocity axis: X=%.0f Y=%.0f Z=%.0f  dominant: %s  flow: (%.2f,%.2f,%.2f)", vx2, vy2, vz2, dominant, vel_sum.e[0], vel_sum.e[1], vel_sum.e[2]);
            }
            if (static_count > 0) debug_ui_text(&ui, "Static: %u  Dynamic: %u  Falling: %u  Grounded: %u  Resting: %u (KE=%.2fJ)", static_count, physics->count - 1 - static_count, falling_count, grounded_count, resting_count, rest_ke);
            if (dyn_count > 0) debug_ui_text(&ui, "Entity age: avg %.1f s  histogram: <5s:%u <20s:%u <60s:%u 60+s:%u  height: [%.1f, %.1f]", age_sum / (f32)dyn_count, age_young, age_mid, age_old, age_ancient, min_y, max_y);
            if (dyn_count > 1) {
                f32 heights[64];
                u32 nh = 0;
                for (u32 bi = 1; bi < physics->count && nh < 64; bi++) {
                    if (!physics->bodies[bi].is_static) heights[nh++] = physics->bodies[bi].position.e[1];
                }
                qsort(heights, nh, sizeof(f32), cmp_f32);
                debug_ui_text(&ui, "Height median: %.1f (p25=%.1f p75=%.1f)", heights[nh/2], heights[nh/4], heights[nh*3/4]);
                f32 hmean = 0.0f;
                for (u32 i = 0; i < nh; i++) hmean += heights[i];
                hmean /= (f32)nh;
                f32 hvar = 0.0f;
                for (u32 i = 0; i < nh; i++) { f32 d = heights[i] - hmean; hvar += d * d; }
                f32 hstd = sqrtf(hvar / (f32)nh);
                u32 outliers = 0;
                for (u32 i = 0; i < nh; i++) if (fabsf(heights[i] - hmean) > 2.0f * hstd) outliers++;
                if (outliers > 0) debug_ui_text(&ui, "Height outliers: %u (z>2, std=%.1f)", outliers, hstd);
                f32 speeds[64];
                u32 ns = 0;
                for (u32 bi = 1; bi < physics->count && ns < 64; bi++) {
                    if (!physics->bodies[bi].is_static) speeds[ns++] = vec3_len(physics->bodies[bi].velocity);
                }
                qsort(speeds, ns, sizeof(f32), cmp_f32);
                if (ns > 1) {
                    f32 s_mean = 0.0f;
                    for (u32 si = 0; si < ns; si++) s_mean += speeds[si];
                    s_mean /= (f32)ns;
                    f32 s_var = 0.0f;
                    for (u32 si = 0; si < ns; si++) { f32 d = speeds[si] - s_mean; s_var += d * d; }
                    f32 s_std = sqrtf(s_var / (f32)ns);
                    f32 cv = s_mean > 0.01f ? s_std / s_mean : 0.0f;
                    debug_ui_text(&ui, "Speed p50=%.1f p90=%.1f p99=%.1f m/s  spread=%.1f  CV=%.2f", speeds[ns/2], speeds[ns*9/10], speeds[ns-1], speeds[ns-1] - speeds[0], cv);
                }
            }
            if (farthest_dist > 1.0f) {
                debug_ui_text(&ui, "Nearest: #%u at %.1f m  Farthest: #%u at %.1f m  In front: %u  fwd density: %.2f/m", nearest_id, nearest_dist, farthest_id, farthest_dist, in_front, farthest_dist > 1.0f ? (f32)in_front / farthest_dist : 0.0f);
                if (nearest_dist < 1e8f) {
                    Vec3 tn = vec3_sub(physics->bodies[nearest_id].position, camera.position);
                    f32 nb = atan2f(tn.e[0], tn.e[2]) * 57.2958f;
                    if (nb < 0) nb += 360.0f;
                    const char *nc = (nb < 22.5f || nb >= 337.5f) ? "N" : nb < 67.5f ? "NE" : nb < 112.5f ? "E" : nb < 157.5f ? "SE" : nb < 202.5f ? "S" : nb < 247.5f ? "SW" : nb < 292.5f ? "W" : "NW";
                    debug_ui_text(&ui, "Nearest bearing: %.0f° (%s)", nb, nc);
                }
            }
            if (min_agl < 1e8f) debug_ui_text(&ui, "Lowest AGL: #%u at %.2f m  avg AGL: %.1f", min_agl_id, min_agl, agl_count > 0 ? avg_agl / (f32)agl_count : 0.0f);
            if (max_displacement > 0.5f) debug_ui_text(&ui, "Displacement: max #%u at %.1f m  avg %.1f m from spawn", max_disp_id, max_displacement, dyn_count > 0 ? avg_displacement / (f32)dyn_count : 0.0f);
            if (hottest_cols > 0) debug_ui_text(&ui, "Collision hot body: #%u (%u collisions  %.1f/s)", hottest_body, hottest_cols, hottest_cols / total_time);
            if (physics->hot_pair_count > 2) debug_ui_text(&ui, "Hot pair: #%u-#%u (%u combined)", physics->hot_pair_a, physics->hot_pair_b, physics->hot_pair_count);
            if (physics->count > 2) {
                u32 cluster_id[64];
                u32 nclusters = 0;
                for (u32 i = 0; i < 64; i++) cluster_id[i] = i;
                for (u32 ai = 1; ai < physics->count && ai < 64; ai++) {
                    for (u32 bi2 = ai + 1; bi2 < physics->count && bi2 < 64; bi2++) {
                        Vec3 dv = vec3_sub(physics->bodies[ai].position, physics->bodies[bi2].position);
                        f32 d2 = dv.e[0]*dv.e[0] + dv.e[1]*dv.e[1] + dv.e[2]*dv.e[2];
                        if (d2 < 25.0f) {
                            u32 ca = cluster_id[ai], cb = cluster_id[bi2];
                            while (cluster_id[ca] != ca) ca = cluster_id[ca];
                            while (cluster_id[cb] != cb) cb = cluster_id[cb];
                            if (ca != cb) cluster_id[ca > cb ? ca : cb] = ca < cb ? ca : cb;
                        }
                    }
                }
                for (u32 i = 1; i < physics->count && i < 64; i++) {
                    u32 root = i;
                    while (cluster_id[root] != root) root = cluster_id[root];
                    if (root == i) nclusters++;
                }
                if (nclusters > 0) debug_ui_text(&ui, "Entity clusters: %u (5m radius)", nclusters);
            }
            if (physics->count > 1) {
                Vec3 bmin = physics->bodies[1].position, bmax = physics->bodies[1].position;
                for (u32 bi = 2; bi < physics->count; bi++) {
                    if (physics->bodies[bi].position.e[0] < bmin.e[0]) bmin.e[0] = physics->bodies[bi].position.e[0];
                    if (physics->bodies[bi].position.e[1] < bmin.e[1]) bmin.e[1] = physics->bodies[bi].position.e[1];
                    if (physics->bodies[bi].position.e[2] < bmin.e[2]) bmin.e[2] = physics->bodies[bi].position.e[2];
                    if (physics->bodies[bi].position.e[0] > bmax.e[0]) bmax.e[0] = physics->bodies[bi].position.e[0];
                    if (physics->bodies[bi].position.e[1] > bmax.e[1]) bmax.e[1] = physics->bodies[bi].position.e[1];
                    if (physics->bodies[bi].position.e[2] > bmax.e[2]) bmax.e[2] = physics->bodies[bi].position.e[2];
                }
                f32 span = vec3_len(vec3_sub(bmax, bmin));
                Vec3 bsz = vec3_sub(bmax, bmin);
                f32 vol = bsz.e[0] * bsz.e[1] * bsz.e[2];
                f32 density = vol > 1.0f ? (f32)(physics->count - 1) / vol : 0.0f;
                debug_ui_text(&ui, "Bodies span: %.1f  density: %.4f/m³  bounds: (%.0f,%.0f,%.0f)-(%.0f,%.0f,%.0f)", span, density, bmin.e[0], bmin.e[1], bmin.e[2], bmax.e[0], bmax.e[1], bmax.e[2]);
            }
            if (physics->count > 2) {
                f32 closest_dist = 1e9f;
                u32 ca = 0, cb = 0;
                f32 nn_sum = 0.0f;
                u32 nn_count = 0;
                for (u32 ai = 1; ai < physics->count; ai++) {
                    f32 nn_min = 1e9f;
                    for (u32 bi2 = 1; bi2 < physics->count; bi2++) {
                        if (bi2 == ai) continue;
                        f32 d = vec3_len(vec3_sub(physics->bodies[ai].position, physics->bodies[bi2].position));
                        if (d < closest_dist) { closest_dist = d; ca = ai; cb = bi2; }
                        if (d < nn_min) nn_min = d;
                    }
                    if (!physics->bodies[ai].is_static && nn_min < 1e8f) { nn_sum += nn_min; nn_count++; }
                }
                if (closest_dist < 1e8f) {
                    f32 rel_v = vec3_len(vec3_sub(physics->bodies[ca].velocity, physics->bodies[cb].velocity));
                    Vec3 mid = vec3_scale(vec3_add(physics->bodies[ca].position, physics->bodies[cb].position), 0.5f);
                    f32 mid_h = terrain_get_height(&terrain, mid.e[0], mid.e[2]);
                    debug_ui_text(&ui, "Closest pair: %u-%u dist=%.1f  rel.v=%.1f m/s  terrain=%.1f  avg NN: %.1f m", ca, cb, closest_dist, rel_v, mid_h, nn_count > 0 ? nn_sum / (f32)nn_count : 0.0f);
                }
            }
            if (physics->count > 1) {
                f32 tmass = 0.0f;
                Vec3 com = vec3(0,0,0);
                for (u32 bi = 0; bi < physics->count; bi++) {
                    f32 m = physics->bodies[bi].mass;
                    com.e[0] += physics->bodies[bi].position.e[0] * m;
                    com.e[1] += physics->bodies[bi].position.e[1] * m;
                    com.e[2] += physics->bodies[bi].position.e[2] * m;
                    tmass += m;
                }
                if (tmass > 0.0f) {
                    com = vec3_scale(com, 1.0f / tmass);
                    debug_ui_text(&ui, "Center of mass: (%.1f,%.1f,%.1f)", com.e[0], com.e[1], com.e[2]);
                }
                Vec3 momentum = vec3(0,0,0);
                Vec3 ang_mom = vec3(0,0,0);
                for (u32 bi = 0; bi < physics->count; bi++) {
                    if (physics->bodies[bi].is_static) continue;
                    Vec3 p = vec3_scale(physics->bodies[bi].velocity, physics->bodies[bi].mass);
                    momentum.e[0] += p.e[0];
                    momentum.e[1] += p.e[1];
                    momentum.e[2] += p.e[2];
                    Vec3 r = physics->bodies[bi].position;
                    Vec3 rxp = vec3_cross(r, p);
                    ang_mom.e[0] += rxp.e[0];
                    ang_mom.e[1] += rxp.e[1];
                    ang_mom.e[2] += rxp.e[2];
                }
            f32 mom_mag = vec3_len(momentum);
            static f32 mom_record = 0.0f;
            static f32 prev_mom_mag = 0.0f;
            static Vec3 prev_momentum = {{0,0,0}};
            if (mom_mag > mom_record) mom_record = mom_mag;
            if (mom_mag > 0.01f) {
                f32 mb = atan2f(momentum.e[0], momentum.e[2]) * 57.2958f;
                if (mb < 0) mb += 360.0f;
                const char *mc = (mb < 22.5f || mb >= 337.5f) ? "N" : mb < 67.5f ? "NE" : mb < 112.5f ? "E" : mb < 157.5f ? "SE" : mb < 202.5f ? "S" : mb < 247.5f ? "SW" : mb < 292.5f ? "W" : "NW";
                f32 mom_drift = fabsf(mom_mag - prev_mom_mag);
                f32 mom_dot = mom_mag > 0.01f && prev_mom_mag > 0.01f ? vec3_dot(momentum, prev_momentum) / (mom_mag * prev_mom_mag) : 0.0f;
                if (mom_dot > 1.0f) { mom_dot = 1.0f; }
                if (mom_dot < -1.0f) { mom_dot = -1.0f; }
                debug_ui_text(&ui, "Momentum: (%.1f,%.1f,%.1f) |p|=%.1f  record: %.1f  drift: %.2f/s  persist: %.2f  dir: %.0f° (%s)", momentum.e[0], momentum.e[1], momentum.e[2], mom_mag, mom_record, mom_drift / engine.delta_time, mom_dot, mb, mc);
                prev_mom_mag = mom_mag;
                prev_momentum = momentum;
            }
            f32 ang = vec3_len(ang_mom);
            if (ang > 0.1f) debug_ui_text(&ui, "Angular momentum: (%.1f,%.1f,%.1f) |L|=%.1f", ang_mom.e[0], ang_mom.e[1], ang_mom.e[2], ang);
            }
            if (collision_peak > 0) {
                f32 energy_per_col = physics->collision_count > 0 ? physics->total_impulse_applied / (f32)physics->collision_count * (total_mass > 0.01f ? mass_speed_sum / total_mass : 1.0f) * 0.5f : 0.0f;
                debug_ui_text(&ui, "Collision peak: %u (total: %u  rate: %.1f/s  ~%.1fJ/col  avg impact v: %.1f m/s)%s", collision_peak, physics->collision_count, physics->collision_count / total_time, energy_per_col, physics->collision_count > 0 ? sqrtf(physics->total_collision_speed / (f32)physics->collision_count) : 0.0f, collision_flash > 0.0f ? "  !" : "");
            }
            if (collision_flash > 0.0f) {
                f32 cdist = vec3_len(vec3_sub(last_collision_pos, camera.position));
                debug_ui_text(&ui, "Last collision: (%.1f,%.1f,%.1f) %u frames ago  dist=%.1f", last_collision_pos.e[0], last_collision_pos.e[1], last_collision_pos.e[2], engine.frame_count - last_collision_frame, cdist);
            }
            if (physics->collision_center_count > 0) {
                f32 cc_inv = 1.0f / (f32)physics->collision_center_count;
                debug_ui_text(&ui, "Collision center: (%.1f,%.1f,%.1f) from %u collisions", physics->collision_center.e[0] * cc_inv, physics->collision_center.e[1] * cc_inv, physics->collision_center.e[2] * cc_inv, physics->collision_center_count);
            }
            if (physics->respawn_count > 0) {
                f32 imp_per_col = physics->collision_count > 0 ? physics->total_impulse_applied / (f32)physics->collision_count : 0.0f;
                static f32 prev_ipc = 0.0f;
                const char *ipc_trend = fabsf(imp_per_col - prev_ipc) < 0.05f ? "→" : imp_per_col > prev_ipc ? "↑" : "↓";
                debug_ui_text(&ui, "Respawns: %u  Impulse: %.0f Ns (avg %.1f/col %s  %.1f Ns/s)", physics->respawn_count, physics->total_impulse_applied, imp_per_col, ipc_trend, physics->total_impulse_applied / total_time);
                prev_ipc = imp_per_col;
            }
            debug_ui_text(&ui, "Mem: ~%zu KB (entities %zu + physics %zu)",
                (world->entity_count * (sizeof(CTransform)+sizeof(CMeshRef)+sizeof(CRigidBody)) + physics->count * sizeof(RigidBody)) / 1024,
                world->entity_count * (sizeof(CTransform)+sizeof(CMeshRef)+sizeof(CRigidBody)),
                physics->count * sizeof(RigidBody));
                f32 spawn_rate = total_time > 1.0f ? (f32)(physics->count - 1) / total_time : 0.0f;
                f32 time_to_cap = spawn_rate > 0.01f ? ((f32)physics->capacity - (f32)physics->count) / spawn_rate : -1.0f;
                if (time_to_cap > 0.0f && time_to_cap < 3600.0f) {
                    debug_ui_text(&ui, "Session: frame %u  uptime %.0fs  spawn: %.2f/s  cap %u in %.0fs", (u32)engine.frame_count, total_time, spawn_rate, physics->capacity, time_to_cap);
                } else {
                    debug_ui_text(&ui, "Session: frame %u  uptime %.0fs  spawn: %.2f/s", (u32)engine.frame_count, total_time, spawn_rate);
                }
            if (physics->count > 1) {
                u32 dyn = physics->count - 1 - static_count;
                if (dyn > 0) {
                    debug_ui_text(&ui, "Activity: %u moving / %u resting / %u falling / %u grounded (%u total)  rest mass: %.0f/%.0f (%.0f%%)", moving, resting_count, falling_count, grounded_count, dyn, rest_mass, total_mass, total_mass > 0.01f ? rest_mass / total_mass * 100.0f : 0.0f);
                    debug_ui_text(&ui, "AGL: <1m:%u <5m:%u <15m:%u 15m+:%u", agl_b[0], agl_b[1], agl_b[2], agl_b[3]);
                }
                if (frame_com_mass > 0.01f && total_time > 1.0f) {
                        f32 com_depth = water.water_y - frame_com.e[1];
                        debug_ui_text(&ui, "CoM: (%.1f,%.1f,%.1f) drift: %.1f m (%.2f m/s)%s", frame_com.e[0], frame_com.e[1], frame_com.e[2], com_drift, com_drift / total_time, com_depth > 0 ? " [UNDERWATER]" : "");
                    }
            }
            } /* end physics debug stats throttle */
        }
        if (debug_viz_mode > 0) {
            const char *viz_names[] = { "off", "depth", "normals", "AO", "cascades" };
            debug_ui_text(&ui, "Debug viz: %s", viz_names[debug_viz_mode]);
        }
        if (inspector_mode > 0) {
            static const char *insp_names[] = {
                "off", "scene_color", "scene_depth", "ssao_raw", "ssao_blur",
                "taa_out", "fxaa_out", "dof_out", "bloom", "godrays", "sharpen_out"
            };
            debug_ui_text(&ui, "Inspector (F3): %s", insp_names[inspector_mode]);
        }
        {
            const char *tm_names[] = { "ACES", "AgX", "Khronos" };
            debug_ui_text(&ui, "Tonemap: %s | Exp: %.1f%s", tm_names[tonemap.mode],
                          tonemap.exposure, tonemap.auto_exposure ? " (auto)" : "");
            debug_ui_text(&ui, "Color%s: sat %.2f con %.2f tmp %.2f tnt %.2f  ShadowBias: %.4f",
                cg_enabled ? "" : " OFF", cg_saturation, cg_contrast, cg_temperature, cg_tint, shadow_bias);
            {
                const char *qp_names[] = { "low", "med", "high" };
                debug_ui_text(&ui, "AA: %s%s  FXAA: %s (%.4f)", taa_enabled ? "TAA " : "", fxaa_enabled ? "FXAA" : "", qp_names[fxaa_preset], fxaa_sys.threshold);
            }
            debug_ui_text(&ui, "Bloom: %.1f", postfx.bloom_strength);
            debug_ui_text(&ui, "SSAO: radius %.1f", ssao.radius);
            debug_ui_text(&ui, "God rays: %.2f", god_rays_intensity);
            debug_ui_text(&ui, "TAA: %s", taa_enabled ? "on" : "off");
            debug_ui_text(&ui, "Motion blur: %s", mb_enabled ? "on" : "off");
            debug_ui_text(&ui, "DOF:%s SSR:%s SSGI:%s",
                dof_enabled ? "on" : "off", ssr_enabled ? "on" : "off", ssgi_enabled ? "on" : "off");
            debug_ui_text(&ui, "Vol:%s CS:%s LF:%s SSS:%s Sharp:%s Lens:%s",
                vol_enabled ? "on" : "off", cs_enabled ? "on" : "off",
                lf_enabled ? "on" : "off", sss_enabled ? "on" : "off",
                sharpen_enabled ? "on" : "off", lensfx_enabled ? "on" : "off");
            if (lensfx_enabled) debug_ui_text(&ui, "  CA:%.3f Vig:%.2f", lens_ca, lens_vignette);
            {
                const char *pnames[] = { "full", "balanced", "performance", "minimal" };
            debug_ui_text(&ui, "Preset: %s (Home)", pnames[effect_preset]);
                }
            if (terrain_follow) debug_ui_text(&ui, "Terrain follow: ON (eye=ground+1.7m)");
            if (third_person) debug_ui_text(&ui, "Camera: third-person (dist=%.1f)", third_person_dist);
            { f32 cagl = camera.position.e[1] - cam_terrain_h;
              /* Throttle 4× terrain gradient lookups to every 10 frames (debug UI only). */
              static f32 cached_cslope = 0.0f, cached_chdx = 0.0f, cached_chdz = 0.0f;
              static u32 slope_frame = 0;
              if (engine.frame_count - slope_frame >= 10 || slope_frame == 0) {
                  slope_frame = (u32)engine.frame_count;
                  cached_chdx = terrain_get_height(&terrain, camera.position.e[0] + 0.5f, camera.position.e[2]) - terrain_get_height(&terrain, camera.position.e[0] - 0.5f, camera.position.e[2]);
                  cached_chdz = terrain_get_height(&terrain, camera.position.e[0], camera.position.e[2] + 0.5f) - terrain_get_height(&terrain, camera.position.e[0], camera.position.e[2] - 0.5f);
                  { f32 d2 = cached_chdx*cached_chdx + cached_chdz*cached_chdz; cached_cslope = d2 > 1e-12f ? d2 * fast_rsqrt(d2) : 0.0f; }
              }
              f32 ch = cam_terrain_h;
              const char *biome = ch < terrain_havg - terrain_hstd ? "valley" : ch < terrain_havg + terrain_hstd ? "plains" : ch < terrain_hmax - terrain_hstd ? "hills" : "peak";
              f32 grad_bearing = atan2f(cached_chdx, cached_chdz) * 57.2958f;
              if (grad_bearing < 0) grad_bearing += 360.0f;
              const char *gdir = (grad_bearing < 22.5f || grad_bearing >= 337.5f) ? "N" : grad_bearing < 67.5f ? "NE" : grad_bearing < 112.5f ? "E" : grad_bearing < 157.5f ? "SE" : grad_bearing < 202.5f ? "S" : grad_bearing < 247.5f ? "SW" : grad_bearing < 292.5f ? "W" : "NW";
              debug_ui_text(&ui, "Camera: yaw=%.1f° pitch=%.1f° fov=%.0f°  AGL=%.1f  slope=%.1f° ↓%s  [%s h=%.1f]", camera.yaw * 57.2958f, camera.pitch * 57.2958f, camera.fov, cagl, atanf(cached_cslope) * 57.2958f, gdir, biome, ch);
              { static f32 prev_yaw=0,prev_pitch=0; f32 yr=(camera.yaw-prev_yaw)/engine.delta_time*57.2958f; f32 pr=(camera.pitch-prev_pitch)/engine.delta_time*57.2958f; debug_ui_text(&ui, "Angular v: yaw=%.0f°/s pitch=%.0f°/s", yr, pr); prev_yaw=camera.yaw; prev_pitch=camera.pitch; }
            }
            { debug_ui_text(&ui, "Forward: (%.2f,%.2f,%.2f)  Mouse: (%.0f,%.0f)  Traveled: %.0f m  Speed: %.1f m/s", cam_fwd.e[0], cam_fwd.e[1], cam_fwd.e[2], inp->mouse_x, inp->mouse_y, camera_distance_traveled, engine.delta_time > 0.0001f ? camera_frame_dist / engine.delta_time : 0.0f); }
            { static const char *tn[] = {"Rolling Hills", "Volcano", "Waves", "Ridged", "Craters"}; u32 ttris = (terrain.grid_size - 1) * (terrain.grid_size - 1) * 2; const char *tclass = terrain_hstd < 1.0f ? "flat" : terrain_hstd < 3.0f ? "hilly" : terrain_hstd < 6.0f ? "mountainous" : "extreme"; f32 mod_rate = total_time > 1.0f ? (f32)terrain.modify_count / total_time : 0.0f; f32 mod_eff = terrain.modify_count > 0 ? terrain.total_delta / (f32)terrain.modify_count : 0.0f; debug_ui_text(&ui, "Terrain: %s (%s) %ux%u (%u tris) mods:%u (%.1f/s) delta:%.0f (avg %.1f/mod) h:[%.1f,%.1f] avg=%.1f std=%.2f (%+.3f)  brush=%.0f", tn[terrain_preset], tclass, terrain.grid_size, terrain.grid_size, ttris, terrain.modify_count, mod_rate, terrain.total_delta, mod_eff, terrain_hmin, terrain_hmax, terrain_havg, terrain_hstd, terrain_hstd_delta, brush_radius); }
            if (terrain.modify_count > 0) { u32 mq=0; for(u32 qi=1;qi<4;qi++) if(terrain.edit_quadrant[qi]>terrain.edit_quadrant[mq]) mq=qi; debug_ui_text(&ui, "Edit heatmap: NW:%u NE:%u SW:%u SE:%u  hottest:%s", terrain.edit_quadrant[0],terrain.edit_quadrant[1],terrain.edit_quadrant[2],terrain.edit_quadrant[3], mq==0?"NW":mq==1?"NE":mq==2?"SW":"SE"); }
            if (underwater) debug_ui_text(&ui, "[UNDERWATER] depth: %.1f m", water.water_y - camera.position.e[1]);
            if (water.enabled) debug_ui_text(&ui, "Water: y=%.1f %s coverage: %.1f%%  vol: %.0f m³  depth: avg=%.2f max=%.2f  centroid: (%.1f,%.1f)  shoreline: %u edges", water.water_y, underwater ? "(below)" : "", terrain_water_pct, terrain_water_vol, terrain_water_depth_avg, terrain_water_depth_max, terrain_water_cx, terrain_water_cz, terrain_shoreline);
            if (recording_path) debug_ui_text(&ui, "[REC] Path: %u/%d frames", path_count, MAX_PATH);
            if (playing_path) debug_ui_text(&ui, "[PLAY] Path: %u/%u", path_idx, path_count);
            if (particle_trail) debug_ui_text(&ui, "[TRAIL] Particles follow entity");
            if (anim_blend_ready)
                debug_ui_text(&ui, "AnimBlend: clip %u/%u (F12 crossfade)",
                              anim_blend_clip_idx, scene.anim_clip_count);
            if (anim_ik_ready)
                debug_ui_text(&ui, "AnimIK: chain 0-1-2 (BREAK_ANIM_IK=1)");
            if (netrep_enabled)
                debug_ui_text(&ui, "NetRep: sent=%u recv=%u stale=%u retry=%u reord=%u dup=%u hb=%u/%u echo=%u rtt=%.1f rt=%.1fms last=%u snaps%s",
                              netrep_sent, netrep_recv, netrep_stale, netrep_retries, netrep_reordered,
                              netrep_reord_dup, netrep_hb_sent, netrep_hb_recv, netrep_hb_echo,
                              netrep_hb_rtt_ms, netrep_hb_rt_ms,
                              netrep_last_count,
                              netrep_ghost_valid ? (netrep_apply ? " ghost:on" : " ghost:off") : "");
            if (netrep_enabled && netrep_ghost_valid && netrep_apply) {
                CTransform *gt = world_get_component(world, netrep_ghost, COMP_TRANSFORM);
                if (gt)
                    debug_ui_text(&ui, "  ghost pos=(%.1f, %.1f, %.1f)",
                                  gt->pos[0], gt->pos[1], gt->pos[2]);
            }
            if (netrep_enabled) {
                u32 pc = net_replicator_peer_count(&net_rep);
                if (net_rep.peer_evicted > 0u)
                    debug_ui_text(&ui, "  peers=%u evicted=%u ttl=%ums",
                                  pc, net_rep.peer_evicted, net_rep.peer_evict_ms);
                for (u32 pi = 0; pi < pc && pi < 4u; pi++) {
                    const NetRepPeerStats *ps = net_replicator_peer_at(&net_rep, pi);
                    if (!ps) continue;
                    debug_ui_text(&ui, "  peer %s:%u rtt=%.1f rt=%.1f hb=%u/%u",
                                  ps->addr.host, ps->addr.port,
                                  ps->last_rtt_ms, ps->roundtrip_ms,
                                  ps->hb_recv, ps->hb_rt_recv);
                }
            }
            debug_ui_text(&ui, "Particles: %.0f/s alive %u/%u%s",
                          particles.emit_rate,
                          particles.last_alive_count, PARTICLES_MAX,
                          particles.cull_ready ? " GPUcull" : "");
            if (tornado_mode) debug_ui_text(&ui, "[TORNADO] Tangential force active");
            if (gravity_well) debug_ui_text(&ui, "[GRAVITY WELL] Attracting to camera (F5 toggle)");
            if (slow_motion) debug_ui_text(&ui, "[SLOW-MO] Physics 0.25x");
            if (physics_mode == 3) debug_ui_text(&ui, "Gravity: (%.1f,%.1f,%.1f) (arrows/PgUp/PgDn)", custom_gravity.e[0], custom_gravity.e[1], custom_gravity.e[2]);
            if (brush_mode == 1) debug_ui_text(&ui, "[FLATTEN] Brush mode: smooth");
            if (brush_mode == 2) debug_ui_text(&ui, "[ERODE] Brush mode: thermal erosion");
            if (brush_mode == 3) debug_ui_text(&ui, "[NOISE] Brush mode: noise stamp");
            if (cam_height_lock) debug_ui_text(&ui, "[LOCK-Y] Camera height: %.1f", cam_locked_y);
            if (selected_entity_count > 0) {
                debug_ui_text(&ui, "Selected: %u/%u (Tab cycle)", selected_entity_idx, selected_entity_count);
                Entity se = world->entities[selected_entity_id];
                CTransform *st = world_get_component(world, se, COMP_TRANSFORM);
                CMeshRef *sm_comp = world_get_component(world, se, COMP_MESH_REF);
                CRigidBody *sr = world_get_component(world, se, COMP_RIGID_BODY);
                debug_ui_text(&ui, "  comps: %s%s%s", st ? "[Transform]" : "", sm_comp ? "[Mesh]" : "", sr ? "[Physics]" : "");
                if (st) {
                    debug_ui_text(&ui, "  pos=(%.1f, %.1f, %.1f)", st->pos[0], st->pos[1], st->pos[2]);
                    /* Throttle entity terrain lookups (5× terrain_get_height) to every 10 frames. */
                    static f32 eth = 0.0f, eslope = 0.0f;
                    static u32 eth_frame = 0;
                    if (engine.frame_count - eth_frame >= 10 || eth_frame == 0) {
                        eth_frame = (u32)engine.frame_count;
                        eth = terrain_get_height(&terrain, st->pos[0], st->pos[2]);
                        f32 sdx = terrain_get_height(&terrain, st->pos[0] + 0.5f, st->pos[2]) - terrain_get_height(&terrain, st->pos[0] - 0.5f, st->pos[2]);
                        f32 sdz = terrain_get_height(&terrain, st->pos[0], st->pos[2] + 0.5f) - terrain_get_height(&terrain, st->pos[0], st->pos[2] - 0.5f);
                        { f32 d2 = sdx * sdx + sdz * sdz; eslope = d2 > 1e-12f ? d2 * fast_rsqrt(d2) : 0.0f; }
                    }
                    debug_ui_text(&ui, "  ground=%.2f  agl=%.2f", eth, st->pos[1] - eth);
                    debug_ui_text(&ui, "  slope=%.2f (%.1f°)", eslope, atanf(eslope) * 57.2958f);
                    Vec3 delta = vec3_sub(vec3(st->pos[0],st->pos[1],st->pos[2]), prev_entity_pos);
                    f32 dx = vec3_len(delta);
                    if (dx > 0.01f) debug_ui_text(&ui, "  delta=(%.2f,%.2f,%.2f)", delta.e[0], delta.e[1], delta.e[2]);
                    prev_entity_pos = vec3(st->pos[0], st->pos[1], st->pos[2]);
                    Vec3 diff = vec3_sub(camera.position, vec3(st->pos[0], st->pos[1], st->pos[2]));
                    f32 dist = vec3_len(diff);
                    debug_ui_text(&ui, "  dist=%.1f", dist);
                }
                if (sr && sr->physics_id > 0 && sr->physics_id < physics->count) {
                    Vec3 v = physics->bodies[sr->physics_id].velocity;
                    f32 spd = vec3_len(v);
                    debug_ui_text(&ui, "  vel=(%.1f, %.1f, %.1f) speed=%.1f  KE=%.1fJ", v.e[0], v.e[1], v.e[2], spd, 0.5f * physics->bodies[sr->physics_id].mass * spd * spd);
                    if (spd > 0.1f) {
                        char arrow = '>';
                        f32 ax = fabsf(v.e[0]), az = fabsf(v.e[2]);
                        if (az > ax) arrow = v.e[2] > 0 ? 'v' : '^';
                        else arrow = v.e[0] > 0 ? '>' : '<';
                        if (fabsf(v.e[1]) > ax && fabsf(v.e[1]) > az) arrow = v.e[1] > 0 ? 'U' : 'D';
                        debug_ui_text(&ui, "  dir=[%c] hat=(%.2f,%.2f,%.2f)", arrow, v.e[0]/spd, v.e[1]/spd, v.e[2]/spd);
                        debug_ui_text(&ui, "  pred=(%.1f,%.1f,%.1f) in 1s", st->pos[0]+v.e[0], st->pos[1]+v.e[1], st->pos[2]+v.e[2]);
                    }
                    RigidBody *pb = &physics->bodies[sr->physics_id];
                    debug_ui_text(&ui, "  size=(%.1f,%.1f,%.1f) r=%.2f mass=%.1f rest=%.1f%s", pb->half_extent.e[0], pb->half_extent.e[1], pb->half_extent.e[2], vec3_len(pb->half_extent), pb->mass, pb->restitution, pb->is_static ? " [STATIC]" : "");
                }
            }
        }

        const ProfilerFrame *pf = profiler_last_frame();
        if (pf) {
            debug_ui_text(&ui, "--- Profiler ---");
            debug_ui_text(&ui, "Frame: %.2f ms", (f64)(pf->frame_end_us - pf->frame_start_us) / 1000.0);
            for (u32 ri = 0; ri < pf->region_count; ri++) {
                debug_ui_text(&ui, "  %s: %.2f ms", pf->regions[ri].name, (f64)pf->regions[ri].elapsed_us / 1000.0);
            }
            f64 gpu_shadow = rhi_gpu_timer_elapsed_ms(gpu_shadow_timer);
            f64 gpu_forward = rhi_gpu_timer_elapsed_ms(gpu_forward_timer);
            f64 gpu_scene = rhi_gpu_timer_elapsed_ms(gpu_scene_timer);
            f64 gpu_postfx = rhi_gpu_timer_elapsed_ms(gpu_postfx_timer);
            debug_ui_text(&ui, "--- GPU ---");
            debug_ui_text(&ui, "  shadow: %.2f ms", gpu_shadow);
            debug_ui_text(&ui, "  forward: %.2f ms", gpu_forward);
            debug_ui_text(&ui, "  scene: %.2f ms", gpu_scene);
            debug_ui_text(&ui, "  postfx: %.2f ms", gpu_postfx);
            debug_ui_text(&ui, "  total: %.2f ms", gpu_scene + gpu_postfx);
            if (occ_cull_enabled && occ_sys.enabled) {
                debug_ui_text(&ui, "--- Occlusion ---");
                debug_ui_text(&ui, "  vis=%u/%u frame_culled=%u",
                              occlusion_cull_visible_count(&occ_sys),
                              occ_sys.object_count, culled_count);
            }
            if (unified_cull_enabled && gpucull_sys.unified_ready) {
                const char *tag = "";
                if (unified_forward_enabled && unified_deferred_enabled) tag = "+fwd+def";
                else if (unified_forward_enabled) tag = "+forward";
                else if (unified_deferred_enabled) tag = "+deferred";
                if (unified_shadow_enabled) {
                    if (tag[0]) debug_ui_text(&ui, "UnifiedCull: on (1-pass%s +shadow-mat)", tag);
                    else debug_ui_text(&ui, "UnifiedCull: on (1-pass +shadow-mat)");
                } else {
                    debug_ui_text(&ui, "UnifiedCull: on (1-pass cull+compact%s)", tag);
                }
            }
            if (draw_bench_enabled && mega_buf.valid) {
                f32 ratio = draw_bench_mega > 0u ?
                    (f32)draw_bench_legacy_est / (f32)draw_bench_mega : 0.0f;
                f64 avg_u = draw_bench_gpu_uni_frames > 0u ?
                    draw_bench_gpu_uni_sum / (f64)draw_bench_gpu_uni_frames : 0.0;
                f64 avg_l = draw_bench_gpu_leg_frames > 0u ?
                    draw_bench_gpu_leg_sum / (f64)draw_bench_gpu_leg_frames : 0.0;
                debug_ui_text(&ui, "DrawBench: mega=%u legacy~%u ratio=%.1fx gpu_u=%.2fms(%u) gpu_l=%.2fms(%u)",
                              draw_bench_mega, draw_bench_legacy_est, ratio,
                              avg_u, draw_bench_gpu_uni_frames,
                              avg_l, draw_bench_gpu_leg_frames);
            }
            if (forward_vel_enabled && forward_vel.ready)
                debug_ui_text(&ui, "ForwardVel: on (BREAK_FORWARD_VEL=1)");
            if (combined_aa.use_combined || combined_color.use_combined) {
                debug_ui_text(&ui, "--- CombinedPost ---");
                debug_ui_text(&ui, "  TAA+FXAA=%s Tonemap+CG=%s",
                              combined_aa.use_combined ? "on" : "off",
                              combined_color.use_combined ? "on" : "off");
            }
            if (mip_stream_idx >= 0) {
                debug_ui_text(&ui, "--- MipStream ---");
                debug_ui_text(&ui,
                    "  level=%u resident=%zuKB loads=%u uploads=%u evict=%u",
                    mipmap_stream_resident_level(&mip_stream, mip_stream_idx),
                    mipmap_stream_resident_bytes(&mip_stream) / 1024,
                    mipmap_stream_load_requests(&mip_stream),
                    mipmap_stream_uploads(&mip_stream),
                    mipmap_stream_evictions(&mip_stream));
            }
            if (audio_stream_id >= 0) {
                f32 atten = audio_stream_attenuation(&audio_stream_mgr,
                                                     audio_stream_id, camera.position);
                debug_ui_text(&ui, "--- AudioStream ---");
                debug_ui_text(&ui, "  3D tone gain=%.2f t=%.1fs",
                              atten,
                              audio_stream_cursor_seconds(&audio_stream_mgr, audio_stream_id));
            }
            {
                static f64 ft_hist[60];
                static i32 ft_idx;
                const ProfilerFrame *pf2 = profiler_last_frame();
                if (pf2) {
                    f64 ft = (f64)(pf2->frame_end_us - pf2->frame_start_us) / 1000.0;
                    ft_hist[ft_idx % 60] = ft;
                    ft_idx++;
                }
                if (ft_idx > 0) {
                    f64 max_ms = 33.33;
                    for (i32 hi = 0; hi < (ft_idx < 60 ? ft_idx : 60); hi++)
                        if (ft_hist[hi] > max_ms) max_ms = ft_hist[hi];
                    char line[64];
                    for (i32 row = 0; row < 4; row++) {
                        f64 thresh_lo = max_ms * (f64)(3 - row) / 4.0;
                        f64 thresh_hi = max_ms * (f64)(4 - row) / 4.0;
                        line[0] = '|';
                        i32 count = ft_idx < 60 ? ft_idx : 60;
                        for (i32 ci = 0; ci < count && ci < 42; ci++) {
                            i32 si = (ft_idx - count + ci) % 60;
                            f64 v = ft_hist[si];
                            if (v >= thresh_hi) line[ci + 1] = '#';
                            else if (v >= thresh_lo) line[ci + 1] = '=';
                            else line[ci + 1] = ' ';
                        }
                        line[count < 42 ? count + 1 : 43] = '|';
                        line[count < 42 ? count + 2 : 44] = '\0';
                        debug_ui_text(&ui, "%s", line);
                    }
                    debug_ui_text(&ui, "  0ms -------- %5.1fms -------- 33ms", max_ms);
                }
            }
        }

        if (show_help && ui.visible) {
            debug_ui_text(&ui, "=== CONTROLS (U to toggle) ===");
            debug_ui_text(&ui, "F1:DebugViz  F3:Inspector  F:Wireframe  H:AA  V:VSync  T:Filter  G:Fullscreen");
            debug_ui_text(&ui, "L/J/I/K:Sun  O:TimeCycle  Z/X:ShadowBias  .:TimePreset  ;:TerrainPreset");
            debug_ui_text(&ui, "WASD:Move  Mouse:Look  Scroll:FOV  9:Gravity  0:WaterColor  R:Reset  E:Spawn+Push");
            debug_ui_text(&ui, "B:Save  N:Load  C:Background  Home:Presets  End:ResetAll  F12:Screenshot  M:Bench");
            debug_ui_text(&ui, "P:Burst  Y/H:Terrain(3:BrushSize)  K:Layout  /:Fog  \\:FogFar  Q:TerrainFollow  =:WaterOn");
            debug_ui_text(&ui, "Tab:Select  ]:Duplicate  Del:Delete  Arrows:Move  PgUp/PgDn:MoveY  Space:Impulse");
            debug_ui_text(&ui, "[:3rdPerson  ,:CamPath  J:Trail  ':Particles  (:WaterUp  ):WaterDown");
            debug_ui_text(&ui, "1:Explosion  2:Magnet  3:BrushSize  4:Throw  5:Bounce  6:Freeze  7:Scale  8:SlowMo");
            debug_ui_text(&ui, "A:BrushMode(4)  D:Mass  S:Ambient  W:EntityToCam  Backspace:SwapPos  Q:HeightLock  Space:Impulse/StopAll");
        }

        {
            static const char hm[] = " .:oO@#";
            char line[12];
            u32 gs = terrain.grid_size;
            for (u32 mz = 0; mz < 8; mz++) {
                for (u32 mx = 0; mx < 8; mx++) {
                    u32 gx = (mx * (gs - 1)) / 7;
                    u32 gz = (mz * (gs - 1)) / 7;
                    f32 h = terrain.heightmap ? terrain.heightmap[gz * gs + gx] : 0;
                    u32 lvl = (u32)(h / terrain.height_scale * 6.0f);
                    if (lvl > 6) lvl = 6;
                    line[mx] = hm[lvl];
                }
                line[8] = '\0';
                debug_ui_text(&ui, "%s", line);
            }
        }

        } /* end if(ui.visible) */

        /* Accumulate com_drift using the CoM computed before the gate. */
        if (physics->count > 1 && frame_com_mass > 0.01f) {
            com_drift += vec3_len(vec3_sub(frame_com, prev_com));
            prev_com = frame_com;
        }

        debug_ui_end(&ui);

        if (particle_trail && selected_entity_count > 0 && selected_entity_id > 0) {
            CTransform *xt = world_get_component(world, (Entity){selected_entity_id, 0}, COMP_TRANSFORM);
            if (xt) {
                particles.emit_pos[0] = xt->pos[0];
                particles.emit_pos[1] = xt->pos[1];
                particles.emit_pos[2] = xt->pos[2];
            }
        }

        profiler_push("render");
        RHICmdBuffer *cmd = rhi_frame_begin(render.device);

        RHISampler active_sampler = nearest_filter && rhi_handle_valid(render.nearest_sampler) ? render.nearest_sampler : render.sampler;

        /* R86-4: Cache sun_color/ambient_col — only recompute when sun_elevation
         * or ambient_mult changes. Previously recomputed every frame. */
        static f32 cached_sun_t = -1.0f;
        static f32 cached_amb_mult = -1.0f;
        static Vec3 cached_sun_color = {0};
        static Vec3 cached_ambient_col = {0};

        f32 sun_t = fmaxf(0.0f, fminf(sun_elevation / 1.0f, 1.0f));
        if (sun_elevation != cached_sun_el || sun_azimuth != cached_sun_az) {
            cached_sun_el = sun_elevation;
            cached_sun_az = sun_azimuth;
            cached_sun_dir = vec3_normalize(vec3(
                cosf(sun_elevation) * sinf(sun_azimuth),
                -sinf(sun_elevation),
                cosf(sun_elevation) * cosf(sun_azimuth)
            ));
        }
        if (sun_t != cached_sun_t || ambient_mult != cached_amb_mult) {
            cached_sun_t = sun_t;
            cached_amb_mult = ambient_mult;
            cached_sun_color = vec3(
                0.8f + 0.2f * sun_t,
                0.4f + 0.55f * sun_t,
                0.2f + 0.7f * sun_t
            );
            f32 amb_t = fmaxf(0.15f, sun_t * 0.35f);
            cached_ambient_col = vec3(amb_t * 0.9f * ambient_mult, amb_t * 0.9f * ambient_mult, amb_t * ambient_mult);
        }
        Vec3 sun_dir_vec = cached_sun_dir;
        Vec3 sun_color = cached_sun_color;
        Vec3 ambient_col = cached_ambient_col;

        draw_calls = 0;
        culled_count = 0;

        profiler_push("particles+csm");
        particles_compute(&particles, cmd, (f32)engine.delta_time);

        /* CSM: compute cascade VP matrices and render depth passes */
        if (rhi_handle_valid(render.depth_pipeline)) {
            rhi_gpu_timer_begin(gpu_shadow_timer);
            Vec3 light_dir = sun_dir_vec;

            /* Pre-compute shadow lookat basis once for all 4 cascades
             * (eliminates 4× normalize + 8× cross + 4× mat4_identity). */
            f32 s_len2 = light_dir.e[0] * light_dir.e[0] + light_dir.e[2] * light_dir.e[2];
            f32 inv_sl = s_len2 > 1e-12f ? fast_rsqrt(s_len2) : 0.0f;
            /* s = normalize(light_dir × (0,1,0)) = (-fz, 0, fx) / len */
            f32 sx = -light_dir.e[2] * inv_sl;
            f32 sz =  light_dir.e[0] * inv_sl;
            /* u = normalize(cross(s_unnorm, f)) = cross(s_unnorm, f) * inv_sl
             * cross(s_unnorm, f) = (-fy*fx, fx²+fz², -fy*fz).
             * For unit light_dir: u_len2 = s_len2, so inv_ul = inv_sl (no extra rsqrt). */
            f32 fx = light_dir.e[0], fy = light_dir.e[1], fz = light_dir.e[2];
            f32 ux = -fy * fx * inv_sl;
            f32 uy = (fx * fx + fz * fz) * inv_sl;
            f32 uz = -fy * fz * inv_sl;

            /* Bind the 2048x2048 shadow atlas once (clears the whole texture),
             * then render each of the 4 cascades into its own 1024x1024 quadrant
             * via a non-flipped quadrant viewport. This replaces the previous
             * 4 separate shadow maps / passes and lets every shader sample all
             * cascades from a single bound texture. */
            u32 atlas_half = render.shadow_map.width / 2u;
            rhi_cmd_bind_shadow_map(cmd, &render.shadow_map);

            /* R73-1: Pre-pack legacy GPU cull objects — object data is cascade-independent.
             * R82-1: Skip when unified cull is active — object data already uploaded
             * via gpucull_upload_objects_unified at init, legacy pack output never consumed. */
            bool legacy_gpucull_packed = false;
            if (mega_buf.valid && gpu_indirect_enabled &&
                gpucull_enabled && gpucull_sys.ready && !unified_cull_enabled) {
                u32 vc_pre = mega_buf.draw_cmd_count;
                if (vc_pre <= GPUCULL_MAX_OBJECTS) {
                    u32 obj_idx = 0;
                    for (u32 ni = 0; ni < scene.node_count && obj_idx < vc_pre; ni++) {
                        if (mega_buf.node_spheres[ni].r < 0.0f) continue;
                        g_cull_positions[obj_idx*3+0] = mega_buf.node_spheres[ni].cx;
                        g_cull_positions[obj_idx*3+1] = mega_buf.node_spheres[ni].cy;
                        g_cull_positions[obj_idx*3+2] = mega_buf.node_spheres[ni].cz;
                        g_cull_radii[obj_idx] = mega_buf.node_spheres[ni].r;
                        obj_idx++;
                    }
                    gpucull_update_objects(&gpucull_sys, g_cull_positions, g_cull_radii, vc_pre);
                    legacy_gpucull_packed = true;
                }
            }

            for (int c = 0; c < 4; c++) {
                f32 zn = render.cascade_splits[c];
                f32 zf = render.cascade_splits[c + 1];
                f32 mid = (zn + zf) * 0.5f;

                Vec3 center = vec3_add(camera.position, vec3_scale(cam_fwd, mid));

                f32 extent = zf - zn;
                /* Direct view matrix from pre-computed basis (avoids mat4_lookat: 2 normalize + 2 cross + identity).
                 * Left-handed convention matching camera_view: right = -cross(f,up). */
                f32 ex = center.e[0] - light_dir.e[0] * extent;
                f32 ey = center.e[1] - light_dir.e[1] * extent;
                f32 ez = center.e[2] - light_dir.e[2] * extent;
                Mat4 lview;
                lview.e[0][0] = -sx;  lview.e[0][1] = 0.0f; lview.e[0][2] = -sz;  lview.e[0][3] = sx*ex + sz*ez;
                lview.e[1][0] = ux;   lview.e[1][1] = uy;   lview.e[1][2] = uz;   lview.e[1][3] = -(ux*ex + uy*ey + uz*ez);
                lview.e[2][0] = -fx;  lview.e[2][1] = -fy;  lview.e[2][2] = -fz;  lview.e[2][3] = fx*ex + fy*ey + fz*ez;
                lview.e[3][0] = 0.0f; lview.e[3][1] = 0.0f; lview.e[3][2] = 0.0f; lview.e[3][3] = 1.0f;
                Mat4 lproj = mat4_ortho(-extent, extent, -extent, extent, 0.1f, extent * 2.0f);
                render.cascade_vp[c] = mat4_mul_ortho_diag(lproj, lview);

                /* Quadrant layout: cascade c -> (c&1, c>>1). Must match the
                 * atlas remap in the shadow-sampling shaders. */
                u32 qx = (u32)(c & 1) * atlas_half;
                u32 qy = (u32)(c >> 1) * atlas_half;
                rhi_cmd_set_shadow_viewport(cmd, qx, qy, atlas_half, atlas_half);
                rhi_cmd_bind_pipeline(cmd, render.depth_pipeline);

                if (render.depth_loc_model >= 0) rhi_cmd_set_uniform_mat4(cmd, render.depth_loc_model, &frame_identity.e[0][0]);
                if (render.depth_loc_lvp >= 0) rhi_cmd_set_uniform_mat4(cmd, render.depth_loc_lvp, &render.cascade_vp[c].e[0][0]);

                if (rhi_handle_valid(terrain.vbo)) {
                    rhi_cmd_bind_vertex_buffer(cmd, terrain.vbo, 0);
                    rhi_cmd_bind_index_buffer(cmd, terrain.ibo, 0);
                    rhi_cmd_draw_indexed(cmd, terrain.index_count, 1);
                    draw_calls++; tri_count += terrain.index_count / 3;
                }

                if (mega_buf.valid && gpu_indirect_enabled) {
                    /* Indirect draw: batch all scene meshes in one GPU call.
                     * Mega-buffer has pre-baked world transforms so u_model=identity. */
                    rhi_cmd_bind_vertex_buffer(cmd, mega_buf.vbo, 0);
                    rhi_cmd_bind_index_buffer(cmd, mega_buf.ibo, 0);

                    /* Per-cascade culling, then GPU stream-compaction. */
                    u32 vis_count = mega_buf.draw_cmd_count;
                    if (mega_use_unified_shadow(&mega_buf) &&
                        mega_unified_vis_flags(&gpucull_sys, cmd, &render.cascade_vp[c].e[0][0],
                                               vis_count, &occ_sys, g_draw_vis)) {
                        u32 mc = mega_mat_groups_indirect(cmd, render.device,
                                                          &mega_buf, g_draw_vis);
                        draw_calls += mc;
                        draw_bench_add(mc, draw_bench_enabled ? mega_count_visible_draws(&mega_buf, g_draw_vis) : 0u);
                        draw_bench_mark_unified();
                    } else if (gpucull_enabled && mega_unified_cull_draw(&gpucull_sys, render.device, cmd,
                                                  &render.cascade_vp[c].e[0][0], vis_count, &occ_sys)) {
                        draw_calls++;
                        draw_bench_add(1u, draw_bench_enabled ? mega_count_visible_draws(&mega_buf, NULL) : 0u);
                        draw_bench_mark_unified();
                    } else {
                    if (legacy_gpucull_packed) {
                        /* Legacy: flags + compact (two compute passes). Object data pre-packed. */
                        gpucull_dispatch_flags(&gpucull_sys, cmd, &render.cascade_vp[c].e[0][0],
                                               indirect_sys.visibility_buf);
                    } else {
                        /* CPU frustum culling per cascade */
                        Frustum shadow_frustum = frustum_from_vp(&render.cascade_vp[c]);
                        u32 obj_idx = 0;
                        for (u32 ni = 0; ni < scene.node_count && obj_idx < vis_count; ni++) {
                            if (mega_buf.node_spheres[ni].r < 0.0f) continue;
                            Vec3 ctr = {{ mega_buf.node_spheres[ni].cx,
                                          mega_buf.node_spheres[ni].cy,
                                          mega_buf.node_spheres[ni].cz }};
                            g_vis_flags[obj_idx] = frustum_test_sphere(&shadow_frustum, ctr, mega_buf.node_spheres[ni].r) ? 1u : 0u;
                            obj_idx++;
                        }
                        indirect_draw_upload_visibility(&indirect_sys, render.device, g_vis_flags, vis_count);
                    }
                    indirect_draw_compact(&indirect_sys, render.device, cmd);
                    indirect_draw_execute(&indirect_sys, render.device);
                    draw_calls++;
                    draw_bench_add(1u, draw_bench_enabled ? mega_count_visible_draws(&mega_buf, NULL) : 0u);
                    draw_bench_mark_legacy();
                    }
                    tri_count += mega_buf.total_index_count / 3;
                } else {
                for (u32 ni = 0; ni < scene.node_count; ni++) {
                    SceneNode *node = &scene.nodes[ni];
                    if (!node->has_mesh) continue;
                    if (node->mesh_index >= scene.mesh_count) continue;
                    Mesh *m = &scene.meshes[node->mesh_index];
                    if (render.depth_loc_model >= 0) rhi_cmd_set_uniform_mat4(cmd, render.depth_loc_model, &node->world_transform.e[0][0]);
                    rhi_cmd_bind_vertex_buffer(cmd, m->vertex_buf, 0);
                    rhi_cmd_bind_index_buffer(cmd, m->index_buf, 0);
                    rhi_cmd_draw_indexed(cmd, m->index_count, 1);
                    draw_calls++; tri_count += m->index_count / 3;
                }
                }
            }

            rhi_cmd_unbind_shadow_map(cmd, w, h);
            rhi_gpu_timer_end(gpu_shadow_timer);
        }

        /* ---- Point-light cubemap shadow depth pass ----
         * Renders 6 depth faces per active shadow-casting point light.
         * Runs in both forward and deferred paths (deferred uses cubemaps
         * for lighting-pass shadow sampling). */
        {
            /* Build contiguous position/radius arrays from LightSystem. */
            u32 pl_count = lights.point_count;
            if (pl_count > 0u && pt_shadows.ready) {
                static Vec3 pl_pos[LIGHT_MAX_POINT];
                static f32  pl_rad[LIGHT_MAX_POINT];
                for (u32 pi = 0; pi < pl_count; pi++) {
                    pl_pos[pi].e[0] = lights.point_lights[pi].pos[0];
                    pl_pos[pi].e[1] = lights.point_lights[pi].pos[1];
                    pl_pos[pi].e[2] = lights.point_lights[pi].pos[2];
                    pl_rad[pi]      = lights.point_lights[pi].radius;
                }
                point_shadow_update(&pt_shadows, pl_pos, pl_rad, pl_count, camera.position);

                /* Render depth cubemap for each active shadow-casting light. */
                for (u32 pli = 0; pli < pt_shadows.active_count; pli++) {
                    for (u32 pface = 0; pface < POINT_SHADOW_FACES; pface++) {
                        point_shadow_render_begin(&pt_shadows, cmd, pli, pface);

                        /* Render scene geometry into depth cubemap face. */
                        if (rhi_handle_valid(terrain.vbo)) {
                            /* R81-4: u_model=identity already set by point_shadow_render_begin. */
                            rhi_cmd_bind_vertex_buffer(cmd, terrain.vbo, 0);
                            rhi_cmd_bind_index_buffer(cmd, terrain.ibo, 0);
                            rhi_cmd_draw_indexed(cmd, terrain.index_count, 1);
                        }

                        if (mega_buf.valid && gpu_indirect_enabled) {
                            /* Indirect draw: mega-buffer has world-space verts, u_model=identity */
                            rhi_cmd_bind_vertex_buffer(cmd, mega_buf.vbo, 0);
                            rhi_cmd_bind_index_buffer(cmd, mega_buf.ibo, 0);

                            /* Frustum cull from this cubemap face's perspective */
                            u32 vis_count = mega_buf.draw_cmd_count;
                            u32 face_idx = pli * POINT_SHADOW_FACES + pface;
                            if (mega_use_unified_shadow(&mega_buf) &&
                                mega_unified_vis_flags(&gpucull_sys, cmd,
                                                       &pt_shadows.light_vp[face_idx].e[0][0],
                                                       vis_count, &occ_sys, g_draw_vis)) {
                                u32 mc = mega_mat_groups_indirect(cmd, render.device,
                                                                  &mega_buf, g_draw_vis);
                                draw_calls += mc;
                                draw_bench_add(mc, draw_bench_enabled ? mega_count_visible_draws(&mega_buf, g_draw_vis) : 0u);
                                draw_bench_mark_unified();
                            } else if (gpucull_enabled && mega_unified_cull_draw(&gpucull_sys, render.device, cmd,
                                                          &pt_shadows.light_vp[face_idx].e[0][0],
                                                          vis_count, &occ_sys)) {
                                draw_calls++;
                                draw_bench_add(1u, draw_bench_enabled ? mega_count_visible_draws(&mega_buf, NULL) : 0u);
                                draw_bench_mark_unified();
                            } else {
                                Frustum pface_frustum = frustum_from_vp(&pt_shadows.light_vp[face_idx]);
                                u32 obj_idx = 0;
                                for (u32 ni = 0; ni < scene.node_count && obj_idx < vis_count; ni++) {
                                    if (mega_buf.node_spheres[ni].r < 0.0f) continue;
                                    Vec3 ctr = {{ mega_buf.node_spheres[ni].cx,
                                                  mega_buf.node_spheres[ni].cy,
                                                  mega_buf.node_spheres[ni].cz }};
                                    g_vis_flags[obj_idx] = frustum_test_sphere(&pface_frustum, ctr, mega_buf.node_spheres[ni].r) ? 1u : 0u;
                                    obj_idx++;
                                }
                                indirect_draw_upload_visibility(&indirect_sys, render.device, g_vis_flags, vis_count);
                                indirect_draw_compact(&indirect_sys, render.device, cmd);
                                indirect_draw_execute(&indirect_sys, render.device);
                                draw_calls++;
                                draw_bench_add(1u, draw_bench_enabled ? mega_count_visible_draws(&mega_buf, g_vis_flags) : 0u);
                                draw_bench_mark_legacy();
                            }
                        } else {
                        for (u32 sni = 0; sni < scene.node_count; sni++) {
                            SceneNode *snode = &scene.nodes[sni];
                            if (!snode->has_mesh) continue;
                            if (snode->mesh_index >= scene.mesh_count) continue;
                            Mesh *sm = &scene.meshes[snode->mesh_index];
                            if (pt_shadows.loc_model >= 0)
                                rhi_cmd_set_uniform_mat4(cmd, pt_shadows.loc_model,
                                                         &snode->world_transform.e[0][0]);
                            rhi_cmd_bind_vertex_buffer(cmd, sm->vertex_buf, 0);
                            if (sm->index_count > 0 && rhi_handle_valid(sm->index_buf)) {
                                rhi_cmd_bind_index_buffer(cmd, sm->index_buf, 0);
                                rhi_cmd_draw_indexed(cmd, sm->index_count, 1);
                            } else {
                                rhi_cmd_draw(cmd, 3, 1);
                            }
                        }
                        }

                    }
                }
                /* R78-3: Unbind cubemap FBO once after all faces — previously called
                 * point_shadow_render_end after each face, causing redundant
                 * glBindFramebuffer(0) → glBindFramebuffer(fbo) + viewport toggling
                 * per face (~96 redundant GL calls/frame with 4 lights × 6 faces). */
                point_shadow_render_end(&pt_shadows, cmd, w, h);
            }
        }

        profiler_pop();
        profiler_push("scene");
        rhi_gpu_timer_begin(gpu_scene_timer);
        rhi_gpu_timer_begin(gpu_forward_timer);

        /* R82-4: Occlusion node map built at init (scene data is static). */

        /* Cache point shadow gather once per frame (consumed by bind_material, deferred, terrain) */
        g_psc.count = point_shadow_gather(&pt_shadows, g_psc.tex, g_psc.far_planes);

        /* ---- Forward path guard: skip entire forward scene pass when deferred is active ---- */
        if (render.render_path == RENDER_PATH_FORWARD) {
        if (rhi_handle_valid(scene_fbo.fb)) {
            rhi_offscreen_fbo_bind(cmd, &scene_fbo);
        }
        rhi_cmd_clear_color(cmd, underwater ? 0.0f : bg_r, underwater ? 0.05f : bg_g, underwater ? 0.15f : bg_b, 1.0f);

        skybox_render(&skybox, cmd, &view.e[0][0], &frame_inv_proj.e[0][0], sun_dir_vec.e[0], sun_dir_vec.e[1], sun_dir_vec.e[2], sun_color.e[0], sun_color.e[1], sun_color.e[2]);

        /* R74-2: terrain_render draws terrain with hardcoded lighting + water interaction
         * effects (shoreline foam, underwater caustics/darkening via u_water_y/u_time).
         * It runs unconditionally — the clustered terrain draw below was always
         * depth-culled (same geometry, same depth, LESS test) and is now skipped. */
        terrain_render(&terrain, cmd, &view.e[0][0], &proj.e[0][0], &camera.position.e[0],
                       render.terrain_tex, active_sampler,
                       render.shadow_map.depth_tex, &render.cascade_vp[0].e[0][0], shadow_bias, water.water_y, (f32)total_time);

        water_update(&water, (f32)engine.delta_time);
        water_render(&water, cmd, &view.e[0][0], &proj.e[0][0], &camera.position.e[0],
                     render.shadow_map.depth_tex, &render.cascade_vp[0].e[0][0], shadow_bias);

        /* Clustered forward lighting pass */
        if (rhi_handle_valid(render.clustered_pipeline)) {
            light_system_clear(&lights);
            light_system_add_dir(&lights, sun_dir_vec.e[0], sun_dir_vec.e[1], sun_dir_vec.e[2], sun_color.e[0], sun_color.e[1], sun_color.e[2]);
            /* R59-fix: Incremental orbit rotation — 0 trig calls per frame.
             * Uses Taylor-approx cos/sin for small dθ = 0.5*dt ≈ 0.008 rad.
             * Renormalize every 256 frames to prevent cumulative drift.
             * Reset on total_time rollback (scene reset). */
            {
                static f32 orb_cos = 1.0f, orb_sin = 0.0f;
                static u32 orb_frames = 0;
                static f64 orb_prev_time = 0.0;
                if (total_time < orb_prev_time) { orb_cos = 1.0f; orb_sin = 0.0f; orb_frames = 0; }
                orb_prev_time = total_time;
                f32 orb_dth = 0.5f * (f32)engine.delta_time;
                if (orb_dth > 0.1f) {
                    /* dt spike — fall back to exact trig */
                    f32 phase = (f32)total_time * 0.5f;
                    orb_cos = cosf(phase); orb_sin = sinf(phase); orb_frames = 0;
                } else {
                f32 d2 = orb_dth * orb_dth;
                f32 od_c = 1.0f - d2 * 0.5f;  /* cos(x) ≈ 1 - x²/2 */
                f32 od_s = orb_dth * (1.0f - d2 / 6.0f); /* sin(x) ≈ x - x³/6 */
                f32 nc = orb_cos * od_c - orb_sin * od_s;
                f32 ns = orb_sin * od_c + orb_cos * od_s;
                orb_cos = nc; orb_sin = ns;
                orb_frames++;
                if ((orb_frames & 255) == 0) { /* periodic reset to exact trig — eliminates angle drift */
                    f32 phase = (f32)total_time * 0.5f;
                    orb_cos = cosf(phase); orb_sin = sinf(phase);
                }
                } /* end else (normal dt) */
                f32 cp = orb_cos, sp = orb_sin;
                for (u32 i = 0; i < 32; i++) {
                    f32 x = orbit_cos[i] * cp - orbit_sin[i] * sp;
                    f32 z = orbit_cos[i] * sp + orbit_sin[i] * cp;
                    light_system_add_point(&lights, x, 2.0f, z, 6.0f, orbit_r[i], orbit_g[i], orbit_b[i]);
                }
            }
            /* R75-1: Skip clustered cull/upload/bind — the clustered terrain draw
             * was skipped in R74-2 (always depth-culled by terrain_render). No
             * forward-path draw consumes the clustered light grid. Light
             * population (clear + add_dir + 32× add_point) is kept because
             * pt_shadows reads lights.point_count/lights.point_lights from the
             * previous frame. This saves ~98K CPU iterations (cluster binning)
             * + GPU upload + pipeline bind + ~10 uniform sets per frame. */
        }

        particles_cull(&particles, cmd);
        particles_render(&particles, cmd, &view.e[0][0], &proj.e[0][0]);

        if (rhi_handle_valid(render.skinned_pipeline)) {
            if (anim_blend_ready && scene.anim_clip_count > 0u) {
                anim_blend_evaluate(&anim_blend, (f32)engine.delta_time,
                                    scene.anim_clips, scene.anim_clip_count);
                if (anim_ik_ready && render.skeleton.joint_count >= 3u) {
                    static Mat4 ik_world[SKELETON_MAX_JOINTS];
                    skeleton_compute_world_transforms(&render.skeleton,
                        anim_blend.local_positions, anim_blend.local_rotations,
                        anim_blend.local_scales, ik_world);
                    /* R58-fix: Incremental rotation cache — 0 trig calls per frame.
                     * dθ = 0.7*dt ≈ 0.011 rad; Taylor approx sufficient.
                     * Renormalize every 256 frames to prevent cumulative drift.
                     * Reset on total_time rollback (scene reset). */
                    static f32 ik_cos = 1.0f, ik_sin = 0.0f;
                    static u32 ik_frames = 0;
                    static f64 ik_prev_time = 0.0;
                    if (total_time < ik_prev_time) { ik_cos = 1.0f; ik_sin = 0.0f; ik_frames = 0; }
                    ik_prev_time = total_time;
                    f32 ik_dth = 0.7f * (f32)engine.delta_time;
                    if (ik_dth > 0.1f) {
                        /* dt spike — fall back to exact trig */
                        f32 phase = (f32)total_time * 0.7f;
                        ik_cos = cosf(phase); ik_sin = sinf(phase); ik_frames = 0;
                    } else {
                    f32 id2 = ik_dth * ik_dth;
                    f32 ik_cd = 1.0f - id2 * 0.5f;         /* cos(x) ≈ 1 - x²/2 */
                    f32 ik_sd = ik_dth * (1.0f - id2 / 6.0f); /* sin(x) ≈ x - x³/6 */
                    f32 nc = ik_cos * ik_cd - ik_sin * ik_sd;
                    f32 ns = ik_sin * ik_cd + ik_cos * ik_sd;
                    ik_cos = nc; ik_sin = ns;
                    ik_frames++;
                    if ((ik_frames & 255) == 0) { /* periodic reset to exact trig — eliminates angle drift */
                        f32 phase = (f32)total_time * 0.7f;
                        ik_cos = cosf(phase); ik_sin = sinf(phase);
                    }
                    } /* end else (normal dt) */
                    Vec3 ik_target = {{
                        camera.position.e[0] + ik_sin * 2.0f,
                        camera.position.e[1] + 1.2f,
                        camera.position.e[2] + ik_cos * 2.0f - 2.5f
                    }};
                    Vec3 ik_pole = {{
                        camera.position.e[0],
                        camera.position.e[1] + 2.0f,
                        camera.position.e[2]
                    }};
                    anim_ik_set_target(&anim_ik, 0, 0u, 1u, 2u, ik_target, ik_pole);
                    anim_ik_solve(&anim_ik, anim_blend.local_positions,
                                   anim_blend.local_rotations, ik_world);
                }
                skeleton_apply_local_trs(&render.skeleton,
                    anim_blend.local_positions, anim_blend.local_rotations,
                    anim_blend.local_scales);
            } else {
                render.anim_clip.time += engine.delta_time;
                if (render.anim_clip.time >= render.anim_clip.duration) {
                    render.anim_clip.time -= render.anim_clip.duration;
                }
                skeleton_evaluate(&render.skeleton, &render.anim_clip, engine.delta_time);
            }
            /* R76-4: Skip skeleton upload, pipeline bind, and uniform sets when
             * no skinned rendering will occur (no skinned meshes and no fallback VBO). */
            if (scene.skinned_mesh_count > 0 || rhi_handle_valid(render.skinned_vbo)) {
            skeleton_upload(&render.skeleton);

            rhi_cmd_bind_pipeline(cmd, wireframe_mode && rhi_handle_valid(render.wire_skinned_pipeline) ? render.wire_skinned_pipeline : render.skinned_pipeline);
            rhi_cmd_set_uniform_mat4(cmd, render.sk_loc_view, &view.e[0][0]);
            rhi_cmd_set_uniform_mat4(cmd, render.sk_loc_proj, &proj.e[0][0]);
            rhi_cmd_set_uniform_vec3(cmd, render.sk_loc_light_dir, sun_dir_vec.e[0], sun_dir_vec.e[1], sun_dir_vec.e[2]);
            rhi_cmd_set_uniform_vec3(cmd, render.sk_loc_light_color, sun_color.e[0], sun_color.e[1], sun_color.e[2]);
            rhi_cmd_set_uniform_vec3(cmd, render.sk_loc_ambient, ambient_col.e[0], ambient_col.e[1], ambient_col.e[2]);
            rhi_cmd_set_uniform_vec3(cmd, render.sk_loc_camera_pos,
                camera.position.e[0], camera.position.e[1], camera.position.e[2]);

            if (scene.skinned_mesh_count > 0) {
                for (u32 si = 0; si < scene.skinned_mesh_count; si++) {
                    SkinnedMesh *sm = &scene.skinned_meshes[si];
                    Material *mat = (sm->material_idx < scene.material_count) ? &scene.materials[sm->material_idx] : NULL;
                    bind_material(cmd, &render, mat, &scene);
                    rhi_cmd_bind_texel_buffers(cmd, render.skeleton.joint_buf, render.skeleton.joint_buf);
                    rhi_cmd_bind_vertex_buffer(cmd, sm->vertex_buf, 0);
                    if (sm->index_count > 0 && rhi_handle_valid(sm->index_buf)) {
                        rhi_cmd_bind_index_buffer(cmd, sm->index_buf, 0);
                        rhi_cmd_draw_indexed(cmd, sm->index_count, 1);
                    } else {
                        rhi_cmd_draw(cmd, 3, 1);
                    }
                    draw_calls++; tri_count += sm->index_count > 0 ? sm->index_count / 3 : 1;
                }
            } else if (rhi_handle_valid(render.skinned_vbo)) {
                bind_material(cmd, &render, NULL, &scene);
                rhi_cmd_bind_texel_buffers(cmd, render.skeleton.joint_buf, render.skeleton.joint_buf);
                rhi_cmd_bind_vertex_buffer(cmd, render.skinned_vbo, 0);
                rhi_cmd_bind_index_buffer(cmd, render.skinned_ibo, 0);
                rhi_cmd_draw_indexed(cmd, render.skinned_index_count, 1);
                draw_calls++; tri_count += render.skinned_index_count / 3;
            }
            }
        }

        rhi_cmd_bind_pipeline(cmd, active_pipeline);
        rhi_cmd_set_uniform_mat4(cmd, render.loc_view, &view.e[0][0]);
        rhi_cmd_set_uniform_mat4(cmd, render.loc_proj, &proj.e[0][0]);
        rhi_cmd_set_uniform_vec3(cmd, render.loc_light_dir, sun_dir_vec.e[0], sun_dir_vec.e[1], sun_dir_vec.e[2]);
        rhi_cmd_set_uniform_vec3(cmd, render.loc_light_color, sun_color.e[0], sun_color.e[1], sun_color.e[2]);
        rhi_cmd_set_uniform_vec3(cmd, render.loc_ambient, ambient_col.e[0], ambient_col.e[1], ambient_col.e[2]);
        rhi_cmd_set_uniform_vec3(cmd, render.loc_camera_pos,
                                 camera.position.e[0], camera.position.e[1], camera.position.e[2]);

        Frustum frustum = frame_frustum;

        if (scene.mesh_count > 0 && rhi_handle_valid(render.instanced_pipeline)) {
            ComponentType mesh_query_types[] = { COMP_TRANSFORM, COMP_MESH_REF };
            Query *mq = world_query_cached(world, mesh_query_types, 2);
            u32 instance_count = 0;

            if (mq && mq->match_count > 0) {
                for (u32 mi = 0; mi < mq->match_count; mi++) {
                    Archetype *a = mq->matching[mi];
                    /* Find COMP_TRANSFORM column index in archetype key */
                    u32 transform_col = UINT32_MAX;
                    for (u32 ki = 0; ki < a->key.count; ki++) {
                        if (a->key.ids[ki] == COMP_TRANSFORM) { transform_col = ki; break; }
                    }
                    if (transform_col == UINT32_MAX) continue;
                    u32 t_offset = a->offsets[transform_col];
                    Chunk *c = a->chunks;
                    while (c) {
                        for (u32 ci = 0; ci < c->count; ci++) {
                            CTransform *et = (CTransform *)((u8 *)c + t_offset + ci * sizeof(CTransform));
                            Vec3 epos = {{ et->pos[0], et->pos[1], et->pos[2] }};
                            if (!frustum_test_sphere(&frustum, epos, 1.0f)) continue;
                            if (instance_count < INSTANCE_DATA_CAP) {
                                /* Direct-write translation matrix (avoids mat4_identity + mat4_translation overhead). */
                                f32 *md = instance_data + instance_count * 16;
                                md[0]=1; md[1]=0; md[2]=0; md[3]=0;
                                md[4]=0; md[5]=1; md[6]=0; md[7]=0;
                                md[8]=0; md[9]=0; md[10]=1; md[11]=0;
                                md[12]=et->pos[0]; md[13]=et->pos[1]; md[14]=et->pos[2]; md[15]=1;
                                instance_count++;
                            }
                        }
                        c = c->next;
                    }
                }
            }
            /* cached query — no query_done() needed */

            {
                InputState *inp = platform_input(engine.platform);
                if (input_key_pressed(inp, 57)) {
                    camera.move_speed = fminf(camera.move_speed + 1.0f, 20.0f);
                    LOG_INFO("Camera speed: %.1f", camera.move_speed);
                }
                if (input_key_pressed(inp, 48)) {
                    camera.move_speed = fmaxf(camera.move_speed - 1.0f, 0.5f);
                    LOG_INFO("Camera speed: %.1f", camera.move_speed);
                }
                if (input_key_down(inp, (i32)'l')) {
                    sun_azimuth += 1.5f * engine.delta_time;
                }
                if (input_key_down(inp, (i32)'j')) {
                    sun_azimuth -= 1.5f * engine.delta_time;
                }
                if (input_key_down(inp, (i32)'i')) {
                    sun_elevation = fminf(sun_elevation + 1.0f * engine.delta_time, 1.55f);
                }
                if (input_key_down(inp, (i32)'k')) {
                    sun_elevation = fmaxf(sun_elevation - 1.0f * engine.delta_time, 0.05f);
                }
                if (input_key_pressed(inp, (i32)'o')) {
                    tod_cycle = !tod_cycle;
                    LOG_INFO("Time-of-day cycle: %s", tod_cycle ? "ON" : "OFF");
                }
                if (tod_cycle) {
                    sun_azimuth += tod_speed * engine.delta_time;
                    sun_elevation = 0.4f + 0.55f * sinf(sun_azimuth * 0.5f);
                    if (sun_elevation < 0.05f) sun_elevation = 0.05f;
                }
                if (input_key_pressed(inp, (i32)'f')) {
                    wireframe_mode = !wireframe_mode;
                    LOG_INFO("Wireframe: %s", wireframe_mode ? "ON" : "OFF");
                }
                if (input_key_pressed(inp, (i32)'p')) {
                    render.render_path = (render.render_path == RENDER_PATH_FORWARD)
                        ? RENDER_PATH_DEFERRED : RENDER_PATH_FORWARD;
                    LOG_INFO("Render path: %s",
                             render.render_path == RENDER_PATH_DEFERRED ? "DEFERRED" : "FORWARD");
                }
                if (input_key_pressed(inp, (i32)'h')) {
                    static i32 aa_mode = 3;
                    aa_mode = (aa_mode + 1) % 4;
                    fxaa_enabled = (aa_mode == 1 || aa_mode == 3);
                    taa_enabled = (aa_mode == 2 || aa_mode == 3);
                    const char *aa_names[] = { "off", "FXAA", "TAA", "FXAA+TAA" };
                    LOG_INFO("AA: %s", aa_names[aa_mode]);
                }
                if (input_key_pressed(inp, (i32)'v')) {
                    vsync_on = !vsync_on;
                    rhi_set_vsync(render.device, vsync_on);
                    LOG_INFO("VSync: %s", vsync_on ? "on" : "off");
                }
                if (input_key_pressed(inp, (i32)'t')) {
                    nearest_filter = !nearest_filter;
                    LOG_INFO("Tex filter: %s", nearest_filter ? "nearest" : "linear");
                }
                if (input_key_pressed(inp, (i32)'c')) {
                    bg_preset = (bg_preset + 1) % 6;
                    f32 bgs[][3] = { {0.05f,0.05f,0.1f}, {0.0f,0.0f,0.0f}, {0.15f,0.15f,0.15f}, {0.4f,0.6f,0.8f}, {0.02f,0.02f,0.05f}, {0.8f,0.85f,0.9f} };
                    bg_r = bgs[bg_preset][0]; bg_g = bgs[bg_preset][1]; bg_b = bgs[bg_preset][2];
                    const char *bg_names[] = { "dark blue", "black", "gray", "sky blue", "deep space", "overcast" };
                    LOG_INFO("Background: %s", bg_names[bg_preset]);
                }
                if (input_key_pressed(inp, (i32)'.')) {
                    time_preset = (time_preset + 1) % 4;
                    switch (time_preset) {
                        case 0: sun_elevation = 0.93f; sun_azimuth = 1.03f; bg_r=0.05f; bg_g=0.05f; bg_b=0.1f; break;
                        case 1: sun_elevation = 0.15f; sun_azimuth = 3.14f; bg_r=0.5f;  bg_g=0.25f; bg_b=0.1f;  break;
                        case 2: sun_elevation = 0.05f; sun_azimuth = 4.71f; bg_r=0.01f; bg_g=0.01f; bg_b=0.03f; break;
                        case 3: sun_elevation = 0.1f;  sun_azimuth = 0.5f;  bg_r=0.4f;  bg_g=0.3f;  bg_b=0.15f; break;
                    }
                    static const char *td[] = {"Noon", "Sunset", "Midnight", "Dawn"};
                    LOG_INFO("Time preset: %s", td[time_preset]);
                }
                if (input_key_pressed(inp, (i32)'z')) {
                    shadow_bias = fmaxf(shadow_bias - 0.001f, 0.0f);
                    LOG_INFO("Shadow bias: %.4f", shadow_bias);
                }
                if (input_key_pressed(inp, (i32)'x')) {
                    shadow_bias = fminf(shadow_bias + 0.001f, 0.05f);
                    LOG_INFO("Shadow bias: %.4f", shadow_bias);
                }
                if (input_key_pressed(inp, (i32)'e')) {
                    if (world->entity_count >= ENTITY_SPAWN_CAP) {
                        LOG_INFO("Entity cap reached (%u/%u)", world->entity_count, ENTITY_SPAWN_CAP);
                    } else {
                    Vec3 ecam_fwd = vec3(cam_cp * cam_sy, cam_sp, -cam_cp * cam_cy);
                    Vec3 ecam_right = vec3(-cam_cy, 0, -cam_sy);
                    for (i32 ei = 0; ei < 3; ei++) {
                        Vec3 offset = vec3_scale(ecam_right, (f32)(ei - 1) * 1.5f);
                        Vec3 spawn_pos = vec3_add(vec3_add(camera.position, vec3_scale(ecam_fwd, 2.0f)), offset);
                        Vec3 half_ext = vec3(0.5f, 0.5f, 0.5f);
                        if (physics->count >= physics->capacity) break;
                        u32 new_body = physics_body_create(physics, spawn_pos, half_ext, 1.0f, false, (u32)engine.frame_count);
                        Vec3 impulse = vec3_scale(ecam_fwd, 15.0f);
                        impulse.e[1] += 5.0f;
                        physics_body_apply_impulse(physics, new_body, impulse);
                        Entity se = world_create_entity(world);
                        CTransform *st = world_add_component(world, se, COMP_TRANSFORM);
                        if (st) { st->pos[0] = spawn_pos.e[0]; st->pos[1] = spawn_pos.e[1]; st->pos[2] = spawn_pos.e[2]; }
                        CRigidBody *srb = world_add_component(world, se, COMP_RIGID_BODY);
                        if (srb) srb->physics_id = new_body;
                        CMeshRef *smr = world_add_component(world, se, COMP_MESH_REF);
                        if (smr) smr->mesh_index = 0;
                    }
                    LOG_INFO("Spawned 3 entities (%u/%u bodies, %u/%u entities)", physics->count, physics->capacity, world->entity_count, ENTITY_SPAWN_CAP);
                    }
                }
                if (input_key_pressed(inp, (i32)'g')) {
                    platform_toggle_fullscreen(engine.platform);
                }
                if (input_key_pressed(inp, (i32)'\'')) {
                    static const f32 rates[] = {200.0f, 500.0f, 1000.0f, 2000.0f, 5000.0f, 0.0f};
                    static const char *rnames[] = {"low", "medium", "high", "ultra", "insane", "OFF"};
                    particle_preset = (particle_preset + 1) % 6;
                    particles.emit_rate = rates[particle_preset];
                    LOG_INFO("Particle rate: %s (%.0f/s)", rnames[particle_preset], rates[particle_preset]);
                }
                if (input_key_pressed(inp, (i32)'q')) {
                    static u32 qm = 0;
                    qm = (qm + 1) % 3;
                    terrain_follow = (qm == 1);
                    cam_height_lock = (qm == 2);
                    if (cam_height_lock) cam_locked_y = camera.position.e[1];
                    static const char *qm_names[] = {"free", "terrain follow", "height lock"};
                    LOG_INFO("Camera Y: %s", qm_names[qm]);
                }
                if (input_key_pressed(inp, (i32)'[')) {
                    static u32 cam_mode = 0;
                    cam_mode = (cam_mode + 1) % 3;
                    third_person = (cam_mode == 1);
                    top_down_view = (cam_mode == 2);
                    static const char *cm[] = {"first-person", "third-person", "top-down"};
                    LOG_INFO("Camera: %s", cm[cam_mode]);
                }
                if (input_key_pressed(inp, (i32)'1')) {
                    Vec3 epicenter = camera.position;
                    particles.emit_pos[0] = epicenter.e[0];
                    particles.emit_pos[1] = epicenter.e[1];
                    particles.emit_pos[2] = epicenter.e[2];
                    particles.emit_rate = 5000.0f;
                    screen_shake = 2.0f;
                    for (u32 bi = 1; bi < physics->count; bi++) {
                        Vec3 dir = vec3_sub(physics->bodies[bi].position, epicenter);
                        f32 dist = vec3_len(dir);
                        if (dist < 0.01f) dist = 0.01f;
                        f32 force = fmaxf(0.0f, 20.0f - dist * 2.0f);
                        Vec3 imp = vec3_scale(vec3_scale(dir, 1.0f/dist), force);
                        imp.e[1] += force * 0.5f;
                        physics_body_apply_impulse(physics, bi, imp);
                    }
                    LOG_INFO("EXPLOSION at (%.1f,%.1f,%.1f)", epicenter.e[0], epicenter.e[1], epicenter.e[2]);
                }
                if (input_key_pressed(inp, (i32)'2')) {
                    Vec3 cam_pos = camera.position;
                    for (u32 bi = 1; bi < physics->count; bi++) {
                        if (physics->bodies[bi].is_static) continue;
                        Vec3 dir = vec3_sub(cam_pos, physics->bodies[bi].position);
                        f32 dist = vec3_len(dir);
                        if (dist < 0.01f) dist = 0.01f;
                        f32 force = 10.0f / (1.0f + dist * 0.5f);
                        physics_body_apply_impulse(physics, bi, vec3_scale(vec3_scale(dir, 1.0f/dist), force));
                    }
                    LOG_INFO("MAGNET: pulling %u bodies", physics->count > 1 ? physics->count - 1 : 0);
                }
                if (input_key_pressed(inp, (i32)'3')) {
                    static const f32 radii[] = {1.0f, 3.0f, 6.0f, 10.0f, 20.0f};
                    static const char *rn[] = {"tiny","small","medium","large","huge"};
                    static u32 ri = 1;
                    ri = (ri + 1) % 5;
                     brush_radius = radii[ri];
                     LOG_INFO("Brush: %s (%.0f)%s", rn[ri], brush_radius, brush_flatten ? " FLAT" : "");
                 }
                 if (input_key_pressed(inp, (i32)'a')) {
                     brush_mode = (brush_mode + 1) % 4;
                     brush_flatten = (brush_mode == 1);
                     static const char *bm[] = {"raise/lower", "flatten", "erode", "noise stamp"};
                     LOG_INFO("Brush mode: %s", bm[brush_mode]);
                 }
                if (input_key_pressed(inp, 260)) {
                    if (selected_entity_count > 0 && selected_entity_id > 0) {
                        Entity se = world->entities[selected_entity_id];
                        CTransform *st = world_get_component(world, se, COMP_TRANSFORM);
                        CRigidBody *sr = world_get_component(world, se, COMP_RIGID_BODY);
                        if (st) {
                            Vec3 old_cam = camera.position;
                            camera.position.e[0] = st->pos[0];
                            camera.position.e[1] = st->pos[1] + 2.0f;
                            camera.position.e[2] = st->pos[2];
                            st->pos[0] = old_cam.e[0];
                            st->pos[1] = old_cam.e[1];
                            st->pos[2] = old_cam.e[2];
                            if (sr && sr->physics_id > 0 && sr->physics_id < physics->count) {
                                physics->bodies[sr->physics_id].position = old_cam;
                                physics->bodies[sr->physics_id].velocity = vec3(0,0,0);
                            }
                            LOG_INFO("SWAPPED positions with entity %u", selected_entity_id);
                        }
                    }
                }
                if (input_key_pressed(inp, (i32)'d')) {
                    if (selected_entity_count > 0 && selected_entity_id > 0) {
                        Entity se = world->entities[selected_entity_id];
                        CRigidBody *sr = world_get_component(world, se, COMP_RIGID_BODY);
                        if (sr && sr->physics_id > 0 && sr->physics_id < physics->count) {
                            static const f32 masses[] = {0.5f, 1.0f, 5.0f, 20.0f, 100.0f};
                            static const char *mn[] = {"light","normal","heavy","very heavy","immovable"};
                            static u32 mi = 1;
                            mi = (mi + 1) % 5;
                            physics->bodies[sr->physics_id].mass = masses[mi];
                            LOG_INFO("Mass: %s (%.1f)", mn[mi], masses[mi]);
                        }
                    }
                }
                if (input_key_pressed(inp, (i32)'s')) {
                    static const f32 am[] = {0.3f, 0.5f, 1.0f, 2.0f, 4.0f};
                    static const char *an[] = {"dark","dim","normal","bright","overlit"};
                    static u32 ai = 2;
                    ai = (ai + 1) % 5;
                    ambient_mult = am[ai];
                    LOG_INFO("Ambient: %s (%.1fx)", an[ai], ambient_mult);
                }
                if (input_key_pressed(inp, (i32)'w')) {
                    if (selected_entity_count > 0 && selected_entity_id > 0) {
                        Entity se = world->entities[selected_entity_id];
                        CTransform *st = world_get_component(world, se, COMP_TRANSFORM);
                        CRigidBody *sr = world_get_component(world, se, COMP_RIGID_BODY);
                        if (st) {
                            st->pos[0] = camera.position.e[0];
                            st->pos[1] = camera.position.e[1];
                            st->pos[2] = camera.position.e[2];
                        }
                        if (sr && sr->physics_id > 0 && sr->physics_id < physics->count) {
                            physics->bodies[sr->physics_id].position = camera.position;
                            physics->bodies[sr->physics_id].velocity = vec3(0,0,0);
                        }
                        LOG_INFO("Entity %u teleported to camera", selected_entity_id);
                    }
                }
                if (input_key_pressed(inp, (i32)'4')) {
                    if (selected_entity_count > 0 && selected_entity_id > 0) {
                        Entity se = world->entities[selected_entity_id];
                        CRigidBody *sr = world_get_component(world, se, COMP_RIGID_BODY);
                        if (sr && sr->physics_id > 0 && sr->physics_id < physics->count) {
                            physics_body_apply_impulse(physics, sr->physics_id, vec3_scale(cam_fwd, 15.0f));
                            LOG_INFO("THREW entity %u forward", selected_entity_id);
                        }
                    }
                }
                if (input_key_pressed(inp, (i32)'5')) {
                    static const f32 rests[] = {0.0f, 0.3f, 0.6f, 0.9f, 1.0f};
                    static const char *rn[] = {"no bounce","low","medium","high","super bouncy"};
                    static u32 ri = 1;
                    ri = (ri + 1) % 5;
                    for (u32 bi = 0; bi < physics->count; bi++) {
                        if (!physics->bodies[bi].is_static) physics->bodies[bi].restitution = rests[ri];
                    }
                    LOG_INFO("Restitution: %s (%.1f)", rn[ri], rests[ri]);
                }
                if (input_key_pressed(inp, (i32)'6')) {
                    if (selected_entity_count > 0 && selected_entity_id > 0) {
                        Entity se = world->entities[selected_entity_id];
                        CRigidBody *sr = world_get_component(world, se, COMP_RIGID_BODY);
                        if (sr && sr->physics_id > 0 && sr->physics_id < physics->count) {
                            physics->bodies[sr->physics_id].is_static = !physics->bodies[sr->physics_id].is_static;
                            if (!physics->bodies[sr->physics_id].is_static) {
                                physics->bodies[sr->physics_id].velocity = vec3(0,0,0);
                            }
                            LOG_INFO("Entity %u: %s", selected_entity_id, physics->bodies[sr->physics_id].is_static ? "FROZEN" : "UNFROZEN");
                        }
                    }
                }
                if (input_key_pressed(inp, (i32)'7')) {
                    if (selected_entity_count > 0 && selected_entity_id > 0) {
                        Entity se = world->entities[selected_entity_id];
                        CRigidBody *sr = world_get_component(world, se, COMP_RIGID_BODY);
                        if (sr && sr->physics_id > 0 && sr->physics_id < physics->count) {
                            static const f32 sizes[] = {0.25f, 0.5f, 1.0f, 2.0f, 4.0f};
                            static const char *sn[] = {"tiny","small","normal","large","huge"};
                            static u32 si = 1;
                            si = (si + 1) % 5;
                            physics->bodies[sr->physics_id].half_extent = vec3(sizes[si], sizes[si], sizes[si]);
                            LOG_INFO("Entity %u scale: %s (%.1f)", selected_entity_id, sn[si], sizes[si]);
                        }
                    }
                }
                if (input_key_pressed(inp, (i32)'8')) {
                    slow_motion = !slow_motion;
                    LOG_INFO("Slow-mo: %s", slow_motion ? "ON (0.25x)" : "OFF");
                }
                if (input_key_pressed(inp, (i32)'0')) {
                    static const Vec3 wcolors[] = {{.e={0.1f,0.3f,0.5f}},{.e={0.0f,0.15f,0.3f}},{.e={0.05f,0.4f,0.3f}},{.e={0.3f,0.2f,0.1f}},{.e={0.15f,0.15f,0.25f}}};
                    static const char *wcn[] = {"ocean blue","deep sea","tropical","murky","twilight"};
                    water_color_preset = (water_color_preset + 1) % 5;
                    water.color = wcolors[water_color_preset];
                    LOG_INFO("Water color: %s", wcn[water_color_preset]);
                }
                if (input_key_pressed(inp, (i32)',')) {
                    if (!recording_path && !playing_path) {
                        recording_path = true; path_count = 0;
                        LOG_INFO("Path recording STARTED (max %d frames)", MAX_PATH);
                    } else if (recording_path) {
                        recording_path = false;
                        LOG_INFO("Path recording STOPPED (%u frames). Press , to playback.", path_count);
                    } else {
                        playing_path = false; path_idx = 0;
                        LOG_INFO("Path playback STOPPED");
                    }
                }
                if (input_key_pressed(inp, (i32)'/')) {
                    fog_enabled = !fog_enabled;
                    LOG_INFO("Distance fog: %s (near=%.0f far=%.0f)", fog_enabled ? "ON" : "OFF", fog_near, fog_far);
                }
                if (fog_enabled) {
                    if (input_key_pressed(inp, (i32)'\\')) { fog_far = fminf(fog_far + 5.0f, 200.0f); LOG_INFO("Fog far: %.0f", fog_far); }
                }
                if (input_key_pressed(inp, (i32)'`')) {
                    fps_limit_idx = (fps_limit_idx + 1) % 6;
                    engine.target_fps = fps_limits[fps_limit_idx];
                    LOG_INFO("FPS limit: %.0f%s", engine.target_fps, engine.target_fps == 0.0f ? " (unlimited)" : "");
                }
                if (input_key_pressed(inp, (i32)'k')) {
                    layout_mode = (layout_mode + 1) % 4;
                    static const char *layout_names[] = { "grid", "circle", "spiral", "wave" };
                    ComponentType lq_types[] = { COMP_TRANSFORM };
                    Query *lq = world_query(world, lq_types, 1);
                    u32 li = 0;
                    if (lq) {
                        for (u32 lmi = 0; lmi < lq->match_count; lmi++) {
                            Archetype *la = lq->matching[lmi];
                            Chunk *lc = la->chunks;
                            while (lc) {
                                u32 *lents = (u32 *)((u8 *)lc + la->entity_offset);
                                for (u32 lci = 0; lci < lc->count; lci++) {
                                    Entity le = world->entities[lents[lci]];
                                    CTransform *lt = world_get_component(world, le, COMP_TRANSFORM);
                                    if (!lt) continue;
                                    f32 t = (f32)li / 10.0f;
                                    switch (layout_mode) {
                                    case 0:
                                        lt->pos[0] = (f32)(li % 5) * 2.0f - 4.0f;
                                        lt->pos[1] = 8.0f + (f32)(li / 5) * 3.0f;
                                        lt->pos[2] = 0.0f;
                                        break;
                                    case 1:
                                        lt->pos[0] = cosf(t * 6.2832f) * 6.0f;
                                        lt->pos[1] = 5.0f;
                                        lt->pos[2] = sinf(t * 6.2832f) * 6.0f;
                                        break;
                                    case 2:
                                        lt->pos[0] = cosf(t * 12.566f) * (1.0f + t * 5.0f);
                                        lt->pos[1] = 2.0f + t * 8.0f;
                                        lt->pos[2] = sinf(t * 12.566f) * (1.0f + t * 5.0f);
                                        break;
                                    case 3:
                                        lt->pos[0] = (f32)(li % 5) * 2.0f - 4.0f;
                                        lt->pos[1] = 5.0f + sinf((f32)li * 0.8f) * 3.0f;
                                        lt->pos[2] = (f32)(li / 5) * 2.0f - 1.0f;
                                        break;
                                    }
                                    li++;
                                }
                                lc = lc->next;
                            }
                        }
                    }
                    query_done(lq);
                    for (u32 ri = 1; ri < physics->count && ri <= 10; ri++) {
                        if (ri - 1 < li) {
                            CTransform *rt = NULL;
                            ComponentType rq_types[] = { COMP_TRANSFORM };
                            Query *rq = world_query(world, rq_types, 1);
                            if (rq) {
                                u32 idx = 0;
                                for (u32 rmi = 0; rmi < rq->match_count && !rt; rmi++) {
                                    Archetype *ra = rq->matching[rmi];
                                    Chunk *rc = ra->chunks;
                                    while (rc && !rt) {
                                        u32 *rents = (u32 *)((u8 *)rc + ra->entity_offset);
                                        for (u32 rci = 0; rci < rc->count; rci++) {
                                            if (idx == ri - 1) {
                                                Entity re = world->entities[rents[rci]];
                                                rt = world_get_component(world, re, COMP_TRANSFORM);
                                                break;
                                            }
                                            idx++;
                                        }
                                        rc = rc->next;
                }
                if (input_key_pressed(inp, 32)) {
                    if (selected_entity_id > 0) {
                        Entity se = world->entities[selected_entity_id];
                        CRigidBody *sr = world_get_component(world, se, COMP_RIGID_BODY);
                        if (sr && sr->physics_id > 0 && sr->physics_id < physics->count) {
                            Vec3 v = physics->bodies[sr->physics_id].velocity;
                            f32 spd = vec3_len(v);
                            if (spd > 2.0f) {
                                physics->bodies[sr->physics_id].velocity = vec3(0, 0, 0);
                                LOG_INFO("Entity %u STOPPED (was %.1f m/s)", selected_entity_id, spd);
                            } else {
                                physics_body_apply_impulse(physics, sr->physics_id, vec3(0, 8.0f, 0));
                            }
                        }
                    } else {
                        u32 stopped = 0;
                        for (u32 bi = 1; bi < physics->count; bi++) {
                            if (!physics->bodies[bi].is_static && vec3_len(physics->bodies[bi].velocity) > 0.1f) {
                                physics->bodies[bi].velocity = vec3(0, 0, 0);
                                stopped++;
                            }
                        }
                        if (stopped > 0) LOG_INFO("ALL STOP: %u bodies", stopped);
                    }
                }
            }
                            }
                            query_done(rq);
                            if (rt) {
                                physics->bodies[ri].position = vec3(rt->pos[0], rt->pos[1], rt->pos[2]);
                                physics->bodies[ri].velocity = vec3(0, 0, 0);
                            }
                        }
                    }
                    LOG_INFO("Layout: %s (%u entities)", layout_names[layout_mode], li);
                }
                if (input_key_pressed(inp, (i32)'m') && bench_frames == 0) {
                    bench_saved.taa = taa_enabled; bench_saved.fxaa = fxaa_enabled;
                    bench_saved.mb = mb_enabled; bench_saved.dof = dof_enabled;
                    bench_saved.ssr = ssr_enabled; bench_saved.ssgi = ssgi_enabled;
                    bench_saved.cs = cs_enabled; bench_saved.vol = vol_enabled;
                    bench_saved.lf = lf_enabled; bench_saved.bloom = (postfx.bloom_strength > 0.0f);
                    bench_saved.gr = (god_rays_intensity > 0.0f); bench_saved.sss = sss_enabled;
                    bench_saved.sharpen = sharpen_enabled; bench_saved.cg = cg_enabled;
                    bench_saved.lensfx = lensfx_enabled;
                    taa_enabled = false; fxaa_enabled = false; mb_enabled = false;
                    dof_enabled = false; ssr_enabled = false; ssgi_enabled = false;
                    cs_enabled = false; vol_enabled = false; lf_enabled = false;
                    postfx.bloom_strength = 0.0f; god_rays_intensity = 0.0f;
                    sss_enabled = false; sharpen_enabled = false; cg_enabled = false;
                    lensfx_enabled = false;
                    bench_frames = 120;
                    bench_start = 0.0;
                    LOG_INFO("Benchmark: 120 frames with all effects OFF");
                }
                if (input_key_pressed(inp, (i32)'u')) {
                    show_help = !show_help;
                }
                if (input_key_pressed(inp, (i32)'r')) {
                    for (u32 ri = 1; ri <= 10 && ri < physics->count; ri++) {
                        physics->bodies[ri].position.e[0] = (f32)((ri - 1) % 5) * 2.0f - 4.0f;
                        physics->bodies[ri].position.e[1] = 8.0f + (f32)((ri - 1) / 5) * 3.0f;
                        physics->bodies[ri].position.e[2] = 0.0f;
                        physics->bodies[ri].velocity = vec3(0, 0, 0);
                    }
                    LOG_INFO("Scene reset: %u bodies + terrain regenerated", physics->count > 1 ? (physics->count - 1 < 10 ? physics->count - 1 : 10) : 0);
                    terrain_generate(&terrain, terrain_preset);
                }
                if (input_key_pressed(inp, (i32)'p')) {
                    particles.emit_pos[0] = camera.position.e[0];
                    particles.emit_pos[1] = camera.position.e[1];
                    particles.emit_pos[2] = camera.position.e[2];
                    particles.emit_rate = 2000.0f;
                    for (u32 bi = 1; bi < physics->count; bi++) {
                        physics_body_apply_impulse(physics, bi, vec3(0, 15.0f, 0));
                    }
                    LOG_INFO("Boom! Particles + impulse at camera");
                    screen_shake = 1.0f;
                }
                if (input_key_released(inp, (i32)'p')) {
                    particles.emit_pos[0] = 0.0f;
                    particles.emit_pos[1] = 2.0f;
                    particles.emit_pos[2] = 0.0f;
                    particles.emit_rate = 200.0f;
                }
                if (input_key_pressed(inp, (i32)'j')) {
                    particle_trail = !particle_trail;
                    LOG_INFO("Particle trail: %s", particle_trail ? "ON (follows selected entity)" : "OFF");
                }
                if (input_key_pressed(inp, (i32)'t')) {
                    tornado_mode = !tornado_mode;
                    LOG_INFO("Tornado mode: %s", tornado_mode ? "ON" : "OFF");
                }
                if (input_key_down(inp, (i32)'y') || input_key_down(inp, (i32)'h')) {
                    f32 fwd_x = cam_fwd.e[0], fwd_z = cam_fwd.e[2];
                    f32 tx = camera.position.e[0] + fwd_x * 5.0f;
                    f32 tz = camera.position.e[2] + fwd_z * 5.0f;
                    if (brush_mode == 1) {
                        terrain_flatten(&terrain, tx, tz, brush_radius);
                    } else if (brush_mode == 2) {
                        terrain_erode(&terrain, tx, tz, brush_radius, 1);
                    } else if (brush_mode == 3) {
                        terrain_noise_stamp(&terrain, tx, tz, brush_radius, 1.5f, (f32)total_time);
                    } else {
                        f32 str = input_key_down(inp, (i32)'y') ? 0.3f : -0.3f;
                        terrain_modify_height(&terrain, tx, tz, brush_radius, str * (f32)engine.delta_time);
                    }
                }
                if (input_key_pressed(inp, (i32)';')) {
                    terrain_preset = (terrain_preset + 1) % 5;
                    terrain_generate(&terrain, terrain_preset);
                    static const char *tnames[] = {"Rolling Hills", "Volcano", "Waves", "Ridged", "Craters"};
                    LOG_INFO("Terrain preset: %s", tnames[terrain_preset]);
                }
                if (input_key_pressed(inp, 259)) {
                    ComponentType sel_types[] = { COMP_TRANSFORM, COMP_MESH_REF };
                    Query *sq = world_query(world, sel_types, 2);
                    u32 total = 0;
                    if (sq) {
                        for (u32 qi = 0; qi < sq->match_count; qi++) {
                            Archetype *a = sq->matching[qi];
                            Chunk *c = a->chunks;
                            while (c) { total += c->count; c = c->next; }
                        }
                    }
                    selected_entity_count = total;
                    if (total > 0) {
                        selected_entity_idx = (selected_entity_idx + 1) % total;
                        u32 si = 0;
                        if (sq) {
                            for (u32 qi = 0; qi < sq->match_count; qi++) {
                                Archetype *a = sq->matching[qi];
                                Chunk *c = a->chunks;
                                while (c) {
                                    u32 *ents = (u32 *)((u8 *)c + a->entity_offset);
                                    for (u32 ci = 0; ci < c->count; ci++) {
                                        if (si == selected_entity_idx) {
                                            selected_entity_id = ents[ci];
                                            Entity se = world->entities[ents[ci]];
                                            CTransform *st = world_get_component(world, se, COMP_TRANSFORM);
                                            if (st) LOG_INFO("Selected entity %u/%u at (%.1f,%.1f,%.1f)",
                                                selected_entity_idx, total,
                                                st->pos[0], st->pos[1], st->pos[2]);
                                        }
                                        si++;
                                    }
                                    c = c->next;
                                }
                            }
                        }
                    }
                }
            }

            if (input_key_pressed(inp, 288) && selected_entity_id > 0) {
                Entity se = world->entities[selected_entity_id];
                world_destroy_entity(world, se);
                LOG_INFO("Deleted entity %u (was %u/%u)", selected_entity_id, selected_entity_idx, selected_entity_count);
                selected_entity_id = 0;
                if (selected_entity_idx > 0) selected_entity_idx--;
                selected_entity_count = selected_entity_count > 0 ? selected_entity_count - 1 : 0;
            }

            if (input_key_pressed(inp, (i32)']') && selected_entity_id > 0) {
                if (world->entity_count >= ENTITY_SPAWN_CAP) {
                    LOG_INFO("Entity cap reached (%u/%u)", world->entity_count, ENTITY_SPAWN_CAP);
                } else {
                Entity se = world->entities[selected_entity_id];
                CTransform *st = world_get_component(world, se, COMP_TRANSFORM);
                CMeshRef   *sm = world_get_component(world, se, COMP_MESH_REF);
                CRigidBody *sr = world_get_component(world, se, COMP_RIGID_BODY);
                Entity ne = world_create_entity(world);
                CTransform *nt = world_add_component(world, ne, COMP_TRANSFORM);
                if (nt && st) { nt->pos[0] = st->pos[0] + 1.5f; nt->pos[1] = st->pos[1]; nt->pos[2] = st->pos[2]; }
                if (sm) { CMeshRef *nm = world_add_component(world, ne, COMP_MESH_REF); if (nm) *nm = *sm; }
                if (sr) {
                    CRigidBody *nr = world_add_component(world, ne, COMP_RIGID_BODY);
                    if (nr) nr->physics_id = physics_body_create(physics, vec3(st->pos[0]+1.5f, st->pos[1], st->pos[2]), vec3(0.5f,0.5f,0.5f), 1.0f, false, (u32)engine.frame_count);
                }
                selected_entity_count++;
                LOG_INFO("Duplicated entity %u -> new %u (])", selected_entity_id, ne.index);
                }
            }

            if (physics_mode == 3) {
                f32 gs = 5.0f * (f32)engine.delta_time;
                if (input_key_down(inp, 261)) custom_gravity.e[0] -= gs;
                if (input_key_down(inp, 262)) custom_gravity.e[0] += gs;
                if (input_key_down(inp, 263)) custom_gravity.e[2] -= gs;
                if (input_key_down(inp, 264)) custom_gravity.e[2] += gs;
                if (input_key_down(inp, 283)) custom_gravity.e[1] += gs;
                if (input_key_down(inp, 284)) custom_gravity.e[1] -= gs;
                for (u32 gi = 0; gi < physics->count; gi++) {
                    if (!physics->bodies[gi].is_static)
                        physics->bodies[gi].acceleration = custom_gravity;
                }
            } else if (selected_entity_id > 0) {
                Entity se = world->entities[selected_entity_id];
                CTransform *st = world_get_component(world, se, COMP_TRANSFORM);
                if (st) {
                    f32 ms = 5.0f * (f32)engine.delta_time;
                    if (input_key_down(inp, 261)) st->pos[0] -= ms;
                    if (input_key_down(inp, 262)) st->pos[0] += ms;
                    if (input_key_down(inp, 263)) st->pos[2] -= ms;
                    if (input_key_down(inp, 264)) st->pos[2] += ms;
                    if (input_key_down(inp, 283)) st->pos[1] += ms;
                    if (input_key_down(inp, 284)) st->pos[1] -= ms;
                }
            }

            if (input_key_pressed(inp, (i32)'9')) {
                physics_mode = (physics_mode + 1) % 4;
                gravity_enabled = (physics_mode == 0);
                velocity_damping = (physics_mode == 2);
                for (u32 gi = 0; gi < physics->count; gi++) {
                    if (!physics->bodies[gi].is_static) {
                        if (physics_mode == 0) physics->bodies[gi].acceleration = vec3(0, -9.81f, 0);
                        else if (physics_mode == 3) physics->bodies[gi].acceleration = custom_gravity;
                        else physics->bodies[gi].acceleration = vec3(0, 0, 0);
                    }
                }
                static const char *gn[] = {"gravity", "zero-g", "damping", "custom gravity"};
                LOG_INFO("Physics mode: %s (%.1f,%.1f,%.1f)", gn[physics_mode], custom_gravity.e[0], custom_gravity.e[1], custom_gravity.e[2]);
            }

            if (instance_count > 0) {
                rhi_buffer_update(render.device, render.instance_buf, instance_data, instance_count * 64);
                rhi_cmd_bind_pipeline(cmd, wireframe_mode && rhi_handle_valid(render.wire_instanced_pipeline) ? render.wire_instanced_pipeline : render.instanced_pipeline);
                rhi_cmd_set_uniform_mat4(cmd, render.inst_loc_view, &view.e[0][0]);
                rhi_cmd_set_uniform_mat4(cmd, render.inst_loc_proj, &proj.e[0][0]);
                rhi_cmd_set_uniform_vec3(cmd, render.inst_loc_light_dir, sun_dir_vec.e[0], sun_dir_vec.e[1], sun_dir_vec.e[2]);
                rhi_cmd_set_uniform_vec3(cmd, render.inst_loc_light_color, sun_color.e[0], sun_color.e[1], sun_color.e[2]);
                rhi_cmd_set_uniform_vec3(cmd, render.inst_loc_ambient, ambient_col.e[0], ambient_col.e[1], ambient_col.e[2]);
                rhi_cmd_set_uniform_vec3(cmd, render.inst_loc_camera_pos,
                    camera.position.e[0], camera.position.e[1], camera.position.e[2]);

                for (u32 i = 0; i < scene.mesh_count; i++) {
                    Mesh *m = &scene.meshes[i];
                    Material *mat = (m->material_idx < scene.material_count) ? &scene.materials[m->material_idx] : NULL;
                    bind_material(cmd, &render, mat, &scene);
                    rhi_cmd_bind_texel_buffers(cmd, render.instance_buf, render.instance_buf);
                    rhi_cmd_bind_vertex_buffer(cmd, m->vertex_buf, 0);
                    if (m->index_count > 0 && rhi_handle_valid(m->index_buf)) {
                        rhi_cmd_bind_index_buffer(cmd, m->index_buf, 0);
                        rhi_cmd_draw_indexed(cmd, m->index_count, instance_count);
                    } else {
                        rhi_cmd_draw(cmd, 3, instance_count);
                    }
                    draw_calls++; tri_count += (m->index_count / 3) * instance_count;
                }
            }
            /* instance_data is persistent — no free here */
        } else if (scene.mesh_count > 0) {
            ComponentType mesh_query_types[] = { COMP_TRANSFORM, COMP_MESH_REF };
            Query *mq = world_query_cached(world, mesh_query_types, 2);
            bool drew_any = false;

            if (mq && mq->match_count > 0) {
                for (u32 mi = 0; mi < mq->match_count; mi++) {
                    Archetype *a = mq->matching[mi];
                    /* Find column indices for direct chunk access */
                    u32 transform_col = UINT32_MAX, meshref_col = UINT32_MAX;
                    for (u32 ki = 0; ki < a->key.count; ki++) {
                        if (a->key.ids[ki] == COMP_TRANSFORM) transform_col = ki;
                        if (a->key.ids[ki] == COMP_MESH_REF)  meshref_col = ki;
                    }
                    if (transform_col == UINT32_MAX || meshref_col == UINT32_MAX) continue;
                    u32 t_off = a->offsets[transform_col];
                    u32 m_off = a->offsets[meshref_col];
                    Chunk *c = a->chunks;
                    while (c) {
                        for (u32 ci = 0; ci < c->count; ci++) {
                            CTransform *et = (CTransform *)((u8 *)c + t_off + ci * sizeof(CTransform));
                            CMeshRef   *em = (CMeshRef *)((u8 *)c + m_off + ci * sizeof(CMeshRef));

                            Vec3 epos2 = {{ et->pos[0], et->pos[1], et->pos[2] }};
                            if (!frustum_test_sphere(&frustum, epos2, 1.0f)) continue;

                            u32 mesh_idx = em->mesh_index;
                            if (mesh_idx >= scene.mesh_count) mesh_idx = 0;
                            Mesh *m = &scene.meshes[mesh_idx];

                            Mat4 model = frame_identity;
                            model.e[3][0] = et->pos[0];
                            model.e[3][1] = et->pos[1];
                            model.e[3][2] = et->pos[2];
                            rhi_cmd_set_uniform_mat4(cmd, render.loc_model, &model.e[0][0]);

                            Material *mat = (m->material_idx < scene.material_count) ? &scene.materials[m->material_idx] : NULL;
                            bind_material(cmd, &render, mat, &scene);

                            rhi_cmd_bind_vertex_buffer(cmd, m->vertex_buf, 0);
                            if (m->index_count > 0 && rhi_handle_valid(m->index_buf)) {
                                rhi_cmd_bind_index_buffer(cmd, m->index_buf, 0);
                                rhi_cmd_draw_indexed(cmd, m->index_count, 1);
                            } else {
                                rhi_cmd_draw(cmd, 3, 1);
                            }
                            draw_calls++; tri_count += m->index_count > 0 ? m->index_count / 3 : 1;
                            drew_any = true;
                        }
                        c = c->next;
                    }
                }
            }
            /* cached query — no query_done() needed */

            if (selected_entity_count > 0 && selected_entity_id > 0 && scene.mesh_count > 0) {
                Entity se = world->entities[selected_entity_id];
                CTransform *st = world_get_component(world, se, COMP_TRANSFORM);
                CMeshRef   *sm = world_get_component(world, se, COMP_MESH_REF);
                if (st && sm) {
                    u32 mesh_idx = sm->mesh_index;
                    if (mesh_idx >= scene.mesh_count) mesh_idx = 0;
                    Mesh *m = &scene.meshes[mesh_idx];
                    Mat4 model = frame_identity;
                    model.e[3][0] = st->pos[0];
                    model.e[3][1] = st->pos[1];
                    model.e[3][2] = st->pos[2];
                    if (wireframe_mode && rhi_handle_valid(render.wire_pipeline)) {
                        rhi_cmd_bind_pipeline(cmd, render.wire_pipeline);
                    }
                    rhi_cmd_set_uniform_mat4(cmd, render.loc_model, &model.e[0][0]);
                    {
                        static const Vec3 hl_colors[] = {
                            {.e={1.0f,1.0f,0.0f}}, {.e={1.0f,0.3f,0.3f}}, {.e={0.3f,1.0f,0.3f}},
                            {.e={0.3f,0.8f,1.0f}}, {.e={1.0f,0.5f,1.0f}}, {.e={1.0f,0.6f,0.2f}},
                            {.e={0.5f,0.5f,1.0f}}, {.e={0.2f,1.0f,0.8f}}
                        };
                        u32 ci = selected_entity_idx % 8;
                        Vec3 hc = hl_colors[ci];
                        rhi_cmd_set_uniform_vec3(cmd, render.loc_albedo, hc.e[0], hc.e[1], hc.e[2]);
                    }
                    rhi_cmd_bind_vertex_buffer(cmd, m->vertex_buf, 0);
                    if (m->index_count > 0 && rhi_handle_valid(m->index_buf)) {
                        rhi_cmd_bind_index_buffer(cmd, m->index_buf, 0);
                        rhi_cmd_draw_indexed(cmd, m->index_count, 1);
                    } else {
                        rhi_cmd_draw(cmd, 3, 1);
                    }
                    draw_calls++;
                }
            }

            if (!drew_any && scene.node_count > 0) {
                scene_compute_world_transforms(&scene);

                if (mega_buf.valid && gpu_indirect_enabled && mega_buf.mat_group_count > 0) {
                    rhi_cmd_set_uniform_mat4(cmd, render.loc_model, &frame_identity.e[0][0]);
                    rhi_cmd_bind_vertex_buffer(cmd, mega_buf.vbo, 0);
                    rhi_cmd_bind_index_buffer(cmd, mega_buf.ibo, 0);

                    if (mega_use_unified_vis(false) &&
                        mega_unified_vis_flags(&gpucull_sys, cmd, &curr_view_proj.e[0][0],
                                               mega_buf.draw_cmd_count, &occ_sys, g_draw_vis)) {
                        u32 mc = mega_mat_groups_draw(cmd, &render, &scene,
                                                      &mega_buf, g_draw_vis);
                        draw_calls += mc;
                        draw_bench_add(mc, draw_bench_enabled ? mega_count_visible_draws(&mega_buf, g_draw_vis) : 0u);
                        draw_bench_mark_unified();
                    } else {
                    /* Pre-compute per-node visibility (frustum + LOD) — parallel */
                    {
                        u32 nc = scene.node_count < 16384 ? scene.node_count : 16384;
                        memset(g_node_vis, 0, nc);
                        u32 wc = task_worker_count(tasks);
                        if (wc < 1) wc = 1;
                        u32 chunk = (nc + wc - 1) / wc;
                        static VisTaskCtx vctxs[8];
                        for (u32 wi = 0; wi < wc; wi++) {
                            vctxs[wi].node_vis = g_node_vis;
                            vctxs[wi].spheres  = mega_buf.node_spheres;
                            vctxs[wi].start    = wi * chunk;
                            vctxs[wi].end      = (wi + 1) * chunk;
                            if (vctxs[wi].end > nc) vctxs[wi].end = nc;
                            vctxs[wi].frustum  = frustum;
                            vctxs[wi].cam_pos  = camera.position;
                            vctxs[wi].lod      = &lod_sys;
                            task_submit(tasks, vis_task_fn, &vctxs[wi]);
                        }
                        task_wait(tasks);
                    }

                    /* R76-3: Batch all compacts before a single barrier — reduces G barriers to 1. */
                    for (u32 g = 0; g < mega_buf.mat_group_count; g++) {
                        u32 gcount = mega_buf.mat_systems[g].current_draw_count;
                        memset(g_vis_flags, 0, gcount * sizeof(u32));
                        /* R75-2: Use pre-built inverse index — O(N) total, not O(N×G). */
                        u32 start = mega_buf.group_cmd_offsets[g];
                        u32 end   = mega_buf.group_cmd_offsets[g + 1];
                        for (u32 gi = 0; gi < end - start; gi++) {
                            u32 ci = mega_buf.group_cmd_list[start + gi];
                            u32 ni = mega_buf.cmd_node_index[ci];
                            g_vis_flags[gi] = g_node_vis[ni];
                            if (!node_occ_visible(ni)) g_vis_flags[gi] = 0;
                        }
                        indirect_draw_upload_visibility(&mega_buf.mat_systems[g], render.device, g_vis_flags, gcount);
                        indirect_draw_compact_no_barrier(&mega_buf.mat_systems[g], render.device, cmd);
                    }
                    rhi_cmd_memory_barrier(cmd);
                    for (u32 g = 0; g < mega_buf.mat_group_count; g++) {
                        u32 mat_idx = mega_buf.mat_indices[g];
                        Material *mat = (mat_idx < scene.material_count) ? &scene.materials[mat_idx] : NULL;
                        bind_material(cmd, &render, mat, &scene);
                        indirect_draw_execute(&mega_buf.mat_systems[g], render.device);
                        draw_calls++;
                    }
                    draw_bench_add(mega_buf.mat_group_count,
                                   draw_bench_enabled ? mega_count_visible_node_vis(&mega_buf, g_node_vis) : 0u);
                    draw_bench_mark_legacy();
                    }
                } else {
                /* Batch frustum cull: build world AABBs, cull in one pass */
                u32 cull_node_count = 0;
                u32 *cull_node_map = cull_node_map_buf;
                CullAABB *cull_aabbs = cull_aabbs_buf;
                u32 *cull_visible = cull_visible_buf;

                for (u32 ni = 0; ni < scene.node_count; ni++) {
                    SceneNode *node = &scene.nodes[ni];
                    if (!node->has_mesh || node->skinned) continue;
                    if (node->mesh_index >= scene.mesh_count) continue;
                    /* R152: Prevent cull buffer overflow — CULL_BUF_CAP is 16384.
                     * A scene with more mesh nodes would overflow cull_aabbs/cull_node_map. */
                    if (cull_node_count >= CULL_BUF_CAP) break;

                    Mesh *m = &scene.meshes[node->mesh_index];
                    Vec3 wmin = vec3(1e30f, 1e30f, 1e30f), wmax = vec3(-1e30f, -1e30f, -1e30f);
                    for (int ci = 0; ci < 8; ci++) {
                        f32 lx = (ci & 1) ? m->aabb_max.e[0] : m->aabb_min.e[0];
                        f32 ly = (ci & 2) ? m->aabb_max.e[1] : m->aabb_min.e[1];
                        f32 lz = (ci & 4) ? m->aabb_max.e[2] : m->aabb_min.e[2];
                        f32 wx = node->world_transform.e[0][0]*lx + node->world_transform.e[1][0]*ly + node->world_transform.e[2][0]*lz + node->world_transform.e[3][0];
                        f32 wy = node->world_transform.e[0][1]*lx + node->world_transform.e[1][1]*ly + node->world_transform.e[2][1]*lz + node->world_transform.e[3][1];
                        f32 wz = node->world_transform.e[0][2]*lx + node->world_transform.e[1][2]*ly + node->world_transform.e[2][2]*lz + node->world_transform.e[3][2];
                        if (wx < wmin.e[0]) { wmin.e[0] = wx; } else if (wx > wmax.e[0]) { wmax.e[0] = wx; }
                        if (wy < wmin.e[1]) { wmin.e[1] = wy; } else if (wy > wmax.e[1]) { wmax.e[1] = wy; }
                        if (wz < wmin.e[2]) { wmin.e[2] = wz; } else if (wz > wmax.e[2]) { wmax.e[2] = wz; }
                    }
                    cull_aabbs[cull_node_count].min = wmin;
                    cull_aabbs[cull_node_count].max = wmax;
                    cull_node_map[cull_node_count] = ni;
                    cull_node_count++;
                }

                u32 visible_count = frustum_cull_batch(&frustum, cull_aabbs, cull_node_count, cull_visible);
                culled_count += cull_node_count - visible_count;

                /* Render only visible nodes (with LOD distance culling) */
                for (u32 vi = 0; vi < visible_count; vi++) {
                    u32 ni = cull_node_map[cull_visible[vi]];
                    if (!node_occ_visible(ni)) {
                        culled_count++;
                        continue;
                    }
                    SceneNode *node = &scene.nodes[ni];
                    Mesh *m = &scene.meshes[node->mesh_index];

                    /* LOD distance culling: skip objects beyond 2x the LOD threshold */
                    if (lod_sys.count > 0 && ni < LOD_MAX_GROUPS) {
                        Vec3 obj_center = {{ node->world_transform.e[3][0],
                                            node->world_transform.e[3][1],
                                            node->world_transform.e[3][2] }};
                        u32 lod_level = lod_select(&lod_sys, ni, obj_center, camera.position, camera.fov);
                        u32 grp_idx = lod_sys.entity_to_group[ni];
                        f32 cull_dist = lod_sys.groups[grp_idx].thresholds[0] * 2.0f;
                        f32 dx = obj_center.e[0] - camera.position.e[0];
                        f32 dy = obj_center.e[1] - camera.position.e[1];
                        f32 dz = obj_center.e[2] - camera.position.e[2];
                        if (dx*dx + dy*dy + dz*dz > cull_dist * cull_dist) {
                            culled_count++;
                            continue;
                        }
                        (void)lod_level;
                    }

                    rhi_cmd_set_uniform_mat4(cmd, render.loc_model, &node->world_transform.e[0][0]);

                    Material *mat = (m->material_idx < scene.material_count) ? &scene.materials[m->material_idx] : NULL;
                    bind_material(cmd, &render, mat, &scene);

                    rhi_cmd_bind_vertex_buffer(cmd, m->vertex_buf, 0);
                    if (m->index_count > 0 && rhi_handle_valid(m->index_buf)) {
                        rhi_cmd_bind_index_buffer(cmd, m->index_buf, 0);
                        rhi_cmd_draw_indexed(cmd, m->index_count, 1);
                    } else {
                        rhi_cmd_draw(cmd, 3, 1);
                    }
                    draw_calls++; tri_count += m->index_count > 0 ? m->index_count / 3 : 1;
                }

                /* cull buffers are persistent — no free needed */
                }
            } else if (!drew_any) {
                for (u32 i = 0; i < scene.mesh_count; i++) {
                    Mesh *m = &scene.meshes[i];
                    rhi_cmd_set_uniform_mat4(cmd, render.loc_model, &frame_identity.e[0][0]);

                    Material *mat = (m->material_idx < scene.material_count) ? &scene.materials[m->material_idx] : NULL;
                    bind_material(cmd, &render, mat, &scene);

                    rhi_cmd_bind_vertex_buffer(cmd, m->vertex_buf, 0);
                    if (m->index_count > 0 && rhi_handle_valid(m->index_buf)) {
                        rhi_cmd_bind_index_buffer(cmd, m->index_buf, 0);
                        rhi_cmd_draw_indexed(cmd, m->index_count, 1);
                    } else {
                        rhi_cmd_draw(cmd, 3, 1);
                    }
                    draw_calls++; tri_count += m->index_count > 0 ? m->index_count / 3 : 1;
            }
        }

        if (gravity_well) {
            for (u32 gi = 0; gi < physics->count; gi++) {
                if (physics->bodies[gi].is_static) continue;
                Vec3 gp = physics->bodies[gi].position;
                Vec3 gd = vec3_sub(camera.position, gp);
                /* R51: fast_rsqrt replaces sqrtf + division in gravity loop. */
                f32 gd2 = gd.e[0]*gd.e[0] + gd.e[1]*gd.e[1] + gd.e[2]*gd.e[2];
                if (gd2 < 0.25f) continue;  /* 0.5^2 */
                f32 inv_gdist = fast_rsqrt(gd2);
                f32 gdist = gd2 * inv_gdist;
                f32 gforce = 20.0f / (1.0f + gdist);
                f32 scale = inv_gdist * gforce * (f32)engine.delta_time;
                physics->bodies[gi].velocity.e[0] += gd.e[0] * scale;
                physics->bodies[gi].velocity.e[1] += gd.e[1] * scale;
                physics->bodies[gi].velocity.e[2] += gd.e[2] * scale;
            }
        }
         }
        } /* end forward path guard */

        /* R53-fix: Compute inv(VP) = inv(V) * inv(P) analytically.
         * (AB)^{-1} = B^{-1}A^{-1}, so (V*P)^{-1} = P^{-1}*V^{-1}.
         * But in engine's row-major convention mat4_mul(P,V) = P*V,
         * and (P*V)^{-1} = V^{-1}*P^{-1} → mat4_mul(iv, frame_inv_proj).
         * frame_inv_proj already includes TAA jitter / screen shake (R47+R53-fix above).
         * inv(V) uses cached trig + adjusted eye for third-person.
         * Falls back to generic inverse for top-down (completely different view matrix). */
        Mat4 frame_inv_vp;
        if (top_down_view) {
            frame_inv_vp = mat4_inverse(curr_view_proj);
        } else {
            f32 tp = third_person ? third_person_dist : 0.0f;
            /* R60-fix: Use camera_inv_view + adjust eye for third-person offset.
             * camera_inv_view gives [R^T | eye]; subtract fwd*tp for third-person. */
            Mat4 iv = camera_inv_view(&camera);
            if (third_person) {
                iv.e[0][3] -= cam_fwd.e[0] * tp;
                iv.e[1][3] -= cam_fwd.e[1] * tp;
                iv.e[2][3] -= cam_fwd.e[2] * tp;
            }
            frame_inv_vp = mat4_mul(iv, frame_inv_proj);
        }

        /* ---- Deferred rendering path (RenderPath branch) ----
         * When active, runs G-Buffer geometry pass + deferred lighting
         * instead of the forward scene pass. */
        if (render.render_path == RENDER_PATH_DEFERRED && render.deferred.initialized) {
            DeferredSystem *dsys = &render.deferred;

            /* G-Buffer pass: render scene geometry into MRT attachments. */
            deferred_begin_gbuffer(dsys, render.device, cmd);

            /* Upload view/proj once per frame using cached locations. */
            if (dsys->_loc_gbuf_view >= 0)
                rhi_cmd_set_uniform_mat4(cmd, dsys->_loc_gbuf_view, &view.e[0][0]);
            if (dsys->_loc_gbuf_proj >= 0)
                rhi_cmd_set_uniform_mat4(cmd, dsys->_loc_gbuf_proj, &proj.e[0][0]);
            if (dsys->_loc_gbuf_prev_vp >= 0)
                rhi_cmd_set_uniform_mat4(cmd, dsys->_loc_gbuf_prev_vp, &prev_view_proj.e[0][0]);

            /* Render terrain. */
            if (rhi_handle_valid(terrain.vbo)) {
                bind_material(cmd, &render, NULL, &scene);
                if (dsys->_loc_gbuf_model >= 0)
                    rhi_cmd_set_uniform_mat4(cmd, dsys->_loc_gbuf_model, &frame_identity.e[0][0]);
                rhi_cmd_bind_vertex_buffer(cmd, terrain.vbo, 0);
                rhi_cmd_bind_index_buffer(cmd, terrain.ibo, 0);
                rhi_cmd_draw_indexed(cmd, terrain.index_count, 1);
            }

            /* Render scene nodes (cached model location, no per-object hash lookup). */
            if (mega_buf.valid && gpu_indirect_enabled && mega_buf.mat_group_count > 0) {
                /* Per-material batched indirect draw: one draw call per material group */
                rhi_cmd_bind_vertex_buffer(cmd, mega_buf.vbo, 0);
                rhi_cmd_bind_index_buffer(cmd, mega_buf.ibo, 0);
                if (dsys->_loc_gbuf_model >= 0)
                    rhi_cmd_set_uniform_mat4(cmd, dsys->_loc_gbuf_model, &frame_identity.e[0][0]);

                /* Pre-compute per-node visibility using camera frustum + LOD — parallel */
                if (mega_use_unified_vis(true) &&
                    mega_unified_vis_flags(&gpucull_sys, cmd, &curr_view_proj.e[0][0],
                                           mega_buf.draw_cmd_count, &occ_sys, g_draw_vis)) {
                    u32 mc = mega_mat_groups_draw(cmd, &render, &scene,
                                                  &mega_buf, g_draw_vis);
                    draw_calls += mc;
                    draw_bench_add(mc, draw_bench_enabled ? mega_count_visible_draws(&mega_buf, g_draw_vis) : 0u);
                    draw_bench_mark_unified();
                } else {
                {
                    u32 nc = scene.node_count < 16384 ? scene.node_count : 16384;
                    memset(g_node_vis, 0, nc);
                    Frustum gbuf_frustum = frame_frustum;
                    u32 wc = task_worker_count(tasks);
                    if (wc < 1) wc = 1;
                    u32 chunk = (nc + wc - 1) / wc;
                    static VisTaskCtx vctxs[8];
                    for (u32 wi = 0; wi < wc; wi++) {
                        vctxs[wi].node_vis = g_node_vis;
                        vctxs[wi].spheres  = mega_buf.node_spheres;
                        vctxs[wi].start    = wi * chunk;
                        vctxs[wi].end      = (wi + 1) * chunk;
                        if (vctxs[wi].end > nc) vctxs[wi].end = nc;
                        vctxs[wi].frustum  = gbuf_frustum;
                        vctxs[wi].cam_pos  = camera.position;
                        vctxs[wi].lod      = &lod_sys;
                        task_submit(tasks, vis_task_fn, &vctxs[wi]);
                    }
                    task_wait(tasks);
                }

                /* R76-3: Batch all compacts before a single barrier — reduces G barriers to 1. */
                for (u32 g = 0; g < mega_buf.mat_group_count; g++) {
                    /* Build visibility for this material group's draw cmds */
                    u32 gcount = mega_buf.mat_systems[g].current_draw_count;
                    memset(g_vis_flags, 0, gcount * sizeof(u32));
                    /* R75-2: Use pre-built inverse index — O(N) total, not O(N×G). */
                    u32 start = mega_buf.group_cmd_offsets[g];
                    u32 end   = mega_buf.group_cmd_offsets[g + 1];
                    for (u32 gi = 0; gi < end - start; gi++) {
                        u32 ci = mega_buf.group_cmd_list[start + gi];
                        u32 ni = mega_buf.cmd_node_index[ci];
                        g_vis_flags[gi] = g_node_vis[ni];
                        if (!node_occ_visible(ni)) g_vis_flags[gi] = 0;
                    }
                    indirect_draw_upload_visibility(&mega_buf.mat_systems[g], render.device, g_vis_flags, gcount);
                    indirect_draw_compact_no_barrier(&mega_buf.mat_systems[g], render.device, cmd);
                }
                rhi_cmd_memory_barrier(cmd);
                for (u32 g = 0; g < mega_buf.mat_group_count; g++) {
                    u32 mat_idx = mega_buf.mat_indices[g];
                    Material *mat = (mat_idx < scene.material_count) ? &scene.materials[mat_idx] : NULL;
                    bind_material(cmd, &render, mat, &scene);
                    indirect_draw_execute(&mega_buf.mat_systems[g], render.device);
                    draw_calls++;
                }
                draw_bench_add(mega_buf.mat_group_count,
                               draw_bench_enabled ? mega_count_visible_node_vis(&mega_buf, g_node_vis) : 0u);
                draw_bench_mark_legacy();
                }
            } else {
            for (u32 ni = 0; ni < scene.node_count; ni++) {
                SceneNode *node = &scene.nodes[ni];
                if (!node->has_mesh) continue;
                if (node->mesh_index >= scene.mesh_count) continue;
                Mesh *m = &scene.meshes[node->mesh_index];
                Material *mat = (node->material_idx < scene.material_count) ? &scene.materials[node->material_idx] : NULL;
                bind_material(cmd, &render, mat, &scene);
                if (dsys->_loc_gbuf_model >= 0)
                    rhi_cmd_set_uniform_mat4(cmd, dsys->_loc_gbuf_model, &node->world_transform.e[0][0]);
                rhi_cmd_bind_vertex_buffer(cmd, m->vertex_buf, 0);
                if (m->index_count > 0 && rhi_handle_valid(m->index_buf)) {
                    rhi_cmd_bind_index_buffer(cmd, m->index_buf, 0);
                    rhi_cmd_draw_indexed(cmd, m->index_count, 1);
                } else {
                    rhi_cmd_draw(cmd, 3, 1);
                }
            }
            }

            deferred_end_gbuffer(dsys, render.device, cmd);

            /* Deferred lighting pass: bind scene_fbo so output feeds post-processing. */
            if (rhi_handle_valid(scene_fbo.fb)) {
                rhi_offscreen_fbo_bind(cmd, &scene_fbo);
            }

            /* Camera data: [0..15] = inv_vp, [16..18] = camera_pos */
            f32 cam_uniform[25];
            memcpy(cam_uniform, &frame_inv_vp.e[0][0], 16 * sizeof(f32));
            cam_uniform[16] = camera.position.e[0];
            cam_uniform[17] = camera.position.e[1];
            cam_uniform[18] = camera.position.e[2];

            RHITexture shadow_tex = render.shadow_map.depth_tex;

            /* Cluster lights + cascade matrices for deferred lighting. */
            light_system_set_point_shadow_indices(&lights, &pt_shadows);
            if (lights.gpu_cull) {
                light_system_upload_lights(&lights);
                light_system_cull_gpu(&lights, cmd, &curr_view_proj.e[0][0], rw, rh);
            } else {
                light_system_cull(&lights, &view, &proj, rw, rh);
                light_system_upload(&lights);
            }

            deferred_lighting_pass(dsys, render.device, cmd,
                                   lights.light_data_buf, lights.light_grid_buf,
                                   lights.point_count, lights.dir_count,
                                   shadow_tex,
                                   render.ibl.brdf_lut,
                                   render.ibl.irradiance_map,
                                   render.ibl.prefilter_map,
                                   g_psc.count, g_psc.count > 0u ? g_psc.tex : NULL, g_psc.far_planes,
                                   0.1f, 100.0f, shadow_bias,
                                   &view.e[0][0], cam_uniform);
        }

        profiler_pop();
        rhi_gpu_timer_end(gpu_forward_timer);
        rhi_gpu_timer_end(gpu_scene_timer);
        if (draw_bench_enabled) {
            f64 mega_gpu = rhi_gpu_timer_elapsed_ms(gpu_shadow_timer) +
                           rhi_gpu_timer_elapsed_ms(gpu_forward_timer) +
                           rhi_gpu_timer_elapsed_ms(gpu_scene_timer);
            draw_bench_sample_gpu(mega_gpu);
            draw_bench_record_frame((u32)engine.frame_count, mega_gpu);
        }

        /* GPU Occlusion Culling: generate Hi-Z pyramid from depth buffer,
         * then dispatch compute to determine per-object visibility.
         * Results are consumed next frame (pipelined readback). */
        if (occ_cull_enabled && occ_sys.enabled && rhi_handle_valid(scene_fbo.depth_tex)) {
            occlusion_cull_generate_hi_z(&occ_sys, cmd, scene_fbo.depth_tex);

            /* R82-2/R83-4: AABBs cached+uploaded at init — per-frame dispatch only.
             * R101: When all rendering paths use unified cull (mega-buffer valid +
             * unified forward enabled), the occlusion_cull_dispatch results are never
             * consumed — node_occ_visible() is not called because the CPU fallback
             * path is skipped.  Skip the dispatch to save 1 compute pass + barrier +
             * buffer copy per frame.  Hi-Z generation above still runs (unified_cull
             * samples it).  When unified is disabled or mega-buffer invalid, the CPU
             * fallback path needs occlusion results, so dispatch as before. */
            bool unified_all_active = mega_buf.valid && unified_forward_enabled;
            if (g_occ_aabbs_count > 0 && !unified_all_active) {
                occlusion_cull_dispatch(&occ_sys, cmd, &curr_view_proj, g_occ_aabbs_count);
            }
        }

        /* Transition the scene depth to a shader-readable layout once, before any
         * post-fx samples it (SSAO, volumetric, contact shadows, SSR/SSGI, DoF,
         * god rays, ...). The occlusion path already did this via Hi-Z above; do
         * it here otherwise so depth reads are correct regardless of which
         * effects are enabled (previously this relied on SSAO running). */
        bool occ_did_depth_read = occ_cull_enabled && occ_sys.enabled &&
                                  rhi_handle_valid(scene_fbo.depth_tex);
        if (!occ_did_depth_read && rhi_handle_valid(scene_fbo.depth_tex)) {
            rhi_cmd_transition_depth_to_read(cmd, scene_fbo.depth_tex);
        }

        profiler_push("postfx");
        rhi_gpu_timer_begin(gpu_postfx_timer);

        if (rhi_handle_valid(scene_fbo.fb) && ssao.ready && ssao.radius > 0.0f) {
            ssao_apply(&ssao, cmd, scene_fbo.depth_tex,
                       &proj.e[0][0], &frame_inv_proj.e[0][0], rw, rh);
            render.ssao_tex = ssao_get_texture(&ssao);
        }

        if (contact_shadow.ready && rhi_handle_valid(scene_fbo.fb) && cs_enabled) {
            contact_shadow_apply(&contact_shadow, cmd, scene_fbo.depth_tex,
                                 &frame_inv_proj.e[0][0], sun_dir_vec.e[0], sun_dir_vec.e[1], sun_dir_vec.e[2], rw, rh);
        }

        if (rhi_handle_valid(scene_fbo.fb) && vol.ready && vol_enabled) {
            f32 light_dir[] = { sun_dir_vec.e[0], sun_dir_vec.e[1], sun_dir_vec.e[2] };
            f32 light_color[] = { sun_color.e[0], sun_color.e[1], sun_color.e[2] };
            volumetric_apply(&vol, cmd, scene_fbo.depth_tex, render.shadow_map.depth_tex,
                             &frame_inv_proj.e[0][0], &view.e[0][0], light_dir, light_color, rw, rh);
        }

        if (lens_flare.ready && rhi_handle_valid(scene_fbo.fb) && lf_enabled) {
            f32 ld[] = { sun_dir_vec.e[0], sun_dir_vec.e[1], sun_dir_vec.e[2] };
            lens_flare_apply(&lens_flare, cmd, scene_fbo.depth_tex,
                             &view.e[0][0], &proj.e[0][0], ld,
                             sun_color.e[0], sun_color.e[1], sun_color.e[2], rw, rh);
        }

        if (rhi_handle_valid(scene_fbo.fb) && ssr_sys.ready && ssr_enabled) {
            ssr_apply(&ssr_sys, cmd, scene_fbo.color_tex, scene_fbo.depth_tex,
                      &proj.e[0][0], &frame_inv_proj.e[0][0], &view.e[0][0], rw, rh);
        }

        if (ssgi_sys.ready && rhi_handle_valid(scene_fbo.fb) && ssgi_enabled) {
            ssgi_apply(&ssgi_sys, cmd, scene_fbo.depth_tex, scene_fbo.color_tex,
                       &frame_inv_proj.e[0][0], &proj.e[0][0], rw, rh);
        }

        RHITexture taa_output = scene_fbo.color_tex;
        RHITexture taa_velocity = RHI_HANDLE_NULL;
        if (render.render_path == RENDER_PATH_DEFERRED && render.deferred.initialized &&
            rhi_handle_valid(render.deferred.gbuf_velocity)) {
            taa_velocity = render.deferred.gbuf_velocity;
        } else if (forward_vel_enabled && forward_vel.ready &&
                   rhi_handle_valid(forward_velocity_get_texture(&forward_vel))) {
            taa_velocity = forward_velocity_get_texture(&forward_vel);
        }
        if (forward_vel_enabled && forward_vel.ready &&
            render.render_path != RENDER_PATH_DEFERRED &&
            rhi_handle_valid(scene_fbo.depth_tex) && taa_enabled) {
            forward_velocity_apply(&forward_vel, cmd, scene_fbo.depth_tex,
                                   &frame_inv_proj.e[0][0], &curr_view_proj.e[0][0],
                                   &prev_view_proj.e[0][0], rw, rh);
            if (!rhi_handle_valid(render.deferred.gbuf_velocity))
                taa_velocity = forward_velocity_get_texture(&forward_vel);
        }
        if (rhi_handle_valid(scene_fbo.fb) && taa_enabled && fxaa_enabled &&
            combined_aa.ready && combined_aa.use_combined) {
            combined_aa_apply(&combined_aa, cmd, scene_fbo.color_tex, scene_fbo.depth_tex,
                               taa_velocity, &curr_view_proj.e[0][0], &prev_view_proj.e[0][0],
                               &frame_inv_vp.e[0][0], rw, rh);
            taa_output = combined_aa_get_output(&combined_aa);
        } else {
            if (rhi_handle_valid(scene_fbo.fb) && taa.ready && taa_enabled) {
                taa_resolve(&taa, cmd, scene_fbo.color_tex, scene_fbo.depth_tex, taa_velocity,
                            &curr_view_proj.e[0][0], &prev_view_proj.e[0][0],
                            &frame_inv_vp.e[0][0], rw, rh);
                taa_output = taa_get_output(&taa);
            }

            if (fxaa_enabled && fxaa_sys.ready && rhi_handle_valid(scene_fbo.fb)) {
                fxaa_apply(&fxaa_sys, cmd, taa_output, rw, rh);
                taa_output = fxaa_get_texture(&fxaa_sys);
            }
        }

        if (sharpen_sys.ready && rhi_handle_valid(scene_fbo.fb) && sharpen_enabled) {
            sharpen_apply(&sharpen_sys, cmd, taa_output, 0.35f, rw, rh);
            taa_output = sharpen_sys.fbo.color_tex;
        }

        if (motion_blur.ready && rhi_handle_valid(scene_fbo.fb) && mb_enabled) {
            motion_blur_apply(&motion_blur, cmd, taa_output, scene_fbo.depth_tex,
                              &frame_inv_proj.e[0][0], &prev_view_proj.e[0][0],
                              1.0f, rw, rh);
            taa_output = motion_blur.fbo.color_tex;
        }

        RHITexture post_input = taa_output;
        if (rhi_handle_valid(scene_fbo.fb) && dof_sys.ready && dof_enabled) {
            dof_apply(&dof_sys, cmd, taa_output, scene_fbo.depth_tex,
                      &frame_inv_proj.e[0][0], rw, rh);
            post_input = dof_get_texture(&dof_sys);
        }

        if (sss_sys.ready && rhi_handle_valid(scene_fbo.fb) && sss_enabled) {
            sss_apply(&sss_sys, cmd, post_input, scene_fbo.depth_tex,
                      0.5f, 0.1f, rw, rh);
            post_input = sss_sys.fbo.color_tex;
        }

        if (rhi_handle_valid(scene_fbo.fb) && postfx.ready) {
            post_process_apply(&postfx, cmd, post_input, rw, rh);
            if (rhi_handle_valid(postfx.fbo_composite.fb))
                post_input = postfx.fbo_composite.color_tex;
        }

        RHITexture tonemap_input = post_input;
        bool used_combined_color = false;
        f32 cine_ab = (cine_enabled && cine_sys.ready) ? cine_sys.aberration : 0.0f;
        f32 cine_vig = (cine_enabled && cine_sys.ready) ? cine_sys.vignette : 0.0f;
        f32 cine_gr  = (cine_enabled && cine_sys.ready) ? cine_sys.grain : 0.0f;
        if (tonemap.ready && rhi_handle_valid(scene_fbo.fb)) {
            tonemap_update_auto_exposure(&tonemap, cmd, post_input, rw, rh, (f32)engine.delta_time);
        }
        if (combined_color.ready && combined_color.use_combined && cg_enabled &&
            rhi_handle_valid(scene_fbo.fb)) {
            combined_color_apply(&combined_color, cmd, post_input,
                                 tonemap.exposure, tonemap.gamma, tonemap.mode,
                                 cg_saturation, cg_contrast, cg_brightness,
                                 cg_temperature, cg_tint,
                                 cine_ab, cine_vig, cine_gr,
                                 (f32)total_time, rw, rh);
            tonemap_input = combined_color_get_output(&combined_color);
            used_combined_color = true;
        } else {
            if (tonemap.ready && rhi_handle_valid(scene_fbo.fb)) {
                rhi_offscreen_fbo_bind(cmd, &scene_fbo);
                tonemap_apply(&tonemap, cmd, post_input, rw, rh);
                tonemap_input = scene_fbo.color_tex;
            }

            if (cg_sys.ready && cg_enabled) {
                InputState *cg_inp = platform_input(engine.platform);
                if (input_key_pressed(cg_inp, 263)) cg_saturation = fminf(cg_saturation + 0.05f, 2.0f);
                if (input_key_pressed(cg_inp, 264)) cg_saturation = fmaxf(cg_saturation - 0.05f, 0.0f);
                if (input_key_pressed(cg_inp, 262)) cg_contrast = fminf(cg_contrast + 0.05f, 2.0f);
                if (input_key_pressed(cg_inp, 261)) cg_contrast = fmaxf(cg_contrast - 0.05f, 0.5f);
                color_grade_apply(&cg_sys, cmd, tonemap_input,
                                  cg_saturation, cg_contrast, cg_brightness, cg_temperature, cg_tint, rw, rh);
                tonemap_input = cg_sys.fbo.color_tex;
            }
        }

        /* Cinematic post-process when combined color path did not already apply it. */
        if (cine_sys.ready && cine_enabled && !used_combined_color) {
            rhi_offscreen_fbo_bind(cmd, &scene_fbo);
            cinematic_apply(&cine_sys, cmd, tonemap_input, rw, rh, (f32)total_time);
            tonemap_input = scene_fbo.color_tex;
        }

        /* tonemap / cinematic above re-bind scene_fbo, whose render pass leaves
         * its depth in the attachment layout again; god rays and debug viz below
         * sample scene_fbo.depth_tex, so re-make it shader-readable (idempotent:
         * no-op on VK if it was never reverted, no-op entirely on GL). */
        if (rhi_handle_valid(scene_fbo.depth_tex))
            rhi_cmd_transition_depth_to_read(cmd, scene_fbo.depth_tex);

        if (gr_sys.ready) {
            Vec3 sun_dir = sun_dir_vec;
            Vec3 sun_world = vec3_scale(sun_dir, -100.0f);
            Mat4 vp = curr_view_proj;
            f32 sx = vp.e[0][0]*sun_world.e[0] + vp.e[1][0]*sun_world.e[1] + vp.e[2][0]*sun_world.e[2] + vp.e[3][0];
            f32 sy = vp.e[0][1]*sun_world.e[0] + vp.e[1][1]*sun_world.e[1] + vp.e[2][1]*sun_world.e[2] + vp.e[3][1];
            f32 sw = vp.e[0][3]*sun_world.e[0] + vp.e[1][3]*sun_world.e[1] + vp.e[2][3]*sun_world.e[2] + vp.e[3][3];
            f32 sun_sx = (sx / sw) * 0.5f + 0.5f;
            f32 sun_sy = (sy / sw) * 0.5f + 0.5f;
            if (sw > 0.0f && sun_sx > -0.5f && sun_sx < 1.5f && sun_sy > -0.5f && sun_sy < 1.5f) {
                god_rays_apply(&gr_sys, cmd, tonemap_input, scene_fbo.depth_tex,
                               sun_sx, sun_sy, god_rays_intensity, rw, rh);
                tonemap_input = gr_sys.fbo.color_tex;
            }
        }

        if (debug_viz_mode > 0 && debug_viz.ready) {
            RHITexture viz_input = tonemap_input;
            if (debug_viz_mode == 3 && ssao.ready)
                viz_input = ssao.blur_fbo.color_tex;
            debug_viz_apply(&debug_viz, cmd, viz_input, scene_fbo.depth_tex,
                            debug_viz_mode, camera.near_plane, camera.far_plane,
                            render.cascade_splits, rw, rh);
            tonemap_input = debug_viz.fbo.color_tex;
        }

        if (lens_fx.ready && debug_viz_mode == 0 && lensfx_enabled) {
            lens_effects_apply(&lens_fx, cmd, tonemap_input,
                               lens_ca, lens_vignette, 0.2f, lens_grain, rw, rh);
            tonemap_input = lens_fx.fbo.color_tex;
        }

        if (inspector_mode > 0) {
            RHITexture insp_tex = scene_fbo.color_tex;
            switch (inspector_mode) {
            case 1: insp_tex = scene_fbo.color_tex; break;
            case 2: insp_tex = scene_fbo.depth_tex; break;
            case 3: insp_tex = rhi_handle_valid(ssao.ssao_fbo.fb) ? ssao.ssao_fbo.color_tex : scene_fbo.color_tex; break;
            case 4: insp_tex = rhi_handle_valid(ssao.blur_fbo.fb) ? ssao.blur_fbo.color_tex : scene_fbo.color_tex; break;
            case 5: insp_tex = taa_enabled && taa.ready ? taa_get_output(&taa) : scene_fbo.color_tex; break;
            case 6: insp_tex = fxaa_sys.ready ? fxaa_get_texture(&fxaa_sys) : scene_fbo.color_tex; break;
            case 7: insp_tex = dof_sys.ready ? dof_get_texture(&dof_sys) : scene_fbo.color_tex; break;
            case 8: insp_tex = post_process_get_bloom_texture(&postfx); break;
            case 9: insp_tex = rhi_handle_valid(gr_sys.fbo.fb) ? gr_sys.fbo.color_tex : scene_fbo.color_tex; break;
            case 10: insp_tex = sharpen_sys.ready ? sharpen_sys.fbo.color_tex : scene_fbo.color_tex; break;
            }
            rhi_offscreen_fbo_unbind(cmd, w, h);
            rhi_cmd_bind_pipeline(cmd, postfx.tex_pipe);
            rhi_cmd_bind_texture(cmd, insp_tex, postfx.sampler, 0);
            rhi_cmd_draw(cmd, 3, 1);
            debug_ui_render(&ui, cmd, w, h);
            rhi_gpu_timer_end(gpu_postfx_timer);
            rhi_frame_end(render.device);
            rhi_present(render.device);
            prev_view_proj = curr_view_proj;
            taa_frame++;
            total_time += engine.delta_time;
            profiler_pop();
            profiler_pop();
            profiler_push("end_frame");
            profiler_pop();
            continue;
        }

        if (upscale_sys.ready) {
            upscale_apply(&upscale_sys, cmd, tonemap_input, scene_fbo.depth_tex,
                          &frame_inv_proj.e[0][0], &prev_view_proj.e[0][0],
                          0.3f, rw, rh, w, h);
            rhi_offscreen_fbo_unbind(cmd, w, h);
            rhi_cmd_bind_pipeline(cmd, postfx.tex_pipe);
            rhi_cmd_bind_texture(cmd, upscale_sys.fbo.color_tex, postfx.sampler, 0);
            rhi_cmd_draw(cmd, 3, 1);
        } else {
            rhi_offscreen_fbo_unbind(cmd, w, h);
            rhi_cmd_bind_pipeline(cmd, postfx.tex_pipe);
            rhi_cmd_bind_texture(cmd, tonemap_input, postfx.sampler, 0);
            rhi_cmd_draw(cmd, 3, 1);
        }

        debug_ui_render(&ui, cmd, w, h);

        if (imui_font_ready && imui_visible) {
            InputState *imin = platform_input(engine.platform);
            bool mdown = input_key_down(imin, INPUT_MOUSE_LEFT);
            imui_begin(&imui_ctx, (f32)w, (f32)h, imin->mouse_x, imin->mouse_y, mdown);
            imui_panel(&imui_ctx, 16.0f, 96.0f, 260.0f, 8.0f + 5.0f * imui_ctx.row_h);
            imui_label(&imui_ctx, "Settings  (` to close)");
            if (imui_checkbox(&imui_ctx, 1, "VSync", &vsync_on))
                rhi_set_vsync(render.device, vsync_on);
            imui_checkbox(&imui_ctx, 2, "Wireframe", &wireframe_mode);
            imui_slider_float(&imui_ctx, 3, "Sun azimuth", &sun_azimuth, 0.0f, 6.2831853f);
            imui_slider_float(&imui_ctx, 4, "Sun elevation", &sun_elevation, -1.4f, 1.4f);
            imui_end(&imui_ctx, cmd);
        }

        rhi_gpu_timer_end(gpu_postfx_timer);
        rhi_frame_end(render.device);
        rhi_present(render.device);
        prev_view_proj = curr_view_proj;
        taa_frame++;
        total_time += engine.delta_time;
        profiler_pop();
        profiler_pop();

        profiler_push("end_frame");
        profiler_pop();

        profiler_end_frame();
    }

    LOG_INFO("Shutting down...");
    world_destroy(world);
    LOG_INFO("  world done");
    task_system_destroy(tasks);
    free(render_buf); /* single free: instance_data + unified_udc_buf + unified_uobj_buf */
    free(cull_node_map_buf); /* single free: cull_node_map + cull_aabbs + cull_visible */
    LOG_INFO("  tasks done");
    if (audio_stream_id >= 0) {
        audio_stream_shutdown(&audio_stream_mgr);
        remove(audio_stream_path);
        LOG_INFO("  audio stream done");
    }
    audio_system_destroy(audio);
    LOG_INFO("  audio done");
    physics_world_destroy(physics);
    LOG_INFO("  physics done");
    particles_shutdown(&particles);
    LOG_INFO("  particles done");
    light_system_shutdown(&lights);
    point_shadow_destroy(&pt_shadows, render.device);
    LOG_INFO("  lights done");
     post_process_shutdown(&postfx);
      ssao_shutdown(&ssao);
      taa_shutdown(&taa);
      ssr_shutdown(&ssr_sys);
      dof_shutdown(&dof_sys);
      volumetric_shutdown(&vol);
       tonemap_shutdown(&tonemap);
       fxaa_shutdown(&fxaa_sys);
       ssgi_shutdown(&ssgi_sys);
       lens_flare_shutdown(&lens_flare);
       sharpen_shutdown(&sharpen_sys);
        motion_blur_shutdown(&motion_blur);
        contact_shadow_shutdown(&contact_shadow);
        sss_shutdown(&sss_sys);
        upscale_shutdown(&upscale_sys);
        color_grade_shutdown(&cg_sys);
        god_rays_shutdown(&gr_sys);
        debug_viz_shutdown(&debug_viz);
        lens_effects_shutdown(&lens_fx);
        cinematic_shutdown(&cine_sys);
        combined_aa_shutdown(&combined_aa);
        combined_color_shutdown(&combined_color);
        forward_velocity_shutdown(&forward_vel);
        lod_shutdown(&lod_sys);
        occlusion_cull_shutdown(&occ_sys);
        indirect_draw_destroy(&indirect_sys, render.device);
        gpucull_shutdown(&gpucull_sys);
        for (u32 g = 0; g < mega_buf.mat_group_count; g++) {
            indirect_draw_destroy(&mega_buf.mat_systems[g], render.device);
        }
        if (rhi_handle_valid(mega_buf.vbo)) rhi_buffer_destroy(render.device, mega_buf.vbo);
        if (rhi_handle_valid(mega_buf.ibo)) rhi_buffer_destroy(render.device, mega_buf.ibo);
        if (rhi_handle_valid(scene_fbo.fb)) rhi_offscreen_fbo_destroy(render.device, &scene_fbo);
    LOG_INFO("  postfx done");
    terrain_shutdown(&terrain);
    water_shutdown(&water);
    LOG_INFO("  terrain done");
    hotreload_pipeline_shutdown(&hotreload);
    if (hotreload_tex_ready) hotreload_texture_shutdown(&hotreload_tex);
    if (netrep_enabled) {
        if (netrep_peer_dir[0])
            net_replicator_peer_save_dir(&net_rep, netrep_peer_dir);
        else if (netrep_peer_file[0])
            net_replicator_peer_save(&net_rep, netrep_peer_file);
        net_replicator_shutdown(&net_rep);
        net_shutdown();
    }
    LOG_INFO("  hotreload done");
    if (mip_stream_idx >= 0) {
        async_loader_tick(); /* flush any completed streaming callbacks */
        mipmap_stream_shutdown(&mip_stream);
        if (rhi_handle_valid(mip_stream_tex)) rhi_texture_destroy(render.device, mip_stream_tex);
        remove(mip_stream_path);
        LOG_INFO("  mipmap stream done");
    }
    async_loader_shutdown();
    vfs_destroy(vfs);
    LOG_INFO("  async loader done");
    script_engine_shutdown(&script);
    if (lua_ready) lua_script_shutdown(&lua_script);
    LOG_INFO("  script done");
    if (anim_blend_ready) anim_blend_state_destroy(&anim_blend);
    if (imui_font_ready) font_renderer_shutdown(&imui_font);
    debug_ui_shutdown(&ui);
    asset_scene_free(&asset, &scene);
    LOG_INFO("  asset done");
    skybox_shutdown(&skybox);
    LOG_INFO("  skybox done");
    if (getenv("PROFILER_TRACE")) {
        export_profiler_chrome_trace(gpu_shadow_timer, gpu_forward_timer,
                                     gpu_scene_timer, gpu_postfx_timer,
                                     "profile_trace.json");
    } else if (draw_bench_enabled) {
        draw_bench_export_all();
    }
    rhi_gpu_timer_destroy(render.device, gpu_scene_timer);
    rhi_gpu_timer_destroy(render.device, gpu_postfx_timer);
    rhi_gpu_timer_destroy(render.device, gpu_shadow_timer);
    rhi_gpu_timer_destroy(render.device, gpu_forward_timer);
    render_shutdown(&render);
    LOG_INFO("  render done");
    engine_shutdown(&engine);
    LOG_INFO("  engine done");
    return 0;
}
