#include <engine.h>
#include <rhi/rhi.h>
#include <renderer/camera.h>
#include <renderer/cull.h>
#include <renderer/skybox.h>
#include <renderer/particles.h>
#include <renderer/terrain.h>
#include <renderer/lighting.h>
#include <renderer/post_process.h>
#include <renderer/ssao.h>
#include <renderer/taa.h>
#include <renderer/ssr.h>
#include <renderer/dof.h>
#include <renderer/volumetric.h>
#include <renderer/tonemap.h>
#include <renderer/fxaa.h>
#include <renderer/ssgi.h>
#include <renderer/lens_flare.h>
#include <renderer/sharpen.h>
#include <renderer/motion_blur.h>
#include <renderer/contact_shadow.h>
#include <renderer/sss.h>
#include <asset/asset.h>
#include <asset/hotreload.h>
#include <ecs/ecs.h>
#include <physics/physics.h>
#include <physics/character.h>
#include <task/task.h>
#include <audio/audio.h>
#include <ui/debug_ui.h>
#include <script/script.h>
#include <animation/skeleton.h>
#include <core/log.h>
#include <core/profiler.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

enum {
    COMP_TRANSFORM   = 1,
    COMP_RIGID_BODY  = 2,
    COMP_MESH_REF    = 3,
};

typedef struct { f32 pos[3]; } CTransform;
typedef struct { u32 physics_id; } CRigidBody;
typedef struct { u32 mesh_index; } CMeshRef;

static char *file_read_full(const char *path, usize *out_len) {
    FILE *f = fopen(path, "rb");
    if (!f) return NULL;
    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    if (sz < 0) { fclose(f); return NULL; }
    fseek(f, 0, SEEK_SET);
    char *buf = malloc((usize)sz + 1);
    if (!buf) { fclose(f); return NULL; }
    usize read = fread(buf, 1, (usize)sz, f);
    buf[read] = '\0';
    fclose(f);
    if (out_len) *out_len = read;
    return buf;
}

#include <renderer/lighting.h>

typedef struct {
    RHIDevice    *device;
    RHIPipeline   pipeline;
    RHIPipeline   clustered_pipeline;
    RHIPipeline   instanced_pipeline;
    RHIPipeline   skinned_pipeline;
    RHIBuffer     instance_buf;
    RHISampler    sampler;
    RHITexture    fallback_tex;
    RHITexture    fallback_mr;
    RHITexture    fallback_normal;
    RHITexture    fallback_emissive;
    RHITexture    terrain_tex;
    RHIShadowMap  shadow_map;
    RHIShadowMap  cascade_maps[4];
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
    i32 inst_loc_view, inst_loc_proj;
    i32 inst_loc_light_dir, inst_loc_light_color, inst_loc_ambient, inst_loc_camera_pos;
    i32 sk_loc_view, sk_loc_proj;
    i32 sk_loc_light_dir, sk_loc_light_color, sk_loc_ambient, sk_loc_camera_pos;
    RHITexture     ssao_tex;
} RenderState;

static bool render_init(RenderState *rs, Platform *platform) {
    void *window = platform_window_native(platform);
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

    RHIPipelineDesc pdesc = {.vert = vs, .frag = fs, .uses_textures = true};
    rs->pipeline = rhi_pipeline_create(rs->device, &pdesc);
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
            RHIShader cvs = rhi_shader_create(rs->device, cv, cvl, false);
            RHIShader cfs = rhi_shader_create(rs->device, cf, cfl, true);
            free(cv); free(cf);
            if (rhi_handle_valid(cvs) && rhi_handle_valid(cfs)) {
                RHIPipelineDesc cpd = {.vert = cvs, .frag = cfs, .uses_textures = true, .uses_texel_buffer = true, .disable_culling = true};
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
    }

    RHISamplerDesc sdesc = {
        .min_filter = RHI_FILTER_LINEAR,
        .mag_filter = RHI_FILTER_LINEAR,
        .wrap_u = RHI_WRAP_REPEAT,
        .wrap_v = RHI_WRAP_REPEAT,
        .wrap_w = RHI_WRAP_REPEAT,
    };
    rs->sampler = rhi_sampler_create(rs->device, &sdesc);

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

    rs->shadow_map = rhi_shadow_map_create(rs->device, 2048, 2048);

    for (int i = 0; i < 4; i++) {
        rs->cascade_maps[i] = rhi_shadow_map_create(rs->device, 1024, 1024);
    }

    rs->cascade_splits[0] = 0.1f;
    rs->cascade_splits[1] = 5.0f;
    rs->cascade_splits[2] = 15.0f;
    rs->cascade_splits[3] = 40.0f;
    rs->cascade_splits[4] = 100.0f;

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
                };
                rs->instanced_pipeline = rhi_pipeline_create(rs->device, &ipd);
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
                };
                rs->skinned_pipeline = rhi_pipeline_create(rs->device, &spd);
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
        u8 *vdata = calloc(vcount, 64);
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

        u32 icount = 36;
        u32 *idata = calloc(icount, 4);
        for (u32 i = 0; i < icount; i++) idata[i] = i;

        RHIBufferDesc vbdesc = {0};
        vbdesc.usage = RHI_BUFFER_USAGE_VERTEX;
        vbdesc.size = vcount * 64;
        vbdesc.initial_data = vdata;
        rs->skinned_vbo = rhi_buffer_create(rs->device, &vbdesc);
        free(vdata);

        RHIBufferDesc ibdesc = {0};
        ibdesc.usage = RHI_BUFFER_USAGE_INDEX;
        ibdesc.size = icount * 4;
        ibdesc.initial_data = idata;
        rs->skinned_ibo = rhi_buffer_create(rs->device, &ibdesc);
        free(idata);
        rs->skinned_index_count = icount;
    }

    return true;
}

