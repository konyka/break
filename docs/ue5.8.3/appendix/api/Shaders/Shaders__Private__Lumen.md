# Shaders / Shaders/Private/Lumen

- files: 87; lines: 30904
- record kinds: class=2, cpp_binding=177, define=443, entry=169, function=556, groupshared=103, include=546, macro_call=10, member=432, method=30, parameter=600, resource=654, static_const=5, struct=85, typedef=6

### `Shaders/Private/Lumen/LumenBufferEncoding.ush` (Private)

- lines: 63; parse: all-branches
- includes: L5 `../Common.ush`, L6 `../SHCommon.ush`

#### Macros (#define, 1)

- L9 `#define LUMEN_DIFFUSE_DIRECTIONAL_ENCODING 1`
- L3 #pragma `once`

#### Functions (2)

- L13-37 _function_ `void EncodeLumenDiffuseLighting(FTwoBandSHVectorRGB SH, out float4 Vector0, out float4 Vector1)` _[#if LUMEN_DIFFUSE_DIRECTIONAL_ENCODING == 1]_
- L39-58 _function_ `void DecodeLumenDiffuseLighting(float4 Vector0, float4 Vector1, out FTwoBandSHVectorRGB SH)` _[#if LUMEN_DIFFUSE_DIRECTIONAL_ENCODING == 1]_

### `Shaders/Private/Lumen/LumenCardBasePass.ush` (Private)

- lines: 149; parse: all-branches

#### Macros (#define, 1)

- L60 `#define CurrentBSDF SubstratePixelHeader.SubstrateTree.BSDFs[BSDFIdx]` _[#if TEMPLATE_USES_SUBSTRATE && !(SUBSTRATE_OPTIMIZED_UNLIT)]_
- L3 #pragma `once`; L82 #undef `CurrentBSDF`

#### Structs / classes (1)

- L5-10 _struct_ **`FLumenCardBasePassOutput`** `struct FLumenCardBasePassOutput`
  - L7 _member_ `float4 Target0;`
  - L8 _member_ `float4 Target1;`
  - L9 _member_ `float4 Target2;`

#### Functions (1)

- L12-149 _function_ `FLumenCardBasePassOutput LumenCardBasePass(FPixelMaterialInputs PixelMaterialInputs, FMaterialPixelParameters MaterialParameters, float4 SvPosition)`

### `Shaders/Private/Lumen/LumenCardCommon.ush` (Private)

- lines: 422; parse: all-branches
- includes: L5 `../OctahedralCommon.ush`

#### Macros (#define, 13)

- L7 `#define CARD_TILE_SIZE 8`
- L71 `#define LumenCardDataBuffer LumenCardScene.CardData` _[#if !(USE_LUMEN_CARD_DATA_BUFFER)]_
- L75 `#define LUMEN_CARD_DATA_STRIDE 7`
- L76 `#define LUMEN_CARD_PAGE_DATA_STRIDE 5`
- L79 `#define LUMEN_HEIGHTFIELD_LOCAL_CARD_INDEX 0`
- L164 `#define LumenCardPageDataBuffer RWLumenCardPageDataBuffer` _[#if USE_RW_LUMEN_CARD_PAGE_DATA_BUFFER]_
- L166 `#define LumenCardPageDataBuffer LumenCardScene.CardPageData` _[#if !(USE_RW_LUMEN_CARD_PAGE_DATA_BUFFER)]_
- L227 `#define LUMEN_MESH_CARDS_DATA_STRIDE 6`
- L228 `#define LUMEN_INVALID_CARD_INDEX 0xFFFFFFFF`
- L229 `#define LUMEN_INVALID_HEIGHTFIELD_OBJECT_INDEX 0xFFFFFFFF`
- L230 `#define LUMEN_INVALID_MESH_CARDS_INDEX 0xFFFFFFFF`
- L231 `#define LUMEN_INVALID_SCENE_INSTANCE_INDEX 0xFFFFFFFF`
- L285 `#define LUMEN_HEIGHTFIELD_DATA_STRIDE 3`
- L3 #pragma `once`

#### Structs / classes (6)

- L9-38 _struct_ **`FLumenCardData`** `struct FLumenCardData`
  - L12 _member_ `uint PackedMeshCardsAxes;` — OBB in MeshCards space
  - L13 _member_ `float3 MeshCardsOrigin;`
  - L14 _member_ `float3 MeshCardsExtent;`
  - L17 _member_ `float3x3 WorldToLocalRotation;` — OBB in world space
  - L18 _member_ `float3 Origin;`
  - L19 _member_ `float3 LocalExtent;`
  - L21 _member_ `uint2 SizeInPages;`
  - L22 _member_ `uint PageTableOffset;`
  - L24 _member_ `uint2 HiResSizeInPages;`
  - L25 _member_ `uint HiResPageTableOffset;`
  - L28 _member_ `uint2 ResLevelToResLevelXYBias;` — Convert Card's uint ResLevel (card's resolution) to uint2 ResLevelXY (each side's resolution)
  - L30 _member_ `bool bVisible;`
  - L31 _member_ `bool bHeightfield;`
  - L32 _member_ `bool bFarField;`
  - L33 _member_ `uint AxisAlignedDirection;`
  - L34 _member_ `uint LightingChannelMask;`
  - L37 _member_ `float TexelSize;` — Average world space texel size of always resident pages
- L137-160 _struct_ **`FLumenCardPageData`** `struct FLumenCardPageData`
  - L139 _member_ `uint CardIndex;`
  - L140 _member_ `bool bMapped;`
  - L142 _member_ `uint ResLevelPageTableOffset;`
  - L143 _member_ `uint2 ResLevelSizeInTiles;`
  - L145 _member_ `float2 SizeInTexels;`
  - L146 _member_ `uint2 PhysicalAtlasCoord;`
  - L148 _member_ `float4 CardUVRect;`
  - L149 _member_ `float4 PhysicalAtlasUVRect;`
  - L150 _member_ `float2 CardUVTexelScale;`
  - L151 _member_ `float2 PhysicalAtlasUVTexelScale;`
  - L153 _member_ `uint LastDirectLightingUpdateFrameIndex;`
  - L154 _member_ `uint LastIndirectLightingUpdateFrameIndex;`
  - L157 _member_ `uint IndirectLightingTemporalIndex;` — Increments each time the page has Radiosity updated, needs to be consecutive for the sample pattern
  - L159 _member_ `uint DirectLightingTemporalIndex;` — Increments each time the page has direct lighting updated. Only used to rotate through the texels in a quad when using adaptive shadow rays currently
- L217-224 _struct_ **`FCardVSToPS`** `struct FCardVSToPS`
  - L219 _member_ `float2 AtlasUV : ATTRIBUTE0;`
  - L220 _member_ `float2 IndirectLightingAtlasUV : ATTRIBUTE1;`
  - L221 _member_ `float2 CardUV : ATTRIBUTE2;`
  - L222 _member_ `nointerpolation uint CardTileIndex : CARD_TILE_INDEX;`
  - L223 _member_ `nointerpolation uint CardPageIndex : CARD_PAGE_INDEX;`
- L233-245 _struct_ **`FLumenMeshCardsData`** `struct FLumenMeshCardsData`
  - L235 _member_ `float3 WorldOrigin;`
  - L236 _member_ `float3x3 WorldToLocalRotation;`
  - L238 _member_ `uint NumCards;`
  - L239 _member_ `uint CardOffset;`
  - L241 _member_ `bool bHeightfield;`
  - L242 _member_ `bool bMostlyTwoSided;`
  - L244 _member_ `uint CardLookup[6];`
- L287-293 _struct_ **`FLumenHeightfieldData`** `struct FLumenHeightfieldData`
  - L289 _member_ `FDFVector3 BoundsCenter;` — World space AABB center
  - L290 _member_ `float3 BoundsExtent;` — World space AABB extent
  - L291 _member_ `uint MeshCardsIndex;`
  - L292 _member_ `bool bValid;`
- L384-391 _struct_ **`FLumenSceneDebugData`** `struct FLumenSceneDebugData`
  - L386 _member_ `bool bValid;`
  - L387 _member_ `uint MeshIndex;`
  - L388 _member_ `uint CardIndex;`
  - L389 _member_ `uint CardPageIndex;`
  - L390 _member_ `float2 PhysicalAtlasUV;`

#### Global resources (textures / buffers / samplers) (2)

- L69 _resource_ `StructuredBuffer<float4> LumenCardDataBuffer;` _[#if USE_LUMEN_CARD_DATA_BUFFER]_
- L162 _resource_ `RWStructuredBuffer<float4> RWLumenCardPageDataBuffer;`

#### Functions (21)

- L40-60 _function_ `float3 ShuffleAxesNoFlip(float3 In, uint PackedAxes)`
- L62-66 _function_ `float3 ShuffleAxes(float3 In, uint PackedAxes)`
- L83-130 _function_ `FLumenCardData GetLumenCardData(uint CardId)` — Fetch from scene card buffer Note: layout must match FLumenCardData in C++
- L132-135 _function_ `float3 RotateMeshCardsToCard(float3 MeshCardsVector, FLumenCardData CardData)`
- L170-200 _function_ `FLumenCardPageData GetLumenCardPageData(uint CardPageId)` — Note: layout must match FLumenCardPageData in C++
- L203-215 _function_ `void SetCardPageUpdateData(uint CardPageId, FLumenCardPageData CardPageData)` — Store only card page update data
- L248-282 _function_ `FLumenMeshCardsData GetLumenMeshCardsData(uint MeshCardsId)` — Note: layout must match FLumenMeshCardsData in C++
- L296-313 _function_ `FLumenHeightfieldData GetLumenHeightfieldData(uint HeightfieldId)` — Note: layout must match FLumenHeightfieldData in C++
- L315-324 _function_ `float3 GetCardLocalPosition(float3 CardLocalExtent, float2 CardUV, float Depth)`
- L326-335 _function_ `void GetCardLocalBBox(FLumenCardPageData CardPage, FLumenCardData Card, float2 UVMin, float2 UVMax, float2 CardTileDepthRange, out float3 CardPageLocalCenter, out float3 CardPageLocalExtent)`
- L337-340 _function_ `void GetCardLocalBBox(FLumenCardPageData CardPage, FLumenCardData Card, float2 UVMin, float2 UVMax, out float3 CardPageLocalCenter, out float3 CardPageLocalExtent)`
- L342-345 _function_ `void GetCardPageLocalBBox(FLumenCardPageData CardPage, FLumenCardData Card, out float3 CardPageLocalCenter, out float3 CardPageLocalExtent)`
- L347-352 _function_ `float3 GetCardWorldPosition(FLumenCardData Card, float2 CardUV, float Depth)`
- L354-358 _function_ `uint2 GetCardPageSizeInTexels(FLumenCardPageData CardPage, uint2 AtlasSize)`
- L360-364 _function_ `float2 CardPageUVToCardUV(FLumenCardPageData CardPage, float2 CardPageUV)`
- L366-370 _function_ `float2 CardPageUVToAtlasUV(FLumenCardPageData CardPage, float2 CardPageUV)`
- L372-376 _function_ `float2 SamplePositonToCardUV(FLumenCardData Card, float2 LocalSamplePosition)`
- L378-382 _function_ `uint GetMeshCardsIndexFromSceneInstanceIndex(uint SceneInstanceIndex)`
- L393-401 _function_ `FLumenSceneDebugData InitLumenSceneDebugData()`
- L403-410 _function_ `void WriteDebugData(FLumenSceneDebugData In, RWStructuredBuffer<uint> OutBuffer)`
- L412-422 _function_ `FLumenSceneDebugData ReadDebugData(StructuredBuffer<uint> InBuffer)`

### `Shaders/Private/Lumen/LumenCardComputeShader.usf` (Private)

- lines: 136; parse: all-branches
- includes: L5 `../Common.ush`, L17 `../BRDF.ush`, L18 `/Engine/Generated/Material.ush`, L19 `/Engine/Generated/VertexFactory.ush`, L20 `../BasePassCommonFunctions.ush`, L22 `../VariableRateShading/VRSShadingRateCommon.ush`, L23 `../Nanite/NaniteShadeCommon.ush`, L24 `../MortonCode.ush`, L28 `/Engine/Public/RootConstants.ush`, L29 `LumenCardBasePass.ush`

#### Macros (#define, 7)

- L3 `#define LUMEN_CARD_CAPTURE 1`
- L7 `#define SceneTexturesStruct LumenCardPass.SceneTextures`
- L8 `#define EyeAdaptationStruct LumenCardPass`
- L9 `#define ForwardLightStruct LumenCardPass.Forward`
- L10 `#define PreIntegratedGF LumenCardPass.PreIntegratedGFTexture`
- L12 `#define PreIntegratedGFSampler View.SharedBilinearClampedSampler` _[#if SUPPORTS_INDEPENDENT_SAMPLERS]_
- L14 `#define PreIntegratedGFSampler LumenCardPass.PreIntegratedGFSampler` _[#if !(SUPPORTS_INDEPENDENT_SAMPLERS)]_

#### Entry points (1)

- L98-135 _entry_ `[numthreads(64, 1, 1)] void Main(uint ThreadIndex : SV_GroupIndex, uint GroupID : SV_GroupID)` — stage: **compute** — C++: `FLumenCardCS` SF_Compute via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/Lumen/LumenSceneCardCapture.cpp:199)

#### Structs / classes (1)

- L93-96 _struct_ **`FLumenShadingBinMeta`** `struct FLumenShadingBinMeta`
  - L95 _member_ `uint DataByteOffset;`

#### Functions (5)

- L26-31 _function_ `COMPILER_ALLOW_CS_DERIVATIVES uint GetShadingBin()`
- L32 _function_ `uint GetQuadBinning()`
- L33 _function_ `uint GetMeshPassIndex()`
- L35-40 _function_ `void ExportPixel(const uint2 PixelPos, FLumenCardBasePassOutput ShadedPixel)`
- L46-91 _function_ `void ProcessPixel(const FPackedNaniteView PackedView, uint ShadingBin, const uint2 PixelPos, const float2 SVPositionXY, const uint ViewIndex)`

### `Shaders/Private/Lumen/LumenCardPixelShader.usf` (Private)

- lines: 61; parse: all-branches
- includes: L5 `../Common.ush`, L17 `../BRDF.ush`, L18 `/Engine/Generated/Material.ush`, L19 `/Engine/Generated/VertexFactory.ush`, L20 `../BasePassCommonFunctions.ush`, L21 `LumenCardBasePass.ush`

#### Macros (#define, 7)

- L3 `#define LUMEN_CARD_CAPTURE 1`
- L7 `#define SceneTexturesStruct LumenCardPass.SceneTextures`
- L8 `#define EyeAdaptationStruct LumenCardPass`
- L9 `#define ForwardLightStruct LumenCardPass.Forward`
- L10 `#define PreIntegratedGF LumenCardPass.PreIntegratedGFTexture`
- L12 `#define PreIntegratedGFSampler View.SharedBilinearClampedSampler` _[#if SUPPORTS_INDEPENDENT_SAMPLERS]_
- L14 `#define PreIntegratedGFSampler LumenCardPass.PreIntegratedGFSampler` _[#if !(SUPPORTS_INDEPENDENT_SAMPLERS)]_

#### Entry points (1)

- L28-61 _entry_ `void Main( FVertexFactoryInterpolantsVSToPS Interpolants, FLumenCardInterpolantsVSToPS PassInterpolants, in INPUT_POSITION_QUALIFIERS float4 SvPosition : SV_Position OPTIONAL_IsFrontFace, out float4 OutTarget0 : SV_Target0, out float4 OutTarget1 : SV_Target1, out float4 OutTarget2 : SV_Target2)` — stage: **pixel (from C++ binding)** — C++: `FLumenCardPS` SF_Pixel via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/Lumen/LumenSceneCardCapture.cpp:128)

#### Structs / classes (1)

- L23-26 _struct_ **`FLumenCardInterpolantsVSToPS`** `struct FLumenCardInterpolantsVSToPS`

### `Shaders/Private/Lumen/LumenCardTile.ush` (Private)

- lines: 178; parse: all-branches
- includes: L9 `/Engine/Shared/LumenDefinitions.h`

#### Macros (#define, 2)

- L11 `#define NULL_PACKED_CARD_TILE 0xFFFFFFFF`
- L151 `#define IN_FRUSTUM_DISTANCE 1`
- L7 #pragma `once`

#### Structs / classes (4)

- L13-17 _struct_ **`FCardTileData`** `struct FCardTileData`
  - L15 _member_ `uint CardPageIndex;`
  - L16 _member_ `uint2 TileCoord;`
- L36-44 _struct_ **`FLightTileForCompactionPass`** `struct FLightTileForCompactionPass`
  - L38 _member_ `uint LightIndex;`
  - L39 _member_ `uint ViewIndex;`
  - L40 _member_ `uint bHasShadowMask;`
  - L41 _member_ `uint CardTileIndex;`
  - L42 _member_ `uint CulledLightIndex;`
  - L43 _member_ `uint LightType;`
- L46-52 _struct_ **`FLightTileForShadowMaskPass`** `struct FLightTileForShadowMaskPass`
  - L48 _member_ `uint LightIndex;`
  - L49 _member_ `uint ViewIndex;`
  - L50 _member_ `uint CardPageIndex;`
  - L51 _member_ `uint2 TileCoord;`
- L54-59 _struct_ **`FLightTileForLightPass`** `struct FLightTileForLightPass`
  - L56 _member_ `uint LightIndex;`
  - L57 _member_ `uint ViewIndex;`
  - L58 _member_ `uint ShadowMaskIndex;`

#### Global parameters (uniforms) (3)

- L119 _parameter_ `float4x4 FrustumTranslatedWorldToClip[LUMEN_MAX_VIEWS];`
- L120 _parameter_ `float4 PreViewTranslationHigh[LUMEN_MAX_VIEWS];`
- L121 _parameter_ `float4 PreViewTranslationLow[LUMEN_MAX_VIEWS];`

#### Functions (11)

- L19-26 _function_ `FCardTileData UnpackCardTileData(uint PackedTile)`
- L28-34 _function_ `uint PackCardTileData(FCardTileData CardTile)`
- L61-71 _function_ `FLightTileForCompactionPass UnpackLightTileForCompactionPass(uint2 PackedTile)`
- L73-82 _function_ `FLightTileForShadowMaskPass UnpackLightTileForShadowMaskPass(uint2 PackedTile)`
- L84-91 _function_ `FLightTileForLightPass UnpackLightTileForLightPass(uint2 PackedTile)`
- L93-99 _function_ `uint2 PackLightTileForCompactionPass(FLightTileForCompactionPass Tile)`
- L101-109 _function_ `uint2 PackLightTileForShadowMaskPass(FLightTileForShadowMaskPass Tile)`
- L111-117 _function_ `uint2 PackLightTileForLightPass(FLightTileForLightPass Tile)`
- L124-127 _function_ `FDFVector3 GetPreViewTranslation(uint ViewIndex)`
- L129-132 _function_ `float GetViewExposure(uint ViewIndex)`
- L134-178 _function_ `uint GetCardViewIndex(FLumenCardPageData CardPage, FLumenCardData Card, float2 UVMin, float2 UVMax, float2 CardTileDepthRange, uint NumViews, bool bPrioritizeWhenInFrustum)`

#### Top-level macro invocations (1)

- L122 _macro_call_ `DECLARE_SCALAR_ARRAY(float, ViewExposure, LUMEN_MAX_VIEWS)`

### `Shaders/Private/Lumen/LumenCardTileShadowDownsampleFactor.ush` (Private)

- lines: 108; parse: all-branches
- includes: L9 `../Visualization.ush`

#### Macros (#define, 2)

- L11 `#define LUMEN_CARD_TILE_SHADOW_DOWNSAMPLE_FACTOR_DWORDS 8`
- L12 `#define LUMEN_CARD_TILE_SHADOW_DOWNSAMPLE_FACTOR_DWORDS_MASK (LUMEN_CARD_TILE_SHADOW_DOWNSAMPLE_FACTOR_DWORDS * 32 - 1u)`
- L7 #pragma `once`

#### Structs / classes (1)

- L31-34 _struct_ **`FTileShadowDownsampleFactor`** `struct FTileShadowDownsampleFactor`
  - L33 _member_ `uint4 Data[2];`

#### Global resources (textures / buffers / samplers) (3)

- L14 _resource_ `Buffer<uint> TileShadowDownsampleFactorAtlas;`
- L36 _resource_ `Buffer<uint4> TileShadowDownsampleFactorAtlasForResampling;`
- L78 _resource_ `RWBuffer<uint4> RWTileShadowDownsampleFactorAtlas;`

#### Functions (8)

- L16-23 _function_ `bool LumenCardTileHasUniformVisibilityToLight(uint TileIndexInPhysicalAtlas, uint LightIndex)`
- L25-29 _function_ `bool LumenCardTileHasUniformVisibilityToLight(uint2 TilePhysicalAtlasCoord, uint PhysicalAtlasWidthInTiles, uint LightIndex)`
- L38-45 _function_ `FTileShadowDownsampleFactor LoadLumenCardTileShadowDownsampleFactor(uint TileIndexInPhysicalAtlas)`
- L47-51 _function_ `FTileShadowDownsampleFactor LoadLumenCardTileShadowDownsampleFactor(uint2 TilePhysicalAtlasCoord, uint PhysicalAtlasWidthInTiles)`
- L53-76 _function_ `float3 GetLumenCardTileShadowDownsampleFactorVisualizationColor(uint2 TilePhysicalAtlasCoord, uint PhysicalAtlasWidthInTiles)`
- L80-85 _function_ `void WriteLumenCardTileShadowDownsampleFactor(FTileShadowDownsampleFactor Factor, uint TileIndexInPhysicalAtlas)`
- L87-91 _function_ `void WriteLumenCardTileShadowDownsampleFactor(FTileShadowDownsampleFactor Factor, uint2 TilePhysicalAtlasCoord, uint PhysicalAtlasWidthInTiles)`
- L93-107 _function_ `void SetLumenCardTileShadowDownsampleFactorForLight(inout FTileShadowDownsampleFactor Factor, uint LightIndex)`

### `Shaders/Private/Lumen/LumenCardVertexShader.usf` (Private)

- lines: 51; parse: all-branches
- includes: L3 `../Common.ush`, L9 `/Engine/Generated/Material.ush`, L10 `/Engine/Generated/VertexFactory.ush`, L11 `../BasePassCommonFunctions.ush`

#### Macros (#define, 2)

- L6 `#define SceneTexturesStruct LumenCardPass.SceneTextures`
- L7 `#define ForwardLightStruct LumenCardPass.Forward`

#### Entry points (1)

- L25-50 _entry_ `void Main( FVertexFactoryInput Input, out FLumenCardVSToPS Output )` — stage: **vertex (from C++ binding)** — C++: `FLumenCardVS` SF_Vertex via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/Lumen/LumenSceneCardCapture.cpp:91)

#### Structs / classes (2)

- L13-16 _struct_ **`FLumenCardInterpolantsVSToPS`** `struct FLumenCardInterpolantsVSToPS`
- L18-23 _struct_ **`FLumenCardVSToPS`** `struct FLumenCardVSToPS`
  - L20 _member_ `FVertexFactoryInterpolantsVSToPS FactoryInterpolants;`
  - L21 _member_ `FLumenCardInterpolantsVSToPS PassInterpolants;`
  - L22 _member_ `float4 Position : SV_POSITION;`

### `Shaders/Private/Lumen/LumenCompositeBackgroundVisibility.usf` (Private)

- lines: 36; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../SceneTextureParameters.ush`

#### Entry points (2)

- L11-23 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void LumenFinalizeBackgroundVisibilityCS(uint2 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FLumenFinalizeBackgroundVisibilityCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenReflections.cpp:1110) _[#if defined(LumenFinalizeBackgroundVisibilityCS)]_
- L29-36 _entry_ `void LumenCopyFinalizedBackgroundVisibilityPS( float4 SvPosition : SV_POSITION, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FLumenCopyFinalizedBackgroundVisibilityPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenReflections.cpp:1135)

#### Global resources (textures / buffers / samplers) (3)

- L8 _resource_ `RWTexture2D<UNORM float> RWFinalBackgroundVisibility;` _[#if defined(LumenFinalizeBackgroundVisibilityCS)]_
- L9 _resource_ `Texture2D<float2> ResolvedBackgroundVisibilityTexture;` _[#if defined(LumenFinalizeBackgroundVisibilityCS)]_
- L27 _resource_ `Texture2D<float> FinalBackgroundVisibilityTexture;`

### `Shaders/Private/Lumen/LumenDiffuseColorBoost.ush` (Private)

- lines: 18; parse: all-branches
- L3 #pragma `once`

#### Functions (1)

- L6-18 _function_ `float3 ApplyDiffuseColorBoost(float3 DiffuseColor, float DiffuseColorBoost)` — Optionally boost albedo, but don't allow it to reach 1 as multi-bounce would explode

### `Shaders/Private/Lumen/LumenFloatQuantization.ush` (Private)

- lines: 30; parse: all-branches
- includes: L9 `../Quantization.ush`
- L7 #pragma `once`

#### Global parameters (uniforms) (1)

- L12 _parameter_ `float3 TargetFormatQuantizationError;` — 2^(-NumMantissaBits)

#### Functions (3)

- L14-17 _function_ `float3 QuantizeForFloatRenderTarget(float3 Color, float E, const float3 QuantizationError)`
- L19-22 _function_ `float3 QuantizeForFloatRenderTarget(float3 Color, float E)`
- L24-29 _function_ `float3 QuantizeForFloatRenderTarget(float3 Color, int3 P)`

### `Shaders/Private/Lumen/LumenHairTracing.ush` (Private)

- lines: 139; parse: all-branches
- includes: L7 `../Common.ush`, L8 `../HZBTracing.ush`, L66 `../HairStrands/HairStrandsVoxelPageTraversal.ush` [USE_HAIRSTRANDS_VOXEL]

#### Macros (#define, 4)

- L14 `#define USE_HAIRSTRANDS_SCREEN 0` _[#if !defined(USE_HAIRSTRANDS_SCREEN)]_
- L58 `#define USE_HAIRSTRANDS_VOXEL 0` _[#if !defined(USE_HAIRSTRANDS_VOXEL)]_
- L63 `#define VOXEL_TRAVERSAL_TYPE VOXEL_TRAVERSAL_LINEAR_MIPMAP` _[#if USE_HAIRSTRANDS_VOXEL]_
- L64 `#define VOXEL_TRAVERSAL_DEBUG 0` _[#if USE_HAIRSTRANDS_VOXEL]_

#### Functions (2)

- L19-51 _function_ `void TraceHairScreen( float3 RayTranslatedWorldOrigin, float3 RayWorldDirection, float MaxWorldTraceDistance, float4 InHZBUvFactorAndInvFactor, float MaxIterations, float UncertainTraceRelativeDepthThreshold, float NumThicknessStepsToDetermineCertainty, inout bool bHit, inout bool bUncertain, inout float3 OutScreenUV, inout float3 OutLastVisibleScreenUV, inout float OutHitTileZ)` _[#if USE_HAIRSTRANDS_SCREEN]_
- L68-136 _function_ `void TraceHairVoxels( const uint2 PixelCoord, const float SceneDepth, const float3 SampleTranslatedWorldPosition, const float3 SampleDirection, const float TraceDistance, const bool bIsReflectionTracing, out bool bHit, out float OutTransparency, out float OutHitT)` _[#if USE_HAIRSTRANDS_VOXEL]_

### `Shaders/Private/Lumen/LumenHardwareRayTracingCommon.ush` (Private)

- lines: 1268; parse: all-branches
- includes: L16 `../Nanite/NaniteRayTrace.ush` [NANITE_RAY_TRACING], L26 `../Substrate/SubstrateEvaluation.ush`, L28 `../SceneData.ush`, L29 `../RayTracing/RayTracingCommon.ush`, L30 `../RayTracing/RayTracingDeferredMaterials.ush`, L32 `../RayTracing/RayTracingDeferredShadingCommon.ush` [!COMPUTESHADER], L33 `../RayTracing/RayTracingLightingCommon.ush` [!COMPUTESHADER], L35 `../RayTracing/RayTracingReflectionEnvironment.ush`, L36 `LumenHardwareRayTracingPayloadCommon.ush`, L39 `LumenHardwareRayTracingPlatformCommon.ush` [!COMPUTESHADER], L43 `../RayTracing/TraceRayInline.ush` [COMPUTESHADER], L46 `LumenTracingCommon.ush`, L47 `SurfaceCache/LumenSurfaceCacheSampling.ush`

#### Macros (#define, 16)

- L8 `#define SUPPORT_CONTACT_SHADOWS 0`
- L9 `#define USE_HAIR_LIGHTING 0`
- L12 `#define FAR_FIELD_OCCLUSION_ONLY 0` _[#if !defined(FAR_FIELD_OCCLUSION_ONLY)]_
- L20 `#define SUBSTRATE_SSS_MATERIAL_OVERRIDE 0`
- L23 `#define PreIntegratedGF ReflectionStruct.PreIntegratedGF`
- L24 `#define PreIntegratedGFSampler GlobalBilinearClampedSampler`
- L62 `#define ENABLE_NEAR_FIELD_TRACING 1` _[#if !defined(ENABLE_NEAR_FIELD_TRACING)]_
- L66 `#define LUMEN_HARDWARE_INLINE_RAYTRACING 0` _[#if !defined(LUMEN_HARDWARE_INLINE_RAYTRACING)]_
- L70 `#define RECURSIVE_REFRACTION_TRACES 0` _[#if !defined(RECURSIVE_REFRACTION_TRACES)]_
- L75 `#define AVOID_SELF_INTERSECTIONS_MODE_DISABLED 0`
- L76 `#define AVOID_SELF_INTERSECTIONS_MODE_RETRACE 1`
- L77 `#define AVOID_SELF_INTERSECTIONS_MODE_AHS 2`
- L80 `#define AVOID_SELF_INTERSECTIONS_MODE AVOID_SELF_INTERSECTIONS_MODE_DISABLED` _[#if !defined(AVOID_SELF_INTERSECTIONS_MODE)]_
- L84 `#define ENABLE_TRACING_FEEDBACK 0` _[#if !defined(ENABLE_TRACING_FEEDBACK)]_
- L91 `#define LUMEN_HARDWARE_RAY_TRACING_ENTRY(name) void name##_INTERNAL(uint3 DispatchThreadIndex, uint3 DispatchGroupId, uint DispatchGroupIndex); [numthreads(INLINE_RAY_TRACING_THREAD_GROUP_SIZE_X, INLINE_RAY_TRACING_THREAD_GROUP_SIZE_Y, 1)] void na ...` (6 lines) _[#if LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L100 `#define LUMEN_HARDWARE_RAY_TRACING_ENTRY(name) void name##_INTERNAL(uint3 DispatchThreadIndex, uint3 DispatchGroupId, uint DispatchGroupIndex); RAY_TRACING_ENTRY_RAYGEN(name##RGS){ name##_INTERNAL(DispatchRaysIndex(), DispatchRaysIndex(), 0);} voi ...` (5 lines) _[#if !(LUMEN_HARDWARE_INLINE_RAYTRACING)]_
- L3 #pragma `once`; L6 #pragma `message("UESHADERMETADATA_VERSION A027A214-A1AF-323E-24C1-AFAF33FAB21C")`

#### Structs / classes (6)

- L130-133 _struct_ **`FHitGroupRootConstants`** `struct FHitGroupRootConstants`
  - L132 _member_ `uint UserData;`
- L135-176 _struct_ **`FRayTracedLightingContext`** `struct FRayTracedLightingContext`
  - L138 _member_ `StructuredBuffer<FHitGroupRootConstants> HitGroupData;` _[#if LUMEN_HARDWARE_INLINE_RAYTRACING]_
  - L139 _member_ `StructuredBuffer<FRayTracingSceneMetadataRecord> RayTracingSceneMetadata;` _[#if LUMEN_HARDWARE_INLINE_RAYTRACING]_
  - L140 _member_ `RWStructuredBuffer<uint> RWInstanceHitCountBuffer;` _[#if LUMEN_HARDWARE_INLINE_RAYTRACING]_
  - L143 _member_ `FRayCone RayCone;`
  - L144 _member_ `uint2 TraceCoord;`
  - L145 _member_ `uint LinearCoord;`
  - L146 _member_ `uint InstanceMask;`
  - L149 _member_ `uint MaxTraversalIterations;` — Max ray tracing traversal iterations on supported platforms
  - L151 _member_ `float MinTraceDistanceToSampleSurfaceCache;`
  - L153 _member_ `uint MaxReflectionBounces;`
  - L154 _member_ `uint MaxRefractionBounces;`
  - L156 _member_ `uint CullingMode;`
  - L158 _member_ `bool bHiResSurface;` — Whether to sample high res surface cache data or low res always resident pages
  - L159 _member_ `bool bAcceptFirstHitAndEndSearch;`
  - L160 _member_ `bool bIsShadowRay;`
  - L161 _member_ `bool bIsFarFieldRay;`
  - L162 _member_ `bool bUseBookmark;`
  - L163 _member_ `bool bForceOpaque;`
  - L164 _member_ `bool bMeshSectionVisibilityTest;`
  - L165 _member_ `bool bForceClosestHitShader;`
  - L168 _member_ `float HitLightingShadowMaxTraceDistance;` — Hit-lighting
  - L169 _member_ `uint HitLightingShadowMode;`
  - L170 _member_ `uint HitLightingShadowTranslucencyMode;`
  - L171 _member_ `bool bHitLightingDirectLighting;`
  - L172 _member_ `bool bHitLightingSkylight;`
  - L173 _member_ `bool bUseReflectionCaptures;`
  - L175 _member_ `uint LightingChannelMask;`
- L222-239 _struct_ **`FLumenMinimalRayResult`** `struct FLumenMinimalRayResult`
  - L224 _member_ `bool bHit;`
  - L225 _member_ `bool bCompleted;`
  - L226 _member_ `bool bTranslucent;`
  - L227 _member_ `bool bTwoSided;`
  - L228 _member_ `bool bAlphaMasked;`
  - L229 _member_ `bool bFrontFace;`
  - L231 _member_ `uint MaterialShaderIndex;`
  - L232 _member_ `uint SceneInstanceIndex;`
  - L233 _member_ `float HitT;`
  - L234 _member_ `float3 HitNormal;`
  - L236 _member_ `uint NumIterations;`
  - L238 _member_ `FLumenRayHitBookmark Bookmark;`
- L249-270 _struct_ **`FRayTracedLightingResult`** `struct FRayTracedLightingResult`
  - L251 _member_ `bool bIsHit;`
  - L252 _member_ `bool bIsCompleted;` — Was ray tracing completed or stopped due to reaching MaxTraversalIterations
  - L253 _member_ `bool bIsFarField;`
  - L254 _member_ `bool bHitTwoSided;`
  - L255 _member_ `bool bFrontface;`
  - L256 _member_ `float TraceHitDistance;`
  - L258 _member_ `float3 PathThroughput;`
  - L259 _member_ `float2 BackgroundVisibility;` — x: BV accumulated from translucent hits, y: alpha used to blend with existing BV in SceneColor
  - L261 _member_ `bool bIsRadianceCompleted;` — Is radiance computation completed or do we need a fallback shading pass
  - L262 _member_ `float3 Radiance;`
  - L264 _member_ `float3 GeometryWorldNormal;`
  - L265 _member_ `uint SceneInstanceIndex;`
  - L267 _member_ `bool bValidSurfaceCache;`
  - L268 _member_ `uint MaterialShaderIndex;`
  - L269 _member_ `FLumenRayHitBookmark Bookmark;`
- L408-434 _struct_ **`FLumenTraceRayInlineCallback`** `struct FLumenTraceRayInlineCallback : FDefaultTraceRayInlineCallback` — base/reg: `FDefaultTraceRayInlineCallback` _[#if COMPUTESHADER && LUMEN_HARDWARE_INLINE_RAYTRACING]_
  - L410 _member_ `StructuredBuffer<FHitGroupRootConstants> HitGroupData;` _[#if COMPUTESHADER && LUMEN_HARDWARE_INLINE_RAYTRACING]_
  - L411 _member_ `bool bShadowRay;` _[#if COMPUTESHADER && LUMEN_HARDWARE_INLINE_RAYTRACING]_
  - L412 _member_ `uint LightingChannelMask;` _[#if COMPUTESHADER && LUMEN_HARDWARE_INLINE_RAYTRACING]_
  - L414 _method_ `bool OnAnyHit(float3 ObjectRayOrigin, float3 ObjectRayDirection, FTraceRayInlineResult Hit)` _[#if COMPUTESHADER && LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L770-784 _struct_ **`FLumenHitLightingMaterial`** `struct FLumenHitLightingMaterial` _[#if !COMPUTESHADER]_
  - L772 _member_ `float3 TopLayerSpecularColor;` _[#if !COMPUTESHADER]_
  - L773 _member_ `float TopLayerRoughness;` _[#if !COMPUTESHADER]_
  - L778 _member_ `float3 ApproxFullyRoughDiffuseColor;` — Return approximate diffuse color as if the entire surface was diffuse in order to conserve energy in secondary bounces Keep in sync with LumenCardPixelShader.usf #lumen_todo: refactor and merge with LumenCardPixelShader.usf to ensure that their logic is the same _[#if !COMPUTESHADER]_
  - L779 _member_ `float3 DiffuseColor;` _[#if !COMPUTESHADER]_
  - L780 _member_ `float3 ApproxFullyRoughSpecularColor;` _[#if !COMPUTESHADER]_
  - L782 _member_ `float3 RefractedThroughputPreCoverage;` _[#if !COMPUTESHADER]_
  - L783 _member_ `float Ior;` _[#if !COMPUTESHADER]_

#### Global parameters (uniforms) (2)

- L437 _parameter_ `uint RayTracingSceneLightingChannelAndMask;`
- L645 _parameter_ `float SurfaceCacheSamplingDepthBias;`

#### Functions (19)

- L49-59 _function_ `float3 CalcPrevTranslatedWorldPositionFromGPUSceneInstanceIndex(float3 TranslatedWorldPosition, uint GPUSceneInstanceIndex)`
- L111-128 _function_ `float ClipAndDitherNearFieldMaxTraceDistance( float3 TranslatedWorldRayOrigin, float3 RayDirection, uint2 NoiseCoord, float NearFieldSceneRadius, float NearFieldMaxTraceDistance, float NearFieldMaxTraceDistanceDitherScale)` — Clip near field ray to ray tracing culling radius, and apply dithering to hide transition region between nead and far field.
- L178-220 _function_ `FRayTracedLightingContext CreateRayTracedLightingContext( in FRayCone RayCone, in uint2 TraceCoord, in uint LinearCoord, in uint CullingMode, uint MaxTraversalIterations, bool bMeshSectionVisibilityTest)`
- L241-247 _function_ `FLumenMinimalRayResult InitLumenMinimalRayResult()`
- L272-293 _function_ `FRayTracedLightingResult CreateRayTracedLightingResult(FRayDesc Ray)`
- L295-330 _function_ `FRayTracedLightingResult CreateRayTracedLightingResult( FRayDesc Ray, FRayTracedLightingContext Context, FLumenMinimalRayResult MinimalRayResult, FSurfaceCacheSample SurfaceCacheSample)`
- L333-358 _function_ `bool TraceLumenHitLightingRay( in RaytracingAccelerationStructure TLAS, in FRayDesc Ray, inout FRayTracedLightingContext Context, inout FLumenRayHitBookmark Bookmark, inout FPackedMaterialClosestHitPayload Payload)` _[#if !COMPUTESHADER]_
- L365-405 _function_ `bool LumenMinimalRayAnyHitShader(uint UserData, float HitT, bool bHitBackFace, bool bShadowRay)` — Lumen minimal (surface cache) ray any hit shader logic shared between inline and RayGen traces. See LumenHardwareRayTracingMaterials.usf.
- L439-643 _function_ `FLumenMinimalRayResult TraceLumenMinimalRay( in RaytracingAccelerationStructure TLAS, FRayDesc Ray, inout FRayTracedLightingContext Context)`
- L647-679 _function_ `FSurfaceCacheSample CalculateSurfaceCacheLighting( FRayDesc Ray, FRayTracedLightingContext Context, float3 RayHitTranslatedWorldPosition, float3 RayHitWorldNormal, float HitDistance, uint SceneInstanceIndex )`
- L681-713 _function_ `FSurfaceCacheSample SampleLumenMinimalRayHit( FRayDesc Ray, FRayTracedLightingContext Context, FLumenMinimalRayResult MinimalRayResult)`
- L716-734 _function_ `bool TraceDeferredMaterialRay( in RaytracingAccelerationStructure TLAS, in FRayDesc Ray, inout FRayTracedLightingContext Context, inout FDeferredMaterialPayload DeferredMaterialPayload )` _[#if !COMPUTESHADER]_
- L736-768 _function_ `float3 CalculateDirectLighting( in RaytracingAccelerationStructure TLAS, in RaytracingAccelerationStructure FarFieldTLAS, in FRayDesc Ray, in FRayTracedLightingContext Context, inout FPackedMaterialClosestHitPayload Payload, FRandomSequence RandSequence, float3 RayHitTranslatedWorldPosition, float3 RayHitWorldNormal)` _[#if !COMPUTESHADER]_
- L786-870 _function_ `FLumenHitLightingMaterial GetLumenHitLightingMaterial(FRayTracedLightingContext Context, FPackedMaterialClosestHitPayload PackedPayload, FRayDesc Ray)` _[#if !COMPUTESHADER]_
- L872-958 _function_ `float3 CalculateLightingAtHit( RaytracingAccelerationStructure TLAS, RaytracingAccelerationStructure FarFieldTLAS, FRayDesc Ray, FRayTracedLightingContext Context, FRandomSequence RandSequence, FLumenHitLightingMaterial LumenMaterial, float NextReflectionRayAlpha, inout FPackedMaterialClosestHitPayload Payload)` _[#if !COMPUTESHADER]_
- L963-1177 _function_ `FRayTracedLightingResult TraceAndCalculateRayTracedLighting( in RaytracingAccelerationStructure TLAS, in RaytracingAccelerationStructure FarFieldTLAS, in FRayDesc Ray, in FRayTracedLightingContext Context, inout FLumenRayHitBookmark Bookmark )` — Traces a ray and calculates lighting at a hit point using hit lighting. _[#if !COMPUTESHADER]_
- L1179-1188 _function_ `FRayTracedLightingResult TraceAndCalculateRayTracedLighting( in RaytracingAccelerationStructure TLAS, in RaytracingAccelerationStructure FarFieldTLAS, in FRayDesc Ray, inout FRayTracedLightingContext Context)` _[#if !COMPUTESHADER]_
- L1196-1242 _function_ `FRayTracedLightingResult TraceSurfaceCacheRay( in RaytracingAccelerationStructure TLAS, FRayDesc Ray, FRayTracedLightingContext Context)` — Trace ray without using any material shaders Optionally handle alpha masking through surface cache
- L1247-1268 _function_ `FRayTracedLightingResult TraceSurfaceCacheFarFieldRay( in RaytracingAccelerationStructure TLAS, FRayDesc Ray, FRayTracedLightingContext Context)` — Trace far field ray without using any material shaders

### `Shaders/Private/Lumen/LumenHardwareRayTracingMaterials.usf` (Private)

- lines: 64; parse: all-branches
- includes: L3 `/Engine/Shared/RayTracingTypes.h`, L4 `/Engine/Private/Common.ush`, L5 `/Engine/Private/SceneData.ush`, L6 `/Engine/Private/RayTracing/RayTracingHitGroupCommon.ush`, L7 `/Engine/Private/Lumen/LumenHardwareRayTracingCommon.ush`, L8 `/Engine/Private/Lumen/LumenHardwareRayTracingPayloadCommon.ush`, L9 `/Engine/Private/Lumen/LumenHardwareRayTracingPlatformCommon.ush`

#### Entry points (3)

- L11-39 _entry_ `RAY_TRACING_ENTRY_CLOSEST_HIT(LumenHardwareRayTracingMaterialCHS, FLumenMinimalPayload, Payload, FRayTracingIntersectionAttributes, Attributes)` — stage: **closesthit** — C++: `FLumenHardwareRayTracingMaterialHitGroup` SF_RayHitGroup via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenHardwareRayTracingMaterials.cpp:87)
- L41-45 _entry_ `RAY_TRACING_ENTRY_MISS(LumenHardwareRayTracingMaterialMS, FLumenMinimalPayload, Payload)` — stage: **miss** — C++: `FLumenHardwareRayTracingMaterialMS` SF_RayMiss via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenHardwareRayTracingMaterials.cpp:118)
- L47-64 _entry_ `RAY_TRACING_ENTRY_ANY_HIT( LumenHardwareRayTracingMaterialAHS, FLumenMinimalPayload, Payload, FRayTracingIntersectionAttributes, Attributes)` — stage: **anyhit** — C++: `FLumenHardwareRayTracingMaterialHitGroup` SF_RayHitGroup via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenHardwareRayTracingMaterials.cpp:87)

### `Shaders/Private/Lumen/LumenHardwareRayTracingPayloadCommon.ush` (Private)

- lines: 125; parse: all-branches
- includes: L5 `../RayTracing/RayTracingCommon.ush`, L6 `/Engine/Shared/LumenDefinitions.h`

#### Macros (#define, 4)

- L13 `#define LUMEN_RAYHIT_BOOKMARK_MISS 0xFFFFFFFF`
- L15 `#define MATERIAL_INDEX 0`
- L16 `#define NORMAL_INDEX 1`
- L17 `#define GPU_SCENE_INSTANCE_INDEX 2`
- L3 #pragma `once`

#### Structs / classes (2)

- L8-11 _struct_ **`FLumenRayHitBookmark`** `struct FLumenRayHitBookmark`
  - L10 _member_ `uint2 PackedData;`
- L20-120 _struct_ **`FLumenMinimalPayload`** `struct FLumenMinimalPayload : FMinimalPayload` — base/reg: `FMinimalPayload` — #lumen_todo: Pack more aggressively. HitT - 2 bytes, GPUSceneIndex - 3 bytes, MaterialIndex - 3 bytes
  - L22 _member_ `uint PackedData[3];`
  - L24 _method_ `void SetIsTranslucent(uint bIsTranslucent)`
  - L29 _method_ `uint IsTranslucent()`
  - L35 _method_ `void SetIsTwoSided(uint bIsTwoSided)`
  - L40 _method_ `uint IsTwoSided()`
  - L46 _method_ `void SetIsShadowRay(uint bIsShadowRay)`
  - L51 _method_ `uint IsShadowRay()`
  - L57 _method_ `void SetIsAlphaMasked(uint bIsAlphaMasked)`
  - L62 _method_ `uint IsAlphaMasked()`
  - L68 _method_ `void SetFrontFace(bool bFrontFace)`
  - L73 _method_ `uint IsFrontFace()`
  - L79 _method_ `void SetIsDynamicGeometry(uint bIsDynamicGoeometry)`
  - L84 _method_ `uint IsDynamicGeometry()`
  - L90 _method_ `void SetMaterialShaderIndex(uint MaterialShaderIndex)`
  - L95 _method_ `uint GetMaterialShaderIndex()`
  - L101 _method_ `void SetWorldNormal(float3 WorldNormal)`
  - L106 _method_ `float3 GetWorldNormal()`
  - L111 _method_ `void SetGPUSceneInstanceIndex(uint GPUSceneInstanceIndex)`
  - L116 _method_ `uint GetGPUSceneInstanceIndex()`

#### Top-level macro invocations (1)

- L123-125 _macro_call_ `CHECK_RT_PAYLOAD_SIZE(FLumenMinimalPayload)` _[#if IS_PAYLOAD_ENABLED(RT_PAYLOAD_TYPE_LUMEN_MINIMAL)]_

### `Shaders/Private/Lumen/LumenHardwareRayTracingPlatformCommon.ush` (Private)

- lines: 66; parse: all-branches
- includes: L6 `/Engine/Public/NvidiaExtensionsCommon.ush` [RAY_TRACING_USE_SER], L11 `/Platform/Private/LumenHardwareRayTracingPlatformCommon.ush` [defined(OVERRIDE_LUMENHARDWARERAYTRACINGPLATFORMCOMMON_USH)]

#### Macros (#define, 1)

- L14 `#define TraceLumenRay(TLAS, RayFlags, InstanceInclusionMask, ShaderSlot, NumShaderSlots, MissIndex, Ray, InOutPayload, OutBookmark) { TraceRay(TLAS, RayFlags, InstanceInclusionMask, ShaderSlot, NumShaderSlots, MissIndex, Ray, InOutPayload); }` (3 lines) _[#if !(defined(OVERRIDE_LUMENHARDWARERAYTRACINGPLATFORMCOMMON_USH))]_
- L3 #pragma `once`

#### Functions (3)

- L18-36 _function_ `void TraceLumenShadingRay( RaytracingAccelerationStructure AccelerationStructure, uint RayFlags, uint InstanceInclusionMask, uint RayContributionToHitGroupIndex, uint MultiplierForGeometryContributionToHitGroupIndex, uint MissShaderIndex, RayDesc Ray, inout FPackedMaterialClosestHitPayload Payload)` _[#if !(defined(OVERRIDE_LUMENHARDWARERAYTRACINGPLATFORMCOMMON_USH))]_
- L38-57 _function_ `void TraceLumenShadingRay( RaytracingAccelerationStructure AccelerationStructure, uint RayFlags, uint InstanceInclusionMask, uint RayContributionToHitGroupIndex, uint MultiplierForGeometryContributionToHitGroupIndex, uint MissShaderIndex, RayDesc Ray, inout FLumenRayHitBookmark Bookmark, inout FPackedMaterialClosestHitPayload Payload)` _[#if !(defined(OVERRIDE_LUMENHARDWARERAYTRACINGPLATFORMCOMMON_USH))]_
- L60-63 _function_ `float3 ComputeWorldNormal(uint PrimitiveIndex, uint ClusterId)` _[#if !(defined(OVERRIDE_LUMENHARDWARERAYTRACINGPLATFORMCOMMON_USH)) && !defined(LUMEN_HARDWARE_RAYTRACING)]_

### `Shaders/Private/Lumen/LumenIrradianceFieldGather.usf` (Private)

- lines: 150; parse: all-branches
- includes: L3 `../Common.ush`, L4 `LumenMaterial.ush`, L6 `../DeferredShadingCommon.ush`, L7 `../BRDF.ush`, L8 `../SceneTextureParameters.ush`, L9 `LumenPosition.ush`, L10 `LumenRadianceCacheMarkCommon.ush`, L11 `LumenTracingCommon.ush`, L12 `LumenIrradianceFieldInterpolation.ush`, L13 `../ClearCoatCommon.ush`, L14 `../ReflectionEnvironmentShared.ush`, L15 `LumenReflectionsCombine.ush`, L16 `LumenUpsample.ush`

#### Macros (#define, 1)

- L19 `#define THREADGROUP_SIZE 1` _[#if !defined(THREADGROUP_SIZE)]_

#### Entry points (3)

- L28-45 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void DownsampleDepthAndNormalCS( uint2 GroupId : SV_GroupID, uint2 GroupThreadId : SV_GroupThreadID, uint2 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FDownsampleDepthAndNormalCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenIrradianceFieldGather.cpp:239) _[#if defined(DownsampleDepthAndNormalCS)]_
- L53-86 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void MarkProbesUsedByGBufferCS( uint2 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FMarkProbesUsedByGBufferCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenIrradianceFieldGather.cpp:277) _[#if defined(MarkProbesUsedByGBufferCS)]_
- L98-148 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void InterpolateIrradianceProbesToPixelsCS( uint2 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FInterpolateIrradianceProbesToPixelsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenIrradianceFieldGather.cpp:327) _[#if defined(InterpolateIrradianceProbesToPixelsCS)]_

#### Global resources (textures / buffers / samplers) (4)

- L24 _resource_ `RWTexture2D<float> RWDownsampledSceneDepth;` _[#if defined(DownsampleDepthAndNormalCS)]_
- L25 _resource_ `RWTexture2D<UNORM float3> RWDownsampledNormal;` _[#if defined(DownsampleDepthAndNormalCS)]_
- L92 _resource_ `RWTexture2DArray<float3> RWDiffuseIndirect;` _[#if defined(InterpolateIrradianceProbesToPixelsCS)]_
- L93 _resource_ `RWTexture2DArray<float3> RWRoughSpecularIndirect;` _[#if defined(InterpolateIrradianceProbesToPixelsCS)]_

#### Global parameters (uniforms) (4)

- L26 _parameter_ `uint DownsampleFactor;` _[#if defined(DownsampleDepthAndNormalCS)]_
- L51 _parameter_ `uint MarkProbesDownsampleFactor;` _[#if defined(MarkProbesUsedByGBufferCS)]_
- L95 _parameter_ `uint InterpolationFeedbackTileWrapMask;` _[#if defined(InterpolateIrradianceProbesToPixelsCS)]_
- L96 _parameter_ `uint2 InterpolationFeedbackTileJitter;` _[#if defined(InterpolateIrradianceProbesToPixelsCS)]_

### `Shaders/Private/Lumen/LumenIrradianceFieldInterpolation.ush` (Private)

- lines: 368; parse: all-branches
- includes: L5 `LumenRadianceCacheInterpolation.ush`, L6 `LumenReflectionsCombine.ush`

#### Macros (#define, 4)

- L86 `#define CHEBYSHEV_PROBE_OCCLUSION 1`
- L112 `#define DISCARD_INVALID_PROBES 1`
- L161 `#define PROBE_OCCLUSION_INTERPOLATION 1`
- L353 `#define DEBUG_VISUALIZE_INTERPOLATION_MISS 0`
- L3 #pragma `once`

#### Structs / classes (1)

- L135-139 _struct_ **`FIrradianceCacheInterpolation`** `struct FIrradianceCacheInterpolation`
  - L137 _member_ `bool bSuccess;`
  - L138 _member_ `uint3 ProbeCoord;`

#### Global resources (textures / buffers / samplers) (6)

- L8 _resource_ `Texture2D<float3> RadianceCacheFinalIrradianceAtlas;`
- L9 _resource_ `Texture2D<float2> RadianceCacheProbeOcclusionAtlas;`
- L10 _resource_ `RWBuffer<uint> RWProbeLastUsedFrame;`
- L11 _resource_ `Buffer<uint> ProbeAdaptiveIndices;`
- L12 _resource_ `Buffer<uint> ProbeValid;`
- L275 _resource_ `RWBuffer<uint> RWProbeInterpolationMisses;` _[#if ADAPTIVE_PROBES]_

#### Global parameters (uniforms) (10)

- L13 _parameter_ `uint FinalIrradianceProbeResolution;`
- L14 _parameter_ `float2 FinalIrradianceAtlasTexelSize;`
- L15 _parameter_ `uint CalculateIrradiance;`
- L16 _parameter_ `uint IrradianceProbeResolution;`
- L18 _parameter_ `uint OcclusionProbeResolution;` — Resolution of Octahedral layout for sampling
- L19 _parameter_ `uint FinalOcclusionProbeResolution;`
- L20 _parameter_ `float2 FinalOcclusionAtlasTexelSize;`
- L276 _parameter_ `uint MaxNumProbes;` _[#if ADAPTIVE_PROBES]_
- L297 _parameter_ `float MaxRoughnessToEvaluateRoughSpecular;`
- L298 _parameter_ `float ProbeOcclusionBias;`

#### Functions (9)

- L22-31 _function_ `float3 SampleIrradianceCacheProbe(uint ProbeIndex, float2 ProbeUV)`
- L33-42 _function_ `float2 SampleProbeOcclusion(uint ProbeIndex, float3 WorldSpaceDirection)`
- L44-47 _function_ `float SampleProbeValid(uint ProbeIndex)`
- L49-53 _function_ `float3 SampleIrradianceCacheProbeCoord(uint3 ProbeCoord, uint ProbeClipmapIndex, float2 ProbeUV)`
- L55-58 _function_ `uint GetAdaptiveProbeIndex(uint UniformProbeIndex, uint ArrayIndex)`
- L60-133 _function_ `void InterpolateIrradianceFromProbe( float3 TranslatedPixelPosition, float3 TranslatedSamplePosition, float3 ProbeTranslatedWorldPosition, float3 WorldSpaceNormal, float2 IrradianceProbeUV, float3 ReflectionWorldSpaceDirection, float ReflectionMipLevel, bool bPixelShouldProcessFeedback, uint ProbeIndex, float TrilinearWeight, bool bAdaptiveProbe, bool bSampleReflection, float MinWeight, inout float3 OutIrradiance, inout float3 OutReflectionRadiance, inout float OutTotalWeight)`
- L141-271 _function_ `float3 SampleIrradianceCacheInterpolated( float3 TranslatedPixelPosition, float3 TranslatedSamplePosition, float3 WorldSpaceNormal, float3 ReflectionWorldSpaceDirection, float ReflectionConeHalfAngle, uint ClipmapIndex, bool bPixelShouldProcessFeedback, bool bSampleReflection, out float3 OutReflectionRadiance, out FIrradianceCacheInterpolation OutInterpolation)`
- L278-294 _function_ `void HandleInterpolationMisses(FIrradianceCacheInterpolation Interpolation, uint ClipmapIndex, float3 TranslatedSamplePosition)` _[#if ADAPTIVE_PROBES]_
- L300-368 _function_ `void GetIrradianceFieldInterpolatedLighting( float2 PixelPos, float3 TranslatedWorldPosition, float3 MaterialWorldNormal, float MaterialRoughness, float3 WorldNormalForReflection, bool bHasBackfaceDiffuse, bool bPixelShouldProcessFeedback, inout float3 OutDiffuseLighting, inout float3 OutSpecularLighting)`

### `Shaders/Private/Lumen/LumenMaterial.ush` (Private)

- lines: 952; parse: all-branches
- includes: L14 `../Common.ush`, L15 `../ShadingModelsSampling.ush`, L16 `../ClearCoatCommon.ush`, L17 `../Lumen/LumenPosition.ush`, L20 `../HairStrands/HairStrandsVisibilityCommon.ush` [MATERIAL_SOURCE == MATERIAL_SOURCE_HAIR_STRANDS], L21 `../HairStrands/HairStrandsVisibilityUtils.ush` [MATERIAL_SOURCE == MATERIAL_SOURCE_HAIR_STRANDS], L30 `/Engine/Private/Substrate/Substrate.ush` [SUBSTRATE_ENABLED], L31 `/Engine/Private/Substrate/SubstrateEvaluation.ush` [SUBSTRATE_ENABLED], L32 `/Engine/Private/Substrate/SubstrateTile.ush` [SUBSTRATE_ENABLED], L33 `../Substrate/SubstrateMaterialSampling.ush` [SUBSTRATE_ENABLED]

#### Macros (#define, 8)

- L6 `#define MATERIAL_SOURCE_GBUFFER 0`
- L7 `#define MATERIAL_SOURCE_FRONT_LAYER_GBUFFER 1`
- L8 `#define MATERIAL_SOURCE_HAIR_STRANDS 2`
- L11 `#define MATERIAL_SOURCE MATERIAL_SOURCE_GBUFFER` _[#if !defined(MATERIAL_SOURCE)]_
- L25 `#define SUBSTRATE_STOCHASTIC_LIGHTING_ALLOWED 0` _[#if !defined(SUBSTRATE_STOCHASTIC_LIGHTING_ALLOWED)]_
- L29 `#define SUBSTRATE_INLINE_SHADING 0` _[#if SUBSTRATE_ENABLED]_
- L67 `#define PERMUTATION_OVERFLOW_TILE 0` _[#if !defined(PERMUTATION_OVERFLOW_TILE)]_
- L72 `#define DOWNSAMPLE_FACTOR 1` _[#if PERMUTATION_OVERFLOW_TILE && !defined(DOWNSAMPLE_FACTOR)]_
- L3 #pragma `once`

#### Structs / classes (2)

- L38-47 _struct_ **`FLumenMaterialCoord`** `struct FLumenMaterialCoord` — Abstract coord for material data
  - L40 _member_ `uint2 SvPosition;`
  - L41 _member_ `uint3 SvPositionFlatten;`
  - L42 _member_ `uint ClosureIndex;`
  - L44 _member_ `uint3 DownsampledCoord;`
  - L45 _member_ `bool bIsValid;`
  - L46 _member_ `bool bIsAnyValid;`
- L244-317 _struct_ **`FLumenMaterialData`** `struct FLumenMaterialData` — Abstract input material data (FGBufferData/Substrate)
  - L247 _member_ `float DeviceZ;` — DeviceZ isn't the same as ConvertToDeviceZ(Depth) due to a small fudge factor preventing divide by zero
  - L248 _member_ `float SceneDepth;`
  - L250 _member_ `float3 DiffuseAlbedo;`
  - L251 _member_ `float3 WorldNormal;`
  - L252 _member_ `float3 WorldNormalForPositionBias;`
  - L253 _member_ `float Roughness;`
  - L254 _member_ `float TopLayerRoughness;`
  - L255 _member_ `float MaterialAO;`
  - L256 _member_ `uint ShadingID;`
  - L257 _member_ `uint DiffuseIndirectSampleOcclusion;`
  - L258 _member_ `bool bNeedsSeparateLightAccumulation;`
  - L259 _member_ `bool bRequiresBxDFImportanceSampling;`
  - L260 _member_ `bool bIsValid;`
  - L261 _member_ `bool bIsMegaLightsValid;`
  - L262 _member_ `bool bIsSimple;`
  - L263 _member_ `bool bIsSingle;`
  - L264 _member_ `bool bIsComplex;`
  - L265 _member_ `bool bIsComplexSpecial;`
  - L266 _member_ `bool bIsSLW;`
  - L267 _member_ `bool bIsHair;`
  - L268 _member_ `bool bHasBackfaceDiffuse;`
  - L269 _member_ `bool bIsFrontLayerTranslucency;`
  - L270 _member_ `bool bIsFirstPerson;`
  - L271 _member_ `float Anisotropy;`
  - L274 _member_ `bool bHasSecondSpecularLobe;` _[#if SUBSTRATE_GBUFFER_FORMAT==1]_
  - L275 _member_ `bool bHasBottomNormal;` _[#if SUBSTRATE_GBUFFER_FORMAT==1]_
  - L276 _member_ `float2 BottomNormalOct;` _[#if SUBSTRATE_GBUFFER_FORMAT==1]_
  - L277 _member_ `float3x3 TangentBasis;` _[#if SUBSTRATE_GBUFFER_FORMAT==1]_
  - L278 _member_ `uint ClosureIndex;` _[#if SUBSTRATE_GBUFFER_FORMAT==1]_
  - L279 _member_ `uint ClosureCount;` _[#if SUBSTRATE_GBUFFER_FORMAT==1]_
  - L281 _member_ `FGBufferData GBufferData;` _[#if !(SUBSTRATE_GBUFFER_FORMAT==1) && !FRONT_LAYER_TRANSLUCENCY]_
  - L284 _method_ `bool IsValid()`
  - L289 _method_ `bool IsMegaLightsValid()`
  - L294 _method_ `bool IsSimple()`
  - L299 _method_ `bool IsSingle()`
  - L304 _method_ `bool IsComplexSpecial()`
  - L309 _method_ `uint GetClosureCount()`

#### Global resources (textures / buffers / samplers) (3)

- L621 _resource_ `Texture2D FrontLayerTranslucencySceneDepth;`
- L622 _resource_ `Texture2D FrontLayerTranslucencyGBufferA;`
- L623 _resource_ `Texture2D FrontLayerTranslucencyGBufferB;`

#### Global parameters (uniforms) (1)

- L82 _parameter_ `uint ScreenProbeGatherStateFrameIndex;`

#### Functions (42)

- L53-64 _function_ `FLumenMaterialCoord GetLumenMaterialCoord(in uint2 SvPosition, uint InClosureIndex)`
- L76-80 _function_ `uint GetLumenMaterialLinearIndex(uint2 GroupId)`
- L87-102 _function_ `uint2 GetDownsampledCoordJitter(uint2 DownsampledScreenCoord, uint DownsampleFactor)` — 4-rooks jittering sampling pattern in the range [0, DownsampleFactor - 1]
- L104-206 _function_ `FLumenMaterialCoord GetLumenMaterialCoordDownsampled(uint2 DispatchThreadId, uint2 GroupId, uint2 GroupThreadId, uint DownsampleFactor, uint2 DownsampledViewMin, uint2 DownsampledViewSize)`
- L208-233 _function_ `FLumenMaterialCoord GetLumenMaterialCoord(uint2 DispatchThreadId, uint2 GroupId, uint2 GroupThreadId, inout bool bIsValid, inout bool bIsAnyValid, bool bAddMinRect=true)`
- L235-240 _function_ `FLumenMaterialCoord GetLumenMaterialCoord(uint2 DispatchThreadId, uint2 GroupId, uint2 GroupThreadId)`
- L320-329 _function_ `bool RequiresBxDFImportanceSampling(uint ShadingModelID)` — Note: must match SampleBxDFWrapper
- L332-385 _function_ `FLumenMaterialData InternalReadMaterialData_Substrate_Stochastic(uint2 InCoord, uint InClosureIndex, float MaxRoughnessToTraceSmoothReflection)` _[#if SUBSTRATE_STOCHASTIC_LIGHTING_ALLOWED]_
- L387-390 _function_ `FLumenMaterialData InternalReadMaterialData_Substrate_Stochastic(uint2 InPixelPos)` _[#if SUBSTRATE_STOCHASTIC_LIGHTING_ALLOWED]_
- L397-462 _function_ `FLumenMaterialData InternalReadMaterialData_Substrate_Regular(uint2 InPixelPos)` — Substrate material internal read function - Average/Top layer data
- L465-540 _function_ `FLumenMaterialData InternalReadMaterialData_Substrate_Regular(uint2 InCoord, uint InClosureIndex, float MaxRoughnessToTraceSmoothReflection)` — Substrate material internal read function - Per-BSDF data
- L543-555 _function_ `FLumenMaterialData InternalReadMaterialData_Substrate(uint2 InCoord, uint InClosureIndex, float MaxRoughnessToTraceSmoothReflection, bool bAllowStochaticMaterial)` — Substrate material internal read function - Per-BSDF data
- L557-569 _function_ `FLumenMaterialData InternalReadMaterialData_Substrate(uint2 InPixelPos, bool bAllowStochaticMaterial)`
- L572-619 _function_ `FLumenMaterialData InternalReadMaterialData_HairStrands(uint2 ScreenCoord)`
- L625-657 _function_ `FLumenMaterialData InternalReadMaterialData_FrontLayerTranslucency(uint2 InPixelPos)`
- L660-704 _function_ `FLumenMaterialData InternalReadMaterialData_GBuffer(const FGBufferData GBufferData, const float DeviceZ, float2 ScreenUV)` — GBuffer material internal read function
- L706-711 _function_ `FLumenMaterialData InternalReadMaterialData_GBuffer(uint2 InPixelPos)`
- L713-717 _function_ `FLumenMaterialData InternalReadMaterialData_GBuffer(float2 InUV)`
- L720-731 _function_ `FLumenMaterialData ReadMaterialData(uint2 InPixelPos, bool bAllowStochaticMaterial=true)` — Read material data
- L733-741 _function_ `FLumenMaterialData ReadMaterialDataFromSceneTextures(uint2 InPixelPos, float2 InBufferUV)`
- L743-754 _function_ `FLumenMaterialData ReadMaterialData(uint2 InPixelPos, float2 InBufferUV, bool bAllowStochaticMaterial=true)`
- L756-767 _function_ `FLumenMaterialData ReadMaterialData(FLumenMaterialCoord InCoord, float MaxRoughnessToTraceSmoothReflection, bool bAllowStochaticMaterial=true)`
- L771-774 _function_ `bool IsValid(FLumenMaterialData In)` — Helper functions. Derive data from FLumenMaterialData
- L776-779 _function_ `bool IsHair(FLumenMaterialData In)`
- L781-784 _function_ `bool HasBackfaceDiffuse(FLumenMaterialData In)`
- L786-793 _function_ `bool IsClearCoat(FLumenMaterialData In)`
- L795-798 _function_ `bool IsSingleLayerWater(FLumenMaterialData In)`
- L800-803 _function_ `bool IsFrontLayerTranslucency(FLumenMaterialData In)`
- L805-808 _function_ `bool bIsUnlit(FLumenMaterialData In)`
- L810-813 _function_ `bool HasAnisotropy(FLumenMaterialData In)`
- L815-818 _function_ `bool ComputeIndirectLighting(FLumenMaterialData In)`
- L821-824 _function_ `bool HasHemisphericalVisibility(FLumenMaterialData In)` — Return true if the material has a hemispherical domain
- L827-830 _function_ `bool HasSphericalVisibility(FLumenMaterialData In)` — Return true if the material has a spherical domain (vs. hemispherical domain)
- L832-839 _function_ `bool HasBentNormal(FLumenMaterialData In)`
- L841-844 _function_ `bool HasDefaultShading(FLumenMaterialData In)`
- L846-849 _function_ `bool HasComplexShading(FLumenMaterialData In)`
- L851-854 _function_ `bool ShouldComputeIndirectLighting(FLumenMaterialData In)`
- L856-883 _function_ `float3x3 GetTangentBasis(FLumenMaterialData In)`
- L885-903 _function_ `float3 GetClearCoatBottomNormal(FLumenMaterialData In)`
- L909-927 _function_ `FBxDFSample SampleSubstrateBxDF(const uint TermMask, FLumenMaterialData InMaterial, float3 V, float4 E)` _[#if SUBSTRATE_GBUFFER_FORMAT==1]_
- L930-936 _function_ `FBxDFSample SampleSimpleBxDF(const uint TermMask, FLumenMaterialData InMaterial, float3 V, float4 E)`
- L938-952 _function_ `FBxDFSample SampleBxDF(const uint TermMask, FLumenMaterialData InMaterial, float3 V, float4 E)`

### `Shaders/Private/Lumen/LumenMeshSDFCulling.usf` (Private)

- lines: 631; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../DistanceFieldLightingShared.ush`, L5 `../HybridIndirectLighting.ush`, L6 `LumenCardCommon.ush`, L7 `../MeshDistanceFieldCommon.ush`, L8 `../HZB.ush`

#### Macros (#define, 10)

- L17 `#define THREADGROUP_SIZE 1` _[#if !defined(THREADGROUP_SIZE)]_
- L20 `#define CULL_MESH_TYPE_SDF 0`
- L21 `#define CULL_MESH_TYPE_HEIGHTFIELD 1`
- L24 `#define CULL_MESH_TYPE CULL_MESH_TYPE_SDF` _[#if !defined(CULL_MESH_TYPE)]_
- L189 `#define USE_FRUSTUM_CULLING 1` _[#if COMPUTESHADER]_
- L341 `#define CULLED_MESH_SDF_DATA_STRIDE 1`
- L342 `#define CULLED_OBJECT_TO_COMPACT_STRIDE 2`
- L457 `#define CULL_TO_HZB 1` _[#if CULL_TO_FROXEL_GRID]_
- L485 `#define INTERSECT_FRUSTUM_WITH_VIEW_AABB 1`
- L496 `#define INTERSECT_FROXEL_WITH_SDF CULL_MESH_SDF`

#### Entry points (7)

- L79-102 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void CombineObjectIndexBuffersCS( uint3 DispatchThreadId : SV_DispatchThreadID )` — stage: **compute** — C++: `FCombineObjectIndexBuffersCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenMeshSDFCulling.cpp:150) _[#if COMPUTESHADER]_
- L114-179 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void CullHeightfieldObjectsForViewCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID )` — stage: **compute** — C++: `FCullHeightfieldObjectsForViewCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenMeshSDFCulling.cpp:470) _[#if COMPUTESHADER]_
- L181-269 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void CullMeshSDFObjectsForViewCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FCullMeshSDFObjectsForViewCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenMeshSDFCulling.cpp:120) _[#if COMPUTESHADER]_
- L281-329 _entry_ `void MeshSDFObjectCullVS( float4 InPosition : ATTRIBUTE0, uint IndexInIndexBuffer : SV_InstanceID, out FObjectCullVertexOutput Output, out float4 OutPosition : SV_POSITION )` — stage: **vertex (from C++ binding)** — C++: `FMeshSDFObjectCullVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenMeshSDFCulling.cpp:180)
- L382-538 _entry_ `void MeshSDFObjectCullPS( FObjectCullVertexOutput Input, in float4 SVPos : SV_POSITION)` — stage: **pixel (from C++ binding)** — C++: `FMeshSDFObjectCullPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenMeshSDFCulling.cpp:241)
- L543-583 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void CompactCulledObjectsCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FCompactCulledObjectsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenMeshSDFCulling.cpp:294)
- L595-630 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void ComputeCulledObjectsStartOffsetCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FComputeCulledObjectsStartOffsetCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenMeshSDFCulling.cpp:333)

#### Structs / classes (2)

- L27-31 _struct_ **`FObjectData`** `struct FObjectData`
  - L29 _member_ `uint Index;`
  - L30 _member_ `uint Type;`
- L272-276 _struct_ **`FObjectCullVertexOutput`** `struct FObjectCullVertexOutput`
  - L274 _member_ `nointerpolation float4 PositionAndRadius : TEXCOORD0;`
  - L275 _member_ `nointerpolation uint ObjectIndex : TEXCOORD1;`

#### Global resources (textures / buffers / samplers) (26)

- L63 _resource_ `RWBuffer<uint> RWObjectIndexBuffer;`
- L72 _resource_ `Buffer<uint> MeshSDFIndexBuffer;` _[#if COMPUTESHADER]_
- L73 _resource_ `Buffer<uint> HeightfieldIndexBuffer;` _[#if COMPUTESHADER]_
- L74 _resource_ `Buffer<uint> NumCulledMeshSDFObjects;` _[#if COMPUTESHADER]_
- L75 _resource_ `Buffer<uint> NumCulledHeightfieldObjects;` _[#if COMPUTESHADER]_
- L77 _resource_ `RWBuffer<uint> RWCombinedObjectIndexBuffer;` _[#if COMPUTESHADER]_
- L109 _resource_ `RWBuffer<uint> RWNumCulledObjects;` _[#if COMPUTESHADER]_
- L110 _resource_ `RWBuffer<uint> RWCulledObjectIndexBuffer;` _[#if COMPUTESHADER]_
- L279 _resource_ `Buffer<uint> ObjectIndexBuffer;`
- L331 _resource_ `RWBuffer<uint> RWNumGridCulledMeshSDFObjects;`
- L332 _resource_ `RWBuffer<uint> RWGridCulledMeshSDFObjectIndicesArray;`
- L333 _resource_ `RWBuffer<uint> RWNumGridCulledHeightfieldObjects;`
- L334 _resource_ `RWBuffer<uint> RWGridCulledHeightfieldObjectIndicesArray;`
- L335 _resource_ `RWBuffer<uint> RWNumCulledObjectsToCompact;`
- L336 _resource_ `RWBuffer<uint> RWCulledObjectsToCompactArray;`
- L339 _resource_ `Buffer<uint> GridCulledMeshSDFObjectStartOffsetArray;` — @todo - put in header for tracing
- L340 _resource_ `Buffer<uint> GridCulledHeightfieldObjectStartOffsetArray;`
- L540 _resource_ `Buffer<uint> NumCulledObjectsToCompact;`
- L541 _resource_ `Buffer<uint> CulledObjectsToCompactArray;`
- L586 _resource_ `Buffer<uint> NumGridCulledMeshSDFObjects;`
- L587 _resource_ `Buffer<uint> NumGridCulledHeightfieldObjects;`
- L589 _resource_ `RWBuffer<uint> RWGridCulledMeshSDFObjectStartOffsetArray;`
- L590 _resource_ `RWBuffer<uint> RWCulledMeshSDFObjectAllocator;`
- L591 _resource_ `RWBuffer<uint> RWGridCulledHeightfieldObjectStartOffsetArray;`
- L592 _resource_ `RWBuffer<uint> RWCulledHeightfieldObjectAllocator;`
- L593 _resource_ `RWBuffer<uint> RWCompactCulledObjectsIndirectArguments;`

#### Global parameters (uniforms) (13)

- L10 _parameter_ `uint ObjectBoundingGeometryIndexCount;`
- L11 _parameter_ `float CardTraceEndDistanceFromCamera;`
- L12 _parameter_ `float MaxMeshSDFInfluenceRadius;`
- L13 _parameter_ `float MeshSDFRadiusThreshold;`
- L14 _parameter_ `uint NumCullGridCells;`
- L108 _parameter_ `uint MaxNumObjects;` _[#if COMPUTESHADER]_
- L112 _parameter_ `uint bShouldCull;` _[#if COMPUTESHADER]_
- L278 _parameter_ `float ConservativeRadiusScale;`
- L343 _parameter_ `float3 CardGridZParams;`
- L344 _parameter_ `uint3 CullGridSize;`
- L345 _parameter_ `uint CardGridPixelSizeShift;`
- L378 _parameter_ `uint MaxNumberOfCulledObjects;`
- L380 _parameter_ `float HZBMipLevel;`

#### groupshared (6)

- L58 _groupshared_ `groupshared uint NumGroupObjects;` _[#if COMPUTESHADER]_
- L59 _groupshared_ `groupshared uint GroupBaseIndex;` _[#if COMPUTESHADER]_
- L60 _groupshared_ `groupshared uint GroupObjectIndices[THREADGROUP_SIZE];` _[#if COMPUTESHADER]_
- L104 _groupshared_ `groupshared uint GSNumCulledObjects;` _[#if COMPUTESHADER]_
- L105 _groupshared_ `groupshared uint GSCulledObjectIndex[THREADGROUP_SIZE];` _[#if COMPUTESHADER]_
- L106 _groupshared_ `groupshared uint GSGlobalWriteBaseIndex;` _[#if COMPUTESHADER]_

#### Functions (7)

- L33-39 _function_ `FObjectData CreateObjectData(uint ObjectIndex, uint ObjectType)`
- L41-47 _function_ `uint PackObjectData(FObjectData ObjectData)`
- L49-55 _function_ `FObjectData UnpackObjectData(uint PackedData)`
- L65-68 _function_ `float LengthSq(float3 X)`
- L347-352 _function_ `uint ComputeFroxelGridZ(float SceneDepth)`
- L354-364 _function_ `float ComputeDepthFromZSlice(float ZSlice)`
- L366-376 _function_ `float3 ComputeCellWorldPosition(uint3 GridCoordinate, float3 CellOffset)`

### `Shaders/Private/Lumen/LumenPosition.ush` (Private)

- lines: 107; parse: all-branches
- L7 #pragma `once`

#### Functions (9)

- L9-14 _function_ `float3 GetWorldPositionFromScreenUV(float2 ScreenUV, float SceneDepth)`
- L16-20 _function_ `float3 GetTranslatedWorldPositionFromScreenUV(float2 ScreenUV, float SceneDepth)`
- L22-28 _function_ `float3 GetPrevTranslatedWorldPosition(float2 HistoryScreenPosition, float HistorySceneDepth)`
- L30-33 _function_ `float3 GetPrevTranslatedWorldPosition(float3 HistoryScreenPosition)`
- L36-60 _function_ `float3 GetHistoryScreenPosition(float2 ScreenPosition, float2 ScreenUV, float DeviceZ)` — This version ignores TAA jitter, use when sampling a history texture
- L62-85 _function_ `float3 GetHistoryScreenPosition(float2 ScreenPosition, float DeviceZ, float ReprojectDeviceZ, float4 EncodedVelocity)`
- L88-93 _function_ `float3 GetHistoryScreenPositionIncludingTAAJitter(float2 ScreenPosition, float2 ScreenUV, float DeviceZ)` — This version accounts for TAA jitter, use when comparing positions like calculating world space velocity
- L95-100 _function_ `float3 ComputeHairNormalForPositionBias(float2 ScreenUV, float SceneDepth, float3 HairN)`
- L103-106 _function_ `float ComputeHairNoV(float3 HairN, float3 V)` — HairN and V are unit vectors

### `Shaders/Private/Lumen/LumenRadianceCache.usf` (Private)

- lines: 1521; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../MonteCarlo.ush`, L5 `../FastMath.ush`, L6 `../SHCommon.ush`, L7 `../DeferredShadingCommon.ush`, L8 `LumenCardCommon.ush`, L9 `LumenTracingCommon.ush`, L10 `LumenSoftwareRayTracing.ush`, L11 `LumenIrradianceFieldInterpolation.ush`, L12 `LumenRadianceCacheMarkCommon.ush`, L13 `LumenRadianceCacheTracingCommon.ush`, L14 `LumenScreenProbeCommon.ush`, L15 `LumenScreenProbeImportanceSamplingShared.ush`, L16 `LumenRadianceCacheUpdate.ush`, L17 `LumenMaterial.ush`, L18 `LumenFloatQuantization.ush`

#### Macros (#define, 12)

- L21 `#define THREADGROUP_SIZE 1` _[#if !defined(THREADGROUP_SIZE)]_
- L67 `#define NUM_RADIANCE_PROBE_PDF_COEFFICIENTS (NUM_PDF_SH_COEFFICIENTS + 1)`
- L388 `#define DEBUG_UNIFORM_TRACES 0` _[#if defined(GenerateUniformProbeTraceTilesCS)]_
- L636 `#define VISUALIZE_BRDF_PDF_SPHERICAL_HARMONIC 0` _[#if defined(GenerateAdaptiveProbeTraceTilesCS)]_
- L695 `#define SORT_TILES_THREADGROUP_SIZE 1` _[#if !defined(SORT_TILES_THREADGROUP_SIZE)]_
- L698 `#define NUM_DIRECTION_BINS_2D 8`
- L699 `#define NUM_DIRECTION_BINS_1D (NUM_DIRECTION_BINS_2D * NUM_DIRECTION_BINS_2D)`
- L846 `#define JITTER_TRACE_DIRECTION 0` _[#if defined(TraceFromProbesCS)]_
- L883 `#define DEBUG_VISUALIZE_SAMPLING_RESOLUTION 0` _[#if defined(TraceFromProbesCS)]_
- L1136 `#define DOWNSAMPLED_RADIANCE_SIZE 8` _[#if defined(CalculateProbeIrradianceCS)]_
- L1159 `#define DOWNSAMPLE_TO_SHARED_MEMORY 1` _[#if defined(CalculateProbeIrradianceCS)]_
- L1275 `#define FILTER_PROBE_OCCLUSION 0` _[#if defined(PrepareProbeOcclusionCS)]_

#### Entry points (15)

- L26-33 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, THREADGROUP_SIZE)] void ClearProbeIndirectionCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FClearProbeIndirectionCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenRadianceCache.cpp:367) _[#if defined(ClearProbeIndirectionCS)]_
- L49-62 _entry_ `[numthreads(1, 1, 1)] void MarkRadianceProbesUsedByVisualizeCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FMarkRadianceProbesUsedByVisualizeCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenRadianceCache.cpp:272) _[#if defined(MarkRadianceProbesUsedByVisualizeCS)]_
- L87-133 _entry_ `[numthreads(1, 1, 1)] void SetupProbeIndirectArgsCS()` — stage: **compute** — C++: `FSetupProbeIndirectArgsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenRadianceCache.cpp:674) _[#if defined(SetupProbeIndirectArgsCS)]_
- L145-282 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void ComputeProbeWorldOffsetsCS( uint3 GroupId : SV_GroupID, uint GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FComputeProbeWorldOffsetsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenRadianceCache.cpp:715) _[#if defined(ComputeProbeWorldOffsetsCS)]_
- L292-300 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void ClearProbePDFs(uint DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FClearProbePDFs` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenRadianceCache.cpp:748) _[#if defined(ClearProbePDFs)]_
- L306-364 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void ScatterScreenProbeBRDFToRadianceProbesCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FScatterScreenProbeBRDFToRadianceProbesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenRadianceCache.cpp:783) _[#if defined(ScatterScreenProbeBRDFToRadianceProbesCS)]_
- L376-427 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void GenerateUniformProbeTraceTilesCS( uint DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FGenerateUniformProbeTraceTilesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenRadianceCache.cpp:822) — Note: should match GetProbeTraceCost as closely as possible _[#if defined(GenerateUniformProbeTraceTilesCS)]_
- L548-653 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void GenerateAdaptiveProbeTraceTilesCS( uint3 GroupId : SV_GroupID, uint2 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FGenerateAdaptiveProbeTraceTilesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenRadianceCache.cpp:871) — Note: should match GetProbeTraceCost as closely as possible _[#if defined(GenerateAdaptiveProbeTraceTilesCS)]_
- L666-690 _entry_ `[numthreads(1, 1, 1)] void SetupTraceFromProbesCS()` — stage: **compute** — C++: `FSetupTraceFromProbesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenRadianceCache.cpp:906) _[#if defined(SetupTraceFromProbesCS)]_
- L709-775 _entry_ `[numthreads(SORT_TILES_THREADGROUP_SIZE, 1, 1)] void SortProbeTraceTilesCS( uint GroupId : SV_GroupID, uint GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FSortProbeTraceTilesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenRadianceCache.cpp:942) _[#if defined(SortProbeTraceTilesCS)]_
- L821-983 _entry_ `[numthreads(RADIANCE_CACHE_TRACE_TILE_SIZE_2D, RADIANCE_CACHE_TRACE_TILE_SIZE_2D, 1)] void TraceFromProbesCS( uint3 GroupId : SV_GroupID, uint2 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FRadianceCacheTraceFromProbesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenRadianceCache.cpp:1011) _[#if defined(TraceFromProbesCS)]_
- L1003-1123 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void FilterProbeRadianceWithGatherCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FFilterProbeRadianceWithGatherCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenRadianceCache.cpp:1062) _[#if defined(FilterProbeRadianceWithGatherCS)]_
- L1139-1231 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void CalculateProbeIrradianceCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FCalculateProbeIrradianceCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenRadianceCache.cpp:1100) _[#if defined(CalculateProbeIrradianceCS)]_
- L1247-1388 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void PrepareProbeOcclusionCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FPrepareProbeOcclusionCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenRadianceCache.cpp:1141) _[#if defined(PrepareProbeOcclusionCS)]_
- L1415-1517 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void FixupBordersAndGenerateMipsCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FFixupBordersAndGenerateMipsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenRadianceCache.cpp:1188) _[#if defined(FixupBordersAndGenerateMipsCS)]_

#### Global resources (textures / buffers / samplers) (49)

- L37 _resource_ `RWBuffer<float4> RWProbeWorldOffset;`
- L40 _resource_ `RWBuffer<int> RWProbeFreeListAllocator;`
- L41 _resource_ `RWBuffer<uint> RWProbeFreeList;`
- L70 _resource_ `RWBuffer<uint> RWProbeAllocator;`
- L71 _resource_ `RWBuffer<uint> RWClearProbePDFsIndirectArgs;`
- L72 _resource_ `RWBuffer<uint> RWGenerateProbeTraceTilesIndirectArgs;`
- L73 _resource_ `RWBuffer<uint> RWGenerateUniformProbeTraceTilesIndirectArgs;`
- L74 _resource_ `RWBuffer<uint> RWProbeTraceTileAllocator;`
- L75 _resource_ `RWBuffer<uint> RWFilterProbesIndirectArgs;`
- L76 _resource_ `RWBuffer<uint> RWPrepareProbeOcclusionIndirectArgs;`
- L77 _resource_ `RWBuffer<uint> RWFixupProbeBordersIndirectArgs;`
- L78 _resource_ `Buffer<uint> ProbeTraceAllocator;`
- L139 _resource_ `Buffer<float4> ProbeTraceData;` _[#if defined(ComputeProbeWorldOffsetsCS)]_
- L286 _resource_ `RWBuffer<int> RWRadianceProbeSH_PDF;`
- L290 _resource_ `Buffer<float4> ProbeTraceData;` _[#if defined(ClearProbePDFs)]_
- L368 _resource_ `RWBuffer<uint2> RWProbeTraceTileData;`
- L372 _resource_ `Buffer<float4> ProbeTraceData;` _[#if defined(GenerateUniformProbeTraceTilesCS)]_
- L444 _resource_ `Buffer<int> RadianceProbeSH_PDF;` _[#if defined(GenerateAdaptiveProbeTraceTilesCS)]_
- L447 _resource_ `RWTexture2D<float> RWDebugBRDFProbabilityDensityFunction;` _[#if defined(GenerateAdaptiveProbeTraceTilesCS)]_
- L545 _resource_ `Buffer<float4> ProbeTraceData;` _[#if defined(GenerateAdaptiveProbeTraceTilesCS)]_
- L659 _resource_ `Buffer<uint> ProbeTraceTileAllocator;` _[#if defined(SetupTraceFromProbesCS)]_
- L660 _resource_ `RWBuffer<uint> RWTraceProbesIndirectArgs;` _[#if defined(SetupTraceFromProbesCS)]_
- L661 _resource_ `RWBuffer<uint> RWSortProbeTraceTilesIndirectArgs;` _[#if defined(SetupTraceFromProbesCS)]_
- L662 _resource_ `RWBuffer<uint> RWRadianceCacheHardwareRayTracingIndirectArgs;` _[#if defined(SetupTraceFromProbesCS)]_
- L663 _resource_ `RWBuffer<uint> RWHardwareRayTracingRayAllocatorBuffer;` _[#if defined(SetupTraceFromProbesCS)]_
- L703 _resource_ `Buffer<uint> ProbeTraceTileAllocator;` _[#if defined(SortProbeTraceTilesCS)]_
- L704 _resource_ `Buffer<uint2> ProbeTraceTileData;` _[#if defined(SortProbeTraceTilesCS)]_
- L807 _resource_ `Buffer<float4> ProbeTraceData;` _[#if defined(TraceFromProbesCS)]_
- L808 _resource_ `Buffer<uint2> ProbeTraceTileData;` _[#if defined(TraceFromProbesCS)]_
- L809 _resource_ `Buffer<uint> ProbeTraceTileAllocator;` _[#if defined(TraceFromProbesCS)]_
- L811 _resource_ `RWTexture2D<float3> RWRadianceProbeAtlasTexture;` _[#if defined(TraceFromProbesCS)]_
- L813 _resource_ `RWTexture2D<float> RWSkyVisibilityProbeAtlasTexture;` _[#if defined(TraceFromProbesCS) && RADIANCE_CACHE_SKY_VISIBILITY]_
- L815 _resource_ `RWTexture2D<uint> RWDepthProbeAtlasTexture;` _[#if defined(TraceFromProbesCS)]_
- L987 _resource_ `Texture2D<float3> RadianceProbeAtlasTexture;`
- L988 _resource_ `Texture2D<float> SkyVisibilityProbeAtlasTexture;`
- L989 _resource_ `Texture2D<uint> DepthProbeAtlasTexture;`
- L993 _resource_ `RWTexture2D<float3> RWRadianceProbeAtlasTexture;` _[#if defined(FilterProbeRadianceWithGatherCS)]_
- L995 _resource_ `RWTexture2D<float> RWSkyVisibilityProbeAtlasTexture;` _[#if defined(FilterProbeRadianceWithGatherCS) && RADIANCE_CACHE_SKY_VISIBILITY]_
- L997 _resource_ `Buffer<float4> ProbeTraceData;` _[#if defined(FilterProbeRadianceWithGatherCS)]_
- L1129 _resource_ `RWTexture2D<float3> RWFinalIrradianceAtlas;` _[#if defined(CalculateProbeIrradianceCS)]_
- L1130 _resource_ `Buffer<float4> ProbeTraceData;` _[#if defined(CalculateProbeIrradianceCS)]_
- L1237 _resource_ `RWTexture2D<float2> RWProbeOcclusionAtlas;` _[#if defined(PrepareProbeOcclusionCS)]_
- L1238 _resource_ `RWBuffer<uint> RWProbeValid;` _[#if defined(PrepareProbeOcclusionCS)]_
- L1239 _resource_ `Buffer<float4> ProbeTraceData;` _[#if defined(PrepareProbeOcclusionCS)]_
- L1394 _resource_ `RWTexture2D<float3> RWFinalRadianceAtlasMip0;` _[#if defined(FixupBordersAndGenerateMipsCS)]_
- L1395 _resource_ `RWTexture2D<float3> RWFinalRadianceAtlasMip1;` _[#if defined(FixupBordersAndGenerateMipsCS)]_
- L1396 _resource_ `RWTexture2D<float3> RWFinalRadianceAtlasMip2;` _[#if defined(FixupBordersAndGenerateMipsCS)]_
- L1398 _resource_ `RWTexture2D<float> RWFinalSkyVisibilityAtlasMip0;` _[#if defined(FixupBordersAndGenerateMipsCS) && RADIANCE_CACHE_SKY_VISIBILITY]_
- L1400 _resource_ `Buffer<float4> ProbeTraceData;` _[#if defined(FixupBordersAndGenerateMipsCS)]_

#### Global parameters (uniforms) (26)

- L42 _parameter_ `uint MaxNumProbes;`
- L44 _parameter_ `float MinTraceDistance;`
- L45 _parameter_ `float MaxTraceDistance;`
- L79 _parameter_ `uint ClearProbePDFGroupSize;`
- L80 _parameter_ `uint TraceFromProbesGroupSizeXY;`
- L81 _parameter_ `uint FilterProbesGroupSizeXY;`
- L82 _parameter_ `uint GenerateUniformProbeTraceTilesGroupSize;`
- L83 _parameter_ `uint MaxProbesToTrace;`
- L373 _parameter_ `uint ForcedUniformLevel;` _[#if defined(GenerateUniformProbeTraceTilesCS)]_
- L445 _parameter_ `float SupersampleTileBRDFThreshold;` _[#if defined(GenerateAdaptiveProbeTraceTilesCS)]_
- L448 _parameter_ `uint DebugProbeBRDFOctahedronResolution;` _[#if defined(GenerateAdaptiveProbeTraceTilesCS)]_
- L664 _parameter_ `uint SortTraceTilesGroupSize;` _[#if defined(SetupTraceFromProbesCS)]_
- L779 _parameter_ `float StepFactor;`
- L780 _parameter_ `float MinSampleRadius;`
- L781 _parameter_ `float MaxMeshSDFTraceDistance;`
- L782 _parameter_ `float CachedLightingPreExposure;`
- L998 _parameter_ `float SpatialFilterMaxRadianceHitAngle;` _[#if defined(FilterProbeRadianceWithGatherCS)]_
- L1000 _parameter_ `uint TempProbeAtlasResolutionModuloMask;` _[#if defined(FilterProbeRadianceWithGatherCS)]_
- L1001 _parameter_ `uint TempProbeAtlasResolutionDivideShift;` _[#if defined(FilterProbeRadianceWithGatherCS)]_
- L1132 _parameter_ `uint bUseTempProbeAtlas;` _[#if defined(CalculateProbeIrradianceCS)]_
- L1133 _parameter_ `uint TempProbeAtlasResolutionModuloMask;` _[#if defined(CalculateProbeIrradianceCS)]_
- L1134 _parameter_ `uint TempProbeAtlasResolutionDivideShift;` _[#if defined(CalculateProbeIrradianceCS)]_
- L1240 _parameter_ `float OcclusionKernelCosineExponent;` _[#if defined(PrepareProbeOcclusionCS)]_
- L1411 _parameter_ `uint TempProbeAtlasResolutionModuloMask;` _[#if defined(FixupBordersAndGenerateMipsCS)]_
- L1412 _parameter_ `uint TempProbeAtlasResolutionDivideShift;` _[#if defined(FixupBordersAndGenerateMipsCS)]_
- L1413 _parameter_ `uint bUseTempProbeAtlas;` _[#if defined(FixupBordersAndGenerateMipsCS)]_

#### groupshared (18)

- L141 _groupshared_ `groupshared float4 SharedBestOffset[THREADGROUP_SIZE];` _[#if defined(ComputeProbeWorldOffsetsCS)]_
- L142 _groupshared_ `groupshared float4 SharedBestOffset2[THREADGROUP_SIZE];` _[#if defined(ComputeProbeWorldOffsetsCS)]_
- L143 _groupshared_ `groupshared uint4 SharedIdealProbeOffset;` _[#if defined(ComputeProbeWorldOffsetsCS)]_
- L450 _groupshared_ `groupshared uint SharedNumPendingTraceTiles;` _[#if defined(GenerateAdaptiveProbeTraceTilesCS)]_
- L451 _groupshared_ `groupshared uint2 PendingTraceTileList[THREADGROUP_SIZE * THREADGROUP_SIZE * 4];` _[#if defined(GenerateAdaptiveProbeTraceTilesCS)]_
- L453 _groupshared_ `groupshared uint SharedNumCompletedTraceTiles;` _[#if defined(GenerateAdaptiveProbeTraceTilesCS)]_
- L454 _groupshared_ `groupshared uint2 CompletedTraceTileList[THREADGROUP_SIZE * THREADGROUP_SIZE * 4];` _[#if defined(GenerateAdaptiveProbeTraceTilesCS)]_
- L456 _groupshared_ `groupshared uint GlobalTraceOffset;` _[#if defined(GenerateAdaptiveProbeTraceTilesCS)]_
- L706 _groupshared_ `groupshared uint SharedNumTraceTileBins[NUM_DIRECTION_BINS_1D];` _[#if defined(SortProbeTraceTilesCS)]_
- L707 _groupshared_ `groupshared uint SharedTraceTileBinOffset[NUM_DIRECTION_BINS_1D];` _[#if defined(SortProbeTraceTilesCS)]_
- L817 _groupshared_ `groupshared float3 SharedTraceRadiance[RADIANCE_CACHE_TRACE_TILE_SIZE_2D][RADIANCE_CACHE_TRACE_TILE_SIZE_2D];` _[#if defined(TraceFromProbesCS)]_
- L818 _groupshared_ `groupshared float SharedTraceSkyVisibility[RADIANCE_CACHE_TRACE_TILE_SIZE_2D][RADIANCE_CACHE_TRACE_TILE_SIZE_2D];` _[#if defined(TraceFromProbesCS)]_
- L819 _groupshared_ `groupshared float SharedTraceHitDistance[RADIANCE_CACHE_TRACE_TILE_SIZE_2D][RADIANCE_CACHE_TRACE_TILE_SIZE_2D];` _[#if defined(TraceFromProbesCS)]_
- L1137 _groupshared_ `groupshared float3 SharedDownsampledProbeRadiance[DOWNSAMPLED_RADIANCE_SIZE][DOWNSAMPLED_RADIANCE_SIZE];` _[#if defined(CalculateProbeIrradianceCS)]_
- L1243 _groupshared_ `groupshared uint SharedNumBackfaces;` _[#if defined(PrepareProbeOcclusionCS) && PROBE_OCCLUSION_HWRT]_
- L1244 _groupshared_ `groupshared uint SharedClosestFrontfaceDistance;` _[#if defined(PrepareProbeOcclusionCS) && PROBE_OCCLUSION_HWRT]_
- L1403 _groupshared_ `groupshared float3 SharedLightingMip0[THREADGROUP_SIZE][THREADGROUP_SIZE];` _[#if defined(FixupBordersAndGenerateMipsCS) && GENERATE_MIPS]_
- L1404 _groupshared_ `groupshared float3 SharedLightingMip1[THREADGROUP_SIZE / 2][THREADGROUP_SIZE / 2];` _[#if defined(FixupBordersAndGenerateMipsCS) && GENERATE_MIPS]_

#### Functions (5)

- L433-442 _function_ `bool ShouldRefineTraceTile(uint2 TraceTileCoord, uint NumTraceTilesXY, float LevelPDFThreshold, FThreeBandSHVector BRDF)` _[#if defined(GenerateAdaptiveProbeTraceTilesCS)]_
- L458-482 _function_ `FThreeBandSHVector GetBRDF_PDF(uint ProbeIndex)` _[#if defined(GenerateAdaptiveProbeTraceTilesCS)]_
- L484-520 _function_ `void SubdivideTraceTileTreeOneStep( uint ThreadIndex, uint BaseNumTraceTilesXY, uint Level, uint NumLevels, uint ProbeTraceIndex, FThreeBandSHVector BRDF, inout uint PendingTraceListStartIndex)` _[#if defined(GenerateAdaptiveProbeTraceTilesCS)]_
- L522-543 _function_ `void SubdivideTraceTileTree( uint ThreadIndex, uint BaseTraceTileResolution, uint NumLevels, uint ProbeTraceIndex, FThreeBandSHVector BRDF)` _[#if defined(GenerateAdaptiveProbeTraceTilesCS)]_
- L784-803 _function_ `FConeTraceResult TraceForProbeTexel(FConeTraceInput TraceInput)`

### `Shaders/Private/Lumen/LumenRadianceCacheCommon.ush` (Private)

- lines: 69; parse: all-branches
- includes: L9 `LumenRadianceCacheInterpolation.ush`
- L7 #pragma `once`

#### Functions (2)

- L11-51 _function_ `FRadianceCacheCoverage GetRadianceCacheCoverageWithUncertainCoverage(float3 TranslatedRayOrigin, float3 RayDirection, float ClipmapDitherRandom)`
- L53-69 _function_ `FRadianceCacheCoverage GetRadianceCacheCoverageWithClipmapBias(float3 TranslatedRayOrigin, float3 RayDirection, uint ClipmapBias, float ClipmapDitherRandom)`

### `Shaders/Private/Lumen/LumenRadianceCacheDebug.usf` (Private)

- lines: 104; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../ShaderPrint.ush`, L5 `LumenRadianceCacheUpdate.ush`

#### Entry points (1)

- L21-104 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void RadianceCacheUpdateStatsCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FRadianceCacheUpdateStatsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenRadianceCache.cpp:629) — Print out various stats for debugging radiance cache probe updates

#### Global resources (textures / buffers / samplers) (9)

- L8 _resource_ `StructuredBuffer<uint> PriorityHistogram;`
- L9 _resource_ `StructuredBuffer<uint> MaxUpdateBucket;`
- L10 _resource_ `StructuredBuffer<uint> MaxTracesFromMaxUpdateBucket;`
- L11 _resource_ `StructuredBuffer<uint> ProbesToUpdateTraceCost;`
- L12 _resource_ `StructuredBuffer<uint> MinNewProbeTraceCost;`
- L13 _resource_ `Buffer<uint> ProbeTraceAllocator;`
- L14 _resource_ `Buffer<uint> ProbeTraceTileAllocator;`
- L15 _resource_ `Buffer<uint> ProbeFreeListAllocator;`
- L16 _resource_ `Buffer<uint> ProbeAllocator;`

#### Global parameters (uniforms) (1)

- L7 _parameter_ `uint MaxNumProbes;`

### `Shaders/Private/Lumen/LumenRadianceCacheHardwareRayTracing.usf` (Private)

- lines: 713; parse: all-branches
- includes: L3 `/Engine/Shared/RayTracingTypes.h`, L4 `../Common.ush`, L5 `../MonteCarlo.ush`, L6 `../MortonCode.ush`, L7 `../SceneTextureParameters.ush`, L8 `../RayTracing/RayGenUtils.ush`, L9 `LumenRadianceCacheCommon.ush`, L10 `LumenRadianceCacheTracingCommon.ush`, L11 `LumenCardCommon.ush`, L12 `LumenCardTile.ush`, L13 `LumenTracingCommon.ush`, L14 `LumenFloatQuantization.ush`, L182 `LumenHardwareRayTracingCommon.ush` [LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]

#### Macros (#define, 5)

- L17 `#define TRACE_TILE_ATLAS_STRITE_IN_TILES 512`
- L19 `#define RAY_TRACING_PASS_DEFAULT 0`
- L20 `#define RAY_TRACING_PASS_FAR_FIELD 1`
- L21 `#define RAY_TRACING_PASS_HIT_LIGHTING 2`
- L311 `#define DEBUG_VISUALIZE_SAMPLING_RESOLUTION 0` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_

#### Entry points (5)

- L63-83 _entry_ `[numthreads(1, 1, 1)] void LumenRadianceCacheHardwareRayTracingIndirectArgsCS()` — stage: **compute** — C++: `FLumenRadianceCacheHardwareRayTracingIndirectArgsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenRadianceCacheHardwareRayTracing.cpp:232) _[#if defined(LumenRadianceCacheHardwareRayTracingIndirectArgsCS)]_
- L423-435 _entry_ `[numthreads(INLINE_RAY_TRACING_THREAD_GROUP_SIZE_X, INLINE_RAY_TRACING_THREAD_GROUP_SIZE_Y, 1)] void LumenRadianceCacheHardwareRayTracingCS( uint3 GroupId : SV_GroupID, uint GroupIndex : SV_GroupIndex )` — stage: **compute** — C++: `FLumenRadianceCacheHardwareRayTracingCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenRadianceCacheHardwareRayTracing.cpp:202) _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING && LUMEN_HARDWARE_INLINE_RAYTRACING && defined(LumenRadianceCacheHardwareRayTracingCS)]_
- L441-448 _entry_ `RAY_TRACING_ENTRY_RAYGEN(LumenRadianceCacheHardwareRayTracingRGS)` — stage: **raygeneration** — C++: `FLumenRadianceCacheHardwareRayTracingRGS` SF_RayGen via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenRadianceCacheHardwareRayTracing.cpp:203) _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING && !(LUMEN_HARDWARE_INLINE_RAYTRACING) && defined(LumenRadianceCacheHardwareRayTracingRGS)]_
- L476-558 _entry_ `[numthreads(RADIANCE_CACHE_TRACE_TILE_SIZE_2D, RADIANCE_CACHE_TRACE_TILE_SIZE_2D, 1)] void RadianceCacheCompactTracesCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FRadianceCacheCompactTracesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenRadianceCacheHardwareRayTracing.cpp:323) — Compact all unfinished traces for the subsequent far field pass. _[#if defined(RadianceCacheCompactTracesCS)]_
- L577-711 _entry_ `[numthreads(RADIANCE_CACHE_TRACE_TILE_SIZE_2D, RADIANCE_CACHE_TRACE_TILE_SIZE_2D, 1)] void SplatRadianceCacheIntoAtlasCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID )` — stage: **compute** — C++: `FSplatRadianceCacheIntoAtlasCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenRadianceCacheHardwareRayTracing.cpp:294) _[#if defined(SplatRadianceCacheIntoAtlasCS)]_

#### Structs / classes (1)

- L116-134 _struct_ **`FRadianceCache`** `struct FRadianceCache`
  - L118 _member_ `uint2 TraceTileCoord;`
  - L119 _member_ `uint TraceTileLevel;`
  - L120 _member_ `uint ProbeTraceIndex;`
  - L122 _member_ `float3 ProbeTranslatedWorldCenter;`
  - L123 _member_ `uint ClipmapIndex;`
  - L124 _member_ `uint ProbeIndex;`
  - L126 _member_ `uint ProbeResolution;`
  - L127 _member_ `float ProbeTMin;`
  - L128 _member_ `uint ProbeAtlasResolutionModuloMask;`
  - L129 _member_ `uint ProbeAtlasResolutionDivideShift;`
  - L131 _member_ `bool bFarField;`
  - L132 _member_ `bool bSkyVisibility;`
  - L133 _member_ `bool bSkylightLeaking;`

#### Global resources (textures / buffers / samplers) (39)

- L49 _resource_ `Buffer<uint> CompactedTraceTexelAllocator_0;`
- L50 _resource_ `Buffer<uint> CompactedTraceTexelData_0;`
- L53 _resource_ `Buffer<uint> CompactedTraceTexelAllocator_1;` _[#if RADIANCE_CACHE_BATCH_SIZE > 1]_
- L54 _resource_ `Buffer<uint> CompactedTraceTexelData_1;` _[#if RADIANCE_CACHE_BATCH_SIZE > 1]_
- L57 _resource_ `RWBuffer<uint> RWHardwareRayTracingIndirectArgs;`
- L58 _resource_ `RWBuffer<uint> RWResolveIndirectArgs;`
- L86 _resource_ `Buffer<float4> RadianceCache_0_ProbeTraceData;`
- L87 _resource_ `Buffer<float4> RadianceCache_0_ProbeWorldOffset;`
- L88 _resource_ `Buffer<uint2> RadianceCache_0_ProbeTraceTileData;`
- L89 _resource_ `Buffer<uint> RadianceCache_0_ProbeTraceTileAllocator;`
- L90 _resource_ `Buffer<uint> RadianceCache_0_CompactedTraceTexelAllocator;`
- L91 _resource_ `Buffer<uint> RadianceCache_0_CompactedTraceTexelData;`
- L101 _resource_ `Buffer<float4> RadianceCache_1_ProbeTraceData;` _[#if RADIANCE_CACHE_BATCH_SIZE > 1]_
- L102 _resource_ `Buffer<float4> RadianceCache_1_ProbeWorldOffset;` _[#if RADIANCE_CACHE_BATCH_SIZE > 1]_
- L103 _resource_ `Buffer<uint2> RadianceCache_1_ProbeTraceTileData;` _[#if RADIANCE_CACHE_BATCH_SIZE > 1]_
- L104 _resource_ `Buffer<uint> RadianceCache_1_ProbeTraceTileAllocator;` _[#if RADIANCE_CACHE_BATCH_SIZE > 1]_
- L105 _resource_ `Buffer<uint> RadianceCache_1_CompactedTraceTexelAllocator;` _[#if RADIANCE_CACHE_BATCH_SIZE > 1]_
- L106 _resource_ `Buffer<uint> RadianceCache_1_CompactedTraceTexelData;` _[#if RADIANCE_CACHE_BATCH_SIZE > 1]_
- L184 _resource_ `RaytracingAccelerationStructure TLAS;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L185 _resource_ `RaytracingAccelerationStructure FarFieldTLAS;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L188 _resource_ `StructuredBuffer<FHitGroupRootConstants> HitGroupData;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING && LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L189 _resource_ `StructuredBuffer<FRayTracingSceneMetadataRecord> RayTracingSceneMetadata;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING && LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L190 _resource_ `RWStructuredBuffer<uint> RWInstanceHitCountBuffer;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING && LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L207 _resource_ `RWTexture2D<float3> RWTraceRadianceTexture;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L209 _resource_ `RWTexture2D<float3> RWTraceSkyVisibilityTexture;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING && RADIANCE_CACHE_SKY_VISIBILITY]_
- L211 _resource_ `RWTexture2D<uint> RWTraceHitTexture;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L455 _resource_ `Texture2D<float3> TraceRadianceTexture;`
- L456 _resource_ `Texture2D<float> TraceSkyVisibilityTexture;`
- L457 _resource_ `Texture2D<uint> TraceHitTexture;`
- L461 _resource_ `RWBuffer<uint> RWCompactedTraceTexelAllocator_0;` _[#if defined(RadianceCacheCompactTracesCS)]_
- L462 _resource_ `RWBuffer<uint> RWCompactedTraceTexelData_0;` _[#if defined(RadianceCacheCompactTracesCS)]_
- L465 _resource_ `RWBuffer<uint> RWCompactedTraceTexelAllocator_1;` _[#if defined(RadianceCacheCompactTracesCS) && RADIANCE_CACHE_BATCH_SIZE > 1]_
- L466 _resource_ `RWBuffer<uint> RWCompactedTraceTexelData_1;` _[#if defined(RadianceCacheCompactTracesCS) && RADIANCE_CACHE_BATCH_SIZE > 1]_
- L563 _resource_ `RWTexture2D<float3> RWRadianceProbeAtlasTexture_0;` _[#if defined(SplatRadianceCacheIntoAtlasCS)]_
- L565 _resource_ `RWTexture2D<float> RWSkyVisibilityProbeAtlasTexture_0;` _[#if defined(SplatRadianceCacheIntoAtlasCS) && RADIANCE_CACHE_SKY_VISIBILITY_0]_
- L567 _resource_ `RWTexture2D<uint> RWDepthProbeAtlasTexture_0;` _[#if defined(SplatRadianceCacheIntoAtlasCS)]_
- L570 _resource_ `RWTexture2D<float3> RWRadianceProbeAtlasTexture_1;` _[#if defined(SplatRadianceCacheIntoAtlasCS) && RADIANCE_CACHE_BATCH_SIZE > 1]_
- L572 _resource_ `RWTexture2D<float> RWSkyVisibilityProbeAtlasTexture_1;` _[#if defined(SplatRadianceCacheIntoAtlasCS) && RADIANCE_CACHE_BATCH_SIZE > 1 && RADIANCE_CACHE_SKY_VISIBILITY_1]_
- L574 _resource_ `RWTexture2D<uint> RWDepthProbeAtlasTexture_1;` _[#if defined(SplatRadianceCacheIntoAtlasCS) && RADIANCE_CACHE_BATCH_SIZE > 1]_

#### Global parameters (uniforms) (32)

- L23 _parameter_ `float MinTraceDistance;`
- L24 _parameter_ `float MaxTraceDistance;`
- L25 _parameter_ `float CachedLightingPreExposure;`
- L59 _parameter_ `uint2 OutputThreadGroupSize;`
- L60 _parameter_ `uint TempAtlasNumTraceTiles;`
- L92 _parameter_ `uint RadianceCache_0_RadianceProbeResolution;`
- L93 _parameter_ `uint RadianceCache_0_ProbeAtlasResolutionModuloMask;`
- L94 _parameter_ `uint RadianceCache_0_ProbeAtlasResolutionDivideShift;`
- L95 _parameter_ `float4 RadianceCache_0_RadianceProbeSettings[RADIANCE_PROBE_MAX_CLIPMAPS];`
- L96 _parameter_ `uint RadianceCache_0_FarField;`
- L97 _parameter_ `uint RadianceCache_0_SkyVisibility;`
- L98 _parameter_ `uint RadianceCache_0_SkylightLeaking;`
- L107 _parameter_ `uint RadianceCache_1_RadianceProbeResolution;` _[#if RADIANCE_CACHE_BATCH_SIZE > 1]_
- L108 _parameter_ `uint RadianceCache_1_ProbeAtlasResolutionModuloMask;` _[#if RADIANCE_CACHE_BATCH_SIZE > 1]_
- L109 _parameter_ `uint RadianceCache_1_ProbeAtlasResolutionDivideShift;` _[#if RADIANCE_CACHE_BATCH_SIZE > 1]_
- L110 _parameter_ `float4 RadianceCache_1_RadianceProbeSettings[RADIANCE_PROBE_MAX_CLIPMAPS];` _[#if RADIANCE_CACHE_BATCH_SIZE > 1]_
- L111 _parameter_ `uint RadianceCache_1_FarField;` _[#if RADIANCE_CACHE_BATCH_SIZE > 1]_
- L112 _parameter_ `uint RadianceCache_1_SkyVisibility;` _[#if RADIANCE_CACHE_BATCH_SIZE > 1]_
- L113 _parameter_ `uint RadianceCache_1_SkylightLeaking;` _[#if RADIANCE_CACHE_BATCH_SIZE > 1]_
- L193 _parameter_ `uint HitLightingForceOpaque;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L194 _parameter_ `uint HitLightingShadowMode;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L195 _parameter_ `uint HitLightingShadowTranslucencyMode;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L196 _parameter_ `uint HitLightingDirectLighting;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L197 _parameter_ `uint HitLightingSkylight;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L198 _parameter_ `float NearFieldSceneRadius;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L199 _parameter_ `float NearFieldMaxTraceDistance;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L200 _parameter_ `float FarFieldBias;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L201 _parameter_ `float FarFieldMaxTraceDistance;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L202 _parameter_ `float PullbackBias;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L203 _parameter_ `uint MaxTraversalIterations;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L204 _parameter_ `uint MeshSectionVisibilityTest;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L205 _parameter_ `uint SkylightLeaking;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_

#### groupshared (3)

- L469 _groupshared_ `groupshared uint SharedTraceTexelAllocator;` _[#if defined(RadianceCacheCompactTracesCS)]_
- L470 _groupshared_ `groupshared uint SharedGlobalTraceTexelStartOffset;` _[#if defined(RadianceCacheCompactTracesCS)]_
- L471 _groupshared_ `groupshared uint SharedTraceTexels[RADIANCE_CACHE_TRACE_TILE_SIZE_2D * RADIANCE_CACHE_TRACE_TILE_SIZE_2D];` _[#if defined(RadianceCacheCompactTracesCS)]_

#### Functions (6)

- L28-32 _function_ `uint2 GetTraceTileAtlasCoord(uint TraceTileIndex, uint2 CoordInTraceTile)` — Index into temporary compacted atlas of probe traces
- L34-40 _function_ `uint EncodeRadianceCacheTraceTexel(uint TraceTileIndex, uint2 TraceTexelCoord)`
- L42-47 _function_ `void DecodeRadianceCacheTraceTexel(uint Encoded, inout uint TraceTileIndex, inout uint2 TraceTexelCoord)`
- L136-178 _function_ `FRadianceCache LoadRadianceCache(uint RadianceCacheIndex, uint LocalTraceTileIndex)`
- L213-327 _function_ `void TraceRadianceCacheProbeTexel( uint RadianceCacheIndex, uint LocalTraceTileIndex, uint GlobalTraceTileIndex, uint2 TexelCoord, float TraceHitDistance)` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L330-418 _function_ `void LumenRadianceCacheHardwareRayTracingCommon(uint GroupId, uint GroupThreadId)` — RADIANCE_CACHE_TRACE_TILE_SIZE_1D thread groups _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_

### `Shaders/Private/Lumen/LumenRadianceCacheInterpolation.ush` (Private)

- lines: 520; parse: all-branches
- includes: L5 `../MonteCarlo.ush`, L6 `../ReflectionEnvironmentShared.ush`

#### Macros (#define, 31)

- L8 `#define RADIANCE_PROBE_MAX_CLIPMAPS 6`
- L9 `#define INVALID_PROBE_INDEX 0xFFFFFFFF`
- L11 `#define MAX_ADAPTIVE_PROBES 2`
- L14 `#define RADIANCE_CACHE_PARAMETERS_IN_UB 1` _[#if IS_MATERIAL_SHADER]_
- L16 `#define RADIANCE_CACHE_PARAMETERS_IN_UB 0` _[#if !(IS_MATERIAL_SHADER)]_
- L20 `#define RADIANCE_CACHE_DEPTH_TEST_SPHERE_PARALLAX 0` _[#if !defined(RADIANCE_CACHE_DEPTH_TEST_SPHERE_PARALLAX)]_
- L25 `#define RadianceProbeIndirectionTexture RadianceCacheInterpolation.RadianceProbeIndirectionTexture` _[#if RADIANCE_CACHE_PARAMETERS_IN_UB]_
- L26 `#define RadianceCacheFinalRadianceAtlas RadianceCacheInterpolation.RadianceCacheFinalRadianceAtlas` _[#if RADIANCE_CACHE_PARAMETERS_IN_UB]_
- L27 `#define RadianceCacheFinalSkyVisibilityAtlas RadianceCacheInterpolation.RadianceCacheFinalSkyVisibilityAtlas` _[#if RADIANCE_CACHE_PARAMETERS_IN_UB]_
- L28 `#define RadianceProbeSettings RadianceCacheInterpolation.RadianceProbeSettings` _[#if RADIANCE_CACHE_PARAMETERS_IN_UB]_
- L29 `#define ClipmapCornerTWSAndCellSize RadianceCacheInterpolation.ClipmapCornerTWSAndCellSize` _[#if RADIANCE_CACHE_PARAMETERS_IN_UB]_
- L30 `#define ReprojectionRadiusScale RadianceCacheInterpolation.ReprojectionRadiusScale` _[#if RADIANCE_CACHE_PARAMETERS_IN_UB]_
- L31 `#define InvClipmapFadeSize RadianceCacheInterpolation.InvClipmapFadeSize` _[#if RADIANCE_CACHE_PARAMETERS_IN_UB]_
- L32 `#define ProbeAtlasResolutionInProbes RadianceCacheInterpolation.ProbeAtlasResolutionInProbes` _[#if RADIANCE_CACHE_PARAMETERS_IN_UB]_
- L33 `#define InvProbeFinalRadianceAtlasResolution RadianceCacheInterpolation.InvProbeFinalRadianceAtlasResolution` _[#if RADIANCE_CACHE_PARAMETERS_IN_UB]_
- L35 `#define InvProbeDepthAtlasResolution RadianceCacheInterpolation.InvProbeDepthAtlasResolution` _[#if RADIANCE_CACHE_PARAMETERS_IN_UB]_
- L36 `#define NumRadianceProbeClipmaps RadianceCacheInterpolation.NumRadianceProbeClipmaps` _[#if RADIANCE_CACHE_PARAMETERS_IN_UB]_
- L37 `#define RadianceProbeClipmapResolution RadianceCacheInterpolation.RadianceProbeClipmapResolution` _[#if RADIANCE_CACHE_PARAMETERS_IN_UB]_
- L38 `#define RadianceProbeResolution RadianceCacheInterpolation.RadianceProbeResolution` _[#if RADIANCE_CACHE_PARAMETERS_IN_UB]_
- L39 `#define FinalProbeResolution RadianceCacheInterpolation.FinalProbeResolution` _[#if RADIANCE_CACHE_PARAMETERS_IN_UB]_
- L40 `#define FinalRadianceAtlasMaxMip RadianceCacheInterpolation.FinalRadianceAtlasMaxMip` _[#if RADIANCE_CACHE_PARAMETERS_IN_UB]_
- L41 `#define RadianceCacheOneOverCachedLightingPreExposure RadianceCacheInterpolation.RadianceCacheOneOverCachedLightingPreExposure` _[#if RADIANCE_CACHE_PARAMETERS_IN_UB]_
- L42 `#define ShowBlackRadianceCacheLighting RadianceCacheInterpolation.ShowBlackRadianceCacheLighting` _[#if RADIANCE_CACHE_PARAMETERS_IN_UB]_
- L43 `#define ProbeWorldOffset RadianceCacheInterpolation.ProbeWorldOffset` _[#if RADIANCE_CACHE_PARAMETERS_IN_UB]_
- L44 `#define RadianceCacheDepthAtlas RadianceCacheInterpolation.RadianceCacheDepthAtlas` _[#if RADIANCE_CACHE_PARAMETERS_IN_UB]_
- L45 `#define ProbeAtlasResolutionModuloMask RadianceCacheInterpolation.ProbeAtlasResolutionModuloMask` _[#if RADIANCE_CACHE_PARAMETERS_IN_UB]_
- L46 `#define ProbeAtlasResolutionDivideShift RadianceCacheInterpolation.ProbeAtlasResolutionDivideShift` _[#if RADIANCE_CACHE_PARAMETERS_IN_UB]_
- L254 `#define VISUALIZE_PROBE_DEPTH 0`
- L343 `#define SIMPLE_SPHERE_PARALLAX 1`
- L344 `#define TRACE_THROUGH_PROBE_DEPTHS_REFERENCE 0`
- L432 `#define DEBUG_VISUALIZE_INVALID_COVERAGE 0`
- L3 #pragma `once`

#### Structs / classes (4)

- L156-165 _struct_ **`FRadianceCacheCoverage`** `struct FRadianceCacheCoverage`
  - L158 _member_ `uint ClipmapIndex;`
  - L161 _member_ `float MinTraceDistanceBeforeInterpolation;` — The minimum distance that must be traced before interpolating from the Radiance Cache, to prevent leaking
  - L164 _member_ `bool bValid;` — Whether the Radiance Cache covers the queried position
- L196-202 _struct_ **`FProbeDepth`** `struct FProbeDepth`
  - L198 _member_ `float HitDistance;`
  - L199 _member_ `bool bHit;`
  - L200 _member_ `bool bFrontface;`
  - L201 _member_ `bool bTwoSided;`
- L237-243 _struct_ **`FRadianceCacheSample`** `struct FRadianceCacheSample`
  - L239 _member_ `float3 Radiance;`
  - L240 _member_ `float SkyVisibility;`
  - L241 _member_ `float TraceHitDistance;`
  - L242 _member_ `bool bBackface;`
- L295-300 _struct_ **`FProbeIndirectionDesc`** `struct FProbeIndirectionDesc`
  - L297 _member_ `uint ProbeIndex;`
  - L298 _member_ `uint NumAdaptiveProbes;`
  - L299 _member_ `bool bValid;`

#### Global resources (textures / buffers / samplers) (5)

- L50 _resource_ `Texture3D<uint> RadianceProbeIndirectionTexture;` _[#if !(RADIANCE_CACHE_PARAMETERS_IN_UB)]_
- L51 _resource_ `Texture2D<float3> RadianceCacheFinalRadianceAtlas;` _[#if !(RADIANCE_CACHE_PARAMETERS_IN_UB)]_
- L52 _resource_ `Texture2D<float> RadianceCacheFinalSkyVisibilityAtlas;` _[#if !(RADIANCE_CACHE_PARAMETERS_IN_UB)]_
- L53 _resource_ `Texture2D<uint> RadianceCacheDepthAtlas;` _[#if !(RADIANCE_CACHE_PARAMETERS_IN_UB)]_
- L54 _resource_ `Buffer<float4> ProbeWorldOffset;` _[#if !(RADIANCE_CACHE_PARAMETERS_IN_UB)]_

#### Global parameters (uniforms) (16)

- L56 _parameter_ `float4 RadianceProbeSettings[RADIANCE_PROBE_MAX_CLIPMAPS];` _[#if !(RADIANCE_CACHE_PARAMETERS_IN_UB)]_
- L57 _parameter_ `float4 ClipmapCornerTWSAndCellSize[RADIANCE_PROBE_MAX_CLIPMAPS];` _[#if !(RADIANCE_CACHE_PARAMETERS_IN_UB)]_
- L59 _parameter_ `float ReprojectionRadiusScale;` _[#if !(RADIANCE_CACHE_PARAMETERS_IN_UB)]_
- L60 _parameter_ `float InvClipmapFadeSize;` _[#if !(RADIANCE_CACHE_PARAMETERS_IN_UB)]_
- L62 _parameter_ `uint2 ProbeAtlasResolutionInProbes;` _[#if !(RADIANCE_CACHE_PARAMETERS_IN_UB)]_
- L63 _parameter_ `float2 InvProbeFinalRadianceAtlasResolution;` _[#if !(RADIANCE_CACHE_PARAMETERS_IN_UB)]_
- L64 _parameter_ `float2 InvProbeDepthAtlasResolution;` _[#if !(RADIANCE_CACHE_PARAMETERS_IN_UB)]_
- L66 _parameter_ `uint NumRadianceProbeClipmaps;` _[#if !(RADIANCE_CACHE_PARAMETERS_IN_UB)]_
- L67 _parameter_ `uint RadianceProbeClipmapResolution;` _[#if !(RADIANCE_CACHE_PARAMETERS_IN_UB)]_
- L69 _parameter_ `uint RadianceProbeResolution;` — Resolution of Octahedral layout during tracing _[#if !(RADIANCE_CACHE_PARAMETERS_IN_UB)]_
- L71 _parameter_ `uint FinalProbeResolution;` — Resolution of Octahedral layout during sampling _[#if !(RADIANCE_CACHE_PARAMETERS_IN_UB)]_
- L73 _parameter_ `uint FinalRadianceAtlasMaxMip;` _[#if !(RADIANCE_CACHE_PARAMETERS_IN_UB)]_
- L74 _parameter_ `float RadianceCacheOneOverCachedLightingPreExposure;` _[#if !(RADIANCE_CACHE_PARAMETERS_IN_UB)]_
- L75 _parameter_ `uint ShowBlackRadianceCacheLighting;` _[#if !(RADIANCE_CACHE_PARAMETERS_IN_UB)]_
- L77 _parameter_ `uint ProbeAtlasResolutionModuloMask;` _[#if !(RADIANCE_CACHE_PARAMETERS_IN_UB)]_
- L78 _parameter_ `uint ProbeAtlasResolutionDivideShift;` _[#if !(RADIANCE_CACHE_PARAMETERS_IN_UB)]_

#### Functions (26)

- L82-85 _function_ `float GetRadianceProbeTMin(uint ClipmapIndex)`
- L88-91 _function_ `float3 GetRadianceProbeClipmapCornerTWS(uint ClipmapIndex)` — The minimum coordinate of the clipmap, in translated world space
- L93-96 _function_ `float GetRadianceProbeClipmapCellSize(uint ClipmapIndex)`
- L98-104 _function_ `float3 GetRadianceProbeCoordFloat(float3 ProbeTranslatedWorldPosition, uint ClipmapIndex)`
- L106-110 _function_ `int3 GetRadianceProbeCoord(float3 ProbeTranslatedWorldPosition, uint ClipmapIndex)`
- L112-115 _function_ `int3 GetRadianceProbeBottomCornerCoord(float3 ProbeTranslatedWorldPosition, uint ClipmapIndex)`
- L117-124 _function_ `float3 GetProbeTranslatedWorldPositionNoOffset(uint3 ProbeCoord, uint ClipmapIndex)`
- L126-129 _function_ `float3 GetProbeTranslatedWorldPosition(uint3 ProbeCoord, uint ClipmapIndex, uint ProbeIndex)`
- L131-134 _function_ `bool IsValidRadianceCacheClipmap(uint FRadianceCacheCoverage)`
- L136-154 _function_ `uint GetRadianceProbeClipmap(float3 TranslatedWorldSpacePosition, float ClipmapDitherRandom)`
- L167-174 _function_ `FRadianceCacheCoverage InitRadianceCacheCoverage()`
- L179-194 _function_ `FRadianceCacheCoverage GetRadianceCacheCoverage(float3 TranslatedRayOrigin, float3 RayDirection, float ClipmapDitherRandom)` — Only positions that were marked during FMarkUsedRadianceCacheProbes can be queried, this version does not check if the position was marked correctly See UnmappedDebugColor for visualizing these errors GetRadianceCacheCoverageWithUncertainCoverage can be used for interpolating to positions with uncertain coverage
- L204-212 _function_ `FProbeDepth InitProbeDepth(float HitDistance, bool bHit, bool bFrontface, bool bTwoSided)`
- L215-225 _function_ `uint EncodeProbeDepth(FProbeDepth ProbeDepth)` — Encode in R16_UINT
- L227-235 _function_ `FProbeDepth DecodeProbeDepth(uint Encoded)`
- L245-293 _function_ `FRadianceCacheSample SampleRadianceCacheProbe(uint ProbeIndex, float3 WorldSpaceDirection, float MipLevel)`
- L302-309 _function_ `uint EncodeProbeIndirection(FProbeIndirectionDesc ProbeIndirectionDesc)`
- L311-318 _function_ `FProbeIndirectionDesc DecodeProbeIndirection(uint Encoded)`
- L320-324 _function_ `uint GetProbeIndexFromIndirectionTexture(uint3 ProbeCoord, uint ClipmapIndex)`
- L326-330 _function_ `FProbeIndirectionDesc GetProbeIndirection(uint3 ProbeCoord, uint ClipmapIndex)`
- L332-404 _function_ `FRadianceCacheSample SampleRadianceCacheProbeWithParallaxCorrection(uint3 ProbeCoord, uint ProbeClipmapIndex, float3 TranslatedWorldSpacePosition, float3 WorldSpaceDirection, float MipLevel)`
- L406-413 _function_ `FRadianceCacheSample LerpRadianceCacheSample(FRadianceCacheSample SampleA, FRadianceCacheSample SampleB, float Alpha)`
- L415-427 _function_ `FRadianceCacheSample RadianceCacheResolveSky(FRadianceCacheSample Sample, float3 WorldSpaceDirection)`
- L429-497 _function_ `FRadianceCacheSample SampleRadianceCacheInterpolated(FRadianceCacheCoverage Coverage, float3 TranslatedWorldSpacePosition, float3 WorldSpaceDirection, float ConeHalfAngle, float RandomScalarForStochasticInterpolation)`
- L499-513 _function_ `void SampleRadianceCacheAndApply(FRadianceCacheCoverage Coverage, float3 TranslatedWorldSpacePosition, float3 WorldSpaceDirection, float ConeHalfAngle, float RandomScalarForStochasticInterpolation, inout float3 Lighting, inout float Transparency, inout float TraceHitDistance)`
- L515-519 _function_ `void SampleRadianceCacheAndApply(FRadianceCacheCoverage Coverage, float3 TranslatedWorldSpacePosition, float3 WorldSpaceDirection, float ConeHalfAngle, float RandomScalarForStochasticInterpolation, inout float3 Lighting, inout float Transparency)`

### `Shaders/Private/Lumen/LumenRadianceCacheMarkCommon.ush` (Private)

- lines: 125; parse: all-branches

#### Macros (#define, 10)

- L9 `#define USED_PROBE_INDEX 0xFFFFFFFE`
- L16 `#define RADIANCE_PROBE_MAX_CLIPMAPS 6`
- L17 `#define INVALID_PROBE_INDEX 0xFFFFFFFF`
- L20 `#define GetRadianceProbeClipmapCornerTWSForMark(index) RadianceCacheMark.ClipmapCornerTWSAndCellSizeForMark[index].xyz` _[#if IS_MATERIAL_SHADER]_
- L21 `#define GetRadianceProbeClipmapCellSizeForMark(index) RadianceCacheMark.ClipmapCornerTWSAndCellSizeForMark[index].w` _[#if IS_MATERIAL_SHADER]_
- L23 `#define NumRadianceProbeClipmapsForMark RadianceCacheMark.NumRadianceProbeClipmapsForMark` _[#if IS_MATERIAL_SHADER]_
- L24 `#define RadianceProbeClipmapResolutionForMark RadianceCacheMark.RadianceProbeClipmapResolutionForMark` _[#if IS_MATERIAL_SHADER]_
- L25 `#define InvClipmapFadeSizeForMark RadianceCacheMark.InvClipmapFadeSizeForMark` _[#if IS_MATERIAL_SHADER]_
- L30 `#define GetRadianceProbeClipmapCornerTWSForMark(index) ClipmapCornerTWSAndCellSizeForMark[index].xyz` _[#if !(IS_MATERIAL_SHADER)]_
- L31 `#define GetRadianceProbeClipmapCellSizeForMark(index) ClipmapCornerTWSAndCellSizeForMark[index].w` _[#if !(IS_MATERIAL_SHADER)]_
- L7 #pragma `once`

#### Structs / classes (1)

- L40-45 _struct_ **`FRadianceProbeCoord`** `struct FRadianceProbeCoord`
  - L42 _member_ `uint3 ProbeMinCoord;`
  - L43 _member_ `uint3 ProbeMaxCoord;`
  - L44 _member_ `uint ClipmapIndex;`

#### Global resources (textures / buffers / samplers) (1)

- L12 _resource_ `RWTexture3D<uint> RWRadianceProbeIndirectionTexture;` _[#if !IS_MATERIAL_SHADER]_

#### Global parameters (uniforms) (4)

- L28 _parameter_ `float4 ClipmapCornerTWSAndCellSizeForMark[RADIANCE_PROBE_MAX_CLIPMAPS];` _[#if !(IS_MATERIAL_SHADER)]_
- L34 _parameter_ `uint NumRadianceProbeClipmapsForMark;` _[#if !(IS_MATERIAL_SHADER)]_
- L35 _parameter_ `uint RadianceProbeClipmapResolutionForMark;` _[#if !(IS_MATERIAL_SHADER)]_
- L36 _parameter_ `float InvClipmapFadeSizeForMark;` _[#if !(IS_MATERIAL_SHADER)]_

#### Functions (7)

- L47-50 _function_ `bool IsValidRadianceCacheClipmapForMark(uint InClipmapIndex)`
- L52-58 _function_ `float3 GetRadianceProbeCoordFloatForMark(float3 ProbeTranslatedWorldPosition, uint ClipmapIndex)`
- L60-89 _function_ `FRadianceProbeCoord GetRadianceProbeCoord(float3 ProbeTranslatedWorldPosition, float ClipmapDitherRandom)`
- L91-95 _function_ `uint GetRadianceProbeClipmapForMark(float3 ProbeTranslatedWorldPosition, float ClipmapDitherRandom)`
- L97-100 _function_ `uint GetRadianceProbeClipmapForMark(float3 ProbeTranslatedWorldPosition)`
- L102-109 _function_ `void MarkProbeIndirectionTextureCoord(int3 ProbeCoord, uint ClipmapIndex)`
- L111-124 _function_ `void MarkPositionUsedInIndirectionTexture(float3 ProbeTranslatedWorldPosition, uint ClipmapIndex)`

### `Shaders/Private/Lumen/LumenRadianceCacheTracingCommon.ush` (Private)

- lines: 64; parse: all-branches

#### Macros (#define, 3)

- L4 `#define RADIANCE_CACHE_TRACE_TILE_SIZE_2D 8`
- L5 `#define RADIANCE_CACHE_TRACE_TILE_SIZE_1D (RADIANCE_CACHE_TRACE_TILE_SIZE_2D * RADIANCE_CACHE_TRACE_TILE_SIZE_2D)`
- L6 `#define TRACE_TILE_GROUP_STRIDE 128`

#### Structs / classes (1)

- L8-14 _struct_ **`FProbeTraceData`** `struct FProbeTraceData`
  - L10 _member_ `float3 ProbeTranslatedWorldCenter;`
  - L11 _member_ `uint ClipmapIndex;`
  - L12 _member_ `uint ProbeIndex;`
  - L13 _member_ `bool bForceDownsample;`

#### Functions (6)

- L16-26 _function_ `float4 PackProbeTraceData(float3 ProbeTranslatedWorldPosition, uint ClipmapIndex, uint ProbeIndex, bool bForceDownsample)`
- L28-38 _function_ `FProbeTraceData GetProbeTraceDataNoOffset(float4 InProbeTraceData)`
- L40-43 _function_ `uint GetProbeIndexFromProbeTraceData(float4 InProbeTraceData)`
- L45-48 _function_ `uint2 PackTraceTileInfo(uint2 TraceTileCoord, uint Level, uint ProbeTraceIndex)`
- L50-56 _function_ `uint2 UnpackTraceTileInfo(uint2 TraceTileInfo)`
- L58-63 _function_ `void UnpackTraceTileInfo(uint2 TraceTileInfo, out uint2 TraceTileCoord, out uint Level, out uint ProbeTraceIndex)`

### `Shaders/Private/Lumen/LumenRadianceCacheUpdate.usf` (Private)

- lines: 533; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../ShaderPrint.ush`, L5 `LumenRadianceCacheCommon.ush`, L6 `LumenRadianceCacheMarkCommon.ush`, L7 `LumenRadianceCacheUpdate.ush`, L8 `LumenRadianceCacheTracingCommon.ush`

#### Entry points (6)

- L19-45 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void ClearProbeFreeListCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FClearProbeFreeList` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenRadianceCache.cpp:337) _[#if defined(ClearProbeFreeListCS)]_
- L76-165 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, THREADGROUP_SIZE)] void UpdateCacheForUsedProbesCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FUpdateCacheForUsedProbesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenRadianceCache.cpp:412) _[#if defined(UpdateCacheForUsedProbesCS)]_
- L194-217 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void ClearRadianceCacheUpdateResourcesCS( uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FClearRadianceCacheUpdateResourcesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenRadianceCache.cpp:447) — Batch clear all resources required for the subsequent radiance cache probe update pass _[#if defined(ClearRadianceCacheUpdateResourcesCS)]_
- L288-389 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, THREADGROUP_SIZE)] void AllocateUsedProbesCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FAllocateUsedProbesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenRadianceCache.cpp:499) — Allocate used probes and build their update priority histogram _[#if defined(AllocateUsedProbesCS)]_
- L398-427 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void SelectMaxPriorityBucketCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FSelectMaxPriorityBucketCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenRadianceCache.cpp:587) — Compute max bucket histogram to update and how many tiles should be updated in that last bucket _[#if defined(SelectMaxPriorityBucketCS)]_
- L502-528 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, THREADGROUP_SIZE)] void AllocateProbeTracesCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FAllocateProbeTracesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenRadianceCache.cpp:552) — Iterate again over all probes and update them based on the histogram priority max update bucket _[#if defined(AllocateProbeTracesCS)]_

#### Global resources (textures / buffers / samplers) (25)

- L11 _resource_ `RWBuffer<uint> RWProbeLastUsedFrame;`
- L12 _resource_ `RWBuffer<int> RWProbeFreeListAllocator;`
- L13 _resource_ `RWBuffer<uint> RWProbeFreeList;`
- L14 _resource_ `RWBuffer<float4> RWProbeWorldOffset;`
- L15 _resource_ `RWBuffer<uint> RWProbeInterpolationMisses;`
- L50 _resource_ `RWBuffer<uint> RWProbeAdaptiveIndices;`
- L54 _resource_ `Buffer<uint> ProbeAllocator;` _[#if defined(UpdateCacheForUsedProbesCS)]_
- L55 _resource_ `Texture3D<uint> LastFrameRadianceProbeIndirectionTexture;` _[#if defined(UpdateCacheForUsedProbesCS)]_
- L170 _resource_ `RWStructuredBuffer<uint> RWPriorityHistogram;`
- L171 _resource_ `StructuredBuffer<uint> PriorityHistogram;`
- L172 _resource_ `RWStructuredBuffer<uint> RWMaxUpdateBucket;`
- L173 _resource_ `StructuredBuffer<uint> MaxUpdateBucket;`
- L174 _resource_ `RWStructuredBuffer<uint> RWMaxTracesFromMaxUpdateBucket;`
- L175 _resource_ `StructuredBuffer<uint> MaxTracesFromMaxUpdateBucket;`
- L176 _resource_ `RWStructuredBuffer<uint> RWProbesToUpdateTraceCost;`
- L177 _resource_ `StructuredBuffer<uint> ProbesToUpdateTraceCost;`
- L178 _resource_ `RWStructuredBuffer<uint> RWMinNewProbeTraceCost;`
- L180 _resource_ `RWStructuredBuffer<uint> RWProbeLastTracedFrame;`
- L181 _resource_ `Buffer<uint> ProbeLastUsedFrame;`
- L183 _resource_ `RWBuffer<uint> RWProbeAllocator;`
- L184 _resource_ `Buffer<uint> ProbeFreeList;`
- L186 _resource_ `RWBuffer<uint> RWProbeTraceAllocator;`
- L187 _resource_ `RWBuffer<float4> RWProbeTraceData;`
- L268 _resource_ `Buffer<uint> LastFrameProbeInterpolationMisses;` _[#if defined(AllocateUsedProbesCS)]_
- L433 _resource_ `Buffer<uint> ProbeAdaptiveIndices;` _[#if defined(AllocateProbeTracesCS)]_

#### Global parameters (uniforms) (6)

- L10 _parameter_ `uint MaxNumProbes;`
- L49 _parameter_ `uint FrameNumber;`
- L56 _parameter_ `float4 LastFrameClipmapCornerTWSAndCellSize[RADIANCE_PROBE_MAX_CLIPMAPS];` _[#if defined(UpdateCacheForUsedProbesCS)]_
- L57 _parameter_ `uint NumFramesToKeepCachedProbes;` _[#if defined(UpdateCacheForUsedProbesCS)]_
- L169 _parameter_ `float FirstClipmapWorldExtentRcp;`
- L435 _parameter_ `uint MaxProbesToTrace;` _[#if defined(AllocateProbeTracesCS)]_

#### Functions (6)

- L59-67 _function_ `float3 GetLastFrameProbeTranslatedWorldPosition(uint3 LastFrameProbeCoord, uint ClipmapIndex)` _[#if defined(UpdateCacheForUsedProbesCS)]_
- L69-74 _function_ `void FreeProbeIndex(uint ProbeIndex)` _[#if defined(UpdateCacheForUsedProbesCS)]_
- L221-241 _function_ `uint GetPriorityBucketIndex(uint LastTracedFrameIndex, uint LastUsedFrameIndex, uint ClipmapIndex)`
- L245-266 _function_ `uint AllocateProbeIndex()` _[#if defined(AllocateUsedProbesCS)]_
- L270-283 _function_ `void UpdatePriorityHistogram(uint LastTracedFrameIndex, uint LastUsedFrameIndex, uint ClipmapIndex, uint3 ProbeCoord)` _[#if defined(AllocateUsedProbesCS)]_
- L437-497 _function_ `void AllocateProbeTraces(uint ProbeTraceCost, uint ProbeIndex, uint ClipmapIndex, uint3 ProbeCoord)` _[#if defined(AllocateProbeTracesCS)]_

### `Shaders/Private/Lumen/LumenRadianceCacheUpdate.ush` (Private)

- lines: 39; parse: all-branches

#### Macros (#define, 7)

- L3 `#define PROBE_FRAME_INDEX_NEVER_TRACED 0`
- L6 `#define PRIORITY_HISTOGRAM_SIZE 16`
- L7 `#define MAX_UPDATE_BUCKET_STRIDE 2`
- L8 `#define PROBES_TO_UPDATE_TRACE_COST_STRIDE 2`
- L10 `#define PROBE_TRACE_COST_DOWNSAMPLED 1`
- L11 `#define PROBE_TRACE_COST_NORMAL 4`
- L12 `#define PROBE_TRACE_COST_SUPERSAMPLED 16`

#### Global parameters (uniforms) (3)

- L14 _parameter_ `uint NumProbesToTraceBudget;`
- L15 _parameter_ `float DownsampleDistanceFromCameraSq;`
- L16 _parameter_ `float SupersampleDistanceFromCameraSq;`

#### Functions (2)

- L18-21 _function_ `uint GetProbeTraceCostBudget()`
- L24-39 _function_ `uint GetProbeTraceCost(float3 ProbeTranslatedWorldPosition)` — Note: should match GenerateProbeTraceTilesCS as closely as possible

### `Shaders/Private/Lumen/LumenReSTIRGather.usf` (Private)

- lines: 1651; parse: all-branches
- includes: L5 `/Engine/Shared/RayTracingTypes.h`, L6 `../Common.ush`, L12 `../DeferredShadingCommon.ush`, L13 `../BRDF.ush`, L14 `../MonteCarlo.ush`, L15 `../BlueNoise.ush`, L16 `../ShadingModelsSampling.ush`, L17 `../SHCommon.ush`, L18 `../SceneTextureParameters.ush`, L19 `../SphericalGaussian.ush`, L20 `../FastMath.ush`, L21 `../ClearCoatCommon.ush`, L22 `../TextureSampling.ush`, L23 `../MortonCode.ush`, L24 `LumenMaterial.ush`, L25 `LumenPosition.ush`, L26 `LumenCardCommon.ush`, L27 `LumenTracingCommon.ush`, L28 `LumenReflectionsCombine.ush`, L266 `LumenHardwareRayTracingCommon.ush` [LUMEN_HARDWARE_RAYTRACING]

#### Macros (#define, 18)

- L3 `#define USE_HAIR_COMPLEX_TRANSMITTANCE 1`
- L9 `#define PreIntegratedGF ReflectionStruct.PreIntegratedGF`
- L10 `#define PreIntegratedGFSampler GlobalBilinearClampedSampler`
- L31 `#define THREADGROUP_SIZE 1` _[#if !defined(THREADGROUP_SIZE)]_
- L52 `#define GENERAL_FRAME_INDEX (FixedJitterIndex >= 0 ? FixedJitterIndex : View.StateFrameIndex)`
- L53 `#define HISTORY_FRAME_INDEX (FixedJitterIndex >= 0 ? FixedJitterIndex : (View.StateFrameIndex - 1))`
- L638 `#define EXPAND_HISTORY_DISTANCE_THRESHOLD_FOR_JITTER 1` _[#if defined(TemporalResamplingCS)]_
- L708 `#define DEBUG_VISUALIZE_HISTORY_MISS 0` _[#if defined(TemporalResamplingCS)]_
- L831 `#define SPIRAL_PATTERN 1` _[#if defined(SpatialResamplingCS)]_
- L953 `#define PLANE_WEIGHTING 1`
- L988 `#define TONEMAP_WEIGHTING_ROUGH_SPECULAR 1`
- L1008 `#define JITTERED_BILINEAR_UPSAMPLE 0`
- L1009 `#define SPIRAL_PATTERN_UPSAMPLE 1`
- L1010 `#define PASSTHROUGH_UPSAMPLE 2`
- L1406 `#define ACCURATE_HISTORY_DISOCCLUSION 1` _[#if defined(TemporalAccumulationCS)]_
- L1425 `#define EXPAND_HISTORY_DISTANCE_THRESHOLD_FOR_JITTER 1` _[#if defined(TemporalAccumulationCS)]_
- L1488 `#define NEIGHBORHOOD_CLAMP 1` _[#if defined(TemporalAccumulationCS)]_
- L1531 `#define TONEMAP_WEIGHTING_BILATERAL 1`

#### Entry points (8)

- L274-380 _entry_ `RAY_TRACING_ENTRY_RAYGEN(LumenValidateReservoirsRGS)` — stage: **raygeneration** — C++: `FLumenValidateReservoirsRGS` SF_RayGen via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenReSTIRGather.cpp:345) _[#if LUMEN_HARDWARE_RAYTRACING]_
- L387-499 _entry_ `RAY_TRACING_ENTRY_RAYGEN(LumenInitialSamplingRGS)` — stage: **raygeneration** — C++: `FLumenInitialSamplingRGS` SF_RayGen via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenReSTIRGather.cpp:387) _[#if LUMEN_HARDWARE_RAYTRACING]_
- L508-536 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void ClearTemporalHistoryCS( uint2 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FClearTemporalHistoryCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenReSTIRGather.cpp:523) _[#if defined(ClearTemporalHistoryCS)]_
- L597-729 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void TemporalResamplingCS( uint2 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FTemporalResamplingCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenReSTIRGather.cpp:485) _[#if defined(TemporalResamplingCS)]_
- L798-916 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void SpatialResamplingCS( uint2 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FSpatialResamplingCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenReSTIRGather.cpp:561) _[#if defined(SpatialResamplingCS)]_
- L1022-1243 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void UpsampleAndIntegrateCS( uint2 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FUpsampleAndIntegrateCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenReSTIRGather.cpp:611) _[#if defined(UpsampleAndIntegrateCS)]_
- L1383-1528 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void TemporalAccumulationCS( uint2 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FTemporalAccumulationCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenReSTIRGather.cpp:673) _[#if defined(TemporalAccumulationCS)]_
- L1558-1649 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void BilateralFilterCS( uint2 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FBilateralFilterCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenReSTIRGather.cpp:714) _[#if defined(BilateralFilterCS)]_

#### Structs / classes (5)

- L91-98 _class_ **`FSample`** `class FSample` — A GI ray hit
  - L93 _member_ `float3 RayDirection;`
  - L94 _member_ `float PDF;`
  - L95 _member_ `float3 OutgoingRadiance;`
  - L96 _member_ `float TraceHitDistance;`
  - L97 _member_ `float3 TraceHitNormal;`
- L146-201 _class_ **`FReservoir`** `class FReservoir`
  - L149 _member_ `FSample Sample;` — The reservoir sample, which has been selected from the input stream with propability wNew / wSum
  - L152 _member_ `float wSum;` — Sum of all weights streamed through the reservoir
  - L155 _member_ `float M;` — Number of samples streamed through the reservoir
  - L158 _member_ `float W;` — RIS combined weights, used for calculating the final integral
  - L160 _method_ `void Initialize()`
  - L170 _method_ `bool Update(FSample NewSample, float wNew, float Noise)` — Update the reservoir with a new sample wNew must be TargetPDF / OriginalPDF Caller must update W after
  - L187 _method_ `bool Merge(FReservoir OtherReservoir, float OtherReservoirSamplePDF, float Noise)` — Merge this reservoir with another Caller must update W after
  - L195 _method_ `bool WillChangeSampleOnMerge(FReservoir OtherReservoir, float OtherReservoirSamplePDF, float Noise)`
- L919-923 _struct_ **`FScreenProbeSample`** `struct FScreenProbeSample`
  - L921 _member_ `uint2 AtlasCoord[4];`
  - L922 _member_ `float4 Weights;`
- L1315-1319 _struct_ **`Bilinear`** `struct Bilinear`
  - L1317 _member_ `float2 Origin;`
  - L1318 _member_ `float2 Weights;`
- L1350-1356 _struct_ **`FGatherUV`** `struct FGatherUV`
  - L1352 _member_ `float2 UV00;`
  - L1353 _member_ `float2 UV10;`
  - L1354 _member_ `float2 UV11;`
  - L1355 _member_ `float2 UV01;`

#### Global resources (textures / buffers / samplers) (42)

- L55 _resource_ `RWTexture2D<float4> RWReservoirRayDirection;`
- L56 _resource_ `RWTexture2D<float3> RWReservoirTraceRadiance;`
- L57 _resource_ `RWTexture2D<float> RWReservoirTraceHitDistance;`
- L58 _resource_ `RWTexture2D<UNORM float3> RWReservoirTraceHitNormal;`
- L59 _resource_ `RWTexture2D<float3> RWReservoirWeights;`
- L61 _resource_ `Texture2D<float4> ReservoirRayDirection;`
- L62 _resource_ `Texture2D<float3> ReservoirTraceRadiance;`
- L63 _resource_ `Texture2D<float> ReservoirTraceHitDistance;`
- L64 _resource_ `Texture2D<UNORM float3> ReservoirTraceHitNormal;`
- L65 _resource_ `Texture2D<float3> ReservoirWeights;`
- L250 _resource_ `RWTexture2D<float3> RWTemporalReservoirTraceRadiance;`
- L251 _resource_ `RWTexture2D<float3> RWTemporalReservoirWeights;`
- L253 _resource_ `Texture2D<float4> TemporalReservoirRayDirection;`
- L254 _resource_ `Texture2D<float> TemporalReservoirTraceHitDistance;`
- L255 _resource_ `Texture2D<UNORM float3> TemporalReservoirTraceHitNormal;`
- L261 _resource_ `Texture2D<float> DownsampledDepthHistory;`
- L262 _resource_ `Texture2D<UNORM float3> DownsampledNormalHistory;`
- L268 _resource_ `RaytracingAccelerationStructure TLAS;` _[#if LUMEN_HARDWARE_RAYTRACING]_
- L269 _resource_ `RaytracingAccelerationStructure FarFieldTLAS;` _[#if LUMEN_HARDWARE_RAYTRACING]_
- L382 _resource_ `RWTexture2D<float> RWDownsampledSceneDepth;` _[#if LUMEN_HARDWARE_RAYTRACING]_
- L383 _resource_ `RWTexture2D<UNORM float3> RWDownsampledWorldNormal;` _[#if LUMEN_HARDWARE_RAYTRACING]_
- L503 _resource_ `RWTexture2D<float4> RWTemporalReservoirRayDirection;`
- L504 _resource_ `RWTexture2D<float> RWTemporalReservoirTraceHitDistance;`
- L505 _resource_ `RWTexture2D<UNORM float3> RWTemporalReservoirTraceHitNormal;`
- L588 _resource_ `Texture2D<float3> TemporalReservoirTraceRadiance;`
- L589 _resource_ `Texture2D<float3> TemporalReservoirWeights;`
- L590 _resource_ `Texture2D<float> DownsampledSceneDepth;`
- L591 _resource_ `Texture2D<UNORM float3> DownsampledWorldNormal;`
- L1012 _resource_ `RWTexture2DArray<float3> RWDiffuseIndirect;`
- L1013 _resource_ `RWTexture2DArray<float3> RWRoughSpecularIndirect;`
- L1014 _resource_ `RWTexture2DArray<float> RWResolveVariance;`
- L1246 _resource_ `RWTexture2DArray<float4> RWNewHistoryDiffuseIndirect;`
- L1247 _resource_ `RWTexture2DArray<float3> RWNewHistoryRoughSpecularIndirect;`
- L1248 _resource_ `RWTexture2DArray<UNORM float> RWNumHistoryFramesAccumulated;`
- L1250 _resource_ `Texture2DArray<float3> DiffuseIndirect;`
- L1251 _resource_ `Texture2DArray<float3> RoughSpecularIndirect;`
- L1252 _resource_ `Texture2DArray<float> ResolveVariance;`
- L1253 _resource_ `Texture2D DiffuseIndirectHistory;`
- L1254 _resource_ `Texture2D RoughSpecularIndirectHistory;`
- L1255 _resource_ `Texture2D ResolveVarianceHistory;`
- L1256 _resource_ `Texture2D DiffuseIndirectDepthHistory;`
- L1257 _resource_ `Texture2D HistoryNumFramesAccumulated;`

#### Global parameters (uniforms) (27)

- L35 _parameter_ `uint ReservoirDownsampleFactor;` — Downsample factor from the viewport that reservoirs will be created (via tracing a ray) and resampled at
- L38 _parameter_ `uint2 ReservoirViewSize;` — Size of the reservoir view
- L41 _parameter_ `uint2 ReservoirBufferSize;` — Size of the reservoir buffer
- L44 _parameter_ `int FixedJitterIndex;` — When >= 0, specifies a fixed frame index that should be used to generate random numbers, for debugging
- L47 _parameter_ `float ResamplingDepthErrorThreshold;` — Depth threshold for temporal and spatial reservoir resampling
- L50 _parameter_ `float ResamplingNormalDotThreshold;` — Normal threshold for temporal and spatial reservoir resampling
- L257 _parameter_ `uint2 HistoryReservoirViewSize;`
- L258 _parameter_ `float4 HistoryScreenPositionScaleBias;`
- L259 _parameter_ `float PrevSceneColorPreExposureCorrection;`
- L270 _parameter_ `float MaxRayIntensity;` _[#if LUMEN_HARDWARE_RAYTRACING]_
- L271 _parameter_ `float MaxTraceDistance;` _[#if LUMEN_HARDWARE_RAYTRACING]_
- L272 _parameter_ `int ApplySkyLight;` _[#if LUMEN_HARDWARE_RAYTRACING]_
- L385 _parameter_ `float PullbackBias;` _[#if LUMEN_HARDWARE_RAYTRACING]_
- L593 _parameter_ `float4 HistoryUVMinMax;`
- L594 _parameter_ `float HistoryDistanceThreshold;`
- L792 _parameter_ `float SpatialResamplingKernelRadius;`
- L793 _parameter_ `uint NumSpatialSamples;`
- L794 _parameter_ `uint SpatialResamplingPassIndex;`
- L795 _parameter_ `float SpatialResamplingOcclusionScreenTraceDistance;`
- L1016 _parameter_ `float UpsampleKernelSize;`
- L1017 _parameter_ `uint UpsampleNumSamples;`
- L1259 _parameter_ `float MaxFramesAccumulated;`
- L1551 _parameter_ `float BilateralFilterSpatialKernelRadius;`
- L1552 _parameter_ `uint BilateralFilterNumSamples;`
- L1553 _parameter_ `float BilateralFilterDepthWeightScale;`
- L1554 _parameter_ `float BilateralFilterNormalAngleThresholdScale;`
- L1555 _parameter_ `float BilateralFilterStrongBlurVarianceThreshold;`

#### static const (3)

- L576-586 _static_const_ `static const int2 PixelNeighborOffsets[8] = { int2(-1, -1), int2(1, 1), int2(-1, 1), int2(1, -1), int2(0, -1), int2(0, 1), int2(-1, 0), int2(1, 0) };`
- L1019 _static_const_ `const static float DisocclusionVariance = 1.0f;`
- L1274-1284 _static_const_ `static const int2 kOffsets3x3[8] = { int2(-1, -1), int2( 0, -1), int2( 1, -1), int2(-1, 0), int2( 1, 0), int2(-1, 1), int2( 0, 1), int2( 1, 1), };`

#### Functions (27)

- L68-71 _function_ `uint2 GetReservoirTileJitter(uint TemporalIndex)` — Returns the jitter offset in the range [0, ReservoirDownsampleFactor - 1]
- L73-77 _function_ `uint2 GetScreenCoordFromReservoirCoord(uint2 ReservoirCoord, uint FrameIndex)`
- L79-82 _function_ `uint2 GetScreenCoordFromReservoirCoord(uint2 ReservoirCoord)`
- L84-88 _function_ `float2 GetScreenUVFromReservoirCoord(uint2 ReservoirCoord)`
- L100-114 _function_ `FSample LoadSample( uint2 Coord, Texture2D<float4> RayDirectionTexture, Texture2D<float3> TraceRadianceTexture, Texture2D<float> TraceHitDistanceTexture, Texture2D<UNORM float3> TraceHitNormalTexture)`
- L116-130 _function_ `FSample LoadSample( uint2 Coord, Texture2D<float4> RayDirectionTexture, RWTexture2D<float3> TraceRadianceTexture, Texture2D<float> TraceHitDistanceTexture, Texture2D<UNORM float3> TraceHitNormalTexture)`
- L132-144 _function_ `void StoreSample( FSample Sample, uint2 Coord, RWTexture2D<float4> RayDirectionTexture, RWTexture2D<float3> TraceRadianceTexture, RWTexture2D<float> TraceHitDistanceTexture, RWTexture2D<UNORM float3> TraceHitNormalTexture)`
- L203-218 _function_ `FReservoir LoadReservoir( uint2 Coord, Texture2D<float4> RayDirection, Texture2D<float3> TraceRadiance, Texture2D<float> TraceHitDistance, Texture2D<UNORM float3> TraceHitNormal, Texture2D<float3> ReservoirWeights)`
- L220-235 _function_ `FReservoir LoadReservoir( uint2 Coord, Texture2D<float4> RayDirection, RWTexture2D<float3> TraceRadiance, Texture2D<float> TraceHitDistance, Texture2D<UNORM float3> TraceHitNormal, RWTexture2D<float3> ReservoirWeights)`
- L237-248 _function_ `void StoreReservoir( FReservoir Reservoir, uint2 Coord, RWTexture2D<float4> RayDirection, RWTexture2D<float3> TraceRadiance, RWTexture2D<float> TraceHitDistance, RWTexture2D<UNORM float3> TraceHitNormal, RWTexture2D<float3> ReservoirWeights)`
- L541-574 _function_ `float CalculateJacobian(float3 ReceiverPosition, float3 NeighborReceiverPosition, const FSample NeighborSample)` — The Jacobian determinant of the transform from the neighbor sample to ourself transforms the neighbor's PDF to our own solid angle space Equation 11 in ReSTIR GI paper
- L733-790 _function_ `float ScreenShadowRayCast( float3 RayOriginTranslatedWorld, float3 RayDirection, float RayLength, int NumSteps, float StepOffset)` — Returns distance along ray that the first hit occurred, or negative on miss
- L925-986 _function_ `void CalculateUniformUpsampleInterpolationWeights( float2 ScreenCoord, float2 NoiseOffset, float3 TranslatedWorldPosition, float SceneDepth, float3 WorldNormal, out FScreenProbeSample ScreenProbeSample)`
- L990-997 _function_ `float3 TonemapLightingForRoughSpecular(float3 Lighting)`
- L999-1006 _function_ `float3 InverseTonemapLightingForRoughSpecular(float3 TonemappedLighting)`
- L1262-1265 _function_ `uint2 GetNeighborFlattenCoord(uint2 InScreenCoord, uint InClosureIndex)` — Return the 'flatten' SvPosition/ScreenCoord of particular closure/layer
- L1268-1272 _function_ `float2 GetPrevUV(const float2 InPrevScreenCoordUV, uint InClosureIndex)` — Return the previous frame 'flatten' UV coord of a particular closure/layer
- L1286-1313 _function_ `float3 ClampHistory( Texture2DArray<float3> LightingTexture, uint2 ScreenCoord, uint2 MinScreenCoord, uint2 MaxScreenCoord, float3 NewLighting, float3 HistoryLighting, uint InClosureIndex)`
- L1321-1327 _function_ `Bilinear GetBilinearFilter(float2 UV, float2 TextureSize)`
- L1329-1337 _function_ `float4 GetBilinearCustomWeights(Bilinear F, float4 CustomWeights)`
- L1339-1343 _function_ `float3 WeightedAverage(float3 V00, float3 V10, float3 V01, float3 V11, float4 Weights)`
- L1345-1348 _function_ `float WeightedAverage(float4 V, float4 Weights)`
- L1358-1366 _function_ `FGatherUV GetGatherUV(Bilinear In, float2 InTexelSize)`
- L1368-1375 _function_ `FLumenMaterialCoord GetLumenMaterialCoordForReSTIRGather(uint2 DispatchThreadId, uint2 GroupId, inout bool bIsValid, inout uint2 FlattenTileCoord)`
- L1377-1380 _function_ `FLumenMaterialCoord GetLumenMaterialCoordForReSTIRGather(uint2 DispatchThreadId, bool bIncludeTileOffset)`
- L1533-1540 _function_ `float3 TonemapLightingForBilateral(float3 Lighting)`
- L1542-1549 _function_ `float3 InverseTonemapLightingForBilateral(float3 TonemappedLighting)`

### `Shaders/Private/Lumen/LumenReflectionCommon.ush` (Private)

- lines: 343; parse: all-branches
- includes: L5 `../MonteCarlo.ush`, L6 `../BlueNoise.ush`, L7 `LumenPosition.ush`, L8 `LumenMaterial.ush`, L9 `LumenReflectionsCombine.ush`

#### Macros (#define, 4)

- L14 `#define REFLECTION_THREADGROUP_SIZE_2D 8`
- L15 `#define REFLECTION_THREADGROUP_SIZE_1D 64`
- L16 `#define DEBUG_VISUALIZE_TRACE_TYPES 0`
- L18 `#define FLOAT_32_MAX float(+3.402823466e+38f)`
- L3 #pragma `once`; L12 #pragma `message("UESHADERMETADATA_VERSION A2EBD51-AD20-4353-B91A-4EE5FF02A797")`

#### Structs / classes (4)

- L106-116 _struct_ **`FRayData`** `struct FRayData`
  - L108 _member_ `float3 Direction;`
  - L109 _member_ `float PDF;`
  - L110 _member_ `float ConeHalfAngle;`
  - L113 _member_ `float RadianceCacheMaxTraceDistance;` — Radiance cache max trace distance. Don't need to load this data if radiance cache isn't used.
  - L114 _member_ `bool bUseRadianceCache;`
  - L115 _member_ `bool bIsFirstPersonPixel;`
- L153-157 _struct_ **`FReflectionTileData`** `struct FReflectionTileData`
  - L155 _member_ `uint2 Coord;`
  - L156 _member_ `uint ClosureIndex;`
- L212-216 _struct_ **`FTraceMaterialId`** `struct FTraceMaterialId`
  - L214 _member_ `bool bNeedsHitLightingPass;`
  - L215 _member_ `uint MaterialId;`
- L251-256 _struct_ **`FReflectionTracingCoord`** `struct FReflectionTracingCoord`
  - L253 _member_ `uint2 Coord;`
  - L254 _member_ `uint3 CoordFlatten;`
  - L255 _member_ `uint ClosureIndex;`

#### Global resources (textures / buffers / samplers) (10)

- L33 _resource_ `Texture2DArray DownsampledDepth;` — Note: negative if invalid ray
- L34 _resource_ `Texture2DArray<float4> RayBuffer;`
- L36 _resource_ `Texture2DArray<uint> RayTraceDistance;` — The distance to trace each ray before interpolating from the Radiance Cache
- L38 _resource_ `Texture2DArray<float3> TraceRadiance;`
- L39 _resource_ `Texture2DArray<float> TraceHit;`
- L150 _resource_ `Buffer<uint> ReflectionClearTileData;`
- L151 _resource_ `Buffer<uint> ReflectionResolveTileData;`
- L190 _resource_ `Buffer<uint> ReflectionTracingTileData;`
- L209 _resource_ `Buffer<uint> CompactedTraceTexelAllocator;`
- L210 _resource_ `Buffer<uint> CompactedTraceTexelData;`

#### Global parameters (uniforms) (12)

- L20 _parameter_ `uint2 ReflectionTracingBufferSize;`
- L23 _parameter_ `uint2 ReflectionDownsampleFactorXY;` — Downsample factor from full res to tracing res
- L24 _parameter_ `float MaxRayIntensity;`
- L25 _parameter_ `float ReflectionSmoothBias;`
- L28 _parameter_ `uint ReflectionPass;` — 0: Opaque, 1: SingleLayerWater, 2: FrontLayerTranslucency
- L29 _parameter_ `uint UseJitter;`
- L30 _parameter_ `uint UseHighResSurface;`
- L41 _parameter_ `uint ReflectionsStateFrameIndex;`
- L42 _parameter_ `uint ReflectionsStateFrameIndexMod8;`
- L43 _parameter_ `uint ReflectionsRayDirectionFrameIndex;`
- L192 _parameter_ `uint2 ReflectionTracingViewMin;`
- L193 _parameter_ `uint2 ReflectionTracingViewSize;`

#### static const (1)

- L119 _static_const_ `const static float MinReflectionConeAngle = 0.00001f;` — Must be larger than FLOAT16_MIN

#### Functions (26)

- L48-74 _function_ `float2 GetScreenTileJitter(uint2 DownsampledScreenCoord)` — Returns sample jitter offset in the range [0, ReflectionDownsampleFactorXY - 1]
- L76-82 _function_ `float2 GetScreenUVFromReflectionTracingCoord(uint2 ReflectionTracingCoord)`
- L84-87 _function_ `float GetMaxHitDistance()`
- L89-93 _function_ `float EncodeRayDistance(float HitDistance, bool bHit)`
- L95-99 _function_ `float DecodeRayDistance(float Encoded, out bool bHit)`
- L101-104 _function_ `float DecodeProbeRayDistance(float Encoded)`
- L121-127 _function_ `uint PackRayTraceDistance(float RayTraceDistance, bool bUseRadianceCache)`
- L129-133 _function_ `void UnpackRayTraceDistance(uint PackedData, inout float RadianceCacheMaxTraceDistance, inout bool bUseRadianceCache)`
- L135-148 _function_ `FRayData GetRayData(uint3 TracingCoord)`
- L159-166 _function_ `uint PackTileData(FReflectionTileData In)`
- L168-174 _function_ `FReflectionTileData UnpackTileData(uint In)`
- L176-181 _function_ `uint2 GetReflectionClearScreenCoord(uint TileIndex, uint2 ThreadIndex, inout FReflectionTileData OutTileData)`
- L183-188 _function_ `uint2 GetReflectionResolveScreenCoord(uint TileIndex, uint2 ThreadIndex, inout FReflectionTileData OutTileData)`
- L195-200 _function_ `uint3 GetReflectionTracingScreenCoord(uint TileIndex, uint ThreadIndex, inout FReflectionTileData OutTileData)`
- L202-207 _function_ `uint2 GetReflectionTracingScreenCoordZOrder(uint TileIndex, uint ThreadIndex, inout FReflectionTileData OutTileData)`
- L218-223 _function_ `uint PackTraceMaterialId(bool bNeedsHitLightingPass, uint MaterialShaderIndex)`
- L225-231 _function_ `FTraceMaterialId UnpackTraceMaterialId(uint PackedMaterialId)`
- L233-246 _function_ `float ApplySmoothBias(float Roughness)`
- L258-265 _function_ `FReflectionTracingCoord GetReflectionTracingCoord(uint2 InReflectionTracingCoord, uint InClosureIndex)`
- L267-275 _function_ `uint EncodeTraceTexel(uint2 ReflectionTracingCoord, uint InClosureIndex)`
- L277-282 _function_ `FReflectionTracingCoord DecodeTraceTexel(uint TraceTexelData)`
- L284-299 _function_ `FLumenMaterialCoord InternalGetLumenMaterialCoord_Reflection(in uint2 SvPosition, FReflectionTileData InTileData, bool bForceClosureIndex, uint InForcedClosureIndex)`
- L301-304 _function_ `FLumenMaterialCoord GetLumenMaterialCoord_Reflection(in uint2 SvPosition, FReflectionTileData InTileData, uint InForcedClosureIndex)`
- L306-309 _function_ `FLumenMaterialCoord GetLumenMaterialCoord_Reflection(in uint2 SvPosition, FReflectionTileData InTileData)`
- L311-323 _function_ `FLumenMaterialData ApplySmoothBias(FLumenMaterialData In, bool bTopLayerRoughness)`
- L325-343 _function_ `bool NeedRayTracedReflections(float InRoughness, const FLumenMaterialData In)`

### `Shaders/Private/Lumen/LumenReflectionDenoiserClear.usf` (Private)

- lines: 50; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../SceneTextureParameters.ush`, L5 `LumenReflectionCommon.ush`, L6 `LumenReflectionDenoiserCommon.ush`

#### Entry points (1)

- L20-50 _entry_ `[numthreads(REFLECTION_THREADGROUP_SIZE_2D, REFLECTION_THREADGROUP_SIZE_2D, 1)] void LumenReflectionDenoiserClearCS( uint GroupId : SV_GroupID, uint2 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FLumenReflectionDenoiserClearCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenReflections.cpp:1077) — Clear tiles which won't be processed, so that temporal and spatial denoising passes don't pickup uninitialized values.

#### Global resources (textures / buffers / samplers) (5)

- L8 _resource_ `RWTexture2DArray<float3> RWResolvedSpecular;`
- L9 _resource_ `RWTexture2DArray<float4> RWSpecularAndSecondMoment;`
- L10 _resource_ `RWTexture2D<float4> RWFinalRadiance;`
- L11 _resource_ `RWTexture2D<float3> RWFinalThroughput;`
- L12 _resource_ `RWTexture2D<UNORM float2> RWBackgroundVisibility;`

#### Global parameters (uniforms) (2)

- L14 _parameter_ `uint bClearToSceneColor;`
- L15 _parameter_ `uint ClosureIndex;`

### `Shaders/Private/Lumen/LumenReflectionDenoiserCommon.ush` (Private)

- lines: 59; parse: all-branches
- includes: L5 `../StochasticLighting/StochasticLightingCommon.ush`
- L3 #pragma `once`

#### Global parameters (uniforms) (1)

- L12 _parameter_ `float ReflectionsDenoiserOneOverTonemapRange;`

#### Functions (7)

- L7-10 _function_ `float3 LumenRGBToYCoCgSafe(float3 RGB)`
- L14-23 _function_ `float3 RGBToDenoiserSpace(float3 V)`
- L25-29 _function_ `float4 RGBAToDenoiserSpace(float4 V)`
- L31-40 _function_ `float3 DenoiserSpaceToRGB(float3 V)`
- L42-48 _function_ `uint GetMaxFramesAccumulated(uint MaxFrames, float Roughness)`
- L51-54 _function_ `half PackNumFramesAccumulated(half X)` — Packing into an UNorm float
- L56-59 _function_ `half UnpackNumFramesAccumulated(half X)`

### `Shaders/Private/Lumen/LumenReflectionDenoiserSpatial.usf` (Private)

- lines: 213; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../SceneTextureParameters.ush`, L5 `LumenReflectionCommon.ush`, L6 `LumenReflectionDenoiserCommon.ush`, L9 `../ShaderPrint.ush` [DEBUG_MODE]

#### Macros (#define, 4)

- L10 `#define FontValue FontWhite` _[#if DEBUG_MODE]_
- L11 `#define FontSelected FontRed` _[#if DEBUG_MODE]_
- L12 `#define FontTitle FontEmerald` _[#if DEBUG_MODE]_
- L13 `#define FontBackground float4(0, 0, 0, 0.25f)` _[#if DEBUG_MODE]_

#### Entry points (1)

- L56-213 _entry_ `[numthreads(REFLECTION_THREADGROUP_SIZE_2D, REFLECTION_THREADGROUP_SIZE_2D, 1)] void LumenReflectionDenoiserSpatialCS( uint GroupId : SV_GroupID, uint2 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FLumenReflectionDenoiserSpatialCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenReflections.cpp:1210) — Run a spatial filter in order to filter out noise based on the temporal variance.

#### Global resources (textures / buffers / samplers) (6)

- L16 _resource_ `Texture2DArray<float4> SpecularLightingAndSecondMomentTexture;`
- L17 _resource_ `Texture2DArray<UNORM float> NumFramesAccumulatedTexture;`
- L18 _resource_ `RWTexture2DArray<float3> RWSpecularIndirectAccumulated;`
- L20 _resource_ `Texture2D<float3> FinalThroughputTexture;`
- L21 _resource_ `Texture2D<float2> BackgroundVisibilityTexture;`
- L22 _resource_ `RWTexture2D<float4> RWTranslucencyLighting;`

#### Global parameters (uniforms) (7)

- L24 _parameter_ `uint ClosureIndex;`
- L25 _parameter_ `float SpatialFilterDepthWeightScale;`
- L26 _parameter_ `float SpatialFilterKernelRadius;`
- L27 _parameter_ `uint SpatialFilterNumSamples;`
- L28 _parameter_ `float TemporalMaxFramesAccumulated;`
- L29 _parameter_ `float SpatialFilterMaxDisocclusionFrames;`
- L30 _parameter_ `uint bCompositeSceneColor;`

#### Functions (3)

- L32-36 _function_ `float3 TonemapLighting(float3 Lighting, float DisocclusionFactor)`
- L38-41 _function_ `float3 InverseTonemapLighting(float3 TonemappedLighting, float DisocclusionFactor)`
- L44-51 _function_ `bool IsLightingValidForDenoiser(float3 In)` — Workaround for Substrate fetching invalid value at tile border

### `Shaders/Private/Lumen/LumenReflectionDenoiserTemporal.usf` (Private)

- lines: 586; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../SceneTextureParameters.ush`, L5 `LumenReflectionCommon.ush`, L6 `LumenReflectionDenoiserCommon.ush`, L9 `../ShaderPrint.ush` [PERMUTATION_DEBUG]

#### Macros (#define, 9)

- L10 `#define FontValue FontWhite` _[#if PERMUTATION_DEBUG]_
- L11 `#define FontSelected FontRed` _[#if PERMUTATION_DEBUG]_
- L12 `#define FontTitle FontEmerald` _[#if PERMUTATION_DEBUG]_
- L13 `#define FontBackground float4(0, 0, 0, 0.25f)` _[#if PERMUTATION_DEBUG]_
- L68 `#define SHARED_TILE_BORDER 2`
- L69 `#define SHARED_TILE_SIZE (8 + 2 * SHARED_TILE_BORDER)`
- L183 `#define REFLECT_HIT_DEPTH_TEST 0`
- L214 `#define EXPAND_HISTORY_DISTANCE_THRESHOLD_FOR_JITTER 1`
- L422 `#define LOBE_CONFIDENCE 0` _[#if PERMUTATION_VALID_HISTORY]_

#### Entry points (1)

- L279-586 _entry_ `[numthreads(REFLECTION_THREADGROUP_SIZE_2D, REFLECTION_THREADGROUP_SIZE_2D, 1)] void LumenReflectionDenoiserTemporalCS( uint GroupId : SV_GroupID, uint2 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FLumenReflectionDenoiserTemporalCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenReflections.cpp:1042)

#### Structs / classes (3)

- L36-42 _struct_ **`FDebug`** `struct FDebug`
  - L39 _member_ `bool bActive;` _[#if PERMUTATION_DEBUG]_
  - L40 _member_ `FShaderPrintContext Context;` _[#if PERMUTATION_DEBUG]_
- L44-48 _struct_ **`FNeighborhood`** `struct FNeighborhood`
  - L46 _member_ `float3 Center;`
  - L47 _member_ `float3 Extent;`
- L113-124 _struct_ **`FLightingHistory`** `struct FLightingHistory`
  - L115 _member_ `bool bValid;`
  - L117 _member_ `float2 ScreenUV;`
  - L118 _member_ `float3 GatherUV;`
  - L119 _member_ `float4 GatherWeights;`
  - L121 _member_ `float3 Specular;`
  - L122 _member_ `float SpecularSecondMoment;`
  - L123 _member_ `float NumFramesAccumulated;`

#### Global resources (textures / buffers / samplers) (8)

- L16 _resource_ `Texture2D VelocityTexture;`
- L17 _resource_ `Texture2D SceneDepthHistory;`
- L18 _resource_ `Texture2DArray ResolvedSpecularLighting;`
- L19 _resource_ `Texture2DArray ResolvedReflectionsDepth;`
- L20 _resource_ `Texture2DArray SpecularHistoryTexture;`
- L21 _resource_ `Texture2DArray<UNORM float> NumFramesAccumulatedHistoryTexture;`
- L33 _resource_ `RWTexture2DArray<float4> RWSpecularAndSecondMoment;`
- L34 _resource_ `RWTexture2DArray<UNORM float> RWNumFramesAccumulated;`

#### Global parameters (uniforms) (10)

- L23 _parameter_ `float4 HistoryScreenPositionScaleBias;`
- L24 _parameter_ `float4 HistoryUVMinMax;`
- L25 _parameter_ `float4 HistoryGatherUVMinMax;`
- L26 _parameter_ `float4 HistoryBufferSizeAndInvSize;`
- L27 _parameter_ `float PrevSceneColorPreExposureCorrection;`
- L28 _parameter_ `float TemporalMaxFramesAccumulated;`
- L29 _parameter_ `float TemporalNeighborhoodClampScale;`
- L30 _parameter_ `float InvSubstrateMaxClosureCount;`
- L31 _parameter_ `float HistoryDistanceThreshold;`
- L277 _parameter_ `uint ClosureIndex;`

#### groupshared (1)

- L70 _groupshared_ `groupshared uint2 SharedResolvedSpecularYCoCg[SHARED_TILE_SIZE][SHARED_TILE_SIZE];`

#### Functions (5)

- L50-56 _function_ `uint2 PackLighting(float4 V)`
- L58-66 _function_ `float4 UnpackLighting(uint2 Packed)`
- L73-111 _function_ `FNeighborhood GetNeighborhood(uint2 LocalCoord, float3 CenterSample, float CenterSampleSceneDepth, inout FDebug Debug)` — Compute local neighborhood statistics
- L126-130 _function_ `float DepthPlaneWeight(float3 HistoryTranslatedWorldPosition, float3 SceneWorldNormal, float3 TranslatedWorldPosition, float DisocclusionDistanceThreshold)`
- L132-275 _function_ `FLightingHistory GetLightingHistory(float2 ScreenPosition, uint ClosureIndex, float DeviceZ, float ReflectionHitDeviceZ, float4 EncodedVelocity, bool bFromReflectHit, float3 TranslatedWorldPosition, float3 SceneWorldNormal, float SceneRoughness, float Noise, inout FDebug Debug)`

### `Shaders/Private/Lumen/LumenReflectionHardwareRayTracing.usf` (Private)

- lines: 425; parse: all-branches
- includes: L8 `/Engine/Shared/RayTracingTypes.h`, L9 `../Common.ush`, L10 `../MonteCarlo.ush`, L11 `../SceneTextureParameters.ush`, L12 `../StochasticLighting/StochasticLightingUpsample.ush`, L21 `LumenMaterial.ush`, L22 `LumenCardCommon.ush`, L23 `LumenTracingCommon.ush`, L24 `LumenReflectionCommon.ush`, L25 `LumenVisualizeTraces.ush`, L26 `LumenRadianceCacheCommon.ush`, L27 `LumenScreenTracing.ush`, L29 `LumenHairTracing.ush`, L56 `LumenHardwareRayTracingCommon.ush` [LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]

#### Macros (#define, 13)

- L4 `#define SUBSTRATE_SSS_MATERIAL_OVERRIDE 0`
- L5 `#define SUBSTRATE_COMPLEXSPECIALPATH 0`
- L6 `#define SUBSTRATE_GLINTS_ALLOWED 0`
- L15 `#define SUBSTRATE_MATERIALCONTAINER_IS_VIEWRESOURCE 0`
- L18 `#define PreIntegratedGF ReflectionStruct.PreIntegratedGF`
- L19 `#define PreIntegratedGFSampler GlobalBilinearClampedSampler`
- L28 `#define USE_HAIRSTRANDS_VOXEL DIM_HAIRSTRANDS_VOXEL`
- L32 `#define THREADGROUP_SIZE_2D 8` _[#if !defined(THREADGROUP_SIZE_2D)]_
- L36 `#define THREADGROUP_SIZE_1D THREADGROUP_SIZE_2D * THREADGROUP_SIZE_2D` _[#if !defined(THREADGROUP_SIZE_1D)]_
- L39 `#define RAY_TRACING_PASS_DEFAULT 0`
- L40 `#define RAY_TRACING_PASS_FAR_FIELD 1`
- L41 `#define RAY_TRACING_PASS_HIT_LIGHTING 2`
- L404 `#define DEBUG_SUPPORT_VISUALIZE_TRACE_COHERENCY 0` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_

#### Entry points (2)

- L47-51 _entry_ `[numthreads(1, 1, 1)] void FLumenReflectionHardwareRayTracingIndirectArgsCS()` — stage: **compute** — C++: `FLumenReflectionHardwareRayTracingIndirectArgsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenReflectionHardwareRayTracing.cpp:356) _[#if defined(FLumenReflectionHardwareRayTracingIndirectArgsCS)]_
- L99-422 _entry_ `LUMEN_HARDWARE_RAY_TRACING_ENTRY(LumenReflectionHardwareRayTracing)` — stage: **raygeneration\|compute(inline)** _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_

#### Global resources (textures / buffers / samplers) (11)

- L44 _resource_ `RWBuffer<uint> RWHardwareRayTracingIndirectArgs;`
- L58 _resource_ `RaytracingAccelerationStructure TLAS;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L59 _resource_ `RaytracingAccelerationStructure FarFieldTLAS;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L62 _resource_ `StructuredBuffer<FHitGroupRootConstants> HitGroupData;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING && LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L63 _resource_ `StructuredBuffer<FRayTracingSceneMetadataRecord> RayTracingSceneMetadata;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING && LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L64 _resource_ `RWStructuredBuffer<uint> RWInstanceHitCountBuffer;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING && LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L92 _resource_ `Texture2DArray<uint2> TraceBookmark;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L94 _resource_ `RWTexture2DArray<float3> RWTraceRadiance;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L95 _resource_ `RWTexture2DArray<float> RWTraceHit;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L96 _resource_ `RWTexture2DArray<uint2> RWTraceBookmark;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L97 _resource_ `RWTexture2DArray<uint> RWTraceMaterialId;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_

#### Global parameters (uniforms) (24)

- L43 _parameter_ `uint2 OutputThreadGroupSize;`
- L67 _parameter_ `uint HitLightingForceOpaque;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L68 _parameter_ `uint HitLightingShadowMode;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L69 _parameter_ `uint HitLightingShadowTranslucencyMode;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L70 _parameter_ `uint HitLightingDirectLighting;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L71 _parameter_ `uint HitLightingSkylight;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L72 _parameter_ `uint UseReflectionCaptures;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L74 _parameter_ `float RayTracingBias;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L75 _parameter_ `float RayTracingNormalBias;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L76 _parameter_ `float NearFieldMaxTraceDistance;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L77 _parameter_ `float FarFieldBias;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L78 _parameter_ `float FarFieldMaxTraceDistance;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L79 _parameter_ `float NearFieldMaxTraceDistanceDitherScale;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L80 _parameter_ `float NearFieldSceneRadius;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L81 _parameter_ `float PullbackBias;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L82 _parameter_ `float DistantScreenTracesStartDistance;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L83 _parameter_ `uint MaxTraversalIterations;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L84 _parameter_ `uint MeshSectionVisibilityTest;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L85 _parameter_ `int ApplySkyLight;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L86 _parameter_ `int HitLightingForceEnabled;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L87 _parameter_ `int SampleSceneColor;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L88 _parameter_ `float RelativeDepthThickness;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L89 _parameter_ `uint MaxReflectionBounces;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L90 _parameter_ `uint MaxRefractionBounces;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_

### `Shaders/Private/Lumen/LumenReflectionResolve.usf` (Private)

- lines: 658; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../SceneTextureParameters.ush`, L5 `LumenReflectionCommon.ush`, L6 `LumenReflectionDenoiserCommon.ush`, L7 `../StochasticLighting/StochasticLightingUpsample.ush`, L10 `../ShaderPrint.ush` [DEBUG_MODE]

#### Macros (#define, 5)

- L11 `#define FontValue FontWhite` _[#if DEBUG_MODE]_
- L12 `#define FontSelected FontRed` _[#if DEBUG_MODE]_
- L13 `#define FontTitle FontEmerald` _[#if DEBUG_MODE]_
- L14 `#define FontBackground float4(0, 0, 0, 0.25f)` _[#if DEBUG_MODE]_
- L260 `#define STOCHASTIC_UPSAMPLE 0` _[#if !(DOWNSAMPLE_FACTOR_X == 1 && DOWNSAMPLE_FACTOR_Y == 1)]_

#### Entry points (1)

- L75-658 _entry_ `[numthreads(REFLECTION_THREADGROUP_SIZE_2D, REFLECTION_THREADGROUP_SIZE_2D, 1)] void LumenReflectionResolveCS( uint GroupId : SV_GroupID, uint2 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FLumenReflectionResolveCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenReflections.cpp:762)

#### Structs / classes (1)

- L41-46 _struct_ **`FReflectionLighting`** `struct FReflectionLighting`
  - L43 _member_ `float3 Lighting;`
  - L44 _member_ `float WeightSum;`
  - L45 _member_ `float MinRayHitT;`

#### Global resources (textures / buffers / samplers) (7)

- L17 _resource_ `RWTexture2DArray<float3> RWSpecularIndirect;`
- L18 _resource_ `RWTexture2DArray<float> RWSpecularIndirectDepth;`
- L20 _resource_ `RWTexture2D<float3> RWFinalThroughput;`
- L21 _resource_ `RWTexture2D<UNORM float2> RWBackgroundVisibility;`
- L22 _resource_ `Texture2DArray<float3> TraceThroughput;`
- L23 _resource_ `Texture2DArray<float2> TraceBackgroundVisibility;`
- L27 _resource_ `Texture2D<float> DownsampledClosureIndex;`

#### Global parameters (uniforms) (7)

- L25 _parameter_ `float2 ReflectionTracingBufferInvSize;`
- L29 _parameter_ `uint ClosureIndex;`
- L30 _parameter_ `uint NumSpatialReconstructionSamples;`
- L31 _parameter_ `float SpatialReconstructionKernelRadius;`
- L32 _parameter_ `float SpatialReconstructionRoughnessScale;`
- L33 _parameter_ `float SpatialReconstructionMinWeight;`
- L34 _parameter_ `float InvSubstrateMaxClosureCount;`

#### Functions (3)

- L36-39 _function_ `bool IsValidDownsampledCoord(uint2 DownsampledScreenCoord)`
- L48-55 _function_ `FReflectionLighting InitReflectionLighting(float3 InitLighting=0.f)`
- L58-73 _function_ `float GetSampleWeight(float3 RayDir, float RayPDF, const float3x3 TangentBasis, float3 V, bool bHasAnisotropy, float a2, float2 ax_ay)` — Weight reflection rays by BRDF(Ray) / RayPDF

### `Shaders/Private/Lumen/LumenReflectionTracing.usf` (Private)

- lines: 959; parse: all-branches
- includes: L3 `../Common.ush`, L4 `LumenMaterial.ush`, L5 `../DeferredShadingCommon.ush`, L6 `../RayTracing/RayTracingRayCone.ush`, L7 `LumenCardCommon.ush`, L8 `LumenTracingCommon.ush`, L9 `LumenSoftwareRayTracing.ush`, L10 `LumenRadianceCacheCommon.ush`, L11 `LumenReflectionCommon.ush`, L12 `../SceneTextureParameters.ush`, L13 `../SHCommon.ush`, L14 `../ShaderPrint.ush`, L16 `LumenScreenTracing.ush`, L17 `LumenHairTracing.ush`, L18 `../StochasticLighting/StochasticLightingRayTracing.ush`

#### Macros (#define, 12)

- L15 `#define HZB_TRACE_INCLUDE_FULL_RES_DEPTH 1`
- L21 `#define THREADGROUP_SIZE 1` _[#if !defined(THREADGROUP_SIZE)]_
- L262 `#define TRACE_COMPACTION_MODE_DEFAULT 0`
- L263 `#define TRACE_COMPACTION_MODE_FAR_FIELD 1`
- L264 `#define TRACE_COMPACTION_MODE_HIT_LIGHTING 2`
- L438 `#define THREADGROUP_SIZE_1D 1` _[#if defined(ReflectionSortTracesByMaterialCS) && !defined(THREADGROUP_SIZE_1D)]_
- L440 `#define NUM_BINS (THREADGROUP_SIZE_1D / 2)` _[#if defined(ReflectionSortTracesByMaterialCS)]_
- L445 `#define Offsets Bins` _[#if defined(ReflectionSortTracesByMaterialCS) && DIM_WAVE_OPS]_
- L454 `#define ELEMENTS_PER_THREAD 16` _[#if defined(ReflectionSortTracesByMaterialCS)]_
- L455 `#define NUM_ELEMENTS THREADGROUP_SIZE_1D * ELEMENTS_PER_THREAD` _[#if defined(ReflectionSortTracesByMaterialCS)]_
- L688 `#define REFLECTION_TRACE_THREADGROUP_SIZE_1D 32` _[#if THREADGROUP_SIZE_32]_
- L690 `#define REFLECTION_TRACE_THREADGROUP_SIZE_1D 64` _[#if !(THREADGROUP_SIZE_32)]_

#### Entry points (9)

- L34-61 _entry_ `[numthreads(REFLECTION_THREADGROUP_SIZE_1D, 1, 1)] void ReflectionClearTracesCS( uint GroupId : SV_GroupID, uint GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FReflectionClearTracesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenReflectionTracing.cpp:428) _[#if defined(ReflectionClearTracesCS)]_
- L72-229 _entry_ `[numthreads(REFLECTION_THREADGROUP_SIZE_1D, 1, 1)] void ReflectionTraceScreenTexturesCS( uint GroupId : SV_GroupID, uint GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FReflectionTraceScreenTexturesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenReflectionTracing.cpp:483) _[#if defined(ReflectionTraceScreenTexturesCS)]_
- L240-255 _entry_ `[numthreads(64, 1, 1)] void SetupCompactionIndirectArgsCS(uint GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FSetupCompactionIndirectArgsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenReflectionTracing.cpp:504) _[#if defined(SetupCompactionIndirectArgsCS)]_
- L288-408 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void ReflectionCompactTracesCS( uint GroupId : SV_GroupID, uint GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FReflectionCompactTracesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenReflectionTracing.cpp:594) _[#if defined(ReflectionCompactTracesCS)]_
- L417-431 _entry_ `[numthreads(1, 1, 1)] void SetupCompactedTracesIndirectArgsCS()` — stage: **compute** — C++: `FSetupReflectionCompactedTracesIndirectArgsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenReflectionTracing.cpp:674) _[#if defined(SetupCompactedTracesIndirectArgsCS)]_
- L460-557 _entry_ `[numthreads(THREADGROUP_SIZE_1D, 1, 1)] void ReflectionSortTracesByMaterialCS( uint GroupId : SV_GroupID, uint GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FReflectionSortTracesByMaterialCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenReflectionTracing.cpp:652) _[#if defined(ReflectionSortTracesByMaterialCS)]_
- L695-707 _entry_ `[numthreads(REFLECTION_TRACE_THREADGROUP_SIZE_1D, 1, 1)] void ReflectionTraceMeshSDFsCS(uint DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FReflectionTraceMeshSDFsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenReflectionTracing.cpp:732) _[#if defined(ReflectionTraceMeshSDFsCS)]_
- L890-902 _entry_ `[numthreads(REFLECTION_TRACE_THREADGROUP_SIZE_1D, 1, 1)] void ReflectionTraceVoxelsCS(uint DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FReflectionTraceVoxelsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenReflectionTracing.cpp:830) _[#if defined(ReflectionTraceVoxelsCS)]_
- L908-956 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void VisualizeReflectionTracesCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FVisualizeReflectionTracesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenReflectionTracing.cpp:863) _[#if defined(VisualizeReflectionTracesCS)]_

#### Global resources (textures / buffers / samplers) (12)

- L26 _resource_ `RWTexture2DArray<float> RWTraceHit;`
- L27 _resource_ `RWTexture2DArray<float3> RWTraceRadiance;`
- L28 _resource_ `RWTexture2DArray<uint> RWTraceMaterialId;`
- L29 _resource_ `RWTexture2DArray<float3> RWTraceThroughput;`
- L30 _resource_ `RWTexture2DArray<UNORM float2> RWTraceBackgroundVisibility;`
- L233 _resource_ `RWBuffer<uint> RWCompactedTraceTexelAllocator;`
- L234 _resource_ `RWBuffer<uint> RWReflectionCompactionIndirectArgs;`
- L235 _resource_ `Buffer<uint> ReflectionTracingTileIndirectArgs;`
- L259 _resource_ `RWBuffer<uint> RWCompactedTraceTexelData;`
- L271 _resource_ `Texture2DArray<uint> TraceMaterialId;`
- L414 _resource_ `RWBuffer<uint> RWReflectionCompactTracingIndirectArgs;` _[#if defined(SetupCompactedTracesIndirectArgsCS)]_
- L415 _resource_ `RWBuffer<uint> RWReflectionCompactRayTraceDispatchIndirectArgs;` _[#if defined(SetupCompactedTracesIndirectArgsCS)]_

#### Global parameters (uniforms) (17)

- L64 _parameter_ `float MaxTraceDistance;`
- L65 _parameter_ `float MaxHierarchicalScreenTraceIterations;`
- L66 _parameter_ `float RelativeDepthThickness;`
- L67 _parameter_ `float HistoryDepthTestRelativeThickness;`
- L68 _parameter_ `uint MinimumTracingThreadOccupancy;`
- L236 _parameter_ `uint CompactionThreadGroupSize;`
- L266 _parameter_ `uint CullByDistanceFromCamera;`
- L267 _parameter_ `float CompactionTracingEndDistanceFromCamera;`
- L268 _parameter_ `float CompactionMaxTraceDistance;`
- L269 _parameter_ `float NearFieldMaxTraceDistance;`
- L270 _parameter_ `float FarFieldDitheredStartDistanceFactor;`
- L561 _parameter_ `uint CardGridPixelSizeShift;`
- L562 _parameter_ `float3 CardGridZParams;`
- L563 _parameter_ `uint3 CullGridSize;`
- L574 _parameter_ `float SurfaceBias;`
- L575 _parameter_ `float CardTraceEndDistanceFromCamera;`
- L576 _parameter_ `float MaxMeshSDFTraceDistance;`

#### groupshared (8)

- L275 _groupshared_ `groupshared uint SharedGlobalTraceTexelStartOffset;` _[#if defined(ReflectionCompactTracesCS)]_
- L278 _groupshared_ `groupshared uint SharedGroupSum;` _[#if defined(ReflectionCompactTracesCS) && WAVE_OP_WAVE_SIZE > 0]_
- L280 _groupshared_ `groupshared uint SharedTraceTexelAllocator;` _[#if defined(ReflectionCompactTracesCS) && !(WAVE_OP_WAVE_SIZE > 0)]_
- L281 _groupshared_ `groupshared uint SharedTraceTexels[THREADGROUP_SIZE];` _[#if defined(ReflectionCompactTracesCS) && !(WAVE_OP_WAVE_SIZE > 0)]_
- L441 _groupshared_ `groupshared uint Bins[NUM_BINS];` _[#if defined(ReflectionSortTracesByMaterialCS)]_
- L444 _groupshared_ `groupshared uint SharedGroupSum;` _[#if defined(ReflectionSortTracesByMaterialCS) && DIM_WAVE_OPS]_
- L448 _groupshared_ `groupshared uint Offsets[NUM_BINS];` _[#if defined(ReflectionSortTracesByMaterialCS) && !(DIM_WAVE_OPS) && NUM_BINS > 0]_
- L450 _groupshared_ `groupshared uint Offsets[1];` _[#if defined(ReflectionSortTracesByMaterialCS) && !(DIM_WAVE_OPS) && !(NUM_BINS > 0)]_

#### Functions (3)

- L565-572 _function_ `uint ComputeCardGridCellIndex(uint2 PixelPos, float SceneDepth)`
- L578-685 _function_ `void TraceMeshSDFs(FReflectionTracingCoord ReflectionTracingCoord, float TraceHitDistance)`
- L711-886 _function_ `void TraceVoxels(FReflectionTracingCoord ReflectionTracingCoord, float TraceHitDistance)`

#### Top-level macro invocations (2)

- L286 _macro_call_ `WAVESIZE(WAVE_OP_WAVE_SIZE)` _[#if defined(ReflectionCompactTracesCS) && COMPILER_SUPPORTS_WAVE_SIZE && WAVE_OP_WAVE_SIZE > 0]_
- L458 _macro_call_ `WAVESIZE(32)` _[#if defined(ReflectionSortTracesByMaterialCS) && COMPILER_SUPPORTS_WAVE_SIZE && DIM_WAVE_OPS]_

### `Shaders/Private/Lumen/LumenReflections.usf` (Private)

- lines: 524; parse: all-branches
- includes: L3 `../Common.ush`, L4 `LumenMaterial.ush`, L6 `../SceneTextureParameters.ush`, L7 `../BRDF.ush`, L8 `../Random.ush`, L9 `LumenReflectionCommon.ush`, L10 `../ClearCoatCommon.ush`, L11 `../FastMath.ush`, L12 `LumenRadianceCacheCommon.ush`, L13 `LumenScreenProbeTileClassication.ush`, L480 `LumenReflectionDenoiserCommon.ush` [defined(ReflectionClearNeighborTileCS)]

#### Macros (#define, 5)

- L16 `#define THREADGROUP_SIZE 1` _[#if !defined(THREADGROUP_SIZE)]_
- L20 `#define FRONT_LAYER_TRANSLUCENCY 0` _[#if !defined(FRONT_LAYER_TRANSLUCENCY)]_
- L48 `#define RESOLVE_TILE_SIZE 8`
- L51 `#define PERMUTATION_OVERFLOW_TILE 0` _[#if !defined(PERMUTATION_OVERFLOW_TILE)]_
- L285 `#define BLUE_NOISE_LUT 1`

#### Entry points (5)

- L28-42 _entry_ `[numthreads(1, 1, 1)] void InitReflectionIndirectArgsCS( uint2 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint2 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FInitReflectionIndirectArgsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenReflections.cpp:499)
- L71-270 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void ReflectionTileClassificationBuildListsCS( uint3 GroupId : SV_GroupID, uint2 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FReflectionTileClassificationBuildListsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenReflections.cpp:565)
- L301-436 _entry_ `[numthreads(REFLECTION_THREADGROUP_SIZE_1D, 1, 1)] void ReflectionGenerateRaysCS( uint GroupId : SV_GroupID, uint GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FReflectionGenerateRaysCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenReflections.cpp:651)
- L444-470 _entry_ `[numthreads(REFLECTION_THREADGROUP_SIZE_2D, REFLECTION_THREADGROUP_SIZE_2D, 1)] void ReflectionClearUnusedTraceTileDataCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FReflectionClearUnusedTraceTileDataCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenReflections.cpp:681) — Clear tracing tile data for tiles which will be skipped due to tile classification, but still may be read during reflection resolve
- L482-522 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void ReflectionClearNeighborTileCS(uint3 GroupId : SV_GroupID, uint2 GroupThreadId : SV_GroupThreadID, uint GroupThread1D : SV_GroupIndex)` — stage: **compute** — C++: `FReflectionClearNeighborTileCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenReflections.cpp:606) _[#if defined(ReflectionClearNeighborTileCS)]_

#### Global resources (textures / buffers / samplers) (16)

- L23 _resource_ `RWBuffer<uint> RWReflectionClearTileIndirectArgs;`
- L24 _resource_ `RWBuffer<uint> RWReflectionResolveTileIndirectArgs;`
- L25 _resource_ `RWBuffer<uint> RWReflectionClearUnusedTracingTileIndirectArgs;`
- L26 _resource_ `RWBuffer<uint> RWReflectionTracingTileIndirectArgs;`
- L44 _resource_ `RWTexture2DArray<float> RWDownsampledDepth;`
- L45 _resource_ `RWTexture2D<float> RWDownsampledClosureIndex;`
- L54 _resource_ `RWBuffer<uint> RWReflectionClearTileData;`
- L55 _resource_ `RWBuffer<uint> RWReflectionTileIndirectArgs;`
- L56 _resource_ `RWBuffer<uint> RWReflectionTileData;`
- L57 _resource_ `Texture2DArray<uint> LumenTileBitmask;`
- L280 _resource_ `RWTexture2DArray<uint> RWRayTraceDistance;`
- L281 _resource_ `RWTexture2DArray<float4> RWRayBuffer;`
- L438 _resource_ `Buffer<uint> ReflectionClearUnusedTracingTileIndirectArgs;`
- L439 _resource_ `Buffer<uint> ReflectionClearUnusedTracingTileData;`
- L474 _resource_ `RWTexture2DArray<float4> RWSpecularAndSecondMoment;` _[#if defined(ReflectionClearNeighborTileCS)]_
- L475 _resource_ `RWTexture2DArray<float3> RWSpecularIndirect;` _[#if defined(ReflectionClearNeighborTileCS)]_

#### Global parameters (uniforms) (12)

- L59 _parameter_ `uint2 TileViewportMin;`
- L60 _parameter_ `uint2 TileViewportDimensions;`
- L61 _parameter_ `uint2 ResolveTileViewportMin;`
- L62 _parameter_ `uint2 ResolveTileViewportDimensions;`
- L272 _parameter_ `float GGXSamplingBias;`
- L273 _parameter_ `float MaxTraceDistance;`
- L274 _parameter_ `float RadianceCacheMinRoughness;`
- L275 _parameter_ `float RadianceCacheMaxRoughness;`
- L276 _parameter_ `float RadianceCacheMinTraceDistance;`
- L277 _parameter_ `float RadianceCacheMaxTraceDistance;`
- L278 _parameter_ `float RadianceCacheRoughnessFadeLength;`
- L476 _parameter_ `uint KernelRadiusInTiles;` _[#if defined(ReflectionClearNeighborTileCS)]_

#### groupshared (7)

- L64 _groupshared_ `groupshared uint SharedNumTiles;`
- L65 _groupshared_ `groupshared uint SharedNumClearTiles;`
- L66 _groupshared_ `groupshared uint SharedTileData[THREADGROUP_SIZE * THREADGROUP_SIZE];`
- L67 _groupshared_ `groupshared uint SharedTileUsed[THREADGROUP_SIZE * THREADGROUP_SIZE];`
- L68 _groupshared_ `groupshared uint SharedGlobalTileOffset;`
- L69 _groupshared_ `groupshared uint SharedGlobalClearTileOffset;`
- L478 _groupshared_ `groupshared uint SharedbIsTileUsed;` _[#if defined(ReflectionClearNeighborTileCS)]_

#### Functions (2)

- L283-294 _function_ `float2 GenerateRandom(uint2 InReflectionTracingCoord)`
- L296-299 _function_ `float LinearStep(float Edge0, float Edge1, float X)`

### `Shaders/Private/Lumen/LumenReflectionsCombine.ush` (Private)

- lines: 42; parse: all-branches
- L3 #pragma `once`

#### Global parameters (uniforms) (3)

- L5 _parameter_ `float MaxRoughnessToTrace;`
- L6 _parameter_ `float MaxRoughnessToTraceForFoliage;`
- L7 _parameter_ `float InvRoughnessFadeLength;`

#### Functions (4)

- L12-16 _function_ `float LumenCombineReflectionsAlpha(float InRoughness, bool bHasBackfaceDiffuse)` — Weight of reflection rays for a current pixel 0 - specular should fallback to some specular approximation 1 - specular should only composite reflection rays
- L18-25 _function_ `bool NeedsLumenReflections(float InRoughness, float InTopRoughness, bool bHasBackfaceDiffuse, bool bIsClearCoat)`
- L27-35 _function_ `bool NeedsLumenClearCoatRoughReflections(float InTopRoughness, bool bIsClearCoat)`
- L39-42 _function_ `float RoughReflectionsDiffuseLerp(float InMaterialRoughness, bool bHasBackfaceDiffuse, float InFadeLength, float InMaxRoughnessToEvaluateRoughSpecular, float InMaxRoughnessToEvaluateRoughSpecularForFoliage)` — Computes the lerp factor to diffuse for rough specular, as an optimization to skip rough specular computations 1 = fully diffuse and rough reflection computation can be skipped

### `Shaders/Private/Lumen/LumenScene.usf` (Private)

- lines: 193; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../ShaderPrint.ush`

#### Macros (#define, 4)

- L6 `#define MAX_LUMEN_VIEWS 2`
- L7 `#define LUMEN_INVALID_MESH_CARDS_INDEX 0xFFFFFFFF`
- L8 `#define FLOAT_32_MAX float(+3.402823466e+38f)`
- L25 `#define LUMEN_PRIMITIVE_GROUP_DATA_STRIDE 2`

#### Entry points (3)

- L70-124 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void LumenSceneUpdateCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FLumenSceneUpdateCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenSceneGPUDrivenUpdate.cpp:255) — Loop over all Lumen Primitive Groups in order to find which ones should be visible and spawn mesh cards.
- L129-150 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void VisualizePrimitiveGroupsCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FVisualizePrimitiveGroupsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenSceneGPUDrivenUpdate.cpp:286) — Visualize GPU side primitive groups data
- L158-193 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void LumenSceneStatsCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FLumenSceneStatsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenSceneGPUDrivenUpdate.cpp:319) — Debug stats for debugging Lumen Scene and its GPU driven updates

#### Structs / classes (1)

- L10-22 _struct_ **`FLumenPrimitiveGroupData`** `struct FLumenPrimitiveGroupData`
  - L12 _member_ `float3 WorldSpaceBoundingBoxCenter;`
  - L13 _member_ `float3 WorldSpaceBoundingBoxExtent;`
  - L15 _member_ `uint MeshCardsIndex;`
  - L17 _member_ `bool bValid;`
  - L18 _member_ `bool bValidMeshCards;`
  - L19 _member_ `bool bFarField;`
  - L20 _member_ `bool bHeightfield;`
  - L21 _member_ `bool bEmissiveLightSource;`

#### Global resources (textures / buffers / samplers) (4)

- L52 _resource_ `RWStructuredBuffer<uint2> RWSceneAddOps;`
- L55 _resource_ `RWStructuredBuffer<uint> RWSceneRemoveOps;`
- L152 _resource_ `StructuredBuffer<uint2> SceneAddOps;`
- L153 _resource_ `StructuredBuffer<uint> SceneRemoveOps;`

#### Global parameters (uniforms) (9)

- L53 _parameter_ `uint MaxSceneAddOps;`
- L56 _parameter_ `uint MaxSceneRemoveOps;`
- L58 _parameter_ `float4 WorldCameraOrigins[MAX_LUMEN_VIEWS];`
- L59 _parameter_ `uint NumCameraOrigins;`
- L61 _parameter_ `float CardMaxDistanceSq;`
- L62 _parameter_ `float CardTexelDensity;`
- L63 _parameter_ `float FarFieldCardMaxDistanceSq;`
- L64 _parameter_ `float FarFieldCardTexelDensity;`
- L65 _parameter_ `float MinCardResolution;`

#### Functions (1)

- L28-50 _function_ `FLumenPrimitiveGroupData GetLumenPrimitiveGroupData(uint PrimitiveGroupId)` — Layout must match FLumenPrimitiveGroup in C++

### `Shaders/Private/Lumen/LumenSceneDebugHardwareRayTracing.usf` (Private)

- lines: 134; parse: all-branches
- includes: L3 `/Engine/Shared/RayTracingTypes.h`, L4 `../Common.ush`, L5 `../MonteCarlo.ush`, L6 `../MortonCode.ush`, L7 `../SceneTextureParameters.ush`, L8 `LumenCardCommon.ush`, L9 `LumenTracingCommon.ush`, L26 `LumenHardwareRayTracingCommon.ush` [LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING], L29 `LumenCardTile.ush`, L30 `../ShaderPrint.ush`

#### Macros (#define, 2)

- L13 `#define LUMEN_HARDWARE_RAYTRACING 0` _[#if !defined(LUMEN_HARDWARE_RAYTRACING)]_
- L17 `#define LUMEN_HARDWARE_INLINE_RAYTRACING 0` _[#if !defined(LUMEN_HARDWARE_INLINE_RAYTRACING)]_
- L23 #undef `ENABLE_TRACING_FEEDBACK`

#### Entry points (1)

- L54-130 _entry_ `LUMEN_HARDWARE_RAY_TRACING_ENTRY(LumenSceneDebugHardwareRayTracing)` — stage: **raygeneration\|compute(inline)** _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING && SHADER_DEBUG_SCENE]_

#### Global resources (textures / buffers / samplers) (4)

- L34 _resource_ `RaytracingAccelerationStructure TLAS;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L37 _resource_ `StructuredBuffer<FHitGroupRootConstants> HitGroupData;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING && LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L38 _resource_ `StructuredBuffer<FRayTracingSceneMetadataRecord> RayTracingSceneMetadata;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING && LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L52 _resource_ `RWStructuredBuffer<uint> RWDebugData;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING && SHADER_DEBUG_SCENE]_

#### Global parameters (uniforms) (1)

- L51 _parameter_ `float ResolutionScale;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING && SHADER_DEBUG_SCENE]_

#### Functions (1)

- L40-46 _function_ `FLumenTraceRayInlineCallback InitLumenTraceRayInlineCallback()` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING && LUMEN_HARDWARE_INLINE_RAYTRACING]_

### `Shaders/Private/Lumen/LumenSceneDirectLighting.usf` (Private)

- lines: 165; parse: all-branches
- includes: L3 `../Common.ush`, L4 `LumenCardCommon.ush`, L5 `LumenCardTile.ush`, L6 `LumenCardTileShadowDownsampleFactor.ush`, L7 `SurfaceCache/LumenSurfaceCache.ush`, L10 `../DeferredLightingCommon.ush`, L11 `../VolumeLightingCommon.ush`, L13 `../ForwardShadowingCommon.ush`, L14 `LumenSceneDirectLighting.ush`, L15 `LumenFloatQuantization.ush`

#### Macros (#define, 4)

- L8 `#define SUPPORT_CONTACT_SHADOWS 0`
- L9 `#define USE_IES_PROFILE 1`
- L12 `#define FILTER_DIRECTIONAL_LIGHT_SHADOWING 1`
- L44 `#define HAS_MULTIPLE_VIEWS 0` _[#if !defined(HAS_MULTIPLE_VIEWS)]_

#### Entry points (1)

- L99-164 _entry_ `[numthreads(CARD_TILE_SIZE, CARD_TILE_SIZE, 1)] void LumenCardBatchDirectLightingCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FLumenCardBatchDirectLightingCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenSceneDirectLighting.cpp:804)

#### Global resources (textures / buffers / samplers) (4)

- L47 _resource_ `RWTexture2D<float3> RWDirectLightingAtlas;`
- L48 _resource_ `StructuredBuffer<uint> CardTiles;`
- L49 _resource_ `StructuredBuffer<uint> LightTileOffsetNumPerCardTile;`
- L50 _resource_ `StructuredBuffer<uint2> LightTilesPerCardTile;`

#### Global parameters (uniforms) (1)

- L52 _parameter_ `float CachedLightingPreExposure;`

#### groupshared (2)

- L54 _groupshared_ `groupshared uint bSharedTileVisibleToLight;`
- L55 _groupshared_ `groupshared uint bSharedTileShadowed;`

#### Functions (3)

- L17-29 _function_ `FDeferredLightData GetLumenDirectLightingLightData(uint LightIndex, float3 PreViewTranslation, float Exposure)`
- L31-41 _function_ `float3 GetIrradianceForLight( uint LightIndex, FLumenSurfaceCacheData SurfaceCacheData, float3 PreViewTranslation, float Exposure, float3 ShadowFactor)`
- L57-94 _function_ `bool TileHasUniformVisibilityToLight(FShadowMaskRay ShadowMaskRay, uint2 TexelCoordInTile, bool bValidTexel)`

#### Top-level macro invocations (1)

- L97 _macro_call_ `WAVESIZE(WAVE_OP_WAVE_SIZE)` _[#if WAVE_OP_WAVE_SIZE > 0 && COMPILER_SUPPORTS_WAVE_SIZE]_

### `Shaders/Private/Lumen/LumenSceneDirectLighting.ush` (Private)

- lines: 358; parse: all-branches
- includes: L5 `LumenSceneLighting.ush`, L6 `../EyeAdaptationCommon.ush`, L7 `/Engine/Shared/LightDefinitions.h`

#### Macros (#define, 16)

- L9 `#define NUM_BATCHABLE_LIGHT_TYPES 3`
- L41 `#define LUMEN_COLORED_LIGHT_FUNCTION_ATLAS (COLORED_LIGHT_FUNCTION_ATLAS)`
- L48 `#define SHADOW_MASK_RAY_BITS 16` _[#if LUMEN_COLORED_LIGHT_FUNCTION_ATLAS]_
- L49 `#define SHADOW_MASK_RAY_BITS_MASK ((1u << SHADOW_MASK_RAY_BITS) - 1)` _[#if LUMEN_COLORED_LIGHT_FUNCTION_ATLAS]_
- L50 `#define SHADOW_MASK_CARD_TILE_DWORDS (SHADOW_MASK_RAY_BITS * CARD_TILE_SIZE * CARD_TILE_SIZE / 32)` _[#if LUMEN_COLORED_LIGHT_FUNCTION_ATLAS]_
- L51 `#define SHADOW_FACTOR_BITS 15` _[#if LUMEN_COLORED_LIGHT_FUNCTION_ATLAS]_
- L52 `#define SHADOW_FACTOR_BITS_MASK ((1u << SHADOW_FACTOR_BITS) - 1)` _[#if LUMEN_COLORED_LIGHT_FUNCTION_ATLAS]_
- L53 `#define SHADOW_FACTOR_COMPLETE_BITS 1` _[#if LUMEN_COLORED_LIGHT_FUNCTION_ATLAS]_
- L54 `#define SHADOW_FACTOR_COMPLETE_BITS_MASK (((1u << SHADOW_FACTOR_COMPLETE_BITS) - 1) << SHADOW_FACTOR_BITS)` _[#if LUMEN_COLORED_LIGHT_FUNCTION_ATLAS]_
- L58 `#define SHADOW_MASK_RAY_BITS 8` _[#if !(LUMEN_COLORED_LIGHT_FUNCTION_ATLAS)]_
- L59 `#define SHADOW_MASK_RAY_BITS_MASK ((1u << SHADOW_MASK_RAY_BITS) - 1)` _[#if !(LUMEN_COLORED_LIGHT_FUNCTION_ATLAS)]_
- L60 `#define SHADOW_MASK_CARD_TILE_DWORDS (SHADOW_MASK_RAY_BITS * CARD_TILE_SIZE * CARD_TILE_SIZE / 32)` _[#if !(LUMEN_COLORED_LIGHT_FUNCTION_ATLAS)]_
- L61 `#define SHADOW_FACTOR_BITS 7` _[#if !(LUMEN_COLORED_LIGHT_FUNCTION_ATLAS)]_
- L62 `#define SHADOW_FACTOR_BITS_MASK ((1u << SHADOW_FACTOR_BITS) - 1)` _[#if !(LUMEN_COLORED_LIGHT_FUNCTION_ATLAS)]_
- L63 `#define SHADOW_FACTOR_COMPLETE_BITS 1` _[#if !(LUMEN_COLORED_LIGHT_FUNCTION_ATLAS)]_
- L64 `#define SHADOW_FACTOR_COMPLETE_BITS_MASK (((1u << SHADOW_FACTOR_COMPLETE_BITS) - 1) << SHADOW_FACTOR_BITS)` _[#if !(LUMEN_COLORED_LIGHT_FUNCTION_ATLAS)]_
- L3 #pragma `once`

#### Structs / classes (6)

- L14-19 _struct_ **`FShadowTrace`** `struct FShadowTrace`
  - L16 _member_ `uint LightTileIndex;`
  - L17 _member_ `uint2 LightTileCoord;`
  - L18 _member_ `uint DownSampleLevel;`
- L68-76 _struct_ **`FShadowMaskRay`** `struct FShadowMaskRay`
  - L71 _member_ `float3 ShadowFactor;` _[#if LUMEN_COLORED_LIGHT_FUNCTION_ATLAS]_
  - L73 _member_ `float ShadowFactor;` _[#if !(LUMEN_COLORED_LIGHT_FUNCTION_ATLAS)]_
  - L75 _member_ `bool bShadowFactorComplete;`
- L158-191 _struct_ **`FLumenPackedLight`** `struct FLumenPackedLight` — Must match FLumenPackedLight in LumenSceneDirectLighting.cpp
  - L160 _member_ `float3 WorldPositionHigh;`
  - L161 _member_ `uint LightingChannelMask;`
  - L163 _member_ `float3 WorldPositionLow;`
  - L164 _member_ `float InvRadius;`
  - L166 _member_ `float3 Color;`
  - L167 _member_ `float FalloffExponent;`
  - L169 _member_ `float3 Direction;`
  - L170 _member_ `uint DiffuseAndSpecularScale;`
  - L172 _member_ `float3 Tangent;`
  - L173 _member_ `float SourceRadius;`
  - L175 _member_ `float2 SpotAngles;`
  - L176 _member_ `float SoftSourceRadius;`
  - L177 _member_ `float SourceLength;`
  - L179 _member_ `float RectLightBarnCosAngle;`
  - L180 _member_ `float RectLightBarnLength;`
  - L181 _member_ `float RectLightAtlasMaxLevel;`
  - L182 _member_ `uint LightType;`
  - L184 _member_ `float2 SinCosConeAngleOrRectLightAtlasUVScale;`
  - L185 _member_ `float2 RectLightAtlasUVOffset;`
  - L187 _member_ `uint LightFunctionAtlasIndex_bHasShadowMask_bIsStandalone_bCastDynamicShadows;`
  - L188 _member_ `float IESAtlasIndex;`
  - L189 _member_ `float InverseExposureBlend;`
  - L190 _member_ `float Padding0;`
- L193-209 _struct_ **`FLumenLight`** `struct FLumenLight`
  - L195 _member_ `FDeferredLightData DeferredLightData;`
  - L197 _member_ `float4 InfluenceSphere;`
  - L198 _member_ `float3 ProxyPosition;`
  - L199 _member_ `float3 ProxyDirection;`
  - L200 _member_ `float ProxyRadius;`
  - L201 _member_ `float CosConeAngle;`
  - L202 _member_ `float SinConeAngle;`
  - L204 _member_ `uint VirtualShadowMapId;`
  - L205 _member_ `uint LightingChannelMask;`
  - L206 _member_ `uint bHasShadowMask;`
  - L207 _member_ `uint bIsStandaloneLight;`
  - L208 _member_ `uint Type;`
- L300-304 _struct_ **`FLumenSampleCoord`** `struct FLumenSampleCoord`
  - L302 _member_ `uint2 Coord;`
  - L303 _member_ `uint LayerIndex;`
- L324-330 _struct_ **`FLumenSampleSceneData`** `struct FLumenSampleSceneData`
  - L326 _member_ `float3 TranslatedWorldPosition;`
  - L327 _member_ `float3 WorldNormal;`
  - L328 _member_ `uint ViewIndex;`
  - L329 _member_ `bool bHeightfield;`

#### Global resources (textures / buffers / samplers) (4)

- L11 _resource_ `RWStructuredBuffer<uint> RWShadowMaskTiles;`
- L12 _resource_ `StructuredBuffer<uint> ShadowMaskTiles;`
- L211 _resource_ `StructuredBuffer<FLumenPackedLight> LumenPackedLights;`
- L215 _resource_ `StructuredBuffer<float4> LumenLightInfluenceSpheres;` — Storing influence spheres in a separate buffer to accelerate light culling. Most lights can be culled by testing only their influence spheres so no point loading other data for culled lights.

#### Global parameters (uniforms) (1)

- L276 _parameter_ `float3 LightFunctionParameters2;` — Fade distance in x, disabled brightness in y, output for preview shadows mask in z. _[#if LIGHT_FUNCTION]_

#### Functions (17)

- L21-29 _function_ `FShadowTrace UnpackShadowTrace(uint PackedValue)`
- L31-39 _function_ `uint PackShadowTrace(FShadowTrace ShadowTrace)`
- L79-83 _function_ `uint GetMaskFromColoredShadowFactor(float3 ShadowFactor)` _[#if LUMEN_COLORED_LIGHT_FUNCTION_ATLAS]_
- L84-88 _function_ `float3 GetColoredShadowFactorFromMask(uint Mask)` _[#if LUMEN_COLORED_LIGHT_FUNCTION_ATLAS]_
- L90-93 _function_ `bool IsVisibleToLight(float3 ShadowFactor)` _[#if LUMEN_COLORED_LIGHT_FUNCTION_ATLAS]_
- L95-98 _function_ `bool IsVisibleToLight(float ShadowFactor)` _[#if !(LUMEN_COLORED_LIGHT_FUNCTION_ATLAS)]_
- L101-114 _function_ `void ReadShadowMaskRayRW(uint CardTileIndex, uint2 CoordInCardTile, inout FShadowMaskRay ShadowMaskRay)`
- L116-129 _function_ `void ReadShadowMaskRay(uint CardTileIndex, uint2 CoordInCardTile, inout FShadowMaskRay ShadowMaskRay)`
- L131-155 _function_ `void WriteShadowMaskRay(FShadowMaskRay Ray, uint CardTileIndex, uint2 CoordInCardTile, const bool bClearExistingMask)`
- L217-220 _function_ `float4 LoadLumenLightInfluenceSphere(uint LightIndex)`
- L222-272 _function_ `FLumenLight LoadLumenLight(uint LightIndex, float3 PreViewTranslation, float Exposure)`
- L278-297 _function_ `float GetLumenLightFunction(float3 TranslatedWorldPosition)` _[#if LIGHT_FUNCTION]_
- L306-309 _function_ `uint PackLumenSampleCoord(uint2 Coord, uint LayerIndex)`
- L311-314 _function_ `uint PackLumenSampleCoord(FLumenSampleCoord In)`
- L316-322 _function_ `FLumenSampleCoord UnpackLumenSampleCoord(uint In)`
- L332-343 _function_ `float4 PackLumenSampleSceneData(float3 InPosition, float3 InNormal, uint InViewIndex, bool bHeightfield)`
- L345-358 _function_ `FLumenSampleSceneData UnpackLumenSampleSceneData(float4 In)`

### `Shaders/Private/Lumen/LumenSceneDirectLightingCulling.usf` (Private)

- lines: 739; parse: per-group
- includes: L3 `../Common.ush`, L4 `../IntersectionUtils.ush`, L6 `../DeferredLightingCommon.ush`, L8 `LumenCardCommon.ush`, L9 `LumenCardTile.ush`, L10 `LumenSceneDirectLighting.ush`, L11 `SurfaceCache/LumenSurfaceCache.ush`

#### Macros (#define, 3)

- L5 `#define SUPPORT_CONTACT_SHADOWS 0`
- L14 `#define THREADGROUP_SIZE 1` _[#if !defined(THREADGROUP_SIZE)]_
- L18 `#define MAX_LIGHT_SAMPLES 1` _[#if !defined(MAX_LIGHT_SAMPLES)]_

#### Entry points (7)

- L35-98 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void SpliceCardPagesIntoTilesCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FSpliceCardPagesIntoTilesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenSceneDirectLighting.cpp:343) — Splice card pages into N card tiles _[#if defined(SpliceCardPagesIntoTilesCS)]_
- L108-121 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void InitializeCardTileIndirectArgsCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FInitializeCardTileIndirectArgsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenSceneDirectLighting.cpp:372) _[#if defined(InitializeCardTileIndirectArgsCS)]_
- L132-174 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void CalculateCardTileDepthRangesCS( uint GroupId : SV_GroupID, uint2 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FCalculateCardTileDepthRangesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenSceneDirectLighting.cpp:469) _[#if defined(CalculateCardTileDepthRangesCS)]_
- L436-593 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void BuildLightTilesCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FBuildLightTilesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenSceneDirectLighting.cpp:574) _[#if defined(BuildLightTilesCS)]_
- L608-640 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void ComputeLightTileOffsetsPerLightCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FComputeLightTileOffsetsPerLightCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenSceneDirectLighting.cpp:610) — Prefix sum for card tile array compaction _[#if defined(ComputeLightTileOffsetsPerLightCS)]_
- L657-691 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void CompactLightTilesCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FCompactLightTilesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenSceneDirectLighting.cpp:649) — Compact card tile array _[#if defined(CompactLightTilesCS)]_
- L704-735 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void InitializeLightTileIndirectArgsCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FInitializeLightTileIndirectArgsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenSceneDirectLighting.cpp:685) _[#if defined(InitializeLightTileIndirectArgsCS)]_

#### Structs / classes (2)

- L272-278 _struct_ **`FLightSample`** `struct FLightSample`
  - L274 _member_ `float Weight;`
  - L275 _member_ `uint LightIndex;`
  - L276 _member_ `uint LightType;` — 0:standalone, 1:point, 2:spot, 3:rect
  - L277 _member_ `bool bHasShadowMask;`
- L280-283 _struct_ **`FLightSampleAccumulator`** `struct FLightSampleAccumulator`
  - L282 _member_ `uint PackedSamples[MAX_LIGHT_SAMPLES];`

#### Global resources (textures / buffers / samplers) (27)

- L21 _resource_ `StructuredBuffer<uint> CardPageIndexAllocator;`
- L22 _resource_ `StructuredBuffer<uint> CardPageIndexData;`
- L23 _resource_ `RWStructuredBuffer<uint> RWCardTileAllocator;`
- L24 _resource_ `RWStructuredBuffer<uint> RWCardTiles;`
- L102 _resource_ `StructuredBuffer<uint> CardTileAllocator;`
- L103 _resource_ `StructuredBuffer<uint> CardTiles;`
- L104 _resource_ `RWBuffer<uint> RWDispatchCardTilesIndirectArgs;`
- L127 _resource_ `RWStructuredBuffer<uint> RWCardTileDepthRanges;` _[#if defined(CalculateCardTileDepthRangesCS)]_
- L179 _resource_ `StructuredBuffer<uint> CardTileDepthRanges;`
- L261 _resource_ `RWStructuredBuffer<uint> RWLightTileAllocator;`
- L262 _resource_ `RWStructuredBuffer<uint2> RWLightTiles;`
- L263 _resource_ `RWStructuredBuffer<uint> RWLightTileAllocatorPerLight;`
- L264 _resource_ `RWStructuredBuffer<uint> RWLightTileAllocatorForPerCardTileDispatch;`
- L265 _resource_ `RWStructuredBuffer<uint> RWLightTileOffsetNumPerCardTile;`
- L597 _resource_ `StructuredBuffer<uint> LightTileAllocatorPerLight;`
- L598 _resource_ `RWStructuredBuffer<uint> RWLightTileOffsetsPerLight;`
- L602 _resource_ `StructuredBuffer<int> StandaloneLightIndices;` _[#if defined(ComputeLightTileOffsetsPerLightCS)]_
- L644 _resource_ `RWStructuredBuffer<uint2> RWCompactedLightTiles;`
- L645 _resource_ `RWStructuredBuffer<uint2> RWLightTilesPerCardTile;`
- L646 _resource_ `RWStructuredBuffer<uint> RWCompactedLightTileAllocatorPerLight;`
- L647 _resource_ `StructuredBuffer<uint> LightTileAllocator;`
- L648 _resource_ `StructuredBuffer<uint2> LightTiles;`
- L649 _resource_ `StructuredBuffer<uint> LightTileOffsetsPerLight;`
- L650 _resource_ `StructuredBuffer<uint> LightTileOffsetNumPerCardTile;`
- L695 _resource_ `RWBuffer<uint> RWDispatchLightTilesIndirectArgs;`
- L696 _resource_ `RWBuffer<uint> RWDrawTilesPerLightIndirectArgs;`
- L697 _resource_ `RWBuffer<uint> RWDispatchTilesPerLightIndirectArgs;`

#### Global parameters (uniforms) (8)

- L178 _parameter_ `uint CullToCardTileDepthRange;`
- L267 _parameter_ `uint MaxLightsPerTile;`
- L268 _parameter_ `uint NumLights;`
- L269 _parameter_ `uint NumViews;`
- L270 _parameter_ `int bUseLightTilesPerLightType;`
- L603 _parameter_ `uint NumStandaloneLights;` _[#if defined(ComputeLightTileOffsetsPerLightCS)]_
- L699 _parameter_ `uint VertexCountPerInstanceIndirect;`
- L700 _parameter_ `uint PerLightDispatchFactor;`

#### groupshared (6)

- L28 _groupshared_ `groupshared uint SharedTileAllocator;` _[#if defined(SpliceCardPagesIntoTilesCS)]_
- L29 _groupshared_ `groupshared uint SharedTiles[THREADGROUP_SIZE * THREADGROUP_SIZE];` _[#if defined(SpliceCardPagesIntoTilesCS)]_
- L30 _groupshared_ `groupshared uint SharedGlobalTileOffset;` _[#if defined(SpliceCardPagesIntoTilesCS)]_
- L129 _groupshared_ `groupshared uint SharedMinTileDepth;` _[#if defined(CalculateCardTileDepthRangesCS)]_
- L130 _groupshared_ `groupshared uint SharedMaxTileDepth;` _[#if defined(CalculateCardTileDepthRangesCS)]_
- L367 _groupshared_ `groupshared uint SharedScratchMemory[THREADGROUP_SIZE];` _[#if defined(BuildLightTilesCS)]_

#### Functions (10)

- L181-190 _function_ `float2 GetCardTileDepthRange(uint CardTileIndex)`
- L192-201 _function_ `bool DoesLightInfluenceSphereAffectCardPageUVRange(float4 InfluenceSphere, FLumenCardPageData CardPage, FLumenCardData Card, float2 UVMin, float2 UVMax, float2 CardTileDepthRange)`
- L204-259 _function_ `bool DoesLightAffectCardPageUVRange(FLumenLight LumenLight, FLumenCardPageData CardPage, FLumenCardData Card, float2 UVMin, float2 UVMax, float2 CardTileDepthRange, inout float3 OutCardPageWorldCenter)` — This function doesn't test light influence spheres
- L285-293 _function_ `FLightSampleAccumulator InitLightSampleAccumulator()`
- L295-302 _function_ `uint PackLightSample(FLightSample LightSample)`
- L304-312 _function_ `FLightSample UnpackLightSample(uint PackedLightSample)`
- L314-334 _function_ `void AddLightSample(inout FLightSampleAccumulator LightSampleAccumulator, FLightSample LightSample)`
- L336-363 _function_ `float GetLightWeight(FLumenLight LumenLight, float3 TranslatedWorldPosition)`
- L369-403 _function_ `uint GetGroupMax(uint GroupThreadIndex, uint Value)` _[#if defined(BuildLightTilesCS)]_
- L405-428 _function_ `uint GroupReadThreadFirst(uint GroupThreadIndex, uint Value)` _[#if defined(BuildLightTilesCS)]_

#### Top-level macro invocations (1)

- L434 _macro_call_ `WAVESIZE(WAVE_OP_WAVE_SIZE)` _[#if defined(BuildLightTilesCS) && WAVE_OP_WAVE_SIZE > 0 && COMPILER_SUPPORTS_WAVE_SIZE]_

### `Shaders/Private/Lumen/LumenSceneDirectLightingHardwareRayTracing.usf` (Private)

- lines: 422; parse: all-branches
- includes: L3 `/Engine/Shared/RayTracingTypes.h`, L4 `../Common.ush`, L5 `../MonteCarlo.ush`, L6 `../MortonCode.ush`, L7 `../SceneTextureParameters.ush`, L9 `../BlueNoise.ush` [USE_STOCHASTIC], L10 `LumenSceneDirectLightingStochastic.ush` [USE_STOCHASTIC], L11 `../MegaLights/MegaLightsRayTracing.ush` [USE_STOCHASTIC], L13 `LumenCardCommon.ush`, L14 `LumenTracingCommon.ush`, L15 `LumenReflectionCommon.ush`, L26 `LumenHardwareRayTracingCommon.ush` [LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING], L29 `LumenCardTile.ush`, L31 `../DeferredLightingCommon.ush`, L32 `LumenSceneDirectLighting.ush`

#### Macros (#define, 3)

- L18 `#define LUMEN_HARDWARE_RAYTRACING 0` _[#if !defined(LUMEN_HARDWARE_RAYTRACING)]_
- L22 `#define LUMEN_HARDWARE_INLINE_RAYTRACING 0` _[#if !defined(LUMEN_HARDWARE_INLINE_RAYTRACING)]_
- L30 `#define SUPPORT_CONTACT_SHADOWS 0`

#### Entry points (2)

- L40-53 _entry_ `[numthreads(1, 1, 1)] void LumenDirectLightingHardwareRayTracingIndirectArgsCS()` — stage: **compute** — C++: `FLumenDirectLightingHardwareRayTracingIndirectArgsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenSceneDirectLightingHardwareRayTracing.cpp:271) _[#if defined(LumenDirectLightingHardwareRayTracingIndirectArgsCS)]_
- L150-419 _entry_ `LUMEN_HARDWARE_RAY_TRACING_ENTRY(LumenSceneDirectLightingHardwareRayTracing)` — stage: **raygeneration\|compute(inline)** _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_

#### Global resources (textures / buffers / samplers) (17)

- L34 _resource_ `Buffer<uint> DispatchLightTilesIndirectArgs;`
- L35 _resource_ `RWBuffer<uint> RWHardwareRayTracingIndirectArgs;`
- L58 _resource_ `RaytracingAccelerationStructure TLAS;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L59 _resource_ `RaytracingAccelerationStructure FarFieldTLAS;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L62 _resource_ `StructuredBuffer<FHitGroupRootConstants> HitGroupData;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING && LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L63 _resource_ `StructuredBuffer<FRayTracingSceneMetadataRecord> RayTracingSceneMetadata;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING && LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L64 _resource_ `RWStructuredBuffer<uint> RWInstanceHitCountBuffer;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING && LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L67 _resource_ `Buffer<uint2> ShadowTraceTileData;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L68 _resource_ `Buffer<int> VirtualShadowMapIds;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L84 _resource_ `StructuredBuffer<uint> LightTileAllocator;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L85 _resource_ `StructuredBuffer<uint2> LightTiles;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L97 _resource_ `StructuredBuffer<uint> ShadowTraceAllocator;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L98 _resource_ `StructuredBuffer<uint> ShadowTraces;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L101 _resource_ `StructuredBuffer<uint> CompactedLightSampleData;` — Only used by the stochastic lighting _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L102 _resource_ `StructuredBuffer<uint> CompactedLightSampleAllocator;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L103 _resource_ `Texture2D<float4> LumenSceneData;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L104 _resource_ `RWTexture2DArray<uint> RWLightSamples;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_

#### Global parameters (uniforms) (13)

- L36 _parameter_ `uint2 OutputThreadGroupSize;`
- L37 _parameter_ `uint bStochastic;`
- L70 _parameter_ `uint MaxTraversalIterations;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L71 _parameter_ `uint MeshSectionVisibilityTest;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L72 _parameter_ `uint ViewIndex;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L74 _parameter_ `uint LumenLightType;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L75 _parameter_ `float MaxTraceDistance;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L76 _parameter_ `float FarFieldMaxTraceDistance;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L78 _parameter_ `float FarFieldBias;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L79 _parameter_ `float HardwareRayTracingEndBias;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L80 _parameter_ `float HardwareRayTracingShadowRayBias;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L81 _parameter_ `float HeightfieldShadowReceiverBias;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L82 _parameter_ `float HeightfieldProjectionBiasSearchRadius;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_

#### Functions (4)

- L87-90 _function_ `bool IsRayOccluded(FLumenMinimalRayResult RayResult)` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L92-95 _function_ `bool IsRayOccluded(FRayTracedLightingResult RayResult)` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L106-110 _function_ `FLumenLight GetLumenLightData(uint LightIndex, uint ViewIndex)` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L116-147 _function_ `FLightSampleTrace GetLightSampleTrace(float3 TranslatedWorldPosition, uint LocalLightIndex, uint2 SampleCoord, uint ViewIndex)` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING && USE_STOCHASTIC]_

### `Shaders/Private/Lumen/LumenSceneDirectLightingPerLightShadowCommon.ush` (Private)

- lines: 67; parse: all-branches
- includes: L5 `LumenSceneDirectLighting.ush`

#### Macros (#define, 4)

- L8 `#define THREADGROUP_SIZE_X 8` _[#if THREADGROUP_SIZE_32]_
- L9 `#define THREADGROUP_SIZE_Y 4` _[#if THREADGROUP_SIZE_32]_
- L11 `#define THREADGROUP_SIZE_X 8` _[#if !(THREADGROUP_SIZE_32)]_
- L12 `#define THREADGROUP_SIZE_Y 8` _[#if !(THREADGROUP_SIZE_32)]_
- L3 #pragma `once`

#### Global resources (textures / buffers / samplers) (2)

- L15 _resource_ `StructuredBuffer<uint2> LightTiles;`
- L16 _resource_ `StructuredBuffer<uint> LightTileOffsetsPerLight;`

#### Global parameters (uniforms) (5)

- L17 _parameter_ `uint LightIndex;`
- L18 _parameter_ `uint ViewIndex;`
- L19 _parameter_ `uint NumViews;`
- L20 _parameter_ `int bUseLightTilesPerLightType;`
- L23 _parameter_ `uint DummyZeroForFixingShaderCompilerBug;` — Workaround for a console shader compiler bug generating incorrect code. Likely can be removed in next SDK.

#### groupshared (1)

- L26 _groupshared_ `groupshared uint SharedShadowMask[(SHADOW_MASK_RAY_BITS * THREADGROUP_SIZE_X * THREADGROUP_SIZE_Y) / 32];` — 8 bits per texel

#### Functions (2)

- L28-41 _function_ `void ReadSharedShadowMaskRay(uint2 CoordInCardTile, inout FShadowMaskRay ShadowMaskRay)`
- L43-67 _function_ `void WriteSharedShadowMaskRay(FShadowMaskRay Ray, uint2 CoordInCardTile, const bool bClearExistingMask)`

### `Shaders/Private/Lumen/LumenSceneDirectLightingShadowMask.usf` (Private)

- lines: 297; parse: all-branches
- includes: L10 `../Common.ush`, L11 `LumenCardCommon.ush`, L12 `LumenCardTile.ush`, L13 `LumenCardTileShadowDownsampleFactor.ush`, L15 `../DeferredLightingCommon.ush`, L16 `../VolumeLightingCommon.ush`, L17 `../ForwardShadowingCommon.ush`, L18 `../LightDataUniforms.ush`, L19 `SurfaceCache/LumenSurfaceCache.ush`, L21 `/Engine/Generated/Material.ush` [LIGHT_FUNCTION], L22 `../LightFunctionCommon.ush` [LIGHT_FUNCTION], L24 `LumenSceneDirectLightingPerLightShadowCommon.ush`, L26 `../VolumetricCloudCommon.ush` [USE_CLOUD_TRANSMITTANCE]

#### Macros (#define, 4)

- L4 `#define VIRTUAL_SHADOW_MAP 0` _[#if !defined(VIRTUAL_SHADOW_MAP)]_
- L7 `#define DENSE_SHADOW_MAP 0` _[#if !defined(DENSE_SHADOW_MAP)]_
- L14 `#define SUPPORT_CONTACT_SHADOWS 0`
- L29 `#define ADAPTIVE_SHADOW_TRACING_USE_WAVE_OP (FEATURE_LEVEL >= FEATURE_LEVEL_SM6 \|\| PLATFORM_SUPPORTS_SM6_0_WAVE_OPERATIONS)`

#### Entry points (1)

- L80-295 _entry_ `[numthreads(THREADGROUP_SIZE_X, THREADGROUP_SIZE_Y, 1)] void LumenSceneDirectLightingShadowMaskFromLightAttenuationCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FLumenDirectLightingShadowMaskFromLightAttenuationCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenSceneDirectLighting.cpp:875) — C++: `FLumenDirectLightingShadowMaskFromLightAttenuationWithLightFunctionCS` SF_Compute via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/Lumen/LumenSceneDirectLighting.cpp:936)

#### Global resources (textures / buffers / samplers) (2)

- L31 _resource_ `RWStructuredBuffer<uint> RWShadowTraces;`
- L32 _resource_ `RWStructuredBuffer<uint> RWShadowTraceAllocator;`

#### Global parameters (uniforms) (2)

- L34 _parameter_ `float HeightfieldShadowReceiverBias;`
- L35 _parameter_ `int bAdaptiveShadowTracing;`

#### groupshared (4)

- L37 _groupshared_ `groupshared uint SharedNumShadowTraces;`
- L38 _groupshared_ `groupshared uint SharedShadowTraces[THREADGROUP_SIZE_X * THREADGROUP_SIZE_Y];`
- L39 _groupshared_ `groupshared uint SharedGlobalShadowTraceOffset;`
- L41 _groupshared_ `groupshared uint bSharedAllTexelsInQuadWriteTrace[(THREADGROUP_SIZE_X / 2) * (THREADGROUP_SIZE_Y / 2)];`

#### Functions (1)

- L43-78 _function_ `uint ComputeTileTraceDownsampleLevel(uint2 GroupThreadId, bool bWriteTrace, bool bTileHasUniformlyVisibility)`

### `Shaders/Private/Lumen/LumenSceneDirectLightingSoftwareRayTracing.usf` (Private)

- lines: 256; parse: all-branches
- includes: L7 `../Common.ush`, L8 `LumenCardCommon.ush`, L9 `LumenCardTile.ush`, L11 `../DeferredLightingCommon.ush`, L12 `../VolumeLightingCommon.ush`, L13 `../ForwardShadowingCommon.ush`, L14 `../LightGridCommon.ush`, L17 `LumenTracingCommon.ush`, L18 `LumenSoftwareRayTracing.ush`, L19 `../DistanceFieldShadowingShared.ush`, L20 `LumenSceneDirectLightingPerLightShadowCommon.ush`, L21 `../LightDataUniforms.ush`

#### Macros (#define, 4)

- L4 `#define THREADGROUP_SIZE 1` _[#if !defined(THREADGROUP_SIZE)]_
- L10 `#define SUPPORT_CONTACT_SHADOWS 0`
- L15 `#define DISTANCE_FIELD_IN_VIEW_UB 1`
- L16 `#define DF_SHADOW_QUALITY 2`

#### Entry points (2)

- L153-237 _entry_ `[numthreads(THREADGROUP_SIZE_X, THREADGROUP_SIZE_Y, 1)] void LumenSceneDirectLightingTraceDistanceFieldShadowsCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FLumenSceneDirectLightingTraceDistanceFieldShadowsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenSceneDirectLighting.cpp:1053) _[#if defined(LIGHT_TYPE)]_
- L243-256 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void InitShadowTraceIndirectArgsCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FInitShadowTraceIndirectArgsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenSceneDirectLighting.cpp:965)

#### Global resources (textures / buffers / samplers) (2)

- L240 _resource_ `RWBuffer<uint> RWShadowTraceIndirectArgs;`
- L241 _resource_ `StructuredBuffer<uint> ShadowTraceAllocator;`

#### Global parameters (uniforms) (5)

- L24 _parameter_ `float HeightfieldShadowRayBias;` — Bias
- L25 _parameter_ `float MeshSDFShadowRayBias;`
- L26 _parameter_ `float GlobalSDFShadowRayBias;`
- L28 _parameter_ `float MaxTraceDistance;`
- L29 _parameter_ `float SDFSurfaceBiasScale;`

#### Functions (2)

- L31-70 _function_ `float ShadowTraceHeightfield( float3 WorldRayStart, float3 TranslatedWorldRayStart, float3 WorldRayDirection, float MaxTraceDistance)`
- L72-150 _function_ `float TraceOffscreenShadows(FLumenCardData CardData, uint2 TexelCoord, float3 WorldPosition, float3 TranslatedWorldPosition, float3 L, float3 ToLight, float3 WorldNormal, bool bLocalLight)`

### `Shaders/Private/Lumen/LumenSceneDirectLightingStochastic.usf` (Private)

- lines: 1080; parse: all-branches
- includes: L17 `../Common.ush`, L18 `../BlueNoise.ush`, L19 `LumenSceneDirectLightingStochastic.ush`, L20 `../MegaLights/MegaLightsRayTracing.ush`, L21 `../DeferredLightingCommon.ush`, L22 `../IntersectionUtils.ush`, L23 `../ShaderPrint.ush`, L27 `/Engine/Generated/Material.ush` [SHADER_STANDALONE_EVALUATE && LIGHT_FUNCTION], L28 `../LightFunctionCommon.ush` [SHADER_STANDALONE_EVALUATE && LIGHT_FUNCTION], L31 `../VolumetricCloudCommon.ush` [SHADER_STANDALONE_EVALUATE && USE_CLOUD_TRANSMITTANCE], L35 `LumenCardCommon.ush`, L36 `LumenCardTile.ush`, L37 `LumenSceneLighting.ush`, L38 `LumenSceneDirectLighting.ush`, L39 `SurfaceCache/LumenSurfaceCache.ush`, L564 `../PackUnpack.ush` [SHADER_COMPACTION]

#### Macros (#define, 8)

- L4 `#define NUM_SAMPLES_PER_PIXEL_1D 1` _[#if !defined(NUM_SAMPLES_PER_PIXEL_1D)]_
- L7 `#define SUPPORT_CONTACT_SHADOWS 0`
- L10 `#define USE_RECT_LIGHT 0` _[#if !defined(USE_RECT_LIGHT)]_
- L14 `#define USE_SOURCE_TEXTURE 1` _[#if USE_RECT_LIGHT]_
- L244 `#define DEBUG_ENABLE 0` _[#if SHADER_GENERATE_SAMPLE]_
- L249 `#define THREADGROUP_COUNT 64` _[#if SHADER_GENERATE_SAMPLE]_
- L434 `#define DEDUPLICATE_SAMPLE 0` _[#if SHADER_GENERATE_SAMPLE]_
- L718 `#define DEBUG_ENABLE 0` _[#if SHADER_SHADING]_

#### Entry points (7)

- L253-556 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void GenerateLightSamplesCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint LinearThreadIndex : SV_GroupIndex, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FLumenSceneGenerateLightSamplesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenSceneDirectLightingStochastic.inl:347) — Run one thread per sample and generate new light samples for tracing _[#if SHADER_GENERATE_SAMPLE]_
- L584-678 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void CompactLightSampleTracesCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FLumenSceneCompactLightSampleTracesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenSceneDirectLightingStochastic.inl:455) _[#if SHADER_COMPACTION]_
- L734-781 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void ShadeLightSamplesCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FLumenSceneShadeLightSamplesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenSceneDirectLightingStochastic.inl:398) _[#if SHADER_SHADING]_
- L865-933 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void DenoiserTemporalCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FLumenSceneDenoiserTemporalCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenSceneDirectLightingStochastic.inl:511) _[#if SHADER_TEMPORAL_DENOISER]_
- L948-964 _entry_ `[numthreads(1, 1, 1)] void MainCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FLumenSceneCompactLightOffsetCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenSceneDirectLightingStochastic.inl:100) — C++: `FLumenSceneCompactLightListCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenSceneDirectLightingStochastic.inl:139) — C++: `FLumenSceneEvaluateStandaloneLightMaterialCS` SF_Compute via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/Lumen/LumenSceneDirectLightingStochastic.inl:208) — C++: `FLumenSceneEvaluateStandaloneLightCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenSceneDirectLightingStochastic.inl:263) _[#if SHADER_STANDALONE_COMPACT_OFFSET]_
- L978-1003 _entry_ `[numthreads(1, 1, 1)] void MainCS( uint3 GroupId : SV_GroupID, uint LinearThreadIndex : SV_GroupIndex, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FLumenSceneCompactLightOffsetCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenSceneDirectLightingStochastic.inl:100) — C++: `FLumenSceneCompactLightListCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenSceneDirectLightingStochastic.inl:139) — C++: `FLumenSceneEvaluateStandaloneLightMaterialCS` SF_Compute via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/Lumen/LumenSceneDirectLightingStochastic.inl:208) — C++: `FLumenSceneEvaluateStandaloneLightCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenSceneDirectLightingStochastic.inl:263) _[#if SHADER_STANDALONE_COMPACT_LIST]_
- L1020-1079 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void MainCS( uint3 GroupId : SV_GroupID, uint LinearThreadIndex : SV_GroupIndex, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FLumenSceneCompactLightOffsetCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenSceneDirectLightingStochastic.inl:100) — C++: `FLumenSceneCompactLightListCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenSceneDirectLightingStochastic.inl:139) — C++: `FLumenSceneEvaluateStandaloneLightMaterialCS` SF_Compute via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/Lumen/LumenSceneDirectLightingStochastic.inl:208) — C++: `FLumenSceneEvaluateStandaloneLightCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenSceneDirectLightingStochastic.inl:263) _[#if SHADER_STANDALONE_EVALUATE]_

#### Structs / classes (3)

- L47-53 _struct_ **`FTransientCoord`** `struct FTransientCoord` — Transient atlas coord used for storing card tile data during the update pass. The coord are only valid for the current frame. These atlas coords are allocated with a simple linear allocator
  - L49 _member_ `uint2 TileCoord;`
  - L50 _member_ `uint2 TexelCoord;`
  - L51 _member_ `uint2 BaseTexelCoord;`
  - L52 _member_ `uint2 TexelCoordWithinTile;`
- L87-91 _struct_ **`FLightTargetPDF`** `struct FLightTargetPDF`
  - L89 _member_ `float3 Diffuse;`
  - L90 _member_ `float Weight;`
- L806-811 _struct_ **`FNeighborhood`** `struct FNeighborhood` _[#if SHADER_TEMPORAL_DENOISER]_
  - L808 _member_ `float3 Mean;` _[#if SHADER_TEMPORAL_DENOISER]_
  - L809 _member_ `float3 ClampMin;` _[#if SHADER_TEMPORAL_DENOISER]_
  - L810 _member_ `float3 ClampMax;` _[#if SHADER_TEMPORAL_DENOISER]_

#### Global resources (textures / buffers / samplers) (48)

- L219 _resource_ `RWTexture2D<float4> RWSceneData;` _[#if SHADER_GENERATE_SAMPLE]_
- L220 _resource_ `RWTexture2D<uint> RWUniqueLightIndices;` _[#if SHADER_GENERATE_SAMPLE]_
- L221 _resource_ `RWTexture2D<uint> RWUniqueLightCount;` _[#if SHADER_GENERATE_SAMPLE]_
- L222 _resource_ `RWStructuredBuffer<uint> RWCardTilePerLightCounters;` _[#if SHADER_GENERATE_SAMPLE]_
- L224 _resource_ `RWTexture2D<float> RWDiffuseLighting;` _[#if SHADER_GENERATE_SAMPLE]_
- L225 _resource_ `RWTexture2D<float> RWSampleLuminanceSum;` _[#if SHADER_GENERATE_SAMPLE]_
- L226 _resource_ `RWTexture2DArray<uint> RWLightSamples;` _[#if SHADER_GENERATE_SAMPLE]_
- L227 _resource_ `RWTexture2DArray<float4> RWSampleDiffuseLighting;` _[#if SHADER_GENERATE_SAMPLE]_
- L240 _resource_ `StructuredBuffer<uint> TileAllocator;` _[#if SHADER_GENERATE_SAMPLE]_
- L241 _resource_ `StructuredBuffer<uint> TileData;` _[#if SHADER_GENERATE_SAMPLE]_
- L242 _resource_ `StructuredBuffer<uint> LumenSceneDebugData;` _[#if SHADER_GENERATE_SAMPLE]_
- L567 _resource_ `Texture2DArray<uint> LightSamples;` _[#if SHADER_COMPACTION]_
- L568 _resource_ `RWStructuredBuffer<uint> RWCompactedTraceTexelData;` _[#if SHADER_COMPACTION]_
- L569 _resource_ `RWStructuredBuffer<uint> RWCompactedTraceTexelAllocator;` _[#if SHADER_COMPACTION]_
- L686 _resource_ `SamplerState BilinearClampedSampler;` _[#if SHADER_SHADING \|\| SHADER_TEMPORAL_DENOISER]_
- L687 _resource_ `RWTexture2D<float3> RWFinalLightingAtlas;` _[#if SHADER_SHADING \|\| SHADER_TEMPORAL_DENOISER]_
- L688 _resource_ `RWTexture2D<float3> RWDirectLightingAtlas;` _[#if SHADER_SHADING \|\| SHADER_TEMPORAL_DENOISER]_
- L691 _resource_ `Texture2D DirectLightingAtlas;` _[#if SHADER_SHADING \|\| SHADER_TEMPORAL_DENOISER]_
- L692 _resource_ `Texture2D IndirectLightingAtlas;` _[#if SHADER_SHADING \|\| SHADER_TEMPORAL_DENOISER]_
- L693 _resource_ `Texture2D AlbedoAtlas;` _[#if SHADER_SHADING \|\| SHADER_TEMPORAL_DENOISER]_
- L694 _resource_ `Texture2D EmissiveAtlas;` _[#if SHADER_SHADING \|\| SHADER_TEMPORAL_DENOISER]_
- L723 _resource_ `StructuredBuffer<uint> TileAllocator;` _[#if SHADER_SHADING]_
- L724 _resource_ `StructuredBuffer<uint> TileData;` _[#if SHADER_SHADING]_
- L726 _resource_ `Texture2DArray<float4> SampleDiffuseLighting;` _[#if SHADER_SHADING && USE_LIGHT_SAMPLES]_
- L727 _resource_ `Texture2DArray<uint> LightSamples;` _[#if SHADER_SHADING && USE_LIGHT_SAMPLES]_
- L729 _resource_ `StructuredBuffer<uint> LumenSceneDebugData;` _[#if SHADER_SHADING]_
- L790 _resource_ `Texture2D<float2> SampleLuminanceSumTexture;` _[#if SHADER_TEMPORAL_DENOISER]_
- L791 _resource_ `Texture2D ResolvedDirectLightingAtlas;` _[#if SHADER_TEMPORAL_DENOISER]_
- L792 _resource_ `Texture2D DiffuseLightingAndSecondMomentHistoryTexture;` _[#if SHADER_TEMPORAL_DENOISER]_
- L793 _resource_ `Texture2D<UNORM float> NumFramesAccumulatedHistoryTexture;` _[#if SHADER_TEMPORAL_DENOISER]_
- L800 _resource_ `RWTexture2D<float4> RWDiffuseLightingAndSecondMoment;` _[#if SHADER_TEMPORAL_DENOISER]_
- L801 _resource_ `RWTexture2D<UNORM float> RWNumFramesAccumulated;` _[#if SHADER_TEMPORAL_DENOISER]_
- L803 _resource_ `StructuredBuffer<uint> TileAllocator;` _[#if SHADER_TEMPORAL_DENOISER]_
- L804 _resource_ `StructuredBuffer<uint> TileData;` _[#if SHADER_TEMPORAL_DENOISER]_
- L944 _resource_ `StructuredBuffer<uint> CardTilePerLightCounters;` _[#if SHADER_STANDALONE_COMPACT_OFFSET]_
- L945 _resource_ `RWStructuredBuffer<uint> RWCardTilePerLightOffsets;` _[#if SHADER_STANDALONE_COMPACT_OFFSET]_
- L946 _resource_ `RWBuffer<uint> RWCardTilePerLightArgs;` _[#if SHADER_STANDALONE_COMPACT_OFFSET]_
- L972 _resource_ `Texture2D<uint> UniqueLightCount;` _[#if SHADER_STANDALONE_COMPACT_LIST]_
- L973 _resource_ `Texture2D<uint> UniqueLightIndices;` _[#if SHADER_STANDALONE_COMPACT_LIST]_
- L974 _resource_ `StructuredBuffer<uint> CardTilePerLightOffsets;` _[#if SHADER_STANDALONE_COMPACT_LIST]_
- L975 _resource_ `RWStructuredBuffer<uint> RWCardTilePerLightCounters;` _[#if SHADER_STANDALONE_COMPACT_LIST]_
- L976 _resource_ `RWStructuredBuffer<uint> RWCardTilePerLightDatas;` _[#if SHADER_STANDALONE_COMPACT_LIST]_
- L1013 _resource_ `StructuredBuffer<uint> CardTilePerLightCounters;` _[#if SHADER_STANDALONE_EVALUATE]_
- L1014 _resource_ `StructuredBuffer<uint> CardTilePerLightOffsets;` _[#if SHADER_STANDALONE_EVALUATE]_
- L1015 _resource_ `StructuredBuffer<uint> CardTilePerLightDatas;` _[#if SHADER_STANDALONE_EVALUATE]_
- L1016 _resource_ `Texture2D<float4> LumenSceneData;` _[#if SHADER_STANDALONE_EVALUATE]_
- L1017 _resource_ `RWTexture2DArray<uint> RWLightSamples;` _[#if SHADER_STANDALONE_EVALUATE]_
- L1018 _resource_ `RWTexture2DArray<float4> RWSampleDiffuseLighting;` _[#if SHADER_STANDALONE_EVALUATE]_

#### Global parameters (uniforms) (24)

- L211 _parameter_ `uint MaxCompositeTiles;` _[#if SHADER_GENERATE_SAMPLE]_
- L212 _parameter_ `float SamplingMinWeight;` _[#if SHADER_GENERATE_SAMPLE]_
- L213 _parameter_ `uint NumSamplesPerPixel1d;` _[#if SHADER_GENERATE_SAMPLE]_
- L214 _parameter_ `uint NumLights;` _[#if SHADER_GENERATE_SAMPLE]_
- L215 _parameter_ `uint NumStandaloneLights;` _[#if SHADER_GENERATE_SAMPLE]_
- L216 _parameter_ `uint NumViews;` _[#if SHADER_GENERATE_SAMPLE]_
- L217 _parameter_ `uint StateFrameIndex;` _[#if SHADER_GENERATE_SAMPLE]_
- L229 _parameter_ `float4 HistoryScreenPositionScaleBias;` _[#if SHADER_GENERATE_SAMPLE]_
- L230 _parameter_ `float4 HistoryUVMinMax;` _[#if SHADER_GENERATE_SAMPLE]_
- L233 _parameter_ `uint DummyZeroForFixingShaderCompilerBug;` — Workaround for a console shader compiler bug generating incorrect code. Likely can be removed in next SDK. _[#if SHADER_GENERATE_SAMPLE]_
- L566 _parameter_ `int2 SampleViewSize;` _[#if SHADER_COMPACTION]_
- L690 _parameter_ `float2 IndirectLightingAtlasHalfTexelSize;` _[#if SHADER_SHADING \|\| SHADER_TEMPORAL_DENOISER]_
- L721 _parameter_ `uint NumSamplesPerPixel1d;` — Workaround for a console shader compiler bug generating incorrect code. Likely can be removed in next SDK. _[#if SHADER_SHADING]_
- L722 _parameter_ `uint DummyZeroForFixingShaderCompilerBug;` _[#if SHADER_SHADING]_
- L788 _parameter_ `uint DummyZeroForFixingShaderCompilerBug;` _[#if SHADER_TEMPORAL_DENOISER]_
- L795 _parameter_ `float PrevSceneColorPreExposureCorrection;` _[#if SHADER_TEMPORAL_DENOISER]_
- L796 _parameter_ `float TemporalMaxFramesAccumulated;` _[#if SHADER_TEMPORAL_DENOISER]_
- L797 _parameter_ `float TemporalNeighborhoodClampScale;` _[#if SHADER_TEMPORAL_DENOISER]_
- L798 _parameter_ `uint TemporalAdvanceFrame;` _[#if SHADER_TEMPORAL_DENOISER]_
- L941 _parameter_ `uint NumLights;` _[#if SHADER_STANDALONE_COMPACT_OFFSET]_
- L942 _parameter_ `uint NumStandaloneLights;` _[#if SHADER_STANDALONE_COMPACT_OFFSET]_
- L943 _parameter_ `uint NumSamplesPerPixel1d;` _[#if SHADER_STANDALONE_COMPACT_OFFSET]_
- L1011 _parameter_ `uint LightIndex;` _[#if SHADER_STANDALONE_EVALUATE]_
- L1012 _parameter_ `uint ViewIndex;` _[#if SHADER_STANDALONE_EVALUATE]_

#### groupshared (8)

- L235 _groupshared_ `groupshared uint SharedCandidateLightCount;` _[#if SHADER_GENERATE_SAMPLE]_
- L236 _groupshared_ `groupshared uint SharedCandidateLightHiMask;` _[#if SHADER_GENERATE_SAMPLE]_
- L237 _groupshared_ `groupshared uint SharedCandidateLightMask[SHARED_LIGHT_MASK_SIZE];` _[#if SHADER_GENERATE_SAMPLE]_
- L238 _groupshared_ `groupshared uint SharedStandaloneLightMask[SHARED_LIGHT_MASK_SIZE];` _[#if SHADER_GENERATE_SAMPLE]_
- L571 _groupshared_ `groupshared uint SharedGlobalTraceTexelStartOffset;` _[#if SHADER_COMPACTION]_
- L574 _groupshared_ `groupshared uint SharedGroupSum;` _[#if SHADER_COMPACTION && WAVE_OPS]_
- L577 _groupshared_ `groupshared uint SharedTraceTexelAllocator;` — @todo - ordered compaction for non-wave ops path _[#if SHADER_COMPACTION && !(WAVE_OPS)]_
- L578 _groupshared_ `groupshared uint SharedTraceTexels[THREADGROUP_SIZE * THREADGROUP_SIZE];` _[#if SHADER_COMPACTION && !(WAVE_OPS)]_

#### Functions (10)

- L55-59 _function_ `uint2 GetTile1dToTile2D(uint LinearTileIndex)`
- L61-69 _function_ `FTransientCoord GetTransientCoord(uint LinearTileIndex, uint2 GroupThreadId)`
- L72-85 _function_ `FShaderPrintContext InitDebugContext(StructuredBuffer<uint> InLumenSceneDebugData, FCardTileData InCardTile, FLumenCardPageData InCardPage, float2 InAtlasUV, uint2 InStartCoord = uint2(50, 50))` — Init debug context for the texel under the mouse cursor
- L93-99 _function_ `FLightTargetPDF InitLightTargetPDF()`
- L101-126 _function_ `FLightTargetPDF GetLocalLightTargetPDF(FDeferredLightData LightData, float3 TranslatedWorldPosition, float3 WorldNormal, float Exposure)`
- L129-133 _function_ `FLumenLight GetLumenLightData(uint LightIndex, uint ViewIndex)` _[#if SHADER_GENERATE_SAMPLE \|\| SHADER_SHADING]_
- L140-209 _function_ `bool DoesLightAffectCardPageUVRange(FLumenLight LumenLight, FLumenCardPageData CardPage, FLumenCardData Card, float2 UVMin, float2 UVMax, inout float3 OutCardPageWorldCenter)` _[#if SHADER_GENERATE_SAMPLE]_
- L696-710 _function_ `float3 GetFinalLighting(float2 AtlasUV, float3 DirectLighting, FLumenCardPageData CardPage)` _[#if SHADER_SHADING \|\| SHADER_TEMPORAL_DENOISER]_
- L813-853 _function_ `FNeighborhood GetNeighborhood( uint2 BaseTexelCoord, uint2 TexelCoordWithinTile, Texture2D SampleTexture, float3 CenterSample, float2 CardPageMinInPixels, float2 CardPageMaxInPixels)` _[#if SHADER_TEMPORAL_DENOISER]_
- L855-863 _function_ `float3 ClampLuminance(float3 Lighting, float LuminanceClamp)` _[#if SHADER_TEMPORAL_DENOISER]_

#### Top-level macro invocations (1)

- L582 _macro_call_ `WAVESIZE(32)` _[#if SHADER_COMPACTION && COMPILER_SUPPORTS_WAVE_SIZE && WAVE_OPS]_

### `Shaders/Private/Lumen/LumenSceneDirectLightingStochastic.ush` (Private)

- lines: 67; parse: all-branches
- includes: L3 `../LightGridCommon.ush`, L6 `../DeferredLightingCommon.ush`

#### Macros (#define, 6)

- L4 `#define SUPPORT_CONTACT_SHADOWS 0`
- L5 `#define NON_DIRECTIONAL_DIRECT_LIGHTING 0`
- L8 `#define DOWNSAMPLE_FACTOR 2`
- L9 `#define MAX_LOCAL_LIGHT_NUM 1024`
- L10 `#define MAX_LOCAL_LIGHT_INDEX (MAX_LOCAL_LIGHT_NUM - 1)`
- L11 `#define SHARED_LIGHT_MASK_SIZE (MAX_LOCAL_LIGHT_NUM / 32)`

#### Structs / classes (1)

- L13-19 _struct_ **`FLightSample`** `struct FLightSample`
  - L15 _member_ `uint LocalLightIndex;`
  - L16 _member_ `float Weight;`
  - L17 _member_ `bool bVisible;`
  - L18 _member_ `bool bCompleted;`

#### Global parameters (uniforms) (2)

- L50 _parameter_ `uint MegaLightsStateFrameIndex;`
- L51 _parameter_ `uint DownsampleFactorMultShift;`

#### Functions (4)

- L21-29 _function_ `FLightSample InitLightSample()`
- L31-38 _function_ `uint PackLightSample(FLightSample LightSample)`
- L40-48 _function_ `FLightSample UnpackLightSample(uint PackedLightSample)`
- L56-67 _function_ `uint2 GetSampleScreenCoordJitter(uint2 DownsampledScreenCoord)` — Returns sample jitter offset in the range [0, DOWNSAMPLE_FACTOR - 1]

### `Shaders/Private/Lumen/LumenSceneLighting.usf` (Private)

- lines: 735; parse: all-branches
- includes: L7 `../Common.ush`, L8 `../BRDF.ush`, L9 `LumenFloatQuantization.ush`, L10 `LumenCardCommon.ush`, L11 `LumenCardTile.ush`, L12 `LumenCardTileShadowDownsampleFactor.ush`, L13 `LumenSceneLighting.ush`, L14 `SurfaceCache/LumenSurfaceCacheSampling.ush`, L15 `Radiosity/LumenRadiosity.ush`

#### Macros (#define, 1)

- L18 `#define THREADGROUP_SIZE 1` _[#if !defined(THREADGROUP_SIZE)]_

#### Entry points (11)

- L57-83 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void ClearCardUpdateContextCS( uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FClearCardUpdateContextCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenSceneLighting.cpp:343) — Batch clear all resources required for the subsequent card context update pass
- L189-208 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void BuildPageUpdatePriorityHistogramCS( uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FBuildPageUpdatePriorityHistogramCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenSceneLighting.cpp:394) — Iterate over all pages and build a histogram of card update priorities
- L238-252 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void SelectMaxUpdateBucketCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FSelectMaxUpdateBucketCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenSceneLighting.cpp:427) — Compute max bucket histogram to update and how many tiles should be updated in that last bucket
- L308-366 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void BuildCardsUpdateListCS( uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FBuildCardsUpdateListCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenSceneLighting.cpp:480) — Iterate over all cards and pick first N for update based on the histogram max update bucket
- L377-414 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void SetCardPageIndexIndirectArgsCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FSetCardPageIndexIndirectArgsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenSceneLighting.cpp:514)
- L424-469 _entry_ `void RasterizeToCardsVS( uint VertexId : SV_VertexID, uint InstanceId : SV_InstanceID, out FCardVSToPS CardInterpolants, out float4 OutPosition : SV_POSITION )` — stage: **vertex (from C++ binding)** — C++: `FRasterizeToCardsVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenSceneLighting.cpp:136)
- L476-507 _entry_ `[numthreads(CARD_TILE_SIZE, CARD_TILE_SIZE, 1)] void CombineLumenSceneLightingCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FLumenCardCombineLightingCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenSceneLighting.cpp:167)
- L509-521 _entry_ `void ClearLumenCardsPS( out float4 Target0 : SV_Target0 ,out float4 Target1 : SV_Target1 )` — stage: **pixel (from C++ binding)** — C++: `FClearLumenCardsPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenSceneLighting.cpp:128)
- L523-532 _entry_ `void ClearLumenCardCapturePS( out float4 OutAlbedo : SV_Target0, out float4 OutNormals : SV_Target1, out float4 OutEmissive : SV_Target2 )` — stage: **pixel (from C++ binding)** — C++: `FClearLumenCardCapturePS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenSceneRendering.cpp:2363)
- L553-674 _entry_ `[numthreads(CARD_TILE_SIZE, CARD_TILE_SIZE, 1)] void ResampleLightingHistoryToCardCaptureAtlasCS(uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FResampleLightingHistoryToCardCaptureAtlasCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenSceneRendering.cpp:1756) _[#if defined(ResampleLightingHistoryToCardCaptureAtlasCS)]_
- L688-734 _entry_ `void CopyCardCaptureLightingToAtlasPS( float4 SvPosition : SV_POSITION, float2 AtlasUV : TEXCOORD0, out float4 OutDirectLightingAtlas : SV_Target0, out float4 OutFinalLightingAtlas : SV_Target1 , out float4 OutRadiosityAtlas : SV_Target2 )` — stage: **pixel (from C++ binding)** — C++: `FCopyCardCaptureLightingToAtlasPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenSceneLighting.cpp:129)

#### Global resources (textures / buffers / samplers) (38)

- L21 _resource_ `RWStructuredBuffer<float4> RWCardPageBuffer;`
- L22 _resource_ `StructuredBuffer<uint> CardPageLastUsedBuffer;`
- L23 _resource_ `StructuredBuffer<uint> CardPageHighResLastUsedBuffer;`
- L25 _resource_ `RWStructuredBuffer<uint> RWDirectLightingCardPageIndexAllocator;`
- L26 _resource_ `RWStructuredBuffer<uint> RWDirectLightingCardPageIndexData;`
- L28 _resource_ `RWStructuredBuffer<uint> RWIndirectLightingCardPageIndexAllocator;`
- L29 _resource_ `RWStructuredBuffer<uint> RWIndirectLightingCardPageIndexData;`
- L31 _resource_ `RWStructuredBuffer<uint> RWPriorityHistogram;`
- L32 _resource_ `StructuredBuffer<uint> PriorityHistogram;`
- L34 _resource_ `RWStructuredBuffer<uint> RWMaxUpdateBucket;`
- L35 _resource_ `StructuredBuffer<uint> MaxUpdateBucket;`
- L37 _resource_ `RWStructuredBuffer<uint> RWCardPageTileAllocator;`
- L38 _resource_ `StructuredBuffer<uint> CardPageTileAllocator;`
- L368 _resource_ `RWBuffer<uint> RWDirectLightingDrawCardPageIndicesIndirectArgs;`
- L369 _resource_ `RWBuffer<uint> RWDirectLightingDispatchCardPageIndicesIndirectArgs;`
- L370 _resource_ `RWBuffer<uint> RWIndirectLightingDrawCardPageIndicesIndirectArgs;`
- L371 _resource_ `RWBuffer<uint> RWIndirectLightingDispatchCardPageIndicesIndirectArgs;`
- L373 _resource_ `StructuredBuffer<uint> DirectLightingCardPageIndexAllocator;`
- L374 _resource_ `StructuredBuffer<uint> IndirectLightingCardPageIndexAllocator;`
- L416 _resource_ `RWStructuredBuffer<uint> RWQuadAllocator;`
- L417 _resource_ `RWStructuredBuffer<uint> RWQuadData;`
- L419 _resource_ `StructuredBuffer<uint> CardPageIndexAllocator;`
- L420 _resource_ `StructuredBuffer<uint> CardPageIndexData;`
- L471 _resource_ `SamplerState BilinearClampedSampler;`
- L472 _resource_ `StructuredBuffer<uint> CardTiles;`
- L473 _resource_ `RWTexture2D<float3> RWFinalLightingAtlas;`
- L536 _resource_ `Buffer<uint> NewCardTileResampleData;` _[#if defined(ResampleLightingHistoryToCardCaptureAtlasCS)]_
- L537 _resource_ `Buffer<uint4> NewCardPageResampleData;` _[#if defined(ResampleLightingHistoryToCardCaptureAtlasCS)]_
- L538 _resource_ `Buffer<uint4> RectCoordBuffer;` _[#if defined(ResampleLightingHistoryToCardCaptureAtlasCS)]_
- L540 _resource_ `RWTexture2D<float4> RWDirectLightingCardCaptureAtlas;` _[#if defined(ResampleLightingHistoryToCardCaptureAtlasCS)]_
- L541 _resource_ `RWTexture2D<float4> RWRadiosityCardCaptureAtlas;` _[#if defined(ResampleLightingHistoryToCardCaptureAtlasCS)]_
- L542 _resource_ `RWTexture2D<UNORM float> RWRadiosityNumFramesAccumulatedCardCaptureAtlas;` _[#if defined(ResampleLightingHistoryToCardCaptureAtlasCS)]_
- L678 _resource_ `RWTexture2D<UNORM float> RWRadiosityNumFramesAccumulatedAtlas;`
- L680 _resource_ `Texture2D AlbedoCardCaptureAtlas;`
- L681 _resource_ `Texture2D EmissiveCardCaptureAtlas;`
- L682 _resource_ `Texture2D DirectLightingCardCaptureAtlas;`
- L683 _resource_ `Texture2D RadiosityCardCaptureAtlas;`
- L684 _resource_ `Texture2D<UNORM float> RadiosityNumFramesAccumulatedCardCaptureAtlas;`

#### Global parameters (uniforms) (18)

- L40 _parameter_ `float MaxDistanceFromFrustumToPrioritize;`
- L41 _parameter_ `uint FreezeUpdateFrame;`
- L42 _parameter_ `uint CardPageNum;`
- L43 _parameter_ `uint MaxDirectLightingTilesToUpdate;`
- L44 _parameter_ `uint MaxIndirectLightingTilesToUpdate;`
- L45 _parameter_ `float FirstClipmapWorldExtentRcp;`
- L46 _parameter_ `uint IndirectLightingHistoryValid;`
- L47 _parameter_ `uint NumCameraOrigins;`
- L48 _parameter_ `float4 WorldCameraOrigins[LUMEN_MAX_VIEWS];`
- L49 _parameter_ `float4 CameraFrustumPlanes[LUMEN_MAX_VIEWS * LUMEN_MAX_CAMERA_PLANES];`
- L51 _parameter_ `float DirectLightingUpdateFactor;`
- L52 _parameter_ `float IndirectLightingUpdateFactor;`
- L375 _parameter_ `uint VertexCountPerInstanceIndirect;`
- L422 _parameter_ `float2 IndirectLightingAtlasSize;`
- L474 _parameter_ `float2 IndirectLightingAtlasHalfTexelSize;`
- L544 _parameter_ `uint CardCaptureAtlasWidthInTiles;` _[#if defined(ResampleLightingHistoryToCardCaptureAtlasCS)]_
- L685 _parameter_ `uint2 CardCaptureAtlasSizeInTiles;`
- L686 _parameter_ `uint OutputAtlasWidthInTiles;`

#### groupshared (3)

- L546 _groupshared_ `groupshared uint SharedShadowDownsampleFactorLow[CARD_TILE_SIZE * CARD_TILE_SIZE];` _[#if defined(ResampleLightingHistoryToCardCaptureAtlasCS)]_
- L547 _groupshared_ `groupshared uint SharedShadowDownsampleFactorHigh[CARD_TILE_SIZE * CARD_TILE_SIZE];` _[#if defined(ResampleLightingHistoryToCardCaptureAtlasCS)]_
- L548 _groupshared_ `groupshared float SharedRadiosityNumFramesAccumulated[CARD_TILE_SIZE * CARD_TILE_SIZE];` _[#if defined(ResampleLightingHistoryToCardCaptureAtlasCS)]_

#### Functions (8)

- L85-88 _function_ `uint GetMaxTilesToUpdate(uint CardUpdateContext)`
- L90-93 _function_ `uint GetLastLightingUpdateFrameIndex(FLumenCardPageData CardPage, uint CardUpdateContext)`
- L95-98 _function_ `uint GetUpdateFactor(uint CardUpdateContext)`
- L100-103 _function_ `uint GetNumCardPageTiles(FLumenCardPageData CardPage)`
- L105-178 _function_ `uint GetPriorityBucketIndex(FLumenCardData Card, FLumenCardPageData CardPage, uint CardPageIndex, uint CardUpdateContext)`
- L180-184 _function_ `void BuildUpdatePriorityHistogram(FLumenCardData Card, FLumenCardPageData CardPage, uint CardPageIndex, uint NumCardPageTiles, uint CardUpdateContext)`
- L210-233 _function_ `void SelectMaxUpdateBucket(uint CardUpdateContext)`
- L254-303 _function_ `bool BuildCardsUpdateList( FLumenCardData Card, FLumenCardPageData CardPage, uint CardPageIndex, uint NumCardPageTiles, uint CardUpdateContext, RWStructuredBuffer<uint> RWCardPageIndexAllocator, RWStructuredBuffer<uint> RWCardPageIndexData)`

#### Top-level macro invocations (1)

- L551 _macro_call_ `WAVESIZE(WAVE_OP_WAVE_SIZE)` _[#if defined(ResampleLightingHistoryToCardCaptureAtlasCS) && WAVE_OP_WAVE_SIZE > 0 && COMPILER_SUPPORTS_WAVE_SIZE]_

### `Shaders/Private/Lumen/LumenSceneLighting.ush` (Private)

- lines: 36; parse: all-branches

#### Macros (#define, 6)

- L5 `#define CARD_UPDATE_CONTEXT_DIRECT_LIGHTING 0`
- L6 `#define CARD_UPDATE_CONTEXT_INDIRECT_LIGHTING 1`
- L7 `#define CARD_UPDATE_CONTEXT_MAX 2`
- L9 `#define PRIORITY_HISTOGRAM_SIZE 16`
- L12 `#define MAX_UPDATE_BUCKET_STRIDE 2`
- L15 `#define CARD_PAGE_TILE_ALLOCATOR_STRIDE 2`
- L3 #pragma `once`

#### Functions (3)

- L17-24 _function_ `float CalculateDistanceBasedHeightfieldBias(float SurfaceBias, float3 WorldPosition, float3 WorldCameraOrigin)`
- L26-31 _function_ `float GetCardBiasForShadowing(float3 L, float3 WorldNormal, float BiasValue)`
- L33-36 _function_ `float3 GetCardWorldPositionForShadowing(float3 WorldPosition, float3 L, float3 WorldNormal, float BiasValue)`

### `Shaders/Private/Lumen/LumenSceneLightingDebug.usf` (Private)

- lines: 244; parse: all-branches
- includes: L7 `../Common.ush`, L8 `../ShaderPrint.ush`, L9 `LumenCardCommon.ush`, L10 `LumenCardTile.ush`, L11 `LumenSceneLighting.ush`

#### Entry points (2)

- L69-83 _entry_ `[numthreads(1, 1, 1)] void LumenSceneLightingStatsCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FLumenSceneLightingStatsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenSceneLighting.cpp:547) — Print out various stats for debugging surface cache updates _[#if SHADER_STATS]_
- L127-243 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void LumenSceneDirectLightingStatsCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FLumenSceneDirectLightingStatsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenSceneDirectLighting.cpp:2322) _[#if SHADER_DEBUG]_

#### Global resources (textures / buffers / samplers) (11)

- L17 _resource_ `StructuredBuffer<uint> PriorityHistogram;` _[#if SHADER_STATS]_
- L18 _resource_ `StructuredBuffer<uint> MaxUpdateBucket;` _[#if SHADER_STATS]_
- L19 _resource_ `StructuredBuffer<uint> CardPageTileAllocator;` _[#if SHADER_STATS]_
- L20 _resource_ `StructuredBuffer<uint> DirectLightingCardPageIndexAllocator;` _[#if SHADER_STATS]_
- L21 _resource_ `StructuredBuffer<uint> IndirectLightingCardPageIndexAllocator;` _[#if SHADER_STATS]_
- L105 _resource_ `StructuredBuffer<uint> CompactedTraceAllocator;` _[#if SHADER_DEBUG]_
- L107 _resource_ `StructuredBuffer<uint> CardPageIndexAllocator;` _[#if SHADER_DEBUG]_
- L108 _resource_ `StructuredBuffer<uint> CardPageIndexData;` _[#if SHADER_DEBUG]_
- L110 _resource_ `StructuredBuffer<uint> CardTileAllocator;` _[#if SHADER_DEBUG]_
- L111 _resource_ `StructuredBuffer<uint> CardTiles;` _[#if SHADER_DEBUG]_
- L113 _resource_ `StructuredBuffer<uint> DebugDataBuffer;` _[#if SHADER_DEBUG]_

#### Global parameters (uniforms) (15)

- L16 _parameter_ `uint LightingStatMode;` _[#if SHADER_STATS]_
- L89 _parameter_ `uint NumLights;` _[#if SHADER_DEBUG]_
- L90 _parameter_ `uint NumViews;` _[#if SHADER_DEBUG]_
- L91 _parameter_ `uint NumBatchedLights;` _[#if SHADER_DEBUG]_
- L92 _parameter_ `uint NumStandaloneLights;` _[#if SHADER_DEBUG]_
- L93 _parameter_ `uint bHasRectLights;` _[#if SHADER_DEBUG]_
- L94 _parameter_ `uint bHasLightFunctionLights;` _[#if SHADER_DEBUG]_
- L95 _parameter_ `uint bHasIESLights;` _[#if SHADER_DEBUG]_
- L96 _parameter_ `uint bStochastic;` _[#if SHADER_DEBUG]_
- L97 _parameter_ `uint bHWRT;` _[#if SHADER_DEBUG]_
- L98 _parameter_ `uint bValidDebugData;` _[#if SHADER_DEBUG]_
- L100 _parameter_ `int2 AtlasResolution;` _[#if SHADER_DEBUG]_
- L101 _parameter_ `int2 UpdateAtlasSize;` _[#if SHADER_DEBUG]_
- L102 _parameter_ `uint MaxUpdateTiles;` _[#if SHADER_DEBUG]_
- L103 _parameter_ `uint UpdateFactor;` _[#if SHADER_DEBUG]_

#### Functions (2)

- L23-64 _function_ `void LumenSceneLightingStats(uint CardUpdateContext, StructuredBuffer<uint> CardPageIndexAllocator)` _[#if SHADER_STATS]_
- L115-125 _function_ `void DrawTile(inout FShaderPrintContext Ctx, uint InCardIndex, float2 UVMin, float2 UVMax, float4 Color)` _[#if SHADER_DEBUG]_

### `Shaders/Private/Lumen/LumenScreenProbeCommon.ush` (Private)

- lines: 270; parse: all-branches
- includes: L5 `../MonteCarlo.ush`, L6 `../BlueNoise.ush`, L7 `../SceneTextureParameters.ush`, L8 `LumenPosition.ush`

#### Macros (#define, 10)

- L11 `#define SH_QUANTIZE_DIRECTIONAL_COEFFICIENTS 0`
- L12 `#define PROBE_THREADGROUP_SIZE_2D 8`
- L13 `#define PROBE_THREADGROUP_SIZE_1D 64`
- L15 `#define PROBE_IRRADIANCE_FORMAT_SH3 0`
- L16 `#define PROBE_IRRADIANCE_FORMAT_OCT 1`
- L17 `#define IRRADIANCE_PROBE_RES 6`
- L18 `#define IRRADIANCE_PROBE_WITH_BORDER_RES (IRRADIANCE_PROBE_RES + 2)`
- L67 `#define SCREEN_TEMPORAL_INDEX (FixedJitterIndex < 0 ? View.StateFrameIndexMod8 : FixedJitterIndex)`
- L68 `#define SCREEN_PROBE_JITTER_INDEX (FixedJitterIndex < 0 ? View.StateFrameIndex : FixedJitterIndex)`
- L69 `#define GENERAL_TEMPORAL_INDEX (FixedJitterIndex < 0 ? View.StateFrameIndexMod8 : FixedJitterIndex)`
- L3 #pragma `once`

#### Structs / classes (1)

- L254-260 _struct_ **`FProbeRayDistance`** `struct FProbeRayDistance`
  - L256 _member_ `float HitDistance;`
  - L257 _member_ `bool bHit;`
  - L258 _member_ `bool bMoving;`
  - L259 _member_ `bool bReachedRadianceCache;`

#### Global resources (textures / buffers / samplers) (11)

- L55 _resource_ `Texture2D<uint> ScreenProbeSceneDepth;` — Screen Probe GBuffers.  These are indexed by ScreenProbeAtlasCoord and adaptive probes are placed at the bottom of the texture. Note: negative if unlit
- L56 _resource_ `Texture2D<float2> ScreenProbeWorldNormal;`
- L57 _resource_ `Texture2D<uint> ScreenProbeWorldSpeed;`
- L60 _resource_ `StructuredBuffer<uint> NumAdaptiveScreenProbes;` — Single element, contains the number of adaptive screen probes placed
- L61 _resource_ `StructuredBuffer<uint> AdaptiveScreenProbeData;`
- L63 _resource_ `Texture2D<uint> ScreenTileAdaptiveProbeHeader;`
- L64 _resource_ `Texture2D<uint> ScreenTileAdaptiveProbeIndices;`
- L192 _resource_ `Texture2D<float> ScreenProbeMoving;`
- L199 _resource_ `Buffer<uint> CompactedTraceTexelAllocator;`
- L200 _resource_ `Buffer<uint> CompactedTraceTexelData;`
- L214 _resource_ `Texture2D<uint> LightingChannelsTexture;`

#### Global parameters (uniforms) (19)

- L21 _parameter_ `uint ScreenProbeTracingOctahedronResolution;` — Main control for Screen Probe tracing resolution.  8 = 8x8 traces per probe
- L23 _parameter_ `uint ScreenProbeGatherOctahedronResolution;` — Screen probe traces are re-sampled to this resolution before filtering / BRDF integration
- L24 _parameter_ `uint ScreenProbeGatherOctahedronResolutionWithBorder;`
- L27 _parameter_ `uint2 ScreenProbeViewSize;` — Size of the downsampled viewport, in probes.  This corresponds to the uniform placement viewport.
- L30 _parameter_ `uint2 ScreenProbeAtlasViewSize;` — Size of the active viewport into the atlas, in probes
- L32 _parameter_ `uint2 ScreenProbeAtlasBufferSize;` — Size of all the probe atlas textures, in probes
- L34 _parameter_ `float ScreenProbeGatherMaxMip;`
- L35 _parameter_ `float RelativeSpeedDifferenceToConsiderLightingMoving;`
- L36 _parameter_ `float ScreenTraceNoFallbackThicknessScale;`
- L39 _parameter_ `float2 SampleRadianceProbeUVMul;` — Used by InterpolateFromScreenProbes() to sample probe radiance with border
- L40 _parameter_ `float2 SampleRadianceProbeUVAdd;`
- L41 _parameter_ `float2 SampleRadianceAtlasUVMul;`
- L44 _parameter_ `uint ScreenProbeDownsampleFactor;` — Downsample factor from full res to Screen Probe res
- L46 _parameter_ `uint NumUniformScreenProbes;` — ScreenProbeViewSize.x * ScreenProbeViewSize.y
- L47 _parameter_ `uint MaxNumAdaptiveProbes;`
- L48 _parameter_ `int FixedJitterIndex;`
- L50 _parameter_ `float ExtraAOMaxDistanceWorldSpace;`
- L51 _parameter_ `float ExtraAOExponent;`
- L66 _parameter_ `uint ScreenProbeRayDirectionFrameIndex;`

#### Functions (27)

- L72-76 _function_ `uint2 GetScreenTileJitter(uint TemporalIndex)` — Returns the jitter offset in the range [0, ScreenProbeDownsampleFactor - 1]
- L79-82 _function_ `float GetScreenProbeDepth(uint2 ScreenProbeAtlasCoord, Texture2D<uint> ProbeSceneDepthTexture)` — Note: Returns negative depth for invalid probe
- L84-87 _function_ `float GetScreenProbeDepth(uint2 ScreenProbeAtlasCoord)`
- L89-92 _function_ `float3 GetScreenProbeNormal(uint2 ScreenProbeAtlasCoord)`
- L94-97 _function_ `uint GetNumAdaptiveScreenProbes()`
- L99-104 _function_ `uint2 GetAdaptiveProbeCoord(uint2 ScreenTileCoord, uint AdaptiveProbeListIndex)`
- L106-109 _function_ `uint GetNumScreenProbes()`
- L111-114 _function_ `uint EncodeScreenProbeData(uint2 ScreenProbeScreenPosition)`
- L116-119 _function_ `uint2 DecodeScreenProbeData(uint EncodedProbeData)`
- L122-133 _function_ `uint2 GetScreenProbeScreenPosition(uint ScreenProbeIndex)` — Note this can return a screen position outside of the valid viewport, since probes can be placed off-screen due to DivideAndRoundUp
- L135-138 _function_ `uint2 GetScreenTileCoord(uint2 ScreenProbeScreenPosition)`
- L140-145 _function_ `uint2 GetUniformScreenProbeScreenPosition(uint2 ScreenTileCoord)`
- L147-150 _function_ `float2 GetScreenTileCoordFromScreenUV(float2 ScreenUV, uint TemporalIndex)`
- L152-156 _function_ `float2 GetScreenUVFromScreenTileCoord(uint2 ScreenTileCoord)`
- L158-163 _function_ `float2 GetScreenUVFromScreenProbePosition(uint2 ScreenProbeScreenPosition)`
- L165-172 _function_ `uint EncodeScreenProbeSpeed(float ProbeSpeed, bool bTwoSidedFoliage, bool bHair)`
- L174-178 _function_ `bool GetScreenProbeIsTwoSidedFoliage(uint2 ScreenProbeAtlasCoord)`
- L180-184 _function_ `bool GetScreenProbeIsHair(uint2 ScreenProbeAtlasCoord)`
- L186-190 _function_ `float GetScreenProbeSpeed(uint2 ScreenProbeAtlasCoord)`
- L194-197 _function_ `float GetScreenProbeMoving(uint2 ScreenProbeAtlasCoord)`
- L202-205 _function_ `uint EncodeScreenProbeTraceTexel(uint ScreenProbeIndex, uint2 TraceTexelCoord)`
- L207-212 _function_ `void DecodeScreenProbeTraceTexel(uint TraceTexelData, out uint ScreenProbeIndex, out uint2 TraceTexelCoord)`
- L216-223 _function_ `bool HasDistanceFieldRepresentation(float2 ScreenUV)`
- L225-232 _function_ `float GetScreenTraceDepthThresholdScale(float2 ScreenUV)`
- L234-237 _function_ `float GetProbeMaxHitDistance()`
- L239-252 _function_ `uint EncodeProbeRayDistance(float HitDistance, bool bHit, bool bMoving, bool bReachedRadianceCache)`
- L262-270 _function_ `FProbeRayDistance DecodeProbeRayDistance(uint Encoded)`

### `Shaders/Private/Lumen/LumenScreenProbeDebug.usf` (Private)

- lines: 101; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../ShaderPrint.ush`, L5 `LumenScreenProbeCommon.ush`, L6 `LumenMaterial.ush`

#### Entry points (1)

- L18-101 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void ScreenProbeGatherDebugCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FScreenProbeGatherDebugCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenScreenProbeGather.cpp:1382)

#### Global resources (textures / buffers / samplers) (1)

- L9 _resource_ `RWTexture2D<float4> RWSceneColor;`

#### Global parameters (uniforms) (1)

- L8 _parameter_ `uint VisualizeProbePlacement;`

#### Functions (1)

- L11-16 _function_ `void DrawPoint(FShaderPrintContext Context, uint2 ScreenCoord, float4 Color)`

### `Shaders/Private/Lumen/LumenScreenProbeFiltering.usf` (Private)

- lines: 1145; parse: all-branches
- includes: L8 `../Common.ush`, L9 `../DeferredShadingCommon.ush`, L10 `../BRDF.ush`, L11 `LumenScreenProbeCommon.ush`, L12 `LumenScreenProbeTracingCommon.ush`, L13 `LumenFloatQuantization.ush`, L14 `../SHCommon.ush`

#### Macros (#define, 5)

- L6 `#define NEED_SH_VECTOR_PADDING 1` _[#if defined(DXC_GROUPSHARED_ALIGNMENT_WORKAROUND) && DXC_GROUPSHARED_ALIGNMENT_WORKAROUND]_
- L17 `#define THREADGROUP_SIZE 1` _[#if !defined(THREADGROUP_SIZE)]_
- L89 `#define DITHER_TRACE_DIRECTIONS 1`
- L318 `#define FILTER_SEARCH_ADAPTIVE_PROBES 0`
- L536 `#define NUM_LIGHTING_SH_COEFFICIENTS 9`

#### Entry points (7)

- L30-186 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void ScreenProbeCompositeTracesWithScatterCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FScreenProbeCompositeTracesWithScatterCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenScreenProbeFiltering.cpp:178)
- L200-283 _entry_ `[numthreads(PROBE_THREADGROUP_SIZE_2D, PROBE_THREADGROUP_SIZE_2D, 1)] void ScreenProbeTemporallyAccumulateTraceRadianceCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FScreenProbeTemporallyAccumulateTraceRadianceCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenScreenProbeFiltering.cpp:214)
- L387-506 _entry_ `[numthreads(PROBE_THREADGROUP_SIZE_2D, PROBE_THREADGROUP_SIZE_2D, 1)] void ScreenProbeFilterGatherTracesCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FScreenProbeFilterGatherTracesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenScreenProbeFiltering.cpp:253)
- L597-998 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void ScreenProbeConvertToIrradianceCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FScreenProbeConvertToIrradianceCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenScreenProbeFiltering.cpp:331)
- L1006-1079 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void ScreenProbeCalculateMovingCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FScreenProbeCalculateMovingCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenScreenProbeFiltering.cpp:376)
- L1081-1107 _entry_ `[numthreads(PROBE_THREADGROUP_SIZE_2D, PROBE_THREADGROUP_SIZE_2D, 1)] void ScreenProbeFixupBordersCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FScreenProbeFixupBordersCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenScreenProbeFiltering.cpp:409)
- L1113-1144 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void ScreenProbeGenerateMipLevelCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FScreenProbeGenerateMipLevelCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenScreenProbeFiltering.cpp:443)

#### Global resources (textures / buffers / samplers) (20)

- L20 _resource_ `RWTexture2D<float3> RWScreenProbeRadiance;`
- L21 _resource_ `RWTexture2D<float> RWScreenProbeHitDistance;`
- L22 _resource_ `RWTexture2D<UNORM float> RWScreenProbeTraceMoving;`
- L23 _resource_ `RWTexture2D<UNORM float> RWScreenProbeExtraAO;`
- L25 _resource_ `Texture2D TraceRadiance;`
- L188 _resource_ `Texture2D<float3> ScreenProbeRadiance;`
- L196 _resource_ `Texture2D<uint> HistoryScreenProbeSceneDepth;`
- L197 _resource_ `Texture2D<float3> HistoryScreenProbeRadiance;`
- L198 _resource_ `Texture2D<float3> HistoryScreenProbeTranslatedWorldPosition;`
- L285 _resource_ `Texture2D<float> ScreenProbeExtraAO;`
- L286 _resource_ `Texture2D<float> ScreenProbeHitDistance;`
- L385 _resource_ `Texture2D<UNORM float> ScreenProbeDisocclusion;`
- L528 _resource_ `RWTexture2D<float3> RWScreenProbeRadianceSHAmbient;` _[#if PROBE_IRRADIANCE_FORMAT == PROBE_IRRADIANCE_FORMAT_SH3]_
- L529 _resource_ `RWTexture2D<float4> RWScreenProbeRadianceSHDirectional;` _[#if PROBE_IRRADIANCE_FORMAT == PROBE_IRRADIANCE_FORMAT_SH3]_
- L531 _resource_ `RWTexture2D<float3> RWScreenProbeIrradianceWithBorder;` _[#if !(PROBE_IRRADIANCE_FORMAT == PROBE_IRRADIANCE_FORMAT_SH3)]_
- L534 _resource_ `RWTexture2D<float> RWScreenProbeExtraAOWithBorder;`
- L1000 _resource_ `RWTexture2D<UNORM float> RWScreenProbeMoving;`
- L1001 _resource_ `Texture2D<float> ScreenProbeTraceMoving;`
- L1109 _resource_ `RWTexture2D<float3> RWScreenProbeRadianceWithBorderMip;`
- L1110 _resource_ `Texture2D<float3> ScreenProbeRadianceWithBorderParentMip;`

#### Global parameters (uniforms) (12)

- L26 _parameter_ `float MaxRayIntensity;`
- L190 _parameter_ `float4 HistoryScreenPositionScaleBias;`
- L191 _parameter_ `float4 HistoryUVMinMax;`
- L192 _parameter_ `float ProbeTemporalFilterHistoryWeight;`
- L193 _parameter_ `float HistoryDistanceThreshold;`
- L194 _parameter_ `float PrevInvPreExposure;`
- L288 _parameter_ `float SpatialFilterMaxRadianceHitAngle;`
- L289 _parameter_ `float SpatialFilterPositionWeightScale;`
- L290 _parameter_ `int SpatialFilterHalfKernelSize;`
- L384 _parameter_ `int SpatialFilterPassIndex;`
- L1002 _parameter_ `float DebugForceTracesMoving;`
- L1111 _parameter_ `uint MipLevel;`

#### groupshared (9)

- L28 _groupshared_ `groupshared uint SharedAccumulators[THREADGROUP_SIZE * THREADGROUP_SIZE][6];`
- L540 _groupshared_ `groupshared FThreeBandSHVectorRGB SharedWaveSumRadianceSH[2];` — Partial wave sums _[#if WAVE_OP_WAVE_SIZE == 32]_
- L542 _groupshared_ `groupshared FThreeBandSHVector SharedWaveSumAOSH[2];` _[#if WAVE_OP_WAVE_SIZE == 32 && SCREEN_PROBE_EXTRA_AO]_
- L543 _groupshared_ `groupshared FThreeBandSHVector SharedWaveSumAOWeightSH[2];` _[#if WAVE_OP_WAVE_SIZE == 32 && SCREEN_PROBE_EXTRA_AO]_
- L546 _groupshared_ `groupshared float SharedSHBasisFunctions[THREADGROUP_SIZE * THREADGROUP_SIZE][NUM_LIGHTING_SH_COEFFICIENTS];` _[#if !(WAVE_OP_WAVE_SIZE == 32) && WAVE_OP_WAVE_SIZE == 0]_
- L547 _groupshared_ `groupshared float SharedLightingRadiance[THREADGROUP_SIZE * THREADGROUP_SIZE][4];` _[#if !(WAVE_OP_WAVE_SIZE == 32) && WAVE_OP_WAVE_SIZE == 0]_
- L548 _groupshared_ `groupshared float SharedSums[NUM_LIGHTING_SH_COEFFICIENTS * 4];` _[#if !(WAVE_OP_WAVE_SIZE == 32) && WAVE_OP_WAVE_SIZE == 0]_
- L550 _groupshared_ `groupshared float SharedAO[THREADGROUP_SIZE][THREADGROUP_SIZE];` _[#if !(WAVE_OP_WAVE_SIZE == 32) && WAVE_OP_WAVE_SIZE == 0 && SCREEN_PROBE_EXTRA_AO]_
- L1004 _groupshared_ `groupshared float SharedTexelMoving[THREADGROUP_SIZE * THREADGROUP_SIZE * 4];`

#### Functions (6)

- L292-297 _function_ `float GetFilterPositionWeight(float ProbeDepth, float SceneDepth)`
- L299-382 _function_ `void GatherNeighborRadiance( int2 NeighborScreenTileCoord, uint2 ProbeTexelCoord, float3 WorldPosition, float3 WorldConeDirection, float SceneDepth, float HitDistance, bool bRelaxAngleWeight, inout float3 TotalRadiance, inout float TotalAO, inout float TotalWeight)`
- L509-515 _function_ `float3 WaveActiveSumFloat3(float3 Vec)` _[#if WAVE_OP_WAVE_SIZE > 0]_
- L517-524 _function_ `float4 WaveActiveSumFloat4(float4 Vec)` _[#if WAVE_OP_WAVE_SIZE > 0]_
- L554-557 _function_ `void WriteExtraAO(uint2 ScreenProbeAtlasCoord, uint2 IrradianceProbeTexelCoord, float AO)`
- L560-591 _function_ `float IntegrateExtraAO(float3 ProbeTexelDirection)` _[#if SCREEN_PROBE_EXTRA_AO && WAVE_OP_WAVE_SIZE == 0]_

#### Top-level macro invocations (1)

- L595 _macro_call_ `WAVESIZE(WAVE_OP_WAVE_SIZE)` _[#if COMPILER_SUPPORTS_WAVE_SIZE && WAVE_OP_WAVE_SIZE > 0 && THREADGROUP_SIZE == 8]_

### `Shaders/Private/Lumen/LumenScreenProbeGather.usf` (Private)

- lines: 1947; parse: all-branches
- includes: L5 `../Common.ush`, L6 `LumenMaterial.ush`, L7 `../DeferredShadingCommon.ush`, L8 `../BRDF.ush`, L9 `LumenScreenProbeCommon.ush`, L10 `LumenScreenProbeTileClassication.ush`, L11 `../MonteCarlo.ush`, L12 `../ShadingModelsSampling.ush`, L13 `../SHCommon.ush`, L14 `../SceneTextureParameters.ush`, L15 `../SphericalGaussian.ush`, L16 `../FastMath.ush`, L17 `../ClearCoatCommon.ush`, L18 `LumenRadianceCacheMarkCommon.ush`, L19 `../TextureSampling.ush`, L20 `../MortonCode.ush`, L21 `LumenScreenSpaceBentNormal.ush`, L22 `LumenReflectionsCombine.ush`, L23 `LumenFloatQuantization.ush`, L24 `../ReflectionEnvironmentShared.ush`, L25 `../StochasticLighting/StochasticLightingCommon.ush`, L26 `LumenUpsample.ush`, L376 `../HairStrands/HairStrandsTileCommon.ush` [defined(MarkRadianceProbesUsedByHairStrandsCS)], L1592 `../ShaderPrint.ush` [defined(ScreenProbeDebugMain)]

#### Macros (#define, 31)

- L3 `#define USE_HAIR_COMPLEX_TRANSMITTANCE 1`
- L29 `#define THREADGROUP_SIZE 1` _[#if !defined(THREADGROUP_SIZE)]_
- L33 `#define INTEGRATE_TILE_CLASSIFICATION_MODE 0` _[#if !defined(INTEGRATE_TILE_CLASSIFICATION_MODE)]_
- L36 `#define MIN_PROBE_INTERPOLATION_WEIGHT 0.01`
- L179 `#define PLANE_WEIGHTING 1`
- L397 `#define MARK_PROBE_FAST 0` _[#if defined(MarkRadianceProbesUsedByHairStrandsCS)]_
- L398 `#define MARK_PROBE_ACCUMRATE 1` _[#if defined(MarkRadianceProbesUsedByHairStrandsCS)]_
- L399 `#define HAIRSTRANDS_MARK_USED_METHOD MARK_PROBE_ACCUMRATE` _[#if defined(MarkRadianceProbesUsedByHairStrandsCS)]_
- L475 `#define INTEGRATE_TILE_SIZE 8`
- L476 `#define INTEGRATE_TILE_SIZE_DIV_AS_SHIFT 3`
- L481 `#define TILE_CLASSIFICATION_SIMPLE_DIFFUSE 0`
- L482 `#define TILE_CLASSIFICATION_SUPPORT_IMPORTANCE_SAMPLE_BRDF 1`
- L484 `#define TILE_CLASSIFICATION_SUPPORT_ALL 2`
- L485 `#define TILE_CLASSIFICATION_NUM 3`
- L489 `#define TILE_CLASSIFICATION_INDIRECT_ARGS_ENTRY_COUNT (TILE_CLASSIFICATION_NUM*2)` _[#if SUBSTRATE_ENABLED && SUBSTRATE_GBUFFER_FORMAT == 1]_
- L491 `#define TILE_CLASSIFICATION_INDIRECT_ARGS_ENTRY_COUNT (TILE_CLASSIFICATION_NUM)` _[#if !(SUBSTRATE_ENABLED && SUBSTRATE_GBUFFER_FORMAT == 1)]_
- L501 `#define PERMUTATION_OVERFLOW_TILE 0` _[#if !defined(PERMUTATION_OVERFLOW_TILE)]_
- L528 `#define TILE_CLASSIFICATION_ARGS_OFFSET (PERMUTATION_OVERFLOW_TILE * TILE_CLASSIFICATION_NUM * DISPATCH_INDIRECT_UINT_COUNT)`
- L879 `#define COMBINED_FACTORS 1`
- L956 `#define ROUGH_SPECULAR_ALONG_REFLECTION_DIRECTION 0`
- L980 `#define SH_DIRECTIONAL_OCCLUSION 1` _[#if PROBE_IRRADIANCE_FORMAT == PROBE_IRRADIANCE_FORMAT_SH3]_
- L1064 `#define TONEMAP_DURING_INTEGRATION 1`
- L1084 `#define TILE_CLASSIFICATION_DISABLED TILE_CLASSIFICATION_NUM`
- L1461 `#define DEBUG_VISUALIZE_PROBE_WORLD_SPEED 0` _[#if defined(ScreenProbeIntegrateCS)]_
- L1471 `#define DEBUG_VISUALIZE_INVALID_UPSAMPLE 0` _[#if defined(ScreenProbeIntegrateCS)]_
- L1479 `#define DEBUG_VISUALIZE_TILE_CLASSIFICATION 0` _[#if defined(ScreenProbeIntegrateCS)]_
- L1487 `#define DEBUG_VISUALIZE_AO 0` _[#if defined(ScreenProbeIntegrateCS)]_
- L1733 `#define NUM_UNIFORM_PROBES_PER_GROUP uint2(THREADGROUP_SIZE / NUM_SAMPLES_PER_UNIFORM_PROBE_X, THREADGROUP_SIZE / NUM_SAMPLES_PER_UNIFORM_PROBE_Y)` _[#if defined(ScreenProbeAdaptivePlacementMarkCS)]_
- L1734 `#define SHARED_PROBE_PLACEMENT_MASK_SIZE_X (THREADGROUP_SIZE / NUM_SAMPLES_PER_UNIFORM_PROBE_X)` _[#if defined(ScreenProbeAdaptivePlacementMarkCS)]_
- L1735 `#define SHARED_PROBE_PLACEMENT_MASK_SIZE_Y (THREADGROUP_SIZE / NUM_SAMPLES_PER_UNIFORM_PROBE_Y)` _[#if defined(ScreenProbeAdaptivePlacementMarkCS)]_
- L1812 `#define NUM_UNIFORM_PROBES_PER_GROUP uint2(THREADGROUP_SIZE / NUM_SAMPLES_PER_UNIFORM_PROBE_X, THREADGROUP_SIZE / NUM_SAMPLES_PER_UNIFORM_PROBE_Y)` _[#if defined(ScreenProbeAdaptivePlacementSpawnCS)]_

#### Entry points (11)

- L116-131 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void ScreenProbeDownsampleDepthUniformCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FScreenProbeDownsampleDepthUniformCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenScreenProbeGather.cpp:793) _[#if defined(ScreenProbeDownsampleDepthUniformCS)]_
- L317-332 _entry_ `[numthreads(1, 1, 1)] void SetupAdaptiveProbeIndirectArgsCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FSetupAdaptiveProbeIndirectArgsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenScreenProbeGather.cpp:903) _[#if defined(SetupAdaptiveProbeIndirectArgsCS)]_
- L338-366 _entry_ `[numthreads(PROBE_THREADGROUP_SIZE_2D, PROBE_THREADGROUP_SIZE_2D, 1)] void MarkRadianceProbesUsedByScreenProbesCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FMarkRadianceProbesUsedByScreenProbesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenScreenProbeGather.cpp:937) _[#if defined(MarkRadianceProbesUsedByScreenProbesCS)]_
- L377-471 _entry_ `[numthreads(64, 1, 1)] void MarkRadianceProbesUsedByHairStrandsCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FMarkRadianceProbesUsedByHairStrandsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenScreenProbeGather.cpp:975) _[#if defined(MarkRadianceProbesUsedByHairStrandsCS)]_
- L533-551 _entry_ `[numthreads(32, 1, 1)] void InitScreenProbeTileIndirectArgsCS( uint2 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint2 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FInitScreenProbeTileIndirectArgsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenScreenProbeGather.cpp:994)
- L621-792 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void ScreenProbeTileClassificationBuildListsCS( uint2 GroupId : SV_GroupID, uint GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FScreenProbeTileClassificationBuildListsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenScreenProbeGather.cpp:1062) _[#if defined(ScreenProbeTileClassificationBuildListsCS)]_
- L1093-1121 _entry_ `[numthreads(INTEGRATE_TILE_SIZE, INTEGRATE_TILE_SIZE, 1)] void ScreenProbeIntegrateClearUnusedTileDataCS( uint2 DispatchThreadId : SV_DispatchThreadID, uint GroupId : SV_GroupID, uint2 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FScreenProbeIntegrateClearUnusedTileDataCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenScreenProbeGather.cpp:1089) — Clear integrate tile data for tiles which will be skipped due to tile classification, but still may be read by upsampling or ClampHistory in ScreenProbeTemporalReprojectionCS _[#if defined(ScreenProbeIntegrateClearUnusedTileDataCS)]_
- L1129-1583 _entry_ `[numthreads(INTEGRATE_TILE_SIZE, INTEGRATE_TILE_SIZE, 1)] void ScreenProbeIntegrateCS( uint2 DispatchThreadId : SV_DispatchThreadID, uint GroupId : SV_GroupID, uint2 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FScreenProbeIntegrateCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenScreenProbeGather.cpp:1204) _[#if defined(ScreenProbeIntegrateCS)]_
- L1657-1717 _entry_ `[numthreads(1, 1, 1)] void ScreenProbeDebugMain(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FLumenScreenProbeSubstrateDebugPass` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenScreenProbeGather.cpp:1347) _[#if defined(ScreenProbeDebugMain)]_
- L1743-1806 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void ScreenProbeAdaptivePlacementMarkCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FScreenProbeAdaptivePlacementMarkCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenScreenProbeGather.cpp:835) — Mark all valid adaptive probe placement locations in RWAdaptiveProbePlacementMask _[#if defined(ScreenProbeAdaptivePlacementMarkCS)]_
- L1824-1945 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void ScreenProbeAdaptivePlacementSpawnCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FScreenProbeAdaptivePlacementSpawnCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenScreenProbeGather.cpp:885) — Loop over all valid adaptive probe locations (based on AdaptiveProbePlacementMask) and spawn probes. In order to minimize number of probes we also check whether probe is already covered by previous spawned probes (samples with a lower index) _[#if defined(ScreenProbeAdaptivePlacementSpawnCS)]_

#### Structs / classes (3)

- L55-62 _struct_ **`FScreenProbeMaterial`** `struct FScreenProbeMaterial`
  - L57 _member_ `float3 WorldNormal;`
  - L58 _member_ `float SceneDepth;`
  - L59 _member_ `bool bIsValid;`
  - L60 _member_ `bool bHasBackfaceDiffuse;`
  - L61 _member_ `bool bHair;`
- L140-145 _struct_ **`FScreenProbeSample`** `struct FScreenProbeSample`
  - L142 _member_ `uint2 AtlasCoord[4];`
  - L143 _member_ `float4 Weights;`
  - L144 _member_ `float4 FallbackWeights;`
- L504-508 _struct_ **`FScreenProbeIntegrateTileData`** `struct FScreenProbeIntegrateTileData`
  - L506 _member_ `uint2 Coord;`
  - L507 _member_ `uint ClosureIndex;`

#### Global resources (textures / buffers / samplers) (31)

- L38 _resource_ `RWTexture2D<uint> RWScreenProbeSceneDepth;`
- L39 _resource_ `RWTexture2D<uint> RWScreenProbeWorldSpeed;`
- L40 _resource_ `RWTexture2D<UNORM float2> RWScreenProbeWorldNormal;`
- L41 _resource_ `RWTexture2D<float4> RWScreenProbeTranslatedWorldPosition;`
- L44 _resource_ `Texture2DArray<uint> ShortRangeAOTexture;` _[#if SHORT_RANGE_AO_BENT_NORMAL]_
- L46 _resource_ `Texture2DArray<UNORM float> ShortRangeAOTexture;` _[#if !(SHORT_RANGE_AO_BENT_NORMAL)]_
- L212 _resource_ `RWTexture2D<uint> RWScreenTileAdaptiveProbeHeader;`
- L213 _resource_ `RWTexture2D<uint> RWScreenTileAdaptiveProbeIndices;`
- L214 _resource_ `RWStructuredBuffer<uint> RWAdaptiveScreenProbeData;`
- L305 _resource_ `RWBuffer<uint> RWScreenProbeIndirectArgs;`
- L494 _resource_ `RWBuffer<uint> RWIntegrateIndirectArgs;`
- L495 _resource_ `RWTexture2DArray<float3> RWDiffuseIndirect;`
- L496 _resource_ `RWTexture2DArray<UNORM float> RWLightIsMoving;`
- L497 _resource_ `RWTexture2DArray<float3> RWBackfaceDiffuseIndirect;`
- L498 _resource_ `RWTexture2DArray<float3> RWRoughSpecularIndirect;`
- L530 _resource_ `RWBuffer<uint> RWClearUnusedIntegrateTileIndirectArgs;`
- L531 _resource_ `RWBuffer<uint> RWClearUnusedIntegrateTileData;`
- L553 _resource_ `RWStructuredBuffer<uint> RWIntegrateTileData;`
- L554 _resource_ `Texture2DArray<uint> LumenTileBitmask;`
- L796 _resource_ `Texture2D<float3> ScreenProbeRadianceSHAmbient;`
- L797 _resource_ `Texture2D<float4> ScreenProbeRadianceSHDirectional;`
- L798 _resource_ `Texture2D<float3> ScreenProbeIrradianceWithBorder;`
- L853 _resource_ `Texture2D<float> ScreenProbeExtraAOWithBorder;`
- L872 _resource_ `Texture2D<float3> ScreenProbeRadianceWithBorder;`
- L873 _resource_ `Texture2D<float3> ScreenProbeRadiance;`
- L1088 _resource_ `Buffer<uint> ClearUnusedIntegrateTileData;` _[#if defined(ScreenProbeIntegrateClearUnusedTileDataCS)]_
- L1125 _resource_ `StructuredBuffer<uint> IntegrateTileData;`
- L1595 _resource_ `Buffer<uint> IntegrateIndirectArgs;` _[#if defined(ScreenProbeDebugMain)]_
- L1737 _resource_ `RWTexture2D<uint> RWAdaptiveProbePlacementMask;` _[#if defined(ScreenProbeAdaptivePlacementMarkCS)]_
- L1814 _resource_ `RWStructuredBuffer<uint> RWNumAdaptiveScreenProbes;` _[#if defined(ScreenProbeAdaptivePlacementSpawnCS)]_
- L1815 _resource_ `Texture2D<uint> AdaptiveProbePlacementMask;` _[#if defined(ScreenProbeAdaptivePlacementSpawnCS)]_

#### Global parameters (uniforms) (19)

- L49 _parameter_ `float ScreenProbeInterpolationDepthWeight;`
- L50 _parameter_ `float ScreenProbeInterpolationDepthWeightFoliage;`
- L51 _parameter_ `float ScreenProbeInterpolationDepthWeightFallback;`
- L372 _parameter_ `int2 HairStrandsResolution;` _[#if defined(MarkRadianceProbesUsedByHairStrandsCS)]_
- L373 _parameter_ `float2 HairStrandsInvResolution;` _[#if defined(MarkRadianceProbesUsedByHairStrandsCS)]_
- L374 _parameter_ `uint HairStrandsMip;` _[#if defined(MarkRadianceProbesUsedByHairStrandsCS)]_
- L556 _parameter_ `uint2 ViewportTileMin;`
- L557 _parameter_ `uint2 ViewportTileDimensions;`
- L558 _parameter_ `uint2 ViewportTileDimensionsWithOverflow;`
- L559 _parameter_ `uint2 ViewportIntegrateTileMin;`
- L560 _parameter_ `uint2 ViewportIntegrateTileDimensions;`
- L561 _parameter_ `uint MaxClosurePerPixel;`
- L908 _parameter_ `float FullResolutionJitterWidth;`
- L949 _parameter_ `uint ApplyMaterialAO;`
- L950 _parameter_ `float MaxAOMultibounceAlbedo;`
- L951 _parameter_ `float LumenFoliageOcclusionStrength;`
- L952 _parameter_ `float LumenAmbientOcclusionIntensity;`
- L953 _parameter_ `uint ShortRangeGI;`
- L1594 _parameter_ `uint LayerCount;` _[#if defined(ScreenProbeDebugMain)]_

#### groupshared (8)

- L563 _groupshared_ `groupshared uint SharedNumClearTiles;`
- L564 _groupshared_ `groupshared uint SharedNumTiles[TILE_CLASSIFICATION_NUM];`
- L565 _groupshared_ `groupshared uint SharedIntegrateTileData[TILE_CLASSIFICATION_NUM * THREADGROUP_SIZE];`
- L566 _groupshared_ `groupshared uint SharedGlobalClearTileOffset;`
- L567 _groupshared_ `groupshared uint SharedGlobalTileOffset[TILE_CLASSIFICATION_NUM];`
- L1738 _groupshared_ `groupshared uint SharedProbePlacementMask[SHARED_PROBE_PLACEMENT_MASK_SIZE_X][SHARED_PROBE_PLACEMENT_MASK_SIZE_Y];` _[#if defined(ScreenProbeAdaptivePlacementMarkCS)]_
- L1817 _groupshared_ `groupshared uint SharedNumProbesToAllocate;` _[#if defined(ScreenProbeAdaptivePlacementSpawnCS)]_
- L1818 _groupshared_ `groupshared uint SharedAdaptiveProbeBaseIndex;` _[#if defined(ScreenProbeAdaptivePlacementSpawnCS)]_

#### Functions (32)

- L64-74 _function_ `FScreenProbeMaterial GetScreenProbeMaterial(uint2 PixelPos)`
- L76-79 _function_ `float3 GetMaterialWorldNormal(uint2 PixelPos)`
- L83-112 _function_ `void WriteDownsampledProbeMaterial(float2 ScreenUV, uint2 ScreenProbeAtlasCoord, FScreenProbeMaterial ProbeMaterial)`
- L135-138 _function_ `float GetScreenProbeDepthFromUAV(uint2 ScreenProbeAtlasCoord)`
- L147-210 _function_ `void CalculateUniformUpsampleInterpolationWeights( float2 ScreenCoord, float2 NoiseOffset, float3 WorldPosition, float SceneDepth, float3 WorldNormal, uniform bool bIsUpsamplePass, bool bFoliage, out uint2 ScreenTileCoord00, inout FScreenProbeSample ScreenProbeSample)`
- L216-242 _function_ `float2 GetAdaptiveProbeInterpolationWeight(float2 ScreenCoord, float4 ScenePlane, float SceneDepth, bool bFoliage, uint2 AdaptiveProbeScreenPosition, float AdaptiveProbeDepth)`
- L244-303 _function_ `void CalculateUpsampleInterpolationWeights( float2 ScreenCoord, float2 NoiseOffset, float3 WorldPosition, float SceneDepth, float3 WorldNormal, bool bIsUpsamplePass, bool bUseAdaptiveProbes, bool bFoliage, inout FScreenProbeSample ScreenProbeSample)`
- L307-313 _function_ `void WriteArgs2D(uint Index, uint GroupSize, uint2 ThreadCount)`
- L510-517 _function_ `uint PackScreenProbeIntegrateTileData(FScreenProbeIntegrateTileData In)`
- L519-525 _function_ `FScreenProbeIntegrateTileData UnpackScreenProbeIntegrateTileData(uint In)`
- L569-586 _function_ `uint GetTileDataOffset(uint2 InViewportIntegrateTileDimensions, uint InMode, bool bOverflow)`
- L590-619 _function_ `uint GetLumenTileMode(FScreenProbeIntegrateTileData TileData)` _[#if defined(ScreenProbeTileClassificationBuildListsCS)]_
- L800-844 _function_ `FThreeBandSHVectorRGB GetScreenProbeSH(uint2 ScreenProbeAtlasCoord, float InterpolationWeight)`
- L846-851 _function_ `float3 GetScreenProbeIrradiance(uint2 ScreenProbeAtlasCoord, float2 IrradianceProbeUV)`
- L855-860 _function_ `float GetScreenProbeExtraAO(uint2 ScreenProbeAtlasCoord, float2 IrradianceProbeUV)`
- L863-870 _function_ `float4 BiasBSDFImportantSample(float4 E)` — Bias the important sampling of SampleBxDF(SHADING_TERM_SPECULAR, ....)
- L875-906 _function_ `float3 InterpolateFromScreenProbes(float3 ConeDirection, float MipLevel, FScreenProbeSample ScreenProbeSample)`
- L910-917 _function_ `FBxDFSample SampleBxDFWrapper(const uint TermMask, FLumenMaterialData MaterialData, float3 V, float4 E)`
- L919-932 _function_ `float3 InterpolateScreenProbeIrradiance(FScreenProbeSample ScreenProbeSample, float3 WorldNormal)`
- L934-947 _function_ `float InterpolateScreenProbeExtraAO(FScreenProbeSample ScreenProbeSample, float3 WorldNormal)`
- L958-1030 _function_ `float3 EvaluateDiffuse(FScreenProbeSample ScreenProbeSample, FLumenMaterialData Material, float3 RoughSpecularMainDirection, bool bHasBackfaceDiffuse, float3 UnitBentNormal, float AO, inout float3 BackfaceDiffuseLighting, inout float3 RoughSpecularLighting)`
- L1032-1044 _function_ `float SimpleSpecularShading(float Roughness, float3 L, float3 V, half3 N)`
- L1046-1062 _function_ `float3 SimpleSpecularShading2(float Roughness, float3 SpecularColor, float3 L, float3 V, float3 N)`
- L1066-1073 _function_ `float3 TonemapLighting(float3 Lighting)`
- L1075-1082 _function_ `float3 InverseTonemapLighting(float3 TonemappedLighting)`
- L1598-1602 _function_ `uint GetTileCount(uint InMode, bool bOverflow)` — Return the number of tile _[#if defined(ScreenProbeDebugMain)]_
- L1604-1609 _function_ `FFontColor GetValidColor(bool bIsValid)` _[#if defined(ScreenProbeDebugMain)]_
- L1610-1624 _function_ `void PrintTile(inout FShaderPrintContext Context, uint LinearCoord, uint InMode, bool bOverflow, uint TileIndexFilter, float4 TileColor)` _[#if defined(ScreenProbeDebugMain)]_
- L1626-1631 _function_ `void PrintTileLegend(inout FShaderPrintContext Context)` _[#if defined(ScreenProbeDebugMain)]_
- L1633-1643 _function_ `void PrintTiles(inout FShaderPrintContext Context, uint LinearCoord, bool bOverflow, int TileIndex)` _[#if defined(ScreenProbeDebugMain)]_
- L1645-1655 _function_ `void PrintTileStats(inout FShaderPrintContext Context, bool bOverflow)` _[#if defined(ScreenProbeDebugMain)]_
- L1722-1728 _function_ `uint2 GetAdaptiveSampleCoord(uint2 UniformScreenProbeCoord, uint SampleIndex)` _[#if defined(NUM_SAMPLES_PER_UNIFORM_PROBE)]_

### `Shaders/Private/Lumen/LumenScreenProbeGatherScreenData.usf` (Private)

- lines: 310; parse: all-branches
- includes: L3 `../Common.ush`, L4 `LumenMaterial.ush`, L5 `../DeferredShadingCommon.ush`, L6 `../SHCommon.ush`, L7 `LumenScreenProbeCommon.ush`, L8 `LumenScreenProbeImportanceSamplingShared.ush`, L9 `LumenScreenProbeGatherTemporal.ush`

#### Macros (#define, 1)

- L218 `#define VISUALIZE_BRDF_PDF_SPHERICAL_HARMONIC 0` _[#if BRDF_PDF_SPHERICAL_HARMONIC]_

#### Entry points (1)

- L77-310 _entry_ `[numthreads(PROBE_THREADGROUP_SIZE_2D, PROBE_THREADGROUP_SIZE_2D, 1)] void ScreenProbeGatherScreenDataCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FScreenProbeGatherScreenDataCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenScreenProbeImportanceSampling.cpp:119)

#### Global resources (textures / buffers / samplers) (4)

- L11 _resource_ `RWTexture2D<UNORM float> RWScreenProbeDisocclusion;`
- L12 _resource_ `RWTexture2D<float> RWBRDFProbabilityDensityFunction;`
- L13 _resource_ `RWBuffer<float> RWBRDFProbabilityDensityFunctionSH;`
- L15 _resource_ `Texture2DArray HistoryFastUpdateMode_NumFramesAccumulated;`

#### Global parameters (uniforms) (5)

- L17 _parameter_ `float4 HistoryBufferSizeAndInvSize;`
- L18 _parameter_ `float ScreenProbeInterpolationDepthWeight;`
- L19 _parameter_ `uint ScreenProbeBRDFOctahedronResolution;`
- L20 _parameter_ `float SpatialFilterDisocclusionMaxFrames;`
- L21 _parameter_ `float SpatialFilterDisocclusionFraction;`

#### groupshared (4)

- L23 _groupshared_ `groupshared float4 PixelPlanes[PROBE_THREADGROUP_SIZE_2D][PROBE_THREADGROUP_SIZE_2D];`
- L26 _groupshared_ `groupshared float SharedSphericalHarmonic[PROBE_THREADGROUP_SIZE_2D * PROBE_THREADGROUP_SIZE_2D][NUM_PDF_SH_COEFFICIENTS];` — x2 larger groupshared for x4 reduction per iteration
- L28 _groupshared_ `groupshared float SharedNumDisocclusionPixels[PROBE_THREADGROUP_SIZE_2D * PROBE_THREADGROUP_SIZE_2D];` _[#if SCREEN_PROBE_DISOCCLUSION]_
- L31 _groupshared_ `groupshared uint SharedNumElements;`

#### Functions (4)

- L33-46 _function_ `FThreeBandSHVector GetGroupSharedSH(uint ThreadIndex)`
- L48-55 _function_ `float GetGroupSharedNumDisocclusionPixels(uint ThreadIndex)`
- L57-68 _function_ `void WriteGroupSharedSH(FThreeBandSHVector SH, uint ThreadIndex)`
- L70-75 _function_ `void WriteGroupSharedNumDisocclusionPixels(float NumDisocclusionPixels, uint ThreadIndex)`

### `Shaders/Private/Lumen/LumenScreenProbeGatherTemporal.usf` (Private)

- lines: 583; parse: all-branches
- includes: L5 `../Common.ush`, L6 `LumenMaterial.ush`, L7 `../DeferredShadingCommon.ush`, L8 `LumenScreenProbeCommon.ush`, L9 `LumenScreenSpaceBentNormal.ush`, L10 `LumenReflectionsCombine.ush`, L11 `LumenFloatQuantization.ush`, L12 `LumenPosition.ush`, L13 `../StochasticLighting/StochasticLightingCommon.ush`, L14 `../StochasticLighting/StochasticLightingUpsample.ush`, L15 `LumenUpsample.ush`, L16 `LumenScreenProbeGatherTemporal.ush`

#### Macros (#define, 4)

- L3 `#define USE_HAIR_COMPLEX_TRANSMITTANCE 1`
- L19 `#define INVALID_LIGHTING float3(65024.0f, 65024.0f, 64512.0f)`
- L221 `#define SHARED_TILE_BORDER 1`
- L222 `#define SHARED_TILE_SIZE (THREADGROUP_SIZE / SHORT_RANGE_AO_DOWNSAMPLE_FACTOR + 2 * SHARED_TILE_BORDER)`

#### Entry points (1)

- L288-583 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void ScreenProbeTemporalReprojectionCS( uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupId : SV_GroupID, uint2 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FScreenProbeTemporalReprojectionCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenScreenProbeGather.cpp:1312)

#### Structs / classes (2)

- L203-209 _struct_ **`FGatherUV`** `struct FGatherUV`
  - L205 _member_ `float2 UV00;`
  - L206 _member_ `float2 UV10;`
  - L207 _member_ `float2 UV11;`
  - L208 _member_ `float2 UV01;`
- L225-229 _struct_ **`FShortRangeAONeighborhood`** `struct FShortRangeAONeighborhood` _[#if SHORT_RANGE_AO_MODE]_
  - L227 _member_ `TShortRangeAO Center;` _[#if SHORT_RANGE_AO_MODE]_
  - L228 _member_ `TShortRangeAO Extent;` _[#if SHORT_RANGE_AO_MODE]_

#### Global resources (textures / buffers / samplers) (18)

- L80 _resource_ `RWTexture2DArray<float3> RWNewHistoryDiffuseIndirect;`
- L81 _resource_ `RWTexture2DArray<float3> RWNewHistoryBackfaceDiffuseIndirect;`
- L82 _resource_ `RWTexture2DArray<float3> RWNewHistoryRoughSpecularIndirect;`
- L83 _resource_ `RWTexture2DArray<UNORM float> RWNewHistoryFastUpdateMode_NumFramesAccumulated;`
- L84 _resource_ `RWTexture2DArray<TShortRangeAOPackedWrite> RWNewHistoryShortRangeAO;`
- L85 _resource_ `RWTexture2DArray<float3> RWNewHistoryShortRangeGI;`
- L87 _resource_ `Texture2DArray DiffuseIndirect;`
- L88 _resource_ `Texture2DArray LightIsMoving;`
- L89 _resource_ `Texture2DArray BackfaceDiffuseIndirect;`
- L90 _resource_ `Texture2DArray RoughSpecularIndirect;`
- L91 _resource_ `Texture2DArray<TShortRangeAOPacked> ShortRangeAOTexture;`
- L92 _resource_ `Texture2DArray ShortRangeGI;`
- L93 _resource_ `Texture2DArray DiffuseIndirectHistory;`
- L94 _resource_ `Texture2DArray BackfaceDiffuseIndirectHistory;`
- L95 _resource_ `Texture2DArray RoughSpecularIndirectHistory;`
- L96 _resource_ `Texture2DArray<TShortRangeAOPacked> ShortRangeAOHistory;`
- L97 _resource_ `Texture2DArray<float3> ShortRangeGIHistory;`
- L98 _resource_ `Texture2DArray HistoryFastUpdateMode_NumFramesAccumulated;`

#### Global parameters (uniforms) (8)

- L100 _parameter_ `float4 HistoryBufferSizeAndInvSize;`
- L102 _parameter_ `float ShortRangeAOTemporalNeighborhoodClampScale;`
- L104 _parameter_ `uint2 ShortRangeAOViewMin;`
- L105 _parameter_ `uint2 ShortRangeAOViewSize;`
- L107 _parameter_ `float PrevSceneColorPreExposureCorrection;`
- L108 _parameter_ `float InvFractionOfLightingMovingForFastUpdateMode;`
- L109 _parameter_ `float MaxFastUpdateModeAmount;`
- L110 _parameter_ `uint bIsSubstrateTileHistoryValid;`

#### groupshared (1)

- L231 _groupshared_ `groupshared TShortRangeAO SharedShortRangeAO[SHARED_TILE_SIZE][SHARED_TILE_SIZE];` _[#if SHORT_RANGE_AO_MODE]_

#### static const (1)

- L112-122 _static_const_ `static const int2 kOffsets3x3[8] = { int2(-1, -1), int2( 0, -1), int2( 1, -1), int2(-1, 0), int2( 1, 0), int2(-1, 1), int2( 0, 1), int2( 1, 1), };`

#### typedef / using (6)

- L24 _typedef_ `typedef uint TShortRangeAOPacked;` — Denoise direction and AO separately for higher quality _[#if SHORT_RANGE_AO_MODE == 2]_
- L25 _typedef_ `typedef uint TShortRangeAOPackedWrite;` _[#if SHORT_RANGE_AO_MODE == 2]_
- L26 _typedef_ `typedef half4 TShortRangeAO;` _[#if SHORT_RANGE_AO_MODE == 2]_
- L59 _typedef_ `typedef half TShortRangeAOPacked;` _[#if !(SHORT_RANGE_AO_MODE == 2)]_
- L60 _typedef_ `typedef UNORM float TShortRangeAOPackedWrite;` _[#if !(SHORT_RANGE_AO_MODE == 2)]_
- L61 _typedef_ `typedef half TShortRangeAO;` _[#if !(SHORT_RANGE_AO_MODE == 2)]_

#### Functions (11)

- L28-31 _function_ `half4 InitShortRangeAO()` _[#if SHORT_RANGE_AO_MODE == 2]_
- L33-43 _function_ `uint PackSharedShortRangeAO(half4 BentNormalAndAO)` _[#if SHORT_RANGE_AO_MODE == 2]_
- L45-55 _function_ `half4 UnpackSharedShortRangeAO(uint Packed)` _[#if SHORT_RANGE_AO_MODE == 2]_
- L63-66 _function_ `half InitShortRangeAO()` _[#if !(SHORT_RANGE_AO_MODE == 2)]_
- L68-71 _function_ `half PackSharedShortRangeAO(half AmbientOcclusion)` _[#if !(SHORT_RANGE_AO_MODE == 2)]_
- L73-76 _function_ `half UnpackSharedShortRangeAO(half AmbientOcclusion)` _[#if !(SHORT_RANGE_AO_MODE == 2)]_
- L124-140 _function_ `bool IsNeighborPixelValid(uint2 InNeighborScreenCoord, uint InClosureIndex, bool bDefaultValue)`
- L142-170 _function_ `float3 GetFilteredNeighborhoodLighting( Texture2DArray LightingTexture, uint2 ScreenCoord, uint2 MinScreenCoord, uint2 MaxScreenCoord, uint InClosureIndex, out bool bLightingIsValid)`
- L172-201 _function_ `float3 ClampHistory( Texture2DArray LightingTexture, uint2 ScreenCoord, uint2 MinScreenCoord, uint2 MaxScreenCoord, float3 NewLighting, float3 HistoryLighting, uint InClosureIndex)`
- L211-219 _function_ `FGatherUV GetGatherUV(Bilinear In, float2 InTexelSize)`
- L234-285 _function_ `FShortRangeAONeighborhood GetShortRangeAONeighborhood(uint2 SharedCoord, TShortRangeAO CenterShortRangeAO)` — Compute local neighborhood statistics _[#if SHORT_RANGE_AO_MODE]_

### `Shaders/Private/Lumen/LumenScreenProbeGatherTemporal.ush` (Private)

- lines: 91; parse: all-branches
- includes: L5 `../StochasticLighting/StochasticLightingCommon.ush`
- L3 #pragma `once`

#### Structs / classes (1)

- L14-18 _struct_ **`Bilinear`** `struct Bilinear`
  - L16 _member_ `float2 Origin;`
  - L17 _member_ `float2 Weights;`

#### Global resources (textures / buffers / samplers) (2)

- L7 _resource_ `Texture2D<uint2> EncodedHistoryScreenCoordTexture;`
- L8 _resource_ `Texture2DArray<uint> PackedPixelDataTexture;`

#### Global parameters (uniforms) (3)

- L10 _parameter_ `float4 HistorySubPixelGridSizeAndInvSize;`
- L11 _parameter_ `uint2 HistoryScreenCoordDecodeShift;`
- L12 _parameter_ `float MaxFramesAccumulated;`

#### Functions (9)

- L20-29 _function_ `Bilinear GetBilinearFilter(uint2 ScreenCoord)`
- L31-39 _function_ `float4 GetBilinearCustomWeights(Bilinear F, float4 CustomWeights)`
- L41-45 _function_ `float4 WeightedAverage(float4 V00, float4 V10, float4 V01, float4 V11, float4 Weights)`
- L47-51 _function_ `float3 WeightedAverage(float3 V00, float3 V10, float3 V01, float3 V11, float4 Weights)`
- L53-56 _function_ `float WeightedAverage(float4 V, float4 Weights)`
- L59-63 _function_ `half4 WeightedAverage(half4 V00, half4 V10, half4 V01, half4 V11, half4 Weights)` _[#if PLATFORM_SUPPORTS_REAL_TYPES]_
- L65-68 _function_ `half WeightedAverage(half4 V, half4 Weights)` _[#if PLATFORM_SUPPORTS_REAL_TYPES]_
- L72-82 _function_ `float PackFastUpdateModeAmountAndNumFramesAccumulated(float FastUpdateModeAmount, float NumFramesAccumulated)` — Pack into 8 bits. NumFramesAccumulated in [3:0] and FastUpdateModeAmount in [7:4]
- L84-91 _function_ `void UnpackFastUpdateModeAmountAndNumFramesAccumulated(float4 Packed, out float4 OutFastUpdateModeAmount, out float4 OutNumFramesAccumulated)`

### `Shaders/Private/Lumen/LumenScreenProbeHardwareRayTracing.usf` (Private)

- lines: 229; parse: all-branches
- includes: L3 `/Engine/Shared/RayTracingTypes.h`, L4 `../Common.ush`, L5 `../MonteCarlo.ush`, L6 `../SceneTextureParameters.ush`, L7 `LumenCardCommon.ush`, L8 `LumenTracingCommon.ush`, L10 `LumenRadianceCacheCommon.ush`, L11 `LumenScreenProbeCommon.ush`, L12 `LumenScreenProbeTracingCommon.ush`, L13 `LumenFloatQuantization.ush`, L40 `LumenHardwareRayTracingCommon.ush` [LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]

#### Macros (#define, 6)

- L9 `#define RADIANCE_CACHE_DEPTH_TEST_SPHERE_PARALLAX 1`
- L16 `#define THREADGROUP_SIZE_2D 8` _[#if !defined(THREADGROUP_SIZE_2D)]_
- L20 `#define THREADGROUP_SIZE_1D THREADGROUP_SIZE_2D * THREADGROUP_SIZE_2D` _[#if !defined(THREADGROUP_SIZE_1D)]_
- L23 `#define RAY_TRACING_PASS_DEFAULT 0`
- L24 `#define RAY_TRACING_PASS_FAR_FIELD 1`
- L25 `#define RAY_TRACING_PASS_HIT_LIGHTING 2`

#### Entry points (2)

- L31-35 _entry_ `[numthreads(1, 1, 1)] void FLumenScreenProbeHardwareRayTracingIndirectArgsCS()` — stage: **compute** — C++: `FLumenScreenProbeGatherHardwareRayTracingIndirectArgsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenScreenProbeHardwareRayTracing.cpp:278) _[#if defined(FLumenScreenProbeHardwareRayTracingIndirectArgsCS)]_
- L71-227 _entry_ `LUMEN_HARDWARE_RAY_TRACING_ENTRY(LumenScreenProbeGatherHardwareRayTracing)` — stage: **raygeneration\|compute(inline)** _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_

#### Global resources (textures / buffers / samplers) (6)

- L27 _resource_ `RWBuffer<uint> RWHardwareRayTracingIndirectArgs;`
- L42 _resource_ `RaytracingAccelerationStructure TLAS;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L43 _resource_ `RaytracingAccelerationStructure FarFieldTLAS;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L46 _resource_ `StructuredBuffer<FHitGroupRootConstants> HitGroupData;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING && LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L47 _resource_ `StructuredBuffer<FRayTracingSceneMetadataRecord> RayTracingSceneMetadata;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING && LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L48 _resource_ `RWStructuredBuffer<uint> RWInstanceHitCountBuffer;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING && LUMEN_HARDWARE_INLINE_RAYTRACING]_

#### Global parameters (uniforms) (20)

- L28 _parameter_ `uint2 OutputThreadGroupSize;`
- L51 _parameter_ `uint HitLightingForceOpaque;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L52 _parameter_ `uint HitLightingShadowMode;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L53 _parameter_ `uint HitLightingShadowTranslucencyMode;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L54 _parameter_ `uint HitLightingDirectLighting;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L55 _parameter_ `uint HitLightingSkylight;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L56 _parameter_ `float MaxTraceDistance;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L57 _parameter_ `float NearFieldSceneRadius;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L58 _parameter_ `float NearFieldMaxTraceDistance;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L59 _parameter_ `float FarFieldBias;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L60 _parameter_ `float FarFieldMaxTraceDistance;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L61 _parameter_ `float PullbackBias;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L62 _parameter_ `float RayTracingBias;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L63 _parameter_ `float RayTracingNormalBias;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L64 _parameter_ `float BiasForTracesFromHairPixels;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L65 _parameter_ `float AvoidSelfIntersectionTraceDistance;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L66 _parameter_ `float SkipFirstTwoSidedHitDistance;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L67 _parameter_ `float MinTraceDistanceToSampleSurfaceCache;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L68 _parameter_ `uint MaxTraversalIterations;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L69 _parameter_ `uint MeshSectionVisibilityTest;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_

### `Shaders/Private/Lumen/LumenScreenProbeImportanceSampling.usf` (Private)

- lines: 496; parse: all-branches
- includes: L3 `../Common.ush`, L4 `LumenMaterial.ush`, L5 `../DeferredShadingCommon.ush`, L6 `LumenRadianceCacheCommon.ush`, L7 `LumenScreenProbeCommon.ush`, L8 `LumenScreenProbeTracingCommon.ush`, L9 `../SHCommon.ush`, L10 `LumenScreenProbeImportanceSamplingShared.ush`

#### Macros (#define, 6)

- L13 `#define THREADGROUP_SIZE 1` _[#if !defined(THREADGROUP_SIZE)]_
- L17 `#define LIGHTING_PDF_THREADGROUP_SIZE 1` _[#if !defined(LIGHTING_PDF_THREADGROUP_SIZE)]_
- L21 `#define GENERATE_RAYS_THREADGROUP_SIZE 1` _[#if !defined(GENERATE_RAYS_THREADGROUP_SIZE)]_
- L202 `#define GENERATE_RAYS_NUM_TOTAL_THREADS (GENERATE_RAYS_THREADGROUP_SIZE * GENERATE_RAYS_THREADGROUP_SIZE)`
- L322 `#define UNIFORM_RAY_DISTRIBUTION_DEBUG 0`
- L385 `#define SERIAL_REFERENCE_DEBUG 0` _[#if !(UNIFORM_RAY_DISTRIBUTION_DEBUG)]_

#### Entry points (2)

- L36-193 _entry_ `[numthreads(LIGHTING_PDF_THREADGROUP_SIZE, LIGHTING_PDF_THREADGROUP_SIZE, 1)] void ScreenProbeComputeLightingProbabilityDensityFunctionCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FScreenProbeComputeLightingProbabilityDensityFunctionCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenScreenProbeImportanceSampling.cpp:179)
- L306-495 _entry_ `[numthreads(GENERATE_RAYS_THREADGROUP_SIZE, GENERATE_RAYS_THREADGROUP_SIZE, 1)] void ScreenProbeGenerateRaysCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FScreenProbeGenerateRaysCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenScreenProbeImportanceSampling.cpp:235)

#### Global resources (textures / buffers / samplers) (7)

- L24 _resource_ `RWTexture2D<float> RWLightingProbabilityDensityFunction;`
- L30 _resource_ `Texture2D<uint> HistoryScreenProbeSceneDepth;`
- L31 _resource_ `Texture2D<float3> HistoryScreenProbeRadiance;`
- L32 _resource_ `Texture2D<float3> HistoryScreenProbeTranslatedWorldPosition;`
- L196 _resource_ `RWTexture2D<uint> RWStructuredImportanceSampledRayInfosForTracing;` — Stores a RayInfo indirection entry for each ray to trace of a Screen Probe, used by tracing passes
- L198 _resource_ `Texture2D<float> BRDFProbabilityDensityFunction;`
- L199 _resource_ `Texture2D<float> LightingProbabilityDensityFunction;`

#### Global parameters (uniforms) (5)

- L26 _parameter_ `float4 ProbeHistoryScreenPositionScaleBias;`
- L27 _parameter_ `float4 ImportanceSamplingHistoryUVMinMax;`
- L28 _parameter_ `float ImportanceSamplingHistoryDistanceThreshold;`
- L29 _parameter_ `float PrevInvPreExposure;`
- L200 _parameter_ `float MinPDFToTrace;`

#### groupshared (3)

- L34 _groupshared_ `groupshared float SharedPDF[LIGHTING_PDF_THREADGROUP_SIZE * LIGHTING_PDF_THREADGROUP_SIZE * 4];`
- L203 _groupshared_ `groupshared uint2 RaysToRefine[GENERATE_RAYS_NUM_TOTAL_THREADS * 2];`
- L204 _groupshared_ `groupshared uint NumRaysToSubdivide;`

#### Functions (5)

- L206-209 _function_ `uint2 PackRaySortInfo(uint2 TexelCoord, uint Level, float PDF)`
- L211-217 _function_ `void UnpackRaySortInfo(uint2 RaySortInfo, out uint2 TexelCoord, out uint Level, out float PDF)`
- L219-222 _function_ `uint Compute1dIndex(uint2 Coord, uint2 Size)`
- L224-231 _function_ `void WriteRay(uint2 ScreenProbeCoord, uint2 TracingRayCoord, uint2 SourceTexelCoord, uint SourceLevel)`
- L233-304 _function_ `uint SubdivideRaysSerialReference(uint2 GroupThreadId)`

### `Shaders/Private/Lumen/LumenScreenProbeImportanceSamplingShared.ush` (Private)

- lines: 8; parse: all-branches

#### Macros (#define, 2)

- L5 `#define NUM_PDF_SH_COEFFICIENTS 9`
- L8 `#define BRDF_PDF_SPHERICAL_HARMONIC 1`
- L3 #pragma `once`

#### Global resources (textures / buffers / samplers) (1)

- L6 _resource_ `Buffer<float> BRDFProbabilityDensityFunctionSH;`

### `Shaders/Private/Lumen/LumenScreenProbeTileClassication.ush` (Private)

- lines: 56; parse: all-branches
- includes: L5 `LumenReflectionsCombine.ush`

#### Macros (#define, 7)

- L7 `#define LUMEN_TILE_BITMASK_GI_SIMPLE_DIFFUSE 0x01`
- L8 `#define LUMEN_TILE_BITMASK_GI_IMPORTANCE_SAMPLE_BRDF 0x02`
- L9 `#define LUMEN_TILE_BITMASK_GI_ALL 0x04`
- L10 `#define LUMEN_TILE_BITMASK_REFLECTIONS 0x08`
- L13 `#define DIFFUSE_INTEGRATION_SPHERICAL_HARMONIC 0`
- L15 `#define DIFFUSE_INTEGRATION_IMPORTANCE_SAMPLE_BRDF 1`
- L17 `#define DIFFUSE_INTEGRATION_NUMERICAL_INTEGRAL 2`
- L3 #pragma `once`

#### Global parameters (uniforms) (3)

- L19 _parameter_ `uint DefaultDiffuseIntegrationMethod;`
- L20 _parameter_ `float MaxRoughnessToEvaluateRoughSpecular;`
- L21 _parameter_ `float MaxRoughnessToEvaluateRoughSpecularForFoliage;`

#### Functions (2)

- L25-37 _function_ `float RoughReflectionsDiffuseLerp(FLumenMaterialData Material)` — Computes the lerp factor to diffuse for rough specular, as an optimization to skip rough specular computations 1 = fully diffuse and rough reflection computation can be skipped
- L39-56 _function_ `uint GetDiffuseIntegrationMethod(FLumenMaterialData In)`

### `Shaders/Private/Lumen/LumenScreenProbeTracing.usf` (Private)

- lines: 1061; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../DeferredShadingCommon.ush`, L5 `LumenCardCommon.ush`, L6 `LumenTracingCommon.ush`, L7 `LumenSoftwareRayTracing.ush`, L9 `LumenRadianceCacheCommon.ush`, L10 `LumenScreenProbeCommon.ush`, L11 `LumenScreenProbeTracingCommon.ush`, L12 `LumenFloatQuantization.ush`, L13 `LumenVisualizeTraces.ush`, L16 `../SHCommon.ush`, L17 `LumenScreenTracing.ush`, L18 `LumenHairTracing.ush`, L19 `../SceneTextureParameters.ush`, L20 `../HZB.ush`

#### Macros (#define, 8)

- L8 `#define RADIANCE_CACHE_DEPTH_TEST_SPHERE_PARALLAX 1`
- L15 `#define IS_SSGI_SHADER 0`
- L23 `#define THREADGROUP_SIZE 0` _[#if !defined(THREADGROUP_SIZE)]_
- L26 `#define DEBUG_VISUALIZE_TRACE_TYPES 0`
- L686 `#define PROBE_TRACE_THREADGROUP_SIZE_1D 32` _[#if THREADGROUP_SIZE_32]_
- L688 `#define PROBE_TRACE_THREADGROUP_SIZE_1D 64` _[#if !(THREADGROUP_SIZE_32)]_
- L814 `#define USE_VOXEL_TRACE_HIT_DISTANCE 0` _[#if defined(ScreenProbeTraceVoxelsCS)]_
- L956 `#define VISUALIZE_SCENE_DEPTH_TEXEL 0` _[#if defined(ScreenProbeSetupVisualizeTraces)]_

#### Entry points (7)

- L30-38 _entry_ `[numthreads(PROBE_THREADGROUP_SIZE_2D, PROBE_THREADGROUP_SIZE_2D, 1)] void ClearTracesCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FClearTracesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenScreenProbeTracing.cpp:166) _[#if defined(ClearTracesCS)]_
- L56-366 _entry_ `[numthreads(PROBE_THREADGROUP_SIZE_2D, PROBE_THREADGROUP_SIZE_2D, 1)] void ScreenProbeTraceScreenTexturesCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FScreenProbeTraceScreenTexturesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenScreenProbeTracing.cpp:264) _[#if defined(ScreenProbeTraceScreenTexturesCS)]_
- L393-499 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void ScreenProbeCompactTracesCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FScreenProbeCompactTracesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenScreenProbeTracing.cpp:326) _[#if defined(ScreenProbeCompactTracesCS)]_
- L507-524 _entry_ `[numthreads(1, 1, 1)] void SetupCompactedTracesIndirectArgsCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FSetupCompactedTracesIndirectArgsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenScreenProbeTracing.cpp:345) _[#if defined(SetupCompactedTracesIndirectArgsCS)]_
- L693-708 _entry_ `[numthreads(PROBE_TRACE_THREADGROUP_SIZE_1D, 1, 1)] void ScreenProbeTraceMeshSDFsCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FScreenProbeTraceMeshSDFsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenScreenProbeTracing.cpp:419) _[#if defined(ScreenProbeTraceMeshSDFsCS)]_
- L874-889 _entry_ `[numthreads(PROBE_TRACE_THREADGROUP_SIZE_1D, 1, 1)] void ScreenProbeTraceVoxelsCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FScreenProbeTraceVoxelsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenScreenProbeTracing.cpp:499) _[#if defined(ScreenProbeTraceVoxelsCS)]_
- L897-1058 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void ScreenProbeSetupVisualizeTraces( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FScreenProbeSetupVisualizeTracesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenScreenProbeTracing.cpp:535) _[#if defined(ScreenProbeSetupVisualizeTraces)]_

#### Global resources (textures / buffers / samplers) (4)

- L372 _resource_ `RWBuffer<uint> RWCompactedTraceTexelAllocator;` _[#if defined(ScreenProbeCompactTracesCS)]_
- L373 _resource_ `RWBuffer<uint> RWCompactedTraceTexelData;` _[#if defined(ScreenProbeCompactTracesCS)]_
- L505 _resource_ `RWBuffer<uint> RWScreenProbeCompactTracingIndirectArgs;` _[#if defined(SetupCompactedTracesIndirectArgsCS)]_
- L895 _resource_ `Texture2D TraceRadiance;` _[#if defined(ScreenProbeSetupVisualizeTraces)]_

#### Global parameters (uniforms) (25)

- L42 _parameter_ `float MaxTraceDistance;`
- L44 _parameter_ `float MaxHierarchicalScreenTraceIterations;`
- L45 _parameter_ `float RelativeDepthThickness;`
- L46 _parameter_ `float HistoryDepthTestRelativeThickness;`
- L47 _parameter_ `float NumThicknessStepsToDetermineCertainty;`
- L48 _parameter_ `uint MinimumTracingThreadOccupancy;`
- L49 _parameter_ `uint SkipFoliageHits;`
- L50 _parameter_ `uint SkipHairHits;`
- L51 _parameter_ `uint SkipUnlitHits;`
- L52 _parameter_ `uint bSupportsHairScreenTraces;`
- L53 _parameter_ `float BiasForTracesFromHairPixels;`
- L375 _parameter_ `uint CullByDistanceFromCamera;` _[#if defined(ScreenProbeCompactTracesCS)]_
- L376 _parameter_ `float CompactionTracingEndDistanceFromCamera;` _[#if defined(ScreenProbeCompactTracesCS)]_
- L377 _parameter_ `float CompactionMaxTraceDistance;` _[#if defined(ScreenProbeCompactTracesCS)]_
- L378 _parameter_ `uint CompactForSkyApply;` _[#if defined(ScreenProbeCompactTracesCS)]_
- L528 _parameter_ `uint CardGridPixelSizeShift;`
- L529 _parameter_ `float3 CardGridZParams;`
- L530 _parameter_ `uint3 CullGridSize;`
- L541 _parameter_ `float StepFactor;`
- L542 _parameter_ `float MinSampleRadius;`
- L543 _parameter_ `float MinTraceDistance;`
- L544 _parameter_ `float SurfaceBias;`
- L545 _parameter_ `float CardInterpolateInfluenceRadius;`
- L546 _parameter_ `float CardTraceEndDistanceFromCamera;`
- L547 _parameter_ `float MaxMeshSDFTraceDistance;`

#### groupshared (4)

- L380 _groupshared_ `groupshared uint SharedGlobalTraceTexelStartOffset;` _[#if defined(ScreenProbeCompactTracesCS)]_
- L383 _groupshared_ `groupshared uint SharedGroupSum;` _[#if defined(ScreenProbeCompactTracesCS) && WAVE_OPS]_
- L386 _groupshared_ `groupshared uint SharedTraceTexelAllocator;` — @todo - ordered compaction for non-wave ops path _[#if defined(ScreenProbeCompactTracesCS) && !(WAVE_OPS)]_
- L387 _groupshared_ `groupshared uint SharedTraceTexels[THREADGROUP_SIZE * THREADGROUP_SIZE];` _[#if defined(ScreenProbeCompactTracesCS) && !(WAVE_OPS)]_

#### Functions (3)

- L532-539 _function_ `uint ComputeCardGridCellIndex(uint2 PixelPos, float SceneDepth)`
- L549-683 _function_ `void TraceMeshSDFs( uint2 ScreenProbeAtlasCoord, uint2 TraceTexelCoord, uint ScreenProbeIndex)`
- L714-872 _function_ `void TraceVoxels( uint2 ScreenProbeAtlasCoord, uint2 TraceTexelCoord, uint ScreenProbeIndex)` _[#if defined(ScreenProbeTraceVoxelsCS)]_

#### Top-level macro invocations (1)

- L391 _macro_call_ `WAVESIZE(32)` _[#if defined(ScreenProbeCompactTracesCS) && COMPILER_SUPPORTS_WAVE_SIZE && WAVE_OPS]_

### `Shaders/Private/Lumen/LumenScreenProbeTracingCommon.ush` (Private)

- lines: 174; parse: all-branches
- includes: L5 `../MonteCarlo.ush`, L6 `../BlueNoise.ush`

#### Macros (#define, 5)

- L10 `#define JITTER_RAY_DIRECTION 1`
- L12 `#define BLUE_NOISE_LUT 1` _[#if JITTER_RAY_DIRECTION]_
- L32 `#define VELOCITY_IS_ACCURATE 0`
- L65 `#define INVALID_TRACING_COORD 0xFE`
- L108 `#define DEINTERLEAVED_TRACE_BUFFER_STORAGE 0`
- L3 #pragma `once`

#### Global resources (textures / buffers / samplers) (4)

- L24 _resource_ `RWTexture2D<uint> RWTraceHit;`
- L25 _resource_ `RWTexture2D<float3> RWTraceRadiance;`
- L26 _resource_ `Texture2D<uint> TraceHit;`
- L61 _resource_ `Texture2D<uint> StructuredImportanceSampledRayInfosForTracing;` — Stores a packed ray info for each tracing shader lane storing the direction and mip level of the ray to trace

#### Global parameters (uniforms) (2)

- L62 _parameter_ `uint MaxImportanceSamplingOctahedronResolution;`
- L63 _parameter_ `uint ScreenProbeBRDFOctahedronResolution;`

#### Functions (15)

- L8-22 _function_ `float2 GetProbeTexelCenter(uint2 ScreenTileCoord)`
- L28-46 _function_ `bool IsTraceMoving(float3 ProbeWorldPosition, float ProbeSceneDepth, uint2 ScreenProbeAtlasCoord, float3 HitWorldPosition, float3 HitWorldVelocity)`
- L48-52 _function_ `float EncodeProbeHitDistanceForFiltering(float HitDistance)`
- L54-58 _function_ `float DecodeProbeHitDistanceForFiltering(float Encoded)`
- L67-71 _function_ `uint PackRayInfo(uint2 TexelCoord, uint Level)`
- L73-78 _function_ `void UnpackRayInfo(uint RayInfo, out uint2 TexelCoord, out uint Level)`
- L80-104 _function_ `void GetProbeTracingUV( uint2 TraceBufferCoord, uint2 TracingTexelCoord, float2 ProbeTexelCenter, float NumSupersamples, out float2 ProbeUV, out float ConeHalfAngle)`
- L106-114 _function_ `uint2 GetTraceBufferCoord(uint2 ScreenProbeAtlasCoord, uint2 TraceTexelCoord)`
- L116-120 _function_ `bool ShouldTraceScreenProbeTexel(uint2 TraceBufferCoord, float ProbeSceneDepth)`
- L122-135 _function_ `void GetScreenProbeTexelRay( uint2 TraceBufferCoord, uint2 TraceTexelCoord, uint2 ScreenTileCoord, float3 TranslatedWorldPosition, inout float3 RayDirection, inout float TraceDistance, inout float ConeHalfAngle)`
- L137-153 _function_ `float3 GetScreenProbeNormalForBiasing(uint2 ScreenProbeAtlasCoord, float3 RayWorldDirection, out bool bBackfaceRay)`
- L155-159 _function_ `float3 GetScreenProbeNormalForBiasing(uint2 ScreenProbeAtlasCoord, float3 RayWorldDirection)`
- L161-164 _function_ `void WriteTraceHit(uint2 TraceBufferCoord, float HitDistance, bool bHit, bool bFastMoving, bool bReachedRadianceCache)`
- L166-169 _function_ `FProbeRayDistance ReadTraceHit(uint2 TraceBufferCoord)`
- L171-174 _function_ `void ReadTraceTexel(uint DispatchThreadId, out uint ScreenProbeIndex, out uint2 TraceTexelCoord)`

### `Shaders/Private/Lumen/LumenScreenSpaceBentNormal.usf` (Private)

- lines: 705; parse: all-branches
- includes: L3 `../Common.ush`, L4 `LumenMaterial.ush`, L5 `../DeferredShadingCommon.ush`, L6 `../BRDF.ush`, L7 `../MonteCarlo.ush`, L8 `../BlueNoise.ush`, L9 `../ShadingModelsSampling.ush`, L10 `../SceneTextureParameters.ush`, L11 `../HZB.ush`, L13 `LumenScreenTracing.ush`, L14 `LumenHairTracing.ush`, L15 `LumenScreenProbeCommon.ush`, L16 `LumenScreenSpaceBentNormal.ush`, L17 `../ShaderPrint.ush`

#### Macros (#define, 5)

- L12 `#define IS_SSGI_SHADER 1`
- L20 `#define THREADGROUP_SIZE 1` _[#if !defined(THREADGROUP_SIZE)]_
- L59 `#define BITMASK_SECTOR_COUNT 32`
- L82 `#define USE_SCENE_COLOR_HISTORY 1`
- L513 `#define TRACE_SCREEN 1`

#### Entry points (1)

- L643-705 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void ScreenSpaceShortRangeAOCS( uint2 GroupId : SV_GroupID, uint2 DispatchThreadId : SV_DispatchThreadID, uint2 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FScreenSpaceShortRangeAOCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenScreenSpaceBentNormal.cpp:387)

#### Global resources (textures / buffers / samplers) (5)

- L630 _resource_ `RWTexture2DArray<uint> RWShortRangeAO;` _[#if OUTPUT_BENT_NORMAL]_
- L632 _resource_ `RWTexture2DArray<UNORM float> RWShortRangeAO;` _[#if !(OUTPUT_BENT_NORMAL)]_
- L635 _resource_ `RWTexture2DArray<float3> RWShortRangeGI;`
- L637 _resource_ `Texture2D<float> DownsampledSceneDepth;`
- L638 _resource_ `Texture2D<UNORM float3> DownsampledWorldNormal;`

#### Global parameters (uniforms) (12)

- L72 _parameter_ `float HistoryDepthTestRelativeThickness;`
- L73 _parameter_ `float2 MaxScreenFractionForAO;`
- L74 _parameter_ `float MaxScreenFractionForGI;`
- L75 _parameter_ `float MaxRayIntensity;`
- L207 _parameter_ `float ForegroundSampleRejectDistanceFraction;`
- L208 _parameter_ `float ForegroundSampleRejectPower;`
- L276 _parameter_ `float SliceCount;`
- L277 _parameter_ `float StepsPerSliceForAO;`
- L278 _parameter_ `float StepsPerSliceForGI;`
- L483 _parameter_ `float SlopeCompareToleranceScale;`
- L640 _parameter_ `uint2 ShortRangeAOViewMin;`
- L641 _parameter_ `uint2 ShortRangeAOViewSize;`

#### Functions (8)

- L24-56 _function_ `float3x3 BuildRotationMatrix(float3 FromDirection, float3 ToDirection)` — "Efficiently building a matrix to rotate one vector to another"
- L62-70 _function_ `uint GetOccludedBitmaskFromHorizonAngles(inout FShaderPrintContext Context, float MinHorizon, float MaxHorizon)` — Converts a min and max horizon angle into a bitmask
- L77-129 _function_ `float3 SampleSceneColor(float3 HitUVz)`
- L131-140 _function_ `float SampleSceneDepth(float2 ScreenUV)`
- L142-205 _function_ `void UpdateOccludedBitmaskForStep( inout FShaderPrintContext Context, float2 SampleScreenPos, float3 ViewSpacePosition, float3 ViewVector, float3 ViewNormal, float SampleThickness, float InvForegroundDistance, float SamplingDirection, float NormalAngle, bool bUpdateAO, float FadeForGI, inout uint OccludedBitmask, inout uint OccludedBitmaskForGI, inout float3 Lighting)`
- L210-274 _function_ `void UpdateOccludedHorizonForStep( inout FShaderPrintContext Context, float2 SampleScreenPos, float3 ViewSpacePosition, float3 ViewVector, float3 ViewNormal, float InvForegroundDistance, float LowHorizonCos, bool bUpdateAO, float FadeForGI, inout float HorizonCos, inout float HorizonCosForGI, inout float3 Lighting)`
- L280-481 _function_ `void CalculateAOHorizonSearch( FLumenMaterialCoord Coord, float SceneDepth, float3 WorldNormal, out float OutAO, out float3 OutBentNormal, out float3 OutLighting)`
- L485-627 _function_ `void CalculateAOStochasticHemisphere( float2 ScreenUV, FLumenMaterialCoord Coord, float SceneDepth, float3 TranslatedWorldPosition, float3 WorldNormal, float TraceDistance, out float OutAO, out float3 OutBentNormal)`

### `Shaders/Private/Lumen/LumenScreenSpaceBentNormal.ush` (Private)

- lines: 61; parse: all-branches
- L3 #pragma `once`

#### Functions (7)

- L5-8 _function_ `float IrradianceBounce0Rescale(float AO)`
- L10-15 _function_ `float IrradianceBounce1Rescale(float AO)`
- L19-26 _function_ `float3 DistantIlluminationRescale(float3 DiffuseColor, float AO)` — From "2018 Patapom - Improved Ambient Occlusion" This version applies AO, remapped to approximate energy lost due to multibounce, assuming the surface causing the occlusion has the same albedo as our albedo
- L28-38 _function_ `float ApproximateConeConeIntersection(float ArcLength0, float ArcLength1, float AngleBetweenCones)`
- L40-51 _function_ `float CalculateSpecularOcclusion(float3 N, float Roughness, float AO, float3 V, float3 BentNormalOcclusion)`
- L53-56 _function_ `uint PackScreenBentNormal(float3 BentNormal)`
- L58-61 _function_ `float3 UnpackScreenBentNormal(uint PackedBentNormal)`

### `Shaders/Private/Lumen/LumenScreenTracing.ush` (Private)

- lines: 213; parse: all-branches
- includes: L5 `../Common.ush`, L6 `../HZBTracing.ush`, L7 `LumenMaterial.ush`, L8 `../FastMath.ush`, L9 `../SceneTextureParameters.ush`, L10 `LumenPosition.ush`, L11 `../HZB.ush`, L63 `../SSRT/SSRTRayCast.ush`
- L3 #pragma `once`

#### Global resources (textures / buffers / samplers) (3)

- L65 _resource_ `Texture2D PrevSceneColorTexture;`
- L66 _resource_ `Texture2D HistorySceneDepth;`
- L142 _resource_ `Texture2D DistantScreenTraceFurthestHZBTexture;`

#### Global parameters (uniforms) (9)

- L67 _parameter_ `float2 PrevSceneColorBilinearUVMin;`
- L68 _parameter_ `float2 PrevSceneColorBilinearUVMax;`
- L69 _parameter_ `float4 PrevScreenPositionScaleBias;`
- L70 _parameter_ `float4 PrevScreenPositionScaleBiasForDepth;`
- L71 _parameter_ `float PrevSceneColorPreExposureCorrection;`
- L73 _parameter_ `float SampleSceneColorNormalTreshold;`
- L139 _parameter_ `float DistantScreenTraceSlopeCompareTolerance;`
- L140 _parameter_ `float DistantScreenTraceMaxTraceDistance;`
- L141 _parameter_ `float DistantScreenTraceStepOffsetBias;`

#### Functions (4)

- L17-26 _function_ `void ApplyScreenSpaceRayBias(inout float3 TranslatedWorldPosition, float3 SceneWorldNormal, float2 ScreenUV, float SceneDepth)` — Bias along the normal to avoid self-intersecting camera facing scene depth texels HZB traversal uses point filtering, so scene depth texels stick out from the plane they are representing
- L28-61 _function_ `void TraceScreen( float3 RayTranslatedWorldOrigin, float3 RayWorldDirection, float MaxWorldTraceDistance, float4 InHZBUvFactorAndInvFactor, float MaxIterations, float RelativeDepthThickness, float NumThicknessStepsToDetermineCertainty, uint MinimumTracingThreadOccupancy, inout bool bHit, inout bool bUncertain, inout float3 OutScreenUV, inout float3 OutLastVisibleScreenUV, inout float OutHitTileZ)`
- L78-137 _function_ `bool SampleSceneColorAtHit(float3 HitTranslatedWorldPosition, float3 HitGeometryWorldNormal, uint2 SvPosition, float RelativeDepthThickness, inout float3 Lighting)` — Try to sample scene color at hit and return whether it was successfull
- L144-213 _function_ `void DistantScreenTrace( float2 NoiseCoord, float4 InHZBUvFactorAndInvFactor, float3 TranslatedRayOrigin, float3 RayDirection, float TraceDistance, float SceneDepth, inout bool bHit, inout float3 TraceRadiance)`

### `Shaders/Private/Lumen/LumenShortRangeAOHardwareRayTracing.usf` (Private)

- lines: 167; parse: all-branches
- includes: L5 `../Common.ush`, L6 `LumenMaterial.ush`, L7 `../DeferredShadingCommon.ush`, L8 `../BRDF.ush`, L9 `../MonteCarlo.ush`, L10 `../BlueNoise.ush`, L11 `../ShadingModelsSampling.ush`, L12 `../SceneTextureParameters.ush`, L13 `../RayTracing/RayTracingCommon.ush`, L14 `../RayTracing/RayTracingDeferredShadingCommon.ush`, L15 `LumenHairTracing.ush`, L16 `LumenPosition.ush`, L17 `LumenScreenProbeCommon.ush`, L18 `LumenScreenSpaceBentNormal.ush`

#### Macros (#define, 2)

- L3 `#define SUBSTRATE_MATERIALCONTAINER_IS_VIEWRESOURCE 1`
- L21 `#define THREADGROUP_SIZE 1` _[#if !defined(THREADGROUP_SIZE)]_

#### Entry points (1)

- L41-167 _entry_ `RAY_TRACING_ENTRY_RAYGEN(LumenShortRangeAOHardwareRayTracing)` — stage: **raygeneration** — C++: `FLumenShortRangeAOHardwareRayTracing` SF_RayGen via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenShortRangeAOHardwareRayTracing.cpp:132)

#### Global resources (textures / buffers / samplers) (5)

- L24 _resource_ `RaytracingAccelerationStructure TLAS;`
- L27 _resource_ `RWTexture2DArray<uint> RWShortRangeAO;` _[#if OUTPUT_BENT_NORMAL]_
- L29 _resource_ `RWTexture2DArray<UNORM float> RWShortRangeAO;` _[#if !(OUTPUT_BENT_NORMAL)]_
- L32 _resource_ `Texture2D<float> DownsampledSceneDepth;`
- L33 _resource_ `Texture2D<UNORM float3> DownsampledWorldNormal;`

#### Global parameters (uniforms) (5)

- L35 _parameter_ `uint NumRays;`
- L36 _parameter_ `float NormalBias;`
- L37 _parameter_ `float MaxScreenTraceFraction;`
- L38 _parameter_ `uint2 ShortRangeAOViewMin;`
- L39 _parameter_ `uint2 ShortRangeAOViewSize;`

### `Shaders/Private/Lumen/LumenSoftwareRayTracing.ush` (Private)

- lines: 889; parse: all-branches
- includes: L5 `../ReflectionEnvironmentShared.ush`, L6 `../BRDF.ush`, L7 `../FastMath.ush`, L9 `../DistanceField/GlobalDistanceFieldShared.ush`, L10 `../DistanceField/GlobalDistanceFieldUtils.ush`, L11 `../DistanceField/GlobalDistanceFieldObjectGrid.ush`, L12 `../DistanceFieldLightingShared.ush`, L13 `../SceneData.ush`

#### Macros (#define, 5)

- L8 `#define DISTANCE_FIELD_IN_VIEW_UB 1`
- L16 `#define SDF_TRACING_TRAVERSE_MIPS 0` _[#if !defined(SDF_TRACING_TRAVERSE_MIPS)]_
- L20 `#define SCENE_TRACE_MESH_SDFS 1` _[#if !defined(SCENE_TRACE_MESH_SDFS)]_
- L24 `#define SCENE_TRACE_HEIGHTFIELDS 0` _[#if !defined(SCENE_TRACE_HEIGHTFIELDS)]_
- L712 `#define DEBUG_CELL_COUNTER 0`
- L3 #pragma `once`

#### Structs / classes (7)

- L27-107 _struct_ **`FConeTraceInput`** `struct FConeTraceInput`
  - L29 _member_ `float3 ConeOrigin;`
  - L30 _member_ `float3 ConeTranslatedOrigin;`
  - L31 _member_ `float3 ConeDirection;`
  - L33 _member_ `float ConeAngle;` — View.EyeToPixelSpreadAngle or RayCone.Spread in HWRT world
  - L34 _member_ `float TanConeAngle;`
  - L36 _member_ `float ConeStartRadius;`
  - L37 _member_ `float MinSampleRadius;`
  - L38 _member_ `float MinTraceDistance;`
  - L39 _member_ `float MaxTraceDistance;`
  - L41 _member_ `float StepFactor;`
  - L42 _member_ `float VoxelTraceStartDistance;`
  - L43 _member_ `float SDFStepFactor;`
  - L44 _member_ `float MinSDFStepFactor;`
  - L45 _member_ `bool bExpandSurfaceUsingRayTimeInsteadOfMaxDistance;`
  - L46 _member_ `float InitialMaxDistance;`
  - L48 _member_ `bool bDitheredTransparency;`
  - L49 _member_ `uint2 DitherScreenCoord;`
  - L52 _member_ `bool bUseEpsilonTraceForHeightfields;` — Whether to use epsilon trace (skip back face hits over initial short distance) for heightfield tracing
  - L55 _member_ `bool bHiResSurface;` — Whether to sample high res surface cache data or low res always resident pages
  - L57 _member_ `bool bZeroRadianceIfRayStartsInsideGeometry;`
  - L58 _member_ `bool bCalculateHitVelocity;`
  - L61 _member_ `uint NumMeshSDFs;` — Mesh SDF traces
  - L62 _member_ `uint MeshSDFStartOffset;`
  - L63 _member_ `uint MeshSDFBitmaskStartOffset;`
  - L64 _member_ `float CardInterpolateInfluenceRadius;`
  - L67 _member_ `uint NumHeightfields;` — Heightfield traces
  - L68 _member_ `uint HeightfieldStartOffset;`
  - L70 _method_ `void Setup( float3 InConeOrigin, float3 InConeTranslatedOrigin, float3 InConeDirection, float InConeAngle, float InMinSampleRadius, float InMinTraceDistance, float InMaxTraceDistance, float InStepFactor)`
- L114-118 _struct_ **`FTraceMeshSDFResult`** `struct FTraceMeshSDFResult`
  - L116 _member_ `float HitDistance;`
  - L117 _member_ `uint HitObject;`
- L270-276 _struct_ **`FTraceMeshSDFDerivedData`** `struct FTraceMeshSDFDerivedData`
  - L272 _member_ `float3 HitNormal;`
  - L273 _member_ `uint SceneInstanceIndex;`
  - L274 _member_ `uint MeshCardsIndex;`
  - L275 _member_ `float3 WorldVelocity;`
- L324-329 _struct_ **`FConeTraceHeightfieldSimpleResult`** `struct FConeTraceHeightfieldSimpleResult`
  - L326 _member_ `bool bIsHit;`
  - L327 _member_ `bool bHitFrontFace;`
  - L328 _member_ `float HitDistance;`
- L331-337 _struct_ **`FHeightfieldRayStep`** `struct FHeightfieldRayStep`
  - L333 _member_ `float tValue;`
  - L334 _member_ `float3 LocalSamplePosition;`
  - L335 _member_ `float LocalHeightfieldDepth;`
  - L336 _member_ `bool bAboveHeightfield;`
- L491-498 _struct_ **`FTraceMeshHeightfieldResult`** `struct FTraceMeshHeightfieldResult`
  - L493 _member_ `FLumenCardData LumenCardData;`
  - L494 _member_ `int LocalCardIndex;`
  - L495 _member_ `float HitDistance;`
  - L496 _member_ `int TotalStepCount;`
  - L497 _member_ `uint HeightfieldObjectIndex;`
- L500-504 _struct_ **`FTraceMeshHeightfieldShadedResult`** `struct FTraceMeshHeightfieldShadedResult`
  - L502 _member_ `float3 Lighting;`
  - L503 _member_ `float Opacity;`

#### Global resources (textures / buffers / samplers) (9)

- L110 _resource_ `Buffer<uint> NumGridCulledMeshSDFObjects;` — Mesh SDF cull grid
- L111 _resource_ `Buffer<uint> GridCulledMeshSDFObjectStartOffsetArray;`
- L112 _resource_ `Buffer<uint> GridCulledMeshSDFObjectIndicesArray;`
- L317 _resource_ `Buffer<uint> NumCulledHeightfieldObjects;`
- L318 _resource_ `Buffer<uint> CulledHeightfieldObjectIndexBuffer;`
- L320 _resource_ `Buffer<uint> NumGridCulledHeightfieldObjects;`
- L321 _resource_ `Buffer<uint> GridCulledHeightfieldObjectStartOffsetArray;`
- L322 _resource_ `Buffer<uint> GridCulledHeightfieldObjectIndicesArray;`
- L634 _resource_ `StructuredBuffer<uint4> GlobalDistanceFieldPageObjectGridBuffer;`

#### Global parameters (uniforms) (5)

- L120 _parameter_ `float MeshSDFNotCoveredExpandSurfaceScale;`
- L121 _parameter_ `float MeshSDFNotCoveredMinStepScale;`
- L122 _parameter_ `float MeshSDFDitheredTransparencyStepThreshold;`
- L382 _parameter_ `int HeightfieldMaxTracingSteps;`
- L635 _parameter_ `uint GlobalDistanceFieldPageObjectGridBufferSize;`

#### Functions (16)

- L124-260 _function_ `void RayTraceSingleMeshSDF( float3 WorldRayStart, float3 WorldRayDirection, float TanConeHalfAngle, float MinTraceDistance, float MaxTraceDistance, uint ObjectIndex, bool bExpandSurfaceUsingRayTimeInsteadOfMaxDistance, float InitialMaxDistance, bool bDitheredTransparency, float2 DitherScreenCoord, inout FTraceMeshSDFResult TraceResult)`
- L262-268 _function_ `float3 GetPrevWorldPositionFromGPUSceneInstanceIndex(float3 WorldPosition, uint GPUSceneInstanceIndex)`
- L278-315 _function_ `FTraceMeshSDFDerivedData CalculateMeshSDFDerivedData( float3 WorldRayStart, float3 WorldRayDirection, float TraceDistance, bool bCalculateHitVelocity, FTraceMeshSDFResult TraceMeshSDFResult)`
- L339-355 _function_ `FHeightfieldRayStep HeightfieldRayStep(FLumenCardData LumenCardData, uint LocalCardIndex, FConeTraceInput TraceInput, float3 LocalConeOrigin, float3 LocalConeDirection, float tValue)`
- L357-380 _function_ `bool EvaluateHeightfieldHit( FLumenCardData LumenCardData, uint LocalCardIndex, FConeTraceInput TraceInput, float3 LocalConeOrigin, float3 LocalConeDirection, FHeightfieldRayStep PrevStep, FHeightfieldRayStep Step, float StepSize, float tMinValue, float tMaxValue, inout FConeTraceHeightfieldSimpleResult Result)`
- L384-489 _function_ `FConeTraceHeightfieldSimpleResult ConeTraceHeightfieldSimple( FConeTraceInput TraceInput, uint HeightfieldIndex )`
- L506-571 _function_ `FTraceMeshHeightfieldResult ConeTraceHeightfield( FConeTraceInput TraceInput, inout FConeTraceResult OutResult )`
- L573-632 _function_ `void ConeTraceMeshSDFsAndInterpolateFromCards( FConeTraceInput TraceInput, inout FConeTraceResult OutResult)`
- L637-763 _function_ `void EvaluateGlobalDistanceFieldHit(FConeTraceInput TraceInput, FGlobalSDFTraceResult SDFTraceResult, inout FConeTraceResult ConeTraceResult)`
- L768-796 _function_ `void RayTraceGlobalDistanceField( FConeTraceInput TraceInput, inout FConeTraceResult OutResult)` — Ray trace the Global Distance Field, compute hit point and hit normal, and then evaluate radiance from surface cache
- L798-802 _function_ `float ComputeSquaredDistanceBetweenAABBs(float3 CenterA, float3 ExtentA, float3 CenterB, float3 ExtentB)`
- L804-819 _function_ `float CalculateVoxelTraceStartDistance(float MinTraceDistance, float MaxTraceDistance, float MaxMeshSDFTraceDistance, bool bContinueCardTracing)`
- L821-838 _function_ `void ConeTraceLumenSceneCards( FConeTraceInput TraceInput, inout FConeTraceResult OutResult)`
- L840-860 _function_ `void ConeTraceLumenSceneHeightfields( FConeTraceInput TraceInput, inout FConeTraceResult OutResult)`
- L862-880 _function_ `void ConeTraceLumenSceneVoxels( FConeTraceInput TraceInput, inout FConeTraceResult OutResult)`
- L882-889 _function_ `void ConeTraceLumenScene( FConeTraceInput TraceInput, inout FConeTraceResult OutResult)`

### `Shaders/Private/Lumen/LumenTracingCommon.ush` (Private)

- lines: 128; parse: all-branches
- includes: L5 `../ReflectionEnvironmentShared.ush`, L6 `../HeightFogCommon.ush`, L7 `SurfaceCache/LumenSurfaceCacheSampling.ush`

#### Macros (#define, 1)

- L10 `#define ENABLE_DYNAMIC_SKY_LIGHT 1` _[#if !defined(ENABLE_DYNAMIC_SKY_LIGHT)]_
- L3 #pragma `once`

#### Structs / classes (1)

- L13-24 _struct_ **`FConeTraceResult`** `struct FConeTraceResult`
  - L15 _member_ `float3 Lighting;`
  - L16 _member_ `float Transparency;`
  - L17 _member_ `float NumSteps;`
  - L18 _member_ `float NumOverlaps;`
  - L19 _member_ `float OpaqueHitDistance;`
  - L20 _member_ `float ExpandSurfaceAmount;`
  - L21 _member_ `float3 Debug;`
  - L22 _member_ `float3 GeometryWorldNormal;`
  - L23 _member_ `float3 WorldVelocity;`

#### Global parameters (uniforms) (7)

- L64 _parameter_ `float3 SkylightLeakingColor;`
- L65 _parameter_ `float ReflectionSkylightLeakingAverageAlbedo;`
- L66 _parameter_ `float SkylightLeakingRoughness;`
- L67 _parameter_ `float InvFullSkylightLeakingDistance;`
- L68 _parameter_ `uint SampleHeightFog;`
- L69 _parameter_ `uint SampleHeightFogOnGI;`
- L70 _parameter_ `float MinDistanceForFoggingSky;`

#### Functions (8)

- L26-30 _function_ `float TanConeAngleToRoughness(float TanConeAngle)`
- L32-48 _function_ `float3 EvaluateSkyRadiance(float3 Direction)`
- L50-62 _function_ `void ApplySkylightToTraceResult(float3 ConeDirection, inout FConeTraceResult TraceResult)`
- L72-75 _function_ `float CalculateSkylightLeakingDistanceFactor(float HitDistance)`
- L77-88 _function_ `float3 GetSkylightLeaking(float3 ConeDirection, float HitDistance)`
- L92-103 _function_ `float3 GetSkylightLeakingForReflections(float3 ConeDirection, float3 HitNormal, float HitDistance)` — Reflections should look exactly like primary view. In order to achieve that, Skylight leaking approximates GetSkylightLeaking for the hit point.
- L105-113 _function_ `float3 ClampMaxRayIntensity(float3 Radiance, float MaxRayIntensity)`
- L115-128 _function_ `float3 GetFogOnLuminance(in float3 SurfaceLuminance, in float3 RayOrigin, in float3 RayDir, in float HitPosDistance, bool bIsHit)`

### `Shaders/Private/Lumen/LumenTranslucencyRadianceCacheMarkShaders.usf` (Private)

- lines: 157; parse: all-branches
- includes: L7 `../Common.ush`, L8 `../BRDF.ush`, L13 `/Engine/Generated/Material.ush`, L14 `/Engine/Generated/VertexFactory.ush`, L20 `LumenRadianceCacheMarkCommon.ush`, L30 `../TranslucencyVolumeCommon.ush`

#### Macros (#define, 4)

- L11 `#define SceneTexturesStruct LumenTranslucencyRadianceCacheMarkPass.SceneTextures`
- L17 `#define RadianceCacheMark LumenTranslucencyRadianceCacheMarkPass`
- L18 `#define RWRadianceProbeIndirectionTexture LumenTranslucencyRadianceCacheMarkPass.RWRadianceProbeIndirectionTexture`
- L116 `#define CULL_TO_HZB 1`

#### Entry points (2)

- L44-70 _entry_ `void MainVS( FVertexFactoryInput Input, out FLumenTranslucencyRadianceCacheMarkVSToPS Output )` — stage: **vertex (from C++ binding)** — C++: `FLumenTranslucencyRadianceCacheMarkVS` SF_Vertex via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/Lumen/LumenTranslucencyRadianceCache.cpp:111)
- L95-157 _entry_ `EARLYDEPTHSTENCIL void MainPS( FVertexFactoryInterpolantsVSToPS Interpolants, FLumenTranslucencyRadianceCacheMarkInterpolantsVSToPS PassInterpolants, in INPUT_POSITION_QUALIFIERS float4 SvPosition : SV_Position OPTIONAL_IsFrontFace)` — stage: **pixel (from C++ binding)** — C++: `FLumenTranslucencyRadianceCacheMarkPS` SF_Pixel via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/Lumen/LumenTranslucencyRadianceCache.cpp:133)

#### Structs / classes (2)

- L32-35 _struct_ **`FLumenTranslucencyRadianceCacheMarkInterpolantsVSToPS`** `struct FLumenTranslucencyRadianceCacheMarkInterpolantsVSToPS`
- L37-42 _struct_ **`FLumenTranslucencyRadianceCacheMarkVSToPS`** `struct FLumenTranslucencyRadianceCacheMarkVSToPS`
  - L39 _member_ `FVertexFactoryInterpolantsVSToPS FactoryInterpolants;`
  - L40 _member_ `FLumenTranslucencyRadianceCacheMarkInterpolantsVSToPS PassInterpolants;`
  - L41 _member_ `float4 Position : SV_POSITION;`

#### Global resources (textures / buffers / samplers) (6)

- L23 _resource_ `Texture3D TranslucencyLightingVolumeAmbientInner;` — unused but necessary to avoid error compiling TranslucencyVolumeCommon.ush on some platforms
- L24 _resource_ `Texture3D TranslucencyLightingVolumeAmbientOuter;`
- L25 _resource_ `Texture3D TranslucencyLightingVolumeDirectionalInner;`
- L26 _resource_ `Texture3D TranslucencyLightingVolumeDirectionalOuter;`
- L27 _resource_ `Texture3D TranslucencySpecularDirectionInner;`
- L28 _resource_ `Texture3D TranslucencySpecularDirectionOuter;`

#### Functions (2)

- L72-78 _function_ `void MarkTranslucencyLightingVoxel(RWTexture3D<uint> MarkTexture, int3 VoxelCoord)`
- L80-93 _function_ `void MarkTranslucencyLightingVoxelTrilinear(RWTexture3D<uint> MarkTexture, float3 UVs)`

### `Shaders/Private/Lumen/LumenTranslucencyVolumeHardwareRayTracing.usf` (Private)

- lines: 163; parse: all-branches
- includes: L8 `../HairStrands/HairStrandsVoxelPageCommonStruct.ush`, L10 `/Engine/Shared/RayTracingTypes.h`, L11 `../Common.ush`, L12 `../SHCommon.ush`, L13 `../MonteCarlo.ush`, L14 `../OctahedralCommon.ush`, L15 `../SceneTextureParameters.ush`, L17 `LumenCardCommon.ush`, L18 `LumenTracingCommon.ush`, L19 `LumenRadianceCacheCommon.ush`, L20 `LumenTranslucencyVolumeLightingShared.ush`, L21 `LumenFloatQuantization.ush`, L24 `LumenHardwareRayTracingCommon.ush` [LUMEN_HARDWARE_RAYTRACING]

#### Macros (#define, 2)

- L27 `#define DIM_LIGHTING_MODE LIGHTING_FROM_SURFACE_CACHE` _[#if LUMEN_HARDWARE_RAYTRACING && !defined(DIM_LIGHTING_MODE)]_
- L50 `#define DEINTERLEAVED_VOLUME_TRACING 0` _[#if LUMEN_HARDWARE_RAYTRACING]_

#### Entry points (1)

- L44-160 _entry_ `LUMEN_HARDWARE_RAY_TRACING_ENTRY(LumenTranslucencyVolumeHardwareRayTracing)` — stage: **raygeneration\|compute(inline)** _[#if LUMEN_HARDWARE_RAYTRACING]_

#### Global resources (textures / buffers / samplers) (7)

- L30 _resource_ `RaytracingAccelerationStructure TLAS;` _[#if LUMEN_HARDWARE_RAYTRACING]_
- L31 _resource_ `RaytracingAccelerationStructure FarFieldTLAS;` _[#if LUMEN_HARDWARE_RAYTRACING]_
- L34 _resource_ `StructuredBuffer<FHitGroupRootConstants> HitGroupData;` _[#if LUMEN_HARDWARE_RAYTRACING && LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L35 _resource_ `StructuredBuffer<FRayTracingSceneMetadataRecord> RayTracingSceneMetadata;` _[#if LUMEN_HARDWARE_RAYTRACING && LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L36 _resource_ `RWStructuredBuffer<uint> RWInstanceHitCountBuffer;` _[#if LUMEN_HARDWARE_RAYTRACING && LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L39 _resource_ `RWTexture3D<float3> RWVolumeTraceRadiance;` _[#if LUMEN_HARDWARE_RAYTRACING]_
- L40 _resource_ `RWTexture3D<float> RWVolumeTraceHitDistance;` _[#if LUMEN_HARDWARE_RAYTRACING]_

#### Global parameters (uniforms) (2)

- L41 _parameter_ `uint MaxTraversalIterations;` _[#if LUMEN_HARDWARE_RAYTRACING]_
- L42 _parameter_ `uint MeshSectionVisibilityTest;` _[#if LUMEN_HARDWARE_RAYTRACING]_

### `Shaders/Private/Lumen/LumenTranslucencyVolumeLighting.usf` (Private)

- lines: 342; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../SHCommon.ush`, L5 `../MonteCarlo.ush`, L6 `../OctahedralCommon.ush`, L7 `../SceneTextureParameters.ush`, L9 `LumenCardCommon.ush`, L10 `LumenTracingCommon.ush`, L11 `LumenSoftwareRayTracing.ush`, L12 `LumenRadianceCacheCommon.ush`, L13 `LumenRadianceCacheMarkCommon.ush`, L14 `LumenTranslucencyVolumeLightingShared.ush`, L15 `LumenScreenProbeCommon.ush`, L16 `../RayTracing/RayGenUtils.ush`, L17 `LumenRadianceCacheTracingCommon.ush`, L18 `LumenFloatQuantization.ush`

#### Macros (#define, 5)

- L21 `#define THREADGROUP_SIZE 1` _[#if !defined(THREADGROUP_SIZE)]_
- L25 `#define PROBE_SOURCE_MODE 0` _[#if !defined(PROBE_SOURCE_MODE)]_
- L28 `#define FROXEL_POS_OFFSET 1`
- L30 `#define FROXEL_PROBE_DEBUG_COLOR 0`
- L82 `#define DEINTERLEAVED_VOLUME_TRACING 0` _[#if defined(TranslucencyVolumeTraceVoxelsCS)]_

#### Entry points (4)

- L39-68 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, THREADGROUP_SIZE)] void MarkRadianceProbesUsedByTranslucencyVolumeCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FMarkRadianceProbesUsedByTranslucencyVolumeCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenTranslucencyVolumeLighting.cpp:449) _[#if defined(MarkRadianceProbesUsedByTranslucencyVolumeCS)]_
- L76-168 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void TranslucencyVolumeTraceVoxelsCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FTranslucencyVolumeTraceVoxelsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenTranslucencyVolumeLighting.cpp:500) _[#if defined(TranslucencyVolumeTraceVoxelsCS)]_
- L190-224 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void TranslucencyVolumeSpatialSeparableFilterCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FTranslucencyVolumeSpatialSeparableFilterCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenTranslucencyVolumeLighting.cpp:541) _[#if defined(TranslucencyVolumeSpatialSeparableFilterCS)]_
- L239-340 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, THREADGROUP_SIZE)] void TranslucencyVolumeIntegrateCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FTranslucencyVolumeIntegrateCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenTranslucencyVolumeLighting.cpp:588) _[#if defined(TranslucencyVolumeIntegrateCS)]_

#### Global resources (textures / buffers / samplers) (12)

- L71 _resource_ `RWTexture3D<float3> RWVolumeTraceRadiance;`
- L72 _resource_ `RWTexture3D<float> RWVolumeTraceHitDistance;`
- L73 _resource_ `Texture3D<float3> VolumeFroxelProbeRadianceHitDistance;` — Only float3, filtering out the unused distance for now.
- L171 _resource_ `Texture3D<float3> VolumeTraceRadiance;`
- L172 _resource_ `Texture3D<float> VolumeTraceHitDistance;`
- L227 _resource_ `RWTexture3D<float4> RWTranslucencyGI0;`
- L228 _resource_ `RWTexture3D<float4> RWTranslucencyGI1;`
- L229 _resource_ `RWTexture3D<float4> RWTranslucencyGINewHistory0;`
- L230 _resource_ `RWTexture3D<float4> RWTranslucencyGINewHistory1;`
- L232 _resource_ `Texture3D TranslucencyGIHistory0;`
- L233 _resource_ `Texture3D TranslucencyGIHistory1;`
- L234 _resource_ `SamplerState TranslucencyGIHistorySampler;`

#### Global parameters (uniforms) (6)

- L174 _parameter_ `float3 PreviousFrameJitterOffset;`
- L175 _parameter_ `float4x4 UnjitteredPrevWorldToClip;`
- L177 _parameter_ `int SpatialFilterSampleCount;`
- L178 _parameter_ `int3 SpatialFilterDirection;`
- L179 _parameter_ `float3 SpatialFilterGaussParams;`
- L236 _parameter_ `float HistoryWeight;`

#### Functions (1)

- L181-187 _function_ `float GaussianWeight1d(float Distance)`

### `Shaders/Private/Lumen/LumenTranslucencyVolumeLightingShared.ush` (Private)

- lines: 146; parse: all-branches
- includes: L9 `../BlueNoise.ush`, L10 `../HZB.ush`

#### Macros (#define, 3)

- L12 `#define PROBE_SOURCE_MODE_NONE 0`
- L13 `#define PROBE_SOURCE_MODE_RADIANCE_CACHE 1`
- L130 `#define HZB_OCCLUSION_TEST 1`
- L7 #pragma `once`

#### Global parameters (uniforms) (18)

- L15 _parameter_ `uint TranslucencyVolumeTracingOctahedronResolution;`
- L16 _parameter_ `uint3 TranslucencyGIGridSize;`
- L17 _parameter_ `float3 TranslucencyGIGridZParams;`
- L18 _parameter_ `uint TranslucencyGIGridPixelSizeShift;`
- L20 _parameter_ `float2 TranslucencyGIScreenToResourceUV;`
- L21 _parameter_ `float2 TranslucencyGIScreenToResourceMaxUV;`
- L23 _parameter_ `int FroxelDirectionJitterFrameIndex;`
- L24 _parameter_ `float3 FrameJitterOffset;`
- L25 _parameter_ `float4x4 UnjitteredClipToTranslatedWorld;`
- L26 _parameter_ `float GridCenterOffsetFromDepthBuffer;`
- L27 _parameter_ `float GridCenterOffsetThresholdToAcceptDepthBufferOffset;`
- L119 _parameter_ `float HZBMipLevel;`
- L141 _parameter_ `float MaxTraceDistance;`
- L142 _parameter_ `float MaxMeshSDFTraceDistance;`
- L143 _parameter_ `float StepFactor;`
- L144 _parameter_ `float VoxelTraceStartDistanceScale;`
- L145 _parameter_ `float MaxRayIntensity;`
- L146 _parameter_ `uint RadianceCacheClipmapBias;`

#### Functions (11)

- L29-33 _function_ `float ComputeDepthFromZSlice(float ZSlice)`
- L35-39 _function_ `float ComputeZSliceFromDepth(float SliceDepth)`
- L41-51 _function_ `float3 ComputeCellTranslatedWorldPosition(uint3 GridCoordinate, float3 CellOffset, out float SceneDepth)`
- L53-57 _function_ `float3 ComputeCellTranslatedWorldPosition(uint3 GridCoordinate, float3 CellOffset)`
- L59-62 _function_ `float3 ComputeCellWorldPosition(uint3 GridCoordinate, float3 CellOffset)`
- L65-87 _function_ `void ApplyDepthConstraintsToOffset(float3 GridCoordinate, inout float3 LocalFrameJitterOffset)` — Applying an offset from the depth buffer helps with reducing self intersection with global distance field tracing.
- L89-101 _function_ `float3 ComputeTranslucencyGIVolumeUV(float3 WorldPosition, float4x4 WorldToClip, out float3 ScreenUV )`
- L103-112 _function_ `void GetProbeTracingUV( float2 TracingTexelCoord, float2 ProbeTexelCenter, out float2 ProbeUV, out float ConeHalfAngle)`
- L114-117 _function_ `float2 GetProbeTexelCenter(uint2 GridCoordinate)`
- L121-126 _function_ `float GetMaxVisibleDepth(uint2 GridCoordinate)`
- L128-139 _function_ `bool IsFroxelVisible(uint3 GridCoordinate)`

### `Shaders/Private/Lumen/LumenTranslucencyVolumeShared.ush` (Private)

- lines: 69; parse: all-branches
- includes: L7 `LumenRadianceCacheInterpolation.ush`, L8 `../SHCommon.ush`

#### Macros (#define, 2)

- L15 `#define LumenTransLightVolumeSharedSampler View.SharedBilinearClampedSampler` _[#if SUPPORTS_INDEPENDENT_SAMPLERS]_
- L17 `#define LumenTransLightVolumeSharedSampler LumenGIVolumeStruct.TranslucencyGIVolumeSampler` _[#if !(SUPPORTS_INDEPENDENT_SAMPLERS)]_
- L12 #pragma `message("UESHADERMETADATA_VERSION F35DABF2-F5F7-4F7C-9056-AF53F2A1DB60")`

#### Functions (3)

- L20-23 _function_ `bool IsLumenTranslucencyGIEnabled()`
- L25-36 _function_ `float3 ComputeTranslucencyGIVolumeUV(FDFVector3 WorldPosition, FDFInverseMatrix WorldToClip)`
- L38-68 _function_ `FTwoBandSHVectorRGB GetTranslucencyGIVolumeLighting(FDFVector3 WorldPosition, FDFInverseMatrix WorldToClip, bool bTemporalFiltered)`

### `Shaders/Private/Lumen/LumenUpsample.ush` (Private)

- lines: 92; parse: all-branches
- includes: L6 `../Common.ush`, L7 `LumenMaterial.ush`, L8 `LumenPosition.ush`, L9 `../DeferredShadingCommon.ush`, L10 `../StochasticLighting/StochasticLightingCommon.ush`, L11 `../StochasticLighting/StochasticLightingUpsample.ush`

#### Macros (#define, 1)

- L4 `#define USE_HAIR_COMPLEX_TRANSMITTANCE 1`
- L2 #pragma `once`

#### Global resources (textures / buffers / samplers) (2)

- L24 _resource_ `Texture2D<float> DownsampledSceneDepth;`
- L25 _resource_ `Texture2D<UNORM float3> DownsampledSceneWorldNormal;`

#### Global parameters (uniforms) (3)

- L13 _parameter_ `uint2 IntegrateViewMin;`
- L14 _parameter_ `uint2 IntegrateViewSize;`
- L15 _parameter_ `float2 DownsampledBufferInvSize;`

#### Functions (3)

- L17-22 _function_ `float2 DownsampledCoordToScreenUV(uint2 DownsampledCoord, uint DownsampleFactor)`
- L27-35 _function_ `float GetNormalWeight(float3 SceneWorldNormal, uint2 DownsampledScreenCoord)`
- L37-91 _function_ `uint2 GetStochasticBilinearOffsetForUpsample(uint2 SvPosition, float2 ScreenUV, float3 TranslatedWorldPosition, float3 WorldNormal, float SceneDepth, float RandomScalar, uint DownsampleFactor)`

### `Shaders/Private/Lumen/LumenVirtualTextureCommon.ush` (Private)

- lines: 101; parse: all-branches
- includes: L6 `../VirtualTextureCommon.ush`

#### Macros (#define, 1)

- L5 `#define NUM_VIRTUALTEXTURE_SAMPLES 1`
- L3 #pragma `once`

#### Global resources (textures / buffers / samplers) (4)

- L49 _resource_ `Texture2D HeightVirtualTexture;`
- L50 _resource_ `Texture2D<uint4> HeightVirtualTexturePageTable;`
- L51 _resource_ `Texture2D<uint> HeightVirtualTexturePageTableIndirection;`
- L53 _resource_ `SamplerState HeightVirtualTextureSampler;`

#### Global parameters (uniforms) (7)

- L52 _parameter_ `uint HeightVirtualTextureAdaptive;`
- L54 _parameter_ `float3 HeightVirtualTextureLWCTile;`
- L55 _parameter_ `float4x4 HeightVirtualTextureWorldToUVTransform;`
- L56 _parameter_ `uint HeightVirtualTextureEnabled;`
- L57 _parameter_ `uint4 HeightVirtualTexturePackedUniform0;`
- L58 _parameter_ `uint4 HeightVirtualTexturePackedUniform1;`
- L59 _parameter_ `uint4 HeightVirtualTextureUniforms;`

#### Functions (2)

- L8-47 _function_ `float4 SampleVirtualTextureLayer( float2 InSampleUV, Texture2D InTexture, SamplerState InSampler, Texture2D<uint4> InPageTable, Texture2D<uint> InPageTableIndirection, uint InAdaptive, uint4 InUniforms, uint4 PageTableUniform0, uint4 PageTableUniform1, out uint OutSampledMipLevel)`
- L61-100 _function_ `void SampleHeightVirtualTexture( float3 InWorldPos, out bool bOutInsideVolume, out uint OutSampledMipLevel, out float OutWorldHeight)`

### `Shaders/Private/Lumen/LumenVisualize.usf` (Private)

- lines: 336; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../DeferredShadingCommon.ush`, L5 `../SHCommon.ush`, L6 `../ShaderPrint.ush`, L7 `LumenCardCommon.ush`, L8 `LumenTracingCommon.ush`, L9 `LumenSoftwareRayTracing.ush`, L11 `LumenRadianceCacheCommon.ush`, L12 `LumenVisualizeTraces.ush`, L13 `LumenVisualize.ush`, L14 `../ShaderPrint.ush`

#### Macros (#define, 3)

- L10 `#define RADIANCE_CACHE_DEPTH_TEST_SPHERE_PARALLAX 1`
- L30 `#define THREADGROUP_SIZE 0` _[#if !defined(THREADGROUP_SIZE)]_
- L147 `#define TRACE_VISUALIZE_MODE 0` _[#if defined(VisualizeQuadsCS)]_

#### Entry points (6)

- L34-172 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void VisualizeQuadsCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FVisualizeLumenSceneCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenVisualize.cpp:390) _[#if defined(VisualizeQuadsCS)]_
- L179-254 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void VisualizeCursorDataCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FVisualizeLumenSceneCursorDataCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenVisualize.cpp:440) _[#if defined(VisualizeCursorDataCS)]_
- L264-280 _entry_ `void VisualizeTracesVS( uint VertexIndex : SV_VertexID, out FVisualizeTracesVertexOutput Output, out float4 OutPosition : SV_POSITION )` — stage: **vertex (from C++ binding)** — C++: `FVisualizeTracesVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenVisualize.cpp:491)
- L282-288 _entry_ `void VisualizeTracesPS( FVisualizeTracesVertexOutput Input, in float4 SVPos : SV_POSITION, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FVisualizeTracesPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenVisualize.cpp:513)
- L296-310 _entry_ `void VisualizeBitFieldFloatTexturePS( in noperspective float4 UVAndScreenPos : TEXCOORD0, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FVisualizeBitFieldFloatTexturePS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenVisualize.cpp:468)
- L315-335 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void VisualizeTracesCS( uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FVisualizeTracesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenVisualize.cpp:551) _[#if defined(VisualizeTracesCS)]_

#### Structs / classes (1)

- L259-262 _struct_ **`FVisualizeTracesVertexOutput`** `struct FVisualizeTracesVertexOutput`
  - L261 _member_ `float3 TraceLighting : TEXCOORD0;`

#### Global resources (textures / buffers / samplers) (6)

- L26 _resource_ `RWTexture2D<float4> RWSceneColor;`
- L27 _resource_ `Buffer<uint> CulledCardGridHeader;`
- L177 _resource_ `StructuredBuffer<uint> DebugData;` _[#if defined(VisualizeCursorDataCS)]_
- L257 _resource_ `Buffer<float4> VisualizeTracesData;`
- L290 _resource_ `Texture2D SceneColorTexture;`
- L291 _resource_ `Texture2D InputTexture;`

#### Global parameters (uniforms) (13)

- L16 _parameter_ `uint3 CullGridSize;`
- L17 _parameter_ `uint CardGridPixelSizeShift;`
- L18 _parameter_ `int VisualizeTileIndex;`
- L19 _parameter_ `float VisualizeStepFactor;`
- L20 _parameter_ `float MinTraceDistance;`
- L21 _parameter_ `float MaxTraceDistance;`
- L22 _parameter_ `float MaxMeshSDFTraceDistanceForVoxelTracing;`
- L23 _parameter_ `float MaxMeshSDFTraceDistance;`
- L24 _parameter_ `float CardInterpolateInfluenceRadius;`
- L292 _parameter_ `float2 ToIntMulAdd;`
- L293 _parameter_ `float2 PreOutputMulAdd;`
- L294 _parameter_ `uint2 BitMaskShift;`
- L313 _parameter_ `uint NumTracesToVisualize;` _[#if defined(VisualizeTracesCS)]_

### `Shaders/Private/Lumen/LumenVisualize.ush` (Private)

- lines: 76; parse: all-branches
- includes: L4 `../StochasticLighting/StochasticLightingVisualize.ush`, L5 `../ShaderPrint.ush`, L6 `LumenReflectionsCombine.ush`, L7 `LumenMaterial.ush`
- L2 #pragma `once`

#### Global parameters (uniforms) (5)

- L9 _parameter_ `uint VisualizeHiResSurface;`
- L10 _parameter_ `uint2 InputViewSize;`
- L11 _parameter_ `uint2 InputViewOffset;`
- L12 _parameter_ `uint2 OutputViewSize;`
- L13 _parameter_ `uint2 OutputViewOffset;`

#### Functions (1)

- L18-76 _function_ `ISOLATE void LumenVisualizationFinalize( uint2 OutputScreenCoord, float2 ViewportUV, float3 CameraVector, inout float3 FinalColor)` — Common Lumen Visualization part, shared between SWRT and HWRT visualization shaders.

### `Shaders/Private/Lumen/LumenVisualizeHardwareRayTracing.usf` (Private)

- lines: 667; parse: all-branches
- includes: L12 `/Engine/Shared/RayTracingTypes.h`, L13 `../Common.ush`, L14 `../MonteCarlo.ush`, L15 `../SceneTextureParameters.ush`, L16 `../VelocityCommon.ush`, L22 `LumenCardCommon.ush`, L23 `LumenTracingCommon.ush`, L24 `LumenVisualize.ush`, L32 `LumenHardwareRayTracingCommon.ush` [LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING], L36 `LumenHairTracing.ush`

#### Macros (#define, 19)

- L7 `#define SUBSTRATE_MATERIALCONTAINER_IS_VIEWRESOURCE 0` _[#if DIM_HIT_LIGHTING == 1]_
- L9 `#define SUBSTRATE_MATERIALCONTAINER_IS_VIEWRESOURCE 1` _[#if !(DIM_HIT_LIGHTING == 1)]_
- L19 `#define PreIntegratedGF ReflectionStruct.PreIntegratedGF`
- L20 `#define PreIntegratedGFSampler GlobalBilinearClampedSampler`
- L35 `#define USE_HAIRSTRANDS_VOXEL DIM_HAIRSTRANDS_VOXEL`
- L39 `#define THREADGROUP_SIZE_2D 8` _[#if !defined(THREADGROUP_SIZE_2D)]_
- L43 `#define THREADGROUP_SIZE_1D THREADGROUP_SIZE_2D * THREADGROUP_SIZE_2D` _[#if !defined(THREADGROUP_SIZE_1D)]_
- L47 `#define DISPATCH_GROUP_SIZE_X 0` _[#if !defined(DISPATCH_GROUP_SIZE_X)]_
- L299 `#define COMPACT_MODE_HIT_LIGHTING_RETRACE 0` _[#if defined(FLumenVisualizeCompactRaysCS)]_
- L300 `#define COMPACT_MODE_FORCE_HIT_LIGHTING 1` _[#if defined(FLumenVisualizeCompactRaysCS)]_
- L352 `#define ELEMENTS_PER_THREAD 16` _[#if !defined(ELEMENTS_PER_THREAD)]_
- L367 `#define NUM_BINS (THREADGROUP_SIZE_1D / 2)` _[#if defined(FLumenVisualizeBucketRaysByMaterialIdCS)]_
- L371 `#define NUM_ELEMENTS THREADGROUP_SIZE_1D * ELEMENTS_PER_THREAD` _[#if defined(FLumenVisualizeBucketRaysByMaterialIdCS)]_
- L442 `#define DIM_LIGHTING_MODE LIGHTING_FROM_SURFACE_CACHE` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING && !defined(DIM_LIGHTING_MODE)]_
- L445 `#define TRACE_MODE_DEFAULT_TRACE 0` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L446 `#define TRACE_MODE_HIT_LIGHTING_RETRACE 1` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L562 `#define DEBUG_VISUAL_ASSERT_ON_RETRACE_MISS 0` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING && DIM_HIT_LIGHTING]_
- L582 `#define DEBUG_VISUALIZE_BACKFACE_HITS 0` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING && !(DIM_HIT_LIGHTING)]_
- L644 `#define DEBUG_VISUALIZE_SKYLIGHT_LEAKING 0` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L29 #undef `ENABLE_TRACING_FEEDBACK`

#### Entry points (7)

- L91-119 _entry_ `[numthreads(THREADGROUP_SIZE_2D, THREADGROUP_SIZE_2D, 1)] void FLumenVisualizeCreateTilesCS( uint2 GroupId : SV_GroupID, uint2 GroupThreadId : SV_GroupThreadID, uint2 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FLumenVisualizeCreateTilesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenVisualizeHardwareRayTracing.cpp:180) _[#if defined(FLumenVisualizeCreateTilesCS)]_
- L171-213 _entry_ `[numthreads(THREADGROUP_SIZE_1D, 1, 1)] void FLumenVisualizeCreateRaysCS( uint2 GroupId : SV_GroupID, uint GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FLumenVisualizeCreateRaysCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenVisualizeHardwareRayTracing.cpp:221) _[#if defined(FLumenVisualizeCreateRaysCS)]_
- L220-224 _entry_ `[numthreads(1, 1, 1)] void FLumenVisualizeCompactRaysIndirectArgsCS()` — stage: **compute** — C++: `FLumenVisualizeCompactRaysIndirectArgsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenVisualizeHardwareRayTracing.cpp:250) _[#if defined(FLumenVisualizeCompactRaysIndirectArgsCS)]_
- L303-346 _entry_ `[numthreads(THREADGROUP_SIZE_1D, 1, 1)] void FLumenVisualizeCompactRaysCS( uint GroupThreadId : SV_GroupThreadID, uint DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FLumenVisualizeCompactRaysCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenVisualizeHardwareRayTracing.cpp:294) _[#if defined(FLumenVisualizeCompactRaysCS)]_
- L356-361 _entry_ `[numthreads(1, 1, 1)] void FLumenVisualizeBucketRaysByMaterialIdIndirectArgsCS()` — stage: **compute** — C++: `FLumenVisualizeBucketRaysByMaterialIdIndirectArgsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenVisualizeHardwareRayTracing.cpp:323) _[#if defined(FLumenVisualizeBucketRaysByMaterialIdIndirectArgsCS)]_
- L373-433 _entry_ `[numthreads(THREADGROUP_SIZE_1D, 1, 1)] void FLumenVisualizeBucketRaysByMaterialIdCS( uint GroupId : SV_GroupID, uint GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FLumenVisualizeBucketRaysByMaterialIdCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenVisualizeHardwareRayTracing.cpp:364) _[#if defined(FLumenVisualizeBucketRaysByMaterialIdCS)]_
- L475-664 _entry_ `LUMEN_HARDWARE_RAY_TRACING_ENTRY(LumenVisualizeHardwareRayTracing)` — stage: **raygeneration\|compute(inline)** _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_

#### Structs / classes (6)

- L50-53 _struct_ **`FTileData`** `struct FTileData`
  - L52 _member_ `uint2 TileCoord;`
- L63-66 _struct_ **`FTileDataPacked`** `struct FTileDataPacked`
  - L65 _member_ `uint PackedData;`
- L122-125 _struct_ **`FRayData`** `struct FRayData`
  - L124 _member_ `uint2 TraceCoord;`
- L135-138 _struct_ **`FRayDataPacked`** `struct FRayDataPacked`
  - L137 _member_ `uint PackedData;`
- L235-243 _struct_ **`FTraceDataLocal`** `struct FTraceDataLocal` — TraceData can represent three types of rays: 1) Rays that hit an object with a valid surface-cache entry 2) Rays that hit an object with an invalid surface-cache entry 3) Rays that do not hit an object after having traveled 'TraceDistance' units NOTE: Miss rays need additional data and must be determined by the caller.
  - L237 _member_ `float TraceDistance;`
  - L238 _member_ `uint MaterialId;`
  - L240 _member_ `bool bIsHit;`
  - L241 _member_ `bool bIsValidMeshCardIndex;`
  - L242 _member_ `bool bIsFarField;`
- L245-248 _struct_ **`FTraceDataLocalPacked`** `struct FTraceDataLocalPacked`
  - L247 _member_ `uint PackedData[2];`

#### Global resources (textures / buffers / samplers) (20)

- L85 _resource_ `RWBuffer<uint> RWTileAllocator;`
- L86 _resource_ `RWStructuredBuffer<FTileDataPacked> RWTileDataPacked;`
- L158 _resource_ `Buffer<uint> TileAllocator;`
- L159 _resource_ `StructuredBuffer<FTileDataPacked> TileDataPacked;`
- L163 _resource_ `RWBuffer<uint> RWRayAllocator;`
- L164 _resource_ `RWStructuredBuffer<FRayDataPacked> RWRayDataPacked;`
- L216 _resource_ `Buffer<uint> RayAllocator;`
- L217 _resource_ `RWBuffer<uint> RWCompactRaysIndirectArgs;`
- L287 _resource_ `StructuredBuffer<FRayDataPacked> RayDataPacked;`
- L288 _resource_ `StructuredBuffer<FTraceDataLocalPacked> TraceDataPacked;`
- L292 _resource_ `RWBuffer<uint> RWCompactedRayAllocator;`
- L293 _resource_ `RWStructuredBuffer<FRayDataPacked> RWCompactedRayDataPacked;`
- L294 _resource_ `RWStructuredBuffer<FTraceDataLocalPacked> RWCompactedTraceDataPacked;`
- L349 _resource_ `RWBuffer<uint> RWBucketRaysByMaterialIdIndirectArgs;`
- L364 _resource_ `RWStructuredBuffer<FTraceDataLocalPacked> RWTraceDataPacked;`
- L437 _resource_ `RWTexture2D<float3> RWRadiance;`
- L448 _resource_ `RaytracingAccelerationStructure TLAS;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L449 _resource_ `RaytracingAccelerationStructure FarFieldTLAS;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L452 _resource_ `StructuredBuffer<FHitGroupRootConstants> HitGroupData;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING && LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L453 _resource_ `StructuredBuffer<FRayTracingSceneMetadataRecord> RayTracingSceneMetadata;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING && LUMEN_HARDWARE_INLINE_RAYTRACING]_

#### Global parameters (uniforms) (19)

- L160 _parameter_ `float MaxTraceDistance;`
- L161 _parameter_ `float FarFieldMaxTraceDistance;`
- L290 _parameter_ `uint MaxRayAllocationCount;`
- L456 _parameter_ `uint ThreadCount;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L457 _parameter_ `uint GroupCount;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L459 _parameter_ `uint HitLightingForceOpaque;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L460 _parameter_ `uint HitLightingShadowMode;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L461 _parameter_ `uint HitLightingShadowTranslucencyMode;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L462 _parameter_ `uint HitLightingDirectLighting;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L463 _parameter_ `uint HitLightingSkylight;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L464 _parameter_ `uint UseReflectionCaptures;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L466 _parameter_ `uint VisualizeCullingMode;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L467 _parameter_ `uint MaxTraversalIterations;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L468 _parameter_ `uint MeshSectionVisibilityTest;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L469 _parameter_ `float NearFieldMaxTraceDistanceDitherScale;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L470 _parameter_ `float NearFieldSceneRadius;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L471 _parameter_ `uint ApplySkylightStage;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L472 _parameter_ `uint MaxReflectionBounces;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_
- L473 _parameter_ `uint MaxRefractionBounces;` _[#if LUMEN_HARDWARE_RAYTRACING \|\| LUMEN_HARDWARE_INLINE_RAYTRACING]_

#### groupshared (7)

- L89 _groupshared_ `groupshared uint SharedTileNeedsTracing;` _[#if defined(FLumenVisualizeCreateTilesCS)]_
- L166 _groupshared_ `groupshared uint SharedGroupOffset;`
- L167 _groupshared_ `groupshared uint SharedRayAllocator;`
- L168 _groupshared_ `groupshared FRayDataPacked SharedRayDataPacked[THREADGROUP_SIZE_1D];`
- L297 _groupshared_ `groupshared FTraceDataLocalPacked SharedTraceDataPacked[THREADGROUP_SIZE_1D];` _[#if defined(FLumenVisualizeCompactRaysCS)]_
- L368 _groupshared_ `groupshared uint BinSize[NUM_BINS];` _[#if defined(FLumenVisualizeBucketRaysByMaterialIdCS)]_
- L369 _groupshared_ `groupshared uint BinOffset[NUM_BINS];` _[#if defined(FLumenVisualizeBucketRaysByMaterialIdCS)]_

#### Functions (9)

- L55-61 _function_ `FTileData CreateTileData(uint2 TileCoord)`
- L68-74 _function_ `FTileDataPacked PackTileData(FTileData TileData)`
- L76-83 _function_ `FTileData UnpackTileData(FTileDataPacked TileDataPacked)`
- L127-133 _function_ `FRayData CreateRayData(uint2 TraceCoord)`
- L140-147 _function_ `FRayDataPacked PackRayData(FRayData RayData)`
- L149-156 _function_ `FRayData UnpackRayData(FRayDataPacked RayDataPacked)`
- L250-260 _function_ `FTraceDataLocal CreateTraceData(float TraceDistance, uint MaterialId, bool bIsHit, bool bIsValidMeshCardIndex, bool bIsFarField)`
- L262-273 _function_ `FTraceDataLocalPacked PackTraceData(FTraceDataLocal TraceData)`
- L275-285 _function_ `FTraceDataLocal UnpackTraceData(FTraceDataLocalPacked TraceDataPacked)`

### `Shaders/Private/Lumen/LumenVisualizeRadianceCache.usf` (Private)

- lines: 273; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../SHCommon.ush`, L5 `LumenTracingCommon.ush`, L6 `LumenIrradianceFieldInterpolation.ush`

#### Macros (#define, 9)

- L71 `#define VISUALIZE_MODE_RADIANCE 1`
- L72 `#define VISUALIZE_MODE_SKY_VISIBILITY 2`
- L136 `#define VISUALIZE_IDEAL_PROBE_POSITION 0` _[#if ADAPTIVE_PROBES]_
- L208 `#define DEBUG_VISUALIZE_PROBE_OCCLUSION 0` _[#if !(VISUALIZE_MODE == VISUALIZE_MODE_SKY_VISIBILITY) && RADIANCE_CACHE_IRRADIANCE]_
- L213 `#define DEBUG_VISUALIZE_PROBES_WITH_OFFSETS 1` _[#if !(VISUALIZE_MODE == VISUALIZE_MODE_SKY_VISIBILITY) && RADIANCE_CACHE_IRRADIANCE]_
- L221 `#define DEBUG_VISUALIZE_BACKFACE_HITS 0` _[#if !(VISUALIZE_MODE == VISUALIZE_MODE_SKY_VISIBILITY) && RADIANCE_CACHE_IRRADIANCE]_
- L229 `#define DEBUG_VISUALIZE_UNIFORM_PROBES_WITH_ADAPTIVE_PROBES 0` _[#if !(VISUALIZE_MODE == VISUALIZE_MODE_SKY_VISIBILITY) && RADIANCE_CACHE_IRRADIANCE]_
- L237 `#define DEBUG_VISUALIZE_INVALID_PROBES 1` _[#if !(VISUALIZE_MODE == VISUALIZE_MODE_SKY_VISIBILITY) && RADIANCE_CACHE_IRRADIANCE]_
- L245 `#define DEBUG_VISUALIZE_ADAPTIVE_PROBES 1` _[#if !(VISUALIZE_MODE == VISUALIZE_MODE_SKY_VISIBILITY) && RADIANCE_CACHE_IRRADIANCE]_

#### Entry points (4)

- L15-29 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void ClearProbeVisualizeBufferCS( uint DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FClearProbeVisualizeBufferCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenVisualizeRadianceCache.cpp:79) _[#if defined(ClearProbeVisualizeBufferCS)]_
- L35-67 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, THREADGROUP_SIZE)] void BuildProbeVisualizeBufferCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FBuildProbeVisualizeBufferCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenVisualizeRadianceCache.cpp:115) _[#if defined(BuildProbeVisualizeBufferCS)]_
- L99-166 _entry_ `void VisualizeRadianceCacheVS( uint VertexId : SV_VertexID, uint InstanceId : SV_InstanceID, out FVisualizeRadianceCacheVSToPS Output, out float4 OutPosition : SV_POSITION )` — stage: **vertex (from C++ binding)** — C++: `FVisualizeRadianceCacheVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenVisualizeRadianceCache.cpp:142)
- L168-272 _entry_ `void VisualizeRadianceCachePS( FVisualizeRadianceCacheVSToPS Input, out float4 OutColor : SV_Target0 )` — stage: **pixel (from C++ binding)** — C++: `FVisualizeRadianceCachePS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/Lumen/LumenVisualizeRadianceCache.cpp:191)

#### Structs / classes (1)

- L80-86 _struct_ **`FVisualizeRadianceCacheVSToPS`** `struct FVisualizeRadianceCacheVSToPS`
  - L82 _member_ `nointerpolation float3 ProbeCoord : TEXCOORD0;`
  - L83 _member_ `nointerpolation uint AdaptiveProbeArrayIndex : TEXCOORD1;`
  - L84 _member_ `nointerpolation float4 CellSphere : TEXCOORD2;`
  - L85 _member_ `float3 PositionTWS : TEXCOORD3;`

#### Global resources (textures / buffers / samplers) (4)

- L10 _resource_ `RWBuffer<uint> RWProbeVisualizeBufferIndirectArguments;`
- L11 _resource_ `RWBuffer<uint4> RWProbeVisualizeBuffer;`
- L77 _resource_ `Buffer<uint4> ProbeVisualizeBuffer;`
- L78 _resource_ `Buffer<uint> LastFrameProbeInterpolationMisses;`

#### Global parameters (uniforms) (3)

- L8 _parameter_ `uint ProbeClipmapIndex;`
- L74 _parameter_ `float4 ClipmapCornerTWSAndCellSizeForVisualization;`
- L75 _parameter_ `float VisualizeProbeRadiusScale;`

#### Functions (1)

- L88-97 _function_ `float3 GetProbeTranslatedWorldPositionForVisualization(uint3 ProbeCoord, uint ProbeIndex)`

### `Shaders/Private/Lumen/LumenVisualizeTraces.ush` (Private)

- lines: 16; parse: all-branches

#### Macros (#define, 1)

- L5 `#define VISUALIZE_TRACE_DATA_STRIDE 3`
- L3 #pragma `once`

#### Global resources (textures / buffers / samplers) (1)

- L9 _resource_ `RWBuffer<float4> RWVisualizeTracesData;`

#### Global parameters (uniforms) (1)

- L7 _parameter_ `uint VisualizeTraceCoherency;`

#### Functions (1)

- L11-16 _function_ `void WriteTraceForVisualization(uint TraceIndex, float3 WorldPosition, float3 WorldDirection, float TraceHitDistance, float3 TraceRadiance)`

### `Shaders/Private/Lumen/RayTracedTranslucency.usf` (Private)

- lines: 719; parse: all-branches
- includes: L9 `/Engine/Shared/RayTracingTypes.h`, L10 `../Common.ush`, L11 `../MonteCarlo.ush`, L12 `../SceneTextureParameters.ush`, L21 `LumenMaterial.ush`, L22 `LumenCardCommon.ush`, L23 `LumenTracingCommon.ush`, L24 `LumenReflectionCommon.ush`, L26 `LumenRadianceCacheCommon.ush`, L30 `../PathTracing/Material/PathTracingFresnel.ush`, L42 `LumenHardwareRayTracingCommon.ush` [LUMEN_HARDWARE_RAYTRACING]

#### Macros (#define, 9)

- L4 `#define SUBSTRATE_SSS_MATERIAL_OVERRIDE 0`
- L5 `#define SUBSTRATE_COMPLEXSPECIALPATH 1`
- L6 `#define SUBSTRATE_GLINTS_ALLOWED 0`
- L7 `#define SUBSTREATE_SIMPLEVOLUME_ENVALBEDO_LUT_JITTERING 1`
- L15 `#define SUBSTRATE_MATERIALCONTAINER_IS_VIEWRESOURCE 0`
- L18 `#define PreIntegratedGF ReflectionStruct.PreIntegratedGF`
- L19 `#define PreIntegratedGFSampler GlobalBilinearClampedSampler`
- L33 `#define THREADGROUP_SIZE_2D 8` _[#if !defined(THREADGROUP_SIZE_2D)]_
- L37 `#define THREADGROUP_SIZE_1D THREADGROUP_SIZE_2D * THREADGROUP_SIZE_2D` _[#if !defined(THREADGROUP_SIZE_1D)]_

#### Entry points (1)

- L631-716 _entry_ `LUMEN_HARDWARE_RAY_TRACING_ENTRY(RayTracedTranslucencyHardwareRayTracing)` — stage: **raygeneration\|compute(inline)** _[#if LUMEN_HARDWARE_RAYTRACING]_

#### Global resources (textures / buffers / samplers) (6)

- L44 _resource_ `RaytracingAccelerationStructure TLAS;` _[#if LUMEN_HARDWARE_RAYTRACING]_
- L45 _resource_ `RaytracingAccelerationStructure FarFieldTLAS;` _[#if LUMEN_HARDWARE_RAYTRACING]_
- L66 _resource_ `RWTexture2DArray<float3> RWTraceRadiance;` _[#if LUMEN_HARDWARE_RAYTRACING]_
- L67 _resource_ `RWTexture2DArray<float3> RWTraceThroughput;` _[#if LUMEN_HARDWARE_RAYTRACING]_
- L68 _resource_ `RWTexture2DArray<UNORM float2> RWTraceBackgroundVisibility;` _[#if LUMEN_HARDWARE_RAYTRACING]_
- L69 _resource_ `RWTexture2DArray<float> RWTraceHit;` _[#if LUMEN_HARDWARE_RAYTRACING]_

#### Global parameters (uniforms) (15)

- L47 _parameter_ `uint TranslucencyForceOpaque;` _[#if LUMEN_HARDWARE_RAYTRACING]_
- L48 _parameter_ `uint HitLightingShadowMode;` _[#if LUMEN_HARDWARE_RAYTRACING]_
- L49 _parameter_ `uint HitLightingShadowTranslucencyMode;` _[#if LUMEN_HARDWARE_RAYTRACING]_
- L50 _parameter_ `uint HitLightingDirectLighting;` _[#if LUMEN_HARDWARE_RAYTRACING]_
- L51 _parameter_ `uint HitLightingSkylight;` _[#if LUMEN_HARDWARE_RAYTRACING]_
- L52 _parameter_ `uint UseReflectionCaptures;` _[#if LUMEN_HARDWARE_RAYTRACING]_
- L54 _parameter_ `float NearFieldMaxTraceDistance;` _[#if LUMEN_HARDWARE_RAYTRACING]_
- L55 _parameter_ `uint MaxTraversalIterations;` _[#if LUMEN_HARDWARE_RAYTRACING]_
- L56 _parameter_ `uint MeshSectionVisibilityTest;` _[#if LUMEN_HARDWARE_RAYTRACING]_
- L58 _parameter_ `float SecondaryPathStartBias;` _[#if LUMEN_HARDWARE_RAYTRACING]_
- L59 _parameter_ `float SecondaryPathStartNormalBias;` _[#if LUMEN_HARDWARE_RAYTRACING]_
- L60 _parameter_ `float PathThroughputThreshold;` _[#if LUMEN_HARDWARE_RAYTRACING]_
- L62 _parameter_ `int MaxPrimaryHitEvents;` _[#if LUMEN_HARDWARE_RAYTRACING]_
- L63 _parameter_ `int MaxSecondaryHitEvents;` _[#if LUMEN_HARDWARE_RAYTRACING]_
- L64 _parameter_ `uint SampleTranslucentReflectionInReflections;` _[#if LUMEN_HARDWARE_RAYTRACING]_

#### Functions (13)

- L71-101 _function_ `void TraceRayWithPotentialRetrace( RaytracingAccelerationStructure TLAS, FRayDesc Ray, FRayTracedLightingContext Context, inout FLumenRayHitBookmark Bookmark, inout FPackedMaterialClosestHitPayload Payload)` _[#if LUMEN_HARDWARE_RAYTRACING]_
- L103-106 _function_ `bool IsPrimaryRay(int SecondaryPathIndex)` _[#if LUMEN_HARDWARE_RAYTRACING]_
- L109-120 _function_ `bool IsRayBent(int SecondaryPathIndex, float3 PrimaryPathThroughput)` _[#if LUMEN_HARDWARE_RAYTRACING && USE_RAY_TRACED_REFRACTION]_
- L122-133 _function_ `void SetRayBent(bool bValue, int SecondaryPathIndex, inout float3 PrimaryPathThroughput)` _[#if LUMEN_HARDWARE_RAYTRACING && USE_RAY_TRACED_REFRACTION]_
- L135-141 _function_ `void UpdatePrimaryPathThroughput(float3 NewValue, inout float3 PrimaryPathThroughput)` _[#if LUMEN_HARDWARE_RAYTRACING && USE_RAY_TRACED_REFRACTION]_
- L145 _function_ `bool IsRayBent(int SecondaryPathIndex, float3 PrimaryPathThroughput)` _[#if LUMEN_HARDWARE_RAYTRACING && !(USE_RAY_TRACED_REFRACTION)]_
- L146 _function_ `void SetRayBent(bool bValue, int SecondaryPathIndex, inout float3 PrimaryPathThroughput)` _[#if LUMEN_HARDWARE_RAYTRACING && !(USE_RAY_TRACED_REFRACTION)]_
- L147 _function_ `void UpdatePrimaryPathThroughput(float3 NewValue, inout float3 PrimaryPathThroughput)` _[#if LUMEN_HARDWARE_RAYTRACING && !(USE_RAY_TRACED_REFRACTION)]_
- L151-154 _function_ `void LockBackgroundVisibilityUpdate(inout float BackgroundVisibility)` _[#if LUMEN_HARDWARE_RAYTRACING]_
- L156-159 _function_ `bool CanUpdateBackgroundVisibility(float BackgroundVisibility)` _[#if LUMEN_HARDWARE_RAYTRACING]_
- L161-167 _function_ `FLumenHitLightingMaterial SanitizeLumenMaterial(FLumenHitLightingMaterial LumenMaterial)` _[#if LUMEN_HARDWARE_RAYTRACING]_
- L169-178 _function_ `float3 GetPathSegmentThroughput(float3 ThroughputPreCoverage, float Coverage)` _[#if LUMEN_HARDWARE_RAYTRACING]_
- L180-629 _function_ `FRayTracedLightingResult TraceRayLighting_Internal( RaytracingAccelerationStructure TLAS, RaytracingAccelerationStructure FarFieldTLAS, FRayDesc Ray, FRayTracedLightingContext Context, FRandomSequence RandSequence, inout FLumenRayHitBookmark Bookmark)` _[#if LUMEN_HARDWARE_RAYTRACING]_
