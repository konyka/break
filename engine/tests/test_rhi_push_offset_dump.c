/* Plan C Task 11: golden dump for push-constant uniform byte offsets.
 * Builds a Vulkan device (any VK host; SKIP=77 when unavailable) and one
 * pipeline per desc-flag combination that distinguishes the offset tables,
 * then prints "<cfg> <name> <offset>" for every name resolving to >= 0.
 * The output is pasted into test_rhi_metal_resources.c as the golden block
 * the Metal backend's rhi_pipeline_get_uniform_location must reproduce
 * byte-for-byte (the two table implementations are a mechanical port).
 * GLSL stubs are content-free: the tables are desc-driven. */
#include "engine.h"
#include "rhi/rhi.h"
#include "platform/platform.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char *k_names[] = {
    "u_model",
    "u_view",
    "u_proj",
    "u_prev_mvp",
    "u_light_vp",
    "u_light_dir",
    "u_shadow_bias",
    "u_light_color",
    "u_water_y",
    "u_ambient",
    "u_time",
    "u_camera_pos",
    "u_water_color",
    "u_mvp",
    "u_light_pos",
    "u_far_plane",
    "u_taa_curr_vp",
    "u_taa_prev_vp",
    "u_taa_inv_proj",
    "u_screen_w",
    "u_screen_h",
    "u_taa_blend",
    "u_taa_first_frame",
    "u_fxaa_threshold",
    "u_taa_use_velocity",
    "u_tm_exposure",
    "u_tm_gamma",
    "u_tm_mode",
    "u_cg_saturation",
    "u_cg_contrast",
    "u_cg_brightness",
    "u_cg_temperature",
    "u_cg_tint",
    "u_cine_aberration",
    "u_cine_vignette",
    "u_cine_grain",
    "u_cine_time",
    "push.dt",
    "push.view",
    "push.proj",
    "u_roughness",
    "u_face",
    "u_face_size",
    "u_mip_size",
    "u_sun_dir",
    "u_sun_color",
    "u_cc_vp",
    "u_cc_params0",
    "u_cc_params1",
    "u_cull_vp",
    "u_cull_count",
    "u_cull_hi_z_width",
    "u_cull_hi_z_height",
    "u_cull_use_hi_z",
    "u_cull_write_draws",
    "pc_view_proj",
    "pc_object_count",
    "pc_hi_z_width",
    "pc_hi_z_height",
    "pc_output_size",
    "total_draws",
    "u_prev_vp",
    "u_vol_inv_proj",
    "u_vol_view",
    "u_vol_ldx",
    "u_vol_ldy",
    "u_vol_ldz",
    "u_vol_lcx",
    "u_vol_lcy",
    "u_vol_lcz",
    "u_vol_density",
    "u_vol_fog_r",
    "u_vol_fog_g",
    "u_vol_fog_b",
    "u_vol_sw",
    "u_vol_sh",
    "u_vol_inv_view",
    "u_lf_light_x",
    "u_lf_light_y",
    "u_lf_intensity",
    "u_lf_sw",
    "u_lf_sh",
    "u_lf_lc_r",
    "u_lf_lc_g",
    "u_lf_lc_b",
    "u_ssgi_inv_proj",
    "u_ssgi_proj",
    "u_ssgi_radius",
    "u_ssgi_intensity",
    "u_ssgi_sw",
    "u_ssgi_sh",
    "u_fxaa_sw",
    "u_fxaa_sh",
    "u_tm_screen_w",
    "u_tm_screen_h",
    "u_cine_sw",
    "u_cine_sh",
    "u_dof_focus",
    "u_dof_range",
    "u_dof_near",
    "u_dof_far",
    "u_dof_sw",
    "u_dof_sh",
    "u_ssr_proj",
    "u_ssr_inv_proj",
    "u_ssr_view",
    "u_ssr_sw",
    "u_ssr_sh",
    "u_ssr_max_steps",
    "u_ssr_stride",
    "u_ssr_thickness",
    "u_taa_sw",
    "u_taa_sh",
    "u_ssao_proj",
    "u_ssao_inv_proj",
    "u_ssao_sw",
    "u_ssao_sh",
    "u_ssao_radius",
    "u_ssao_bias",
    "u_dv_mode",
    "u_dv_near",
    "u_dv_far",
    "u_dv_split0",
    "u_dv_split1",
    "u_dv_split2",
    "u_dv_split3",
    "u_ca_strength",
    "u_vignette_strength",
    "u_vignette_softness",
    "u_grain_strength",
    "u_sharp_strength",
    "u_sharp_sw",
    "u_sharp_sh",
    "u_ups_rw",
    "u_ups_rh",
    "u_ups_dw",
    "u_ups_dh",
    "u_ups_sharp",
    "u_ups_copy_only",
    "u_ups_first_frame",
    "u_ups_inv_proj",
    "u_ups_prev_vp",
    "u_lum_w",
    "u_lum_h",
    "u_lum_speed",
    "u_lum_dt",
    "u_gr_sun_x",
    "u_gr_sun_y",
    "u_gr_intensity",
    "u_gr_decay",
    "u_gr_sw",
    "u_gr_sh",
    "u_mb_strength",
    "u_mb_sw",
    "u_mb_sh",
    "u_mb_inv_proj",
    "u_mb_prev_vp",
    "u_mb_use_velocity",
    "u_cs_light_x",
    "u_cs_light_y",
    "u_cs_light_z",
    "u_cs_inv_proj",
    "u_cs_sw",
    "u_cs_sh",
    "u_threshold",
    "u_direction",
    "u_bloom_strength",
    "u_sss_strength",
    "u_sss_sw",
    "u_sss_sh",
    "u_sss_max_dist",
    "u_sssv_strength",
    "u_sssv_sw",
    "u_sssv_sh",
    "u_sssv_max_dist",
    "u_fog_near",
    "u_fog_far",
    "u_near",
    "u_far",
    "u_point_count",
    "u_dir_count",
    "u_fog_color",
    "u_underwater",
    "u_point_shadow_far_planes",
    "u_pom_enabled",
    "u_occlusion_strength",
    "u_mr_factor",
    "u_emissive_factor",
    "u_inv_vp",
    "u_albedo",
    "u_inv_proj",
    "u_curr_vp"
};

