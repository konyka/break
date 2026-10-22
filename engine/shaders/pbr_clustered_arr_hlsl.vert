// pbr_clustered_arr_hlsl.vert - clustered forward PBR, TEXTURE-ARRAY vertex
// stage (D3D12 hand-authored sidecar of shaders/pbr_clustered_arr.vert,
// FORWARD_MRT variant). Differs from pbr_clustered_hlsl.vert only in forwarding
// the indirect command's first_instance (the material-array layer) to the
// pixel stage: GLSL uint(gl_BaseInstanceARB), here SV_StartInstanceLocation,
// a shader-model 6.8 vertex input (the build compiles this file as vs_6_8).
//
// Original header of the static variant follows.
//
// Root budget: the fragment stage declares 16 SRV tables and this pair
// shares one frame CBV at b1, 17 tables in all, which leaves 47 DWORDs of
// root constants. u_model (per draw), u_view and the per-material block fit;
// everything that is constant for the frame (projection, previous view-proj,
// camera, fog, counts, ...) lives in the b1 cbuffer the engine fills once per
// frame (main.c forward_clustered_bind_frame) instead of in the push block.
// PushConsts and ClusterFrame are declared byte-identically in the fragment
// sidecar.
struct PushConsts {
    float4x4 u_model;            //   0
    float4x4 u_view;             //  64
    float2   u_mr_factor;        // 128
    float    u_occlusion_strength; // 136
    float3   u_emissive_factor;  // 144
};                               // tail at 156
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_model 0
// rhi:uniform u_view 64

struct ClusterFrame {
    float4x4 prev_vp;            //   0
    float4x4 prev_model;         //  64
    float4x4 proj;               // 128
    float4   camera_pos;         // 192 xyz
    float4   ambient;            // 208 xyz
    float4   fog_color;          // 224 xyz
    float4   fog;                // 240 x near, y far, z underwater, w pom
    float4   screen;             // 256 x w, y h, z near, w far
    float4   counts;             // 272 x point, y dir, z shadow_bias
    float4   far_planes;         // 288
};                               // tail at 304
ConstantBuffer<ClusterFrame> g_frame : register(b1, space0);

struct VSIn {
    float3 pos : POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD0;
    uint layer : SV_StartInstanceLocation;
};
struct VSOut {
    float4 pos : SV_Position;
    float3 world : TEXCOORD0;
    float3 normal : TEXCOORD1;
    float2 uv : TEXCOORD2;
    float2 velocity : TEXCOORD3;
    nointerpolation uint layer : TEXCOORD4;
};

VSOut main(VSIn i) {
    VSOut o;
    float4 wp = mul(g_push.u_model, float4(i.pos, 1.0f));
    o.world = wp.xyz;
    o.normal = mul((float3x3)g_push.u_model, i.normal);
    o.uv = i.uv;
    o.layer = i.layer;
    float4 curr_clip = mul(g_frame.proj, mul(g_push.u_view, wp));
    float4 prev_clip = mul(g_frame.prev_vp, mul(g_frame.prev_model, float4(i.pos, 1.0f)));
    o.velocity = curr_clip.xy / curr_clip.w - prev_clip.xy / prev_clip.w;
    o.pos = curr_clip;
    o.pos.z = (o.pos.z + o.pos.w) * 0.5f;   // GL clip z [-w, w] -> D3D12 [0, w]
    return o;
}
