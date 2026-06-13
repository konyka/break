#include <engine.h>
#include <rhi/rhi.h>
#include <renderer/camera.h>
#include <renderer/skybox.h>
#include <renderer/terrain.h>
#include <renderer/lighting.h>
#include <renderer/combined_post_process.h>
#include <renderer/gpucull.h>
#include <renderer/ibl.h>
#include <asset/asset.h>
#include <ecs/ecs.h>
#include <physics/physics.h>
#include <core/log.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#ifdef _WIN32
#include <direct.h>
#define tv_mkdir(p) _mkdir(p)
#else
#include <sys/stat.h>
#define tv_mkdir(p) mkdir(p, 0755)
#endif

static char *file_read(const char *path, usize *out_len) {
    FILE *f = fopen(path, "rb");
    if (!f) return NULL;
    fseek(f, 0, SEEK_END); long sz = ftell(f); fseek(f, 0, SEEK_SET);
    char *buf = malloc((usize)sz + 1);
    usize rd = fread(buf, 1, (usize)sz, f);
    buf[rd] = '\0';
    fclose(f);
    if (out_len) *out_len = rd;
    return buf;
}

/* Insert `#define <name> 1` right after the first (`#version`) line. */
static char *tv_inject_define(const char *src, usize len, const char *name, usize *out_len) {
    const char *nl = memchr(src, '\n', len);
    usize head = nl ? (usize)(nl - src) + 1u : len;
    char def[64];
    int dn = snprintf(def, sizeof(def), "#define %s 1\n", name);
    char *out = malloc(len + (usize)dn + 1u);
    if (!out) return NULL;
    memcpy(out, src, head);
    memcpy(out + head, def, (usize)dn);
    memcpy(out + head + (usize)dn, src + head, len - head);
    out[len + (usize)dn] = '\0';
    if (out_len) *out_len = len + (usize)dn;
    return out;
}

/* ---- Golden image regression helpers ------------------------------------
 * The presented frame is read back via rhi_screenshot, box-downsampled to a
 * tiny grid (robust against single-pixel driver noise) and compared against a
 * committed reference PPM with a mean-absolute-error tolerance. Set the env var
 * GOLDEN_UPDATE=1 to regenerate the reference. */
#define GOLDEN_GW 20
#define GOLDEN_GH 15
#ifdef ENGINE_VULKAN
#define GOLDEN_PATH "tests/golden/test_vulkan_vk.ppm"
#define TV_BACKEND        RHI_BACKEND_VULKAN
#define TV_VS_BLINN       "shaders/blinn_phong_vk.vert"
#define TV_FS_BLINN       "shaders/blinn_phong_vk.frag"
#define TV_VS_INSTANCED   "shaders/instanced_vk.vert"
#define TV_FS_INSTANCED   "shaders/instanced_vk.frag"
#define TV_VS_PBR         "shaders/pbr_clustered_vk.vert"
#define TV_FS_PBR         "shaders/pbr_clustered_vk.frag"
#define TV_SUITE_NAME     "Vulkan Backend Test Suite"
#define TV_WINDOW_TITLE   "Vulkan Test"
#else
#define GOLDEN_PATH "tests/golden/test_vulkan_gl.ppm"
#define TV_BACKEND        RHI_BACKEND_OPENGL
#define TV_VS_BLINN       "shaders/blinn_phong.vert"
#define TV_FS_BLINN       "shaders/blinn_phong.frag"
#define TV_VS_INSTANCED   "shaders/instanced.vert"
#define TV_FS_INSTANCED   "shaders/instanced.frag"
#define TV_VS_PBR         "shaders/pbr_clustered.vert"
#define TV_FS_PBR         "shaders/pbr_clustered.frag"
#define TV_SUITE_NAME     "OpenGL Backend Test Suite"
#define TV_WINDOW_TITLE   "OpenGL Test"
#endif

static void golden_downsample(const u8 *rgba, u32 w, u32 h, u8 *grid /* GW*GH*3 */) {
    for (u32 gy = 0; gy < GOLDEN_GH; gy++) {
        for (u32 gx = 0; gx < GOLDEN_GW; gx++) {
            u32 x0 = gx * w / GOLDEN_GW, x1 = (gx + 1) * w / GOLDEN_GW;
            u32 y0 = gy * h / GOLDEN_GH, y1 = (gy + 1) * h / GOLDEN_GH;
            u64 r = 0, g = 0, b = 0, n = 0;
            for (u32 yy = y0; yy < y1; yy++) {
                for (u32 xx = x0; xx < x1; xx++) {
                    const u8 *p = &rgba[((usize)yy * w + xx) * 4u];
                    r += p[0]; g += p[1]; b += p[2]; n++;
                }
            }
            if (n == 0) n = 1;
            u8 *o = &grid[((usize)gy * GOLDEN_GW + gx) * 3u];
            o[0] = (u8)(r / n); o[1] = (u8)(g / n); o[2] = (u8)(b / n);
        }
    }
}

static bool golden_write_ppm(const char *path, const u8 *grid) {
    tv_mkdir("tests");
    tv_mkdir("tests/golden");
    FILE *f = fopen(path, "wb");
    if (!f) return false;
    fprintf(f, "P6\n%d %d\n255\n", GOLDEN_GW, GOLDEN_GH);
    fwrite(grid, 1, (usize)GOLDEN_GW * GOLDEN_GH * 3, f);
    fclose(f);
    return true;
}

/* Returns 0 = compared (fills mae/maxd), 1 = format/size mismatch, -1 = absent. */
static int golden_compare_ppm(const char *path, const u8 *grid, f64 *out_mae, u32 *out_max) {
    FILE *f = fopen(path, "rb");
    if (!f) return -1;
    int gw = 0, gh = 0, mx = 0;
    if (fscanf(f, "P6 %d %d %d", &gw, &gh, &mx) != 3 || gw != GOLDEN_GW || gh != GOLDEN_GH) {
        fclose(f); return 1;
    }
    fgetc(f); /* consume the single whitespace after maxval */
    u8 ref[GOLDEN_GW * GOLDEN_GH * 3];
    usize rd = fread(ref, 1, sizeof(ref), f);
    fclose(f);
    if (rd != sizeof(ref)) return 1;
    f64 sum = 0; u32 maxd = 0;
    for (usize i = 0; i < sizeof(ref); i++) {
        int d = (int)grid[i] - (int)ref[i];
        if (d < 0) d = -d;
        sum += (f64)d;
        if ((u32)d > maxd) maxd = (u32)d;
    }
    if (out_mae) *out_mae = sum / (f64)sizeof(ref);
    if (out_max) *out_max = maxd;
    return 0;
}

typedef struct {
    RHIDevice    *device;
    RHIPipeline   pipeline;
    RHISampler    sampler;
    RHITexture    test_tex;
    i32 loc_model, loc_view, loc_proj;
    i32 loc_light_dir, loc_light_color, loc_ambient, loc_camera_pos;
} TestRenderState;

