#version 450

layout(location = 0) in vec2 vUV;
layout(location = 0) out vec4 fragColor;

layout(binding = 0) uniform sampler2D tex;
layout(binding = 1) uniform sampler2D depth_tex;

uniform int u_dv_mode;
uniform float u_dv_near;
uniform float u_dv_far;
uniform float u_dv_split0;
uniform float u_dv_split1;
uniform float u_dv_split2;
uniform float u_dv_split3;

vec3 normals_from_depth(vec2 uv) {
    vec2 ts = 1.0 / vec2(textureSize(depth_tex, 0));
    float d0 = texture(depth_tex, uv).r;
    float dx = texture(depth_tex, uv + vec2(ts.x, 0.0)).r;
    float dy = texture(depth_tex, uv + vec2(0.0, ts.y)).r;
    vec3 p0 = vec3(uv, d0) * 2.0 - 1.0;
    vec3 p1 = vec3(uv + vec2(ts.x, 0.0), dx) * 2.0 - 1.0;
    vec3 p2 = vec3(uv + vec2(0.0, ts.y), dy) * 2.0 - 1.0;
    vec3 n = normalize(cross(p1 - p0, p2 - p0));
    return n * 0.5 + 0.5;
}

void main() {
    vec3 result = vec3(0.0);

    if (u_dv_mode == 0) {
        result = texture(tex, vUV).rgb;
    } else if (u_dv_mode == 1) {
        float d = texture(depth_tex, vUV).r;
        float linear_d = u_dv_near * u_dv_far / (u_dv_far - d * (u_dv_far - u_dv_near));
        float viz = clamp(linear_d / u_dv_far, 0.0, 1.0);
        result = mix(vec3(0.0, 0.0, 1.0), vec3(1.0, 0.0, 0.0), viz);
    } else if (u_dv_mode == 2) {
        result = normals_from_depth(vUV);
    } else if (u_dv_mode == 3) {
        result = texture(tex, vUV).rrr;
    } else if (u_dv_mode == 4) {
        float d = texture(depth_tex, vUV).r;
        float linear_d = u_dv_near * u_dv_far / (u_dv_far - d * (u_dv_far - u_dv_near));
        vec3 cascade_colors[4];
        cascade_colors[0] = vec3(1.0, 0.2, 0.2);
        cascade_colors[1] = vec3(0.2, 1.0, 0.2);
        cascade_colors[2] = vec3(0.2, 0.4, 1.0);
        cascade_colors[3] = vec3(1.0, 1.0, 0.2);
        float splits[4];
        splits[0] = u_dv_split0; splits[1] = u_dv_split1;
        splits[2] = u_dv_split2; splits[3] = u_dv_split3;
        result = cascade_colors[3];
        for (int i = 0; i < 4; i++) {
            if (linear_d < splits[i]) {
                result = cascade_colors[i];
                break;
            }
        }
    }

    fragColor = vec4(result, 1.0);
}
