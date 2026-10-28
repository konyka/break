# Shaders / Shaders/Private/InstanceCulling

- files: 7; lines: 1435
- record kinds: cpp_binding=9, define=23, entry=9, function=25, groupshared=6, include=29, member=66, parameter=13, resource=29, struct=13

### `Shaders/Private/InstanceCulling/BuildInstanceDrawCommands.usf` (Private)

- lines: 381; parse: all-branches
- includes: L31 `../Common.ush`, L32 `../SceneData.ush`, L33 `../LightmapData.ush`, L34 `../DynamicMeshBounds.ush`, L35 `InstanceCullingCommon.ush`, L36 `InstanceCompactionCommon.ush`, L40 `../Nanite/NaniteCullingCommon.ush`, L41 `../WaveOpUtil.ush`, L42 `../ComputeShaderUtils.ush`, L50 `InstanceCullingLoadBalancer.ush`, L51 `InstanceCullingSetup.ush`, L78 `../SceneDataMobileWriter.ush` [PLATFORM_USES_PRIMITIVE_UBO]

#### Macros (#define, 8)

- L7 `#define ENABLE_PER_INSTANCE_CUSTOM_DATA 1` _[#if !defined(ENABLE_PER_INSTANCE_CUSTOM_DATA)]_
- L12 `#define ENABLE_EXTENDED_INSTANCE_CULLING_PAYLOADS 1` _[#if ENABLE_INSTANCE_COMPACTION]_
- L16 `#define INSTANCE_DATA_STRIDE_ELEMENTS 1u` _[#if !defined(INSTANCE_DATA_STRIDE_ELEMENTS)]_
- L21 `#define VF_SUPPORTS_PRIMITIVE_SCENE_DATA 1u` _[#if !defined(VF_SUPPORTS_PRIMITIVE_SCENE_DATA)]_
- L26 `#define ALLOW_TEMPLATES 0`
- L29 `#define USE_HZB_SHARED_SAMPLERS 0`
- L39 `#define NANITE_CULLING_ENABLE_MIN_RADIUS_CULL 1`
- L46 `#define LOAD_BALANCER_SINGLE_INSTANCE_MODE 1` _[#if SINGLE_INSTANCE_MODE]_
- L4 #pragma `message("UESHADERMETADATA_VERSION 5F4355AE-A326-40DB-99A4-0666E9076245")`

#### Entry points (2)

- L242-365 _entry_ `[numthreads(NUM_THREADS_PER_GROUP, 1, 1)] void InstanceCullBuildInstanceIdBufferCS(uint3 GroupId : SV_GroupID, int GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FBuildInstanceIdBufferAndCommandsFromPrimitiveIdsCs` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/InstanceCulling/InstanceCullingContext.cpp:603) — Each thread loops over a range on instances loaded from a buffer. The instance bounds are projected to all cached virtual shadow map address space and any overlapped pages are marked as invalid.
- L371-380 _entry_ `[numthreads(NUM_THREADS_PER_GROUP, 1, 1)] void ClearIndirectArgInstanceCountCS(uint3 GroupId : SV_GroupID, int GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FClearIndirectArgInstanceCountCs` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/InstanceCulling/InstanceCullingContext.cpp:1391)

#### Global resources (textures / buffers / samplers) (10)

- L53 _resource_ `StructuredBuffer<uint2> DrawCommandDescs;`
- L54 _resource_ `Buffer<uint> InstanceIdOffsetBuffer;`
- L55 _resource_ `StructuredBuffer<uint> ViewIds;`
- L64 _resource_ `RWStructuredBuffer<uint> InstanceIdsBufferOut;`
- L65 _resource_ `RWStructuredBuffer<float4> InstanceIdsBufferOutMobile;`
- L66 _resource_ `RWBuffer<uint> DrawIndirectArgsBufferOut;`
- L69 _resource_ `StructuredBuffer<FPackedDrawCommandCompactionData> DrawCommandCompactionData;` — Used for draw commands that need to use compaction to preserve instance order
- L70 _resource_ `RWStructuredBuffer<uint> CompactInstanceIdsBufferOut;`
- L71 _resource_ `RWStructuredBuffer<uint> CompactionBlockCounts;`
- L74 _resource_ `Buffer<uint> InstanceOcclusionQueryBuffer;` — uint per instance with 1 bit per view identified by NaniteView::InstanceOcclusionQueryMask

#### Global parameters (uniforms) (7)

- L57 _parameter_ `uint NumViewIds;`
- L58 _parameter_ `uint DynamicInstanceIdOffset;`
- L59 _parameter_ `uint DynamicInstanceIdMax;`
- L60 _parameter_ `uint NumCullingViews;`
- L61 _parameter_ `uint CurrentBatchProcessingMode;`
- L62 _parameter_ `uint bDrawOnlySelected;`
- L368 _parameter_ `uint NumIndirectArgs;`

#### Functions (5)

- L80-87 _function_ `void WriteDataUBO(RWStructuredBuffer<float4> Output, uint Offset, uint InstanceId, FPrimitiveSceneData PrimitiveData, FInstanceSceneData InstanceData, uint MeshLODIndex)` _[#if PLATFORM_USES_PRIMITIVE_UBO]_
- L90-101 _function_ `void WriteInstance(uint Offset, uint InstanceId, FPrimitiveSceneData PrimitiveData, FInstanceSceneData InstanceData, uint ViewIdIndex, uint CullingFlags, uint MeshLODIndex)`
- L103-110 _function_ `void WriteInstanceForCompaction(uint Offset, bool bVisible, uint InstanceId, FInstanceSceneData InstanceData, uint ViewIdIndex, uint CullingFlags)`
- L112-115 _function_ `float RoundUpF16(float DeviceZ)`
- L117-235 _function_ `bool IsInstanceVisible(FPrimitiveSceneData PrimitiveData, FInstanceSceneData InstanceData, uint InstanceId, uint ViewIdIndex, bool bAllowOcclusionCulling, bool bDrawOnlySelected, FDrawCommandDesc DrawCommandDesc, inout uint CullingFlags)`

### `Shaders/Private/InstanceCulling/CompactVisibleInstances.usf` (Private)

- lines: 161; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../ComputeShaderUtils.ush`, L5 `../ThreadGroupPrefixSum.ush`, L6 `InstanceCompactionCommon.ush`

#### Macros (#define, 1)

- L10 `#define COMPACTION_USES_WAVE_OPS 0` _[#if COMPILER_SUPPORTS_WAVE_VOTE]_

#### Entry points (2)

- L34-81 _entry_ `[numthreads(NUM_THREADS_PER_GROUP, 1, 1)] void CalculateCompactBlockInstanceOffsetsCS(uint3 GroupId : SV_GroupID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FCalculateCompactBlockInstanceOffsetsCs` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/InstanceCulling/InstanceCullingContext.cpp:461) — Entry point _[#if CALCULATE_COMPACT_BLOCK_INSTANCE_OFFSETS]_
- L108-159 _entry_ `[numthreads(NUM_THREADS_PER_GROUP, 1, 1)] void CompactVisibleInstances(uint3 GroupId : SV_GroupID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FCompactVisibleInstancesCs` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/InstanceCulling/InstanceCullingContext.cpp:490) — Entry point _[#if COMPACT_VISIBLE_INSTANCES]_

#### Global resources (textures / buffers / samplers) (9)

- L14 _resource_ `StructuredBuffer<FPackedDrawCommandCompactionData> DrawCommandCompactionData;` — Data needed per draw command for compaction
- L26 _resource_ `StructuredBuffer<uint> BlockInstanceCounts;` — Number of valid instances per block in a draw command (accumulated by BuildInstanceDrawCommands.usf) _[#if CALCULATE_COMPACT_BLOCK_INSTANCE_OFFSETS]_
- L29 _resource_ `RWStructuredBuffer<uint> BlockDestInstanceOffsetsOut;` — Destination instance offset per block of instances in a draw command. (Relative to draw command's InstanceIdOffset) _[#if CALCULATE_COMPACT_BLOCK_INSTANCE_OFFSETS]_
- L31 _resource_ `RWBuffer<uint> DrawIndirectArgsBufferOut;` — The indirect args buffer to receive the final, compacted instance count _[#if CALCULATE_COMPACT_BLOCK_INSTANCE_OFFSETS]_
- L96 _resource_ `StructuredBuffer<uint> BlockDrawCommandIndices;` — Draw command index per block _[#if COMPACT_VISIBLE_INSTANCES]_
- L98 _resource_ `StructuredBuffer<uint> InstanceIdsBufferIn;` — The raw, uncompacted instance ID buffer (provided by BuildInstanceDrawCommands.usf) _[#if COMPACT_VISIBLE_INSTANCES]_
- L100 _resource_ `StructuredBuffer<uint> BlockDestInstanceOffsets;` — Instance output offsets per block (provided by CalculateCompactBlockInstanceOffsetsCS) _[#if COMPACT_VISIBLE_INSTANCES]_
- L103 _resource_ `RWStructuredBuffer<uint> InstanceIdsBufferOut;` — The compacted output buffer of InstanceIds (non-mobile) _[#if COMPACT_VISIBLE_INSTANCES]_
- L105 _resource_ `RWByteAddressBuffer InstanceIdsBufferOutMobile;` — The compacted output buffer of instance data consumed by vertex shaders on mobile _[#if COMPACT_VISIBLE_INSTANCES]_

### `Shaders/Private/InstanceCulling/InstanceCompactionCommon.ush` (Private)

- lines: 57; parse: all-branches
- L3 #pragma `once`

#### Structs / classes (2)

- L21-28 _struct_ **`FPackedDrawCommandCompactionData`** `struct FPackedDrawCommandCompactionData`
  - L23 _member_ `uint NumInstances_NumViews;`
  - L24 _member_ `uint BlockOffset;`
  - L25 _member_ `uint IndirectArgIndex;`
  - L26 _member_ `uint SrcInstanceIdOffset;`
  - L27 _member_ `uint DestInstanceIdOffset;`
- L30-44 _struct_ **`FDrawCommandCompactionData`** `struct FDrawCommandCompactionData`
  - L33 _member_ `uint NumViews;` — The number of views for which the instances were written
  - L35 _member_ `uint NumInstances;` — The total number of instances in the draw command
  - L37 _member_ `uint BlockOffset;` — The offset of the first compaction "block" (group of N instances * NumViewIds) of the draw command
  - L39 _member_ `uint IndirectArgIndex;` — The indirect argument index of the draw command
  - L41 _member_ `uint SrcInstanceIdOffset;` — The offset of the input instance ID buffer for the start of the draw command before compaction
  - L43 _member_ `uint DestInstanceIdOffset;` — The offset of the output instance ID buffer for the start of the draw command after compaction

#### Functions (3)

- L10-13 _function_ `uint GetCompactionBlockCount(uint NumInstances)` — Determines number of compaction blocks required for the specified number of instances
- L16-19 _function_ `uint GetCompactionBlockIndexFromInstanceIndex(uint InstanceIndex)` — Determines number of compaction blocks required for the specified number of instances
- L46-57 _function_ `FDrawCommandCompactionData UnpackDrawCommandCompactionData(FPackedDrawCommandCompactionData Data)`

### `Shaders/Private/InstanceCulling/InstanceCullingCommon.ush` (Private)

- lines: 184; parse: all-branches
- includes: L5 `../Common.ush`, L6 `/Engine/Shared/InstanceCullingDefinitions.h`

#### Macros (#define, 2)

- L9 `#define BATCH_PROCESSING_MODE_NUM 1` _[#if !defined(BATCH_PROCESSING_MODE_NUM)]_
- L13 `#define ENABLE_EXTENDED_INSTANCE_CULLING_PAYLOADS 0` _[#if !defined(ENABLE_EXTENDED_INSTANCE_CULLING_PAYLOADS)]_
- L3 #pragma `once`

#### Structs / classes (5)

- L16-24 _struct_ **`FDrawCommandDesc`** `struct FDrawCommandDesc`
  - L18 _member_ `bool bMaterialUsesWorldPositionOffset;`
  - L19 _member_ `bool bMaterialAlwaysEvaluatesWorldPositionOffset;`
  - L20 _member_ `uint MeshLODIndex;`
  - L21 _member_ `float MinScreenSize;`
  - L22 _member_ `float MaxScreenSize;`
  - L23 _member_ `int DynamicMeshBoundsIndex;`
- L38-52 _struct_ **`FContextBatchInfoPacked`** `struct FContextBatchInfoPacked`
  - L40 _member_ `uint IndirectArgOffset;`
  - L41 _member_ `uint InstanceDataWriteOffset;`
  - L42 _member_ `uint PayloadOffset;`
  - L43 _member_ `uint CompactionDataOffset;`
  - L44 _member_ `uint ViewIdsOffset;`
  - L45 _member_ `uint NumViewIds_Flags;`
  - L46 _member_ `uint DynamicInstanceIdOffset;`
  - L47 _member_ `uint DynamicInstanceIdMax;`
  - L50 _member_ `uint ItemDataOffset0;` — Must be equal to ItemDataOffset[BATCH_PROCESSING_MODE_NUM] Not using array here to avoid GL shader compiler bug on Adreno devices
  - L51 _member_ `uint ItemDataOffset1;`
- L54-70 _struct_ **`FContextBatchInfo`** `struct FContextBatchInfo`
  - L56 _member_ `uint IndirectArgOffset;`
  - L57 _member_ `uint InstanceDataWriteOffset;`
  - L58 _member_ `uint PayloadOffset;`
  - L59 _member_ `uint CompactionDataOffset;`
  - L60 _member_ `uint ViewIdsOffset;`
  - L61 _member_ `uint NumViewIds;`
  - L62 _member_ `bool bAllowOcclusionCulling;`
  - L63 _member_ `bool bDrawOnlySelected;`
  - L64 _member_ `uint DynamicInstanceIdOffset;`
  - L65 _member_ `uint DynamicInstanceIdMax;`
  - L68 _member_ `uint ItemDataOffset0;` — Must be equal to ItemDataOffset[BATCH_PROCESSING_MODE_NUM] Not using array here to avoid GL shader compiler bug on Adreno devices
  - L69 _member_ `uint ItemDataOffset1;`
- L104-116 _struct_ **`FInstanceCullingPayload`** `struct FInstanceCullingPayload`
  - L107 _member_ `bool bDynamicInstanceDataOffset;` — Whether or not the instances are dynamic
  - L109 _member_ `uint IndirectArgIndex;` — The IndirectArgs index for instances in the run.
  - L111 _member_ `uint InstanceDataOffset;` — The instance data offset of the start of the current instance run, or -1 if this data should not be needed for this work item
  - L113 _member_ `uint RunInstanceOffset;` — The number of instances added from other runs before this one, or -1 if this data should not be needed for this work item
  - L115 _member_ `uint CompactionDataIndex;` — When compaction is enabled, the index into the FDrawCommandCompactionData buffer (or -1 otherwise)
- L118-124 _struct_ **`FPackedInstanceCullingPayload`** `struct FPackedInstanceCullingPayload`
  - L120 _member_ `uint bDynamicInstanceDataOffset_IndirectArgIndex;`
  - L121 _member_ `uint InstanceDataOffset;`
  - L122 _member_ `uint RunInstanceOffset;`
  - L123 _member_ `uint CompactionDataIndex;`

#### Global resources (textures / buffers / samplers) (3)

- L82 _resource_ `StructuredBuffer<FContextBatchInfoPacked> BatchInfos;` _[#if ENABLE_BATCH_MODE]_
- L83 _resource_ `StructuredBuffer<uint> BatchInds;` _[#if ENABLE_BATCH_MODE]_
- L149 _resource_ `StructuredBuffer<FPackedInstanceCullingPayload> InstanceCullingPayloads;` _[#if ENABLE_EXTENDED_INSTANCE_CULLING_PAYLOADS]_

#### Functions (7)

- L26-36 _function_ `FDrawCommandDesc UnpackDrawCommandDesc(uint2 PackedData)`
- L72-79 _function_ `uint GetItemDataOffset(FContextBatchInfo BatchInfo, uint BatchProcessingMode)`
- L84-101 _function_ `FContextBatchInfo LoadBatchInfo(uint GroupIndex)` _[#if ENABLE_BATCH_MODE]_
- L126-129 _function_ `bool IsExtendedInstanceCullingPayload(uint WorkItemPayload)`
- L131-134 _function_ `bool IsDynamicInstanceDataOffset(uint WorkItemPayload)`
- L136-146 _function_ `FInstanceCullingPayload UnpackInstanceCullingPayload(FPackedInstanceCullingPayload Payload)`
- L158-184 _function_ `FInstanceCullingPayload LoadInstanceCullingPayload(uint WorkItemPayload, FContextBatchInfo BatchInfo)` — Retrieves the instance culling payload data. When instance compaction is not needed to preserve instance order, much of the instance culling payload need not take up space, so it is compacted into the 26-bit payload provided by the load balancer. Otherwise, the first bit of the load balancer's payload is set, and the remaining 25 bits are used to index into the payload structured buffer.

### `Shaders/Private/InstanceCulling/InstanceCullingLoadBalancer.ush` (Private)

- lines: 266; parse: all-branches
- includes: L5 `../Common.ush`, L6 `../WaveOpUtil.ush`, L7 `../ComputeShaderUtils.ush`

#### Macros (#define, 2)

- L11 `#define USE_WAVE_BIT_PREFIX_WORK_DISTRIBUTION 0` _[#if COMPILER_SUPPORTS_WAVE_VOTE]_
- L16 `#define LOAD_BALANCER_SINGLE_INSTANCE_MODE 0` _[#if !defined(LOAD_BALANCER_SINGLE_INSTANCE_MODE)]_
- L3 #pragma `once`

#### Structs / classes (5)

- L19-22 _struct_ **`FPackedInstanceBatch`** `struct FPackedInstanceBatch`
  - L21 _member_ `uint FirstItem_NumItems;`
- L24-30 _struct_ **`FPackedInstanceBatchItem`** `struct FPackedInstanceBatchItem`
  - L27 _member_ `uint InstanceDataOffset_NumInstances;` — packed 32-NumInstancesItemBits:NumInstancesItemBits - need one more bit for the case where one item has ThreadGroupSize work to do
  - L29 _member_ `uint Payload_BatchPrefixOffset;` — packed 32-PrefixBits:PrefixBits
- L40-44 _struct_ **`FInstanceBatch`** `struct FInstanceBatch`
  - L42 _member_ `uint FirstItem;`
  - L43 _member_ `uint NumItems;`
- L55-61 _struct_ **`FInstanceBatchItem`** `struct FInstanceBatchItem`
  - L57 _member_ `uint InstanceDataOffset;`
  - L58 _member_ `uint NumInstances;`
  - L59 _member_ `uint Payload;`
  - L60 _member_ `uint BatchPrefixOffset;`
- L152-160 _struct_ **`FInstanceWorkSetup`** `struct FInstanceWorkSetup`
  - L154 _member_ `bool bValid;`
  - L155 _member_ `FInstanceBatchItem Item;`
  - L157 _member_ `int LocalItemIndex;` — Work out who I am in expansion of  the item in range [0,WorkItem.Count], may be negative when no work at end of batch
  - L158 _member_ `uint WorkItemIndex;`
  - L159 _member_ `uint GroupIndexPerBatch;` — 0..NumGroupsPerBatch if multiple groups per batch are requested

#### Global resources (textures / buffers / samplers) (2)

- L33 _resource_ `StructuredBuffer<FPackedInstanceBatch> BatchBuffer;`
- L34 _resource_ `StructuredBuffer<FPackedInstanceBatchItem> ItemBuffer;`

#### Global parameters (uniforms) (3)

- L35 _parameter_ `uint NumBatches;`
- L36 _parameter_ `uint NumItems;`
- L37 _parameter_ `uint NumGroupsPerBatch;`

#### groupshared (3)

- L78 _groupshared_ `groupshared uint WorkBoundary[NUM_THREADS_PER_GROUP];` _[#if USE_WAVE_BIT_PREFIX_WORK_DISTRIBUTION]_
- L82 _groupshared_ `groupshared uint ItemIndex[NUM_THREADS_PER_GROUP];` _[#if !(USE_WAVE_BIT_PREFIX_WORK_DISTRIBUTION)]_
- L150 _groupshared_ `groupshared FInstanceBatchItem Items[NUM_THREADS_PER_GROUP];`

#### Functions (7)

- L46-53 _function_ `FInstanceBatch UnpackBatch(FPackedInstanceBatch PackedBatch, uint ItemDataOffset)`
- L63-73 _function_ `FInstanceBatchItem UnpackItem(FPackedInstanceBatchItem PackedItem)`
- L84-97 _function_ `void PrefixMaxStep(uint ElementIndex, uint StepSize, inout uint CurrentValue)` _[#if !(USE_WAVE_BIT_PREFIX_WORK_DISTRIBUTION)]_
- L99-113 _function_ `uint PrefixMaxLastStep(uint ElementIndex, inout uint CurrentValue)` _[#if !(USE_WAVE_BIT_PREFIX_WORK_DISTRIBUTION)]_
- L115-145 _function_ `uint PrefixMax(uint ElementIndex)` _[#if !(USE_WAVE_BIT_PREFIX_WORK_DISTRIBUTION)]_
- L164-260 _function_ `FInstanceWorkSetup InstanceCullingLoadBalancer_Setup(uint3 GroupId, uint GroupThreadIndex, uint ItemDataOffset, bool bSupportMultipleBatches = false)` — Set bSupportMultipleBatches to true if this kernel is dispatched with more than 1 group per batch.
- L263-266 _function_ `uint InstanceCullingLoadBalancer_GetNumBatches()`

### `Shaders/Private/InstanceCulling/InstanceCullingOcclusionQuery.usf` (Private)

- lines: 342; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../SceneData.ush`, L5 `../VertexFactoryCommon.ush`, L6 `../Nanite/NaniteHZBCull.ush`, L20 `InstanceCullingSetup.ush` [USE_LOAD_BALANCER]

#### Macros (#define, 10)

- L10 `#define NUM_THREADS_PER_GROUP_DEFAULT 64` _[#if !defined(NUM_THREADS_PER_GROUP_DEFAULT)]_
- L14 `#define NUM_THREADS_PER_GROUP NUM_THREADS_PER_GROUP_DEFAULT` _[#if !defined(NUM_THREADS_PER_GROUP)]_
- L19 `#define LOAD_BALANCER_SINGLE_INSTANCE_MODE 0` _[#if USE_LOAD_BALANCER]_
- L24 `#define HZB_DESIRED_FOOTPRINT_PIXELS 4` _[#if !defined(HZB_DESIRED_FOOTPRINT_PIXELS)]_
- L32 `#define DIM_MULTI_VIEW 0` _[#if !defined(DIM_MULTI_VIEW)]_
- L41 `#define EInstanceVisibilityStatus uint`
- L42 `#define IVS_Hidden 0`
- L43 `#define IVS_Visible 1`
- L44 `#define IVS_PossiblyVisible 2`
- L45 `#define IVS_Incompatible 3`

#### Entry points (5)

- L153-227 _entry_ `[numthreads(NUM_THREADS_PER_GROUP, 1, 1)] void MainCS(uint3 GroupId : SV_GroupID, uint GroupThreadIndex : SV_GroupIndex, uint DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FInstanceCullingOcclusionQueryCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/InstanceCulling/InstanceCullingOcclusionQuery.cpp:122)
- L229-256 _entry_ `void MainVS( float3 InPosition : ATTRIBUTE0, uint InstanceId : SV_InstanceID, out nointerpolation uint OutInstanceId : INSTANCE_ID, out nointerpolation uint OutVisibilityMask : VISIBILITY_MASK, out float4 OutPosition : SV_POSITION )` — stage: **vertex (from C++ binding)** — C++: `FInstanceCullingOcclusionQueryVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/InstanceCulling/InstanceCullingOcclusionQuery.cpp:178)
- L259-268 _entry_ `EARLYDEPTHSTENCIL void MainPS( in nointerpolation uint InstanceId : INSTANCE_ID, in nointerpolation uint VisibilityMask : VISIBILITY_MASK, out float4 OutColor : SV_Target0 )` — stage: **pixel (from C++ binding)** — C++: `FInstanceCullingOcclusionQueryPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/InstanceCulling/InstanceCullingOcclusionQuery.cpp:179)
- L274-309 _entry_ `void DebugMainVS( float3 InPosition : ATTRIBUTE0, uint InstanceId : SV_InstanceID, out nointerpolation uint OutDebugVisibility : INSTANCE_DEBUG_VISIBILITY, out float4 OutPosition : SV_POSITION )` — stage: **vertex (from C++ binding)** — C++: `FInstanceCullingOcclusionQueryDebugVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/InstanceCulling/InstanceCullingOcclusionQuery.cpp:869)
- L311-340 _entry_ `void DebugMainPS( in nointerpolation uint DebugVisibility : INSTANCE_DEBUG_VISIBILITY, out float4 OutColor : SV_Target0 )` — stage: **pixel (from C++ binding)** — C++: `FInstanceCullingOcclusionQueryDebugPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/InstanceCulling/InstanceCullingOcclusionQuery.cpp:870)

#### Global resources (textures / buffers / samplers) (5)

- L35 _resource_ `RWBuffer<uint> RWVisibilityMask;`
- L130 _resource_ `RWBuffer<uint> OutIndirectArgsBuffer;`
- L131 _resource_ `RWBuffer<uint> OutInstanceIdBuffer;`
- L134 _resource_ `Buffer<uint> InstanceIdBuffer;` — Remap linear visible index to a visible GPUScene instance index
- L272 _resource_ `Buffer<uint> InstanceOcclusionQueryBuffer;`

#### Global parameters (uniforms) (3)

- L37 _parameter_ `uint NumInstances;`
- L38 _parameter_ `uint ViewMask;`
- L39 _parameter_ `float OcclusionSlop;`

#### groupshared (3)

- L126 _groupshared_ `groupshared uint GroupNumVisibleInstances;` — TODO: could also add a wave-op variant in the future if there is evidence of significant perf overhead
- L127 _groupshared_ `groupshared uint GroupVisibleInstances[NUM_THREADS_PER_GROUP];`
- L128 _groupshared_ `groupshared uint GroupOutputBaseIndex;`

#### Functions (2)

- L47-123 _function_ `EInstanceVisibilityStatus GetInstanceDataAndVisibility(uint InstanceId, out FInstanceSceneData OutInstanceData)`
- L136-151 _function_ `bool LoadInstanceId(uint3 GroupId, uint GroupThreadIndex, uint DispatchThreadId, inout uint InstanceId)`

### `Shaders/Private/InstanceCulling/InstanceCullingSetup.ush` (Private)

- lines: 44; parse: all-branches
- includes: L5 `../Common.ush`, L7 `InstanceCullingCommon.ush`, L9 `InstanceCullingLoadBalancer.ush`
- L3 #pragma `once`

#### Structs / classes (1)

- L11-17 _struct_ **`FInstanceCullingSetup`** `struct FInstanceCullingSetup`
  - L13 _member_ `FInstanceWorkSetup InstanceWorkSetup;`
  - L14 _member_ `bool bValid;`
  - L15 _member_ `bool bIsDynamic;`
  - L16 _member_ `uint InstanceId;`

#### Functions (1)

- L21-43 _function_ `FInstanceCullingSetup LoadInstanceCullingSetup(uint3 GroupId, uint GroupThreadIndex, uint InDynamicInstanceIdOffset, uint InDynamicInstanceIdMax, uint ItemDataOffset)` — InDynamicInstanceIdOffset/InDynamicInstanceIdMax are only needed if you want to support dynamic instances, otherwise you can provide 0 ItemDataOffset is only needed if you work in batched mode where multiple load balancers are processed at the same time, see ENABLE_BATCH_MODE
