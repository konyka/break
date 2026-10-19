// texel_buffer_hlsl.frag -- test-only PS for the rhi_cmd_bind_texel_buffers
// proof. Writes the vertex stage's per-instance tint straight out, so a
// missing or mis-strided descriptor shows up as the wrong colour rather than
// as a subtle shading difference.
struct PSOut { float4 color : SV_Target0; };
PSOut main(float4 pos : SV_Position, float3 tint : TEXCOORD0) {
    PSOut o;
    o.color = float4(tint, 1.0f);
    return o;
}
