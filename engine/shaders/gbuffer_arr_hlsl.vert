// gbuffer_arr_hlsl.vert - texture-array G-Buffer write pass, vertex stage
// (D3D12 hand-authored sidecar of shaders/gbuffer_arr.vert, the GL variant).
//
// Same push layout as gbuffer_hlsl.vert (u_model, u_vp = proj * view,
// u_prev_mvp; see that file for why view and proj arrive folded), plus one
// difference: the layer is the indirect command's first_instance, read as
// SV_StartInstanceLocation -- a shader-model 6.8 vertex input, so the build
// compiles this file as vs_6_8. GLSL: v_layer = uint(gl_BaseInstanceARB).
// SV_InstanceID would be wrong: it is gl_InstanceID and never includes the
// base (production draws one instance per command with first_instance =
// layer).
struct PushConsts {
    float4x4 u_model;     //   0
    float4x4 u_vp;        //  64
    float4x4 u_prev_mvp;  // 128
};                        // tail at 192
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_model 0
// rhi:uniform u_vp 64
// rhi:uniform u_prev_mvp 128

struct VSIn {
    float3 pos : POSITION;    // a_position @ 0
    float3 normal : NORMAL;   // a_normal   @ 12
    float2 uv : TEXCOORD0;    // a_texcoord @ 24
    uint layer : SV_StartInstanceLocation;
};
struct VSOut {
    float4 pos : SV_Position;
    float3 world : TEXCOORD0;     // v_world_pos (location 0)
    float3 normal : TEXCOORD1;    // v_normal    (location 1)
    float2 uv : TEXCOORD2;        // v_texcoord  (location 2)
    float2 velocity : TEXCOORD3;  // v_velocity  (location 3)
    nointerpolation uint layer : TEXCOORD4;  // v_layer (flat, location 4)
};

VSOut main(VSIn i) {
    VSOut o;
    float4 wp = mul(g_push.u_model, float4(i.pos, 1.0f));
    o.world = wp.xyz;
    o.normal = mul((float3x3)g_push.u_model, i.normal);
    o.uv = i.uv;
    o.layer = i.layer;
    float4 curr_clip = mul(g_push.u_vp, wp);
    float4 prev_clip = mul(g_push.u_prev_mvp, float4(i.pos, 1.0f));
    o.velocity = curr_clip.xy / curr_clip.w - prev_clip.xy / prev_clip.w;
    o.pos = curr_clip;
    o.pos.z = (o.pos.z + o.pos.w) * 0.5f;
    return o;
}
