/* ==========================================================================
 *  test_pbr_math.c — Unit tests for the CPU reference Cook-Torrance PBR
 *  math (renderer/pbr_math.h).
 *
 *  The C reference mirrors the GLSL terms in pbr_clustered.frag and
 *  deferred_light.frag exactly (alpha = roughness^2, k = (r+1)^2/8 for
 *  direct lighting, manual 5th-power Schlick per R84-4). The closed-form
 *  anchors below lock the formulas so shader drift is detectable.
 * ========================================================================== */

#include "test_framework.h"
#include <renderer/pbr_math.h>
#include <math.h>

#define PI_REF 3.14159265358979f

/* ----------------------------------------------------------------------- */
/*  Fresnel (Schlick)                                                        */
/* ----------------------------------------------------------------------- */

TEST(fresnel_endpoints) {
    float f0[3] = {0.04f, 0.20f, 0.90f};
    float out[3];
    pbr_f_schlick(1.0f, f0, out); /* normal incidence (0 deg): exactly F0 */
    ASSERT_FLOAT_EQ(out[0], 0.04f, 1e-6f);
    ASSERT_FLOAT_EQ(out[1], 0.20f, 1e-6f);
    ASSERT_FLOAT_EQ(out[2], 0.90f, 1e-6f);
    pbr_f_schlick(0.0f, f0, out); /* grazing (90 deg): fully reflective */
    ASSERT_FLOAT_EQ(out[0], 1.0f, 1e-6f);
    ASSERT_FLOAT_EQ(out[1], 1.0f, 1e-6f);
    ASSERT_FLOAT_EQ(out[2], 1.0f, 1e-6f);
}

TEST(fresnel_golden_midpoint) {
    /* cos = 0.5 -> F0 + (1-F0) * 0.5^5 = F0 + (1-F0) * 0.03125 */
    float f0[3] = {0.04f, 0.04f, 0.04f};
    float out[3];
    pbr_f_schlick(0.5f, f0, out);
    ASSERT_FLOAT_EQ(out[0], 0.04f + 0.96f * 0.03125f, 1e-6f); /* 0.07 exactly */
}

TEST(fresnel_monotonic_in_cos) {
    float f0[3] = {0.04f, 0.04f, 0.04f};
    float prev = 2.0f;
    for (int i = 0; i <= 20; i++) {
        float c = (float)i / 20.0f; /* 0 = grazing, 1 = normal incidence */
        float out[3];
        pbr_f_schlick(c, f0, out);
        ASSERT_TRUE(out[0] <= prev + 1e-6f); /* F decreases toward normal incidence */
        ASSERT_TRUE(out[0] >= f0[0] - 1e-6f && out[0] <= 1.0f + 1e-6f);
        prev = out[0];
    }
}

/* ----------------------------------------------------------------------- */
/*  GGX / Trowbridge-Reitz normal distribution                               */
/* ----------------------------------------------------------------------- */

TEST(ggx_peak_closed_form) {
    /* At NdotH = 1: denom = a2 -> D = 1 / (pi * a2). r=0.5 -> a2 = 0.0625. */
    ASSERT_FLOAT_EQ(pbr_d_ggx(1.0f, 0.5f), 1.0f / (PI_REF * 0.0625f), 1e-4f);
    ASSERT_FLOAT_EQ(pbr_d_ggx(1.0f, 1.0f), 1.0f / PI_REF, 1e-4f);
}

TEST(ggx_peak_spreads_with_roughness) {
    /* Sharper (lower) roughness concentrates the lobe: higher peak. */
    ASSERT_TRUE(pbr_d_ggx(1.0f, 0.3f) > pbr_d_ggx(1.0f, 0.7f));
}

TEST(ggx_positive_and_tail_decays) {
    float prev = pbr_d_ggx(1.0f, 0.4f);
    for (int i = 19; i >= 0; i--) {
        float ndoth = (float)i / 20.0f;
        float d = pbr_d_ggx(ndoth, 0.4f);
        ASSERT_TRUE(d > 0.0f);
        ASSERT_TRUE(d <= prev + 1e-6f); /* non-increasing away from the peak */
        prev = d;
    }
}

/* ----------------------------------------------------------------------- */
/*  Geometry (Smith, Schlick-GGX, k = (r+1)^2/8)                             */
/* ----------------------------------------------------------------------- */

TEST(g_smith_range_and_identity) {
    /* Perfect alignment at r=0 (k=0.125): both terms = 1/(0.875+0.125) = 1. */
    ASSERT_FLOAT_EQ(pbr_g_smith(1.0f, 1.0f, 0.0f), 1.0f, 1e-6f);
    for (int ri = 0; ri <= 10; ri++) {
        float r = (float)ri / 10.0f;
        for (int vi = 1; vi <= 4; vi++) {
            float ndotv = (float)vi / 4.0f;
            float g = pbr_g_smith(ndotv, ndotv, r);
            ASSERT_TRUE(g > 0.0f && g <= 1.0f + 1e-5f);
        }
    }
}

TEST(g_smith_golden) {
    /* r=0.5 -> k = 2.25/8 = 0.28125; each term 0.5/(0.5*0.71875+0.28125);
     * G = (0.5/0.640625)^2 = 0.609161... */
    ASSERT_FLOAT_EQ(pbr_g_smith(0.5f, 0.5f, 0.5f), 0.6091613f, 1e-5f);
}

TEST(g_smith_decreases_with_roughness) {
    ASSERT_TRUE(pbr_g_smith(0.5f, 0.5f, 0.2f) > pbr_g_smith(0.5f, 0.5f, 0.8f));
}

