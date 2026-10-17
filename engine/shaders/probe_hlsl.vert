// probe_hlsl.vert - minimal D3D12 rasterisation probe sidecar.
// Deliberately declares NO register(...) bindings and NO uniform block:
// a green full-screen triangle straight from SV_VertexID. Its only job is to
// answer one question in isolation - can this backend rasterise and present
// geometry at all, without push constants or descriptor tables in the way?
struct VSOut { float4 pos : SV_Position; };
VSOut main(uint vid : SV_VertexID) {
    // Oversized triangle covering the whole viewport: vid 0 -> (-1,-1),
    // vid 1 -> (3,-1), vid 2 -> (-1,3).
    float2 p = float2((float)(vid & 1u) * 4.0 - 1.0,
                      (float)(vid >> 1u) * 4.0 - 1.0);
    VSOut o;
    o.pos = float4(p, 0.0, 1.0);
    return o;
}
