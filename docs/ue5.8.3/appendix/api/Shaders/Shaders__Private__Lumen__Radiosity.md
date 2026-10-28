# Shaders / Shaders/Private/Lumen/Radiosity

- files: 5; lines: 1399
- record kinds: cpp_binding=11, define=13, entry=10, function=23, groupshared=1, include=38, member=12, parameter=38, resource=39, struct=2, typedef=1

### `Shaders/Private/Lumen/Radiosity/LumenRadiosity.usf` (Private)

- lines: 575; parse: all-branches
- includes: L3 `../../Common.ush`, L4 `../../MonteCarlo.ush`, L5 `../../SHCommon.ush`, L6 `../LumenCardCommon.ush`, L7 `../LumenTracingCommon.ush`, L8 `../LumenSoftwareRayTracing.ush`, L9 `../LumenCardTile.ush`, L10 `../LumenFloatQuantization.ush`, L11 `LumenRadiosity.ush`, L12 `../../RayTracing/RayGenUtils.ush`

#### Macros (#define, 4)

- L15 `#define THREADGROUP_SIZE 1` _[#if !defined(THREADGROUP_SIZE)]_
- L76 `#define RADIOSITY_TRACE_THREADGROUP_SIZE 32` _[#if THREADGROUP_SIZE_32]_
- L78 `#define RADIOSITY_TRACE_THREADGROUP_SIZE 64` _[#if !(THREADGROUP_SIZE_32)]_
- L561 `#define DEBUG_VISUALIZE_PROBE_PLACEMENT 0` _[#if defined(LumenRadiosityIntegrateCS)]_

#### Entry points (5)

- L29-63 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void LumenRadiosityIndirectArgsCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FLumenRadiosityIndirectArgsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenRadiosity.cpp:388)
- L81-170 _entry_ `[numthreads(RADIOSITY_TRACE_THREADGROUP_SIZE, 1, 1)] void LumenRadiosityDistanceFieldTracingCS( uint DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FLumenRadiosityDistanceFieldTracingCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenRadiosity.cpp:431)
- L249-330 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void LumenRadiositySpatialFilterProbeRadiance( uint DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FLumenRadiositySpatialFilterProbeRadiance` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenRadiosity.cpp:542)
- L336-385 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void LumenRadiosityConvertToSH( uint DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FLumenRadiosityConvertToSH` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenRadiosity.cpp:577)
- L474-573 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void LumenRadiosityIntegrateCS( uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FLumenRadiosityIntegrateCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenRadiosity.cpp:620) _[#if defined(LumenRadiosityIntegrateCS)]_

#### Global resources (textures / buffers / samplers) (13)

- L18 _resource_ `RWBuffer<uint> RWDispatchCardTilesIndirectArgs;`
- L19 _resource_ `RWBuffer<uint> RWDispatchRadiosityTilesIndirectArgs;`
- L65 _resource_ `RWTexture2D<float3> RWTraceRadianceAtlas;`
- L66 _resource_ `RWTexture2D<float> RWTraceHitDistanceAtlas;`
- L172 _resource_ `RWTexture2D<float3> RWFilteredTraceRadianceAtlas;`
- L332 _resource_ `RWTexture2D<float4> RWRadiosityProbeSHRedAtlas;`
- L333 _resource_ `RWTexture2D<float4> RWRadiosityProbeSHGreenAtlas;`
- L334 _resource_ `RWTexture2D<float4> RWRadiosityProbeSHBlueAtlas;`
- L387 _resource_ `Texture2D<float4> RadiosityProbeSHRedAtlas;`
- L388 _resource_ `Texture2D<float4> RadiosityProbeSHGreenAtlas;`
- L389 _resource_ `Texture2D<float4> RadiosityProbeSHBlueAtlas;`
- L469 _resource_ `RWTexture2D<float3> RWRadiosityAtlas;` _[#if defined(LumenRadiosityIntegrateCS)]_
- L470 _resource_ `RWTexture2D<UNORM float> RWRadiosityNumFramesAccumulatedAtlas;` _[#if defined(LumenRadiosityIntegrateCS)]_

#### Global parameters (uniforms) (8)

- L20 _parameter_ `uint HardwareRayTracingThreadGroupSize;`
- L68 _parameter_ `float SurfaceBias;`
- L69 _parameter_ `float MinTraceDistance;`
- L70 _parameter_ `float MaxTraceDistance;`
- L71 _parameter_ `float MaxMeshSDFTraceDistance;`
- L72 _parameter_ `float MaxRayIntensity;`
- L73 _parameter_ `float CachedLightingPreExposure;`
- L173 _parameter_ `float ProbePlaneWeightingDepthScale;`

#### groupshared (1)

- L472 _groupshared_ `groupshared float SharedNumFramesAccumulated;` _[#if defined(LumenRadiosityIntegrateCS)]_

#### Functions (5)

- L22-27 _function_ `void SetHardwareRayTracingIndirectArgs(uint ArgIndex, uint NumThreads, uint ThreadGroupSize)`
- L175-182 _function_ `float CalculatePlaneWeight(float3 WorldPosition, float3 WorldNormal, float3 ProbeWorldPosition)`
- L184-247 _function_ `void SampleTraceRadianceAtlas( FRadiosityTexel GatherProbeTexel, uint2 GatherProbeAtlasCoord, uint ResLevelPageTableOffset, uint2 ResLevelSizeInProbes, int2 ProbeCoordInCard, uint2 TraceTexelCoord, float InterpolationWeight, inout float3 Radiance, inout float WeightSum)`
- L391-403 _function_ `FTwoBandSHVectorRGB GetRadiosityProbeSH(uint2 RadiosityProbeAtlasCoord)`
- L405-465 _function_ `void SampleRadiositySH( uint2 TexelCoordInCard, float3 TexelWorldPosition, float3 TexelNormal, uint ResLevelPageTableOffset, uint2 ResLevelSizeInProbes, uint2 ProbeCoordInCard, float InterpolationWeight, inout FTwoBandSHVectorRGB IrradianceSH, inout float WeightSum, inout float3 Debug)`

### `Shaders/Private/Lumen/Radiosity/LumenRadiosity.ush` (Private)

- lines: 357; parse: all-branches
- includes: L9 `../../MonteCarlo.ush`, L10 `../../BlueNoise.ush`

#### Macros (#define, 7)

- L13 `#define RADIOSITY_ATLAS_DOWNSAMPLE_FACTOR 1`
- L238 `#define JITTER_RAY_DIRECTION 1`
- L241 `#define BLUE_NOISE 1` _[#if JITTER_RAY_DIRECTION]_
- L277 `#define PROBE_HEMISPHERE_HEMI_OCTAHEDRON 0`
- L278 `#define PROBE_HEMISPHERE_UNIFORM 1`
- L279 `#define PROBE_HEMISPHERE_COSINE 2`
- L281 `#define RADIOSITY_PROBE_MAPPING PROBE_HEMISPHERE_UNIFORM`
- L7 #pragma `once`

#### Structs / classes (1)

- L130-143 _struct_ **`FRadiosityTexel`** `struct FRadiosityTexel`
  - L132 _member_ `bool bInsideAtlas;`
  - L133 _member_ `bool bHeightfield;`
  - L134 _member_ `bool bValid;`
  - L136 _member_ `float3 WorldPosition;`
  - L137 _member_ `float3 WorldNormal;`
  - L138 _member_ `float3x3 WorldToLocalRotation;`
  - L140 _member_ `uint2 AtlasCoord;`
  - L141 _member_ `uint2 CardCoord;`
  - L142 _member_ `uint IndirectLightingTemporalIndex;`

#### Global resources (textures / buffers / samplers) (6)

- L15 _resource_ `StructuredBuffer<uint> CardTileAllocator;`
- L16 _resource_ `StructuredBuffer<uint> CardTileData;`
- L18 _resource_ `StructuredBuffer<uint> RadiosityTileAllocator;`
- L19 _resource_ `StructuredBuffer<uint> RadiosityTileData;`
- L22 _resource_ `Texture2D<float3> TraceRadianceAtlas;` — Probe trace radiance in hemisphere layout
- L25 _resource_ `Texture2D<float> TraceHitDistanceAtlas;` — Probe trace hit distance

#### Global parameters (uniforms) (13)

- L28 _parameter_ `uint ProbeSpacingInCardTexels;` — Number of texels between Radiosity probes, always a power of two
- L31 _parameter_ `uint ProbeSpacingInCardTexelsDivideShift;` — Shift to apply to divide by ProbeSpacingInCardTexels
- L34 _parameter_ `uint CardTileSizeInProbes;` — CARD_TILE_SIZE / ProbeSpacingInCardTexels
- L37 _parameter_ `uint RadiosityTileSizeInProbes;` — CardTileSizeInProbes <= 2 ? 1 : CardTileSizeInProbes
- L40 _parameter_ `uint HemisphereProbeResolution;` — Resolution of the hemisphere trace layout in one dimension
- L43 _parameter_ `uint NumTracesPerProbe;` — HemisphereProbeResolution * HemisphereProbeResolution
- L45 _parameter_ `float ProbeOcclusionStrength;`
- L48 _parameter_ `int FixedJitterIndex;` — When >= 0, specifies a fixed temporal index for debugging
- L51 _parameter_ `uint2 RadiosityAtlasSize;` — Size of the Radiosity physical texture
- L54 _parameter_ `uint MaxFramesAccumulated;` — Length of the temporal jitter pattern, and controls the weight of the temporal accumulation history
- L57 _parameter_ `uint NumViews;` — Number of views in the renderer
- L60 _parameter_ `uint ViewIndex;` — Index of the current view for the dispatch
- L63 _parameter_ `uint MaxRadiosityTiles;` — Maximum number of radiosity tiles for one view

#### typedef / using (1)

- L65 _typedef_ `typedef FCardTileData FRadiosityTileData;`

#### Functions (15)

- L67-73 _function_ `uint PackRadiosityTileData(FRadiosityTileData TileData)`
- L75-82 _function_ `FRadiosityTileData UnpackRadiosityTileData(uint Packed)`
- L84-87 _function_ `uint GetRadiosityTileCount(uint ViewIndex)`
- L90-94 _function_ `uint2 GetProbeJitter(uint IndirectLightingTemporalIndex)` — Returns the jitter offset in the range [0, ProbeSpacingInRadiosityTexels - 1]
- L96-99 _function_ `FRadiosityTileData GetRadiosityTile(uint TileIndex)`
- L101-114 _function_ `void UnswizzleRadiosityTileIndex( uint RadiosityProbeIndex, inout uint RadiosityTileIndex, inout uint2 CoordInRadiosityTile)`
- L116-128 _function_ `void UnswizzleTexelTraceCoords( uint DispatchThreadId, inout uint RadiosityTileIndex, inout uint2 CoordInRadiosityTile, inout uint2 TraceTexelCoord)`
- L145-208 _function_ `FRadiosityTexel GetRadiosityTexel(FLumenCardPageData CardPage, uint2 CoordInCardPage)`
- L210-226 _function_ `FRadiosityTexel GetRadiosityTexelFromRadiosityTile(uint RadiosityTileIndex, uint2 CoordInRadiosityTile)`
- L229-234 _function_ `uint2 GetRadiosityProbeAtlasCoord(FLumenCardPageData CardPage, FRadiosityTileData RadiosityTile, uint2 CoordInRadiosityTile)` — Coord in persistent radiosity probe atlas
- L236-251 _function_ `float2 GetProbeTexelCenter(uint IndirectLightingTemporalIndex, uint2 ProbeTileCoord)`
- L253-263 _function_ `float2 CosineSampleHemisphereInverseFast(float3 Vector)`
- L265-275 _function_ `float2 UniformSampleHemisphereInverseFast(float3 Vector)`
- L283-315 _function_ `void GetRadiosityRay(FRadiosityTexel RadiosityTexel, uint2 ProbeCoord, uint2 TracingTexelCoord, out float3 WorldRayDirection, out float ConeHalfAngle, out float PDF)`
- L317-357 _function_ `float CalculateProbeVisibility(float3 WorldPositionBeingTested, FRadiosityTexel ProbeTexel, uint2 ProbeAtlasCoord)`

### `Shaders/Private/Lumen/Radiosity/LumenRadiosityCulling.usf` (Private)

- lines: 109; parse: all-branches
- includes: L7 `../../Common.ush`, L8 `../LumenCardCommon.ush`, L9 `../LumenCardTile.ush`, L10 `../SurfaceCache/LumenSurfaceCache.ush`, L11 `LumenRadiosity.ush`

#### Entry points (1)

- L25-108 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void BuildRadiosityTilesCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FBuildRadiosityTilesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenRadiosity.cpp:347) — Build a list of radiosity tiles

#### Global resources (textures / buffers / samplers) (6)

- L13 _resource_ `StructuredBuffer<uint> CardPageIndexAllocator;`
- L14 _resource_ `StructuredBuffer<uint> CardPageIndexData;`
- L16 _resource_ `RWStructuredBuffer<uint> RWCardTileAllocator;`
- L17 _resource_ `RWStructuredBuffer<uint> RWCardTileData;`
- L19 _resource_ `RWStructuredBuffer<uint> RWRadiosityTileAllocator;`
- L20 _resource_ `RWStructuredBuffer<uint> RWRadiosityTileData;`

### `Shaders/Private/Lumen/Radiosity/LumenRadiosityHardwareRayTracing.usf` (Private)

- lines: 155; parse: all-branches
- includes: L8 `../../HairStrands/HairStrandsVoxelPageCommonStruct.ush`, L10 `/Engine/Shared/RayTracingTypes.h`, L11 `../../Common.ush`, L12 `../../MonteCarlo.ush`, L13 `../../MortonCode.ush`, L14 `../../SceneTextureParameters.ush`, L15 `../../RayTracing/RayGenUtils.ush`, L17 `../LumenCardCommon.ush`, L18 `../LumenTracingCommon.ush`, L19 `../LumenHardwareRayTracingCommon.ush`, L20 `../LumenSceneLighting.ush`, L21 `../LumenCardTile.ush`, L22 `LumenRadiosity.ush`

#### Entry points (1)

- L49-154 _entry_ `LUMEN_HARDWARE_RAY_TRACING_ENTRY(LumenRadiosityHardwareRayTracing)` — stage: **raygeneration\|compute(inline)**

#### Global resources (textures / buffers / samplers) (7)

- L24 _resource_ `RWTexture2D<float3> RWTraceRadianceAtlas;`
- L25 _resource_ `RWTexture2D<float> RWTraceHitDistanceAtlas;`
- L27 _resource_ `RaytracingAccelerationStructure TLAS;`
- L28 _resource_ `RaytracingAccelerationStructure FarFieldTLAS;`
- L31 _resource_ `StructuredBuffer<FHitGroupRootConstants> HitGroupData;` _[#if LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L32 _resource_ `StructuredBuffer<FRayTracingSceneMetadataRecord> RayTracingSceneMetadata;` _[#if LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L33 _resource_ `RWStructuredBuffer<uint> RWInstanceHitCountBuffer;` _[#if LUMEN_HARDWARE_INLINE_RAYTRACING]_

#### Global parameters (uniforms) (12)

- L36 _parameter_ `float MaxTraceDistance;`
- L37 _parameter_ `float RayTracingBias;`
- L38 _parameter_ `float RayTracingNormalBias;`
- L39 _parameter_ `float HeightfieldSurfaceBias;`
- L40 _parameter_ `float AvoidSelfIntersectionTraceDistance;`
- L41 _parameter_ `float MaxRayIntensity;`
- L42 _parameter_ `uint NumThreadsToDispatch;`
- L43 _parameter_ `float TanRadiosityRayConeHalfAngle;`
- L44 _parameter_ `uint MaxTraversalIterations;`
- L45 _parameter_ `float MinTraceDistanceToSampleSurfaceCache;`
- L46 _parameter_ `uint MeshSectionVisibilityTest;`
- L47 _parameter_ `float CachedLightingPreExposure;`

### `Shaders/Private/Lumen/Radiosity/LumenVisualizeRadiosityProbes.usf` (Private)

- lines: 203; parse: all-branches
- includes: L3 `../../Common.ush`, L4 `../../MonteCarlo.ush`, L5 `../../ComputeShaderUtils.ush`, L6 `../../SHCommon.ush`, L7 `../LumenCardCommon.ush`, L8 `../LumenTracingCommon.ush`, L9 `../LumenCardTile.ush`, L10 `LumenRadiosity.ush`

#### Macros (#define, 2)

- L13 `#define THREADGROUP_SIZE 1` _[#if !defined(THREADGROUP_SIZE)]_
- L16 `#define INVALID_PACKED_PROBE_ATLAS_COORD 0xFFFFFFFF`

#### Entry points (3)

- L26-95 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void BuildVisualizeProbesCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadIndex : SV_GroupThreadID)` — stage: **compute** — C++: `FBuildVisualizeProbesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenRadiosity.cpp:1179)
- L119-156 _entry_ `void VisualizeRadiosityProbesVS( uint VertexId : SV_VertexID, uint InstanceId : SV_InstanceID, out FVisualizeRadianceCacheVSToPS Output, out float4 OutPosition : SV_POSITION )` — stage: **vertex (from C++ binding)** — C++: `FVisualizeRadiosityProbesVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenRadiosity.cpp:1204)
- L176-203 _entry_ `void VisualizeRadiosityProbesPS( FVisualizeRadianceCacheVSToPS Input, out float4 OutColor : SV_Target0 )` — stage: **pixel (from C++ binding)** — C++: `FVisualizeRadiosityProbesPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenRadiosity.cpp:1226)

#### Structs / classes (1)

- L97-102 _struct_ **`FVisualizeRadianceCacheVSToPS`** `struct FVisualizeRadianceCacheVSToPS`
  - L99 _member_ `nointerpolation float4 CellTranslatedSphere : TEXCOORD0;`
  - L100 _member_ `nointerpolation uint2 ProbeAtlasCoord : TEXCOORD1;`
  - L101 _member_ `float3 PositionTWS : TEXCOORD2;`

#### Global resources (textures / buffers / samplers) (7)

- L23 _resource_ `RWStructuredBuffer<uint> RWVisualizeProbeAllocator;`
- L24 _resource_ `RWStructuredBuffer<float4> RWVisualizeProbeData;`
- L104 _resource_ `StructuredBuffer<uint> VisualizeProbeAllocator;`
- L105 _resource_ `StructuredBuffer<float4> VisualizeProbeData;`
- L158 _resource_ `Texture2D<float4> RadiosityProbeSHRedAtlas;`
- L159 _resource_ `Texture2D<float4> RadiosityProbeSHGreenAtlas;`
- L160 _resource_ `Texture2D<float4> RadiosityProbeSHBlueAtlas;`

#### Global parameters (uniforms) (5)

- L18 _parameter_ `float VisualizeProbeRadius;`
- L19 _parameter_ `uint ProbesPerPhysicalPage;`
- L20 _parameter_ `uint ProbeTileSize;`
- L21 _parameter_ `uint MaxVisualizeProbes;`
- L107 _parameter_ `int bShowInvalidProbes;`

#### Functions (3)

- L109-112 _function_ `bool IsProbeValid(uint PackedProbeAtlasCoord)`
- L114-117 _function_ `bool IsProbeValid(uint2 ProbeAtlasCoord)`
- L162-174 _function_ `FTwoBandSHVectorRGB GetRadiosityProbeSH(uint2 RadiosityProbeAtlasCoord)`
