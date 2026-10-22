# Shaders / Shaders/Private/HeterogeneousVolumes

- files: 35; lines: 11425
- record kinds: cpp_binding=49, define=177, entry=51, function=451, groupshared=11, include=131, macro_call=1, member=148, method=7, parameter=209, resource=103, struct=34

### `Shaders/Private/HeterogeneousVolumes/HeterogeneousVolumesAdaptiveVolumetricShadowMapSampler.ush` (Private)

- lines: 512; parse: all-branches
- includes: L5 `HeterogeneousVolumesAdaptiveVolumetricShadowMapUtils.ush`, L6 `HeterogeneousVolumesAdaptiveVolumetricShadowMapSampling.ush`

#### Macros (#define, 3)

- L9 `#define AVSM_BILINEAR_INTERPOLATION 1` _[#if !defined(AVSM_BILINEAR_INTERPOLATION)]_
- L12 `#define INVALID_SAMPLE_INDEX 0xFFu`
- L13 `#define INVALID_SAMPLE_INDEX4 0xFFFFFFFFu`
- L3 #pragma `once`

#### Structs / classes (2)

- L17-31 _struct_ **`FAVSM_Sampler`** `struct FAVSM_Sampler` — Reference single-channel implementation _[#if 0]_
  - L19 _member_ `FAdaptiveVolumetricShadowMap ShadowMap;` _[#if 0]_
  - L20 _member_ `uint PixelOffset;` _[#if 0]_
  - L21 _member_ `uint SampleCount;` _[#if 0]_
  - L22 _member_ `uint SampleIndex;` _[#if 0]_
  - L25 _member_ `FAVSMSampleData SampleData[2];` — Query cache _[#if 0]_
  - L28 _member_ `int Face;` — Convenience creation data _[#if 0]_
  - L29 _member_ `int2 Pixel;` _[#if 0]_
  - L30 _member_ `float DepthOffset;` _[#if 0]_
- L132-149 _struct_ **`FAVSM_Sampler4`** `struct FAVSM_Sampler4` — Sampler4 implementation reduces VGPR usage
  - L134 _member_ `FAdaptiveVolumetricShadowMap ShadowMap;`
  - L135 _member_ `uint4 PixelOffset4;`
  - L136 _member_ `uint SampleCount4;`
  - L137 _member_ `float4 BeginX4;`
  - L138 _member_ `float4 EndX4;`
  - L139 _member_ `uint SampleIndex4;`
  - L142 _member_ `uint4 SampleData0Packed4;` — Query cache
  - L143 _member_ `uint4 SampleData1Packed4;`
  - L146 _member_ `int Face;` — Convenience creation data
  - L147 _member_ `float2 Pixel;`
  - L148 _member_ `float DepthOffset;`

#### Functions (32)

- L33-36 _function_ `bool IsValid(FAVSM_Sampler Iterator)` _[#if 0]_
- L38-71 _function_ `FAVSM_Sampler AVSM_Sampler_Create( inout FAdaptiveVolumetricShadowMap ShadowMap, int Face, int2 Pixel, float DepthOffset )` _[#if 0]_
- L73-91 _function_ `float AVSM_Sampler_Eval(inout FAVSM_Sampler Iterator, float X)` _[#if 0]_
- L93-111 _function_ `FAVSMSampleData AVSM_Sampler_EvalInverse(inout FAVSM_Sampler Iterator, float Tau)` _[#if 0]_
- L113-128 _function_ `float AVSM_Sampler_Last(inout FAVSM_Sampler Iterator)` _[#if 0]_
- L151-155 _function_ `uint AVSM_Sampler4_GetSampleIndex(inout FAVSM_Sampler4 Sampler4, uint Index)`
- L157-165 _function_ `void AVSM_Sampler4_SetSampleIndex(inout FAVSM_Sampler4 Sampler4, int4 SampleIndex4)`
- L167-172 _function_ `void AVSM_Sampler4_SetSampleIndex(inout FAVSM_Sampler4 Sampler4, uint Index, uint SampleIndex)`
- L174-178 _function_ `uint AVSM_Sampler4_GetSampleCount(inout FAVSM_Sampler4 Sampler4, uint Index)`
- L180-184 _function_ `float AVSM_Sampler4_GetBeginX(inout FAVSM_Sampler4 Sampler4, uint Index)`
- L186-190 _function_ `float AVSM_Sampler4_GetEndX(inout FAVSM_Sampler4 Sampler4, uint Index)`
- L192-195 _function_ `bool AVSM_Sampler4_IsValid(inout FAVSM_Sampler4 Sampler4, uint Index)`
- L197-205 _function_ `void AVSM_Sampler4_SetSampleCount(inout FAVSM_Sampler4 Sampler4, int4 SampleCount4)`
- L207-211 _function_ `uint AVSM_Sampler4_GetPixelOffset(inout FAVSM_Sampler4 Sampler4, uint Index)`
- L213-216 _function_ `void AVSM_Sampler4_SetPixelOffset(inout FAVSM_Sampler4 Sampler4, uint4 PixelOffset)`
- L218-221 _function_ `void AVSM_Sampler4_SetBeginX(inout FAVSM_Sampler4 Sampler4, float4 BeginX4)`
- L223-226 _function_ `void AVSM_Sampler4_SetEndX(inout FAVSM_Sampler4 Sampler4, float4 EndX4)`
- L228-240 _function_ `FAVSMSampleData AVSM_Sampler4_GetSampleData0(inout FAVSM_Sampler4 Sampler4, uint Index)`
- L242-245 _function_ `void AVSM_Sampler4_SetSampleData0(inout FAVSM_Sampler4 Sampler4, uint4 SampleDataPacked4)`
- L247-250 _function_ `void AVSM_Sampler4_SetSampleData0(inout FAVSM_Sampler4 Sampler4, uint Index, uint SampleDataPacked)`
- L252-264 _function_ `FAVSMSampleData AVSM_Sampler4_GetSampleData1(inout FAVSM_Sampler4 Sampler4, uint Index)`
- L266-269 _function_ `void AVSM_Sampler4_SetSampleData1(inout FAVSM_Sampler4 Sampler4, uint4 SampleDataPacked4)`
- L271-274 _function_ `void AVSM_Sampler4_SetSampleData1(inout FAVSM_Sampler4 Sampler4, uint Index, uint SampleDataPacked)`
- L276-340 _function_ `FAVSM_Sampler4 AVSM_Sampler4_Create( inout FAdaptiveVolumetricShadowMap ShadowMap, int Face, float2 Pixel, float DepthOffset )`
- L342-379 _function_ `float AVSM_Sampler4_Eval_Internal(inout FAVSM_Sampler4 Sampler4, int Index, float X)`
- L381-388 _function_ `float AVSM_Bilinear_Interpolate(float Value[4], float2 Weight)`
- L390-403 _function_ `float AVSM_Sampler4_Eval(inout FAVSM_Sampler4 Sampler4, float X)`
- L405-409 _function_ `float AVSM_Sampler4_Eval_NoInterpolation(inout FAVSM_Sampler4 Sampler4, float X)`
- L411-446 _function_ `FAVSMSampleData AVSM_Sampler4_EvalInverse_Internal(inout FAVSM_Sampler4 Sampler4, int Index, float Tau)`
- L448-461 _function_ `FAVSMSampleData AVSM_Sampler4_EvalInverse(inout FAVSM_Sampler4 Sampler4, float Tau)`
- L463-487 _function_ `FAVSMSampleData AVSM_Sampler4_Last_Internal(inout FAVSM_Sampler4 Sampler4, int Index)`
- L489-511 _function_ `FAVSMSampleData AVSM_Sampler4_Last(inout FAVSM_Sampler4 Sampler4)`

### `Shaders/Private/HeterogeneousVolumes/HeterogeneousVolumesAdaptiveVolumetricShadowMapSampling.ush` (Private)

- lines: 915; parse: first-branch
- includes: L5 `HeterogeneousVolumesAdaptiveVolumetricShadowMapUtils.ush`, L6 `HeterogeneousVolumesBeerShadowMapUtils.ush`

#### Macros (#define, 11)

- L8 `#define AVSM_SAMPLE_MODE_DISABLED 0`
- L9 `#define AVSM_SAMPLE_MODE_TWO_LEVEL_VECTORIZED 1`
- L10 `#define AVSM_SAMPLE_MODE_TWO_LEVEL_VECTORIZED_LOOP 2`
- L16 `#define AVSM_SAMPLE_MODE AVSM_SAMPLE_MODE_TWO_LEVEL_VECTORIZED_LOOP` _[#if !defined(AVSM_SAMPLE_MODE)]_
- L89 `#define INTERPOLANT_TYPE_LINEAR 0`
- L90 `#define INTERPOLANT_TYPE_EXPONENTIAL 1`
- L91 `#define INTERPOLANT_TYPE_EXPONENTIAL_FIT 2`
- L92 `#define INTERPOLANT_TYPE INTERPOLANT_TYPE_EXPONENTIAL_FIT`
- L507 `#define BILINEAR_INTERPOLATION 1`
- L733 `#define BILINEAR_INTERPOLATION 1`
- L854 `#define BILINEAR_INTERPOLATION 1`
- L3 #pragma `once`

#### Structs / classes (2)

- L21-39 _struct_ **`FAdaptiveVolumetricShadowMap`** `struct FAdaptiveVolumetricShadowMap`
  - L23 _member_ `float4x4 TranslatedWorldToShadow[6];`
  - L24 _member_ `float3 TranslatedWorldOrigin[6];`
  - L25 _member_ `float4 TranslatedWorldPlane[6];`
  - L26 _member_ `float4 SplitDepths[6];`
  - L27 _member_ `float DownsampleFactor;`
  - L29 _member_ `int2 Resolution;`
  - L30 _member_ `int NumShadowMatrices;`
  - L31 _member_ `int MaxSampleCount;`
  - L32 _member_ `bool bIsEmpty;`
  - L33 _member_ `bool bIsDirectionalLight;`
  - L35 _member_ `StructuredBuffer<uint4> IndirectionBuffer;`
  - L36 _member_ `StructuredBuffer<uint> SampleBuffer;`
  - L37 _member_ `Texture2D<float4> RadianceTexture;`
  - L38 _member_ `SamplerState TextureSampler;`
- L622-639 _struct_ **`FBeerShadowMap`** `struct FBeerShadowMap`
  - L624 _member_ `float4x4 TranslatedWorldToShadow[6];`
  - L625 _member_ `float3 TranslatedWorldOrigin[6];`
  - L626 _member_ `float4 TranslatedWorldPlane[6];`
  - L627 _member_ `float4 SplitDepths[6];`
  - L628 _member_ `float DownsampleFactor;`
  - L630 _member_ `int2 Resolution;`
  - L631 _member_ `int NumShadowMatrices;`
  - L632 _member_ `int MaxSampleCount;`
  - L633 _member_ `bool bIsEmpty;`
  - L634 _member_ `bool bIsDirectionalLight;`
  - L636 _member_ `Texture2D<float4> BeerShadowMapTexture;`
  - L637 _member_ `Texture2D<float4> RadianceTexture;`
  - L638 _member_ `SamplerState TextureSampler;`

#### Functions (21)

- L41-67 _function_ `bool AVSM_PixelAndDepth( inout FAdaptiveVolumetricShadowMap ShadowMap, int Face, float3 TranslatedWorldPosition, inout float2 Pixel, inout float Depth )`
- L69-77 _function_ `uint AVSM_LinearIndex( inout FAdaptiveVolumetricShadowMap ShadowMap, uint Face, uint2 PixelCoord )`
- L79-82 _function_ `float SafeRcp(float Value)`
- L84-87 _function_ `float SafeLog(float Value)`
- L94-129 _function_ `float Interpolate( FAVSMSampleData ShadowData[2], float WorldHitT )`
- L131-178 _function_ `float AVSM_Sample_Reference( inout FAdaptiveVolumetricShadowMap ShadowMap, int Face, int2 Pixel, float WorldHitT )`
- L180-235 _function_ `float AVSM_Sample_BinarySearch( inout FAdaptiveVolumetricShadowMap ShadowMap, int Face, int2 Pixel, float WorldHitT )`
- L237-302 _function_ `float AVSM_Sample_TwoLevel_Reference( inout FAdaptiveVolumetricShadowMap ShadowMap, int Face, int2 Pixel, float WorldHitT )` _[#if 0]_
- L305-404 _function_ `float AVSM_Sample_TwoLevel_Vectorized( inout FAdaptiveVolumetricShadowMap ShadowMap, int Face, int2 Pixel, float WorldHitT )`
- L406-425 _function_ `float AVSM_Sample( inout FAdaptiveVolumetricShadowMap ShadowMap, int Face, int2 Pixel, float WorldHitT )`
- L427-538 _function_ `float AVSM_SampleTransmittance( inout FAdaptiveVolumetricShadowMap ShadowMap, float3 TranslatedWorldPosition, float3 LightTranslatedWorldPosition )`
- L540-564 _function_ `FAdaptiveVolumetricShadowMap GetAdaptiveVolumetricShadowMap()`
- L566-592 _function_ `FAdaptiveVolumetricShadowMap GetAdaptiveVolumetricShadowMapForCamera()`
- L594-601 _function_ `float AVSM_SampleTransmittance( float3 TranslatedWorldPosition, float3 LightTranslatedWorldPosition )`
- L603-618 _function_ `float4 AVSM_SampleCameraRadianceAndTransmittance4( float2 ScreenUV, float3 TranslatedWorldPosition, float3 LightTranslatedWorldPosition )`
- L641-663 _function_ `FBeerShadowMap GetBeerShadowMap()`
- L665-686 _function_ `float BeerShadowMap_Sample( inout FBeerShadowMap ShadowMap, float2 UV, float ShadowZ )`
- L688-765 _function_ `float BeerShadowMap_SampleTransmittanceSimple( inout FBeerShadowMap ShadowMap, float3 TranslatedWorldPosition, float3 LightTranslatedWorldPosition )`
- L767-888 _function_ `float BeerShadowMap_SampleTransmittance( inout FBeerShadowMap ShadowMap, float3 TranslatedWorldPosition, float3 LightTranslatedWorldPosition )`
- L890-897 _function_ `float BeerShadowMap_SampleTransmittance( float3 TranslatedWorldPosition, float3 LightTranslatedWorldPosition )`
- L899-914 _function_ `float4 BeerShadowMap_SampleCameraRadianceAndTransmittance4( float2 ScreenUV, float3 TranslatedWorldPosition, float3 LightTranslatedWorldPosition )`

### `Shaders/Private/HeterogeneousVolumes/HeterogeneousVolumesAdaptiveVolumetricShadowMapUtils.ush` (Private)

- lines: 154; parse: all-branches

#### Macros (#define, 2)

- L5 `#define AVSM_NULL_PTR 0xFF`
- L13 `#define AVSM_INVALID_PIXEL_OFFSET 0x3FFFFFF`
- L3 #pragma `once`

#### Structs / classes (2)

- L7-11 _struct_ **`FAVSMSampleData`** `struct FAVSMSampleData`
  - L9 _member_ `float X;`
  - L10 _member_ `float Tau;`
- L15-21 _struct_ **`FAVSMIndirectionData`** `struct FAVSMIndirectionData`
  - L17 _member_ `uint PixelOffset;`
  - L18 _member_ `int SampleCount;`
  - L19 _member_ `float BeginX;`
  - L20 _member_ `float EndX;`

#### Functions (18)

- L25-31 _function_ `FAVSMSampleData AVSM_CreateSampleData(float X, float Tau)`
- L33-36 _function_ `FAVSMSampleData AVSM_CreateSampleData(float X, float3 Transmittance)`
- L38-44 _function_ `uint AVSM_PackSampleDataX(float X, FAVSMIndirectionData IndirectionData)`
- L46-52 _function_ `float AVSM_UnpackSampleDataX(uint FixedX, FAVSMIndirectionData IndirectionData)`
- L54-60 _function_ `int AVSM_PackSampleData(FAVSMSampleData SampleData, FAVSMIndirectionData IndirectionData)`
- L62-68 _function_ `FAVSMSampleData AVSM_UnpackSampleData(int PackedData, FAVSMIndirectionData IndirectionData)`
- L70-73 _function_ `int AVSM_PackSampleData(float X, float Tau, FAVSMIndirectionData IndirectionData)`
- L77-83 _function_ `FAVSMSampleData AVSM_GetLinkedListSampleData(uint2 PackedData)`
- L85-90 _function_ `void AVSM_SetLinkedListSampleData(inout uint2 PackedData, FAVSMSampleData SampleData)`
- L92-95 _function_ `uint AVSM_GetLinkedListPrevPtr(uint2 PackedData)`
- L97-100 _function_ `uint AVSM_GetLinkedListNextPtr(uint2 PackedData)`
- L102-106 _function_ `void AVSM_SetLinkedListPrevPtr(inout uint2 PackedData, uint PrevPtr)`
- L108-112 _function_ `void AVSM_SetLinkedListNextPtr(inout uint2 PackedData, uint NextPtr)`
- L116-124 _function_ `FAVSMIndirectionData AVSM_CreateIndirectionData(uint PixelOffset, int SampleCount, float BeginX, float EndX)`
- L126-133 _function_ `uint4 AVSM_PackIndirectionData(FAVSMIndirectionData IndirectionData)`
- L135-143 _function_ `FAVSMIndirectionData AVSM_UnpackIndirectionData(uint4 PackedData)`
- L145-148 _function_ `int Align4(int Value)`
- L150-154 _function_ `int CalcTopLevelSampleCount(int SampleCount)`

### `Shaders/Private/HeterogeneousVolumes/HeterogeneousVolumesAmbientOcclusionPipeline.usf` (Private)

- lines: 414; parse: all-branches
- includes: L3 `../Common.ush`, L7 `/Engine/Generated/Material.ush`, L8 `HeterogeneousVolumesStochasticFiltering.ush`, L9 `HeterogeneousVolumesLiveShadingUtils.ush`, L10 `HeterogeneousVolumesTracingUtils.ush`, L11 `HeterogeneousVolumesLightingUtils.ush`, L12 `../BlueNoise.ush`, L266 `HeterogeneousVolumesRayMarchingUtils.ush`

#### Macros (#define, 11)

- L5 `#define SUPPORT_CONTACT_SHADOWS 0`
- L15 `#define THREADGROUP_SIZE_1D 1` _[#if !defined(THREADGROUP_SIZE_1D)]_
- L19 `#define THREADGROUP_SIZE_2D 1` _[#if !defined(THREADGROUP_SIZE_2D)]_
- L23 `#define THREADGROUP_SIZE_3D 1` _[#if !defined(THREADGROUP_SIZE_3D)]_
- L27 `#define USE_EXISTENCE_MASK 1` _[#if !defined(USE_EXISTENCE_MASK)]_
- L229 `#define INDIRECT_LIGHTING_MODE_OFF 0`
- L230 `#define INDIRECT_LIGHTING_MODE_LIGHTING_CACHE 1`
- L231 `#define INDIRECT_LIGHTING_MODE_SINGLE_SCATTERING 2`
- L257 `#define FOG_INSCATTERING_MODE_OFF 0`
- L258 `#define FOG_INSCATTERING_MODE_REFERENCE 1`
- L259 `#define FOG_INSCATTERING_MODE_LINEAR_APPROX 2`

#### Entry points (2)

- L312-365 _entry_ `[numthreads(THREADGROUP_SIZE_3D, THREADGROUP_SIZE_3D, THREADGROUP_SIZE_3D)] void RenderAmbientOcclusionWithLiveShadingCS( uint3 DispatchThreadId : SV_DispatchThreadID )` — stage: **compute** — C++: `FRenderAmbientOcclusionWithLiveShadingCS` SF_Compute via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/HeterogeneousVolumes/HeterogeneousVolumesAmbientOcclusionPipeline.cpp:534)
- L369-413 _entry_ `[numthreads(THREADGROUP_SIZE_3D, THREADGROUP_SIZE_3D, THREADGROUP_SIZE_3D)] void RenderExistenceMaskWithLiveShadingCS( uint3 DispatchThreadId : SV_DispatchThreadID )` — stage: **compute** — C++: `FRenderExistenceMaskWithLiveShadingCS` SF_Compute via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/HeterogeneousVolumes/HeterogeneousVolumesAmbientOcclusionPipeline.cpp:234)

#### Structs / classes (1)

- L144-148 _struct_ **`FVolumeSampleContext`** `struct FVolumeSampleContext` — Material sampling hooks..
  - L146 _member_ `FMaterialPixelParameters MaterialParameters;`
  - L147 _member_ `FPixelMaterialInputs PixelMaterialInputs;`

#### Global resources (textures / buffers / samplers) (3)

- L55 _resource_ `Texture3D ExistenceMaskTexture;`
- L269 _resource_ `RWTexture3D<uint> RWAmbientOcclusionUIntTexture;` — Output
- L367 _resource_ `RWTexture3D<float> RWExistenceMaskTexture;`

#### Global parameters (uniforms) (19)

- L31 _parameter_ `float4x4 LocalToWorld;` — Object data
- L32 _parameter_ `float4x4 WorldToLocal;`
- L33 _parameter_ `float3 LocalBoundsOrigin;`
- L34 _parameter_ `float3 LocalBoundsExtent;`
- L35 _parameter_ `int PrimitiveId;`
- L38 _parameter_ `int3 VoxelResolution;` — Volume data
- L39 _parameter_ `int3 VoxelMin;`
- L40 _parameter_ `int3 VoxelMax;`
- L43 _parameter_ `float ShadowStepSize;` — Shadowing
- L44 _parameter_ `float ShadowStepFactor;`
- L47 _parameter_ `float MaxTraceDistance;` — Ray data
- L48 _parameter_ `float MaxShadowTraceDistance;`
- L49 _parameter_ `float StepSize;`
- L50 _parameter_ `float StepFactor;`
- L51 _parameter_ `int MaxStepCount;`
- L52 _parameter_ `int bJitter;`
- L53 _parameter_ `int StochasticFilteringMode;`
- L58 _parameter_ `int bIsOfflineRender;` — Optional cinematic features
- L61 _parameter_ `int2 NumRays;` — AO data

#### Functions (28)

- L63-66 _function_ `FPrimitiveSceneData GetPrimitiveData(FMaterialVertexParameters Parameters)`
- L68-71 _function_ `FPrimitiveSceneData GetPrimitiveData(FMaterialPixelParameters Parameters)`
- L73-76 _function_ `float4x4 GetLocalToWorld()`
- L78-81 _function_ `float4x4 GetWorldToLocal()`
- L83-86 _function_ `float3 GetLocalBoundsOrigin()`
- L88-91 _function_ `float3 GetLocalBoundsExtent()`
- L93-96 _function_ `int3 GetVolumeResolution()`
- L98-101 _function_ `float GetStepSize()`
- L103-106 _function_ `float GetShadowStepSize()`
- L108-111 _function_ `float GetStepFactor()`
- L113-116 _function_ `float GetShadowStepFactor()`
- L118-121 _function_ `float GetMaxTraceDistance()`
- L123-126 _function_ `float GetMaxShadowTraceDistance()`
- L128-131 _function_ `int GetStochasticFilteringMode()`
- L133-136 _function_ `float EvalAmbientOcclusion(float3 WorldPosition)`
- L138-141 _function_ `float GetIndirectInscatteringFactor()`
- L150-170 _function_ `FVolumeSampleContext CreateVolumeSampleContext(float3 LocalPosition, float3 WorldPosition, float3 WorldPosition_DDX, float3 WorldPosition_DDY, float MipLevel)`
- L172-183 _function_ `FVolumeSampleContext CreateVolumeSampleContext(float3 LocalPosition, float3 WorldPosition, float MipLevel)`
- L185-207 _function_ `FVolumeSampleContext CreateVolumeSampleContext(float3 LocalPosition, float3 WorldPosition, float3 FilterWidth, float MipLevel, float Rand, int StochasticFilteringMode)`
- L209-213 _function_ `float3 SampleExtinction(inout FVolumeSampleContext Context)`
- L215-219 _function_ `float3 SampleEmission(inout FVolumeSampleContext Context)`
- L221-225 _function_ `float3 SampleAlbedo(inout FVolumeSampleContext Context)`
- L233-236 _function_ `int GetIndirectLightingMode()`
- L238-245 _function_ `bool IsOfflineRender()`
- L247-250 _function_ `int ShouldApplyHeightFog()`
- L252-255 _function_ `int ShouldApplyVolumetricFog()`
- L261-264 _function_ `int GetFogInscatteringMode()`
- L271-310 _function_ `FRayMarchingContext CreateShadowRayMarchingContext( float3 WorldRayOrigin, float3 WorldToLight, uint MaxStepCount )`

### `Shaders/Private/HeterogeneousVolumes/HeterogeneousVolumesBeerShadowMapUtils.ush` (Private)

- lines: 108; parse: all-branches

#### Macros (#define, 2)

- L42 `#define BEER_SHADOW_MAP_COMBINE_METHOD_FIRST 0`
- L43 `#define BEER_SHADOW_MAP_COMBINE_METHOD_EXPAND 1`
- L3 #pragma `once`

#### Structs / classes (1)

- L6-10 _struct_ **`FBeerShadowMapData`** `struct FBeerShadowMapData` — Beer Shadow Map implementation
  - L8 _member_ `float T[2];`
  - L9 _member_ `float Tau[2];`

#### Functions (7)

- L12-20 _function_ `FBeerShadowMapData InitializeBeerShadowMapData(float Transmittance, float MaxTraceDistance)`
- L22-30 _function_ `FBeerShadowMapData UnpackBeerShadowMapData(float4 PackedData)`
- L32-40 _function_ `float4 PackBeerShadowMapData(FBeerShadowMapData Data)`
- L45-53 _function_ `FBeerShadowMapData ExpandBeerShadowMapData(FBeerShadowMapData Data0, FBeerShadowMapData Data1)`
- L55-58 _function_ `bool IsValid(FBeerShadowMapData Data)`
- L60-82 _function_ `FBeerShadowMapData FirstBeerShadowMapData(FBeerShadowMapData Data0, FBeerShadowMapData Data1)`
- L84-107 _function_ `FBeerShadowMapData CombineBeerShadowMapData(FBeerShadowMapData Data0, FBeerShadowMapData Data1, int CombineMethod)`

### `Shaders/Private/HeterogeneousVolumes/HeterogeneousVolumesComposite.usf` (Private)

- lines: 227; parse: all-branches
- includes: L3 `../Common.ush`, L4 `HeterogeneousVolumesAdaptiveVolumetricShadowMapSampling.ush`

#### Macros (#define, 7)

- L7 `#define UPSAMPLE_MODE 0` _[#if !defined(UPSAMPLE_MODE)]_
- L10 `#define UPSAMPLE_MODE_NEAREST 1`
- L11 `#define UPSAMPLE_MODE_BILINEAR 2`
- L14 `#define FILTER_MODE 0` _[#if !defined(FILTER_MODE)]_
- L17 `#define FILTER_MODE_BILATERAL 1`
- L18 `#define FILTER_MODE_GAUSSIAN_3X3 2`
- L19 `#define FILTER_MODE_GAUSSIAN_5x5 3`

#### Entry points (3)

- L43-65 _entry_ `[numthreads(THREADGROUP_SIZE_2D, THREADGROUP_SIZE_2D, 1)] void HeterogeneousVolumesUpsampleCS( uint2 GroupThreadId : SV_GroupThreadID, uint2 DispatchThreadId : SV_DispatchThreadID )` — stage: **compute** — C++: `FHeterogeneousVolumesUpsampleCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HeterogeneousVolumes/HeterogeneousVolumes.cpp:1456)
- L70-181 _entry_ `[numthreads(THREADGROUP_SIZE_2D, THREADGROUP_SIZE_2D, 1)] void HeterogeneousVolumesFilterCS( uint2 GroupThreadId : SV_GroupThreadID, uint2 DispatchThreadId : SV_DispatchThreadID )` — stage: **compute** — C++: `FHeterogeneousVolumesFilterCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HeterogeneousVolumes/HeterogeneousVolumes.cpp:1520)
- L193-226 _entry_ `[numthreads(THREADGROUP_SIZE_2D, THREADGROUP_SIZE_2D, 1)] void HeterogeneousVolumesCompositeCS( uint2 GroupThreadId : SV_GroupThreadID, uint2 DispatchThreadId : SV_DispatchThreadID )` — stage: **compute** — C++: `FHeterogeneousVolumesCompositeCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HeterogeneousVolumes/HeterogeneousVolumes.cpp:1579)

#### Global resources (textures / buffers / samplers) (7)

- L21 _resource_ `Texture2D SceneDepthTexture;`
- L22 _resource_ `Texture2D<float4> HeterogeneousVolumeRadiance;`
- L23 _resource_ `Texture2D<float> HeterogeneousVolumeHoldout;`
- L24 _resource_ `RWTexture2D<float4> RWColorTexture;`
- L37 _resource_ `RWTexture2D<float4> RWUpsampledTexture;`
- L38 _resource_ `SamplerState TextureSampler;`
- L68 _resource_ `RWTexture2D<float4> RWFilteredTexture;`

#### Global parameters (uniforms) (6)

- L25 _parameter_ `int DownsampleFactor;`
- L26 _parameter_ `int bUseAVSM;`
- L39 _parameter_ `uint2 UpsampledResolution;`
- L40 _parameter_ `uint2 UpsampledViewRect;`
- L41 _parameter_ `uint2 UpsampledViewRectMin;`
- L67 _parameter_ `int FilterWidth;`

#### Functions (3)

- L28-35 _function_ `float SampleTransmittance(uint2 ViewPixelCoord)`
- L183-186 _function_ `int2 GetDownsampledResolution(int2 Resolution, int Factor)`
- L188-191 _function_ `int2 GetScaledViewRect()`

### `Shaders/Private/HeterogeneousVolumes/HeterogeneousVolumesFrustumVoxelGrid.usf` (Private)

- lines: 78; parse: all-branches
- includes: L3 `HeterogeneousVolumesVoxelGridTypes.ush`, L5 `../Common.ush`, L6 `../DeferredShadingCommon.ush`, L7 `../ComputeShaderUtils.ush`, L8 `HeterogeneousVolumesTracingUtils.ush`, L9 `HeterogeneousVolumesVoxelGridTraversal.ush`

#### Entry points (1)

- L50-77 _entry_ `[numthreads(THREADGROUP_SIZE_3D, THREADGROUP_SIZE_3D, THREADGROUP_SIZE_3D)] void MarkTopLevelGridVoxelsForFrustumGridCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID )` — stage: **compute** — C++: `FMarkTopLevelGridVoxelsForFrustumGrid` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HeterogeneousVolumes/HeterogeneousVolumesVoxelGridPipeline.cpp:676) — Mark voxels which intersect a given primitive

#### Global resources (textures / buffers / samplers) (5)

- L13 _resource_ `StructuredBuffer<FTopLevelGridData> TopLevelGridBuffer;`
- L14 _resource_ `StructuredBuffer<FScalarGridData> ExtinctionGridBuffer;`
- L15 _resource_ `StructuredBuffer<FVectorGridData> EmissionGridBuffer;`
- L16 _resource_ `StructuredBuffer<FVectorGridData> ScatteringGridBuffer;`
- L21 _resource_ `RWStructuredBuffer<FTopLevelGridData> RWTopLevelGridBuffer;`

#### Global parameters (uniforms) (8)

- L11 _parameter_ `int3 TopLevelGridResolution;`
- L18 _parameter_ `float3 PrimitiveWorldBoundsMin;`
- L19 _parameter_ `float3 PrimitiveWorldBoundsMax;`
- L23 _parameter_ `float4x4 ViewToWorld;`
- L24 _parameter_ `int3 VoxelDimensions;`
- L26 _parameter_ `float TanHalfFOV;`
- L27 _parameter_ `float NearPlaneDepth;`
- L28 _parameter_ `float FarPlaneDepth;`

#### Functions (1)

- L30-47 _function_ `bool BoxIntersectsVoxel(float3 WorldBoxCenter, float WorldBoxRadius, uint3 VoxelIndex)`

### `Shaders/Private/HeterogeneousVolumes/HeterogeneousVolumesFrustumVoxelGridUtils.ush` (Private)

- lines: 163; parse: all-branches
- L3 #pragma `once`

#### Functions (16)

- L5-9 _function_ `float Exponential(float sigma, float x)`
- L11-16 _function_ `float InverseExponential(float sigma, float X)`
- L18-25 _function_ `float FindSigma(float x, float X)`
- L27-32 _function_ `float ExponentialRemap(float ViewDepth, float NearPlaneDepth, float FarPlaneDepth)`
- L34-39 _function_ `float InverseExponentialRemap(float NormalizedDepth, float NearPlaneDepth, float FarPlaneDepth)`
- L41-45 _function_ `float LinearRemap(float ViewDepth, float NearPlaneDepth, float FarPlaneDepth)`
- L47-51 _function_ `float InverseLinearRemap(float NormalizedDepth, float NearPlaneDepth, float FarPlaneDepth)`
- L53-64 _function_ `float SquareDistanceRemap(float ViewDepth, float NearPlaneDepth, float FarPlaneDepth)`
- L66-77 _function_ `float InverseSquareDistanceRemap(float NormalizedDepth, float NearPlaneDepth, float FarPlaneDepth)`
- L79-84 _function_ `float3 ScreenToVoxel(float3 ScreenPos, int3 VoxelDimensions)`
- L86-91 _function_ `float3 VoxelToScreen(float3 VoxelPos, int3 VoxelDimensions)`
- L93-98 _function_ `float PerspectiveRemap(float ViewDepth, int3 VoxelDimensions)`
- L100-105 _function_ `float InversePerspectiveRemap(float NormalizedDepth, int3 VoxelDimensions)`
- L107-127 _function_ `float3 ViewToVoxel(float3 ViewPos, int3 VoxelDimensions, float NearPlaneDepth, float FarPlaneDepth, float TanHalfFOV)`
- L129-147 _function_ `float3 VoxelToView(float3 VoxelPos, int3 VoxelDimensions, float NearPlaneDepth, float FarPlaneDepth, float TanHalfFOV)`
- L149-163 _function_ `float2 ClipRay(float3 Origin, float3 Direction, float TMin, float TMax, float4 Plane)`

### `Shaders/Private/HeterogeneousVolumes/HeterogeneousVolumesHardwareRayTracing.usf` (Private)

- lines: 637; parse: all-branches
- includes: L3 `HeterogeneousVolumesSparseVoxelUtils.ush`, L4 `../Common.ush`, L5 `../RayTracing/RayTracingCommon.ush`, L16 `../VirtualShadowMaps/VirtualShadowMapProjectionCommon.ush` [VIRTUAL_SHADOW_MAP], L19 `HeterogeneousVolumesSparseVoxelUniformBufferUtils.ush`, L20 `HeterogeneousVolumesTracingUtils.ush`, L21 `HeterogeneousVolumesLightingUtils.ush`, L446 `HeterogeneousVolumesRayMarchingUtils.ush` [RAYGENSHADER]

#### Macros (#define, 15)

- L7 `#define SUPPORT_CONTACT_SHADOWS 0`
- L9 `#define DYNAMICALLY_SHADOWED 1`
- L10 `#define TREAT_MAXDEPTH_UNSHADOWED 1`
- L12 `#define SHADOW_QUALITY 2`
- L13 `#define NO_TRANSLUCENCY_AVAILABLE `
- L24 `#define DIM_APPLY_SHADOW_TRANSMITTANCE 0` _[#if !defined(DIM_APPLY_SHADOW_TRANSMITTANCE)]_
- L27 `#define VOXEL_COUNT_MAX 6`
- L29 `#define SHADOW_BIT 0x80000000u`
- L422 `#define INDIRECT_LIGHTING_MODE_OFF 0` _[#if RAYGENSHADER]_
- L423 `#define INDIRECT_LIGHTING_MODE_LIGHTING_CACHE 1` _[#if RAYGENSHADER]_
- L424 `#define INDIRECT_LIGHTING_MODE_SINGLE_SCATTERING 2` _[#if RAYGENSHADER]_
- L436 `#define FOG_INSCATTERING_MODE_OFF 0` _[#if RAYGENSHADER]_
- L437 `#define FOG_INSCATTERING_MODE_REFERENCE 1` _[#if RAYGENSHADER]_
- L438 `#define FOG_INSCATTERING_MODE_LINEAR_APPROX 2` _[#if RAYGENSHADER]_
- L445 `#define HARDWARE_RAY_TRACING 1` _[#if RAYGENSHADER]_

#### Entry points (7)

- L112-121 _entry_ `RAY_TRACING_ENTRY_CLOSEST_HIT(SparseVoxelsClosestHitShader, FSparseVoxelPayload, Payload, FSparseVoxelIntersectionAttributes, Attributes)` — stage: **closesthit** — C++: `FHeterogeneousVolumesSparseVoxelsHitGroup` SF_RayHitGroup via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HeterogeneousVolumes/HeterogeneousVolumesHardwareRayTracing.cpp:295)
- L123-173 _entry_ `RAY_TRACING_ENTRY_ANY_HIT(SparseVoxelsAnyHitShader, FSparseVoxelPayload, Payload, FSparseVoxelIntersectionAttributes, Attributes)` — stage: **anyhit** — C++: `FHeterogeneousVolumesSparseVoxelsHitGroup` SF_RayHitGroup via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HeterogeneousVolumes/HeterogeneousVolumesHardwareRayTracing.cpp:295)
- L175-188 _entry_ `RAY_TRACING_ENTRY_INTERSECTION(SparseVoxelsIntersectionShader)` — stage: **intersection** — C++: `FHeterogeneousVolumesSparseVoxelsHitGroup` SF_RayHitGroup via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HeterogeneousVolumes/HeterogeneousVolumesHardwareRayTracing.cpp:295)
- L190-194 _entry_ `RAY_TRACING_ENTRY_MISS(SparseVoxelsMissShader, FSparseVoxelPayload, Payload)` — stage: **miss** — C++: `FHeterogeneousVolumesSparseVoxelMS` SF_RayMiss via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HeterogeneousVolumes/HeterogeneousVolumesHardwareRayTracing.cpp:321)
- L322-381 _entry_ `RAY_TRACING_ENTRY_RAYGEN(SparseVoxelsRayGenerationShader1)` — stage: **raygeneration** _[#if RAYGENSHADER]_
- L459-517 _entry_ `RAY_TRACING_ENTRY_RAYGEN(RenderLightingCacheWithPreshadingRGS)` — stage: **raygeneration** — C++: `FRenderLightingCacheWithPreshadingRGS` SF_RayGen via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HeterogeneousVolumes/HeterogeneousVolumesHardwareRayTracing.cpp:410) _[#if RAYGENSHADER]_
- L519-634 _entry_ `RAY_TRACING_ENTRY_RAYGEN(RenderSingleScatteringWithPreshadingRGS)` — stage: **raygeneration** — C++: `FRenderSingleScatteringWithPreshadingRGS` SF_RayGen via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HeterogeneousVolumes/HeterogeneousVolumesHardwareRayTracing.cpp:493) _[#if RAYGENSHADER]_

#### Structs / classes (2)

- L31-60 _struct_ **`FSparseVoxelPayload`** `struct FSparseVoxelPayload`
  - L33 _member_ `float HitT[2];`
  - L34 _member_ `uint VoxelID;`
  - L35 _member_ `uint Data;`
  - L36 _member_ `float3 Transmittance;`
  - L38 _method_ `void SetMiss()`
  - L39 _method_ `bool IsMiss()`
  - L40 _method_ `bool IsHit()`
  - L42 _method_ `void SetShadowRay()`
  - L46 _method_ `bool IsShadowRay()`
  - L51 _method_ `void SetTransmittance(float3 Transm)`
  - L56 _method_ `float3 GetTransmittance()`
- L100-103 _struct_ **`FSparseVoxelIntersectionAttributes`** `struct FSparseVoxelIntersectionAttributes`
  - L102 _member_ `float2 HitT;`

#### Global resources (textures / buffers / samplers) (3)

- L201 _resource_ `RaytracingAccelerationStructure TLAS;` — Scene _[#if RAYGENSHADER]_
- L211 _resource_ `RWTexture2D<float4> RWLightingTexture;` — Output _[#if RAYGENSHADER]_
- L457 _resource_ `RWTexture3D<float3> RWLightingCacheTexture;` _[#if RAYGENSHADER]_

#### Global parameters (uniforms) (9)

- L204 _parameter_ `int MaxStepCount;` — Ray data _[#if RAYGENSHADER]_
- L205 _parameter_ `int bJitter;` _[#if RAYGENSHADER]_
- L208 _parameter_ `int MipLevel;` — Volume sampling data _[#if RAYGENSHADER]_
- L384 _parameter_ `int bApplyEmissionAndTransmittance;` — Lighting _[#if RAYGENSHADER]_
- L385 _parameter_ `int bApplyDirectLighting;` _[#if RAYGENSHADER]_
- L386 _parameter_ `int bApplyShadowTransmittance;` _[#if RAYGENSHADER]_
- L387 _parameter_ `int LightType;` _[#if RAYGENSHADER]_
- L388 _parameter_ `float VolumetricScatteringIntensity;` _[#if RAYGENSHADER]_
- L391 _parameter_ `uint VirtualShadowMapId;` — Shadowing _[#if RAYGENSHADER]_

#### Functions (20)

- L63-70 _function_ `FSparseVoxelPayload CreateSparseVoxelPayload()`
- L72-80 _function_ `uint3 GetVolumeResolutionAtMip(uint MipLevel)`
- L82-86 _function_ `FVoxelData GetVoxelData(uint PrimitiveIndex, uint InstanceID)`
- L88-92 _function_ `float3 GetObjectBoundsMin()`
- L94-98 _function_ `float3 GetObjectBoundsMax()`
- L105-110 _function_ `FSparseVoxelIntersectionAttributes CreateVolumeIntersectionAttributes(float2 HitT)`
- L213-227 _function_ `FRayDesc CreateVolumeRay( float3 Origin, float3 Direction, float TMin, float TMax )` _[#if RAYGENSHADER]_
- L229-250 _function_ `void TraceVolumeRay( FRayDesc Ray, inout FSparseVoxelPayload Payload )` _[#if RAYGENSHADER]_
- L252-259 _function_ `void TraceVolumeShadowRay( FRayDesc Ray, inout FSparseVoxelPayload Payload )` _[#if RAYGENSHADER]_
- L265-307 _function_ `float3 hsv2rgb(float h, float s, float v)` — h = [0, 1], s = [0 ,1], v = [0, 1] h: hue, s: saturate v: value _[#if RAYGENSHADER]_
- L309-313 _function_ `float3 GetVoxelDebugColor(uint VoxelID)` _[#if RAYGENSHADER]_
- L315-320 _function_ `float3 GetVoxelDebugColor(uint3 VoxelIndex)` _[#if RAYGENSHADER]_
- L392-395 _function_ `uint GetVirtualShadowMapId()` _[#if RAYGENSHADER]_
- L397-409 _function_ `float3 ComputeTransmittanceHardwareRayTracing( float3 Origin, float3 Direction, float TMin, float TMax )` _[#if RAYGENSHADER]_
- L411-414 _function_ `float EvalAmbientOcclusion(float3 WorldPosition)` _[#if RAYGENSHADER]_
- L417-420 _function_ `bool UseInscatteringVolume()` — Cinematic feature options _[#if RAYGENSHADER]_
- L426-429 _function_ `int GetIndirectLightingMode()` _[#if RAYGENSHADER]_
- L431-434 _function_ `bool IsOfflineRender()` _[#if RAYGENSHADER]_
- L440-443 _function_ `int GetFogInscatteringMode()` _[#if RAYGENSHADER]_
- L448-455 _function_ `uint3 DispatchRaysToVoxelIndex(uint2 DispatchRaysIndex)` _[#if RAYGENSHADER]_

#### Top-level macro invocations (1)

- L61 _macro_call_ `CHECK_RT_PAYLOAD_SIZE(FSparseVoxelPayload)`

### `Shaders/Private/HeterogeneousVolumes/HeterogeneousVolumesLightingUtils.ush` (Private)

- lines: 14; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../DeferredLightingCommon.ush`, L5 `../LightGridCommon.ush`, L6 `../LightDataUniforms.ush`

#### Functions (1)

- L8-14 _function_ `FDeferredLightData InitDeferredLightFromUniforms(uint LightType, float VolumetricScatteringIntensity)`

### `Shaders/Private/HeterogeneousVolumes/HeterogeneousVolumesLiveShadingGlobalPipeline.usf` (Private)

- lines: 159; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../SceneTexturesCommon.ush`, L5 `HeterogeneousVolumesTracingUtils.ush`

#### Macros (#define, 3)

- L8 `#define THREADGROUP_SIZE_1D 1` _[#if !defined(THREADGROUP_SIZE_1D)]_
- L12 `#define THREADGROUP_SIZE_2D 1` _[#if !defined(THREADGROUP_SIZE_2D)]_
- L16 `#define THREADGROUP_SIZE_3D 1` _[#if !defined(THREADGROUP_SIZE_3D)]_

#### Entry points (3)

- L49-121 _entry_ `[numthreads(THREADGROUP_SIZE_2D, THREADGROUP_SIZE_2D, 1)] void ScreenTileClassificationCS( uint2 GroupId : SV_GroupID, uint2 GroupThreadId : SV_GroupThreadID, uint2 DispatchThreadId : SV_DispatchThreadID )` — stage: **compute** — C++: `FScreenTileClassificationCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HeterogeneousVolumes/HeterogeneousVolumesLiveShadingPipeline.cpp:1154)
- L127-134 _entry_ `[numthreads(THREADGROUP_SIZE_3D, THREADGROUP_SIZE_3D, THREADGROUP_SIZE_3D)] void ConvertTexture3DFixedPointToFloatCS( uint3 DispatchThreadId : SV_DispatchThreadID )` — stage: **compute** — C++: `FConvertTexture3DFixedPointToFloatCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HeterogeneousVolumes/HeterogeneousVolumesAmbientOcclusionPipeline.cpp:694)
- L140-158 _entry_ `[numthreads(THREADGROUP_SIZE_3D, THREADGROUP_SIZE_3D, THREADGROUP_SIZE_3D)] void DilateExistenceMaskCS( uint3 DispatchThreadId : SV_DispatchThreadID )` — stage: **compute** — C++: `FDilateExistenceMaskCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HeterogeneousVolumes/HeterogeneousVolumesAmbientOcclusionPipeline.cpp:384)

#### Structs / classes (1)

- L19-23 _struct_ **`FScreenTile`** `struct FScreenTile`
  - L22 _member_ `uint Id;` — TODO: This could be 16-bit..

#### Global resources (textures / buffers / samplers) (8)

- L39 _resource_ `RWBuffer<uint> RWNumScreenTilesBuffer;` — Output
- L40 _resource_ `RWStructuredBuffer<FScreenTile> RWScreenTileBuffer;`
- L123 _resource_ `uint3 TextureResolution;`
- L124 _resource_ `Texture3D<uint> UIntTexture3D;`
- L125 _resource_ `RWTexture3D<float> RWFloatTexture3D;`
- L136 _resource_ `Texture3D<float> ExistenceTexture;`
- L137 _resource_ `SamplerState TextureSampler;`
- L138 _resource_ `RWTexture3D<float> RWDilatedExistenceTexture;`

#### Global parameters (uniforms) (7)

- L26 _parameter_ `float4x4 LocalToWorld;` — Object data
- L27 _parameter_ `float4x4 WorldToLocal;`
- L28 _parameter_ `float3 LocalBoundsOrigin;`
- L29 _parameter_ `float3 LocalBoundsExtent;`
- L32 _parameter_ `float MaxTraceDistance;` — Ray data
- L35 _parameter_ `int3 GroupCount;` — Dispatch data
- L36 _parameter_ `int DownsampleFactor;`

#### groupshared (1)

- L42 _groupshared_ `groupshared uint GSNumRayHits;`

#### Functions (1)

- L44-47 _function_ `int2 GetDispatchSize()`

### `Shaders/Private/HeterogeneousVolumes/HeterogeneousVolumesLiveShadingPipeline.usf` (Private)

- lines: 916; parse: all-branches
- includes: L3 `HeterogeneousVolumesSparseVoxelUtils.ush`, L4 `../Common.ush`, L46 `/Engine/Generated/Material.ush`, L47 `HeterogeneousVolumesBeerShadowMapUtils.ush`, L48 `HeterogeneousVolumesStochasticFiltering.ush`, L49 `HeterogeneousVolumesLiveShadingUtils.ush`, L50 `HeterogeneousVolumesTracingUtils.ush`, L51 `HeterogeneousVolumesLightingUtils.ush`, L52 `../BlueNoise.ush`, L55 `../VirtualShadowMaps/VirtualShadowMapProjectionCommon.ush` [VIRTUAL_SHADOW_MAP], L427 `HeterogeneousVolumesRayMarchingUtils.ush`

#### Macros (#define, 29)

- L6 `#define SUPPORT_CONTACT_SHADOWS 0`
- L7 `#define EYE_ADAPTATION_LOOSE_PARAMETERS 1`
- L9 `#define DYNAMICALLY_SHADOWED 1`
- L10 `#define TREAT_MAXDEPTH_UNSHADOWED 1`
- L12 `#define SHADOW_QUALITY 2`
- L13 `#define NO_TRANSLUCENCY_AVAILABLE `
- L16 `#define SUPPORT_OVERLAPPING_VOLUMES 0` _[#if !defined(SUPPORT_OVERLAPPING_VOLUMES)]_
- L20 `#define ADAPTIVE_MARCH 0` _[#if !defined(ADAPTIVE_MARCH)]_
- L24 `#define REFERENCE_FAST_PATH 0` _[#if !defined(REFERENCE_FAST_PATH)]_
- L28 `#define DIM_USE_ADAPTIVE_VOLUMETRIC_SHADOW_MAP (AVSM_SAMPLE_MODE != 0)` _[#if !defined(DIM_USE_ADAPTIVE_VOLUMETRIC_SHADOW_MAP)]_
- L32 `#define USE_ANALYTIC_DERIVATIVES 0` _[#if !defined(USE_ANALYTIC_DERIVATIVES)]_
- L36 `#define DIM_WRITE_VELOCITY 0` _[#if !defined(DIM_WRITE_VELOCITY)]_
- L39 `#define USE_CAMERA_AVSM (DIM_USE_ADAPTIVE_VOLUMETRIC_SHADOW_MAP && (SUPPORT_OVERLAPPING_VOLUMES != 0))`
- L42 `#define AVSM AVSMs.AVSM` _[#if SUPPORT_OVERLAPPING_VOLUMES]_
- L43 `#define CameraAVSM AVSMs.CameraAVSM` _[#if SUPPORT_OVERLAPPING_VOLUMES]_
- L59 `#define THREADGROUP_SIZE_1D 1` _[#if !defined(THREADGROUP_SIZE_1D)]_
- L63 `#define THREADGROUP_SIZE_2D 1` _[#if !defined(THREADGROUP_SIZE_2D)]_
- L67 `#define THREADGROUP_SIZE_3D 1` _[#if !defined(THREADGROUP_SIZE_3D)]_
- L362 `#define HV_SCALABILITY_MODE_LOW 0`
- L363 `#define HV_SCALABILITY_MODE_HIGH 1`
- L364 `#define HV_SCALABILITY_MODE_EPIC 2`
- L365 `#define HV_SCALABILITY_MODE_CINEMATIC 3`
- L368 `#define HV_SCALABILITY_MODE HV_SCALABILITY_MODE_EPIC` _[#if !defined(HV_SCALABILITY_MODE)]_
- L381 `#define INDIRECT_LIGHTING_MODE_OFF 0`
- L382 `#define INDIRECT_LIGHTING_MODE_LIGHTING_CACHE 1`
- L383 `#define INDIRECT_LIGHTING_MODE_SINGLE_SCATTERING 2`
- L414 `#define FOG_INSCATTERING_MODE_OFF 0`
- L415 `#define FOG_INSCATTERING_MODE_REFERENCE 1`
- L416 `#define FOG_INSCATTERING_MODE_LINEAR_APPROX 2`

#### Entry points (3)

- L442-531 _entry_ `[numthreads(THREADGROUP_SIZE_3D, THREADGROUP_SIZE_3D, THREADGROUP_SIZE_3D)] void RenderLightingCacheWithLiveShadingCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID )` — stage: **compute** — C++: `FRenderLightingCacheWithLiveShadingCS` SF_Compute via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/HeterogeneousVolumes/HeterogeneousVolumesLiveShadingPipeline.cpp:499)
- L883-892 _entry_ `[numthreads(THREADGROUP_SIZE_2D, THREADGROUP_SIZE_2D, 1)] void RenderSingleScatteringWithLiveShadingCS( uint2 GroupThreadId : SV_GroupThreadID, uint2 DispatchThreadId : SV_DispatchThreadID )` — stage: **compute** — C++: `FRenderSingleScatteringWithLiveShadingDirectCS` SF_Compute via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/HeterogeneousVolumes/HeterogeneousVolumesLiveShadingPipeline.cpp:708)
- L901-914 _entry_ `[numthreads(THREADGROUP_SIZE_2D, THREADGROUP_SIZE_2D, 1)] void RenderSingleScatteringWithLiveShadingIndirectCS( uint GroupId : SV_GroupID, uint2 GroupThreadId : SV_GroupThreadID )` — stage: **compute**

#### Structs / classes (3)

- L138-146 _struct_ **`FDebugOutput`** `struct FDebugOutput`
  - L140 _member_ `int PrimitiveId;`
  - L141 _member_ `float3 LocalObjectBoundsMin;`
  - L142 _member_ `float3 LocalObjectBoundsMax;`
  - L143 _member_ `int Paddington;`
  - L144 _member_ `float4x4 LocalToWorld;`
  - L145 _member_ `float4x4 WorldToLocal;`
- L252-256 _struct_ **`FVolumeSampleContext`** `struct FVolumeSampleContext`
  - L254 _member_ `FMaterialPixelParameters MaterialParameters;`
  - L255 _member_ `FPixelMaterialInputs PixelMaterialInputs;`
- L894-897 _struct_ **`FScreenTile`** `struct FScreenTile`
  - L896 _member_ `uint Id;`

#### Global resources (textures / buffers / samplers) (9)

- L133 _resource_ `RWTexture2D<float4> RWLightingTexture;` — Output
- L134 _resource_ `RWTexture2D<float4> RWVelocityTexture;`
- L135 _resource_ `RWTexture2D<float> RWHoldoutTexture;`
- L136 _resource_ `RWTexture2D<float4> RWBeerShadowMapTexture;`
- L148 _resource_ `RWStructuredBuffer<FDebugOutput> RWDebugOutputBuffer;`
- L346 _resource_ `Texture3D AmbientOcclusionTexture;`
- L430 _resource_ `Texture3D ExistenceMaskTexture;`
- L431 _resource_ `RWTexture3D<float3> RWLightingCacheTexture;`
- L899 _resource_ `StructuredBuffer<FScreenTile> ScreenTileBuffer;`

#### Global parameters (uniforms) (41)

- L71 _parameter_ `float4x4 LocalToWorld;` — Object data
- L72 _parameter_ `float4x4 WorldToLocal;`
- L73 _parameter_ `float3 LocalBoundsOrigin;`
- L74 _parameter_ `float3 LocalBoundsExtent;`
- L75 _parameter_ `int PrimitiveId;`
- L78 _parameter_ `int3 VoxelResolution;` — Volume data
- L79 _parameter_ `int3 VoxelMin;`
- L80 _parameter_ `int3 VoxelMax;`
- L83 _parameter_ `int bHoldout;` — Lighting
- L84 _parameter_ `int bApplyEmissionAndTransmittance;`
- L85 _parameter_ `int bApplyDirectLighting;`
- L86 _parameter_ `int bApplyShadowTransmittance;`
- L87 _parameter_ `int LightType;`
- L88 _parameter_ `float VolumetricScatteringIntensity;`
- L91 _parameter_ `uint VirtualShadowMapId;` — Shadowing
- L97 _parameter_ `float ShadowStepSize;`
- L98 _parameter_ `float ShadowStepFactor;`
- L101 _parameter_ `int bApplyHeightFog;` — Atmosphere
- L102 _parameter_ `int bApplyVolumetricFog;`
- L103 _parameter_ `int bCreateBeerShadowMap;`
- L106 _parameter_ `float IndirectInscatteringFactor;` — Indirect
- L109 _parameter_ `float MaxTraceDistance;` — Ray data
- L110 _parameter_ `float MaxShadowTraceDistance;`
- L111 _parameter_ `float StepSize;`
- L112 _parameter_ `float StepFactor;`
- L113 _parameter_ `int MaxStepCount;`
- L114 _parameter_ `int bJitter;`
- L115 _parameter_ `int StochasticFilteringMode;`
- L118 _parameter_ `int3 GroupCount;` — Dispatch data
- L119 _parameter_ `int DownsampleFactor;`
- L122 _parameter_ `int bUseLightingCacheForInscattering;` — Optional cinematic features
- L123 _parameter_ `int IndirectLightingMode;`
- L124 _parameter_ `int bWriteVelocity;`
- L125 _parameter_ `int AVSMSampleMode;`
- L126 _parameter_ `int bSupportsOverlappingVolumes;`
- L127 _parameter_ `int bIsOfflineRender;`
- L128 _parameter_ `int FogInscatteringMode;`
- L129 _parameter_ `int bUseAnalyticDerivatives;`
- L130 _parameter_ `int bUseReferenceFastPath;`
- L345 _parameter_ `int3 AmbientOcclusionResolution;`
- L429 _parameter_ `uint bUseExistenceMask;`

#### Functions (35)

- L92-95 _function_ `uint GetVirtualShadowMapId()`
- L167-170 _function_ `FPrimitiveSceneData GetPrimitiveData(FMaterialVertexParameters Parameters)`
- L172-175 _function_ `FPrimitiveSceneData GetPrimitiveData(FMaterialPixelParameters Parameters)`
- L177-180 _function_ `float4x4 GetLocalToWorld()`
- L182-185 _function_ `float4x4 GetWorldToLocal()`
- L187-190 _function_ `float3 GetLocalBoundsOrigin()`
- L192-195 _function_ `float3 GetLocalBoundsExtent()`
- L197-200 _function_ `int3 GetVolumeResolution()`
- L202-205 _function_ `float GetStepSize()`
- L207-210 _function_ `float GetShadowStepSize()`
- L212-215 _function_ `float GetStepFactor()`
- L217-220 _function_ `float GetShadowStepFactor()`
- L222-225 _function_ `float GetMaxTraceDistance()`
- L227-230 _function_ `float GetMaxShadowTraceDistance()`
- L232-235 _function_ `int GetStochasticFilteringMode()`
- L237-240 _function_ `int ShouldApplyHeightFog()`
- L242-245 _function_ `int ShouldApplyVolumetricFog()`
- L247-250 _function_ `float GetIndirectInscatteringFactor()`
- L258-287 _function_ `FVolumeSampleContext CreateVolumeSampleContext( float3 LocalPosition, float3 WorldPosition, float3 WorldPosition_DDX, float3 WorldPosition_DDY, float MipLevel )`
- L289-301 _function_ `FVolumeSampleContext CreateVolumeSampleContext(float3 LocalPosition, float3 WorldPosition, float MipLevel)`
- L303-325 _function_ `FVolumeSampleContext CreateVolumeSampleContext(float3 LocalPosition, float3 WorldPosition, float3 FilterWidth, float MipLevel, float Rand, int StochasticFilteringMode)`
- L327-331 _function_ `float3 SampleExtinction(inout FVolumeSampleContext Context)`
- L333-337 _function_ `float3 SampleEmission(inout FVolumeSampleContext Context)`
- L339-343 _function_ `float3 SampleAlbedo(inout FVolumeSampleContext Context)`
- L348-360 _function_ `float EvalAmbientOcclusion(float3 WorldPosition)`
- L372-379 _function_ `bool UseInscatteringVolume()` — Cinematic feature options
- L385-394 _function_ `int GetIndirectLightingMode()`
- L396-403 _function_ `bool ShouldWriteVelocity()`
- L405-412 _function_ `bool IsOfflineRender()`
- L418-425 _function_ `int GetFogInscatteringMode()`
- L433-440 _function_ `bool UseExistenceMask()`
- L533-536 _function_ `int2 GetDownsampledResolution(int2 Resolution, int Factor)`
- L538-541 _function_ `int2 GetScaledViewRect()`
- L545-637 _function_ `void RayMarchSingleScatteringAdaptive( inout FRayMarchingContext RayMarchingContext, inout FAVSM_Sampler4 TransmittanceSampler, uint StepCount, inout float3 Radiance, inout float3 Transmittance )` _[#if USE_CAMERA_AVSM]_
- L641-881 _function_ `void RenderSingleScatteringWithLiveShading( uint2 DispatchThreadId )`

### `Shaders/Private/HeterogeneousVolumes/HeterogeneousVolumesLiveShadingShadows.usf` (Private)

- lines: 648; parse: all-branches
- includes: L3 `../Common.ush`, L13 `/Engine/Generated/Material.ush`, L14 `HeterogeneousVolumesStochasticFiltering.ush`, L15 `HeterogeneousVolumesLiveShadingUtils.ush`, L16 `HeterogeneousVolumesTracingUtils.ush`, L17 `HeterogeneousVolumesAdaptiveVolumetricShadowMapUtils.ush`, L18 `HeterogeneousVolumesBeerShadowMapUtils.ush`, L19 `../BlueNoise.ush`, L307 `HeterogeneousVolumesRayMarchingUtils.ush`

#### Macros (#define, 17)

- L5 `#define SUPPORT_CONTACT_SHADOWS 0`
- L7 `#define DYNAMICALLY_SHADOWED 1`
- L8 `#define TREAT_MAXDEPTH_UNSHADOWED 1`
- L10 `#define SHADOW_QUALITY 2`
- L11 `#define NO_TRANSLUCENCY_AVAILABLE `
- L22 `#define THREADGROUP_SIZE_1D 1` _[#if !defined(THREADGROUP_SIZE_1D)]_
- L26 `#define THREADGROUP_SIZE_2D 1` _[#if !defined(THREADGROUP_SIZE_2D)]_
- L30 `#define THREADGROUP_SIZE_3D 1` _[#if !defined(THREADGROUP_SIZE_3D)]_
- L33 `#define SHADOW_MAP_TYPE_AVSM 0`
- L34 `#define SHADOW_MAP_TYPE_BEER 1`
- L37 `#define SHADOW_MAP_TYPE SHADOW_MAP_TYPE_AVSM` _[#if !defined(SHADOW_MAP_TYPE)]_
- L274 `#define INDIRECT_LIGHTING_MODE_OFF 0`
- L275 `#define INDIRECT_LIGHTING_MODE_LIGHTING_CACHE 1`
- L276 `#define INDIRECT_LIGHTING_MODE_SINGLE_SCATTERING 2`
- L298 `#define FOG_INSCATTERING_MODE_OFF 0`
- L299 `#define FOG_INSCATTERING_MODE_REFERENCE 1`
- L300 `#define FOG_INSCATTERING_MODE_LINEAR_APPROX 2`

#### Entry points (1)

- L534-647 _entry_ `[numthreads(THREADGROUP_SIZE_2D, THREADGROUP_SIZE_2D, 1)] void RenderVolumetricShadowMapForLightWithLiveShadingCS( uint2 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID )` — stage: **compute** — C++: `FRenderVolumetricShadowMapForLightWithLiveShadingCS` SF_Compute via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/HeterogeneousVolumes/HeterogeneousVolumesLiveShadingPipeline.cpp:2116)

#### Structs / classes (1)

- L163-167 _struct_ **`FVolumeSampleContext`** `struct FVolumeSampleContext`
  - L165 _member_ `FMaterialPixelParameters MaterialParameters;`
  - L166 _member_ `FPixelMaterialInputs PixelMaterialInputs;`

#### Global resources (textures / buffers / samplers) (3)

- L79 _resource_ `RWBuffer<int> RWVolumetricShadowLinkedListAllocatorBuffer;` — Output
- L80 _resource_ `RWStructuredBuffer<uint2> RWVolumetricShadowLinkedListBuffer;`
- L81 _resource_ `RWTexture2D<float4> RWBeerShadowMapTexture;`

#### Global parameters (uniforms) (26)

- L41 _parameter_ `float4x4 LocalToWorld;` — Object data
- L42 _parameter_ `float4x4 WorldToLocal;`
- L43 _parameter_ `float3 LocalBoundsOrigin;`
- L44 _parameter_ `float3 LocalBoundsExtent;`
- L45 _parameter_ `int PrimitiveId;`
- L48 _parameter_ `int3 VoxelResolution;` — Volume data
- L51 _parameter_ `float MaxTraceDistance;` — Ray data
- L52 _parameter_ `float MaxShadowTraceDistance;`
- L53 _parameter_ `float StepSize;`
- L54 _parameter_ `float StepFactor;`
- L55 _parameter_ `float ShadowStepSize;`
- L56 _parameter_ `float ShadowStepFactor;`
- L57 _parameter_ `int MaxStepCount;`
- L58 _parameter_ `int bJitter;`
- L59 _parameter_ `int StochasticFilteringMode;`
- L62 _parameter_ `int NumShadowMatrices;` — Shadow data
- L63 _parameter_ `float4x4 TranslatedWorldToShadow[6];`
- L64 _parameter_ `float4x4 ShadowToTranslatedWorld[6];`
- L65 _parameter_ `float4 TranslatedWorldOrigin[6];`
- L67 _parameter_ `int2 ShadowResolution;`
- L68 _parameter_ `int MaxSampleCount;`
- L69 _parameter_ `float AbsoluteErrorThreshold;`
- L70 _parameter_ `float RelativeErrorThreshold;`
- L73 _parameter_ `int3 GroupCount;` — Dispatch data
- L76 _parameter_ `int ShadowDebugTweak;` — Debug data
- L418 _parameter_ `int CameraDownsampleFactor;`

#### Functions (35)

- L83-86 _function_ `FPrimitiveSceneData GetPrimitiveData(FMaterialVertexParameters Parameters)`
- L88-91 _function_ `FPrimitiveSceneData GetPrimitiveData(FMaterialPixelParameters Parameters)`
- L93-96 _function_ `float4x4 GetLocalToWorld()`
- L98-101 _function_ `float4x4 GetWorldToLocal()`
- L103-106 _function_ `float3 GetLocalBoundsOrigin()`
- L108-111 _function_ `float3 GetLocalBoundsExtent()`
- L113-116 _function_ `int3 GetVolumeResolution()`
- L118-121 _function_ `float GetShadowStepSize()`
- L123-126 _function_ `float GetShadowStepFactor()`
- L128-131 _function_ `float GetStepSize()`
- L133-136 _function_ `float GetStepFactor()`
- L138-141 _function_ `float GetMaxTraceDistance()`
- L143-146 _function_ `float GetMaxShadowTraceDistance()`
- L148-151 _function_ `int GetStochasticFilteringMode()`
- L153-156 _function_ `float EvalAmbientOcclusion(float3 WorldPosition)`
- L158-161 _function_ `float GetIndirectInscatteringFactor()`
- L169-198 _function_ `FVolumeSampleContext CreateVolumeSampleContext( float3 LocalPosition, float3 WorldPosition, float3 WorldPosition_DDX, float3 WorldPosition_DDY, float MipLevel )`
- L200-212 _function_ `FVolumeSampleContext CreateVolumeSampleContext(float3 LocalPosition, float3 WorldPosition, float MipLevel)`
- L214-236 _function_ `FVolumeSampleContext CreateVolumeSampleContext(float3 LocalPosition, float3 WorldPosition, float3 FilterWidth, float MipLevel, float Rand, int StochasticFilteringMode)`
- L238-242 _function_ `float3 SampleExtinction(inout FVolumeSampleContext Context)`
- L244-248 _function_ `float3 SampleEmission(inout FVolumeSampleContext Context)`
- L250-254 _function_ `float3 SampleAlbedo(inout FVolumeSampleContext Context)`
- L256-260 _function_ `uint GetLinearIndex(uint Face, uint2 PixelCoord)`
- L262-266 _function_ `uint2 GetTexture2DIndex(uint Face, uint2 PixelCoord)`
- L269-272 _function_ `bool UseInscatteringVolume()` — Cinematic feature options
- L278-281 _function_ `int GetIndirectLightingMode()`
- L283-286 _function_ `bool IsOfflineRender()`
- L288-291 _function_ `int ShouldApplyHeightFog()`
- L293-296 _function_ `int ShouldApplyVolumetricFog()`
- L302-305 _function_ `int GetFogInscatteringMode()`
- L309-340 _function_ `int FindSampleIndexWithLowestError( int PixelIndex )`
- L342-350 _function_ `void AddSample(FAVSMSampleData SampleData, int PixelIndex, inout int PrevSampleIndex, inout int SampleIndex)`
- L352-377 _function_ `void ReplaceSample( int PixelIndex, int SampleIndex, FAVSMSampleData SampleData, int PrevPtrIndex, int NextPtrIndex )`
- L379-416 _function_ `void AddOrReplaceSample(FAVSMSampleData Data, int PixelIndex, inout int PrevSampleIndex, inout int SampleIndex)`
- L420-532 _function_ `float3 RayMarchTransmittance( inout FRayMarchingContext RayMarchingContext, int PixelIndex, inout FBeerShadowMapData BeerShadowMapData )`

### `Shaders/Private/HeterogeneousVolumes/HeterogeneousVolumesLiveShadingUtils.ush` (Private)

- lines: 75; parse: all-branches
- L4 #pragma `message("UESHADERMETADATA_VERSION 80584AA0-BFD9-4021-BE67-273077B48601")`

#### Functions (6)

- L6-23 _function_ `FPrimitiveSceneData GetPrimitiveData( uint PrimitiveId, float4x4 LocalToWorld, float4x4 WorldToLocal, float3 LocalBoundsOrigin, float3 LocalBoundsExtent )`
- L25-28 _function_ `FPrimitiveSceneData GetPrimitiveData(FMaterialVertexParameters Parameters, float4x4 LocalToWorld, float4x4 WorldToLocal, float3 LocalBoundsOrigin, float3 LocalBoundsExtent)`
- L30-33 _function_ `FPrimitiveSceneData GetPrimitiveData(FMaterialPixelParameters Parameters, float4x4 LocalToWorld, float4x4 WorldToLocal, float3 LocalBoundsOrigin, float3 LocalBoundsExtent)`
- L36-48 _function_ `float3 SampleExtinctionCoefficients(in FPixelMaterialInputs PixelMaterialInputs)` — Stolen from VolumetricFog
- L50-60 _function_ `float3 SampleEmissive(in FPixelMaterialInputs PixelMaterialInputs)`
- L62-74 _function_ `float3 SampleAlbedo(in FPixelMaterialInputs PixelMaterialInputs)`

### `Shaders/Private/HeterogeneousVolumes/HeterogeneousVolumesMaterialBakingPipeline.usf` (Private)

- lines: 627; parse: all-branches
- includes: L3 `../Common.ush`, L9 `/Engine/Generated/Material.ush`, L10 `../BlueNoise.ush`, L11 `../PositionReconstructionCommon.ush`, L12 `../MortonCode.ush`, L13 `../ComputeShaderUtils.ush`, L14 `../Hash.ush`, L15 `../HashTable.ush`, L16 `HeterogeneousVolumesLiveShadingUtils.ush`, L114 `HeterogeneousVolumesVoxelGridTypes.ush`, L115 `HeterogeneousVolumesVoxelGridUtils.ush`, L480 `HeterogeneousVolumesFrustumVoxelGridUtils.ush`

#### Macros (#define, 4)

- L5 `#define SUPPORT_CONTACT_SHADOWS 0`
- L6 `#define EYE_ADAPTATION_LOOSE_PARAMETERS 1`
- L7 `#define SQRT_THREE 1.7320508075688772`
- L20 `#define THREADGROUP_SIZE_3D 1` _[#if !defined(THREADGROUP_SIZE_3D)]_

#### Entry points (3)

- L56-110 _entry_ `[numthreads(THREADGROUP_SIZE_3D, THREADGROUP_SIZE_3D, THREADGROUP_SIZE_3D)] void HeterogeneousVolumesBakeMaterialCS( uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID )` — stage: **compute** — C++: `FHeterogeneousVolumesBakeMaterialCS` SF_Compute via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/HeterogeneousVolumes/HeterogeneousVolumesMaterialBakingPipeline.cpp:107)
- L236-471 _entry_ `[numthreads(THREADGROUP_SIZE_3D, THREADGROUP_SIZE_3D, THREADGROUP_SIZE_3D)] void RasterizeBottomLevelOrthoGridCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID )` — stage: **compute** — C++: `FRasterizeBottomLevelOrthoGridCS` SF_Compute via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/HeterogeneousVolumes/HeterogeneousVolumesVoxelGridPipeline.cpp:1109)
- L484-626 _entry_ `[numthreads(THREADGROUP_SIZE_3D, THREADGROUP_SIZE_3D, THREADGROUP_SIZE_3D)] void RasterizeBottomLevelFrustumGridCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID )` — stage: **compute** — C++: `FRasterizeBottomLevelFrustumGridCS` SF_Compute via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/HeterogeneousVolumes/HeterogeneousVolumesVoxelGridPipeline.cpp:792)

#### Structs / classes (1)

- L161-165 _struct_ **`FRasterTileData`** `struct FRasterTileData`
  - L163 _member_ `uint TopLevelGridLinearIndex;`
  - L164 _member_ `uint BottomLevelGridLinearOffset;`

#### Global resources (textures / buffers / samplers) (11)

- L37 _resource_ `RWTexture3D<float3> RWExtinctionTexture;` — Output
- L38 _resource_ `RWTexture3D<float3> RWEmissionTexture;`
- L39 _resource_ `RWTexture3D<float3> RWAlbedoTexture;`
- L167 _resource_ `Buffer<uint> RasterTileAllocatorBuffer;`
- L168 _resource_ `StructuredBuffer<FRasterTileData> RasterTileBuffer;`
- L170 _resource_ `RWStructuredBuffer<FTopLevelGridData> RWTopLevelGridBuffer;`
- L171 _resource_ `RWStructuredBuffer<FTopLevelGridData> RWIndirectionGridBuffer;`
- L173 _resource_ `RWBuffer<uint> RWBottomLevelGridAllocatorBuffer;`
- L174 _resource_ `RWStructuredBuffer<FScalarGridData> RWExtinctionGridBuffer;`
- L175 _resource_ `RWStructuredBuffer<FVectorGridData> RWEmissionGridBuffer;`
- L176 _resource_ `RWStructuredBuffer<FVectorGridData> RWScatteringGridBuffer;`

#### Global parameters (uniforms) (23)

- L24 _parameter_ `float4x4 LocalToWorld;` — Object data
- L25 _parameter_ `float4x4 WorldToLocal;`
- L26 _parameter_ `float3 LocalBoundsOrigin;`
- L27 _parameter_ `float3 LocalBoundsExtent;`
- L28 _parameter_ `int PrimitiveId;`
- L29 _parameter_ `int bJitter;`
- L30 _parameter_ `int bEvaluateEmission;`
- L31 _parameter_ `int bEvaluateAlbedo;`
- L34 _parameter_ `int3 VolumeResolution;` — Volume data
- L117 _parameter_ `int3 TopLevelGridResolution;`
- L118 _parameter_ `float3 TopLevelGridWorldBoundsMin;`
- L119 _parameter_ `float3 TopLevelGridWorldBoundsMax;`
- L121 _parameter_ `float3 PrimitiveWorldBoundsMin;`
- L122 _parameter_ `float3 PrimitiveWorldBoundsMax;`
- L124 _parameter_ `int BottomLevelGridBufferSize;`
- L178 _parameter_ `int FixedBottomLevelResolution;`
- L184 _parameter_ `int bSampleAtVertices;` — Sampling mode
- L186 _parameter_ `float HomogeneousThreshold;`
- L473 _parameter_ `int3 VoxelDimensions;`
- L474 _parameter_ `float4x4 ViewToWorld;`
- L476 _parameter_ `float TanHalfFOV;`
- L477 _parameter_ `float NearPlaneDepth;`
- L478 _parameter_ `float FarPlaneDepth;`

#### groupshared (6)

- L188 _groupshared_ `groupshared float3 GSExtinctionSum[THREADGROUP_SIZE_1D];`
- L189 _groupshared_ `groupshared float GSExtinctionVariance[THREADGROUP_SIZE_1D];`
- L190 _groupshared_ `groupshared float GSZeroCrossings[THREADGROUP_SIZE_1D];`
- L191 _groupshared_ `groupshared int3 GSAllocatedVoxelResolution;`
- L192 _groupshared_ `groupshared int GSAllocatedVoxelCount;`
- L482 _groupshared_ `groupshared float GSExtinctionSumScalar[THREADGROUP_SIZE_1D];`

#### Functions (12)

- L41-44 _function_ `FPrimitiveSceneData GetPrimitiveData(FMaterialVertexParameters Parameters)`
- L46-49 _function_ `FPrimitiveSceneData GetPrimitiveData(FMaterialPixelParameters Parameters)`
- L51-54 _function_ `uint2 VoxelIndex2D(uint3 VoxelIndex)`
- L126-131 _function_ `void CalcVoxelBounds(float3 VoxelIndex, inout float3 VoxelBoundsMin, inout float3 VoxelBoundsMax)`
- L133-137 _function_ `float3 GetVoxelCenter(float3 VoxelIndex, inout float3 VoxelBoundsMin, inout float3 VoxelBoundsMax)`
- L139-147 _function_ `bool PrimitiveIntersectsVoxel(float3 VoxelBoundsMin, float3 VoxelBoundsMax)`
- L149-152 _function_ `bool WorldPositionIntersectsPrimitive(float3 WorldPosition)`
- L154-159 _function_ `bool LocalPositionIntersectsPrimitive(float3 LocalPosition)`
- L194-197 _function_ `float GetZeroThreshold()`
- L199-203 _function_ `float CalcSampleVariance(float3 MeanValue, float3 SampleValue)`
- L205-209 _function_ `float CalcZeroCrossing(float3 SampleValue)`
- L212-233 _function_ `uint2 CalcStencil(uint VoxelCount)` _[#if 0]_

### `Shaders/Private/HeterogeneousVolumes/HeterogeneousVolumesPreshadingPipeline.usf` (Private)

- lines: 324; parse: all-branches
- includes: L3 `../Common.ush`, L26 `../VirtualShadowMaps/VirtualShadowMapProjectionCommon.ush` [VIRTUAL_SHADOW_MAP], L29 `HeterogeneousVolumesPreshadingUniformBufferUtils.ush`, L30 `HeterogeneousVolumesPreshadingUtils.ush`, L31 `HeterogeneousVolumesTracingUtils.ush`, L32 `HeterogeneousVolumesLightingUtils.ush`, L34 `HeterogeneousVolumesRayMarchingUtils.ush`

#### Macros (#define, 8)

- L5 `#define SUPPORT_CONTACT_SHADOWS 0`
- L7 `#define DYNAMICALLY_SHADOWED 1`
- L8 `#define TREAT_MAXDEPTH_UNSHADOWED 1`
- L10 `#define SHADOW_QUALITY 2`
- L11 `#define NO_TRANSLUCENCY_AVAILABLE `
- L14 `#define DIM_APPLY_SHADOW_TRANSMITTANCE 0` _[#if !defined(DIM_APPLY_SHADOW_TRANSMITTANCE)]_
- L18 `#define THREADGROUP_SIZE_3D 1` _[#if !defined(THREADGROUP_SIZE_3D)]_
- L22 `#define THREADGROUP_SIZE_2D 1` _[#if !defined(THREADGROUP_SIZE_2D)]_

#### Entry points (6)

- L40-50 _entry_ `[numthreads(THREADGROUP_SIZE_3D, THREADGROUP_SIZE_3D, THREADGROUP_SIZE_3D)] void CopyTexture3D( uint3 DispatchThreadId : SV_DispatchThreadID )` — stage: **compute** — C++: `FCopyTexture3D` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HeterogeneousVolumes/HeterogeneousVolumesSparseVoxelPipeline.cpp:46)
- L55-73 _entry_ `[numthreads(THREADGROUP_SIZE_3D, THREADGROUP_SIZE_3D, THREADGROUP_SIZE_3D)] void MaxTexture3D( uint3 DispatchThreadId : SV_DispatchThreadID )` — stage: **compute** — C++: `FMaxTexture3D` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HeterogeneousVolumes/HeterogeneousVolumesPreshadingPipeline.cpp:347)
- L77-102 _entry_ `[numthreads(THREADGROUP_SIZE_3D, THREADGROUP_SIZE_3D, THREADGROUP_SIZE_3D)] void GenerateMips3D( uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID )` — stage: **compute** — C++: `FGenerateMips3D` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HeterogeneousVolumes/HeterogeneousVolumesPreshadingPipeline.cpp:1221)
- L104-123 _entry_ `[numthreads(THREADGROUP_SIZE_3D, THREADGROUP_SIZE_3D, THREADGROUP_SIZE_3D)] void GenerateMin3D( uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID )` — stage: **compute** — C++: `FGenerateMin3D` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HeterogeneousVolumes/HeterogeneousVolumesPreshadingPipeline.cpp:1256)
- L127-197 _entry_ `[numthreads(THREADGROUP_SIZE_3D, THREADGROUP_SIZE_3D, THREADGROUP_SIZE_3D)] void RenderLightingCacheWithPreshadingCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID )` — stage: **compute** — C++: `FRenderLightingCacheWithPreshadingCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HeterogeneousVolumes/HeterogeneousVolumesPreshadingPipeline.cpp:164)
- L212-323 _entry_ `[numthreads(THREADGROUP_SIZE_2D, THREADGROUP_SIZE_2D, 1)] void RenderSingleScatteringWithPreshadingCS( uint GroupId : SV_GroupID, uint GroupThreadId : SV_GroupThreadID, uint2 DispatchThreadId : SV_DispatchThreadID )` — stage: **compute** — C++: `FRenderSingleScatteringWithPreshadingCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HeterogeneousVolumes/HeterogeneousVolumesPreshadingPipeline.cpp:313)

#### Global resources (textures / buffers / samplers) (9)

- L36 _resource_ `int3 TextureResolution;`
- L37 _resource_ `Texture3D InputTexture;`
- L38 _resource_ `RWTexture3D<float3> RWOutputTexture;`
- L52 _resource_ `Texture3D InputTextureLHS;`
- L53 _resource_ `Texture3D InputTextureRHS;`
- L75 _resource_ `SamplerState TextureSampler;`
- L125 _resource_ `RWTexture3D<float3> RWLightingCacheTexture;`
- L199 _resource_ `RWTexture2D<float4> RWLightingTexture;`
- L200 _resource_ `RWTexture2D<float4> RWVelocityTexture;`

#### Functions (2)

- L202-205 _function_ `int2 GetDownsampledResolution(int2 Resolution, int Factor)`
- L207-210 _function_ `int2 GetScaledViewRect()`

### `Shaders/Private/HeterogeneousVolumes/HeterogeneousVolumesPreshadingUniformBufferUtils.ush` (Private)

- lines: 118; parse: all-branches
- includes: L3 `HeterogeneousVolumesStochasticFiltering.ush`

#### Structs / classes (1)

- L5-9 _struct_ **`FVolumeSampleContext`** `struct FVolumeSampleContext`
  - L7 _member_ `float3 UVW;`
  - L8 _member_ `float MipLevel;`

#### Functions (10)

- L11-14 _function_ `float4x4 GetLocalToWorld()`
- L16-19 _function_ `float4x4 GetWorldToLocal()`
- L21-24 _function_ `float3 GetLocalBoundsOrigin()`
- L26-29 _function_ `float3 GetLocalBoundsExtent()`
- L31-40 _function_ `float3 SampleExtinction(inout FVolumeSampleContext Context)`
- L42-51 _function_ `float3 SampleEmission(inout FVolumeSampleContext Context)`
- L53-62 _function_ `float3 SampleAlbedo(inout FVolumeSampleContext Context)`
- L64-80 _function_ `FVolumeSampleContext CreateVolumeSampleContext( float3 LocalPosition, float3 WorldPosition, float3 WorldPosition_DDX, float3 WorldPosition_DDY, float MipLevel )`
- L82-94 _function_ `FVolumeSampleContext CreateVolumeSampleContext(float3 LocalPosition, float3 WorldPosition, float MipLevel)`
- L96-118 _function_ `FVolumeSampleContext CreateVolumeSampleContext(float3 LocalPosition, float3 WorldPosition, float3 FilterWidth, float MipLevel, float Rand, int SamplingMethod)`

### `Shaders/Private/HeterogeneousVolumes/HeterogeneousVolumesPreshadingUtils.ush` (Private)

- lines: 191; parse: all-branches
- includes: L3 `HeterogeneousVolumesStochasticFiltering.ush`

#### Macros (#define, 6)

- L157 `#define INDIRECT_LIGHTING_MODE_OFF 0`
- L158 `#define INDIRECT_LIGHTING_MODE_LIGHTING_CACHE 1`
- L159 `#define INDIRECT_LIGHTING_MODE_SINGLE_SCATTERING 2`
- L178 `#define FOG_INSCATTERING_MODE_OFF 0`
- L179 `#define FOG_INSCATTERING_MODE_REFERENCE 1`
- L180 `#define FOG_INSCATTERING_MODE_LINEAR_APPROX 2`

#### Global parameters (uniforms) (17)

- L5 _parameter_ `int bApplyEmissionAndTransmittance;`
- L11 _parameter_ `int bApplyDirectLighting;`
- L17 _parameter_ `int LightType;`
- L23 _parameter_ `uint VirtualShadowMapId;`
- L29 _parameter_ `int MipLevel;`
- L35 _parameter_ `int MaxStepCount;`
- L41 _parameter_ `int bJitter;`
- L47 _parameter_ `float VolumetricScatteringIntensity;`
- L53 _parameter_ `float MaxStepSize;`
- L59 _parameter_ `int3 GroupCount;`
- L65 _parameter_ `int DownsampleFactor;`
- L71 _parameter_ `float MaxTraceDistance;`
- L77 _parameter_ `float MaxShadowTraceDistance;`
- L83 _parameter_ `float StepSize;`
- L90 _parameter_ `float StepFactor;` — TEST..
- L97 _parameter_ `float ShadowStepSize;`
- L104 _parameter_ `float ShadowStepFactor;`

#### Functions (29)

- L6-9 _function_ `bool ShouldApplyEmissionAndTransmittance()`
- L12-15 _function_ `bool ShouldApplyDirectLighting()`
- L18-21 _function_ `int GetLightType()`
- L24-27 _function_ `uint GetVirtualShadowMapId()`
- L30-33 _function_ `int GetMipLevel()`
- L36-39 _function_ `int GetMaxStepCount()`
- L42-45 _function_ `bool ShouldJitter()`
- L48-51 _function_ `float GetVolumetricScatteringIntensity()`
- L54-57 _function_ `float GetMaxStepSize()`
- L60-63 _function_ `int3 GetGroupCount()`
- L66-69 _function_ `int GetDownsampleFactor()`
- L72-75 _function_ `float GetMaxTraceDistance()`
- L78-81 _function_ `float GetMaxShadowTraceDistance()`
- L84-87 _function_ `float GetStepSize()`
- L91-95 _function_ `float GetStepFactor()`
- L98-102 _function_ `float GetShadowStepSize()`
- L105-109 _function_ `float GetShadowStepFactor()`
- L112-115 _function_ `int GetStochasticFilteringMode()`
- L117-121 _function_ `int ShouldApplyShadowTransmittance()`
- L124-128 _function_ `int ShouldApplyHeightFog()` — int bApplyHeightFog;
- L131-135 _function_ `int ShouldApplyVolumetricFog()` — int bApplyVolumetricFog;
- L138-142 _function_ `float GetIndirectInscatteringFactor()` — float IndirectInscatteringFactor;
- L145-148 _function_ `float EvalAmbientOcclusion(float3 WorldPosition)` — TODO: Implement ambient occlusion for preshading pipeline
- L151-155 _function_ `bool UseInscatteringVolume()` — Cinematic feature options
- L161-164 _function_ `int GetIndirectLightingMode()`
- L166-170 _function_ `bool ShouldWriteVelocity()`
- L172-176 _function_ `bool IsOfflineRender()`
- L182-185 _function_ `int GetFogInscatteringMode()`
- L187-190 _function_ `uint3 GetVolumeResolution()`

### `Shaders/Private/HeterogeneousVolumes/HeterogeneousVolumesRayMarchingTypes.ush` (Private)

- lines: 190; parse: all-branches
- includes: L3 `../PathTracing/Utilities/PathTracingRandomSequence.ush`

#### Structs / classes (1)

- L5-39 _struct_ **`FRayMarchingContext`** `struct FRayMarchingContext`
  - L8 _member_ `float3 LocalRayOrigin;` — Local-space
  - L9 _member_ `float3 LocalRayDirection;`
  - L10 _member_ `float LocalRayTMin;`
  - L11 _member_ `float LocalRayTMax;`
  - L14 _member_ `float3 WorldRayOrigin;` — World-space
  - L15 _member_ `float3 WorldRayDirection;`
  - L17 _member_ `float3 WorldRayDirection_DDX;` _[#if USE_ANALYTIC_DERIVATIVES]_
  - L18 _member_ `float3 WorldRayDirection_DDY;` _[#if USE_ANALYTIC_DERIVATIVES]_
  - L20 _member_ `float LocalToWorldScale;`
  - L23 _member_ `float Jitter;` — Ray-step attributes
  - L24 _member_ `float StepSize;`
  - L25 _member_ `uint MaxStepCount;`
  - L27 _member_ `float MipLevel;`
  - L30 _member_ `int bApplyEmissionAndTransmittance;` — Lighting
  - L31 _member_ `int bApplyDirectLighting;`
  - L32 _member_ `int bApplyShadowTransmittance;`
  - L35 _member_ `FRandomSequence RandSequence;` — TEMPORARY STORAGE!!
  - L36 _member_ `float LocalScatterT0;`
  - L37 _member_ `float LocalScatterT1;`
  - L38 _member_ `float3 Transmittance0;`

#### Functions (7)

- L41-96 _function_ `FRayMarchingContext CreateRayMarchingContext( float3 LocalRayOrigin, float3 LocalRayDirection, float3 LocalRayDirection_DDX, float3 LocalRayDirection_DDY, float LocalRayTMin, float LocalRayTMax, float3 WorldRayOrigin, float3 WorldRayDirection, float3 WorldRayDirection_DDX, float3 WorldRayDirection_DDY, float Jitter, float StepSize, uint MaxStepCount, int bApplyEmissionAndTransmittance, int bApplyDirectLighting, int bApplyShadowTransmittance )`
- L98-144 _function_ `FRayMarchingContext CreateRayMarchingContext( float3 LocalRayOrigin, float3 LocalRayDirection, float LocalRayTMin, float LocalRayTMax, float3 WorldRayOrigin, float3 WorldRayDirection, float Jitter, float StepSize, uint MaxStepCount, int bApplyEmissionAndTransmittance, int bApplyDirectLighting, int bApplyShadowTransmittance )`
- L146-157 _function_ `float CalcStepSize(float3 LocalRayDirection, float LocalStepSize, float LocalStepFactor)`
- L159-164 _function_ `float CalcStepSize(float3 LocalRayDirection)`
- L166-171 _function_ `float CalcShadowStepSize(float3 LocalRayDirection)`
- L173-181 _function_ `float RecalculateStepSize(inout FRayMarchingContext Context)`
- L183-190 _function_ `uint CalcStepCount(inout FRayMarchingContext Context)`

### `Shaders/Private/HeterogeneousVolumes/HeterogeneousVolumesRayMarchingUtils.ush` (Private)

- lines: 693; parse: all-branches
- includes: L6 `HeterogeneousVolumesRayMarchingTypes.ush`, L7 `HeterogeneousVolumesTracingUtils.ush`, L8 `HeterogeneousVolumesTransmittanceVolumeUtils.ush`, L10 `../ForwardShadowingCommon.ush`, L11 `../VolumeLightingCommon.ush`, L12 `../LightData.ush`, L13 `../DeferredLightingCommon.ush`, L15 `../SHCommon.ush`, L17 `../Lumen/LumenTranslucencyVolumeShared.ush`, L36 `HeterogeneousVolumesAdaptiveVolumetricShadowMapSampling.ush` [DIM_USE_ADAPTIVE_VOLUMETRIC_SHADOW_MAP], L37 `HeterogeneousVolumesAdaptiveVolumetricShadowMapSampler.ush` [DIM_USE_ADAPTIVE_VOLUMETRIC_SHADOW_MAP], L40 `../HeightFogCommon.ush`

#### Macros (#define, 5)

- L16 `#define RadianceCacheInterpolation LumenGIVolumeStruct`
- L20 `#define CUSTOM_TRANSMITTANCE_FUNCTION 0` _[#if !defined(CUSTOM_TRANSMITTANCE_FUNCTION)]_
- L24 `#define HARDWARE_RAY_TRACING 0` _[#if !defined(HARDWARE_RAY_TRACING)]_
- L28 `#define HARD_SURFACE_SHADOWING 1` _[#if !defined(HARD_SURFACE_SHADOWING)]_
- L32 `#define DIM_USE_ADAPTIVE_VOLUMETRIC_SHADOW_MAP 0` _[#if !defined(DIM_USE_ADAPTIVE_VOLUMETRIC_SHADOW_MAP)]_
- L4 #pragma `message("UESHADERMETADATA_VERSION 498251B5-BC1F-4250-A0A2-7BB218050A9A")`

#### Functions (11)

- L42-54 _function_ `float3 GetWorldVoxelSizeOfLightingCache()`
- L56-69 _function_ `float CalcShadowBias()`
- L71-114 _function_ `float ComputeHardSurfaceShadowFactor( float3 TranslatedWorldPosition, FDeferredLightData LightData, uint LightType )`
- L116-148 _function_ `void RayMarchTransmittance( inout FRayMarchingContext RayMarchingContext, uint StepCount, inout float3 Transmittance )`
- L150-182 _function_ `float3 ComputeTransmittance( inout FRayMarchingContext RayMarchingContext )`
- L184-253 _function_ `float3 ComputeTransmittance( float3 WorldRayOrigin, float3 ToLight, uint MaxStepCount )`
- L255-271 _function_ `float3 ComputeIndirectInscattering( float3 WorldPosition, float3 WorldRayDirection )`
- L273-322 _function_ `float3 ComputeInscattering( float3 WorldPosition, FDeferredLightData LightData, uint LightType, uint MaxStepCount, float WorldShadowBias, bool bApplyShadowTransmittance )`
- L324-355 _function_ `void RayMarchEmissionAbsorption( inout FRayMarchingContext RayMarchingContext, uint StepCount, inout float3 Radiance, inout float3 Transmittance )`
- L357-597 _function_ `void RayMarchSingleScattering( inout FRayMarchingContext RayMarchingContext, inout FAVSM_Sampler4 TransmittanceSampler, FDeferredLightData LightData, uint LightType, uint StepCount, inout float LocalScatterTMin, inout float3 Radiance, inout float3 Transmittance )`
- L599-692 _function_ `void RayMarchSingleScatteringReferenceFastPath( inout FRayMarchingContext RayMarchingContext, inout FAVSM_Sampler4 TransmittanceSampler, uint StepCount, inout float3 Radiance, inout float3 Transmittance )`

### `Shaders/Private/HeterogeneousVolumes/HeterogeneousVolumesShadowMask.usf` (Private)

- lines: 89; parse: all-branches
- includes: L11 `../Common.ush`, L12 `../DeferredLightingCommon.ush`, L13 `HeterogeneousVolumesAdaptiveVolumetricShadowMapSampling.ush`

#### Macros (#define, 10)

- L3 `#define SUPPORT_CONTACT_SHADOWS 0`
- L5 `#define DYNAMICALLY_SHADOWED 1`
- L6 `#define TREAT_MAXDEPTH_UNSHADOWED 1`
- L8 `#define SHADOW_QUALITY 2`
- L9 `#define NO_TRANSLUCENCY_AVAILABLE `
- L16 `#define THREADGROUP_SIZE_1D 1` _[#if !defined(THREADGROUP_SIZE_1D)]_
- L20 `#define THREADGROUP_SIZE_2D 1` _[#if !defined(THREADGROUP_SIZE_2D)]_
- L23 `#define SHADOW_TYPE_VOLUMETRIC_SHADOW_MAP 0`
- L24 `#define SHADOW_TYPE_BEER_SHADOW_MAP 1`
- L27 `#define SHADOW_TYPE SHADOW_TYPE_VOLUMETRIC_SHADOW_MAP` _[#if !defined(SHADOW_TYPE)]_

#### Entry points (1)

- L65-89 _entry_ `[numthreads(THREADGROUP_SIZE_2D, THREADGROUP_SIZE_2D, 1)] void RenderVolumetricShadowMaskCS( uint GroupId : SV_GroupID, uint GroupThreadId : SV_GroupThreadID, uint2 DispatchThreadId : SV_DispatchThreadID )` — stage: **compute** — C++: `FRenderVolumetricShadowMaskCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HeterogeneousVolumes/HeterogeneousVolumesLiveShadingPipeline.cpp:3514)

#### Global resources (textures / buffers / samplers) (2)

- L38 _resource_ `Texture2D<float4> ShadowMaskTexture;` — Shadow mask
- L41 _resource_ `RWTexture2D<float4> RWVolumetricShadowMaskTexture;` — Output

#### Global parameters (uniforms) (3)

- L31 _parameter_ `int LightType;` — Light data
- L34 _parameter_ `int3 GroupCount;` — Dispatch data
- L35 _parameter_ `int DownsampleFactor;`

#### Functions (3)

- L43-46 _function_ `int2 GetDownsampledResolution(int2 Resolution, int Factor)`
- L48-51 _function_ `int2 GetScaledViewRect()`
- L53-63 _function_ `float SampleTransmittance( float3 TranslatedWorldPosition, float3 LightTranslatedWorldPosition )`

### `Shaders/Private/HeterogeneousVolumes/HeterogeneousVolumesSparseVoxelPipeline.usf` (Private)

- lines: 214; parse: all-branches
- includes: L3 `HeterogeneousVolumesSparseVoxelUtils.ush`, L4 `../Common.ush`, L6 `HeterogeneousVolumesSparseVoxelUniformBufferUtils.ush`

#### Macros (#define, 4)

- L9 `#define THREADGROUP_SIZE_1D 1` _[#if !defined(THREADGROUP_SIZE_1D)]_
- L13 `#define THREADGROUP_SIZE_2D 1` _[#if !defined(THREADGROUP_SIZE_2D)]_
- L17 `#define THREADGROUP_SIZE_3D 1` _[#if !defined(THREADGROUP_SIZE_3D)]_
- L176 `#define VULKAN_ALIGNMENT_WORKAROUND 1`

#### Entry points (5)

- L22-30 _entry_ `[numthreads(1, 1, 1)] void ClearAllocator( uint DispatchThreadId : SV_DispatchThreadID )` — stage: **compute** — C++: `FClearAllocator` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HeterogeneousVolumes/HeterogeneousVolumesSparseVoxelPipeline.cpp:94)
- L42-62 _entry_ `[numthreads(THREADGROUP_SIZE_3D, THREADGROUP_SIZE_3D, THREADGROUP_SIZE_3D)] void AllocateSparseVoxels( uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID )` — stage: **compute** — C++: `FAllocateSparseVoxels` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HeterogeneousVolumes/HeterogeneousVolumesSparseVoxelPipeline.cpp:129)
- L68-116 _entry_ `[numthreads(THREADGROUP_SIZE_3D, THREADGROUP_SIZE_3D, THREADGROUP_SIZE_3D)] void AllocateSparseVoxelsToRefine( uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID )` — stage: **compute** — C++: `FAllocateSparseVoxelsToRefine` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HeterogeneousVolumes/HeterogeneousVolumesSparseVoxelPipeline.cpp:167) — TODO: Operate at lower MIP, using wave intrinsics to broadcast non-zero
- L122-172 _entry_ `[numthreads(THREADGROUP_SIZE_1D, 1, 1)] void RefineSparseVoxels( uint GroupThreadId : SV_GroupThreadID, uint DispatchThreadId : SV_DispatchThreadID )` — stage: **compute** — C++: `FRefineSparseVoxels` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HeterogeneousVolumes/HeterogeneousVolumesSparseVoxelPipeline.cpp:213)
- L183-214 _entry_ `[numthreads(64, 1, 1)] void CreateSparseVoxelBLAS( uint GroupThreadId : SV_GroupThreadID, uint DispatchThreadId : SV_DispatchThreadID )` — stage: **compute** — C++: `FCreateSparseVoxelBLAS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HeterogeneousVolumes/HeterogeneousVolumesHardwareRayTracing.cpp:80)

#### Global resources (textures / buffers / samplers) (10)

- L20 _resource_ `RWBuffer<uint> RWAllocatorBuffer;`
- L32 _resource_ `Texture3D VoxelMinTexture;`
- L39 _resource_ `RWStructuredBuffer<FVoxelDataPacked> RWVoxelBuffer;`
- L40 _resource_ `RWBuffer<uint> RWNumVoxelsBuffer;`
- L64 _resource_ `RWStructuredBuffer<FVoxelDataPacked> RWVoxelsToRefineBuffer;`
- L65 _resource_ `RWBuffer<uint> RWNumVoxelsToRefineBuffer;`
- L118 _resource_ `StructuredBuffer<FVoxelDataPacked> VoxelsToRefineBuffer;`
- L119 _resource_ `Buffer<uint> NumVoxelsToRefineBuffer;`
- L178 _resource_ `RWStructuredBuffer<float> RWPositionBuffer;` _[#if VULKAN_ALIGNMENT_WORKAROUND]_
- L180 _resource_ `RWStructuredBuffer<float3> RWPositionBuffer;` _[#if !(VULKAN_ALIGNMENT_WORKAROUND)]_

#### Global parameters (uniforms) (4)

- L33 _parameter_ `uint3 VoxelMinResolution;`
- L36 _parameter_ `int3 VolumeResolution;` — Volume data
- L37 _parameter_ `int MipLevel;`
- L120 _parameter_ `uint3 MipVolumeResolution;`

### `Shaders/Private/HeterogeneousVolumes/HeterogeneousVolumesSparseVoxelUniformBufferUtils.ush` (Private)

- lines: 183; parse: all-branches
- includes: L3 `HeterogeneousVolumesStochasticFiltering.ush`

#### Structs / classes (1)

- L90-94 _struct_ **`FVolumeSampleContext`** `struct FVolumeSampleContext`
  - L92 _member_ `float3 UVW;`
  - L93 _member_ `float MipLevel;`

#### Functions (23)

- L5-8 _function_ `float4x4 GetLocalToWorld()`
- L10-13 _function_ `float4x4 GetWorldToLocal()`
- L15-18 _function_ `float3 GetLocalBoundsOrigin()`
- L20-23 _function_ `float3 GetLocalBoundsExtent()`
- L25-28 _function_ `float GetMaxTraceDistance()`
- L30-33 _function_ `float GetMaxShadowTraceDistance()`
- L35-38 _function_ `float GetStepSize()`
- L40-43 _function_ `float GetStepFactor()`
- L45-48 _function_ `float GetShadowStepSize()`
- L50-53 _function_ `float GetShadowStepFactor()`
- L55-58 _function_ `int GetStochasticFilteringMode()`
- L60-63 _function_ `int ShouldApplyHeightFog()`
- L65-68 _function_ `int ShouldApplyVolumetricFog()`
- L70-73 _function_ `float GetIndirectInscatteringFactor()`
- L75-78 _function_ `uint3 GetVolumeResolution()`
- L80-83 _function_ `uint GetNumVoxels()`
- L85-88 _function_ `FVoxelDataPacked GetVoxelDataPacked(uint VoxelIndex)`
- L96-112 _function_ `FVolumeSampleContext CreateVolumeSampleContext( float3 LocalPosition, float3 WorldPosition, float3 WorldPosition_DDX, float3 WorldPosition_DDY, float MipLevel )`
- L114-126 _function_ `FVolumeSampleContext CreateVolumeSampleContext(float3 LocalPosition, float3 WorldPosition, float MipLevel)`
- L128-150 _function_ `FVolumeSampleContext CreateVolumeSampleContext(float3 LocalPosition, float3 WorldPosition, float3 FilterWidth, float MipLevel, float Rand, int SamplingMethod)`
- L152-161 _function_ `float3 SampleExtinction(inout FVolumeSampleContext Context)`
- L163-172 _function_ `float3 SampleEmission(inout FVolumeSampleContext Context)`
- L174-183 _function_ `float3 SampleAlbedo(inout FVolumeSampleContext Context)`

### `Shaders/Private/HeterogeneousVolumes/HeterogeneousVolumesSparseVoxelUtils.ush` (Private)

- lines: 90; parse: all-branches

#### Macros (#define, 1)

- L3 `#define INVALID_VOXEL 0xFFFFFFFF;`

#### Structs / classes (3)

- L5-9 _struct_ **`FVoxelData`** `struct FVoxelData`
  - L7 _member_ `uint3 VoxelIndex;`
  - L8 _member_ `uint MipLevel;`
- L11-15 _struct_ **`FVoxelDataPacked`** `struct FVoxelDataPacked`
  - L13 _member_ `uint LinearIndex;`
  - L14 _member_ `uint MipLevel;`
- L66-70 _struct_ **`FBox`** `struct FBox`
  - L68 _member_ `float3 Min;`
  - L69 _member_ `float3 Max;`

#### Functions (6)

- L17-29 _function_ `FVoxelDataPacked EncodeVoxelData(uint3 VoxelIndex, uint MipLevel, uint3 VolumeResolutionAtMipLevel)`
- L31-43 _function_ `FVoxelData DecodeVoxelData(FVoxelDataPacked VoxelDataPacked, uint3 VolumeResolutionAtMip0)`
- L45-51 _function_ `FVoxelData CreateEmptyVoxelData()`
- L53-56 _function_ `bool IsVoxelDataValid(FVoxelData VoxelData)`
- L58-64 _function_ `bool IsVoxelDataEqual(FVoxelData LHS, FVoxelData RHS)`
- L72-89 _function_ `FBox GetVoxelBoundingBox(FVoxelData VoxelData, int3 VolumeResolution, float3 ObjectBoundsMin, float3 ObjectBoundsMax)`

### `Shaders/Private/HeterogeneousVolumes/HeterogeneousVolumesStochasticFiltering.ush` (Private)

- lines: 74; parse: all-branches

#### Macros (#define, 4)

- L20 `#define STOCHASTIC_FILTERING_DISABLED 0`
- L21 `#define STOCHASTIC_FILTERING_CONSTANT 1`
- L22 `#define STOCHASTIC_FILTERING_TRILINEAR 2`
- L23 `#define STOCHASTIC_FILTERING_TRICUBIC 3`
- L3 #pragma `once`

#### Functions (4)

- L5-18 _function_ `int3 WeightedReservoir(int i, int j, float Prob, int3 Index, inout float Rand)`
- L25-28 _function_ `int3 StochasticFilteringConstant(float3 Position, inout float Rand)`
- L30-43 _function_ `int3 StochasticFilteringTrilinear(float3 Position, inout float Rand)`
- L45-73 _function_ `int3 StochasticFilteringTricubic(float3 Position, inout float Rand)`

### `Shaders/Private/HeterogeneousVolumes/HeterogeneousVolumesTracingUtils.ush` (Private)

- lines: 42; parse: all-branches
- includes: L5 `../VelocityCommon.ush`
- L3 #pragma `once`

#### Functions (2)

- L8-27 _function_ `float2 IntersectAABB(float3 RayOrigin, float3 RayDirection, float RayTMin, float RayTMax, float3 BoxMin, float3 BoxMax)` — Modified LineBoxIntersect() to operate at consistent RayDirection scale, within some [TMin, TMax] span
- L29-42 _function_ `float3 Calculate3DVelocityAtWorldPos(float3 WorldRayOrigin, float3 WorldRayDirection, float WorldHitT)`

### `Shaders/Private/HeterogeneousVolumes/HeterogeneousVolumesTransmittanceVolumeUtils.ush` (Private)

- lines: 34; parse: all-branches

#### Macros (#define, 3)

- L4 `#define DIM_USE_TRANSMITTANCE_VOLUME 0` _[#if !defined(DIM_USE_TRANSMITTANCE_VOLUME)]_
- L7 `#define LIGHTING_CACHE_TRANSMITTANCE 0`
- L8 `#define LIGHTING_CACHE_INSCATTERING 1`

#### Global resources (textures / buffers / samplers) (1)

- L12 _resource_ `Texture3D LightingCacheTexture;`

#### Global parameters (uniforms) (2)

- L10 _parameter_ `uint3 LightingCacheResolution;`
- L11 _parameter_ `float LightingCacheVoxelBias;`

#### Functions (3)

- L14-17 _function_ `uint3 GetLightingCacheResolution()`
- L19-22 _function_ `float GetLightingCacheVoxelBias()`
- L24-33 _function_ `float3 SampleLightingCache(float3 UVW, float MipLevel)`

### `Shaders/Private/HeterogeneousVolumes/HeterogeneousVolumesVisualizeCascades.usf` (Private)

- lines: 125; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../SceneTexturesCommon.ush`

#### Entry points (1)

- L92-125 _entry_ `[numthreads(THREADGROUP_SIZE_2D, THREADGROUP_SIZE_2D, 1)] void VisualizeCascadesCS( uint2 DispatchThreadId : SV_DispatchThreadID )` — stage: **compute** — C++: `FVisualizeCascadesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HeterogeneousVolumes/HeterogeneousVolumesVoxelGridPipeline.cpp:4580)

#### Structs / classes (1)

- L11-29 _struct_ **`FAdaptiveVolumetricShadowMap`** `struct FAdaptiveVolumetricShadowMap`
  - L13 _member_ `float4x4 TranslatedWorldToShadow[6];`
  - L14 _member_ `float3 TranslatedWorldOrigin[6];`
  - L15 _member_ `float4 TranslatedWorldPlane[6];`
  - L16 _member_ `float4 SplitDepths[6];`
  - L17 _member_ `float DownsampleFactor;`
  - L19 _member_ `int2 Resolution;`
  - L20 _member_ `int NumShadowMatrices;`
  - L21 _member_ `int MaxSampleCount;`
  - L22 _member_ `bool bIsEmpty;`
  - L23 _member_ `bool bIsDirectionalLight;`
  - L25 _member_ `StructuredBuffer<uint4> IndirectionBuffer;`
  - L26 _member_ `StructuredBuffer<uint> SampleBuffer;`
  - L27 _member_ `Texture2D<float4> RadianceTexture;`
  - L28 _member_ `SamplerState TextureSampler;`

#### Global resources (textures / buffers / samplers) (2)

- L8 _resource_ `Texture2D SceneDepthTexture;`
- L9 _resource_ `RWTexture2D<float4> RWVisualizationTexture;`

#### Global parameters (uniforms) (1)

- L6 _parameter_ `int DownsampleFactor;`

#### Functions (5)

- L31-55 _function_ `FAdaptiveVolumetricShadowMap GetAdaptiveVolumetricShadowMap()`
- L57-60 _function_ `int2 GetDownsampledResolution(int2 Resolution, int Factor)`
- L62-65 _function_ `int2 GetScaledViewRect()`
- L67-84 _function_ `float3 FaceToColor(int Face)`
- L86-90 _function_ `float GetMaxTraceDistance()`

### `Shaders/Private/HeterogeneousVolumes/HeterogeneousVolumesVoxelGridPipeline.usf` (Private)

- lines: 551; parse: all-branches
- includes: L3 `HeterogeneousVolumesVoxelGridTypes.ush`, L5 `../Common.ush`, L6 `../DeferredShadingCommon.ush`, L7 `../ComputeShaderUtils.ush`, L8 `HeterogeneousVolumesTracingUtils.ush`, L9 `HeterogeneousVolumesVoxelGridTraversal.ush`

#### Macros (#define, 4)

- L12 `#define THREADGROUP_SIZE_1D 1` _[#if !defined(THREADGROUP_SIZE_1D)]_
- L16 `#define THREADGROUP_SIZE_2D 1` _[#if !defined(THREADGROUP_SIZE_2D)]_
- L20 `#define THREADGROUP_SIZE_3D 1` _[#if !defined(THREADGROUP_SIZE_3D)]_
- L24 `#define DIM_ENABLE_INDIRECTION_GRID 0` _[#if !defined(DIM_ENABLE_INDIRECTION_GRID)]_

#### Entry points (8)

- L154-210 _entry_ `[numthreads(THREADGROUP_SIZE_3D, THREADGROUP_SIZE_3D, THREADGROUP_SIZE_3D)] void TopLevelGridCalculateVoxelSize( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID )` — stage: **compute** — C++: `FTopLevelGridCalculateVoxelSize` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HeterogeneousVolumes/HeterogeneousVolumesVoxelGridPipeline.cpp:842)
- L233-313 _entry_ `[numthreads(THREADGROUP_SIZE_3D, THREADGROUP_SIZE_3D, THREADGROUP_SIZE_3D)] void AllocateBottomLevelGrid( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID )` — stage: **compute** — C++: `FAllocateBottomLevelGrid` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HeterogeneousVolumes/HeterogeneousVolumesVoxelGridPipeline.cpp:892)
- L327-378 _entry_ `[numthreads(THREADGROUP_SIZE_3D, THREADGROUP_SIZE_3D, THREADGROUP_SIZE_3D)] void GenerateRasterTiles( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID )` — stage: **compute** — C++: `FGenerateRasterTiles` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HeterogeneousVolumes/HeterogeneousVolumesVoxelGridPipeline.cpp:938)
- L404-411 _entry_ `[numthreads(1, 1, 1)] void SetRasterizeBottomLevelGridIndirectArgs()` — stage: **compute** — C++: `FSetRasterizeBottomLevelGridIndirectArgs` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HeterogeneousVolumes/HeterogeneousVolumesVoxelGridPipeline.cpp:975)
- L415-447 _entry_ `[numthreads(THREADGROUP_SIZE_3D, THREADGROUP_SIZE_3D, THREADGROUP_SIZE_3D)] void TopLevelCreateBitmaskCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID )` — stage: **compute** — C++: `FTopLevelCreateBitmaskCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HeterogeneousVolumes/HeterogeneousVolumesVoxelGridPipeline.cpp:1149)
- L451-501 _entry_ `[numthreads(THREADGROUP_SIZE_3D, THREADGROUP_SIZE_3D, THREADGROUP_SIZE_3D)] void BuildMajorantVoxelGridCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID )` — stage: **compute** — C++: `FBuildMajorantVoxelGridCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HeterogeneousVolumes/HeterogeneousVolumesVoxelGridPipeline.cpp:1240)
- L510-545 _entry_ `[numthreads(THREADGROUP_SIZE_3D, THREADGROUP_SIZE_3D, THREADGROUP_SIZE_3D)] void DownsampleMajorantVoxelGridCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID )` — stage: **compute** — C++: `FDownsampleMajorantVoxelGridCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HeterogeneousVolumes/HeterogeneousVolumesVoxelGridPipeline.cpp:1276)
- L547-551 _entry_ `[numthreads(1, 1, 1)] void CopyMaximumIntoMajorantVoxelGridCS()` — stage: **compute** — C++: `FCopyMaxIntoMajorantVoxelGridCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HeterogeneousVolumes/HeterogeneousVolumesVoxelGridPipeline.cpp:1311)

#### Structs / classes (1)

- L315-319 _struct_ **`FRasterTileData`** `struct FRasterTileData`
  - L317 _member_ `uint TopLevelGridLinearIndex;`
  - L318 _member_ `uint BottomLevelGridLinearOffset;`

#### Global resources (textures / buffers / samplers) (17)

- L31 _resource_ `StructuredBuffer<FTopLevelGridBitmaskData> TopLevelGridBitmaskBuffer;`
- L32 _resource_ `StructuredBuffer<FTopLevelGridData> TopLevelGridBuffer;`
- L33 _resource_ `StructuredBuffer<FTopLevelGridData> IndirectionGridBuffer;`
- L34 _resource_ `StructuredBuffer<FScalarGridData> ExtinctionGridBuffer;`
- L35 _resource_ `StructuredBuffer<FVectorGridData> EmissionGridBuffer;`
- L36 _resource_ `StructuredBuffer<FVectorGridData> ScatteringGridBuffer;`
- L48 _resource_ `RWStructuredBuffer<FTopLevelGridData> RWTopLevelGridBuffer;`
- L230 _resource_ `RWBuffer<uint> RWIndirectionGridAllocatorBuffer;`
- L231 _resource_ `RWStructuredBuffer<FTopLevelGridData> RWIndirectionGridBuffer;`
- L324 _resource_ `RWBuffer<uint> RWRasterTileAllocatorBuffer;`
- L325 _resource_ `RWStructuredBuffer<FRasterTileData> RWRasterTileBuffer;`
- L381 _resource_ `Buffer<uint> RasterTileAllocatorBuffer;`
- L382 _resource_ `RWBuffer<uint> RWRasterizeBottomLevelGridIndirectArgsBuffer;`
- L413 _resource_ `RWStructuredBuffer<FTopLevelGridBitmaskData> RWTopLevelGridBitmaskBuffer;`
- L449 _resource_ `RWStructuredBuffer<FScalarGridData> RWMajorantVoxelGridBuffer;`
- L503 _resource_ `StructuredBuffer<FScalarGridData> InputBuffer;`
- L504 _resource_ `RWStructuredBuffer<FScalarGridData> RWOutputBuffer;`

#### Global parameters (uniforms) (18)

- L27 _parameter_ `int3 TopLevelGridResolution;`
- L28 _parameter_ `float3 TopLevelGridWorldBoundsMin;`
- L29 _parameter_ `float3 TopLevelGridWorldBoundsMax;`
- L38 _parameter_ `float3 PrimitiveWorldBoundsMin;`
- L39 _parameter_ `float3 PrimitiveWorldBoundsMax;`
- L41 _parameter_ `float ShadingRateInFrustum;`
- L42 _parameter_ `float ShadingRateOutOfFrustum;`
- L43 _parameter_ `float MinVoxelSizeInFrustum;`
- L44 _parameter_ `float MinVoxelSizeOutOfFrustum;`
- L45 _parameter_ `float DownsampleFactor;`
- L46 _parameter_ `int bUseProjectedPixelSize;`
- L225 _parameter_ `int MaxVoxelResolution;`
- L226 _parameter_ `int bSampleAtVertices;`
- L229 _parameter_ `int IndirectionGridBufferSize;` — Indirection Grid
- L321 _parameter_ `int RasterTileVoxelResolution;`
- L322 _parameter_ `int MaxNumRasterTiles;`
- L380 _parameter_ `int3 MaxDispatchThreadGroupsPerDimension;`
- L506 _parameter_ `int3 InputDimensions;`

#### groupshared (1)

- L508 _groupshared_ `groupshared float GSMajorant[THREADGROUP_SIZE_1D];`

#### Functions (10)

- L50-56 _function_ `void CalcVoxelBounds(float3 VoxelIndex, float3 GridResolution, float3 WorldBoundsMin, float3 WorldBoundsMax, inout float3 VoxelBoundsMin, inout float3 VoxelBoundsMax)`
- L58-62 _function_ `void CalcTopLevelVoxelBounds(float3 VoxelIndex, inout float3 VoxelBoundsMin, inout float3 VoxelBoundsMax)`
- L64-68 _function_ `float3 GetVoxelCenter(float3 VoxelIndex, inout float3 VoxelBoundsMin, inout float3 VoxelBoundsMax)`
- L70-78 _function_ `bool PrimitiveIntersectsVoxel(float3 VoxelBoundsMin, float3 VoxelBoundsMax)`
- L81-93 _function_ `float4 CreatePlane( float3 P_000, float3 P_100, float3 P_010 )` — Copied from LiveShadingPipeline.usf
- L95-98 _function_ `float CalcSignedDistance(float3 P, float4 Plane)`
- L100-114 _function_ `bool BoxIntersectsFrustum(float3 BoxOrigin, float3 BoxExtent, float4 Planes[5])`
- L116-152 _function_ `bool BoxIntersectsViewFrustum(float3 BoxOrigin, float3 BoxExtent)`
- L212-223 _function_ `int3 NextPowerOfTwo(int3 Value)`
- L384-402 _function_ `uint3 GetGroupCountWrapped(uint TargetGroupCount)`

### `Shaders/Private/HeterogeneousVolumes/HeterogeneousVolumesVoxelGridRendering.usf` (Private)

- lines: 765; parse: all-branches
- includes: L3 `HeterogeneousVolumesVoxelGridTypes.ush`, L5 `../Common.ush`, L6 `../DeferredShadingCommon.ush`, L7 `../ComputeShaderUtils.ush`, L8 `HeterogeneousVolumesTracingUtils.ush`, L9 `HeterogeneousVolumesVoxelGridTraversal.ush`, L10 `HeterogeneousVolumesVoxelGridRenderingUtils.ush`, L12 `../PathTracing/Utilities/PathTracingRandomSequence.ush`

#### Macros (#define, 14)

- L14 `#define DEBUG_MODE_DDA_MARCHING 0`
- L16 `#define DEBUG_MODE_SAMPLE_BASED_MARCHING 1`
- L17 `#define DEBUG_MODE_SAMPLE_BASED_MAJORANT 2`
- L18 `#define DEBUG_MODE_SAMPLE_BASED_MAX_MAJORANT 3`
- L19 `#define DEBUG_MODE_SAMPLE_BASED_MAJORANT_DDA 4`
- L21 `#define DEBUG_MODE_TRACKING_BASED_DELTA_TRACKING 5`
- L22 `#define DEBUG_MODE_TRACKING_BASED_RATIO_TRACKING 6`
- L23 `#define DEBUG_MODE_TRACKING_BASED_SPECTRAL_RATIO_TRACKING 7`
- L24 `#define DEBUG_MODE_TRACKING_BASED_MAJORANT_DDA 8`
- L26 `#define DEBUG_MODE_SAMPLING_BASED (DEBUG_MODE == DEBUG_MODE_SAMPLE_BASED_MARCHING) \|\| (DEBUG_MODE == DEBUG_MODE_SAMPLE_BASED_MAJORANT) \|\| (DEBUG_MODE == DEBUG_MODE_SAMPLE_BASED_MAX_MAJORANT) \|\| (DEBUG_MODE == DEBUG_MODE_SAMPLE_BASED_M ...` (5 lines)
- L32 `#define DEBUG_MODE_TRACKING_BASED (DEBUG_MODE == DEBUG_MODE_TRACKING_BASED_DELTA_TRACKING) \|\| (DEBUG_MODE == DEBUG_MODE_TRACKING_BASED_RATIO_TRACKING) \|\| (DEBUG_MODE == DEBUG_MODE_TRACKING_BASED_SPECTRAL_RATIO_TRACKING) \|\| (DEBUG_MODE ...` (5 lines)
- L38 `#define COLLISION_MODE_RATIO_TRACKING 0`
- L39 `#define COLLISION_MODE_MAX_COMPONENT 1`
- L40 `#define COLLISION_MODE_AVG_COMPONENT 2`

#### Entry points (1)

- L560-764 _entry_ `[numthreads(THREADGROUP_SIZE_2D, THREADGROUP_SIZE_2D, 1)] void RenderTransmittanceWithVoxelGridCS( uint2 GroupThreadId : SV_GroupThreadID, uint2 DispatchThreadId : SV_DispatchThreadID )` — stage: **compute** — C++: `FRenderTransmittanceWithVoxelGridCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HeterogeneousVolumes/HeterogeneousVolumesVoxelGridPipeline.cpp:1503)

#### Structs / classes (2)

- L42-54 _struct_ **`FRenderDebugData`** `struct FRenderDebugData`
  - L44 _member_ `float3 Estimate;`
  - L45 _member_ `float3 RayOrigin;`
  - L46 _member_ `float3 RayDirection;`
  - L47 _member_ `float TMin;`
  - L48 _member_ `float TMax;`
  - L49 _member_ `float Pdf;`
  - L50 _member_ `float Distance;`
  - L52 _member_ `float4x4 ScreenToTranslatedWorld;`
  - L53 _member_ `float4x4 ClipToTranslatedWorld;`
- L70-77 _struct_ **`FTrackingResult`** `struct FTrackingResult`
  - L72 _member_ `float3 Radiance;`
  - L73 _member_ `float3 Throughput;`
  - L74 _member_ `float Pdf;`
  - L75 _member_ `float Distance;`
  - L76 _member_ `bool bIsScattering;`

#### Global resources (textures / buffers / samplers) (2)

- L67 _resource_ `RWTexture2D<float4> RWLightingTexture;` — Output
- L68 _resource_ `RWStructuredBuffer<FRenderDebugData> RWDebugBuffer;`

#### Global parameters (uniforms) (6)

- L57 _parameter_ `int bJitter;` — Ray data
- L58 _parameter_ `float MaxTraceDistance;`
- L59 _parameter_ `float StepSize;`
- L60 _parameter_ `int MaxStepCount;`
- L63 _parameter_ `int3 GroupCount;` — Dispatch data
- L64 _parameter_ `int DebugMode;`

#### Functions (16)

- L79-90 _function_ `FTrackingResult CreateTrackingResult(float Distance)`
- L93-103 _function_ `FTrackingResult ConcatenateTrackingResult(FTrackingResult lhs, FTrackingResult rhs)` — Concatenates the result of rhs onto lhs
- L105-113 _function_ `FTrackingResult AddTrackingResult(FTrackingResult lhs, FTrackingResult rhs)`
- L115-123 _function_ `FTrackingResult DivideTrackingResult(FTrackingResult Value, int SPP)`
- L125-129 _function_ `float3 GetTranslatedWorldPos(float3 WorldPos)`
- L131-148 _function_ `FMajorantData EvalMajorant(float3 TranslatedWorldPos)`
- L150-163 _function_ `float CalcStepSizeLocal(float3 WorldDirection)`
- L165-188 _function_ `FTrackingResult SampleBasedMarch(float3 WorldRayOrigin, float3 WorldRayDirection, float TMin, float TMax, float WorldStepSize)`
- L190-211 _function_ `FTrackingResult SampleBasedMajorantMarch(float3 WorldRayOrigin, float3 WorldRayDirection, float TMin, float TMax, float WorldStepSize)`
- L213-234 _function_ `FTrackingResult SampleBasedMaxMajorantMarch(float3 WorldRayOrigin, float3 WorldRayDirection, float TMin, float TMax, float WorldStepSize)`
- L236-239 _function_ `float MaxComponent(float3 Value)`
- L241-275 _function_ `FTrackingResult DeltaTracking(float3 WorldRayOrigin, float3 WorldRayDirection, float TMin, float TMax, float SigmaBar, inout FRandomSequence RandSequence)`
- L277-364 _function_ `FTrackingResult SpectralWeightedDeltaTracking(float3 WorldRayOrigin, float3 WorldRayDirection, float TMin, float TMax, float SigmaBar, int CollisionMode, inout FRandomSequence RandSequence)`
- L366-399 _function_ `FTrackingResult RatioTracking(float3 WorldRayOrigin, float3 WorldRayDirection, float TMin, float TMax, float SigmaBar, inout FRandomSequence RandSequence)`
- L401-443 _function_ `FTrackingResult SpectralRatioTracking(float3 WorldRayOrigin, float3 WorldRayDirection, float TMin, float TMax, float SigmaBar, inout FRandomSequence RandSequence)`
- L445-558 _function_ `FTrackingResult DDABasedMajorantMarch(float3 WorldRayOrigin, float3 Direction, float TMin, float TMax, int DistanceSamplingMethod, int CollisionSamplingMethod, inout FRandomSequence RandSequence)`

### `Shaders/Private/HeterogeneousVolumes/HeterogeneousVolumesVoxelGridRenderingUtils.ush` (Private)

- lines: 317; parse: all-branches
- includes: L3 `HeterogeneousVolumesVoxelGridUtils.ush`, L4 `HeterogeneousVolumesFrustumVoxelGridUtils.ush`

#### Functions (9)

- L6-65 _function_ `float3 EvalExtinctionOutOfFrustum(float3 WorldPos, inout int LinearBottomLevelVoxelPos)`
- L67-97 _function_ `float3 EvalExtinctionInFrustum(float3 WorldPos, inout bool bInFrustum)`
- L99-109 _function_ `float3 EvalExtinction(float3 WorldPos)`
- L111-170 _function_ `float3 EvalAlbedoOutOfFrustum(float3 WorldPos, inout int LinearBottomLevelVoxelPos)`
- L172-202 _function_ `float3 EvalAlbedoInFrustum(float3 WorldPos, inout bool bInFrustum)`
- L204-214 _function_ `float3 EvalAlbedo(float3 WorldPos)`
- L216-273 _function_ `float3 EvalEmissionOutOfFrustum(float3 WorldPos, inout int LinearBottomLevelVoxelPos)`
- L275-305 _function_ `float3 EvalEmissionInFrustum(float3 WorldPos, inout bool bInFrustum)`
- L307-317 _function_ `float3 EvalEmission(float3 WorldPos)`

### `Shaders/Private/HeterogeneousVolumes/HeterogeneousVolumesVoxelGridShadows.usf` (Private)

- lines: 990; parse: all-branches
- includes: L3 `HeterogeneousVolumesVoxelGridTypes.ush`, L5 `../Common.ush`, L6 `../DeferredShadingCommon.ush`, L7 `../ComputeShaderUtils.ush`, L8 `HeterogeneousVolumesStochasticFiltering.ush`, L9 `HeterogeneousVolumesTracingUtils.ush`, L10 `HeterogeneousVolumesVoxelGridTraversal.ush`, L11 `HeterogeneousVolumesVoxelGridRenderingUtils.ush`, L12 `../BlueNoise.ush`, L14 `../PathTracing/Utilities/PathTracingRandomSequence.ush`, L291 `HeterogeneousVolumesLightingUtils.ush`, L292 `HeterogeneousVolumesRayMarchingUtils.ush`, L293 `HeterogeneousVolumesAdaptiveVolumetricShadowMapUtils.ush`

#### Macros (#define, 13)

- L17 `#define USE_AVSM_COMPRESSION 0` _[#if !defined(USE_AVSM_COMPRESSION)]_
- L244 `#define SUPPORT_CONTACT_SHADOWS 0`
- L246 `#define DYNAMICALLY_SHADOWED 1`
- L247 `#define TREAT_MAXDEPTH_UNSHADOWED 1`
- L249 `#define SHADOW_QUALITY 2`
- L250 `#define NO_TRANSLUCENCY_AVAILABLE `
- L258 `#define INDIRECT_LIGHTING_MODE_OFF 0`
- L259 `#define INDIRECT_LIGHTING_MODE_LIGHTING_CACHE 1`
- L260 `#define INDIRECT_LIGHTING_MODE_SINGLE_SCATTERING 2`
- L272 `#define FOG_INSCATTERING_MODE_OFF 0`
- L273 `#define FOG_INSCATTERING_MODE_REFERENCE 1`
- L274 `#define FOG_INSCATTERING_MODE_LINEAR_APPROX 2`
- L840 `#define MAX_SAMPLE_COUNT 2`

#### Entry points (6)

- L308-330 _entry_ `[numthreads(THREADGROUP_SIZE_2D, THREADGROUP_SIZE_2D, 1)] void ClearVolumetricShadowMapCS( uint2 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID )` — stage: **compute** — C++: `FClearVolumetricShadowMapCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HeterogeneousVolumes/HeterogeneousVolumesLiveShadingPipeline.cpp:1967)
- L453-612 _entry_ `[numthreads(THREADGROUP_SIZE_2D, THREADGROUP_SIZE_2D, 1)] void RenderVolumetricShadowMapForLightWithVoxelGridCS( uint2 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID )` — stage: **compute** — C++: `FRenderVolumetricShadowMapForLightWithVoxelGridCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HeterogeneousVolumes/HeterogeneousVolumesVoxelGridPipeline.cpp:3162)
- L646-756 _entry_ `[numthreads(THREADGROUP_SIZE_2D, THREADGROUP_SIZE_2D, 1)] void CompressVolumetricShadowMapCS( uint2 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID, uint GroupIndex : SV_GroupIndex )` — stage: **compute** — C++: `FCompressVolumetricShadowMapCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HeterogeneousVolumes/HeterogeneousVolumesVoxelGridPipeline.cpp:3215) — CompressVolumetricShadowMapCS Builds a compressed Adaptive Volumetric Shadow Map. The structure utilizes two buffers: 1) Per-pixel indirection buffer: a) Indirection pointer to transmittance function. b) Number of samples stored in the transmittance function (max = 64). c) Bounding depth information: (z_0, z_n) 2) Transmittance function atlas: The atlas is a densely packed two-level structure, containing spans of transmittance information for a given pixel. To optimize for query performance, only the top-level contains the first element, offsetting the second-level elements by 1 to optimize fo
- L761-838 _entry_ `[numthreads(THREADGROUP_SIZE_2D, THREADGROUP_SIZE_2D, 1)] void CombineVolumetricShadowMapsCS( uint2 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID, uint GroupIndex : SV_GroupIndex )` — stage: **compute** — C++: `FCombineVolumetricShadowMapsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HeterogeneousVolumes/HeterogeneousVolumesVoxelGridPipeline.cpp:3270)
- L872-953 _entry_ `[numthreads(THREADGROUP_SIZE_2D, THREADGROUP_SIZE_2D, 1)] void ConvertBeerLawShadowMapToVolumetricShadowMapCS( uint2 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID )` — stage: **compute** — C++: `FConvertBeerLawShadowMapToVolumetricShadowMapCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HeterogeneousVolumes/HeterogeneousVolumesVoxelGridPipeline.cpp:3319)
- L955-989 _entry_ `[numthreads(THREADGROUP_SIZE_2D, THREADGROUP_SIZE_2D, 1)] void ConvertVolumetricShadowMapToBeerLawShadowMapCS( uint3 DispatchThreadId : SV_DispatchThreadID )` — stage: **compute** — C++: `FConvertVolumetricShadowMapToBeerLawShadowMapCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HeterogeneousVolumes/HeterogeneousVolumesVoxelGridPipeline.cpp:3430)

#### Structs / classes (3)

- L49-52 _struct_ **`FVolumeSampleContext`** `struct FVolumeSampleContext`
  - L51 _member_ `float3 WorldPosition;`
- L333-340 _struct_ **`FVolumetricShadowMapDebugData`** `struct FVolumetricShadowMapDebugData` — Debug
  - L335 _member_ `float3 LightRayStart;`
  - L336 _member_ `float3 LightRayEnd;`
  - L337 _member_ `float3 RayOrigin;`
  - L338 _member_ `float3 RayEnd;`
  - L339 _member_ `float2 HitSpan;`
- L846-850 _struct_ **`FBeerShadowMapData`** `struct FBeerShadowMapData`
  - L848 _member_ `float T[2];`
  - L849 _member_ `float Tau[2];`

#### Global resources (textures / buffers / samplers) (11)

- L44 _resource_ `Texture2D<float4> BeerShadowMapTexture;` — Beer shadow map
- L47 _resource_ `RWTexture2D<float4> RWBeerShadowMapTexture;`
- L299 _resource_ `RWBuffer<int> RWVolumetricShadowLinkedListAllocatorBuffer;`
- L300 _resource_ `RWStructuredBuffer<uint2> RWVolumetricShadowLinkedListBuffer;`
- L342 _resource_ `RWStructuredBuffer<FVolumetricShadowMapDebugData> RWDebugBuffer;`
- L614 _resource_ `StructuredBuffer<uint2> VolumetricShadowLinkedListBuffer;`
- L616 _resource_ `RWBuffer<uint> RWVolumetricShadowIndirectionAllocatorBuffer;`
- L617 _resource_ `RWStructuredBuffer<uint4> RWVolumetricShadowIndirectionBuffer;`
- L618 _resource_ `RWStructuredBuffer<uint> RWVolumetricShadowTransmittanceBuffer;`
- L758 _resource_ `StructuredBuffer<uint2> VolumetricShadowLinkedListBuffer0;`
- L759 _resource_ `StructuredBuffer<uint2> VolumetricShadowLinkedListBuffer1;`

#### Global parameters (uniforms) (19)

- L21 _parameter_ `int bJitter;` — Ray data
- L22 _parameter_ `float ShadowStepSize;`
- L25 _parameter_ `int3 GroupCount;` — Dispatch data
- L26 _parameter_ `int ShadowDebugTweak;`
- L28 _parameter_ `int MaxStepCount;`
- L29 _parameter_ `int StochasticFilteringMode;`
- L31 _parameter_ `int NumShadowMatrices;`
- L32 _parameter_ `float4x4 TranslatedWorldToShadow[6];`
- L33 _parameter_ `float4x4 ShadowToTranslatedWorld[6];`
- L34 _parameter_ `float3 TranslatedWorldOrigin;`
- L37 _parameter_ `int bApplyEmissionAndTransmittance;` — Lighting
- L38 _parameter_ `int bApplyDirectLighting;`
- L39 _parameter_ `int bApplyShadowTransmittance;`
- L40 _parameter_ `int LightType;`
- L41 _parameter_ `float VolumetricScatteringIntensity;`
- L45 _parameter_ `int2 ShadowResolution;`
- L295 _parameter_ `int MaxSampleCount;`
- L296 _parameter_ `float AbsoluteErrorThreshold;`
- L297 _parameter_ `float RelativeErrorThreshold;`

#### groupshared (3)

- L620 _groupshared_ `groupshared int GSWarpSampleCount[THREADGROUP_SIZE_2D * THREADGROUP_SIZE_2D];`
- L621 _groupshared_ `groupshared int GSWarpPrefixSum[THREADGROUP_SIZE_2D * THREADGROUP_SIZE_2D];`
- L622 _groupshared_ `groupshared int GSWarpOffset;`

#### Functions (37)

- L54-61 _function_ `float4x4 IdentityMatrix()`
- L63-66 _function_ `float4x4 GetLocalToWorld()`
- L68-71 _function_ `float4x4 GetWorldToLocal()`
- L73-85 _function_ `float3 GetLocalBoundsMin()`
- L87-99 _function_ `float3 GetLocalBoundsMax()`
- L101-104 _function_ `float3 GetLocalBoundsOrigin()`
- L106-109 _function_ `float3 GetLocalBoundsExtent()`
- L111-114 _function_ `float GetMaxTraceDistance()`
- L116-119 _function_ `float GetMaxShadowTraceDistance()`
- L121-124 _function_ `float GetStepSize()`
- L126-129 _function_ `float GetStepFactor()`
- L131-134 _function_ `float GetShadowStepSize()`
- L136-139 _function_ `float GetShadowStepFactor()`
- L141-144 _function_ `int GetStochasticFilteringMode()`
- L146-149 _function_ `float EvalAmbientOcclusion(float3 WorldPosition)`
- L151-154 _function_ `float GetIndirectInscatteringFactor()`
- L156-159 _function_ `uint3 GetVolumeResolution()`
- L161-164 _function_ `uint GetNumVoxels()`
- L166-190 _function_ `FVolumeSampleContext CreateVolumeSampleContext(float3 LocalPosition, float3 WorldPosition, float3 FilterWidth, float MipLevel, float Rand, int StochasticFilteringMode)`
- L192-204 _function_ `FVolumeSampleContext CreateVolumeSampleContext( float3 LocalPosition, float3 WorldPosition, float3 WorldPosition_DDX, float3 WorldPosition_DDY, float MipLevel )`
- L206-218 _function_ `FVolumeSampleContext CreateVolumeSampleContext(float3 LocalPosition, float3 WorldPosition, float MipLevel)`
- L220-223 _function_ `float3 SampleExtinction(inout FVolumeSampleContext Context)`
- L225-228 _function_ `float3 SampleEmission(inout FVolumeSampleContext Context)`
- L230-242 _function_ `float3 SampleAlbedo(inout FVolumeSampleContext Context)`
- L253-256 _function_ `bool UseInscatteringVolume()` — Cinematic feature options
- L262-265 _function_ `int GetIndirectLightingMode()`
- L267-270 _function_ `bool IsOfflineRender()`
- L276-279 _function_ `int GetFogInscatteringMode()`
- L281-284 _function_ `int ShouldApplyHeightFog()`
- L286-289 _function_ `int ShouldApplyVolumetricFog()`
- L302-306 _function_ `uint GetLinearIndex(uint Face, uint2 PixelCoord)`
- L344-375 _function_ `uint FindSampleIndexWithLowestError( uint PixelIndex )`
- L377-385 _function_ `void AddSample(FAVSMSampleData Data, int PixelIndex, inout int PrevSampleIndex, inout int SampleIndex)`
- L387-412 _function_ `void ReplaceSample( int PixelIndex, int SampleIndex, FAVSMSampleData SampleData, int PrevPtrIndex, int NextPtrIndex )`
- L414-451 _function_ `void AddOrReplaceSample(FAVSMSampleData Data, int PixelIndex, inout int PrevSampleIndex, inout int SampleIndex)`
- L852-860 _function_ `float4 PackBeerShadowMapData(FBeerShadowMapData Data)`
- L862-870 _function_ `FBeerShadowMapData UnpackBeerShadowMapData(float4 PackedData)`

### `Shaders/Private/HeterogeneousVolumes/HeterogeneousVolumesVoxelGridTraversal.ush` (Private)

- lines: 531; parse: all-branches
- includes: L5 `HeterogeneousVolumesVoxelGridUtils.ush`, L6 `HeterogeneousVolumesFrustumVoxelGridUtils.ush`
- L3 #pragma `once`

#### Functions (6)

- L8-98 _function_ `void MarchBottomLevelVoxelGrid( float3 VoxelRayOrigin, float3 VoxelRayDirection, float VoxelRayTMin, float VoxelRayTMax, float WorldRayHitSpan, float3 TopLevelVoxelStartPos, float3 TopLevelVoxelEndPos, FTopLevelGridData TopLevelGridData, StructuredBuffer<FScalarGridData> ExtinctionGridBuffer, inout float3 Transmittance )`
- L100-206 _function_ `void MarchIndirectionOrthoVoxelGrid( float3 VoxelRayOrigin, float3 VoxelRayDirection, float VoxelRayTMin, float VoxelRayTMax, float WorldRayHitSpan, float3 TopLevelVoxelStartPos, float3 TopLevelVoxelEndPos, FTopLevelGridData TopLevelGridData, StructuredBuffer<FTopLevelGridData> IndirectionGridBuffer, StructuredBuffer<FScalarGridData> ExtinctionGridBuffer, inout float3 Transmittance )`
- L208-328 _function_ `void MarchTopLevelOrthoVoxelGrid( float3 VoxelRayOrigin, float3 VoxelRayDirection, float VoxelRayTMin, float VoxelRayTMax, float WorldRayHitSpan, bool bEnableIndirectionGrid, int3 TopLevelGridResolution, StructuredBuffer<FTopLevelGridData> TopLevelGridBuffer, StructuredBuffer<FTopLevelGridData> IndirectionGridBuffer, StructuredBuffer<FScalarGridData> ExtinctionGridBuffer, inout float3 Transmittance )`
- L330-373 _function_ `float3 TraceOrthoVoxelGrid(float3 Origin, float3 Direction, float TMin, float TMax)`
- L375-477 _function_ `void MarchTopLevelFrustumVoxelGrid( float3 VoxelRayOrigin, float3 VoxelRayDirection, float VoxelRayTMin, float VoxelRayTMax, float WorldRayHitSpan, int3 TopLevelGridResolution, StructuredBuffer<FTopLevelGridData> TopLevelGridBuffer, StructuredBuffer<FScalarGridData> ExtinctionGridBuffer, inout float3 Transmittance )`
- L479-530 _function_ `float3 TraceFrustumVoxelGrid(float3 Origin, float3 Direction, inout float TMin, inout float TMax)`

### `Shaders/Private/HeterogeneousVolumes/HeterogeneousVolumesVoxelGridTypes.ush` (Private)

- lines: 22; parse: all-branches

#### Structs / classes (4)

- L3-6 _struct_ **`FScalarGridData`** `struct FScalarGridData`
  - L5 _member_ `uint PackedData[2];`
- L8-11 _struct_ **`FVectorGridData`** `struct FVectorGridData`
  - L10 _member_ `uint PackedData[2];`
- L13-16 _struct_ **`FTopLevelGridData`** `struct FTopLevelGridData`
  - L15 _member_ `uint PackedData[1];`
- L18-21 _struct_ **`FTopLevelGridBitmaskData`** `struct FTopLevelGridBitmaskData`
  - L20 _member_ `uint PackedData[2];`

### `Shaders/Private/HeterogeneousVolumes/HeterogeneousVolumesVoxelGridUtils.ush` (Private)

- lines: 235; parse: all-branches
- includes: L5 `../MortonCode.ush`

#### Macros (#define, 1)

- L7 `#define EMPTY_VOXEL_INDEX 0x1FFFFFFF`
- L3 #pragma `once`

#### Structs / classes (1)

- L9-12 _struct_ **`FMajorantData`** `struct FMajorantData`
  - L11 _member_ `float Majorant;`

#### Functions (32)

- L14-19 _function_ `FMajorantData CreateMajorantData()`
- L21-25 _function_ `void UpdateMajorantData(inout FMajorantData MajorantData, float3 Value)`
- L27-32 _function_ `FMajorantData CreateMajorantData(float3 Majorant)`
- L35-38 _function_ `void UpdateMajorantData(inout FMajorantData MajorantData, FMajorantData Value)` — Updating majorant data should occur for a single media
- L41-44 _function_ `void MergeMajorantData(inout FMajorantData MajorantData, FMajorantData OverlappingMajorant)` — Merging majorant data should occur when mixing media
- L46-51 _function_ `FMajorantData GetMajorantData(FScalarGridData MajorantGridData)`
- L53-56 _function_ `void SetMajorantData(inout FScalarGridData MajorantGridData, FMajorantData MajorantData)`
- L58-65 _function_ `float3 GetExtinction(FScalarGridData ExtinctionGridData)`
- L67-71 _function_ `void SetExtinction(inout FScalarGridData ExtinctionGridData, float3 Extinction)`
- L73-80 _function_ `float3 GetEmission(FVectorGridData EmissionGridData)`
- L82-86 _function_ `void SetEmission(inout FVectorGridData EmissionGridData, float3 Emission)`
- L88-95 _function_ `float3 GetAlbedo(FVectorGridData AlbedoGridData)`
- L97-101 _function_ `void SetAlbedo(inout FVectorGridData AlbedoGridData, float3 Albedo)`
- L103-108 _function_ `FTopLevelGridData CreateTopLevelGridData(uint PackedData)`
- L110-113 _function_ `uint MortonEncode3(uint3 Voxel)`
- L115-119 _function_ `uint3 MortonDecode3(uint Morton)`
- L121-129 _function_ `int GetLinearIndex(uint3 VoxelIndex, int3 TopLevelGridResolution)`
- L131-142 _function_ `int3 GetVoxelIndex(int LinearIndex, int3 TopLevelGridResolution)`
- L144-148 _function_ `uint GetBottomLevelIndex(FTopLevelGridData TopLevelGridData)`
- L150-155 _function_ `void SetBottomLevelIndex(inout FTopLevelGridData TopLevelGridData, uint BottomLevelIndex)`
- L157-160 _function_ `bool IsBottomLevelAllocated(FTopLevelGridData TopLevelGridData)`
- L162-166 _function_ `bool IsBottomLevelEmpty(FTopLevelGridData TopLevelGridData)`
- L168-174 _function_ `int3 GetBottomLevelVoxelResolution(FTopLevelGridData TopLevelGridData)`
- L176-181 _function_ `void SetBottomLevelVoxelResolution(inout FTopLevelGridData TopLevelGridData, int3 BottomLevelVoxelResolution)`
- L183-186 _function_ `float GetVoxelSize(FTopLevelGridData TopLevelGridData)`
- L188-191 _function_ `void SetVoxelSize(inout FTopLevelGridData TopLevelGridData, float VoxelSize)`
- L194-198 _function_ `float3 GetExtinction(FTopLevelGridData TopLevelGridData, StructuredBuffer<FScalarGridData> ExtinctionGridBuffer)` — Convenience functions to retrieve the first element of a tile
- L200-206 _function_ `float3 GetExtinction(FTopLevelGridData TopLevelGridData, StructuredBuffer<FTopLevelGridData> IndirectionGridBuffer, StructuredBuffer<FScalarGridData> ExtinctionGridBuffer)`
- L208-212 _function_ `float3 GetEmission(FTopLevelGridData TopLevelGridData, StructuredBuffer<FVectorGridData> EmissionGridBuffer)`
- L214-220 _function_ `float3 GetEmission(FTopLevelGridData TopLevelGridData, StructuredBuffer<FTopLevelGridData> IndirectionGridBuffer, StructuredBuffer<FVectorGridData> EmissionGridBuffer)`
- L222-226 _function_ `float3 GetAlbedo(FTopLevelGridData TopLevelGridData, StructuredBuffer<FVectorGridData> ScatteringGridBuffer)`
- L228-234 _function_ `float3 GetAlbedo(FTopLevelGridData TopLevelGridData, StructuredBuffer<FTopLevelGridData> IndirectionGridBuffer, StructuredBuffer<FVectorGridData> ScatteringGridBuffer)`
