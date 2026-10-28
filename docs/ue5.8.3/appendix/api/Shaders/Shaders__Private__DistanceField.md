# Shaders / Shaders/Private/DistanceField

- files: 9; lines: 2452
- record kinds: cpp_binding=19, define=70, entry=19, function=52, groupshared=10, include=30, member=40, parameter=78, resource=76, struct=8

### `Shaders/Private/DistanceField/GlobalDistanceField.usf` (Private)

- lines: 696; parse: all-branches
- includes: L5 `../Common.ush`, L6 `../ComputeShaderUtils.ush`, L7 `../DeferredShadingCommon.ush`, L8 `../DistanceFieldLightingShared.ush`, L9 `../DistanceFieldAOShared.ush`, L10 `../MeshDistanceFieldCommon.ush`, L11 `GlobalDistanceFieldUpdate.ush`, L12 `GlobalDistanceFieldShared.ush`, L13 `GlobalDistanceFieldUtils.ush`

#### Macros (#define, 10)

- L3 `#define USE_DISTANCE_FIELD_SAMPLER 1`
- L16 `#define CULLOBJECTS_THREADGROUP_SIZE 1` _[#if !defined(CULLOBJECTS_THREADGROUP_SIZE)]_
- L20 `#define THREADGROUP_SIZE 1` _[#if !defined(THREADGROUP_SIZE)]_
- L24 `#define THREADGROUP_SIZE_X 1` _[#if !defined(THREADGROUP_SIZE_X)]_
- L25 `#define THREADGROUP_SIZE_Y 1` _[#if !defined(THREADGROUP_SIZE_X)]_
- L26 `#define THREADGROUP_SIZE_Z 1` _[#if !defined(THREADGROUP_SIZE_X)]_
- L80 `#define CULL_GRID_FACTOR 4`
- L81 `#define GRID_CULL_THREADGROUP_TOTALSIZE 256`
- L203 `#define MAX_CULLED_TILES 511u` _[#if defined(BuildGridTilesCS)]_
- L394 `#define PROCESS_DISTANCE_FIELDS 0` _[#if defined(AllocatePagesCS) && !defined(PROCESS_DISTANCE_FIELDS)]_

#### Entry points (8)

- L103-152 _entry_ `[numthreads(CULLOBJECTS_THREADGROUP_SIZE, 1, 1)] void CullObjectsToClipmapCS( uint GroupIndex : SV_GroupIndex, uint3 GroupId : SV_GroupID)` — stage: **compute** — C++: `FCullObjectsToClipmapCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/GlobalDistanceField.cpp:1505) _[#if defined(CullObjectsToClipmapCS)]_
- L164-178 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void ClearIndirectArgBufferCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FClearIndirectArgBufferCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/GlobalDistanceField.cpp:1536) _[#if defined(ClearIndirectArgBufferCS)]_
- L248-340 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, THREADGROUP_SIZE)] void BuildGridTilesCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FBuildGridTilesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/GlobalDistanceField.cpp:1579) — Run two pass culling to find out which cull and page tiles need to be updated. First cull into cull tiles, then cull into pages tiles. Every cull tile consists out of 4x4x4 (CULL_GRID_FACTOR) page tiles. _[#if defined(BuildGridTilesCS)]_
- L350-367 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void InitPageFreeListCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FInitPageFreeListCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/GlobalDistanceField.cpp:1755) _[#if defined(InitPageFreeListCS)]_
- L397-561 _entry_ `[numthreads(THREADGROUP_SIZE_X, 1, 1)] void AllocatePagesCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FAllocatePagesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/GlobalDistanceField.cpp:1837) _[#if defined(AllocatePagesCS)]_
- L571-584 _entry_ `[numthreads(1, 1, 1)] void PageFreeListReturnIndirectArgBufferCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FPageFreeListReturnIndirectArgBufferCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/GlobalDistanceField.cpp:1864) _[#if defined(PageFreeListReturnIndirectArgBufferCS)]_
- L590-605 _entry_ `[numthreads(THREADGROUP_SIZE_X, 1, 1)] void PageFreeListReturnCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FPageFreeListReturnCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/GlobalDistanceField.cpp:1898) _[#if defined(PageFreeListReturnCS)]_
- L620-693 _entry_ `[numthreads(GRID_CULL_THREADGROUP_TOTALSIZE, 1, 1)] void CullObjectsToGridCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FCullObjectsToGridCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/GlobalDistanceField.cpp:1617) _[#if defined(CullObjectsToGridCS)]_

#### Structs / classes (2)

- L30-42 _struct_ **`FPackedClipmapData`** `struct FPackedClipmapData` — Must match FPackedClipmapData in GlobalDistanceField.cpp
  - L32 _member_ `float3 TranslatedWorldCenter;` — Camera-centered world space
  - L33 _member_ `float MeshSDFRadiusThreshold;`
  - L35 _member_ `float3 WorldExtent;`
  - L36 _member_ `float InfluenceRadiusSq;`
  - L38 _member_ `uint ClipmapIndex;`
  - L39 _member_ `uint Flags;`
  - L40 _member_ `uint Padding0;`
  - L41 _member_ `uint Padding1;`
- L44-54 _struct_ **`FPackedClipmap`** `struct FPackedClipmap`
  - L46 _member_ `float3 TranslatedWorldCenter;` — Camera-centered world space
  - L47 _member_ `float3 WorldExtent;`
  - L49 _member_ `float MeshSDFRadiusThreshold;`
  - L50 _member_ `float InfluenceRadiusSq;`
  - L52 _member_ `uint ClipmapIndex;` — Global index
  - L53 _member_ `bool bReadbackHasPendingStreaming;`

#### Global resources (textures / buffers / samplers) (35)

- L56 _resource_ `StructuredBuffer<FPackedClipmapData> PackedClipmapBuffer;`
- L76 _resource_ `RWStructuredBuffer<uint> RWCullGridAllocator;`
- L77 _resource_ `RWStructuredBuffer<uint> RWCullGridObjectHeader;`
- L78 _resource_ `RWStructuredBuffer<uint> RWCullGridObjectArray;`
- L84 _resource_ `StructuredBuffer<uint> CullGridObjectHeader;`
- L85 _resource_ `StructuredBuffer<uint> CullGridObjectArray;`
- L87 _resource_ `RWStructuredBuffer<uint> RWObjectIndexBuffer;`
- L88 _resource_ `RWStructuredBuffer<uint> RWObjectIndexNumBuffer;`
- L90 _resource_ `RWStructuredBuffer<uint> RWHasPendingStreaming;`
- L156 _resource_ `RWBuffer<uint> RWPageComposeIndirectArgBuffer;`
- L157 _resource_ `RWBuffer<uint> RWPageUpdateIndirectArgBuffer;`
- L158 _resource_ `RWBuffer<uint> RWCullGridUpdateIndirectArgBuffer;`
- L159 _resource_ `RWBuffer<uint> RWBuildObjectGridIndirectArgBuffer;`
- L182 _resource_ `RWStructuredBuffer<uint> RWPageTileBuffer;`
- L183 _resource_ `RWBuffer<uint> RWPageIndirectArgBuffer;`
- L185 _resource_ `RWStructuredBuffer<uint> RWCullGridTileBuffer;`
- L186 _resource_ `RWBuffer<uint> RWCullGridIndirectArgBuffer;`
- L188 _resource_ `Buffer<float4> UpdateBoundsBuffer;`
- L344 _resource_ `RWStructuredBuffer<uint> RWPageFreeListBuffer;`
- L345 _resource_ `RWStructuredBuffer<int> RWPageFreeListAllocatorBuffer;`
- L373 _resource_ `RWTexture3D<uint> RWPageTableCombinedTexture;` _[#if defined(AllocatePagesCS)]_
- L374 _resource_ `RWTexture3D<uint> RWPageTableLayerTexture;` _[#if defined(AllocatePagesCS)]_
- L375 _resource_ `Texture3D<uint> ParentPageTableLayerTexture;` _[#if defined(AllocatePagesCS)]_
- L382 _resource_ `RWStructuredBuffer<uint> RWPageComposeTileBuffer;` _[#if defined(AllocatePagesCS)]_
- L384 _resource_ `RWStructuredBuffer<uint> RWPageFreeListReturnBuffer;` _[#if defined(AllocatePagesCS)]_
- L385 _resource_ `RWStructuredBuffer<uint> RWPageFreeListReturnAllocatorBuffer;` _[#if defined(AllocatePagesCS)]_
- L387 _resource_ `StructuredBuffer<uint> MarkedHeightfieldPageBuffer;` _[#if defined(AllocatePagesCS)]_
- L388 _resource_ `StructuredBuffer<uint> PageUpdateTileBuffer;` _[#if defined(AllocatePagesCS)]_
- L389 _resource_ `StructuredBuffer<uint> PageFreeListBuffer;` _[#if defined(AllocatePagesCS)]_
- L565 _resource_ `StructuredBuffer<uint> PageFreeListReturnAllocatorBuffer;`
- L566 _resource_ `StructuredBuffer<uint> PageFreeListReturnBuffer;`
- L567 _resource_ `RWBuffer<uint> RWFreeListReturnIndirectArgBuffer;`
- L614 _resource_ `StructuredBuffer<uint> ObjectIndexBuffer;` _[#if defined(CullObjectsToGridCS)]_
- L615 _resource_ `StructuredBuffer<uint> ObjectIndexNumBuffer;` _[#if defined(CullObjectsToGridCS)]_
- L616 _resource_ `StructuredBuffer<uint> CullGridTileBuffer;` _[#if defined(CullObjectsToGridCS)]_

#### Global parameters (uniforms) (22)

- L83 _parameter_ `uint3 UpdateRegionSize;`
- L93 _parameter_ `float3 PreViewTranslationHigh;`
- L94 _parameter_ `float3 PreViewTranslationLow;`
- L97 _parameter_ `uint AcceptOftenMovingObjectsOnly;` — 0: accept only mostly static objects, 1: accept only often moving objects, 2: accept all objects
- L98 _parameter_ `uint NumPackedClipmaps;`
- L99 _parameter_ `uint ObjectIndexBufferStride;`
- L189 _parameter_ `uint NumUpdateBounds;`
- L190 _parameter_ `float InfluenceRadiusSq;`
- L192 _parameter_ `uint3 CullGridResolution;`
- L193 _parameter_ `float3 CullGridCoordToTranslatedWorldCenterScale;`
- L194 _parameter_ `float3 CullGridCoordToTranslatedWorldCenterBias;`
- L195 _parameter_ `float3 CullGridTileWorldExtent;`
- L197 _parameter_ `float3 PageGridCoordToTranslatedWorldCenterScale;`
- L198 _parameter_ `float3 PageGridCoordToTranslatedWorldCenterBias;`
- L199 _parameter_ `float3 PageGridTileWorldExtent;`
- L346 _parameter_ `uint GlobalDistanceFieldMaxPageNum;`
- L377 _parameter_ `float3 InvPageGridResolution;` _[#if defined(AllocatePagesCS)]_
- L378 _parameter_ `float3 PageWorldExtent;` _[#if defined(AllocatePagesCS)]_
- L379 _parameter_ `float PageWorldRadius;` _[#if defined(AllocatePagesCS)]_
- L380 _parameter_ `float ClipmapInfluenceRadius;` _[#if defined(AllocatePagesCS)]_
- L617 _parameter_ `float3 CullTileWorldExtent;` _[#if defined(CullObjectsToGridCS)]_
- L618 _parameter_ `uint PackedClipmapIndex;` _[#if defined(CullObjectsToGridCS)]_

#### groupshared (6)

- L204 _groupshared_ `groupshared uint SharedCulledBoundsList[MAX_CULLED_TILES];` _[#if defined(BuildGridTilesCS)]_
- L205 _groupshared_ `groupshared uint SharedNumCulledBounds;` _[#if defined(BuildGridTilesCS)]_
- L208 _groupshared_ `groupshared uint SharedCullGridMask[2];` — 4x4x4 bitmask with occupied cells _[#if defined(BuildGridTilesCS)]_
- L391 _groupshared_ `groupshared float GroupMinPageDistance[64];` _[#if defined(AllocatePagesCS)]_
- L611 _groupshared_ `groupshared uint NumObjectsGridCell;` _[#if defined(CullObjectsToGridCS)]_
- L612 _groupshared_ `groupshared uint GridCellStartOffset;` _[#if defined(CullObjectsToGridCS)]_

#### Functions (4)

- L58-74 _function_ `FPackedClipmap GetPackedClipmap(uint PackedClipmapIndex)`
- L210-222 _function_ `void SetSharedCullGridMaskBit(uint3 LocalGridCoord)` _[#if defined(BuildGridTilesCS)]_
- L224-236 _function_ `bool IsSharedCullGridMaskBitSet(uint3 LocalGridCoord)` _[#if defined(BuildGridTilesCS)]_
- L238-241 _function_ `bool IsAnySharedCullGridMaskBitSet()` _[#if defined(BuildGridTilesCS)]_

### `Shaders/Private/DistanceField/GlobalDistanceFieldCompositeObjects.usf` (Private)

- lines: 367; parse: all-branches
- includes: L5 `../Common.ush`, L6 `../DeferredShadingCommon.ush`, L7 `../DistanceFieldLightingShared.ush`, L8 `../MeshDistanceFieldCommon.ush`, L9 `GlobalDistanceFieldUpdate.ush`, L10 `GlobalDistanceFieldShared.ush`, L11 `GlobalDistanceFieldUtils.ush`, L12 `GlobalDistanceFieldObjectGrid.ush`

#### Macros (#define, 4)

- L3 `#define USE_DISTANCE_FIELD_SAMPLER 1`
- L15 `#define MAX_CULLED_DF_OBJECTS 511u`
- L19 `#define USE_CULL_GRID 1`
- L126 `#define USE_OBJECT_COMPOSITING_TILE_CULLING 1` _[#if PROCESS_DISTANCE_FIELDS]_
- L125 #undef `USE_OBJECT_COMPOSITING_TILE_CULLING`

#### Entry points (2)

- L78-257 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, THREADGROUP_SIZE)] void CompositeObjectsIntoPagesCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FCompositeObjectsIntoPagesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/GlobalDistanceField.cpp:1725)
- L261-367 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, THREADGROUP_SIZE)] void CompositeObjectsIntoObjectGridPagesCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FCompositeObjectsIntoObjectGridPagesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/GlobalDistanceField.cpp:1680)

#### Global resources (textures / buffers / samplers) (10)

- L21 _resource_ `RWTexture3D<UNORM float> RWPageAtlasTexture;`
- L22 _resource_ `RWTexture3D<UNORM float> RWCoverageAtlasTexture;`
- L24 _resource_ `Texture3D<uint> PageTableLayerTexture;`
- L25 _resource_ `RWTexture3D<uint> RWPageTableCombinedTexture;`
- L26 _resource_ `Texture3D<uint> ParentPageTableLayerTexture;`
- L28 _resource_ `StructuredBuffer<uint> ComposeTileBuffer;`
- L29 _resource_ `StructuredBuffer<uint> PageTileBuffer;`
- L42 _resource_ `StructuredBuffer<uint> CullGridObjectHeader;`
- L43 _resource_ `StructuredBuffer<uint> CullGridObjectArray;`
- L259 _resource_ `RWStructuredBuffer<uint4> RWPageObjectGridBuffer;`

#### Global parameters (uniforms) (11)

- L30 _parameter_ `float InfluenceRadius;`
- L31 _parameter_ `float InfluenceRadiusSq;`
- L32 _parameter_ `uint3 ClipmapResolution;`
- L33 _parameter_ `float3 PageCoordToVoxelTranslatedCenterScale;`
- L34 _parameter_ `float3 PageCoordToVoxelTranslatedCenterBias;`
- L35 _parameter_ `float3 ComposeTileWorldExtent;`
- L36 _parameter_ `float3 ClipmapMinBounds;`
- L37 _parameter_ `float ClipmapVoxelExtent;`
- L39 _parameter_ `float3 PreViewTranslationHigh;`
- L40 _parameter_ `float3 PreViewTranslationLow;`
- L44 _parameter_ `uint3 CullGridResolution;`

#### groupshared (3)

- L16 _groupshared_ `groupshared uint SharedCulledObjectList[MAX_CULLED_DF_OBJECTS];`
- L17 _groupshared_ `groupshared uint NumTileCulledObjects;`
- L76 _groupshared_ `groupshared uint SharedCompositeMask;`

#### Functions (1)

- L46-74 _function_ `void CompositeMeshSDF(uint ObjectIndex, FDFVector3 VoxelWorldCenter, inout float MinDistance, inout bool bVoxelHasOneSidedMeshes, inout bool bVoxelHasTwoSidedMeshes)`

### `Shaders/Private/DistanceField/GlobalDistanceFieldDebug.usf` (Private)

- lines: 143; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../ShaderPrint.ush`, L5 `GlobalDistanceFieldShared.ush`, L6 `GlobalDistanceFieldUpdate.ush`

#### Macros (#define, 1)

- L9 `#define THREADGROUP_SIZE 0` _[#if !defined(THREADGROUP_SIZE)]_

#### Entry points (3)

- L28-38 _entry_ `[numthreads(1, 1, 1)] void GlobalDistanceFieldAccumulateUpdatedPagesCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FGlobalDistanceFieldAccumulateUpdatedPagesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/GlobalDistanceField.cpp:1963) _[#if defined(GlobalDistanceFieldAccumulateUpdatedPagesCS)]_
- L44-90 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, THREADGROUP_SIZE)] void GlobalDistanceFieldPageStatsCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FGlobalDistanceFieldPageStatsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/GlobalDistanceField.cpp:1997) _[#if defined(GlobalDistanceFieldPageStatsCS)]_
- L96-140 _entry_ `[numthreads(1, 1, 1)] void GlobalDistanceFieldDebugCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FGlobalDistanceFieldDebugCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/GlobalDistanceField.cpp:2035) _[#if defined(GlobalDistanceFieldDebugCS)]_

#### Global resources (textures / buffers / samplers) (7)

- L12 _resource_ `StructuredBuffer<uint> GlobalDistanceFieldPageFreeListAllocatorBuffer;`
- L18 _resource_ `RWStructuredBuffer<uint> RWPageStatsBuffer;`
- L19 _resource_ `StructuredBuffer<uint> PageStatsBuffer;`
- L20 _resource_ `Texture3D<uint> PageTableCombinedTexture;`
- L21 _resource_ `Texture3D PageAtlasTexture;`
- L22 _resource_ `SamplerState DistanceFieldSampler;`
- L24 _resource_ `Buffer<uint> PageComposeIndirectArgBuffer;`

#### Global parameters (uniforms) (4)

- L13 _parameter_ `uint GlobalDistanceFieldMaxPageNum;`
- L15 _parameter_ `uint ClipmapSizeInPages;`
- L16 _parameter_ `uint ClipmapIndex;`
- L17 _parameter_ `float3 InvPageAtlasSize;`

### `Shaders/Private/DistanceField/GlobalDistanceFieldHeightfields.usf` (Private)

- lines: 338; parse: all-branches
- includes: L5 `../Common.ush`, L6 `../HeightfieldLightingShared.ush`, L7 `GlobalDistanceFieldUpdate.ush`, L8 `GlobalDistanceFieldShared.ush`, L9 `GlobalDistanceFieldUtils.ush`, L10 `GlobalDistanceFieldObjectGrid.ush`

#### Macros (#define, 1)

- L3 `#define USE_DISTANCE_FIELD_SAMPLER 1`

#### Entry points (5)

- L103-183 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void MarkHeightfieldPagesCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FMarkHeightfieldPagesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/GlobalDistanceFieldHeightfields.h:58) _[#if defined(MarkHeightfieldPagesCS)]_
- L193-206 _entry_ `[numthreads(1, 1, 1)] void BuildHeightfieldComposeTilesIndirectArgBufferCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FBuildHeightfieldComposeTilesIndirectArgBufferCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/GlobalDistanceFieldHeightfields.h:83) _[#if defined(BuildHeightfieldComposeTilesIndirectArgBufferCS)]_
- L215-236 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void BuildHeightfieldComposeTilesCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FBuildHeightfieldComposeTilesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/GlobalDistanceFieldHeightfields.h:116) _[#if defined(BuildHeightfieldComposeTilesCS)]_
- L242-292 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void ComposeHeightfieldsIntoPagesCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FComposeHeightfieldsIntoPagesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/GlobalDistanceFieldHeightfields.h:170) _[#if defined(ComposeHeightfieldsIntoPagesCS)]_
- L300-335 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, THREADGROUP_SIZE)] void CompositeHeightfieldsIntoObjectGridPagesCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FCompositeHeightfieldsIntoObjectGridPagesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/GlobalDistanceFieldHeightfields.h:220) _[#if defined(CompositeHeightfieldsIntoObjectGridPagesCS)]_

#### Structs / classes (1)

- L31-37 _struct_ **`FHeightfieldSample`** `struct FHeightfieldSample`
  - L33 _member_ `bool bValid;`
  - L34 _member_ `uint HeightfieldIndex;`
  - L35 _member_ `float3 TranslatedWorldPosition;`
  - L36 _member_ `float3 WorldNormal;`

#### Global resources (textures / buffers / samplers) (12)

- L12 _resource_ `RWStructuredBuffer<uint> RWMarkedHeightfieldPageBuffer;`
- L13 _resource_ `RWTexture3D<UNORM float> RWPageAtlasTexture;`
- L14 _resource_ `RWTexture3D<UNORM float> RWCoverageAtlasTexture;`
- L16 _resource_ `StructuredBuffer<uint> MarkedHeightfieldPageBuffer;`
- L17 _resource_ `StructuredBuffer<uint> PageUpdateTileBuffer;`
- L18 _resource_ `StructuredBuffer<uint> ComposeTileBuffer;`
- L19 _resource_ `Texture3D<uint> PageTableLayerTexture;`
- L187 _resource_ `RWBuffer<uint> RWBuildHeightfieldComposeTilesIndirectArgBuffer;`
- L188 _resource_ `RWBuffer<uint> RWPageComposeHeightfieldIndirectArgBuffer;`
- L189 _resource_ `Buffer<uint> PageUpdateIndirectArgBuffer;`
- L213 _resource_ `RWStructuredBuffer<uint> RWPageComposeHeightfieldTileBuffer;` _[#if defined(BuildHeightfieldComposeTilesCS)]_
- L298 _resource_ `RWStructuredBuffer<uint4> RWPageObjectGridBuffer;` _[#if defined(CompositeHeightfieldsIntoObjectGridPagesCS)]_

#### Global parameters (uniforms) (9)

- L21 _parameter_ `float3 PageCoordToVoxelTranslatedCenterScale;`
- L22 _parameter_ `float3 PageCoordToVoxelTranslatedCenterBias;`
- L23 _parameter_ `float3 PageWorldExtent;`
- L24 _parameter_ `float3 InvPageGridResolution;`
- L25 _parameter_ `float ClipmapVoxelExtent;`
- L26 _parameter_ `float InfluenceRadius;`
- L27 _parameter_ `float HeightfieldThickness;`
- L28 _parameter_ `float3 PreViewTranslationHigh;`
- L29 _parameter_ `float3 PreViewTranslationLow;`

#### groupshared (1)

- L101 _groupshared_ `groupshared uint GroupMarkedPage[64];` _[#if defined(MarkHeightfieldPagesCS)]_

#### Functions (2)

- L39-81 _function_ `FHeightfieldSample SampleHeightfield(FDFVector3 PreViewTranslation, FDFVector3 VoxelWorldCenter, float VoxelWorldExtent)`
- L83-97 _function_ `float ComputeHeightfieldDistance(FHeightfieldSample HeightfieldSample, float3 TranslatedWorldPosition)`

### `Shaders/Private/DistanceField/GlobalDistanceFieldMip.usf` (Private)

- lines: 110; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../DeferredShadingCommon.ush`, L5 `GlobalDistanceFieldShared.ush`

#### Entry points (1)

- L78-110 _entry_ `[numthreads(THREADGROUP_SIZE_X, THREADGROUP_SIZE_Y, THREADGROUP_SIZE_Z)] void PropagateMipDistanceCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FPropagateMipDistanceCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/GlobalDistanceField.cpp:1945)

#### Global resources (textures / buffers / samplers) (5)

- L7 _resource_ `RWTexture3D<float> RWMipTexture;`
- L11 _resource_ `Texture3D<uint> PageTableTexture;`
- L12 _resource_ `Texture3D PageAtlasTexture;`
- L13 _resource_ `Texture3D PrevMipTexture;`
- L14 _resource_ `SamplerState DistanceFieldSampler;`

#### Global parameters (uniforms) (9)

- L8 _parameter_ `uint ClipmapMipResolution;`
- L9 _parameter_ `float OneOverClipmapMipResolution;`
- L10 _parameter_ `float MipInfluenceRadius;`
- L38 _parameter_ `uint ClipmapIndex;`
- L39 _parameter_ `uint PrevClipmapOffsetZ;`
- L40 _parameter_ `uint ClipmapOffsetZ;`
- L41 _parameter_ `float3 ClipmapUVScrollOffset;`
- L42 _parameter_ `float CoarseDistanceFieldValueScale;`
- L43 _parameter_ `float CoarseDistanceFieldValueBias;`

#### Functions (4)

- L17-20 _function_ `float Eikonal1(float X, float Step)` — https://en.wikipedia.org/wiki/Eikonal_equation
- L22-28 _function_ `float Eikonal2(float X, float Y, float Step)`
- L30-36 _function_ `float Eikonal3(float X, float Y, float Z, float Step)`
- L45-76 _function_ `float LoadPrevDistanceFieldValue(int3 MipCoord, int3 Offset)`

### `Shaders/Private/DistanceField/GlobalDistanceFieldObjectGrid.ush` (Private)

- lines: 84; parse: all-branches

#### Macros (#define, 5)

- L3 `#define DISTANCE_FIELD_OBJECT_GRID_INVALID_ID 0xFFFFFFFF`
- L4 `#define DISTANCE_FIELD_OBJECT_GRID_CELL_SIZE 4`
- L5 `#define DISTANCE_FIELD_OBJECT_GRID_PAGE_RESOLUTION 4`
- L6 `#define DISTANCE_FIELD_OBJECT_GRID_CARD_INTERPOLATION_RANGE_IN_VOXELS 3.0f`
- L7 `#define DISTANCE_FIELD_OBJECT_GRID_PAGE_STRIDE (DISTANCE_FIELD_OBJECT_GRID_PAGE_RESOLUTION * DISTANCE_FIELD_OBJECT_GRID_PAGE_RESOLUTION * DISTANCE_FIELD_OBJECT_GRID_PAGE_RESOLUTION)`

#### Structs / classes (2)

- L9-12 _struct_ **`FObjectGridCell`** `struct FObjectGridCell`
  - L11 _member_ `uint4 PackedIndex4;`
- L21-25 _struct_ **`FObjectGridCellIndex`** `struct FObjectGridCellIndex`
  - L23 _member_ `uint GPUSceneInstanceIndex;`
  - L24 _member_ `bool bValid;`

#### Functions (5)

- L14-19 _function_ `FObjectGridCell InitObjectGridCell()`
- L27-33 _function_ `uint PackObjectGridCellIndex(uint GPUSceneInstanceIndex, float Distance, float ObjectGridCellWorldExtent, float MaxQueryDistance)`
- L36-42 _function_ `FObjectGridCellIndex UnpackObjectGridCellIndex(uint PackedIndex)` — Unpack GPUSceneInstanceIndex
- L45-69 _function_ `void AddToObjectGridCell(inout FObjectGridCell ObjectGridCell, uint GPUSceneInstanceIndex, float Distance, float ObjectGridCellWorldExtent, float MaxQueryDistance)` — Unordered add to a grid cell
- L72-84 _function_ `void SortObjectGridCell(inout FObjectGridCell ObjectGridCell)` — Sort grid cell elements by distance

### `Shaders/Private/DistanceField/GlobalDistanceFieldShared.ush` (Private)

- lines: 452; parse: all-branches

#### Macros (#define, 43)

- L6 `#define DISTANCE_FIELD_IN_VIEW_UB 1` _[#if IS_MATERIAL_SHADER]_
- L10 `#define MaxGlobalDFAOConeDistance View.MaxGlobalDFAOConeDistance` _[#if DISTANCE_FIELD_IN_VIEW_UB]_
- L19 `#define MAX_GLOBAL_DF_CLIPMAPS 6` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS]_
- L23 `#define GlobalDistanceFieldPageAtlasTexture View.GlobalDistanceFieldPageAtlasTexture` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && DISTANCE_FIELD_IN_VIEW_UB]_
- L24 `#define GlobalDistanceFieldCoverageAtlasTexture View.GlobalDistanceFieldCoverageAtlasTexture` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && DISTANCE_FIELD_IN_VIEW_UB]_
- L25 `#define GlobalDistanceFieldPageTableTexture View.GlobalDistanceFieldPageTableTexture` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && DISTANCE_FIELD_IN_VIEW_UB]_
- L26 `#define GlobalDistanceFieldMipTexture View.GlobalDistanceFieldMipTexture` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && DISTANCE_FIELD_IN_VIEW_UB]_
- L27 `#define GlobalVolumeTranslatedCenterAndExtent View.GlobalVolumeTranslatedCenterAndExtent` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && DISTANCE_FIELD_IN_VIEW_UB]_
- L28 `#define GlobalVolumeTranslatedWorldToUVAddAndMul View.GlobalVolumeTranslatedWorldToUVAddAndMul` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && DISTANCE_FIELD_IN_VIEW_UB]_
- L29 `#define GlobalDistanceFieldMipTranslatedWorldToUVScale View.GlobalDistanceFieldMipTranslatedWorldToUVScale` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && DISTANCE_FIELD_IN_VIEW_UB]_
- L30 `#define GlobalDistanceFieldMipTranslatedWorldToUVBias View.GlobalDistanceFieldMipTranslatedWorldToUVBias` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && DISTANCE_FIELD_IN_VIEW_UB]_
- L31 `#define GlobalDistanceFieldMipUVMinZ View.GlobalDistanceFieldMipUVMinZ` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && DISTANCE_FIELD_IN_VIEW_UB]_
- L32 `#define GlobalDistanceFieldMipUVMaxZ View.GlobalDistanceFieldMipUVMaxZ` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && DISTANCE_FIELD_IN_VIEW_UB]_
- L33 `#define GlobalDistanceFieldMipFactor View.GlobalDistanceFieldMipFactor` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && DISTANCE_FIELD_IN_VIEW_UB]_
- L34 `#define GlobalDistanceFieldMipTransition View.GlobalDistanceFieldMipTransition` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && DISTANCE_FIELD_IN_VIEW_UB]_
- L35 `#define GlobalDistanceFieldInvPageAtlasSize View.GlobalDistanceFieldInvPageAtlasSize` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && DISTANCE_FIELD_IN_VIEW_UB]_
- L36 `#define GlobalDistanceFieldInvCoverageAtlasSize View.GlobalDistanceFieldInvCoverageAtlasSize` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && DISTANCE_FIELD_IN_VIEW_UB]_
- L37 `#define GlobalDistanceFieldClipmapSizeInPages View.GlobalDistanceFieldClipmapSizeInPages` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && DISTANCE_FIELD_IN_VIEW_UB]_
- L38 `#define GlobalVolumeDimension View.GlobalVolumeDimension` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && DISTANCE_FIELD_IN_VIEW_UB]_
- L39 `#define GlobalVolumeTexelSize View.GlobalVolumeTexelSize` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && DISTANCE_FIELD_IN_VIEW_UB]_
- L40 `#define NumGlobalSDFClipmaps View.NumGlobalSDFClipmaps` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && DISTANCE_FIELD_IN_VIEW_UB]_
- L41 `#define CoveredExpandSurfaceScale View.CoveredExpandSurfaceScale` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && DISTANCE_FIELD_IN_VIEW_UB]_
- L42 `#define NotCoveredExpandSurfaceScale View.NotCoveredExpandSurfaceScale` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && DISTANCE_FIELD_IN_VIEW_UB]_
- L43 `#define NotCoveredMinStepScale View.NotCoveredMinStepScale` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && DISTANCE_FIELD_IN_VIEW_UB]_
- L44 `#define DitheredTransparencyStepThreshold View.DitheredTransparencyStepThreshold` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && DISTANCE_FIELD_IN_VIEW_UB]_
- L45 `#define DitheredTransparencyTraceThreshold View.DitheredTransparencyTraceThreshold` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && DISTANCE_FIELD_IN_VIEW_UB]_
- L73 `#define GlobalDistanceFieldCoverageAtlasTextureSampler GlobalTrilinearWrappedSampler` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && SUPPORTS_INDEPENDENT_SAMPLERS]_
- L74 `#define GlobalDistanceFieldPageAtlasTextureSampler GlobalTrilinearWrappedSampler` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && SUPPORTS_INDEPENDENT_SAMPLERS]_
- L75 `#define GlobalDistanceFieldMipTextureSampler GlobalTrilinearClampedSampler` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && SUPPORTS_INDEPENDENT_SAMPLERS]_
- L78 `#define GlobalDistanceFieldCoverageAtlasTextureSampler View.GlobalDistanceFieldCoverageAtlasTextureSampler` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && !(SUPPORTS_INDEPENDENT_SAMPLERS) && DISTANCE_FIELD_IN_VIEW_UB]_
- L79 `#define GlobalDistanceFieldPageAtlasTextureSampler View.GlobalDistanceFieldPageAtlasTextureSampler` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && !(SUPPORTS_INDEPENDENT_SAMPLERS) && DISTANCE_FIELD_IN_VIEW_UB]_
- L80 `#define GlobalDistanceFieldMipTextureSampler View.GlobalDistanceFieldMipTextureSampler` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && !(SUPPORTS_INDEPENDENT_SAMPLERS) && DISTANCE_FIELD_IN_VIEW_UB]_
- L89 `#define GLOBAL_DISTANCE_FIELD_PAGE_BORDER 0.5f` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS]_
- L90 `#define GLOBAL_DISTANCE_FIELD_PAGE_RESOLUTION_IN_ATLAS 8` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS]_
- L91 `#define GLOBAL_DISTANCE_FIELD_PAGE_RESOLUTION (GLOBAL_DISTANCE_FIELD_PAGE_RESOLUTION_IN_ATLAS - 1)` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS]_
- L92 `#define GLOBAL_DISTANCE_FIELD_PAGE_ATLAS_SIZE_IN_PAGES_X 128` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS]_
- L93 `#define GLOBAL_DISTANCE_FIELD_PAGE_ATLAS_SIZE_IN_PAGES_Y 128` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS]_
- L94 `#define GLOBAL_DISTANCE_FIELD_INFLUENCE_RANGE_IN_VOXELS 4` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS]_
- L95 `#define GLOBAL_DISTANCE_FIELD_INVALID_PAGE_ID 0xFFFFFFFF` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS]_
- L97 `#define GLOBAL_DISTANCE_FIELD_PAGE_COVERAGE_BIT 0x80000000` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS]_
- L100 `#define GLOBAL_DISTANCE_FIELD_COVERAGE_PAGE_RESOLUTION_IN_ATLAS 4` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS]_
- L101 `#define GLOBAL_DISTANCE_FIELD_COVERAGE_PAGE_RESOLUTION (GLOBAL_DISTANCE_FIELD_COVERAGE_PAGE_RESOLUTION_IN_ATLAS - 1)` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS]_
- L102 `#define GLOBAL_DISTANCE_FIELD_COVERAGE_DOWNSAMPLE_FACTOR (GLOBAL_DISTANCE_FIELD_PAGE_RESOLUTION_IN_ATLAS / GLOBAL_DISTANCE_FIELD_COVERAGE_PAGE_RESOLUTION_IN_ATLAS)` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS]_
- L3 #pragma `once`

