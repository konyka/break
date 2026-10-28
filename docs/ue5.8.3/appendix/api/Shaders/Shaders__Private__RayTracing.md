# Shaders / Shaders/Private/RayTracing

- files: 64; lines: 10787
- record kinds: cpp_binding=72, define=200, entry=58, function=163, include=290, macro_call=7, member=206, method=177, parameter=122, resource=89, static_var=2, struct=45

### `Shaders/Private/RayTracing/CompositeAmbientOcclusionPS.usf` (Private)

- lines: 20; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../DeferredShadingCommon.ush`

#### Global resources (textures / buffers / samplers) (2)

- L6 _resource_ `Texture2D<float4> AmbientOcclusionTexture;`
- L7 _resource_ `SamplerState AmbientOcclusionTextureSampler;`

#### Functions (1)

- L9-19 _function_ `void CompositeAmbientOcclusionPS( in noperspective float2 UV : TEXCOORD0, out float4 OutColor : SV_Target0 )` — sv-semantics

### `Shaders/Private/RayTracing/CompositeSkyLightPS.usf` (Private)

- lines: 71; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../DeferredShadingCommon.ush`, L5 `../SceneTextureParameters.ush`, L14 `../Substrate/Substrate.ush` [SUBSTRATE_ENABLED && SUBSTRATE_GBUFFER_FORMAT==1], L15 `../Substrate/SubstrateEvaluation.ush` [SUBSTRATE_ENABLED && SUBSTRATE_GBUFFER_FORMAT==1]

#### Macros (#define, 6)

- L8 `#define SUBSTRATE_MATERIALCONTAINER_IS_VIEWRESOURCE 1` _[#if SUBSTRATE_ENABLED && SUBSTRATE_GBUFFER_FORMAT==1]_
- L9 `#define SUBSTRATE_FASTPATH 0` _[#if SUBSTRATE_ENABLED && SUBSTRATE_GBUFFER_FORMAT==1]_
- L10 `#define SUBSTRATE_SINGLEPATH 0` _[#if SUBSTRATE_ENABLED && SUBSTRATE_GBUFFER_FORMAT==1]_
- L11 `#define SUBSTRATE_COMPLEXSPECIALPATH 0` _[#if SUBSTRATE_ENABLED && SUBSTRATE_GBUFFER_FORMAT==1]_
- L12 `#define SUBSTRATE_SSS_MATERIAL_OVERRIDE 0` _[#if SUBSTRATE_ENABLED && SUBSTRATE_GBUFFER_FORMAT==1]_
- L13 `#define SUBSTRATE_GLINTS_ALLOWED 0` _[#if SUBSTRATE_ENABLED && SUBSTRATE_GBUFFER_FORMAT==1]_

#### Entry points (1)

- L21-70 _entry_ `void CompositeSkyLightPS( in noperspective float4 OutUVAndScreenPos : TEXCOORD0, out float4 OutColor : SV_Target0 )` — stage: **pixel (from C++ binding)** — C++: `FCompositeSkyLightPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/RayTracing/RaytracingSkylight.cpp:652)

#### Global resources (textures / buffers / samplers) (2)

- L18 _resource_ `Texture2D<float4> SkyLightTexture;`
- L19 _resource_ `SamplerState SkyLightTextureSampler;`

### `Shaders/Private/RayTracing/GenerateSkyLightVisibilityRaysCS.usf` (Private)

- lines: 66; parse: all-branches
- includes: L7 `../Common.ush`, L8 `../MonteCarlo.ush`, L9 `RayTracingCommon.ush`, L10 `RayTracingSkyLightCommon.ush`, L11 `SkyLightVisibilityRaysData.ush`, L12 `../PathTracing/Utilities/PathTracingRandomSequence.ush`

#### Entry points (1)

- L17-65 _entry_ `[numthreads(TILE_SIZE, TILE_SIZE, 1)] void MainCS( uint3 DispatchThreadId : SV_DispatchThreadID )` — stage: **compute** — C++: `FGenerateSkyLightVisibilityRaysCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/RayTracing/RaytracingSkylight.cpp:334)

#### Global resources (textures / buffers / samplers) (1)

- L15 _resource_ `RWStructuredBuffer<FSkyLightVisibilityRays> OutSkyLightVisibilityRays;`

#### Global parameters (uniforms) (1)

- L14 _parameter_ `uint3 SkyLightVisibilityRaysDimensions;`

### `Shaders/Private/RayTracing/MipTreeCommon.ush` (Private)

- lines: 34; parse: all-branches
- includes: L7 `../MortonCode.ush`

#### Macros (#define, 1)

- L9 `#define USE_MORTON_CODE 1`

#### Functions (2)

- L11-14 _function_ `uint2 DimensionsAtLevel(uint2 Dimensions, uint Level)`
- L16-33 _function_ `uint BufferOffsetAtPixel(uint2 Pixel, uint Level, uint2 Dimensions)`

### `Shaders/Private/RayTracing/RayGenUtils.ush` (Private)

- lines: 29; parse: all-branches

#### Macros (#define, 1)

- L5 `#define MAX_DISPATCH_THREAD_PER_DIMENSION 4096`
- L3 #pragma `once`

#### Functions (2)

- L7-23 _function_ `int3 GetRayTracingThreadCountWrapped(uint TargetThreadCount, uint ThreadGroupSize)`
- L25-28 _function_ `uint GetUnWrappedRayTracingDispatchThreadId(int3 DispatchThreadId, uint ThreadGroupSize)`

### `Shaders/Private/RayTracing/RayTracingAmbientOcclusionRGS.usf` (Private)

- lines: 239; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../Montecarlo.ush`, L5 `../DeferredShadingCommon.ush`, L6 `../SceneTextureParameters.ush`, L7 `../PathTracing/Utilities/PathTracingRandomSequence.ush`, L8 `../SphericalGaussian.ush`, L9 `../Substrate/Substrate.ush`, L10 `RayTracingCommon.ush`, L11 `RayTracingDeferredShadingCommon.ush`

#### Macros (#define, 1)

- L14 `#define CONFIG_SHOOT_WITH_GEOMETRIC_NORMAL 1`

#### Entry points (1)

- L85-239 _entry_ `RAY_TRACING_ENTRY_RAYGEN(AmbientOcclusionRGS)` — stage: **raygeneration** — C++: `FRayTracingAmbientOcclusionRGS` SF_RayGen via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/RayTracing/RayTracingAmbientOcclusion.cpp:120)

#### Global resources (textures / buffers / samplers) (3)

- L21 _resource_ `RaytracingAccelerationStructure TLAS;`
- L22 _resource_ `RWTexture2D<float> RWAmbientOcclusionMaskUAV;`
- L23 _resource_ `RWTexture2D<float> RWAmbientOcclusionHitDistanceUAV;`

#### Global parameters (uniforms) (4)

- L17 _parameter_ `uint SamplesPerPixel;`
- L18 _parameter_ `float MaxRayDistance;`
- L19 _parameter_ `float Intensity;`
- L20 _parameter_ `float MaxNormalBias;`

#### Functions (3)

- L27-31 _function_ `float ComputeWorldBluringRadiusCausedByPixelSize(float WorldDepth)` — Returns the radius of a pixel in world space.
- L33-74 _function_ `void GenerateCosineNormalRay( uint2 PixelCoord, float3 TranslatedWorldPosition, float3 WorldNormal, float3 GeometricNormal, inout FRandomSequence RandSequence, out float3 RayOrigin, out float3 RayDirection, out float RayTMin, out float RayTMax, out float RayPDF )`
- L76-83 _function_ `float3 SampleNeightborPosition(uint2 PixelCoord, int2 Offset)`

### `Shaders/Private/RayTracing/RayTracingBarycentrics.usf` (Private)

- lines: 127; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../Visualization.ush`, L5 `RayTracingCommon.ush`, L8 `RayTracingDeferredMaterials.ush` [COMPUTESHADER], L9 `TraceRayInline.ush` [COMPUTESHADER]

#### Entry points (3)

- L106-110 _entry_ `[numthreads(INLINE_RAY_TRACING_THREAD_GROUP_SIZE_X, INLINE_RAY_TRACING_THREAD_GROUP_SIZE_Y, 1)] void RayTracingBarycentricsMainCS(uint2 DispatchThreadIndex : SV_DispatchThreadID)` — stage: **compute** — C++: `FRayTracingBarycentricsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/RayTracing/RayTracingBarycentrics.cpp:137) _[#if COMPUTESHADER]_
- L114-117 _entry_ `RAY_TRACING_ENTRY_RAYGEN(RayTracingBarycentricsMainRGS)` — stage: **raygeneration** — C++: `FRayTracingBarycentricsRGS` SF_RayGen via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/RayTracing/RayTracingBarycentrics.cpp:65) _[#if !(COMPUTESHADER)]_
- L119-125 _entry_ `RAY_TRACING_ENTRY_CLOSEST_HIT(RayTracingBarycentricsMainCHS, FDefaultPayload, Payload, FRayTracingIntersectionAttributes, Attributes)` — stage: **closesthit** — C++: `FRayTracingBarycentricsCHS` SF_RayHitGroup via IMPLEMENT_SHADER_TYPE (Source/Runtime/Renderer/Private/RayTracing/RayTracingBarycentrics.cpp:97) _[#if !(COMPUTESHADER)]_

#### Structs / classes (1)

- L19-38 _struct_ **`FNaniteTraceRayInlineCallback`** `struct FNaniteTraceRayInlineCallback : FDefaultTraceRayInlineCallback` — base/reg: `FDefaultTraceRayInlineCallback` _[#if COMPUTESHADER]_
  - L21 _member_ `float2 Barycentrics;` _[#if COMPUTESHADER]_
  - L22 _member_ `float NaniteCutError;` _[#if COMPUTESHADER]_
  - L24 _method_ `bool OnProceduralPrimitive(float3 ObjectRayOrigin, float3 ObjectRayDirection, float RayTMin, inout float RayTCurrent, FTraceRayInlineProceduralIntersectionParameters ProceduralIntersectionParameters)` _[#if COMPUTESHADER]_

#### Global resources (textures / buffers / samplers) (2)

- L12 _resource_ `RWTexture2D<float4> Output;`
- L13 _resource_ `RaytracingAccelerationStructure TLAS;`

#### Global parameters (uniforms) (2)

- L14 _parameter_ `float RTDebugVisualizationNaniteCutError;`
- L16 _parameter_ `float TimingScale;`

#### Functions (1)

- L42-102 _function_ `void RayTracingBarycentricsCommon(uint2 DispatchThreadIndex)`

### `Shaders/Private/RayTracing/RayTracingBuildDecalGrid.usf` (Private)

- lines: 89; parse: all-branches
- includes: L3 `../Common.ush`, L4 `/Engine/Shared/RayTracingDefinitions.h`, L5 `/Engine/Shared/RayTracingTypes.h`, L6 `/Engine/Shared/PathTracingDefinitions.h`

#### Entry points (1)

- L20-88 _entry_ `[numthreads(THREADGROUPSIZE_X, THREADGROUPSIZE_Y, 1)] void BuildDecalGridCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FRayTracingBuildDecalGridCS` SF_Compute via IMPLEMENT_SHADER_TYPE (Source/Runtime/Renderer/Private/RayTracing/RayTracingDecals.cpp:148)

#### Global resources (textures / buffers / samplers) (3)

- L8 _resource_ `StructuredBuffer<FRayTracingDecal> SceneDecals;`
- L17 _resource_ `RWTexture2DArray<uint> RWDecalGrid;`
- L18 _resource_ `RWBuffer<uint> RWDecalGridData;`

#### Global parameters (uniforms) (6)

- L9 _parameter_ `uint SceneDecalCount;`
- L11 _parameter_ `float3 SceneDecalsTranslatedBoundMin;`
- L12 _parameter_ `float3 SceneDecalsTranslatedBoundMax;`
- L13 _parameter_ `uint DecalGridResolution;`
- L14 _parameter_ `uint DecalGridMaxCount;`
- L15 _parameter_ `uint DecalGridAxis;`

### `Shaders/Private/RayTracing/RayTracingBuildLightGrid.usf` (Private)

- lines: 118; parse: all-branches
- includes: L3 `../Common.ush`, L4 `/Engine/Shared/LightDefinitions.h`, L5 `/Engine/Shared/RayTracingDefinitions.h`, L6 `/Engine/Shared/RayTracingTypes.h`, L7 `../IntersectionUtils.ush`

#### Macros (#define, 2)

- L21 `#define RECT_TEST 2`
- L25 `#define CONE_TEST 1`

#### Entry points (1)

- L29-117 _entry_ `[numthreads(THREADGROUPSIZE_X, THREADGROUPSIZE_Y, 1)] void RayTracingBuildLightGridCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FRayTracingBuildLightGridCS` SF_Compute via IMPLEMENT_SHADER_TYPE (Source/Runtime/Renderer/Private/RayTracing/RayTracingLighting.cpp:79)

#### Global resources (textures / buffers / samplers) (3)

- L10 _resource_ `StructuredBuffer<FRTLightingData> SceneLights;`
- L14 _resource_ `RWTexture2DArray<uint> RWLightGrid;`
- L15 _resource_ `RWBuffer<uint> RWLightGridData;`

#### Global parameters (uniforms) (7)

- L9 _parameter_ `uint SceneLightCount;`
- L11 _parameter_ `uint SceneInfiniteLightCount;`
- L12 _parameter_ `float3 SceneLightsTranslatedBoundMin;`
- L13 _parameter_ `float3 SceneLightsTranslatedBoundMax;`
- L16 _parameter_ `uint LightGridResolution;`
- L17 _parameter_ `uint LightGridMaxCount;`
- L18 _parameter_ `uint LightGridAxis;`

### `Shaders/Private/RayTracing/RayTracingBuiltInShaders.usf` (Private)

- lines: 112; parse: all-branches
- includes: L4 `../Common.ush`, L5 `RayTracingCommon.ush`

#### Entry points (7)

- L12-45 _entry_ `RAY_TRACING_ENTRY_RAYGEN(OcclusionMainRGS)` — stage: **raygeneration** — C++: `FBasicOcclusionMainRGS` SF_RayGen via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/RayTracing/RayTracingBasicShaders.cpp:11)
- L47-74 _entry_ `RAY_TRACING_ENTRY_RAYGEN(IntersectionMainRGS)` — stage: **raygeneration** — C++: `FBasicIntersectionMainRGS` SF_RayGen via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/RayTracing/RayTracingBasicShaders.cpp:12)
- L76-84 _entry_ `RAY_TRACING_ENTRY_CLOSEST_HIT(IntersectionMainCHS, FDefaultPayload, Payload, FRayTracingIntersectionAttributes, Attributes)` — stage: **closesthit** — C++: `FBasicIntersectionMainCHS` SF_RayHitGroup via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/RayTracing/RayTracingBasicShaders.cpp:13)
- L86-95 _entry_ `RAY_TRACING_ENTRY_CLOSEST_HIT(DefaultMainCHS, FDefaultPayload, Payload, FRayTracingIntersectionAttributes, Attributes)` — stage: **closesthit**
- L97-101 _entry_ `RAY_TRACING_ENTRY_ANY_HIT(DefaultOpaqueAHS, FDefaultPayload, Payload, FRayTracingIntersectionAttributes, Attributes)` — stage: **anyhit**
- L103-106 _entry_ `RAY_TRACING_ENTRY_MISS(DefaultPayloadMS, FDefaultPayload, Payload)` — stage: **miss** — C++: `FDefaultPayloadMS` SF_RayMiss via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/RenderCore/Private/BuiltInRayTracingShaders.cpp:32)
- L108-111 _entry_ `RAY_TRACING_ENTRY_MISS(PackedMaterialClosestHitPayloadMS, FPackedMaterialClosestHitPayload, Payload)` — stage: **miss** — C++: `FPackedMaterialClosestHitPayloadMS` SF_RayMiss via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/RenderCore/Private/BuiltInRayTracingShaders.cpp:33)

#### Global resources (textures / buffers / samplers) (4)

- L7 _resource_ `RaytracingAccelerationStructure TLAS;`
- L8 _resource_ `StructuredBuffer<FBasicRayData> Rays;`
- L9 _resource_ `RWStructuredBuffer<uint> OcclusionOutput;`
- L10 _resource_ `RWStructuredBuffer<FIntersectionPayload> IntersectionOutput;`

### `Shaders/Private/RayTracing/RayTracingCalcInterpolants.ush` (Private)

- lines: 140; parse: all-branches
- includes: L5 `../Barycentrics.ush`
- L3 #pragma `once`

#### Structs / classes (1)

- L7-16 _struct_ **`FRaytracingDerivatives`** `struct FRaytracingDerivatives`
  - L9 _member_ `TDual< float3 > WorldPosition;`
  - L10 _member_ `TDual< float3 > WorldGeoNormals;`
  - L11 _member_ `TDual< float4 > ScreenPosition;`
  - L14 _member_ `TDual< float2 > TexCoords[NUM_TEX_COORD_INTERPOLATORS];` _[#if NUM_TEX_COORD_INTERPOLATORS]_

#### Functions (4)

- L18-105 _function_ `void CalcInterpolants( in float4 SvPosition, in FRayCone RayCone, in FRayTracingIntersectionAttributes Attributes, inout FVertexFactoryInterpolantsVSToPS OutInterpolants, inout FRaytracingDerivatives OutDerivateData, inout float3 OutFaceNormal)`
- L107-111 _function_ `void CalcInterpolants(in FRayCone RayCone, in FRayTracingIntersectionAttributes Attributes, inout FVertexFactoryInterpolantsVSToPS OutInterpolants, inout float3 OutFaceNormal)`
- L114-119 _function_ `void CalcInterpolants(in FRayCone RayCone, in FRayTracingIntersectionAttributes Attributes, inout FVertexFactoryInterpolantsVSToPS OutInterpolants)` — simplified call when Geometric Normal is not needed
- L121-140 _function_ `void ApplyRaytracingDerivatives(inout FMaterialPixelParameters Out, in FRaytracingDerivatives In)`

### `Shaders/Private/RayTracing/RayTracingCapsuleLight.ush` (Private)

- lines: 53; parse: all-branches
- includes: L5 `../LightData.ush`, L6 `../CapsuleLightSampling.ush`
- L3 #pragma `once`

#### Functions (1)

- L8-52 _function_ `bool GenerateCapsuleLightOcclusionRayWithSolidAngleSampling( FLightShaderParameters LightParameters, float3 TranslatedWorldPosition, float3 WorldNormal, float2 RandSample, out float3 RayOrigin, out float3 RayDirection, out float RayTMin, out float RayTMax, out float RayPdf )`

### `Shaders/Private/RayTracing/RayTracingCommon.ush` (Private)

- lines: 1449; parse: all-branches
- includes: L13 `/Engine/Public/ShaderVersion.ush` [!defined(RAYTRACINGCOMMON_USH_INCLUDED)], L18 `../ShadingCommon.ush` [!defined(RAYTRACINGCOMMON_USH_INCLUDED)], L19 `../OctahedralCommon.ush` [!defined(RAYTRACINGCOMMON_USH_INCLUDED)], L20 `../SceneData.ush` [!defined(RAYTRACINGCOMMON_USH_INCLUDED)], L21 `../Common.ush` [!defined(RAYTRACINGCOMMON_USH_INCLUDED)], L23 `/Engine/Shared/RayTracingDefinitions.h` [!defined(RAYTRACINGCOMMON_USH_INCLUDED)], L24 `/Engine/Shared/RayTracingPayloadType.h` [!defined(RAYTRACINGCOMMON_USH_INCLUDED)], L25 `RayTracingRayCone.ush` [!defined(RAYTRACINGCOMMON_USH_INCLUDED)], L31 `../Substrate/Substrate.ush` [!defined(RAYTRACINGCOMMON_USH_INCLUDED)], L34 `/Platform/Private/RayTracing.ush` [!defined(RAYTRACINGCOMMON_USH_INCLUDED) && defined(OVERRIDE_RAYTRACING_USH)], L38 `/Engine/Private/RayTracing/RayTracingCommonMetal.ush` [!defined(RAYTRACINGCOMMON_USH_INCLUDED) && COMPILER_METAL], L372 `../PositionReconstructionCommon.ush` [!defined(RAYTRACINGCOMMON_USH_INCLUDED)], L1197 `TraceRayInline.ush` [!defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && COMPUTESHADER]

#### Macros (#define, 64)

- L10 `#define RAYTRACINGCOMMON_USH_INCLUDED ` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L28 `#define SUBSTRATE_INLINE_SHADING 1` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && SUBSTRATE_ENABLED && MATERIAL_IS_SUBSTRATE]_
- L64 `#define ALLOW_ALL_DXR_INTRINSICS 1` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L70 `#define DispatchRaysIndex() DispatchRaysIndex_is_only_supported_in_raygen_shaders` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !ALLOW_ALL_DXR_INTRINSICS && !RAYGENSHADER]_
- L71 `#define DispatchRaysDimensions() DispatchRaysDimensions_is_only_supported_in_raygen_shaders` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !ALLOW_ALL_DXR_INTRINSICS && !RAYGENSHADER]_
- L75 `#define RayTMin() RayTMin_is_not_supported` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !ALLOW_ALL_DXR_INTRINSICS]_
- L76 `#define RayFlags() RayFlags_is_not_supported` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !ALLOW_ALL_DXR_INTRINSICS]_
- L77 `#define GeometryIndex() GeometryIndex_is_not_supported` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !ALLOW_ALL_DXR_INTRINSICS]_
- L78 `#define ObjectRayOrigin() ObjectRayOrigin_is_not_supported` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !ALLOW_ALL_DXR_INTRINSICS]_
- L79 `#define ObjectRayDirection() ObjectRayDirection_is_not_supported` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !ALLOW_ALL_DXR_INTRINSICS]_
- L80 `#define ObjectToWorld3x4() ObjectToWorld3x4_is_not_supported` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !ALLOW_ALL_DXR_INTRINSICS]_
- L81 `#define ObjectToWorld4x3() ObjectToWorld4x3_is_not_supported` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !ALLOW_ALL_DXR_INTRINSICS]_
- L82 `#define WorldToObject3x4() WorldToObject3x4_is_not_supported` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !ALLOW_ALL_DXR_INTRINSICS]_
- L83 `#define WorldToObject4x3() WorldToObject4x3_is_not_supported` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !ALLOW_ALL_DXR_INTRINSICS]_
- L89 `#define RAY_TRACING_ENTRY_RAYGEN(name) [shader("raygeneration")] void name()` (2 lines) _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !defined(RAY_TRACING_ENTRY_RAYGEN)]_
- L94 `#define RAY_TRACING_ENTRY_INTERSECTION(name) [shader("intersection")] void name()` (2 lines) _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !defined(RAY_TRACING_ENTRY_INTERSECTION)]_
- L99 `#define RAY_TRACING_ENTRY_CLOSEST_HIT(name, payload_type, payload_name, attributes_type, attributes_name) [shader("closesthit")] void name(inout payload_type payload_name, in attributes_type attributes_name)` (2 lines) _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !defined(RAY_TRACING_ENTRY_CLOSEST_HIT)]_
- L104 `#define RAY_TRACING_ENTRY_ANY_HIT(name, payload_type, payload_name, attributes_type, attributes_name) [shader("anyhit")] void name(inout payload_type payload_name, in attributes_type attributes_name)` (2 lines) _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !defined(RAY_TRACING_ENTRY_ANY_HIT)]_
- L109 `#define RAY_TRACING_ENTRY_MISS(name, payload_type, payload_name) [shader("miss")] void name(inout payload_type payload_name)` (2 lines) _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !defined(RAY_TRACING_ENTRY_MISS)]_
- L114 `#define RAY_TRACING_ENTRY_CALLABLE(name, params_type, params_name) [shader("callable")] void name(inout params_type params_name)` (2 lines) _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !defined(RAY_TRACING_ENTRY_CALLABLE)]_
- L124 `#define RAY_TRACING_ENTRY_RAYGEN_OR_INLINE(name) void name##_INTERNAL(uint3 DispatchThreadIndex); [numthreads(INLINE_RAY_TRACING_THREAD_GROUP_SIZE_X, INLINE_RAY_TRACING_THREAD_GROUP_SIZE_Y, 1)] void name##CS(uint3 DispatchThreadIndex : SV_DispatchTh ...` (6 lines) _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !defined(RAY_TRACING_ENTRY_RAYGEN_OR_INLINE) && COMPUTESHADER && PLATFORM_SUPPORTS_INLINE_RAY_TRACING]_
- L133 `#define RAY_TRACING_ENTRY_RAYGEN_OR_INLINE(name) void name##_INTERNAL(uint3 DispatchThreadIndex); RAY_TRACING_ENTRY_RAYGEN(name##RGS){ name##_INTERNAL(DispatchRaysIndex());} void name##_INTERNAL(uint3 DispatchThreadIndex)` (5 lines) _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !defined(RAY_TRACING_ENTRY_RAYGEN_OR_INLINE) && !(COMPUTESHADER && PLATFORM_SUPPORTS_INLINE_RAY_TRACING)]_
- L146 `#define PLATFORM_RAYTRACING_INSTANCE_FLAG_NONE 0` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !defined(OVERRIDE_PLATFORM_RAYTRACING_INSTANCE_DESCRITOR)]_
- L147 `#define PLATFORM_RAYTRACING_INSTANCE_FLAG_TRIANGLE_CULL_DISABLE 0x1` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !defined(OVERRIDE_PLATFORM_RAYTRACING_INSTANCE_DESCRITOR)]_
- L148 `#define PLATFORM_RAYTRACING_INSTANCE_FLAG_TRIANGLE_FRONT_COUNTERCLOCKWISE 0x2` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !defined(OVERRIDE_PLATFORM_RAYTRACING_INSTANCE_DESCRITOR)]_
- L149 `#define PLATFORM_RAYTRACING_INSTANCE_FLAG_FORCE_OPAQUE 0x4` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !defined(OVERRIDE_PLATFORM_RAYTRACING_INSTANCE_DESCRITOR)]_
- L150 `#define PLATFORM_RAYTRACING_INSTANCE_FLAG_FORCE_NON_OPAQUE 0x8` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !defined(OVERRIDE_PLATFORM_RAYTRACING_INSTANCE_DESCRITOR)]_
- L155 `#define RAYTRACING_INSTANCE_FLAG_NONE 0` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L156 `#define RAYTRACING_INSTANCE_FLAG_TRIANGLE_CULL_DISABLE (1 << 1)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L157 `#define RAYTRACING_INSTANCE_FLAG_TRIANGLE_CULL_REVERSE (1 << 2)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L158 `#define RAYTRACING_INSTANCE_FLAG_FORCE_OPAQUE (1 << 3)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L159 `#define RAYTRACING_INSTANCE_FLAG_FORCE_NON_OPAQUE (1 << 4)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L161 `#define RAY_TRACING_BLEND_MODE_OPAQUE 0` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L162 `#define RAY_TRACING_BLEND_MODE_ALPHA_COMPOSITE 1` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L163 `#define RAY_TRACING_BLEND_MODE_TRANSLUCENT 2` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L164 `#define RAY_TRACING_BLEND_MODE_ADDITIVE 3` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L165 `#define RAY_TRACING_BLEND_MODE_MODULATE 4` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L166 `#define RAY_TRACING_BLEND_MODE_ALPHA_HOLDOUT 5` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L173 `#define RAY_TRACING_PAYLOAD_OUTPUT_FLAG_NONE 0` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L174 `#define RAY_TRACING_PAYLOAD_OUTPUT_FLAG_FRONT_FACE (1 << 0)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L175 `#define RAY_TRACING_PAYLOAD_OUTPUT_FLAG_TWO_SIDED (1 << 1)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L176 `#define RAY_TRACING_PAYLOAD_OUTPUT_FLAG_IS_HOLDOUT (1 << 2)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L177 `#define RAY_TRACING_PAYLOAD_OUTPUT_FLAG_HAS_INDIRECT_LIGHTING (1 << 3)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L178 `#define RAY_TRACING_PAYLOAD_OUTPUT_FLAG_UNUSED4 (1 << 4)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L179 `#define RAY_TRACING_PAYLOAD_OUTPUT_FLAG_UNUSED5 (1 << 5)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L181 `#define RAY_TRACING_PAYLOAD_INPUT_FLAG_NONE 0` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L182 `#define RAY_TRACING_PAYLOAD_INPUT_FLAG_MINIMAL_PAYLOAD (1 << 0)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L183 `#define RAY_TRACING_PAYLOAD_INPUT_FLAG_ENABLE_SKY_LIGHT_CONTRIBUTION (1 << 1)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L184 `#define RAY_TRACING_PAYLOAD_INPUT_FLAG_LUMEN_PAYLOAD (1 << 2)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L185 `#define RAY_TRACING_PAYLOAD_INPUT_FLAG_IGNORE_TRANSLUCENT (1 << 3)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L186 `#define RAY_TRACING_PAYLOAD_INPUT_FLAG_SHADOW_RAY (1 << 4)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L187 `#define RAY_TRACING_PAYLOAD_INPUT_FLAG_CAMERA_RAY (1 << 5)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L188 `#define RAY_TRACING_PAYLOAD_INPUT_FLAG_INDIRECT_LIGHTING_RAY (1 << 6)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L189 `#define RAY_TRACING_PAYLOAD_INPUT_FLAG_UNUSED (1 << 7)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L195 `#define OVERRIDE_PLATFORM_RAYTRACING_INSTANCE_DESCRITOR ` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !defined(OVERRIDE_PLATFORM_RAYTRACING_INSTANCE_DESCRITOR)]_
- L323 `#define RAY_TRACING_DEFERRED_MATERIAL_KEY_INVALID 0xFFFFFFFF` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L324 `#define RAY_TRACING_DEFERRED_MATERIAL_KEY_RAY_MISS 0xFFFFFFFE` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L337 `#define RAY_TRACING_SUPPORT_CUSTOM_UINT_IN_INTERSECTION_ATTRIBUTES 0` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !defined(RAY_TRACING_SUPPORT_CUSTOM_UINT_IN_INTERSECTION_ATTRIBUTES)]_
- L473 `#define RAY_DEFAULT_T_MAX (FLOAT_MAX)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L1116 `#define DECAL_WRITE_BASE_COLOR_FLAG (1 << 0)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L1117 `#define DECAL_WRITE_NORMAL_FLAG (1 << 1)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L1118 `#define DECAL_WRITE_ROUGHNESS_SPECULAR_METALLIC_FLAG (1 << 2)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L1119 `#define DECAL_WRITE_EMISSIVE_FLAG (1 << 3)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L1121 `#define DECAL_USE_REVERSE_CULLING 1` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L7 #pragma `once`; L16 #pragma `message("UESHADERMETADATA_VERSION 82EF3461-600F-45F4-94A7-F2D9EF032386")`

