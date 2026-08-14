#include "test_framework.h"
#include <core/shader_io.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

static bool read_shader_source(const char *name, char *buf, usize cap)
{
    char rel[1024];
    const char *slash = strrchr(__FILE__, '/');
    const char *candidates[3] = { NULL, name, NULL };
    if (slash) {
        snprintf(rel, sizeof(rel), "%.*s/../shaders/%s",
                 (int)(slash - __FILE__), __FILE__, name);
        candidates[0] = rel;
    }
    for (usize i = 0; i < 2 && candidates[i]; i++) {
        FILE *f = fopen(candidates[i], "rb");
        if (!f) continue;
        usize n = fread(buf, 1, cap - 1, f);
        fclose(f);
        buf[n] = '\0';
        if (n > 0) return true;
    }
    return false;
}

static bool read_engine_source(const char *name, char *buf, usize cap)
{
    char rel[1024];
    const char *slash = strrchr(__FILE__, '/');
    if (!slash) return false;
    snprintf(rel, sizeof(rel), "%.*s/../src/%s",
             (int)(slash - __FILE__), __FILE__, name);
    FILE *f = fopen(rel, "rb");
    if (!f) return false;
    usize n = fread(buf, 1, cap - 1, f);
    fclose(f);
    buf[n] = '\0';
    return n > 0;
}

/* R444: per-pid path — parallel ctest trees raced on the fixed name. */
static const char *shader_io_tmp_path(void)
{
    static char b[128];
    return test_tmp(b, sizeof b, "test_shader_io.glsl");
}
#define TMP_SHADER shader_io_tmp_path()

TEST(shader_read_rejects_oversized_file)
{
    FILE *f = fopen(TMP_SHADER, "wb");
    ASSERT_NOT_NULL(f);
#if defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE >= 200112L
    ASSERT_TRUE(ftruncate(fileno(f), (off_t)SHADER_MAX_FILE_BYTES + 1) == 0);
#else
    if (fseek(f, (long)SHADER_MAX_FILE_BYTES, SEEK_SET) == 0) fputc('x', f);
#endif
    fclose(f);

    usize len = 99;
    char *data = shader_read_file(TMP_SHADER, &len);
    ASSERT_TRUE(data == NULL);
    ASSERT_EQ(len, (usize)99);

    remove(TMP_SHADER);
}

TEST(upscale_shaders_guard_first_temporal_frame)
{
    const char *frags[] = { "upscale.frag", "upscale_vk.frag" };
    for (usize i = 0; i < sizeof(frags) / sizeof(frags[0]); i++) {
        char src[16384];
        ASSERT_TRUE(read_shader_source(frags[i], src, sizeof(src)));
        /* Both implementations need the uniform and must gate the only
         * history reprojection path so init/resize cannot sample an invalid
         * previous-frame transform. */
        ASSERT_NOT_NULL(strstr(src, "u_ups_first_frame"));
        ASSERT_NOT_NULL(strstr(src, "u_ups_first_frame < 0.5"));
    }
}

/* R550-A: the five previously dead-end post passes (SSR/SSGI/volumetric/
 * lens flare/contact shadow) self-composite the incoming frame-chain color
 * like god_rays does.  Assert the contract on BOTH backends: each shader
 * must declare the chain-color sampler (SSR reuses u_ssr_color — it already
 * samples the chain) and must blend its effect into it. */
TEST(postfx_passes_composite_chain_color)
{
    struct { const char *file; const char *sampler; const char *blend; } cases[] = {
        { "contact_shadow.frag",    "u_cs_scene",  "scene * shadow" },
        { "contact_shadow_vk.frag", "u_cs_scene",  "scene * shadow" },
        { "volumetric.frag",        "u_vol_scene", "scene * transmittance + accum" },
        { "volumetric_vk.frag",     "u_vol_scene", "scene * transmittance + accum" },
        { "lens_flare.frag",        "u_lf_scene",  "scene + flare" },
        { "lens_flare_vk.frag",     "u_lf_scene",  "scene + flare" },
        { "ssr.frag",               NULL,          "mix(scene, ssr_color, fade)" },
        { "ssr_vk.frag",            NULL,          "mix(scene, ssr_color, fade)" },
        { "ssgi_blur.frag",         "u_ssgi_scene", "scene + result" },
        { "ssgi_blur_vk.frag",      "u_ssgi_scene", "scene + result" },
    };
    for (usize i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
        char src[16384];
        ASSERT_TRUE(read_shader_source(cases[i].file, src, sizeof(src)));
        if (cases[i].sampler)
            ASSERT_NOT_NULL(strstr(src, cases[i].sampler));
        ASSERT_NOT_NULL(strstr(src, cases[i].blend));
    }
}