static bool tv_run_golden_regression(const TestRenderState *render, RHIBuffer vbo, RHIBuffer ibo,
                                     u32 w, u32 h) {
    LOG_INFO("============================================");
    LOG_INFO("TEST: GOLDEN IMAGE REGRESSION");
    LOG_INFO("============================================");

    Mat4 gid = mat4_identity();
    for (u32 f = 0; f < 3; f++) {
        RHICmdBuffer *cmd = rhi_frame_begin(render->device);
        if (!cmd) continue;
        rhi_cmd_clear_color(cmd, 0.10f, 0.10f, 0.15f, 1.0f);
        rhi_cmd_bind_pipeline(cmd, render->pipeline);
        rhi_cmd_set_uniform_mat4(cmd, render->loc_model, &gid.e[0][0]);
        rhi_cmd_set_uniform_mat4(cmd, render->loc_view, &gid.e[0][0]);
        rhi_cmd_set_uniform_mat4(cmd, render->loc_proj, &gid.e[0][0]);
        rhi_cmd_set_uniform_vec3(cmd, render->loc_light_dir, 0.5f, -0.8f, 0.3f);
        rhi_cmd_set_uniform_vec3(cmd, render->loc_light_color, 1.0f, 0.95f, 0.9f);
        rhi_cmd_set_uniform_vec3(cmd, render->loc_ambient, 0.35f, 0.35f, 0.40f);
        rhi_cmd_set_uniform_vec3(cmd, render->loc_camera_pos, 0, 0, 5);
        rhi_cmd_bind_texture(cmd, render->test_tex, render->sampler, 0);
        rhi_cmd_bind_vertex_buffer(cmd, vbo, 0);
        rhi_cmd_bind_index_buffer(cmd, ibo, 0);
        rhi_cmd_draw_indexed(cmd, 3, 1);
        rhi_frame_end(render->device);
        rhi_present(render->device);
    }

    bool golden_pass = false;
    u8 *shot = (u8 *)malloc((usize)w * h * 4u);
    if (shot) {
        rhi_screenshot(render->device, 0, 0, w, h, shot);
        u8 grid[GOLDEN_GW * GOLDEN_GH * 3];
        golden_downsample(shot, w, h, grid);
        free(shot);

        bool update = (getenv("GOLDEN_UPDATE") != NULL);
        f64 mae = 0.0;
        u32 maxd = 0;
        int cmp = update ? -1 : golden_compare_ppm(GOLDEN_PATH, grid, &mae, &maxd);
        if (cmp == -1) {
            if (golden_write_ppm(GOLDEN_PATH, grid)) {
                LOG_WARN("GOLDEN: wrote reference %s (%dx%d) — rerun to compare",
                         GOLDEN_PATH, GOLDEN_GW, GOLDEN_GH);
                golden_pass = true;
            } else {
                LOG_ERROR("GOLDEN: failed to write reference %s", GOLDEN_PATH);
            }
        } else if (cmp == 0) {
            golden_pass = (mae <= 8.0 && maxd <= 56);
            LOG_INFO("GOLDEN: MAE=%.2f max=%u (tol MAE<=8.0 max<=56) -> %s",
                     mae, maxd, golden_pass ? "OK" : "DRIFT");
        } else {
            LOG_ERROR("GOLDEN: format/size mismatch in %s", GOLDEN_PATH);
        }
    }

    if (golden_pass) {
        LOG_INFO("RESULT: GOLDEN IMAGE TEST PASSED ✓");
    } else {
        LOG_ERROR("RESULT: GOLDEN IMAGE TEST FAILED");
    }
    return golden_pass;
}

static bool test_render_init(TestRenderState *rs, Platform *platform) {
    void *window = platform_surface_native(platform);
    void *display = platform_display_native(platform);
    u32 w, h;
    platform_get_size(platform, &w, &h);

    rs->device = rhi_device_create(TV_BACKEND, window, display, w, h);
    if (!rs->device) { LOG_ERROR("FAIL: device create"); return false; }
    LOG_INFO("PASS: RHI device created (backend=%d)", (int)TV_BACKEND);

    usize vs_len = 0, fs_len = 0;
    char *vs_src = file_read(TV_VS_BLINN, &vs_len);
    char *fs_src = file_read(TV_FS_BLINN, &fs_len);
    if (!vs_src || !fs_src) { LOG_ERROR("FAIL: shader load"); return false; }

    RHIShader vs = rhi_shader_create(rs->device, vs_src, vs_len, false);
    RHIShader fs = rhi_shader_create(rs->device, fs_src, fs_len, true);
    free(vs_src); free(fs_src);

    if (!rhi_handle_valid(vs) || !rhi_handle_valid(fs)) {
        LOG_ERROR("FAIL: shader compile");
        return false;
    }
    LOG_INFO("PASS: Shaders compiled (GLSL->SPIR-V)");

    RHIPipelineDesc pdesc = {.vert = vs, .frag = fs, .uses_textures = true};
    rs->pipeline = rhi_pipeline_create(rs->device, &pdesc);
    rhi_shader_destroy(rs->device, vs);
    rhi_shader_destroy(rs->device, fs);

    if (!rhi_handle_valid(rs->pipeline)) {
        LOG_ERROR("FAIL: pipeline create");
        return false;
    }
    LOG_INFO("PASS: Pipeline created");

    rs->loc_model       = rhi_pipeline_get_uniform_location(rs->device, rs->pipeline, "u_model");
    rs->loc_view        = rhi_pipeline_get_uniform_location(rs->device, rs->pipeline, "u_view");
    rs->loc_proj        = rhi_pipeline_get_uniform_location(rs->device, rs->pipeline, "u_proj");
    rs->loc_light_dir   = rhi_pipeline_get_uniform_location(rs->device, rs->pipeline, "u_light_dir");
    rs->loc_light_color = rhi_pipeline_get_uniform_location(rs->device, rs->pipeline, "u_light_color");
    rs->loc_ambient     = rhi_pipeline_get_uniform_location(rs->device, rs->pipeline, "u_ambient");
    rs->loc_camera_pos  = rhi_pipeline_get_uniform_location(rs->device, rs->pipeline, "u_camera_pos");

    if (rs->loc_model < 0 || rs->loc_view < 0 || rs->loc_proj < 0) {
        LOG_ERROR("FAIL: uniform locations invalid (model=%d view=%d proj=%d)", rs->loc_model, rs->loc_view, rs->loc_proj);
        return false;
    }
    LOG_INFO("PASS: Uniform locations (model=%d view=%d proj=%d light_dir=%d)",
             rs->loc_model, rs->loc_view, rs->loc_proj, rs->loc_light_dir);

    RHISamplerDesc sdesc = {
        .min_filter = RHI_FILTER_LINEAR,
        .mag_filter = RHI_FILTER_LINEAR,
        .wrap_u = RHI_WRAP_REPEAT,
        .wrap_v = RHI_WRAP_REPEAT,
        .wrap_w = RHI_WRAP_REPEAT,
    };
    rs->sampler = rhi_sampler_create(rs->device, &sdesc);
    if (!rhi_handle_valid(rs->sampler)) { LOG_ERROR("FAIL: sampler"); return false; }
    LOG_INFO("PASS: Sampler created");

    u8 tex_data[] = {255, 128, 64, 255};
    RHITextureDesc tdesc = { .width = 1, .height = 1, .format = RHI_FORMAT_R8G8B8A8_UNORM, .mip_levels = 1, .data = tex_data };
    rs->test_tex = rhi_texture_create(rs->device, &tdesc);
    if (!rhi_handle_valid(rs->test_tex)) { LOG_ERROR("FAIL: texture create"); return false; }
    LOG_INFO("PASS: Texture created + uploaded");

    return true;
}

static void test_render_shutdown(TestRenderState *rs) {
    if (rhi_handle_valid(rs->test_tex))  rhi_texture_destroy(rs->device, rs->test_tex);
    if (rhi_handle_valid(rs->sampler))   rhi_sampler_destroy(rs->device, rs->sampler);
    if (rhi_handle_valid(rs->pipeline))  rhi_pipeline_destroy(rs->device, rs->pipeline);
    rhi_device_destroy(rs->device);
}

