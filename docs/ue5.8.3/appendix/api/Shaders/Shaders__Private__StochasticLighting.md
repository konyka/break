# Shaders / Shaders/Private/StochasticLighting

- files: 5; lines: 1557
- record kinds: cpp_binding=1, define=22, entry=1, function=33, groupshared=6, include=11, member=10, method=30, parameter=25, resource=21, struct=5

### `Shaders/Private/StochasticLighting/StochasticLightingCommon.ush` (Private)

- lines: 240; parse: all-branches
- includes: L4 `../Common.ush`

#### Macros (#define, 3)

- L6 `#define LUMEN_INVALID_PACKED_PIXEL_DATA 0x30`
- L7 `#define MEGALIGHTS_INVALID_PACKED_PIXEL_DATA 0x30`
- L189 `#define INVALID_LIGHTING half3(65024.0, 65024.0, 64512.0)`
- L2 #pragma `once`

#### Structs / classes (3)

- L12-17 _struct_ **`FNormalAndShadingInfo`** `struct FNormalAndShadingInfo` — Used for storing normal and shading info history data and used by: * LumenScreenProbeGather * MegaLightDenoiserTemporal
  - L14 _member_ `float3 Normal;`
  - L15 _member_ `bool bIsHair;`
  - L16 _member_ `bool bHasBackfaceDiffuse;`
- L56-117 _struct_ **`FLumenPackedPixelData`** `struct FLumenPackedPixelData`
  - L58 _member_ `uint Packed;`
  - L60 _method_ `void SetHistorySampleValidity(bool4 bSampleValid)`
  - L68 _method_ `bool4 GetHistorySampleValidity()`
  - L78 _method_ `bool AnyHistoryValid()`
  - L83 _method_ `void SetStochasticSampleOffset(uint2 Offset, bool bCanReconstruct)`
  - L93 _method_ `uint2 GetStochasticSampleOffset()`
  - L98 _method_ `bool HasValidStochasticSample()`
  - L103 _method_ `void SetHasBackfaceDiffuse(bool bBackfaceDiffuse)`
  - L108 _method_ `bool HasBackfaceDiffuse()`
  - L113 _method_ `bool IsValid()`
- L119-186 _struct_ **`FMegaLightsPackedPixelData`** `struct FMegaLightsPackedPixelData`
  - L121 _member_ `uint Packed;`
  - L123 _method_ `void SetHistorySampleValidity(bool4 bSampleValid)`
  - L131 _method_ `bool4 GetHistorySampleValidity()`
  - L141 _method_ `bool AnyHistoryValid()`
  - L146 _method_ `void SetStochasticSampleOffset(uint2 Offset, bool bCanReconstruct)`
  - L156 _method_ `uint2 GetStochasticSampleOffset()`
  - L161 _method_ `int2 GetStochasticSampleOffset(int2 SampleOffsets[4])`
  - L167 _method_ `bool HasValidStochasticSample()`
  - L172 _method_ `void SetBicubicFootprintValid(bool bAnyValid)`
  - L177 _method_ `bool IsBicubicFootprintValid()`
  - L182 _method_ `bool IsValid()`

#### Functions (10)

- L19-28 _function_ `float4 PackNormalAndShadingInfo(FNormalAndShadingInfo In)`
- L30-40 _function_ `FNormalAndShadingInfo UnpackNormalAndShadingInfo(float4 In)`
- L42-46 _function_ `uint2 EncodeHistoryScreenCoord(float2 HistoryScreenCoord, float2 SubPixelGridSize)`
- L48-54 _function_ `float4 DecodeHistoryScreenCoord(uint2 EncodeCoord, uint2 HistoryScreenCoordShift, float2 InvSubPixelGridSize)`
- L191-194 _function_ `bool IsLightingValid(half3 V)`
- L196-204 _function_ `half3 LumenRGBToYCoCg(half3 RGB)`
- L206-218 _function_ `half3 LumenYCoCgToRGB(half3 YCoCg)`
- L222-226 _function_ `float GetSpecularDominantDirFactor(float Roughness)` — [Moving Frostbite to Physically Based Rendering 3.0] Approximates factor in Lerp(N, R, factor) = dominant direction of a GGX lobe
- L229-234 _function_ `float GetSpecularLobeHalfAngle(float Roughness)` — [Moving Frostbite to Physically Based Rendering 3.0]
- L236-239 _function_ `float DegreesToRadians(float InDeg)`

