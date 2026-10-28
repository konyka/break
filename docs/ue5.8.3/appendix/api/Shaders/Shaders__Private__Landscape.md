# Shaders / Shaders/Private/Landscape

- files: 6; lines: 1331
- record kinds: cpp_binding=15, define=25, entry=15, function=18, include=10, macro_call=1, member=15, parameter=29, resource=30, static_const=3, struct=4

### `Shaders/Private/Landscape/LandscapeCommon.ush` (Private)

- lines: 101; parse: all-branches

#### Macros (#define, 10)

- L6 `#define EHEIGHTMAPALPHAFLAGS_NONE 0`
- L7 `#define EHEIGHTMAPALPHAFLAGS_ADDITIVE 0`
- L8 `#define EHEIGHTMAPALPHAFLAGS_MIN (1 << 0)`
- L9 `#define EHEIGHTMAPALPHAFLAGS_MAX (1 << 1)`
- L10 `#define EHEIGHTMAPALPHAFLAGS_ALPHABLEND (EHEIGHTMAPALPHAFLAGS_MIN \| EHEIGHTMAPALPHAFLAGS_MAX)`
- L13 `#define EWEIGHTMAPALPHAFLAGS_NONE 0`
- L14 `#define EWEIGHTMAPALPHAFLAGS_ADDITIVE 0`
- L15 `#define EWEIGHTMAPALPHAFLAGS_MIN (1 << 0)`
- L16 `#define EWEIGHTMAPALPHAFLAGS_MAX (1 << 1)`
- L17 `#define EWEIGHTMAPALPHAFLAGS_ALPHABLEND (EHEIGHTMAPALPHAFLAGS_MIN \| EHEIGHTMAPALPHAFLAGS_MAX)`
- L3 #pragma `once`

#### static const (3)

- L20 _static_const_ `static const float LANDSCAPE_MAX_VALUE = 65535.0f;` — Must match LandscapeDataAccess::MaxValue :
- L22 _static_const_ `static const float LANDSCAPE_MID_VALUE = 32768.0f;` — Must match LandscapeDataAccess::MidValue :
- L24 _static_const_ `static const uint INDEX_NONE = uint(-1);`

#### Functions (9)

- L27-31 _function_ `float2 PackHeight(float InHeight)` — Height is packed from a [0, 2^16-1] value to two bytes, each of which we need to provide as a 0-1 float for writing
- L33-41 _function_ `float UnpackHeight(float2 InPackedHeight)`
- L44-49 _function_ `float2 PackHeightAlpha(float InAlpha, uint InAlphaFlags)` — Height alpha is 14 bits-wide + 2 bits are left for flags. InAlpha is expected in the [0,1] range
- L51-59 _function_ `void UnpackHeightAlpha(float2 InPackedAlpha, out float OutAlpha, out uint OutFlags)`
- L63-67 _function_ `float2 PackWeight(float InWeight)` — It's a bit overkill but we have 2 channels available for weight, so we can use 16 bits for storing it Weight is packed from a [0, 2^16-1] value to two bytes, each of which we need to provide as a 0-1 float for writing
- L69-72 _function_ `float UnpackWeight(float2 InPackedWeight)`
- L75-80 _function_ `float2 PackWeightAlpha(float InAlpha, uint InAlphaFlags)` — Weight Alpha is 14 bits-wide + 2 bits are left for flags. InWeight is expected in the [0,1] range
- L82-90 _function_ `void UnpackWeightAlpha(float2 InPackedAlpha, out float OutAlpha, out uint OutFlags)`
- L96-100 _function_ `float3 ComputeNullableTriangleNormal(float4 InPoint0, float4 InPoint1, float4 InPoint2)` — Compute the normal of the triangle formed by the 3 points (in winding order). .xyz of each point is its world space position Additionally, the .w component of each point indicates its validity (valid: .w == 1, invalid: .w == 0) the resulting normal will be 0 if any of the points is invalid

### `Shaders/Private/Landscape/LandscapeCulling.usf` (Private)

- lines: 92; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../Nanite/NaniteHZBCull.ush`

#### Macros (#define, 1)

- L7 `#define LANDSCAPE_TILE_QUADS 4u` _[#if !defined(LANDSCAPE_TILE_QUADS)]_

#### Entry points (1)

- L44-91 _entry_ `[numthreads(8, 8, 1)] void BuildLandscapeTileDataCS(uint3 ThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `FBuildLandscapeTileDataCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Landscape/Private/LandscapeCulling.cpp:410) — XY for each tile in a section Z for each NumLandscapeSections * NumLandscapeViews

