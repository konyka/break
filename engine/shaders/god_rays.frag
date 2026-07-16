#version 450

layout(location = 0) in vec2 vUV;
layout(location = 0) out vec4 fragColor;

/* R217-B: Match bind_material_textures (scene@0, depth@shadow@1) and VK. */
layout(binding = 0) uniform sampler2D u_gr_scene;
layout(binding = 1) uniform sampler2D u_gr_depth;

uniform float u_gr_sun_x;
uniform float u_gr_sun_y;
uniform float u_gr_intensity;
uniform float u_gr_sw;
uniform float u_gr_sh;

void main() {
    vec2 sun_uv = vec2(u_gr_sun_x, u_gr_sun_y);
    vec2 delta = (vUV - sun_uv) / 32.0;

    vec3 scene = texture(u_gr_scene, vUV).rgb;

    float illum = 0.0;
    vec2 ray = vUV;

    for (int i = 0; i < 32; i++) {
        ray -= delta;
        if (ray.x < 0.0 || ray.x > 1.0 || ray.y < 0.0 || ray.y > 1.0) break;

        float d = texture(u_gr_depth, ray).r;
        if (d >= 1.0) {
            float dist = 1.0 - float(i) / 32.0;
            illum += dist * dist;
        }
    }
    illum /= 32.0;
    illum *= u_gr_intensity;

    float sun_dist = length(vUV - sun_uv);
    float mask = 1.0 - smoothstep(0.0, 0.8, sun_dist);

    vec3 rays = scene * illum * mask * 2.0;

    fragColor = vec4(clamp(scene + rays, 0.0, 1.0), 1.0);
}