TEST(per_object_velocity_contract_is_not_camera_only)
{
    const char *files[] = {
        "gbuffer.vert", "gbuffer_vk.vert",
        "gbuffer_arr.vert", "gbuffer_arr_vk.vert"
    };
    for (usize i = 0; i < sizeof(files) / sizeof(files[0]); i++) {
        char src[16384];
        ASSERT_TRUE(read_shader_source(files[i], src, sizeof(src)));
        ASSERT_NOT_NULL(strstr(src, "u_prev_mvp"));
        ASSERT_NOT_NULL(strstr(src, "v_velocity"));
        /* The deferred path already computes velocity from the geometry pass;
         * keep this contract explicit while forward MRT is being migrated. */
        ASSERT_NOT_NULL(strstr(src, "curr_ndc"));
        ASSERT_NOT_NULL(strstr(src, "prev_ndc"));
        ASSERT_NOT_NULL(strstr(src, "u_prev_mvp * vec4"));
    }
}

TEST(gl_ibl_test_contract_is_documented)
{
    char src[32768];
    ASSERT_TRUE(read_shader_source("brdf_lut.comp", src, sizeof(src)));
    ASSERT_NOT_NULL(strstr(src, "#version"));
    ASSERT_TRUE(read_shader_source("irradiance_env.comp", src, sizeof(src)));
    ASSERT_NOT_NULL(strstr(src, "image2D"));
    ASSERT_TRUE(read_shader_source("prefilter_env.comp", src, sizeof(src)));
    ASSERT_NOT_NULL(strstr(src, "image2D"));
}

/* The directional light vector points from the sun toward the scene, while
 * sky_to_cube uses u_sun_dir as the sun's position. Keep IBL reflections
 * aligned with the raster sky without adding a runtime rebake. */
TEST(ibl_capture_uses_to_sun_direction)
{
    char src[131072];
    ASSERT_TRUE(read_engine_source("main.c", src, sizeof(src)));
    ASSERT_NOT_NULL(strstr(src, "ibl_capture_env_sky(&rs->ibl"));
    ASSERT_NOT_NULL(strstr(src, "f32 sky_sun_dir[3] = { -sdir[0], -sdir[1], -sdir[2] }"));
    ASSERT_NOT_NULL(strstr(src, "ibl_capture_env_sky(&rs->ibl, rs->device, sky_sun_dir, scol)"));

    char shader[16384];
    ASSERT_TRUE(read_shader_source("sky_to_cube.comp", shader, sizeof(shader)));
    ASSERT_NOT_NULL(strstr(shader, "vec3 sun = normalize(SUN_DIR)"));
    ASSERT_NOT_NULL(strstr(shader, "float cos_sun = max(dot(ray, sun), -1.0)"));
}

TEST(gl_ibl_graphics_gate_runs_real_shared_test)
{
    char src[131072];
    ASSERT_TRUE(read_engine_source("test_vulkan.c", src, sizeof(src)));
    ASSERT_NOT_NULL(strstr(src, "static bool tv_test_ibl"));
    ASSERT_NOT_NULL(strstr(src, "bool ibl_pass = tv_test_ibl(&render"));
    ASSERT_NOT_NULL(strstr(src, "golden_pass && ibl_pass && idraw_pass"));
}

TEST(forward_velocity_uses_single_pass_mrt_contract)
{
    char src[131072];
    ASSERT_TRUE(read_engine_source("main.c", src, sizeof(src)));
    ASSERT_NOT_NULL(strstr(src, "FORWARD_MRT"));
    ASSERT_NOT_NULL(strstr(src, "RHI_FORMAT_R16G16_SFLOAT"));
    ASSERT_NOT_NULL(strstr(src, "rhi_mrt_fbo_create"));
    ASSERT_NOT_NULL(strstr(src, "forward_scene.color_tex[1]"));

    const char *files[] = {
        "blinn_phong.vert", "blinn_phong_vk.vert",
        "instanced.vert", "instanced_vk.vert",
        "skinned.vert", "skinned_vk.vert"
    };
    for (usize i = 0; i < sizeof(files) / sizeof(files[0]); i++) {
        char shader[16384];
        ASSERT_TRUE(read_shader_source(files[i], shader, sizeof(shader)));
        ASSERT_NOT_NULL(strstr(shader, "FORWARD_MRT"));
        ASSERT_NOT_NULL(strstr(shader, "v_velocity"));
    }

    ASSERT_TRUE(read_engine_source("rhi/rhi_vk.c", src, sizeof(src)));
    ASSERT_NOT_NULL(strstr(src, "bound_ubo"));
    ASSERT_NOT_NULL(strstr(src, "vk_rebind_uniform_buffers"));
    ASSERT_TRUE(read_engine_source("rhi/rhi.h", src, sizeof(src)));
    ASSERT_NOT_NULL(strstr(src, "rhi_cmd_clear_color_attachment"));
    ASSERT_TRUE(read_engine_source("main.c", src, sizeof(src)));
    ASSERT_NOT_NULL(strstr(src, "rhi_cmd_clear_color_attachment(cmd, 1u"));
    ASSERT_NOT_NULL(strstr(src, "rhi_offscreen_fbo_bind_load(cmd, &scene_fbo)"));
}

TEST(vulkan_ibl_gate_uses_compatible_vertex_contract)
{
    char src[131072];
    ASSERT_TRUE(read_engine_source("test_vulkan.c", src, sizeof(src)));
    ASSERT_NOT_NULL(strstr(src, "pbr_ibl_test_vk.vert"));
    ASSERT_TRUE(read_shader_source("pbr_ibl_test_vk.vert", src, sizeof(src)));
    ASSERT_NOT_NULL(strstr(src, "gl_Position = vec4(aPos, 1.0)"));
}

