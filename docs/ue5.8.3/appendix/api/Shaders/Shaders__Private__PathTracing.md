# Shaders / Shaders/Private/PathTracing

- files: 26; lines: 10757
- record kinds: cpp_binding=61, define=188, entry=42, function=119, include=135, macro_call=3, member=79, method=204, parameter=92, resource=107, static_const=9, static_var=3, struct=11

### `Shaders/Private/PathTracing/PathTracing.usf` (Private)

- lines: 173; parse: all-branches
- includes: L16 `PathTracingCore.ush`

#### Macros (#define, 3)

- L7 `#define PATH_TRACING 1`
- L9 `#define PATH_TRACING_SHADER_VERSION 0x51478b68`
- L13 `#define SUBSTRATE_COMPLEXSPECIALPATH 1` _[#if SUBSTRATE_ENABLED && PATH_TRACER_USE_SUBSTRATE_SPECIAL_COMPLEX_MATERIAL]_

#### Entry points (1)

- L90-172 _entry_ `RAY_TRACING_ENTRY_RAYGEN(PathTracingMainRG)` — stage: **raygeneration** — C++: `FPathTracingRG` SF_RayGen via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PathTracing.cpp:1544)

#### Global resources (textures / buffers / samplers) (4)

- L43 _resource_ `RWStructuredBuffer<FPathTracingPackedPathState> PathStateData;`
- L44 _resource_ `RWBuffer<uint> ActivePaths;`
- L45 _resource_ `RWBuffer<uint> NumPathStates;`
- L48 _resource_ `RWBuffer<uint> NextActivePaths;` _[#if PATH_TRACER_KERNEL_TYPE != PATH_TRACER_KERNEL_TAIL]_

#### Global parameters (uniforms) (5)

- L19 _parameter_ `int2 TilePixelOffset;` — describe how we split up the image between tiles and amongst GPUs
- L20 _parameter_ `int2 TileTextureOffset;`
- L21 _parameter_ `int ScanlineStride;`
- L22 _parameter_ `int ScanlineWidth;`
- L40 _parameter_ `int FirstBounce;` _[#if PATH_TRACER_KERNEL_TYPE != PATH_TRACER_KERNEL_CAMERA]_

#### Functions (4)

- L27-30 _function_ `int2 ComputePixelIndex(uint2 DispatchIdx)` — Which pixel on screen are we computing? We want to spread out the scanlines evenly across the screen so that each GPU works on a similarly sized task
- L34-37 _function_ `int2 ComputeTextureIndex(uint2 DispatchIdx)` — Where should we store the accumulated pixels of this dispatch? We want all the scanlines computed by a given GPU to be contiguous in memory so we can copy them easily
- L52-69 _function_ `FPathState LoadPathStateData(uint Index)` _[#if PATH_TRACER_KERNEL_TYPE != PATH_TRACER_KERNEL_CAMERA]_
- L73-87 _function_ `void StorePathStateData(FPathState PathState, uint Index)` _[#if PATH_TRACER_KERNEL_TYPE != PATH_TRACER_KERNEL_TAIL]_

### `Shaders/Private/PathTracing/PathTracingAdaptiveStart.usf` (Private)

- lines: 39; parse: all-branches
- includes: L3 `../Common.ush`, L4 `PathTracingAdaptiveUtils.ush`

#### Entry points (1)

- L13-38 _entry_ `[numthreads(THREADGROUPSIZE_X, THREADGROUPSIZE_Y, 1)] void PathTracingAdaptiveStartCS(uint2 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FPathTracingAdaptiveStartCS` SF_Compute via IMPLEMENT_SHADER_TYPE (Source/Runtime/Renderer/Private/PathTracing.cpp:2575)

#### Global resources (textures / buffers / samplers) (2)

- L7 _resource_ `RWBuffer<uint> NextActivePaths;`
- L8 _resource_ `RWBuffer<uint> NumPathStates;`

#### Global parameters (uniforms) (2)

- L9 _parameter_ `int2 TileTextureOffset;`
- L10 _parameter_ `uint2 DispatchDim;`

### `Shaders/Private/PathTracing/PathTracingAdaptiveUtils.ush` (Private)

- lines: 93; parse: all-branches
- L3 #pragma `once`

#### Global resources (textures / buffers / samplers) (2)

- L5 _resource_ `Texture2D<float4> VarianceTexture;`
- L6 _resource_ `SamplerState VarianceSampler;`

#### Global parameters (uniforms) (2)

- L7 _parameter_ `uint3 VarianceTextureDims;`
- L8 _parameter_ `float AdaptiveSamplingErrorThreshold;`

#### Functions (3)

- L13-32 _function_ `float PerceptualError(float Mean, float StdErr)` — Variance of the tonemapped color can be predicted from the variance of the scene linear color: https://en.wikipedia.org/wiki/Taylor_expansions_for_the_moments_of_functions_of_random_variables
- L34-66 _function_ `float4 SampleVarianceTexture(float2 VarianceUV, int Mip)`
- L68-92 _function_ `float GetAdaptiveSampleFactor(uint2 TexCoord)`

### `Shaders/Private/PathTracing/PathTracingBuildAdaptiveError.usf` (Private)

- lines: 139; parse: all-branches
- includes: L3 `../Common.ush`

#### Entry points (1)

- L19-139 _entry_ `[numthreads(THREADGROUPSIZE_X, THREADGROUPSIZE_Y, 1)] void PathTracingBuildAdaptiveErrorTextureCS(uint2 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FPathTracingBuildAdaptiveErrorTextureCS` SF_Compute via IMPLEMENT_SHADER_TYPE (Source/Runtime/Renderer/Private/PathTracing.cpp:2545)

#### Global resources (textures / buffers / samplers) (3)

- L7 _resource_ `SamplerState InputMipSampler;`
- L8 _resource_ `Texture2D<float4> InputMip;`
- L9 _resource_ `RWTexture2D<float4> OutputMip;`

#### Global parameters (uniforms) (2)

- L5 _parameter_ `int2 InputResolution;`
- L6 _parameter_ `int2 OutputResolution;`

#### Functions (1)

- L11-17 _function_ `float4 CombinePixels(float4 A, float4 B, float W)`

### `Shaders/Private/PathTracing/PathTracingBuildAtmosphereLUT.usf` (Private)

- lines: 87; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../SkyAtmosphereCommon.ush`, L5 `./Volume/PathTracingAtmosphereCommon.ush`

#### Entry points (1)

- L11-86 _entry_ `[numthreads(THREADGROUPSIZE_X, THREADGROUPSIZE_Y, 1)] void PathTracingBuildAtmosphereOpticalDepthLUTCS(uint2 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FPathTracingBuildAtmosphereOpticalDepthLUTCS` SF_Compute via IMPLEMENT_SHADER_TYPE (Source/Runtime/Renderer/Private/PathTracing.cpp:1772)

#### Global resources (textures / buffers / samplers) (1)

- L9 _resource_ `RWTexture2D<float3> AtmosphereOpticalDepthLUT;`

#### Global parameters (uniforms) (2)

- L7 _parameter_ `uint NumSamples;`
- L8 _parameter_ `uint Resolution;`

### `Shaders/Private/PathTracing/PathTracingBuildCloudAccelerationMap.usf` (Private)

- lines: 85; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../MonteCarlo.ush`, L5 `../SkyAtmosphereCommon.ush`, L6 `./Volume/PathTracingAtmosphereCommon.ush`, L7 `./Volume/PathTracingCloudsCommon.ush`, L8 `./Volume/PathTracingCloudsMaterialCommon.ush`, L9 `./Utilities/PathTracingRandomSequence.ush`

#### Entry points (1)

- L17-84 _entry_ `[numthreads(THREADGROUPSIZE_X, THREADGROUPSIZE_Y, 1)] void PathTracingBuildCloudAccelerationMapCS(uint2 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FPathTracingBuildCloudAccelerationMapCS` SF_Compute via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/PathTracing.cpp:1871)

#### Global resources (textures / buffers / samplers) (1)

- L15 _resource_ `RWTexture2D<float4> CloudAccelerationMap;`

#### Global parameters (uniforms) (3)

- L11 _parameter_ `uint NumSamples;`
- L12 _parameter_ `uint TemporalSeed;`
- L13 _parameter_ `uint Iteration;`

### `Shaders/Private/PathTracing/PathTracingBuildLightGrid.usf` (Private)

- lines: 123; parse: all-branches
- includes: L3 `../Common.ush`, L4 `/Engine/Shared/RayTracingDefinitions.h`, L5 `/Engine/Shared/RayTracingTypes.h`, L6 `/Engine/Shared/PathTracingDefinitions.h`, L7 `../IntersectionUtils.ush`, L11 `Light/PathTracingLightCommon.ush`

#### Macros (#define, 4)

- L9 `#define USE_ATTENUATION_TERM 0`
- L10 `#define USE_IES_TERM 0`
- L22 `#define RECT_TEST 2`
- L26 `#define CONE_TEST 1`

#### Entry points (1)

- L29-122 _entry_ `[numthreads(THREADGROUPSIZE_X, THREADGROUPSIZE_Y, 1)] void PathTracingBuildLightGridCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FPathTracingBuildLightGridCS` SF_Compute via IMPLEMENT_SHADER_TYPE (Source/Runtime/Renderer/Private/PathTracing.cpp:1265)

#### Global resources (textures / buffers / samplers) (2)

- L16 _resource_ `RWTexture2DArray<uint> RWLightGrid;`
- L17 _resource_ `RWBuffer<uint> RWLightGridData;`

#### Global parameters (uniforms) (6)

- L13 _parameter_ `uint SceneInfiniteLightCount;`
- L14 _parameter_ `float3 SceneLightsTranslatedBoundMin;`
- L15 _parameter_ `float3 SceneLightsTranslatedBoundMax;`
- L18 _parameter_ `uint LightGridResolution;`
- L19 _parameter_ `uint LightGridMaxCount;`
- L20 _parameter_ `uint LightGridAxis;`

### `Shaders/Private/PathTracing/PathTracingCommon.ush` (Private)

- lines: 1037; parse: all-branches
- includes: L9 `Material/PathTracingMaterialCommon.ush`, L10 `Utilities/PathTracingRandomSequence.ush`, L11 `Utilities/PathTracingRIS.ush`, L12 `../RayTracing/RayTracingCommon.ush`, L13 `../OctahedralCommon.ush`, L14 `../DoubleFloat.ush`, L15 `/Engine/Shared/PathTracingDefinitions.h`

#### Macros (#define, 40)

- L18 `#define PATH_TRACING_PAYLOAD_OUTPUT_FLAG_FRONT_FACE (1 << 0)`
- L19 `#define PATH_TRACING_PAYLOAD_OUTPUT_FLAG_TWO_SIDED_MATERIAL (1 << 1)`
- L20 `#define PATH_TRACING_PAYLOAD_OUTPUT_FLAG_IS_HOLDOUT (1 << 2)`
- L21 `#define PATH_TRACING_PAYLOAD_OUTPUT_FLAG_DECAL_RESPONSE_MASK_SHIFT (3)`
- L22 `#define PATH_TRACING_PAYLOAD_OUTPUT_FLAG_DECAL_RESPONSE_COLOR (1 << 3)`
- L23 `#define PATH_TRACING_PAYLOAD_OUTPUT_FLAG_DECAL_RESPONSE_NORMAL (1 << 4)`
- L24 `#define PATH_TRACING_PAYLOAD_OUTPUT_FLAG_DECAL_RESPONSE_ROUGHNESS (1 << 5)`
- L25 `#define PATH_TRACING_PAYLOAD_OUTPUT_FLAG_USE_DBUFFER_LOOKUP (1 << 6)`
- L26 `#define PATH_TRACING_PAYLOAD_OUTPUT_FLAG_OUTOUT_DEPTH (1 << 7)`
- L27 `#define PATH_TRACING_PAYLOAD_OUTPUT_FLAG_UNUSED8 (1 << 8)`
- L29 `#define PATH_TRACING_PAYLOAD_INPUT_FLAG_RAY_TYPE_MASK (7 << 0)`
- L30 `#define PATH_TRACING_PAYLOAD_INPUT_FLAG_RAY_TYPE_CAMERA 0`
- L31 `#define PATH_TRACING_PAYLOAD_INPUT_FLAG_RAY_TYPE_SHADOW 1`
- L32 `#define PATH_TRACING_PAYLOAD_INPUT_FLAG_RAY_TYPE_INDIRECT_DIFFUSE 2`
- L33 `#define PATH_TRACING_PAYLOAD_INPUT_FLAG_RAY_TYPE_INDIRECT_SPECULAR 3`
- L34 `#define PATH_TRACING_PAYLOAD_INPUT_FLAG_RAY_TYPE_INDIRECT_VOLUME 4`
- L35 `#define PATH_TRACING_PAYLOAD_INPUT_FLAG_HAS_SCENE_DEPTH (1 << 4)`
- L36 `#define PATH_TRACING_PAYLOAD_INPUT_FLAG_IGNORE_TRANSLUCENT (1 << 5)`
- L37 `#define PATH_TRACING_PAYLOAD_INPUT_FLAG_DEBUG_INFO_MASK (3 << 6)`
- L38 `#define PATH_TRACING_PAYLOAD_INPUT_FLAG_DEBUG_TRIANGLE_ID (1 << 6)`
- L39 `#define PATH_TRACING_PAYLOAD_INPUT_FLAG_DEBUG_INSTANCE_ID (2 << 6)`
- L40 `#define PATH_TRACING_PAYLOAD_INPUT_FLAG_DEBUG_CLUSTER_ID (3 << 6)`
- L41 `#define PATH_TRACING_PAYLOAD_INPUT_FLAG_UNUSED8 (1 << 8)`
- L43 `#define PATH_TRACING_PAYLOAD_NORMAL_BITS 32`
- L44 `#define PATH_TRACING_PAYLOAD_TANGENT_ANGLE_BITS 16`
- L48 `#define PATH_TRACING_SHADINGMODELID_BASIC 0`
- L49 `#define PATH_TRACING_SHADINGMODELID_FOLIAGE 1`
- L50 `#define PATH_TRACING_SHADINGMODELID_CLEARCOAT 2`
- L51 `#define PATH_TRACING_SHADINGMODELID_SOLID_GLASS 3`
- L52 `#define PATH_TRACING_SHADINGMODELID_THIN_GLASS 4`
- L53 `#define PATH_TRACING_SHADINGMODELID_EYE 5`
- L54 `#define PATH_TRACING_SHADINGMODELID_HAIR 6`
- L55 `#define PATH_TRACING_SHADINGMODELID_MEDIUM 7`
- L56 `#define PATH_TRACING_SHADINGMODELID_VOLUMETRIC 8`
- L57 `#define PATH_TRACING_SHADINGMODELID_LAMBERT 9`
- L58 `#define PATH_TRACING_SHADINGMODELID_MASK 0xf`
- L61 `#define PATH_TRACING_ABSORPTION_SCALE 0.01`
- L65 `#define PATH_TRACING_SKIP_HAIR_DISTANCE 1e6`
- L72 `#define SUBSTRATE_PATH_TRACING_SPECULAR_PROFILE (SUBSTRATE_ENABLED && PLATFORM_ENABLES_SUBSTRATE_SPECULAR_PROFILE)`
- L73 `#define SUBSTRATE_PATH_TRACING_GLINTS (SUBSTRATE_ENABLED && PLATFORM_ENABLES_SUBSTRATE_GLINTS)`
- L7 #pragma `once`

#### Structs / classes (2)

- L255-664 _struct_ **`FPackedPathTracingPayload`** `struct FPackedPathTracingPayload : FMinimalPayload` — base/reg: `FMinimalPayload` — This payload structure is what we transport between RGS/CHS/AHS programs
  - L259 _member_ `uint PackedData[7];` — 28 bytes (encoded data, depends on shading model and ray type) _[#if IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS)]_
  - L262 _member_ `uint PackedData[18];` — 72 bytes _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L266 _method_ `float UnpackBSDFOpacity()`
  - L267 _method_ `uint GetPathTracingShadingModelID()`
  - L268 _method_ `uint GetFlags()`
  - L269 _method_ `void SetFlag(uint Flag)`
  - L270 _method_ `void RemoveFlag(uint Flag)`
  - L271 _method_ `uint GetPrimitiveLightingChannelMask()`
  - L274 _method_ `void SetCameraRay()` — Flag methods
  - L275 _method_ `bool IsCameraRay()`
  - L277 _method_ `void SetVisibilityRay()`
  - L278 _method_ `bool IsVisibilityRay()`
  - L280 _method_ `bool IsFrontFace()`
  - L282 _method_ `bool IsDecalReceiver()`
  - L291 _method_ `bool HasDecalResponseColor()`
  - L292 _method_ `bool HasDecalResponseNormal()`
  - L293 _method_ `bool HasDecalResponseRoughness()`
  - L294 _method_ `bool UsesDBufferLookup()`
  - L296 _method_ `void SetOutputDepth()`
  - L297 _method_ `bool ShouldOutputDepth()`
  - L299 _method_ `bool IsHoldout()`
  - L302 _method_ `float3 GetRayThroughput()` — These method are meant to be used only when IsVisibilityRay() is true
  - L311 _method_ `void SetRayThroughput(float3 RayThroughput)`
  - L318 _method_ `float GetPathRoughness()`
  - L323 _method_ `void SetPathRoughness(float PathRoughness)`
  - L332 _method_ `float3 GetTau()` — tau: optical depth along shadow ray, this is the integral of the extinction coefficient _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L341 _method_ `void SetTau(float3 Tau)` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L350 _method_ `bool CheckDuplicateAHS(float T)` — Check if we have already run the same hit through AHS
  - L360 _method_ `void UpdateDuplicateAHS(float T)`
  - L372 _method_ `float3 UnpackWorldGeoNormal()` _[#if IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS)]_
  - L373 _method_ `float3 UnpackWorldNormal()` _[#if IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS)]_
  - L374 _method_ `float3 UnpackRadiance()` _[#if IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS)]_
  - L375 _method_ `float3 UnpackBaseColor()` _[#if IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS)]_
  - L376 _method_ `float3 UnpackTransparencyColor()` _[#if IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS)]_
  - L377 _method_ `float3 UnpackSubsurfaceColor()` _[#if IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS)]_
  - L382 _method_ `float3 UnpackWorldGeoNormal()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L383 _method_ `float3 UnpackWorldSmoothNormal()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L384 _method_ `float3 UnpackWorldNormal()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L385 _method_ `float3 UnpackRadiance()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L387 _method_ `void PackWorldNormal(float3 N)` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L388 _method_ `void PackRadiance(float3 R)` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L390 _method_ `float3 UnpackWorldTangent()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L391 _method_ `float UnpackIor()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L393 _method_ `float3 UnpackDiffuseColor()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L394 _method_ `float3 UnpackSpecularColor()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L395 _method_ `float3 UnpackSpecularEdgeColor()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L396 _method_ `float4 UnpackRoughnessAniso()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L397 _method_ `float3 UnpackTransparencyColor()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L398 _method_ `float3 UnpackMeanFreePath()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L401 _method_ `float UnpackPhaseG()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L402 _method_ `float3 UnpackFuzzColor()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L403 _method_ `float3 UnpackWeightV()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L404 _method_ `float3 UnpackTransmittanceN()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L406 _method_ `float UnpackCoverageAboveAlongN()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L407 _method_ `float UnpackSpecularProfileId()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L409 _method_ `void PackDiffuseColor(float3 C)` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L410 _method_ `void PackSpecularColor(float3 C)` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L411 _method_ `void PackRoughnessAniso(float4 D)` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L413 _method_ `float4 GetDBufferA()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L421 _method_ `void SetDBufferA(float4 DBufferA)` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L427 _method_ `float4 GetDBufferB()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L435 _method_ `void SetDBufferB(float4 DBufferB)` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L441 _method_ `float4 GetDBufferC()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L449 _method_ `void SetDBufferC(float4 DBufferC)` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L455 _method_ `void SetStochasticSlabRand(float SlabRand)` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L460 _method_ `float GetStochasticSlabRand()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L465 _method_ `float GetSceneDepth()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L471 _method_ `void SetSceneDepth(float SceneZ)` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L478 _method_ `void SetVolumetricCallableShaderInput(float3 Origin, float3 Direction, float TMin, float TMax, FRandomSequence RandSeq, uint Flags, float3 Throughput, float CloudDensity)` — Volumetric callable shaders _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS)) && PATH_TRACER_USE_CLOUD_SHADER]_
  - L496 _method_ `void SetVolumetricCallableShaderInputCloudFactor(float CloudFactor)` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS)) && PATH_TRACER_USE_CLOUD_SHADER]_
  - L501 _method_ `void SetVolumetricCallableShaderRISContext(FRISContext SurfaceContext)` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS)) && PATH_TRACER_USE_CLOUD_SHADER]_
  - L507 _method_ `FRayDesc GetVolumetricCallableShaderInputRay()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS)) && PATH_TRACER_USE_CLOUD_SHADER]_
  - L517 _method_ `FRandomSequence GetVolumetricCallableShaderInputRandSequence()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS)) && PATH_TRACER_USE_CLOUD_SHADER]_
  - L525 _method_ `uint GetVolumetricCallableShaderInputFlags()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS)) && PATH_TRACER_USE_CLOUD_SHADER]_
  - L530 _method_ `float3 GetVolumetricCallableShaderInputThroughput()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS)) && PATH_TRACER_USE_CLOUD_SHADER]_
  - L535 _method_ `float GetVolumetricCallableShaderInputCloudFactor()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS)) && PATH_TRACER_USE_CLOUD_SHADER]_
  - L540 _method_ `float GetVolumetricCallableShaderInputCloudDensity()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS)) && PATH_TRACER_USE_CLOUD_SHADER]_
  - L545 _method_ `FRISContext GetVolumetricCallableShaderRISContext()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS)) && PATH_TRACER_USE_CLOUD_SHADER]_
  - L553 _method_ `void SetVolumetricCallableShaderOutput(FRandomSequence RandSeq, float3 Throughput, float3 Albedo)` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS)) && PATH_TRACER_USE_CLOUD_SHADER]_
  - L563 _method_ `void SetVolumetricCallableShaderOutput(FRandomSequence RandSeq, float3 Throughput)` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS)) && PATH_TRACER_USE_CLOUD_SHADER]_
  - L573 _method_ `void SetVolumetricCallableShaderOutputSample(float SampleT, float3 AlbedoRayleigh, float3 AlbedoHG1, float PhaseG, float3 AlbedoHG2, float3 DualPhaseData, float3 PayloadThroughput)` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS)) && PATH_TRACER_USE_CLOUD_SHADER]_
  - L584 _method_ `void SetVolumetricCallableShaderOutputCloudDensityFactor(float Factor)` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS)) && PATH_TRACER_USE_CLOUD_SHADER]_
  - L590 _method_ `void SetVolumetricCallableShaderOutputRadiance(float3 Radiance, float Alpha)` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS)) && PATH_TRACER_USE_CLOUD_SHADER]_
  - L597 _method_ `FRandomSequence GetVolumetricCallableShaderOutputRandSeq()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS)) && PATH_TRACER_USE_CLOUD_SHADER]_
  - L605 _method_ `float3 GetVolumetricCallableShaderOutputThroughput()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS)) && PATH_TRACER_USE_CLOUD_SHADER]_
  - L610 _method_ `float3 GetVolumetricCallableShaderOutputAlbedo()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS)) && PATH_TRACER_USE_CLOUD_SHADER]_
  - L615 _method_ `float3 GetVolumetricCallableShaderOutputTransmittanceThroughput()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS)) && PATH_TRACER_USE_CLOUD_SHADER]_
  - L621 _method_ `float3 GetVolumetricCallableShaderOutputPayloadThroughput()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS)) && PATH_TRACER_USE_CLOUD_SHADER]_
  - L626 _method_ `float3 GetVolumetricCallableShaderOutputRayleighWeight()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS)) && PATH_TRACER_USE_CLOUD_SHADER]_
  - L631 _method_ `float4 GetVolumetricCallableShaderOutputHG()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS)) && PATH_TRACER_USE_CLOUD_SHADER]_
  - L636 _method_ `float3 GetVolumetricCallableShaderOutputDualHGWeight()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS)) && PATH_TRACER_USE_CLOUD_SHADER]_
  - L641 _method_ `float3 GetVolumetricCallableShaderOutputDualHGPhaseData()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS)) && PATH_TRACER_USE_CLOUD_SHADER]_
  - L646 _method_ `float3 GetVolumetricCallableShaderOutputRadiance()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS)) && PATH_TRACER_USE_CLOUD_SHADER]_
  - L651 _method_ `float GetVolumetricCallableShaderOutputAlpha()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS)) && PATH_TRACER_USE_CLOUD_SHADER]_
  - L656 _method_ `float GetVolumetricCallableShaderOutputCloudDensityFactor()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS)) && PATH_TRACER_USE_CLOUD_SHADER]_
