#version 450 core

uniform mat4 u_inv_proj;
uniform mat4 u_view;

out vec3 v_ray_dir;

const vec2 POS[3] = vec2[3](
    vec2(-1.0, -1.0),
    vec2( 3.0, -1.0),
    vec2(-1.0,  3.0)
);

void main() {
    vec2 p = POS[gl_VertexID];
    gl_Position = vec4(p, 1.0, 1.0);

    vec4 ray_clip = vec4(p, 1.0, 1.0);
    vec4 ray_eye = u_inv_proj * ray_clip;
    ray_eye = vec4(ray_eye.xy, -1.0, 0.0);
    vec3 ray_world = mat3(u_view) * ray_eye.xyz;
    v_ray_dir = normalize(ray_world);
}
