// ssr_hlsl.frag - screen-space reflections, depth ray-march (D3D12
// hand-authored sidecar of shaders/ssr.frag, the GL variant).
//
// 208 bytes of push block: three matrices and four floats. Two descriptor
// tables (t0 colour, t1 depth), which clamps 32BIT_CONSTANTS at 62 DWORDs =
// 248 bytes, so 208 fits -- unlike instanced, whose six uniforms do not (R616
// in docs/superpowers/plans/2026-10-19-d3d12-forward-mrt-velocity-design-plan.md).
//
// u_ssr_thickness is a GLSL const (R89-2 hardcoded it), so ssr_apply's write
// is already a no-op on GL; static const here with no rhi:uniform marker, so
// both backends resolve -1.
//
// R621 matters here: this shader decodes depth with depth * 2 - 1, which
// assumes the forward pass wrote (ndc_z + 1) / 2. Before R621 D3D12's forward
// sidecars wrote raw ndc_z and never converted, so every view position this
// reconstructed was wrong. The front and back early-outs below are the parts
// a pixel test can pin; the march is not, and the test says so.
struct PushConsts {
    float4x4 u_ssr_proj;      //   0
    float4x4 u_ssr_inv_proj;  //  64
    float4x4 u_ssr_view;      // 128
    float    u_ssr_sw;        // 192
    float    u_ssr_sh;        // 196
    float    u_ssr_max_steps; // 200
    float    u_ssr_stride;    // 204
};                           // tail at 208
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_ssr_proj 0
// rhi:uniform u_ssr_inv_proj 64
// rhi:uniform u_ssr_view 128
// rhi:uniform u_ssr_sw 192
// rhi:uniform u_ssr_sh 196
// rhi:uniform u_ssr_max_steps 200
// rhi:uniform u_ssr_stride 204

static const float u_ssr_thickness = 0.05f;

Texture2D g_color : register(t0, space0);
Texture2D g_depth : register(t1, space0);
SamplerState g_smp0 : register(s0, space0);
SamplerState g_smp1 : register(s1, space0);

float3 view_pos_from_depth(float2 uv, float depth) {
    float4 clip = float4(uv * 2.0f - 1.0f, depth * 2.0f - 1.0f, 1.0f);
    float4 view_h = mul(g_push.u_ssr_inv_proj, clip);
    return view_h.xyz / view_h.w;
}

float4 main(float4 pos : SV_Position, float2 uv : TEXCOORD0) : SV_Target0 {
    // R550-A: self-composite -- g_color is both the reflection source and the
    // incoming colour; the result is lerped by the reflection confidence.
    float3 scene = g_color.Sample(g_smp0, uv).rgb;
    float depth = g_depth.Sample(g_smp1, uv).r;

    if (depth >= 1.0f)
        return float4(scene, 1.0f);

    float3 pos_vs = view_pos_from_depth(uv, depth);
    // GLSL's dFdx / dFdy are the FINE screen-space derivatives, and this
    // DXC's spelling for them is ddx_fine / ddy_fine. The naming here is
    // worth writing down because all three obvious spellings fail or mislead:
    //
    //   DDX / DDY    rejected ("use of undeclared identifier")
    //   dFdx / dFdy  rejected, same
    //   ddx / ddy    accepted -- but these are the COARSE derivatives
    //                (dx.op.unary.f32 opcode 83, DerivCoarseX), which are NOT
    //                what the GLSL twin uses. On a 2x2 quad the coarse and
    //                fine slopes differ, so silently using ddx here would make
    //                the reconstructed normal differ from GL's.
    //   ddx_fine     -> dx.op.unary.f32 opcode 81, DerivFineX. Correct.
    float3 normal_vs = normalize(cross(ddx_fine(pos_vs), ddy_fine(pos_vs)));

    float3 view_dir = normalize(-pos_vs);
    float3 refl_dir = reflect(-view_dir, normal_vs);

    if (refl_dir.z > 0.0f)
        return float4(scene, 1.0f);

    float3 ray_start = pos_vs;
    float3 ray_end = ray_start + refl_dir * 100.0f;

    float4 start_clip = mul(g_push.u_ssr_proj, float4(ray_start, 1.0f));
    float4 end_clip = mul(g_push.u_ssr_proj, float4(ray_end, 1.0f));
    start_clip.xyz /= start_clip.w;
    end_clip.xyz /= end_clip.w;

    float3 start_screen = start_clip.xyz * 0.5f + 0.5f;
    float3 end_screen = end_clip.xyz * 0.5f + 0.5f;

    float3 ray_delta = end_screen - start_screen;
    float3 step_delta = ray_delta * (g_push.u_ssr_stride / g_push.u_ssr_max_steps);

    float3 ray = start_screen;
    float3 prev_ray = ray;
    float2 hit_uv = (float2)0.0f;
    bool found = false;

    for (int i = 0; i < (int)g_push.u_ssr_max_steps; i++) {
        prev_ray = ray;
        ray += step_delta;
        if (ray.x < 0.0f || ray.x > 1.0f || ray.y < 0.0f || ray.y > 1.0f) break;
        float sample_depth = g_depth.Sample(g_smp1, ray.xy).r;
        float diff = ray.z - sample_depth;
        if (diff > 0.0f && diff < u_ssr_thickness) {
            float3 lo = prev_ray;
            float3 hi = ray;
            for (int j = 0; j < 4; j++) {
                float3 mid = (lo + hi) * 0.5f;
                float mid_depth = g_depth.Sample(g_smp1, mid.xy).r;
                if (mid.z - mid_depth > 0.0f && mid.z - mid_depth < u_ssr_thickness)
                    hi = mid;
                else
                    lo = mid;
            }
            hit_uv = hi.xy;
            found = true;
            break;
        }
    }

    float3 ssr_color = (float3)0.0f;
    float fade = 0.0f;
    if (found) {
        ssr_color = g_color.Sample(g_smp0, hit_uv).rgb;
        float edge_fade = min(min(hit_uv.x, 1.0f - hit_uv.x),
                              min(hit_uv.y, 1.0f - hit_uv.y));
        fade = smoothstep(0.0f, 0.15f, edge_fade);
        // R84-4: Schlick with fifth power.
        float n_dot_v = max(dot(normal_vs, view_dir), 0.0f);
        float t = 1.0f - n_dot_v;
        float fresnel = 0.04f + 0.96f * (t * t * t * t * t);
        fade *= fresnel;
    }

    return float4(lerp(scene, ssr_color, fade), 1.0f);
}
