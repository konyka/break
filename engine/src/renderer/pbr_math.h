/* ==========================================================================
 *  pbr_math.h — CPU reference Cook-Torrance microfacet BRDF (R579).
 *
 *  Mirrors the GLSL terms in shaders/pbr_clustered.frag and
 *  shaders/deferred_light.frag exactly:
 *    - alpha = roughness^2 (alpha^2 = roughness^4 in D's numerator)
 *    - Smith geometry with Schlick-GGX terms, k = (r+1)^2 / 8 (direct light)
 *    - Schlick Fresnel with the manual 5th power (R84-4, no pow())
 *
 *  Locked by tests/test_pbr_math.c (closed-form anchors + properties).
 *  Radiance and the NdotL cosine factor stay with the caller, matching the
 *  shaders' outer multiply: Lo += (kD * albedo / PI + specular) * E * NdotL.
 * ========================================================================== */

#ifndef PBR_MATH_H
#define PBR_MATH_H

#include <math.h>

#define PBR_PI 3.14159265358979f

/* F0 = mix(0.04, albedo, metallic) — dielectric constant vs metal tint. */
static inline void pbr_f0(const float albedo[3], float metallic, float out[3]) {
    for (int i = 0; i < 3; i++)
        out[i] = 0.04f + (albedo[i] - 0.04f) * metallic;
}

/* Schlick Fresnel; manual 5th power (R84-4). cos_theta in [0, 1]. */
static inline void pbr_f_schlick(float cos_theta, const float f0[3], float out[3]) {
    float t = 1.0f - cos_theta;
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;
    float t5 = t * t * t * t * t;
    for (int i = 0; i < 3; i++)
        out[i] = f0[i] + (1.0f - f0[i]) * t5;
}

/* GGX / Trowbridge-Reitz normal distribution. alpha = roughness^2. */
static inline float pbr_d_ggx(float ndoth, float roughness) {
    float a  = roughness * roughness;
    float a2 = a * a;
    float ndoth2 = ndoth * ndoth;
    float denom  = ndoth2 * (a2 - 1.0f) + 1.0f;
    return a2 / (PBR_PI * denom * denom);
}

/* Smith geometry, Schlick-GGX terms, k = (r+1)^2/8 (direct lighting). */
static inline float pbr_g_smith(float ndotv, float ndotl, float roughness) {
    float r = roughness + 1.0f;
    float k = (r * r) / 8.0f;
    float ggx1 = ndotv / (ndotv * (1.0f - k) + k);
    float ggx2 = ndotl / (ndotl * (1.0f - k) + k);
    return ggx1 * ggx2;
}

/* Full split BRDF evaluation f(V, L) without the NdotL cosine factor.
 *   diffuse  = kD * albedo / PI,  kD = (1 - F) * (1 - metallic)
 *   specular = D * F * G / (4 * NdotV * NdotL + 1e-4)
 * V, L, N are unit vectors. */
static inline void pbr_brdf_eval(const float v[3], const float l[3], const float n[3],
                                 const float albedo[3], float metallic, float roughness,
                                 float out_diffuse[3], float out_specular[3]) {
    float hx = v[0] + l[0], hy = v[1] + l[1], hz = v[2] + l[2];
    float hlen = sqrtf(hx * hx + hy * hy + hz * hz);
    if (hlen > 0.0f) { hx /= hlen; hy /= hlen; hz /= hlen; }

    float ndoth = n[0] * hx + n[1] * hy + n[2] * hz;
    float ndotv = n[0] * v[0] + n[1] * v[1] + n[2] * v[2];
    float ndotl = n[0] * l[0] + n[1] * l[1] + n[2] * l[2];
    float hdotv = hx * v[0] + hy * v[1] + hz * v[2];
    if (ndoth < 0.0f) ndoth = 0.0f;
    if (ndotv < 0.0f) ndotv = 0.0f;
    if (ndotl < 0.0f) ndotl = 0.0f;
    if (hdotv < 0.0f) hdotv = 0.0f;

    float f0[3];
    pbr_f0(albedo, metallic, f0);

    float d = pbr_d_ggx(ndoth, roughness);
    float f[3];
    pbr_f_schlick(hdotv, f0, f);
    float g = pbr_g_smith(ndotv, ndotl, roughness);

    float denom = 4.0f * ndotv * ndotl + 1e-4f;
    for (int i = 0; i < 3; i++) {
        out_specular[i] = d * f[i] * g / denom;
        float kd = (1.0f - f[i]) * (1.0f - metallic);
        out_diffuse[i]  = kd * albedo[i] / PBR_PI;
    }
}

#endif /* PBR_MATH_H */
