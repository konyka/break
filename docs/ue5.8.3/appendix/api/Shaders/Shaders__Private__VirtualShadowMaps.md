# Shaders / Shaders/Private/VirtualShadowMaps

- files: 37; lines: 10729
- record kinds: cpp_binding=52, define=102, entry=52, function=232, groupshared=14, include=209, macro_call=2, member=153, method=29, parameter=103, resource=156, static_const=1, struct=34

### `Shaders/Private/VirtualShadowMaps/Desaturate.usf` (Private)

- lines: 22; parse: all-branches
- includes: L3 `../Common.ush`

#### Entry points (1)

- L13-21 _entry_ `float4 DesaturatePS( noperspective float4 UVAndScreenPos : TEXCOORD0 ) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FDesaturatePS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapArray.cpp:5208)

#### Global resources (textures / buffers / samplers) (2)

- L5 _resource_ `Texture2D InputTexture;`
- L6 _resource_ `SamplerState InputSampler;`

#### Functions (1)

- L8-11 _function_ `float Grayscale(float3 SourceClr)`

### `Shaders/Private/VirtualShadowMaps/VirtualShadowMapBuildPerPageDrawCommands.usf` (Private)

- lines: 504; parse: all-branches
- includes: L10 `../Common.ush`, L11 `../ViewData.ush`, L12 `VirtualShadowMapPageOverlap.ush`, L13 `VirtualShadowMapProjectionCommon.ush`, L23 `../Nanite/NaniteCullingCommon.ush`, L24 `../Nanite/NaniteDataDecode.ush`, L25 `../InstanceCulling/InstanceCullingCommon.ush`, L26 `../InstanceCulling/InstanceCullingLoadBalancer.ush`, L27 `../WaveOpUtil.ush`, L28 `../DynamicMeshBounds.ush`, L29 `/Engine/Shared/VirtualShadowMapDefinitions.h`, L30 `VirtualShadowMapStats.ush`, L31 `VirtualShadowMapPageCacheCommon.ush`, L33 `../ShaderPrint.ush`

#### Macros (#define, 6)

- L8 `#define USE_HZB_SHARED_SAMPLERS 0`
- L15 `#define VIRTUAL_TEXTURE_TARGET 1`
- L18 `#define NANITE_CULLING_ENABLE_MIN_RADIUS_CULL 1`
- L21 `#define VIRTUAL_TEXTURE_TARGET 1`
- L89 `#define MAX_SINGLE_THREAD_MARKING_AREA (8U)`
- L90 `#define MARKING_JOB_QUEUE_SIZE (NUM_THREADS_PER_GROUP * 2U)`

#### Entry points (3)

- L154-441 _entry_ `[numthreads(NUM_THREADS_PER_GROUP, 1, 1)] void CullPerPageDrawCommandsCs(uint3 GroupId : SV_GroupID, int GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FCullPerPageDrawCommandsCs` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapArray.cpp:3848)
- L453-475 _entry_ `[numthreads(NUM_THREADS_PER_GROUP, 1, 1)] void AllocateCommandInstanceOutputSpaceCs(uint IndirectArgIndex : SV_DispatchThreadID)` — stage: **compute** — C++: `FAllocateCommandInstanceOutputSpaceCs` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapArray.cpp:3887) — Separate pass to allocate space, needs to run once the final space requirements are known. We buffer the page/instance-draw info and reshuffle later. TODO: Possibly just re-run the culling process in the output pass, saves storing stuff, but may cost more and runs the risk of the passes disagreeing e.g., due to rounding or whatever.
- L484-502 _entry_ `[numthreads(NUM_THREADS_PER_GROUP, 1, 1)] void OutputCommandInstanceListsCs(uint VisibleInstanceIndex : SV_DispatchThreadID)` — stage: **compute** — C++: `FOutputCommandInstanceListsCs` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapArray.cpp:3928)

#### Structs / classes (1)

- L92-99 _struct_ **`FSharedMarkingJob`** `struct FSharedMarkingJob`
  - L94 _member_ `uint4 RectPages;`
  - L95 _member_ `uint VirtualShadowMapId;`
  - L96 _member_ `uint MipLevel;`
  - L97 _member_ `uint FlagMask;`
  - L98 _member_ `uint MarkPageDirtyFlags;`

#### Global resources (textures / buffers / samplers) (13)

