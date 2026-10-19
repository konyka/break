// skinned_mrt_hlsl.vert - skinned VS (D3D12 hand-authored sidecar of
// shaders/skinned.vert, the GL variant -- not skinned_vk.vert).
//
// Same structure as instanced_mrt_hlsl.vert and for the same reasons:
//   - the four lighting uniforms live in the temporal CBV, not the push block,
//     because six push words plus two mat4 overflows what two descriptor
//     tables leave of the root constants (R616);
//   - they are appended to ForwardTemporalUbo after prev_model so blinn_phong's
//     u_camera_pos@0 and u_prev_vp@16 do not move;
//   - the block is NOT made unconditional the way R600 did for blinn_phong --
//     only the MRT variant is ever built, and forcing a bind on every draw
//     for an MRT-only value is the trap R600's header warns about.
//
// The vertex layout adds two attributes over instanced: aJoints (uvec4) and
// aWeights (vec4), giving a 48-byte stride -- 3 + 3 + 2 + 4 + 4 floats.
//
// Joint matrices come from rhi_cmd_bind_texel_buffers at unit 5 (R103-1, the
// GL binding = 5), which the backend binds as an SRV at t5. The previous
// joints sit 512 texels further in, exactly as the GLSL indexes them.
struct PushConsts {
    float4x4 u_view;   //   0
    float4x4 u_proj;   //  64
};                    // tail at 128
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_view 0
// rhi:uniform u_proj 64

// Byte-identical to ForwardTemporalUbo in main.c.
struct ForwardTemporal {
    float3   u_camera_pos;     //   0
    float    _cam_pad;         //  12
    float4x4 u_prev_vp;        //  16
    float4x4 u_prev_model;     //  80
    float3   light_dir;        // 144
    float    _light_dir_pad;   // 156
    float3   light_color;      // 160
    float    _light_color_pad; // 172
    float3   ambient;          // 176
    float    _ambient_pad;     // 188
};                              // tail at 192
ConstantBuffer<ForwardTemporal> g_temporal : register(b1, space0);

StructuredBuffer<float4> g_joints : register(t5, space0);

struct VSOut {
    float4 pos : SV_Position;
    float3 world : TEXCOORD0;
    float3 normal : TEXCOORD1;
    float2 uv : TEXCOORD2;
    float2 velocity : TEXCOORD3;
};
// The two skinning attributes use the glTF-conventional D3D12 semantic
// names BLENDINDICES / BLENDWEIGHT, which is what
// rhi_d3d12_input_layout's skinned_vertex arm declares (and the layout it
// declares also fixes the stride at 64: POSITION 3, NORMAL 3, TEXCOORD 2,
// BLENDINDICES 4, BLENDWEIGHT 4). Naming them TEXCOORD1/2 instead compiles
// and then fails PSO creation, because no input element answers to those
// names -- which is exactly what the first draft did.
VSOut main(float3 aPos : POSITION, float3 aNormal : NORMAL,
           float2 aUV : TEXCOORD, uint4 aJoints : BLENDINDICES,
           float4 aWeights : BLENDWEIGHT) {
    VSOut o;
    float4x4 skin = (float4x4)0.0f;
    float4x4 prev_skin = (float4x4)0.0f;
    for (int i = 0; i < 4; i++) {
        int j = (int)aJoints[i];
        float4x4 joint = float4x4(g_joints[j * 4 + 0], g_joints[j * 4 + 1],
                                   g_joints[j * 4 + 2], g_joints[j * 4 + 3]);
        skin += aWeights[i] * joint;
        float4x4 prev_joint =
            float4x4(g_joints[512 + j * 4 + 0], g_joints[512 + j * 4 + 1],
                     g_joints[512 + j * 4 + 2], g_joints[512 + j * 4 + 3]);
        prev_skin += aWeights[i] * prev_joint;
    }

    float4 world_pos = mul(skin, float4(aPos, 1.0f));
    o.world = world_pos.xyz;
    o.normal = mul((float3x3)skin, aNormal);
    o.uv = aUV;
    float4 curr_clip = mul(g_push.u_proj, mul(g_push.u_view, world_pos));
    float4 prev_clip = mul(g_temporal.u_prev_vp,
                           mul(prev_skin, float4(aPos, 1.0f)));
    o.velocity = curr_clip.xy / curr_clip.w - prev_clip.xy / prev_clip.w;
    o.pos = curr_clip;
    // R621: OpenGL proj -> D3D12 clip.z [0,1].
    o.pos.z = (o.pos.z + o.pos.w) * 0.5f;
    return o;
}
