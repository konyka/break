#include <engine.h>
#include <rhi/rhi.h>
#include <renderer/camera.h>
#include <renderer/skybox.h>
#include <renderer/terrain.h>
#include <renderer/lighting.h>
#include <renderer/combined_post_process.h>
#include <renderer/gpucull.h>
#include <renderer/ibl.h>
#include <renderer/indirect_draw.h> /* R437: TEST 10 grouped compact gate */
#include <renderer/occlusion_cull.h> /* R436: TEST 9 Hi-Z occlusion assertions */
#include <asset/asset.h>
#include <ecs/ecs.h>
#include <physics/physics.h>
#include <core/log.h>
#include <core/shader_io.h>
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

/* R441: CPU nearest-neighbour RGBA8 resample (texture-array layer baking —
 * mirrors the MatArraySet layer resample in main.c). R442: used by the TEST 11
 * body on BOTH backends now (the suite is shared, see tv_test_material_array). */
static void tv_resample_nearest_rgba8(const u8 *src, u32 sw, u32 sh,
                                      u8 *dst, u32 dw, u32 dh) {
    for (u32 y = 0; y < dh; y++) {
        u32 sy = y * sh / dh;
        for (u32 x = 0; x < dw; x++) {
            u32 sx = x * sw / dw;
            memcpy(dst + ((usize)y * dw + x) * 4u, src + ((usize)sy * sw + sx) * 4u, 4u);
        }
    }
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
#define GOLDEN_CAM_PATH "tests/golden/test_vulkan_vk_cam.ppm"
#define TV_BACKEND        RHI_BACKEND_VULKAN
#define TV_VS_BLINN       "shaders/blinn_phong_vk.vert"
#define TV_FS_BLINN       "shaders/blinn_phong_vk.frag"
#define TV_VS_INSTANCED   "shaders/instanced_vk.vert"
#define TV_FS_INSTANCED   "shaders/instanced_vk.frag"
#define TV_VS_PBR         "shaders/pbr_clustered_vk.vert"
#define TV_FS_PBR         "shaders/pbr_clustered_vk.frag"
#define TV_VS_BLINN_ARR   "shaders/blinn_phong_arr_vk.vert"  /* R441/R442 TEST 11 */
#define TV_FS_BLINN_ARR   "shaders/blinn_phong_arr_vk.frag"
#define TV_VS_GBUFFER_ARR "shaders/gbuffer_arr_vk.vert"      /* R442 TEST 12 */
#define TV_FS_GBUFFER_ARR "shaders/gbuffer_arr_vk.frag"
#define TV_SUITE_NAME     "Vulkan Backend Test Suite"
#define TV_WINDOW_TITLE   "Vulkan Test"
#else
#define GOLDEN_PATH "tests/golden/test_vulkan_gl.ppm"
#define GOLDEN_CAM_PATH "tests/golden/test_vulkan_gl_cam.ppm"
#define TV_BACKEND        RHI_BACKEND_OPENGL
#define TV_VS_BLINN       "shaders/blinn_phong.vert"
#define TV_FS_BLINN       "shaders/blinn_phong.frag"
#define TV_VS_INSTANCED   "shaders/instanced.vert"
#define TV_FS_INSTANCED   "shaders/instanced.frag"
#define TV_VS_PBR         "shaders/pbr_clustered.vert"
#define TV_FS_PBR         "shaders/pbr_clustered.frag"
#define TV_VS_BLINN_ARR   "shaders/blinn_phong_arr.vert"     /* R442: GL TEST 11 */
#define TV_FS_BLINN_ARR   "shaders/blinn_phong_arr.frag"
#define TV_VS_GBUFFER_ARR "shaders/gbuffer_arr.vert"         /* R442: GL TEST 12 */
#define TV_FS_GBUFFER_ARR "shaders/gbuffer_arr.frag"
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
    usize gbytes = (usize)GOLDEN_GW * GOLDEN_GH * 3;
    bool ok = fwrite(grid, 1, gbytes, f) == gbytes;
    fclose(f);
    if (!ok) return false;
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

/* Capture the presented frame, downsample, and compare against (or, with
 * GOLDEN_UPDATE=1, write) the reference PPM at `path`.
 * `reject_blank`: fail when the captured grid is a single flat color —
 * a blank reference/compare is layout-insensitive and silently useless
 * (R438: the camera golden was blank for exactly this reason). */
static bool golden_capture_compare(RHIDevice *device, const char *path, u32 w, u32 h,
                                   bool reject_blank) {
    bool golden_pass = false;
    u8 *shot = (u8 *)malloc((usize)w * h * 4u);
    if (shot) {
        rhi_screenshot(device, 0, 0, w, h, shot);
        u8 grid[GOLDEN_GW * GOLDEN_GH * 3];
        golden_downsample(shot, w, h, grid);
        free(shot);

        if (reject_blank) {
            bool varied = false;
            for (usize i = 3; i < sizeof(grid) && !varied; i += 3)
                if (grid[i] != grid[0] || grid[i+1] != grid[1] || grid[i+2] != grid[2])
                    varied = true;
            if (!varied) {
                LOG_ERROR("GOLDEN: %s captured a single flat color — blank image "
                          "cannot detect layout regressions", path);
                return false;
            }
        }

        bool update = (getenv("GOLDEN_UPDATE") != NULL);
        f64 mae = 0.0;
        u32 maxd = 0;
        int cmp = update ? -1 : golden_compare_ppm(path, grid, &mae, &maxd);
        if (cmp == -1) {
            if (golden_write_ppm(path, grid)) {
                LOG_WARN("GOLDEN: wrote reference %s (%dx%d) — rerun to compare",
                         path, GOLDEN_GW, GOLDEN_GH);
                golden_pass = true;
            } else {
                LOG_ERROR("GOLDEN: failed to write reference %s", path);
            }
        } else if (cmp == 0) {
            golden_pass = (mae <= 8.0 && maxd <= 56);
            LOG_INFO("GOLDEN: %s MAE=%.2f max=%u (tol MAE<=8.0 max<=56) -> %s",
                     path, mae, maxd, golden_pass ? "OK" : "DRIFT");
        } else {
            LOG_ERROR("GOLDEN: format/size mismatch in %s", path);
        }
    }
    return golden_pass;
}

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
        rhi_cmd_bind_index_buffer(cmd, ibo, 0, true);
        rhi_cmd_draw_indexed(cmd, 3, 1);
        rhi_frame_end(render->device);
        rhi_present(render->device);
    }

    bool golden_pass = golden_capture_compare(render->device, GOLDEN_PATH, w, h, false);
    if (golden_pass) {
        LOG_INFO("RESULT: GOLDEN IMAGE TEST PASSED ✓");
    } else {
        LOG_ERROR("RESULT: GOLDEN IMAGE TEST FAILED");
    }
    return golden_pass;
}

/* R438: golden variant with a fixed NON-IDENTITY camera. The identity
 * golden above is transpose-invariant (I == I^T) and can never catch a
 * view-matrix layout regression; this one renders the same triangle through
 * camera_view() + camera_projection() at a fixed off-axis pose, so any
 * layout/chirality change in the view matrix shifts the image and fails
 * the compare. */
