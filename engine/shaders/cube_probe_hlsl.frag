// cube_probe_hlsl.frag - test-only PS for the point-shadow cube round trip
// (test_d3d12_warp_runtime). Paired with shadow_sample_hlsl.vert.
//
// Reads face u_face.x of the cube on t10 back by DIRECTION, the way the
// lighting pass does: the pixel's uv is the face-space (s, t) and the
// direction is rebuilt from the cube addressing rule (major axis = the
// face), so a face rendered rotated or mirrored reads back the wrong texel.
// Output .r = the stored depth.
struct PushConsts {
    float4x4 u_transform;
    float4   u_face;      // x = face index 0..5
};
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_transform 0
// rhi:uniform u_face 64
TextureCube g_cube : register(t10, space0);
SamplerState g_smp : register(s10, space0);
float4 main(float4 pos : SV_Position, float2 uv : TEXCOORD0) : SV_Target {
    float a = uv.x * 2.0 - 1.0;
    float b = uv.y * 2.0 - 1.0;
    int f = (int)g_push.u_face.x;
    float3 d;
    if (f == 0)      d = float3( 1.0, -b, -a);
    else if (f == 1) d = float3(-1.0, -b,  a);
    else if (f == 2) d = float3( a,  1.0,  b);
    else if (f == 3) d = float3( a, -1.0, -b);
    else if (f == 4) d = float3( a, -b,  1.0);
    else             d = float3(-a, -b, -1.0);
    float depth = g_cube.Sample(g_smp, d).r;
    return float4(depth, depth, depth, 1.0);
}
