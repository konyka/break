# Shaders / Shaders/Private/Lumen/SurfaceCache

- files: 3; lines: 1307
- record kinds: cpp_binding=5, define=39, entry=5, function=23, groupshared=3, include=12, member=29, parameter=14, resource=31, struct=5

### `Shaders/Private/Lumen/SurfaceCache/LumenSurfaceCache.usf` (Private)

- lines: 533; parse: all-branches
- includes: L3 `../../Common.ush`, L4 `../../BRDF.ush`, L5 `../../BlockCompressionCommon.ush`, L6 `../../BCCompressionCommon.ush`, L7 `LumenSurfaceCache.ush`, L8 `LumenSurfaceCacheSampling.ush`, L9 `../LumenVirtualTextureCommon.ush`

#### Macros (#define, 8)

- L12 `#define THREADGROUP_SIZE 0` _[#if !defined(THREADGROUP_SIZE)]_
- L29 `#define SURFACE_LAYER_DEPTH 0`
- L30 `#define SURFACE_LAYER_ALBEDO 1`
- L31 `#define SURFACE_LAYER_NORMAL 2`
- L32 `#define SURFACE_LAYER_EMISSIVE 3`
- L316 `#define TILE_SIZE 8` _[#if defined(CopyCapturedCardPageCS)]_
- L317 `#define BORDER_SIZE 1` _[#if defined(CopyCapturedCardPageCS)]_
- L318 `#define TILE_SIZE_WITH_BORDER (TILE_SIZE + BORDER_SIZE * 2)` _[#if defined(CopyCapturedCardPageCS)]_

#### Entry points (5)

- L34-149 _entry_ `void LumenCardCopyPS( float4 Position : SV_POSITION, float2 AtlasUV : TEXCOORD0, float2 RectUV : TEXCOORD1, float RectIndex : RECT_INDEX , out float4 OutColor0 : SV_Target0 )` — stage: **pixel (from C++ binding)** — C++: `FLumenCardCopyPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenSurfaceCache.cpp:177)
- L153-235 _entry_ `void LumenCardResamplePS( float4 SvPosition : SV_POSITION, float2 AtlasUV : TEXCOORD0, float2 RectUV : TEXCOORD1, float RectIndexF : RECT_INDEX, out float4 OutAlbedoOpacity : SV_Target0, out float4 OutNormal : SV_Target1, out float4 OutEmissive : SV_Target2, out float OutDepth : SV_DEPTH)` — stage: **pixel (from C++ binding)** — C++: `FLumenCardResamplePS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenSceneRendering.cpp:1781)
- L241-290 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void ClearCompressedAtlasCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FClearCompressedAtlasCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenSurfaceCache.cpp:874) _[#if defined(ClearCompressedAtlasCS)]_
- L362-471 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void CopyCapturedCardPageCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FCopyCapturedCardPageCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenSurfaceCache.cpp:385) _[#if defined(CopyCapturedCardPageCS)]_
- L485-530 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void GenerateDilationTileDataCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FGenerateDilationTileDataCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenSurfaceCache.cpp:344) _[#if defined(GenerateDilationTileDataCS)]_

#### Global resources (textures / buffers / samplers) (18)

- L15 _resource_ `Buffer<float4> CardUVRects;`
- L16 _resource_ `Buffer<uint> CardIndices;`
- L18 _resource_ `RWTexture2D<uint4> RWAtlasBlock4;`
- L19 _resource_ `RWTexture2D<uint2> RWAtlasBlock2;`
- L21 _resource_ `Texture2D SourceAlbedoAtlas;`
- L22 _resource_ `Texture2D SourceNormalAtlas;`
- L23 _resource_ `Texture2D SourceEmissiveAtlas;`
- L24 _resource_ `Texture2D SourceDepthAtlas;`
- L151 _resource_ `Buffer<uint4> SourceCardData;`
- L295 _resource_ `Buffer<uint4> CardPageRectBuffer;`
- L296 _resource_ `Buffer<uint> PackedCardTileDataBuffer;`
- L298 _resource_ `RWTexture2D<UNORM float4> RWAlbedoAtlas;`
- L299 _resource_ `RWTexture2D<UNORM float4> RWNormalAtlas;`
- L300 _resource_ `RWTexture2D<float> RWDepthAtlas;`
- L477 _resource_ `Buffer<uint> DilationPageMaskBuffer;`
- L479 _resource_ `RWBuffer<uint> RWTileAllocator;`
- L480 _resource_ `RWBuffer<uint> RWDilationTileAllocator;`
- L481 _resource_ `RWBuffer<uint> RWPackedCardTileDataBuffer;`

#### Global parameters (uniforms) (6)

- L26 _parameter_ `float2 OneOverSourceAtlasSize;`
- L27 _parameter_ `float TexelCullingHeightBias;`
- L238 _parameter_ `float3 ClearValue;` _[#if defined(ClearCompressedAtlasCS)]_
- L239 _parameter_ `uint2 OutputAtlasSize;` _[#if defined(ClearCompressedAtlasCS)]_
- L293 _parameter_ `uint DilationTileDataOffset;`
- L475 _parameter_ `uint NumCardPages;`

#### groupshared (3)

- L320 _groupshared_ `groupshared uint GroupAlbedoStorage[TILE_SIZE_WITH_BORDER][TILE_SIZE_WITH_BORDER];` _[#if defined(CopyCapturedCardPageCS)]_
- L321 _groupshared_ `groupshared uint GroupNormalStorage[TILE_SIZE_WITH_BORDER][TILE_SIZE_WITH_BORDER];` _[#if defined(CopyCapturedCardPageCS)]_
- L322 _groupshared_ `groupshared float GroupDepthStorage[TILE_SIZE_WITH_BORDER][TILE_SIZE_WITH_BORDER];` _[#if defined(CopyCapturedCardPageCS)]_

#### Functions (6)

- L302-305 _function_ `uint PackTileData(uint2 TileCoord, uint PageIndex)`
- L307-312 _function_ `void UnpackTileData(uint Packed, out uint2 TileCoord, out uint PageIndex)`
- L324-333 _function_ `float4 LoadGroupAlbedo(uint2 Coord)` _[#if defined(CopyCapturedCardPageCS)]_
- L335-340 _function_ `void StoreGroupAlbedo(uint2 Coord, float4 Albedo)` _[#if defined(CopyCapturedCardPageCS)]_
- L342-352 _function_ `float4 LoadGroupNormal(uint2 Coord)` _[#if defined(CopyCapturedCardPageCS)]_
- L354-360 _function_ `void StoreGroupNormal(uint2 Coord, float4 Normal)` _[#if defined(CopyCapturedCardPageCS)]_

### `Shaders/Private/Lumen/SurfaceCache/LumenSurfaceCache.ush` (Private)

- lines: 101; parse: all-branches
- includes: L5 `../LumenDiffuseColorBoost.ush`
- L3 #pragma `once`

#### Structs / classes (2)

- L7-11 _struct_ **`FSurfaceCacheDepthData`** `struct FSurfaceCacheDepthData`
  - L9 _member_ `bool bValid;`
  - L10 _member_ `float Depth;`
- L63-74 _struct_ **`FLumenSurfaceCacheData`** `struct FLumenSurfaceCacheData`
  - L65 _member_ `bool bValid;`
  - L67 _member_ `float Depth;`
  - L68 _member_ `float3 Albedo;`
  - L69 _member_ `float3 Emissive;`
  - L72 _member_ `float3 WorldPosition;` — Derived
  - L73 _member_ `float3 WorldNormal;`

#### Global parameters (uniforms) (1)

- L42 _parameter_ `float DiffuseColorBoost;`

#### Functions (7)

- L13-19 _function_ `float EncodeSurfaceCacheDepth(float Depth, bool bValid)`
- L21-24 _function_ `bool IsSurfaceCacheDepthValid(float Depth)`
- L26-32 _function_ `float3 DecodeSurfaceCacheCardSpaceNormal(float2 EncodedNormal)`
- L35-39 _function_ `float3 DecodeSurfaceCacheNormal(FLumenCardData Card, float2 EncodedNormal)` _[#if defined(LUMEN_CARD_DATA_STRIDE)]_
- L44-48 _function_ `float3 DecodeSurfaceCacheAlbedo(float3 EncodedAlbedo)`
- L50-61 _function_ `float3 CombineFinalLighting(float3 Albedo, float3 Emissive, float3 DirectLighting, float3 IndirectLighting)`
- L77-100 _function_ `FLumenSurfaceCacheData GetSurfaceCacheData(FLumenCardData Card, float2 CardUV, float2 AtlasUV)` _[#if defined(LUMEN_CARD_DATA_STRIDE)]_

### `Shaders/Private/Lumen/SurfaceCache/LumenSurfaceCacheSampling.ush` (Private)

- lines: 673; parse: all-branches
- includes: L5 `LumenSurfaceCache.ush`, L6 `../LumenCardCommon.ush`, L21 `../LumenCardTileShadowDownsampleFactor.ush` [ENABLE_VISUALIZE_MODE == 1], L22 `../../Visualization.ush` [ENABLE_VISUALIZE_MODE == 1]

#### Macros (#define, 31)

- L24 `#define VISUALIZE_MODE_DISABLE 0` _[#if ENABLE_VISUALIZE_MODE == 1]_
- L25 `#define VISUALIZE_MODE_OVERVIEW 1` _[#if ENABLE_VISUALIZE_MODE == 1]_
- L26 `#define VISUALIZE_MODE_PERFORMANCE_OVERVIEW 2` _[#if ENABLE_VISUALIZE_MODE == 1]_
- L27 `#define VISUALIZE_MODE_LUMEN_SCENE 3` _[#if ENABLE_VISUALIZE_MODE == 1]_
- L28 `#define VISUALIZE_MODE_REFLECTION_VIEW 4` _[#if ENABLE_VISUALIZE_MODE == 1]_
- L29 `#define VISUALIZE_MODE_SURFACE_CACHE 5` _[#if ENABLE_VISUALIZE_MODE == 1]_
- L30 `#define VISUALIZE_MODE_GEOMETRY_NORMALS 6` _[#if ENABLE_VISUALIZE_MODE == 1]_
- L31 `#define VISUALIZE_MODE_DEDICATED_REFLECTION_RAYS 7` _[#if ENABLE_VISUALIZE_MODE == 1]_
- L32 `#define VISUALIZE_MODE_ALBEDO 8` _[#if ENABLE_VISUALIZE_MODE == 1]_
- L33 `#define VISUALIZE_MODE_NORMALS 9` _[#if ENABLE_VISUALIZE_MODE == 1]_
- L34 `#define VISUALIZE_MODE_EMISSIVE 10` _[#if ENABLE_VISUALIZE_MODE == 1]_
- L35 `#define VISUALIZE_MODE_CARD_WEIGHTS 11` _[#if ENABLE_VISUALIZE_MODE == 1]_
- L36 `#define VISUALIZE_MODE_DIRECT_LIGHTING 12` _[#if ENABLE_VISUALIZE_MODE == 1]_
- L37 `#define VISUALIZE_MODE_INDIRECT_LIGHTING 13` _[#if ENABLE_VISUALIZE_MODE == 1]_
- L38 `#define VISUALIZE_MODE_LOCAL_POSITION 14` _[#if ENABLE_VISUALIZE_MODE == 1]_
- L39 `#define VISUALIZE_MODE_VELOCITY 15` _[#if ENABLE_VISUALIZE_MODE == 1]_
- L40 `#define VISUALIZE_MODE_DIRECT_LIGHTING_UPDATES 16` _[#if ENABLE_VISUALIZE_MODE == 1]_
- L41 `#define VISUALIZE_MODE_INDIRECT_LIGHTING_UPDATES 17` _[#if ENABLE_VISUALIZE_MODE == 1]_
- L42 `#define VISUALIZE_MODE_LAST_USED_PAGE 18` _[#if ENABLE_VISUALIZE_MODE == 1]_
- L43 `#define VISUALIZE_MODE_LAST_USED_PAGE_HIGH_RES 19` _[#if ENABLE_VISUALIZE_MODE == 1]_
- L44 `#define VISUALIZE_MODE_TILE_SHADOW_DOWNSAMPLE_FACTOR 20` _[#if ENABLE_VISUALIZE_MODE == 1]_
- L45 `#define VISUALIZE_MODE_CARD_SHARING_ID 21` _[#if ENABLE_VISUALIZE_MODE == 1]_
- L46 `#define VISUALIZE_MODE_SCREENPROBEGATHER_FAST_UPDATE_MODE_AMOUNT 22` _[#if ENABLE_VISUALIZE_MODE == 1]_
- L47 `#define VISUALIZE_MODE_SCREENPROBEGATHER_NUM_FRAMES_ACCUMULATED 23` _[#if ENABLE_VISUALIZE_MODE == 1]_
- L48 `#define VISUALIZE_MODE_RADIOSITY_NUM_FRAMES_ACCUMULATED 24` _[#if ENABLE_VISUALIZE_MODE == 1]_
- L81 `#define VIRTUAL_PAGE_SIZE 127`
- L82 `#define PHYSICAL_PAGE_SIZE 128`
- L83 `#define MIN_CARD_RESOLUTION 8`
- L84 `#define MIN_RES_LEVEL 3`
- L85 `#define MAX_RES_LEVEL 11`
- L86 `#define SUB_ALLOCATION_RES_LEVEL 7`
- L3 #pragma `once`

#### Structs / classes (3)

- L68-78 _struct_ **`FLumenCardSample`** `struct FLumenCardSample`
  - L70 _member_ `uint CardIndex;`
  - L71 _member_ `uint CardPageIndex;`
  - L72 _member_ `float2 PhysicalAtlasUV;`
  - L73 _member_ `float4 TexelBilinearWeights;`
  - L74 _member_ `float2 IndirectLightingPhysicalAtlasUV;`
  - L75 _member_ `uint2 PackedFeedback;`
  - L76 _member_ `uint2 CardTileAtlasCoord;`
  - L77 _member_ `bool bValid;`
- L192-206 _struct_ **`FCardSampleAccumulator`** `struct FCardSampleAccumulator`
  - L195 _member_ `FLumenCardSample CardSample;` — Single stochastically selected sample
  - L197 _member_ `bool bHeightfield;`
  - L198 _member_ `bool bValidMeshCardsIndex;`
  - L199 _member_ `float MaxSampleWeight;`
  - L202 _member_ `float3 DirectLightingSum;` — Accumulated
  - L203 _member_ `float3 IndirectLightingSum;`
  - L204 _member_ `float3 FinalLightingSum;`
  - L205 _member_ `float SampleWeightSum;`
- L558-565 _struct_ **`FSurfaceCacheSample`** `struct FSurfaceCacheSample`
  - L560 _member_ `float3 Radiance;`
  - L561 _member_ `float3 DirectLighting;`
  - L562 _member_ `float3 IndirectLighting;`
  - L563 _member_ `bool bValid;`
  - L564 _member_ `bool bHeightfield;`

#### Global resources (textures / buffers / samplers) (13)

- L8 _resource_ `Texture2D DirectLightingAtlas;`
- L9 _resource_ `Texture2D IndirectLightingAtlas;`
- L10 _resource_ `Texture2D FinalLightingAtlas;`
- L12 _resource_ `Texture2D<UNORM float> RadiosityNumFramesAccumulatedAtlas;`
- L13 _resource_ `Texture2D AlbedoAtlas;`
- L14 _resource_ `Texture2D NormalAtlas;`
- L15 _resource_ `Texture2D EmissiveAtlas;`
- L16 _resource_ `Texture2D DepthAtlas;`
- L51 _resource_ `Buffer<uint> MeshCardsIndexToCardSharingIdBuffer;` _[#if ENABLE_VISUALIZE_MODE == 1]_
- L58 _resource_ `RWStructuredBuffer<uint> RWCardPageLastUsedBuffer;` _[#if SURFACE_CACHE_FEEDBACK]_
- L59 _resource_ `RWStructuredBuffer<uint> RWCardPageHighResLastUsedBuffer;` _[#if SURFACE_CACHE_FEEDBACK]_
- L61 _resource_ `RWStructuredBuffer<uint> RWSurfaceCacheFeedbackBufferAllocator;` _[#if SURFACE_CACHE_FEEDBACK]_
- L62 _resource_ `RWStructuredBuffer<uint2> RWSurfaceCacheFeedbackBuffer;` _[#if SURFACE_CACHE_FEEDBACK]_

#### Global parameters (uniforms) (7)

- L18 _parameter_ `float OneOverCachedLightingPreExposure;`
- L50 _parameter_ `uint VisualizeMode;` _[#if ENABLE_VISUALIZE_MODE == 1]_
- L54 _parameter_ `uint SurfaceCacheUpdateFrameIndex;`
- L57 _parameter_ `uint SurfaceCacheFeedbackBufferSize;` _[#if SURFACE_CACHE_FEEDBACK]_
- L63 _parameter_ `uint SurfaceCacheFeedbackBufferTileWrapMask;` _[#if SURFACE_CACHE_FEEDBACK]_
- L64 _parameter_ `uint2 SurfaceCacheFeedbackBufferTileJitter;` _[#if SURFACE_CACHE_FEEDBACK]_
- L65 _parameter_ `float SurfaceCacheFeedbackResLevelBias;` _[#if SURFACE_CACHE_FEEDBACK]_

#### Functions (10)

- L88-91 _function_ `uint2 ResLevelXYToSizeInPages(uint2 ResLevelXY)`
- L93-97 _function_ `uint2 GetSizeInPages(FLumenCardData Card, uint ResLevel)`
- L99-190 _function_ `FLumenCardSample ComputeSurfaceCacheSample(FLumenCardData Card, uint CardIndex, float2 LocalSamplePosition, float SampleRadius, bool bHiResSurface)`
- L208-220 _function_ `void InitCardSampleAccumulator(inout FCardSampleAccumulator CardSampleAccumulator)`
- L222-233 _function_ `float3 SampleSurfaceCacheAtlas(Texture2D AtlasTexture, float2 AtlasUV, float4 TexelWeights)`
- L235-437 _function_ `void SampleLumenCard( float3 MeshCardsSpacePosition, float3 MeshCardsSpaceNormal, float SampleRadius, float SurfaceCacheBias, uint CardIndex, float3 AxisWeights, bool bHiResSurface, bool bHeightfield, inout FCardSampleAccumulator CardSampleAccumulator)`
- L442-556 _function_ `void SampleLumenMeshCards( uint MeshCardsIndex, float3 WorldSpacePosition, float3 WorldSpaceNormal, float SampleRadius, float SurfaceCacheBias, bool bHiResSurface, inout FCardSampleAccumulator CardSampleAccumulator )` — Sample surface cads, by accumulating cards samples into CardSampleAccumulator
- L567-576 _function_ `FSurfaceCacheSample InitSurfaceCacheSample()`
- L578-642 _function_ `FSurfaceCacheSample EvaluateRayHitFromCardSampleAccumulator( uint2 DitherScreenCoord, float3 HitWorldPosition, float3 HitWorldNormal, FCardSampleAccumulator CardSampleAccumulator)`
- L647-673 _function_ `FSurfaceCacheSample EvaluateRayHitFromSurfaceCache( uint2 DitherScreenCoord, uint MeshCardsIndex, float3 HitWorldPosition, float3 HitWorldNormal, float SampleRadius, float SurfaceCacheBias, bool bHiResSurface)` — Calculate and return radiance for a hit point using surface cache and radiance field.