#### Structs / classes (2)

- L10-18 _struct_ **`FLandscapeView`** `struct FLandscapeView`
  - L12 _member_ `float4x4 ViewToClip;`
  - L13 _member_ `float4x4 TranslatedWorldToClip;`
  - L14 _member_ `float3 RelativePreViewTranslation;`
  - L15 _member_ `float _Pad0;`
  - L16 _member_ `float3 ViewTilePosition;`
  - L17 _member_ `float _Pad1;`
- L20-28 _struct_ **`FLandscapeSection`** `struct FLandscapeSection`
  - L22 _member_ `float4x4 LocalToRelativeWorld;`
  - L23 _member_ `float3 TilePosition;`
  - L24 _member_ `float LocalZ;`
  - L25 _member_ `float HalfHeight;`
  - L26 _member_ `float NeighborLODExtent;`
  - L27 _member_ `float _Pad[2];`

#### Global resources (textures / buffers / samplers) (4)

- L30 _resource_ `StructuredBuffer<FLandscapeView> LandscapeViews;`
- L31 _resource_ `StructuredBuffer<FLandscapeSection> LandscapeSections;`
- L39 _resource_ `RWBuffer<uint> IndirectArgsBufferOut;`
- L40 _resource_ `RWByteAddressBuffer TileDataOut;`

#### Global parameters (uniforms) (5)

- L33 _parameter_ `uint NumLandscapeSections;`
- L34 _parameter_ `uint NumLandscapeViews;`
- L35 _parameter_ `uint SubsectionSizeTiles;`
- L36 _parameter_ `uint NumSubsections;`
- L37 _parameter_ `uint NearClip;`

### `Shaders/Private/Landscape/LandscapeEditLayersHeightmaps.usf` (Private)

- lines: 312; parse: all-branches
- includes: L3 `../Common.ush`, L4 `LandscapeCommon.ush`

#### Macros (#define, 3)

