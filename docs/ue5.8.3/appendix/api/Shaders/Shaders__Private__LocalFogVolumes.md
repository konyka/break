# Shaders / Shaders/Private/LocalFogVolumes

- files: 3; lines: 749
- record kinds: cpp_binding=6, define=27, entry=2, function=8, include=13, member=15, parameter=17, resource=7, struct=3, unparsed=1

### `Shaders/Private/LocalFogVolumes/LocalFogVolumeCommon.ush` (Private)

- lines: 438; parse: all-branches
- includes: L2 `../Common.ush`, L4 `../SHCommon.ush`, L5 `../ParticipatingMediaCommon.ush`, L6 `../ReflectionEnvironmentShared.ush`, L7 `../FastMath.ush`

#### Macros (#define, 22)

- L38 `#define LFVInsts LFVStruct.LFV.LocalFogVolumeInstances` _[#if defined(LFVStruct)]_
- L39 `#define LFVTileDataTex LFVStruct.LFV.LocalFogVolumeTileDataTexture` _[#if defined(LFVStruct)]_
- L41 `#define LFVTileDataResolution LFVStruct.LFV.LocalFogVolumeTileDataTextureResolution` _[#if defined(LFVStruct)]_
- L42 `#define LFVInstcount LFVStruct.LFV.LocalFogVolumeInstanceCount` _[#if defined(LFVStruct)]_
- L43 `#define LFVTilePixelSize LFVStruct.LFV.LocalFogVolumeTilePixelSize` _[#if defined(LFVStruct)]_
- L44 `#define LFVMaxDensityIntoVolumetricFog LFVStruct.LFV.LocalFogVolumeMaxDensityIntoVolumetricFog` _[#if defined(LFVStruct)]_
- L45 `#define LFVRenderInVolumetricFog LFVStruct.LFV.ShouldRenderLocalFogVolumeInVolumetricFog` _[#if defined(LFVStruct)]_
- L46 `#define LFVGlobalStartDistance LFVStruct.LFV.GlobalStartDistance` _[#if defined(LFVStruct)]_
- L47 `#define LFVHalfResTextureSizeAndInvSize LFVStruct.LFV.HalfResTextureSizeAndInvSize` _[#if defined(LFVStruct)]_
- L49 `#define LFVDirectionalLightColor LFVStruct.LFV.DirectionalLightColor` _[#if defined(LFVStruct)]_
- L50 `#define LFVDirectionalLightDirection LFVStruct.LFV.DirectionalLightDirection` _[#if defined(LFVStruct)]_
- L68 `#define LFVInsts LFV_LocalFogVolumeInstances` _[#if !(defined(LFVStruct))]_
- L69 `#define LFVTileDataTex LFV_LocalFogVolumeTileDataTexture` _[#if !(defined(LFVStruct))]_
- L71 `#define LFVTileDataResolution LFV_LocalFogVolumeTileDataTextureResolution` _[#if !(defined(LFVStruct))]_
- L72 `#define LFVInstcount LFV_LocalFogVolumeInstanceCount` _[#if !(defined(LFVStruct))]_
- L73 `#define LFVTilePixelSize LFV_LocalFogVolumeTilePixelSize` _[#if !(defined(LFVStruct))]_
- L74 `#define LFVMaxDensityIntoVolumetricFog LFV_LocalFogVolumeMaxDensityIntoVolumetricFog` _[#if !(defined(LFVStruct))]_
- L75 `#define LFVRenderInVolumetricFog LFV_ShouldRenderLocalFogVolumeInVolumetricFog` _[#if !(defined(LFVStruct))]_
- L76 `#define LFVGlobalStartDistance LFV_GlobalStartDistance` _[#if !(defined(LFVStruct))]_
- L77 `#define LFVHalfResTextureSizeAndInvSize LFV_HalfResTextureSizeAndInvSize` _[#if !(defined(LFVStruct))]_
- L79 `#define LFVDirectionalLightColor LFV_DirectionalLightColor` _[#if !(defined(LFVStruct))]_
- L80 `#define LFVDirectionalLightDirection LFV_DirectionalLightDirection` _[#if !(defined(LFVStruct))]_

#### Structs / classes (2)

- L14-30 _struct_ **`FLocalFogVolumeGPUInstanceData`** `struct FLocalFogVolumeGPUInstanceData`
  - L16 _member_ `float3x3 PreTranslatedInvTransform;`
  - L17 _member_ `float3 TranslatedWorlPos;`
  - L18 _member_ `float UniformScale;`
  - L19 _member_ `float UniformScaleInv;` — Derived from UniformScale
  - L20 _member_ `float StartDistance;`
  - L22 _member_ `float RadialFogExtinction;`
  - L23 _member_ `float HeightFogExtinction;`
  - L24 _member_ `float HeightFogFalloff;`
  - L25 _member_ `float HeightFogOffset;`
  - L27 _member_ `float3 Emissive;`
  - L28 _member_ `float3 Albedo;`
  - L29 _member_ `float PhaseG;`
- L162-166 _struct_ **`FFogData`** `struct FFogData`
  - L164 _member_ `float IntegratedLuminanceFactor;`
  - L165 _member_ `float Coverage;`

#### Global resources (textures / buffers / samplers) (2)

- L65 _resource_ `Buffer<float4> LFV_LocalFogVolumeInstances;` _[#if !(defined(LFVStruct))]_
- L66 _resource_ `Texture2DArray<uint> LFV_LocalFogVolumeTileDataTexture;` _[#if !(defined(LFVStruct))]_

#### Global parameters (uniforms) (9)

- L54 _parameter_ `uint2 LFV_LocalFogVolumeTileDataTextureResolution;` _[#if !(defined(LFVStruct))]_
- L55 _parameter_ `uint LFV_LocalFogVolumeInstanceCount;` _[#if !(defined(LFVStruct))]_
- L56 _parameter_ `uint LFV_LocalFogVolumeTilePixelSize;` _[#if !(defined(LFVStruct))]_
- L57 _parameter_ `float LFV_LocalFogVolumeMaxDensityIntoVolumetricFog;` _[#if !(defined(LFVStruct))]_
- L58 _parameter_ `uint LFV_ShouldRenderLocalFogVolumeInVolumetricFog;` _[#if !(defined(LFVStruct))]_
- L59 _parameter_ `float LFV_GlobalStartDistance;` _[#if !(defined(LFVStruct))]_
- L60 _parameter_ `float4 LFV_HalfResTextureSizeAndInvSize;` _[#if !(defined(LFVStruct))]_
- L62 _parameter_ `float3 LFV_DirectionalLightColor;` _[#if !(defined(LFVStruct))]_
- L63 _parameter_ `float3 LFV_DirectionalLightDirection;` _[#if !(defined(LFVStruct))]_

#### Functions (8)

- L85-136 _function_ `FLocalFogVolumeGPUInstanceData GetLocalFogVolumeGPUInstanceData(uint Index)`
- L143-146 _function_ `uint2 LFVUnpackTile(uint In)`
- L148-155 _function_ `uint LFVPackTile(uint2 TileCoord)`
- L168-293 _function_ `FFogData LocalFogVolumeEvaluateAnalyticalIntegral(FLocalFogVolumeGPUInstanceData FogInstance, float3 RayStartU, float3 RayDirU, float RayLengthU)`
- L300-327 _function_ `float3 LocalFogVolumeEvaluateInScattering(in FLocalFogVolumeGPUInstanceData FogInstance, in FFogData FogData, in float3 RayDirWorld)`
- L335-389 _function_ `float4 GetLFVInstanceContribution( in uint InstanceIndex, in float3 CamRayTranslatedWorldOrigin, in float3 CamRayTranslatedWorldDir, in float3 DepthBufferTranslatedWorldPos, in bool bPlatformSupportsVolumetricFogOntranslucent)` — Returns color transmittance
- L395-425 _function_ `float4 GetLFVContribution( in ViewState ResolvedView, in uint2 TilePos, in float3 DepthBufferTranslatedWorldPos, in bool bPlatformSupportsVolumetricFogOntranslucent, inout uint OutLFVCount)` — Evaluate the local fog volume contribution for a world position. Returns a float4 with Luminance Color in RGB and Transmittance in A.
- L427-435 _function_ `float4 GetLFVContribution( in ViewState ResolvedView, in uint2 TilePos, in float3 TranslatedWorldPosition, in bool bPlatformSupportsVolumetricFogOntranslucent = true)`

### `Shaders/Private/LocalFogVolumes/LocalFogVolumeSplat.usf` (Private)

- lines: 153; parse: first-branch; parse notes: 1
- includes: L2 `../Common.ush`, L8 `../SceneTexturesCommon.ush`, L10 `LocalFogVolumeCommon.ush`, L68 `../ColorMap.ush` [LFV_TILED_PS && LFV_VISUALIZATION_PS]

#### Macros (#define, 5)

- L5 `#define MobileSceneTextures MobileBasePass.SceneTextures` _[#if SHADING_PATH_MOBILE]_
- L13 `#define LFV_TILED_VS 0` _[#if !defined(LFV_TILED_VS)]_
- L16 `#define LFV_TILED_PS 0` _[#if !defined(LFV_TILED_PS)]_
- L19 `#define LFV_HALFRES_PS 0` _[#if !defined(LFV_HALFRES_PS)]_
- L22 `#define LFV_VISUALIZATION_PS 0` _[#if !defined(LFV_VISUALIZATION_PS)]_

#### Entry points (1)

- L41-60 _entry_ `void LocalFogVolumeTiledVS( in uint VertexIndex : SV_VertexID, in uint InstanceIndex : SV_InstanceID, out float4 OutPosition : SV_POSITION, out FLocalFogVolumeVertexOutput OtherVertexOutput )` — stage: **vertex (from C++ binding)** — C++: `FLocalFogVolumeTiledRenderVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/LocalFogVolumeRendering.cpp:752) — C++: `FMobileLocalFogVolumeTiledRenderVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/LocalFogVolumeRendering.cpp:1086) _[#if LFV_TILED_VS]_

#### Structs / classes (1)

- L27-32 _struct_ **`FLocalFogVolumeVertexOutput`** `struct FLocalFogVolumeVertexOutput`
  - L30 _member_ `nointerpolation uint TileData : TEXCOORD0;` — #if LFV_TILED_VS \|\| LFV_TILED_PS

#### Global resources (textures / buffers / samplers) (1)

- L38 _resource_ `Buffer<uint> TileDataBuffer;` _[#if LFV_TILED_VS]_

#### Global parameters (uniforms) (2)

- L39 _parameter_ `float StartDepthZ;` _[#if LFV_TILED_VS]_
- L65 _parameter_ `int LocalFogVolumeTileDebug;` _[#if LFV_TILED_PS]_

#### Unparsed (raw text) (1)

- L71-150 _unparsed_ `void LocalFogVolumeTiledPS( in float4 SVPos : SV_POSITION, out float4 OutColorThroughput : SV_Target0, out float OutDepth : SV_Target1) in FLocalFogVolumeVertexOutput OtherVertexOutput, out float4 OutColor : SV_Target0)` _[#if LFV_TILED_PS]_

#### C++ shader bindings (IMPLEMENT_* naming this file, 3)

- `LocalFogVolumeTiledPS` → entry not found in file (macro-generated or #include'd); C++ `FLocalFogVolumeTiledRenderPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/LocalFogVolumeRendering.cpp:784)
- `LocalFogVolumeTiledPS` → entry not found in file (macro-generated or #include'd); C++ `FMobileLocalFogVolumeTiledRenderPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/LocalFogVolumeRendering.cpp:1120)
- `LocalFogVolumeTiledPS` → entry not found in file (macro-generated or #include'd); C++ `FMobileLocalFogVolumeTiledRenderHalfResPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/LocalFogVolumeRendering.cpp:1157)

<details><summary>parse notes</summary>

- L71: unrecognised block header 'void LocalFogVolumeTiledPS( in float4 SVPos : SV_POSITION, out float4 OutColorTh'

</details>

### `Shaders/Private/LocalFogVolumes/LocalFogVolumeTiledCulling.usf` (Private)

- lines: 158; parse: all-branches
- includes: L2 `../Common.ush`, L4 `LocalFogVolumeCommon.ush`, L5 `../Nanite/NaniteHZBCull.ush`, L6 `../HZB.ush`

#### Entry points (1)

- L26-155 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void LocalFogVolumeTiledCullingCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FLocalFogVolumeTiledCullingCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/LocalFogVolumeRendering.cpp:335)

#### Global resources (textures / buffers / samplers) (4)

- L15 _resource_ `Buffer<float4> LocalFogVolumeCullingDataBuffer;`
- L17 _resource_ `RWTexture2DArray<uint> LocalFogVolumeTileDataTextureUAV;`
- L19 _resource_ `RWBuffer<uint> TileDataBufferUAV;`
- L20 _resource_ `RWBuffer<uint> TileDrawIndirectBufferUAV;`

#### Global parameters (uniforms) (6)

- L8 _parameter_ `float4 LeftPlane;`
- L9 _parameter_ `float4 RightPlane;`
- L10 _parameter_ `float4 TopPlane;`
- L11 _parameter_ `float4 BottomPlane;`
- L12 _parameter_ `float4 NearPlane;`
- L13 _parameter_ `float2 ViewToTileSpaceRatio;`
