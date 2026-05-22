#version 450 core

in vec3 v_ray_dir;

layout(location = 0) out vec4 frag_color;

const vec3 SKY_ZENITH  = vec3(0.25, 0.42, 0.78);
const vec3 SKY_HORIZON = vec3(0.50, 0.68, 0.90);
const vec3 SKY_NADIR   = vec3(0.08, 0.08, 0.12);

void main() {
    float t = v_ray_dir.y;

    vec3 col;
    if (t > 0.0) {
        col = mix(SKY_HORIZON, SKY_ZENITH, pow(t, 0.6));
    } else {
        col = mix(SKY_HORIZON, SKY_NADIR, pow(-t, 0.8));
    }

    frag_color = vec4(col, 1.0);
}