- L22 `#define EHEIGHTMAPBLENDMODE_ADDITIVE 0` _[#if MERGE_EDIT_LAYER]_
- L23 `#define EHEIGHTMAPBLENDMODE_LEGACYALPHABLEND 1` _[#if MERGE_EDIT_LAYER]_
- L24 `#define EHEIGHTMAPBLENDMODE_ALPHABLEND 2` _[#if MERGE_EDIT_LAYER]_

#### Entry points (3)

- L99-158 _entry_ `void MergeEditLayerPS(in float4 SVPos : SV_POSITION, out float4 OutPackedHeight : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FLandscapeEditLayersHeightmapsMergeEditLayerPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Landscape/Private/LandscapeEditLayerMergeRenderContext.cpp:158) _[#if MERGE_EDIT_LAYER]_
- L165-238 _entry_ `void GenerateNormalsPS(in float4 SVPos : SV_POSITION, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FLandscapeEditLayersHeightmapsGenerateNormalsPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Landscape/Private/LandscapeEditLayers.cpp:745) _[#if GENERATE_NORMALS]_
- L244-311 _entry_ `void GenerateMipsPS(in float4 SVPos : SV_POSITION, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FLandscapeEditLayersHeightmapsGenerateMipsPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Landscape/Private/LandscapeEditLayers.cpp:785) _[#if GENERATE_MIPS]_

#### Global resources (textures / buffers / samplers) (6)

- L29 _resource_ `Texture2D<float4> InCurrentEditLayerHeightmap;` — The height of the current edit layer to merge _[#if MERGE_EDIT_LAYER]_
- L30 _resource_ `Texture2D<float4> InPreviousEditLayersHeightmap;` — The resulting height from the merge of all prior edit layers _[#if MERGE_EDIT_LAYER]_
- L42 _resource_ `SamplerState InSourceHeightmapSampler;` — TODO [jonathan.bard] : this can be replaced by GlobalPointClampedSampler : _[#if GENERATE_NORMALS]_
- L43 _resource_ `Texture2D<float4> InSourceHeightmap;` _[#if GENERATE_NORMALS]_
- L44 _resource_ `Texture2D<float> InComponentIdTexture;` _[#if GENERATE_NORMALS]_
- L52 _resource_ `Texture2D<float4> InSourceHeightmap;` — Source heightmap (containing the current mip level - 1) _[#if GENERATE_MIPS]_

#### Global parameters (uniforms) (7)

- L26 _parameter_ `uint InEditLayerBlendMode;` — See EHeightmapBlendMode _[#if MERGE_EDIT_LAYER]_
- L27 _parameter_ `float InEditLayerAlpha;` — Alpha value to be used in the blend _[#if MERGE_EDIT_LAYER]_
- L36 _parameter_ `uint4 InTextureSize;` — .xy == Effective size in pixels of InSourceHeightmap, .zw == actual texture size in pixels of InSourceHeightmap _[#if GENERATE_NORMALS]_
- L37 _parameter_ `float3 InLandscapeGridScale;` — x == LS Actor DrawScale.X, y == LS Actor DrawScale.y, z == LS Actor DrawScale.z / 128.0f (ZSCALE) _[#if GENERATE_NORMALS]_
- L38 _parameter_ `uint InComponentSizeQuads;` — Number of quads per component _[#if GENERATE_NORMALS]_
- L39 _parameter_ `uint2 InNumComponents;` — Number of components in the effective region of the texture (.xy) _[#if GENERATE_NORMALS]_
- L50 _parameter_ `uint2 InCurrentMipSubsectionSize;` — Size of the the subsection at the currently generated mip level _[#if GENERATE_MIPS]_

#### Functions (5)

- L60-65 _function_ `float ExtractAlpha(float2 InPackedAlpha)` _[#if MERGE_EDIT_LAYER]_
- L69-72 _function_ `float ScaleHeight(float InHeight)` _[#if GENERATE_NORMALS]_
- L74-77 _function_ `float ExtractAndScaleHeight(float2 InPackedHeight)` _[#if GENERATE_NORMALS]_
- L79-82 _function_ `float UnscaleHeight(float InScaledHeight)` _[#if GENERATE_NORMALS]_
- L84-91 _function_ `float4 ExtractSampleInfo(int2 InTextureCoordinates, float2 InPackedHeight)` _[#if GENERATE_NORMALS]_

### `Shaders/Private/Landscape/LandscapeEditLayersUtils.usf` (Private)

- lines: 210; parse: all-branches
- includes: L3 `../Common.ush`, L4 `LandscapeCommon.ush`

#### Macros (#define, 3)

- L35 `#define FOREACH_SOURCETEXTURE(op) op(0) op(1) op(2) op(3) op(4) op(5) op(6) op(7) op(8) op(9) op(10) op(11) op(12) op(13) op(14) op(15) op(16) op(17) op(18) op(19) op(20) op(21) op(22) op(23) op(24) op(25) op(26) op(27) op(28) op(29)  ...` (63 lines) _[#if COPY_QUADS_MULTISOURCE]_
- L103 `#define DECLARE_SOURCE_TEXTURE(n) Texture2D<float4> InSourceTexture_##n;` _[#if COPY_QUADS_MULTISOURCE]_
- L150 `#define IMPLEMENT_SAMPLE_SWITCH_CASE(n) case n: return InSourceTexture_##n.SampleLevel(GlobalPointClampedSampler, SourceUV, 0);` _[#if COPY_QUADS_MULTISOURCE]_
- L105 #undef `DECLARE_SOURCE_TEXTURE`; L152 #undef `IMPLEMENT_SAMPLE_SWITCH_CASE`

#### Entry points (4)

- L117-121 _entry_ `void RenderComponentIdPS(float4 SvPosition : SV_POSITION, float2 SourceUV : TEXCOORD0, float2 UnusedQuadUV : TEXCOORD1, float InRectIndex : RECT_INDEX, out float OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FRenderComponentIdPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Landscape/Private/LandscapeEditLayerMergeRenderContext.cpp:68) _[#if RENDER_COMPONENTID]_
- L130-133 _entry_ `void CopyQuadsPS(float4 SvPosition : SV_POSITION, float2 QuadUV : TEXCOORD0, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FCopyQuadsPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Landscape/Private/LandscapeEditLayerMergeRenderContext.cpp:104) _[#if COPY_QUADS]_
- L158-184 _entry_ `void CopyQuadsMultiSourcePS(float4 SvPosition : SV_POSITION, float2 SourceUV : TEXCOORD0, float2 UnusedQuadUV : TEXCOORD1, float InRectIndex : RECT_INDEX, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FCopyQuadsMultiSourcePSDefault` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Landscape/Private/LandscapeEditLayers.cpp:1033) _[#if COPY_QUADS_MULTISOURCE]_
- L192-208 _entry_ `void ResolveLayerData(in float4 SVPos : SV_POSITION, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FLandscapeEditLayersResolveLayerDataPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Landscape/Private/LandscapeBlueprintBrushBase.cpp:91) _[#if RESOLVE_LAYER_DATA]_

#### Global resources (textures / buffers / samplers) (5)

- L22 _resource_ `Buffer<uint> InQuadComponentIds;` — RenderComponentIdPS inputs/outputs : _[#if RENDER_COMPONENTID]_
- L28 _resource_ `Texture2D<float4> InSourceTexture;` _[#if COPY_QUADS]_
- L99 _resource_ `Buffer<uint4> InQuadInfos;` — .x = source texture index, .y = source texture channel (for weightmaps), .z = component id of the component this quad corresponds to, .w = unused _[#if COPY_QUADS_MULTISOURCE]_
- L100 _resource_ `Texture2D<float> InComponentIdTexture;` — texture containing the linear index of the components in this batch. This allows to resolve conflicts in case multiple quads render to the same pixel _[#if COPY_QUADS_MULTISOURCE]_
- L109 _resource_ `Texture2D<float4> InSourceTexture;` _[#if RESOLVE_LAYER_DATA]_

#### Functions (1)

- L142-156 _function_ `float4 GetSourceTextureColor(uint SourceTextureIndex, float2 SourceUV)` _[#if COPY_QUADS_MULTISOURCE]_

#### Top-level macro invocations (1)

- L104 _macro_call_ `FOREACH_SOURCETEXTURE(DECLARE_SOURCE_TEXTURE)` _[#if COPY_QUADS_MULTISOURCE]_

### `Shaders/Private/Landscape/LandscapeEditLayersWeightmaps.usf` (Private)

- lines: 489; parse: all-branches
- includes: L3 `../Common.ush`, L4 `LandscapeCommon.ush`

#### Macros (#define, 8)

- L20 `#define EWEIGHTMAPBLENDMODE_ADDITIVE 0`
- L21 `#define EWEIGHTMAPBLENDMODE_SUBTRACTIVE 1`
- L22 `#define EWEIGHTMAPBLENDMODE_PASSTHROUGH 2`
- L23 `#define EWEIGHTMAPBLENDMODE_ALPHABLEND 3`
- L26 `#define EWEIGHTMAPTARGETLAYERFLAGS_ISVISIBILITYLAYER (1 << 0)`
- L31 `#define EWEIGHTMAPTARGETLAYERFLAGS_ISWEIGHTBLENDED (1 << 1)`
- L32 `#define EWEIGHTMAPTARGETLAYERFLAGS_SKIP (1 << 2)`
- L40 `#define EWEIGHTMAPTARGETLAYERFLAGS_ISPREMULTIPLIEDALPHAWEIGHTBLENDED (1 << 3)`

#### Entry points (4)

- L140-351 _entry_ `void MergeEditLayerPS(in float4 SVPos : SV_POSITION, out float4 OutPackedWeight : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FLandscapeEditLayersWeightmapsMergeEditLayerPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Landscape/Private/LandscapeEditLayerMergeRenderContext.cpp:209) _[#if MERGE_EDIT_LAYER]_
- L355-394 _entry_ `void PerformFinalWeightBlendingPS(in float4 SVPos : SV_POSITION, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FLandscapeEditLayersWeightmapsPerformFinalWeightBlendingPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Landscape/Private/LandscapeEditLayers.cpp:832) _[#if PERFORM_FINAL_WEIGHT_BLENDING]_
- L400-420 _entry_ `void PackWeightmapPS(in float4 SVPos : SV_POSITION, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FLandscapeEditLayersWeightmapsPackWeightmapPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Landscape/Private/LandscapeEditLayers.cpp:876) _[#if PACK_WEIGHTMAP]_
- L426-488 _entry_ `void GenerateMipsPS(in float4 SVPos : SV_POSITION, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FLandscapeEditLayersWeightmapsGenerateMipsPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Landscape/Private/LandscapeEditLayers.cpp:916) _[#if GENERATE_MIPS]_

#### Structs / classes (2)

- L46-50 _struct_ **`FMergeEditLayerTargetLayerInfo`** `struct FMergeEditLayerTargetLayerInfo` — Per-target layer information : _[#if MERGE_EDIT_LAYER]_
  - L48 _member_ `uint Flags;` — See EWeightmapTargetLayerFlags _[#if MERGE_EDIT_LAYER]_
  - L49 _member_ `int BlendGroupIndex;` — Defines the target layer blend group that this target layer belongs to in this blend operation. -1 if not applicable _[#if MERGE_EDIT_LAYER]_
- L68-71 _struct_ **`FFinalWeightBlendingTargetLayerInfo`** `struct FFinalWeightBlendingTargetLayerInfo` — Per-target layer information : _[#if PERFORM_FINAL_WEIGHT_BLENDING]_
  - L70 _member_ `uint Flags;` — See EWeightmapTargetLayerFlags _[#if PERFORM_FINAL_WEIGHT_BLENDING]_

#### Global resources (textures / buffers / samplers) (8)

- L58 _resource_ `StructuredBuffer<FMergeEditLayerTargetLayerInfo> InMergeEditLayerTargetLayerInfos;` — Array that contains per-target layer information (e.g. target layer's flags) _[#if MERGE_EDIT_LAYER]_
- L59 _resource_ `Texture2DArray<float4> InCurrentEditLayerWeightmaps;` — The target layers of the current edit layer to merge (1 slice per weightmap in the target layer group) _[#if MERGE_EDIT_LAYER]_
- L60 _resource_ `Texture2DArray<float4> InPreviousEditLayersWeightmaps;` — The result from the merge of all prior edit layers (1 slice per weightmap in the target layer group) _[#if MERGE_EDIT_LAYER]_
- L76 _resource_ `StructuredBuffer<FFinalWeightBlendingTargetLayerInfo> InFinalWeightBlendingTargetLayerInfos;` — Array that contains per-target layer information (e.g. target layer's flags) _[#if PERFORM_FINAL_WEIGHT_BLENDING]_
- L77 _resource_ `Texture2DArray<float4> InCurrentEditLayerWeightmaps;` — The texture to horizontally blend (1 slice per weightmap in the target layer group) _[#if PERFORM_FINAL_WEIGHT_BLENDING]_
- L88 _resource_ `Texture2DArray<float4> InSourceWeightmaps;` — Source, single-channel (we don't care about the alpha flags at this point), texture to pack _[#if PACK_WEIGHTMAP]_
- L89 _resource_ `Texture2D<float4> InWeightmapBeingPacked;` — The weightmap being packed, in case the packing operation is additive, i.e. it occurs across multiple draws (contains the channels that have previously been packed) _[#if PACK_WEIGHTMAP]_
- L97 _resource_ `Texture2D<float4> InSourceWeightmap;` — Source weightmap (containing the current mip level - 1) _[#if GENERATE_MIPS]_

#### Global parameters (uniforms) (11)

- L52 _parameter_ `uint InTargetLayerIndex;` — Index of the target layer being processed _[#if MERGE_EDIT_LAYER]_
- L53 _parameter_ `uint InNumTargetLayers;` — Number of target layers (i.e. == InMergeEditLayerTargetLayerInfos.Num()) _[#if MERGE_EDIT_LAYER]_
- L54 _parameter_ `uint InEditLayerTargetLayerBlendMode;` — See EWeightmapBlendMode. Target layer's blend mode, which is per-edit layer and per-target layer and can therefore differ from one edit layer to another _[#if MERGE_EDIT_LAYER]_
- L55 _parameter_ `float InEditLayerAlpha;` — Global alpha value of the edit layer currently being merged _[#if MERGE_EDIT_LAYER]_
- L73 _parameter_ `uint InTargetLayerIndex;` — Index of the target layer being processed _[#if PERFORM_FINAL_WEIGHT_BLENDING]_
- L74 _parameter_ `uint InNumTargetLayers;` — Number of target layers (i.e. == InFinalWeightBlendingTargetLayerInfos.Num()) _[#if PERFORM_FINAL_WEIGHT_BLENDING]_
- L83 _parameter_ `int4 InSourceSliceIndices;` — For each channel of the output texture (rgba), this indicates the slice index in InSourceWeightmaps where to read from _[#if PACK_WEIGHTMAP]_
- L84 _parameter_ `uint4 InSourcePixelOffsets[4];` — For each channel, offset to add to the pixel's coordinates to load the proper sample in InSourceWeightmaps (.xy, .zw is unused, only there for alignment purposes) _[#if PACK_WEIGHTMAP]_
- L85 _parameter_ `uint2 InSubsectionPixelOffset;` — Offset of the subsection currently being rendered _[#if PACK_WEIGHTMAP]_
- L86 _parameter_ `uint InIsAdditive;` — = 1 if some channels of this texture have been packed in a previous draw, 0 otherwise _[#if PACK_WEIGHTMAP]_
- L95 _parameter_ `uint2 InCurrentMipSubsectionSize;` — Size of the the subsection at the currently generated mip level _[#if GENERATE_MIPS]_

#### Functions (3)

- L105-112 _function_ `bool IsPremultipliedAlphaWeightBlendedTargetLayer(FMergeEditLayerTargetLayerInfo InTargetLayerInfo)` _[#if MERGE_EDIT_LAYER]_
- L116-123 _function_ `bool IsWeightBlendedTargetLayer(FFinalWeightBlendingTargetLayerInfo InTargetLayerInfo)` _[#if PERFORM_FINAL_WEIGHT_BLENDING]_
- L131-138 _function_ `float PerformPremultipliedAlphaBlending(float InPreviousLayersWeight, float InCurrentLayerWeight, float InPremultipliedAlphaBlendGroupWeightSum)` _[#if MERGE_EDIT_LAYER]_

### `Shaders/Private/Landscape/LandscapeMergeTexturesPS.usf` (Private)

- lines: 127; parse: all-branches
- includes: L3 `../Common.ush`, L4 `LandscapeCommon.ush`

#### Entry points (3)

- L51-66 _entry_ `void MergeTexture(in float4 SVPos : SV_POSITION, out float OutValue : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FLandscapeMergeTexturesPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Landscape/Private/Landscape.cpp:3547) _[#if MERGE_TEXTURE]_
- L75-100 _entry_ `void ResampleMergedTexture(in float4 SVPos : SV_POSITION, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FLandscapeResampleMergedTexturePS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Landscape/Private/Landscape.cpp:3614) _[#if RESAMPLE_MERGED_TEXTURE]_
- L109-125 _entry_ `void PackRGBAChannels(in float4 SVPos : SV_POSITION, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FLandscapePackRGBAChannelsPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Landscape/Private/Landscape.cpp:3660) _[#if PACK_RGBA_CHANNELS]_

#### Global resources (textures / buffers / samplers) (7)

- L25 _resource_ `Texture2D<float4> InSourceTexture;` — Source texture (packed height in the .rg channels for heightmap, weight in one the 4 .rgba channels for the weightmap) _[#if MERGE_TEXTURE]_
- L32 _resource_ `Texture2D<float> InMergedTexture;` — Source texture (unpacked floating point height for heightmap) _[#if RESAMPLE_MERGED_TEXTURE]_
- L33 _resource_ `SamplerState InMergedTextureSampler;` _[#if RESAMPLE_MERGED_TEXTURE]_
- L39 _resource_ `Texture2D<float> InSourceTextures_0;` — Source, single-channel, texture to pack _[#if PACK_RGBA_CHANNELS]_
- L40 _resource_ `Texture2D<float> InSourceTextures_1;` — Source, single-channel, texture to pack _[#if PACK_RGBA_CHANNELS]_
- L41 _resource_ `Texture2D<float> InSourceTextures_2;` — Source, single-channel, texture to pack _[#if PACK_RGBA_CHANNELS]_
- L42 _resource_ `Texture2D<float> InSourceTextures_3;` — Source, single-channel, texture to pack _[#if PACK_RGBA_CHANNELS]_

#### Global parameters (uniforms) (6)

- L22 _parameter_ `uint4 InAtlasSubregion;` — Subregion of the atlas texture that is being rendered to _[#if MERGE_TEXTURE]_
- L23 _parameter_ `uint4 InSourceTextureSubregion;` — Subregion of the input texture that we copy from _[#if MERGE_TEXTURE]_
- L24 _parameter_ `int InSourceTextureChannel;` — Channel of the input texture that we copy from (for weightmaps only) _[#if MERGE_TEXTURE]_
- L31 _parameter_ `float4x4 InOutputUVToMergedTextureUV;` — Transform to apply to the texture coordinates in order to resample the atlas in the requested render area _[#if RESAMPLE_MERGED_TEXTURE]_
- L34 _parameter_ `uint2 InRenderAreaSize;` — Size of the output render target _[#if RESAMPLE_MERGED_TEXTURE]_
- L38 _parameter_ `int InNumChannels;` — Number of channels to pack _[#if PACK_RGBA_CHANNELS]_
