# Shaders / Shaders/Private/SSRT

- files: 6; lines: 2395
- record kinds: cpp_binding=7, define=57, entry=7, function=32, groupshared=4, include=27, member=10, parameter=21, resource=30, struct=3

### `Shaders/Private/SSRT/SSRTDiffuseIndirect.usf` (Private)

- lines: 587; parse: all-branches
- includes: L102 `SSRTRayCast.ush`, L103 `SSRTTileClassificationBuffer.ush`, L104 `../DeferredShadingCommon.ush`, L105 `../Random.ush`, L106 `../BRDF.ush`, L107 `../MonteCarlo.ush`, L108 `../SceneTextureParameters.ush`, L109 `../Substrate/Substrate.ush`, L110 `../HZB.ush`

#### Macros (#define, 39)

- L8 `#define CASTING_PASS_STANDALONE 0`
- L9 `#define CASTING_PASS_PROBE_OCCLUSION 1`
- L11 `#define DIFFUSE_TERM 0`
- L12 `#define SPECULAR_TERM 1`
- L17 `#define DEBUG_SSRT 0`
- L18 `#define DEBUG_RAY_COUNT 0`
- L21 `#define CONFIG_LDS_STORE_VIEW_N 1`
- L24 `#define CONFIG_RAY_STEPS 8` _[#if QUALITY == 1]_
- L25 `#define CONFIG_RAY_COUNT 4` _[#if QUALITY == 1]_
- L28 `#define CONFIG_RAY_STEPS 8` _[#if !(QUALITY == 1) && QUALITY == 2]_
- L29 `#define CONFIG_RAY_COUNT 8` _[#if !(QUALITY == 1) && QUALITY == 2]_
- L32 `#define CONFIG_RAY_STEPS 8` _[#if !(QUALITY == 1) && !(QUALITY == 2) && QUALITY == 3]_
- L33 `#define CONFIG_RAY_COUNT 16` _[#if !(QUALITY == 1) && !(QUALITY == 2) && QUALITY == 3]_
- L36 `#define CONFIG_RAY_STEPS 12` _[#if !(QUALITY == 1) && !(QUALITY == 2) && !(QUALITY == 3) && QUALITY == 4]_
- L37 `#define CONFIG_RAY_COUNT 32` _[#if !(QUALITY == 1) && !(QUALITY == 2) && !(QUALITY == 3) && QUALITY == 4]_
- L44 `#define TILE_PIXEL_SIZE_X 8` _[#if CONFIG_RAY_COUNT == 4]_
- L45 `#define TILE_PIXEL_SIZE_X_LOG 3` _[#if CONFIG_RAY_COUNT == 4]_
- L47 `#define TILE_PIXEL_SIZE_Y 8` _[#if CONFIG_RAY_COUNT == 4]_
- L48 `#define TILE_PIXEL_SIZE_Y_LOG 3` _[#if CONFIG_RAY_COUNT == 4]_
- L51 `#define TILE_PIXEL_SIZE_X 8` _[#if !(CONFIG_RAY_COUNT == 4) && CONFIG_RAY_COUNT == 8]_
- L52 `#define TILE_PIXEL_SIZE_X_LOG 3` _[#if !(CONFIG_RAY_COUNT == 4) && CONFIG_RAY_COUNT == 8]_
- L54 `#define TILE_PIXEL_SIZE_Y 4` _[#if !(CONFIG_RAY_COUNT == 4) && CONFIG_RAY_COUNT == 8]_
- L55 `#define TILE_PIXEL_SIZE_Y_LOG 2` _[#if !(CONFIG_RAY_COUNT == 4) && CONFIG_RAY_COUNT == 8]_
- L58 `#define TILE_PIXEL_SIZE_X 4` _[#if !(CONFIG_RAY_COUNT == 4) && !(CONFIG_RAY_COUNT == 8) && CONFIG_RAY_COUNT == 16]_
- L59 `#define TILE_PIXEL_SIZE_X_LOG 2` _[#if !(CONFIG_RAY_COUNT == 4) && !(CONFIG_RAY_COUNT == 8) && CONFIG_RAY_COUNT == 16]_
- L61 `#define TILE_PIXEL_SIZE_Y 4` _[#if !(CONFIG_RAY_COUNT == 4) && !(CONFIG_RAY_COUNT == 8) && CONFIG_RAY_COUNT == 16]_
- L62 `#define TILE_PIXEL_SIZE_Y_LOG 2` _[#if !(CONFIG_RAY_COUNT == 4) && !(CONFIG_RAY_COUNT == 8) && CONFIG_RAY_COUNT == 16]_
- L65 `#define TILE_PIXEL_SIZE_X 4` _[#if !(CONFIG_RAY_COUNT == 4) && !(CONFIG_RAY_COUNT == 8) && !(CONFIG_RAY_COUNT == 16) && CONFIG_RAY_COUNT == 32]_
- L66 `#define TILE_PIXEL_SIZE_X_LOG 2` _[#if !(CONFIG_RAY_COUNT == 4) && !(CONFIG_RAY_COUNT == 8) && !(CONFIG_RAY_COUNT == 16) && CONFIG_RAY_COUNT == 32]_
- L68 `#define TILE_PIXEL_SIZE_Y 2` _[#if !(CONFIG_RAY_COUNT == 4) && !(CONFIG_RAY_COUNT == 8) && !(CONFIG_RAY_COUNT == 16) && CONFIG_RAY_COUNT == 32]_
- L69 `#define TILE_PIXEL_SIZE_Y_LOG 1` _[#if !(CONFIG_RAY_COUNT == 4) && !(CONFIG_RAY_COUNT == 8) && !(CONFIG_RAY_COUNT == 16) && CONFIG_RAY_COUNT == 32]_
- L77 `#define CONFIG_KARIS_WEIGHTING 1` _[#if CONFIG_RAY_COUNT > 1]_
- L79 `#define CONFIG_KARIS_WEIGHTING 0` _[#if !(CONFIG_RAY_COUNT > 1)]_
- L86 `#define CONFIG_LDS_STORE_VIEW_N 0` _[#if !defined(CONFIG_LDS_STORE_VIEW_N)]_
- L92 `#define TILE_PIXEL_COUNT (TILE_PIXEL_SIZE_X * TILE_PIXEL_SIZE_Y)`
- L93 `#define LANE_PER_GROUPS (TILE_PIXEL_COUNT * CONFIG_RAY_COUNT)`
- L99 `#define IS_SSGI_SHADER 1` _[#if DIM_LIGHTING_TERM == DIFFUSE_TERM]_
- L121 `#define ColorTextureSampler GlobalPointClampedSampler` _[#if SUPPORTS_INDEPENDENT_SAMPLERS]_
- L148 `#define GroupMemoryBarrierWithGroupSync() ` _[#if LANE_PER_GROUPS == 64 && 0]_
- L4 #pragma `warning(error: 3206)`; L147 #undef `GroupMemoryBarrierWithGroupSync`

#### Entry points (1)

- L234-586 _entry_ `[numthreads(TILE_PIXEL_SIZE_X, TILE_PIXEL_SIZE_Y, CONFIG_RAY_COUNT)] void MainCS( uint2 GroupId : SV_GroupID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FScreenSpaceCastStandaloneRayCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/ScreenSpaceRayTracing.cpp:659)

#### Global resources (textures / buffers / samplers) (6)

- L116 _resource_ `Texture2D<float> ProbeOcclusionDistanceTexture;`
- L118 _resource_ `Texture2D ColorTexture;`
- L123 _resource_ `SamplerState ColorTextureSampler;` _[#if !(SUPPORTS_INDEPENDENT_SAMPLERS)]_
- L132 _resource_ `RWTexture2D<float4> IndirectDiffuseOutput;`
- L133 _resource_ `RWTexture2D<float> AmbientOcclusionOutput;`
- L135 _resource_ `RWTexture2D<float4> DebugOutput;`

#### Global parameters (uniforms) (5)

- L114 _parameter_ `uint bRejectUncertainRays;`
- L126 _parameter_ `float4 ColorBufferScaleBias;`
- L127 _parameter_ `float2 ReducedColorUVMax;`
- L129 _parameter_ `float PixelPositionToFullResPixel;`
- L130 _parameter_ `float2 FullResPixelOffset;`

#### groupshared (2)

- L140 _groupshared_ `groupshared uint SharedMemory0[LANE_PER_GROUPS * 2];`
- L141 _groupshared_ `groupshared uint SharedMemory1[LANE_PER_GROUPS];`

#### Functions (11)

- L151-156 _function_ `uint CompressN(float3 N)`
- L158-166 _function_ `float3 DecompressN(uint EncodedN)`
- L168-171 _function_ `uint2 DecodeGroupPixelOffset(uint GroupPixelId)`
- L173-176 _function_ `uint EncodeGroupPixelOffset(uint2 GroupPixelOffset)`
- L178-181 _function_ `uint2 ComputePixelPosition(uint2 GroupId, uint2 GroupPixelOffset)`
- L183-194 _function_ `void UpdateLane2DCoordinateInformations( uint2 PixelPosition, inout float2 BufferUV, inout float2 ScreenPos, inout float2 FullResPixelPosition)`
- L196-199 _function_ `float3 ComputeTranslatedWorldPositions(float2 ScreenPos, float SceneDepth)`
- L201-207 _function_ `uint2 ComputePixelPosition(float3 TranslatedWorldPosition)`
- L209-213 _function_ `float ComputeSceneDepth(float3 TranslatedWorldPosition)`
- L215-218 _function_ `uint2 ComputeRandomSeed(uint2 PixelPosition)`
- L220-229 _function_ `float3 ComputeL(float3 N, float2 E)`

### `Shaders/Private/SSRT/SSRTPrevFrameReduction.usf` (Private)

- lines: 354; parse: all-branches
- includes: L5 `SSRTRayCast.ush`, L6 `../SceneTextureParameters.ush`, L7 `../HZB.ush`

#### Macros (#define, 8)

- L3 `#define CONFIG_COLOR_TILE_CLASSIFICATION 0`
- L9 `#define GROUP_TILE_SIZE 8`
- L10 `#define GROUP_PIXEL_COUNT GROUP_TILE_SIZE * GROUP_TILE_SIZE`
- L21 `#define PrevSceneColorSampler GlobalPointClampedSampler` _[#if SUPPORTS_INDEPENDENT_SAMPLERS && DIM_LEAK_FREE]_
- L23 `#define PrevSceneColorSampler GlobalBilinearClampedSampler` _[#if SUPPORTS_INDEPENDENT_SAMPLERS && !(DIM_LEAK_FREE)]_
- L25 `#define PrevSceneDepthSampler GlobalPointClampedSampler` _[#if SUPPORTS_INDEPENDENT_SAMPLERS]_
- L26 `#define HigherMipTextureSampler GlobalPointClampedSampler` _[#if SUPPORTS_INDEPENDENT_SAMPLERS]_
- L27 `#define HigherAlphaMipTextureSampler GlobalPointClampedSampler` _[#if SUPPORTS_INDEPENDENT_SAMPLERS]_

#### Entry points (1)

- L74-353 _entry_ `[numthreads(GROUP_TILE_SIZE, GROUP_TILE_SIZE, 1)] void MainCS( uint2 DispatchThreadId : SV_DispatchThreadID, uint2 GroupId : SV_GroupID, uint2 GroupThreadId : SV_GroupThreadID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FSSRTPrevFrameReductionCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/ScreenSpaceRayTracing.cpp:651)

#### Global resources (textures / buffers / samplers) (14)

- L13 _resource_ `Texture2D PrevSceneColor;`
- L14 _resource_ `Texture2D PrevSceneDepth;`
- L16 _resource_ `Texture2D HigherMipTexture;`
- L17 _resource_ `Texture2D HigherAlphaMipTexture;`
- L29 _resource_ `SamplerState PrevSceneColorSampler;` _[#if !(SUPPORTS_INDEPENDENT_SAMPLERS)]_
- L30 _resource_ `SamplerState PrevSceneDepthSampler;` _[#if !(SUPPORTS_INDEPENDENT_SAMPLERS)]_
- L31 _resource_ `SamplerState HigherMipTextureSampler;` _[#if !(SUPPORTS_INDEPENDENT_SAMPLERS)]_
- L32 _resource_ `SamplerState HigherAlphaMipTextureSampler;` _[#if !(SUPPORTS_INDEPENDENT_SAMPLERS)]_
- L45 _resource_ `RWTexture2D<float4> ReducedSceneColorOutput_0;`
- L46 _resource_ `RWTexture2D<float4> ReducedSceneColorOutput_1;`
- L47 _resource_ `RWTexture2D<float4> ReducedSceneColorOutput_2;`
- L49 _resource_ `RWTexture2D<float> ReducedSceneAlphaOutput_0;`
- L50 _resource_ `RWTexture2D<float> ReducedSceneAlphaOutput_1;`
- L51 _resource_ `RWTexture2D<float> ReducedSceneAlphaOutput_2;`

#### Global parameters (uniforms) (9)

- L35 _parameter_ `float4 PrevBufferBilinearUVMinMax;`
- L36 _parameter_ `float4 PrevScreenPositionScaleBias;`
- L37 _parameter_ `float2 ReducedSceneColorSize;`
- L38 _parameter_ `float2 ReducedSceneColorTexelSize;`
- L39 _parameter_ `float2 HigherMipBufferBilinearMax;`
- L40 _parameter_ `float PrevSceneColorPreExposureCorrection;`
- L41 _parameter_ `float MinimumLuminance;`
- L42 _parameter_ `float HigherMipDownScaleFactor;`
- L43 _parameter_ `float SkyDistance;`

#### groupshared (2)

- L53 _groupshared_ `groupshared uint SharedMemory[GROUP_PIXEL_COUNT * 2];`
- L56 _groupshared_ `groupshared float SharedFurthestDepth[GROUP_PIXEL_COUNT];` _[#if DIM_LEAK_FREE]_

#### Functions (1)

- L60-71 _function_ `float3 ComputeTranslatedWorldPosition(float2 ScreenPosition, float WorldDepth, bool bIsPrevFrame)`

### `Shaders/Private/SSRT/SSRTRayCast.ush` (Private)

- lines: 749; parse: all-branches
- includes: L16 `../Common.ush`

#### Macros (#define, 7)

- L6 `#define SSRT_SAMPLE_BATCH_SIZE 4`
- L8 `#define SSRT_TILE_RES_DIVISOR_LOG2 3`
- L9 `#define SSRT_TILE_RES_DIVISOR 8`
- L10 `#define SSRT_DIRECTIONALITY_DIVISION 8`
- L13 `#define IS_SSGI_SHADER 0` _[#if !defined(IS_SSGI_SHADER)]_
- L18 `#define SSGI_TRACE_CONE 0`
- L22 `#define DEBUG_SSRT 0` _[#if !defined(DEBUG_SSRT)]_
- L3 #pragma `once`

#### Structs / classes (3)

- L60-66 _struct_ **`FSSRTRay`** `struct FSSRTRay` — Structure that represent a ray to be shot in screen space.
  - L62 _member_ `float3 RayStartScreen;`
  - L63 _member_ `float3 RayStepScreen;`
  - L65 _member_ `float CompareTolerance;`
- L171-177 _struct_ **`FSSRTTileInfos`** `struct FSSRTTileInfos` — Information about tiles in SGPRs.
  - L173 _member_ `float Directionality[SSRT_DIRECTIONALITY_DIVISION];`
  - L174 _member_ `float ClosestDeviceZ;`
  - L175 _member_ `uint2 Coord;`
  - L176 _member_ `float _Padding[5];`
- L180-190 _struct_ **`FSSRTCastingSettings`** `struct FSSRTCastingSettings` — Casting.
  - L183 _member_ `bool bStopWhenUncertain;` — (Compile time) whether should terminate the ray immediately if the ray become uncertain.
  - L186 _member_ `bool bUseTileInfo;` — (Compile time) whether should use tile informations
  - L189 _member_ `FSSRTTileInfos TileInfos;` — (SGPRs) Information about the tile to speed up casting.

#### Global resources (textures / buffers / samplers) (1)

- L27 _resource_ `RWTexture2D<float4> ScreenSpaceRayTracingDebugOutput;` _[#if DEBUG_SSRT]_

#### Functions (15)

- L30-40 _function_ `void PrintSample( float4 InHZBUvFactorAndInvFactor, float2 HZBUV, float4 DebugColor)` _[#if DEBUG_SSRT]_
- L46-56 _function_ `float GetStepScreenFactorToClipAtScreenEdge(float2 RayStartScreen, float2 RayStepScreen)` — Return float multiplier to scale RayStepScreen such that it clip it right at the edge of the screen.
- L69-121 _function_ `FSSRTRay InitScreenSpaceRayFromWorldSpace( float3 RayOriginTranslatedWorld, float3 WorldRayDirection, float WorldTMax, float SceneDepth, float SlopeCompareToleranceScale, const bool bExtendRayToScreenBorder, out bool bRayWasClipped, const float WorldTMaxClamp = 1000000)` — Compile a ray for screen space ray casting.
- L123-129 _function_ `float4 ApplyProjMatrix(float4 V)`
- L133-168 _function_ `FSSRTRay InitScreenSpaceRay( float2 ScreenPos, float DeviceZ, float3 ViewRayDirection)` — Compile a ray for screen space ray casting, but avoiding the computation of translated world position. TODO: passdown ViewRayDirection instead?
- L193-200 _function_ `FSSRTCastingSettings CreateDefaultCastSettings()`
- L202-252 _function_ `uint ComputeRayDirectionId(FSSRTRay Ray)`
- L255-627 _function_ `void CastScreenSpaceRay( Texture2D Texture, SamplerState Sampler, float StartMipLevel, FSSRTCastingSettings CastSettings, FSSRTRay Ray, float Roughness, uint NumSteps, float StepOffset, float4 InHZBUvFactorAndInvFactor, bool bDebugPrint, out float3 DebugOutput, out float3 OutHitUVz, out float Level, out bool bFoundHit, out bool bUncertain)` — Cast a screen space ray.
- L630-672 _function_ `bool RayCast( Texture2D Texture, SamplerState Sampler, float3 RayOriginTranslatedWorld, float3 RayDirection, float Roughness, float SceneDepth, uint NumSteps, float StepOffset, float4 InHZBUvFactorAndInvFactor, bool bDebugPrint, out float3 OutHitUVz, out float Level)`
- L674-681 _function_ `float ComputeHitVignetteFromScreenPos(float2 ScreenPos)`
- L683-694 _function_ `void ReprojectHit(float4 PrevScreenPositionScaleBias, float3 HitUVz, out float2 OutPrevUV, out float OutVignette)`
- L696-714 _function_ `void ReprojectHit(float4 PrevScreenPositionScaleBias, Texture2D Texture, SamplerState Sampler, float3 HitUVz, out float2 OutPrevUV, out float OutVignette)`
- L716-725 _function_ `float ComputeRayHitSqrDistance(float3 OriginTranslatedWorld, float3 HitUVz)`
- L727-737 _function_ `float4 SampleScreenColor(Texture2D Texture, SamplerState Sampler, float2 UV)`
- L739-749 _function_ `float4 SampleHCBLevel( Texture2D Texture, SamplerState Sampler, float2 UV, float Level, float4 InHZBUvFactorAndInvFactor )`

### `Shaders/Private/SSRT/SSRTReflections.usf` (Private)

- lines: 490; parse: all-branches
- includes: L3 `SSRTRayCast.ush`, L4 `../Random.ush`, L5 `../BRDF.ush`, L6 `../MonteCarlo.ush`, L7 `../SceneTextureParameters.ush`, L8 `../ScreenSpaceDenoise/SSDPublic.ush`, L9 `../Substrate/Substrate.ush`, L10 `../HZB.ush`
- L13 #pragma `warning(error: 3206)`

#### Entry points (4)

- L59-103 _entry_ `void ScreenSpaceReflectionsStencilPS( float4 SvPosition : SV_POSITION , out float4 OutColor : SV_Target0 , out float4 OutClosestHitDistance : SV_Target1 )` — stage: **pixel (from C++ binding)** — C++: `FScreenSpaceReflectionsStencilPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/ScreenSpaceRayTracing.cpp:658) — Used only if r.SSR.Stencil = 1 This shader generate the stencil buffer according to if a pixel needs to compute SSR. If it doesn't, it initializes the pixel's color. This optimization use the stencil to test to prunes out the pixel that dones't need to compute SSR, before pixel shader invocation are packed into front lines.
- L418-431 _entry_ `void ScreenSpaceReflectionsPS( float4 SvPosition : SV_POSITION , out float4 OutColor : SV_Target0 , out float4 OutClosestHitDistance : SV_Target1 )` — stage: **pixel (from C++ binding)** — C++: `FScreenSpaceReflectionsPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/ScreenSpaceRayTracing.cpp:653)
- L440-462 _entry_ `[numthreads(THREADGROUP_SIZE_X, THREADGROUP_SIZE_Y, 1)] void ScreenSpaceReflectionsCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FScreenSpaceReflectionsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/ScreenSpaceRayTracing.cpp:654) _[#if COMPUTE_SHADER]_
- L466-488 _entry_ `void VisualizeTiledScreenSpaceReflectionsPS( float4 SvPosition : SV_POSITION , out float4 OutColor : SV_Target0 , out float4 OutClosestHitDistance : SV_Target1 )` — stage: **pixel (from C++ binding)** — C++: `FVisualizeTiledScreenSpaceReflectionsPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/ScreenSpaceRayTracing.cpp:656)

#### Global resources (textures / buffers / samplers) (4)

- L24 _resource_ `Texture2D SceneColor;`
- L25 _resource_ `SamplerState SceneColorSampler;`
- L435 _resource_ `RWTexture2D<float4> SSRColorOutput;` _[#if COMPUTE_SHADER]_
- L437 _resource_ `RWTexture2D<float> SSRHitDistanceOutput;` _[#if COMPUTE_SHADER && SSR_OUTPUT_FOR_DENOISER]_

#### Global parameters (uniforms) (4)

- L17 _parameter_ `float4 SSRParams;` — .r:Intensity in 0..1 range .g:RoughnessMaskMul, b:EnableDiscard for FPostProcessScreenSpaceReflectionsStencilPS, a:(bTemporalAAIsOn?TemporalAAIndex:StateFrameIndexMod8)*1551
- L19 _parameter_ `float PrevSceneColorPreExposureCorrection;`
- L22 _parameter_ `float4 PrevScreenPositionScaleBias;` — Equivalent of View.ScreenPositionScaleBias, but for SSR.
- L27 _parameter_ `uint ShouldReflectOnlyWater;`

#### Functions (3)

- L29-43 _function_ `float GetRoughness(const in FGBufferData GBuffer)`
- L45-49 _function_ `float GetRoughnessFade(in float Roughness)`
- L105-416 _function_ `void ScreenSpaceReflections( float4 SvPosition , out float4 OutColor , out float4 OutClosestHitDistance )`

### `Shaders/Private/SSRT/SSRTTileClassification.usf` (Private)

- lines: 174; parse: all-branches
- includes: L10 `SSRTTileClassificationBuffer.ush`, L11 `SSRTRayCast.ush`, L12 `../SceneTextureParameters.ush`, L13 `../FastMath.ush`, L14 `../HZB.ush`

#### Macros (#define, 3)

- L7 `#define CONFIG_COLOR_TILE_CLASSIFICATION 0`
- L17 `#define GROUP_TILE_SIZE 8`
- L22 `#define ColorTextureSampler GlobalPointClampedSampler` _[#if SUPPORTS_INDEPENDENT_SAMPLERS]_
- L4 #pragma `warning(error: 3206)`

#### Entry points (1)

- L42-173 _entry_ `[numthreads(GROUP_TILE_SIZE, GROUP_TILE_SIZE, SSRT_DIRECTIONALITY_DIVISION)] void MainCS( uint2 DispatchThreadId : SV_DispatchThreadID, uint2 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FSSRTDiffuseTileClassificationCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/ScreenSpaceRayTracing.cpp:652)

#### Global resources (textures / buffers / samplers) (4)

- L19 _resource_ `Texture2D ColorTexture;`
- L24 _resource_ `SamplerState ColorTextureSampler;` _[#if !(SUPPORTS_INDEPENDENT_SAMPLERS)]_
- L27 _resource_ `RWStructuredBuffer<FSSRTTileInfos> TileClassificationBufferOutput;`
- L28 _resource_ `RWTexture2D<float4> DebugOutput;`

### `Shaders/Private/SSRT/SSRTTileClassificationBuffer.ush` (Private)

- lines: 41; parse: all-branches
- includes: L5 `SSRTRayCast.ush`
- L3 #pragma `once`

#### Global resources (textures / buffers / samplers) (1)

- L13 _resource_ `StructuredBuffer<FSSRTTileInfos> TileClassificationBuffer;`

#### Global parameters (uniforms) (3)

- L9 _parameter_ `uint2 TileBufferExtent;`
- L10 _parameter_ `uint ViewTileCount;`
- L11 _parameter_ `uint MaxTileCount;`

#### Functions (2)

- L16-23 _function_ `FSSRTTileInfos LoadTileInfos(uint2 TileCoord)` — Load tile informations using scalar load.
- L27-39 _function_ `bool TestRayEarlyReturn(FSSRTTileInfos TileInfos, FSSRTRay Ray)` — Test whether a screen space ray can be discarded or not based on tile information.
