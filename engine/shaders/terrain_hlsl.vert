// terrain_hlsl.vert - terrain VS (D3D12 hand-authored sidecar). Twin of
// shaders/terrain.vert (the GL variant, NOT terrain_vk.vert). Semantics match
// RHIPipelineDesc's default mesh layout (POSITION/NORMAL/TEXCOORD0, 32B
// stride) -- terrain_init leaves .vertex_stride at 0, which rhi_d3d12_
// input_layout turns into stride 32 with three elements, and terrain's vertex
// staging is exactly 8 floats per vertex. b0 is the reserved 32BIT_CONSTANTS
// root-constant register: the struct below is declared byte-identically in the
// fragment sidecar so both stages read one block.
//
// u_model is ABSENT, and that is deliberate. terrain.vert reads u_model to
// build world_pos, but terrain_render writes the identity matrix to it on
// every backend and terrain_vk.vert omits the member for the same reason.
// Keeping it would put world_pos at byte 256 in a block that has to end by
// 252 (64 DWORDs of root-signature budget minus the one descriptor table the
// shadow SRV costs), and rhi_d3d12_stage_uniform would DROP the writes past
// the declared range -- silently zeroed uniforms behind a warning. Omitting it
// reproduces the identity transform exactly and leaves the block 32 bytes
// smaller than the limit; terrain_render's model write now resolves -1 and is
// guarded.
struct PushConsts {
    float4x4 u_view;          //   0
    float4x4 u_proj;          //  64
    float4x4 u_light_vp;      // 128
    float3   u_camera_pos;    // 192
    float    u_time;          // 204
    float    u_water_y;       // 208
    float    u_shadow_bias;   // 212
    float    u_fog_strength;  // 216
};                            // tail ends at 220, 16B-aligned to 224
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_view 0
// rhi:uniform u_proj 64

struct VSIn {
    float3 pos : POSITION;    /* GLSL aPos,    location 0 */
    float3 normal : NORMAL;   /* GLSL aNormal, location 1 */
    float2 uv : TEXCOORD0;    /* GLSL aUV,     location 2 */
};
struct VSOut {
    float4 pos : SV_Position;
    float3 world : TEXCOORD0;
    float3 normal : TEXCOORD1;
    float2 uv : TEXCOORD2;
    float2 velocity : TEXCOORD3;
};
VSOut main(VSIn i) {
    VSOut o;
    /* u_model is the identity (see the header), so world_pos is the object
     * position and the normal passes through unchanged -- exactly what
     * terrain_vk.vert does, and what terrain.vert computes when the engine
     * writes identity. */
    float4 world_pos = float4(i.pos, 1.0f);
    o.world = world_pos.xyz;
    o.normal = i.normal;
    o.uv = i.uv;
    o.pos = mul(g_push.u_proj, mul(g_push.u_view, world_pos));
    // R621: OpenGL proj -> D3D12 clip.z [0,1], matching terrain_vk.vert. The
    // terrain shadow cascade is a separate shader (depth_only_hlsl.vert) and
    // had this from R613 already.
    o.pos.z = (o.pos.z + o.pos.w) * 0.5f;
    /* FORWARD_MRT: terrain.vert reconstructs v_velocity from the
     * ForwardTemporal UBO at binding 0 (u_prev_vp). This sidecar does NOT
     * take that block: terrain_render never calls rhi_cmd_bind_uniform_buffer,
     * so on D3D12 the CBV table this would add is never written, and
     * rhi_cmd_bind_pipeline does not reset descriptor tables -- the draw would
     * read whatever stale table the previous draw left at that root
     * parameter. vec2(0.0) is defined and is also what the attachment is
     * cleared to, so RT1 is correct without a binding the engine never makes. */
    o.velocity = float2(0.0f, 0.0f);
    return o;
}
