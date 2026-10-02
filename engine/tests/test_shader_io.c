#include "test_framework.h"
#include <core/shader_io.h>
#include <stdio.h>

static bool read_shader_source(const char *name, char *buf, usize cap)
{
    char rel[1024];
    /* MSVC does not merge separate __FILE__ expansions into one literal, so
     * `slash - __FILE__` across two expansions is garbage — expand it once. */
    const char *self = __FILE__;
    const char *slash = strrchr(self, '/');
    const char *backslash = strrchr(self, '\\');
    if (!slash || (backslash && backslash > slash)) slash = backslash;
    const char *candidates[4] = { NULL, name, NULL, NULL };
    char root_rel[1024];
    snprintf(root_rel, sizeof(root_rel), "../shaders/%s", name);
    candidates[2] = root_rel;
    if (slash) {
        snprintf(rel, sizeof(rel), "%.*s/../shaders/%s",
                 (int)(slash - self), self, name);
        candidates[0] = rel;
    }
    for (usize i = 0; i < 3 && candidates[i]; i++) {
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
    char root_rel[1024];
    /* MSVC does not merge separate __FILE__ expansions into one literal, so
     * `slash - __FILE__` across two expansions is garbage — expand it once. */
    const char *self = __FILE__;
    const char *slash = strrchr(self, '/');
    const char *backslash = strrchr(self, '\\');
    if (!slash || (backslash && backslash > slash)) slash = backslash;
    snprintf(root_rel, sizeof(root_rel), "../src/%s", name);
    FILE *root_file = fopen(root_rel, "rb");
    if (root_file) {
        usize n = fread(buf, 1, cap - 1, root_file);
        fclose(root_file);
        buf[n] = '\0';
        if (n > 0) return true;
    }
    if (!slash) return false;
    snprintf(rel, sizeof(rel), "%.*s/../src/%s",
             (int)(slash - self), self, name);
    FILE *f = fopen(rel, "rb");
    if (!f) return false;
    if (fseek(f, 0, SEEK_END) != 0) {
        fclose(f);
        return false;
    }
    long size = ftell(f);
    if (size < 0 || fseek(f, 0, SEEK_SET) != 0) {
        fclose(f);
        return false;
    }
    usize limit = (usize)size < cap - 1u ? (usize)size : cap - 1u;
    usize n = fread(buf, 1, limit, f);
    fclose(f);
    buf[n] = '\0';
    return n == limit && n > 0;
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

/* The static IBL cannot re-converge every frame. Keep a bounded, time-driven
 * re-capture that is opt-out with BREAK_IBL_STATIC=1, uses the frame's cached
 * to-sun direction, and emits only one standalone GPU dispatch per frame. */
TEST(ibl_runtime_recapture_contract)
{
    static char src[524288];
    ASSERT_TRUE(read_engine_source("main.c", src, sizeof(src)));
    ASSERT_NOT_NULL(strstr(src, "bool ibl_static = false"));
    ASSERT_NOT_NULL(strstr(src, "BREAK_IBL_STATIC"));
    ASSERT_NOT_NULL(strstr(src, "BREAK_IBL_REBAKE_FRAMES"));
    ASSERT_NOT_NULL(strstr(src, "ibl_recapture_accum"));
    ASSERT_NOT_NULL(strstr(src, "ibl_recapture_interval"));
    ASSERT_NOT_NULL(strstr(src, "if (ibl_recapture_accum >= ibl_recapture_interval)"));
    ASSERT_NOT_NULL(strstr(src, "render.ibl.rebake_active"));
    ASSERT_NOT_NULL(strstr(src, "ibl_rebake_step(&render.ibl, render.device)"));
    ASSERT_NOT_NULL(strstr(src, "ibl_rebake_begin(&render.ibl, render.device,"));
    ASSERT_NOT_NULL(strstr(src, "-sun_dir_vec.e[0], -sun_dir_vec.e[1], -sun_dir_vec.e[2]"));
    ASSERT_NOT_NULL(strstr(src, "continue;"));
}

TEST(gl_ibl_graphics_gate_runs_real_shared_test)
{
#if defined(ENGINE_PLATFORM_WINDOWS)
    return;
#else
    /* R584: test_vulkan.c outgrew 128KiB (TEST 12d) — static, per the
     * line-279 precedent; the grepped contracts sit past the old cut. */
    static char src[524288];
    ASSERT_TRUE(read_engine_source("test_vulkan.c", src, sizeof(src)));
    ASSERT_NOT_NULL(strstr(src, "static bool tv_test_ibl"));
    ASSERT_NOT_NULL(strstr(src, "bool ibl_pass = tv_test_ibl(&render"));
    ASSERT_NOT_NULL(strstr(src, "golden_pass && ibl_pass && idraw_pass"));
#endif
}

/* LightSystem owns the full clustered-light grid (>1 MiB). The Windows main
 * thread stack cannot hold it as a local in the graphics integration test. */
TEST(ibl_graphics_gate_keeps_cluster_grid_off_stack)
{
    static char src[524288]; /* R584: test_vulkan.c > 128KiB (see line ~215) */
    ASSERT_TRUE(read_engine_source("test_vulkan.c", src, sizeof(src)));
    const char *ibl = strstr(src, "static bool tv_test_ibl");
    ASSERT_NOT_NULL(ibl);
    ASSERT_NOT_NULL(strstr(ibl, "LightSystem *ls = calloc(1, sizeof(*ls))"));
    ASSERT_TRUE(strstr(ibl, "LightSystem ls;") == NULL);
}

TEST(forward_velocity_uses_single_pass_mrt_contract)
{
    /* main.c is ~460 KB — the old 128 KB stack buffer silently truncated it
     * (the markers below live past the cut). Static, per the line-277
     * precedent, and sized with headroom. */
    static char src[524288];
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
    static char src[524288]; /* R584: test_vulkan.c > 128KiB (see line ~215) */
    ASSERT_TRUE(read_engine_source("test_vulkan.c", src, sizeof(src)));
    ASSERT_NOT_NULL(strstr(src, "pbr_ibl_test_vk.vert"));
    ASSERT_TRUE(read_shader_source("pbr_ibl_test_vk.vert", src, sizeof(src)));
    ASSERT_NOT_NULL(strstr(src, "gl_Position = vec4(aPos, 1.0)"));
}

TEST(transparent_motion_vectors_do_not_alpha_blend_rt1)
{
    /* rhi_vk.c outgrew the old 128KiB cap; the grepped contracts sit past it. */
    static char src[262144];
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
    static char src[524288];
    ASSERT_TRUE(read_engine_source("rhi/rhi_vk.c", src, sizeof(src)));
    /* rhi_cmd_update_buffer records vkCmdUpdateBuffer, whose target must
     * advertise TRANSFER_DST even when it is a UBO or uniform texel buffer. */
    ASSERT_NOT_NULL(strstr(src, "RHI_BUFFER_USAGE_UNIFORM"));
    ASSERT_NOT_NULL(strstr(src, "RHI_BUFFER_USAGE_TEXEL"));
    ASSERT_NOT_NULL(strstr(src, "ci.usage |= VK_BUFFER_USAGE_TRANSFER_DST_BIT"));
}

TEST(vulkan_init_failure_cleanup_contract)
{
    static char src[524288];
    ASSERT_TRUE(read_engine_source("rhi/rhi_vk.c", src, sizeof(src)));
    ASSERT_NOT_NULL(strstr(src, "static void vk_init_cleanup"));
    ASSERT_NOT_NULL(strstr(src, "vk_init_cleanup(dev, vk)"));
    ASSERT_NOT_NULL(strstr(src, "static bool vk_create_depth"));
    ASSERT_NOT_NULL(strstr(src, "static bool vk_create_framebuffers"));
    ASSERT_NOT_NULL(strstr(src, "static bool vk_create_render_pass"));
    ASSERT_NOT_NULL(strstr(src, "vk->cmd_buffer_count"));
    ASSERT_NOT_NULL(strstr(src, "g_validation_gate_active = false"));
}

TEST(vulkan_distinct_graphics_present_queues_use_safe_sharing)
{
    static char src[524288];
    ASSERT_TRUE(read_engine_source("rhi/rhi_vk.c", src, sizeof(src)));
    ASSERT_NOT_NULL(strstr(src, "VkDeviceQueueCreateInfo queue_infos[2]"));
    ASSERT_NOT_NULL(strstr(src, "queue_info_count = 2u"));
    ASSERT_NOT_NULL(strstr(src, "VK_SHARING_MODE_CONCURRENT"));
    ASSERT_NOT_NULL(strstr(src, "sci.queueFamilyIndexCount = 2u"));
    ASSERT_NOT_NULL(strstr(src, "sci.pQueueFamilyIndices = queue_families"));
}

TEST(vulkan_swapchain_rebuild_recreates_render_pass_before_attachments)
{
    static char src[524288];
    ASSERT_TRUE(read_engine_source("rhi/rhi_vk.c", src, sizeof(src)));
    const char *recreate = strstr(src, "static void vk_recreate_swapchain");
    ASSERT_NOT_NULL(recreate);
    ASSERT_NOT_NULL(strstr(recreate, "vk_create_render_pass(vk)"));
    ASSERT_NOT_NULL(strstr(recreate, "!vk_create_depth(vk)"));
    ASSERT_NOT_NULL(strstr(recreate, "!vk_create_framebuffers(vk)"));
}

TEST(vulkan_swapchain_queries_fail_closed)
{
    static char src[524288];
    ASSERT_TRUE(read_engine_source("rhi/rhi_vk.c", src, sizeof(src)));
    ASSERT_NOT_NULL(strstr(src, "vkGetPhysicalDeviceSurfaceFormatsKHR(vk->physical, vk->surface,"));
    ASSERT_NOT_NULL(strstr(src, "&fmt_count, NULL) != VK_SUCCESS"));
    ASSERT_NOT_NULL(strstr(src, "VK: surface format query failed"));
    ASSERT_NOT_NULL(strstr(src, "vkGetPhysicalDeviceSurfacePresentModesKHR(vk->physical, vk->surface,"));
    ASSERT_NOT_NULL(strstr(src, "&mode_count, NULL) != VK_SUCCESS"));
    ASSERT_NOT_NULL(strstr(src, "VK: present mode query failed"));
    ASSERT_NOT_NULL(strstr(src, "VK: surface reports no present modes"));
}

TEST(vulkan_memory_allocation_rejects_invalid_type)
{
    static char src[524288];
    ASSERT_TRUE(read_engine_source("rhi/rhi_vk.c", src, sizeof(src)));
    /* Returns VkResult so callers can compare against VK_SUCCESS directly. */
    ASSERT_NOT_NULL(strstr(src, "static VkResult vk_allocate_memory"));
    ASSERT_NOT_NULL(strstr(src, "info->memoryTypeIndex == UINT32_MAX"));
    ASSERT_TRUE(strstr(src, "vkAllocateMemory(vk->device, &") == NULL);
}

TEST(vulkan_extension_and_device_enumeration_fail_closed)
{
    static char src[524288];
    ASSERT_TRUE(read_engine_source("rhi/rhi_vk.c", src, sizeof(src)));
    ASSERT_NOT_NULL(strstr(src, "static bool vk_instance_extension_available"));
    ASSERT_NOT_NULL(strstr(src, "VK: required instance extension unavailable"));
    ASSERT_NOT_NULL(strstr(src, "static bool vk_device_extension_available"));
    ASSERT_NOT_NULL(strstr(src, "VK: required device extension unavailable"));
    ASSERT_NOT_NULL(strstr(src, "vkEnumeratePhysicalDevices(vk->instance, &gpu_count, NULL) != VK_SUCCESS"));
    ASSERT_NOT_NULL(strstr(src, "vkEnumeratePhysicalDevices(vk->instance, &gpu_count, gpus) != VK_SUCCESS"));
    ASSERT_NOT_NULL(strstr(src, "VK: physical device enumeration failed"));
}

TEST(vulkan_physical_device_selection_is_suitable_and_fail_closed)
{
    static char src[524288];
    ASSERT_TRUE(read_engine_source("rhi/rhi_vk.c", src, sizeof(src)));
    ASSERT_NOT_NULL(strstr(src, "static bool vk_physical_device_suitable"));
    ASSERT_NOT_NULL(strstr(src, "VK_KHR_SWAPCHAIN_EXTENSION_NAME"));
    ASSERT_NOT_NULL(strstr(src, "vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physical, surface"));
    ASSERT_NOT_NULL(strstr(src, "vkGetPhysicalDeviceSurfaceFormatsKHR(physical, surface"));
    ASSERT_NOT_NULL(strstr(src, "vkGetPhysicalDeviceSurfacePresentModesKHR(physical, surface"));
    ASSERT_NOT_NULL(strstr(src, "vkGetPhysicalDeviceSurfaceSupportKHR(physical, q, surface"));
    ASSERT_NOT_NULL(strstr(src, "!= VK_SUCCESS"));
    ASSERT_NOT_NULL(strstr(src, "RE_VK_DEVICE_INDEX"));
    ASSERT_NOT_NULL(strstr(src, "requested GPU is not suitable"));
    ASSERT_NOT_NULL(strstr(src, "no suitable Vulkan GPU found"));
    ASSERT_TRUE(strstr(src, "falling back to the first device") == NULL);
}

TEST(ui_command_dispatch_context_is_internal)
{
    static char src[65536];
    ASSERT_TRUE(read_engine_source("myui/myui/my_ui_command.h", src, sizeof(src)));
    ASSERT_TRUE(strstr(src, "my_ui_command_dispatch_context_enter") == NULL);
    ASSERT_TRUE(strstr(src, "my_ui_command_dispatch_context_leave") == NULL);
    ASSERT_TRUE(read_engine_source("myui/myui/my_ui_command_internal.h", src,
                                   sizeof(src)));
    ASSERT_NOT_NULL(strstr(src, "my_ui_command_dispatch_context_enter"));
    ASSERT_NOT_NULL(strstr(src, "my_ui_command_dispatch_context_leave"));
    ASSERT_TRUE(read_engine_source("myui/mypal/dummy/my_pal_dummy.c", src, sizeof(src)));
    ASSERT_NOT_NULL(strstr(src, "my_ui_command_dispatch_context_enter"));
    ASSERT_NOT_NULL(strstr(src, "my_ui_command_dispatch_context_leave"));
    ASSERT_TRUE(read_engine_source("myui/mypal/break/my_pal_break.c", src, sizeof(src)));
    ASSERT_NOT_NULL(strstr(src, "my_ui_command_dispatch_context_enter"));
    ASSERT_NOT_NULL(strstr(src, "my_ui_command_dispatch_context_leave"));
}

TEST(vulkan_deferred_mip_upload_is_backend_owned)
{
    static char src[524288];
    ASSERT_TRUE(read_engine_source("rhi/rhi_vk.c", src, sizeof(src)));
    ASSERT_NOT_NULL(strstr(src, "VKBackend      *owner_backend"));
    ASSERT_NOT_NULL(strstr(src, "vk_mip_upload_owned_by_other"));
    ASSERT_NOT_NULL(strstr(src, "g_mip_upload_pending.owner_backend = vk"));
    ASSERT_NOT_NULL(strstr(src, "mip upload slot is owned by another device"));
}

TEST(motion_blur_prefers_per_object_velocity_texture)
{
    static char src[524288]; /* R584: test_vulkan.c > 128KiB (see line ~215) */
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

TEST(deferred_skinned_gbuffer_contract)
{
    const char *files[] = {
        "gbuffer_skinned.vert", "gbuffer_skinned_vk.vert"
    };
    for (usize i = 0; i < sizeof(files) / sizeof(files[0]); i++) {
        char shader[16384];
        ASSERT_TRUE(read_shader_source(files[i], shader, sizeof(shader)));
        ASSERT_NOT_NULL(strstr(shader, "u_joints"));
        ASSERT_NOT_NULL(strstr(shader, "texelFetch"));
        ASSERT_NOT_NULL(strstr(shader, "u_model"));
        ASSERT_NOT_NULL(strstr(shader, "u_view"));
        ASSERT_NOT_NULL(strstr(shader, "u_proj"));
        ASSERT_NOT_NULL(strstr(shader, "u_prev_mvp"));
        ASSERT_NOT_NULL(strstr(shader, "v_world_pos"));
        ASSERT_NOT_NULL(strstr(shader, "v_normal"));
        ASSERT_NOT_NULL(strstr(shader, "v_texcoord"));
        ASSERT_NOT_NULL(strstr(shader, "v_velocity"));
        ASSERT_NOT_NULL(strstr(shader, "curr_ndc"));
        ASSERT_NOT_NULL(strstr(shader, "prev_ndc"));
        ASSERT_NOT_NULL(strstr(shader, "512 +"));
        ASSERT_NOT_NULL(strstr(shader, "u_prev_mvp *"));
        ASSERT_NOT_NULL(strstr(shader, "prev_skin"));
    }

    char src[131072];
    ASSERT_TRUE(read_engine_source("renderer/deferred.h", src, sizeof(src)));
    ASSERT_NOT_NULL(strstr(src, "gbuffer_skinned_pipeline"));

    ASSERT_TRUE(read_engine_source("renderer/deferred.c", src, sizeof(src)));
    ASSERT_NOT_NULL(strstr(src, "gbuffer_skinned_pipeline"));
    ASSERT_NOT_NULL(strstr(src, "shaders/gbuffer_skinned_vk.vert"));
    ASSERT_NOT_NULL(strstr(src, "shaders/gbuffer_skinned.vert"));
    ASSERT_NOT_NULL(strstr(src, "skinned_desc.skinned_vertex"));
    ASSERT_NOT_NULL(strstr(src, "skinned_desc.uses_texel_buffer"));

    static char main_src[524288];
    ASSERT_TRUE(read_engine_source("main.c", main_src, sizeof(main_src)));
    ASSERT_NOT_NULL(strstr(main_src, "dsys->gbuffer_skinned_pipeline"));
    ASSERT_NOT_NULL(strstr(main_src, "skeleton_upload(&render.skeleton)"));
}

TEST(deferred_skinned_gbuffer_regressions_are_guarded)
{
    /* rhi_vk.c is ~350KB; the clustered definition sits ~220KB in, so the
     * buffer must comfortably cover it (1MB stack buffers are already the
     * pattern in this suite for main.c). */
    static char vk_src[524288];
    ASSERT_TRUE(read_engine_source("rhi/rhi_vk.c", vk_src, sizeof(vk_src)));

    /* A texel-buffer skinned G-Buffer still uses the ordinary 256B
     * model/view/proj/previous-MVP block; it must not enter clustered's
     * u_proj=-1 mapping. */
    const char *layout = strstr(vk_src, "if (pd && pd->skinned_gbuffer_layout)");
    const char *clustered = strstr(vk_src, "bool clustered =");
    ASSERT_NOT_NULL(layout);
    ASSERT_NOT_NULL(clustered);
    ASSERT_TRUE(layout < clustered);
    const char *layout_end = strstr(layout, "/* Terrain:");
    ASSERT_NOT_NULL(layout_end);
    ASSERT_TRUE(strstr(layout, "u_model") < layout_end);
    ASSERT_TRUE(strstr(layout, "u_view") < layout_end);
    ASSERT_TRUE(strstr(layout, "u_proj") < layout_end);
    ASSERT_TRUE(strstr(layout, "u_prev_mvp") < layout_end);
    ASSERT_NOT_NULL(strstr(layout, "return 128;") );
    ASSERT_NOT_NULL(strstr(layout, "return 192;") );

    static char main_src[524288];
    ASSERT_TRUE(read_engine_source("main.c", main_src, sizeof(main_src)));
    const char *skinned = strstr(main_src,
                                 "rhi_cmd_bind_pipeline(cmd, dsys->gbuffer_skinned_pipeline)");
    const char *terrain = strstr(main_src, "/* Render terrain. */");
    const char *restore = skinned ? strstr(skinned,
                                           "rhi_cmd_bind_pipeline(cmd, dsys->gbuffer_pipeline)") : NULL;
    ASSERT_NOT_NULL(skinned);
    ASSERT_NOT_NULL(terrain);
    ASSERT_NOT_NULL(restore);
    ASSERT_TRUE(restore < terrain);
}

/* R561: the mega-buffer path bakes static geometry into world space and keeps
 * the standard five-field indirect command. Per-node dynamic transform
 * indirection is intentionally NOT implemented (it would add per-vertex SSBO
 * fetches, per-frame transform/bounds uploads, and shader/descriptor churn
 * across both backends without a performance win on the static bake). Freeze
 * that boundary so a future refactor cannot silently change the contract. */
TEST(static_mega_geometry_contract_is_documented_and_unchanged)
{
    char src[131072];

    /* The indirect command must stay the standard five u32 fields used by both
     * Vulkan VkDrawIndexedIndirectCommand and GL DrawElementsIndirectCommand;
     * adding a per-draw transform index would change the shared buffer layout. */
    ASSERT_TRUE(read_engine_source("renderer/indirect_draw.h", src, sizeof(src)));
    ASSERT_NOT_NULL(strstr(src, "u32 index_count;"));
    ASSERT_NOT_NULL(strstr(src, "u32 instance_count;"));
    ASSERT_NOT_NULL(strstr(src, "u32 first_index;"));
    ASSERT_NOT_NULL(strstr(src, "i32 vertex_offset;"));
    ASSERT_NOT_NULL(strstr(src, "u32 first_instance;"));

    /* The bake excludes skinned nodes and pre-transforms positions + normals
     * into world space so u_model=identity works for the GPU-driven paths. */
    static char main_src[524288];
    ASSERT_TRUE(read_engine_source("main.c", main_src, sizeof(main_src)));
    ASSERT_NOT_NULL(strstr(main_src, "Vertices are pre-transformed to world space"));
    ASSERT_NOT_NULL(strstr(main_src, "nd->skinned"));
    ASSERT_NOT_NULL(strstr(main_src, "MegaVert"));

    /* Cull/compact shaders must not fetch per-node transforms; they only carry
     * the view-projection matrix, world-space bounds, and standard indirect
     * commands. A per-draw transform lookup would appear as an array binding
     * (mat4 transforms[]) or a per-object model uniform — neither is allowed. */
    ASSERT_TRUE(read_shader_source("unified_cull.comp", src, sizeof(src)));
    ASSERT_NOT_NULL(strstr(src, "CullObject"));
    ASSERT_NOT_NULL(strstr(src, "DrawIndexedIndirectCommand"));
    ASSERT_TRUE(strstr(src, "mat4 transforms") == NULL); /* no per-node array */
    ASSERT_TRUE(strstr(src, "transforms[]") == NULL);
    ASSERT_TRUE(strstr(src, "u_model") == NULL);

    ASSERT_TRUE(read_shader_source("compact_draws.comp", src, sizeof(src)));
    ASSERT_NOT_NULL(strstr(src, "DrawIndexedIndirectCommand"));
    ASSERT_TRUE(strstr(src, "mat4 transforms") == NULL);
    ASSERT_TRUE(strstr(src, "transforms[]") == NULL);
    ASSERT_TRUE(strstr(src, "u_model") == NULL);
}

/* R589: BREAK_FORWARD_CLUSTERED opt-in — the repaired pbr_clustered pipeline
 * (R579 终局 / R586 像素门实证) becomes reachable in production for the
 * forward static-scene draws. Lock the wiring markers: env gate, effective
 * pipeline selector, emissive-factor location, VK proj aux UBO, clustered
 * material wrapper (factor writes the shared blinn helper must not emit,
 * R579-D), per-frame observability counter. */
TEST(forward_clustered_opt_in_production_wiring)
{
    static char src[524288]; /* main.c > 460 KiB (line-238 precedent) */
    ASSERT_TRUE(read_engine_source("main.c", src, sizeof(src)));
    ASSERT_NOT_NULL(strstr(src, "BREAK_FORWARD_CLUSTERED"));
    ASSERT_NOT_NULL(strstr(src, "fwd_static_pipeline"));
    ASSERT_NOT_NULL(strstr(src, "cl_loc_emissive_factor"));
    ASSERT_NOT_NULL(strstr(src, "clustered_proj_ubo"));
    ASSERT_NOT_NULL(strstr(src, "clustered_bind_material"));
    ASSERT_NOT_NULL(strstr(src, "g_fwd_clustered_taken"));
    /* R589 MRT contract: the production clustered pipeline draws inside the
     * 2-attachment forward pass — shaders carry FORWARD_MRT velocity output
     * and the pipeline desc carries the 2-format MRT contract (validation
     * VUID-vkCmdDrawIndexedIndirectCount-renderPass-02684 otherwise). */
    ASSERT_NOT_NULL(strstr(src, "cfl_mrt"));
    const char *cfiles[] = {
        "pbr_clustered.vert", "pbr_clustered_vk.vert",
        "pbr_clustered.frag", "pbr_clustered_vk.frag"
    };
    for (usize i = 0; i < sizeof(cfiles) / sizeof(cfiles[0]); i++) {
        char sh[24576];
        ASSERT_TRUE(read_shader_source(cfiles[i], sh, sizeof(sh)));
        ASSERT_NOT_NULL(strstr(sh, "FORWARD_MRT"));
        ASSERT_NOT_NULL(strstr(sh, "v_velocity"));
    }
    char vsh[24576];
    ASSERT_TRUE(read_shader_source("pbr_clustered_vk.vert", vsh, sizeof(vsh)));
    /* R589: single aux-UBO binding {prev_vp, prev_model, proj} — the RHI
     * binds one UBO descriptor set per call, so two bindings never coexist. */
    ASSERT_NOT_NULL(strstr(vsh, "mat4 u_prev_model;"));
    ASSERT_NOT_NULL(strstr(vsh, "set = 2, binding = 0"));
}

/* R590: clustered INSTANCED variant — the ECS entity draws join the opt-in
 * clustered forward mode. Instance data rides a vertex-stage SSBO (the
 * shared texel set is capped at 2 bindings and GL texture units are
 * exhausted; particles.c proves vertex SSBO on both backends); the
 * clustered frag is reused unchanged (light texel set untouched). */
TEST(forward_clustered_instanced_variant_wiring)
{
    static char src[524288]; /* main.c > 460 KiB (line-238 precedent) */
    ASSERT_TRUE(read_engine_source("main.c", src, sizeof(src)));
    ASSERT_NOT_NULL(strstr(src, "clustered_inst_pipeline"));
    ASSERT_NOT_NULL(strstr(src, "pbr_clustered_inst_vk.vert"));
    /* instance_buf gains STORAGE usage so the same dual-slot buffer binds
     * as the variant's vertex SSBO (blinn path keeps the texel view). */
    ASSERT_NOT_NULL(strstr(src, "RHI_BUFFER_USAGE_TEXEL | RHI_BUFFER_USAGE_STORAGE"));
    /* per-mesh instanced draw binds the instance SSBO */
    ASSERT_NOT_NULL(strstr(src, "rhi_cmd_bind_storage_buffer(cmd, inst_slot"));

    /* VK vert: SSBO at set=2 (textures@0 texel@1 storage@2 ubo@3), frame
     * UBO at set=3, same merged {prev_vp, prev_model, proj} layout. */
    char vsh[8192];
    ASSERT_TRUE(read_shader_source("pbr_clustered_inst_vk.vert", vsh, sizeof(vsh)));
    ASSERT_NOT_NULL(strstr(vsh, "readonly buffer"));
    ASSERT_NOT_NULL(strstr(vsh, "set = 2, binding = 0"));
    ASSERT_NOT_NULL(strstr(vsh, "set = 3, binding = 0"));
    ASSERT_NOT_NULL(strstr(vsh, "gl_InstanceIndex"));
    ASSERT_NOT_NULL(strstr(vsh, "v_velocity"));

    /* GL vert: plain uniforms + SSBO at storage binding 0. */
    ASSERT_TRUE(read_shader_source("pbr_clustered_inst.vert", vsh, sizeof(vsh)));
    ASSERT_NOT_NULL(strstr(vsh, "readonly buffer"));
    ASSERT_NOT_NULL(strstr(vsh, "binding = 0"));

    /* R590 RHI fix: graphics storage binds must target the pipeline's OWN
     * storage set index (hardcoded 0 only worked for texture-less
     * pipelines like particles). */
    ASSERT_TRUE(read_engine_source("rhi/rhi_vk.c", src, sizeof(src)));
    ASSERT_NOT_NULL(strstr(src, "storage_set"));
}

/* R591: clustered SKINNED variant — skinned draws join the opt-in clustered
 * forward mode. Joint matrices ride a vertex SSBO (same R590 rationale:
 * texel set capped at 2, GL units exhausted); the clustered frag is reused
 * unchanged. The skinned_gbuffer_layout classification must NOT claim the
 * variant (it carries uses_storage for the joint SSBO — the formula is
 * narrowed so clustered mapping applies). */
TEST(forward_clustered_skinned_variant_wiring)
{
    static char src[524288]; /* main.c > 460 KiB (line-238 precedent) */
    ASSERT_TRUE(read_engine_source("main.c", src, sizeof(src)));
    ASSERT_NOT_NULL(strstr(src, "clustered_skin_pipeline"));
    ASSERT_NOT_NULL(strstr(src, "pbr_clustered_skin_vk.vert"));
    ASSERT_NOT_NULL(strstr(src, "rhi_cmd_bind_storage_buffer(cmd, skeleton_joint_slot"));

    /* Joint buffer gains STORAGE usage for the vertex SSBO bind. */
    ASSERT_TRUE(read_engine_source("animation/skeleton.c", src, sizeof(src)));
    ASSERT_NOT_NULL(strstr(src, "RHI_BUFFER_USAGE_TEXEL | RHI_BUFFER_USAGE_STORAGE"));

    /* R591 classification narrowing: a skinned_vertex pipeline WITH
     * uses_storage is the clustered-skinned variant — it must fall through
     * to the clustered uniform table, not the G-Buffer table. */
    ASSERT_TRUE(read_engine_source("rhi/rhi_vk.c", src, sizeof(src)));
    ASSERT_NOT_NULL(strstr(src, "!desc->uses_storage"));

    /* VK vert: joints SSBO at set=2, frame UBO at set=3, joint attributes. */
    char vsh[8192];
    ASSERT_TRUE(read_shader_source("pbr_clustered_skin_vk.vert", vsh, sizeof(vsh)));
    ASSERT_NOT_NULL(strstr(vsh, "readonly buffer"));
    ASSERT_NOT_NULL(strstr(vsh, "set = 2, binding = 0"));
    ASSERT_NOT_NULL(strstr(vsh, "set = 3, binding = 0"));
    ASSERT_NOT_NULL(strstr(vsh, "aJoints"));
    ASSERT_NOT_NULL(strstr(vsh, "v_velocity"));

    /* GL vert: plain uniforms + joints SSBO at storage binding 0. */
    ASSERT_TRUE(read_shader_source("pbr_clustered_skin.vert", vsh, sizeof(vsh)));
    ASSERT_NOT_NULL(strstr(vsh, "readonly buffer"));
    ASSERT_NOT_NULL(strstr(vsh, "aJoints"));
}

/* R592: clustered texture-ARRAY variant — the material-array single-execute
 * path (the default mega branch) joins the opt-in clustered forward mode.
 * The shared pbr_clustered frag gains a CLUSTERED_ARR conditional block
 * (2D_ARRAY samplers at the same bindings + per-layer factor tables from
 * the frame UBO's factor region at offsets 192+); the vert forwards
 * gl_BaseInstanceARB as the layer (blinn_phong_arr precedent). */
TEST(forward_clustered_array_variant_wiring)
{
    static char src[524288]; /* main.c > 460 KiB (line-238 precedent) */
    ASSERT_TRUE(read_engine_source("main.c", src, sizeof(src)));
    ASSERT_NOT_NULL(strstr(src, "clustered_arr_pipeline"));
    ASSERT_NOT_NULL(strstr(src, "pbr_clustered_arr_vk.vert"));
    /* factor region update into the shared frame UBO (offsets 192+) */
    ASSERT_NOT_NULL(strstr(src, "rhi_buffer_update_region"));
    /* the five arrays bound through the shared IBL helper */
    ASSERT_NOT_NULL(strstr(src, "mb->mats.mr_array"));

    /* Shared frag carries the CLUSTERED_ARR block with array samplers and
     * the factor-table block (both backends). */
    const char *frags[] = { "pbr_clustered.frag", "pbr_clustered_vk.frag" };
    for (usize i = 0; i < sizeof(frags) / sizeof(frags[0]); i++) {
        char fsh[24576];
        ASSERT_TRUE(read_shader_source(frags[i], fsh, sizeof(fsh)));
        ASSERT_NOT_NULL(strstr(fsh, "CLUSTERED_ARR"));
        ASSERT_NOT_NULL(strstr(fsh, "sampler2DArray"));
        ASSERT_NOT_NULL(strstr(fsh, "u_factor_arr[64]"));
        ASSERT_NOT_NULL(strstr(fsh, "vLayer"));
    }

    /* VK vert: ARB base-instance layer forward + velocity at location 4. */
    char vsh[8192];
    ASSERT_TRUE(read_shader_source("pbr_clustered_arr_vk.vert", vsh, sizeof(vsh)));
    ASSERT_NOT_NULL(strstr(vsh, "gl_BaseInstanceARB"));
    ASSERT_NOT_NULL(strstr(vsh, "location = 3) flat out uint vLayer"));
    ASSERT_NOT_NULL(strstr(vsh, "location = 4) out vec2 v_velocity"));
    ASSERT_NOT_NULL(strstr(vsh, "set = 2, binding = 0"));
}

/* R594: the material-array bake gains a NORMAL array — the clustered arr
 * variant's u_normal_map_arr slot (R592) finally receives per-layer normal
 * maps instead of the 1-layer flat fallback. MatArraySet grows normal_array;
 * BOTH dedup passes gain the normal handle; the mapping pass's R583-era
 * occlusion key drift (collect keyed on occ, mapping did not — materials
 * differing only in occlusion collapsed onto one layer) is repaired so the
 * two passes key identically. */
TEST(mat_array_bake_includes_normal_array)
{
    static char src[524288]; /* main.c > 460 KiB (line-238 precedent) */
    ASSERT_TRUE(read_engine_source("main.c", src, sizeof(src)));
    /* MatArraySet fifth array + unique-handle table + per-layer bake */
    ASSERT_NOT_NULL(strstr(src, "normal_array"));
    ASSERT_NOT_NULL(strstr(src, "uniq_nrm"));
    /* flat-normal fill for layer 0 and textureless layers */
    ASSERT_NOT_NULL(strstr(src, "flat_normal_rgba"));
    /* clustered arr path binds the baked array (not the 1-layer fallback) */
    ASSERT_NOT_NULL(strstr(src, "mb->mats.normal_array"));
    /* Both dedup passes key on the normal handle. */
    int nrm_key_hits = 0;
    for (const char *p = src; (p = strstr(p, "mat_arr_tex_same(uniq_nrm[i], nrm)")) != NULL; p++)
        nrm_key_hits++;
    ASSERT_TRUE(nrm_key_hits >= 2);
    /* R583 drift repair: the group->layer mapping pass matches on occlusion
     * too (previously only the collect pass did). */
    int occ_key_hits = 0;
    for (const char *p = src; (p = strstr(p, "mat_arr_tex_same(uniq_occ[i], occ)")) != NULL; p++)
        occ_key_hits++;
    ASSERT_TRUE(occ_key_hits >= 2);
}

/* R595: deferred G-Buffer normal-map perturbation — the five gbuffer frags
 * (base GL/VK, skinned VK, arr GL/VK; the GL skinned path shares gbuffer.frag)
 * sample the slot-3 normal map and perturb via derivative TBN (no tangent
 * attribute in the 32B/64B vertex contracts). Production bind_material has
 * always bound the material's normal map at slot 3 — only the shaders were
 * missing; the arr gbuffer path upgrades from fallback_normal to the R594
 * baked per-layer normal_array. */
TEST(deferred_gbuffer_normal_mapping_wiring)
{
    /* Base + skinned frags: 2D sampler at binding 3 + derivative TBN. */
    const char *base_frags[] = { "gbuffer.frag", "gbuffer_vk.frag",
                                 "gbuffer_skinned_vk.frag" };
    for (usize i = 0; i < sizeof(base_frags) / sizeof(base_frags[0]); i++) {
        char fsh[16384];
        ASSERT_TRUE(read_shader_source(base_frags[i], fsh, sizeof(fsh)));
        ASSERT_NOT_NULL(strstr(fsh, "binding = 3"));
        ASSERT_NOT_NULL(strstr(fsh, "u_normal_map"));
        ASSERT_NOT_NULL(strstr(fsh, "dFdx"));
        ASSERT_NOT_NULL(strstr(fsh, "octahedron_encode(nrm"));
    }
    /* Arr frags: per-layer 2D_ARRAY sampler, same perturbation. */
    const char *arr_frags[] = { "gbuffer_arr.frag", "gbuffer_arr_vk.frag" };
    for (usize i = 0; i < sizeof(arr_frags) / sizeof(arr_frags[0]); i++) {
        char fsh[16384];
        ASSERT_TRUE(read_shader_source(arr_frags[i], fsh, sizeof(fsh)));
        ASSERT_NOT_NULL(strstr(fsh, "binding = 3"));
        ASSERT_NOT_NULL(strstr(fsh, "u_normal_map_arr"));
        ASSERT_NOT_NULL(strstr(fsh, "dFdx"));
        ASSERT_NOT_NULL(strstr(fsh, "float(v_layer)"));
    }
    /* The arr gbuffer path binds the R594 baked per-layer normal array
     * (forward clustered arr bind is the other consumer — count both). */
    static char src[524288]; /* main.c > 460 KiB (line-238 precedent) */
    ASSERT_TRUE(read_engine_source("main.c", src, sizeof(src)));
    int nrm_bind_hits = 0;
    for (const char *p = src; (p = strstr(p, "mb->mats.normal_array")) != NULL; p++)
        nrm_bind_hits++;
    ASSERT_TRUE(nrm_bind_hits >= 2);
}

/* R596: the ECS PER-ENTITY fallback (the outer else of the instanced-pipeline
 * branch — runs when the instanced pipeline is invalid, or under the new
 * BREAK_FORCE_PER_ENTITY diagnostic) joins the opt-in clustered forward
 * mode: the STATIC clustered variant is bound with per-draw model via
 * cl_loc_model and clustered_bind_material per entity, instead of the
 * blinn pipeline. The selected-entity highlight stays blinn (debug tint
 * draw) and rebinds the blinn frame state. */
TEST(forward_clustered_per_entity_fallback_wiring)
{
    static char src[524288]; /* main.c > 460 KiB (line-238 precedent) */
    ASSERT_TRUE(read_engine_source("main.c", src, sizeof(src)));
    /* Diagnostic env that forces the fallback branch (makes the path
     * exercisable without an instanced-pipeline failure). */
    ASSERT_NOT_NULL(strstr(src, "BREAK_FORCE_PER_ENTITY"));
    /* Per-entity branch clustered split: frame emit + per-draw model +
     * per-material bind through the static clustered variant. */
    ASSERT_NOT_NULL(strstr(src, "pe_clustered"));
    ASSERT_NOT_NULL(strstr(src, "pe_clustered ? render.cl.cl_loc_model"));
    /* The blinn-era highlight rebinds the blinn frame state after the
     * clustered per-entity loop. */
    ASSERT_NOT_NULL(strstr(src, "highlight is a blinn-era debug"));
}

/* R597: forward clustered PBR becomes the DEFAULT forward path after the
 * blinn-vs-clustered comparison landed in clustered's favor on BOTH
 * backends (steady-state median GPU ms over 120 frames: VK 10.71 -> 8.75,
 * GL 23.92 -> 12.81 — and clustered carries the PBR + point-light feature
 * set blinn lacks). BREAK_FORWARD_CLUSTERED=0 opts out back to blinn. */
TEST(forward_clustered_default_on_after_bench)
{
    static char src[524288]; /* main.c > 460 KiB (line-238 precedent) */
    ASSERT_TRUE(read_engine_source("main.c", src, sizeof(src)));
    /* Default ON at declaration; env semantics inverted to opt-out. */
    ASSERT_NOT_NULL(strstr(src, "bool fwd_clustered_mode = true"));
    ASSERT_NOT_NULL(strstr(src, "if (e && !atoi(e)) fwd_clustered_mode = false"));
    /* The startup log names the opt-out. */
    ASSERT_NOT_NULL(strstr(src, "BREAK_FORWARD_CLUSTERED=0"));
}

/* R598: glTF occlusion STRENGTH in the non-arr clustered forward variants
 * (R586's residual boundary — strength was hardcoded 1.0 outside
 * CLUSTERED_ARR). The push-constant block has a free std430 pad at 228
 * (u_pom_enabled@224 + vec2@232): u_occlusion_strength lands there, the
 * block stays exactly 256B; GL gets the plain float uniform. Written per
 * material by clustered_bind_material (default 1.0 = full effect). */
TEST(forward_clustered_occlusion_strength_wiring)
{
    static char src[524288]; /* main.c > 460 KiB (line-238 precedent) */
    ASSERT_TRUE(read_engine_source("main.c", src, sizeof(src)));
    ASSERT_NOT_NULL(strstr(src, "cl_loc_occ_strength"));
    ASSERT_NOT_NULL(strstr(src, "occlusion_strength : 1.0f"));

    char fsh[24576];
    ASSERT_TRUE(read_shader_source("pbr_clustered.frag", fsh, sizeof(fsh)));
    ASSERT_NOT_NULL(strstr(fsh, "uniform float u_occlusion_strength"));
    ASSERT_NOT_NULL(strstr(fsh, "CL_OCC_STRENGTH (u_occlusion_strength)"));

    ASSERT_TRUE(read_shader_source("pbr_clustered_vk.frag", fsh, sizeof(fsh)));
    ASSERT_NOT_NULL(strstr(fsh, "float u_occlusion_strength;"));
    ASSERT_NOT_NULL(strstr(fsh, "228"));
    ASSERT_NOT_NULL(strstr(fsh, "CL_OCC_STRENGTH (pc.u_occlusion_strength)"));

    /* VK push-offset map entry in the clustered uniform table. */
    ASSERT_TRUE(read_engine_source("rhi/rhi_vk.c", src, sizeof(src)));
    ASSERT_NOT_NULL(strstr(src, "\"u_occlusion_strength\""));
}

TEST_MAIN_BEGIN()
    RUN_TEST(shader_read_rejects_oversized_file);
    RUN_TEST(upscale_shaders_guard_first_temporal_frame);
    RUN_TEST(postfx_passes_composite_chain_color);
    RUN_TEST(per_object_velocity_contract_is_not_camera_only);
    RUN_TEST(gl_ibl_test_contract_is_documented);
    RUN_TEST(ibl_capture_uses_to_sun_direction);
    RUN_TEST(ibl_runtime_recapture_contract);
    RUN_TEST(gl_ibl_graphics_gate_runs_real_shared_test);
    RUN_TEST(ibl_graphics_gate_keeps_cluster_grid_off_stack);
    RUN_TEST(forward_velocity_uses_single_pass_mrt_contract);
    RUN_TEST(vulkan_ibl_gate_uses_compatible_vertex_contract);
    RUN_TEST(transparent_motion_vectors_do_not_alpha_blend_rt1);
    RUN_TEST(vulkan_command_buffer_updates_have_transfer_dst_usage);
    RUN_TEST(vulkan_init_failure_cleanup_contract);
    RUN_TEST(vulkan_distinct_graphics_present_queues_use_safe_sharing);
    RUN_TEST(vulkan_swapchain_rebuild_recreates_render_pass_before_attachments);
    RUN_TEST(vulkan_swapchain_queries_fail_closed);
    RUN_TEST(vulkan_memory_allocation_rejects_invalid_type);
    RUN_TEST(vulkan_extension_and_device_enumeration_fail_closed);
    RUN_TEST(vulkan_physical_device_selection_is_suitable_and_fail_closed);
    RUN_TEST(ui_command_dispatch_context_is_internal);
    RUN_TEST(vulkan_deferred_mip_upload_is_backend_owned);
    RUN_TEST(motion_blur_prefers_per_object_velocity_texture);
    RUN_TEST(deferred_skinned_gbuffer_contract);
    RUN_TEST(deferred_skinned_gbuffer_regressions_are_guarded);
    RUN_TEST(static_mega_geometry_contract_is_documented_and_unchanged);
    RUN_TEST(forward_clustered_opt_in_production_wiring);
    RUN_TEST(forward_clustered_instanced_variant_wiring);
    RUN_TEST(forward_clustered_skinned_variant_wiring);
    RUN_TEST(forward_clustered_array_variant_wiring);
    RUN_TEST(mat_array_bake_includes_normal_array);
    RUN_TEST(deferred_gbuffer_normal_mapping_wiring);
    RUN_TEST(forward_clustered_per_entity_fallback_wiring);
    RUN_TEST(forward_clustered_default_on_after_bench);
    RUN_TEST(forward_clustered_occlusion_strength_wiring);
TEST_MAIN_END()