#### Structs / classes (1)

- L104-109 _struct_ **`FGlobalDistanceFieldPage`** `struct FGlobalDistanceFieldPage` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS]_
  - L106 _member_ `uint PageIndex;` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS]_
  - L107 _member_ `bool bValid;` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS]_
  - L108 _member_ `bool bCoverage;` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS]_

#### Global resources (textures / buffers / samplers) (7)

- L49 _resource_ `Texture3D GlobalDistanceFieldPageAtlasTexture;` — these are only used for the precomputation shaders; which don't have a view UB _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && !(DISTANCE_FIELD_IN_VIEW_UB)]_
- L50 _resource_ `Texture3D GlobalDistanceFieldCoverageAtlasTexture;` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && !(DISTANCE_FIELD_IN_VIEW_UB)]_
- L51 _resource_ `Texture3D<uint> GlobalDistanceFieldPageTableTexture;` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && !(DISTANCE_FIELD_IN_VIEW_UB)]_
- L52 _resource_ `Texture3D GlobalDistanceFieldMipTexture;` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && !(DISTANCE_FIELD_IN_VIEW_UB)]_
- L82 _resource_ `SamplerState GlobalDistanceFieldCoverageAtlasTextureSampler;` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && !(SUPPORTS_INDEPENDENT_SAMPLERS) && !(DISTANCE_FIELD_IN_VIEW_UB)]_
- L83 _resource_ `SamplerState GlobalDistanceFieldPageAtlasTextureSampler;` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && !(SUPPORTS_INDEPENDENT_SAMPLERS) && !(DISTANCE_FIELD_IN_VIEW_UB)]_
- L84 _resource_ `SamplerState GlobalDistanceFieldMipTextureSampler;` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && !(SUPPORTS_INDEPENDENT_SAMPLERS) && !(DISTANCE_FIELD_IN_VIEW_UB)]_

