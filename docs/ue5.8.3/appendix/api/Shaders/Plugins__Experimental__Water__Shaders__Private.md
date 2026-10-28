# Shaders / Plugins/Experimental/Water/Shaders/Private

- files: 11; lines: 2807
- record kinds: cpp_binding=16, define=27, entry=15, function=94, groupshared=3, include=22, macro_call=3, member=84, parameter=74, prototype=2, resource=57, struct=19

### `Plugins/Experimental/Water/Shaders/Private/GerstnerWaveFunctions.ush` (Private)

- lines: 433; parse: all-branches
- includes: L9 `WaterDataFunctions.ush`

#### Macros (#define, 3)

- L11 `#define Gravity 980`
- L12 `#define SOLVE_NORMAL_Z 1`
- L13 `#define SteepnessThreshold 50`
- L7 #pragma `once`

#### Structs / classes (3)

- L15-19 _struct_ **`WaveOutput`** `struct WaveOutput`
  - L17 _member_ `float3 Normal;`
  - L18 _member_ `float3 WPO;`
- L21-27 _struct_ **`WaveOutputs`** `struct WaveOutputs`
  - L23 _member_ `WaveOutput LowFrequency;`
  - L24 _member_ `WaveOutput MiddleFrequency;`
  - L25 _member_ `WaveOutput HighFrequency;`
  - L26 _member_ `WaveOutput AllWaves;`
- L29-35 _struct_ **`GerstnerWaveRenderer`** `struct GerstnerWaveRenderer`
  - L31 _member_ `float2 WaveParamRTSize;`
  - L32 _member_ `int MaxWaves;`
  - L33 _member_ `float2 WorldPos;`
  - L34 _member_ `float Time;`

#### Functions (25)

- L37-61 _function_ `FWaveParams GetWaveRTData(GerstnerWaveRenderer inWaveRenderer, Texture2D inWaveParamsRT, SamplerState inWaveParamsRTSampler, int inWaveIndex, int inWaterBodyIndex)`
- L63-69 _function_ `WaveOutput AddWaves(WaveOutput inWaveA, WaveOutput inWaveB)`
- L71-74 _function_ `float3 FinalizeNormal(float3 inNormal)`
- L76-84 _function_ `float3 PackNormalAndWPO(WaveOutput inWave)`
- L86-92 _function_ `float3 UnpackWaveNormal(float inPackedWave)`
- L94-99 _function_ `float3 UnpackWaveWPO(float inPackedWave)`
- L101-111 _function_ `float2 GetWavePositionAndDispersion(GerstnerWaveRenderer inWaveRenderer, FWaveParams inWaveParams)`
- L113-133 _function_ `WaveOutput ComputeSingleWaveVectorized(float inWaveSin, float inWaveCos, float inDispersion, FWaveParams inWaveParams)`
- L135-170 _function_ `WaveOutput GetSingleGerstnerWave(GerstnerWaveRenderer inWaveRenderer, Texture2D inWaveParamsRT, SamplerState inWaveParamsRTSampler, int inWaveIndex, int inWaterBodyIndex)`
- L172-189 _function_ `WaveOutput GetAllGerstnerWaves(GerstnerWaveRenderer inWaveRenderer, Texture2D inWaveParamsRT, SamplerState inWaveParamsRTSampler, int inWaterBodyIndex)`
- L191-235 _function_ `WaveOutput GetAllGerstnerWavesVectorized(GerstnerWaveRenderer inWaveRenderer, int inWaterBodyIndex)`
- L237-254 _function_ `WaveOutput GetRangeGerstnerWaves(GerstnerWaveRenderer inWaveRenderer, Texture2D inWaveParamsRT, SamplerState inWaveParamsRTSampler, int inMinWaveIndex, int inMaxWaveIndex, int inWaterBodyIndex)`
- L257-260 _function_ `float ComputeWaveDepthAttenuationFactor(int InWaterBodyIndex, float InWaterDepth)` — TODO[ jbard] placeholder : Remove ASAP
- L262-272 _function_ `GerstnerWaveRenderer InitializeGerstnerWaveRenderer(float2 inWaveParamsRTSize, int inMaxwaves, float2 inWorldPos, float inTime)`
- L274-280 _function_ `WaveOutput AddWavesNew(WaveOutput inWaveA, WaveOutput inWaveB)`
- L282-285 _function_ `float3 FinalizeNormalNew(float3 inNormal)`
- L287-291 _function_ `FWaveParams GetWaveDataByWaveIndexNew(int InWaterBodyIndex, int InWaveIndex)`
- L293-301 _function_ `float3 PackNormalAndWPONew(WaveOutput inWave)`
- L303-356 _function_ `WaveOutput GetSingleGerstnerWaveNew(int InWaveIndex, FWaterBodyData InWaterBodyData, float InTime, FDFVector2 InWorldPos)`
- L358-375 _function_ `WaveOutput GetAllGerstnerWavesNew(int InWaterBodyIndex, float InTime, FDFVector2 InWorldPos)`
- L377 _function_ `WaveOutput GetAllGerstnerWavesNew(int InWaterBodyIndex, float InTime, FLWCVector2 InWorldPos)`
- L379-400 _function_ `WaveOutput GetRangeGerstnerWavesNew(int InMinWaveIndex, int InMaxWaveIndex, int InWaterBodyIndex, float InTime, FDFVector2 InWorldPos)`
- L402-415 _function_ `WaveOutputs GetPerFrequencyGerstnerWavesNew(int LowFrequencyMaxIndex, int MiddleFrequencyMaxIndex, int InWaterBodyIndex, float InTime, FDFVector2 InWorldPos)`
- L417-420 _function_ `WaveOutputs GetPerFrequencyGerstnerWavesNew(int LowFrequencyMaxIndex, int MiddleFrequencyMaxIndex, int InWaterBodyIndex, float InTime, FLWCVector2 InWorldPos)`
- L423-431 _function_ `float ComputeWaveDepthAttenuationFactorNew(int InWaterBodyIndex, float InWaterDepth)` — Returns the wave attenuation factor according to a given water body and a given water depth. Should match the CPU version (GetWaveAttenuationFactor)

### `Plugins/Experimental/Water/Shaders/Private/WaterDataFunctions.ush` (Private)

- lines: 215; parse: all-branches

#### Macros (#define, 4)

