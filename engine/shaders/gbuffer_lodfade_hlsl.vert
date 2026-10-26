// gbuffer_hlsl.vert - G-Buffer write pass, vertex stage
// (D3D12 hand-authored sidecar of shaders/gbuffer.vert, the GL variant).
//
// The GLSL twin takes u_model, u_view, u_proj and u_prev_mvp: four mat4,
// 256 bytes. The paired fragment stage declares five textures and the factor
// CBV, six descriptor tables, which leaves 64 - 6 = 58 DWORDs (232 bytes) of
// root constants -- one matrix short. view and proj are only ever used as
// their product, so this twin takes that product as u_vp; deferred.c resolves
// "u_vp" (GL/VK resolve it to -1) and main.c uploads proj*view there, while
// u_view / u_proj resolve to -1 here. Same arithmetic, one matrix fewer.
//
// The clip position is remapped from GL's z in [-w, w] to D3D12's [0, w]
// (the Vulkan twin does the same, R214-A). The velocity is computed from the
// GL-convention clip positions before that remap, as in the GLSL.
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
    uint start_instance : SV_StartInstanceLocation;
};
struct VSOut {
    float4 pos : SV_Position;
    float3 world : TEXCOORD0;     // v_world_pos (location 0)
    float3 normal : TEXCOORD1;    // v_normal    (location 1)
    float2 uv : TEXCOORD2;        // v_texcoord  (location 2)
    float2 velocity : TEXCOORD3;  // v_velocity  (location 3)
    nointerpolation float lod_fade : TEXCOORD4;
};

VSOut main(VSIn i) {
    VSOut o;
    uint fade_code = i.start_instance >> 16;
    o.lod_fade = fade_code == 0u ? 0.0f : (float)((int)fade_code - 16);
    float4 wp = mul(g_push.u_model, float4(i.pos, 1.0f));
    o.world = wp.xyz;
    o.normal = mul((float3x3)g_push.u_model, i.normal);
    o.uv = i.uv;
    float4 curr_clip = mul(g_push.u_vp, wp);
    float4 prev_clip = mul(g_push.u_prev_mvp, float4(i.pos, 1.0f));
    o.velocity = curr_clip.xy / curr_clip.w - prev_clip.xy / prev_clip.w;
    o.pos = curr_clip;
    o.pos.z = (o.pos.z + o.pos.w) * 0.5f;
    return o;
}
