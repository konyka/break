# Shaders / Shaders/Private/PathTracing/Light

- files: 8; lines: 1623
- record kinds: define=6, function=80, include=18, member=18, method=5, parameter=7, resource=3, struct=4

### `Shaders/Private/PathTracing/Light/PathTracingCapsuleLight.ush` (Private)

- lines: 224; parse: all-branches
- includes: L9 `PathTracingLightCommon.ush`, L10 `../../CapsuleLightSampling.ush`

#### Macros (#define, 1)

- L12 `#define CAPSULE_SOLIDANGLE_SAMPLING 1`
- L7 #pragma `once`

#### Functions (4)

- L14-19 _function_ `float3 CapsuleNormal(float3 Pos, float3 Center, float3 Axis)`
- L21-30 _function_ `float GetCapsuleRadius(int LightId, float3 Origin, float3 Axis, float Length)`
- L32-128 _function_ `FLightHit CapsuleLight_TraceLight(FRayDesc Ray, int LightId)`
- L131-223 _function_ `FLightSample CapsuleLight_SampleLight( int LightId, float2 RandSample, float3 TranslatedWorldPos, float3 WorldNormal )`

### `Shaders/Private/PathTracing/Light/PathTracingDirectionalLight.ush` (Private)

- lines: 80; parse: all-branches
- includes: L9 `PathTracingLightCommon.ush`
- L7 #pragma `once`

#### Functions (4)

- L11-34 _function_ `FLightHit DirectionalLight_TraceLight(FRayDesc Ray, int LightId)`
- L36-48 _function_ `FLightSample DirectionalLight_SampleLight( int LightId, float2 RandSample, float3 WorldNormal )`
- L50-62 _function_ `float DirectionalLight_EstimateLight( int LightId, float3 WorldNormal, bool IsTransmissiveMaterial )`
- L65-79 _function_ `FVolumeLightSampleSetup DirectionalLight_PrepareLightVolumeSample( int LightId, float3 RayOrigin, float3 RayDirection, float TMin, float TMax )` — NOTE: unused

### `Shaders/Private/PathTracing/Light/PathTracingLightCommon.ush` (Private)

- lines: 380; parse: all-branches
- includes: L9 `/Engine/Shared/RayTracingTypes.h`, L10 `/Engine/Shared/PathTracingDefinitions.h`

#### Macros (#define, 2)

