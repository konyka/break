// blit_hlsl.vert — swapchain blit VS (D3D12 hand-authored sidecar, plan D
// Task 6 decision record: no GLSL translation). b0 is reserved for the
// 32BIT_CONSTANTS root-constant param (Task 5 review handoff): no other CBV
// may claim b0 or root-signature serialization fails closed.
struct PushConsts { float4x4 u_transform; };
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_transform 0
struct VSOut { float4 pos : SV_Position; float2 uv : TEXCOORD0; };
VSOut main(uint vid : SV_VertexID) {
    // Oversized triangle covers the complete target with three vertices.
    float2 p = float2((float)(vid & 1u) * 4.0 - 1.0,
                      (float)(vid >> 1u) * 4.0 - 1.0);
    VSOut o;
    o.pos = mul(g_push.u_transform, float4(p, 0.0, 1.0));
    o.uv = p * 0.5 + 0.5;
    return o;
}
