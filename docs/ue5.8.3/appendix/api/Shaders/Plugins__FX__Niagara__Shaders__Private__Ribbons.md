# Shaders / Plugins/FX/Niagara/Shaders/Private/Ribbons

- files: 10; lines: 1674
- record kinds: cpp_binding=9, define=47, entry=10, function=42, groupshared=3, include=20, member=11, parameter=84, resource=49, static_const=3, struct=2

### `Plugins/FX/Niagara/Shaders/Private/Ribbons/NiagaraRibbonAggregationApply.usf` (Private)

- lines: 55; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `NiagaraRibbonCommon.ush`

#### Entry points (1)

- L20-54 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void RibbonAggregationApply(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FNiagaraRibbonAggregationApplyCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraShader/Private/NiagaraRibbonCompute.cpp:103)

#### Global resources (textures / buffers / samplers) (6)

- L6 _resource_ `Buffer<uint> SortedIndices;`
- L8 _resource_ `StructuredBuffer<FRibbonAccumulationValues> InputAccumulation;`
- L10 _resource_ `RWBuffer<float> OutputTangentsAndDistances;`
- L13 _resource_ `RWBuffer<uint> OutputMultiRibbonIndices;` _[#if HAS_RIBBON_ID]_
- L16 _resource_ `RWBuffer<float> OutputTessellationStats;`
- L18 _resource_ `RWBuffer<uint> OutputSegments;`

### `Plugins/FX/Niagara/Shaders/Private/Ribbons/NiagaraRibbonAggregationStep.usf` (Private)

- lines: 68; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `NiagaraRibbonCommon.ush`

#### Entry points (1)

- L13-67 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void RibbonAggregationStep(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FNiagaraRibbonAggregationStepCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraShader/Private/NiagaraRibbonCompute.cpp:102)

#### Global resources (textures / buffers / samplers) (3)

- L6 _resource_ `Buffer<uint> SortedIndices;`
- L8 _resource_ `StructuredBuffer<FRibbonAccumulationValues> InputAccumulation;`
- L9 _resource_ `RWStructuredBuffer<FRibbonAccumulationValues> OutputAccumulation;`

#### Global parameters (uniforms) (1)

- L11 _parameter_ `uint PrefixScanStride;`

### `Plugins/FX/Niagara/Shaders/Private/Ribbons/NiagaraRibbonCommon.ush` (Private)

- lines: 273; parse: all-branches
- includes: L5 `/Plugin/FX/Niagara/Shared/NiagaraRibbonShared.h`, L112 `/Plugin/FX/Niagara/Private/NiagaraParticleAccess.ush`

#### Macros (#define, 37)

- L7 `#define INDEX_NONE (-1)`
- L8 `#define INT_MIN (-2147483647 - 1)`
- L9 `#define UE_SMALL_NUMBER (1.e-8f)`
- L11 `#define PACKED_PER_RIBBON_DATA_STRIDE 8`
- L12 `#define PACKED_PER_RIBBON_UVDATAOFFSET 0`
- L13 `#define PACKED_PER_RIBBON_STARTPARTICLEOFFSET 6`
- L14 `#define PACKED_PER_RIBBON_ENDPARTICLEOFFSET 7`
- L16 `#define VERTEX_GEN_OUTPUT_DATA_FINALIZATION_INDIRECT_ARGS_OFFSET 0`
- L17 `#define VERTEX_GEN_OUTPUT_DATA_TOTAL_NUM_SEGMENTS_OFFSET 3`
- L18 `#define VERTEX_GEN_OUTPUT_DATA_TOTAL_NUM_RIBBONS_OFFSET 4`
- L21 `#define VERTEX_GEN_OUTPUT_DATA_TESSELLATION_ANGLE 5`
- L22 `#define VERTEX_GEN_OUTPUT_DATA_TESSELLATION_CURVATURE 6`
- L23 `#define VERTEX_GEN_OUTPUT_DATA_TESSELLATION_TWIST_ANGLE 7`
- L24 `#define VERTEX_GEN_OUTPUT_DATA_TESSELLATION_TWIST_CURVATURE 8`
- L25 `#define VERTEX_GEN_OUTPUT_DATA_TESSELLATION_TOTAL_SEGMENT_LENGTH 9`
- L27 `#define VERTEX_GEN_OUTPUT_DATA_TESSELLATION_CURRENT_FRAME_TOTAL_SEGMENT_LENGTH 10`
- L28 `#define VERTEX_GEN_OUTPUT_DATA_TESSELLATION_CURRENT_FRAME_AVERAGE_SEGMENT_LENGTH 11`
- L29 `#define VERTEX_GEN_OUTPUT_DATA_TESSELLATION_CURRENT_FRAME_AVERAGE_SEGMENT_ANGLE 12`
- L30 `#define VERTEX_GEN_OUTPUT_DATA_TESSELLATION_CURRENT_FRAME_AVERAGE_TWIST_ANGLE 13`
- L31 `#define VERTEX_GEN_OUTPUT_DATA_TESSELLATION_CURRENT_FRAME_AVERAGE_WIDTH 14`
- L34 `#define INDEX_GEN_EXECUTE_INDIRECT_OFFSET 0`
- L35 `#define INDEX_GEN_DRAW_INDIRECT_OFFSET 3`
- L36 `#define INDEX_GEN_STEREO_DRAW_INDIRECT_OFFSET 8`
- L38 `#define INDEX_GEN_TESSELLATION_FACTOR_OFFSET 13`
- L39 `#define INDEX_GEN_NUM_SEGMENTS_OFFSET 14`
- L40 `#define INDEX_GEN_NUM_SUB_SEGMENTS_OFFSET 15`
- L41 `#define INDEX_GEN_ONE_OVER_NUM_SUB_SEGMENTS_OFFSET 16`
- L43 `#define INDEX_GEN_INDIRECT_ARGS_STRIDE 17`
- L103 `#define USE_GLOBAL_NIAGARA_DATA_BUFFERS 0`
- L104 `#define ENABLE_NIAGARA_INT_DATA_ACCESS 1`
- L106 `#define NiagaraGetFloatBuffer() (NiagaraParticleDataFloat)`
- L107 `#define NiagaraGetHalfBuffer() (NiagaraParticleDataHalf)`
- L108 `#define NiagaraGetIntBuffer() (NiagaraParticleDataInt)`
- L129 `#define HAS_RIBBON_ID (RIBBONID_IS_NIAGARAID \|\| RIBBONID_IS_INT)`
- L131 `#define FNiagaraID int2`
- L136 `#define FRibbonID int2` _[#if RIBBONID_IS_NIAGARAID]_
- L184 `#define FRibbonID int` _[#if !(RIBBONID_IS_NIAGARAID) && RIBBONID_IS_INT]_
- L3 #pragma `once`

#### Global resources (textures / buffers / samplers) (4)

- L48 _resource_ `Buffer<uint> EmitterParticleCountsBuffer;`
- L52 _resource_ `Buffer<float> NiagaraParticleDataFloat;` — Niagara sim data
- L53 _resource_ `Buffer<float> NiagaraParticleDataHalf;`
- L54 _resource_ `Buffer<int> NiagaraParticleDataInt;`

#### Global parameters (uniforms) (32)

- L47 _parameter_ `uint TotalNumParticlesDirect;` — Total particle Count
- L49 _parameter_ `uint EmitterParticleCountsBufferOffset;`
- L55 _parameter_ `int NiagaraFloatDataStride;`
- L56 _parameter_ `int NiagaraIntDataStride;`
- L59 _parameter_ `int RibbonIdDataOffset;` — Int bindings
- L62 _parameter_ `int PositionDataOffset;` — Float bindings
- L63 _parameter_ `int PrevPositionDataOffset;`
- L64 _parameter_ `int VelocityDataOffset;`
- L65 _parameter_ `int WidthDataOffset;`
- L66 _parameter_ `int PrevWidthDataOffset;`
- L67 _parameter_ `int TwistDataOffset;`
- L68 _parameter_ `int PrevTwistDataOffset;`
- L69 _parameter_ `int ColorDataOffset;`
- L70 _parameter_ `int FacingDataOffset;`
- L71 _parameter_ `int PrevFacingDataOffset;`
- L72 _parameter_ `int NormalizedAgeDataOffset;`
- L73 _parameter_ `int MaterialRandomDataOffset;`
- L74 _parameter_ `uint MaterialParamValidMask;`
- L75 _parameter_ `int MaterialParamDataOffset;`
- L76 _parameter_ `int MaterialParam1DataOffset;`
- L77 _parameter_ `int MaterialParam2DataOffset;`
- L78 _parameter_ `int MaterialParam3DataOffset;`
- L79 _parameter_ `int DistanceFromStartOffset;`
- L80 _parameter_ `int U0OverrideDataOffset;`
- L81 _parameter_ `int V0RangeOverrideDataOffset;`
- L82 _parameter_ `int U1OverrideDataOffset;`
- L83 _parameter_ `int V1RangeOverrideDataOffset;`
- L84 _parameter_ `int U0DistributionMode;`
- L85 _parameter_ `int U1DistributionMode;`
- L87 _parameter_ `int RibbonLinkOrderIsFloat;`
- L88 _parameter_ `int RibbonLinkOrderDataOffset;`
- L90 _parameter_ `int RibbonTessellationMode;`

#### static const (3)

- L132 _static_const_ `static const FNiagaraID InvalidID = { INT_MIN, INT_MIN };`
- L137 _static_const_ `static const FNiagaraID InvalidRibbonID = { INT_MIN, INT_MIN };` _[#if RIBBONID_IS_NIAGARAID]_
- L185 _static_const_ `static const FRibbonID InvalidRibbonID = INT_MIN;` _[#if !(RIBBONID_IS_NIAGARAID) && RIBBONID_IS_INT]_

#### Functions (32)

- L93-100 _function_ `int GetTotalNumParticles()` — Gets the num particles from the indirect buffer if available, or if not from the fallback direct input
- L109 _function_ `uint NiagaraGetFloatDataStride()`
- L110 _function_ `uint NiagaraGetIntDataStride()`
- L115 _function_ `float GetFloat(int RegisterIdx, uint InstanceID)` — Define some shorter name functions for legacy use in existing VFs
- L116 _function_ `float2 GetVec2(int RegisterIdx, uint InstanceID)`
- L117 _function_ `float3 GetVec3(int RegisterIdx, uint InstanceID)`
- L118 _function_ `float4 GetVec4(int RegisterIdx, uint InstanceID)`
- L119 _function_ `float SafeGetFloat(int RegisterIdx, uint InstanceID, float Default)`
- L120 _function_ `float2 SafeGetVec2(int RegisterIdx, uint InstanceID, float2 Default)`
- L121 _function_ `float3 SafeGetVec3(int RegisterIdx, uint InstanceID, float3 Default)`
- L122 _function_ `float4 SafeGetVec4(int RegisterIdx, uint InstanceID, float4 Default)`
- L124 _function_ `int GetInt(int RegisterIdx, uint InstanceID)`
- L125 _function_ `int2 GetInt2(int RegisterIdx, uint InstanceID)`
- L126 _function_ `int SafeGetInt(int RegisterIdx, uint InstanceID, int Default)`
- L127 _function_ `int2 SafeGetInt2(int RegisterIdx, uint InstanceID, int2 Default)`
- L139-142 _function_ `FRibbonID GetRibbonID(int InstanceID)` _[#if RIBBONID_IS_NIAGARAID]_
- L144-147 _function_ `FNiagaraID ConvertRibbonIDToNiagaraID(FRibbonID RibbonID)` _[#if RIBBONID_IS_NIAGARAID]_
- L149-152 _function_ `FNiagaraID GetRibbonIDAsNiagaraID(int InstanceID)` _[#if RIBBONID_IS_NIAGARAID]_
- L154-157 _function_ `bool AreRibbonIDsEqual(FRibbonID Left, FRibbonID Right)` _[#if RIBBONID_IS_NIAGARAID]_
- L159-180 _function_ `int CompareRibbonIDs(FRibbonID Left, FRibbonID Right)` _[#if RIBBONID_IS_NIAGARAID]_
- L187-190 _function_ `FRibbonID GetRibbonID(int InstanceID)` _[#if !(RIBBONID_IS_NIAGARAID) && RIBBONID_IS_INT]_
- L192-195 _function_ `FNiagaraID ConvertRibbonIDToNiagaraID(FRibbonID RibbonID)` _[#if !(RIBBONID_IS_NIAGARAID) && RIBBONID_IS_INT]_
- L197-200 _function_ `FNiagaraID GetRibbonIDAsNiagaraID(int InstanceID)` _[#if !(RIBBONID_IS_NIAGARAID) && RIBBONID_IS_INT]_
- L202-205 _function_ `bool AreRibbonIDsEqual(FRibbonID Left, FRibbonID Right)` _[#if !(RIBBONID_IS_NIAGARAID) && RIBBONID_IS_INT]_
- L207-220 _function_ `int CompareRibbonIDs(FRibbonID Left, FRibbonID Right)` _[#if !(RIBBONID_IS_NIAGARAID) && RIBBONID_IS_INT]_
- L224-234 _function_ `float GetRibbonLinkID(int InstanceID)`
- L236-239 _function_ `bool RibbonHasTwist()`
- L241-244 _function_ `bool RibbonWantsAutomaticTessellation()`
- L246-249 _function_ `bool RibbonWantsConstantTessellation()`
- L251-254 _function_ `uint GetTessellationDataStride()`
- L256-260 _function_ `uint GetVertexGenOutputDataStride()`
- L265-271 _function_ `float AcosFast(float InX)` — max absolute error 9.0x10^-3 Eberly's polynomial degree 1 - respect bounds input [-1, 1] and output [0, PI]

### `Plugins/FX/Niagara/Shaders/Private/Ribbons/NiagaraRibbonGenerateIndices.usf` (Private)

- lines: 125; parse: all-branches
- includes: L4 `/Engine/Private/Common.ush`, L5 `NiagaraRibbonCommon.ush`

#### Entry points (1)

- L47-124 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void GenerateIndices(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FNiagaraRibbonCreateIndexBufferCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraShader/Private/NiagaraRibbonCompute.cpp:100)

#### Global resources (textures / buffers / samplers) (6)

- L8 _resource_ `RWBuffer<uint> GeneratedIndicesBuffer;` — Output generated vertices buffer
- L10 _resource_ `Buffer<uint> SortedIndices;`
- L14 _resource_ `Buffer<uint> MultiRibbonIndices;` _[#if HAS_RIBBON_ID]_
- L17 _resource_ `Buffer<uint> Segments;` — Index of the final segment this particle starts
- L22 _resource_ `Buffer<uint> IndirectDrawInfo;` — Buffer containing the indirect dispatch args we're using as well as the tessellation factor from the previous stage
- L25 _resource_ `Buffer<uint> TriangleToVertexIds;` — Buffer containing the triangle to vertex ids for the current shape

#### Global parameters (uniforms) (11)

- L27 _parameter_ `uint IndexBufferOffset;`
- L28 _parameter_ `uint IndirectDrawInfoIndex;`
- L29 _parameter_ `uint TriangleToVertexIdsCount;`
- L31 _parameter_ `uint TrianglesPerSegment;`
- L32 _parameter_ `uint NumVerticesInSlice;`
- L33 _parameter_ `uint BitsNeededForShape;`
- L34 _parameter_ `uint BitMaskForShape;`
- L35 _parameter_ `uint SegmentBitShift;`
- L36 _parameter_ `uint SegmentBitMask;`
- L37 _parameter_ `uint SubSegmentBitShift;`
- L38 _parameter_ `uint SubSegmentBitMask;`

#### Functions (1)

- L40-45 _function_ `uint PackIndex(uint SortedIndex, uint SubSegmentID, uint SliceVertex)`

### `Plugins/FX/Niagara/Shaders/Private/Ribbons/NiagaraRibbonInitializeIndices.usf` (Private)

- lines: 159; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `NiagaraRibbonCommon.ush`

#### Macros (#define, 3)

- L30 `#define TESSELLATIONMODE_AUTOMATIC 0`
- L31 `#define TESSELLATIONMODE_CUSTOM 1`
- L32 `#define TESSELLATIONMODE_DISABLED 2`

#### Entry points (1)

- L34-158 _entry_ `[numthreads(1, 1, 1)] void InitializeIndices(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FNiagaraRibbonCreateIndexBufferParamsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraShader/Private/NiagaraRibbonCompute.cpp:99)

#### Global resources (textures / buffers / samplers) (2)

- L6 _resource_ `RWBuffer<uint> IndirectDrawOutput;`
- L9 _resource_ `Buffer<uint> VertexGenerationResults;` — Stats of the vertex gen, including tessellation stats

#### Global parameters (uniforms) (16)

- L11 _parameter_ `uint IndirectDrawOutputIndex;`
- L12 _parameter_ `uint VertexGenerationResultsIndex;`
- L14 _parameter_ `uint IndexGenThreadSize;`
- L15 _parameter_ `uint TrianglesPerSegment;`
- L17 _parameter_ `float ViewDistance;`
- L18 _parameter_ `float LODDistanceFactor;`
- L19 _parameter_ `uint TessellationMode;`
- L20 _parameter_ `uint bCustomUseConstantFactor;`
- L21 _parameter_ `uint CustomTessellationFactor;`
- L22 _parameter_ `float CustomTessellationMinAngle;`
- L23 _parameter_ `uint bCustomUseScreenSpace;`
- L24 _parameter_ `uint GNiagaraRibbonMaxTessellation;`
- L25 _parameter_ `float GNiagaraRibbonTessellationAngle;`
- L26 _parameter_ `float GNiagaraRibbonTessellationScreenPercentage;`
- L27 _parameter_ `uint GNiagaraRibbonTessellationEnabled;`
- L28 _parameter_ `float GNiagaraRibbonTessellationMinDisplacementError;`

### `Plugins/FX/Niagara/Shaders/Private/Ribbons/NiagaraRibbonRibbonUVParamCalculation.usf` (Private)

- lines: 288; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `NiagaraRibbonCommon.ush`

#### Macros (#define, 6)

- L84 `#define UV_EDGE_MODE_SMOOTH_TRANSITION 0`
- L85 `#define UV_EDGE_MODE_LOCKED 1`
- L87 `#define UV_DISTRIBUTION_MODE_SCALED_UNIFORMLY 0`
- L88 `#define UV_DISTRIBUTION_MODE_SCALED_USING_RIBBON_SEGMENT_LENGTH 1`
- L89 `#define UV_DISTRIBUTION_MODE_TILED_OVER_RIBBON_LENGTH 2`
- L90 `#define UV_DISTRIBUTION_MODE_TILED_FROM_START_OVER_RIBBON_LENGTH 3`

#### Entry points (1)

- L205-288 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] [numthreads(1,1,1)] void GenerateRibbonUVParams(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FNiagaraRibbonUVParamCalculationCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraShader/Private/NiagaraRibbonCompute.cpp:97) _[#if HAS_RIBBON_ID]_

#### Structs / classes (2)

- L38-48 _struct_ **`FNiagaraRibbonUVSettings`** `struct FNiagaraRibbonUVSettings`
  - L40 _member_ `float2 Offset;`
  - L41 _member_ `float2 Scale;`
  - L42 _member_ `float TilingLength;`
  - L43 _member_ `int DistributionMode;`
  - L44 _member_ `int LeadingEdgeMode;`
  - L45 _member_ `int TrailingEdgeMode;`
  - L46 _member_ `bool bEnablePerParticleUOverride;`
  - L47 _member_ `bool bEnablePerParticleVRangeOverride;`
- L77-82 _struct_ **`FRibbonUVScaleAndOffsets`** `struct FRibbonUVScaleAndOffsets`
  - L79 _member_ `float UScale;`
  - L80 _member_ `float UOffset;`
  - L81 _member_ `float UDistributionScalar;`

#### Global resources (textures / buffers / samplers) (4)

- L6 _resource_ `Buffer<uint> SortedIndices;`
- L8 _resource_ `RWBuffer<float> TangentsAndDistances;` — Tangent of the particle, and the distance along the ribbon if we're computing it
- L12 _resource_ `RWBuffer<uint> PackedPerRibbonData;` — Buffer containing basic stats about each ribbon including the first/last indices, as well as UV offsets/scales/distributions for both channels
- L15 _resource_ `Buffer<uint> CommandBuffer;` — Output of the previous stage, allows us access to things like total num segments, and total num ribbons

#### Global parameters (uniforms) (17)

- L16 _parameter_ `int CommandBufferOffset;`
- L19 _parameter_ `float2 UV0Settings_Offset;` — Settings for UV Channel 0
- L20 _parameter_ `float2 UV0Settings_Scale;`
- L21 _parameter_ `float UV0Settings_TilingLength;`
- L22 _parameter_ `int UV0Settings_DistributionMode;`
- L23 _parameter_ `int UV0Settings_LeadingEdgeMode;`
- L24 _parameter_ `int UV0Settings_TrailingEdgeMode;`
- L25 _parameter_ `int UV0Settings_bEnablePerParticleUOverride;`
- L26 _parameter_ `int UV0Settings_bEnablePerParticleVRangeOverride;`
- L29 _parameter_ `float2 UV1Settings_Offset;` — Settings for UV Channel 1
- L30 _parameter_ `float2 UV1Settings_Scale;`
- L31 _parameter_ `float UV1Settings_TilingLength;`
- L32 _parameter_ `int UV1Settings_DistributionMode;`
- L33 _parameter_ `int UV1Settings_LeadingEdgeMode;`
- L34 _parameter_ `int UV1Settings_TrailingEdgeMode;`
- L35 _parameter_ `int UV1Settings_bEnablePerParticleUOverride;`
- L36 _parameter_ `int UV1Settings_bEnablePerParticleVRangeOverride;`

#### Functions (6)

- L50-62 _function_ `FNiagaraRibbonUVSettings GetUV0Params()`
- L63-75 _function_ `FNiagaraRibbonUVSettings GetUV1Params()`
- L92-98 _function_ `float3 LoadTangent(int Index)`
- L100-105 _function_ `void StoreTangent(int Index, float3 NewTangent)`
- L107-110 _function_ `float GetSegmentDistance(uint ParticleID)`
- L112-201 _function_ `FRibbonUVScaleAndOffsets CalculateUVScaleAndOffsets(const FNiagaraRibbonUVSettings UVSettings, uint FirstIndex, uint LastIndex, float TotalLength)`

### `Plugins/FX/Niagara/Shaders/Private/Ribbons/NiagaraRibbonSortParticles.usf` (Private)

- lines: 177; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `NiagaraRibbonCommon.ush`

#### Macros (#define, 1)

- L14 `#define FRibbonLink float`

#### Entry points (2)

- L23-83 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void InitialSortList(uint3 DispatchThreadId : SV_DispatchThreadID, uint InGroupIndex : SV_GroupIndex, uint3 InGroupID : SV_GroupID)` — stage: **compute** — C++: `FNiagaraRibbonSortPhase1CS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraShader/Private/NiagaraRibbonCompute.cpp:92)
- L121-176 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void MergeSort(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FNiagaraRibbonSortPhase2CS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraShader/Private/NiagaraRibbonCompute.cpp:93) — This is a scatter based mergesort kernel

#### Global resources (textures / buffers / samplers) (3)

- L6 _resource_ `Buffer<uint> SortedIndices;`
- L7 _resource_ `RWBuffer<uint> DestinationSortedIndices;`
- L8 _resource_ `Buffer<uint> EmitterCounts;`

#### Global parameters (uniforms) (3)

- L9 _parameter_ `uint CountOffset;`
- L11 _parameter_ `int MergeSortSourceBlockSize;`
- L12 _parameter_ `int MergeSortDestinationBlockSize;`

#### groupshared (3)

- L17 _groupshared_ `groupshared uint SortParticleIDs[THREADGROUP_SIZE + 1];`
- L18 _groupshared_ `groupshared FRibbonLink SortLinkIDs[THREADGROUP_SIZE + 1];`
- L20 _groupshared_ `groupshared FRibbonID SortRibbonIDs[THREADGROUP_SIZE + 1];` _[#if HAS_RIBBON_ID]_

#### Functions (3)

- L15 _function_ `bool CompareRibbonLink(float Lhs, float Rhs)`
- L86-99 _function_ `int MergeSortCompare(FRibbonLink SearchLinkOrder, FRibbonLink TestLinkOrder)`
- L102-117 _function_ `int MergeSortCompare(FRibbonID Left, FRibbonLink LeftLinkOrder, FRibbonID Right, FRibbonLink RightLinkOrder)` _[#if HAS_RIBBON_ID]_

### `Plugins/FX/Niagara/Shaders/Private/Ribbons/NiagaraRibbonVertexReductionFinalization.usf` (Private)

- lines: 202; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `NiagaraRibbonCommon.ush`

#### Entry points (1)

- L39-201 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] [numthreads(1,1,1)] void OutputRibbonStats(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FNiagaraRibbonVertexReductionFinalizeCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraShader/Private/NiagaraRibbonCompute.cpp:96) _[#if HAS_RIBBON_ID]_

#### Global resources (textures / buffers / samplers) (7)

- L7 _resource_ `Buffer<uint> SortedIndices;`
- L11 _resource_ `Buffer<uint> MultiRibbonIndices;` _[#if HAS_RIBBON_ID]_
- L15 _resource_ `Buffer<uint> Segments;` — Index of the final segment this particle starts
- L18 _resource_ `Buffer<float> TessellationStats;` — Tessellation reduction stats if we're computing them
- L20 _resource_ `StructuredBuffer<FRibbonAccumulationValues> AccumulationBuffer;`
- L24 _resource_ `RWBuffer<uint> PackedPerRibbonData;` — Buffer containing basic stats about each ribbon including the first/last indices, as well as UV offsets/scales/distributions for both channels
- L28 _resource_ `RWBuffer<uint> OutputCommandBuffer;` — Buffer to output the results of vertex gen to This is shared across all running ribbon renderers as it's readback to the CPU in one shot

#### Global parameters (uniforms) (2)

- L31 _parameter_ `int OutputCommandBufferIndex;` — Index of the entry we should write too
- L35 _parameter_ `int FinalizationThreadBlockSize;` — ThreadBlock size of the finalization shader that comes next. We compute the draw indirect args while we're here

### `Plugins/FX/Niagara/Shaders/Private/Ribbons/NiagaraRibbonVertexReductionInitialization.usf` (Private)

- lines: 193; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `NiagaraRibbonCommon.ush`

#### Entry points (1)

- L29-186 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void VertexGenInitialize(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FNiagaraRibbonVertexReductionInitializationCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraShader/Private/NiagaraRibbonCompute.cpp:95) — Super simple shader just to initialize the ribbon reduction list sizes to zero

#### Global resources (textures / buffers / samplers) (5)

- L7 _resource_ `Buffer<uint> SortedIndices;`
- L13 _resource_ `RWBuffer<float> OutputTangentsAndDistances;` — Tangent of the particle, and the distance along the ribbon if we're computing it
- L18 _resource_ `RWBuffer<uint> OutputMultiRibbonIndices;` _[#if HAS_RIBBON_ID]_
- L22 _resource_ `RWBuffer<uint> OutputSegments;` — Index of the final segment this particle starts
- L24 _resource_ `RWStructuredBuffer<FRibbonAccumulationValues> OutputAccumulationBuffer;`

#### Global parameters (uniforms) (1)

- L26 _parameter_ `float CurveTension;`

### `Plugins/FX/Niagara/Shaders/Private/Ribbons/NiagaraRibbonVertexReductionPropagation.usf` (Private)

- lines: 134; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `NiagaraRibbonCommon.ush`

#### Entry points (1)

- L30-133 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void VertexGenPrefixSumPropagation(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute**

#### Global resources (textures / buffers / samplers) (9)

- L6 _resource_ `Buffer<uint> SortedIndices;`
- L9 _resource_ `Buffer<float> InputTangentsAndDistances;` — Tangent of the particle, and the distance along the ribbon if we're computing it
- L10 _resource_ `RWBuffer<float> OutputTangentsAndDistances;`
- L16 _resource_ `Buffer<uint> InputMultiRibbonIndices;` _[#if HAS_RIBBON_ID]_
- L17 _resource_ `RWBuffer<uint> OutputMultiRibbonIndices;` _[#if HAS_RIBBON_ID]_
- L21 _resource_ `Buffer<uint> InputSegments;` — Index of the final segment this particle starts
- L22 _resource_ `RWBuffer<uint> OutputSegments;`
- L25 _resource_ `Buffer<float> InputTessellationStats;` — Tessellation reduction stats if we're computing them
- L26 _resource_ `RWBuffer<float> OutputTessellationStats;`

#### Global parameters (uniforms) (1)

- L28 _parameter_ `int PrefixScanStride;`
