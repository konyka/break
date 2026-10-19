// blinn_phong_arr_hlsl.frag - material-array blinn_phong forward PS (D3D12
// hand-authored sidecar). Twin of shaders/blinn_phong_arr.frag with FORWARD_MRT
// defined: RT0 carries the shaded colour, RT1 the screen-space motion vector,
// exactly as blinn_phong_mrt_hlsl.frag does for the non-array pair. The root-
// constant struct is declared byte-identically to the vertex sidecar (one
// shared block); only the markers this stage actually reads are published
// here. Sampled Texture2DArray tN pairs with SamplerState sN - the
// root-signature generator emits the SRV range plus the matching static
// sampler.
//
// R441: the only structural delta from blinn_phong_mrt_hlsl.frag is
// g_albedo's type. GLSL's sampler2DArray is HLSL's Texture2DArray; the layer
// arrives as nointerpolation uint vLayer, the HLSL form of GLSL's
// flat in uint vLayer, and becomes the third component of the sample
// coordinate - texture(u_albedo, vec3(vUV, float(vLayer))) line for line.
// The D3D12 SRV this binding receives is created by rhi_cmd_bind_texture,
// which selects D3D12_SRV_DIMENSION_TEXTURE2DARRAY for an array texture, so
// the register needs no extra range or dimension.
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

// R600: the temporal block; see blinn_phong_arr_hlsl.vert for why u_camera_pos
// rides the CBV instead of the push block. No rhi:uniform marker for it - it
// is not a push member, so rhi_pipeline_bindings_resolve("u_camera_pos") must
// -1 and a dropped write cannot masquerade as a successful one.
struct ForwardTemporal {
    float3   u_camera_pos;  //  0 (16B slot)
    float    _cam_pad;      // 12
    float4x4 u_prev_vp;     // 16
    float4x4 u_prev_model;  // 80
};
ConstantBuffer<ForwardTemporal> g_temporal : register(b1, space0);

Texture2DArray g_albedo : register(t0, space0);   // sampler2DArray u_albedo
SamplerState g_smp : register(s0, space0);       // static sampler for t0

struct PSOut {
    float4 color : SV_Target0;
    float2 velocity : SV_Target1;   // GLSL layout(location = 1)
};
PSOut main(float4 pos : SV_Position, float3 world : TEXCOORD0,
            float3 normal : TEXCOORD1, float2 uv : TEXCOORD2,
            float2 velocity : TEXCOORD3,
            nointerpolation uint layer : TEXCOORD4) {
    float3 N = normalize(normal);
    // R96-3: u_light_dir pre-normalized on CPU.
    float3 L = (-g_push.u_light_dir);
    float3 V = normalize(g_temporal.u_camera_pos - world);
    float3 H = normalize(L + V);

    float diff = max(dot(N, L), 0.0);
    float spec = max(dot(N, H), 0.0);
    spec *= spec; spec *= spec; spec *= spec; spec *= spec; spec *= spec;

    // GLSL: texture(u_albedo, vec3(vUV, float(vLayer))) where
    //     vLayer = uint(gl_BaseInstanceARB)
    //
    // ⚠️ KNOWN BROKEN ON D3D12 -- measured on the RTX 4060, not inferred.
    // `layer` below arrives from SV_InstanceID in the vertex stage, and
    // D3D12's SV_InstanceID does NOT include StartInstanceLocation; it is
    // gl_InstanceID, and here it runs 0..InstanceCount-1 with the base
    // dropped. Evidence: an ExecuteIndirect record with
    // StartInstanceLocation = 1, InstanceCount = 1 renders layer 0, and one
    // with StartInstanceLocation = 2, InstanceCount = 2 renders the last
    // instance's layer as 1 -- i.e. 0..1, not 2..3. Production sets
    // first_instance = array layer with InstanceCount = 1 (main.c:3779 and
    // :3947), so on D3D12 every material-array mesh currently samples layer 0.
    //
    // There is no HLSL spelling of the base instance to fix this with:
    // `SV_StartInstanceLocation` is the correct semantic and dxc rejects it
    // for every shader model from ps_6_0 to ps_6_11 ("invalid semantic ...
    // for ps 6.x"), in both the vertex and pixel stages. The bare name
    // `StartInstanceLocation` compiles but dumps as SysValue = NONE, i.e. a
    // user semantic the runtime never populates.
    //
    // The sanctioned D3D12 route is a command signature with a second
    // D3D12_INDIRECT_ARGUMENT_TYPE_CONSTANT argument, which copies the value
    // out of the argument buffer and into a root constant the shader can
    // read. There is room for it: this push block ends at 240 and two
    // descriptor tables clamp 32BIT_CONSTANTS at 62 DWORDs = 248 bytes, so
    // `uint u_layer` at 240 fits without a new root parameter. That change
    // spans the command signature, the indirect-argument ABI (the array path
    // would need 24-byte records), and this shader, so it is recorded rather
    // than attempted blind. See the R609 entry in
    // docs/superpowers/plans/2026-10-19-d3d12-forward-mrt-velocity-design-plan.md.
    float3 albedo = g_albedo.Sample(g_smp, float3(uv, (float)layer)).rgb;
    float3 color = albedo * (g_push.u_ambient + g_push.u_light_color * diff)
                 + g_push.u_light_color * spec * 0.15;

    PSOut o;
    o.color = float4(color, 1.0);
    o.velocity = velocity;
    return o;
}
