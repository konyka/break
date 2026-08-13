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
    // R438: view is now canonical (rows = basis); eye->world needs R^T.
    vec3 ray_world = transpose(mat3(u_view)) * ray_eye.xyz;
    /* R551-E: do NOT normalize here — the fragment shader normalizes.
     * Normalizing per-vertex makes the interpolated direction field a
     * distorted (barycentric-on-the-sphere) remap of the true ray field:
     * across the huge fullscreen triangle it shifted the sun disc ~26
     * degrees in azimuth away from its projected position. The raw ray is
     * linear in NDC (w=1), so interpolation reproduces it exactly. */
    v_ray_dir = ray_world;
}
