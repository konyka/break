// blinn_phong_hlsl.vert - blinn_phong forward VS (D3D12 hand-authored sidecar).
// Twin of shaders/blinn_phong.vert; semantics match RHIPipelineDesc's default
// mesh layout (POSITION/NORMAL/TEXCOORD0, 32B stride). b0 is the reserved
// 32BIT_CONSTANTS root-constant register: the struct below is declared
// byte-identically in the fragment sidecar so both stages read one 256B block.
// FORWARD_MRT (u_prev_vp/u_prev_model, v_velocity) is deliberately omitted -
// that variant is the separate MRT FBO plan, and its extra 128B UBO does not
// fit beside the seven base uniforms in the 256B graphics push range.
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
// rhi:uniform u_model 0
// rhi:uniform u_view 64
// rhi:uniform u_proj 128
struct VSIn {
    float3 pos : POSITION;   // aPos    float3 @ 0
    float3 normal : NORMAL;  // aNormal float3 @ 12
    float2 uv : TEXCOORD0;   // aUV     float2 @ 24
};
struct VSOut {
    float4 pos : SV_Position;
    float3 world : TEXCOORD0;
    float3 normal : TEXCOORD1;
    float2 uv : TEXCOORD2;
};
VSOut main(VSIn i) {
    VSOut o;
    float4 world_pos = mul(g_push.u_model, float4(i.pos, 1.0));
    o.world = world_pos.xyz;
    // GLSL: mat3(u_model) * aNormal - upper-left 3x3, no inverse-transpose.
    o.normal = mul((float3x3)g_push.u_model, i.normal);
    o.uv = i.uv;
    o.pos = mul(mul(g_push.u_proj, g_push.u_view), world_pos);
    return o;
}
