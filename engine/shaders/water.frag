#version 450 core

in vec3 vWorldPos;

uniform float u_time;
uniform vec3 u_camera_pos;
uniform vec3 u_water_color;
uniform mat4 u_light_vp;
uniform sampler2D u_shadow_map;
uniform float u_shadow_bias;
uniform float u_water_y;

out vec4 FragColor;

float water_shadow(vec3 wp) {
    vec4 clip = u_light_vp * vec4(wp, 1.0);
    vec3 ndc = clip.xyz / clip.w;
    vec2 uv = ndc.xy * 0.5 + 0.5;
    if (uv.x < 0.0 || uv.x > 1.0 || uv.y < 0.0 || uv.y > 1.0) return 1.0;
    /* u_light_vp is CSM cascade 0 -> quadrant (0,0) of the shadow atlas. */
    vec2 texel = 1.0 / vec2(textureSize(u_shadow_map, 0));
    vec2 atlas_uv = clamp(uv * 0.5, texel, vec2(0.5) - texel);
    return (ndc.z - u_shadow_bias) > texture(u_shadow_map, atlas_uv).r ? 0.5 : 1.0;
}

void main() {
    float dist = length(vWorldPos.xz - u_camera_pos.xz);
    float fade = 1.0 - smoothstep(10.0, 50.0, dist);

    float wave1 = sin(vWorldPos.x * 0.8 + u_time * 1.2) * 0.15;
    float wave2 = sin(vWorldPos.z * 1.1 + u_time * 0.9) * 0.1;
    float wave3 = sin((vWorldPos.x + vWorldPos.z) * 0.5 + u_time * 1.5) * 0.08;
    float wave = (wave1 + wave2 + wave3) * fade;

    float fresnel = 0.04 + 0.96 * pow(1.0 - max(dot(normalize(u_camera_pos - vWorldPos), vec3(0, 1, 0)), 0.0), 3.0);

    vec3 deep = u_water_color * 0.5;
    vec3 surface = u_water_color * 1.2 + vec3(0.05, 0.08, 0.1) * wave;
    vec3 color = mix(deep, surface, fresnel * fade);

    float shadow = water_shadow(vWorldPos);
    color *= shadow;

    float depth_darken = 1.0;
    if (u_camera_pos.y < u_water_y) {
        depth_darken = clamp(1.0 - (u_water_y - u_camera_pos.y) * 0.15, 0.2, 1.0);
    }
    color *= depth_darken;

    float specular = pow(max(0.0, sin(vWorldPos.x * 3.0 + u_time * 2.0) * sin(vWorldPos.z * 2.5 + u_time * 1.7)), 32.0) * 0.4 * fade;
    color += vec3(specular);

    float alpha = mix(0.5, 0.85, fresnel) * fade;
    FragColor = vec4(color, alpha);
}
