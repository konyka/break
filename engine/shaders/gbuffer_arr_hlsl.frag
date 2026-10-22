// gbuffer_arr_hlsl.frag - texture-array G-Buffer write pass, fragment stage
// (D3D12 hand-authored sidecar of shaders/gbuffer_arr.frag, the GL variant).
// Same as gbuffer_hlsl.frag except the albedo, metallic-roughness, normal,
// emissive and occlusion registers are Texture2DArray sampled at the layer the
// vertex stage forwards (nointerpolation uint layer, the indirect
// first_instance), and the b1 cbuffer holds the two 64-entry per-layer tables
// (u_factor_arr then u_emissive_arr, same layout as the GL GbufFactorArr)
// instead of one pair of factors.
//
// Five render targets in the deferred RT layout (deferred.c
// defrd_alloc_targets): RT0 albedo+metallic, RT1 octahedral normal, RT2
// roughness/AO/emissive flag, RT3 velocity, RT4 HDR emissive.
//
// Textures sit at the GL units bind_material uses (rhi_cmd_bind_material_
// textures_ibl): albedo t0, metallic-roughness t2, normal map t3, emissive t4,
// occlusion t15. No push block: the vertex stage owns b0. The factor block is
// the GLSL GbufFactorArr UBO (binding 0 on GL), here at b1 because b0 is the
// root-constant register; deferred.c binds it at caps.temporal_ubo_binding.
//
// dFdx / dFdy are ddx_fine / ddy_fine. Under the backend's offscreen
// viewport SV_Position.y and gl_FragCoord.y both grow with the memory row,
// and memory row 0 is NDC y = -1 on both, so the derivative signs -- and the
// derivative TBN built from them -- match GL. The static sampler is
// LINEAR + WRAP (known D3D12 limit), the GL sampler is LINEAR + REPEAT for
// material textures, so the material reads agree.
struct GbufFactorArr {
    float4 u_factor_arr[64];    // x metallic, y roughness, z AO strength, w emissive flag
    float4 u_emissive_arr[64];  // rgb emissiveFactor x strength
};
ConstantBuffer<GbufFactorArr> g_factors : register(b1, space0);

Texture2DArray g_albedo     : register(t0, space0);
Texture2DArray g_mr         : register(t2, space0);
Texture2DArray g_normal_map : register(t3, space0);
Texture2DArray g_emissive   : register(t4, space0);
Texture2DArray g_occlusion  : register(t15, space0);
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

float3 perturb_normal(float3 world, float3 n, float2 uv, float layer) {
    float3 map = g_normal_map.Sample(g_smp3, float3(uv, layer)).rgb * 2.0f - 1.0f;
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
           float2 velocity : TEXCOORD3,
           nointerpolation uint layer_id : TEXCOORD4) {
    PSOut o;
    uint li = min(layer_id, 63u);
    float layer = (float)li;
    float4 fac  = g_factors.u_factor_arr[li];
    float4 efac = g_factors.u_emissive_arr[li];
    float3 base  = g_albedo.Sample(g_smp0, float3(uv, layer)).rgb;
    float2 mr    = g_mr.Sample(g_smp2, float3(uv, layer)).bg;
    float2 mrf   = mr * fac.xy;
    float  metal = clamp(mrf.x, 0.0f, 1.0f);
    float  rough = clamp(mrf.y, 0.04f, 1.0f);
    float  ao    = lerp(1.0f, g_occlusion.Sample(g_smp15, float3(uv, layer)).r,
                        clamp(fac.z, 0.0f, 1.0f));
    float3 emis  = g_emissive.Sample(g_smp4, float3(uv, layer)).rgb * efac.rgb;

    o.albedo_metallic = float4(base, metal);
    float3 nrm = perturb_normal(world, normalize(normal), uv, layer);
    o.normal       = float4(octahedron_encode(nrm), 0.0f, 1.0f);
    o.roughness_ao = float4(rough, ao, clamp(fac.w, 0.0f, 1.0f), 1.0f);
    o.emissive     = float4(emis, 1.0f);
    o.velocity     = float4(velocity, 0.0f, 1.0f);
    return o;
}
