// probe_vb_hlsl.vert - push-constant probe sidecar.
// POSITION-only vertex input plus a root-constant transform. The quad is
// authored directly in NDC, so it only rasterises if u_transform actually
// reached the shader: a dropped/zeroed constant collapses every vertex onto
// the origin and the triangles degenerate. No texture, no descriptor table.
struct PushConsts { float4x4 u_transform; };
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_transform 0
struct VSOut { float4 pos : SV_Position; };
VSOut main(float3 pos : POSITION) {
    VSOut o;
    o.pos = mul(g_push.u_transform, float4(pos, 1.0));
    return o;
}