- L674-868 _struct_ **`FPathTracingPayload`** `struct FPathTracingPayload : FMinimalPayload` — base/reg: `FMinimalPayload` — This payload structure is the expanded version of the above which is more convenient to work with
  - L676 _member_ `float3 Radiance;`
  - L677 _member_ `float3 WorldGeoNormal;` — normal of the actual triangle (faceted)
  - L678 _member_ `float3 WorldNormal;` — normal output of the material (includes normal/bump)
  - L682 _member_ `float3 WorldSmoothNormal;` — smooth normal before normal/bump is applied _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L685 _member_ `float BSDFOpacity;` — how much should we weigh down the bsdf by? (this also accounts for the probability of picking a particular lobe in multi-lobed materials)
  - L686 _member_ `float3 TransparencyColor;` — how much do we see straight through the surface?
  - L687 _member_ `uint PathTracingShadingModelID;`
  - L688 _member_ `uint Flags;`
  - L689 _member_ `uint PrimitiveLightingChannelMask;`
  - L692 _member_ `float3 BaseColor;` _[#if IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS)]_
  - L693 _member_ `float3 SubsurfaceColor;` _[#if IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS)]_
  - L695 _member_ `float3 DiffuseColor;` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L696 _member_ `float3 SpecularColor;` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L697 _member_ `float3 SpecularEdgeColor;` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L698 _member_ `float3 RoughnessData;` — r0,r1,rblend _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L699 _member_ `float Anisotropy;` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L700 _member_ `float3 WorldTangent;` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L701 _member_ `float3 MeanFreePath;` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L702 _member_ `float PhaseG;` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L703 _member_ `float Ior;` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L704 _member_ `float FuzzAmount;` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L705 _member_ `float FuzzRoughness;` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L706 _member_ `float3 FuzzColor;` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L707 _member_ `float3 WeightV;` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L708 _member_ `float3 TransmittanceN;` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L709 _member_ `float CoverageAboveAlongN;` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L711 _member_ `float SpecularProfileId;` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS)) && SUBSTRATE_PATH_TRACING_SPECULAR_PROFILE]_
  - L714 _member_ `float GlintValue;` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS)) && SUBSTRATE_PATH_TRACING_GLINTS]_
  - L715 _member_ `float2 GlintUV;` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS)) && SUBSTRATE_PATH_TRACING_GLINTS]_
  - L716 _member_ `float2 GlintUVdx;` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS)) && SUBSTRATE_PATH_TRACING_GLINTS]_
  - L717 _member_ `float2 GlintUVdy;` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS)) && SUBSTRATE_PATH_TRACING_GLINTS]_
  - L720 _member_ `float3 SubsurfaceColor;` — not transported through packed payload, but used in raygen _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L725 _member_ `float3 TranslatedWorldPos;`
  - L727 _method_ `void SetFrontFace()`
  - L728 _method_ `bool IsFrontFace()`
  - L730 _method_ `void SetDecalReceiver(uint DecalResponseMask)`
  - L732 _method_ `void SetUseDBufferLookup()`
  - L733 _method_ `bool UsesDBufferLookup()`
  - L735 _method_ `void SetHoldout()`
  - L736 _method_ `bool IsHoldout()`
  - L738 _method_ `void SetMaterialTwoSided()`
  - L739 _method_ `bool IsMaterialTwoSided()`
  - L741 _method_ `void SetOutputDepth()`
  - L742 _method_ `bool ShouldOutputDepth()`
  - L745 _method_ `float3 GetBaseColor()` _[#if IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS)]_
  - L746 _method_ `float3 GetSubsurfaceColor()` _[#if IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS)]_
  - L747 _method_ `bool IsMaterialTransmissive()` _[#if IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS)]_
  - L754 _method_ `float3 GetMaxLobeWeight()` — SHADINGMODELID_SUBSTRATE _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L760 _method_ `float3 GetBaseColor()` — SHADINGMODELID_LAMBERT and SHADINGMODELID_MEDIUM _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L761 _method_ `void SetBaseColor(float3 BaseColor)` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L764 _method_ `float3 GetHGWeight()` — SHADINGMODELID_MEDIUM _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L765 _method_ `float GetHGPhaseG()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L766 _method_ `void SetHG(float3 Weight, float G)` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L771 _method_ `float3 GetDualHGWeight()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L772 _method_ `float3 GetDualHGPhaseData()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L773 _method_ `void SetDualHG(float3 Weight, float3 PhaseData)` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L778 _method_ `float GetCloudFactor()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L779 _method_ `void SetCloudFactor(float Factor)` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L782 _method_ `float GetEyeRoughness()` — SHADINGMODELID_EYE _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L783 _method_ `void SetEyeRoughness(float R)` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L784 _method_ `float3 GetEyeCausticNormal()` — SUBSTRATE_TODO: not optimal since packed as color _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L785 _method_ `void SetEyeCausticNormal(float3 CausticNormal)` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L786 _method_ `float GetEyeIrisMask()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L787 _method_ `void SetEyeIrisMask(float IrisMask)` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L788 _method_ `float3 GetEyeIrisNormal()` — SUBSTRATE_TODO: not optimal since packed as color _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L789 _method_ `void SetEyeIrisNormal(float3 IrisNormal)` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L792 _method_ `float GetHairLongitudinalRoughness()` — SHADINGMODELID_HAIR _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L793 _method_ `void SetHairLongitudinalRoughness(float Roughness)` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L794 _method_ `float GetHairAzimuthalRoughness()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L795 _method_ `void SetHairAzimuthalRoughness(float AzimuthalRoughness)` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L796 _method_ `float GetHairSpecular()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L797 _method_ `void SetHairSpecular(float Specular)` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L798 _method_ `float2 GetHairPrimitiveUV()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L799 _method_ `void SetHairPrimitiveUV(float2 UV)` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L802 _method_ `float3 GetExtinction()` — SHADINGMODELID_SOLID_GLASS _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L803 _method_ `float3 GetGlassAlbedo()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L804 _method_ `void SetGlassAlbedo(float3 A)` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L805 _method_ `float GetGlassPhase()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L806 _method_ `void SetGlassPhase(float G)` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L809 _method_ `float3 GetTransmittanceColor()` — SHADINGMODELID_THIN_TRANSLUCENT _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L810 _method_ `void SetTransmittanceColor(float3 TransmittanceColor)` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L813 _method_ `float3 GetFoliageTransmissionColor()` — SHADINGMODELID_TWOSIDED_FOLIAGE _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L814 _method_ `void SetFoliageTransmissionColor(float3 C)` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L817 _method_ `float3 GetBottomCoatNormal()` — SHADINGMODELID_CLEAR_COAT _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L818 _method_ `void SetBottomCoatNormal(float3 BottomNormal)` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L822 _method_ `bool HasRefraction()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L827 _method_ `bool IsMaterialSolidGlass()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L832 _method_ `bool IsMaterialThinGlass()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L837 _method_ `bool IsMaterialTransmissive()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L848 _method_ `bool IsSubsurfaceMaterial()` _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_
  - L856 _method_ `bool HasFuzzLobe()` — Are the Fuzz* parameters used for the fuzz lobe? _[#if !(IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS))]_

#### static const (2)

- L99 _static_const_ `static const float DenoiserMaxRoughness = 0.15f;` — Utilities to help weight the contribution of the albedo/normal to the denoising buffers We want cases like low roughness mirrors to "pass through" the signal
- L100 _static_const_ `static const float DenoiserMinRoughness = 0.10f;` — capture anything below this level

#### Functions (22)

- L67-70 _function_ `uint GetPathTracingHairRayFlags(float3 RayOrigin)`
- L78-94 _function_ `float ComputeNewTMin(float3 O, float3 D, float THit)` — Given a ray with origin O in direction D, assuming we have found a valid hit at THit, compute a new TMin value that we can use to retrace the same ray and find more hits. This is used for transparency, mesh decals and SSS tracing.
- L103-106 _function_ `float DenoiserAOVWeight(float PathRoughness)` — Given the current path roughness, how much contribution should the current hit make to the denoiser AOVs?
- L109-113 _function_ `float DenoiserRoughnessWeight(float Roughness, float PathRoughness)` — For a given surface of roughness R, how much should its own contribution be counted This heuristic lets us skip the contribution a mirror's albedo would normally make because we will be seeing "through" it to the next hit
- L116-119 _function_ `float3 PathTracingGlassTransmittanceToExtinction(float3 TransmittanceColor)` — This function is meant for the solid glass case so we can store the transmittance as a color in [0,1]
- L121-128 _function_ `uint PayloadEncodeUnitVector(float3 Normal)`
- L130-139 _function_ `float3 PayloadDecodeUnitVector(uint Encoded)`
- L142-159 _function_ `uint PayloadEncodeTangentAngle(float3 Normal, float3 Tangent)` — Encode a tangent vector relative to a given Normal
- L162-179 _function_ `float3 PayloadDecodeTangentAngle(float3 Normal, uint Bits)` — Decode a tangent vector relative to a given Normal
- L181-184 _function_ `uint PayloadEncodeHDRColor(float3 rgb)`
- L186-189 _function_ `float3 PayloadDecodeHDRColor(uint rgb)`
- L191-194 _function_ `uint PayloadEncodeLDRColor(float3 rgb)`
- L196-199 _function_ `float3 PayloadDecodeLDRColor(uint rgb)`
- L201-208 _function_ `uint PayloadEncodeRoughnessAniso(float3 RoughnessData, float Anisotropy)`
- L210-217 _function_ `float4 PayloadDecodeRoughnessAniso(uint rgba)`
- L219-223 _function_ `uint PayloadEncodeFuzz(float FuzzAmount, float FuzzRoughness)`
- L225-230 _function_ `void PayloadDecodeFuzz(uint Bits, inout float FuzzAmount, inout float FuzzRoughness)`
- L232-247 _function_ `float3 AdjustShadingNormal(float3 ShadingNormal, float3 GeoNormal, float3 V_World)`
- L870-885 _function_ `FPackedPathTracingPayload InitPathTracingPayload(uint ScatterType, float PathRoughness)`
- L887-902 _function_ `FPackedPathTracingPayload InitPathTracingVisibilityPayload(float PathRoughness)`
- L904-962 _function_ `FPackedPathTracingPayload PackPathTracingPayload(FPathTracingPayload Input)`
- L965-1035 _function_ `FPathTracingPayload UnpackPathTracingPayload(FPackedPathTracingPayload Input, FRayDesc Ray)` _[#if RAYGENSHADER]_

#### Top-level macro invocations (2)

- L667 _macro_call_ `CHECK_RT_PAYLOAD_SIZE(FPackedPathTracingPayload)` _[#if IS_PAYLOAD_ENABLED(RT_PAYLOAD_PATH_TRACING_MATERIAL)]_
- L670 _macro_call_ `CHECK_RT_PAYLOAD_SIZE(FPackedPathTracingPayload)` _[#if IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_GPULIGHTMASS)]_

### `Shaders/Private/PathTracing/PathTracingCompositingPixelShader.usf` (Private)

- lines: 99; parse: all-branches
- includes: L7 `../Common.ush`, L8 `../ColorMap.ush`, L9 `PathTracingAdaptiveUtils.ush`

#### Entry points (1)

- L19-98 _entry_ `void CompositeMain( in noperspective float4 UVAndScreenPos : TEXCOORD0, out float4 OutColor : SV_Target0, out float OutDepth : SV_DEPTH )` — stage: **pixel (from C++ binding)** — C++: `FPathTracingCompositorPS` SF_Pixel via IMPLEMENT_SHADER_TYPE (Source/Runtime/Renderer/Private/PathTracing.cpp:3775)

#### Global resources (textures / buffers / samplers) (2)

- L14 _resource_ `Texture2D<float4> RadianceTexture;`
- L15 _resource_ `Texture2D<float> DepthTexture;`

#### Global parameters (uniforms) (5)

- L11 _parameter_ `uint Iteration;`
- L12 _parameter_ `uint MaxSamples;`
- L13 _parameter_ `int ProgressDisplayEnabled;`
- L16 _parameter_ `float PreExposure;` — Taken from the view, but adjusted by the base exposure already applied to the Radiance texture
- L17 _parameter_ `int AdaptiveSamplingVisualize;`

### `Shaders/Private/PathTracing/PathTracingCopyDepth.usf` (Private)

- lines: 21; parse: all-branches
- includes: L3 `../Common.ush`

#### Entry points (1)

- L9-20 _entry_ `void CopyDepth( in noperspective float4 UVAndScreenPos : TEXCOORD0, out float OutDepth : SV_DEPTH, out float4 OutColor : SV_Target0 )` — stage: **pixel (from C++ binding)** — C++: `FPathTracingCopyDepthPS` SF_Pixel via IMPLEMENT_SHADER_TYPE (Source/Runtime/Renderer/Private/PathTracing.cpp:1683)

#### Global resources (textures / buffers / samplers) (1)

- L5 _resource_ `Texture2D<float> DepthTexture;`

#### Global parameters (uniforms) (2)

- L6 _parameter_ `float PreExposure;` — Taken from the view, but adjusted by the base exposure already applied to the Radiance texture
- L7 _parameter_ `int AdaptiveSamplingVisualize;`

### `Shaders/Private/PathTracing/PathTracingCore.ush` (Private)

- lines: 2032; parse: all-branches
- includes: L15 `../HeterogeneousVolumes/HeterogeneousVolumesVoxelGridTypes.ush`, L16 `../Common.ush`, L17 `../PostProcessCommon.ush`, L18 `../RectLight.ush`, L19 `../RayTracing/RayTracingCommon.ush`, L21 `PathTracingCommon.ush`, L22 `../RayTracing/RayTracingHitGroupCommon.ush`, L23 `PathTracingDecals.ush`, L25 `../ShadingModels.ush`, L27 `./Utilities/PathTracingRandomSequence.ush`, L28 `./Utilities/PathTracingRIS.ush`, L29 `./Light/PathTracingLightSampling.ush`, L30 `./Light/PathTracingLightGrid.ush`, L31 `./Material/PathTracingMaterialSampling.ush`, L32 `./Volume/PathTracingVolume.ush`, L33 `./Volume/PathTracingVolumeSampling.ush`, L36 `../ShaderPrint.ush` [DEBUG_ENABLE], L40 `/Engine/Public/NvidiaExtensionsCommon.ush` [PATH_TRACER_USE_SER]

#### Macros (#define, 8)

- L5 `#define RANDSEQ_SFC_TEXTURE 1`
- L7 `#define USE_PATH_TRACING_LIGHT_GRID 1`
- L8 `#define USE_RAY_TRACING_DECAL_GRID 1`
- L12 `#define DEBUG_ENABLE 0` _[#if !defined(DEBUG_ENABLE)]_
- L972 `#define SSS_USE_INTERFACE_COUNTING 1`
- L1261 `#define SSS_USE_TIR 1`
- L1278 `#define SSS_USE_DWIVEDI 1`
- L1279 `#define SSS_USE_DWIVEDI_USE_THIN_SLABS 1`
- L3 #pragma `once`

#### Structs / classes (2)

- L91-364 _struct_ **`FPathState`** `struct FPathState`
  - L93 _member_ `FRandomSequence RandSequence;` — 8 bytes
  - L94 _member_ `float3 Radiance;` — 12 bytes
  - L95 _member_ `float Alpha;` — 4 bytes
  - L96 _member_ `uint3 PackedAlbedoNormal;` — 6 bytes // half precision (Albedo)
  - L98 _member_ `FRayDesc Ray;` — 6 bytes // half precision (Normal)
  - L99 _member_ `float3 PathThroughput;` — 12 bytes
  - L100 _member_ `uint2 PackedRoughnessSigma;` — 2 bytes // half precision (PathRoughness)
  - L103 _member_ `uint2 PackedScatterPhase;` — 6 bytes // half precision  (SigmaT) 3 bits - packed in sign bits of SigmaT (FirstScatterType)
  - L109 _member_ `float DepthZ;` — Camera ray depth (don't need it otherwise) _[#if PATH_TRACER_KERNEL_TYPE == PATH_TRACER_KERNEL_CAMERA]_
  - L112 _member_ `uint2 PixelCoord;` — Pixel index/coord _[#if DEBUG_ENABLE && PATH_TRACER_KERNEL_TYPE == PATH_TRACER_KERNEL_CAMERA]_
  - L115 _method_ `float3 GetAlbedo()`
  - L121 _method_ `float3 GetNormal()`
  - L127 _method_ `void SetAlbedoNormal(float3 Albedo, float3 Normal)`
  - L134 _method_ `uint GetFirstScatterType()`
  - L143 _method_ `void SetFirstScatterType(uint ScatterType)`
  - L157 _method_ `float GetPathRoughness()`
  - L162 _method_ `void SetPathRoughness(float PathRoughness)`
  - L168 _method_ `float3 GetSigmaT()`
  - L175 _method_ `void SetSigmaT(float3 SigmaT)`
  - L187 _method_ `float4 GetSigmaSAndPhase()`
  - L192 _method_ `void SetSigmaSAndPhase(float3 SigmaS, float PhaseG)`
  - L198 _method_ `bool HasMadeContributionScatter()`
  - L207 _method_ `bool HasMadeDiffuseOrSpecularScatter()`
  - L213 _method_ `uint GetInstanceInclusionMaskOpaque()`
  - L228 _method_ `uint GetInstanceInclusionMaskTranslucent()`
  - L243 _method_ `bool UpdateScatterType(uint ScatterType)`
  - L265 _method_ `bool ShouldAccumulateEmissive()`
  - L272 _method_ `bool ShouldAccumulateDiffuse()` — The following functions allow us to scale down the contributions for lighting components before we have scattered
  - L277 _method_ `bool ShouldAccumulateSpecular()`
  - L282 _method_ `bool ShouldAccumulateVolume()`
  - L287 _method_ `float2 GetDiffuseSpecularScale(bool bIsVolumeSample)`
  - L311 _method_ `void WritePixel(uint2 TextureIndex)`
  - L340 _method_ `void WriteDepth(uint2 TextureIndex)` _[#if PATH_TRACER_KERNEL_TYPE == PATH_TRACER_KERNEL_CAMERA]_
  - L348 _method_ `void AccumulateRadiance(float3 PathRadiance)`
- L955-964 _struct_ **`FProbeResult`** `struct FProbeResult`
  - L957 _member_ `float HitT;`
  - L958 _member_ `float3 WorldNormal;`
  - L959 _member_ `float3 WorldSmoothNormal;`
  - L960 _member_ `float3 WorldGeoNormal;`
  - L961 _member_ `int FrontFace;`
  - L963 _method_ `bool IsMiss()`

#### Global resources (textures / buffers / samplers) (7)

- L79 _resource_ `RWTexture2D<float4> RadianceTexture;`
- L81 _resource_ `RWTexture2D<float4> VarianceTexture;` _[#if PATH_TRACER_USE_ADAPTIVE_SAMPLING]_
- L83 _resource_ `RWTexture2D<float4> AlbedoTexture;`
- L84 _resource_ `RWTexture2D<float4> NormalTexture;`
- L85 _resource_ `RWTexture2D<float> DepthTexture;`
- L86 _resource_ `RaytracingAccelerationStructure TLAS;`
- L89 _resource_ `Buffer<float> StartingMediumData;`

#### Global parameters (uniforms) (26)

- L44 _parameter_ `float BlendFactor;`
- L45 _parameter_ `float BaseExposure;`
- L46 _parameter_ `uint Iteration;`
- L47 _parameter_ `uint TemporalSeed;`
- L48 _parameter_ `uint MaxSamples;`
- L49 _parameter_ `uint MaxBounces;`
- L50 _parameter_ `uint MaxSSSBounces;`
- L51 _parameter_ `float SSSGuidingRatio;`
- L53 _parameter_ `float BackgroundAlpha;`
- L58 _parameter_ `uint MISMode;` — 0: only Material sampling 1: only Light sampling 2: both Material and Light
- L62 _parameter_ `uint VolumeMISMode;` — 0: only Density sampling 1: Light sampling
- L64 _parameter_ `float ApproximateCaustics;` — Either 0 (off) or 1 (on) -- done this way to avoid conditionals
- L65 _parameter_ `uint SamplerType;`
- L66 _parameter_ `uint ApplyDiffuseSpecularOverrides;`
- L67 _parameter_ `uint EnabledDirectLightingContributions;`
- L68 _parameter_ `uint EnabledIndirectLightingContributions;`
- L69 _parameter_ `float MaxPathIntensity;`
- L70 _parameter_ `float MaxNormalBias;`
- L71 _parameter_ `float FilterWidth;`
- L72 _parameter_ `float CameraFocusDistance;`
- L73 _parameter_ `float2 CameraLensRadius;`
- L74 _parameter_ `float Petzval;`
- L75 _parameter_ `float PetzvalFalloffPower;`
- L76 _parameter_ `float2 PetzvalExclusionBoxExtents;`
- L77 _parameter_ `float PetzvalExclusionBoxRadius;`
- L87 _parameter_ `uint SceneVisibleLightCount;`

#### Functions (12)

- L366-889 _function_ `FPackedPathTracingPayload TraceTransparentRay(inout FPathState PathState, int Bounce, inout FVolumeSegment VolumeSegment)`
- L891-953 _function_ `float3 TraceTransparentVisibilityRay(FRayDesc Ray, float PathRoughness, float PreviousPathRoughness, uint MissShaderIndex, bool bCastShadows, bool bCloudCastShadows, float CloudFactor, inout FRandomSequence RandSequence)`
- L966-1029 _function_ `FProbeResult TraceSSSProbeRay(FRayDesc Ray, inout int InterfaceCounter)`
- L1031-1039 _function_ `float3 ComputeDwivediScale(float3 Albedo)`
- L1041-1092 _function_ `float SampleGuidedSpectralTransmittance(float RandValue, float SlabCosine, float3 DwivediScale, float GuidingFactor, float3 Sigma, float3 ProbT, float3 ColorChannelPdf)`
- L1094-1109 _function_ `float4 EvaluateGuidedSpectralTransmittanceHit(float SampledT, float SlabCosine, float3 DwivediScale, float GuidingFactor, float3 Sigma, float3 ProbT, float3 ColorChannelPdf)`
- L1111-1127 _function_ `float4 EvaluateGuidedSpectralTransmittanceMiss(float MaxT, float SlabCosine, float3 DwivediScale, float GuidingFactor, float3 Sigma, float3 ProbT, float3 ColorChannelPdf)`
- L1130-1207 _function_ `float4 SampleDwivediPhaseFunction(float3 ColorChannelPdf, float3 DwivediScale, float GuidingFraction, float3 ProbT, float3 DwivediSlabNormal, float3 RayDirection, float G, float2 RandSample)` — returns: xyz: world space direction, w: throughput scale
- L1209-1441 _function_ `bool ProcessSubsurfaceRandomWalk(inout FPathTracingPayload Payload, inout float3 PathThroughput, inout FRandomSequence RandSequence, float3 RayDirection, bool SimplifySSS)`
- L1446-1478 _function_ `float2 ApplyPetzval(float2 BokehCenterUV, float2 SamplePos)` — Apply sagittal/tangential Petzval lens effect BokehCenterUV: Viewport UV of the center of the bokeh SamplePos: UV of the sample relative to the bokeh center, with 1 = bokeh boundary
- L1480-1561 _function_ `FPathState CreatePathState(int2 PixelIndex, int2 TextureIndex)`
- L1563-2031 _function_ `bool PathTracingKernel(inout FPathState PathState, int Bounce)`

### `Shaders/Private/PathTracing/PathTracingDebug.usf` (Private)

- lines: 1770; parse: per-group
- includes: L35 `../Common.ush`, L36 `../RayTracing/RayTracingCommon.ush`, L37 `../RayTracing/RayTracingDecalGrid.ush`, L38 `PathTracingCommon.ush`, L39 `PathTracingDecals.ush`, L40 `Material/PathTracingMaterialSampling.ush`, L41 `Utilities/PathTracingRandomSequence.ush`, L42 `Utilities/PathTracingRIS.ush`, L43 `Light/PathTracingLightSampling.ush`, L44 `Light/PathTracingLightGrid.ush`, L47 `/Engine/Public/NvidiaExtensionsCommon.ush` [PATH_TRACER_USE_SER]

#### Macros (#define, 15)

- L3 `#define RANDSEQ_SFC_TEXTURE 1`
- L5 `#define LIGHT_LOOP_METHOD 2`
- L7 `#define EVALUATE_MATERIAL_BSDF 1`
- L8 `#define USE_BSDF_SAMPLING 1`
- L11 `#define LIGHT_SELECTION_METHOD 1` _[#if LIGHT_LOOP_METHOD == 0]_
- L12 `#define BSDF_SAMPLING_METHOD 0` _[#if LIGHT_LOOP_METHOD == 0]_
- L17 `#define ACCUMULATE_UNSHADOWED_LIGHTS 1` _[#if LIGHT_LOOP_METHOD == 2]_
- L18 `#define FORCE_TRACE_INFINITE_LIGHTS 0` _[#if LIGHT_LOOP_METHOD == 2]_
- L21 `#define CLAMP_PATH_INTENSITY 1`
- L23 `#define USE_PATH_TRACING_LIGHT_GRID 1`
- L24 `#define USE_RAY_TRACING_DECAL_GRID 1`
- L27 `#define PATH_TRACER_PRIMARY_RAYS 1` _[#if !defined(PATH_TRACER_PRIMARY_RAYS)]_
- L31 `#define PATH_TRACER_INCLUDE_TRANSLUCENT 1` _[#if !defined(PATH_TRACER_INCLUDE_TRANSLUCENT)]_
- L631 `#define PackedPayload OpaquePackedPayload` _[#if PATH_TRACER_PRIMARY_RAYS && !(PATH_TRACER_INCLUDE_TRANSLUCENT)]_
- L1403 `#define PackedPayload OpaquePackedPayload` _[#if !(PATH_TRACER_PRIMARY_RAYS) && !(PATH_TRACER_INCLUDE_TRANSLUCENT)]_

#### Entry points (1)

- L1675-1769 _entry_ `RAY_TRACING_ENTRY_RAYGEN(PathTracingDebugRG)` — stage: **raygeneration** — C++: `FPathTracingDebugRG` SF_RayGen via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PathTracing.cpp:1659)

#### Structs / classes (2)

- L123-131 _struct_ **`FPathTracingResult`** `struct FPathTracingResult`
  - L124 _member_ `float4 Radiance;`
  - L125 _member_ `float3 DiffuseColor;`
  - L126 _member_ `float3 SpecularColor;`
  - L127 _member_ `float3 WorldNormal;`
  - L128 _member_ `float Roughness;`
  - L129 _member_ `float LinearDepth;`
  - L130 _member_ `float Z;`
- L146-442 _struct_ **`FPathState`** `struct FPathState`
  - L148 _member_ `FRandomSequence RandSequence;` — 8 bytes
  - L149 _member_ `float3 Radiance;` — 12 bytes
  - L150 _member_ `float Alpha;` — 4 bytes
  - L151 _member_ `uint3 PackedDiffSpecColor;` — 12 bytes
  - L152 _member_ `uint2 PackedNormalRoughness;` — 8 bytes
  - L153 _member_ `FRayDesc Ray;` — 12+12 = 24 bytes (TMin/TMax do not need to be stored)
  - L154 _member_ `float3 PathThroughput;` — 12 bytes
  - L155 _member_ `uint2 PackedRoughnessSigma;` — 2 bytes // half precision (PathRoughness)
  - L158 _member_ `uint2 PackedScatterPhase;` — 6 bytes // half precision  (SigmaT) 3 bits - packed in sign bits of SigmaT (FirstScatterType)
  - L163 _member_ `float DepthZ;` — Camera ray depth (don't need it otherwise) _[#if PATH_TRACER_KERNEL_TYPE == PATH_TRACER_KERNEL_CAMERA]_
  - L166 _method_ `float3 GetDiffuseColor()`
  - L172 _method_ `float3 GetSpecularColor()`
  - L178 _method_ `float3 GetNormal()`
  - L184 _method_ `float GetRoughness()`
  - L189 _method_ `void SetDiffuseSpecularColor(float3 Diffuse, float3 Specular)`
  - L196 _method_ `void SetNormal(float3 Normal)`
  - L202 _method_ `void SetRoughness(float Roughness)`
  - L207 _method_ `uint GetFirstScatterType()`
  - L216 _method_ `void SetFirstScatterType(uint ScatterType)`
  - L230 _method_ `float GetPathRoughness()`
  - L235 _method_ `void SetPathRoughness(float PathRoughness)`
  - L241 _method_ `float3 GetSigmaT()`
  - L248 _method_ `void SetSigmaT(float3 SigmaT)`
  - L260 _method_ `float4 GetSigmaSAndPhase()`
  - L265 _method_ `void SetSigmaSAndPhase(float3 SigmaS, float PhaseG)`
  - L271 _method_ `bool HasMadeContributionScatter()`
  - L280 _method_ `bool HasMadeDiffuseOrSpecularScatter()`
  - L286 _method_ `uint GetInstanceInclusionMaskOpaque()`
  - L301 _method_ `uint GetInstanceInclusionMaskTranslucent()`
  - L316 _method_ `bool UpdateScatterType(uint ScatterType)`
  - L338 _method_ `bool ShouldAccumulateEmissive()`
  - L345 _method_ `bool ShouldAccumulateDiffuse()` — The following functions allow us to scale down the contributions for lighting components before we have scattered
  - L350 _method_ `bool ShouldAccumulateSpecular()`
  - L355 _method_ `bool ShouldAccumulateVolume()`
  - L360 _method_ `float2 GetDiffuseSpecularScale(bool bIsVolumeSample)`
  - L384 _method_ `void WritePixel(uint2 TextureIndex)`
  - L412 _method_ `void WriteDepth(uint2 TextureIndex)` _[#if PATH_TRACER_KERNEL_TYPE == PATH_TRACER_KERNEL_CAMERA]_
  - L421 _method_ `void AccumulateRadiance(float3 PathRadiance)`

#### Global resources (textures / buffers / samplers) (12)

- L50 _resource_ `RWTexture2D<float4> RWSceneColor;`
- L51 _resource_ `RWTexture2D<float4> RWSceneDiffuseColor;`
- L52 _resource_ `RWTexture2D<float4> RWSceneSpecularColor;`
- L53 _resource_ `RWTexture2D<float4> RWSceneNormal;`
- L54 _resource_ `RWTexture2D<float> RWSceneRoughness;`
- L55 _resource_ `RWTexture2D<float> RWSceneLinearDepth;`
- L56 _resource_ `RWTexture2D<float> RWSceneDepth;`
- L57 _resource_ `RaytracingAccelerationStructure TLAS;`
- L1625 _resource_ `RWStructuredBuffer<FPathTracingDebugPackedPathState> PathStateData;`
- L1626 _resource_ `RWBuffer<uint> ActivePaths;`
- L1627 _resource_ `RWBuffer<uint> NumPathStates;`
- L1630 _resource_ `RWBuffer<uint> NextActivePaths;` _[#if PATH_TRACER_KERNEL_TYPE != PATH_TRACER_KERNEL_TAIL]_

#### Global parameters (uniforms) (11)

- L58 _parameter_ `uint SceneVisibleLightCount;`
- L60 _parameter_ `int DebugMode;`
- L61 _parameter_ `int SamplesPerPixel;`
- L62 _parameter_ `int SampleIndex;`
- L63 _parameter_ `float SampleBlendFactor;`
- L64 _parameter_ `int MaxBounces;`
- L65 _parameter_ `int EnableEmissive;`
- L67 _parameter_ `float MaxPathIntensity;` _[#if CLAMP_PATH_INTENSITY]_
- L70 _parameter_ `float AmbientOcclusionMaxDistance;` _[#if PATH_TRACER_PRIMARY_RAYS == 0]_
- L71 _parameter_ `uint VisualizeMaxCount;` _[#if PATH_TRACER_PRIMARY_RAYS == 0]_
- L74 _parameter_ `int FirstBounce;` _[#if PATH_TRACER_KERNEL_TYPE != PATH_TRACER_KERNEL_CAMERA]_

#### static const (2)

- L143 _static_const_ `static const uint EnabledDirectLightingContributions = 15u;` — TODO: Expose these like for the normal path tracer
- L144 _static_const_ `static const uint EnabledIndirectLightingContributions = 15u;`

#### Functions (13)

- L77-85 _function_ `uint4 GridHash(uint4 P)`
- L87-121 _function_ `float3 TraceShadowRay(FRayDesc Ray, float PathRoughness, float PreviousPathRoughness, uint MissShaderIndex, bool bCastShadows)`
- L133-140 _function_ `FPathTracingResult MakeResult(float3 Radiance, float Alpha, float Z)`
- L447-453 _function_ `float3 GetLightingChannelMaskDebugColor(int LightingChannelMask)`
- L455-461 _function_ `float3 AnisoDebugColor(float InAniso)`
- L465-748 _function_ `FPackedPathTracingPayload TraceTransparentRay(inout FPathState PathState, int Bounce)` _[#if PATH_TRACER_PRIMARY_RAYS]_
- L750-764 _function_ `float LightContribToSelectionWeight(float3 C)` _[#if PATH_TRACER_PRIMARY_RAYS]_
- L766-1208 _function_ `bool PathTracingDebugCore(inout FPathState PathState, int Bounce)` _[#if PATH_TRACER_PRIMARY_RAYS]_
- L1213-1229 _function_ `float3 GetPathTracingShadingModelColor(uint PathTracingShadingModelID)` — for debugging and to visualize _[#if !(PATH_TRACER_PRIMARY_RAYS)]_
- L1232-1264 _function_ `bool DebugModeRequiresFakeShading()` _[#if !(PATH_TRACER_PRIMARY_RAYS)]_
- L1266-1621 _function_ `FPathTracingResult PathTracingDebugCore(FRayDesc Ray, uint2 LaunchIndex)` _[#if !(PATH_TRACER_PRIMARY_RAYS)]_
- L1634-1652 _function_ `FPathState LoadPathStateData(uint Index)` _[#if PATH_TRACER_KERNEL_TYPE != PATH_TRACER_KERNEL_CAMERA]_
- L1656-1671 _function_ `void StorePathStateData(FPathState PathState, uint Index)` _[#if PATH_TRACER_KERNEL_TYPE != PATH_TRACER_KERNEL_TAIL]_

### `Shaders/Private/PathTracing/PathTracingDecals.ush` (Private)

- lines: 191; parse: all-branches
- includes: L5 `PathTracingCommon.ush`, L6 `../RayTracing/RayTracingCommon.ush`, L7 `../RayTracing/RayTracingDecalGrid.ush`

#### Macros (#define, 2)

- L148 `#define PATH_TRACER_DECAL_PROCESS_DBUFFER(OpaquePayload, ApproximateCaustics, SlabRand) if (OpaquePayload.UsesDBufferLookup() && HasDecalData(DecalPayload)) { if (EnableDBuffer) { OpaquePayload = InitPathTracingPayload( PathState.GetFirstScatterType(), ApproximateCaustics * PathState.Get ...` (36 lines) _[#if USE_DBUFFER]_
- L188 `#define PATH_TRACER_DECAL_PROCESS_DBUFFER(OpaquePayload, ApproximateCaustics, SlabRand) ` _[#if !(USE_DBUFFER)]_
- L3 #pragma `once`

#### Global resources (textures / buffers / samplers) (1)

- L9 _resource_ `RaytracingAccelerationStructure DecalTLAS;`

#### Global parameters (uniforms) (4)

- L10 _parameter_ `float DecalRoughnessCutoff;`
- L11 _parameter_ `float MeshDecalRoughnessCutoff;`
- L12 _parameter_ `float MeshDecalBias;`
- L13 _parameter_ `uint EnableDBuffer;`

#### Functions (3)

- L15-74 _function_ `void EvaluateDecals(float3 RayDirection, uint InstanceInclusionMask, float HitT, float PathRoughness, inout FDecalShaderPayload DecalPayload)`
- L76-79 _function_ `bool HasDecalData(FDecalShaderPayload DecalPayload)`
- L81-139 _function_ `void ApplyDecal(FDecalShaderPayload DecalPayload, inout FPackedPathTracingPayload PackedPayload, float PathRoughness)`

### `Shaders/Private/PathTracing/PathTracingDefaultHitShader.usf` (Private)

- lines: 38; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `/Engine/Private/RayTracing/RayTracingCommon.ush`, L5 `/Engine/Private/PathTracing/PathTracingCommon.ush`

#### Entry points (3)

- L8-18 _entry_ `RAY_TRACING_ENTRY_CLOSEST_HIT(PathTracingDefaultOpaqueCHS, FPackedPathTracingPayload, PackedPayload, FRayTracingIntersectionAttributes, Attributes)` — stage: **closesthit** — C++: `FPathTracingDefaultOpaqueHitGroup` SF_RayHitGroup via IMPLEMENT_SHADER_TYPE (Source/Runtime/Renderer/Private/PathTracing.cpp:3051) — C++: `FGPULightmassDefaultOpaqueHitGroup` SF_RayHitGroup via IMPLEMENT_SHADER_TYPE (Source/Runtime/Renderer/Private/PathTracing.cpp:3052)
- L20-30 _entry_ `RAY_TRACING_ENTRY_CLOSEST_HIT(PathTracingDefaultHiddenCHS, FPackedPathTracingPayload, PackedPayload, FRayTracingIntersectionAttributes, Attributes)` — stage: **closesthit** — C++: `FPathTracingDefaultHiddenHitGroup` SF_RayHitGroup via IMPLEMENT_SHADER_TYPE (Source/Runtime/Renderer/Private/PathTracing.cpp:3053) — C++: `FGPULightmassDefaultHiddenHitGroup` SF_RayHitGroup via IMPLEMENT_SHADER_TYPE (Source/Runtime/Renderer/Private/PathTracing.cpp:3054)
- L32-37 _entry_ `RAY_TRACING_ENTRY_ANY_HIT(PathTracingDefaultHiddenAHS, FPackedPathTracingPayload, PackedPayload, FRayTracingIntersectionAttributes, Attributes)` — stage: **anyhit** — C++: `FPathTracingDefaultHiddenHitGroup` SF_RayHitGroup via IMPLEMENT_SHADER_TYPE (Source/Runtime/Renderer/Private/PathTracing.cpp:3053) — C++: `FGPULightmassDefaultHiddenHitGroup` SF_RayHitGroup via IMPLEMENT_SHADER_TYPE (Source/Runtime/Renderer/Private/PathTracing.cpp:3054)

### `Shaders/Private/PathTracing/PathTracingGPULightmassMaterialHitShader.usf` (Private)

- lines: 496; parse: all-branches
- includes: L21 `/Engine/Private/Common.ush`, L22 `/Engine/Private/RayTracing/RayTracingCommon.ush`, L23 `/Engine/Private/RayTracing/RayTracingHitGroupCommon.ush`, L24 `/Engine/Private/PathTracing/PathTracingShaderUtils.ush`, L25 `/Engine/Generated/Material.ush`, L26 `/Engine/Generated/VertexFactory.ush`, L28 `/Engine/Private/RayTracing/RayTracingCalcInterpolants.ush`, L29 `/Engine/Private/ShadingCommon.ush`, L30 `/Engine/Private/DeferredShadingCommon.ush`, L31 `/Engine/Private/SubsurfaceProfileCommon.ush`, L32 `/Engine/Private/BurleyNormalizedSSSCommon.ush`, L33 `/Engine/Private/PathTracing/Material/PathTracingFresnel.ush`, L37 `/Engine/Private/Substrate/Substrate.ush` [SUBSTRATE_ENABLED], L40 `/Engine/Private/Substrate/SubstrateExport.ush` [SUBSTRATE_ENABLED && MATERIAL_IS_SUBSTRATE]

#### Macros (#define, 8)

- L3 `#define PATH_TRACING 1`
- L4 `#define ENABLE_SKY_LIGHT 1`
- L5 `#define NEEDS_LIGHTMAP_COORDINATE 0`
- L10 `#define NEEDS_VERTEX_FACTORY_INTERPOLATION 1`
- L13 `#define EYE_ADAPTATION_PREV_FRAME_EXPOSURE 1`
- L16 `#define SUBSTRATE_SSS_MATERIAL_OVERRIDE 0`
- L19 `#define MATERIAL_SUBSTRATE_OPAQUE_PRECOMPUTED_LIGHTING 0`
- L36 `#define SUBSTRATE_GPU_LIGHTMASS 1` _[#if SUBSTRATE_ENABLED]_
- L7 #undef `NEEDS_VERTEX_FACTORY_INTERPOLATION`

#### Entry points (2)

- L45-332 _entry_ `RAY_TRACING_ENTRY_CLOSEST_HIT(GPULightmassMaterialCHS, FPackedPathTracingPayload, PackedPayload, FRayTracingIntersectionAttributes, Attributes)` — stage: **closesthit** — C++: `FGPULightmassCHS` SF_RayHitGroup via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/PathTracing.cpp:3005) — C++: `FGPULightmassCHS_AHS` SF_RayHitGroup via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/PathTracing.cpp:3006)
- L336-493 _entry_ `RAY_TRACING_ENTRY_ANY_HIT(GPULightmassMaterialAHS, FPackedPathTracingPayload, PackedPayload, FRayTracingIntersectionAttributes, Attributes)` — stage: **anyhit** — C++: `FGPULightmassCHS_AHS` SF_RayHitGroup via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/PathTracing.cpp:3006) _[#if USE_MATERIAL_ANY_HIT_SHADER]_

### `Shaders/Private/PathTracing/PathTracingHeterogeneousVolumeMaterialShader.usf` (Private)

- lines: 274; parse: all-branches
- includes: L10 `/Engine/Private/Common.ush`, L11 `/Engine/Private/RayTracing/RayTracingCommon.ush`, L12 `/Engine/Private/PathTracing/PathTracingShaderUtils.ush`, L13 `/Engine/Private/PathTracing/Volume/PathTracingVolumeSampling.ush`, L14 `/Engine/Private/HeterogeneousVolumes/HeterogeneousVolumesTracingUtils.ush`, L15 `/Engine/Private/HeterogeneousVolumes/HeterogeneousVolumesVoxelGridTypes.ush`, L16 `/Engine/Private/HeterogeneousVolumes/HeterogeneousVolumesVoxelGridUtils.ush`, L17 `/Engine/Private/PathTracing/Volume/PathTracingVolumeCommon.ush`, L18 `/Engine/Private/PathTracing/Volume/PathTracingHeterogeneousVolumesForwardDecl.ush`, L19 `/Engine/Private/PathTracing/Volume/PathTracingHeterogeneousVolumesMaterialCommon.ush`, L20 `/Engine/Private/PathTracing/Volume/PathTracingHeterogeneousVolumesTrackingCommon.ush`, L21 `/Engine/Private/PathTracing/Volume/PathTracingHeterogeneousVolumesPreshadingCommon.ush`

#### Macros (#define, 5)

- L3 `#define PATH_TRACING 1`
- L4 `#define PATH_TRACER_USE_CLOUD_SHADER 1`
- L6 `#define USE_PRESHADED_UNIFORM_BUFFER 1`
- L7 `#define USE_CALLABLE_SHADERS 1`
- L8 `#define USE_MULTIPLE_VOLUMES 1`

#### Entry points (6)

- L23-26 _entry_ `RAY_TRACING_ENTRY_CALLABLE(PathTracingHeterogeneousVolumeMaterialShader, FPackedPathTracingPayload, PackedPayload)` — stage: **callable**
- L28-151 _entry_ `RAY_TRACING_ENTRY_CALLABLE(PathTracingHeterogeneousVolumesIntersectCS, FPackedPathTracingPayload, PackedPayload)` — stage: **callable** — C++: `FPathTracingHeterogeneousVolumesIntersectCS` SF_RayCallable via IMPLEMENT_SHADER_TYPE (Source/Runtime/Renderer/Private/PathTracing.cpp:2054)
- L153-156 _entry_ `RAY_TRACING_ENTRY_CALLABLE(PathTracingHeterogeneousVolumesGetDensityBoundsCS, FPackedPathTracingPayload, PackedPayload)` — stage: **callable** — C++: `FPathTracingHeterogeneousVolumesGetDensityBoundsCS` SF_RayCallable via IMPLEMENT_SHADER_TYPE (Source/Runtime/Renderer/Private/PathTracing.cpp:2055)
- L176-190 _entry_ `RAY_TRACING_ENTRY_CALLABLE(PathTracingHeterogeneousVolumesGetDensityCS, FPackedPathTracingPayload, PackedPayload)` — stage: **callable** — C++: `FPathTracingHeterogeneousVolumesGetDensityCS` SF_RayCallable via IMPLEMENT_SHADER_TYPE (Source/Runtime/Renderer/Private/PathTracing.cpp:2056)
- L192-248 _entry_ `RAY_TRACING_ENTRY_CALLABLE(PathTracingHeterogeneousVolumesSampleDistanceCS, FPackedPathTracingPayload, PackedPayload)` — stage: **callable** — C++: `FPathTracingHeterogeneousVolumesSampleDistanceCS` SF_RayCallable via IMPLEMENT_SHADER_TYPE (Source/Runtime/Renderer/Private/PathTracing.cpp:2057)
- L250-273 _entry_ `RAY_TRACING_ENTRY_CALLABLE(PathTracingHeterogeneousVolumesGetTransmittanceCS, FPackedPathTracingPayload, PackedPayload)` — stage: **callable** — C++: `FPathTracingHeterogeneousVolumesGetTransmittanceCS` SF_RayCallable via IMPLEMENT_SHADER_TYPE (Source/Runtime/Renderer/Private/PathTracing.cpp:2058)

#### Functions (1)

- L159-174 _function_ `FVolumeShadedResult HeterogeneousVolumesGetDensity(float3 TranslatedWorldPos, int HeterogeneousVolumesIndex)` — Specialize GetDensity() to locally fetch from the preshaded volume

### `Shaders/Private/PathTracing/PathTracingInitExtinctionCoefficient.usf` (Private)

- lines: 84; parse: all-branches
- includes: L3 `../Common.ush`, L4 `PathTracingCommon.ush`

#### Entry points (1)

- L9-83 _entry_ `RAY_TRACING_ENTRY_RAYGEN(PathTracingInitExtinctionCoefficientRG)` — stage: **raygeneration** — C++: `FPathTracingInitExtinctionCoefficientRG` SF_RayGen via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PathTracing.cpp:1718)

#### Global resources (textures / buffers / samplers) (2)

- L6 _resource_ `RaytracingAccelerationStructure TLAS;`
- L7 _resource_ `RWBuffer<float> RWStartingMediumData;`

### `Shaders/Private/PathTracing/PathTracingLightingMissShader.usf` (Private)

- lines: 36; parse: all-branches
- includes: L5 `PathTracingCommon.ush`, L6 `PathTracingShaderUtils.ush`, L10 `/Engine/Generated/Material.ush`, L16 `../LightFunctionCommon.ush`, L17 `../RayTracing/RayTracingLightFunctionCommon.ush`

#### Macros (#define, 5)

- L3 `#define PATH_TRACING 1`
- L8 `#define CameraRelativeLightPosition PathTracingLightFunctionParameters.CameraRelativeLightPosition`
- L13 `#define LightFunctionParameters PathTracingLightFunctionParameters.LightFunctionParameters`
- L14 `#define LightFunctionParameters2 PathTracingLightFunctionParameters.LightFunctionParameters2`
- L15 `#define LightFunctionTranslatedWorldToLight PathTracingLightFunctionParameters.LightFunctionTranslatedWorldToLight`

#### Entry points (1)

- L19-35 _entry_ `RAY_TRACING_ENTRY_MISS(PathTracingLightingMS, FPackedPathTracingPayload, Payload)` — stage: **miss** — C++: `FPathTracingLightingMS` SF_RayMiss via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/PathTracing.cpp:2751)

### `Shaders/Private/PathTracing/PathTracingMaterialHitShader.usf` (Private)

- lines: 1714; parse: all-branches
- includes: L34 `/Engine/Private/Common.ush`, L35 `/Engine/Private/RayTracing/RayTracingCommon.ush`, L36 `/Engine/Private/RayTracing/RayTracingHitGroupCommon.ush`, L37 `/Engine/Private/PathTracing/PathTracingShaderUtils.ush`, L38 `/Engine/Private/PathTracing/Utilities/PathTracingRIS.ush`, L39 `/Engine/Generated/Material.ush`, L40 `/Engine/Generated/VertexFactory.ush`, L42 `/Engine/Private/RayTracing/RayTracingCalcInterpolants.ush`, L43 `/Engine/Private/ShadingCommon.ush`, L44 `/Engine/Private/DeferredShadingCommon.ush`, L45 `/Engine/Private/SubsurfaceProfileCommon.ush`, L46 `/Engine/Private/BurleyNormalizedSSSCommon.ush`, L47 `/Engine/Private/ParticipatingMediaCommon.ush`, L48 `/Engine/Private/PathTracing/PathTracingCommon.ush`, L49 `/Engine/Private/PathTracing/Material/PathTracingFresnel.ush`, L65 `/Engine/Private/Substrate/SubstrateExport.ush` [(SUBSTRATE_ENABLED && TEMPLATE_USES_SUBSTRATE) \|\| USE_LEGACY_CODEPATH_FOR_SUBSTRATE], L66 `/Engine/Private/PathTracing/Material/PathTracingSubstrateCommon.ush` [(SUBSTRATE_ENABLED && TEMPLATE_USES_SUBSTRATE) \|\| USE_LEGACY_CODEPATH_FOR_SUBSTRATE]

#### Macros (#define, 19)

- L3 `#define PATH_TRACING 1`
- L4 `#define ENABLE_SKY_LIGHT 1`
- L5 `#define NEEDS_LIGHTMAP_COORDINATE 0`
- L10 `#define USE_SSS_PROFILE_ANISOTROPY 0`
- L16 `#define NEEDS_VERTEX_FACTORY_INTERPOLATION 1`
- L19 `#define EYE_ADAPTATION_PREV_FRAME_EXPOSURE 1`
- L22 `#define SUBSTRATE_SSS_MATERIAL_OVERRIDE 0`
- L28 `#define SUBSTRATE_INLINE_SHADING 1` _[#if (SUBSTRATE_ENABLED && !TEMPLATE_USES_SUBSTRATE)]_
- L32 `#define USE_ANALYTIC_DERIVATIVES 1`
- L58 `#define USE_LEGACY_CODEPATH_FOR_SUBSTRATE 1` _[#if SUBSTRATE_ENABLED && (TEMPLATE_USES_LEGACYGBUFFERDATA \|\| MATERIAL_IS_SUBSTRATEHIDDENCONVERSION)]_
- L60 `#define USE_LEGACY_CODEPATH_FOR_SUBSTRATE 0` _[#if !(SUBSTRATE_ENABLED && (TEMPLATE_USES_LEGACYGBUFFERDATA \|\| MATERIAL_IS_SUBSTRATEHIDDENCONVERSION))]_
- L64 `#define MATERIAL_SUBSTRATE_OPAQUE_PRECOMPUTED_LIGHTING 0` _[#if (SUBSTRATE_ENABLED && TEMPLATE_USES_SUBSTRATE) \|\| USE_LEGACY_CODEPATH_FOR_SUBSTRATE]_
- L79 `#define PATH_TRACER_USE_SUBSTRATE_GLASS_LOBE (MATERIALBLENDING_TRANSLUCENT && (SUBSTRATE_BLENDING_TRANSLUCENT_GREYTRANSMITTANCE \|\| SUBSTRATE_BLENDING_TRANSLUCENT_COLOREDTRANSMITTANCE))`
- L82 `#define PATH_TRACER_USE_VOLUMETRIC_SHADING_MODEL (TRANSLUCENCY_LIGHTING_SURFACE_LIGHTINGVOLUME \|\| TRANSLUCENCY_LIGHTING_VOLUMETRIC_PERVERTEX_NONDIRECTIONAL \|\| TRANSLUCENCY_LIGHTING_VOLUMETRIC_PERVERTEX_DIRECTIONAL \|\| TRANSLUCENCY_LIGHTING_VOLUMETRIC ...`
- L83 `#define PATH_TRACER_USE_VOLUMETRIC_SHADING_MODEL_DIRECTIONAL (TRANSLUCENCY_LIGHTING_SURFACE_LIGHTINGVOLUME \|\| TRANSLUCENCY_LIGHTING_VOLUMETRIC_PERVERTEX_DIRECTIONAL \|\| TRANSLUCENCY_LIGHTING_VOLUMETRIC_DIRECTIONAL)`
- L87 `#define PATH_TRACER_REFRACTION_ENABLED 1` _[#if REFRACTION_USE_INDEX_OF_REFRACTION \|\| REFRACTION_USE_INDEX_OF_REFRACTION_FROM_F0]_
- L149 `#define PATH_TRACER_REFRACTION_ENABLED 0` _[#if !(REFRACTION_USE_INDEX_OF_REFRACTION \|\| REFRACTION_USE_INDEX_OF_REFRACTION_FROM_F0)]_
- L381 `#define BSDF SubstratePixelHeader.SubstrateTree.BSDFs[BSDFIdx]` _[#if SUBSTRATE_ENABLED && !USE_LEGACY_CODEPATH_FOR_SUBSTRATE]_
- L1486 `#define BSDF SubstratePixelHeader.SubstrateTree.BSDFs[BSDFIdx]` _[#if USE_MATERIAL_ANY_HIT_SHADER && MATERIALBLENDING_MODULATE \|\| (MATERIALBLENDING_MASKED && MATERIAL_DITHER_OPACITY_MASK) \|\| MATERIALBLENDING_ALPHACOMPOSITE \|\| MATERIALBLENDING_TRANSLUCENT && SUBSTRATE...]_
- L13 #undef `NEEDS_VERTEX_FACTORY_INTERPOLATION`; L835 #undef `BSDF`; L1555 #undef `BSDF`

#### Entry points (2)

- L187-1378 _entry_ `RAY_TRACING_ENTRY_CLOSEST_HIT(PathTracingMaterialCHS, FPackedPathTracingPayload, PackedPayload, FRayTracingIntersectionAttributes, Attributes)` — stage: **closesthit** — C++: `FPathTracingMaterialCHS` SF_RayHitGroup via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/PathTracing.cpp:2996) — C++: `FPathTracingMaterialCHS_AHS` SF_RayHitGroup via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/PathTracing.cpp:2997) — C++: `FPathTracingMaterialCHS_IS` SF_RayHitGroup via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/PathTracing.cpp:2998) — C++: `FPathTracingMaterialCHS_AHS_IS` SF_RayHitGroup via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/PathTracing.cpp:2999) — C++: `FPathTracingMaterialSimplifiedCHS` SF_RayHitGroup via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/PathTracing.cpp:3000) — C++: `FPathTracingMaterialSimplifiedCHS_AHS` SF_RayHitGroup via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/PathTracing.cpp:3001) — C++: `FPathTracingMaterialSimplifiedCHS_IS` SF_RayHitGroup via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/PathTracing.cpp:3002) — C++: `FPathTracingMaterialSimplifiedCHS_AHS_IS` SF_RayHitGroup via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/PathTracing.cpp:3003)
- L1382-1711 _entry_ `RAY_TRACING_ENTRY_ANY_HIT(PathTracingMaterialAHS, FPackedPathTracingPayload, PackedPayload, FRayTracingIntersectionAttributes, Attributes)` — stage: **anyhit** — C++: `FPathTracingMaterialCHS_AHS` SF_RayHitGroup via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/PathTracing.cpp:2997) — C++: `FPathTracingMaterialCHS_AHS_IS` SF_RayHitGroup via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/PathTracing.cpp:2999) — C++: `FPathTracingMaterialSimplifiedCHS_AHS` SF_RayHitGroup via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/PathTracing.cpp:3001) — C++: `FPathTracingMaterialSimplifiedCHS_AHS_IS` SF_RayHitGroup via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/PathTracing.cpp:3003) _[#if USE_MATERIAL_ANY_HIT_SHADER]_

#### Functions (9)

- L69-77 _function_ `float AdjustMaterialRoughness(float Roughness, float PathRoughness)`
- L89-97 _function_ `float GetRefractionIor(FPixelMaterialInputs PixelMaterialInputs, float3 F0)` _[#if REFRACTION_USE_INDEX_OF_REFRACTION \|\| REFRACTION_USE_INDEX_OF_REFRACTION_FROM_F0]_
- L99-111 _function_ `float GetRefractionIor(FPixelMaterialInputs PixelMaterialInputs)` _[#if REFRACTION_USE_INDEX_OF_REFRACTION \|\| REFRACTION_USE_INDEX_OF_REFRACTION_FROM_F0]_
- L113-123 _function_ `float FakeCausticsPathFactor(float Roughness, float PathRoughness)` _[#if REFRACTION_USE_INDEX_OF_REFRACTION \|\| REFRACTION_USE_INDEX_OF_REFRACTION_FROM_F0]_
- L125-130 _function_ `float FakeCaustics(float F0, float Ior, float NoV)` _[#if REFRACTION_USE_INDEX_OF_REFRACTION \|\| REFRACTION_USE_INDEX_OF_REFRACTION_FROM_F0]_
- L132-145 _function_ `float3 ComputeOpticalDepthForHit(float3 LocalSigmaT, bool bIsFrontFace)` _[#if REFRACTION_USE_INDEX_OF_REFRACTION \|\| REFRACTION_USE_INDEX_OF_REFRACTION_FROM_F0]_
- L152-165 _function_ `float3 DecodeSSSProfileRadius(uint ProfileId, float3 DiffuseColor, float Opacity)`
- L167-171 _function_ `float DecodeSSSProfileScatteringDistribution(uint ProfileId)`
- L175-183 _function_ `float3 GetSimpleVolumeDiffuseColor(float3 DiffuseColor, float3 MeanFreePath)` _[#if SUBSTRATE_ENABLED]_

#### C++ shader bindings (IMPLEMENT_* naming this file, 4)

- `MaterialIS` → entry not found in file (macro-generated or #include'd); C++ `FPathTracingMaterialCHS_IS` SF_RayHitGroup via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/PathTracing.cpp:2998)
- `MaterialIS` → entry not found in file (macro-generated or #include'd); C++ `FPathTracingMaterialCHS_AHS_IS` SF_RayHitGroup via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/PathTracing.cpp:2999)
- `MaterialIS` → entry not found in file (macro-generated or #include'd); C++ `FPathTracingMaterialSimplifiedCHS_IS` SF_RayHitGroup via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/PathTracing.cpp:3002)
- `MaterialIS` → entry not found in file (macro-generated or #include'd); C++ `FPathTracingMaterialSimplifiedCHS_AHS_IS` SF_RayHitGroup via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/PathTracing.cpp:3003)

### `Shaders/Private/PathTracing/PathTracingMissShader.usf` (Private)

- lines: 10; parse: all-branches
- includes: L3 `PathTracingCommon.ush`

#### Entry points (1)

- L5-9 _entry_ `RAY_TRACING_ENTRY_MISS(PathTracingDefaultMS, FPackedPathTracingPayload, Payload)` — stage: **miss** — C++: `FPathTracingDefaultMS` SF_RayMiss via IMPLEMENT_SHADER_TYPE (Source/Runtime/Renderer/Private/PathTracing.cpp:2627) — C++: `FGPULightmassDefaultMS` SF_RayMiss via IMPLEMENT_SHADER_TYPE (Source/Runtime/Renderer/Private/PathTracing.cpp:2628)

### `Shaders/Private/PathTracing/PathTracingShaderUtils.ush` (Private)

- lines: 57; parse: all-branches
- includes: L11 `PathTracingCommon.ush`
- L3 #pragma `once`

#### static variables (1)

- L24 _static_var_ `static int CurrentPayloadInputFlags = 0;` — Use a global variable for convenience. This must be set prior to running the generated material code.

#### Functions (7)

- L13-21 _function_ `bool GetPathTracingQualitySwitch()`
- L25-28 _function_ `bool GetPathTracingIsShadow()`
- L30-33 _function_ `bool GetPathTracingIsIndirectDiffuse()`
- L35-38 _function_ `bool GetPathTracingIsIndirectSpecular()`
- L40-43 _function_ `bool GetPathTracingIsIndirectVolume()`
- L47-50 _function_ `bool GetShadowReplaceState()` — In the CHS/AHS case, also define these (which will be missing from Common.ush) _[#if RAYHITGROUPSHADER]_
- L52-55 _function_ `float IsShadowDepthShader()` _[#if RAYHITGROUPSHADER]_

### `Shaders/Private/PathTracing/PathTracingSkylightMISCompensation.usf` (Private)

- lines: 24; parse: all-branches
- includes: L3 `../Common.ush`

#### Entry points (1)

- L10-23 _entry_ `[numthreads(THREADGROUPSIZE_X, THREADGROUPSIZE_Y, 1)] void PathTracingSkylightMISCompensationCS(uint2 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FPathTracingSkylightMISCompensationCS` SF_Compute via IMPLEMENT_SHADER_TYPE (Source/Runtime/Renderer/Private/PathTracing.cpp:1224)

#### Global resources (textures / buffers / samplers) (3)

- L5 _resource_ `Texture2D<float> SkylightTexturePdfAverage;`
- L6 _resource_ `RWTexture2D<float4> SkylightTextureOutput;`
- L7 _resource_ `RWTexture2D<float> SkylightTexturePdf;`

### `Shaders/Private/PathTracing/PathTracingSkylightPrepare.usf` (Private)

- lines: 37; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../MonteCarlo.ush`

#### Entry points (1)

- L17-36 _entry_ `[numthreads(THREADGROUPSIZE_X, THREADGROUPSIZE_Y, 1)] void PathTracingSkylightPrepareCS(uint2 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FPathTracingSkylightPrepareCS` SF_Compute via IMPLEMENT_SHADER_TYPE (Source/Runtime/Renderer/Private/PathTracing.cpp:1196)

#### Global resources (textures / buffers / samplers) (6)

- L6 _resource_ `TextureCube SkyLightCubemap0;`
- L7 _resource_ `TextureCube SkyLightCubemap1;`
- L8 _resource_ `SamplerState SkyLightCubemapSampler0;`
- L9 _resource_ `SamplerState SkyLightCubemapSampler1;`
- L13 _resource_ `RWTexture2D<float4> SkylightTextureOutput;`
- L14 _resource_ `RWTexture2D<float> SkylightTexturePdf;`

#### Global parameters (uniforms) (3)

- L10 _parameter_ `float SkylightBlendFactor;`
- L11 _parameter_ `float SkylightInvResolution;`
- L15 _parameter_ `float3 SkyColor;`

### `Shaders/Private/PathTracing/PathTracingSpatialTemporalDenoising.usf` (Private)

- lines: 1600; parse: all-branches
- includes: L8 `/Engine/Public/Platform.ush`, L9 `../ScreenPass.ush`, L10 `../../Private/Common.ush`, L11 `../TextureSampling.ush`, L12 `../ColorDifference.ush`

#### Macros (#define, 48)

- L15 `#define THREAD_SIZE 8` _[#if !defined(THREAD_SIZE)]_
- L16 `#define THREAD_SIZE_X THREAD_SIZE` _[#if !defined(THREAD_SIZE)]_
- L17 `#define THREAD_SIZE_Y THREAD_SIZE` _[#if !defined(THREAD_SIZE)]_
- L21 `#define TEMPORAL_REPROJECTION_ALIGN 0` _[#if !defined(TEMPORAL_REPROJECTION_ALIGN)]_
- L25 `#define TEMPORAL_REPROJECTION_BLUR 0` _[#if !defined(TEMPORAL_REPROJECTION_BLUR)]_
- L26 `#define DIRECT_COPY 0` _[#if !defined(TEMPORAL_REPROJECTION_BLUR)]_
- L30 `#define TEMPORAL_REPROJECTION_MERGE 0` _[#if !defined(TEMPORAL_REPROJECTION_MERGE)]_
- L34 `#define TEMPORAL_REPROJECTION_RESOLVE 0` _[#if !defined(TEMPORAL_REPROJECTION_RESOLVE)]_
- L38 `#define TEMPORAL_FEATURE_FUSION 0` _[#if !defined(TEMPORAL_FEATURE_FUSION)]_
- L42 `#define RADIANCE_MULTI_CHANNEL 0`
- L43 `#define RADIANCE_ALBEDO_NORMAL_SINGLECHANNEL 1`
- L46 `#define TEMPORAL_PREPASS 0` _[#if !defined(TEMPORAL_PREPASS)]_
- L47 `#define VARIANCE_TYPE RADIANCE_MULTI_CHANNEL` _[#if !defined(TEMPORAL_PREPASS)]_
- L50 `#define PREPASS_PHASE_INIT 0`
- L51 `#define PREPASS_PHASE_UPDATE 1`
- L54 `#define RANKED_LUMINANCE_VARIANCE 0` _[#if !defined(RANKED_LUMINANCE_VARIANCE)]_
- L58 `#define SPATIAL_DENOISING 0` _[#if !defined(SPATIAL_DENOISING)]_
- L62 `#define PREPASS_GENERATE_TEXTURE 0` _[#if !defined(PREPASS_GENERATE_TEXTURE)]_
- L66 `#define VISUALIZE_MOTIONVECTOR 0` _[#if !defined(VISUALIZE_MOTIONVECTOR)]_
- L70 `#define MOTION_VECTOR_SUBTRACT 0` _[#if !defined(MOTION_VECTOR_SUBTRACT)]_
- L74 `#define TEMPORAL_HIGHFREQ_REJECT 0` _[#if !defined(TEMPORAL_HIGHFREQ_REJECT)]_
- L78 `#define VISUALIZE_WARPING 0` _[#if !defined(VISUALIZE_WARPING)]_
- L82 `#define TOTAL_VARIATION 0` _[#if !defined(TOTAL_VARIATION)]_
- L86 `#define PREPROCESS_BUFFER 0` _[#if !defined(PREPROCESS_BUFFER)]_
- L90 `#define METRICS_LUMINANCE 0`
- L91 `#define METRICS_EUCLIDEAN 1`
- L92 `#define METRICS_PERCEPTION 2`
- L95 `#define DISTANCE_METRICS METRICS_LUMINANCE` _[#if !defined(DISTANCE_METRICS)]_
- L100 `#define APPLY_SIMPLIFIED_GAMMA (DISTANCE_METRICS == METRICS_EUCLIDEAN \|\| DISTANCE_METRICS == METRICS_LUMINANCE)` (2 lines)
- L104 `#define K_NUM_OF_TEXTURES_PER_PASS 7` _[#if !defined(K_NUM_OF_TEXTURES_PER_PASS)]_
- L108 `#define K_NUM_OF_SHIFTS_PER_SLICE 4` _[#if !defined(K_NUM_OF_SHIFTS_PER_SLICE)]_
- L112 `#define MIP_DIFF_DELTA 2`
- L119 `#define DISTANCE_L1 0`
- L120 `#define DISTANCE_L2 1`
- L121 `#define DISTANCE_LOG_L1 2`
- L122 `#define DISTANCE_LOG_REGULARIZED_L1 3`
- L123 `#define DISTANCE_TYPE DISTANCE_LOG_REGULARIZED_L1`
- L318 `#define ESTIMATE_SUBPIXELOFFSET SUBPIXEL_OFFSET` _[#if K_NUM_OF_TEXTURES_PER_PASS <= 7 && (TEMPORAL_REPROJECTION_ALIGN\|\|TEMPORAL_REPROJECTION_MERGE)]_
- L410 `#define MAX_HEAP_SIZE 4` _[#if K_NUM_OF_TEXTURES_PER_PASS <= 7 && (TEMPORAL_REPROJECTION_ALIGN\|\|TEMPORAL_REPROJECTION_MERGE)]_
- L660 `#define NormalizeDeltaE2000(X) (NormalizeDeltaEAndEuclideanDistanceToSameMean*X)`
- L944 `#define SOURCE(x) x##_0[Position]` _[#if TEMPORAL_FEATURE_FUSION]_
- L945 `#define TARGET(x) x##_1[Position]` _[#if TEMPORAL_FEATURE_FUSION]_
- L947 `#define SOURCE_BUFFER(B) B##_0[Position.x+int(Position.y*TargetViewport_Extent.x)]` _[#if TEMPORAL_FEATURE_FUSION]_
- L948 `#define TARGET_BUFFER(B) B##_1[Position.x+int(Position.y*TargetViewport_Extent.x)]` _[#if TEMPORAL_FEATURE_FUSION]_
- L1396 `#define VISUALIZE_VECTOR 1` _[#if VISUALIZE_MOTIONVECTOR]_
- L1397 `#define VISUALIZE_COLOR_ENCODING 1` _[#if VISUALIZE_MOTIONVECTOR]_
- L1398 `#define VECTOR_GRID_LENGTH 32` _[#if VISUALIZE_MOTIONVECTOR]_
- L1399 `#define COLOR_METER_LENGTH 50` _[#if VISUALIZE_MOTIONVECTOR]_
- L6 #pragma `once`

#### Entry points (13)

- L861-893 _entry_ `[numthreads(THREAD_SIZE_X, THREAD_SIZE_Y, 1)] void TemporalPrepassCS(uint3 DT_ID : SV_DispatchThreadID)` — stage: **compute** — C++: `FTemporalPrepassCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PathTracingSpatialTemporalDenoising.cpp:1866) _[#if TEMPORAL_PREPASS]_
- L901-917 _entry_ `[numthreads(THREAD_SIZE_X, THREAD_SIZE_Y, 1)] void PrepassGenerateTextureCS(uint3 DT_ID : SV_DispatchThreadID)` — stage: **compute** — C++: `FPrepassGenerateTextureCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PathTracingSpatialTemporalDenoising.cpp:1895) _[#if PREPASS_GENERATE_TEXTURE]_
- L981-991 _entry_ `[numthreads(THREAD_SIZE_X, THREAD_SIZE_Y, 1)] void TemporalFeatureFusionCS(uint3 DT_ID : SV_DispatchThreadID)` — stage: **compute** — C++: `FTemporalFeatureFusionCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PathTracingSpatialTemporalDenoising.cpp:938) _[#if TEMPORAL_FEATURE_FUSION]_
- L997-1028 _entry_ `[numthreads(THREAD_SIZE_X, THREAD_SIZE_Y, 1)] void ReprojectionAlignCS(uint3 DT_ID : SV_DispatchThreadID)` — stage: **compute** — C++: `FTemporalReprojectionAlignCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PathTracingSpatialTemporalDenoising.cpp:779) _[#if TEMPORAL_REPROJECTION_ALIGN]_
- L1091-1102 _entry_ `[numthreads(THREAD_SIZE_X, THREAD_SIZE_Y, 1)] void ReprojectionBlurCS(uint3 DT_ID : SV_DispatchThreadID)` — stage: **compute** — C++: `FTemporalReprojectionBlurCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PathTracingSpatialTemporalDenoising.cpp:808) _[#if TEMPORAL_REPROJECTION_BLUR]_
- L1129-1173 _entry_ `[numthreads(THREAD_SIZE_X, THREAD_SIZE_Y, 1)] void ReprojectionMergeCS(uint3 DT_ID : SV_DispatchThreadID)` — stage: **compute** — C++: `FTemporalReprojectionMergeCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PathTracingSpatialTemporalDenoising.cpp:841) _[#if TEMPORAL_REPROJECTION_MERGE]_
- L1181-1213 _entry_ `[numthreads(THREAD_SIZE_X, THREAD_SIZE_Y, 1)] void TemporalHighFrequencyRejectCS(uint3 DT_ID : SV_DispatchThreadID)` — stage: **compute** — C++: `FTemporalHighFrequencyRejectMapCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PathTracingSpatialTemporalDenoising.cpp:897) _[#if TEMPORAL_HIGHFREQ_REJECT]_
- L1227-1290 _entry_ `[numthreads(THREAD_SIZE_X, THREAD_SIZE_Y, 1)] void TemporalResolveCS(uint3 DT_ID : SV_DispatchThreadID)` — stage: **compute** — C++: `FTemporalResolveCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PathTracingSpatialTemporalDenoising.cpp:973) _[#if TEMPORAL_REPROJECTION_RESOLVE]_
- L1307-1329 _entry_ `[numthreads(THREAD_SIZE_X, THREAD_SIZE_Y, 1)] void MotionVectorSubtractCS(uint3 DT_ID : SV_DispatchThreadID)` — stage: **compute** — C++: `FMotionVectorSubtractCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PathTracingSpatialTemporalDenoising.cpp:867) _[#if MOTION_VECTOR_SUBTRACT]_
- L1401-1533 _entry_ `void VisualizePathTracingMotionVector( in noperspective float2 UV : TEXCOORD0, out float4 OutColor : SV_Target0 )` — stage: **pixel (from C++ binding)** — C++: `FVisualizePathTracingMotionVectorPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PathTracingSpatialTemporalDenoising.cpp:2152) _[#if VISUALIZE_MOTIONVECTOR]_
- L1544-1560 _entry_ `void FVisualizeWarpingPS( in noperspective float2 UV : TEXCOORD0, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FVisualizeWarpingPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PathTracingSpatialTemporalDenoising.cpp:2184) _[#if VISUALIZE_WARPING]_
- L1570-1579 _entry_ `[numthreads(THREAD_SIZE_X, THREAD_SIZE_Y, 1)] void SpatialDenoiserCS(uint3 DT_ID : SV_DispatchThreadID)` — stage: **compute** — C++: `FSpatialDenoiserCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PathTracingSpatialTemporalDenoising.cpp:1001) _[#if SPATIAL_DENOISING]_
- L1588-1598 _entry_ `[numthreads(THREAD_SIZE_X, THREAD_SIZE_Y, 1)] void ConvertWorldSpaceNormalToCameraSpaceCS(uint3 DT_ID : SV_DispatchThreadID)` — stage: **compute** — C++: `FConvertWorldSpaceNormalToCameraSpaceCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PathTracingSpatialTemporalDenoising.cpp:1028) _[#if PREPROCESS_BUFFER]_

#### Structs / classes (5)

- L127-132 _struct_ **`FPixelOffset`** `struct FPixelOffset`
  - L129 _member_ `float2 xy;`
  - L130 _member_ `float Dist;`
  - L131 _member_ `float TV;`
- L134-138 _struct_ **`FPixelMaterialLightingFingerprint`** `struct FPixelMaterialLightingFingerprint`
  - L136 _member_ `float4 Mean;`
  - L137 _member_ `float4 Var;`
- L265-269 _struct_ **`FQuadricFittingContext`** `struct FQuadricFittingContext` _[#if K_NUM_OF_TEXTURES_PER_PASS <= 7 && (TEMPORAL_REPROJECTION_ALIGN\|\|TEMPORAL_REPROJECTION_MERGE)]_
  - L267 _member_ `int2 Offset;` — integer shift of the minimal value _[#if K_NUM_OF_TEXTURES_PER_PASS <= 7 && (TEMPORAL_REPROJECTION_ALIGN\|\|TEMPORAL_REPROJECTION_MERGE)]_
  - L268 _member_ `float3x3 Values;` — holding the surrounding distance to fit a bivariate polynomial. _[#if K_NUM_OF_TEXTURES_PER_PASS <= 7 && (TEMPORAL_REPROJECTION_ALIGN\|\|TEMPORAL_REPROJECTION_MERGE)]_
- L281-286 _struct_ **`FFindMinContext`** `struct FFindMinContext` _[#if K_NUM_OF_TEXTURES_PER_PASS <= 7 && (TEMPORAL_REPROJECTION_ALIGN\|\|TEMPORAL_REPROJECTION_MERGE)]_
  - L283 _member_ `int TextureOffset;` _[#if K_NUM_OF_TEXTURES_PER_PASS <= 7 && (TEMPORAL_REPROJECTION_ALIGN\|\|TEMPORAL_REPROJECTION_MERGE)]_
  - L284 _member_ `int Index;` _[#if K_NUM_OF_TEXTURES_PER_PASS <= 7 && (TEMPORAL_REPROJECTION_ALIGN\|\|TEMPORAL_REPROJECTION_MERGE)]_
  - L285 _member_ `float Value;` _[#if K_NUM_OF_TEXTURES_PER_PASS <= 7 && (TEMPORAL_REPROJECTION_ALIGN\|\|TEMPORAL_REPROJECTION_MERGE)]_
- L416-420 _struct_ **`FMaxHeap`** `struct FMaxHeap` _[#if K_NUM_OF_TEXTURES_PER_PASS <= 7 && (TEMPORAL_REPROJECTION_ALIGN\|\|TEMPORAL_REPROJECTION_MERGE)]_
  - L418 _member_ `float Heap[MAX_HEAP_SIZE];` _[#if K_NUM_OF_TEXTURES_PER_PASS <= 7 && (TEMPORAL_REPROJECTION_ALIGN\|\|TEMPORAL_REPROJECTION_MERGE)]_
  - L419 _member_ `uint Index[MAX_HEAP_SIZE];` _[#if K_NUM_OF_TEXTURES_PER_PASS <= 7 && (TEMPORAL_REPROJECTION_ALIGN\|\|TEMPORAL_REPROJECTION_MERGE)]_

#### Global resources (textures / buffers / samplers) (56)

- L176 _resource_ `RWTexture2D<float4> RWDistanceTextures_0;` _[#if K_NUM_OF_TEXTURES_PER_PASS <= 7 && (TEMPORAL_REPROJECTION_ALIGN\|\|TEMPORAL_REPROJECTION_MERGE)]_
- L177 _resource_ `RWTexture2D<float4> RWDistanceTextures_1;` _[#if K_NUM_OF_TEXTURES_PER_PASS <= 7 && (TEMPORAL_REPROJECTION_ALIGN\|\|TEMPORAL_REPROJECTION_MERGE)]_
- L178 _resource_ `RWTexture2D<float4> RWDistanceTextures_2;` _[#if K_NUM_OF_TEXTURES_PER_PASS <= 7 && (TEMPORAL_REPROJECTION_ALIGN\|\|TEMPORAL_REPROJECTION_MERGE)]_
- L179 _resource_ `RWTexture2D<float4> RWDistanceTextures_3;` _[#if K_NUM_OF_TEXTURES_PER_PASS <= 7 && (TEMPORAL_REPROJECTION_ALIGN\|\|TEMPORAL_REPROJECTION_MERGE)]_
- L180 _resource_ `RWTexture2D<float4> RWDistanceTextures_4;` _[#if K_NUM_OF_TEXTURES_PER_PASS <= 7 && (TEMPORAL_REPROJECTION_ALIGN\|\|TEMPORAL_REPROJECTION_MERGE)]_
- L181 _resource_ `RWTexture2D<float4> RWDistanceTextures_5;` _[#if K_NUM_OF_TEXTURES_PER_PASS <= 7 && (TEMPORAL_REPROJECTION_ALIGN\|\|TEMPORAL_REPROJECTION_MERGE)]_
- L182 _resource_ `RWTexture2D<float4> RWDistanceTextures_6;` _[#if K_NUM_OF_TEXTURES_PER_PASS <= 7 && (TEMPORAL_REPROJECTION_ALIGN\|\|TEMPORAL_REPROJECTION_MERGE)]_
- L184 _resource_ `Texture2D<float4> DistanceTextures_0;` _[#if K_NUM_OF_TEXTURES_PER_PASS <= 7 && (TEMPORAL_REPROJECTION_ALIGN\|\|TEMPORAL_REPROJECTION_MERGE)]_
- L185 _resource_ `Texture2D<float4> DistanceTextures_1;` _[#if K_NUM_OF_TEXTURES_PER_PASS <= 7 && (TEMPORAL_REPROJECTION_ALIGN\|\|TEMPORAL_REPROJECTION_MERGE)]_
- L186 _resource_ `Texture2D<float4> DistanceTextures_2;` _[#if K_NUM_OF_TEXTURES_PER_PASS <= 7 && (TEMPORAL_REPROJECTION_ALIGN\|\|TEMPORAL_REPROJECTION_MERGE)]_
- L187 _resource_ `Texture2D<float4> DistanceTextures_3;` _[#if K_NUM_OF_TEXTURES_PER_PASS <= 7 && (TEMPORAL_REPROJECTION_ALIGN\|\|TEMPORAL_REPROJECTION_MERGE)]_
- L188 _resource_ `Texture2D<float4> DistanceTextures_4;` _[#if K_NUM_OF_TEXTURES_PER_PASS <= 7 && (TEMPORAL_REPROJECTION_ALIGN\|\|TEMPORAL_REPROJECTION_MERGE)]_
- L189 _resource_ `Texture2D<float4> DistanceTextures_5;` _[#if K_NUM_OF_TEXTURES_PER_PASS <= 7 && (TEMPORAL_REPROJECTION_ALIGN\|\|TEMPORAL_REPROJECTION_MERGE)]_
- L190 _resource_ `Texture2D<float4> DistanceTextures_6;` _[#if K_NUM_OF_TEXTURES_PER_PASS <= 7 && (TEMPORAL_REPROJECTION_ALIGN\|\|TEMPORAL_REPROJECTION_MERGE)]_
- L746 _resource_ `Texture2D<float4> PixelOffsetTexture;` _[#if TEMPORAL_REPROJECTION_ALIGN \|\| TEMPORAL_REPROJECTION_MERGE \|\| TEMPORAL_REPROJECTION_RESOLVE \|\| TEMPORAL_HIGHFREQ_REJECT]_
- L747 _resource_ `Texture2D<float4> SourceTexture;` _[#if TEMPORAL_REPROJECTION_ALIGN \|\| TEMPORAL_REPROJECTION_MERGE \|\| TEMPORAL_REPROJECTION_RESOLVE \|\| TEMPORAL_HIGHFREQ_REJECT]_
- L748 _resource_ `Texture2D<float4> TargetTexture;` _[#if TEMPORAL_REPROJECTION_ALIGN \|\| TEMPORAL_REPROJECTION_MERGE \|\| TEMPORAL_REPROJECTION_RESOLVE \|\| TEMPORAL_HIGHFREQ_REJECT]_
- L749 _resource_ `SamplerState SharedTextureSampler;` _[#if TEMPORAL_REPROJECTION_ALIGN \|\| TEMPORAL_REPROJECTION_MERGE \|\| TEMPORAL_REPROJECTION_RESOLVE \|\| TEMPORAL_HIGHFREQ_REJECT]_
- L805 _resource_ `Texture2D<float4> InputTexture;` _[#if TEMPORAL_PREPASS]_
- L806 _resource_ `Texture2D<float4> AlbedoTexture;` _[#if TEMPORAL_PREPASS]_
- L807 _resource_ `Texture2D<float4> NormalTexture;` _[#if TEMPORAL_PREPASS]_
- L808 _resource_ `RWStructuredBuffer<FPixelMaterialLightingFingerprint> RWVarianceMap;` _[#if TEMPORAL_PREPASS]_
- L897 _resource_ `RWTexture2D<float4> OutputTexture;` _[#if PREPASS_GENERATE_TEXTURE]_
- L898 _resource_ `StructuredBuffer<FPixelMaterialLightingFingerprint> VarianceMap;` _[#if PREPASS_GENERATE_TEXTURE]_
- L924 _resource_ `Texture2D<float4> AlbedoTexture_0;` _[#if TEMPORAL_FEATURE_FUSION]_
- L925 _resource_ `Texture2D<float4> AlbedoTexture_1;` _[#if TEMPORAL_FEATURE_FUSION]_
- L927 _resource_ `Texture2D<float4> NormalTexture_0;` _[#if TEMPORAL_FEATURE_FUSION]_
- L928 _resource_ `Texture2D<float4> NormalTexture_1;` _[#if TEMPORAL_FEATURE_FUSION]_
- L930 _resource_ `Texture2D<float4> RadianceTexture_0;` _[#if TEMPORAL_FEATURE_FUSION]_
- L931 _resource_ `Texture2D<float4> RadianceTexture_1;` _[#if TEMPORAL_FEATURE_FUSION]_
- L933 _resource_ `StructuredBuffer<FPixelMaterialLightingFingerprint> VarianceMap_0;` _[#if TEMPORAL_FEATURE_FUSION]_
- L934 _resource_ `StructuredBuffer<FPixelMaterialLightingFingerprint> VarianceMap_1;` _[#if TEMPORAL_FEATURE_FUSION]_
- L937 _resource_ `Texture2D<float4> LastDenoisedRadiance;` _[#if TEMPORAL_FEATURE_FUSION]_
- L939 _resource_ `SamplerState SharedTextureSampler;` _[#if TEMPORAL_FEATURE_FUSION]_
- L941 _resource_ `RWTexture2D<float4> OutputTexture_0;` _[#if TEMPORAL_FEATURE_FUSION]_
- L942 _resource_ `RWTexture2D<float4> OutputTexture_1;` _[#if TEMPORAL_FEATURE_FUSION]_
- L1033 _resource_ `Texture2D<float4> InputTexture;` — Previous accumulation _[#if TEMPORAL_REPROJECTION_BLUR]_
- L1034 _resource_ `RWTexture2D<float4> OutputTexture;` — new observation _[#if TEMPORAL_REPROJECTION_BLUR]_
- L1035 _resource_ `SamplerState SharedTextureSampler;` _[#if TEMPORAL_REPROJECTION_BLUR]_
- L1107 _resource_ `RWTexture2D<float4> RWPixelOffsetTexture;` _[#if TEMPORAL_REPROJECTION_MERGE]_
- L1178 _resource_ `RWTexture2D<float4> OutputTexture;` _[#if TEMPORAL_HIGHFREQ_REJECT]_
- L1218 _resource_ `Texture2D<float4> HighFrequencyRejectMap;` _[#if TEMPORAL_REPROJECTION_RESOLVE]_
- L1219 _resource_ `RWTexture2D<float4> OutputTexture;` _[#if TEMPORAL_REPROJECTION_RESOLVE]_
- L1303 _resource_ `RWTexture2D<float4> Minuend;` _[#if MOTION_VECTOR_SUBTRACT]_
- L1304 _resource_ `Texture2D<float4> Subtrahend;` _[#if MOTION_VECTOR_SUBTRACT]_
- L1393 _resource_ `Texture2D<float4> TemporalDenoisingMotionVector;` _[#if VISUALIZE_MOTIONVECTOR]_
- L1394 _resource_ `Texture2D<float4> DenoisedTexture;` _[#if VISUALIZE_MOTIONVECTOR]_
- L1539 _resource_ `Texture2D<float4> TemporalDenoisingMotionVector;` _[#if VISUALIZE_WARPING]_
- L1540 _resource_ `Texture2D<float4> DenoisedTexture;` _[#if VISUALIZE_WARPING]_
- L1541 _resource_ `Texture2D<float4> SourceTexture;` _[#if VISUALIZE_WARPING]_
- L1542 _resource_ `SamplerState SharedTextureSampler;` _[#if VISUALIZE_WARPING]_
- L1565 _resource_ `Texture2D<float4> InputTexture;` _[#if SPATIAL_DENOISING]_
- L1566 _resource_ `Texture2D<float4> InputNormal;` _[#if SPATIAL_DENOISING]_
- L1567 _resource_ `Texture2D<float4> InputAlbedo;` _[#if SPATIAL_DENOISING]_
- L1568 _resource_ `RWTexture2D<float4> OutputTexture;` _[#if SPATIAL_DENOISING]_
- L1584 _resource_ `RWTexture2D<float4> NormalTexture;` _[#if PREPROCESS_BUFFER]_

#### Global parameters (uniforms) (16)

- L750 _parameter_ `uint MipLevel;` _[#if TEMPORAL_REPROJECTION_ALIGN \|\| TEMPORAL_REPROJECTION_MERGE \|\| TEMPORAL_REPROJECTION_RESOLVE \|\| TEMPORAL_HIGHFREQ_REJECT]_
- L809 _parameter_ `int Iteration;` _[#if TEMPORAL_PREPASS]_
- L899 _parameter_ `int Iteration;` _[#if PREPASS_GENERATE_TEXTURE]_
- L1036 _parameter_ `uint MipLevel;` _[#if TEMPORAL_REPROJECTION_BLUR]_
- L1108 _parameter_ `uint PatchId;` _[#if TEMPORAL_REPROJECTION_MERGE]_
- L1109 _parameter_ `uint PatchCount;` _[#if TEMPORAL_REPROJECTION_MERGE]_
- L1179 _parameter_ `float HighFrequencyCutoffDeltaE;` _[#if TEMPORAL_HIGHFREQ_REJECT]_
- L1220 _parameter_ `float Alpha;` _[#if TEMPORAL_REPROJECTION_RESOLVE]_
- L1221 _parameter_ `float Kappa;` _[#if TEMPORAL_REPROJECTION_RESOLVE]_
- L1222 _parameter_ `float Eta;` _[#if TEMPORAL_REPROJECTION_RESOLVE]_
- L1223 _parameter_ `float HighFrequencyCutoffDeltaE;` _[#if TEMPORAL_REPROJECTION_RESOLVE]_
- L1224 _parameter_ `uint PatchId;` _[#if TEMPORAL_REPROJECTION_RESOLVE]_
- L1225 _parameter_ `uint PatchCount;` _[#if TEMPORAL_REPROJECTION_RESOLVE]_
- L1305 _parameter_ `uint MipLevel;` _[#if MOTION_VECTOR_SUBTRACT]_
- L1585 _parameter_ `float Width;` _[#if PREPROCESS_BUFFER]_
- L1586 _parameter_ `float Height;` _[#if PREPROCESS_BUFFER]_

#### static const (5)

- L329-331 _static_const_ `static const float FA11[9] = { 1.0f, -2.0f, 1.0f, 2.0f, -4.0f, 2.0f, 1.0f, -2.0f, 1.0f};` _[#if K_NUM_OF_TEXTURES_PER_PASS <= 7 && (TEMPORAL_REPROJECTION_ALIGN\|\|TEMPORAL_REPROJECTION_MERGE) && ESTIMATE_SUBPIXELOFFSET]_
- L333-335 _static_const_ `static const float FA22[9] = { 1.0f / 4.0f, 2.0f / 4.0f, 1.0f / 4.0f, -2.0f / 4.0f, -4.0f / 4.0f, -2.0f / 4.0f, 1.0f / 4.0f, 2.0f / 4.0f, 1.0f / 4.0f };` _[#if K_NUM_OF_TEXTURES_PER_PASS <= 7 && (TEMPORAL_REPROJECTION_ALIGN\|\|TEMPORAL_REPROJECTION_MERGE) && ESTIMATE_SUBPIXELOFFSET]_
- L338-340 _static_const_ `static const float FA12[9] = { 1.0f / 4.0f, 0.0f, -1.0f / 4.0f, 0.0f, 0.0f, 0.0f, -1.0f / 4.0f, 0.0f, 1.0f / 4.0f };` _[#if K_NUM_OF_TEXTURES_PER_PASS <= 7 && (TEMPORAL_REPROJECTION_ALIGN\|\|TEMPORAL_REPROJECTION_MERGE) && ESTIMATE_SUBPIXELOFFSET]_
- L342-344 _static_const_ `static const float FB1[9] = { -1.0f / 8.0f, 0.0f, 1.0f / 8.0f, -2.0f / 8.0f, 0.0f, 2.0f / 8.0f, -1.0f / 8.0f, 0.0f, 1.0f / 8.0f };` _[#if K_NUM_OF_TEXTURES_PER_PASS <= 7 && (TEMPORAL_REPROJECTION_ALIGN\|\|TEMPORAL_REPROJECTION_MERGE) && ESTIMATE_SUBPIXELOFFSET]_
- L346-348 _static_const_ `static const float FB2[9] = { -1.0f / 8.0f, -2.0f / 8.0f, -1.0f / 8.0f, 0.0f, 0.0f, 0.0f, 1.0f / 8.0f, 2.0f / 8.0f, 1.0f / 8.0f };` _[#if K_NUM_OF_TEXTURES_PER_PASS <= 7 && (TEMPORAL_REPROJECTION_ALIGN\|\|TEMPORAL_REPROJECTION_MERGE) && ESTIMATE_SUBPIXELOFFSET]_

#### static variables (2)

- L168-174 _static_var_ `static int2 Shifts[25] = { {-2,-2},{-1,-2},{0,-2},{1,-2},{2,-2}, {-2,-1},{-1,-1},{0,-1},{1,-1},{2,-1}, {-2, 0},{-1, 0},{0, 0},{1, 0},{2, 0}, {-2, 1},{-1, 1},{0, 1},{1, 1},{2, 1}, {-2, 2},{-1, 2},{0, 2},{1, 2},{2, 2}, };` _[#if K_NUM_OF_TEXTURES_PER_PASS <= 7 && (TEMPORAL_REPROJECTION_ALIGN\|\|TEMPORAL_REPROJECTION_MERGE)]_
- L659 _static_var_ `static float NormalizeDeltaEAndEuclideanDistanceToSameMean = 0.0141f;` — Error Normalization. to have a similar error level between euclidean e.g. for color C0 = (0.58f, 0.46f, 0.28f), C1 = (0.28f, 0.96f, 0.43f) the color difference of euclidean with gamma corrected D_eu_g D_eu_g(C0, C1) = 0.38f the color difference of DeltaE_CIE2000 has DeltaE(C0,C1)  = 27.71 To have the error on the same level, we multiply by 0.53f/ 37.85f = 1/70.78f, which is an experimental value of running 1e6 random pair of colors to get the mean of different measures where Mean_eu_g = 0.53f, Mean_DeltaE = 37.85f;

#### Functions (43)

- L140-144 _function_ `void Max3Index(in float3 Value, out int MaxIndex)`
- L146-151 _function_ `void Max3(in float3 Value, out float MaxValue, out int MaxIndex)`
- L153-157 _function_ `void Min3Index(in float3 Value, out int MinIndex)`
- L159-164 _function_ `void Min3(in float3 Value, out float MinValue, out int MinIndex)`
- L193-224 _function_ `void SaveOffsets(int2 Position, int BasePixelShift, float4 Value)` _[#if K_NUM_OF_TEXTURES_PER_PASS <= 7 && (TEMPORAL_REPROJECTION_ALIGN\|\|TEMPORAL_REPROJECTION_MERGE)]_
- L226-263 _function_ `float GetOffsets(int2 Position, int2 Offset)` _[#if K_NUM_OF_TEXTURES_PER_PASS <= 7 && (TEMPORAL_REPROJECTION_ALIGN\|\|TEMPORAL_REPROJECTION_MERGE)]_
- L271-274 _function_ `float Min3(float3 value)` _[#if K_NUM_OF_TEXTURES_PER_PASS <= 7 && (TEMPORAL_REPROJECTION_ALIGN\|\|TEMPORAL_REPROJECTION_MERGE)]_
- L276-279 _function_ `float Min4(float4 value)` _[#if K_NUM_OF_TEXTURES_PER_PASS <= 7 && (TEMPORAL_REPROJECTION_ALIGN\|\|TEMPORAL_REPROJECTION_MERGE)]_
- L288-294 _function_ `void Min4(in float4 Value, out float MinValue, out int MinIndex)` _[#if K_NUM_OF_TEXTURES_PER_PASS <= 7 && (TEMPORAL_REPROJECTION_ALIGN\|\|TEMPORAL_REPROJECTION_MERGE)]_
- L296-302 _function_ `void Max4(in float4 Value, out float MaxValue, out int MaxIndex)` _[#if K_NUM_OF_TEXTURES_PER_PASS <= 7 && (TEMPORAL_REPROJECTION_ALIGN\|\|TEMPORAL_REPROJECTION_MERGE)]_
- L304-316 _function_ `void UpdateMin4Index(int TextureOffset, float4 Value, inout FFindMinContext Context)` _[#if K_NUM_OF_TEXTURES_PER_PASS <= 7 && (TEMPORAL_REPROJECTION_ALIGN\|\|TEMPORAL_REPROJECTION_MERGE)]_
- L354-359 _function_ `float Dot9(float A[9], float B[9])` _[#if K_NUM_OF_TEXTURES_PER_PASS <= 7 && (TEMPORAL_REPROJECTION_ALIGN\|\|TEMPORAL_REPROJECTION_MERGE) && ESTIMATE_SUBPIXELOFFSET]_
- L363-407 _function_ `float2 EstimateSubpixelOffset(float3x3 D)` — D holds the 3x3 image distance. Return the subpixel offset in range [-1, 1] x [-1, 1] _[#if K_NUM_OF_TEXTURES_PER_PASS <= 7 && (TEMPORAL_REPROJECTION_ALIGN\|\|TEMPORAL_REPROJECTION_MERGE) && ESTIMATE_SUBPIXELOFFSET]_
- L422-434 _function_ `FMaxHeap CreateMaxHeap()` _[#if K_NUM_OF_TEXTURES_PER_PASS <= 7 && (TEMPORAL_REPROJECTION_ALIGN\|\|TEMPORAL_REPROJECTION_MERGE)]_
- L436-439 _function_ `float GetMax(in float Array[MAX_HEAP_SIZE])` _[#if K_NUM_OF_TEXTURES_PER_PASS <= 7 && (TEMPORAL_REPROJECTION_ALIGN\|\|TEMPORAL_REPROJECTION_MERGE)]_
- L441-446 _function_ `void _Swap(inout float Array[MAX_HEAP_SIZE], uint i, uint j)` _[#if K_NUM_OF_TEXTURES_PER_PASS <= 7 && (TEMPORAL_REPROJECTION_ALIGN\|\|TEMPORAL_REPROJECTION_MERGE)]_
- L448-453 _function_ `void _Swap(inout uint Array[MAX_HEAP_SIZE], uint i, uint j)` _[#if K_NUM_OF_TEXTURES_PER_PASS <= 7 && (TEMPORAL_REPROJECTION_ALIGN\|\|TEMPORAL_REPROJECTION_MERGE)]_
- L455-475 _function_ `void Insert(inout FMaxHeap MaxHeap, float Value, int Index)` _[#if K_NUM_OF_TEXTURES_PER_PASS <= 7 && (TEMPORAL_REPROJECTION_ALIGN\|\|TEMPORAL_REPROJECTION_MERGE)]_
- L477-484 _function_ `void Insert(inout FMaxHeap MaxHeap, float4 Values, int4 Indices)` _[#if K_NUM_OF_TEXTURES_PER_PASS <= 7 && (TEMPORAL_REPROJECTION_ALIGN\|\|TEMPORAL_REPROJECTION_MERGE)]_
- L486-515 _function_ `void Sort4(float Values[MAX_HEAP_SIZE], inout uint4 Indices)` _[#if K_NUM_OF_TEXTURES_PER_PASS <= 7 && (TEMPORAL_REPROJECTION_ALIGN\|\|TEMPORAL_REPROJECTION_MERGE)]_
- L518-588 _function_ `FQuadricFittingContext GetQuadricFittingContext(int2 Position, int kth = 0)` — based on the target position, and the shift from the last mip, we fetch _[#if K_NUM_OF_TEXTURES_PER_PASS <= 7 && (TEMPORAL_REPROJECTION_ALIGN\|\|TEMPORAL_REPROJECTION_MERGE)]_
- L590-620 _function_ `float GetTotalVariation(int2 Position, FQuadricFittingContext Context)` _[#if K_NUM_OF_TEXTURES_PER_PASS <= 7 && (TEMPORAL_REPROJECTION_ALIGN\|\|TEMPORAL_REPROJECTION_MERGE)]_
- L622-635 _function_ `FPixelOffset GetQuadricFittingOffset(FQuadricFittingContext Context)` _[#if K_NUM_OF_TEXTURES_PER_PASS <= 7 && (TEMPORAL_REPROJECTION_ALIGN\|\|TEMPORAL_REPROJECTION_MERGE)]_
- L639-642 _function_ `int2 GetShiftedPosition(int2 Position, int2 Shift)`
- L644-647 _function_ `float2 GetBufferUVFromPosition(float2 Position, int MipLevel)`
- L663-677 _function_ `float GetDeltaE(float3 LinearRGB0, float3 LinearRGB1, bool bNormalizeToEuclideanMean = true)` — rgb is in linear space
- L679-695 _function_ `float GetDistance(float LumA, float LumB, int2 shift)`
- L697-700 _function_ `float GetFinalMipDistance(float LumA, float LumB, int2 shift)`
- L702-721 _function_ `float GetDistance(float3 A, float3 B, int2 shift)`
- L723-742 _function_ `float GetFinalMipDistance(float3 A, float3 B, int2 shift)`
- L752-784 _function_ `FPixelOffset GetPixelOffsetFromLowerMip(float2 Position, uint MipDiff)` _[#if TEMPORAL_REPROJECTION_ALIGN \|\| TEMPORAL_REPROJECTION_MERGE \|\| TEMPORAL_REPROJECTION_RESOLVE \|\| TEMPORAL_HIGHFREQ_REJECT]_
- L786-790 _function_ `float3 GetTextureValue(Texture2D Tex, float2 Position)` _[#if TEMPORAL_REPROJECTION_ALIGN \|\| TEMPORAL_REPROJECTION_MERGE \|\| TEMPORAL_REPROJECTION_RESOLVE \|\| TEMPORAL_HIGHFREQ_REJECT]_
- L792-799 _function_ `float3 GetTextureValueWithOffset(Texture2D Tex, float2 Position)` _[#if TEMPORAL_REPROJECTION_ALIGN \|\| TEMPORAL_REPROJECTION_MERGE \|\| TEMPORAL_REPROJECTION_RESOLVE \|\| TEMPORAL_HIGHFREQ_REJECT]_
- L814-823 _function_ `float ChannelRankedLuminance(float3 Value)` — Channel ranked luminance places the max value to g, and minimal to b In this way, the luminance is perception independent. The variance of (X,0,0) is the same to (0,X,0) instead of being smaller. _[#if TEMPORAL_PREPASS]_
- L826-859 _function_ `float4 GetMeanFromTextures(int2 Position)` — Note that the radiance, albedo and normal are the mean value. _[#if TEMPORAL_PREPASS]_
- L950-957 _function_ `float4 Fuse(float4 Albedo, float4 Normal, float4 Radiance, float4 History, FPixelMaterialLightingFingerprint Fingerprint)` _[#if TEMPORAL_FEATURE_FUSION]_
- L959-968 _function_ `float4 FuseSource(int2 Position)` _[#if TEMPORAL_FEATURE_FUSION]_
- L970-979 _function_ `float4 FuseTarget(int2 Position)` _[#if TEMPORAL_FEATURE_FUSION]_
- L1038-1089 _function_ `float4 Get3x3Blur(int2 Position)` _[#if TEMPORAL_REPROJECTION_BLUR]_
- L1116-1127 _function_ `uint GetTheKthPatchBasedOnMipAndPatchId()` _[#if TEMPORAL_REPROJECTION_MERGE]_
- L1294-1300 _function_ `float GetWeightMultiplier(float SourceTV, float TargetSourceTV)` — TODO: Ablation test
- L1338-1380 _function_ `float3 hsv2rgb(float h, float s, float v)` — h = [0, 1], s = [0 ,1], v = [0, 1] h: hue, s: saturate v: value _[#if VISUALIZE_MOTIONVECTOR]_
- L1383-1390 _function_ `float3 hsv2rgb_smooth(float3 c)` — :adapted from https://www.shadertoy.com/view/MsS3Wc by iq _[#if VISUALIZE_MOTIONVECTOR]_

#### Top-level macro invocations (1)

- L125 _macro_call_ `SCREEN_PASS_TEXTURE_VIEWPORT(TargetViewport)`

### `Shaders/Private/PathTracing/PathTracingSwizzleScanlines.usf` (Private)

- lines: 36; parse: all-branches
- includes: L3 `../Common.ush`

#### Entry points (1)

- L11-35 _entry_ `[numthreads(THREADGROUPSIZE_X, THREADGROUPSIZE_Y, 1)] void PathTracingSwizzleScanlinesCS(uint2 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FPathTracingSwizzleScanlinesCS` SF_Compute via IMPLEMENT_SHADER_TYPE (Source/Runtime/Renderer/Private/PathTracing.cpp:1745)

#### Global resources (textures / buffers / samplers) (2)

- L8 _resource_ `Texture2D<float4> InputTexture;`
- L9 _resource_ `RWTexture2D<float4> OutputTexture;`

#### Global parameters (uniforms) (3)

- L5 _parameter_ `uint2 DispatchDim;`
- L6 _parameter_ `uint2 TileSize;`
- L7 _parameter_ `uint ScanlineStride;`

### `Shaders/Private/PathTracing/PathTracingVolumetricCloudMaterialShader.usf` (Private)

- lines: 462; parse: all-branches
- includes: L6 `/Engine/Private/Common.ush`, L7 `/Engine/Private/RayTracing/RayTracingCommon.ush`, L8 `/Engine/Private/PathTracing/PathTracingShaderUtils.ush`, L48 `./Volume/PathTracingCloudsMaterialCommon.ush`, L49 `./Volume/PathTracingFog.ush`, L50 `./Volume/PathTracingAtmosphere.ush`, L51 `./Volume/PathTracingVolumeSampling.ush`, L53 `./PathTracingCommon.ush`

#### Macros (#define, 31)

- L3 `#define PATH_TRACING 1`
- L4 `#define PATH_TRACER_USE_CLOUD_SHADER 1`
- L11 `#define FogDensity PathTracingCloudParameters.FogDensity`
- L12 `#define FogHeight PathTracingCloudParameters.FogHeight`
- L13 `#define FogFalloff PathTracingCloudParameters.FogFalloff`
- L14 `#define FogAlbedo PathTracingCloudParameters.FogAlbedo`
- L15 `#define FogPhaseG PathTracingCloudParameters.FogPhaseG`
- L16 `#define FogCenter PathTracingCloudParameters.FogCenter`
- L17 `#define FogMinZ PathTracingCloudParameters.FogMinZ`
- L18 `#define FogMaxZ PathTracingCloudParameters.FogMaxZ`
- L19 `#define FogRadius PathTracingCloudParameters.FogRadius`
- L20 `#define FogFalloffClamp PathTracingCloudParameters.FogFalloffClamp`
- L22 `#define PlanetCenterTranslatedWorldHi PathTracingCloudParameters.PlanetCenterTranslatedWorldHi`
- L23 `#define PlanetCenterTranslatedWorldLo PathTracingCloudParameters.PlanetCenterTranslatedWorldLo`
- L24 `#define Atmosphere PathTracingCloudParameters`
- L26 `#define CloudAccelerationMap PathTracingCloudParameters.CloudAccelerationMap`
- L27 `#define CloudAccelerationMapSampler PathTracingCloudParameters.CloudAccelerationMapSampler`
- L29 `#define CloudClipX PathTracingCloudParameters.CloudClipX`
- L30 `#define CloudClipY PathTracingCloudParameters.CloudClipY`
- L31 `#define CloudClipZ PathTracingCloudParameters.CloudClipZ`
- L33 `#define CloudLayerBotKm PathTracingCloudParameters.CloudLayerBotKm`
- L34 `#define CloudLayerTopKm PathTracingCloudParameters.CloudLayerTopKm`
- L35 `#define CloudClipDistKm PathTracingCloudParameters.CloudClipDistKm`
- L36 `#define CloudClipRadiusKm PathTracingCloudParameters.CloudClipRadiusKm`
- L38 `#define CloudClipCenterKm PathTracingCloudParameters.CloudClipCenterKm`
- L40 `#define CloudTracingMaxDistance PathTracingCloudParameters.CloudTracingMaxDistance`
- L41 `#define CloudRoughnessCutoff PathTracingCloudParameters.CloudRoughnessCutoff`
- L43 `#define CloudAccelMapResolution PathTracingCloudParameters.CloudAccelMapResolution`
- L44 `#define CloudVoxelWidth PathTracingCloudParameters.CloudVoxelWidth`
- L45 `#define CloudInvVoxelWidth PathTracingCloudParameters.CloudInvVoxelWidth`
- L239 `#define USE_VOXEL_TRAVERSAL 1`

#### Entry points (1)

- L92-461 _entry_ `RAY_TRACING_ENTRY_CALLABLE(PathTracingVolumetricCloudMaterialShader, FPackedPathTracingPayload, PackedPayload)` — stage: **callable** — C++: `FPathTracingVolumetricCloudMaterial` SF_RayCallable via IMPLEMENT_SHADER_TYPE (Source/Runtime/Renderer/Private/PathTracing.cpp:1955) — C++: `FPathTracingVolumetricCloudMaterialVisualize` SF_RayCallable via IMPLEMENT_SHADER_TYPE (Source/Runtime/Renderer/Private/PathTracing.cpp:2130)

#### Functions (1)

- L55-90 _function_ `FVolumeShadedResult CloudsGetDensity(float3 TranslatedWorldPos)`