static void render_shutdown(RenderState *rs) {
    rhi_shadow_map_destroy(rs->device, &rs->shadow_map);
    for (int i = 0; i < 4; i++) rhi_shadow_map_destroy(rs->device, &rs->cascade_maps[i]);
    if (rhi_handle_valid(rs->depth_pipeline)) rhi_pipeline_destroy(rs->device, rs->depth_pipeline);
    if (rhi_handle_valid(rs->skinned_pipeline)) rhi_pipeline_destroy(rs->device, rs->skinned_pipeline);
    if (rhi_handle_valid(rs->skinned_ibo)) rhi_buffer_destroy(rs->device, rs->skinned_ibo);
    if (rhi_handle_valid(rs->skinned_vbo)) rhi_buffer_destroy(rs->device, rs->skinned_vbo);
    skeleton_shutdown(&rs->skeleton);
    if (rhi_handle_valid(rs->instanced_pipeline)) rhi_pipeline_destroy(rs->device, rs->instanced_pipeline);
    if (rhi_handle_valid(rs->instance_buf)) rhi_buffer_destroy(rs->device, rs->instance_buf);
    if (rhi_handle_valid(rs->clustered_pipeline)) rhi_pipeline_destroy(rs->device, rs->clustered_pipeline);
    if (rhi_handle_valid(rs->terrain_tex))  rhi_texture_destroy(rs->device, rs->terrain_tex);
    if (rhi_handle_valid(rs->fallback_tex)) rhi_texture_destroy(rs->device, rs->fallback_tex);
    if (rhi_handle_valid(rs->fallback_mr)) rhi_texture_destroy(rs->device, rs->fallback_mr);
    if (rhi_handle_valid(rs->fallback_normal)) rhi_texture_destroy(rs->device, rs->fallback_normal);
    if (rhi_handle_valid(rs->fallback_emissive)) rhi_texture_destroy(rs->device, rs->fallback_emissive);
    if (rhi_handle_valid(rs->sampler)) rhi_sampler_destroy(rs->device, rs->sampler);
    if (rhi_handle_valid(rs->pipeline)) rhi_pipeline_destroy(rs->device, rs->pipeline);
    rhi_device_destroy(rs->device);
}

