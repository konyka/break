// blinn_phong_hlsl.vert - blinn_phong forward VS (D3D12 hand-authored sidecar).
// Twin of shaders/blinn_phong.vert; semantics match RHIPipelineDesc's default
// mesh layout (POSITION/NORMAL/TEXCOORD0, 32B stride). b0 is the reserved
// 32BIT_CONSTANTS root-constant register: the struct below is declared
// byte-identically in the fragment sidecar so both stages read one block.
// The FORWARD_MRT twin of this pair is blinn_phong_mrt_hlsl.{vert,frag}.
struct PushConsts {
    float4x4 u_model;       //   0
    float4x4 u_view;        //  64
    float4x4 u_proj;        // 128
    float3   u_light_dir;   // 192 (16B slot)
    float3   u_light_color; // 208
    float3   u_ambient;     // 224
};                          // tail ends at 240
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_model 0
// rhi:uniform u_view 64
// rhi:uniform u_proj 128
// rhi:uniform u_light_dir 192
// rhi:uniform u_light_color 208
// rhi:uniform u_ambient 224

// R600: mirrors the GLSL ForwardTemporal block member for member
// (std140 {vec3 u_camera_pos; float pad; mat4 u_prev_vp; mat4
// u_prev_model}) and the engine's ForwardTemporalUbo, so the same uploaded
// bytes serve all three backends. The camera position used to sit in the
// push block at 240..252, which is exactly the tail a second descriptor
// table truncates away: the D3D12 root signature is capped at 64 DWORDs and
// every table costs one, so adding this b1 CBV drops the declared push range
// from 252 to 248 bytes and rhi_cmd_push_constants would DROP the write — a
// silently zeroed camera behind a log line. With the camera here the push
// block ends at 240 and survives 248 with room to spare.
struct ForwardTemporal {
    float3   u_camera_pos;  //  0 (16B slot)
    float    _cam_pad;      // 12
    float4x4 u_prev_vp;     // 16
    float4x4 u_prev_model;  // 80
};
ConstantBuffer<ForwardTemporal> g_temporal : register(b1, space0);

struct VSIn {
    float3 pos : POSITION;   // aPos    float3 @ 0
    float3 normal : NORMAL;  // aNormal float3 @ 12
    float2 uv : TEXCOORD0;   // aUV     float2 @ 24
};
struct VSOut {
    float4 pos : SV_Position;
    float3 world : TEXCOORD0;
    float3 normal : TEXCOORD1;
    float2 uv : TEXCOORD2;
};
VSOut main(VSIn i) {
    VSOut o;
    float4 world_pos = mul(g_push.u_model, float4(i.pos, 1.0));
    o.world = world_pos.xyz;
    // GLSL: mat3(u_model) * aNormal - upper-left 3x3, no inverse-transpose.
    o.normal = mul((float3x3)g_push.u_model, i.normal);
    o.uv = i.uv;
    o.pos = mul(mul(g_push.u_proj, g_push.u_view), world_pos);
    // R621: OpenGL proj -> D3D12 clip.z [0,1]. Every Vulkan forward twin does
    // this (blinn_phong_vk.vert R214-A); without it the whole near half of the
    // scene is clipped away. See the shared note in blinn_phong_hlsl.frag.
    o.pos.z = (o.pos.z + o.pos.w) * 0.5f;
    return o;
}