- L35 _resource_ `RWStructuredBuffer<FVSMVisibleInstanceCmd> VisibleInstancesOut;`
- L36 _resource_ `RWStructuredBuffer<uint> VisibleInstanceCountBufferOut;`
- L41 _resource_ `StructuredBuffer<FVSMCullingBatchInfo> VSMCullingBatchInfos;` _[#if ENABLE_BATCH_MODE]_
- L49 _resource_ `StructuredBuffer<uint2> DrawCommandDescs;`
- L51 _resource_ `RWBuffer<uint> DrawIndirectArgsBufferOut;`
- L443 _resource_ `Buffer<uint> DrawIndirectArgsBuffer;`
- L444 _resource_ `RWBuffer<uint> InstanceIdOffsetBufferOut;`
- L445 _resource_ `RWStructuredBuffer<uint> OutputOffsetBufferOut;`
- L446 _resource_ `RWStructuredBuffer<uint> TmpInstanceIdOffsetBufferOut;`
- L477 _resource_ `StructuredBuffer<FVSMVisibleInstanceCmd> VisibleInstances;`
- L478 _resource_ `StructuredBuffer <uint> VisibleInstanceCountBuffer;`
- L480 _resource_ `RWStructuredBuffer<uint> InstanceIdsBufferOut;` — RWStructuredBuffer<uint> TmpInstanceIdOffsetBufferOut;
- L481 _resource_ `RWStructuredBuffer<uint> PageInfoBufferOut;`

#### Global parameters (uniforms) (9)

- L37 _parameter_ `uint TotalPrimaryViews;`
- L38 _parameter_ `uint VisibleInstancesBufferNum;`
- L43 _parameter_ `uint FirstPrimaryView;` _[#if !(ENABLE_BATCH_MODE)]_
- L44 _parameter_ `uint NumPrimaryViews;` _[#if !(ENABLE_BATCH_MODE)]_
- L45 _parameter_ `uint DynamicInstanceIdOffset;` _[#if !(ENABLE_BATCH_MODE)]_
- L46 _parameter_ `uint DynamicInstanceIdMax;` _[#if !(ENABLE_BATCH_MODE)]_
- L150 _parameter_ `uint NumPageAreaDiagnosticSlots;` _[#if VSM_GENERATE_STATS]_
- L151 _parameter_ `uint LargeInstancePageAreaThreshold;` _[#if VSM_GENERATE_STATS]_
- L447 _parameter_ `uint NumIndirectArgs;`

#### groupshared (2)

- L101 _groupshared_ `groupshared uint NumSharedMarkingJobs;`
- L102 _groupshared_ `groupshared uint2 SharedMarkingJobs[MARKING_JOB_QUEUE_SIZE];`

#### Functions (5)

- L55-63 _function_ `uint GetInclusiveRectArea(uint4 Rect)` — TODO: Move to common header Get the area of an "inclusive" rect (which means that the max is inside the rect), also guards against negative area (where min > max)
- L65-87 _function_ `bool WriteCmd(uint MipViewId, uint InstanceId, uint IndirectArgIndex, uint CullingFlags, bool bStaticPage)`
- L104-116 _function_ `uint2 PackJob(FSharedMarkingJob Job)`
- L118-130 _function_ `FSharedMarkingJob UnpackJob(uint2 Packed)`
- L132-147 _function_ `bool MarkPageDirty( FVirtualSMLevelOffset PageTableLevelOffset, uint2 vPage, uint MipLevel, uint PageFlagMask, uint MarkPageDirtyFlags)`

### `Shaders/Private/VirtualShadowMaps/VirtualShadowMapCacheGPUInvalidation.usf` (Private)

- lines: 237; parse: all-branches
- includes: L6 `../Common.ush`, L7 `../SceneData.ush`, L8 `../ViewData.ush`, L9 `VirtualShadowMapPageCacheCommon.ush`, L10 `VirtualShadowMapCacheInvalidation.ush`, L11 `../WaveOpUtil.ush`, L198 `../InstanceCulling/InstanceCullingLoadBalancer.ush` [defined(VSMResetInstanceStateCS)]

#### Macros (#define, 3)

- L4 `#define USE_HZB_SHARED_SAMPLERS 0`
- L51 `#define FOREACH_SET_BIT_BEGIN(MaskWord, BitIndexVarName, BitMaskVarName) { uint MaskWordTemp = (MaskWord); while (MaskWordTemp != 0u) { uint BitIndexVarName = firstbitlow(MaskWordTemp); uint BitMaskVarName = 1u << BitIndexVarName; MaskWordTemp ^= BitMaskVarName;` (8 lines)
- L61 `#define FOREACH_SET_BIT_END() } }`

#### Entry points (3)

- L65-141 _entry_ `[numthreads(THREAD_GROUP_SIZE, 1, 1)] void VSMUpdateViewInstanceStateCS(uint3 GroupId : SV_GroupID, uint GroupThreadIndex : SV_GroupIndex, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FVSMUpdateViewInstanceStateCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapCacheManager.cpp:2231) _[#if defined(VSMUpdateViewInstanceStateCS)]_
- L150-193 _entry_ `[numthreads(THREAD_GROUP_SIZE, 1, 1)] void ProcessInvalidationQueueGPUCS(uint3 GroupId : SV_GroupID, uint GroupThreadIndex : SV_GroupIndex, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FProcessInvalidationQueueGPUCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapCacheManager.cpp:1765) _[#if defined(ProcessInvalidationQueueGPUCS)]_
- L200-234 _entry_ `[numthreads(NUM_THREADS_PER_GROUP, 1, 1)] void VSMResetInstanceStateCS(uint3 GroupId : SV_GroupID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FVSMResetInstanceStateCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapCacheManager.cpp:2107) _[#if defined(VSMResetInstanceStateCS)]_

#### Structs / classes (1)

- L26-31 _struct_ **`FInvalidationItem`** `struct FInvalidationItem`
  - L28 _member_ `uint InstanceId;`
  - L29 _member_ `int SceneRendererPrimaryViewId;`
  - L30 _member_ `bool bStateChange;`

#### Global resources (textures / buffers / samplers) (6)

- L15 _resource_ `RWStructuredBuffer<uint> InOutViewInstanceState;` — Per-view isolate persistent buffer, bound for each dispatch
- L16 _resource_ `RWBuffer<uint> OutInvalidationArgs;`
- L17 _resource_ `RWStructuredBuffer<uint> OutInvalidationQueue;`
- L43 _resource_ `RWStructuredBuffer<uint> OutCacheInstanceAsDynamic;` — Buffer containing one bit for each scene renderer view, such that we can random access in the renderer. Stores a copy of the output state but is transient
- L147 _resource_ `Buffer<uint> InvalidationArgs;` _[#if defined(ProcessInvalidationQueueGPUCS)]_
- L148 _resource_ `StructuredBuffer<uint> InvalidationQueue;` _[#if defined(ProcessInvalidationQueueGPUCS)]_

#### Global parameters (uniforms) (4)

- L45 _parameter_ `int SceneRendererViewId;`
- L46 _parameter_ `int StateWordStride;`
- L47 _parameter_ `int MaxValidInstanceIndex;`
- L48 _parameter_ `int InvalidationQueueMax;`

#### Functions (2)

- L19-24 _function_ `uint PackInvalidationItem(uint InstanceId, int SceneRendererPrimaryViewId, bool bStateChange)`
- L33-40 _function_ `FInvalidationItem UnpackInvalidationItem(uint PackedItem)`

### `Shaders/Private/VirtualShadowMaps/VirtualShadowMapCacheInvalidation.ush` (Private)

- lines: 171; parse: all-branches
- includes: L8 `../Common.ush`, L9 `../SceneData.ush`, L10 `VirtualShadowMapProjectionCommon.ush`, L11 `VirtualShadowMapPageOverlap.ush`, L12 `VirtualShadowMapPageCacheCommon.ush`, L13 `../ScreenSpaceDenoise/SSDDefinitions.ush`, L14 `../Nanite/NaniteHZBCull.ush`
- L6 #pragma `once`

#### Global resources (textures / buffers / samplers) (2)

- L16 _resource_ `RWStructuredBuffer<FPhysicalPageMetaData> PhysicalPageMetaDataOut;`
- L20 _resource_ `RWTexture2D<uint> OutPageRequestFlags;` — We write the invalidation flags to the page request flags buffer to be consumed by the next physical page update pass.

#### Functions (4)

- L22-35 _function_ `bool IsValidInstanceAndCastShadows(FInstanceSceneData InstanceSceneData)`
- L37-41 _function_ `bool IsValidInstanceAndCastShadows(uint InstanceId)`
- L43-163 _function_ `void InvalidateInstancePages(FVirtualShadowMapProjectionShaderData ProjectionData, FInstanceSceneData InstanceSceneData, uint OverrideInvalidationFlags)`
- L165-170 _function_ `void InvalidateInstancePages(FVirtualShadowMapHandle VirtualShadowMapHandle, uint InstanceId, uint OverrideInvalidationFlags)`

### `Shaders/Private/VirtualShadowMaps/VirtualShadowMapCacheLoadBalancer.usf` (Private)

- lines: 50; parse: all-branches
- includes: L6 `../Common.ush`, L7 `../SceneData.ush`, L8 `VirtualShadowMapPageCacheCommon.ush`, L9 `VirtualShadowMapCacheInvalidation.ush`, L10 `../WaveOpUtil.ush`, L11 `../InstanceCulling/InstanceCullingLoadBalancer.ush`

#### Macros (#define, 1)

- L4 `#define USE_HZB_SHARED_SAMPLERS 0`

#### Entry points (1)

- L27-49 _entry_ `[numthreads(CS_1D_GROUP_SIZE_X, 1, 1)] void InvalidateInstancePagesLoadBalancerCS( uint3 GroupId : SV_GroupID, uint GroupThreadIndex : SV_GroupIndex, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FInvalidateInstancePagesLoadBalancerCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapCacheManager.cpp:1728)

#### Structs / classes (1)

- L13-17 _struct_ **`FInstanceInvalidationPayload`** `struct FInstanceInvalidationPayload`
  - L15 _member_ `int VirtualShadowMapId;`
  - L16 _member_ `uint Flags;`

#### Functions (1)

- L19-25 _function_ `FInstanceInvalidationPayload DecodeInstanceInvalidationPayload(uint Payload)`

### `Shaders/Private/VirtualShadowMaps/VirtualShadowMapCompactViews.usf` (Private)

- lines: 116; parse: all-branches
- includes: L7 `../Common.ush`, L8 `/Engine/Shared/VirtualShadowMapDefinitions.h`, L9 `/Engine/Shared/SceneCullingDefinitions.h`, L12 `../Nanite/NaniteDataDecode.ush`

#### Macros (#define, 2)

- L11 `#define NANITE_MULTI_VIEW 1`
- L23 `#define VSM_MAX_VIEWS_PER_GROUP (VSM_MAX_MIP_LEVELS*6)`

#### Entry points (1)

- L39-115 _entry_ `[numthreads(VSM_MAX_VIEWS_PER_GROUP, 1, 1)] void CompactViewsVSM_CS( uint GroupId : SV_GroupID, uint ThreadId : SV_GroupIndex)` — stage: **compute** — C++: `FCompactViewsVSM_CS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapArray.cpp:4203)

#### Global resources (textures / buffers / samplers) (3)

- L14 _resource_ `RWStructuredBuffer< FPackedNaniteView > CompactedViewsOut;`
- L15 _resource_ `RWStructuredBuffer< uint > CompactedViewsAllocationOut;`
- L17 _resource_ `RWStructuredBuffer< FViewDrawGroup > InOutViewDrawRanges;`

#### Global parameters (uniforms) (1)

- L18 _parameter_ `uint NumViewRanges;`

#### groupshared (3)

- L25 _groupshared_ `groupshared uint OutputViewId[VSM_MAX_VIEWS_PER_GROUP];`
- L26 _groupshared_ `groupshared uint OutputViewCount;`
- L27 _groupshared_ `groupshared uint OutputViewRangeOffset;`

#### Functions (2)

- L29-32 _function_ `uint PackViewIdMip(uint PrimaryViewId, uint MipLevel)`
- L34-37 _function_ `uint2 UnpackViewIdMip(uint Packed)`

### `Shaders/Private/VirtualShadowMaps/VirtualShadowMapComputeExplicitChunkDrawsViewMask.usf` (Private)

- lines: 27; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../ComputeShaderUtils.ush`, L5 `/Engine/Shared/SceneCullingDefinitions.h`

#### Entry points (1)

- L11-26 _entry_ `[numthreads(64, 1, 1)] void ComputeExplicitChunkDrawsViewMask( uint3 GroupId : SV_GroupID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FComputeExplicitChunkDrawsViewMask_CS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapArray.cpp:4216)

#### Global resources (textures / buffers / samplers) (2)

- L8 _resource_ `StructuredBuffer< FViewDrawGroup > InViewDrawRanges;`
- L9 _resource_ `RWStructuredBuffer< FInstanceCullingGroupWork > InOutInstanceCullingWorkGroups;`

#### Global parameters (uniforms) (1)

- L7 _parameter_ `uint NumWorkGroups;`

### `Shaders/Private/VirtualShadowMaps/VirtualShadowMapCopyStats.usf` (Private)

- lines: 33; parse: all-branches
- includes: L3 `../Common.ush`, L4 `VirtualShadowMapStats.ush`, L5 `/Engine/Shared/NaniteDefinitions.h`

#### Entry points (1)

- L13-32 _entry_ `[numthreads(1, 1, 1)] void CopyStatsCS()` — stage: **compute** — C++: `FVirtualSmCopyStatsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapCacheManager.cpp:1407)

#### Global resources (textures / buffers / samplers) (3)

- L7 _resource_ `StructuredBuffer<uint> InStatsBuffer;`
- L8 _resource_ `RWBuffer<uint> AccumulatedStatsBufferOut;`
- L11 _resource_ `StructuredBuffer<FNaniteStats> NaniteStatsBuffer;` — Pull out a bunch of nanite stats for our CSV as well

### `Shaders/Private/VirtualShadowMaps/VirtualShadowMapDebug.usf` (Private)

- lines: 191; parse: all-branches
- includes: L7 `../Common.ush`, L8 `../SceneTexturesCommon.ush`, L9 `VirtualShadowMapPageOverlap.ush`, L10 `VirtualShadowMapPageCacheCommon.ush`, L11 `VirtualShadowMapProjectionCommon.ush`, L12 `../Visualization.ush`, L13 `/Engine/Shared/VirtualShadowMapDefinitions.h`

#### Entry points (2)

- L135-155 _entry_ `[numthreads(VSM_DEFAULT_CS_GROUP_XY, VSM_DEFAULT_CS_GROUP_XY, 1)] void DebugVisualizeVirtualSmCS(uint2 PixelPos : SV_DispatchThreadID)` — stage: **compute** — C++: `FDebugVisualizeVirtualSmCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapArray.cpp:3550)
- L162-190 _entry_ `float4 TonemapProjectionDebugTexturePS( noperspective float4 UVAndScreenPos : TEXCOORD0 ) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FTonemapProjectionDebugTexturePS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapArray.cpp:5224)

#### Global resources (textures / buffers / samplers) (4)

- L21 _resource_ `StructuredBuffer<FPhysicalPageMetaData> PhysicalPageMetaData;`
- L22 _resource_ `RWTexture2D<float4> OutVisualize;`
- L159 _resource_ `Texture2D DebugTexture;`
- L160 _resource_ `SamplerState DebugTextureSampler;`

#### Global parameters (uniforms) (7)

- L15 _parameter_ `uint DebugTargetWidth;`
- L16 _parameter_ `uint DebugTargetHeight;`
- L17 _parameter_ `uint BorderWidth;`
- L18 _parameter_ `uint VisualizeModeId;` — VIRTUAL_SHADOW_MAP_VISUALIZE_*
- L19 _parameter_ `int VirtualShadowMapId;`
- L157 _parameter_ `int VisualizeVirtualShadowMapId;`
- L158 _parameter_ `float VisualizeNaniteOverdrawScale;`

#### static const (1)

- L24 _static_const_ `static const float3 BlackColor = float3(0.0f, 0.0f, 0.0f);`

#### Functions (2)

- L27-109 _function_ `float3 DebugVisualizeClipmap(float2 PixelUV, FVirtualShadowMapProjectionShaderData ProjectionData0)`
- L111-132 _function_ `float4 DebugVisualizeClipmap(uint2 OutputPixel, int VirtualShadowMapId)`

### `Shaders/Private/VirtualShadowMaps/VirtualShadowMapHandle.ush` (Private)

- lines: 76; parse: all-branches
- includes: L4 `../Common.ush`, L5 `/Engine/Shared/VirtualShadowMapDefinitions.h`
- L2 #pragma `once`

#### Structs / classes (1)

- L10-75 _struct_ **`FVirtualShadowMapHandle`** `struct FVirtualShadowMapHandle` — Abstraction to facilitate passing meta-data (which is sometimes compiletime constant) along in addition to just an index.
  - L12 _member_ `uint Id;`
  - L13 _member_ `bool bIsSinglePageSM;`
  - L15 _method_ `static FVirtualShadowMapHandle MakeFromId(uint VirtualShadowMapId)`
  - L23 _method_ `static FVirtualShadowMapHandle MakeFromIdDirectional(uint VirtualShadowMapId)`
  - L31 _method_ `static FVirtualShadowMapHandle MakeFromFullIndex(uint FullVirtualShadowMapIndex)`
  - L39 _method_ `static FVirtualShadowMapHandle MakeInvalid()`
  - L50 _method_ `FVirtualShadowMapHandle MakeOffset(int Offset)` — Note: signed offset, can go both ways.
  - L61 _method_ `bool IsValid()`
  - L66 _method_ `bool IsSinglePage()`
  - L71 _method_ `uint GetDataIndex()`

### `Shaders/Private/VirtualShadowMaps/VirtualShadowMapLightGrid.ush` (Private)

- lines: 33; parse: all-branches
- includes: L8 `../Common.ush`, L9 `../LightGridCommon.ush`
- L6 #pragma `once`

#### Functions (2)

- L11-22 _function_ `FCulledLightsGridHeader VirtualShadowMapGetLightsGridHeader(uint2 PixelPos, float SceneDepth)`
- L24-32 _function_ `FLocalLightData VirtualShadowMapGetLocalLightData(FCulledLightsGridHeader GridHeader, uint Index)`

### `Shaders/Private/VirtualShadowMaps/VirtualShadowMapMaskBitsCommon.ush` (Private)

- lines: 71; parse: all-branches
- includes: L9 `../Common.ush`, L10 `../SceneTexturesCommon.ush`, L11 `../LightShaderParameters.ush`, L12 `../LightGridCommon.ush`, L13 `../VirtualShadowMaps/VirtualShadowMapLightGrid.ush`, L14 `../VirtualShadowMaps/VirtualShadowMapProjectionCommon.ush`
- L7 #pragma `once`

#### Functions (2)

- L16-60 _function_ `float GetVirtualShadowMapMaskForLight( uint4 ShadowMask, uint2 PixelPos, float SceneDepth, int VirtualShadowMapId, float3 TranslatedWorldPosition, inout uint OutLightIndex)`
- L62-71 _function_ `float GetVirtualShadowMapMaskForLight( uint4 ShadowMask, uint2 PixelPos, float SceneDepth, int VirtualShadowMapId, float3 TranslatedWorldPosition)`

### `Shaders/Private/VirtualShadowMaps/VirtualShadowMapPageAccessCommon.ush` (Private)

- lines: 437; parse: all-branches
- includes: L8 `../Common.ush`, L9 `../BitPacking.ush`, L10 `/Engine/Shared/VirtualShadowMapDefinitions.h`, L11 `VirtualShadowMapHandle.ush`

#### Macros (#define, 29)

- L15 `#define VSM_FLAG_ALLOCATED (1U << 0)`
- L17 `#define VSM_FLAG_DYNAMIC_UNCACHED (1U << 1)`
- L19 `#define VSM_FLAG_STATIC_UNCACHED (1U << 2)`
- L22 `#define VSM_FLAG_DETAIL_GEOMETRY (1U << 3)`
- L24 `#define VSM_FLAG_PRIMARY_REQUEST (1u << 4)`
- L26 `#define VSM_FLAG_SECONDARY_REQUEST (1u << 5)`
- L29 `#define VSM_PAGE_FLAGS_BITS_PER_HMIP (6U)`
- L30 `#define VSM_PAGE_FLAGS_BITS_MASK ((1U<<VSM_PAGE_FLAGS_BITS_PER_HMIP)-1U)`
- L33 `#define VSM_FLAG_ANY_UNCACHED (VSM_FLAG_DYNAMIC_UNCACHED \| VSM_FLAG_STATIC_UNCACHED)`
- L34 `#define VSM_FLAG_AUX_MASK (VSM_FLAG_DETAIL_GEOMETRY \| VSM_FLAG_PRIMARY_REQUEST \| VSM_FLAG_SECONDARY_REQUEST)`
- L37 `#define VSM_FLAG_TEST_ANY_MASK (VSM_FLAG_ANY_UNCACHED \| VSM_FLAG_ALLOCATED)`
- L39 `#define VSM_FLAG_TEST_ALL_MASK (VSM_FLAG_DETAIL_GEOMETRY \| VSM_FLAG_PRIMARY_REQUEST \| VSM_FLAG_SECONDARY_REQUEST)`
- L45 `#define VSM_EXTENDED_FLAG_DYNAMIC_INITIALIZED (1U << 6)`
- L47 `#define VSM_EXTENDED_FLAG_STATIC_INITIALIZED (1U << 7)`
- L49 `#define VSM_EXTENDED_FLAG_DYNAMIC_DIRTY (1U << 8)`
- L51 `#define VSM_EXTENDED_FLAG_STATIC_DIRTY (1U << 9)`
- L53 `#define VSM_EXTENDED_FLAG_INVALIDATE_DYNAMIC (1U << 10)`
- L55 `#define VSM_EXTENDED_FLAG_INVALIDATE_STATIC (1U << 11)`
- L57 `#define VSM_EXTENDED_FLAG_VIEW_UNCACHED (1U << 12)`
- L59 `#define VSM_EXTENDED_FLAG_UNREFERENCED (1U << 13)`
- L63 `#define VSM_EXTENDED_FLAG_FORCE_CACHED (1U << 14)`
- L66 `#define VSM_EXTENDED_FLAG_DEFERRED_INVALIDATION (1U << 15)`
- L68 `#define VSM_EXTENDED_FLAG_ANY_INITIALIZED (VSM_EXTENDED_FLAG_DYNAMIC_INITIALIZED \| VSM_EXTENDED_FLAG_STATIC_INITIALIZED)`
- L69 `#define VSM_EXTENDED_FLAG_ANY_DIRTY (VSM_EXTENDED_FLAG_DYNAMIC_DIRTY \| VSM_EXTENDED_FLAG_STATIC_DIRTY)`
- L70 `#define VSM_EXTENDED_FLAG_ANY_INVALIDATED (VSM_EXTENDED_FLAG_INVALIDATE_DYNAMIC \| VSM_EXTENDED_FLAG_INVALIDATE_STATIC)`
- L256 `#define VSM_PHYSICAL_PAGE_SECONDARY_REQUEST_FLAG 0x20000000`
- L257 `#define VSM_PHYSICAL_PAGE_VALID_FOR_RENDERING_FLAG 0x40000000`
- L258 `#define VSM_PHYSICAL_PAGE_ANY_MIP_VALID_FLAG 0x80000000`
- L259 `#define VSM_PHYSICAL_PAGE_INVALID 0x00000000`
- L6 #pragma `once`

#### Structs / classes (5)

- L102-121 _struct_ **`FVirtualSMLevelOffset`** `struct FVirtualSMLevelOffset`
  - L104 _member_ `bool bIsSinglePageSM;`
  - L105 _member_ `uint2 LevelTexelOffset;`
  - L107 _method_ `uint GetPacked()`
  - L112 _method_ `static FVirtualSMLevelOffset Unpack(uint PackedLevelOffset)`
- L165-187 _struct_ **`FVSMPageOffset`** `struct FVSMPageOffset` — Offset of an individual page in the global page table data structure, whatever it may be.
  - L167 _member_ `uint2 TexelAddress;`
  - L170 _method_ `uint2 GetResourceAddress()` — Returns the address formated for resource (texture / buffer) access.
  - L175 _method_ `uint GetPacked()`
  - L180 _method_ `static FVSMPageOffset Unpack(uint Packed)`
- L246-254 _struct_ **`FShadowPhysicalPage`** `struct FShadowPhysicalPage` — Current page table format: NOTE: Some redundancy in flags and encoding, but we have spare bits for now [0:9] PageAddress.x [10:19] PageAddress.y [20:25] LODOffset [26:28] (currently unused) [29] bIsSecondaryRequest [30] bThisLODValidForRendering [31] bAnyLODValid
  - L248 _member_ `uint2 PhysicalAddress;` — Physical page address X, Y
  - L249 _member_ `uint LODOffset;` — 0 if page is mapped at this mip/clipmap level; 1 if mapped at next courser level, etc. [0..64)
  - L250 _member_ `bool bAnyLODValid;` — Valid physical page mapped at some LOD level
  - L251 _member_ `bool bIsSecondaryRequest;` — VSM_PHYSICAL_PAGE_SECONDARY_REQUEST_FLAG
  - L252 _member_ `bool bThisLODValidForRendering;` — Valid physical page mapped for rendering into
  - L253 _member_ `bool bThisLODValid;` — Valid page mapped at this specific level (equivalent to bAnyMipValid && LODOffset == 0)
- L347-354 _struct_ **`FShadowPageTranslationResult`** `struct FShadowPageTranslationResult`
  - L349 _member_ `bool bValid;`
  - L350 _member_ `uint LODOffset;`
  - L351 _member_ `uint2 VirtualTexelAddress;`
  - L352 _member_ `float2 VirtualTexelAddressFloat;`
  - L353 _member_ `uint2 PhysicalTexelAddress;`
- L373-377 _struct_ **`FPageInfo`** `struct FPageInfo`
  - L375 _member_ `uint ViewId;`
  - L376 _member_ `bool bStaticPage;` — Write to static page vs dynamic page

#### Functions (31)

- L72-75 _function_ `uint CalcLog2LevelDimsPages(uint Level)`
- L77-80 _function_ `uint CalcLevelDimsPages(uint Level)`
- L82-85 _function_ `uint CalcLevelDimsTexels(uint Level)`
- L87-100 _function_ `uint2 CalcLevelOffsets(uint MipLevel)`
- L127-147 _function_ `FVirtualSMLevelOffset CalcPageTableLevelOffset(FVirtualShadowMapHandle VirtualShadowMapHandle, uint MipLevel)` — Compute the offset for a mip level page table given a shadow map ID and a level.
- L152-155 _function_ `FVirtualSMLevelOffset CalcPageTableLevelOffset(int VirtualShadowMapId, uint MipLevel)` — Compute the offset for a mip level page table given a shadow map ID and a level.
- L157-160 _function_ `uint2 CalcPageOffsetInFullLevel(uint Level, uint2 PageAddress)`
- L192-204 _function_ `FVSMPageOffset CalcPageOffset(FVirtualSMLevelOffset LevelOffset, uint Level, uint2 PageAddress)` — Compute the offset for page within a level page table given a level and PageAddress.
- L206-210 _function_ `FVSMPageOffset CalcPageOffset(FVirtualShadowMapHandle VirtualShadowMapHandle, uint Level, uint2 PageAddress)`
- L212-215 _function_ `FVSMPageOffset CalcPageOffset(int VirtualShadowMapId, uint Level, uint2 PageAddress)`
- L217-220 _function_ `bool IsVirtualShadowMapPageAddressValid(int2 PageAddress, uint Level)`
- L223-226 _function_ `uint VSMPhysicalPageAddressToIndex(uint2 PhysicalPageAddress)` — Linearlize a physical page address to a linear offset
- L228-234 _function_ `uint2 VSMPhysicalIndexToPageAddress(uint PageIndex)`
- L261-269 _function_ `uint ShadowEncodePageTable(uint2 PhysicalAddress, bool bValidForRendering, bool bIsSecondaryRequest)`
- L270-275 _function_ `uint ShadowEncodePageTable(uint2 PhysicalAddress, uint LODOffset)`
- L277-287 _function_ `FShadowPhysicalPage ShadowDecodePageTable(uint Value)`
- L289-292 _function_ `FShadowPhysicalPage ShadowGetPhysicalPage(FVSMPageOffset VSMPageOffset, Texture2D<uint> InPageTable)`
- L294-297 _function_ `FShadowPhysicalPage ShadowGetPhysicalPage(FVSMPageOffset VSMPageOffset)`
- L299-302 _function_ `uint VirtualShadowMapGetPageFlag(FVSMPageOffset VSMPageOffset)`
- L305-313 _function_ `FShadowPhysicalPage VirtualToPhysicalTexelBase(FVirtualSMLevelOffset PageTableLevelOffset, uint Level, uint2 VirtualTexelAddress, inout uint2 PhysicalTexelAddress)` — Returns true if the page is valid *for rendering*
- L316-319 _function_ `bool VirtualToPhysicalTexelForRendering(FVirtualSMLevelOffset PageTableLevelOffset, uint Level, uint2 VirtualTexelAddress, inout uint2 PhysicalTexelAddress)` — Returns true if the page is valid *for rendering*
- L322-325 _function_ `bool VirtualToPhysicalTexel(FVirtualSMLevelOffset PageTableLevelOffset, uint Level, uint2 VirtualTexelAddress, inout uint2 PhysicalTexelAddress)` — Returns true if the page is valid at all
- L327-330 _function_ `bool VirtualToPhysicalTexel(FVirtualShadowMapHandle VirtualShadowMapHandle, uint Level, uint2 VirtualTexelAddress, inout uint2 PhysicalTexelAddress)`
- L332-345 _function_ `bool VirtualToPhysicalPage(FVirtualSMLevelOffset PageTableLevelOffset, uint Level, int2 VirtualPageAddress, inout uint2 PhysicalPageAddress)`
- L357-371 _function_ `FShadowPageTranslationResult ShadowVirtualToPhysicalUV(FVirtualShadowMapHandle VirtualShadowMapHandle, float2 ShadowMapUV, uint MinMipLevel)` — Finds the best-resolution mapped page at the given UV
- L379-385 _function_ `uint PackPageInfo(FPageInfo PageInfo)`
- L387-393 _function_ `FPageInfo UnpackPageInfo(uint PackedData)`
- L395-398 _function_ `uint GetVirtualShadowMapStaticArrayIndex()`
- L400-403 _function_ `uint GetVirtualShadowMapHZBArrayIndex(bool bUseStaticOcclusion)`
- L406-424 _function_ `uint4 GatherPageTable(Texture2D<uint> PageTableTexture, uint2 TexelCoord, uint HMipLevel, float2 UVScaleFactor)` — Gather a 2x2 footprint from a page table texture.
- L426-436 _function_ `uint4 GatherPageTableRW(RWTexture2D<uint> PageTableTexture, uint2 TexelCoord)`

### `Shaders/Private/VirtualShadowMaps/VirtualShadowMapPageCacheCommon.ush` (Private)

- lines: 123; parse: all-branches
- includes: L8 `../Nanite/NaniteDataDecode.ush`, L9 `VirtualShadowMapProjectionStructs.ush`
- L6 #pragma `once`

#### Functions (7)

- L11-21 _function_ `bool ShouldMaterialInvalidateShadowCache(FPrimitiveSceneData PrimitiveData, bool bEnableWPO)`
- L26-44 _function_ `bool VirtualShadowMapIsWPOAllowed(FPrimitiveSceneData PrimitiveData, FVirtualShadowMapHandle VirtualShadowMapHandle)` — NOTE: This logic must be constant, or else we could miss invalidations if it swaps suddenly. Any changes to the underlying data (i.e. evaluate WPO flag) need to generate a GPUScene update and associated VSM instance invalidation.
- L46-49 _function_ `bool VirtualShadowMapIsWPOAllowed(FPrimitiveSceneData PrimitiveData, int VirtualShadowMapId)`
- L51-62 _function_ `bool GetCachePrimitiveAsDynamic(uint PersistentPrimitiveIndex)`
- L64-75 _function_ `bool GetCacheInstanceAsDynamic(uint InstanceId, int SceneRendererPrimaryViewId)`
- L80-92 _function_ `bool GetCacheTransitioned(uint InstanceId, int SceneRendererPrimaryViewId)` — Returns true if, for the currect view & frame, the instance transitioned from being static to dynamic or vice versa.
- L94-122 _function_ `bool ShouldCacheInstanceAsStatic(uint InstanceId, bool bViewUncached, bool bAllowWPO, int SceneRendererPrimaryViewId)`

### `Shaders/Private/VirtualShadowMaps/VirtualShadowMapPageManagement.usf` (Private)

- lines: 509; parse: all-branches
- includes: L7 `../Common.ush`, L8 `../WaveOpUtil.ush`, L9 `VirtualShadowMapProjectionStructs.ush`, L10 `VirtualShadowMapProjectionCommon.ush`, L11 `VirtualShadowMapPageAccessCommon.ush`, L12 `VirtualShadowMapStats.ush`, L13 `VirtualShadowMapPerPageDispatch.ush`

#### Macros (#define, 1)

- L225 `#define PROCESS_LEVEL(_Level_) if (_Level_ < MaxHLevel && !bDone) { bDone = ProcessMipLevel(OutPageFlagMips_##_Level_, Flag, GlobalPageTableEntryIndex, _Level_ + 1); }` (4 lines) _[#if defined(GenerateHierarchicalPageFlags)]_
- L237 #undef `PROCESS_LEVEL`

#### Entry points (3)

- L162-264 _entry_ `[numthreads(VSM_DEFAULT_CS_GROUP_X, 1, 1)] void GenerateHierarchicalPageFlags(uint ThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FGenerateHierarchicalPageFlagsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapArray.cpp:1432) — One thread per page physical table flag entry _[#if defined(GenerateHierarchicalPageFlags)]_
- L393-399 _entry_ `[numthreads(PER_PAGE_THREAD_GROUP_SIZE_XY, PER_PAGE_THREAD_GROUP_SIZE_XY, 1)] void PropagateMappedMips(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FPropagateMappedMipsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapArray.cpp:1749) — One thread per page in level 0, launched as 1d groups, with 2D grid with Y dim ==  NumFullShadowMaps. This is effectively just a big broadcast operation. There are more efficient ways to do this with fewer threads and wave ops, but given the page counts just relying on memory coalescing is good enough for now. _[#if defined(PropagateMappedMips)]_
- L500-506 _entry_ `[numthreads(PER_PAGE_THREAD_GROUP_SIZE_XY, PER_PAGE_THREAD_GROUP_SIZE_XY, 1)] void PropagateFilterableRequestsCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FPropagateFilterableRequestsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapArray.cpp:1763) _[#if defined(PropagateFilterableRequestsCS)]_

#### Structs / classes (2)

- L271-385 _struct_ **`FMappedMipPropagator`** `struct FMappedMipPropagator` _[#if defined(PropagateMappedMips)]_
  - L273 _method_ `void Run(FPerPageDispatchSetup Setup)` _[#if defined(PropagateMappedMips)]_
- L408-496 _struct_ **`FRequestPropagator`** `struct FRequestPropagator` _[#if defined(PropagateFilterableRequestsCS)]_
  - L410 _method_ `void Run(FPerPageDispatchSetup Setup)` _[#if defined(PropagateFilterableRequestsCS)]_

#### Global resources (textures / buffers / samplers) (21)

- L15 _resource_ `StructuredBuffer<FPhysicalPageMetaData> PhysicalPageMetaData;`
- L16 _resource_ `RWTexture2D<uint> OutPageTable;`
- L17 _resource_ `RWStructuredBuffer<uint4> OutUncachedPageRectBounds;`
- L18 _resource_ `RWStructuredBuffer<uint4> OutAllocatedPageRectBounds;`
- L77 _resource_ `Texture2D<uint> InPageFlags;` — Not yet set up in the UB _[#if defined(GenerateHierarchicalPageFlags)]_
- L78 _resource_ `Texture2D<uint> InPageReceiverMasks;` _[#if defined(GenerateHierarchicalPageFlags)]_
- L80 _resource_ `RWTexture2D<uint> OutPageFlagMips_0;` _[#if defined(GenerateHierarchicalPageFlags)]_
- L81 _resource_ `RWTexture2D<uint> OutPageFlagMips_1;` _[#if defined(GenerateHierarchicalPageFlags)]_
- L82 _resource_ `RWTexture2D<uint> OutPageFlagMips_2;` _[#if defined(GenerateHierarchicalPageFlags)]_
- L83 _resource_ `RWTexture2D<uint> OutPageFlagMips_3;` _[#if defined(GenerateHierarchicalPageFlags)]_
- L84 _resource_ `RWTexture2D<uint> OutPageFlagMips_4;` _[#if defined(GenerateHierarchicalPageFlags)]_
- L85 _resource_ `RWTexture2D<uint> OutPageFlagMips_5;` _[#if defined(GenerateHierarchicalPageFlags)]_
- L88 _resource_ `RWTexture2D<uint> OutPageReceiverMaskMips_0;` _[#if defined(GenerateHierarchicalPageFlags)]_
- L89 _resource_ `RWTexture2D<uint> OutPageReceiverMaskMips_1;` _[#if defined(GenerateHierarchicalPageFlags)]_
- L90 _resource_ `RWTexture2D<uint> OutPageReceiverMaskMips_2;` _[#if defined(GenerateHierarchicalPageFlags)]_
- L91 _resource_ `RWTexture2D<uint> OutPageReceiverMaskMips_3;` _[#if defined(GenerateHierarchicalPageFlags)]_
- L92 _resource_ `RWTexture2D<uint> OutPageReceiverMaskMips_4;` _[#if defined(GenerateHierarchicalPageFlags)]_
- L93 _resource_ `RWTexture2D<uint> OutPageReceiverMaskMips_5;` _[#if defined(GenerateHierarchicalPageFlags)]_
- L94 _resource_ `RWTexture2D<uint> OutPageReceiverMaskMips_6;` _[#if defined(GenerateHierarchicalPageFlags)]_
- L405 _resource_ `RWTexture2D<uint> InOutPageRequestFlags;` _[#if defined(PropagateFilterableRequestsCS)]_
- L406 _resource_ `RWTexture2D<uint> InOutPageReceiverMasks;` _[#if defined(PropagateFilterableRequestsCS)]_

#### Functions (7)

- L21-47 _function_ `uint MipMask8x4(uint2 Mask2x1)` — Mip a 2x1 (i.e., 8x4 bit) mask into a 4x4 mask
- L50-62 _function_ `uint MipMask8x8(uint4 Mask2x2)` — Mip a 2x2 (i.e., 8x8 bit) mask into a 4x4 mask
- L65-72 _function_ `uint MipMask4x4(uint Mask4x4, uint2 FracPos)` — Mip a 4x4 mask & use fractional position to position inside resulting 4x4 mask
- L97-106 _function_ `bool ProcessMipLevel(RWTexture2D<uint> OutPageFlagMip, uint Flag, FVSMPageOffset PageOffset, uint HMipLevel)` _[#if defined(GenerateHierarchicalPageFlags)]_
- L109-142 _function_ `bool IntersectMask8x8(uint4 Mask2x2, uint2 Min, uint2 Max)` _[#if defined(GenerateHierarchicalPageFlags)]_
- L145-151 _function_ `void ProcessMaskMip4x4(RWTexture2D<uint> OutPageReceiverMaskMip, inout uint Mask4x4, inout uint2 MaskAddress)` _[#if defined(GenerateHierarchicalPageFlags)]_
- L154-157 _function_ `uint4 GatherReceiverMask(uint2 TexelCoord)` — Gather a 2x2 footprint given the upper-left coordinate _[#if defined(GenerateHierarchicalPageFlags)]_

### `Shaders/Private/VirtualShadowMaps/VirtualShadowMapPageMarking.usf` (Private)

- lines: 874; parse: all-branches
- includes: L9 `VirtualShadowMapPageMarking.ush`, L10 `/Engine/Shared/SingleLayerWaterDefinitions.h`, L11 `../HairStrands/HairStrandsVisibilityCommonStruct.ush`, L12 `../Common.ush`, L13 `../WaveOpUtil.ush`, L14 `../LightGridCommon.ush`, L15 `../SceneTexturesCommon.ush`, L16 `../DeferredShadingCommon.ush`, L17 `../HairStrands/HairStrandsVisibilityCommon.ush`, L18 `../HairStrands/HairStrandsTileCommon.ush`, L19 `../Substrate/Substrate.ush`, L20 `VirtualShadowMapProjectionDirectional.ush`, L21 `VirtualShadowMapProjectionSpot.ush`, L22 `VirtualShadowMapProjectionCommon.ush`, L23 `VirtualShadowMapStats.ush`, L24 `VirtualShadowMapLightGrid.ush`, L25 `../ShaderPrint.ush`, L26 `../Froxel/Froxel.ush`, L27 `../Nanite/NaniteHZBCull.ush`

#### Macros (#define, 4)

- L7 `#define VSM_WITH_DOF_BIAS 1`
- L30 `#define INPUT_TYPE_GBUFFER 0`
- L31 `#define INPUT_TYPE_HAIRSTRANDS 1`
- L32 `#define INPUT_TYPE_GBUFFER_AND_WATER_DEPTH 2`

#### Entry points (4)

- L209-274 _entry_ `[numthreads(VSM_DEFAULT_CS_GROUP_X, 1, 1)] void PruneLightGridCS(uint GridLinearIndex : SV_DispatchThreadID)` — stage: **compute** — C++: `FPruneLightGridCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapArray.cpp:1256)
- L319-615 _entry_ `[numthreads(SLW_TILE_SIZE_XY, SLW_TILE_SIZE_XY, 1)] void GeneratePageFlagsFromPixels( uint3 InGroupId : SV_GroupID, uint GroupIndex : SV_GroupIndex, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FGeneratePageFlagsFromPixelsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapArray.cpp:1368) — Note: we use the tile size defined by the water as the group-size - this is needed because the tile mask testing code relies on the size being the same to scalarize efficiently.
- L646-792 _entry_ `[numthreads(FROXEL_INDIRECT_ARG_WORKGROUP_SIZE, 1, 1)] void GeneratePageFlagsFromFroxelsCS(uint FroxelIndex : SV_DispatchThreadID)` — stage: **compute** — C++: `FGeneratePageFlagsFromFroxelsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapArray.cpp:1399) _[#if defined(GeneratePageFlagsFromFroxelsCS)]_
- L799-873 _entry_ `[numthreads(VSM_DEFAULT_CS_GROUP_X, 1, 1)] void MarkCoarsePages(uint DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FMarkCoarsePagesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapArray.cpp:1413)

#### Structs / classes (2)

- L45-51 _struct_ **`FFroxelDebugDrawSetup`** `struct FFroxelDebugDrawSetup`
  - L48 _member_ `FShaderPrintContext Context;` _[#if DEBUG_DRAW_GENERATE_FROM_FROXELS]_
  - L49 _member_ `bool bDraw;` _[#if DEBUG_DRAW_GENERATE_FROM_FROXELS]_
- L293-299 _struct_ **`FPositionData`** `struct FPositionData`
  - L295 _member_ `float SceneDepth;`
  - L296 _member_ `float4 SvPosition;`
  - L297 _member_ `float3 TranslatedWorldPosition;`
  - L298 _member_ `float DeviceZ;`

#### Global resources (textures / buffers / samplers) (9)

- L34 _resource_ `StructuredBuffer<uint> ThrottleBuffer;`
- L206 _resource_ `RWStructuredBuffer<uint> OutPrunedLightGridData;`
- L207 _resource_ `RWStructuredBuffer<uint> OutPrunedNumCulledLightsGrid;`
- L279 _resource_ `Texture2D<float> SingleLayerWaterDepthTexture;` _[#if PERMUTATION_WATER_DEPTH]_
- L280 _resource_ `StructuredBuffer< uint > SingleLayerWaterTileMask;` _[#if PERMUTATION_WATER_DEPTH]_
- L289 _resource_ `Texture2D<float> FrontLayerTranslucencyDepthTexture;` _[#if PERMUTATION_TRANSLUCENCY_DEPTH]_
- L290 _resource_ `Texture2D<float4> FrontLayerTranslucencyNormalTexture;` _[#if PERMUTATION_TRANSLUCENCY_DEPTH]_
- L619 _resource_ `StructuredBuffer<FPackedFroxel> Froxels;` _[#if defined(GeneratePageFlagsFromFroxelsCS)]_
- L620 _resource_ `Buffer<uint> FroxelArgs;` _[#if defined(GeneratePageFlagsFromFroxelsCS)]_

#### Global parameters (uniforms) (20)

- L36 _parameter_ `float PageDilationBorderSizeDirectional;`
- L37 _parameter_ `float PageDilationBorderSizeLocal;`
- L38 _parameter_ `uint InputType;`
- L39 _parameter_ `uint bCullBackfacingPixels;`
- L42 _parameter_ `int PassId;` _[#if defined(GeneratePageFlagsFromFroxelsCS)]_
- L203 _parameter_ `uint MinLocalLightIndex;`
- L204 _parameter_ `uint MaxLocalLightIndex;`
- L205 _parameter_ `int bIncludeMegaLights;`
- L276 _parameter_ `uint2 PixelStride;`
- L281 _parameter_ `int2 SingleLayerWaterTileViewRes;` _[#if PERMUTATION_WATER_DEPTH]_
- L285 _parameter_ `uint FrontLayerMode;` _[#if PERMUTATION_TRANSLUCENCY_DEPTH]_
- L286 _parameter_ `float4 FrontLayerHistoryUVMinMax;` _[#if PERMUTATION_TRANSLUCENCY_DEPTH]_
- L287 _parameter_ `float4 FrontLayerHistoryScreenPositionScaleBias;` _[#if PERMUTATION_TRANSLUCENCY_DEPTH]_
- L288 _parameter_ `float4 FrontLayerHistoryBufferSizeAndInvSize;` _[#if PERMUTATION_TRANSLUCENCY_DEPTH]_
- L315 _parameter_ `float FirstPersonPixelRequestBias;` — Bias applied to pixels originating from first-person geometry, if negative marking is skipped for these
- L316 _parameter_ `int FirstPersonPixelRequestLevelClamp;`
- L643 _parameter_ `uint bShouldMarkLocaLights;` _[#if defined(GeneratePageFlagsFromFroxelsCS)]_
- L644 _parameter_ `float DebugRange;` _[#if defined(GeneratePageFlagsFromFroxelsCS)]_
- L796 _parameter_ `uint bMarkCoarsePagesLocal;`
- L797 _parameter_ `uint bIncludeNonNaniteGeometry;`

#### Functions (6)

- L53-64 _function_ `uint MakeMask4x4(uint2 Min, uint2 Max)`
- L67-173 _function_ `void MarkPageFroxel( FVirtualShadowMapProjectionShaderData ProjectionData, bool bUsePageDilation, float2 PageDilationOffset, float3 TranslatedWorldPosition, FFroxelViewBounds FroxelViewAabb, uint MipLevel, bool bDirectionalLight, FFroxelDebugDrawSetup FroxelDebugDrawSetup)`
- L176-201 _function_ `void MarkPageClipmapFroxel( FVirtualShadowMapProjectionShaderData BaseProjectionData, bool bUsePageDilation, float2 PageDilationOffset, float3 TranslatedWorldPosition, FFroxelViewBounds FroxelViewAabb, FFroxelDebugDrawSetup FroxelDebugDrawSetup, float ExtraBias = 0.0f, int MinLevelClamp = 0)`
- L301-312 _function_ `FPositionData InitPositionData(uint2 PixelPos, float DeviceZ, bool bIsValid)`
- L622-625 _function_ `int3 LoadFroxel(uint Index)` _[#if defined(GeneratePageFlagsFromFroxelsCS)]_
- L627-641 _function_ `FCulledLightsGridHeader VirtualShadowMapGetLightsGridForFroxel(int3 FroxelCoord, float FroxelCenterViewZ)` _[#if defined(GeneratePageFlagsFromFroxelsCS)]_

### `Shaders/Private/VirtualShadowMaps/VirtualShadowMapPageMarking.ush` (Private)

- lines: 175; parse: all-branches
- includes: L8 `../Common.ush`, L9 `../LightData.ush`, L10 `VirtualShadowMapProjectionStructs.ush`, L11 `VirtualShadowMapProjectionCommon.ush`
- L6 #pragma `once`

#### Global resources (textures / buffers / samplers) (2)

- L14 _resource_ `RWTexture2D<uint> OutPageRequestFlags;` — Flags generated by per-pixel pass to determine which pages are required to provide shadow for the visible geometry
- L15 _resource_ `RWTexture2D<uint> OutPageReceiverMasks;`

#### Functions (9)

- L18-39 _function_ `int GetBiasedClipmapLevel(FVirtualShadowMapProjectionShaderData BaseProjectionData, float3 TranslatedWorldPosition, float ExtraBias)` — NOTE: Returned absolute clipmap level can be negative; these are well defined
- L41-49 _function_ `uint GetMipLevelLocal(FVirtualShadowMapProjectionShaderData ProjectionData, float3 TranslatedWorldPosition, float SceneDepth, float ExtraBias = 0.0f)`
- L51-54 _function_ `uint GetMipLevelLocal(FVirtualShadowMapHandle VirtualShadowMapHandle, float3 TranslatedWorldPosition, float SceneDepth, float ExtraBias = 0.0f)`
- L56-60 _function_ `void MarkPageAddress(FVSMPageOffset PageOffset, uint Flags)`
- L62-69 _function_ `void MarkFullPageReceiverMask(FVSMPageOffset PageOffset)`
- L71-80 _function_ `void MarkPageReceiverMask(FVSMPageOffset PageOffset, uint2 VirtualAddress)`
- L82-137 _function_ `void MarkPage(FVirtualShadowMapHandle VirtualShadowMapHandle, uint MipLevel, float3 TranslatedWorldPosition, bool bUsePageDilation, float2 PageDilationOffset)`
- L139-154 _function_ `void MarkPageDirectional( FVirtualShadowMapHandle VirtualShadowMapHandle, float3 TranslatedWorldPosition, bool bUsePageDilation = false, float2 PageDilationOffset = float2(0, 0), float ExtraBias = 0.0f, int MinLevelClamp = -10000)`
- L156-174 _function_ `void MarkPageLocal( FDeferredLightData Light, FVirtualShadowMapHandle VirtualShadowMapHandle, float3 TranslatedWorldPosition, float SceneDepth, bool bUsePageDilation = false, float2 PageDilationOffset = float2(0, 0), float LocalExtraBias = 0.0f)`

### `Shaders/Private/VirtualShadowMaps/VirtualShadowMapPageOverlap.ush` (Private)

- lines: 465; parse: all-branches
- includes: L5 `../Common.ush`, L6 `../Nanite/NaniteHZBCull.ush`, L7 `../Nanite/NaniteDataDecode.ush`, L8 `../SceneData.ush`, L9 `VirtualShadowMapPageAccessCommon.ush`, L10 `VirtualShadowMapPageCacheCommon.ush`

#### Macros (#define, 6)

- L398 `#define VSM_MARK_PAGE_DIRTY_FLAG_DYNAMIC 1`
- L399 `#define VSM_MARK_PAGE_DIRTY_FLAG_STATIC 2`
- L400 `#define VSM_MARK_PAGE_DIRTY_FLAG_INVALIDATE_DYNAMIC 4`
- L401 `#define VSM_MARK_PAGE_DIRTY_FLAG_INVALIDATE_STATIC 8`
- L402 `#define VSM_MARK_PAGE_DIRTY_FLAG_WPO_ALLOWED 16`
- L403 `#define VSM_MARK_PAGE_DIRTY_FLAG_INVALIDATE_LOD_DELTA 32`
- L3 #pragma `once`

#### Structs / classes (1)

- L210-217 _struct_ **`FPageTestScreenRect`** `struct FPageTestScreenRect` — Wrapper type to make misuse slightly harder.
  - L212 _member_ `FScreenRect ScreenRect;`
  - L213 _member_ `uint HZBLevelPageSizeShift;`
  - L214 _member_ `int HZBLevelPageSizeInclusive;`
  - L215 _member_ `uint4 RectPages;`
  - L216 _member_ `bool bWasPageRectClipped;`

#### Global resources (textures / buffers / samplers) (4)

- L12 _resource_ `Texture2D<uint> HZBPageTable;`
- L13 _resource_ `StructuredBuffer<uint4> HZBPageRectBounds;`
- L14 _resource_ `Texture2D<uint> HZBPageFlags;`
- L395 _resource_ `RWStructuredBuffer<uint> OutDirtyPageFlags;`

#### Functions (21)

- L16-19 _function_ `uint4 VirtualShadowMapGetPageRect(FScreenRect Rect)`
- L21-25 _function_ `uint4 VirtualShadowMapClipPageRect(uint4 RectPages, FVirtualShadowMapHandle VirtualShadowMapHandle, uint MipLevel, StructuredBuffer<uint4> PageRectBoundsBuffer)`
- L27-34 _function_ `uint4 VirtualShadowMapGetAllocatedPageRect(FScreenRect Rect, FVirtualShadowMapHandle VirtualShadowMapHandle, uint MipLevel)`
- L36-43 _function_ `uint4 VirtualShadowMapGetUncachedPageRect(FScreenRect Rect, FVirtualShadowMapHandle VirtualShadowMapHandle, uint MipLevel)`
- L45-54 _function_ `FScreenRect VirtualShadowMapClipScreenRect(FScreenRect ScreenRect, FVirtualShadowMapHandle VirtualShadowMapHandle, uint MipLevel, StructuredBuffer<uint4> PageRectBoundsBuffer)`
- L59-62 _function_ `FScreenRect VirtualShadowMapGetUncachedScreenRect(FScreenRect ScreenRect, FVirtualShadowMapHandle VirtualShadowMapHandle, uint MipLevel)` — Same but returns the clamped pixel rect rather than the page rect.
- L64-67 _function_ `uint4 GatherPageFlags(uint2 TexelCoord, uint HMipLevel)`
- L69-73 _function_ `uint4 GatherReceiverMask(uint2 TexelCoord, uint HMipLevel)`
- L75-86 _function_ `bool TestPageFlagMask(uint PageFlags, uint PageFlagMask)`
- L91-115 _function_ `bool OverlapsAnyValidPage(FVirtualShadowMapHandle VirtualShadowMapHandle, uint MipLevel, uint4 RectPages, uint InFlagMask, bool bDetailGeometry)` — Returns true if ANY flags in FlagMask are set on at least one overlapped page (see GetPageFlagMaskForRendering below) NOTE: Only VSM_FLAG_* are allowed to be used here, not VSM_EXTENDED_*, as this does a hierarchical page flag lookup If bDetailGeometry is set, additionally tests whether at least one page has VSM_FLAG_DETAIL_GEOMETRY marked on it
- L117-150 _function_ `bool IntersectMask8x8(uint4 Mask2x2, uint2 Min, uint2 Max)`
- L155-205 _function_ `bool OverlapsAnyValidPage(FVirtualShadowMapHandle VirtualShadowMapHandle, uint MipLevel, FScreenRect ClampedScreenRect, uint InFlagMask, bool bDetailGeometry, bool bUseReceiverMask)` — Expectes a pixel rect clamped to the valid page region but still in pixels rather than pages.
- L224-244 _function_ `FPageTestScreenRect SetupPageHZBRect(FScreenRect ScreenRect, FVirtualShadowMapHandle VirtualShadowMapHandle, uint MipLevel)` — Set up a screen rect and pre-computed data for testing pages against HZB, this assumes a 4x4-HZB FScreenRect as input. The resulting rect has been clamped to the mip level where a page is 4x4 texels, as higher mips are meaningless.
- L247-267 _function_ `bool IsPageVisibleHZB(uint2 vPage, FVSMPageOffset PageFlagOffset, bool bTreatUnmappedAsOccluded, FPageTestScreenRect PageTestScreenRect, bool bUseStaticOcclusion)`
- L275-321 _function_ `bool IsVisibleMaskedHZB(FVirtualShadowMapHandle PrevShadowMapHandle, uint MipLevel, FScreenRect Rect, bool bClampToPageLevel, bool bTreatUnmappedAsOccluded, uint VisiblePageMask, uint TestPageMask, bool bUseStaticOcclusion)` — Perform HZB-Test for a rectangle of pages, returning true if the Rect is visible in at least one page. @param TestPageMask - page flags to inlcude in occlusion test, e.g., VSM_FLAG_ALLOCATED will test any allocated page, but ignore unallocated ones. @param VisiblePageMask - page flags to treat as un-occluded, tested after the above mask, e.g., use VSM_UNCACHED_FLAG to treat any uncached page as visible.
- L329-332 _function_ `bool IsVisibleMaskedHZB(uint PrevShadowMapID, uint MipLevel, FScreenRect Rect, bool bClampToPageLevel, bool bTreatUnmappedAsOccluded, uint VisiblePageMask, uint TestPageMask, bool bUseStaticOcclusion)` — Perform HZB-Test for a rectangle of pages, returning true if the Rect is visible in at least one page. @param TestPageMask - page flags to inlcude in occlusion test, e.g., VSM_FLAG_ALLOCATED will test any allocated page, but ignore unallocated ones. @param VisiblePageMask - page flags to treat as un-occluded, tested after the above mask, e.g., use VSM_UNCACHED_FLAG to treat any uncached page as visible.
- L334-346 _function_ `uint GetPageFlagMaskForRendering(bool bCacheAsStatic, uint InstanceId, int SceneRendererPrimaryViewId)`
- L348-362 _function_ `float CalcClipSpaceRadiusEstimate(bool bIsOrtho, FInstanceSceneData InstanceData, float4x4 LocalToTranslatedWorld, float4x4 ViewToClip)`
- L370-392 _function_ `bool IsDetailGeometry(bool bCacheAsStatic, bool bIsNaniteGeometry, float InstancePixelEstRadius)` — Figure out the coarse page flag for a given footprint pixel-radius of an instance (estimated from bounds). IF the footprint is considered "small" and thus a candidate for not rendering to coarse pages, we return true - which means it will get compared against the same flag in the page flags in the footprint. When the comparison is not 1 (i.e., for a page _not_ marked with VSM_FLAG_DETAIL_GEOMETRY) the instance is culled. This test should only be performed at the instance level, as it does not make sense to partially cull geometry, (e.g, creating holes based on varying cluster size).
- L405-426 _function_ `uint VirtualShadowMapGetMarkPageDirtyFlags( bool bCacheAsStatic, bool bInvalidatePage, bool bWPOAllowed, bool bInvalidateLODDelta)`
- L428-464 _function_ `bool VirtualShadowMapMarkPageDirty( FVSMPageOffset PageFlagOffset, uint MarkPageDirtyFlags)`

### `Shaders/Private/VirtualShadowMaps/VirtualShadowMapPerPageDispatch.ush` (Private)

- lines: 133; parse: all-branches
- includes: L4 `../Common.ush`
- L2 #pragma `once`

#### Structs / classes (1)

- L17-130 _struct_ **`FPerPageDispatchSetup`** `struct FPerPageDispatchSetup` — Helper to set up the per-thread indexing to process all relevant pages in the page table. _[#if defined(PER_PAGE_DISPATCH_SETUP)]_
  - L19 _member_ `bool bValid;` _[#if defined(PER_PAGE_DISPATCH_SETUP)]_
  - L20 _member_ `FVirtualShadowMapHandle VirtualShadowMapHandle;` _[#if defined(PER_PAGE_DISPATCH_SETUP)]_
  - L22 _member_ `uint2 LoopStart;` _[#if defined(PER_PAGE_DISPATCH_SETUP)]_
  - L23 _member_ `uint LoopStride;` _[#if defined(PER_PAGE_DISPATCH_SETUP)]_
  - L25 _member_ `uint PageStartOffset;` _[#if defined(PER_PAGE_DISPATCH_SETUP)]_
  - L26 _member_ `uint PageEndOffset;` _[#if defined(PER_PAGE_DISPATCH_SETUP)]_
  - L27 _member_ `uint MipLevelStart;` _[#if defined(PER_PAGE_DISPATCH_SETUP)]_
  - L28 _member_ `uint MipLevelEnd;` _[#if defined(PER_PAGE_DISPATCH_SETUP)]_
  - L30 _method_ `void Init(uint3 DispatchThreadId)` _[#if defined(PER_PAGE_DISPATCH_SETUP)]_
  - L74 _method_ `uint GetLoopEnd(uint MipLevel)` _[#if defined(PER_PAGE_DISPATCH_SETUP)]_
  - L79 _method_ `template <typename FWorkType> void ExecuteInternal(inout FWorkType Work)` _[#if defined(PER_PAGE_DISPATCH_SETUP)]_
  - L101 _method_ `template <typename FWorkType> void Execute(uint3 DispatchThreadId, inout FWorkType Work)` _[#if defined(PER_PAGE_DISPATCH_SETUP)]_

#### Global resources (textures / buffers / samplers) (1)

- L8 _resource_ `StructuredBuffer<uint> VirtualShadowMapIds;` _[#if defined(PER_PAGE_DISPATCH_SETUP)]_

#### Global parameters (uniforms) (4)

- L9 _parameter_ `uint NumVirtualShadowMapIds;` _[#if defined(PER_PAGE_DISPATCH_SETUP)]_
- L10 _parameter_ `uint VirtualShadowMapIdsOffset;` _[#if defined(PER_PAGE_DISPATCH_SETUP)]_
- L11 _parameter_ `uint PerPageDispatchDimXY;` _[#if defined(PER_PAGE_DISPATCH_SETUP)]_
- L12 _parameter_ `uint bUseThreadPerId;` _[#if defined(PER_PAGE_DISPATCH_SETUP)]_

### `Shaders/Private/VirtualShadowMaps/VirtualShadowMapPhysicalPageManagement.usf` (Private)

- lines: 1953; parse: all-branches
- includes: L7 `../Common.ush`, L8 `../WaveOpUtil.ush`, L9 `../ReductionCommon.ush`, L10 `../GPUMessaging.ush`, L11 `../ShaderPrint.ush`, L12 `/Engine/Shared/VirtualShadowMapDefinitions.h`, L13 `VirtualShadowMapProjectionStructs.ush`, L14 `VirtualShadowMapProjectionCommon.ush`, L15 `VirtualShadowMapPageAccessCommon.ush`, L16 `VirtualShadowMapStats.ush`, L17 `VirtualShadowMapPerPageDispatch.ush`, L683 `../ThreadGroupPrefixSum.ush`

#### Macros (#define, 25)

- L20 `#define HAS_CACHE_DATA 1` _[#if !defined(HAS_CACHE_DATA)]_
- L34 `#define PHYSICAL_PAGE_LIST_LRU 0`
- L37 `#define PHYSICAL_PAGE_LIST_AVAILABLE 1`
- L39 `#define PHYSICAL_PAGE_LIST_EMPTY 2`
- L41 `#define PHYSICAL_PAGE_LIST_REQUESTED 3`
- L43 `#define PHYSICAL_PAGE_LIST_COUNT 4`
- L549 `#define HAS_MIP_LEVELS (NUM_MIP_LEVELS > 1)` _[#if defined(ClearPageTableCS)]_
- L595 `#define DO_MIP_LEVEL(_HLevel_) ClearMip(OutDestBufferMips_##_HLevel_,_HLevel_ + 1, LevelOffset, uint2(PageX, PageY), 2u, MipLevel)` _[#if defined(ClearPageTableCS) && HAS_MIP_LEVELS]_
- L615 `#define DO_MIP_LEVEL(_HLevel_) ClearMip(OutDestBufferMips_##_HLevel_,_HLevel_ + 1, LevelOffset, uint2(PageX, PageY), 1u, MipLevel)` _[#if defined(ClearPageTableCS) && HAS_MIP_LEVELS]_
- L682 `#define NUM_THREADS_PER_GROUP 1024`
- L814 `#define LOG2_TILE_THREAD_GROUP_SIZE_XY 4u`
- L815 `#define TILE_THREAD_GROUP_SIZE_XY (1u << LOG2_TILE_THREAD_GROUP_SIZE_XY)`
- L818 `#define LOG2_TILE_SIZE_XY (LOG2_TILE_THREAD_GROUP_SIZE_XY + 1u)`
- L825 `#define LOG2_TILES_PER_PAGE_XY ( VSM_LOG2_PAGE_SIZE - LOG2_TILE_SIZE_XY )`
- L827 `#define LOG2_TILES_PER_PAGE_1D ( 2U * LOG2_TILES_PER_PAGE_XY )`
- L829 `#define TILES_PER_PAGE_1D ( 1U << LOG2_TILES_PER_PAGE_1D )`
- L831 `#define TILES_PER_PAGE_XY_MASK ( ( 1U << LOG2_TILES_PER_PAGE_XY ) - 1U )`
- L832 `#define TILES_PER_PAGE_1D_MASK ( ( 1U << LOG2_TILES_PER_PAGE_1D ) - 1U )`
- L1110 `#define SEPARABLE_KERNEL_EXT (2)`
- L1111 `#define SEPARABLE_DISABLE_BLUR 0`
- L1716 `#define DIM_FURTHEST 1`
- L1717 `#define DIM_CLOSEST 0`
- L1722 `#define COND_OUTPUT_LEVEL(_level_) if (MipLevel == _level_) { FurthestHZBArrayOutput_##_level_[uint3(OutputPixelPos, ArrayIndex)] = FurthestDeviceZ; return; }` (6 lines) _[#if DIM_FURTHEST]_
- L1850 `#define TOP_MIP_TILE_SIZE_XY 4`
- L1852 `#define TOP_MIP_TILE_THREAD_GROUP_SIZE_XY (TOP_MIP_TILE_SIZE_XY/2)`
- L606 #undef `DO_MIP_LEVEL`; L626 #undef `DO_MIP_LEVEL`; L724 #undef `NUM_THREADS_PER_GROUP`; L1738 #undef `COND_OUTPUT_LEVEL`

#### Entry points (21)

- L116-144 _entry_ `[numthreads(VSM_DEFAULT_CS_GROUP_X, 1, 1)] void InitPageRectBounds(uint3 Index : SV_DispatchThreadID)` — stage: **compute** — C++: `FInitPageRectBoundsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapArray.cpp:2176) — This is admitadly a weird fusion of several initializations but it is the first thing we run in a given analysis phase so it's more efficient to do it all here rather than have several small passes later.
- L154-222 _entry_ `[numthreads(VSM_DEFAULT_CS_GROUP_X, 1, 1)] void UpdatePhysicalPageAddresses(uint3 Index : SV_DispatchThreadID)` — stage: **compute** — C++: `FUpdatePhysicalPageAddresses` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapArray.cpp:1455)
- L235-473 _entry_ `[numthreads(VSM_DEFAULT_CS_GROUP_X, 1, 1)] void UpdatePhysicalPages(uint3 Index : SV_DispatchThreadID)` — stage: **compute** — C++: `FUpdatePhysicalPages` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapArray.cpp:1486)
- L637-643 _entry_ `[numthreads(PER_PAGE_THREAD_GROUP_SIZE_XY, PER_PAGE_THREAD_GROUP_SIZE_XY, 1)] void ClearPageTableCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FClearPageTableCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapArray.cpp:1687) _[#if defined(ClearPageTableCS)]_
- L670-676 _entry_ `[numthreads(PER_PAGE_THREAD_GROUP_SIZE_XY, PER_PAGE_THREAD_GROUP_SIZE_XY, 1)] void AllocateNewPageMappingsCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FAllocateNewPageMappingsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapArray.cpp:1709) _[#if defined(AllocateNewPageMappingsCS)]_
- L685-722 _entry_ `[numthreads(NUM_THREADS_PER_GROUP, 1, 1)] void PackAvailablePages(uint GroupIndex : SV_GroupIndex)` — stage: **compute** — C++: `FPackAvailablePagesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapArray.cpp:1722)
- L731-799 _entry_ `[numthreads(VSM_DEFAULT_CS_GROUP_X, 1, 1)] void AppendPhysicalPageLists(uint ThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FAppendPhysicalPageListsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapArray.cpp:1736)
- L851-907 _entry_ `[numthreads(VSM_DEFAULT_CS_GROUP_X, 1, 1)] void SelectPagesToInitializeCS(uint PhysicalPageIndex : SV_DispatchThreadID)` — stage: **compute** — C++: `FSelectPagesToInitializeCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapArray.cpp:1782)
- L992-1017 _entry_ `[numthreads(TILE_THREAD_GROUP_SIZE_XY, TILE_THREAD_GROUP_SIZE_XY, 1)] void InitializePhysicalPagesIndirectCS(uint2 TileThreadID : SV_GroupThreadID, uint GroupIndex : SV_GroupID)` — stage: **compute** — C++: `FInitializePhysicalPagesIndirectCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapArray.cpp:1797)
- L1027-1070 _entry_ `[numthreads(VSM_DEFAULT_CS_GROUP_X, 1, 1)] void SelectPagesToPostProcessCS(uint PhysicalPageIndex : SV_DispatchThreadID)` — stage: **compute** — C++: `FSelectPagesToPostProcessCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapArray.cpp:1818) _[#if defined(SelectPagesToPostProcessCS)]_
- L1076-1086 _entry_ `[numthreads(TILE_THREAD_GROUP_SIZE_XY, TILE_THREAD_GROUP_SIZE_XY, 1)] void MergeStaticPhysicalPagesIndirectCS(uint2 TileThreadID : SV_GroupThreadID, uint GroupIndex : SV_GroupID)` — stage: **compute** — C++: `FMergeStaticPhysicalPagesIndirectCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapArray.cpp:1832)
- L1166-1225 _entry_ `[numthreads(128, 1, 1)] void UpdateFilterablePagesSeparableX_CS(uint GroupThreadIndex : SV_GroupIndex, uint GroupIndex : SV_GroupID)` — stage: **compute** — C++: `FUpdateFilterablePagesSeparableX_CS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapArray.cpp:1859) — one thread per texel _[#if defined(UpdateFilterablePagesSeparableX_CS)]_
- L1281-1374 _entry_ `[numthreads(128, 1, 1)] void UpdateFilterablePagesSeparableY_CS(uint GroupThreadIndex : SV_GroupIndex, uint GroupIndex : SV_GroupID)` — stage: **compute** — C++: `FUpdateFilterablePagesSeparableY_CS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapArray.cpp:1885) — one thread per texel _[#if defined(UpdateFilterablePagesSeparableY_CS)]_
- L1408-1448 _entry_ `[numthreads(128, 1, 1)] void GatherFilterableBorderTexels_CS(uint GroupThreadIndex : SV_GroupIndex, uint GroupIndex : SV_GroupID)` — stage: **compute** — C++: `FGatherFilterableBorderTexels_CS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapArray.cpp:1901) _[#if defined(GatherFilterableBorderTexels_CS)]_
- L1469-1575 _entry_ `[numthreads(TILE_THREAD_GROUP_SIZE_XY, TILE_THREAD_GROUP_SIZE_XY, 1)] void MergeDownFilterablePagesCS(uint2 TileThreadID : SV_GroupThreadID, uint GroupIndex : SV_GroupID)` — stage: **compute** — C++: `FMergeDownFilterablePagesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapArray.cpp:1918) _[#if defined(MergeDownFilterablePagesCS)]_
- L1627-1636 _entry_ `[numthreads(VSM_DEFAULT_CS_GROUP_X, 1, 1)] void UpdateAndClearDirtyFlagsCS(uint PhysicalPageIndex : SV_DispatchThreadID)` — stage: **compute** — C++: `FUpdateAndClearDirtyFlagsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapArray.cpp:1931)
- L1643-1681 _entry_ `[numthreads(VSM_DEFAULT_CS_GROUP_X, 1, 1)] void SelectPagesForHZBAndUpdateDirtyFlagsCS(uint PhysicalPageIndex : SV_DispatchThreadID)` — stage: **compute** — C++: `FSelectPagesForHZBAndUpdateDirtyFlagsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapArray.cpp:4782)
- L1808-1837 _entry_ `[numthreads(TILE_THREAD_GROUP_SIZE_XY, TILE_THREAD_GROUP_SIZE_XY, 1)] void BuildHZBPerPageCS(uint GroupThreadIndex : SV_GroupIndex, uint GroupIndex : SV_GroupID)` — stage: **compute** — C++: `FVirtualSmBuildHZBPerPageCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapArray.cpp:4805)
- L1895-1913 _entry_ `[numthreads(TOP_MIP_TILE_THREAD_GROUP_SIZE_XY, TOP_MIP_TILE_THREAD_GROUP_SIZE_XY, 1)] void BuildHZBPerPageTopCS(uint2 GroupThreadId : SV_GroupThreadID, uint PageInputIndex : SV_GroupID)` — stage: **compute** — C++: `FVirtualSmBBuildHZBPerPageTopCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapArray.cpp:4827)
- L1918-1931 _entry_ `[numthreads(1, 1, 1)] void FeedbackStatusCS()` — stage: **compute** — C++: `FVirtualSmFeedbackStatusCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapArray.cpp:2197)
- L1937-1952 _entry_ `[numthreads(1, 1, 1)] void LogPageListStatsCS()` — stage: **compute** — C++: `FVirtualSmLogPageListStatsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapArray.cpp:3734)

#### Structs / classes (5)

- L572-633 _struct_ **`FClearPageTableWorker`** `struct FClearPageTableWorker` _[#if defined(ClearPageTableCS)]_
  - L574 _method_ `void Run(FPerPageDispatchSetup Setup)` _[#if defined(ClearPageTableCS)]_
- L649-666 _struct_ **`FAllocateNewPageMappingsWorker`** `struct FAllocateNewPageMappingsWorker` _[#if defined(AllocateNewPageMappingsCS)]_
  - L651 _method_ `void Run(FPerPageDispatchSetup Setup)` _[#if defined(AllocateNewPageMappingsCS)]_
- L909-913 _struct_ **`FTileInputSetup`** `struct FTileInputSetup`
  - L911 _member_ `uint2 TileOffsetInPage;`
  - L912 _member_ `uint PageInputIndex;`
- L926-935 _struct_ **`FTileSetup`** `struct FTileSetup`
  - L928 _member_ `FPhysicalPageMetaData MetaData;`
  - L929 _member_ `uint PageIndex;`
  - L930 _member_ `uint ArrayIndex;`
  - L932 _member_ `uint2 PhysPageAddress;`
  - L934 _member_ `uint2 TileOffsetInPage;`
- L1116-1121 _struct_ **`FBorderSampleData`** `struct FBorderSampleData`
  - L1118 _member_ `bool bSrcPosValid;`
  - L1119 _member_ `uint2 SrcPos;`
  - L1120 _member_ `int DestTempIndex;`

#### Global resources (textures / buffers / samplers) (56)

- L24 _resource_ `Texture2D<uint> PageRequestFlags;` — Page flags generated by page allocation to indicate state to rendering passes (i.e., present / invalid)
- L25 _resource_ `RWTexture2D<uint> OutPageFlags;`
- L26 _resource_ `RWTexture2D<uint> OutPageTable;`
- L27 _resource_ `RWStructuredBuffer<FPhysicalPageMetaData> OutPhysicalPageMetaData;`
- L31 _resource_ `RWStructuredBuffer<int> OutPhysicalPageLists;` — A series of lists used to track various page states (free, used) Each list is MaxPhysicalPages + 1 uint counter
- L107 _resource_ `StructuredBuffer<int> PrevPhysicalPageLists;`
- L109 _resource_ `RWStructuredBuffer<uint4> OutUncachedPageRectBounds;`
- L110 _resource_ `RWStructuredBuffer<uint4> OutAllocatedPageRectBounds;`
- L148 _resource_ `StructuredBuffer<FNextVirtualShadowMapData> NextVirtualShadowMapData;` — Mapping of previous frame/update data to current frame
- L152 _resource_ `Texture2D<uint> PrevPageRequestFlags;` — To propogate any invalidation flags to the physical page flags
- L230 _resource_ `RWStructuredBuffer<uint> DirtyPageFlagsInOut;` — Shadow.Virtual.DirtyPageFlags storage. Allocated with VSM_DIRTY_PAGE_FLAGS_NUM_SLICES * MaxPhysicalPages per-page slices plus one trailing element used as the deferred-invalidation budget atomic.
- L545 _resource_ `RWTexture2D<uint> OutDestBuffer;` _[#if defined(ClearPageTableCS)]_
- L552 _resource_ `RWTexture2D<uint> OutDestBufferMips_0;` _[#if defined(ClearPageTableCS) && HAS_MIP_LEVELS]_
- L553 _resource_ `RWTexture2D<uint> OutDestBufferMips_1;` _[#if defined(ClearPageTableCS) && HAS_MIP_LEVELS]_
- L554 _resource_ `RWTexture2D<uint> OutDestBufferMips_2;` _[#if defined(ClearPageTableCS) && HAS_MIP_LEVELS]_
- L555 _resource_ `RWTexture2D<uint> OutDestBufferMips_3;` _[#if defined(ClearPageTableCS) && HAS_MIP_LEVELS]_
- L556 _resource_ `RWTexture2D<uint> OutDestBufferMips_4;` _[#if defined(ClearPageTableCS) && HAS_MIP_LEVELS]_
- L557 _resource_ `RWTexture2D<uint> OutDestBufferMips_5;` _[#if defined(ClearPageTableCS) && HAS_MIP_LEVELS]_
- L558 _resource_ `RWTexture2D<uint> OutDestBufferMips_6;` _[#if defined(ClearPageTableCS) && HAS_MIP_LEVELS]_
- L801 _resource_ `StructuredBuffer<FPhysicalPageMetaData> PhysicalPageMetaData;`
- L802 _resource_ `RWTexture2DArray<uint> OutPhysicalPagePool;`
- L834 _resource_ `RWBuffer<uint> OutInitializePagesIndirectArgsBuffer;`
- L835 _resource_ `RWStructuredBuffer<uint> OutPhysicalPagesToInitialize;`
- L990 _resource_ `StructuredBuffer<uint> PhysicalPagesToInitialize;`
- L1021 _resource_ `RWBuffer<uint> OutPostProcessPagesIndirectArgsBuffer;` _[#if defined(SelectPagesToPostProcessCS)]_
- L1022 _resource_ `RWStructuredBuffer<uint> OutPhysicalPagesToMerge;` _[#if defined(SelectPagesToPostProcessCS)]_
- L1023 _resource_ `RWStructuredBuffer<uint> OutPhysicalPagesWithFilterable;` _[#if defined(SelectPagesToPostProcessCS)]_
- L1024 _resource_ `RWStructuredBuffer<uint> OutPhysicalPagesWithSeparableFilterable;` _[#if defined(SelectPagesToPostProcessCS)]_
- L1074 _resource_ `StructuredBuffer<uint> PhysicalPagesToMerge;`
- L1088 _resource_ `StructuredBuffer<uint> PhysicalPagesWithFilterable;`
- L1089 _resource_ `StructuredBuffer<uint> PhysicalPagesWithSeparableFilterable;`
- L1162 _resource_ `RWTexture2D<float> OutPrefilteredDistantPhysicalPagePoolX;` _[#if defined(UpdateFilterablePagesSeparableX_CS)]_
- L1231 _resource_ `Texture2D<float> PrefilteredDistantPhysicalPagePoolX;` _[#if defined(UpdateFilterablePagesSeparableY_CS)]_
- L1232 _resource_ `RWTexture2D<float> OutPrefilteredDistantPhysicalPagePool;` _[#if defined(UpdateFilterablePagesSeparableY_CS)]_
- L1234 _resource_ `Texture2D<float> PrevPrefilteredDistantPhysicalPagePool;` _[#if defined(UpdateFilterablePagesSeparableY_CS)]_
- L1235 _resource_ `Texture2D<uint> PrevPageReceiverMasks;` _[#if defined(UpdateFilterablePagesSeparableY_CS)]_
- L1236 _resource_ `ByteAddressBuffer PrevProjectionData;` _[#if defined(UpdateFilterablePagesSeparableY_CS)]_
- L1237 _resource_ `Texture2D<uint> PrevPageTable;` _[#if defined(UpdateFilterablePagesSeparableY_CS)]_
- L1241 _resource_ `StructuredBuffer<uint> PrevVirtualShadowMapIds;` _[#if defined(UpdateFilterablePagesSeparableY_CS)]_
- L1380 _resource_ `RWTexture2D<float> InOutPrefilteredDistantPhysicalPagePool;` _[#if defined(GatherFilterableBorderTexels_CS)]_
- L1454 _resource_ `RWTexture2D<float> OutPrefilteredDistantPhysicalPagePool;` _[#if defined(MergeDownFilterablePagesCS)]_
- L1455 _resource_ `Texture2D<float> PrefilteredDistantPhysicalPagePool;` _[#if defined(MergeDownFilterablePagesCS)]_
- L1456 _resource_ `Texture2D<uint> PrefilteredDistantPhysicalPagePoolPacked;` _[#if defined(MergeDownFilterablePagesCS)]_
- L1638 _resource_ `RWBuffer<uint> OutPagesForHZBIndirectArgsBuffer;`
- L1639 _resource_ `RWStructuredBuffer<uint> OutPhysicalPagesForHZB;`
- L1684 _resource_ `SamplerState PhysicalPagePoolSampler;`
- L1685 _resource_ `Texture2DArray<uint> PhysicalPagePool;`
- L1705 _resource_ `StructuredBuffer<uint> PhysicalPagesForHzb;`
- L1707 _resource_ `RWTexture2DArray<float> FurthestHZBArrayOutput_0;` — out                input               output
- L1708 _resource_ `RWTexture2DArray<float> FurthestHZBArrayOutput_1;` — 32 // 1            16                  8
- L1709 _resource_ `RWTexture2DArray<float> FurthestHZBArrayOutput_2;` — 16                 8                   4
- L1710 _resource_ `RWTexture2DArray<float> FurthestHZBArrayOutput_3;` — 8                  4                   2
- L1711 _resource_ `RWTexture2DArray<float> FurthestHZBArrayOutput_4;` — 4                  2                   1
- L1845 _resource_ `Texture2DArray ParentTextureArrayMip;`
- L1846 _resource_ `SamplerState ParentTextureMipSampler;`
- L1916 _resource_ `StructuredBuffer<int> PhysicalPageLists;`

#### Global parameters (uniforms) (19)

- L111 _parameter_ `uint NumPageRectsToClear;`
- L149 _parameter_ `uint NextVirtualShadowMapDataCount;`
- L224 _parameter_ `int bDynamicPageInvalidation;`
- L225 _parameter_ `int bAllocateViaLRU;`
- L226 _parameter_ `int MaxPageAgeSinceLastRequest;`
- L233 _parameter_ `int DeferredInvalidationBudget;` — Per-frame budget for the deferred-invalidation extended-flag channel. -1 unbounded, 0 disabled, >0 max per frame.
- L546 _parameter_ `uint ClearValue;` _[#if defined(ClearPageTableCS)]_
- L547 _parameter_ `uint SampleStride;` _[#if defined(ClearPageTableCS)]_
- L726 _parameter_ `uint bAppendEmptyToAvailable;`
- L729 _parameter_ `uint bUpdateCounts;` — If true, simply updates the counts instead of copying items This should be run with the same parameters right after the copy pass, with a single group
- L836 _parameter_ `int bUseClearedFlags;`
- L1025 _parameter_ `uint PostProcessPagesIndirectArgsBufferStride;` _[#if defined(SelectPagesToPostProcessCS)]_
- L1238 _parameter_ `float HistoryBlendFactor;` _[#if defined(UpdateFilterablePagesSeparableY_CS)]_
- L1239 _parameter_ `uint bHavePrevReceiverMasks;` _[#if defined(UpdateFilterablePagesSeparableY_CS)]_
- L1640 _parameter_ `uint bFirstBuildThisFrame;`
- L1641 _parameter_ `uint bForceFullHZBUpdate;`
- L1848 _parameter_ `float2 InvHzbInputSize;`
- L1915 _parameter_ `uint StatusMessageId;`
- L1935 _parameter_ `int PageListStatsRow;`

#### groupshared (5)

- L1114 _groupshared_ `groupshared float TmpRowCol[VSM_PAGE_SIZE + SEPARABLE_KERNEL_EXT * 2];` — load border to enable sampling neighbors in the filter kernel
- L1466 _groupshared_ `groupshared uint PageCacheGS[32];` _[#if defined(MergeDownFilterablePagesCS)]_
- L1467 _groupshared_ `groupshared float2 BiasGS[32];` _[#if defined(MergeDownFilterablePagesCS)]_
- L1713 _groupshared_ `groupshared float SharedMinDeviceZ[TILE_THREAD_GROUP_SIZE_XY * TILE_THREAD_GROUP_SIZE_XY];`
- L1714 _groupshared_ `groupshared float SharedMaxDeviceZ[TILE_THREAD_GROUP_SIZE_XY * TILE_THREAD_GROUP_SIZE_XY];`

#### Functions (31)

- L45-48 _function_ `int GetPhysicalPageListStart(int PageList)`
- L50-53 _function_ `int GetPhysicalPageListItem(uint PageList, int Index)`
- L55-59 _function_ `void SetPhysicalPageListItem(uint PageList, int Index, int Value)`
- L61-64 _function_ `int GetPhysicalPageListCount(int PageList)`
- L66-69 _function_ `void SetPhysicalPageListCount(int PageList, int NewCount)`
- L71-87 _function_ `bool PushPhysicalPageList(uint PageList, int PhysicalPageIndex)`
- L90-105 _function_ `int PopPhysicalPageList(uint PageList)` — Returns <0 if none available, otherwise returns the actual value
- L475-541 _function_ `void AllocateNewPageMappings(FVirtualShadowMapHandle VirtualShadowMapHandle, FVSMPageOffset GlobalPageOffset, uint MipLevel, uint2 PageAddress)`
- L560-568 _function_ `void ClearMip(RWTexture2D<uint> OutDestBufferMip, uint HMipLevel, FVirtualSMLevelOffset LevelOffset, uint2 PageCoord, uint SampleStrideLocal, uint MipLevel)` _[#if defined(ClearPageTableCS) && HAS_MIP_LEVELS]_
- L805-811 _function_ `void MergePhysicalPixel(uint2 PixelCoord)` — Helper function to merge static and dynamic depth.
- L838-844 _function_ `void EmitPageToProcess(RWBuffer<uint> OutIndirectArgsBuffer, uint ArgsBufferOffset, RWStructuredBuffer<uint> OutSelectedPhysicalIndexBuffer, uint PhysicalPageIndex)`
- L846-849 _function_ `void EmitPageToProcess(RWBuffer<uint> OutIndirectArgsBuffer, RWStructuredBuffer<uint> OutSelectedPhysicalIndexBuffer, uint PhysicalPageIndex)`
- L915-924 _function_ `FTileInputSetup GetTileInputSetup(uint GroupIndex)`
- L937-955 _function_ `FTileSetup GetTileSetupBase(uint GroupIndex, StructuredBuffer<uint> PageIndexBuffer)`
- L957-962 _function_ `FTileSetup GetTileSetup(uint GroupIndex, StructuredBuffer<uint> PageIndexBuffer)`
- L964-972 _function_ `uint3 GetTileOffset(uint GroupIndex, StructuredBuffer<uint> PageIndexBuffer, inout FPhysicalPageMetaData OutMetaData)`
- L974-982 _function_ `uint3 GetTileBasePos(uint2 TileThreadID, uint GroupIndex, StructuredBuffer<uint> PageIndexBuffer, inout FPhysicalPageMetaData OutMetaData)`
- L984-988 _function_ `uint3 GetTileBasePos(uint2 TileThreadID, uint GroupIndex, StructuredBuffer<uint> PageIndexBuffer)`
- L1091-1108 _function_ `float CalculateOcclusion(float ShadowMapDepth, float TestDepth, float TransitionScale)`
- L1123-1158 _function_ `FBorderSampleData CalcBorderSampleCoord(FVirtualSMLevelOffset Level0Offset, uint GroupThreadIndex, uint2 vPageIn, uint RowOrCol, int2 Axis)`
- L1243-1255 _function_ `bool SampleVirtualShadowMapDirectionalPrefilteredDistantMappedPrev(FVirtualShadowMapHandle MappedClipmapHandle, float3 TranslatedWorldPositionView, inout float OutShadowFactor)` _[#if defined(UpdateFilterablePagesSeparableY_CS)]_
- L1257-1278 _function_ `bool SampleVirtualShadowMapDirectionalPrefilteredDistantPrev(FVirtualShadowMapHandle BaseVirtualShadowMapHandle, FDFVector3 WoldPosition, inout float OutShadowFactor)` _[#if defined(UpdateFilterablePagesSeparableY_CS)]_
- L1382-1397 _function_ `void MapToNeighborClamp(FVirtualSMLevelOffset PageTableLevelOffset, int2 Dir, uint2 DestPPage, uint2 DestVPage, inout uint2 DstPhysBaseAddress, inout uint2 SrcPhysBaseAddress)` _[#if defined(GatherFilterableBorderTexels_CS)]_
- L1399-1406 _function_ `void CopyBorderRowColClamp(FVirtualSMLevelOffset PageTableLevelOffset, int2 Dir, uint2 DestPPage, uint2 DestVPage, uint GroupThreadIndex)` _[#if defined(GatherFilterableBorderTexels_CS)]_
- L1458-1464 _function_ `void AccumulateShadowFactor(FVirtualShadowMapFilterableContext Context, FShadowPhysicalPage ShadowPhysicalPage, float2 VirtualTexelPos, inout float OutAccumulator)` _[#if defined(MergeDownFilterablePagesCS)]_
- L1580-1625 _function_ `uint UpdateAndClearDirtyFlags(uint PhysicalPageIndex)` — Returns updated physical page flags
- L1687-1703 _function_ `float4 Gather4VisZ(uint2 PixelCoord, uint ArrayIndex)`
- L1719-1739 _function_ `void OutputMipLevel(uint MipLevel, uint2 OutputPixelPos, int ArrayIndex, float FurthestDeviceZ, float ClosestDeviceZ)`
- L1741-1806 _function_ `void BuildHZBPerPage(uint2 SrcPos, uint GroupThreadIndex, uint HZBArrayIndex, uint SrcArrayIndex, inout float4 InOutDeviceZ)`
- L1839-1843 _function_ `float4 Gather4(Texture2DArray Texture, SamplerState TextureSampler, uint2 SrcPos, uint ArrayIndex, float2 InvSize)`
- L1854-1893 _function_ `void BuildHZBPerPageTop(uint2 SrcPos, uint2 GroupThreadId, uint ArrayIndex)`

### `Shaders/Private/VirtualShadowMaps/VirtualShadowMapPrintStats.usf` (Private)

- lines: 560; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../ShaderPrint.ush`, L5 `VirtualShadowMapPageAccessCommon.ush`, L6 `VirtualShadowMapStats.ush`, L7 `VirtualShadowMapProjectionStructs.ush`, L8 `../Nanite/NaniteDataDecode.ush`, L9 `../GPUMessaging.ush`, L10 `../Visualization.ush`

#### Macros (#define, 2)

- L12 `#define VSM_GENERATE_STATS_GROUPSIZE 128`
- L164 `#define NANITE_GEO_HISTOGRAM_NUM_BINS (VSM_GENERATE_STATS_GROUPSIZE*2)`

#### Entry points (2)

- L481-508 _entry_ `[numthreads(VSM_GENERATE_STATS_GROUPSIZE, 1, 1)] [numthreads(1, 1, 1)] void LogVirtualSmStatsCS(uint ThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FVirtualSmLogStatsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapArray.cpp:3643) _[#if VSM_GENERATE_STATS]_
- L513-559 _entry_ `[numthreads(1, 1, 1)] void PrintClipmapStats()` — stage: **compute** — C++: `FVirtualSmPrintClipmapStatsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapArray.cpp:3750)

#### Global resources (textures / buffers / samplers) (6)

- L14 _resource_ `StructuredBuffer<uint> InStatsBuffer;`
- L16 _resource_ `StructuredBuffer<uint4> AllocatedPageRectBounds;` — Rectangles bounding (allocated) pages for each mip level
- L88 _resource_ `StructuredBuffer<uint> NanitePerformanceFeedback;`
- L91 _resource_ `StructuredBuffer<uint> ThrottleBuffer;`
- L94 _resource_ `StructuredBuffer<FNaniteStats> NaniteStats;`
- L96 _resource_ `ByteAddressBuffer PrevProjectionData;`

#### Global parameters (uniforms) (9)

- L22 _parameter_ `int ShowStatsValue;` — From cvar, used to determine which stats are shown 1 = all 2 = only physical pages 3 = only non-nanite-instances
- L82 _parameter_ `uint StatusMessageId;`
- L84 _parameter_ `uint StatsMessageId;`
- L85 _parameter_ `uint StatsMessageTimestampHigh;`
- L86 _parameter_ `uint StatsMessageTimestampLow;`
- L89 _parameter_ `uint NanitePerformanceFeedbackNumEntries;`
- L92 _parameter_ `uint bThrottlingEnabled;`
- L510 _parameter_ `uint ShadowMapIdRangeStart;`
- L511 _parameter_ `uint ShadowMapIdRangeEnd;`

#### groupshared (4)

- L166 _groupshared_ `groupshared uint NaniteGeoHistogramHWClusters[NANITE_GEO_HISTOGRAM_NUM_BINS];`
- L167 _groupshared_ `groupshared uint NaniteGeoHistogramSWClusters[NANITE_GEO_HISTOGRAM_NUM_BINS];`
- L168 _groupshared_ `groupshared uint NaniteGeoHistogramMax;`
- L169 _groupshared_ `groupshared uint NaniteGeoHistogramNonZeroBins;`

#### Functions (7)

- L24-42 _function_ `void PrintLeftAlign(inout FShaderPrintContext Context, uint Value)`
- L44-62 _function_ `void PrintLeftAlign(inout FShaderPrintContext Context, float Value)`
- L64-80 _function_ `void PrintUnits(inout FShaderPrintContext Context, uint Value)`
- L98-103 _function_ `void SendStatusMessage()`
- L105-162 _function_ `void SendStatsMessage()`
- L171-219 _function_ `void BuildNaniteGeoHistogram(uint ThreadId)`
- L221-476 _function_ `void PrintStats()`

### `Shaders/Private/VirtualShadowMaps/VirtualShadowMapProjection.usf` (Private)

- lines: 1084; parse: all-branches
- includes: L3 `../Common.ush`, L7 `/Platform/Private/VSMPlatformConfig.ush` [defined(OVERRIDE_VSM_PLATFORM_CONFIG_USH)], L10 `../SceneTexturesCommon.ush`, L11 `../Substrate/Substrate.ush`, L12 `../DeferredShadingCommon.ush`, L13 `../DynamicLightingCommon.ush`, L14 `../MortonCode.ush`, L15 `../LightShaderParameters.ush`, L16 `../LightGridCommon.ush`, L17 `../HairStrands/HairStrandsVisibilityCommon.ush`, L18 `../Visualization.ush`, L19 `../BlueNoise.ush`, L24 `VirtualShadowMapPageAccessCommon.ush`, L25 `VirtualShadowMapProjectionCommon.ush`, L26 `VirtualShadowMapProjectionFilter.ush`, L27 `VirtualShadowMapProjectionDirectional.ush`, L28 `VirtualShadowMapProjectionSpot.ush`, L29 `VirtualShadowMapTransmissionCommon.ush`, L30 `VirtualShadowMapScreenRayTrace.ush`, L31 `VirtualShadowMapLightGrid.ush`, L32 `VirtualShadowMapStats.ush`, L33 `/Engine/Shared/VirtualShadowMapDefinitions.h`, L38 `../HairStrands/HairStrandsVoxelPageCommon.ush` [HAS_HAIR_STRANDS], L39 `../HairStrands/HairStrandsVoxelPageTraversal.ush` [HAS_HAIR_STRANDS]

#### Macros (#define, 9)

- L5 `#define VSM_PLATFORM_PROJECTION_SHADER 1`
- L36 `#define VOXEL_TRAVERSAL_TYPE VOXEL_TRAVERSAL_LINEAR_MIPMAP` _[#if HAS_HAIR_STRANDS]_
- L37 `#define VOXEL_TRAVERSAL_DEBUG 0` _[#if HAS_HAIR_STRANDS]_
- L46 `#define DIRECTIONAL_LIGHT 0` _[#if !defined(DIRECTIONAL_LIGHT)]_
- L50 `#define VISUALIZE_OUTPUT 0` _[#if !defined(VISUALIZE_OUTPUT)]_
- L53 `#define SCREEN_RAY_SAMPLES 4`
- L279 `#define INPUT_TYPE_GBUFFER 0`
- L280 `#define INPUT_TYPE_HAIRSTRANDS 1`
- L620 `#define USE_ADAPTATIVE 1` _[#if HAS_HAIR_STRANDS]_

#### Entry points (1)

- L943-1083 _entry_ `[numthreads(WORK_TILE_SIZE, WORK_TILE_SIZE, 1)] void VirtualShadowMapProjection( uint3 GroupId : SV_GroupID, uint GroupIndex : SV_GroupIndex, uint3 DispatchThreadId : SV_DispatchThreadID )` — stage: **compute** — C++: `FVirtualShadowMapProjectionCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapProjection.cpp:315)

#### Structs / classes (1)

- L57-66 _struct_ **`FProjectionShadingInfo`** `struct FProjectionShadingInfo`
  - L59 _member_ `bool bIsValid;`
  - L60 _member_ `bool bIsHair;`
  - L61 _member_ `bool bIsSubsurface;`
  - L62 _member_ `bool bDisableBackFaceCulling;`
  - L63 _member_ `bool bIsFirstPerson;`
  - L65 _member_ `float3 WorldNormal;`

#### Global resources (textures / buffers / samplers) (6)

- L41-55 _resource_ `DEFINE_HAIR_BLUE_NOISE_JITTER_FUNCTION StructuredBuffer< FPhysicalPageMetaData > PhysicalPageMetaData;` _[#if HAS_HAIR_STRANDS && USE_BLUE_NOISE]_
- L159 _resource_ `Texture2D<float> PrefilteredDistantPhysicalPagePool;` _[#if PREFILTERED_DISTANT_CLIPMAP]_
- L259 _resource_ `RWTexture2D< uint4 > OutShadowMaskBits;` _[#if ONE_PASS_PROJECTION \|\| UBERSHADER]_
- L265 _resource_ `RWTexture2D< float2 > OutShadowFactor;` _[#if !ONE_PASS_PROJECTION \|\| UBERSHADER]_
- L269 _resource_ `RWTexture2D< float4 > OutVisualize;` — Visualization output
- L928 _resource_ `Buffer<uint> TileListData;` _[#if USE_TILE_LIST]_

#### Global parameters (uniforms) (16)

- L21 _parameter_ `int SMRTSamplePerRay;`
- L22 _parameter_ `uint bSMRTExtrapolateSlope;`
- L250 _parameter_ `uint bPrefilteredDistantClipmap;`
- L251 _parameter_ `uint bFirstPersonShadow;`
- L252 _parameter_ `uint bOnePassProjection;`
- L253 _parameter_ `uint bVisualizeOutput;`
- L254 _parameter_ `int4 ProjectionRect;`
- L255 _parameter_ `float SubsurfaceMinSourceRadius;`
- L264 _parameter_ `int LightUniformVirtualShadowMapId;` — Single light per pass Light parameters loaded via GetRootLightShaderParameters(); _[#if !ONE_PASS_PROJECTION \|\| UBERSHADER]_
- L270 _parameter_ `int VisualizeModeId;`
- L271 _parameter_ `int bVisualizeCachedPagesOnly;`
- L272 _parameter_ `int VisualizeVirtualShadowMapId;`
- L275 _parameter_ `int FirstPersonVirtualShadowMapId;` _[#if FIRST_PERSON_SHADOW]_
- L281 _parameter_ `uint InputType;`
- L282 _parameter_ `uint bCullBackfacingPixels;`
- L927 _parameter_ `uint bUseTileList;` _[#if USE_TILE_LIST]_

#### Functions (12)

- L68-107 _function_ `FProjectionShadingInfo GetProjectionShadingInfo(uint2 PixelPos)`
- L109-116 _function_ `int GetSMRTRayCount()`
- L118-144 _function_ `SCHEDULER_MIN_PRESSURE MAX_OCCUPANCY float3 GetEstimatedGeoWorldNormal(float3 TranslatedWorldPosition, float3 ShadingNormal)`
- L146-154 _function_ `float4 ComputeRandom4(uint2 PixelPosition)`
- L161-172 _function_ `float SamplShadowMaskMapVirtualBilinear(FVirtualShadowMapHandle VirtualShadowMapHandle, float2 VirtualTexelAddressFloat)` _[#if PREFILTERED_DISTANT_CLIPMAP]_
- L174-201 _function_ `FVirtualShadowMapSampleResult SampleVirtualShadowMapDirectionalFilterableMapped(FVirtualShadowMapHandle MappedClipmapHandle, float3 TranslatedWorldPositionView)` _[#if PREFILTERED_DISTANT_CLIPMAP]_
- L203-246 _function_ `FVirtualShadowMapSampleResult SampleVirtualShadowMapDirectionalPrefilteredDistant( int VirtualShadowMapId, FLightShaderParameters Light, uint2 PixelPos, float3 TranslatedWorldPosition)` _[#if PREFILTERED_DISTANT_CLIPMAP]_
- L284-663 _function_ `FVirtualShadowMapSampleResult ProjectLight( int VirtualShadowMapId, FLightShaderParameters Light, FProjectionShadingInfo ShadingInfo, uint2 PixelPos, float SceneDepth, float ScreenRayLengthWorld, float3 TranslatedWorldPosition, const float Noise, const FSubsurfaceOpacityMFP SubsurfaceOpacityMFP)`
- L665-669 _function_ `float3 GetVirtualPageColor(uint2 VirtualTexelAddress)`
- L671-674 _function_ `float Grayscale(float3 SourceClr)`
- L676-924 _function_ `void OutputVisualize( int VirtualShadowMapId, uint2 PixelPos, float3 TranslatedWorldPosition, FVirtualShadowMapSampleResult Result)`
- L931-941 _function_ `uint2 GetTileCoord(uint2 GroupId)`

### `Shaders/Private/VirtualShadowMaps/VirtualShadowMapProjectionCommon.ush` (Private)

- lines: 791; parse: all-branches
- includes: L8 `../Common.ush`, L9 `VirtualShadowMapPageAccessCommon.ush`, L10 `VirtualShadowMapProjectionStructs.ush`, L11 `/Engine/Shared/LightDefinitions.h`, L20 `../DiaphragmDOF/DOFCommon.ush` [VSM_WITH_DOF_BIAS]

#### Macros (#define, 3)

- L13 `#define VIRTUAL_SHADOW_MAP_MIN_OCCLUDER_DISTANCE 1e-6f`
- L16 `#define VSM_WITH_DOF_BIAS 0` _[#if !defined(VSM_WITH_DOF_BIAS)]_
- L260 `#define DEBUG_VSM_CLIPMAP_LEVEL_SEARCH 0`
- L6 #pragma `once`

#### Structs / classes (4)

- L137-146 _struct_ **`FVirtualShadowMapSample`** `struct FVirtualShadowMapSample`
  - L139 _member_ `float Depth;`
  - L140 _member_ `uint MipLevel;`
  - L141 _member_ `FVirtualShadowMapHandle VirtualShadowMapHandle;` — May be offset from input for clipmaps
  - L142 _member_ `bool bValid;`
  - L143 _member_ `uint2 VirtualTexelAddress;`
  - L144 _member_ `float2 VirtualTexelAddressFloat;`
  - L145 _member_ `uint2 PhysicalTexelAddress;`
- L211-215 _struct_ **`FVirtualShadowMapClipmapRelativeTransform`** `struct FVirtualShadowMapClipmapRelativeTransform` — Data to convert UV's and depths from one clipmap level basis to another
  - L213 _member_ `float Scale;`
  - L214 _member_ `float3 Bias;`
- L398-410 _struct_ **`FVirtualShadowMapSampleResult`** `struct FVirtualShadowMapSampleResult`
  - L400 _member_ `bool bValid;`
  - L401 _member_ `float ShadowFactor;` — 0 = fully occluded, 1 = no occlusion
  - L402 _member_ `float OccluderDistance;`
  - L405 _member_ `int ClipmapOrMipLevel;` — Debug data; do not reference in non-debug permutations or performance may be affected!
  - L406 _member_ `uint RayCount;`
  - L407 _member_ `uint2 VirtualTexelAddress;`
  - L408 _member_ `uint2 PhysicalTexelAddress;`
  - L409 _member_ `float3 GeneralDebug;` — General purpose debug output during shader development
- L677-783 _struct_ **`FVirtualShadowMapFilterableContext`** `struct FVirtualShadowMapFilterableContext`
  - L679 _member_ `Texture2D<uint> PageTable;`
  - L680 _member_ `Texture2D<uint> PageReceiverMasks;`
  - L681 _member_ `Texture2D<float> PrefilteredDistantPhysicalPagePool;`
  - L682 _member_ `bool bHavePrevReceiverMasks;`
  - L683 _member_ `ByteAddressBuffer ProjectionDataBuffer;`
  - L685 _method_ `FShadowPhysicalPage VirtualToPhysicalTexelBase(FVirtualSMLevelOffset PageTableLevelOffset, uint Level, uint2 VirtualTexelAddress, inout uint2 PhysicalTexelAddress)`
  - L696 _method_ `bool VirtualToPhysicalTexel(FVirtualSMLevelOffset PageTableLevelOffset, uint Level, uint2 VirtualTexelAddress, inout uint2 PhysicalTexelAddress)` — Returns true if the page is valid at all
  - L702 _method_ `FShadowPhysicalPage VirtualToPhysicalTexelBase(FVirtualSMLevelOffset PageTableLevelOffset, uint Level, float2 VirtualTexelAddressFloat, inout float2 PhysicalTexelAddressFloat)` — Returns true if the page is valid *for rendering*
  - L714 _method_ `bool VirtualToPhysicalTexel(FVirtualSMLevelOffset PageTableLevelOffset, uint Level, float2 VirtualTexelAddressFloat, inout float2 PhysicalTexelAddressFloat)` — Returns true if the page is valid at all
  - L720 _method_ `bool VirtualToPhysicalTexelReceiverMask(FVirtualSMLevelOffset PageTableLevelOffset, uint Level, float2 VirtualTexelAddressFloat, inout float2 PhysicalTexelAddressFloat)` — Returns true if the page is valid and the receiver mask is set for the given texel (or is disabled)
  - L747 _method_ `bool SampleBilinearReceiverMask(FVirtualSMLevelOffset PageTableLevelOffset, float2 VirtualTexelAddressFloat, inout float OutShadowFactor)`
  - L760 _method_ `bool SampleBilinear(FVirtualSMLevelOffset PageTableLevelOffset, float2 VirtualTexelAddressFloat, inout float OutShadowFactor)`
  - L773 _method_ `bool SampleBilinear(FShadowPhysicalPage PhysicalPageEntry, float2 VirtualTexelAddressFloat, inout float OutShadowFactor)`

#### Global parameters (uniforms) (1)

- L22 _parameter_ `float DOFBiasStrength;` _[#if VSM_WITH_DOF_BIAS]_

#### Functions (32)

- L25-38 _function_ `float CalculateResolutionBiasFromDepthOfField(float SceneDepth)` — Areas that are out of focus get a lower VSM resolution, as the resulting image will get blurred anyway _[#if VSM_WITH_DOF_BIAS]_
- L41-45 _function_ `float CalcAbsoluteClipmapLevel(float DistanceToClipmapOriginSquared)`
- L48-75 _function_ `float CalcBiasedAbsoluteClipmapLevelForSampling(FVirtualShadowMapProjectionShaderData BaseProjectionData, float DistanceToClipmapOriginSquared, float SceneDepth)` — Optionally apply the resolution bias (rather than greedy sampling highest res data) depending on the global setting
- L77-82 _function_ `float CalcDistanceToClipmapOriginSquared(FVirtualShadowMapProjectionShaderData BaseProjectionData, float3 TranslatedWorldPosition)`
- L84-87 _function_ `float CalcAbsoluteClipmapLevel(FVirtualShadowMapProjectionShaderData BaseProjectionData, float3 TranslatedWorldPosition)`
- L89-92 _function_ `float CalcBiasedAbsoluteClipmapLevelForSampling(FVirtualShadowMapProjectionShaderData BaseProjectionData, float3 TranslatedWorldPosition, float SceneDepth)`
- L96-118 _function_ `float VirtualShadowMapCalcPixelFootprintLocal( FVirtualShadowMapProjectionShaderData ProjectionData, float3 ShadowTranslatedWorldPosition, float SceneDepth)` — Calculate the projected pixel footprint onto a local light, scaled in shadow map texels ShadowTranslatedWorldPosition should already be translated by both the primary view and shadow ProjectionData.PreViewTranslation
- L120-135 _function_ `uint VirtualShadowMapGetMipLevelLocalFromReceiver( FVirtualShadowMapProjectionShaderData ProjectionData, float3 ReceiverShadowTranslatedWorld, float ReceiverSceneDepth)`
- L148-158 _function_ `FVirtualShadowMapSample InitVirtualShadowMapSample()`
- L160-163 _function_ `float SampleVirtualShadowMapPhysicalDepth(uint2 PhysicalTexelAddress)`
- L165-182 _function_ `FVirtualShadowMapSample SampleVirtualShadowMapLevel(FVirtualShadowMapHandle VirtualShadowMapHandle, float2 ShadowMapUV, uint MipLevel)`
- L184-200 _function_ `FVirtualShadowMapSample SampleVirtualShadowMap(FVirtualShadowMapHandle VirtualShadowMapHandle, float2 ShadowMapUV, uint MinMipLevel)`
- L203-208 _function_ `float3 VirtualShadowMapGetNormalBiasLength(float3 TranslatedWorldPosition)` — VSM normal bias that smoothly scales with distance to camera
- L220-238 _function_ `FVirtualShadowMapClipmapRelativeTransform CalcClipmapRelativeTransform(FVirtualShadowMapHandle ClipmapHandle, int LevelOffset)` — Resulting transform takes UV's/depths from clipmap level ClipmapId to ClipmapId + LevelOffset ClipmapId + LevelOffset should be a valid level in the same clipmap See VirtualShadowMapClipmap.cpp for construction details
- L243-252 _function_ `uint2 CalcClipmapOffsetLevelPage(uint2 BasePage, FVirtualShadowMapHandle ClipmapHandle, uint LevelOffset)` — Transforms a virtual page in a given clipmap level to a page in the offset coarser level This offset must be positive or else the page would not be guaranteed to exist in the target level This is done entirely in integer math as well to avoid precision issues when looking up coarser fallback pages
- L256-327 _function_ `FVirtualShadowMapSample SampleVirtualShadowMapClipmap(FVirtualShadowMapHandle VirtualShadowMapHandle, float2 ShadowMapUV)` — Will sample from the given clipmap level Id, onwards to coarser levels if no valid data is present ShadowMapUVs are in terms of the given clipmap level/virtual shadow map
- L329-360 _function_ `float ComputeVirtualShadowMapOptimalSlopeBias( FVirtualShadowMapHandle RequestedVirtualShadowMapHandle, FVirtualShadowMapSample SmSample, float3 TranslatedWorldPosition, float3 EstimatedGeoWorldNormal, bool bClamp = true)`
- L364-372 _function_ `float ComputeOccluderDistanceOrtho(float4x4 ShadowViewToClip, float OccluderDepth, float ReceiverDepth)` — Used for orthographic projections (i.e. directional lights) Receiver depth is post-projection-divide.
- L376-385 _function_ `float ComputeOccluderDistancePerspective(float4x4 ShadowViewToClip, float OccluderDepth, float ReceiverDepth, float ReceiverDistance)` — Used for perspective projections (i.e. spot lights) Receiver depth is post-projection-divide.
- L387-396 _function_ `uint VirtualShadowMapGetCubeFace( float3 Dir )`
- L413-425 _function_ `FVirtualShadowMapSampleResult InitVirtualShadowMapSampleResult()`
- L442-507 _function_ `FVirtualShadowMapSampleResult SampleVirtualShadowMapDirectional( FVirtualShadowMapHandle VirtualShadowMapHandle, float3 TranslatedWorldPosition, float RayStartDistance, float3 EstimatedGeoWorldNormal, bool bUseOptimalBias = true, float SceneDepth = -1.0f)` — Sample virtual shadow (clip)map for a directional light VirtualShadowMapId is the ID of the virtual shadow map to sample TranslatedWorldPosition is the sample position in PrimaryViews translated world space to project into the shadow map RayStartDistance is an optional offset to move the lookup along the shadow ray towards the light - Should be zero or positive - This offset is useful in that it does *not* affect the selection of clipmap level, unlike offsetting the WorldPosition itself - OccluderDistance will still be relative to the original sample position EstimatedGeoWorldNormal is ideally
- L509-524 _function_ `FVirtualShadowMapSampleResult SampleVirtualShadowMapDirectional( int VirtualShadowMapId, float3 TranslatedWorldPosition, float RayStartDistance, float3 EstimatedGeoWorldNormal, bool bUseOptimalBias = true, float SceneDepth = -1.0f)`
- L533-606 _function_ `FVirtualShadowMapSampleResult SampleVirtualShadowMapLocal( FVirtualShadowMapHandle VirtualShadowMapHandle, float3 TranslatedWorldPosition, float RayStartDistance, float3 EstimatedGeoWorldNormal, bool bUseOptimalBias = true, float SceneDepth = -1.0f)` — Sample virtual shadow map for a local light Parameter descriptions are as above, except: - SceneDepth can be optionally provided to allow computing the appropriate mip level for sampling when using receiver mask to avoid sampling incomplete data from more detailed mip levels.
- L608-623 _function_ `FVirtualShadowMapSampleResult SampleVirtualShadowMapLocal( int VirtualShadowMapId, float3 TranslatedWorldPosition, float RayStartDistance, float3 EstimatedGeoWorldNormal, bool bUseOptimalBias = true, float SceneDepth = -1.0f)`
- L628-631 _function_ `FVirtualShadowMapSampleResult SampleVirtualShadowMapDirectional(int VirtualShadowMapId, float3 TranslatedWorldPosition, float RayStartDistance = 0.0f, float SceneDepth = -1.0f)` — Sample in PrimaryView translated world space with no optimal bias
- L632-635 _function_ `FVirtualShadowMapSampleResult SampleVirtualShadowMapDirectional(FVirtualShadowMapHandle VirtualShadowMapHandle, float3 TranslatedWorldPosition, float RayStartDistance = 0.0f, float SceneDepth = -1.0f)`
- L636-639 _function_ `FVirtualShadowMapSampleResult SampleVirtualShadowMapLocal(int VirtualShadowMapId, float3 TranslatedWorldPosition, float RayStartDistance = 0.0f, float SceneDepth = -1.0f)`
- L640-643 _function_ `FVirtualShadowMapSampleResult SampleVirtualShadowMapLocal(FVirtualShadowMapHandle VirtualShadowMapHandle, float3 TranslatedWorldPosition, float RayStartDistance = 0.0f, float SceneDepth = -1.0f)`
- L653-664 _function_ `FVirtualShadowMapSampleResult SampleVirtualShadowMapTranslatedWorld(FVirtualShadowMapHandle VirtualShadowMapHandle, float3 TranslatedWorldPosition, float RayStartDistance = 0.0f)` — Sample a virtual shadow map for an unknown light type with no optimal bias. Will route to the appropriate function above. Generally the directional/local variants should be used when the light's type is known to cut down on the code/register overhead of including both paths.
- L672-675 _function_ `FVirtualShadowMapSampleResult SampleVirtualShadowMapTranslatedWorld(int VirtualShadowMapId, float3 TranslatedWorldPosition, float RayStartDistance = 0.0f)` — Sample a virtual shadow map for an unknown light type with no optimal bias. Will route to the appropriate function above. Generally the directional/local variants should be used when the light's type is known to cut down on the code/register overhead of including both paths.
- L785-790 _function_ `float2 ViewTranslatedWorldToVirtualTexel(FVirtualShadowMapProjectionShaderData ProjectionData, float3 TranslatedWorldPositionView, uint MipLevel = 0u)`

### `Shaders/Private/VirtualShadowMaps/VirtualShadowMapProjectionComposite.usf` (Private)

- lines: 61; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../SceneTexturesCommon.ush`, L5 `../LightShaderParameters.ush`, L6 `VirtualShadowMapMaskBitsCommon.ush`

#### Macros (#define, 1)

- L9 `#define WORK_TILE_SIZE 8` _[#if !defined(WORK_TILE_SIZE)]_

#### Entry points (3)

- L14-28 _entry_ `void VirtualShadowMapCompositeTileVS( in uint InstanceId : SV_InstanceID, in uint VertexId : SV_VertexID, out float4 Position : SV_POSITION)` — stage: **vertex (from C++ binding)** — C++: `FVirtualShadowMapProjectionCompositeTileVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapProjection.cpp:675)
- L36-42 _entry_ `void VirtualShadowMapCompositePS( in float4 SvPosition : SV_Position, out float4 OutShadowMask : SV_Target)` — stage: **pixel (from C++ binding)** — C++: `FVirtualShadowMapProjectionCompositePS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapProjection.cpp:702)
- L44-60 _entry_ `void VirtualShadowMapCompositeFromMaskBitsPS( in float4 SvPosition : SV_Position, out float4 OutShadowMask : SV_Target)` — stage: **pixel (from C++ binding)** — C++: `FVirtualShadowMapProjectionCompositeFromMaskBitsPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapProjection.cpp:831)

#### Global resources (textures / buffers / samplers) (4)

- L12 _resource_ `Buffer<uint> TileListData;`
- L30 _resource_ `Texture2D<float2> InputShadowFactor;`
- L31 _resource_ `Texture2D<float> InputDepthTexture;`
- L32 _resource_ `Texture2D<uint4> ShadowMaskBits;`

#### Global parameters (uniforms) (2)

- L33 _parameter_ `int CompositeVirtualShadowMapId;`
- L34 _parameter_ `uint bModulateRGB;`

### `Shaders/Private/VirtualShadowMaps/VirtualShadowMapProjectionDirectional.ush` (Private)

- lines: 350; parse: all-branches
- includes: L8 `../DeferredShadingCommon.ush`, L9 `../SceneTexturesCommon.ush`, L10 `../LightShaderParameters.ush`, L11 `../Visualization.ush`, L12 `VirtualShadowMapPageAccessCommon.ush`, L13 `VirtualShadowMapProjectionCommon.ush`, L14 `VirtualShadowMapSMRTCommon.ush`, L149 `VirtualShadowMapSMRTTemplate.ush`

#### Macros (#define, 1)

- L148 `#define SMRT_TEMPLATE_RAY_STRUCT FSMRTClipmapRayState`
- L6 #pragma `once`; L150 #undef `SMRT_TEMPLATE_RAY_STRUCT`

#### Structs / classes (1)

- L73-82 _struct_ **`FSMRTClipmapRayState`** `struct FSMRTClipmapRayState`
  - L75 _member_ `FVirtualShadowMapHandle ClipmapHandle;` — Pre-offset virtual shadow map ID of specific clipmap level
  - L76 _member_ `float3 RayStartUVZ;`
  - L77 _member_ `float3 RayStepUVZ;`
  - L78 _member_ `float ExtrapolateSlope;`
  - L79 _member_ `uint2 PhysicalTexelAddress;`
  - L80 _member_ `uint2 VirtualTexelAddress;`
  - L81 _member_ `FVirtualShadowMapHandle SampledClipmapHandle;`

#### Functions (9)

- L16-29 _function_ `float2 ComputeDepthSlopeDirectionalUV( FVirtualShadowMapProjectionShaderData ProjectionData, float3 EstimatedGeoWorldNormal, bool bClamp = true)`
- L31-36 _function_ `float ComputeOptimalSlopeBiasDirectional( float2 DepthSlopeUV, float2 OffsetUV)`
- L38-71 _function_ `FVirtualShadowMapHandle GetMappedClipmap(FVirtualShadowMapHandle VirtualShadowMapHandle, float3 RayOriginTranslatedWorld, float SceneDepth)`
- L84-122 _function_ `FSMRTClipmapRayState SMRTClipmapRayInitialize( const FVirtualShadowMapProjectionShaderData ProjectionData, float3 RayOriginShadowTranslatedWorld, float3 RayDir, float RayLength, float RayStartOffset, float2 DepthSlopeUV, float2 TexelOffset, float ExtrapolateSlope)`
- L124-145 _function_ `FSMRTSample SMRTFindSample(inout FSMRTClipmapRayState RayState, float SampleTime)`
- L153-164 _function_ `float3 GetRandomDirectionalLightRayDir(FLightShaderParameters Light, float2 E)`
- L167-173 _function_ `bool IsBackfaceToDirectionalLight(float3 Normal, float3 LightDirection, float LightSourceRadius)` — Normal and LightDirection should be normalized
- L175-320 _function_ `FVirtualShadowMapSampleResult TraceDirectional( int VirtualShadowMapId, FLightShaderParameters Light, uint2 PixelPos, const float SceneDepth, float3 TranslatedWorldPosition, float RayStartOffset, const float Noise, float3 WorldNormal, const FSMRTTraceSettings Settings = GetSMRTTraceSettingsDirectional())`
- L323-349 _function_ `bool GenerateRayDirectional( FLightShaderParameters Light, uint2 PixelPos, float3 TranslatedWorldPosition, float RayLengthScale, uint RayIndex, uint RayCount, inout float3 OutRayStart, inout float3 OutRayEnd)` — Generate a ray based on directional light source geometry (e.g, source radius)

### `Shaders/Private/VirtualShadowMaps/VirtualShadowMapProjectionFilter.ush` (Private)

- lines: 28; parse: all-branches
- includes: L8 `../Common.ush`, L9 `../BlueNoise.ush`, L10 `VirtualShadowMapProjectionCommon.ush`
- L6 #pragma `once`

#### Functions (1)

- L12-27 _function_ `void FilterVirtualShadowMapSampleResult(uint2 PixelPos, inout FVirtualShadowMapSampleResult In)`

### `Shaders/Private/VirtualShadowMaps/VirtualShadowMapProjectionSpot.ush` (Private)

- lines: 524; parse: all-branches
- includes: L8 `../DeferredShadingCommon.ush`, L9 `../SceneTexturesCommon.ush`, L10 `../LightShaderParameters.ush`, L11 `../PathTracing/Utilities/PathTracingRandomSequence.ush`, L12 `VirtualShadowMapPageAccessCommon.ush`, L13 `VirtualShadowMapProjectionCommon.ush`, L14 `VirtualShadowMapSMRTCommon.ush`, L138 `VirtualShadowMapSMRTTemplate.ush`, L188 `VirtualShadowMapSMRTTemplate.ush`

#### Macros (#define, 2)

- L137 `#define SMRT_TEMPLATE_RAY_STRUCT FSMRTSingleRayState`
- L187 `#define SMRT_TEMPLATE_RAY_STRUCT FSMRTTwoCubeFaceRayState`
- L6 #pragma `once`; L139 #undef `SMRT_TEMPLATE_RAY_STRUCT`; L189 #undef `SMRT_TEMPLATE_RAY_STRUCT`

#### Structs / classes (2)

- L52-63 _struct_ **`FSMRTSingleRayState`** `struct FSMRTSingleRayState`
  - L54 _member_ `FVirtualShadowMapHandle VirtualShadowMapHandle;`
  - L55 _member_ `float3 RayStartUVz;`
  - L56 _member_ `float3 RayStepUVz;`
  - L57 _member_ `float ExtrapolateSlope;`
  - L58 _member_ `uint MinMipLevel;`
  - L60 _member_ `int MipLevel;` — Debug output
  - L61 _member_ `uint2 VirtualTexelAddress;`
  - L62 _member_ `uint2 PhysicalTexelAddress;`
- L142-147 _struct_ **`FSMRTTwoCubeFaceRayState`** `struct FSMRTTwoCubeFaceRayState`
  - L144 _member_ `FSMRTSingleRayState Face0;`
  - L145 _member_ `FSMRTSingleRayState Face1;`
  - L146 _member_ `bool bSampleInFace1;`

#### Functions (13)

- L16-27 _function_ `float2 ComputeDepthSlopeLocalUV( FVirtualShadowMapHandle VirtualShadowMapHandle, float3 ShadowTranslatedWorldPosition, float3 WorldNormal)`
- L29-49 _function_ `float ComputeOptimalSlopeBiasLocal( FVirtualShadowMapHandle VirtualShadowMapHandle, float3 ShadowTranslatedWorldPosition, float2 DepthSlopeUV, bool bClamp = true)`
- L65-107 _function_ `FSMRTSingleRayState SMRTSingleRayInitialize( FVirtualShadowMapHandle VirtualShadowMapHandle, float3 RayStartShadowTranslatedWorld, float3 RayEndShadowTranslatedWorld, float ExtrapolateSlope, float DepthBias, uint MipLevel, bool bClampUVs = true)`
- L109-134 _function_ `FSMRTSample SMRTFindSample(inout FSMRTSingleRayState RayState, float SampleTime)`
- L149-163 _function_ `FSMRTTwoCubeFaceRayState SMRTTwoCubeFaceRayInitialize( FVirtualShadowMapHandle VirtualShadowMapHandle0, FVirtualShadowMapHandle VirtualShadowMapHandle1, float3 RayStartShadowTranslatedWorld, float3 RayEndShadowTranslatedWorld, float ExtrapolateSlope, float DepthBias, uint MipLevel)`
- L165-184 _function_ `FSMRTSample SMRTFindSample(inout FSMRTTwoCubeFaceRayState RayState, float SampleTime)`
- L192-206 _function_ `FSMRTResult ShadowRayCastSpotLight( FVirtualShadowMapHandle VirtualShadowMapHandle, float3 RayStartShadowTranslatedWorld, float3 RayEndShadowTranslatedWorld, float DepthBias, uint MipLevel, int NumSteps, float StepOffset, float ExtrapolateSlope, inout FSMRTSingleRayState OutRayState)`
- L208-247 _function_ `FSMRTResult ShadowRayCastPointLight( FVirtualShadowMapHandle VirtualShadowMapHandle, float3 RayStartShadowTranslatedWorld, float3 RayEndShadowTranslatedWorld, float DepthBias, uint MipLevel, int NumSteps, float StepOffset, float ExtrapolateSlope, inout FSMRTSingleRayState OutRayState)`
- L250-262 _function_ `bool IsBackfaceToLocalLight( float3 ToLight, float3 Normal, float LightSourceRadius)` — Normal should be normalized
- L265-276 _function_ `float ComputeShadowResolutionScale(FVirtualShadowMapProjectionShaderData ProjectionData, float SceneDepth)` — Shadow resolution scale that roughly matches the LOD function in VSM page marking
- L278-287 _function_ `float VirtualShadowMapGetClampedRayDistanceScaleLocal(float CosTheta)`
- L289-489 _function_ `FVirtualShadowMapSampleResult TraceLocalLight( int VirtualShadowMapId, FLightShaderParameters Light, uint2 PixelPos, const float SceneDepth, float3 TranslatedWorldPosition, float RayStartOffset, const float Noise, float3 WorldNormal, const FSMRTTraceSettings Settings = GetSMRTTraceSettingsLocal())`
- L492-523 _function_ `bool GenerateRayLocalLight( FLightShaderParameters Light, uint2 PixelPos, float3 TranslatedWorldPosition, float3 WorldNormal, uint RayIndex, uint RayCount, inout float3 OutRayStart, inout float3 OutRayEnd)` — Generate ray based on light source geometry

### `Shaders/Private/VirtualShadowMaps/VirtualShadowMapProjectionStructs.ush` (Private)

- lines: 142; parse: all-branches
- includes: L5 `../LargeWorldCoordinates.ush`, L6 `../ByteBuffer.ush`, L7 `/Engine/Shared/VirtualShadowMapDefinitions.h`, L8 `VirtualShadowMapHandle.ush`

#### Macros (#define, 2)

- L10 `#define VSM_PSD_OFFSET_RESOLUTION_LOD_BIAS 252`
- L11 `#define VSM_PSD_OFFSET_LIGHT_TYPE 220`
- L3 #pragma `once`

#### Structs / classes (1)

- L14-56 _struct_ **`FVirtualShadowMapProjectionShaderData`** `struct FVirtualShadowMapProjectionShaderData` — Rougly the same structure as in VirtualShadowMapArray.h, with some logic around LWC values
  - L16 _member_ `float4x4 ShadowViewToClipMatrix;`
  - L17 _member_ `float4x4 TranslatedWorldToShadowUVMatrix;`
  - L18 _member_ `float4x4 ShadowUVToTranslatedWorldMatrix;`
  - L19 _member_ `float4x4 TranslatedWorldToShadowUVNormalMatrix;`
  - L21 _member_ `float3 LightDirection;`
  - L22 _member_ `uint LightType;` — Matches ELightComponentType via defines in SSDDefinitions.ush
  - L24 _member_ `FDFVector3 PreViewTranslation;`
  - L25 _member_ `float LightRadius;`
  - L26 _member_ `float ResolutionLodBias;`
  - L28 _member_ `float3 ClipmapWorldOriginOffset;` — Clipmap origin, in shadow translated world
  - L30 _member_ `int2 ClipmapCornerRelativeOffset;`
  - L31 _member_ `int ClipmapLevel;` — "Absolute" level, can be negative
  - L32 _member_ `int ClipmapLevelCountRemaining;` — Remaining levels, relative to this one
  - L33 _member_ `uint ClipmapLevelIndex;` — Level index, relative to the base level
  - L35 _member_ `uint Flags;`
  - L36 _member_ `float ClipmapLevelWPODistanceDisabledThresholdSquared;`
  - L37 _member_ `float LightSourceRadius;`
  - L38 _member_ `float TexelDitherScale;` — Per-light additional dither filtering
  - L39 _member_ `uint MinMipLevel;` — Minimum mip level that is used for this mip chain (only valid for local lights)
  - L41 _member_ `int SceneRendererPrimaryViewId;`
  - L42 _member_ `int PersistentViewId;`
  - L44 _member_ `int LightId;`
  - L46 _member_ `float2 DynamicDepthCullRange;`
  - L49 _member_ `FVirtualShadowMapHandle VirtualShadowMapHandle;` — Derived data for convenience when passing the structure around
  - L50 _member_ `bool bUnCached;` — see VSM_PROJ_FLAG_UNCACHED
  - L51 _member_ `bool bUnreferenced;` — see VSM_PROJ_FLAG_UNREFERENCED
  - L52 _member_ `bool bIsCoarseClipLevel;` — see VSM_PROJ_FLAG_IS_COARSE_CLIP_LEVEL
  - L53 _member_ `bool bHasPrefilteredDistant;` — see VSM_PROJ_FLAG_HAS_PREFILTERED_DISTANT;
  - L54 _member_ `bool bUseReceiverMask;` — see VSM_PROJ_FLAG_USE_RECEIVER_MASK
  - L55 _member_ `bool bForceCacheDynamicCoarse;` — see VSM_PROJ_FLAG_FORCE_CACHE_DYNAMIC_COARSE

#### Functions (3)

- L58-131 _function_ `FVirtualShadowMapProjectionShaderData DecodeVirtualShadowMapProjectionData(ByteAddressBuffer ProjectionData, FVirtualShadowMapHandle VirtualShadowMapHandle)`
- L133-136 _function_ `FVirtualShadowMapProjectionShaderData GetVirtualShadowMapProjectionData(FVirtualShadowMapHandle VirtualShadowMapHandle)`
- L138-141 _function_ `FVirtualShadowMapProjectionShaderData GetVirtualShadowMapProjectionData(FVirtualShadowMapHandle VirtualShadowMapHandle, ByteAddressBuffer ProjectionDataBuffer)`

### `Shaders/Private/VirtualShadowMaps/VirtualShadowMapSMRTCommon.ush` (Private)

- lines: 98; parse: all-branches
- includes: L10 `../BlueNoise.ush`
- L7 #pragma `once`

#### Structs / classes (3)

- L12-19 _struct_ **`FSMRTSample`** `struct FSMRTSample`
  - L14 _member_ `bool bValid;`
  - L15 _member_ `float SampleDepth;`
  - L16 _member_ `float ReferenceDepth;`
  - L17 _member_ `float ExtrapolateSlope;`
  - L18 _member_ `bool bResetExtrapolation;`
- L32-36 _struct_ **`FSMRTResult`** `struct FSMRTResult`
  - L34 _member_ `bool bValidHit;`
  - L35 _member_ `float HitDepth;` — Valid if bValidHit is true
- L68-75 _struct_ **`FSMRTTraceSettings`** `struct FSMRTTraceSettings` — Handy structure for locally modifying some common SMRT parameters
  - L70 _member_ `int AdaptiveRayCount;`
  - L71 _member_ `int RayCount;`
  - L72 _member_ `int SamplesPerRay;`
  - L73 _member_ `float ExtrapolateMaxSlope;`
  - L74 _member_ `float TexelDitherScale;`

#### Functions (5)

- L21-30 _function_ `FSMRTSample InitSMRTSample()`
- L39-42 _function_ `float2 R2Sequence(int n)` — See http://extremelearning.com.au/unreasonable-effectiveness-of-quasirandom-sequences/
- L44-65 _function_ `float4 VirtualShadowMapGetRandomSample( uint2 PixelPos, uint TimeIndex, uint SampleIndex, uint MaxSampleCount)`
- L77-86 _function_ `FSMRTTraceSettings GetSMRTTraceSettingsDirectional()`
- L88-97 _function_ `FSMRTTraceSettings GetSMRTTraceSettingsLocal()`

### `Shaders/Private/VirtualShadowMaps/VirtualShadowMapSMRTTemplate.ush` (Private)

- lines: 142; parse: all-branches

#### Macros (#define, 1)

- L23 `#define SMRT_TEMPLATE_STATIC_SAMPLES_PER_RAY -1` _[#if !defined(SMRT_TEMPLATE_STATIC_SAMPLES_PER_RAY)]_

#### Functions (1)

- L26-141 _function_ `FSMRTResult SMRTRayCast( inout SMRT_TEMPLATE_RAY_STRUCT RayState, int NumSteps, float StepOffset)`

### `Shaders/Private/VirtualShadowMaps/VirtualShadowMapScreenRayTrace.ush` (Private)

- lines: 62; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../SceneTexturesCommon.ush`

#### Macros (#define, 1)

- L7 `#define SCREEN_RAY_SAMPLES 4` _[#if !defined(SCREEN_RAY_SAMPLES)]_

#### Functions (1)

- L12-61 _function_ `float VirtualShadowMapScreenRayCast( float3 RayOriginTranslatedWorld, float3 RayDirection, float RayLength, float Dither)` — Screen space ray trace to attempt to skip over ambiguous regions near the receiver surface Returns length at which to start the virtual shadow map ray; usually this is where the screen ray ended or went behind a surface

### `Shaders/Private/VirtualShadowMaps/VirtualShadowMapShadowCasterBounds.usf` (Private)

- lines: 219; parse: all-branches
- includes: L3 `../Common.ush`, L6 `VirtualShadowMapVisualize.ush`

#### Macros (#define, 2)

- L5 `#define NANITE_USE_VIEW_UNIFORM_BUFFER 1`
- L9 `#define MSAA_SAMPLE_COUNT 1` _[#if !defined(MSAA_SAMPLE_COUNT)]_

#### Entry points (2)

- L29-64 _entry_ `void MainVS( float3 InPosition : ATTRIBUTE0, uint InstanceId : SV_InstanceID, out FVSToPS Output )` — stage: **vertex (from C++ binding)** — C++: `FShadowCasterBoundsVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapArray.cpp:5336)
- L113-218 _entry_ `void MainPS( FVSToPS Input, out float4 OutColor : SV_Target0 )` — stage: **pixel (from C++ binding)** — C++: `FShadowCasterBoundsPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapArray.cpp:5337)

#### Structs / classes (1)

- L12-20 _struct_ **`FVSToPS`** `struct FVSToPS`
  - L14 _member_ `float4 SvPosition : SV_POSITION;`
  - L15 _member_ `float3 CubePosition : DBG_CUBE_POSITION;`
  - L16 _member_ `float3 WorldPosition : DBG_WORLD_POSITION;`
  - L17 _member_ `nointerpolation float3 Color : DBG_COLOR;`
  - L18 _member_ `nointerpolation uint InstanceId : DBG_INSTANCEID;`
  - L19 _member_ `nointerpolation float3 BoundingBoxMin : DBG_BB_MIN;`

#### Global resources (textures / buffers / samplers) (4)

- L67 _resource_ `Texture2DMS<float, MSAA_SAMPLE_COUNT> DebugDepth;` _[#if MSAA_SAMPLE_COUNT > 1]_
- L67 _resource_ `Texture2DMS<float, MSAA_SAMPLE_COUNT> DebugDepth;` _[#if MSAA_SAMPLE_COUNT > 1]_
- L69 _resource_ `Texture2D<float> DebugDepth;` _[#if !(MSAA_SAMPLE_COUNT > 1)]_
- L74 _resource_ `Texture2D<float> SceneDepth;`

#### Global parameters (uniforms) (1)

- L72 _parameter_ `float4 SampleOffsetArray[MSAA_SAMPLE_COUNT];`

#### Functions (5)

- L22-27 _function_ `float3 GetBoundsVertexTWSPosition(float3 CubeVertex, in FInstanceSceneData InstanceData)`
- L76-79 _function_ `float ComputeDepthMask(float DeviceZA, float DeviceZB, float Fade = 1e-5)`
- L82-92 _function_ `float3 FindMajorComponent(float3 InPosition)` — Find the axis with the largest absolute value, and return a vector pointing to that axis (or its negation)
- L95-106 _function_ `float3 ProjectOntoNearestCubeEdge(float3 InPosition)` — Given a position on a cube, return the point after projection onto the nearest cube edge.
- L108-111 _function_ `float LinStep(float E0, float E1, float Value)`

### `Shaders/Private/VirtualShadowMaps/VirtualShadowMapShadowCasterColor.usf` (Private)

- lines: 54; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../ScreenPass.ush`, L5 `../SceneData.ush`, L6 `VirtualShadowMapVisualize.ush`

#### Entry points (1)

- L17-53 _entry_ `float4 MainPS( noperspective float4 UVAndScreenPos : TEXCOORD0 ) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FDrawShadowCastersFalseColor` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapArray.cpp:5259)

#### Global resources (textures / buffers / samplers) (2)

- L8 _resource_ `Texture2D<uint> DebugAuxTexture;`
- L9 _resource_ `Texture2D SceneColorTexture;`

#### Global parameters (uniforms) (2)

- L14 _parameter_ `FScreenTransform ViewportUVToDebugAuxTextureUV;`
- L15 _parameter_ `FScreenTransform ViewportUVToSceneColorTextureUV;`

#### Top-level macro invocations (2)

- L11 _macro_call_ `SCREEN_PASS_TEXTURE_VIEWPORT(DebugAuxTextureViewport)`
- L12 _macro_call_ `SCREEN_PASS_TEXTURE_VIEWPORT(SceneColorTextureViewport)`

### `Shaders/Private/VirtualShadowMaps/VirtualShadowMapStats.ush` (Private)

- lines: 54; parse: all-branches
- includes: L7 `/Engine/Shared/VirtualShadowMapDefinitions.h`, L9 `../Common.ush`, L10 `../WaveOpUtil.ush`

#### Macros (#define, 1)

- L15 `#define VSM_GENERATE_STATS 0` _[#if !defined(VSM_GENERATE_STATS)]_

#### Global resources (textures / buffers / samplers) (1)

- L18 _resource_ `RWStructuredBuffer<uint> OutStatsBuffer;`

#### Functions (4)

- L20-26 _function_ `void StatsBufferWrite(uint Index, uint Value, bool bWriteEnabled = VSM_GENERATE_STATS)`
- L28-34 _function_ `void StatsBufferInterlockedAdd(uint Index, uint Value, bool bWriteEnabled = VSM_GENERATE_STATS)`
- L36-42 _function_ `void StatsBufferInterlockedInc(uint Index, bool bWriteEnabled = VSM_GENERATE_STATS)`
- L44-53 _function_ `void StatsBufferInterlockedEnableFlags(uint Index, uint Flags, bool bEnabled, bool bWriteEnabled = VSM_GENERATE_STATS)`

### `Shaders/Private/VirtualShadowMaps/VirtualShadowMapThrottle.usf` (Private)

- lines: 163; parse: all-branches
- includes: L3 `../Common.ush`, L4 `VirtualShadowMapHandle.ush`, L5 `VirtualShadowMapProjectionStructs.ush`, L6 `/Engine/Shared/VirtualShadowMapDefinitions.h`, L7 `/Engine/Shared/LightDefinitions.h`

#### Entry points (2)

- L27-61 _entry_ `[numthreads(64, 1, 1)] void ProcessPrevFramePerfDataCS(uint DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FProcessPrevFramePerfDataCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapArray.cpp:1284)
- L90-162 _entry_ `[numthreads(64, 1, 1)] void UpdateThrottleParametersCS(uint DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FUpdateThrottleParametersCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VirtualShadowMaps/VirtualShadowMapArray.cpp:1303)

#### Global resources (textures / buffers / samplers) (5)

- L9 _resource_ `StructuredBuffer<uint> PrevThrottleBuffer;`
- L10 _resource_ `StructuredBuffer<uint> PrevNanitePerformanceFeedback;`
- L12 _resource_ `StructuredBuffer<FNextVirtualShadowMapData> NextVirtualShadowMapData;`
- L16 _resource_ `RWStructuredBuffer<uint> OutThrottleBuffer;`
- L18 _resource_ `RWByteAddressBuffer InOutProjectionData;`

#### Global parameters (uniforms) (7)

- L13 _parameter_ `uint NextVirtualShadowMapDataCount;`
- L15 _parameter_ `uint NumThrottleBufferEntries;`
- L20 _parameter_ `float DynResThrottleStrength;`
- L21 _parameter_ `float ThrottleLoadBudget;`
- L22 _parameter_ `float ThrottleEMAHistoryWeight;`
- L24 _parameter_ `float ThrottleMaxBiasDirectional;`
- L25 _parameter_ `float ThrottleMaxBiasLocal;`

#### Functions (3)

- L63-67 _function_ `float CalculateCostHeuristic(const float NaniteClustersHW, const float NaniteClustersSW)`
- L69-82 _function_ `void ApplyResolutionLODBias(RWByteAddressBuffer ProjectionData, FVirtualShadowMapHandle VirtualShadowMapHandle, float ExtraBias)`
- L84-88 _function_ `uint GetLightType(RWByteAddressBuffer ProjectionData, FVirtualShadowMapHandle VirtualShadowMapHandle)`

### `Shaders/Private/VirtualShadowMaps/VirtualShadowMapTransmissionCommon.ush` (Private)

- lines: 112; parse: all-branches
- includes: L8 `../Common.ush`, L9 `../SceneTexturesCommon.ush`, L10 `../DeferredShadingCommon.ush`, L11 `../TransmissionCommon.ush`, L12 `VirtualShadowMapProjectionCommon.ush`, L13 `../Substrate/SubstrateSubsurface.ush`, L15 `../ToonProfileCommon.ush` [SUBSTRATE_ENABLED]
- L6 #pragma `once`

#### Functions (2)

- L18-80 _function_ `FSubsurfaceOpacityMFP GetSubsurfaceOpacityFromGbuffer(uint2 PixelPos)`
- L83-111 _function_ `float GetShadowFactorSubsurface(float ShadowFactor, float OccluderDistance, FSubsurfaceOpacityMFP SubsurfaceOpacityMFP)` — Compute Subsurface transmission

### `Shaders/Private/VirtualShadowMaps/VirtualShadowMapVisualize.ush` (Private)

- lines: 85; parse: all-branches
- includes: L5 `VirtualShadowMapPageCacheCommon.ush`, L6 `../ViewData.ush`, L7 `../Nanite/NaniteSceneCommon.ush`
- L3 #pragma `once`

#### Structs / classes (1)

- L9-13 _struct_ **`FShadowCasterDrawParameters`** `struct FShadowCasterDrawParameters`
  - L11 _member_ `float3 Color;`
  - L12 _member_ `bool bShowBounds;`

#### Functions (1)

- L15-85 _function_ `FShadowCasterDrawParameters GetShadowCasterDrawParameters( in FNaniteView NaniteView, in FInstanceSceneData InstanceData, in FInstanceViewData InstanceViewData, in FInstanceDynamicData InstanceDynamicData, in FPrimitiveSceneData PrimitiveData)`
