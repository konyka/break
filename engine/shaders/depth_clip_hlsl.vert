// depth_clip_hlsl.vert -- R621 probe. Not a production shader: it proves the
// forward sidecars' clip.z conversion is what keeps near geometry on screen.
//
// It is the blinn_phong push block with ONE difference: u_proj is taken as
// given, and the conversion line the R621 sidecars add is applied, so a
// caller can drive it either way and compare.
//
// The point of the probe is a vertex whose clip z is NEGATIVE under the
// OpenGL projection. D3D12's rasteriser clips z < 0, so without the
// conversion that vertex vanishes; with it, z becomes 0 and the vertex
// survives. main() writes the pre-conversion sign into the colour so the
// difference is visible from the fragment side too.
struct PushConsts {
    float4x4 u_model;     //   0
    float4x4 u_view;      //  64
    float4x4 u_proj;      // 128
};
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_model 0
// rhi:uniform u_view 64
// rhi:uniform u_proj 128

struct VSOut {
    float4 pos : SV_Position;
    float3 tint : TEXCOORD0;
};
VSOut main(float3 p : POSITION) {
    VSOut o;
    float4 clip = mul(g_push.u_proj, mul(g_push.u_view, mul(g_push.u_model,
                                                            float4(p, 1.0f))));
    // R621 conversion, identical to the five forward sidecars.
    o.pos = float4(clip.xy, (clip.z + clip.w) * 0.5f, clip.w);
    // 1.0 when the un-converted ndc_z was negative (i.e. would have clipped).
    o.tint = (clip.z < 0.0f) ? float3(1.0f, 0.0f, 0.0f) : float3(0.0f, 1.0f, 0.0f);
    return o;
}
