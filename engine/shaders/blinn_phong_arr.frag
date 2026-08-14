#version 450 core
/* R441: texture-array variant of blinn_phong.frag — u_albedo becomes a
 * sampler2DArray, layer selected by vLayer (flat, from gl_BaseInstanceARB).
 * Lighting math is byte-identical to blinn_phong.frag. */

in vec3 vWorldPos;
in vec3 vNormal;
in vec2 vUV;
flat in uint vLayer;
#ifdef FORWARD_MRT
in vec2 v_velocity;
#endif

uniform vec3 u_light_dir;
uniform vec3 u_light_color;
uniform vec3 u_ambient;
uniform vec3 u_camera_pos;

uniform sampler2DArray u_albedo;

layout(location = 0) out vec4 FragColor;
#ifdef FORWARD_MRT
layout(location = 1) out vec2 out_velocity;
#endif

void main() {
    vec3 N = normalize(vNormal);
    vec3 L = (-u_light_dir)  /* R96-3: u_light_dir pre-normalized on CPU */;
    vec3 V = normalize(u_camera_pos - vWorldPos);
    vec3 H = normalize(L + V);

    float diff = max(dot(N, L), 0.0);
    float spec = max(dot(N, H), 0.0); spec *= spec; spec *= spec; spec *= spec; spec *= spec; spec *= spec;

    vec3 albedo = texture(u_albedo, vec3(vUV, float(vLayer))).rgb;
    vec3 color = albedo * (u_ambient + u_light_color * diff) + u_light_color * spec * 0.15;
    FragColor = vec4(color, 1.0);
#ifdef FORWARD_MRT
    out_velocity = v_velocity;
#endif
}
