// pbr_clustered_skin_lodfade_hlsl.vert - R707c LOD cross-fade twin of pbr_clustered_skin_hlsl.vert (D3D12). Identical except
// that the draw's first_instance high half (SV_StartInstanceLocation,
// R703b packing: 0 = no fade, else k + 16) is forwarded as the dither
// value at TEXCOORD4 for pbr_clustered_lodfade_hlsl.frag. main.c / deferred.c build the skinned
// pipeline with it only when the LOD fade is on. Keep the two in sync.
//
// pbr_clustered_skin_hlsl.vert - clustered forward PBR, SKINNED vertex stage
// (D3D12 hand-authored sidecar of shaders/pbr_clustered_skin.vert, FORWARD_MRT
// variant). Shares pbr_clustered_hlsl.frag with the static variant, so
// PushConsts and ClusterFrame are declared byte-identically to
// pbr_clustered_hlsl.vert; u_model is part of that block but unused here (the
// joint matrices already carry the world transform).
//
// Joints ride a structured buffer at t16 (the shared pixel stage owns
// t0-t15; main.c binds them with rhi_cmd_bind_storage_buffer(cmd, buf, 16)).
// Current pose at float4 slot 0, previous pose 512 slots further in, each
// joint four COLUMNS (hence the transpose, as in gbuffer_skinned_hlsl.vert).
// The skinning attributes use the BLENDINDICES / BLENDWEIGHT names of the
// backend's 64-byte skinned input layout.
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

StructuredBuffer<float4> g_joints : register(t16, space0);

struct VSOut {
    float4 pos : SV_Position;
    float3 world : TEXCOORD0;
    float3 normal : TEXCOORD1;
    float2 uv : TEXCOORD2;
    float2 velocity : TEXCOORD3;
    nointerpolation float lod_fade : TEXCOORD4;
};

float4x4 joint_at(int base) {
    return transpose(float4x4(g_joints[base + 0], g_joints[base + 1],
                              g_joints[base + 2], g_joints[base + 3]));
}

VSOut main(float3 aPos : POSITION, float3 aNormal : NORMAL,
           float2 aUV : TEXCOORD, uint4 aJoints : BLENDINDICES,
           float4 aWeights : BLENDWEIGHT,
           uint start_instance : SV_StartInstanceLocation) {
    VSOut o;
    uint fade_code = start_instance >> 16;
    o.lod_fade = fade_code == 0u ? 0.0f : (float)((int)fade_code - 16);
    float4x4 skin = (float4x4)0.0f;
    float4x4 prev_skin = (float4x4)0.0f;
    for (int i = 0; i < 4; i++) {
        int j = (int)aJoints[i];
        skin += aWeights[i] * joint_at(j * 4);
        prev_skin += aWeights[i] * joint_at(512 + j * 4);
    }
    float4 world_pos = mul(skin, float4(aPos, 1.0f));
    o.world = world_pos.xyz;
    o.normal = mul((float3x3)skin, aNormal);
    o.uv = aUV;
    float4 curr_clip = mul(g_frame.proj, mul(g_push.u_view, world_pos));
    float4 prev_clip = mul(g_frame.prev_vp, mul(prev_skin, float4(aPos, 1.0f)));
    o.velocity = curr_clip.xy / curr_clip.w - prev_clip.xy / prev_clip.w;
    o.pos = curr_clip;
    o.pos.z = (o.pos.z + o.pos.w) * 0.5f;   // GL clip z [-w, w] -> D3D12 [0, w]
    return o;
}
