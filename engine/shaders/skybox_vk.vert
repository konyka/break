#version 450 core

#extension GL_ARB_shader_draw_parameters : enable

layout(push_constant) uniform PushConstants {
    layout(offset = 0)  mat4 u_inv_proj;
    layout(offset = 64) mat4 u_view;
} pc;

layout(location = 0) out vec3 v_ray_dir;

vec2 POS[3] = vec2[3](
    vec2(-1.0, -1.0),
    vec2( 3.0, -1.0),
    vec2(-1.0,  3.0)
);

void main() {
    vec2 p = POS[gl_VertexIndex];
    gl_Position = vec4(p, 1.0, 1.0);

    vec4 ray_clip = vec4(p, 1.0, 1.0);
    vec4 ray_eye = pc.u_inv_proj * ray_clip;
    ray_eye = vec4(ray_eye.xy, -1.0, 0.0);
    vec3 ray_world = mat3(pc.u_view) * ray_eye.xyz;
    v_ray_dir = normalize(ray_world);
}
