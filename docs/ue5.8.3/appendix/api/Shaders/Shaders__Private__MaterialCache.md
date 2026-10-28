# Shaders / Shaders/Private/MaterialCache

- files: 9; lines: 770
- record kinds: cpp_binding=7, define=13, entry=6, function=18, include=48, member=8, parameter=6, resource=12, struct=5, typedef=1

### `Shaders/Private/MaterialCache/MaterialCacheABufferBorderFillHardwarePages.usf` (Private)

- lines: 75; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `/Engine/Shared/MaterialCacheDefinitions.h`

#### Entry points (1)

- L52-74 _entry_ `[numthreads(8, 8, 1)] void BorderFillHardwarePagesMain(uint3 DTid : SV_DispatchThreadID)` — stage: **compute** — C++: `FMaterialCacheABufferFillBorderHardwarePagesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/MaterialCache/MaterialCacheShaders.cpp:18)

#### Global resources (textures / buffers / samplers) (4)

- L6 _resource_ `StructuredBuffer<FMaterialCachePageWriteData> PageWriteData;`
- L8 _resource_ `RWTexture2DArray<float4> RWABuffer;`
- L10 _resource_ `Texture2DArray<uint> R8Mask;`
- L12 _resource_ `SamplerState TextureSampler;`

#### Global parameters (uniforms) (2)

- L14 _parameter_ `uint BorderWidth;`
- L15 _parameter_ `uint ThreadCount;`

#### Functions (1)

- L17-50 _function_ `bool FindNearestInfillMaskPixel(uint3 ABufferPhysicalLocation, out uint3 ABufferPhysicalLocationInFill)`

### `Shaders/Private/MaterialCache/MaterialCacheABufferPages.usf` (Private)

- lines: 113; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `/Engine/Shared/MaterialCacheDefinitions.h`, L5 `/Engine/Private/GammaCorrectionCommon.ush`, L6 `/Engine/Private/BlockCompressionCommon.ush`, L7 `/Engine/Private/BCCompressionCommon.ush`

#### Entry points (1)

- L27-112 _entry_ `[numthreads(8, 8, 1)] void WritePagesMain(uint3 DTid : SV_DispatchThreadID)` — stage: **compute** — C++: `FMaterialCacheABufferWritePagesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/MaterialCache/MaterialCacheShaders.cpp:19)

#### Global resources (textures / buffers / samplers) (6)