static bool tv_run_golden_camera_regression(const TestRenderState *render, RHIBuffer vbo, RHIBuffer ibo,
                                            u32 w, u32 h) {
    LOG_INFO("============================================");
    LOG_INFO("TEST: GOLDEN IMAGE REGRESSION (NON-IDENTITY CAMERA)");
    LOG_INFO("============================================");

    Camera cam;
    camera_init(&cam, 1.047f, (f32)w / (f32)(h > 0 ? h : 1), 0.1f, 100.0f);
    /* Eye (2,1.5,4) looking back at the origin-centered triangle:
     * dir = normalize(-2,-1.5,-4) -> yaw = atan2(-0.438, 0.877) = -0.463,
     * pitch = asin(-0.312) = -0.317. The triangle must be ON-SCREEN —
     * a blank reference is layout-insensitive (verified R438). */
    cam.position = vec3(2.0f, 1.5f, 4.0f);
    cam.yaw = -0.463f;
    cam.pitch = -0.317f;
    InputState dummy = {0};
    camera_update(&cam, &dummy, 0.0f); /* cache trig for camera_view */
    Mat4 model = mat4_identity();
    Mat4 view = camera_view(&cam);
    Mat4 proj = camera_projection(&cam);

    for (u32 f = 0; f < 3; f++) {
        RHICmdBuffer *cmd = rhi_frame_begin(render->device);
        if (!cmd) continue;
        rhi_cmd_clear_color(cmd, 0.10f, 0.10f, 0.15f, 1.0f);
        rhi_cmd_bind_pipeline(cmd, render->pipeline);
        rhi_cmd_set_uniform_mat4(cmd, render->loc_model, &model.e[0][0]);
        rhi_cmd_set_uniform_mat4(cmd, render->loc_view, &view.e[0][0]);
        rhi_cmd_set_uniform_mat4(cmd, render->loc_proj, &proj.e[0][0]);
        rhi_cmd_set_uniform_vec3(cmd, render->loc_light_dir, 0.5f, -0.8f, 0.3f);
        rhi_cmd_set_uniform_vec3(cmd, render->loc_light_color, 1.0f, 0.95f, 0.9f);
        rhi_cmd_set_uniform_vec3(cmd, render->loc_ambient, 0.35f, 0.35f, 0.40f);
        rhi_cmd_set_uniform_vec3(cmd, render->loc_camera_pos,
                                 cam.position.e[0], cam.position.e[1], cam.position.e[2]);
        rhi_cmd_bind_texture(cmd, render->test_tex, render->sampler, 0);
        rhi_cmd_bind_vertex_buffer(cmd, vbo, 0);
        rhi_cmd_bind_index_buffer(cmd, ibo, 0, true);
        rhi_cmd_draw_indexed(cmd, 3, 1);
        rhi_frame_end(render->device);
        rhi_present(render->device);
    }

    bool golden_pass = golden_capture_compare(render->device, GOLDEN_CAM_PATH, w, h, true);
    if (golden_pass) {
        LOG_INFO("RESULT: GOLDEN CAMERA IMAGE TEST PASSED ✓");
    } else {
        LOG_ERROR("RESULT: GOLDEN CAMERA IMAGE TEST FAILED");
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
    char *vs_src = shader_read_file(TV_VS_BLINN, &vs_len);
    char *fs_src = shader_read_file(TV_FS_BLINN, &fs_len);
    if (!vs_src || !fs_src) { LOG_ERROR("FAIL: shader load"); free(vs_src); free(fs_src); rhi_device_destroy(rs->device); rs->device = NULL; return false; }

    RHIShader vs = rhi_shader_create(rs->device, vs_src, vs_len, false);
    RHIShader fs = rhi_shader_create(rs->device, fs_src, fs_len, true);
    free(vs_src); free(fs_src);

    if (!rhi_handle_valid(vs) || !rhi_handle_valid(fs)) {
        LOG_ERROR("FAIL: shader compile");
        /* R425: destroy on the way out — the valid handle and the device
         * used to leak when only one shader compiled. */
        if (rhi_handle_valid(vs)) rhi_shader_destroy(rs->device, vs);
        if (rhi_handle_valid(fs)) rhi_shader_destroy(rs->device, fs);
        rhi_device_destroy(rs->device);
        rs->device = NULL;
        return false;
    }
    LOG_INFO("PASS: Shaders compiled (GLSL->SPIR-V)");

    /* R439: culling re-enabled — the view basis is now right-handed (det=+1),
     * so the golden triangle's CCW winding is front-facing again (under the
     * pre-flip left-handed basis it appeared CW and was culled, forcing
     * disable_culling). The reject_blank golden guard now double-duties as a
     * winding regression check: wrong chirality -> triangle culled -> blank. */
    RHIPipelineDesc pdesc = {.vert = vs, .frag = fs, .uses_textures = true};
    rs->pipeline = rhi_pipeline_create(rs->device, &pdesc);
    rhi_shader_destroy(rs->device, vs);
    rhi_shader_destroy(rs->device, fs);

    if (!rhi_handle_valid(rs->pipeline)) {
        LOG_ERROR("FAIL: pipeline create");
        /* R425: destroy the device on the way out. */
        rhi_device_destroy(rs->device);
        rs->device = NULL;
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
        /* R425: destroy pipeline + device on the way out. */
        rhi_pipeline_destroy(rs->device, rs->pipeline);
        rs->pipeline = RHI_HANDLE_NULL;
        rhi_device_destroy(rs->device);
        rs->device = NULL;
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

/* ========================================================================
 * R442: backend-neutral bodies of TEST 10/11/12. They were VK-only inline
 * blocks; the GL backend now has every RHI piece they need (texture arrays,
 * gl_BaseInstanceARB, compute compact, MRT FBO, glGetTexImage readback), so
 * both backends run the SAME code — only the shader file names (TV_*_ARR
 * macros) and the TEST 11 dark-tone thresholds differ.
 * ======================================================================== */

/* TEST 10 body: R437 grouped indirect_draw compact gate. */
static bool tv_test_grouped_compact(const TestRenderState *rs) {
    /* R437: regression gate for the merged per-material compact. 3 material
     * groups {3,3,2} = 8 cmds with mixed visibility; a single merged compact
     * must (a) report per-group visible counts {2,2,1} + total 5,
     * (b) scatter each group's visible cmds inside its CPU-known capacity
     * interval, (c) keep surplus slots zeroed (R234-B fallback safety),
     * (d) cost exactly 1 compact dispatch per frame for all groups. */
    IndirectDrawSystem ids;
    if (!indirect_draw_init_grouped(&ids, rs->device, 8, 3)) {
        LOG_ERROR("FAIL: indirect_draw_init_grouped unavailable");
        return false;
    }
    DrawIndexedIndirectCmd cmds[8];
    for (u32 i = 0; i < 8; i++) {
        cmds[i].index_count    = 3;
        cmds[i].instance_count = 1;
        cmds[i].first_index    = 0;
        cmds[i].vertex_offset  = 0;
        cmds[i].first_instance = 100u + i; /* marker identifying the cmd */
    }
    const u32 gsizes[3] = {3u, 3u, 2u};
    indirect_draw_upload_grouped(&ids, rs->device, cmds, gsizes, 3);
    /* group-sorted visibility: g0 {1,0,1} g1 {1,1,0} g2 {0,1} */
    const u32 vis[8] = {1u, 0u, 1u,  1u, 1u, 0u,  0u, 1u};

    indirect_draw_debug_reset_compact_count();
    u32 frames_ok = 0;
    for (u32 f = 0; f < 3; f++) {
        RHICmdBuffer *cmd = rhi_frame_begin(rs->device);
        if (!cmd) break;
        rhi_cmd_end_render_pass(cmd);
        indirect_draw_upload_visibility(&ids, rs->device, vis, 8);
        indirect_draw_compact_no_barrier(&ids, rs->device, cmd);
        rhi_cmd_memory_barrier(cmd);
        rhi_frame_end(rs->device);
        rhi_present(rs->device);
        frames_ok++;
    }
    u32 dispatches = indirect_draw_debug_compact_count();

    u32 counts[3] = {0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu};
    u32 total = 0xFFFFFFFFu;
    DrawIndexedIndirectCmd out[8];
    memset(out, 0xFF, sizeof(out));
    bool rd_ok =
        rhi_buffer_read(rs->device, ids.group_counts_buf, counts, 0, sizeof(counts)) &&
        rhi_buffer_read(rs->device, ids.draw_count_buf, &total, 0, sizeof(u32)) &&
        rhi_buffer_read(rs->device, ids.visible_draws_buf, out, 0, sizeof(out));

    bool counts_ok = rd_ok && counts[0] == 2u && counts[1] == 2u &&
                     counts[2] == 1u && total == 5u;
    if (!counts_ok)
        LOG_ERROR("FAIL: group counts {%u,%u,%u} total %u, want {2,2,1} total 5",
                  counts[0], counts[1], counts[2], total);

    /* Capacity intervals: visible markers must match the expected sets
     * (intra-group order is atomic-nondeterministic); surplus slots
     * must stay zeroed so the R234-B fallback cannot resurrect them. */
    bool intervals_ok = rd_ok;
    const u32 want[3][3] = { {100u, 102u, 0u}, {103u, 104u, 0u}, {107u, 0u, 0u} };
    const u32 bases[3]   = {0u, 3u, 6u};
    const u32 visn[3]    = {2u, 2u, 1u};
    const u32 caps[3]    = {3u, 3u, 2u};
    for (u32 g = 0; g < 3 && intervals_ok; g++) {
        u32 seen[3] = {0u, 0u, 0u};
        for (u32 s = 0; s < visn[g]; s++) {
            const DrawIndexedIndirectCmd *c = &out[bases[g] + s];
            if (c->index_count != 3u) { intervals_ok = false; break; }
            bool match = false;
            for (u32 w = 0; w < visn[g]; w++) {
                if (c->first_instance == want[g][w] && !seen[w]) {
                    seen[w] = 1u; match = true; break;
                }
            }
            if (!match) break;
        }
        for (u32 s = 0; s < visn[g]; s++)
            if (!seen[s]) intervals_ok = false;
        for (u32 s = visn[g]; s < caps[g]; s++) {
            const DrawIndexedIndirectCmd *c = &out[bases[g] + s];
            if (c->index_count != 0u || c->instance_count != 0u) intervals_ok = false;
        }
    }
    if (!intervals_ok)
        LOG_ERROR("FAIL: visible_draws intervals wrong (group packing / zero-fill)");

    bool dispatch_ok = (frames_ok == 3u) && (dispatches == frames_ok);
    if (!dispatch_ok)
        LOG_ERROR("FAIL: compact dispatches=%u over %u frames, want 1/frame (merged)",
                  dispatches, frames_ok);

    bool idraw_pass = counts_ok && intervals_ok && dispatch_ok;
    if (idraw_pass)
        LOG_INFO("PASS: grouped compact ({2,2,1}/5, intervals packed+zeroed, 1 dispatch/frame)");
    indirect_draw_destroy(&ids, rs->device);
    return idraw_pass;
}

/* TEST 11 body: R441 material texture-array single-execute forward.
 * scr_w/scr_h: presentable size for the screenshot readback. */
static bool tv_test_material_array(const TestRenderState *rs, u32 scr_w, u32 scr_h) {
    /* R441: end-to-end gate for the texture-array material-indirect path.
     * 4 quads (one per screen quadrant) draw through ONE indirect execute;
     * each cmd's first_instance carries the sampler2DArray layer:
     *   quad0 red 64x64 (upsampled to 128), quad1 green 128x128 native,
     *   quad2 blue 64x64 (upsampled, CULLED by visibility), quad3 layer 0
     * white fallback (no texture). Each texture is two-tone (left half
     * bright, right half dark) so a broken nearest-upsample shifts the
     * hue/intensity split and fails the per-quadrant pixel assertions. */
    bool setup_ok = false;
    RHIPipeline arr_pipe = RHI_HANDLE_NULL;
    RHITexture  arr_tex  = RHI_HANDLE_NULL;
    RHIBuffer   arr_vbo  = RHI_HANDLE_NULL, arr_ibo = RHI_HANDLE_NULL;
    IndirectDrawSystem ids;
    memset(&ids, 0, sizeof(ids));
    bool ids_ok = false;

    /* Two-tone 64x64 / 128x128 sources (left bright, right dark). */
    const u32 ARR_SZ = 128u; /* array layer size = max source size */
    u8 *tex_red   = malloc((usize)64 * 64 * 4u);
    u8 *tex_green = malloc((usize)128 * 128 * 4u);
    u8 *tex_blue  = malloc((usize)64 * 64 * 4u);
    u8 *layer_buf = malloc((usize)ARR_SZ * ARR_SZ * 4u);
    if (tex_red && tex_green && tex_blue && layer_buf) {
        for (u32 y = 0; y < 64; y++)
            for (u32 x = 0; x < 64; x++) {
                u8 *pr = &tex_red[((usize)y * 64 + x) * 4u];
                u8 *pb = &tex_blue[((usize)y * 64 + x) * 4u];
                bool left = x < 32u;
                pr[0] = left ? 255 : 76; pr[1] = 0; pr[2] = 0; pr[3] = 255;
                pb[0] = 0; pb[1] = 0; pb[2] = left ? 255 : 76; pb[3] = 255;
            }
        for (u32 y = 0; y < 128; y++)
            for (u32 x = 0; x < 128; x++) {
                u8 *pg = &tex_green[((usize)y * 128 + x) * 4u];
                pg[0] = 0; pg[1] = (x < 64u) ? 255 : 76; pg[2] = 0; pg[3] = 255;
            }

        arr_tex = rhi_texture_array_create(rs->device, ARR_SZ, ARR_SZ, 4u,
                                           RHI_FORMAT_R8G8B8A8_UNORM);
        if (rhi_handle_valid(arr_tex)) {
            /* Layer 0: white fallback (no-texture materials). */
            memset(layer_buf, 0xFF, (usize)ARR_SZ * ARR_SZ * 4u);
            rhi_texture_array_upload_layer(rs->device, arr_tex, 0u,
                                           layer_buf, (usize)ARR_SZ * ARR_SZ * 4u);
            /* Layers 1/3: 64x64 -> 128 nearest upsample; layer 2 native. */
            tv_resample_nearest_rgba8(tex_red, 64, 64, layer_buf, ARR_SZ, ARR_SZ);
            rhi_texture_array_upload_layer(rs->device, arr_tex, 1u,
                                           layer_buf, (usize)ARR_SZ * ARR_SZ * 4u);
            rhi_texture_array_upload_layer(rs->device, arr_tex, 2u,
                                           tex_green, (usize)128 * 128 * 4u);
            tv_resample_nearest_rgba8(tex_blue, 64, 64, layer_buf, ARR_SZ, ARR_SZ);
            rhi_texture_array_upload_layer(rs->device, arr_tex, 3u,
                                           layer_buf, (usize)ARR_SZ * ARR_SZ * 4u);

            /* 4 quads, one per NDC quadrant (pos3+nrm3+uv2, 32B stride).
             * Indices are LOCAL to each quad — vertex_offset in the cmd
             * applies the per-quad shift (mega-buffer convention). */
            f32 qv[4 * 4 * 8];
            u32 qi[4 * 6];
            const f32 qcx[4] = { -0.5f, 0.5f, -0.5f, 0.5f };
            const f32 qcy[4] = {  0.5f, 0.5f, -0.5f, -0.5f };
            for (u32 k = 0; k < 4; k++) {
                f32 x0 = qcx[k] - 0.45f, x1 = qcx[k] + 0.45f;
                f32 y0 = qcy[k] - 0.45f, y1 = qcy[k] + 0.45f;
                const f32 qpos[4][2] = { {x0, y0}, {x1, y0}, {x1, y1}, {x0, y1} };
                const f32 quv[4][2]  = { {0, 0}, {1, 0}, {1, 1}, {0, 1} };
                for (u32 v = 0; v < 4; v++) {
                    f32 *d = &qv[(k * 4 + v) * 8];
                    d[0] = qpos[v][0]; d[1] = qpos[v][1]; d[2] = 0.0f;
                    d[3] = 0.0f; d[4] = 0.0f; d[5] = 1.0f;
                    d[6] = quv[v][0]; d[7] = quv[v][1];
                }
                u32 *di = &qi[k * 6];
                di[0] = 0; di[1] = 1; di[2] = 2;
                di[3] = 0; di[4] = 2; di[5] = 3;
            }
            RHIBufferDesc qvb = { .usage = RHI_BUFFER_USAGE_VERTEX,
                                  .size = sizeof(qv), .initial_data = qv };
            RHIBufferDesc qib = { .usage = RHI_BUFFER_USAGE_INDEX,
                                  .size = sizeof(qi), .initial_data = qi };
            arr_vbo = rhi_buffer_create(rs->device, &qvb);
            arr_ibo = rhi_buffer_create(rs->device, &qib);

            usize avl = 0, afl = 0;
            char *avs = shader_read_file(TV_VS_BLINN_ARR, &avl);
            char *afs = shader_read_file(TV_FS_BLINN_ARR, &afl);
            if (avs && afs) {
                RHIShader svs = rhi_shader_create(rs->device, avs, avl, false);
                RHIShader sfs = rhi_shader_create(rs->device, afs, afl, true);
                if (rhi_handle_valid(svs) && rhi_handle_valid(sfs)) {
                    RHIPipelineDesc apd = { .vert = svs, .frag = sfs,
                                            .uses_textures = true };
                    arr_pipe = rhi_pipeline_create(rs->device, &apd);
                }
                if (rhi_handle_valid(svs)) rhi_shader_destroy(rs->device, svs);
                if (rhi_handle_valid(sfs)) rhi_shader_destroy(rs->device, sfs);
            }
            free(avs); free(afs);

            /* Ungrouped bake-order upload; first_instance = array layer.
             * quad2 (blue) gets layer 3 but is culled by visibility. */
            DrawIndexedIndirectCmd acmds[4];
            const u32 layers_of_quad[4] = { 1u, 2u, 3u, 0u };
            for (u32 k = 0; k < 4; k++) {
                acmds[k].index_count    = 6;
                acmds[k].instance_count = 1;
                acmds[k].first_index    = k * 6u;
                acmds[k].vertex_offset  = (i32)(k * 4u);
                acmds[k].first_instance = layers_of_quad[k];
            }
            ids_ok = indirect_draw_init(&ids, rs->device, 4);
            if (ids_ok) indirect_draw_upload(&ids, rs->device, acmds, 4);

            setup_ok = rhi_handle_valid(arr_pipe) && rhi_handle_valid(arr_vbo) &&
                       rhi_handle_valid(arr_ibo) && ids_ok;
        }
    }
    if (!setup_ok) {
        LOG_ERROR("FAIL: material-array setup (pipe=%d tex=%d vbo=%d ibo=%d ids=%d)",
                  (int)rhi_handle_valid(arr_pipe), (int)rhi_handle_valid(arr_tex),
                  (int)rhi_handle_valid(arr_vbo), (int)rhi_handle_valid(arr_ibo),
                  (int)ids_ok);
    }

    u32 exec_count = 0xFFFFFFFFu, frames_ok = 0;
    if (setup_ok) {
        i32 l_model = rhi_pipeline_get_uniform_location(rs->device, arr_pipe, "u_model");
        i32 l_view  = rhi_pipeline_get_uniform_location(rs->device, arr_pipe, "u_view");
        i32 l_proj  = rhi_pipeline_get_uniform_location(rs->device, arr_pipe, "u_proj");
        i32 l_ldir  = rhi_pipeline_get_uniform_location(rs->device, arr_pipe, "u_light_dir");
        i32 l_lcol  = rhi_pipeline_get_uniform_location(rs->device, arr_pipe, "u_light_color");
        i32 l_amb   = rhi_pipeline_get_uniform_location(rs->device, arr_pipe, "u_ambient");
        i32 l_cam   = rhi_pipeline_get_uniform_location(rs->device, arr_pipe, "u_camera_pos");
        Mat4 idm = mat4_identity();
        const u32 vis[4] = { 1u, 1u, 0u, 1u }; /* blue quad culled */

        indirect_draw_debug_reset_execute_count();
        for (u32 f = 0; f < 3; f++) {
            RHICmdBuffer *cmd = rhi_frame_begin(rs->device);
            if (!cmd) break;
            rhi_cmd_clear_color(cmd, 0.0f, 0.0f, 0.0f, 1.0f);
            indirect_draw_upload_visibility(&ids, rs->device, vis, 4);
            indirect_draw_compact_no_barrier(&ids, rs->device, cmd);
            rhi_cmd_memory_barrier(cmd);
            /* R234-A: rebind graphics pipeline after compact compute, and
             * only THEN set the push constants — a set before the compact
             * would be flushed (and consumed) by the compute dispatch. */
            rhi_cmd_bind_pipeline(cmd, arr_pipe);
            rhi_cmd_set_uniform_mat4(cmd, l_model, &idm.e[0][0]);
            rhi_cmd_set_uniform_mat4(cmd, l_view,  &idm.e[0][0]);
            rhi_cmd_set_uniform_mat4(cmd, l_proj,  &idm.e[0][0]);
            rhi_cmd_set_uniform_vec3(cmd, l_ldir, 0.0f, 0.0f, -1.0f);
            rhi_cmd_set_uniform_vec3(cmd, l_lcol, 1.0f, 1.0f, 1.0f);
            rhi_cmd_set_uniform_vec3(cmd, l_amb, 0.35f, 0.35f, 0.35f);
            rhi_cmd_set_uniform_vec3(cmd, l_cam, 0.0f, 0.0f, 5.0f);
            rhi_cmd_bind_material_textures_ibl(cmd,
                arr_tex, arr_tex, arr_tex, arr_tex, arr_tex, arr_tex,
                rs->sampler,
                RHI_HANDLE_NULL, RHI_HANDLE_NULL, RHI_HANDLE_NULL, NULL, 0u);
            rhi_cmd_bind_vertex_buffer(cmd, arr_vbo, 0);
            rhi_cmd_bind_index_buffer(cmd, arr_ibo, 0, true);
            indirect_draw_execute(&ids, rs->device);
            rhi_frame_end(rs->device);
            rhi_present(rs->device);
            frames_ok++;
        }
        exec_count = indirect_draw_debug_execute_count();
    }

    /* Readback: 4 quadrant samples (uv 0.25 / 0.75 per quad for the
     * two-tone split). Non-flipped viewport on both backends; the readback
     * row origin differs (VK top-down, GL bottom-up) but the NDC->row
     * formula lands on the same index under either convention (R442:
     * verified against both drivers). */
    bool pixels_ok = false;
    if (setup_ok && frames_ok == 3u) {
        u32 pw = scr_w, ph = scr_h;
        u8 *shot = malloc((usize)pw * ph * 4u);
        if (shot) {
            rhi_screenshot(rs->device, 0, 0, pw, ph, shot);
            /* quad k: NDC center (qcx,qcy) -> px = (x+1)/2*w, py = (y+1)/2*h */
            const f32 qcx[4] = { -0.5f, 0.5f, -0.5f, 0.5f };
            const f32 qcy[4] = {  0.5f, 0.5f, -0.5f, -0.5f };
            u8 rgb[4][2][3]; /* [quad][left/right sample][rgb] */
            for (u32 k = 0; k < 4; k++) {
                u32 by = (u32)((qcy[k] + 1.0f) * 0.5f * (f32)ph);
                /* uv 0.25 / 0.75 within the 0.9-NDC-wide quad. */
                u32 xl = (u32)((qcx[k] - 0.45f * 0.5f + 1.0f) * 0.5f * (f32)pw);
                u32 xr = (u32)((qcx[k] + 0.45f * 0.5f + 1.0f) * 0.5f * (f32)pw);
                if (by >= ph) by = ph - 1;
                if (xl >= pw) xl = pw - 1;
                if (xr >= pw) xr = pw - 1;
                const u8 *pl = &shot[((usize)by * pw + xl) * 4u];
                const u8 *pr = &shot[((usize)by * pw + xr) * 4u];
                rgb[k][0][0] = pl[0]; rgb[k][0][1] = pl[1]; rgb[k][0][2] = pl[2];
                rgb[k][1][0] = pr[0]; rgb[k][1][1] = pr[1]; rgb[k][1][2] = pr[2];
            }
            free(shot);

            /* Hue assertions, sRGB-aware. The VK swapchain encodes sRGB on
             * write, so the lit dark half (76/255 albedo) lands ~170-200
             * there; the GL default framebuffer is written RAW (nothing ever
             * enables GL_FRAMEBUFFER_SRGB), so the same dark half lands
             * ~120-135 linear (R442 — bounds calibrated against Mesa/i965).
             * bright half clamps to 255; the culled quad keeps the black
             * clear; the fallback layer is white. */
#ifdef ENGINE_VULKAN
            const u32 dark_lo = 120, dark_hi = 230;
#else
            const u32 dark_lo = 90, dark_hi = 200; /* R442: GL linear range */
#endif
            bool q0 = rgb[0][0][0] > 230 && rgb[0][0][1] < 140 && rgb[0][0][2] < 140 &&
                      rgb[0][1][0] > dark_lo && rgb[0][1][0] < dark_hi &&
                      rgb[0][1][0] + 40 < rgb[0][0][0];          /* red */
            bool q1 = rgb[1][0][1] > 230 && rgb[1][0][0] < 140 && rgb[1][0][2] < 140 &&
                      rgb[1][1][1] > dark_lo && rgb[1][1][1] < dark_hi &&
                      rgb[1][1][1] + 40 < rgb[1][0][1];          /* green */
            bool q2 = rgb[2][0][0] < 40 && rgb[2][0][1] < 40 && rgb[2][0][2] < 40 &&
                      rgb[2][1][0] < 40 && rgb[2][1][2] < 40;     /* culled = clear */
            bool q3 = rgb[3][0][0] > 230 && rgb[3][0][1] > 230 && rgb[3][0][2] > 230; /* white */
            pixels_ok = q0 && q1 && q2 && q3;
            if (!pixels_ok)
                LOG_ERROR("FAIL: quadrant pixels red{%u,%u} green{%u,%u} culled{%u,%u,%u} white{%u} "
                          "(want bright/dark split, black culled, white bright)",
                          rgb[0][0][0], rgb[0][1][0], rgb[1][0][1], rgb[1][1][1],
                          rgb[2][0][0], rgb[2][0][1], rgb[2][0][2], rgb[3][0][0]);
        }
    }

    bool exec_ok = (frames_ok == 3u) && (exec_count == frames_ok);
    if (!exec_ok)
        LOG_ERROR("FAIL: execute draws=%u over %u frames, want exactly 1/frame",
                  exec_count, frames_ok);

    bool matarr_pass = setup_ok && pixels_ok && exec_ok;
    if (matarr_pass)
        LOG_INFO("PASS: material-array single execute (4 layers incl. fallback, "
                 "1 execute/frame, quadrant pixels + two-tone upsample verified)");

    if (ids_ok) indirect_draw_destroy(&ids, rs->device);
    if (rhi_handle_valid(arr_pipe)) rhi_pipeline_destroy(rs->device, arr_pipe);
    if (rhi_handle_valid(arr_tex))  rhi_texture_destroy(rs->device, arr_tex);
    if (rhi_handle_valid(arr_ibo))  rhi_buffer_destroy(rs->device, arr_ibo);
    if (rhi_handle_valid(arr_vbo))  rhi_buffer_destroy(rs->device, arr_vbo);
    free(tex_red); free(tex_green); free(tex_blue); free(layer_buf);
    return matarr_pass;
}

/* TEST 12 body: R442 deferred G-buffer material-array single execute. */
static bool tv_test_deferred_gbuffer_array(const TestRenderState *rs) {
    /* R442: end-to-end gate for the deferred (G-buffer) texture-array
     * path. 4 quads (one per NDC quadrant) draw through ONE indirect
     * execute into a 4-attachment MRT matching the deferred G-Buffer
     * layout; each cmd's first_instance carries the sampler2DArray layer
     * shared by the albedo AND metallic-roughness arrays:
     *   quad0 layer1: red   albedo, MR metal=1.0 rough=0.1
     *   quad1 layer2: green albedo, MR metal=0.0 rough=0.9
     *   quad2 layer3: blue  albedo, MR metal=0.5 rough=0.5 (CULLED)
     *   quad3 layer0: white fallback albedo + neutral MR (metal=0,
     *                 rough=0.5 — the {255,128,0,255} neutral matching
     *                 main.c's fallback_mr).
     * Assertions (all pixel-level on the raw UNORM attachments, no sRGB):
     *   albedo_metallic (RT0): per-quadrant hue, alpha = metallic;
     *   roughness_ao    (RT2): r = roughness per layer, g = 255 (ao 1.0);
     *   exactly 1 indirect execute per frame. */
    const u32 GBW = 256u, GBH = 256u;
    bool setup_ok = false;
    RHIMRTFBO   gb_mrt;
    memset(&gb_mrt, 0, sizeof(gb_mrt));
    RHIPipeline gb_pipe = RHI_HANDLE_NULL;
    RHITexture  gb_alb_arr = RHI_HANDLE_NULL, gb_mr_arr = RHI_HANDLE_NULL;
    RHIBuffer   gb_vbo = RHI_HANDLE_NULL, gb_ibo = RHI_HANDLE_NULL;
    IndirectDrawSystem gids;
    memset(&gids, 0, sizeof(gids));
    bool gids_ok = false;

    const u32 GA = 64u; /* array layer extent (all sources native 64x64) */
    u8 *alb_red   = malloc((usize)GA * GA * 4u);
    u8 *alb_green = malloc((usize)GA * GA * 4u);
    u8 *alb_blue  = malloc((usize)GA * GA * 4u);
    u8 *mr_l1     = malloc((usize)GA * GA * 4u);
    u8 *mr_l2     = malloc((usize)GA * GA * 4u);
    u8 *mr_l3     = malloc((usize)GA * GA * 4u);
    u8 *glayer    = malloc((usize)GA * GA * 4u);
    if (alb_red && alb_green && alb_blue && mr_l1 && mr_l2 && mr_l3 && glayer) {
        for (u32 p = 0; p < GA * GA; p++) {
            u8 *pr = &alb_red[(usize)p * 4u];
            u8 *pg = &alb_green[(usize)p * 4u];
            u8 *pb = &alb_blue[(usize)p * 4u];
            pr[0] = 255; pr[1] = 0;   pr[2] = 0;   pr[3] = 255;
            pg[0] = 0;   pg[1] = 255; pg[2] = 0;   pg[3] = 255;
            pb[0] = 0;   pb[1] = 0;   pb[2] = 255; pb[3] = 255;
            /* MR semantics (gbuffer shader samples .bg): b = metallic,
             * g = roughness. */
            u8 *m1 = &mr_l1[(usize)p * 4u];
            u8 *m2 = &mr_l2[(usize)p * 4u];
            u8 *m3 = &mr_l3[(usize)p * 4u];
            m1[0] = 0; m1[1] = 26;  m1[2] = 255; m1[3] = 255; /* metal 1.0, rough 0.1 */
            m2[0] = 0; m2[1] = 230; m2[2] = 0;   m2[3] = 255; /* metal 0.0, rough 0.9 */
            m3[0] = 0; m3[1] = 128; m3[2] = 128; m3[3] = 255; /* metal 0.5, rough 0.5 */
        }

        gb_alb_arr = rhi_texture_array_create(rs->device, GA, GA, 4u,
                                              RHI_FORMAT_R8G8B8A8_UNORM);
        gb_mr_arr  = rhi_texture_array_create(rs->device, GA, GA, 4u,
                                              RHI_FORMAT_R8G8B8A8_UNORM);
        if (rhi_handle_valid(gb_alb_arr) && rhi_handle_valid(gb_mr_arr)) {
            const usize lbytes = (usize)GA * GA * 4u;
            /* Layer 0: white albedo fallback + neutral MR {255,128,0,255}
             * (metal 0, rough ~0.5 — main.c fallback_mr). */
            memset(glayer, 0xFF, lbytes);
            rhi_texture_array_upload_layer(rs->device, gb_alb_arr, 0u, glayer, lbytes);
            for (u32 p = 0; p < GA * GA; p++) {
                u8 *d = &glayer[(usize)p * 4u];
                d[0] = 255; d[1] = 128; d[2] = 0; d[3] = 255;
            }
            rhi_texture_array_upload_layer(rs->device, gb_mr_arr, 0u, glayer, lbytes);
            rhi_texture_array_upload_layer(rs->device, gb_alb_arr, 1u, alb_red, lbytes);
            rhi_texture_array_upload_layer(rs->device, gb_alb_arr, 2u, alb_green, lbytes);
            rhi_texture_array_upload_layer(rs->device, gb_alb_arr, 3u, alb_blue, lbytes);
            rhi_texture_array_upload_layer(rs->device, gb_mr_arr, 1u, mr_l1, lbytes);
            rhi_texture_array_upload_layer(rs->device, gb_mr_arr, 2u, mr_l2, lbytes);
            rhi_texture_array_upload_layer(rs->device, gb_mr_arr, 3u, mr_l3, lbytes);

            /* G-Buffer MRT (same layout as deferred.c defrd_alloc_targets).
             * GL ignores the R440 mrt_formats pipeline fields (glDrawBuffers
             * needs no render-pass compatibility), but they are set identically
             * so the shared body stays byte-for-byte backend-neutral. */
            RHIFormat gfmts[4] = {
                RHI_FORMAT_R8G8B8A8_UNORM,
                RHI_FORMAT_R16G16B16A16_SFLOAT,
                RHI_FORMAT_R8G8B8A8_UNORM,
                RHI_FORMAT_R16G16B16A16_SFLOAT,
            };
            gb_mrt = rhi_mrt_fbo_create(rs->device, GBW, GBH, gfmts, 4u);

            /* 4 quads, one per NDC quadrant (pos3+nrm3+uv2, 32B stride);
             * local indices + per-cmd vertex_offset (mega convention). */
            f32 qv[4 * 4 * 8];
            u32 qi[4 * 6];
            const f32 qcx[4] = { -0.5f, 0.5f, -0.5f, 0.5f };
            const f32 qcy[4] = {  0.5f, 0.5f, -0.5f, -0.5f };
            for (u32 k = 0; k < 4; k++) {
                f32 x0 = qcx[k] - 0.45f, x1 = qcx[k] + 0.45f;
                f32 y0 = qcy[k] - 0.45f, y1 = qcy[k] + 0.45f;
                const f32 qpos[4][2] = { {x0, y0}, {x1, y0}, {x1, y1}, {x0, y1} };
                const f32 quv[4][2]  = { {0, 0}, {1, 0}, {1, 1}, {0, 1} };
                for (u32 v = 0; v < 4; v++) {
                    f32 *d = &qv[(k * 4 + v) * 8];
                    d[0] = qpos[v][0]; d[1] = qpos[v][1]; d[2] = 0.0f;
                    d[3] = 0.0f; d[4] = 0.0f; d[5] = 1.0f;
                    d[6] = quv[v][0]; d[7] = quv[v][1];
                }
                u32 *di = &qi[k * 6];
                di[0] = 0; di[1] = 1; di[2] = 2;
                di[3] = 0; di[4] = 2; di[5] = 3;
            }
            RHIBufferDesc qvb = { .usage = RHI_BUFFER_USAGE_VERTEX,
                                  .size = sizeof(qv), .initial_data = qv };
            RHIBufferDesc qib = { .usage = RHI_BUFFER_USAGE_INDEX,
                                  .size = sizeof(qi), .initial_data = qi };
            gb_vbo = rhi_buffer_create(rs->device, &qvb);
            gb_ibo = rhi_buffer_create(rs->device, &qib);

            usize gvl = 0, gfl = 0;
            char *gvs = shader_read_file(TV_VS_GBUFFER_ARR, &gvl);
            char *gfs = shader_read_file(TV_FS_GBUFFER_ARR, &gfl);
            if (gvs && gfs) {
                RHIShader svs = rhi_shader_create(rs->device, gvs, gvl, false);
                RHIShader sfs = rhi_shader_create(rs->device, gfs, gfl, true);
                if (rhi_handle_valid(svs) && rhi_handle_valid(sfs)) {
                    RHIPipelineDesc dpd;
                    memset(&dpd, 0, sizeof(dpd));
                    dpd.vert = svs;
                    dpd.frag = sfs;
                    dpd.vertex_stride = 8u * sizeof(f32);
                    dpd.uses_textures = true;
                    dpd.depth_compare_lequal = true;
                    /* R440: pipeline must be render-pass-compatible with
                     * the 4-attachment G-Buffer MRT. */
                    dpd.mrt_attachment_count = 4u;
                    dpd.mrt_formats[0] = RHI_FORMAT_R8G8B8A8_UNORM;
                    dpd.mrt_formats[1] = RHI_FORMAT_R16G16B16A16_SFLOAT;
                    dpd.mrt_formats[2] = RHI_FORMAT_R8G8B8A8_UNORM;
                    dpd.mrt_formats[3] = RHI_FORMAT_R16G16B16A16_SFLOAT;
                    gb_pipe = rhi_pipeline_create(rs->device, &dpd);
                }
                if (rhi_handle_valid(svs)) rhi_shader_destroy(rs->device, svs);
                if (rhi_handle_valid(sfs)) rhi_shader_destroy(rs->device, sfs);
            }
            free(gvs); free(gfs);

            /* Ungrouped bake-order upload; first_instance = array layer.
             * quad2 (blue) gets layer 3 but is culled by visibility. */
            DrawIndexedIndirectCmd gcmds[4];
            const u32 glayer_of_quad[4] = { 1u, 2u, 3u, 0u };
            for (u32 k = 0; k < 4; k++) {
                gcmds[k].index_count    = 6;
                gcmds[k].instance_count = 1;
                gcmds[k].first_index    = k * 6u;
                gcmds[k].vertex_offset  = (i32)(k * 4u);
                gcmds[k].first_instance = glayer_of_quad[k];
            }
            gids_ok = indirect_draw_init(&gids, rs->device, 4);
            if (gids_ok) indirect_draw_upload(&gids, rs->device, gcmds, 4);

            setup_ok = rhi_handle_valid(gb_pipe) && rhi_handle_valid(gb_mrt.fb) &&
                       rhi_handle_valid(gb_mrt.color_tex[0]) &&
                       rhi_handle_valid(gb_mrt.color_tex[2]) &&
                       rhi_handle_valid(gb_vbo) && rhi_handle_valid(gb_ibo) && gids_ok;
        }
    }
    if (!setup_ok) {
        LOG_ERROR("FAIL: deferred-array setup (pipe=%d mrt=%d vbo=%d ibo=%d ids=%d)",
                  (int)rhi_handle_valid(gb_pipe), (int)rhi_handle_valid(gb_mrt.fb),
                  (int)rhi_handle_valid(gb_vbo), (int)rhi_handle_valid(gb_ibo),
                  (int)gids_ok);
    }

    u32 exec_count = 0xFFFFFFFFu, frames_ok = 0;
    if (setup_ok) {
        i32 l_model   = rhi_pipeline_get_uniform_location(rs->device, gb_pipe, "u_model");
        i32 l_view    = rhi_pipeline_get_uniform_location(rs->device, gb_pipe, "u_view");
        i32 l_proj    = rhi_pipeline_get_uniform_location(rs->device, gb_pipe, "u_proj");
        i32 l_prev_vp = rhi_pipeline_get_uniform_location(rs->device, gb_pipe, "u_prev_vp");
        Mat4 idm = mat4_identity();
        const u32 vis[4] = { 1u, 1u, 0u, 1u }; /* blue quad culled */

        indirect_draw_debug_reset_execute_count();
        for (u32 f = 0; f < 3; f++) {
            RHICmdBuffer *cmd = rhi_frame_begin(rs->device);
            if (!cmd) break;
            rhi_mrt_fbo_bind(cmd, &gb_mrt);
            rhi_cmd_clear_color(cmd, 0.0f, 0.0f, 0.0f, 0.0f);
            rhi_cmd_clear_depth(cmd);
            /* R442: no rhi_cmd_set_viewport here — rhi_mrt_fbo_bind already
             * set the full-target NON-flipped viewport; rhi_cmd_set_viewport
             * is the flipped variant and would invert winding (culling). */
            indirect_draw_upload_visibility(&gids, rs->device, vis, 4);
            indirect_draw_compact_no_barrier(&gids, rs->device, cmd);
            rhi_cmd_memory_barrier(cmd);
            /* R234-A: rebind graphics pipeline after compact compute, then
             * push constants (a set before the compact would be flushed). */
            rhi_cmd_bind_pipeline(cmd, gb_pipe);
            rhi_cmd_set_uniform_mat4(cmd, l_model,   &idm.e[0][0]);
            rhi_cmd_set_uniform_mat4(cmd, l_view,    &idm.e[0][0]);
            rhi_cmd_set_uniform_mat4(cmd, l_proj,    &idm.e[0][0]);
            rhi_cmd_set_uniform_mat4(cmd, l_prev_vp, &idm.e[0][0]);
            /* Slot 0 = albedo array, slot 2 = MR array; the remaining
             * slots are unsampled by gbuffer_arr — reuse the arrays. */
            rhi_cmd_bind_material_textures_ibl(cmd,
                gb_alb_arr, gb_mr_arr, gb_alb_arr, gb_alb_arr,
                RHI_HANDLE_NULL, RHI_HANDLE_NULL, rs->sampler,
                RHI_HANDLE_NULL, RHI_HANDLE_NULL, RHI_HANDLE_NULL, NULL, 0u);
            rhi_cmd_bind_vertex_buffer(cmd, gb_vbo, 0);
            rhi_cmd_bind_index_buffer(cmd, gb_ibo, 0, true);
            indirect_draw_execute(&gids, rs->device);
            rhi_mrt_fbo_unbind(cmd, GBW, GBH);
            rhi_frame_end(rs->device);
            rhi_present(rs->device);
            frames_ok++;
        }
        exec_count = indirect_draw_debug_execute_count();
    }

    /* Readback of RT0 (albedo+metallic) and RT2 (roughness+ao): raw UNORM
     * attachment values — no lighting, no sRGB encode on this path.
     * R442 (GL): glGetTexImage row 0 = texture t 0 = window-y 0 (bottom);
     * VK row 0 = image top. The NDC->row formula below lands on the same
     * index under both conventions because GL's viewport is NOT flipped
     * (NDC +y up) while VK's is non-flipped too (NDC +y down) — the two
     * origin flips cancel. Verified against Mesa + Intel Vulkan. */
    bool pixels_ok = false;
    if (setup_ok && frames_ok == 3u) {
        const usize gbytes = (usize)GBW * GBH * 4u;
        u8 *rt0 = malloc(gbytes);
        u8 *rt2 = malloc(gbytes);
        if (rt0 && rt2 &&
            rhi_texture_read_pixels(rs->device, gb_mrt.color_tex[0], rt0, gbytes) &&
            rhi_texture_read_pixels(rs->device, gb_mrt.color_tex[2], rt2, gbytes)) {
            const f32 qcx[4] = { -0.5f, 0.5f, -0.5f, 0.5f };
            const f32 qcy[4] = {  0.5f, 0.5f, -0.5f, -0.5f };
            u8 qa[4][4], qr[4][4]; /* per-quad RGBA of RT0 / RT2 */
            for (u32 k = 0; k < 4; k++) {
                u32 px = (u32)((qcx[k] + 1.0f) * 0.5f * (f32)GBW);
                u32 py = (u32)((qcy[k] + 1.0f) * 0.5f * (f32)GBH);
                if (px >= GBW) px = GBW - 1;
                if (py >= GBH) py = GBH - 1;
                const u8 *p0 = &rt0[((usize)py * GBW + px) * 4u];
                const u8 *p2 = &rt2[((usize)py * GBW + px) * 4u];
                memcpy(qa[k], p0, 4u);
                memcpy(qr[k], p2, 4u);
            }

            bool q0 = qa[0][0] > 200 && qa[0][1] < 80 && qa[0][2] < 80 &&
                      qa[0][3] > 200 &&                    /* red, metal 1.0 */
                      qr[0][0] > 20 && qr[0][0] < 34 &&    /* rough 0.1 (26) */
                      qr[0][1] > 200;                      /* ao 1.0 */
            bool q1 = qa[1][1] > 200 && qa[1][0] < 80 && qa[1][2] < 80 &&
                      qa[1][3] < 10 &&                     /* green, metal 0 */
                      qr[1][0] > 220 && qr[1][0] < 240 &&  /* rough 0.9 (230) */
                      qr[1][1] > 200;
            bool q2 = qa[2][0] < 10 && qa[2][1] < 10 && qa[2][2] < 10 &&
                      qa[2][3] < 10 &&                     /* culled = clear */
                      qr[2][0] < 10 && qr[2][1] < 10;
            bool q3 = qa[3][0] > 200 && qa[3][1] > 200 && qa[3][2] > 200 &&
                      qa[3][3] < 10 &&                     /* white, neutral metal 0 */
                      qr[3][0] > 120 && qr[3][0] < 136 &&  /* neutral rough 0.5 (128) */
                      qr[3][1] > 200;
            pixels_ok = q0 && q1 && q2 && q3;
            if (!pixels_ok)
                LOG_ERROR("FAIL: gbuffer pixels "
                          "q0 alb{%u,%u,%u,%u} mr{%u,%u} q1 alb{%u,%u,%u,%u} mr{%u,%u} "
                          "q2 alb{%u,%u,%u,%u} q3 alb{%u,%u,%u,%u} mr{%u,%u}",
                          qa[0][0], qa[0][1], qa[0][2], qa[0][3], qr[0][0], qr[0][1],
                          qa[1][0], qa[1][1], qa[1][2], qa[1][3], qr[1][0], qr[1][1],
                          qa[2][0], qa[2][1], qa[2][2], qa[2][3],
                          qa[3][0], qa[3][1], qa[3][2], qa[3][3], qr[3][0], qr[3][1]);
        } else {
            LOG_ERROR("FAIL: gbuffer attachment readback");
        }
        free(rt0); free(rt2);
    }

    bool exec_ok = (frames_ok == 3u) && (exec_count == frames_ok);
    if (!exec_ok)
        LOG_ERROR("FAIL: deferred-array execute draws=%u over %u frames, want exactly 1/frame",
                  exec_count, frames_ok);

    bool defarr_pass = setup_ok && pixels_ok && exec_ok;
    if (defarr_pass)
        LOG_INFO("PASS: deferred gbuffer array single execute (4 layers incl. "
                 "neutral MR fallback, 1 execute/frame, RT0 hue+metallic & "
                 "RT2 roughness layer differences verified)");

    if (gids_ok) indirect_draw_destroy(&gids, rs->device);
    if (rhi_handle_valid(gb_pipe))    rhi_pipeline_destroy(rs->device, gb_pipe);
    if (rhi_handle_valid(gb_alb_arr)) rhi_texture_destroy(rs->device, gb_alb_arr);
    if (rhi_handle_valid(gb_mr_arr))  rhi_texture_destroy(rs->device, gb_mr_arr);
    if (rhi_handle_valid(gb_ibo))     rhi_buffer_destroy(rs->device, gb_ibo);
    if (rhi_handle_valid(gb_vbo))     rhi_buffer_destroy(rs->device, gb_vbo);
    if (rhi_handle_valid(gb_mrt.fb))  rhi_mrt_fbo_destroy(rs->device, &gb_mrt);
    free(alb_red); free(alb_green); free(alb_blue);
    free(mr_l1); free(mr_l2); free(mr_l3); free(glayer);
    return defarr_pass;
}

/* TEST 7 is backend-neutral: both GL and Vulkan generate the same procedural
 * sky cubemap, convolve it, then sample it through the clustered PBR path. */
static bool tv_test_ibl(const TestRenderState *rs, RHIBuffer vbo, RHIBuffer ibo,
                        u32 iw, u32 ih) {
    IBLSystem ibl = {0};
    ibl_init(&ibl, rs->device);
    f32 sdir[3] = { 0.3f, -0.7f, 0.5f };
    f32 scol[3] = { 1.0f, 0.95f, 0.85f };
    ibl_capture_env_sky(&ibl, rs->device, sdir, scol);
    ibl_generate(&ibl, rs->device, ibl.env_map);

    bool gen_ok = ibl.ready
               && rhi_handle_valid(ibl.brdf_lut)
               && rhi_handle_valid(ibl.env_map)
               && rhi_handle_valid(ibl.irradiance_map)
               && rhi_handle_valid(ibl.prefilter_map);
    if (gen_ok)
        LOG_INFO("PASS: IBL generated (env+irradiance+prefilter+BRDF LUT)");
    else
        LOG_ERROR("FAIL: IBL generation incomplete (ready=%d)", ibl.ready);

    RHIPipeline cl_pipe = RHI_HANDLE_NULL;
    usize vl = 0, fl = 0;
    const char *ibl_vs_path =
#ifdef ENGINE_VULKAN
        "shaders/pbr_ibl_test_vk.vert";
#else
        TV_VS_PBR;
#endif
    char *vsrc = shader_read_file(ibl_vs_path, &vl);
    char *fsrc = shader_read_file(TV_FS_PBR, &fl);
    if (vsrc && fsrc) {
        usize fl_ibl = 0;
        char *fsrc_ibl = tv_inject_define(fsrc, fl, "HAS_IBL", &fl_ibl);
        RHIShader vs = rhi_shader_create(rs->device, vsrc, vl, false);
        RHIShader fs = fsrc_ibl ? rhi_shader_create(rs->device, fsrc_ibl, fl_ibl, true)
                                : rhi_shader_create(rs->device, fsrc, fl, true);
        if (rhi_handle_valid(vs) && rhi_handle_valid(fs)) {
            RHIPipelineDesc d = {.vert = vs, .frag = fs, .uses_textures = true,
                                 .uses_texel_buffer = true,
                                 .color_format = RHI_FORMAT_R16G16B16A16_SFLOAT};
            cl_pipe = rhi_pipeline_create(rs->device, &d);
        }
        rhi_shader_destroy(rs->device, vs);
        rhi_shader_destroy(rs->device, fs);
        free(fsrc_ibl);
    }
    free(vsrc);
    free(fsrc);

    LightSystem ls;
    light_system_init(&ls, rs->device);
    bool gpu_cull_ok = light_system_init_gpu_cull(&ls);
    light_system_add_dir(&ls, 0.3f, -0.7f, 0.5f, 1.0f, 0.95f, 0.85f);
    light_system_add_point(&ls, 0.0f, 1.0f, 2.0f, 8.0f, 1.0f, 0.6f, 0.3f);

    bool sample_ok = false;
    RHIOffscreenFBO scene = {0};
    if (gen_ok && rhi_handle_valid(cl_pipe) && iw > 0u && ih > 0u) {
        scene = rhi_offscreen_fbo_create_fmt(
            rs->device, iw, ih, RHI_FORMAT_R16G16B16A16_SFLOAT);
        bool scene_ok = rhi_handle_valid(scene.fb) &&
                        rhi_handle_valid(scene.color_tex) &&
                        rhi_handle_valid(scene.depth_tex);

        Mat4 model = mat4_identity();
        Mat4 view  = mat4_identity();
        Mat4 proj  = mat4_identity();
        i32 l_model = rhi_pipeline_get_uniform_location(rs->device, cl_pipe, "u_model");
        i32 l_view  = rhi_pipeline_get_uniform_location(rs->device, cl_pipe, "u_view");
        i32 l_proj  = rhi_pipeline_get_uniform_location(rs->device, cl_pipe, "u_proj");
        i32 l_cam   = rhi_pipeline_get_uniform_location(rs->device, cl_pipe, "u_camera_pos");
        i32 l_amb   = rhi_pipeline_get_uniform_location(rs->device, cl_pipe, "u_ambient");
        i32 l_sw    = rhi_pipeline_get_uniform_location(rs->device, cl_pipe, "u_screen_w");
        i32 l_sh    = rhi_pipeline_get_uniform_location(rs->device, cl_pipe, "u_screen_h");
        i32 l_near  = rhi_pipeline_get_uniform_location(rs->device, cl_pipe, "u_near");
        i32 l_far   = rhi_pipeline_get_uniform_location(rs->device, cl_pipe, "u_far");
        i32 l_pc    = rhi_pipeline_get_uniform_location(rs->device, cl_pipe, "u_point_count");
        i32 l_dc    = rhi_pipeline_get_uniform_location(rs->device, cl_pipe, "u_dir_count");

        u32 ierr = scene_ok ? 0u : 1u;
        for (u32 f = 0; scene_ok && f < 8u; f++) {
            if (gpu_cull_ok) {
                light_system_upload_lights(&ls);
            } else {
                light_system_cull(&ls, &view, &proj, iw, ih);
                light_system_upload(&ls);
            }

            RHICmdBuffer *cmd = rhi_frame_begin(rs->device);
            if (!cmd) { ierr++; continue; }
            rhi_offscreen_fbo_bind(cmd, &scene);
            rhi_cmd_clear_color(cmd, 0.01f, 0.02f, 0.03f, 1.0f);
            rhi_cmd_clear_depth(cmd);
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
            rhi_cmd_bind_texel_buffers(cmd, light_system_data_slot(&ls),
                                       light_system_grid_slot(&ls));
            rhi_cmd_bind_material_textures_ibl(cmd,
                rs->test_tex, rs->test_tex, rs->test_tex, rs->test_tex,
                rs->test_tex, rs->test_tex, rs->sampler,
                ibl.brdf_lut, ibl.irradiance_map, ibl.prefilter_map, NULL, 0u);
            rhi_cmd_bind_vertex_buffer(cmd, vbo, 0);
            rhi_cmd_bind_index_buffer(cmd, ibo, 0, true);
            rhi_cmd_draw_indexed(cmd, 3, 1);
            rhi_offscreen_fbo_unbind(cmd, iw, ih);
            rhi_frame_end(rs->device);
            rhi_present(rs->device);
        }

        bool pixels_ok = false;
        usize bytes = (usize)iw * ih * 8u;
        u8 *pixels = malloc(bytes);
        if (ierr == 0u && pixels &&
            rhi_texture_read_pixels(rs->device, scene.color_tex, pixels, bytes)) {
            const usize pixel_stride = 8u;
            const usize pixel_count = (usize)iw * ih;
            bool varied = false;
            bool nonzero = false;
            for (usize i = 0; i < pixel_count && (!varied || !nonzero); i++) {
                const u8 *p = pixels + i * pixel_stride;
                if (memcmp(p, pixels, pixel_stride) != 0) varied = true;
                for (usize b = 0; b < pixel_stride; b++)
                    if (p[b] != 0u) nonzero = true;
            }
            pixels_ok = varied && nonzero;
            if (!pixels_ok)
                LOG_ERROR("FAIL: IBL PBR output is blank or flat");
        } else if (ierr == 0u) {
            LOG_ERROR("FAIL: IBL PBR output readback failed");
        }
        free(pixels);
        sample_ok = (ierr == 0u) && pixels_ok;
    }

    if (rhi_handle_valid(scene.fb)) rhi_offscreen_fbo_destroy(rs->device, &scene);
    if (rhi_handle_valid(cl_pipe)) rhi_pipeline_destroy(rs->device, cl_pipe);
    light_system_shutdown(&ls);
    ibl_destroy(&ibl, rs->device);
    return gen_ok && sample_ok;
}

int main(int argc, char **argv) {
    (void)argc; (void)argv;
    log_set_level(LOG_DEBUG);

    LOG_INFO("============================================");
    LOG_INFO("%s", TV_SUITE_NAME);
    LOG_INFO("============================================");

#if defined(ENGINE_VULKAN) && defined(ENGINE_VK_VALIDATION)
    /* R550-E: opt this process into the VK validation gate in every build
     * type (the engine library default keeps Release demos messenger-free;
     * CMake defines ENGINE_VK_VALIDATION on this target unconditionally). */
    rhi_vk_validation_set_enabled(true);
#endif

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
    /* OpenGL CTest: golden-image regression, real IBL, and the material-
     * indirect pixel gates. The expensive backend-specific stress body stays
     * Vulkan-only, while TEST 7 uses the same helper on both backends. */
    {
        u32 gw, gh;
        platform_get_size(engine.platform, &gw, &gh);
        LOG_INFO("OpenGL build: golden + material-indirect gates (suite body is Vulkan-only)");
        bool golden_pass = tv_run_golden_regression(&render, vbo, ibo, gw, gh);
        /* R438: non-identity camera variant (transpose-sensitive). */
        bool golden_cam_pass = tv_run_golden_camera_regression(&render, vbo, ibo, gw, gh);
        golden_pass = golden_pass && golden_cam_pass;

        LOG_INFO("============================================");
        LOG_INFO("TEST 7: IMAGE-BASED LIGHTING (REAL CUBEMAP)");
        LOG_INFO("============================================");
        bool ibl_pass = tv_test_ibl(&render, vbo, ibo, gw, gh);
        LOG_INFO("RESULT: IBL TEST %s",
                 ibl_pass ? "PASSED ✓" : "FAILED");

        LOG_INFO("============================================");
        LOG_INFO("TEST 10: INDIRECT DRAW GROUPED COMPACT");
        LOG_INFO("============================================");
        bool idraw_pass = tv_test_grouped_compact(&render);
        LOG_INFO("RESULT: INDIRECT DRAW GROUPED COMPACT TEST %s",
                 idraw_pass ? "PASSED ✓" : "FAILED");

        LOG_INFO("============================================");
        LOG_INFO("TEST 11: MATERIAL ARRAY SINGLE-EXECUTE DRAW");
        LOG_INFO("============================================");
        bool matarr_pass = tv_test_material_array(&render, gw, gh);
        LOG_INFO("RESULT: MATERIAL ARRAY SINGLE-EXECUTE TEST %s",
                 matarr_pass ? "PASSED ✓" : "FAILED");

        LOG_INFO("============================================");
        LOG_INFO("TEST 12: DEFERRED GBUFFER ARRAY SINGLE-EXECUTE");
        LOG_INFO("============================================");
        bool defarr_pass = tv_test_deferred_gbuffer_array(&render);
        LOG_INFO("RESULT: DEFERRED GBUFFER ARRAY SINGLE-EXECUTE TEST %s",
                 defarr_pass ? "PASSED ✓" : "FAILED");

        /* R442: GL has no validation-layers concept — the VK VALIDATION GATE
         * is intentionally absent here; the pixel gates above are the check. */
        bool all_pass = golden_pass && ibl_pass && idraw_pass && matarr_pass && defarr_pass;
        if (rhi_handle_valid(ibo)) rhi_buffer_destroy(render.device, ibo);
        if (rhi_handle_valid(vbo)) rhi_buffer_destroy(render.device, vbo);
        test_render_shutdown(&render);
        engine_shutdown(&engine);
        LOG_INFO("FINAL RESULT: %s", all_pass ? "ALL PASSED ✓" : "FAILED");
        return all_pass ? 0 : 1;
    }
#endif

#ifdef ENGINE_VULKAN
    /* R438: reset the validation gate — only messages emitted during the
     * suite body count (init-time chatter is excluded). */
    rhi_vk_validation_message_count_reset();
#endif

    /* Test: Skybox */
    Skybox skybox = {0};
    bool sky_ok = skybox_init(&skybox, render.device, false);
    if (sky_ok) { LOG_INFO("PASS: Skybox initialized"); }
    else { LOG_WARN("WARN: Skybox init failed (non-fatal)"); }

    /* Test: Terrain */
    Terrain terrain = {0};
    bool terr_ok = terrain_init(&terrain, render.device, 32, 20.0f, 1.0f, false);
    if (terr_ok) { LOG_INFO("PASS: Terrain created (%u indices)", terrain.index_count); }
    else { LOG_WARN("WARN: Terrain init failed"); }

    /* Camera */
    Camera camera = {0};
    u32 w, h;
    platform_get_size(engine.platform, &w, &h);
    camera_init(&camera, 1.047f, (f32)w / (f32)(h > 0 ? h : 1), 0.1f, 100.0f); /* R142: guard h==0 */

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
            rhi_cmd_bind_index_buffer(cmd, ibo, 0, true);
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

        skybox_render(&skybox, cmd, &view.e[0][0], &mat4_inv_perspective(proj).e[0][0], 0.5f, -0.8f, 0.3f, 1.0f, 0.95f, 0.9f);

        terrain_render(&terrain, cmd, &view.e[0][0], &proj.e[0][0],
                       &camera.position.e[0], render.test_tex, render.sampler,
                       (RHITexture){0,0}, NULL, 0.0f, -1.0f, 0.0f, 0.0f);

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
        rhi_cmd_bind_index_buffer(cmd, ibo, 0, true);
        rhi_cmd_bind_texture(cmd, render.test_tex, render.sampler, 0);
        rhi_cmd_draw_indexed(cmd, 3, 1);

        /* Multi-draw with different textures */
        if (rhi_handle_valid(tex2)) {
            Mat4 m2 = mat4_identity();
            m2.e[3][0] = 2.0f;
            rhi_cmd_set_uniform_mat4(cmd, render.loc_model, &m2.e[0][0]);
            rhi_cmd_bind_texture(cmd, tex2, render.sampler, 0);
            rhi_cmd_bind_vertex_buffer(cmd, vbo, 0);
            rhi_cmd_bind_index_buffer(cmd, ibo, 0, true);
            rhi_cmd_draw_indexed(cmd, 3, 1);
        }

        /* Pipeline rebind test: bind skybox then back to blinn_phong */
        if (sky_ok && frame_count % 10 == 0) {
            skybox_render(&skybox, cmd, &view.e[0][0], &mat4_inv_perspective(proj).e[0][0], 0.5f, -0.8f, 0.3f, 1.0f, 0.95f, 0.9f);
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
            rhi_cmd_bind_index_buffer(cmd, ibo, 0, true);
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

        skybox_render(&skybox, cmd, &view.e[0][0], &mat4_inv_perspective(proj).e[0][0], 0.5f, -0.8f, 0.3f, 1.0f, 0.95f, 0.9f);

        rhi_cmd_bind_pipeline(cmd, render.pipeline);
        rhi_cmd_set_uniform_mat4(cmd, render.loc_view, &view.e[0][0]);
        rhi_cmd_set_uniform_mat4(cmd, render.loc_proj, &proj.e[0][0]);
        rhi_cmd_set_uniform_vec3(cmd, render.loc_light_dir, 0.5f, -0.8f, 0.3f);
        rhi_cmd_set_uniform_vec3(cmd, render.loc_light_color, 1.0f, 0.95f, 0.9f);
        rhi_cmd_set_uniform_vec3(cmd, render.loc_ambient, 0.35f, 0.35f, 0.40f);
        rhi_cmd_set_uniform_vec3(cmd, render.loc_camera_pos,
                                 camera.position.e[0], camera.position.e[1], camera.position.e[2]);

        rhi_cmd_bind_vertex_buffer(cmd, vbo, 0);
        rhi_cmd_bind_index_buffer(cmd, ibo, 0, true);

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
    char *ivs_src = shader_read_file(TV_VS_INSTANCED, &ivs_len);
    char *ifs_src = shader_read_file(TV_FS_INSTANCED, &ifs_len);
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
    /* R425: NULL-check — the instanced frame loop below writes into it. */
    if (!instance_data) LOG_ERROR("FAIL: instance_data allocation");
    u32 inst_frame_count = 0;
    u32 inst_errors = 0;

    ComponentType qtypes[] = { TEST_COMP_TRANSFORM };
    bool inst_test_active = rhi_handle_valid(inst_pipeline) && rhi_handle_valid(instance_tbo)
                            && instance_data != NULL;

    while (engine_frame(&engine) && inst_frame_count < INST_FRAMES && inst_test_active) {
        inst_frame_count++;

        RHICmdBuffer *cmd = rhi_frame_begin(render.device);
        if (!cmd) { inst_errors++; continue; }

        rhi_cmd_clear_color(cmd, 0.05f, 0.05f, 0.1f, 1.0f);

        Mat4 view = camera_view(&camera);
        Mat4 proj = camera_projection(&camera);

        skybox_render(&skybox, cmd, &view.e[0][0], &mat4_inv_perspective(proj).e[0][0], 0.5f, -0.8f, 0.3f, 1.0f, 0.95f, 0.9f);

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
        rhi_cmd_bind_index_buffer(cmd, ibo, 0, true);
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
                rhi_cmd_bind_index_buffer(cmd, ibo, 0, true);
                rhi_cmd_draw_indexed(cmd, 3, 1);
                rhi_offscreen_fbo_unbind(cmd, cw, ch);

                /* Combined AA reads the scene depth as a texture, so transition it. */
                rhi_cmd_transition_depth_to_read(cmd, src.depth_tex);

                combined_aa_apply(&caa, cmd, src.color_tex, src.depth_tex, RHI_HANDLE_NULL,
                                  &id.e[0][0], &id.e[0][0], &id.e[0][0], cw, ch);
                RHITexture aa_out = combined_aa_get_output(&caa);

                combined_color_apply(&cc, cmd, aa_out,
                                     RHI_HANDLE_NULL, false,
                                     1.0f, 2.2f, 0,
                                     1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
                                     0.0f, 0.0f, 0.0f,
                                     (f32)f, cw, ch);

                rhi_frame_end(render.device);
                rhi_present(render.device);
            }

            /* R445: pixel-level guard for the fullscreen-blit depth-test fix.
             * The combined AA/color passes are fullscreen z=1.0 blits with
             * depth_write_disable pipelines; both backends previously
             * depth-tested them against the (cleared 1.0) depth attachment,
             * discarding every fragment — and TEST 6 passed vacuously because
             * it only checked init + frame completion. Read back the combined
             * color output and require non-flat content (the HDR source draws
             * a lit triangle over the dark clear, so a working chain cannot
             * be a single flat color). */
            bool pixels_ok = false;
            {
                RHITexture cc_out = combined_color_get_output(&cc);
                u32 ow = 0, oh = 0;
                bool dims_ok = rhi_handle_valid(cc_out) &&
                               rhi_texture_get_size(render.device, cc_out, &ow, &oh) &&
                               ow > 0 && oh > 0;
                usize psz = (usize)(ow > 0 ? ow : 1) * (oh > 0 ? oh : 1) * 8u;
                u8 *pix = (u8 *)malloc(psz);
                if (dims_ok && pix && rhi_texture_read_pixels(render.device, cc_out, pix, psz)) {
                    /* 4-byte units over the first w*h*4 bytes: full image for
                     * RGBA8, top half for RGBA16F — either way plenty of
                     * coverage for a flat-color check. */
                    u32 units = ow * oh;
                    bool varied = false;
                    for (u32 i = 1; i < units && !varied; i++)
                        if (memcmp(pix + (usize)i * 4u, pix, 4u) != 0) varied = true;
                    pixels_ok = varied;
                    if (!varied)
                        LOG_ERROR("FAIL: combined color output is one flat color "
                                  "(fullscreen blits discarded, R445 regression)");
                } else {
                    LOG_ERROR("FAIL: combined color output readback failed "
                              "(dims_ok=%d valid=%d %ux%u)",
                              (int)dims_ok, (int)rhi_handle_valid(cc_out), ow, oh);
                }
                free(pix);
            }

            combined_pass = (cerr == 0) && pixels_ok;
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

    u32 iw, ih;
    platform_get_size(engine.platform, &iw, &ih);
    bool ibl_pass = tv_test_ibl(&render, vbo, ibo, iw, ih);

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
                gpucull_dispatch_unified(&uc, cmd, &vp.e[0][0], NULL, RHI_HANDLE_NULL, 0, 0, RHI_HANDLE_NULL, true, false);
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

            /* ---- R436: real Hi-Z pyramid occlusion assertions --------------
             * Previous TEST 9 only smoked the fallback path (hi_z = NULL), so
             * the Hi-Z consumption chain had zero coverage. Here we:
             *   1. render a near fullscreen triangle into a 64x64 offscreen
             *      depth target (window depth 0.1 everywhere),
             *   2. run occlusion_cull_generate_hi_z on it,
             *   3. dispatch unified cull against the REAL pyramid with two
             *      spheres at screen center: near (closest_z 0.05, visible)
             *      and far (closest_z 0.90, must be culled),
             *   4. read back vis flags (1-frame pipelined staging) and assert
             *      {1,0}; the fallback control (hi_z = NULL) must give {1,1}.
             * Also asserts the segmented generation chain issued the expected
             * (reduced) number of compute dispatches. */
            bool hiz_occ_ok = false;
            {
                const u32 HW = 64, HH = 64;          /* -> Hi-Z 32x32, 6 levels */
                OcclusionCullSystem occ;
                memset(&occ, 0, sizeof(occ));
                bool occ_ok = occlusion_cull_init(&occ, render.device, HW, HH);
                RHIOffscreenFBO hz_fbo = rhi_offscreen_fbo_create(render.device, HW, HH);

                /* Two spheres at screen center; identity vp keeps NDC == world. */
                GPUCullDrawCmd dcmd2[2];
                dcmd2[0] = dcmd; dcmd2[1] = dcmd;
                GPUCullObject objs[2];
                memset(objs, 0, sizeof(objs));
                objs[0].position[2] = -0.85f; objs[0].position[3] = 0.05f; /* near: visible */
                objs[1].position[2] =  0.85f; objs[1].position[3] = 0.05f; /* far: occluded */
                gpucull_upload_draw_cmds(&uc, dcmd2, 2);
                gpucull_upload_objects_unified(&uc, objs, 2);

                /* Fullscreen near triangle (scaled x3 to cover all pixels) at
                 * NDC z=-0.8 -> window depth 0.1 across the whole pyramid. */
                Mat4 quad = mat4_identity();
                quad.e[0][0] = 3.0f;
                quad.e[1][1] = 3.0f;
                quad.e[3][2] = -0.8f;
                Mat4 vp_id = mat4_identity();

                bool fallback_ok = false, real_ok = false, count_ok = false;
                if (occ_ok && occ.enabled && rhi_handle_valid(hz_fbo.depth_tex)) {
                    /* Control phase: hi_z = NULL -> 1x1 fallback -> all visible. */
                    u32 flags[2] = {0xFFFFFFFFu, 0xFFFFFFFFu};
                    for (u32 f = 0; f < 4; f++) {
                        RHICmdBuffer *cmd = rhi_frame_begin(render.device);
                        if (!cmd) break;
                        rhi_cmd_end_render_pass(cmd);
                        gpucull_dispatch_unified(&uc, cmd, &vp_id.e[0][0], NULL,
                                                 RHI_HANDLE_NULL, 0, 0,
                                                 RHI_HANDLE_NULL, true, true);
                        rhi_frame_end(render.device);
                        rhi_present(render.device);
                    }
                    if (gpucull_read_vis_flags(&uc, 2, flags))
                        fallback_ok = (flags[0] == 1u && flags[1] == 1u);
                    if (!fallback_ok)
                        LOG_ERROR("FAIL: fallback vis flags {%u,%u}, want {1,1}",
                                  flags[0], flags[1]);

                    /* Real pyramid phase. */
                    flags[0] = flags[1] = 0xFFFFFFFFu;
                    u32 hiz_dispatches = 0;
                    for (u32 f = 0; f < 4; f++) {
                        RHICmdBuffer *cmd = rhi_frame_begin(render.device);
                        if (!cmd) break;
                        rhi_offscreen_fbo_bind(cmd, &hz_fbo);
                        rhi_cmd_bind_pipeline(cmd, render.pipeline);
                        rhi_cmd_set_uniform_mat4(cmd, render.loc_model, &quad.e[0][0]);
                        rhi_cmd_set_uniform_mat4(cmd, render.loc_view,  &vp_id.e[0][0]);
                        rhi_cmd_set_uniform_mat4(cmd, render.loc_proj,  &vp_id.e[0][0]);
                        rhi_cmd_set_uniform_vec3(cmd, render.loc_light_dir, 0.5f, -0.8f, 0.3f);
                        rhi_cmd_set_uniform_vec3(cmd, render.loc_light_color, 1.0f, 0.95f, 0.9f);
                        rhi_cmd_set_uniform_vec3(cmd, render.loc_ambient, 0.35f, 0.35f, 0.40f);
                        rhi_cmd_set_uniform_vec3(cmd, render.loc_camera_pos, 0, 0, 5);
                        rhi_cmd_bind_texture(cmd, render.test_tex, render.sampler, 0);
                        rhi_cmd_bind_vertex_buffer(cmd, vbo, 0);
                        rhi_cmd_bind_index_buffer(cmd, ibo, 0, true);
                        rhi_cmd_draw_indexed(cmd, 3, 1);
                        rhi_offscreen_fbo_unbind(cmd, HW, HH);
                        rhi_cmd_end_render_pass(cmd);
                        occlusion_cull_generate_hi_z(&occ, cmd, hz_fbo.depth_tex);
                        hiz_dispatches = occlusion_cull_hiz_dispatch_count(&occ);
                        gpucull_dispatch_unified(&uc, cmd, &vp_id.e[0][0], NULL,
                                                 occ.hi_z_texture,
                                                 occ.hi_z_width, occ.hi_z_height,
                                                 RHI_HANDLE_NULL, true, true);
                        rhi_frame_end(render.device);
                        rhi_present(render.device);
                    }
                    if (gpucull_read_vis_flags(&uc, 2, flags))
                        real_ok = (flags[0] == 1u && flags[1] == 0u);
                    if (!real_ok)
                        LOG_ERROR("FAIL: Hi-Z vis flags {%u,%u}, want {1,0}",
                                  flags[0], flags[1]);

                    /* 6 levels -> ceil(6/4) = 2 chunked dispatches (was 6). */
                    u32 want_dispatches = (occ.hi_z_levels + 3u) / 4u;
                    count_ok = (hiz_dispatches == want_dispatches);
                    if (!count_ok)
                        LOG_ERROR("FAIL: Hi-Z dispatches=%u, want %u (segmented chain)",
                                  hiz_dispatches, want_dispatches);

                    hiz_occ_ok = fallback_ok && real_ok && count_ok;
                } else {
                    LOG_ERROR("FAIL: Hi-Z occlusion setup (occ=%d fbo=%d)",
                              (int)occ_ok, (int)rhi_handle_valid(hz_fbo.depth_tex));
                }
                if (hiz_occ_ok) {
                    LOG_INFO("PASS: Hi-Z occlusion (fallback {1,1}, pyramid {1,0}, dispatches=%u)",
                             count_ok ? (occ.hi_z_levels + 3u) / 4u : 0u);
                }
                rhi_offscreen_fbo_destroy(render.device, &hz_fbo);
                if (occ_ok) occlusion_cull_shutdown(&occ);
            }
            unified_pass = unified_pass && hiz_occ_ok;
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

    /* ---- TEST 10: R437 grouped indirect_draw compact gate ---- */
    LOG_INFO("============================================");
    LOG_INFO("TEST 10: INDIRECT DRAW GROUPED COMPACT");
    LOG_INFO("============================================");

    /* R442: VK/GL share the backend-neutral body (tv_test_grouped_compact);
     * the GL build runs it in its own early-exit branch above. */
    bool idraw_pass = tv_test_grouped_compact(&render);

    if (idraw_pass) {
        LOG_INFO("RESULT: INDIRECT DRAW GROUPED COMPACT TEST PASSED ✓");
    } else {
        LOG_ERROR("RESULT: INDIRECT DRAW GROUPED COMPACT TEST FAILED");
    }

    /* ---- TEST 11: R441 material texture-array single-execute forward ---- */
    LOG_INFO("============================================");
    LOG_INFO("TEST 11: MATERIAL ARRAY SINGLE-EXECUTE DRAW");
    LOG_INFO("============================================");

    /* R442: VK/GL share the backend-neutral body (tv_test_material_array);
     * the GL build runs it in its own early-exit branch above. */
    u32 tw = 0, th = 0;
    platform_get_size(engine.platform, &tw, &th);
    bool matarr_pass = tv_test_material_array(&render, tw, th);

    if (matarr_pass) {
        LOG_INFO("RESULT: MATERIAL ARRAY SINGLE-EXECUTE TEST PASSED ✓");
    } else {
        LOG_ERROR("RESULT: MATERIAL ARRAY SINGLE-EXECUTE TEST FAILED");
    }

    /* ---- TEST 12: R442 deferred G-buffer material-array single execute ---- */
    LOG_INFO("============================================");
    LOG_INFO("TEST 12: DEFERRED GBUFFER ARRAY SINGLE-EXECUTE");
    LOG_INFO("============================================");

    /* R442: VK/GL share the backend-neutral body (tv_test_deferred_gbuffer_array);
     * the GL build runs it in its own early-exit branch above. */
    bool defarr_pass = tv_test_deferred_gbuffer_array(&render);

    if (defarr_pass) {
        LOG_INFO("RESULT: DEFERRED GBUFFER ARRAY SINGLE-EXECUTE TEST PASSED ✓");
    } else {
        LOG_ERROR("RESULT: DEFERRED GBUFFER ARRAY SINGLE-EXECUTE TEST FAILED");
    }

    /* ---- TEST 8: Golden image regression ---- */
    u32 gw2, gh2;
    platform_get_size(engine.platform, &gw2, &gh2);
    bool golden_pass = tv_run_golden_regression(&render, vbo, ibo, gw2, gh2);
    /* R438: non-identity camera variant (transpose-sensitive). */
    bool golden_cam_pass = tv_run_golden_camera_regression(&render, vbo, ibo, gw2, gh2);
    golden_pass = golden_pass && golden_cam_pass;

    /* R438: hard gate — any validation warning/error during the suite fails
     * it. Skipped when the debug messenger is inactive (no layer/ext). */
    bool validation_pass = true;
#ifdef ENGINE_VULKAN
    if (rhi_vk_validation_gate_active()) {
        u32 val_msgs = rhi_vk_validation_message_count();
        validation_pass = (val_msgs == 0);
        if (!validation_pass) {
            LOG_ERROR("VALIDATION GATE: %u Vulkan validation message(s) — FAIL", val_msgs);
        } else {
            LOG_INFO("VALIDATION GATE: 0 Vulkan validation messages ✓");
        }
    } else {
        LOG_WARN("VALIDATION GATE: debug messenger inactive — gate skipped");
    }
#endif

    bool all_pass = stress_pass && draw_pass && inst_pass && fbo_pass &&
                    compute_pass && combined_pass && ibl_pass && unified_pass &&
                    idraw_pass && matarr_pass && defarr_pass && golden_pass &&
                    validation_pass;

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
