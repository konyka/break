// blinn_phong_hlsl.frag - blinn_phong forward PS (D3D12 hand-authored
// sidecar). Twin of shaders/blinn_phong.frag. The root-constant struct is
// declared byte-identically to the vertex sidecar (one shared block); only
// the markers this stage actually reads are published here. Sampled
// Texture2D tN pairs with SamplerState sN - the root-signature generator
// emits the SRV range plus the matching static sampler.
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
// position left the push block. No rhi:uniform marker for it — it is not a
// push member, so rhi_pipeline_bindings_resolve("u_camera_pos") must -1 and
// a dropped write cannot masquerade as a successful one.
struct ForwardTemporal {
    float3   u_camera_pos;  //  0 (16B slot)
    float    _cam_pad;      // 12
    float4x4 u_prev_vp;     // 16
    float4x4 u_prev_model;  // 80
};
ConstantBuffer<ForwardTemporal> g_temporal : register(b1, space0);

Texture2D g_albedo : register(t0, space0);   // sampler2D u_albedo
SamplerState g_smp : register(s0, space0);   // static sampler for t0
float4 main(float4 pos : SV_Position, float3 world : TEXCOORD0,
            float3 normal : TEXCOORD1, float2 uv : TEXCOORD2) : SV_Target {
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
    return float4(color, 1.0);
}