static void bind_material(RHICmdBuffer *cmd, RenderState *rs, Material *mat, Scene *scene) {
    RHITexture alb = (mat && rhi_handle_valid(mat->albedo)) ? mat->albedo : rs->fallback_tex;
    RHITexture mr  = (mat && rhi_handle_valid(mat->metallic_roughness)) ? mat->metallic_roughness : rs->fallback_mr;
    RHITexture nrm = (mat && rhi_handle_valid(mat->normal_map)) ? mat->normal_map : rs->fallback_normal;
    RHITexture em  = (mat && rhi_handle_valid(mat->emissive)) ? mat->emissive : rs->fallback_emissive;
    RHITexture shadow = rhi_handle_valid(rs->cascade_maps[0].depth_tex) ? rs->cascade_maps[0].depth_tex : rs->shadow_map.depth_tex;
    rhi_cmd_bind_material_textures(cmd, alb, mr, nrm, em, shadow, rs->ssao_tex, rs->sampler);
    (void)scene;
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

    LightSystem lights = {0};
    light_system_init(&lights, render.device);

    ParticleSystem particles = {0};
    particles_init(&particles, render.device);

    DebugUI ui = {0};
    debug_ui_init(&ui);
    debug_ui_init_renderer(&ui, render.device);

    HotReloadPipeline hotreload = {0};
#ifdef ENGINE_VULKAN
    hotreload_pipeline_init(&hotreload, render.device,
                             "shaders/blinn_phong_vk.vert", "shaders/blinn_phong_vk.frag", NULL);
#else
    hotreload_pipeline_init(&hotreload, render.device,
                             "shaders/blinn_phong.vert", "shaders/blinn_phong.frag", NULL);
#endif

    ScriptEngine script = {0};
    script_engine_init(&script);
    script_load(&script, "assets/init.script");

    CharacterController character = character_create(vec3(0, 5, 5), 0.3f, 1.8f);

    AssetCtx asset = {0};
    asset_ctx_init(&asset, render.device);
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
    u32 ground = physics_body_create(physics, vec3(0, -2, 0), vec3(20, 0.5f, 20), 0, true);

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
                                              vec3(0.5f, 0.5f, 0.5f), 1.0f, false);

        CMeshRef *mr = world_add_component(world, e, COMP_MESH_REF);
        if (mr) mr->mesh_index = 0;
        (void)ground;
    }

    TaskSystem *tasks = task_system_create(2);
    AudioSystem *audio = audio_system_create();

    Camera camera = {0};
    u32 w, h;
    platform_get_size(engine.platform, &w, &h);
    camera_init(&camera, 1.047f, (f32)w / (f32)h, 0.1f, 100.0f);

    LOG_INFO("Phase 4 running — ECS: %u entities, Physics: %u bodies, Script: %s",
             world->entity_count - 1, physics->count, script.loaded ? "yes" : "no");
    LOG_INFO("WASD+mouse to move | ESC to quit | Tab=debug UI | F5=reload script");

    profiler_set_enabled(true);
    u32 frame_w = w, frame_h = h;
    f64 total_time = 0.0;
    u32 taa_frame = 0;
    Mat4 prev_view_proj = mat4_identity();
    RHIPipeline last_hr_pipeline = RHI_HANDLE_NULL;
    RHIOffscreenFBO scene_fbo = rhi_offscreen_fbo_create_fmt(render.device, w > 0 ? w : 1, h > 0 ? h : 1, RHI_FORMAT_R16G16B16A16_SFLOAT);
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
    post_process_init(&postfx, render.device, w, h);
    ssao_init(&ssao, render.device, w, h);
    taa_init(&taa, render.device, w, h);
    ssr_init(&ssr_sys, render.device, w, h);
    dof_init(&dof_sys, render.device, w, h);
    volumetric_init(&vol, render.device, w, h);
    tonemap_init(&tonemap, render.device);
    fxaa_init(&fxaa_sys, render.device, w, h);
    ssgi_init(&ssgi_sys, render.device, w, h);
    lens_flare_init(&lens_flare, render.device, w, h);
    sharpen_init(&sharpen_sys, render.device, w, h);
    motion_blur_init(&motion_blur, render.device, w, h);
    contact_shadow_init(&contact_shadow, render.device, w, h);
    sss_init(&sss_sys, render.device, w, h);

    while (engine_frame(&engine)) {
        profiler_begin_frame();

        platform_get_size(engine.platform, &w, &h);
        if (w != frame_w || h != frame_h) {
            rhi_device_resize(render.device, w, h);
            camera.aspect = (f32)w / (f32)h;
            if (rhi_handle_valid(scene_fbo.fb)) rhi_offscreen_fbo_destroy(render.device, &scene_fbo);
            scene_fbo = rhi_offscreen_fbo_create_fmt(render.device, w, h, RHI_FORMAT_R16G16B16A16_SFLOAT);
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
            post_process_init(&postfx, render.device, w, h);
            ssao_init(&ssao, render.device, w, h);
            taa_init(&taa, render.device, w, h);
            ssr_init(&ssr_sys, render.device, w, h);
            dof_init(&dof_sys, render.device, w, h);
            volumetric_init(&vol, render.device, w, h);
            tonemap_init(&tonemap, render.device);
            fxaa_init(&fxaa_sys, render.device, w, h);
            ssgi_init(&ssgi_sys, render.device, w, h);
            lens_flare_init(&lens_flare, render.device, w, h);
            sharpen_init(&sharpen_sys, render.device, w, h);
            motion_blur_init(&motion_blur, render.device, w, h);
            contact_shadow_init(&contact_shadow, render.device, w, h);
            sss_init(&sss_sys, render.device, w, h);
            frame_w = w;
            frame_h = h;
        }

        u32 draw_calls = 0;
        camera_update(&camera, platform_input(engine.platform), (f32)engine.delta_time);

        if (input_key_pressed(platform_input(engine.platform), 259)) {
            debug_ui_toggle(&ui);
        }

        hotreload_pipeline_poll(&hotreload);
        script_reload_if_changed(&script, "assets/init.script");

        /* Use hot-reloaded pipeline as active pipeline when available */
        RHIPipeline active_pipeline = render.pipeline;
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
            script_load(&script, "assets/init.script");
        }

        profiler_push("physics");
        physics_step(physics, (f32)engine.delta_time);

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
        ComponentType query_types[] = { COMP_TRANSFORM, COMP_RIGID_BODY };
        Query *q = world_query(world, query_types, 2);
        QueryIter it = query_begin(q);
        while (query_next(&it)) {
            (void)it;
        }
        query_done(q);
        profiler_pop();

        Mat4 view = camera_view(&camera);
        Mat4 proj = camera_projection(&camera);

        {
            u32 n = taa_frame + 1;
            f32 hx = 0.f, base = 0.5f;
            for (u32 d = n; d > 0; d >>= 1) { if (d & 1) hx += base; base *= 0.5f; }
            f32 hy = 0.f; base = 1.f/3.f;
            for (u32 d = n; d > 0; d /= 3) { hy += (d % 3) * base; base /= 3.f; }
            proj.e[2][0] += (hx - 0.5f) * 2.0f / (f32)w;
            proj.e[2][1] += (hy - 0.5f) * 2.0f / (f32)h;
        }
        Mat4 curr_view_proj = mat4_mul(proj, view);

        debug_ui_begin(&ui);
        debug_ui_text(&ui, "FPS: %.0f (%.2f ms)", engine.fps, engine.delta_time * 1000.0);
        debug_ui_text(&ui, "Entities: %u", world->entity_count - 1);
        debug_ui_text(&ui, "Physics bodies: %u", physics->count);
        debug_ui_text(&ui, "Draw calls: %u", draw_calls);
        debug_ui_text(&ui, "Script: %s (%u funcs)", script.loaded ? "loaded" : "none", script.func_count);
        debug_ui_text(&ui, "Character: %.1f %.1f %.1f %s",
                      character.position.e[0], character.position.e[1], character.position.e[2],
                      character.grounded ? "grounded" : "airborne");

        const ProfilerFrame *pf = profiler_last_frame();
        if (pf) {
            debug_ui_text(&ui, "--- Profiler ---");
            debug_ui_text(&ui, "Frame: %.2f ms", (f64)(pf->frame_end_us - pf->frame_start_us) / 1000.0);
            for (u32 ri = 0; ri < pf->region_count; ri++) {
                debug_ui_text(&ui, "  %s: %.2f ms", pf->regions[ri].name, (f64)pf->regions[ri].elapsed_us / 1000.0);
            }
        }

        debug_ui_end(&ui);

        profiler_push("render");
        RHICmdBuffer *cmd = rhi_frame_begin(render.device);

        draw_calls = 0;

        particles_compute(&particles, cmd, (f32)engine.delta_time);

        /* CSM: compute cascade VP matrices and render depth passes */
        if (rhi_handle_valid(render.depth_pipeline)) {
            Vec3 light_dir = vec3_normalize(vec3(0.5f, -0.8f, 0.3f));
            f32 cy = cosf(camera.yaw);
            f32 sy = sinf(camera.yaw);
            f32 cp = cosf(camera.pitch);
            f32 sp = sinf(camera.pitch);
            Vec3 fwd = vec3(cy * cp, sp, sy * cp);

            for (int c = 0; c < 4; c++) {
                f32 zn = render.cascade_splits[c];
                f32 zf = render.cascade_splits[c + 1];
                f32 mid = (zn + zf) * 0.5f;

                Vec3 center = vec3_add(camera.position, vec3_scale(fwd, mid));

                f32 extent = zf - zn;
                Mat4 lview = mat4_lookat(vec3_add(center, vec3_scale(light_dir, -extent)), center, vec3(0, 1, 0));
                Mat4 lproj = mat4_ortho(-extent, extent, -extent, extent, 0.1f, extent * 2.0f);
                render.cascade_vp[c] = mat4_mul(lproj, lview);

                rhi_cmd_bind_shadow_map(cmd, &render.cascade_maps[c]);
                rhi_cmd_bind_pipeline(cmd, render.depth_pipeline);

                Mat4 identity = mat4_identity();
                i32 loc_model = rhi_pipeline_get_uniform_location(render.device, render.depth_pipeline, "u_model");
                if (loc_model >= 0) rhi_cmd_set_uniform_mat4(cmd, loc_model, &identity.e[0][0]);
                i32 loc_lvp = rhi_pipeline_get_uniform_location(render.device, render.depth_pipeline, "u_light_vp");
                if (loc_lvp >= 0) rhi_cmd_set_uniform_mat4(cmd, loc_lvp, &render.cascade_vp[c].e[0][0]);

                if (rhi_handle_valid(terrain.vbo)) {
                    rhi_cmd_bind_vertex_buffer(cmd, terrain.vbo, 0);
                    rhi_cmd_bind_index_buffer(cmd, terrain.ibo, 0);
                    rhi_cmd_draw_indexed(cmd, terrain.index_count, 1);
                    draw_calls++;
                }

                for (u32 ni = 0; ni < scene.node_count; ni++) {
                    SceneNode *node = &scene.nodes[ni];
                    if (!node->has_mesh) continue;
                    if (node->mesh_index >= scene.mesh_count) continue;
                    Mesh *m = &scene.meshes[node->mesh_index];
                    if (loc_model >= 0) rhi_cmd_set_uniform_mat4(cmd, loc_model, &node->world_transform.e[0][0]);
                    rhi_cmd_bind_vertex_buffer(cmd, m->vertex_buf, 0);
                    rhi_cmd_bind_index_buffer(cmd, m->index_buf, 0);
                    rhi_cmd_draw_indexed(cmd, m->index_count, 1);
                    draw_calls++;
                }

                rhi_cmd_unbind_shadow_map(cmd, w, h);
            }
        }

        if (rhi_handle_valid(scene_fbo.fb)) {
            rhi_offscreen_fbo_bind(cmd, &scene_fbo);
        }
        rhi_cmd_clear_color(cmd, 0.05f, 0.05f, 0.1f, 1.0f);

        skybox_render(&skybox, cmd, &view.e[0][0], &proj.e[0][0]);

        terrain_render(&terrain, cmd, &view.e[0][0], &proj.e[0][0], &camera.position.e[0],
                       render.terrain_tex, render.sampler);

        /* Clustered forward lighting pass */
        if (rhi_handle_valid(render.clustered_pipeline)) {
            light_system_clear(&lights);
            light_system_add_dir(&lights, 0.5f, -0.8f, 0.3f, 1.0f, 0.95f, 0.9f);
            for (u32 i = 0; i < 32; i++) {
                f32 angle = (f32)i * 6.283185f / 32.0f + (f32)total_time * 0.5f;
                f32 x = cosf(angle) * 8.0f;
                f32 z = sinf(angle) * 8.0f;
                f32 r = ((i * 7919) % 256) / 256.0f;
                f32 g = ((i * 6271) % 256) / 256.0f;
                f32 b = ((i * 4253) % 256) / 256.0f;
                light_system_add_point(&lights, x, 2.0f, z, 6.0f, r, g, b);
            }
            light_system_cull(&lights, &view.e[0][0], &proj.e[0][0], w, h);
            memcpy(lights.cascade_vp, render.cascade_vp, sizeof(render.cascade_vp));
            light_system_upload(&lights);

            rhi_cmd_bind_pipeline(cmd, render.clustered_pipeline);
            rhi_cmd_set_uniform_mat4(cmd, render.cl_loc_view, &view.e[0][0]);
            rhi_cmd_set_uniform_mat4(cmd, render.cl_loc_proj, &proj.e[0][0]);
            rhi_cmd_set_uniform_vec3(cmd, render.cl_loc_ambient, 0.08f, 0.08f, 0.1f);
            rhi_cmd_set_uniform_vec3(cmd, render.cl_loc_camera_pos,
                                     camera.position.e[0], camera.position.e[1], camera.position.e[2]);
            rhi_cmd_set_uniform_f32(cmd, render.cl_loc_screen_w, (f32)w);
            rhi_cmd_set_uniform_f32(cmd, render.cl_loc_screen_h, (f32)h);
            rhi_cmd_set_uniform_f32(cmd, render.cl_loc_near, 0.1f);
            rhi_cmd_set_uniform_f32(cmd, render.cl_loc_far, 100.0f);
            rhi_cmd_set_uniform_i32(cmd, render.cl_loc_point_count, (i32)lights.point_count);
            rhi_cmd_set_uniform_i32(cmd, render.cl_loc_dir_count, (i32)lights.dir_count);

            rhi_cmd_bind_texel_buffers(cmd, lights.light_data_buf, lights.light_grid_buf);

            Mat4 cl_model = mat4_identity();
            rhi_cmd_set_uniform_mat4(cmd, render.cl_loc_model, &cl_model.e[0][0]);
            rhi_cmd_bind_material_textures(cmd, render.terrain_tex, render.fallback_mr, render.fallback_normal, render.fallback_emissive, render.cascade_maps[0].depth_tex, render.ssao_tex, render.sampler);
            rhi_cmd_bind_vertex_buffer(cmd, terrain.vbo, 0);
            rhi_cmd_bind_index_buffer(cmd, terrain.ibo, 0);
            rhi_cmd_draw_indexed(cmd, terrain.index_count, 1);
            draw_calls++;
        }

        particles_render(&particles, cmd, &view.e[0][0], &proj.e[0][0]);

        if (rhi_handle_valid(render.skinned_pipeline)) {
            render.anim_clip.time += engine.delta_time;
            if (render.anim_clip.time >= render.anim_clip.duration) {
                render.anim_clip.time -= render.anim_clip.duration;
            }
            skeleton_evaluate(&render.skeleton, &render.anim_clip, engine.delta_time);
            skeleton_upload(&render.skeleton);

            rhi_cmd_bind_pipeline(cmd, render.skinned_pipeline);
            rhi_cmd_set_uniform_mat4(cmd, render.sk_loc_view, &view.e[0][0]);
            rhi_cmd_set_uniform_mat4(cmd, render.sk_loc_proj, &proj.e[0][0]);
            rhi_cmd_set_uniform_vec3(cmd, render.sk_loc_light_dir, 0.5f, -0.8f, 0.3f);
            rhi_cmd_set_uniform_vec3(cmd, render.sk_loc_light_color, 1.0f, 0.95f, 0.9f);
            rhi_cmd_set_uniform_vec3(cmd, render.sk_loc_ambient, 0.3f, 0.3f, 0.35f);
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
                    draw_calls++;
                }
            } else if (rhi_handle_valid(render.skinned_vbo)) {
                bind_material(cmd, &render, NULL, &scene);
                rhi_cmd_bind_texel_buffers(cmd, render.skeleton.joint_buf, render.skeleton.joint_buf);
                rhi_cmd_bind_vertex_buffer(cmd, render.skinned_vbo, 0);
                rhi_cmd_bind_index_buffer(cmd, render.skinned_ibo, 0);
                rhi_cmd_draw_indexed(cmd, render.skinned_index_count, 1);
                draw_calls++;
            }
        }

        rhi_cmd_bind_pipeline(cmd, active_pipeline);
        rhi_cmd_set_uniform_mat4(cmd, render.loc_view, &view.e[0][0]);
        rhi_cmd_set_uniform_mat4(cmd, render.loc_proj, &proj.e[0][0]);
        rhi_cmd_set_uniform_vec3(cmd, render.loc_light_dir, 0.5f, -0.8f, 0.3f);
        rhi_cmd_set_uniform_vec3(cmd, render.loc_light_color, 1.0f, 0.95f, 0.9f);
        rhi_cmd_set_uniform_vec3(cmd, render.loc_ambient, 0.3f, 0.3f, 0.35f);
        rhi_cmd_set_uniform_vec3(cmd, render.loc_camera_pos,
                                 camera.position.e[0], camera.position.e[1], camera.position.e[2]);

        Frustum frustum = frustum_from_vp(mat4_mul(proj, view));

        if (scene.mesh_count > 0 && rhi_handle_valid(render.instanced_pipeline)) {
            ComponentType mesh_query_types[] = { COMP_TRANSFORM, COMP_MESH_REF };
            Query *mq = world_query(world, mesh_query_types, 2);
            u32 instance_count = 0;
            f32 *instance_data = malloc(10000 * 16 * sizeof(f32));

            if (mq && mq->match_count > 0) {
                for (u32 mi = 0; mi < mq->match_count; mi++) {
                    Archetype *a = mq->matching[mi];
                    Chunk *c = a->chunks;
                    while (c) {
                        u32 *entities = (u32 *)((u8 *)c + a->entity_offset);
                        for (u32 ci = 0; ci < c->count; ci++) {
                            u32 eidx = entities[ci];
                            Entity e = world->entities[eidx];
                            CTransform *et = world_get_component(world, e, COMP_TRANSFORM);
                            if (!et) continue;
                            Vec3 epos = {{ et->pos[0], et->pos[1], et->pos[2] }};
                            if (!frustum_test_sphere(&frustum, epos, 1.0f)) continue;
                            Mat4 model = mat4_identity();
                            model.e[3][0] = et->pos[0];
                            model.e[3][1] = et->pos[1];
                            model.e[3][2] = et->pos[2];
                            if (instance_count < 10000) {
                                memcpy(instance_data + instance_count * 16, model.e, 64);
                                instance_count++;
                            }
                        }
                        c = c->next;
                    }
                }
            }
            query_done(mq);

            if (instance_count > 0) {
                rhi_buffer_update(render.device, render.instance_buf, instance_data, instance_count * 64);
                rhi_cmd_bind_pipeline(cmd, render.instanced_pipeline);
                rhi_cmd_set_uniform_mat4(cmd, render.inst_loc_view, &view.e[0][0]);
                rhi_cmd_set_uniform_mat4(cmd, render.inst_loc_proj, &proj.e[0][0]);
                rhi_cmd_set_uniform_vec3(cmd, render.inst_loc_light_dir, 0.5f, -0.8f, 0.3f);
                rhi_cmd_set_uniform_vec3(cmd, render.inst_loc_light_color, 1.0f, 0.95f, 0.9f);
                rhi_cmd_set_uniform_vec3(cmd, render.inst_loc_ambient, 0.3f, 0.3f, 0.35f);
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
                    draw_calls++;
                }
            }
            free(instance_data);
        } else if (scene.mesh_count > 0) {
            ComponentType mesh_query_types[] = { COMP_TRANSFORM, COMP_MESH_REF };
            Query *mq = world_query(world, mesh_query_types, 2);
            bool drew_any = false;

            if (mq && mq->match_count > 0) {
                for (u32 mi = 0; mi < mq->match_count; mi++) {
                    Archetype *a = mq->matching[mi];
                    Chunk *c = a->chunks;
                    while (c) {
                        u32 *entities = (u32 *)((u8 *)c + a->entity_offset);
                        for (u32 ci = 0; ci < c->count; ci++) {
                            u32 eidx = entities[ci];
                            Entity e = world->entities[eidx];

                            CTransform *et = world_get_component(world, e, COMP_TRANSFORM);
                            CMeshRef   *em = world_get_component(world, e, COMP_MESH_REF);
                            if (!et || !em) continue;

                            Vec3 epos2 = {{ et->pos[0], et->pos[1], et->pos[2] }};
                            if (!frustum_test_sphere(&frustum, epos2, 1.0f)) continue;

                            u32 mesh_idx = em->mesh_index;
                            if (mesh_idx >= scene.mesh_count) mesh_idx = 0;
                            Mesh *m = &scene.meshes[mesh_idx];

                            Mat4 model = mat4_identity();
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
                            draw_calls++;
                            drew_any = true;
                        }
                        c = c->next;
                    }
                }
            }
            query_done(mq);

            if (!drew_any && scene.node_count > 0) {
                scene_compute_world_transforms(&scene);
                for (u32 ni = 0; ni < scene.node_count; ni++) {
                    SceneNode *node = &scene.nodes[ni];
                    if (!node->has_mesh || node->skinned) continue;
                    if (node->mesh_index >= scene.mesh_count) continue;

                    Vec3 node_pos = {{ node->world_transform.e[3][0], node->world_transform.e[3][1], node->world_transform.e[3][2] }};
                    if (!frustum_test_sphere(&frustum, node_pos, 2.0f)) continue;

                    Mesh *m = &scene.meshes[node->mesh_index];
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
                    draw_calls++;
                }
            } else if (!drew_any) {
                for (u32 i = 0; i < scene.mesh_count; i++) {
                    Mesh *m = &scene.meshes[i];
                    Mat4 model = mat4_identity();
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
                    draw_calls++;
                }
            }
        }

        if (rhi_handle_valid(scene_fbo.fb) && ssao.ready) {
            Mat4 p;
            memcpy(&p, &proj, sizeof(Mat4));
            Mat4 inv_proj = mat4_inverse(p);
            ssao_apply(&ssao, cmd, scene_fbo.depth_tex,
                       &proj.e[0][0], &inv_proj.e[0][0], w, h);
            render.ssao_tex = ssao_get_texture(&ssao);
        }

        if (contact_shadow.ready && rhi_handle_valid(scene_fbo.fb)) {
            Mat4 cs_p;
            memcpy(&cs_p, &proj, sizeof(Mat4));
            Mat4 cs_inv = mat4_inverse(cs_p);
            contact_shadow_apply(&contact_shadow, cmd, scene_fbo.depth_tex,
                                 &cs_inv.e[0][0], 0.5f, -0.8f, 0.3f, w, h);
        }

        if (rhi_handle_valid(scene_fbo.fb) && vol.ready) {
            Mat4 pv;
            memcpy(&pv, &proj, sizeof(Mat4));
            Mat4 inv_proj_v = mat4_inverse(pv);
            f32 light_dir[] = { 0.5f, -0.8f, 0.3f };
            f32 light_color[] = { 1.0f, 0.95f, 0.9f };
            volumetric_apply(&vol, cmd, scene_fbo.depth_tex, render.cascade_maps[0].depth_tex,
                             &inv_proj_v.e[0][0], &view.e[0][0], light_dir, light_color, w, h);
        }

        if (lens_flare.ready && rhi_handle_valid(scene_fbo.fb)) {
            f32 ld[] = { 0.5f, -0.8f, 0.3f };
            lens_flare_apply(&lens_flare, cmd, scene_fbo.depth_tex,
                             &view.e[0][0], &proj.e[0][0], ld,
                             1.0f, 0.95f, 0.9f, w, h);
        }

        if (rhi_handle_valid(scene_fbo.fb) && ssr_sys.ready) {
            Mat4 p3;
            memcpy(&p3, &proj, sizeof(Mat4));
            Mat4 inv_proj3 = mat4_inverse(p3);
            ssr_apply(&ssr_sys, cmd, scene_fbo.color_tex, scene_fbo.depth_tex,
                      &proj.e[0][0], &inv_proj3.e[0][0], &view.e[0][0], w, h);
        }

        if (ssgi_sys.ready && rhi_handle_valid(scene_fbo.fb)) {
            Mat4 p_ssgi;
            memcpy(&p_ssgi, &proj, sizeof(Mat4));
            Mat4 inv_proj_ssgi = mat4_inverse(p_ssgi);
            ssgi_apply(&ssgi_sys, cmd, scene_fbo.depth_tex, scene_fbo.color_tex,
                       &inv_proj_ssgi.e[0][0], &proj.e[0][0], w, h);
        }

        RHITexture taa_output = scene_fbo.color_tex;
        if (rhi_handle_valid(scene_fbo.fb) && taa.ready) {
            Mat4 p2;
            memcpy(&p2, &proj, sizeof(Mat4));
            Mat4 inv_proj2 = mat4_inverse(p2);
            taa_resolve(&taa, cmd, scene_fbo.color_tex, scene_fbo.depth_tex,
                        &curr_view_proj.e[0][0], &prev_view_proj.e[0][0],
                        &inv_proj2.e[0][0], w, h);
            taa_output = taa_get_output(&taa);
        }

        if (fxaa_sys.ready && rhi_handle_valid(scene_fbo.fb)) {
            fxaa_apply(&fxaa_sys, cmd, taa_output, w, h);
            taa_output = fxaa_get_texture(&fxaa_sys);
        }

        if (sharpen_sys.ready && rhi_handle_valid(scene_fbo.fb)) {
            sharpen_apply(&sharpen_sys, cmd, taa_output, 0.35f, w, h);
            taa_output = sharpen_sys.fbo.color_tex;
        }

        if (motion_blur.ready && rhi_handle_valid(scene_fbo.fb)) {
            Mat4 mb_p;
            memcpy(&mb_p, &proj, sizeof(Mat4));
            Mat4 mb_inv = mat4_inverse(mb_p);
            motion_blur_apply(&motion_blur, cmd, taa_output, scene_fbo.depth_tex,
                              &mb_inv.e[0][0], &prev_view_proj.e[0][0],
                              1.0f, w, h);
            taa_output = motion_blur.fbo.color_tex;
        }

        RHITexture post_input = taa_output;
        if (rhi_handle_valid(scene_fbo.fb) && dof_sys.ready) {
            Mat4 p4;
            memcpy(&p4, &proj, sizeof(Mat4));
            Mat4 inv_proj4 = mat4_inverse(p4);
            dof_apply(&dof_sys, cmd, taa_output, scene_fbo.depth_tex,
                      &inv_proj4.e[0][0], w, h);
            post_input = dof_get_texture(&dof_sys);
        }

        if (sss_sys.ready && rhi_handle_valid(scene_fbo.fb)) {
            sss_apply(&sss_sys, cmd, post_input, scene_fbo.depth_tex,
                      0.5f, 0.1f, w, h);
            post_input = sss_sys.fbo.color_tex;
        }

        if (rhi_handle_valid(scene_fbo.fb) && postfx.ready) {
            post_process_apply(&postfx, cmd, post_input, w, h);
        }

        if (tonemap.ready && rhi_handle_valid(scene_fbo.fb)) {
            tonemap_apply(&tonemap, cmd, post_input, w, h, (f32)total_time, (f32)engine.delta_time);
        } else if (rhi_handle_valid(scene_fbo.fb)) {
            rhi_offscreen_fbo_unbind(cmd, w, h);
            rhi_cmd_bind_pipeline(cmd, postfx.tex_pipe);
            rhi_cmd_bind_texture(cmd, post_input, postfx.sampler, 0);
            rhi_cmd_draw(cmd, 3, 1);
        }

        debug_ui_render(&ui, cmd, w, h);

        rhi_frame_end(render.device);
        rhi_present(render.device);
        prev_view_proj = curr_view_proj;
        taa_frame++;
        total_time += engine.delta_time;
        profiler_pop();

        profiler_push("end_frame");
        profiler_pop();

        profiler_end_frame();
    }

    LOG_INFO("Shutting down...");
    world_destroy(world);
    LOG_INFO("  world done");
    task_system_destroy(tasks);
    LOG_INFO("  tasks done");
    audio_system_destroy(audio);
    LOG_INFO("  audio done");
    physics_world_destroy(physics);
    LOG_INFO("  physics done");
    particles_shutdown(&particles);
    LOG_INFO("  particles done");
    light_system_shutdown(&lights);
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
       if (rhi_handle_valid(scene_fbo.fb)) rhi_offscreen_fbo_destroy(render.device, &scene_fbo);
    LOG_INFO("  postfx done");
    terrain_shutdown(&terrain);
    LOG_INFO("  terrain done");
    hotreload_pipeline_shutdown(&hotreload);
    LOG_INFO("  hotreload done");
    script_engine_shutdown(&script);
    LOG_INFO("  script done");
    debug_ui_shutdown(&ui);
    asset_scene_free(&asset, &scene);
    LOG_INFO("  asset done");
    skybox_shutdown(&skybox);
    LOG_INFO("  skybox done");
    render_shutdown(&render);
    LOG_INFO("  render done");
    engine_shutdown(&engine);
    LOG_INFO("  engine done");
    return 0;
}
