// ui_img_hlsl.frag - tinted image PS (D3D12 sidecar of shaders/ui_img.frag).
Texture2D g_image : register(t0, space0);
SamplerState g_smp : register(s0, space0);
float4 main(float4 pos : SV_Position, float2 uv : TEXCOORD0,
            float4 color : COLOR0) : SV_Target {
    return g_image.Sample(g_smp, uv) * color;
}
