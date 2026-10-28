// depth_clip_hlsl.frag -- R621 probe fragment stage; writes the vertex stage's
// pre-conversion sign straight out so the test can see red (ndc_z < 0, would
// have been clipped without R621) or green (ndc_z >= 0).
struct PSOut { float4 color : SV_Target0; };
PSOut main(float4 pos : SV_Position, float3 tint : TEXCOORD0) {
    PSOut o;
    o.color = float4(tint, 1.0f);
    return o;
}
