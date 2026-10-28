// particle_mrt_hlsl.vert - D3D12 sidecar of shaders/particle.vert with
// FORWARD_MRT (the only variant the engine builds).
//
// D3D12 has no gl_PointSize: a POINTLIST draw rasterises one pixel per
// point. So each particle is a six-vertex quad instead (two triangles, the
// host writes vertexCount = 6 into the DrawBuf), expanded here around the
// particle's clip position to the same pixel size the GLSL asks for,
// max(1, size * 400 / w), using the target size in u_viewport. uv plays
// gl_PointCoord's role for the fragment mask.
//
// u_prev_vp is in the push block rather than the GLSL ForwardTemporal UBO:
// the engine binds that UBO at binding 0, which on D3D12 is the reserved
// root-constant register, so it can never reach this stage. Two SRV tables
// leave 62 DWORDs; view + proj + prev_vp + viewport is 50.
struct PushConsts {
    float4x4 u_view;      //   0
    float4x4 u_proj;      //  64
    float4x4 u_prev_vp;   // 128
    float2   u_viewport;  // 192
};                        // tail at 200
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_view 0
// rhi:uniform u_proj 64
// rhi:uniform u_prev_vp 128
// rhi:uniform u_viewport 192
StructuredBuffer<float4> g_particles : register(t0);
ByteAddressBuffer        g_draw      : register(t1);

struct VSOut {
    float4 pos : SV_Position;
    float4 color : COLOR0;
    float2 uv : TEXCOORD0;
    float2 velocity : TEXCOORD1;
};

VSOut main(uint vid : SV_VertexID, uint inst : SV_InstanceID) {
    static const float2 k_corner[6] = {
        float2(-1, -1), float2(1, -1), float2(1, 1),
        float2(-1, -1), float2(1, 1), float2(-1, 1)
    };
    VSOut o;
    o.pos = float4(0, 0, 0, 0);
    o.color = float4(0, 0, 0, 0);
    o.uv = float2(0, 0);
    o.velocity = float2(0, 0);
    uint n, stride;
    g_particles.GetDimensions(n, stride);
    if (inst >= g_draw.Load(4u)) return o;
    uint idx = g_draw.Load(16u + inst * 4u);
    if (idx >= n / 4u) return o;
    float4 pos_life = g_particles[idx * 4u + 0u];
    float4 size_color = g_particles[idx * 4u + 2u];
    float4 previous_pos = g_particles[idx * 4u + 3u];
    if (pos_life.w <= 0.0) return o;

    float size = size_color.x;
    float alpha = size_color.w;
    float3 color = size_color.yzw;
    float4 current_clip = mul(g_push.u_proj, mul(g_push.u_view, float4(pos_life.xyz, 1.0)));
    float point_px = max(1.0, size * 400.0 / current_clip.w);
    float2 corner = k_corner[vid % 6u];
    o.pos = current_clip;
    o.pos.xy += corner * (point_px / g_push.u_viewport) * current_clip.w;
    o.pos.z = (current_clip.z + current_clip.w) * 0.5;
    o.color = float4(color * alpha, alpha);
    o.uv = corner * 0.5 + 0.5;
    float4 previous_clip = mul(g_push.u_prev_vp, float4(previous_pos.xyz, 1.0));
    o.velocity = current_clip.xy / current_clip.w - previous_clip.xy / previous_clip.w;
    return o;
}
