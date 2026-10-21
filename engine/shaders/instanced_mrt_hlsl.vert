// instanced_mrt_hlsl.vert - instanced VS (D3D12 hand-authored sidecar of
// shaders/instanced.vert, the GL variant -- not instanced_vk.vert).
//
// The interesting part is where the lighting uniforms live. The GLSL twin
// keeps u_light_dir / u_light_color / u_ambient / u_camera_pos as loose
// uniforms in the FRAGMENT stage and the instanced VERTEX block holds only
// {u_prev_vp, u_prev_model_unused}, inside #ifdef FORWARD_MRT. On D3D12 that
// shape does not work:
//
//   - rhi_cmd_set_uniform_* only writes root constants, so every uniform the
//     engine sets per draw has to be in the push block. Six words plus two
//     mat4 is 320 bytes, and two descriptor tables clamp the root constants
//     at 244 (R616).
//   - Making the temporal block unconditional, as R600 did for blinn_phong,
//     would force a UBO bind on every draw for a value only the MRT path
//     reads. R600's header warns about exactly that.
//
// So the lighting uniforms move INTO the temporal block, appended after
// prev_model so the blinn_phong family's u_camera_pos@0 and u_prev_vp@16
// keep their offsets. That block is the engine's ForwardTemporalUbo, byte for
// byte -- main.c owns the layout and this file mirrors it. The three vec3s
// carry an explicit pad word each because a cbuffer float3 occupies 16 bytes;
// without them the offsets would not match the engine struct.
//
// u_prev_model_unused is deliberately absent: instanced.vert reads the
// per-instance previous model from the instance buffer at texelFetch
// idx + 4 .. idx + 7, so the UBO's copy really is unused.
//
// Register note: the instance rows arrive through rhi_cmd_bind_texel_buffers
// at unit 5 (R103-1, matching the GLSL binding = 5), which the backend binds
// as an SRV at t5.
struct PushConsts {
    float4x4 u_view;   //   0
    float4x4 u_proj;   //  64
};                    // tail at 128
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_view 0
// rhi:uniform u_proj 64

// Byte-identical to ForwardTemporalUbo in main.c.
struct ForwardTemporal {
    float3   u_camera_pos;  //   0
    float    _cam_pad;      //  12
    float4x4 u_prev_vp;     //  16
    float4x4 u_prev_model;  //  80
    float3   light_dir;     // 144
    float    _light_dir_pad;   // 156
    float3   light_color;   // 160
    float    _light_color_pad; // 172
    float3   ambient;       // 176
    float    _ambient_pad;     // 188
};                          // tail at 192
ConstantBuffer<ForwardTemporal> g_temporal : register(b1, space0);

StructuredBuffer<float4> g_rows : register(t5, space0);

struct VSOut {
    float4 pos : SV_Position;
    float3 world : TEXCOORD0;
    float3 normal : TEXCOORD1;
    float2 uv : TEXCOORD2;
    float2 velocity : TEXCOORD3;
};
VSOut main(float3 aPos : POSITION, float3 aNormal : NORMAL,
           float2 aUV : TEXCOORD0, uint inst : SV_InstanceID) {
    VSOut o;
    int idx = (int)inst * 8;
    float4 r0 = g_rows[idx + 0];
    float4 r1 = g_rows[idx + 1];
    float4 r2 = g_rows[idx + 2];
    float4 r3 = g_rows[idx + 3];
    // The rows are COLUMNS: the engine uploads column-major mat4s (translation
    // in r3.xyz), and GLSL's mat4(r0, r1, r2, r3) consumes its arguments as
    // columns. HLSL's float4x4(...) consumes them as ROWS, so it must be
    // transposed to be the same matrix. Without it the translation lands in
    // the bottom (projective) row and every translated instance is a sliver
    // stretched across the screen -- R638's demo showed exactly that. The
    // pre-R638 test only ever used identity, which is its own transpose.
    float4x4 model = transpose(float4x4(r0, r1, r2, r3));

    float4 world_pos = mul(model, float4(aPos, 1.0f));
    o.world = world_pos.xyz;
    o.normal = mul((float3x3)model, aNormal);
    o.uv = aUV;
    float4 curr_clip = mul(g_push.u_proj, mul(g_push.u_view, world_pos));
    // FORWARD_MRT: the per-instance previous model comes from the instance
    // buffer, not the UBO -- GLSL indexes idx + 4 .. idx + 7.
    float4 p0 = g_rows[idx + 4];
    float4 p1 = g_rows[idx + 5];
    float4 p2 = g_rows[idx + 6];
    float4 p3 = g_rows[idx + 7];
    float4x4 prev_model = transpose(float4x4(p0, p1, p2, p3));
    float4 prev_clip = mul(g_temporal.u_prev_vp,
                           mul(prev_model, float4(aPos, 1.0f)));
    o.velocity = curr_clip.xy / curr_clip.w - prev_clip.xy / prev_clip.w;
    o.pos = curr_clip;
    // R621: OpenGL proj -> D3D12 clip.z [0,1], matching instanced_vk.vert.
    o.pos.z = (o.pos.z + o.pos.w) * 0.5f;
    return o;
}