#### Global parameters (uniforms) (18)

- L12 _parameter_ `float MaxGlobalDFAOConeDistance;` _[#if !(DISTANCE_FIELD_IN_VIEW_UB)]_
- L53 _parameter_ `float4 GlobalVolumeTranslatedCenterAndExtent[MAX_GLOBAL_DF_CLIPMAPS];` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && !(DISTANCE_FIELD_IN_VIEW_UB)]_
- L54 _parameter_ `float4 GlobalVolumeTranslatedWorldToUVAddAndMul[MAX_GLOBAL_DF_CLIPMAPS];` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && !(DISTANCE_FIELD_IN_VIEW_UB)]_
- L55 _parameter_ `float4 GlobalDistanceFieldMipTranslatedWorldToUVScale[MAX_GLOBAL_DF_CLIPMAPS];` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && !(DISTANCE_FIELD_IN_VIEW_UB)]_
- L56 _parameter_ `float4 GlobalDistanceFieldMipTranslatedWorldToUVBias[MAX_GLOBAL_DF_CLIPMAPS];` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && !(DISTANCE_FIELD_IN_VIEW_UB)]_
- L57 _parameter_ `float GlobalDistanceFieldMipFactor;` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && !(DISTANCE_FIELD_IN_VIEW_UB)]_
- L58 _parameter_ `float GlobalDistanceFieldMipTransition;` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && !(DISTANCE_FIELD_IN_VIEW_UB)]_
- L59 _parameter_ `float3 GlobalDistanceFieldInvPageAtlasSize;` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && !(DISTANCE_FIELD_IN_VIEW_UB)]_
- L60 _parameter_ `float3 GlobalDistanceFieldInvCoverageAtlasSize;` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && !(DISTANCE_FIELD_IN_VIEW_UB)]_
- L61 _parameter_ `uint GlobalDistanceFieldClipmapSizeInPages;` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && !(DISTANCE_FIELD_IN_VIEW_UB)]_
- L62 _parameter_ `float GlobalVolumeDimension;` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && !(DISTANCE_FIELD_IN_VIEW_UB)]_
- L63 _parameter_ `float GlobalVolumeTexelSize;` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && !(DISTANCE_FIELD_IN_VIEW_UB)]_
- L64 _parameter_ `uint NumGlobalSDFClipmaps;` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && !(DISTANCE_FIELD_IN_VIEW_UB)]_
- L65 _parameter_ `float CoveredExpandSurfaceScale;` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && !(DISTANCE_FIELD_IN_VIEW_UB)]_
- L66 _parameter_ `float NotCoveredExpandSurfaceScale;` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && !(DISTANCE_FIELD_IN_VIEW_UB)]_
- L67 _parameter_ `float NotCoveredMinStepScale;` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && !(DISTANCE_FIELD_IN_VIEW_UB)]_
- L68 _parameter_ `float DitheredTransparencyStepThreshold;` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && !(DISTANCE_FIELD_IN_VIEW_UB)]_
- L69 _parameter_ `float DitheredTransparencyTraceThreshold;` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS && !(DISTANCE_FIELD_IN_VIEW_UB)]_

