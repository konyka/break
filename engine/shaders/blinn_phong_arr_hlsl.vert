// blinn_phong_arr_hlsl.vert - material-array blinn_phong forward VS (D3D12
// hand-authored sidecar). Twin of shaders/blinn_phong_arr.vert with
// FORWARD_MRT defined; the non-array pair is blinn_phong_hlsl.{vert,frag} and
// the array shader's non-MRT GLSL twin is blinn_phong.vert. Semantics match
// RHIPipelineDesc's default mesh layout (POSITION/NORMAL/TEXCOORD0, 32B
// stride). b0 is the reserved 32BIT_CONSTANTS root-constant register: the
// struct below is declared byte-identically in the fragment sidecar so both
// stages read one block.
//
// R441 + R600: two deltas from the non-array pair, both forced by the array
// variant's own contract.
//   1. u_albedo is a sampler2DArray in the fragment sidecar, so this stage
//      must hand the layer down. GLSL spells it uint(gl_BaseInstanceARB) --
//      the indirect draw command's first_instance, which is independent of
//      InstanceCount. HLSL's equivalent is SV_StartInstanceLocation.
//      SV_InstanceID is NOT the twin: that is gl_InstanceID, i.e.
//      base + instance index, so the two agree only when first_instance is 0
//      and the draw is a single instance. Production here is
//      first_instance = layer with InstanceCount = 1, and reading
//      SV_InstanceID on the RTX 4060 renders layer 0 for StartInstanceLocation
//      1 and 2 alike, so the old pairing was silently wrong on the one route
//      the engine actually uses. See blinn_phong_arr_hlsl.frag for the full
//      measurement and for why no other semantic fixes it.
//   2. The push block has no u_camera_pos: R600 moved the camera into the
//      b1 temporal CBV, exactly as blinn_phong_hlsl.vert did. Both twins of
//      this pair below share the shortened 240-byte tail.
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
// bytes serve all three backends. See blinn_phong_hlsl.vert for why the camera
// position left the push block: a second descriptor table costs a DWORD of the
// 64-DWORD root-signature budget and would truncate the declared push range
// from 252 to 248 bytes, dropping u_camera_pos@240+12=252 on the floor.
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
    // GLSL: vLayer = uint(gl_BaseInstanceARB). nointerpolation is HLSL's
    // flat-equivalent and is mandatory for an integer interpolant to survive
    // the trip unchanged; it must match the PS input's modifier exactly.
    // ⚠️ This is NOT the GLSL twin -- SV_InstanceID is gl_InstanceID, not
    // gl_BaseInstance, and on D3D12 the base never reaches it. The array path
    // is disabled on D3D12 today (caps.indirect_draw_supported is never set),
    // so this is latent, not live. See the long note in
    // blinn_phong_arr_hlsl.frag.
    uint layer : SV_InstanceID;
};
struct VSOut {
    float4 pos : SV_Position;
    float3 world : TEXCOORD0;
    float3 normal : TEXCOORD1;
    float2 uv : TEXCOORD2;
    float2 velocity : TEXCOORD3;         // GLSL location 3
    nointerpolation uint layer : TEXCOORD4;  // GLSL flat out uint vLayer
};
VSOut main(VSIn i) {
    VSOut o;
    float4 world_pos = mul(g_push.u_model, float4(i.pos, 1.0));
    o.world = world_pos.xyz;
    // GLSL: mat3(u_model) * aNormal - upper-left 3x3, no inverse-transpose.
    o.normal = mul((float3x3)g_push.u_model, i.normal);
    o.uv = i.uv;
    o.layer = i.layer;
    float4 curr_clip = mul(mul(g_push.u_proj, g_push.u_view), world_pos);
    // GLSL: u_prev_vp * u_prev_model * aPos - the object-space position, not
    // world_pos, because u_prev_model is the model matrix of the PREVIOUS
    // frame and mega vertices are pre-transformed to world space.
    float4 prev_clip = mul(mul(g_temporal.u_prev_vp, g_temporal.u_prev_model),
                           float4(i.pos, 1.0));
    o.velocity = curr_clip.xy / curr_clip.w - prev_clip.xy / prev_clip.w;
    o.pos = curr_clip;
    // R621: OpenGL proj -> D3D12 clip.z [0,1], matching blinn_phong_arr_vk.
    o.pos.z = (o.pos.z + o.pos.w) * 0.5f;
    return o;
}
