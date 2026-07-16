#version 450 core

layout(location = 0) in vec3 aPos;

layout(push_constant) uniform PushConstants {
    mat4 u_light_mvp;
} pc;

void main() {
    gl_Position = pc.u_light_mvp * vec4(aPos, 1.0);
    /* R211-A: OpenGL-style ortho → clip.z∈[-1,1]; Vulkan expects [0,1].
     * Remap so stored depth matches GL window depth (ndc*0.5+0.5). */
    gl_Position.z = (gl_Position.z + gl_Position.w) * 0.5;
}
