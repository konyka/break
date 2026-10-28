// skybox_mrt_hlsl.frag - skybox PS, FORWARD_MRT twin of skybox_hlsl.frag
// (D3D12 hand-authored sidecar). Identical shading; the only delta is the
// second render target, which carries the zero motion vector skybox.frag
// emits under FORWARD_MRT. The fullscreen triangle is generated from
// SV_VertexID and the GLSL never applies a previous-frame transform to it, so
// there is no previous position to reconstruct and vec2(0.0) is the whole of
// the GLSL MRT arm.
struct PushConsts {
    float4x4 u_inv_proj;   //   0
    float4x4 u_view;       //  64
    float3   u_sun_dir;    // 128 (16B slot)
    float3   u_sun_color;  // 144
};                         // tail ends at 160
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_sun_dir 128
// rhi:uniform u_sun_color 144

static const float PI = 3.14159265;

static const float3 RAYLEIGH_COEFF = float3(5.5e-6, 13.0e-6, 22.4e-6);
static const float MIE_COEFF = 21.0e-6;
static const float RAYLEIGH_SCALE = 8.4e3;
static const float MIE_SCALE = 1.25e3;
static const float G_MIE = 0.758;
static const float SUN_INTENSITY = 20.0;
/* R446: Rayleigh gain lifts the linear sky base to ~0.05-0.2 so it survives
 * the single engine tonemap; Mie gets a much smaller gain because its
 * forward peak is ~20x stronger than Rayleigh near the sun. */
static const float SKY_RAYLEIGH_GAIN = 1500.0;
static const float SKY_MIE_GAIN = 50.0;

float phase_rayleigh(float cos_theta) {
    return (3.0f / (16.0f * PI)) * (1.0f + cos_theta * cos_theta);
}

float phase_mie(float cos_theta) {
    float g = G_MIE;
    float g2 = g * g;
    float num = (1.0f - g2);
    float denom = (4.0f * PI) * (1.0f + g2 - 2.0f * g * cos_theta)
                * sqrt(1.0f + g2 - 2.0f * g * cos_theta);
    return num / max(denom, 1e-6f);
}

float atmosphere_density(float height) {
    float rayleigh = exp(-max(height, 0.0f) / RAYLEIGH_SCALE);
    float mie = exp(-max(height, 0.0f) / MIE_SCALE);
    return min(rayleigh + mie, 1.0f);
}

float hash3(float3 p) {
    p = frac(p * float3(0.1031f, 0.1030f, 0.0973f));
    p += dot(p, p.yxz + 33.33f);
    return frac((p.x + p.y) * p.z);
}

/* R573: the GLSL name sky_noise3 exists because GLSL already has a builtin
 * float noise3(vec3) and an overload with a different return type is illegal
 * (strict Windows drivers reject it). The HLSL name is free; keep it anyway so
 * the twin stays diffable line for line. */
float sky_noise3(float3 p) {
    float3 i = floor(p);
    float3 f = frac(p);
    f = f * f * (3.0f - 2.0f * f);
    return lerp(
        lerp(lerp(hash3(i),                hash3(i + float3(1,0,0)), f.x),
             lerp(hash3(i + float3(0,1,0)), hash3(i + float3(1,1,0)), f.x), f.y),
        lerp(lerp(hash3(i + float3(0,0,1)), hash3(i + float3(1,0,1)), f.x),
             lerp(hash3(i + float3(0,1,1)), hash3(i + float3(1,1,1)), f.x), f.y),
        f.z);
}

float fbm(float2 p) {
    float v = 0.0f;
    float a = 0.5f;
    float2 shift = float2(100.0f, 100.0f);
    for (int i = 0; i < 4; ++i) {
        v += a * sky_noise3(float3(p, (float)i * 0.3f));
        p = p * 2.0f + shift;
        a *= 0.5f;
    }
    return v;
}

