# Shaders / Shaders/Private/SceneCulling

- files: 3; lines: 504
- record kinds: cpp_binding=2, define=4, entry=2, function=18, include=17, member=13, parameter=11, resource=12, struct=3

### `Shaders/Private/SceneCulling/SceneCulling.ush` (Private)

- lines: 186; parse: all-branches
- includes: L5 `../Common.ush`, L7 `/Engine/Shared/SceneCullingDefinitions.h`, L8 `../BitPacking.ush`, L9 `../ByteBuffer.ush`

#### Macros (#define, 4)

- L12 `#define SCENE_CULL_EXPLICIT_BOUNDS_BITS_PER_ELEMENT (8u)`
- L113 `#define PCAF_ANY_CAST_SHADOW (1u << 0u)`
- L114 `#define PCAF_ANY_SKINNED_MESH (1u << 1u)`
- L115 `#define PCAF_ANY_RAYTRACING_FAR_FIELD (1u << 2u)`
- L3 #pragma `once`

#### Structs / classes (3)

- L17-26 _struct_ **`FSceneHiearchyCellData`** `struct FSceneHiearchyCellData` — Unpacked cell data.
  - L19 _member_ `uint3 LocalCellCoord;`
  - L20 _member_ `float3 LocalBoundsCenter;` — Bounds center is local to the cell block
  - L21 _member_ `float3 LocalBoundsExtent;`
  - L22 _member_ `uint BlockId;`
  - L23 _member_ `float MaxInstanceRadius;`
  - L25 _member_ `FCellBlockData BlockData;`
- L99-103 _struct_ **`FAabb`** `struct FAabb`
  - L101 _member_ `float3 Min;`
  - L102 _member_ `float3 Max;`
- L117-124 _struct_ **`FInstanceChunkAttributes`** `struct FInstanceChunkAttributes`
  - L119 _member_ `FAabb Aabb;`
  - L120 _member_ `float2 InstanceDrawDistanceMinMaxSquared;`
  - L121 _member_ `float MinAnimationMinScreenSize;`
  - L122 _member_ `float MaxInstanceRadius;`
  - L123 _member_ `uint AnyFlags;` — Flags that are true if _any_ of the instances/primitive meet the criteria

#### Global resources (textures / buffers / samplers) (7)

- L36 _resource_ `StructuredBuffer<uint> InstanceIds;`
- L37 _resource_ `StructuredBuffer<FCellBlockData> InstanceHierarchyCellBlockData;`
- L44 _resource_ `StructuredBuffer<FPackedCellHeader> InstanceHierarchyCellHeaders;`
- L69 _resource_ `StructuredBuffer<uint> InstanceHierarchyItemChunks;`
- L77 _resource_ `StructuredBuffer<uint> UsedChunkIdMask;`
- L85 _resource_ `ByteAddressBuffer ExplicitChunkBounds;`
- L86 _resource_ `StructuredBuffer<uint> ExplicitChunkCellIds;`

#### Global parameters (uniforms) (7)

- L29 _parameter_ `uint NumCellsPerBlockLog2;` — Make these compile time constants?
- L30 _parameter_ `uint LocalCellCoordMask;`
- L31 _parameter_ `uint CellBlockDimLog2;`
- L32 _parameter_ `int FirstLevel;`
- L33 _parameter_ `uint MaxCells;`
- L34 _parameter_ `uint NumAllocatedChunks;`
- L84 _parameter_ `uint bCullChunkViewDistance;`

#### Functions (12)

- L39-42 _function_ `FCellBlockData GetCellBlockData(uint BlockId)`
- L46-63 _function_ `FCellHeader UnpackCellHeader(FPackedCellHeader Packed)`
- L65-68 _function_ `FCellHeader GetCellHeader(uint CellId)`
- L71-74 _function_ `inline uint CellIndexToBlockId(uint CellIndex)`
- L79-82 _function_ `uint IsChunkUsed(uint ChunkId)`
- L88-97 _function_ `FPackedChunkAttributes LoadPackedExplicitChunkBounds(uint ChunkId)`
- L105-111 _function_ `FAabb UnpackAabb(uint2 Packed, uint BitsPerElement, float SizeScale = 1.0f)`
- L126-136 _function_ `FInstanceChunkAttributes UnpackInstanceChunkAttributes(FPackedChunkAttributes Packed, float AabbSizeScale = 1.0f, float RadiusScale = 1.0f)`
- L139-142 _function_ `FInstanceChunkAttributes LoadInstanceChunkAttributes(uint ChunkId, float AabbSizeScale = 1.0f, float RadiusScale = 1.0f)`
- L145-164 _function_ `FSceneHiearchyCellData GetSceneHiearchyCellData(uint CellId)`
- L166-171 _function_ `uint UnpackChunkInstanceCount(uint PackedItemChunkDesc, inout bool bOutIsRLEPackedChunk)`
- L173-185 _function_ `uint UnpackChunkInstanceId(bool bIsRLEPackedChunk, uint PackedItemChunkDesc, uint GroupThreadIndex)`

