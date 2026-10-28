// gbuffer_skinned_hlsl.vert - skinned G-Buffer write pass, vertex stage
// (D3D12 hand-authored sidecar of shaders/gbuffer_skinned.vert, the GL
// variant). Paired with gbuffer_hlsl.frag, as the GL loader pairs the GLSL
// twin with gbuffer.frag.
//
// Push block: the gbuffer_hlsl.vert one (u_model, u_vp = proj * view,
// u_prev_mvp), for the same budget reason -- the fragment stage's six
// descriptor tables plus the joint SRV here leave 57 DWORDs, not room for
// four matrices. deferred.c resolves u_vp for this pipeline too.
//
// Joints: rhi_cmd_bind_texel_buffers unit 5 -> t5, current pose at 0 and the
// previous pose 512 float4 further in, column-major (hence the transpose,
// as in skinned_mrt_hlsl.vert). The skinning attributes use the
// BLENDINDICES / BLENDWEIGHT names the backend's 64-byte skinned input
// layout declares.
//
// As in the GLSL: the current position is u_model * (skin * pos), the
// previous one is u_prev_mvp * (prev_skin * pos) with no model matrix, and
// the velocity is taken from the GL-convention clip positions before the
// clip z remap to D3D12's [0, w].
struct PushConsts {
    float4x4 u_model;     //   0
    float4x4 u_vp;        //  64
    float4x4 u_prev_mvp;  // 128
};                        // tail at 192
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_model 0
// rhi:uniform u_vp 64
// rhi:uniform u_prev_mvp 128

StructuredBuffer<float4> g_joints : register(t5, space0);

struct VSOut {
    float4 pos : SV_Position;
    float3 world : TEXCOORD0;     // v_world_pos (location 0)
    float3 normal : TEXCOORD1;    // v_normal    (location 1)
    float2 uv : TEXCOORD2;        // v_texcoord  (location 2)
    float2 velocity : TEXCOORD3;  // v_velocity  (location 3)
};

float4x4 joint_at(int base) {
    return transpose(float4x4(g_joints[base + 0], g_joints[base + 1],
                              g_joints[base + 2], g_joints[base + 3]));
}

VSOut main(float3 aPos : POSITION, float3 aNormal : NORMAL,
           float2 aUV : TEXCOORD, uint4 aJoints : BLENDINDICES,
           float4 aWeights : BLENDWEIGHT) {
    VSOut o;
    float4x4 skin = (float4x4)0.0f;
    float4x4 prev_skin = (float4x4)0.0f;
    for (int i = 0; i < 4; i++) {
        int j = (int)aJoints[i];
        skin += aWeights[i] * joint_at(j * 4);
        prev_skin += aWeights[i] * joint_at(512 + j * 4);
    }
    float4 world_pos = mul(g_push.u_model, mul(skin, float4(aPos, 1.0f)));
    o.world = world_pos.xyz;
    o.normal = mul((float3x3)g_push.u_model, mul((float3x3)skin, aNormal));
    o.uv = aUV;
    float4 curr_clip = mul(g_push.u_vp, world_pos);
    float4 prev_clip = mul(g_push.u_prev_mvp, mul(prev_skin, float4(aPos, 1.0f)));
    o.velocity = curr_clip.xy / curr_clip.w - prev_clip.xy / prev_clip.w;
    o.pos = curr_clip;
    o.pos.z = (o.pos.z + o.pos.w) * 0.5f;
    return o;
}
