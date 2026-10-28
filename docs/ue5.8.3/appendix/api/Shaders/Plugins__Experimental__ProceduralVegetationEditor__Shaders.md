# Shaders / Plugins/Experimental/ProceduralVegetationEditor/Shaders

- files: 3; lines: 743
- record kinds: cpp_binding=4, define=5, entry=4, function=16, include=3, member=44, parameter=14, resource=17, struct=8

### `Plugins/Experimental/ProceduralVegetationEditor/Shaders/PVLightDetectionCS.usf` (Other)

- lines: 538; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`

#### Macros (#define, 4)

- L4 `#define COLLISION_MAX_DISTANCE 999999`
- L5 `#define COLLISION_TYPE_CARD 0`
- L6 `#define COLLISION_TYPE_CYLINDER 1`
- L7 `#define EPSILON 1e-6`

#### Entry points (1)

- L468-537 _entry_ `[numthreads(64,1,1)] void MainCS(uint3 DTid : SV_DispatchThreadID, uint3 GTid : SV_GroupThreadID, uint3 Gid : SV_GroupID)` — stage: **compute** — C++: `FPVLightDetectionCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Implementations/PVLightDetection.cpp:16) — 2D dispatch: (min(N,65535), ceil(N/65535), 1) groups x [64,1,1] threads. One group = one skeleton point; threads within the group = 64 rays.

#### Structs / classes (6)

- L9-14 _struct_ **`PVRaycastOrigin`** `struct PVRaycastOrigin`
  - L11 _member_ `int PointNumber;`
  - L12 _member_ `int BranchNumber;`
  - L13 _member_ `float3 Position;`
- L16-25 _struct_ **`PVCollisionData`** `struct PVCollisionData`
  - L18 _member_ `int PointNumber;`
  - L19 _member_ `int BranchNumber;`
  - L20 _member_ `int ApicalRay;`
  - L21 _member_ `int Type;`
  - L22 _member_ `float3 Position;`
  - L23 _member_ `float3 Direction;`
  - L24 _member_ `float3 Extents;`
- L27-35 _struct_ **`PVLightDetectionData`** `struct PVLightDetectionData`
  - L29 _member_ `int PointNumber;`
  - L30 _member_ `int RayNumber;`
  - L31 _member_ `float3 Direction;`
  - L32 _member_ `float LightValue;`
  - L33 _member_ `int Hits;`
  - L34 _member_ `int FaliureType;`
- L39-45 _struct_ **`PVMeshGeometryRange`** `struct PVMeshGeometryRange` — Object-space geometry for one unique static mesh, shared across all instances. Must match FPVMeshGeometryRange in PVLightDetection.h (16 bytes).
  - L41 _member_ `int StartVertex;`
  - L42 _member_ `int EndVertex;`
  - L43 _member_ `int StartIndex;`
  - L44 _member_ `int EndIndex;`
- L49-58 _struct_ **`PVMeshInstanceData`** `struct PVMeshInstanceData` — One placed instance: references shared geometry and carries its own transform + world AABB. Must match FPVMeshInstanceData in PVLightDetection.h (112 bytes).
  - L51 _member_ `float4x4 Transform;` — object-to-world  (64 bytes)
  - L52 _member_ `float4 AABBMin;` — world-space AABB  (16 bytes, w unused)
  - L53 _member_ `float4 AABBMax;` — world-space AABB  (16 bytes, w unused)
  - L54 _member_ `int GeometryIndex;` — ( 4 bytes)
  - L55 _member_ `int _Pad0;` — (12 bytes padding)
  - L56 _member_ `int _Pad1;`
  - L57 _member_ `int _Pad2;`
- L63-72 _struct_ **`PVLeafMeshInstanceData`** `struct PVLeafMeshInstanceData` — One placed leaf instance: same layout as PVMeshInstanceData but carries a BranchNumber so the shader can skip leaves that belong to the same branch as the ray-cast origin. Must match FPVLeafMeshInstanceData in PVLightDetection.h (112 bytes).
  - L65 _member_ `float4x4 Transform;` — object-to-world  (64 bytes)
  - L66 _member_ `float4 AABBMin;` — world-space AABB  (16 bytes, w unused)
  - L67 _member_ `float4 AABBMax;` — world-space AABB  (16 bytes, w unused)
  - L68 _member_ `int GeometryIndex;` — ( 4 bytes)
  - L69 _member_ `int BranchNumber;` — ( 4 bytes)
  - L70 _member_ `int _Pad0;` — ( 8 bytes padding)
  - L71 _member_ `int _Pad1;`

#### Global resources (textures / buffers / samplers) (9)

- L80 _resource_ `StructuredBuffer<PVRaycastOrigin> RaycastOrigins;`
- L81 _resource_ `StructuredBuffer<PVCollisionData> CollisionData;`
- L82 _resource_ `StructuredBuffer<float3> Rays;`
- L83 _resource_ `StructuredBuffer<PVMeshGeometryRange> MeshGeometries;`
- L84 _resource_ `StructuredBuffer<PVMeshInstanceData> MeshInstances;`
- L85 _resource_ `StructuredBuffer<PVLeafMeshInstanceData> LeafInstances;`
- L86 _resource_ `StructuredBuffer<float3> ColliderMeshVertices;`
- L87 _resource_ `StructuredBuffer<uint> ColliderMeshIndices;`
- L88 _resource_ `RWStructuredBuffer<PVLightDetectionData> LightDetectionData;`

#### Global parameters (uniforms) (6)

- L74 _parameter_ `uint NumCollisionData;`
- L75 _parameter_ `uint MaxBounce;`
- L76 _parameter_ `uint NumRaycastOrigins;`
- L77 _parameter_ `uint NumInstances;`
- L78 _parameter_ `uint NumGeometries;`
- L79 _parameter_ `uint NumLeafInstances;`

#### Functions (13)

- L109-116 _function_ `float InvariantDot3(float3 A, float3 B)` — Vendor-stable dot / cross used only by RayTriangleHit's sign predicates. 'precise' binds the HLSL compiler (no algebraic reordering, no FMA fusion in the IR), but each vendor's driver still gets to lower DXIL 'dp3'/'cross' into whatever FMA chain it prefers — and the spec doesn't pin the bit-exact order. For a ray grazing a leaf-edge, the values DdN / DdQxE2 / DdE1xQ / QdN sit at a few ULP from zero, where that driver freedom flips the >0 / >=0 result across machines.  Once one ray's hit-or-miss disagrees the bounce path diverges, Hits/LightValue diverge, downstream growth diverges visibly. En
- L118-124 _function_ `float3 InvariantCross3(float3 A, float3 B)`
- L141-147 _function_ `float3 InvariantTransformPosition(float3 P, float4x4 M)` — Bit-exact equivalent of 'mul(float4(P, 1.0f), M).xyz' (UE row-vector * matrix convention) with the accumulation order pinned.  Used to transform mesh/leaf collider vertices into world space before the ray-triangle test.
- L151-157 _function_ `float3 InvariantMad3(float3 A, float B, float3 C)` — Pinned 'A * B + C' (scalar B) — blocks the compiler from picking a per-vendor FMA for vector multiply-adds (PB, HitPosition, Closest, bounce position).
- L170-180 _function_ `float PVStableSqrt(float X)` — Vendor-stable fp32 sqrt.  The D3D spec only requires 'sqrt' to be accurate to +/-1 ULP — it is NOT correctly rounded — so two GPU vendors legitimately return values 1 ULP apart.  That is the entire remaining divergence: the ray-miss path has no sqrt and is already bit-identical across machines, but the moment a ray hits geometry the cylinder discriminant and the hit-normal normalize introduce sqrt, and the 1-ULP disagreement compounds through the bounce reflections. 'precise'/INVARIANT cannot fix this — they pin op *order*, not the accuracy of an intrinsic.  One Heron correction step from the 
- L186-195 _function_ `float3 InvariantNormalize(float3 V)` — Deterministic normalize.  HLSL 'normalize' lowers to mul(v, rsqrt(dot(v,v))) and 'rsqrt' is a vendor approximation, so we build the unit vector from a vendor-stable sqrt + correctly-rounded divide instead.  Returns 0 for a degenerate input rather than propagating NaN (NaN comparisons are themselves a divergence risk).
- L199-206 _function_ `float3 InvariantReflect(float3 I, float3 N)` — Pinned reflect: I - 2*dot(I,N)*N.  The reflected direction is the next bounce's ray, so a ULP here flips which triangle/cylinder the next bounce hits.
- L210-217 _function_ `bool RayAABBHit(float3 RayOrigin, float3 InvRayDir, float3 BoxMin, float3 BoxMax, float TMax)` — Fast axis-aligned bounding box slab test. Returns true if the ray [RayOrigin, +inf) hits the box before TMax.
- L229-288 _function_ `bool RayTriangleHit(float3 RayOrigin, float3 RayDir, float3 Vert0, float3 Vert1, float3 Vert2, inout float t, inout float3 HitPos, inout float3 HitNormal)` — This function is the HLSL translation of FindIntersection in IterRay3Triangle3.h Cross-vendor determinism: the dot/cross used to compute DdN, DdQxE2, DdE1xQ, QdN are routed through InvariantDot3 / InvariantCross3, and the multiply by Sign plus the b1+b2 sum go through INVARIANT_MUL / INVARIANT_ADD.  This is the engine's standard pattern for "I need this comparison to agree on every machine" — see Platform.ush:836-856 and how DoubleFloatOperations.ush uses it for Kahan summation.  The values themselves are unchanged; only their evaluation order is pinned, which stops driver-level FMA fusion fro
- L293-328 _function_ `bool RayInstanceGeometryHit( float3 RayOrigin, float3 RayDir, float3 InvRayDir, float4x4 Transform, float3 AABBMin, float3 AABBMax, int GeometryIndex, inout float tOut, inout float3 HitPos, inout float3 HitNormal)` — AABB slab test followed by a triangle loop for a single mesh instance. InvRayDir is precomputed by the caller and shared across all instance calls. tOut is inout so successive calls automatically track the globally closest hit.
- L334-361 _function_ `bool RayMeshHit(float3 RayOrigin, float3 RayDir, int RayBranchNumber, out float tOut, out float3 HitPos, out float3 HitNormal)` — Tests the ray against all external collider instances and all leaf instances. Leaf instances on the same branch as the ray origin are skipped. Both loops share tOut so the closest hit across all instance types wins automatically, and the leaf AABB tests benefit from any closer hit already found in the collider loop.
- L363-416 _function_ `bool RayCylinderHit(float3 RayOrigin, float3 RayDirection, PVCollisionData Data, inout float t, inout float3 Normal, inout int FalureType)`
- L418-464 _function_ `bool RayHit(float3 RayOrigin, int RayBranchNumber, float3 RayDirection, out float tOut, out float3 NormalOut, out int FalureType)`

### `Plugins/Experimental/ProceduralVegetationEditor/Shaders/PVLightVectorCalculationCS.usf` (Other)

- lines: 155; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`