/* ----------------------------------------------------------------------- */
/*  F0 mix + full BRDF evaluation                                           */
/* ----------------------------------------------------------------------- */

TEST(f0_mix_endpoints) {
    float albedo[3] = {0.7f, 0.4f, 0.2f};
    float f0[3];
    pbr_f0(albedo, 0.0f, f0); /* dielectric: constant 0.04 (glTF default) */
    ASSERT_FLOAT_EQ(f0[0], 0.04f, 1e-6f);
    ASSERT_FLOAT_EQ(f0[2], 0.04f, 1e-6f);
    pbr_f0(albedo, 1.0f, f0); /* metal: F0 = albedo */
    ASSERT_FLOAT_EQ(f0[0], 0.7f, 1e-6f);
    ASSERT_FLOAT_EQ(f0[1], 0.4f, 1e-6f);
    ASSERT_FLOAT_EQ(f0[2], 0.2f, 1e-6f);
}

static void normalize3(float v[3]) {
    float len = sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    v[0] /= len; v[1] /= len; v[2] /= len;
}

TEST(brdf_reciprocity) {
    float n[3] = {0.0f, 1.0f, 0.0f};
    float v[3] = {0.3f, 0.8f, 0.2f}; normalize3(v);
    float l[3] = {-0.4f, 0.7f, 0.3f}; normalize3(l);
    float albedo[3] = {0.7f, 0.4f, 0.2f};
    float diff_vl[3], spec_vl[3], diff_lv[3], spec_lv[3];
    pbr_brdf_eval(v, l, n, albedo, 0.3f, 0.45f, diff_vl, spec_vl);
    pbr_brdf_eval(l, v, n, albedo, 0.3f, 0.45f, diff_lv, spec_lv);
    for (int i = 0; i < 3; i++) {
        ASSERT_FLOAT_EQ(diff_vl[i], diff_lv[i], 1e-5f); /* Helmholtz reciprocity */
        ASSERT_FLOAT_EQ(spec_vl[i], spec_lv[i], 1e-5f);
    }
}

TEST(brdf_metallic_one_kills_diffuse) {
    float n[3] = {0.0f, 1.0f, 0.0f};
    float v[3] = {0.0f, 0.6f, 0.8f}; normalize3(v);
    float l[3] = {0.3f, 0.6f, 0.7f}; normalize3(l);
    float albedo[3] = {0.9f, 0.6f, 0.3f};
    float diff[3], spec[3];
    pbr_brdf_eval(v, l, n, albedo, 1.0f, 0.5f, diff, spec);
    ASSERT_FLOAT_EQ(diff[0], 0.0f, 1e-6f);
    ASSERT_FLOAT_EQ(diff[1], 0.0f, 1e-6f);
    ASSERT_FLOAT_EQ(diff[2], 0.0f, 1e-6f);
    ASSERT_TRUE(spec[0] > 0.0f); /* metallic surfaces still reflect specularly */
}

TEST(brdf_dielectric_diffuse_dominates_at_normal_incidence) {
    /* Head-on geometry: H = N so F = F0 = 0.04 and diffuse = 0.96 * albedo/pi. */
    float n[3] = {0.0f, 1.0f, 0.0f};
    float v[3] = {0.0f, 1.0f, 0.0f};
    float l[3] = {0.0f, 1.0f, 0.0f};
    float albedo[3] = {0.5f, 0.5f, 0.5f};
    float diff[3], spec[3];
    pbr_brdf_eval(v, l, n, albedo, 0.0f, 0.8f, diff, spec);
    ASSERT_FLOAT_EQ(diff[0], 0.96f * 0.5f / PI_REF, 1e-5f); /* (1-F0)*albedo/pi */
    ASSERT_TRUE(spec[0] < diff[0]);                          /* rough dielectric: diffuse dominant */
}

TEST(brdf_outputs_finite_and_nonnegative) {
    float n[3] = {0.0f, 1.0f, 0.0f};
    float albedo[3] = {0.8f, 0.8f, 0.8f};
    for (int ri = 1; ri <= 9; ri += 4) {
        for (int mi = 0; mi <= 1; mi++) {
            float v[3] = {0.2f, 0.9f, 0.4f}; normalize3(v);
            float l[3] = {-0.3f, 0.8f, 0.5f}; normalize3(l);
            float diff[3], spec[3];
            pbr_brdf_eval(v, l, n, albedo, (float)mi, (float)ri / 10.0f, diff, spec);
            for (int i = 0; i < 3; i++) {
                ASSERT_TRUE(isfinite(diff[i]) && diff[i] >= 0.0f);
                ASSERT_TRUE(isfinite(spec[i]) && spec[i] >= 0.0f);
            }
        }
    }
}

TEST_MAIN_BEGIN()
    RUN_TEST(fresnel_endpoints);
    RUN_TEST(fresnel_golden_midpoint);
    RUN_TEST(fresnel_monotonic_in_cos);
    RUN_TEST(ggx_peak_closed_form);
    RUN_TEST(ggx_peak_spreads_with_roughness);
    RUN_TEST(ggx_positive_and_tail_decays);
    RUN_TEST(g_smith_range_and_identity);
    RUN_TEST(g_smith_golden);
    RUN_TEST(g_smith_decreases_with_roughness);
    RUN_TEST(f0_mix_endpoints);
    RUN_TEST(brdf_reciprocity);
    RUN_TEST(brdf_metallic_one_kills_diffuse);
    RUN_TEST(brdf_dielectric_diffuse_dominates_at_normal_incidence);
    RUN_TEST(brdf_outputs_finite_and_nonnegative);
TEST_MAIN_END()