#### Structs / classes (16)

- L198-224 _struct_ **`FPlatformRayTracingInstanceDescriptor`** `struct FPlatformRayTracingInstanceDescriptor` — Must match D3D12_RAYTRACING_INSTANCE_DESC / VkAccelerationStructureInstanceKHR _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !defined(OVERRIDE_PLATFORM_RAYTRACING_INSTANCE_DESCRITOR)]_
  - L200 _member_ `float3x4 Transform;` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !defined(OVERRIDE_PLATFORM_RAYTRACING_INSTANCE_DESCRITOR)]_
  - L201 _member_ `uint InstanceIdAndMask;` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !defined(OVERRIDE_PLATFORM_RAYTRACING_INSTANCE_DESCRITOR)]_
  - L202 _member_ `uint InstanceContributionToHitGroupIndexAndFlags;` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !defined(OVERRIDE_PLATFORM_RAYTRACING_INSTANCE_DESCRITOR)]_
  - L203 _member_ `uint2 AccelerationStructure;` — uint64 _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !defined(OVERRIDE_PLATFORM_RAYTRACING_INSTANCE_DESCRITOR)]_
  - L205 _method_ `uint GetInstanceId()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !defined(OVERRIDE_PLATFORM_RAYTRACING_INSTANCE_DESCRITOR)]_
  - L210 _method_ `uint GetMask()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !defined(OVERRIDE_PLATFORM_RAYTRACING_INSTANCE_DESCRITOR)]_
  - L215 _method_ `uint GetInstanceContributionToHitGroupIndex()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !defined(OVERRIDE_PLATFORM_RAYTRACING_INSTANCE_DESCRITOR)]_
  - L220 _method_ `uint GetFlags()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !defined(OVERRIDE_PLATFORM_RAYTRACING_INSTANCE_DESCRITOR)]_
- L269-273 _struct_ **`FTriangleBaseAttributes`** `struct FTriangleBaseAttributes` — Indices and vertex positions of the ray tracing geometry triangle. Used for loading and interpolation of per-vertex attributes and computing per-triangle normals. _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
  - L271 _member_ `uint3 Indices;` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
  - L272 _member_ `float3 LocalPositions[3];` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L275-281 _struct_ **`FBasicRayData`** `struct FBasicRayData` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
  - L277 _member_ `float3 Origin;` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
  - L278 _member_ `uint Mask;` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
  - L279 _member_ `float3 Direction;` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
  - L280 _member_ `float TFar;` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L283-291 _struct_ **`FMinimalPayload`** `struct FMinimalPayload` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
  - L285 _member_ `float HitT;` — Distance from ray origin to the intersection point in the ray direction. Negative on miss. _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
  - L287 _method_ `bool IsMiss()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
  - L288 _method_ `bool IsHit()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
  - L290 _method_ `void SetMiss()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L296-301 _struct_ **`FIntersectionPayload`** `struct FIntersectionPayload : FMinimalPayload` — base/reg: `FMinimalPayload` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
  - L298 _member_ `uint PrimitiveIndex;` — Index of the primitive within the geometry inside the bottom-level acceleration structure instance. Undefined on miss. _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
  - L299 _member_ `uint InstanceIndex;` — Index of the current instance in the top-level structure. Undefined on miss. _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
  - L300 _member_ `float2 Barycentrics;` — Primitive barycentric coordinates of the intersection point. Undefined on miss. _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L303-306 _struct_ **`FDefaultPayload`** `struct FDefaultPayload : FIntersectionPayload` — base/reg: `FIntersectionPayload` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
  - L305 _member_ `uint InstanceID;` — Value of FRayTracingGeometryInstance::UserData. Undefined on miss. _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L313-319 _struct_ **`FVFXTracePayload`** `struct FVFXTracePayload : FMinimalPayload` — base/reg: `FMinimalPayload` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_VFX)]_
  - L315 _member_ `uint GPUSceneInstanceId;` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_VFX)]_
  - L316 _member_ `float2 Barycentrics;` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_VFX)]_
  - L317 _member_ `float3 TranslatedWorldPosition;` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_VFX)]_
  - L318 _member_ `float3 WorldNormal;` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_VFX)]_
- L326-330 _struct_ **`FDeferredMaterialPayload`** `struct FDeferredMaterialPayload : FMinimalPayload` — base/reg: `FMinimalPayload` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
  - L328 _member_ `uint SortKey;` — MaterialID by default _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
  - L329 _member_ `uint PixelCoordinates;` — X in low 16 bits, Y in high 16 bits _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L340-369 _struct_ **`FRayTracingIntersectionAttributes`** `struct FRayTracingIntersectionAttributes` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
  - L342 _member_ `uint2 PackedData;` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
  - L344 _method_ `float2 GetBarycentrics()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
  - L353 _method_ `void SetBarycentrics(float2 Barycentrics)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
  - L363 _method_ `void SetCustomData(uint Data)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && RAY_TRACING_SUPPORT_CUSTOM_UINT_IN_INTERSECTION_ATTRIBUTES]_
- L477-493 _struct_ **`FRayDesc`** `struct FRayDesc` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING]_
  - L479 _member_ `float3 Origin;` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING]_
  - L480 _member_ `float TMin;` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING]_
  - L481 _member_ `float3 Direction;` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING]_
  - L482 _member_ `float TMax;` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING]_
  - L484 _method_ `RayDesc GetNativeDesc()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING]_
- L592-630 _struct_ **`FMaterialClosestHitPayload`** `struct FMaterialClosestHitPayload : FMinimalPayload` — base/reg: `FMinimalPayload` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L595 _member_ `FRayCone RayCone;` — float FMinimalPay	// float FMinimalPayload::HitT _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L596 _member_ `float3 Radiance;` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L597 _member_ `float IorOverride;` — If >= 0, the material overridden IOR value _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L598 _member_ `float3 WorldNormal;` — Top Layer Normal _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L599 _member_ `float Opacity;` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L600 _member_ `float3 TransmittancePreCoverage;` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L601 _member_ `uint BlendingMode;` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L602 _member_ `uint PrimitiveLightingChannelMask;` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L603 _member_ `float3 IndirectIrradiance;` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L604 _member_ `uint ShadingModelID;` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L605 _member_ `float3 RayDirection;` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L606 _member_ `bool bIsThinSurface;` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L611 _member_ `float3 TranslatedWorldPos;` — Quite some code assume FRayHitInfo has a WorldPos So keep it here and force to re-construct it in Unpack call using ray information. It is not packed in FRayHitInfoPacked _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L612 _member_ `uint Flags;` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L613 _member_ `FSubstrateRaytracingPayload SubstrateData;` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L615 _method_ `void SetFrontFace()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L616 _method_ `bool IsFrontFace()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L618 _method_ `void SetTwoSided()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L619 _method_ `bool IsTwoSided()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L621 _method_ `void SetHoldout()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L622 _method_ `bool IsHoldout()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L624 _method_ `void SetHasIndirectLighting()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L625 _method_ `bool HasIndirectLighting()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L627 _method_ `FRayCone GetRayCone()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L628 _method_ `void SetRayCone(FRayCone In)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L629 _method_ `float3 GetRayDirection()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L803 _member_ `FRayCone RayCone;` — Unpacked  Packed offset    bytes float FMinimalPayload::HitT		// 0         4       32bits _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L804 _member_ `float3 Radiance;` — 8         6       48bits _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L805 _member_ `float3 WorldNormal;` — 24        6       48bits _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L806 _member_ `float3 BaseColor;` — 36        6       48bits _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L807 _member_ `float3 DiffuseColor;` — 48        0       (derived) _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L808 _member_ `float3 SpecularColor;` — 60        0       (derived) _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L809 _member_ `float Opacity;` — 72        2       16bits _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L810 _member_ `float Metallic;` — 76        1       8bits _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L811 _member_ `float Specular;` — 80        1       8bits _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L812 _member_ `float Roughness;` — 84        2       16bits _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L813 _member_ `float Ior;` — 88        2       16bits _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L814 _member_ `uint ShadingModelID;` — 92        1       4bits _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L815 _member_ `uint BlendingMode;` — 96        0       3bits (packed with ShadingModelID) _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L816 _member_ `uint PrimitiveLightingChannelMask;` — 100       0       3bits (packed with ShadingModelID) _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L817 _member_ `float4 CustomData;` — 104       4       32bits _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L818 _member_ `float GBufferAO;` — 120       0       (removed) _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L819 _member_ `float3 IndirectIrradiance;` — 124       0       48bits -- gbuffer only has float payload and there are truncation HLSL warnings _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L824 _member_ `float3 TranslatedWorldPos;` — Quite some code assume FRayHitInfo has a WorldPos So keep it here and force to re-construct it in Unpack call using ray information. It is not packed in FRayHitInfoPacked _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L825 _member_ `uint Flags;` — 148       0       6bits (packed with ShadingModelID) _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L826 _member_ `float3 WorldTangent;` — 152       6       48bits _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L827 _member_ `float Anisotropy;` — 164       2       16bits (packed with WorldTangent) _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L830 _method_ `void SetFrontFace()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L831 _method_ `bool IsFrontFace()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L833 _method_ `void SetTwoSided()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L834 _method_ `bool IsTwoSided()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L836 _method_ `void SetHoldout()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L837 _method_ `bool IsHoldout()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L839 _method_ `FRayCone GetRayCone()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L840 _method_ `void SetRayCone(FRayCone NewRayCone)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L842 _method_ `bool HasAnisotropy()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L844 _method_ `float3 GetRayDirection()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
- L632-756 _struct_ **`FPackedMaterialClosestHitPayload`** `struct FPackedMaterialClosestHitPayload : FMinimalPayload` — base/reg: `FMinimalPayload` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L639 _member_ `uint PackedRayCone;` — float FMinimalPayload::HitT                       // 4  bytes _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L640 _member_ `uint Flags;` — 4  bytes (see layout above) _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L641 _member_ `uint TransmittancePreCoverage;` — 4  bytes _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L642 _member_ `uint Radiance;` — 4  bytes _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L643 _member_ `uint PackedGeometryNormal;` — 4  bytes _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L644 _member_ `uint SceneInstanceIndex;` — 4  bytes - GPUSceneInstanceIndex _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L646 _member_ `FSubstrateRaytracingPayload SubstrateData;` — =28 bytes - must be in sync with InternalGetRayTracingMaterialPayloadSizeInBytes() _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L649 _method_ `void SetMinimalPayloadMode()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L650 _method_ `bool IsMinimalPayloadMode()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L652 _method_ `void SetEnableSkyLightContribution()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L653 _method_ `bool IsEnableSkyLightContribution()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L655 _method_ `void SetLumenPayload()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L656 _method_ `bool IsLumenPayload()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L658 _method_ `void SetIgnoreTranslucentMaterials()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L659 _method_ `bool IsIgnoreTranslucentMaterials()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L661 _method_ `void SetShadowRay()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L662 _method_ `bool IsShadowRay()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L664 _method_ `void SetCameraRay()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L665 _method_ `bool IsCameraRay()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L667 _method_ `void SetIndirectLightingRay()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L668 _method_ `bool IsIndirectLightingRay()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L670 _method_ `FRayCone GetRayCone()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L671 _method_ `void SetRayCone(FRayCone NewRayCone)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L673 _method_ `float GetMipBias()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L674 _method_ `void SetMipBias(float NewMipBias)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L676 _method_ `void SetRadiance(in float3 In)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L677 _method_ `float3 GetRadiance()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L680 _method_ `void SetIndirectIrradiance(float3 In)` — For now we use the last material data slot to store the indirect irradiance in order to not increase the payload over 64bytes _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L681 _method_ `float3 GetIndirectIrradiance()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L683 _method_ `float3 GetWorldNormal()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L685 _method_ `void SetGeometryNormal(float3 GeometryNormal)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L690 _method_ `float3 GetGeometryNormal()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L695 _method_ `float3 GetShadowVisibility()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L700 _method_ `void SetShadowVisibility(float3 ShadowVisibility)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L705 _method_ `uint GetLightIndex()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L710 _method_ `void SetLightIndex(uint LightIndex)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L715 _method_ `bool IsValid()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L716 _method_ `uint GetShadingModelID()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L717 _method_ `uint GetFlags()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L718 _method_ `bool IsTwoSided()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L719 _method_ `bool IsFrontFace()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L720 _method_ `uint GetBlendingMode()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L721 _method_ `uint GetPrimitiveLightingChannelMask()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L722 _method_ `bool IsThinSurface()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L723 _method_ `float GetOpacity()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L724 _method_ `float3 GetTransmittancePreCoverage()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L726 _method_ `void SetFlags(uint In)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L727 _method_ `void SetBlendingMode(uint In)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L728 _method_ `void SetPrimitiveLightingChannelMask(uint In)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L729 _method_ `void SetIsThinSurface(bool In)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L730 _method_ `void SetOpacity(float In)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L731 _method_ `void SetTransmittancePreCoverage(float3 In)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L733 _method_ `void SetRayDirection(float3 In)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L734 _method_ `float3 GetRayDirection()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L737 _method_ `void SetSceneInstanceIndex(uint In)` — Member function for (IsLumenPayload() == 1) _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L738 _method_ `int GetSceneInstanceIndex()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L740 _method_ `void SetRandom(float E)` — SceneInstanceIndex is not used in hit group shaders so reuse it to pass a random number _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L741 _method_ `float GetRandom()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L745 _method_ `float3 GetWorldTangent()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1 && SUBSTRATE_LEGACY_REFLECTION_API]_
  - L746 _method_ `float3 GetBaseColor()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1 && SUBSTRATE_LEGACY_REFLECTION_API]_
  - L747 _method_ `float4 GetCustomData()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1 && SUBSTRATE_LEGACY_REFLECTION_API]_
  - L748 _method_ `float GetMetallic()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1 && SUBSTRATE_LEGACY_REFLECTION_API]_
  - L749 _method_ `float GetSpecular()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1 && SUBSTRATE_LEGACY_REFLECTION_API]_
  - L750 _method_ `float GetRoughness()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1 && SUBSTRATE_LEGACY_REFLECTION_API]_
  - L751 _method_ `float GetIor()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1 && SUBSTRATE_LEGACY_REFLECTION_API]_
  - L752 _method_ `float GetAnisotropy()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1 && SUBSTRATE_LEGACY_REFLECTION_API]_
  - L753 _method_ `float3 GetDiffuseColor()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1 && SUBSTRATE_LEGACY_REFLECTION_API]_
  - L754 _method_ `float3 GetSpecularColor()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1 && SUBSTRATE_LEGACY_REFLECTION_API]_
  - L851 _member_ `uint PackedRayCone;` — 4 bytes (fp16 width, fp16 spread) _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L855 _member_ `uint FlagsAndMipBias;` — 8 bits - MipBias 8 bits - Flags 16 bits - Unused _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L857 _member_ `uint RadianceAndNormal[3];` — 12 bytes _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L858 _member_ `uint BaseColorAndOpacity[2];` — 8  bytes _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L859 _member_ `uint MetallicAndSpecularAndRoughness;` — 4  bytes _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L865 _member_ `uint IorAndShadingModelIDAndBlendingModeAndPrimitiveLightingChannelMask;` — 16 bits - IOR 4 bits - Shading Model Id 3 bits - Blending Mode 6 bits - Unused 3 bits - Lighting Channel Mask _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L866 _member_ `uint PackedIndirectIrradiance[2];` — 8  bytes _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L867 _member_ `uint PackedCustomData;` — 4  bytes _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L868 _member_ `uint WorldTangentAndAnisotropy[2];` — 8  bytes _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L869 _member_ `uint PackedGeometryNormal;` — 4  bytes _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L872 _method_ `void SetMinimalPayloadMode()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L873 _method_ `bool IsMinimalPayloadMode()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L875 _method_ `void SetEnableSkyLightContribution()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L876 _method_ `bool IsEnableSkyLightContribution()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L878 _method_ `void SetLumenPayload()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L879 _method_ `bool IsLumenPayload()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L881 _method_ `void SetIgnoreTranslucentMaterials()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L882 _method_ `bool IsIgnoreTranslucentMaterials()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L884 _method_ `void SetShadowRay()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L885 _method_ `bool IsShadowRay()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L887 _method_ `void SetCameraRay()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L888 _method_ `bool IsCameraRay()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L890 _method_ `void SetIndirectLightingRay()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L891 _method_ `bool IsIndirectLightingRay()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L893 _method_ `FRayCone GetRayCone()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L894 _method_ `void SetRayCone(FRayCone NewRayCone)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L896 _method_ `float GetMipBias()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L897 _method_ `void SetMipBias(float NewMipBias)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L899 _method_ `void SetRadiance(in float3 InRadiance)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L906 _method_ `float3 GetRadiance()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L915 _method_ `void SetIndirectIrradiance(float3 InIndirectIrradiance)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L922 _method_ `float3 GetIndirectIrradiance()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L932 _method_ `void SetRayDirection(float3 In)` — Alias IndirectIrradiance for storing ray direction _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L933 _method_ `float3 GetRayDirection()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L935 _method_ `float3 GetWorldNormal()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L944 _method_ `float4 GetCustomData()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L955 _method_ `float3 GetBaseColor()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L964 _method_ `float3 GetWorldTangent()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L973 _method_ `float3 GetShadowVisibility()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L978 _method_ `void SetShadowVisibility(float3 ShadowVisibility)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L983 _method_ `uint GetLightIndex()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L988 _method_ `void SetLightIndex(uint LightIndex)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L994 _method_ `float GetOpacity()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L995 _method_ `void SetOpacity(float Opacity)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L996 _method_ `float GetMetallic()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L997 _method_ `float GetSpecular()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L998 _method_ `float GetRoughness()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L999 _method_ `float GetIor()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L1000 _method_ `uint GetShadingModelID()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L1001 _method_ `uint GetBlendingMode()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L1002 _method_ `uint GetFlags()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L1003 _method_ `void SetFlags(uint Flags)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L1004 _method_ `bool IsTwoSided()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L1005 _method_ `bool IsFrontFace()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L1006 _method_ `uint GetPrimitiveLightingChannelMask()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L1007 _method_ `float GetAnisotropy()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L1008 _method_ `bool IsValid()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L1010 _method_ `float3 GetDiffuseColor()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L1011 _method_ `float3 GetSpecularColor()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L1014 _method_ `void SetSceneInstanceIndex(uint GPUSceneInstanceIndex)` — Member function for (IsLumenPayload() == 1) _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L1020 _method_ `void SetGeometryNormal(float3 GeometryNormal)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L1025 _method_ `float3 GetGeometryNormal()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L1030 _method_ `int GetSceneInstanceIndex()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L1033 _method_ `void SetRandom(float E)` — SceneInstanceIndex is not used in hit group shaders so reuse it to pass a random number _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L1034 _method_ `float GetRandom()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
- L798-845 _struct_ **`FMaterialClosestHitPayload`** `struct FMaterialClosestHitPayload : FMinimalPayload` — base/reg: `FMinimalPayload` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L595 _member_ `FRayCone RayCone;` — float FMinimalPay	// float FMinimalPayload::HitT _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L596 _member_ `float3 Radiance;` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L597 _member_ `float IorOverride;` — If >= 0, the material overridden IOR value _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L598 _member_ `float3 WorldNormal;` — Top Layer Normal _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L599 _member_ `float Opacity;` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L600 _member_ `float3 TransmittancePreCoverage;` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L601 _member_ `uint BlendingMode;` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L602 _member_ `uint PrimitiveLightingChannelMask;` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L603 _member_ `float3 IndirectIrradiance;` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L604 _member_ `uint ShadingModelID;` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L605 _member_ `float3 RayDirection;` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L606 _member_ `bool bIsThinSurface;` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L611 _member_ `float3 TranslatedWorldPos;` — Quite some code assume FRayHitInfo has a WorldPos So keep it here and force to re-construct it in Unpack call using ray information. It is not packed in FRayHitInfoPacked _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L612 _member_ `uint Flags;` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L613 _member_ `FSubstrateRaytracingPayload SubstrateData;` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L615 _method_ `void SetFrontFace()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L616 _method_ `bool IsFrontFace()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L618 _method_ `void SetTwoSided()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L619 _method_ `bool IsTwoSided()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L621 _method_ `void SetHoldout()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L622 _method_ `bool IsHoldout()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L624 _method_ `void SetHasIndirectLighting()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L625 _method_ `bool HasIndirectLighting()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L627 _method_ `FRayCone GetRayCone()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L628 _method_ `void SetRayCone(FRayCone In)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L629 _method_ `float3 GetRayDirection()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L803 _member_ `FRayCone RayCone;` — Unpacked  Packed offset    bytes float FMinimalPayload::HitT		// 0         4       32bits _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L804 _member_ `float3 Radiance;` — 8         6       48bits _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L805 _member_ `float3 WorldNormal;` — 24        6       48bits _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L806 _member_ `float3 BaseColor;` — 36        6       48bits _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L807 _member_ `float3 DiffuseColor;` — 48        0       (derived) _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L808 _member_ `float3 SpecularColor;` — 60        0       (derived) _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L809 _member_ `float Opacity;` — 72        2       16bits _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L810 _member_ `float Metallic;` — 76        1       8bits _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L811 _member_ `float Specular;` — 80        1       8bits _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L812 _member_ `float Roughness;` — 84        2       16bits _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L813 _member_ `float Ior;` — 88        2       16bits _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L814 _member_ `uint ShadingModelID;` — 92        1       4bits _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L815 _member_ `uint BlendingMode;` — 96        0       3bits (packed with ShadingModelID) _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L816 _member_ `uint PrimitiveLightingChannelMask;` — 100       0       3bits (packed with ShadingModelID) _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L817 _member_ `float4 CustomData;` — 104       4       32bits _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L818 _member_ `float GBufferAO;` — 120       0       (removed) _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L819 _member_ `float3 IndirectIrradiance;` — 124       0       48bits -- gbuffer only has float payload and there are truncation HLSL warnings _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L824 _member_ `float3 TranslatedWorldPos;` — Quite some code assume FRayHitInfo has a WorldPos So keep it here and force to re-construct it in Unpack call using ray information. It is not packed in FRayHitInfoPacked _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L825 _member_ `uint Flags;` — 148       0       6bits (packed with ShadingModelID) _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L826 _member_ `float3 WorldTangent;` — 152       6       48bits _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L827 _member_ `float Anisotropy;` — 164       2       16bits (packed with WorldTangent) _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L830 _method_ `void SetFrontFace()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L831 _method_ `bool IsFrontFace()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L833 _method_ `void SetTwoSided()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L834 _method_ `bool IsTwoSided()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L836 _method_ `void SetHoldout()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L837 _method_ `bool IsHoldout()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L839 _method_ `FRayCone GetRayCone()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L840 _method_ `void SetRayCone(FRayCone NewRayCone)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L842 _method_ `bool HasAnisotropy()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L844 _method_ `float3 GetRayDirection()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
- L847-1035 _struct_ **`FPackedMaterialClosestHitPayload`** `struct FPackedMaterialClosestHitPayload : FMinimalPayload` — base/reg: `FMinimalPayload` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L639 _member_ `uint PackedRayCone;` — float FMinimalPayload::HitT                       // 4  bytes _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L640 _member_ `uint Flags;` — 4  bytes (see layout above) _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L641 _member_ `uint TransmittancePreCoverage;` — 4  bytes _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L642 _member_ `uint Radiance;` — 4  bytes _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L643 _member_ `uint PackedGeometryNormal;` — 4  bytes _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L644 _member_ `uint SceneInstanceIndex;` — 4  bytes - GPUSceneInstanceIndex _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L646 _member_ `FSubstrateRaytracingPayload SubstrateData;` — =28 bytes - must be in sync with InternalGetRayTracingMaterialPayloadSizeInBytes() _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L649 _method_ `void SetMinimalPayloadMode()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L650 _method_ `bool IsMinimalPayloadMode()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L652 _method_ `void SetEnableSkyLightContribution()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L653 _method_ `bool IsEnableSkyLightContribution()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L655 _method_ `void SetLumenPayload()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L656 _method_ `bool IsLumenPayload()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L658 _method_ `void SetIgnoreTranslucentMaterials()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L659 _method_ `bool IsIgnoreTranslucentMaterials()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L661 _method_ `void SetShadowRay()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L662 _method_ `bool IsShadowRay()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L664 _method_ `void SetCameraRay()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L665 _method_ `bool IsCameraRay()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L667 _method_ `void SetIndirectLightingRay()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L668 _method_ `bool IsIndirectLightingRay()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L670 _method_ `FRayCone GetRayCone()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L671 _method_ `void SetRayCone(FRayCone NewRayCone)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L673 _method_ `float GetMipBias()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L674 _method_ `void SetMipBias(float NewMipBias)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L676 _method_ `void SetRadiance(in float3 In)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L677 _method_ `float3 GetRadiance()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L680 _method_ `void SetIndirectIrradiance(float3 In)` — For now we use the last material data slot to store the indirect irradiance in order to not increase the payload over 64bytes _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L681 _method_ `float3 GetIndirectIrradiance()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L683 _method_ `float3 GetWorldNormal()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L685 _method_ `void SetGeometryNormal(float3 GeometryNormal)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L690 _method_ `float3 GetGeometryNormal()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L695 _method_ `float3 GetShadowVisibility()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L700 _method_ `void SetShadowVisibility(float3 ShadowVisibility)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L705 _method_ `uint GetLightIndex()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L710 _method_ `void SetLightIndex(uint LightIndex)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L715 _method_ `bool IsValid()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L716 _method_ `uint GetShadingModelID()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L717 _method_ `uint GetFlags()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L718 _method_ `bool IsTwoSided()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L719 _method_ `bool IsFrontFace()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L720 _method_ `uint GetBlendingMode()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L721 _method_ `uint GetPrimitiveLightingChannelMask()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L722 _method_ `bool IsThinSurface()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L723 _method_ `float GetOpacity()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L724 _method_ `float3 GetTransmittancePreCoverage()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L726 _method_ `void SetFlags(uint In)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L727 _method_ `void SetBlendingMode(uint In)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L728 _method_ `void SetPrimitiveLightingChannelMask(uint In)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L729 _method_ `void SetIsThinSurface(bool In)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L730 _method_ `void SetOpacity(float In)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L731 _method_ `void SetTransmittancePreCoverage(float3 In)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L733 _method_ `void SetRayDirection(float3 In)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L734 _method_ `float3 GetRayDirection()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L737 _method_ `void SetSceneInstanceIndex(uint In)` — Member function for (IsLumenPayload() == 1) _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L738 _method_ `int GetSceneInstanceIndex()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L740 _method_ `void SetRandom(float E)` — SceneInstanceIndex is not used in hit group shaders so reuse it to pass a random number _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L741 _method_ `float GetRandom()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
  - L745 _method_ `float3 GetWorldTangent()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1 && SUBSTRATE_LEGACY_REFLECTION_API]_
  - L746 _method_ `float3 GetBaseColor()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1 && SUBSTRATE_LEGACY_REFLECTION_API]_
  - L747 _method_ `float4 GetCustomData()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1 && SUBSTRATE_LEGACY_REFLECTION_API]_
  - L748 _method_ `float GetMetallic()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1 && SUBSTRATE_LEGACY_REFLECTION_API]_
  - L749 _method_ `float GetSpecular()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1 && SUBSTRATE_LEGACY_REFLECTION_API]_
  - L750 _method_ `float GetRoughness()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1 && SUBSTRATE_LEGACY_REFLECTION_API]_
  - L751 _method_ `float GetIor()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1 && SUBSTRATE_LEGACY_REFLECTION_API]_
  - L752 _method_ `float GetAnisotropy()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1 && SUBSTRATE_LEGACY_REFLECTION_API]_
  - L753 _method_ `float3 GetDiffuseColor()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1 && SUBSTRATE_LEGACY_REFLECTION_API]_
  - L754 _method_ `float3 GetSpecularColor()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1 && SUBSTRATE_LEGACY_REFLECTION_API]_
  - L851 _member_ `uint PackedRayCone;` — 4 bytes (fp16 width, fp16 spread) _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L855 _member_ `uint FlagsAndMipBias;` — 8 bits - MipBias 8 bits - Flags 16 bits - Unused _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L857 _member_ `uint RadianceAndNormal[3];` — 12 bytes _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L858 _member_ `uint BaseColorAndOpacity[2];` — 8  bytes _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L859 _member_ `uint MetallicAndSpecularAndRoughness;` — 4  bytes _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L865 _member_ `uint IorAndShadingModelIDAndBlendingModeAndPrimitiveLightingChannelMask;` — 16 bits - IOR 4 bits - Shading Model Id 3 bits - Blending Mode 6 bits - Unused 3 bits - Lighting Channel Mask _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L866 _member_ `uint PackedIndirectIrradiance[2];` — 8  bytes _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L867 _member_ `uint PackedCustomData;` — 4  bytes _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L868 _member_ `uint WorldTangentAndAnisotropy[2];` — 8  bytes _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L869 _member_ `uint PackedGeometryNormal;` — 4  bytes _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L872 _method_ `void SetMinimalPayloadMode()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L873 _method_ `bool IsMinimalPayloadMode()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L875 _method_ `void SetEnableSkyLightContribution()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L876 _method_ `bool IsEnableSkyLightContribution()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L878 _method_ `void SetLumenPayload()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L879 _method_ `bool IsLumenPayload()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L881 _method_ `void SetIgnoreTranslucentMaterials()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L882 _method_ `bool IsIgnoreTranslucentMaterials()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L884 _method_ `void SetShadowRay()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L885 _method_ `bool IsShadowRay()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L887 _method_ `void SetCameraRay()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L888 _method_ `bool IsCameraRay()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L890 _method_ `void SetIndirectLightingRay()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L891 _method_ `bool IsIndirectLightingRay()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L893 _method_ `FRayCone GetRayCone()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L894 _method_ `void SetRayCone(FRayCone NewRayCone)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L896 _method_ `float GetMipBias()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L897 _method_ `void SetMipBias(float NewMipBias)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L899 _method_ `void SetRadiance(in float3 InRadiance)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L906 _method_ `float3 GetRadiance()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L915 _method_ `void SetIndirectIrradiance(float3 InIndirectIrradiance)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L922 _method_ `float3 GetIndirectIrradiance()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L932 _method_ `void SetRayDirection(float3 In)` — Alias IndirectIrradiance for storing ray direction _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L933 _method_ `float3 GetRayDirection()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L935 _method_ `float3 GetWorldNormal()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L944 _method_ `float4 GetCustomData()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L955 _method_ `float3 GetBaseColor()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L964 _method_ `float3 GetWorldTangent()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L973 _method_ `float3 GetShadowVisibility()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L978 _method_ `void SetShadowVisibility(float3 ShadowVisibility)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L983 _method_ `uint GetLightIndex()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L988 _method_ `void SetLightIndex(uint LightIndex)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L994 _method_ `float GetOpacity()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L995 _method_ `void SetOpacity(float Opacity)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L996 _method_ `float GetMetallic()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L997 _method_ `float GetSpecular()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L998 _method_ `float GetRoughness()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L999 _method_ `float GetIor()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L1000 _method_ `uint GetShadingModelID()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L1001 _method_ `uint GetBlendingMode()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L1002 _method_ `uint GetFlags()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L1003 _method_ `void SetFlags(uint Flags)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L1004 _method_ `bool IsTwoSided()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L1005 _method_ `bool IsFrontFace()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L1006 _method_ `uint GetPrimitiveLightingChannelMask()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L1007 _method_ `float GetAnisotropy()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L1008 _method_ `bool IsValid()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L1010 _method_ `float3 GetDiffuseColor()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L1011 _method_ `float3 GetSpecularColor()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L1014 _method_ `void SetSceneInstanceIndex(uint GPUSceneInstanceIndex)` — Member function for (IsLumenPayload() == 1) _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L1020 _method_ `void SetGeometryNormal(float3 GeometryNormal)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L1025 _method_ `float3 GetGeometryNormal()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L1030 _method_ `int GetSceneInstanceIndex()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L1033 _method_ `void SetRandom(float E)` — SceneInstanceIndex is not used in hit group shaders so reuse it to pass a random number _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
  - L1034 _method_ `float GetRandom()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
