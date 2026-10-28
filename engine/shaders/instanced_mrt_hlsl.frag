// instanced_mrt_hlsl.frag - instanced PS, MRT (D3D12 hand-authored sidecar of
// shaders/instanced.frag, the GL variant).
//
// The GLSL twin keeps u_light_dir / u_light_color / u_ambient /
// u_camera_pos as loose fragment uniforms. They are read from the temporal
// CBV here instead, because on D3D12 rhi_cmd_set_uniform_* only reaches root
// constants and this pipeline's six push-block words plus two mat4 already
// overflow the 244-byte ceiling two descriptor tables leave (R616). The CBV
// layout is the engine's ForwardTemporalUbo byte for byte; see
// instanced_mrt_hlsl.vert for why the members sit where they do.
//
// The albedo texture is register t0 because the material binder puts it
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
PSOut main(float4 pos : SV_Position, float3 vWorldPos : TEXCOORD0,
           float3 vNormal : TEXCOORD1, float2 vUV : TEXCOORD2,
           float2 velocity : TEXCOORD3) {
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
