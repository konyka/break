# Shaders / Shaders/Private/Nanite

- files: 52; lines: 26220
- record kinds: cpp_binding=91, define=323, entry=93, function=536, groupshared=64, include=332, macro_block=1, macro_call=17, member=676, method=139, method_proto=11, parameter=165, resource=302, static_const=9, struct=115, unparsed=1

### `Shaders/Private/Nanite/NaniteAttributeDecode.ush` (Private)

- lines: 991; parse: all-branches
- includes: L5 `NaniteDataDecode.ush`, L6 `../Barycentrics.ush`, L7 `../MonteCarlo.ush`

#### Macros (#define, 8)

- L11 `#define NANITE_FIXED_FUNCTION_BIN_MASK_VOXEL 0x10` _[#if NANITE_VOXEL_DATA]_
- L13 `#define NANITE_FIXED_FUNCTION_BIN_MASK_VOXEL 0` _[#if !(NANITE_VOXEL_DATA)]_
- L17 `#define NANITE_FIXED_FUNCTION_BIN_MASK_CURVE 0x20` _[#if NANITE_CURVE_DATA]_
- L19 `#define NANITE_FIXED_FUNCTION_BIN_MASK_CURVE 0` _[#if !(NANITE_CURVE_DATA)]_
- L22 `#define NANITE_FIXED_FUNCTION_BIN_MASK (0xFu \| NANITE_FIXED_FUNCTION_BIN_MASK_VOXEL \| NANITE_FIXED_FUNCTION_BIN_MASK_CURVE)`
- L92 `#define SIZEOF_PACKED_UV_HEADER 8`
- L100 `#define SIZEOF_PACKED_BONE_INFLUENCE_HEADER 8`
- L945 `#define DEFINE_ITERATE_CLUSTER_SEGMENTS (0)` _[#if !defined(DEFINE_ITERATE_CLUSTER_SEGMENTS)]_
- L3 #pragma `once`

#### Structs / classes (7)

- L24-31 _struct_ **`FNaniteRawAttributeData`** `struct FNaniteRawAttributeData`
  - L26 _member_ `float4 TangentXAndSign;`
  - L27 _member_ `float3 TangentZ;`
  - L28 _member_ `float CurveRadius;`
  - L29 _member_ `float4 Color;`
  - L30 _member_ `float2 TexCoords[NANITE_MAX_UVS];`
- L33-57 _struct_ **`FNaniteTangentBasis`** `struct FNaniteTangentBasis`
  - L35 _member_ `float4 TangentXAndSign;` — Tangent and Bitangent Sign Bit
  - L36 _member_ `float3 TangentZ;` — Normal
  - L38 _method_ `float3 DeriveTangentY()`
  - L44 _method_ `void RecalculateTangentX()`
  - L52 _method_ `void Normalize()`
- L93-98 _struct_ **`FUVHeader`** `struct FUVHeader`
  - L95 _member_ `uint2 Min;`
  - L96 _member_ `uint2 NumBits;`
  - L97 _member_ `uint NumMantissaBits;`
- L101-107 _struct_ **`FBoneInfluenceHeader`** `struct FBoneInfluenceHeader`
  - L103 _member_ `uint DataAddress;`
  - L104 _member_ `uint NumVertexBoneInfluences;`
  - L105 _member_ `uint NumVertexBoneIndexBits;`
  - L106 _member_ `uint NumVertexBoneWeightBits;`
- L268-276 _struct_ **`FNaniteMaterialPrimitiveData`** `struct FNaniteMaterialPrimitiveData`
  - L270 _member_ `uint MaterialBufferOffset;`
  - L271 _member_ `uint MaterialMaxIndex;`
  - L272 _member_ `uint MeshPassMask;`
  - L273 _member_ `bool bHasUVDensities;`
  - L274 _member_ `uint HitProxyBufferOffset;`
  - L275 _member_ `float4 OverlayColor;`
- L312-319 _struct_ **`FNaniteMaterialSlot`** `struct FNaniteMaterialSlot`
  - L314 _member_ `uint TriangleShadingBin;`
  - L315 _member_ `uint VoxelShadingBin;`
  - L316 _member_ `uint CurveShadingBin;`
  - L317 _member_ `uint RasterBin;`
  - L318 _member_ `uint FallbackRasterBin;`
- L632-637 _struct_ **`FNaniteAssemblyBoneInfluenceHeader`** `struct FNaniteAssemblyBoneInfluenceHeader`
  - L634 _member_ `uint NumInfluences;`
  - L635 _member_ `uint SingleBoneIndex;`
  - L636 _member_ `uint InfluenceBufferOffset;`

#### Functions (50)

- L59-65 _function_ `FNaniteTangentBasis MakeTangentBasis(FNaniteRawAttributeData RawAttributeData)`
- L68-74 _function_ `FNaniteTangentBasis WaveReadLaneAt(FNaniteTangentBasis In, uint SrcIndex)`
- L77-90 _function_ `FNaniteRawAttributeData WaveReadLaneAt(FNaniteRawAttributeData In, uint SrcIndex)`
- L109-122 _function_ `FUVHeader UnpackUVHeader(uint2 Data)`
- L124-128 _function_ `FUVHeader GetUVHeader(ByteAddressBuffer InputBuffer, uint StartOffset, uint Index)`
- L130-134 _function_ `FUVHeader GetUVHeader(RWByteAddressBuffer InputBuffer, uint StartOffset, uint Index)`
- L136-146 _function_ `FBoneInfluenceHeader GetBoneInfluenceHeader(FCluster Cluster)`
- L148-158 _function_ `float DecodeUVFloat(uint EncodedValue, uint NumMantissaBits)`
- L160-166 _function_ `float2 UnpackTexCoord(uint2 Packed, FUVHeader UVHeader)`
- L168-176 _function_ `float3 UnpackNormal(uint Packed, uint Bits)`
- L178-192 _function_ `uint CalculateMaxAttributeBits(uint NumTexCoordInterpolators, bool bCompileTimeCouldBeCurve)`
- L194-204 _function_ `void DecodeMaterialRange(uint EncodedRange, out uint TriStart, out uint TriLength, out uint MaterialIndex)`
- L206-209 _function_ `bool IsMaterialFastPath(FCluster InCluster)`
- L211-222 _function_ `uint GetMaterialCount(FCluster InCluster)`
- L224-266 _function_ `uint GetRelativeMaterialIndex(FCluster InCluster, uint InTriIndex)`
- L278-289 _function_ `FNaniteMaterialPrimitiveData UnpackNaniteMaterialPrimitiveData(uint4 Data)`
- L291-310 _function_ `FNaniteMaterialPrimitiveData LoadNaniteMaterialPrimitiveData(uint InPrimitiveIndex)`
- L321-330 _function_ `FNaniteMaterialSlot UnpackMaterialSlot(uint4 Data)`
- L332-336 _function_ `FNaniteMaterialSlot LoadMaterialSlot(uint Offset)`
- L338-345 _function_ `float4 LoadMaterialUVDensities(uint Offset)`
- L347-364 _function_ `uint GetMaterialSlotOffset(uint InRelativeMaterialIndex, uint InPrimitiveIndex, uint InMeshPassIndex)`
- L366-389 _function_ `uint GetMaterialUVDensitiesOffset(uint InRelativeMaterialIndex, uint InPrimitiveIndex)`
- L391-394 _function_ `FNaniteMaterialSlot LoadMaterialSlot(uint InRelativeMaterialIndex, uint InPrimitiveIndex, uint InMeshPassIndex)`
- L396-399 _function_ `float4 LoadMaterialUVDensities(uint InRelativeMaterialIndex, uint InPrimitiveIndex)`
- L401-410 _function_ `uint GetMaterialShadingBinFromIndex( uint InRelativeMaterialIndex, uint InPrimitiveIndex, uint InMeshPassIndex, bool bVoxel, bool bCurve)`
- L412-443 _function_ `uint RemapRasterBin(uint InBinIndex, uint InRenderFlags, FNaniteMaterialFlags MaterialFlags, bool bVoxel, bool bCurve, bool bIsDeforming)`
- L445-452 _function_ `uint TranslateRasterBin(uint RasterBin, uint InRegularRasterBinCount)`
- L454-463 _function_ `template<typename TRasterBinMetaBufferType> FNaniteMaterialFlags GetRasterBinMaterialFlags(TRasterBinMetaBufferType RasterBinMeta, uint BinIndex)`
- L465-492 _function_ `template<typename TRasterBinMetaBufferType> uint GetMaterialRasterBinAndFlagsFromIndex( TRasterBinMetaBufferType RasterBinMeta, FNaniteView NaniteView, uint InRelativeMaterialIndex, uint InPrimitiveIndex, uint InMeshPassIndex, uint InRegularRasterBinCount, bool bFallbackRasterBin, inout FNaniteMaterialFlags MaterialFlags)`
- L494-501 _function_ `float4 GetMaterialUVDensities( FCluster InCluster, uint InPrimitiveIndex, uint InTriIndex)`
- L503-511 _function_ `uint GetMaterialShadingBin( FCluster InCluster, uint InPrimitiveIndex, uint InMeshPassIndex, uint InTriIndex)`
- L513-535 _function_ `template<typename TRasterBinMetaBufferType> uint GetMaterialRasterBinAndFlags( TRasterBinMetaBufferType RasterBinMeta, FNaniteView NaniteView, FCluster InCluster, uint InPrimitiveIndex, uint InMeshPassIndex, uint InTriIndex, uint InRegularSlotCount, bool bFallbackRasterBin, out FNaniteMaterialFlags MaterialFlags)`
- L537-548 _function_ `uint LoadMaterialHitProxyId(uint InPrimitiveIndex, uint InMaterialIndex, ByteAddressBuffer InMaterialHitProxyTable)`
- L550-559 _function_ `uint GetMaterialHitProxyId( FCluster InCluster, uint InPrimitiveIndex, uint InTriIndex, ByteAddressBuffer InMaterialHitProxyTable)`
- L561-565 _function_ `float4 LoadNaniteMaterialOverlayColor(uint InPrimitiveIndex)`
- L567-581 _function_ `float3 UnpackTangentX(float3 TangentZ, uint TangentAngleBits, uint NumTangentBits)`
- L583-603 _function_ `void DecodeVertexBoneInfluence(FBoneInfluenceHeader BoneInfluenceHeader, uint VertIndex, uint InfluenceIndex, inout uint OutBoneIndex, inout float OutBoneWeight)`
- L606-609 _function_ `FClusterBoneInfluence DecodeClusterBoneInfluence(FCluster Cluster, uint InfluenceIndex)` _[#if COMPILER_SUPPORTS_HLSL2021]_
- L612-618 _function_ `FBoneInfluence DecodeBoneInfluence(uint PackedBoneInfluence)`
- L620-624 _function_ `FBoneInfluence DecodeVoxelBoneInfluence(FCluster Cluster, uint InfluenceIndex)`
- L626-630 _function_ `FBoneInfluence DecodeHierarchyAssemblyTransformBoneInfluence(uint BufferOffsetDwords, uint InfluenceIndex)`
- L639-654 _function_ `FNaniteAssemblyBoneInfluenceHeader DecodeHierarchyAssemblyTransformBoneInfluenceHeader(uint TransformBufferOffset, uint NumTransforms, uint TransformIndex)`
- L656-663 _function_ `float3 GetNaniteFallbackTangent(float3 TangentZ)`
- L665-668 _function_ `void DecodeImplicitTangents(inout FNaniteRawAttributeData RawAttributeData[1], float3 Positions[1], FCluster Cluster)`
- L670-722 _function_ `void DecodeImplicitTangents(inout FNaniteRawAttributeData RawAttributeData[3], float3 Positions[3], FCluster Cluster)`
- L725-738 _function_ `void DecodeImplicitTangents(inout FNaniteRawAttributeData RawAttributeData[2], float3 Positions[2], FCluster Cluster)`
- L742-888 _function_ `template<uint N> void GetRawAttributeData(inout FNaniteRawAttributeData RawAttributeData[N], FCluster Cluster, float3 LocalPositions[N], uint3 VertIndices, uint CompileTimeMaxTexCoords )` — Decodes vertex attributes for N vertices. N must be compile-time constant and <= 3. Decoding multiple vertices from the same cluster simultaneously tends to generate better code than decoding them individually.
- L890-894 _function_ `half3x3 NaniteTangentToLocal(float4 TangentXAndSign, float3 UnnormalizedTangentZ)`
- L896-942 _function_ `TDual< float2 > GetTexCoord( FCluster Cluster, uint3 TriIndices, FBarycentrics Barycentrics, uint TexCoordIndex )`
- L951-988 _function_ `template<class ClusterSegmentProcessor> void IterateClusterSegments(FCluster Cluster, ByteAddressBuffer InClusterPageData, inout ClusterSegmentProcessor Processor)` _[#if DEFINE_ITERATE_CLUSTER_SEGMENTS]_

#### Top-level macro invocations (2)

- L67 _macro_call_ `HLSL_STATIC_ASSERT(sizeof(FNaniteTangentBasis) == 28, "Unexpected size of FNaniteTangentBasis. Update WaveReadLaneAt to reflect changes.")`
- L76 _macro_call_ `HLSL_STATIC_ASSERT(sizeof(FNaniteRawAttributeData) == 48 + 8 * NANITE_MAX_UVS, "Unexpected size of FNaniteRawAttributeData. Update WaveReadLaneAt to reflect changes.")`

### `Shaders/Private/Nanite/NaniteClusterCulling.usf` (Private)

- lines: 1153; parse: all-branches
- includes: L21 `NaniteCulling.ush`, L26 `/Platform/Private/NanitePlatformConfig.ush` [defined(OVERRIDE_NANITE_PLATFORM_CONFIG_USH)], L37 `NaniteHierarchyTraversal.ush` [NANITE_HIERARCHY_TRAVERSAL], L41 `../MaterialCache/MaterialCacheCommon.ush` [MATERIAL_CACHE], L47 `../Common.ush`, L48 `../SceneData.ush`, L49 `../ViewData.ush`, L50 `../WaveOpUtil.ush`, L51 `../ComputeShaderUtils.ush`, L53 `../VirtualShadowMaps/VirtualShadowMapPageOverlap.ush` [VIRTUAL_TEXTURE_TARGET], L54 `../VirtualShadowMaps/VirtualShadowMapPageCacheCommon.ush` [VIRTUAL_TEXTURE_TARGET], L56 `NaniteCullingCommon.ush`, L57 `NaniteDataDecode.ush`, L58 `NaniteAttributeDecode.ush`, L59 `NaniteVertexDeformation.ush`, L60 `NaniteHZBCull.ush`, L61 `NaniteStreaming.ush`, L62 `../GPUMessaging.ush`, L64 `../SplineMeshCommon.ush` [USE_SPLINEDEFORM]

#### Macros (#define, 11)

- L10 `#define CULLING_PASS 0` _[#if !defined(CULLING_PASS)]_
- L14 `#define VIRTUAL_TEXTURE_TARGET 0` _[#if !defined(VIRTUAL_TEXTURE_TARGET)]_
- L18 `#define NANITE_HIERARCHY_TRAVERSAL 0` _[#if !defined(NANITE_HIERARCHY_TRAVERSAL)]_
- L24 `#define NANITE_PLATFORM_CULLING_SHADER 1`
- L29 `#define GROUP_NODE_SIZE NANITE_CANDIDATE_NODE_SIZE_DWORDS(CULLING_PASS == CULLING_PASS_OCCLUSION_POST)`
- L33 `#define CHECK_AND_TRIM_CLUSTER_COUNT (CULLING_PASS == CULLING_PASS_OCCLUSION_MAIN \|\| CULLING_PASS == CULLING_PASS_OCCLUSION_POST)`
- L36 `#define NANITE_HIERARCHY_TRAVERSAL_TYPE (CULLING_TYPE)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
- L45 `#define USE_HZB_SHARED_SAMPLERS 0`
- L67 `#define NANITE_DEPTH_BUCKETING NANITE_EXTENDED_VISIBLE_CLUSTERS`
- L80 `#define OPTIONAL_COHERENT(Name) Name##Coherent` _[#if CULLING_TYPE == NANITE_CULLING_TYPE_PERSISTENT_NODES_AND_CLUSTERS]_
- L86 `#define OPTIONAL_COHERENT(Name) Name` _[#if !(CULLING_TYPE == NANITE_CULLING_TYPE_PERSISTENT_NODES_AND_CLUSTERS)]_

#### Entry points (6)

- L968-978 _entry_ `[numthreads(NANITE_PERSISTENT_CLUSTER_CULLING_GROUP_SIZE, 1, 1)] void NodeAndClusterCull(uint GroupID : SV_GroupID, uint GroupIndex : SV_GroupIndex)` — stage: **compute** — C++: `FNodeAndClusterCull_CS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteCullRaster.cpp:1023) _[#if NANITE_HIERARCHY_TRAVERSAL]_
- L988-1035 _entry_ `[numthreads(1, 1, 1)] void CalculateSafeRasterizerArgs()` — stage: **compute** — C++: `FCalculateSafeRasterizerArgs_CS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteCullRaster.cpp:1097)
- L1044-1083 _entry_ `[numthreads(1, 1, 1)] void InitArgs()` — stage: **compute** — C++: `FInitArgs_CS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteCullRaster.cpp:1045)
- L1089-1096 _entry_ `[numthreads(1, 1, 1)] void InitClusterCullArgs()` — stage: **compute** — C++: `FInitClusterCullArgs_CS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteCullRaster.cpp:1059)
- L1101-1131 _entry_ `[numthreads(NANITE_MAX_CLUSTER_HIERARCHY_DEPTH + 1, 1, 1)] void InitNodeCullArgs(uint GroupID : SV_GroupID, uint GroupIndex : SV_GroupIndex)` — stage: **compute** — C++: `FInitNodeCullArgs_CS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteCullRaster.cpp:1074)
- L1137-1151 _entry_ `[numthreads(1, 1, 1)] void FeedbackStatus()` — stage: **compute** — C++: `FNaniteFeedbackStatusCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteCullRaster.cpp:7506)

#### Structs / classes (1)

- L355-966 _struct_ **`FNaniteTraversalClusterCullCallback`** `struct FNaniteTraversalClusterCullCallback` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L357 _member_ `uint ChildIndex;` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L358 _member_ `uint LocalNodeIndex;` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L360 _member_ `FCandidateNode CandidateNode;` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L361 _member_ `FNaniteView NaniteView;` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L362 _member_ `FInstanceSceneData InstanceData;` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L363 _member_ `uint AssemblyTransformIndex;` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L365 _member_ `bool bVisible;` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L367 _member_ `float StreamingPriority;` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L369 _method_ `void Init(uint InChildIndex, uint InLocalNodeIndex, uint GroupNodeFetchIndex)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L385 _method_ `uint GetHierarchyNodeOffset()` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L390 _method_ `bool ShouldVisitChild(FHierarchyNodeSlice HierarchyNodeSlice, bool bInVisible)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L569 _method_ `void OnPreProcessNodeBatch(uint GroupIndex)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L579 _method_ `void OnPostNodeVisit(FHierarchyNodeSlice HierarchyNodeSlice)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L609 _method_ `void StoreChildNode(uint StoreIndex, FHierarchyNodeSlice HierarchyNodeSlice)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L622 _method_ `void StoreCluster(uint StoreIndex, FHierarchyNodeSlice HierarchyNodeSlice, uint ClusterIndex)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L638 _method_ `uint4 LoadPackedCluster(uint CandidateIndex)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L645 _method_ `bool IsNodeDataReady(uint4 RawData)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L650 _method_ `bool LoadCandidateNodeDataToGroup(uint NodeIndex, uint GroupIndex, bool bCheckIfReady = true)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L663 _method_ `void ClearCandidateNodeData(uint NodeIndex)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L669 _method_ `void AddToClusterBatch(uint BatchIndex, uint Num)` _[#if NANITE_HIERARCHY_TRAVERSAL && CULLING_TYPE == NANITE_CULLING_TYPE_PERSISTENT_NODES_AND_CLUSTERS]_
  - L675 _method_ `void ClearClusterBatch(uint BatchIndex)` _[#if NANITE_HIERARCHY_TRAVERSAL && CULLING_TYPE == NANITE_CULLING_TYPE_PERSISTENT_NODES_AND_CLUSTERS]_
  - L681 _method_ `uint LoadClusterBatch(uint BatchIndex)` _[#if NANITE_HIERARCHY_TRAVERSAL && CULLING_TYPE == NANITE_CULLING_TYPE_PERSISTENT_NODES_AND_CLUSTERS]_
  - L688 _method_ `void EmitVisibleCluster(bool bUseHWRaster, uint2 TotalPrevDrawClusters, uint HWClusterCounterIndex, FVisibleCluster VisibleCluster)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L722 _method_ `MAX_OCCUPANCY DISABLE_TARGET_OCCUPANCY_WARNING void ProcessCluster(uint4 PackedCluster)` _[#if NANITE_HIERARCHY_TRAVERSAL]_

#### Global resources (textures / buffers / samplers) (24)

- L87 _resource_ `RWByteAddressBuffer CandidateNodes;` _[#if !(CULLING_TYPE == NANITE_CULLING_TYPE_PERSISTENT_NODES_AND_CLUSTERS)]_
- L88 _resource_ `RWByteAddressBuffer CandidateClusters;` _[#if !(CULLING_TYPE == NANITE_CULLING_TYPE_PERSISTENT_NODES_AND_CLUSTERS)]_
- L89 _resource_ `RWByteAddressBuffer InOutAssemblyTransforms;` _[#if !(CULLING_TYPE == NANITE_CULLING_TYPE_PERSISTENT_NODES_AND_CLUSTERS)]_
- L92 _resource_ `Buffer<uint> OffsetClustersArgsSWHW;`
- L93 _resource_ `StructuredBuffer<uint2> InTotalPrevDrawClusters;`
- L95 _resource_ `RWStructuredBuffer<FStreamingRequest> OutStreamingRequests;` — First entry holds count
- L97 _resource_ `RWByteAddressBuffer OutVisibleClustersSWHW;`
- L98 _resource_ `RWBuffer<uint> VisibleClustersArgsSWHW;`
- L101 _resource_ `RWStructuredBuffer<FNaniteStats> OutStatsBuffer;` _[#if DEBUG_FLAGS]_
- L102 _resource_ `RWByteAddressBuffer OutDebugBuffer;` _[#if DEBUG_FLAGS]_
- L983 _resource_ `Buffer<uint> InRasterizerArgsSWHW;` — Make sure the indirect args we give to the rasterizer are not out of bounds and that the SW/HW ranges are not overlapping.
- L984 _resource_ `RWBuffer<uint> OutSafeRasterizerArgsSWHW;`
- L985 _resource_ `RWStructuredBuffer<uint2> OutClusterCountSWHW;`
- L986 _resource_ `RWBuffer<uint> OutClusterClassifyArgs;`
- L1037 _resource_ `RWBuffer< uint > OutOccludedInstancesArgs;`
- L1039 _resource_ `RWStructuredBuffer<FQueueState> OutQueueState;`
- L1040 _resource_ `RWStructuredBuffer< uint2 > InOutTotalPrevDrawClusters;`
- L1041 _resource_ `RWBuffer< uint > InOutMainPassRasterizeArgsSWHW;`
- L1042 _resource_ `RWBuffer< uint > InOutPostPassRasterizeArgsSWHW;`
- L1087 _resource_ `RWBuffer< uint > OutClusterCullArgs;`
- L1098 _resource_ `RWBuffer< uint > OutNodeCullArgs0;`
- L1099 _resource_ `RWBuffer< uint > OutNodeCullArgs1;`
- L1133 _resource_ `Buffer<uint> InMainRasterizerArgsSWHW;`
- L1134 _resource_ `Buffer<uint> InPostRasterizerArgsSWHW;`

#### Global parameters (uniforms) (10)

- L81 _parameter_ `RWCoherentByteAddressBuffer CandidateNodes;` _[#if CULLING_TYPE == NANITE_CULLING_TYPE_PERSISTENT_NODES_AND_CLUSTERS]_
- L82 _parameter_ `RWCoherentByteAddressBuffer CandidateClusters;` _[#if CULLING_TYPE == NANITE_CULLING_TYPE_PERSISTENT_NODES_AND_CLUSTERS]_
- L83 _parameter_ `RWCoherentByteAddressBuffer ClusterBatches;` _[#if CULLING_TYPE == NANITE_CULLING_TYPE_PERSISTENT_NODES_AND_CLUSTERS]_
- L84 _parameter_ `RWCoherentByteAddressBuffer InOutAssemblyTransforms;` _[#if CULLING_TYPE == NANITE_CULLING_TYPE_PERSISTENT_NODES_AND_CLUSTERS]_
- L105 _parameter_ `uint MaxAssemblyTransforms;`
- L106 _parameter_ `uint LargePageRectThreshold;`
- L107 _parameter_ `float DepthBucketsMinZ;`
- L108 _parameter_ `float DepthBucketsMaxZ;`
- L1085 _parameter_ `uint InitIsPostPass;`
- L1135 _parameter_ `uint StatusMessageId;`

#### groupshared (1)

- L77 _groupshared_ `groupshared uint GroupOccludedBitmask[NANITE_MAX_BVH_NODES_PER_GROUP];`

#### static const (4)

- L70 _static_const_ `static const bool bIsPostPass = true;` _[#if CULLING_PASS == CULLING_PASS_OCCLUSION_POST]_
- L71 _static_const_ `static const uint QueueStateIndex = 1;` _[#if CULLING_PASS == CULLING_PASS_OCCLUSION_POST]_
- L73 _static_const_ `static const bool bIsPostPass = false;` _[#if !(CULLING_PASS == CULLING_PASS_OCCLUSION_POST)]_
- L74 _static_const_ `static const uint QueueStateIndex = 0;` _[#if !(CULLING_PASS == CULLING_PASS_OCCLUSION_POST)]_

#### Functions (6)

- L110-245 _function_ `void TransformNodeCullingBounds( FNaniteView NaniteView, FPrimitiveSceneData PrimitiveData, FInstanceSceneData InstanceData, FCluster Cluster, FHierarchyNodeSlice HierarchyNodeSlice, bool bCompileTimeCluster, bool bIsAssemblyPart, uint CullingFlags, bool bEnableWPOBoundsExpansion, inout FNodeCullingBounds Bounds )`
- L248-256 _function_ `uint GetInclusiveRectArea(uint4 Rect)` — Get the area of an "inclusive" rect (which means that the max is inside the rect), also guards against negative area (where min > max)
- L258-285 _function_ `bool ShouldVisitChildInternal( FNaniteView NaniteView, FInstanceSceneData InstanceData, FInstanceDynamicData DynamicData, FNodeCullingBounds Bounds, FHierarchyNodeSlice HierarchyNodeSlice, inout float Priority )`
- L287-312 _function_ `bool SmallEnoughToDraw( FNaniteView NaniteView, FInstanceSceneData InstanceData, FInstanceDynamicData DynamicData, FNodeCullingBounds Bounds, float LODError, float EdgeLength, inout bool bUseHWRaster )`
- L314-327 _function_ `uint DepthToBucket(float Z)`
- L329-348 _function_ `float4x4 LoadAssemblyTransform(uint TransformIndex)`

### `Shaders/Private/Nanite/NaniteClusterRayTracing.usf` (Private)

- lines: 1156; parse: all-branches
- includes: L3 `/Engine/Shared/NaniteDefinitions.h`, L4 `/Engine/Shared/NaniteRayTracingDefinitions.h`, L15 `NaniteHierarchyTraversal.ush` [NANITE_HIERARCHY_TRAVERSAL], L19 `../Common.ush`, L20 `../ShaderPrint.ush`, L21 `../ColorMap.ush`, L22 `../WaveOpUtil.ush`, L23 `../ComputeShaderUtils.ush`, L25 `NaniteDataDecode.ush`, L26 `NaniteAttributeDecode.ush`, L27 `NaniteCulling.ush`, L28 `NaniteCullingCommon.ush`, L29 `NaniteStreaming.ush`, L30 `NaniteClusterRayTracingStats.ush`

#### Macros (#define, 5)

- L7 `#define NANITE_HIERARCHY_TRAVERSAL 0` _[#if !defined(NANITE_HIERARCHY_TRAVERSAL)]_
- L12 `#define NANITE_HIERARCHY_TRAVERSAL_TYPE (CULLING_TYPE)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
- L13 `#define GROUP_NODE_SIZE 3` _[#if NANITE_HIERARCHY_TRAVERSAL]_
- L33 `#define NANITE_RAYTRACING_AS_UNUSED_INDEX ((~0U))`
- L34 `#define NANITE_RAYTRACING_AS_CACHE_HIT_INDEX ((~0U)-1U)`

#### Entry points (10)

- L349-357 _entry_ `[numthreads(NANITE_PERSISTENT_CLUSTER_CULLING_GROUP_SIZE, 1, 1)] void HierarchyTraversalCS(uint GroupID : SV_GroupID, uint GroupIndex : SV_GroupIndex)` — stage: **compute** — C++: `FNaniteRayTracingGeometryClusterCutTraversalCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteRayTracing.cpp:711) _[#if NANITE_HIERARCHY_TRAVERSAL]_
- L397-484 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void InitQueueCS(uint GroupIndex : SV_GroupIndex, uint3 GroupId : SV_GroupID)` — stage: **compute** — C++: `FRayTracingGeometryClusterCutInitQueueCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteRayTracing.cpp:650) _[#if defined(InitQueueCS)]_
- L501-593 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void StreamOutClusterCS(uint GroupIndex : SV_GroupIndex, uint3 GroupId : SV_GroupID)` — stage: **compute** — C++: `FNaniteRayTracingStreamOutClusterCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteRayTracing.cpp:436) _[#if defined(StreamOutClusterCS)]_
- L622-735 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void AllocateClusterCS(uint GroupIndex : SV_GroupIndex, uint3 GroupId : SV_GroupID)` — stage: **compute** — C++: `FNaniteRayTracingAllocateClusterCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteRayTracing.cpp:553) _[#if defined(AllocateClusterCS) \|\| defined(FreeClusterCS)]_
- L740-784 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void FreeClusterCS(uint GroupIndex : SV_GroupIndex, uint3 GroupId : SV_GroupID)` — stage: **compute** — C++: `FNaniteRayTracingFreeClusterCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteRayTracing.cpp:598) _[#if defined(AllocateClusterCS) \|\| defined(FreeClusterCS)]_
- L809-901 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void AllocateBLASCS(uint GroupIndex : SV_GroupIndex, uint3 GroupId : SV_GroupID)` — stage: **compute** — C++: `FNaniteRayTracingAllocateBLASCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteRayTracing.cpp:765) _[#if defined(AllocateBLASCS)]_
- L910-924 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void ResetAllocatorCS(uint GroupIndex : SV_GroupIndex, uint3 GroupId : SV_GroupID)` — stage: **compute** — C++: `FNaniteRayTracingResetAllocatorCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteRayTracing.cpp:470) _[#if defined(ResetAllocatorCS)]_
- L933-938 _entry_ `[numthreads(1, 1, 1)] void ClampAllocatorCS(uint GroupIndex : SV_GroupIndex, uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FNaniteRayTracingClampAllocatorCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteRayTracing.cpp:500) _[#if defined(ClampAllocatorCS)]_
- L953-982 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void DebugHistogramCS(uint GroupIndex : SV_GroupIndex, uint3 GroupId : SV_GroupID)` — stage: **compute** — C++: `FNaniteRayTracingDebugHistogramCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteRayTracing.cpp:853) _[#if defined(DebugHistogramCS)]_
- L1019-1153 _entry_ `[numthreads(1, 1, 1)] void DebugCS(uint GroupIndex : SV_GroupIndex, uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FNaniteRayTracingDebugCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteRayTracing.cpp:813) _[#if defined(DebugCS)]_

#### Structs / classes (3)

- L44-50 _struct_ **`FCandidateCluster`** `struct FCandidateCluster`
  - L46 _member_ `uint PageIndex;`
  - L47 _member_ `uint ClusterIndex;`
  - L48 _member_ `uint RequestIndex;`
  - L49 _member_ `uint AssemblyTransformIndex;`
- L76-81 _struct_ **`FCandidateNodeRT`** `struct FCandidateNodeRT`
  - L78 _member_ `uint NodeIndex;`
  - L79 _member_ `uint RequestIndex;`
  - L80 _member_ `uint AssemblyTransformIndex;`
- L172-347 _struct_ **`FTraversalCallback`** `struct FTraversalCallback` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L174 _member_ `FCandidateNodeRT CandidateNode;` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L176 _member_ `FGeometryClusterCutRequest RequestData;` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L178 _member_ `uint AssemblyTransformIndex;` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L180 _method_ `void Init(uint InChildIndex, uint InLocalNodeIndex, uint GroupNodeFetchIndex)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L191 _method_ `uint GetHierarchyNodeOffset()` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L196 _method_ `bool ShouldVisitChild(FHierarchyNodeSlice HierarchyNodeSlice, bool bInVisible)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L230 _method_ `void OnPreProcessNodeBatch(uint GroupIndex)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L235 _method_ `void OnPostNodeVisit(FHierarchyNodeSlice HierarchyNodeSlice)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L240 _method_ `void StoreChildNode(uint StoreIndex, FHierarchyNodeSlice HierarchyNodeSlice)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L250 _method_ `void StoreCluster(uint StoreIndex, FHierarchyNodeSlice HierarchyNodeSlice, uint ClusterIndex)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L261 _method_ `uint4 LoadPackedCluster(uint CandidateIndex)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L267 _method_ `bool IsNodeDataReady(uint4 RawData)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L272 _method_ `bool LoadCandidateNodeDataToGroup(uint NodeIndex, uint GroupIndex, bool bCheckIfReady = true)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L285 _method_ `void ClearCandidateNodeData(uint NodeIndex)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L290 _method_ `void AddToClusterBatch(uint BatchIndex, uint Num)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L295 _method_ `void ClearClusterBatch(uint BatchIndex)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L300 _method_ `uint LoadClusterBatch(uint BatchIndex)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L306 _method_ `void ProcessCluster(uint4 PackedCluster)` _[#if NANITE_HIERARCHY_TRAVERSAL]_

#### Global resources (textures / buffers / samplers) (57)

- L36 _resource_ `StructuredBuffer<FClusterStreamOutRequest> StreamOutRequests;`
- L39 _resource_ `StructuredBuffer<FGeometryClusterCutRequest> CutRequests;`
- L160 _resource_ `RWByteAddressBuffer Nodes;` _[#if NANITE_HIERARCHY_TRAVERSAL]_
- L161 _resource_ `RWByteAddressBuffer CandidateClusters;` _[#if NANITE_HIERARCHY_TRAVERSAL]_
- L163 _resource_ `RWStructuredBuffer<RAYTRACING_CLUSTER_OPS_BUILD_BLAS_DESC> RWBLASBuildDescs;` _[#if NANITE_HIERARCHY_TRAVERSAL]_
- L164 _resource_ `RWStructuredBuffer<GPU_VIRTUAL_ADDRESS> RWCLASAddresses;` _[#if NANITE_HIERARCHY_TRAVERSAL]_
- L166 _resource_ `ByteAddressBuffer PageDataBuffer;` _[#if NANITE_HIERARCHY_TRAVERSAL]_
- L167 _resource_ `ByteAddressBuffer CLASDataBuffer;` _[#if NANITE_HIERARCHY_TRAVERSAL]_
- L168 _resource_ `ByteAddressBuffer BLASDataBuffer;` _[#if NANITE_HIERARCHY_TRAVERSAL]_
- L169 _resource_ `StructuredBuffer<uint> ReferenceErrors;` _[#if NANITE_HIERARCHY_TRAVERSAL]_
- L363 _resource_ `RWStructuredBuffer<FQueueState> QueueState;` _[#if defined(InitQueueCS)]_
- L364 _resource_ `RWByteAddressBuffer Nodes;` _[#if defined(InitQueueCS)]_
- L366 _resource_ `StructuredBuffer<GPU_VIRTUAL_ADDRESS> ResourceAddressesBuffer;` _[#if defined(InitQueueCS)]_
- L367 _resource_ `RWStructuredBuffer<RAYTRACING_CLUSTER_OPS_BUILD_BLAS_DESC> RWBLASBuildBuffer;` _[#if defined(InitQueueCS)]_
- L369 _resource_ `StructuredBuffer<FNaniteRayTracingASCacheEntry> BLASCacheAllocationTable;` _[#if defined(InitQueueCS)]_
- L370 _resource_ `RWStructuredBuffer<FNaniteRayTracingASCacheMetadata> RWBLASCacheMetadata;` _[#if defined(InitQueueCS)]_
- L371 _resource_ `StructuredBuffer<uint> ReferenceErrors;` _[#if defined(InitQueueCS)]_
- L374 _resource_ `RWByteAddressBuffer RWBLASData;` _[#if defined(InitQueueCS)]_
- L375 _resource_ `RWStructuredBuffer<uint> RWBLASCountBuffer;` _[#if defined(InitQueueCS)]_
- L490 _resource_ `StructuredBuffer<GPU_VIRTUAL_ADDRESS> ResourceAddresses;` _[#if defined(StreamOutClusterCS)]_
- L492 _resource_ `ByteAddressBuffer SegmentMappingBuffer;` _[#if defined(StreamOutClusterCS)]_
- L494 _resource_ `RWByteAddressBuffer RWVertexBuffer;` _[#if defined(StreamOutClusterCS)]_
- L495 _resource_ `RWByteAddressBuffer RWIndexBuffer;` _[#if defined(StreamOutClusterCS)]_
- L496 _resource_ `RWByteAddressBuffer RWGeometryIndexAndFlagsBuffer;` _[#if defined(StreamOutClusterCS)]_
- L498 _resource_ `RWStructuredBuffer<uint> RWClusterCount;` _[#if defined(StreamOutClusterCS)]_
- L499 _resource_ `RWStructuredBuffer<RAYTRACING_CLUSTER_OPS_BUILD_CLAS_DESC> RWCLASBuildDescs;` _[#if defined(StreamOutClusterCS)]_
- L599 _resource_ `StructuredBuffer<uint> CLASSizes;` _[#if defined(AllocateClusterCS) \|\| defined(FreeClusterCS)]_
- L600 _resource_ `StructuredBuffer<GPU_VIRTUAL_ADDRESS> CLASAddresses;` _[#if defined(AllocateClusterCS) \|\| defined(FreeClusterCS)]_
- L603 _resource_ `RWStructuredBuffer<int> RWAllocator;` _[#if defined(AllocateClusterCS) \|\| defined(FreeClusterCS)]_
- L610 _resource_ `StructuredBuffer<GPU_VIRTUAL_ADDRESS> ResourceAddresses;` _[#if defined(AllocateClusterCS) \|\| defined(FreeClusterCS)]_
- L612 _resource_ `RWStructuredBuffer<uint> RWMoveCount;` _[#if defined(AllocateClusterCS) \|\| defined(FreeClusterCS)]_
- L613 _resource_ `RWStructuredBuffer<GPU_VIRTUAL_ADDRESS> RWSrcAddresses;` _[#if defined(AllocateClusterCS) \|\| defined(FreeClusterCS)]_
- L614 _resource_ `RWStructuredBuffer<GPU_VIRTUAL_ADDRESS> RWDstAddresses;` _[#if defined(AllocateClusterCS) \|\| defined(FreeClusterCS)]_
- L616 _resource_ `RWByteAddressBuffer RWPageDataBuffer;` _[#if defined(AllocateClusterCS) \|\| defined(FreeClusterCS)]_
- L617 _resource_ `RWByteAddressBuffer RWCLASData;` _[#if defined(AllocateClusterCS) \|\| defined(FreeClusterCS)]_
- L619 _resource_ `StructuredBuffer<FAllocateClustersRequest> AllocateClustersRequests;` _[#if defined(AllocateClusterCS) \|\| defined(FreeClusterCS)]_
- L737 _resource_ `StructuredBuffer<FFreeClustersRequest> FreeClustersRequests;` _[#if defined(AllocateClusterCS) \|\| defined(FreeClusterCS)]_
- L790 _resource_ `StructuredBuffer<uint> BLASSizes;` _[#if defined(AllocateBLASCS)]_
- L791 _resource_ `StructuredBuffer<GPU_VIRTUAL_ADDRESS> BLASAddresses;` _[#if defined(AllocateBLASCS)]_
- L796 _resource_ `StructuredBuffer<GPU_VIRTUAL_ADDRESS> ResourceAddresses;` _[#if defined(AllocateBLASCS)]_
- L798 _resource_ `RWStructuredBuffer<uint> RWMoveCount;` _[#if defined(AllocateBLASCS)]_
- L799 _resource_ `RWStructuredBuffer<GPU_VIRTUAL_ADDRESS> RWSrcAddresses;` _[#if defined(AllocateBLASCS)]_
- L800 _resource_ `RWStructuredBuffer<GPU_VIRTUAL_ADDRESS> RWDstAddresses;` _[#if defined(AllocateBLASCS)]_
- L802 _resource_ `RWByteAddressBuffer RWBLASCacheRequest;` _[#if defined(AllocateBLASCS)]_
- L803 _resource_ `RWByteAddressBuffer RWBLASData;` _[#if defined(AllocateBLASCS)]_
- L805 _resource_ `StructuredBuffer<FNaniteRayTracingASCacheEntry> BLASCacheAllocationTable;` _[#if defined(AllocateBLASCS)]_
- L806 _resource_ `RWStructuredBuffer<FNaniteRayTracingASCacheMetadata> RWBLASCacheMetadata;` _[#if defined(AllocateBLASCS)]_
- L907 _resource_ `RWStructuredBuffer<int> RWAllocator;` _[#if defined(ResetAllocatorCS)]_
- L930 _resource_ `RWStructuredBuffer<int> RWAllocator;` _[#if defined(ClampAllocatorCS)]_
- L944 _resource_ `ByteAddressBuffer ASDataBuffer;` _[#if defined(DebugHistogramCS)]_
- L947 _resource_ `RWStructuredBuffer<uint> RWHistogram;` _[#if defined(DebugHistogramCS)]_
- L951 _resource_ `RWStructuredBuffer<uint> RWSizeSum;` _[#if defined(DebugHistogramCS)]_
- L995 _resource_ `StructuredBuffer<int> CLASAllocator;` _[#if defined(DebugCS)]_
- L996 _resource_ `StructuredBuffer<uint> CLASHistogram;` _[#if defined(DebugCS)]_
- L997 _resource_ `StructuredBuffer<uint> CLASSizeSum;` _[#if defined(DebugCS)]_
- L1003 _resource_ `StructuredBuffer<uint> BLASHistogram;` _[#if defined(DebugCS)]_
- L1005 _resource_ `StructuredBuffer<uint> StatsBuffer;` _[#if defined(DebugCS)]_

#### Global parameters (uniforms) (29)

- L37 _parameter_ `uint NumStreamOutRequests;`
- L40 _parameter_ `uint NumCutRequests;`
- L42 _parameter_ `float MinCutError;`
- L170 _parameter_ `uint UseReferenceErrors;` _[#if NANITE_HIERARCHY_TRAVERSAL]_
- L372 _parameter_ `uint BLASCacheEnabled;` _[#if defined(InitQueueCS)]_
- L373 _parameter_ `float CacheRelativeErrorTolerance;` _[#if defined(InitQueueCS)]_
- L601 _parameter_ `uint NumCLAS;` _[#if defined(AllocateClusterCS) \|\| defined(FreeClusterCS)]_
- L604 _parameter_ `uint AllocationSize;` _[#if defined(AllocateClusterCS) \|\| defined(FreeClusterCS)]_
- L605 _parameter_ `uint PoolSize;` _[#if defined(AllocateClusterCS) \|\| defined(FreeClusterCS)]_
- L606 _parameter_ `uint CLASBufferSize;` _[#if defined(AllocateClusterCS) \|\| defined(FreeClusterCS)]_
- L608 _parameter_ `uint CLASAlignment;` _[#if defined(AllocateClusterCS) \|\| defined(FreeClusterCS)]_
- L620 _parameter_ `uint NumAllocateClustersRequests;` _[#if defined(AllocateClusterCS) \|\| defined(FreeClusterCS)]_
- L738 _parameter_ `uint NumFreeClustersRequests;` _[#if defined(AllocateClusterCS) \|\| defined(FreeClusterCS)]_
- L792 _parameter_ `uint NumBLAS;` _[#if defined(AllocateBLASCS)]_
- L794 _parameter_ `uint BLASAlignment;` _[#if defined(AllocateBLASCS)]_
- L807 _parameter_ `uint BLASCacheEnabled;` _[#if defined(AllocateBLASCS)]_
- L908 _parameter_ `uint PoolSize;` _[#if defined(ResetAllocatorCS)]_
- L931 _parameter_ `uint PoolSize;` _[#if defined(ClampAllocatorCS)]_
- L945 _parameter_ `uint NumAS;` _[#if defined(DebugHistogramCS)]_
- L948 _parameter_ `float2 HistogramScaleBias;` _[#if defined(DebugHistogramCS)]_
- L949 _parameter_ `uint HistogramSize;` _[#if defined(DebugHistogramCS)]_
- L989 _parameter_ `uint CLASBufferSize;` _[#if defined(DebugCS)]_
- L990 _parameter_ `uint NumCLAS;` _[#if defined(DebugCS)]_
- L992 _parameter_ `uint CLASPoolAllocationSize;` _[#if defined(DebugCS)]_
- L993 _parameter_ `uint CLASPoolSize;` _[#if defined(DebugCS)]_
- L999 _parameter_ `uint BLASCacheBufferSize;` _[#if defined(DebugCS)]_
- L1000 _parameter_ `uint BLASStagingBufferSize;` _[#if defined(DebugCS)]_
- L1001 _parameter_ `uint NumBLAS;` _[#if defined(DebugCS)]_
- L1007 _parameter_ `uint ShowHistograms;` _[#if defined(DebugCS)]_

#### Functions (16)

- L52-61 _function_ `uint4 PackCandidateClusterRT(uint ClusterIdx, FCandidateCluster CandidateCluster)`
- L63-74 _function_ `FCandidateCluster UnpackCandidateClusterRT(uint4 RawData)`
- L83-96 _function_ `uint4 PackCandidateNodeRT(FCandidateNodeRT Node)`
- L98-106 _function_ `FCandidateNodeRT UnpackCandidateNodeRT(uint4 RawData)`
- L108 _function_ `uint GetCandidateNodeSizeRT()`
- L109 _function_ `uint GetCandidateClusterSizeRT()`
- L111-115 _function_ `FCandidateCluster LoadCandidateClusterRT(ByteAddressBuffer CandidateClusters, uint ClusterIndex)`
- L117-120 _function_ `void StorePackedCandidateClusterRT(RWByteAddressBuffer CandidateClusters, uint ClusterIndex, uint4 PackedCluster)`
- L122-126 _function_ `void StoreCandidateClusterNoCheckRT(RWByteAddressBuffer CandidateClusters, uint ClusterIndex, FCandidateCluster CandidateCluster)`
- L128-132 _function_ `void StoreCandidateClusterRT(RWByteAddressBuffer CandidateClusters, uint ClusterIndex, FCandidateCluster CandidateCluster)`
- L134-138 _function_ `uint4 LoadCandidateNodeDataRT(RWByteAddressBuffer InNodes, uint NodeIndex)`
- L140-144 _function_ `void StoreCandidateNodeDataRT(RWByteAddressBuffer InNodes, uint NodeIndex, uint4 RawData)`
- L146-150 _function_ `void StoreCandidateNodeRT(RWByteAddressBuffer InNodes, uint NodeIndex, FCandidateNodeRT Node)`
- L152-156 _function_ `void ClearCandidateNodeRT(RWByteAddressBuffer InNodes, uint NodeIndex)`
- L377-395 _function_ `bool IsBLASCacheHit( FNaniteRayTracingASCacheEntry CacheEntry, FNaniteRayTracingASCacheMetadata Metadata, float ReferenceError, float RelativeErrorTolerance)` _[#if defined(InitQueueCS)]_
- L1009-1017 _function_ `void PrintSizeMBAndPercent(inout FShaderPrintContext Context, float SizeBytes, float BufferSizeBytes)` _[#if defined(DebugCS)]_

### `Shaders/Private/Nanite/NaniteClusterRayTracingStats.ush` (Private)

- lines: 42; parse: all-branches
- includes: L3 `/Engine/Shared/NaniteRayTracingDefinitions.h`, L5 `../WaveOpUtil.ush`

#### Macros (#define, 1)

- L8 `#define NANITERT_GENERATE_STATS 0` _[#if !defined(NANITERT_GENERATE_STATS)]_

#### Global resources (textures / buffers / samplers) (1)

- L11 _resource_ `RWStructuredBuffer<uint> OutStatsBuffer;`

#### Functions (3)

- L13-21 _function_ `void StatsBufferWrite(uint Index, uint Value, bool bWriteEnabled = true)`
- L23-31 _function_ `void StatsBufferInterlockedAdd(uint Index, uint Value, bool bWriteEnabled = true)`
- L33-41 _function_ `void StatsBufferInterlockedInc(uint Index, bool bWriteEnabled = true)`

### `Shaders/Private/Nanite/NaniteCulling.ush` (Private)

- lines: 160; parse: all-branches
- includes: L5 `../Common.ush`, L6 `NaniteDataDecode.ush`, L7 `NaniteHierarchyTraversalCommon.ush`

#### Macros (#define, 8)

- L9 `#define CULLING_PASS_NO_OCCLUSION 0`
- L10 `#define CULLING_PASS_OCCLUSION_MAIN 1`
- L11 `#define CULLING_PASS_OCCLUSION_POST 2`
- L12 `#define CULLING_PASS_EXPLICIT_LIST 3`
- L26 `#define NANITE_CANDIDATE_NODE_SIZE_DWORDS(IS_POSTPASS) ((IS_POSTPASS) ? 4u : 3u)` _[#if NANITE_ASSEMBLY_DATA]_
- L28 `#define NANITE_CANDIDATE_NODE_SIZE_DWORDS(IS_POSTPASS) ((IS_POSTPASS) ? 3u : 2u)` _[#if !(NANITE_ASSEMBLY_DATA)]_
- L37 `#define STORE_COMPONENTS_FUNCTION(BufferType, FunctionName) void FunctionName(BufferType DataBuffer, uint NumComponents, uint OffsetInBytes, uint Index, uint4 Data) { const uint Address = OffsetInBytes + Index * (NumComponents * 4u); switch (NumComponents) { c ...` (12 lines)
- L52 `#define LOAD_COMPONENTS_FUNCTION(BufferType, FunctionName) uint4 FunctionName(BufferType DataBuffer, uint NumComponents, uint OffsetInBytes, uint Index) { const uint Address = OffsetInBytes + Index * (NumComponents * 4u); switch (NumComponents) { case 1: retu ...` (13 lines)
- L3 #pragma `once`

#### Structs / classes (1)

- L14-22 _struct_ **`FCandidateNode`** `struct FCandidateNode`
  - L16 _member_ `uint Flags;`
  - L17 _member_ `uint ViewId;`
  - L18 _member_ `uint InstanceId;`
  - L19 _member_ `uint NodeIndex;`
  - L20 _member_ `uint AssemblyTransformIndex;`
  - L21 _member_ `uint EnabledBitmask;`

#### Functions (15)

- L31 _function_ `uint GetCandidateNodeDwords(bool bPostPass)`
- L32 _function_ `uint GetVisibleClusterDwords(bool bHasPageData)`
- L34 _function_ `uint GetCandidateNodesOffset(bool bPostPass)`
- L35 _function_ `uint GetClusterBatchesOffset(bool bPostPass)`
- L68-84 _function_ `uint4 PackCandidateNode(FCandidateNode Node)`
- L86-102 _function_ `FCandidateNode UnpackCandidateNode(uint4 RawData, bool bHasEnabledMask)`
- L105-109 _function_ `uint4 LoadVisibleClusterDataCoherent(RWCoherentByteAddressBuffer DataBuffer, uint ClusterIndex, bool bHasPageData)` — Load/Store/Clear each have globally coherent buffer versions. Fix this with templates.
- L111-115 _function_ `uint4 LoadVisibleClusterData(RWByteAddressBuffer DataBuffer, uint ClusterIndex, bool bHasPageData)`
- L117-121 _function_ `void StoreVisibleClusterCoherent(RWCoherentByteAddressBuffer DataBuffer, uint ClusterIndex, FVisibleCluster VisibleCluster, bool bHasPageData)`
- L123-127 _function_ `void StoreVisibleCluster(RWByteAddressBuffer DataBuffer, uint ClusterIndex, FVisibleCluster VisibleCluster, bool bHasPageData)`
- L131-135 _function_ `void CheckNodeIndexHelper(uint NodeIndex)` — helper function to work around a shader macro expansion issue (incorrect expansion of self-referential macros) that causes, e.g., #define MaxNodes NaniteRaster.MaxNodes, to expand to things like NaniteRaster.NaniteRaster.NaniteRaster.MaxNodes when used as parameter to a macro.
- L137-141 _function_ `uint4 LoadCandidateNodeDataCoherent(RWCoherentByteAddressBuffer DataBuffer, uint NodeIndex, bool bPostPass)`
- L143-147 _function_ `uint4 LoadCandidateNodeData(RWByteAddressBuffer DataBuffer, uint NodeIndex, bool bPostPass)`
- L149-153 _function_ `void StoreCandidateNodeDataCoherent(RWCoherentByteAddressBuffer DataBuffer, uint NodeIndex, uint4 RawData, bool bPostPass)`
- L155-159 _function_ `void StoreCandidateNodeData(RWByteAddressBuffer DataBuffer, uint NodeIndex, uint4 RawData, bool bPostPass)`

#### Top-level macro invocations (4)

- L49 _macro_call_ `STORE_COMPONENTS_FUNCTION(RWCoherentByteAddressBuffer, StoreComponentsCoherent)`
- L50 _macro_call_ `STORE_COMPONENTS_FUNCTION(RWByteAddressBuffer, StoreComponents)`
- L65 _macro_call_ `LOAD_COMPONENTS_FUNCTION(RWCoherentByteAddressBuffer, LoadComponentsCoherent)`
- L66 _macro_call_ `LOAD_COMPONENTS_FUNCTION(RWByteAddressBuffer, LoadComponents)`

### `Shaders/Private/Nanite/NaniteCullingCommon.ush` (Private)

- lines: 676; parse: all-branches
- includes: L5 `../Common.ush`, L8 `../VirtualShadowMaps/VirtualShadowMapPageOverlap.ush` [VIRTUAL_TEXTURE_TARGET], L20 `../SceneData.ush`, L21 `../ViewData.ush`, L22 `NaniteDataDecode.ush`, L23 `NaniteHZBCull.ush`, L24 `NaniteCulling.ush`, L25 `NaniteSceneCommon.ush`

#### Macros (#define, 2)

- L12 `#define CULLING_PASS CULLING_PASS_NO_OCCLUSION` _[#if !defined(CULLING_PASS)]_
- L17 `#define NANITE_CULLING_ENABLE_MIN_RADIUS_CULL 0` _[#if !defined(NANITE_CULLING_ENABLE_MIN_RADIUS_CULL)]_
- L3 #pragma `once`

#### Structs / classes (3)

- L27-41 _struct_ **`FNodeCullingBounds`** `struct FNodeCullingBounds`
  - L29 _member_ `float3 BoxCenter;`
  - L30 _member_ `float3 BoxExtent;`
  - L31 _member_ `float4 Sphere;` — XYZ = Center, W = Radius
  - L39 _member_ `float MeshMinDeformScale;` — These values are the approximate amount of scaling due to deformation (such as spline meshes). This is used when scaling error for culling. One is the smallest average dimension for the whole mesh and is used to scale error, which must necessarily be uniform between a parent node and its children or it's possible the two may not agree on visibility, resulting in missing clusters. The second is the largest deformation dimension for the node, and is used to scale the edge length when determining if the cluster should be rendered in HW or SW, as we can use a more localized value to get more accur
  - L40 _member_ `float NodeMaxDeformScale;`
- L232-676 _struct_ **`FBoxCull`** `struct FBoxCull`
  - L234 _member_ `FNaniteView NaniteView;`
  - L236 _member_ `float3 LocalBoxCenter;`
  - L237 _member_ `float3 LocalBoxExtent;`
  - L239 _member_ `float4 NonUniformScale;`
  - L240 _member_ `float4x4 LocalToTranslatedWorld;`
  - L241 _member_ `float4x4 PrevLocalToTranslatedWorld;`
  - L243 _member_ `bool bIsOrtho;`
  - L244 _member_ `bool bNearClip;`
  - L245 _member_ `bool bViewHZB;`
  - L246 _member_ `bool bDistanceCull;`
  - L247 _member_ `bool bIsViewUncached;`
  - L249 _member_ `bool bSkipCullFrustum;`
  - L250 _member_ `bool bSkipCullHZB;`
  - L251 _member_ `bool bSkipCullGlobalClipPlane;`
  - L252 _member_ `bool bSkipDrawDistance;`
  - L253 _member_ `bool bSkipWPODisableDistance;`
  - L254 _member_ `bool bSkipPixelProgrammableDistance;`
  - L255 _member_ `bool bSkipDisplacementFadeOutDistance;`
  - L257 _member_ `bool bIsVisible;`
  - L258 _member_ `bool bWasOccluded;`
  - L259 _member_ `bool bNeedsClipping;`
  - L260 _member_ `bool bEnableWPO;`
  - L261 _member_ `bool bFallbackRaster;`
  - L262 _member_ `bool bMinScreenRadiusCull;`
  - L265 _member_ `uint PageFlagMask;` _[#if VIRTUAL_TEXTURE_TARGET]_
  - L266 _member_ `bool bDetailGeometry;` _[#if VIRTUAL_TEXTURE_TARGET]_
  - L267 _member_ `uint4 RectPages;` _[#if VIRTUAL_TEXTURE_TARGET]_
  - L270 _member_ `bool bIsStaticGeometry;` — controls which HZB layer is used and whether the DynamicDepthCullRange is used. static HZB is always safe to use but cached static geometry should not use the dynamic HZB or we get incorrect cached pages _[#if VIRTUAL_TEXTURE_TARGET]_
  - L272 _member_ `bool bUseReceiverMask;` — Maps to NANITE_VIEW_FLAG_USE_RECEIVER_MASK, in the future may be driven differently (always on for dynamic paths). _[#if VIRTUAL_TEXTURE_TARGET]_
  - L274 _member_ `float2 DynamicDepthCullRange;` — Extra range used to cull dynamic geometry tighter than static so as to allow using a large depth range to "scrolling" cached pages while tight culling of dynamic geo _[#if VIRTUAL_TEXTURE_TARGET]_
  - L275 _member_ `bool bUsePrefilteredDistantDepthCullRange;` _[#if VIRTUAL_TEXTURE_TARGET]_
  - L278 _method_ `void Init( const FNaniteView InNaniteView, const float3 InLocalBoxCenter, const float3 InLocalBoxExtent, const float4 InNonUniformScale, const float4x4 InLocalToTranslatedWorld, const float4x4 InPrevLocalToTranslatedWorld )`
  - L347 _method_ `void SetupCacheDependentState(bool bInCacheAsStatic, uint InstanceId, uint SceneRendererPrimaryViewId)` _[#if VIRTUAL_TEXTURE_TARGET]_
  - L356 _method_ `void GlobalClipPlane()`
  - L399 _method_ `FDistanceCullSetup ViewDistanceInternal(bool bTestViewDistance)`
  - L414 _method_ `void Distance()` — Only NaniteView.RangeBasedCullingDistance test, useful where there is no primitive available.
  - L427 _method_ `void Distance( FPrimitiveSceneData PrimitiveData )` — Both NaniteView.RangeBasedCullingDistance and draw distance test based on center point as well as ProgrammableRasterDistance
  - L455 _method_ `void DistanceConservative( bool bDrawDistance, float MinDistanceSq, float MaxDistanceSq)` — Both NaniteView.RangeBasedCullingDistance and conservative draw distance test including the radius (as opposed to using the center point). Does not perform the ProgrammableRasterDistance.
  - L470 _method_ `void ProgrammableRasterDistance( FPrimitiveSceneData PrimitiveData )`
  - L480 _method_ `void ProgrammableRasterDistanceInternal( FPrimitiveSceneData PrimitiveData, float3 CenterTranslatedWorld, float Radius, float InstanceDrawDistSq )`
  - L527 _method_ `FFrustumCullData Frustum()`
  - L558 _method_ `bool ScreenSize(float MinScreenSize, float MaxScreenSize)`
  - L595 _method_ `void HZB( FFrustumCullData FrustumCull, bool bClampToPageLevel )`
  - L665 _method_ `void FrustumHZB( bool bClampToPageLevel )`
- L393-397 _struct_ **`FBoxCull::FDistanceCullSetup`** `struct FDistanceCullSetup` — Helper to collect shared data between the different flavors of distance testing. Not moving this data to the parent class as it changes life times, potentially to the detriment of register allocation.
  - L395 _member_ `float3 CenterTranslatedWorld;`
  - L396 _member_ `float Radius;`

#### Functions (8)

- L43-52 _function_ `FNodeCullingBounds InitNodeCullingBounds(FHierarchyNodeSlice HierarchyNodeSlice)`
- L54-62 _function_ `FNodeCullingBounds InitNodeCullingBounds(FInstanceSceneData InstanceData, FCluster Cluster)`
- L65-85 _function_ `FNodeCullingBounds TransformNodeCullingBounds(FNodeCullingBounds Bounds, float4x4 CullingTransform, float4x4 LODTransform)` — TODO: Different name to not be confused with the other TransformNodeCullingBounds
- L87-110 _function_ `FNodeCullingBounds InitNodeCullingBounds(FInstanceSceneData InstanceData, FInstanceViewData InstanceViewData, FVisibleCluster VisibleCluster, FCluster Cluster)`
- L112-159 _function_ `float2 GetProjectedEdgeScales(FNaniteView NaniteView, FInstanceSceneData InstanceData, FInstanceDynamicData DynamicData, float4 Bounds)` — float2(min, max)
- L161-204 _function_ `float2 GetProjectedEdgeScales_Offscreen(FNaniteView NaniteView, FInstanceSceneData InstanceData, FInstanceDynamicData DynamicData, float4 Bounds)` — float2(min, max)
- L206-209 _function_ `float GetGlobalClipPlaneDistance(FNaniteView NaniteView, float3 TranslatedWorldPosition)`
- L211-230 _function_ `void ApplyFirstPersonTransformToBounds(FNaniteView NaniteView, FInstanceSceneData InstanceData, inout float3 BoundsCenter, inout float3 BoundsExtent)`

### `Shaders/Private/Nanite/NaniteCurve.usf` (Private)

- lines: 567; parse: all-branches
- includes: L3 `NaniteCurveCommon.ush`, L4 `../ComputeShaderUtils.ush`, L418 `../BlueNoiseCommon.ush` [defined(CurveTileTranslate)], L419 `NaniteWritePixel.ush` [defined(CurveTileTranslate)], L494 `../ShaderPrint.ush` [defined(CurveTileDebug)], L495 `../ColorMap.ush` [defined(CurveTileDebug)], L496 `NaniteDataDecode.ush` [defined(CurveTileDebug)]

#### Macros (#define, 27)

- L201 `#define DEDUP_METHOD_OFF 0` _[#if defined(CurveTileResolve)]_
- L202 `#define DEDUP_METHOD_BIN 1` _[#if defined(CurveTileResolve)]_
- L203 `#define DEDUP_METHOD_BIN_SM 2` _[#if defined(CurveTileResolve)]_
- L205 `#define DEDUP_METHOD_BLOOM 4` _[#if defined(CurveTileResolve)]_
- L206 `#define DEDUP_METHOD DEDUP_METHOD_BIN_SM` _[#if defined(CurveTileResolve)]_
- L208 `#define DEDUP_BIN_COUNT 32` _[#if defined(CurveTileResolve)]_
- L209 `#define DEDUP_BIN_TYPE half` _[#if defined(CurveTileResolve)]_
- L210 `#define DEDUP_BIN_PACK 1` _[#if defined(CurveTileResolve)]_
- L212 `#define DEDUP_BLOOM_M_BITS 512` _[#if defined(CurveTileResolve)]_
- L213 `#define DEDUP_BLOOM_K_ITER 3` _[#if defined(CurveTileResolve)]_
- L230 `#define USUM_DECLARE(X) groupshared DEDUP_BIN_TYPE X##_DedupBin[DEDUP_BIN_COUNT / DEDUP_BIN_PACK * GROUP_SIZE_X * GROUP_SIZE_Y]` _[#if defined(CurveTileResolve) && DEDUP_METHOD == DEDUP_METHOD_BIN_SM]_
- L231 `#define USUM_INI(X) for (uint X##_i = 0; X##_i < DEDUP_BIN_COUNT; X##_i++) { X##_DedupBin[LocalIndex*DEDUP_BIN_COUNT + X##_i]=0; }` (5 lines) _[#if defined(CurveTileResolve) && DEDUP_METHOD == DEDUP_METHOD_BIN_SM]_
- L236 `#define USUM_ADD(X, Y, I) { uint X##_i = PCGHash(I) & (DEDUP_BIN_COUNT - 1); X##_DedupBin[LocalIndex * DEDUP_BIN_COUNT + X##_i] = max(X##_DedupBin[LocalIndex*DEDUP_BIN_COUNT+ X##_i], (DEDUP_BIN_TYPE)Y); }` (6 lines) _[#if defined(CurveTileResolve) && DEDUP_METHOD == DEDUP_METHOD_BIN_SM]_
- L242 `#define USUM_OUT(X) float X = 0.0; for (uint X##_i = 0; X##_i < DEDUP_BIN_COUNT; X##_i++) { X += X##_DedupBin[LocalIndex*DEDUP_BIN_COUNT+X##_i]; }` (5 lines) _[#if defined(CurveTileResolve) && DEDUP_METHOD == DEDUP_METHOD_BIN_SM]_
- L248 `#define USUM_DECLARE(X) ` _[#if defined(CurveTileResolve) && !(DEDUP_METHOD == DEDUP_METHOD_BIN_SM) && DEDUP_METHOD == DEDUP_METHOD_BIN]_
- L249 `#define USUM_INI(X) static DEDUP_BIN_TYPE X##_DedupBin[DEDUP_BIN_COUNT / DEDUP_BIN_PACK];` _[#if defined(CurveTileResolve) && !(DEDUP_METHOD == DEDUP_METHOD_BIN_SM) && DEDUP_METHOD == DEDUP_METHOD_BIN]_
- L250 `#define USUM_ADD(X, Y, I) { uint X##_i = PCGHash(I) & (DEDUP_BIN_COUNT - 1); X##_DedupBin[X##_i] = max(X##_DedupBin[X##_i], (DEDUP_BIN_TYPE)Y); }` (5 lines) _[#if defined(CurveTileResolve) && !(DEDUP_METHOD == DEDUP_METHOD_BIN_SM) && DEDUP_METHOD == DEDUP_METHOD_BIN]_
- L255 `#define USUM_OUT(X) float X = 0.0; for (uint X##_i = 0; X##_i < DEDUP_BIN_COUNT; X##_i++) { X += X##_DedupBin[X##_i]; }` (5 lines) _[#if defined(CurveTileResolve) && !(DEDUP_METHOD == DEDUP_METHOD_BIN_SM) && DEDUP_METHOD == DEDUP_METHOD_BIN]_
- L261 `#define USUM_DECLARE(X) ` _[#if defined(CurveTileResolve) && !(DEDUP_METHOD == DEDUP_METHOD_BIN_SM) && !(DEDUP_METHOD == DEDUP_METHOD_BIN) && DEDUP_METHOD == DEDUP_METHOD_BLOOM]_
- L262 `#define USUM_INI(X) const uint X##_M = DEDUP_BLOOM_M_BITS; const uint X##_K = DEDUP_BLOOM_K_ITER; static uint X##_Bloom[X##_M / 32]; static FPCGHashOp X##_HashOp; float X = 0.0;` (5 lines) _[#if defined(CurveTileResolve) && !(DEDUP_METHOD == DEDUP_METHOD_BIN_SM) && !(DEDUP_METHOD == DEDUP_METHOD_BIN) && DEDUP_METHOD == DEDUP_METHOD_BLOOM]_
- L267 `#define USUM_ADD(X, Y, I) X = BloomFilter<X##_M, X##_K>(X##_Bloom, I, X##_HashOp) ? max(X, Y) : X + Y;` (2 lines) _[#if defined(CurveTileResolve) && !(DEDUP_METHOD == DEDUP_METHOD_BIN_SM) && !(DEDUP_METHOD == DEDUP_METHOD_BIN) && DEDUP_METHOD == DEDUP_METHOD_BLOOM]_
- L269 `#define USUM_OUT(X) ;` _[#if defined(CurveTileResolve) && !(DEDUP_METHOD == DEDUP_METHOD_BIN_SM) && !(DEDUP_METHOD == DEDUP_METHOD_BIN) && DEDUP_METHOD == DEDUP_METHOD_BLOOM]_
- L271 `#define USUM_DECLARE(X) ` _[#if defined(CurveTileResolve) && !(DEDUP_METHOD == DEDUP_METHOD_BIN_SM) && !(DEDUP_METHOD == DEDUP_METHOD_BIN) && !(DEDUP_METHOD == DEDUP_METHOD_BLOOM)]_
- L272 `#define USUM_INI(X) float X = 0.0;` _[#if defined(CurveTileResolve) && !(DEDUP_METHOD == DEDUP_METHOD_BIN_SM) && !(DEDUP_METHOD == DEDUP_METHOD_BIN) && !(DEDUP_METHOD == DEDUP_METHOD_BLOOM)]_
- L273 `#define USUM_ADD(X, Y, I) X += Y;` _[#if defined(CurveTileResolve) && !(DEDUP_METHOD == DEDUP_METHOD_BIN_SM) && !(DEDUP_METHOD == DEDUP_METHOD_BIN) && !(DEDUP_METHOD == DEDUP_METHOD_BLOOM)]_
- L274 `#define USUM_OUT(X) ;` _[#if defined(CurveTileResolve) && !(DEDUP_METHOD == DEDUP_METHOD_BIN_SM) && !(DEDUP_METHOD == DEDUP_METHOD_BIN) && !(DEDUP_METHOD == DEDUP_METHOD_BLOOM)]_
- L301 `#define Z16 1` _[#if defined(CurveTileResolve)]_

#### Entry points (8)

- L10-29 _entry_ `[numthreads(GROUP_SIZE, 1, 1)] void CurveTileClear( uint3 GroupID : SV_GroupID, uint3 WorldID : SV_DispatchThreadID, uint3 LocalID : SV_GroupThreadID, uint LocalIndex : SV_GroupIndex)` — stage: **compute** _[#if defined(CurveTileClear)]_
- L37-73 _entry_ `[numthreads(GROUP_SIZE, 1, 1)] void CurveTileCountCap( uint3 GroupID : SV_GroupID, uint3 WorldID : SV_DispatchThreadID, uint3 LocalID : SV_GroupThreadID, uint LocalIndex : SV_GroupIndex)` — stage: **compute** _[#if defined(CurveTileCountCap)]_
- L77-89 _entry_ `[numthreads(1, 1, 1)] void CurveTileIndirectArgs( uint3 GroupID : SV_GroupID, uint3 WorldID : SV_DispatchThreadID, uint3 LocalID : SV_GroupThreadID, uint LocalIndex : SV_GroupIndex)` — stage: **compute** _[#if defined(CurveTileIndirectArgs)]_
- L95-152 _entry_ `[numthreads(GROUP_SIZE, 1, 1)] void CurveTileOffsetScan( uint3 GroupID : SV_GroupID, uint3 WorldID : SV_DispatchThreadID, uint3 LocalID : SV_GroupThreadID, uint LocalIndex : SV_GroupIndex)` — stage: **compute** _[#if defined(CurveTileOffsetScan)]_
- L158-190 _entry_ `[numthreads(GROUP_SIZE, 1, 1)] void CurveTileOffsetMerge( uint3 GroupID : SV_GroupID, uint3 WorldID : SV_DispatchThreadID, uint3 LocalID : SV_GroupThreadID, uint LocalIndex : SV_GroupIndex)` — stage: **compute** _[#if defined(CurveTileOffsetMerge)]_
- L279-414 _entry_ `[numthreads(GROUP_SIZE_X, GROUP_SIZE_Y, 1)] void CurveTileResolve( uint3 GroupID : SV_GroupID, uint3 WorldID : SV_DispatchThreadID, uint3 LocalID : SV_GroupThreadID, uint LocalIndex : SV_GroupIndex)` — stage: **compute** _[#if defined(CurveTileResolve)]_
- L421-487 _entry_ `[numthreads(GROUP_SIZE_X, GROUP_SIZE_Y, 1)] void CurveTileTranslate( uint3 GroupID : SV_GroupID, uint3 WorldID : SV_DispatchThreadID, uint3 LocalID : SV_GroupThreadID, uint LocalIndex : SV_GroupIndex)` — stage: **compute** _[#if defined(CurveTileTranslate)]_
- L498-565 _entry_ `[numthreads(GROUP_SIZE_X, GROUP_SIZE_Y, 1)] void CurveTileDebug( uint3 GroupID : SV_GroupID, uint3 WorldID : SV_DispatchThreadID, uint3 LocalID : SV_GroupThreadID, uint LocalIndex : SV_GroupIndex)` — stage: **compute** _[#if defined(CurveTileDebug)]_

#### groupshared (2)

- L93 _groupshared_ `groupshared uint GroupWaveAdd[128];` _[#if defined(CurveTileOffsetScan)]_
- L156 _groupshared_ `groupshared uint GroupAdd;` _[#if defined(CurveTileOffsetMerge)]_

#### Top-level macro invocations (1)

- L277 _macro_call_ `USUM_DECLARE(W)` _[#if defined(CurveTileResolve)]_

#### C++ shader bindings (IMPLEMENT_* naming this file, 8)

- `SF_Compute` → entry not found in file (macro-generated or #include'd); C++ `FNaniteCurveCommonParameters` SF_Compute via IMPLEMENT_GLOBAL_SHADER_STRUCT (Source/Runtime/Renderer/Private/Nanite/NaniteCurveRaster.inl:275)
- `SF_Compute` → entry not found in file (macro-generated or #include'd); C++ `FNaniteCurveCommonParameters` SF_Compute via IMPLEMENT_GLOBAL_SHADER_STRUCT (Source/Runtime/Renderer/Private/Nanite/NaniteCurveRaster.inl:276)
- `SF_Compute` → entry not found in file (macro-generated or #include'd); C++ `FNaniteCurveCommonParameters` SF_Compute via IMPLEMENT_GLOBAL_SHADER_STRUCT (Source/Runtime/Renderer/Private/Nanite/NaniteCurveRaster.inl:277)
- `SF_Compute` → entry not found in file (macro-generated or #include'd); C++ `FNaniteCurveCommonParameters` SF_Compute via IMPLEMENT_GLOBAL_SHADER_STRUCT (Source/Runtime/Renderer/Private/Nanite/NaniteCurveRaster.inl:278)
- `SF_Compute` → entry not found in file (macro-generated or #include'd); C++ `FNaniteCurveCommonParameters` SF_Compute via IMPLEMENT_GLOBAL_SHADER_STRUCT (Source/Runtime/Renderer/Private/Nanite/NaniteCurveRaster.inl:279)
- `SF_Compute` → entry not found in file (macro-generated or #include'd); C++ `FNaniteCurveResolveParameters` SF_Compute via IMPLEMENT_GLOBAL_SHADER_STRUCT (Source/Runtime/Renderer/Private/Nanite/NaniteCurveRaster.inl:281)
- `SF_Compute` → entry not found in file (macro-generated or #include'd); C++ `FNaniteCurveResolveParameters` SF_Compute via IMPLEMENT_GLOBAL_SHADER_STRUCT_EX2 (Source/Runtime/Renderer/Private/Nanite/NaniteCurveRaster.inl:282)
- `SF_Compute` → entry not found in file (macro-generated or #include'd); C++ `FNaniteCurveDebugParameters` SF_Compute via IMPLEMENT_GLOBAL_SHADER_STRUCT_SP (Source/Runtime/Renderer/Private/Nanite/NaniteCurveRaster.inl:284)

### `Shaders/Private/Nanite/NaniteCurveCommon.ush` (Private)

- lines: 1477; parse: all-branches; parse notes: 1
- includes: L5 `/Engine/Private/Common.ush`, L6 `/Engine/Generated/UniformBuffers/View.ush`, L911 `../Hash.ush`

#### Macros (#define, 66)

- L93 `#define CLIP_AUX_PERSPECTIVE 0`
- L234 `#define TILE_PRIM_PACK_16NDWS_0Z 1`
- L235 `#define TILE_PRIM_PACK_16NDW_6S_10Z 2`
- L236 `#define TILE_PRIM_PACK_16NW_8Wx_10Dx_7S_16Z 3`
- L237 `#define TILE_PRIM_PACK TILE_PRIM_PACK_16NW_8Wx_10Dx_7S_16Z`
- L238 `#define TILE_PRIM_ENCODE_REL_DEPTH 0`
- L256 `#define UNORM_MAX(Bits) ((1u << (Bits)) - 1u)`
- L257 `#define UNORM_ENC(Bits, Expr) (uint)floor(UNORM_MAX(Bits) * saturate(Expr))`
- L258 `#define UNORM_DEC(Bits, Expr) ((Expr) & UNORM_MAX(Bits)) * (1.0 / UNORM_MAX(Bits))`
- L260 `#define UNORM_ENC_RANGE(Bits, Expr, Min, Max) UNORM_ENC(Bits, ((Expr) - (Min)) / ((Max) - (Min)))`
- L261 `#define UNORM_DEC_RANGE(Bits, Expr, Min, Max) (UNORM_DEC(Bits, (Expr)) * ((Max) - (Min)) + (Min))`
- L262 `#define UNORM_ENC_SDIST(Bits, Expr, Len) UNORM_ENC(Bits, ((Expr) * (0.5 / (Len))) + 0.5)`
- L263 `#define UNORM_DEC_SDIST(Bits, Expr, Len) (UNORM_DEC(Bits, (Expr)) * 2.0 * (Len) - (Len))`
- L264 `#define UNORM_ENC_UDIST(Bits, Expr, Len) UNORM_ENC(Bits, ((Expr) / (Len)))`
- L265 `#define UNORM_DEC_UDIST(Bits, Expr, Len) (UNORM_DEC(Bits, (Expr)) * (Len))`
- L267 `#define PACK_BEGIN { uint PACK_POS = 0u;`
- L268 `#define PACK_ENC_UNORM(Bits, Expr) ( PACK_POS += Bits, UNORM_ENC(Bits, (Expr)) << (PACK_POS - Bits) )`
- L269 `#define PACK_DEC_UNORM(Bits, Expr) ( PACK_POS += Bits, UNORM_DEC(Bits, (Expr) >> (PACK_POS - Bits)) )`
- L270 `#define PACK_ENC_FLAGS(Bits, Expr) ( PACK_POS += Bits, ((Expr) & UNORM_MAX(Bits)) << (PACK_POS - Bits) )`
- L271 `#define PACK_DEC_FLAGS(Bits, Expr) ( PACK_POS += Bits, ((Expr) >> (PACK_POS - Bits)) & UNORM_MAX(Bits) )`
- L272 `#define PACK_END }`
- L274 `#define PACK_ENC_RANGE(Bits, Expr, Min, Max) ( PACK_POS += Bits, UNORM_ENC_RANGE(Bits, (Expr), (Min), (Max)) << (PACK_POS - Bits) )`
- L275 `#define PACK_DEC_RANGE(Bits, Expr, Min, Max) ( PACK_POS += Bits, UNORM_DEC_RANGE(Bits, (Expr) >> (PACK_POS - Bits), (Min), (Max)) )`
- L276 `#define PACK_ENC_SDIST(Bits, Expr, Len) ( PACK_POS += Bits, UNORM_ENC_SDIST(Bits, (Expr), (Len)) << (PACK_POS - Bits) )`
- L277 `#define PACK_DEC_SDIST(Bits, Expr, Len) ( PACK_POS += Bits, UNORM_DEC_SDIST(Bits, (Expr) >> (PACK_POS - Bits), (Len)) )`
- L278 `#define PACK_ENC_UDIST(Bits, Expr, Len) ( PACK_POS += Bits, UNORM_ENC_UDIST(Bits, (Expr), (Len)) << (PACK_POS - Bits) )`
- L279 `#define PACK_DEC_UDIST(Bits, Expr, Len) ( PACK_POS += Bits, UNORM_DEC_UDIST(Bits, (Expr) >> (PACK_POS - Bits), (Len)) )`
- L312 `#define PACKBITS_W_SEL 1` _[#if TILE_PRIM_PACK == TILE_PRIM_PACK_16NW_8Wx_10Dx_7S_16Z]_
- L313 `#define PACKBITS_W_LO 7` _[#if TILE_PRIM_PACK == TILE_PRIM_PACK_16NW_8Wx_10Dx_7S_16Z]_
- L314 `#define PACKBITS_D_N 10` _[#if TILE_PRIM_PACK == TILE_PRIM_PACK_16NW_8Wx_10Dx_7S_16Z]_
- L315 `#define PACKBITS_S_MIN 7` _[#if TILE_PRIM_PACK == TILE_PRIM_PACK_16NW_8Wx_10Dx_7S_16Z]_
- L316 `#define PACKBITS_S_MAX 7` _[#if TILE_PRIM_PACK == TILE_PRIM_PACK_16NW_8Wx_10Dx_7S_16Z]_
- L354 `#define PACKBITS_S_MIN 6` _[#if !(TILE_PRIM_PACK == TILE_PRIM_PACK_16NW_8Wx_10Dx_7S_16Z) && TILE_PRIM_PACK == TILE_PRIM_PACK_16NDW_6S_10Z]_
- L355 `#define PACKBITS_S_MAX 6` _[#if !(TILE_PRIM_PACK == TILE_PRIM_PACK_16NW_8Wx_10Dx_7S_16Z) && TILE_PRIM_PACK == TILE_PRIM_PACK_16NDW_6S_10Z]_
- L356 `#define PACKBITS_Z_MIN 10` _[#if !(TILE_PRIM_PACK == TILE_PRIM_PACK_16NW_8Wx_10Dx_7S_16Z) && TILE_PRIM_PACK == TILE_PRIM_PACK_16NDW_6S_10Z]_
- L357 `#define PACKBITS_Z_MAX 10` _[#if !(TILE_PRIM_PACK == TILE_PRIM_PACK_16NW_8Wx_10Dx_7S_16Z) && TILE_PRIM_PACK == TILE_PRIM_PACK_16NDW_6S_10Z]_
- L588 `#define RASTER_CLAMP 1`
- L589 `#define RASTER_DEBUG 0`
- L725 `#define RASTER_BATCH_ALLOC (COMPILER_SUPPORTS_WAVE_MATCH_INTRINSICS)`
- L727 `#define INVALID_TILE_INDEX (~0u)`
- L951 `#define PAR_DECL template <typename FLayout, typename FUInt>`
- L952 `#define PAR_DECL_TO template <typename FLayout, typename FLayoutTo, typename FUIntTo, typename FUInt>`
- L953 `#define PAR_ARGS FLayout, FUInt`
- L954 `#define PAR_ARGS_TO FLayoutTo, FUIntTo`
- L955 `#define PAR_SPEC FLayout`
- L956 `#define PAR_SPEC_TO FLayoutTo`
- L957 `#define PAR_UINT FUInt`
- L958 `#define PAR_UINT_TO FUIntTo`
- L959 `#define PAR_UINT2 vector<FUInt, 2>`
- L960 `#define PAR_UINT3 vector<FUInt, 3>`
- L961 `#define PAR_UINT4 vector<FUInt, 4>`
- L989 `#define NUM_LANES PAR_SPEC::NUM_LANES`
- L990 `#define LANE_BITS PAR_SPEC::LANE_BITS`
- L991 `#define LANE_MASK PAR_SPEC::LANE_MASK`
- L992 `#define MSB PAR_SPEC::MSB`
- L993 `#define LSB PAR_SPEC::LSB`
- L1299 `#define PAR_DECL_TYPED template <typename FParallel>`
- L1300 `#define PAR_FUNC_TYPED(F,A,V) F(A) { FParallel L = { F<typename FParallel::FLayout>(V) }; return L; }`
- L1301 `#define PAR_PASS_TYPED(...) __VA_ARGS__`
- L1302 `#define PAR_SPEC_TYPED FParallel::FLayout`
- L1303 `#define PAR_UINT_TYPED FParallel`
- L1304 `#define PAR_UINT_VAL(L) L.Value`
- L1383 `#define ParallelPack8xU4(...) { FParallel8xU4::Pack(__VA_ARGS__) }`
- L1407 `#define ParallelPack4xU8(...) { FParallel4xU8::Pack(__VA_ARGS__) }`
- L1431 `#define ParallelPack8xU8(...) { FParallel8xU8::Pack(__VA_ARGS__) }`
- L1462 `#define ParallelPack4xU16(...) { FParallel4xU16::Pack(__VA_ARGS__) }`
- L3 #pragma `once`; L1290 #undef `NUM_LANES`; L1291 #undef `LANE_BITS`; L1292 #undef `LANE_MASK`; L1293 #undef `MSB`; L1294 #undef `LSB`

#### Structs / classes (13)

- L62-67 _struct_ **`FMinMaxZ`** `struct FMinMaxZ`
  - L64 _member_ `float MinZ;`
  - L65 _member_ `float MaxZ;`
  - L66 _member_ `float RangeZ;`
- L81-91 _struct_ **`FCurveSegment`** `struct FCurveSegment`
  - L84 _member_ `uint ID;` — TODO what mask is used to isolate curveID with nanite sourcepixelvalue being assigned?
  - L86 _member_ `float3 PosA;`
  - L87 _member_ `float3 PosB;`
  - L89 _member_ `float WidthA;`
  - L90 _member_ `float WidthB;`
- L240-253 _struct_ **`FTilePrimitive`** `struct FTilePrimitive`
  - L243 _member_ `float2 N;` — TODO illustration
  - L244 _member_ `float2 N_Perp;`
  - L245 _member_ `float D_N;`
  - L246 _member_ `float S_Min;`
  - L247 _member_ `float S_Max;`
  - L248 _member_ `float Z_Min;`
  - L249 _member_ `float Z_Max;`
  - L250 _member_ `float W_Min;`
  - L251 _member_ `float W_Max;`
  - L252 _member_ `uint ID;`
- L759-785 _struct_ **`FRasterOpTileCount`** `struct FRasterOpTileCount`
  - L761 _member_ `FRaster Raster;`
  - L762 _member_ `FCurveSegment Seg;`
  - L764 _method_ `void operator()(int i, int j)`
- L787-861 _struct_ **`FRasterOpTileWrite`** `struct FRasterOpTileWrite`
  - L789 _member_ `FRaster Raster;`
  - L790 _member_ `FCurveSegment Seg;`
  - L792 _method_ `void operator()(int i, int j)`
- L863-874 _struct_ **`FRasterOpTileWriteConditional`** `struct FRasterOpTileWriteConditional`
  - L865 _member_ `FCurveSegment Seg;`
  - L867 _method_ `void operator()(int i, int j)`
- L913-919 _struct_ **`FPCGHashOp`** `struct FPCGHashOp`
  - L915 _method_ `uint operator()(uint Key)`
- L1396-1418 _struct_ **`FParallel4xU8`** `struct FParallel4xU8`
  - L1408 _method_ `static uint Pack(uint x, uint y, uint z, uint w)`
  - L1417 _member_ `uint Value;` — for typed operations
- L1398-1405 _struct_ **`FParallel4xU8::FLayout`** `struct FLayout`
  - L1400 _member_ `static const uint NUM_LANES = 4;`
  - L1401 _member_ `static const uint LANE_BITS = 8;`
  - L1402 _member_ `static const uint LANE_MASK = 0xFFu;`
  - L1403 _member_ `static const uint MSB = 0x80808080u;`
  - L1404 _member_ `static const uint LSB = 0x01010101u;`
- L1420-1449 _struct_ **`FParallel8xU8`** `struct FParallel8xU8`
  - L1432 _method_ `static uint64_t Pack(uint x, uint y, uint z, uint w, uint a, uint b, uint c, uint d)`
  - L1448 _member_ `uint64_t Value;` — for typed operations
- L1422-1429 _struct_ **`FParallel8xU8::FLayout`** `struct FLayout`
  - L1424 _member_ `static const uint NUM_LANES = 8;`
  - L1425 _member_ `static const uint LANE_BITS = 8;`
  - L1426 _member_ `static const uint LANE_MASK = 0xFFu;`
  - L1427 _member_ `static const uint64_t MSB = 0x8080808080808080uL;`
  - L1428 _member_ `static const uint64_t LSB = 0x0101010101010101uL;`
- L1451-1476 _struct_ **`FParallel4xU16`** `struct FParallel4xU16`
  - L1463 _method_ `static uint64_t Pack(uint x, uint y, uint z, uint w)`
  - L1475 _member_ `uint64_t Value;` — for typed operations
- L1453-1460 _struct_ **`FParallel4xU16::FLayout`** `struct FLayout`
  - L1455 _member_ `static const uint NUM_LANES = 4;`
  - L1456 _member_ `static const uint LANE_BITS = 16;`
  - L1457 _member_ `static const uint LANE_MASK = 0xFFFFu;`
  - L1458 _member_ `static const uint64_t MSB = 0x8000800080008000uL;`
  - L1459 _member_ `static const uint64_t LSB = 0x0001000100010001uL;`

#### Global resources (textures / buffers / samplers) (22)

- L11 _resource_ `StructuredBuffer<uint> TileCount;`
- L12 _resource_ `StructuredBuffer<uint> TileOffset;`
- L13 _resource_ `StructuredBuffer<uint> TileMinMaxZ;`
- L14 _resource_ `StructuredBuffer<uint4> TileSegment;`
- L16 _resource_ `RWStructuredBuffer<uint> RWTileCount;`
- L17 _resource_ `RWStructuredBuffer<uint> RWTileOffset;`
- L18 _resource_ `RWStructuredBuffer<uint> RWTileMinMaxZ;`
- L19 _resource_ `RWStructuredBuffer<uint4> RWTileSegment;`
- L21 _resource_ `Texture2D<float> TileHeat;`
- L22 _resource_ `Texture2D<float> OutCoverage;`
- L23 _resource_ `Texture2D<uint> OutVisibility;`
- L24 _resource_ `Texture2D<uint> OutVisibilityW;`
- L26 _resource_ `RWTexture2D<float> RWTileHeat;`
- L27 _resource_ `RWTexture2D<float> RWOutCoverage;`
- L28 _resource_ `RWTexture2D<uint> RWOutVisibility;`
- L29 _resource_ `RWTexture2D<uint> RWOutVisibilityW;`
- L31 _resource_ `StructuredBuffer<uint> ActiveTile;`
- L32 _resource_ `StructuredBuffer<uint> ActiveTileCount;`
- L33 _resource_ `RWStructuredBuffer<uint> RWActiveTile;`
- L34 _resource_ `RWStructuredBuffer<uint> RWActiveTileCount;`
- L36 _resource_ `Buffer<uint> ActiveTileIndirectArgs;`
- L37 _resource_ `RWBuffer<uint> RWActiveTileIndirectArgs;`

#### Global parameters (uniforms) (8)

- L42 _parameter_ `uint FrameIndex;`
- L43 _parameter_ `uint TileSegmentMaxCount;`
- L44 _parameter_ `uint3 MaxDispatchThreadGroupsPerDimension;`
- L46 _parameter_ `uint NumTilesX;`
- L47 _parameter_ `uint NumTilesY;`
- L48 _parameter_ `uint NumTilesA;`
- L50 _parameter_ `int2 RasterViewSize;`
- L52 _parameter_ `uint TileStride;`

#### Functions (38)

- L57-60 _function_ `uint2 GetTileCoord(uint InTileIndex)`
- L69-76 _function_ `FMinMaxZ GetTileMinMaxZ()`
- L95-210 _function_ `bool SegmentClipHomogeneous(inout float4 ClipPosA, inout float4 ClipPosB, inout float4 ClipAuxA, inout float4 ClipAuxB)`
- L212-222 _function_ `bool SegmentScreenToCell(inout FCurveSegment Seg, uint CellWidth)`
- L224-228 _function_ `bool SegmentScreenToTile(inout FCurveSegment Seg, uint CompileTimeTileWidth)`
- L281-406 _function_ `uint4 TilePrimitivePack(FTilePrimitive Prim)`
- L408-485 _function_ `FTilePrimitive TilePrimitiveUnpack(uint4 PackedPrim)`
- L487-567 _function_ `bool TilePrimitivePrepare(int i, int j, FCurveSegment Seg, inout FTilePrimitive Prim)`
- L569-583 _function_ `void TilePrimitiveResolve(FTilePrimitive Prim, float2 V, out float3 V_Pos, out float2 V_Ext)`
- L595-692 _function_ `template <bool bConservative, typename FRasterOp> void RasterizeSegmentSorted(float2 P_0, float2 P_1, float w_0, float w_1, FRasterOp RasterOp)` — rasterizes segment (P0, P1, w0, w1) to unit grid invokes FRasterOp for each overlapping cell assumes P0.y <= P1.y (TODO fix this) TODO add capped rasteriation
- L694-698 _function_ `template <bool bConservative, typename FRasterOp> void RasterizeSegmentSorted(FCurveSegment Seg, FRasterOp RasterOp)`
- L702-714 _function_ `template <bool bConservative, typename FRasterOp> void RasterizeSegment(float2 P_0, float2 P_1, float w_0, float w_1, FRasterOp RasterOp)` — rasterizes segment (P0, P1, w0, w1) to unit grid invokes FRasterOp for each overlapping cell
- L716-720 _function_ `template <bool bConservative, typename FRasterOp> void RasterizeSegment(FCurveSegment Seg, FRasterOp RasterOp)`
- L729-757 _function_ `uint ComputeTileIndex(FRaster InRaster, int i, int j)`
- L880-896 _function_ `float SdSegment(float2 p, float r, float h)` — Compute signed distance to vertical segment with radius r, and half-height h, at position p
- L899-906 _function_ `float SliceHeightUnitSquare(float2 n, float d)` — Compute slice height of unit square at n*d where (n, d) is slicing plane normal, distance
- L925-946 _function_ `template <uint M, uint K, typename FHashOp> bool BloomFilter(inout uint State[M >> 5], uint Key, FHashOp HashOp)` — Insert key in (approximate) set; returns true if maybe duplicate, false if definitely not duplicate
- L996-1000 _function_ `PAR_DECL PAR_UINT ParallelBroadcast(uint x)` — x x x x . . . .
- L1003-1007 _function_ `PAR_DECL PAR_UINT ParallelBroadcast(PAR_UINT, uint x)` — x x x x . . . .
- L1010-1022 _function_ `PAR_DECL PAR_UINT ParallelPack(uint x[NUM_LANES])` — x y z w . . . .
- L1025-1029 _function_ `PAR_DECL PAR_UINT ParallelPack(PAR_UINT, uint x[NUM_LANES])` — x y z w . . . .
- L1032-1048 _function_ `PAR_DECL_TO PAR_UINT_TO ParallelConvert(PAR_UINT a)` — b b b b (from a a a a)
- L1051-1066 _function_ `PAR_DECL PAR_UINT UnmaskedParallelNZ(PAR_UINT a)` — a a a a != 0 0 0 0
- L1069-1086 _function_ `PAR_DECL PAR_UINT UnmaskedParallelLT(PAR_UINT a, PAR_UINT b)` — a a a a < b b b b
- L1089-1090 _function_ `PAR_DECL PAR_UINT ParallelNZ(PAR_UINT a)` — a a a a != 0 0 0 0
- L1093-1094 _function_ `PAR_DECL PAR_UINT ParallelEZ(PAR_UINT a)` — a a a a == 0 0 0 0
- L1097-1098 _function_ `PAR_DECL PAR_UINT ParallelNE(PAR_UINT a, PAR_UINT b)` — a a a a != b b b b
- L1101-1102 _function_ `PAR_DECL PAR_UINT ParallelEQ(PAR_UINT a, PAR_UINT b)` — a a a a == b b b b
- L1105-1106 _function_ `PAR_DECL PAR_UINT ParallelLT(PAR_UINT a, PAR_UINT b)` — a a a a < b b b b
- L1109-1110 _function_ `PAR_DECL PAR_UINT ParallelLE(PAR_UINT a, PAR_UINT b)` — a a a a <= b b b b
- L1113-1114 _function_ `PAR_DECL PAR_UINT ParallelGT(PAR_UINT a, PAR_UINT b)` — a a a a > b b b b
- L1117-1118 _function_ `PAR_DECL PAR_UINT ParallelGE(PAR_UINT a, PAR_UINT b)` — a a a a >= b b b b
- L1121-1127 _function_ `PAR_DECL PAR_UINT ParallelMax(PAR_UINT a, PAR_UINT b)` — (a a a a > b b b b) ? a a a a : b b b b
- L1130-1136 _function_ `PAR_DECL PAR_UINT ParallelMin(PAR_UINT a, PAR_UINT b)` — (a a a a < b b b b) ? a a a a : b b b b
- L1139-1211 _function_ `PAR_DECL PAR_UINT ParallelSortedInsert(PAR_UINT a, uint x)` — bb bb bb aa => bb bb xx aa (insert x where x < a)
- L1214-1234 _function_ `PAR_DECL PAR_UINT ParallelSortedInsertWithPayload(PAR_UINT a, uint x, inout PAR_UINT b, uint y)` — bb bb bb aa => bb bb xx/yy aa (insert x/y where x < a)
- L1236-1266 _function_ `PAR_DECL PAR_UINT4 MultiParallelSortedInsert(PAR_UINT4 a, uint x)`
- L1268-1288 _function_ `PAR_DECL PAR_UINT4 MultiParallelSortedInsertWithPayload(PAR_UINT4 a, uint x, inout PAR_UINT4 b, uint y)`

#### Unparsed (raw text) (1)

- L1339-1394 _unparsed_ `PAR_DECL_TYPED PAR_UINT_TYPED PAR_FUNC_TYPED(ParallelPack, PAR_PASS_TYPED(uint x[PAR_SPEC_TYPED::NUM_LANES]), PAR_PASS_TYPED(PAR_UINT_VAL(PAR_UINT_TYPED()), x)) PAR_DECL_TYPED PAR_UINT_TYPED PAR_FUNC_TYPED(ParallelNZ, PAR_PASS_TYPED(PAR_UINT_TYPED a), PAR_PASS_TYPED(PAR_UINT_VAL(a))) PAR_DECL_TYPED PAR_UINT_TYPED PAR_FUNC_TYPED(ParallelEZ, PAR_PASS_TYPED(PAR_UINT_TYPED a), PAR_PASS_TYPED(PAR_UINT_` — PAR_DECL_TYPED PAR_UINT_TYPED PAR_FUNC_TYPED(ParallelBroadcast, PAR_PASS_TYPED(uint x), PAR_PASS_TYPED(PAR_UINT_VAL(PAR_UINT_TYPED()), x))

<details><summary>parse notes</summary>

- L1339: unrecognised block header 'PAR_DECL_TYPED PAR_UINT_TYPED PAR_FUNC_TYPED(ParallelPack, PAR_PASS_TYPED(uint x'

</details>

### `Shaders/Private/Nanite/NaniteDataDecode.ush` (Private)

- lines: 1252; parse: all-branches
- includes: L5 `../Common.ush`, L6 `../BitPacking.ush`, L7 `../SceneData.ush`, L8 `../WaveOpUtil.ush`, L9 `../BoneTransform.ush`, L10 `../Skinning/SkinningSceneDataDecode.ush`, L11 `/Engine/Shared/NaniteDefinitions.h`, L12 `/Engine/Shared/SkinningDefinitions.h`, L13 `/Engine/Shared/HLSLStaticAssert.h`, L14 `NanitePackedNaniteView.ush`

#### Macros (#define, 30)

- L17 `#define DEBUG_FLAGS 0` _[#if !defined(DEBUG_FLAGS)]_
- L25 `#define NANITE_EXTENDED_VISIBLE_CLUSTERS (NANITE_ASSEMBLY_DATA \|\| NANITE_VOXEL_DATA)`
- L27 `#define NANITE_CANDIDATE_CLUSTER_SIZE_DWORDS 3` _[#if NANITE_EXTENDED_VISIBLE_CLUSTERS]_
- L29 `#define NANITE_CANDIDATE_CLUSTER_SIZE_DWORDS 2` _[#if !(NANITE_EXTENDED_VISIBLE_CLUSTERS)]_
- L32 `#define NANITE_CLUSTER_TYPE_UNKNOWN 0`
- L33 `#define NANITE_CLUSTER_TYPE_TRIANGLES 1`
- L34 `#define NANITE_CLUSTER_TYPE_VOXELS 2`
- L35 `#define NANITE_CLUSTER_TYPE_CURVES 3`
- L266 `#define PageConstants NaniteRayTracing.PageConstants` _[#if NANITE_USE_RAYTRACING_UNIFORM_BUFFER]_
- L267 `#define MaxNodes NaniteRayTracing.MaxNodes` _[#if NANITE_USE_RAYTRACING_UNIFORM_BUFFER]_
- L268 `#define ClusterPageData NaniteRayTracing.ClusterPageData` _[#if NANITE_USE_RAYTRACING_UNIFORM_BUFFER]_
- L269 `#define HierarchyBuffer NaniteRayTracing.HierarchyBuffer` _[#if NANITE_USE_RAYTRACING_UNIFORM_BUFFER]_
- L270 `#define RayTracingDataBuffer NaniteRayTracing.RayTracingDataBuffer` _[#if NANITE_USE_RAYTRACING_UNIFORM_BUFFER]_
- L271 `#define UsingCLAS NaniteRayTracing.UsingCLAS` _[#if NANITE_USE_RAYTRACING_UNIFORM_BUFFER]_
- L274 `#define RenderFlags 0` _[#if NANITE_USE_RAYTRACING_UNIFORM_BUFFER]_
- L281 `#define PageConstants NaniteRaster.PageConstants` _[#if !(NANITE_USE_RAYTRACING_UNIFORM_BUFFER) && NANITE_USE_RASTER_UNIFORM_BUFFER]_
- L282 `#define MaxNodes NaniteRaster.MaxNodes` _[#if !(NANITE_USE_RAYTRACING_UNIFORM_BUFFER) && NANITE_USE_RASTER_UNIFORM_BUFFER]_
- L283 `#define MaxVisibleClusters NaniteRaster.MaxVisibleClusters` _[#if !(NANITE_USE_RAYTRACING_UNIFORM_BUFFER) && NANITE_USE_RASTER_UNIFORM_BUFFER]_
- L284 `#define MaxPatchesPerGroup NaniteRaster.MaxPatchesPerGroup` _[#if !(NANITE_USE_RAYTRACING_UNIFORM_BUFFER) && NANITE_USE_RASTER_UNIFORM_BUFFER]_
- L285 `#define MeshPass NaniteRaster.MeshPass` _[#if !(NANITE_USE_RAYTRACING_UNIFORM_BUFFER) && NANITE_USE_RASTER_UNIFORM_BUFFER]_
- L286 `#define InvDiceRate NaniteRaster.InvDiceRate` _[#if !(NANITE_USE_RAYTRACING_UNIFORM_BUFFER) && NANITE_USE_RASTER_UNIFORM_BUFFER]_
- L287 `#define RenderFlags NaniteRaster.RenderFlags` _[#if !(NANITE_USE_RAYTRACING_UNIFORM_BUFFER) && NANITE_USE_RASTER_UNIFORM_BUFFER]_
- L288 `#define DebugFlags NaniteRaster.DebugFlags` _[#if !(NANITE_USE_RAYTRACING_UNIFORM_BUFFER) && NANITE_USE_RASTER_UNIFORM_BUFFER]_
- L289 `#define CurveSubdivisionThreshold NaniteRaster.CurveSubdivisionThreshold` _[#if !(NANITE_USE_RAYTRACING_UNIFORM_BUFFER) && NANITE_USE_RASTER_UNIFORM_BUFFER]_
- L290 `#define CurveSubdivisionMaxSegments NaniteRaster.CurveSubdivisionMaxSegments` _[#if !(NANITE_USE_RAYTRACING_UNIFORM_BUFFER) && NANITE_USE_RASTER_UNIFORM_BUFFER]_
- L305 `#define ClusterPageData NaniteShading.ClusterPageData` _[#if !(NANITE_USE_RAYTRACING_UNIFORM_BUFFER) && NANITE_USE_SHADING_UNIFORM_BUFFER]_
- L306 `#define VisibleClustersSWHW NaniteShading.VisibleClustersSWHW` _[#if !(NANITE_USE_RAYTRACING_UNIFORM_BUFFER) && NANITE_USE_SHADING_UNIFORM_BUFFER]_
- L307 `#define HierarchyBuffer NaniteShading.HierarchyBuffer` _[#if !(NANITE_USE_RAYTRACING_UNIFORM_BUFFER) && NANITE_USE_SHADING_UNIFORM_BUFFER]_
- L308 `#define AssemblyTransforms NaniteShading.AssemblyTransforms` _[#if !(NANITE_USE_RAYTRACING_UNIFORM_BUFFER) && NANITE_USE_SHADING_UNIFORM_BUFFER]_
- L1020 `#define NANITE_VIEWS_DECLARATION 1` _[#if !defined(NANITE_VIEWS_DECLARATION)]_
- L3 #pragma `once`

#### Structs / classes (12)

- L48-59 _struct_ **`FVisibleCluster`** `struct FVisibleCluster`
  - L50 _member_ `uint Flags;`
  - L51 _member_ `uint ViewId;`
  - L52 _member_ `uint InstanceId;`
  - L53 _member_ `uint PageIndex;`
  - L54 _member_ `uint ClusterIndex;`
  - L55 _member_ `uint AssemblyTransformIndex;`
  - L56 _member_ `uint DepthBucket;`
  - L57 _member_ `uint2 vPage;`
  - L58 _member_ `uint2 vPageEnd;` — Last page to render (inclusive). Only used during SW rasterization currently
- L61-66 _struct_ **`FPageHeader`** `struct FPageHeader`
  - L63 _member_ `uint NumClusters;`
  - L64 _member_ `uint MaxClusterBoneInfluences;`
  - L65 _member_ `uint MaxVoxelBoneInfluences;`
- L68-149 _struct_ **`FCluster`** `struct FCluster`
  - L70 _member_ `uint PageBaseAddress;`
  - L72 _member_ `uint NumVerts;`
  - L73 _member_ `uint PositionOffset;`
  - L75 _member_ `uint NumTris;`
  - L76 _member_ `uint IndexOffset;`
  - L78 _member_ `int3 PosStart;`
  - L79 _member_ `uint BitsPerIndex;`
  - L80 _member_ `int PosPrecision;`
  - L81 _member_ `uint3 PosBits;`
  - L82 _member_ `uint NormalPrecision;`
  - L83 _member_ `uint TangentPrecision;`
  - L84 _member_ `float PosScale;`
  - L85 _member_ `float PosRcpScale;`
  - L87 _member_ `float4 LODBounds;`
  - L89 _member_ `float3 BoxBoundsCenter;`
  - L90 _member_ `float LODError;`
  - L91 _member_ `float EdgeLength;`
  - L93 _member_ `float3 BoxBoundsExtent;`
  - L94 _member_ `uint Flags;`
  - L96 _member_ `uint AttributeOffset;`
  - L97 _member_ `uint BitsPerAttribute;`
  - L98 _member_ `uint DecodeInfoOffset;`
  - L99 _member_ `bool bHasTangents;`
  - L100 _member_ `bool bSkinning;`
  - L101 _member_ `bool bVoxel;`
  - L102 _member_ `bool bCurve;`
  - L103 _member_ `uint NumUVs;`
  - L104 _member_ `uint ColorMode;`
  - L105 _member_ `uint UVBitOffsets;`
  - L107 _member_ `uint ColorMin;`
  - L108 _member_ `uint ColorBits;`
  - L109 _member_ `uint GroupIndex;` — Debug only
  - L111 _member_ `uint NumClusterBoneInfluences;`
  - L112 _member_ `uint ClusterBoneInfluenceAddress;`
  - L113 _member_ `uint ClusterBoneInfluenceStride;`
  - L116 _member_ `uint MaterialTableOffset;` — Material Slow path
  - L117 _member_ `uint MaterialTableLength;`
  - L119 _member_ `uint VertReuseBatchCountTableOffset;` — dword offset from page base
  - L120 _member_ `uint VertReuseBatchCountTableSize;` — number of entries, each 4-bit
  - L123 _member_ `uint Material0Length;` — Material Fast path
  - L124 _member_ `uint Material0Index;`
  - L125 _member_ `uint Material1Length;`
  - L126 _member_ `uint Material1Index;`
  - L127 _member_ `uint Material2Index;`
  - L128 _member_ `uint MaterialTotalLength;`
  - L130 _member_ `uint4 VertReuseBatchInfo;`
  - L132 _member_ `uint ExtendedDataOffset;`
  - L133 _member_ `uint ExtendedDataNum;`
  - L135 _member_ `uint BrickDataOffset;`
  - L136 _member_ `uint BrickDataNum;`
  - L138 _member_ `uint NumCurves;`
  - L139 _member_ `uint NumPointsPerCurve;`
  - L141 _member_ `bool CompileTimeCouldBeCurve;`
  - L142 _member_ `bool bHasCurveRadius;`
  - L143 _member_ `uint CurveRadiusBits;`
  - L144 _member_ `float CurveRadiusScale;`
  - L145 _member_ `uint CurveFadingIndex;`
  - L147 _member_ `float ParentLODError;`
  - L148 _member_ `float ParentSphereBoundRadius;`
- L151-158 _struct_ **`FBrick`** `struct FBrick`
  - L153 _member_ `uint2 ReverseBrickBits;`
  - L154 _member_ `int3 StartPos;`
  - L155 _member_ `uint3 BrickMax;`
  - L156 _member_ `uint VertOffset;`
  - L157 _member_ `uint BoneIndex;`
- L160-163 _struct_ **`FClusterBoneInfluence`** `struct FClusterBoneInfluence`
  - L162 _member_ `uint BoneIndex;`
- L165-169 _struct_ **`FBoneInfluence`** `struct FBoneInfluence`
  - L167 _member_ `uint BoneIndex;`
  - L168 _member_ `float Weight;`
- L171-187 _struct_ **`FHierarchyNodeSlice`** `struct FHierarchyNodeSlice`
  - L173 _member_ `float4 LODBounds;`
  - L174 _member_ `float3 BoxBoundsCenter;`
  - L175 _member_ `float3 BoxBoundsExtent;`
  - L176 _member_ `float MinLODError;`
  - L177 _member_ `float MaxParentLODError;`
  - L178 _member_ `uint ChildStartReference;` — Can be node (index) or cluster (page:cluster)
  - L179 _member_ `uint NumChildren;`
  - L180 _member_ `uint ResourcePageRangeKey;`
  - L181 _member_ `uint AssemblyTransformIndex;`
  - L182 _member_ `uint NumBones;`
  - L183 _member_ `uint BoneIndicesOffsetInDwords;`
  - L184 _member_ `bool bEnabled;`
  - L185 _member_ `bool bLoaded;`
  - L186 _member_ `bool bLeaf;`
- L189-194 _struct_ **`FInstanceDynamicData`** `struct FInstanceDynamicData`
  - L191 _member_ `float4x4 LocalToTranslatedWorld;`
  - L192 _member_ `float4x4 PrevLocalToTranslatedWorld;`
  - L193 _member_ `bool bHasMoved;`
- L196-248 _struct_ **`FNaniteView`** `struct FNaniteView`
  - L198 _member_ `float4x4 SVPositionToTranslatedWorld;`
  - L199 _member_ `float4x4 ViewToTranslatedWorld;`
  - L201 _member_ `float4x4 TranslatedWorldToView;`
  - L202 _member_ `float4x4 TranslatedWorldToClip;`
  - L203 _member_ `float4x4 ViewToClip;`
  - L204 _member_ `FDFMatrix ClipToWorld;`
  - L206 _member_ `float4x4 PrevTranslatedWorldToView;`
  - L207 _member_ `float4x4 PrevTranslatedWorldToClip;`
  - L208 _member_ `float4x4 PrevViewToClip;`
  - L209 _member_ `FDFMatrix PrevClipToWorld;`
  - L211 _member_ `float3x3 FirstPersonTransform;`
  - L212 _member_ `float3x3 PrevFirstPersonTransform;`
  - L213 _member_ `float3x3 InvFirstPersonTransform;`
  - L215 _member_ `float4 TranslatedGlobalClipPlane;`
  - L217 _member_ `int4 ViewRect;`
  - L218 _member_ `float4 ViewSizeAndInvSize;`
  - L219 _member_ `float4 ClipSpaceScaleOffset;`
  - L220 _member_ `float4 MaterialCacheUnwrapMinAndInvSize;`
  - L221 _member_ `float4 MaterialCachePageOffsetAndInvSize;`
  - L222 _member_ `FDFVector3 PreViewTranslation;`
  - L223 _member_ `FDFVector3 PrevPreViewTranslation;`
  - L224 _member_ `FDFVector3 PrevPreViewTranslationHZB;`
  - L225 _member_ `FDFVector3 WorldCameraOrigin;`
  - L226 _member_ `float3 CullingViewOriginTranslatedWorld;`
  - L227 _member_ `float3 ViewForward;`
  - L228 _member_ `float3 ViewOriginHigh;`
  - L229 _member_ `float NearPlane;`
  - L230 _member_ `float LODScale;`
  - L231 _member_ `float LODScaleHW;`
  - L232 _member_ `float CullingViewMinRadiusTestFactorSq;`
  - L233 _member_ `uint StreamingPriorityCategory;`
  - L234 _member_ `uint Flags;`
  - L235 _member_ `int TargetLayerIndex;`
  - L236 _member_ `int TargetMipLevel;`
  - L237 _member_ `int TargetNumMipLevels;`
  - L238 _member_ `int TargetPrevLayerIndex;`
  - L239 _member_ `float RangeBasedCullingDistance;`
  - L240 _member_ `int4 HZBTestViewRect;`
  - L241 _member_ `float CullingViewScreenMultipleSq;`
  - L242 _member_ `uint InstanceOcclusionQueryMask;`
  - L243 _member_ `bool bUseLightingChannelMask;`
  - L244 _member_ `uint LightingChannelMask;`
  - L245 _member_ `int SceneRendererPrimaryViewId;`
  - L246 _member_ `float2 DynamicDepthCullRange;`
  - L247 _member_ `uint FrameIndex;`
- L250-254 _struct_ **`FInstanceDraw`** `struct FInstanceDraw`
  - L252 _member_ `uint InstanceId;`
  - L253 _member_ `uint ViewId;`
- L256-263 _struct_ **`FNaniteFullscreenVSToPS`** `struct FNaniteFullscreenVSToPS`
  - L259 _member_ `nointerpolation uint EyeIndex : PACKED_EYE_INDEX;` _[#if INSTANCED_STEREO]_
  - L261 _member_ `nointerpolation uint ViewIndex : PACKED_VIEW_INDEX;`
  - L262 _member_ `nointerpolation uint TileIndex : MACRO_TILE_INDEX;`
- L822-831 _struct_ **`FShadingMask`** `struct FShadingMask`
  - L824 _member_ `bool bIsNanitePixel;`
  - L825 _member_ `bool bIsDecalReceiver;`
  - L826 _member_ `bool bHasRayTracingRepresentation;`
  - L827 _member_ `bool bCastShadow;`
  - L828 _member_ `uint LightingChannels;`
  - L829 _member_ `uint ShadingBin;`
  - L830 _member_ `uint ShadingRate;`

#### Global resources (textures / buffers / samplers) (6)

- L310 _resource_ `ByteAddressBuffer ClusterPageData;` _[#if !(NANITE_USE_RAYTRACING_UNIFORM_BUFFER) && !(NANITE_USE_SHADING_UNIFORM_BUFFER)]_
- L311 _resource_ `ByteAddressBuffer VisibleClustersSWHW;` _[#if !(NANITE_USE_RAYTRACING_UNIFORM_BUFFER) && !(NANITE_USE_SHADING_UNIFORM_BUFFER)]_
- L312 _resource_ `ByteAddressBuffer HierarchyBuffer;` _[#if !(NANITE_USE_RAYTRACING_UNIFORM_BUFFER) && !(NANITE_USE_SHADING_UNIFORM_BUFFER)]_
- L313 _resource_ `ByteAddressBuffer AssemblyTransforms;` _[#if !(NANITE_USE_RAYTRACING_UNIFORM_BUFFER) && !(NANITE_USE_SHADING_UNIFORM_BUFFER)]_
- L314 _resource_ `ByteAddressBuffer RayTracingDataBuffer;` _[#if !(NANITE_USE_RAYTRACING_UNIFORM_BUFFER) && !(NANITE_USE_SHADING_UNIFORM_BUFFER)]_
- L1024 _resource_ `StructuredBuffer<FPackedNaniteView> InViews;` _[#if NANITE_VIEWS_DECLARATION]_

#### Global parameters (uniforms) (10)

- L292 _parameter_ `uint4 PageConstants;` _[#if !(NANITE_USE_RAYTRACING_UNIFORM_BUFFER) && !(NANITE_USE_RASTER_UNIFORM_BUFFER)]_
- L293 _parameter_ `uint MaxNodes;` _[#if !(NANITE_USE_RAYTRACING_UNIFORM_BUFFER) && !(NANITE_USE_RASTER_UNIFORM_BUFFER)]_
- L294 _parameter_ `uint MaxVisibleClusters;` _[#if !(NANITE_USE_RAYTRACING_UNIFORM_BUFFER) && !(NANITE_USE_RASTER_UNIFORM_BUFFER)]_
- L295 _parameter_ `uint MaxPatchesPerGroup;` _[#if !(NANITE_USE_RAYTRACING_UNIFORM_BUFFER) && !(NANITE_USE_RASTER_UNIFORM_BUFFER)]_
- L296 _parameter_ `uint MeshPass;` _[#if !(NANITE_USE_RAYTRACING_UNIFORM_BUFFER) && !(NANITE_USE_RASTER_UNIFORM_BUFFER)]_
- L297 _parameter_ `float InvDiceRate;` _[#if !(NANITE_USE_RAYTRACING_UNIFORM_BUFFER) && !(NANITE_USE_RASTER_UNIFORM_BUFFER)]_
- L298 _parameter_ `uint RenderFlags;` _[#if !(NANITE_USE_RAYTRACING_UNIFORM_BUFFER) && !(NANITE_USE_RASTER_UNIFORM_BUFFER)]_
- L299 _parameter_ `uint DebugFlags;` _[#if !(NANITE_USE_RAYTRACING_UNIFORM_BUFFER) && !(NANITE_USE_RASTER_UNIFORM_BUFFER)]_
- L300 _parameter_ `float CurveSubdivisionThreshold;` _[#if !(NANITE_USE_RAYTRACING_UNIFORM_BUFFER) && !(NANITE_USE_RASTER_UNIFORM_BUFFER)]_
- L301 _parameter_ `uint CurveSubdivisionMaxSegments;` _[#if !(NANITE_USE_RAYTRACING_UNIFORM_BUFFER) && !(NANITE_USE_RASTER_UNIFORM_BUFFER)]_

#### Functions (52)

- L37-46 _function_ `uint GetHWClusterCounterIndex(uint InRenderFlags)`
- L321-330 _function_ `FInstanceDynamicData WaveReadLaneAt(FInstanceDynamicData In, uint SrcIndex)` _[#if FEATURE_LEVEL >= FEATURE_LEVEL_SM6 \|\| PLATFORM_SUPPORTS_SM6_0_WAVE_OPERATIONS]_
- L333-336 _function_ `bool IsPixelInRect(int2 PixelCoord, int4 Rect)`
- L338-341 _function_ `float ClipZFromLinearZ(FNaniteView NaniteView, float LinearZ)`
- L344-350 _function_ `uint PackPoolClusterRef(uint PageIndex, uint ClusterIndex)` — Packs a (PageIndex, ClusterIndex) pair into a flat index based on max clusters per page.
- L352-367 _function_ `void UnpackPoolClusterRef(uint PackedClusterRef, inout uint PageIndex, inout uint ClusterIndex)`
- L369-395 _function_ `uint4 PackVisibleCluster(FVisibleCluster VisibleCluster, bool bHasPageData)`
- L397-429 _function_ `FVisibleCluster UnpackVisibleCluster(uint4 RawData, bool bHasPageData = false)`
- L431-447 _function_ `FVisibleCluster GetVisibleCluster( ByteAddressBuffer VisibleClusters, uint ClusterIdx, bool bHasPageData = false )`
- L449-456 _function_ `FVisibleCluster GetVisibleCluster( uint ClusterIdx, bool bHasPageData )`
- L458-461 _function_ `FVisibleCluster GetVisibleCluster( uint ClusterIndex )`
- L463-471 _function_ `bool IsValidHierarchyAssemblyTransformIndex(uint Index)`
- L473-481 _function_ `bool IsValidAssemblyTransformIndex(uint Index)`
- L483-486 _function_ `bool IsAssemblyPartCluster(FVisibleCluster VisibleCluster)`
- L488-625 _function_ `FCluster UnpackCluster(uint4 ClusterData[NANITE_NUM_PACKED_CLUSTER_FLOAT4S], FPageHeader PageHeader, uint PageBaseAddress, uint LocalClusterIndex, uint ClusterType)`
- L627-631 _function_ `uint GPUPageIndexToGPUOffset(uint PageIndex)`
- L633-640 _function_ `FPageHeader UnpackPageHeader(uint4 Data)`
- L642-645 _function_ `FPageHeader GetPageHeader(ByteAddressBuffer InputBuffer, uint PageAddress)`
- L647-650 _function_ `FPageHeader GetPageHeader(RWByteAddressBuffer InputBuffer, uint PageAddress)`
- L652-665 _function_ `FCluster GetCluster(ByteAddressBuffer InputBuffer, FPageHeader PageHeader, uint SrcBaseOffset, uint ClusterIndex, uint ClusterType = NANITE_CLUSTER_TYPE_UNKNOWN)`
- L667-680 _function_ `FCluster GetCluster(RWByteAddressBuffer InputBuffer, FPageHeader PageHeader, uint PageBaseAddress, uint ClusterIndex, uint ClusterType = NANITE_CLUSTER_TYPE_UNKNOWN)`
- L682-687 _function_ `FCluster GetCluster(uint PageIndex, uint ClusterIndex, uint ClusterType = NANITE_CLUSTER_TYPE_UNKNOWN)`
- L689-725 _function_ `FHierarchyNodeSlice UnpackHierarchyNodeSlice(uint4 RawData0, uint4 RawData1, uint4 RawData2, uint3 RawData3)`
- L727-730 _function_ `uint GetHierarchyNodeOffset(uint RootOffset, uint NodeIndex)`
- L732-743 _function_ `FHierarchyNodeSlice GetHierarchyNodeSlice(ByteAddressBuffer InputBuffer, uint NodeOffset, uint ChildIndex)`
- L745-756 _function_ `FHierarchyNodeSlice GetHierarchyNodeSlice(RWByteAddressBuffer InputBuffer, uint NodeOffset, uint ChildIndex)`
- L758-761 _function_ `FHierarchyNodeSlice GetHierarchyNodeSlice(uint NodeOffset, uint ChildIndex)`
- L763-767 _function_ `void StoreHierarchyNodeChildStartReference(RWByteAddressBuffer OutputBuffer, uint NodeOffset, uint ChildIndex, uint ChildStartReference)`
- L769-777 _function_ `uint3 DecodeSegmentIndices(FCluster Cluster, uint TriIndex)`
- L780-799 _function_ `uint3 DecodeTriangleIndices(FCluster Cluster, uint TriIndex)` — Decode triangle that is represented by one base index and two 5-bit offsets.
- L801-820 _function_ `FBrick DecodeBrick(FCluster Cluster, uint BrickIndex)`
- L833-850 _function_ `uint PackShadingMask( uint ShadingBin, uint ShadingRate, bool bIsDecalReceiver, bool bHasRayTracingRepresentation, bool bCastShadow, uint LightingChannels )`
- L852-862 _function_ `uint PackShadingMask(FShadingMask Mask)`
- L864-875 _function_ `FShadingMask UnpackShadingMask(uint Packed)`
- L878-881 _function_ `uint PackClusterIndexAndTriIndex(uint VisibleClusterIndex, uint TriIndex)` — PackClusterIndexAndTriIndex/UnpackClusterIndexAndTriIndex are used internally by triangle tesselation code
- L883-887 _function_ `void UnpackClusterIndexAndTriIndex(uint In, out uint OutVisibleClusterIndex, out uint OutTriIndex)`
- L890-893 _function_ `uint PackVisPixelX(uint VisibleClusterIndex, uint TriIndex)` — PackVisPixelX/UnpackVisPixelX/UnpackVisPixel are used by all rasterizers and material evaluation
- L895-899 _function_ `void UnpackVisPixelX(uint Unpacked, out uint OutVisibleClusterIndex, out uint OutTriIndex)`
- L901-911 _function_ `void UnpackVisPixel( UlongType Pixel, out uint DepthInt, out uint VisibleClusterIndex, out uint TriIndex )`
- L913-922 _function_ `void UnpackDbgPixel( UlongType Pixel, out uint DepthInt, out uint DebugValue )`
- L924-939 _function_ `uint3 GetClusterPosition(uint VertIndex, FCluster Cluster)`
- L941-951 _function_ `float3 DecodePosition(uint VertIndex, FCluster Cluster)`
- L953-1017 _function_ `FNaniteView UnpackNaniteView(FPackedNaniteView PackedView)`
- L1027-1095 _function_ `FNaniteView GetNaniteView( uint ViewIndex )`
- L1098-1130 _function_ `void PatchViewState(FNaniteView NaniteView, inout ViewState InOutView)` — Fill ViewState using data from a NaniteView
- L1132-1136 _function_ `float GetProjectedEdgeLengthAtDepth(float InLength, float ViewZ, FNaniteView NaniteView)`
- L1138-1146 _function_ `float GetdViewPosdXY(FNaniteView InView, float InSvPositionZ, bool bInv=false)`
- L1148-1159 _function_ `void WriteDispatchArgsSWHW(RWBuffer<uint> RasterizerArgsSWHW, uint ArgsOffset, uint NumClustersSW, uint NumClustersHW)`
- L1161-1192 _function_ `void WriteRasterizerArgsSWHW(RWBuffer<uint> RasterizerArgsSWHW, uint ArgsOffset, uint NumClustersSW, uint NumClustersHW)`
- L1196-1215 _function_ `float4x4 LoadNaniteHierarchyAssemblyTransform(uint HierarchyBufferOffset, uint TransformIndex)` _[#if COMPILER_SUPPORTS_HLSL2021]_
- L1217-1236 _function_ `float4x4 LoadNaniteAssemblyTransform(uint TransformIndex)` _[#if COMPILER_SUPPORTS_HLSL2021]_
- L1238-1250 _function_ `float4x4 InverseNaniteAssemblyTransform(float4x4 Input)` _[#if COMPILER_SUPPORTS_HLSL2021]_

#### Top-level macro invocations (1)

- L320 _macro_call_ `HLSL_STATIC_ASSERT(sizeof(FInstanceDynamicData) == 132, "Unexpected size of FInstanceDynamicData. Update WaveReadLaneAt to reflect changes.")` _[#if FEATURE_LEVEL >= FEATURE_LEVEL_SM6 \|\| PLATFORM_SUPPORTS_SM6_0_WAVE_OPERATIONS]_

### `Shaders/Private/Nanite/NaniteDebugViews.usf` (Private)

- lines: 337; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../SceneData.ush`, L5 `../DeferredShadingCommon.ush`, L6 `../SplineMeshCommon.ush`, L8 `NaniteDataDecode.ush`, L9 `NaniteAttributeDecode.ush`, L10 `NaniteVertexFetch.ush`, L11 `NaniteVertexDeformation.ush`, L12 `NaniteEditorCommon.ush`

#### Macros (#define, 1)

- L37 `#define SOBEL_WIREFRAME_FILTER_ONLY 0`

#### Entry points (1)

- L135-335 _entry_ `void ExportDebugViewPS( in float4 SvPosition : SV_Position, out float4 OutColor : SV_Target0, out float OutDepth : SV_Depth )` — stage: **pixel (from C++ binding)** — C++: `FExportDebugViewPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteVisualize.cpp:358)

#### Structs / classes (1)

- L106-114 _struct_ **`FNaniteMaterialDebugViewInfo`** `struct FNaniteMaterialDebugViewInfo`
  - L108 _member_ `uint InstructionCountVS;`
  - L109 _member_ `uint InstructionCountPS;`
  - L110 _member_ `uint InstructionCountCS;`
  - L111 _member_ `uint LWCComplexityVS;`
  - L112 _member_ `uint LWCComplexityPS;`
  - L113 _member_ `uint LWCComplexityCS;`

#### Global resources (textures / buffers / samplers) (8)

- L14 _resource_ `Texture2D<UlongType> VisBuffer64;`
- L16 _resource_ `Texture2DMS<float, MSAA_SAMPLE_COUNT> SceneDepth;` _[#if MSAA_SAMPLE_COUNT > 1]_
- L16 _resource_ `Texture2DMS<float, MSAA_SAMPLE_COUNT> SceneDepth;` _[#if MSAA_SAMPLE_COUNT > 1]_
- L18 _resource_ `Texture2D<float> SceneDepth;` _[#if !(MSAA_SAMPLE_COUNT > 1)]_
- L20 _resource_ `Texture2D<uint> ShadingMask;`
- L21 _resource_ `ByteAddressBuffer DebugViewData;`
- L23 _resource_ `ByteAddressBuffer ShadingBinData;`
- L34 _resource_ `ByteAddressBuffer StreamingDeficitData;`

#### Global parameters (uniforms) (6)

- L26 _parameter_ `uint4 ViewRect;` — .xy = min, .zw = max
- L28 _parameter_ `float InvShaderBudget;`
- L29 _parameter_ `float3 SelectionColor;`
- L30 _parameter_ `float3 OverlayIntensityColor;`
- L32 _parameter_ `uint DebugViewMode;`
- L35 _parameter_ `float4 StreamingDeficitColors[NUM_LOD_COLORATION_COLORS];`

#### Functions (2)

- L39-104 _function_ `float3 ApplyWireframeFilter(uint2 PixelPosXY, uint DepthInt, float3 WireColor)`
- L116-133 _function_ `FNaniteMaterialDebugViewInfo ReadMaterialDebugViewInfo(uint ShadingBin)`

### `Shaders/Private/Nanite/NaniteDepthDecode.usf` (Private)

- lines: 69; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../SceneData.ush`, L5 `../DeferredShadingCommon.ush`, L6 `../HTileEncoding.ush`, L7 `../VelocityCommon.ush`, L8 `NaniteDataDecode.ush`, L9 `NaniteAttributeDecode.ush`

#### Entry points (2)

- L27-60 _entry_ `[numthreads(8, 8, 1)] void DepthDecode(uint2 GroupId : SV_GroupID, uint ThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FDepthDecodeCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteVisualize.cpp:286) _[#if PLATFORM_SUPPORTS_HTILE_LOOKUP]_
- L64-67 _entry_ `[numthreads(8, 8, 1)] void DepthDecode(uint3 PixelPos : SV_DispatchThreadID, uint ThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FDepthDecodeCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteVisualize.cpp:286) _[#if !(PLATFORM_SUPPORTS_HTILE_LOOKUP)]_

#### Global resources (textures / buffers / samplers) (5)

- L16 _resource_ `Texture2D<float> SceneDepth;` _[#if PLATFORM_SUPPORTS_HTILE_LOOKUP]_
- L18 _resource_ `Texture2D<uint> ShadingMask;` _[#if PLATFORM_SUPPORTS_HTILE_LOOKUP]_
- L20 _resource_ `StructuredBuffer<uint> SceneHTileBuffer;` _[#if PLATFORM_SUPPORTS_HTILE_LOOKUP]_
- L22 _resource_ `RWTexture2D<float> SceneZDecoded;` _[#if PLATFORM_SUPPORTS_HTILE_LOOKUP]_
- L23 _resource_ `RWTexture2D<uint4> SceneZLayout;` _[#if PLATFORM_SUPPORTS_HTILE_LOOKUP]_

#### Global parameters (uniforms) (2)

- L13 _parameter_ `uint4 ViewRect;` _[#if PLATFORM_SUPPORTS_HTILE_LOOKUP]_
- L14 _parameter_ `uint4 HTileConfig;` _[#if PLATFORM_SUPPORTS_HTILE_LOOKUP]_

### `Shaders/Private/Nanite/NaniteDepthExport.usf` (Private)

- lines: 240; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../SceneData.ush`, L5 `../DeferredShadingCommon.ush`, L6 `../VariableRateShading/VRSShadingRateCommon.ush`, L7 `../HTileEncoding.ush`, L8 `../VelocityCommon.ush`, L9 `NaniteVertexDeformation.ush`, L13 `NaniteDataDecode.ush` [PLATFORM_SUPPORTS_HTILE_LOOKUP], L14 `NaniteAttributeDecode.ush` [PLATFORM_SUPPORTS_HTILE_LOOKUP], L15 `NaniteVertexFetch.ush` [PLATFORM_SUPPORTS_HTILE_LOOKUP]

#### Entry points (2)

- L70-224 _entry_ `[numthreads(HTILE_PIXELS_PER_TILE_WIDE, HTILE_PIXELS_PER_TILE_TALL, 1)] void DepthExport(uint2 GroupId : SV_GroupID, uint ThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FDepthExportCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteComposition.cpp:241) _[#if PLATFORM_SUPPORTS_HTILE_LOOKUP]_
- L235-238 _entry_ `[numthreads(8, 8, 1)] void DepthExport(uint3 PixelPos : SV_DispatchThreadID)` — stage: **compute** — C++: `FDepthExportCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteComposition.cpp:241) _[#if !(PLATFORM_SUPPORTS_HTILE_LOOKUP)]_

#### Global resources (textures / buffers / samplers) (7)

- L36 _resource_ `Texture2D<UlongType> VisBuffer64;` _[#if PLATFORM_SUPPORTS_HTILE_LOOKUP]_
- L38 _resource_ `RWStructuredBuffer<uint> SceneHTile;` _[#if PLATFORM_SUPPORTS_HTILE_LOOKUP]_
- L39 _resource_ `RWTexture2D<float> SceneDepth;` _[#if PLATFORM_SUPPORTS_HTILE_LOOKUP]_
- L40 _resource_ `RWTexture2D<uint> SceneStencil;` _[#if PLATFORM_SUPPORTS_HTILE_LOOKUP]_
- L42 _resource_ `RWTexture2D<float4> Velocity;` _[#if PLATFORM_SUPPORTS_HTILE_LOOKUP]_
- L45 _resource_ `RWTexture2D<uint> ShadingMask;` _[#if PLATFORM_SUPPORTS_HTILE_LOOKUP && SHADING_MASK_EXPORT]_
- L47 _resource_ `StructuredBuffer<FNaniteRasterBinMeta> RasterBinMeta;` _[#if PLATFORM_SUPPORTS_HTILE_LOOKUP]_

#### Global parameters (uniforms) (5)

- L17-24 _parameter_ `MAX_OCCUPANCY DISABLE_TARGET_OCCUPANCY_WARNING uint4 DepthExportConfig;` _[#if PLATFORM_SUPPORTS_HTILE_LOOKUP]_
- L25 _parameter_ `uint4 ViewRect;` _[#if PLATFORM_SUPPORTS_HTILE_LOOKUP]_
- L26 _parameter_ `uint bWriteCustomStencil;` _[#if PLATFORM_SUPPORTS_HTILE_LOOKUP]_
- L27 _parameter_ `uint MeshPassIndex;` _[#if PLATFORM_SUPPORTS_HTILE_LOOKUP]_
- L28 _parameter_ `uint RegularMaterialRasterBinCount;` _[#if PLATFORM_SUPPORTS_HTILE_LOOKUP]_

#### Functions (1)

- L49-68 _function_ `uint EncodeTileMinMaxDepth(float MinDepth, float MaxDepth, uint PlatformConfig)` _[#if PLATFORM_SUPPORTS_HTILE_LOOKUP]_

### `Shaders/Private/Nanite/NaniteDice.ush` (Private)

- lines: 356; parse: all-branches
- includes: L5 `NaniteRasterizationCommon.ush`, L6 `NaniteTessellation.ush`

#### Macros (#define, 1)

- L10 `#define NANITE_TESSELLATION_DICE_USE_LDS 1` _[#if NANITE_TESSELLATION]_
- L3 #pragma `once`

#### Structs / classes (2)

- L52-136 _struct_ **`FDiceTask`** `struct FDiceTask` _[#if NANITE_TESSELLATION]_
  - L54 _member_ `FRaster Raster;` _[#if NANITE_TESSELLATION]_
  - L55 _member_ `FMaterialShader Shader;` _[#if NANITE_TESSELLATION]_
  - L56 _member_ `uint PixelValue;` _[#if NANITE_TESSELLATION]_
  - L57 _member_ `uint2 VisualizeValues;` _[#if NANITE_TESSELLATION]_
  - L58 _member_ `float4 UVDensities;` _[#if NANITE_TESSELLATION]_
  - L59 _member_ `bool bReverseWinding;` _[#if NANITE_TESSELLATION]_
  - L61 _member_ `FNaniteTransformedVert Vert;` _[#if NANITE_TESSELLATION]_
  - L62 _member_ `FTessellatedPatch TessellatedPatch;` _[#if NANITE_TESSELLATION]_
  - L64 _member_ `uint4 Encoded;` _[#if NANITE_TESSELLATION]_
  - L65 _member_ `uint PatchData;` _[#if NANITE_TESSELLATION]_
  - L68 _member_ `float3 CachedPackedSubpixelPosition;` — Vertex cache _[#if NANITE_TESSELLATION]_
  - L70 _method_ `void Init( float3 TessFactors, uint3 VertIndexes, uint TriIndex )` _[#if NANITE_TESSELLATION]_
  - L82 _method_ `FDiceTask CreateChild( uint ParentLaneIndex )` _[#if NANITE_TESSELLATION]_
  - L122 _method_ `void CacheToLDS()` _[#if NANITE_TESSELLATION]_
  - L135 _method_proto_ `void RunChild( inout FDiceTask ParentTask, bool bActive, uint LocalItemIndex )` _[#if NANITE_TESSELLATION]_
- L288-298 _struct_ **`FClusterSplitTask`** `struct FClusterSplitTask` _[#if NANITE_TESSELLATION]_
  - L290 _member_ `FTessellatedPatch TessellatedPatch;` _[#if NANITE_TESSELLATION]_
  - L292 _member_ `uint4 Encoded;` _[#if NANITE_TESSELLATION]_
  - L294 _method_proto_ `void Init( float3 TessFactors, uint VisibleClusterIndex, uint TriIndex )` _[#if NANITE_TESSELLATION]_
  - L296 _method_proto_ `FClusterSplitTask CreateChild( uint ParentLaneIndex )` _[#if NANITE_TESSELLATION]_
  - L297 _method_proto_ `void RunChild( inout FClusterSplitTask ParentTask, bool bActive, uint LocalItemIndex )` _[#if NANITE_TESSELLATION]_

#### groupshared (2)

- L49 _groupshared_ `groupshared float4 GroupPointPackedClip[ THREADGROUP_SIZE ];` — TODO: Convert to PackedClip ? _[#if NANITE_TESSELLATION]_
- L50 _groupshared_ `groupshared float4 GroupNormalPackedClip[ THREADGROUP_SIZE ];` _[#if NANITE_TESSELLATION]_

#### Functions (5)

- L12-47 _function_ `void RasterizeDicedTri( FRasterTri Tri, FRaster Raster, FMaterialShader Shader, uint PixelValue, uint2 VisualizeValues )` _[#if NANITE_TESSELLATION]_
- L141-286 _function_ `void FDiceTask::RunChild( inout FDiceTask ParentTask, bool bActive, uint LocalItemIndex )` (scope `FDiceTask`) _[#if NANITE_TESSELLATION]_
- L300-308 _function_ `void FClusterSplitTask::Init( float3 TessFactors, uint VisibleClusterIndex, uint TriIndex )` (scope `FClusterSplitTask`) _[#if NANITE_TESSELLATION]_
- L310-316 _function_ `FClusterSplitTask FClusterSplitTask::CreateChild( uint ParentLaneIndex )` (scope `FClusterSplitTask`) _[#if NANITE_TESSELLATION]_
- L318-354 _function_ `void FClusterSplitTask::RunChild( inout FClusterSplitTask ParentTask, bool bActive, uint LocalItemIndex )` (scope `FClusterSplitTask`) _[#if NANITE_TESSELLATION]_

### `Shaders/Private/Nanite/NaniteEditorCommon.ush` (Private)

- lines: 58; parse: all-branches
- includes: L3 `../BinarySearch.ush`, L5 `NaniteDataDecode.ush`, L6 `NaniteAttributeDecode.ush`

#### Global resources (textures / buffers / samplers) (2)

- L8 _resource_ `ByteAddressBuffer MaterialHitProxyTable;`
- L11 _resource_ `Buffer<uint> EditorSelectedHitProxyIds;` _[#if USE_EDITOR_SHADERS]_

#### Global parameters (uniforms) (1)

- L12 _parameter_ `uint NumEditorSelectedHitProxyIds;` _[#if USE_EDITOR_SHADERS]_

#### Functions (2)

- L15-33 _function_ `uint GetHitProxySearchId(FInstanceSceneData InstanceData, FVisibleCluster VisibleCluster, uint TriIndex)`
- L35-57 _function_ `bool IsInstanceSelected(FInstanceSceneData InstanceData, FVisibleCluster VisibleCluster, uint TriIndex)`

### `Shaders/Private/Nanite/NaniteEmitShadow.usf` (Private)

- lines: 113; parse: all-branches
- includes: L3 `../Common.ush`

#### Entry points (4)

- L15-48 _entry_ `void EmitShadowMapPS( in float4 SvPosition : SV_Position, out float OutDepth : SV_Depth )` — stage: **pixel (from C++ binding)** — C++: `FEmitShadowMapPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/Nanite.cpp:118)
- L58-69 _entry_ `void EmitCubemapShadowVS( in uint VertexID : SV_VertexID, out FEmitCubemapShadowVSOut Output)` — stage: **vertex (from C++ binding)** — C++: `FEmitCubemapShadowVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/Nanite.cpp:161)
- L77-92 _entry_ `[maxvertexcount(3)] void EmitCubemapShadowGS( triangle FEmitCubemapShadowVSOut Input[3], inout TriangleStream<FEmitCubemapShadowGSOut> OutStream)` — stage: **geometry** — C++: `FEmitCubemapShadowGS` SF_Geometry via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/Nanite.cpp:182)
- L94-112 _entry_ `void EmitCubemapShadowPS( in float4 SvPosition : SV_Position, out float OutDepth : SV_Depth )` — stage: **pixel (from C++ binding)** — C++: `FEmitCubemapShadowPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/Nanite.cpp:202)

#### Structs / classes (2)

- L50-56 _struct_ **`FEmitCubemapShadowVSOut`** `struct FEmitCubemapShadowVSOut`
  - L52 _member_ `float4 Position : SV_Position;`
  - L54 _member_ `uint RTIndex : SV_RenderTargetArrayIndex;` _[#if USE_GEOMETRY_SHADER == 0]_
- L71-75 _struct_ **`FEmitCubemapShadowGSOut`** `struct FEmitCubemapShadowGSOut`
  - L73 _member_ `float4 Position : SV_Position;`
  - L74 _member_ `uint RTIndex : SV_RenderTargetArrayIndex;`

#### Global resources (textures / buffers / samplers) (1)

- L5 _resource_ `Texture2D<uint> DepthBuffer;`

#### Global parameters (uniforms) (5)

- L7 _parameter_ `int2 SourceOffset;`
- L8 _parameter_ `float ViewToClip22;`
- L9 _parameter_ `float DepthBias;`
- L10 _parameter_ `uint CubemapFaceIndex;`
- L13 _parameter_ `uint ShadowMapID;` — VSM

### `Shaders/Private/Nanite/NaniteExportGBuffer.usf` (Private)

- lines: 378; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../SceneData.ush`, L5 `../VelocityCommon.ush`, L6 `../DeferredShadingCommon.ush`, L7 `../VariableRateShading/VRSShadingRateCommon.ush`, L8 `../BRDF.ush`, L9 `NaniteDataDecode.ush`, L10 `NaniteAttributeDecode.ush`, L11 `NaniteVertexFetch.ush`, L12 `NaniteEditorCommon.ush`, L13 `NaniteVertexDeformation.ush`

#### Entry points (6)

- L46-68 _entry_ `void MarkStencilPS( in float4 SvPosition : SV_Position, out float OutDepth : SV_Depth )` — stage: **pixel (from C++ binding)** — C++: `FNaniteMarkStencilPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteComposition.cpp:58)
- L70-157 _entry_ `void EmitSceneDepthPS( in float4 SvPosition : SV_Position, out uint OutShadingMask : SV_Target0, out float4 OutVelocity : SV_Target1, out float OutDepth : SV_Depth )` — stage: **pixel (from C++ binding)** — C++: `FEmitSceneDepthPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteComposition.cpp:113)
- L161-185 _entry_ `void EmitSceneStencilPS( in float4 SvPosition : SV_Position, out float OutDepth : SV_Depth )` — stage: **pixel (from C++ binding)** — C++: `FEmitSceneStencilPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteComposition.cpp:145) _[#if SHADING_MASK_LOAD]_
- L189-236 _entry_ `void EmitCustomDepthStencilPS ( in float4 SvPosition : SV_Position , out uint2 OutStencil : SV_Target0 , out float OutDepth : SV_Depth )` — stage: **pixel (from C++ binding)** — C++: `FEmitCustomDepthStencilPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteComposition.cpp:186)
- L276-322 _entry_ `void EmitHitProxyIdPS( in float4 SvPosition : SV_Position, out float4 OutHitProxyId : SV_Target0, out float OutDepth : SV_Depth )` — stage: **pixel (from C++ binding)** — C++: `FEmitHitProxyIdPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteEditor.cpp:76)
- L329-377 _entry_ `void EmitEditorSelectionDepthPS( float4 SvPosition : SV_Position , out float4 OutOverlay : SV_Target0 , out float OutDepth : SV_Depth )` — stage: **pixel (from C++ binding)** — C++: `FEmitEditorSelectionDepthPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteEditor.cpp:95) — This shader is used to output depth (and stencil) for both editor selection outlines and visualize level instances. Additionally, it is used to output editor overlay colors.

#### Global resources (textures / buffers / samplers) (6)

- L23 _resource_ `Texture2D<UlongType> VisBuffer64;`
- L25 _resource_ `Texture2D<uint> ShadingMask;` _[#if SHADING_MASK_LOAD]_
- L27 _resource_ `StructuredBuffer<FNaniteRasterBinMeta> RasterBinMeta;`
- L30 _resource_ `Texture2D<float> CustomDepth;` — These are only used for custom depth/stencil output
- L31 _resource_ `Texture2D<uint2> CustomStencil;`
- L241 _resource_ `Texture2D< uint > DepthBuffer;`

#### Global parameters (uniforms) (11)

- L15 _parameter_ `uint DummyZero;` — TODO: Remove me
- L16 _parameter_ `uint StencilClear;`
- L17 _parameter_ `uint StencilDecal;`
- L18 _parameter_ `uint bWriteCustomStencil;` — only used to repurpose EmitSceneDepthStencilPS for custom depth/stencil where possible
- L19 _parameter_ `uint MeshPassIndex;`
- L20 _parameter_ `uint RegularMaterialRasterBinCount;`
- L21 _parameter_ `int4 ViewRect;`
- L238 _parameter_ `float ViewToClip22;`
- L239 _parameter_ `float DepthBias;`
- L324 _parameter_ `float2 OutputToInputScale;`
- L325 _parameter_ `float2 OutputToInputBias;`

#### Functions (2)

- L33-44 _function_ `uint GetCustomStencilValue(FPrimitiveSceneData PrimitiveData)`
- L243-274 _function_ `void EmitShadowMapPS( in float4 SvPosition : SV_Position, out float OutDepth : SV_Depth )` — sv-semantics

### `Shaders/Private/Nanite/NaniteFastClear.usf` (Private)

- lines: 61; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../SceneData.ush`, L5 `../DeferredShadingCommon.ush`, L6 `../HTileEncoding.ush`, L9 `/Platform/Private/RTWriteMaskLookup.ush` [defined(OVERRIDE_RTWRITEMASKPROCESSING_USH)], L12 `NaniteDataDecode.ush`, L13 `NaniteAttributeDecode.ush`

#### Entry points (1)

- L20-60 _entry_ `[numthreads(8, 8, 1)] void VisualizeClearTilesCS(uint2 GroupId : SV_GroupID, uint ThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FVisualizeClearTilesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteShading.cpp:365)

#### Global resources (textures / buffers / samplers) (2)

- L17 _resource_ `RWByteAddressBuffer OutCMaskBuffer;`
- L18 _resource_ `RWTexture2D<uint> OutVisualized;`

#### Global parameters (uniforms) (1)

- L15 _parameter_ `uint4 ViewRect;`

### `Shaders/Private/Nanite/NaniteHZBCull.ush` (Private)

- lines: 704; parse: all-branches
- includes: L7 `../Common.ush`, L8 `../HZB.ush`

#### Macros (#define, 3)

- L5 `#define USE_HZB_HALF_TYPE 1`
- L11 `#define PLATFORM_SPECIFIC_ISOLATE ISOLATE` _[#if !defined(PLATFORM_SPECIFIC_ISOLATE)]_
- L461 `#define EVAL_POINTS(PC0, PC1) MinW = min3(MinW, PC0.w, PC1.w); MaxW = max3(MaxW, PC0.w, PC1.w); PlanesMin = min3(PlanesMin, float4(PC0.xy, -PC0.xy) - PC0.w, float4(PC1.xy, -PC1.xy) - PC1.w); float2 PS0 = PC0.xy / PC0.w; float2 PS1 ...` (8 lines)
- L3 #pragma `once`; L503 #undef `EVAL_POINTS`

#### Structs / classes (2)

- L16-25 _struct_ **`FFrustumCullData`** `struct FFrustumCullData`
  - L18 _member_ `float3 RectMin;`
  - L19 _member_ `float3 RectMax;`
  - L21 _member_ `bool bCrossesFarPlane;`
  - L22 _member_ `bool bCrossesNearPlane;`
  - L23 _member_ `bool bFrustumSideCulled;`
  - L24 _member_ `bool bIsVisible;`
- L27-37 _struct_ **`FScreenRect`** `struct FScreenRect`
  - L29 _member_ `int4 Pixels;`
  - L30 _member_ `bool bOverlapsPixelCenter;`
  - L33 _member_ `int4 HZBTexels;` — For HZB sampling
  - L34 _member_ `int HZBLevel;`
  - L36 _member_ `float Depth;`

#### Global resources (textures / buffers / samplers) (1)

- L14 _resource_ `Texture2DArray< half > HZBTextureArray;`

#### Functions (24)

- L40-69 _function_ `int MipLevelForRect( int4 RectPixels, int DesiredFootprintPixels )` — Rect is inclusive [Min.xy, Max.xy]
- L71-107 _function_ `FScreenRect GetScreenRect( int4 ViewRect, float3 CullRectMin, float3 CullRectMax, int DesiredFootprintPixels )`
- L109-112 _function_ `FScreenRect GetScreenRect( int4 ViewRect, FFrustumCullData Cull, int DesiredFootprintPixels )`
- L116-123 _function_ `float4 LoadHZBRow4(float4 XCoords, float YCoord, float MipLevel)` _[#if !COMPILER_SUPPORTS_GATHER_LOD_RED]_
- L125-132 _function_ `float4 LoadHZBRow4(float4 XCoords, float YCoord, float MipLevel, float ArrayIndex)` _[#if !COMPILER_SUPPORTS_GATHER_LOD_RED]_
- L135-193 _function_ `float GetMinDepthFromHZB(FScreenRect Rect, bool bSample4x4)`
- L195-201 _function_ `bool IsVisibleHZB( FScreenRect Rect, bool bSample4x4 )`
- L203-263 _function_ `float GetMinDepthFromHZBArray(FScreenRect Rect, bool bSample4x4, float ArrayIndex)`
- L265-271 _function_ `bool IsVisibleHZBArray( FScreenRect Rect, bool bSample4x4, int ArrayIndex)`
- L273-332 _function_ `bool IsVisibleHZB( FScreenRect Rect, float3 PlaneHZB )`
- L335-350 _function_ `uint GetCubeFaceIndex( float3 Dir )`
- L353-366 _function_ `float4 GetCubeFacePlane( float3 Dir )` — Normalized cube [-1,1]
- L368-385 _function_ `float4 GetDominantFacePlane( float3 ViewOrigin, float3 BoundsCenter, float3 BoundsExtent )`
- L387-412 _function_ `float3 GetFacePlaneHZB( float3 ViewOriginLocal, float4x4 ClipToLocal, float3 BoundsCenter, float3 BoundsExtent )`
- L414-442 _function_ `FFrustumCullData BoxCullFrustumOrtho(float3 Center, float3 Extent, float4x4 LocalToWorld, float4x4 WorldToClip, bool bNearClip, bool bSkipFrustumCull)`
- L444-540 _function_ `FFrustumCullData BoxCullFrustumPerspective(float3 Center, float3 Extent, float4x4 LocalToWorld, float4x4 WorldToClip, float4x4 ViewToClip, bool bSkipFrustumCull)`
- L543-558 _function_ `FFrustumCullData BoxCullFrustum( float3 Center, float3 Extent, float4x4 LocalToWorld, float4x4 WorldToClip, float4x4 ViewToClip, bool bIsOrtho, bool bNearClip, bool bSkipFrustumCull )` — Splitting the transform in two generates much better code on DXC when WorldToClip is scalar.
- L560-563 _function_ `FFrustumCullData BoxCullFrustum(float3 Center, float3 Extent, float4x4 LocalToClip, float4x4 ViewToClip, bool bIsOrtho, bool bNearClip, bool bSkipFrustumCull)`
- L565-586 _function_ `float2 ProjectSphere( float x, float z, float r, float ResultScale )`
- L589-595 _function_ `float4 SphereToScreenRect( float3 Center, float Radius, float4x4 ViewToClip )` — [ Mara & Morgan 2013, "2D Polyhedral Bounds of a Clipped, Perspective-Projected 3D Sphere" ]
- L598-628 _function_ `float2 ProjectSphereNearClip( float x, float z, float r, float ResultScale, float ZNear )` — Assumes we have already handled the z+r < ZNear case
- L632-638 _function_ `float4 SphereToScreenRectNearClip( float3 Center, float Radius, float4x4 ViewToClip, float ZNear )` — [ Mara & Morgan 2013, "2D Polyhedral Bounds of a Clipped, Perspective-Projected 3D Sphere" ]
- L640-646 _function_ `float4 SphereToScreenRectOrtho( float3 Center, float Radius, float4x4 ViewToClip )`
- L648-704 _function_ `FFrustumCullData SphereCullFrustum(float3 Center, float Radius, float4x4 ViewToClip, float ZNear, bool bNearClip, bool bSkipFrustumCull)`

### `Shaders/Private/Nanite/NaniteHierarchyTraversal.ush` (Private)

- lines: 428; parse: all-branches
- includes: L5 `NaniteDataDecode.ush`, L6 `NaniteHierarchyTraversalCommon.ush`, L8 `../Common.ush`, L9 `../WaveOpUtil.ush`, L10 `../ComputeShaderUtils.ush`

#### Macros (#define, 1)

- L17 `#define CHECK_AND_TRIM_CLUSTER_COUNT 0` _[#if !defined(CHECK_AND_TRIM_CLUSTER_COUNT)]_
- L3 #pragma `once`

#### Global resources (textures / buffers / samplers) (3)

- L45 _resource_ `RWStructuredBuffer<FQueueState> QueueState;` _[#if !(NANITE_HIERARCHY_TRAVERSAL_TYPE == NANITE_CULLING_TYPE_PERSISTENT_NODES_AND_CLUSTERS)]_
- L49 _resource_ `Buffer<uint> CurrentNodeIndirectArgs;` _[#if NANITE_HIERARCHY_TRAVERSAL_TYPE == NANITE_CULLING_TYPE_NODES]_
- L50 _resource_ `RWBuffer<uint> NextNodeIndirectArgs;` _[#if NANITE_HIERARCHY_TRAVERSAL_TYPE == NANITE_CULLING_TYPE_NODES]_

#### Global parameters (uniforms) (2)

- L43 _parameter_ `RWCoherentStructuredBuffer(FQueueState) QueueState;` _[#if NANITE_HIERARCHY_TRAVERSAL_TYPE == NANITE_CULLING_TYPE_PERSISTENT_NODES_AND_CLUSTERS]_
- L51 _parameter_ `uint NodeLevel;` _[#if NANITE_HIERARCHY_TRAVERSAL_TYPE == NANITE_CULLING_TYPE_NODES]_

#### groupshared (11)

- L22 _groupshared_ `groupshared uint2 GroupNodeData[NANITE_MAX_BVH_NODES_PER_GROUP];` _[#if GROUP_NODE_SIZE == 2]_
- L28 _groupshared_ `groupshared uint3 GroupNodeData[NANITE_MAX_BVH_NODES_PER_GROUP];` _[#if !(GROUP_NODE_SIZE == 2) && GROUP_NODE_SIZE == 3]_
- L34 _groupshared_ `groupshared uint4 GroupNodeData[NANITE_MAX_BVH_NODES_PER_GROUP];` _[#if !(GROUP_NODE_SIZE == 2) && !(GROUP_NODE_SIZE == 3) && GROUP_NODE_SIZE == 4]_
- L54 _groupshared_ `groupshared uint GroupNumCandidateNodes;`
- L55 _groupshared_ `groupshared uint GroupCandidateNodesOffset;`
- L57 _groupshared_ `groupshared int GroupNodeCount;`
- L58 _groupshared_ `groupshared uint GroupNodeBatchStartIndex;`
- L59 _groupshared_ `groupshared uint GroupNodeMask;`
- L61 _groupshared_ `groupshared uint GroupClusterBatchStartIndex;`
- L62 _groupshared_ `groupshared uint GroupClusterBatchReadySize;`
- L370 _groupshared_ `groupshared uint GroupReadOffset;` _[#if NANITE_HIERARCHY_TRAVERSAL_TYPE == NANITE_CULLING_TYPE_NODES]_

#### Functions (11)

- L23 _function_ `uint4 GetGroupNodeData(uint NodeIndex)` _[#if GROUP_NODE_SIZE == 2]_
- L24 _function_ `void SetGroupNodeData(uint NodeIndex, uint4 Data)` _[#if GROUP_NODE_SIZE == 2]_
- L29 _function_ `uint4 GetGroupNodeData(uint NodeIndex)` _[#if !(GROUP_NODE_SIZE == 2) && GROUP_NODE_SIZE == 3]_
- L30 _function_ `void SetGroupNodeData(uint NodeIndex, uint4 Data)` _[#if !(GROUP_NODE_SIZE == 2) && GROUP_NODE_SIZE == 3]_
- L35 _function_ `uint4 GetGroupNodeData(uint NodeIndex)` _[#if !(GROUP_NODE_SIZE == 2) && !(GROUP_NODE_SIZE == 3) && GROUP_NODE_SIZE == 4]_
- L36 _function_ `void SetGroupNodeData(uint NodeIndex, uint4 Data)` _[#if !(GROUP_NODE_SIZE == 2) && !(GROUP_NODE_SIZE == 3) && GROUP_NODE_SIZE == 4]_
- L68-189 _function_ `template<typename FNaniteTraversalCallback> void ProcessNodeBatch(uint BatchSize, uint GroupIndex, uint QueueStateIndex)` _[#if NANITE_HIERARCHY_TRAVERSAL_TYPE == NANITE_CULLING_TYPE_PERSISTENT_NODES_AND_CLUSTERS \|\| NANITE_HIERARCHY_TRAVERSAL_TYPE == NANITE_CULLING_TYPE_NODES]_
- L195-212 _function_ `template<typename FNaniteTraversalCallback> void ProcessClusterBatch(uint BatchStartIndex, uint BatchSize, uint GroupIndex)` _[#if NANITE_HIERARCHY_TRAVERSAL_TYPE == NANITE_CULLING_TYPE_PERSISTENT_NODES_AND_CLUSTERS \|\| NANITE_HIERARCHY_TRAVERSAL_TYPE == NANITE_CULLING_TYPE_CLUSTERS]_
- L250-364 _function_ `template<typename FNaniteTraversalCallback> void PersistentNodeAndClusterCull(uint GroupIndex, uint QueueStateIndex)` _[#if NANITE_HIERARCHY_TRAVERSAL_TYPE == NANITE_CULLING_TYPE_PERSISTENT_NODES_AND_CLUSTERS]_
- L371-410 _function_ `template<typename FNaniteTraversalCallback> void NodeCull(uint GroupID, uint GroupIndex, uint QueueStateIndex)` _[#if NANITE_HIERARCHY_TRAVERSAL_TYPE == NANITE_CULLING_TYPE_NODES]_
- L416-425 _function_ `template<typename FNaniteTraversalCallback> void ClusterCull(uint GroupID, uint GroupIndex, uint QueueStateIndex)` _[#if NANITE_HIERARCHY_TRAVERSAL_TYPE == NANITE_CULLING_TYPE_CLUSTERS]_

### `Shaders/Private/Nanite/NaniteHierarchyTraversalCommon.ush` (Private)

- lines: 26; parse: all-branches
- includes: L5 `/Engine/Shared/NaniteDefinitions.h`
- L3 #pragma `once`

#### Structs / classes (2)

- L7-14 _struct_ **`FQueuePassState`** `struct FQueuePassState`
  - L9 _member_ `uint ClusterBatchReadOffset;` — Offset in batches
  - L10 _member_ `uint ClusterWriteOffset;` — Offset in individual clusters
  - L11 _member_ `uint NodeReadOffset;`
  - L12 _member_ `uint NodeWriteOffset;`
  - L13 _member_ `int NodeCount;` — Can temporarily be conservatively higher
- L16-21 _struct_ **`FQueueState`** `struct FQueueState`
  - L18 _member_ `uint TotalClusters;`
  - L19 _member_ `uint AssemblyTransformsWriteOffset;`
  - L20 _member_ `FQueuePassState PassState[2];`

#### Global parameters (uniforms) (1)

- L23 _parameter_ `uint MaxCandidateClusters;`

#### Functions (1)

- L25 _function_ `uint GetMaxClusterBatches()`

### `Shaders/Private/Nanite/NaniteInstanceCulling.usf` (Private)

- lines: 451; parse: per-group
- includes: L6 `../Common.ush`, L7 `../SceneData.ush`, L8 `../WaveOpUtil.ush`, L9 `../ComputeShaderUtils.ush`, L10 `../VirtualShadowMaps/VirtualShadowMapPageOverlap.ush`, L11 `../VirtualShadowMaps/VirtualShadowMapPageCacheCommon.ush`, L13 `NaniteCullingCommon.ush`, L14 `NaniteCulling.ush`, L15 `NaniteDataDecode.ush`, L16 `NaniteHZBCull.ush`, L17 `NaniteWritePixel.ush`, L19 `../SceneCulling/SceneCulling.ush`

#### Macros (#define, 1)

- L4 `#define USE_HZB_SHARED_SAMPLERS 0`

#### Entry points (1)

- L177-450 _entry_ `[numthreads(64, 1, 1)] void InstanceCull( uint3 GroupId : SV_GroupID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FInstanceCull_CS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteCullRaster.cpp:904)

#### Global resources (textures / buffers / samplers) (11)

- L142 _resource_ `StructuredBuffer<FInstanceDraw> InInstanceDraws;`
- L143 _resource_ `Buffer<uint> InOccludedInstancesArgs;`
- L147 _resource_ `Buffer<uint> InInstanceWorkArgs;` _[#if INSTANCE_CULL_USE_WORK_GROUP_BUFFER]_
- L148 _resource_ `StructuredBuffer<FInstanceCullingGroupWork> InInstanceWorkGroups;` _[#if INSTANCE_CULL_USE_WORK_GROUP_BUFFER]_
- L151 _resource_ `StructuredBuffer<FViewDrawGroup> InViewDrawRanges;` — These paths are coupled for the time being _[#if INSTANCE_CULL_USE_WORK_GROUP_BUFFER]_
- L156 _resource_ `StructuredBuffer<uint> InPrimitiveFilterBuffer;` _[#if PRIMITIVE_FILTER]_
- L159 _resource_ `RWStructuredBuffer<FInstanceDraw> OutOccludedInstances;`
- L160 _resource_ `RWBuffer<uint> OutOccludedInstancesArgs;`
- L161 _resource_ `RWByteAddressBuffer OutCandidateNodes;`
- L162 _resource_ `RWStructuredBuffer<FQueueState> OutQueueState;`
- L165 _resource_ `RWStructuredBuffer<FNaniteStats> OutStatsBuffer;` _[#if DEBUG_FLAGS]_

#### Global parameters (uniforms) (4)

- L138 _parameter_ `uint NumInstances;`
- L139 _parameter_ `uint NumViews;`
- L140 _parameter_ `uint IsExplicitDraw;`
- L146 _parameter_ `uint MaxInstanceWorkGroups;` _[#if INSTANCE_CULL_USE_WORK_GROUP_BUFFER]_

#### Functions (2)

- L22-130 _function_ `MAX_OCCUPANCY DISABLE_TARGET_OCCUPANCY_WARNING bool IsPrimitiveShown(FPrimitiveSceneData PrimitiveData, uint RenderFlags, bool bIsShadowPass)` _[#if VIRTUAL_TEXTURE_TARGET]_
- L169-175 _function_ `void WriteOccludedInstance(uint ViewId, uint InstanceId)`

### `Shaders/Private/Nanite/NaniteInstanceHierarchyCulling.usf` (Private)

- lines: 367; parse: all-branches
- includes: L6 `../Common.ush`, L7 `../SceneData.ush`, L8 `../WaveOpUtil.ush`, L9 `../ComputeShaderUtils.ush`, L10 `../SceneCulling/SceneCulling.ush`, L11 `../WorkGroupLoadBalancer.ush`, L13 `NaniteCullingCommon.ush`, L14 `NaniteCulling.ush`, L15 `NaniteDataDecode.ush`, L16 `NaniteHZBCull.ush`

#### Macros (#define, 1)

- L4 `#define USE_HZB_SHARED_SAMPLERS 0`

#### Entry points (5)

- L228-245 _entry_ `[numthreads(64, 1, 1)] void InstanceHierarchyCellChunkCull_CS(uint3 GroupId : SV_GroupID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FInstanceHierarchyCellChunkCull_CS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteCullRaster.cpp:698) _[#if defined(InstanceHierarchyCellChunkCull_CS)]_
- L251-287 _entry_ `[numthreads(64, 1, 1)] void InstanceHierarchyChunkCull_CS(uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `FInstanceHierarchyChunkCull_CS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteCullRaster.cpp:712) _[#if defined(InstanceHierarchyChunkCull_CS)]_
- L296-312 _entry_ `[numthreads(64, 1, 1)] void AppendUncullableInstanceWork(uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `FInstanceHierarchyAppendUncullable_CS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteCullRaster.cpp:748) — One thread per uncullable chunk in the X dimension * View draw groups in the Y dimensions.
- L317-349 _entry_ `[numthreads(1, 1, 1)] void InitArgs()` — stage: **compute** — C++: `FInitInstanceHierarchyArgs_CS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteCullRaster.cpp:798)
- L356-364 _entry_ `[numthreads(1, 1, 1)] void InstanceHierarchySanitizeInstanceArgsCS()` — stage: **compute** — C++: `FInstanceHierarchySanitizeInstanceArgs_CS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteCullRaster.cpp:773) _[#if defined(InstanceHierarchySanitizeInstanceArgsCS)]_

#### Global resources (textures / buffers / samplers) (13)

- L19 _resource_ `RWStructuredBuffer<FNaniteStats> OutStatsBuffer;` _[#if DEBUG_FLAGS]_
- L23 _resource_ `RWStructuredBuffer<FOccludedChunkDraw> OutOccludedChunkDraws;` — Occluded chunks fed back to post-pass.
- L24 _resource_ `RWBuffer<uint> OutOccludedChunkArgs;`
- L40 _resource_ `StructuredBuffer<FViewDrawGroup> InViewDrawRanges;`
- L44 _resource_ `RWStructuredBuffer<FInstanceCullingGroupWork> OutInstanceWorkGroups;` — Yet another format TODO: unify/remove paths
- L48 _resource_ `RWBuffer<uint> OutInstanceWorkArgs;` — TODO: this used to be the same arg as the post pass instances from the instance culling main pass, but due to a weird bug they are separate, for now. Output indirect dispatch args for the following instance culling pass (x will contain all the groups, which matches the array count above).
- L97 _resource_ `Buffer<uint> InOccludedChunkArgs;` _[#if CULLING_PASS == CULLING_PASS_OCCLUSION_POST]_
- L98 _resource_ `StructuredBuffer<FOccludedChunkDraw> InOccludedChunkDraws;` _[#if CULLING_PASS == CULLING_PASS_OCCLUSION_POST]_
- L100 _resource_ `StructuredBuffer<FCellChunkDraw> ParentInfoBuffer;` _[#if !(CULLING_PASS == CULLING_PASS_OCCLUSION_POST)]_
- L101 _resource_ `StructuredBuffer<uint> InGroupIds;` _[#if !(CULLING_PASS == CULLING_PASS_OCCLUSION_POST)]_
- L314 _resource_ `RWBuffer< uint > OutInstanceWorkArgs0;`
- L315 _resource_ `RWBuffer< uint > OutInstanceWorkArgs1;`
- L353 _resource_ `RWBuffer< uint > InOutInstanceWorkArgs;` _[#if defined(InstanceHierarchySanitizeInstanceArgsCS)]_

#### Global parameters (uniforms) (8)

- L49 _parameter_ `uint MaxInstanceWorkGroups;`
- L50 _parameter_ `uint bAllowStaticGeometryPath;`
- L102 _parameter_ `uint NumGroupIds;` _[#if !(CULLING_PASS == CULLING_PASS_OCCLUSION_POST)]_
- L103 _parameter_ `uint NumParentInfos;` _[#if !(CULLING_PASS == CULLING_PASS_OCCLUSION_POST)]_
- L291 _parameter_ `uint NumViewDrawGroups;` — Store the uncullable in the regular cell draw array, at the end.
- L292 _parameter_ `uint UncullableItemChunksOffset;`
- L293 _parameter_ `uint UncullableNumItemChunks;`
- L354 _parameter_ `uint GroupWorkArgsMaxCount;` _[#if defined(InstanceHierarchySanitizeInstanceArgsCS)]_

#### Functions (4)

- L27-38 _function_ `void WriteOccludedChunk(uint ChunkId, uint ViewGroupId, uint OccludedViewMask)`
- L52-80 _function_ `bool AppendInstanceCullingWorkGroup(uint ItemChunksOffset, uint ViewGroupId, uint ActiveViewMask, bool bIsStaticSceneGeometry)`
- L82-94 _function_ `void UpdateChunkPreCullStat(uint NumChunks, bool bShouldUpdate)`
- L106-224 _function_ `void ProcessChunk(uint ChunkId, uint ViewGroupId, uint InOccludedViewMask)`

### `Shaders/Private/Nanite/NanitePackedNaniteView.ush` (Private)

- lines: 70; parse: all-branches
- L3 #pragma `once`

#### Structs / classes (1)

- L6-69 _struct_ **`FPackedNaniteView`** `struct FPackedNaniteView` — Counterpart to Nanite::FPackedView in NaniteShared.h
  - L8 _member_ `float4x4 SVPositionToTranslatedWorld;`
  - L9 _member_ `float4x4 ViewToTranslatedWorld;`
  - L11 _member_ `float4x4 TranslatedWorldToView;`
  - L12 _member_ `float4x4 TranslatedWorldToClip;`
  - L13 _member_ `float4x4 ViewToClip;`
  - L14 _member_ `float4x4 ClipToRelativeWorld;`
  - L16 _member_ `float4x4 PrevTranslatedWorldToView;`
  - L17 _member_ `float4x4 PrevTranslatedWorldToClip;`
  - L18 _member_ `float4x4 PrevViewToClip;`
  - L19 _member_ `float4x4 PrevClipToRelativeWorld;`
  - L21 _member_ `int4 ViewRect;`
  - L22 _member_ `float4 ViewSizeAndInvSize;`
  - L23 _member_ `float4 ClipSpaceScaleOffset;`
  - L24 _member_ `float4 MaterialCacheUnwrapMinAndInvSize;`
  - L25 _member_ `float4 MaterialCachePageOffsetAndInvSize;`
  - L26 _member_ `float3 PreViewTranslationHigh;`
  - L27 _member_ `float ViewOriginHighX;`
  - L28 _member_ `float3 PrevPreViewTranslationHigh;`
  - L29 _member_ `float ViewOriginHighY;`
  - L30 _member_ `float3 PrevPreViewTranslationLow;`
  - L31 _member_ `float CullingViewMinRadiusTestFactorSq;`
  - L32 _member_ `float3 ViewOriginLow;`
  - L33 _member_ `float ViewOriginHighZ;`
  - L34 _member_ `float3 CullingViewOriginTranslatedWorld;`
  - L35 _member_ `float RangeBasedCullingDistance;`
  - L36 _member_ `float3 ViewForward;`
  - L37 _member_ `float NearPlane;`
  - L39 _member_ `float4 TranslatedGlobalClipPlane;` — Not actually used unless project setting is enabled
  - L41 _member_ `float3 PreViewTranslationLow;`
  - L42 _member_ `float CullingViewScreenMultipleSq;`
  - L44 _member_ `float2 LODScales;`
  - L45 _member_ `uint InstanceOcclusionQueryMask;`
  - L46 _member_ `uint StreamingPriorityCategory_AndFlags;`
  - L48 _member_ `int4 TargetLayerIdX_AndMipLevelY_AndNumMipLevelsZ;`
  - L50 _member_ `int4 HZBTestViewRect;`
  - L52 _member_ `float4 FirstPersonTransform0;` — 0,0; 0,1; 0,2; 1,0
  - L53 _member_ `float4 FirstPersonTransform1;` — 1,1; 1,2; 2,0; 2,1
  - L54 _member_ `float4 PrevFirstPersonTransform0;` — 0,0; 0,1; 0,2; 1,0
  - L55 _member_ `float4 PrevFirstPersonTransform1;` — 1,1; 1,2; 2,0; 2,1
  - L56 _member_ `float4 InvFirstPersonTransform0;` — 0,0; 0,1; 0,2; 1,0
  - L57 _member_ `float4 InvFirstPersonTransform1;` — 1,1; 1,2; 2,0; 2,1
  - L58 _member_ `float3 PrevPreViewTranslationHZBHigh;`
  - L59 _member_ `float FirstPersonTransform2;` — 2,2
  - L60 _member_ `float3 PrevPreViewTranslationHZBLow;`
  - L61 _member_ `float PrevFirstPersonTransform2;` — 2,2
  - L62 _member_ `float2 DynamicDepthCullRange;`
  - L63 _member_ `float InvFirstPersonTransform2;` — 2,2
  - L64 _member_ `uint LightingChannelMask;`
  - L65 _member_ `int SceneRendererPrimaryViewId;`
  - L66 _member_ `uint FrameIndex;`
  - L67 _member_ `float Pad0;`
  - L68 _member_ `float Pad1;`

### `Shaders/Private/Nanite/NanitePrimitiveFilter.usf` (Private)

- lines: 74; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../SceneData.ush`, L5 `../WaveOpUtil.ush`, L6 `../ComputeShaderUtils.ush`, L7 `../BinarySearch.ush`, L9 `NaniteDataDecode.ush`

#### Entry points (1)

- L31-73 _entry_ `[numthreads(64, 1, 1)] void PrimitiveFilter ( uint3 GroupId : SV_GroupID, uint GroupIndex : SV_GroupIndex )` — stage: **compute** — C++: `FPrimitiveFilter_CS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteCullRaster.cpp:614)

#### Global resources (textures / buffers / samplers) (3)

- L16 _resource_ `Buffer<uint> HiddenPrimitivesList;` _[#if HAS_HIDDEN_PRIMITIVES_LIST]_
- L21 _resource_ `Buffer<uint> ShowOnlyPrimitivesList;` _[#if HAS_SHOW_ONLY_PRIMITIVES_LIST]_
- L24 _resource_ `RWStructuredBuffer<uint> PrimitiveFilterBuffer;`

#### Global parameters (uniforms) (4)

- L11 _parameter_ `uint NumPrimitives;`
- L12 _parameter_ `uint HiddenFilterFlags;`
- L15 _parameter_ `uint NumHiddenPrimitives;` _[#if HAS_HIDDEN_PRIMITIVES_LIST]_
- L20 _parameter_ `uint NumShowOnlyPrimitives;` _[#if HAS_SHOW_ONLY_PRIMITIVES_LIST]_

#### Functions (1)

- L26-29 _function_ `uint GetNaniteFilterFlags(const FPrimitiveSceneData PrimitiveData)`

### `Shaders/Private/Nanite/NanitePrintStats.usf` (Private)

- lines: 727; parse: all-branches
- includes: L3 `../Common.ush`, L6 `../ShaderPrint.ush` [SHADER_PRINT_STATS], L9 `NaniteCulling.ush`, L560 `/Engine/Shared/VirtualShadowMapDefinitions.h` [defined(ExtractVSMPerformanceFeedback)]

#### Macros (#define, 6)

- L12 `#define VIRTUAL_TEXTURE_TARGET 0` _[#if !defined(VIRTUAL_TEXTURE_TARGET)]_
- L564 `#define THREADGROUP_SIZE 64` _[#if defined(ExtractVSMPerformanceFeedback)]_
- L565 `#define GROUP_COUNTER_ENTRIES_SINGLE_PAGE 64` _[#if defined(ExtractVSMPerformanceFeedback)]_
- L566 `#define GROUP_COUNTER_ENTRIES_MULTI_PAGE 128` _[#if defined(ExtractVSMPerformanceFeedback)]_
- L567 `#define GROUP_COUNTER_ENTRIES (GROUP_COUNTER_ENTRIES_SINGLE_PAGE + GROUP_COUNTER_ENTRIES_MULTI_PAGE)` _[#if defined(ExtractVSMPerformanceFeedback)]_
- L568 `#define GROUP_COUNTER_SIZE (GROUP_COUNTER_ENTRIES * VSM_NPF_SIZEOF_ENTRY)` _[#if defined(ExtractVSMPerformanceFeedback)]_

#### Entry points (6)

- L67-417 _entry_ `[numthreads(1, 1, 1)] void PrintStats()` — stage: **compute** — C++: `FPrintStatsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/Nanite.cpp:266) _[#if SHADER_PRINT_STATS]_
- L423-444 _entry_ `[numthreads(1, 1, 1)] void CalculateClusterIndirectArgs()` — stage: **compute** — C++: `FCalculateClusterIndirectArgsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteCullRaster.cpp:7262) _[#if defined(CalculateClusterIndirectArgs)]_
- L450-528 _entry_ `[numthreads(1, 1, 1)] void CalculateRasterStats()` — stage: **compute** — C++: `FCalculateRasterStatsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteCullRaster.cpp:7335) _[#if SHADER_CALCULATE_STATS]_
- L530-554 _entry_ `[numthreads(1, 1, 1)] void CalculateShadingStats()` — stage: **compute** — C++: `FCalculateShadingStatsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/Nanite.cpp:231) _[#if SHADER_CALCULATE_STATS]_
- L571-655 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void ExtractVSMPerformanceFeedback( uint DispatchThreadIndex : SV_DispatchThreadID, uint GroupIndex : SV_GroupIndex, uint GroupThreadIndex : SV_GroupThreadID )` — stage: **compute** — C++: `FExtractVSMPerformanceFeedbackCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteCullRaster.cpp:7191) _[#if defined(ExtractVSMPerformanceFeedback)]_
- L669-725 _entry_ `[numthreads(64, 1, 1)] void CalculateClusterStats( uint DispatchThreadIndex : SV_DispatchThreadID, uint GroupIndex : SV_GroupIndex )` — stage: **compute** — C++: `FCalculateClusterStatsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteCullRaster.cpp:7374) _[#if SHADER_CALCULATE_CLUSTER_STATS]_

#### Global resources (textures / buffers / samplers) (15)

- L23 _resource_ `StructuredBuffer<FQueueState> QueueState;`
- L24 _resource_ `Buffer<uint> MainPassRasterizeArgsSWHW;`
- L25 _resource_ `Buffer<uint> PostPassRasterizeArgsSWHW;`
- L27 _resource_ `StructuredBuffer<FNaniteRasterBinMeta> MainPassRasterBinMeta;`
- L29 _resource_ `StructuredBuffer<FNaniteRasterGroupMeta> MainPassRasterGroupMeta;`
- L30 _resource_ `StructuredBuffer<FNaniteRasterGroupMeta> PostPassRasterGroupMeta;`
- L32 _resource_ `ByteAddressBuffer ShadingDispatchArgs;`
- L34 _resource_ `ByteAddressBuffer ShadingBinData;`
- L35 _resource_ `StructuredBuffer<FNaniteShadingBinStats> ShadingBinStats;`
- L37 _resource_ `StructuredBuffer<FNaniteStats> InStatsBuffer;`
- L38 _resource_ `RWStructuredBuffer<FNaniteStats> OutStatsBuffer;`
- L40 _resource_ `RWBuffer<uint> OutClusterStatsArgs;`
- L41 _resource_ `RWStructuredBuffer<uint> OutClusterStats;`
- L42 _resource_ `StructuredBuffer<uint> InClusterStats;`
- L562 _resource_ `RWStructuredBuffer<uint> OutPerformanceFeedbackBuffer;` _[#if defined(ExtractVSMPerformanceFeedback)]_

#### Global parameters (uniforms) (6)

- L15 _parameter_ `uint PackedClusterSize;`
- L17 _parameter_ `uint NumMainPassRasterBins;`
- L18 _parameter_ `uint NumMainPassRasterGroups;`
- L19 _parameter_ `uint NumPostPassRasterGroups;`
- L20 _parameter_ `uint NumShadingBins;`
- L21 _parameter_ `uint NumShadingGroups;`

#### groupshared (8)

- L569 _groupshared_ `groupshared uint LDS[GROUP_COUNTER_SIZE];` _[#if defined(ExtractVSMPerformanceFeedback)]_
- L661 _groupshared_ `groupshared uint GroupNumTris;` _[#if SHADER_CALCULATE_CLUSTER_STATS]_
- L662 _groupshared_ `groupshared uint GroupNumVerts;` _[#if SHADER_CALCULATE_CLUSTER_STATS]_
- L663 _groupshared_ `groupshared uint GroupNumBricks;` _[#if SHADER_CALCULATE_CLUSTER_STATS]_
- L664 _groupshared_ `groupshared uint GroupNumBrickThreads;` _[#if SHADER_CALCULATE_CLUSTER_STATS]_
- L665 _groupshared_ `groupshared uint GroupIndexDataSize;` _[#if SHADER_CALCULATE_CLUSTER_STATS]_
- L666 _groupshared_ `groupshared uint GroupPositionDataSize;` _[#if SHADER_CALCULATE_CLUSTER_STATS]_
- L667 _groupshared_ `groupshared uint GroupAttribDataSize;` _[#if SHADER_CALCULATE_CLUSTER_STATS]_

#### Functions (1)

- L46-65 _function_ `void PrintLeftAlign(inout FShaderPrintContext Context, uint Value)` _[#if SHADER_PRINT_STATS]_

### `Shaders/Private/Nanite/NaniteRasterBinning.usf` (Private)

- lines: 807; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../SceneData.ush`, L5 `../ViewData.ush`, L6 `../WaveOpUtil.ush`, L7 `../ComputeShaderUtils.ush`, L15 `NaniteAttributeDecode.ush`, L16 `NaniteTessellation.ush`

#### Macros (#define, 11)

- L9 `#define SPLIT_WORK_QUEUE (PATCHES)`
- L12 `#define NANITE_TESSELLATION PATCHES` _[#if !defined(NANITE_TESSELLATION)]_
- L18 `#define RASTER_BIN_INIT (RASTER_BIN_PASS == NANITE_RASTER_BIN_INIT)`
- L19 `#define RASTER_BIN_COUNT (RASTER_BIN_PASS == NANITE_RASTER_BIN_COUNT)`
- L20 `#define RASTER_BIN_SCATTER (RASTER_BIN_PASS == NANITE_RASTER_BIN_SCATTER)`
- L21 `#define RASTER_BIN_RESERVE (RASTER_BIN_PASS == NANITE_RASTER_BIN_RESERVE)`
- L22 `#define RASTER_BIN_DEPTHBLOCK (RASTER_BIN_PASS == NANITE_RASTER_BIN_DEPTHBLOCK)`
- L23 `#define RASTER_BIN_FINALIZE (RASTER_BIN_PASS == NANITE_RASTER_BIN_FINALIZE)`
- L26 `#define VIRTUAL_TEXTURE_TARGET 0` _[#if !defined(VIRTUAL_TEXTURE_TARGET)]_
- L30 `#define FORCE_BATCHING 0` _[#if !defined(FORCE_BATCHING)]_
- L34 `#define DEPTH_BUCKETING 1` _[#if !defined(DEPTH_BUCKETING)]_

#### Entry points (6)

- L121-129 _entry_ `[numthreads(1, 1, 1)] void InitVisiblePatchesArgs()` — stage: **compute** — C++: `FInitVisiblePatchesArgsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteCullRaster.cpp:1125) _[#if NANITE_TESSELLATION]_
- L137-144 _entry_ `[numthreads(64, 1, 1)] void RasterGroupInit(uint RasterGroupIndex : SV_DispatchThreadID)` — stage: **compute** — C++: `FRasterGroupInit_CS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteCullRaster.cpp:1224) _[#if RASTER_BIN_INIT]_
- L160-172 _entry_ `[numthreads(64, 1, 1)] void RasterGroupReserve(uint RasterGroupIndex : SV_DispatchThreadID)` — stage: **compute** — C++: `FRasterGroupReserve_CS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteCullRaster.cpp:1248) _[#if !(RASTER_BIN_INIT) && RASTER_BIN_RESERVE]_
- L181-235 _entry_ `[numthreads(64, 1, 1)] void RasterGroupFinalize(uint RasterGroupIndex : SV_DispatchThreadID)` — stage: **compute** — C++: `FRasterBinFinalize_CS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteCullRaster.cpp:1296) _[#if !(RASTER_BIN_INIT) && !(RASTER_BIN_RESERVE) && RASTER_BIN_FINALIZE]_
- L240-263 _entry_ `[numthreads(64, 1, 1)] void RasterGroupDepthBlock(uint DepthBlockIndex : SV_GroupID, uint ThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FRasterGroupDepthBlock_CS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteCullRaster.cpp:1271) — TODO: Permute based on wave width for slightly better perf? _[#if !(RASTER_BIN_INIT) && !(RASTER_BIN_RESERVE) && !(RASTER_BIN_FINALIZE) && RASTER_BIN_DEPTHBLOCK]_
- L519-804 _entry_ `[numthreads(64, 1, 1)] void RasterBinBuild(uint RelativeClusterIndex : SV_DispatchThreadID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FRasterBinBuild_CS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteCullRaster.cpp:1203) _[#if !(RASTER_BIN_INIT) && !(RASTER_BIN_RESERVE) && !(RASTER_BIN_FINALIZE) && !(RASTER_BIN_DEPTHBLOCK)]_

#### Global resources (textures / buffers / samplers) (11)

- L42 _resource_ `RWStructuredBuffer<FNaniteRasterBinMeta> OutRasterBinMeta;`
- L43 _resource_ `RWStructuredBuffer<FNaniteRasterGroupMeta> OutRasterGroupMeta;`
- L44 _resource_ `RWStructuredBuffer<uint> OutDepthBuckets;`
- L150 _resource_ `RWStructuredBuffer<uint> OutRangeAllocator;` _[#if !(RASTER_BIN_INIT) && RASTER_BIN_RESERVE]_
- L151 _resource_ `RWBuffer<uint> OutRasterGroupArgsSWHW;` _[#if !(RASTER_BIN_INIT) && RASTER_BIN_RESERVE]_
- L179 _resource_ `RWBuffer<uint> OutRasterGroupArgsSWHW;` _[#if !(RASTER_BIN_INIT) && !(RASTER_BIN_RESERVE) && RASTER_BIN_FINALIZE]_
- L267 _resource_ `Buffer<uint> InClusterOffsetSWHW;` _[#if !(RASTER_BIN_INIT) && !(RASTER_BIN_RESERVE) && !(RASTER_BIN_FINALIZE) && !(RASTER_BIN_DEPTHBLOCK)]_
- L269 _resource_ `StructuredBuffer<uint2> InClusterCountSWHW;` _[#if !(RASTER_BIN_INIT) && !(RASTER_BIN_RESERVE) && !(RASTER_BIN_FINALIZE) && !(RASTER_BIN_DEPTHBLOCK)]_
- L270 _resource_ `StructuredBuffer<uint2> InTotalPrevDrawClusters;` _[#if !(RASTER_BIN_INIT) && !(RASTER_BIN_RESERVE) && !(RASTER_BIN_FINALIZE) && !(RASTER_BIN_DEPTHBLOCK)]_
- L277 _resource_ `RWBuffer<uint> OutRasterGroupArgsSWHW;` _[#if !(RASTER_BIN_INIT) && !(RASTER_BIN_RESERVE) && !(RASTER_BIN_FINALIZE) && !(RASTER_BIN_DEPTHBLOCK) && RASTER_BIN_SCATTER]_
- L278 _resource_ `RWStructuredBuffer<uint2> OutRasterBinData;` _[#if !(RASTER_BIN_INIT) && !(RASTER_BIN_RESERVE) && !(RASTER_BIN_FINALIZE) && !(RASTER_BIN_DEPTHBLOCK) && RASTER_BIN_SCATTER]_

#### Global parameters (uniforms) (10)

- L37 _parameter_ `uint MeshPassIndex;`
- L38 _parameter_ `uint MinSupportedWaveSize;`
- L39 _parameter_ `uint MaxVisiblePatches;`
- L40 _parameter_ `uint MaxClusterIndirections;`
- L135 _parameter_ `uint RasterGroupCount;` _[#if RASTER_BIN_INIT]_
- L148 _parameter_ `uint RasterGroupCount;` _[#if !(RASTER_BIN_INIT) && RASTER_BIN_RESERVE]_
- L176 _parameter_ `uint RasterGroupCount;` _[#if !(RASTER_BIN_INIT) && !(RASTER_BIN_RESERVE) && RASTER_BIN_FINALIZE]_
- L177 _parameter_ `uint FinalizeMode;` _[#if !(RASTER_BIN_INIT) && !(RASTER_BIN_RESERVE) && RASTER_BIN_FINALIZE]_
- L272 _parameter_ `uint bUsePrimOrMeshShader;` _[#if !(RASTER_BIN_INIT) && !(RASTER_BIN_RESERVE) && !(RASTER_BIN_FINALIZE) && !(RASTER_BIN_DEPTHBLOCK)]_
- L274 _parameter_ `uint RegularMaterialRasterBinCount;` _[#if !(RASTER_BIN_INIT) && !(RASTER_BIN_RESERVE) && !(RASTER_BIN_FINALIZE) && !(RASTER_BIN_DEPTHBLOCK)]_

#### Functions (17)

- L46-49 _function_ `FNaniteMaterialFlags GetRasterBinMaterialFlags(uint RasterBin)`
- L51-58 _function_ `uint GetRasterBinGroup(uint RasterBinIndex)`
- L60-63 _function_ `uint GetRasterBinDepthBlock(uint GroupIndex)`
- L65-70 _function_ `void InitRasterGroup(uint GroupIndex)`
- L72-75 _function_ `uint2 GetRasterGroupCount(uint GroupIndex)`
- L77-81 _function_ `uint GetRasterGroupCapacity(uint GroupIndex)`
- L83-86 _function_ `void SetRasterGroupOffset(uint GroupIndex, uint Offset)`
- L88-91 _function_ `uint GetRasterGroupOffset(uint GroupIndex)`
- L93-117 _function_ `uint GetRemappedRasterBinFromIndex( FNaniteView NaniteView, uint InRelativeMaterialIndex, uint InPrimitiveIndex, uint InRegularRasterBinCount, uint InRenderFlags, bool bFallbackRasterBin, bool bVoxel, bool bCurve, bool bIsDeforming)`
- L153-158 _function_ `uint AllocateRasterGroupRange(uint ClusterCount)` _[#if !(RASTER_BIN_INIT) && RASTER_BIN_RESERVE]_
- L281-290 _function_ `uint ExtractVertReuseBatchInfo(uint2 PackedData, uint BitOffset)` _[#if !(RASTER_BIN_INIT) && !(RASTER_BIN_RESERVE) && !(RASTER_BIN_FINALIZE) && !(RASTER_BIN_DEPTHBLOCK)]_
- L292-309 _function_ `uint DecodeVertReuseBatchInfo(FCluster Cluster, uint BatchInfoOffset, uint BatchIndex, bool bInlined)` _[#if !(RASTER_BIN_INIT) && !(RASTER_BIN_RESERVE) && !(RASTER_BIN_FINALIZE) && !(RASTER_BIN_DEPTHBLOCK)]_
- L312-352 _function_ `void IncrementRasterGroupCount(uint GroupIndex, bool bSoftware, uint BatchCount, uint FlatDepthBucket)` _[#if !(RASTER_BIN_INIT) && !(RASTER_BIN_RESERVE) && !(RASTER_BIN_FINALIZE) && !(RASTER_BIN_DEPTHBLOCK) && RASTER_BIN_COUNT]_
- L354-403 _function_ `uint AllocateRasterGroupCluster(uint GroupIndex, bool bSoftware, uint BatchCount, uint FlatDepthBucket)` _[#if !(RASTER_BIN_INIT) && !(RASTER_BIN_RESERVE) && !(RASTER_BIN_FINALIZE) && !(RASTER_BIN_DEPTHBLOCK) && !(RASTER_BIN_COUNT) && RASTER_BIN_SCATTER]_
- L406-494 _function_ `void ExportRasterGroup(uint RasterGroup, uint RasterBin, FNaniteMaterialFlags MaterialFlags, uint ClusterIndex, uint RangeStart, uint RangeEnd, uint BatchCount, uint BatchInfoOffset, FCluster Cluster, bool bBatchInfoInlined, bool bSoftware, uint DepthBucket)` _[#if !(RASTER_BIN_INIT) && !(RASTER_BIN_RESERVE) && !(RASTER_BIN_FINALIZE) && !(RASTER_BIN_DEPTHBLOCK)]_
- L496-512 _function_ `template< typename T, typename FFunction > void ScalarizeForEachMatching( T Value, FFunction Function )` _[#if !(RASTER_BIN_INIT) && !(RASTER_BIN_RESERVE) && !(RASTER_BIN_FINALIZE) && !(RASTER_BIN_DEPTHBLOCK)]_
- L514-517 _function_ `bool IsNaniteMaterialMergingAllowed(uint BinIndex, FNaniteMaterialFlags MaterialFlags)` _[#if !(RASTER_BIN_INIT) && !(RASTER_BIN_RESERVE) && !(RASTER_BIN_FINALIZE) && !(RASTER_BIN_DEPTHBLOCK)]_

### `Shaders/Private/Nanite/NaniteRasterClear.usf` (Private)

- lines: 62; parse: all-branches
- includes: L3 `../Common.ush`

#### Entry points (2)

- L32-47 _entry_ `[numthreads(8, 8, 1)] void RasterClear(uint3 TilePos : SV_DispatchThreadID)` — stage: **compute** — C++: `FRasterClearCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteCullRaster.cpp:578) _[#if RASTER_CLEAR_TILED]_
- L51-60 _entry_ `[numthreads(8, 8, 1)] void RasterClear(uint3 PixelPos : SV_DispatchThreadID)` — stage: **compute** — C++: `FRasterClearCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteCullRaster.cpp:578) _[#if !(RASTER_CLEAR_TILED)]_

#### Global resources (textures / buffers / samplers) (4)

- L6 _resource_ `RWTexture2D<uint> OutDepthBuffer;` _[#if RASTER_CLEAR_DEPTH]_
- L8 _resource_ `RWTexture2D<UlongType> OutVisBuffer64;` _[#if !(RASTER_CLEAR_DEPTH)]_
- L11 _resource_ `RWTexture2D<UlongType> OutDbgBuffer64;` _[#if RASTER_CLEAR_DEBUG]_
- L12 _resource_ `RWTexture2D<uint> OutDbgBuffer32;` _[#if RASTER_CLEAR_DEBUG]_

#### Global parameters (uniforms) (1)

- L15 _parameter_ `uint4 ClearRect;`

#### Functions (1)

- L17-28 _function_ `void ClearPixelPos(uint2 PixelPos)`

### `Shaders/Private/Nanite/NaniteRasterizationCommon.ush` (Private)

- lines: 728; parse: all-branches
- includes: L5 `../Common.ush`, L6 `../SceneData.ush`, L7 `../WaveOpUtil.ush`, L8 `NaniteRasterizer.ush`, L9 `NaniteAttributeDecode.ush`, L10 `../VirtualShadowMaps/VirtualShadowMapPageAccessCommon.ush`, L11 `../VirtualShadowMaps/VirtualShadowMapPageOverlap.ush`, L12 `NaniteWritePixel.ush`, L13 `NaniteCullingCommon.ush`, L21 `/Engine/Generated/Material.ush` [NANITE_MATERIAL_INCLUDES], L22 `NaniteVertexFactory.ush` [NANITE_MATERIAL_INCLUDES], L26 `NaniteTessellation.ush` [NANITE_TESSELLATION]

#### Macros (#define, 6)

- L16 `#define NANITE_MATERIAL_INCLUDES 1` _[#if !defined(NANITE_MATERIAL_INCLUDES)]_
- L30 `#define NANITE_TWO_SIDED 0` _[#if !defined(NANITE_TWO_SIDED)]_
- L33 `#define ENABLE_EARLY_Z_TEST (NANITE_PIXEL_PROGRAMMABLE)`
- L36 `#define ENABLE_FALLBACK_DISPLACEMENT (SHADOW_DEPTH_SHADER && ( FIXED_DISPLACEMENT_FALLBACK \|\| (NANITE_VERTEX_PROGRAMMABLE && USES_DISPLACEMENT && !NANITE_TESSELLATION) ))` (4 lines)
- L41 `#define MATERIAL_SHADER_HAS_DOMAIN (NANITE_TESSELLATION && (NANITE_VERTEX_PROGRAMMABLE \|\| NANITE_PIXEL_PROGRAMMABLE))`
- L42 `#define MATERIAL_SHADER_HAS_DISPLACEMENT (ENABLE_FALLBACK_DISPLACEMENT \|\| (MATERIAL_SHADER_HAS_DOMAIN && USES_DISPLACEMENT))`
- L3 #pragma `once`

#### Structs / classes (7)

- L45-58 _struct_ **`FRaster`** `struct FRaster` — State encompassing mapping a pixel position to memory address
  - L47 _member_ `float2 ViewportScale;`
  - L48 _member_ `float2 ViewportBias;`
  - L49 _member_ `int4 ScissorRect;`
  - L52 _member_ `uint2 pPage;` _[#if VIRTUAL_TEXTURE_TARGET]_
  - L53 _member_ `uint2 vPage;` _[#if VIRTUAL_TEXTURE_TARGET]_
  - L54 _member_ `float2 vTranslation;` _[#if VIRTUAL_TEXTURE_TARGET]_
  - L55 _member_ `bool bSinglePage;` _[#if VIRTUAL_TEXTURE_TARGET]_
  - L56 _member_ `uint ArrayIndex;` _[#if VIRTUAL_TEXTURE_TARGET]_
- L236-302 _struct_ **`TSlidingWindowVertexCache`** `template< typename FVertex > struct TSlidingWindowVertexCache` — Only works for WaveSize >= 32 and only efficient for == 32. A sliding window approach like this relies on the index buffer being constrained such that a triangle can't referance a vertex >= window size back from the largest seen index so far in the index buffer. In addition the WaveSize must be at least as large as the window so that vertices referenced by triangles in this wave must either be present in the cache from the previous iteration (Lane0 - Window) or  in this iteration. Since we constrain to 32 when building the clusters the WaveSize that makes sense is the matching 32. Larger WaveS
  - L239 _member_ `FVertex CachedVert;`
  - L240 _member_ `uint NumCached;`
  - L241 _member_ `bool bFirstPass;`
  - L243 _member_ `FVertex TriangleVerts[3];`
  - L244 _member_ `bool TriangleVertsRead[3];`
  - L246 _method_ `void Init()`
  - L253 _method_ `uint PullExisting( uint3 VertIndexes )` — Grab what's there for this triangle before updating cache. Otherwise cache would need to be double size.
  - L278 _method_ `uint PullRemaining( uint3 VertIndexes )`
- L305-311 _struct_ **`FNullTranslation`** `struct FNullTranslation`
  - L307 _method_ `bool operator()( inout FVisBufferPixel Pixel )`
- L313-371 _struct_ **`TNaniteWritePixel`** `template< typename FSoftwareShader, typename FPageTranslation = FNullTranslation > struct TNaniteWritePixel`
  - L316 _member_ `FRaster Raster;`
  - L317 _member_ `FSoftwareShader Shader;`
  - L318 _member_ `uint PixelValue;`
  - L319 _member_ `uint2 VisualizeValues;`
  - L320 _member_ `FPageTranslation PageTranslation;`
  - L322 _method_ `void operator()( uint2 PixelPos, float3 C, FRasterTri Tri )`
- L374-633 _struct_ **`FMaterialShader`** `struct FMaterialShader` _[#if NANITE_MATERIAL_INCLUDES]_
  - L376 _member_ `FNaniteView NaniteView;` _[#if NANITE_MATERIAL_INCLUDES]_
  - L377 _member_ `FPrimitiveSceneData PrimitiveData;` _[#if NANITE_MATERIAL_INCLUDES]_
  - L378 _member_ `FInstanceSceneData InstanceData;` _[#if NANITE_MATERIAL_INCLUDES]_
  - L379 _member_ `FInstanceDynamicData InstanceDynamicData;` _[#if NANITE_MATERIAL_INCLUDES]_
  - L380 _member_ `FCluster Cluster;` _[#if NANITE_MATERIAL_INCLUDES]_
  - L381 _member_ `FVisibleCluster VisibleCluster;` _[#if NANITE_MATERIAL_INCLUDES]_
  - L382 _member_ `FNaniteVertTransforms VertTransforms;` _[#if NANITE_MATERIAL_INCLUDES]_
  - L383 _member_ `FNaniteTransformedVert Verts[3];` _[#if NANITE_MATERIAL_INCLUDES]_
  - L384 _member_ `FMaterialVertexParameters VertexParameters;` _[#if NANITE_MATERIAL_INCLUDES]_
  - L387 _member_ `FNaniteMaterialDisplacementParams DisplacementParams;` _[#if NANITE_MATERIAL_INCLUDES && MATERIAL_SHADER_HAS_DISPLACEMENT]_
  - L388 _member_ `float DisplacementFadeSlope;` _[#if NANITE_MATERIAL_INCLUDES && MATERIAL_SHADER_HAS_DISPLACEMENT]_
  - L389 _member_ `float DisplacementFadeOffset;` _[#if NANITE_MATERIAL_INCLUDES && MATERIAL_SHADER_HAS_DISPLACEMENT]_
  - L392 _method_ `void InitVertexParameters(FNanitePostDeformVertex InputVert, float4x4 LocalToTranslatedWorld)` _[#if NANITE_MATERIAL_INCLUDES]_
  - L417 _method_ `void InitVertexParameters(FNanitePostDeformVertex InputVert)` _[#if NANITE_MATERIAL_INCLUDES]_
  - L423 _method_ `void GetCustomizedUVs(inout float2 OutCustomizedUVs[NUM_TEX_COORD_INTERPOLATORS])` _[#if NANITE_MATERIAL_INCLUDES && NANITE_PIXEL_PROGRAMMABLE && NUM_TEX_COORD_INTERPOLATORS > 0]_
  - L430 _method_ `float3 EvaluateWorldPositionOffset()` _[#if NANITE_MATERIAL_INCLUDES]_
  - L443 _method_ `void ApplyFirstPersonTransform(inout float3 TranslatedWorldPosition, float3x3 FirstPersonTransform)` _[#if NANITE_MATERIAL_INCLUDES]_
  - L452 _method_ `void ApplyFirstPersonTransform(inout float3 TranslatedWorldPosition)` _[#if NANITE_MATERIAL_INCLUDES]_
  - L458 _method_ `void InitDisplacement(FNaniteMaterialDisplacementParams InParams)` _[#if NANITE_MATERIAL_INCLUDES && MATERIAL_SHADER_HAS_DISPLACEMENT]_
  - L490 _method_ `bool ApplyFallbackDisplacement(inout FNanitePostDeformVertex InOutVert)` _[#if NANITE_MATERIAL_INCLUDES && MATERIAL_SHADER_HAS_DISPLACEMENT]_
  - L506 _method_ `float4 EvaluateDomain( float4 UVDensities, FBarycentrics Barycentrics )` _[#if NANITE_MATERIAL_INCLUDES && MATERIAL_SHADER_HAS_DOMAIN]_
  - L607 _method_ `bool EvaluatePixel( FBarycentrics Barycentrics, float4 SvPosition, bool bBackFace, inout FVisBufferPixel Pixel )` _[#if NANITE_MATERIAL_INCLUDES]_
- L665-679 _struct_ **`FCachedPageTable`** `struct FCachedPageTable` _[#if VIRTUAL_TEXTURE_TARGET && NANITE_LATE_VSM_PAGE_TRANSLATION]_
  - L667 _method_ `bool operator()( inout FVisBufferPixel Pixel )` _[#if VIRTUAL_TEXTURE_TARGET && NANITE_LATE_VSM_PAGE_TRANSLATION]_
- L683-699 _struct_ **`FFetchPageTable`** `struct FFetchPageTable`
  - L685 _member_ `uint MipLevel;`
  - L686 _member_ `FVirtualSMLevelOffset LevelOffset;`
  - L688 _method_ `bool operator()( inout FVisBufferPixel Pixel )`

#### groupshared (3)

- L143 _groupshared_ `groupshared uint GroupBaseVertIndex;`
- L144 _groupshared_ `groupshared uint2 GroupUsedVertMask;`
- L638 _groupshared_ `groupshared uint GroupVsmPageTableCache[NANITE_VSM_PAGE_TABLE_CACHE_DIM * NANITE_VSM_PAGE_TABLE_CACHE_DIM];` _[#if VIRTUAL_TEXTURE_TARGET && NANITE_LATE_VSM_PAGE_TRANSLATION]_

#### Functions (13)

- L60-66 _function_ `float4 CalculateSubpixelCoordinates( float2 ViewportScale, float2 ViewportBias, float4 PointClip )`
- L68-71 _function_ `float4 CalculateSubpixelCoordinates( FRaster Raster, float4 PointClip )`
- L73-79 _function_ `float3 GetPerspectiveCorrectBarycentrics( float3 C, float3 InvW )`
- L81-105 _function_ `FBarycentrics CalculateBarycentrics( FRasterTri Tri, float3 C, bool bPerspectiveCorrectDerivatives )`
- L107-118 _function_ `int FindNthSetBit( uint Mask, int Index )`
- L120-124 _function_ `int FindNthSetBit( uint2 Mask, int Index )`
- L132-141 _function_ `uint MaskedBitCount2( uint2 Bits, uint Index )`
- L147-226 _function_ `void DeduplicateVertIndexes( uint3 VertIndexes, uint GroupThreadIndex, bool bTriValid, out uint OutNumUniqueVerts, out uint OutLaneVertIndex, out uint3 OutCornerLaneIndexes )`
- L640-645 _function_ `void VsmPageTableStore(uint2 pPage, uint2 Coords)` _[#if VIRTUAL_TEXTURE_TARGET && NANITE_LATE_VSM_PAGE_TRANSLATION]_
- L647-652 _function_ `uint2 VsmPageTableLoad(uint2 Coords)` _[#if VIRTUAL_TEXTURE_TARGET && NANITE_LATE_VSM_PAGE_TRANSLATION]_
- L654-663 _function_ `void FetchAndCachePageTableEntry(FNaniteView NaniteView, uint2 vPageStart, uint2 vPageEnd, uint CacheIndex)` _[#if VIRTUAL_TEXTURE_TARGET && NANITE_LATE_VSM_PAGE_TRANSLATION]_
- L701-722 _function_ `uint2 GetVisualizeValues(uint AddValue, uint SubPatch, uint MicroTri)`
- L724-727 _function_ `uint2 GetVisualizeValues()`

### `Shaders/Private/Nanite/NaniteRasterizer.usf` (Private)

- lines: 3532; parse: last-branch (retry, +15 merged from all-branches pass)
- includes: L17 `NaniteVertexDeformation.ush` [IS_CURVE_RASTERIZER], L20 `NaniteRasterizationCommon.ush`, L21 `../VirtualShadowMaps/VirtualShadowMapPageAccessCommon.ush`, L22 `../VirtualShadowMaps/VirtualShadowMapPageOverlap.ush`, L24 `../MaterialCache/MaterialCacheCommon.ush` [MATERIAL_CACHE], L26 `../ComputeShaderUtils.ush`, L27 `../Random.ush`, L28 `../Matrices.ush`, L30 `NaniteCurveCommon.ush` [NANITE_CURVES], L34 `../ShaderPrint.ush` [NANITE_CURVES && NANITE_CURVES_DEBUG_DRAW], L38 `NaniteTessellation.ush` [NANITE_TESSELLATION], L39 `NaniteDice.ush` [NANITE_TESSELLATION], L47 `../ShaderBundleWorkGraphCommon.ush` [WORKGRAPH_NODE], L117 `/Engine/Public/RootConstants.ush`, L1122 `Voxel/Voxel.ush` [NANITE_VOXELS]

#### Macros (#define, 55)

- L4 `#define SHADOW_DEPTH_SHADER DEPTH_ONLY`
- L6 `#define SPLIT_WORK_QUEUE NANITE_TESSELLATION`
- L7 `#define ALLOW_SUBSTRATE_TREE 0`
- L8 `#define NANITE_CURVES_DEBUG_DRAW 0`
- L9 `#define NANITE_CURVES_SUBDIVISION_ENABLE 0`
- L10 `#define NANITE_CURVES_DITHERING 1`
- L12 `#define IS_CURVE_RASTERIZER (defined(RasterCurveDebug) \|\| defined(CurveTileCount) \|\| defined(CurveTileWrite))`
- L14 `#define NANITE_MATERIAL_INCLUDES 0` _[#if IS_CURVE_RASTERIZER]_
- L15 `#define NANITE_PIXEL_PROGRAMMABLE 0` _[#if IS_CURVE_RASTERIZER]_
- L16 `#define NANITE_CURVES 1` _[#if IS_CURVE_RASTERIZER]_
- L43 `#define WORKGRAPH_NODE 0` _[#if !defined(WORKGRAPH_NODE)]_
- L50 `#define CONSTANT_DIR_RECT 1`
- L51 `#define BRICK_TRACE_WORK_REDISTRIBUTION 1`
- L52 `#define BRICK_TRACE_APPROXIMATE_DIVIDE 1`
- L63 `#define NANITE_MESH_SHADER 0` _[#if !defined(NANITE_MESH_SHADER)]_
- L67 `#define NANITE_PRIM_SHADER 0` _[#if !defined(NANITE_PRIM_SHADER)]_
- L71 `#define NANITE_VERT_REUSE_BATCH 0` _[#if !defined(NANITE_VERT_REUSE_BATCH)]_
- L75 `#define NANITE_TWO_SIDED 0` _[#if !defined(NANITE_TWO_SIDED)]_
- L78 `#define NANITE_HW_RASTER_INTERPOLATE_DEPTH (DEPTH_ONLY)`
- L81 `#define THREADGROUP_SIZE 32` _[#if NANITE_VERT_REUSE_BATCH \|\| NANITE_VOXELS]_
- L83 `#define THREADGROUP_SIZE 64` _[#if !(NANITE_VERT_REUSE_BATCH \|\| NANITE_VOXELS)]_
- L87 `#define NANITE_TRIANGLES 1` _[#if NANITE_CURVES == 0 && NANITE_VOXELS == 0 && PATCHES == 0]_
- L89 `#define NANITE_TRIANGLES 0` _[#if !(NANITE_CURVES == 0 && NANITE_VOXELS == 0 && PATCHES == 0)]_
- L101 `#define NANITE_BINDLESS (UE_BINDLESS_ENABLED && SUPPORTS_BINDLESS_UNIFORM_BUFFER)`
- L102 `#define NANITE_BINDLESS_EXPORT (UE_BINDLESS_ENABLED && NANITE_PIXEL_PROGRAMMABLE)`
- L111 `#define NANITE_PLATFORM_RASTER_VERT_LOOP_HINT UNROLL` _[#if !defined(NANITE_PLATFORM_RASTER_VERT_LOOP_HINT)]_
- L114 `#define NANITE_PLATFORM_RASTER_STAGE_UNIFORMS_TO_LDS 0` _[#if !defined(NANITE_PLATFORM_RASTER_STAGE_UNIFORMS_TO_LDS)]_
- L302 `#define VERTEX_CACHE_SIZE 120` _[#if PATCHES]_
- L304 `#define VERTEX_CACHE_SIZE 256` _[#if !(PATCHES)]_
- L767 `#define LOCAL_TO_TRANSLATED_WORLD GroupLocalToTranslatedWorld` _[#if NANITE_TRIANGLES && !(NANITE_TESSELLATION) && !(NANITE_PIXEL_PROGRAMMABLE) && NANITE_PLATFORM_RASTER_STAGE_UNIFORMS_TO_LDS]_
- L768 `#define TRANSLATED_WORLD_TO_CLIP GroupTranslatedWorldToClip` _[#if NANITE_TRIANGLES && !(NANITE_TESSELLATION) && !(NANITE_PIXEL_PROGRAMMABLE) && NANITE_PLATFORM_RASTER_STAGE_UNIFORMS_TO_LDS]_
- L769 `#define FIRST_PERSON_TRANSFORM GroupFirstPersonTransform` _[#if NANITE_TRIANGLES && !(NANITE_TESSELLATION) && !(NANITE_PIXEL_PROGRAMMABLE) && NANITE_PLATFORM_RASTER_STAGE_UNIFORMS_TO_LDS]_
- L770 `#define VIEWPORT_SCALE GroupViewportScale` _[#if NANITE_TRIANGLES && !(NANITE_TESSELLATION) && !(NANITE_PIXEL_PROGRAMMABLE) && NANITE_PLATFORM_RASTER_STAGE_UNIFORMS_TO_LDS]_
- L771 `#define VIEWPORT_BIAS GroupViewportBias` _[#if NANITE_TRIANGLES && !(NANITE_TESSELLATION) && !(NANITE_PIXEL_PROGRAMMABLE) && NANITE_PLATFORM_RASTER_STAGE_UNIFORMS_TO_LDS]_
- L772 `#define SCISSOR_RECT GroupScissorRect` _[#if NANITE_TRIANGLES && !(NANITE_TESSELLATION) && !(NANITE_PIXEL_PROGRAMMABLE) && NANITE_PLATFORM_RASTER_STAGE_UNIFORMS_TO_LDS]_
- L774 `#define LOCAL_TO_TRANSLATED_WORLD InstanceDynamicData.LocalToTranslatedWorld` _[#if NANITE_TRIANGLES && !(NANITE_TESSELLATION) && !(NANITE_PIXEL_PROGRAMMABLE) && !(NANITE_PLATFORM_RASTER_STAGE_UNIFORMS_TO_LDS)]_
- L775 `#define TRANSLATED_WORLD_TO_CLIP NaniteView.TranslatedWorldToClip` _[#if NANITE_TRIANGLES && !(NANITE_TESSELLATION) && !(NANITE_PIXEL_PROGRAMMABLE) && !(NANITE_PLATFORM_RASTER_STAGE_UNIFORMS_TO_LDS)]_
- L776 `#define FIRST_PERSON_TRANSFORM NaniteView.FirstPersonTransform` _[#if NANITE_TRIANGLES && !(NANITE_TESSELLATION) && !(NANITE_PIXEL_PROGRAMMABLE) && !(NANITE_PLATFORM_RASTER_STAGE_UNIFORMS_TO_LDS)]_
- L777 `#define VIEWPORT_SCALE Raster.ViewportScale` _[#if NANITE_TRIANGLES && !(NANITE_TESSELLATION) && !(NANITE_PIXEL_PROGRAMMABLE) && !(NANITE_PLATFORM_RASTER_STAGE_UNIFORMS_TO_LDS)]_
- L778 `#define VIEWPORT_BIAS Raster.ViewportBias` _[#if NANITE_TRIANGLES && !(NANITE_TESSELLATION) && !(NANITE_PIXEL_PROGRAMMABLE) && !(NANITE_PLATFORM_RASTER_STAGE_UNIFORMS_TO_LDS)]_
- L779 `#define SCISSOR_RECT Raster.ScissorRect` _[#if NANITE_TRIANGLES && !(NANITE_TESSELLATION) && !(NANITE_PIXEL_PROGRAMMABLE) && !(NANITE_PLATFORM_RASTER_STAGE_UNIFORMS_TO_LDS)]_
- L1449 `#define EVAL_X01( _PointClip ) { const float4 Clip0 = ( _PointClip ); const float4 Clip1 = ( _PointClip ) + DeltaX; const float2 Screen0 = Clip0.xy / Clip0.w; const float2 Screen1 = Clip1.xy / Clip1.w; MinW = min3( MinW, Clip0.w, C ...` (11 lines) _[#if NANITE_VOXELS && !(CONSTANT_DIR_RECT)]_
- L2117 `#define USE_SEGMENT_TRIANGLE 1` _[#if NANITE_CURVES]_
- L2441 `#define HW_RASTERIZER (defined(HWRasterizePS) \|\| defined(CommonRasterizerVS) \|\| defined(HWRasterizeVS) \|\| defined(HWRasterizeMS) \|\| defined(HWRasterizePS))`
- L2445 `#define VERTEX_TO_TRIANGLE_MASKS (NANITE_PRIM_SHADER && (!DEPTH_ONLY \|\| NANITE_PIXEL_PROGRAMMABLE))` _[#if HW_RASTERIZER]_
- L2448 `#define NANITE_ALLOW_SV_BARYCENTRICS 1` _[#if HW_RASTERIZER && !defined(NANITE_ALLOW_SV_BARYCENTRICS)]_
- L2453 `#define BARYCENTRIC_MODE_NONE (!NANITE_PIXEL_PROGRAMMABLE)` _[#if HW_RASTERIZER]_
- L2454 `#define BARYCENTRIC_MODE_INTRINSICS (!BARYCENTRIC_MODE_NONE && (NANITE_MESH_SHADER \|\| NANITE_PRIM_SHADER) && COMPILER_SUPPORTS_BARYCENTRIC_INTRINSICS)` _[#if HW_RASTERIZER]_
- L2455 `#define BARYCENTRIC_MODE_SV_BARYCENTRICS (!BARYCENTRIC_MODE_NONE && NANITE_MESH_SHADER && NANITE_ALLOW_SV_BARYCENTRICS && !COMPILER_SUPPORTS_BARYCENTRIC_INTRINSICS)` _[#if HW_RASTERIZER]_
- L2456 `#define BARYCENTRIC_MODE_EXPORT (!BARYCENTRIC_MODE_NONE && !BARYCENTRIC_MODE_INTRINSICS && !BARYCENTRIC_MODE_SV_BARYCENTRICS)` _[#if HW_RASTERIZER]_
- L2471 `#define NANITE_MESH_SHADING_PER_PRIMITIVE_ATTRIBUTE MESH_SHADING_PER_PRIMITIVE_ATTRIBUTE` _[#if HW_RASTERIZER && NANITE_MESH_SHADER]_
- L2473 `#define NANITE_MESH_SHADING_PER_PRIMITIVE_ATTRIBUTE ` _[#if HW_RASTERIZER && !(NANITE_MESH_SHADER)]_
- L2486 `#define STORE_CLIP_IN_INTERPOLATOR (VIRTUAL_TEXTURE_TARGET \|\| NANITE_HW_RASTER_INTERPOLATE_DEPTH)` _[#if HW_RASTERIZER]_
- L2752 `#define NUM_VERTEX_MASKS ((NANITE_MAX_CLUSTER_VERTICES + 31)/32)` _[#if HW_RASTERIZER && NANITE_PRIM_SHADER]_
- L3475 `#define WIDTH_SCALE 1.0`
- L56 #pragma `message("UESHADERMETADATA_VERSION A6174FDD-04E8-4C49-A97C-18750449C462")`; L875 #undef `LOCAL_TO_TRANSLATED_WORLD`; L876 #undef `TRANSLATED_WORLD_TO_CLIP`; L877 #undef `FIRST_PERSON_TRANSFORM`; L878 #undef `VIEWPORT_SCALE`; L879 #undef `VIEWPORT_BIAS`; L880 #undef `SCISSOR_RECT`; L1473 #undef `EVAL_X01`; L2720 #pragma `argument(realtypes)`

#### Entry points (6)

- L2416-2439 _entry_ `[Shader("node")] [NodeLaunch("broadcasting")] [NodeMaxDispatchGrid(65535,1,1)] [numthreads(THREADGROUP_SIZE, 1, 1)] void MicropolyRasterize( uint DispatchThreadID : SV_DispatchThreadID, uint GroupID : SV_GroupID, uint GroupIndex : SV_GroupIndex , DispatchNodeInputRecord<FShaderBundleNodeRecord> InputRecord )` — stage: **node(broadcasting)** — C++: `FMicropolyRasterizeCS` SF_Compute via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/Nanite/NaniteCullRaster.cpp:1715) — C++: `FMicropolyRasterizeWG` SF_WorkGraphComputeNode via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/Nanite/NaniteCullRaster.cpp:1743) _[#if WORKGRAPH_NODE]_
- L2782-3012 _entry_ `PRIM_SHADER_OUTPUT_TRIANGLES PRIM_SHADER_PRIM_COUNT(1) PRIM_SHADER_VERT_COUNT(1) PRIM_SHADER_VERT_LIMIT(32) PRIM_SHADER_AMP_FACTOR(32) PRIM_SHADER_VERT_LIMIT(256) PRIM_SHADER_AMP_FACTOR(128) PRIM_SHADER_AMP_ENABLE PrimitiveOutput HWRasterizeVS(PrimitiveInput Input)` — stage: **vertex (from C++ binding)** — C++: `FHWRasterizeVS` SF_Vertex via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/Nanite/NaniteCullRaster.cpp:1911) _[#if HW_RASTERIZER && NANITE_PRIM_SHADER]_
- L3161-3222 _entry_ `VSOut HWRasterizeVS( uint VertexID : SV_VertexID, uint InstanceID : SV_InstanceID )` — stage: **vertex (from C++ binding)** — C++: `FHWRasterizeVS` SF_Vertex via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/Nanite/NaniteCullRaster.cpp:1911) _[#if HW_RASTERIZER && !(NANITE_PRIM_SHADER) && !(NANITE_MESH_SHADER)]_
- L3247-3469 _entry_ `MESH_SHADING_COMPATIBLE_PS_ENTRY_POINT void HWRasterizePS(VSOut In , PrimitiveAttributesPacked PrimitivePacked , bool bFrontFace : SV_IsFrontFace )` — stage: **pixel (from C++ binding)** — C++: `FHWRasterizePS` SF_Pixel via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/Nanite/NaniteCullRaster.cpp:2226) _[#if HW_RASTERIZER && NANITE_MESH_SHADER]_
- L3493-3501 _entry_ `[numthreads(GROUP_SIZE, 1, 1)] void CurveTileCount( uint DispatchThreadID : SV_DispatchThreadID, uint GroupID : SV_GroupID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FNaniteCurveTileCount` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteCurveRaster.inl:361) _[#if defined(CurveTileCount)]_
- L3522-3530 _entry_ `[numthreads(GROUP_SIZE, 1, 1)] void CurveTileWrite( uint DispatchThreadID : SV_DispatchThreadID, uint GroupID : SV_GroupID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FNaniteCurveTileWrite` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteCurveRaster.inl:362) _[#if defined(CurveTileWrite)]_

#### Structs / classes (14)

- L141-145 _struct_ **`FTriRange`** `struct FTriRange`
  - L143 _member_ `uint Start;`
  - L144 _member_ `uint Num;`
- L147-153 _struct_ **`FClusterRef`** `struct FClusterRef`
  - L149 _member_ `FTriRange TriRange;`
  - L150 _member_ `uint VisibleIndex;`
  - L151 _member_ `uint MaterialFlags;`
  - L152 _member_ `uint RasterBin;`
- L337-341 _struct_ **`FCachedVertex`** `struct FCachedVertex` _[#if NANITE_TRIANGLES]_
  - L339 _member_ `FNaniteTransformedVert TransformedVert;` _[#if NANITE_TRIANGLES]_
  - L340 _member_ `float4 PointSubpixelClip;` _[#if NANITE_TRIANGLES]_
- L1384-1388 _struct_ **`FBounds`** `struct FBounds` _[#if NANITE_VOXELS]_
  - L1386 _member_ `float3 Min;` _[#if NANITE_VOXELS]_
  - L1387 _member_ `float3 Max;` _[#if NANITE_VOXELS]_
- L1839-1845 _struct_ **`FCurveDDA`** `struct FCurveDDA` _[#if NANITE_CURVES]_
  - L1841 _member_ `float2 Coord;` _[#if NANITE_CURVES]_
  - L1842 _member_ `float2 DeltaDist;` _[#if NANITE_CURVES]_
  - L1843 _member_ `float2 Step;` _[#if NANITE_CURVES]_
  - L1844 _member_ `float2 SideDist;` _[#if NANITE_CURVES]_
- L2119-2129 _struct_ **`FTransformedCurvePoint`** `struct FTransformedCurvePoint` _[#if NANITE_CURVES]_
  - L2122 _member_ `float3 ClipPointLeft;` — Used by Triangle geometry _[#if NANITE_CURVES]_
  - L2123 _member_ `float3 ClipPointRight;` _[#if NANITE_CURVES]_
  - L2126 _member_ `float WorldRadius;` — Used by Line geometry _[#if NANITE_CURVES]_
  - L2127 _member_ `float RadiusInPixel;` _[#if NANITE_CURVES]_
  - L2128 _member_ `float4 ClipPoint;` _[#if NANITE_CURVES]_
- L2400-2406 _struct_ **`FSegmentOpVisibility`** `struct FSegmentOpVisibility` _[#if NANITE_CURVES]_
  - L2402 _method_ `void operator()(FCurveSegment Seg)` _[#if NANITE_CURVES]_
- L2458-2468 _struct_ **`PrimitiveAttributes`** `struct PrimitiveAttributes` _[#if HW_RASTERIZER]_
  - L2460 _member_ `uint PixelValue;` _[#if HW_RASTERIZER]_
  - L2461 _member_ `uint ViewId;` _[#if HW_RASTERIZER]_
  - L2462 _member_ `bool bSwapVW;` _[#if HW_RASTERIZER]_
  - L2463 _member_ `uint MipLevel;` _[#if HW_RASTERIZER]_
  - L2464 _member_ `uint ArrayIndex;` _[#if HW_RASTERIZER]_
  - L2465 _member_ `uint LevelOffset;` _[#if HW_RASTERIZER]_
  - L2466 _member_ `uint4 ViewRect;` _[#if HW_RASTERIZER]_
  - L2467 _member_ `uint MaterialCBIndex;` _[#if HW_RASTERIZER]_
- L2476-2484 _struct_ **`PrimitiveAttributesPacked`** `struct PrimitiveAttributesPacked` _[#if HW_RASTERIZER]_
  - L2479 _member_ `NANITE_MESH_SHADING_PER_PRIMITIVE_ATTRIBUTE nointerpolation uint4 PackedData : TEXCOORD1;` — Use uint4 to prevent compiler from erroneously packing per-vertex and per-prim attributes together _[#if HW_RASTERIZER]_
  - L2482 _member_ `NANITE_MESH_SHADING_PER_PRIMITIVE_ATTRIBUTE nointerpolation uint4 MaterialCBIndex : TEXCOORD2;` — TODO: Would it make more sense to pack this into PackedData, even if that means spilling something else? _[#if HW_RASTERIZER && NANITE_BINDLESS_EXPORT]_
- L2488-2523 _struct_ **`VSOut`** `struct VSOut` _[#if HW_RASTERIZER]_
  - L2491 _member_ `float4 Clip : TEXCOORD0;` _[#if HW_RASTERIZER && STORE_CLIP_IN_INTERPOLATOR]_
  - L2495 _member_ `PrimitiveAttributesPacked PrimitivePacked;` _[#if HW_RASTERIZER && !NANITE_MESH_SHADER]_
  - L2500 _member_ `CUSTOM_INTERPOLATION uint2 ToTriangleMask_TriRangeStart : TEXCOORD3;` _[#if HW_RASTERIZER && VERTEX_TO_TRIANGLE_MASKS && NANITE_VERT_REUSE_BATCH]_
  - L2502 _member_ `CUSTOM_INTERPOLATION uint4 ToTriangleMasks : TEXCOORD3;` _[#if HW_RASTERIZER && VERTEX_TO_TRIANGLE_MASKS && !(NANITE_VERT_REUSE_BATCH)]_
  - L2507 _member_ `CUSTOM_INTERPOLATION uint VertexID : TEXCOORD4;` _[#if HW_RASTERIZER && BARYCENTRIC_MODE_INTRINSICS]_
  - L2509 _member_ `float3 Barycentrics : SV_Barycentrics;` _[#if HW_RASTERIZER && !(BARYCENTRIC_MODE_INTRINSICS) && BARYCENTRIC_MODE_SV_BARYCENTRICS && PIXELSHADER]_
  - L2511 _member_ `float2 BarycentricsUV : TEXCOORD4;` _[#if HW_RASTERIZER && !(BARYCENTRIC_MODE_INTRINSICS) && !(BARYCENTRIC_MODE_SV_BARYCENTRICS && PIXELSHADER) && BARYCENTRIC_MODE_EXPORT]_
  - L2515 _member_ `float4 TexCoords : TEXCOORD5;` _[#if HW_RASTERIZER && NANITE_PIXEL_PROGRAMMABLE]_
  - L2518 _member_ `float4 Position : SV_Position;` _[#if HW_RASTERIZER]_
  - L2521 _member_ `float OutGlobalClipPlaneDistance : SV_ClipDistance;` _[#if HW_RASTERIZER && USE_GLOBAL_CLIP_PLANE && !PIXELSHADER]_
- L2722-2728 _struct_ **`PrimitiveInput`** `struct PrimitiveInput` _[#if HW_RASTERIZER && NANITE_PRIM_SHADER]_
  - L2724 _member_ `uint Index : PRIM_SHADER_SEM_VERT_INDEX;` _[#if HW_RASTERIZER && NANITE_PRIM_SHADER]_
  - L2726 _member_ `uint WaveIndex : PRIM_SHADER_SEM_WAVE_INDEX;` _[#if HW_RASTERIZER && NANITE_PRIM_SHADER && !NANITE_VERT_REUSE_BATCH]_
- L2730-2737 _struct_ **`PrimitiveOutput`** `struct PrimitiveOutput` _[#if HW_RASTERIZER && NANITE_PRIM_SHADER]_
  - L2732 _member_ `VSOut Out;` _[#if HW_RASTERIZER && NANITE_PRIM_SHADER]_
  - L2734 _member_ `uint PrimExport : PRIM_SHADER_SEM_PRIM_EXPORT;` _[#if HW_RASTERIZER && NANITE_PRIM_SHADER]_
  - L2735 _member_ `uint VertCount : PRIM_SHADER_SEM_VERT_COUNT;` _[#if HW_RASTERIZER && NANITE_PRIM_SHADER]_
  - L2736 _member_ `uint PrimCount : PRIM_SHADER_SEM_PRIM_COUNT;` _[#if HW_RASTERIZER && NANITE_PRIM_SHADER]_
- L3478-3491 _struct_ **`FSegmentOpTileCount`** `struct FSegmentOpTileCount` _[#if defined(CurveTileCount)]_
  - L3480 _method_ `void operator()(FRaster Raster, FCurveSegment Seg)` _[#if defined(CurveTileCount)]_
- L3507-3520 _struct_ **`FSegmentOpTileWrite`** `struct FSegmentOpTileWrite` _[#if defined(CurveTileWrite)]_
  - L3509 _method_ `void operator()(FRaster Raster, FCurveSegment Seg)` _[#if defined(CurveTileWrite)]_

#### Global resources (textures / buffers / samplers) (6)

- L121 _resource_ `RWStructuredBuffer<FNaniteStats> OutStatsBuffer;`
- L122 _resource_ `StructuredBuffer<FNaniteRasterBinMeta> RasterBinMeta;`
- L123 _resource_ `StructuredBuffer<FNaniteRasterGroupMeta> RasterGroupMeta;`
- L124 _resource_ `StructuredBuffer<uint2> RasterBinData;`
- L242 _resource_ `StructuredBuffer< uint2 > InTotalPrevDrawClusters;`
- L243 _resource_ `Buffer<uint> InClusterOffsetSWHW;`

#### Global parameters (uniforms) (1)

- L2767 _parameter_ `LDS;` _[#if HW_RASTERIZER && NANITE_PRIM_SHADER]_

#### groupshared (28)

- L309 _groupshared_ `groupshared float GroupVertsX[VERTEX_CACHE_SIZE];` — Use SOA layout as some compilers will pad float3 array to 4 components per vertex. _[#if NANITE_TRIANGLES \|\| PATCHES]_
- L310 _groupshared_ `groupshared float GroupVertsY[VERTEX_CACHE_SIZE];` _[#if NANITE_TRIANGLES \|\| PATCHES]_
- L311 _groupshared_ `groupshared float GroupVertsZ[VERTEX_CACHE_SIZE];` _[#if NANITE_TRIANGLES \|\| PATCHES]_
- L327 _groupshared_ `groupshared float4x4 GroupLocalToTranslatedWorld;` _[#if NANITE_PLATFORM_RASTER_STAGE_UNIFORMS_TO_LDS]_
- L328 _groupshared_ `groupshared float4x4 GroupTranslatedWorldToClip;` _[#if NANITE_PLATFORM_RASTER_STAGE_UNIFORMS_TO_LDS]_
- L329 _groupshared_ `groupshared float3x3 GroupFirstPersonTransform;` _[#if NANITE_PLATFORM_RASTER_STAGE_UNIFORMS_TO_LDS]_
- L330 _groupshared_ `groupshared float2 GroupViewportScale;` _[#if NANITE_PLATFORM_RASTER_STAGE_UNIFORMS_TO_LDS]_
- L331 _groupshared_ `groupshared float2 GroupViewportBias;` _[#if NANITE_PLATFORM_RASTER_STAGE_UNIFORMS_TO_LDS]_
- L332 _groupshared_ `groupshared int4 GroupScissorRect;` _[#if NANITE_PLATFORM_RASTER_STAGE_UNIFORMS_TO_LDS]_
- L345 _groupshared_ `groupshared float3 VertexCache_PointLocal[64];` — 64 rolling window vertex cache for pixel programmable shaders. The expectation is that most materials will only require PointSubpixelClip and maybe 1/2 UV sets and the rest will be DCE'd _[#if NANITE_TRIANGLES]_
- L346 _groupshared_ `groupshared float3 VertexCache_PointPostDeform[64];` _[#if NANITE_TRIANGLES]_
- L347 _groupshared_ `groupshared float3 VertexCache_PrevPointPostDeform[64];` _[#if NANITE_TRIANGLES]_
- L348 _groupshared_ `groupshared float3 VertexCache_PointWorld[64];` _[#if NANITE_TRIANGLES]_
- L349 _groupshared_ `groupshared float3 VertexCache_PointWorld_NoOffset[64];` _[#if NANITE_TRIANGLES]_
- L350 _groupshared_ `groupshared float4 VertexCache_PointClip[64];` _[#if NANITE_TRIANGLES]_
- L351 _groupshared_ `groupshared half3 VertexCache_NormalPostDeform[64];` _[#if NANITE_TRIANGLES]_
- L352 _groupshared_ `groupshared float4 VertexCache_NormalClip[64];` _[#if NANITE_TRIANGLES]_
- L353 _groupshared_ `groupshared half4 VertexCache_TangentXAndSignPostDeform[64];` _[#if NANITE_TRIANGLES]_
- L354 _groupshared_ `groupshared float4 VertexCache_Color[64];` _[#if NANITE_TRIANGLES]_
- L355 _groupshared_ `groupshared float2 VertexCache_CustomizedUVs0[64];` _[#if NANITE_TRIANGLES]_
- L356 _groupshared_ `groupshared float2 VertexCache_CustomizedUVs1[64];` _[#if NANITE_TRIANGLES]_
- L357 _groupshared_ `groupshared float2 VertexCache_CustomizedUVs2[64];` _[#if NANITE_TRIANGLES]_
- L358 _groupshared_ `groupshared float2 VertexCache_CustomizedUVs3[64];` _[#if NANITE_TRIANGLES]_
- L359 _groupshared_ `groupshared float4 VertexCache_PointSubpixelClip[64];` _[#if NANITE_TRIANGLES]_
- L1277 _groupshared_ `groupshared uint GroupWorkEnd[32];` _[#if NANITE_VOXELS]_
- L1278 _groupshared_ `groupshared uint3 GroupBrickData[32];` _[#if NANITE_VOXELS]_
- L1279 _groupshared_ `groupshared uint GroupSourceLaneAndPixelPos[64];` _[#if NANITE_VOXELS]_
- L2769 _groupshared_ `groupshared uint GroupVertToTriMasks[32];` _[#if HW_RASTERIZER && NANITE_PRIM_SHADER]_

#### Functions (44)

- L59-119 _function_ `ALLOW_NO_PS_EXPORT MAX_OCCUPANCY DISABLE_TARGET_OCCUPANCY_WARNING DISABLE_POTENTIALLY_UNINITIALIZED_WARNING COMPILER_ALLOW_NON_UNIFORM_DESCRIPTORS HOIST_DESCRIPTORS uint GetRasterGroup()` _[#if PIXELSHADER]_
- L127-138 _function_ `void SetBindlessMaterial(uint Index)` _[#if NANITE_BINDLESS]_
- L155-181 _function_ `template<bool bHardware> FClusterRef FetchClusterRef(const uint ClusterIndex)`
- L183-218 _function_ `ViewState ResolveView(FNaniteView NaniteView)`
- L221-240 _function_ `bool ReverseWindingOrder(FNaniteView NaniteView, FPrimitiveSceneData PrimitiveData, FInstanceSceneData InstanceData)` — Default cull mode is CW. If this returns true, CCW culling is required
- L245-299 _function_ `FRaster CreateRaster( FNaniteView NaniteView, FVisibleCluster VisibleCluster )`
- L313-318 _function_ `void SetGroupVert(uint Index, float3 Value)` _[#if NANITE_TRIANGLES \|\| PATCHES]_
- L320-323 _function_ `float3 GetGroupVert(uint Index)` _[#if NANITE_TRIANGLES \|\| PATCHES]_
- L362-391 _function_ `void StoreVertexToLDS( uint VertexIndex, FCachedVertex Vertex )` _[#if NANITE_TRIANGLES]_
- L394-427 _function_ `FCachedVertex LoadVertexFromLDS( uint VertexIndex )` _[#if NANITE_TRIANGLES]_
- L429-883 _function_ `void ClusterRasterize( uint GroupIndex, uint GroupThreadIndex )` _[#if NANITE_TRIANGLES]_
- L887-1118 _function_ `void PatchRasterize( uint GroupID, uint GroupThreadIndex )` _[#if PATCHES]_
- L1124-1138 _function_ `bool IntersectBox(float3 RayOrigin, float3 RayDir, float3 BoxCenter, float3 BoxHalfSize, inout float OutIntersectionTime)` _[#if NANITE_VOXELS]_
- L1140-1162 _function_ `void PlotPixel(FRaster Raster, int2 PixelCoord, uint PixelValue, float DeviceZ)` _[#if NANITE_VOXELS]_
- L1164-1189 _function_ `template<bool bOrtho> FRay GetLocalRay( FNaniteView NaniteView, FInstanceSceneData InstanceData, float4 SvPosition )` _[#if NANITE_VOXELS]_
- L1191-1275 _function_ `template<bool bOrtho> void ProcessBrickPixel( FNaniteView NaniteView, FRaster Raster, FInstanceSceneData InstanceData, FRay Ray, int2 PixelPos, uint PixelValue, uint2 ReverseBrickBits, float3 LocalVoxelBoundsExtent, float VoxelSize, float RcpVoxelSize, float Bias )` _[#if NANITE_VOXELS]_
- L1281-1360 _function_ `template<bool bOrtho> void ProcessBrickPixelBatchFromQueue( inout int QueueNumElements, inout uint QueueReadOffset, FNaniteView NaniteView, FRaster Raster, FInstanceSceneData InstanceData, FCluster Cluster, uint VisibleIndex, float VoxelSize, float RcpVoxelSize, float Bias, float3 RayDirection, float3 RayDirection_dx, float3 RayDirection_dy, float3 RayOrigin, float3 RayOrigin_dx, float3 RayOrigin_dy, uint2 ReverseBrickBits, uint BrickMax_VertIndex, uint GroupThreadIndex )` _[#if NANITE_VOXELS]_
- L1362-1382 _function_ `bool OcclusionTestPixel( FRaster Raster, int2 PixelPos, float Depth )` _[#if NANITE_VOXELS]_
- L1391-1477 _function_ `template<bool bOrtho> FBounds ApproximateScreenBounds(float3 LocalCenter, float3 LocalExtent, float4x4 LocalToClip, float4x4 ViewToClip)` — This is a conservative approximation when CONSTANT_DIR_RECT is set. _[#if NANITE_VOXELS]_
- L1479-1781 _function_ `template<bool bOrtho> void ClusterTraceBricks( uint VisibleIndex, uint GroupThreadIndex, FNaniteView NaniteView, FVisibleCluster VisibleCluster, FInstanceSceneData InstanceData, FCluster Cluster, FRaster Raster, FInstanceDynamicData InstanceDynamicData )` _[#if NANITE_VOXELS]_
- L1783-1834 _function_ `void ClusterTraceBricks( uint GroupID, uint GroupThreadIndex )` _[#if NANITE_VOXELS]_
- L1847-1858 _function_ `FCurveDDA CurveDDACreateContext(float2 RayStart, float2 RayDir)` _[#if NANITE_CURVES]_
- L1860-1872 _function_ `void CurveDDAAdvance(inout FCurveDDA Context)` _[#if NANITE_CURVES]_
- L1874-1884 _function_ `float4 InterpolateCubicBezier(float4 P0, float4 P1, float4 P2, float4 P3, float Alpha)` _[#if NANITE_CURVES]_
- L1890-1947 _function_ `void RasterizeSegmentImmediate( FRaster Raster, int4 ViewRect, float4 Pos0, float4 Pos1, uint SourcePixelValue, float2 vTranslation, uint FrameIndex)` — Input * Pos0.xy : screen pos in pixels * Pos.z   : view-space depth * Pos.w   : curve radius in pixels _[#if NANITE_CURVES]_
- L1950-1972 _function_ `void DrawTangentBasis(inout FShaderPrintContext Ctx, FInstanceDynamicData InstanceDynamicData, FCluster Cluster, FNaniteLocalVertex P0, float3 TWS_P0, float3 TWS_P1)` _[#if NANITE_CURVES && NANITE_CURVES_DEBUG_DRAW]_
- L1975-1980 _function_ `float2 TransformToScreen(float4 ClipPos, uint2 InViewSize)` _[#if NANITE_CURVES]_
- L1982-1989 _function_ `float PointToLineDistanceInPixels(float2 P0, float2 L0, float2 Ps)` _[#if NANITE_CURVES]_
- L1991-1996 _function_ `uint ComputeNumSegments(float MaxDistanceInPixels)` _[#if NANITE_CURVES]_
- L1998-2010 _function_ `uint4 GetClusterMinMaxRect(FCluster Cluster, FInstanceDynamicData InstanceDynamicData, FNaniteView NaniteView)` _[#if NANITE_CURVES]_
- L2012-2027 _function_ `void RasterClusterBound(FCluster Cluster, FRaster Raster, uint2 MinRect, uint2 MaxRect, uint GroupThreadIndex, uint ThreadGroupSize)` _[#if NANITE_CURVES]_
- L2031-2049 _function_ `void BuildSegmentTrianglePoints( FRaster Raster, FNaniteView NaniteView, float3 PointTWS, float3 TangentTWS, float WorldRadius, inout float4 OutPointClip_Left, inout float4 OutPointClip_Right)` _[#if NANITE_CURVES && NANITE_MATERIAL_INCLUDES]_
- L2051-2091 _function_ `void RasterSegmentTriangle( FRaster Raster, FMaterialShader MaterialShader, uint SourcePixelValue, float3 P0, float3 P1, float3 P2)` _[#if NANITE_CURVES && NANITE_MATERIAL_INCLUDES]_
- L2097-2113 _function_ `float ComputeClusterLODTransition( FNaniteView NaniteView, FInstanceSceneData InstanceData, FInstanceDynamicData DynamicData, FCluster Cluster)` — Return a transition factor between current and parent cluster (in [0..1]) * 0: Parent cluster * 1: Child  cluster _[#if NANITE_CURVES]_
- L2131-2160 _function_ `FTransformedCurvePoint WaveReadAdjacentLane(FTransformedCurvePoint In)` _[#if NANITE_CURVES]_
- L2162-2398 _function_ `template<typename FSegmentOp> void RasterizeClusterCurves(uint GroupID, uint GroupThreadIndex, uint ThreadGroupSize, FSegmentOp SegmentOp, bool bComputeClusterMinMaxZ=false)` _[#if NANITE_CURVES]_
- L2408-2412 _function_ `void ClusterRasterizeCurves(uint VisibleIndex, uint GroupThreadIndex)` _[#if NANITE_CURVES]_
- L2525-2553 _function_ `PrimitiveAttributesPacked PackPrimitiveAttributes(PrimitiveAttributes In)` _[#if HW_RASTERIZER]_
- L2555-2585 _function_ `PrimitiveAttributes UnpackPrimitiveAttributes(PrimitiveAttributesPacked In)` _[#if HW_RASTERIZER]_
- L2587-2615 _function_ `PrimitiveAttributes MakePrimitiveAttributes(FNaniteView NaniteView, FVisibleCluster VisibleCluster, uint PixelValue, bool bReverseWindingOrder, uint MaterialCBIndex)` _[#if HW_RASTERIZER]_
- L2617-2716 _function_ `VSOut CommonRasterizerVS(FNaniteView NaniteView, FPrimitiveSceneData PrimitiveData, FInstanceSceneData InstanceData, FVisibleCluster VisibleCluster, FCluster Cluster, uint VertIndex, uint PixelValue, bool bReverseWindingOrder, uint MaterialCBIndex, uint RasterBin)` _[#if HW_RASTERIZER]_
- L2739-2742 _function_ `uint PackTriangleExport(uint3 TriangleIndices)` _[#if HW_RASTERIZER && NANITE_PRIM_SHADER]_
- L2744-2750 _function_ `uint3 UnpackTriangleExport(uint Packed)` _[#if HW_RASTERIZER && NANITE_PRIM_SHADER]_
- L3226-3244 _function_ `bool QuadActiveAnyTrue(bool Expr)` _[#if HW_RASTERIZER]_

#### Macro blocks (1)

- L3019-3155 _macro_block_ `[Shader("node")] [NodeLaunch("mesh")] [NodeMaxDispatchGrid(65535,1,1)] MESH_SHADER_TRIANGLE_ATTRIBUTES(NANITE_MESH_SHADER_TG_SIZE) void HWRasterizeMS( uint GroupThreadID : SV_GroupThreadID, uint3 GroupID : SV_GroupID, DispatchNodeInputRecord<FShaderBundleNodeRecord> InputRecord, MESH_SHADER_VERTEX_EXPORT(VSOut, 32), MESH_SHADER_TRIANGLE_EXPORT(32), MESH_SHADER_PRIMITIVE_EXPORT(PrimitiveAttributesPacked, 32) MESH_SHADER_VERTEX_EXPORT(VSOut, 256), MESH_SHADER_TRIANGLE_` _[#if HW_RASTERIZER && !(NANITE_PRIM_SHADER) && NANITE_MESH_SHADER && MESHSHADER \|\| WORKGRAPH_NODE && WORKGRAPH_NODE]_

#### Top-level macro invocations (2)

- L361 _macro_call_ `HLSL_STATIC_ASSERT( sizeof( FCachedVertex ) == 164 + 8 * NUM_TEX_COORD_INTERPOLATORS, "Unexpected size of FCachedVertex. Update StoreVertexToLDS to reflect changes." )` _[#if NANITE_TRIANGLES]_
- L393 _macro_call_ `HLSL_STATIC_ASSERT( sizeof( FCachedVertex ) == 164 + 8 * NUM_TEX_COORD_INTERPOLATORS, "Unexpected size of FCachedVertex. Update LoadVertexFromLDS to reflect changes." )` _[#if NANITE_TRIANGLES]_

#### C++ shader bindings (IMPLEMENT_* naming this file, 2)

- `HWRasterizeMS` → entry not found in file (macro-generated or #include'd); C++ `FHWRasterizeMS` SF_Mesh via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/Nanite/NaniteCullRaster.cpp:2059)
- `HWRasterizeMS` → entry not found in file (macro-generated or #include'd); C++ `FHWRasterizeWGMS` SF_WorkGraphComputeNode via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/Nanite/NaniteCullRaster.cpp:2084)

### `Shaders/Private/Nanite/NaniteRasterizer.ush` (Private)

- lines: 300; parse: all-branches
- L3 #pragma `once`

#### Structs / classes (1)

- L5-26 _struct_ **`FRasterTri`** `struct FRasterTri`
  - L7 _member_ `int2 MinPixel;`
  - L8 _member_ `int2 MaxPixel;`
  - L10 _member_ `float2 Edge01;`
  - L11 _member_ `float2 Edge12;`
  - L12 _member_ `float2 Edge20;`
  - L14 _member_ `float C0;`
  - L15 _member_ `float C1;`
  - L16 _member_ `float C2;`
  - L18 _member_ `float3 DepthPlane;`
  - L19 _member_ `float3 InvW;`
  - L21 _member_ `float3 Barycentrics_dx;`
  - L22 _member_ `float3 Barycentrics_dy;`
  - L24 _member_ `bool bIsValid;`
  - L25 _member_ `bool bBackFace;`

#### Functions (5)

- L28-130 _function_ `template< uint SubpixelSamples, bool bBackFaceCull > FRasterTri SetupTriangle( int4 ScissorRect, float4 Verts[3] )`
- L132-180 _function_ `template< typename FWritePixel > void RasterizeTri_Rect( FRasterTri Tri, FWritePixel WritePixel )`
- L182-227 _function_ `template< typename FWritePixel > void RasterizeTri_RectSingle( FRasterTri Tri, FWritePixel WritePixel )`
- L229-289 _function_ `template< typename FWritePixel > void RasterizeTri_Scanline( FRasterTri Tri, FWritePixel WritePixel )`
- L291-300 _function_ `template< typename FWritePixel > void RasterizeTri_Adaptive( FRasterTri Tri, FWritePixel WritePixel )`

### `Shaders/Private/Nanite/NaniteRayTrace.ush` (Private)

- lines: 316; parse: all-branches
- includes: L5 `../Common.ush`, L10 `/Engine/Private/Nanite/NaniteDataDecode.ush`, L11 `/Engine/Private/Nanite/NaniteAttributeDecode.ush`, L72 `/Engine/Shared/ThirdParty/RayTriangleIntersection.h` [NANITE_PROCEDURAL_RAY_TRACING], L74 `../RayTracing/RayTracingCommon.ush` [NANITE_PROCEDURAL_RAY_TRACING], L75 `NaniteVertexFetch.ush` [NANITE_PROCEDURAL_RAY_TRACING]

#### Macros (#define, 13)

- L7 `#define NANITE_USE_RAYTRACING_UNIFORM_BUFFER 1`
- L8 `#define NANITE_NUM_TEXCOORDS_TO_DECODE 0`
- L67 `#define NANITE_PROCEDURAL_RAY_TRACING 0` _[#if !defined(NANITE_PROCEDURAL_RAY_TRACING)]_
- L77 `#define INTERSECT_NANITE_TYPE_NAIVE (0)` _[#if NANITE_PROCEDURAL_RAY_TRACING]_
- L78 `#define INTERSECT_NANITE_TYPE INTERSECT_NANITE_TYPE_NAIVE` _[#if NANITE_PROCEDURAL_RAY_TRACING]_
- L80 `#define INTERSECT_TRIANGLE_TYPE_MOLLER_TRUMBORE (0)` _[#if NANITE_PROCEDURAL_RAY_TRACING]_
- L81 `#define INTERSECT_TRIANGLE_TYPE_WATERTIGHT (1)` _[#if NANITE_PROCEDURAL_RAY_TRACING]_
- L82 `#define INTERSECT_TRIANGLE_TYPE INTERSECT_TRIANGLE_TYPE_WATERTIGHT` _[#if NANITE_PROCEDURAL_RAY_TRACING]_
- L84 `#define BACKFACE_CULLING (0)` _[#if NANITE_PROCEDURAL_RAY_TRACING]_
- L85 `#define INTERSECTION_LOCAL_SPACE (1)` _[#if NANITE_PROCEDURAL_RAY_TRACING]_
- L86 `#define LOCAL_SPACE_WITHOUT_MATRIX_MUL (1)` _[#if NANITE_PROCEDURAL_RAY_TRACING]_
- L88 `#define TEST_BBOX (1 && INTERSECTION_LOCAL_SPACE)` _[#if NANITE_PROCEDURAL_RAY_TRACING]_
- L102 `#define STACK_SIZE 32` _[#if NANITE_PROCEDURAL_RAY_TRACING]_
- L3 #pragma `once`

#### Structs / classes (2)

- L90-100 _struct_ **`FNaniteIntersectionResult`** `struct FNaniteIntersectionResult` _[#if NANITE_PROCEDURAL_RAY_TRACING]_
  - L92 _member_ `float2 Barycentrics;` _[#if NANITE_PROCEDURAL_RAY_TRACING]_
  - L93 _member_ `uint PageIndex;` _[#if NANITE_PROCEDURAL_RAY_TRACING]_
  - L94 _member_ `uint ClusterIndex;` _[#if NANITE_PROCEDURAL_RAY_TRACING]_
  - L95 _member_ `uint TriIndex;` _[#if NANITE_PROCEDURAL_RAY_TRACING]_
  - L97 _member_ `uint NodeIntersectionCount;` _[#if NANITE_PROCEDURAL_RAY_TRACING]_
  - L98 _member_ `uint ClusterIntersectionCount;` _[#if NANITE_PROCEDURAL_RAY_TRACING]_
  - L99 _member_ `uint TriangleIntersectionCount;` _[#if NANITE_PROCEDURAL_RAY_TRACING]_
- L103-127 _struct_ **`FSimpleStack`** `struct FSimpleStack` _[#if NANITE_PROCEDURAL_RAY_TRACING]_
  - L105 _method_ `void Init()` _[#if NANITE_PROCEDURAL_RAY_TRACING]_
  - L110 _method_ `void Push(uint Value)` _[#if NANITE_PROCEDURAL_RAY_TRACING]_
  - L115 _method_ `uint Pop()` _[#if NANITE_PROCEDURAL_RAY_TRACING]_
  - L120 _method_ `bool Empty()` _[#if NANITE_PROCEDURAL_RAY_TRACING]_
  - L125 _member_ `uint Data[STACK_SIZE];` _[#if NANITE_PROCEDURAL_RAY_TRACING]_
  - L126 _member_ `uint DataOffset;` _[#if NANITE_PROCEDURAL_RAY_TRACING]_

#### Functions (6)

- L13-46 _function_ `void GetNaniteTriangleEdges( uint PageIndex, uint ClusterIndex, uint TriIndex, uint AssemblyTransformIndex, uint NaniteAssemblyTransformOffset, out float3 LocalEdge0, out float3 LocalEdge1)`
- L48-64 _function_ `void GetNaniteTriangleEdges(uint TriangleDataOffset, uint NaniteAssemblyTransformOffset, out float3 LocalEdge0, out float3 LocalEdge1)`
- L129-138 _function_ `bool RayTriangleIntersection(float3 RayOrigin, float3 RayDirection, float3 Vertex0, float3 Vertex1, float3 Vertex2, out float IntersectionT, out float2 Barycentrics)` _[#if NANITE_PROCEDURAL_RAY_TRACING]_
- L140-158 _function_ `bool RayAABBIntersection(float3 RayOrigin, float3 RayDirection, float3 BoxCenter, float3 BoxExtent, float TMin, float RayTCurrent)` _[#if NANITE_PROCEDURAL_RAY_TRACING]_
- L160-230 _function_ `bool NaniteClustersIntersection( FInstanceSceneData InstanceData, uint PageIndex, uint BaseClusterIndex, uint NumClusters, uint AssemblyTransformIndex, float CutError, float3 Origin, float3 Direction, float4x4 LocalToTranslatedWorld, float3 InvScale, float3 BoundsCenter, float MaxWPOExtent, float TMin, inout float RayTCurrent, inout FNaniteIntersectionResult NaniteIntersectionResult)` _[#if NANITE_PROCEDURAL_RAY_TRACING]_
- L232-313 _function_ `bool NaniteIntersection(float3 Origin, float3 Direction, FInstanceSceneData InstanceData, FPrimitiveSceneData PrimitiveData, float CutError, float TMin, inout float RayTCurrent, out FNaniteIntersectionResult NaniteIntersectionResult)` _[#if NANITE_PROCEDURAL_RAY_TRACING]_

### `Shaders/Private/Nanite/NaniteRayTracing.usf` (Private)

- lines: 463; parse: all-branches
- includes: L3 `/Engine/Shared/NaniteDefinitions.h`, L4 `/Engine/Shared/NaniteRayTracingDefinitions.h`, L15 `NaniteHierarchyTraversal.ush` [NANITE_HIERARCHY_TRAVERSAL], L19 `../Common.ush`, L20 `../ShaderPrint.ush`, L21 `../WaveOpUtil.ush`, L22 `../ComputeShaderUtils.ush`, L24 `NaniteDataDecode.ush`, L25 `NaniteAttributeDecode.ush`, L26 `NaniteCulling.ush`, L27 `NaniteCullingCommon.ush`, L28 `NaniteStreaming.ush`, L346 `../InstanceCulling/InstanceCullingLoadBalancer.ush` [defined(InitQueueCS)], L403 `../InstanceCulling/InstanceCullingLoadBalancer.ush` [defined(CalculateReferenceErrorCS)]

#### Macros (#define, 3)

- L7 `#define NANITE_HIERARCHY_TRAVERSAL 0` _[#if !defined(NANITE_HIERARCHY_TRAVERSAL)]_
- L12 `#define NANITE_HIERARCHY_TRAVERSAL_TYPE (CULLING_TYPE)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
- L13 `#define GROUP_NODE_SIZE 2` _[#if NANITE_HIERARCHY_TRAVERSAL]_

#### Entry points (3)

- L332-340 _entry_ `[numthreads(NANITE_PERSISTENT_CLUSTER_CULLING_GROUP_SIZE, 1, 1)] void NaniteRayTracingStreamingTraversalCS(uint GroupID : SV_GroupID, uint GroupIndex : SV_GroupIndex)` — stage: **compute** — C++: `FNaniteRayTracingStreamingTraversalCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteRayTracing.cpp:354) _[#if NANITE_HIERARCHY_TRAVERSAL]_
- L351-397 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void InitQueueCS(uint GroupIndex : SV_GroupIndex, uint3 GroupId : SV_GroupID)` — stage: **compute** — C++: `FRayTracingStreamingInitQueueCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteRayTracing.cpp:299) _[#if defined(InitQueueCS)]_
- L407-460 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void CalculateReferenceErrorCS(uint GroupIndex : SV_GroupIndex, uint3 GroupId : SV_GroupID)` — stage: **compute** — C++: `FNaniteRayTracingCalculateReferenceErrorCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteRayTracing.cpp:385) _[#if defined(CalculateReferenceErrorCS)]_

#### Structs / classes (2)

- L45-53 _struct_ **`FCandidateNodeRT`** `struct FCandidateNodeRT`
  - L47 _member_ `uint NodeIndex;`
  - L49 _member_ `uint RequestIndex;` _[#if USE_REFERENCE_INSTANCES]_
  - L51 _member_ `uint InstanceId;` _[#if !(USE_REFERENCE_INSTANCES)]_
- L154-330 _struct_ **`FNaniteTraversalRayTracingStreamingCallback`** `struct FNaniteTraversalRayTracingStreamingCallback` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L156 _member_ `FCandidateNodeRT CandidateNode;` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L158 _member_ `FNaniteView NaniteView;` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L159 _member_ `FNaniteView OffscreenNaniteView;` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L162 _member_ `FStreamingTraversalRequest RequestData;` _[#if NANITE_HIERARCHY_TRAVERSAL && USE_REFERENCE_INSTANCES]_
  - L164 _member_ `FInstanceSceneData InstanceData;` _[#if NANITE_HIERARCHY_TRAVERSAL && !(USE_REFERENCE_INSTANCES)]_
  - L167 _member_ `bool bVisible;` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L169 _member_ `uint StreamingPriorityCategory;` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L170 _member_ `float StreamingPriority;` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L172 _method_ `void Init(uint InChildIndex, uint InLocalNodeIndex, uint GroupNodeFetchIndex)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L188 _method_ `uint GetHierarchyNodeOffset()` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L197 _method_ `bool ShouldVisitChild(FHierarchyNodeSlice HierarchyNodeSlice, bool bInVisible)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L246 _method_ `void OnPreProcessNodeBatch(uint GroupIndex)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L251 _method_ `void OnPostNodeVisit(FHierarchyNodeSlice HierarchyNodeSlice)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L263 _method_ `void StoreChildNode(uint StoreIndex, FHierarchyNodeSlice HierarchyNodeSlice)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L276 _method_ `void StoreCluster(uint StoreIndex, FHierarchyNodeSlice HierarchyNodeSlice, uint ClusterIndex)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L281 _method_ `uint4 LoadPackedCluster(uint CandidateIndex)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L287 _method_ `bool IsNodeDataReady(uint4 RawData)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L292 _method_ `bool LoadCandidateNodeDataToGroup(uint NodeIndex, uint GroupIndex, bool bCheckIfReady = true)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L305 _method_ `void ClearCandidateNodeData(uint NodeIndex)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L310 _method_ `void AddToClusterBatch(uint BatchIndex, uint Num)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L315 _method_ `void ClearClusterBatch(uint BatchIndex)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L320 _method_ `uint LoadClusterBatch(uint BatchIndex)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L326 _method_ `void ProcessCluster(uint4 PackedCluster)` _[#if NANITE_HIERARCHY_TRAVERSAL]_

#### Global resources (textures / buffers / samplers) (8)

- L30 _resource_ `RWStructuredBuffer<FStreamingRequest> OutStreamingRequests;` — First entry holds count
- L35 _resource_ `StructuredBuffer<uint> ReferenceErrors;`
- L39 _resource_ `StructuredBuffer<FStreamingTraversalRequest> StreamingTraversalRequests;` _[#if USE_REFERENCE_INSTANCES]_
- L43 _resource_ `StructuredBuffer<FPackedNaniteView> PackedNaniteViews;`
- L113 _resource_ `RWByteAddressBuffer Nodes;` _[#if NANITE_HIERARCHY_TRAVERSAL]_
- L348 _resource_ `RWStructuredBuffer<FQueueState> QueueState;` _[#if defined(InitQueueCS)]_
- L349 _resource_ `RWByteAddressBuffer Nodes;` _[#if defined(InitQueueCS)]_
- L405 _resource_ `RWStructuredBuffer<uint> RWReferenceErrors;` _[#if defined(CalculateReferenceErrorCS)]_

#### Global parameters (uniforms) (4)

- L32 _parameter_ `float MinCutError;`
- L33 _parameter_ `float OffscreenMinCutError;`
- L36 _parameter_ `uint UseReferenceErrors;`
- L40 _parameter_ `uint NumStreamingTraversalRequests;` _[#if USE_REFERENCE_INSTANCES]_

#### Functions (8)

- L55-71 _function_ `uint4 PackCandidateNodeRT(FCandidateNodeRT Node)`
- L73-83 _function_ `FCandidateNodeRT UnpackCandidateNodeRT(uint4 RawData)`
- L85 _function_ `uint GetCandidateNodeSizeRT()`
- L87-91 _function_ `uint4 LoadCandidateNodeDataRT(RWByteAddressBuffer InNodes, uint NodeIndex)`
- L93-97 _function_ `void StoreCandidateNodeDataRT(RWByteAddressBuffer InNodes, uint NodeIndex, uint4 RawData)`
- L99-103 _function_ `void StoreCandidateNodeRT(RWByteAddressBuffer InNodes, uint NodeIndex, FCandidateNodeRT Node)`
- L105-109 _function_ `void ClearCandidateNodeRT(RWByteAddressBuffer InNodes, uint NodeIndex)`
- L115-152 _function_ `bool ShouldVisitChildInternal( FNaniteView NaniteView, FInstanceSceneData InstanceData, FInstanceDynamicData DynamicData, FNodeCullingBounds Bounds, FHierarchyNodeSlice HierarchyNodeSlice, bool bOffscreen, inout float Priority )` _[#if NANITE_HIERARCHY_TRAVERSAL]_

### `Shaders/Private/Nanite/NaniteSVO.ush` (Private)

- lines: 218; parse: all-branches
- includes: L5 `Voxel/Voxel.ush`

#### Macros (#define, 2)

- L7 `#define MAX_LEVEL 7`
- L9 `#define NODE_CACHE_SIZE 0`
- L3 #pragma `once`

#### groupshared (2)

- L11 _groupshared_ `groupshared uint GroupNodes[ NODE_CACHE_SIZE ];` _[#if NODE_CACHE_SIZE]_
- L16 _groupshared_ `groupshared uint GroupStack[ THREADGROUP_SIZE * (MAX_LEVEL - 1) ];` — no need for leaf no need for root?

#### Functions (1)

- L18-218 _function_ `int TraceSVO( uint GroupThreadIndex, inout FRay Ray, ByteAddressBuffer NodeBuffer, uint NodesOffset, uint NodesNum, inout FRayCastCounters Counters )`

### `Shaders/Private/Nanite/NaniteScatterUpdates.usf` (Private)

- lines: 41; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../ComputeShaderUtils.ush`

#### Macros (#define, 3)

- L6 `#define SCATTER_OPERATION_OR 0`
- L7 `#define SCATTER_OPERATION_AND 1`
- L8 `#define SCATTER_OPERATION_WRITE 2`

#### Entry points (1)

- L14-40 _entry_ `[numthreads(64, 1, 1)] void ScatterUpdates(uint3 GroupID : SV_GroupID, uint GroupIndex : SV_GroupIndex)` — stage: **compute** — C++: `FScatterUpdates_CS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Engine/Private/Nanite/NaniteOrderedScatterUpdater.cpp:30)

#### Global resources (textures / buffers / samplers) (2)

- L11 _resource_ `StructuredBuffer<uint2> PackedUpdates;`
- L12 _resource_ `RWByteAddressBuffer DstBuffer;`

#### Global parameters (uniforms) (1)

- L10 _parameter_ `uint NumUpdates;`

### `Shaders/Private/Nanite/NaniteSceneCommon.ush` (Private)

- lines: 61; parse: all-branches
- includes: L5 `../Common.ush`, L6 `../SceneData.ush`, L8 `/Engine/Shared/NaniteDefinitions.h`, L9 `NaniteDataDecode.ush`

#### Macros (#define, 1)

- L12 `#define DISABLE_DISPLACEMENT_BOUNDS 0` _[#if !defined(DISABLE_DISPLACEMENT_BOUNDS)]_
- L3 #pragma `once`

#### Functions (5)

- L15-20 _function_ `FInstanceSceneData GetInstanceSceneDataUnchecked(inout FVisibleCluster VisibleCluster)`
- L22-38 _function_ `FInstanceDynamicData CalculateInstanceDynamicData( FNaniteView NaniteView, FInstanceSceneData InstanceData, bool bSetUpForCulling = false)`
- L40-47 _function_ `float GetAbsMaxMaterialDisplacement(FPrimitiveSceneData PrimitiveData)`
- L49-54 _function_ `float GetMaxMaterialDisplacementExtent(FPrimitiveSceneData PrimitiveData, bool bFallbackRaster, bool bIsShadowPass)`
- L56-60 _function_ `float3 GetLocalMaxWPOExtent(FPrimitiveSceneData PrimitiveData, FInstanceSceneData InstanceData, bool bEnableWPO = true)`

### `Shaders/Private/Nanite/NaniteShadeBinning.usf` (Private)

- lines: 1181; parse: all-branches
- includes: L3 `NaniteShadeCommon.ush`, L6 `/Platform/Private/RTWriteMaskLookup.ush` [defined(OVERRIDE_RTWRITEMASKPROCESSING_USH)], L13 `../MortonCode.ush`

#### Macros (#define, 18)

- L10 `#define OPTIMIZE_WRITE_MASK 0` _[#if !defined(OPTIMIZE_WRITE_MASK)]_
- L25 `#define SHADING_BIN_COUNT (SHADING_BIN_PASS == NANITE_SHADING_BIN_COUNT)`
- L26 `#define SHADING_BIN_RESERVE (SHADING_BIN_PASS == NANITE_SHADING_BIN_RESERVE)`
- L27 `#define SHADING_BIN_SCATTER (SHADING_BIN_PASS == NANITE_SHADING_BIN_SCATTER)`
- L28 `#define SHADING_BIN_VALIDATE (SHADING_BIN_PASS == NANITE_SHADING_BIN_VALIDATE)`
- L29 `#define SHADING_BIN_CMASK_CLEAR (SHADING_BIN_PASS == NANITE_SHADING_BIN_CMASK_CLEAR)`
- L30 `#define SHADING_BIN_GROUP_COUNT (SHADING_BIN_PASS == NANITE_SHADING_BIN_GROUP_COUNT)`
- L31 `#define SHADING_BIN_GROUP_RESERVE (SHADING_BIN_PASS == NANITE_SHADING_BIN_GROUP_RESERVE)`
- L33 `#define BINNING_THREADS_PER_SHADING_TILE (COMPUTE_MATERIAL_GROUP_SIZE / 4)`
- L36 `#define SHADING_BIN_TILE_SIZE_BITS 5` _[#if BINNING_TECHNIQUE == 1]_
- L38 `#define SHADING_BIN_TILE_SIZE_BITS 3` _[#if !(BINNING_TECHNIQUE == 1)]_
- L41 `#define SHADING_BIN_TILE_SIZE (1u << SHADING_BIN_TILE_SIZE_BITS)`
- L42 `#define SHADING_BIN_TILE_THREADS (SHADING_BIN_TILE_SIZE * SHADING_BIN_TILE_SIZE)`
- L45 `#define INVALID_BIN0 (-1)`
- L46 `#define INVALID_BIN1 (-2)`
- L47 `#define INVALID_BIN2 (-3)`
- L48 `#define INVALID_BIN3 (-4)`
- L58 `#define NUM_EXPORTS 1` _[#if OPTIMIZE_WRITE_MASK && !defined(NUM_EXPORTS)]_

#### Entry points (6)

- L941-954 _entry_ `[numthreads(SHADING_BIN_TILE_THREADS, 1, 1)] void ShadingBinBuildCS(uint ThreadIndex : SV_GroupIndex, uint2 GroupId : SV_GroupID)` — stage: **compute** — C++: `FShadingBinBuildCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteShading.cpp:467) _[#if SHADING_BIN_COUNT \|\| SHADING_BIN_SCATTER]_
- L958-1044 _entry_ `[numthreads(64, 1, 1)] void ShadingBinReserveCS(uint ShadingBin : SV_DispatchThreadID)` — stage: **compute** — C++: `FShadingBinReserveCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteShading.cpp:551) _[#if !(SHADING_BIN_COUNT \|\| SHADING_BIN_SCATTER) && SHADING_BIN_RESERVE]_
- L1047-1060 _entry_ `[numthreads(64, 1, 1)] void ShadingBinValidateCS(uint ShadingBin : SV_DispatchThreadID)` — stage: **compute** — C++: `FShadingBinValidateCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteShading.cpp:576) _[#if !(SHADING_BIN_COUNT \|\| SHADING_BIN_SCATTER) && !(SHADING_BIN_RESERVE) && SHADING_BIN_VALIDATE]_
- L1067-1118 _entry_ `[numthreads(8, 8, 1)] void ClearCMaskRectCS(uint2 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `FClearCMaskRectCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteShading.cpp:633) _[#if !(SHADING_BIN_COUNT \|\| SHADING_BIN_SCATTER) && !(SHADING_BIN_RESERVE) && !(SHADING_BIN_VALIDATE) && SHADING_BIN_CMASK_CLEAR]_
- L1121-1146 _entry_ `[numthreads(64, 1, 1)] void ShadingGroupCS(uint ShadingBin : SV_DispatchThreadID)` — stage: **compute** — C++: `FShadingGroupCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteShading.cpp:499) _[#if !(SHADING_BIN_COUNT \|\| SHADING_BIN_SCATTER) && !(SHADING_BIN_RESERVE) && !(SHADING_BIN_VALIDATE) && !(SHADING_BIN_CMASK_CLEAR) && SHADING_BIN_GROUP_COUNT]_
- L1149-1180 _entry_ `[numthreads(64, 1, 1)] void ShadingGroupCS(uint ShadingGroup : SV_DispatchThreadID)` — stage: **compute** — C++: `FShadingGroupCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteShading.cpp:499) _[#if !(SHADING_BIN_COUNT \|\| SHADING_BIN_SCATTER) && !(SHADING_BIN_RESERVE) && !(SHADING_BIN_VALIDATE) && !(SHADING_BIN_CMASK_CLEAR) && !(SHADING_BIN_GROUP_COUNT) && SHADING_BIN_GROUP_RESERVE]_

#### Structs / classes (4)

- L397-418 _struct_ **`FCountPixelsTask`** `struct FCountPixelsTask` _[#if SHADING_BIN_COUNT \|\| SHADING_BIN_SCATTER]_
  - L399 _method_ `void ProcessBin(inout int4 ShadingBins, int VotedBin, uint LaneBin, uint ThreadIndex)` _[#if SHADING_BIN_COUNT \|\| SHADING_BIN_SCATTER]_
  - L417 _method_ `void Finish(int4 ShadingBins)` _[#if SHADING_BIN_COUNT \|\| SHADING_BIN_SCATTER]_
- L422-525 _struct_ **`FScatterPixelsTask`** `template<bool bSingleWave> struct FScatterPixelsTask` _[#if SHADING_BIN_COUNT \|\| SHADING_BIN_SCATTER && SHADING_BIN_SCATTER]_
  - L425 _member_ `uint2 QuadTLCoord;` _[#if SHADING_BIN_COUNT \|\| SHADING_BIN_SCATTER && SHADING_BIN_SCATTER]_
  - L426 _member_ `uint2 VRSShift;` _[#if SHADING_BIN_COUNT \|\| SHADING_BIN_SCATTER && SHADING_BIN_SCATTER]_
  - L427 _member_ `uint WriteMasks;` _[#if SHADING_BIN_COUNT \|\| SHADING_BIN_SCATTER && SHADING_BIN_SCATTER]_
  - L428 _member_ `uint4 DataWriteOffsets;` _[#if SHADING_BIN_COUNT \|\| SHADING_BIN_SCATTER && SHADING_BIN_SCATTER]_
  - L430 _method_ `void Init(uint2 InQuadTLCoord, uint2 InVRSShift, uint InWriteMasks)` _[#if SHADING_BIN_COUNT \|\| SHADING_BIN_SCATTER && SHADING_BIN_SCATTER]_
  - L437 _method_ `void ProcessBin(inout int4 ShadingBins, int VotedBin, int LaneBin, uint ThreadIndex)` _[#if SHADING_BIN_COUNT \|\| SHADING_BIN_SCATTER && SHADING_BIN_SCATTER]_
  - L507 _method_ `void Finish(int4 ShadingBins)` _[#if SHADING_BIN_COUNT \|\| SHADING_BIN_SCATTER && SHADING_BIN_SCATTER]_
- L529-581 _struct_ **`FCountQuadsTask`** `struct FCountQuadsTask` _[#if SHADING_BIN_COUNT \|\| SHADING_BIN_SCATTER]_
  - L531 _member_ `bool bWaveQuadVRS;` _[#if SHADING_BIN_COUNT \|\| SHADING_BIN_SCATTER]_
  - L532 _member_ `uint ShadingRate;` _[#if SHADING_BIN_COUNT \|\| SHADING_BIN_SCATTER]_
  - L534 _method_ `void Init(bool bInWaveQuadVRS, uint InShadingRate)` _[#if SHADING_BIN_COUNT \|\| SHADING_BIN_SCATTER]_
  - L540 _method_ `void ProcessBin(inout int4 ShadingBins, int VotedBin, int LaneBin, uint ThreadIndex)` _[#if SHADING_BIN_COUNT \|\| SHADING_BIN_SCATTER]_
  - L580 _method_ `void Finish(int4 ShadingBins)` _[#if SHADING_BIN_COUNT \|\| SHADING_BIN_SCATTER]_
- L585-711 _struct_ **`FScatterQuadsTask`** `template<bool bSingleWave> struct FScatterQuadsTask` _[#if SHADING_BIN_COUNT \|\| SHADING_BIN_SCATTER && SHADING_BIN_SCATTER]_
  - L588 _member_ `bool bWaveQuadVRS;` _[#if SHADING_BIN_COUNT \|\| SHADING_BIN_SCATTER && SHADING_BIN_SCATTER]_
  - L589 _member_ `uint2 QuadTLCoord;` _[#if SHADING_BIN_COUNT \|\| SHADING_BIN_SCATTER && SHADING_BIN_SCATTER]_
  - L590 _member_ `uint2 VRSShift;` _[#if SHADING_BIN_COUNT \|\| SHADING_BIN_SCATTER && SHADING_BIN_SCATTER]_
  - L591 _member_ `uint ShadingRate;` _[#if SHADING_BIN_COUNT \|\| SHADING_BIN_SCATTER && SHADING_BIN_SCATTER]_
  - L592 _member_ `uint WriteMasks;` _[#if SHADING_BIN_COUNT \|\| SHADING_BIN_SCATTER && SHADING_BIN_SCATTER]_
  - L594 _method_ `void Init(bool bInWaveQuadVRS, uint2 InQuadTLCoord, uint2 InVRSShift, uint InShadingRate, uint InWriteMasks)` _[#if SHADING_BIN_COUNT \|\| SHADING_BIN_SCATTER && SHADING_BIN_SCATTER]_
  - L603 _method_ `void ProcessBin(inout int4 ShadingBins, int VotedBin, int LaneBin, uint ThreadIndex)` _[#if SHADING_BIN_COUNT \|\| SHADING_BIN_SCATTER && SHADING_BIN_SCATTER]_
  - L710 _method_ `void Finish(int4 ShadingBins)` _[#if SHADING_BIN_COUNT \|\| SHADING_BIN_SCATTER && SHADING_BIN_SCATTER]_

#### Global resources (textures / buffers / samplers) (22)

- L61 _resource_ `RWByteAddressBuffer OutCMaskBuffer_0;` _[#if OPTIMIZE_WRITE_MASK]_
- L64 _resource_ `RWByteAddressBuffer OutCMaskBuffer_1;` _[#if OPTIMIZE_WRITE_MASK && NUM_EXPORTS > 1]_
- L68 _resource_ `RWByteAddressBuffer OutCMaskBuffer_2;` _[#if OPTIMIZE_WRITE_MASK && NUM_EXPORTS > 2]_
- L72 _resource_ `RWByteAddressBuffer OutCMaskBuffer_3;` _[#if OPTIMIZE_WRITE_MASK && NUM_EXPORTS > 3]_
- L76 _resource_ `RWByteAddressBuffer OutCMaskBuffer_4;` _[#if OPTIMIZE_WRITE_MASK && NUM_EXPORTS > 4]_
- L80 _resource_ `RWByteAddressBuffer OutCMaskBuffer_5;` _[#if OPTIMIZE_WRITE_MASK && NUM_EXPORTS > 5]_
- L84 _resource_ `RWByteAddressBuffer OutCMaskBuffer_6;` _[#if OPTIMIZE_WRITE_MASK && NUM_EXPORTS > 6]_
- L88 _resource_ `RWByteAddressBuffer OutCMaskBuffer_7;` _[#if OPTIMIZE_WRITE_MASK && NUM_EXPORTS > 7]_
- L122 _resource_ `Texture2D<uint> ShadingRateImage;` _[#if VARIABLE_SHADING_RATE]_
- L126 _resource_ `Texture2D<uint> ShadingMask;` _[#if SHADING_BIN_COUNT \|\| SHADING_BIN_SCATTER]_
- L127 _resource_ `SamplerState ShadingMaskSampler;` _[#if SHADING_BIN_COUNT \|\| SHADING_BIN_SCATTER]_
- L128 _resource_ `RWStructuredBuffer<uint> OutThreadGroupData;` _[#if SHADING_BIN_COUNT \|\| SHADING_BIN_SCATTER]_
- L131 _resource_ `RWByteAddressBuffer OutShadingBinData;`
- L149 _resource_ `RWStructuredBuffer<uint> OutShadingBinAllocator;` _[#if SHADING_BIN_RESERVE \|\| SHADING_BIN_GROUP_RESERVE]_
- L150 _resource_ `RWByteAddressBuffer OutShadingDispatchArgs;` _[#if SHADING_BIN_RESERVE \|\| SHADING_BIN_GROUP_RESERVE]_
- L151 _resource_ `StructuredBuffer<FNaniteShadingBinMeta> ShadingBinMeta;` _[#if SHADING_BIN_RESERVE \|\| SHADING_BIN_GROUP_RESERVE]_
- L155 _resource_ `RWStructuredBuffer<FNaniteShadingBinStats> OutShadingBinStats;` _[#if GATHER_STATS]_
- L159 _resource_ `RWStructuredBuffer<FNaniteShadingBinScatterCounters> OutShadingBinScatterCounters;` _[#if SHADING_BIN_COUNT \|\| SHADING_BIN_RESERVE \|\| SHADING_BIN_SCATTER \|\| SHADING_BIN_VALIDATE \|\| SHADING_BIN_GROUP_COUNT]_
- L163 _resource_ `RWStructuredBuffer<FNaniteShadingBinScatterRanges> OutShadingBinScatterRanges;` _[#if SHADING_BIN_RESERVE]_
- L167 _resource_ `StructuredBuffer<FNaniteShadingBinScatterRanges> ShadingBinScatterRanges;` _[#if SHADING_BIN_SCATTER]_
- L171 _resource_ `RWStructuredBuffer<FNaniteShadingGroupMeta> OutShadingGroupMeta;` _[#if SHADING_BIN_RESERVE \|\| SHADING_BIN_GROUP_COUNT \|\| SHADING_BIN_GROUP_RESERVE]_
- L172 _resource_ `RWStructuredBuffer<FNaniteShadingGroupAllocator> OutShadingGroupAllocator;` _[#if SHADING_BIN_RESERVE \|\| SHADING_BIN_GROUP_COUNT \|\| SHADING_BIN_GROUP_RESERVE]_

#### Global parameters (uniforms) (10)

- L15 _parameter_ `uint4 ViewRect;`
- L17 _parameter_ `uint ValidWriteMask;` _[#if OPTIMIZE_WRITE_MASK]_
- L19 _parameter_ `uint2 DispatchOffsetTL;`
- L20 _parameter_ `uint ShadingBinCount;`
- L21 _parameter_ `uint ShadingGroupCount;`
- L22 _parameter_ `uint DummyZero;`
- L23 _parameter_ `uint SubTileMatch;`
- L121 _parameter_ `uint ShadingRateTileSizeBits;` _[#if VARIABLE_SHADING_RATE]_
- L1064 _parameter_ `uint2 ClearTileRectMin;` _[#if !(SHADING_BIN_COUNT \|\| SHADING_BIN_SCATTER) && !(SHADING_BIN_RESERVE) && !(SHADING_BIN_VALIDATE) && SHADING_BIN_CMASK_CLEAR]_
- L1065 _parameter_ `uint2 ClearTileRectSize;` _[#if !(SHADING_BIN_COUNT \|\| SHADING_BIN_SCATTER) && !(SHADING_BIN_RESERVE) && !(SHADING_BIN_VALIDATE) && SHADING_BIN_CMASK_CLEAR]_

#### groupshared (5)

- L177 _groupshared_ `groupshared int GroupVotedBin;` _[#if SHADING_BIN_COUNT \|\| SHADING_BIN_SCATTER]_
- L179 _groupshared_ `groupshared uint GroupFullTileCount_LooseCount;` — 16:16 _[#if SHADING_BIN_COUNT \|\| SHADING_BIN_SCATTER]_
- L180 _groupshared_ `groupshared uint GroupFullTileOffset;` _[#if SHADING_BIN_COUNT \|\| SHADING_BIN_SCATTER]_
- L181 _groupshared_ `groupshared uint GroupLooseOffset;` _[#if SHADING_BIN_COUNT \|\| SHADING_BIN_SCATTER]_
- L182 _groupshared_ `groupshared uint GroupEarlyOut;` _[#if SHADING_BIN_COUNT \|\| SHADING_BIN_SCATTER]_

#### static const (1)

- L91-115 _static_const_ `static const RWByteAddressBuffer CMaskExports[] = { OutCMaskBuffer_0, OutCMaskBuffer_1, OutCMaskBuffer_2, OutCMaskBuffer_3, OutCMaskBuffer_4, OutCMaskBuffer_5, OutCMaskBuffer_6, OutCMaskBuffer_7 };` _[#if OPTIMIZE_WRITE_MASK]_

#### Functions (12)

- L50-53 _function_ `bool IsValidBin(int BinIndex)`
- L133-136 _function_ `uint GetShadingBinMetaOffset()`
- L138-141 _function_ `uint GetShadingBinDataOffset()`
- L143-146 _function_ `FNaniteShadingBinMeta GetShadingBinMeta(uint ShadingBin)`
- L184-202 _function_ `uint PackShadingPixel(uint2 TopLeft, uint2 VRSShift, uint WriteMask)` _[#if SHADING_BIN_COUNT \|\| SHADING_BIN_SCATTER]_
- L204-210 _function_ `uint2 PackShadingQuad(uint2 TopLeft, uint2 VRSShift, uint WriteMask)` _[#if SHADING_BIN_COUNT \|\| SHADING_BIN_SCATTER]_
- L212-218 _function_ `uint ConvertQuadCoverageMaskToWriteMask(uint Coverage)` _[#if SHADING_BIN_COUNT \|\| SHADING_BIN_SCATTER]_
- L220-239 _function_ `void UpdateVRSActiveAndWriteMasks(uint ActiveMask, uint2 VRSShift, inout int4 ShadingBins, inout uint WriteMasks)` _[#if SHADING_BIN_COUNT \|\| SHADING_BIN_SCATTER]_
- L241-255 _function_ `bool IsFullTile(bool bFullQuad)` _[#if SHADING_BIN_COUNT \|\| SHADING_BIN_SCATTER]_
- L257-334 _function_ `template<bool bSingleWave, bool bQuadMode> void AllocateElements(uint Bin, uint ThreadIndex, uint QuadFullTileCount, uint QuadLooseCount, inout uint FullTileDataOffset, inout uint LooseDataOffset)` _[#if SHADING_BIN_COUNT \|\| SHADING_BIN_SCATTER]_
- L336-395 _function_ `template<typename FTask, bool bGroupUniform, bool bAllowInactiveLanes> void BinScalarization(FTask Task, int4 ShadingBins, uint ThreadIndex)` _[#if SHADING_BIN_COUNT \|\| SHADING_BIN_SCATTER]_
- L715-939 _function_ `template<bool bSingleWave> void BinShadingQuad(uint2 Coord, uint ThreadIndex)` _[#if SHADING_BIN_COUNT \|\| SHADING_BIN_SCATTER]_

### `Shaders/Private/Nanite/NaniteShadeCommon.ush` (Private)

- lines: 32; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../SceneData.ush`, L5 `../WaveOpUtil.ush`, L6 `../VariableRateShading/VRSShadingRateCommon.ush`, L7 `../Visualization.ush`, L8 `../MortonCode.ush`, L10 `NaniteAttributeDecode.ush`

#### Macros (#define, 3)

- L13 `#define COMPUTE_MATERIAL_GROUP_SIZE_BITS 5` _[#if COMPILER_SUPPORTS_WAVE_32_64_MODE]_
- L15 `#define COMPUTE_MATERIAL_GROUP_SIZE_BITS 6` _[#if !(COMPILER_SUPPORTS_WAVE_32_64_MODE)]_
- L18 `#define COMPUTE_MATERIAL_GROUP_SIZE (1u << COMPUTE_MATERIAL_GROUP_SIZE_BITS)`

#### Functions (1)

- L20-31 _function_ `uint PackQuadMask(bool4 Quad)`

### `Shaders/Private/Nanite/NaniteShadeDebug.usf` (Private)

- lines: 5; parse: all-branches
- includes: L3 `NaniteShadeCommon.ush`

### `Shaders/Private/Nanite/NaniteSkinningUpdateViewData.usf` (Private)

- lines: 178; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../SceneData.ush`, L5 `../ViewData.ush`, L6 `../ComputeShaderUtils.ush`, L7 `../WaveOpUtil.ush`, L8 `../SceneCulling/SceneCulling.ush`, L12 `NaniteDataDecode.ush`, L13 `NaniteSceneCommon.ush`

#### Macros (#define, 1)

- L10 `#define NANITE_MULTI_VIEW 1`

#### Entry points (2)

- L36-103 _entry_ `[numthreads(THREAD_GROUP_SIZE, 1, 1)] void NaniteSkinningUpdateChunkCullCS(uint ChunkId : SV_DispatchThreadID)` — stage: **compute** — C++: `FNaniteSkinningUpdateChunkCullCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Skinning/SkinningSceneExtension.cpp:1762)
- L109-177 _entry_ `[numthreads(THREAD_GROUP_SIZE, 1, 1)] void NaniteSkinningUpdateViewDataCS(uint3 GroupId : SV_GroupID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FNaniteSkinningUpdateViewDataCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Skinning/SkinningSceneExtension.cpp:1727)

#### Global resources (textures / buffers / samplers) (3)

- L17 _resource_ `RWStructuredBuffer<uint2> OutInstanceWorkGroups;`
- L18 _resource_ `RWBuffer<uint> OutInstanceWorkArgs;`
- L107 _resource_ `StructuredBuffer<uint2> InstanceWorkGroups;`

#### Global parameters (uniforms) (1)

- L15 _parameter_ `float DefaultAnimationMinScreenSize;`

#### Functions (2)

- L20-25 _function_ `void EmitChunk(uint ChunkId, uint ViewMask)`
- L31-34 _function_ `float GetScreenMultipleSquared(FNaniteView NaniteView)` — We do this instead of relying on FNaniteView::CullingViewScreenMultipleSq because that has a number of other factors based into it, some which make no sense for Nanite. This should ideally be cleaned up in the future.

### `Shaders/Private/Nanite/NaniteSplit.usf` (Private)

- lines: 438; parse: all-branches
- includes: L6 `../Common.ush`, L7 `../SceneData.ush`, L8 `NaniteAttributeDecode.ush`, L9 `NaniteTessellation.ush`, L10 `NaniteHZBCull.ush`, L11 `NaniteCullingCommon.ush`, L12 `NaniteVertexDeformation.ush`, L14 `../VirtualShadowMaps/VirtualShadowMapPageOverlap.ush` [VIRTUAL_TEXTURE_TARGET]

#### Macros (#define, 2)

- L3 `#define SPLIT_WORK_QUEUE 1`
- L4 `#define OCCLUDED_PATCHES_QUEUE (CULLING_PASS == 1)`

#### Entry points (4)

- L343-376 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void PatchSplit( uint GroupID : SV_GroupID, uint GroupIndex : SV_GroupIndex )` — stage: **compute** — C++: `FPatchSplitCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteCullRaster.cpp:1425) _[#if NANITE_TESSELLATION && PATCHSPLIT_PASS]_
- L382-389 _entry_ `[numthreads(1, 1, 1)] void InitClearQueueArgs()` — stage: **compute** _[#if NANITE_TESSELLATION && !(PATCHSPLIT_PASS)]_
- L391-399 _entry_ `[numthreads(64, 1, 1)] void ClearQueue(uint DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** _[#if NANITE_TESSELLATION && !(PATCHSPLIT_PASS)]_
- L404-433 _entry_ `[numthreads(NANITE_TESSELLATION_MAX_PATCH_SPLIT_LEVELS, 1, 1)] void InitPatchSplitArgs(uint GroupID : SV_GroupID, uint GroupIndex : SV_GroupIndex)` — stage: **compute** — C++: `FInitPatchSplitArgs_CS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteCullRaster.cpp:1317) _[#if NANITE_TESSELLATION && !(PATCHSPLIT_PASS)]_

#### Structs / classes (1)

- L52-72 _struct_ **`FSplitTask`** `struct FSplitTask` _[#if NANITE_TESSELLATION && PATCHSPLIT_PASS]_
  - L54 _member_ `FTessellatedPatch TessellatedPatch;` _[#if NANITE_TESSELLATION && PATCHSPLIT_PASS]_
  - L56 _member_ `uint4 Encoded;` _[#if NANITE_TESSELLATION && PATCHSPLIT_PASS]_
  - L57 _member_ `uint QueueOffset;` _[#if NANITE_TESSELLATION && PATCHSPLIT_PASS]_
  - L59 _method_proto_ `void Init( uint VisibleClusterIndex, uint TriIndex )` _[#if NANITE_TESSELLATION && PATCHSPLIT_PASS]_
  - L61 _method_proto_ `template< typename QueueType > bool Load( QueueType WorkQueue, uint Offset )` _[#if NANITE_TESSELLATION && PATCHSPLIT_PASS]_
  - L63 _method_proto_ `template< typename QueueType > void Store( QueueType WorkQueue, uint Offset )` _[#if NANITE_TESSELLATION && PATCHSPLIT_PASS]_
  - L65 _method_proto_ `template< typename QueueType > void Clear( QueueType WorkQueue, uint Offset )` _[#if NANITE_TESSELLATION && PATCHSPLIT_PASS]_
  - L68 _method_proto_ `uint Run()` _[#if NANITE_TESSELLATION && PATCHSPLIT_PASS]_
  - L70 _method_proto_ `FSplitTask CreateChild( uint ParentLaneIndex )` _[#if NANITE_TESSELLATION && PATCHSPLIT_PASS]_
  - L71 _method_proto_ `void RunChild( inout FSplitTask ParentTask, bool bActive, uint LocalItemIndex )` _[#if NANITE_TESSELLATION && PATCHSPLIT_PASS]_

#### Global resources (textures / buffers / samplers) (7)

- L41 _resource_ `StructuredBuffer<FNaniteRasterBinMeta> RasterBinMeta;` _[#if NANITE_TESSELLATION && PATCHSPLIT_PASS]_
- L43 _resource_ `Buffer<uint> CurrentIndirectArgs;` _[#if NANITE_TESSELLATION && PATCHSPLIT_PASS]_
- L44 _resource_ `RWBuffer<uint> NextIndirectArgs;` _[#if NANITE_TESSELLATION && PATCHSPLIT_PASS]_
- L49 _resource_ `RWStructuredBuffer<FNaniteStats> OutStatsBuffer;` _[#if NANITE_TESSELLATION && PATCHSPLIT_PASS && WRITE_STATS]_
- L380 _resource_ `RWBuffer<uint> OutClearQueueArgs;` _[#if NANITE_TESSELLATION && !(PATCHSPLIT_PASS)]_
- L401 _resource_ `RWBuffer< uint > OutPatchSplitArgs0;` _[#if NANITE_TESSELLATION && !(PATCHSPLIT_PASS)]_
- L402 _resource_ `RWBuffer< uint > OutPatchSplitArgs1;` _[#if NANITE_TESSELLATION && !(PATCHSPLIT_PASS)]_

#### Global parameters (uniforms) (2)

- L40 _parameter_ `uint RegularMaterialRasterSlotCount;` _[#if NANITE_TESSELLATION && PATCHSPLIT_PASS]_
- L46 _parameter_ `uint Level;` _[#if NANITE_TESSELLATION && PATCHSPLIT_PASS]_

#### Functions (8)

- L22-38 _function_ `void DisplaceBounds( float3 ConeCenter, float ConeCos, float DisplacementMin, float DisplacementMax, inout float3 BoundsMin, inout float3 BoundsMax )` — [ Nießner and Loop 2021, "Patch-Based Occlusion Culling for Hardware Tessellation" ] Input cone bounds normalized displacement directions _[#if NANITE_TESSELLATION && PATCHSPLIT_PASS]_
- L74-80 _function_ `void FSplitTask::Init( uint VisibleClusterIndex, uint TriIndex )` (scope `FSplitTask`) _[#if NANITE_TESSELLATION && PATCHSPLIT_PASS]_
- L82-94 _function_ `template< typename QueueType > bool FSplitTask::Load( QueueType WorkQueue, uint Offset )` (scope `FSplitTask`) _[#if NANITE_TESSELLATION && PATCHSPLIT_PASS]_
- L96-106 _function_ `template< typename QueueType > void FSplitTask::Store( QueueType WorkQueue, uint Offset )` (scope `FSplitTask`) _[#if NANITE_TESSELLATION && PATCHSPLIT_PASS]_
- L108-115 _function_ `template< typename QueueType > void FSplitTask::Clear( QueueType WorkQueue, uint Offset )` (scope `FSplitTask`) _[#if NANITE_TESSELLATION && PATCHSPLIT_PASS]_
- L117-288 _function_ `uint FSplitTask::Run()` (scope `FSplitTask`) _[#if NANITE_TESSELLATION && PATCHSPLIT_PASS]_
- L290-296 _function_ `FSplitTask FSplitTask::CreateChild( uint ParentLaneIndex )` (scope `FSplitTask`) _[#if NANITE_TESSELLATION && PATCHSPLIT_PASS]_
- L298-341 _function_ `void FSplitTask::RunChild( inout FSplitTask ParentTask, bool bActive, uint LocalItemIndex )` (scope `FSplitTask`) _[#if NANITE_TESSELLATION && PATCHSPLIT_PASS]_

### `Shaders/Private/Nanite/NaniteStreamOut.usf` (Private)

- lines: 745; parse: all-branches
- includes: L3 `/Engine/Shared/NaniteDefinitions.h`, L16 `NaniteHierarchyTraversal.ush` [NANITE_HIERARCHY_TRAVERSAL], L20 `../Common.ush`, L22 `../WaveOpUtil.ush`, L23 `../ComputeShaderUtils.ush`, L25 `NaniteDataDecode.ush`, L26 `NaniteAttributeDecode.ush`, L27 `NaniteCulling.ush`

#### Macros (#define, 7)

- L6 `#define NANITE_HIERARCHY_TRAVERSAL 0` _[#if !defined(NANITE_HIERARCHY_TRAVERSAL)]_
- L9 `#define DEFINE_ITERATE_CLUSTER_SEGMENTS (1)`
- L13 `#define NANITE_HIERARCHY_TRAVERSAL_TYPE (CULLING_TYPE)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
- L14 `#define GROUP_NODE_SIZE 3` _[#if NANITE_HIERARCHY_TRAVERSAL]_
- L692 `#define STREAM_OUT_GROUP_SIZE (64)` _[#if !NANITE_HIERARCHY_TRAVERSAL]_
- L693 `#define STREAM_OUT_NUM_CLUSTER_PER_THREAD (8)` _[#if !NANITE_HIERARCHY_TRAVERSAL]_
- L694 `#define STREAM_OUT_NUM_GROUPS_DIVISOR (STREAM_OUT_GROUP_SIZE * STREAM_OUT_NUM_CLUSTER_PER_THREAD)` _[#if !NANITE_HIERARCHY_TRAVERSAL]_

#### Entry points (4)

- L598-606 _entry_ `[numthreads(NANITE_PERSISTENT_CLUSTER_CULLING_GROUP_SIZE, 1, 1)] void NaniteStreamOutTraversalCS(uint GroupID : SV_GroupID, uint GroupIndex : SV_GroupIndex)` — stage: **compute** — C++: `FNaniteStreamOutTraversalCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteStreamOut.cpp:118) _[#if NANITE_HIERARCHY_TRAVERSAL]_
- L660-690 _entry_ `[numthreads(64, 1, 1)] void InitQueue(uint GroupIndex : SV_GroupIndex, uint3 GroupId : SV_GroupID)` — stage: **compute** — C++: `FInitQueueCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteStreamOut.cpp:63) _[#if !NANITE_HIERARCHY_TRAVERSAL]_
- L698-716 _entry_ `[numthreads(64, 1, 1)] void AllocateRangesCS(uint GroupIndex : SV_GroupIndex, uint3 GroupId : SV_GroupID)` — stage: **compute** — C++: `FAllocateRangesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteStreamOut.cpp:143) _[#if !NANITE_HIERARCHY_TRAVERSAL]_
- L720-742 _entry_ `[numthreads(STREAM_OUT_GROUP_SIZE, 1, 1)] void NaniteStreamOutCS(uint GroupIndex : SV_GroupIndex, uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FNaniteStreamOutCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteStreamOut.cpp:181) _[#if !NANITE_HIERARCHY_TRAVERSAL]_

#### Structs / classes (6)

- L43-51 _struct_ **`FNaniteStreamOutRequest`** `struct FNaniteStreamOutRequest`
  - L45 _member_ `uint PrimitiveId;`
  - L46 _member_ `uint NumMaterials;`
  - L47 _member_ `uint NumSegments;`
  - L48 _member_ `uint SegmentMappingOffset;`
  - L49 _member_ `uint AuxiliaryDataOffset;`
  - L50 _member_ `uint MeshDataOffset;`
- L155-162 _struct_ **`FCandidateCluster`** `struct FCandidateCluster`
  - L157 _member_ `uint PageIndex;`
  - L158 _member_ `uint ClusterIndex;`
  - L159 _member_ `uint PrimitiveId;`
  - L160 _member_ `uint RequestIndex;`
  - L161 _member_ `uint AssemblyTransformIndex;`
- L190-196 _struct_ **`FCandidateNodeRT`** `struct FCandidateNodeRT`
  - L192 _member_ `uint NodeIndex;`
  - L193 _member_ `uint PrimitiveId;`
  - L194 _member_ `uint RequestIndex;`
  - L195 _member_ `uint AssemblyTransformIndex;`
- L330-344 _struct_ **`FStreamOutClusterSegmentProcessor`** `struct FStreamOutClusterSegmentProcessor`
  - L332 _member_ `uint ClusterVertexOffset;`
  - L333 _member_ `uint MeshDataOffset;`
  - L334 _member_ `uint IndexBufferOffset;`
  - L335 _member_ `uint AuxiliaryDataOffset;`
  - L336 _member_ `FCluster Cluster;`
  - L337 _member_ `FCandidateCluster CandidateCluster;`
  - L338 _member_ `FNaniteStreamOutRequest RequestData;`
  - L340 _method_ `void Process(uint TriStart, uint TriLength, uint MaterialIndex)`
- L411-423 _struct_ **`FCountTrianglesClusterSegmentProcessor`** `struct FCountTrianglesClusterSegmentProcessor` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L413 _member_ `uint MeshDataOffset;` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L414 _member_ `FNaniteStreamOutRequest RequestData;` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L416 _method_ `void Process(uint TriStart, uint TriLength, uint MaterialIndex)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
- L425-596 _struct_ **`FNaniteTraversalStreamOutCallback`** `struct FNaniteTraversalStreamOutCallback` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L427 _member_ `FCandidateNodeRT CandidateNode;` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L429 _member_ `FPrimitiveSceneData PrimitiveData;` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L431 _member_ `uint AssemblyTransformIndex;` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L433 _method_ `void Init(uint InChildIndex, uint InLocalNodeIndex, uint GroupNodeFetchIndex)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L444 _method_ `uint GetHierarchyNodeOffset()` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L449 _method_ `bool ShouldVisitChild(FHierarchyNodeSlice HierarchyNodeSlice, bool bInVisible)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L475 _method_ `void OnPreProcessNodeBatch(uint GroupIndex)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L480 _method_ `void OnPostNodeVisit(FHierarchyNodeSlice HierarchyNodeSlice)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L485 _method_ `void StoreChildNode(uint StoreIndex, FHierarchyNodeSlice HierarchyNodeSlice)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L496 _method_ `void StoreCluster(uint StoreIndex, FHierarchyNodeSlice HierarchyNodeSlice, uint ClusterIndex)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L508 _method_ `uint4 LoadPackedCluster(uint CandidateIndex)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L514 _method_ `bool IsNodeDataReady(uint4 RawData)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L519 _method_ `bool LoadCandidateNodeDataToGroup(uint NodeIndex, uint GroupIndex, bool bCheckIfReady = true)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L532 _method_ `void ClearCandidateNodeData(uint NodeIndex)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L537 _method_ `void AddToClusterBatch(uint BatchIndex, uint Num)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L542 _method_ `void ClearClusterBatch(uint BatchIndex)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L547 _method_ `uint LoadClusterBatch(uint BatchIndex)` _[#if NANITE_HIERARCHY_TRAVERSAL]_
  - L553 _method_ `void ProcessCluster(uint4 PackedCluster)` _[#if NANITE_HIERARCHY_TRAVERSAL]_

#### Global resources (textures / buffers / samplers) (15)

- L53 _resource_ `StructuredBuffer<FNaniteStreamOutRequest> StreamOutRequests;`
- L56 _resource_ `ByteAddressBuffer SegmentMappingBuffer;`
- L107 _resource_ `RWStructuredBuffer<uint> MeshDataBuffer;`
- L108 _resource_ `RWStructuredBuffer<float> VertexBuffer;` — can't use RWStructuredBuffer<float3> because of bDisableScalarBlockLayout
- L109 _resource_ `RWStructuredBuffer<uint> IndexBuffer;`
- L110 _resource_ `RWByteAddressBuffer AuxiliaryDataBufferRW;`
- L112 _resource_ `RWByteAddressBuffer OutputClustersRW;`
- L113 _resource_ `RWStructuredBuffer<uint> OutputClustersStateRW;`
- L116 _resource_ `RWStructuredBuffer<uint> VertexAndIndexAllocator;` — \| current vertex marker \| current index marker \|
- L408 _resource_ `RWByteAddressBuffer Nodes;` _[#if NANITE_HIERARCHY_TRAVERSAL]_
- L409 _resource_ `RWByteAddressBuffer CandidateClusters;` _[#if NANITE_HIERARCHY_TRAVERSAL]_
- L657 _resource_ `RWStructuredBuffer<FQueueState> QueueState;` _[#if !NANITE_HIERARCHY_TRAVERSAL]_
- L658 _resource_ `RWByteAddressBuffer Nodes;` _[#if !NANITE_HIERARCHY_TRAVERSAL]_
- L696 _resource_ `RWBuffer<uint> StreamOutDispatchIndirectArgsRW;` _[#if !NANITE_HIERARCHY_TRAVERSAL]_
- L718 _resource_ `ByteAddressBuffer OutputClusters;` _[#if !NANITE_HIERARCHY_TRAVERSAL]_

#### Global parameters (uniforms) (4)

- L54 _parameter_ `uint NumRequests;`
- L58 _parameter_ `float StreamOutCutError;`
- L117 _parameter_ `uint VertexBufferSize;`
- L118 _parameter_ `uint IndexBufferSize;`

#### Functions (30)

- L72-75 _function_ `uint GetMeshClusterCountIndex(uint MeshDataOffset)`
- L77-80 _function_ `uint GetMeshVertexBufferOffsetIndex(uint MeshDataOffset)`
- L82-85 _function_ `uint GetMeshIndexBufferOffsetIndex(uint MeshDataOffset)`
- L87-90 _function_ `uint GetMeshVertexCountIndex(uint MeshDataOffset)`
- L92-95 _function_ `uint GetMeshIndexCountIndex(uint MeshDataOffset)`
- L97-100 _function_ `uint GetMeshSegmentIndexCountIndex(uint MeshDataOffset, uint SegmentIndex)`
- L102-105 _function_ `uint GetMeshSegmentIndexBufferOffsetIndex(uint MeshDataOffset, uint SegmentIndex)`
- L120-130 _function_ `bool Allocate(uint Size, uint BufferSize, uint AllocatorEntry, out uint OutOffset)`
- L132-135 _function_ `uint Align16(uint Value)`
- L137-153 _function_ `bool AllocateVertexAndIndexRanges(uint VertexSize, uint IndexSize, out uint OutVertexOffset, out uint OutIndexOffset)`
- L164-174 _function_ `uint4 PackCandidateClusterRT(uint ClusterIdx, FCandidateCluster CandidateCluster)`
- L176-188 _function_ `FCandidateCluster UnpackCandidateClusterRT(uint4 RawData)`
- L198-212 _function_ `uint4 PackCandidateNodeRT(FCandidateNodeRT Node)`
- L214-225 _function_ `FCandidateNodeRT UnpackCandidateNodeRT(uint4 RawData)`
- L227 _function_ `uint GetCandidateNodeSizeRT()`
- L228 _function_ `uint GetCandidateClusterSizeRT()`
- L230-234 _function_ `FCandidateCluster LoadCandidateClusterRT(ByteAddressBuffer CandidateClusters, uint ClusterIndex)`
- L236-239 _function_ `void StorePackedCandidateClusterRT(RWByteAddressBuffer CandidateClusters, uint ClusterIndex, uint4 PackedCluster)`
- L241-245 _function_ `void StoreCandidateClusterNoCheckRT(RWByteAddressBuffer CandidateClusters, uint ClusterIndex, FCandidateCluster CandidateCluster)`
- L247-251 _function_ `void StoreCandidateClusterRT(RWByteAddressBuffer CandidateClusters, uint ClusterIndex, FCandidateCluster CandidateCluster)`
- L253-257 _function_ `uint4 LoadCandidateNodeDataRT(RWByteAddressBuffer InNodes, uint NodeIndex)`
- L259-263 _function_ `void StoreCandidateNodeDataRT(RWByteAddressBuffer InNodes, uint NodeIndex, uint4 RawData)`
- L265-269 _function_ `void StoreCandidateNodeRT(RWByteAddressBuffer InNodes, uint NodeIndex, FCandidateNodeRT Node)`
- L271-275 _function_ `void ClearCandidateNodeRT(RWByteAddressBuffer InNodes, uint NodeIndex)`
- L277-280 _function_ `bool IsAssemblyPartCluster(FCandidateCluster CandidateCluster)`
- L282-294 _function_ `void WriteAuxiliaryData(FCandidateCluster CandidateCluster, uint TriangleIndex, uint AuxiliaryDataBufferOffset)`
- L296-307 _function_ `void WriteTriangles(FCluster Cluster, FCandidateCluster CandidateCluster, uint StartTriangle, uint NumTriangles, uint BaseIndex, uint IndexBufferOffset, uint AuxiliaryDataBufferOffset)`
- L309-328 _function_ `void WriteSegment(uint MaterialIndex, uint TriStart, uint TriLength, uint ClusterVertexOffset, uint MeshDataOffset, uint IndexBufferOffset, uint AuxiliaryDataOffset, FCluster Cluster, FCandidateCluster CandidateCluster, FNaniteStreamOutRequest RequestData)`
- L346-404 _function_ `void StreamOutClusterCommon(FCluster Cluster, FCandidateCluster CandidateCluster, FNaniteStreamOutRequest RequestData)`
- L612-655 _function_ `bool AllocateRangesCommon(FNaniteStreamOutRequest RequestData)` _[#if !NANITE_HIERARCHY_TRAVERSAL]_

### `Shaders/Private/Nanite/NaniteStreaming.usf` (Private)

- lines: 30; parse: all-branches
- includes: L3 `../Common.ush`, L4 `NaniteDataDecode.ush`, L5 `NaniteStreaming.ush`, L6 `../ComputeShaderUtils.ush`

#### Entry points (2)

- L11-15 _entry_ `[numthreads(1, 1, 1)] void ClearStreamingRequestCount()` — stage: **compute** — C++: `FClearStreamingRequestCount_CS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Engine/Private/Nanite/NaniteReadbackManager.cpp:48)
- L21-30 _entry_ `[numthreads(64, 1, 1)] void Memcpy(uint3 GroupID : SV_GroupID, uint GroupIndex : SV_GroupIndex)` — stage: **compute** — C++: `FMemcpy_CS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Engine/Private/Rendering/NaniteStreamingManager.cpp:323)

#### Global resources (textures / buffers / samplers) (2)

- L8 _resource_ `RWStructuredBuffer<FStreamingRequest> OutStreamingRequests;`
- L9 _resource_ `RWByteAddressBuffer DstBuffer;`

#### Global parameters (uniforms) (3)

- L17 _parameter_ `uint SrcOffset;`
- L18 _parameter_ `uint DstOffset;`
- L19 _parameter_ `uint NumThreads;`

### `Shaders/Private/Nanite/NaniteStreaming.ush` (Private)

- lines: 49; parse: all-branches
- includes: L5 `../Common.ush`, L6 `../WaveOpUtil.ush`, L7 `/Engine/Shared/NaniteDefinitions.h`
- L3 #pragma `once`

#### Structs / classes (1)

- L9-14 _struct_ **`FStreamingRequest`** `struct FStreamingRequest`
  - L11 _member_ `uint RuntimeResourceID_Magic;`
  - L12 _member_ `uint ResourcePageRangeKey;`
  - L13 _member_ `uint Priority_Magic;`

#### Global parameters (uniforms) (2)

- L16 _parameter_ `uint StreamingRequestsBufferVersion;`
- L17 _parameter_ `uint StreamingRequestsBufferSize;`

#### Functions (1)

- L19-49 _function_ `void RequestPageRange( RWStructuredBuffer<FStreamingRequest> RequestsBuffer, uint RuntimeResourceID, uint ResourcePageRangeKey, uint PriorityCategory, float Priority )`

### `Shaders/Private/Nanite/NaniteTessellation.ush` (Private)

- lines: 357; parse: all-branches
- includes: L5 `../Common.ush`, L6 `NaniteSceneCommon.ush`, L325 `../WorkDistribution.ush` [NANITE_TESSELLATION]

#### Macros (#define, 3)

- L8 `#define NANITE_TESSELLATION_PATCH_REFS 1`
- L9 `#define NANITE_TESSELLATION_NORMALIZE 0`
- L324 `#define THREADGROUP_SIZE 32` _[#if NANITE_TESSELLATION]_
- L3 #pragma `once`

#### Structs / classes (2)

- L135-266 _struct_ **`FTessellatedPatch`** `struct FTessellatedPatch` _[#if NANITE_TESSELLATION]_
  - L137 _member_ `uint TableOffset;` _[#if NANITE_TESSELLATION]_
  - L138 _member_ `uint Pattern_NumVerts_NumTris;` _[#if NANITE_TESSELLATION]_
  - L141 _method_ `void Init( float3 TessFactors, inout uint3 VertData, bool bImmediateTable )` _[#if NANITE_TESSELLATION]_
  - L187 _method_ `void Init( uint InPattern, bool bImmediateTable)` _[#if NANITE_TESSELLATION]_
  - L195 _method_ `uint GetPattern()` _[#if NANITE_TESSELLATION]_
  - L196 _method_ `uint GetNumVerts()` _[#if NANITE_TESSELLATION]_
  - L197 _method_ `uint GetNumTris()` _[#if NANITE_TESSELLATION]_
  - L199 _method_ `float3 GetVert( uint VertIndex )` _[#if NANITE_TESSELLATION]_
  - L206 _method_ `uint3 GetIndexes( uint TriIndex )` _[#if NANITE_TESSELLATION]_
  - L224 _method_ `uint3 GetTriangleEncoded( uint TriIndex )` _[#if NANITE_TESSELLATION]_
  - L253 _method_ `uint3 GetTessFactors()` _[#if NANITE_TESSELLATION]_
- L278-307 _struct_ **`FSplitPatch`** `struct FSplitPatch` _[#if NANITE_TESSELLATION]_
  - L280 _member_ `uint VisibleClusterIndex;` _[#if NANITE_TESSELLATION]_
  - L281 _member_ `uint TriIndex;` _[#if NANITE_TESSELLATION]_
  - L282 _member_ `float3 Barycentrics[3];` _[#if NANITE_TESSELLATION]_
  - L284 _method_ `void Decode( uint4 Encoded )` _[#if NANITE_TESSELLATION]_
  - L291 _method_ `float3 TransformBarycentrics( float3 Local )` _[#if NANITE_TESSELLATION]_
  - L299 _method_ `FBarycentrics TransformBarycentrics( FBarycentrics Local )` _[#if NANITE_TESSELLATION]_

#### Global resources (textures / buffers / samplers) (10)

- L46 _resource_ `ByteAddressBuffer TessellationTable_Offsets;` _[#if NANITE_TESSELLATION]_
- L47 _resource_ `ByteAddressBuffer TessellationTable_VertsAndIndexes;` _[#if NANITE_TESSELLATION]_
- L328 _resource_ `RWByteAddressBuffer SplitWorkQueue_DataBuffer;` _[#if NANITE_TESSELLATION && SPLIT_WORK_QUEUE]_
- L329 _resource_ `RWStructuredBuffer< FWorkQueueState > SplitWorkQueue_StateBuffer;` _[#if NANITE_TESSELLATION && SPLIT_WORK_QUEUE]_
- L338 _resource_ `RWByteAddressBuffer OccludedPatches_DataBuffer;` _[#if NANITE_TESSELLATION]_
- L339 _resource_ `RWStructuredBuffer< FWorkQueueState > OccludedPatches_StateBuffer;` _[#if NANITE_TESSELLATION]_
- L350 _resource_ `ByteAddressBuffer VisiblePatches;` _[#if NANITE_TESSELLATION]_
- L351 _resource_ `Buffer< uint > VisiblePatchesArgs;` _[#if NANITE_TESSELLATION]_
- L354 _resource_ `RWByteAddressBuffer RWVisiblePatches;` _[#if NANITE_TESSELLATION]_
- L355 _resource_ `RWBuffer< uint > RWVisiblePatchesArgs;` _[#if NANITE_TESSELLATION]_

#### Global parameters (uniforms) (1)

- L352 _parameter_ `uint VisiblePatchesSize;` _[#if NANITE_TESSELLATION]_

#### static const (3)

- L13 _static_const_ `static const uint BarycentricMax = (1 << 15);` — Must be pow2 _[#if NANITE_TESSELLATION]_
- L335 _static_const_ `static const FOutputQueue SplitWorkQueue = { GetSplitWorkQueue_DataBuffer(), GetSplitWorkQueue_StateBuffer(), 0, NaniteRaster.MaxCandidatePatches };` _[#if NANITE_TESSELLATION && SPLIT_WORK_QUEUE]_
- L347 _static_const_ `static const FOutputQueue OccludedPatches = { GetOccludedPatches_DataBuffer(), GetOccludedPatches_StateBuffer(), 0, NaniteRaster.MaxCandidatePatches };` _[#if NANITE_TESSELLATION && OCCLUDED_PATCHES_QUEUE]_

#### Functions (12)

- L15-32 _function_ `uint EncodeBarycentrics( float3 Barycentrics )` _[#if NANITE_TESSELLATION]_
- L34-43 _function_ `float3 DecodeBarycentrics( uint Encoded )` _[#if NANITE_TESSELLATION]_
- L49-60 _function_ `float CalcDisplacementLowTessDistance(FPrimitiveSceneData PrimitiveData, FInstanceSceneData InstanceData, FNaniteView NaniteView)` _[#if NANITE_TESSELLATION]_
- L62-101 _function_ `float3 GetTessFactors( FNaniteView NaniteView, float3 PointView[3], float LowTessDistance )` _[#if NANITE_TESSELLATION]_
- L103-123 _function_ `float3 GetSplitFactors( float3 TessFactors )` _[#if NANITE_TESSELLATION]_
- L125-133 _function_ `float2 CalculateUVDerivativeForDomainPoint( FNaniteView NaniteView, float ViewZ, float UniformScale, float UVDensity )` _[#if NANITE_TESSELLATION]_
- L269-275 _function_ `FTessellatedPatch WaveReadLaneAt( FTessellatedPatch In, uint SrcIndex )` _[#if NANITE_TESSELLATION]_
- L310-321 _function_ `FSplitPatch WaveReadLaneAt(FSplitPatch In, uint SrcIndex)` _[#if NANITE_TESSELLATION]_
- L332 _function_ `RWByteAddressBuffer GetSplitWorkQueue_DataBuffer()` — TODO: Use function to return a non-const variable before setting it in the queue to work around issue in bindless, remove when fixed in DXC _[#if NANITE_TESSELLATION && SPLIT_WORK_QUEUE]_
- L333 _function_ `RWStructuredBuffer< FWorkQueueState > GetSplitWorkQueue_StateBuffer()` _[#if NANITE_TESSELLATION && SPLIT_WORK_QUEUE]_
- L344 _function_ `RWByteAddressBuffer GetOccludedPatches_DataBuffer()` — TODO: Use function to return a non-const variable before setting it in the queue to work around issue in bindless, remove when fixed in DXC _[#if NANITE_TESSELLATION && OCCLUDED_PATCHES_QUEUE]_
- L345 _function_ `RWStructuredBuffer< FWorkQueueState > GetOccludedPatches_StateBuffer()` _[#if NANITE_TESSELLATION && OCCLUDED_PATCHES_QUEUE]_

#### Top-level macro invocations (2)

- L268 _macro_call_ `HLSL_STATIC_ASSERT(sizeof(FTessellatedPatch) == 8, "Unexpected size of FTessellatedPatch. Update WaveReadLaneAt to reflect changes.")` _[#if NANITE_TESSELLATION]_
- L309 _macro_call_ `HLSL_STATIC_ASSERT(sizeof(FSplitPatch) == 44, "Unexpected size of FSplitPatch. Update WaveReadLaneAt to reflect changes.")` _[#if NANITE_TESSELLATION]_

### `Shaders/Private/Nanite/NaniteTranscode.usf` (Private)

- lines: 723; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../SceneData.ush`, L5 `../ComputeShaderUtils.ush`, L6 `NaniteDataDecode.ush`, L7 `NaniteAttributeDecode.ush`

#### Macros (#define, 2)

- L35 `#define SIZEOF_PAGE_DISK_HEADER (5*4)`
- L51 `#define SIZEOF_CLUSTER_DISK_HEADER (10*4)`

#### Entry points (1)

- L698-721 _entry_ `[numthreads(GROUP_SIZE, 1, 1)] void TranscodePageToGPU(uint3 GroupID : SV_GroupID, uint GroupIndex : SV_GroupIndex)` — stage: **compute** — C++: `FTranscodePageToGPU_CS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Engine/Private/Nanite/NaniteStreamingPageUploader.cpp:109)

#### Structs / classes (4)

- L9-17 _struct_ **`FClusterInstallInfo`** `struct FClusterInstallInfo`
  - L11 _member_ `uint LocalPageIndex;`
  - L12 _member_ `uint LocalClusterIndex;`
  - L14 _member_ `uint SrcPageOffset;`
  - L15 _member_ `uint DstPageOffset;`
  - L16 _member_ `uint PageDependenciesOffset;`
- L19-25 _struct_ **`FPackedClusterInstallInfo`** `struct FPackedClusterInstallInfo`
  - L21 _member_ `uint LocalPageIndex_LocalClusterIndex;`
  - L22 _member_ `uint SrcPageOffset;`
  - L23 _member_ `uint DstPageOffset;`
  - L24 _member_ `uint PageDependenciesOffset;`
- L27-34 _struct_ **`FPageDiskHeader`** `struct FPageDiskHeader`
  - L29 _member_ `uint NumClusters;`
  - L30 _member_ `uint NumRawFloat4s;`
  - L31 _member_ `uint NumVertexRefs;`
  - L32 _member_ `uint StripBitmaskOffset;`
  - L33 _member_ `uint VertexRefBitmaskOffset;`
- L37-49 _struct_ **`FClusterDiskHeader`** `struct FClusterDiskHeader`
  - L39 _member_ `uint DecodeInfoOffset;`
  - L40 _member_ `uint IndexDataOffset;`
  - L41 _member_ `uint PageClusterMapOffset;`
  - L42 _member_ `uint VertexRefDataOffset;`
  - L43 _member_ `uint LowBytesDataOffset;`
  - L44 _member_ `uint MidBytesDataOffset;`
  - L45 _member_ `uint HighBytesDataOffset;`
  - L46 _member_ `uint NumVertexRefs;`
  - L47 _member_ `uint NumPrevRefVerticesBeforeDwords;`
  - L48 _member_ `uint NumPrevNewVerticesBeforeDwords;`

#### Global resources (textures / buffers / samplers) (4)

- L56 _resource_ `StructuredBuffer<FPackedClusterInstallInfo> ClusterInstallInfoBuffer;`
- L57 _resource_ `StructuredBuffer<uint> PageDependenciesBuffer;`
- L58 _resource_ `ByteAddressBuffer SrcPageBuffer;`
- L59 _resource_ `RWByteAddressBuffer DstPageBuffer;`

#### Global parameters (uniforms) (3)

- L53 _parameter_ `uint StartClusterIndex;`
- L54 _parameter_ `uint NumClusters;`
- L55 _parameter_ `uint ZeroUniform;`

#### groupshared (2)

- L365 _groupshared_ `groupshared uint GroupRefToVertex[NANITE_MAX_CLUSTER_VERTICES];`
- L366 _groupshared_ `groupshared uint GroupNonRefToVertex[NANITE_MAX_CLUSTER_VERTICES];`

#### Functions (15)

- L62-74 _function_ `FPageDiskHeader GetPageDiskHeader(uint PageBaseOffset)`
- L76-96 _function_ `FClusterDiskHeader GetClusterDiskHeader(uint PageBaseOffset, uint ClusterIndex)`
- L98-111 _function_ `FClusterInstallInfo GetClusterInstallInfo(uint Index)`
- L113-121 _function_ `uint ReadUnalignedDword(ByteAddressBuffer InputBuffer, uint BaseAddressInBytes, int BitOffset)`
- L123-145 _function_ `template<uint NumComponents> uint4 ReadBytes(ByteAddressBuffer InputBuffer, uint BaseAddress, uint Index)`
- L147-151 _function_ `int DecodeZigZag(uint Data)`
- L153-158 _function_ `uint3 LowMidHighIncrement(uint NumBytesPerValue, uint Num)`
- L160-189 _function_ `template<uint NumComponents, uint MaxBytesPerDelta> int4 UnpackZigZagDeltas(ByteAddressBuffer InputBuffer, uint3 LowMidHighOffsets, uint BytesPerDelta, uint Index, inout int4 PrevLastValue)`
- L192-198 _function_ `void CopyDwords(RWByteAddressBuffer DstBuffer, uint DstAddress, ByteAddressBuffer SrcBuffer, uint SrcAddress, uint NumDwords)` — Debug only. Performance doesn't matter.
- L200-298 _function_ `uint3 UnpackStripIndices(uint SrcPageBaseOffset, FPageDiskHeader PageDiskHeader, FClusterDiskHeader ClusterDiskHeader, uint LocalClusterIndex, uint TriIndex)`
- L300-363 _function_ `template<uint NumTexCoords> void TranscodeVertexAttributes(FPageDiskHeader PageDiskHeader, FClusterDiskHeader ClusterDiskHeader, FCluster Cluster, uint DstPageBaseOffset, uint LocalClusterIndex, uint VertexIndex, FCluster RefCluster, uint RefPageBaseOffset, uint RefVertexIndex, uint SrcPageBaseOffset)`
- L368-396 _function_ `template<bool bRefToVertex, bool bNonRefToVertex> void BuildRefTable(uint AlignedBitmaskOffset, uint NumVerts, uint WaveNumActiveLanes, uint GroupIndex)`
- L398-404 _function_ `FPageHeader PageHeaderFromPageDiskHeader(FPageDiskHeader PageDiskHeader)`
- L406-594 _function_ `void TranscodePageIndependent(uint ClusterInstallIndex, uint WaveNumActiveLanes, uint GroupIndex)`
- L596-692 _function_ `void TranscodePageParentDependent(uint ClusterInstallIndex, uint WaveNumActiveLanes, uint GroupIndex)`

#### Top-level macro invocations (1)

- L695 _macro_call_ `WAVESIZE(GROUP_SIZE)` _[#if COMPILER_SUPPORTS_WAVE_SIZE]_

### `Shaders/Private/Nanite/NaniteTranslucency.usf` (Private)

- lines: 62; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../SceneData.ush`, L5 `../ViewData.ush`, L6 `../WaveOpUtil.ush`, L7 `../ComputeShaderUtils.ush`, L9 `NaniteDataDecode.ush`

#### Entry points (1)

- L19-61 _entry_ `[numthreads(64, 1, 1)] void TranscodeRasterizerArgs(uint RasterBin : SV_DispatchThreadID)` — stage: **compute** — C++: `FTranscodeRasterizerArgs_CS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteTranslucency.cpp:149)

#### Global resources (textures / buffers / samplers) (2)

- L11 _resource_ `Buffer<uint> InRasterizerArgsSWHW;`
- L12 _resource_ `RWBuffer<uint> OutRasterizerArgsSWHW;`

#### Global parameters (uniforms) (3)

- L14 _parameter_ `uint RasterBinCount;`
- L16 _parameter_ `uint InputFormat;`
- L17 _parameter_ `uint OutputFormat;`

### `Shaders/Private/Nanite/NaniteTranslucencyFactory.ush` (Private)

- lines: 568; parse: all-branches
- includes: L15 `../VertexFactoryCommon.ush`, L16 `../LightmapData.ush`, L17 `../SplineMeshCommon.ush`, L18 `../SGGX.ush`, L19 `../ComputeShaderUtils.ush`, L22 `NaniteDataDecode.ush`, L23 `NaniteAttributeDecode.ush`, L24 `NaniteSceneCommon.ush`, L25 `NaniteVertexDeformation.ush`, L28 `NaniteRasterizationCommon.ush`, L30 `../VirtualShadowMaps/VirtualShadowMapPageAccessCommon.ush`, L31 `../VirtualShadowMaps/VirtualShadowMapPageOverlap.ush`, L33 `/Engine/Public/RootConstants.ush`

#### Macros (#define, 11)

- L7 `#define InViews TranslucentBasePass.NaniteTranslucency.InViews`
- L8 `#define RasterGroupMeta TranslucentBasePass.NaniteTranslucency.RasterGroupMeta`
- L9 `#define RasterBinMeta TranslucentBasePass.NaniteTranslucency.RasterBinMeta`
- L10 `#define RasterBinData TranslucentBasePass.NaniteTranslucency.RasterBinData`
- L13 `#define USE_HZB_SHARED_SAMPLERS 0`
- L21 `#define NANITE_VIEWS_DECLARATION 0`
- L27 `#define NANITE_MATERIAL_INCLUDES 0`
- L37 `#define NANITE_NUM_TEXCOORDS_TO_DECODE NUM_MATERIAL_TEXCOORDS_VERTEX` _[#if NUM_MATERIAL_TEXCOORDS_VERTEX > NUM_MATERIAL_TEXCOORDS]_
- L39 `#define NANITE_NUM_TEXCOORDS_TO_DECODE NUM_MATERIAL_TEXCOORDS` _[#if !(NUM_MATERIAL_TEXCOORDS_VERTEX > NUM_MATERIAL_TEXCOORDS)]_
- L44 `#define NANITE_NUM_TEXCOORDS_TO_DECODE_HW_VS 2` _[#if NANITE_PIXEL_PROGRAMMABLE && NANITE_NUM_TEXCOORDS_TO_DECODE < 2]_
- L46 `#define NANITE_NUM_TEXCOORDS_TO_DECODE_HW_VS NANITE_NUM_TEXCOORDS_TO_DECODE` _[#if !(NANITE_PIXEL_PROGRAMMABLE && NANITE_NUM_TEXCOORDS_TO_DECODE < 2)]_
- L3 #pragma `once`; L5 #pragma `message("UESHADERMETADATA_VERSION 0D21601A-4F76-42D0-BCAB-32B7ECC7AB54")`

#### Structs / classes (6)

- L66-70 _struct_ **`FTriRange`** `struct FTriRange`
  - L68 _member_ `uint Start;`
  - L69 _member_ `uint Num;`
- L72-78 _struct_ **`FClusterRef`** `struct FClusterRef`
  - L74 _member_ `FTriRange TriRange;`
  - L75 _member_ `uint VisibleIndex;`
  - L76 _member_ `uint MaterialFlags;`
  - L77 _member_ `uint RasterBin;`
- L130-142 _struct_ **`FVertexFactoryInterpolantsVSToPS`** `struct FVertexFactoryInterpolantsVSToPS`
  - L132 _member_ `TANGENTTOWORLD_INTERPOLATOR_BLOCK float4 TexCoords[(NUM_TEX_COORD_INTERPOLATORS+1)/2] : TEXCOORD0;`
  - L138 _member_ `float2 ClipZW : CLIP_ZW;` _[#if STORE_CLIP_ZW_IN_INTERPOLATOR]_
  - L140 _member_ `nointerpolation uint PrimitiveId : PRIMITIVE_ID;`
  - L141 _member_ `nointerpolation uint ViewIndex : PACKED_VIEW_INDEX;`
- L144-161 _struct_ **`FVertexFactoryMeshShaderIntermediates`** `struct FVertexFactoryMeshShaderIntermediates`
  - L146 _member_ `bool bValidIndex;`
  - L147 _member_ `bool bTriValid;`
  - L148 _member_ `uint DrawClusterIndex;`
  - L149 _member_ `FClusterRef ClusterRef;`
  - L150 _member_ `FTriRange TriRange;`
  - L151 _member_ `FCluster Cluster;`
  - L152 _member_ `FVisibleCluster VisibleCluster;`
  - L153 _member_ `FPrimitiveSceneData PrimitiveData;`
  - L154 _member_ `FInstanceSceneData InstanceData;`
  - L155 _member_ `FInstanceDynamicData InstanceDynamicData;`
  - L156 _member_ `FNaniteVertTransforms Transforms;`
  - L157 _member_ `FNaniteView NaniteView;`
  - L158 _member_ `uint TriIndex;`
  - L159 _member_ `uint NumUniqueVerts;`
  - L160 _member_ `uint3 VertIndexes;`
- L163-172 _struct_ **`FVertexFactoryInput`** `struct FVertexFactoryInput`
  - L166 _member_ `FVertexFactoryMeshShaderIntermediates MSIntermediates;` _[#if MESHSHADER]_
  - L167 _member_ `uint VertexID;` _[#if MESHSHADER]_
  - L169 _member_ `uint VertexID : SV_VertexID;` _[#if !(MESHSHADER)]_
  - L170 _member_ `uint VisibleIndex : SV_InstanceID;` _[#if !(MESHSHADER)]_
- L177-195 _struct_ **`FVertexFactoryIntermediates`** `struct FVertexFactoryIntermediates` — Caches intermediates that would otherwise have to be computed multiple times.  Avoids relying on the compiler to optimize out redundant operations.
  - L179 _member_ `FVisibleCluster VisibleCluster;`
  - L180 _member_ `FPrimitiveSceneData PrimitiveData;`
  - L181 _member_ `FInstanceSceneData InstanceData;`
  - L182 _member_ `FInstanceDynamicData InstanceDynamicData;`
  - L184 _member_ `float3x3 TangentToLocal;`
  - L185 _member_ `float3x3 TangentToWorld;`
  - L186 _member_ `float TangentToWorldSign;`
  - L188 _member_ `float4 Position;`
  - L190 _member_ `uint VertexID;`
  - L192 _member_ `FNanitePostDeformVertex Vertex;`
  - L194 _member_ `FNaniteVertTransforms Transforms;`

#### Functions (22)

- L49 _function_ `uint GetRasterGroup()`
- L52-63 _function_ `void SetBindlessMaterial(uint Index)` _[#if NANITE_BINDLESS]_
- L80-106 _function_ `template<bool bHardware> FClusterRef FetchClusterRef(const uint ClusterIndex)`
- L109-128 _function_ `bool ReverseWindingOrder(FNaniteView NaniteView, FPrimitiveSceneData PrimitiveData, FInstanceSceneData InstanceData)` — Default cull mode is CW. If this returns true, CCW culling is required
- L198-202 _function_ `float2 GetUV(FVertexFactoryInterpolantsVSToPS Interpolants, int UVIndex)` _[#if NUM_TEX_COORD_INTERPOLATORS]_
- L204-215 _function_ `void SetUV(inout FVertexFactoryInterpolantsVSToPS Interpolants, int UVIndex, float2 InValue)` _[#if NUM_TEX_COORD_INTERPOLATORS]_
- L219-234 _function_ `half3x3 CalcVertexTangentToLocal(FPrimitiveSceneData PrimitiveData, FInstanceSceneData InstanceData, FNanitePostDeformVertex Vert)` — Determines the tangent to local frame of the specified vertex
- L236-339 _function_ `FVertexFactoryIntermediates GetVertexFactoryIntermediates(FVertexFactoryInput Input)`
- L341-344 _function_ `float4 VertexFactoryGetWorldPosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)`
- L346-349 _function_ `float4 VertexFactoryGetRasterizedWorldPosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, float4 InWorldPosition)`
- L351-354 _function_ `half3x3 VertexFactoryGetTangentToLocal(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)`
- L356-398 _function_ `FMaterialVertexParameters GetMaterialVertexParameters(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, float3 WorldPosition, half3x3 TangentToLocal, bool bIsPreviousFrame = false)`
- L401-438 _function_ `FMaterialPixelParameters GetMaterialPixelParameters(FVertexFactoryInterpolantsVSToPS Interpolants, float4 SvPosition)` — Converts from vertex factory specific interpolants to a FMaterialPixelParameters, which is used by material inputs.
- L440-468 _function_ `FVertexFactoryInterpolantsVSToPS VertexFactoryGetInterpolantsVSToPS(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, FMaterialVertexParameters VertexParameters)`
- L470-477 _function_ `float4 VertexFactoryGetInstanceHitProxyId(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)`
- L479-534 _function_ `FVertexFactoryMeshShaderIntermediates VertexFactoryMeshShaderGetIntermediates(uint GroupThreadID, uint3 GroupID)`
- L536-539 _function_ `bool VertexFactoryMeshShaderIsValidIndex(FVertexFactoryMeshShaderIntermediates Intermediates)`
- L541-544 _function_ `bool VertexFactoryMeshShaderIsPrimitiveValid(FVertexFactoryMeshShaderIntermediates Intermediates, uint ExportIndex)`
- L546-549 _function_ `bool VertexFactoryMeshShaderIsVertexValid(FVertexFactoryMeshShaderIntermediates Intermediates, uint ExportIndex)`
- L551-555 _function_ `void VertexFactoryGetMeshShaderOutputCount(FVertexFactoryMeshShaderIntermediates Intermediates, out uint UniqueVertexCount, out uint TriangleCount)`
- L557-560 _function_ `void VertexFactoryDedupMeshShaderVertIndexes(inout FVertexFactoryMeshShaderIntermediates Intermediates, uint GroupThreadIndex, out uint OutLaneVertIndex)`
- L562-568 _function_ `FVertexFactoryInput VertexFactoryMeshShaderGetInput(FVertexFactoryMeshShaderIntermediates Intermediates, uint VertExportIndex)`

#### C++ shader bindings (IMPLEMENT_* naming this file, 1)

- `EVertexFactoryFlags::UsedWithMaterials
	\| EVertexFactoryFlags::SupportsStaticLighting
	\| EVertexFactoryFlags::SupportsPrimitiveIdStream
	\| EVertexFactoryFlags::SupportsNaniteRendering
	\| EVertexFactoryFlags::SupportsManualVertexFetch
	\| EVertexFactoryFlags::SupportsMeshShading` → entry not found in file (macro-generated or #include'd); C++ `FNaniteTranslucencyFactory`  via IMPLEMENT_VERTEX_FACTORY_TYPE (Source/Runtime/Renderer/Private/Nanite/NaniteTranslucency.cpp:127)

### `Shaders/Private/Nanite/NaniteVertexDeformation.ush` (Private)

- lines: 645; parse: all-branches
- includes: L5 `../Common.ush`, L6 `../ViewData.ush`, L7 `../SplineMeshCommon.ush`, L8 `NaniteSceneCommon.ush`, L9 `NaniteAttributeDecode.ush`, L10 `NaniteSceneCommon.ush`, L11 `NaniteVertexFetch.ush`, L12 `../Matrices.ush`

#### Macros (#define, 1)

- L14 `#define NANITE_VOXEL_FAST_INVERSE 0`
- L3 #pragma `once`

#### Structs / classes (3)

- L28-54 _struct_ **`FNanitePostDeformVertex`** `struct FNanitePostDeformVertex` — Represents vertex data for a Nanite mesh in local space, post-deformation (when applicable) This includes fixed function deformation from splines and skinning, but no material specific deformation like WPO or displacement.
  - L31 _member_ `uint VertIndex;` — Index of the vertex in the cluster
  - L34 _member_ `float3 Position;` — Post-deformed position of the vertex
  - L35 _member_ `float3 PrevPosition;`
  - L38 _member_ `float3 PointLocal;` — Decoded vertex position (BEFORE deformation)
  - L41 _member_ `float3 PreSkinnedNormal;` — Vertex normal (BEFORE deformation)
  - L44 _member_ `FNaniteTangentBasis TangentBasis;` — Post-deformed tangent basis of the vertex
  - L47 _member_ `float CurveRadius;` — Curve radius (used only by curve geometry)
  - L50 _member_ `float4 Color;` — Vertex color
  - L53 _member_ `float2 TexCoords[NANITE_MAX_UVS];` — Texture coordinates
- L56-65 _struct_ **`FReconstructedVoxelData`** `struct FReconstructedVoxelData`
  - L58 _member_ `float3 LocalPosition;`
  - L59 _member_ `float3 PostDeformPosition;`
  - L60 _member_ `float3 PrevPostDeformPosition;`
  - L61 _member_ `uint VertIndex;`
  - L63 _member_ `float4x3 SkinningTransform;`
  - L64 _member_ `bool bActiveSkinning;`
- L592-603 _struct_ **`FNaniteVertTransforms`** `struct FNaniteVertTransforms` — Group of transforms needed to transform a Nanite vertex
  - L594 _member_ `float4x4 LocalToTranslatedWorld;`
  - L595 _member_ `float4x4 PrevLocalToTranslatedWorld;`
  - L596 _member_ `float4x4 TranslatedWorldToClip;`
  - L597 _member_ `float3x3 LocalToWorldNoScale;`
  - L598 _member_ `float3x3 PrevLocalToWorldNoScale;`
  - L599 _member_ `float3x3 WorldToLocalVector;`
  - L600 _member_ `float3x3 PrevWorldToLocalVector;`
  - L601 _member_ `float3x3 TranslatedWorldToFirstPerson;`
  - L602 _member_ `float3x3 PrevTranslatedWorldToFirstPerson;`

#### Functions (15)

- L16-23 _function_ `float3x3 VoxelInverse(float3x3 M)`
- L67-89 _function_ `FNanitePostDeformVertex DeformLocalNaniteVoxelVertex(FReconstructedVoxelData VoxelData, FNaniteLocalVertex Input)`
- L91-171 _function_ `FNanitePostDeformVertex DeformLocalNaniteVertex(FPrimitiveSceneData PrimitiveData, FInstanceSceneData InstanceData, FInstanceViewData InstanceViewData, FCluster Cluster, FNaniteLocalVertex Input)`
- L173-181 _function_ `FNanitePostDeformVertex FetchAndDeformLocalNaniteVertex(FPrimitiveSceneData PrimitiveData, FInstanceSceneData InstanceData, FInstanceViewData InstanceViewData, FCluster Cluster, FVisibleCluster VisibleCluster, uint VertIndex, uint CompileTimeMaxTexCoords)`
- L183-202 _function_ `template<uint N> void FetchAndDeformLocalNaniteVerts( FPrimitiveSceneData PrimitiveData, FInstanceSceneData InstanceData, FInstanceViewData InstanceViewData, FCluster Cluster, FVisibleCluster VisibleCluster, uint3 VertIndexes, uint CompileTimeMaxTexCoords, inout FNanitePostDeformVertex OutVerts[N])`
- L204-210 _function_ `void SampleVoxelPerBrickSkinningTransforms(FInstanceSceneData InstanceData, FSkinningHeader SkinningHeader, FBrick Brick, inout float4x3 OutSkinningTransform, inout float4x3 OutPrevSkinningTransform)`
- L213-218 _function_ `float4x3 SampleVoxelPerBrickSkinningTransform(FInstanceSceneData InstanceData, FSkinningHeader SkinningHeader, FBrick Brick)`
- L220-246 _function_ `void SampleVoxelPerClusterSkinningTransforms(FInstanceSceneData InstanceData, FCluster Cluster, FSkinningHeader SkinningHeader, inout float4x3 OutSkinningTransform, inout float4x3 OutPrevSkinningTransform)`
- L248-253 _function_ `float4x3 SampleVoxelPerClusterSkinningTransform(FInstanceSceneData InstanceData, FCluster Cluster, FSkinningHeader SkinningHeader)`
- L255-278 _function_ `void SkinClusterBounds(FCluster Cluster, FInstanceSceneData InstanceData, FSkinningHeader SkinningHeader, inout float3 BoxCenter, inout float3 BoxExtent)`
- L280-292 _function_ `float4x4 Orthogonalize(float4x4 Input)`
- L294-332 _function_ `float4x4 SkinNaniteHierarchyAssemblyTransform(FPrimitiveSceneData PrimitiveData, FInstanceSceneData InstanceData, uint AssemblyTransformIndex, float4x4 AssemblyTransform, bool bPrevTransform)`
- L334-504 _function_ `ENCODED_VELOCITY_TYPE CalculateNaniteVelocity(FNaniteView NaniteView, FInstanceSceneData InstanceData, FCluster Cluster, FVisibleCluster VisibleCluster, float4 SvPosition, uint TriIndex, uint PrimitiveFlags, bool bWPOEnabled)`
- L507-589 _function_ `FReconstructedVoxelData ReconstructVoxel(FNaniteView NaniteView, FPrimitiveSceneData PrimitiveData, FInstanceSceneData InstanceData, FInstanceViewData InstanceViewData, FVisibleCluster VisibleCluster, FCluster Cluster, float4 SvPosition, uint BrickIndex)` — TODO: Find a better place for this?
- L605-644 _function_ `FNaniteVertTransforms CalculateNaniteVertexTransforms(FInstanceSceneData InstanceData, FInstanceDynamicData InstanceDynamicData, FNaniteView NaniteView)`

### `Shaders/Private/Nanite/NaniteVertexFactory.ush` (Private)

- lines: 1445; parse: all-branches
- includes: L5 `../VertexFactoryCommon.ush`, L6 `../LightmapData.ush`, L7 `../SplineMeshCommon.ush`, L8 `../SGGX.ush`, L10 `../RayTracing/RayTracingCommon.ush` [RAYHITGROUPSHADER], L13 `../MaterialCache/MaterialCacheCommon.ush` [MATERIAL_CACHE], L15 `NaniteDataDecode.ush`, L16 `NaniteAttributeDecode.ush`, L17 `NaniteSceneCommon.ush`, L18 `NaniteVertexDeformation.ush`, L22 `/Platform/Private/NanitePlatformConfig.ush` [defined(OVERRIDE_NANITE_PLATFORM_CONFIG_USH)]

#### Macros (#define, 8)

- L20 `#define NANITE_PLATFORM_MATERIAL_SHADER 1`
- L26 `#define VIRTUAL_TEXTURE_TARGET 0` _[#if !defined(VIRTUAL_TEXTURE_TARGET)]_
- L30 `#define NANITE_USE_HW_BARYCENTRICS 0` _[#if !defined(NANITE_USE_HW_BARYCENTRICS)]_
- L35 `#define NANITE_NUM_TEXCOORDS_TO_DECODE NUM_MATERIAL_TEXCOORDS_VERTEX` _[#if NUM_MATERIAL_TEXCOORDS_VERTEX > NUM_MATERIAL_TEXCOORDS]_
- L37 `#define NANITE_NUM_TEXCOORDS_TO_DECODE NUM_MATERIAL_TEXCOORDS` _[#if !(NUM_MATERIAL_TEXCOORDS_VERTEX > NUM_MATERIAL_TEXCOORDS)]_
- L42 `#define NANITE_NUM_TEXCOORDS_TO_DECODE_HW_VS 2` _[#if NANITE_PIXEL_PROGRAMMABLE && NANITE_NUM_TEXCOORDS_TO_DECODE < 2]_
- L44 `#define NANITE_NUM_TEXCOORDS_TO_DECODE_HW_VS NANITE_NUM_TEXCOORDS_TO_DECODE` _[#if !(NANITE_PIXEL_PROGRAMMABLE && NANITE_NUM_TEXCOORDS_TO_DECODE < 2)]_
- L1277 `#define VF_SUPPORTS_RAYTRACING_PREPARE_MATERIAL_PIXEL_PARAMETERS 1` _[#if RAYHITGROUPSHADER]_
- L3 #pragma `once`

#### Structs / classes (9)

- L50-65 _struct_ **`FVertexFactoryInterpolantsVSToPS`** `struct FVertexFactoryInterpolantsVSToPS` — Nanite material evaluation is deferred to a screenspace pass sampling the visibility buffer, so the 'interpolants' used in the GBuffer pass are almost all generated in the PixelShader, instead of exported from VS. FNaniteFullscreenVSToPS is the struct containing what actually needs to be passed between VS and PS in the Nanite GBuffer pass.
  - L53 _member_ `nointerpolation float4 LightMapCoordinate : TEXCOORD3;` _[#if NEEDS_LIGHTMAP_COORDINATE]_
  - L54 _member_ `nointerpolation float4 LightMapCoordinateDDX: TEXCOORD4;` _[#if NEEDS_LIGHTMAP_COORDINATE]_
  - L55 _member_ `nointerpolation float4 LightMapCoordinateDDY: TEXCOORD5;` _[#if NEEDS_LIGHTMAP_COORDINATE]_
  - L58 _member_ `nointerpolation uint LightmapDataIndex : LIGHTMAP_ID;` _[#if VF_USE_PRIMITIVE_SCENE_DATA && NEEDS_LIGHTMAP_COORDINATE]_
  - L61 _member_ `nointerpolation uint EyeIndex : PACKED_EYE_INDEX;` _[#if INSTANCED_STEREO]_
  - L63 _member_ `nointerpolation uint ViewIndex : PACKED_VIEW_INDEX;`
  - L64 _member_ `nointerpolation uint2 PixelPos : PIXEL_POS;`
- L89-93 _struct_ **`FVertexFactoryInput`** `struct FVertexFactoryInput` _[#if IS_NANITE_RASTER_PASS]_
- L95-98 _struct_ **`FVertexFactoryIntermediates`** `struct FVertexFactoryIntermediates` _[#if IS_NANITE_RASTER_PASS]_
  - L97 _member_ `float3x3 TangentToLocal;` _[#if IS_NANITE_RASTER_PASS]_
  - L1393 _member_ `half3x3 TangentToLocal;` _[#if RAYHITGROUPSHADER]_
- L259-276 _struct_ **`FNaniteTransformedVert`** `struct FNaniteTransformedVert`
  - L261 _member_ `uint VertIndex;`
  - L262 _member_ `float3 PointLocal;`
  - L263 _member_ `float3 PointPostDeform;`
  - L264 _member_ `float3 PrevPointPostDeform;`
  - L265 _member_ `float3 PointWorld;`
  - L266 _member_ `float3 PointWorld_NoOffset;`
  - L267 _member_ `float4 PointClip;`
  - L268 _member_ `float4 NormalClip;`
  - L269 _member_ `float4 Color;`
  - L270 _member_ `FNaniteTangentBasis TangentBasis;`
  - L271 _member_ `float SplineDist;`
  - L272 _member_ `float CurveRadius;`
  - L274 _member_ `float2 CustomizedUVs[NUM_TEX_COORD_INTERPOLATORS];` _[#if NUM_TEX_COORD_INTERPOLATORS]_
- L312-318 _struct_ **`FNaniteFirstPersonOffsets`** `struct FNaniteFirstPersonOffsets`
  - L314 _member_ `float3 WorldOffset;`
  - L315 _member_ `float3 PrevWorldOffset;`
  - L316 _member_ `float3 LocalOffset;`
  - L317 _member_ `float3 PrevLocalOffset;`
- L652-672 _struct_ **`FNanitePixelAttributes`** `struct FNanitePixelAttributes`
  - L654 _member_ `TDual< float3 > PointWorld;`
  - L655 _member_ `TDual< float3 > PointWorld_NoOffset;`
  - L656 _member_ `TDual< float3 > PrevPointPostDeform;`
  - L657 _member_ `TDual< float4 > PointClip;`
  - L659 _member_ `TDual< half3 > TangentZ;`
  - L662 _member_ `TDual< float4 > Color;` — Interpolated vertex color, in linear color space.
  - L665 _member_ `TDual< float2 > TexCoords[NUM_TEX_COORD_INTERPOLATORS];` _[#if NUM_TEX_COORD_INTERPOLATORS]_
  - L669 _member_ `half3x3 TangentToWorld;` — Orthonormal rotation-only transform from tangent space to world space.
  - L671 _member_ `half UnMirrored;`
- L1267-1271 _struct_ **`FVertexFactoryInput`** `struct FVertexFactoryInput` _[#if RAYHITGROUPSHADER]_
- L1367-1370 _struct_ **`FVertexFactoryRayTracingInterpolants`** `struct FVertexFactoryRayTracingInterpolants`
  - L1369 _member_ `FVertexFactoryInterpolantsVSToPS InterpolantsVSToPS;`
- L1391-1394 _struct_ **`FVertexFactoryIntermediates`** `struct FVertexFactoryIntermediates` _[#if RAYHITGROUPSHADER]_
  - L97 _member_ `float3x3 TangentToLocal;` _[#if IS_NANITE_RASTER_PASS]_
  - L1393 _member_ `half3x3 TangentToLocal;` _[#if RAYHITGROUPSHADER]_

#### Functions (51)

- L67-85 _function_ `void GetNaniteMaterialSceneData(FVisibleCluster VisibleCluster, inout FPrimitiveSceneData PrimitiveData, inout FInstanceSceneData InstanceData)`
- L100-104 _function_ `FVertexFactoryIntermediates GetVertexFactoryIntermediates(FVertexFactoryInput Input)` _[#if IS_NANITE_RASTER_PASS]_
- L106-109 _function_ `float3x3 VertexFactoryGetTangentToLocal(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)` _[#if IS_NANITE_RASTER_PASS]_
- L111-116 _function_ `FMaterialVertexParameters GetMaterialVertexParameters(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, float3 WorldPosition, float3x3 TangentToLocal, bool bIsPreviousFrame = false)` _[#if IS_NANITE_RASTER_PASS]_
- L122-132 _function_ `void GetLightMapCoordinates(FVertexFactoryInterpolantsVSToPS Interpolants, out float2 LightmapUV0, out float2 LightmapUV1, out uint LightmapDataIndex)` _[#if NEEDS_LIGHTMAP_COORDINATE]_
- L134-148 _function_ `void GetLightMapCoordinates(FVertexFactoryInterpolantsVSToPS Interpolants, out FloatDeriv2 LightmapUV0, out FloatDeriv2 LightmapUV1, out uint LightmapDataIndex)` _[#if NEEDS_LIGHTMAP_COORDINATE]_
- L150-158 _function_ `void GetShadowMapCoordinate(FVertexFactoryInterpolantsVSToPS Interpolants, out float2 ShadowMapCoordinate, out uint LightmapDataIndex)` _[#if NEEDS_LIGHTMAP_COORDINATE]_
- L160-170 _function_ `void GetShadowMapCoordinate(FVertexFactoryInterpolantsVSToPS Interpolants, out FloatDeriv2 ShadowMapCoordinate, out uint LightmapDataIndex)` _[#if NEEDS_LIGHTMAP_COORDINATE]_
- L172-178 _function_ `void SetLightMapCoordinate(inout FVertexFactoryInterpolantsVSToPS Interpolants, float2 InLightMapCoordinate, float2 InShadowMapCoordinate)` _[#if NEEDS_LIGHTMAP_COORDINATE]_
- L180-185 _function_ `void SetLightMapCoordinate(inout FVertexFactoryInterpolantsVSToPS Interpolants, TDual< float2 > InLightMapCoordinate, TDual< float2 > InShadowMapCoordinate)` _[#if NEEDS_LIGHTMAP_COORDINATE]_
- L187-192 _function_ `void SetLightMapDataIndex(inout FVertexFactoryInterpolantsVSToPS Interpolants, uint LightmapDataIndex)` _[#if NEEDS_LIGHTMAP_COORDINATE]_
- L197-212 _function_ `half3x3 CalcVertexTangentToLocal(FPrimitiveSceneData PrimitiveData, FInstanceSceneData InstanceData, FNanitePostDeformVertex Vert)` — Determines the tangent to local frame of the specified vertex
- L214-232 _function_ `void SetVertexParameterInstanceData(inout FMaterialVertexParameters VertexParameters, FInstanceSceneData InstanceData, FPrimitiveSceneData PrimitiveData, bool bEvaluateWorldPositionOffset)`
- L234-257 _function_ `void SetVertexParameterAttributeData(inout FMaterialVertexParameters VertexParameters, FNanitePostDeformVertex Vert, float4x4 LocalToTranslatedWorld, float3x3 LocalToWorldNoScale, bool bUsePrevPosition)`
- L279-294 _function_ `FNaniteVertTransforms WaveReadLaneAt(FNaniteVertTransforms In, uint SrcIndex)`
- L296-310 _function_ `float4 GetNaniteClipPosition(in FNaniteView NaniteView, in FMaterialVertexParameters MaterialParameters, FPrimitiveSceneData PrimitiveData, FNaniteVertTransforms Transforms, FNanitePostDeformVertex Vertex, float3 PointWorld)`
- L320-337 _function_ `FNaniteFirstPersonOffsets GetNaniteFirstPersonOffsets(FNaniteVertTransforms Transforms, FMaterialVertexParameters VertexParameters, float3 WorldPositionOffset, FMaterialVertexParameters PrevVertexParameters, float3 PrevWorldPositionOffset)`
- L339-457 _function_ `template<uint N> void TransformNaniteVerts(in FNaniteView NaniteView, FPrimitiveSceneData PrimitiveData, FInstanceSceneData InstanceData, FNaniteVertTransforms Transforms, bool bEvaluateWPO, FNanitePostDeformVertex InVerts[N], inout FNaniteTransformedVert OutVerts[N])`
- L459-500 _function_ `template<uint N> void FetchTransformedNaniteVerts( FNaniteView NaniteView, FPrimitiveSceneData PrimitiveData, FInstanceSceneData InstanceData, FInstanceViewData InstanceViewData, FNaniteVertTransforms Transforms, FCluster Cluster, FVisibleCluster VisibleCluster, uint3 VertIndexes, FReconstructedVoxelData VoxelData, bool bEvaluateWPO, inout FNaniteTransformedVert OutVerts[N] )`
- L502-610 _function_ `FNaniteTransformedVert TransformNaniteVertex(FPrimitiveSceneData PrimitiveData, FInstanceSceneData InstanceData, FNaniteVertTransforms Transforms, FNanitePostDeformVertex InVert, bool bEvaluateWPO)`
- L612-624 _function_ `FNaniteTransformedVert FetchTransformedNaniteVertex( FPrimitiveSceneData PrimitiveData, FInstanceSceneData InstanceData, FInstanceViewData InstanceViewData, FNaniteVertTransforms Transforms, FCluster Cluster, FVisibleCluster VisibleCluster, uint VertIndex, bool bEvaluateWPO)`
- L627-650 _function_ `FNaniteTransformedVert WaveReadLaneAt(FNaniteTransformedVert Vert, uint SrcIndex)`
- L674-709 _function_ `FNanitePixelAttributes GetPixelAttributes( FInstanceSceneData InstanceData, FCluster Cluster, FNaniteVertTransforms Transforms, FNaniteTransformedVert Verts[1], FBarycentrics Barycentrics )`
- L712-753 _function_ `FNanitePixelAttributes GetPixelAttributes( FInstanceSceneData InstanceData, FCluster Cluster, FNaniteVertTransforms Transforms, FNaniteTransformedVert Verts[3], FBarycentrics Barycentrics )`
- L757-769 _function_ `FNanitePixelAttributes GetPixelAttributes( FInstanceSceneData InstanceData, FCluster Cluster, FNaniteVertTransforms Transforms, FNaniteTransformedVert Verts[2], FBarycentrics Barycentrics)` — Used by Curves. To avoid duplicated code for Verts<2>, forward the call to the Verts<3> version with dummy data.
- L771-780 _function_ `float GetNaniteVoxelTwoSidedSign(FInstanceSceneData InstanceData, FNaniteView NaniteView, FNaniteTransformedVert Vert)`
- L782-785 _function_ `float GetNaniteCurveTwoSidedSign(FInstanceSceneData InstanceData, FNaniteView NaniteView, FNaniteTransformedVert Vert0, FNaniteTransformedVert Vert1)`
- L787-791 _function_ `float GetNaniteTwoSidedSign(FInstanceSceneData InstanceData, FNaniteView NaniteView, FCluster Cluster, FBarycentrics Barycentrics, FNaniteTransformedVert Verts[1])`
- L793-797 _function_ `float GetNaniteTwoSidedSign(FInstanceSceneData InstanceData, FNaniteView NaniteView, FCluster Cluster, FBarycentrics Barycentrics, FNaniteTransformedVert Verts[2])`
- L799-819 _function_ `float GetNaniteTwoSidedSign(FInstanceSceneData InstanceData, FNaniteView NaniteView, FCluster Cluster, FBarycentrics Barycentrics, FNaniteTransformedVert Verts[3])`
- L821-1015 _function_ `template<uint N> FMaterialPixelParameters FetchNaniteMaterialPixelParameters( FPrimitiveSceneData PrimitiveData, FInstanceSceneData InstanceData, FInstanceDynamicData InstanceDynamicData, FNaniteVertTransforms Transforms, FNaniteView NaniteView, FNaniteTransformedVert Verts[N], FCluster Cluster, FBarycentrics Barycentrics, inout FVertexFactoryInterpolantsVSToPS Interpolants, inout float4 SvPosition)`
- L1017-1029 _function_ `FBarycentrics CalculateBarycentrics( FNaniteView NaniteView, FInstanceSceneData InstanceData, FCluster Cluster, FNaniteTransformedVert Verts[1], float4 SvPosition)`
- L1031-1041 _function_ `FBarycentrics CalculateBarycentrics( FNaniteView NaniteView, FInstanceSceneData InstanceData, FCluster Cluster, FNaniteTransformedVert Verts[2], float4 SvPosition)`
- L1043-1098 _function_ `FBarycentrics CalculateBarycentrics( FNaniteView NaniteView, FInstanceSceneData InstanceData, FCluster Cluster, FNaniteTransformedVert Verts[3], float4 SvPosition)`
- L1101-1184 _function_ `template<uint N> FMaterialPixelParameters FetchNaniteMaterialPixelParameters_Inner( FNaniteView NaniteView, FCluster Cluster, FVisibleCluster VisibleCluster, FBarycentrics Barycentrics, uint TriIndex, bool bCalcBarycentrics, uint3 TriIndices, bool bCalcTriIndices, inout FVertexFactoryInterpolantsVSToPS Interpolants, float4 SvPosition)`
- L1187-1231 _function_ `FMaterialPixelParameters FetchNaniteMaterialPixelParameters(FNaniteView NaniteView, UlongType PackedPixel, bool bHasPageData, FBarycentrics Barycentrics, bool bCalcBarycentrics, uint3 TriIndices, bool bCalcTriIndices, inout FVertexFactoryInterpolantsVSToPS Interpolants, inout float4 SvPosition)` — Shared function (for Nanite raster and shading passes) to fetch a valid FMaterialPixelParameters struct, which is used by material inputs.
- L1240-1251 _function_ `FMaterialPixelParameters GetMaterialPixelParameters(FNaniteView NaniteView, inout FVertexFactoryInterpolantsVSToPS Interpolants, inout float4 SvPosition)` — Converts from vertex factory specific interpolants to a FMaterialPixelParameters, which is used by material inputs. _[#if IS_NANITE_SHADING_PASS]_
- L1253-1261 _function_ `FMaterialPixelParameters GetMaterialPixelParameters(inout FVertexFactoryInterpolantsVSToPS Interpolants, inout float4 SvPosition)` _[#if IS_NANITE_SHADING_PASS]_
- L1279-1363 _function_ `FMaterialPixelParameters GetMaterialPixelParameters(float3 RayOrigin, float3 RayDirection, float HitT, uint HitPrimitiveIndex, uint HitClusterID, FRayTracingIntersectionAttributes HitAttributes, uint HitKind, float4 SvPosition, out float3 WorldGeoNormal)` _[#if RAYHITGROUPSHADER]_
- L1372-1375 _function_ `float2 VertexFactoryGetRayTracingTextureCoordinate( FVertexFactoryRayTracingInterpolants Interpolants )`
- L1377-1380 _function_ `FVertexFactoryInterpolantsVSToPS VertexFactoryAssignInterpolants(FVertexFactoryRayTracingInterpolants Input)`
- L1382-1385 _function_ `FVertexFactoryRayTracingInterpolants VertexFactoryInterpolate(FVertexFactoryRayTracingInterpolants a, float aInterp, FVertexFactoryRayTracingInterpolants b, float bInterp)`
- L1396-1400 _function_ `FVertexFactoryInput LoadVertexFactoryInputForHGS(uint TriangleIndex, int VertexIndex)` _[#if RAYHITGROUPSHADER]_
- L1402-1406 _function_ `FVertexFactoryIntermediates GetVertexFactoryIntermediates(FVertexFactoryInput Input)` _[#if RAYHITGROUPSHADER]_
- L1408-1411 _function_ `half3x3 VertexFactoryGetTangentToLocal(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)` _[#if RAYHITGROUPSHADER]_
- L1413-1416 _function_ `float4 VertexFactoryGetWorldPosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)` _[#if RAYHITGROUPSHADER]_
- L1418-1421 _function_ `float3 VertexFactoryGetWorldNormal(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)` _[#if RAYHITGROUPSHADER]_
- L1423-1426 _function_ `float3 VertexFactoryGetInstanceSpacePosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)` _[#if RAYHITGROUPSHADER]_
- L1428-1431 _function_ `float3 VertexFactoryGetPreviousInstanceSpacePosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)` _[#if RAYHITGROUPSHADER]_
- L1433-1437 _function_ `FMaterialVertexParameters GetMaterialVertexParameters(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, float3 WorldPosition, half3x3 TangentToLocal, bool bIsPreviousFrame = false)` _[#if RAYHITGROUPSHADER]_
- L1439-1443 _function_ `FVertexFactoryRayTracingInterpolants VertexFactoryGetRayTracingInterpolants(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, FMaterialVertexParameters VertexParameters)` _[#if RAYHITGROUPSHADER]_

#### Top-level macro invocations (4)

- L91-93 _macro_call_ `VF_INSTANCED_STEREO_DECLARE_INPUT_BLOCK() VF_MOBILE_MULTI_VIEW_DECLARE_INPUT_BLOCK()` (scope `FVertexFactoryInput`) _[#if IS_NANITE_RASTER_PASS]_
- L278 _macro_call_ `HLSL_STATIC_ASSERT(sizeof(FNaniteVertTransforms) == 408, "Unexpected size of FNaniteVertTransforms. Update WaveReadLaneAt to reflect changes.")`
- L626 _macro_call_ `HLSL_STATIC_ASSERT(sizeof(FNaniteTransformedVert) == (148 + 8 * NUM_TEX_COORD_INTERPOLATORS), "Unexpected size of FNaniteTransformedVert. WaveReadLaneAt implementation needs to be updated.")`
- L1270-1271 _macro_call_ `VF_GPUSCENE_DECLARE_INPUT_BLOCK(13)` (scope `FVertexFactoryInput`) _[#if RAYHITGROUPSHADER]_

#### C++ shader bindings (IMPLEMENT_* naming this file, 1)

- `EVertexFactoryFlags::UsedWithMaterials
	\| EVertexFactoryFlags::SupportsStaticLighting
	\| EVertexFactoryFlags::SupportsPrimitiveIdStream
	\| EVertexFactoryFlags::SupportsNaniteRendering
	\| EVertexFactoryFlags::SupportsComputeShading
	\| EVertexFactoryFlags::SupportsManualVertexFetch
	\| EVertexFactoryFlags::SupportsRayTracing
	\| EVertexFactoryFlags::SupportsLumenMeshCards
	\| EVertexFactoryFlags::SupportsLandscape
	\| EVertexFactoryFlags::SupportsPSOPrecaching` → entry not found in file (macro-generated or #include'd); C++ `FNaniteVertexFactory`  via IMPLEMENT_VERTEX_FACTORY_TYPE (Source/Runtime/Engine/Private/Rendering/NaniteResources.cpp:3732)

### `Shaders/Private/Nanite/NaniteVertexFetch.ush` (Private)

- lines: 148; parse: all-branches
- includes: L5 `../Common.ush`, L6 `../ViewData.ush`, L7 `NaniteSceneCommon.ush`
- L3 #pragma `once`

#### Structs / classes (1)

- L10-22 _struct_ **`FNaniteLocalVertex`** `struct FNaniteLocalVertex` — Represents vertex data for a Nanite mesh in local space
  - L13 _member_ `uint VertIndex;` — Index of the vertex in the cluster
  - L15 _member_ `float3 Position;` — Decoded vertex position (NOTE: On assembly parts, this is transformed into local, and is not "part"-local)
  - L17 _member_ `float3 PrevPosition;` — Prev vertex position (NOTE: This is currently only different than Position with skinned assembly parts)
  - L19 _member_ `FNaniteRawAttributeData RawAttributeData;` — Decoded vertex attribute data
  - L21 _member_ `bool bEnableSkinning;` — Whether or not this vertex should be skinned

#### Functions (5)

- L25-38 _function_ `void TransformNaniteAssemblyVertex(float4x4 AssemblyTransform, float4x4 PrevAssemblyTransform, inout FNaniteLocalVertex Vert)` — Transforms a vertex that is part of an assembly into local space
- L40-94 _function_ `template<uint N> void FetchLocalNaniteVerts( FPrimitiveSceneData PrimitiveData, FInstanceSceneData InstanceData, FInstanceViewData InstanceViewData, FCluster Cluster, FVisibleCluster VisibleCluster, uint3 VertIndexes, uint CompileTimeMaxTexCoords, inout FNaniteLocalVertex OutVerts[N])`
- L96-109 _function_ `FNaniteLocalVertex FetchLocalNaniteVertex( FPrimitiveSceneData PrimitiveData, FInstanceSceneData InstanceData, FInstanceViewData InstanceViewData, FCluster Cluster, FVisibleCluster VisibleCluster, uint VertIndex, uint CompileTimeMaxTexCoords)`
- L112-136 _function_ `template<uint N> void FetchLocalNaniteVertexPositions( FInstanceSceneData InstanceData, FCluster Cluster, FVisibleCluster VisibleCluster, uint3 VertIndexes, inout float3 OutPositions[N])`
- L138-148 _function_ `float3 FetchLocalNaniteVertexPosition( FInstanceSceneData InstanceData, FCluster Cluster, FVisibleCluster VisibleCluster, uint VertIndex)`

### `Shaders/Private/Nanite/NaniteVisualize.usf` (Private)

- lines: 1042; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../ShaderPrint.ush`, L5 `../SceneData.ush`, L6 `../DeferredShadingCommon.ush`, L7 `../ColorMap.ush`, L8 `../Visualization.ush`, L9 `../VirtualShadowMaps/VirtualShadowMapPageCacheCommon.ush`, L10 `../VirtualShadowMaps/VirtualShadowMapVisualize.ush`, L11 `../SplineMeshCommon.ush`, L12 `../MeshPaintTextureCommon.ush`, L15 `../VirtualTextureCommon.ush`, L17 `NaniteDataDecode.ush`, L18 `NaniteAttributeDecode.ush`, L19 `NaniteCullingCommon.ush`, L20 `NaniteVertexFetch.ush`, L21 `NaniteVertexDeformation.ush`, L22 `NaniteEditorCommon.ush`

#### Macros (#define, 1)

- L14 `#define NUM_VIRTUALTEXTURE_SAMPLES 1`

#### Entry points (2)

- L269-819 _entry_ `[numthreads(8, 8, 1)] void VisualizeCS(uint3 DTID : SV_DispatchThreadID, uint3 GID : SV_GroupID)` — stage: **compute** — C++: `FNaniteVisualizeCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteVisualize.cpp:211)
- L821-1042 _entry_ `[numthreads(1, 1, 1)] void PickingCS(uint3 DTID : SV_DispatchThreadID, uint3 GID : SV_GroupID)` — stage: **compute** — C++: `FNanitePickingCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Nanite/NaniteVisualize.cpp:261)

#### Structs / classes (1)

- L153-159 _struct_ **`FVisualizeEffects`** `struct FVisualizeEffects`
  - L155 _member_ `float3 OutlineColor;`
  - L156 _member_ `bool bDarkOutline;`
  - L157 _member_ `bool bApplySobel;`
  - L158 _member_ `bool bApplyDebugShading;`

#### Global resources (textures / buffers / samplers) (14)

- L24 _resource_ `RWTexture2D<float4> DebugOutput;`
- L26 _resource_ `Texture2D<UlongType> VisBuffer64;`
- L27 _resource_ `Texture2D<UlongType> DbgBuffer64;`
- L28 _resource_ `Texture2D<uint> DbgBuffer32;`
- L29 _resource_ `Texture2D<float> SceneDepth;`
- L30 _resource_ `Texture2D<float> SceneZDecoded;`
- L31 _resource_ `Texture2D<uint4> SceneZLayout;`
- L32 _resource_ `Texture2D<uint> ShadingMask;`
- L33 _resource_ `Texture2D<uint> FastClearTileVis;`
- L34 _resource_ `Texture2D<float4> MeshPaintTexture;`
- L36 _resource_ `StructuredBuffer<FNaniteRasterBinMeta> RasterBinMeta;`
- L37 _resource_ `ByteAddressBuffer ShadingBinData;`
- L38 _resource_ `ByteAddressBuffer AssemblyMeta;`
- L51 _resource_ `RWStructuredBuffer<FNanitePickingFeedback> FeedbackBuffer;`

#### Global parameters (uniforms) (6)

- L40 _parameter_ `int4 VisualizeConfig;`
- L41 _parameter_ `int4 VisualizeScales;`
- L42 _parameter_ `uint RegularMaterialRasterBinCount;`
- L43 _parameter_ `int2 PickingPixelPos;`
- L44 _parameter_ `uint MeshPaintTextureCoordinate;`
- L46 _parameter_ `uint NumShadingGroups;`

#### static const (1)

- L49 _static_const_ `static const uint MeshPassIndex = 0;` — NOTE: Just hardcoded to ENaniteMeshPass::BasePass as an optimization, as all these shaders are only concerned with base pass materials

#### Functions (16)

- L53-56 _function_ `uint GetVisualizeMode()`
- L58-65 _function_ `uint GetPickingDomain()`
- L67-74 _function_ `uint GetPixelProgrammableVisMode()`
- L76-83 _function_ `uint GetMeshPaintingShowMode()`
- L85-92 _function_ `uint GetMeshPaintingChannelMode()`
- L94-101 _function_ `uint GetMeshPaintingTextureMode()`
- L103-114 _function_ `float3 ApplyMeshPaintingChannelMode(uint Mode, float4 Color)`
- L118-121 _function_ `float3 LinearToPostTonemapSpace(float3 Color)` — Apply this to color output because we composite the visualization result with post-tone-mapped space. Call this for visualization modes where it matters, but possibly we should do this in all modes.
- L123-126 _function_ `float GetOverdrawScale()`
- L128-131 _function_ `float GetComplexityScale()`
- L133-136 _function_ `uint GetShadingExportCount()`
- L138-141 _function_ `bool GetCompositeWithSceneDepth()`
- L143-146 _function_ `bool ShouldApplySobelFilter()`
- L148-151 _function_ `bool ShouldApplyDebugShading()`
- L161-200 _function_ `FVisualizeEffects GetVisualizeModeEffects(uint VisualizeMode)`
- L202-266 _function_ `float3 ApplySobelFilter(uint2 PixelPosXY, uint DepthInt, float3 Color, FVisualizeEffects Effects)`

### `Shaders/Private/Nanite/NaniteWritePixel.ush` (Private)

- lines: 111; parse: all-branches
- includes: L5 `../Common.ush`, L6 `/Engine/Shared/NaniteDefinitions.h`, L8 `../VirtualShadowMaps/VirtualShadowMapPageAccessCommon.ush` [VIRTUAL_TEXTURE_TARGET]
- L3 #pragma `once`

#### Structs / classes (1)

- L37-96 _struct_ **`FVisBufferPixel`** `struct FVisBufferPixel`
  - L39 _member_ `uint2 Position;`
  - L40 _member_ `uint Value;`
  - L41 _member_ `uint2 VisualizeValues;`
  - L42 _member_ `float Depth;`
  - L45 _member_ `uint3 PhysicalPosition;` _[#if VIRTUAL_TEXTURE_TARGET]_
  - L48 _method_ `bool EarlyDepthTest()`
  - L67 _method_ `void WriteOverdraw()`
  - L79 _method_ `void Write()`

#### Global resources (textures / buffers / samplers) (5)

- L11 _resource_ `RWTexture2D<uint> OutDepthBuffer;`
- L12 _resource_ `RWTexture2DArray<uint> OutDepthBufferArray;`
- L13 _resource_ `RWTexture2D<UlongType> OutVisBuffer64;`
- L16 _resource_ `RWTexture2D<UlongType> OutDbgBuffer64;` _[#if VISUALIZE]_
- L17 _resource_ `RWTexture2D<uint> OutDbgBuffer32;` _[#if VISUALIZE]_

#### Functions (2)

- L20-35 _function_ `void WritePixel( RWTexture2D<UlongType> OutBuffer, uint PixelValue, uint2 PixelPos, uint DepthInt )`
- L98-110 _function_ `FVisBufferPixel CreateVisBufferPixel( uint2 Position, uint Value, float Depth )`
