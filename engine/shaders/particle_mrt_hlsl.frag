// particle_mrt_hlsl.frag - D3D12 sidecar of shaders/particle.frag with
// FORWARD_MRT. uv is the quad's gl_PointCoord (particle_mrt_hlsl.vert).
struct PSOut {
    float4 color : SV_Target0;
    float2 velocity : SV_Target1;
};
PSOut main(float4 pos : SV_Position, float4 color : COLOR0,
           float2 uv : TEXCOORD0, float2 velocity : TEXCOORD1) {
    PSOut o;
    float2 coord = uv - 0.5;
    float dist = dot(coord, coord);
    if (dist > 0.25) discard;
    float alpha = 1.0 - smoothstep(0.1, 0.25, dist);
    o.color = float4(color.rgb, color.a * alpha);
    o.velocity = o.color.a > 0.01 ? velocity : float2(0.0, 0.0);
    return o;
}
