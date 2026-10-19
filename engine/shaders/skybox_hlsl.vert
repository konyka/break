// skybox_hlsl.vert - skybox fullscreen VS (D3D12 hand-authored sidecar).
// Twin of shaders/skybox.vert (the GL variant, NOT skybox_vk.vert: D3D12 is
// not Vulkan, and the loose `uniform mat4` the GL twin declares is what the
// offset markers below reproduce). skybox.vert has no FORWARD_MRT arm, so this
// one file serves both the single-target and the MRT pipeline; only the
// fragment stage differs between them.
//
// Input: none. The GL twin indexes a const vec2[3] fullscreen triangle with
// gl_VertexID; HLSL names that same system value SV_VertexID. Both are
// SYSTEM-VALUE semantics — they consume no vertex-buffer slot — so the
// input layout stays at rhi_d3d12_input_layout's `no_vertex_input` arm
// (zero elements, zero stride), which is exactly what RHIPipelineDesc's
// .no_vertex_input = true in skybox.c selects.
//
// b0 is the reserved 32BIT_CONSTANTS root-constant register: the struct below
// is declared byte-identically in the fragment sidecars so both stages read
// one block.
struct PushConsts {
    float4x4 u_inv_proj;   //   0
    float4x4 u_view;       //  64
    float3   u_sun_dir;    // 128 (16B slot)
    float3   u_sun_color;  // 144
};                         // tail ends at 160
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_inv_proj 0
// rhi:uniform u_view 64

static const float2 POS[3] = {
    float2(-1.0, -1.0),
    float2( 3.0, -1.0),
    float2(-1.0,  3.0)
};

struct VSOut {
    float4 pos : SV_Position;
    float3 ray_dir : TEXCOORD0;
};
VSOut main(uint vid : SV_VertexID) {
    VSOut o;
    float2 p = POS[vid];
    o.pos = float4(p, 1.0, 1.0);

    // GLSL: u_inv_proj * vec4(p, 1, 1) — same bytes, same column-major
    // product, so mul() is the identical operation.
    float4 ray_clip = float4(p, 1.0, 1.0);
    float4 ray_eye = mul(g_push.u_inv_proj, ray_clip);
    ray_eye = float4(ray_eye.xy, -1.0, 0.0);
    // R438: view is canonical (rows = basis); eye->world needs R^T. GLSL
    // spells that transpose(mat3(u_view)) * v; mul(M, v) is M*v, so the
    // transpose has to be explicit — do NOT "simplify" it away.
    o.ray_dir = mul(transpose((float3x3)g_push.u_view), ray_eye.xyz);
    // R551-E: NOT normalized here — the fragment stage normalizes.
    return o;
}
