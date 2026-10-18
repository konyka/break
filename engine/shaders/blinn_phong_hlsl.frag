// blinn_phong_hlsl.frag - blinn_phong forward PS (D3D12 hand-authored
// sidecar). Twin of shaders/blinn_phong.frag. The root-constant struct is
// declared byte-identically to the vertex sidecar (one shared 256B block);
// only the markers this stage actually reads are published here. Sampled
// Texture2D tN pairs with SamplerState sN - the root-signature generator
// emits the SRV range plus the matching static sampler.
struct PushConsts {
    float4x4 u_model;       //   0
    float4x4 u_view;        //  64
    float4x4 u_proj;        // 128
    float3   u_light_dir;   // 192 (16B slot)
    float3   u_light_color; // 208
    float3   u_ambient;     // 224
    float3   u_camera_pos;  // 240
};
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_light_dir 192
// rhi:uniform u_light_color 208
// rhi:uniform u_ambient 224
// rhi:uniform u_camera_pos 240
Texture2D g_albedo : register(t0, space0);   // sampler2D u_albedo
SamplerState g_smp : register(s0, space0);   // static sampler for t0
float4 main(float4 pos : SV_Position, float3 world : TEXCOORD0,
            float3 normal : TEXCOORD1, float2 uv : TEXCOORD2) : SV_Target {
    float3 N = normalize(normal);
    // R96-3: u_light_dir pre-normalized on CPU.
    float3 L = (-g_push.u_light_dir);
    float3 V = normalize(g_push.u_camera_pos - world);
    float3 H = normalize(L + V);

    float diff = max(dot(N, L), 0.0);
    float spec = max(dot(N, H), 0.0);
    spec *= spec; spec *= spec; spec *= spec; spec *= spec; spec *= spec;

    float3 albedo = g_albedo.Sample(g_smp, uv).rgb;
    float3 color = albedo * (g_push.u_ambient + g_push.u_light_color * diff)
                 + g_push.u_light_color * spec * 0.15;
    return float4(color, 1.0);
}