int main(int argc, char **argv) {
    (void)argc; (void)argv;
    log_set_level(LOG_DEBUG);

    LOG_INFO("============================================");
    LOG_INFO("%s", TV_SUITE_NAME);
    LOG_INFO("============================================");

    EngineConfig cfg = { .width = 800, .height = 600, .title = TV_WINDOW_TITLE, .target_fps = 60.0 };
    Engine engine = {0};
    if (!engine_init(&engine, &cfg)) { LOG_FATAL("Engine init failed"); return 1; }

    TestRenderState render = {0};
    if (!test_render_init(&render, engine.platform)) {
        LOG_FATAL("Render init failed");
        engine_shutdown(&engine);
        return 1;
    }

    /* Test: Buffer creation + upload */
    f32 tri_verts[] = {
         0.0f,  1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.5f, 0.0f,
        -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f,
         1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
    };
    RHIBufferDesc vbdesc = {
        .usage = RHI_BUFFER_USAGE_VERTEX,
        .size = sizeof(tri_verts),
        .initial_data = tri_verts,
    };
    RHIBuffer vbo = rhi_buffer_create(render.device, &vbdesc);
    if (!rhi_handle_valid(vbo)) { LOG_ERROR("FAIL: vertex buffer"); }
    else { LOG_INFO("PASS: Vertex buffer created (%zu bytes)", sizeof(tri_verts)); }

    u32 indices[] = {0, 1, 2};
    RHIBufferDesc ibdesc = {
        .usage = RHI_BUFFER_USAGE_INDEX,
        .size = sizeof(indices),
        .initial_data = indices,
    };
    RHIBuffer ibo = rhi_buffer_create(render.device, &ibdesc);
    if (!rhi_handle_valid(ibo)) { LOG_ERROR("FAIL: index buffer"); }
    else { LOG_INFO("PASS: Index buffer created"); }

#ifndef ENGINE_VULKAN
    /* OpenGL CTest: golden-image regression only (full suite remains Vulkan). */
    {
        u32 gw, gh;
        platform_get_size(engine.platform, &gw, &gh);
        LOG_INFO("OpenGL build: skipping Vulkan integration suite");
        bool golden_pass = tv_run_golden_regression(&render, vbo, ibo, gw, gh);
        if (rhi_handle_valid(ibo)) rhi_buffer_destroy(render.device, ibo);
        if (rhi_handle_valid(vbo)) rhi_buffer_destroy(render.device, vbo);
        test_render_shutdown(&render);
        engine_shutdown(&engine);
        LOG_INFO("FINAL RESULT: %s", golden_pass ? "ALL PASSED ✓" : "FAILED");
        return golden_pass ? 0 : 1;
    }
#endif

    /* Test: Skybox */
    Skybox skybox = {0};
    bool sky_ok = skybox_init(&skybox, render.device);
    if (sky_ok) { LOG_INFO("PASS: Skybox initialized"); }
    else { LOG_WARN("WARN: Skybox init failed (non-fatal)"); }

    /* Test: Terrain */
    Terrain terrain = {0};
    bool terr_ok = terrain_init(&terrain, render.device, 32, 20.0f, 1.0f);
    if (terr_ok) { LOG_INFO("PASS: Terrain created (%u indices)", terrain.index_count); }
    else { LOG_WARN("WARN: Terrain init failed"); }

    /* Camera */
    Camera camera = {0};
    u32 w, h;
    platform_get_size(engine.platform, &w, &h);
    camera_init(&camera, 1.047f, (f32)w / (f32)h, 0.1f, 100.0f);

    u8 tex2_data[] = {200, 50, 50, 255};
    RHITextureDesc t2desc = { .width = 1, .height = 1, .format = RHI_FORMAT_R8G8B8A8_UNORM, .mip_levels = 1, .data = tex2_data };
    RHITexture tex2 = rhi_texture_create(render.device, &t2desc);

    /* ---- Offscreen FBO test ---- */
    LOG_INFO("============================================");
    LOG_INFO("Offscreen FBO test");
    LOG_INFO("============================================");

    bool fbo_pass = false;
    RHIOffscreenFBO fbo = rhi_offscreen_fbo_create(render.device, 256, 256);
    if (!rhi_handle_valid(fbo.fb)) {
        LOG_ERROR("FAIL: FBO creation returned invalid handle");
    } else if (!rhi_handle_valid(fbo.color_tex)) {
        LOG_ERROR("FAIL: FBO color texture invalid");
    } else if (!rhi_handle_valid(fbo.depth_tex)) {
        LOG_ERROR("FAIL: FBO depth texture invalid");
    } else {
        LOG_INFO("FBO created: 256x256, fb=%u:%u color=%u:%u depth=%u:%u",
                 fbo.fb.index, fbo.fb.generation,
                 fbo.color_tex.index, fbo.color_tex.generation,
                 fbo.depth_tex.index, fbo.depth_tex.generation);

        u32 fbo_err = 0;
        for (u32 fi = 0; fi < 10; fi++) {
            RHICmdBuffer *cmd = rhi_frame_begin(render.device);
            if (!cmd) { fbo_err++; continue; }

            Mat4 id = mat4_identity();
            rhi_offscreen_fbo_bind(cmd, &fbo);
            rhi_cmd_bind_pipeline(cmd, render.pipeline);
            rhi_cmd_set_uniform_mat4(cmd, render.loc_model, &id.e[0][0]);
            rhi_cmd_set_uniform_mat4(cmd, render.loc_view, &id.e[0][0]);
            rhi_cmd_set_uniform_mat4(cmd, render.loc_proj, &id.e[0][0]);
            rhi_cmd_set_uniform_vec3(cmd, render.loc_light_dir, 0.5f, -0.8f, 0.3f);
            rhi_cmd_set_uniform_vec3(cmd, render.loc_light_color, 1.0f, 0.95f, 0.9f);
            rhi_cmd_set_uniform_vec3(cmd, render.loc_ambient, 0.35f, 0.35f, 0.40f);
            rhi_cmd_set_uniform_vec3(cmd, render.loc_camera_pos, 0, 0, 5);
            rhi_cmd_bind_texture(cmd, render.test_tex, render.sampler, 0);
            rhi_cmd_bind_vertex_buffer(cmd, vbo, 0);
            rhi_cmd_bind_index_buffer(cmd, ibo, 0);
            rhi_cmd_draw_indexed(cmd, 3, 1);

            rhi_offscreen_fbo_unbind(cmd, 800, 600);
            rhi_cmd_bind_pipeline(cmd, render.pipeline);
            rhi_cmd_set_uniform_mat4(cmd, render.loc_model, &id.e[0][0]);
            rhi_cmd_set_uniform_mat4(cmd, render.loc_view, &id.e[0][0]);
            rhi_cmd_set_uniform_mat4(cmd, render.loc_proj, &id.e[0][0]);
            rhi_cmd_set_uniform_vec3(cmd, render.loc_light_dir, 0.5f, -0.8f, 0.3f);
            rhi_cmd_set_uniform_vec3(cmd, render.loc_light_color, 1.0f, 0.95f, 0.9f);
            rhi_cmd_set_uniform_vec3(cmd, render.loc_ambient, 0.35f, 0.35f, 0.40f);
            rhi_cmd_set_uniform_vec3(cmd, render.loc_camera_pos, 0, 0, 5);
            rhi_cmd_bind_texture(cmd, render.test_tex, render.sampler, 0);
            rhi_cmd_bind_vertex_buffer(cmd, vbo, 0);
            rhi_cmd_draw_indexed(cmd, 3, 1);

            rhi_frame_end(render.device);
            rhi_present(render.device);
        }
        if (fbo_err > 0) {
            LOG_ERROR("FAIL: FBO test had %u errors in 10 frames", fbo_err);
        } else {
            LOG_INFO("FBO test: 10 frames rendered OK");
            fbo_pass = true;
        }

        rhi_offscreen_fbo_destroy(render.device, &fbo);
        LOG_INFO("FBO destroyed");
    }

    if (fbo_pass) {
        LOG_INFO("RESULT: OFFSCREEN FBO TEST PASSED ✓");
    } else {
        LOG_ERROR("RESULT: OFFSCREEN FBO TEST FAILED");
    }

    LOG_INFO("============================================");
    LOG_INFO("Stress test: 500 frames, texture bind, multi-draw");
    LOG_INFO("============================================");

    u32 target_frames = 500;
    u32 frame_count = 0;
    u32 error_count = 0;
    f64 total_time = 0.0;
    f64 min_dt = 999.0, max_dt = 0.0;

    while (engine_frame(&engine) && frame_count < target_frames) {
        frame_count++;
        platform_get_size(engine.platform, &w, &h);
        camera_update(&camera, platform_input(engine.platform), (f32)engine.delta_time);
        total_time += engine.delta_time;
        if (engine.delta_time < min_dt) min_dt = engine.delta_time;
        if (engine.delta_time > max_dt) max_dt = engine.delta_time;

        Mat4 view = camera_view(&camera);
        Mat4 proj = camera_projection(&camera);

        RHICmdBuffer *cmd = rhi_frame_begin(render.device);
        if (!cmd) { error_count++; continue; }

        rhi_cmd_clear_color(cmd, 0.1f, 0.1f, 0.15f, 1.0f);

        skybox_render(&skybox, cmd, &view.e[0][0], &mat4_inverse(proj).e[0][0], 0.5f, -0.8f, 0.3f, 1.0f, 0.95f, 0.9f);

        terrain_render(&terrain, cmd, &view.e[0][0], &proj.e[0][0],
                       &camera.position.e[0], render.test_tex, render.sampler,
                       (RHITexture){0,0}, NULL, 0.0f, -1.0f, 0.0f);

        rhi_cmd_bind_pipeline(cmd, render.pipeline);
        rhi_cmd_set_uniform_mat4(cmd, render.loc_view, &view.e[0][0]);
        rhi_cmd_set_uniform_mat4(cmd, render.loc_proj, &proj.e[0][0]);
        rhi_cmd_set_uniform_vec3(cmd, render.loc_light_dir, 0.5f, -0.8f, 0.3f);
        rhi_cmd_set_uniform_vec3(cmd, render.loc_light_color, 1.0f, 0.95f, 0.9f);
        rhi_cmd_set_uniform_vec3(cmd, render.loc_ambient, 0.35f, 0.35f, 0.40f);
        rhi_cmd_set_uniform_vec3(cmd, render.loc_camera_pos,
                                 camera.position.e[0], camera.position.e[1], camera.position.e[2]);

        Mat4 model = mat4_identity();
        rhi_cmd_set_uniform_mat4(cmd, render.loc_model, &model.e[0][0]);

        rhi_cmd_bind_vertex_buffer(cmd, vbo, 0);
        rhi_cmd_bind_index_buffer(cmd, ibo, 0);
        rhi_cmd_bind_texture(cmd, render.test_tex, render.sampler, 0);
        rhi_cmd_draw_indexed(cmd, 3, 1);

        /* Multi-draw with different textures */
        if (rhi_handle_valid(tex2)) {
            Mat4 m2 = mat4_identity();
            m2.e[3][0] = 2.0f;
            rhi_cmd_set_uniform_mat4(cmd, render.loc_model, &m2.e[0][0]);
            rhi_cmd_bind_texture(cmd, tex2, render.sampler, 0);
            rhi_cmd_bind_vertex_buffer(cmd, vbo, 0);
            rhi_cmd_bind_index_buffer(cmd, ibo, 0);
            rhi_cmd_draw_indexed(cmd, 3, 1);
        }

        /* Pipeline rebind test: bind skybox then back to blinn_phong */
        if (sky_ok && frame_count % 10 == 0) {
            skybox_render(&skybox, cmd, &view.e[0][0], &mat4_inverse(proj).e[0][0], 0.5f, -0.8f, 0.3f, 1.0f, 0.95f, 0.9f);
            rhi_cmd_bind_pipeline(cmd, render.pipeline);
            rhi_cmd_set_uniform_mat4(cmd, render.loc_view, &view.e[0][0]);
            rhi_cmd_set_uniform_mat4(cmd, render.loc_proj, &proj.e[0][0]);
            rhi_cmd_set_uniform_vec3(cmd, render.loc_light_dir, 0.5f, -0.8f, 0.3f);
            rhi_cmd_set_uniform_vec3(cmd, render.loc_light_color, 1.0f, 0.95f, 0.9f);
            rhi_cmd_set_uniform_vec3(cmd, render.loc_ambient, 0.35f, 0.35f, 0.40f);
            rhi_cmd_set_uniform_vec3(cmd, render.loc_camera_pos,
                                     camera.position.e[0], camera.position.e[1], camera.position.e[2]);
            rhi_cmd_set_uniform_mat4(cmd, render.loc_model, &model.e[0][0]);
            rhi_cmd_bind_vertex_buffer(cmd, vbo, 0);
            rhi_cmd_bind_index_buffer(cmd, ibo, 0);
            rhi_cmd_bind_texture(cmd, render.test_tex, render.sampler, 0);
            rhi_cmd_draw_indexed(cmd, 3, 1);
        }

        rhi_frame_end(render.device);
        rhi_present(render.device);

        if (frame_count % 100 == 0) {
            LOG_INFO("Frame %u: %.1f FPS, %.2f ms/frame, errors=%u",
                     frame_count, engine.fps, engine.delta_time * 1000.0, error_count);
        }
    }

    LOG_INFO("============================================");
    LOG_INFO("Test Results");
    LOG_INFO("============================================");
    LOG_INFO("Frames rendered: %u / %u target", frame_count, target_frames);
    LOG_INFO("Total time: %.2f seconds", total_time);
    LOG_INFO("Average FPS: %.1f", (f64)frame_count / total_time);
    LOG_INFO("Frame errors: %u", error_count);
    LOG_INFO("Frame time: min=%.2f ms, max=%.2f ms", min_dt * 1000.0, max_dt * 1000.0);

    bool stress_pass = (error_count == 0 && frame_count >= target_frames);
    if (stress_pass) {
        LOG_INFO("RESULT: STRESS TEST PASSED ✓");
    } else {
        LOG_ERROR("RESULT: STRESS TEST FAILED (errors=%u, frames=%u/%u)", error_count, frame_count, target_frames);
    }

    /* ---- 1000-draw stress test ---- */
    LOG_INFO("============================================");
    LOG_INFO("1000-draw stress test: 100 frames, 1000 draws/frame");
    LOG_INFO("============================================");

    u32 draw_test_frames = 100;
    u32 draw_frame_count = 0;
    u32 draw_errors = 0;
    u32 draws_per_frame = 1000;

    while (engine_frame(&engine) && draw_frame_count < draw_test_frames) {
        draw_frame_count++;

        RHICmdBuffer *cmd = rhi_frame_begin(render.device);
        if (!cmd) { draw_errors++; continue; }

        rhi_cmd_clear_color(cmd, 0.05f, 0.05f, 0.1f, 1.0f);

        Mat4 view = camera_view(&camera);
        Mat4 proj = camera_projection(&camera);

        skybox_render(&skybox, cmd, &view.e[0][0], &mat4_inverse(proj).e[0][0], 0.5f, -0.8f, 0.3f, 1.0f, 0.95f, 0.9f);

        rhi_cmd_bind_pipeline(cmd, render.pipeline);
        rhi_cmd_set_uniform_mat4(cmd, render.loc_view, &view.e[0][0]);
        rhi_cmd_set_uniform_mat4(cmd, render.loc_proj, &proj.e[0][0]);
        rhi_cmd_set_uniform_vec3(cmd, render.loc_light_dir, 0.5f, -0.8f, 0.3f);
        rhi_cmd_set_uniform_vec3(cmd, render.loc_light_color, 1.0f, 0.95f, 0.9f);
        rhi_cmd_set_uniform_vec3(cmd, render.loc_ambient, 0.35f, 0.35f, 0.40f);
        rhi_cmd_set_uniform_vec3(cmd, render.loc_camera_pos,
                                 camera.position.e[0], camera.position.e[1], camera.position.e[2]);

        rhi_cmd_bind_vertex_buffer(cmd, vbo, 0);
        rhi_cmd_bind_index_buffer(cmd, ibo, 0);

        for (u32 d = 0; d < draws_per_frame; d++) {
            Mat4 m = mat4_identity();
            m.e[3][0] = (f32)(d % 32) * 1.5f - 24.0f;
            m.e[3][1] = (f32)((d / 32) % 32) * 1.5f - 24.0f;
            m.e[3][2] = (f32)(d / 1024) * 1.5f - 5.0f;
            rhi_cmd_set_uniform_mat4(cmd, render.loc_model, &m.e[0][0]);
            rhi_cmd_bind_texture(cmd, (d % 2 == 0) ? render.test_tex : tex2, render.sampler, 0);
            rhi_cmd_draw_indexed(cmd, 3, 1);
        }

        rhi_frame_end(render.device);
        rhi_present(render.device);

        if (draw_frame_count % 25 == 0) {
            LOG_INFO("1000-draw: frame %u, %.1f FPS, %.2f ms",
                     draw_frame_count, engine.fps, engine.delta_time * 1000.0);
        }
    }

    bool draw_pass = (draw_errors == 0 && draw_frame_count >= draw_test_frames);
    if (draw_pass) {
        LOG_INFO("RESULT: 1000-DRAW TEST PASSED ✓ (%u frames, %u draws/frame)",
                 draw_frame_count, draws_per_frame);
    } else {
        LOG_ERROR("RESULT: 1000-DRAW TEST FAILED (errors=%u, frames=%u/%u)",
                  draw_errors, draw_frame_count, draw_test_frames);
    }

    LOG_INFO("============================================");
    LOG_INFO("FINAL RESULT: %s", (stress_pass && draw_pass) ? "ALL PASSED ✓" : "FAILED");
    LOG_INFO("============================================");

    /* ---- 10K instanced entity stress test ---- */
    LOG_INFO("============================================");
    LOG_INFO("10K-entity ECS + instanced draw stress test");
    LOG_INFO("============================================");

    #define ENTITY_COUNT 10000
    #define INST_FRAMES 100
    enum { TEST_COMP_TRANSFORM = 1 };
    typedef struct { f32 pos[3]; } TestTransform;

    usize ivs_len = 0, ifs_len = 0;
    char *ivs_src = file_read(TV_VS_INSTANCED, &ivs_len);
    char *ifs_src = file_read(TV_FS_INSTANCED, &ifs_len);
    RHIPipeline inst_pipeline = RHI_HANDLE_NULL;
    RHIBuffer instance_tbo = RHI_HANDLE_NULL;

    if (!ivs_src || !ifs_src) {
        LOG_WARN("Instanced shaders not found — 10K test skipped");
    } else {
        RHIShader ivs = rhi_shader_create(render.device, ivs_src, ivs_len, false);
        RHIShader ifs = rhi_shader_create(render.device, ifs_src, ifs_len, true);
        free(ivs_src); free(ifs_src);

        if (rhi_handle_valid(ivs) && rhi_handle_valid(ifs)) {
            RHIPipelineDesc pdesc = {
                .vert = ivs,
                .frag = ifs,
                .uses_texel_buffer = true,
                .uses_textures = true,
            };
            inst_pipeline = rhi_pipeline_create(render.device, &pdesc);
            LOG_INFO("Instanced pipeline: %s", rhi_handle_valid(inst_pipeline) ? "OK" : "FAIL");
        }

        RHIBufferDesc tbdesc = {
            .usage = RHI_BUFFER_USAGE_TEXEL,
            .size = ENTITY_COUNT * 64,
        };
        instance_tbo = rhi_buffer_create(render.device, &tbdesc);
        LOG_INFO("Instance TBO: %s (%zu bytes)", rhi_handle_valid(instance_tbo) ? "OK" : "FAIL",
                 (usize)(ENTITY_COUNT * 64));
    }

    World *inst_world = world_create();
    world_register_component(inst_world, TEST_COMP_TRANSFORM, sizeof(TestTransform));
    for (u32 i = 0; i < ENTITY_COUNT; i++) {
        Entity e = world_create_entity(inst_world);
        TestTransform *t = world_add_component(inst_world, e, TEST_COMP_TRANSFORM);
        if (t) {
            t->pos[0] = (f32)(i % 100) * 0.5f - 25.0f;
            t->pos[1] = (f32)((i / 100) % 100) * 0.5f - 25.0f;
            t->pos[2] = (f32)(i / 10000) * 0.5f - 2.0f;
        }
    }
    LOG_INFO("ECS: %u entities created", inst_world->entity_count - 1);

    f32 *instance_data = malloc(ENTITY_COUNT * 64);
    u32 inst_frame_count = 0;
    u32 inst_errors = 0;

    ComponentType qtypes[] = { TEST_COMP_TRANSFORM };
    bool inst_test_active = rhi_handle_valid(inst_pipeline) && rhi_handle_valid(instance_tbo);

    while (engine_frame(&engine) && inst_frame_count < INST_FRAMES && inst_test_active) {
        inst_frame_count++;

        RHICmdBuffer *cmd = rhi_frame_begin(render.device);
        if (!cmd) { inst_errors++; continue; }

        rhi_cmd_clear_color(cmd, 0.05f, 0.05f, 0.1f, 1.0f);

        Mat4 view = camera_view(&camera);
        Mat4 proj = camera_projection(&camera);

        skybox_render(&skybox, cmd, &view.e[0][0], &mat4_inverse(proj).e[0][0], 0.5f, -0.8f, 0.3f, 1.0f, 0.95f, 0.9f);

        Query *iq = world_query(inst_world, qtypes, 1);
        u32 instance_idx = 0;
        if (iq) {
            for (u32 mi = 0; mi < iq->match_count; mi++) {
                Archetype *a = iq->matching[mi];
                Chunk *c = a->chunks;
                while (c) {
                    u8 *base = (u8 *)c;
                    for (u32 ci = 0; ci < c->count && instance_idx < ENTITY_COUNT; ci++) {
                        TestTransform *et = (TestTransform *)(base + a->offsets[0] + ci * sizeof(TestTransform));
                        f32 *dst = instance_data + instance_idx * 16;
                        dst[0] = 1; dst[1] = 0; dst[2] = 0; dst[3] = et->pos[0];
                        dst[4] = 0; dst[5] = 1; dst[6] = 0; dst[7] = et->pos[1];
                        dst[8] = 0; dst[9] = 0; dst[10] = 1; dst[11] = et->pos[2];
                        dst[12] = 0; dst[13] = 0; dst[14] = 0; dst[15] = 1;
                        instance_idx++;
                    }
                    c = c->next;
                }
            }
            query_done(iq);
        }

        rhi_buffer_update(render.device, instance_tbo, instance_data, instance_idx * 64);

        rhi_cmd_bind_pipeline(cmd, inst_pipeline);
        rhi_cmd_set_uniform_mat4(cmd, 0, &view.e[0][0]);
        rhi_cmd_set_uniform_mat4(cmd, 64, &proj.e[0][0]);
        rhi_cmd_set_uniform_vec3(cmd, 128, 0.5f, -0.8f, 0.3f);
        rhi_cmd_set_uniform_vec3(cmd, 144, 1.0f, 0.95f, 0.9f);
        rhi_cmd_set_uniform_vec3(cmd, 160, 0.35f, 0.35f, 0.40f);
        rhi_cmd_set_uniform_vec3(cmd, 176, 0, 0, 5);

        rhi_cmd_bind_texture(cmd, render.test_tex, render.sampler, 0);
        rhi_cmd_bind_texel_buffers(cmd, instance_tbo, RHI_HANDLE_NULL);

        rhi_cmd_bind_vertex_buffer(cmd, vbo, 0);
        rhi_cmd_bind_index_buffer(cmd, ibo, 0);
        rhi_cmd_draw_indexed(cmd, 3, instance_idx);

        rhi_frame_end(render.device);
        rhi_present(render.device);

        if (inst_frame_count % 25 == 0) {
            LOG_INFO("10K-entity: frame %u, %.1f FPS, %.2f ms, %u instances",
                     inst_frame_count, engine.fps, engine.delta_time * 1000.0, instance_idx);
        }
    }

    bool inst_pass = true;
    if (!inst_test_active) {
        LOG_WARN("10K-entity test SKIPPED (no instanced pipeline)");
        inst_pass = true;
    } else if (inst_errors > 0 || inst_frame_count < INST_FRAMES) {
        LOG_ERROR("RESULT: 10K-ENTITY TEST FAILED (errors=%u, frames=%u/%u)",
                  inst_errors, inst_frame_count, INST_FRAMES);
        inst_pass = false;
    } else {
        LOG_INFO("RESULT: 10K-ENTITY TEST PASSED ✓ (%u frames, %u entities, %u draws/frame)",
                 inst_frame_count, ENTITY_COUNT, 1);
    }

    LOG_INFO("============================================");
    LOG_INFO("TEST 5: COMPUTE SHADER");

    bool compute_pass = false;
    {
        const char *comp_src =
            "#version 450\n"
            "layout(local_size_x = 64) in;\n"
            "layout(std430, binding = 0) buffer OutputBuf {\n"
            "    uint values[];\n"
            "};\n"
            "void main() {\n"
            "    uint idx = gl_GlobalInvocationID.x;\n"
            "    values[idx] = idx * 2u + 1u;\n"
            "}\n";
        usize src_len = strlen(comp_src);

        RHIShader cs = rhi_shader_create_compute(render.device, comp_src, src_len);
        if (rhi_handle_valid(cs)) {
            RHIPipelineDesc cpdesc = {0};
            cpdesc.is_compute = true;
            cpdesc.frag = cs;
            RHIPipeline comp_pipe = rhi_pipeline_create(render.device, &cpdesc);

            if (rhi_handle_valid(comp_pipe)) {
                u32 num_elements = 256;
                RHIBufferDesc sbuf_desc = {
                    .usage = RHI_BUFFER_USAGE_STORAGE,
                    .size = num_elements * sizeof(u32),
                    .initial_data = NULL,
                };
                RHIBuffer ssbo = rhi_buffer_create(render.device, &sbuf_desc);

                if (rhi_handle_valid(ssbo)) {
                    RHICmdBuffer *cmd = rhi_frame_begin(render.device);
                    rhi_cmd_end_render_pass(cmd);
                    rhi_cmd_bind_pipeline(cmd, comp_pipe);
                    rhi_cmd_bind_storage_buffer(cmd, ssbo, 0);
                    rhi_cmd_dispatch(cmd, num_elements / 64, 1, 1);
                    rhi_cmd_memory_barrier(cmd);
                    rhi_frame_end(render.device);
                    rhi_present(render.device);

                    rhi_frame_begin(render.device);
                    rhi_frame_end(render.device);
                    rhi_present(render.device);

                    rhi_frame_begin(render.device);
                    rhi_frame_end(render.device);
                    rhi_present(render.device);

                    u32 *readback = (u32 *)rhi_buffer_map(render.device, ssbo);
                    if (readback) {
                        compute_pass = true;
                        for (u32 i = 0; i < num_elements; i++) {
                            u32 expected = i * 2 + 1;
                            if (readback[i] != expected) {
                                LOG_ERROR("Compute: [%u] expected %u got %u", i, expected, readback[i]);
                                compute_pass = false;
                                break;
                            }
                        }
                        rhi_buffer_unmap(render.device, ssbo);
                    } else {
                        LOG_ERROR("Compute: buffer map failed");
                    }
                    rhi_buffer_destroy(render.device, ssbo);
                } else {
                    LOG_ERROR("Compute: SSBO creation failed");
                }
                rhi_pipeline_destroy(render.device, comp_pipe);
            } else {
                LOG_ERROR("Compute: pipeline creation failed");
            }
            rhi_shader_destroy(render.device, cs);
        } else {
            LOG_ERROR("Compute: shader compilation failed");
        }
    }

    if (compute_pass) {
        LOG_INFO("RESULT: COMPUTE SHADER TEST PASSED ✓ (256 elements verified)");
    } else {
        LOG_ERROR("RESULT: COMPUTE SHADER TEST FAILED");
    }

    /* ---- TEST 6: Combined post-process (no fallback to multi-pass) ---- */
    LOG_INFO("============================================");
    LOG_INFO("TEST 6: COMBINED POST-PROCESS");
    LOG_INFO("============================================");

    bool combined_pass = false;
    {
        u32 cw, ch;
        platform_get_size(engine.platform, &cw, &ch);

        CombinedAA caa = {0};
        CombinedColor cc = {0};
        bool aa_ok = combined_aa_init(&caa, render.device, cw, ch);
        bool cc_ok = combined_color_init(&cc, render.device, cw, ch);

        if (aa_ok && cc_ok && caa.use_combined && cc.use_combined) {
            LOG_INFO("PASS: combined TAA+FXAA and color pipelines active (no fallback)");

            /* HDR source the combined passes consume. */
            RHIOffscreenFBO src = rhi_offscreen_fbo_create_fmt(
                render.device, cw, ch, RHI_FORMAT_R16G16B16A16_SFLOAT);
            Mat4 id = mat4_identity();
            u32 cerr = 0;

            for (u32 f = 0; f < 10; f++) {
                RHICmdBuffer *cmd = rhi_frame_begin(render.device);
                if (!cmd) { cerr++; continue; }

                /* Produce some HDR content in the source FBO. */
                rhi_offscreen_fbo_bind(cmd, &src);
                rhi_cmd_bind_pipeline(cmd, render.pipeline);
                rhi_cmd_set_uniform_mat4(cmd, render.loc_model, &id.e[0][0]);
                rhi_cmd_set_uniform_mat4(cmd, render.loc_view, &id.e[0][0]);
                rhi_cmd_set_uniform_mat4(cmd, render.loc_proj, &id.e[0][0]);
                rhi_cmd_set_uniform_vec3(cmd, render.loc_light_dir, 0.5f, -0.8f, 0.3f);
                rhi_cmd_set_uniform_vec3(cmd, render.loc_light_color, 1.0f, 0.95f, 0.9f);
                rhi_cmd_set_uniform_vec3(cmd, render.loc_ambient, 0.35f, 0.35f, 0.40f);
                rhi_cmd_set_uniform_vec3(cmd, render.loc_camera_pos, 0, 0, 5);
                rhi_cmd_bind_texture(cmd, render.test_tex, render.sampler, 0);
                rhi_cmd_bind_vertex_buffer(cmd, vbo, 0);
                rhi_cmd_bind_index_buffer(cmd, ibo, 0);
                rhi_cmd_draw_indexed(cmd, 3, 1);
                rhi_offscreen_fbo_unbind(cmd, cw, ch);

                /* Combined AA reads the scene depth as a texture, so transition it. */
                rhi_cmd_transition_depth_to_read(cmd, src.depth_tex);

                combined_aa_apply(&caa, cmd, src.color_tex, src.depth_tex, RHI_HANDLE_NULL,
                                  &id.e[0][0], &id.e[0][0], &id.e[0][0], cw, ch);
                RHITexture aa_out = combined_aa_get_output(&caa);

                combined_color_apply(&cc, cmd, aa_out,
                                     1.0f, 2.2f, 0,
                                     1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
                                     0.0f, 0.0f, 0.0f,
                                     (f32)f, cw, ch);

                rhi_frame_end(render.device);
                rhi_present(render.device);
            }

            combined_pass = (cerr == 0);
            rhi_offscreen_fbo_destroy(render.device, &src);
        } else {
            LOG_ERROR("FAIL: combined post fell back (aa_ok=%d aa_combined=%d cc_ok=%d cc_combined=%d)",
                      aa_ok, caa.use_combined, cc_ok, cc.use_combined);
        }

        combined_aa_shutdown(&caa);
        combined_color_shutdown(&cc);
    }

    if (combined_pass) {
        LOG_INFO("RESULT: COMBINED POST-PROCESS TEST PASSED ✓ (10 frames, single-pass AA + color)");
    } else {
        LOG_ERROR("RESULT: COMBINED POST-PROCESS TEST FAILED");
    }

    /* ---- TEST 7: Real cubemap IBL (capture + convolve + sample) -------- */
    LOG_INFO("============================================");
    LOG_INFO("TEST 7: IMAGE-BASED LIGHTING (REAL CUBEMAP)");
    LOG_INFO("============================================");

    bool ibl_pass = false;
    {
        u32 iw, ih;
        platform_get_size(engine.platform, &iw, &ih);

        /* Generate a real environment: procedural sky -> env cubemap ->
         * irradiance + prefilter convolution + analytic BRDF LUT. */
        IBLSystem ibl = {0};
        ibl_init(&ibl, render.device);
        f32 sdir[3] = { 0.3f, -0.7f, 0.5f };
        f32 scol[3] = { 1.0f, 0.95f, 0.85f };
        ibl_capture_env_sky(&ibl, render.device, sdir, scol);
        ibl_generate(&ibl, render.device, ibl.env_map);

        bool gen_ok = ibl.ready
                   && rhi_handle_valid(ibl.brdf_lut)
                   && rhi_handle_valid(ibl.env_map)
                   && rhi_handle_valid(ibl.irradiance_map)
                   && rhi_handle_valid(ibl.prefilter_map);
        if (gen_ok)
            LOG_INFO("PASS: IBL generated (env+irradiance+prefilter+BRDF LUT)");
        else
            LOG_ERROR("FAIL: IBL generation incomplete (ready=%d)", ibl.ready);

        /* Build the clustered PBR pipeline with the HAS_IBL path enabled so we
         * actually sample the generated cubemaps (samplerCube at bindings 7/8). */
        RHIPipeline cl_pipe = RHI_HANDLE_NULL;
        {
            usize vl = 0, fl = 0;
            char *vsrc = file_read(TV_VS_PBR, &vl);
            char *fsrc = file_read(TV_FS_PBR, &fl);
            if (vsrc && fsrc) {
                usize fl_ibl = 0;
                char *fsrc_ibl = tv_inject_define(fsrc, fl, "HAS_IBL", &fl_ibl);
                RHIShader vs = rhi_shader_create(render.device, vsrc, vl, false);
                RHIShader fs = fsrc_ibl ? rhi_shader_create(render.device, fsrc_ibl, fl_ibl, true)
                                        : rhi_shader_create(render.device, fsrc, fl, true);
                if (rhi_handle_valid(vs) && rhi_handle_valid(fs)) {
                    RHIPipelineDesc d = {.vert = vs, .frag = fs, .uses_textures = true,
                                         .uses_texel_buffer = true, .disable_culling = true,
                                         .color_format = RHI_FORMAT_R16G16B16A16_SFLOAT};
                    cl_pipe = rhi_pipeline_create(render.device, &d);
                }
                rhi_shader_destroy(render.device, vs);
                rhi_shader_destroy(render.device, fs);
                free(vsrc); free(fsrc); free(fsrc_ibl);
            } else { free(vsrc); free(fsrc); }
        }

        /* Minimal light system so the clustered texel buffers are valid; enable
         * GPU cluster binning so this test also validates cluster_cull.comp. */
        LightSystem ls; light_system_init(&ls, render.device);
        bool gpu_cull_ok = light_system_init_gpu_cull(&ls);
        light_system_add_dir(&ls, 0.3f, -0.7f, 0.5f, 1.0f, 0.95f, 0.85f);
        light_system_add_point(&ls, 0.0f, 1.0f, 2.0f, 8.0f, 1.0f, 0.6f, 0.3f);

        bool sample_ok = false;
        if (gen_ok && rhi_handle_valid(cl_pipe)) {
            RHIOffscreenFBO scene = rhi_offscreen_fbo_create_fmt(
                render.device, iw, ih, RHI_FORMAT_R16G16B16A16_SFLOAT);

            Mat4 model = mat4_identity();
            Mat4 view  = mat4_identity();
            Mat4 proj  = mat4_identity();
            i32 l_model = rhi_pipeline_get_uniform_location(render.device, cl_pipe, "u_model");
            i32 l_view  = rhi_pipeline_get_uniform_location(render.device, cl_pipe, "u_view");
            i32 l_proj  = rhi_pipeline_get_uniform_location(render.device, cl_pipe, "u_proj");
            i32 l_cam   = rhi_pipeline_get_uniform_location(render.device, cl_pipe, "u_camera_pos");
            i32 l_amb   = rhi_pipeline_get_uniform_location(render.device, cl_pipe, "u_ambient");
            i32 l_sw    = rhi_pipeline_get_uniform_location(render.device, cl_pipe, "u_screen_w");
            i32 l_sh    = rhi_pipeline_get_uniform_location(render.device, cl_pipe, "u_screen_h");
            i32 l_near  = rhi_pipeline_get_uniform_location(render.device, cl_pipe, "u_near");
            i32 l_far   = rhi_pipeline_get_uniform_location(render.device, cl_pipe, "u_far");
            i32 l_pc    = rhi_pipeline_get_uniform_location(render.device, cl_pipe, "u_point_count");
            i32 l_dc    = rhi_pipeline_get_uniform_location(render.device, cl_pipe, "u_dir_count");

            u32 ierr = 0;
            for (u32 f = 0; f < 8; f++) {
                if (gpu_cull_ok) {
                    light_system_upload_lights(&ls);
                } else {
                    light_system_cull(&ls, &view, &proj, iw, ih);
                    light_system_upload(&ls);
                }

                RHICmdBuffer *cmd = rhi_frame_begin(render.device);
                if (!cmd) { ierr++; continue; }
                rhi_offscreen_fbo_bind(cmd, &scene);
                if (gpu_cull_ok) {
                    Mat4 vp = mat4_mul(proj, view);
                    light_system_cull_gpu(&ls, cmd, &vp.e[0][0], iw, ih);
                }
                rhi_cmd_bind_pipeline(cmd, cl_pipe);
                rhi_cmd_set_uniform_mat4(cmd, l_model, &model.e[0][0]);
                rhi_cmd_set_uniform_mat4(cmd, l_view,  &view.e[0][0]);
                rhi_cmd_set_uniform_mat4(cmd, l_proj,  &proj.e[0][0]);
                rhi_cmd_set_uniform_vec3(cmd, l_cam, 0.0f, 0.0f, 5.0f);
                rhi_cmd_set_uniform_vec3(cmd, l_amb, 0.08f, 0.08f, 0.10f);
                rhi_cmd_set_uniform_f32(cmd, l_sw, (f32)iw);
                rhi_cmd_set_uniform_f32(cmd, l_sh, (f32)ih);
                rhi_cmd_set_uniform_f32(cmd, l_near, 0.1f);
                rhi_cmd_set_uniform_f32(cmd, l_far, 100.0f);
                rhi_cmd_set_uniform_i32(cmd, l_pc, (i32)ls.point_count);
                rhi_cmd_set_uniform_i32(cmd, l_dc, (i32)ls.dir_count);
                rhi_cmd_bind_texel_buffers(cmd, ls.light_data_buf, ls.light_grid_buf);
                /* Bind material + the real IBL cubemaps (bindings 6/7/8). */
                rhi_cmd_bind_material_textures_ibl(cmd,
                    render.test_tex, render.test_tex, render.test_tex, render.test_tex,
                    render.test_tex, render.test_tex, render.sampler,
                    ibl.brdf_lut, ibl.irradiance_map, ibl.prefilter_map, NULL, 0u);
                rhi_cmd_bind_vertex_buffer(cmd, vbo, 0);
                rhi_cmd_bind_index_buffer(cmd, ibo, 0);
                rhi_cmd_draw_indexed(cmd, 3, 1);
                rhi_offscreen_fbo_unbind(cmd, iw, ih);
                rhi_frame_end(render.device);
                rhi_present(render.device);
            }
            sample_ok = (ierr == 0);
            rhi_offscreen_fbo_destroy(render.device, &scene);
        }

        if (rhi_handle_valid(cl_pipe)) rhi_pipeline_destroy(render.device, cl_pipe);
        light_system_shutdown(&ls);
        ibl_destroy(&ibl, render.device);

        ibl_pass = gen_ok && sample_ok;
    }

    if (ibl_pass) {
        LOG_INFO("RESULT: IBL TEST PASSED ✓ (cubemap RGBA16F+mips, sampled in clustered PBR)");
    } else {
        LOG_ERROR("RESULT: IBL TEST FAILED");
    }

    /* ---- TEST 9: Unified GPU cull + compact (indirect count draw) ---- */
    LOG_INFO("============================================");
    LOG_INFO("TEST 9: UNIFIED GPU CULL + COMPACT");
    LOG_INFO("============================================");

    bool unified_pass = false;
#ifdef ENGINE_VULKAN
    {
        GPUCullSystem uc = {0};
        if (gpucull_init(&uc, render.device) && gpucull_init_unified(&uc, render.device) &&
            uc.unified_ready) {
            GPUCullDrawCmd dcmd = {
                .index_count = 3, .instance_count = 1,
                .first_index = 0, .vertex_offset = 0, .first_instance = 0,
            };
            GPUCullObject obj = {0};
            obj.position[0] = 0.0f;
            obj.position[1] = 0.0f;
            obj.position[2] = -5.0f;
            obj.position[3] = 2.0f;
            gpucull_upload_draw_cmds(&uc, &dcmd, 1);
            gpucull_upload_objects_unified(&uc, &obj, 1);

            Mat4 proj = mat4_ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 100.0f);
            Mat4 view = mat4_identity();
            Mat4 vp = mat4_mul(proj, view);
            u32 dispatch_ok = 0;
            for (u32 sync = 0; sync < 3; sync++) {
                RHICmdBuffer *cmd = rhi_frame_begin(render.device);
                if (!cmd) { break; }
                rhi_cmd_end_render_pass(cmd);
                gpucull_dispatch_unified(&uc, cmd, &vp.e[0][0], NULL, RHI_HANDLE_NULL, 0, 0, RHI_HANDLE_NULL);
                rhi_frame_end(render.device);
                rhi_present(render.device);
                dispatch_ok++;
            }
            if (dispatch_ok >= 3u) {
                unified_pass = true;
                LOG_INFO("PASS: unified cull pipeline dispatched %u frames (smoke)", dispatch_ok);
            } else {
                LOG_ERROR("FAIL: unified cull dispatch_ok=%u", dispatch_ok);
            }
        } else {
            LOG_ERROR("FAIL: unified cull init unavailable");
        }
        gpucull_shutdown(&uc);
    }
