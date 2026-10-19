// water_hlsl.vert - water plane VS (D3D12 hand-authored sidecar). Twin of
// shaders/water.vert (the GL variant, NOT water_vk.vert). b0 is the reserved
// 32BIT_CONSTANTS root-constant register: the struct below is declared
// byte-identically in the fragment sidecar so both stages read one block.
//
// Input: position only. water_init declares .vertex_stride = 3*sizeof(f32),
// and rhi_d3d12_input_layout's `stride == 12u` arm emits exactly one
// POSITION element at that stride -- the default 3-attribute layout would
// fetch past the end of a 12-byte vertex.
//
// Layout note: u_view(0) u_proj(64) u_light_vp(128) are vertex-only/fragment-
// only but share the one block; the tail packs u_camera_pos/u_time into a
// float3+float pair at 192/204 rather than a float4 at 192, which buys the
// three scalars (u_water_color@208, u_shadow_bias@220, u_water_y@224) room
// inside the 252-byte root-constant range the pipeline ends up declaring
// (64 DWORDs minus the one descriptor table the shadow SRV costs). Everything
// must end by 252; see rhi_d3d12_root_signature_create.
struct PushConsts {
    float4x4 u_view;         //   0
    float4x4 u_proj;         //  64
    float4x4 u_light_vp;     // 128
    float3   u_camera_pos;   // 192
    float    u_time;         // 204
    float3   u_water_color;  // 208
    float    u_shadow_bias;  // 220
    float    u_water_y;      // 224
};                           // tail ends at 228, 16B-aligned to 240
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_view 0
// rhi:uniform u_proj 64
// rhi:uniform u_water_y 224

struct VSIn {
    float3 pos : POSITION;   /* GLSL aPos, location 0 */
};
struct VSOut {
    float4 pos : SV_Position;
    float3 world : TEXCOORD0;
    float2 velocity : TEXCOORD1;
};
VSOut main(VSIn i) {
    VSOut o;
    /* R235-B: Mesh verts sit at y=0; lift to logical water plane. */
    float3 wp = float3(i.pos.x, g_push.u_water_y, i.pos.z);
    o.world = wp;
    o.pos = mul(g_push.u_proj, mul(g_push.u_view, float4(wp, 1.0f)));
    /* FORWARD_MRT: water.vert reconstructs v_velocity from the ForwardTemporal
     * UBO at binding 0 (u_prev_vp). This sidecar does NOT take that block.
     * water_render never calls rhi_cmd_bind_uniform_buffer, so on D3D12 the
     * CBV descriptor table this would add is never written -- rhi_cmd_bind_
     * pipeline does not reset descriptor tables, so the draw would sample
     * whatever stale table the previous draw left at that root parameter. A
     * zero motion vector is both defined and the value the attachment is
     * cleared to, so RT1 gets it without inventing a binding the engine does
     * not make. */
    o.velocity = float2(0.0f, 0.0f);
    return o;
}
