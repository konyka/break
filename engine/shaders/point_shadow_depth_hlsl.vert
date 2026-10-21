// point_shadow_depth_hlsl.vert - point-light cube depth pass, vertex stage
// (D3D12 hand-authored sidecar of shaders/point_shadow_depth.vert).
//
// u_mvp is the face view-projection only; u_model is applied first so the
// clip position and the world position the PS measures from agree (R248).
// The engine's projection is the GL one (clip z in [-w, w]); D3D12 wants
// [0, w], hence the remap, as in depth_only_hlsl.vert.
//
// Push block in the GLSL _vk twin's layout (vec4-padded light pos and far
// plane), byte-identical in the fragment sidecar.
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
struct VSOut { float4 pos : SV_Position; float3 world_pos : TEXCOORD0; };
VSOut main(float3 pos : POSITION) {
    VSOut o;
    float4 world = mul(g_push.u_model, float4(pos, 1.0));
    o.world_pos = world.xyz;
    o.pos = mul(g_push.u_mvp, world);
    o.pos.z = (o.pos.z + o.pos.w) * 0.5;
    return o;
}
