// font_hlsl.frag - coverage-alpha glyph PS (D3D12 sidecar of
// shaders/font.frag). The atlas stores raw coverage (R=G=B=255, A = stbtt
// coverage), so only .a is read; solid rects use a white patch with A=255.
Texture2D g_atlas : register(t0, space0);
SamplerState g_smp : register(s0, space0);
float4 main(float4 pos : SV_Position, float2 uv : TEXCOORD0,
            float4 color : COLOR0) : SV_Target {
    float cov = g_atlas.Sample(g_smp, uv).a;
    return float4(color.rgb, color.a * cov);
}
