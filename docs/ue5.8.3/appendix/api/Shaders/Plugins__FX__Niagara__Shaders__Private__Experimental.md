# Shaders / Plugins/FX/Niagara/Shaders/Private/Experimental

- files: 1; lines: 272
- record kinds: define=4, function=7, include=1, member=6, struct=1

### `Plugins/FX/Niagara/Shaders/Private/Experimental/NiagaraUvMappingUtils.ush` (Private)

- lines: 272; parse: all-branches
- includes: L5 `/Plugin/FX/Niagara/Private/NiagaraBaryCentricUtils.ush`

#### Macros (#define, 4)

- L17 `#define UvMapping_ElementCountOffset 4`
- L18 `#define UvMapping_TriangleIndexOffset 5`
- L19 `#define UvMapping_MinValidUvMappingBufferSize 24`
- L31 `#define AXIS_COUNT 3`
- L3 #pragma `once`

#### Structs / classes (1)

- L7-15 _struct_ **`UvMappingParameters`** `struct UvMappingParameters`
  - L9 _member_ `int NumUVs;`
  - L10 _member_ `Buffer<uint> IndexBuffer;`
  - L11 _member_ `Buffer<float2> UVBuffer;`
  - L12 _member_ `Buffer<int> UvMappingBuffer;`
  - L13 _member_ `uint UvMappingBufferLength;`
  - L14 _member_ `uint UvMappingSet;`

#### Functions (7)

- L21-48 _function_ `bool UvMapping_NormalizedAabbTriangleIntersection(float2 A, float2 B, float2 C)`
- L51-79 _function_ `bool UvMapping_QuadTreeTriangleOverlap( UvMappingParameters MappingParam, float2 Uv, float Tolerance, int TriangleIndex, out float3 OutBaryCoord)` — Evaluates QuadTree for a single point
- L81-108 _function_ `bool UvMapping_QuadTreeNodeContains( UvMappingParameters MappingParam, int NodeBufferOffset, float2 Uv, float Tolerance, out int OutTriangleIndex, out float3 OutBaryCoord)`
- L110-151 _function_ `void UvMapping_GetTriangleCoordAtUV( UvMappingParameters MappingParam, bool Enabled, float2 InUv, float InTolerance, out int OutTriangle, out float3 OutBaryCoord, out bool OutIsValid)`
- L154-188 _function_ `bool UvMapping_QuadTreeTriangleAabbOverlap( UvMappingParameters MappingParam, float2 UvRef, float2 UvExtentScale, float2 UvExtentBias, int TriangleIndex, out float3 OutBaryCoord)` — Evaluates QuadTree for an AABB region
- L190-228 _function_ `bool UvMapping_QuadTreeNodeContainsAabb( UvMappingParameters MappingParam, int NodeBufferOffset, float2 UvMin, float2 UvMax, out int OutTriangleIndex, out float3 OutBaryCoord)`
- L230-272 _function_ `void UvMapping_GetTriangleCoordInAabb( UvMappingParameters MappingParam, bool Enabled, float2 InUvMin, float2 InUvMax, out int OutTriangle, out float3 OutBaryCoord, out bool OutIsValid)`
