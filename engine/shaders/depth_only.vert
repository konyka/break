#version 450 core

/* Shadow / depth-only vertex stage. Shared by both backends: Vulkan uses a
 * push-constant block, desktop GL uses loose uniforms with the same names so
 * the host's rhi_pipeline_get_uniform_location("u_model"/"u_light_vp") resolves
 * on either backend. */
#ifdef VULKAN
layout(push_constant) uniform PushConstants {
    mat4 u_model;
    mat4 u_light_vp;
} pc;
#define U_MODEL    pc.u_model
#define U_LIGHT_VP pc.u_light_vp
#else
uniform mat4 u_model;
uniform mat4 u_light_vp;
#define U_MODEL    u_model
#define U_LIGHT_VP u_light_vp
#endif

layout(location = 0) in vec3 a_pos;

void main() {
    gl_Position = U_LIGHT_VP * U_MODEL * vec4(a_pos, 1.0);
#ifdef VULKAN
    /* R213-A: OpenGL ortho → clip.z∈[-1,1]; Vulkan expects [0,1].
     * Matches R211 intent (legacy unused shadow_depth_vk.vert removed in R223-B). */
    gl_Position.z = (gl_Position.z + gl_Position.w) * 0.5;
#endif
}
