// myui_hlsl.frag — myui passthrough PS (D3D12 hand-authored sidecar):
// sampled texture modulated by the vertex color.
Texture2D g_tex : register(t0, space0);
SamplerState g_smp : register(s0, space0);
float4 main(float4 pos : SV_Position, float2 uv : TEXCOORD0,
            float4 color : COLOR0) : SV_Target {
    return g_tex.Sample(g_smp, uv) * color;
}