- L1124-1173 _struct_ **`FDecalShaderPayload`** `struct FDecalShaderPayload : FMinimalPayload` — base/reg: `FMinimalPayload` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_DECALS)]_
  - L1127 _member_ `float3 TranslatedWorldPos;` — float HitT                          //  4 bytes _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_DECALS)]_
  - L1128 _member_ `uint2 PackedBaseColor;` — 8 bytes half4 _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_DECALS)]_
  - L1129 _member_ `uint2 PackedMetallicSpecularRoughness;` — 8 bytes - half4 _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_DECALS)]_
  - L1130 _member_ `uint2 PackedWorldNormal;` — 8 bytes - half4 _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_DECALS)]_
  - L1131 _member_ `uint2 PackedEmissive;` — 8 bytes - half3 (alpha is not used) _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_DECALS)]_
  - L1134 _method_ `float4 GetBaseColor()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_DECALS)]_
  - L1139 _method_ `void SetBaseColor(float4 BaseColor)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_DECALS)]_
  - L1144 _method_ `float4 GetMetallicSpecularRoughness()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_DECALS)]_
  - L1149 _method_ `void SetMetallicSpecularRoughness(float4 MetallicSpecularRoughness)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_DECALS)]_
  - L1154 _method_ `float4 GetWorldNormal()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_DECALS)]_
  - L1159 _method_ `void SetWorldNormal(float4 WorldNormal)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_DECALS)]_
  - L1164 _method_ `float3 GetEmissive()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_DECALS)]_
  - L1169 _method_ `void SetEmissive(float3 Emissive)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_DECALS)]_
- L1277-1280 _struct_ **`FTranslucentMinimalPayload`** `struct FTranslucentMinimalPayload : FMinimalPayload` — base/reg: `FMinimalPayload` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !COMPUTESHADER]_
  - L1279 _member_ `float3 ShadowVisibility;` — What fraction of the ray's radiance is visible? (1.0 - fully visible, 0.0 - fully shadowed) _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !COMPUTESHADER]_

#### Functions (33)

- L226-229 _function_ `void SetRayTracingInstanceTransform(inout FPlatformRayTracingInstanceDescriptor Desc, float3x4 LocalToWorld)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !defined(OVERRIDE_PLATFORM_RAYTRACING_INSTANCE_DESCRITOR)]_
- L231-234 _function_ `uint GetRayTracingInstanceDescriptorInstanceId(FPlatformRayTracingInstanceDescriptor Desc)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !defined(OVERRIDE_PLATFORM_RAYTRACING_INSTANCE_DESCRITOR)]_
- L236-239 _function_ `uint GetRayTracingInstanceDescriptorMask(FPlatformRayTracingInstanceDescriptor Desc)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !defined(OVERRIDE_PLATFORM_RAYTRACING_INSTANCE_DESCRITOR)]_
- L241-244 _function_ `uint GetRayTracingInstanceDescriptorInstanceContributionToHitGroupIndex(FPlatformRayTracingInstanceDescriptor Desc)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !defined(OVERRIDE_PLATFORM_RAYTRACING_INSTANCE_DESCRITOR)]_
- L246-249 _function_ `uint GetRayTracingInstanceDescriptorFlags(FPlatformRayTracingInstanceDescriptor Desc)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !defined(OVERRIDE_PLATFORM_RAYTRACING_INSTANCE_DESCRITOR)]_
- L251-260 _function_ `FPlatformRayTracingInstanceDescriptor BuildPlatformRayTracingInstanceDesc(uint InstanceMask, uint InstanceId, uint InstanceFlags, uint InstanceContributionToHitGroupIndex, float3x4 LocalToWorld, uint2 AccelerationStructureAddress)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !defined(OVERRIDE_PLATFORM_RAYTRACING_INSTANCE_DESCRITOR)]_
- L377-380 _function_ `uint CalcLinearIndex(uint2 PixelCoord)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L382-390 _function_ `uint2 GetPixelCoord(uint2 DispatchThreadId, uint UpscaleFactor)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L393-407 _function_ `void ApplyPositionBias(inout float3 RayOrigin, float3 RayDirection, const float3 WorldNormal, const float MaxNormalBias)` — WorldNormal is the vector towards which the ray position will be offseted. _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L409-421 _function_ `void ApplyCameraRelativeDepthBias(inout float3 RayOrigin, float3 RayDirection, uint2 PixelCoord, float DeviceZ, const float3 WorldNormal, const float AbsoluteNormalBias)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L424-432 _function_ `void ApplyRayBias(inout float3 RayOrigin, float HitT, float3 GeoNormal)` — This strategy is similar to ApplyPositionBias, but is the version used in the path tracer _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L434-439 _function_ `float3 TranslatedWorldToTLASWorld(float3 TranslatedWorldPosition)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L441-446 _function_ `float3 TLASWorldToTranslatedWorld(float3 TLASWorldPosition)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L448-453 _function_ `float4 TranslatedWorldPositionToSvPosition(float3 TranslatedWorldPosition)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L456-461 _function_ `uint PackNormalToUInt32(float3 Normal)` — Pack normal vector into an uint32 using Octahedron encoding _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L464-470 _function_ `float3 UnpackNormalFromUInt32(uint PackedNormal)` — Pack normal vector into from an uint32 using Octahedron encoding _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L495-498 _function_ `float3 TranslatedWorldRayOrigin()` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING]_
- L500-503 _function_ `void ApplyPositionBias(inout FRayDesc Ray, const float3 WorldNormal, const float MaxNormalBias)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING]_
- L505-508 _function_ `void ApplyCameraRelativeDepthBias(inout FRayDesc Ray, uint2 PixelCoord, float DeviceZ, const float3 WorldNormal, const float AbsoluteNormalBias)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING]_
- L510-526 _function_ `FRayDesc CreatePrimaryRay(float2 UV)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING]_
- L530-556 _function_ `uint TranslateRayTracingInstanceFlags(uint InFlags)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L558-583 _function_ `uint TranslateRayTracingPlatformInstanceFlags(uint InPlatformFlags)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_
- L758-773 _function_ `FPackedMaterialClosestHitPayload PackRayTracingPayload(FMaterialClosestHitPayload In, in FRayCone RayCone)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
- L775-794 _function_ `FMaterialClosestHitPayload UnpackRayTracingPayload(FPackedMaterialClosestHitPayload In, FRayDesc Ray)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && SUBSTRATE_GBUFFER_FORMAT==1]_
- L1037-1071 _function_ `FPackedMaterialClosestHitPayload PackRayTracingPayload(FMaterialClosestHitPayload Input, in FRayCone RayCone)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
- L1073-1101 _function_ `FMaterialClosestHitPayload UnpackRayTracingPayload(FPackedMaterialClosestHitPayload Input, FRayDesc Ray)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(SUBSTRATE_GBUFFER_FORMAT==1)]_
- L1177-1186 _function_ `FDecalShaderPayload InitDecalShaderPayload(float3 TranslatedWorldPos)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_DECALS)]_
- L1200-1243 _function_ `void TraceVisibilityRayPacked( inout FPackedMaterialClosestHitPayload PackedPayload, in RaytracingAccelerationStructure TLAS, in uint RayFlags, in uint InstanceInclusionMask, in FRayDesc Ray)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING]_
- L1245-1270 _function_ `FMinimalPayload TraceVisibilityRay( in RaytracingAccelerationStructure TLAS, in uint RayFlags, in uint InstanceInclusionMask, in FRayDesc Ray)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING]_
- L1282-1320 _function_ `FTranslucentMinimalPayload TraceTranslucentVisibilityRay( in RaytracingAccelerationStructure TLAS, in uint RayFlags, in uint InstanceInclusionMask, in FRayDesc Ray)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !COMPUTESHADER]_
- L1322-1367 _function_ `void TraceMaterialRayPacked( inout FPackedMaterialClosestHitPayload Payload, in RaytracingAccelerationStructure TLAS, in uint RayFlags, in uint InstanceInclusionMask, in FRayDesc Ray, inout FRayCone RayCone, in bool bEnableSkyLightContribution, in bool bIsCameraRay)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !COMPUTESHADER]_
- L1369-1425 _function_ `FMaterialClosestHitPayload TraceMaterialRay( in RaytracingAccelerationStructure TLAS, in uint RayFlags, in uint InstanceInclusionMask, in FRayDesc Ray, inout FRayCone RayCone, in bool bEnableSkyLightContribution, in bool bIgnoreTranslucentMaterials, in bool bIsCameraRay)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !COMPUTESHADER]_
- L1431-1446 _function_ `uint GetGPUSceneInstanceIndex(uint PrimitiveIndex, uint InstanceIndex)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED)]_

#### Top-level macro invocations (6)

- L293 _macro_call_ `CHECK_RT_PAYLOAD_SIZE(FMinimalPayload)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_MINIMAL)]_
- L308 _macro_call_ `CHECK_RT_PAYLOAD_SIZE(FDefaultPayload)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_DEFAULT)]_
- L320 _macro_call_ `CHECK_RT_PAYLOAD_SIZE(FVFXTracePayload)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_VFX)]_
- L332 _macro_call_ `CHECK_RT_PAYLOAD_SIZE(FDeferredMaterialPayload)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_DEFERRED)]_
- L1106 _macro_call_ `CHECK_RT_PAYLOAD_SIZE(FPackedMaterialClosestHitPayload)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && !COMPUTESHADER \|\| PLATFORM_SUPPORTS_INLINE_RAY_TRACING && IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_RAYTRACING_MATERIAL)]_
- L1174 _macro_call_ `CHECK_RT_PAYLOAD_SIZE(FDecalShaderPayload)` _[#if !defined(RAYTRACINGCOMMON_USH_INCLUDED) && IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_DECALS)]_

### `Shaders/Private/RayTracing/RayTracingCommonMetal.ush` (Private)

- lines: 88; parse: all-branches

#### Macros (#define, 6)

- L9 `#define OVERRIDE_PLATFORM_RAYTRACING_INSTANCE_DESCRITOR 1`
- L11 `#define PLATFORM_RAYTRACING_INSTANCE_FLAG_NONE 0`
- L12 `#define PLATFORM_RAYTRACING_INSTANCE_FLAG_TRIANGLE_CULL_DISABLE 0x1`
- L13 `#define PLATFORM_RAYTRACING_INSTANCE_FLAG_TRIANGLE_FRONT_COUNTERCLOCKWISE 0x2`
- L14 `#define PLATFORM_RAYTRACING_INSTANCE_FLAG_FORCE_OPAQUE 0x4`
- L15 `#define PLATFORM_RAYTRACING_INSTANCE_FLAG_FORCE_NON_OPAQUE 0x8`
- L7 #pragma `once`

#### Structs / classes (1)

- L18-46 _struct_ **`FPlatformRayTracingInstanceDescriptor`** `struct FPlatformRayTracingInstanceDescriptor` — Mirrors IndirectAccelerationStructureInstanceDescriptor:
  - L20 _member_ `float Transform[4][3];` — MTLPackedFloat4x3 transformationMatrix;
  - L21 _member_ `uint Options;` — MTLAccelerationStructureInstanceOptions options;
  - L22 _member_ `uint InstanceMask;` — uint32_t mask;
  - L23 _member_ `uint intersectionFunctionTableOffset;` — uint32_t intersectionFunctionTableOffset;
  - L24 _member_ `uint InstanceID;` — uint32_t userID;
  - L25 _member_ `uint2 AccelerationStructure;` — uint2 accelerationStructureIndex;
  - L27 _method_ `uint GetInstanceId()`
  - L32 _method_ `uint GetMask()`
  - L37 _method_ `uint GetInstanceContributionToHitGroupIndex()`
  - L42 _method_ `uint GetFlags()`

#### Functions (6)

