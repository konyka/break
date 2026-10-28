# Shaders / Shaders/Private/PathTracing/Volume

- files: 14; lines: 2808
- record kinds: define=19, function=106, include=29, member=42, method=10, parameter=29, prototype=9, resource=9, struct=10

### `Shaders/Private/PathTracing/Volume/PathTracingAtmosphere.ush` (Private)

- lines: 302; parse: all-branches
- includes: L5 `./PathTracingAtmosphereCommon.ush`, L6 `../../DoubleFloat.ush`, L7 `../../SkyAtmosphereCommon.ush`

#### Macros (#define, 1)

- L10 `#define PLANET_ISECT_USES_DOUBLE_WORD_MATH 1`
- L3 #pragma `once`

#### Structs / classes (1)

- L146-165 _struct_ **`FSphericalPlanetParameters`** `struct FSphericalPlanetParameters`
  - L147 _member_ `float HeightKm;` — Distance from planet center (in Km)
  - L148 _member_ `float ZenithCosAngle;` — angle between the ray and the planet normal (+1 goes up towards space, -1 points down toward the ground)
  - L150 _method_ `FSphericalPlanetParameters GetAt(float TKm)`
  - L161 _method_ `float GetHorizonCosine()`

#### Global resources (textures / buffers / samplers) (2)

