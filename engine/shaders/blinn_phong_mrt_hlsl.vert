// blinn_phong_mrt_hlsl.vert - blinn_phong forward VS, FORWARD_MRT variant
// (D3D12 hand-authored sidecar). The GLSL twin is shaders/blinn_phong.vert
// with FORWARD_MRT defined; the non-MRT pair is blinn_phong_hlsl.{vert,frag}.
// The push block and the b1 temporal CBV are identical to that pair on
// purpose - only the velocity output is added, so the two sidecars cannot
// drift apart field for field.
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

// R600: mirrors the GLSL ForwardTemporal block member for member; see
// blinn_phong_hlsl.vert for why u_camera_pos rides the CBV instead of the
// push block.
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
    float2 velocity : TEXCOORD3;   // GLSL location 3
};
VSOut main(VSIn i) {
    VSOut o;
    float4 world_pos = mul(g_push.u_model, float4(i.pos, 1.0));
    o.world = world_pos.xyz;
    // GLSL: mat3(u_model) * aNormal - upper-left 3x3, no inverse-transpose.
    o.normal = mul((float3x3)g_push.u_model, i.normal);
    o.uv = i.uv;
    float4 curr_clip = mul(mul(g_push.u_proj, g_push.u_view), world_pos);
    // GLSL: u_prev_vp * u_prev_model * aPos — the object-space position, not
    // world_pos, because u_prev_model is the model matrix of the PREVIOUS
    // frame and mega vertices are pre-transformed to world space.
    float4 prev_clip = mul(mul(g_temporal.u_prev_vp, g_temporal.u_prev_model),
                           float4(i.pos, 1.0));
    o.velocity = curr_clip.xy / curr_clip.w - prev_clip.xy / prev_clip.w;
    o.pos = curr_clip;
    // R621: OpenGL proj -> D3D12 clip.z [0,1], matching every Vulkan forward
    // twin. Velocity above is computed from curr_clip.xy / .w, which the
    // conversion does not touch.
    o.pos.z = (o.pos.z + o.pos.w) * 0.5f;
    return o;
}