#### Macros (#define, 1)

- L29 `#define PV_EPSILON 1e-6`

#### Entry points (1)

- L68-154 _entry_ `[numthreads(1,1,1)] void MainCS(uint3 DTid : SV_DispatchThreadID, uint3 GTid : SV_GroupThreadID, uint3 Gid : SV_GroupID)` — stage: **compute** — C++: `FPVLightVectorCalculationCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Implementations/PVLightDetection.cpp:17) — 2D dispatch: (min(N,65535), ceil(N/65535), 1) groups x [1,1,1] threads. One thread = one skeleton point; reads all 64 ray results for that point.

#### Structs / classes (2)

- L4-12 _struct_ **`PVLightDetectionData`** `struct PVLightDetectionData`
  - L6 _member_ `int PointNumber;`
  - L7 _member_ `int RayNumber;`
  - L8 _member_ `float3 Direction;`
  - L9 _member_ `float LightValue;`
  - L10 _member_ `int Hits;`
  - L11 _member_ `int FaliureType;`
- L14-20 _struct_ **`PVPointLightVectorData`** `struct PVPointLightVectorData`
  - L16 _member_ `int PointNumber;`
  - L17 _member_ `float LightAvailable;`
  - L18 _member_ `float3 LightOptimalDirection;`
  - L19 _member_ `float3 LightSubOptimalDirection;`

#### Global resources (textures / buffers / samplers) (3)

- L25 _resource_ `StructuredBuffer<PVLightDetectionData> LightDetectionData;`
- L26 _resource_ `StructuredBuffer<float3> Rays;`
- L27 _resource_ `RWStructuredBuffer<PVPointLightVectorData> PointLightVectorData;`

#### Global parameters (uniforms) (3)

- L22 _parameter_ `uint MaxBounce;`
- L23 _parameter_ `uint NumRays;`
- L24 _parameter_ `uint NumPoints;`

#### Functions (3)

- L35-45 _function_ `float PVStableSqrt(float X)` — Vendor-stable fp32 sqrt — see PVLightDetectionCS.usf. Hardware 'sqrt'/'rsqrt' are only +/-1 ULP (not correctly rounded) and differ across GPU vendors; one Heron correction from the hardware seed removes that dependence. This direction feeds the grower's phototropism, so a ULP here propagates into visibly different growth.
- L47-53 _function_ `float PVLenSq(float3 V)`
- L55-64 _function_ `float3 InvariantNormalize(float3 V)`

### `Plugins/Experimental/ProceduralVegetationEditor/Shaders/PVTrunkTextureSetupCS.usf` (Other)

- lines: 50; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`

