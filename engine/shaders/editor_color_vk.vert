#version 450 core

/* Vulkan variant of editor_color.vert: uniforms arrive via the push-constant
 * block (rhi_cmd_set_uniform_mat4/vec4 write byte offsets into it). The
 * editor camera projection is GL-style (clip z in [-1,1]); remap to
 * Vulkan's [0,1] like blinn_phong_vk.vert (R214-A). */

layout(location = 0) in vec3 aPos;

layout(push_constant) uniform PushConstants {
    mat4 u_mvp;
    vec4 u_color;
} pc;

void main() {
    gl_Position = pc.u_mvp * vec4(aPos, 1.0);
    /* OpenGL proj -> Vulkan clip.z [0,1]. */
    gl_Position.z = (gl_Position.z + gl_Position.w) * 0.5;
}