### `Shaders/Private/SceneCulling/SceneCullingBuildExplicitBounds.usf` (Private)

- lines: 209; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../SceneData.ush`, L5 `../WaveOpUtil.ush`, L6 `../ComputeShaderUtils.ush`, L7 `../ThreadGroupPrefixSum.ush`, L10 `../Visualization.ush`, L11 `../ShaderPrint.ush`, L13 `SceneCulling.ush`

#### Entry points (1)

- L149-206 _entry_ `[numthreads(NUM_THREADS_PER_GROUP, 1, 1)] void ComputeExplicitChunkBounds(uint3 GroupId : SV_GroupID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FComputeExplicitChunkBounds_CS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/SceneCulling/SceneCulling.cpp:705) _[#if defined(ComputeExplicitChunkBounds)]_

#### Global resources (textures / buffers / samplers) (3)

- L137 _resource_ `StructuredBuffer<uint2> DirtyChunkBoundsData;` _[#if defined(ComputeExplicitChunkBounds)]_
- L138 _resource_ `RWByteAddressBuffer OutExplicitChunkBoundsBuffer;` _[#if defined(ComputeExplicitChunkBounds)]_
- L139 _resource_ `RWStructuredBuffer<uint> OutExplicitChunkCellIdsBuffer;` _[#if defined(ComputeExplicitChunkBounds)]_

#### Global parameters (uniforms) (1)

- L136 _parameter_ `int DirtyChunkCount;` _[#if defined(ComputeExplicitChunkBounds)]_

#### Functions (6)

- L15-27 _function_ `FAabb TransformAABB(float4x4 Transform, float3 Center, float3 Extent)`
- L31-41 _function_ `uint2 PackNormToUint2(FAabb NormAabb, uint BitsPerElement)` — pack a normalized FInstanceChunkAttributes to an uint2, using BitsPerElement for each dimension rounds the upper bounds up, and the lower down to ensure conservative bounds.
- L45-56 _function_ `FPackedChunkAttributes PackNormToUint2(FInstanceChunkAttributes InstanceCellAttributes)` — pack a normalized FInstanceChunkAttributes to an uint2, using BitsPerElement for each dimension rounds the upper bounds up, and the lower down to ensure conservative bounds.
- L58-88 _function_ `FInstanceChunkAttributes ThreadGroupReduce(FInstanceChunkAttributes InstanceCellAttributes, uint GroupThreadIndex)`
- L90-132 _function_ `void ProcessInstance(uint InstanceId, FDFVector3 WorldToBlockRelativeTranslation, inout FInstanceChunkAttributes InOutAttributes)`
- L141-147 _function_ `void StorePackedExplicitChunkBounds(uint ChunkId, FPackedChunkAttributes PackedChunkAttributes)` _[#if defined(ComputeExplicitChunkBounds)]_

### `Shaders/Private/SceneCulling/SceneCullingDebugRender.usf` (Private)

- lines: 109; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../ComputeShaderUtils.ush`, L5 `../Visualization.ush`, L6 `../ShaderPrint.ush`, L8 `SceneCulling.ush`

#### Entry points (1)

- L16-108 _entry_ `[numthreads(NUM_THREADS_PER_GROUP, 1, 1)] void DebugRender(uint3 GroupId : SV_GroupID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FSceneCullingDebugRender_CS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/SceneCulling/SceneCullingRenderer.cpp:167)

#### Global resources (textures / buffers / samplers) (2)

- L10 _resource_ `StructuredBuffer<uint> ValidCellsMask;`
- L14 _resource_ `RWStructuredBuffer<uint> RWDrawCellInfoCounter;`

#### Global parameters (uniforms) (3)

- L11 _parameter_ `float3 PickingRayStart;`
- L12 _parameter_ `float3 PickingRayEnd;`
- L13 _parameter_ `uint DebugMode;`