- L266 `#define USE_ATTENUATION_TERM 1` _[#if !defined(USE_ATTENUATION_TERM)]_
- L294 `#define USE_IES_TERM 1` _[#if !defined(USE_IES_TERM)]_
- L7 #pragma `once`

#### Structs / classes (3)

- L15-23 _struct_ **`FLightHit`** `struct FLightHit`
  - L17 _member_ `float3 Radiance;`
  - L18 _member_ `float Pdf;`
  - L19 _member_ `float HitT;`
  - L21 _method_ `bool IsMiss()`
  - L22 _method_ `bool IsHit()`
- L25-31 _struct_ **`FLightSample`** `struct FLightSample`
  - L27 _member_ `float3 RadianceOverPdf;`
  - L28 _member_ `float Pdf;`
  - L29 _member_ `float3 Direction;`
  - L30 _member_ `float Distance;`
- L34-86 _struct_ **`FVolumeLightSampleSetup`** `struct FVolumeLightSampleSetup`
  - L36 _member_ `float VolumeTMin;` — range of 't' values along the ray that overlap the light (and the volume)
  - L37 _member_ `float VolumeTMax;`
  - L39 _member_ `float LightImportance;` — estimate of the light radiance for this ray (could be 0 if light does not support equi-angular sampling)
  - L42 _member_ `float T0;` — Equi-Angular case
  - L43 _member_ `float Height;` — distance from light center to ray (when negative, use uniform sampler)
  - L44 _member_ `float ThetaMin;` — angle to start of ray interval
  - L45 _member_ `float ThetaMax;` — angle to end of ray interval
  - L47 _member_ `float K;` — normalization constant for the pdf
  - L49 _method_ `bool IsValid()` — NOTE: we assume the range is a subset of the ray's TMin/TMax
  - L51 _method_ `float2 SampleDistance(float RandSample)`
  - L70 _method_ `float Pdf(float T)`

#### Global resources (textures / buffers / samplers) (1)

- L13 _resource_ `StructuredBuffer<FPathTracingLight> SceneLights;`

#### Global parameters (uniforms) (1)

- L12 _parameter_ `uint SceneLightCount;`

#### Functions (43)

- L88-104 _function_ `FVolumeLightSampleSetup CreateEquiAngularSampler(float LightImportance, float3 Center, float3 Ro, float3 Rd, float TMin, float TMax)`
- L106-115 _function_ `FVolumeLightSampleSetup CreateUniformSampler(float LightImportance, float TMin, float TMax)`
- L120-123 _function_ `FLightHit NullLightHit()`
- L125-132 _function_ `FLightHit CreateLightHit(float3 Radiance, float Pdf, float HitT)`
- L134-137 _function_ `FLightSample NullLightSample()`
- L139-147 _function_ `FLightSample CreateLightSample(float3 RadianceOverPdf, float Pdf, float3 Direction, float Distance)`
- L149-152 _function_ `FVolumeLightSampleSetup NullVolumeLightSetup()`
- L154-157 _function_ `bool IsEnvironmentLight(int LightId)`
- L159-162 _function_ `bool IsPointLight(int LightId)`
- L164-167 _function_ `bool IsDirectionalLight(int LightId)`
- L169-172 _function_ `bool IsRectLight(int LightId)`
- L174-177 _function_ `bool IsSpotLight(int LightId)`
- L180-183 _function_ `bool IsPhysicalLight(int LightId)` — A light is a physical light if it can be intersected by a ray.
- L185-188 _function_ `float3 GetTranslatedPosition(int LightId)`
- L190-193 _function_ `float3 GetNormal(int LightId)`
- L195-198 _function_ `float3 GetdPdu(int LightId)`
- L200-203 _function_ `float3 GetdPdv(int LightId)`
- L205-208 _function_ `float GetWidth(int LightId)`
- L210-213 _function_ `float GetHeight(int LightId)`
- L215-218 _function_ `float2 GetRectSize(int LightId)`
- L220-223 _function_ `float2 GetCosConeAngles(int LightId)`
- L225-228 _function_ `float3 GetColor(int LightId)`
- L230-233 _function_ `float GetRadius(int LightId)`
- L235-238 _function_ `float GetSourceLength(int LightId)`
- L240-243 _function_ `float GetAttenuation(int LightId)`
- L245-248 _function_ `float GetRectLightBarnCosAngle(int LightId)`
- L250-253 _function_ `float GetRectLightBarnLength(int LightId)`
- L255-258 _function_ `float2 GetRectLightAtlasUVScale(int LightId)`
- L260-263 _function_ `float2 GetRectLightAtlasUVOffset(int LightId)`
- L269-290 _function_ `float ComputeAttenuationFalloff(float DistanceSquared, int LightId)`
- L297-318 _function_ `float ComputeIESAttenuation(int LightId, float3 TranslatedWorldPosition)`
- L320-323 _function_ `bool HasTransmission(int LightId)`
- L325-328 _function_ `uint GetLightingChannelMask(int LightId)`
- L330-333 _function_ `bool IsStationary(int LightId)`
- L335-338 _function_ `bool CastsShadow(int LightId)`
- L340-343 _function_ `bool CastsVolumeShadow(int LightId)`
- L345-348 _function_ `bool CastsCloudShadow(int LightId)`
- L350-353 _function_ `bool HasRectTexture(int LightId)`
- L355-358 _function_ `float GetVolumetricScatteringIntensity(int LightId)`
- L360-363 _function_ `float GetLightSpecularScale(int LightId)`
- L365-368 _function_ `float GetLightDiffuseScale(int LightId)`
- L370-374 _function_ `float GetLightIndirectScale(int LightId, float PathRoughness)`
- L376-379 _function_ `uint GetLightMissShaderIndex(int LightId)`

### `Shaders/Private/PathTracing/Light/PathTracingLightGrid.ush` (Private)

- lines: 177; parse: all-branches
- includes: L7 `/Engine/Shared/PathTracingDefinitions.h`, L12 `../../Visualization.ush` [USE_PATH_TRACING_LIGHT_GRID]

#### Macros (#define, 1)

- L4 `#define USE_PATH_TRACING_LIGHT_GRID 0` _[#if !defined(USE_PATH_TRACING_LIGHT_GRID)]_

#### Structs / classes (1)

- L25-31 _struct_ **`FLightLoopCount`** `struct FLightLoopCount`
  - L26 _member_ `uint NumLights;`
  - L27 _member_ `uint NumMISLights;`
  - L29 _member_ `uint LightGridOffset;` _[#if USE_PATH_TRACING_LIGHT_GRID]_

#### Global resources (textures / buffers / samplers) (2)

- L18 _resource_ `Texture2DArray<uint> LightGrid;` _[#if USE_PATH_TRACING_LIGHT_GRID]_
- L19 _resource_ `Buffer<uint> LightGridData;` _[#if USE_PATH_TRACING_LIGHT_GRID]_

#### Global parameters (uniforms) (6)

- L15 _parameter_ `uint SceneInfiniteLightCount;` — extra shader parameters that must be defined when using the light grid _[#if USE_PATH_TRACING_LIGHT_GRID]_
- L16 _parameter_ `float3 SceneLightsTranslatedBoundMin;` _[#if USE_PATH_TRACING_LIGHT_GRID]_
- L17 _parameter_ `float3 SceneLightsTranslatedBoundMax;` _[#if USE_PATH_TRACING_LIGHT_GRID]_
- L20 _parameter_ `uint LightGridResolution;` _[#if USE_PATH_TRACING_LIGHT_GRID]_
- L21 _parameter_ `uint LightGridMaxCount;` _[#if USE_PATH_TRACING_LIGHT_GRID]_
- L22 _parameter_ `uint LightGridAxis;` _[#if USE_PATH_TRACING_LIGHT_GRID]_

#### Functions (6)

- L35-75 _function_ `FLightLoopCount LightGridLookup(float3 TranslatedWorldPos)` _[#if USE_PATH_TRACING_LIGHT_GRID]_
- L77-145 _function_ `float3 LightGridVisualize(FLightLoopCount LoopCount, int DebugMode, uint MaxCount)` _[#if USE_PATH_TRACING_LIGHT_GRID]_
- L147-154 _function_ `uint GetLightId(uint Index, FLightLoopCount LoopCount)` _[#if USE_PATH_TRACING_LIGHT_GRID]_
- L158-164 _function_ `FLightLoopCount LightGridLookup(float3 TranslatedWorldPos)` _[#if !(USE_PATH_TRACING_LIGHT_GRID)]_
- L166-169 _function_ `float3 LightGridVisualize(FLightLoopCount LoopCount, int DebugMode, uint MaxCount)` _[#if !(USE_PATH_TRACING_LIGHT_GRID)]_
- L171-174 _function_ `uint GetLightId(uint Index, FLightLoopCount LoopCount)` _[#if !(USE_PATH_TRACING_LIGHT_GRID)]_

### `Shaders/Private/PathTracing/Light/PathTracingLightSampling.ush` (Private)

- lines: 169; parse: all-branches
- includes: L15 `PathTracingLightCommon.ush`, L16 `PathTracingDirectionalLight.ush`, L17 `PathTracingPointLight.ush`, L18 `PathTracingRectLight.ush`, L19 `PathTracingSkyLight.ush`

#### Macros (#define, 1)

- L10 `#define ENABLE_TRANSMISSION 1` _[#if !defined(ENABLE_TRANSMISSION)]_
- L7 #pragma `once`

#### Functions (6)

- L22-33 _function_ `FLightHit TraceLight(FRayDesc Ray, int LightId)` — Returns float4 packed with Radiance and Pdf
- L36-52 _function_ `FLightSample SampleLight( int LightId, float2 RandSample, float3 TranslatedWorldPos, float3 WorldNormal )` — Choose a point on a light as seen from the given shading point
- L54-76 _function_ `float EstimateLight( int LightId, float3 TranslatedWorldPos, float3 WorldNormal, uint PrimitiveLightingChannelMask, bool IsTransmissiveMaterial )`
- L78-96 _function_ `FVolumeLightSampleSetup PrepareLightVolumeSample( int LightId, float3 RayOrigin, float3 RayDirection, float TMin, float TMax )`
- L99-121 _function_ `float InitLightPickingCdf( float3 TranslatedWorldPos, float3 WorldNormal, uint PrimitiveLightingChannelMask, bool IsTransmissiveMaterial, inout float LightPickingCdf[RAY_TRACING_LIGHT_COUNT_MAXIMUM])` — #dxr_todo: passing LightPickingCdf as anything but inout causes performance to drop significantly -- why ?
- L124-168 _function_ `void SelectLight(float RandSample, int NumLights, inout float LightPickingCdf[RAY_TRACING_LIGHT_COUNT_MAXIMUM], out uint LightId, out float LightPickPdf)` — #dxr_todo: passing LightPickingCdf as anything but inout causes performance to drop significantly -- why ?

### `Shaders/Private/PathTracing/Light/PathTracingPointLight.ush` (Private)

- lines: 223; parse: all-branches
- includes: L9 `PathTracingLightCommon.ush`, L10 `PathTracingCapsuleLight.ush`, L11 `../../IntersectionUtils.ush`
- L7 #pragma `once`

#### Functions (5)

- L21-25 _function_ `float SpotAttenuation(float3 L, float3 SpotDirection, float2 SpotAngles)` — Calculates attenuation for a spot light. L normalize vector to light. SpotDirection is the direction of the spot light. SpotAngles.x is CosOuterCone, SpotAngles.y is InvCosConeDifference.
- L28-81 _function_ `FLightHit PointLight_TraceLight(FRayDesc Ray, int LightId)`
- L83-137 _function_ `FLightSample PointLight_SampleLight( int LightId, float2 RandSample, float3 TranslatedWorldPos, float3 WorldNormal )`
- L139-163 _function_ `float PointLight_EstimateLight( int LightId, float3 TranslatedWorldPos, float3 WorldNormal, bool IsTransmissiveMaterial )`
- L165-222 _function_ `FVolumeLightSampleSetup PointLight_PrepareLightVolumeSample( int LightId, float3 RayOrigin, float3 RayDirection, float TMin, float TMax )`

### `Shaders/Private/PathTracing/Light/PathTracingRectLight.ush` (Private)

- lines: 268; parse: all-branches
- includes: L9 `../../RectLight.ush`, L10 `PathTracingLightCommon.ush`
- L7 #pragma `once`

#### Functions (8)

- L14-27 _function_ `float3 EvaluateTexture(int LightId, float2 UV)` _[#if USE_RECT_LIGHT_TEXTURES]_
- L31-45 _function_ `float3 BilinearQuadWarp(float2 uv, float W00, float W01, float W10, float W11)`
- L51-75 _function_ `float4 SampleApproxProjectionSphericalRect(float2 Rand, FSphericalRect SphericalRect, float3 WorldNormal)` — TODO: This method should be moved to RectLight.ush TODO: Analyze the overall efficiency (MSE reduction vs. time) Projected solid angle sampling converges faster at equal sample count, but is a bit slower TODO: Unify with UniformSampleSphericalRect so both return the same struct, making them easier to interchange
- L77-123 _function_ `FLightHit RectLight_TraceLight(FRayDesc Ray, int LightId)`
- L125-164 _function_ `FLightSample RectLight_SampleLight( int LightId, float2 RandSample, float3 TranslatedWorldPos, float3 WorldNormal )`
- L166-196 _function_ `float RectLight_EstimateLight( int LightId, float3 TranslatedWorldPos, float3 WorldNormal, bool IsTransmissiveMaterial )`
- L198-212 _function_ `void ClipRayByPlane(float3 RayOrigin, float3 RayDirection, float3 N, float3 C, inout float TMin, inout float TMax)`
- L214-267 _function_ `FVolumeLightSampleSetup RectLight_PrepareLightVolumeSample( int LightId, float3 RayOrigin, float3 RayDirection, float TMin, float TMax )`

### `Shaders/Private/PathTracing/Light/PathTracingSkyLight.ush` (Private)

- lines: 102; parse: all-branches
- includes: L9 `../../RayTracing/RayTracingSkyLightCommon.ush`

#### Macros (#define, 1)

- L15 `#define PATHTRACING_SKY_MIS 0` _[#if !defined(PATHTRACING_SKY_MIS)]_
- L7 #pragma `once`

#### Functions (4)

- L18-29 _function_ `float SkyLight_EstimateLight( int LightId, float3 WorldNormal, bool IsTransmissiveMaterial )`
- L31-39 _function_ `FLightHit SkyLight_TraceLight(FRayDesc Ray, int LightId)`
- L41-89 _function_ `FLightSample SkyLight_SampleLight( int LightId, float2 RandSample, float3 WorldNormal )`
- L92-101 _function_ `FVolumeLightSampleSetup SkyLight_PrepareLightVolumeSample( int LightId, float3 RayOrigin, float3 RayDirection, float TMin, float TMax )` — NOTE: unused