- L48-53 _function_ `void SetRayTracingInstanceTransform(inout FPlatformRayTracingInstanceDescriptor Desc, float3x4 LocalToWorld)`
- L55-58 _function_ `uint GetRayTracingInstanceDescriptorInstanceId(FPlatformRayTracingInstanceDescriptor Desc)`
- L60-63 _function_ `uint GetRayTracingInstanceDescriptorMask(FPlatformRayTracingInstanceDescriptor Desc)`
- L65-68 _function_ `uint GetRayTracingInstanceDescriptorInstanceContributionToHitGroupIndex(FPlatformRayTracingInstanceDescriptor Desc)`
- L70-73 _function_ `uint GetRayTracingInstanceDescriptorFlags(FPlatformRayTracingInstanceDescriptor Desc)`
- L75-87 _function_ `FPlatformRayTracingInstanceDescriptor BuildPlatformRayTracingInstanceDesc(uint InstanceMask, uint InstanceId, uint InstanceFlags, uint InstanceContributionToHitGroupIndex, float3x4 LocalToWorld, uint2 AccelerationStructureAddress)`

### `Shaders/Private/RayTracing/RayTracingDebug.usf` (Private)

- lines: 499; parse: all-branches
- includes: L11 `/Engine/Shared/RayTracingDebugTypes.h`, L12 `/Engine/Shared/RayTracingTypes.h`, L13 `../Common.ush`, L14 `../ShadingCommon.ush`, L15 `../ColorMap.ush`, L16 `../Hash.ush`, L17 `../Visualization.ush`, L18 `../ShaderPrint.ush`, L19 `../Substrate/Substrate.ush`, L20 `../Substrate/SubstrateEvaluation.ush`, L21 `../Substrate/SubstrateVisualizeCommon.ush`, L22 `../Nanite/NaniteRayTrace.ush`, L23 `/Engine/Shared/SubstrateVisualizeDefinitions.h`, L25 `RayTracingDebugUtils.ush`, L26 `RayTracingLightCullingCommon.ush`, L28 `/Engine/Shared/RaytracingDebugDefinitions.h`

#### Macros (#define, 6)

- L3 `#define SUBSTRATE_MATERIALCONTAINER_IS_VIEWRESOURCE 0`
- L4 `#define SUBSTRATE_SSS_MATERIAL_OVERRIDE 0`
- L5 `#define SUBSTRATE_SSS_TRANSMISSION 0`
- L6 `#define SUBSTRATE_COMPLEXSPECIALPATH 1`
- L7 `#define SUBSTRATE_INLINE_SHADING 0`
- L9 `#define RAYTRACING_DEBUG_INLINE COMPUTESHADER`

#### Entry points (1)

- L459-498 _entry_ `RAY_TRACING_ENTRY_RAYGEN_OR_INLINE(RayTracingDebugMain)` — stage: **raygeneration\|compute(inline)**

#### Global resources (textures / buffers / samplers) (8)

