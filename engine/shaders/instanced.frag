#version 450 core

layout(location = 0) in vec3 vWorldPos;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vUV;
#ifdef FORWARD_MRT
layout(location = 3) in vec2 v_velocity;
#endif

uniform vec3 u_light_dir;
uniform vec3 u_light_color;
uniform vec3 u_ambient;
uniform vec3 u_camera_pos;

layout(binding = 0) uniform sampler2D u_albedo;

layout(location = 0) out vec4 FragColor;
#ifdef FORWARD_MRT
layout(location = 1) out vec2 out_velocity;
#endif
#ifdef LOD_FADE
flat in float vLodFade;
/* Runtime LOD cross-fade (R703a): vLodFade = +k keeps the pixels whose 4x4
 * Bayer threshold + 0.5 is <= k (finer level), -k keeps those >= k (coarser
 * level), 0 keeps everything; the two draws of a fading instance cover
 * complementary pixels. Mirrors lod_fade_keep() in renderer/lod.c. */
bool lod_fade_discard(float fade) {
    if (fade == 0.0) return false;
    const float bayer[16] = float[16](0.0, 8.0, 2.0, 10.0, 12.0, 4.0, 14.0, 6.0,
                                      3.0, 11.0, 1.0, 9.0, 15.0, 7.0, 13.0, 5.0);
    ivec2 p = ivec2(gl_FragCoord.xy) & 3;
    float b = bayer[p.y * 4 + p.x] + 0.5;
    return fade > 0.0 ? (b > fade) : (b < -fade);
}
#endif

void main() {
#ifdef LOD_FADE
    if (lod_fade_discard(vLodFade)) discard;
#endif
    vec3 N = normalize(vNormal);
    vec3 L = (-u_light_dir)  /* R96-3: u_light_dir pre-normalized on CPU */;
    vec3 V = normalize(u_camera_pos - vWorldPos);
    vec3 H = normalize(L + V);

    float diff = max(dot(N, L), 0.0);
    float spec = max(dot(N, H), 0.0); spec *= spec; spec *= spec; spec *= spec; spec *= spec; spec *= spec;
    vec3 albedo = texture(u_albedo, vUV).rgb;

    vec3 color = u_ambient * albedo + u_light_color * (diff + spec * 0.15) * albedo;
    FragColor = vec4(color, 1.0);
#ifdef FORWARD_MRT
    out_velocity = v_velocity;
#endif
}