### `Shaders/Private/StochasticLighting/StochasticLightingRayTracing.ush` (Private)

- lines: 26; parse: all-branches
- L3 #pragma `once`

#### Global parameters (uniforms) (2)

- L5 _parameter_ `float4 FirstPersonWorldSpaceRepresentationBounds;` — Collective bounding sphere for all the invisible primitives tagged as FirstPersonWorldSpaceRepresentation
- L6 _parameter_ `float FirstPersonMinimumHitDistanceOnScreenTraceMiss;`

#### Functions (1)

- L12-26 _function_ `float ClipFirstPersonScreenSpaceRay(float3 TranslatedWorldPosition, float3 RayDirection, float RayT, bool bHit)` — First person world space representation primitives are invisible to the camera but visible in shadows and HWRT reflections. Screen traces can miss intersections with these invisible meshes, so when HWRT picks up, we end up seeing holes and other artifacts in the reflected meshes. To work around this issue, we move the ray position at which we hand off to HWRT outside the bounds of the invisible geometry such that HWRT has a chance to intersect it.

### `Shaders/Private/StochasticLighting/StochasticLightingTileClassification.usf` (Private)

- lines: 1100; parse: all-branches
- includes: L9 `../Common.ush`, L10 `../LightGridCommon.ush`, L11 `../Lumen/LumenMaterial.ush`, L12 `../Lumen/LumenReflectionCommon.ush`, L13 `../Lumen/LumenScreenProbeTileClassication.ush`, L14 `../MegaLights/MegaLightsTileClassification.ush`, L15 `StochasticLightingUpsample.ush`, L16 `StochasticLightingCommon.ush`

#### Macros (#define, 16)