typedef struct {
    const char *tag;
    RHIPipelineDesc desc;
} DumpCfg;

static const char *k_vs =
    "#version 450\n"
    "void main() { gl_Position = vec4(0.0); }\n";
static const char *k_fs =
    "#version 450\n"
    "layout(location = 0) out vec4 o_color;\n"
    "void main() { o_color = vec4(1.0); }\n";
static const char *k_cs =
    "#version 450\n"
    "layout(local_size_x = 1) in;\n"
    "void main() { }\n";
/* Shadow-depth pipelines pair against a depth-only pass (zero color
 * attachments); mimic the production depth shaders (gl_FragDepth write, no
 * color output) or vkCreateGraphicsPipelines fails. */
static const char *k_fs_shadow =
    "#version 450\n"
    "void main() { gl_FragDepth = 1.0; }\n";

int main(void) {
#ifndef ENGINE_VULKAN
    return 77;
#else
    static const DumpCfg cfgs[] = {
        /* All-default desc. Written as a designated init of the first member:
         * elided "{0}" trips GCC -Werror=missing-braces (RHIPipelineDesc's
         * first member vert is itself an aggregate), while a braced "{{
         * 0 }}" trips Clang -Werror=missing-field-initializers. */
        { "default", { .vert = { 0u, 0u } } },
        { "terrain", { .terrain_layout = true } },
        { "water", { .water_layout = true } },
        { "combined_aa", { .combined_aa_layout = true } },
        { "combined_color", { .combined_color_layout = true } },
        { "shadow_depth", { .is_shadow_depth = true } },
        { "skinned_gbuffer", { .skinned_vertex = true, .uses_texel_buffer = true } },
        { "clustered", { .uses_texel_buffer = true } },
        { "nonclustered_tbo", { .uses_texel_buffer = true, .is_instanced = true } },
        { "compute", { .is_compute = true } },
        { "storage", { .uses_storage = true } },
        { "no_vertex_input", { .no_vertex_input = true } },
        { "nvi_tbo", { .no_vertex_input = true, .uses_texel_buffer = true } },
    };
    PlatformConfig cfg = { 320u, 240u, "push-offset-dump", NULL, NULL, false };
    Platform *platform = platform_create(&cfg);
    RHIDevice *dev;
    u32 w = 0u, h = 0u, ci;
    RHIShader vs, fs, cs, fs_shadow;
    if (platform == NULL) return 77;
    platform_get_drawable_size(platform, &w, &h);
    dev = rhi_device_create(RHI_BACKEND_VULKAN,
                            platform_surface_native(platform),
                            platform_display_native(platform), w, h);
    if (dev == NULL) { platform_destroy(platform); return 77; }
    vs = rhi_shader_create(dev, k_vs, (usize)strlen(k_vs), false);
    fs = rhi_shader_create(dev, k_fs, (usize)strlen(k_fs), true);
    cs = rhi_shader_create_compute(dev, k_cs, (usize)strlen(k_cs));
    fs_shadow = rhi_shader_create(dev, k_fs_shadow, (usize)strlen(k_fs_shadow),
                                  true);
    if (!rhi_handle_valid(vs) || !rhi_handle_valid(fs) ||
        !rhi_handle_valid(cs) || !rhi_handle_valid(fs_shadow)) {
        rhi_device_destroy(dev);
        platform_destroy(platform);
        return 77;
    }
    {
        /* vk->shadow_render_pass is created lazily by rhi_shadow_map_create;
         * without it the is_shadow_depth pipeline create fails closed. */
        RHIShadowMap sm = rhi_shadow_map_create(dev, 64u, 64u);
        if (!rhi_handle_valid(sm.fbo)) {
            rhi_device_destroy(dev);
            platform_destroy(platform);
            return 77;
        }
        for (ci = 0u; ci < sizeof(cfgs) / sizeof(cfgs[0]); ++ci) {
        RHIPipelineDesc desc = cfgs[ci].desc;
        RHIPipeline pipe;
        usize ni;
        desc.vert = vs;
        desc.frag = cfgs[ci].desc.is_compute ? cs
                  : cfgs[ci].desc.is_shadow_depth ? fs_shadow : fs;
        pipe = rhi_pipeline_create(dev, &desc);
        if (!rhi_handle_valid(pipe)) {
            fprintf(stderr, "pipeline create failed for cfg %s\n", cfgs[ci].tag);
            continue;
        }
        for (ni = 0u; ni < sizeof(k_names) / sizeof(k_names[0]); ++ni) {
            i32 off = rhi_pipeline_get_uniform_location(dev, pipe, k_names[ni]);
            if (off >= 0)
                printf("%s %s %d\n", cfgs[ci].tag, k_names[ni], (int)off);
        }
        rhi_pipeline_destroy(dev, pipe);
        }
        rhi_shadow_map_destroy(dev, &sm);
    }
    rhi_shader_destroy(dev, vs);
    rhi_shader_destroy(dev, fs);
    rhi_shader_destroy(dev, cs);
    rhi_shader_destroy(dev, fs_shadow);
    rhi_device_destroy(dev);
    platform_destroy(platform);
    return 0;
#endif
}
