// post_tex_hlsl.frag - plain textured fullscreen copy (D3D12 sidecar of
// shaders/post_tex.frag). This is PostProcess.tex_pipe, the pass main.c uses
// for the final blit of the post chain onto the swapchain, so without it the
// D3D12 back buffer is never written and the frame is black.
Texture2D g_texture : register(t0, space0);
SamplerState g_smp : register(s0, space0);
float4 main(float4 pos : SV_Position, float2 uv : TEXCOORD0) : SV_Target {
    return g_texture.Sample(g_smp, uv);
}
