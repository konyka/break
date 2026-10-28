// skinned_mrt_lodfade_hlsl.frag - R707c LOD cross-fade twin of
// skinned_mrt_hlsl.frag (D3D12). Identical except for the 4x4 Bayer dither
// discard driven by skinned_mrt_lodfade_hlsl.vert's TEXCOORD4. Keep the two
// in sync.
//
// skinned_mrt_hlsl.frag - skinned PS, MRT (D3D12 hand-authored sidecar of
// shaders/skinned.frag, the GL variant).
//
// Lighting is read from the temporal CBV rather than written per draw; see
// skinned_mrt_hlsl.vert for the reasoning, and R632 for the same move on the
// instanced pass. The layout below is the engine's ForwardTemporalUbo byte for
// byte. The albedo texture is register t0 because the material binder puts it
// there, the same slot every other forward pass uses.
struct ForwardTemporal {
    float3   u_camera_pos;     //   0
    float    _cam_pad;         //  12
    float4x4 u_prev_vp;        //  16
    float4x4 u_prev_model;     //  80
    float3   light_dir;        // 144
    float    _light_dir_pad;   // 156
    float3   light_color;      // 160
    float    _light_color_pad; // 172
    float3   ambient;          // 176
    float    _ambient_pad;     // 188
};
ConstantBuffer<ForwardTemporal> g_temporal : register(b1, space0);

Texture2D g_albedo : register(t0, space0);
SamplerState g_smp : register(s0, space0);

struct PSOut {
    float4 color : SV_Target0;
    float2 velocity : SV_Target1;   // GLSL layout(location = 1)
};
// Runtime LOD cross-fade (R703a): lod_fade = +k keeps the pixels whose 4x4
// Bayer threshold + 0.5 is <= k (finer level), -k keeps those >= k (coarser
// level), 0 keeps everything; the two draws of a fading mesh cover
// complementary pixels. Mirrors lod_fade_keep() in renderer/lod.c.
static const float k_lod_bayer[16] = { 0.0f, 8.0f, 2.0f, 10.0f, 12.0f, 4.0f, 14.0f, 6.0f,
                                       3.0f, 11.0f, 1.0f, 9.0f, 15.0f, 7.0f, 13.0f, 5.0f };
bool lod_fade_discard(float4 frag_pos, float fade) {
    if (fade == 0.0f) return false;
    uint2 p = uint2(frag_pos.xy) & 3u;
    float b = k_lod_bayer[p.y * 4u + p.x] + 0.5f;
    return fade > 0.0f ? (b > fade) : (b < -fade);
}

PSOut main(float4 pos : SV_Position, float3 vWorldPos : TEXCOORD0,
           float3 vNormal : TEXCOORD1, float2 vUV : TEXCOORD2,
           float2 velocity : TEXCOORD3,
           nointerpolation float lod_fade : TEXCOORD4) {
    if (lod_fade_discard(pos, lod_fade)) discard;
    float3 N = normalize(vNormal);
    // R96-3: u_light_dir is pre-normalized on the CPU.
    float3 L = (-g_temporal.light_dir);
    float3 V = normalize(g_temporal.u_camera_pos - vWorldPos);
    float3 H = normalize(L + V);

    float diff = max(dot(N, L), 0.0f);
    float spec = max(dot(N, H), 0.0f);
    spec *= spec; spec *= spec; spec *= spec; spec *= spec; spec *= spec;

    float3 albedo = g_albedo.Sample(g_smp, vUV).rgb;
    float3 color = g_temporal.ambient * albedo +
                   g_temporal.light_color * (diff + spec * 0.15f) * albedo;

    PSOut o;
    o.color = float4(color, 1.0f);
    o.velocity = velocity;
    return o;
}
