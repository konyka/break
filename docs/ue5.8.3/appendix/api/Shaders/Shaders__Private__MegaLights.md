# Shaders / Shaders/Private/MegaLights

- files: 32; lines: 9889
- record kinds: cpp_binding=39, define=133, entry=36, function=147, groupshared=23, include=201, macro_call=2, member=74, method=7, parameter=232, resource=185, static_const=2, struct=13, typedef=1

### `Shaders/Private/MegaLights/MegaLights.usf` (Private)

- lines: 350; parse: all-branches
- includes: L6 `../Common.ush`, L7 `MegaLights.ush`, L8 `MegaLightsMaterial.ush`, L9 `MegaLightsTileClassification.ush`, L221 `../BlueNoise.ush` [defined(HairTransmittanceCS)], L222 `MegaLightsRayTracing.ush` [defined(HairTransmittanceCS)], L223 `../HairStrands/HairStrandsDeepShadowCommon.ush` [defined(HairTransmittanceCS)], L224 `../HairStrands/HairStrandsCommon.ush` [defined(HairTransmittanceCS)], L225 `../HairStrands/HairStrandsDeepTransmittanceCommon.ush` [defined(HairTransmittanceCS)], L226 `../HairStrands/HairStrandsVisibilityCommon.ush` [defined(HairTransmittanceCS)], L227 `../HairStrands/HairStrandsVoxelPageCommon.ush` [defined(HairTransmittanceCS)], L228 `../HairStrands/HairStrandsVoxelPageTraversal.ush` [defined(HairTransmittanceCS)], L229 `../HairStrands/HairStrandsScreenTracing.ush` [defined(HairTransmittanceCS)]

#### Macros (#define, 6)

