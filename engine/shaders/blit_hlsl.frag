// blit_hlsl.frag — swapchain blit PS (D3D12 hand-authored sidecar).
// Convention: a sampled Texture2D tN pairs with SamplerState sN; the root
// signature generator emits the SRV range plus the matching static sampler.
Texture2D g_tex : register(t0, space0);
SamplerState g_smp : register(s0, space0);
float4 main(float4 pos : SV_Position, float2 uv : TEXCOORD0) : SV_Target {
    return g_tex.Sample(g_smp, uv);
}