TEST(transparent_motion_vectors_do_not_alpha_blend_rt1)
{
    char src[131072];
    ASSERT_TRUE(read_engine_source("rhi/rhi_vk.c", src, sizeof(src)));
    ASSERT_NOT_NULL(strstr(src, "alpha_blend_color_only"));
    ASSERT_NOT_NULL(strstr(src, "enabled_features.independentBlend = VK_TRUE"));
    ASSERT_NOT_NULL(strstr(src, "vk->feat_independent_blend"));
    ASSERT_NOT_NULL(strstr(src, "blend_atts[1].blendEnable = VK_FALSE"));
    ASSERT_TRUE(read_engine_source("rhi/rhi_gl.c", src, sizeof(src)));
    ASSERT_NOT_NULL(strstr(src, "glBlendFunci(1, GL_ONE, GL_ZERO)"));
    ASSERT_TRUE(read_shader_source("particle.vert", src, sizeof(src)));
    ASSERT_NOT_NULL(strstr(src, "previous_pos"));
    ASSERT_NOT_NULL(strstr(src, "v_velocity"));
    ASSERT_TRUE(read_shader_source("particle_update.comp", src, sizeof(src)));
    ASSERT_NOT_NULL(strstr(src, "p.previous_pos"));
}

TEST(vulkan_command_buffer_updates_have_transfer_dst_usage)
{
    char src[524288];
    ASSERT_TRUE(read_engine_source("rhi/rhi_vk.c", src, sizeof(src)));
    /* rhi_cmd_update_buffer records vkCmdUpdateBuffer, whose target must
     * advertise TRANSFER_DST even when it is a UBO or uniform texel buffer. */
    ASSERT_NOT_NULL(strstr(src, "RHI_BUFFER_USAGE_UNIFORM"));
    ASSERT_NOT_NULL(strstr(src, "RHI_BUFFER_USAGE_TEXEL"));
    ASSERT_NOT_NULL(strstr(src, "ci.usage |= VK_BUFFER_USAGE_TRANSFER_DST_BIT"));
}

TEST(motion_blur_prefers_per_object_velocity_texture)
{
    char src[131072];
    ASSERT_TRUE(read_engine_source("renderer/motion_blur.h", src, sizeof(src)));
    ASSERT_NOT_NULL(strstr(src, "RHITexture velocity_tex"));
    ASSERT_TRUE(read_engine_source("renderer/motion_blur.c", src, sizeof(src)));
    ASSERT_NOT_NULL(strstr(src, "RHITexture velocity_tex"));
    ASSERT_NOT_NULL(strstr(src, "rhi_cmd_bind_textures_multi(cmd, tex, 3"));

    const char *files[] = { "motion_blur.frag", "motion_blur_vk.frag" };
    for (usize i = 0; i < sizeof(files) / sizeof(files[0]); i++) {
        char shader[16384];
        ASSERT_TRUE(read_shader_source(files[i], shader, sizeof(shader)));
        ASSERT_NOT_NULL(strstr(shader, "u_mb_velocity"));
        ASSERT_NOT_NULL(strstr(shader, "u_mb_use_velocity"));
        ASSERT_NOT_NULL(strstr(shader, "velocity = texture(u_mb_velocity"));
    }

    ASSERT_TRUE(read_engine_source("test_vulkan.c", src, sizeof(src)));
    ASSERT_NOT_NULL(strstr(src, "#include <renderer/motion_blur.h>"));
    ASSERT_NOT_NULL(strstr(src, "static bool tv_test_motion_blur_rt1"));
    ASSERT_NOT_NULL(strstr(src, "bool motion_rt1_pass = tv_test_motion_blur_rt1"));
    ASSERT_NOT_NULL(strstr(src, "RHI_FORMAT_R16G16_SFLOAT"));
    ASSERT_NOT_NULL(strstr(src, "motion blur RT1 texture did not affect output"));
}

TEST_MAIN_BEGIN()
    RUN_TEST(shader_read_rejects_oversized_file);
    RUN_TEST(upscale_shaders_guard_first_temporal_frame);
    RUN_TEST(postfx_passes_composite_chain_color);
    RUN_TEST(per_object_velocity_contract_is_not_camera_only);
    RUN_TEST(gl_ibl_test_contract_is_documented);
    RUN_TEST(ibl_capture_uses_to_sun_direction);
    RUN_TEST(gl_ibl_graphics_gate_runs_real_shared_test);
    RUN_TEST(forward_velocity_uses_single_pass_mrt_contract);
    RUN_TEST(vulkan_ibl_gate_uses_compatible_vertex_contract);
    RUN_TEST(transparent_motion_vectors_do_not_alpha_blend_rt1);
    RUN_TEST(vulkan_command_buffer_updates_have_transfer_dst_usage);
    RUN_TEST(motion_blur_prefers_per_object_velocity_texture);
TEST_MAIN_END()
