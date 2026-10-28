// blinn_phong_mrt_hlsl.frag - blinn_phong forward PS, FORWARD_MRT variant
// (D3D12 hand-authored sidecar). The GLSL twin is shaders/blinn_phong.frag
// with FORWARD_MRT defined: RT0 carries the shaded colour, RT1 the screen
// -space motion vector. Push block and temporal CBV are byte-identical to
// blinn_phong_hlsl.{vert,frag}.
struct PushConsts {
    float4x4 u_model;       //   0
    float4x4 u_view;        //  64
    float4x4 u_proj;        // 128
    float3   u_light_dir;   // 192 (16B slot)
    float3   u_light_color; // 208
    float3   u_ambient;     // 224
};                          // tail ends at 240
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_light_dir 192
// rhi:uniform u_light_color 208
// rhi:uniform u_ambient 224

// R600: the temporal block; see blinn_phong_hlsl.vert for why the camera
// position left the push block.
struct ForwardTemporal {
    float3   u_camera_pos;  //  0 (16B slot)
    float    _cam_pad;      // 12
    float4x4 u_prev_vp;     // 16
    float4x4 u_prev_model;  // 80
};
ConstantBuffer<ForwardTemporal> g_temporal : register(b1, space0);

Texture2D g_albedo : register(t0, space0);   // sampler2D u_albedo
SamplerState g_smp : register(s0, space0);   // static sampler for t0

struct PSOut {
    float4 color : SV_Target0;
    float2 velocity : SV_Target1;   // GLSL layout(location = 1)
};
static const float k_lod_bayer[16] = { 0.0f, 8.0f, 2.0f, 10.0f, 12.0f, 4.0f, 14.0f, 6.0f,
                                       3.0f, 11.0f, 1.0f, 9.0f, 15.0f, 7.0f, 13.0f, 5.0f };
bool lod_fade_discard(float4 frag_pos, float fade) {
    if (fade == 0.0f) return false;
    uint2 p = uint2(frag_pos.xy) & 3u;
    float b = k_lod_bayer[p.y * 4u + p.x] + 0.5f;
    return fade > 0.0f ? (b > fade) : (b < -fade);
}
PSOut main(float4 pos : SV_Position, float3 world : TEXCOORD0,
            float3 normal : TEXCOORD1, float2 uv : TEXCOORD2,
            float2 velocity : TEXCOORD3,
            nointerpolation float lod_fade : TEXCOORD4) {
    if (lod_fade_discard(pos, lod_fade)) discard;
    float3 N = normalize(normal);
    // R96-3: u_light_dir pre-normalized on CPU.
    float3 L = (-g_push.u_light_dir);
    float3 V = normalize(g_temporal.u_camera_pos - world);
    float3 H = normalize(L + V);

    float diff = max(dot(N, L), 0.0);
    float spec = max(dot(N, H), 0.0);
    spec *= spec; spec *= spec; spec *= spec; spec *= spec; spec *= spec;

    float3 albedo = g_albedo.Sample(g_smp, uv).rgb;
    float3 color = albedo * (g_push.u_ambient + g_push.u_light_color * diff)
                 + g_push.u_light_color * spec * 0.15;

    PSOut o;
    o.color = float4(color, 1.0);
    o.velocity = velocity;
    return o;
}