- L30 _resource_ `RWTexture2D<float4> Output;`
- L31 _resource_ `RWTexture2D<float> OutputDepth;`
- L33 _resource_ `RaytracingAccelerationStructure TLAS;`
- L36 _resource_ `StructuredBuffer<FRayTracingSceneMetadataRecord> RayTracingSceneMetadata;` _[#if RAYTRACING_DEBUG_INLINE]_
- L49 _resource_ `StructuredBuffer<FRayTracingInstanceExtraData> InstancesExtraData;`
- L50 _resource_ `StructuredBuffer<FRayTracingInstanceDebugData> InstancesDebugData;`
- L51 _resource_ `StructuredBuffer<FPlatformRayTracingInstanceDescriptor> InstanceBuffer;`
- L52 _resource_ `StructuredBuffer<FRayTracingPickingFeedback> PickingBuffer;`

#### Global parameters (uniforms) (8)

- L39 _parameter_ `uint VisualizationMode;`
- L40 _parameter_ `uint PickerDomain;`
- L41 _parameter_ `uint OpaqueOnly;`
- L42 _parameter_ `float TimingScale;`
- L44 _parameter_ `float TriangleHitCountMaxThreshold;`
- L45 _parameter_ `float TriangleHitCountPerInstanceMaxThreshold;`
- L46 _parameter_ `uint TopKMostHitInstances;`
- L47 _parameter_ `uint NumTotalInstances;`

#### Functions (4)

- L56-62 _function_ `float4 AnisoDebugColor(float InAniso)` _[#if (USE_DEBUG_CHS == 0) && (RAYTRACING_DEBUG_INLINE == 0)]_
- L64-67 _function_ `float4 RoughnessDebugColor(float InRoughness)` _[#if (USE_DEBUG_CHS == 0) && (RAYTRACING_DEBUG_INLINE == 0)]_
- L69-213 _function_ `float4 DebugRayTracingMaterial(uint2 PixelCoord, FRayDesc Ray)` _[#if (USE_DEBUG_CHS == 0) && (RAYTRACING_DEBUG_INLINE == 0)]_
- L219-455 _function_ `float4 DebugRayTracingInstance(FRayDesc Ray, out float OutDepth)` _[#if !((USE_DEBUG_CHS == 0) && (RAYTRACING_DEBUG_INLINE == 0))]_

### `Shaders/Private/RayTracing/RayTracingDebugCHS.usf` (Private)

- lines: 43; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../Hash.ush`, L6 `RayTracingCommon.ush`, L7 `RayTracingDebugUtils.ush`, L8 `RayTracingHitGroupCommon.ush`

#### Entry points (2)

- L10-35 _entry_ `RAY_TRACING_ENTRY_CLOSEST_HIT(RayTracingDebugMainCHS, FRayTracingDebugPayload, Payload, FRayTracingIntersectionAttributes, Attributes)` — stage: **closesthit** — C++: `FRayTracingDebugCHS` SF_RayHitGroup via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/RayTracing/RayTracingDebug.cpp:354)
- L37-42 _entry_ `RAY_TRACING_ENTRY_ANY_HIT(RayTracingDebugAHS, FRayTracingDebugPayload, Payload, FRayTracingIntersectionAttributes, Attributes)` — stage: **anyhit** — C++: `FRayTracingDebugCHS` SF_RayHitGroup via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/RayTracing/RayTracingDebug.cpp:354)

### `Shaders/Private/RayTracing/RayTracingDebugHitStats.usf` (Private)

- lines: 39; parse: all-branches
- includes: L3 `../Common.ush`, L4 `RayTracingDebugUtils.ush`, L6 `/Engine/Shared/RaytracingDebugDefinitions.h`, L7 `/Engine/Shared/RayTracingDebugTypes.h`

#### Entry points (1)

- L15-38 _entry_ `RAY_TRACING_ENTRY_RAYGEN(RayTracingDebugHitStatsRGS)` — stage: **raygeneration** — C++: `FRayTracingDebugHitStatsRGS` SF_RayGen via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/RayTracing/RayTracingDebug.cpp:420)

#### Global resources (textures / buffers / samplers) (1)

- L13 _resource_ `RaytracingAccelerationStructure TLAS;`

#### Global parameters (uniforms) (3)

- L9 _parameter_ `uint OpaqueOnly;`
- L11 _parameter_ `uint VisualizationMode;`
- L12 _parameter_ `uint TriangleHitCountForceNonOpaque;`

### `Shaders/Private/RayTracing/RayTracingDebugHitStatsCHS.usf` (Private)

- lines: 28; parse: all-branches
- includes: L3 `/Engine/Shared/RayTracingDebugTypes.h`, L4 `../Common.ush`, L5 `../Hash.ush`, L7 `RayTracingCommon.ush`, L8 `RayTracingDebugUtils.ush`, L9 `RayTracingHitGroupCommon.ush`

#### Entry points (2)

- L11-22 _entry_ `RAY_TRACING_ENTRY_ANY_HIT(RayTracingDebugHitStatsAHS, FRayTracingDebugPayload, Payload, FRayTracingIntersectionAttributes, Attributes)` — stage: **anyhit** — C++: `FRayTracingDebugHitStatsCHS` SF_RayHitGroup via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/RayTracing/RayTracingDebug.cpp:457)
- L24-28 _entry_ `RAY_TRACING_ENTRY_CLOSEST_HIT(RayTracingDebugHitStatsCHS, FRayTracingDebugPayload, Payload, FRayTracingIntersectionAttributes, Attributes)` — stage: **closesthit** — C++: `FRayTracingDebugHitStatsCHS` SF_RayHitGroup via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/RayTracing/RayTracingDebug.cpp:457)

### `Shaders/Private/RayTracing/RayTracingDebugHitStatsUtils.usf` (Private)

- lines: 69; parse: all-branches
- includes: L2 `../Common.ush`, L3 `../SceneData.ush`, L4 `../ShaderPrint.ush`

#### Macros (#define, 1)

- L6 `#define INVALID_PRIMITIVEID ~0`

#### Entry points (1)

- L35-68 _entry_ `[numthreads(NUM_THREADS_PER_GROUP, 1, 1)] void RayTracingSceneDebugHitStatsRenderCS(uint3 DispatchThread : SV_DispatchThreadID)` — stage: **compute** — C++: `FRayTracingSceneHitStatsDebugRenderCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/RayTracing/RayTracingDebug.cpp:1179) — Simple local bin sort based on shared atomics

#### Structs / classes (1)

- L13-21 _struct_ **`FRayTracingSceneDebugHitStatsNameInfo`** `struct FRayTracingSceneDebugHitStatsNameInfo`
  - L15 _member_ `uint PrimitiveID;`
  - L16 _member_ `uint Count;`
  - L17 _member_ `uint Length;`
  - L18 _member_ `uint Offset;`
  - L19 _member_ `uint Pad0;`
  - L20 _member_ `uint Pad1;`

#### Global resources (textures / buffers / samplers) (2)

- L10 _resource_ `StructuredBuffer<uint3> SelectedPrimitiveNameInfos;`
- L11 _resource_ `Buffer<uint> SelectedPrimitiveNames;`

#### Global parameters (uniforms) (2)

- L8 _parameter_ `uint SelectedNameInfoCount;`
- L9 _parameter_ `uint SelectedNameCharacterCount;`

#### Functions (1)

- L23-32 _function_ `FRayTracingSceneDebugHitStatsNameInfo UnpackDebugNameInfo(uint3 In)`

### `Shaders/Private/RayTracing/RayTracingDebugInstanceOverlap.usf` (Private)

- lines: 121; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../ShadingCommon.ush`, L5 `../ColorMap.ush`, L6 `../Hash.ush`, L7 `../Visualization.ush`, L8 `../SceneData.ush`, L9 `/Engine/Shared/RayTracingDebugTypes.h`

#### Macros (#define, 3)

- L11 `#define MAX_FLT (+3.402823466e+38f)`
- L12 `#define MIN_FLT (-3.402823466e+38f)`
- L13 `#define INVALID_INSTANCE_GPUSCENE_INDEX (0xFFFFFFFF)`

#### Entry points (4)

- L66-88 _entry_ `void InstanceOverlapMainVS( float4 InPosition : ATTRIBUTE0, uint InstanceIndex : SV_InstanceID, out float4 OutPosition : SV_POSITION )` — stage: **vertex (from C++ binding)** — C++: `FRayTracingDebugInstanceOverlapVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/RayTracing/RayTracingDebug.cpp:615)
- L90-96 _entry_ `void InstanceOverlapMainPS( in float4 Position : SV_POSITION, out float4 OutColor : SV_Target0 )` — stage: **pixel (from C++ binding)** — C++: `FRayTracingDebugInstanceOverlapPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/RayTracing/RayTracingDebug.cpp:632)
- L100-105 _entry_ `void ConvertToDeviceDepthPS( in float4 SvPosition : SV_POSITION, out float OutDepth : SV_DEPTH)` — stage: **pixel (from C++ binding)** — C++: `FRayTracingDebugConvertToDeviceDepthPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/RayTracing/RayTracingDebug.cpp:657)
- L110-121 _entry_ `void BlendInstanceOverlapPS( in float4 SvPosition : SV_POSITION, out float4 OutColor : SV_Target0 )` — stage: **pixel (from C++ binding)** — C++: `FRayTracingDebugBlendInstanceOverlapPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/RayTracing/RayTracingDebug.cpp:677)

#### Structs / classes (1)

- L19-23 _struct_ **`FInstanceBounds`** `struct FInstanceBounds`
  - L21 _member_ `float3 Center;`
  - L22 _member_ `float3 Extent;`

#### Global resources (textures / buffers / samplers) (3)

- L17 _resource_ `StructuredBuffer<FRayTracingInstanceExtraData> InstanceExtraDataBuffer;`
- L98 _resource_ `Texture2D<float> InputDepth;`
- L108 _resource_ `Texture2D<float> InstanceOverlap;`

#### Global parameters (uniforms) (2)

- L15 _parameter_ `float BoundingBoxExtentScale;`
- L107 _parameter_ `float HeatmapScale;`

#### Functions (1)

- L25-64 _function_ `FInstanceBounds GetTranslatedWorldAABBForInstance(uint GPUSceneInstanceId)`

### `Shaders/Private/RayTracing/RayTracingDebugMS.usf` (Private)

- lines: 14; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../Hash.ush`, L6 `RayTracingCommon.ush`, L7 `RayTracingDebugUtils.ush`, L8 `RayTracingHitGroupCommon.ush`

#### Entry points (1)

- L10-13 _entry_ `RAY_TRACING_ENTRY_MISS(RayTracingDebugMS, FRayTracingDebugPayload, Payload)` — stage: **miss** — C++: `FRayTracingDebugMS` SF_RayMiss via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/RayTracing/RayTracingDebug.cpp:387)

### `Shaders/Private/RayTracing/RayTracingDebugPicking.usf` (Private)

- lines: 81; parse: all-branches
- includes: L3 `../Common.ush`, L4 `RayTracingDebugUtils.ush`, L6 `/Engine/Shared/RayTracingDebugTypes.h`

#### Entry points (1)

- L19-80 _entry_ `RAY_TRACING_ENTRY_RAYGEN_OR_INLINE(RayTracingDebugPicking)` — stage: **raygeneration\|compute(inline)**

#### Global resources (textures / buffers / samplers) (6)

- L10 _resource_ `RaytracingAccelerationStructure TLAS;`
- L12 _resource_ `StructuredBuffer<FRayTracingInstanceExtraData> InstancesExtraData;`
- L13 _resource_ `StructuredBuffer<FRayTracingInstanceDebugData> InstancesDebugData;`
- L14 _resource_ `StructuredBuffer<FRayTracingPickingFeedback> PickingBuffer;`
- L16 _resource_ `RWStructuredBuffer<FRayTracingPickingFeedback> PickingOutput;`
- L17 _resource_ `StructuredBuffer<FPlatformRayTracingInstanceDescriptor> InstanceBuffer;`

#### Global parameters (uniforms) (1)

- L8 _parameter_ `uint OpaqueOnly;`

### `Shaders/Private/RayTracing/RayTracingDebugTraversal.usf` (Private)

- lines: 149; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../ShadingCommon.ush`, L5 `../ColorMap.ush`, L6 `../BlueNoise.ush`, L8 `RayTracingCommon.ush`, L9 `RayTracingDeferredMaterials.ush`, L11 `RayTracingDeferredShadingCommon.ush`, L12 `../Substrate/Substrate.ush`, L13 `../Lumen/LumenPosition.ush`, L15 `/Engine/Shared/RaytracingDebugDefinitions.h`, L17 `TraceRayInline.ush`

#### Entry points (1)

- L86-148 _entry_ `[numthreads(INLINE_RAY_TRACING_THREAD_GROUP_SIZE_X, INLINE_RAY_TRACING_THREAD_GROUP_SIZE_Y, 1)] void RayTracingDebugTraversalCS(uint3 DispatchThread : SV_DispatchThreadID)` — stage: **compute** — C++: `FRayTracingDebugTraversalCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/RayTracing/RayTracingDebug.cpp:520)

#### Structs / classes (1)

- L30-47 _struct_ **`FNaniteTraceRayInlineCallback`** `struct FNaniteTraceRayInlineCallback : FDefaultTraceRayInlineCallback` — base/reg: `FDefaultTraceRayInlineCallback`
  - L32 _member_ `uint ClusterIntersectionCount;`
  - L34 _method_ `bool OnProceduralPrimitive(float3 ObjectRayOrigin, float3 ObjectRayDirection, float RayTMin, inout float RayTCurrent, FTraceRayInlineProceduralIntersectionParameters ProceduralIntersectionParameters)`

#### Global resources (textures / buffers / samplers) (2)

- L19 _resource_ `RWTexture2D<float4> Output;`
- L20 _resource_ `RaytracingAccelerationStructure TLAS;`

#### Global parameters (uniforms) (6)

- L22 _parameter_ `uint VisualizationMode;`
- L23 _parameter_ `float TraversalBoxScale;`
- L24 _parameter_ `float TraversalClusterScale;`
- L25 _parameter_ `float TraversalTriangleScale;`
- L27 _parameter_ `float NormalBias;`
- L28 _parameter_ `float TraceDistance;`

#### Functions (1)

- L49-84 _function_ `FRayDesc CreateSecondaryRay(uint2 PixelCoord, float2 ScreenUV, out bool bIsValid)`

### `Shaders/Private/RayTracing/RayTracingDebugUtils.ush` (Private)

- lines: 35; parse: all-branches
- includes: L5 `/Engine/Shared/RayTracingPayloadType.h`, L6 `RayTracingCommon.ush`
- L3 #pragma `once`

#### Structs / classes (1)

- L8-31 _struct_ **`FRayTracingDebugPayload`** `struct FRayTracingDebugPayload : FMinimalPayload` — base/reg: `FMinimalPayload`
  - L10 _member_ `uint GPUSceneInstanceId;`
  - L11 _member_ `uint TriangleIndex;`
  - L12 _member_ `uint InstanceIndex;`
  - L13 _member_ `uint GeometryIndex;`
  - L15 _member_ `uint ClusterId;` _[#if PLATFORM_SUPPORTS_RAYTRACING_CLUSTER_OPS]_
  - L18 _member_ `float3 WorldNormal;`
  - L20 _member_ `uint TriangleHitCountPerRay;`
  - L21 _member_ `uint Flags;`
  - L23 _method_ `void SetFrontFace()`
  - L27 _method_ `bool IsFrontFace()`

#### Top-level macro invocations (1)

- L33-35 _macro_call_ `CHECK_RT_PAYLOAD_SIZE(FRayTracingDebugPayload)` _[#if IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_RAYTRACING_DEBUG)]_

### `Shaders/Private/RayTracing/RayTracingDecalGrid.ush` (Private)

- lines: 140; parse: all-branches
- includes: L9 `../Common.ush`, L10 `../Visualization.ush`, L11 `/Engine/Shared/RayTracingDefinitions.h`, L12 `/Engine/Shared/PathTracingDefinitions.h`

#### Macros (#define, 1)

- L6 `#define USE_RAY_TRACING_DECAL_GRID 0` _[#if !defined(USE_RAY_TRACING_DECAL_GRID)]_
- L3 #pragma `once`

#### Structs / classes (1)

- L14-19 _struct_ **`FDecalLoopCount`** `struct FDecalLoopCount`
  - L15 _member_ `uint NumDecals;`
  - L17 _member_ `uint DecalGridOffset;` _[#if USE_RAY_TRACING_DECAL_GRID]_

#### Functions (6)

- L23-58 _function_ `FDecalLoopCount DecalGridLookup(float3 TranslatedWorldPos)` _[#if USE_RAY_TRACING_DECAL_GRID]_
- L60-111 _function_ `float3 DecalGridVisualize(FDecalLoopCount LoopCount, int DebugMode, uint MaxCount)` _[#if USE_RAY_TRACING_DECAL_GRID]_
- L114-117 _function_ `uint GetDecalId(uint Index, FDecalLoopCount LoopCount)` _[#if USE_RAY_TRACING_DECAL_GRID]_
- L121-127 _function_ `FDecalLoopCount DecalGridLookup(float3 TranslatedWorldPos)` _[#if !(USE_RAY_TRACING_DECAL_GRID)]_
- L129-132 _function_ `float3 DecalGridVisualize(FDecalLoopCount LoopCount, int DebugMode, uint MaxCount)` _[#if !(USE_RAY_TRACING_DECAL_GRID)]_
- L134-137 _function_ `uint GetDecalId(uint Index, FDecalLoopCount LoopCount)` _[#if !(USE_RAY_TRACING_DECAL_GRID)]_

### `Shaders/Private/RayTracing/RayTracingDecalMaterialShader.usf` (Private)

- lines: 284; parse: all-branches
- includes: L11 `/Engine/Private/Common.ush`, L12 `/Engine/Private/RayTracing/RayTracingCommon.ush`, L13 `/Engine/Private/PathTracing/PathTracingShaderUtils.ush`, L25 `/Engine/Generated/Material.ush`, L179 `/Engine/Private/RayTracing/RayTracingHitGroupCommon.ush` [RAYHITGROUPSHADER], L181 `/Engine/Generated/VertexFactory.ush` [RAYHITGROUPSHADER], L183 `/Engine/Private/RayTracing/RayTracingCalcInterpolants.ush` [RAYHITGROUPSHADER]

#### Macros (#define, 14)

- L3 `#define PATH_TRACING 1`
- L4 `#define SCENE_TEXTURES_DISABLED 1`
- L7 `#define EYE_ADAPTATION_PREV_FRAME_EXPOSURE 1`
- L9 `#define SUBSTRATE_INLINE_SHADING 1`
- L15 `#define DecalPositionHigh RayTracingDecalParameters.DecalPositionHigh`
- L16 `#define WorldToDecal RayTracingDecalParameters.WorldToDecal`
- L17 `#define SvPositionToDecal WorldToDecal`
- L18 `#define DecalToWorld RayTracingDecalParameters.DecalToWorld`
- L19 `#define DecalToWorldInvScale RayTracingDecalParameters.DecalToWorldInvScale`
- L20 `#define DecalOrientation RayTracingDecalParameters.DecalOrientation`
- L21 `#define DecalParams RayTracingDecalParameters.DecalParams`
- L22 `#define DecalColorParam RayTracingDecalParameters.DecalColorParam`
- L23 `#define DecalWriteFlags RayTracingDecalParameters.DecalWriteFlags`
- L177 `#define NEEDS_VERTEX_FACTORY_INTERPOLATION 1` _[#if RAYHITGROUPSHADER]_
- L174 #undef `NEEDS_VERTEX_FACTORY_INTERPOLATION`

#### Entry points (3)

- L104-168 _entry_ `RAY_TRACING_ENTRY_CALLABLE(RayTracingDecalMaterialShader, FDecalShaderPayload, Payload)` — stage: **callable** — C++: `FRayTracingDecalMaterialShader` SF_RayCallable via IMPLEMENT_SHADER_TYPE (Source/Runtime/Renderer/Private/RayTracing/RayTracingDecals.cpp:245) _[#if RAYCALLABLESHADER]_
- L185-243 _entry_ `RAY_TRACING_ENTRY_CLOSEST_HIT(RayTracingDecalMaterialCHS, FDecalShaderPayload, Payload, FRayTracingIntersectionAttributes, Attributes)` — stage: **closesthit** — C++: `FRayTracingDecalMaterialCHS` SF_RayHitGroup via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/RayTracing/RayTracingDecals.cpp:341) — C++: `FRayTracingDecalMaterialCHS_AHS` SF_RayHitGroup via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/RayTracing/RayTracingDecals.cpp:342) _[#if RAYHITGROUPSHADER]_
- L247-279 _entry_ `RAY_TRACING_ENTRY_ANY_HIT(RayTracingDecalMaterialAHS, FDecalShaderPayload, Payload, FRayTracingIntersectionAttributes, Attributes)` — stage: **anyhit** — C++: `FRayTracingDecalMaterialCHS_AHS` SF_RayHitGroup via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/RayTracing/RayTracingDecals.cpp:342) _[#if RAYHITGROUPSHADER && USE_MATERIAL_ANY_HIT_SHADER]_

#### Structs / classes (1)

- L28-66 _struct_ **`FDecalData`** `struct FDecalData`
  - L30 _member_ `float Opacity;`
  - L31 _member_ `float3 BaseColor;`
  - L32 _member_ `float3 WorldNormal;`
  - L33 _member_ `float3 MetallicSpecularRoughness;`
  - L34 _member_ `float3 Emissive;`
  - L36 _method_ `void CombineWithPayload(inout FDecalShaderPayload Payload, uint WriteFlags, float OpacityMult)`

#### Functions (1)

- L70-100 _function_ `FDecalData GetDecalData(FPixelMaterialInputs PixelMaterialInputs, FMaterialPixelParameters MaterialParameters)`

### `Shaders/Private/RayTracing/RayTracingDefaultDecalHitShader.usf` (Private)

- lines: 27; parse: all-branches
- includes: L3 `/Engine/Private/RayTracing/RayTracingCommon.ush`

#### Entry points (3)

- L5-12 _entry_ `RAY_TRACING_ENTRY_CLOSEST_HIT(RayTracingDefaultOpaqueDecalMaterialCHS, FDecalShaderPayload, Payload, FRayTracingIntersectionAttributes, Attributes)` — stage: **closesthit** — C++: `FDefaultOpaqueMeshDecalHitGroup` SF_RayHitGroup via IMPLEMENT_SHADER_TYPE (Source/Runtime/Renderer/Private/RayTracing/RayTracingDecals.cpp:379)
- L14-19 _entry_ `RAY_TRACING_ENTRY_CLOSEST_HIT(RayTracingDefaultHiddenDecalMaterialCHS, FDecalShaderPayload, Payload, FRayTracingIntersectionAttributes, Attributes)` — stage: **closesthit** — C++: `FDefaultHiddenMeshDecalHitGroup` SF_RayHitGroup via IMPLEMENT_SHADER_TYPE (Source/Runtime/Renderer/Private/RayTracing/RayTracingDecals.cpp:404)
- L21-26 _entry_ `RAY_TRACING_ENTRY_ANY_HIT(RayTracingDefaultHiddenDecalMaterialAHS, FDecalShaderPayload, Payload, FRayTracingIntersectionAttributes, Attributes)` — stage: **anyhit** — C++: `FDefaultHiddenMeshDecalHitGroup` SF_RayHitGroup via IMPLEMENT_SHADER_TYPE (Source/Runtime/Renderer/Private/RayTracing/RayTracingDecals.cpp:404)

### `Shaders/Private/RayTracing/RayTracingDeferredMaterials.usf` (Private)

- lines: 21; parse: all-branches
- includes: L3 `../Common.ush`, L4 `RayTracingCommon.ush`, L5 `RayTracingHitGroupCommon.ush`

#### Entry points (2)

- L7-13 _entry_ `RAY_TRACING_ENTRY_CLOSEST_HIT(DeferredMaterialCHS, FDeferredMaterialPayload, Payload, FRayTracingIntersectionAttributes, Attributes)` — stage: **closesthit**
- L15-19 _entry_ `RAY_TRACING_ENTRY_MISS(DeferredMaterialMS, FDeferredMaterialPayload, Payload)` — stage: **miss**

### `Shaders/Private/RayTracing/RayTracingDeferredMaterials.ush` (Private)

- lines: 53; parse: all-branches
- includes: L5 `RayTracingCommon.ush`, L8 `/Platform/Private/RayTracingDeferredMaterials.ush` [defined(OVERRIDE_RAYTRACINGDEFERREDMATERIALS_USH)], L22 `/Engine/Shared/ThirdParty/AMD/ags_shader_intrinsics_dx12.h` [!(defined(OVERRIDE_RAYTRACINGDEFERREDMATERIALS_USH)) && DIM_AMD_HIT_TOKEN]

#### Macros (#define, 5)

- L19 `#define AGS_RAY_HIT_TOKEN 1` _[#if !(defined(OVERRIDE_RAYTRACINGDEFERREDMATERIALS_USH)) && DIM_AMD_HIT_TOKEN && !defined(AGS_RAY_HIT_TOKEN)]_
- L24 `#define TraceDeferredMaterialGatherRay(TLAS, RayFlags, InstanceInclusionMask, Ray, OutBookmark, InOutPayload) { TraceRay(TLAS, RayFlags, InstanceInclusionMask, RAY_TRACING_SHADER_SLOT_MATERIAL, RAY_TRACING_NUM_SHADER_SLOTS, 0, Ray, InOutPayload); OutBookmark.Data[0] = AmdGetLastHitToken().x; OutBookmark.Data[ ...` (5 lines) _[#if !(defined(OVERRIDE_RAYTRACINGDEFERREDMATERIALS_USH)) && DIM_AMD_HIT_TOKEN]_
- L30 `#define TraceDeferredMaterialShadingRay(TLAS, RayFlags, InstanceInclusionMask, Ray, Bookmark, InOutPayload) { AmdSetHitToken(uint2(Bookmark.Data[0], Bookmark.Data[1])); TraceRay(TLAS, RayFlags, InstanceInclusionMask, RAY_TRACING_SHADER_SLOT_MATERIAL, RAY_TRACING_NUM_SHADER_SLOTS, 0, Ray, InOutPayload); }` (4 lines) _[#if !(defined(OVERRIDE_RAYTRACINGDEFERREDMATERIALS_USH)) && DIM_AMD_HIT_TOKEN]_
- L37 `#define TraceDeferredMaterialGatherRay(TLAS, RayFlags, InstanceInclusionMask, Ray, OutBookmark, InOutPayload) { TraceRay(TLAS, RayFlags, InstanceInclusionMask, RAY_TRACING_SHADER_SLOT_MATERIAL, RAY_TRACING_NUM_SHADER_SLOTS, 0, Ray, InOutPayload); OutBookmark.Data[0] = asuint(InOutPayload.HitT); OutBookmark.Da ...` (5 lines) _[#if !(defined(OVERRIDE_RAYTRACINGDEFERREDMATERIALS_USH)) && !(DIM_AMD_HIT_TOKEN)]_
- L43 `#define TraceDeferredMaterialShadingRay(TLAS, RayFlags, InstanceInclusionMask, Ray, Bookmark, InOutPayload) { RayDesc BookmarkRay = Ray; BookmarkRay.TMin = asfloat(Bookmark.Data[0]) - 0.5f; BookmarkRay.TMax = asfloat(Bookmark.Data[1]) + 0.5f; TraceRay(TLAS, RayFlags, InstanceInclusionMask, RAY_TRACING_SHADE ...` (6 lines) _[#if !(defined(OVERRIDE_RAYTRACINGDEFERREDMATERIALS_USH)) && !(DIM_AMD_HIT_TOKEN)]_
- L3 #pragma `once`

#### Structs / classes (1)

- L11-14 _struct_ **`FRayIntersectionBookmark`** `struct FRayIntersectionBookmark` _[#if !(defined(OVERRIDE_RAYTRACINGDEFERREDMATERIALS_USH))]_
  - L13 _member_ `uint Data[2];` _[#if !(defined(OVERRIDE_RAYTRACINGDEFERREDMATERIALS_USH))]_

### `Shaders/Private/RayTracing/RayTracingDeferredShadingCommon.ush` (Private)

- lines: 60; parse: all-branches
- includes: L5 `../DeferredShadingCommon.ush`
- L3 #pragma `once`

#### Functions (3)

- L9-32 _function_ `FGBufferData GetGBufferDataFromSceneTexturesLoad(uint2 PixelCoord, bool bGetNormalizedNormal = true)`
- L34-54 _function_ `FGBufferData GetGBufferDataFromPayload(in FMaterialClosestHitPayload Payload)`
- L56-60 _function_ `FGBufferData GetGBufferDataFromPayload(in FPackedMaterialClosestHitPayload Payload)`

### `Shaders/Private/RayTracing/RayTracingDirectionalLight.ush` (Private)

- lines: 27; parse: all-branches
- includes: L5 `../PathTracing/Utilities/PathTracingRandomSequence.ush`, L6 `../MonteCarlo.ush`, L7 `../LightData.ush`, L8 `RayTracingCommon.ush`
- L3 #pragma `once`

#### Functions (1)

- L10-26 _function_ `void GenerateDirectionalLightOcclusionRay( FLightShaderParameters LightParameters, float3 TranslatedWorldPosition, float3 WorldNormal, float2 RandSample, out float3 RayOrigin, out float3 RayDirection, out float RayTMin, out float RayTMax)`

### `Shaders/Private/RayTracing/RayTracingDispatchDesc.usf` (Private)

- lines: 39; parse: all-branches
- includes: L8 `../Common.ush`

#### Macros (#define, 2)

- L11 `#define DISPATCH_DESC_MAX_SIZE_DWORDS 32` _[#if !defined(DISPATCH_DESC_MAX_SIZE_DWORDS)]_
- L14 `#define DISPATCH_DESC_MAX_SIZE_UINT4S (DISPATCH_DESC_MAX_SIZE_DWORDS/4)`

#### Entry points (1)

- L23-38 _entry_ `[numthreads(DISPATCH_DESC_MAX_SIZE_DWORDS, 1, 1)] void RayTracingDispatchDescCS(uint i : SV_DispatchThreadID)` — stage: **compute** — C++: `FRayTracingDispatchDescCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/RenderCore/Private/BuiltInRayTracingShaders.cpp:34)

#### Global resources (textures / buffers / samplers) (2)

- L20 _resource_ `Buffer<uint> DispatchDimensions;`
- L21 _resource_ `RWBuffer<uint> DispatchDescOutput;`

#### Global parameters (uniforms) (4)

- L16 _parameter_ `uint4 DispatchDescInput[DISPATCH_DESC_MAX_SIZE_UINT4S];`
- L17 _parameter_ `uint DispatchDescSizeDwords;`
- L18 _parameter_ `uint DispatchDescDimensionsOffsetDwords;`
- L19 _parameter_ `uint DimensionsBufferOffsetDwords;`

### `Shaders/Private/RayTracing/RayTracingDynamicMesh.usf` (Private)

- lines: 156; parse: all-branches
- includes: L10 `/Engine/Private/Common.ush`, L11 `/Engine/Private/ComputeShaderUtils.ush`, L12 `/Engine/Generated/Material.ush`, L13 `/Engine/Generated/VertexFactory.ush`

#### Macros (#define, 1)

- L15 `#define PER_VERTEX_MASK_ENABLED (USE_VERTEX_MASK && VF_SUPPORTS_RAYTRACING_VERTEX_MASK && MATERIALBLENDING_MASKED && RAY_TRACING_DYNAMIC_MESH_IN_LOCAL_SPACE)`
- L8 #pragma `message("UESHADERMETADATA_VERSION 74B3439C-C6C2-47F8-B07C-05009AB185D1")`

#### Entry points (1)

- L45-154 _entry_ `[numthreads(64, 1, 1)] void RayTracingDynamicGeometryConverterCS(uint3 GroupId : SV_GroupID, int GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FRayTracingDynamicGeometryConverterCS` SF_Compute via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/RayTracing/RayTracingDynamicGeometryUpdateManager.cpp:222) _[#if COMPUTESHADER]_

#### Global resources (textures / buffers / samplers) (2)

- L27 _resource_ `RWBuffer<float> RWVertexPositions;` _[#if COMPUTESHADER]_
- L30 _resource_ `Buffer<uint> IndexBuffer;` _[#if COMPUTESHADER]_

#### Global parameters (uniforms) (10)

- L18 _parameter_ `uint UsingIndirectDraw;` _[#if COMPUTESHADER]_
- L19 _parameter_ `uint MaxNumThreads;` _[#if COMPUTESHADER]_
- L20 _parameter_ `uint NumVertices;` _[#if COMPUTESHADER]_
- L21 _parameter_ `uint MinVertexIndex;` _[#if COMPUTESHADER]_
- L22 _parameter_ `uint PrimitiveId;` _[#if COMPUTESHADER]_
- L23 _parameter_ `uint OutputVertexBaseIndex;` _[#if COMPUTESHADER]_
- L24 _parameter_ `int InstanceId;` _[#if COMPUTESHADER]_
- L25 _parameter_ `float4x4 WorldToInstance;` _[#if COMPUTESHADER]_
- L28 _parameter_ `int bApplyWorldPositionOffset;` _[#if COMPUTESHADER]_
- L31 _parameter_ `uint IndexBufferOffset;` _[#if COMPUTESHADER]_

#### Functions (1)

- L33-43 _function_ `void HideTriangle(uint TriangleIndex, float3 ReferenceLocalPositon)` _[#if COMPUTESHADER]_

### `Shaders/Private/RayTracing/RayTracingFeedback.usf` (Private)

- lines: 63; parse: all-branches
- includes: L7 `../Common.ush`, L8 `../ComputeShaderUtils.ush`, L9 `/Engine/Shared/RayTracingDebugTypes.h`

#### Macros (#define, 1)

- L12 `#define THREADGROUP_SIZE 1` _[#if !defined(THREADGROUP_SIZE)]_

#### Entry points (2)

- L24-40 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void RayTracingProcessFeedbackCS(uint3 GroupId : SV_GroupID, int GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FRayTracingProcessFeedbackCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/RayTracing/RayTracingScene.cpp:667)
- L46-62 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void RayTracingUpdateGeometryHitCountCS(uint3 GroupId : SV_GroupID, int GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FRayTracingUpdateGeometryHitCountCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/RayTracing/RayTracingScene.cpp:703)

#### Global resources (textures / buffers / samplers) (8)

- L18 _resource_ `StructuredBuffer<uint> GeometryHitCountBuffer;`
- L19 _resource_ `StructuredBuffer<uint> GeometryHandleBuffer;`
- L20 _resource_ `StructuredBuffer<uint> AccelerationStructureIndexBuffer;`
- L21 _resource_ `RWStructuredBuffer<uint> RWGeometryHandleBuffer;`
- L22 _resource_ `RWBuffer<uint> RWGeometryHandleAllocator;`
- L42 _resource_ `StructuredBuffer<uint> InstanceHitCountBuffer;`
- L43 _resource_ `RWStructuredBuffer<uint> RWGeometryHitCountBuffer;`
- L44 _resource_ `StructuredBuffer<FRayTracingInstanceExtraData> InstanceExtraDataBuffer;`

#### Global parameters (uniforms) (2)

- L15 _parameter_ `uint NumGeometries;`
- L16 _parameter_ `uint NumInstances;`

### `Shaders/Private/RayTracing/RayTracingGatherPoints.ush` (Private)

- lines: 103; parse: all-branches

#### Macros (#define, 1)

- L3 `#define MAXIMUM_GATHER_POINTS_PER_PIXEL 32`

#### Structs / classes (3)

- L5-10 _struct_ **`FGatherPoints`** `struct FGatherPoints`
  - L7 _member_ `float3 TranslatedCreationPoint;`
  - L8 _member_ `float3 TranslatedPosition;`
  - L9 _member_ `uint2 Irradiance;`
- L12-18 _struct_ **`FGatherSample`** `struct FGatherSample`
  - L14 _member_ `float3 TranslatedCreationPoint;`
  - L15 _member_ `float3 TranslatedPosition;`
  - L16 _member_ `float3 Irradiance;`
  - L17 _member_ `float Pdf;`
- L21-25 _struct_ **`FRejectionCriteria`** `struct FRejectionCriteria`
  - L23 _member_ `float3 TranslatedCreationPoint;`
  - L24 _member_ `float DistanceThreshold2;`

#### Functions (6)

- L27-36 _function_ `uint2 PackIrradiance(float3 Irradiance, float Pdf)`
- L38-48 _function_ `float3 UnpackIrradiance(uint2 Irradiance, inout float Pdf)`
- L50-60 _function_ `FGatherSample ReadGatherSample(StructuredBuffer<FGatherPoints> GatherBuffer, uint BaseIndex, uint SampleIndex, uint ElementCount)`
- L62-68 _function_ `void WriteGatherSample(RWStructuredBuffer<FGatherPoints> GatherBuffer, uint BaseIndex, uint SampleIndex, uint ElementCount, FGatherSample GatherSample)`
- L70-76 _function_ `FRejectionCriteria CreateRejectionCriteria(float3 TranslatedCreationPoint, float DistanceThreshold)`
- L78-102 _function_ `void CreateRejectionMask( FRejectionCriteria RejectionCriteria, StructuredBuffer<FGatherPoints> GatherBuffer, uint BaseIndex, uint SampleIndex, uint ElementCount, int SampleCount, out bool bShouldReject[MAXIMUM_GATHER_POINTS_PER_PIXEL] )`

### `Shaders/Private/RayTracing/RayTracingHitGroupCommon.ush` (Private)

- lines: 175; parse: all-branches
- includes: L12 `/Engine/Private/RayTracing/RayTracingCommon.ush` [!defined(RAYTRACINGHITGROUPCOMMON_USH_INCLUDED)], L13 `/Engine/Shared/RayTracingBuiltInResources.h` [!defined(RAYTRACINGHITGROUPCOMMON_USH_INCLUDED)], L16 `../Nanite/NaniteRayTrace.ush` [!defined(RAYTRACINGHITGROUPCOMMON_USH_INCLUDED) && NANITE_RAY_TRACING], L20 `/Engine/Public/NvidiaExtensionsCommon.ush` [!defined(RAYTRACINGHITGROUPCOMMON_USH_INCLUDED) && PLATFORM_SUPPORTS_RAYTRACING_CLUSTER_OPS]

#### Macros (#define, 1)

- L10 `#define RAYTRACINGHITGROUPCOMMON_USH_INCLUDED ` _[#if !defined(RAYTRACINGHITGROUPCOMMON_USH_INCLUDED)]_
- L7 #pragma `once`

#### Functions (9)

- L23-48 _function_ `uint3 LoadIndices16Bit(ByteAddressBuffer SourceBuffer, uint OffsetInBytes)` _[#if !defined(RAYTRACINGHITGROUPCOMMON_USH_INCLUDED)]_
- L50-53 _function_ `uint3 LoadIndices32Bit(ByteAddressBuffer SourceBuffer, uint OffsetInBytes)` _[#if !defined(RAYTRACINGHITGROUPCOMMON_USH_INCLUDED)]_
- L55-59 _function_ `float3 LoadVertexPositionFloat3(ByteAddressBuffer SourceBuffer, uint BaseOffsetInBytes, uint Index, uint StrideInBytes)` _[#if !defined(RAYTRACINGHITGROUPCOMMON_USH_INCLUDED)]_
- L63-95 _function_ `FTriangleBaseAttributes LoadTriangleBaseAttributes( ByteAddressBuffer IndexBuffer, uint IndexBufferOffsetInBytes, uint IndexBufferStride, ByteAddressBuffer VertexBuffer, uint VertexBufferOffsetInBytes, uint VertexBufferStride, uint PrimitiveId)` _[#if !defined(RAYTRACINGHITGROUPCOMMON_USH_INCLUDED)]_
- L97-104 _function_ `FTriangleBaseAttributes LoadTriangleBaseAttributes(uint PrimitiveId)` _[#if !defined(RAYTRACINGHITGROUPCOMMON_USH_INCLUDED)]_
- L106-109 _function_ `uint GetInstanceUserData()` _[#if !defined(RAYTRACINGHITGROUPCOMMON_USH_INCLUDED)]_
- L111-114 _function_ `uint GetHitGroupUserData()` _[#if !defined(RAYTRACINGHITGROUPCOMMON_USH_INCLUDED)]_
- L116-163 _function_ `float3 GetGeometryNormalFromTriangleBaseAttributes(uint PrimitiveIndex, uint ClusterID)` _[#if !defined(RAYTRACINGHITGROUPCOMMON_USH_INCLUDED)]_
- L165-172 _function_ `uint GetClusterID()` _[#if !defined(RAYTRACINGHITGROUPCOMMON_USH_INCLUDED)]_

### `Shaders/Private/RayTracing/RayTracingInstanceBufferUtil.usf` (Private)

- lines: 312; parse: all-branches
- includes: L7 `RayTracingCommon.ush`, L8 `../SceneData.ush`, L9 `../ComputeShaderUtils.ush`, L10 `../Common.ush`, L11 `/Engine/Shared/RayTracingDebugTypes.h`, L14 `/Engine/Shared/NaniteRayTracingDefinitions.h` [NANITE_RAYTRACING]

#### Macros (#define, 1)

- L18 `#define THREADGROUP_SIZE 1` _[#if !defined(THREADGROUP_SIZE)]_

#### Entry points (1)

- L258-311 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void RayTracingBuildInstanceBufferCS(uint GroupThreadIndex : SV_GroupIndex, uint3 GroupId : SV_GroupID)` — stage: **compute** — C++: `FRayTracingBuildInstanceBufferCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/RayTracing/RayTracingInstanceBufferUtil.cpp:655)

#### Structs / classes (1)

- L21-30 _struct_ **`FRayTracingInstanceDescriptor`** `struct FRayTracingInstanceDescriptor`
  - L23 _member_ `uint GPUSceneInstanceOrTransformIndex;`
  - L24 _member_ `uint OutputDescriptorIndex;`
  - L25 _member_ `uint AccelerationStructureIndex;`
  - L26 _member_ `uint InstanceId;`
  - L27 _member_ `uint InstanceMaskAndFlags;`
  - L28 _member_ `uint InstanceContributionToHitGroupIndex;`
  - L29 _member_ `uint SceneInstanceIndexAndApplyLocalBoundsTransform;`

#### Global resources (textures / buffers / samplers) (9)

- L41 _resource_ `RWStructuredBuffer<FPlatformRayTracingInstanceDescriptor> OutPlatformInstanceDescriptors;`
- L44 _resource_ `RWStructuredBuffer<uint> OutHitGroupContributions;` _[#if USE_SEPARATE_HIT_CONTRIBUTION_BUFFER]_
- L47 _resource_ `StructuredBuffer<uint> InstanceGroupDescriptors;`
- L48 _resource_ `StructuredBuffer<FRayTracingInstanceDescriptor> InstanceDescriptors;`
- L49 _resource_ `ByteAddressBuffer AccelerationStructureAddresses;`
- L52 _resource_ `StructuredBuffer<float4> InstanceTransforms;` — Transforms are float3x4 row-major matrices stored as 3 float4 because of FXC matrix packing issues when using StructuredBuffer<float3x4>
- L55 _resource_ `RWStructuredBuffer<FRayTracingInstanceExtraData> RWInstanceExtraData;` — Extra per instance data
- L58 _resource_ `RWStructuredBuffer<uint> RWOutputStats;` _[#if OUTPUT_STATS]_
- L62 _resource_ `ByteAddressBuffer NaniteBLASData;`

#### Global parameters (uniforms) (15)

- L32 _parameter_ `uint MaxNumInstances;`
- L33 _parameter_ `uint NumGroups;`
- L34 _parameter_ `uint NumInstanceDescriptors;`
- L35 _parameter_ `uint BaseGroupDescriptorIndex;`
- L36 _parameter_ `uint BaseInstanceDescriptorIndex;`
- L38 _parameter_ `float3 PreViewTranslationHigh;`
- L39 _parameter_ `float3 PreViewTranslationLow;`
- L59 _parameter_ `uint OutputStatsOffset;` _[#if OUTPUT_STATS]_
- L66 _parameter_ `float CullingRadius;` _[#if GPU_CULLING]_
- L67 _parameter_ `float FarFieldCullingRadius;` _[#if GPU_CULLING]_
- L68 _parameter_ `float AngleThresholdRatioSq;` _[#if GPU_CULLING]_
- L69 _parameter_ `float3 ViewOrigin;` _[#if GPU_CULLING]_
- L70 _parameter_ `uint CullingMode;` _[#if GPU_CULLING]_
- L71 _parameter_ `uint CullUsingGroups;` _[#if GPU_CULLING]_
- L72 _parameter_ `int bUseDistanceToBox;` _[#if GPU_CULLING]_

#### Functions (2)

- L74-139 _function_ `bool CullInstance(FInstanceSceneData InstanceSceneData, FPrimitiveSceneData PrimitiveData, float4x4 LocalToTranslatedWorld4x4, bool bFarFieldInstance)` _[#if GPU_CULLING]_
- L143-256 _function_ `void ProcessInstance(FRayTracingInstanceDescriptor InputDesc)`

### `Shaders/Private/RayTracing/RayTracingLightCullingCommon.ush` (Private)

- lines: 125; parse: all-branches
- includes: L9 `../Visualization.ush`
- L7 #pragma `once`

#### Structs / classes (1)

- L14-123 _struct_ **`FCulledLightList`** `struct FCulledLightList`
  - L16 _member_ `uint NumLights;`
  - L17 _member_ `uint LightGridOffset;`
  - L19 _method_ `static FCulledLightList Create(float3 TranslatedWorldPos)`
  - L57 _method_ `uint GetNumLights()`
  - L62 _method_ `uint GetLightIndex(int LightNum, out uint Valid)`
  - L77 _method_ `float3 Visualize(int VisualizeMode)`

### `Shaders/Private/RayTracing/RayTracingLightFunctionCommon.ush` (Private)

- lines: 32; parse: all-branches

#### Functions (1)

- L6-29 _function_ `float3 GetRayTracingLightFunction(float3 TranslatedWorldPosition)` — base light function material shader, so it can be folded where apprpriate see LightFunctionCommon and LightFunctionPixelShader for additional information

### `Shaders/Private/RayTracing/RayTracingLightingCommon.ush` (Private)

- lines: 606; parse: first-branch (retry, +0 merged from all-branches pass)
- includes: L5 `RayTracingCommon.ush`, L7 `../DeferredLightingCommon.ush`, L8 `../PathTracing/Utilities/PathTracingRandomSequence.ush`, L9 `../LightShaderParameters.ush`, L10 `RayTracingDirectionalLight.ush`, L11 `RayTracingRectLight.ush`, L12 `RayTracingSphereLight.ush`, L13 `RayTracingCapsuleLight.ush`, L14 `RayTracingSkyLightEvaluation.ush`, L15 `RayTracingLightCullingCommon.ush`, L16 `/Engine/Shared/LightDefinitions.h`, L17 `/Engine/Shared/RayTracingTypes.h`

#### Macros (#define, 1)

- L20 `#define ENABLE_FAR_FIELD_TRACING 0` _[#if !defined(ENABLE_FAR_FIELD_TRACING)]_
- L3 #pragma `once`

#### Functions (11)

- L23-82 _function_ `FDeferredLightData GetRayTracingDeferredLightData( int LightIndex, bool bIndirectLighting, inout uint OutLightType, inout uint OutLightMissShaderIndex)`
- L84-91 _function_ `FDeferredLightData GetRayTracingDeferredLightData( int LightIndex, bool bIndirectLighting, inout uint OutLightType)`
- L93-125 _function_ `float3 GenerateReflectedRayDirection( float3 IncidentDirection, float3 WorldNormal, float Roughness, float2 RandSample )`
- L127-146 _function_ `void TraceShadowRayMissShaderLighting( in FRayDesc Ray, in uint RayFlags, in uint InstanceInclusionMask, in RaytracingAccelerationStructure TLAS, in uint MissShaderIndex, inout FPackedMaterialClosestHitPayload PackedPayload)`
- L149-231 _function_ `float4 SampleAreaLightDirection( in FDeferredLightData LightData, in float3 TranslatedWorldPosition, in float3 WorldNormal, in uint LightType, inout FRandomSequence RandSequence )` — Returns xyz: Direction, w: RayLength
- L233-245 _function_ `float3 ComputeIndirectLighting( in float3 TranslatedWorldPosition, in float3 ViewDirection, in RaytracingAccelerationStructure TLAS, in uint2 PixelCoord, in FPackedMaterialClosestHitPayload Payload, in bool bRayTraceSkyLightContribution, in bool bDecoupleSampleGeneration)`
- L296-316 _function_ `bool HasBackfaceDiffuse(FPackedMaterialClosestHitPayload Payload)`
- L318-479 _function_ `float3 ComputeDirectLighting( in float3 TranslatedWorldPosition, in float3 ViewDirection, in FRayCone RayCone, in RaytracingAccelerationStructure TLAS, in RaytracingAccelerationStructure FarFieldTLAS, inout FPackedMaterialClosestHitPayload Payload, inout FRandomSequence RandSequence, in uint ShadowsType, in uint ShadowsTranslucencyType, float ShadowMaxNormalBias, float MaxTraceDistance)`
- L481-484 _function_ `void ComputeBottomLayerMaterialProperties(FRayDesc Ray, inout FMaterialClosestHitPayload Payload)`
- L486-543 _function_ `void AccumulateResults( inout FPackedMaterialClosestHitPayload Payload, in float3 TranslatedWorldPosition, in float3 ViewDirection, in RaytracingAccelerationStructure TLAS, in RaytracingAccelerationStructure FarFieldTLAS, inout FRandomSequence RandSequence, in uint2 PixelCoord, in float ShadowMaxNormalBias, float MaxTraceDistance, in uint ShadowsType, in uint ShadowsTranslucencyType, in uint ShouldDoDirectLighting, in uint ShouldDoEmissiveAndIndirectLighting, in bool bRayTraceSkyLightContribution, in bool bDecoupleSampleGeneration, inout FRayCone RayCone, inout float3 Radiance)`
- L545-606 _function_ `FMaterialClosestHitPayload TraceRayAndAccumulateResults( in FRayDesc Ray, in RaytracingAccelerationStructure TLAS, in RaytracingAccelerationStructure FarFieldTLAS, in uint RayFlags, in uint InstanceInclusionMask, inout FRandomSequence RandSequence, in uint2 PixelCoord, in float ShadowMaxNormalBias, float MaxTraceDistance, in uint ShadowsType, in uint ShadowsTranslucencyType, in uint ShouldDoDirectLighting, in uint ShouldDoEmissiveAndIndirectLighting, in bool bRayTraceSkyLightContribution, in bool bDecoupleSampleGeneration, in bool bIsCameraRay, inout FRayCone RayCone, in bool bEnableSkyLightContribution, inout float3 Radiance)`

### `Shaders/Private/RayTracing/RayTracingLightingMS.usf` (Private)

- lines: 144; parse: all-branches
- includes: L3 `/Engine/Shared/RayTracingTypes.h`, L4 `../Common.ush`, L24 `../SceneTextureParameters.ush`, L25 `RayTracingCommon.ush`, L26 `../Lumen/LumenDiffuseColorBoost.ush`, L32 `../Substrate/Substrate.ush` [SUBSTRATE_ENABLED], L33 `../Substrate/SubstrateEvaluation.ush` [SUBSTRATE_ENABLED], L36 `RayTracingDeferredShadingCommon.ush`, L37 `RayTracingLightingCommon.ush`, L39 `../Substrate/SubstrateDeferredLighting.ush` [SUBSTRATE_ENABLED], L44 `/Engine/Generated/Material.ush` [SUPPORT_LIGHT_FUNCTION], L51 `../LightFunctionCommon.ush` [SUPPORT_LIGHT_FUNCTION], L52 `RayTracingLightFunctionCommon.ush` [SUPPORT_LIGHT_FUNCTION]

#### Macros (#define, 15)

- L6 `#define SUPPORT_CONTACT_SHADOWS 0`
- L7 `#define USE_SOURCE_TEXTURE 1`
- L8 `#define USE_SOURCE_TEXTURE_ARRAY 1`
- L10 `#define PreIntegratedGF ReflectionStruct.PreIntegratedGF`
- L11 `#define PreIntegratedGFSampler ReflectionStruct.PreIntegratedGFSampler`
- L14 `#define SUBSTRATE_SSS_MATERIAL_OVERRIDE 0`
- L15 `#define MATERIAL_FULLY_ROUGH 0`
- L16 `#define SUBSTRATE_COMPLEXSPECIALPATH 0`
- L17 `#define SUBSTRATE_GLINTS_ALLOWED 0`
- L18 `#define SUBSTRATE_DIFFUSE_COLOR_BOOST 1`
- L21 `#define SUPPORT_LIGHT_FUNCTION 0` _[#if !defined(SUPPORT_LIGHT_FUNCTION)]_
- L43 `#define CameraRelativeLightPosition RaytracingLightFunctionParameters.CameraRelativeLightPosition` _[#if SUPPORT_LIGHT_FUNCTION]_
- L47 `#define LightFunctionParameters RaytracingLightFunctionParameters.LightFunctionParameters` _[#if SUPPORT_LIGHT_FUNCTION]_
- L48 `#define LightFunctionParameters2 RaytracingLightFunctionParameters.LightFunctionParameters2` _[#if SUPPORT_LIGHT_FUNCTION]_
- L49 `#define LightFunctionTranslatedWorldToLight RaytracingLightFunctionParameters.LightFunctionTranslatedWorldToLight` _[#if SUPPORT_LIGHT_FUNCTION]_

#### Entry points (1)

- L55-144 _entry_ `RAY_TRACING_ENTRY_MISS(RayTracingLightingMS, FPackedMaterialClosestHitPayload, PackedPayload)` — stage: **miss** — C++: `FRayTracingLightingMS` SF_RayMiss via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/RayTracing/RayTracingLighting.cpp:510) — C++: `FLightFunctionRayTracingShader` SF_RayMiss via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/RayTracing/RayTracingLighting.cpp:645)

### `Shaders/Private/RayTracing/RayTracingMaterialDefaultHitShaders.usf` (Private)

- lines: 36; parse: all-branches
- includes: L3 `../Common.ush`, L4 `RayTracingCommon.ush`

#### Entry points (4)

- L7-12 _entry_ `RAY_TRACING_ENTRY_CLOSEST_HIT(OpaqueShadowCHS, FPackedMaterialClosestHitPayload, PackedPayload, FRayTracingIntersectionAttributes, Attributes)` — stage: **closesthit** — C++: `FTrivialMaterialCHS` SF_RayHitGroup via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/RayTracing/RayTracingMaterialHitShaders.cpp:272) — C++: `FOpaqueShadowHitGroup` SF_RayHitGroup via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/RayTracing/RayTracingMaterialHitShaders.cpp:299) _[#if IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_RAYTRACING_MATERIAL)]_
- L14-18 _entry_ `RAY_TRACING_ENTRY_CLOSEST_HIT(HiddenMaterialCHS, FPackedMaterialClosestHitPayload, PackedPayload, FRayTracingIntersectionAttributes, Attributes)` — stage: **closesthit** — C++: `FHiddenMaterialHitGroup` SF_RayHitGroup via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/RayTracing/RayTracingMaterialHitShaders.cpp:298) _[#if IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_RAYTRACING_MATERIAL)]_
- L20-25 _entry_ `RAY_TRACING_ENTRY_ANY_HIT(HiddenMaterialAHS, FPackedMaterialClosestHitPayload, PackedPayload, FRayTracingIntersectionAttributes, Attributes)` — stage: **anyhit** — C++: `FHiddenMaterialHitGroup` SF_RayHitGroup via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/RayTracing/RayTracingMaterialHitShaders.cpp:298) _[#if IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_RAYTRACING_MATERIAL)]_
- L29-34 _entry_ `RAY_TRACING_ENTRY_CALLABLE(DefaultCallableShader, FDecalShaderPayload, Params)` — stage: **callable** — C++: `FDefaultCallableShader` SF_RayCallable via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/RayTracing/RayTracingMaterialHitShaders.cpp:300) _[#if IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_DECALS)]_

### `Shaders/Private/RayTracing/RayTracingMaterialHitShaders.usf` (Private)

- lines: 1025; parse: first-branch (retry, +0 merged from all-branches pass)
- includes: L29 `/Engine/Private/Common.ush`, L30 `RayTracingCommon.ush`, L31 `RayTracingHitGroupCommon.ush`, L32 `RayTracingShaderUtils.ush`, L33 `/Engine/Private/PathTracing/Material/PathTracingFresnel.ush`, L35 `/Engine/Generated/Material.ush`, L36 `/Engine/Generated/VertexFactory.ush`, L38 `RayTracingCalcInterpolants.ush`, L39 `/Engine/Private/ShadingCommon.ush`, L40 `/Engine/Private/DeferredShadingCommon.ush`, L41 `/Engine/Private/SHCommon.ush`, L42 `/Engine/Private/ReflectionEnvironmentShared.ush`, L43 `/Engine/Private/VirtualTextureCommon.ush`, L44 `/Engine/Private/LightmapCommon.ush`, L45 `/Engine/Private/Lumen/LumenHardwareRayTracingPayloadCommon.ush`, L48 `/Engine/Private/Substrate/SubstrateExport.ush`

#### Macros (#define, 9)

- L5 `#define ENABLE_SKY_LIGHT 1`
- L6 `#define NEEDS_LIGHTMAP_COORDINATE (HQ_TEXTURE_LIGHTMAP \|\| LQ_TEXTURE_LIGHTMAP)`
- L11 `#define NEEDS_VERTEX_FACTORY_INTERPOLATION 1`
- L14 `#define EYE_ADAPTATION_PREV_FRAME_EXPOSURE 1`
- L17 `#define SUBSTRATE_INLINE_SHADING 1` _[#if SUBSTRATE_ENABLED]_
- L18 `#define SUBSTRATE_USES_FORCED_COMPLEXITY 0` _[#if SUBSTRATE_ENABLED]_
- L26 `#define SUBSTRATE_COMPLEXSPECIALPATH 0` _[#if SUBSTRATE_USE_FULLYSIMPLIFIED_MATERIAL]_
- L47 `#define MATERIAL_SUBSTRATE_OPAQUE_PRECOMPUTED_LIGHTING 0`
- L350 `#define CurrentBSDF SubstratePixelHeader.SubstrateTree.BSDFs[0]` _[#if SUBSTRATE_GBUFFER_FORMAT==1 && MATERIAL_IS_SUBSTRATE && !(SUBSTRATE_OPTIMIZED_UNLIT)]_
- L3 #pragma `once`; L8 #undef `NEEDS_VERTEX_FACTORY_INTERPOLATION`; L24 #undef `SUBSTRATE_COMPLEXSPECIALPATH`; L383 #undef `CurrentBSDF`

#### Entry points (2)

- L639-800 _entry_ `RAY_TRACING_ENTRY_CLOSEST_HIT(MaterialCHS, FPackedMaterialClosestHitPayload, PackedPayload, FRayTracingIntersectionAttributes, Attributes)` — stage: **closesthit** — C++: `template<>` SF_RayHitGroup via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/RayTracing/RayTracingMaterialHitShaders.cpp:276) — C++: `template<>` SF_RayHitGroup via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/RayTracing/RayTracingMaterialHitShaders.cpp:278) — C++: `template<>` SF_RayHitGroup via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/RayTracing/RayTracingMaterialHitShaders.cpp:280) — C++: `template<>` SF_RayHitGroup via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/RayTracing/RayTracingMaterialHitShaders.cpp:282) — C++: `template<>` SF_RayHitGroup via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/RayTracing/RayTracingMaterialHitShaders.cpp:284) — C++: `template<>` SF_RayHitGroup via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/RayTracing/RayTracingMaterialHitShaders.cpp:286) — C++: `template<>` SF_RayHitGroup via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/RayTracing/RayTracingMaterialHitShaders.cpp:288) — C++: `template<>` SF_RayHitGroup via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/RayTracing/RayTracingMaterialHitShaders.cpp:290)
- L802-1024 _entry_ `RAY_TRACING_ENTRY_ANY_HIT(MaterialAHS, FPackedMaterialClosestHitPayload, PackedPayload, FRayTracingIntersectionAttributes, Attributes)` — stage: **anyhit** — C++: `template<>` SF_RayHitGroup via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/RayTracing/RayTracingMaterialHitShaders.cpp:278) — C++: `template<>` SF_RayHitGroup via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/RayTracing/RayTracingMaterialHitShaders.cpp:282) — C++: `template<>` SF_RayHitGroup via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/RayTracing/RayTracingMaterialHitShaders.cpp:286) — C++: `template<>` SF_RayHitGroup via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/RayTracing/RayTracingMaterialHitShaders.cpp:290)

#### Functions (4)

- L51-144 _function_ `void GetSkyLighting( FMaterialPixelParameters MaterialParameters, VTPageTableResult LightmapVTPageTableResult, float3 WorldNormal, LightmapUVType LightmapUV, uint LightmapDataIndex, float3 SkyOcclusionUV3D, uint ShadingModel, bool bEnableSkyLightContribution, out float3 OutDiffuseLighting, out float3 OutSubsurfaceLighting)` — Computes sky diffuse lighting, including precomputed shadowing.
- L148-169 _function_ `float GetRefractionIor(FPixelMaterialInputs PixelMaterialInputs)` — TODO: Consolidate this definition with similar one in PathTracing Material _[#if !SUBSTRATE_ENABLED \|\| SUBSTRATE_GBUFFER_FORMAT==0]_
- L176-258 _function_ `void GetPrecomputedIndirectLightingAndSkyLight( FMaterialPixelParameters MaterialParameters, FVertexFactoryInterpolantsVSToPS Interpolants, VTPageTableResult LightmapVTPageTableResult, float3 DiffuseDir, float3 VolumetricLightmapBrickTextureUVs, bool bEvaluateBackface, bool bEnableSkyLightContribution, out float3 OutDiffuseLighting, out float3 OutSubsurfaceLighting, out float OutIndirectIrradiance)` — Calculates indirect lighting contribution on this object from precomputed data.
- L260-421 _function_ `void GetMaterialPayload( FPixelMaterialInputs PixelMaterialInputs, FMaterialPixelParameters MaterialParameters, FVertexFactoryInterpolantsVSToPS Interpolants, bool bIsEnableSkyLightContribution, float Dither, inout FMaterialClosestHitPayload Payload)`

#### C++ shader bindings (IMPLEMENT_* naming this file, 4)

- `MaterialIS` → entry not found in file (macro-generated or #include'd); C++ `template<>` SF_RayHitGroup via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/RayTracing/RayTracingMaterialHitShaders.cpp:284)
- `MaterialIS` → entry not found in file (macro-generated or #include'd); C++ `template<>` SF_RayHitGroup via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/RayTracing/RayTracingMaterialHitShaders.cpp:286)
- `MaterialIS` → entry not found in file (macro-generated or #include'd); C++ `template<>` SF_RayHitGroup via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/RayTracing/RayTracingMaterialHitShaders.cpp:288)
- `MaterialIS` → entry not found in file (macro-generated or #include'd); C++ `template<>` SF_RayHitGroup via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/RayTracing/RayTracingMaterialHitShaders.cpp:290)

### `Shaders/Private/RayTracing/RayTracingOcclusionRGS.usf` (Private)

- lines: 899; parse: all-branches
- includes: L9 `../Common.ush`, L10 `../MonteCarlo.ush`, L11 `../DeferredShadingCommon.ush`, L12 `../LightShaderParameters.ush`, L13 `../SceneTextureParameters.ush`, L14 `../ScreenSpaceDenoise/SSDPublic.ush`, L15 `../TransmissionCommon.ush`, L16 `../HairStrands/HairStrandsVisibilityCommon.ush`, L17 `../Substrate/Substrate.ush`, L18 `../Substrate/SubstrateSubsurface.ush`, L19 `RayTracingCommon.ush`, L20 `RayTracingDeferredShadingCommon.ush`, L21 `RayTracingDirectionalLight.ush`, L22 `RayTracingRectLight.ush`, L23 `RayTracingSphereLight.ush`, L24 `RayTracingCapsuleLight.ush`, L25 `/Engine/Shared/LightDefinitions.h`, L62 `../HairStrands/HairStrandsRaytracing.ush` [USE_HAIR_LIGHTING]

#### Macros (#define, 8)

- L7 `#define SUBSTRATE_MATERIALCONTAINER_IS_VIEWRESOURCE 1`
- L27 `#define USE_TRANSLUCENT_SHADOW !COMPUTESHADER`
- L29 `#define ShadowMaskType_Opaque 0`
- L30 `#define ShadowMaskType_Hair 1`
- L55 `#define TransmissionSampling_ConstantTrackingInfiniteDomain 0`
- L56 `#define TransmissionSampling_ConstantTrackingFiniteDomain 1`
- L58 `#define TransmissionMeanFreePathType_ExtinctionScale 0`
- L59 `#define TransmissionMeanFreePathType_MaxMeanFreePath 1`
- L4 #pragma `message("UESHADERMETADATA_VERSION 42D4CD2F-D217-4305-81AB-F113F7114047")`

#### Entry points (1)

- L666-898 _entry_ `RAY_TRACING_ENTRY_RAYGEN_OR_INLINE(Occlusion)` — stage: **raygeneration\|compute(inline)**

#### Structs / classes (2)

- L300-308 _struct_ **`FOcclusionResult`** `struct FOcclusionResult`
  - L302 _member_ `float Visibility;`
  - L303 _member_ `float SumRayDistance;`
  - L304 _member_ `float ClosestRayDistance;`
  - L305 _member_ `float TransmissionDistance;`
  - L306 _member_ `float HitCount;`
  - L307 _member_ `float RayCount;`
- L343-351 _struct_ **`FOcclusionShadingParameters`** `struct FOcclusionShadingParameters`
  - L345 _member_ `bool bIsValid;`
  - L346 _member_ `bool bBackfaceCulling;`
  - L347 _member_ `bool bIsHair;`
  - L348 _member_ `bool bIsHairStrands;`
  - L349 _member_ `bool bIsSubsurface;`
  - L350 _member_ `bool bHasSubsurfaceProfile;`

#### Global resources (textures / buffers / samplers) (5)

- L32 _resource_ `RaytracingAccelerationStructure TLAS;`
- L33 _resource_ `RWTexture2D<float4> RWOcclusionMaskUAV;`
- L34 _resource_ `RWTexture2D<float> RWRayDistanceUAV;`
- L35 _resource_ `RWTexture2D<float4> RWSubPixelOcclusionMaskUAV;`
- L65 _resource_ `Texture2D<uint> HairLightChannelMaskTexture;` _[#if USE_HAIR_LIGHTING]_

#### Global parameters (uniforms) (19)

- L37 _parameter_ `uint LightingChannelMask;`
- L38 _parameter_ `uint SamplesPerPixel;`
- L39 _parameter_ `float NormalBias;`
- L40 _parameter_ `int4 LightScissor;`
- L41 _parameter_ `int2 PixelOffset;`
- L42 _parameter_ `float TraceDistance;`
- L43 _parameter_ `float LODTransitionStart;`
- L44 _parameter_ `float LODTransitionEnd;`
- L45 _parameter_ `float AvoidSelfIntersectionTraceDistance;`
- L46 _parameter_ `uint bTransmissionSamplingDistanceCulling;`
- L47 _parameter_ `uint TransmissionSamplingTechnique;`
- L48 _parameter_ `uint TransmissionMeanFreePathType;`
- L49 _parameter_ `uint RejectionSamplingTrials;`
- L50 _parameter_ `uint bAcceptFirstHit;`
- L51 _parameter_ `uint bTwoSidedGeometry;`
- L52 _parameter_ `uint bTranslucentShadow;`
- L53 _parameter_ `uint MaxTranslucencyHitCount;`
- L63 _parameter_ `uint bUseHairVoxel;` _[#if USE_HAIR_LIGHTING]_
- L64 _parameter_ `float HairOcclusionThreshold;` _[#if USE_HAIR_LIGHTING]_

#### Functions (8)

- L67-82 _function_ `bool NeedTraceHair( in uint2 PixelCoord, inout float HairDeviceZ)` _[#if USE_HAIR_LIGHTING]_
- L85-163 _function_ `bool GenerateOcclusionRay( FLightShaderParameters LightParameters, float3 TranslatedWorldPosition, float3 WorldNormal, float2 RandSample, out float3 RayOrigin, out float3 RayDirection, out float RayTMin, out float RayTMax )`
- L165-298 _function_ `float ComputeDiffuseTransmission( float3 V, float3 P, float3 N, float MeanFreePath, float MaxTransmissionDistance, float Eta, FLightShaderParameters LightParameters, float2 LightSample, inout FRandomSequence RandSequence, uint RejectionRetryMax, uint2 PixelCoord)`
- L310-322 _function_ `FOcclusionResult InitOcclusionResult()`
- L324-327 _function_ `float OcclusionToShadow(FOcclusionResult In, uint LocalSamplesPerPixel)`
- L329-341 _function_ `FRayDesc Invert(in FRayDesc Ray)`
- L353-647 _function_ `FOcclusionResult ComputeOcclusion( const uint2 PixelCoord, const uint RaytracingMask, const float DeviceZ, float3 WorldNormal, const FOcclusionShadingParameters ShadingDesc, const FLightShaderParameters LightParameters, const FTransmissionProfileParams TransmissionProfileParams, const float SubsurfaceSamplingMeanFreePath, const uint LocalSamplesPerPixel)`
- L650-663 _function_ `float DecodeSamplingSSSProfileRadius(FGBufferData GBufferData)` _[#if SUBSTRATE_GBUFFER_FORMAT==0]_

### `Shaders/Private/RayTracing/RayTracingPrimaryRays.usf` (Private)

- lines: 537; parse: all-branches
- includes: L4 `/Engine/Shared/RayTracingTypes.h`, L5 `../Common.ush`, L13 `../DeferredShadingCommon.ush`, L14 `../DeferredLightingCommon.ush`, L15 `../ReflectionEnvironmentShared.ush`, L16 `../Montecarlo.ush`, L17 `../PathTracing/Utilities/PathTracingRandomSequence.ush`, L18 `../PathTracing/Material/PathTracingFresnel.ush`, L19 `../HeightFogCommon.ush`, L20 `../SobolRandom.ush`, L21 `../SceneTextureParameters.ush`, L22 `RayTracingCommon.ush`, L23 `RayTracingDeferredShadingCommon.ush`, L24 `RayTracingHitGroupCommon.ush`, L32 `../Substrate/Substrate.ush`, L33 `../Substrate/SubstrateEvaluation.ush`, L60 `RayTracingLightingCommon.ush`, L64 `../Lumen/LumenTranslucencyVolumeShared.ush`

#### Macros (#define, 10)

- L7 `#define SUPPORT_CONTACT_SHADOWS 0`
- L8 `#define USE_SOURCE_TEXTURE 1`
- L10 `#define PreIntegratedGF ReflectionStruct.PreIntegratedGF`
- L11 `#define PreIntegratedGFSampler GlobalBilinearClampedSampler`
- L26 `#define ERayTracingPrimaryRaysFlag_None 0`
- L27 `#define ERayTracingPrimaryRaysFlag_UseGBufferForMaxDistance (1u << 0)`
- L28 `#define ERayTracingPrimaryRaysFlag_PrimaryView (1u << 1)`
- L29 `#define ERayTracingPrimaryRaysFlag_AllowSkipSkySample (1u << 2)`
- L31 `#define SUBSTRATE_MATERIALCONTAINER_IS_VIEWRESOURCE 0`
- L62 `#define RadianceCacheInterpolation LumenGIVolumeStruct`

#### Entry points (1)

- L87-536 _entry_ `RAY_TRACING_ENTRY_RAYGEN(RayTracingPrimaryRaysRGS)` — stage: **raygeneration** — C++: `FRayTracingPrimaryRaysRGS` SF_RayGen via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/RayTracing/RayTracingPrimaryRays.cpp:83)

#### Global resources (textures / buffers / samplers) (5)

- L52 _resource_ `Texture2D SceneColorTexture;`
- L54 _resource_ `RaytracingAccelerationStructure TLAS;`
- L55 _resource_ `RaytracingAccelerationStructure FarFieldTLAS;`
- L57 _resource_ `RWTexture2D<float4> ColorOutput;`
- L58 _resource_ `RWTexture2D<float> RayHitDistanceOutput;`

#### Global parameters (uniforms) (15)

- L35 _parameter_ `int SamplesPerPixel;`
- L36 _parameter_ `int MaxRefractionRays;`
- L37 _parameter_ `int HeightFog;`
- L38 _parameter_ `int ForceOpaqueRays;`
- L39 _parameter_ `int ShadowsType;`
- L40 _parameter_ `int ShadowsTranslucencyType;`
- L41 _parameter_ `int ShouldDoDirectLighting;`
- L42 _parameter_ `int ShouldDoEmissiveAndIndirectLighting;`
- L43 _parameter_ `int UpscaleFactor;`
- L44 _parameter_ `uint PrimaryRayFlags;`
- L46 _parameter_ `float TranslucencyMinRayDistance;`
- L47 _parameter_ `float TranslucencyMaxRayDistance;`
- L48 _parameter_ `float TranslucencyMaxRoughness;`
- L49 _parameter_ `int TranslucencyRefraction;`
- L50 _parameter_ `float MaxNormalBias;`

#### Functions (3)

- L66-72 _function_ `float CalcNoT(float CosTheta1, float N1, float N2)`
- L74-79 _function_ `float FresnelDielectric(float Eta, float IoH, float ToH)`
- L81-85 _function_ `float3 GetSkyRadiance(float3 Direction, float Roughness)`

### `Shaders/Private/RayTracing/RayTracingRayCone.ush` (Private)

- lines: 30; parse: all-branches
- L3 #pragma `once`

#### Structs / classes (1)

- L5-9 _struct_ **`FRayCone`** `struct FRayCone`
  - L7 _member_ `float Width;`
  - L8 _member_ `float SpreadAngle;`

#### Functions (3)

- L11-17 _function_ `FRayCone UnpackRayCone(uint PackedRayCone)`
- L19-22 _function_ `uint PackRayCone(FRayCone RayCone)`
- L24-30 _function_ `FRayCone PropagateRayCone(in FRayCone Cone, in float SurfaceSpreadAngle, in float HitT)`

### `Shaders/Private/RayTracing/RayTracingRectLight.ush` (Private)

- lines: 46; parse: all-branches
- includes: L5 `../LightShaderParameters.ush`, L6 `../PathTracing/Utilities/PathTracingRandomSequence.ush`, L7 `../RectLight.ush`
- L3 #pragma `once`

#### Functions (1)

- L9-46 _function_ `bool GenerateRectLightOcclusionRay( FLightShaderParameters LightParameters, float3 TranslatedWorldPosition, float3 WorldNormal, float2 RandSample, out float3 RayOrigin, out float3 RayDirection, out float RayTMin, out float RayTMax, out float RayPdf )`

### `Shaders/Private/RayTracing/RayTracingReflectionEnvironment.ush` (Private)

- lines: 33; parse: all-branches
- includes: L30 `../ReflectionEnvironmentShared.ush`, L31 `../ReflectionEnvironmentComposite.ush`

#### Macros (#define, 7)

- L13 `#define REFLECTION_COMPOSITE_HAS_BOX_CAPTURES 1`
- L14 `#define REFLECTION_COMPOSITE_HAS_SPHERE_CAPTURES 1`
- L15 `#define REFLECTION_COMPOSITE_USE_BLENDED_REFLECTION_CAPTURES 1`
- L16 `#define REFLECTION_COMPOSITE_SUPPORT_SKYLIGHT_BLEND 1`
- L21 `#define ENABLE_SKY_LIGHT 1`
- L26 `#define ALLOW_STATIC_LIGHTING 0`
- L29 `#define REFLECTION_COMPOSITE_NO_CULLING_DATA `
- L3 #pragma `once`; L19 #undef `ENABLE_SKY_LIGHT`; L24 #undef `ALLOW_STATIC_LIGHTING`

### `Shaders/Private/RayTracing/RayTracingShaderUtils.ush` (Private)

- lines: 27; parse: all-branches
- includes: L13 `RayTracingCommon.ush` [!defined(PATH_TRACING)]
- L3 #pragma `once`

#### static variables (1)

- L15 _static_var_ `static int CurrentPayloadInputFlags = 0;` _[#if !defined(PATH_TRACING)]_

#### Functions (2)

- L17-20 _function_ `bool GetShadowReplaceState()` _[#if !defined(PATH_TRACING)]_
- L22-25 _function_ `float IsShadowDepthShader()` _[#if !defined(PATH_TRACING)]_

### `Shaders/Private/RayTracing/RayTracingSkyLightCommon.ush` (Private)

- lines: 123; parse: all-branches
- includes: L9 `../MonteCarlo.ush`

#### Macros (#define, 1)

- L18 `#define USE_HIERARCHICAL_IMPORTANCE_SAMPLING 1`
- L7 #pragma `once`

#### Structs / classes (1)

- L45-49 _struct_ **`FSkyLightSample`** `struct FSkyLightSample`
  - L46 _member_ `float3 Direction;`
  - L47 _member_ `float3 Radiance;`
  - L48 _member_ `float Pdf;`

#### Global resources (textures / buffers / samplers) (3)

- L12 _resource_ `Texture2D SkylightTexture;` — shader parameters for skylight integration
- L13 _resource_ `Texture2D<float> SkylightPdf;`
- L14 _resource_ `SamplerState SkylightTextureSampler;`

#### Global parameters (uniforms) (2)

- L15 _parameter_ `float SkylightInvResolution;`
- L16 _parameter_ `int SkylightMipCount;`

#### Functions (3)

- L20-28 _function_ `float SkyLight_Estimate()`
- L31-43 _function_ `float4 SkyLight_EvalLight(float3 Dir)` — Returns: Radiance and Pdf for the specified direction
- L51-122 _function_ `FSkyLightSample SkyLight_SampleLight(float2 RandSample)`

### `Shaders/Private/RayTracing/RayTracingSkyLightEvaluation.ush` (Private)

- lines: 327; parse: all-branches
- includes: L9 `../Common.ush`, L10 `../ShadingModels.ush`, L11 `../DeferredShadingCommon.ush`, L12 `../ReflectionEnvironmentShared.ush`, L13 `RayTracingCommon.ush`, L14 `RayTracingSkyLightCommon.ush`, L15 `SkyLightVisibilityRaysData.ush`, L25 `../HairStrands/HairStrandsRaytracing.ush` [USE_HAIR_LIGHTING]

#### Macros (#define, 1)

- L21 `#define USE_HAIR_LIGHTING 0` _[#if !defined(USE_HAIR_LIGHTING)]_
- L7 #pragma `once`

#### Global resources (textures / buffers / samplers) (1)

- L18 _resource_ `StructuredBuffer<FSkyLightVisibilityRays> SkyLightVisibilityRays;`

#### Global parameters (uniforms) (1)

- L17 _parameter_ `uint3 SkyLightVisibilityRaysDimensions;`

#### Functions (2)

- L40-291 _function_ `void SkyLightEvaluate( in const uint2 SampleCoord, in const uint2 PixelCoord, in const uint SamplesPerPixel, in const float3 TranslatedWorldPosition, in const float3 WorldNormal, in const float3 ViewDirection, in const FGBufferData GBufferData, in const RaytracingAccelerationStructure TLAS, in const bool bGBufferSampleOrigin, in const float DeviceZ, in const bool bDecoupleSampleGeneration, inout float3 ExitantRadiance, inout float3 DiffuseExitantRadiance, inout float AmbientOcclusion, inout float HitDistance)` — UE_DEPRECATED 5.7 - Deprecated by Substrate
- L295-327 _function_ `void SkyLightEvaluate( in const uint2 SampleCoord, in const uint SamplesPerPixel, in const float3 TranslatedWorldPosition, in const float3 WorldNormal, in const float3 ViewDirection, in const FGBufferData GBufferData, in const RaytracingAccelerationStructure TLAS, in const bool bGBufferSampleOrigin, in const float DeviceZ, in const bool bDecoupleSampleGeneration, inout float3 ExitantRadiance, inout float3 DiffuseExitantRadiance, inout float AmbientOcclusion, inout float HitDistance)` — UE_DEPRECATED 5.7 - Deprecated by Substrate special case of pixel coord == sample coord

### `Shaders/Private/RayTracing/RayTracingSkyLightRGS.usf` (Private)

- lines: 161; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../SceneTextureParameters.ush`, L5 `../PathTracing/Utilities/PathTracingRandomSequence.ush`, L8 `../HairStrands/HairStrandsRaytracing.ush` [USE_HAIR_LIGHTING], L18 `../Substrate/Substrate.ush` [SUBSTRATE_ENABLED && SUBSTRATE_GBUFFER_FORMAT==1], L19 `../Substrate/SubstrateEvaluation.ush` [SUBSTRATE_ENABLED && SUBSTRATE_GBUFFER_FORMAT==1], L22 `RayTracingSkyLightEvaluation.ush`, L23 `RayTracingDeferredShadingCommon.ush`

#### Macros (#define, 6)

- L12 `#define SUBSTRATE_MATERIALCONTAINER_IS_VIEWRESOURCE 1` _[#if SUBSTRATE_ENABLED && SUBSTRATE_GBUFFER_FORMAT==1]_
- L13 `#define SUBSTRATE_FASTPATH 0` _[#if SUBSTRATE_ENABLED && SUBSTRATE_GBUFFER_FORMAT==1]_
- L14 `#define SUBSTRATE_SINGLEPATH 0` _[#if SUBSTRATE_ENABLED && SUBSTRATE_GBUFFER_FORMAT==1]_
- L15 `#define SUBSTRATE_COMPLEXSPECIALPATH 0` _[#if SUBSTRATE_ENABLED && SUBSTRATE_GBUFFER_FORMAT==1]_
- L16 `#define SUBSTRATE_SSS_MATERIAL_OVERRIDE 0` _[#if SUBSTRATE_ENABLED && SUBSTRATE_GBUFFER_FORMAT==1]_
- L17 `#define SUBSTRATE_GLINTS_ALLOWED 0` _[#if SUBSTRATE_ENABLED && SUBSTRATE_GBUFFER_FORMAT==1]_

#### Entry points (1)

- L32-161 _entry_ `RAY_TRACING_ENTRY_RAYGEN(SkyLightRGS)` — stage: **raygeneration** — C++: `FRayTracingSkyLightRGS` SF_RayGen via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/RayTracing/RaytracingSkylight.cpp:272)

#### Global resources (textures / buffers / samplers) (3)

- L27 _resource_ `RaytracingAccelerationStructure TLAS;`
- L29 _resource_ `RWTexture2D<float4> RWSkyOcclusionMaskUAV;`
- L30 _resource_ `RWTexture2D<float2> RWSkyOcclusionRayDistanceUAV;`

#### Global parameters (uniforms) (1)

- L25 _parameter_ `uint UpscaleFactor;`

### `Shaders/Private/RayTracing/RayTracingSphereLight.ush` (Private)

- lines: 91; parse: all-branches
- includes: L5 `../LightShaderParameters.ush`
- L3 #pragma `once`

#### Functions (2)

- L7-34 _function_ `bool GenerateSphereLightOcclusionRayWithAreaSampling( FLightShaderParameters LightParameters, float3 TranslatedWorldPosition, float3 WorldNormal, float2 RandSample, out float3 RayOrigin, out float3 RayDirection, out float RayTMin, out float RayTMax, out float RayPdf )`
- L36-91 _function_ `bool GenerateSphereLightOcclusionRayWithSolidAngleSampling( FLightShaderParameters LightParameters, float3 TranslatedWorldPosition, float3 WorldNormal, float2 RandSample, out float3 RayOrigin, out float3 RayDirection, out float RayTMin, out float RayTMax, out float RayPdf )`

### `Shaders/Private/RayTracing/RayTracingTest.usf` (Private)

- lines: 36; parse: all-branches
- includes: L3 `../Common.ush`, L4 `RayTracingCommon.ush`

#### Entry points (1)

- L10-35 _entry_ `RAY_TRACING_ENTRY_RAYGEN(TestMainRGS)` — stage: **raygeneration** — C++: `FTestRaygenShader` SF_RayGen via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Tests/RayTracingTestbed.cpp:368)

#### Global resources (textures / buffers / samplers) (3)

- L6 _resource_ `RaytracingAccelerationStructure TLAS;`
- L7 _resource_ `StructuredBuffer<FBasicRayData> Rays;`
- L8 _resource_ `RWStructuredBuffer<uint> Output;`

### `Shaders/Private/RayTracing/RayTracingValidation.usf` (Private)

- lines: 164; parse: all-branches
- includes: L3 `../Common.ush`, L11 `/Engine/Private/RayTracing/RayTracingHitGroupCommon.ush` [PLATFORM_SUPPORTS_DIAGNOSTIC_BUFFER]

#### Macros (#define, 1)

- L6 `#define NUM_THREADS_X 1024` _[#if !defined(NUM_THREADS_X)]_

#### Entry points (4)

- L65-95 _entry_ `[numthreads(NUM_THREADS_X, 1, 1)] void RayTracingValidateGeometryBuildParamsCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FRayTracingValidateGeometryBuildParamsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/RenderCore/Private/RayTracingValidationShaders.cpp:11) _[#if PLATFORM_SUPPORTS_DIAGNOSTIC_BUFFER]_
- L103-148 _entry_ `[numthreads(NUM_THREADS_X, 1, 1)] void RayTracingValidateSceneBuildParamsCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FRayTracingValidateSceneBuildParamsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/RenderCore/Private/RayTracingValidationShaders.cpp:85) _[#if PLATFORM_SUPPORTS_DIAGNOSTIC_BUFFER]_
- L152-155 _entry_ `[numthreads(NUM_THREADS_X, 1, 1)] void RayTracingValidateGeometryBuildParamsCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FRayTracingValidateGeometryBuildParamsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/RenderCore/Private/RayTracingValidationShaders.cpp:11) _[#if !(PLATFORM_SUPPORTS_DIAGNOSTIC_BUFFER)]_
- L157-160 _entry_ `[numthreads(NUM_THREADS_X, 1, 1)] void RayTracingValidateSceneBuildParamsCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FRayTracingValidateSceneBuildParamsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/RenderCore/Private/RayTracingValidationShaders.cpp:85) _[#if !(PLATFORM_SUPPORTS_DIAGNOSTIC_BUFFER)]_

#### Global resources (textures / buffers / samplers) (3)

- L13 _resource_ `ByteAddressBuffer IndexBuffer;` _[#if PLATFORM_SUPPORTS_DIAGNOSTIC_BUFFER]_
- L14 _resource_ `ByteAddressBuffer VertexBuffer;` _[#if PLATFORM_SUPPORTS_DIAGNOSTIC_BUFFER]_
- L99 _resource_ `ByteAddressBuffer InstanceBuffer;` _[#if PLATFORM_SUPPORTS_DIAGNOSTIC_BUFFER]_

#### Global parameters (uniforms) (10)

- L15 _parameter_ `uint VertexBufferStride;` _[#if PLATFORM_SUPPORTS_DIAGNOSTIC_BUFFER]_
- L16 _parameter_ `uint VertexBufferOffsetInBytes;` _[#if PLATFORM_SUPPORTS_DIAGNOSTIC_BUFFER]_
- L17 _parameter_ `uint IndexBufferOffsetInBytes;` _[#if PLATFORM_SUPPORTS_DIAGNOSTIC_BUFFER]_
- L18 _parameter_ `uint IndexBufferStride;` _[#if PLATFORM_SUPPORTS_DIAGNOSTIC_BUFFER]_
- L19 _parameter_ `uint NumPrimitives;` _[#if PLATFORM_SUPPORTS_DIAGNOSTIC_BUFFER]_
- L20 _parameter_ `uint MaxVertices;` _[#if PLATFORM_SUPPORTS_DIAGNOSTIC_BUFFER]_
- L97 _parameter_ `uint NumInstances;` _[#if PLATFORM_SUPPORTS_DIAGNOSTIC_BUFFER]_
- L98 _parameter_ `uint NumHitGroups;` _[#if PLATFORM_SUPPORTS_DIAGNOSTIC_BUFFER]_
- L100 _parameter_ `uint InstanceBufferOffsetInBytes;` _[#if PLATFORM_SUPPORTS_DIAGNOSTIC_BUFFER]_
- L101 _parameter_ `uint InstanceBufferStrideInBytes;` _[#if PLATFORM_SUPPORTS_DIAGNOSTIC_BUFFER]_

#### Functions (2)

- L22-29 _function_ `bool IsNaN(float F)` _[#if PLATFORM_SUPPORTS_DIAGNOSTIC_BUFFER]_
- L33-63 _function_ `void CheckTriangle(FTriangleBaseAttributes Tri, uint PrimitiveIndex)` — Returns true if all vertices are finite or if vertex X components are NaN. DXR inactive primitive rule applies: Triangles are considered "inactive" (but legal input to acceleration structure build) if the x component of each vertex is NaN. _[#if PLATFORM_SUPPORTS_DIAGNOSTIC_BUFFER]_

### `Shaders/Private/RayTracing/SkyLightMipTreeCommon.ush` (Private)

- lines: 273; parse: all-branches
- includes: L7 `MipTreeCommon.ush`

#### Functions (12)

- L9-43 _function_ `float3 GetTextureCubeVector(float3 TexelCoord, uint2 TextureRes)`
- L45-58 _function_ `uint GetMaximumComponentIndex(float3 Input)`
- L60-103 _function_ `uint3 GetTextureCubeCoordinate(float3 WorldDirection, uint2 TextureRes)`
- L109-113 _function_ `float AreaElement(float x, float y)` — Cube texel solid angle computation based on formula from Manne Öhrström's thesis - "Spherical Harmonics, Precomputed Radiance Transfer and Realtime Radiosity in Computer Games".
- L115-132 _function_ `float TexelCoordSolidAngle(uint2 TextureCoord, uint2 TextureRes)`
- L134-152 _function_ `void BuildFaceCdf(uint MipCount, out float FaceCdf[7])`
- L154-168 _function_ `uint SampleFace(float FaceCdf[7], float RandSample, out float FacePdf)`
- L170-175 _function_ `uint SampleFace(int MipCount, float RandSample, out float FacePdf)`
- L177-183 _function_ `float PdfFace(float FaceCdf[7], uint FaceIndex)`
- L185-190 _function_ `float PdfFace(int MipCount, uint FaceIndex)`
- L192-239 _function_ `float4 SampleMipTree(uint FaceIndex, uint4 BufferOffset)`
- L241-270 _function_ `float PdfMipTree(uint3 TextureCoord, uint StopLevel)`

### `Shaders/Private/RayTracing/SkyLightVisibilityRaysData.ush` (Private)

- lines: 33; parse: all-branches
- L3 #pragma `once`

#### Structs / classes (1)

- L5-8 _struct_ **`FSkyLightVisibilityRays`** `struct FSkyLightVisibilityRays`
  - L7 _member_ `float4 DirectionAndPdf;`

#### Functions (2)

- L10-19 _function_ `uint GetSkyLightVisibilityRayIndex( in uint2 PixelCoord, in uint SampleIndex, in uint2 SkyLightVisibilityRaysDimensions)`
- L21-32 _function_ `uint GetSkyLightVisibilityRayTiledIndex( in uint2 PixelCoord, in uint SampleIndex, in uint2 SkyLightVisibilityRaysDimensions)`

### `Shaders/Private/RayTracing/TraceRayInline.ush` (Private)

- lines: 232; parse: all-branches
- includes: L24 `/Platform/Private/TraceRayInline.ush` [PLATFORM_SUPPORTS_INLINE_RAY_TRACING && OVERRIDE_TRACERAYINLINE_USH], L28 `/Engine/Private/RayTracing/TraceRayInlineCommon.ush` [PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(OVERRIDE_TRACERAYINLINE_USH)], L31 `/Engine/Private/RayTracing/TraceRayInlineVulkan.ush` [PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(OVERRIDE_TRACERAYINLINE_USH) && (COMPILER_VULKAN \|\| PLATFORM_USE_TRACE_RAY_INLINE_VULKAN_USH)], L33 `/Engine/Private/RayTracing/TraceRayInlineMetal.ush` [PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(OVERRIDE_TRACERAYINLINE_USH) && !((COMPILER_VULKAN \|\| PLATFORM_USE_TRACE_RAY_INLINE_VULKAN_USH)) && COMPILER_METAL], L35 `/Engine/Private/RayTracing/TraceRayInlineD3D12.ush` [PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(OVERRIDE_TRACERAYINLINE_USH) && !((COMPILER_VULKAN \|\| PLATFORM_USE_TRACE_RAY_INLINE_VULKAN_USH)) && !(COMPILER_METAL) && SM6_PROFILE \|\| SM5_PROFILE], L39 `/Engine/Public/NvidiaExtensionsCommon.ush` [PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(OVERRIDE_TRACERAYINLINE_USH) && PLATFORM_SUPPORTS_RAYTRACING_CLUSTER_OPS]

#### Macros (#define, 10)

- L6 `#define PLATFORM_SUPPORTS_INLINE_RAY_TRACING 0` _[#if !defined(PLATFORM_SUPPORTS_INLINE_RAY_TRACING)]_
- L16 `#define ENABLE_TRACE_RAY_INLINE_PROCEDURAL_PRIMITIVE 0` _[#if PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !defined(ENABLE_TRACE_RAY_INLINE_PROCEDURAL_PRIMITIVE)]_
- L20 `#define ENABLE_TRACE_RAY_INLINE_TRAVERSAL_STATISTICS 0` _[#if PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !defined(ENABLE_TRACE_RAY_INLINE_TRAVERSAL_STATISTICS)]_
- L43 `#define PLATFORM_SUPPORTS_INLINE_RAY_TRACING_TRIANGLE_NORMALS 0` _[#if PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(OVERRIDE_TRACERAYINLINE_USH) && !defined(PLATFORM_SUPPORTS_INLINE_RAY_TRACING_TRIANGLE_NORMALS)]_
- L48 `#define GetInlineRayTracingWorldGeometryNormal(RayQ, Mat, Committed) RayQ.WorldRayDirection()` _[#if PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(OVERRIDE_TRACERAYINLINE_USH) && !PLATFORM_SUPPORTS_INLINE_RAY_TRACING_TRIANGLE_NORMALS]_
- L51 `#define PLATFORM_SUPPORTS_INLINE_RAY_TRACING_MAX_ITERATIONS 0` _[#if PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(OVERRIDE_TRACERAYINLINE_USH)]_
- L52 `#define PLATFORM_SUPPORTS_INLINE_RAY_TRACING_INSTANCE_MATRIX 1` _[#if PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(OVERRIDE_TRACERAYINLINE_USH)]_
- L215 `#define PLATFORM_SUPPORTS_INLINE_RAY_TRACING_MAX_ITERATIONS 0` _[#if PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !defined(PLATFORM_SUPPORTS_INLINE_RAY_TRACING_MAX_ITERATIONS)]_
- L219 `#define PLATFORM_SUPPORTS_INLINE_RAY_TRACING_TRIANGLE_ATTRIBUTES 0` _[#if PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !defined(PLATFORM_SUPPORTS_INLINE_RAY_TRACING_TRIANGLE_ATTRIBUTES)]_
- L223 `#define PLATFORM_SUPPORTS_INLINE_RAY_TRACING_INSTANCE_MATRIX 0` _[#if PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !defined(PLATFORM_SUPPORTS_INLINE_RAY_TRACING_INSTANCE_MATRIX)]_
- L3 #pragma `once`

#### Structs / classes (1)

- L228-228 _struct_ **`FRayTracingSceneMetadataRecord`** `struct FRayTracingSceneMetadataRecord` — Not used, but must be a valid structure declaration as it may appear in interfaces, resource declarations, etc. _[#if PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !defined(FRayTracingSceneMetadataRecord)]_
  - L228 _member_ `uint Dummy;` — Not used, but must be a valid structure declaration as it may appear in interfaces, resource declarations, etc. _[#if PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !defined(FRayTracingSceneMetadataRecord)]_

#### Functions (2)

- L54-199 _function_ `template<typename TTraceRayInlineCallback> FTraceRayInlineResult TraceRayInlineWithCallback(RaytracingAccelerationStructure AccelerationStructure, uint RayFlags, uint InstanceInclusionMask, RayDesc Ray, FTraceRayInlineContext TraceRayInlineContext, inout TTraceRayInlineCallback Callback)` _[#if PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(OVERRIDE_TRACERAYINLINE_USH)]_
- L201-210 _function_ `FTraceRayInlineResult TraceRayInline(RaytracingAccelerationStructure AccelerationStructure, uint RayFlags, uint InstanceInclusionMask, RayDesc InRay, FTraceRayInlineContext TraceRayInlineContext)` _[#if PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(OVERRIDE_TRACERAYINLINE_USH)]_

### `Shaders/Private/RayTracing/TraceRayInlineCommon.ush` (Private)

- lines: 130; parse: all-branches
- L3 #pragma `once`; L6 #pragma `message("UESHADERMETADATA_VERSION 06A6E5F1-49BF-4FF3-9D90-4B501E7E5FC4")`

#### Structs / classes (5)

- L8-23 _struct_ **`FTraceRayInlineTraversalStatistics`** `struct FTraceRayInlineTraversalStatistics`
  - L10 _member_ `uint NodeIntersectionCount;`
  - L11 _member_ `uint ClusterIntersectionCount;`
  - L12 _member_ `uint TriangleIntersectionCount;`
  - L13 _member_ `uint IterationCount;`
  - L15 _member_ `uint WaveNodeIntersectionCount;`
  - L16 _member_ `uint WaveTriangleIntersectionCount;`
  - L18 _member_ `uint RayCount;`
  - L19 _member_ `uint WavefrontCount;`
  - L21 _member_ `uint ActiveLaneCount;`
  - L22 _member_ `uint TotalLaneCount;`
- L47-82 _struct_ **`FTraceRayInlineResult`** `struct FTraceRayInlineResult`
  - L49 _member_ `float HitT;`
  - L50 _member_ `float2 Barycentrics;` — Only valid if bIsProcedural is false
  - L51 _member_ `uint InstanceIndex;`
  - L52 _member_ `uint InstanceID;`
  - L53 _member_ `uint InstanceContributionToHitGroupIndex;`
  - L54 _member_ `uint GeometryIndex;`
  - L55 _member_ `uint PrimitiveIndex;`
  - L57 _member_ `uint ClusterID;` _[#if PLATFORM_SUPPORTS_RAYTRACING_CLUSTER_OPS]_
  - L59 _member_ `bool bIsFrontFace;` — Only valid if bIsProcedural is false
  - L61 _member_ `uint2 Bookmark;`
  - L64 _member_ `float3x4 WorldToObject3x4;` — Only valid when PLATFORM_SUPPORTS_INLINE_RAY_TRACING_INSTANCE_MATRIX is 1
  - L67 _member_ `float3 WorldGeometryNormal;` — Only valid when PLATFORM_SUPPORTS_INLINE_RAY_TRACING_TRIANGLE_NORMALS is 1
  - L70 _member_ `bool bIsCompleted;` — Can be false only if PLATFORM_SUPPORTS_INLINE_RAY_TRACING_MAX_ITERATIONS is 1
  - L73 _member_ `bool bIsProcedural;` — Can only be true if ENABLE_TRACE_RAY_INLINE_PROCEDURAL_PRIMITIVE is 1
  - L76 _member_ `FTraceRayInlineTraversalStatistics TraversalStatistics;` — Only valid if shader was compiled with ENABLE_TRACE_RAY_INLINE_TRAVERSAL_STATISTICS
  - L78 _method_ `bool IsMiss()`
  - L79 _method_ `bool IsHit()`
  - L81 _method_ `void SetMiss()`
- L84-94 _struct_ **`FTraceRayInlineContext`** `struct FTraceRayInlineContext`
  - L87 _member_ `uint MaxIterations;` — Only used if PLATFORM_SUPPORTS_INLINE_RAY_TRACING_MAX_ITERATIONS is 1
  - L90 _member_ `bool bProcedural;` — Only used if shader was compiled with ENABLE_TRACE_RAY_INLINE_PROCEDURAL_PRIMITIVE
  - L93 _member_ `bool bOutputClusterID;` — Only used if shader was compiled with PLATFORM_SUPPORTS_RAYTRACING_CLUSTER_OPS
- L96-103 _struct_ **`FTraceRayInlineProceduralIntersectionParameters`** `struct FTraceRayInlineProceduralIntersectionParameters`
  - L98 _member_ `uint InstanceIndex;`
  - L99 _member_ `uint InstanceID;`
  - L100 _member_ `uint InstanceContributionToHitGroupIndex;`
  - L101 _member_ `uint GeometryIndex;`
  - L102 _member_ `uint PrimitiveIndex;`
- L107-120 _struct_ **`FDefaultTraceRayInlineCallback`** `struct FDefaultTraceRayInlineCallback` — Default callback structure for use with TraceRayInline. If custom functions are needed the new structure should derive from this structure.
  - L110 _method_ `bool OnAnyHit(float3 ObjectRayOrigin, float3 ObjectRayDirection, FTraceRayInlineResult Hit)` — Returning true means to accept the hit and false means to continue search (default accept)
  - L116 _method_ `bool OnProceduralPrimitive(float3 ObjectRayOrigin, float3 ObjectRayDirection, float RayTMin, inout float RayTCurrent, FTraceRayInlineProceduralIntersectionParameters ProceduralIntersectionParameters)` — Returning true means accept the procedural hit and false means to skip it (default skip)

#### Global resources (textures / buffers / samplers) (1)

- L26 _resource_ `RWStructuredBuffer<FTraceRayInlineTraversalStatistics> TraceRayInlineTraversalStatistics_Accumulator;`

#### static variables (1)

- L25 _static_var_ `static FTraceRayInlineTraversalStatistics TraceRayInlineTraversalStatistics_Sample;`

#### Functions (2)

- L28-45 _function_ `void TraceRayInlineAccumulateStatistics()`
- L122-129 _function_ `FTraceRayInlineContext CreateTraceRayInlineContext()`

### `Shaders/Private/RayTracing/TraceRayInlineD3D12.ush` (Private)

- lines: 71; parse: all-branches
- includes: L10 `/Engine/Shared/RayTracingDefinitions.h`, L11 `/Engine/Shared/RayTracingBuiltInResources.h`, L12 `/Engine/Private/RayTracing/RayTracingCommon.ush`, L13 `/Engine/Private/RayTracing/RayTracingHitGroupCommon.ush`

#### Macros (#define, 2)

- L17 `#define PLATFORM_SUPPORTS_INLINE_RAY_TRACING_TRIANGLE_ATTRIBUTES 1` _[#if COMPILER_DXC && PLATFORM_SUPPORTS_INLINE_RAY_TRACING && UE_BINDLESS_ENABLED]_
- L32 `#define FRayTracingSceneMetadataRecord FD3DHitGroupSystemParametersWithPadding` _[#if COMPILER_DXC && PLATFORM_SUPPORTS_INLINE_RAY_TRACING && UE_BINDLESS_ENABLED]_
- L8 #pragma `once`

#### Structs / classes (1)

- L19-29 _struct_ **`FD3DHitGroupSystemParametersWithPadding`** `struct FD3DHitGroupSystemParametersWithPadding` _[#if COMPILER_DXC && PLATFORM_SUPPORTS_INLINE_RAY_TRACING && UE_BINDLESS_ENABLED]_
  - L21 _member_ `FHitGroupSystemRootConstants RootConstants;` _[#if COMPILER_DXC && PLATFORM_SUPPORTS_INLINE_RAY_TRACING && UE_BINDLESS_ENABLED]_
  - L23 _member_ `uint BindlessHitGroupSystemIndexBuffer;` _[#if COMPILER_DXC && PLATFORM_SUPPORTS_INLINE_RAY_TRACING && UE_BINDLESS_ENABLED]_
  - L24 _member_ `uint BindlessHitGroupSystemVertexBuffer;` _[#if COMPILER_DXC && PLATFORM_SUPPORTS_INLINE_RAY_TRACING && UE_BINDLESS_ENABLED]_
  - L27 _member_ `uint Padding0;` — Add padding because c++ side has union for GPU address of index/vertex buffer data for non bindless code path which are uint64 each _[#if COMPILER_DXC && PLATFORM_SUPPORTS_INLINE_RAY_TRACING && UE_BINDLESS_ENABLED]_
  - L28 _member_ `uint Padding1;` _[#if COMPILER_DXC && PLATFORM_SUPPORTS_INLINE_RAY_TRACING && UE_BINDLESS_ENABLED]_

#### Functions (2)

- L34-44 _function_ `uint GetInlineRayTracingHitGroupFirstPrimitive( StructuredBuffer<FRayTracingSceneMetadataRecord> RayTracingSceneMetadata, uint InstanceContributionToHitGroupIndex, uint MultiplierForGeometryContributionToHitGroupIndex, uint GeometryIndex)` _[#if COMPILER_DXC && PLATFORM_SUPPORTS_INLINE_RAY_TRACING && UE_BINDLESS_ENABLED]_
- L46-68 _function_ `FTriangleBaseAttributes LoadInlineRayTracingTriangleAttributes( StructuredBuffer<FRayTracingSceneMetadataRecord> RayTracingSceneMetadata, uint InstanceContributionToHitGroupIndex, uint MultiplierForGeometryContributionToHitGroupIndex, uint GeometryIndex, uint PrimitiveIndex)` _[#if COMPILER_DXC && PLATFORM_SUPPORTS_INLINE_RAY_TRACING && UE_BINDLESS_ENABLED]_

### `Shaders/Private/RayTracing/TraceRayInlineMetal.ush` (Private)

- lines: 58; parse: all-branches
- includes: L10 `/Engine/Shared/RayTracingDefinitions.h`, L11 `/Engine/Shared/RayTracingBuiltInResources.h`, L12 `/Engine/Private/RayTracing/RayTracingCommon.ush`, L13 `/Engine/Private/RayTracing/RayTracingHitGroupCommon.ush`

#### Macros (#define, 2)

- L17 `#define PLATFORM_SUPPORTS_INLINE_RAY_TRACING_TRIANGLE_ATTRIBUTES 1` _[#if COMPILER_DXC && PLATFORM_SUPPORTS_INLINE_RAY_TRACING && UE_BINDLESS_ENABLED]_
- L19 `#define FRayTracingSceneMetadataRecord FMetalHitGroupSystemParameters` _[#if COMPILER_DXC && PLATFORM_SUPPORTS_INLINE_RAY_TRACING && UE_BINDLESS_ENABLED]_
- L8 #pragma `once`

#### Functions (2)

- L21-31 _function_ `uint GetInlineRayTracingHitGroupFirstPrimitive( StructuredBuffer<FRayTracingSceneMetadataRecord> RayTracingSceneMetadata, uint InstanceContributionToHitGroupIndex, uint MultiplierForGeometryContributionToHitGroupIndex, uint GeometryIndex)` _[#if COMPILER_DXC && PLATFORM_SUPPORTS_INLINE_RAY_TRACING && UE_BINDLESS_ENABLED]_
- L33-55 _function_ `FTriangleBaseAttributes LoadInlineRayTracingTriangleAttributes( StructuredBuffer<FRayTracingSceneMetadataRecord> RayTracingSceneMetadata, uint InstanceContributionToHitGroupIndex, uint MultiplierForGeometryContributionToHitGroupIndex, uint GeometryIndex, uint PrimitiveIndex)` _[#if COMPILER_DXC && PLATFORM_SUPPORTS_INLINE_RAY_TRACING && UE_BINDLESS_ENABLED]_

### `Shaders/Private/RayTracing/TraceRayInlineStatistics.usf` (Private)

- lines: 63; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../ShaderPrint.ush`, L5 `TraceRayInlineCommon.ush`

#### Entry points (1)

- L9-62 _entry_ `[numthreads(1, 1, 1)] void TraceRayInlinePrintStatisticsCS()` — stage: **compute** — C++: `FTraceRayInlinePrintStatisticsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/RayTracing/RayTracingTraversalStatistics.cpp:42)

#### Global resources (textures / buffers / samplers) (1)

- L7 _resource_ `StructuredBuffer<FTraceRayInlineTraversalStatistics> TraversalStatistics;`

### `Shaders/Private/RayTracing/TraceRayInlineVulkan.ush` (Private)

- lines: 190; parse: all-branches
- includes: L10 `/Engine/Shared/RayTracingDefinitions.h`, L11 `/Engine/Private/RayTracing/RayTracingCommon.ush`

#### Macros (#define, 8)

- L16 `#define VULKAN_SUPPORTS_RAY_TRACING_POSITION_FETCH 0` _[#if COMPILER_DXC && (COMPILER_VULKAN \|\| PLATFORM_USE_TRACE_RAY_INLINE_VULKAN_USH) && PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !defined(VULKAN_SUPPORTS_RAY_TRACING_POSITION_FETCH)]_
- L20 `#define PLATFORM_SUPPORTS_INLINE_RAY_TRACING_TRIANGLE_ATTRIBUTES !VULKAN_SUPPORTS_RAY_TRACING_POSITION_FETCH` _[#if COMPILER_DXC && (COMPILER_VULKAN \|\| PLATFORM_USE_TRACE_RAY_INLINE_VULKAN_USH) && PLATFORM_SUPPORTS_INLINE_RAY_TRACING]_
- L31 `#define VK_ADDR_TYPE uint2` _[#if COMPILER_DXC && (COMPILER_VULKAN \|\| PLATFORM_USE_TRACE_RAY_INLINE_VULKAN_USH) && PLATFORM_SUPPORTS_INLINE_RAY_TRACING && EMULATE_VKDEVICEADRESS]_
- L32 `#define VK_RAW_BUFFER_LOAD(Type, Addr, Offs) vk::RawBufferLoad2<Type>(AddEmulated64(Addr,Offs))` _[#if COMPILER_DXC && (COMPILER_VULKAN \|\| PLATFORM_USE_TRACE_RAY_INLINE_VULKAN_USH) && PLATFORM_SUPPORTS_INLINE_RAY_TRACING && EMULATE_VKDEVICEADRESS]_
- L34 `#define VK_ADDR_TYPE uint64_t` _[#if COMPILER_DXC && (COMPILER_VULKAN \|\| PLATFORM_USE_TRACE_RAY_INLINE_VULKAN_USH) && PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(EMULATE_VKDEVICEADRESS)]_
- L35 `#define VK_RAW_BUFFER_LOAD(Type, Addr, Offs) vk::RawBufferLoad<Type>(Addr + Offs)` _[#if COMPILER_DXC && (COMPILER_VULKAN \|\| PLATFORM_USE_TRACE_RAY_INLINE_VULKAN_USH) && PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(EMULATE_VKDEVICEADRESS)]_
- L78 `#define PLATFORM_SUPPORTS_INLINE_RAY_TRACING_TRIANGLE_NORMALS 1` _[#if COMPILER_DXC && (COMPILER_VULKAN \|\| PLATFORM_USE_TRACE_RAY_INLINE_VULKAN_USH) && PLATFORM_SUPPORTS_INLINE_RAY_TRACING && VULKAN_SUPPORTS_RAY_TRACING_POSITION_FETCH]_
- L130 `#define FRayTracingSceneMetadataRecord FVulkanRayTracingGeometryParameters` _[#if COMPILER_DXC && (COMPILER_VULKAN \|\| PLATFORM_USE_TRACE_RAY_INLINE_VULKAN_USH) && PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(VULKAN_SUPPORTS_RAY_TRACING_POSITION_FETCH)]_
- L8 #pragma `once`

#### Structs / classes (1)

- L121-127 _struct_ **`FVulkanRayTracingGeometryParameters`** `struct FVulkanRayTracingGeometryParameters` — Counterpart of FVulkanRayTracingGeometryParameters in VulkanRayTracing.cpp _[#if COMPILER_DXC && (COMPILER_VULKAN \|\| PLATFORM_USE_TRACE_RAY_INLINE_VULKAN_USH) && PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(VULKAN_SUPPORTS_RAY_TRACING_POSITION_FETCH)]_
  - L123 _member_ `uint Config;` _[#if COMPILER_DXC && (COMPILER_VULKAN \|\| PLATFORM_USE_TRACE_RAY_INLINE_VULKAN_USH) && PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(VULKAN_SUPPORTS_RAY_TRACING_POSITION_FETCH)]_
  - L124 _member_ `uint IndexBufferOffsetInBytes;` _[#if COMPILER_DXC && (COMPILER_VULKAN \|\| PLATFORM_USE_TRACE_RAY_INLINE_VULKAN_USH) && PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(VULKAN_SUPPORTS_RAY_TRACING_POSITION_FETCH)]_
  - L125 _member_ `VK_ADDR_TYPE IndexBuffer;` _[#if COMPILER_DXC && (COMPILER_VULKAN \|\| PLATFORM_USE_TRACE_RAY_INLINE_VULKAN_USH) && PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(VULKAN_SUPPORTS_RAY_TRACING_POSITION_FETCH)]_
  - L126 _member_ `VK_ADDR_TYPE VertexBuffer;` _[#if COMPILER_DXC && (COMPILER_VULKAN \|\| PLATFORM_USE_TRACE_RAY_INLINE_VULKAN_USH) && PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(VULKAN_SUPPORTS_RAY_TRACING_POSITION_FETCH)]_

#### Global parameters (uniforms) (1)

- L80-89 _parameter_ `[[vk::ext_capability(5391 )]] [[vk::ext_extension("SPV_KHR_ray_tracing_position_fetch")]] [[vk::ext_instruction(5340 )]] float3 RayQueryGetIntersectionTriangleVertexPositionsKHR( [[vk::ext_reference]] RayQuery<RAY_FLAG_NONE> RayQ, [[vk::ext_reference]] RayQuery<RAY_FLAG_SKIP_PROCEDURAL_PRIMITIVES> RayQ, int committed)[3];` _[#if COMPILER_DXC && (COMPILER_VULKAN \|\| PLATFORM_USE_TRACE_RAY_INLINE_VULKAN_USH) && PLATFORM_SUPPORTS_INLINE_RAY_TRACING && VULKAN_SUPPORTS_RAY_TRACING_POSITION_FETCH]_

#### Functions (7)

- L23-29 _function_ `inline uint2 AddEmulated64(uint2 a, uint b)` _[#if COMPILER_DXC && (COMPILER_VULKAN \|\| PLATFORM_USE_TRACE_RAY_INLINE_VULKAN_USH) && PLATFORM_SUPPORTS_INLINE_RAY_TRACING && EMULATE_VKDEVICEADRESS]_
- L38-63 _function_ `uint3 VulkanLoadIndices16Bit(VK_ADDR_TYPE SourceBufferBaseAddress, uint OffsetInBytes)` _[#if COMPILER_DXC && (COMPILER_VULKAN \|\| PLATFORM_USE_TRACE_RAY_INLINE_VULKAN_USH) && PLATFORM_SUPPORTS_INLINE_RAY_TRACING]_
- L65-68 _function_ `uint3 VulkanLoadIndices32Bit(VK_ADDR_TYPE SourceBufferBaseAddress, uint OffsetInBytes)` _[#if COMPILER_DXC && (COMPILER_VULKAN \|\| PLATFORM_USE_TRACE_RAY_INLINE_VULKAN_USH) && PLATFORM_SUPPORTS_INLINE_RAY_TRACING]_
- L70-74 _function_ `float3 VulkanLoadVertexPositionFloat3(VK_ADDR_TYPE SourceBufferBaseAddress, uint Index, uint StrideInBytes)` _[#if COMPILER_DXC && (COMPILER_VULKAN \|\| PLATFORM_USE_TRACE_RAY_INLINE_VULKAN_USH) && PLATFORM_SUPPORTS_INLINE_RAY_TRACING]_
- L91-116 _function_ `float3 GetInlineRayTracingWorldGeometryNormal( RayQuery<RAY_FLAG_NONE> RayQ, RayQuery<RAY_FLAG_SKIP_PROCEDURAL_PRIMITIVES> RayQ, float3x4 WorldToObject3x4, bool Committed)` _[#if COMPILER_DXC && (COMPILER_VULKAN \|\| PLATFORM_USE_TRACE_RAY_INLINE_VULKAN_USH) && PLATFORM_SUPPORTS_INLINE_RAY_TRACING && VULKAN_SUPPORTS_RAY_TRACING_POSITION_FETCH]_
- L132-142 _function_ `uint GetInlineRayTracingHitGroupFirstPrimitive( StructuredBuffer<FRayTracingSceneMetadataRecord> RayTracingSceneMetadata, uint InstanceContributionToHitGroupIndex, uint MultiplierForGeometryContributionToHitGroupIndex, uint GeometryIndex)` _[#if COMPILER_DXC && (COMPILER_VULKAN \|\| PLATFORM_USE_TRACE_RAY_INLINE_VULKAN_USH) && PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(VULKAN_SUPPORTS_RAY_TRACING_POSITION_FETCH)]_
- L144-185 _function_ `FTriangleBaseAttributes LoadInlineRayTracingTriangleAttributes( StructuredBuffer<FRayTracingSceneMetadataRecord> RayTracingSceneMetadata, uint InstanceContributionToHitGroupIndex, uint MultiplierForGeometryContributionToHitGroupIndex, uint GeometryIndex, uint PrimitiveIndex)` _[#if COMPILER_DXC && (COMPILER_VULKAN \|\| PLATFORM_USE_TRACE_RAY_INLINE_VULKAN_USH) && PLATFORM_SUPPORTS_INLINE_RAY_TRACING && !(VULKAN_SUPPORTS_RAY_TRACING_POSITION_FETCH)]_

### `Shaders/Private/RayTracing/VFXTraceRay.ush` (Private)

- lines: 122; parse: all-branches
- includes: L12 `RayTracingCommon.ush` [!defined(VFX_TRACE_RAY_USH_INCLUDED)], L13 `RayTracingHitGroupCommon.ush` [!defined(VFX_TRACE_RAY_USH_INCLUDED)], L16 `TraceRayInline.ush` [!defined(VFX_TRACE_RAY_USH_INCLUDED) && COMPUTESHADER], L35 `/Platform/Private/VFXTraceRay.ush` [!defined(VFX_TRACE_RAY_USH_INCLUDED) && defined(OVERRIDE_VFXTRACERAY_USH)]

#### Macros (#define, 1)

- L10 `#define VFX_TRACE_RAY_USH_INCLUDED ` _[#if !defined(VFX_TRACE_RAY_USH_INCLUDED)]_
- L7 #pragma `once`

#### Structs / classes (1)

- L18-30 _struct_ **`FVFXTracePayload`** `struct FVFXTracePayload` _[#if !defined(VFX_TRACE_RAY_USH_INCLUDED) && COMPUTESHADER]_
  - L20 _member_ `float HitT;` _[#if !defined(VFX_TRACE_RAY_USH_INCLUDED) && COMPUTESHADER]_
  - L21 _member_ `uint GPUSceneInstanceId;` _[#if !defined(VFX_TRACE_RAY_USH_INCLUDED) && COMPUTESHADER]_
  - L22 _member_ `float2 Barycentrics;` _[#if !defined(VFX_TRACE_RAY_USH_INCLUDED) && COMPUTESHADER]_
  - L23 _member_ `float3 TranslatedWorldPosition;` _[#if !defined(VFX_TRACE_RAY_USH_INCLUDED) && COMPUTESHADER]_
  - L24 _member_ `float3 WorldNormal;` _[#if !defined(VFX_TRACE_RAY_USH_INCLUDED) && COMPUTESHADER]_
  - L26 _method_ `bool IsMiss()` _[#if !defined(VFX_TRACE_RAY_USH_INCLUDED) && COMPUTESHADER]_
  - L27 _method_ `bool IsHit()` _[#if !defined(VFX_TRACE_RAY_USH_INCLUDED) && COMPUTESHADER]_
  - L29 _method_ `void SetMiss()` _[#if !defined(VFX_TRACE_RAY_USH_INCLUDED) && COMPUTESHADER]_

#### Global resources (textures / buffers / samplers) (1)

- L78 _resource_ `StructuredBuffer<FRayTracingSceneMetadataRecord> RayTracingSceneMetadata;` _[#if !defined(VFX_TRACE_RAY_USH_INCLUDED) && COMPUTESHADER]_

#### Functions (3)

- L38-59 _function_ `void InitVFXTracePayloadFromHitShader(FRayTracingIntersectionAttributes Attributes, out FVFXTracePayload OutPayload)` _[#if !defined(VFX_TRACE_RAY_USH_INCLUDED) && !(defined(OVERRIDE_VFXTRACERAY_USH))]_
- L61-72 _function_ `void VfxTraceRay( RaytracingAccelerationStructure AccelerationStructure, uint RayFlags, uint InstanceInclusionMask, uint RayContributionToHitGroupIndex, uint MultiplierForGeometryContributionToHitGroupIndex, uint MissShaderIndex, RayDesc InRay, inout FVFXTracePayload Payload)` _[#if !defined(VFX_TRACE_RAY_USH_INCLUDED) && !(defined(OVERRIDE_VFXTRACERAY_USH))]_
- L80-117 _function_ `void VfxTraceRayInline( RaytracingAccelerationStructure AccelerationStructure, uint RayFlags, uint InstanceInclusionMask, RayDesc InRay, inout FVFXTracePayload Payload)` _[#if !defined(VFX_TRACE_RAY_USH_INCLUDED) && COMPUTESHADER]_