struct PSOut {
    float4 color : SV_Target0;
    float2 velocity : SV_Target1;   /* GLSL layout(location = 1) */
};
PSOut main(float4 pos : SV_Position, float3 ray_dir : TEXCOORD0) {
    float3 ray = normalize(ray_dir);
    float3 sun = g_push.u_sun_dir;  /* R91-3: C code already normalizes sun_dir */

    float cos_sun = max(dot(ray, sun), -1.0f);

    float rayleigh_phase = phase_rayleigh(cos_sun);
    float mie_phase = phase_mie(cos_sun);

    float zenith = acos(clamp(ray.y, -1.0f, 1.0f));
    float density = atmosphere_density(zenith * 6371.0f);

    float3 rayleigh_scat = RAYLEIGH_COEFF * rayleigh_phase * density;
    float mie_scat = MIE_COEFF * mie_phase * density;

    float3 scattering = rayleigh_scat * (SUN_INTENSITY * SKY_RAYLEIGH_GAIN)
                      + float3(mie_scat, mie_scat, mie_scat)
                        * (SUN_INTENSITY * SKY_MIE_GAIN);

    float mb = MIE_COEFF * 0.1f;
    float optical_depth = density * 0.5f;
    float3 extinction = exp(-(RAYLEIGH_COEFF + float3(mb, mb, mb))
                            * optical_depth * 6371.0f * 0.01f);

    float3 sky = g_push.u_sun_color * scattering * extinction;

    float sun_disc = smoothstep(0.9995f, 0.9999f, cos_sun);
    float sun_halo = smoothstep(0.993f, 0.999f, cos_sun);
    /* R446: the disc is a real HDR emitter (~10x the 1.0 bloom threshold) so
     * bloom isolates the sun instead of the whole sky. Halo stays modest. */
    sky += g_push.u_sun_color * SUN_INTENSITY * 0.5f * sun_disc * extinction;
    sky += g_push.u_sun_color * SUN_INTENSITY * 0.008f * sun_halo * extinction;

    float horizon_fog = 1.0f - abs(ray.y);
    horizon_fog = horizon_fog * horizon_fog * horizon_fog;
    sky += g_push.u_sun_color * 0.1f * horizon_fog * extinction;

    const float CLOUD_MIN = 1500.0f;
    const float CLOUD_MAX = 4000.0f;
    const float CLOUD_DENSITY = 0.4f;
    const int CLOUD_STEPS = 24;

    float3 cloud_color = sky;
    if (ray.y > 0.01f) {
        float t_min = CLOUD_MIN / ray.y;
        float t_max = CLOUD_MAX / ray.y;
        float step_size = (t_max - t_min) / (float)CLOUD_STEPS;

        float transmittance = 1.0f;
        float3 accumulated = float3(0.0f, 0.0f, 0.0f);

        for (int i = 0; i < CLOUD_STEPS; ++i) {
            float t = t_min + ((float)i + 0.5f) * step_size;
            float3 pos = ray * t;

            float2 cloud_uv = pos.xz * 0.0003f;
            float n = fbm(cloud_uv);
            float cloud_d = smoothstep(1.0f - CLOUD_DENSITY, 1.0f, n);

            if (cloud_d > 0.01f) {
                float height_frac = (t - t_min) / (t_max - t_min);
                cloud_d *= 1.0f - smoothstep(0.0f, 0.15f, height_frac);
                cloud_d *= 1.0f - smoothstep(0.85f, 1.0f, height_frac);

                float absorption = cloud_d * step_size * 0.001f;
                float beer = exp(-absorption);

                /* R85-2: cos_light is loop-invariant —
                 * normalize(ray*t) = ray, dot(ray,sun) = cos_sun */
                float cos_light = max(cos_sun, 0.0f);
                float powder = 1.0f - exp(-cloud_d * 2.0f);
                float phase = 0.3f + 0.7f * max(cos_light, 0.0f);
                phase *= powder;

                float3 light = g_push.u_sun_color * phase * (1.0f + cos_light * 0.5f);
                float3 ambient = g_push.u_sun_color * 0.15f * cloud_d;

                accumulated += transmittance * (light + ambient) * (1.0f - beer);
                transmittance *= beer;

                if (transmittance < 0.01f) break;
            }
        }

        cloud_color = accumulated + sky * transmittance;
    }

    /* R446: output LINEAR HDR. The scene pass renders into an HDR float
     * buffer that the combined_color pass tonemaps + gamma-encodes exactly
     * once. Matches the sky_to_cube.comp contract. */
    PSOut o;
    o.color = float4(max(cloud_color, float3(0.0f, 0.0f, 0.0f)), 1.0f);
    o.velocity = float2(0.0f, 0.0f);
    return o;
}
