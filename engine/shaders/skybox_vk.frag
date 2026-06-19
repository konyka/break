#version 450 core

layout(location = 0) in vec3 v_ray_dir;

layout(location = 0) out vec4 frag_color;

layout(push_constant) uniform PushConstants {
    layout(offset = 0)   mat4 u_inv_proj;
    layout(offset = 64)  mat4 u_view;
    layout(offset = 128) vec3 u_sun_dir;
    layout(offset = 140) float _pad0;
    layout(offset = 144) vec3 u_sun_color;
} pc;

const float PI = 3.14159265;

const vec3 RAYLEIGH_COEFF = vec3(5.5e-6, 13.0e-6, 22.4e-6);
const float MIE_COEFF = 21.0e-6;
const float RAYLEIGH_SCALE = 8.4e3;
const float MIE_SCALE = 1.25e3;
const float G_MIE = 0.758;
const float SUN_INTENSITY = 20.0;

float phase_rayleigh(float cos_theta) {
    return (3.0 / (16.0 * PI)) * (1.0 + cos_theta * cos_theta);
}

float phase_mie(float cos_theta) {
    float g = G_MIE;
    float g2 = g * g;
    float num = (1.0 - g2);
    float denom = (4.0 * PI) * (1.0 + g2 - 2.0 * g * cos_theta) * sqrt(1.0 + g2 - 2.0 * g * cos_theta);
    return num / max(denom, 1e-6);
}

float atmosphere_density(float height) {
    float rayleigh = exp(-max(height, 0.0) / RAYLEIGH_SCALE);
    float mie = exp(-max(height, 0.0) / MIE_SCALE);
    return min(rayleigh + mie, 1.0);
}

float hash3(vec3 p) {
    p = fract(p * vec3(0.1031, 0.1030, 0.0973));
    p += dot(p, p.yxz + 33.33);
    return fract((p.x + p.y) * p.z);
}

float noise3(vec3 p) {
    vec3 i = floor(p);
    vec3 f = fract(p);
    f = f * f * (3.0 - 2.0 * f);
    return mix(
        mix(mix(hash3(i), hash3(i + vec3(1,0,0)), f.x),
            mix(hash3(i + vec3(0,1,0)), hash3(i + vec3(1,1,0)), f.x), f.y),
        mix(mix(hash3(i + vec3(0,0,1)), hash3(i + vec3(1,0,1)), f.x),
            mix(hash3(i + vec3(0,1,1)), hash3(i + vec3(1,1,1)), f.x), f.y),
        f.z);
}

float fbm(vec2 p) {
    float v = 0.0;
    float a = 0.5;
    vec2 shift = vec2(100.0);
    for (int i = 0; i < 4; i++) {
        v += a * noise3(vec3(p, float(i) * 0.3));
        p = p * 2.0 + shift;
        a *= 0.5;
    }
    return v;
}

void main() {
    vec3 ray = normalize(v_ray_dir);
    vec3 sun = pc.u_sun_dir;  /* R91-3: C code already normalizes sun_dir */

    float cos_sun = max(dot(ray, sun), -1.0);

    float rayleigh_phase = phase_rayleigh(cos_sun);
    float mie_phase = phase_mie(cos_sun);

    float zenith = acos(clamp(ray.y, -1.0, 1.0));
    float density = atmosphere_density(zenith * 6371.0);

    vec3 rayleigh_scat = RAYLEIGH_COEFF * rayleigh_phase * density;
    float mie_scat = MIE_COEFF * mie_phase * density;

    vec3 scattering = (rayleigh_scat + vec3(mie_scat)) * SUN_INTENSITY;

    float optical_depth = density * 0.5;
    vec3 extinction = exp(-(RAYLEIGH_COEFF + vec3(MIE_COEFF * 0.1)) * optical_depth * 6371.0 * 0.01);

    vec3 sky = pc.u_sun_color * scattering * extinction;

    float sun_disc = smoothstep(0.9995, 0.9999, cos_sun);
    float sun_halo = smoothstep(0.993, 0.999, cos_sun);
    sky += pc.u_sun_color * SUN_INTENSITY * 0.05 * sun_disc * extinction;
    sky += pc.u_sun_color * SUN_INTENSITY * 0.008 * sun_halo * extinction;

    float horizon_fog = 1.0 - abs(ray.y);
    horizon_fog = horizon_fog * horizon_fog * horizon_fog;
    sky += pc.u_sun_color * 0.1 * horizon_fog * extinction;

    const float CLOUD_MIN = 1500.0;
    const float CLOUD_MAX = 4000.0;
    const float CLOUD_DENSITY = 0.4;
    const int CLOUD_STEPS = 24;

    vec3 cloud_color = sky;
    if (ray.y > 0.01) {
        float t_min = CLOUD_MIN / ray.y;
        float t_max = CLOUD_MAX / ray.y;
        float step_size = (t_max - t_min) / float(CLOUD_STEPS);

        float transmittance = 1.0;
        vec3 accumulated = vec3(0.0);

        for (int i = 0; i < CLOUD_STEPS; i++) {
            float t = t_min + (float(i) + 0.5) * step_size;
            vec3 pos = ray * t;

            vec2 cloud_uv = pos.xz * 0.0003;
            float n = fbm(cloud_uv);
            float cloud_d = smoothstep(1.0 - CLOUD_DENSITY, 1.0, n);

            if (cloud_d > 0.01) {
                float height_frac = (t - t_min) / (t_max - t_min);
                cloud_d *= 1.0 - smoothstep(0.0, 0.15, height_frac);
                cloud_d *= 1.0 - smoothstep(0.85, 1.0, height_frac);

                float absorption = cloud_d * step_size * 0.001;
                float beer = exp(-absorption);

                /* R85-2: cos_light is loop-invariant — normalize(ray*t) = ray, dot(ray,sun) = cos_sun */
                float cos_light = max(cos_sun, 0.0);
                float powder = 1.0 - exp(-cloud_d * 2.0);
                float phase = 0.3 + 0.7 * max(cos_light, 0.0);
                phase *= powder;

                vec3 light = pc.u_sun_color * phase * (1.0 + cos_light * 0.5);
                vec3 ambient = pc.u_sun_color * 0.15 * cloud_d;

                accumulated += transmittance * (light + ambient) * (1.0 - beer);
                transmittance *= beer;

                if (transmittance < 0.01) break;
            }
        }

        cloud_color = accumulated + sky * transmittance;
    }

    cloud_color = cloud_color / (cloud_color + vec3(1.0));
    cloud_color = exp2(log2(max(cloud_color, vec3(0.0))) * (1.0 / 2.2));  /* R94-1: exp2 replaces pow */

    frag_color = vec4(cloud_color, 1.0);
}