- L6 `#define PER_WAVE_DATA_SIZE 2` _[#if VM_SIMULATION==0]_
- L7 `#define PER_WATERZONE_DATA_SIZE 2` _[#if VM_SIMULATION==0]_
- L8 `#define PER_WATERBODY_DATA_SIZE 2` _[#if VM_SIMULATION==0]_
- L9 `#define PER_WATERZONEVIEW_DATA_SIZE 1` _[#if VM_SIMULATION==0]_
- L2 #pragma `once`

#### Structs / classes (4)

- L12-29 _struct_ **`FWaterBodyData`** `struct FWaterBodyData` — Struct containing the decoded water body data _[#if VM_SIMULATION==0]_
  - L15 _member_ `int WaterZoneIndex;` — Index of the water zone which owns this body. Points to the position of the water zone in the zone sub-buffer. _[#if VM_SIMULATION==0]_
  - L18 _member_ `int WaveDataIndex;` — Index into the wave data sub-buffer. _[#if VM_SIMULATION==0]_
  - L21 _member_ `int NumWaves;` — Number of waves to be read from the wave data buffer _[#if VM_SIMULATION==0]_
  - L24 _member_ `float TargetWaveMaskDepth;` — Target Wave Mask Depth _[#if VM_SIMULATION==0]_
  - L26 _member_ `float3 FixedVelocity;` _[#if VM_SIMULATION==0]_
  - L27 _member_ `float FixedZHeight;` _[#if VM_SIMULATION==0]_
  - L28 _member_ `float FixedWaterDepth;` _[#if VM_SIMULATION==0]_
- L32-38 _struct_ **`FWaterZoneData`** `struct FWaterZoneData` — Struct containing the decoded per-water zone data. _[#if VM_SIMULATION==0]_
  - L34 _member_ `float2 Location;` _[#if VM_SIMULATION==0]_
  - L35 _member_ `float2 Extent;` _[#if VM_SIMULATION==0]_
  - L36 _member_ `float2 HeightExtent;` _[#if VM_SIMULATION==0]_
  - L37 _member_ `float GroundZMin;` _[#if VM_SIMULATION==0]_
- L40-46 _struct_ **`FWaveParams`** `struct FWaveParams` _[#if VM_SIMULATION==0]_
  - L42 _member_ `float2 Direction;` _[#if VM_SIMULATION==0]_
  - L43 _member_ `float Wavelength;` _[#if VM_SIMULATION==0]_
  - L44 _member_ `float Amplitude;` _[#if VM_SIMULATION==0]_
  - L45 _member_ `float Steepness;` _[#if VM_SIMULATION==0]_
- L48-51 _struct_ **`FWaterZoneViewData`** `struct FWaterZoneViewData` _[#if VM_SIMULATION==0]_
  - L50 _member_ `float2 Location;` _[#if VM_SIMULATION==0]_

#### Functions (17)

- L53-56 _function_ `int GetWaterZoneDataOffset()` _[#if VM_SIMULATION==0]_
- L58-61 _function_ `int GetWaveDataOffset()` _[#if VM_SIMULATION==0]_
- L63-66 _function_ `int GetWaterZoneViewDataOffset()` _[#if VM_SIMULATION==0]_
- L68-71 _function_ `int GetNumWaterViewData()` _[#if VM_SIMULATION==0]_
- L73-79 _function_ `bool IsWaterLocalTessellationEnabled(int InWaterZoneIndex)` _[#if VM_SIMULATION==0]_
- L81-86 _function_ `int GetWaterInfoTextureViewIndex(int InWaterZoneIndex)` _[#if VM_SIMULATION==0]_
- L89-101 _function_ `FWaterBodyData DecodeWaterBodyData(float4 InDataToDecode0, float4 InDataToDecode1)` — Function to decode the raw data from the water indirection buffer _[#if VM_SIMULATION==0]_
- L103-110 _function_ `FWaterBodyData GetWaterBodyData(int InWaterBodyIndex)` _[#if VM_SIMULATION==0]_
- L113-122 _function_ `FWaveParams DecodeWaveParams(float4 InDataToDecode0, float4 InDataToDecode1)` — Function to decode the data for an individual gerstner wave from the water data buffer _[#if VM_SIMULATION==0]_
- L124-132 _function_ `FWaveParams GetWaveDataNew(int InWaveIndex, FWaterBodyData InWaterBodyData)` _[#if VM_SIMULATION==0]_
- L134-143 _function_ `FWaterZoneData DecodeWaterZoneData(float2 Location, float4 Data0, float4 Data1)` _[#if VM_SIMULATION==0]_
- L145-158 _function_ `FWaterZoneViewData GetWaterZoneViewData(int InWaterZoneIndex)` _[#if VM_SIMULATION==0]_
- L160-173 _function_ `FWaterZoneData GetWaterZoneData(int InWaterZoneIndex)` _[#if VM_SIMULATION==0]_
- L175-180 _function_ `FWaterZoneData GetWaterZoneDataForWaterBody(int InWaterBodyIndex)` _[#if VM_SIMULATION==0]_
- L182-190 _function_ `float DecodeWaterInfoGroundHeight(float4 WaterInfoSample, int WaterZoneIndex)` _[#if VM_SIMULATION==0]_
- L192-207 _function_ `float DecodeWaterInfoZHeight(float4 WaterInfoSample, int WaterZoneIndex)` _[#if VM_SIMULATION==0]_
- L209-213 _function_ `float2 DecodeWaterInfoVelocity(float4 WaterInfoSample, float MaxVelocity)` _[#if VM_SIMULATION==0]_

### `Plugins/Experimental/Water/Shaders/Private/WaterInfoFinalize.usf` (Private)

- lines: 78; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `/Engine/Private/DeferredShadingCommon.ush`

#### Entry points (1)

- L66-77 _entry_ `void Main( in FScreenVertexOutput Input, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FWaterInfoFinalizePS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterInfoRendering.cpp:228)

#### Structs / classes (1)

- L15-20 _struct_ **`FWaterInfo`** `struct FWaterInfo`
  - L17 _member_ `float2 Velocity;`
  - L18 _member_ `float NormalizedWaterZ;`
  - L19 _member_ `float NormalizedGroundZ;`

#### Global resources (textures / buffers / samplers) (1)

- L6 _resource_ `Texture2D<float4> WaterInfoTexture;`

#### Global parameters (uniforms) (5)

- L8 _parameter_ `float WaterZMin;`
- L9 _parameter_ `float WaterZMax;`
- L10 _parameter_ `float GroundZMin;`
- L11 _parameter_ `float CaptureZ;`
- L13 _parameter_ `int BlurRadius;`

#### Functions (2)

- L22-29 _function_ `FWaterInfo MakeWaterInfo(float4 InSampleData)`
- L31-64 _function_ `float2 VelocityBlur(float Radius, uint2 TextureCoordinates)`

### `Plugins/Experimental/Water/Shaders/Private/WaterInfoMerge.usf` (Private)

- lines: 110; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `/Engine/Private/DeferredShadingCommon.ush`

#### Entry points (1)

- L46-109 _entry_ `void Main( in FScreenVertexOutput Input, out float4 OutColor : SV_Target0 )` — stage: **pixel (from C++ binding)** — C++: `FWaterInfoMergePS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterInfoRendering.cpp:111)

#### Structs / classes (1)

- L20-24 _struct_ **`FWaterColorPassResult`** `struct FWaterColorPassResult`
  - L22 _member_ `float2 Velocity;`
  - L23 _member_ `float SceneDepth;`

#### Global resources (textures / buffers / samplers) (6)

- L6 _resource_ `Texture2D<float4> DepthTexture;`
- L7 _resource_ `SamplerState DepthTextureSampler;`
- L8 _resource_ `Texture2D<float4> ColorTexture;`
- L9 _resource_ `SamplerState ColorTextureSampler;`
- L10 _resource_ `Texture2D<float4> DilationTexture;`
- L11 _resource_ `SamplerState DilationTextureSampler;`

#### Global parameters (uniforms) (5)

- L14 _parameter_ `float2 WaterHeightExtents;`
- L15 _parameter_ `float GroundZMin;`
- L16 _parameter_ `float CaptureZ;`
- L17 _parameter_ `float UndergroundDilationDepthOffset;`
- L18 _parameter_ `float DilationOverwriteMinimumDistance;`

#### Functions (2)

- L26-32 _function_ `FWaterColorPassResult MakeWaterColorPassResult(float4 InSampleData)`
- L34-44 _function_ `float NormalizeHeight(float Height, float Min, float Max)`

### `Plugins/Experimental/Water/Shaders/Private/WaterMeshVertexFactory.ush` (Private)

- lines: 669; parse: all-branches
- includes: L3 `/Engine/Private/VertexFactoryCommon.ush`, L668 `/Engine/Private/VertexFactoryDefaultInterface.ush`

#### Macros (#define, 3)

- L6 `#define WATER_MESH_DRAW_INDIRECT 0` _[#if !defined(WATER_MESH_DRAW_INDIRECT)]_
- L9 `#define WATER_MESH_DRAW_INDIRECT_INTERNAL WATER_MESH_DRAW_INDIRECT && !RAYHITGROUPSHADER && !COMPUTESHADER`
- L447 `#define VF_IMPLEMENTED_GET_INSTANCE_HIT_PROXY_ID ` _[#if HIT_PROXY_SHADER]_

#### Structs / classes (7)

- L31-42 _struct_ **`FVertexFactoryInterpolantsVSToPS`** `struct FVertexFactoryInterpolantsVSToPS`
  - L34 _member_ `float4 TexCoords[(NUM_TEX_COORD_INTERPOLATORS+1)/2] : TEXCOORD0;` _[#if NUM_TEX_COORD_INTERPOLATORS]_
  - L37 _member_ `nointerpolation uint WaveParamIndex : WAVE_PARAM_INDEX;`
  - L40 _member_ `nointerpolation uint PrimitiveId : PRIMITIVE_ID;` _[#if VF_USE_PRIMITIVE_SCENE_DATA]_
- L47-72 _struct_ **`FVertexFactoryInput`** `struct FVertexFactoryInput` — Per-vertex inputs from bound vertex buffers
  - L49 _member_ `float4 Position : ATTRIBUTE0;`
  - L53 _member_ `uint InstanceData0 : ATTRIBUTE8;` _[#if WATER_MESH_DRAW_INDIRECT_INTERNAL && !INSTANCED_STEREO]_
  - L54 _member_ `uint InstanceData1 : ATTRIBUTE9;` _[#if WATER_MESH_DRAW_INDIRECT_INTERNAL && !INSTANCED_STEREO]_
  - L55 _member_ `uint InstanceData2 : ATTRIBUTE10;` _[#if WATER_MESH_DRAW_INDIRECT_INTERNAL && !INSTANCED_STEREO]_
  - L57 _member_ `uint InstanceData3 : ATTRIBUTE11;` _[#if WATER_MESH_DRAW_INDIRECT_INTERNAL && !INSTANCED_STEREO && HIT_PROXY_SHADER \|\| WITH_WATER_SELECTION_SUPPORT_VF]_
  - L62 _member_ `float4 InstanceData0 : ATTRIBUTE8;` _[#if !(WATER_MESH_DRAW_INDIRECT_INTERNAL)]_
  - L63 _member_ `float4 InstanceData1 : ATTRIBUTE9;` _[#if !(WATER_MESH_DRAW_INDIRECT_INTERNAL)]_
  - L65 _member_ `float4 InstanceData2 : ATTRIBUTE10;` — Store an HitProxyID per instance _[#if !(WATER_MESH_DRAW_INDIRECT_INTERNAL) && HIT_PROXY_SHADER \|\| WITH_WATER_SELECTION_SUPPORT_VF]_
- L77-96 _struct_ **`FPositionOnlyVertexFactoryInput`** `struct FPositionOnlyVertexFactoryInput` — Per-vertex inputs from bound vertex buffers.  Used by passes with a trimmed down position-only shader.
  - L79 _member_ `float4 Position : ATTRIBUTE0;`
  - L83 _member_ `uint InstanceData0 : ATTRIBUTE8;` _[#if WATER_MESH_DRAW_INDIRECT_INTERNAL && !INSTANCED_STEREO]_
  - L84 _member_ `uint InstanceData1 : ATTRIBUTE9;` _[#if WATER_MESH_DRAW_INDIRECT_INTERNAL && !INSTANCED_STEREO]_
  - L85 _member_ `uint InstanceData2 : ATTRIBUTE10;` _[#if WATER_MESH_DRAW_INDIRECT_INTERNAL && !INSTANCED_STEREO]_
  - L89 _member_ `float4 InstanceData0 : ATTRIBUTE8;` _[#if !(WATER_MESH_DRAW_INDIRECT_INTERNAL)]_
  - L90 _member_ `float4 InstanceData1 : ATTRIBUTE9;` _[#if !(WATER_MESH_DRAW_INDIRECT_INTERNAL)]_
- L101-121 _struct_ **`FPositionAndNormalOnlyVertexFactoryInput`** `struct FPositionAndNormalOnlyVertexFactoryInput` — Per-vertex inputs from bound vertex buffers.  Used by passes with a trimmed down position-and-normal-only shader.
  - L103 _member_ `float4 Position : ATTRIBUTE0;`
  - L104 _member_ `float4 Normal : ATTRIBUTE2;`
  - L108 _member_ `uint InstanceData0 : ATTRIBUTE8;` _[#if WATER_MESH_DRAW_INDIRECT_INTERNAL && !INSTANCED_STEREO]_
  - L109 _member_ `uint InstanceData1 : ATTRIBUTE9;` _[#if WATER_MESH_DRAW_INDIRECT_INTERNAL && !INSTANCED_STEREO]_
  - L110 _member_ `uint InstanceData2 : ATTRIBUTE10;` _[#if WATER_MESH_DRAW_INDIRECT_INTERNAL && !INSTANCED_STEREO]_
  - L114 _member_ `float4 InstanceData0 : ATTRIBUTE8;` _[#if !(WATER_MESH_DRAW_INDIRECT_INTERNAL)]_
  - L115 _member_ `float4 InstanceData1 : ATTRIBUTE9;` _[#if !(WATER_MESH_DRAW_INDIRECT_INTERNAL)]_
- L126-133 _struct_ **`FVertexFactoryIntermediates`** `struct FVertexFactoryIntermediates` — Caches intermediates that would otherwise have to be computed multiple times.  Avoids relying on the compiler to optimize out redundant operations.
  - L128 _member_ `float3 MorphedTranslatedWorldPos;`
  - L130 _member_ `uint WaveParamIndex;`
  - L132 _member_ `FSceneDataIntermediates SceneData;` — Cached primitive and instance data
- L284-295 _struct_ **`FWaterVertexFactoryInstanceInput`** `struct FWaterVertexFactoryInstanceInput`
  - L286 _member_ `float2 Position;`
  - L287 _member_ `float3 Translation;`
  - L288 _member_ `uint WaterBodyIndex;`
  - L289 _member_ `float LODLevel;`
  - L290 _member_ `float2 Scale;`
  - L291 _member_ `float HeightLODFactor;`
  - L292 _member_ `uint NumQuadsPerTileSide;`
  - L293 _member_ `bool bShouldMorph;`
  - L294 _member_ `bool bCanMorphTwice;`
- L630-633 _struct_ **`FVertexFactoryRayTracingInterpolants`** `struct FVertexFactoryRayTracingInterpolants` _[#if NEEDS_VERTEX_FACTORY_INTERPOLATION]_
  - L632 _member_ `FVertexFactoryInterpolantsVSToPS InterpolantsVSToPS;` _[#if NEEDS_VERTEX_FACTORY_INTERPOLATION]_

#### Global resources (textures / buffers / samplers) (5)

- L17 _resource_ `Buffer<uint> InstanceDataOffsetsBuffer;` _[#if WATER_MESH_DRAW_INDIRECT_INTERNAL && INSTANCED_STEREO]_
- L18 _resource_ `Buffer<uint> InstanceData0Buffer;` _[#if WATER_MESH_DRAW_INDIRECT_INTERNAL && INSTANCED_STEREO]_
- L19 _resource_ `Buffer<uint> InstanceData1Buffer;` _[#if WATER_MESH_DRAW_INDIRECT_INTERNAL && INSTANCED_STEREO]_
- L20 _resource_ `Buffer<uint> InstanceData2Buffer;` _[#if WATER_MESH_DRAW_INDIRECT_INTERNAL && INSTANCED_STEREO]_
- L22 _resource_ `Buffer<uint> InstanceData3Buffer;` _[#if WATER_MESH_DRAW_INDIRECT_INTERNAL && INSTANCED_STEREO && WITH_WATER_SELECTION_SUPPORT_VF]_

#### Global parameters (uniforms) (5)

- L12 _parameter_ `float3 QuadTreePosition;` _[#if WATER_MESH_DRAW_INDIRECT_INTERNAL]_
- L13 _parameter_ `float CaptureDepthRange;` _[#if WATER_MESH_DRAW_INDIRECT_INTERNAL]_
- L14 _parameter_ `uint bLODMorphingEnabled;` _[#if WATER_MESH_DRAW_INDIRECT_INTERNAL]_
- L25 _parameter_ `uint DrawBucketIndex;` _[#if WATER_MESH_DRAW_INDIRECT_INTERNAL && INSTANCED_STEREO]_
- L26 _parameter_ `uint StereoPassInstanceFactor;` _[#if WATER_MESH_DRAW_INDIRECT_INTERNAL && INSTANCED_STEREO]_

#### Functions (33)

- L135-138 _function_ `FPrimitiveSceneData GetPrimitiveData(FVertexFactoryIntermediates Intermediates)`
- L140-147 _function_ `uint GetPrimitiveId(FVertexFactoryInterpolantsVSToPS Interpolants)`
- L149-154 _function_ `void SetPrimitiveId(inout FVertexFactoryInterpolantsVSToPS Interpolants, uint PrimitiveId)`
- L157-161 _function_ `float2 GetUV(FVertexFactoryInterpolantsVSToPS Interpolants, int UVIndex)` _[#if NUM_TEX_COORD_INTERPOLATORS]_
- L163-174 _function_ `void SetUV(inout FVertexFactoryInterpolantsVSToPS Interpolants, int UVIndex, float2 InValue)` _[#if NUM_TEX_COORD_INTERPOLATORS]_
- L178-199 _function_ `FMaterialPixelParameters GetMaterialPixelParameters(FVertexFactoryInterpolantsVSToPS Interpolants, float4 SvPosition)` — Converts from vertex factory specific interpolants to a FMaterialPixelParameters, which is used by material inputs.
- L205-250 _function_ `FMaterialVertexParameters GetMaterialVertexParameters( FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, float3 WorldPosition, half3x3 TangentToLocal, bool bIsPreviousFrame = false)` — Converts from vertex factory specific input to a FMaterialVertexParameters, which is used by vertex shader material inputs.
- L252-282 _function_ `float3 MorphTranslatedWorldPosition(float3 OriginalTranslatedWorldPos, float2 InMorphOriginTWS, float LODLevel, float InLODScale, float2 QuadSize, float HeightLODFactor, out float LODFactor)`
- L299-350 _function_ `FWaterVertexFactoryInstanceInput UnpackWaterVertexFactoryInstanceInput(float4 InPosition, uint InData0, uint InData1, uint InData2)` _[#if WATER_MESH_DRAW_INDIRECT_INTERNAL]_
- L354-370 _function_ `FWaterVertexFactoryInstanceInput UnpackWaterVertexFactoryInstanceInput(float4 InPosition, float4 InData0, float4 InData1)` _[#if !(WATER_MESH_DRAW_INDIRECT_INTERNAL)]_
- L374-443 _function_ `FVertexFactoryIntermediates GetVertexFactoryIntermediates(FVertexFactoryInput Input)`
- L449-466 _function_ `float4 VertexFactoryGetInstanceHitProxyId(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)` _[#if HIT_PROXY_SHADER]_
- L476-479 _function_ `half3x3 VertexFactoryGetTangentToLocal( FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates )` — Get the 3x3 tangent basis vectors for this vertex factory this vertex factory will calculate the binormal on-the-fly @param Input - vertex input stream structure @return 3x3 matrix
- L482-485 _function_ `float4 VertexFactoryGetWorldPosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)` — @return translated world position
- L487-492 _function_ `float4 TransformTranslatedWorldToLocal(float4 TranslatedWorldPosition, FDFInverseMatrix WorldToLocal)`
- L495-499 _function_ `float3 VertexFactoryGetInstanceSpacePosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)` — local position relative to instance
- L501-504 _function_ `float4 VertexFactoryGetRasterizedWorldPosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, float4 InWorldPosition)`
- L506-509 _function_ `float3 VertexFactoryGetPositionForVertexLighting(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, float3 TranslatedWorldPosition)`
- L511-536 _function_ `FVertexFactoryInterpolantsVSToPS VertexFactoryGetInterpolantsVSToPS(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, FMaterialVertexParameters VertexParameters)`
- L539-542 _function_ `float4 VertexFactoryGetWorldPosition(FPositionOnlyVertexFactoryInput Input)` — for depth-only pass
- L545-548 _function_ `float4 VertexFactoryGetPreviousWorldPosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)` — @return previous translated world position
- L551-554 _function_ `float3 VertexFactoryGetPreviousInstanceSpacePosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)` — local position relative to instance
- L556-560 _function_ `float4 VertexFactoryGetTranslatedPrimitiveVolumeBounds(FVertexFactoryInterpolantsVSToPS Interpolants)`
- L562-565 _function_ `uint VertexFactoryGetPrimitiveId(FVertexFactoryInterpolantsVSToPS Interpolants)`
- L567-570 _function_ `float3 VertexFactoryGetWorldNormal(FPositionAndNormalOnlyVertexFactoryInput Input)`
- L572-576 _function_ `float3 VertexFactoryGetWorldNormal(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)`
- L579-596 _function_ `FVertexFactoryInput LoadVertexFactoryInputForHGS(uint TriangleIndex, int VertexIndex)` _[#if RAYHITGROUPSHADER]_
- L600-621 _function_ `FVertexFactoryInput LoadVertexFactoryInputForDynamicUpdate(uint TriangleIndex, int VertexIndex, uint PrimitiveId, uint DrawInstanceId)` _[#if COMPUTESHADER]_
- L623-626 _function_ `uint GetNumRayTracingDynamicMeshVerticesIndirect()` _[#if COMPUTESHADER]_
- L635-642 _function_ `float2 VertexFactoryGetRayTracingTextureCoordinate( FVertexFactoryRayTracingInterpolants Interpolants )` _[#if NEEDS_VERTEX_FACTORY_INTERPOLATION]_
- L644-647 _function_ `FVertexFactoryInterpolantsVSToPS VertexFactoryAssignInterpolants(FVertexFactoryRayTracingInterpolants Input)` _[#if NEEDS_VERTEX_FACTORY_INTERPOLATION]_
- L649-654 _function_ `FVertexFactoryRayTracingInterpolants VertexFactoryGetRayTracingInterpolants(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, FMaterialVertexParameters VertexParameters)` _[#if NEEDS_VERTEX_FACTORY_INTERPOLATION]_
- L656-665 _function_ `FVertexFactoryRayTracingInterpolants VertexFactoryInterpolate(FVertexFactoryRayTracingInterpolants a, float aInterp, FVertexFactoryRayTracingInterpolants b, float bInterp)` _[#if NEEDS_VERTEX_FACTORY_INTERPOLATION]_

#### Prototypes (2)

- L201 _prototype_ `float3 VertexFactoryGetPreviousInstanceSpacePosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)`
- L202 _prototype_ `float3 VertexFactoryGetInstanceSpacePosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)`

#### Top-level macro invocations (3)

- L69-72 _macro_call_ `VF_GPUSCENE_DECLARE_INPUT_BLOCK(13) VF_INSTANCED_STEREO_DECLARE_INPUT_BLOCK() VF_MOBILE_MULTI_VIEW_DECLARE_INPUT_BLOCK()` (scope `FVertexFactoryInput`)
- L93-96 _macro_call_ `VF_GPUSCENE_DECLARE_INPUT_BLOCK(1) VF_INSTANCED_STEREO_DECLARE_INPUT_BLOCK() VF_MOBILE_MULTI_VIEW_DECLARE_INPUT_BLOCK()` (scope `FPositionOnlyVertexFactoryInput`)
- L118-121 _macro_call_ `VF_GPUSCENE_DECLARE_INPUT_BLOCK(1) VF_INSTANCED_STEREO_DECLARE_INPUT_BLOCK() VF_MOBILE_MULTI_VIEW_DECLARE_INPUT_BLOCK()` (scope `FPositionAndNormalOnlyVertexFactoryInput`)

#### C++ shader bindings (IMPLEMENT_* naming this file, 1)

- `\
		EVertexFactoryFlags::UsedWithMaterials																									\
		\| EVertexFactoryFlags::SupportsDynamicLighting																							\
		\| EVertexFactoryFlags::SupportsPrecisePrevWorldPos																						\
		\| EVertexFactoryFlags::SupportsPrimitiveIdStream																						\
		\| EVertexFactoryFlags::SupportsRayTracing																								\
		\| EVertexFactoryFlags::SupportsRayTracingDynamicGeometry																				\
		\| EVertexFactoryFlags::SupportsPSOPrecaching																							\` → entry not found in file (macro-generated or #include'd); C++ `template<>`  via IMPLEMENT_TEMPLATE_VERTEX_FACTORY_TYPE (Plugins/Experimental/Water/Source/Runtime/Private/WaterVertexFactory.cpp:175)

### `Plugins/Experimental/Water/Shaders/Private/WaterQuadTreeBuild.usf` (Private)

- lines: 55; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `/Engine/Private/PackUnpack.ush`, L5 `WaterQuadTreeCommon.ush`

#### Entry points (1)

- L11-55 _entry_ `void Main(in float4 Position : SV_Position, out float4 OutColor : SV_Target0, out float4 OutWaterZBounds : SV_Target1)` — stage: **pixel (from C++ binding)** — C++: `FWaterQuadTreeBuildPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:145)

#### Global resources (textures / buffers / samplers) (2)

- L7 _resource_ `Texture2D<float4> QuadTreeTexture;`
- L8 _resource_ `Texture2D<float4> WaterZBoundsTexture;`

#### Global parameters (uniforms) (1)

- L9 _parameter_ `int InputMipLevelIndex;`

### `Plugins/Experimental/Water/Shaders/Private/WaterQuadTreeCommon.ush` (Private)

- lines: 73; parse: all-branches
- includes: L3 `/Engine/Private/PackUnpack.ush`

#### Macros (#define, 3)

- L5 `#define WATER_BODY_TYPE_RIVER 0`
- L6 `#define WATER_BODY_TYPE_LAKE 1`
- L7 `#define WATER_BODY_TYPE_OCEAN 2`

#### Structs / classes (2)

- L9-21 _struct_ **`FWaterBodyRenderData`** `struct FWaterBodyRenderData`
  - L11 _member_ `uint WaterBodyIndex;`
  - L12 _member_ `uint MaterialIndex;`
  - L13 _member_ `uint RiverToLakeMaterialIndex;`
  - L14 _member_ `uint RiverToOceanMaterialIndex;`
  - L15 _member_ `uint WaterBodyType;`
  - L16 _member_ `uint HitProxyColorAndIsSelected;`
  - L17 _member_ `float SurfaceBaseHeight;`
  - L18 _member_ `float MinZ;`
  - L19 _member_ `float MaxZ;`
  - L20 _member_ `float MaxWaveHeight;`
- L23-29 _struct_ **`FWaterQuadTreeNode`** `struct FWaterQuadTreeNode`
  - L25 _member_ `uint WaterBodyRenderDataIndex;`
  - L26 _member_ `uint TransitionWaterBodyRenderDataIndex;`
  - L27 _member_ `bool bHasCompleteSubtree;`
  - L28 _member_ `bool bIsSubtreeSameWaterBody;`

#### Functions (4)

- L31-40 _function_ `uint WaterQuadTreePackNode(FWaterQuadTreeNode Node)`
- L42-51 _function_ `float4 WaterQuadTreePackNodeRGBA8(FWaterQuadTreeNode Node)`
- L53-62 _function_ `FWaterQuadTreeNode WaterQuadTreeUnpackNode(uint Packed)`
- L64-72 _function_ `FWaterQuadTreeNode WaterQuadTreeUnpackNodeRGBA8(float4 Packed)`

### `Plugins/Experimental/Water/Shaders/Private/WaterQuadTreeDraws.usf` (Private)

- lines: 908; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `/Engine/Private/PackUnpack.ush`, L5 `WaterQuadTreeCommon.ush`, L132 `/Engine/Private/Nanite/NaniteHZBCull.ush` [defined(QUAD_TREE_TRAVERSE)], L494 `/Engine/Private/WaveOpUtil.ush` [defined(COMPUTE_BUCKET_PREFIX_SUM) && PARALLEL_PREFIX_SUM], L829 `/Engine/Private/ShaderPrint.ush` [DEBUG_SHOW_TILES]

#### Macros (#define, 8)

- L57 `#define PRECISE_OCCLUSION_QUERIES 0` _[#if defined(INITIALIZE_INDIRECT_ARGS) && !defined(PRECISE_OCCLUSION_QUERIES)]_
- L135 `#define PRECISE_OCCLUSION_QUERIES 0` _[#if defined(QUAD_TREE_TRAVERSE) && !defined(PRECISE_OCCLUSION_QUERIES)]_
- L413 `#define PRECISE_OCCLUSION_QUERIES 0` _[#if defined(COMPUTE_BUCKET_COUNTS) && !defined(PRECISE_OCCLUSION_QUERIES)]_
- L483 `#define PARALLEL_PREFIX_SUM 0` _[#if defined(COMPUTE_BUCKET_PREFIX_SUM) && !defined(PARALLEL_PREFIX_SUM)]_
- L496 `#define GROUP_SIZE 128` _[#if defined(COMPUTE_BUCKET_PREFIX_SUM) && PARALLEL_PREFIX_SUM]_
- L497 `#define ARRAY_SIZE (GROUP_SIZE * 2)` _[#if defined(COMPUTE_BUCKET_PREFIX_SUM) && PARALLEL_PREFIX_SUM]_
- L663 `#define PRECISE_OCCLUSION_QUERIES 0` _[#if defined(GENERATE_INSTANCE_DATA) && !defined(PRECISE_OCCLUSION_QUERIES)]_
- L832 `#define PRECISE_OCCLUSION_QUERIES 0` _[#if DEBUG_SHOW_TILES && !defined(PRECISE_OCCLUSION_QUERIES)]_

#### Entry points (9)

- L68-103 _entry_ `[numthreads(64, 1, 1)] void MainCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FWaterQuadTreeInitializeIndirectArgsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:170) — C++: `FWaterQuadTreeClearPerViewBuffersCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:190) — C++: `FWaterQuadTreeTraverseCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:233) — C++: `FWaterQuadTreeBucketCountsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:306) — C++: `FWaterQuadTreeBucketPrefixSumCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:331) — C++: `FWaterQuadTreeGenerateInstanceDataCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:380) — C++: `FWaterQuadTreeDebugCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:416) _[#if defined(INITIALIZE_INDIRECT_ARGS)]_
- L113-126 _entry_ `[numthreads(64, 1, 1)] void MainCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FWaterQuadTreeInitializeIndirectArgsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:170) — C++: `FWaterQuadTreeClearPerViewBuffersCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:190) — C++: `FWaterQuadTreeTraverseCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:233) — C++: `FWaterQuadTreeBucketCountsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:306) — C++: `FWaterQuadTreeBucketPrefixSumCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:331) — C++: `FWaterQuadTreeGenerateInstanceDataCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:380) — C++: `FWaterQuadTreeDebugCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:416) _[#if defined(CLEAR_PER_VIEW_BUFFERS)]_
- L207-356 _entry_ `[numthreads(64, 1, 1)] void MainCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FWaterQuadTreeInitializeIndirectArgsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:170) — C++: `FWaterQuadTreeClearPerViewBuffersCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:190) — C++: `FWaterQuadTreeTraverseCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:233) — C++: `FWaterQuadTreeBucketCountsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:306) — C++: `FWaterQuadTreeBucketPrefixSumCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:331) — C++: `FWaterQuadTreeGenerateInstanceDataCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:380) — C++: `FWaterQuadTreeDebugCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:416) _[#if defined(QUAD_TREE_TRAVERSE)]_
- L364-390 _entry_ `void MainVS( in float3 InPosition : ATTRIBUTE0, in uint InInstanceId : SV_InstanceID, out nointerpolation uint OutQueryIndex : QUERY_INDEX, out float4 OutPosition : SV_Position )` — stage: **vertex (from C++ binding)** — C++: `FWaterQuadTreeOcclusionQueryVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:252) _[#if defined(OCCLUSION_QUERY_RASTER_VS)]_
- L398-406 _entry_ `EARLYDEPTHSTENCIL void MainPS( in uint InQueryIndex : QUERY_INDEX, out float4 OutColor : SV_Target0 )` — stage: **pixel (from C++ binding)** — C++: `FWaterQuadTreeOcclusionQueryPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:271) _[#if defined(OCCLUSION_QUERY_RASTER_PS)]_
- L428-476 _entry_ `[numthreads(64, 1, 1)] void MainCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FWaterQuadTreeInitializeIndirectArgsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:170) — C++: `FWaterQuadTreeClearPerViewBuffersCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:190) — C++: `FWaterQuadTreeTraverseCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:233) — C++: `FWaterQuadTreeBucketCountsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:306) — C++: `FWaterQuadTreeBucketPrefixSumCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:331) — C++: `FWaterQuadTreeGenerateInstanceDataCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:380) — C++: `FWaterQuadTreeDebugCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:416) _[#if defined(COMPUTE_BUCKET_COUNTS)]_
- L525-656 _entry_ `[numthreads(GROUP_SIZE, 1, 1)] [numthreads(1, 1, 1)] void MainCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FWaterQuadTreeInitializeIndirectArgsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:170) — C++: `FWaterQuadTreeClearPerViewBuffersCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:190) — C++: `FWaterQuadTreeTraverseCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:233) — C++: `FWaterQuadTreeBucketCountsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:306) — C++: `FWaterQuadTreeBucketPrefixSumCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:331) — C++: `FWaterQuadTreeGenerateInstanceDataCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:380) — C++: `FWaterQuadTreeDebugCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:416) _[#if defined(COMPUTE_BUCKET_PREFIX_SUM) && PARALLEL_PREFIX_SUM]_
- L699-823 _entry_ `[numthreads(64, 1, 1)] void MainCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FWaterQuadTreeInitializeIndirectArgsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:170) — C++: `FWaterQuadTreeClearPerViewBuffersCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:190) — C++: `FWaterQuadTreeTraverseCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:233) — C++: `FWaterQuadTreeBucketCountsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:306) — C++: `FWaterQuadTreeBucketPrefixSumCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:331) — C++: `FWaterQuadTreeGenerateInstanceDataCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:380) — C++: `FWaterQuadTreeDebugCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:416) _[#if defined(GENERATE_INSTANCE_DATA)]_
- L848-906 _entry_ `[numthreads(64, 1, 1)] void MainCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FWaterQuadTreeInitializeIndirectArgsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:170) — C++: `FWaterQuadTreeClearPerViewBuffersCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:190) — C++: `FWaterQuadTreeTraverseCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:233) — C++: `FWaterQuadTreeBucketCountsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:306) — C++: `FWaterQuadTreeBucketPrefixSumCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:331) — C++: `FWaterQuadTreeGenerateInstanceDataCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:380) — C++: `FWaterQuadTreeDebugCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:416) _[#if DEBUG_SHOW_TILES]_

#### Structs / classes (1)

- L27-31 _struct_ **`FWaterLODParams`** `struct FWaterLODParams`
  - L29 _member_ `int LowestLOD;`
  - L30 _member_ `float HeightLODFactor;`

#### Global resources (textures / buffers / samplers) (36)

- L60 _resource_ `RWBuffer<uint> IndirectArgs;` _[#if defined(INITIALIZE_INDIRECT_ARGS)]_
- L62 _resource_ `RWBuffer<uint> OcclusionQueryArgs;` _[#if defined(INITIALIZE_INDIRECT_ARGS) && PRECISE_OCCLUSION_QUERIES]_
- L109 _resource_ `RWByteAddressBuffer BucketCounts;` _[#if defined(CLEAR_PER_VIEW_BUFFERS)]_
- L110 _resource_ `RWByteAddressBuffer PackedNodes;` _[#if defined(CLEAR_PER_VIEW_BUFFERS)]_
- L138 _resource_ `RWByteAddressBuffer PackedNodes;` _[#if defined(QUAD_TREE_TRAVERSE)]_
- L141 _resource_ `RWBuffer<float4> OcclusionQueryBoxes;` _[#if defined(QUAD_TREE_TRAVERSE) && PRECISE_OCCLUSION_QUERIES]_
- L142 _resource_ `RWBuffer<uint> OcclusionVisibility;` _[#if defined(QUAD_TREE_TRAVERSE) && PRECISE_OCCLUSION_QUERIES]_
- L143 _resource_ `RWBuffer<uint> OcclusionQueryArgs;` _[#if defined(QUAD_TREE_TRAVERSE) && PRECISE_OCCLUSION_QUERIES]_
- L146 _resource_ `Texture2D<float4> QuadTreeTexture;` _[#if defined(QUAD_TREE_TRAVERSE)]_
- L147 _resource_ `Texture2D<float4> WaterZBoundsTexture;` _[#if defined(QUAD_TREE_TRAVERSE)]_
- L148 _resource_ `StructuredBuffer<FWaterBodyRenderData> WaterBodyRenderData;` _[#if defined(QUAD_TREE_TRAVERSE)]_
- L362 _resource_ `Buffer<float4> OcclusionQueryBoxes;` _[#if defined(OCCLUSION_QUERY_RASTER_VS)]_
- L396 _resource_ `RWBuffer<uint> Visibility;` _[#if defined(OCCLUSION_QUERY_RASTER_PS)]_
- L416 _resource_ `RWByteAddressBuffer BucketCounts;` _[#if defined(COMPUTE_BUCKET_COUNTS)]_
- L417 _resource_ `Texture2D<float4> QuadTreeTexture;` _[#if defined(COMPUTE_BUCKET_COUNTS)]_
- L418 _resource_ `StructuredBuffer<FWaterBodyRenderData> WaterBodyRenderData;` _[#if defined(COMPUTE_BUCKET_COUNTS)]_
- L419 _resource_ `ByteAddressBuffer PackedNodes;` _[#if defined(COMPUTE_BUCKET_COUNTS)]_
- L421 _resource_ `Buffer<uint> OcclusionResults;` _[#if defined(COMPUTE_BUCKET_COUNTS) && PRECISE_OCCLUSION_QUERIES]_
- L486 _resource_ `RWBuffer<uint> BucketPrefixSums;` _[#if defined(COMPUTE_BUCKET_PREFIX_SUM)]_
- L487 _resource_ `ByteAddressBuffer BucketCounts;` _[#if defined(COMPUTE_BUCKET_PREFIX_SUM)]_
- L666 _resource_ `RWBuffer<uint> IndirectArgs;` _[#if defined(GENERATE_INSTANCE_DATA)]_
- L667 _resource_ `RWBuffer<uint> InstanceData0;` _[#if defined(GENERATE_INSTANCE_DATA)]_
- L668 _resource_ `RWBuffer<uint> InstanceData1;` _[#if defined(GENERATE_INSTANCE_DATA)]_
- L669 _resource_ `RWBuffer<uint> InstanceData2;` _[#if defined(GENERATE_INSTANCE_DATA)]_
- L670 _resource_ `RWBuffer<uint> InstanceData3;` _[#if defined(GENERATE_INSTANCE_DATA)]_
- L671 _resource_ `Texture2D<float4> QuadTreeTexture;` _[#if defined(GENERATE_INSTANCE_DATA)]_
- L672 _resource_ `Texture2D<float4> WaterZBoundsTexture;` _[#if defined(GENERATE_INSTANCE_DATA)]_
- L673 _resource_ `StructuredBuffer<FWaterBodyRenderData> WaterBodyRenderData;` _[#if defined(GENERATE_INSTANCE_DATA)]_
- L674 _resource_ `ByteAddressBuffer PackedNodes;` _[#if defined(GENERATE_INSTANCE_DATA)]_
- L675 _resource_ `Buffer<uint> InstanceDataOffsets;` _[#if defined(GENERATE_INSTANCE_DATA)]_
- L677 _resource_ `Buffer<uint> OcclusionResults;` _[#if defined(GENERATE_INSTANCE_DATA) && PRECISE_OCCLUSION_QUERIES]_
- L835 _resource_ `Texture2D<float4> QuadTreeTexture;` _[#if DEBUG_SHOW_TILES]_
- L836 _resource_ `Texture2D<float4> WaterZBoundsTexture;` _[#if DEBUG_SHOW_TILES]_
- L837 _resource_ `StructuredBuffer<FWaterBodyRenderData> WaterBodyRenderData;` _[#if DEBUG_SHOW_TILES]_
- L838 _resource_ `ByteAddressBuffer PackedNodes;` _[#if DEBUG_SHOW_TILES]_
- L840 _resource_ `Buffer<uint> OcclusionResults;` _[#if DEBUG_SHOW_TILES && PRECISE_OCCLUSION_QUERIES]_

#### Global parameters (uniforms) (46)

- L64 _parameter_ `uint NumDrawBuckets;` _[#if defined(INITIALIZE_INDIRECT_ARGS)]_
- L65 _parameter_ `uint NumViews;` _[#if defined(INITIALIZE_INDIRECT_ARGS)]_
- L66 _parameter_ `uint NumQuads;` _[#if defined(INITIALIZE_INDIRECT_ARGS)]_
- L111 _parameter_ `uint NumDrawBuckets;` _[#if defined(CLEAR_PER_VIEW_BUFFERS)]_
- L149 _parameter_ `float4 CullingBoundsAABB;` _[#if defined(QUAD_TREE_TRAVERSE)]_
- L150 _parameter_ `float3 QuadTreePosition;` _[#if defined(QUAD_TREE_TRAVERSE)]_
- L151 _parameter_ `float3 ObserverPosition;` _[#if defined(QUAD_TREE_TRAVERSE)]_
- L152 _parameter_ `uint QuadTreeResolutionX;` _[#if defined(QUAD_TREE_TRAVERSE)]_
- L153 _parameter_ `uint QuadTreeResolutionY;` _[#if defined(QUAD_TREE_TRAVERSE)]_
- L154 _parameter_ `uint ViewIndex;` _[#if defined(QUAD_TREE_TRAVERSE)]_
- L155 _parameter_ `float LeafSize;` _[#if defined(QUAD_TREE_TRAVERSE)]_
- L156 _parameter_ `float LODScale;` _[#if defined(QUAD_TREE_TRAVERSE)]_
- L157 _parameter_ `float CaptureDepthRange;` _[#if defined(QUAD_TREE_TRAVERSE)]_
- L158 _parameter_ `int ForceCollapseDensityLevel;` _[#if defined(QUAD_TREE_TRAVERSE)]_
- L159 _parameter_ `uint NumLODs;` _[#if defined(QUAD_TREE_TRAVERSE)]_
- L160 _parameter_ `uint NumDispatchedThreads;` _[#if defined(QUAD_TREE_TRAVERSE)]_
- L161 _parameter_ `uint bHZBOcclusionCullingEnabled;` _[#if defined(QUAD_TREE_TRAVERSE)]_
- L423 _parameter_ `uint NumDispatchedThreads;` _[#if defined(COMPUTE_BUCKET_COUNTS)]_
- L424 _parameter_ `uint NumDensities;` _[#if defined(COMPUTE_BUCKET_COUNTS)]_
- L425 _parameter_ `uint NumQuadsLOD0;` _[#if defined(COMPUTE_BUCKET_COUNTS)]_
- L426 _parameter_ `uint NumQuadsPerDraw;` _[#if defined(COMPUTE_BUCKET_COUNTS)]_
- L488 _parameter_ `uint NumBuckets;` _[#if defined(COMPUTE_BUCKET_PREFIX_SUM)]_
- L489 _parameter_ `uint OutputOffset;` _[#if defined(COMPUTE_BUCKET_PREFIX_SUM)]_
- L490 _parameter_ `uint bWriteTotalSumAtBufferEnd;` _[#if defined(COMPUTE_BUCKET_PREFIX_SUM)]_
- L680 _parameter_ `float3 QuadTreePosition;` _[#if defined(GENERATE_INSTANCE_DATA)]_
- L681 _parameter_ `float3 ObserverPosition;` _[#if defined(GENERATE_INSTANCE_DATA)]_
- L682 _parameter_ `uint QuadTreeResolutionX;` _[#if defined(GENERATE_INSTANCE_DATA)]_
- L683 _parameter_ `uint QuadTreeResolutionY;` _[#if defined(GENERATE_INSTANCE_DATA)]_
- L684 _parameter_ `uint NumDensities;` _[#if defined(GENERATE_INSTANCE_DATA)]_
- L685 _parameter_ `uint NumMaterials;` _[#if defined(GENERATE_INSTANCE_DATA)]_
- L686 _parameter_ `uint NumDispatchedThreads;` _[#if defined(GENERATE_INSTANCE_DATA)]_
- L687 _parameter_ `uint BucketIndexOffset;` _[#if defined(GENERATE_INSTANCE_DATA)]_
- L688 _parameter_ `uint NumLODs;` _[#if defined(GENERATE_INSTANCE_DATA)]_
- L689 _parameter_ `uint NumQuadsLOD0;` _[#if defined(GENERATE_INSTANCE_DATA)]_
- L690 _parameter_ `uint NumQuadsPerDraw;` _[#if defined(GENERATE_INSTANCE_DATA)]_
- L691 _parameter_ `float LeafSize;` _[#if defined(GENERATE_INSTANCE_DATA)]_
- L692 _parameter_ `float LODScale;` _[#if defined(GENERATE_INSTANCE_DATA)]_
- L693 _parameter_ `float CaptureDepthRange;` _[#if defined(GENERATE_INSTANCE_DATA)]_
- L694 _parameter_ `uint StereoPassInstanceFactor;` _[#if defined(GENERATE_INSTANCE_DATA)]_
- L695 _parameter_ `uint bWithWaterSelectionSupport;` _[#if defined(GENERATE_INSTANCE_DATA)]_
- L696 _parameter_ `uint bLODMorphingEnabled;` _[#if defined(GENERATE_INSTANCE_DATA)]_
- L697 _parameter_ `uint bInstancedStereoRendering;` _[#if defined(GENERATE_INSTANCE_DATA)]_
- L843 _parameter_ `float3 QuadTreePosition;` _[#if DEBUG_SHOW_TILES]_
- L844 _parameter_ `uint NumDispatchedThreads;` _[#if DEBUG_SHOW_TILES]_
- L845 _parameter_ `float LeafSize;` _[#if DEBUG_SHOW_TILES]_
- L846 _parameter_ `float CaptureDepthRange;` _[#if DEBUG_SHOW_TILES]_

#### groupshared (3)

- L498 _groupshared_ `groupshared uint SharedData[ARRAY_SIZE];` _[#if defined(COMPUTE_BUCKET_PREFIX_SUM) && PARALLEL_PREFIX_SUM]_
- L499 _groupshared_ `groupshared uint BlockPrefixSum;` _[#if defined(COMPUTE_BUCKET_PREFIX_SUM) && PARALLEL_PREFIX_SUM]_
- L500 _groupshared_ `groupshared uint TotalGlobalSum;` _[#if defined(COMPUTE_BUCKET_PREFIX_SUM) && PARALLEL_PREFIX_SUM]_

#### Functions (9)

- L7-15 _function_ `uint PackNodeCoord(uint4 InNode)`
- L17-25 _function_ `uint4 UnpackNodeCoord(uint InPacked)`
- L33-46 _function_ `FWaterLODParams GetWaterLODParams(float InObserverHeight, float InWaterHeightForLOD, float InLODScale, uint InTreeDepth)`
- L48-52 _function_ `float4 GetNodeAABB2D(uint3 InNodeCoord, float3 InQuadTreePosition, float InLeafSize)`
- L163-187 _function_ `float ComputeSquaredDistanceToPoint(float2 InBox2DMin, float2 InBox2DMax, float2 InPoint)` _[#if defined(QUAD_TREE_TRAVERSE)]_
- L189-192 _function_ `float GetLODDistance(int InLODLevel, float InLODScale)` _[#if defined(QUAD_TREE_TRAVERSE)]_
- L194-205 _function_ `bool CanRender(FWaterQuadTreeNode Node, int InDensityLevel, int InForceCollapseDensityLevel)` _[#if defined(QUAD_TREE_TRAVERSE)]_
- L502-512 _function_ `uint LoadFromBuffer(uint InIndex)` _[#if defined(COMPUTE_BUCKET_PREFIX_SUM) && PARALLEL_PREFIX_SUM]_
- L514-520 _function_ `void WriteToBuffer(uint InIndex, uint InWriteOffset, uint InGlobalPrefixSum)` _[#if defined(COMPUTE_BUCKET_PREFIX_SUM) && PARALLEL_PREFIX_SUM]_

### `Plugins/Experimental/Water/Shaders/Private/WaterQuadTreeMerge.usf` (Private)

- lines: 106; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `/Engine/Private/PackUnpack.ush`, L5 `WaterQuadTreeCommon.ush`

#### Macros (#define, 1)

- L8 `#define NUM_MSAA_SAMPLES 1` _[#if !defined(NUM_MSAA_SAMPLES)]_

#### Entry points (1)

- L29-106 _entry_ `void Main( in float4 Position : SV_Position, out float4 OutPackedNode : SV_Target0, out float4 OutWaterZBounds : SV_Target1)` — stage: **pixel (from C++ binding)** — C++: `FWaterQuadTreeMergePS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:125)

#### Global resources (textures / buffers / samplers) (7)

- L12 _resource_ `Texture2DMS<float4, NUM_MSAA_SAMPLES> WaterBodyRasterTextureMS;` _[#if NUM_MSAA_SAMPLES > 1]_
- L12 _resource_ `Texture2DMS<float4, NUM_MSAA_SAMPLES> WaterBodyRasterTextureMS;` _[#if NUM_MSAA_SAMPLES > 1]_
- L13 _resource_ `Texture2DMS<float4, NUM_MSAA_SAMPLES> ZBoundsRasterTextureMS;` _[#if NUM_MSAA_SAMPLES > 1]_
- L13 _resource_ `Texture2DMS<float4, NUM_MSAA_SAMPLES> ZBoundsRasterTextureMS;` _[#if NUM_MSAA_SAMPLES > 1]_
- L15 _resource_ `Texture2D<float4> WaterBodyRasterTexture;` _[#if !(NUM_MSAA_SAMPLES > 1)]_
- L16 _resource_ `Texture2D<float4> ZBoundsRasterTexture;` _[#if !(NUM_MSAA_SAMPLES > 1)]_
- L18 _resource_ `StructuredBuffer<FWaterBodyRenderData> WaterBodyRenderData;`

#### Global parameters (uniforms) (3)

- L19 _parameter_ `int SuperSamplingFactor;`
- L20 _parameter_ `float RcpCaptureDepthRange;`
- L21 _parameter_ `float ZBoundsPadding;` — We base our tile Z bounds on rasterization, however with sloped rivers we will likely miss part of the Z extent. Add some padding to account for that.

#### Functions (1)

- L23-27 _function_ `uint UnpackWaterBodyRenderDataIndex(float Packed)`

### `Plugins/Experimental/Water/Shaders/Private/WaterQuadTreePixelShader.usf` (Private)

- lines: 58; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`

#### Macros (#define, 1)

- L6 `#define CLIP_CONSERVATIVE_TRIANGLE 0` _[#if !defined(CLIP_CONSERVATIVE_TRIANGLE)]_

#### Entry points (1)

- L16-57 _entry_ `void Main( in float4 InPosition : SV_Position, in float4 InClipPosition : CLIP_POSITION, in float4 InTriangleAABB : TRIANGLE_AABB, out float4 OutWaterBody : SV_Target0, out float4 OutZBounds : SV_Target1)` — stage: **pixel (from C++ binding)** — C++: `FWaterQuadTreePS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:91)

#### Global parameters (uniforms) (6)

- L9 _parameter_ `uint WaterBodyRenderDataIndex;`
- L10 _parameter_ `uint Priority;`
- L11 _parameter_ `float WaterBodyMinZ;`
- L12 _parameter_ `float WaterBodyMaxZ;`
- L13 _parameter_ `float MaxWaveHeight;`
- L14 _parameter_ `uint bIsRiver;`

### `Plugins/Experimental/Water/Shaders/Private/WaterQuadTreeVertexShader.usf` (Private)

- lines: 102; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`

#### Macros (#define, 4)

- L5 `#define RASTER_MODE_REGULAR 0`
- L6 `#define RASTER_MODE_JITTER 1`
- L7 `#define RASTER_MODE_CONSERVATIVE 2`
- L10 `#define RASTER_MODE RASTER_MODE_REGULAR` _[#if !defined(RASTER_MODE)]_

#### Entry points (1)

- L36-101 _entry_ `void Main( in float3 InPosition : ATTRIBUTE0, in float2 InJitter : ATTRIBUTE1, in float2 InPrevNextVertex0 : ATTRIBUTE1, in float2 InPrevNextVertex1 : ATTRIBUTE2, in float2 InPrevNextVertex2 : ATTRIBUTE3, out float4 OutPosition : SV_Position ,out float4 OutClipPosition : CLIP_POSITION ,out float4 OutTriangleAABB : TRIANGLE_AABB )` — stage: **vertex (from C++ binding)** — C++: `FWaterQuadTreeVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/Water/Source/Runtime/Private/WaterQuadTreeGPU.cpp:65)

#### Global parameters (uniforms) (3)

- L13 _parameter_ `float4x4 Transform;`
- L16 _parameter_ `float2 JitterScale;` _[#if RASTER_MODE == RASTER_MODE_JITTER]_
- L18 _parameter_ `float2 HalfPixelSize;` _[#if !(RASTER_MODE == RASTER_MODE_JITTER) && RASTER_MODE == RASTER_MODE_CONSERVATIVE]_

#### Functions (1)

- L21-34 _function_ `float4 AddPoint(float4 InPos, float4 InAABB)`