- L4 `#define SUBSTRATE_COMPLEXSPECIALPATH 0`
- L6 `#define SUBSTRATE_MATERIALCONTAINER_IS_VIEWRESOURCE 1`
- L7 `#define USE_HAIR_COMPLEX_TRANSMITTANCE 1`
- L20 `#define DOWNSAMPLE_FACTOR 2`
- L21 `#define TILE_SIZE 8`
- L22 `#define TILE_SIZE_DIV_SHIFT 3`
- L24 `#define STOCHASTIC_SAMPLE_OFFSET_2x1 1`
- L25 `#define STOCHASTIC_SAMPLE_OFFSET_2x2 2`
- L27 `#define USE_CLOSURECOUNT_HISTORY_REJECTION (SUBSTRATE_ENABLED && SUBSTRATE_GBUFFER_FORMAT == 1 && MATERIAL_SOURCE == MATERIAL_SOURCE_GBUFFER)`
- L73 `#define TILE_BITMASK_INDEX_LUMEN 0` _[#if TILE_CLASSIFY_LUMEN \|\| TILE_CLASSIFY_MEGALIGHTS \|\| TILE_CLASSIFY_SUBSTRATE]_
- L74 `#define TILE_BITMASK_INDEX_MEGALIGHTS 1` _[#if TILE_CLASSIFY_LUMEN \|\| TILE_CLASSIFY_MEGALIGHTS \|\| TILE_CLASSIFY_SUBSTRATE]_
- L75 `#define TILE_BITMASK_INDEX_SUBSTRATE 2` _[#if TILE_CLASSIFY_LUMEN \|\| TILE_CLASSIFY_MEGALIGHTS \|\| TILE_CLASSIFY_SUBSTRATE]_
- L76 `#define TILE_BITMASK_BIT_COUNT 10` _[#if TILE_CLASSIFY_LUMEN \|\| TILE_CLASSIFY_MEGALIGHTS \|\| TILE_CLASSIFY_SUBSTRATE]_
- L77 `#define TILE_BITMASK_BIT_MASK 0x3FF` _[#if TILE_CLASSIFY_LUMEN \|\| TILE_CLASSIFY_MEGALIGHTS \|\| TILE_CLASSIFY_SUBSTRATE]_
- L79 `#define WriteSharedTileBitmask(LinearThreadIndex, InBitmask, InBitmaskIndex) { GroupTileBitmask \|= (TILE_BITMASK_BIT_MASK & InBitmask) << (InBitmaskIndex*TILE_BITMASK_BIT_COUNT); }` _[#if TILE_CLASSIFY_LUMEN \|\| TILE_CLASSIFY_MEGALIGHTS \|\| TILE_CLASSIFY_SUBSTRATE && PLATFORM_SUPPORTS_SM6_0_WAVE_OPERATIONS]_
- L80 `#define ReadSharedTileBitmask(LinearThreadIndex, InBitmaskIndex) BitFieldExtractU32(GroupTileBitmask, TILE_BITMASK_BIT_COUNT, InBitmaskIndex * TILE_BITMASK_BIT_COUNT)` _[#if TILE_CLASSIFY_LUMEN \|\| TILE_CLASSIFY_MEGALIGHTS \|\| TILE_CLASSIFY_SUBSTRATE && PLATFORM_SUPPORTS_SM6_0_WAVE_OPERATIONS]_

#### Entry points (1)

- L504-1100 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void StochasticLightingTileClassificationMarkCS( uint2 GroupId : SV_GroupID, uint2 GroupThreadId : SV_GroupThreadID, uint2 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FStochasticLightingTileClassificationMarkCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/StochasticLighting/StochasticLighting.cpp:286) — Load GBuffer data once and transform it for subsequent lighting passes This includes full res depth and normal copy for opaque before it gets overwritten by water or other translucency writing depth

#### Structs / classes (2)

- L409-432 _struct_ **`FHistoryTaps4`** `struct FHistoryTaps4` — 2x2 bilinear taps stored in one bool4 like this: x y z w
  - L411 _member_ `bool4 Quad;`
  - L413 _method_ `void Init()`
  - L418 _method_ `void SetBilinear(bool4 bValid)`
  - L423 _method_ `void TestBilinear(bool4 bValid)`
  - L428 _method_ `bool4 GetBilinear()`
- L442-498 _struct_ **`FHistoryTaps12`** `struct FHistoryTaps12` — 12 taps stored in 4 x bool3 12 used for the Catmull-Rom approximation Center 4 used for the 2x2 bilinear filter 0x \| 1x 0y 0z \| 1y 1z 2x 2y \| 3x 3y 2z \| 3z
  - L444 _member_ `bool3 Quad0;`
  - L445 _member_ `bool3 Quad1;`
  - L446 _member_ `bool3 Quad2;`
  - L447 _member_ `bool3 Quad3;`
  - L449 _method_ `void Init()`
  - L457 _method_ `void SetBicubic(bool3 bValid0, bool3 bValid1, bool3 bValid2, bool3 bValid3)`
  - L465 _method_ `void TestBicubic(bool3 bValid0, bool3 bValid1, bool3 bValid2, bool3 bValid3)`
  - L473 _method_ `void SetBilinear(bool4 bValid)`
  - L481 _method_ `void TestBilinear(bool4 bValid)`
  - L489 _method_ `bool4 GetBilinear()`
  - L494 _method_ `bool IsBicubicValid()`

#### Global resources (textures / buffers / samplers) (19)

- L18-29 _resource_ `MAX_OCCUPANCY Texture2D DepthHistoryTexture;`
- L30 _resource_ `Texture2D<float4> NormalAndShadingInfoHistory;`
- L31 _resource_ `Texture2D<uint> ClosureHistory;`
- L32 _resource_ `Texture2D<uint> MegaLightsNumFramesAccumulatedHistory;`
- L35 _resource_ `StructuredBuffer<uint> TileIndirectDispatchData;` _[#if TILE_INDIRECT_DISPATCH]_
- L38 _resource_ `RWTexture2D<float> RWDepthTexture;`
- L39 _resource_ `RWTexture2D<float4> RWNormalTexture;`
- L40 _resource_ `RWTexture2D<uint> RWClosureTexture;`
- L41 _resource_ `RWTexture2DArray<uint> RWLumenTileBitmask;`
- L42 _resource_ `RWTexture2D<uint> RWMegaLightsTileBitmask;`
- L43 _resource_ `RWTexture2D<uint2> RWEncodedHistoryScreenCoord;`
- L44 _resource_ `RWTexture2DArray<uint> RWLumenPackedPixelData;`
- L45 _resource_ `RWTexture2D<uint> RWMegaLightsPackedPixelData;`
- L87 _resource_ `RWTexture2D<float> RWDownsampledSceneDepth2x1;`
- L88 _resource_ `RWTexture2D<float> RWDownsampledSceneDepth2x2;`
- L89 _resource_ `RWTexture2D<UNORM float3> RWDownsampledWorldNormal2x1;`
- L90 _resource_ `RWTexture2D<UNORM float3> RWDownsampledWorldNormal2x2;`
- L385 _resource_ `RWBuffer<uint> TileDrawIndirectDataBufferUAV;` _[#if TILE_CLASSIFY_SUBSTRATE]_
- L386 _resource_ `RWBuffer<uint> TileListBufferUAV;` _[#if TILE_CLASSIFY_SUBSTRATE]_

#### Global parameters (uniforms) (21)

- L47 _parameter_ `uint EnableTexturedRectLights;`
- L48 _parameter_ `float4 HistoryScreenPositionScaleBias;`
- L49 _parameter_ `float4 HistoryUVMinMax;`
- L50 _parameter_ `float4 HistoryGatherUVMinMax;`
- L51 _parameter_ `float4 HistoryBufferSizeAndInvSize;`
- L52 _parameter_ `float4 HistorySubPixelGridSizeAndInvSize;`
- L53 _parameter_ `float LumenHistoryDistanceThreshold;`
- L54 _parameter_ `float LumenHistoryDistanceThresholdForFoliage;`
- L55 _parameter_ `float LumenHistoryNormalCosThreshold;`
- L56 _parameter_ `float MegaLightsHistoryDistanceThreshold;`
- L57 _parameter_ `uint2 HistoryScreenCoordDecodeShift;`
- L58 _parameter_ `uint2 DownsampledViewMin2x1;`
- L59 _parameter_ `uint2 DownsampledViewMin2x2;`
- L60 _parameter_ `uint2 DownsampledViewSize2x1;`
- L61 _parameter_ `uint2 DownsampledViewSize2x2;`
- L62 _parameter_ `uint LumenStochasticSampleMode;`
- L63 _parameter_ `uint MegaLightsStochasticSampleMode;`
- L64 _parameter_ `uint OutputDownsampledDepthAndNormal;`
- L387 _parameter_ `uint bRectPrimitive;` _[#if TILE_CLASSIFY_SUBSTRATE]_
- L388 _parameter_ `uint TileEncoding;` _[#if TILE_CLASSIFY_SUBSTRATE]_
- L389 _parameter_ `uint4 TileListBufferOffsets[SUBSTRATE_TILE_TYPE_COUNT];` _[#if TILE_CLASSIFY_SUBSTRATE]_

#### groupshared (6)

- L68 _groupshared_ `groupshared uint SharedTileBitmask;` _[#if TILE_CLASSIFY_LUMEN \|\| TILE_CLASSIFY_MEGALIGHTS \|\| TILE_CLASSIFY_SUBSTRATE && PLATFORM_SUPPORTS_SM6_0_WAVE_OPERATIONS]_
- L70 _groupshared_ `groupshared uint SharedTileBitmask[THREADGROUP_SIZE * THREADGROUP_SIZE];` _[#if TILE_CLASSIFY_LUMEN \|\| TILE_CLASSIFY_MEGALIGHTS \|\| TILE_CLASSIFY_SUBSTRATE && !(PLATFORM_SUPPORTS_SM6_0_WAVE_OPERATIONS)]_
- L92 _groupshared_ `groupshared float SharedSceneDepth2x1[6][10];`
- L93 _groupshared_ `groupshared float3 SharedEncodedNormal2x1[6][10];`
- L94 _groupshared_ `groupshared float SharedSceneDepth2x2[6][6];`
- L95 _groupshared_ `groupshared float3 SharedEncodedNormal2x2[6][6];`

#### Functions (14)

- L82 _function_ `void WriteSharedTileBitmask(uint LinearThreadIndex, uint InBitmask, uint InBitmaskIndex)` _[#if TILE_CLASSIFY_LUMEN \|\| TILE_CLASSIFY_MEGALIGHTS \|\| TILE_CLASSIFY_SUBSTRATE && !(PLATFORM_SUPPORTS_SM6_0_WAVE_OPERATIONS)]_
- L83 _function_ `uint ReadSharedTileBitmask(uint LinearThreadIndex, uint InBitmaskIndex)` _[#if TILE_CLASSIFY_LUMEN \|\| TILE_CLASSIFY_MEGALIGHTS \|\| TILE_CLASSIFY_SUBSTRATE && !(PLATFORM_SUPPORTS_SM6_0_WAVE_OPERATIONS)]_
- L97-107 _function_ `void StoreDepthToCache(uint2 SharedCoord, const uint2 DownsampleFactor, float Depth)`
- L109-119 _function_ `float LoadDepthFromCache(uint2 SharedCoord, const uint2 DownsampleFactor)`
- L121-131 _function_ `void StoreNormalToCache(uint2 SharedCoord, const uint2 DownsampleFactor, float3 Normal)`
- L133-143 _function_ `float3 LoadNormalFromCache(uint2 SharedCoord, const uint2 DownsampleFactor)`
- L145-151 _function_ `float GetNormalWeight(float3 SceneWorldNormal, float3 SampleWorldNormal)`
- L153-179 _function_ `uint2 ThreadIndexToBorderCoord(uint LinearThreadIndex, const uint2 DownsampleFactor)`
- L181-195 _function_ `uint2 GetDownsampleJitter(uint2 DownsampledCoord, const uint2 DownsampleFactor)`
- L197-265 _function_ `void DownsampleDepthAndNormal( uint2 GroupId, uint2 GroupThreadId, uint2 ScreenCoord, FLumenMaterialData Material, const uint2 DownsampleFactor, RWTexture2D<float> RWDownsampledDepth, RWTexture2D<UNORM float3> RWDownsampledNormal)`
- L267-277 _function_ `bool IsValidDownsampledCoord(uint2 DownsampledScreenCoord, const uint2 DownsampleFactor)`
- L279-382 _function_ `float4 ComputeUpsampleWeights(uint2 GroupThreadId, uint2 ScreenCoord, float2 ScreenUV, float2 ScreenPosition, float3 TranslatedWorldPosition, FLumenMaterialData Material, const uint2 DownsampleFactor)`
- L390-393 _function_ `uint GetTileListBufferOffsets(uint Type)` _[#if TILE_CLASSIFY_SUBSTRATE]_
- L396-404 _function_ `float4 ConvertFromDeviceZ4(float4 DeviceZ4)`

### `Shaders/Private/StochasticLighting/StochasticLightingUpsample.ush` (Private)

- lines: 126; parse: all-branches
- L3 #pragma `once`

#### Global parameters (uniforms) (1)

- L5 _parameter_ `uint StochasticLightingStateFrameIndex;`

#### Functions (5)

- L7-14 _function_ `uint2 GetDownsampleJitter2x1(uint2 DownsampledScreenCoord)`
- L16-27 _function_ `uint2 GetDownsampleJitter2x2(uint2 DownsampledScreenCoord)`
- L29-59 _function_ `uint2 GetStochasticBilinearOffset(float RandomScalar, float4 UpsampleWeights, int2 SampleOffsets[4])`
- L62-71 _function_ `int2 GetStochasticBilinearOffset(float RandomScalar, float4 UpsampleWeights)` — Stochastic bilinear 2x2 filter
- L74-125 _function_ `uint3 GetStochasticTrilinearOffset(float RandomScalar, float4 InterpolationWeights0, float4 InterpolationWeights1)` — Stochastic trilinear 2x2x2 filter

### `Shaders/Private/StochasticLighting/StochasticLightingVisualize.ush` (Private)

- lines: 65; parse: all-branches
- includes: L6 `../EyeAdaptationCommon.ush`, L7 `../TonemapCommon.ush`

#### Macros (#define, 3)

- L5 `#define EYE_ADAPTATION_LOOSE_PARAMETERS 1`
- L9 `#define LUT_SCALING 1.05f`
- L10 `#define LUT_SIZE 32.f`
- L3 #pragma `once`

#### Global resources (textures / buffers / samplers) (2)

- L11 _resource_ `Texture3D ColorGradingLUT;`
- L12 _resource_ `SamplerState ColorGradingLUTSampler;`

#### Global parameters (uniforms) (1)

- L22 _parameter_ `uint Tonemap;`

#### Functions (3)

- L14-20 _function_ `float3 ColorLookupTable(float3 LinearColor)`
- L27-41 _function_ `float3 VisualizeTonemap(float3 LinearColor)` — Simplified tonemapper, which is useful for visualizations done after the main tonemapping pass, so that they can match colors.
- L46-65 _function_ `bool IsInsideVisualizeRect(int2 PixelCoord, int2 OutputViewSize, int2 OutputViewOffset)` — Drop pixels outside of a round visualization output view tile
