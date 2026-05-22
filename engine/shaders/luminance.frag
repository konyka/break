#version 450

layout(location = 0) in vec2 vUV;
layout(location = 0) out vec4 fragColor;

uniform sampler2D u_lum_hdr;

void main() {
    vec3 color = texture(u_lum_hdr, vUV).rgb;
    float luma = dot(color, vec3(0.2126, 0.7152, 0.0722));
    fragColor = vec4(luma, 0.0, 0.0, 1.0);
}
