// pbr_clustered_inst_hlsl.vert - clustered forward PBR, INSTANCED vertex
// stage (D3D12 hand-authored sidecar of shaders/pbr_clustered_inst.vert,
// FORWARD_MRT variant). Shares pbr_clustered_hlsl.frag with the static
// variant, so PushConsts and ClusterFrame are declared byte-identically to
// pbr_clustered_hlsl.vert; u_model is part of that block but unused here (the
// model matrix is per instance).
//
// Instances ride a structured buffer, as on GL, where they are the vertex
// SSBO at storage binding 0. D3D12 cannot put it at t0: the shared pixel
// stage owns t0-t15 (albedo ... occlusion), so the rows are at t16, and
// main.c binds them with rhi_cmd_bind_storage_buffer(cmd, buf, 16) -- the
// storage binder resolves a readonly buffer to the SRV at that register.
// Eight float4 per instance: the model matrix as four COLUMNS, then the
// previous model as four COLUMNS (the engine uploads column-major mat4s and
// GLSL's mat4(c0..c3) takes columns; HLSL's float4x4(...) takes rows, hence
// the transpose, as in instanced_mrt_hlsl.vert).
struct PushConsts {
    float4x4 u_model;              //   0 (unused here)
    float4x4 u_view;               //  64
    float2   u_mr_factor;          // 128
    float    u_occlusion_strength; // 136
    float3   u_emissive_factor;    // 144
};                                 // tail at 156
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_model 0
// rhi:uniform u_view 64

struct ClusterFrame {
    float4x4 prev_vp;              //   0
    float4x4 prev_model;           //  64
    float4x4 proj;                 // 128
    float4   camera_pos;           // 192
    float4   ambient;              // 208
    float4   fog_color;            // 224
    float4   fog;                  // 240
    float4   screen;               // 256
    float4   counts;               // 272
    float4   far_planes;           // 288
};                                 // tail at 304
ConstantBuffer<ClusterFrame> g_frame : register(b1, space0);

StructuredBuffer<float4> g_rows : register(t16, space0);

struct VSOut {
    float4 pos : SV_Position;
    float3 world : TEXCOORD0;
    float3 normal : TEXCOORD1;
    float2 uv : TEXCOORD2;
    float2 velocity : TEXCOORD3;
};

VSOut main(float3 aPos : POSITION, float3 aNormal : NORMAL,
           float2 aUV : TEXCOORD0, uint inst : SV_InstanceID) {
    VSOut o;
    int idx = (int)inst * 8;
    float4x4 model = transpose(float4x4(g_rows[idx + 0], g_rows[idx + 1],
                                        g_rows[idx + 2], g_rows[idx + 3]));
    float4x4 prev_model = transpose(float4x4(g_rows[idx + 4], g_rows[idx + 5],
                                             g_rows[idx + 6], g_rows[idx + 7]));
    float4 world_pos = mul(model, float4(aPos, 1.0f));
    o.world = world_pos.xyz;
    o.normal = mul((float3x3)model, aNormal);
    o.uv = aUV;
    float4 curr_clip = mul(g_frame.proj, mul(g_push.u_view, world_pos));
    float4 prev_clip = mul(g_frame.prev_vp, mul(prev_model, float4(aPos, 1.0f)));
    o.velocity = curr_clip.xy / curr_clip.w - prev_clip.xy / prev_clip.w;
    o.pos = curr_clip;
    o.pos.z = (o.pos.z + o.pos.w) * 0.5f;   // GL clip z [-w, w] -> D3D12 [0, w]
    return o;
}
