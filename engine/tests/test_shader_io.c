#include "test_framework.h"
#include <core/shader_io.h>
#include <rhi/rhi.h>
#include <stdio.h>

#ifndef TEST_SOURCE_ROOT
#error "TEST_SOURCE_ROOT must point to the engine source tree"
#endif

static bool read_shader_source(const char *name, char *buf, usize cap)
{
    char rel[1024];
    /* MSVC does not merge separate __FILE__ expansions into one literal, so
     * `slash - __FILE__` across two expansions is garbage — expand it once. */
    const char *self = __FILE__;
    const char *slash = strrchr(self, '/');
    const char *backslash = strrchr(self, '\\');
    if (!slash || (backslash && backslash > slash)) slash = backslash;
    const char *candidates[5] = { NULL, NULL, name, NULL, NULL };
    char source_rel[1024];
    char root_rel[1024];
    snprintf(source_rel, sizeof(source_rel), "%s/shaders/%s", TEST_SOURCE_ROOT, name);
    candidates[0] = source_rel;
    snprintf(root_rel, sizeof(root_rel), "../shaders/%s", name);
    candidates[3] = root_rel;
    if (slash) {
        snprintf(rel, sizeof(rel), "%.*s/../shaders/%s",
                 (int)(slash - self), self, name);
        candidates[1] = rel;
    }
    for (usize i = 0; i < 4 && candidates[i]; i++) {
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
    char source_rel[1024];
    char root_rel[1024];
    /* MSVC does not merge separate __FILE__ expansions into one literal, so
     * `slash - __FILE__` across two expansions is garbage — expand it once. */
    const char *self = __FILE__;
    const char *slash = strrchr(self, '/');
    const char *backslash = strrchr(self, '\\');
    if (!slash || (backslash && backslash > slash)) slash = backslash;
    snprintf(source_rel, sizeof(source_rel), "%s/src/%s", TEST_SOURCE_ROOT, name);
    snprintf(root_rel, sizeof(root_rel), "../src/%s", name);
    FILE *root_file = fopen(source_rel, "rb");
    if (!root_file) root_file = fopen(root_rel, "rb");
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

static const ShaderIOPushMember *push_member_by_name(
    const ShaderIOPushMember *members, usize n, const char *name)
{
    for (usize i = 0u; i < n; i++)
        if (strcmp(members[i].name, name) == 0) return &members[i];
    return NULL;
}

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
    static char src[1048576];
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
    static char src[1048576];
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

/* R600: the D3D12 blinn_phong sidecars must mirror their GLSL twins field for
 * field. The contract that actually bites is the `// rhi:uniform` marker
 * table — that is what rhi_pipeline_bindings_resolve reads, so a missing
 * marker is the only thing that turns a dropped push write from a log line
 * into a silently zeroed camera. These four files therefore assert:
 *   - every base push member still carries its marker,
 *   - u_camera_pos carries NONE (it rides the b1 temporal CBV now),
 *   - the CBV is declared at b1, which is what adds the second descriptor
 *     table that truncates the push range from 252 to 248 bytes. */
TEST(hlsl_blinn_sidecars_mirror_glsl_twin_after_camera_moved_to_cbv)
{
    static const char *const k_sidecars[] = {
        "blinn_phong_hlsl.vert", "blinn_phong_hlsl.frag",
        "blinn_phong_mrt_hlsl.vert", "blinn_phong_mrt_hlsl.frag",
    };
    /* Names each sidecar declares in the push block, with their offsets. */
    static const char *const k_push_markers[] = {
        "// rhi:uniform u_model 0",
        "// rhi:uniform u_view 64",
        "// rhi:uniform u_proj 128",
        "// rhi:uniform u_light_dir 192",
        "// rhi:uniform u_light_color 208",
        "// rhi:uniform u_ambient 224",
    };
    usize i;
    for (i = 0; i < sizeof(k_sidecars) / sizeof(k_sidecars[0]); i++) {
        char src[16384];
        ASSERT_TRUE(read_shader_source(k_sidecars[i], src, sizeof(src)));
        /* The push block must not grow back past 240: that is the whole
         * reason the camera moved, and 240 is what survives the 248-byte
         * clamp a second descriptor table imposes. */
        ASSERT_FALSE(strstr(src, "u_camera_pos;  // 240") != NULL);
        ASSERT_FALSE(strstr(src, "rhi:uniform u_camera_pos") != NULL);
        /* The temporal CBV is the second table; losing it puts the camera
         * back into a push write that would be dropped. */
        ASSERT_NOT_NULL(strstr(src, "struct ForwardTemporal {"));
        ASSERT_NOT_NULL(strstr(src, "register(b1, space0)"));
    }
    /* Markers are per-stage (VS publishes the matrices, PS the lights), so
     * each stage file is checked against the members it must carry. */
    {
        char src[16384];
        ASSERT_TRUE(read_shader_source("blinn_phong_hlsl.vert", src, sizeof(src)));
        for (i = 0; i < 3; i++)
            ASSERT_NOT_NULL(strstr(src, k_push_markers[i]));
        ASSERT_TRUE(read_shader_source("blinn_phong_hlsl.frag", src, sizeof(src)));
        for (i = 3; i < sizeof(k_push_markers) / sizeof(k_push_markers[0]); i++)
            ASSERT_NOT_NULL(strstr(src, k_push_markers[i]));
    }
    /* The MRT pair is the only one that may emit velocity, and it must emit
     * it to RT1 — the whole point of the variant. */
    {
        char src[16384];
        ASSERT_TRUE(read_shader_source("blinn_phong_mrt_hlsl.vert", src, sizeof(src)));
        ASSERT_NOT_NULL(strstr(src, "float2 velocity : TEXCOORD3"));
        ASSERT_NOT_NULL(strstr(src, "curr_clip.xy / curr_clip.w - prev_clip.xy / prev_clip.w"));
        ASSERT_TRUE(read_shader_source("blinn_phong_mrt_hlsl.frag", src, sizeof(src)));
        ASSERT_NOT_NULL(strstr(src, "float2 velocity : SV_Target1"));
        ASSERT_TRUE(read_shader_source("blinn_phong_hlsl.frag", src, sizeof(src)));
        ASSERT_FALSE(strstr(src, "SV_Target1") != NULL);
    }
    /* The engine publishes the CBV bytes: one struct, one buffer, both
     * backends. If it drifts from the sidecar the whole contract is a lie. */
    {
        static char src[1048576];
        ASSERT_TRUE(read_engine_source("main.c", src, sizeof(src)));
        ASSERT_NOT_NULL(strstr(src, "cam_pos[3]"));
        ASSERT_NOT_NULL(strstr(src, "forward_temporal_ubo"));
        ASSERT_NOT_NULL(strstr(src, "forward_temporal_ubo_write"));
        /* R606: the production forward pipeline must reach the sidecar
         * through the path API on a sidecar backend, and it must ask
         * for the MRT pair -- the pipeline declares two colour
         * attachments, so the non-MRT sidecar would drop the velocity
         * output RT1 exists for. The temporal UBO must be bound at the
         * index the backend reports: a hard 0 is the GLSL binding and a
         * silent no-op against register b1. */
        ASSERT_NOT_NULL(strstr(src, "caps.shader_sidecar_paths"));
        ASSERT_NOT_NULL(strstr(src,
            "rhi_shader_create_path(rs->device, \"shaders/blinn_phong_mrt.vert\", false)"));
        ASSERT_NOT_NULL(strstr(src,
            "rhi_shader_create_path(rs->device, \"shaders/blinn_phong_mrt.frag\", true)"));
        ASSERT_NOT_NULL(strstr(src,
            "rs->temporal_ubo_binding = caps.temporal_ubo_binding;"));
        ASSERT_TRUE(strstr(src,
            "rhi_cmd_bind_uniform_buffer(cmd, render.forward_temporal_ubo, 0u)") == NULL);
    }
}

/* R605: the D3D12 root-signature builder used to run once per shader stage with
 * no dedupe, so a register both stages declared produced TWO descriptor tables
 * for the same (type, register, space). Only the last index was ever recorded
 * in image_root_params / uniform_root_params and only that one was ever bound,
 * leaving a root parameter permanently unbound -- which D3D12 forbids, and
 * which a vertex shader reading a cbuffer paid for: it read the unbound table
 * and got garbage, silently on hardware and as device loss on WARP. The pixel
 * stage read the bound table and was fine, which is what made the asymmetry so
 * hard to see.
 *
 * Two things are pinned here, both of which a naive fix gets wrong:
 *   1. the tables must be reused, not duplicated;
 *   2. the visibility must be ASSIGNED D3D12_SHADER_VISIBILITY_ALL, never
 *      OR-ed with the incoming stage visibility -- in this SDK the
 *      D3D12_SHADER_VISIBILITY enumerators are sequential values (ALL 0,
 *      VERTEX 1, PIXEL 5), not bitmasks, so VERTEX | PIXEL evaluates to PIXEL
 *      and silently drops vertex visibility. That failure still builds fine and
 *      only shows up as the same unreadable-cbuffer symptom, so it earns a
 *      test of its own. */
TEST(d3d12_root_signature_dedupes_per_stage_tables_with_full_visibility)
{
    static char src[524288];
    ASSERT_TRUE(read_engine_source("rhi/rhi_d3d12.c", src, sizeof(src)));
    /* The dedupe itself. */
    ASSERT_NOT_NULL(strstr(src, "for (reuse = 0u; reuse < b->param_count; ++reuse)"));
    ASSERT_NOT_NULL(strstr(src, "goto next_binding;"));
    ASSERT_NOT_NULL(strstr(src, "next_binding:"));
    /* Visibility assigned, never OR-ed: the OR form is a silent regression. */
    ASSERT_NOT_NULL(strstr(src,
                         "rp->ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;"));
    ASSERT_FALSE(strstr(src, "rp->ShaderVisibility |= visibility;") != NULL);
    /* The reused param index has to be recorded for BOTH binding kinds,
     * otherwise the resource still resolves to the param that is never bound. */
    ASSERT_NOT_NULL(strstr(src,
                         "b->image_root_params[base_register] = reuse;"));
    ASSERT_NOT_NULL(strstr(src,
                         "b->uniform_root_params[base_register] = reuse;"));
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
    const char *recreate = strstr(src, "static RHIResult vk_recreate_swapchain");
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

TEST(shader_abi_reflection_is_deterministic_and_backend_neutral)
{
    const char src[] =
        "layout(std430, set = 1, binding = 2) readonly buffer Draws { uint data[]; };\n"
        "layout(push_constant) uniform PushConstants { vec4 value; };\n"
        "layout(set = 0, binding = 4) uniform sampler2D u_color;\n"
        "layout(std140, binding = 0) uniform Frame { mat4 vp; };\n";
    ShaderIOBinding a[4];
    ShaderIOBinding b[4];
    usize na = shader_reflect_bindings(src, sizeof(src) - 1u, a, 4u);
    usize nb = shader_reflect_bindings(src, sizeof(src) - 1u, b, 4u);
    ASSERT_EQ(na, (usize)4);
    ASSERT_EQ(nb, na);
    ASSERT_EQ(memcmp(a, b, sizeof(a)), 0);
    ASSERT_STR_EQ(a[0].name, "Frame");
    ASSERT_EQ(a[0].set, 0u);
    ASSERT_EQ(a[0].binding, 0u);
    ASSERT_EQ(a[0].layout, SHADER_IO_LAYOUT_STD140);
    ASSERT_STR_EQ(a[1].name, "PushConstants");
    ASSERT_EQ(a[1].kind, SHADER_IO_RESOURCE_PUSH_CONSTANT);
    ASSERT_STR_EQ(a[2].name, "u_color");
    ASSERT_EQ(a[2].kind, SHADER_IO_RESOURCE_SAMPLER);
    ASSERT_EQ(a[3].kind, SHADER_IO_RESOURCE_STORAGE);
    ASSERT_EQ(a[3].set, 1u);
    ASSERT_EQ(a[3].binding, 2u);
}

TEST(shader_abi_reflection_capacity_and_gl_defaults)
{
    const char src[] = "uniform sampler2D tex;\n"
                       "layout(binding = 3) buffer Storage { uint x[]; };\n";
    ShaderIOBinding bindings[2];
    ASSERT_EQ(shader_reflect_bindings(src, sizeof(src) - 1u, bindings, 2u), (usize)2);
    ASSERT_EQ(bindings[0].set, 0u);
    ASSERT_EQ(bindings[0].binding, 0u);
    ASSERT_EQ(bindings[0].kind, SHADER_IO_RESOURCE_SAMPLER);
    ASSERT_EQ(shader_reflect_bindings(src, sizeof(src) - 1u, bindings, 1u), (usize)0);
}

TEST(shader_abi_reflection_rejects_malformed_boundaries)
{
    const char source[] =
        "// layout(binding = 9) uniform sampler2D ignored;\n"
        "#define GENERATED 1\n"
        "layout(binding = nope) uniform sampler2D bad_binding;\n"
        "layout(location = 2) uniform sampler2D bad_layout;\n"
        "uniform mysteryType bad_format;\n"
        "layout(binding = 4) uniform sampler2D valid;\n";
    ShaderIOBinding bindings[2];
    usize count = shader_reflect_bindings(source, sizeof(source) - 1u,
                                          bindings, 2u);
    ASSERT_EQ(count, (usize)1);
    ASSERT_STR_EQ(bindings[0].name, "valid");
    ASSERT_EQ(bindings[0].binding, 4u);
}

TEST(shader_abi_reflection_rejects_unknown_layout_and_duplicate_bindings)
{
    const char malformed[] =
        "layout(binding = 1, made_up = 2) uniform sampler2D unknown_layout;\n"
        "layout(set = 0, binding = 3) uniform sampler2D first;\n"
        "layout(set = 0, binding = 3) buffer Conflict { uint value; };\n";
    ShaderIOBinding bindings[4];
    ASSERT_EQ(shader_reflect_bindings(malformed, sizeof(malformed) - 1u,
                                      bindings, 4u), (usize)0);
}

TEST(shader_abi_reflection_rejects_unsupported_resource_kind)
{
    const char malformed[] =
        "layout(binding = 1) uniform atomic_uint counters;\n"
        "layout(binding = 2) uniform sampler2D valid;\n";
    ShaderIOBinding bindings[2];
    ASSERT_EQ(shader_reflect_bindings(malformed, sizeof(malformed) - 1u,
                                      bindings, 2u), (usize)1);
    ASSERT_STR_EQ(bindings[0].name, "valid");
}

TEST(shader_abi_reflection_rejects_duplicates_beyond_output_capacity)
{
    const char malformed[] =
        "layout(binding = 1) uniform sampler2D first;\n"
        "layout(binding = 2) uniform sampler2D second;\n"
        "layout(binding = 1) uniform sampler2D duplicate;\n";
    ShaderIOBinding binding;
    ASSERT_EQ(shader_reflect_bindings(malformed, sizeof(malformed) - 1u,
                                      &binding, 1u), (usize)0);
}

TEST(shader_abi_reflection_requires_exact_supported_types)
{
    const char source[] =
        "layout(binding = 1) uniform sampler2DShadow rejected;\n"
        "layout(binding = 2) uniform sampler2D accepted;\n";
    ShaderIOBinding bindings[2];
    ASSERT_EQ(shader_reflect_bindings(source, sizeof(source) - 1u,
                                      bindings, 2u), (usize)1);
    ASSERT_STR_EQ(bindings[0].name, "accepted");
}

TEST(shader_abi_reflection_classifies_images)
{
    const char source[] = "layout(binding = 5) uniform image2D output_image;\n";
    ShaderIOBinding binding[1];
    ASSERT_EQ(shader_reflect_bindings(source, sizeof(source) - 1u,
                                      binding, 1u), (usize)1);
    ASSERT_EQ(binding[0].kind, SHADER_IO_RESOURCE_IMAGE);
    ASSERT_STR_EQ(binding[0].format, "image2D");
}

TEST(shader_abi_reflection_accepts_non_nul_input_and_hashes_canonically)
{
    const char first[] = "layout(binding = 2) uniform sampler2D b;\n"
                         "layout(binding = 1) uniform sampler2D a;\n";
    const char second[] = "layout(binding = 1) uniform sampler2D a;\n"
                          "layout(binding = 2) uniform sampler2D b;\n";
    ShaderIOBinding a[2];
    ShaderIOBinding b[2];
    ShaderIOBinding c[2];
    ASSERT_EQ(shader_reflect_bindings(first, sizeof(first) - 1u, a, 2u), (usize)2);
    ASSERT_EQ(shader_reflect_bindings(second, sizeof(second) - 1u, b, 2u), (usize)2);
    ASSERT_EQ(shader_reflect_bindings("layout(binding = 7) uniform sampler2D x;TRAIL",
                                     strlen("layout(binding = 7) uniform sampler2D x;"),
                                     c, 2u), (usize)1);
    ASSERT_EQ(shader_reflect_bindings_hash(a, 2u), shader_reflect_bindings_hash(b, 2u));
    ASSERT_NEQ(shader_reflect_bindings_hash(a, 2u), (u64)0);
}

TEST(shader_abi_hash_ignores_struct_padding)
{
    ShaderIOBinding a;
    ShaderIOBinding b;
    memset(&a, 0x11, sizeof(a));
    memset(&b, 0xee, sizeof(b));
    snprintf(a.name, sizeof(a.name), "resource");
    snprintf(b.name, sizeof(b.name), "resource");
    snprintf(a.format, sizeof(a.format), "sampler2D");
    snprintf(b.format, sizeof(b.format), "sampler2D");
    a.kind = b.kind = SHADER_IO_RESOURCE_SAMPLER;
    a.layout = b.layout = SHADER_IO_LAYOUT_DEFAULT;
    a.set = b.set = 2u;
    a.binding = b.binding = 7u;
    a.location = b.location = 13u;
    ASSERT_EQ(shader_reflect_bindings_hash(&a, 1u),
              shader_reflect_bindings_hash(&b, 1u));
}

TEST(shader_abi_reflection_rejects_extreme_lengths_and_missing_names)
{
    const char malformed[] =
        "layout(notbinding = 2) uniform sampler2D spoofed;\n"
        "layout(binding = 2) uniform sampler2D ;\n"
        "layout(push_constant) uniform { vec4 value; };\n";
    ShaderIOBinding bindings[2];
    ASSERT_EQ(shader_reflect_bindings(malformed, sizeof(malformed) - 1u,
                                      bindings, 2u), (usize)0);
    ASSERT_EQ(shader_reflect_bindings(malformed, (usize)-1, NULL, 0u), (usize)0);
    ASSERT_EQ(shader_reflect_bindings("x", (usize)-1, bindings, 2u), (usize)0);
    ASSERT_EQ(shader_reflect_bindings_hash(NULL, (usize)-1), (u64)0);
}

TEST(shader_abi_hash_handles_non_nul_fixed_fields)
{
    ShaderIOBinding a;
    ShaderIOBinding b;
    memset(&a, 'A', sizeof(a));
    memset(&b, 'A', sizeof(b));
    a.kind = b.kind = SHADER_IO_RESOURCE_SAMPLER;
    a.layout = b.layout = SHADER_IO_LAYOUT_DEFAULT;
    a.set = b.set = 1u;
    a.binding = b.binding = 3u;
    a.location = b.location = 5u;
    ASSERT_EQ(shader_reflect_bindings_hash(&a, 1u),
              shader_reflect_bindings_hash(&b, 1u));
    b.format[SHADER_IO_FORMAT_MAX - 1u] = 'B';
    ASSERT_NEQ(shader_reflect_bindings_hash(&a, 1u),
               shader_reflect_bindings_hash(&b, 1u));
}

TEST(shader_abi_hash_total_order_covers_all_hashed_fields)
{
    ShaderIOBinding first;
    ShaderIOBinding second;
    memset(&first, 0, sizeof(first));
    memset(&second, 0, sizeof(second));
    snprintf(first.name, sizeof(first.name), "same");
    snprintf(second.name, sizeof(second.name), "same");
    snprintf(first.format, sizeof(first.format), "float");
    snprintf(second.format, sizeof(second.format), "vec4");
    first.kind = second.kind = SHADER_IO_RESOURCE_UNIFORM;
    first.set = second.set = 1u;
    first.binding = second.binding = 2u;
    first.layout = SHADER_IO_LAYOUT_STD140;
    second.layout = SHADER_IO_LAYOUT_STD430;
    first.location = 3u;
    second.location = 4u;
    ASSERT_NEQ(shader_reflect_bindings_hash(&first, 1u),
               shader_reflect_bindings_hash(&second, 1u));
    ASSERT_EQ(shader_reflect_bindings_hash((ShaderIOBinding[]){ first, second }, 2u),
              shader_reflect_bindings_hash((ShaderIOBinding[]){ second, first }, 2u));
}

TEST(shader_abi_reflection_partial_input_skips_malformed_declarations)
{
    const char source[] =
        "layout(binding = nope) uniform sampler2D malformed;\n"
        "layout(binding = 6) uniform sampler2D valid;\n";
    ShaderIOBinding binding[1];
    ASSERT_EQ(shader_reflect_bindings(source, sizeof(source) - 1u,
                                      binding, 1u), (usize)1);
    ASSERT_STR_EQ(binding[0].name, "valid");
}

TEST(shader_abi_rhi_formats_mrt_resources_and_indirect)
{
    const RHIFormat formats[] = { RHI_FORMAT_R8G8B8A8_UNORM,
                                  RHI_FORMAT_R16G16_SFLOAT };
    ASSERT_TRUE(rhi_format_is_color(RHI_FORMAT_R32_FLOAT));
    ASSERT_FALSE(rhi_format_is_color(RHI_FORMAT_D32_FLOAT));
    ASSERT_FALSE(rhi_format_is_color(RHI_FORMAT_UNDEFINED));
    ASSERT_FALSE(rhi_format_is_color((RHIFormat)99));
    ASSERT_TRUE(rhi_mrt_formats_valid(formats, 2u));
    ASSERT_FALSE(rhi_mrt_formats_valid(formats, 0u));
    ASSERT_TRUE(rhi_mrt_formats_valid(
        (const RHIFormat[]){ RHI_FORMAT_R8G8B8A8_UNORM,
                             RHI_FORMAT_B8G8R8A8_UNORM,
                             RHI_FORMAT_R16G16B16A16_SFLOAT,
                             RHI_FORMAT_R16G16_SFLOAT,
                             RHI_FORMAT_R32_FLOAT }, 5u));
    ASSERT_FALSE(rhi_mrt_formats_valid(
        (const RHIFormat[]){ RHI_FORMAT_R8G8B8A8_UNORM,
                             RHI_FORMAT_B8G8R8A8_UNORM,
                             RHI_FORMAT_R16G16B16A16_SFLOAT,
                             RHI_FORMAT_R16G16_SFLOAT,
                             RHI_FORMAT_R32_FLOAT,
                             RHI_FORMAT_R8G8B8A8_UNORM }, 6u));
    ASSERT_FALSE(rhi_mrt_formats_valid((const RHIFormat[]){ RHI_FORMAT_D32_FLOAT }, 1u));
    ASSERT_FALSE(rhi_mrt_formats_valid((const RHIFormat[]){ (RHIFormat)99 }, 1u));
    ASSERT_FALSE(rhi_mrt_formats_valid(NULL, 1u));
    ASSERT_TRUE(rhi_shader_resource_kind_is_buffer(RHI_SHADER_RESOURCE_UNIFORM));
    ASSERT_TRUE(rhi_shader_resource_kind_is_buffer(RHI_SHADER_RESOURCE_STORAGE));
    ASSERT_TRUE(rhi_shader_resource_kind_is_push(RHI_SHADER_RESOURCE_PUSH_CONSTANT));
    ASSERT_FALSE(rhi_shader_resource_kind_is_push(RHI_SHADER_RESOURCE_UNIFORM));
    ASSERT_EQ(sizeof(RHIIndexedIndirectCommand), (usize)20);
    ASSERT_TRUE(rhi_indirect_abi_valid(20u, 1u));
    ASSERT_TRUE(rhi_indirect_abi_valid(32u, 2u));
    ASSERT_FALSE(rhi_indirect_abi_valid(16u, 1u));
    ASSERT_FALSE(rhi_indirect_abi_valid(21u, 1u));
    ASSERT_FALSE(rhi_indirect_abi_valid(20u, 0u));
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
    /* 计划 E Task 6 F2 迁移后基名经 shader_variant_path 派生 _vk 变体；
     * 断言改为钉住新接线（基名 + caps.shader_variant 驱动）。 */
    ASSERT_NOT_NULL(strstr(src, "shader_variant_path(\"shaders/gbuffer_skinned.vert\""));
    /* Task 6 review fix：skinned frag 不是 base+后缀变体对（VK 用独立文件
     * gbuffer_skinned_vk.frag——GbufFactors UBO 需 Set 2；GL 用 gbuffer.frag）。
     * 钉住按 caps.shader_variant 三元选择的赋值形状。 */
    ASSERT_NOT_NULL(strstr(src,
        "const char *skinned_fs = (caps.shader_variant == (u32)RHI_SHADER_VARIANT_GLSL_VK)"));
    ASSERT_NOT_NULL(strstr(src, "? \"shaders/gbuffer_skinned_vk.frag\""));
    ASSERT_NOT_NULL(strstr(src, ": \"shaders/gbuffer.frag\";"));
    ASSERT_NOT_NULL(strstr(src, "skinned_desc.skinned_vertex"));
    ASSERT_NOT_NULL(strstr(src, "skinned_desc.uses_texel_buffer"));

    static char main_src[1048576];
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
     * u_proj=-1 mapping. Plan E Task 5 Stage C-2 batch 6 deleted the
     * hand-written offset tables (reflection is the authority), so the
     * contract re-anchors: the skinned_gbuffer_layout classification flag
     * must still be set at pipeline create, and the shader's own push
     * block must carry the four members at 0/64/128/192 — the 5a gate
     * table pins the same rows (vk_push_tables_match_reflection). */
    const char *flag = strstr(vk_src, "pd->skinned_gbuffer_layout =");
    ASSERT_NOT_NULL(flag);
    ASSERT_NOT_NULL(strstr(vk_src, "!desc->uses_storage"));

    char sh[16384];
    ASSERT_TRUE(read_shader_source("gbuffer_skinned_vk.vert", sh, sizeof(sh)));
    ShaderIOPushMember members[8];
    usize n = shader_reflect_push_constants(sh, strlen(sh), members, 8u);
    ASSERT_TRUE(n >= 4u);
    const ShaderIOPushMember *m;
    m = push_member_by_name(members, n, "u_model");    ASSERT_NOT_NULL(m); ASSERT_EQ(m->offset, 0u);
    m = push_member_by_name(members, n, "u_view");     ASSERT_NOT_NULL(m); ASSERT_EQ(m->offset, 64u);
    m = push_member_by_name(members, n, "u_proj");     ASSERT_NOT_NULL(m); ASSERT_EQ(m->offset, 128u);
    m = push_member_by_name(members, n, "u_prev_mvp"); ASSERT_NOT_NULL(m); ASSERT_EQ(m->offset, 192u);

    static char main_src[1048576];
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
    static char main_src[1048576];
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
    static char src[1048576]; /* main.c > 512 KiB */
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
    static char src[1048576]; /* main.c > 512 KiB */
    ASSERT_TRUE(read_engine_source("main.c", src, sizeof(src)));
    ASSERT_NOT_NULL(strstr(src, "clustered_inst_pipeline"));
    /* 计划 E Task 2：路径由 caps.shader_variant 驱动（shader_variant_path），
     * 契约改为断言基底路径 + 变体选择调用，而非硬编码 _vk 文件名。 */
    ASSERT_NOT_NULL(strstr(src, "shader_variant_path(\"shaders/pbr_clustered_inst.vert\""));
    ASSERT_NOT_NULL(strstr(src, "caps.shader_variant"));
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
    static char src[1048576]; /* main.c > 512 KiB */
    ASSERT_TRUE(read_engine_source("main.c", src, sizeof(src)));
    ASSERT_NOT_NULL(strstr(src, "clustered_skin_pipeline"));
    /* 计划 E Task 2：caps 驱动变体路径（见 instanced 变体注释）。 */
    ASSERT_NOT_NULL(strstr(src, "shader_variant_path(\"shaders/pbr_clustered_skin.vert\""));
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
    static char src[1048576]; /* main.c > 512 KiB */
    ASSERT_TRUE(read_engine_source("main.c", src, sizeof(src)));
    ASSERT_NOT_NULL(strstr(src, "clustered_arr_pipeline"));
    /* 计划 E Task 2：caps 驱动变体路径（见 instanced 变体注释）。 */
    ASSERT_NOT_NULL(strstr(src, "shader_variant_path(\"shaders/pbr_clustered_arr.vert\""));
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
    static char src[1048576]; /* main.c > 512 KiB */
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
    static char src[1048576]; /* main.c > 512 KiB */
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
    static char src[1048576]; /* main.c > 512 KiB */
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
    static char src[1048576]; /* main.c > 512 KiB */
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
    static char src[1048576]; /* main.c > 512 KiB */
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

    /* Plan E Task 5 Stage C-2 batch 6: the hand-written VK push-offset map
     * was deleted (reflection is the authority; the 5a gate table pins
     * u_occlusion_strength@228). Re-anchor the "has a resolvable VK slot"
     * contract on reflection itself. */
    {
        ShaderIOPushMember members[32];
        usize n = shader_reflect_push_constants(fsh, strlen(fsh), members, 32u);
        const ShaderIOPushMember *m = push_member_by_name(members, n,
                                                           "u_occlusion_strength");
        ASSERT_NOT_NULL(m);
        ASSERT_EQ(m->offset, 228u);
        ASSERT_EQ(m->size, 4u);
    }
}

/* R599: TEST 7b restored as a REAL, both-backend gate. Two latent defects
 * had stacked since R579: (1) the gate returned true unconditionally —
 * diagnostic-only, vacuous even on VK; (2) its scene never consumed mr
 * (minimal-write discipline from the broken-vert era left the camera
 * in-plane, light counts 0, fog 0/0 — the output was mr-independent, so
 * any real assertion measured moved=0). The GL park was retired after the
 * driver probe (24.10.38 rasterizes the draw fine; the R579-B "zero
 * fragments" no-op is gone) and the scene was rebuilt to TEST 7c's full
 * frame-state write set. */
TEST(pbr_factor_gate_restored_real_assertion)
{
    static char src[524288]; /* test_vulkan.c lives in engine/src */
    ASSERT_TRUE(read_engine_source("test_vulkan.c", src, sizeof(src)));
    /* Non-vacuous assertion: lit pixels must exist AND the factor change
     * must move at least one of them. */
    ASSERT_NOT_NULL(strstr(src, "REAL A/B assertion restored"));
    ASSERT_NOT_NULL(strstr(src, "lit > 0u && moved > 0u"));
    ASSERT_NOT_NULL(strstr(src, "return pass;"));
    /* GL park retired — the call site runs the gate on both backends. */
    ASSERT_NOT_NULL(strstr(src, "R599: gate restored on GL"));
    /* The scene writes the full frame state (light counts evaluated). */
    ASSERT_NOT_NULL(strstr(src, "rhi_cmd_set_uniform_i32(cmd, l_pc,   1)"));
}

TEST(variant_path_appends_suffix_before_extension)
{
    char out[128];
    ASSERT_TRUE(shader_variant_path("shaders/blinn_phong.vert",
                                    RHI_SHADER_VARIANT_GLSL_VK,
                                    out, sizeof(out)) != NULL);
    ASSERT_TRUE(strcmp(out, "shaders/blinn_phong_vk.vert") == 0);
    ASSERT_TRUE(shader_variant_path("shaders/blinn_phong.vert",
                                    RHI_SHADER_VARIANT_GLSL,
                                    out, sizeof(out)) != NULL);
    ASSERT_TRUE(strcmp(out, "shaders/blinn_phong.vert") == 0);
    ASSERT_TRUE(shader_variant_path("shaders/blinn_phong.vert",
                                    RHI_SHADER_VARIANT_GLSL_VK, out, 8u) == NULL);
    ASSERT_TRUE(strcmp(shader_variant_suffix(RHI_SHADER_VARIANT_GLSL_VK), "_vk") == 0);
}

TEST(push_constants_follow_std430_offsets)
{
    static const char src[] =
        "#version 460\n"
        "layout(push_constant) uniform Push {\n"
        "    mat4 u_model;\n"     /* 0,   64 */
        "    mat4 u_view;\n"      /* 64,  64 */
        "    mat4 u_proj;\n"      /* 128, 64 */
        "    vec3 u_light_dir;\n" /* 192, 12 */
        "    float u_shadow_bias;\n" /* 204, 4（vec3 尾部打包，std430） */
        "} pc;\n";
    ShaderIOPushMember members[8];
    usize n = shader_reflect_push_constants(src, sizeof(src) - 1u, members, 8u);
    ASSERT_EQ(n, 5u);
    ASSERT_TRUE(strcmp(members[0].name, "u_model") == 0);
    ASSERT_EQ(members[0].offset, 0u);   ASSERT_EQ(members[0].size, 64u);
    ASSERT_EQ(members[1].offset, 64u);
    ASSERT_EQ(members[2].offset, 128u);
    ASSERT_TRUE(strcmp(members[3].name, "u_light_dir") == 0);
    ASSERT_EQ(members[3].offset, 192u);
    ASSERT_EQ(members[4].offset, 204u); ASSERT_EQ(members[4].size, 4u);
}

TEST(push_constants_absent_returns_zero_and_handles_null)
{
    ASSERT_EQ(shader_reflect_push_constants("#version 460\nvoid main(){}", 26u,
                                            NULL, 0u), 0u);
    ASSERT_EQ(shader_reflect_push_constants(NULL, 0u, NULL, 0u), 0u);
}

/* 计划 E Task 5 Step 5：std430 反射 vs rhi_vk.c 手写 push 表交叉对照 gate。
 * 期望值逐项转录自 rhi_vk.c `rhi_pipeline_get_uniform_location`（:7271-7652）
 * 的现状硬编码表 —— 反射结果必须等于当前生产行为；任何偏差都是反射器的
 * bug，不许改表、不许改 shader。
 *
 * 两类条目：
 *  - 直接条目（vk_name == member）：rhi_vk.c 名字即 shader 成员名，offset
 *    必须严格相等，size 按成员类型核对。
 *  - 打包别名（vk_name != member）：rhi_vk.c 名字是 vec4 打包成员的
 *    swizzle 宏（如 terrain 的 u_shadow_bias = u_light_dir_bias.w），断言
 *    表 offset 落在该成员 [offset, offset+size) 内 —— 生产路径正是往这
 *    个字节区间写 4 字节。
 * 反向覆盖：每个被 gate 文件的非 _pad 成员都必须被至少一条直接/别名条目
 * 命中，防止反射器对表未映射的成员算错而 gate 漏检。 */
typedef struct {
    const char *file;
    const char *vk_name; /* rhi_vk.c 表中的查询名 */
    const char *member;  /* shader 实际成员名（别名时指向 vec4 打包成员） */
    u32 offset;          /* rhi_vk.c 表偏移 */
    u32 size;            /* 期望字节数；0 = 不核对（别名条目） */
} VKPushRow;

TEST(vk_push_tables_match_reflection)
{
    static const VKPushRow rows[] = {
        /* blinn 家族（默认 forward 段：u_model@0 u_view@64 u_proj@128 +
         * else 段 u_light_dir@192 u_light_color@208 u_ambient@224）。
         * R600：u_camera_pos 不再是 push 成员 —— 它进了 ForwardTemporal
         * UBO（std140 {vec3 u_camera_pos; float pad; mat4 u_prev_vp;
         * mat4 u_prev_model}），push 尾部止于 240。这样 D3D12 sidecar 加
         * 一张 b1 CBV 表时，根签名 64-DWORD 预算只会把 push range 从
         * 252 压到 248，而 u_camera_pos 不再落在被丢弃的那一段。 */
        { "blinn_phong_vk.vert", "u_model", "u_model", 0u, 64u },
        { "blinn_phong_vk.vert", "u_view", "u_view", 64u, 64u },
        { "blinn_phong_vk.vert", "u_proj", "u_proj", 128u, 64u },
        { "blinn_phong_vk.vert", "u_light_dir", "u_light_dir", 192u, 12u },
        { "blinn_phong_vk.vert", "u_light_color", "u_light_color", 208u, 12u },
        { "blinn_phong_vk.vert", "u_ambient", "u_ambient", 224u, 12u },

        { "blinn_phong_vk.frag", "u_model", "u_model", 0u, 64u },
        { "blinn_phong_vk.frag", "u_view", "u_view", 64u, 64u },
        { "blinn_phong_vk.frag", "u_proj", "u_proj", 128u, 64u },
        { "blinn_phong_vk.frag", "u_light_dir", "u_light_dir", 192u, 12u },
        { "blinn_phong_vk.frag", "u_light_color", "u_light_color", 208u, 12u },
        { "blinn_phong_vk.frag", "u_ambient", "u_ambient", 224u, 12u },

        { "blinn_phong_arr_vk.vert", "u_model", "u_model", 0u, 64u },
        { "blinn_phong_arr_vk.vert", "u_view", "u_view", 64u, 64u },
        { "blinn_phong_arr_vk.vert", "u_proj", "u_proj", 128u, 64u },
        { "blinn_phong_arr_vk.vert", "u_light_dir", "u_light_dir", 192u, 12u },
        { "blinn_phong_arr_vk.vert", "u_light_color", "u_light_color", 208u, 12u },
        { "blinn_phong_arr_vk.vert", "u_ambient", "u_ambient", 224u, 12u },
        { "blinn_phong_arr_vk.frag", "u_model", "u_model", 0u, 64u },
        { "blinn_phong_arr_vk.frag", "u_view", "u_view", 64u, 64u },
        { "blinn_phong_arr_vk.frag", "u_proj", "u_proj", 128u, 64u },
        { "blinn_phong_arr_vk.frag", "u_light_dir", "u_light_dir", 192u, 12u },
        { "blinn_phong_arr_vk.frag", "u_light_color", "u_light_color", 208u, 12u },
        { "blinn_phong_arr_vk.frag", "u_ambient", "u_ambient", 224u, 12u },
        /* gbuffer 家族（共享段 + skinned_gbuffer 段，两段同值） */
        { "gbuffer_vk.vert", "u_model", "u_model", 0u, 64u },
        { "gbuffer_vk.vert", "u_view", "u_view", 64u, 64u },
        { "gbuffer_vk.vert", "u_proj", "u_proj", 128u, 64u },
        { "gbuffer_vk.vert", "u_prev_mvp", "u_prev_mvp", 192u, 64u },
        { "gbuffer_arr_vk.vert", "u_model", "u_model", 0u, 64u },
        { "gbuffer_arr_vk.vert", "u_view", "u_view", 64u, 64u },
        { "gbuffer_arr_vk.vert", "u_proj", "u_proj", 128u, 64u },
        { "gbuffer_arr_vk.vert", "u_prev_mvp", "u_prev_mvp", 192u, 64u },
        { "gbuffer_skinned_vk.vert", "u_model", "u_model", 0u, 64u },
        { "gbuffer_skinned_vk.vert", "u_view", "u_view", 64u, 64u },
        { "gbuffer_skinned_vk.vert", "u_proj", "u_proj", 128u, 64u },
        { "gbuffer_skinned_vk.vert", "u_prev_mvp", "u_prev_mvp", 192u, 64u },
        /* pbr_probe_vk.vert（默认段） */
        { "pbr_probe_vk.vert", "u_model", "u_model", 0u, 64u },
        { "pbr_probe_vk.vert", "u_view", "u_view", 64u, 64u },
        { "pbr_probe_vk.vert", "u_proj", "u_proj", 128u, 64u },
        /* instanced/skinned forward（non_clustered_tbo 段） */
        { "instanced_vk.vert", "u_view", "u_view", 0u, 64u },
        { "instanced_vk.vert", "u_proj", "u_proj", 64u, 64u },
        { "instanced_vk.vert", "u_light_dir", "u_light_dir", 128u, 12u },
        { "instanced_vk.vert", "u_light_color", "u_light_color", 144u, 12u },
        { "instanced_vk.vert", "u_ambient", "u_ambient", 160u, 12u },
        { "instanced_vk.vert", "u_camera_pos", "u_camera_pos", 176u, 12u },
        { "instanced_vk.frag", "u_view", "u_view", 0u, 64u },
        { "instanced_vk.frag", "u_proj", "u_proj", 64u, 64u },
        { "instanced_vk.frag", "u_light_dir", "u_light_dir", 128u, 12u },
        { "instanced_vk.frag", "u_light_color", "u_light_color", 144u, 12u },
        { "instanced_vk.frag", "u_ambient", "u_ambient", 160u, 12u },
        { "instanced_vk.frag", "u_camera_pos", "u_camera_pos", 176u, 12u },
        { "skinned_vk.vert", "u_view", "u_view", 0u, 64u },
        { "skinned_vk.vert", "u_proj", "u_proj", 64u, 64u },
        { "skinned_vk.vert", "u_light_dir", "u_light_dir", 128u, 12u },
        { "skinned_vk.vert", "u_light_color", "u_light_color", 144u, 12u },
        { "skinned_vk.vert", "u_ambient", "u_ambient", 160u, 12u },
        { "skinned_vk.vert", "u_camera_pos", "u_camera_pos", 176u, 12u },
        { "skinned_vk.frag", "u_view", "u_view", 0u, 64u },
        { "skinned_vk.frag", "u_proj", "u_proj", 64u, 64u },
        { "skinned_vk.frag", "u_light_dir", "u_light_dir", 128u, 12u },
        { "skinned_vk.frag", "u_light_color", "u_light_color", 144u, 12u },
        { "skinned_vk.frag", "u_ambient", "u_ambient", 160u, 12u },
        { "skinned_vk.frag", "u_camera_pos", "u_camera_pos", 176u, 12u },
        /* clustered 家族 vert（clustered 段只映射 u_model@0 + 共享 u_view@64） */
        { "pbr_clustered_vk.vert", "u_model", "u_model", 0u, 64u },
        { "pbr_clustered_vk.vert", "u_view", "u_view", 64u, 64u },
        { "pbr_clustered_inst_vk.vert", "u_model", "u_model", 0u, 64u },
        { "pbr_clustered_inst_vk.vert", "u_view", "u_view", 64u, 64u },
        { "pbr_clustered_skin_vk.vert", "u_model", "u_model", 0u, 64u },
        { "pbr_clustered_skin_vk.vert", "u_view", "u_view", 64u, 64u },
        { "pbr_clustered_arr_vk.vert", "u_model", "u_model", 0u, 64u },
        { "pbr_clustered_arr_vk.vert", "u_view", "u_view", 64u, 64u },
        /* pbr_clustered_vk.frag（共享段 + clustered 段） */
        { "pbr_clustered_vk.frag", "u_model", "u_model", 0u, 64u },
        { "pbr_clustered_vk.frag", "u_view", "u_view", 64u, 64u },
        { "pbr_clustered_vk.frag", "u_camera_pos", "u_camera_pos", 128u, 12u },
        { "pbr_clustered_vk.frag", "u_fog_near", "u_fog_near", 140u, 4u },
        { "pbr_clustered_vk.frag", "u_ambient", "u_ambient", 144u, 12u },
        { "pbr_clustered_vk.frag", "u_fog_far", "u_fog_far", 156u, 4u },
        { "pbr_clustered_vk.frag", "u_screen_w", "u_screen_w", 160u, 4u },
        { "pbr_clustered_vk.frag", "u_screen_h", "u_screen_h", 164u, 4u },
        { "pbr_clustered_vk.frag", "u_near", "u_near", 168u, 4u },
        { "pbr_clustered_vk.frag", "u_far", "u_far", 172u, 4u },
        { "pbr_clustered_vk.frag", "u_point_count", "u_point_count", 176u, 4u },
        { "pbr_clustered_vk.frag", "u_dir_count", "u_dir_count", 180u, 4u },
        { "pbr_clustered_vk.frag", "u_shadow_bias", "u_shadow_bias", 184u, 4u },
        { "pbr_clustered_vk.frag", "u_fog_color", "u_fog_color", 192u, 12u },
        { "pbr_clustered_vk.frag", "u_underwater", "u_underwater", 204u, 4u },
        { "pbr_clustered_vk.frag", "u_point_shadow_far_planes",
          "u_point_shadow_far_planes", 208u, 16u },
        { "pbr_clustered_vk.frag", "u_pom_enabled", "u_pom_enabled", 224u, 4u },
        { "pbr_clustered_vk.frag", "u_occlusion_strength",
          "u_occlusion_strength", 228u, 4u },
        { "pbr_clustered_vk.frag", "u_mr_factor", "u_mr_factor", 232u, 8u },
        { "pbr_clustered_vk.frag", "u_emissive_factor",
          "u_emissive_factor", 240u, 12u },
        /* terrain（terrain 段；vec4 打包成员 + swizzle 宏别名） */
        { "terrain_vk.vert", "u_view", "u_view", 0u, 64u },
        { "terrain_vk.vert", "u_proj", "u_proj", 64u, 64u },
        { "terrain_vk.vert", "u_light_vp", "u_light_vp", 128u, 64u },
        { "terrain_vk.vert", "u_light_dir", "u_light_dir_bias", 192u, 0u },
        { "terrain_vk.vert", "u_shadow_bias", "u_light_dir_bias", 204u, 0u },
        { "terrain_vk.vert", "u_light_color", "u_light_color_watery", 208u, 0u },
        { "terrain_vk.vert", "u_water_y", "u_light_color_watery", 220u, 0u },
        { "terrain_vk.vert", "u_ambient", "u_ambient_time", 224u, 0u },
        { "terrain_vk.vert", "u_time", "u_ambient_time", 236u, 0u },
        { "terrain_vk.vert", "u_camera_pos", "u_camera_pos", 240u, 16u },
        { "terrain_vk.frag", "u_view", "u_view", 0u, 64u },
        { "terrain_vk.frag", "u_proj", "u_proj", 64u, 64u },
        { "terrain_vk.frag", "u_light_vp", "u_light_vp", 128u, 64u },
        { "terrain_vk.frag", "u_light_dir", "u_light_dir_bias", 192u, 0u },
        { "terrain_vk.frag", "u_shadow_bias", "u_light_dir_bias", 204u, 0u },
        { "terrain_vk.frag", "u_light_color", "u_light_color_watery", 208u, 0u },
        { "terrain_vk.frag", "u_water_y", "u_light_color_watery", 220u, 0u },
        { "terrain_vk.frag", "u_ambient", "u_ambient_time", 224u, 0u },
        { "terrain_vk.frag", "u_time", "u_ambient_time", 236u, 0u },
        { "terrain_vk.frag", "u_camera_pos", "u_cam_pos", 240u, 0u },
        /* water（water 段；同为 vec4 打包别名） */
        { "water_vk.vert", "u_view", "u_view", 0u, 64u },
        { "water_vk.vert", "u_proj", "u_proj", 64u, 64u },
        { "water_vk.vert", "u_light_vp", "u_light_vp", 128u, 64u },
        { "water_vk.vert", "u_camera_pos", "u_camera_time", 192u, 0u },
        { "water_vk.vert", "u_time", "u_camera_time", 204u, 0u },
        { "water_vk.vert", "u_water_color", "u_color_bias", 208u, 0u },
        { "water_vk.vert", "u_shadow_bias", "u_color_bias", 220u, 0u },
        { "water_vk.vert", "u_water_y", "u_watery", 224u, 0u },
        { "water_vk.frag", "u_view", "u_view", 0u, 64u },
        { "water_vk.frag", "u_proj", "u_proj", 64u, 64u },
        { "water_vk.frag", "u_light_vp", "u_light_vp", 128u, 64u },
        { "water_vk.frag", "u_camera_pos", "u_camera_time", 192u, 0u },
        { "water_vk.frag", "u_time", "u_camera_time", 204u, 0u },
        { "water_vk.frag", "u_water_color", "u_color_bias", 208u, 0u },
        { "water_vk.frag", "u_shadow_bias", "u_color_bias", 220u, 0u },
        { "water_vk.frag", "u_water_y", "u_watery", 224u, 0u },
        /* shadow depth（is_shadow_depth 段；point light 变体） */
        { "point_shadow_depth_vk.vert", "u_model", "u_model", 0u, 64u },
        { "point_shadow_depth_vk.vert", "u_mvp", "u_mvp", 64u, 64u },
        { "point_shadow_depth_vk.vert", "u_light_pos", "u_light_pos", 128u, 16u },
        { "point_shadow_depth_vk.vert", "u_far_plane", "u_far_plane", 144u, 16u },
        { "point_shadow_depth_vk.frag", "u_model", "u_model", 0u, 64u },
        { "point_shadow_depth_vk.frag", "u_mvp", "u_mvp", 64u, 64u },
        { "point_shadow_depth_vk.frag", "u_light_pos", "u_light_pos", 128u, 16u },
        { "point_shadow_depth_vk.frag", "u_far_plane", "u_far_plane", 144u, 16u },
        /* combined TAA+FXAA（combined_aa 段） */
        { "combined_taa_fxaa_vk.frag", "u_taa_curr_vp", "u_taa_curr_vp", 0u, 64u },
        { "combined_taa_fxaa_vk.frag", "u_taa_prev_vp", "u_taa_prev_vp", 64u, 64u },
        { "combined_taa_fxaa_vk.frag", "u_taa_inv_proj", "u_taa_inv_proj", 128u, 64u },
        { "combined_taa_fxaa_vk.frag", "u_screen_w", "u_screen_w", 192u, 4u },
        { "combined_taa_fxaa_vk.frag", "u_screen_h", "u_screen_h", 196u, 4u },
        { "combined_taa_fxaa_vk.frag", "u_taa_blend", "u_taa_blend", 200u, 4u },
        { "combined_taa_fxaa_vk.frag", "u_taa_first_frame",
          "u_taa_first_frame", 204u, 4u },
        { "combined_taa_fxaa_vk.frag", "u_fxaa_threshold",
          "u_fxaa_threshold", 208u, 4u },
        { "combined_taa_fxaa_vk.frag", "u_taa_use_velocity",
          "u_taa_use_velocity", 212u, 4u },
        /* combined tonemap+colorgrade+cinematic（combined_color 段） */
        { "combined_color_vk.frag", "u_tm_exposure", "u_tm_exposure", 0u, 4u },
        { "combined_color_vk.frag", "u_tm_gamma", "u_tm_gamma", 4u, 4u },
        { "combined_color_vk.frag", "u_tm_mode", "u_tm_mode", 8u, 4u },
        { "combined_color_vk.frag", "u_cg_saturation", "u_cg_saturation", 12u, 4u },
        { "combined_color_vk.frag", "u_cg_contrast", "u_cg_contrast", 16u, 4u },
        { "combined_color_vk.frag", "u_cg_brightness", "u_cg_brightness", 20u, 4u },
        { "combined_color_vk.frag", "u_cg_temperature", "u_cg_temperature", 24u, 4u },
        { "combined_color_vk.frag", "u_cg_tint", "u_cg_tint", 28u, 4u },
        { "combined_color_vk.frag", "u_cine_aberration", "u_cine_aberration", 32u, 4u },
        { "combined_color_vk.frag", "u_cine_vignette", "u_cine_vignette", 36u, 4u },
        { "combined_color_vk.frag", "u_cine_grain", "u_cine_grain", 40u, 4u },
        { "combined_color_vk.frag", "u_cine_time", "u_cine_time", 44u, 4u },
        { "combined_color_vk.frag", "u_screen_w", "u_screen_w", 48u, 4u },
        { "combined_color_vk.frag", "u_screen_h", "u_screen_h", 52u, 4u },
        /* deferred lighting（no_vertex_input+texel 段；vec4 打包别名） */
        { "deferred_light_vk.frag", "u_inv_vp", "u_inv_vp", 0u, 64u },
        { "deferred_light_vk.frag", "u_view", "u_view", 64u, 64u },
        { "deferred_light_vk.frag", "u_camera_pos", "u_camera_pos", 128u, 16u },
        { "deferred_light_vk.frag", "u_screen_w", "u_screen_params", 144u, 0u },
        { "deferred_light_vk.frag", "u_screen_h", "u_screen_params", 148u, 0u },
        { "deferred_light_vk.frag", "u_near", "u_clip_params", 160u, 0u },
        { "deferred_light_vk.frag", "u_far", "u_clip_params", 164u, 0u },
        { "deferred_light_vk.frag", "u_shadow_bias", "u_clip_params", 168u, 0u },
        { "deferred_light_vk.frag", "u_point_count", "u_point_count", 176u, 4u },
        { "deferred_light_vk.frag", "u_dir_count", "u_dir_count", 180u, 4u },
        { "deferred_light_vk.frag", "u_point_shadow_far_planes",
          "u_point_shadow_far_planes", 192u, 16u },
        /* skybox（no_vertex_input 非 texel 段 + 末尾共享 u_inv_proj@0） */
        { "skybox_vk.vert", "u_inv_proj", "u_inv_proj", 0u, 64u },
        { "skybox_vk.vert", "u_view", "u_view", 64u, 64u },
        { "skybox_vk.frag", "u_inv_proj", "u_inv_proj", 0u, 64u },
        { "skybox_vk.frag", "u_view", "u_view", 64u, 64u },
        { "skybox_vk.frag", "u_sun_dir", "u_sun_dir", 128u, 12u },
        { "skybox_vk.frag", "u_sun_color", "u_sun_color", 144u, 12u },
        /* camera velocity（no_vertex_input：u_prev_vp@128 per R203-A；
         * 成员 0 是 u_inv_proj —— 表的 u_inv_vp@0 与 u_inv_proj@0 同指它） */
        { "camera_velocity_vk.frag", "u_inv_vp", "u_inv_proj", 0u, 0u },
        { "camera_velocity_vk.frag", "u_inv_proj", "u_inv_proj", 0u, 64u },
        { "camera_velocity_vk.frag", "u_curr_vp", "u_curr_vp", 64u, 64u },
        { "camera_velocity_vk.frag", "u_prev_vp", "u_prev_vp", 128u, 64u },
        /* 共享段的独立 post pass（每文件一段） */
        { "volumetric_vk.frag", "u_vol_inv_proj", "u_vol_inv_proj", 0u, 64u },
        { "volumetric_vk.frag", "u_vol_view", "u_vol_view", 64u, 64u },
        { "volumetric_vk.frag", "u_vol_ldx", "u_vol_ldx", 128u, 4u },
        { "volumetric_vk.frag", "u_vol_ldy", "u_vol_ldy", 132u, 4u },
        { "volumetric_vk.frag", "u_vol_ldz", "u_vol_ldz", 136u, 4u },
        { "volumetric_vk.frag", "u_vol_lcx", "u_vol_lcx", 140u, 4u },
        { "volumetric_vk.frag", "u_vol_lcy", "u_vol_lcy", 144u, 4u },
        { "volumetric_vk.frag", "u_vol_lcz", "u_vol_lcz", 148u, 4u },
        { "volumetric_vk.frag", "u_vol_density", "u_vol_density", 152u, 4u },
        { "volumetric_vk.frag", "u_vol_fog_r", "u_vol_fog_r", 156u, 4u },
        { "volumetric_vk.frag", "u_vol_fog_g", "u_vol_fog_g", 160u, 4u },
        { "volumetric_vk.frag", "u_vol_fog_b", "u_vol_fog_b", 164u, 4u },
        { "volumetric_vk.frag", "u_vol_sw", "u_vol_sw", 168u, 4u },
        { "volumetric_vk.frag", "u_vol_sh", "u_vol_sh", 172u, 4u },
        { "volumetric_vk.frag", "u_vol_inv_view", "u_vol_inv_view", 176u, 64u },
        { "lens_flare_vk.frag", "u_lf_light_x", "u_lf_light_x", 0u, 4u },
        { "lens_flare_vk.frag", "u_lf_light_y", "u_lf_light_y", 4u, 4u },
        { "lens_flare_vk.frag", "u_lf_intensity", "u_lf_intensity", 8u, 4u },
        { "lens_flare_vk.frag", "u_lf_sw", "u_lf_sw", 12u, 4u },
        { "lens_flare_vk.frag", "u_lf_sh", "u_lf_sh", 16u, 4u },
        { "lens_flare_vk.frag", "u_lf_lc_r", "u_lf_lc_r", 20u, 4u },
        { "lens_flare_vk.frag", "u_lf_lc_g", "u_lf_lc_g", 24u, 4u },
        { "lens_flare_vk.frag", "u_lf_lc_b", "u_lf_lc_b", 28u, 4u },
        { "ssgi_vk.frag", "u_ssgi_inv_proj", "u_ssgi_inv_proj", 0u, 64u },
        { "ssgi_vk.frag", "u_ssgi_proj", "u_ssgi_proj", 64u, 64u },
        { "ssgi_vk.frag", "u_ssgi_radius", "u_ssgi_radius", 128u, 4u },
        { "ssgi_vk.frag", "u_ssgi_intensity", "u_ssgi_intensity", 132u, 4u },
        { "ssgi_vk.frag", "u_ssgi_sw", "u_ssgi_sw", 136u, 4u },
        { "ssgi_vk.frag", "u_ssgi_sh", "u_ssgi_sh", 140u, 4u },
        { "fxaa_vk.frag", "u_fxaa_sw", "u_fxaa_sw", 0u, 4u },
        { "fxaa_vk.frag", "u_fxaa_sh", "u_fxaa_sh", 4u, 4u },
        { "fxaa_vk.frag", "u_fxaa_threshold", "u_fxaa_threshold", 8u, 4u },
        { "tonemap_vk.frag", "u_tm_exposure", "u_tm_exposure", 0u, 4u },
        { "tonemap_vk.frag", "u_tm_gamma", "u_tm_gamma", 4u, 4u },
        { "tonemap_vk.frag", "u_tm_screen_w", "u_tm_screen_w", 8u, 4u },
        { "tonemap_vk.frag", "u_tm_screen_h", "u_tm_screen_h", 12u, 4u },
        { "tonemap_vk.frag", "u_tm_mode", "u_tm_mode", 16u, 4u },
        { "cinematic_vk.frag", "u_cine_aberration", "u_cine_aberration", 0u, 4u },
        { "cinematic_vk.frag", "u_cine_vignette", "u_cine_vignette", 4u, 4u },
        { "cinematic_vk.frag", "u_cine_grain", "u_cine_grain", 8u, 4u },
        { "cinematic_vk.frag", "u_cine_time", "u_cine_time", 12u, 4u },
        { "cinematic_vk.frag", "u_cine_sw", "u_cine_sw", 16u, 4u },
        { "cinematic_vk.frag", "u_cine_sh", "u_cine_sh", 20u, 4u },
        { "color_grade_vk.frag", "u_cg_saturation", "u_cg_saturation", 0u, 4u },
        { "color_grade_vk.frag", "u_cg_contrast", "u_cg_contrast", 4u, 4u },
        { "color_grade_vk.frag", "u_cg_brightness", "u_cg_brightness", 8u, 4u },
        { "color_grade_vk.frag", "u_cg_temperature", "u_cg_temperature", 12u, 4u },
        { "color_grade_vk.frag", "u_cg_tint", "u_cg_tint", 16u, 4u },
        { "dof_vk.frag", "u_dof_focus", "u_dof_focus", 0u, 4u },
        { "dof_vk.frag", "u_dof_range", "u_dof_range", 4u, 4u },
        { "dof_vk.frag", "u_dof_near", "u_dof_near", 8u, 4u },
        { "dof_vk.frag", "u_dof_far", "u_dof_far", 12u, 4u },
        { "dof_vk.frag", "u_dof_sw", "u_dof_sw", 16u, 4u },
        { "dof_vk.frag", "u_dof_sh", "u_dof_sh", 20u, 4u },
        { "ssr_vk.frag", "u_ssr_proj", "u_ssr_proj", 0u, 64u },
        { "ssr_vk.frag", "u_ssr_inv_proj", "u_ssr_inv_proj", 64u, 64u },
        { "ssr_vk.frag", "u_ssr_view", "u_ssr_view", 128u, 64u },
        { "ssr_vk.frag", "u_ssr_sw", "u_ssr_sw", 192u, 4u },
        { "ssr_vk.frag", "u_ssr_sh", "u_ssr_sh", 196u, 4u },
        { "ssr_vk.frag", "u_ssr_max_steps", "u_ssr_max_steps", 200u, 4u },
        { "ssr_vk.frag", "u_ssr_stride", "u_ssr_stride", 204u, 4u },
        { "ssr_vk.frag", "u_ssr_thickness", "u_ssr_thickness", 208u, 4u },
        { "taa_vk.frag", "u_taa_curr_vp", "u_taa_curr_vp", 0u, 64u },
        { "taa_vk.frag", "u_taa_prev_vp", "u_taa_prev_vp", 64u, 64u },
        { "taa_vk.frag", "u_taa_inv_proj", "u_taa_inv_proj", 128u, 64u },
        { "taa_vk.frag", "u_taa_sw", "u_taa_sw", 192u, 4u },
        { "taa_vk.frag", "u_taa_sh", "u_taa_sh", 196u, 4u },
        { "taa_vk.frag", "u_taa_blend", "u_taa_blend", 200u, 4u },
        { "taa_vk.frag", "u_taa_first_frame", "u_taa_first_frame", 204u, 4u },
        { "taa_vk.frag", "u_taa_use_velocity", "u_taa_use_velocity", 208u, 4u },
        { "ssao_vk.frag", "u_ssao_proj", "u_ssao_proj", 0u, 64u },
        { "ssao_vk.frag", "u_ssao_inv_proj", "u_ssao_inv_proj", 64u, 64u },
        { "ssao_vk.frag", "u_ssao_sw", "u_ssao_sw", 128u, 4u },
        { "ssao_vk.frag", "u_ssao_sh", "u_ssao_sh", 132u, 4u },
        { "ssao_vk.frag", "u_ssao_radius", "u_ssao_radius", 136u, 4u },
        { "ssao_vk.frag", "u_ssao_bias", "u_ssao_bias", 140u, 4u },
        { "debug_viz_vk.frag", "u_dv_mode", "u_dv_mode", 0u, 4u },
        { "debug_viz_vk.frag", "u_dv_near", "u_dv_near", 4u, 4u },
        { "debug_viz_vk.frag", "u_dv_far", "u_dv_far", 8u, 4u },
        { "debug_viz_vk.frag", "u_dv_split0", "u_dv_split0", 12u, 4u },
        { "debug_viz_vk.frag", "u_dv_split1", "u_dv_split1", 16u, 4u },
        { "debug_viz_vk.frag", "u_dv_split2", "u_dv_split2", 20u, 4u },
        { "debug_viz_vk.frag", "u_dv_split3", "u_dv_split3", 24u, 4u },
        { "lens_effects_vk.frag", "u_ca_strength", "u_ca_strength", 0u, 4u },
        { "lens_effects_vk.frag", "u_vignette_strength",
          "u_vignette_strength", 4u, 4u },
        { "lens_effects_vk.frag", "u_vignette_softness",
          "u_vignette_softness", 8u, 4u },
        { "lens_effects_vk.frag", "u_grain_strength",
          "u_grain_strength", 12u, 4u },
        { "sharpen_vk.frag", "u_sharp_strength", "u_sharp_strength", 0u, 4u },
        { "sharpen_vk.frag", "u_sharp_sw", "u_sharp_sw", 4u, 4u },
        { "sharpen_vk.frag", "u_sharp_sh", "u_sharp_sh", 8u, 4u },
        { "upscale_vk.frag", "u_ups_rw", "u_ups_rw", 0u, 4u },
        { "upscale_vk.frag", "u_ups_rh", "u_ups_rh", 4u, 4u },
        { "upscale_vk.frag", "u_ups_dw", "u_ups_dw", 8u, 4u },
        { "upscale_vk.frag", "u_ups_dh", "u_ups_dh", 12u, 4u },
        { "upscale_vk.frag", "u_ups_sharp", "u_ups_sharp", 16u, 4u },
        { "upscale_vk.frag", "u_ups_copy_only", "u_ups_copy_only", 20u, 4u },
        { "upscale_vk.frag", "u_ups_first_frame", "u_ups_first_frame", 24u, 4u },
        { "upscale_vk.frag", "u_ups_inv_proj", "u_ups_inv_proj", 32u, 64u },
        { "upscale_vk.frag", "u_ups_prev_vp", "u_ups_prev_vp", 96u, 64u },
        { "luminance_vk.frag", "u_lum_w", "u_lum_w", 0u, 4u },
        { "luminance_vk.frag", "u_lum_h", "u_lum_h", 4u, 4u },
        { "luminance_vk.frag", "u_lum_speed", "u_lum_speed", 8u, 4u },
        { "luminance_vk.frag", "u_lum_dt", "u_lum_dt", 12u, 4u },
        { "god_rays_vk.frag", "u_gr_sun_x", "u_gr_sun_x", 0u, 4u },
        { "god_rays_vk.frag", "u_gr_sun_y", "u_gr_sun_y", 4u, 4u },
        { "god_rays_vk.frag", "u_gr_intensity", "u_gr_intensity", 8u, 4u },
        { "god_rays_vk.frag", "u_gr_decay", "u_gr_decay", 12u, 4u },
        { "god_rays_vk.frag", "u_gr_sw", "u_gr_sw", 16u, 4u },
        { "god_rays_vk.frag", "u_gr_sh", "u_gr_sh", 20u, 4u },
        /* 数组成员（stride 4 的 float[16] — 显式 offset 转录） */
        { "motion_blur_vk.frag", "u_mb_strength", "u_mb_strength", 0u, 4u },
        { "motion_blur_vk.frag", "u_mb_sw", "u_mb_sw", 4u, 4u },
        { "motion_blur_vk.frag", "u_mb_sh", "u_mb_sh", 8u, 4u },
        { "motion_blur_vk.frag", "u_mb_inv_proj", "u_mb_inv_proj", 12u, 64u },
        { "motion_blur_vk.frag", "u_mb_prev_vp", "u_mb_prev_vp", 76u, 64u },
        { "motion_blur_vk.frag", "u_mb_use_velocity", "u_mb_use_velocity", 140u, 4u },
        { "contact_shadow_vk.frag", "u_cs_light_x", "u_cs_light_x", 0u, 4u },
        { "contact_shadow_vk.frag", "u_cs_light_y", "u_cs_light_y", 4u, 4u },
        { "contact_shadow_vk.frag", "u_cs_light_z", "u_cs_light_z", 8u, 4u },
        { "contact_shadow_vk.frag", "u_cs_inv_proj", "u_cs_inv_proj", 12u, 64u },
        { "contact_shadow_vk.frag", "u_cs_sw", "u_cs_sw", 76u, 4u },
        { "contact_shadow_vk.frag", "u_cs_sh", "u_cs_sh", 80u, 4u },
        { "bloom_extract_vk.frag", "u_threshold", "u_threshold", 0u, 4u },
        { "bloom_blur_vk.frag", "u_direction", "u_direction", 0u, 8u },
        { "bloom_composite_vk.frag", "u_bloom_strength", "u_bloom_strength", 0u, 4u },
        { "ssgi_blur_vk.frag", "u_direction", "u_direction", 0u, 8u },
        { "sss_vk.frag", "u_sss_strength", "u_sss_strength", 0u, 4u },
        { "sss_vk.frag", "u_sss_sw", "u_sss_sw", 4u, 4u },
        { "sss_vk.frag", "u_sss_sh", "u_sss_sh", 8u, 4u },
        { "sss_vk.frag", "u_sss_max_dist", "u_sss_max_dist", 12u, 4u },
        { "sss_vertical_vk.frag", "u_sssv_strength", "u_sssv_strength", 0u, 4u },
        { "sss_vertical_vk.frag", "u_sssv_sw", "u_sssv_sw", 4u, 4u },
        { "sss_vertical_vk.frag", "u_sssv_sh", "u_sssv_sh", 8u, 4u },
        { "sss_vertical_vk.frag", "u_sssv_max_dist", "u_sssv_max_dist", 12u, 4u },
        /* particle.vert（particles render 的 uses_storage graphics 管线；
         * 块实例别名 push.view/push.proj，legacy uses_storage 段 0/64。
         * C-2A review 修复 pin：alias 的 delta 是「成员内」偏移 —— 曾把
         * push.proj 的 legacy 绝对偏移 64 误写进 delta（64+64=128 腐蚀
         * VK 粒子投影写入），下方 alias 算术 pin 钉死 member+delta ==
         * legacy 值。 */
        { "particle.vert", "push.view", "view", 0u, 0u },
        { "particle.vert", "push.proj", "proj", 64u, 0u },
    };
    static char src[32768];
    ShaderIOPushMember members[32];
    char current[64] = "";
    usize n = 0u;
    usize row_count = sizeof(rows) / sizeof(rows[0]);

    /* 正向：每条表项必须命中反射结果（直接条目 offset 严格相等；别名
     * 条目 offset 落在成员范围内）。 */
    for (usize i = 0u; i < row_count; i++) {
        const VKPushRow *r = &rows[i];
        const ShaderIOPushMember *m;
        if (strcmp(current, r->file) != 0) {
            ASSERT_TRUE(read_shader_source(r->file, src, sizeof(src)));
            n = shader_reflect_push_constants(src, strlen(src), members, 32u);
            snprintf(current, sizeof(current), "%s", r->file);
            ASSERT_TRUE(n > 0u);
        }
        m = push_member_by_name(members, n, r->member);
        if (m == NULL) {
            printf("  FAIL: %s: member '%s' (vk name '%s') not reflected\n",
                   r->file, r->member, r->vk_name);
        }
        ASSERT_TRUE(m != NULL);
        if (strcmp(r->vk_name, r->member) == 0) {
            if (m->offset != r->offset) {
                printf("  FAIL: %s: %s reflected @%u, rhi_vk.c table @%u\n",
                       r->file, r->vk_name, m->offset, r->offset);
            }
            ASSERT_EQ(m->offset, r->offset);
            if (r->size != 0u && m->size != r->size) {
                printf("  FAIL: %s: %s reflected size %u, expected %u\n",
                       r->file, r->vk_name, m->size, r->size);
            }
            ASSERT_TRUE(r->size == 0u || m->size == r->size);
        } else {
            if (r->offset < m->offset || r->offset >= m->offset + m->size) {
                printf("  FAIL: %s: alias '%s'@%u outside member '%s'"
                       " [%u, %u)\n", r->file, r->vk_name, r->offset,
                       r->member, m->offset, m->offset + m->size);
            }
            ASSERT_TRUE(r->offset >= m->offset);
            ASSERT_TRUE(r->offset < m->offset + m->size);
        }
    }

    /* 反向：每个 gate 文件的非 _pad 成员必须被至少一条表项覆盖。 */
    current[0] = '\0';
    for (usize i = 0u; i < row_count; i++) {
        if (strcmp(current, rows[i].file) == 0) continue;
        snprintf(current, sizeof(current), "%s", rows[i].file);
        ASSERT_TRUE(read_shader_source(current, src, sizeof(src)));
        n = shader_reflect_push_constants(src, strlen(src), members, 32u);
        ASSERT_TRUE(n > 0u);
        for (usize j = 0u; j < n; j++) {
            bool covered = false;
            if (strncmp(members[j].name, "_pad", 4u) == 0) continue;
            for (usize k = 0u; k < row_count && !covered; k++) {
                if (strcmp(rows[k].file, current) != 0) continue;
                if (strcmp(rows[k].member, members[j].name) != 0) continue;
                covered = rows[k].offset >= members[j].offset &&
                          rows[k].offset < members[j].offset + members[j].size;
            }
            if (!covered) {
                printf("  FAIL: %s: member '%s'@%u not covered by any"
                       " rhi_vk.c table row\n",
                       current, members[j].name, members[j].offset);
            }
            ASSERT_TRUE(covered);
        }
    }

    /* C-2A review pin：块实例别名的「运行时算术」。上面的行只证明 legacy
     * 值落在反射成员范围内；bindings/legacy 实际输出的是 rhi_vk.c
     * vk_push_alias_rows 的 成员反射偏移 + delta。这里静态读出该表每个
     * particle 家族行的 delta 字面量，断言 反射成员偏移 + delta == legacy
     * 值 —— 最初的 push.proj delta 64u（64+64=128≠64）正是缺这一层 pin
     * 才漏过所有 gate。行内解析容忍表对齐空格（成员名回读校验防误配）。 */
    {
        static const struct {
            const char *alias;
            const char *file;
            const char *member;
            u32 legacy;
        } pin[] = {
            { "push.dt",   "particle_update.comp", "dt",   0u },
            { "push.view", "particle.vert",        "view", 0u },
            { "push.proj", "particle.vert",        "proj", 64u },
        };
        static char vk_src[524288];
        ASSERT_TRUE(read_engine_source("rhi/rhi_vk.c", vk_src, sizeof(vk_src)));
        for (usize i = 0u; i < sizeof(pin) / sizeof(pin[0]); i++) {
            ASSERT_TRUE(read_shader_source(pin[i].file, src, sizeof(src)));
            n = shader_reflect_push_constants(src, strlen(src), members, 32u);
            const ShaderIOPushMember *m = push_member_by_name(members, n,
                                                               pin[i].member);
            ASSERT_NOT_NULL(m);
            char needle[96];
            snprintf(needle, sizeof(needle), "{ \"%s\",", pin[i].alias);
            const char *row = strstr(vk_src, needle);
            char row_member[64] = {0};
            unsigned delta = 0u;
            if (row == NULL ||
                sscanf(row + strlen(needle), " \"%63[^\"]\" , %u",
                       row_member, &delta) != 2 ||
                strcmp(row_member, pin[i].member) != 0) {
                printf("  FAIL: alias row '%s' -> '%s' not found/parseable in"
                       " rhi_vk.c vk_push_alias_rows\n", pin[i].alias,
                       pin[i].member);
            }
            ASSERT_NOT_NULL(row);
            ASSERT_TRUE(strcmp(row_member, pin[i].member) == 0);
            if (m->offset + (u32)delta != pin[i].legacy) {
                printf("  FAIL: alias %s: member@%u + delta %u = %u,"
                       " legacy %u\n", pin[i].alias, m->offset, delta,
                       m->offset + (u32)delta, pin[i].legacy);
            }
            ASSERT_EQ(m->offset + (u32)delta, pin[i].legacy);
        }
    }

    /* 计划 E Task 6 Step 1：RHIPipelineDesc 布局布尔 ↔ 契约 shader ↔
     * 反射布局三方闭环。5c-2a 删除 rhi_vk.c 手写布局表后，四个 *_layout
     * 字段在 rhi_vk.c 只被复制进 pipeline desc（write-only——原读者即被删
     * 的表）；本段是它们成文的真实消费证明：每个字段命名一个 shader
     * 家族的 push 布局契约，断言 (1) renderer 源码经 shader_variant_path
     * 加载该家族基名并设置字段（字段→shader），(2) 该家族每个 _vk 文件
     * 的非 pad 反射成员都被本 gate 的期望 offset 表行精确覆盖——直接条目
     * offset 严格相等（shader→反射布局）。 */
    {
        static const struct {
            const char *field;    /* RHIPipelineDesc 字段名 */
            const char *producer; /* 设置字段的 renderer 源（相对 engine/src） */
            const char *wiring;   /* 源码字段赋值片段 */
            const char *base;     /* shader_variant_path 基名 */
            const char *files[2]; /* 布局契约 _vk 文件（NULL 结尾） */
        } layouts[] = {
            { "terrain_layout", "renderer/terrain.c",
              ".terrain_layout", "shaders/terrain.vert",
              { "terrain_vk.vert", "terrain_vk.frag" } },
            { "water_layout", "renderer/water.c",
              ".water_layout", "shaders/water.vert",
              { "water_vk.vert", "water_vk.frag" } },
            { "combined_aa_layout", "renderer/combined_post_process.c",
              ".combined_aa_layout", "shaders/combined_taa_fxaa.frag",
              { "combined_taa_fxaa_vk.frag", NULL } },
            { "combined_color_layout", "renderer/combined_post_process.c",
              ".combined_color_layout", "shaders/combined_color.frag",
              { "combined_color_vk.frag", NULL } },
        };
        static char producer_src[65536];
        char base_needle[96];
        for (usize li = 0u; li < sizeof(layouts) / sizeof(layouts[0]); li++) {
            usize file_rows = 0u;
            ASSERT_TRUE(read_engine_source(layouts[li].producer, producer_src,
                                           sizeof(producer_src)));
            if (strstr(producer_src, layouts[li].wiring) == NULL) {
                printf("  FAIL: %s does not set %s\n",
                       layouts[li].producer, layouts[li].field);
            }
            ASSERT_NOT_NULL(strstr(producer_src, layouts[li].wiring));
            snprintf(base_needle, sizeof(base_needle),
                     "shader_variant_path(\"%s\"", layouts[li].base);
            if (strstr(producer_src, base_needle) == NULL) {
                printf("  FAIL: %s does not load %s via shader_variant_path\n",
                       layouts[li].producer, layouts[li].base);
            }
            ASSERT_NOT_NULL(strstr(producer_src, base_needle));
            for (usize fi = 0u; fi < 2u && layouts[li].files[fi] != NULL; fi++) {
                usize non_pad = 0u;
                ASSERT_TRUE(read_shader_source(layouts[li].files[fi], src,
                                               sizeof(src)));
                n = shader_reflect_push_constants(src, strlen(src), members, 32u);
                ASSERT_TRUE(n > 0u);
                for (usize j = 0u; j < n; j++) {
                    bool covered = false;
                    if (strncmp(members[j].name, "_pad", 4u) == 0) continue;
                    non_pad++;
                    for (usize k = 0u; k < row_count && !covered; k++) {
                        if (strcmp(rows[k].file, layouts[li].files[fi]) != 0) continue;
                        if (strcmp(rows[k].member, members[j].name) != 0) continue;
                        covered = rows[k].offset >= members[j].offset &&
                                  rows[k].offset < members[j].offset + members[j].size;
                        if (covered && strcmp(rows[k].vk_name, rows[k].member) == 0 &&
                            rows[k].offset != members[j].offset) {
                            printf("  FAIL: %s: direct row %s@%u != reflected @%u\n",
                                   layouts[li].files[fi], rows[k].vk_name,
                                   rows[k].offset, members[j].offset);
                        }
                        ASSERT_TRUE(!covered ||
                                    strcmp(rows[k].vk_name, rows[k].member) != 0 ||
                                    rows[k].offset == members[j].offset);
                    }
                    if (!covered) {
                        printf("  FAIL: layout %s: %s member '%s'@%u"
                               " not covered by expectation rows\n",
                               layouts[li].field, layouts[li].files[fi],
                               members[j].name, members[j].offset);
                    }
                    ASSERT_TRUE(covered);
                }
                for (usize k = 0u; k < row_count; k++) {
                    if (strcmp(rows[k].file, layouts[li].files[fi]) == 0) file_rows++;
                }
                if (non_pad == 0u) {
                    printf("  FAIL: layout %s: %s reflected no non-pad members\n",
                           layouts[li].field, layouts[li].files[fi]);
                }
                ASSERT_TRUE(non_pad > 0u);
            }
            if (file_rows == 0u) {
                printf("  FAIL: layout %s: no expectation rows\n", layouts[li].field);
            }
            ASSERT_TRUE(file_rows > 0u);
        }
    }
}

/* 计划 E Task 5 Stage C-2 前置：把 5a 的 push 反射交叉对照 gate 扩展到
 * compute shader。期望值逐项转录自 rhi_vk.c `rhi_pipeline_get_uniform_location`
 * 的 is_compute 段（gpucull/hi-z/indirect 等 .comp 消费者的现行表）——
 * 转录纪律与 5a 相同：反射必须等于表；发现真实 mismatch 先停线报告，不许
 * 改表、不许改 shader。批次 7-9 将把 compute offset 变成 bindings API 的
 * 承重路径，静态 gate 必须先行（5b review finding）。
 *
 * 两类条目（同 5a）：
 *  - 直接条目（vk_name == member）：offset 严格相等，size 按类型核对。
 *  - 别名条目（vk_name != member）：rhi_vk.c 查询名指向真实成员（cull.comp
 *    的成员就叫 vp/obj_count，表名 u_cull_vp/u_cull_count；occlusion_cull/
 *    hi_z_generate 同理），断言表 offset 落在成员 [offset, offset+size) 内。
 * 反向覆盖：除 particle_update.comp 外（见下），每个 gate 文件的非 pad 成员
 * 必须被至少一条条目命中。particle_update.comp 豁免：host 用硬编码 std430
 * 模板整块写 80 字节 push（particles.c push_data[]），除 push.dt 外没有
 * 逐成员 legacy 查询，emit 参数成员不在表内是设计现状而非漏项。
 * push.view/push.proj 不是 compute 条目——它们走 graphics uses_storage 段
 * （particle.vert 的 push 块），归批次 5 的 alias 行证明。 */
TEST(vk_compute_push_tables_match_reflection)
{
    static const VKPushRow rows[] = {
        /* cluster_cull.comp（直接条目） */
        { "cluster_cull.comp", "u_cc_vp", "u_cc_vp", 0u, 64u },
        { "cluster_cull.comp", "u_cc_params0", "u_cc_params0", 64u, 16u },
        { "cluster_cull.comp", "u_cc_params1", "u_cc_params1", 80u, 16u },
        /* compact_draws.comp（直接条目；成员名即 total_draws） */
        { "compact_draws.comp", "total_draws", "total_draws", 0u, 4u },
        /* irradiance_env.comp（直接条目） */
        { "irradiance_env.comp", "u_roughness", "u_roughness", 0u, 4u },
        { "irradiance_env.comp", "u_face", "u_face", 4u, 4u },
        { "irradiance_env.comp", "u_face_size", "u_face_size", 8u, 4u },
        /* prefilter_env.comp（直接条目；u_mip_size 与 u_face_size 同槽@8） */
        { "prefilter_env.comp", "u_roughness", "u_roughness", 0u, 4u },
        { "prefilter_env.comp", "u_face", "u_face", 4u, 4u },
        { "prefilter_env.comp", "u_mip_size", "u_mip_size", 8u, 4u },
        /* sky_to_cube.comp（直接条目；sun 向量在 16 对齐槽） */
        { "sky_to_cube.comp", "u_roughness", "u_roughness", 0u, 4u },
        { "sky_to_cube.comp", "u_face", "u_face", 4u, 4u },
        { "sky_to_cube.comp", "u_face_size", "u_face_size", 8u, 4u },
        { "sky_to_cube.comp", "u_sun_dir", "u_sun_dir", 16u, 12u },
        { "sky_to_cube.comp", "u_sun_color", "u_sun_color", 32u, 12u },
        /* cull.comp（别名条目：成员名 vp/obj_count） */
        { "cull.comp", "u_cull_vp", "vp", 0u, 0u },
        { "cull.comp", "u_cull_count", "obj_count", 64u, 0u },
        /* unified_cull.comp（别名条目：成员名 vp/obj_count/hi_z_width 等） */
        { "unified_cull.comp", "u_cull_vp", "vp", 0u, 0u },
        { "unified_cull.comp", "u_cull_count", "obj_count", 64u, 0u },
        { "unified_cull.comp", "u_cull_hi_z_width", "hi_z_width", 68u, 0u },
        { "unified_cull.comp", "u_cull_hi_z_height", "hi_z_height", 72u, 0u },
        { "unified_cull.comp", "u_cull_use_hi_z", "use_hi_z", 76u, 0u },
        { "unified_cull.comp", "u_cull_write_draws", "write_draws", 80u, 0u },
        /* occlusion_cull.comp（别名条目：成员名 view_proj/object_count/
         * hi_z_width/hi_z_height） */
        { "occlusion_cull.comp", "pc_view_proj", "view_proj", 0u, 0u },
        { "occlusion_cull.comp", "pc_object_count", "object_count", 64u, 0u },
        { "occlusion_cull.comp", "pc_hi_z_width", "hi_z_width", 68u, 0u },
        { "occlusion_cull.comp", "pc_hi_z_height", "hi_z_height", 72u, 0u },
        /* hi_z_generate.comp（别名条目：成员名 output_size，vec4） */
        { "hi_z_generate.comp", "pc_output_size", "output_size", 0u, 0u },
        /* particle_update.comp（别名条目：块实例名 push.dt → 成员 dt@0） */
        { "particle_update.comp", "push.dt", "dt", 0u, 0u },
    };
    static char src[32768];
    ShaderIOPushMember members[32];
    char current[64] = "";
    usize n = 0u;
    usize row_count = sizeof(rows) / sizeof(rows[0]);

    for (usize i = 0u; i < row_count; i++) {
        const VKPushRow *r = &rows[i];
        const ShaderIOPushMember *m;
        if (strcmp(current, r->file) != 0) {
            ASSERT_TRUE(read_shader_source(r->file, src, sizeof(src)));
            n = shader_reflect_push_constants(src, strlen(src), members, 32u);
            snprintf(current, sizeof(current), "%s", r->file);
            ASSERT_TRUE(n > 0u);
        }
        m = push_member_by_name(members, n, r->member);
        if (m == NULL) {
            printf("  FAIL: %s: member '%s' (vk name '%s') not reflected\n",
                   r->file, r->member, r->vk_name);
        }
        ASSERT_TRUE(m != NULL);
        if (strcmp(r->vk_name, r->member) == 0) {
            if (m->offset != r->offset) {
                printf("  FAIL: %s: %s reflected @%u, rhi_vk.c table @%u\n",
                       r->file, r->vk_name, m->offset, r->offset);
            }
            ASSERT_EQ(m->offset, r->offset);
            if (r->size != 0u && m->size != r->size) {
                printf("  FAIL: %s: %s reflected size %u, expected %u\n",
                       r->file, r->vk_name, m->size, r->size);
            }
            ASSERT_TRUE(r->size == 0u || m->size == r->size);
        } else {
            if (r->offset < m->offset || r->offset >= m->offset + m->size) {
                printf("  FAIL: %s: alias '%s'@%u outside member '%s'"
                       " [%u, %u)\n", r->file, r->vk_name, r->offset,
                       r->member, m->offset, m->offset + m->size);
            }
            ASSERT_TRUE(r->offset >= m->offset);
            ASSERT_TRUE(r->offset < m->offset + m->size);
        }
    }

    /* 反向覆盖（particle_update.comp 豁免 + pad 成员跳过，见上）。 */
    current[0] = '\0';
    for (usize i = 0u; i < row_count; i++) {
        if (strcmp(current, rows[i].file) == 0) continue;
        snprintf(current, sizeof(current), "%s", rows[i].file);
        if (strcmp(current, "particle_update.comp") == 0) continue;
        ASSERT_TRUE(read_shader_source(current, src, sizeof(src)));
        n = shader_reflect_push_constants(src, strlen(src), members, 32u);
        ASSERT_TRUE(n > 0u);
        for (usize j = 0u; j < n; j++) {
            bool covered = false;
            if (strncmp(members[j].name, "_pad", 4u) == 0 ||
                strncmp(members[j].name, "u_pad", 5u) == 0 ||
                strncmp(members[j].name, "pad", 3u) == 0) continue;
            for (usize k = 0u; k < row_count && !covered; k++) {
                if (strcmp(rows[k].file, current) != 0) continue;
                if (strcmp(rows[k].member, members[j].name) != 0) continue;
                covered = rows[k].offset >= members[j].offset &&
                          rows[k].offset < members[j].offset + members[j].size;
            }
            if (!covered) {
                printf("  FAIL: %s: member '%s'@%u not covered by any"
                       " rhi_vk.c compute table row\n",
                       current, members[j].name, members[j].offset);
            }
            ASSERT_TRUE(covered);
        }
    }
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
    RUN_TEST(shader_abi_reflection_is_deterministic_and_backend_neutral);
    RUN_TEST(shader_abi_reflection_capacity_and_gl_defaults);
    RUN_TEST(shader_abi_reflection_rejects_malformed_boundaries);
    RUN_TEST(shader_abi_reflection_rejects_unknown_layout_and_duplicate_bindings);
    RUN_TEST(shader_abi_reflection_rejects_unsupported_resource_kind);
    RUN_TEST(shader_abi_reflection_rejects_duplicates_beyond_output_capacity);
    RUN_TEST(shader_abi_reflection_requires_exact_supported_types);
    RUN_TEST(shader_abi_reflection_classifies_images);
    RUN_TEST(shader_abi_reflection_accepts_non_nul_input_and_hashes_canonically);
    RUN_TEST(shader_abi_hash_ignores_struct_padding);
    RUN_TEST(shader_abi_reflection_rejects_extreme_lengths_and_missing_names);
    RUN_TEST(shader_abi_hash_handles_non_nul_fixed_fields);
    RUN_TEST(shader_abi_hash_total_order_covers_all_hashed_fields);
    RUN_TEST(shader_abi_reflection_partial_input_skips_malformed_declarations);
    RUN_TEST(shader_abi_rhi_formats_mrt_resources_and_indirect);
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
    RUN_TEST(pbr_factor_gate_restored_real_assertion);
    RUN_TEST(variant_path_appends_suffix_before_extension);
    RUN_TEST(push_constants_follow_std430_offsets);
    RUN_TEST(push_constants_absent_returns_zero_and_handles_null);
    RUN_TEST(vk_push_tables_match_reflection);
    RUN_TEST(vk_compute_push_tables_match_reflection);
    RUN_TEST(hlsl_blinn_sidecars_mirror_glsl_twin_after_camera_moved_to_cbv);
    RUN_TEST(d3d12_root_signature_dedupes_per_stage_tables_with_full_visibility);
TEST_MAIN_END()
