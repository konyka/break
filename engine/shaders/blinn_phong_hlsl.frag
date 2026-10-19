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
// R621 -- shared clip.z convention for every D3D12 forward sidecar.
// mat4_perspective in src/math/math.c is the OpenGL form (NDC z in [-1,1]).
// GL's depth range maps that to [0,1] in fixed function; every Vulkan forward
// twin converts in the shader instead (blinn_phong_vk.vert R214-A, and the
// same line in terrain_vk / water_vk / blinn_phong_arr_vk); D3D12's NDC is
// [0,1] natively, so a D3D12 forward vertex stage MUST do the same line.
// Until R621 none of them did, which meant two things on this backend:
//
//   - everything with ndc_z < 0 was clipped by the rasteriser. At the demo's
//     near 0.1 / far 100 that is eye distance 0.1 to about 0.2 -- a thin band
//     right against the camera, easy to miss on a wide shot;
//   - the depth buffer held raw ndc_z instead of (ndc_z + 1) / 2, so every
//     post pass that decodes scene depth (dof, ssr, ssao, contact shadow)
//     reconstructed the wrong distance.
//
// Both are fixed by one line in each forward vertex shader. Post-process and
// fullscreen-triangle shaders are unaffected: post_hlsl.vert and skybox write
// a literal z of 1 with w of 1, where the conversion is the identity.
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