#### Functions (27)

- L111-124 _function_ `uint3 GlobalDistanceFieldPageLinearIndexToPageAtlasOffset(FGlobalDistanceFieldPage Page)` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS]_
- L126-135 _function_ `uint PackGlobalDistanceFieldPage(FGlobalDistanceFieldPage Page)` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS]_
- L137-144 _function_ `FGlobalDistanceFieldPage UnpackGlobalDistanceFieldPage(uint PackedPage)` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS]_
- L146-151 _function_ `FGlobalDistanceFieldPage GetGlobalDistanceFieldPage(float3 VolumeUV, uint ClipmapIndex)` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS]_
- L153-163 _function_ `void ComputeGlobalDistanceFieldPageUV(float3 VolumeUV, FGlobalDistanceFieldPage Page, out float3 OutPageUV, out float3 OutCoveragePageUV)` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS]_
- L165-172 _function_ `float3 ComputeGlobalDistanceFieldPageUV(float3 VolumeUV, FGlobalDistanceFieldPage Page)` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS]_
- L174-181 _function_ `float3 ComputeGlobalDistanceFieldCoveragePageUV(float3 VolumeUV, FGlobalDistanceFieldPage Page)` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS]_
- L183-186 _function_ `float EncodeGlobalDistanceFieldPageDistance(float Distance, float ClipmapInfluenceRange)` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS]_
- L188-191 _function_ `float DecodeGlobalDistanceFieldPageDistance(float EncodedDistance, float ClipmapInfluenceRange)` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS]_
- L193-200 _function_ `float3 ComputeGlobalUV(float3 TranslatedWorldPosition, uint ClipmapIndex)` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS]_
- L202-212 _function_ `float3 ComputeGlobalMipUV(float3 TranslatedWorldPosition, uint ClipmapIndex)` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS]_
- L214-247 _function_ `float GetDistanceToNearestSurfaceGlobal(float3 TranslatedWorldPosition)` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS]_
- L249-272 _function_ `float SampleGlobalDistanceField(float3 TranslatedWorldPosition, float MaxDistance, int MinClipmapIndex)` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS]_
- L274-289 _function_ `float GlobalDistanceFieldSampleClipmap(float3 ClipmapVolumeUV, uint ClipmapIndex)` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS]_
- L291-303 _function_ `float3 GlobalDistanceFieldPageCentralDiff(float3 ClipmapVolumeUV, uint ClipmapIndex)` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS]_
- L305-312 _function_ `float3 ComputeGlobalDistanceFieldNormal(float3 SampleTranslatedWorldPosition, uint ClipmapIndex, float3 FallbackNormal)` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS]_
- L316-356 _function_ `float3 GetDistanceFieldGradientGlobal(float3 TranslatedWorldPosition)` — Returns vector (unnormalized) to the nearest surface point. This vector is rescaled by 128 * GlobalVolumeTexelSize for backwards compatiblity. _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS]_
- L358-395 _function_ `float CalculateDistanceFieldApproxAO(float3 TranslatedWorldPosition, float3 WorldNormal, uint NumSteps, float StepDistance, float StepScale, float DistanceBias, float MaxDistance)` _[#if PLATFORM_SUPPORTS_DISTANCE_FIELDS]_
- L399-402 _function_ `float GetDistanceToNearestSurfaceGlobal(float3 TranslatedWorldPosition)` _[#if !(PLATFORM_SUPPORTS_DISTANCE_FIELDS)]_
- L404-407 _function_ `float3 GetDistanceFieldGradientGlobal(float3 TranslatedWorldPosition)` _[#if !(PLATFORM_SUPPORTS_DISTANCE_FIELDS)]_
- L409-412 _function_ `float CalculateDistanceFieldApproxAO(float3 TranslatedWorldPosition, float3 WorldNormal, uint NumSteps, float StepDistance, float StepScale, float DistanceBias, float MaxDistance)` _[#if !(PLATFORM_SUPPORTS_DISTANCE_FIELDS)]_
- L416-420 _function_ `float GetDistanceToNearestSurfaceGlobal(FDFVector3 WorldPosition)`
- L422-425 _function_ `float GetDistanceToNearestSurfaceGlobal(FLWCVector3 WorldPosition)`
- L427-431 _function_ `float3 GetDistanceFieldGradientGlobal(FDFVector3 WorldPosition)`
- L433-436 _function_ `float3 GetDistanceFieldGradientGlobal(FLWCVector3 WorldPosition)`
- L438-442 _function_ `float CalculateDistanceFieldApproxAO(FDFVector3 WorldPosition, float3 WorldNormal, uint NumSteps, float StepDistance, float StepScale, float DistanceBias, float MaxDistance)`
- L444-448 _function_ `float CalculateDistanceFieldApproxAO(FLWCVector3 WorldPosition, float3 WorldNormal, uint NumSteps, float StepDistance, float StepScale, float DistanceBias, float MaxDistance)`

### `Shaders/Private/DistanceField/GlobalDistanceFieldUpdate.ush` (Private)

- lines: 41; parse: all-branches

#### Macros (#define, 3)

- L3 `#define CULL_GRID_FACTOR 4`
- L4 `#define GLOBAL_DISTANCE_FIELD_PAGE_GROUP_X (GLOBAL_DISTANCE_FIELD_PAGE_RESOLUTION_IN_ATLAS / 4)`
- L5 `#define GLOBAL_DISTANCE_FIELD_PAGE_GROUP_NUM (GLOBAL_DISTANCE_FIELD_PAGE_GROUP_X * GLOBAL_DISTANCE_FIELD_PAGE_GROUP_X * GLOBAL_DISTANCE_FIELD_PAGE_GROUP_X)`

#### Global parameters (uniforms) (5)

- L21 _parameter_ `uint3 PageGridResolution;`
- L22 _parameter_ `uint PageTableClipmapOffsetZ;`
- L23 _parameter_ `float3 PageCoordToPageTranslatedWorldCenterScale;`
- L24 _parameter_ `float3 PageCoordToPageTranslatedWorldCenterBias;`
- L25 _parameter_ `float4 ClipmapVolumeTranslatedWorldToUVAddAndMul;`

#### Functions (4)

- L7-14 _function_ `uint3 UnpackPageUpdateTile(uint PackedPageTile)`
- L16-19 _function_ `uint PackPageUpdateTile(uint3 GridCoord)`
- L27-35 _function_ `uint3 PageGridCoordToPageTableTextureCoord(uint3 PageGridCoord)`
- L37-41 _function_ `float ComputeSquaredDistanceBetweenAABBs(float3 CenterA, float3 ExtentA, float3 CenterB, float3 ExtentB)`

### `Shaders/Private/DistanceField/GlobalDistanceFieldUtils.ush` (Private)

- lines: 221; parse: all-branches

#### Macros (#define, 3)

- L5 `#define ONE_SIDED_BAND_SIZE (4.0f * GLOBAL_DISTANCE_FIELD_COVERAGE_DOWNSAMPLE_FACTOR)`
- L8 `#define GLOBALSDF_USE_COVERAGE_BASED_EXPAND 1` _[#if !defined(GLOBALSDF_USE_COVERAGE_BASED_EXPAND)]_
- L12 `#define GLOBALSDF_SIMPLE_COVERAGE_BASED_EXPAND 0` _[#if !defined(GLOBALSDF_SIMPLE_COVERAGE_BASED_EXPAND)]_

#### Structs / classes (2)

- L33-55 _struct_ **`FGlobalSDFTraceInput`** `struct FGlobalSDFTraceInput`
  - L35 _member_ `float3 TranslatedWorldRayStart;`
  - L36 _member_ `float3 WorldRayDirection;`
  - L37 _member_ `float MinTraceDistance;`
  - L38 _member_ `float MaxTraceDistance;`
  - L39 _member_ `float StepFactor;`
  - L40 _member_ `float MinStepFactor;`
  - L44 _member_ `bool bExpandSurfaceUsingRayTimeInsteadOfMaxDistance;` — The SDF surface is expanded to reduce leaking through thin surfaces, especially foliage meshes with bGenerateDistanceFieldAsIfTwoSided Expanding as RayTime increases errors on the side of over-occlusion, especially at grazing angles, which can be desirable for diffuse GI. Expanding as MaxDistance increases has less incorrect self-intersection which is desirable for reflections rays.
  - L45 _member_ `float InitialMaxDistance;`
  - L48 _member_ `float VoxelSizeRelativeBias;` — Bias relative to the clipmap's voxel size
  - L50 _member_ `float VoxelSizeRelativeRayEndBias;` — Ray length bias relative to the clipmap's voxel size
  - L53 _member_ `bool bDitheredTransparency;` — For dithered semi-transparency
  - L54 _member_ `float2 DitherScreenCoord;`
- L75-83 _struct_ **`FGlobalSDFTraceResult`** `struct FGlobalSDFTraceResult`
  - L77 _member_ `float HitTime;`
  - L78 _member_ `uint HitClipmapIndex;`
  - L79 _member_ `uint TotalStepsTaken;`
  - L82 _member_ `float ExpandSurfaceAmount;` — Amount the surface was expanded at the hit

#### Functions (5)

- L15-31 _function_ `uint ComputeGlobalDistanceFieldClipmapIndex(float3 TranslatedWorldPosition)`
- L57-73 _function_ `FGlobalSDFTraceInput SetupGlobalSDFTraceInput(float3 InTranslatedWorldRayStart, float3 InWorldRayDirection, float InMinTraceDistance, float InMaxTraceDistance, float InStepFactor, float InMinStepFactor)`
- L85-88 _function_ `bool GlobalSDFTraceResultIsHit(FGlobalSDFTraceResult TraceResult)`
- L90-200 _function_ `FGlobalSDFTraceResult RayTraceGlobalDistanceField(FGlobalSDFTraceInput TraceInput)`
- L202-221 _function_ `void ClipRayToStartOutsideGlobalSDF(inout float3 TranslatedRayOrigin, float3 RayDirection, inout float RayLength)`
