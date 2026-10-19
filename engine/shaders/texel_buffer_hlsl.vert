// texel_buffer_hlsl.vert -- test-only VS proving rhi_cmd_bind_texel_buffers
// works on D3D12 (see that function's header for why it was a stub).
//
// The engine's real consumer is instanced.vert, which fetches an 8-vec4
// instance row with texelFetch(u_instances, gl_InstanceID * 8 + k). This
// reproducer keeps the same shape -- a StructuredBuffer<float4> at t5 read
// per instance -- but drops the transform, because what is under test is the
// descriptor, not the matrix path. Position comes straight from POSITION.xy
// so the expected pixels can be stated exactly.
StructuredBuffer<float4> g_rows : register(t5, space0);

struct VSOut { float4 pos : SV_Position; float3 tint : TEXCOORD0; };
VSOut main(float3 pos : POSITION, uint inst : SV_InstanceID) {
    VSOut o;
    o.pos = float4(pos.xy, 0.0f, 1.0f);
    o.tint = g_rows[inst].xyz;
    return o;
}