#### Entry points (2)

- L16-32 _entry_ `[numthreads(8,8,1)] void DilationCS(uint3 DTid : SV_DispatchThreadID, uint3 GTid : SV_GroupThreadID, uint3 Gid : SV_GroupID)` — stage: **compute** — C++: `FPVTrunkTextureSetupDilationCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Implementations/PVTrunkTextureSetup.cpp:21)
- L34-49 _entry_ `[numthreads(8,8,1)] void ScaleCS(uint3 DTid : SV_DispatchThreadID, uint3 GTid : SV_GroupThreadID, uint3 Gid : SV_GroupID)` — stage: **compute** — C++: `FPVTrunkTextureSetupScaleCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Implementations/PVTrunkTextureSetup.cpp:22)

#### Global resources (textures / buffers / samplers) (5)

- L9 _resource_ `Texture2D<float4> Source;`
- L10 _resource_ `SamplerState SourceSampler;`
- L11 _resource_ `Texture2D<float4> SourceB;`
- L12 _resource_ `SamplerState SourceSamplerB;`
- L13 _resource_ `RWTexture2D<float4> Target;`

#### Global parameters (uniforms) (5)

- L4 _parameter_ `float OffsetX;`
- L5 _parameter_ `float TileX;`
- L6 _parameter_ `float TileY;`
- L7 _parameter_ `float ScaleX;`
- L14 _parameter_ `uint2 TargetSize;`
