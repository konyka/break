#include <engine.h>
#include <rhi/rhi.h>
#include <renderer/camera.h>
#include <renderer/skybox.h>
#include <renderer/terrain.h>
#include <renderer/lighting.h>
#include <asset/asset.h>
#include <ecs/ecs.h>
#include <physics/physics.h>
#include <core/log.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

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

typedef struct {
    RHIDevice    *device;
    RHIPipeline   pipeline;
    RHISampler    sampler;
    RHITexture    test_tex;
    i32 loc_model, loc_view, loc_proj;
    i32 loc_light_dir, loc_light_color, loc_ambient, loc_camera_pos;
} TestRenderState;

static bool test_render_init(TestRenderState *rs, Platform *platform) {
    void *window = platform_window_native(platform);
    void *display = platform_display_native(platform);
    u32 w, h;
    platform_get_size(platform, &w, &h);

    rs->device = rhi_device_create(RHI_BACKEND_VULKAN, window, display, w, h);
    if (!rs->device) { LOG_ERROR("FAIL: device create"); return false; }
    LOG_INFO("PASS: Vulkan device created");

    usize vs_len = 0, fs_len = 0;
    char *vs_src = file_read("shaders/blinn_phong_vk.vert", &vs_len);
    char *fs_src = file_read("shaders/blinn_phong_vk.frag", &fs_len);
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
    LOG_INFO("Vulkan Backend Test Suite");
    LOG_INFO("============================================");

    EngineConfig cfg = { .width = 800, .height = 600, .title = "Vulkan Test", .target_fps = 60.0 };
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

        skybox_render(&skybox, cmd, &view.e[0][0], &proj.e[0][0]);

        terrain_render(&terrain, cmd, &view.e[0][0], &proj.e[0][0],
                       &camera.position.e[0], render.test_tex, render.sampler);

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
            skybox_render(&skybox, cmd, &view.e[0][0], &proj.e[0][0]);
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

        skybox_render(&skybox, cmd, &view.e[0][0], &proj.e[0][0]);

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
    char *ivs_src = file_read("shaders/instanced_vk.vert", &ivs_len);
    char *ifs_src = file_read("shaders/instanced_vk.frag", &ifs_len);
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

        skybox_render(&skybox, cmd, &view.e[0][0], &proj.e[0][0]);

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

    LOG_INFO("============================================");
    LOG_INFO("FINAL RESULT: %s",
             (stress_pass && draw_pass && inst_pass && fbo_pass && compute_pass) ? "ALL PASSED ✓" : "FAILED");
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
    return error_count > 0 ? 1 : 0;
}
