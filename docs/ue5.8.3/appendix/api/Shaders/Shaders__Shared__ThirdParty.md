# Shaders / Shaders/Shared/ThirdParty

- files: 1; lines: 100
- record kinds: function=3

### `Shaders/Shared/ThirdParty/RayTriangleIntersection.h` (Shared)

- lines: 100; parse: all-branches
- L2 #pragma `once`

#### Functions (3)

- L5-36 _function_ `bool RayTriangleIntersectionMollerTrumbore(float3 RayOrigin, float3 RayDirection, float3 Vertex0, float3 Vertex1, float3 Vertex2, out float IntersectionT, out float2 Barycentrics)` — "Fast, minimum storage ray-triangle intersection" Moller-Trumbore, 1997
- L39-42 _function_ `uint MaxDimension(float3 V)` — "Watertight Ray/Triangle Intersection" Woop, Benthin and Wald 2013
- L44-100 _function_ `bool RayTriangleIntersectionWatertight(float3 RayOrigin, float3 RayDirection, float3 Vertex0, float3 Vertex1, float3 Vertex2, out float IntersectionT, out float2 Barycentrics)`
