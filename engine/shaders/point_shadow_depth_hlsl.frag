// point_shadow_depth_hlsl.frag - point-light cube depth pass, pixel stage
// (D3D12 hand-authored sidecar of shaders/point_shadow_depth.frag).
//
// Stores linear distance to the light over the far plane, not the
// rasterised depth: the lighting pass compares length(frag - light) / far
// against texture(cube, frag - light).r.
struct PushConsts {
    float4x4 u_model;       //   0
    float4x4 u_mvp;         //  64
    float4   u_light_pos;   // 128 (xyz)
    float4   u_far_plane;   // 144 (x)
};                          // tail at 160
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_model 0
// rhi:uniform u_mvp 64
// rhi:uniform u_light_pos 128
// rhi:uniform u_far_plane 144
float main(float4 pos : SV_Position, float3 world_pos : TEXCOORD0) : SV_Depth {
    float dist = length(world_pos - g_push.u_light_pos.xyz);
    return saturate(dist / max(g_push.u_far_plane.x, 0.0001));
}