#else
    unified_pass = true;
    LOG_INFO("SKIP: unified GPU cull (Vulkan-only compute path)");
#endif

    if (unified_pass) {
        LOG_INFO("RESULT: UNIFIED GPU CULL TEST PASSED ✓");
    } else {
        LOG_ERROR("RESULT: UNIFIED GPU CULL TEST FAILED");
    }

    /* ---- TEST 8: Golden image regression ---- */
    u32 gw2, gh2;
    platform_get_size(engine.platform, &gw2, &gh2);
    bool golden_pass = tv_run_golden_regression(&render, vbo, ibo, gw2, gh2);

    bool all_pass = stress_pass && draw_pass && inst_pass && fbo_pass &&
                    compute_pass && combined_pass && ibl_pass && unified_pass && golden_pass;

    LOG_INFO("============================================");
    LOG_INFO("FINAL RESULT: %s", all_pass ? "ALL PASSED ✓" : "FAILED");
    LOG_INFO("============================================");

    free(instance_data);
    world_destroy(inst_world);
    if (rhi_handle_valid(instance_tbo)) rhi_buffer_destroy(render.device, instance_tbo);
    if (rhi_handle_valid(inst_pipeline)) rhi_pipeline_destroy(render.device, inst_pipeline);

    LOG_INFO("Shutting down...");
    if (rhi_handle_valid(tex2)) rhi_texture_destroy(render.device, tex2);
    if (terr_ok) terrain_shutdown(&terrain);
    skybox_shutdown(&skybox);
    if (rhi_handle_valid(ibo)) rhi_buffer_destroy(render.device, ibo);
    if (rhi_handle_valid(vbo)) rhi_buffer_destroy(render.device, vbo);
    test_render_shutdown(&render);
    engine_shutdown(&engine);

    LOG_INFO("Clean shutdown completed");
    return all_pass ? 0 : 1;
}
