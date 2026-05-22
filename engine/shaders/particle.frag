#version 450

layout(location = 0) in vec4 v_color;
layout(location = 1) in float v_size;

layout(location = 0) out vec4 frag_color;

void main() {
    /* Make point sprite circular with soft edge */
    vec2 coord = gl_PointCoord - vec2(0.5);
    float dist = dot(coord, coord);
    if (dist > 0.25) discard;

    float alpha = 1.0 - smoothstep(0.1, 0.25, dist);
    frag_color = vec4(v_color.rgb, v_color.a * alpha);
}