- L4 `#define ALLOW_SSS_MATERIAL_CHECKERBOARD_OVERRIDE 0`
- L67 `#define SHARED_TILE_MODE_BORDER (FAST_CLEAR ? 1 : 0)` _[#if defined(MegaLightsTileClassificationBuildListsCS)]_
- L68 `#define SHARED_TILE_MODE_SIZE (THREADGROUP_SIZE + SHARED_TILE_MODE_BORDER * 2)` _[#if defined(MegaLightsTileClassificationBuildListsCS)]_
- L219 `#define VOXEL_TRAVERSAL_DEBUG 0` _[#if defined(HairTransmittanceCS)]_
- L220 `#define VOXEL_TRAVERSAL_TYPE VOXEL_TRAVERSAL_LINEAR_MIPMAP` _[#if defined(HairTransmittanceCS)]_
- L245 `#define USE_BLUE_NOISE 1` _[#if defined(HairTransmittanceCS)]_

#### Entry points (3)

- L77-191 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void MegaLightsTileClassificationBuildListsCS( uint2 GroupId : SV_GroupID, uint2 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FMegaLightsTileClassificationBuildListsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/MegaLights/MegaLights.cpp:1171) — Output tile lists for future processing based on the tile bitmask _[#if defined(MegaLightsTileClassificationBuildListsCS)]_
- L203-212 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void InitTileIndirectArgsCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FInitTileIndirectArgsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/MegaLights/MegaLights.cpp:1203) _[#if defined(InitTileIndirectArgsCS)]_
- L258-347 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void HairTransmittanceCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FMegaLightHairTransmittanceCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/MegaLights/MegaLightsResolve.cpp:680) — Compute hair transmittance _[#if defined(HairTransmittanceCS)]_

#### Global resources (textures / buffers / samplers) (11)

- L13 _resource_ `Texture2D<uint> MegaLightsTileBitmask;` _[#if defined(MegaLightsTileClassificationBuildListsCS)]_
- L15 _resource_ `RWStructuredBuffer<uint> RWTileAllocator;` _[#if defined(MegaLightsTileClassificationBuildListsCS)]_
- L16 _resource_ `RWStructuredBuffer<uint> RWTileData;` _[#if defined(MegaLightsTileClassificationBuildListsCS)]_
- L198 _resource_ `RWBuffer<uint> RWTileIndirectArgs;` _[#if defined(InitTileIndirectArgsCS)]_
- L199 _resource_ `RWBuffer<uint> RWDownsampledTileIndirectArgs;` _[#if defined(InitTileIndirectArgsCS)]_
- L200 _resource_ `StructuredBuffer<uint> TileAllocator;` _[#if defined(InitTileIndirectArgsCS)]_
- L201 _resource_ `StructuredBuffer<uint> DownsampledTileAllocator;` _[#if defined(InitTileIndirectArgsCS)]_
- L240 _resource_ `Texture2D<uint> MegaLightsTileBitmask;` _[#if defined(HairTransmittanceCS)]_
- L241 _resource_ `Texture2D<uint> LightSamples;` _[#if defined(HairTransmittanceCS)]_
- L242 _resource_ `Texture2D<uint> LightSampleRays;` _[#if defined(HairTransmittanceCS)]_
- L243 _resource_ `RWTexture2D<uint> RWTransmittanceMaskTexture;` _[#if defined(HairTransmittanceCS)]_

#### Global parameters (uniforms) (10)

- L18 _parameter_ `uint2 ViewSizeInTiles;` _[#if defined(MegaLightsTileClassificationBuildListsCS)]_
- L19 _parameter_ `uint2 ViewMinInTiles;` _[#if defined(MegaLightsTileClassificationBuildListsCS)]_
- L20 _parameter_ `uint2 DownsampledViewMinInTiles;` _[#if defined(MegaLightsTileClassificationBuildListsCS)]_
- L21 _parameter_ `uint2 DownsampledViewSizeInTiles;` _[#if defined(MegaLightsTileClassificationBuildListsCS)]_
- L22 _parameter_ `uint OutputTileDataStride;` _[#if defined(MegaLightsTileClassificationBuildListsCS)]_
- L23 _parameter_ `uint UseTexturedRectLights;` _[#if defined(MegaLightsTileClassificationBuildListsCS)]_
- L235 _parameter_ `uint bUseScreenTrace;` _[#if defined(HairTransmittanceCS)]_
- L236 _parameter_ `uint2 NumSamplesPerPixel;` _[#if defined(HairTransmittanceCS)]_
- L237 _parameter_ `int2 SampleViewMin;` _[#if defined(HairTransmittanceCS)]_
- L238 _parameter_ `int2 SampleViewSize;` _[#if defined(HairTransmittanceCS)]_

#### groupshared (3)

- L70 _groupshared_ `groupshared uint SharedGroupSum[MAX_USED_TILE_MODE];` _[#if defined(MegaLightsTileClassificationBuildListsCS)]_
- L71 _groupshared_ `groupshared uint SharedGlobalTileOffset[MAX_USED_TILE_MODE];` _[#if defined(MegaLightsTileClassificationBuildListsCS)]_
- L72 _groupshared_ `groupshared uint SharedTileMode[SHARED_TILE_MODE_SIZE][SHARED_TILE_MODE_SIZE];` _[#if defined(MegaLightsTileClassificationBuildListsCS)]_

#### Functions (3)

- L25-41 _function_ `uint BuildTileMode(uint TileBitmask, uint InShading, uint InShadingRect, uint InShadingRectTextured)` _[#if defined(MegaLightsTileClassificationBuildListsCS)]_
- L43-65 _function_ `uint GetTileModeFromBitmask(uint TileBitmask)` _[#if defined(MegaLightsTileClassificationBuildListsCS)]_
- L246-253 _function_ `DEFINE_HAIR_BLUE_NOISE_JITTER_FUNCTION float3 InternalGetHairVoxelJitter(uint2 PixelCoord, uint SampleIndex, uint MaxSampleCount, uint TimeIndex, uint JitterMode)` _[#if defined(HairTransmittanceCS)]_

### `Shaders/Private/MegaLights/MegaLights.ush` (Private)

- lines: 436; parse: all-branches
- includes: L8 `/Engine/Shared/MegaLightsDefinitions.h`, L66 `../LightGridCommon.ush`, L69 `../DeferredLightingCommon.ush`, L70 `../SceneData.ush`, L71 `../Hash.ush`, L74 `../ShaderPrint.ush` [DEBUG_MODE], L86 `../Lumen/LumenPosition.ush`, L87 `../StochasticLighting/StochasticLightingUpsample.ush`, L90 `../VolumetricCloudCommon.ush`

#### Macros (#define, 21)

- L48 `#define MAX_USED_TILE_MODE TILE_MODE_MAX_SUBSTRATE_ADAPTIVE` _[#if SUBSTRATE_ENABLED && SUBSTRATE_GBUFFER_FORMAT == 1]_
- L50 `#define MAX_USED_TILE_MODE TILE_MODE_MAX_SUBSTRATE_BLENDABLE` _[#if !(SUBSTRATE_ENABLED && SUBSTRATE_GBUFFER_FORMAT == 1) && SUBSTRATE_ENABLED && SUBSTRATE_GBUFFER_FORMAT == 0]_
- L52 `#define MAX_USED_TILE_MODE TILE_MODE_MAX_LEGACY` _[#if !(SUBSTRATE_ENABLED && SUBSTRATE_GBUFFER_FORMAT == 1) && !(SUBSTRATE_ENABLED && SUBSTRATE_GBUFFER_FORMAT == 0)]_
- L56 `#define USE_SOURCE_TEXTURE 1` _[#if TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT_TEXTURED \|\| TILE_TYPE == TILE_MODE_COMPLEX_SHADING_RECT_TEXTURED \|\| TILE_TYPE == TILE_MODE_SINGLE_SHADING_RECT_TEXTURED \|\| TILE_TYPE == TILE_MODE_COMPLEX_...]_
- L58 `#define USE_SOURCE_TEXTURE 0` _[#if !(TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT_TEXTURED \|\| TILE_TYPE == TILE_MODE_COMPLEX_SHADING_RECT_TEXTURED \|\| TILE_TYPE == TILE_MODE_SINGLE_SHADING_RECT_TEXTURED \|\| TILE_TYPE == TILE_MODE_COMPLE...]_
- L63 `#define USE_SOURCE_TEXTURE OVERRIDE_USE_SOURCE_TEXTURE` _[#if defined(OVERRIDE_USE_SOURCE_TEXTURE)]_
- L67 `#define SUPPORT_CONTACT_SHADOWS 0`
- L68 `#define NON_DIRECTIONAL_DIRECT_LIGHTING 0`
- L75 `#define FontValue FontWhite` _[#if DEBUG_MODE]_
- L76 `#define FontSelected FontRed` _[#if DEBUG_MODE]_
- L77 `#define FontTitle FontEmerald` _[#if DEBUG_MODE]_
- L78 `#define FontBackground float4(0, 0, 0, 0.25f)` _[#if DEBUG_MODE]_
- L89 `#define USE_CLOUD_TRANSMITTANCE 1`
- L93 `#define half3x2 float3x2` _[#if !PLATFORM_SUPPORTS_REAL_TYPES]_
- L96 `#define DEBUG_VISUALIZE_TRACES_RAYS 1`
- L97 `#define DEBUG_VISUALIZE_TRACES_SAMPLES 2`
- L247 `#define LIGHT_SAMPLE_RAY_MAX_DISTANCE 65504.0f`
- L249 `#define LIGHT_SAMPLE_RAY_TYPE_DEFAULT 0`
- L250 `#define LIGHT_SAMPLE_RAY_TYPE_HAIR 1`
- L251 `#define LIGHT_SAMPLE_RAY_TYPE_TWO_SIDED 2`
- L252 `#define LIGHT_SAMPLE_RAY_TYPE_TRANSMISSION 3`
- L3 #pragma `once`; L6 #pragma `message("UESHADERMETADATA_VERSION 380843C1-9E17-4EDB-91FC-D247E0FD54FE")`; L62 #undef `USE_SOURCE_TEXTURE`

#### Structs / classes (4)

- L81-83 _struct_ **`FDebugContext`** `struct FDebugContext` _[#if !(DEBUG_MODE)]_
- L199-206 _struct_ **`FLightSample`** `struct FLightSample`
  - L201 _member_ `uint LocalLightIndex;`
  - L202 _member_ `float Weight;`
  - L203 _member_ `bool bVisible;`
  - L204 _member_ `bool bGuidedAsVisible;`
  - L205 _member_ `bool bCastVolumetricShadow;`
- L254-276 _struct_ **`FLightSampleRay`** `struct FLightSampleRay`
  - L256 _member_ `float RayDistance;` — Distance traversed by ray
  - L257 _member_ `float2 UV;`
  - L258 _member_ `uint RayType;`
  - L259 _member_ `bool bIsFirstPerson;` — Whether this ray is traced from First Person geometry
  - L260 _member_ `bool bCompleted;` — Whether tracing was completed
  - L262 _method_ `bool IsHair()`
  - L267 _method_ `bool IsTwoSided()`
  - L272 _method_ `bool IsTransmission()`
- L320-323 _struct_ **`FVolumeLightSampleRay`** `struct FVolumeLightSampleRay`
  - L322 _member_ `bool bCompleted;` — Whether tracing was completed

#### Global parameters (uniforms) (7)

- L125 _parameter_ `int2 DebugCursorPosition;`
- L134 _parameter_ `uint2 DownsampleFactor;`
- L350 _parameter_ `uint MegaLightsStateFrameIndex;`
- L386 _parameter_ `uint2 NumSamplesPerPixelDivideShift;`
- L394 _parameter_ `uint3 NumSamplesPerVoxelDivideShift;`
- L422 _parameter_ `int bCloudShadowEnabled;`
- L423 _parameter_ `int SelectedForwardDirectionalLightIndex;`

#### typedef / using (1)

- L79 _typedef_ `typedef FShaderPrintContext FDebugContext;` _[#if DEBUG_MODE]_

#### Functions (29)

- L10-15 _function_ `bool IsSimpleShadingTileType(uint TileType)`
- L17-32 _function_ `bool IsRectLightTileType(uint TileType)`
- L34-45 _function_ `bool IsTexturedLightTileType(uint TileType)`
- L100-122 _function_ `void PrintTileTypeString(inout FDebugContext Context, uint TileType, FFontColor InColor = FontWhite)` _[#if DEBUG_MODE]_
- L127-132 _function_ `int2 GetDebugScreenCoord()`
- L137-140 _function_ `uint2 GetDownsampleFactor()` — Utility to avoid int mult/div operations
- L142-161 _function_ `FDebugContext InitDebugContext(uint2 ScreenCoord, bool bDownsampled, float2 StartPos, bool bDebugModeEnabled)`
- L163-166 _function_ `FDebugContext InitDebugContext(uint2 ScreenCoord, bool bDownsampled, float2 StartPos)`
- L168-182 _function_ `FDebugContext InitDebugContext(bool bActive, float2 StartPos)`
- L184-187 _function_ `uint PackTile(uint2 TileCoord)`
- L189-192 _function_ `uint2 UnpackTile(uint PackedTile)`
- L194-197 _function_ `void BitFieldSetU32(inout uint Packed, uint V, uint Size, uint Offset)`
- L208-217 _function_ `FLightSample InitLightSample()`
- L219-231 _function_ `uint PackLightSample(FLightSample LightSample)`
- L233-245 _function_ `FLightSample UnpackLightSample(uint PackedLightSample)`
- L278-287 _function_ `FLightSampleRay InitLightSampleRay()`
- L289-303 _function_ `uint PackLightSampleRay(FLightSampleRay LightSampleRay)`
- L305-318 _function_ `FLightSampleRay UnpackLightSampleRay(uint Packed)`
- L325-330 _function_ `FVolumeLightSampleRay InitVolumeLightSampleRay()`
- L332-339 _function_ `uint PackVolumeLightSampleRay(FVolumeLightSampleRay VolumeLightSampleRay)`
- L341-348 _function_ `FVolumeLightSampleRay UnpackVolumeLightSampleRay(uint Packed)`
- L355-372 _function_ `uint2 GetSampleScreenCoordJitter(uint2 DownsampledScreenCoord)` — Returns sample jitter offset in the range [0, DOWNSAMPLE_FACTOR_XY - 1]
- L374-377 _function_ `uint2 DownsampledScreenCoordToScreenCoord(uint2 DownsampledScreenCoord)`
- L379-384 _function_ `float2 DownsampledScreenCoordToScreenUV(uint2 DownsampledScreenCoord)`
- L388-392 _function_ `uint2 SampleCoordToDownsampledScreenCoord(uint2 SampleCoord)`
- L396-400 _function_ `uint3 SampleCoordToDownsampledVolumeCoord(uint3 SampleCoord)`
- L402-406 _function_ `uint2 SampleCoordToScreenCoord(uint2 SampleCoord)`
- L409-420 _function_ `float SmoothFalloffMask(float X, float Treshold)` — Smooth blend out of X values below Treshold to 0
- L425-435 _function_ `float GetVolumetricCloudShadowFactor(float3 TranslatedWorldPosition, int ForwardLightIndex, FDeferredLightData LightData)`

### `Shaders/Private/MegaLights/MegaLightsDebug.usf` (Private)

- lines: 137; parse: all-branches
- includes: L5 `../Common.ush`, L6 `/Engine/Shared/MegaLightsDefinitions.h`, L7 `MegaLights.ush`

#### Macros (#define, 1)

- L3 `#define DEBUG_MODE 1`

#### Entry points (1)

- L87-137 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void MegaLightsDebugCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FMegaLightsDebugCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/MegaLights/MegaLightsVisualizeLightComplexity.cpp:213) — Run one thread per tile and output debug tile classification visualization

#### Global resources (textures / buffers / samplers) (4)

- L9 _resource_ `StructuredBuffer<uint> DownsampledTileAllocator;`
- L10 _resource_ `StructuredBuffer<uint> DownsampledTileData;`
- L13 _resource_ `StructuredBuffer<uint> TileAllocator;`
- L14 _resource_ `StructuredBuffer<uint> TileData;`

#### Global parameters (uniforms) (3)

- L11 _parameter_ `uint DownsampledTileDataStride;`
- L15 _parameter_ `uint TileDataStride;`
- L17 _parameter_ `uint DebugTileClassificationMode;`

#### Functions (3)

- L19-22 _function_ `uint GetNumTiles(uint TileType)`
- L24-34 _function_ `uint2 GetUnpackedTileData(uint TileType, uint TileIndex)`
- L36-82 _function_ `float4 GetTileTypeColor(uint TileType)`

### `Shaders/Private/MegaLights/MegaLightsDenoiser.ush` (Private)

- lines: 27; parse: all-branches
- includes: L4 `../Common.ush`
- L2 #pragma `once`

#### Functions (4)

- L7-10 _function_ `half LinearStep(half Edge0, half Edge1, half X)` — smoothstep(), but using lerp
- L12-16 _function_ `half ShadingConfidenceToMaxFramesAccumulated(half ShadingConfidence, half TemporalMaxFramesAccumulated)`
- L19-22 _function_ `uint PackNumFramesAccumulated(half X)` — Packing into an R8_UInt
- L24-27 _function_ `half UnpackNumFramesAccumulated(uint X)`

### `Shaders/Private/MegaLights/MegaLightsDenoiserSpatial.usf` (Private)

- lines: 618; parse: all-branches
- includes: L13 `../Common.ush`, L14 `MegaLights.ush`, L15 `MegaLightsMaterial.ush`, L16 `MegaLightsTileClassification.ush`, L17 `MegaLightsDenoiser.ush`, L18 `../StochasticLighting/StochasticLightingCommon.ush`, L19 `../PostProcessSubsurfaceDiffuse.ush`

#### Macros (#define, 7)

- L5 `#define SUBSTRATE_FASTPATH 0`
- L6 `#define SUBSTRATE_SINGLEPATH 0`
- L7 `#define SUBSTRATE_COMPLEXSPECIALPATH 1`
- L11 `#define ALLOW_SSS_MATERIAL_CHECKERBOARD_OVERRIDE 1`
- L82 `#define SHARED_TILE_BORDER 2`
- L83 `#define SHARED_TILE_SIZE_X (THREADGROUP_SIZE + 2 * SHARED_TILE_BORDER)`
- L84 `#define SHARED_TILE_SIZE_Y (THREADGROUP_SIZE + 2 * SHARED_TILE_BORDER)`

#### Entry points (1)

- L158-618 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void DenoiserSpatialCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FDenoiserSpatialCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/MegaLights/MegaLightsDenoising.cpp:434) — Run a spatial filter in order to filter out noise based on the temporal variance.

#### Global resources (textures / buffers / samplers) (11)

- L21 _resource_ `Texture2D<uint> MegaLightsTileBitmask;`
- L22 _resource_ `Texture2D<float3> DiffuseLightingTexture;`
- L23 _resource_ `Texture2D<float3> SpecularLightingTexture;`
- L24 _resource_ `Texture2D<float4> LightingMomentsTexture;`
- L25 _resource_ `Texture2D<float4> NormalAndShadingInfoTexture;`
- L26 _resource_ `Texture2D<uint> NumFramesAccumulatedTexture;`
- L27 _resource_ `Texture2D<float2> HistoryConfidenceTexture;`
- L28 _resource_ `Texture2D<UNORM float> ShadingConfidenceTexture;`
- L30 _resource_ `RWTexture2D<float4> RWSceneColor;`
- L33 _resource_ `RWTexture2D<UNORM float4> RWVisualizeSpatialFilterTexture;` _[#if DEBUG_MODE]_
- L34 _resource_ `RWTexture2D<UNORM float4> RWVisualizeSpatialFilterTexture2;` _[#if DEBUG_MODE]_

#### Global parameters (uniforms) (10)

- L37 _parameter_ `float SpatialFilterMaxDisocclusionFrames;`
- L38 _parameter_ `float SpatialFilterDisocclusionDiffuseSpatialVarianceScale;`
- L39 _parameter_ `float SpatialFilterDisocclusionSpecularSpatialVarianceScale;`
- L40 _parameter_ `float TemporalMaxFramesAccumulated;`
- L41 _parameter_ `float SpatialFilterDepthWeightScale;`
- L42 _parameter_ `float SpatialFilterKernelRadius;`
- L43 _parameter_ `float HistorySpatialStdDevThreshold;`
- L44 _parameter_ `uint SpatialFilterNumSamples;`
- L45 _parameter_ `uint bSubPixelShading;`
- L48 _parameter_ `uint DebugModeEnabled;` — DEBUG_MODE permutation is shared between debug mode and visualization

#### groupshared (3)

- L50 _groupshared_ `groupshared uint SharedGroupDword;`
- L85 _groupshared_ `groupshared float2 SharedHistoryConfidence[SHARED_TILE_SIZE_Y][SHARED_TILE_SIZE_X];`
- L152 _groupshared_ `groupshared uint2 SharedPackedLightingMoments[SHARED_TILE_SIZE_Y][SHARED_TILE_SIZE_X];` _[#if (INPUT_TYPE == INPUT_TYPE_GBUFFER \|\| INPUT_TYPE == INPUT_TYPE_FRONTLAYERTRANSLUCENCY) && SPATIAL_FILTER]_

#### Functions (6)

- L52-80 _function_ `void GroupActiveAnyAllTrue(inout bool bAnyTrue, inout bool bAllTrue)`
- L87-121 _function_ `float2 GetHistoryConfidenceSpatialStdDev(uint2 LocalCoord, inout FDebugContext DebugContext)`
- L123-127 _function_ `float3 TonemapLighting(float3 Lighting, float DisocclusionFactor)`
- L129-133 _function_ `float3 InverseTonemapLighting(float3 TonemappedLighting, float DisocclusionFactor)`
- L135-141 _function_ `uint2 PackLightingMoments(float4 Moments)`
- L143-149 _function_ `float4 UnpackLightingMoments(uint2 Packed)`

### `Shaders/Private/MegaLights/MegaLightsDenoiserTemporal.usf` (Private)

- lines: 619; parse: all-branches
- includes: L12 `../Common.ush`, L13 `../Quantization.ush`, L14 `MegaLights.ush`, L15 `MegaLightsMaterial.ush`, L16 `MegaLightsTileClassification.ush`, L17 `../StochasticLighting/StochasticLightingCommon.ush`, L18 `../TextureSampling.ush`, L19 `MegaLightsDenoiser.ush`, L23 `/Engine/Public/DualPixelVectorization.ush` [defined(DenoiserTemporalCS)]

#### Macros (#define, 11)

- L4 `#define ALLOW_SSS_MATERIAL_CHECKERBOARD_OVERRIDE 0`
- L8 `#define SUBSTRATE_FASTPATH 0`
- L9 `#define SUBSTRATE_SINGLEPATH 0`
- L10 `#define SUBSTRATE_COMPLEXSPECIALPATH 1`
- L26 `#define PACKED_LIGHTING_TYPE half4x2` _[#if defined(DenoiserTemporalCS) && PLATFORM_SUPPORTS_REAL_TYPES]_
- L28 `#define PACKED_LIGHTING_TYPE uint4` _[#if defined(DenoiserTemporalCS) && !(PLATFORM_SUPPORTS_REAL_TYPES)]_
- L30 `#define LIGHTING_TYPE half3x2` _[#if defined(DenoiserTemporalCS)]_
- L31 `#define LIGHTING_EXTRA_EXPOSURE half(16.0)` _[#if defined(DenoiserTemporalCS)]_
- L76 `#define SHARED_TILE_BORDER 2` _[#if defined(DenoiserTemporalCS)]_
- L77 `#define SHARED_TILE_SIZE_X (THREADGROUP_SIZE + 2 * SHARED_TILE_BORDER)` _[#if defined(DenoiserTemporalCS)]_
- L78 `#define SHARED_TILE_SIZE_Y (THREADGROUP_SIZE + 2 * SHARED_TILE_BORDER)` _[#if defined(DenoiserTemporalCS)]_

#### Entry points (2)

- L179-575 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void DenoiserTemporalCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FDenoiserTemporalCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/MegaLights/MegaLightsDenoising.cpp:343) — Temporal accumulation of shaded light samples _[#if defined(DenoiserTemporalCS)]_
- L594-617 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void ClearTemporalAccumulationCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FClearTemporalAccumulationCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/MegaLights/MegaLightsDenoising.cpp:261) — Clear some data for empty tiles, which won't be processed by DenoiserTemporalCS _[#if defined(ClearTemporalAccumulationCS)]_

#### Structs / classes (1)

- L69-74 _struct_ **`FNeighborhood`** `struct FNeighborhood` _[#if defined(DenoiserTemporalCS)]_
  - L71 _member_ `LIGHTING_TYPE Min;` _[#if defined(DenoiserTemporalCS)]_
  - L72 _member_ `LIGHTING_TYPE Max;` _[#if defined(DenoiserTemporalCS)]_
  - L73 _member_ `LIGHTING_TYPE Extent;` _[#if defined(DenoiserTemporalCS)]_

#### Global resources (textures / buffers / samplers) (24)

- L33 _resource_ `Texture2D<uint> MegaLightsTileBitmask;` _[#if defined(DenoiserTemporalCS)]_
- L34 _resource_ `Texture2D<half3> ResolvedDiffuseLighting;` _[#if defined(DenoiserTemporalCS)]_
- L35 _resource_ `Texture2D<half3> ResolvedSpecularLighting;` _[#if defined(DenoiserTemporalCS)]_
- L36 _resource_ `Texture2D<half> ShadingConfidenceTexture;` _[#if defined(DenoiserTemporalCS)]_
- L37 _resource_ `Texture2D MegaLightsDepthHistory;` _[#if defined(DenoiserTemporalCS)]_
- L38 _resource_ `Texture2D<float4> MegaLightsNormalAndShading;` _[#if defined(DenoiserTemporalCS)]_
- L39 _resource_ `Texture2D<half3> DiffuseLightingHistoryTexture;` _[#if defined(DenoiserTemporalCS)]_
- L40 _resource_ `Texture2D<half3> SpecularLightingHistoryTexture;` _[#if defined(DenoiserTemporalCS)]_
- L41 _resource_ `Texture2D<half4> LightingMomentsHistoryTexture;` _[#if defined(DenoiserTemporalCS)]_
- L42 _resource_ `Texture2D<uint> NumFramesAccumulatedHistoryTexture;` _[#if defined(DenoiserTemporalCS)]_
- L43 _resource_ `Texture2D<uint2> EncodedHistoryScreenCoordTexture;` _[#if defined(DenoiserTemporalCS)]_
- L44 _resource_ `Texture2D<uint> PackedPixelDataTexture;` _[#if defined(DenoiserTemporalCS)]_
- L60 _resource_ `RWTexture2D<float3> RWDiffuseLighting;` _[#if defined(DenoiserTemporalCS)]_
- L61 _resource_ `RWTexture2D<float3> RWSpecularLighting;` _[#if defined(DenoiserTemporalCS)]_
- L62 _resource_ `RWTexture2D<float4> RWLightingMoments;` _[#if defined(DenoiserTemporalCS)]_
- L63 _resource_ `RWTexture2D<UNORM float2> RWHistoryConfidence;` _[#if defined(DenoiserTemporalCS)]_
- L64 _resource_ `RWTexture2D<uint> RWNumFramesAccumulated;` _[#if defined(DenoiserTemporalCS)]_
- L66 _resource_ `RWTexture2D<UNORM float4> RWVisualizeTemporalFilterTexture;` _[#if defined(DenoiserTemporalCS) && DEBUG_MODE]_
- L582 _resource_ `StructuredBuffer<uint> TileAllocator;` _[#if defined(ClearTemporalAccumulationCS)]_
- L583 _resource_ `StructuredBuffer<uint> TileData;` _[#if defined(ClearTemporalAccumulationCS)]_
- L586 _resource_ `RWTexture2D<float3> RWDiffuseLighting;` _[#if defined(ClearTemporalAccumulationCS)]_
- L587 _resource_ `RWTexture2D<float3> RWSpecularLighting;` _[#if defined(ClearTemporalAccumulationCS)]_
- L588 _resource_ `RWTexture2D<UNORM float2> RWHistoryConfidence;` _[#if defined(ClearTemporalAccumulationCS)]_
- L589 _resource_ `RWTexture2D<uint> RWNumFramesAccumulated;` _[#if defined(ClearTemporalAccumulationCS)]_

#### Global parameters (uniforms) (10)

- L47 _parameter_ `float3 TargetFormatQuantizationError;` — 2^(-NumMantissaBits) _[#if defined(DenoiserTemporalCS)]_
- L49 _parameter_ `float4 HistoryBufferSizeAndInvSize;` _[#if defined(DenoiserTemporalCS)]_
- L50 _parameter_ `float4 HistorySubPixelGridSizeAndInvSize;` _[#if defined(DenoiserTemporalCS)]_
- L51 _parameter_ `float PrevSceneColorPreExposureCorrection;` _[#if defined(DenoiserTemporalCS)]_
- L52 _parameter_ `float MinFramesAccumulatedForHistoryMiss;` _[#if defined(DenoiserTemporalCS)]_
- L53 _parameter_ `float TemporalMaxFramesAccumulated;` _[#if defined(DenoiserTemporalCS)]_
- L54 _parameter_ `float TemporalNeighborhoodClampScale;` _[#if defined(DenoiserTemporalCS)]_
- L55 _parameter_ `uint2 HistoryScreenCoordDecodeShift;` _[#if defined(DenoiserTemporalCS)]_
- L58 _parameter_ `uint DebugModeEnabled;` — DEBUG_MODE permutation is shared between debug mode and visualization _[#if defined(DenoiserTemporalCS)]_
- L584 _parameter_ `uint TileDataStride;` _[#if defined(ClearTemporalAccumulationCS)]_

#### groupshared (1)

- L79 _groupshared_ `groupshared PACKED_LIGHTING_TYPE SharedResolvedLightingYCoCg[SHARED_TILE_SIZE_Y][SHARED_TILE_SIZE_X];` _[#if defined(DenoiserTemporalCS)]_

#### Functions (4)

- L81-94 _function_ `PACKED_LIGHTING_TYPE PackDiffuseAndSpecularWithWeight(LIGHTING_TYPE Lighting, half2 Weight)` _[#if defined(DenoiserTemporalCS)]_
- L96-108 _function_ `LIGHTING_TYPE UnpackDiffuseAndSpecular(PACKED_LIGHTING_TYPE Packed)` _[#if defined(DenoiserTemporalCS)]_
- L110-120 _function_ `half2 UnpackDiffuseAndSpecularWeight(PACKED_LIGHTING_TYPE Packed)` _[#if defined(DenoiserTemporalCS)]_
- L123-174 _function_ `void GetNeighborhood( uint2 LocalCoord, LIGHTING_TYPE CenterSample, inout FNeighborhood Neighborhood, half NeighborhoodClampScale, inout FDebugContext DebugContext)` — Compute local neighborhood statistics _[#if defined(DenoiserTemporalCS)]_

### `Shaders/Private/MegaLights/MegaLightsEstimateLight.ush` (Private)

- lines: 58; parse: all-branches
- L3 #pragma `once`

#### Functions (3)

- L9-31 _function_ `float EstimateLocalLight( float DistanceSquared, float LightPower, float LightInvRadius, float LightFalloffExponent)` — Estimate local light weight based on the light mask (radius) and falloff Follows GetLocalLightAttenuation() in DeferredLightingCommon.ush
- L33-44 _function_ `float ComputeLightPower(FDeferredLightData LightData)`
- L46-58 _function_ `float EstimateLocalLight(FDeferredLightData LightData, float3 TranslatedWorldPosition)`

### `Shaders/Private/MegaLights/MegaLightsFilterVisibleLightHash.usf` (Private)

- lines: 166; parse: all-branches
- includes: L9 `../Common.ush`, L10 `MegaLights.ush`, L11 `MegaLightsVisibility.ush`

#### Macros (#define, 3)

- L4 `#define NUM_SAMPLES_PER_PIXEL_1D 1` _[#if !defined(NUM_SAMPLES_PER_PIXEL_1D)]_
- L5 `#define NUM_SAMPLES_PER_PIXEL_2D_X 1` _[#if !defined(NUM_SAMPLES_PER_PIXEL_1D)]_
- L6 `#define NUM_SAMPLES_PER_PIXEL_2D_Y 1` _[#if !defined(NUM_SAMPLES_PER_PIXEL_1D)]_

#### Entry points (2)

- L51-91 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void FilterVisibleLightHashCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FFilterVisibleLightHashCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/MegaLights/MegaLightsResolve.cpp:634) — Propagate visible light data by merging neighboring tiles. _[#if defined(FilterVisibleLightHashCS)]_
- L122-164 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, THREADGROUP_SIZE)] void VolumeFilterVisibleLightHashCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FVolumeFilterVisibleLightHashCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/MegaLights/MegaLightsResolve.cpp:550) — Propagate visible light data by merging neighboring voxels. _[#if defined(VolumeFilterVisibleLightHashCS)]_

#### Global resources (textures / buffers / samplers) (4)

- L13 _resource_ `RWStructuredBuffer<uint> RWVisibleLightHash;`
- L14 _resource_ `RWStructuredBuffer<uint> RWHiddenLightHash;`
- L16 _resource_ `StructuredBuffer<uint> VisibleLightHashBuffer;`
- L17 _resource_ `StructuredBuffer<uint> HiddenLightHashBuffer;`

#### Global parameters (uniforms) (3)

- L21 _parameter_ `uint2 VisibleLightHashViewMinInTiles;` _[#if defined(FilterVisibleLightHashCS)]_
- L22 _parameter_ `uint2 VisibleLightHashViewSizeInTiles;` _[#if defined(FilterVisibleLightHashCS)]_
- L97 _parameter_ `uint3 VolumeVisibleLightHashViewSizeInTiles;` _[#if defined(VolumeFilterVisibleLightHashCS)]_

#### Functions (2)

- L24-46 _function_ `void AppendVisibleLightHash( uint2 BaseTileCoord, int2 TileOffset, inout uint VisibleLightHash[VISIBLE_LIGHT_HASH_SIZE], inout uint HiddenLightHash[HIDDEN_LIGHT_HASH_SIZE])` _[#if defined(FilterVisibleLightHashCS)]_
- L99-117 _function_ `void AppendVisibleLightHash(uint3 BaseVoxelCoord, int3 VoxelOffset, inout uint VisibleLightHash[VISIBLE_LIGHT_HASH_SIZE], inout uint HiddenLightHash[HIDDEN_LIGHT_HASH_SIZE])` _[#if defined(VolumeFilterVisibleLightHashCS)]_

### `Shaders/Private/MegaLights/MegaLightsHardwareRayTracing.usf` (Private)

- lines: 381; parse: all-branches
- includes: L3 `/Engine/Shared/RayTracingTypes.h`, L4 `../Common.ush`, L5 `../BlueNoise.ush`, L6 `../IntersectionUtils.ush`, L7 `../RayTracing/RayTracingCommon.ush`, L8 `../SceneTexturesCommon.ush`, L9 `MegaLights.ush`, L10 `MegaLightsRayTracing.ush`, L11 `../Lumen/LumenHardwareRayTracingPayloadCommon.ush`, L12 `../Lumen/LumenHardwareRayTracingCommon.ush`, L14 `../HairStrands/HairStrandsRaytracing.ush` [HAIR_VOXEL_TRACES], L17 `../ColorMap.ush` [DEBUG_MODE]

#### Entry points (1)

- L60-381 _entry_ `RAY_TRACING_ENTRY_RAYGEN_OR_INLINE(HardwareRayTraceLightSamples)` — stage: **raygeneration\|compute(inline)**

#### Global resources (textures / buffers / samplers) (11)

- L26 _resource_ `RaytracingAccelerationStructure TLAS;`
- L27 _resource_ `RaytracingAccelerationStructure FarFieldTLAS;`
- L47 _resource_ `StructuredBuffer<FHitGroupRootConstants> HitGroupData;` _[#if LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L48 _resource_ `StructuredBuffer<FRayTracingSceneMetadataRecord> RayTracingSceneMetadata;` _[#if LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L49 _resource_ `RWStructuredBuffer<uint> RWInstanceHitCountBuffer;` _[#if LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L52 _resource_ `RWTexture2D<uint> RWLightSamples;`
- L53 _resource_ `RWTexture2D<uint> RWLightSampleRays;`
- L55 _resource_ `Buffer<uint> CompactedTraceTexelData;`
- L56 _resource_ `Buffer<uint> CompactedTraceTexelAllocator;`
- L57 _resource_ `Texture2D<float> DownsampledSceneDepth;`
- L58 _resource_ `Texture2D<UNORM float3> DownsampledSceneWorldNormal;`

#### Global parameters (uniforms) (19)

- L20 _parameter_ `float RayTracingBias;`
- L21 _parameter_ `float RayTracingNormalBias;`
- L22 _parameter_ `float RayTracingPullbackBias;`
- L23 _parameter_ `uint DebugVisualizeTraces;`
- L24 _parameter_ `uint MaxTraversalIterations;`
- L25 _parameter_ `uint MeshSectionVisibilityTest;`
- L29 _parameter_ `float NearFieldSceneRadius;`
- L30 _parameter_ `float NearFieldMaxTraceDistance;`
- L31 _parameter_ `float NearFieldMaxTraceDistanceDitherScale;`
- L32 _parameter_ `float FarFieldBias;`
- L33 _parameter_ `float FarFieldMaxTraceDistance;`
- L34 _parameter_ `float HairNonShadowedLightMaxTraceDistance;`
- L36 _parameter_ `float DistantScreenTraceSlopeCompareTolerance;`
- L37 _parameter_ `float DistantScreenTraceStartDistance;`
- L38 _parameter_ `float DistantScreenTraceLength;`
- L41 _parameter_ `uint VisualizeRays;` — Visualize Rays
- L42 _parameter_ `uint VisualizeRaysMinIterations;`
- L43 _parameter_ `uint VisualizeRaysHeatmapMin;`
- L44 _parameter_ `uint VisualizeRaysHeatmapMax;`

### `Shaders/Private/MegaLights/MegaLightsLightComplexity.usf` (Private)

- lines: 1643; parse: all-branches
- includes: L3 `MegaLightsSamplingDefinitionsCommon.ush`, L5 `../Common.ush`, L17 `MegaLightsLightTargetPDF.ush`, L18 `MegaLightsVolume.ush`, L19 `MegaLightsVisibility.ush`, L20 `../StochasticLighting/StochasticLightingCommon.ush`, L1609 `../ColorMap.ush` [defined(MegaLightsPostProcessVisualizePS)], L1610 `../ScreenPass.ush` [defined(MegaLightsPostProcessVisualizePS)]

#### Macros (#define, 10)

- L8 `#define SUBSTRATE_FASTPATH 0` _[#if SUBSTRATE_ENABLED]_
- L9 `#define SUBSTRATE_SINGLEPATH 0` _[#if SUBSTRATE_ENABLED]_
- L10 `#define SUBSTRATE_COMPLEXSPECIALPATH 1` _[#if SUBSTRATE_ENABLED]_
- L12 `#define USE_HAIR_COMPLEX_TRANSMITTANCE 1`
- L13 `#define USE_LIGHT_SOFT_FADING 1`
- L14 `#define DEBUG_MODE 1`
- L15 `#define OVERRIDE_USE_SOURCE_TEXTURE 1`
- L23 `#define IS_VISUALIZING_VOLUME 0` _[#if !defined(IS_VISUALIZING_VOLUME)]_
- L26 `#define DEPTH_SCALE_SLIDER_NAME TEXT("Depth:")`
- L27 `#define LATCH_DEPTH_CHKBOX_NAME TEXT("Latch depth")`
- L209 #pragma `warning(disable:7203)`

#### Entry points (5)

- L278-580 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void MegaLightsSortLightsForDisplayCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FMegaLightsSortLightsForDisplayCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/MegaLights/MegaLightsVisualizeLightComplexity.cpp:286) _[#if defined(MegaLightsSortLightsForDisplayCS)]_
- L859-1064 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void MegaLightsIntersectDisplayedLightsCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FMegaLightsIntersectDisplayedLightsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/MegaLights/MegaLightsVisualizeLightComplexity.cpp:329) _[#if defined(MegaLightsIntersectDisplayedLightsCS)]_
- L1202-1503 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void MegaLightsDisplayLightsCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FMegaLightsDisplayLightsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/MegaLights/MegaLightsVisualizeLightComplexity.cpp:397) _[#if defined(MegaLightsDisplayLightsCS)]_
- L1537-1603 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void MegaLightsEstimateLightSamplingCostCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FMegaLightsEstimateLightSamplingCostCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/MegaLights/MegaLightsVisualizeLightComplexity.cpp:437) _[#if defined(MegaLightsEstimateLightSamplingCostCS)]_
- L1618-1640 _entry_ `void MegaLightsPostProcessVisualizePS( in float4 SvPosition : SV_POSITION, out float4 OutLuminanceTransmittance : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FMegaLightsPostProcessVisualizePS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/MegaLights/MegaLightsVisualizeLightComplexity.cpp:478) _[#if defined(MegaLightsPostProcessVisualizePS)]_

#### Structs / classes (2)

- L619-627 _struct_ **`FGlobalFrozenData`** `struct FGlobalFrozenData`
  - L621 _member_ `uint NumLights;`
  - L622 _member_ `float LightTargetPDFSum;`
  - L623 _member_ `float3 TranslatedWorldPosition;`
  - L624 _member_ `float3 FrozenTranslatedWorldDelta;`
  - L625 _member_ `float3 VoxelVerts[8];`
  - L626 _member_ `float3 VolumeVerts[8];`
- L684-691 _struct_ **`FLightFrozenDataExceptName`** `struct FLightFrozenDataExceptName`
  - L686 _member_ `float LightVisibility;`
  - L687 _member_ `float LightTargetPDF;`
  - L688 _member_ `float3 LightTWPositionOrDirection;`
  - L689 _member_ `float3 LightColor;`
  - L690 _member_ `uint LightType;`

#### Global resources (textures / buffers / samplers) (14)

- L150 _resource_ `RWByteAddressBuffer RWGeneralPurposeFeedback;` — Total: 1 dword 0: bit0 - bIsWritten, bit1 - bInnerTLVSelected
- L160 _resource_ `RWByteAddressBuffer RWGeneralPurposeState;` — Total: 1 dword 0: Latched scene depth. Zero means nothing is latched
- L173 _resource_ `RWStructuredBuffer<uint> RWSortedLightInfo;` — SortedLightInfo: 2 dwords + 2 dwords/light
- L174 _resource_ `StructuredBuffer<uint> SortedLightInfo;`
- L211 _resource_ `Texture2D<uint> PackedPixelDataTexture;` _[#if defined(MegaLightsSortLightsForDisplayCS)]_
- L212 _resource_ `Texture2D<uint2> EncodedHistoryScreenCoordTexture;` _[#if defined(MegaLightsSortLightsForDisplayCS)]_
- L213 _resource_ `StructuredBuffer<uint> VisibleLightHashHistory;` _[#if defined(MegaLightsSortLightsForDisplayCS)]_
- L584 _resource_ `RWByteAddressBuffer RWFrozenLightData;`
- L585 _resource_ `ByteAddressBuffer FrozenLightData;`
- L855 _resource_ `RWStructuredBuffer<uint> RWSelectedLightIndex;` _[#if defined(MegaLightsIntersectDisplayedLightsCS)]_
- L1070 _resource_ `StructuredBuffer<uint> SelectedLightIndexBuffer;` _[#if defined(MegaLightsDisplayLightsCS)]_
- L1509 _resource_ `RWTexture2D<float> RWLightSamplingCostEstimate;` _[#if defined(MegaLightsEstimateLightSamplingCostCS)]_
- L1612 _resource_ `Texture2D InputSceneColor;` _[#if defined(MegaLightsPostProcessVisualizePS)]_
- L1613 _resource_ `Texture2D<float> LightSamplingCostEstimateTexture;` _[#if defined(MegaLightsPostProcessVisualizePS)]_

#### Global parameters (uniforms) (17)

- L32 _parameter_ `uint TranslucencyVolumeCascadeIndex;` _[#if !TRANSLUCENCY_LIGHTING_VOLUME]_
- L34 _parameter_ `float VolumeInverseSquaredLightDistanceBiasScale;`
- L35 _parameter_ `uint IsUnifiedVolume;`
- L215 _parameter_ `float4 HistorySubPixelGridSizeAndInvSize;` _[#if defined(MegaLightsSortLightsForDisplayCS)]_
- L216 _parameter_ `uint2 HistoryScreenCoordDecodeShift;` _[#if defined(MegaLightsSortLightsForDisplayCS)]_
- L217 _parameter_ `uint2 HistoryVisibleLightHashViewMinInTiles;` _[#if defined(MegaLightsSortLightsForDisplayCS)]_
- L218 _parameter_ `uint2 HistoryVisibleLightHashViewSizeInTiles;` _[#if defined(MegaLightsSortLightsForDisplayCS)]_
- L219 _parameter_ `float TransmissionSampleWeight;` _[#if defined(MegaLightsSortLightsForDisplayCS)]_
- L221 _parameter_ `uint3 VolumeVisibleLightHashTileSize;` _[#if defined(MegaLightsSortLightsForDisplayCS)]_
- L222 _parameter_ `uint3 HistoryVolumeVisibleLightHashViewSizeInTiles;` _[#if defined(MegaLightsSortLightsForDisplayCS)]_
- L749 _parameter_ `uint MaxNumLightsToDisplay;`
- L851 _parameter_ `int bUseFrozenLightData;`
- L1072 _parameter_ `int bOutputFrozenLightData;` _[#if defined(MegaLightsDisplayLightsCS)]_
- L1073 _parameter_ `int bIsVisualizingVolume;` _[#if defined(MegaLightsDisplayLightsCS)]_
- L1511 _parameter_ `int bUseHairComplexTransmittance;` _[#if defined(MegaLightsEstimateLightSamplingCostCS)]_
- L1615 _parameter_ `FScreenTransform OutputToInputPixelPos;` _[#if defined(MegaLightsPostProcessVisualizePS)]_
- L1616 _parameter_ `float MaxLightSamplingCost;` _[#if defined(MegaLightsPostProcessVisualizePS)]_

#### groupshared (4)

- L224 _groupshared_ `groupshared uint SharedLightSortKeys[THREADGROUP_SIZE * 2];` _[#if defined(MegaLightsSortLightsForDisplayCS)]_
- L225 _groupshared_ `groupshared uint SharedLightIndices[THREADGROUP_SIZE * 2];` _[#if defined(MegaLightsSortLightsForDisplayCS)]_
- L857 _groupshared_ `groupshared uint2 SharedScratchMemory[THREADGROUP_SIZE];` _[#if defined(MegaLightsIntersectDisplayedLightsCS)]_
- L1075 _groupshared_ `groupshared uint SharedScratchMemory[THREADGROUP_SIZE];` _[#if defined(MegaLightsDisplayLightsCS)]_

#### static const (2)

- L29 _static_const_ `static const float GMinCursorDepth = 20.0f;`
- L747 _static_const_ `static const float2 GLightListPrintStartPos = float2(0.05, 0.05);`

#### Functions (33)

- L37-103 _function_ `FLightTargetPDF GetLightTargetPDF( uint2 ScreenCoord, float3 VolumeCoord, float3 TranslatedWorldPosition, const FMegaLightsMaterial Material, int ForwardLightIndex, FDeferredLightData LightData, FForwardLightData ForwardLightData, float AssumedTransmissionThickness, inout FShaderPrintContext DebugContext)`
- L105-120 _function_ `FLightTargetPDF GetDirectionalLightTargetPDF( uint2 ScreenCoord, float3 VolumeCoord, float3 TranslatedWorldPosition, const FMegaLightsMaterial Material, int ForwardLightIndex, FDeferredLightData LightData, FForwardLightData ForwardLightData, float AssumedTransmissionThickness, inout FShaderPrintContext DebugContext)`
- L122-146 _function_ `float GetMaxSceneDepthForInvalidPixels()`
- L152-156 _function_ `void WriteIsInnerTLVSelectedFeedback(bool bInnerTLVSelected)`
- L162-165 _function_ `void WriteLatchedSceneDepth(float SceneDepth)`
- L167-170 _function_ `float ReadLatchedSceneDepth()`
- L176-180 _function_ `void StoreSortedLightInfoGlobalData(uint NumLights, float LightTargetPDFSum)`
- L182-186 _function_ `void LoadSortedLightInfoGlobalData(out uint OutNumLights, out float OutLightTargetPDFSum)`
- L188-195 _function_ `void StoreSortedLightInfo(uint SortedIndex, uint ForwardLightIndex, float LightVisibility, float LightTargetPDF)`
- L197-205 _function_ `void LoadSortedLightInfo(uint SortedIndex, out uint OutForwardLightIndex, out float OutLightVisibility, out float OutLightTargetPDF)`
- L227-276 _function_ `void SortLights(uint GroupThreadIndex, uint NumLights)` _[#if defined(MegaLightsSortLightsForDisplayCS)]_
- L587-594 _function_ `void StoreSingleFrozenData(uint GroupThreadIndex, inout uint Ptr, uint Value)`
- L596-603 _function_ `void StoreSingleFrozenData(uint GroupThreadIndex, inout uint Ptr, uint3 Value)`
- L605-610 _function_ `uint LoadFrozenData(inout uint Ptr)`
- L612-617 _function_ `uint3 LoadFrozenData3(inout uint Ptr)`
- L629-633 _function_ `FGlobalFrozenData InitGlobalFrozenData()`
- L636-654 _function_ `void StoreGlobalFrozenData( uint GroupThreadIndex, inout uint Ptr, FGlobalFrozenData In)` — Serialized GloablFrozenData: 59 dwords
- L656-682 _function_ `FGlobalFrozenData LoadGlobalFrozenData(inout uint Ptr)`
- L694-697 _function_ `uint GetLightFrozenDataSizeInBytes()` — Serialized LightFrozenData: 8 dwords + ForwardLightStruct.LightNameDwords
- L699-703 _function_ `FLightFrozenDataExceptName InitLightFrozenDataExceptName()`
- L705-724 _function_ `void StoreLightFrozenDataExceptName( uint GroupThreadIndex, inout uint Ptr, FLightFrozenDataExceptName In, bool bValid)`
- L726-745 _function_ `bool LoadLightFrozenDataExceptName( inout uint Ptr, float3 FrozenTranslatedWorldDelta, out FLightFrozenDataExceptName Out)`
- L751-789 _function_ `void PrintHeader(inout FShaderPrintContext Context, uint GroupThreadIndex, uint2 ScreenCoord, int3 VolumeCoord, uint NumLights, bool bIsVisualizingVolume, bool bUseFrozenLightData)`
- L791-807 _function_ `uint GetLightType(FDeferredLightData LightData)`
- L809-828 _function_ `FShaderPrintText GetLightTypeText(uint LightType)`
- L830-849 _function_ `uint PrintLightInfoExceptName(inout FShaderPrintContext Context, uint GroupThreadIndex, float WeightRatio, float LightVisibility, uint LightType, FFontColor FontColor)`
- L1077-1096 _function_ `void AddRectLightSymbol(inout FShaderPrintContext Context, float3 LightTranslatedWorldPosition, float2 Extent, float4 Color)` _[#if defined(MegaLightsDisplayLightsCS)]_
- L1098-1125 _function_ `void AddSpotLightSymbol(inout FShaderPrintContext Context, float3 LightTranslatedWorldPosition, float Radius, float4 Color)` _[#if defined(MegaLightsDisplayLightsCS)]_
- L1127-1154 _function_ `void AddCameraFacingStar(inout FShaderPrintContext Context, float3 TranslatedWorldPosition, float Size, float4 Color)` _[#if defined(MegaLightsDisplayLightsCS)]_
- L1156-1168 _function_ `void GetVoxelVertices(int3 VolumeCoord, out float3 OutVerts[8])` _[#if defined(MegaLightsDisplayLightsCS)]_
- L1170-1182 _function_ `void GetVolumeVertices(out float3 OutVerts[8])` _[#if defined(MegaLightsDisplayLightsCS)]_
- L1184-1200 _function_ `void AddBoxTWS(inout FShaderPrintContext Context, float3 Verts[8], float4 Color)` _[#if defined(MegaLightsDisplayLightsCS)]_
- L1513-1535 _function_ `float GetLightSamplingCostEstimate( float MaterialCostAdd, uint LightingChannelMask, FDeferredLightData LightData, FForwardLightData ForwardLightData)` _[#if defined(MegaLightsEstimateLightSamplingCostCS)]_

### `Shaders/Private/MegaLights/MegaLightsLightPowerDelta.usf` (Private)

- lines: 63; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../LightGridCommon.ush`, L5 `../MegaLights/MegaLightsEstimateLight.ush`, L6 `../LightFunctionAtlas/LightFunctionAtlasCommon.usf`

#### Entry points (1)

- L30-61 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void ComputeLightPowerDeltaCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FComputeLightPowerDeltaCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/MegaLights/MegaLightsLightPowerDelta.cpp:84) _[#if defined(ComputeLightPowerDeltaCS)]_

#### Global resources (textures / buffers / samplers) (3)

- L10 _resource_ `RWBuffer<float> RWLightPowerHistoryRatio;` _[#if defined(ComputeLightPowerDeltaCS)]_
- L11 _resource_ `RWBuffer<float> RWLightPower;` _[#if defined(ComputeLightPowerDeltaCS)]_
- L12 _resource_ `Buffer<float> PrevLightPowerBuffer;` _[#if defined(ComputeLightPowerDeltaCS)]_

#### Global parameters (uniforms) (3)

- L14 _parameter_ `int bUseLightFunctionAtlas;` _[#if defined(ComputeLightPowerDeltaCS)]_
- L15 _parameter_ `int bHasPrevLightPower;` _[#if defined(ComputeLightPowerDeltaCS)]_
- L16 _parameter_ `float HistoryPreExposureCorrection;` _[#if defined(ComputeLightPowerDeltaCS)]_

#### Functions (1)

- L18-28 _function_ `FLightFunctionColor GetLightFunctionForPowerEstimate(FDeferredLightData LightData)` _[#if defined(ComputeLightPowerDeltaCS)]_

### `Shaders/Private/MegaLights/MegaLightsLightTargetPDF.ush` (Private)

- lines: 61; parse: all-branches
- includes: L5 `MegaLightsShading.ush`
- L3 #pragma `once`

#### Structs / classes (1)

- L9-13 _struct_ **`FLightTargetPDF`** `struct FLightTargetPDF`
  - L11 _member_ `float Weight;`
  - L12 _member_ `float Luminance;` — Linear, no falloff mask

#### Global parameters (uniforms) (1)

- L7 _parameter_ `float MinSampleWeight;`

#### Functions (2)

- L15-21 _function_ `FLightTargetPDF InitLightTargetPDF()`
- L23-60 _function_ `FLightTargetPDF GetLocalLightTargetPDF(int ForwardLightIndex, FDeferredLightData LightData, float4 LightAttenuation, float3 TranslatedWorldPosition, FMegaLightsMaterial Material, uint2 ScreenCoord)`

### `Shaders/Private/MegaLights/MegaLightsMaterial.ush` (Private)

- lines: 480; parse: first-branch (retry, +13 merged from all-branches pass)
- includes: L14 `../BRDF.ush`, L15 `/Engine/Private/HairShadingCommon.ush`, L16 `../DeferredShadingCommon.ush`, L17 `../GammaCorrectionCommon.ush`, L18 `../Lumen/LumenPosition.ush`, L20 `../HairStrands/HairStrandsVisibilityCommon.ush`, L21 `../HairStrands/HairStrandsVisibilityUtils.ush`, L22 `../HairStrands/HairStrandsCommon.ush`, L23 `../HairStrands/HairStrandsDeepTransmittanceCommon.ush`, L24 `../HairStrands/HairStrandsDeepTransmittanceDualScattering.ush`, L26 `../Substrate/Substrate.ush`, L27 `../Substrate/SubstrateEvaluation.ush`, L28 `../Substrate/SubstrateMaterialSampling.ush`, L29 `../Substrate/SubstrateTile.ush`, L30 `../Substrate/SubstrateRead.ush`

#### Macros (#define, 5)

- L6 `#define SUBSTRATE_LOAD_FROM_MATERIALCONTAINER 0` _[#if SUBSTRATE_ENABLED && SUBSTRATE_GBUFFER_FORMAT==0]_
- L11 `#define FORCE_SIMPLE_SHADING 0` _[#if !defined(FORCE_SIMPLE_SHADING)]_
- L33 `#define INPUT_TYPE_GBUFFER 0`
- L34 `#define INPUT_TYPE_HAIRSTRANDS 1`
- L35 `#define INPUT_TYPE_FRONTLAYERTRANSLUCENCY 2`
- L3 #pragma `once`

#### Structs / classes (2)

- L46-115 _struct_ **`FMegaLightsMaterial`** `struct FMegaLightsMaterial`
  - L49 _member_ `float DeviceZ;` — DeviceZ isn't the same as ConvertToDeviceZ(Depth) due to a small fudge factor preventing divide by zero
  - L50 _member_ `float Depth;`
  - L52 _member_ `float3 WorldNormal;`
  - L53 _member_ `float3 WorldNormalForPositionBias;`
  - L54 _member_ `float Roughness;`
  - L55 _member_ `bool bIsValid;`
  - L56 _member_ `bool bIsSimple;`
  - L57 _member_ `bool bIsSingle;`
  - L58 _member_ `bool bIsComplexSpecial;`
  - L59 _member_ `bool bIsHair;`
  - L60 _member_ `bool bIsTwoSided;`
  - L61 _member_ `bool bIsFirstPerson;`
  - L62 _member_ `bool bHasTransmission;`
  - L63 _member_ `bool bNeedsSeparateSubsurfaceLightAccumulation;`
  - L64 _member_ `bool bNeedsComplexTransmittance;`
  - L65 _member_ `bool bAllowSpatialFilter;`
  - L66 _member_ `uint LightingChannelMask;` — Not loaded by default
  - L67 _member_ `float Coverage;`
  - L68 _member_ `uint GlobalIndex1D;`
  - L69 _member_ `uint2 GlobalIndex2D;`
  - L71 _member_ `float3 DiffuseColor;`
  - L72 _member_ `float3 SpecularColor;`
  - L74 _method_ `bool IsValid()`
  - L79 _method_ `bool IsSimple()`
  - L84 _method_ `bool IsSingle()`
  - L89 _method_ `bool IsComplexSpecial()`
  - L95 _member_ `FGBufferData GBuffer;` _[#if INPUT_TYPE == INPUT_TYPE_HAIRSTRANDS]_
  - L96 _member_ `uint MacroGroupId;` _[#if INPUT_TYPE == INPUT_TYPE_HAIRSTRANDS]_
  - L98 _member_ `FGBufferData GBuffer;` _[#if !(INPUT_TYPE == INPUT_TYPE_HAIRSTRANDS) && INPUT_TYPE == INPUT_TYPE_FRONTLAYERTRANSLUCENCY]_
  - L99 _member_ `float Opacity;` _[#if !(INPUT_TYPE == INPUT_TYPE_HAIRSTRANDS) && INPUT_TYPE == INPUT_TYPE_FRONTLAYERTRANSLUCENCY]_
  - L101 _member_ `uint ClosureIndex;` _[#if !(INPUT_TYPE == INPUT_TYPE_HAIRSTRANDS) && !(INPUT_TYPE == INPUT_TYPE_FRONTLAYERTRANSLUCENCY) && SUBSTRATE_ENABLED && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L102 _member_ `float PDF;` _[#if !(INPUT_TYPE == INPUT_TYPE_HAIRSTRANDS) && !(INPUT_TYPE == INPUT_TYPE_FRONTLAYERTRANSLUCENCY) && SUBSTRATE_ENABLED && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L103 _member_ `FSubstrateSubsurfaceHeader SSSHeader;` _[#if !(INPUT_TYPE == INPUT_TYPE_HAIRSTRANDS) && !(INPUT_TYPE == INPUT_TYPE_FRONTLAYERTRANSLUCENCY) && SUBSTRATE_ENABLED && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L104 _member_ `FSubstrateBSDF BSDF;` _[#if !(INPUT_TYPE == INPUT_TYPE_HAIRSTRANDS) && !(INPUT_TYPE == INPUT_TYPE_FRONTLAYERTRANSLUCENCY) && SUBSTRATE_ENABLED && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L105 _member_ `float3x3 BSDFTangentBasis;` _[#if !(INPUT_TYPE == INPUT_TYPE_HAIRSTRANDS) && !(INPUT_TYPE == INPUT_TYPE_FRONTLAYERTRANSLUCENCY) && SUBSTRATE_ENABLED && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L106 _member_ `float BSDFAO;` _[#if !(INPUT_TYPE == INPUT_TYPE_HAIRSTRANDS) && !(INPUT_TYPE == INPUT_TYPE_FRONTLAYERTRANSLUCENCY) && SUBSTRATE_ENABLED && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L108 _member_ `FGBufferData GBuffer;` _[#if !(INPUT_TYPE == INPUT_TYPE_HAIRSTRANDS) && !(INPUT_TYPE == INPUT_TYPE_FRONTLAYERTRANSLUCENCY) && !(SUBSTRATE_ENABLED && SUBSTRATE_GBUFFER_FORMAT==1) && SUBSTRATE_ENABLED && SUBSTRATE_GBUFFER_FORMAT==0]_
  - L109 _member_ `FSubstrateBSDF BSDF;` _[#if !(INPUT_TYPE == INPUT_TYPE_HAIRSTRANDS) && !(INPUT_TYPE == INPUT_TYPE_FRONTLAYERTRANSLUCENCY) && !(SUBSTRATE_ENABLED && SUBSTRATE_GBUFFER_FORMAT==1) && SUBSTRATE_ENABLED && SUBSTRATE_GBUFFER_FORMAT==0]_
  - L110 _member_ `float3x3 BSDFTangentBasis;` _[#if !(INPUT_TYPE == INPUT_TYPE_HAIRSTRANDS) && !(INPUT_TYPE == INPUT_TYPE_FRONTLAYERTRANSLUCENCY) && !(SUBSTRATE_ENABLED && SUBSTRATE_GBUFFER_FORMAT==1) && SUBSTRATE_ENABLED && SUBSTRATE_GBUFFER_FORMAT==0]_
  - L111 _member_ `float BSDFAO;` _[#if !(INPUT_TYPE == INPUT_TYPE_HAIRSTRANDS) && !(INPUT_TYPE == INPUT_TYPE_FRONTLAYERTRANSLUCENCY) && !(SUBSTRATE_ENABLED && SUBSTRATE_GBUFFER_FORMAT==1) && SUBSTRATE_ENABLED && SUBSTRATE_GBUFFER_FORMAT==0]_
  - L113 _member_ `FGBufferData GBuffer;` _[#if !(INPUT_TYPE == INPUT_TYPE_HAIRSTRANDS) && !(INPUT_TYPE == INPUT_TYPE_FRONTLAYERTRANSLUCENCY) && !(SUBSTRATE_ENABLED && SUBSTRATE_GBUFFER_FORMAT==1) && !(SUBSTRATE_ENABLED && SUBSTRATE_GBUFFER_FORM...]_
- L452-456 _struct_ **`FDenoisingModulateFactors`** `struct FDenoisingModulateFactors`
  - L454 _member_ `float3 Diffuse;`
  - L455 _member_ `float3 Specular;`

#### Global resources (textures / buffers / samplers) (4)

- L38 _resource_ `Texture2D FrontLayerTranslucencySceneDepth;` _[#if INPUT_TYPE == INPUT_TYPE_FRONTLAYERTRANSLUCENCY]_
- L39 _resource_ `Texture2D FrontLayerTranslucencyGBufferA;` _[#if INPUT_TYPE == INPUT_TYPE_FRONTLAYERTRANSLUCENCY]_
- L40 _resource_ `Texture2D FrontLayerTranslucencyGBufferB;` _[#if INPUT_TYPE == INPUT_TYPE_FRONTLAYERTRANSLUCENCY]_
- L41 _resource_ `Texture2D FrontLayerTranslucencyGBufferC;` _[#if INPUT_TYPE == INPUT_TYPE_FRONTLAYERTRANSLUCENCY]_

#### Global parameters (uniforms) (1)

- L43 _parameter_ `uint FrontLayerTranslucencySpecularOnly;` _[#if INPUT_TYPE == INPUT_TYPE_FRONTLAYERTRANSLUCENCY]_

#### Functions (2)

- L118-173 _function_ `FMegaLightsMaterial LoadMaterial(float2 ScreenUV, uint2 ScreenCoord, uint SampleIt=0)` _[#if defined(INPUT_TYPE)]_
- L462-480 _function_ `FDenoisingModulateFactors GetDenoisingModulateFactors(FMegaLightsMaterial Material, float NoV)` — Factors used to remove non-stochastic material detail before denoising in order to preserve texture detail Divide before denoising and multiply after

### `Shaders/Private/MegaLights/MegaLightsRayTracing.usf` (Private)

- lines: 510; parse: all-branches
- includes: L3 `../Common.ush`, L5 `../BlueNoise.ush`, L6 `../DistanceField/GlobalDistanceFieldShared.ush`, L7 `../DistanceField/GlobalDistanceFieldUtils.ush`, L15 `../Lumen/LumenScreenTracing.ush`, L16 `../SceneTexturesCommon.ush`, L17 `MegaLights.ush`, L18 `MegaLightsRayTracing.ush`, L19 `MegaLightsTileClassification.ush`, L20 `../StochasticLighting/StochasticLightingRayTracing.ush`, L22 `../HairStrands/HairStrandsRaytracing.ush` [HAIR_VOXEL_TRACES]

#### Macros (#define, 5)

- L4 `#define DISTANCE_FIELD_IN_VIEW_UB 1`
- L9 `#define HZB_TRACE_INCLUDE_FULL_RES_DEPTH 1` _[#if SCREEN_TRACE_QUALITY == 1]_
- L10 `#define HZB_TRACE_USE_BILINEAR_SAMPLED_DEPTH 1` _[#if SCREEN_TRACE_QUALITY == 1]_
- L12 `#define HZB_TRACE_INCLUDE_FULL_RES_DEPTH 0` _[#if !(SCREEN_TRACE_QUALITY == 1)]_
- L13 `#define HZB_TRACE_USE_BILINEAR_SAMPLED_DEPTH 0` _[#if !(SCREEN_TRACE_QUALITY == 1)]_

#### Entry points (5)

- L31-48 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void InitCompactedTraceTexelIndirectArgsCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FInitCompactedTraceTexelIndirectArgsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/MegaLights/MegaLightsRayTracing.cpp:783) _[#if defined(InitCompactedTraceTexelIndirectArgsCS)]_
- L90-211 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void CompactLightSampleTracesCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FCompactLightSampleTracesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/MegaLights/MegaLightsRayTracing.cpp:683) _[#if defined(CompactLightSampleTracesCS)]_
- L237-374 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void ScreenSpaceRayTraceLightSamplesCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FScreenSpaceRayTraceLightSamplesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/MegaLights/MegaLightsRayTracing.cpp:1185) _[#if defined(ScreenSpaceRayTraceLightSamplesCS)]_
- L381-454 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void SoftwareRayTraceLightSamplesCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FSoftwareRayTraceLightSamplesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/MegaLights/MegaLightsRayTracing.cpp:1077) _[#if defined(SoftwareRayTraceLightSamplesCS)]_
- L468-507 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void PrintTraceStatsCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FPrintTraceStatsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/MegaLights/MegaLightsRayTracing.cpp:820) _[#if defined(PrintTraceStatsCS)]_

#### Global resources (textures / buffers / samplers) (20)

- L25 _resource_ `Buffer<uint> CompactedTraceTexelAllocator;`
- L29 _resource_ `RWBuffer<uint> RWIndirectArgs;` _[#if defined(InitCompactedTraceTexelIndirectArgsCS)]_
- L64 _resource_ `Texture2D<uint> MegaLightsTileBitmask;`
- L65 _resource_ `Texture2D<uint> LightSamples;`
- L66 _resource_ `Texture2D<uint> LightSampleRays;`
- L68 _resource_ `Texture2D<uint> RWTraceTile;`
- L69 _resource_ `RWBuffer<uint> RWCompactedTraceTexelData;`
- L70 _resource_ `RWBuffer<uint> RWCompactedTraceTexelAllocator;`
- L215 _resource_ `RWTexture2D<uint> RWLightSamples;`
- L216 _resource_ `RWTexture2D<uint> RWLightSampleRays;`
- L218 _resource_ `Buffer<uint> CompactedTraceTexelData;`
- L219 _resource_ `Texture2D<float> DownsampledSceneDepth;`
- L220 _resource_ `Texture2D<UNORM float3> DownsampledSceneWorldNormal;`
- L460 _resource_ `Buffer<uint> VSMIndirectArgs;` _[#if defined(PrintTraceStatsCS)]_
- L461 _resource_ `Buffer<uint> ScreenIndirectArgs;` _[#if defined(PrintTraceStatsCS)]_
- L462 _resource_ `Buffer<uint> WorldIndirectArgs;` _[#if defined(PrintTraceStatsCS)]_
- L463 _resource_ `Buffer<uint> WorldMaterialRetraceIndirectArgs;` _[#if defined(PrintTraceStatsCS)]_
- L464 _resource_ `Buffer<uint> VolumeIndirectArgs;` _[#if defined(PrintTraceStatsCS)]_
- L465 _resource_ `Buffer<uint> TranslucencyVolume0IndirectArgs;` _[#if defined(PrintTraceStatsCS)]_
- L466 _resource_ `Buffer<uint> TranslucencyVolume1IndirectArgs;` _[#if defined(PrintTraceStatsCS)]_

#### Global parameters (uniforms) (16)

- L52 _parameter_ `uint2 SampleViewMin;`
- L53 _parameter_ `uint2 SampleViewSize;`
- L54 _parameter_ `uint DebugVisualizeTraces;`
- L55 _parameter_ `float MaxHierarchicalScreenTraceIterations;`
- L56 _parameter_ `float MaxTraceDistance;`
- L57 _parameter_ `float HairNonShadowedLightMaxTraceDistance;`
- L58 _parameter_ `float RelativeDepthThickness;`
- L59 _parameter_ `float RelativeDepthThicknessNoFallback;`
- L60 _parameter_ `float RelativeDepthThicknessForFirstPerson;`
- L61 _parameter_ `uint MinimumTracingThreadOccupancy;`
- L62 _parameter_ `uint UseRayTracingRepresentationBit;`
- L74 _parameter_ `uint CompactForScreenSpaceTraces;` _[#if defined(CompactLightSampleTracesCS)]_
- L75 _parameter_ `uint UseFirstPersonScreenTraces;` _[#if defined(CompactLightSampleTracesCS)]_
- L76 _parameter_ `uint UseHairScreenTraces;` _[#if defined(CompactLightSampleTracesCS)]_
- L224 _parameter_ `float RayTracingNormalBias;` _[#if defined(ScreenSpaceRayTraceLightSamplesCS)]_
- L225 _parameter_ `float HairScreenTraceBias;` _[#if defined(ScreenSpaceRayTraceLightSamplesCS)]_

#### groupshared (4)

- L78 _groupshared_ `groupshared uint SharedGlobalTraceTexelStartOffset;` _[#if defined(CompactLightSampleTracesCS)]_
- L81 _groupshared_ `groupshared uint SharedGroupSum;` _[#if defined(CompactLightSampleTracesCS) && WAVE_OP_WAVE_SIZE > 0]_
- L83 _groupshared_ `groupshared uint SharedTraceTexelAllocator;` _[#if defined(CompactLightSampleTracesCS) && !(WAVE_OP_WAVE_SIZE > 0)]_
- L84 _groupshared_ `groupshared uint SharedTraceTexels[THREADGROUP_SIZE * THREADGROUP_SIZE];` _[#if defined(CompactLightSampleTracesCS) && !(WAVE_OP_WAVE_SIZE > 0)]_

#### Functions (2)

- L227-230 _function_ `bool CastShadow(uint SceneLightingChannelsMask)` _[#if defined(ScreenSpaceRayTraceLightSamplesCS)]_
- L232-235 _function_ `bool HasRaytracingRepresentation(uint SceneLightingChannelsMask)` _[#if defined(ScreenSpaceRayTraceLightSamplesCS)]_

#### Top-level macro invocations (1)

- L88 _macro_call_ `WAVESIZE(WAVE_OP_WAVE_SIZE)` _[#if defined(CompactLightSampleTracesCS) && COMPILER_SUPPORTS_WAVE_SIZE && WAVE_OP_WAVE_SIZE > 0]_

### `Shaders/Private/MegaLights/MegaLightsRayTracing.ush` (Private)

- lines: 159; parse: all-branches
- includes: L5 `../RayTracing/RayTracingCapsuleLight.ush`, L6 `../RayTracing/RayTracingSphereLight.ush`, L7 `../RayTracing/RayTracingRectLight.ush`, L8 `../RayTracing/RayTracingDirectionalLight.ush`
- L3 #pragma `once`

#### Structs / classes (1)

- L76-80 _struct_ **`FLightSampleTrace`** `struct FLightSampleTrace`
  - L78 _member_ `float3 Direction;`
  - L79 _member_ `float Distance;`

#### Functions (6)

- L10-74 _function_ `bool GenerateShadowRay( FLightShaderParameters LightParameters, bool bSpotLight, bool bRectLight, bool bDirLight, float3 TranslatedWorldPosition, float3 WorldNormal, float2 RandSample, out float3 RayOrigin, out float3 RayDirection, out float RayTMin, out float RayTMax)`
- L85-127 _function_ `FLightSampleTrace GetLightSampleTrace(float3 TranslatedWorldPosition, uint LocalLightIndex, float2 LightSampleUV)` — Compute shadow ray direction and distance for a given light sample.
- L129-134 _function_ `uint PackTraceTexel(uint2 SampleCoord)`
- L136-142 _function_ `uint2 UnpackTraceTexel(uint PackedTraceTexel)`
- L144-150 _function_ `uint PackTraceVoxel(uint3 SampleCoord)`
- L152-159 _function_ `uint3 UnpackTraceVoxel(uint PackedTraceVoxel)`

### `Shaders/Private/MegaLights/MegaLightsSampling.usf` (Private)

- lines: 640; parse: all-branches
- includes: L13 `MegaLightsSamplingDefinitionsCommon.ush`, L15 `../Common.ush`, L16 `/Engine/Shared/MegaLightsDefinitions.h`, L48 `../BlueNoise.ush`, L49 `MegaLightsLightTargetPDF.ush`, L50 `MegaLightsRayTracing.ush`, L51 `MegaLightsSampling.ush`, L52 `MegaLightsEstimateLight.ush`, L53 `MegaLightsVisibility.ush`, L54 `../LightFunctionAtlas/LightFunctionAtlasCommon.usf`, L55 `../StochasticLighting/StochasticLightingCommon.ush`

#### Macros (#define, 19)

- L4 `#define NUM_SAMPLES_PER_PIXEL_1D 1` _[#if !defined(NUM_SAMPLES_PER_PIXEL_1D)]_
- L5 `#define NUM_SAMPLES_PER_PIXEL_2D_X 1` _[#if !defined(NUM_SAMPLES_PER_PIXEL_1D)]_
- L6 `#define NUM_SAMPLES_PER_PIXEL_2D_Y 1` _[#if !defined(NUM_SAMPLES_PER_PIXEL_1D)]_
- L10 `#define TILE_TYPE TILE_MODE_EMPTY` _[#if !defined(TILE_TYPE)]_
- L20 `#define FORCE_SIMPLE_SHADING 1` _[#if TILE_TYPE == TILE_MODE_SIMPLE_SHADING \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT_TEXTURED \|\| TILE_TYPE == TILE_MODE_EMPTY]_
- L26 `#define SUBSTRATE_FASTPATH 1` _[#if SUBSTRATE_ENABLED && TILE_TYPE == TILE_MODE_SIMPLE_SHADING \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT_TEXTURED \|\| TILE_TYPE == TILE_MODE_EMPTY]_
- L27 `#define SUBSTRATE_SINGLEPATH 0` _[#if SUBSTRATE_ENABLED && TILE_TYPE == TILE_MODE_SIMPLE_SHADING \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT_TEXTURED \|\| TILE_TYPE == TILE_MODE_EMPTY]_
- L28 `#define SUBSTRATE_COMPLEXSPECIALPATH 0` _[#if SUBSTRATE_ENABLED && TILE_TYPE == TILE_MODE_SIMPLE_SHADING \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT_TEXTURED \|\| TILE_TYPE == TILE_MODE_EMPTY]_
- L30 `#define SUBSTRATE_FASTPATH 0` _[#if SUBSTRATE_ENABLED && !(TILE_TYPE == TILE_MODE_SIMPLE_SHADING \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT_TEXTURED \|\| TILE_TYPE == TILE_MODE_EMPTY) &&...]_
- L31 `#define SUBSTRATE_SINGLEPATH 1` _[#if SUBSTRATE_ENABLED && !(TILE_TYPE == TILE_MODE_SIMPLE_SHADING \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT_TEXTURED \|\| TILE_TYPE == TILE_MODE_EMPTY) &&...]_
- L32 `#define SUBSTRATE_COMPLEXSPECIALPATH 0` _[#if SUBSTRATE_ENABLED && !(TILE_TYPE == TILE_MODE_SIMPLE_SHADING \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT_TEXTURED \|\| TILE_TYPE == TILE_MODE_EMPTY) &&...]_
- L34 `#define SUBSTRATE_FASTPATH 0` _[#if SUBSTRATE_ENABLED && !(TILE_TYPE == TILE_MODE_SIMPLE_SHADING \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT_TEXTURED \|\| TILE_TYPE == TILE_MODE_EMPTY) &&...]_
- L35 `#define SUBSTRATE_SINGLEPATH 0` _[#if SUBSTRATE_ENABLED && !(TILE_TYPE == TILE_MODE_SIMPLE_SHADING \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT_TEXTURED \|\| TILE_TYPE == TILE_MODE_EMPTY) &&...]_
- L36 `#define SUBSTRATE_COMPLEXSPECIALPATH 0` _[#if SUBSTRATE_ENABLED && !(TILE_TYPE == TILE_MODE_SIMPLE_SHADING \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT_TEXTURED \|\| TILE_TYPE == TILE_MODE_EMPTY) &&...]_
- L38 `#define SUBSTRATE_FASTPATH 0` _[#if SUBSTRATE_ENABLED && !(TILE_TYPE == TILE_MODE_SIMPLE_SHADING \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT_TEXTURED \|\| TILE_TYPE == TILE_MODE_EMPTY) &&...]_
- L39 `#define SUBSTRATE_SINGLEPATH 0` _[#if SUBSTRATE_ENABLED && !(TILE_TYPE == TILE_MODE_SIMPLE_SHADING \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT_TEXTURED \|\| TILE_TYPE == TILE_MODE_EMPTY) &&...]_
- L40 `#define SUBSTRATE_COMPLEXSPECIALPATH 1` _[#if SUBSTRATE_ENABLED && !(TILE_TYPE == TILE_MODE_SIMPLE_SHADING \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT_TEXTURED \|\| TILE_TYPE == TILE_MODE_EMPTY) &&...]_
- L45 `#define SUBSTRATE_LOAD_FROM_MATERIALCONTAINER 0` _[#if SUBSTRATE_FASTPATH \|\| SUBSTRATE_SINGLEPATH]_
- L325 `#define REPROJECT_HISTORY_FOR_GUIDING 1` _[#if defined(GenerateLightSamplesCS)]_
- L59 #pragma `warning(disable:7203)`

#### Entry points (2)

- L286-603 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void GenerateLightSamplesCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FGenerateLightSamplesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/MegaLights/MegaLightsSampling.cpp:202) — Run one thread per sample and generate new light samples for tracing _[#if defined(GenerateLightSamplesCS)]_
- L612-637 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void ClearLightSamplesCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FClearLightSamplesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/MegaLights/MegaLightsSampling.cpp:328) — Clear data for empty tiles, which won't be processed by GenerateLightSamplesCS _[#if defined(ClearLightSamplesCS)]_

#### Global resources (textures / buffers / samplers) (12)

- L78 _resource_ `RWTexture2D<float> RWDownsampledSceneDepth;`
- L79 _resource_ `RWTexture2D<UNORM float3> RWDownsampledSceneWorldNormal;`
- L80 _resource_ `RWTexture2D<uint> RWLightSamples;`
- L81 _resource_ `RWTexture2D<uint> RWLightSampleRays;`
- L83 _resource_ `Texture2D<uint> PackedPixelDataTexture;`
- L84 _resource_ `Texture2D<uint2> EncodedHistoryScreenCoordTexture;`
- L85 _resource_ `Texture2D MegaLightsDepthHistory;`
- L89 _resource_ `Buffer<float> LightPowerHistoryRatioBuffer;`
- L91 _resource_ `StructuredBuffer<uint> DownsampledTileAllocator;`
- L92 _resource_ `StructuredBuffer<uint> DownsampledTileData;`
- L94 _resource_ `StructuredBuffer<uint> VisibleLightHashHistory;`
- L95 _resource_ `StructuredBuffer<uint> HiddenLightHashHistory;`

#### Global parameters (uniforms) (22)

- L62-64 _parameter_ `ADAPTIVE_LICM uint2 DownsampledViewMin;`
- L65 _parameter_ `uint2 DownsampledViewSize;`
- L66 _parameter_ `float MinSampleWeightEstimate;`
- L67 _parameter_ `uint2 NumSamplesPerPixel;`
- L68 _parameter_ `int UseIESProfiles;`
- L69 _parameter_ `int UseLightFunctionAtlas;`
- L70 _parameter_ `uint bGuideByHistory;`
- L71 _parameter_ `uint bMergeRays;`
- L72 _parameter_ `uint bSupportSoftShadows;`
- L73 _parameter_ `uint DebugVisualizeTraces;`
- L74 _parameter_ `uint DebugVisualizeLight;`
- L75 _parameter_ `uint DebugLightId;`
- L76 _parameter_ `float HairNonShadowedLightMaxTraceDistance;`
- L86 _parameter_ `float4 HistorySubPixelGridSizeAndInvSize;`
- L87 _parameter_ `uint2 HistoryScreenCoordDecodeShift;`
- L96 _parameter_ `uint2 HistoryVisibleLightHashViewMinInTiles;`
- L97 _parameter_ `uint2 HistoryVisibleLightHashViewSizeInTiles;`
- L99 _parameter_ `float LightHiddenPDFWeight;`
- L100 _parameter_ `float LightHiddenPDFWeightForHistoryMiss;`
- L102 _parameter_ `uint DownsampledTileDataStride;`
- L103 _parameter_ `float2 DownsampledBufferInvSize;`
- L115 _parameter_ `float TransmissionSampleWeight;`

#### groupshared (2)

- L279 _groupshared_ `groupshared int SharedGridCellLightCount[2];` _[#if defined(GenerateLightSamplesCS) && DEBUG_MODE]_
- L280 _groupshared_ `groupshared int SharedLightLoopIterationCount[2];` _[#if defined(GenerateLightSamplesCS) && DEBUG_MODE]_

#### Functions (5)

- L105-108 _function_ `uint2 GetSampleCoord(uint2 DownsampledScreenCoord, uint LightSampleX, uint LightSampleY)`
- L110-113 _function_ `uint2 GetSampleCoord(uint2 DownsampledScreenCoord, uint LightSampleIndex)`
- L117-212 _function_ `void SampleLight( uint2 ScreenCoord, float3 TranslatedWorldPosition, const FMegaLightsMaterial Material, uint VisibleLightHash[VISIBLE_LIGHT_HASH_SIZE], bool bHasValidHistory, uint ForwardLightIndex, FDeferredLightData LightData, FForwardLightData ForwardLightData, uint LightLightingChannelMask, inout FLightSampler LightSampler, inout FDebugContext DebugContext)`
- L214-243 _function_ `void SampleLocalLight( uint2 ScreenCoord, float3 TranslatedWorldPosition, const FMegaLightsMaterial Material, uint VisibleLightHash[VISIBLE_LIGHT_HASH_SIZE], bool bHasValidHistory, uint LocalLightIndex, inout FLightSampler LightSampler, inout FDebugContext DebugContext)`
- L245-274 _function_ `void SampleDirectionalLight( uint DirectionalLightIndex, uint2 ScreenCoord, float3 TranslatedWorldPosition, const FMegaLightsMaterial Material, uint VisibleLightHash[VISIBLE_LIGHT_HASH_SIZE], bool bHasValidHistory, inout FLightSampler LightSampler, inout FDebugContext DebugContext)`

### `Shaders/Private/MegaLights/MegaLightsSampling.ush` (Private)

- lines: 142; parse: all-branches

#### Macros (#define, 2)

- L6 `#define NUM_SAMPLES_1D NUM_SAMPLES_PER_VOXEL_1D` _[#if defined(NUM_SAMPLES_PER_VOXEL_1D)]_
- L10 `#define NUM_SAMPLES_1D NUM_SAMPLES_PER_PIXEL_1D` _[#if defined(NUM_SAMPLES_PER_PIXEL_1D)]_
- L3 #pragma `once`

#### Structs / classes (2)

- L13-18 _struct_ **`FCandidateLightSample`** `struct FCandidateLightSample`
  - L15 _member_ `uint LocalLightIndex;`
  - L16 _member_ `bool bLightWasVisible;`
  - L17 _member_ `float Weight;`
- L47-52 _struct_ **`FLightSampler`** `struct FLightSampler`
  - L49 _member_ `uint PackedSamples[NUM_SAMPLES_1D];`
  - L50 _member_ `float LightIndexRandom[NUM_SAMPLES_1D];`
  - L51 _member_ `float WeightSum;`

#### Global parameters (uniforms) (2)

- L81 _parameter_ `float DirectionalLightSampleRatio;`
- L82 _parameter_ `float DirectionalMinSampleClampingWeight;`

#### Functions (8)

- L20-27 _function_ `FCandidateLightSample InitCandidateLightSample()`
- L29-36 _function_ `uint PackCandidateLightSample(FCandidateLightSample LightSample)`
- L38-45 _function_ `FCandidateLightSample UnpackCandidateLightSample(uint PackedSample)`
- L54-66 _function_ `FLightSampler InitLightSamplerStratified(float RandomScalar)`
- L68-79 _function_ `void InitLightSamplerFromSequence(inout FLightSampler LightSampler, uint2 ScreenCoord, uint StateFrameIndex)`
- L84-115 _function_ `void AddLightSample(inout FLightSampler LightSampler, float SampleWeight, uint ForwardLightIndex, bool bWasVisibleInLastFrame, bool bRadialLight)`
- L118-136 _function_ `void PrintLightType(inout FDebugContext DebugContext, FDeferredLightData LightData)` _[#if DEBUG_MODE]_
- L139-142 _function_ `bool IsAreaLight(FDeferredLightData LightData)`

### `Shaders/Private/MegaLights/MegaLightsSamplingDefinitionsCommon.ush` (Private)

- lines: 20; parse: all-branches

#### Macros (#define, 6)

- L6 `#define ALLOW_SSS_MATERIAL_CHECKERBOARD_OVERRIDE 0`
- L10 `#define HAIR_BSDF_BACKLIT 0`
- L12 `#define USE_IES_PROFILE 1`
- L13 `#define USE_LIGHT_FUNCTION_ATLAS 1`
- L17 `#define USE_TRANSMISSION 1` _[#if INPUT_TYPE == 0]_
- L18 `#define SUBSTRATE_SSS_TRANSMISSION 1` _[#if INPUT_TYPE == 0]_
- L3 #pragma `once`

### `Shaders/Private/MegaLights/MegaLightsShading.usf` (Private)

- lines: 627; parse: all-branches
- includes: L25 `../Common.ush`, L26 `/Engine/Shared/MegaLightsDefinitions.h`, L58 `../BlueNoise.ush`, L59 `MegaLightsShading.ush`, L60 `../StochasticLighting/StochasticLightingCommon.ush`

#### Macros (#define, 23)

- L4 `#define TILE_TYPE TILE_MODE_EMPTY` _[#if !defined(TILE_TYPE)]_
- L8 `#define NUM_SAMPLES_PER_PIXEL_1D 1` _[#if !defined(NUM_SAMPLES_PER_PIXEL_1D)]_
- L9 `#define NUM_SAMPLES_PER_PIXEL_2D_X 1` _[#if !defined(NUM_SAMPLES_PER_PIXEL_1D)]_
- L10 `#define NUM_SAMPLES_PER_PIXEL_2D_Y 1` _[#if !defined(NUM_SAMPLES_PER_PIXEL_1D)]_
- L14 `#define ALLOW_SSS_MATERIAL_CHECKERBOARD_OVERRIDE 0`
- L16 `#define USE_IES_PROFILE 1`
- L17 `#define USE_LIGHT_FUNCTION_ATLAS 1`
- L21 `#define USE_TRANSMISSION 1` _[#if INPUT_TYPE == 0]_
- L22 `#define SUBSTRATE_SSS_TRANSMISSION 1` _[#if INPUT_TYPE == 0]_
- L30 `#define FORCE_SIMPLE_SHADING 1` _[#if TILE_TYPE == TILE_MODE_SIMPLE_SHADING \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT_TEXTURED \|\| TILE_TYPE == TILE_MODE_EMPTY]_
- L36 `#define SUBSTRATE_FASTPATH 1` _[#if SUBSTRATE_ENABLED && TILE_TYPE == TILE_MODE_SIMPLE_SHADING \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT_TEXTURED \|\| TILE_TYPE == TILE_MODE_EMPTY]_
- L37 `#define SUBSTRATE_SINGLEPATH 0` _[#if SUBSTRATE_ENABLED && TILE_TYPE == TILE_MODE_SIMPLE_SHADING \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT_TEXTURED \|\| TILE_TYPE == TILE_MODE_EMPTY]_
- L38 `#define SUBSTRATE_COMPLEXSPECIALPATH 0` _[#if SUBSTRATE_ENABLED && TILE_TYPE == TILE_MODE_SIMPLE_SHADING \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT_TEXTURED \|\| TILE_TYPE == TILE_MODE_EMPTY]_
- L40 `#define SUBSTRATE_FASTPATH 0` _[#if SUBSTRATE_ENABLED && !(TILE_TYPE == TILE_MODE_SIMPLE_SHADING \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT_TEXTURED \|\| TILE_TYPE == TILE_MODE_EMPTY) &&...]_
- L41 `#define SUBSTRATE_SINGLEPATH 1` _[#if SUBSTRATE_ENABLED && !(TILE_TYPE == TILE_MODE_SIMPLE_SHADING \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT_TEXTURED \|\| TILE_TYPE == TILE_MODE_EMPTY) &&...]_
- L42 `#define SUBSTRATE_COMPLEXSPECIALPATH 0` _[#if SUBSTRATE_ENABLED && !(TILE_TYPE == TILE_MODE_SIMPLE_SHADING \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT_TEXTURED \|\| TILE_TYPE == TILE_MODE_EMPTY) &&...]_
- L44 `#define SUBSTRATE_FASTPATH 0` _[#if SUBSTRATE_ENABLED && !(TILE_TYPE == TILE_MODE_SIMPLE_SHADING \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT_TEXTURED \|\| TILE_TYPE == TILE_MODE_EMPTY) &&...]_
- L45 `#define SUBSTRATE_SINGLEPATH 0` _[#if SUBSTRATE_ENABLED && !(TILE_TYPE == TILE_MODE_SIMPLE_SHADING \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT_TEXTURED \|\| TILE_TYPE == TILE_MODE_EMPTY) &&...]_
- L46 `#define SUBSTRATE_COMPLEXSPECIALPATH 0` _[#if SUBSTRATE_ENABLED && !(TILE_TYPE == TILE_MODE_SIMPLE_SHADING \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT_TEXTURED \|\| TILE_TYPE == TILE_MODE_EMPTY) &&...]_
- L48 `#define SUBSTRATE_FASTPATH 0` _[#if SUBSTRATE_ENABLED && !(TILE_TYPE == TILE_MODE_SIMPLE_SHADING \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT_TEXTURED \|\| TILE_TYPE == TILE_MODE_EMPTY) &&...]_
- L49 `#define SUBSTRATE_SINGLEPATH 0` _[#if SUBSTRATE_ENABLED && !(TILE_TYPE == TILE_MODE_SIMPLE_SHADING \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT_TEXTURED \|\| TILE_TYPE == TILE_MODE_EMPTY) &&...]_
- L50 `#define SUBSTRATE_COMPLEXSPECIALPATH 1` _[#if SUBSTRATE_ENABLED && !(TILE_TYPE == TILE_MODE_SIMPLE_SHADING \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT \|\| TILE_TYPE == TILE_MODE_SIMPLE_SHADING_RECT_TEXTURED \|\| TILE_TYPE == TILE_MODE_EMPTY) &&...]_
- L55 `#define SUBSTRATE_LOAD_FROM_MATERIALCONTAINER 0` _[#if SUBSTRATE_FASTPATH \|\| SUBSTRATE_SINGLEPATH]_
- L64 #pragma `warning(disable:7203)`

#### Entry points (2)

- L185-598 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void ShadeLightSamplesCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FShadeLightSamplesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/MegaLights/MegaLightsResolve.cpp:250) — Upsample light samples and apply all lights per pixel to affected tiles _[#if defined(ShadeLightSamplesCS)]_
- L607-625 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void ClearResolvedLightingCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FClearResolvedLightingCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/MegaLights/MegaLightsResolve.cpp:584) — Clear some data for empty tiles, which won't be processed by ShadeLightSamplesCS _[#if defined(ClearResolvedLightingCS)]_

#### Global resources (textures / buffers / samplers) (12)

- L67-69 _resource_ `ADAPTIVE_LICM RWTexture2D<float3> RWResolvedDiffuseLighting;`
- L70 _resource_ `RWTexture2D<float3> RWResolvedSpecularLighting;`
- L71 _resource_ `RWTexture2D<UNORM float> RWShadingConfidence;`
- L72 _resource_ `RWTexture2D<float3> RWOutputColor;`
- L78 _resource_ `Texture2D<float> DownsampledSceneDepth;`
- L79 _resource_ `Texture2D<UNORM float3> DownsampledSceneWorldNormal;`
- L82 _resource_ `StructuredBuffer<uint> TileAllocator;`
- L83 _resource_ `StructuredBuffer<uint> TileData;`
- L86 _resource_ `Texture2D<uint> LightSamples;`
- L87 _resource_ `Texture2D<uint> LightSampleRays;`
- L88 _resource_ `Texture2D<uint> HairTransmittanceMaskTexture;`
- L89 _resource_ `Texture2D<uint> PackedPixelDataTexture;`

#### Global parameters (uniforms) (17)

- L74 _parameter_ `int2 SampleViewMin;`
- L75 _parameter_ `int2 SampleViewSize;`
- L76 _parameter_ `uint2 DownsampledViewMin;`
- L77 _parameter_ `uint2 DownsampledViewSize;`
- L80 _parameter_ `float2 DownsampledBufferInvSize;`
- L84 _parameter_ `uint TileDataStride;`
- L91 _parameter_ `uint bSubPixelShading;`
- L92 _parameter_ `uint ShadingSampleIndex;`
- L93 _parameter_ `float MinSampleWeight;`
- L94 _parameter_ `float MaxShadingWeight;`
- L95 _parameter_ `float MaxShadingWeightForHiddenLight;`
- L96 _parameter_ `uint UseShadingConfidence;`
- L97 _parameter_ `uint ShadingPassIndex;`
- L98 _parameter_ `int UseIESProfiles;`
- L99 _parameter_ `int UseLightFunctionAtlas;`
- L100 _parameter_ `float TransmissionSampleWeight;`
- L101 _parameter_ `uint DebugLightId;`

#### Functions (4)

- L103-123 _function_ `bool FindNextLocalLightIndex(uint PackedLightSamples[NUM_SAMPLES_PER_PIXEL_1D], inout uint NextLocalLightIndex)`
- L125-163 _function_ `void AccumulateLightSample(uint PackedLightSamples[NUM_SAMPLES_PER_PIXEL_1D], uint LocalLightIndex, inout uint NextLocalLightIndex, inout float SampleWeightSum, inout float WeightRatioSum, inout uint ValidSampleMask, inout FDebugContext DebugContext)`
- L165-168 _function_ `bool IsValidDownsampledCoord(uint2 DownsampledScreenCoord)`
- L170-178 _function_ `float GetNormalWeight(float3 SceneWorldNormal, uint2 DownsampledScreenCoord)`

### `Shaders/Private/MegaLights/MegaLightsShading.ush` (Private)

- lines: 166; parse: first-branch (retry, +0 merged from all-branches pass)
- includes: L9 `MegaLights.ush`, L10 `MegaLightsMaterial.ush`, L11 `../Substrate/SubstrateDeferredLighting.ush`, L135 `../HairStrands/HairStrandsVisibilityCommon.ush` [INPUT_TYPE == INPUT_TYPE_HAIRSTRANDS], L136 `../HairStrands/HairStrandsVisibilityUtils.ush` [INPUT_TYPE == INPUT_TYPE_HAIRSTRANDS], L137 `../HairStrands/HairStrandsCommon.ush` [INPUT_TYPE == INPUT_TYPE_HAIRSTRANDS], L138 `../HairStrands/HairStrandsDeepTransmittanceCommon.ush` [INPUT_TYPE == INPUT_TYPE_HAIRSTRANDS], L139 `../HairStrands/HairStrandsDeepTransmittanceDualScattering.ush` [INPUT_TYPE == INPUT_TYPE_HAIRSTRANDS]

#### Macros (#define, 1)

- L7 `#define SUBSTRATE_STOCHASTIC_LIGHTING 0`
- L3 #pragma `once`

#### Functions (2)

- L13-121 _function_ `FDeferredLightingSplit GetMegaLightsSplitLighting( float3 TranslatedWorldPosition, float3 CameraVector, FMegaLightsMaterial Material, float AmbientOcclusion, int ForwardLightIndex, FDeferredLightData LightData, float4 LightAttenuation, float Dither, uint2 ScreenCoord, inout float SurfaceShadow)`
- L142-164 _function_ `FHairTransmittanceData GetTransmittanceDataFromTransmitttanceMask( FDeferredLightData LightData, FMegaLightsMaterial Material, FHairTransmittanceMask TransmittanceMask, float3 TranslatedWorldPosition, float3 CameraVector)` — Compute transmittance data from a transmittance mask _[#if INPUT_TYPE == INPUT_TYPE_HAIRSTRANDS]_

### `Shaders/Private/MegaLights/MegaLightsTileClassification.ush` (Private)

- lines: 21; parse: all-branches

#### Macros (#define, 7)

- L5 `#define MEGALIGHTS_TILE_BITMASK_SIMPLE 0x01`
- L6 `#define MEGALIGHTS_TILE_BITMASK_SINGLE 0x02`
- L7 `#define MEGALIGHTS_TILE_BITMASK_COMPLEX 0x04`
- L8 `#define MEGALIGHTS_TILE_BITMASK_COMPLEX_SPECIAL 0x08`
- L9 `#define MEGALIGHTS_TILE_BITMASK_RECT_LIGHT 0x10`
- L10 `#define MEGALIGHTS_TILE_BITMASK_TEXTURED_RECT_LIGHT 0x20`
- L12 `#define MEGALIGHTS_TILE_BITMASK_FAST_CLEAR_MASK (MEGALIGHTS_TILE_BITMASK_SIMPLE \| MEGALIGHTS_TILE_BITMASK_SINGLE \| MEGALIGHTS_TILE_BITMASK_COMPLEX \| MEGALIGHTS_TILE_BITMASK_COMPLEX_SPECIAL)` (4 lines)
- L3 #pragma `once`

#### Functions (1)

- L17-20 _function_ `bool IsFastClearTile(uint TileBitmask)`

### `Shaders/Private/MegaLights/MegaLightsVSMMarking.usf` (Private)

- lines: 65; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../SceneTexturesCommon.ush`, L5 `../LightData.ush`, L6 `MegaLights.ush`, L7 `MegaLightsRayTracing.ush`, L8 `../VirtualShadowMaps/VirtualShadowMapPageMarking.ush`

#### Entry points (1)

- L18-64 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void VirtualShadowMapMarkLightSamplesCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FVirtualShadowMapMarkLightSamplesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/MegaLights/MegaLightsRayTracing.cpp:1269)

#### Global resources (textures / buffers / samplers) (5)

- L10 _resource_ `RWTexture2D<uint> RWLightSamples;`
- L11 _resource_ `RWTexture2D<uint> RWLightSampleRays;`
- L13 _resource_ `Buffer<uint> CompactedTraceTexelAllocator;`
- L14 _resource_ `Buffer<uint> CompactedTraceTexelData;`
- L15 _resource_ `Texture2D<float> DownsampledSceneDepth;`

### `Shaders/Private/MegaLights/MegaLightsVSMTracing.usf` (Private)

- lines: 162; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../BlueNoise.ush`, L5 `../SceneTexturesCommon.ush`, L6 `../LightData.ush`, L7 `../VirtualShadowMaps/VirtualShadowMapProjectionCommon.ush`, L8 `../VirtualShadowMaps/VirtualShadowMapProjectionSpot.ush`, L9 `../VirtualShadowMaps/VirtualShadowMapProjectionDirectional.ush`, L10 `../VirtualShadowMaps/VirtualShadowMapScreenRayTrace.ush`, L11 `MegaLights.ush`, L12 `MegaLightsRayTracing.ush`

#### Entry points (1)

- L22-161 _entry_ `SCHEDULER_MIN_PRESSURE [numthreads(THREADGROUP_SIZE, 1, 1)] void VirtualShadowMapTraceLightSamplesCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FVirtualShadowMapTraceLightSamplesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/MegaLights/MegaLightsRayTracing.cpp:1233)

#### Global resources (textures / buffers / samplers) (6)

- L14 _resource_ `RWTexture2D<uint> RWLightSamples;`
- L15 _resource_ `RWTexture2D<uint> RWLightSampleRays;`
- L17 _resource_ `Buffer<uint> CompactedTraceTexelAllocator;`
- L18 _resource_ `Buffer<uint> CompactedTraceTexelData;`
- L19 _resource_ `Texture2D<float> DownsampledSceneDepth;`
- L20 _resource_ `Texture2D<UNORM float3> DownsampledSceneWorldNormal;`

### `Shaders/Private/MegaLights/MegaLightsVisibility.ush` (Private)

- lines: 71; parse: all-branches

#### Macros (#define, 2)

- L6 `#define VISIBLE_LIGHT_HASH_SIZE 4`
- L7 `#define HIDDEN_LIGHT_HASH_SIZE 2`
- L3 #pragma `once`

#### Functions (4)

- L9-25 _function_ `bool IsLightVisible(uint VisibleLightHash[VISIBLE_LIGHT_HASH_SIZE], uint LightIndex)`
- L27-39 _function_ `void MarkVisibleLight(inout uint VisibleLightHash[VISIBLE_LIGHT_HASH_SIZE], uint LightHash)`
- L41-57 _function_ `bool IsLightHidden(StructuredBuffer<uint> HiddenLightHashBuffer, uint LinearTileCoord, uint LightIndex)`
- L59-71 _function_ `void MarkHiddenLight(inout uint HiddenLightHash[HIDDEN_LIGHT_HASH_SIZE], uint LightHash)`

### `Shaders/Private/MegaLights/MegaLightsVisibleLightHash.usf` (Private)

- lines: 229; parse: all-branches
- includes: L3 `../Common.ush`, L4 `MegaLightsTileClassification.ush`, L5 `MegaLights.ush`, L6 `MegaLightsVolume.ush`, L7 `MegaLightsVisibility.ush`

#### Entry points (2)

- L29-137 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void VisibleLightHashCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FVisibleLightHashCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/MegaLights/MegaLightsResolve.cpp:309) — Run one group per visible light list tile in order to prepare visible light list for light guiding in the next frame _[#if defined(VisibleLightHashCS)]_
- L152-227 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, THREADGROUP_SIZE)] void VolumeVisibleLightHashCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FVolumeVisibleLightHashCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/MegaLights/MegaLightsResolve.cpp:498) — Run one thread per visible light list tile in order to prepare visible light list for light guiding in the next frame _[#if defined(VolumeVisibleLightHashCS)]_

#### Global resources (textures / buffers / samplers) (6)

- L9 _resource_ `RWStructuredBuffer<uint> RWVisibleLightHash;`
- L10 _resource_ `RWStructuredBuffer<uint> RWHiddenLightHash;`
- L14 _resource_ `Texture2D<uint> MegaLightsTileBitmask;` _[#if defined(VisibleLightHashCS)]_
- L15 _resource_ `Texture2D<uint> LightSamples;` _[#if defined(VisibleLightHashCS)]_
- L16 _resource_ `Texture2D<uint> LightSampleRays;` _[#if defined(VisibleLightHashCS)]_
- L143 _resource_ `Texture3D<uint> LightSamples;` _[#if defined(VolumeVisibleLightHashCS)]_

#### Global parameters (uniforms) (7)

- L18 _parameter_ `uint2 VisibleLightHashViewMinInTiles;` _[#if defined(VisibleLightHashCS)]_
- L19 _parameter_ `uint2 VisibleLightHashViewSizeInTiles;` _[#if defined(VisibleLightHashCS)]_
- L20 _parameter_ `uint2 SampleViewMin;` _[#if defined(VisibleLightHashCS)]_
- L21 _parameter_ `uint2 SampleViewSize;` _[#if defined(VisibleLightHashCS)]_
- L145 _parameter_ `uint3 VolumeVisibleLightHashTileSize;` _[#if defined(VolumeVisibleLightHashCS)]_
- L146 _parameter_ `uint3 VolumeVisibleLightHashViewSizeInTiles;` _[#if defined(VolumeVisibleLightHashCS)]_
- L147 _parameter_ `uint3 VolumeSampleViewSize;` _[#if defined(VolumeVisibleLightHashCS)]_

#### groupshared (2)

- L23 _groupshared_ `groupshared uint SharedVisibleLightHash[VISIBLE_LIGHT_HASH_SIZE];` _[#if defined(VisibleLightHashCS)]_
- L24 _groupshared_ `groupshared uint SharedHiddenLightHash[HIDDEN_LIGHT_HASH_SIZE];` _[#if defined(VisibleLightHashCS)]_

### `Shaders/Private/MegaLights/MegaLightsVisualize.usf` (Private)

- lines: 197; parse: all-branches
- includes: L3 `../Common.ush`, L4 `/Engine/Shared/MegaLightsDefinitions.h`, L6 `MegaLightsMaterial.ush`, L7 `MegaLightsDenoiser.ush`, L8 `../StochasticLighting/StochasticLightingVisualize.ush`, L9 `../Visualization.ush`, L10 `../Lumen/LumenTracingCommon.ush`, L11 `../ReflectionEnvironmentShared.ush`, L12 `../StochasticLighting/StochasticLightingCommon.ush`

#### Macros (#define, 1)

- L5 `#define INPUT_TYPE 0`

#### Entry points (1)

- L31-197 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void MegaLightsVisualizeCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FMegaLightsVisualizeCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/MegaLights/MegaLightsVisualize.cpp:154)

#### Global resources (textures / buffers / samplers) (6)

- L23 _resource_ `Texture2D<UNORM float4> VisualizeSpatialFilterTexture;`
- L24 _resource_ `Texture2D<UNORM float4> VisualizeSpatialFilterTexture2;`
- L25 _resource_ `Texture2D<UNORM float4> VisualizeTemporalFilterTexture;`
- L26 _resource_ `Texture2D<UNORM float> ShadingConfidenceTexture;`
- L27 _resource_ `Texture2D<uint> NumFramesAccumulatedTexture;`
- L29 _resource_ `RWTexture2D<float3> RWSceneColor;`

#### Global parameters (uniforms) (7)

- L14 _parameter_ `uint VisualizeMode;`
- L15 _parameter_ `uint2 InputViewSize;`
- L16 _parameter_ `uint2 InputViewOffset;`
- L17 _parameter_ `uint2 OutputViewSize;`
- L18 _parameter_ `uint2 OutputViewOffset;`
- L20 _parameter_ `float TemporalMaxFramesAccumulated;`
- L21 _parameter_ `float HistorySpatialStdDevThreshold;`

### `Shaders/Private/MegaLights/MegaLightsVisualizeHardwareRayTracing.usf` (Private)

- lines: 258; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../MonteCarlo.ush`, L5 `/Engine/Shared/RayTracingTypes.h`, L6 `/Engine/Shared/MegaLightsDefinitions.h`, L7 `../RayTracing/RayTracingCommon.ush`, L8 `../Lumen/LumenHardwareRayTracingPayloadCommon.ush`, L9 `../Lumen/LumenHardwareRayTracingCommon.ush`, L11 `../PathTracing/Utilities/PathTracingRandomSequence.ush` [HAIR_VOXEL_TRACES], L12 `../HairStrands/HairStrandsRaytracing.ush` [HAIR_VOXEL_TRACES], L15 `MegaLightsMaterial.ush`, L16 `../StochasticLighting/StochasticLightingVisualize.ush`, L17 `../Visualization.ush`

#### Macros (#define, 1)

- L14 `#define INPUT_TYPE 0`

#### Entry points (1)

- L54-258 _entry_ `LUMEN_HARDWARE_RAY_TRACING_ENTRY(MegaLightsVisualizeHardwareRayTracing)` — stage: **raygeneration\|compute(inline)**

#### Global resources (textures / buffers / samplers) (7)

- L20 _resource_ `StructuredBuffer<FHitGroupRootConstants> HitGroupData;` _[#if LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L21 _resource_ `StructuredBuffer<FRayTracingSceneMetadataRecord> RayTracingSceneMetadata;` _[#if LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L22 _resource_ `RWStructuredBuffer<uint> RWInstanceHitCountBuffer;` _[#if LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L46 _resource_ `RaytracingAccelerationStructure TLAS;`
- L47 _resource_ `RaytracingAccelerationStructure FarFieldTLAS;`
- L50 _resource_ `Texture2D OpaqueOnlyDepthTexture;` — Depth texture containing only opaque objects (no single layer water or depth-writing translucency)
- L52 _resource_ `RWTexture2D<float3> RWSceneColor;`

#### Global parameters (uniforms) (18)

- L25 _parameter_ `uint VisualizeMode;`
- L26 _parameter_ `uint2 InputViewSize;`
- L27 _parameter_ `uint2 InputViewOffset;`
- L28 _parameter_ `uint2 OutputViewSize;`
- L29 _parameter_ `uint2 OutputViewOffset;`
- L31 _parameter_ `uint MegaLightsStateFrameIndex;`
- L32 _parameter_ `float ShadowCasterQualityMissingProxyDistanceThreshold;`
- L33 _parameter_ `float ShadowCasterQualityPoorQualityDistanceThreshold;`
- L35 _parameter_ `float NearFieldSceneRadius;`
- L36 _parameter_ `float NearFieldMaxTraceDistance;`
- L37 _parameter_ `float NearFieldMaxTraceDistanceDitherScale;`
- L38 _parameter_ `float FarFieldBias;`
- L39 _parameter_ `float FarFieldMaxTraceDistance;`
- L41 _parameter_ `uint UseFarField;`
- L42 _parameter_ `uint UseHairVoxelTraces;`
- L43 _parameter_ `uint ForceTwoSided;`
- L44 _parameter_ `uint MaxTraversalIterations;`
- L45 _parameter_ `uint MeshSectionVisibilityTest;`

### `Shaders/Private/MegaLights/MegaLightsVolume.ush` (Private)

- lines: 345; parse: all-branches
- includes: L5 `MegaLights.ush`, L6 `../LightFunctionAtlas/LightFunctionAtlasCommon.usf`, L7 `../Nanite/NaniteHZBCull.ush`, L8 `../TranslucencyVolumeInjectionCommon.ush`
- L3 #pragma `once`

#### Global parameters (uniforms) (19)

- L10 _parameter_ `uint VolumeDownsampleFactorMultShift;`
- L52 _parameter_ `uint3 VolumeViewSize;`
- L53 _parameter_ `float3 VolumeInvBufferSize;`
- L54 _parameter_ `float3 MegaLightsVolumeZParams;`
- L71 _parameter_ `float LightSoftFading;`
- L72 _parameter_ `float4x4 UnjitteredTranslatedWorldToClip;`
- L75 _parameter_ `uint3 ResampleVolumeViewSize;` _[#if RESAMPLE_VOLUME]_
- L76 _parameter_ `float3 ResampleVolumeInvBufferSize;` _[#if RESAMPLE_VOLUME]_
- L77 _parameter_ `float3 ResampleVolumeZParams;` _[#if RESAMPLE_VOLUME]_
- L82 _parameter_ `uint TranslucencyVolumeCascadeIndex;` _[#if TRANSLUCENCY_LIGHTING_VOLUME]_
- L83 _parameter_ `float TranslucencyVolumeInvResolution;` _[#if TRANSLUCENCY_LIGHTING_VOLUME]_
- L100 _parameter_ `float4x4 UnjitteredClipToTranslatedWorld;` _[#if !(TRANSLUCENCY_LIGHTING_VOLUME)]_
- L101 _parameter_ `float4x4 UnjitteredPrevTranslatedWorldToClip;` _[#if !(TRANSLUCENCY_LIGHTING_VOLUME)]_
- L102 _parameter_ `uint MegaLightsVolumePixelSize;` _[#if !(TRANSLUCENCY_LIGHTING_VOLUME)]_
- L128 _parameter_ `float VolumePhaseG;`
- L129 _parameter_ `uint UseLightFunctionAtlas;`
- L130 _parameter_ `uint UseIESProfiles;`
- L241 _parameter_ `uint UseHZBOcclusionTest;`
- L312 _parameter_ `int VolumeDebugSliceIndex;`

#### Functions (16)

- L15-33 _function_ `uint3 GetSampleVoxelCoordJitter(uint3 DownsampledVolumeCoord)` — Returns sample jitter offset in the range [0, VOLUME_DOWNSAMPLE_FACTOR - 1]
- L35-38 _function_ `uint3 DownsampledVolumeCoordToVolumeCoord(uint3 DownsampledVolumeCoord)`
- L40-43 _function_ `uint3 VolumeCoordToDownsampledVolumeCoord(uint3 VolumeCoord)`
- L45-50 _function_ `uint2 VolumeCoordToNoiseCoord(uint3 VolumeCoord)`
- L56-59 _function_ `float ComputeMegaLightsDepthFromZSlice(float ZSlice)`
- L61-64 _function_ `float ComputeMegaLightsZSliceFromDepth(float SliceDepth)`
- L66-69 _function_ `float ComputeMegaLightsNormalizedZSliceFromDepth(float SceneDepth)`
- L85-89 _function_ `float3 ComputeCellTranslatedWorldPosition(uint3 GridCoordinate, float3 CellOffset, out float SceneDepth)` _[#if TRANSLUCENCY_LIGHTING_VOLUME]_
- L91-96 _function_ `float3 ComputeTranslatedWorldPointCellCoord(float3 TranslatedWorldPosition)` _[#if TRANSLUCENCY_LIGHTING_VOLUME]_
- L104-114 _function_ `float3 ComputeCellTranslatedWorldPosition(uint3 GridCoordinate, float3 CellOffset, out float SceneDepth)` _[#if !(TRANSLUCENCY_LIGHTING_VOLUME)]_
- L116-124 _function_ `float3 ComputeTranslatedWorldPointCellCoord(float3 TranslatedWorldPosition)` _[#if !(TRANSLUCENCY_LIGHTING_VOLUME)]_
- L132-239 _function_ `float3 GetMegaLightsVolumeLighting( float3 TranslatedWorldPosition, float3 CameraVector, float DistanceBiasSqr, float LightVolumetricSoftFadeDistance, int ForwardLightIndex, FDeferredLightData LightData, float VolumetricScatteringIntensity, bool bUnifiedVolumeSampling, out float3 OutL)`
- L245-269 _function_ `FScreenRect ComputeFroxelCullRect(uint3 GridCoordinate, float MinTileZ, float MaxTileZ, float FootprintMargin)` _[#if !TRANSLUCENCY_LIGHTING_VOLUME]_
- L271-284 _function_ `bool IsFroxelVisible(uint3 GridCoordinate, float FootprintMargin)` _[#if !TRANSLUCENCY_LIGHTING_VOLUME]_
- L288-310 _function_ `void GetVolumeDistanceBiasSqrAndSoftFadeDistance( float3 TranslatedWorldPosition, uint3 CellCoord, float3 OffsetInCell, float DistanceBiasScale, float SoftFadeDistanceScale, out float OutDistanceBiasSqr, out float OutLightVolumetricSoftFadeDistance)`
- L314-345 _function_ `FDebugContext InitVolumeDebugContext(uint3 VolumeCoord, bool bDownsampled, float2 StartPos)`

### `Shaders/Private/MegaLights/MegaLightsVolumeHardwareRayTracing.usf` (Private)

- lines: 147; parse: all-branches
- includes: L3 `/Engine/Shared/RayTracingTypes.h`, L4 `../Common.ush`, L5 `../BlueNoise.ush`, L6 `../RayTracing/RayTracingCommon.ush`, L7 `MegaLights.ush`, L8 `MegaLightsVolume.ush`, L9 `MegaLightsRayTracing.ush`, L10 `../Lumen/LumenHardwareRayTracingPayloadCommon.ush`, L11 `../Lumen/LumenHardwareRayTracingCommon.ush`

#### Entry points (1)

- L39-147 _entry_ `RAY_TRACING_ENTRY_RAYGEN_OR_INLINE(VolumeHardwareRayTraceLightSamples)` — stage: **raygeneration\|compute(inline)**

#### Global resources (textures / buffers / samplers) (8)

- L19 _resource_ `RaytracingAccelerationStructure TLAS;`
- L20 _resource_ `RaytracingAccelerationStructure FarFieldTLAS;`
- L29 _resource_ `StructuredBuffer<FHitGroupRootConstants> HitGroupData;` _[#if LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L30 _resource_ `StructuredBuffer<FRayTracingSceneMetadataRecord> RayTracingSceneMetadata;` _[#if LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L31 _resource_ `RWStructuredBuffer<uint> RWInstanceHitCountBuffer;` _[#if LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L34 _resource_ `RWTexture3D<uint> RWVolumeLightSamples;`
- L36 _resource_ `Buffer<uint> CompactedTraceTexelData;`
- L37 _resource_ `Buffer<uint> CompactedTraceTexelAllocator;`

#### Global parameters (uniforms) (11)

- L13 _parameter_ `float RayTracingBias;`
- L14 _parameter_ `float RayTracingNormalBias;`
- L15 _parameter_ `uint DebugVisualizeTraces;`
- L16 _parameter_ `float3 VolumeFrameJitterOffset;`
- L17 _parameter_ `uint MaxTraversalIterations;`
- L18 _parameter_ `uint MeshSectionVisibilityTest;`
- L22 _parameter_ `float NearFieldSceneRadius;`
- L23 _parameter_ `float NearFieldMaxTraceDistance;`
- L24 _parameter_ `float NearFieldMaxTraceDistanceDitherScale;`
- L25 _parameter_ `float FarFieldBias;`
- L26 _parameter_ `float FarFieldMaxTraceDistance;`

### `Shaders/Private/MegaLights/MegaLightsVolumeRayTracing.usf` (Private)

- lines: 197; parse: all-branches
- includes: L3 `../Common.ush`, L5 `../BlueNoise.ush`, L6 `../DistanceField/GlobalDistanceFieldShared.ush`, L7 `../DistanceField/GlobalDistanceFieldUtils.ush`, L8 `MegaLights.ush`, L9 `MegaLightsRayTracing.ush`, L10 `MegaLightsVolume.ush`

#### Macros (#define, 1)

- L4 `#define DISTANCE_FIELD_IN_VIEW_UB 1`

#### Entry points (2)

- L34-131 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, THREADGROUP_SIZE)] void VolumeCompactLightSampleTracesCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FVolumeCompactLightSampleTracesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/MegaLights/MegaLightsRayTracing.cpp:753) _[#if defined(VolumeCompactLightSampleTracesCS)]_
- L142-195 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void VolumeSoftwareRayTraceLightSamplesCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FVolumeSoftwareRayTraceLightSamplesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/MegaLights/MegaLightsRayTracing.cpp:1126) _[#if defined(VolumeSoftwareRayTraceLightSamplesCS)]_

#### Global resources (textures / buffers / samplers) (6)

- L15 _resource_ `Texture3D<uint> VolumeLightSampleRays;`
- L17 _resource_ `RWBuffer<uint> RWCompactedTraceTexelData;`
- L18 _resource_ `RWBuffer<uint> RWCompactedTraceTexelAllocator;`
- L135 _resource_ `RWTexture3D<uint> RWVolumeLightSamples;`
- L137 _resource_ `Buffer<uint> CompactedTraceTexelData;`
- L138 _resource_ `Buffer<uint> CompactedTraceTexelAllocator;`

#### Global parameters (uniforms) (3)

- L12 _parameter_ `uint DebugVisualizeTraces;`
- L13 _parameter_ `uint3 VolumeSampleViewSize;`
- L14 _parameter_ `float3 VolumeFrameJitterOffset;`

#### groupshared (4)

- L22 _groupshared_ `groupshared uint SharedGlobalTraceTexelStartOffset;` _[#if defined(VolumeCompactLightSampleTracesCS)]_
- L25 _groupshared_ `groupshared uint SharedGroupSum;` _[#if defined(VolumeCompactLightSampleTracesCS) && WAVE_OP_WAVE_SIZE > 0]_
- L27 _groupshared_ `groupshared uint SharedTraceTexelAllocator;` _[#if defined(VolumeCompactLightSampleTracesCS) && !(WAVE_OP_WAVE_SIZE > 0)]_
- L28 _groupshared_ `groupshared uint SharedTraceTexels[THREADGROUP_SIZE * THREADGROUP_SIZE * THREADGROUP_SIZE];` _[#if defined(VolumeCompactLightSampleTracesCS) && !(WAVE_OP_WAVE_SIZE > 0)]_

#### Top-level macro invocations (1)

- L32 _macro_call_ `WAVESIZE(WAVE_OP_WAVE_SIZE)` _[#if defined(VolumeCompactLightSampleTracesCS) && COMPILER_SUPPORTS_WAVE_SIZE && WAVE_OP_WAVE_SIZE > 0]_

### `Shaders/Private/MegaLights/MegaLightsVolumeSampling.usf` (Private)

- lines: 486; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../BlueNoise.ush`, L5 `MegaLights.ush`, L6 `MegaLightsVolume.ush`, L7 `MegaLightsRayTracing.ush`, L8 `MegaLightsSampling.ush`, L9 `MegaLightsEstimateLight.ush`, L10 `MegaLightsVisibility.ush`

#### Macros (#define, 1)

- L222 `#define REPROJECT_HISTORY_FOR_GUIDING (!TRANSLUCENCY_LIGHTING_VOLUME)`

#### Entry points (1)

- L186-485 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, THREADGROUP_SIZE)] void VolumeGenerateLightSamplesCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FVolumeGenerateLightSamplesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/MegaLights/MegaLightsSampling.cpp:279) — Run one thread per sample and generate new light samples for tracing

#### Global resources (textures / buffers / samplers) (5)

- L31 _resource_ `StructuredBuffer<uint> VolumeVisibleLightHashHistory;`
- L32 _resource_ `StructuredBuffer<uint> VolumeHiddenLightHashHistory;`
- L34 _resource_ `Buffer<float> LightPowerHistoryRatioBuffer;`
- L36 _resource_ `RWTexture3D<uint> RWVolumeLightSamples;`
- L37 _resource_ `RWTexture3D<uint> RWVolumeLightSampleRays;`

#### Global parameters (uniforms) (16)

- L12 _parameter_ `uint DebugVisualizeTraces;`
- L13 _parameter_ `float3 VolumeFrameJitterOffset;`
- L14 _parameter_ `uint3 NumSamplesPerVoxel;`
- L15 _parameter_ `float VolumeMinSampleWeight;`
- L16 _parameter_ `float MinSampleWeightEstimate;`
- L17 _parameter_ `uint3 DownsampledVolumeViewSize;`
- L18 _parameter_ `float VolumeInverseSquaredLightDistanceBiasScale;`
- L19 _parameter_ `uint DebugVisualizeLight;`
- L20 _parameter_ `uint DebugLightId;`
- L22 _parameter_ `float LightHiddenPDFWeight;`
- L23 _parameter_ `float LightHiddenPDFWeightForHistoryMiss;`
- L25 _parameter_ `uint IsUnifiedVolume;`
- L26 _parameter_ `int bGuideByHistory;`
- L27 _parameter_ `uint bMergeRays;`
- L29 _parameter_ `uint3 VolumeVisibleLightHashTileSize;`
- L30 _parameter_ `uint3 HistoryVolumeVisibleLightHashViewSizeInTiles;`

#### Functions (4)

- L39-42 _function_ `uint3 GetSampleCoord(uint3 DownsampledVolumeCoord, uint LightSampleIndex)`
- L44-110 _function_ `void SampleLight( float3 TranslatedWorldPosition, float3 CameraVector, float DistanceBiasSqr, float LightVolumetricSoftFadeDistance, uint VisibleLightHash[VISIBLE_LIGHT_HASH_SIZE], bool bHasValidHistory, uint ForwardLightIndex, uint LightSceneId, FDeferredLightData LightData, float VolumetricScatteringIntensity, int PrevForwardLightIndex, inout FLightSampler LightSampler, inout FDebugContext DebugContext)`
- L112-146 _function_ `void SampleLocalLight( float3 TranslatedWorldPosition, float3 CameraVector, float DistanceBiasSqr, float LightVolumetricSoftFadeDistance, uint VisibleLightHash[VISIBLE_LIGHT_HASH_SIZE], bool bHasValidHistory, uint LocalLightIndex, inout FLightSampler LightSampler, inout FDebugContext DebugContext)`
- L148-181 _function_ `void SampleDirectionalLight( uint DirectionalLightIndex, float3 TranslatedWorldPosition, float3 CameraVector, float DistanceBiasSqr, float LightVolumetricSoftFadeDistance, uint VisibleLightHash[VISIBLE_LIGHT_HASH_SIZE], bool bHasValidHistory, inout FLightSampler LightSampler, inout FDebugContext DebugContext)`

### `Shaders/Private/MegaLights/MegaLightsVolumeShading.usf` (Private)

- lines: 408; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../SHCommon.ush`, L5 `../BlueNoise.ush`, L6 `../ComputeShaderUtils.ush`, L7 `MegaLights.ush`, L8 `MegaLightsVolume.ush`, L9 `../StochasticLighting/StochasticLightingUpsample.ush`

#### Entry points (1)

- L115-407 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, THREADGROUP_SIZE)] void VolumeShadeLightSamplesCS( uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupId : SV_GroupID, uint GroupIndex : SV_GroupIndex)` — stage: **compute** — C++: `FVolumeShadeLightSamplesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/MegaLights/MegaLightsResolve.cpp:435) — Upsample light samples and apply all lights per voxel

#### Global resources (textures / buffers / samplers) (6)

- L19 _resource_ `Texture3D<uint> VolumeLightSamples;`
- L22 _resource_ `RWTexture3D<float4> RWTranslucencyVolumeResolvedLightingAmbient;` _[#if TRANSLUCENCY_LIGHTING_VOLUME]_
- L23 _resource_ `RWTexture3D<float4> RWTranslucencyVolumeResolvedLightingDirectional;` _[#if TRANSLUCENCY_LIGHTING_VOLUME]_
- L25 _resource_ `RWTexture3D<float3> RWVolumeResolvedLighting;` _[#if !(TRANSLUCENCY_LIGHTING_VOLUME)]_
- L32 _resource_ `StructuredBuffer<uint> VoxelAllocator;` _[#if INDIRECT_VOXEL_DISPATCH]_
- L33 _resource_ `StructuredBuffer<uint> VoxelData;` _[#if INDIRECT_VOXEL_DISPATCH]_

#### Global parameters (uniforms) (10)

- L11 _parameter_ `float VolumeMinSampleWeight;`
- L12 _parameter_ `float MaxShadingWeight;`
- L13 _parameter_ `float MaxShadingWeightForHiddenLight;`
- L14 _parameter_ `float3 VolumeFrameJitterOffset;`
- L15 _parameter_ `float VolumeInverseSquaredLightDistanceBiasScale;`
- L16 _parameter_ `uint3 VolumeSampleViewSize;`
- L17 _parameter_ `uint3 DownsampledVolumeViewSize;`
- L18 _parameter_ `uint3 NumSamplesPerVoxel;`
- L28 _parameter_ `uint DebugLightId;`
- L29 _parameter_ `uint ShadingPassIndex;`

#### Functions (3)

- L36-47 _function_ `void LoadPackedLightSamples(inout uint PackedLightSamples[NUM_SAMPLES_PER_VOXEL_1D], int3 DownsampledVolumeCoord)`
- L49-68 _function_ `void AccumulateLightSample(uint PackedLightSamples[NUM_SAMPLES_PER_VOXEL_1D], inout uint NextLocalLightIndex)`
- L70-110 _function_ `void AccumulateLightSample(uint PackedLightSamples[NUM_SAMPLES_PER_VOXEL_1D], uint LocalLightIndex, float UpsampleWeight, inout uint NextLocalLightIndex, inout float SampleWeightSum)`
