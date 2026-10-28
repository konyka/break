// gbuffer_hlsl.frag - G-Buffer write pass, fragment stage
// (D3D12 hand-authored sidecar of shaders/gbuffer.frag, the GL variant).
//
// Five render targets in the deferred RT layout (deferred.c
// defrd_alloc_targets): RT0 albedo+metallic, RT1 octahedral normal, RT2
// roughness/AO/emissive flag, RT3 velocity, RT4 HDR emissive.
//
// Textures sit at the GL units bind_material uses (rhi_cmd_bind_material_
// textures_ibl): albedo t0, metallic-roughness t2, normal map t3, emissive t4,
// occlusion t15. No push block: the vertex stage owns b0. The factor block is
// the GLSL GbufFactors UBO (binding 0 on GL), here at b1 because b0 is the
// root-constant register; deferred.c binds it at caps.temporal_ubo_binding.
//
// dFdx / dFdy are ddx_fine / ddy_fine. Under the backend's offscreen
// viewport SV_Position.y and gl_FragCoord.y both grow with the memory row,
// and memory row 0 is NDC y = -1 on both, so the derivative signs -- and the
// derivative TBN built from them -- match GL. The static sampler is
// LINEAR + WRAP (known D3D12 limit), the GL sampler is LINEAR + REPEAT for
// material textures, so the material reads agree.
struct GbufFactors {
    float4 u_factors;          // x metallic, y roughness, z AO strength, w emissive flag
    float4 u_emissive_factor;  // rgb emissiveFactor x strength
};
ConstantBuffer<GbufFactors> g_factors : register(b1, space0);

Texture2D g_albedo     : register(t0, space0);
Texture2D g_mr         : register(t2, space0);
Texture2D g_normal_map : register(t3, space0);
Texture2D g_emissive   : register(t4, space0);
Texture2D g_occlusion  : register(t15, space0);
SamplerState g_smp0  : register(s0, space0);
SamplerState g_smp2  : register(s2, space0);
SamplerState g_smp3  : register(s3, space0);
SamplerState g_smp4  : register(s4, space0);
SamplerState g_smp15 : register(s15, space0);

struct PSOut {
    float4 albedo_metallic : SV_Target0;
    float4 normal          : SV_Target1;
    float4 roughness_ao    : SV_Target2;
    float4 velocity        : SV_Target3;
    float4 emissive        : SV_Target4;
};

float2 octahedron_encode(float3 n) {
    n = normalize(n);
    n /= (abs(n.x) + abs(n.y) + abs(n.z));
    if (n.z < 0.0f) {
        float2 wrapped = (1.0f - abs(n.yx)) * float2(
            n.x >= 0.0f ? 1.0f : -1.0f,
            n.y >= 0.0f ? 1.0f : -1.0f);
        n.xy = wrapped;
    }
    return n.xy * 0.5f + 0.5f;
}

float3 perturb_normal(float3 world, float3 n, float2 uv) {
    float3 map = g_normal_map.Sample(g_smp3, uv).rgb * 2.0f - 1.0f;
    float3 q1  = ddx_fine(world);
    float3 q2  = ddy_fine(world);
    float2 st1 = ddx_fine(uv);
    float2 st2 = ddy_fine(uv);
    float3 t = normalize(q1 * st2.y - q2 * st1.y);
    float3 b = -normalize(cross(n, t));
    // GLSL mat3(t, b, n) * map: t, b, n are the COLUMNS.
    return normalize(t * map.x + b * map.y + n * map.z);
}

PSOut main(float4 pos : SV_Position, float3 world : TEXCOORD0,
           float3 normal : TEXCOORD1, float2 uv : TEXCOORD2,
           float2 velocity : TEXCOORD3) {
    PSOut o;
    float3 base  = g_albedo.Sample(g_smp0, uv).rgb;
    float2 mr    = g_mr.Sample(g_smp2, uv).bg;
    float2 mrf   = mr * g_factors.u_factors.xy;
    float  metal = clamp(mrf.x, 0.0f, 1.0f);
    float  rough = clamp(mrf.y, 0.04f, 1.0f);
    float  ao    = lerp(1.0f, g_occlusion.Sample(g_smp15, uv).r,
                        clamp(g_factors.u_factors.z, 0.0f, 1.0f));
    float3 emis  = g_emissive.Sample(g_smp4, uv).rgb * g_factors.u_emissive_factor.rgb;

    o.albedo_metallic = float4(base, metal);
    float3 nrm = perturb_normal(world, normalize(normal), uv);
    o.normal       = float4(octahedron_encode(nrm), 0.0f, 1.0f);
    o.roughness_ao = float4(rough, ao, clamp(g_factors.u_factors.w, 0.0f, 1.0f), 1.0f);
    o.emissive     = float4(emis, 1.0f);
    o.velocity     = float4(velocity, 0.0f, 1.0f);
    return o;
}
