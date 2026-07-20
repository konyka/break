#version 450 core

layout(location = 0) in vec3 aPos;

uniform mat4 u_view;
uniform mat4 u_proj;
uniform float u_water_y;

out vec3 vWorldPos;

void main() {
    /* R235-B: Mesh verts sit at y=0; lift to logical water plane. */
    vec3 wp = vec3(aPos.x, u_water_y, aPos.z);
    vWorldPos = wp;
    gl_Position = u_proj * u_view * vec4(wp, 1.0);
}
