// shadow_depth_hlsl.vert — depth-only VS for the shadow-atlas test (D3D12
// hand-authored sidecar, matching the probe/blit sidecars).
//
// The quad is authored directly in NDC and placed by the root constant, so it
// only covers the intended region if u_transform really reached the shader.
// POSITION-only input, SV_Position only out: the pipeline is built with
// is_shadow_depth, which drops every render target.
struct PushConsts { float4x4 u_transform; };
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_transform 0
struct VSOut { float4 pos : SV_Position; };
VSOut main(float3 pos : POSITION) {
    VSOut o;
    o.pos = mul(g_push.u_transform, float4(pos, 1.0));
    return o;
}
