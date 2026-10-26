#version 450 core

in vec3 vWorldPos;
in vec3 vNormal;
in vec2 vUV;
#ifdef FORWARD_MRT
in vec2 v_velocity;
#endif


/* R600: the temporal block is UNCONDITIONAL and leads with the camera
 * position. It used to be FORWARD_MRT-only, which is what forced
 * u_camera_pos into the base block even though only the MRT path wanted
 * the matrices. A D3D12 sidecar that adds the temporal CBV pays a whole
 * DWORD of the 64-DWORD root-signature budget, clamping the declared push
 * range from 252 to 248 bytes and dropping u_camera_pos@240+12=252 on the
 * floor. Leading with the camera keeps the read self-consistent if the
 * buffer is ever rebound stale, the rule the matrices already follow
 * (R589). */
layout(std140, binding = 0) uniform ForwardTemporal {
    vec3 u_camera_pos;
    float _cam_pad;
    mat4 u_prev_vp;
    mat4 u_prev_model;
} temporal;

uniform vec3 u_light_dir;
uniform vec3 u_light_color;
uniform vec3 u_ambient;

uniform sampler2D u_albedo;

layout(location = 0) out vec4 FragColor;
#ifdef FORWARD_MRT
layout(location = 1) out vec2 out_velocity;
#endif

#ifdef LOD_FADE
flat in float vLodFade;
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
    vec3 V = normalize(temporal.u_camera_pos - vWorldPos);
    vec3 H = normalize(L + V);

    float diff = max(dot(N, L), 0.0);
    float spec = max(dot(N, H), 0.0); spec *= spec; spec *= spec; spec *= spec; spec *= spec; spec *= spec;

    vec3 albedo = texture(u_albedo, vUV).rgb;
    vec3 color = albedo * (u_ambient + u_light_color * diff) + u_light_color * spec * 0.15;
    FragColor = vec4(color, 1.0);
#ifdef FORWARD_MRT
    out_velocity = v_velocity;
#endif
}