- L9 _resource_ `StructuredBuffer<FMaterialCachePageWriteData> PageWriteData;`
- L12 _resource_ `RWTexture2D<float4> RWVTLayerUncompressed;` _[#if COMPRESS_MODE == BC_NONE]_
- L14 _resource_ `RWTexture2D<uint2> RWVTLayerCompressed64;` _[#if !(COMPRESS_MODE == BC_NONE) && COMPRESS_MODE == BC1 \|\| COMPRESS_MODE == BC4]_
- L16 _resource_ `RWTexture2D<uint4> RWVTLayerCompressed128;` _[#if !(COMPRESS_MODE == BC_NONE) && !(COMPRESS_MODE == BC1 \|\| COMPRESS_MODE == BC4)]_
- L18 _resource_ `SamplerState TextureSampler;`
- L20 _resource_ `Texture2DArray<float4> ABuffer;`

#### Global parameters (uniforms) (4)

- L22 _parameter_ `uint BlockOrThreadCount;`
- L23 _parameter_ `float2 TexelSize;`
- L24 _parameter_ `uint bYCoCg;`
- L25 _parameter_ `uint bSRGB;`

### `Shaders/Private/MaterialCache/MaterialCacheCommon.ush` (Private)

- lines: 92; parse: all-branches
- includes: L4 `/Engine/Shared/MaterialCacheDefinitions.h`, L5 `/Engine/Private/MortonCode.ush`, L6 `/Engine/Private/SceneData.ush`
- L2 #pragma `once`

#### Structs / classes (1)

- L8-12 _struct_ **`FMaterialCacheDescriptor`** `struct FMaterialCacheDescriptor`
  - L10 _member_ `uint TagOffset;`
  - L11 _member_ `uint UVChannel;`

#### Functions (5)

- L14-17 _function_ `float2 GetMaterialCacheUV(FMaterialCacheDescriptor Descriptor, float2 SourceUV)`
- L19-38 _function_ `float4 GetMaterialCacheUnwrapClipPosition(FMaterialCacheDescriptor Descriptor, float2 TexCoord, float4 UnwrapMinAndInvSize, float4 PageOffsetAndInvSize = float4(0, 0, 1, 1))`
- L40-55 _function_ `FMaterialCacheBinData GetMaterialCacheShadingData(uint Index)`
- L57-86 _function_ `uint2 GetMaterialCacheCSShadePixel(uint3 DTid, uint4 TileParams, uint4 TileOrderingParams)`
- L88-91 _function_ `uint GetMaterialCacheUVCoordinateIndex(in FPrimitiveSceneData Data)`

### `Shaders/Private/MaterialCache/MaterialCacheMaterialCommon.ush` (Private)

- lines: 59; parse: all-branches
- includes: L4 `/Engine/Private/SceneData.ush`, L5 `/Engine/Private/MaterialCache/MaterialCacheCommon.ush`, L8 `/Engine/Private/VirtualTextureCommon.ush` [MATERIAL_CACHE \|\| MATERIAL_SAMPLES_CACHE \|\| NUM_VIRTUALTEXTURE_SAMPLES > 0]
- L2 #pragma `once`

#### Functions (5)

- L11-18 _function_ `bool GetMaterialCacheState()`
- L21-38 _function_ `VTPageTableUniform MaterialCacheUnpackPageTableUniform(uint2 PackedPageTableUniform)` _[#if NUM_VIRTUALTEXTURE_SAMPLES > 0]_
- L41-48 _function_ `FMaterialCacheDescriptor GetMaterialCacheTextureDescriptor(FPrimitiveSceneData PrimitiveData)`
- L50-53 _function_ `uint GetMaterialCacheTagOffset(FPrimitiveSceneData PrimitiveData)`
- L55-58 _function_ `bool GetMaterialCacheTextureDescriptorIsValid(FPrimitiveSceneData PrimitiveData)`

### `Shaders/Private/MaterialCache/MaterialCacheShade.usf` (Private)

- lines: 89; parse: all-branches
- includes: L3 `/Engine/Shared/MaterialCacheDefinitions.h`, L4 `/Engine/Private/Common.ush`, L9 `/Engine/Generated/Material.ush`, L10 `/Engine/Generated/VertexFactory.ush`, L11 `/Engine/Private/MortonCode.ush`, L12 `/Engine/Public/RootConstants.ush`, L13 `/Engine/Private/MaterialCache/MaterialCacheShadeCommon.ush`, L14 `/Engine/Private/MaterialCache/MaterialCacheCommon.ush`

#### Macros (#define, 4)

- L6 `#define SceneTexturesStruct MaterialCachePass.SceneTextures`
- L7 `#define EyeAdaptationStruct MaterialCachePass`
- L17 `#define NUM_TEX_COORD_INTERPOLATORS 1` _[#if !defined(NUM_TEX_COORD_INTERPOLATORS)]_
- L21 `#define USE_ANALYTIC_DERIVATIVES 1` _[#if !defined(USE_ANALYTIC_DERIVATIVES)]_

#### Entry points (1)

- L70-88 _entry_ `[numthreads(64, 1, 1)] void Main(uint3 DTid : SV_DispatchThreadID)` — stage: **compute** — C++: `FMaterialCacheShadeCS` SF_Compute via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/MaterialCache/MaterialCacheShaders.cpp:16)

#### Global resources (textures / buffers / samplers) (1)

- L24-26 _resource_ `COMPILER_ALLOW_CS_DERIVATIVES Buffer<uint> PageIndirections;`

#### Functions (2)

- L28-48 _function_ `FMaterialPixelParameters GetMaterialPixelParameters(in FMaterialCacheBinData BinData, uint2 ThreadIndex)`
- L50-68 _function_ `FMaterialCacheABufferTag ShadeAttributes(in FMaterialCacheBinData BinData, uint2 ThreadIndex)`

### `Shaders/Private/MaterialCache/MaterialCacheShadeCommon.ush` (Private)

- lines: 69; parse: all-branches
- includes: L3 `/Engine/Private/MaterialCache/MaterialCacheCommon.ush`, L4 `/Engine/Shared/MaterialCacheDefinitions.h`

#### Macros (#define, 5)

- L7 `#define MATERIAL_CACHE_TAG_INDEX 0` _[#if !defined(MATERIAL_CACHE_TAG_INDEX)]_
- L10 `#define TOKEN_CONCAT(A, B, C) A ## B ## C`
- L11 `#define TOKEN_EXPAND(A, B, C) TOKEN_CONCAT(A, B, C)`
- L12 `#define TAG_NAME(NAME) TOKEN_EXPAND(NAME, MATERIAL_CACHE_TAG_INDEX, )`
- L13 `#define TAG_NAME_ANALYTIC(NAME) TOKEN_EXPAND(NAME, MATERIAL_CACHE_TAG_INDEX, _Analytic)`

#### typedef / using (1)

- L16 _typedef_ `typedef TAG_NAME(FMaterialCacheABuffer_) FMaterialCacheABufferTag;` — Current tag in use

#### Functions (3)

- L18-47 _function_ `FMaterialCacheABufferTag GetMaterialABuffer(in FMaterialPixelParameters MaterialParameters, in FPixelMaterialInputs PixelMaterialInputs)`
- L49-59 _function_ `FMaterialCacheABufferTag GetMaterialBottomABuffer(EMaterialCacheFlag Flags, uint3 ABufferPhysicalPosition, uint2 PagePixelPos)`
- L61-68 _function_ `void StoreMaterialABufferPixel(FMaterialCacheABufferTag Top, EMaterialCacheFlag Flags, uint3 ABufferPhysicalPosition, uint2 PagePixelPos)`

### `Shaders/Private/MaterialCache/MaterialCacheUnwrapNaniteShade.usf` (Private)

- lines: 137; parse: all-branches
- includes: L3 `/Engine/Shared/MaterialCacheDefinitions.h`, L4 `/Engine/Private/Common.ush`, L5 `/Engine/Private/Nanite/NaniteShadeCommon.ush`, L6 `/Engine/Private/MortonCode.ush`, L7 `/Engine/Public/RootConstants.ush`, L12 `/Engine/Generated/Material.ush`, L13 `/Engine/Generated/VertexFactory.ush`, L14 `/Engine/Generated/UniformBuffers/MaterialCachePass.ush`, L15 `/Engine/Private/MaterialCache/MaterialCacheShadeCommon.ush`, L16 `/Engine/Private/MaterialCache/MaterialCacheCommon.ush`

#### Macros (#define, 2)

- L9 `#define SceneTexturesStruct MaterialCachePass.SceneTextures`
- L10 `#define EyeAdaptationStruct MaterialCachePass`

#### Entry points (1)

- L90-136 _entry_ `[numthreads(64, 1, 1)] void Main(uint3 DTid : SV_DispatchThreadID)` — stage: **compute** — C++: `FMaterialCacheNaniteShadeCS` SF_Compute via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/MaterialCache/MaterialCacheShaders.cpp:15)

#### Global resources (textures / buffers / samplers) (1)

- L18-20 _resource_ `COMPILER_ALLOW_CS_DERIVATIVES Buffer<uint> PageIndirections;`

#### Functions (2)

- L22-51 _function_ `FMaterialCacheABufferTag ShadeAttributes(in FPackedNaniteView PackedView, uint2 VisBufferPixelPos, uint ViewIndex)`
- L53-88 _function_ `bool FindNearestInfillVisPixel(inout uint2 VisBufferPixelPos, out uint DepthInt, out uint VisibleClusterIndex, out uint VisTriIndex)`

### `Shaders/Private/MaterialCache/MaterialCacheUnwrapPixelShader.usf` (Private)

- lines: 65; parse: all-branches
- includes: L3 `/Engine/Shared/MaterialCacheDefinitions.h`, L4 `/Engine/Private/Common.ush`, L5 `/Engine/Public/RootConstants.ush`, L9 `/Engine/Generated/Material.ush`, L10 `/Engine/Generated/VertexFactory.ush`, L11 `/Engine/Generated/UniformBuffers/MaterialCachePass.ush`, L12 `/Engine/Private/MaterialCache/MaterialCacheShadeCommon.ush`, L13 `/Engine/Private/MaterialCache/MaterialCacheCommon.ush`

#### Macros (#define, 1)

- L7 `#define SceneTexturesStruct MaterialCachePass.SceneTextures`

#### Entry points (1)

- L25-64 _entry_ `void Main( FVertexFactoryInterpolantsVSToPS Interpolants, FMaterialCacheInterpolantsVSToPS PassInterpolants, in INPUT_POSITION_QUALIFIERS float4 SvPosition : SV_Position, in FMaterialCacheVSToPS Input OPTIONAL_IsFrontFace )` — stage: **pixel (from C++ binding)** — C++: `FMaterialCacheUnwrapPS` SF_Pixel via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/MaterialCache/MaterialCacheShaders.cpp:14)

#### Structs / classes (2)

- L15-18 _struct_ **`FMaterialCacheInterpolantsVSToPS`** `struct FMaterialCacheInterpolantsVSToPS`
- L20-23 _struct_ **`FMaterialCacheVSToPS`** `struct FMaterialCacheVSToPS`
  - L22 _member_ `float4 DualWorldPosition : DUAL_POSITION;`

### `Shaders/Private/MaterialCache/MaterialCacheUnwrapVertexShader.usf` (Private)

- lines: 71; parse: all-branches
- includes: L3 `/Engine/Shared/MaterialCacheDefinitions.h`, L4 `/Engine/Private/Common.ush`, L5 `/Engine/Public/RootConstants.ush`, L9 `/Engine/Generated/Material.ush`, L10 `/Engine/Generated/VertexFactory.ush`, L11 `/Engine/Generated/UniformBuffers/MaterialCachePass.ush`, L12 `/Engine/Private/MaterialCache/MaterialCacheCommon.ush`

#### Macros (#define, 1)

- L7 `#define SceneTexturesStruct MaterialCachePass.SceneTextures`

#### Entry points (1)

- L33-70 _entry_ `void Main(FVertexFactoryInput Input, out FMaterialCacheVSToPS Output)` — stage: **vertex (from C++ binding)** — C++: `FMaterialCacheUnwrapVS0` SF_Vertex via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/MaterialCache/MaterialCacheShaders.cpp:11) — C++: `FMaterialCacheUnwrapVS1` SF_Vertex via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/MaterialCache/MaterialCacheShaders.cpp:12)

#### Structs / classes (2)

- L14-17 _struct_ **`FMaterialCacheInterpolantsVSToPS`** `struct FMaterialCacheInterpolantsVSToPS`
- L19-31 _struct_ **`FMaterialCacheVSToPS`** `struct FMaterialCacheVSToPS`
  - L21 _member_ `FVertexFactoryInterpolantsVSToPS FactoryInterpolants;`
  - L22 _member_ `FMaterialCacheInterpolantsVSToPS PassInterpolants;`
  - L25 _member_ `uint PageIndex : SV_RenderTargetArrayIndex;` _[#if SUPPORTS_VIEWPORT_FROM_VS]_
  - L28 _member_ `float4 Position : SV_POSITION;`
  - L30 _member_ `float4 DualWorldPosition : DUAL_POSITION;`