- L17 _resource_ `Texture2D<float3> AtmosphereOpticalDepthLUT;` _[#if !defined(PlanetCenterTranslatedWorldHi)]_
- L18 _resource_ `SamplerState AtmosphereOpticalDepthLUTSampler;` _[#if !defined(PlanetCenterTranslatedWorldHi)]_

#### Global parameters (uniforms) (2)

- L15 _parameter_ `float3 PlanetCenterTranslatedWorldHi;` _[#if !defined(PlanetCenterTranslatedWorldHi)]_
- L16 _parameter_ `float3 PlanetCenterTranslatedWorldLo;` _[#if !defined(PlanetCenterTranslatedWorldHi)]_

#### Functions (9)

- L25-67 _function_ `float3 RayPlanetIntersectPrecise(float3 Ro, float3 Rd)` — intersect the planet using high precision returns: planet hit T, atmo hit min/max (or -1.0 for any if missed) _[#if PLANET_ISECT_USES_DOUBLE_WORD_MATH]_
- L72-106 _function_ `float3 RayPlanetIntersectPrecise(float3 Ro, float3 Rd)` — robust intersector with plain floats, still runs into trouble beyond 1000km or so _[#if !(PLANET_ISECT_USES_DOUBLE_WORD_MATH)]_
- L112-120 _function_ `FVolumeIntersection AtmosphereIntersect(float3 Origin, float3 Direction, float TMin, float TMax)` _[#if CLOUD_LAYER_PIXEL_SHADER == 0]_
- L122-142 _function_ `FPackedPathTracingPayload AtmosphereGetBlockerHit(float3 Origin, float3 Direction, float HitT, bool bIsCameraRay)` _[#if CLOUD_LAYER_PIXEL_SHADER == 0]_
- L167-186 _function_ `FSphericalPlanetParameters GetSphericalPlanetParameters(float3 Origin, float3 Direction)`
- L188-243 _function_ `FVolumeDensityBounds AtmosphereGetDensityBounds(float3 Origin, float3 Direction, float TMin, float TMax)`
- L245-261 _function_ `FVolumeShadedResult AtmosphereGetDensity(float3 TranslatedWorldPos)`
- L265-288 _function_ `float3 AtmosphereGetOpticalDensity(FSphericalPlanetParameters Params)` _[#if CLOUD_LAYER_PIXEL_SHADER == 0]_
- L290-300 _function_ `float3 AtmosphereGetTransmittance(float3 Origin, float3 Direction, float TMin, float TMax)` _[#if CLOUD_LAYER_PIXEL_SHADER == 0]_

### `Shaders/Private/PathTracing/Volume/PathTracingAtmosphereCommon.ush` (Private)

- lines: 54; parse: all-branches
- L3 #pragma `once`

#### Functions (4)

- L7-11 _function_ `float Gain(float x, float k)`
- L13-17 _function_ `float ComputeHorizonCosine(float ViewHeight, float BotRadius)`
- L19-33 _function_ `float2 ToAtmosphereOpticalDepthLUTUV(float Height, float Cosine, float BotRadius, float TopRadius)`
- L35-53 _function_ `float2 FromAtmosphereOpticalDepthLUTUV(float2 UV, float BotRadius, float TopRadius)`

### `Shaders/Private/PathTracing/Volume/PathTracingClouds.ush` (Private)

- lines: 166; parse: all-branches
- includes: L5 `./PathTracingAtmosphereCommon.ush`, L6 `./PathTracingCloudsCommon.ush`
- L3 #pragma `once`

#### Global resources (textures / buffers / samplers) (2)

- L9 _resource_ `Texture2D<float4> CloudAccelerationMap;`
- L10 _resource_ `SamplerState CloudAccelerationMapSampler;`

#### Functions (2)

- L13-59 _function_ `float4 RayCloudIntersectPrecise(float3 Ro, float3 Rd)` — intersect the cloud layer with high precision
- L61-165 _function_ `FVolumeIntersection CloudsIntersect(float3 Origin, float3 Direction, float TMin, float TMax, float PathRoughness)`

### `Shaders/Private/PathTracing/Volume/PathTracingCloudsCommon.ush` (Private)

- lines: 68; parse: all-branches
- includes: L5 `../PathTracingCommon.ush`, L6 `../../SkyAtmosphereCommon.ush`
- L3 #pragma `once`

#### Global parameters (uniforms) (14)

- L9 _parameter_ `float3 CloudClipX;` _[#if !defined(CloudClipX)]_
- L10 _parameter_ `float3 CloudClipY;` _[#if !defined(CloudClipX)]_
- L11 _parameter_ `float3 CloudClipZ;` _[#if !defined(CloudClipX)]_
- L13 _parameter_ `float3 CloudClipCenterKm;` _[#if !defined(CloudClipX)]_
- L15 _parameter_ `float CloudLayerBotKm;` _[#if !defined(CloudClipX)]_
- L16 _parameter_ `float CloudLayerTopKm;` _[#if !defined(CloudClipX)]_
- L17 _parameter_ `float CloudClipDistKm;` _[#if !defined(CloudClipX)]_
- L18 _parameter_ `float CloudClipRadiusKm;` _[#if !defined(CloudClipX)]_
- L20 _parameter_ `float CloudTracingMaxDistance;` _[#if !defined(CloudClipX)]_
- L21 _parameter_ `float CloudRoughnessCutoff;` _[#if !defined(CloudClipX)]_
- L22 _parameter_ `float CloudVoxelWidth;` _[#if !defined(CloudClipX)]_
- L23 _parameter_ `float CloudInvVoxelWidth;` _[#if !defined(CloudClipX)]_
- L24 _parameter_ `int CloudAccelMapResolution;` _[#if !defined(CloudClipX)]_
- L25 _parameter_ `int CloudCallableShaderId;` _[#if !defined(CloudClipX)]_

#### Functions (6)

- L28-31 _function_ `float3x3 GetCloudClipBasis()`
- L33-36 _function_ `float GetLowestCloudZ()`
- L38-41 _function_ `float GetFarthestCornerDist()`
- L43-56 _function_ `float2 GetRadiusBounds()`
- L58-62 _function_ `int2 PositionToVoxel(float2 P)`
- L64-67 _function_ `float2 VoxelToPosition(int2 Idx)`

### `Shaders/Private/PathTracing/Volume/PathTracingCloudsMaterialCommon.ush` (Private)

- lines: 141; parse: all-branches
- includes: L8 `../../Common.ush`, L10 `/Engine/Generated/Material.ush` [CLOUD_VISUALIZATION_SHADER == 0], L12 `PathTracingVolumeCommon.ush`, L13 `PathTracingCloudsCommon.ush`, L14 `../../DoubleFloat.ush`, L15 `../../SkyAtmosphereCommon.ush`

#### Macros (#define, 7)

- L20 `#define MATVEC float` _[#if MATERIAL_VOLUMETRIC_ADVANCED_GRAYSCALE_MATERIAL]_
- L21 `#define ColorToMATVEC(C) ((C).r)` _[#if MATERIAL_VOLUMETRIC_ADVANCED_GRAYSCALE_MATERIAL]_
- L22 `#define MATVEC_Max(C) (C)` _[#if MATERIAL_VOLUMETRIC_ADVANCED_GRAYSCALE_MATERIAL]_
- L23 `#define MATVEC_Min(C) (C)` _[#if MATERIAL_VOLUMETRIC_ADVANCED_GRAYSCALE_MATERIAL]_
- L24 `#define MATVEC_Avg(C) (C)` _[#if MATERIAL_VOLUMETRIC_ADVANCED_GRAYSCALE_MATERIAL]_
- L28 `#define MATVEC float3` _[#if !(MATERIAL_VOLUMETRIC_ADVANCED_GRAYSCALE_MATERIAL)]_
- L29 `#define ColorToMATVEC(C) ((C).rgb)` _[#if !(MATERIAL_VOLUMETRIC_ADVANCED_GRAYSCALE_MATERIAL)]_
- L3 #pragma `once`

#### Structs / classes (2)

- L37-47 _struct_ **`FSampleCloudMaterialResult`** `struct FSampleCloudMaterialResult` — Simplified struct that represents what a CloudMaterial can return
  - L39 _member_ `MATVEC Extinction;`
  - L40 _member_ `MATVEC Albedo;`
  - L41 _member_ `MATVEC Emission;`
  - L43 _member_ `float PhaseG1;` _[#if MATERIAL_VOLUMETRIC_ADVANCED]_
  - L44 _member_ `float PhaseG2;` _[#if MATERIAL_VOLUMETRIC_ADVANCED]_
  - L45 _member_ `float PhaseBlend;` _[#if MATERIAL_VOLUMETRIC_ADVANCED]_
- L50-55 _struct_ **`FCloudMaterialMSParams`** `struct FCloudMaterialMSParams` _[#if MATERIAL_VOLUMETRIC_ADVANCED_MULTISCATTERING_OCTAVE_COUNT > 0]_
  - L52 _member_ `float ScattFactor;` _[#if MATERIAL_VOLUMETRIC_ADVANCED_MULTISCATTERING_OCTAVE_COUNT > 0]_
  - L53 _member_ `float ExtinFactor;` _[#if MATERIAL_VOLUMETRIC_ADVANCED_MULTISCATTERING_OCTAVE_COUNT > 0]_
  - L54 _member_ `float PhaseFactor;` _[#if MATERIAL_VOLUMETRIC_ADVANCED_MULTISCATTERING_OCTAVE_COUNT > 0]_

#### Functions (5)

- L30 _function_ `float MATVEC_Max(float3 C)` _[#if !(MATERIAL_VOLUMETRIC_ADVANCED_GRAYSCALE_MATERIAL)]_
- L31 _function_ `float MATVEC_Min(float3 C)` _[#if !(MATERIAL_VOLUMETRIC_ADVANCED_GRAYSCALE_MATERIAL)]_
- L32 _function_ `float MATVEC_Avg(float3 C)` _[#if !(MATERIAL_VOLUMETRIC_ADVANCED_GRAYSCALE_MATERIAL)]_
- L57-75 _function_ `FCloudMaterialMSParams CloudMaterialGetMSParams()` _[#if MATERIAL_VOLUMETRIC_ADVANCED_MULTISCATTERING_OCTAVE_COUNT > 0]_
- L81-139 _function_ `FSampleCloudMaterialResult SampleCloudMaterial(FDFVector3 AbsoluteWorldPosition, float HeightKm, float CloudBotKm, float CloudTopKm)` — For path tracing, we need to be able to evaluate the material starting from a single point in space In all contexts, we have a slightly more accurate Height already available so pass that in instead of measuring it from the position _[#if CLOUD_VISUALIZATION_SHADER == 0]_

### `Shaders/Private/PathTracing/Volume/PathTracingFog.ush` (Private)

- lines: 117; parse: all-branches
- L3 #pragma `once`

#### Global parameters (uniforms) (10)

- L7 _parameter_ `float2 FogDensity;` _[#if !defined(FogDensity)]_
- L8 _parameter_ `float2 FogHeight;` _[#if !defined(FogDensity)]_
- L9 _parameter_ `float2 FogFalloff;` _[#if !defined(FogDensity)]_
- L10 _parameter_ `float4 FogAlbedo;` _[#if !defined(FogDensity)]_
- L11 _parameter_ `float FogPhaseG;` _[#if !defined(FogDensity)]_
- L12 _parameter_ `float2 FogCenter;` _[#if !defined(FogDensity)]_
- L13 _parameter_ `float FogMinZ;` _[#if !defined(FogDensity)]_
- L14 _parameter_ `float FogMaxZ;` _[#if !defined(FogDensity)]_
- L15 _parameter_ `float FogRadius;` _[#if !defined(FogDensity)]_
- L16 _parameter_ `float FogFalloffClamp;` _[#if !defined(FogDensity)]_

#### Functions (5)

- L19-46 _function_ `FVolumeIntersection FogIntersect(float3 Origin, float3 Direction, float TMin, float TMax)`
- L49-52 _function_ `float2 FogGetDualDensity(float Z)` — returns the density for each bank of fog
- L54-73 _function_ `FVolumeDensityBounds FogGetDensityBounds(float3 Origin, float3 Direction, float TMin, float TMax)`
- L76-85 _function_ `FVolumeShadedResult FogGetDensity(float3 TranslatedWorldPos)` — Given a point in world space, return the amount of volume and its scattering properties
- L88-116 _function_ `float3 FogGetTransmittance(float3 Origin, float3 Direction, float TMin, float TMax)` — Return the transmittance along a ray segment

### `Shaders/Private/PathTracing/Volume/PathTracingHeterogeneousVolumes.ush` (Private)

- lines: 389; parse: all-branches
- includes: L11 `../../HeterogeneousVolumes/HeterogeneousVolumesTracingUtils.ush`, L12 `../../HeterogeneousVolumes/HeterogeneousVolumesVoxelGridTraversal.ush`, L13 `../Utilities/PathTracingRandomSequence.ush`, L14 `PathTracingVolumeSampling.ush`, L15 `PathTracingVolumeCommon.ush`, L16 `PathTracingHeterogeneousVolumesForwardDecl.ush`, L17 `PathTracingHeterogeneousVolumesMaterialCommon.ush`, L18 `PathTracingHeterogeneousVolumesTrackingCommon.ush`, L19 `PathTracingHeterogeneousVolumesPreshadingCommon.ush`

#### Macros (#define, 4)

- L5 `#define USE_MEGAVOXEL 0`
- L6 `#define USE_CALLABLE_SHADERS 1`
- L7 `#define USE_MULTIPLE_VOLUMES 1`
- L9 `#define USE_PRESHADED_UNIFORM_BUFFER (PATH_TRACER_HETEROGENEOUS_VOLUMES_PIPELINE != USE_MEGAVOXEL)`
- L3 #pragma `once`

#### Functions (14)

- L24-51 _function_ `FVolumeIntersection HeterogeneousVolumesIntersectInternal(float3 Origin, float3 Direction, float TMin, float TMax)` — Intersection API..
- L53-60 _function_ `FVolumeIntersection HeterogeneousVolumesIntersect(float3 Origin, float3 Direction, float TMin, float TMax)`
- L65-69 _function_ `FVolumeDensityBounds HeterogeneousVolumesGetDensityBoundsInternal(float3 Origin, float3 Direction, float TMin, float TMax)` — Density APIs..
- L71-75 _function_ `FVolumeDensityBounds HeterogeneousVolumesGetDensityBoundsPreshading(float3 Origin, float3 Direction, float TMin, float TMax)`
- L77-84 _function_ `FVolumeDensityBounds HeterogeneousVolumesGetDensityBounds(float3 Origin, float3 Direction, float TMin, float TMax)`
- L86-155 _function_ `FVolumeShadedResult GetOrthoVoxelGridDensity(float3 TranslatedWorldPos)`
- L157-198 _function_ `FVolumeShadedResult GetFrustumVoxelGridDensity(float3 TranslatedWorldPos, inout bool bInFrustum)`
- L200-214 _function_ `FVolumeShadedResult HeterogeneousVolumesGetDensityInternal(float3 TranslatedWorldPos)`
- L216-223 _function_ `FVolumeShadedResult HeterogeneousVolumesGetDensity(float3 TranslatedWorldPos, int HeterogeneousVolumesIndex)`
- L225-349 _function_ `FVolumeTrackingResult HeterogeneousVolumesMajorantBasedTrackingInternal(float3 PathThroughput, float3 WorldRayOrigin, float3 WorldRayDirection, float WorldTMin, float WorldTMax, int bTransmittanceOnly, FMajorantData OverlappingMajorant, inout FRandomSequence RandSequence)`
- L355-359 _function_ `FVolumeTrackingResult HeterogeneousVolumesSampleDistanceInternal(float3 PathThroughput, float3 Origin, float3 Direction, float TMin, float TMax, FMajorantData OverlappingMajorant, inout FRandomSequence RandSequence)`
- L361-368 _function_ `FVolumeTrackingResult HeterogeneousVolumesSampleDistance(float3 PathThroughput, float3 Origin, float3 Direction, float TMin, float TMax, FMajorantData OverlappingMajorant, inout FRandomSequence RandSequence)`
- L374-379 _function_ `float3 HeterogeneousVolumesGetTransmittanceInternal(float3 PathThroughput, float3 Origin, float3 Direction, float TMin, float TMax, inout FRandomSequence RandSequence)`
- L381-388 _function_ `float3 HeterogeneousVolumesGetTransmittance(float3 PathThroughput, float3 Origin, float3 Direction, float TMin, float TMax, inout FRandomSequence RandSequence)`

### `Shaders/Private/PathTracing/Volume/PathTracingHeterogeneousVolumesForwardDecl.ush` (Private)

- lines: 27; parse: all-branches
- L3 #pragma `once`

#### Structs / classes (1)

- L9-17 _struct_ **`FVolumeTrackingResult`** `struct FVolumeTrackingResult`
  - L11 _member_ `float3 Throughput;`
  - L12 _member_ `float Pdf;`
  - L13 _member_ `float Distance;`
  - L14 _member_ `float3 SigmaBar;`
  - L15 _member_ `bool bIsCollision;`
  - L16 _member_ `int HeterogeneousVolumesIndex;`

#### Prototypes (9)

- L5 _prototype_ `FVolumeIntersection HeterogeneousVolumesIntersect(float3 Origin, float3 Direction, float TMin, float TMax)`
- L6 _prototype_ `FVolumeDensityBounds HeterogeneousVolumesGetDensityBounds(float3 Origin, float3 Direction, float TMin, float TMax)`
- L7 _prototype_ `FVolumeShadedResult HeterogeneousVolumesGetDensity(float3 TranslatedWorldPos, int CustomData)`
- L19 _prototype_ `FVolumeTrackingResult CreateVolumeTrackingResult(float Distance)`
- L20 _prototype_ `FVolumeTrackingResult ConcatenateVolumeTrackingResult(FVolumeTrackingResult lhs, FVolumeTrackingResult rhs)`
- L22 _prototype_ `FVolumeTrackingResult HeterogeneousVolumesSampleDistance(float3 PathThroughput, float3 Origin, float3 Direction, float TMin, float TMax, FMajorantData OverlappingMajorant, inout FRandomSequence RandSequence)`
- L23 _prototype_ `float3 HeterogeneousVolumesGetTransmittance(float3 PathThroughput, float3 Origin, float3 Direction, float TMin, float TMax, inout FRandomSequence RandSequence)`
- L25 _prototype_ `FVolumeTrackingResult HeterogeneousVolumesDeltaTracking(float3 PathThroughput, float LocalTMin, float LocalTMax, float LocalToWorldScale, FMajorantData MajorantData, inout FRandomSequence RandSequence)`
- L26 _prototype_ `FVolumeTrackingResult HeterogeneousVolumesRatioTracking(float3 PathThroughput, float3 TranslatedWorldOrigin, float3 WorldDirection, float LocalTMax, float LocalToWorldScale, FMajorantData MajorantData, inout FRandomSequence RandSequence)`

### `Shaders/Private/PathTracing/Volume/PathTracingHeterogeneousVolumesMaterialCommon.ush` (Private)

- lines: 296; parse: all-branches
- includes: L5 `../../Common.ush`
- L3 #pragma `once`

#### Functions (29)

- L9-13 _function_ `float3 GetHeterogeneousVolumeCallableShaderWorldPos(float3 TranslatedWorldPos)`
- L15-19 _function_ `float3 GetHeterogeneousVolumeCallableShaderTranslatedWorldPos(float3 WorldPos)`
- L23-26 _function_ `float GetHeterogeneousVolumeCallableShaderPhaseG()`
- L30-37 _function_ `void SetHeterogeneousVolumeCallableShaderHitT( float2 HitT, inout FPackedPathTracingPayload Payload )`
- L39-47 _function_ `float2 GetHeterogeneousVolumeCallableShaderHitT( FPackedPathTracingPayload Payload )`
- L51-66 _function_ `void SetHeterogeneousVolumeCallableShaderRay( FRayDesc Ray, inout FPackedPathTracingPayload Payload )`
- L68-84 _function_ `FRayDesc GetHeterogeneousVolumeCallableShaderRay( FPackedPathTracingPayload Payload )`
- L86-93 _function_ `void SetHeterogeneousVolumeCallableShaderRandomSequence( FRandomSequence RandSeq, inout FPackedPathTracingPayload Payload )`
- L95-103 _function_ `FRandomSequence GetHeterogeneousVolumeCallableShaderRandomSequence( FPackedPathTracingPayload Payload )`
- L105-113 _function_ `void SetHeterogeneousVolumeCallableShaderThroughput( float3 Throughput, inout FPackedPathTracingPayload Payload )`
- L115-124 _function_ `float3 GetHeterogeneousVolumeCallableShaderThroughput( FPackedPathTracingPayload Payload )`
- L126-132 _function_ `void SetHeterogeneousVolumeCallableShaderMajorant( float Majorant, FPackedPathTracingPayload Payload )`
- L134-140 _function_ `float GetHeterogeneousVolumeCallableShaderMajorant( FPackedPathTracingPayload Payload )`
- L144-152 _function_ `void SetHeterogeneousVolumeCallableShaderTranslatedWorldPos( float3 TranslatedWorldPos, inout FPackedPathTracingPayload Payload )`
- L154-163 _function_ `float3 GetHeterogeneousVolumeCallableShaderTranslatedWorldPos( FPackedPathTracingPayload Payload )`
- L165-173 _function_ `void SetHeterogeneousVolumeCallableShaderSigmaT( float3 SigmaT, inout FPackedPathTracingPayload Payload )`
- L175-184 _function_ `float3 GetHeterogeneousVolumeCallableShaderSigmaT( FPackedPathTracingPayload Payload )`
- L186-194 _function_ `void SetHeterogeneousVolumeCallableShaderAlbedo( float3 Albedo, inout FPackedPathTracingPayload Payload )`
- L196-205 _function_ `float3 GetHeterogeneousVolumeCallableShaderAlbedo( FPackedPathTracingPayload Payload )`
- L207-215 _function_ `void SetHeterogeneousVolumeCallableShaderEmission( float3 Emission, inout FPackedPathTracingPayload Payload )`
- L217-226 _function_ `float3 GetHeterogeneousVolumeCallableShaderEmission( FPackedPathTracingPayload Payload )`
- L228-234 _function_ `void SetHeterogeneousVolumeCallableShaderPdf( float Pdf, inout FPackedPathTracingPayload Payload )`
- L236-242 _function_ `float GetHeterogeneousVolumeCallableShaderPdf( FPackedPathTracingPayload Payload )`
- L244-250 _function_ `void SetHeterogeneousVolumeCallableShaderDistance( float Distance, inout FPackedPathTracingPayload Payload )`
- L252-258 _function_ `float GetHeterogeneousVolumeCallableShaderDistance( FPackedPathTracingPayload Payload )`
- L260-268 _function_ `void SetHeterogeneousVolumeCallableShaderSigmaBar( float3 SigmaBar, inout FPackedPathTracingPayload Payload )`
- L270-279 _function_ `float3 GetHeterogeneousVolumeCallableShaderSigmaBar( FPackedPathTracingPayload Payload )`
- L281-287 _function_ `void SetHeterogeneousVolumeCallableShaderIsCollision( bool bIsCollision, inout FPackedPathTracingPayload Payload )`
- L289-295 _function_ `bool GetHeterogeneousVolumeCallableShaderIsCollision( FPackedPathTracingPayload Payload )`

### `Shaders/Private/PathTracing/Volume/PathTracingHeterogeneousVolumesPreshadingCommon.ush` (Private)

- lines: 422; parse: all-branches

#### Macros (#define, 3)

- L6 `#define USE_PRESHADED_UNIFORM_BUFFER 0` _[#if !defined(USE_PRESHADED_UNIFORM_BUFFER)]_
- L10 `#define USE_CALLABLE_SHADERS 0` _[#if !defined(USE_CALLABLE_SHADERS)]_
- L14 `#define USE_MULTIPLE_VOLUMES 0` _[#if !defined(USE_MULTIPLE_VOLUMES)]_
- L3 #pragma `once`

#### Global resources (textures / buffers / samplers) (5)

- L20 _resource_ `Buffer<int> HeterogeneousVolumesCallableShaderIdIntersect;` _[#if USE_PRESHADED_UNIFORM_BUFFER]_
- L21 _resource_ `Buffer<int> HeterogeneousVolumesCallableShaderIdGetDensityBounds;` _[#if USE_PRESHADED_UNIFORM_BUFFER]_
- L22 _resource_ `Buffer<int> HeterogeneousVolumesCallableShaderIdGetDensity;` _[#if USE_PRESHADED_UNIFORM_BUFFER]_
- L23 _resource_ `Buffer<int> HeterogeneousVolumesCallableShaderIdSampleDistance;` _[#if USE_PRESHADED_UNIFORM_BUFFER]_
- L24 _resource_ `Buffer<int> HeterogeneousVolumesCallableShaderIdGetTransmittance;` _[#if USE_PRESHADED_UNIFORM_BUFFER]_

#### Global parameters (uniforms) (1)

- L19 _parameter_ `int HeterogeneousVolumesNum;` _[#if USE_PRESHADED_UNIFORM_BUFFER]_

#### Functions (7)

- L26-30 _function_ `void ExpandHitT(float2 RayHitT, inout float2 ResultHitT)` _[#if USE_PRESHADED_UNIFORM_BUFFER]_
- L32-79 _function_ `FVolumeIntersection HeterogeneousVolumesIntersectPreshading(float3 TranslatedWorldOrigin, float3 WorldDirection, float TMin, float TMax)` _[#if USE_PRESHADED_UNIFORM_BUFFER]_
- L81-122 _function_ `void SampleVolumeRenderingCoefficients( float3 TranslatedWorldPos, inout float3 SigmaT, inout float3 Albedo, inout float3 Emission )` _[#if USE_PRESHADED_UNIFORM_BUFFER]_
- L124-178 _function_ `FVolumeShadedResult HeterogeneousVolumesGetDensityPreshading(float3 TranslatedWorldPos, int HeterogeneousVolumesIndex)` _[#if USE_PRESHADED_UNIFORM_BUFFER]_
- L180-321 _function_ `FVolumeTrackingResult HeterogeneousVolumesMajorantBasedTrackingPreshading(float3 PathThroughput, float3 TranslatedWorldOrigin, float3 WorldDirection, float TMin, float TMax, int bTransmittanceOnly, FMajorantData OverlappingMajorant, inout FRandomSequence RandSequence)` _[#if USE_PRESHADED_UNIFORM_BUFFER]_
- L323-380 _function_ `FVolumeTrackingResult HeterogeneousVolumesSampleDistancePreshading(float3 PathThroughput, float3 Origin, float3 Direction, float TMin, float TMax, FMajorantData OverlappingMajorant, inout FRandomSequence RandSequence)` _[#if USE_PRESHADED_UNIFORM_BUFFER]_
- L382-420 _function_ `float3 HeterogeneousVolumesGetTransmittancePreshading(float3 PathThroughput, float3 Origin, float3 Direction, float TMin, float TMax, inout FRandomSequence RandSequence)` _[#if USE_PRESHADED_UNIFORM_BUFFER]_

### `Shaders/Private/PathTracing/Volume/PathTracingHeterogeneousVolumesTrackingCommon.ush` (Private)

- lines: 128; parse: all-branches

#### Macros (#define, 1)

- L39 `#define SAMPLE_ACHROMATIC 0`
- L3 #pragma `once`

#### Functions (4)

- L5-16 _function_ `FVolumeTrackingResult CreateVolumeTrackingResult(float Distance)`
- L18-31 _function_ `FVolumeTrackingResult ConcatenateVolumeTrackingResult(FVolumeTrackingResult lhs, FVolumeTrackingResult rhs)`
- L33-74 _function_ `FVolumeTrackingResult HeterogeneousVolumesDeltaTracking(float3 PathThroughput, float LocalTMin, float LocalTMax, float LocalToWorldScale, FMajorantData MajorantData, inout FRandomSequence RandSequence)`
- L76-128 _function_ `FVolumeTrackingResult HeterogeneousVolumesRatioTracking(float3 PathThroughput, float3 TranslatedWorldOrigin, float3 WorldDirection, float LocalTMax, float LocalToWorldScale, FMajorantData MajorantData, inout FRandomSequence RandSequence)`

### `Shaders/Private/PathTracing/Volume/PathTracingVolume.ush` (Private)

- lines: 341; parse: all-branches
- includes: L5 `PathTracingVolumeCommon.ush`, L6 `PathTracingAtmosphere.ush`, L7 `PathTracingClouds.ush`, L8 `PathTracingFog.ush`, L9 `PathTracingHeterogeneousVolumes.ush`, L10 `PathTracingVolumeSampling.ush`

#### Macros (#define, 3)

- L90 `#define PATH_TRACER_REFERENCE_TRANSMITTANCE_LOOP_BODY(GetDensityFunc) float3 ColorChannelPdf = Throughput; float RandValue = RandSequence.Get1D(); float DeltaT = SampleSpectralTransmittance(RandValue.x, SigmaBar, ColorChannelPdf); if (DeltaT < 0.0) { break; } if (TMin + ...` (36 lines)
- L130 `#define PATH_TRACER_REFERENCE_TRANSMITTANCE_LOOP(GetDensityBoundsFunc, GetDensityFunc) for (int Step = 0; Step < MaxRaymarchSteps; Step++) { float3 SigmaBar = GetDensityBoundsFunc(Origin, Direction, TMin, TMax).SigmaMax; PATH_TRACER_REFERENCE_TRANSMITTANCE_LOOP_BODY(GetDensityFunc); }` (7 lines)
- L139 `#define PATH_TRACER_REFERENCE_TRANSMITTANCE_LOOP_CONSTANT_BOUNDS(GetDensityFunc) for (int Step = 0; Step < MaxRaymarchSteps; Step++) { PATH_TRACER_REFERENCE_TRANSMITTANCE_LOOP_BODY(GetDensityFunc); }` (6 lines)
- L3 #pragma `once`

#### Global parameters (uniforms) (2)

- L12 _parameter_ `uint VolumeFlags;`
- L13 _parameter_ `int MaxRaymarchSteps;`

#### Functions (8)

- L17-38 _function_ `FVolumeIntersectionList VolumeIntersect(float3 Origin, float3 Direction, float TMin, float TMax, float PathRoughness, uint VolumeMask)` — Given an input ray, figure out where the provided volume intersects it
- L40-45 _function_ `FPackedPathTracingPayload VolumeGetBlockerHit(float3 Origin, float3 Direction, float HitT, bool bIsCameraRay)`
- L48-68 _function_ `FVolumeDensityBounds VolumeGetDensityBounds(float3 Origin, float3 Direction, FVolumeIntersectionInterval Interval)` — Given an input ray, figure out the bounds on density. The T interval may be smaller than the one returned by VolumeIntersect
- L71-87 _function_ `FVolumeShadedResult VolumeGetDensity(float3 TranslatedWorldPos, int HeterogeneousVolumesIndex, uint VolumeMask, bool bIsCameraRay)` — Given a point in world space, return the amount of volume and its scattering properties
- L149-187 _function_ `float3 VolumeGetTransmittance(float3 StartThroughput, float3 Origin, float3 Direction, FVolumeIntersectionInterval Interval, inout FRandomSequence RandSequence)` — The returned value factors in the initial throughput. This is used to avoid sampling too much if throughput reaches 0. Return the transmittance along a ray segment
- L191-241 _function_ `float3 VolumeGetTransmittance(float3 StartThroughput, float3 Origin, float3 Direction, FVolumeIntersectionList IntersectionList, inout FRandomSequence RandSequence, float CloudFactor)` — Return the transmittance along a whole intersection list Each volume type has its own range unlike the function above. This is used for shadow rays, so this version adds the CloudFactor for cloud shadows
- L243-290 _function_ `FVolumeShadedResult VolumeGetDensityAndTransmittance(float3 Origin, float3 Direction, FVolumeIntersectionInterval Interval, uint Bounce, inout FRandomSequence RandSequence, inout float3 Throughput, inout float CloudFactor)`
- L292-340 _function_ `FVolumeTrackingResult VolumeSampleDistance(float3 PathThroughput, float3 Origin, float3 Direction, FVolumeIntersectionInterval Interval, bool bIsCameraRay, inout FRandomSequence RandSequence)`

### `Shaders/Private/PathTracing/Volume/PathTracingVolumeCommon.ush` (Private)

- lines: 294; parse: all-branches
- L3 #pragma `once`

#### Structs / classes (6)

- L5-21 _struct_ **`FVolumeIntersection`** `struct FVolumeIntersection`
  - L7 _member_ `float VolumeTMin;`
  - L8 _member_ `float VolumeTMax;`
  - L9 _member_ `float BlockerHitT;`
  - L10 _member_ `float MaxDensity;`
  - L12 _method_ `bool HitVolume()`
  - L17 _method_ `bool HitBlocker()`
- L48-54 _struct_ **`FVolumeIntersectionInterval`** `struct FVolumeIntersectionInterval` — representes an interval along the ray over which the specified volumes are known to exist
  - L50 _member_ `float VolumeTMin;`
  - L51 _member_ `float VolumeTMax;`
  - L52 _member_ `uint VolumeMask;`
  - L53 _member_ `float CloudDensity;`
- L56-187 _struct_ **`FVolumeIntersectionList`** `struct FVolumeIntersectionList`
  - L58 _member_ `float4 VolumeTMin;`
  - L59 _member_ `float4 VolumeTMax;`
  - L60 _member_ `float CloudDensity;`
  - L61 _member_ `uint VolumeMask;`
  - L64 _member_ `float BlockerHitT;` — only need to track one blocker (assume they are opaque)
  - L66 _method_ `bool HitVolume()`
  - L71 _method_ `bool HitBlocker()`
  - L76 _method_ `void Add(uint ID, FVolumeIntersection VolumeIntersection)`
  - L99 _method_ `FVolumeIntersectionInterval GetCurrentInterval()` — Return the interval of TValues closest to the front of the list
  - L162 _method_ `FVolumeIntersectionList Update(float T)` — Update all active intervals, knowing we have processed everything up to distance 'T'
- L196-200 _struct_ **`FVolumeDensityBounds`** `struct FVolumeDensityBounds` — Represent a strict lower and upper bound on the values that can be returned by VolumeGetDensity along the given ray
  - L198 _member_ `float3 SigmaMin;` — minorant (control extinction)
  - L199 _member_ `float3 SigmaMax;` — majorant (upper bound)
- L219-229 _struct_ **`FVolumeShadedResult`** `struct FVolumeShadedResult` — The result of sampling a volume at a given point See PathTracingMedium.usf for the implementation of the scattering model
  - L221 _member_ `float3 SigmaT;` — extinction
  - L222 _member_ `float3 SigmaH;` — holdout density
  - L223 _member_ `float3 SigmaSRayleigh;` — Rayleight scattering coefficient
  - L224 _member_ `float3 SigmaSHG;` — Henyey-Greenstein scattering coefficient (for atmosphere, fog and heterogeneous volumes)
  - L225 _member_ `float3 SigmaSDualHG;` — Dual Henyey-Greenstein scattering coefficient (for clouds)
  - L226 _member_ `float3 Emission;`
  - L227 _member_ `float PhaseG;` — 'g' term for HG lobe
  - L228 _member_ `float3 DualPhaseData;` — g1,g2,blend for DualHG lobe
- L282-288 _struct_ **`FVolumeSegment`** `struct FVolumeSegment` — represent a stochastically chosen volume element that is guaranteed to lie between
  - L284 _member_ `float3 Throughput;` — path contribution from the start of the volume segment
  - L285 _member_ `FVolumeIntersectionInterval Interval;`
  - L287 _method_ `bool IsValid()`

#### Functions (9)

- L23-30 _function_ `FVolumeIntersection CreateVolumeIntersection(float TMin, float TMax, float BlockerT = 0.0)`
- L32-39 _function_ `FVolumeIntersection CreateVolumeIntersectionWithDensity(float TMin, float TMax, float MaxDensity)`
- L41-44 _function_ `FVolumeIntersection CreateEmptyVolumeIntersection()`
- L189-192 _function_ `FVolumeIntersectionList CreateEmptyVolumeIntersectionList()`
- L202-208 _function_ `FVolumeDensityBounds CreateVolumeDensityBound(float3 SigmaMin, float3 SigmaMax)`
- L210-214 _function_ `void MergeVolumeDensityBounds(inout FVolumeDensityBounds Merged, FVolumeDensityBounds Other)`
- L232-253 _function_ `FPathTracingPayload CreateMediumHitPayload(float HitT, float3 TranslatedWorldPos, FVolumeShadedResult ShadedResult)`
- L256-279 _function_ `void MergeVolumeShadedResult(inout FVolumeShadedResult M, FVolumeShadedResult R, bool bAsHoldout)` — Merge the shaded result "R" into "M"
- L290-293 _function_ `FVolumeSegment CreateEmptyVolumeSegment()`

### `Shaders/Private/PathTracing/Volume/PathTracingVolumeSampling.ush` (Private)

- lines: 63; parse: all-branches
- L3 #pragma `once`

#### Functions (4)

- L7-35 _function_ `float SampleSpectralTransmittance(float RandValue, float3 Sigma, float3 ColorChannelPdf)` — Returns a distance sampled proportionally to transmittance with an extinction of Sigma, using the provided color channel pdf for weighting the probabilities
- L38-46 _function_ `float4 EvaluateSpectralTransmittanceHit(float SampledT, float3 Sigma, float3 ColorChannelPdf)`
- L48-56 _function_ `float4 EvaluateSpectralTransmittanceMiss(float MaxT, float3 Sigma, float3 ColorChannelPdf)`
- L59-63 _function_ `float LowThroughputClampFactor(float3 Throughput)` — Factor to multiply the path throughput by so that paths that have low overall contribution can get terminated earlier
