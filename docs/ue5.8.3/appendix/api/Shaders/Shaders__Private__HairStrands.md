# Shaders / Shaders/Private/HairStrands

- files: 79; lines: 28376
- record kinds: cpp_binding=143, define=370, entry=143, function=666, groupshared=145, include=388, macro_call=25, member=437, parameter=573, prototype=10, resource=566, static_const=3, stray_block=4, struct=85

### `Shaders/Private/HairStrands/HairBsdfSample.ush` (Private)

- lines: 213; parse: all-branches; parse notes: 1
- includes: L7 `../Common.ush`, L8 `../ShadingCommon.ush`, L9 `../ShadingModels.ush`, L10 `../HairBsdf.ush`

#### Macros (#define, 1)

- L5 `#define HAIR_CUSTOM_BSDF 1`
- L3 #pragma `once`

#### Functions (6)

- L13-26 _function_ `float2 SampleMp(float2 u, float Roughness, float cosThetaO, float sinThetaO)`
- L28-31 _function_ `float Phi(int p, float gammaO, float gammaT)`
- L33-48 _function_ `float3 SampleNp(float h, float cosThetaO, float sinThetaO)`
- L50-56 _function_ `float3 asinFast3(float3 a)`
- L58-180 _function_ `void SampleHair( float Roughness, float3 BaseColor, float Specular, float Backlit, float3 V, float3 T, float2 u0, float2 u1, uint HairComponents, inout float3 OutDirection, inout float3 OutWeight)`
- L186-192 _function_ `float2 Rand1SPPDenoiserInput(uint2 PixelPos, uint FrameIndexMod8)` _[#if 0]_

#### Stray brace blocks (function body split by #if) (1)

- L198-211 _stray_block_ `{ ... }` _[#if 0]_

<details><summary>parse notes</summary>

- L198: brace block without header (code split across #if branches)

</details>

### `Shaders/Private/HairStrands/HairCardsAttributeCommon.ush` (Private)

- lines: 223; parse: all-branches
- includes: L5 `/Engine/Shared/HairStrandsDefinitions.h`, L81 `/Engine/Private/HairStrands/HairStrandsVertexFactoryCommon.ush` [HAIR_CARD_MESH_FACTORY]

#### Macros (#define, 19)

- L10 `#define EHairCardsVFlags_Texture0 0x1`
- L11 `#define EHairCardsVFlags_Texture1 0x2`
- L12 `#define EHairCardsVFlags_Texture2 0x4`
- L13 `#define EHairCardsVFlags_Texture3 0x8`
- L14 `#define EHairCardsVFlags_Texture4 0x10`
- L15 `#define EHairCardsVFlags_Texture5 0x20`
- L16 `#define EHairCardsVFlags_InvertedUV 0x40`
- L17 `#define EHairCardsVFlags_VertexColor 0x80`
- L20 `#define EHairCardsVFAttribute_Depth 0`
- L21 `#define EHairCardsVFAttribute_Seed 1`
- L22 `#define EHairCardsVFAttribute_CoordU 2`
- L23 `#define EHairCardsVFAttribute_GroupIndex 3`
- L24 `#define EHairCardsVFAttribute_Roughness 4`
- L25 `#define EHairCardsVFAttribute_RootUV 5`
- L26 `#define EHairCardsVFAttribute_Color 6`
- L27 `#define EHairCardsVFAttribute_Tangent 7`
- L28 `#define EHairCardsVFAttribute_Coverage 8`
- L29 `#define EHairCardsVFAttribute_Auxilary 9`
- L31 `#define LAYOUT_VALUES(LayoutIdx, L0, L1, L2, L3) (LayoutIdx == 0 ? L0 : (LayoutIdx == 1 ? L1 : (LayoutIdx == 2 ? L2 : L3)))` (4 lines)
- L3 #pragma `once`

#### Functions (36)

- L36-53 _function_ `uint GetHairCardTextureIndex(uint InLayoutIndex, uint InAttribute)`
- L55-58 _function_ `bool IsHairCardTextureIndexValid(uint InLayoutIndex, uint InAttribute)`
- L60-77 _function_ `uint GetHairCardChannelIndex(uint InLayoutIndex, uint InAttribute)`
- L90 _function_ `float2 GetAtlasUV(float2 In)` _[#if HAIR_CARD_MESH_FACTORY]_
- L91 _function_ `bool HasHairCardsVertexColor()` _[#if HAIR_CARD_MESH_FACTORY]_
- L93-98 _function_ `bool HasTextureBound(uint In)` _[#if HAIR_CARD_MESH_FACTORY]_
- L101-111 _function_ `float4 FetchAttributeTexture(uint InTextureIndex, float2 InAtlasUV, float InBias)` — Generic attribute texture fetches _[#if HAIR_CARD_MESH_FACTORY]_
- L113-123 _function_ `float4 FetchAttributeTexture(uint InTextureIndex, float2 InAtlasUV)` _[#if HAIR_CARD_MESH_FACTORY]_
- L126 _function_ `float FetchAttribute1(uint In, float2 InAtlasUV, float InBias)` — Generic attribute fetch functions _[#if HAIR_CARD_MESH_FACTORY]_
- L127 _function_ `float FetchAttribute1(uint In, float2 InAtlasUV)` _[#if HAIR_CARD_MESH_FACTORY]_
- L128 _function_ `float2 FetchAttribute2(uint In, float2 InAtlasUV)` — float2 alignemnt is forced onto .xy or .zw _[#if HAIR_CARD_MESH_FACTORY]_
- L129 _function_ `float3 FetchAttribute3(uint In, float2 InAtlasUV)` — float3 alignemnt forced onto .xyz _[#if HAIR_CARD_MESH_FACTORY]_
- L130 _function_ `float4 FetchAttribute4(uint In, float2 InAtlasUV)` _[#if HAIR_CARD_MESH_FACTORY]_
- L133 _function_ `float GetDepthOffset (float2 InAtlasUV)` — Special attribute fetch functions _[#if HAIR_CARD_MESH_FACTORY]_
- L134 _function_ `float GetSeed (float2 InAtlasUV)` _[#if HAIR_CARD_MESH_FACTORY]_
- L135 _function_ `float GetCoordU (float2 InAtlasUV)` _[#if HAIR_CARD_MESH_FACTORY]_
- L136 _function_ `float GetGroupIndex (float2 InAtlasUV, float InDefault)` _[#if HAIR_CARD_MESH_FACTORY]_
- L137 _function_ `float GetRoughness (float2 InAtlasUV, float InDefault)` _[#if HAIR_CARD_MESH_FACTORY]_
- L138 _function_ `float GetCoverage (float2 InAtlasUV, float InDefault)` _[#if HAIR_CARD_MESH_FACTORY]_
- L139 _function_ `float2 GetRootUV (float2 InAtlasUV, float2 InDefault)` _[#if HAIR_CARD_MESH_FACTORY]_
- L140 _function_ `float3 GetColor (float2 InAtlasUV, float3 InDefault)` — Cheap sRGB -> Linear encoding _[#if HAIR_CARD_MESH_FACTORY]_
- L141 _function_ `float3 GetTangent (float2 InAtlasUV, float3 InDefault)` _[#if HAIR_CARD_MESH_FACTORY]_
- L142 _function_ `float4 GetAuxilary (float2 InAtlasUV, float4 InDefault)` _[#if HAIR_CARD_MESH_FACTORY]_
- L147-152 _function_ `float GetHairCardsDepth(float2 InAtlasUV, float InDeviceZ)` _[#if HAIR_CARD_MESH_FACTORY]_
- L154-159 _function_ `float3 GetHairCardsTangent(float2 InAtlasUV, half3x3 TangentToWorld, bool bUseTangentSpace)` _[#if HAIR_CARD_MESH_FACTORY]_
- L161-164 _function_ `float GetHairCardsCoverage(float2 InAtlasUV)` _[#if HAIR_CARD_MESH_FACTORY]_
- L166-169 _function_ `float4 GetHairCardsAuxilaryData(float2 InAtlasUV)` _[#if HAIR_CARD_MESH_FACTORY]_
- L171-174 _function_ `float2 GetHairCardsUV(float2 InAtlasUV)` _[#if HAIR_CARD_MESH_FACTORY]_
- L176-179 _function_ `float2 GetHairCardsDimensions(float2 InAtlasUV, float HairPrimitiveLength)` _[#if HAIR_CARD_MESH_FACTORY]_
- L181-186 _function_ `float2 GetHairCardsRootUV(float2 InAtlasUV, float2 InRootUV)` _[#if HAIR_CARD_MESH_FACTORY]_
- L188-191 _function_ `float GetHairCardsSeed(float2 InAtlasUV)` _[#if HAIR_CARD_MESH_FACTORY]_
- L193-196 _function_ `uint3 GetHairCardsClumpID(float2 InAtlasUV)` _[#if HAIR_CARD_MESH_FACTORY]_
- L198-202 _function_ `float3 GetHairCardsColor(float2 InAtlasUV, float3 InColor)` _[#if HAIR_CARD_MESH_FACTORY]_
- L204-208 _function_ `float GetHairCardsRoughness(float2 InAtlasUV, float InCardRoughness)` _[#if HAIR_CARD_MESH_FACTORY]_
- L210-213 _function_ `float GetHairCardsAO(float2 InAtlasUV, float InAO)` _[#if HAIR_CARD_MESH_FACTORY]_
- L215-220 _function_ `float GetHairCardsGroupIndex(float2 InAtlasUV, float InCardGroupIndex)` _[#if HAIR_CARD_MESH_FACTORY]_

### `Shaders/Private/HairStrands/HairCardsDeformation.usf` (Private)

- lines: 203; parse: all-branches
- includes: L3 `../Common.ush`, L4 `HairStrandsPack.ush`, L5 `HairStrandsVertexFactoryCommon.ush`, L6 `HairStrandsBindingCommon.ush`, L11 `../ShaderPrint.ush` [DEBUG_ENABLE]

#### Macros (#define, 1)

- L8 `#define DEBUG_ENABLE 0`

#### Entry points (1)

- L97-202 _entry_ `[numthreads(GROUP_SIZE, 1, 1)] void MainCS(uint DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FHairCardsDeformationCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsInterpolation.cpp:1069) _[#if SHADER_DEFORM_CARDS]_

#### Global resources (textures / buffers / samplers) (13)

- L22 _resource_ `StructuredBuffer<float4> GuideDeformedPositionOffsetBuffer;` _[#if SHADER_DEFORM_CARDS]_
- L24 _resource_ `ByteAddressBuffer GuideRestPositionBuffer;` _[#if SHADER_DEFORM_CARDS]_
- L25 _resource_ `ByteAddressBuffer GuideDeformedPositionBuffer;` _[#if SHADER_DEFORM_CARDS]_
- L26 _resource_ `Buffer<float4> CardsRestPositionBuffer;` _[#if SHADER_DEFORM_CARDS]_
- L27 _resource_ `ByteAddressBuffer CardsInterpolationBuffer;` _[#if SHADER_DEFORM_CARDS]_
- L29 _resource_ `RWBuffer<float4> CardsDeformedPositionBuffer;` _[#if SHADER_DEFORM_CARDS]_
- L31 _resource_ `Buffer<float4> CardsRestTangentBuffer;` _[#if SHADER_DEFORM_CARDS]_
- L32 _resource_ `RWBuffer<float4> CardsDeformedTangentBuffer;` _[#if SHADER_DEFORM_CARDS]_
- L35 _resource_ `Buffer<float4> TriangleRestPositionBuffer;` — Guides == Strands going through the middle of the card geometry _[#if SHADER_DEFORM_CARDS]_
- L37 _resource_ `Buffer<float4> TriangleDeformedPositionBuffer;` _[#if SHADER_DEFORM_CARDS]_
- L39 _resource_ `Buffer<uint> GuideRootBarycentricBuffer;` _[#if SHADER_DEFORM_CARDS]_
- L40 _resource_ `ByteAddressBuffer GuideVertexToRootIndexBuffer;` _[#if SHADER_DEFORM_CARDS]_
- L41 _resource_ `Buffer<uint> GuideRootToUniqueTriangleIndexBuffer;` _[#if SHADER_DEFORM_CARDS]_

#### Global parameters (uniforms) (6)

- L15 _parameter_ `float4x4 LocalToWorld;` _[#if SHADER_DEFORM_CARDS]_
- L17 _parameter_ `uint CardLODIndex;` _[#if SHADER_DEFORM_CARDS]_
- L18 _parameter_ `uint InstanceRegisteredIndex;` _[#if SHADER_DEFORM_CARDS]_
- L19 _parameter_ `uint CardsVertexCount;` _[#if SHADER_DEFORM_CARDS]_
- L20 _parameter_ `uint GuideVertexCount;` _[#if SHADER_DEFORM_CARDS]_
- L21 _parameter_ `float3 GuideRestPositionOffset;` _[#if SHADER_DEFORM_CARDS]_

#### Functions (4)

- L44-58 _function_ `float3 ComputeDynamicGeometryOffset( uint GuideIndex, float GuideVertexWeight, FHairMeshBasis RestBasis, FHairMeshBasis DeformedBasis, float3 GuideDeformedPositionOffset)` _[#if SHADER_DEFORM_CARDS && PERMUTATION_DYNAMIC_GEOMETRY == 1]_
- L61-71 _function_ `void TransformTangent( uint InVertexId, uint InOffset, FHairMeshBasis InRestBasis, FHairMeshBasis InDeformedBasis)` _[#if SHADER_DEFORM_CARDS]_
- L73-76 _function_ `void CopyTangent(uint InVertexId, uint InOffset)` _[#if SHADER_DEFORM_CARDS]_
- L78-95 _function_ `const FHairMeshBasis ConstructBasis(float3 GuideP0, float3 GuideP1, float3 P)` _[#if SHADER_DEFORM_CARDS]_

### `Shaders/Private/HairStrands/HairCardsGeneration.usf` (Private)

- lines: 316; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../ShaderPrint.ush`, L5 `../MonteCarlo.ush`, L7 `HairStrandsVisibilityCommon.ush`, L8 `HairCardsTextureCommon.ush`, L48 `HairStrandsVertexFactoryCommon.ush` [SHADER_VERTEX_RECT], L159 `HairStrandsVertexFactoryCommon.ush` [SHADER_PIXEL_RECT]

#### Macros (#define, 1)

- L161 `#define DEBUG_ENABLE 0` _[#if SHADER_PIXEL_RECT]_

#### Global resources (textures / buffers / samplers) (2)

- L37 _resource_ `Buffer<float4> Curve_PositionBuffer;` _[#if SHADER_VERTEX_RECT \|\| SHADER_PIXEL_RECT]_
- L38 _resource_ `Buffer<float4> Curve_AttributeBuffer;` _[#if SHADER_VERTEX_RECT \|\| SHADER_PIXEL_RECT]_

#### Global parameters (uniforms) (15)

- L14 _parameter_ `uint SampleCount;` _[#if SHADER_VERTEX_RECT \|\| SHADER_PIXEL_RECT]_
- L16 _parameter_ `int2 Atlas_Resolution;` _[#if SHADER_VERTEX_RECT \|\| SHADER_PIXEL_RECT]_
- L17 _parameter_ `int2 Atlas_RectOffset;` _[#if SHADER_VERTEX_RECT \|\| SHADER_PIXEL_RECT]_
- L18 _parameter_ `int2 Atlas_RectResolution;` _[#if SHADER_VERTEX_RECT \|\| SHADER_PIXEL_RECT]_
- L20 _parameter_ `int2 Tile_Coord;` _[#if SHADER_VERTEX_RECT \|\| SHADER_PIXEL_RECT]_
- L21 _parameter_ `int2 Tile_Count;` _[#if SHADER_VERTEX_RECT \|\| SHADER_PIXEL_RECT]_
- L22 _parameter_ `int2 Tile_Resolution;` _[#if SHADER_VERTEX_RECT \|\| SHADER_PIXEL_RECT]_
- L24 _parameter_ `float3 Raster_MinBound;` _[#if SHADER_VERTEX_RECT \|\| SHADER_PIXEL_RECT]_
- L25 _parameter_ `float3 Raster_MaxBound;` _[#if SHADER_VERTEX_RECT \|\| SHADER_PIXEL_RECT]_
- L27 _parameter_ `float3 Raster_AxisX;` — Not normalized, contains AABB (full) length _[#if SHADER_VERTEX_RECT \|\| SHADER_PIXEL_RECT]_
- L28 _parameter_ `float3 Raster_AxisY;` — Not normalized, contains AABB (full) length _[#if SHADER_VERTEX_RECT \|\| SHADER_PIXEL_RECT]_
- L29 _parameter_ `float3 Raster_AxisZ;` — Not normalized, contains AABB (full) length _[#if SHADER_VERTEX_RECT \|\| SHADER_PIXEL_RECT]_
- L33 _parameter_ `uint Curve_VertexOffset;` — Offset to the first strands vertex Count of all vertex belonging to this cluster _[#if SHADER_VERTEX_RECT \|\| SHADER_PIXEL_RECT]_
- L34 _parameter_ `uint Curve_VertexCount;` _[#if SHADER_VERTEX_RECT \|\| SHADER_PIXEL_RECT]_
- L35 _parameter_ `uint Curve_TotalVertexCount;` _[#if SHADER_VERTEX_RECT \|\| SHADER_PIXEL_RECT]_

#### Functions (3)

- L40-43 _function_ `float GetPixelWorldRadius()` _[#if SHADER_VERTEX_RECT \|\| SHADER_PIXEL_RECT]_
- L50-150 _function_ `void MainVS( uint VertexId : SV_VertexID, out float4 OutPosition : SV_Position, nointerpolation out uint OutVertexId : SEG_ID)` — sv-semantics _[#if SHADER_VERTEX_RECT]_
- L166-313 _function_ `void MainPS( in float4 SvPosition : SV_Position, nointerpolation in uint VertexId : SEG_ID, out float4 OutDepth : SV_Target0, out float4 OutTangent : SV_Target1, out float4 OutAttribute : SV_Target2 out float4 OutCoverage : SV_Target0 )` — sv-semantics — Two output type: 0 = Depth/Tangent/Attributes 1 = Coverage _[#if SHADER_PIXEL_RECT]_

### `Shaders/Private/HairStrands/HairCardsTextureCommon.ush` (Private)

- lines: 54; parse: all-branches
- L3 #pragma `once`

#### Functions (2)

- L8-33 _function_ `float2 LineLineIntersect(float3 p1, float3 p2, float3 p3, float3 p4)`
- L35-54 _function_ `float Intersection(float3 InP0, float3 InP1, float3 RayP0, float3 RayP1, float Radius, inout float OutU)`

### `Shaders/Private/HairStrands/HairCardsVertexFactory.ush` (Private)

- lines: 592; parse: all-branches
- includes: L6 `../VertexFactoryCommon.ush`, L7 `../LocalVertexFactoryCommon.ush`, L8 `HairStrandsVisibilityCommon.ush`, L9 `HairStrandsVertexFactoryCommon.ush`, L10 `HairCardsAttributeCommon.ush`, L12 `/Engine/Generated/UniformBuffers/PrecomputedLightingBuffer.ush`, L15 `../RayTracing/RayTracingCommon.ush` [RAYHITGROUPSHADER], L16 `../RayTracing/RayTracingHitGroupCommon.ush` [RAYHITGROUPSHADER], L591 `/Engine/Private/VertexFactoryDefaultInterface.ush`

#### Macros (#define, 1)

- L19 `#define USE_HAIR_COMPLEX_TRANSMITTANCE 1`

#### Structs / classes (4)

- L35-75 _struct_ **`FVertexFactoryInput`** `struct FVertexFactoryInput`
  - L38 _member_ `uint VertexId : SV_VertexID;` _[#if MANUAL_VERTEX_FETCH]_
  - L40 _member_ `float4 Position : ATTRIBUTE0;` _[#if !(MANUAL_VERTEX_FETCH)]_
  - L41 _member_ `float4 PrevPosition : ATTRIBUTE1;` _[#if !(MANUAL_VERTEX_FETCH)]_
  - L45 _member_ `float3 TangentX : ATTRIBUTE2;` _[#if !(MANUAL_VERTEX_FETCH) && METAL_ES3_1_PROFILE]_
  - L46 _member_ `float4 TangentZ : ATTRIBUTE3;` _[#if !(MANUAL_VERTEX_FETCH) && METAL_ES3_1_PROFILE]_
  - L48 _member_ `half3 TangentX : ATTRIBUTE2;` _[#if !(MANUAL_VERTEX_FETCH) && !(METAL_ES3_1_PROFILE)]_
  - L49 _member_ `half4 TangentZ : ATTRIBUTE3;` _[#if !(MANUAL_VERTEX_FETCH) && !(METAL_ES3_1_PROFILE)]_
  - L51 _member_ `float4 Materials : ATTRIBUTE4;` _[#if !(MANUAL_VERTEX_FETCH)]_
  - L52 _member_ `float4 VertexColors : ATTRIBUTE5;` _[#if !(MANUAL_VERTEX_FETCH)]_
  - L53 _member_ `float4 UVs : ATTRIBUTE6;` — RootUV/AtlasUV _[#if !(MANUAL_VERTEX_FETCH)]_
  - L58 _member_ `float4 TexCoords0 : ATTRIBUTE7;` _[#if !(MANUAL_VERTEX_FETCH) && NUM_MATERIAL_TEXCOORDS_VERTEX && NUM_MATERIAL_TEXCOORDS_VERTEX >= 1]_
  - L61 _member_ `float4 TexCoords1 : ATTRIBUTE8;` _[#if !(MANUAL_VERTEX_FETCH) && NUM_MATERIAL_TEXCOORDS_VERTEX && NUM_MATERIAL_TEXCOORDS_VERTEX >= 3]_
  - L64 _member_ `float4 TexCoords2 : ATTRIBUTE9;` _[#if !(MANUAL_VERTEX_FETCH) && NUM_MATERIAL_TEXCOORDS_VERTEX && NUM_MATERIAL_TEXCOORDS_VERTEX >= 5]_
  - L67 _member_ `float4 TexCoords3 : ATTRIBUTE10;` _[#if !(MANUAL_VERTEX_FETCH) && NUM_MATERIAL_TEXCOORDS_VERTEX && NUM_MATERIAL_TEXCOORDS_VERTEX >= 7]_
- L97-109 _struct_ **`FVertexFactoryIntermediates`** `struct FVertexFactoryIntermediates` — Caches intermediates that would otherwise have to be computed multiple times.  Avoids relying on the compiler to optimize out redundant operations.
  - L99 _member_ `half3x3 TangentToLocal;`
  - L100 _member_ `half3x3 TangentToWorld;`
  - L101 _member_ `half TangentToWorldSign;`
  - L102 _member_ `half4 VertexColors;`
  - L103 _member_ `float2 HairPrimitiveLength;`
  - L104 _member_ `float4 HairPrimitiveMaterial;`
  - L105 _member_ `float HairPrimitiveGroupIndex;`
  - L108 _member_ `FSceneDataIntermediates SceneData;` — Cached primitive and instance data
- L125-132 _struct_ **`FHairCardsPoint`** `struct FHairCardsPoint`
  - L127 _member_ `float3 Position;`
  - L128 _member_ `float CardLength;`
  - L129 _member_ `float GroupIndex;`
  - L130 _member_ `float4 Materials;`
  - L131 _member_ `half4 VertexColors;`
- L514-517 _struct_ **`FVertexFactoryRayTracingInterpolants`** `struct FVertexFactoryRayTracingInterpolants` _[#if NEEDS_VERTEX_FACTORY_INTERPOLATION]_
  - L516 _member_ `FVertexFactoryInterpolantsVSToPS InterpolantsVSToPS;` _[#if NEEDS_VERTEX_FACTORY_INTERPOLATION]_

#### Global resources (textures / buffers / samplers) (2)

- L22 _resource_ `Buffer<float4> VertexFetch_InstanceOriginBuffer;` _[#if MANUAL_VERTEX_FETCH]_
- L23 _resource_ `Buffer<float4> VertexFetch_InstanceTransformBuffer;` _[#if MANUAL_VERTEX_FETCH]_

#### Functions (33)

- L78-91 _function_ `FVertexFactoryInput LoadVertexFactoryInputForHGS(uint TriangleIndex, int VertexIndex)` _[#if RAYHITGROUPSHADER]_
- L111-114 _function_ `FPrimitiveSceneData GetPrimitiveData(FVertexFactoryIntermediates Intermediates)`
- L116-123 _function_ `uint GetHairVertexFetchId(FVertexFactoryInput Input)`
- L134-163 _function_ `FHairCardsPoint GetVertexPosition(FVertexFactoryInput Input)`
- L165-174 _function_ `float3 GetVertexPreviousPosition(FVertexFactoryInput Input)`
- L177-184 _function_ `float2 GetSegmentUVCoord(FVertexFactoryInput Input)` — Segment UV coord of an hair segment. This is different from the UV coord of the hair strands
- L187-219 _function_ `FMaterialPixelParameters GetMaterialPixelParameters(FVertexFactoryInterpolantsVSToPS Interpolants, float4 SvPosition)` — Converts from vertex factory specific interpolants to a FMaterialPixelParameters, which is used by material inputs.
- L221-229 _function_ `half3x3 CalcTangentToWorldNoScale(FVertexFactoryIntermediates Intermediates, half3x3 TangentToLocal)`
- L234-246 _function_ `void GetRootUVsAtlasUVs(FVertexFactoryInput Input, inout float2 OutAtlasUV, inout float2 OutRootUV)`
- L249-291 _function_ `void GetTexCoords(FVertexFactoryInput Input, inout float2 OutTexCoords[NUM_MATERIAL_TEXCOORDS_VERTEX])` _[#if NUM_MATERIAL_TEXCOORDS_VERTEX]_
- L295-332 _function_ `FMaterialVertexParameters GetMaterialVertexParameters( FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, float3 WorldPosition, half3x3 TangentToLocal, bool bIsPreviousFrame = false)` — Converts from vertex factory specific input to a FMaterialVertexParameters, which is used by vertex shader material inputs.
- L334-337 _function_ `float4 CalcWorldPosition(float3 Position, FDFMatrix LocalToWorld)`
- L339-366 _function_ `half3x3 CalcTangentToLocal(FVertexFactoryInput Input, inout float TangentSign)`
- L368-372 _function_ `half3x3 CalcTangentToWorld(FVertexFactoryIntermediates Intermediates, half3x3 TangentToLocal)`
- L374-390 _function_ `FVertexFactoryIntermediates GetVertexFactoryIntermediates(FVertexFactoryInput Input)`
- L399-402 _function_ `half3x3 VertexFactoryGetTangentToLocal( FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates )` — Get the 3x3 tangent basis vectors for this vertex factory this vertex factory will calculate the binormal on-the-fly @param Input - vertex input stream structure @return 3x3 matrix
- L405-410 _function_ `float4 VertexFactoryGetWorldPosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)` — @return translated world position
- L412-415 _function_ `float3 VertexFactoryGetInstanceSpacePosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)`
- L417-420 _function_ `float4 VertexFactoryGetRasterizedWorldPosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, float4 InWorldPosition)`
- L422-425 _function_ `float3 VertexFactoryGetPositionForVertexLighting(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, float3 TranslatedWorldPosition)`
- L427-462 _function_ `FVertexFactoryInterpolantsVSToPS VertexFactoryGetInterpolantsVSToPS(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, FMaterialVertexParameters VertexParameters)`
- L465-468 _function_ `float4 VertexFactoryGetWorldPosition(FVertexFactoryInput Input)` — for depth-only pass (Not used by the actual hair shaders)
- L471-474 _function_ `float4 VertexFactoryGetWorldPositionRaw(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)` — @return translated world position (without quad extension/reorientation).This is used only for velocity computation
- L477-481 _function_ `float4 VertexFactoryGetPreviousWorldPosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)` — @return previous translated world position
- L484-487 _function_ `float3 VertexFactoryGetPreviousInstanceSpacePosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)` — local position relative to instance
- L489-493 _function_ `float4 VertexFactoryGetTranslatedPrimitiveVolumeBounds(FVertexFactoryInterpolantsVSToPS Interpolants)`
- L495-498 _function_ `uint VertexFactoryGetPrimitiveId(FVertexFactoryInterpolantsVSToPS Interpolants)`
- L500-503 _function_ `float3 VertexFactoryGetWorldNormal(FVertexFactoryInput Input)`
- L505-508 _function_ `float3 VertexFactoryGetWorldNormal(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)`
- L519-526 _function_ `float2 VertexFactoryGetRayTracingTextureCoordinate(FVertexFactoryRayTracingInterpolants Interpolants)` _[#if NEEDS_VERTEX_FACTORY_INTERPOLATION]_
- L528-531 _function_ `FVertexFactoryInterpolantsVSToPS VertexFactoryAssignInterpolants(FVertexFactoryRayTracingInterpolants Input)` _[#if NEEDS_VERTEX_FACTORY_INTERPOLATION]_
- L533-538 _function_ `FVertexFactoryRayTracingInterpolants VertexFactoryGetRayTracingInterpolants(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, FMaterialVertexParameters VertexParameters)` _[#if NEEDS_VERTEX_FACTORY_INTERPOLATION]_
- L540-588 _function_ `FVertexFactoryRayTracingInterpolants VertexFactoryInterpolate(FVertexFactoryRayTracingInterpolants a, float aInterp, FVertexFactoryRayTracingInterpolants b, float bInterp)` _[#if NEEDS_VERTEX_FACTORY_INTERPOLATION]_

#### Prototypes (2)

- L231 _prototype_ `float3 VertexFactoryGetPreviousInstanceSpacePosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)`
- L232 _prototype_ `float3 VertexFactoryGetInstanceSpacePosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)`

#### Top-level macro invocations (1)

- L72-75 _macro_call_ `VF_GPUSCENE_DECLARE_INPUT_BLOCK(13) VF_INSTANCED_STEREO_DECLARE_INPUT_BLOCK() VF_MOBILE_MULTI_VIEW_DECLARE_INPUT_BLOCK()` (scope `FVertexFactoryInput`)

#### C++ shader bindings (IMPLEMENT_* naming this file, 1)

- `EVertexFactoryFlags::UsedWithMaterials
	\| EVertexFactoryFlags::SupportsDynamicLighting
	\| EVertexFactoryFlags::SupportsPrecisePrevWorldPos
	\| EVertexFactoryFlags::SupportsCachingMeshDrawCommands
	\| EVertexFactoryFlags::SupportsRayTracing
	\| EVertexFactoryFlags::SupportsPrimitiveIdStream
	\| EVertexFactoryFlags::SupportsPSOPrecaching
	\| EVertexFactoryFlags::SupportsManualVertexFetch` → entry not found in file (macro-generated or #include'd); C++ `FHairCardsVertexFactory`  via IMPLEMENT_VERTEX_FACTORY_TYPE (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairCardsVertexFactory.cpp:576)

### `Shaders/Private/HairStrands/HairStrandsAABB.usf` (Private)

- lines: 103; parse: all-branches
- includes: L3 `../Common.ush`, L4 `HairStrandsAABBCommon.ush`, L5 `/Engine/Shared/HairStrandsDefinitions.h`

#### Entry points (1)

- L31-99 _entry_ `[numthreads(GROUP_SIZE, 1, 1)] void Main(uint2 DispatchThreadId : SV_DispatchThreadID, uint LinearIndex : SV_GroupIndex)` — stage: **compute** — C++: `FHairMacroGroupAABBCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsMacroGroup.cpp:54) _[#if SHADER_AABBUPDATE]_

#### Global resources (textures / buffers / samplers) (4)

- L19 _resource_ `Buffer<uint> RegisteredIndexBuffer;` — Group data packed as {uint3 AABBMin, uint3 AABBMax} _[#if SHADER_AABBUPDATE]_
- L20 _resource_ `Buffer<int> InGroupAABBBuffer;` _[#if SHADER_AABBUPDATE]_
- L21 _resource_ `RWBuffer<int> OutMacroGroupAABBBuffer;` _[#if SHADER_AABBUPDATE]_
- L22 _resource_ `RWBuffer<float> OutMacroGroupVoxelSizeBuffer;` _[#if SHADER_AABBUPDATE]_

#### Global parameters (uniforms) (7)

- L9 _parameter_ `uint MacroGroupId;` _[#if SHADER_AABBUPDATE]_
- L10 _parameter_ `uint MacroGroupCount;` _[#if SHADER_AABBUPDATE]_
- L12 _parameter_ `float PixelSizeAtDepth1;` _[#if SHADER_AABBUPDATE]_
- L13 _parameter_ `float NumPixelPerVoxel;` _[#if SHADER_AABBUPDATE]_
- L14 _parameter_ `uint VoxelPageResolution;` _[#if SHADER_AABBUPDATE]_
- L15 _parameter_ `uint PassCount;` _[#if SHADER_AABBUPDATE]_
- L16 _parameter_ `float3 TranslatedWorldOffsetCorrection;` _[#if SHADER_AABBUPDATE]_

#### groupshared (2)

- L29 _groupshared_ `groupshared float3 g_MinBounds[GROUP_SIZE];` _[#if SHADER_AABBUPDATE]_
- L30 _groupshared_ `groupshared float3 g_MaxBounds[GROUP_SIZE];` _[#if SHADER_AABBUPDATE]_

#### Functions (1)

- L24-28 _function_ `void UpdateValue(inout FHairAABB B, in uint Index, in Buffer<int> InBuffer)` _[#if SHADER_AABBUPDATE]_

### `Shaders/Private/HairStrands/HairStrandsAABBCommon.ush` (Private)

- lines: 125; parse: all-branches

#### Macros (#define, 1)

- L3 `#define HAIR_AABB_PRECISION_SCALE 1000.f`

#### Structs / classes (1)

- L5-9 _struct_ **`FHairAABB`** `struct FHairAABB`
  - L7 _member_ `float3 Min;`
  - L8 _member_ `float3 Max;`

#### Functions (9)

- L11-14 _function_ `float3 GetCenter(const FHairAABB In)`
- L16-19 _function_ `float3 GetExtents(const FHairAABB In)`
- L21-27 _function_ `FHairAABB InitHairAABB()`
- L30-59 _function_ `FHairAABB Transform(const FHairAABB In, float4x4 T)`
- L61-73 _function_ `FHairAABB ReadHairAABB(uint Index, RWBuffer<int> InBuffer, float PrecisionScale = HAIR_AABB_PRECISION_SCALE)`
- L75-87 _function_ `FHairAABB ReadHairAABB(uint Index, Buffer<int> InBuffer, float PrecisionScale = HAIR_AABB_PRECISION_SCALE)`
- L89-99 _function_ `void WriteHairAABB(uint Index, FHairAABB In, RWBuffer<int> OutBuffer, float PrecisionScale = HAIR_AABB_PRECISION_SCALE)`
- L101-112 _function_ `FHairAABB UnionHairAABB(FHairAABB A, FHairAABB B)`
- L114-124 _function_ `void InterlockHairAABB(uint Index, FHairAABB In, RWBuffer<int> OutBuffer, float PrecisionScale = HAIR_AABB_PRECISION_SCALE)`

### `Shaders/Private/HairStrands/HairStrandsAttributeCommon.ush` (Private)

- lines: 114; parse: all-branches
- includes: L5 `/Engine/Private/HairStrands/HairStrandsPack.ush`, L102 `/Engine/Private/HairStrands/HairStrandsVertexFactoryCommon.ush`, L112 `/Engine/Private/HairStrands/HairStrandsAttributeTemplate.ush` [HAIR_STRAND_MESH_FACTORY]

#### Macros (#define, 18)

- L10 `#define HAIR_CURVE_ATTRIBUTE_STRIDE_ROOTUV 4`
- L11 `#define HAIR_CURVE_ATTRIBUTE_STRIDE_SEED 1`
- L12 `#define HAIR_CURVE_ATTRIBUTE_STRIDE_LENGTH 2`
- L13 `#define HAIR_CURVE_ATTRIBUTE_STRIDE_CLUMPID 2`
- L14 `#define HAIR_CURVE_ATTRIBUTE_STRIDE_CLUMPID3 8`
- L16 `#define HAIR_POINT_ATTRIBUTE_STRIDE_COLOR 4`
- L17 `#define HAIR_POINT_ATTRIBUTE_STRIDE_ROUGHNESS 1`
- L18 `#define HAIR_POINT_ATTRIBUTE_STRIDE_AO 1`
- L21 `#define HAIR_CURVE_ATTRIBUTE_OFFSET_ROOTUV(InOffsets) (InOffsets[0].x)`
- L22 `#define HAIR_CURVE_ATTRIBUTE_OFFSET_SEED(InOffsets) (InOffsets[0].y)`
- L23 `#define HAIR_CURVE_ATTRIBUTE_OFFSET_LENGTH(InOffsets) (InOffsets[0].z)`
- L24 `#define HAIR_CURVE_ATTRIBUTE_OFFSET_CLUMPID(InOffsets) (InOffsets[0].w)`
- L25 `#define HAIR_CURVE_ATTRIBUTE_OFFSET_CLUMPID3(InOffsets) (InOffsets[1].x)`
- L27 `#define HAIR_POINT_ATTRIBUTE_OFFSET_COLOR(InOffsets) (InOffsets[0].x)`
- L28 `#define HAIR_POINT_ATTRIBUTE_OFFSET_ROUGHNESS(InOffsets) (InOffsets[0].y)`
- L29 `#define HAIR_POINT_ATTRIBUTE_OFFSET_AO(InOffsets) (InOffsets[0].z)`
- L107 `#define HAIR_STRANDS_ATTRIBUTE_ACCESSORS(Name) HairStrandsVF_##Name` _[#if HAIR_STRAND_MESH_FACTORY && HAIR_STRANDS_PARAMETERS == 1]_
- L110 `#define HAIR_STRANDS_ATTRIBUTE_ACCESSORS(Name) HairStrandsVF.##Name` _[#if HAIR_STRAND_MESH_FACTORY && !(HAIR_STRANDS_PARAMETERS == 1)]_
- L3 #pragma `once`

#### Functions (8)

- L33-48 _function_ `uint InternalGetHairStrandsAttributes(uint Index, uint AttributeOffsetInBytes, uint AttributeStrideInBytes, ByteAddressBuffer InAttributeBuffer, uint InIndexToChunkDivAsShift, uint InChunkElementCount, uint InChunkStrideInBytes)` — Attribute access functions
- L50-65 _function_ `uint2 InternalGetHairStrandsAttributes64(uint Index, uint AttributeOffsetInBytes, uint AttributeStrideInBytes, ByteAddressBuffer InAttributeBuffer, uint InIndexToChunkDivAsShift, uint InChunkElementCount, uint InChunkStrideInBytes)`
- L67-71 _function_ `uint InternalGetHairStrandsAttributesPerCurve(uint HairControlPointId, uint AttributeOffsetInBytes, uint AttributeStrideInBytes, ByteAddressBuffer InAttributeBuffer, ByteAddressBuffer InPointToCurveBuffer, uint InIndexToChunkDivAsShift, uint InChunkElementCount, uint InChunkStrideInBytes)`
- L73-77 _function_ `uint2 InternalGetHairStrandsAttributesPerCurve64(uint HairControlPointId, uint AttributeOffsetInBytes, uint AttributeStrideInBytes, ByteAddressBuffer InAttributeBuffer, ByteAddressBuffer InPointToCurveBuffer, uint InIndexToChunkDivAsShift, uint InChunkElementCount, uint InChunkStrideInBytes)`
- L79-82 _function_ `uint InternalGetHairStrandsAttributesPerVertex(uint HairControlPointId, uint AttributeOffsetInBytes, uint AttributeStrideInBytes, ByteAddressBuffer InAttributeBuffer, uint InIndexToChunkDivAsShift, uint InChunkElementCount, uint InChunkStrideInBytes)`
- L84-87 _function_ `float InternalGetHairStrandsCoordU(ByteAddressBuffer InPositionBuffer, uint InPointIndex, float InRadius, float InRootScale, float InTipScale)`
- L89-92 _function_ `float InternalGetHairStrandsWorldRadius(ByteAddressBuffer InPositionBuffer, uint InPointIndex, float InRadius, float InRootScale, float InTipScale)`
- L94-97 _function_ `bool IsAttributeValid(uint InOffset)`

### `Shaders/Private/HairStrands/HairStrandsAttributeTemplate.ush` (Private)

- lines: 130; parse: all-branches

#### Macros (#define, 1)

- L11 `#define PREFIX(Name) HAIR_STRANDS_ATTRIBUTE_ACCESSORS(Name)`
- L3 #pragma `once`

#### Functions (17)

- L13-22 _function_ `float2 GetHairStrandsUV(uint InControlPointId, float2 InSegmentUV)`
- L23-36 _function_ `float2 GetHairStrandsDimensions(uint InControlPointId, float InSegmentU)`
- L37-48 _function_ `float2 GetHairStrandsRootUV(uint InControlPointId)`
- L49-52 _function_ `float GetHairStrandsSeed(uint InControlPointId)`
- L53-69 _function_ `uint3 GetHairStrandsClumpID(uint InControlPointId)`
- L70-83 _function_ `float3 GetHairStrandsColor(uint InControlPointId, float InSegmentU)`
- L84-97 _function_ `float GetHairStrandsRoughness(uint InControlPointId, float InSegmentU)`
- L98-111 _function_ `float GetHairStrandsAO(uint InControlPointId, float InSegmentU)`
- L112-115 _function_ `float GetHairStrandsDepth()`
- L116-119 _function_ `float GetHairStrandsCoverage()`
- L120-123 _function_ `float GetHairStrandsGroupIndex()`
- L124 _function_ `bool HasHairStrandsRootUV()`
- L125 _function_ `bool HasHairStrandsClumpId()`
- L126 _function_ `bool HasHairStrandsClumpId3()`
- L127 _function_ `bool HasHairStrandsColor()`
- L128 _function_ `bool HasHairStrandsRoughness()`
- L129 _function_ `bool HasHairStrandsAO()`

### `Shaders/Private/HairStrands/HairStrandsBindingCommon.ush` (Private)

- lines: 209; parse: all-branches
- includes: L4 `HairStrandsPack.ush`

#### Macros (#define, 2)

- L7 `#define HAIR_MESH_BASIS_PAD(x) x` _[#if defined(NEED_HAIR_MESH_BASIS_PADDING) && NEED_HAIR_MESH_BASIS_PADDING]_
- L9 `#define HAIR_MESH_BASIS_PAD(x) ` _[#if !(defined(NEED_HAIR_MESH_BASIS_PADDING) && NEED_HAIR_MESH_BASIS_PADDING)]_
- L2 #pragma `once`

#### Structs / classes (2)

- L12-22 _struct_ **`FHairMeshBasis`** `struct FHairMeshBasis`
  - L14 _member_ `float3 BaseO;`
  - L16 _member_ `float3 BaseT;`
  - L18 _member_ `float3 BaseB;`
  - L20 _member_ `float3 BaseN;`
- L24-33 _struct_ **`FHairMeshTriangle`** `struct FHairMeshTriangle`
  - L26 _member_ `float3 P0;`
  - L27 _member_ `float3 P1;`
  - L28 _member_ `float3 P2;`
  - L30 _member_ `float3 N0;`
  - L31 _member_ `float3 N1;`
  - L32 _member_ `float3 N2;`

#### Functions (11)

- L35-46 _function_ `float3 GetVertexPosition(uint VId, Buffer<float> InPositionBuffer, Buffer<uint> InIndexBuffer, uint InIndexOffset, uint InMaxIndexCount, uint InMaxVertexCount)`
- L48-64 _function_ `float3 GetVertexNormal(uint VId, Buffer<float4> InTangentBuffer, Buffer<uint> InIndexBuffer, uint InIndexOffset, uint InMaxIndexCount, uint InMaxVertexCount, uint InTangentFormat)`
- L67-87 _function_ `FHairMeshTriangle GetHairMeshTriangle(uint TriangleIndex, Buffer<float> InPositionBuffer, Buffer<float4> InTangentBuffer, Buffer<uint> InIndexBuffer, uint InIndexOffset, uint InMaxIndexCount, uint InMaxVertexCount, uint InTangentFormat, bool bUseVertexTangent)` — Return a mesh triangle (position + normal)
- L90-103 _function_ `FHairMeshTriangle GetHairMeshTriangle(uint TriangleIndex, Buffer<float4> InPositionBuffer)` — Return a mesh triangle (position + normal)
- L106-138 _function_ `FHairMeshBasis GetHairMeshBasis( uint TriangleIndex, Buffer<float4> InPositionBuffer, float3 B )` — Return a hair basis (origin + tangent frame)
- L140-149 _function_ `float3 ToTriangle(const float3 P, const FHairMeshBasis T)`
- L151-157 _function_ `float3 ToWorld(const float3 P, const FHairMeshBasis T)`
- L159-163 _function_ `float3 VectorToWorld(const float3 P, const FHairMeshBasis T)`
- L165-172 _function_ `float3 VectorToTriangle(const float3 P, const FHairMeshBasis T)`
- L174-178 _function_ `float3 TransformPoint(float3 P, const FHairMeshBasis RestBasis, const FHairMeshBasis DeformedBasis)`
- L181-208 _function_ `float3 ApplyRBF( float3 RestControlPoint, int InMaxSampleCount, StructuredBuffer<float4> InRestSamplePositionsBuffer, StructuredBuffer<float4> InMeshSampleWeightsBuffer, StructuredBuffer<float4> InDeformedSamplePositionsBuffer, uint RBFLocalSpace)` — Apply RBF weight onto a control point

#### Top-level macro invocations (4)

- L15 _macro_call_ `HAIR_MESH_BASIS_PAD(float _Pad0;)` (scope `FHairMeshBasis`)
- L17 _macro_call_ `HAIR_MESH_BASIS_PAD(float _Pad1;)` (scope `FHairMeshBasis`)
- L19 _macro_call_ `HAIR_MESH_BASIS_PAD(float _Pad2;)` (scope `FHairMeshBasis`)
- L21-22 _macro_call_ `HAIR_MESH_BASIS_PAD(float _Pad3;)` (scope `FHairMeshBasis`)

### `Shaders/Private/HairStrands/HairStrandsClusterCommon.ush` (Private)

- lines: 247; parse: all-branches
- includes: L3 `../Common.ush`, L4 `/Engine/Shared/HairStrandsDefinitions.h`

#### Macros (#define, 2)

- L13 `#define INDIRECT_GROUP_COUNT_X 16`
- L16 `#define MAX_HAIR_LOD 8`

#### Structs / classes (4)

- L35-59 _struct_ **`FHairClusterInfo`** `struct FHairClusterInfo` — Store info about all LODS of a cluster (total LOD count, screen size, ...)
  - L37 _member_ `uint LODCount;`
  - L38 _member_ `uint LOD_bIsVisible;`
  - L41 _member_ `float LOD0_ScreenSize;` — ScreenSize
  - L42 _member_ `float LOD1_ScreenSize;`
  - L43 _member_ `float LOD2_ScreenSize;`
  - L44 _member_ `float LOD3_ScreenSize;`
  - L45 _member_ `float LOD4_ScreenSize;`
  - L46 _member_ `float LOD5_ScreenSize;`
  - L47 _member_ `float LOD6_ScreenSize;`
  - L48 _member_ `float LOD7_ScreenSize;`
  - L51 _member_ `float LOD0_RadiusScale;` — Scale
  - L52 _member_ `float LOD1_RadiusScale;`
  - L53 _member_ `float LOD2_RadiusScale;`
  - L54 _member_ `float LOD3_RadiusScale;`
  - L55 _member_ `float LOD4_RadiusScale;`
  - L56 _member_ `float LOD5_RadiusScale;`
  - L57 _member_ `float LOD6_RadiusScale;`
  - L58 _member_ `float LOD7_RadiusScale;`
- L61-67 _struct_ **`FPackedHairClusterInfo`** `struct FPackedHairClusterInfo`
  - L63 _member_ `uint ScreenSizeX123;`
  - L64 _member_ `uint ScreenSize4567;`
  - L65 _member_ `uint RadiusScaleX123;`
  - L66 _member_ `uint RadiusScale4567;`
- L105-110 _struct_ **`FHairClusterLOD`** `struct FHairClusterLOD`
  - L107 _member_ `float RadiusScale;`
  - L108 _member_ `float LOD;`
  - L109 _member_ `uint LODCount;`
- L114-120 _struct_ **`FHairClusterDebugInfo`** `struct FHairClusterDebugInfo`
  - L116 _member_ `uint GroupIndex;`
  - L117 _member_ `float LOD;`
  - L118 _member_ `float VertexCount;`
  - L119 _member_ `float CurveCount;`

#### Functions (11)

- L22-25 _function_ `uint GetHairStrandsVertexFetchIndex(uint2 InDispatchThreadId, uint InGroupSize, uint InGroupCountX)` — When culling is disabled: return the vertex index at which the control point should be fetched.
- L28-31 _function_ `uint GetHairStrandsVertexFetchIndex_Culled(uint2 InDispatchThreadId, uint InGroupSize)` — When culling is enabled: return the vertex index at which the control point should be fetched.
- L69-101 _function_ `FHairClusterInfo UnpackHairClusterInfo(FPackedHairClusterInfo In, float4 InParameters)`
- L125-129 _function_ `bool IsLODVisible(FHairClusterInfo InInfo, float LOD)` — Compute if a hair cluster is visible for a given LOD
- L132-173 _function_ `float GetLOD(FHairClusterInfo InInfo, float InScreenSize, float InLODBias)` — Compute the hair LOD based on the cluster screen size
- L176-203 _function_ `FHairClusterLOD GetHairClusterLOD( FPackedHairClusterInfo InPacked, float4 InClusterInfoParameters, float LOD)` — Compute the hair cluster LOD for a given LOD level
- L207-219 _function_ `float ComputeBoundsScreenSize(float3 InSphereOrigin, float InSphereRadius, float3 InViewOrigin, float4x4 InProjMatrix)` — Compute the screen size of a bounding sphere This is the equivalent of ComputeBoundsScreenSize in SceneManagement.h
- L224-227 _function_ `uint UnpackPointLOD(uint InPacked, uint InIndex)`
- L229-236 _function_ `uint GetHairControlPointMinLOD(uint InPointIndex, Buffer<uint> InPointLODBuffer)`
- L238-241 _function_ `bool IsHairControlPointActive(uint InMinLOD, float InLODIndex)`
- L243-247 _function_ `bool IsHairControlPointActive(uint InPointIndex, Buffer<uint> InPointLODBuffer, float InLODIndex)`

### `Shaders/Private/HairStrands/HairStrandsClusterCulling.usf` (Private)

- lines: 566; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`, L4 `../ColorMap.ush`, L5 `HairStrandsAABBCommon.ush`, L6 `HairStrandsClusterCommon.ush`, L7 `HairStrandsVertexFactoryCommon.ush`, L62 `../ThreadGroupPrefixSum.ush` [SHADER_CLUSTER_CULL]

#### Macros (#define, 9)

- L13 `#define COMPACTCS_NUMTHREAD 64`
- L17 `#define PREFIXSUM_PARALLEL 512`
- L18 `#define PREFIXSUM_LASTTHREAD (PREFIXSUM_PARALLEL-1)`
- L20 `#define D_USE_CONTINUOUSLOD 1`
- L21 `#define D_LOD_DEBUG_SCALE 1000.0f`
- L61 `#define NUM_THREADS_PER_GROUP GROUP_SIZE` _[#if SHADER_CLUSTER_CULL]_
- L87 `#define CURVE_PER_GROUP (GROUP_SIZE / PERMUTATION_POINT_PER_CURVE)` _[#if SHADER_CLUSTER_CULL]_
- L88 `#define MAX_CURVE CURVE_PER_GROUP` _[#if SHADER_CLUSTER_CULL]_
- L89 `#define MAX_POINT PERMUTATION_POINT_PER_CURVE` _[#if SHADER_CLUSTER_CULL]_

#### Entry points (5)

- L42-52 _entry_ `[numthreads(64, 1, 1)] void MainClearAABBCS(uint2 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FClearAABBCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsInterpolation.cpp:1430) _[#if defined(SHADER_CLEARAABB)]_
- L122-233 _entry_ `[numthreads(GROUP_SIZE, 1, 1)] void Main(uint3 DispatchThreadId : SV_DispatchThreadID, uint ThreadIndex : SV_GroupIndex, uint2 GroupIndex : SV_GroupID)` — stage: **compute** — C++: `FHairClusterCullCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsClusterCulling.cpp:58) — C++: `FHairClusterCullArgsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsClusterCulling.cpp:85) _[#if SHADER_CLUSTER_CULL && PERMUTATION_POINT_PER_CURVE < 64]_
- L253-354 _entry_ `[numthreads(GROUP_SIZE, 1, 1)] void Main(uint3 DispatchThreadId : SV_DispatchThreadID, uint ThreadIndex : SV_GroupIndex, uint2 GroupIndex : SV_GroupID)` — stage: **compute** — C++: `FHairClusterCullCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsClusterCulling.cpp:58) — C++: `FHairClusterCullArgsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsClusterCulling.cpp:85) — Version for curve with >32 points _[#if SHADER_CLUSTER_CULL && PERMUTATION_POINT_PER_CURVE == 64]_
- L372-392 _entry_ `[numthreads(1, 1, 1)] void Main(uint DispatchThreadId : SV_DispatchThreadID, uint ThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FHairClusterCullCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsClusterCulling.cpp:58) — C++: `FHairClusterCullArgsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsClusterCulling.cpp:85) _[#if SHADER_CLUSTER_CULL_ARGS]_
- L425-563 _entry_ `[numthreads(GROUP_SIZE, 1, 1)] void ClusterAABBEvaluationCS(uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint ThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FHairClusterAABBCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsInterpolation.cpp:950) _[#if SHADER_CLUSTERAABB]_

#### Global resources (textures / buffers / samplers) (18)

- L40 _resource_ `RWBuffer<int> OutAABBBuffer;` _[#if defined(SHADER_CLEARAABB)]_
- L73 _resource_ `ByteAddressBuffer CurveBuffer;` _[#if SHADER_CLUSTER_CULL]_
- L74 _resource_ `Buffer<uint> CurveToClusterIdBuffer;` _[#if SHADER_CLUSTER_CULL]_
- L75 _resource_ `Buffer<uint> PointLODBuffer;` _[#if SHADER_CLUSTER_CULL]_
- L76 _resource_ `StructuredBuffer<FPackedHairClusterInfo> ClusterInfoBuffer;` _[#if SHADER_CLUSTER_CULL]_
- L78 _resource_ `RWStructuredBuffer<uint> OutPointCounter;` _[#if SHADER_CLUSTER_CULL]_
- L79 _resource_ `RWBuffer<uint> OutIndexBuffer;` _[#if SHADER_CLUSTER_CULL]_
- L80 _resource_ `RWByteAddressBuffer OutCulledCurveBuffer;` _[#if SHADER_CLUSTER_CULL]_
- L367 _resource_ `StructuredBuffer<uint> PointCounterBuffer;` _[#if SHADER_CLUSTER_CULL_ARGS]_
- L368 _resource_ `RWBuffer<uint> RWIndirectDrawArgsBuffer;` _[#if SHADER_CLUSTER_CULL_ARGS]_
- L369 _resource_ `RWBuffer<uint> RWIndirectDispatchArgsBuffer;` _[#if SHADER_CLUSTER_CULL_ARGS]_
- L370 _resource_ `RWBuffer<uint> RWIndirectDispatchArgsGlobalBuffer;` _[#if SHADER_CLUSTER_CULL_ARGS]_
- L411 _resource_ `ByteAddressBuffer RenCurveBuffer;` _[#if SHADER_CLUSTERAABB]_
- L412 _resource_ `Buffer<uint> RenPointLODBuffer;` _[#if SHADER_CLUSTERAABB]_
- L413 _resource_ `ByteAddressBuffer RenderDeformedPositionBuffer;` _[#if SHADER_CLUSTERAABB]_
- L414 _resource_ `StructuredBuffer<float4> RenderDeformedOffsetBuffer;` _[#if SHADER_CLUSTERAABB]_
- L416 _resource_ `RWBuffer<int> OutClusterAABBBuffer;` — Cluster data packed as {uint3 AABBMin, uint3 AABBMax} _[#if SHADER_CLUSTERAABB]_
- L417 _resource_ `RWBuffer<int> OutGroupAABBBuffer;` — Group data packed as {uint3 AABBMin, uint3 AABBMax} _[#if SHADER_CLUSTERAABB]_

#### Global parameters (uniforms) (19)

- L39 _parameter_ `uint AABBCount;` _[#if defined(SHADER_CLEARAABB)]_
- L65 _parameter_ `uint ClusterGroupIndex;` — uint ForceLOD; _[#if SHADER_CLUSTER_CULL]_
- L66 _parameter_ `float LODIndex;` _[#if SHADER_CLUSTER_CULL]_
- L67 _parameter_ `float LODBias;` _[#if SHADER_CLUSTER_CULL]_
- L68 _parameter_ `uint CurveCount;` _[#if SHADER_CLUSTER_CULL]_
- L69 _parameter_ `uint CurvePerGroup;` _[#if SHADER_CLUSTER_CULL]_
- L70 _parameter_ `uint DispatchCountX;` _[#if SHADER_CLUSTER_CULL]_
- L71 _parameter_ `float4 ClusterInfoParameters;` _[#if SHADER_CLUSTER_CULL]_
- L365 _parameter_ `uint InstanceRegisteredIndex;` _[#if SHADER_CLUSTER_CULL_ARGS]_
- L366 _parameter_ `uint ClusterGroupIndex;` _[#if SHADER_CLUSTER_CULL_ARGS]_
- L401 _parameter_ `uint InstanceRegisteredIndex;` _[#if SHADER_CLUSTERAABB]_
- L402 _parameter_ `uint CurveCount;` _[#if SHADER_CLUSTERAABB]_
- L403 _parameter_ `uint ClusterOffset;` _[#if SHADER_CLUSTERAABB]_
- L404 _parameter_ `uint ClusterCount;` _[#if SHADER_CLUSTERAABB]_
- L405 _parameter_ `float ClusterScale;` _[#if SHADER_CLUSTERAABB]_
- L406 _parameter_ `float3 CPUBoundMin;` _[#if SHADER_CLUSTERAABB]_
- L407 _parameter_ `float3 CPUBoundMax;` _[#if SHADER_CLUSTERAABB]_
- L408 _parameter_ `float LODIndex;` _[#if SHADER_CLUSTERAABB]_
- L409 _parameter_ `float4x4 LocalToTranslatedWorldMatrix;` _[#if SHADER_CLUSTERAABB]_

#### groupshared (22)

- L107 _groupshared_ `groupshared uint CurvePointIndex[MAX_CURVE];` _[#if SHADER_CLUSTER_CULL && PERMUTATION_POINT_PER_CURVE < 64]_
- L108 _groupshared_ `groupshared uint CurvePointCount[MAX_CURVE];` _[#if SHADER_CLUSTER_CULL && PERMUTATION_POINT_PER_CURVE < 64]_
- L109 _groupshared_ `groupshared uint ClusterLOD[MAX_CURVE];` _[#if SHADER_CLUSTER_CULL && PERMUTATION_POINT_PER_CURVE < 64]_
- L110 _groupshared_ `groupshared uint LODCount[MAX_CURVE];` _[#if SHADER_CLUSTER_CULL && PERMUTATION_POINT_PER_CURVE < 64]_
- L112 _groupshared_ `groupshared uint AllocationOffset;` _[#if SHADER_CLUSTER_CULL && PERMUTATION_POINT_PER_CURVE < 64]_
- L113 _groupshared_ `groupshared uint AllocationCount;` _[#if SHADER_CLUSTER_CULL && PERMUTATION_POINT_PER_CURVE < 64]_
- L116 _groupshared_ `groupshared uint CulledPointIndices[MAX_CURVE * MAX_POINT];` — Store locally the culled point index (encoded into 8 bits, and store 4 per uint) _[#if SHADER_CLUSTER_CULL && PERMUTATION_POINT_PER_CURVE < 64]_
- L117 _groupshared_ `groupshared uint ValidPoints[MAX_CURVE][MAX_POINT];` _[#if SHADER_CLUSTER_CULL && PERMUTATION_POINT_PER_CURVE < 64]_
- L119 _groupshared_ `groupshared uint WriteOffset0[MAX_CURVE];` _[#if SHADER_CLUSTER_CULL && PERMUTATION_POINT_PER_CURVE < 64]_
- L120 _groupshared_ `groupshared uint WriteOffsetN[MAX_CURVE];` _[#if SHADER_CLUSTER_CULL && PERMUTATION_POINT_PER_CURVE < 64]_
- L241 _groupshared_ `groupshared uint CurvePointIndex;` _[#if SHADER_CLUSTER_CULL && PERMUTATION_POINT_PER_CURVE == 64]_
- L242 _groupshared_ `groupshared uint CurvePointCount;` _[#if SHADER_CLUSTER_CULL && PERMUTATION_POINT_PER_CURVE == 64]_
- L243 _groupshared_ `groupshared float ClusterLOD;` _[#if SHADER_CLUSTER_CULL && PERMUTATION_POINT_PER_CURVE == 64]_
- L244 _groupshared_ `groupshared uint LODCount;` _[#if SHADER_CLUSTER_CULL && PERMUTATION_POINT_PER_CURVE == 64]_
- L246 _groupshared_ `groupshared uint AllocationOffset;` _[#if SHADER_CLUSTER_CULL && PERMUTATION_POINT_PER_CURVE == 64]_
- L247 _groupshared_ `groupshared uint AllocationCount;` _[#if SHADER_CLUSTER_CULL && PERMUTATION_POINT_PER_CURVE == 64]_
- L250 _groupshared_ `groupshared uint CulledPointIndices[HAIR_MAX_NUM_POINT_PER_CURVE];` — Store locally the culled point index (encoded into 8 bits, and store 4 per uint) _[#if SHADER_CLUSTER_CULL && PERMUTATION_POINT_PER_CURVE == 64]_
- L419 _groupshared_ `groupshared float3 SharedClusterAABBMin[GROUP_SIZE];` _[#if SHADER_CLUSTERAABB]_
- L420 _groupshared_ `groupshared float3 SharedClusterAABBMax[GROUP_SIZE];` _[#if SHADER_CLUSTERAABB]_
- L421 _groupshared_ `groupshared uint CurvePointIndex;` _[#if SHADER_CLUSTERAABB]_
- L422 _groupshared_ `groupshared uint CurvePointCount;` _[#if SHADER_CLUSTERAABB]_
- L423 _groupshared_ `groupshared float3 OutHairPositionOffset;` _[#if SHADER_CLUSTERAABB]_

#### Functions (2)

- L28-34 _function_ `uint3 ComputeDispatchGroupCount2D(uint GroupCount)`
- L91-99 _function_ `uint GetGlobalCurveIndex(uint ThreadIndex, uint2 GroupIndex)` _[#if SHADER_CLUSTER_CULL]_

### `Shaders/Private/HairStrands/HairStrandsCommon.ush` (Private)

- lines: 47; parse: all-branches
- L3 #pragma `once`

#### Structs / classes (2)

- L5-10 _struct_ **`FHairAverageEnergy`** `struct FHairAverageEnergy`
  - L7 _member_ `float3 A_R;`
  - L8 _member_ `float3 A_TT;`
  - L9 _member_ `float3 A_TRT;`
- L12-16 _struct_ **`FHairAverageScattering`** `struct FHairAverageScattering`
  - L14 _member_ `float3 A_front;` — Front Scattering A_f
  - L15 _member_ `float3 A_back;` — Back Scattering A_b

#### Functions (4)

- L18 _function_ `float3 FromLinearAbsorption(float3 In)`
- L19 _function_ `float3 ToLinearAbsorption(float3 In)`
- L21-32 _function_ `FHairAverageScattering SampleHairLUT(Texture3D<float4> LUTTexture, SamplerState LUTSampler, float3 InAbsorption, float Roughness, float SinViewAngle)`
- L34-46 _function_ `FHairAverageEnergy SampleHairEnergyLUT(Texture3D<float4> LUTTexture, SamplerState LUTSampler, float3 InAbsorption, float Roughness, float SinViewAngle)`

### `Shaders/Private/HairStrands/HairStrandsComposition.usf` (Private)

- lines: 507; parse: first-branch (retry, +0 merged from all-branches pass)
- includes: L3 `../Common.ush`, L4 `../SceneTexturesCommon.ush`, L5 `../DeferredShadingCommon.ush`, L6 `HairStrandsVisibilityCommon.ush`, L29 `../HeightFogCommon.ush` [SHADER_COMPOSE_SAMPLE \|\| SHADER_HOLDOUT], L30 `../SkyAtmosphereCommon.ush` [SHADER_COMPOSE_SAMPLE \|\| SHADER_HOLDOUT], L294 `../CircleDOFCommon.ush` [SHADER_DOFDEPTH], L345 `HairStrandsGBufferCommon.ush` [SHADER_WRITE_GBUFFER], L350 `../Substrate/Substrate.ush` [SHADER_WRITE_GBUFFER && SUBSTRATE_ENABLED && SUBSTRATE_GBUFFER_FORMAT==1], L351 `../Substrate/SubstrateExport.ush` [SHADER_WRITE_GBUFFER && SUBSTRATE_ENABLED && SUBSTRATE_GBUFFER_FORMAT==1]

#### Macros (#define, 5)

- L81 `#define SLW_COMPOSE_NONE 0` _[#if SHADER_COMPOSE_SAMPLE && PERMUTATION_READ_SLW_DEPTH]_
- L82 `#define SLW_COMPOSE_BEHIND_WATER 1` _[#if SHADER_COMPOSE_SAMPLE && PERMUTATION_READ_SLW_DEPTH]_
- L83 `#define SLW_COMPOSE_INFRONTOF_WATER 2` _[#if SHADER_COMPOSE_SAMPLE && PERMUTATION_READ_SLW_DEPTH]_
- L348 `#define SUBSTRATE_INLINE_SHADING 1` _[#if SHADER_WRITE_GBUFFER && SUBSTRATE_ENABLED && SUBSTRATE_GBUFFER_FORMAT==1]_
- L349 `#define MATERIAL_SUBSTRATE_OPAQUE_PRECOMPUTED_LIGHTING 0` _[#if SHADER_WRITE_GBUFFER && SUBSTRATE_ENABLED && SUBSTRATE_GBUFFER_FORMAT==1]_

#### Entry points (5)

- L14-21 _entry_ `void FastResolvePS(in FScreenVertexOutput Input)` — stage: **pixel (from C++ binding)** — C++: `FHairVisibilityFastResolveMaskPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsComposition.cpp:486) _[#if SHADER_FASTRESOLVE_MASK]_
- L91-183 _entry_ `void ComposeSamplePS( in FScreenVertexOutput Input, out float4 OutColor : SV_Target0 ,out float OutDepth : SV_DEPTH )` — stage: **pixel (from C++ binding)** — C++: `FHairVisibilityComposeSamplePS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsComposition.cpp:329) _[#if SHADER_COMPOSE_SAMPLE]_
- L233-287 _entry_ `void HoldoutPS( in FScreenVertexOutput Input, out float4 OutColor : SV_Target0, out float OutDepth : SV_DEPTH)` — stage: **pixel (from C++ binding)** — C++: `FHairHoldoutPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsComposition.cpp:223) _[#if SHADER_HOLDOUT]_
- L299-337 _entry_ `void DOFDepthPS( in FScreenVertexOutput Input, out float OutTexture : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FHairDOFDepthPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsComposition.cpp:420) _[#if SHADER_DOFDEPTH]_
- L359-505 _entry_ `void MainPS( in float2 UV : TEXCOORD , in float4 SvPosition: SV_Position , out float OutDepth : SV_DEPTH , out float4 OutGBufferA : SV_Target0 , out float4 OutGBufferB : SV_Target1 , out float4 OutGBufferC : SV_Target2 , out float4 OutGBufferD : SV_Target3 , out float4 OutGBufferE : SV_Target4 , out float OutDepth : SV_DEPTH )` — stage: **pixel (from C++ binding)** — C++: `FHairVisibilityGBufferWritePS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsComposition.cpp:569) _[#if SHADER_WRITE_GBUFFER]_

#### Global resources (textures / buffers / samplers) (7)

- L12 _resource_ `Texture2D<uint> ResolveMaskTexture;` _[#if SHADER_FASTRESOLVE_MASK]_
- L85 _resource_ `Texture2D<float> SLWDepthTexture;` _[#if SHADER_COMPOSE_SAMPLE && PERMUTATION_READ_SLW_DEPTH]_
- L88 _resource_ `Texture2D<float> HairDOFDepthTexture;` _[#if SHADER_COMPOSE_SAMPLE]_
- L89 _resource_ `Texture2D<float4> HairLightingSampleBuffer;` _[#if SHADER_COMPOSE_SAMPLE]_
- L231 _resource_ `Texture2D<float> HairDOFDepthTexture;` _[#if SHADER_HOLDOUT]_
- L353 _resource_ `RWTexture2D<SUBSTRATE_TOP_LAYER_TYPE> RWTopLayerTexture;` _[#if SHADER_WRITE_GBUFFER && SUBSTRATE_ENABLED && SUBSTRATE_GBUFFER_FORMAT==1]_
- L354 _resource_ `RWTexture2DArray<uint> RWMaterialTextureArray;` _[#if SHADER_WRITE_GBUFFER && SUBSTRATE_ENABLED && SUBSTRATE_GBUFFER_FORMAT==1]_

#### Global parameters (uniforms) (8)

- L76 _parameter_ `int2 OutputResolution;` _[#if SHADER_COMPOSE_SAMPLE]_
- L77 _parameter_ `uint bComposeDofDepth;` _[#if SHADER_COMPOSE_SAMPLE]_
- L78 _parameter_ `uint bHasHoldout;` _[#if SHADER_COMPOSE_SAMPLE]_
- L84 _parameter_ `uint SLWComposeType;` _[#if SHADER_COMPOSE_SAMPLE && PERMUTATION_READ_SLW_DEPTH]_
- L229 _parameter_ `uint PassType;` — PassType: * 0: Output attenuation for the scene pixel (alpha only) * 1: Output hair contribution to the scene pixel (alpha value only) _[#if SHADER_HOLDOUT]_
- L230 _parameter_ `uint bComposeDofDepth;` _[#if SHADER_HOLDOUT]_
- L352 _parameter_ `uint MaxBytesPerPixel;` _[#if SHADER_WRITE_GBUFFER && SUBSTRATE_ENABLED && SUBSTRATE_GBUFFER_FORMAT==1]_
- L357 _parameter_ `uint bWriteDummyData;` _[#if SHADER_WRITE_GBUFFER]_

#### Functions (1)

- L32-69 _function_ `float4 EvaluateVolumetric(float3 WorldPosition, float SceneDepth)` _[#if SHADER_COMPOSE_SAMPLE \|\| SHADER_HOLDOUT]_

### `Shaders/Private/HairStrands/HairStrandsCoverage.usf` (Private)

- lines: 57; parse: all-branches; parse notes: 1
- includes: L3 `../Common.ush`, L4 `HairStrandsVisibilityCommon.ush`

#### Macros (#define, 1)

- L19 `#define TILE_PIXEL_SIZE 8`

#### Entry points (1)

- L21-41 _entry_ `[numthreads(TILE_PIXEL_SIZE, TILE_PIXEL_SIZE, 1)] void MainCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FHairCountToCoverageCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVisibility.cpp:3131)

#### Global resources (textures / buffers / samplers) (5)

- L10 _resource_ `SamplerState LinearSampler;`
- L11 _resource_ `Texture2D<float> HairCoverageLUT;`
- L13 _resource_ `Texture2D<float2> HairCountTexture;` _[#if PERMUTATION_INPUT_TYPE == 0]_
- L15 _resource_ `Texture2D<uint> HairCountTexture;` _[#if !(PERMUTATION_INPUT_TYPE == 0) && PERMUTATION_INPUT_TYPE == 1]_
- L17 _resource_ `RWTexture2D<float> OutputTexture;`

#### Global parameters (uniforms) (3)

- L6 _parameter_ `int2 OutputResolution;`
- L7 _parameter_ `float LUT_HairCount;`
- L8 _parameter_ `float LUT_HairRadiusCount;`

#### Stray brace blocks (function body split by #if) (1)

- L44-56 _stray_block_ `{ ... }` _[#if PERMUTATION_INPUT_TYPE == 1]_

<details><summary>parse notes</summary>

- L44: brace block without header (code split across #if branches)

</details>

### `Shaders/Private/HairStrands/HairStrandsDebug.usf` (Private)

- lines: 3043; parse: all-branches
- includes: L3 `../Common.ush`, L4 `/Engine/Shared/HairStrandsDefinitions.h`, L5 `../HairShadingCommon.ush`, L6 `../ColorMap.ush`, L12 `../ShaderPrint.ush` [SHADER_PRINT_INSTANCE \|\| SHADER_PRINT \|\| SHADER_PRINT_MEMORY \|\| SHADER_CLUSTERAABB \|\| SHADER_DOMINFO \|\| SHADER_PRINT_HAIR_SKIN_CACHE], L99 `../ColorMap.ush` [SHADER_DEBUG_MODE], L100 `HairStrandsVisibilityCommon.ush` [SHADER_DEBUG_MODE], L252 `HairStrandsVertexFactoryCommon.ush` [SHADER_CVS], L253 `../ShaderPrint.ush` [SHADER_CVS], L351 `HairStrandsBindingCommon.ush` [SHADER_MESH_PROJECTION_HAIR], L352 `../ShaderPrint.ush` [SHADER_MESH_PROJECTION_HAIR], L763 `../ShaderPrint.ush` [SHADER_PPLL_DEBUG], L764 `HairStrandsVisibilityCommon.ush` [SHADER_PPLL_DEBUG], L860 `../PostProcessCommon.ush` [SHADER_VISUALIZEDOM], L980 `../ShaderPrint.ush` [SHADER_DOMINFO], L981 `../Matrices.ush` [SHADER_DOMINFO], L982 `../ShadingCommon.ush` [SHADER_DOMINFO], L983 `HairStrandsDeepShadowCommonStruct.ush` [SHADER_DOMINFO], L984 `HairStrandsAABBCommon.ush` [SHADER_DOMINFO], L1095 `../SceneData.ush` [SHADER_PRINT], L1096 `../ShaderPrint.ush` [SHADER_PRINT], L1097 `../CommonViewUniformBuffer.ush` [SHADER_PRINT], L1098 `../SceneTextureParameters.ush` [SHADER_PRINT], L1099 `../DeferredShadingCommon.ush` [SHADER_PRINT], L1100 `../ShaderPrint.ush` [SHADER_PRINT], L1101 `../PositionReconstructionCommon.ush` [SHADER_PRINT], L1102 `HairStrandsVisibilityCommon.ush` [SHADER_PRINT], L1103 `HairStrandsAABBCommon.ush` [SHADER_PRINT], L1460 `HairStrandsAABBCommon.ush` [SHADER_PRINT_INSTANCE], L1866 `../CommonViewUniformBuffer.ush` [SHADER_TANGENT], L1867 `../SceneTextureParameters.ush` [SHADER_TANGENT], L1868 `../DeferredShadingCommon.ush` [SHADER_TANGENT], L1869 `../ShaderPrint.ush` [SHADER_TANGENT], L1870 `../PositionReconstructionCommon.ush` [SHADER_TANGENT], L1871 `HairStrandsVisibilityCommon.ush` [SHADER_TANGENT], L1872 `HairStrandsAABBCommon.ush` [SHADER_TANGENT], L2003 `../ShaderPrint.ush` [SHADER_LOD_INFO], L2065 `../ShaderPrint.ush` [SHADER_CARDS_ATLAS], L2137 `HairStrandsVertexFactoryCommon.ush` [SHADER_CARDS_GUIDE], L2138 `../ShaderPrint.ush` [SHADER_CARDS_GUIDE], L2314 `../ShaderPrint.ush` [SHADER_SHADOW_CULLING], L2315 `../Matrices.ush` [SHADER_SHADOW_CULLING], L2412 `../Common.ush` [SHADER_ATTRIBUTE_DEBUG], L2413 `../ShaderPrint.ush` [SHADER_ATTRIBUTE_DEBUG], L2414 `HairStrandsVisibilityCommon.ush` [SHADER_ATTRIBUTE_DEBUG], L2415 `HairStrandsVertexFactoryCommon.ush` [SHADER_ATTRIBUTE_DEBUG], L2418 `HairStrandsAttributeCommon.ush` [SHADER_ATTRIBUTE_DEBUG], L2420 `/Engine/Private/HairStrands/HairStrandsAttributeTemplate.ush` [SHADER_ATTRIBUTE_DEBUG], L2841 `HairStrandsAABBCommon.ush` [defined(SHADER_CLUSTERAABB)]

#### Macros (#define, 28)

- L110 `#define DEBUG_MODE_SAMPLE_COUNT 0` _[#if SHADER_DEBUG_MODE]_
- L111 `#define DEBUG_MODE_COVERAGE_TYPE 1` _[#if SHADER_DEBUG_MODE]_
- L112 `#define DEBUG_MODE_TAA_RESOLVE_TYPE 2` _[#if SHADER_DEBUG_MODE]_
- L113 `#define DEBUG_MODE_COVERAGE 3` _[#if SHADER_DEBUG_MODE]_
- L114 `#define DEBUG_MODE_DEPTH 4` _[#if SHADER_DEBUG_MODE]_
- L115 `#define DEBUG_MODE_BASECOLOR 5` _[#if SHADER_DEBUG_MODE]_
- L116 `#define DEBUG_MODE_ROUGHNESS 6` _[#if SHADER_DEBUG_MODE]_
- L117 `#define DEBUG_MODE_SPECULAR 7` _[#if SHADER_DEBUG_MODE]_
- L118 `#define DEBUG_MODE_TANGENT 8` _[#if SHADER_DEBUG_MODE]_
- L119 `#define DEBUG_MODE_TILE 9` _[#if SHADER_DEBUG_MODE]_
- L354 `#define INPUT_ROOTS 0` _[#if SHADER_MESH_PROJECTION_HAIR]_
- L355 `#define INPUT_SAMPLES 1` _[#if SHADER_MESH_PROJECTION_HAIR]_
- L1127 `#define MATERIAL_DATA 1` _[#if SHADER_PRINT]_
- L1128 `#define DETAIL_DATA 1` _[#if SHADER_PRINT]_
- L1879 `#define HAIR_TANGENT_INVALID 0` _[#if SHADER_TANGENT]_
- L1880 `#define HAIR_TANGENT_STRANDS 1` _[#if SHADER_TANGENT]_
- L1881 `#define HAIR_TANGENT_CARDS 2` _[#if SHADER_TANGENT]_
- L2067 `#define DEBUG_MODE_DEPTH 1` _[#if SHADER_CARDS_ATLAS]_
- L2068 `#define DEBUG_MODE_COVERAGE 2` _[#if SHADER_CARDS_ATLAS]_
- L2069 `#define DEBUG_MODE_TANGENT 3` _[#if SHADER_CARDS_ATLAS]_
- L2070 `#define DEBUG_MODE_ROOTUV 4` _[#if SHADER_CARDS_ATLAS]_
- L2071 `#define DEBUG_MODE_U 5` _[#if SHADER_CARDS_ATLAS]_
- L2072 `#define DEBUG_MODE_SEED 6` _[#if SHADER_CARDS_ATLAS]_
- L2161 `#define DEBUGMODE_REN_REST 1` _[#if SHADER_CARDS_GUIDE]_
- L2162 `#define DEBUGMODE_REN_DEFORMED 2` _[#if SHADER_CARDS_GUIDE]_
- L2163 `#define DEBUGMODE_SIM_REST 3` _[#if SHADER_CARDS_GUIDE]_
- L2164 `#define DEBUGMODE_SIM_DEFORMED 4` _[#if SHADER_CARDS_GUIDE]_
- L2419 `#define HAIR_STRANDS_ATTRIBUTE_ACCESSORS(Name) HairInstance_##Name` _[#if SHADER_ATTRIBUTE_DEBUG]_

#### Entry points (19)

- L121-244 _entry_ `void MainPS( in FScreenVertexOutput Input, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FHairDebugPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:455) _[#if SHADER_DEBUG_MODE]_
- L264-338 _entry_ `[numthreads(256, 1, 1)] void MainCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FHairProjectionHairDebugCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:142) — C++: `FDrawDebugCardAtlasCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:407) — C++: `FDrawDebugStrandsCVsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:487) — C++: `FDrawDebugCardGuidesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:587) — C++: `FHairDebugPrintInstanceCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:780) — C++: `FHairDebugPrintMemoryCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:1026) — C++: `FHairDebugPrintHairSkinCacheCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomManager.cpp:514) — C++: `FHairPrintLODInfoCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:107) — C++: `FHairDebugPrintCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:203) — C++: `FHairDebugShadowCullingCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:345) — C++: `FDeepShadowInfoCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:677) — C++: `FDebugHairTangentCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:834) _[#if SHADER_CVS]_
- L435-755 _entry_ `[numthreads(256, 1, 1)] void MainCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FHairProjectionHairDebugCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:142) — C++: `FDrawDebugCardAtlasCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:407) — C++: `FDrawDebugStrandsCVsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:487) — C++: `FDrawDebugCardGuidesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:587) — C++: `FHairDebugPrintInstanceCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:780) — C++: `FHairDebugPrintMemoryCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:1026) — C++: `FHairDebugPrintHairSkinCacheCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomManager.cpp:514) — C++: `FHairPrintLODInfoCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:107) — C++: `FHairDebugPrintCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:203) — C++: `FHairDebugShadowCullingCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:345) — C++: `FDeepShadowInfoCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:677) — C++: `FDebugHairTangentCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:834) _[#if SHADER_MESH_PROJECTION_HAIR]_
- L781-851 _entry_ `[numthreads(8, 8, 1)] void VisibilityDebugPPLLCS(uint GroupIndex : SV_GroupIndex, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FHairVisibilityDebugPPLLCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:909) _[#if SHADER_PPLL_DEBUG]_
- L899-945 _entry_ `void VisualizeDomPS( in FScreenVertexOutput Input, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FDeepShadowVisualizePS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:579) _[#if SHADER_VISUALIZEDOM && PERMUTATION_OUTPUT_TYPE == 0]_
- L950-969 _entry_ `void VisualizeDomPS( in FScreenVertexOutput Input, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FDeepShadowVisualizePS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:579) _[#if SHADER_VISUALIZEDOM && PERMUTATION_OUTPUT_TYPE == 1]_
- L995-1084 _entry_ `[numthreads(1, 1, 1)] void MainCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FHairProjectionHairDebugCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:142) — C++: `FDrawDebugCardAtlasCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:407) — C++: `FDrawDebugStrandsCVsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:487) — C++: `FDrawDebugCardGuidesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:587) — C++: `FHairDebugPrintInstanceCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:780) — C++: `FHairDebugPrintMemoryCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:1026) — C++: `FHairDebugPrintHairSkinCacheCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomManager.cpp:514) — C++: `FHairPrintLODInfoCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:107) — C++: `FHairDebugPrintCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:203) — C++: `FHairDebugShadowCullingCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:345) — C++: `FDeepShadowInfoCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:677) — C++: `FDebugHairTangentCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:834) _[#if SHADER_DOMINFO]_
- L1182-1451 _entry_ `[numthreads(1, 1, 1)] void MainCS(uint InGroupIndex : SV_GroupIndex, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FHairProjectionHairDebugCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:142) — C++: `FDrawDebugCardAtlasCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:407) — C++: `FDrawDebugStrandsCVsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:487) — C++: `FDrawDebugCardGuidesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:587) — C++: `FHairDebugPrintInstanceCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:780) — C++: `FHairDebugPrintMemoryCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:1026) — C++: `FHairDebugPrintHairSkinCacheCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomManager.cpp:514) — C++: `FHairPrintLODInfoCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:107) — C++: `FHairDebugPrintCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:203) — C++: `FHairDebugShadowCullingCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:345) — C++: `FDeepShadowInfoCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:677) — C++: `FDebugHairTangentCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:834) _[#if SHADER_PRINT]_
- L1611-1857 _entry_ `[numthreads(1, 1, 1)] void MainCS(uint GroupIndex : SV_GroupIndex, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FHairProjectionHairDebugCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:142) — C++: `FDrawDebugCardAtlasCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:407) — C++: `FDrawDebugStrandsCVsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:487) — C++: `FDrawDebugCardGuidesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:587) — C++: `FHairDebugPrintInstanceCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:780) — C++: `FHairDebugPrintMemoryCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:1026) — C++: `FHairDebugPrintHairSkinCacheCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomManager.cpp:514) — C++: `FHairPrintLODInfoCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:107) — C++: `FHairDebugPrintCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:203) — C++: `FHairDebugShadowCullingCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:345) — C++: `FDeepShadowInfoCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:677) — C++: `FDebugHairTangentCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:834) _[#if SHADER_PRINT_INSTANCE]_
- L1964-1995 _entry_ `[numthreads(8, 8, 1)] void MainCS(int2 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FHairProjectionHairDebugCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:142) — C++: `FDrawDebugCardAtlasCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:407) — C++: `FDrawDebugStrandsCVsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:487) — C++: `FDrawDebugCardGuidesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:587) — C++: `FHairDebugPrintInstanceCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:780) — C++: `FHairDebugPrintMemoryCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:1026) — C++: `FHairDebugPrintHairSkinCacheCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomManager.cpp:514) — C++: `FHairPrintLODInfoCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:107) — C++: `FHairDebugPrintCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:203) — C++: `FHairDebugShadowCullingCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:345) — C++: `FDeepShadowInfoCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:677) — C++: `FDebugHairTangentCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:834) _[#if SHADER_TANGENT]_
- L2015-2057 _entry_ `[numthreads(1, 1, 1)] void MainCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FHairProjectionHairDebugCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:142) — C++: `FDrawDebugCardAtlasCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:407) — C++: `FDrawDebugStrandsCVsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:487) — C++: `FDrawDebugCardGuidesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:587) — C++: `FHairDebugPrintInstanceCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:780) — C++: `FHairDebugPrintMemoryCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:1026) — C++: `FHairDebugPrintHairSkinCacheCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomManager.cpp:514) — C++: `FHairPrintLODInfoCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:107) — C++: `FHairDebugPrintCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:203) — C++: `FHairDebugShadowCullingCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:345) — C++: `FDeepShadowInfoCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:677) — C++: `FDebugHairTangentCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:834) _[#if SHADER_LOD_INFO]_
- L2082-2128 _entry_ `[numthreads(8, 8, 1)] void MainCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FHairProjectionHairDebugCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:142) — C++: `FDrawDebugCardAtlasCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:407) — C++: `FDrawDebugStrandsCVsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:487) — C++: `FDrawDebugCardGuidesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:587) — C++: `FHairDebugPrintInstanceCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:780) — C++: `FHairDebugPrintMemoryCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:1026) — C++: `FHairDebugPrintHairSkinCacheCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomManager.cpp:514) — C++: `FHairPrintLODInfoCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:107) — C++: `FHairDebugPrintCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:203) — C++: `FHairDebugShadowCullingCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:345) — C++: `FDeepShadowInfoCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:677) — C++: `FDebugHairTangentCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:834) _[#if SHADER_CARDS_ATLAS]_
- L2166-2219 _entry_ `[numthreads(32, 1, 1)] void MainCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FHairProjectionHairDebugCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:142) — C++: `FDrawDebugCardAtlasCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:407) — C++: `FDrawDebugStrandsCVsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:487) — C++: `FDrawDebugCardGuidesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:587) — C++: `FHairDebugPrintInstanceCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:780) — C++: `FHairDebugPrintMemoryCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:1026) — C++: `FHairDebugPrintHairSkinCacheCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomManager.cpp:514) — C++: `FHairPrintLODInfoCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:107) — C++: `FHairDebugPrintCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:203) — C++: `FHairDebugShadowCullingCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:345) — C++: `FDeepShadowInfoCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:677) — C++: `FDebugHairTangentCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:834) _[#if SHADER_CARDS_GUIDE]_
- L2235-2305 _entry_ `[numthreads(4, 4, 4)] void MainCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FHairProjectionHairDebugCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:142) — C++: `FDrawDebugCardAtlasCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:407) — C++: `FDrawDebugStrandsCVsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:487) — C++: `FDrawDebugCardGuidesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:587) — C++: `FHairDebugPrintInstanceCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:780) — C++: `FHairDebugPrintMemoryCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:1026) — C++: `FHairDebugPrintHairSkinCacheCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomManager.cpp:514) — C++: `FHairPrintLODInfoCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:107) — C++: `FHairDebugPrintCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:203) — C++: `FHairDebugShadowCullingCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:345) — C++: `FDeepShadowInfoCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:677) — C++: `FDebugHairTangentCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:834) _[#if SHADER_CARDS_DIRECTION_OCCLUSION]_
- L2367-2404 _entry_ `[numthreads(1, 1, 1)] void MainCS(uint GroupIndex : SV_GroupIndex, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FHairProjectionHairDebugCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:142) — C++: `FDrawDebugCardAtlasCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:407) — C++: `FDrawDebugStrandsCVsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:487) — C++: `FDrawDebugCardGuidesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:587) — C++: `FHairDebugPrintInstanceCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:780) — C++: `FHairDebugPrintMemoryCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:1026) — C++: `FHairDebugPrintHairSkinCacheCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomManager.cpp:514) — C++: `FHairPrintLODInfoCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:107) — C++: `FHairDebugPrintCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:203) — C++: `FHairDebugShadowCullingCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:345) — C++: `FDeepShadowInfoCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:677) — C++: `FDebugHairTangentCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:834) _[#if SHADER_SHADOW_CULLING]_
- L2426-2479 _entry_ `[numthreads(1, 1, 1)] void CSMain( uint DispatchThreadID : SV_DispatchThreadID, uint GroupThreadID : SV_GroupThreadID, uint GroupID : SV_GroupID)` — stage: **compute** — C++: `FHairAttributeDebugCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVisibility.cpp:1248) _[#if SHADER_ATTRIBUTE_DEBUG]_
- L2691-2833 _entry_ `[numthreads(1, 1, 1)] void MainCS(uint GroupIndex : SV_GroupIndex, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FHairProjectionHairDebugCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:142) — C++: `FDrawDebugCardAtlasCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:407) — C++: `FDrawDebugStrandsCVsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:487) — C++: `FDrawDebugCardGuidesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:587) — C++: `FHairDebugPrintInstanceCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:780) — C++: `FHairDebugPrintMemoryCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:1026) — C++: `FHairDebugPrintHairSkinCacheCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomManager.cpp:514) — C++: `FHairPrintLODInfoCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:107) — C++: `FHairDebugPrintCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:203) — C++: `FHairDebugShadowCullingCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:345) — C++: `FDeepShadowInfoCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:677) — C++: `FDebugHairTangentCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:834) _[#if SHADER_PRINT_MEMORY]_
- L2854-2898 _entry_ `[numthreads(GROUP_SIZE, 1, 1)] void MainDrawDebugAABBCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FDrawDebugClusterAABBCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:313) _[#if defined(SHADER_CLUSTERAABB)]_
- L2954-3041 _entry_ `[numthreads(1, 1, 1)] void MainCS(uint GroupIndex : SV_GroupIndex, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FHairProjectionHairDebugCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:142) — C++: `FDrawDebugCardAtlasCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:407) — C++: `FDrawDebugStrandsCVsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:487) — C++: `FDrawDebugCardGuidesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:587) — C++: `FHairDebugPrintInstanceCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:780) — C++: `FHairDebugPrintMemoryCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomDebug.cpp:1026) — C++: `FHairDebugPrintHairSkinCacheCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomManager.cpp:514) — C++: `FHairPrintLODInfoCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:107) — C++: `FHairDebugPrintCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:203) — C++: `FHairDebugShadowCullingCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:345) — C++: `FDeepShadowInfoCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:677) — C++: `FDebugHairTangentCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:834) _[#if SHADER_PRINT_HAIR_SKIN_CACHE]_

#### Structs / classes (8)

- L1160-1166 _struct_ **`FData`** `struct FData` _[#if SHADER_PRINT]_
  - L1162 _member_ `uint InstanceID;` _[#if SHADER_PRINT]_
  - L1163 _member_ `uint RegisteredIndex;` _[#if SHADER_PRINT]_
  - L1164 _member_ `uint GeometryType;` _[#if SHADER_PRINT]_
  - L1165 _member_ `float4 InstanceScreenSphereBound;` _[#if SHADER_PRINT]_
- L1477-1521 _struct_ **`FInstanceInfo`** `struct FInstanceInfo` _[#if SHADER_PRINT_INSTANCE]_
  - L1479 _member_ `uint GroupIndex;` _[#if SHADER_PRINT_INSTANCE]_
  - L1480 _member_ `uint GroupCount;` _[#if SHADER_PRINT_INSTANCE]_
  - L1481 _member_ `uint LODCount;` _[#if SHADER_PRINT_INSTANCE]_
  - L1482 _member_ `uint GeometryType;` _[#if SHADER_PRINT_INSTANCE]_
  - L1483 _member_ `uint BindingType;` _[#if SHADER_PRINT_INSTANCE]_
  - L1484 _member_ `bool bHasSim;` _[#if SHADER_PRINT_INSTANCE]_
  - L1485 _member_ `bool bHasRBF;` _[#if SHADER_PRINT_INSTANCE]_
  - L1486 _member_ `bool bHasRTGeom;` _[#if SHADER_PRINT_INSTANCE]_
  - L1487 _member_ `float LOD;` _[#if SHADER_PRINT_INSTANCE]_
  - L1488 _member_ `float ClipValue;` _[#if SHADER_PRINT_INSTANCE]_
  - L1491 _member_ `uint StrandsCount;` — Strands data _[#if SHADER_PRINT_INSTANCE]_
  - L1492 _member_ `uint VertexCount;` _[#if SHADER_PRINT_INSTANCE]_
  - L1493 _member_ `float ScreenSize;` _[#if SHADER_PRINT_INSTANCE]_
  - L1494 _member_ `uint ActivePointCount;` _[#if SHADER_PRINT_INSTANCE]_
  - L1495 _member_ `uint ActiveCurveCount;` _[#if SHADER_PRINT_INSTANCE]_
  - L1496 _member_ `uint Attributes;` _[#if SHADER_PRINT_INSTANCE]_
  - L1497 _member_ `float Radius;` _[#if SHADER_PRINT_INSTANCE]_
  - L1498 _member_ `float Density;` _[#if SHADER_PRINT_INSTANCE]_
  - L1499 _member_ `float TipScale;` _[#if SHADER_PRINT_INSTANCE]_
  - L1500 _member_ `float RootScale;` _[#if SHADER_PRINT_INSTANCE]_
  - L1501 _member_ `float Length;` _[#if SHADER_PRINT_INSTANCE]_
  - L1502 _member_ `float LengthScale;` _[#if SHADER_PRINT_INSTANCE]_
  - L1503 _member_ `float CoverageScale;` _[#if SHADER_PRINT_INSTANCE]_
  - L1504 _member_ `bool Voxel;` _[#if SHADER_PRINT_INSTANCE]_
  - L1505 _member_ `bool CacheRen;` _[#if SHADER_PRINT_INSTANCE]_
  - L1506 _member_ `bool CacheSim;` _[#if SHADER_PRINT_INSTANCE]_
  - L1507 _member_ `bool bHasLODSwitched;` _[#if SHADER_PRINT_INSTANCE]_
  - L1508 _member_ `bool bAutoLOD;` _[#if SHADER_PRINT_INSTANCE]_
  - L1509 _member_ `bool bCurveRemapping;` _[#if SHADER_PRINT_INSTANCE]_
  - L1510 _member_ `bool bPointRemapping;` _[#if SHADER_PRINT_INSTANCE]_
  - L1511 _member_ `uint Flags;` _[#if SHADER_PRINT_INSTANCE]_
  - L1514 _member_ `uint UniqueTriangle;` — Binding _[#if SHADER_PRINT_INSTANCE]_
  - L1515 _member_ `uint UniqueSection;` _[#if SHADER_PRINT_INSTANCE]_
  - L1516 _member_ `uint RootCount;` _[#if SHADER_PRINT_INSTANCE]_
  - L1517 _member_ `uint ControlPointCount;` _[#if SHADER_PRINT_INSTANCE]_
  - L1519 _member_ `uint bIsVisibleInPrimaryView;` _[#if SHADER_PRINT_INSTANCE]_
  - L1520 _member_ `uint bIsVisibleInShadowView;` _[#if SHADER_PRINT_INSTANCE]_
  - L2916 _member_ `uint InstanceIndex;` _[#if SHADER_PRINT_HAIR_SKIN_CACHE]_
  - L2917 _member_ `uint GeometryType;` _[#if SHADER_PRINT_HAIR_SKIN_CACHE]_
  - L2918 _member_ `uint CacheType;` _[#if SHADER_PRINT_HAIR_SKIN_CACHE]_
  - L2919 _member_ `uint InstanceCount;` _[#if SHADER_PRINT_HAIR_SKIN_CACHE]_
  - L2920 _member_ `uint ActiveSectionCount;` _[#if SHADER_PRINT_HAIR_SKIN_CACHE]_
  - L2921 _member_ `uint TotalSectionCount;` _[#if SHADER_PRINT_HAIR_SKIN_CACHE]_
  - L2922 _member_ `uint LOD;` _[#if SHADER_PRINT_HAIR_SKIN_CACHE]_
  - L2923 _member_ `uint Pad;` _[#if SHADER_PRINT_HAIR_SKIN_CACHE]_
- L1884-1888 _struct_ **`FTangentDesc`** `struct FTangentDesc` _[#if SHADER_TANGENT]_
  - L1886 _member_ `float3 Tangent;` _[#if SHADER_TANGENT]_
  - L1887 _member_ `uint Type;` _[#if SHADER_TANGENT]_
- L2501-2508 _struct_ **`FInfo`** `struct FInfo` _[#if SHADER_PRINT_MEMORY]_
  - L2503 _member_ `uint4 Data0;` _[#if SHADER_PRINT_MEMORY]_
  - L2504 _member_ `uint4 Data1;` _[#if SHADER_PRINT_MEMORY]_
  - L2505 _member_ `uint4 Data2;` _[#if SHADER_PRINT_MEMORY]_
  - L2506 _member_ `uint4 Data3;` _[#if SHADER_PRINT_MEMORY]_
  - L2507 _member_ `uint4 Data4;` _[#if SHADER_PRINT_MEMORY]_
- L2537-2548 _struct_ **`FComponent`** `struct FComponent` _[#if SHADER_PRINT_MEMORY]_
  - L2539 _member_ `uint GroupIndex;` _[#if SHADER_PRINT_MEMORY]_
  - L2540 _member_ `uint GroupCount;` _[#if SHADER_PRINT_MEMORY]_
  - L2541 _member_ `uint RestCurve;` _[#if SHADER_PRINT_MEMORY]_
  - L2542 _member_ `uint ActiveCurve;` _[#if SHADER_PRINT_MEMORY]_
  - L2544 _member_ `uint GPU_Guides;` _[#if SHADER_PRINT_MEMORY]_
  - L2545 _member_ `uint GPU_Strands;` _[#if SHADER_PRINT_MEMORY]_
  - L2546 _member_ `uint GPU_Cards;` _[#if SHADER_PRINT_MEMORY]_
  - L2547 _member_ `uint GPU_Meshes;` _[#if SHADER_PRINT_MEMORY]_
- L2568-2594 _struct_ **`FGroom`** `struct FGroom` _[#if SHADER_PRINT_MEMORY]_
  - L2570 _member_ `uint GroupIndex;` _[#if SHADER_PRINT_MEMORY]_
  - L2571 _member_ `uint GroupCount;` _[#if SHADER_PRINT_MEMORY]_
  - L2572 _member_ `uint RestCurve;` _[#if SHADER_PRINT_MEMORY]_
  - L2573 _member_ `uint ActiveCurve;` _[#if SHADER_PRINT_MEMORY]_
  - L2575 _member_ `uint CPU_Guides;` _[#if SHADER_PRINT_MEMORY]_
  - L2576 _member_ `uint CPU_Strands;` _[#if SHADER_PRINT_MEMORY]_
  - L2577 _member_ `uint CPU_Cards;` _[#if SHADER_PRINT_MEMORY]_
  - L2578 _member_ `uint CPU_Meshes;` _[#if SHADER_PRINT_MEMORY]_
  - L2580 _member_ `uint GPU_Guides;` _[#if SHADER_PRINT_MEMORY]_
  - L2581 _member_ `uint GPU_Strands;` _[#if SHADER_PRINT_MEMORY]_
  - L2582 _member_ `uint GPU_Cards;` _[#if SHADER_PRINT_MEMORY]_
  - L2583 _member_ `uint GPU_Meshes;` _[#if SHADER_PRINT_MEMORY]_
  - L2585 _member_ `uint GPU_Rest;` _[#if SHADER_PRINT_MEMORY]_
  - L2586 _member_ `uint GPU_Interpolation;` _[#if SHADER_PRINT_MEMORY]_
  - L2587 _member_ `uint GPU_Cluster;` _[#if SHADER_PRINT_MEMORY]_
  - L2588 _member_ `uint GPU_Raytracing;` _[#if SHADER_PRINT_MEMORY]_
  - L2590 _member_ `uint Curve_Rest;` _[#if SHADER_PRINT_MEMORY]_
  - L2591 _member_ `uint Curve_Interpolation;` _[#if SHADER_PRINT_MEMORY]_
  - L2592 _member_ `uint Curve_Cluster;` _[#if SHADER_PRINT_MEMORY]_
  - L2593 _member_ `uint Curve_Raytracing;` _[#if SHADER_PRINT_MEMORY]_
- L2629-2645 _struct_ **`FBinding`** `struct FBinding` _[#if SHADER_PRINT_MEMORY]_
  - L2631 _member_ `uint GroupIndex;` _[#if SHADER_PRINT_MEMORY]_
  - L2632 _member_ `uint GroupCount;` _[#if SHADER_PRINT_MEMORY]_
  - L2633 _member_ `uint RestCurve;` _[#if SHADER_PRINT_MEMORY]_
  - L2634 _member_ `uint ActiveCurve;` _[#if SHADER_PRINT_MEMORY]_
  - L2636 _member_ `uint CPU_Guides;` _[#if SHADER_PRINT_MEMORY]_
  - L2637 _member_ `uint CPU_Strands;` _[#if SHADER_PRINT_MEMORY]_
  - L2638 _member_ `uint CPU_Cards;` _[#if SHADER_PRINT_MEMORY]_
  - L2639 _member_ `uint CPU_Meshes;` _[#if SHADER_PRINT_MEMORY]_
  - L2641 _member_ `uint GPU_Guides;` _[#if SHADER_PRINT_MEMORY]_
  - L2642 _member_ `uint GPU_Strands;` _[#if SHADER_PRINT_MEMORY]_
  - L2643 _member_ `uint GPU_Cards;` _[#if SHADER_PRINT_MEMORY]_
  - L2644 _member_ `uint GPU_Meshes;` _[#if SHADER_PRINT_MEMORY]_
- L2914-2924 _struct_ **`FInstanceInfo`** `struct FInstanceInfo` _[#if SHADER_PRINT_HAIR_SKIN_CACHE]_
  - L1479 _member_ `uint GroupIndex;` _[#if SHADER_PRINT_INSTANCE]_
  - L1480 _member_ `uint GroupCount;` _[#if SHADER_PRINT_INSTANCE]_
  - L1481 _member_ `uint LODCount;` _[#if SHADER_PRINT_INSTANCE]_
  - L1482 _member_ `uint GeometryType;` _[#if SHADER_PRINT_INSTANCE]_
  - L1483 _member_ `uint BindingType;` _[#if SHADER_PRINT_INSTANCE]_
  - L1484 _member_ `bool bHasSim;` _[#if SHADER_PRINT_INSTANCE]_
  - L1485 _member_ `bool bHasRBF;` _[#if SHADER_PRINT_INSTANCE]_
  - L1486 _member_ `bool bHasRTGeom;` _[#if SHADER_PRINT_INSTANCE]_
  - L1487 _member_ `float LOD;` _[#if SHADER_PRINT_INSTANCE]_
  - L1488 _member_ `float ClipValue;` _[#if SHADER_PRINT_INSTANCE]_
  - L1491 _member_ `uint StrandsCount;` — Strands data _[#if SHADER_PRINT_INSTANCE]_
  - L1492 _member_ `uint VertexCount;` _[#if SHADER_PRINT_INSTANCE]_
  - L1493 _member_ `float ScreenSize;` _[#if SHADER_PRINT_INSTANCE]_
  - L1494 _member_ `uint ActivePointCount;` _[#if SHADER_PRINT_INSTANCE]_
  - L1495 _member_ `uint ActiveCurveCount;` _[#if SHADER_PRINT_INSTANCE]_
  - L1496 _member_ `uint Attributes;` _[#if SHADER_PRINT_INSTANCE]_
  - L1497 _member_ `float Radius;` _[#if SHADER_PRINT_INSTANCE]_
  - L1498 _member_ `float Density;` _[#if SHADER_PRINT_INSTANCE]_
  - L1499 _member_ `float TipScale;` _[#if SHADER_PRINT_INSTANCE]_
  - L1500 _member_ `float RootScale;` _[#if SHADER_PRINT_INSTANCE]_
  - L1501 _member_ `float Length;` _[#if SHADER_PRINT_INSTANCE]_
  - L1502 _member_ `float LengthScale;` _[#if SHADER_PRINT_INSTANCE]_
  - L1503 _member_ `float CoverageScale;` _[#if SHADER_PRINT_INSTANCE]_
  - L1504 _member_ `bool Voxel;` _[#if SHADER_PRINT_INSTANCE]_
  - L1505 _member_ `bool CacheRen;` _[#if SHADER_PRINT_INSTANCE]_
  - L1506 _member_ `bool CacheSim;` _[#if SHADER_PRINT_INSTANCE]_
  - L1507 _member_ `bool bHasLODSwitched;` _[#if SHADER_PRINT_INSTANCE]_
  - L1508 _member_ `bool bAutoLOD;` _[#if SHADER_PRINT_INSTANCE]_
  - L1509 _member_ `bool bCurveRemapping;` _[#if SHADER_PRINT_INSTANCE]_
  - L1510 _member_ `bool bPointRemapping;` _[#if SHADER_PRINT_INSTANCE]_
  - L1511 _member_ `uint Flags;` _[#if SHADER_PRINT_INSTANCE]_
  - L1514 _member_ `uint UniqueTriangle;` — Binding _[#if SHADER_PRINT_INSTANCE]_
  - L1515 _member_ `uint UniqueSection;` _[#if SHADER_PRINT_INSTANCE]_
  - L1516 _member_ `uint RootCount;` _[#if SHADER_PRINT_INSTANCE]_
  - L1517 _member_ `uint ControlPointCount;` _[#if SHADER_PRINT_INSTANCE]_
  - L1519 _member_ `uint bIsVisibleInPrimaryView;` _[#if SHADER_PRINT_INSTANCE]_
  - L1520 _member_ `uint bIsVisibleInShadowView;` _[#if SHADER_PRINT_INSTANCE]_
  - L2916 _member_ `uint InstanceIndex;` _[#if SHADER_PRINT_HAIR_SKIN_CACHE]_
  - L2917 _member_ `uint GeometryType;` _[#if SHADER_PRINT_HAIR_SKIN_CACHE]_
  - L2918 _member_ `uint CacheType;` _[#if SHADER_PRINT_HAIR_SKIN_CACHE]_
  - L2919 _member_ `uint InstanceCount;` _[#if SHADER_PRINT_HAIR_SKIN_CACHE]_
  - L2920 _member_ `uint ActiveSectionCount;` _[#if SHADER_PRINT_HAIR_SKIN_CACHE]_
  - L2921 _member_ `uint TotalSectionCount;` _[#if SHADER_PRINT_HAIR_SKIN_CACHE]_
  - L2922 _member_ `uint LOD;` _[#if SHADER_PRINT_HAIR_SKIN_CACHE]_
  - L2923 _member_ `uint Pad;` _[#if SHADER_PRINT_HAIR_SKIN_CACHE]_

#### Global resources (textures / buffers / samplers) (56)

- L107 _resource_ `Texture2D<uint2> DepthStencilTexture;` _[#if SHADER_DEBUG_MODE]_
- L108 _resource_ `SamplerState LinearSampler;` _[#if SHADER_DEBUG_MODE]_
- L260 _resource_ `SamplerState LinearSampler;` _[#if SHADER_CVS]_
- L261 _resource_ `Texture2D<float> DepthTexture;` _[#if SHADER_CVS]_
- L262 _resource_ `RWTexture2D<float4> ColorTexture;` _[#if SHADER_CVS]_
- L379 _resource_ `Buffer<uint> RootBarycentricBuffer;` _[#if SHADER_MESH_PROJECTION_HAIR && PERMUTATION_INPUT_TYPE == INPUT_ROOTS]_
- L380 _resource_ `Buffer<float4> RestPositionBuffer;` _[#if SHADER_MESH_PROJECTION_HAIR && PERMUTATION_INPUT_TYPE == INPUT_ROOTS]_
- L381 _resource_ `Buffer<float4> DeformedPositionBuffer;` _[#if SHADER_MESH_PROJECTION_HAIR && PERMUTATION_INPUT_TYPE == INPUT_ROOTS]_
- L382 _resource_ `Buffer<uint> RootToUniqueTriangleIndexBuffer;` _[#if SHADER_MESH_PROJECTION_HAIR && PERMUTATION_INPUT_TYPE == INPUT_ROOTS]_
- L386 _resource_ `StructuredBuffer<float4> RestSamplePositionsBuffer;` _[#if SHADER_MESH_PROJECTION_HAIR && PERMUTATION_INPUT_TYPE == INPUT_SAMPLES]_
- L387 _resource_ `StructuredBuffer<float4> DeformedSamplePositionsBuffer;` _[#if SHADER_MESH_PROJECTION_HAIR && PERMUTATION_INPUT_TYPE == INPUT_SAMPLES]_
- L390 _resource_ `StructuredBuffer<float4> RestPositionOffset;` _[#if SHADER_MESH_PROJECTION_HAIR]_
- L391 _resource_ `StructuredBuffer<float4> DeformedPositionOffset;` _[#if SHADER_MESH_PROJECTION_HAIR]_
- L769 _resource_ `Texture2D<uint> PPLLCounter;` _[#if SHADER_PPLL_DEBUG]_
- L770 _resource_ `Texture2D<uint> PPLLNodeIndex;` _[#if SHADER_PPLL_DEBUG]_
- L771 _resource_ `StructuredBuffer<FPackedHairVisPPLL> PPLLNodeData;` _[#if SHADER_PPLL_DEBUG]_
- L773 _resource_ `RWTexture2D<float4> SceneColorTextureUAV;` _[#if SHADER_PPLL_DEBUG]_
- L868 _resource_ `Texture2D<float> DeepShadowDepthTexture;` _[#if SHADER_VISUALIZEDOM]_
- L869 _resource_ `Texture2D<float4> DeepShadowLayerTexture;` _[#if SHADER_VISUALIZEDOM]_
- L871 _resource_ `SamplerState LinearSampler;` _[#if SHADER_VISUALIZEDOM]_
- L992 _resource_ `Buffer<int> MacroGroupAABBBuffer;` _[#if SHADER_DOMINFO]_
- L993 _resource_ `StructuredBuffer<FDeepShadowViewInfo> ShadowViewInfoBuffer;` _[#if SHADER_DOMINFO]_
- L1114 _resource_ `Buffer<uint> HairInstanceDataBuffer;` _[#if SHADER_PRINT]_
- L1115 _resource_ `Buffer<int> InstanceAABBBuffer;` _[#if SHADER_PRINT]_
- L1117 _resource_ `Texture2D<float> HairCountTexture;` _[#if SHADER_PRINT]_
- L1118 _resource_ `Texture2D<uint> HairCountUintTexture;` _[#if SHADER_PRINT]_
- L1120 _resource_ `Texture2D<uint2> StencilTexture;` _[#if SHADER_PRINT]_
- L1121 _resource_ `SamplerState LinearSampler;` _[#if SHADER_PRINT]_
- L1122 _resource_ `Buffer<uint> HairVisibilityIndirectArgsBuffer;` _[#if SHADER_PRINT]_
- L1124 _resource_ `Buffer<int> HairMacroGroupAABBBuffer;` _[#if SHADER_PRINT]_
- L1125 _resource_ `Buffer<int> HairMacroGroupVoxelAlignedAABBBuffer;` _[#if SHADER_PRINT]_
- L1470 _resource_ `Buffer<uint> Infos;` _[#if SHADER_PRINT_INSTANCE]_
- L1471 _resource_ `Buffer<int> InstanceAABB;` _[#if SHADER_PRINT_INSTANCE]_
- L1877 _resource_ `RWTexture2D<float4> OutputTexture;` _[#if SHADER_TANGENT]_
- L2078 _resource_ `Texture2D<float4> AtlasTexture;` _[#if SHADER_CARDS_ATLAS]_
- L2079 _resource_ `RWTexture2D<float4> OutputTexture;` _[#if SHADER_CARDS_ATLAS]_
- L2080 _resource_ `SamplerState LinearSampler;` _[#if SHADER_CARDS_ATLAS]_
- L2151 _resource_ `ByteAddressBuffer RenRestPosition;` _[#if SHADER_CARDS_GUIDE]_
- L2152 _resource_ `ByteAddressBuffer RenDeformedPosition;` _[#if SHADER_CARDS_GUIDE]_
- L2153 _resource_ `StructuredBuffer<float4> RenDeformedOffset;` _[#if SHADER_CARDS_GUIDE]_
- L2155 _resource_ `ByteAddressBuffer SimRestPosition;` _[#if SHADER_CARDS_GUIDE]_
- L2156 _resource_ `ByteAddressBuffer SimDeformedPosition;` _[#if SHADER_CARDS_GUIDE]_
- L2157 _resource_ `StructuredBuffer<float4> SimDeformedOffset;` _[#if SHADER_CARDS_GUIDE]_
- L2232 _resource_ `Buffer<uint> Voxel_DensityBuffer;` _[#if SHADER_CARDS_DIRECTION_OCCLUSION]_
- L2233 _resource_ `RWBuffer<uint> OutBuffer;` _[#if SHADER_CARDS_DIRECTION_OCCLUSION]_
- L2353 _resource_ `Buffer<float> InstanceBoundInLightSpace;` _[#if SHADER_SHADOW_CULLING]_
- L2354 _resource_ `Buffer<float> InstanceBoundInWorldSpace;` _[#if SHADER_SHADOW_CULLING]_
- L2355 _resource_ `Buffer<uint> InstanceIntersection;` _[#if SHADER_SHADOW_CULLING]_
- L2423 _resource_ `Texture2D<uint> NodeIndexTexture;` _[#if SHADER_ATTRIBUTE_DEBUG]_
- L2424 _resource_ `StructuredBuffer<FPackedHairVis> NodeVisBuffer;` _[#if SHADER_ATTRIBUTE_DEBUG]_
- L2497 _resource_ `Buffer<uint> ComponentBuffer;` _[#if SHADER_PRINT_MEMORY]_
- L2498 _resource_ `Buffer<uint> GroomBuffer;` _[#if SHADER_PRINT_MEMORY]_
- L2499 _resource_ `Buffer<uint> BindingBuffer;` _[#if SHADER_PRINT_MEMORY]_
- L2851 _resource_ `Buffer<int> GroupAABBBuffer;` _[#if defined(SHADER_CLUSTERAABB)]_
- L2852 _resource_ `Buffer<int> ClusterAABBBuffer;` _[#if defined(SHADER_CLUSTERAABB)]_
- L2910 _resource_ `Buffer<uint> Infos;` _[#if SHADER_PRINT_HAIR_SKIN_CACHE]_

#### Global parameters (uniforms) (102)

- L102 _parameter_ `float2 OutputResolution;` _[#if SHADER_DEBUG_MODE]_
- L103 _parameter_ `uint FastResolveMask;` _[#if SHADER_DEBUG_MODE]_
- L104 _parameter_ `uint DebugMode;` _[#if SHADER_DEBUG_MODE]_
- L105 _parameter_ `int SampleIndex;` _[#if SHADER_DEBUG_MODE]_
- L255 _parameter_ `float4x4 LocalToWorld;` _[#if SHADER_CVS]_
- L256 _parameter_ `uint MaxVertexCount;` _[#if SHADER_CVS]_
- L257 _parameter_ `uint InstanceIt;` _[#if SHADER_CVS]_
- L258 _parameter_ `float3 GroupColor;` _[#if SHADER_CVS]_
- L357 _parameter_ `uint bSimPass;` _[#if SHADER_MESH_PROJECTION_HAIR]_
- L358 _parameter_ `uint bRestPass;` _[#if SHADER_MESH_PROJECTION_HAIR]_
- L359 _parameter_ `uint DrawIndex;` _[#if SHADER_MESH_PROJECTION_HAIR]_
- L360 _parameter_ `uint MaxUniqueSection;` _[#if SHADER_MESH_PROJECTION_HAIR]_
- L361 _parameter_ `uint MaxUniqueTriangleCount;` _[#if SHADER_MESH_PROJECTION_HAIR]_
- L362 _parameter_ `uint MaxRootCount;` _[#if SHADER_MESH_PROJECTION_HAIR]_
- L363 _parameter_ `float4x4 RootLocalToWorld;` _[#if SHADER_MESH_PROJECTION_HAIR]_
- L364 _parameter_ `uint DeformedFrameEnable;` _[#if SHADER_MESH_PROJECTION_HAIR]_
- L366 _parameter_ `uint bOverride;` _[#if SHADER_MESH_PROJECTION_HAIR]_
- L367 _parameter_ `uint Render_HairRestTriangles;` _[#if SHADER_MESH_PROJECTION_HAIR]_
- L368 _parameter_ `uint Render_HairRestFrames;` _[#if SHADER_MESH_PROJECTION_HAIR]_
- L369 _parameter_ `uint Render_HairDeformedTriangles;` _[#if SHADER_MESH_PROJECTION_HAIR]_
- L370 _parameter_ `uint Render_HairDeformedFrames;` _[#if SHADER_MESH_PROJECTION_HAIR]_
- L371 _parameter_ `uint Sim_HairRestTriangles;` _[#if SHADER_MESH_PROJECTION_HAIR]_
- L372 _parameter_ `uint Sim_HairRestFrames;` _[#if SHADER_MESH_PROJECTION_HAIR]_
- L373 _parameter_ `uint Sim_HairRestSamples;` _[#if SHADER_MESH_PROJECTION_HAIR]_
- L374 _parameter_ `uint Sim_HairDeformedTriangles;` _[#if SHADER_MESH_PROJECTION_HAIR]_
- L375 _parameter_ `uint Sim_HairDeformedFrames;` _[#if SHADER_MESH_PROJECTION_HAIR]_
- L376 _parameter_ `uint Sim_HairDeformedSamples;` _[#if SHADER_MESH_PROJECTION_HAIR]_
- L766 _parameter_ `float PPLLMeanListElementCountPerPixel;` _[#if SHADER_PPLL_DEBUG]_
- L767 _parameter_ `float PPLLMaxTotalListElementCount;` _[#if SHADER_PPLL_DEBUG]_
- L862 _parameter_ `float DomScale;` _[#if SHADER_VISUALIZEDOM]_
- L863 _parameter_ `float2 OutputResolution;` _[#if SHADER_VISUALIZEDOM]_
- L864 _parameter_ `float2 InvOutputResolution;` _[#if SHADER_VISUALIZEDOM]_
- L866 _parameter_ `int4 HairViewRect;` _[#if SHADER_VISUALIZEDOM]_
- L986 _parameter_ `uint AllocatedSlotCount;` _[#if SHADER_DOMINFO]_
- L987 _parameter_ `uint MacroGroupCount;` _[#if SHADER_DOMINFO]_
- L988 _parameter_ `uint bViewRectOptimizeEnabled;` _[#if SHADER_DOMINFO]_
- L989 _parameter_ `uint bVoxelizationEnabled;` _[#if SHADER_DOMINFO]_
- L990 _parameter_ `int2 AtlasResolution;` _[#if SHADER_DOMINFO]_
- L1105 _parameter_ `float ResolutionScale;` _[#if SHADER_PRINT]_
- L1106 _parameter_ `int2 MaxResolution;` _[#if SHADER_PRINT]_
- L1107 _parameter_ `uint FastResolveMask;` _[#if SHADER_PRINT]_
- L1108 _parameter_ `uint HairMacroGroupCount;` _[#if SHADER_PRINT]_
- L1109 _parameter_ `uint2 GroupSize;` _[#if SHADER_PRINT]_
- L1110 _parameter_ `uint HairVisibilityNodeGroupSize;` _[#if SHADER_PRINT]_
- L1111 _parameter_ `uint AllocatedSampleCount;` _[#if SHADER_PRINT]_
- L1112 _parameter_ `uint HairInstanceCount;` _[#if SHADER_PRINT]_
- L1462 _parameter_ `uint InstanceRegisteredIndex;` _[#if SHADER_PRINT_INSTANCE]_
- L1463 _parameter_ `int2 MaxResolution;` _[#if SHADER_PRINT_INSTANCE]_
- L1464 _parameter_ `uint InstanceCount;` _[#if SHADER_PRINT_INSTANCE]_
- L1465 _parameter_ `uint InstanceCount_StrandsPrimaryView;` _[#if SHADER_PRINT_INSTANCE]_
- L1466 _parameter_ `uint InstanceCount_StrandsShadowView;` _[#if SHADER_PRINT_INSTANCE]_
- L1467 _parameter_ `uint InstanceCount_CardsOrMeshesPrimaryView;` _[#if SHADER_PRINT_INSTANCE]_
- L1468 _parameter_ `uint InstanceCount_CardsOrMeshesShadowView;` _[#if SHADER_PRINT_INSTANCE]_
- L1472 _parameter_ `float4 InstanceScreenSphereBound;` _[#if SHADER_PRINT_INSTANCE]_
- L1874 _parameter_ `uint TileSize;` _[#if SHADER_TANGENT]_
- L1875 _parameter_ `int2 TileCount;` _[#if SHADER_TANGENT]_
- L1876 _parameter_ `float2 OutputResolution;` _[#if SHADER_TANGENT]_
- L2005 _parameter_ `int2 MaxResolution;` _[#if SHADER_LOD_INFO]_
- L2006 _parameter_ `uint GroupIndex;` _[#if SHADER_LOD_INFO]_
- L2007 _parameter_ `uint GeometryType;` _[#if SHADER_LOD_INFO]_
- L2008 _parameter_ `uint CurveCount;` _[#if SHADER_LOD_INFO]_
- L2009 _parameter_ `uint PointCount;` _[#if SHADER_LOD_INFO]_
- L2010 _parameter_ `float CoverageScale;` _[#if SHADER_LOD_INFO]_
- L2011 _parameter_ `float LOD;` _[#if SHADER_LOD_INFO]_
- L2012 _parameter_ `float ScreenSize;` _[#if SHADER_LOD_INFO]_
- L2013 _parameter_ `float3 GroupColor;` _[#if SHADER_LOD_INFO]_
- L2074 _parameter_ `int2 OutputResolution;` _[#if SHADER_CARDS_ATLAS]_
- L2075 _parameter_ `int2 AtlasResolution;` _[#if SHADER_CARDS_ATLAS]_
- L2076 _parameter_ `int DebugMode;` _[#if SHADER_CARDS_ATLAS]_
- L2140 _parameter_ `uint InstanceRegisteredIndex;` _[#if SHADER_CARDS_GUIDE]_
- L2141 _parameter_ `uint CardLODIndex;` _[#if SHADER_CARDS_GUIDE]_
- L2143 _parameter_ `uint RenVertexCount;` _[#if SHADER_CARDS_GUIDE]_
- L2144 _parameter_ `float3 RenRestOffset;` _[#if SHADER_CARDS_GUIDE]_
- L2146 _parameter_ `uint SimVertexCount;` _[#if SHADER_CARDS_GUIDE]_
- L2147 _parameter_ `float3 SimRestOffset;` _[#if SHADER_CARDS_GUIDE]_
- L2149 _parameter_ `float4x4 LocalToWorld;` _[#if SHADER_CARDS_GUIDE]_
- L2159 _parameter_ `int DebugMode;` _[#if SHADER_CARDS_GUIDE]_
- L2228 _parameter_ `int3 Voxel_Resolution;` _[#if SHADER_CARDS_DIRECTION_OCCLUSION]_
- L2229 _parameter_ `float Voxel_VoxelSize;` _[#if SHADER_CARDS_DIRECTION_OCCLUSION]_
- L2230 _parameter_ `float3 Voxel_MinBound;` _[#if SHADER_CARDS_DIRECTION_OCCLUSION]_
- L2231 _parameter_ `float3 Voxel_MaxBound;` _[#if SHADER_CARDS_DIRECTION_OCCLUSION]_
- L2357 _parameter_ `uint InstanceCount;` _[#if SHADER_SHADOW_CULLING]_
- L2359 _parameter_ `float3 LightCenter;` _[#if SHADER_SHADOW_CULLING]_
- L2360 _parameter_ `float3 LightExtent;` _[#if SHADER_SHADOW_CULLING]_
- L2362 _parameter_ `float4x4 LightToWorld;` _[#if SHADER_SHADOW_CULLING]_
- L2364 _parameter_ `float4x4 ViewWorldToProj;` _[#if SHADER_SHADOW_CULLING]_
- L2365 _parameter_ `float4x4 ViewProjToWorld;` _[#if SHADER_SHADOW_CULLING]_
- L2422 _parameter_ `uint MaterialId;` _[#if SHADER_ATTRIBUTE_DEBUG]_
- L2493 _parameter_ `uint ComponentCount;` _[#if SHADER_PRINT_MEMORY]_
- L2494 _parameter_ `uint GroomCount;` _[#if SHADER_PRINT_MEMORY]_
- L2495 _parameter_ `uint BindingCount;` _[#if SHADER_PRINT_MEMORY]_
- L2843 _parameter_ `uint InstanceRegisteredIndex;` _[#if defined(SHADER_CLUSTERAABB)]_
- L2844 _parameter_ `uint ClusterOffset;` _[#if defined(SHADER_CLUSTERAABB)]_
- L2845 _parameter_ `uint ClusterCount;` _[#if defined(SHADER_CLUSTERAABB)]_
- L2846 _parameter_ `uint HairGroupId;` _[#if defined(SHADER_CLUSTERAABB)]_
- L2847 _parameter_ `uint PointCount;` _[#if defined(SHADER_CLUSTERAABB)]_
- L2848 _parameter_ `uint CurveCount;` _[#if defined(SHADER_CLUSTERAABB)]_
- L2849 _parameter_ `uint bDrawAABB;` _[#if defined(SHADER_CLUSTERAABB)]_
- L2906 _parameter_ `uint HairSkinCacheEnable;` _[#if SHADER_PRINT_HAIR_SKIN_CACHE]_
- L2907 _parameter_ `uint GPUSkinCacheEnable;` _[#if SHADER_PRINT_HAIR_SKIN_CACHE]_
- L2908 _parameter_ `uint InstanceCount;` _[#if SHADER_PRINT_HAIR_SKIN_CACHE]_
- L2909 _parameter_ `uint UniqueMeshCount;` _[#if SHADER_PRINT_HAIR_SKIN_CACHE]_

#### Functions (32)

- L15 _function_ `float4 GetGPUSceneBoundColor()` — Shared color _[#if SHADER_PRINT_INSTANCE \|\| SHADER_PRINT \|\| SHADER_PRINT_MEMORY \|\| SHADER_CLUSTERAABB \|\| SHADER_DOMINFO \|\| SHADER_PRINT_HAIR_SKIN_CACHE]_
- L16 _function_ `float4 GetInstanceGroupScreenBoundColor()` _[#if SHADER_PRINT_INSTANCE \|\| SHADER_PRINT \|\| SHADER_PRINT_MEMORY \|\| SHADER_CLUSTERAABB \|\| SHADER_DOMINFO \|\| SHADER_PRINT_HAIR_SKIN_CACHE]_
- L18 _function_ `float4 GetGPUAABBInstanceGroupBoundColor()` _[#if SHADER_PRINT_INSTANCE \|\| SHADER_PRINT \|\| SHADER_PRINT_MEMORY \|\| SHADER_CLUSTERAABB \|\| SHADER_DOMINFO \|\| SHADER_PRINT_HAIR_SKIN_CACHE]_
- L19 _function_ `float4 GetGPUAABBMacroGroupBoundColor()` _[#if SHADER_PRINT_INSTANCE \|\| SHADER_PRINT \|\| SHADER_PRINT_MEMORY \|\| SHADER_CLUSTERAABB \|\| SHADER_DOMINFO \|\| SHADER_PRINT_HAIR_SKIN_CACHE]_
- L20 _function_ `float4 GetGPUAABBMacroGroupBoundVoxelAlignedColor()` _[#if SHADER_PRINT_INSTANCE \|\| SHADER_PRINT \|\| SHADER_PRINT_MEMORY \|\| SHADER_CLUSTERAABB \|\| SHADER_DOMINFO \|\| SHADER_PRINT_HAIR_SKIN_CACHE]_
- L23-39 _function_ `void PrintNumberAlignedRight(inout FShaderPrintContext Context, float Value, FFontColor InColor)` — Print float number in 0..1000 aligned on the right _[#if SHADER_PRINT_INSTANCE \|\| SHADER_PRINT \|\| SHADER_PRINT_MEMORY \|\| SHADER_CLUSTERAABB \|\| SHADER_DOMINFO \|\| SHADER_PRINT_HAIR_SKIN_CACHE]_
- L42-70 _function_ `void PrintLargeNumber(inout FShaderPrintContext Context, uint Value, FFontColor InColor)` — Print _[#if SHADER_PRINT_INSTANCE \|\| SHADER_PRINT \|\| SHADER_PRINT_MEMORY \|\| SHADER_CLUSTERAABB \|\| SHADER_DOMINFO \|\| SHADER_PRINT_HAIR_SKIN_CACHE]_
- L72-90 _function_ `void PrintPercentage(inout FShaderPrintContext Context, float Value, FFontColor InColor)` _[#if SHADER_PRINT_INSTANCE \|\| SHADER_PRINT \|\| SHADER_PRINT_MEMORY \|\| SHADER_CLUSTERAABB \|\| SHADER_DOMINFO \|\| SHADER_PRINT_HAIR_SKIN_CACHE]_
- L393-401 _function_ `void Move(inout FShaderPrintContext Ctx, uint2 InPos)` _[#if SHADER_MESH_PROJECTION_HAIR]_
- L403-408 _function_ `float2 ToScreenUV(float3 TWSPos)` _[#if SHADER_MESH_PROJECTION_HAIR]_
- L410-428 _function_ `float4 GetScreenMinMax(float3 WP0, float3 WP1, float3 WP2)` _[#if SHADER_MESH_PROJECTION_HAIR]_
- L430-433 _function_ `bool IsInRect(float4 MinMaxUV, float2 UV)` _[#if SHADER_MESH_PROJECTION_HAIR]_
- L775-779 _function_ `FFontColor GetOccupancyColor(float In)` _[#if SHADER_PPLL_DEBUG]_
- L873-879 _function_ `bool IsInsideRect(float4 Rect, float2 PixelPos, inout float2 LocalUV)` _[#if SHADER_VISUALIZEDOM]_
- L881-889 _function_ `bool IsOnBorder(float2 LocalUV, float4 Rect)` _[#if SHADER_VISUALIZEDOM]_
- L891-895 _function_ `float3 AddBorder(float2 LocalUV, float4 Rect)` _[#if SHADER_VISUALIZEDOM]_
- L1130-1134 _function_ `FFontColor GetOccupancyColor(float In)` _[#if SHADER_PRINT]_
- L1136-1158 _function_ `void DrawInstanceAABB(uint PrimitiveId)` _[#if SHADER_PRINT]_
- L1168-1181 _function_ `FData LoadInstanceData(uint InIndex)` _[#if SHADER_PRINT]_
- L1523-1604 _function_ `FInstanceInfo ReadInstanceInfo(uint Index)` _[#if SHADER_PRINT_INSTANCE]_
- L1606-1609 _function_ `bool HasAttribute(FInstanceInfo In, uint InAttributeIt)` _[#if SHADER_PRINT_INSTANCE]_
- L1890-1944 _function_ `FTangentDesc AddTangentPlot(uint2 PixelCoord, float2 UV)` _[#if SHADER_TANGENT]_
- L1946-1962 _function_ `void AddTangentText(float2 UV, float3 Tangent, uint TangentType)` _[#if SHADER_TANGENT]_
- L2317-2351 _function_ `void AddFrustumWS(float4x4 In, float4 InColor, bool bInv)` _[#if SHADER_SHADOW_CULLING]_
- L2510-2535 _function_ `FInfo ReadInfo(uint Index, Buffer<uint> InBuffer)` _[#if SHADER_PRINT_MEMORY]_
- L2550-2566 _function_ `FComponent GetComponent(uint Index)` _[#if SHADER_PRINT_MEMORY]_
- L2596-2627 _function_ `FGroom GetGroom(uint Index)` _[#if SHADER_PRINT_MEMORY]_
- L2647-2667 _function_ `FBinding GetBinding(uint Index)` _[#if SHADER_PRINT_MEMORY]_
- L2669-2674 _function_ `void PrintGroup(inout FShaderPrintContext Ctx, uint GroupIndex, uint GroupCount)` _[#if SHADER_PRINT_MEMORY]_
- L2676-2680 _function_ `FFontColor GetOccupancyColor(float In)` _[#if SHADER_PRINT_MEMORY]_
- L2682-2689 _function_ `void PrintCurve(inout FShaderPrintContext Ctx, uint ActiveCurve, uint RestCurve)` _[#if SHADER_PRINT_MEMORY]_
- L2926-2952 _function_ `FInstanceInfo ReadInstanceInfo(uint Index)` _[#if SHADER_PRINT_HAIR_SKIN_CACHE]_

#### Top-level macro invocations (7)

- L1474 _macro_call_ `FSTRINGS(InstanceNames)` _[#if SHADER_PRINT_INSTANCE]_
- L1475 _macro_call_ `FSTRINGS(AttributeNames)` _[#if SHADER_PRINT_INSTANCE]_
- L2416 _macro_call_ `HAIR_STRANDS_INSTANCE_PARAMETERS(HairInstance)` _[#if SHADER_ATTRIBUTE_DEBUG]_
- L2489 _macro_call_ `FSTRINGS(GroomNames)` _[#if SHADER_PRINT_MEMORY]_
- L2490 _macro_call_ `FSTRINGS(BindingNames)` _[#if SHADER_PRINT_MEMORY]_
- L2491 _macro_call_ `FSTRINGS(ComponentNames)` _[#if SHADER_PRINT_MEMORY]_
- L2912 _macro_call_ `FSTRINGS(UniqueMeshNames)` _[#if SHADER_PRINT_HAIR_SKIN_CACHE]_

### `Shaders/Private/HairStrands/HairStrandsDebugCommonStruct.ush` (Private)

- lines: 21; parse: all-branches
- L3 #pragma `once`

#### Structs / classes (2)

- L5-13 _struct_ **`FDebugShadingInfo`** `struct FDebugShadingInfo`
  - L7 _member_ `float3 BaseColor;`
  - L8 _member_ `float Roughness;`
  - L9 _member_ `float3 T;`
  - L10 _member_ `uint SampleCount;`
  - L11 _member_ `float3 V;`
  - L12 _member_ `uint SampleOffset;`
- L15-21 _struct_ **`FDebugSample`** `struct FDebugSample`
  - L17 _member_ `float3 Direction;`
  - L18 _member_ `float Pdf;`
  - L19 _member_ `float3 Weight;`
  - L20 _member_ `float Pad;`

### `Shaders/Private/HairStrands/HairStrandsDeepShadowAllocation.usf` (Private)

- lines: 338; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../Matrices.ush`, L5 `HairStrandsDeepShadowCommonStruct.ush`, L6 `HairStrandsAABBCommon.ush`

#### Macros (#define, 1)

- L66 `#define NUM_ATLAS_TILE_BINS 6` _[#if SHADER_ALLOCATE]_

#### Entry points (1)

- L288-336 _entry_ `[numthreads(MAX_SLOT_COUNT, 1, 1)] void CreateViewInfo(uint2 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FDeepShadowCreateViewInfoCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDeepShadow.cpp:210) — This code assume we have less than 32 macro group (which fit into a single CU/SM) _[#if SHADER_ALLOCATE]_

#### Structs / classes (1)

- L39-45 _struct_ **`FLightData`** `struct FLightData` — Mirror of FLightData in HairStrands/HairStrandsDeepShadow.cpp _[#if SHADER_ALLOCATE]_
  - L41 _member_ `float3 LightDirection;` _[#if SHADER_ALLOCATE]_
  - L42 _member_ `uint MacroGroupId;` _[#if SHADER_ALLOCATE]_
  - L43 _member_ `float3 TranslatedLightPosition;` _[#if SHADER_ALLOCATE]_
  - L44 _member_ `uint bIsLightDirectional;` _[#if SHADER_ALLOCATE]_

#### Global resources (textures / buffers / samplers) (3)

- L60 _resource_ `StructuredBuffer<FLightData> LightDataBuffer;` _[#if SHADER_ALLOCATE]_
- L61 _resource_ `Buffer<int> MacroGroupAABBBuffer;` _[#if SHADER_ALLOCATE]_
- L62 _resource_ `RWStructuredBuffer<FDeepShadowViewInfo> OutShadowViewInfoBuffer;` _[#if SHADER_ALLOCATE]_

#### Global parameters (uniforms) (10)

- L47 _parameter_ `float RasterizationScale;` _[#if SHADER_ALLOCATE]_
- L48 _parameter_ `float AABBScale;` _[#if SHADER_ALLOCATE]_
- L49 _parameter_ `float MaxHafFovInRad;` _[#if SHADER_ALLOCATE]_
- L51 _parameter_ `int2 SlotResolution;` _[#if SHADER_ALLOCATE]_
- L52 _parameter_ `uint SlotIndexCount;` _[#if SHADER_ALLOCATE]_
- L53 _parameter_ `uint MacroGroupCount;` _[#if SHADER_ALLOCATE]_
- L55 _parameter_ `uint2 AtlasResolution;` _[#if SHADER_ALLOCATE]_
- L56 _parameter_ `float2 AtlasTexelSize;` _[#if SHADER_ALLOCATE]_
- L57 _parameter_ `uint MinAtlasTileResolution;` _[#if SHADER_ALLOCATE]_
- L58 _parameter_ `uint MinAtlasTileResolutionLog2;` _[#if SHADER_ALLOCATE]_

#### groupshared (4)

- L67 _groupshared_ `groupshared uint AtlasTileBinElementCounts[NUM_ATLAS_TILE_BINS];` _[#if SHADER_ALLOCATE]_
- L68 _groupshared_ `groupshared uint AtlasTileBins[NUM_ATLAS_TILE_BINS][MAX_SLOT_COUNT];` _[#if SHADER_ALLOCATE]_
- L69 _groupshared_ `groupshared uint4 AtlasTileAllocations[MAX_SLOT_COUNT];` _[#if SHADER_ALLOCATE]_
- L70 _groupshared_ `groupshared uint AtlasTileDesiredResolutions[MAX_SLOT_COUNT];` _[#if SHADER_ALLOCATE]_

#### Functions (8)

- L16-34 _function_ `float4x4 ComputeTranslatedWorldToLight( const FHairAABB TranslatedAABB, const float3 LightDirection, const float3 TranslatedLightPosition, const bool bIsDirectional)` _[#if SHADER_ALLOCATE]_
- L72-75 _function_ `float DegreesToRadians(float InDeg)` _[#if SHADER_ALLOCATE]_
- L77-83 _function_ `float ComputeMinStrandRadiusAtDepth1(const int2 Resolution, const float InFOVInRad, const float InRasterizationScale)` _[#if SHADER_ALLOCATE]_
- L86-134 _function_ `void ComputeTranslatedWorldToLightClip( inout float4x4 OutTranslatedWorldToClipTransform, inout float OutMinStrandRadiusAtDepth1, inout float3 OutLightDirection, const FHairAABB TranslatedWorld_AABB, const FLightData LightData)` — This function is similar to the CPU version in HairStrandsDeepShadow.cpp _[#if SHADER_ALLOCATE]_
- L136-160 _function_ `float2 ComputeProjectedScreenSize(float4x4 TranslatedWorldToLightClipTransform)` _[#if SHADER_ALLOCATE]_
- L162-180 _function_ `void AddToAtlasTileBin(float2 ProjectedShadowSize, uint SlotIndex)` _[#if SHADER_ALLOCATE]_
- L182-240 _function_ `void AllocateAtlasTiles()` _[#if SHADER_ALLOCATE]_
- L242-285 _function_ `void ApplyAtlasTileScaleBias(float4x4 ShadowMatrix, uint SlotIndex, out float4x4 ModifiedTranslatedWorldToClip, out float4 AtlasScaleBias)` _[#if SHADER_ALLOCATE]_

### `Shaders/Private/HairStrands/HairStrandsDeepShadowCommon.ush` (Private)

- lines: 257; parse: all-branches
- includes: L4 `../ColorMap.ush`

#### Macros (#define, 1)

- L6 `#define DEBUG_MODE 0`
- L3 #pragma `once`

#### Functions (15)

- L10-13 _function_ `bool IsDepthCloser(float a, float b)`
- L15-18 _function_ `float ComputeDOMWeight(float DistanceToFrontDepth, float LayerDepth)`
- L20-28 _function_ `float4 ComputeDOMWeights(float DistanceToFrontDepth, float4 InLayerDepths)`
- L30-38 _function_ `float3 HairDebugColor(float DistanceToFrontDepth, float4 InLayerDepths)`
- L40-43 _function_ `float InterpolateCount(float DepthToFrontDepth, float Layer0Depth, float Layer1Depth)`
- L45-60 _function_ `float ComputeHairCount(float4 DomValue, float DistanceToFrontDepth, float4 InLayerDepths)`
- L62-65 _function_ `float GetDomDistanceToFrontDepth(float FrontDepth, float LightSpaceZ)`
- L67-70 _function_ `float GetDomDistanceToFrontDepthWithBias(float FrontDepth, float LightSpaceZ, float DepthBias)`
- L72-106 _function_ `float SampleDOM_PCF2x2( float3 LightSpacePosition, float DepthBias, const float4 InLayerDepths, Texture2D<float> FrontDepthTexture, Texture2D<float4> DomTexture)`
- L108-132 _function_ `float SampleDOM_PCF( float3 LightSpacePosition, float DepthBias, const float4 InLayerDepths, Texture2D<float> FrontDepthTexture, Texture2D<float4> DomTexture)`
- L136-145 _function_ `float2 ComputeJitteredSample(float2 Sample, float2 Jitter)` — Sample [-1,1] Jitter [0,1]
- L147-219 _function_ `float SampleDOM_PCSS( float3 LightSpacePosition, uint2 DeepShadowAtlasResolution, float DepthBias, float4 InLayerDepths, Texture2D<float> FrontDepthTexture, Texture2D<float4> DomTexture, float ApexAngleInDegree, float2 Jitter)`
- L221-227 _function_ `float3 ToLightPosition(float3 WorldPosition, float4x4 WorldToLightTransform)`
- L229-240 _function_ `float3 ComputeDomDebugColor( float3 WorldPosition, float4x4 WorldToLightTransform, float4 InLayerDepths, Texture2D<float> FrontDepthTexture, SamplerState LinearSampler)`
- L242-257 _function_ `float3 ComputeHairCountDebugColor( float3 WorldPosition, float4x4 WorldToLightTransform, float4 InLayerDepths, Texture2D<float> FrontDepthTexture, Texture2D<float4> DomTexture, SamplerState LinearSampler, float MaxHairCount)`

### `Shaders/Private/HairStrands/HairStrandsDeepShadowCommonStruct.ush` (Private)

- lines: 12; parse: all-branches
- L3 #pragma `once`

#### Structs / classes (1)

- L5-12 _struct_ **`FDeepShadowViewInfo`** `struct FDeepShadowViewInfo`
  - L7 _member_ `float4x4 TranslatedWorldToClipScaledBiased;` — Has the shadow atlas tile scale bias baked in
  - L8 _member_ `float4x4 TranslatedWorldToClip;`
  - L9 _member_ `float4 AtlasScaleBias;` — Scale/bias for transforming UV coordinates into the shadow atlas tile of this shadow view.
  - L10 _member_ `float3 ViewForward;`
  - L11 _member_ `float MinRadiusAtDepth1;`

### `Shaders/Private/HairStrands/HairStrandsDeepShadowMask.usf` (Private)

- lines: 565; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../DeferredShadingCommon.ush`, L5 `../MonteCarlo.ush`, L6 `HairStrandsVisibilityCommon.ush`, L7 `HairStrandsVoxelPageCommon.ush`, L8 `HairStrandsCommon.ush`, L9 `HairStrandsDeepShadowCommon.ush`, L10 `HairStrandsDeepTransmittanceCommon.ush`, L410 `HairStrandsVoxelPageTraversal.ush` [SHADER_SHADOWMASK_VOXEL && SHADER_SHADOWMASK_VOXEL], L414 `../BlueNoise.ush` [SHADER_SHADOWMASK_VOXEL]

#### Macros (#define, 10)

- L29 `#define KERNEL_TYPE_2x2 0`
- L30 `#define KERNEL_TYPE_4x4 1`
- L31 `#define KERNEL_TYPE_Gaussian8 2`
- L32 `#define KERNEL_TYPE_Gaussian16 3`
- L33 `#define KERNEL_TYPE_GaussianTransmission8 4`
- L84 `#define TILE_PIXEL_SIZE 8` _[#if SHADER_SHADOWMASK_DEEPSHADOW]_
- L85 `#define OPAQUE_PCF 1` _[#if SHADER_SHADOWMASK_DEEPSHADOW]_
- L408 `#define VOXEL_TRAVERSAL_DEBUG 0` _[#if SHADER_SHADOWMASK_VOXEL && SHADER_SHADOWMASK_VOXEL]_
- L409 `#define VOXEL_TRAVERSAL_TYPE VOXEL_TRAVERSAL_LINEAR_MIPMAP` _[#if SHADER_SHADOWMASK_VOXEL && SHADER_SHADOWMASK_VOXEL]_
- L413 `#define USE_BLUE_NOISE 1` _[#if SHADER_SHADOWMASK_VOXEL]_

#### Entry points (2)

- L332-399 _entry_ `void MainPS( FScreenVertexOutput Input, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FHairStrandsVoxelShadowMaskPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsTransmittance.cpp:489) — C++: `FHairStrandsDeepShadowMaskPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsTransmittance.cpp:649) _[#if SHADER_SHADOWMASK_DEEPSHADOW]_
- L459-563 _entry_ `void MainPS( FScreenVertexOutput Input, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FHairStrandsVoxelShadowMaskPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsTransmittance.cpp:489) — C++: `FHairStrandsDeepShadowMaskPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsTransmittance.cpp:649) _[#if SHADER_SHADOWMASK_VOXEL]_

#### Structs / classes (1)

- L87-97 _struct_ **`FHairSamplingSettings`** `struct FHairSamplingSettings` _[#if SHADER_SHADOWMASK_DEEPSHADOW]_
  - L89 _member_ `Texture2D<float>ShadowDepthTexture;` _[#if SHADER_SHADOWMASK_DEEPSHADOW]_
  - L90 _member_ `Texture2D<float4>ShadowDomTexture;` _[#if SHADER_SHADOWMASK_DEEPSHADOW]_
  - L91 _member_ `SamplerState ShadowDepthTextureSampler;` _[#if SHADER_SHADOWMASK_DEEPSHADOW]_
  - L92 _member_ `float2 ShadowAtlasInvResolution;` _[#if SHADER_SHADOWMASK_DEEPSHADOW]_
  - L93 _member_ `float2 ShadowAtlasResolution;` _[#if SHADER_SHADOWMASK_DEEPSHADOW]_
  - L94 _member_ `float2 ShadowSlotResolution;` _[#if SHADER_SHADOWMASK_DEEPSHADOW]_
  - L95 _member_ `float2 ShadowSlotOffset;` _[#if SHADER_SHADOWMASK_DEEPSHADOW]_
  - L96 _member_ `float SceneDepth;` — SceneDepth in lightspace. _[#if SHADER_SHADOWMASK_DEEPSHADOW]_

#### Global resources (textures / buffers / samplers) (7)

- L44 _resource_ `StructuredBuffer<FDeepShadowViewInfo> DeepShadow_ViewInfoBuffer;` _[#if SHADER_SHADOWMASK_DEEPSHADOW]_
- L45 _resource_ `StructuredBuffer<uint> DeepShadow_AtlasSlotIndexBuffer;` _[#if SHADER_SHADOWMASK_DEEPSHADOW]_
- L56 _resource_ `Texture2D<float> DeepShadow_FrontDepthTexture;` _[#if SHADER_SHADOWMASK_DEEPSHADOW]_
- L57 _resource_ `Texture2D<float4> DeepShadow_DomTexture;` _[#if SHADER_SHADOWMASK_DEEPSHADOW]_
- L59 _resource_ `SamplerState LinearSampler;` _[#if SHADER_SHADOWMASK_DEEPSHADOW]_
- L60 _resource_ `SamplerState ShadowSampler;` _[#if SHADER_SHADOWMASK_DEEPSHADOW]_
- L421 _resource_ `Texture2D<float4> RayMarchMaskTexture;` _[#if SHADER_SHADOWMASK_VOXEL]_

#### Global parameters (uniforms) (14)

- L47 _parameter_ `int2 DeepShadow_AtlasResolution;` _[#if SHADER_SHADOWMASK_DEEPSHADOW]_
- L48 _parameter_ `uint DeepShadow_KernelType;` _[#if SHADER_SHADOWMASK_DEEPSHADOW]_
- L49 _parameter_ `float DeepShadow_DepthBiasScale;` _[#if SHADER_SHADOWMASK_DEEPSHADOW]_
- L50 _parameter_ `float DeepShadow_DensityScale;` _[#if SHADER_SHADOWMASK_DEEPSHADOW]_
- L51 _parameter_ `float4 DeepShadow_LayerDepths;` _[#if SHADER_SHADOWMASK_DEEPSHADOW]_
- L52 _parameter_ `float FadeAlpha;` _[#if SHADER_SHADOWMASK_DEEPSHADOW]_
- L53 _parameter_ `uint EncodingType;` _[#if SHADER_SHADOWMASK_DEEPSHADOW]_
- L54 _parameter_ `uint EffectiveAtlasSlotCount;` _[#if SHADER_SHADOWMASK_DEEPSHADOW]_
- L415-417 _parameter_ `DEFINE_HAIR_BLUE_NOISE_JITTER_FUNCTION float4 Voxel_TranslatedLightPosition_LightDirection;` _[#if SHADER_SHADOWMASK_VOXEL]_
- L418 _parameter_ `uint Voxel_MacroGroupCount;` _[#if SHADER_SHADOWMASK_VOXEL]_
- L419 _parameter_ `uint Voxel_MacroGroupId;` _[#if SHADER_SHADOWMASK_VOXEL]_
- L420 _parameter_ `uint Voxel_RandomType;` _[#if SHADER_SHADOWMASK_VOXEL]_
- L422 _parameter_ `float FadeAlpha;` _[#if SHADER_SHADOWMASK_VOXEL]_
- L423 _parameter_ `uint EncodingType;` _[#if SHADER_SHADOWMASK_VOXEL]_

#### Functions (17)

- L12-24 _function_ `float4 WriteShadowMaskOutput(const float InFadedShadow, uint InEncodingType)`
- L35-39 _function_ `float3 GetTranslatedWorldPosition(float2 UV, float SceneDepth)`
- L66-76 _function_ `float4 ToLightPosition(float3 InTranslatedWorldPosition, uint InAtlasSlotIndex, out float4 AtlasScaleBias)` — Return the light space position of a world space. XY: UV of the shadow space Z: Normalized depth value in light clip space W: Positive if the position is valid, negative otherwise _[#if SHADER_SHADOWMASK_DEEPSHADOW]_
- L78-82 _function_ `bool IsCloser(float DepthA, float DepthB)` _[#if SHADER_SHADOWMASK_DEEPSHADOW]_
- L99-105 _function_ `void InternalFetchRowOfThree(float2 Sample00TexelCenter, float VerticalOffset, inout float3 Values0, FHairSamplingSettings Settings)` _[#if SHADER_SHADOWMASK_DEEPSHADOW]_
- L107-114 _function_ `void FetchRowOfFour(float2 Sample00TexelCenter, float VerticalOffset, inout float4 Values0, FHairSamplingSettings Settings)` _[#if SHADER_SHADOWMASK_DEEPSHADOW]_
- L116-131 _function_ `float InternalPCF2x2(float2 Fraction, float3 Values0, float3 Values1, float3 Values2)` _[#if SHADER_SHADOWMASK_DEEPSHADOW]_
- L133-155 _function_ `float InternalPCF3x3(float2 Fraction, float4 Values0, float4 Values1, float4 Values2, float4 Values3)` _[#if SHADER_SHADOWMASK_DEEPSHADOW]_
- L157-170 _function_ `float InternalManual2x2PCF(float2 ShadowPosition, FHairSamplingSettings Settings)` _[#if SHADER_SHADOWMASK_DEEPSHADOW]_
- L172-185 _function_ `float InternalManual4x4PCF(float2 ShadowPosition, FHairSamplingSettings Settings)` _[#if SHADER_SHADOWMASK_DEEPSHADOW]_
- L187-206 _function_ `float2 InternalHorizontalPCF5x2(float2 Fraction, float4 Values00, float4 Values20, float4 Values40)` _[#if SHADER_SHADOWMASK_DEEPSHADOW]_
- L208-216 _function_ `float4 InternalGather4(float2 SamplePos, int2 Offset, FHairSamplingSettings Settings)` _[#if SHADER_SHADOWMASK_DEEPSHADOW]_
- L219-256 _function_ `float InternalManual7x7PCF(float2 ShadowPosition, FHairSamplingSettings Settings)` — high quality, 6x6 samples, using gather4 _[#if SHADER_SHADOWMASK_DEEPSHADOW]_
- L258-292 _function_ `float InternalGaussianFilter(float2 ShadowPosition, FHairSamplingSettings Settings, uint SampleCount)` _[#if SHADER_SHADOWMASK_DEEPSHADOW]_
- L294-330 _function_ `float InternalGaussianTransmissionFilter(float3 ShadowPosition, FHairSamplingSettings Settings, uint SampleCount)` _[#if SHADER_SHADOWMASK_DEEPSHADOW]_
- L429-435 _function_ `float4 ComputeRandom4_0(uint2 PixelPosition, uint InSeed, uint JitterMode)` — The hair shadow mask is rendered by tracing ray/cone through the voxel structure. The traversing is done with point sampling and jittering to get the smooth aspect, and avoid expensive trilinear sampling in a sparse structure. These random functions make various tradeoff between randomness and correlation, so that the output can coverge with TAA without any denoiser. They result from experimentation, and don't have a good grounding _[#if SHADER_SHADOWMASK_VOXEL]_
- L437-457 _function_ `float3 GetShadowMaskRandom(uint2 PixelPosition)` _[#if SHADER_SHADOWMASK_VOXEL]_

### `Shaders/Private/HairStrands/HairStrandsDeepShadowPS.usf` (Private)

- lines: 49; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../SceneTexturesCommon.ush`, L5 `HairStrandsDeepShadowCommon.ush`, L6 `HairStrandsVisibilityCommon.ush`, L7 `HairStrandsVoxelPageCommon.ush`, L8 `/Engine/Generated/Material.ush`, L9 `/Engine/Generated/VertexFactory.ush`

#### Macros (#define, 1)

- L15 `#define SUPPORT_OPACITY_MASK 0`

#### Entry points (2)

- L17-27 _entry_ `void MainDepth( in float4 SvPosition : SV_Position)` — stage: **pixel (from C++ binding)** — C++: `FDeepShadowDepthMeshPS` SF_Pixel via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/HairStrands/HairStrandsRasterCommon.cpp:105)
- L29-49 _entry_ `void MainDom( in float4 SvPosition : SV_Position, in float HairCoverage : CUSTOM_COVERAGE, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FDeepShadowDomMeshPS` SF_Pixel via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/HairStrands/HairStrandsRasterCommon.cpp:129)

#### static const (3)

- L11 _static_const_ `static const float FixPointMaxValue = 1000;` — 100m @hair_todo: make this camera relative, and expose a CVAR fix changing this value
- L12 _static_const_ `static const float FixPointScale = 100;` — 0.1mm precision
- L13 _static_const_ `static const float FixPointRange = 2 * FixPointMaxValue * FixPointScale;`

### `Shaders/Private/HairStrands/HairStrandsDeepShadowVS.usf` (Private)

- lines: 77; parse: all-branches
- includes: L3 `../Common.ush`, L4 `/Engine/Generated/Material.ush`, L5 `/Engine/Generated/VertexFactory.ush`, L7 `HairStrandsVisibilityCommon.ush`

#### Macros (#define, 4)

- L9 `#define MESH_RENDER_DEPTH 0`
- L10 `#define MESH_RENDER_DOM 1`
- L27 `#define VS_OUTPUT_TYPE FDeepShadowAccumulateVSToPS`
- L28 `#define SUPPORT_WPO 0`

#### Entry points (1)

- L33-74 _entry_ `void Main( FVertexFactoryInput Input, out VS_OUTPUT_TYPE Output )` — stage: **vertex (from C++ binding)** — C++: `FDeepShadowDepthMeshVS` SF_Vertex via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/HairStrands/HairStrandsRasterCommon.cpp:49) — C++: `FDeepShadowDomMeshVS` SF_Vertex via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/HairStrands/HairStrandsRasterCommon.cpp:81) — transform mesh as normal _[#if VERTEXSHADER]_

#### Structs / classes (1)

- L16-25 _struct_ **`FDeepShadowAccumulateVSToPS`** `struct FDeepShadowAccumulateVSToPS`
  - L19 _member_ `FVertexFactoryInterpolantsVSToPS Interpolants;` _[#if SUPPORT_TANGENT_PROPERTY == 1 \|\| SUPPORT_MATERIAL_PROPERTY == 1]_
  - L21 _member_ `float4 Position : SV_POSITION;`
  - L23 _member_ `float HairCoverage : CUSTOM_COVERAGE;` _[#if MESH_RENDER_MODE == MESH_RENDER_DOM]_

### `Shaders/Private/HairStrands/HairStrandsDeepTransmittanceCommon.ush` (Private)

- lines: 67; parse: all-branches
- L3 #pragma `once`

#### Structs / classes (1)

- L7-11 _struct_ **`FHairTransmittanceMask`** `struct FHairTransmittanceMask`
  - L9 _member_ `float HairCount;`
  - L10 _member_ `float Visibility;`

#### Functions (8)

- L13-19 _function_ `FHairTransmittanceMask InitHairTransmittanceMask()`
- L21-27 _function_ `FHairTransmittanceMask InitHairTransmittanceMask(float HairCount, float Visibility)`
- L29-32 _function_ `uint PackTransmittanceMask(FHairTransmittanceMask In)`
- L34-37 _function_ `uint InitNullPackedHairTransmittanceMask()`
- L39-45 _function_ `FHairTransmittanceMask UnpackTransmittanceMask(uint In)`
- L47-50 _function_ `bool IsLightDirectional(float4 InTranslatedLightPosition_LightDirection)`
- L53-57 _function_ `float3 GetTranslatedLightDirection(float4 InTranslatedLightPosition_LightDirection, float3 InTranslatedWorldPosition)` — Return the direction from the world position to the light
- L59-66 _function_ `float3 GetTranslatedLightPosition(float4 InTranslatedLightPosition_LightDirection, float3 InTranslatedWorldPosition)`

### `Shaders/Private/HairStrands/HairStrandsDeepTransmittanceDualScattering.ush` (Private)

- lines: 191; parse: all-branches

#### Macros (#define, 2)

- L13 `#define HairScatteringLUTSampler View.SharedBilinearClampedSampler` _[#if SUPPORTS_INDEPENDENT_SAMPLERS]_
- L15 `#define HairScatteringLUTSampler View.HairScatteringLUTSampler` _[#if !(SUPPORTS_INDEPENDENT_SAMPLERS)]_
- L2 #pragma `once`

#### Functions (6)

- L18-23 _function_ `float Hair_g2(float Variance,float Theta)`
- L26-122 _function_ `FHairTransmittanceData ComputeDualScatteringTerms( const FHairTransmittanceMask TransmittanceMask, const FHairAverageScattering AverageScattering, float Roughness, const float Backlit, const float3 V, const float3 L, const float3 T, const uint HairComponents)` — Dual scattering computation are done here for faster iteration (i.e., does not invalidate tons of shaders)
- L124-153 _function_ `FHairTransmittanceData GetHairTransmittance( const float3 V, const float3 L, FGBufferData GBuffer, FHairTransmittanceMask TransmittanceMask, Texture3D<float4> HairLUTTexture, SamplerState HairLUTSampler, const uint HairComponents)`
- L155-163 _function_ `float3 GetHairTransmittanceOnly(FHairTransmittanceMask TransmittanceMask, FGBufferData GBuffer, float SinLightAngle, Texture3D<float4> InHairScatteringLUTTexture, SamplerState InHairLUTSampler)`
- L166-184 _function_ `FHairTransmittanceData EvaluateDualScattering(inout float3 BaseColor, float3 WorldNormal, float Roughness, float3 V, float3 L)` — Evaluate local scattering scattering
- L186-190 _function_ `FHairTransmittanceData EvaluateDualScattering(inout FGBufferData GBuffer, float3 V, float3 L)`

### `Shaders/Private/HairStrands/HairStrandsDeepTransmittanceMask.usf` (Private)

- lines: 526; parse: first-branch (retry, +2 merged from all-branches pass)
- includes: L3 `../Common.ush`, L4 `../SceneTextureParameters.ush`, L5 `../DeferredShadingCommon.ush`, L6 `../ShadowFilteringCommon.ush`, L7 `HairStrandsDeepShadowCommon.ush`, L8 `HairStrandsCommon.ush`, L9 `HairStrandsDeepTransmittanceCommon.ush`, L10 `HairStrandsVisibilityCommon.ush`, L11 `HairStrandsVoxelPageCommon.ush`, L15 `../ShaderPrint.ush` [DEBUG_ENABLE], L225 `HairStrandsVoxelPageTraversal.ush` [SHADER_TRANSMITTANCE_VOXEL], L226 `../LightGridCommon.ush` [SHADER_TRANSMITTANCE_VOXEL], L229 `../ShaderPrint.ush` [SHADER_TRANSMITTANCE_VOXEL && VOXEL_TRAVERSAL_DEBUG], L263 `../VirtualShadowMaps/VirtualShadowMapLightGrid.ush` [SHADER_TRANSMITTANCE_VOXEL], L266 `../BlueNoise.ush` [SHADER_TRANSMITTANCE_VOXEL], L268 `HairStrandsScreenTracing.ush` [SHADER_TRANSMITTANCE_VOXEL]

#### Macros (#define, 7)

- L13 `#define DEBUG_ENABLE 0`
- L61 `#define TRANSMITTANCE_GROUP_SIZE 64` _[#if SHADER_TRANSMITTANCE_DEEPSHADOW \|\| SHADER_TRANSMITTANCE_VOXEL && PERMUTATION_GROUP_SIZE == 64]_
- L63 `#define TRANSMITTANCE_GROUP_SIZE 32` _[#if SHADER_TRANSMITTANCE_DEEPSHADOW \|\| SHADER_TRANSMITTANCE_VOXEL && !(PERMUTATION_GROUP_SIZE == 64) && PERMUTATION_GROUP_SIZE == 32]_
- L219 `#define VOXEL_TRAVERSAL_TYPE VOXEL_TRAVERSAL_LINEAR_MIPMAP` _[#if SHADER_TRANSMITTANCE_VOXEL && PERMUTATION_TRAVERSAL == 1]_
- L221 `#define VOXEL_TRAVERSAL_TYPE VOXEL_TRAVERSAL_LINEAR` _[#if SHADER_TRANSMITTANCE_VOXEL && !(PERMUTATION_TRAVERSAL == 1)]_
- L224 `#define VOXEL_TRAVERSAL_DEBUG 0` _[#if SHADER_TRANSMITTANCE_VOXEL]_
- L265 `#define USE_BLUE_NOISE 1` _[#if SHADER_TRANSMITTANCE_VOXEL]_

#### Entry points (3)

- L156-210 _entry_ `[numthreads(TRANSMITTANCE_GROUP_SIZE, 1, 1)] void MainCS(uint2 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FHairStrandsClearTransmittanceMaskCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsTransmittance.cpp:148) — C++: `FHairStrandsVoxelTransmittanceMaskCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsTransmittance.cpp:242) — C++: `FHairStrandsDeepShadowTransmittanceMaskCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsTransmittance.cpp:373) _[#if SHADER_TRANSMITTANCE_DEEPSHADOW]_
- L360-440 _entry_ `[numthreads(TRANSMITTANCE_GROUP_SIZE, 1, 1)] void MainCS(uint2 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FHairStrandsClearTransmittanceMaskCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsTransmittance.cpp:148) — C++: `FHairStrandsVoxelTransmittanceMaskCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsTransmittance.cpp:242) — C++: `FHairStrandsDeepShadowTransmittanceMaskCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsTransmittance.cpp:373) _[#if SHADER_TRANSMITTANCE_VOXEL]_
- L513-523 _entry_ `[numthreads(64, 1, 1)] void MainCS(uint2 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FHairStrandsClearTransmittanceMaskCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsTransmittance.cpp:148) — C++: `FHairStrandsVoxelTransmittanceMaskCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsTransmittance.cpp:242) — C++: `FHairStrandsDeepShadowTransmittanceMaskCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsTransmittance.cpp:373) _[#if SHADER_CLEAR]_

#### Structs / classes (1)

- L24-40 _struct_ **`FTransmittanceSettings`** `struct FTransmittanceSettings` — Utils function & structs
  - L26 _member_ `int2 AtlasResolution;`
  - L27 _member_ `float4x4 TranslatedWorldToLightTransform;`
  - L28 _member_ `float4 AtlasScaleBias;`
  - L29 _member_ `float3 LightDirection;` — Direction from world position to the light
  - L30 _member_ `float3 TranslatedLightPosition;`
  - L31 _member_ `bool bIsDirectional;`
  - L33 _member_ `float DeepShadowDepthBiasScale;`
  - L34 _member_ `float DeepShadowDensityScale;`
  - L35 _member_ `float TransmittanceKernelApertureInDegree;`
  - L36 _member_ `float3 Random;`
  - L37 _member_ `uint DebugMode;`
  - L39 _member_ `uint TransmittanceKernelType;`

#### Global resources (textures / buffers / samplers) (11)

- L74 _resource_ `StructuredBuffer<uint> DeepShadow_AtlasSlotIndexBuffer;` _[#if SHADER_TRANSMITTANCE_DEEPSHADOW]_
- L75 _resource_ `StructuredBuffer<FDeepShadowViewInfo> DeepShadow_ViewInfoBuffer;` _[#if SHADER_TRANSMITTANCE_DEEPSHADOW]_
- L88 _resource_ `Texture2D<float> DeepShadow_FrontDepthTexture;` _[#if SHADER_TRANSMITTANCE_DEEPSHADOW]_
- L89 _resource_ `Texture2D<float4> DeepShadow_DomTexture;` _[#if SHADER_TRANSMITTANCE_DEEPSHADOW]_
- L91 _resource_ `Buffer<uint4> IndirectArgsBuffer;` _[#if SHADER_TRANSMITTANCE_DEEPSHADOW]_
- L92 _resource_ `RWBuffer<uint> OutTransmittanceMask;` _[#if SHADER_TRANSMITTANCE_DEEPSHADOW]_
- L255 _resource_ `Texture2D<uint4> ShadowMaskBitsTexture;` _[#if SHADER_TRANSMITTANCE_VOXEL && PERMUTATION_ONE_PASS]_
- L257 _resource_ `Texture2D<float4> RayMarchMaskTexture;` _[#if SHADER_TRANSMITTANCE_VOXEL && !(PERMUTATION_ONE_PASS)]_
- L260 _resource_ `Buffer<uint> IndirectArgsBuffer;` _[#if SHADER_TRANSMITTANCE_VOXEL]_
- L261 _resource_ `RWBuffer<uint> OutTransmittanceMask;` _[#if SHADER_TRANSMITTANCE_VOXEL]_
- L511 _resource_ `RWBuffer<uint> OutputMask;` _[#if SHADER_CLEAR]_

#### Global parameters (uniforms) (17)

- L77 _parameter_ `uint2 DeepShadow_AtlasResolution;` _[#if SHADER_TRANSMITTANCE_DEEPSHADOW]_
- L78 _parameter_ `uint LightChannelMask;` _[#if SHADER_TRANSMITTANCE_DEEPSHADOW]_
- L79 _parameter_ `float4 ShadowChannelMask;` _[#if SHADER_TRANSMITTANCE_DEEPSHADOW]_
- L80 _parameter_ `float4 TranslatedLightPosition_LightDirection;` _[#if SHADER_TRANSMITTANCE_DEEPSHADOW]_
- L81 _parameter_ `float DeepShadow_DepthBiasScale;` _[#if SHADER_TRANSMITTANCE_DEEPSHADOW]_
- L82 _parameter_ `float DeepShadow_DensityScale;` _[#if SHADER_TRANSMITTANCE_DEEPSHADOW]_
- L83 _parameter_ `float LightRadius;` _[#if SHADER_TRANSMITTANCE_DEEPSHADOW]_
- L84 _parameter_ `float DeepShadow_KernelAperture;` _[#if SHADER_TRANSMITTANCE_DEEPSHADOW]_
- L85 _parameter_ `float4 DeepShadow_LayerDepths;` _[#if SHADER_TRANSMITTANCE_DEEPSHADOW]_
- L86 _parameter_ `uint DeepShadow_KernelType;` _[#if SHADER_TRANSMITTANCE_DEEPSHADOW]_
- L87 _parameter_ `uint DeepShadow_DebugMode;` _[#if SHADER_TRANSMITTANCE_DEEPSHADOW]_
- L251 _parameter_ `uint LightChannelMask;` _[#if SHADER_TRANSMITTANCE_VOXEL]_
- L252 _parameter_ `float4 TranslatedLightPosition_LightDirection;` _[#if SHADER_TRANSMITTANCE_VOXEL]_
- L253 _parameter_ `float LightRadius;` _[#if SHADER_TRANSMITTANCE_VOXEL]_
- L258 _parameter_ `float4 ShadowChannelMask;` _[#if SHADER_TRANSMITTANCE_VOXEL && !(PERMUTATION_ONE_PASS)]_
- L267-269 _parameter_ `DEFINE_HAIR_BLUE_NOISE_JITTER_FUNCTION uint bUseScreenTrace;` _[#if SHADER_TRANSMITTANCE_VOXEL]_
- L510 _parameter_ `uint ElementCount;` _[#if SHADER_CLEAR]_

#### Functions (6)

- L42-47 _function_ `float3 GetViewVector(float3 InTranslatedWorldPosition)`
- L49-53 _function_ `float3 GetTranslatedWorldPosition(float2 UV, float SceneDepth)`
- L94-154 _function_ `FHairTransmittanceMask ComputeTransmittance( float3 TranslatedWorldPosition, FTransmittanceSettings Settings, float4 InLayerDepths, Texture2D<float> FrontDepthTexture, Texture2D<float4> DomTexture)` _[#if SHADER_TRANSMITTANCE_DEEPSHADOW]_
- L230-248 _function_ `void PrintInfo(uint Index, uint2 PixelCoord, FHairTransmittanceMask TransmittanceMask)` _[#if SHADER_TRANSMITTANCE_VOXEL && VOXEL_TRAVERSAL_DEBUG]_
- L271-281 _function_ `float3 InternalGetHairVoxelJitter(uint2 PixelCoord, uint SampleIndex, uint MaxSampleCount, uint TimeIndex, uint JitterMode)` _[#if SHADER_TRANSMITTANCE_VOXEL]_
- L283-358 _function_ `FHairTransmittanceMask ComputeTransmittanceVoxel( const uint2 PixelCoord, const float PixelRadius, const float SceneDepth, float3 TranslatedWorldPosition, uint MacroGroupId, FTransmittanceSettings Settings, bool bDebugEnabled)` _[#if SHADER_TRANSMITTANCE_VOXEL]_

### `Shaders/Private/HairStrands/HairStrandsEnvironmentAO.usf` (Private)

- lines: 154; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../MonteCarlo.ush`, L5 `../DeferredShadingCommon.ush`, L6 `../PositionReconstructionCommon.ush`, L7 `../HairShadingCommon.ush`, L8 `../HairBsdf.ush`, L9 `HairStrandsEnvironmentLightingCommon.ush`, L10 `../Substrate/Substrate.ush`, L14 `HairStrandsVoxelPageTraversal.ush`

#### Macros (#define, 2)

- L12 `#define VOXEL_TRAVERSAL_TYPE VOXEL_TRAVERSAL_LINEAR_MIPMAP`
- L13 `#define VOXEL_TRAVERSAL_DEBUG 0`

#### Entry points (1)

- L113-153 _entry_ `void MainPS( in float4 SvPosition : SV_Position, out float4 OutAO : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FHairEnvironmentAO` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsEnvironment.cpp:135)

#### Global resources (textures / buffers / samplers) (1)

- L16 _resource_ `Texture2D<uint4> HairCategorizationTexture;`

#### Global parameters (uniforms) (8)

- L18 _parameter_ `uint Voxel_MacroGroupId;`
- L19 _parameter_ `float Voxel_TanConeAngle;`
- L20 _parameter_ `float AO_Power;`
- L21 _parameter_ `float AO_Intensity;`
- L22 _parameter_ `uint AO_SampleCount;`
- L23 _parameter_ `float AO_DistanceThreshold;`
- L25 _parameter_ `uint Output_bHalfRes;`
- L26 _parameter_ `float2 Output_InvResolution;`

#### Functions (1)

- L28-111 _function_ `float TraceAO(float3 TranslatedWorldPosition, float3 WorldNormal, float2 SvPosition, float PixelRadius)`

### `Shaders/Private/HairStrands/HairStrandsEnvironmentLighting.usf` (Private)

- lines: 933; parse: all-branches
- includes: L45 `../Common.ush`, L46 `/Engine/Shared/HairStrandsDefinitions.h`, L47 `HairStrandsCommon.ush`, L48 `../DeferredShadingCommon.ush`, L49 `../BRDF.ush`, L50 `../ReflectionEnvironmentShared.ush`, L51 `../SkyLightingShared.ush`, L52 `../SkyLightingDiffuseShared.ush`, L53 `../DistanceFieldAOShared.ush`, L54 `../ShadingModels.ush`, L55 `../LightGridCommon.ush`, L56 `../SceneTextureParameters.ush`, L57 `../ReflectionEnvironmentComposite.ush`, L58 `../SHCommon.ush`, L59 `../ReflectionEnvironmentShared.ush`, L60 `../SkyLightingShared.ush`, L61 `../VolumetricLightmapShared.ush`, L62 `../HairBsdf.ush`, L63 `../ShaderPrint.ush`, L65 `../Lumen/LumenRadianceCacheCommon.ush` [PERMUTATION_LUMEN == 1], L66 `../Lumen/LumenMaterial.ush` [PERMUTATION_LUMEN == 1], L69 `../Lumen/LumenTracingCommon.ush` [PERMUTATION_LUMEN == 2], L70 `../Lumen/LumenIrradianceFieldInterpolation.ush` [PERMUTATION_LUMEN == 2], L71 `../Lumen/LumenMaterial.ush` [PERMUTATION_LUMEN == 2], L74 `HairStrandsVisibilityCommon.ush`, L75 `HairStrandsVisibilityUtils.ush`, L76 `HairStrandsVoxelPageCommon.ush`, L77 `HairStrandsDeepShadowCommon.ush`, L78 `HairStrandsDeepTransmittanceCommon.ush`, L79 `HairStrandsDeepTransmittanceDualScattering.ush`, L80 `HairStrandsEnvironmentLightingCommon.ush`, L85 `HairStrandsVoxelPageTraversal.ush`, L88 `../BlueNoise.ush`, L216 `HairStrandsDebugCommonStruct.ush` [PERMUTATION_DEBUG], L302 `HairStrandsScreenTracing.ush` [PERMUTATION_INTEGRATION_TYPE == INTEGRATION_UNIFORM \|\| PERMUTATION_INTEGRATION_TYPE == INTEGRATION_ADHOC \|\| PERMUTATION_INTEGRATION_TYPE == INTEGRATION_SH]

#### Macros (#define, 24)

- L29 `#define ALLOW_STATIC_LIGHTING 1` _[#if PERMUTATION_STATIC_LIGHTING]_
- L30 `#define REFLECTION_COMPOSITE_SUPPORT_SKYLIGHT_BLEND 1` _[#if PERMUTATION_STATIC_LIGHTING]_
- L31 `#define PRECOMPUTED_IRRADIANCE_VOLUME_LIGHTING 1` _[#if PERMUTATION_STATIC_LIGHTING]_
- L32 `#define APPLY_SKY_SHADOWING 1` _[#if PERMUTATION_STATIC_LIGHTING]_
- L34 `#define ALLOW_STATIC_LIGHTING 0` _[#if !(PERMUTATION_STATIC_LIGHTING)]_
- L35 `#define REFLECTION_COMPOSITE_SUPPORT_SKYLIGHT_BLEND 0` _[#if !(PERMUTATION_STATIC_LIGHTING)]_
- L36 `#define PRECOMPUTED_IRRADIANCE_VOLUME_LIGHTING 0` _[#if !(PERMUTATION_STATIC_LIGHTING)]_
- L38 `#define REFLECTION_COMPOSITE_USE_BLENDED_REFLECTION_CAPTURES 1`
- L39 `#define REFLECTION_COMPOSITE_HAS_BOX_CAPTURES 1`
- L40 `#define REFLECTION_COMPOSITE_HAS_SPHERE_CAPTURES 1`
- L41 `#define ENABLE_SKY_LIGHT 1`
- L42 `#define USE_HAIR_COMPLEX_TRANSMITTANCE 1`
- L43 `#define ADAPTIVE_PROBES 0`
- L82 `#define VOXEL_TRAVERSAL_TYPE VOXEL_TRAVERSAL_LINEAR_MIPMAP`
- L84 `#define VOXEL_TRAVERSAL_DEBUG 0`
- L87 `#define USE_BLUE_NOISE 1`
- L94 `#define INTEGRATION_SCENECOLOR 0`
- L95 `#define INTEGRATION_ADHOC 1`
- L96 `#define INTEGRATION_UNIFORM 2`
- L97 `#define INTEGRATION_SH 3`
- L311 `#define ADHOC_SAMPLING_R 1` _[#if PERMUTATION_INTEGRATION_TYPE == INTEGRATION_ADHOC]_
- L312 `#define ADHOC_SAMPLING_TT 0` _[#if PERMUTATION_INTEGRATION_TYPE == INTEGRATION_ADHOC]_
- L313 `#define ADHOC_SAMPLING_TRT 1` _[#if PERMUTATION_INTEGRATION_TYPE == INTEGRATION_ADHOC]_
- L314 `#define ADHOC_SAMPLING_MS 1` _[#if PERMUTATION_INTEGRATION_TYPE == INTEGRATION_ADHOC]_
- L27 #undef `ALLOW_STATIC_LIGHTING`

#### Entry points (2)

- L852-866 _entry_ `void MainVS( in uint InVertexId : SV_VertexID, out float4 OutPosition : SV_POSITION, nointerpolation out uint OutNodeCount : DISPATCH_NODECOUNT, nointerpolation out uint2 OutResolution : DISPATCH_RESOLUTION)` — stage: **vertex (from C++ binding)** — C++: `FHairEnvironmentLightingVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsEnvironment.cpp:312) _[#if LIGHTING_VS]_
- L874-930 _entry_ `void MainPS( float4 SVPos : SV_POSITION, uint NodeCount : DISPATCH_NODECOUNT, uint2 Resolution : DISPATCH_RESOLUTION, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FHairEnvironmentLightingPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsEnvironment.cpp:311) _[#if LIGHTING_PS]_

#### Global resources (textures / buffers / samplers) (8)

- L104 _resource_ `Texture3D<float4> HairEnergyLUTTexture;`
- L218 _resource_ `RWStructuredBuffer<FDebugShadingInfo> Debug_ShadingPointBuffer;` _[#if PERMUTATION_DEBUG]_
- L219 _resource_ `RWBuffer<uint> Debug_ShadingPointCounter;` _[#if PERMUTATION_DEBUG]_
- L220 _resource_ `RWStructuredBuffer<FDebugSample> Debug_SampleBuffer;` _[#if PERMUTATION_DEBUG]_
- L221 _resource_ `RWBuffer<uint> Debug_SampleCounter;` _[#if PERMUTATION_DEBUG]_
- L261 _resource_ `Texture2D<float> HairCountTexture;`
- L818 _resource_ `Texture2D<float4> SceneColorTexture;` _[#if PERMUTATION_INTEGRATION_TYPE == INTEGRATION_SCENECOLOR]_
- L872 _resource_ `Buffer<uint> IndirectArgsBuffer;` _[#if LIGHTING_PS]_

#### Global parameters (uniforms) (9)

- L89-102 _parameter_ `DEFINE_HAIR_BLUE_NOISE_JITTER_FUNCTION uint bDynamicSkyLight;`
- L103 _parameter_ `uint bHasStaticLighting;`
- L222 _parameter_ `uint Debug_MaxShadingPointCount;` _[#if PERMUTATION_DEBUG]_
- L223 _parameter_ `uint Debug_MaxSampleCount;` _[#if PERMUTATION_DEBUG]_
- L259 _parameter_ `float HairDistanceThreshold;`
- L260 _parameter_ `uint bHairUseViewHairCount;`
- L263 _parameter_ `uint MultipleScatterSampleCount;`
- L264 _parameter_ `float TransmissionDensityScaleFactor;`
- L303 _parameter_ `uint bScreenTrace;` _[#if PERMUTATION_INTEGRATION_TYPE == INTEGRATION_UNIFORM \|\| PERMUTATION_INTEGRATION_TYPE == INTEGRATION_ADHOC \|\| PERMUTATION_INTEGRATION_TYPE == INTEGRATION_SH]_

#### Functions (11)

- L111-129 _function_ `float3 GetPrecomputedIndirectLighting(float3 AbsoluteWorldPosition, float3 DiffuseDir)` — Calculates indirect lighting contribution on this object from precomputed data. _[#if PERMUTATION_STATIC_LIGHTING]_
- L132-152 _function_ `float3 GetStaticLighting(in FGBufferData GBuffer, float3 CameraDirection, float3 AbsoluteWorldPosition)`
- L157-210 _function_ `float3 GatherRadiance(float3 RayDirection, float Roughness, uint2 PixelPosition, float PixelSceneDepth, float3 TranslatedWorldPosition)` — Reflection probe evaluation
- L225-245 _function_ `uint AddShadingPoint(const FGBufferData GB, const float3 V, uint SampleCount)` _[#if PERMUTATION_DEBUG]_
- L247-254 _function_ `void AddSample(uint SampleOffset, uint SampleIt, const float3 D, const float3 W)` _[#if PERMUTATION_DEBUG]_
- L266-299 _function_ `FHairTraversalResult InternalComputeHairCountVoxel( const FVirtualVoxelNodeDesc NodeDesc, float3 TranslatedWorldPosition, float3 TranslatedLightPosition, float ExtraDensityScale, float CountThreshold, float DistanceThreshold, float PixelRadius, bool bUseConeTracing, bool bDebugEnabled)`
- L316-319 _function_ `float MaxComponent3(float3 In)` _[#if PERMUTATION_INTEGRATION_TYPE == INTEGRATION_ADHOC]_
- L321-625 _function_ `float3 ReflectionEnvironment(FGBufferData GBuffer, float2 ScreenPosition, float2 SvPosition, uint ControlPointId, uint MacroGroupId)` _[#if PERMUTATION_INTEGRATION_TYPE == INTEGRATION_ADHOC]_
- L632-734 _function_ `float3 ReflectionEnvironmentUniformSampling( FGBufferData GBuffer, float2 ScreenPosition, float2 SvPosition, uint HairControlPointId, uint MacroGroupId, bool bDebugEnabled)` _[#if PERMUTATION_INTEGRATION_TYPE == INTEGRATION_UNIFORM]_
- L742-811 _function_ `float3 ReflectionEnvironmentSH( FGBufferData GBuffer, float2 ScreenPosition, float2 SvPosition, uint HairControlPointId, uint MacroGroupId, bool bDebugEnabled)` _[#if PERMUTATION_INTEGRATION_TYPE == INTEGRATION_SH]_
- L820-844 _function_ `float3 ComputeThinTransmission(FGBufferData GBuffer, float2 ScreenPosition, float2 SvPosition, uint HairControlPointId)` _[#if PERMUTATION_INTEGRATION_TYPE == INTEGRATION_SCENECOLOR]_

### `Shaders/Private/HairStrands/HairStrandsEnvironmentLightingCommon.ush` (Private)

- lines: 92; parse: all-branches
- includes: L67 `HairStrandsCommon.ush` [USE_HAIR_COMPLEX_TRANSMITTANCE], L68 `HairStrandsDeepTransmittanceCommon.ush` [USE_HAIR_COMPLEX_TRANSMITTANCE], L69 `HairStrandsDeepTransmittanceDualScattering.ush` [USE_HAIR_COMPLEX_TRANSMITTANCE]

#### Macros (#define, 1)

- L63 `#define USE_HAIR_COMPLEX_TRANSMITTANCE 0` _[#if !defined(USE_HAIR_COMPLEX_TRANSMITTANCE)]_
- L3 #pragma `once`

#### Functions (6)

- L8-12 _function_ `float HairToGGXRoughness_R(float R_Roughness)` — Roughness remapping functions of each term of the hair BSDF to the default lit model (GGX based) This remapping is done based on the hair longitudinal component. This means it does not take into around the anistotropic streatching which happen along the azimuthal plane
- L14-28 _function_ `float HairToGGXRoughness_TRT(float R_Roughness)`
- L30-41 _function_ `float HairToGGXRoughness_TT(float TT_Roughness)`
- L43-51 _function_ `float4 ComputeRandom4(uint2 PixelPosition, uint SampleIt, uint SampleCount, uint FrameIdMod8)`
- L55-60 _function_ `float3 ComputePositionBias(float3 SampleDirection, float3 SampleOffset, float VoxelWorldSize, float DepthBiasScale)` — Compute a sample bias by adding a constant bias (3d jitter within a voxel) + a directional offset (jitter along the direction). Both constant & directional bias are scaled with the size of a voxel
- L72-92 _function_ `float3 EvaluateEnvHair(FGBufferData GBuffer, float3 V, float3 N, inout float3 OutL)`

### `Shaders/Private/HairStrands/HairStrandsFollicleMask.usf` (Private)

- lines: 226; parse: all-branches
- includes: L3 `../Common.ush`, L4 `HairStrandsBindingCommon.ush`

#### Macros (#define, 2)

- L14 `#define UV_MESH 0` _[#if SHADER_FOLLICLE_MASK]_
- L15 `#define UV_ROOT 1` _[#if SHADER_FOLLICLE_MASK]_

#### Entry points (3)

- L27-84 _entry_ `void MainVS( uint VertexId : SV_VertexID, out float2 OutVertexUV : TRI_UVs, out float2 OutRootUV : ROOT_UV, out float4 OutPosition : SV_POSITION)` — stage: **vertex (from C++ binding)** — C++: `FHairFollicleMaskVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsMeshProjection.cpp:826) _[#if SHADER_FOLLICLE_MASK]_
- L86-118 _entry_ `void MainPS( in float2 VertexUV : TRI_UVs, in float2 RootUV : ROOT_UV, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FHairFollicleMaskPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsMeshProjection.cpp:825) _[#if SHADER_FOLLICLE_MASK]_
- L172-224 _entry_ `[numthreads(8, 8, 1)] void MainCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FGenerateMipCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsMeshProjection.cpp:1035) _[#if SHADER_GENERATE_MIPS]_

#### Structs / classes (2)

- L131-136 _struct_ **`Gaussian3x3`** `struct Gaussian3x3` _[#if SHADER_GENERATE_MIPS]_
  - L133 _member_ `float Weight[9];` _[#if SHADER_GENERATE_MIPS]_
  - L134 _member_ `int Offset;` _[#if SHADER_GENERATE_MIPS]_
  - L135 _member_ `int Width;` _[#if SHADER_GENERATE_MIPS]_
- L151-156 _struct_ **`Gaussian5x5`** `struct Gaussian5x5` _[#if SHADER_GENERATE_MIPS]_
  - L153 _member_ `float Weight[25];` _[#if SHADER_GENERATE_MIPS]_
  - L154 _member_ `int Offset;` _[#if SHADER_GENERATE_MIPS]_
  - L155 _member_ `int Width;` _[#if SHADER_GENERATE_MIPS]_

#### Global resources (textures / buffers / samplers) (7)

- L18 _resource_ `Buffer<float4> UniqueTrianglePositionBuffer;` _[#if SHADER_FOLLICLE_MASK && PERMUTATION_UV_TYPE == UV_MESH]_
- L19 _resource_ `Buffer<uint> RootToUniqueTriangleIndexBuffer;` _[#if SHADER_FOLLICLE_MASK && PERMUTATION_UV_TYPE == UV_MESH]_
- L20 _resource_ `Buffer<uint> RootBarycentricBuffer;` _[#if SHADER_FOLLICLE_MASK && PERMUTATION_UV_TYPE == UV_MESH]_
- L24 _resource_ `Buffer<float2> RootUVsBuffer;` _[#if SHADER_FOLLICLE_MASK && PERMUTATION_UV_TYPE == UV_ROOT]_
- L127 _resource_ `Texture2D<float4> InTexture;` _[#if SHADER_GENERATE_MIPS]_
- L128 _resource_ `RWTexture2D<float4> OutTexture;` _[#if SHADER_GENERATE_MIPS]_
- L129 _resource_ `SamplerState LinearSampler;` _[#if SHADER_GENERATE_MIPS]_

#### Global parameters (uniforms) (8)

- L8 _parameter_ `float2 OutputResolution;` _[#if SHADER_FOLLICLE_MASK]_
- L9 _parameter_ `uint MaxRootCount;` _[#if SHADER_FOLLICLE_MASK]_
- L10 _parameter_ `uint MaxUniqueTriangleIndex;` _[#if SHADER_FOLLICLE_MASK]_
- L11 _parameter_ `uint Channel;` _[#if SHADER_FOLLICLE_MASK]_
- L12 _parameter_ `uint KernelSizeInPixels;` _[#if SHADER_FOLLICLE_MASK]_
- L123 _parameter_ `uint Resolution;` _[#if SHADER_GENERATE_MIPS]_
- L124 _parameter_ `uint SourceMip;` _[#if SHADER_GENERATE_MIPS]_
- L125 _parameter_ `uint TargetMip;` _[#if SHADER_GENERATE_MIPS]_

#### Functions (2)

- L138-149 _function_ `Gaussian3x3 Initialize3x3()` _[#if SHADER_GENERATE_MIPS]_
- L158-170 _function_ `Gaussian5x5 Initialize5x5()` _[#if SHADER_GENERATE_MIPS]_

### `Shaders/Private/HairStrands/HairStrandsForwardCulling.usf` (Private)

- lines: 345; parse: all-branches
- includes: L12 `../Common.ush` [SHADER_RASTERCOMPUTE_CULL], L13 `HairStrandsVisibilityCommon.ush` [SHADER_RASTERCOMPUTE_CULL], L14 `HairStrandsVertexFactoryCommon.ush` [SHADER_RASTERCOMPUTE_CULL]

#### Macros (#define, 5)

- L3 `#define HAIR_STRANDS_PARAMETERS 1`
- L5 `#define CULL_ENABLE 0`
- L7 `#define CULLING_CURVE 1`
- L8 `#define CULLING_POINT 2`
- L9 `#define CULLING_TYPE CULLING_CURVE`

#### Entry points (2)

- L89-233 _entry_ `[numthreads(1024, 1, 1)] void CSMain(uint DispatchThreadID : SV_DispatchThreadID, uint GroupThreadID : SV_GroupThreadID, uint GroupID : SV_GroupID)` — stage: **compute** — C++: `FHairCullSegmentCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsForwardRaster.cpp:66) _[#if SHADER_RASTERCOMPUTE_CULL && CULLING_TYPE == CULLING_CURVE]_
- L242-342 _entry_ `[numthreads(1024, 1, 1)] void CSMain(uint DispatchThreadID : SV_DispatchThreadID, uint GroupThreadID : SV_GroupThreadID, uint GroupID : SV_GroupID)` — stage: **compute** — C++: `FHairCullSegmentCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsForwardRaster.cpp:66) _[#if SHADER_RASTERCOMPUTE_CULL && CULLING_TYPE == CULLING_POINT]_

#### Global resources (textures / buffers / samplers) (5)

- L22 _resource_ `Texture2D<float> SceneDepthTexture;` — Input _[#if SHADER_RASTERCOMPUTE_CULL]_
- L29 _resource_ `RWBuffer<float4> RWPoints;` — Output _[#if SHADER_RASTERCOMPUTE_CULL]_
- L30 _resource_ `RWStructuredBuffer<FPackedHairVis> RWHairVis;` _[#if SHADER_RASTERCOMPUTE_CULL]_
- L31 _resource_ `RWBuffer<uint2> RWCoord;` _[#if SHADER_RASTERCOMPUTE_CULL]_
- L32 _resource_ `RWStructuredBuffer<uint> RWCounter;` _[#if SHADER_RASTERCOMPUTE_CULL]_

#### Global parameters (uniforms) (4)

- L23 _parameter_ `float2 OutputResolution;` _[#if SHADER_RASTERCOMPUTE_CULL]_
- L24 _parameter_ `uint HairMaterialId;` _[#if SHADER_RASTERCOMPUTE_CULL]_
- L25 _parameter_ `uint ControlPointCount;` _[#if SHADER_RASTERCOMPUTE_CULL]_
- L26 _parameter_ `uint CurveCount;` _[#if SHADER_RASTERCOMPUTE_CULL]_

#### groupshared (4)

- L86 _groupshared_ `groupshared uint s_ValidSegmentCount;` _[#if SHADER_RASTERCOMPUTE_CULL && CULLING_TYPE == CULLING_CURVE]_
- L87 _groupshared_ `groupshared uint s_WriteOffset;` _[#if SHADER_RASTERCOMPUTE_CULL && CULLING_TYPE == CULLING_CURVE]_
- L239 _groupshared_ `groupshared uint s_ValidSegmentCount;` _[#if SHADER_RASTERCOMPUTE_CULL && CULLING_TYPE == CULLING_POINT]_
- L240 _groupshared_ `groupshared uint s_WriteOffset;` _[#if SHADER_RASTERCOMPUTE_CULL && CULLING_TYPE == CULLING_POINT]_

#### Functions (2)

- L37-42 _function_ `float3 NDCToPixelCoord(float4 InDC)` _[#if SHADER_RASTERCOMPUTE_CULL]_
- L45-81 _function_ `bool IsViewportVisible(inout float4 P0, inout float4 P1)` — Line clipping based on "CLIPPING USING HOMOGENEOUS COORDINATES" by Blinn et al. _[#if SHADER_RASTERCOMPUTE_CULL]_

### `Shaders/Private/HairStrands/HairStrandsForwardRaster.usf` (Private)

- lines: 2098; parse: all-branches
- includes: L5 `../Common.ush`, L6 `../WaveOpUtil.ush`, L7 `HairStrandsClusterCommon.ush`, L8 `HairStrandsVertexFactoryCommon.ush`, L9 `HairStrandsVisibilityCommon.ush`, L10 `../ColorMap.ush`, L13 `../ShaderPrint.ush` [PERMUTATION_DEBUG], L1954 `../ShaderPrint.ush` [SHADER_RASTERCOMPUTE_DEBUG]

#### Macros (#define, 26)

- L3 `#define HAIR_STRANDS_PARAMETERS 0`
- L72 `#define MAX_WORK_COUNT 4096`
- L74 `#define BIN_TILE_SIZE 32`
- L75 `#define BIN_RCP_TILE_SIZE (1.f / BIN_TILE_SIZE)`
- L76 `#define BIN_TILE_SIZE_AS_SHIFT 5`
- L77 `#define BIN_THREAD_COUNT 1024`
- L79 `#define RASTER_TILE_SIZE 8`
- L80 `#define RASTER_RCP_TILE_SIZE (1.f / RASTER_TILE_SIZE)`
- L81 `#define RASTER_TILE_SIZE_AS_SHIFT 3`
- L82 `#define RASTER_THREAD_COUNT 64`
- L104 `#define DDA_MAX_ITERATIONS 256`
- L153 `#define VT_PrimOffset 0`
- L154 `#define VT_PrimCount 1`
- L155 `#define VT_Coord 2`
- L156 `#define VT_MinWriteIndex 3`
- L157 `#define VT_MinMaxDepth 4`
- L158 `#define VT_SIZE 5`
- L466 `#define BIN_MINMAX 1`
- L486 `#define TILES_TO_ALLOCATE_MAX 1024` _[#if SHADER_RASTERCOMPUTE_BINNING]_
- L761 `#define COMPACTION_DEPTH_BUCKET 1024` _[#if SHADER_RASTERCOMPUTE_COMPACTION]_
- L1016 `#define RASTER_DEPTH_BUCKET 64`
- L1017 `#define RASTER_SEGMENT_COUNT 32`
- L1018 `#define SEGMENT_COUNT_PER_GROUP 1024`
- L1019 `#define INVALID_PRIM_ID 0xFFFFFFFF`
- L1020 `#define INVALID_VELOCITY -1e8f`
- L1024 `#define SHADER_RASTERCOMPUTE_RASTER 1` _[#if !SHADER_RASTERCOMPUTE_DEBUG && !SHADER_RASTERCOMPUTE_COMPACTION && !SHADER_RASTERCOMPUTE_BINNING && !SHADER_RASTERCOMPUTE_RASTER_MULTI_SAMPLE && !SHADER_RASTERCOMPUTE_DEPTH_GRID]_

#### Entry points (5)

- L430-460 _entry_ `[numthreads(BIN_THREAD_COUNT, 1, 1)] void PrepareDepthGridCS(uint DispatchThreadID : SV_DispatchThreadID, uint GroupThreadID : SV_GroupThreadID, uint2 GroupID : SV_GroupID)` — stage: **compute** — C++: `FHairStrandsForwardRasterPrepareDepthGridCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsForwardRaster.cpp:114) _[#if SHADER_RASTERCOMPUTE_DEPTH_GRID]_
- L494-735 _entry_ `[numthreads(1024, 1, 1)] void BinningCS(uint GroupThreadID : SV_GroupThreadID, uint GroupID : SV_GroupID)` — stage: **compute** — C++: `FHairStrandsForwardRasterBinningCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsForwardRaster.cpp:161) _[#if SHADER_RASTERCOMPUTE_BINNING]_
- L778-1010 _entry_ `[numthreads(1024, 1, 1)] void CompactionCS(uint DispatchThreadID : SV_DispatchThreadID, uint GroupThreadID : SV_GroupThreadID, uint2 GroupID : SV_GroupID)` — stage: **compute** — C++: `FHairStrandsForwardRasterCompactionCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsForwardRaster.cpp:208) — Launch based on CPU BinTileResX x BinTileResY 1 group per screen-tile, 1 threads per bin-tile matching the screen-tile coord There can be/are several bins for the same screen area _[#if SHADER_RASTERCOMPUTE_COMPACTION]_
- L1228-1946 _entry_ `[numthreads(RASTER_TILE_SIZE, RASTER_TILE_SIZE, 1)] void RasterCS( uint GroupThread1D : SV_GroupIndex, uint2 GroupThread2D : SV_GroupThreadID, uint GroupID : SV_GroupID)` — stage: **compute** — C++: `FHairStrandsForwardRasterRasterizeCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsForwardRaster.cpp:263) _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L2014-2095 _entry_ `[numthreads(8, 8, 1)] void MainCS(uint3 ThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FHairStrandsForwardRasterDebugCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsForwardRaster.cpp:304) _[#if SHADER_RASTERCOMPUTE_DEBUG]_

#### Structs / classes (3)

- L38-42 _struct_ **`FDepthRange`** `struct FDepthRange`
  - L40 _member_ `float MinZ;`
  - L41 _member_ `float MaxZ;`
- L106-112 _struct_ **`FDDAContext`** `struct FDDAContext`
  - L108 _member_ `float2 Coord;`
  - L109 _member_ `float2 DeltaDist;`
  - L110 _member_ `float2 Step;`
  - L111 _member_ `float2 SideDist;`
- L1149-1154 _struct_ **`FSampleData`** `struct FSampleData` _[#if SHADER_RASTERCOMPUTE_RASTER]_
  - L1151 _member_ `uint2 Coord;` — 2x3bits - Pixel coord within the tile 8x8 _[#if SHADER_RASTERCOMPUTE_RASTER]_
  - L1152 _member_ `float Depth;` — 16 bits _[#if SHADER_RASTERCOMPUTE_RASTER]_
  - L1153 _member_ `float Coverage;` — 10 bits _[#if SHADER_RASTERCOMPUTE_RASTER]_

#### Global resources (textures / buffers / samplers) (42)

- L216 _resource_ `Buffer<float4> ControlPoints;` — Control points
- L217 _resource_ `StructuredBuffer<uint> ControlPointCount;`
- L426 _resource_ `Texture2D<float> SceneDepthTexture;` _[#if SHADER_RASTERCOMPUTE_DEPTH_GRID]_
- L427 _resource_ `RWTexture2D<uint> OutVisTileDepthGrid;` _[#if SHADER_RASTERCOMPUTE_DEPTH_GRID]_
- L470 _resource_ `RWTexture2DArray<uint> OutVisTileBinningGrid;` _[#if SHADER_RASTERCOMPUTE_BINNING]_
- L472 _resource_ `RWTexture2DArray<uint> OutVisTileBinningGridMinZ;` _[#if SHADER_RASTERCOMPUTE_BINNING && BIN_MINMAX]_
- L473 _resource_ `RWTexture2DArray<uint> OutVisTileBinningGridMaxZ;` _[#if SHADER_RASTERCOMPUTE_BINNING && BIN_MINMAX]_
- L475 _resource_ `RWBuffer<uint> OutVisTilePrims;` _[#if SHADER_RASTERCOMPUTE_BINNING]_
- L476 _resource_ `RWBuffer<uint> OutVisTilePrimDepths;` _[#if SHADER_RASTERCOMPUTE_BINNING]_
- L477 _resource_ `RWBuffer<uint> OutVisTileArgs;` _[#if SHADER_RASTERCOMPUTE_BINNING]_
- L478 _resource_ `RWByteAddressBuffer OutVisTileData;` _[#if SHADER_RASTERCOMPUTE_BINNING]_
- L479 _resource_ `Texture2D<uint> VisTileDepthGrid;` _[#if SHADER_RASTERCOMPUTE_BINNING]_
- L480 _resource_ `ByteAddressBuffer IndirectPrimIDCount;` _[#if SHADER_RASTERCOMPUTE_BINNING]_
- L742 _resource_ `ByteAddressBuffer InData;` _[#if SHADER_RASTERCOMPUTE_COMPACTION]_
- L743 _resource_ `Buffer<uint> InPrims;` _[#if SHADER_RASTERCOMPUTE_COMPACTION]_
- L744 _resource_ `Buffer<uint> InDepths;` _[#if SHADER_RASTERCOMPUTE_COMPACTION]_
- L745 _resource_ `Buffer<uint> InArgs;` _[#if SHADER_RASTERCOMPUTE_COMPACTION]_
- L746 _resource_ `RWByteAddressBuffer OutData;` _[#if SHADER_RASTERCOMPUTE_COMPACTION]_
- L747 _resource_ `RWBuffer<uint> OutPrims;` _[#if SHADER_RASTERCOMPUTE_COMPACTION]_
- L748 _resource_ `RWBuffer<uint> OutArgs;` _[#if SHADER_RASTERCOMPUTE_COMPACTION]_
- L749 _resource_ `RWStructuredBuffer<uint> OutWork;` — Offset & Count _[#if SHADER_RASTERCOMPUTE_COMPACTION]_
- L750 _resource_ `RWStructuredBuffer<uint> OutDataCount;` _[#if SHADER_RASTERCOMPUTE_COMPACTION]_
- L751 _resource_ `RWStructuredBuffer<uint> OutWorkCount;` _[#if SHADER_RASTERCOMPUTE_COMPACTION]_
- L1029 _resource_ `Buffer<uint> VisTilePrims;` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L1030 _resource_ `StructuredBuffer<uint> VisTileWork;` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L1031 _resource_ `StructuredBuffer<uint> VisTileWorkCount;` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L1032 _resource_ `Buffer<uint> VisTileArgs;` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L1033 _resource_ `ByteAddressBuffer VisTileData;` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L1034 _resource_ `RWTexture2D<float4> OutSceneColorTexture;` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L1035 _resource_ `RWTexture2D<float4> OutSceneVelocityTexture;` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L1036 _resource_ `RWStructuredBuffer<uint> RWWorkCounter;` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L1039 _resource_ `RWTexture2D<uint> OutHairCountTexture_ForDebug;` _[#if SHADER_RASTERCOMPUTE_RASTER && PERMUTATION_DEBUG]_
- L1040 _resource_ `RWTexture2D<uint> OutHairPixelCountPerTile_ForDebug;` _[#if SHADER_RASTERCOMPUTE_RASTER && PERMUTATION_DEBUG]_
- L1044 _resource_ `Texture2D<float4> SampleLightingTexture;` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L1045 _resource_ `Buffer<float4> SampleVelocityBuffer;` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L1047 _resource_ `Texture2D<float> SceneDepthTexture;` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L1956 _resource_ `Buffer<uint> VisTileArgs;` _[#if SHADER_RASTERCOMPUTE_DEBUG]_
- L1957 _resource_ `ByteAddressBuffer VisTileData;` _[#if SHADER_RASTERCOMPUTE_DEBUG]_
- L1959 _resource_ `Buffer<uint> CompactedVisTileArgs;` _[#if SHADER_RASTERCOMPUTE_DEBUG]_
- L1960 _resource_ `ByteAddressBuffer CompactedVisTileData;` _[#if SHADER_RASTERCOMPUTE_DEBUG]_
- L1962 _resource_ `Texture2D<uint> HairCountTexture_ForDebug;` _[#if SHADER_RASTERCOMPUTE_DEBUG]_
- L1963 _resource_ `Texture2D<uint> HairPixelCountPerTile_ForDebug;` _[#if SHADER_RASTERCOMPUTE_DEBUG]_

#### Global parameters (uniforms) (14)

- L201 _parameter_ `int2 BinTileRes;`
- L202 _parameter_ `int2 RasterTileRes;`
- L204 _parameter_ `uint NumBinners;`
- L205 _parameter_ `float RcpNumBinners;`
- L207 _parameter_ `uint NumRasterizers;`
- L208 _parameter_ `float RcpNumRasterizers;`
- L210 _parameter_ `int2 OutputResolution;`
- L211 _parameter_ `float2 OutputResolutionf;`
- L212 _parameter_ `float RadiusAtDepth1;`
- L218 _parameter_ `uint MaxControlPointCount;`
- L1043 _parameter_ `int2 SampleLightingViewportResolution;` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L1964 _parameter_ `uint InstanceCount;` _[#if SHADER_RASTERCOMPUTE_DEBUG]_
- L1965 _parameter_ `uint CPUAllocatedTileCount;` _[#if SHADER_RASTERCOMPUTE_DEBUG]_
- L1966 _parameter_ `uint CPUAllocatedCompactedTileCount;` _[#if SHADER_RASTERCOMPUTE_DEBUG]_

#### groupshared (32)

- L428 _groupshared_ `groupshared uint group_FurthestDepth;` — (4 bytes) _[#if SHADER_RASTERCOMPUTE_DEPTH_GRID]_
- L482 _groupshared_ `groupshared uint group_LoopNum;` _[#if SHADER_RASTERCOMPUTE_BINNING]_
- L483 _groupshared_ `groupshared uint group_VerticesNum;` _[#if SHADER_RASTERCOMPUTE_BINNING]_
- L484 _groupshared_ `groupshared uint group_BatchNum;` _[#if SHADER_RASTERCOMPUTE_BINNING]_
- L488 _groupshared_ `groupshared uint group_TilesToAllocate[TILES_TO_ALLOCATE_MAX];` _[#if SHADER_RASTERCOMPUTE_BINNING]_
- L489 _groupshared_ `groupshared uint group_TilesToAllocateCount;` _[#if SHADER_RASTERCOMPUTE_BINNING]_
- L753 _groupshared_ `groupshared uint group_TotalPrimCount;` _[#if SHADER_RASTERCOMPUTE_COMPACTION]_
- L754 _groupshared_ `groupshared uint group_PrimWriteOffset;` _[#if SHADER_RASTERCOMPUTE_COMPACTION]_
- L755 _groupshared_ `groupshared uint group_NumTiles;` _[#if SHADER_RASTERCOMPUTE_COMPACTION]_
- L756 _groupshared_ `groupshared uint group_TilesToCompact[1024];` _[#if SHADER_RASTERCOMPUTE_COMPACTION]_
- L757 _groupshared_ `groupshared uint group_MaxLDSTileIdx;` _[#if SHADER_RASTERCOMPUTE_COMPACTION]_
- L758 _groupshared_ `groupshared uint group_MinZ;` _[#if SHADER_RASTERCOMPUTE_COMPACTION]_
- L759 _groupshared_ `groupshared uint group_MaxZ;` _[#if SHADER_RASTERCOMPUTE_COMPACTION]_
- L762 _groupshared_ `groupshared uint s_BinOffset[COMPACTION_DEPTH_BUCKET];` _[#if SHADER_RASTERCOMPUTE_COMPACTION]_
- L763 _groupshared_ `groupshared uint s_BinCount[COMPACTION_DEPTH_BUCKET];` _[#if SHADER_RASTERCOMPUTE_COMPACTION]_
- L1050 _groupshared_ `groupshared uint2 s_Segments[1024];` — Depth\|ID _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L1051 _groupshared_ `groupshared uint2 s_Segments_Sorted[1024];` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L1052 _groupshared_ `groupshared uint s_Segments_Min;` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L1053 _groupshared_ `groupshared uint s_Segments_Max;` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L1054 _groupshared_ `groupshared uint s_Segments_ValidCount;` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L1055 _groupshared_ `groupshared uint s_SegmentsCount[RASTER_DEPTH_BUCKET];` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L1056 _groupshared_ `groupshared uint s_SegmentsAlloc[RASTER_DEPTH_BUCKET];` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L1059 _groupshared_ `groupshared uint s_Mask[8][8];` — groupshared uint   s_Mask[RASTER_THREAD_COUNT]; _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L1060 _groupshared_ `groupshared uint2 s_OpaqueMask;` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L1061 _groupshared_ `groupshared uint s_Data[RASTER_SEGMENT_COUNT][8];` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L1062 _groupshared_ `groupshared uint s_Color[RASTER_SEGMENT_COUNT][8];` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L1063 _groupshared_ `groupshared uint2 s_Velocity[RASTER_SEGMENT_COUNT][8];` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L1064 _groupshared_ `groupshared uint s_bDataOrder;` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L1065 _groupshared_ `groupshared uint s_WorkID;` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L1067 _groupshared_ `groupshared uint s_BinTileOffset;` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L1068 _groupshared_ `groupshared uint s_BinTileCount;` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L1071 _groupshared_ `groupshared float s_Coverage[RASTER_THREAD_COUNT];` _[#if SHADER_RASTERCOMPUTE_RASTER && PERMUTATION_DEBUG]_

#### Functions (49)

- L18-21 _function_ `uint PackTileCoord(uint2 In)` — Pack/unpack helpers
- L23-26 _function_ `uint2 UnpackTileCoord(uint In)`
- L28-31 _function_ `uint PackDepth(float In)`
- L33-36 _function_ `float UnpackDepth(uint In)`
- L44-47 _function_ `uint PackDepthRange(FDepthRange In)`
- L49-56 _function_ `FDepthRange UnpackDepthRange(uint In)`
- L58-61 _function_ `uint PackWork(uint InTileIndex, uint InTileCount)`
- L63-66 _function_ `uint2 UnpackWork(uint In)`
- L84-95 _function_ `uint2 LinearTo2D_Common(uint In, uint InTileSize, float InRcpTileSize)`
- L97 _function_ `uint2 LinearTo2D_Bin(uint In)`
- L98 _function_ `uint2 LinearTo2D_Raster(uint In)`
- L114-125 _function_ `FDDAContext DDACreateContext(float2 RayStart, float2 RayDir)`
- L127-139 _function_ `void DDAAdvance(inout FDDAContext Context)`
- L167-170 _function_ `uint PackVisTileCoord(uint2 In)`
- L172-175 _function_ `uint2 UnpackVisTileCoord(uint In)`
- L177-181 _function_ `uint LoadOutVisTileData(RWByteAddressBuffer OutBuffer, uint Index, uint VTEntry)`
- L183-187 _function_ `void StoreOutVisTileData(RWByteAddressBuffer OutBuffer, uint Index, uint VTEntry, uint Value)`
- L189-192 _function_ `uint LoadVisTileData(ByteAddressBuffer InBuffer, uint Index, uint VTEntry)`
- L196 _function_ `float4 Transparent(float4 Color)` — Misc.
- L220-223 _function_ `uint GetControlPointCount()`
- L226-240 _function_ `FHairControlPoint UnpackHairControlPoint(uint InPrimId)` — Custom encoding for forward rasterizer. Position are 32bits float. This is temporary.
- L246-251 _function_ `float3 NDCToPixelCoord(float4 InDC)` _[#if SHADER_RASTERCOMPUTE_BINNING \|\| SHADER_RASTERCOMPUTE_COMPACTION \|\| SHADER_RASTERCOMPUTE_RASTER \|\| SHADER_RASTERCOMPUTE_DEPTH_GRID \|\| SHADER_RASTERCOMPUTE_DEBUG]_
- L253-260 _function_ `void CalcHomogenousPos(in uint PrimId, out float4 HP, out uint Type)` _[#if SHADER_RASTERCOMPUTE_BINNING \|\| SHADER_RASTERCOMPUTE_COMPACTION \|\| SHADER_RASTERCOMPUTE_RASTER \|\| SHADER_RASTERCOMPUTE_DEPTH_GRID \|\| SHADER_RASTERCOMPUTE_DEBUG]_
- L262-270 _function_ `void CalcHomogenousPosAndRad(in uint PrimId, out float4 HP, out float Rad, out uint Type)` _[#if SHADER_RASTERCOMPUTE_BINNING \|\| SHADER_RASTERCOMPUTE_COMPACTION \|\| SHADER_RASTERCOMPUTE_RASTER \|\| SHADER_RASTERCOMPUTE_DEPTH_GRID \|\| SHADER_RASTERCOMPUTE_DEBUG]_
- L272-282 _function_ `float ComputeLerpAlpha(int2 Coord, float2 P0, float2 P1, float SegmentLenSqRcp)` _[#if SHADER_RASTERCOMPUTE_BINNING \|\| SHADER_RASTERCOMPUTE_COMPACTION \|\| SHADER_RASTERCOMPUTE_RASTER \|\| SHADER_RASTERCOMPUTE_DEPTH_GRID \|\| SHADER_RASTERCOMPUTE_DEBUG]_
- L284-294 _function_ `float ComputePerspectiveCorrectRadius(float Rad0, float Rad1, float Alpha, float RcpW0, float RcpW1)` _[#if SHADER_RASTERCOMPUTE_BINNING \|\| SHADER_RASTERCOMPUTE_COMPACTION \|\| SHADER_RASTERCOMPUTE_RASTER \|\| SHADER_RASTERCOMPUTE_DEPTH_GRID \|\| SHADER_RASTERCOMPUTE_DEBUG]_
- L297-341 _function_ `bool BlinnLineClipping(inout float4 P0, inout float4 P1)` — Line clipping based on "CLIPPING USING HOMOGENEOUS COORDINATES" by Blinn et al. _[#if SHADER_RASTERCOMPUTE_BINNING \|\| SHADER_RASTERCOMPUTE_COMPACTION \|\| SHADER_RASTERCOMPUTE_RASTER \|\| SHADER_RASTERCOMPUTE_DEPTH_GRID \|\| SHADER_RASTERCOMPUTE_DEBUG]_
- L343-381 _function_ `bool ClipRaySegment(float2 AABBMin, float2 AABBMax, float4 P0, float4 P1, out float2 T, out bool2 bClipped)` _[#if SHADER_RASTERCOMPUTE_BINNING \|\| SHADER_RASTERCOMPUTE_COMPACTION \|\| SHADER_RASTERCOMPUTE_RASTER \|\| SHADER_RASTERCOMPUTE_DEPTH_GRID \|\| SHADER_RASTERCOMPUTE_DEBUG]_
- L383-418 _function_ `bool ClipRaySegment(float2 AABBMin, float2 AABBMax, inout float4 P0, inout float4 P1, inout float Rad0, inout float Rad1, inout float Alpha0, inout float Alpha1, out bool2 bClipped, out float2 T)` _[#if SHADER_RASTERCOMPUTE_BINNING \|\| SHADER_RASTERCOMPUTE_COMPACTION \|\| SHADER_RASTERCOMPUTE_RASTER \|\| SHADER_RASTERCOMPUTE_DEPTH_GRID \|\| SHADER_RASTERCOMPUTE_DEBUG]_
- L765-773 _function_ `uint GetDepthBinIndex(float InDepth)` _[#if SHADER_RASTERCOMPUTE_COMPACTION]_
- L1074-1078 _function_ `void ClearMask(uint2 In)` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L1080-1084 _function_ `uint ReadMask(uint2 In)` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L1086-1090 _function_ `void WriteMask(uint2 In, uint InValue)` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L1093-1113 _function_ `void PrintCoverage(inout FShaderPrintContext Ctx)` _[#if SHADER_RASTERCOMPUTE_RASTER && PERMUTATION_DEBUG]_
- L1115-1129 _function_ `void PrintPixelMask(inout FShaderPrintContext Ctx, uint InMask)` _[#if SHADER_RASTERCOMPUTE_RASTER && PERMUTATION_DEBUG]_
- L1131-1146 _function_ `void PrintOpaqueMask(inout FShaderPrintContext Ctx, uint2 InOpaqueMask)` _[#if SHADER_RASTERCOMPUTE_RASTER && PERMUTATION_DEBUG]_
- L1156-1159 _function_ `uint PackSampleData(FSampleData In)` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L1161-1168 _function_ `FSampleData UnpackSampleData(uint In)` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L1170-1173 _function_ `uint PackColorData(float3 In)` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L1175-1178 _function_ `float3 UnpackColorData(uint In)` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L1180-1183 _function_ `uint2 PackVelocityData(float4 In)` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L1185-1188 _function_ `float4 UnpackVelocityData(uint2 In)` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L1190-1194 _function_ `float3 LoadSampleColor(uint InPrimId, uint2 InSampleResolution)` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L1196-1201 _function_ `float4 LoadSampleVelocity(uint InPrimId)` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L1203-1210 _function_ `uint GetDepthBinIndex(float InDepth, float InvDepthExtent)` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L1213-1218 _function_ `void ShiftX(inout FShaderPrintContext Out, uint InPixelCountX)` _[#if SHADER_RASTERCOMPUTE_RASTER && PERMUTATION_DEBUG]_
- L1220-1225 _function_ `void ShiftY(inout FShaderPrintContext Out, uint InPixelCountY)` _[#if SHADER_RASTERCOMPUTE_RASTER && PERMUTATION_DEBUG]_
- L1968-2000 _function_ `uint GetTileTotalSegment(uint2 TileCoord, bool bPrintDetails, uint InTileSize)` _[#if SHADER_RASTERCOMPUTE_DEBUG]_
- L2002-2012 _function_ `void PrintTile(uint2 TileCoord, uint TotalSegments, bool bPrintText, uint InTileSize)` _[#if SHADER_RASTERCOMPUTE_DEBUG]_

### `Shaders/Private/HairStrands/HairStrandsGBufferCommon.ush` (Private)

- lines: 69; parse: all-branches
- L3 #pragma `once`

#### Functions (2)

- L6-34 _function_ `void WriteGBuffer( const float3 Tangent, const float Specular, const float3 BaseColor, const float Roughness, const float LightChannelMask, const float Backlit, const float Depth, const float2 Velocity, inout float4 OutGBufferA, inout float4 OutGBufferB, inout float4 OutGBufferC, inout float4 OutGBufferD, inout float4 OutGBufferE, inout float OutDepth, inout float4 OutVelocity)` — Utils function for writing data into GBuffer textures
- L36-69 _function_ `void WriteGBuffer( const float3 Tangent, const float Specular, const float3 BaseColor, const float Roughness, const float LightChannelMask, const float Backlit, const float Depth, inout float4 OutGBufferA, inout float4 OutGBufferB, inout float4 OutGBufferC, inout float4 OutGBufferD, inout float4 OutGBufferE, inout float OutDepth)`

### `Shaders/Private/HairStrands/HairStrandsGuideDeform.usf` (Private)

- lines: 117; parse: all-branches
- includes: L3 `../Common.ush`, L4 `HairStrandsClusterCommon.ush`, L5 `HairStrandsBindingCommon.ush`, L6 `HairStrandsVertexFactoryCommon.ush`

#### Macros (#define, 5)

- L18 `#define DEFORMATION_BYPASS 0` _[#if SHADER_DEFORM_GUIDE]_
- L19 `#define DEFORMATION_OFFSET_GUIDE 1` _[#if SHADER_DEFORM_GUIDE]_
- L20 `#define DEFORMATION_OFFSET_GUIDE_DYNAMIC 2` _[#if SHADER_DEFORM_GUIDE]_
- L21 `#define DEFORMATION_OFFSET_GUIDE_GLOBAL 3` _[#if SHADER_DEFORM_GUIDE]_
- L22 `#define DEFORMATION_OFFSET_GUIDE_BONES 4` _[#if SHADER_DEFORM_GUIDE]_

#### Entry points (1)

- L102-115 _entry_ `[numthreads(GROUP_SIZE, 1, 1)] void MainCS(uint DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FDeformGuideCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsInterpolation.cpp:391) _[#if SHADER_DEFORM_GUIDE]_

#### Global resources (textures / buffers / samplers) (12)

- L14 _resource_ `StructuredBuffer<float4> SimDeformedOffsetBuffer;` _[#if SHADER_DEFORM_GUIDE]_
- L15 _resource_ `ByteAddressBuffer SimRestPosePositionBuffer;` _[#if SHADER_DEFORM_GUIDE]_
- L16 _resource_ `RWByteAddressBuffer OutSimDeformedPositionBuffer;` _[#if SHADER_DEFORM_GUIDE]_
- L26 _resource_ `Buffer<float4> SimRestPositionBuffer;` _[#if SHADER_DEFORM_GUIDE && PERMUTATION_DEFORMATION == DEFORMATION_OFFSET_GUIDE_DYNAMIC]_
- L27 _resource_ `Buffer<float4> SimDeformedPositionBuffer;` _[#if SHADER_DEFORM_GUIDE && PERMUTATION_DEFORMATION == DEFORMATION_OFFSET_GUIDE_DYNAMIC]_
- L29 _resource_ `Buffer<uint> SimRootBarycentricBuffer;` _[#if SHADER_DEFORM_GUIDE && PERMUTATION_DEFORMATION == DEFORMATION_OFFSET_GUIDE_DYNAMIC]_
- L30 _resource_ `ByteAddressBuffer SimPointToCurveBuffer;` _[#if SHADER_DEFORM_GUIDE && PERMUTATION_DEFORMATION == DEFORMATION_OFFSET_GUIDE_DYNAMIC]_
- L31 _resource_ `Buffer<uint> SimRootToUniqueTriangleIndexBuffer;` _[#if SHADER_DEFORM_GUIDE && PERMUTATION_DEFORMATION == DEFORMATION_OFFSET_GUIDE_DYNAMIC]_
- L50 _resource_ `Buffer<float4> BoneDeformedPositionBuffer;` _[#if SHADER_DEFORM_GUIDE && PERMUTATION_DEFORMATION == DEFORMATION_OFFSET_GUIDE_BONES]_
- L58 _resource_ `StructuredBuffer<float4> RestSamplePositionsBuffer;` _[#if SHADER_DEFORM_GUIDE && PERMUTATION_DEFORMATION == DEFORMATION_OFFSET_GUIDE_GLOBAL]_
- L59 _resource_ `StructuredBuffer<float4> DeformedSamplePositionsBuffer;` _[#if SHADER_DEFORM_GUIDE && PERMUTATION_DEFORMATION == DEFORMATION_OFFSET_GUIDE_GLOBAL]_
- L60 _resource_ `StructuredBuffer<float4> MeshSampleWeightsBuffer;` _[#if SHADER_DEFORM_GUIDE && PERMUTATION_DEFORMATION == DEFORMATION_OFFSET_GUIDE_GLOBAL]_

#### Global parameters (uniforms) (5)

- L10 _parameter_ `float3 SimRestOffset;` _[#if SHADER_DEFORM_GUIDE]_
- L11 _parameter_ `uint VertexCount;` _[#if SHADER_DEFORM_GUIDE]_
- L12 _parameter_ `uint InstanceRegisteredIndex;` _[#if SHADER_DEFORM_GUIDE]_
- L56 _parameter_ `uint SampleCount;` _[#if SHADER_DEFORM_GUIDE && PERMUTATION_DEFORMATION == DEFORMATION_OFFSET_GUIDE_GLOBAL]_
- L57 _parameter_ `uint RBFLocalSpace;` _[#if SHADER_DEFORM_GUIDE && PERMUTATION_DEFORMATION == DEFORMATION_OFFSET_GUIDE_GLOBAL]_

#### Functions (2)

- L34-44 _function_ `float3 DeformGuideByTriangle( uint GuideIndex, FHairMeshBasis RestBasis, FHairMeshBasis DeformedBasis)` — Return world position of a guide vertex deformed by a skinned triangle _[#if SHADER_DEFORM_GUIDE && PERMUTATION_DEFORMATION == DEFORMATION_OFFSET_GUIDE_DYNAMIC]_
- L63-100 _function_ `float3 DisplacePosition(uint VertexIndex, float3 Pos)` _[#if SHADER_DEFORM_GUIDE]_

### `Shaders/Private/HairStrands/HairStrandsHitProxy.usf` (Private)

- lines: 78; parse: all-branches
- includes: L3 `../Common.ush`, L5 `HairStrandsVisibilityCommon.ush`

#### Entry points (1)

- L22-75 _entry_ `void EmitPS( in FScreenVertexOutput In, in float4 InPosition : SV_POSITION, out float4 OutHitProxyId : SV_Target0, out float OutDepth : SV_Depth)` — stage: **pixel (from C++ binding)** — C++: `FHairStrandsEmitDepthPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVisibility.cpp:4193) _[#if SHADER_EMIT_DEPTH]_

#### Global resources (textures / buffers / samplers) (5)

- L16 _resource_ `Buffer<uint> ActiveMaterialIdBuffer;` _[#if SHADER_EMIT_DEPTH]_
- L17 _resource_ `Texture2D<uint> VisNodeIndex;` _[#if SHADER_EMIT_DEPTH]_
- L18 _resource_ `StructuredBuffer<FPackedHairVis> VisNodeData;` _[#if SHADER_EMIT_DEPTH]_
- L19 _resource_ `Texture2D<float> CoverageTexture;` _[#if SHADER_EMIT_DEPTH]_
- L20 _resource_ `Texture2D<float> HairOnlyDepthTexture;` _[#if SHADER_EMIT_DEPTH]_

#### Global parameters (uniforms) (4)

- L12 _parameter_ `uint bDiscardIfZero;` _[#if SHADER_EMIT_DEPTH]_
- L13 _parameter_ `float CoverageThreshold;` _[#if SHADER_EMIT_DEPTH]_
- L14 _parameter_ `float2 InvViewportResolution;` _[#if SHADER_EMIT_DEPTH]_
- L15 _parameter_ `uint MaxMaterialCount;` _[#if SHADER_EMIT_DEPTH]_

#### Prototypes (1)

- L4 _prototype_ `float3 DecodeVelocityFromTexture(float4 EncodedV)`

### `Shaders/Private/HairStrands/HairStrandsInterpolation.usf` (Private)

- lines: 1048; parse: all-branches
- includes: L3 `../Common.ush`, L8 `HairStrandsBindingCommon.ush`, L9 `HairStrandsVisibilityCommon.ush`, L10 `HairStrandsAABBCommon.ush`, L11 `HairStrandsClusterCommon.ush`, L12 `HairStrandsVertexFactoryCommon.ush`, L23 `../ShaderPrint.ush` [DEBUG_ENABLE && ALLOW_DEBUG_RENDERING], L24 `../ColorMap.ush` [DEBUG_ENABLE && ALLOW_DEBUG_RENDERING], L824 `HairStrandsVertexFactoryCommon.ush` [SHADER_PATCHATTRIBUTE], L825 `HairStrandsAttributeCommon.ush` [SHADER_PATCHATTRIBUTE]

#### Macros (#define, 16)

- L6 `#define NEED_HAIR_MESH_BASIS_PADDING 1` _[#if defined(DXC_GROUPSHARED_ALIGNMENT_WORKAROUND) && DXC_GROUPSHARED_ALIGNMENT_WORKAROUND]_
- L15 `#define ALLOW_DEBUG_RENDERING 0` _[#if COMPILER_METAL \|\| COMPILER_VULKAN]_
- L17 `#define ALLOW_DEBUG_RENDERING 1` _[#if !(COMPILER_METAL \|\| COMPILER_VULKAN)]_
- L20 `#define DEBUG_ENABLE 0`
- L31 `#define DEFORMER_NONE 0`
- L32 `#define DEFORMER_ADDITIVE 1`
- L33 `#define DEFORMER_OVERWRITE 2`
- L71 `#define INTERPOLATION_RIGID 0`
- L72 `#define INTERPOLATION_SKINNING_OFFSET 1`
- L73 `#define INTERPOLATION_SKINNING_TRANSLATION 2`
- L74 `#define INTERPOLATION_SKINNING_ROTATION 3`
- L75 `#define INTERPOLATION_SKINNING_TRANSLATION_AND_ROTATION 4`
- L410 `#define TOTALMAXPOINTPERCURVE 32` _[#if SHADER_HAIRINTERPOLATION]_
- L413 `#define CURVE_PER_GROUP (GROUP_SIZE / PERMUTATION_POINT_PER_CURVE)` _[#if SHADER_HAIRINTERPOLATION]_
- L414 `#define MAX_CURVE CURVE_PER_GROUP` _[#if SHADER_HAIRINTERPOLATION]_
- L415 `#define MAX_POINT PERMUTATION_POINT_PER_CURVE` _[#if SHADER_HAIRINTERPOLATION]_
- L27 #pragma `warning (default:7203)`

#### Entry points (5)

- L439-593 _entry_ `[numthreads(GROUP_SIZE, 1, 1)] void MainCS(uint3 DispatchThreadId : SV_DispatchThreadID, uint ThreadIndex : SV_GroupIndex, uint2 GroupIndex : SV_GroupID)` — stage: **compute** — C++: `FTransferVelocityPassCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsInterpolation.cpp:222) — C++: `FGroomCacheUpdatePassCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsInterpolation.cpp:290) — C++: `FHairInterpolationCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsInterpolation.cpp:627) — C++: `FHairPatchAttributeCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsInterpolation.cpp:855) _[#if SHADER_HAIRINTERPOLATION && PERMUTATION_POINT_PER_CURVE < TOTALMAXPOINTPERCURVE]_
- L637-816 _entry_ `[numthreads(GROUP_SIZE, 1, 1)] void MainCS(uint3 DispatchThreadId : SV_DispatchThreadID, uint ThreadIndex : SV_GroupIndex, uint2 GroupIndex : SV_GroupID)` — stage: **compute** — C++: `FTransferVelocityPassCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsInterpolation.cpp:222) — C++: `FGroomCacheUpdatePassCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsInterpolation.cpp:290) — C++: `FHairInterpolationCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsInterpolation.cpp:627) — C++: `FHairPatchAttributeCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsInterpolation.cpp:855) _[#if SHADER_HAIRINTERPOLATION && PERMUTATION_POINT_PER_CURVE == TOTALMAXPOINTPERCURVE]_
- L858-908 _entry_ `[numthreads(GROUP_SIZE, 1, 1)] void MainCS(uint2 DispatchThreadId : SV_DispatchThreadID, uint GroupThread1D : SV_GroupIndex)` — stage: **compute** — C++: `FTransferVelocityPassCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsInterpolation.cpp:222) — C++: `FGroomCacheUpdatePassCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsInterpolation.cpp:290) — C++: `FHairInterpolationCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsInterpolation.cpp:627) — C++: `FHairPatchAttributeCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsInterpolation.cpp:855) _[#if SHADER_PATCHATTRIBUTE]_
- L922-930 _entry_ `[numthreads(GROUP_SIZE, 1, 1)] void MainCS(uint DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FTransferVelocityPassCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsInterpolation.cpp:222) — C++: `FGroomCacheUpdatePassCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsInterpolation.cpp:290) — C++: `FHairInterpolationCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsInterpolation.cpp:627) — C++: `FHairPatchAttributeCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsInterpolation.cpp:855) _[#if SHADER_HAIRTRANSFER_PREV_POSITION]_
- L979-1045 _entry_ `[numthreads(GROUP_SIZE, 1, 1)] void MainCS(uint DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FTransferVelocityPassCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsInterpolation.cpp:222) — C++: `FGroomCacheUpdatePassCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsInterpolation.cpp:290) — C++: `FHairInterpolationCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsInterpolation.cpp:627) — C++: `FHairPatchAttributeCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsInterpolation.cpp:855) _[#if SHADER_GROOMCACHE_UPDATE]_

#### Structs / classes (3)

- L43-50 _struct_ **`FGuideDataWithOffset`** `struct FGuideDataWithOffset`
  - L45 _member_ `uint2 RootPointIndices;`
  - L46 _member_ `uint2 PointIndices;`
  - L47 _member_ `float2 PointLerps;`
  - L48 _member_ `float2 PointWeights;`
  - L49 _member_ `float3 OutPositionOffset;`
- L133-137 _struct_ **`FGuideIndex`** `struct FGuideIndex` _[#if SHADER_HAIRINTERPOLATION]_
  - L135 _member_ `uint PointIndex;` _[#if SHADER_HAIRINTERPOLATION]_
  - L136 _member_ `uint RootPointIndex;` _[#if SHADER_HAIRINTERPOLATION]_
- L216-220 _struct_ **`FRootBasis`** `struct FRootBasis` _[#if SHADER_HAIRINTERPOLATION]_
  - L218 _member_ `FHairMeshBasis RestBasis;` _[#if SHADER_HAIRINTERPOLATION]_
  - L219 _member_ `FHairMeshBasis DeformedBasis;` _[#if SHADER_HAIRINTERPOLATION]_

#### Global resources (textures / buffers / samplers) (34)

- L39 _resource_ `ByteAddressBuffer CurveInterpolationBuffer;` _[#if SHADER_HAIRINTERPOLATION \|\| SHADER_PATCHATTRIBUTE]_
- L40 _resource_ `ByteAddressBuffer PointInterpolationBuffer;` _[#if SHADER_HAIRINTERPOLATION \|\| SHADER_PATCHATTRIBUTE]_
- L94 _resource_ `ByteAddressBuffer RenRestPosePositionBuffer;` _[#if SHADER_HAIRINTERPOLATION]_
- L95 _resource_ `ByteAddressBuffer SimRestPosePositionBuffer;` _[#if SHADER_HAIRINTERPOLATION]_
- L96 _resource_ `ByteAddressBuffer SimDeformedPositionBuffer;` _[#if SHADER_HAIRINTERPOLATION]_
- L100 _resource_ `Buffer<uint> HairStrandsVFTODO_CullingIndirectBuffer;` _[#if SHADER_HAIRINTERPOLATION && PERMUTATION_CULLING == 1]_
- L101 _resource_ `Buffer<uint> HairStrandsVFTODO_CullingIndexBuffer;` _[#if SHADER_HAIRINTERPOLATION && PERMUTATION_CULLING == 1]_
- L105 _resource_ `ByteAddressBuffer RenDeformerPositionBuffer;` _[#if SHADER_HAIRINTERPOLATION && PERMUTATION_DEFORMER]_
- L107 _resource_ `RWByteAddressBuffer OutRenDeformedPositionBuffer;` _[#if SHADER_HAIRINTERPOLATION]_
- L112 _resource_ `Buffer<float4> RenRootRestPositionBuffer;` — Compact all these buffers into 2 buffers: translation + quaternion _[#if SHADER_HAIRINTERPOLATION && PERMUTATION_DYNAMIC_GEOMETRY >= 1]_
- L113 _resource_ `Buffer<float4> RenRootDeformedPositionBuffer;` _[#if SHADER_HAIRINTERPOLATION && PERMUTATION_DYNAMIC_GEOMETRY >= 1]_
- L114 _resource_ `Buffer<uint> RenRootBarycentricBuffer;` _[#if SHADER_HAIRINTERPOLATION && PERMUTATION_DYNAMIC_GEOMETRY >= 1]_
- L115 _resource_ `Buffer<uint> RenRootToUniqueTriangleIndexBuffer;` _[#if SHADER_HAIRINTERPOLATION && PERMUTATION_DYNAMIC_GEOMETRY >= 1]_
- L117 _resource_ `Buffer<float4> SimRootRestPositionBuffer;` _[#if SHADER_HAIRINTERPOLATION && PERMUTATION_DYNAMIC_GEOMETRY >= 1]_
- L118 _resource_ `Buffer<float4> SimRootDeformedPositionBuffer;` _[#if SHADER_HAIRINTERPOLATION && PERMUTATION_DYNAMIC_GEOMETRY >= 1]_
- L119 _resource_ `Buffer<uint> SimRootBarycentricBuffer;` _[#if SHADER_HAIRINTERPOLATION && PERMUTATION_DYNAMIC_GEOMETRY >= 1]_
- L120 _resource_ `Buffer<uint> SimRootToUniqueTriangleIndexBuffer;` _[#if SHADER_HAIRINTERPOLATION && PERMUTATION_DYNAMIC_GEOMETRY >= 1]_
- L124 _resource_ `StructuredBuffer<float4> OutSimHairPositionOffsetBuffer;` _[#if SHADER_HAIRINTERPOLATION]_
- L125 _resource_ `StructuredBuffer<float4> OutRenHairPositionOffsetBuffer;` _[#if SHADER_HAIRINTERPOLATION]_
- L408 _resource_ `ByteAddressBuffer RenCurveBuffer;` _[#if SHADER_HAIRINTERPOLATION]_
- L830 _resource_ `ByteAddressBuffer RenCurveBuffer;` _[#if SHADER_PATCHATTRIBUTE]_
- L831 _resource_ `Buffer<uint> RenCurveToClusterIdBuffer;` _[#if SHADER_PATCHATTRIBUTE]_
- L832 _resource_ `RWByteAddressBuffer OutRenAttributeBuffer;` _[#if SHADER_PATCHATTRIBUTE]_
- L919 _resource_ `ByteAddressBuffer InBuffer;` _[#if SHADER_HAIRTRANSFER_PREV_POSITION]_
- L920 _resource_ `RWByteAddressBuffer OutBuffer;` _[#if SHADER_HAIRTRANSFER_PREV_POSITION]_
- L948 _resource_ `Buffer<float> InPosition0Buffer;` _[#if SHADER_GROOMCACHE_UPDATE]_
- L949 _resource_ `Buffer<float> InPosition1Buffer;` _[#if SHADER_GROOMCACHE_UPDATE]_
- L950 _resource_ `Buffer<float> InRadius0Buffer;` _[#if SHADER_GROOMCACHE_UPDATE]_
- L951 _resource_ `Buffer<float> InRadius1Buffer;` _[#if SHADER_GROOMCACHE_UPDATE]_
- L953 _resource_ `ByteAddressBuffer InRestCurveBuffer;` _[#if SHADER_GROOMCACHE_UPDATE]_
- L954 _resource_ `ByteAddressBuffer InRestPositionBuffer;` _[#if SHADER_GROOMCACHE_UPDATE]_
- L955 _resource_ `ByteAddressBuffer InRestPointToCurveBuffer;` _[#if SHADER_GROOMCACHE_UPDATE]_
- L956 _resource_ `StructuredBuffer<float4> InDeformedOffsetBuffer;` _[#if SHADER_GROOMCACHE_UPDATE]_
- L957 _resource_ `RWByteAddressBuffer OutDeformedBuffer;` _[#if SHADER_GROOMCACHE_UPDATE]_

#### Global parameters (uniforms) (33)

- L83 _parameter_ `uint DispatchCountX;` _[#if SHADER_HAIRINTERPOLATION]_
- L84 _parameter_ `uint VertexCount;` _[#if SHADER_HAIRINTERPOLATION]_
- L85 _parameter_ `uint HairDebugMode;` _[#if SHADER_HAIRINTERPOLATION]_
- L86 _parameter_ `float HairLengthScale;` _[#if SHADER_HAIRINTERPOLATION]_
- L87 _parameter_ `float3 InRenHairPositionOffset;` _[#if SHADER_HAIRINTERPOLATION]_
- L88 _parameter_ `float3 InSimHairPositionOffset;` _[#if SHADER_HAIRINTERPOLATION]_
- L89 _parameter_ `float4x4 LocalToWorldMatrix;` _[#if SHADER_HAIRINTERPOLATION]_
- L90 _parameter_ `uint bUseSingleGuide;` _[#if SHADER_HAIRINTERPOLATION]_
- L91 _parameter_ `uint SimPointCount;` _[#if SHADER_HAIRINTERPOLATION]_
- L92 _parameter_ `uint SimCurveCount;` _[#if SHADER_HAIRINTERPOLATION]_
- L98 _parameter_ `uint HairStrandsVFTODO_bCullingEnable;` _[#if SHADER_HAIRINTERPOLATION]_
- L123 _parameter_ `uint InstanceRegisteredIndex;` _[#if SHADER_HAIRINTERPOLATION]_
- L406 _parameter_ `uint CurveCount;` _[#if SHADER_HAIRINTERPOLATION]_
- L827 _parameter_ `uint CurveCount;` _[#if SHADER_PATCHATTRIBUTE]_
- L828 _parameter_ `uint bUseSingleGuide;` _[#if SHADER_PATCHATTRIBUTE]_
- L834 _parameter_ `uint CurveAttributeIndexToChunkDivAsShift;` _[#if SHADER_PATCHATTRIBUTE]_
- L835 _parameter_ `uint CurveAttributeChunkElementCount;` _[#if SHADER_PATCHATTRIBUTE]_
- L836 _parameter_ `uint CurveAttributeChunkStrideInBytes;` _[#if SHADER_PATCHATTRIBUTE]_
- L837 _parameter_ `uint PointAttributeIndexToChunkDivAsShift;` _[#if SHADER_PATCHATTRIBUTE]_
- L838 _parameter_ `uint PointAttributeChunkElementCount;` _[#if SHADER_PATCHATTRIBUTE]_
- L839 _parameter_ `uint PointAttributeChunkStrideInBytes;` _[#if SHADER_PATCHATTRIBUTE]_
- L840 _parameter_ `uint4 CurveAttributeOffsets[HAIR_CURVE_ATTRIBUTE_OFFSET_COUNT];` _[#if SHADER_PATCHATTRIBUTE]_
- L916 _parameter_ `uint PointCount;` _[#if SHADER_HAIRTRANSFER_PREV_POSITION]_
- L917 _parameter_ `uint PointOffset;` _[#if SHADER_HAIRTRANSFER_PREV_POSITION]_
- L918 _parameter_ `uint TotalPointCount;` _[#if SHADER_HAIRTRANSFER_PREV_POSITION]_
- L939 _parameter_ `uint InstanceRegisteredIndex;` _[#if SHADER_GROOMCACHE_UPDATE]_
- L940 _parameter_ `uint CachePointCount;` _[#if SHADER_GROOMCACHE_UPDATE]_
- L941 _parameter_ `uint PointCount;` _[#if SHADER_GROOMCACHE_UPDATE]_
- L942 _parameter_ `uint CurveCount;` _[#if SHADER_GROOMCACHE_UPDATE]_
- L943 _parameter_ `uint bHasRadiusData;` _[#if SHADER_GROOMCACHE_UPDATE]_
- L944 _parameter_ `uint bHasAddedControlPoint;` _[#if SHADER_GROOMCACHE_UPDATE]_
- L945 _parameter_ `float InterpolationFactor;` _[#if SHADER_GROOMCACHE_UPDATE]_
- L946 _parameter_ `float MaxHairRadius;` _[#if SHADER_GROOMCACHE_UPDATE]_

#### groupshared (13)

- L430 _groupshared_ `groupshared uint CurvePointIndex[MAX_CURVE];` _[#if SHADER_HAIRINTERPOLATION && PERMUTATION_POINT_PER_CURVE < TOTALMAXPOINTPERCURVE]_
- L431 _groupshared_ `groupshared uint CurvePointCount[MAX_CURVE];` _[#if SHADER_HAIRINTERPOLATION && PERMUTATION_POINT_PER_CURVE < TOTALMAXPOINTPERCURVE]_
- L433 _groupshared_ `groupshared FRootBasis g_RenTri[MAX_CURVE];` _[#if SHADER_HAIRINTERPOLATION && PERMUTATION_POINT_PER_CURVE < TOTALMAXPOINTPERCURVE]_
- L434 _groupshared_ `groupshared float3 RenPositionOffset;` _[#if SHADER_HAIRINTERPOLATION && PERMUTATION_POINT_PER_CURVE < TOTALMAXPOINTPERCURVE]_
- L436 _groupshared_ `groupshared FGuideCurveData SimCurveData[MAX_CURVE];` _[#if SHADER_HAIRINTERPOLATION && PERMUTATION_POINT_PER_CURVE < TOTALMAXPOINTPERCURVE]_
- L437 _groupshared_ `groupshared FRootBasis g_SimTris[MAX_CURVE][2];` _[#if SHADER_HAIRINTERPOLATION && PERMUTATION_POINT_PER_CURVE < TOTALMAXPOINTPERCURVE]_
- L624 _groupshared_ `groupshared uint CurvePointIndex;` _[#if SHADER_HAIRINTERPOLATION && PERMUTATION_POINT_PER_CURVE == TOTALMAXPOINTPERCURVE && !(PERMUTATION_WAVEOPS)]_
- L625 _groupshared_ `groupshared uint CurvePointCount;` _[#if SHADER_HAIRINTERPOLATION && PERMUTATION_POINT_PER_CURVE == TOTALMAXPOINTPERCURVE && !(PERMUTATION_WAVEOPS)]_
- L627 _groupshared_ `groupshared FRootBasis RenTri;` _[#if SHADER_HAIRINTERPOLATION && PERMUTATION_POINT_PER_CURVE == TOTALMAXPOINTPERCURVE && !(PERMUTATION_WAVEOPS)]_
- L628 _groupshared_ `groupshared float3 RenPositionOffset;` _[#if SHADER_HAIRINTERPOLATION && PERMUTATION_POINT_PER_CURVE == TOTALMAXPOINTPERCURVE && !(PERMUTATION_WAVEOPS)]_
- L630 _groupshared_ `groupshared FGuideCurveData SimCurveData;` _[#if SHADER_HAIRINTERPOLATION && PERMUTATION_POINT_PER_CURVE == TOTALMAXPOINTPERCURVE && !(PERMUTATION_WAVEOPS)]_
- L631 _groupshared_ `groupshared FRootBasis SimTris[2];` _[#if SHADER_HAIRINTERPOLATION && PERMUTATION_POINT_PER_CURVE == TOTALMAXPOINTPERCURVE && !(PERMUTATION_WAVEOPS)]_
- L842 _groupshared_ `groupshared uint SeedValues[1024];` _[#if SHADER_PATCHATTRIBUTE]_

#### Functions (22)

- L52-65 _function_ `FGuideDataWithOffset GetGuideData(FGuideCurveData InCurveData, FGuidePointData InPointData, float3 OutPositionOffset)`
- L127 _function_ `float3 GetSimPositionOffset()` _[#if SHADER_HAIRINTERPOLATION]_
- L128 _function_ `float3 GetRenPositionOffset()` _[#if SHADER_HAIRINTERPOLATION]_
- L139-145 _function_ `FGuideIndex ToGuideIndex(FGuideDataWithOffset In, uint InK, uint InOffset)` _[#if SHADER_HAIRINTERPOLATION]_
- L148-158 _function_ `float3 ComputeStaticGeometryOffset( FGuideIndex GuideIndex, float GuideVertexWeight, float3 OutSimHairPositionOffset)` _[#if SHADER_HAIRINTERPOLATION]_
- L160-169 _function_ `float3 ComputeLocalGeometryOffset( FGuideIndex GuideIndex, float GuideVertexWeight)` _[#if SHADER_HAIRINTERPOLATION]_
- L171-185 _function_ `float3 ComputeDynamicGeometryOffset( FGuideIndex GuideIndex, float GuideVertexWeight, FHairMeshBasis RestBasis, FHairMeshBasis DeformedBasis, float3 OutSimHairPositionOffset)` _[#if SHADER_HAIRINTERPOLATION]_
- L187-196 _function_ `float3 ComputeTranslateGeometryOffset( FGuideIndex GuideIndex, float GuideVertexWeight)` _[#if SHADER_HAIRINTERPOLATION]_
- L198-211 _function_ `float3 ComputeRotateGeometryOffset( FGuideIndex GuideIndex, float GuideVertexWeight, FHairMeshBasis RestBasis, FHairMeshBasis DeformedBasis)` _[#if SHADER_HAIRINTERPOLATION]_
- L222-242 _function_ `FRootBasis GetRootBasis(uint CurveIndex, bool bSim)` _[#if SHADER_HAIRINTERPOLATION]_
- L246-265 _function_ `float3 ApplyRigidInterpolation(FGuideDataWithOffset GuideData, float3 InPosition)` — Rigid interpolation _[#if SHADER_HAIRINTERPOLATION]_
- L269-295 _function_ `float3 ApplySkinningWithOffset(const FGuideDataWithOffset GuideData, const FRootBasis RenTri, const FRootBasis SimTris[2], float3 InPosition)` — Skinning with offset _[#if SHADER_HAIRINTERPOLATION]_
- L299-322 _function_ `float3 ApplySkinningWithTranslation(const FGuideDataWithOffset GuideData, const FRootBasis RenTri, float3 InPosition)` — Skinning with translantion _[#if SHADER_HAIRINTERPOLATION]_
- L326-353 _function_ `float3 ApplySkinningWithRotation(const FGuideDataWithOffset GuideData, const FRootBasis RenTri, const FRootBasis SimTris[2], float3 InPosition)` — Skinning with rotation _[#if SHADER_HAIRINTERPOLATION]_
- L357-381 _function_ `float3 ApplySkinningWithTranslationAndRotation(const FGuideDataWithOffset GuideData, const FRootBasis RenTri, const FRootBasis SimTris[2], float3 InPosition)` — Skinning with translation and rotation _[#if SHADER_HAIRINTERPOLATION]_
- L385-401 _function_ `float3 ApplyDeformer(const FRootBasis RenTri, float3 InRestPostion, float3 InDeformerPosition, float3 InDeformedPosition)` — Deformer transformation _[#if SHADER_HAIRINTERPOLATION]_
- L417-425 _function_ `uint GetGlobalCurveIndex(uint ThreadIndex, uint2 GroupIndex)` _[#if SHADER_HAIRINTERPOLATION]_
- L599-613 _function_ `FRootBasis WaveReadLaneFirstTriangle(FRootBasis In)` _[#if SHADER_HAIRINTERPOLATION && PERMUTATION_POINT_PER_CURVE == TOTALMAXPOINTPERCURVE && PERMUTATION_WAVEOPS]_
- L615-622 _function_ `FGuideCurveData WaveReadLaneFirstCurveData(FGuideCurveData In)` _[#if SHADER_HAIRINTERPOLATION && PERMUTATION_POINT_PER_CURVE == TOTALMAXPOINTPERCURVE && PERMUTATION_WAVEOPS]_
- L844-856 _function_ `uint ToSeedHash(uint In)` _[#if SHADER_PATCHATTRIBUTE]_
- L959-972 _function_ `float3 ReadCachePosition(uint InCachePointIndex)` _[#if SHADER_GROOMCACHE_UPDATE]_
- L974-977 _function_ `float ReadCacheRadius(uint InCachePointIndex)` _[#if SHADER_GROOMCACHE_UPDATE]_

#### Top-level macro invocations (1)

- L635 _macro_call_ `WAVESIZE(32)` _[#if SHADER_HAIRINTERPOLATION && PERMUTATION_POINT_PER_CURVE == TOTALMAXPOINTPERCURVE && PERMUTATION_WAVEOPS && COMPILER_SUPPORTS_WAVE_SIZE]_

### `Shaders/Private/HairStrands/HairStrandsLUT.usf` (Private)

- lines: 319; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../CommonViewUniformBuffer.ush`, L5 `../SceneTextureParameters.ush`, L6 `../DeferredShadingCommon.ush`, L7 `HairStrandsCommon.ush`, L11 `../ShadingModels.ush` [SHADER_HAIRLUT], L14 `../HairBsdf.ush` [SHADER_HAIRLUT && defined(HAIR_CUSTOM_BSDF)]

#### Macros (#define, 5)

- L17 `#define PERMUTATION_LUT_TYPE_DUALSCATTERING 0` _[#if SHADER_HAIRLUT]_
- L18 `#define PERMUTATION_LUT_TYPE_MEAN_ENERGY 1` _[#if SHADER_HAIRLUT]_
- L42 `#define TILE_PIXEL_SIZE 8` _[#if SHADER_HAIRLUT]_
- L43 `#define JITTER_VIEW 0` _[#if SHADER_HAIRLUT]_
- L304 `#define TILE_PIXEL_SIZE 8` _[#if SHADER_HAIRCOVERAGE]_

#### Entry points (3)

- L54-184 _entry_ `[numthreads(TILE_PIXEL_SIZE, TILE_PIXEL_SIZE, TILE_PIXEL_SIZE)] void MainCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FHairLUTCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsLUT.cpp:62) — C++: `FHairCoverageLUTCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsLUT.cpp:311) _[#if SHADER_HAIRLUT && PERMUTATION_LUT_TYPE == PERMUTATION_LUT_TYPE_DUALSCATTERING]_
- L193-291 _entry_ `[numthreads(TILE_PIXEL_SIZE, TILE_PIXEL_SIZE, TILE_PIXEL_SIZE)] void MainCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FHairLUTCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsLUT.cpp:62) — C++: `FHairCoverageLUTCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsLUT.cpp:311) _[#if SHADER_HAIRLUT && PERMUTATION_LUT_TYPE == PERMUTATION_LUT_TYPE_MEAN_ENERGY]_
- L306-317 _entry_ `[numthreads(TILE_PIXEL_SIZE, TILE_PIXEL_SIZE, 1)] void MainCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FHairLUTCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsLUT.cpp:62) — C++: `FHairCoverageLUTCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsLUT.cpp:311) _[#if SHADER_HAIRCOVERAGE]_

#### Global resources (textures / buffers / samplers) (4)

- L25 _resource_ `RWTexture3D<float4> Out3D;` _[#if SHADER_HAIRLUT]_
- L26 _resource_ `RWTexture2D<float4> Out2D;` _[#if SHADER_HAIRLUT]_
- L301 _resource_ `Buffer<float> InputBuffer;` _[#if SHADER_HAIRCOVERAGE]_
- L302 _resource_ `RWTexture2D<float> OutputTexture;` _[#if SHADER_HAIRCOVERAGE]_

#### Global parameters (uniforms) (6)

- L20 _parameter_ `uint AbsorptionCount;` _[#if SHADER_HAIRLUT]_
- L21 _parameter_ `uint RoughnessCount;` _[#if SHADER_HAIRLUT]_
- L22 _parameter_ `uint ThetaCount;` _[#if SHADER_HAIRLUT]_
- L23 _parameter_ `uint SampleCountScale;` _[#if SHADER_HAIRLUT]_
- L24 _parameter_ `uint3 OutputResolution;` _[#if SHADER_HAIRLUT]_
- L300 _parameter_ `int2 OutputResolution;` _[#if SHADER_HAIRCOVERAGE]_

#### Functions (3)

- L28-35 _function_ `float radicalInverse_VdC(uint bits)` _[#if SHADER_HAIRLUT]_
- L37-40 _function_ `float2 hammersley2d(uint i, uint N)` _[#if SHADER_HAIRLUT]_
- L45-50 _function_ `uint2 GetAtlasCoord2d(uint3 PixelCoord)` _[#if SHADER_HAIRLUT]_

### `Shaders/Private/HairStrands/HairStrandsLightSample.usf` (Private)

- lines: 46; parse: all-branches
- includes: L3 `../Common.ush`, L4 `HairStrandsVisibilityCommon.ush`

#### Entry points (2)

- L13-27 _entry_ `void MainVS( in uint InVertexId : SV_VertexID, out float4 OutPosition : SV_POSITION, nointerpolation out uint OutNodeCount : DISPATCH_NODECOUNT, nointerpolation out uint2 OutResolution : DISPATCH_RESOLUTION)` — stage: **vertex (from C++ binding)** — C++: `FHairLightSampleClearVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVisibility.cpp:475) _[#if SHADER_VERTEX]_
- L34-45 _entry_ `void ClearPS( float4 SVPos : SV_POSITION, uint NodeCount : DISPATCH_NODECOUNT, uint2 Resolution : DISPATCH_RESOLUTION, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FHairLightSampleClearPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVisibility.cpp:476) _[#if SHADER_CLEAR]_

#### Global resources (textures / buffers / samplers) (1)

- L11 _resource_ `StructuredBuffer<uint> HairNodeCountBuffer;` _[#if SHADER_VERTEX]_

#### Global parameters (uniforms) (1)

- L10 _parameter_ `int2 MaxViewportResolution;` _[#if SHADER_VERTEX]_

### `Shaders/Private/HairStrands/HairStrandsMaterialCommon.ush` (Private)

- lines: 282; parse: all-branches
- includes: L5 `HairStrandsVisibilityCommon.ush`, L17 `../Common.ush`, L19 `../SceneTexturesCommon.ush`, L20 `../DeferredShadingCommon.ush`, L21 `../VelocityCommon.ush`, L23 `/Engine/Generated/Material.ush`, L24 `/Engine/Generated/VertexFactory.ush`, L26 `HairStrandsVertexFactoryCommon.ush`

#### Macros (#define, 5)

- L13 `#define USE_CULLED_CLUSTER 0`
- L15 `#define USE_FORCE_TEXTURE_MIP 1`
- L16 `#define FORCED_TEXTURE_MIP 0.0f`
- L32 `#define SUPPORT_MATERIAL_PROPERTY 1`
- L41 `#define HAIR_MATERIAL_DEBUG_OUTPUT 0` _[#if !defined(HAIR_MATERIAL_DEBUG_OUTPUT)]_
- L3 #pragma `once`

#### Structs / classes (2)

- L45-49 _struct_ **`FEvaluateOutput`** `struct FEvaluateOutput` _[#if HAIR_STRAND_MESH_FACTORY]_
  - L47 _member_ `FHairSample NodeData;` _[#if HAIR_STRAND_MESH_FACTORY]_
  - L48 _member_ `float4 NodeVelocity;` _[#if HAIR_STRAND_MESH_FACTORY]_
- L51-57 _struct_ **`FHairVertexData`** `struct FHairVertexData` _[#if HAIR_STRAND_MESH_FACTORY]_
  - L53 _member_ `float3 World_P;` _[#if HAIR_STRAND_MESH_FACTORY]_
  - L54 _member_ `float3 World_P_Prev;` _[#if HAIR_STRAND_MESH_FACTORY]_
  - L55 _member_ `float Radius;` _[#if HAIR_STRAND_MESH_FACTORY]_
  - L56 _member_ `bool bIsValid;` _[#if HAIR_STRAND_MESH_FACTORY]_

#### Global parameters (uniforms) (6)

- L33 _parameter_ `uint MaterialPass_MacroGroupId;`
- L34 _parameter_ `uint MaterialPass_MaterialId;`
- L35 _parameter_ `uint MaterialPass_PrimitiveId;`
- L36 _parameter_ `uint MaterialPass_LightChannelMask;`
- L37 _parameter_ `uint MaterialPass_Flags;`
- L38 _parameter_ `float MaterialPass_HairCoverageScale;`

#### Functions (2)

- L60-82 _function_ `FVertexFactoryInterpolantsVSToPS GetInterpolants(uint PrimitiveId, uint HairControlPointId, inout FHairVertexData OutHairVertex)` — GPUCULL_TODO: this should be switched over to use Instance ID instead of Primitive ID. _[#if HAIR_STRAND_MESH_FACTORY]_
- L84-280 _function_ `FEvaluateOutput Evaluate( in float2 SamplePixelCoord, in float SampleDepth, in uint SampleControlPointId, in uint SampleCoverage8bit, in uint PrimitiveId, in bool bUpdateSampleCoverage, in bool bInterpolationEnabled)` _[#if HAIR_STRAND_MESH_FACTORY]_

#### Prototypes (1)

- L4 _prototype_ `float3 DecodeVelocityFromTexture(float4 In)`

### `Shaders/Private/HairStrands/HairStrandsMaterialPS.usf` (Private)

- lines: 59; parse: all-branches
- includes: L3 `HairStrandsMaterialCommon.ush`

#### Entry points (1)

- L5-56 _entry_ `void Main( in float4 SvPosition: SV_Position , in uint2 Resolution : DISPATCH_RESOLUTION , in uint TotalNodeCount : DISPATCH_NODE_COUNT , in uint InPrimitiveId : PRIMITIVE_ID , out float4 OutColor0 : SV_Target0 )` — stage: **pixel (from C++ binding)** — C++: `FHairMaterialPS` SF_Pixel via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVisibility.cpp:663)

### `Shaders/Private/HairStrands/HairStrandsMaterialVS.usf` (Private)

- lines: 32; parse: all-branches
- includes: L4 `HairStrandsVisibilityCommon.ush`, L5 `../Common.ush`, L6 `/Engine/Generated/Material.ush`, L7 `/Engine/Generated/VertexFactory.ush`

#### Entry points (1)

- L11-29 _entry_ `void Main( FVertexFactoryInput Input, out float4 Position : SV_POSITION, nointerpolation out uint2 OutResolution : DISPATCH_RESOLUTION, nointerpolation out uint OutTotalNodeCount : DISPATCH_NODE_COUNT, nointerpolation out uint OutPrimitiveId : PRIMITIVE_ID)` — stage: **vertex (from C++ binding)** — C++: `FHairMaterialVS` SF_Vertex via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVisibility.cpp:564) _[#if VERTEXSHADER]_

#### Prototypes (1)

- L3 _prototype_ `float3 DecodeVelocityFromTexture(float4 In)`

### `Shaders/Private/HairStrands/HairStrandsMesh.usf` (Private)

- lines: 389; parse: all-branches
- includes: L3 `../Common.ush`, L4 `HairStrandsBindingCommon.ush`, L5 `HairstrandsVertexFactoryCommon.ush`, L99 `../Common.ush` [SHADER_SAMPLE_UPDATE]

#### Macros (#define, 6)

- L48 `#define MeshPositionBuffer0 RDGMeshPositionBuffer0` _[#if SHADER_SAMPLE_INIT && !(PERMUTATION_POSITION_TYPE == 0) && PERMUTATION_POSITION_TYPE == 1]_
- L49 `#define MeshPositionBuffer1 RDGMeshPositionBuffer1` _[#if SHADER_SAMPLE_INIT && !(PERMUTATION_POSITION_TYPE == 0) && PERMUTATION_POSITION_TYPE == 1]_
- L176 `#define MeshTangentBuffer RDGMeshTangentBuffer` _[#if SHADER_MESH_UPDATE && !(PERMUTATION_POSITION_TYPE == 0)]_
- L177 `#define MeshPositionBuffer RDGMeshPositionBuffer` _[#if SHADER_MESH_UPDATE && !(PERMUTATION_POSITION_TYPE == 0)]_
- L178 `#define MeshPreviousPositionBuffer RDGMeshPreviousPositionBuffer` _[#if SHADER_MESH_UPDATE && !(PERMUTATION_POSITION_TYPE == 0)]_
- L335 `#define TEMPLATE_BUFFERS(TPrefix, TSuffix) TPrefix##Buffers_0##TSuffix; TPrefix##Buffers_1##TSuffix; TPrefix##Buffers_2##TSuffix; TPrefix##Buffers_3##TSuffix; TPrefix##Buffers_4##TSuffix; TPrefix##Buffers_5##TSuffix; TPrefix##Buffers_6##TSuffi ...` (17 lines) _[#if SHADER_RESOURCE_TRANSITION]_

#### Entry points (6)

- L23-33 _entry_ `[numthreads(128, 1, 1)] void MainHairMeshesCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FHairMeshesInterpolateCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsMeshProjection.cpp:465) _[#if SHADER_HAIRMESHES]_
- L59-88 _entry_ `[numthreads(GROUP_SIZE, 1, 1)] void MainCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FHairUpdateMeshTriangleCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsMeshProjection.cpp:218) — C++: `FHairInitMeshSamplesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsMeshProjection.cpp:599) — C++: `FHairUpdateMeshSamplesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsMeshProjection.cpp:719) — C++: `FHairUpdatePositionOffsetCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsMeshProjection.cpp:1110) — C++: `FHairResourceTransitionPass` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsUtils.cpp:438) _[#if SHADER_SAMPLE_INIT]_
- L110-133 _entry_ `[numthreads(128, 1, 1)] void MainCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FHairUpdateMeshTriangleCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsMeshProjection.cpp:218) — C++: `FHairInitMeshSamplesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsMeshProjection.cpp:599) — C++: `FHairUpdateMeshSamplesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsMeshProjection.cpp:719) — C++: `FHairUpdatePositionOffsetCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsMeshProjection.cpp:1110) — C++: `FHairResourceTransitionPass` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsUtils.cpp:438) _[#if SHADER_SAMPLE_UPDATE]_
- L239-281 _entry_ `[numthreads(GROUP_SIZE, 1, 1)] void MainCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FHairUpdateMeshTriangleCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsMeshProjection.cpp:218) — C++: `FHairInitMeshSamplesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsMeshProjection.cpp:599) — C++: `FHairUpdateMeshSamplesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsMeshProjection.cpp:719) — C++: `FHairUpdatePositionOffsetCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsMeshProjection.cpp:1110) — C++: `FHairResourceTransitionPass` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsUtils.cpp:438) _[#if SHADER_MESH_UPDATE]_
- L315-325 _entry_ `[numthreads(1, 1, 1)] void MainCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FHairUpdateMeshTriangleCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsMeshProjection.cpp:218) — C++: `FHairInitMeshSamplesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsMeshProjection.cpp:599) — C++: `FHairUpdateMeshSamplesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsMeshProjection.cpp:719) — C++: `FHairUpdatePositionOffsetCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsMeshProjection.cpp:1110) — C++: `FHairResourceTransitionPass` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsUtils.cpp:438) _[#if SHADER_OFFSET_UPDATE]_
- L365-386 _entry_ `[numthreads(1, 1, 1)] void MainCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FHairUpdateMeshTriangleCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsMeshProjection.cpp:218) — C++: `FHairInitMeshSamplesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsMeshProjection.cpp:599) — C++: `FHairUpdateMeshSamplesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsMeshProjection.cpp:719) — C++: `FHairUpdatePositionOffsetCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsMeshProjection.cpp:1110) — C++: `FHairResourceTransitionPass` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsUtils.cpp:438) _[#if SHADER_RESOURCE_TRANSITION]_

#### Structs / classes (1)

- L146-155 _struct_ **`FMeshSectionData`** `struct FMeshSectionData` _[#if SHADER_MESH_UPDATE]_
  - L148 _member_ `uint MaxIndexCount;` _[#if SHADER_MESH_UPDATE]_
  - L149 _member_ `uint MaxVertexCount;` _[#if SHADER_MESH_UPDATE]_
  - L150 _member_ `uint IndexOffset;` _[#if SHADER_MESH_UPDATE]_
  - L151 _member_ `uint UVsChannelOffset;` _[#if SHADER_MESH_UPDATE]_
  - L152 _member_ `uint UVsChannelCount;` _[#if SHADER_MESH_UPDATE]_
  - L153 _member_ `uint bIsSwapped;` _[#if SHADER_MESH_UPDATE]_
  - L154 _member_ `uint bUseFaceNormal;` _[#if SHADER_MESH_UPDATE]_

#### Global resources (textures / buffers / samplers) (32)

- L16 _resource_ `StructuredBuffer<float4> RestSamplePositionsBuffer;` _[#if SHADER_HAIRMESHES]_
- L17 _resource_ `StructuredBuffer<float4> MeshSampleWeightsBuffer;` _[#if SHADER_HAIRMESHES]_
- L18 _resource_ `StructuredBuffer<float4> DeformedSamplePositionsBuffer;` _[#if SHADER_HAIRMESHES]_
- L20 _resource_ `Buffer<float4> RestPositionBuffer;` _[#if SHADER_HAIRMESHES]_
- L21 _resource_ `RWBuffer<float4> OutDeformedPositionBuffer;` _[#if SHADER_HAIRMESHES]_
- L43 _resource_ `Buffer<float> MeshPositionBuffer0;` _[#if SHADER_SAMPLE_INIT && PERMUTATION_POSITION_TYPE == 0]_
- L44 _resource_ `Buffer<float> MeshPositionBuffer1;` _[#if SHADER_SAMPLE_INIT && PERMUTATION_POSITION_TYPE == 0]_
- L46 _resource_ `Buffer<float> RDGMeshPositionBuffer0;` _[#if SHADER_SAMPLE_INIT && !(PERMUTATION_POSITION_TYPE == 0) && PERMUTATION_POSITION_TYPE == 1]_
- L47 _resource_ `Buffer<float> RDGMeshPositionBuffer1;` _[#if SHADER_SAMPLE_INIT && !(PERMUTATION_POSITION_TYPE == 0) && PERMUTATION_POSITION_TYPE == 1]_
- L55 _resource_ `Buffer<uint> SampleIndicesAndSectionsBuffer;` _[#if SHADER_SAMPLE_INIT]_
- L56 _resource_ `StructuredBuffer<uint> MeshSectionBuffer;` _[#if SHADER_SAMPLE_INIT]_
- L57 _resource_ `RWStructuredBuffer<float4> OutSamplePositionsBuffer;` _[#if SHADER_SAMPLE_INIT]_
- L103 _resource_ `StructuredBuffer<float> InterpolationWeightsBuffer;` _[#if SHADER_SAMPLE_UPDATE]_
- L105 _resource_ `StructuredBuffer<float4> SampleRestPositionsBuffer;` _[#if SHADER_SAMPLE_UPDATE]_
- L106 _resource_ `StructuredBuffer<float4> SampleDeformedPositionsBuffer;` _[#if SHADER_SAMPLE_UPDATE]_
- L108 _resource_ `RWStructuredBuffer<float4> OutSampleDeformationsBuffer;` _[#if SHADER_SAMPLE_UPDATE]_
- L160 _resource_ `Buffer<uint> MeshIndexBuffer;` _[#if SHADER_MESH_UPDATE]_
- L161 _resource_ `Buffer<uint> UniqueTriangleIndices;` _[#if SHADER_MESH_UPDATE]_
- L162 _resource_ `StructuredBuffer<uint4> MeshSectionBuffer;` _[#if SHADER_MESH_UPDATE]_
- L169 _resource_ `Buffer<float4> MeshTangentBuffer;` _[#if SHADER_MESH_UPDATE && PERMUTATION_POSITION_TYPE == 0]_
- L170 _resource_ `Buffer<float> MeshPositionBuffer;` _[#if SHADER_MESH_UPDATE && PERMUTATION_POSITION_TYPE == 0]_
- L171 _resource_ `Buffer<float> MeshPreviousPositionBuffer;` _[#if SHADER_MESH_UPDATE && PERMUTATION_POSITION_TYPE == 0]_
- L173 _resource_ `Buffer<float4> RDGMeshTangentBuffer;` _[#if SHADER_MESH_UPDATE && !(PERMUTATION_POSITION_TYPE == 0)]_
- L174 _resource_ `Buffer<float> RDGMeshPositionBuffer;` _[#if SHADER_MESH_UPDATE && !(PERMUTATION_POSITION_TYPE == 0)]_
- L175 _resource_ `Buffer<float> RDGMeshPreviousPositionBuffer;` _[#if SHADER_MESH_UPDATE && !(PERMUTATION_POSITION_TYPE == 0)]_
- L181 _resource_ `RWBuffer<float4> OutUniqueTriangleCurrPosition;` _[#if SHADER_MESH_UPDATE]_
- L183 _resource_ `RWBuffer<float4> OutUniqueTrianglePrevPosition;` _[#if SHADER_MESH_UPDATE && PERMUTATION_PREVIOUS]_
- L291 _resource_ `Buffer<float4> RootTriangleCurrPositionBuffer;` _[#if SHADER_OFFSET_UPDATE && PERMUTATION_USE_GPU_OFFSET]_
- L295 _resource_ `Buffer<float4> RootTrianglePrevPositionBuffer;` _[#if SHADER_OFFSET_UPDATE && PERMUTATION_USE_GPU_OFFSET && PERMUTATION_PREVIOUS]_
- L306 _resource_ `RWStructuredBuffer<float4> OutCurrOffsetBuffer;` _[#if SHADER_OFFSET_UPDATE]_
- L308 _resource_ `RWStructuredBuffer<float4> OutPrevOffsetBuffer;` _[#if SHADER_OFFSET_UPDATE && PERMUTATION_PREVIOUS]_
- L359 _resource_ `RWStructuredBuffer<uint> DummyOutput;` _[#if SHADER_RESOURCE_TRANSITION]_

#### Global parameters (uniforms) (20)

- L12 _parameter_ `uint VertexCount;` _[#if SHADER_HAIRMESHES]_
- L13 _parameter_ `uint MaxSampleCount;` _[#if SHADER_HAIRMESHES]_
- L14 _parameter_ `uint RBFLocalSpace;` _[#if SHADER_HAIRMESHES]_
- L52 _parameter_ `uint MaxSectionCount;` _[#if SHADER_SAMPLE_INIT]_
- L53 _parameter_ `uint MaxVertexCount;` _[#if SHADER_SAMPLE_INIT]_
- L54 _parameter_ `uint MaxSampleCount;` _[#if SHADER_SAMPLE_INIT]_
- L101 _parameter_ `uint MaxSampleCount;` _[#if SHADER_SAMPLE_UPDATE]_
- L102 _parameter_ `uint RBFLocalSpace;` _[#if SHADER_SAMPLE_UPDATE]_
- L157 _parameter_ `uint TangentFormat;` _[#if SHADER_MESH_UPDATE]_
- L158 _parameter_ `uint MaxSectionCount;` _[#if SHADER_MESH_UPDATE]_
- L159 _parameter_ `uint MaxUniqueTriangleCount;` _[#if SHADER_MESH_UPDATE]_
- L299 _parameter_ `float3 CPUCurrPositionOffset;` _[#if SHADER_OFFSET_UPDATE && !(PERMUTATION_USE_GPU_OFFSET)]_
- L300 _parameter_ `float3 CPUPrevPositionOffset;` _[#if SHADER_OFFSET_UPDATE && !(PERMUTATION_USE_GPU_OFFSET)]_
- L311 _parameter_ `uint UpdateType;` _[#if SHADER_OFFSET_UPDATE]_
- L312 _parameter_ `uint CardLODIndex;` _[#if SHADER_OFFSET_UPDATE]_
- L313 _parameter_ `uint InstanceRegisteredIndex;` _[#if SHADER_OFFSET_UPDATE]_
- L360 _parameter_ `uint DummyValue;` _[#if SHADER_RESOURCE_TRANSITION]_
- L361 _parameter_ `uint NumVertexUint;` _[#if SHADER_RESOURCE_TRANSITION]_
- L362 _parameter_ `uint NumVertexUint4;` _[#if SHADER_RESOURCE_TRANSITION]_
- L363 _parameter_ `uint NumVertexFloat4;` _[#if SHADER_RESOURCE_TRANSITION]_

#### Functions (7)

- L186-199 _function_ `FMeshSectionData ReadMeshSectionData(uint InSectionIndex)` _[#if SHADER_MESH_UPDATE]_
- L201-230 _function_ `FHairMeshTriangle GetHairMeshTriangle(uint InTriangleIndex, FMeshSectionData MeshSectionData, bool bPrevious, bool bUseVertexTangent)` _[#if SHADER_MESH_UPDATE]_
- L232-237 _function_ `float3 GetTriangleFaceNormal(FHairMeshTriangle Tri)` _[#if SHADER_MESH_UPDATE]_
- L292 _function_ `float3 GetOffsetCurrPosition()` _[#if SHADER_OFFSET_UPDATE && PERMUTATION_USE_GPU_OFFSET]_
- L296 _function_ `float3 GetOffsetPrevPosition()` _[#if SHADER_OFFSET_UPDATE && PERMUTATION_USE_GPU_OFFSET && PERMUTATION_PREVIOUS]_
- L302 _function_ `float3 GetOffsetCurrPosition()` _[#if SHADER_OFFSET_UPDATE && !(PERMUTATION_USE_GPU_OFFSET)]_
- L303 _function_ `float3 GetOffsetPrevPosition()` _[#if SHADER_OFFSET_UPDATE && !(PERMUTATION_USE_GPU_OFFSET)]_

#### Top-level macro invocations (5)

- L353 _macro_call_ `TEMPLATE_BUFFERS(StructuredBuffer<float4> Structured, )` _[#if SHADER_RESOURCE_TRANSITION]_
- L354 _macro_call_ `TEMPLATE_BUFFERS(Buffer<uint> VertexUInt, )` _[#if SHADER_RESOURCE_TRANSITION]_
- L355 _macro_call_ `TEMPLATE_BUFFERS(Buffer<uint4> VertexUInt4, )` _[#if SHADER_RESOURCE_TRANSITION]_
- L356 _macro_call_ `TEMPLATE_BUFFERS(Buffer<float4> VertexFloat4, )` _[#if SHADER_RESOURCE_TRANSITION]_
- L357 _macro_call_ `TEMPLATE_BUFFERS(ByteAddressBuffer ByteAddress, )` _[#if SHADER_RESOURCE_TRANSITION]_

### `Shaders/Private/HairStrands/HairStrandsPack.ush` (Private)

- lines: 542; parse: all-branches
- includes: L5 `/Engine/Public/Platform.ush`, L6 `/Engine/Private/PackUnpack.ush`, L7 `/Engine/Shared/HairStrandsDefinitions.h`
- L3 #pragma `once`

#### Structs / classes (6)

- L34-40 _struct_ **`FHairControlPoint`** `struct FHairControlPoint`
  - L36 _member_ `float3 Position;`
  - L37 _member_ `float WorldRadius;`
  - L38 _member_ `float UCoord;`
  - L39 _member_ `uint Type;`
- L260-265 _struct_ **`FGuideCurveData`** `struct FGuideCurveData`
  - L262 _member_ `uint2 CurveIndices;` — Index of the sim curve
  - L263 _member_ `float2 CurveWeights;` — Weight of the sim curve
  - L264 _member_ `uint2 RootPointIndices;` — Index of the first/root point of the sim curve (stored to avoid indirect fetch on CurveBuffer)
- L299-303 _struct_ **`FGuidePointData`** `struct FGuidePointData`
  - L301 _member_ `uint2 PointIndices;`
  - L302 _member_ `float2 PointLerps;`
- L344-348 _struct_ **`FCardsGuideData`** `struct FCardsGuideData`
  - L346 _member_ `uint VertexIndex;`
  - L347 _member_ `float VertexLerp;`
- L363-367 _struct_ **`FHairCurve`** `struct FHairCurve`
  - L365 _member_ `uint PointIndex;`
  - L366 _member_ `uint PointCount;`
- L492-496 _struct_ **`FHairTriangleIndex`** `struct FHairTriangleIndex`
  - L494 _member_ `uint TriangleIndex;`
  - L495 _member_ `uint SectionIndex;`

#### Functions (54)

- L12-15 _function_ `FPackedHairPosition ReadPackedHairPosition(ByteAddressBuffer InBuffer, uint InPointIndex)`
- L17-20 _function_ `void WritePackedHairPosition(RWByteAddressBuffer InBuffer, uint InPointIndex, FPackedHairPosition In)`
- L22-26 _function_ `void CopyPackedAttribute(inout FPackedHairPosition Out, in FPackedHairPosition In)`
- L28-32 _function_ `void CopyPackedHairControlPoint(RWByteAddressBuffer OutBuffer, ByteAddressBuffer InBuffer, uint Index)`
- L42-56 _function_ `FPackedHairPosition PackHairControlPoint( FHairControlPoint CP, float3 InVF_PositionOffset, float InVF_Radius)`
- L58-73 _function_ `FHairControlPoint UnpackHairControlPoint( FPackedHairPosition In, float3 InVF_PositionOffset=0, float InVF_Radius=1, float InVF_RootScale=1, float InVF_TipScale=1)`
- L75-89 _function_ `FHairControlPoint ReadHairControlPoint( ByteAddressBuffer InBuffer, uint InIndex, float3 InVF_PositionOffset=0, float InVF_Radius=1, float InVF_RootScale=1, float InVF_TipScale=1)`
- L91-105 _function_ `FHairControlPoint ReadHairControlPoint( RWByteAddressBuffer InBuffer, uint InIndex, float3 InVF_PositionOffset=0, float InVF_Radius=1, float InVF_RootScale=1, float InVF_TipScale=1)`
- L107-115 _function_ `void WriteHairControlPointPosition( RWByteAddressBuffer OutBuffer, uint InIndex, FHairControlPoint InCP, float3 InVF_PositionOffset=0, float InVF_Radius=1)`
- L117-120 _function_ `float UnpackHairControlPointCoordU(FPackedHairPosition In)`
- L122-125 _function_ `float3 UnpackHairControlPointPosition(FPackedHairPosition In, float3 InVF_PositionOffset=0)`
- L127-130 _function_ `float3 ReadHairControlPointPosition(ByteAddressBuffer InBuffer, uint InPointIndex, float3 InVF_PositionOffset=0)`
- L132-135 _function_ `float3 ReadHairControlPointPosition(RWByteAddressBuffer InBuffer, uint InPointIndex, float3 InVF_PositionOffset=0)`
- L137-145 _function_ `FPackedHairPosition PackHairControlPointPosition(FPackedHairPosition InPackedData, float3 InNewPosition, float3 InPositionOffset=0)`
- L147-150 _function_ `void WritePackedHairControlPointPosition(RWByteAddressBuffer OutBuffer, uint InIndex, FPackedHairPosition InPackedData, float3 InNewPosition, float3 InPositionOffset=0)`
- L152-159 _function_ `FPackedHairPosition PackHairControlPointRadius(FPackedHairPosition InPackedData, float InNewWorldRadius, float InVFRadius)`
- L161-164 _function_ `bool IsValidHairStrandsSegment(const FHairControlPoint CP0, const FHairControlPoint CP1)`
- L169-175 _function_ `uint PackHairRootUV(float2 In)`
- L177-189 _function_ `float2 UnpackHairRootUV(uint In)`
- L191-194 _function_ `float UnpackHairLength(uint In)`
- L196-199 _function_ `uint PackHairSeed(float In)`
- L201-204 _function_ `float UnpackHairSeed(uint In)`
- L206-209 _function_ `uint PackHairClumpID(uint In)`
- L211-214 _function_ `uint3 UnpackHairClumpID(uint In)`
- L216-219 _function_ `uint3 UnpackHairClumpID(uint2 In)`
- L221-226 _function_ `uint PackHairColor(float3 In)`
- L228-235 _function_ `float3 UnpackHairColor(uint In)`
- L237-240 _function_ `uint PackHairRoughness(float In)`
- L242-245 _function_ `float UnpackHairRoughness(uint In)`
- L247-250 _function_ `uint PackHairAO(float In)`
- L252-255 _function_ `float UnpackHairAO(uint In)`
- L267-297 _function_ `FGuideCurveData UnpackGuideCurveData(ByteAddressBuffer InBuffer, uint InCurveIndex, bool bUseSingleGuide)`
- L305-338 _function_ `FGuidePointData UnpackGuidePointData(ByteAddressBuffer InBuffer, uint InPointIndex, bool bUseSingleGuide)`
- L350-358 _function_ `FCardsGuideData ReadCardGuideData(ByteAddressBuffer InBuffer, uint InVertexId)`
- L369-376 _function_ `uint PackHairCurve(FHairCurve In)`
- L378-388 _function_ `FHairCurve UnpackHairCurve(uint In)`
- L390-393 _function_ `FHairCurve ReadHairCurve(ByteAddressBuffer InBuffer, uint InIndex)`
- L395-398 _function_ `void WriteHairCurve(RWByteAddressBuffer InBuffer, uint InIndex, FHairCurve In)`
- L400-414 _function_ `uint ReadHairPointToCurveIndex(ByteAddressBuffer InBuffer, uint InPointIndex)`
- L419-422 _function_ `uint PackUVs(float2 UV)`
- L424-427 _function_ `float PackUVsToFloat(float2 UV)`
- L429-435 _function_ `float2 UnPackUVs(uint InUV)`
- L437-440 _function_ `float2 UnPackUVs(float InUV)`
- L445-451 _function_ `uint PackVertexNormal(float3 In)`
- L453-456 _function_ `float PackVertexNormalToFloat(float3 In)`
- L458-465 _function_ `float3 UnpackVertexNormal(uint In)`
- L467-470 _function_ `float3 UnpackVertexNormal(float In)`
- L475-478 _function_ `uint PackBarycentrics(float2 B)`
- L480-487 _function_ `float3 UnpackBarycentrics(uint E)`
- L498-501 _function_ `uint PackTriangleIndex(uint TriangleIndex, uint SectionIndex)`
- L503-509 _function_ `FHairTriangleIndex UnpackTriangleIndex(uint Encoded)`
- L515-523 _function_ `uint ReadHairSourceCurveIndex(ByteAddressBuffer InBuffer, uint InIndex, bool bIsBufferValid)`
- L525-533 _function_ `uint ReadHairSourcePointIndex(ByteAddressBuffer InBuffer, uint InIndex, bool bIsBufferValid)`
- L534-542 _function_ `uint ReadHairSourceAttributeIndex(ByteAddressBuffer InBuffer, uint InIndex, bool bIsBufferValid)`

### `Shaders/Private/HairStrands/HairStrandsRaytracing.ush` (Private)

- lines: 111; parse: all-branches
- includes: L11 `../HairStrands/HairStrandsVoxelPageCommon.ush`, L12 `../HairStrands/HairStrandsVoxelPageTraversal.ush`

#### Macros (#define, 2)

- L6 `#define VOXEL_TRAVERSAL_DEBUG 0` _[#if !defined(VOXEL_TRAVERSAL_DEBUG)]_
- L8 `#define VOXEL_TRAVERSAL_TYPE VOXEL_TRAVERSAL_LINEAR_MIPMAP`
- L3 #pragma `once`

#### Functions (3)

- L16-77 _function_ `float InternalTraverseHair(uint2 PixelCoord, float3 RayOrigin, float3 RayDirection, float InMinT, float InOcclusionThreshold, float3 VoxelRandom, float RayRandom)` — RayOrigin is in translated world space
- L79-86 _function_ `float TraverseHair(uint2 PixelCoord, float3 RayOrigin, float3 RayDirection, float InMinT, float InOcclusionThreshold)`
- L88-111 _function_ `float TraverseHair(uint2 PixelCoord, inout FRandomSequence RandSequence, float3 RayOrigin, float3 RayDirection, float InMinT, float InOcclusionThreshold)`

### `Shaders/Private/HairStrands/HairStrandsRaytracingGeometry.usf` (Private)

- lines: 483; parse: all-branches
- includes: L3 `../Common.ush`, L4 `HairStrandsClusterCommon.ush`, L5 `HairStrandsVertexFactoryCommon.ush`, L356 `../ShaderPrint.ush` [SHADER_POSITION_CHANGED], L357 `HairStrandsAABBCommon.ush` [SHADER_POSITION_CHANGED]

#### Macros (#define, 3)

- L12 `#define PRIMITIVE_TYPE_PROCEDURAL 0` _[#if SHADER_RT_GEOMETRY]_
- L13 `#define PRIMITIVE_TYPE_TRIANGLE 1` _[#if SHADER_RT_GEOMETRY]_
- L14 `#define PRIMITIVE_TYPE_LINEAR_SWEPT_SPHERE 2` _[#if SHADER_RT_GEOMETRY]_

#### Entry points (2)

- L166-348 _entry_ `[numthreads(GROUP_SIZE, 1, 1)] void MainCS(uint DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FHairRaytracingGeometryCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsInterpolation.cpp:1347) — C++: `FHairStrandsPositionChangedCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVisibility.cpp:4389) _[#if SHADER_RT_GEOMETRY]_
- L379-480 _entry_ `[numthreads(GROUP_SIZE, 1, 1)] void MainCS(uint2 DispatchThreadId : SV_DispatchThreadID, uint LinearIndex : SV_GroupIndex)` — stage: **compute** — C++: `FHairRaytracingGeometryCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsInterpolation.cpp:1347) — C++: `FHairStrandsPositionChangedCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVisibility.cpp:4389) _[#if SHADER_POSITION_CHANGED]_

#### Global resources (textures / buffers / samplers) (15)

- L23 _resource_ `StructuredBuffer<float4> PositionOffsetBuffer;` _[#if SHADER_RT_GEOMETRY]_
- L24 _resource_ `ByteAddressBuffer PositionBuffer;` _[#if SHADER_RT_GEOMETRY]_
- L25 _resource_ `Buffer<float4> TangentBuffer;` _[#if SHADER_RT_GEOMETRY]_
- L26 _resource_ `RWBuffer<float4> OutputPositionBuffer;` _[#if SHADER_RT_GEOMETRY]_
- L30 _resource_ `RWStructuredBuffer<uint> OutputIndexBuffer;` _[#if SHADER_RT_GEOMETRY && !(PRIMITIVE_TYPE == PRIMITIVE_TYPE_PROCEDURAL)]_
- L35 _resource_ `Buffer<uint> HairStrandsVF_CullingIndirectBuffer;` _[#if SHADER_RT_GEOMETRY && PERMUTATION_CULLING == 1]_
- L36 _resource_ `Buffer<uint> HairStrandsVF_CullingIndexBuffer;` _[#if SHADER_RT_GEOMETRY && PERMUTATION_CULLING == 1]_
- L37 _resource_ `Buffer<uint> HairStrandsVF_CullingIndirectBufferArgs;` _[#if SHADER_RT_GEOMETRY && PERMUTATION_CULLING == 1]_
- L369 _resource_ `Buffer<uint> HairStrandsVF_CullingIndirectBuffer;` _[#if SHADER_POSITION_CHANGED]_
- L370 _resource_ `Buffer<uint> HairStrandsVF_CullingIndexBuffer;` _[#if SHADER_POSITION_CHANGED]_
- L371 _resource_ `ByteAddressBuffer CurrPositionBuffer;` _[#if SHADER_POSITION_CHANGED]_
- L372 _resource_ `ByteAddressBuffer PrevPositionBuffer;` _[#if SHADER_POSITION_CHANGED]_
- L373 _resource_ `Buffer<int> GroupAABBBuffer;` _[#if SHADER_POSITION_CHANGED]_
- L374 _resource_ `RWBuffer<uint> InvalidationBuffer;` _[#if SHADER_POSITION_CHANGED]_
- L375 _resource_ `RWBuffer<uint> InvalidationPrintCounter;` _[#if SHADER_POSITION_CHANGED]_

#### Global parameters (uniforms) (12)

- L16 _parameter_ `uint PointCount;` _[#if SHADER_RT_GEOMETRY]_
- L18 _parameter_ `float HairStrandsVF_HairRadius;` _[#if SHADER_RT_GEOMETRY]_
- L19 _parameter_ `float HairStrandsVF_HairRootScale;` _[#if SHADER_RT_GEOMETRY]_
- L20 _parameter_ `float HairStrandsVF_HairTipScale;` _[#if SHADER_RT_GEOMETRY]_
- L22 _parameter_ `uint HairStrandsVF_RegisteredIndex;` _[#if SHADER_RT_GEOMETRY]_
- L28 _parameter_ `uint RaytracingProceduralSplits;` _[#if SHADER_RT_GEOMETRY && PRIMITIVE_TYPE == PRIMITIVE_TYPE_PROCEDURAL]_
- L33 _parameter_ `uint HairStrandsVF_bCullingEnable;` _[#if SHADER_RT_GEOMETRY]_
- L363 _parameter_ `uint InstanceResgisteredIndex;` _[#if SHADER_POSITION_CHANGED]_
- L364 _parameter_ `uint PointCount;` _[#if SHADER_POSITION_CHANGED]_
- L365 _parameter_ `uint bDrawInvalidElement;` _[#if SHADER_POSITION_CHANGED]_
- L366 _parameter_ `float PositionThreshold2;` _[#if SHADER_POSITION_CHANGED]_
- L368 _parameter_ `uint HairStrandsVF_bCullingEnable;` _[#if SHADER_POSITION_CHANGED]_

#### groupshared (1)

- L377 _groupshared_ `groupshared uint s_InvalidMask[GROUP_SIZE];` _[#if SHADER_POSITION_CHANGED]_

#### Functions (8)

- L40-56 _function_ `FHairControlPoint GetControlPoint(uint ControlPointId)` _[#if SHADER_RT_GEOMETRY]_
- L58-64 _function_ `float3x3 GetTangentBasis(uint ControlPointId)` _[#if SHADER_RT_GEOMETRY]_
- L67-71 _function_ `void SetAABB(uint InVertexIndex, float3 Lo, float3 Hi)` _[#if SHADER_RT_GEOMETRY && PRIMITIVE_TYPE == PRIMITIVE_TYPE_PROCEDURAL]_
- L75-96 _function_ `void SetInvalidSegment(uint InVertexIndex)` — a whole segment of invalid values _[#if SHADER_RT_GEOMETRY]_
- L99-123 _function_ `void SetCapSegment(uint InVertexIndex)` — TODO: this is not used at the moment _[#if SHADER_RT_GEOMETRY]_
- L126-149 _function_ `void SetBodySegment(uint InVertexIndex)` _[#if SHADER_RT_GEOMETRY && PRIMITIVE_TYPE == PRIMITIVE_TYPE_TRIANGLE]_
- L153-159 _function_ `float GetAABBHalfAreaForSegment(float4 A, float4 B)` _[#if SHADER_RT_GEOMETRY]_
- L161-164 _function_ `bool IsValidPosition(FHairControlPoint P)` _[#if SHADER_RT_GEOMETRY]_

### `Shaders/Private/HairStrands/HairStrandsScreenTracing.ush` (Private)

- lines: 74; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../BlueNoise.ush`, L5 `../SSRT/SSRTRayCast.ush`, L6 `../HZB.ush`

#### Global parameters (uniforms) (1)

- L8 _parameter_ `float ScreenTraceLength;`

#### Functions (2)

- L10-58 _function_ `float GetRayVisibility(float3 TranslatedWorldPosition,float SceneDepth, float3 RayDirection, uint2 PixelCoord, uint PixelRayIndex, uint NumPixelSamples, bool bJitter)`
- L60-73 _function_ `float ComputeScreenTraceHairCount( const uint2 PixelCoord, const float PixelRadius, const float SceneDepth, float3 TranslatedWorldPosition, float3 SampleDirection, uint SampleIt=0, uint SampleCount=1, bool bJitter = true)`

### `Shaders/Private/HairStrands/HairStrandsSkinUpdate.usf` (Private)

- lines: 121; parse: all-branches
- includes: L5 `/Engine/Public/Platform.ush`, L6 `../GpuSkinCommon.ush`
- L3 #pragma `once`

#### Entry points (1)

- L54-119 _entry_ `[numthreads(GROUP_SIZE,1,1)] void UpdateSkinPositionCS(uint3 GroupID : SV_GroupID, uint3 DispatchThreadID : SV_DispatchThreadID, uint3 GroupThreadID : SV_GroupThreadID)` — stage: **compute** — C++: `FSkinUpdateCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsMeshProjection.cpp:82) _[#if SHADER_SKIN_UPDATE]_

#### Global resources (textures / buffers / samplers) (7)

- L25 _resource_ `Buffer<uint> WeightLookup;` _[#if SHADER_SKIN_UPDATE]_
- L26 _resource_ `Buffer<uint> VertexWeights;` _[#if SHADER_SKIN_UPDATE]_
- L27 _resource_ `Buffer<float> RestPositions;` _[#if SHADER_SKIN_UPDATE]_
- L28 _resource_ `Buffer<SNORM float4> RestTangents;` _[#if SHADER_SKIN_UPDATE]_
- L32 _resource_ `RWBuffer<float> DeformedPositions;` _[#if SHADER_SKIN_UPDATE]_
- L33 _resource_ `RWBuffer<TANGENT_RWBUFFER_FORMAT> DeformedTangents;` — GL does not support SNORM images, so instead we write to SINT _[#if SHADER_SKIN_UPDATE]_
- L38 _resource_ `RWBuffer<float> PrevDeformedPositions;` _[#if SHADER_SKIN_UPDATE && PERMUTATION_PREV]_

#### Global parameters (uniforms) (11)

- L11 _parameter_ `uint bWriteTangent;` _[#if SHADER_SKIN_UPDATE]_
- L12 _parameter_ `uint WeightIndexSize;` — bone index size: 1 - 8bit or 2 - 16bit _[#if SHADER_SKIN_UPDATE]_
- L13 _parameter_ `uint SectionVertexBaseIndex;` _[#if SHADER_SKIN_UPDATE]_
- L14 _parameter_ `uint NumTotalVertices;` _[#if SHADER_SKIN_UPDATE]_
- L15 _parameter_ `uint NumVertexToProcess;` _[#if SHADER_SKIN_UPDATE]_
- L16 _parameter_ `uint WeightStride;` _[#if SHADER_SKIN_UPDATE]_
- L17 _parameter_ `uint TangentFormat;` _[#if SHADER_SKIN_UPDATE]_
- L22 _parameter_ `uint BoneTransformOffset;` — Bone transform offset (supports both per-section buffers and shared scene skinning buffer). When using per-section bone buffers (skin cache), offset is 0. When using the scene skinning extension's shared buffer, offset indexes into the correct region. _[#if SHADER_SKIN_UPDATE]_
- L23 _parameter_ `uint PrevBoneTransformOffset;` _[#if SHADER_SKIN_UPDATE]_
- L31 _parameter_ `FCompressedBoneTransformBuffer BoneMatrices;` — Current Position _[#if SHADER_SKIN_UPDATE]_
- L37 _parameter_ `FCompressedBoneTransformBuffer PrevBoneMatrices;` _[#if SHADER_SKIN_UPDATE && PERMUTATION_PREV]_

#### Functions (1)

- L41-50 _function_ `FComputeBoneMatrixInputs MakeBoneInputs(FCompressedBoneTransformBuffer InBoneMatrices, uint InBoneTransformOffset)` _[#if SHADER_SKIN_UPDATE]_

### `Shaders/Private/HairStrands/HairStrandsTangent.usf` (Private)

- lines: 105; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../MonteCarlo.ush`, L5 `HairStrandsPack.ush`, L6 `HairStrandsClusterCommon.ush`

#### Entry points (1)

- L27-104 _entry_ `[numthreads(GROUP_SIZE, 1, 1)] void MainCS(uint DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FHairTangentCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsInterpolation.cpp:1224) _[#if SHADER_TANGENT]_

#### Global resources (textures / buffers / samplers) (5)

- L11 _resource_ `ByteAddressBuffer PositionBuffer;` _[#if SHADER_TANGENT]_
- L12 _resource_ `RWBuffer<float4> OutputTangentBuffer;` _[#if SHADER_TANGENT]_
- L17 _resource_ `Buffer<uint> HairStrandsVF_CullingIndirectBuffer;` _[#if SHADER_TANGENT && PERMUTATION_CULLING == 1]_
- L18 _resource_ `Buffer<uint> HairStrandsVF_CullingIndexBuffer;` _[#if SHADER_TANGENT && PERMUTATION_CULLING == 1]_
- L19 _resource_ `Buffer<uint> IndirectBufferArgs;` _[#if SHADER_TANGENT && PERMUTATION_CULLING == 1]_

#### Global parameters (uniforms) (2)

- L9 _parameter_ `uint PointCount;` _[#if SHADER_TANGENT]_
- L14 _parameter_ `uint HairStrandsVF_bCullingEnable;` _[#if SHADER_TANGENT]_

#### Functions (1)

- L22-25 _function_ `float4 PackNormal(float3 V, uint A)` _[#if SHADER_TANGENT]_

### `Shaders/Private/HairStrands/HairStrandsTexturesGeneration.usf` (Private)

- lines: 939; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../MonteCarlo.ush`, L6 `HairStrandsVisibilityCommon.ush`, L7 `HairCardsTextureCommon.ush`, L11 `../ShaderPrint.ush` [DEBUG_ENABLE], L170 `HairStrandsVertexFactoryCommon.ush` [SHADER_COMPUTE], L171 `HairStrandsAttributeCommon.ush` [SHADER_COMPUTE], L172 `HairCardsAttributeCommon.ush` [SHADER_COMPUTE], L176 `HairStrandsAttributeCommon.ush` [SHADER_COMPUTE], L178 `/Engine/Private/HairStrands/HairStrandsAttributeTemplate.ush` [SHADER_COMPUTE], L723 `HairCardsAttributeCommon.ush` [SHADER_TEXTURE_DILATION], L859 `HairStrandsVertexFactoryCommon.ush` [SHADER_READ_POSITIONS], L883 `HairCardsAttributeCommon.ush` [SHADER_TEXTURE_CLEAR]

#### Macros (#define, 5)

- L9 `#define DEBUG_ENABLE 0`
- L43 `#define WriteValue1(InLayout, InAttribute, In) { if (IsHairCardTextureIndexValid(InLayout, InAttribute)) { const uint TexIndex = GetHairCardTextureIndex(InLayout, InAttribute); const uint ChannelIndex = GetHairCardChannelIndex(InLayout, InAttribut ...` (17 lines)
- L60 `#define WriteValue2(InLayout, InAttribute, In) { if (IsHairCardTextureIndexValid(InLayout, InAttribute)) { const uint TexIndex = GetHairCardTextureIndex(InLayout, InAttribute); const uint ChannelIndex = GetHairCardChannelIndex(InLayout, InAttribut ...` (17 lines)
- L77 `#define WriteValue3(InLayout, InAttribute, In) { if (IsHairCardTextureIndexValid(InLayout, InAttribute)) { const uint TexIndex = GetHairCardTextureIndex(InLayout, InAttribute); switch (TexIndex) { case 0: OutTexture0.xyz = In; break; case 1: OutTe ...` (16 lines)
- L177 `#define HAIR_STRANDS_ATTRIBUTE_ACCESSORS(Name) InVF_##Name` _[#if SHADER_COMPUTE]_

#### Entry points (7)

- L109-136 _entry_ `void MainVS( uint VertexId : SV_VertexID, out float4 UVPosition : SV_POSITION, out float2 OutUV : MESH_UV, out float3 OutPosition : MESH_POSITION, out float3 OutTangent : MESH_TANGENT, out float3 OutBitangent : MESH_BITANGENT, out float3 OutNormal : MESH_NORMAL)` — stage: **vertex (from C++ binding)** — C++: `FHairStrandsTextureVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomTextureBuilder.cpp:733) _[#if SHADER_VERTEX]_
- L141-165 _entry_ `void MainPS( in float4 SvPosition : SV_Position, in float2 InUV : MESH_UV, in float3 InPosition : MESH_POSITION, in float3 InTangent : MESH_TANGENT, in float3 InBitangent : MESH_BITANGENT, in float3 InNormal : MESH_NORMAL, out float4 OutPosition : SV_Target0, out float4 OutTangent : SV_Target1, out float4 OutBitangent : SV_Target2, out float4 OutNormal : SV_Target3, out float2 OutUV : SV_Target4, out uint OutTriangleMask : SV_Target5)` — stage: **pixel (from C++ binding)** — C++: `FHairStrandsTexturePS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomTextureBuilder.cpp:734) _[#if SHADER_PIXEL]_
- L557-716 _entry_ `[numthreads(8, 8, 1)] void MainCS( uint GroupIndex : SV_GroupIndex, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FHairStrandTextureClearCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomTextureBuilder.cpp:489) — C++: `FHairStrandTextureCopyCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomTextureBuilder.cpp:538) — C++: `FHairStrandTextureDilationCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomTextureBuilder.cpp:598) — C++: `FHairStrandsTextureCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomTextureBuilder.cpp:793) — C++: `FHairStrandCopyPositionCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomBuilder.cpp:4056) _[#if SHADER_COMPUTE]_
- L741-852 _entry_ `[numthreads(8, 8, 1)] void MainCS(int2 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FHairStrandTextureClearCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomTextureBuilder.cpp:489) — C++: `FHairStrandTextureCopyCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomTextureBuilder.cpp:538) — C++: `FHairStrandTextureDilationCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomTextureBuilder.cpp:598) — C++: `FHairStrandsTextureCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomTextureBuilder.cpp:793) — C++: `FHairStrandCopyPositionCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomBuilder.cpp:4056) — Dilate the source texture (Depth/Coverage/Tanget/Attribute), using a distance to triangle edge metric. Original valid pixel are marked into the triangleMasktexture during the texture generation. Then successive dilation pass are run. At each pass the triangleMaskTexure stored the distance to triangle edge in order to propagate correctly the pixel edge information. _[#if SHADER_TEXTURE_DILATION]_
- L865-876 _entry_ `[numthreads(128, 1, 1)] void MainCS(int2 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FHairStrandTextureClearCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomTextureBuilder.cpp:489) — C++: `FHairStrandTextureCopyCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomTextureBuilder.cpp:538) — C++: `FHairStrandTextureDilationCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomTextureBuilder.cpp:598) — C++: `FHairStrandsTextureCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomTextureBuilder.cpp:793) — C++: `FHairStrandCopyPositionCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomBuilder.cpp:4056) _[#if SHADER_READ_POSITIONS]_
- L888-918 _entry_ `[numthreads(8, 8, 1)] void MainCS(int2 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FHairStrandTextureClearCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomTextureBuilder.cpp:489) — C++: `FHairStrandTextureCopyCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomTextureBuilder.cpp:538) — C++: `FHairStrandTextureDilationCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomTextureBuilder.cpp:598) — C++: `FHairStrandsTextureCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomTextureBuilder.cpp:793) — C++: `FHairStrandCopyPositionCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomBuilder.cpp:4056) _[#if SHADER_TEXTURE_CLEAR]_
- L930-938 _entry_ `[numthreads(8, 8, 1)] void MainCS(int2 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FHairStrandTextureClearCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomTextureBuilder.cpp:489) — C++: `FHairStrandTextureCopyCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomTextureBuilder.cpp:538) — C++: `FHairStrandTextureDilationCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomTextureBuilder.cpp:598) — C++: `FHairStrandsTextureCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomTextureBuilder.cpp:793) — C++: `FHairStrandCopyPositionCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomBuilder.cpp:4056) _[#if SHADER_TEXTURE_COPY]_

#### Global resources (textures / buffers / samplers) (28)

- L105 _resource_ `Buffer<float> VertexBuffer;` _[#if SHADER_VERTEX]_
- L106 _resource_ `Buffer<float4> NormalsBuffer;` _[#if SHADER_VERTEX]_
- L107 _resource_ `Buffer<float2> UVsBuffer;` _[#if SHADER_VERTEX]_
- L205 _resource_ `Buffer<float> VertexBuffer;` _[#if SHADER_COMPUTE]_
- L206 _resource_ `Buffer<float4> NormalsBuffer;` _[#if SHADER_COMPUTE]_
- L207 _resource_ `Buffer<float2> UVsBuffer;` _[#if SHADER_COMPUTE]_
- L220 _resource_ `StructuredBuffer<uint2> Voxel_OffsetAndCount;` _[#if SHADER_COMPUTE]_
- L221 _resource_ `StructuredBuffer<uint2> Voxel_Data;` _[#if SHADER_COMPUTE]_
- L222 _resource_ `RWTexture2DArray<float4> OutTexture;` _[#if SHADER_COMPUTE]_
- L224 _resource_ `Texture2D<float4> PositionTexture;` _[#if SHADER_COMPUTE]_
- L225 _resource_ `Texture2D<float4> TangentTexture;` _[#if SHADER_COMPUTE]_
- L226 _resource_ `Texture2D<float4> BitangentTexture;` _[#if SHADER_COMPUTE]_
- L227 _resource_ `Texture2D<float4> NormalTexture;` _[#if SHADER_COMPUTE]_
- L228 _resource_ `Texture2D<float2> UVTexture;` _[#if SHADER_COMPUTE]_
- L727 _resource_ `uint TextureCount;` _[#if SHADER_TEXTURE_DILATION]_
- L730 _resource_ `Texture2D<float> DepthTestTexture;` _[#if SHADER_TEXTURE_DILATION]_
- L731 _resource_ `Texture2D<uint> OriginalTriangleMaskTexture;` _[#if SHADER_TEXTURE_DILATION]_
- L732 _resource_ `Texture2D<uint> SourceTriangleMaskTexture;` _[#if SHADER_TEXTURE_DILATION]_
- L733 _resource_ `RWTexture2D<uint> TargetTriangleMaskTexture;` _[#if SHADER_TEXTURE_DILATION]_
- L734 _resource_ `Texture2DArray<float4> SourceTexture;` _[#if SHADER_TEXTURE_DILATION]_
- L735 _resource_ `RWTexture2DArray<float4> TargetTexture;` _[#if SHADER_TEXTURE_DILATION]_
- L862 _resource_ `ByteAddressBuffer InPositions;` _[#if SHADER_READ_POSITIONS]_
- L863 _resource_ `Buffer<float4> InPositionOffset;` _[#if SHADER_READ_POSITIONS]_
- L864 _resource_ `RWBuffer<float4> OutPositions;` _[#if SHADER_READ_POSITIONS]_
- L886 _resource_ `RWTexture2DArray<float4> OutTexture;` _[#if SHADER_TEXTURE_CLEAR]_
- L925 _resource_ `uint TextureIndex;` _[#if SHADER_TEXTURE_COPY]_
- L927 _resource_ `Texture2DArray<float4> InTexture;` _[#if SHADER_TEXTURE_COPY]_
- L928 _resource_ `RWTexture2D<float4> OutTexture;` _[#if SHADER_TEXTURE_COPY]_

#### Global parameters (uniforms) (29)

- L98 _parameter_ `int2 OutputResolution;` _[#if SHADER_VERTEX]_
- L99 _parameter_ `uint VertexCount;` _[#if SHADER_VERTEX]_
- L100 _parameter_ `uint PrimitiveCount;` _[#if SHADER_VERTEX]_
- L102 _parameter_ `uint UVsChannelIndex;` _[#if SHADER_VERTEX]_
- L103 _parameter_ `uint UVsChannelCount;` _[#if SHADER_VERTEX]_
- L197 _parameter_ `int2 TileSize;` _[#if SHADER_COMPUTE]_
- L198 _parameter_ `int2 TileOffsetInPixels;` _[#if SHADER_COMPUTE]_
- L199 _parameter_ `uint LayoutIndex;` _[#if SHADER_COMPUTE]_
- L200 _parameter_ `int2 OutputResolution;` _[#if SHADER_COMPUTE]_
- L201 _parameter_ `uint VertexCount;` _[#if SHADER_COMPUTE]_
- L202 _parameter_ `uint PrimitiveCount;` _[#if SHADER_COMPUTE]_
- L203 _parameter_ `uint bHasMaterialData;` _[#if SHADER_COMPUTE]_
- L209 _parameter_ `float MaxDistance;` _[#if SHADER_COMPUTE]_
- L210 _parameter_ `int TracingDirection;` _[#if SHADER_COMPUTE]_
- L212 _parameter_ `float3 Voxel_MinBound;` _[#if SHADER_COMPUTE]_
- L213 _parameter_ `float3 Voxel_MaxBound;` _[#if SHADER_COMPUTE]_
- L214 _parameter_ `int3 Voxel_Resolution;` _[#if SHADER_COMPUTE]_
- L215 _parameter_ `float Voxel_Size;` _[#if SHADER_COMPUTE]_
- L216 _parameter_ `uint Voxel_MaxSegmentPerVoxel;` _[#if SHADER_COMPUTE]_
- L217 _parameter_ `uint Voxel_OffsetAndCount_MaxCount;` _[#if SHADER_COMPUTE]_
- L218 _parameter_ `uint Voxel_Data_MaxCount;` _[#if SHADER_COMPUTE]_
- L725 _parameter_ `uint LayoutIndex;` _[#if SHADER_TEXTURE_DILATION]_
- L726 _parameter_ `uint bClearPass;` _[#if SHADER_TEXTURE_DILATION]_
- L728 _parameter_ `int2 Resolution;` _[#if SHADER_TEXTURE_DILATION]_
- L729 _parameter_ `int ClearDistance;` _[#if SHADER_TEXTURE_DILATION]_
- L861 _parameter_ `uint MaxVertexCount;` _[#if SHADER_READ_POSITIONS]_
- L884 _parameter_ `int2 Resolution;` _[#if SHADER_TEXTURE_CLEAR]_
- L885 _parameter_ `uint LayoutIndex;` _[#if SHADER_TEXTURE_CLEAR]_
- L926 _parameter_ `int2 Resolution;` _[#if SHADER_TEXTURE_COPY]_

#### Functions (9)

- L21-31 _function_ `void AssignValue1(inout float4 OutTexture, uint ChannelIndex, float Value)`
- L33-41 _function_ `void AssignValue2(inout float4 OutTexture, uint ChannelIndex, float2 Value)`
- L180-188 _function_ `float3 ComputeTangent( const FHairControlPoint CP0, const FHairControlPoint CP1, const FHairControlPoint CP2)` _[#if SHADER_COMPUTE]_
- L190-195 _function_ `float3 ComputeTangent( const FHairControlPoint CP0, const FHairControlPoint CP1)` _[#if SHADER_COMPUTE]_
- L230-236 _function_ `uint3 PositionToCoord(float3 P, float3 InMinAABB, float3 InMaxAABB, uint3 InResolution)` _[#if SHADER_COMPUTE]_
- L238-245 _function_ `uint CoordToIndex(uint3 InCoord, uint3 InResolution, uint LinearOffset)` _[#if SHADER_COMPUTE]_
- L248-286 _function_ `bool ClipRaySegment(float3 AABBMin, float3 AABBMax, float4 P0, float4 P1, out float2 T, out bool3 bClipped)` _[#if SHADER_COMPUTE]_
- L288-322 _function_ `bool ClipRaySegment(float3 AABBMin, float3 AABBMax, inout float4 P0, inout float4 P1, inout float Rad0, inout float Rad1, out bool3 bClipped)` _[#if SHADER_COMPUTE]_
- L324-555 _function_ `bool Trace( float3 InRayO, float3 InRayD, float InMaxDistance, float InPixelRadius, bool bDebugEnable, inout float OutDepth, inout float OutCoverage, inout float3 OutTangent, inout float2 OutRootUV, inout float OutU, inout float OutSeed, inout float4 OutMaterial)` _[#if SHADER_COMPUTE]_

#### Top-level macro invocations (1)

- L174 _macro_call_ `HAIR_STRANDS_INSTANCE_PARAMETERS(InVF)` _[#if SHADER_COMPUTE]_

### `Shaders/Private/HairStrands/HairStrandsTileCommon.ush` (Private)

- lines: 13; parse: all-branches

#### Macros (#define, 6)

- L6 `#define HAIR_TILE_SIZE 8`
- L9 `#define HAIRTILE_HAIR_ALL 0`
- L10 `#define HAIRTILE_HAIR_FULL 1`
- L11 `#define HAIRTILE_HAIR_PARTIAL 2`
- L12 `#define HAIRTILE_OTHER 3`
- L13 `#define HAIRTILE_COUNT 4`
- L3 #pragma `once`

### `Shaders/Private/HairStrands/HairStrandsTranscode.usf` (Private)

- lines: 130; parse: first-branch (retry, +0 merged from all-branches pass)
- includes: L5 `/Engine/Private/Common.ush`, L6 `/Engine/Shared/HairStrandsDefinitions.h`, L7 `../PackUnpack.ush`, L8 `HairStrandsPack.ush`
- L3 #pragma `once`

#### Entry points (1)

- L54-116 _entry_ `[numthreads(GROUP_SIZE, 1, 1)] void MainCS(uint ThreadIndex : SV_DispatchThreadID)` — stage: **compute** — C++: `FHairTranscodeCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/GroomResources.cpp:313) _[#if SHADER_TRANSCODE]_

#### Global resources (textures / buffers / samplers) (2)

- L22 _resource_ `ByteAddressBuffer InBuffer;` _[#if SHADER_TRANSCODE]_
- L23 _resource_ `RWByteAddressBuffer OutBuffer;` _[#if SHADER_TRANSCODE]_

#### Global parameters (uniforms) (7)

- L12 _parameter_ `uint OffsetInBytes;` _[#if SHADER_TRANSCODE]_
- L13 _parameter_ `uint DataSizeInBytes;` _[#if SHADER_TRANSCODE]_
- L14 _parameter_ `uint TotalSizeInBytes;` _[#if SHADER_TRANSCODE]_
- L16 _parameter_ `uint UncompressedOffsetInBytes;` _[#if SHADER_TRANSCODE]_
- L17 _parameter_ `uint UncompressedTotalSizeInBytes;` _[#if SHADER_TRANSCODE]_
- L19 _parameter_ `float3 PositionScale;` _[#if SHADER_TRANSCODE]_
- L20 _parameter_ `float3 PositionOffset;` _[#if SHADER_TRANSCODE]_

#### Functions (4)

- L29 _function_ `float UnpackR7(uint In)` _[#if SHADER_TRANSCODE]_
- L30 _function_ `float UnpackR2(uint In)` _[#if SHADER_TRANSCODE]_
- L32-42 _function_ `FHairControlPoint UnpackTranscoodedPosition(uint In)` _[#if SHADER_TRANSCODE]_
- L44-52 _function_ `void UnpackUCoord(inout FHairControlPoint InCP, uint DataW0, uint DataW1, inout uint bFirst)` _[#if SHADER_TRANSCODE]_

### `Shaders/Private/HairStrands/HairStrandsVelocity.usf` (Private)

- lines: 145; parse: all-branches
- includes: L5 `../Common.ush`, L6 `HairStrandsVisibilityCommon.ush`, L7 `HairStrandsTileCommon.ush`

#### Macros (#define, 6)

- L9 `#define TILE_PIXEL_SIZE_X 8`
- L10 `#define TILE_PIXEL_SIZE_Y 8`
- L27 `#define VELOCITY_TYPE_NONE 0`
- L28 `#define VELOCITY_TYPE_AVG 1`
- L29 `#define VELOCITY_TYPE_CLOSEST 2`
- L30 `#define VELOCITY_TYPE_MAX 3`
- L3 #pragma `once`

#### Entry points (1)

- L52-144 _entry_ `[numthreads(TILE_PIXEL_SIZE_X, TILE_PIXEL_SIZE_Y, 1)] void MainCS(uint3 DispatchThreadId : SV_DispatchThreadID, uint2 InGroupId : SV_GroupID, uint2 InGroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FHairVelocityCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVisibility.cpp:1340)

#### Global resources (textures / buffers / samplers) (9)

- L22 _resource_ `Texture2D<uint> NodeIndex;`
- L23 _resource_ `Buffer<float4> NodeVelocity;`
- L24 _resource_ `StructuredBuffer<FPackedHairVis> NodeVis;`
- L25 _resource_ `Texture2D<float> CoverageTexture;`
- L33 _resource_ `RWTexture2D<float2> OutVelocityTexture;` _[#if PERMUTATION_VELOCITY != VELOCITY_TYPE_NONE && PERMUTATION_OUTPUT_FORMAT == 0]_
- L35 _resource_ `RWTexture2D<float4> OutVelocityTexture;` _[#if PERMUTATION_VELOCITY != VELOCITY_TYPE_NONE && !(PERMUTATION_OUTPUT_FORMAT == 0)]_
- L41 _resource_ `Buffer<uint> TileCountBuffer;`
- L42 _resource_ `Buffer<uint2> TileDataBuffer;`
- L44 _resource_ `RWTexture2D<uint> OutResolveMaskTexture;`

#### Global parameters (uniforms) (7)

- L16 _parameter_ `int2 Resolution;`
- L17 _parameter_ `int2 ResolutionOffset;`
- L18 _parameter_ `float VelocityThreshold;`
- L19 _parameter_ `float CoverageThreshold;`
- L20 _parameter_ `uint bNeedClear;`
- L39 _parameter_ `uint TileSize;`
- L40 _parameter_ `int2 TileCountXY;`

#### Functions (2)

- L47 _function_ `float2 ToOutput(float4 In)` _[#if PERMUTATION_OUTPUT_FORMAT == 0]_
- L49 _function_ `float4 ToOutput(float4 In)` _[#if !(PERMUTATION_OUTPUT_FORMAT == 0)]_

### `Shaders/Private/HairStrands/HairStrandsVertexFactory.ush` (Private)

- lines: 1025; parse: all-branches
- includes: L6 `../VertexFactoryCommon.ush`, L7 `../LocalVertexFactoryCommon.ush`, L8 `HairStrandsVisibilityCommon.ush`, L9 `HairStrandsVertexFactoryCommon.ush`, L10 `HairStrandsAttributeCommon.ush`, L12 `/Engine/Generated/UniformBuffers/PrecomputedLightingBuffer.ush`, L1024 `/Engine/Private/VertexFactoryDefaultInterface.ush`

#### Macros (#define, 4)

- L14 `#define USE_HAIR_COMPLEX_TRANSMITTANCE 1`
- L20 `#define ENABLE_HAIRSTRANDS_TRIANGLE_INTERSECTOR !(ENABLE_HAIRSTRANDS_LINEAR_SWEPT_SPHERE_INTERSECTOR \|\| ENABLE_HAIRSTRANDS_PROCEDURAL_INTERSECTOR)`
- L31 `#define USE_CULLED_CLUSTER 1` _[#if !defined(USE_CULLED_CLUSTER)]_
- L583 `#define VF_SUPPORTS_RAYTRACING_PREPARE_MATERIAL_PIXEL_PARAMETERS 1` _[#if RAYHITGROUPSHADER]_

#### Entry points (1)

- L509-575 _entry_ `RAY_TRACING_ENTRY_INTERSECTION(MaterialIS)` — stage: **intersection** _[#if RAYHITGROUPSHADER && USE_MATERIAL_INTERSECTION_SHADER]_

#### Structs / classes (4)

- L87-106 _struct_ **`FVertexFactoryInput`** `struct FVertexFactoryInput`
  - L90 _member_ `float4 Position;` _[#if RAYHITGROUPSHADER]_
  - L91 _member_ `uint PrimitiveId;` — from RayHit (either TriangleId or SegmendId) _[#if RAYHITGROUPSHADER]_
  - L94 _member_ `uint PrimitiveVertexId;` — 0,1,2 (Vertex within the triangle) _[#if RAYHITGROUPSHADER && ENABLE_HAIRSTRANDS_TRIANGLE_INTERSECTOR]_
  - L105 _member_ `uint VertexId : SV_VertexID;`
- L108-117 _struct_ **`FVertexInfo`** `struct FVertexInfo`
  - L110 _member_ `uint VertexIndex;`
  - L111 _member_ `uint HairControlPointId;`
  - L112 _member_ `uint IsTip;` — The vertex is on the quad side toward the tip of the strand.
  - L114 _member_ `uint IsLeft;` _[#if !RAYHITGROUPSHADER]_
  - L115 _member_ `bool bForceInvalidQuad;` _[#if !RAYHITGROUPSHADER]_
- L240-251 _struct_ **`FVertexFactoryIntermediates`** `struct FVertexFactoryIntermediates` — Caches intermediates that would otherwise have to be computed multiple times.  Avoids relying on the compiler to optimize out redundant operations.
  - L242 _member_ `half3x3 TangentToLocal;`
  - L243 _member_ `half3x3 TangentToWorld;`
  - L244 _member_ `half TangentToWorldSign;`
  - L245 _member_ `uint HairControlPointId;`
  - L246 _member_ `float2 HairPrimitiveUV;`
  - L247 _member_ `float2 HairDimensions;` — This is kept on the intermediate as this is used in several vertex shader for the actual coverage.
  - L248 _member_ `float HairDensity;`
  - L250 _member_ `FSceneDataIntermediates SceneData;` — Cached primitive and instance data
- L945-948 _struct_ **`FVertexFactoryRayTracingInterpolants`** `struct FVertexFactoryRayTracingInterpolants` _[#if NEEDS_VERTEX_FACTORY_INTERPOLATION]_
  - L947 _member_ `FVertexFactoryInterpolantsVSToPS InterpolantsVSToPS;` _[#if NEEDS_VERTEX_FACTORY_INTERPOLATION]_

#### Global resources (textures / buffers / samplers) (2)

- L23 _resource_ `Buffer<float4> VertexFetch_InstanceOriginBuffer;` _[#if MANUAL_VERTEX_FETCH]_
- L24 _resource_ `Buffer<float4> VertexFetch_InstanceTransformBuffer;` _[#if MANUAL_VERTEX_FETCH]_

#### Functions (57)

- L77-80 _function_ `bool UseStableRasterization()` — Per-vertex inputs from bound vertex buffers
- L82-85 _function_ `bool UseScatterSceneLighting()`
- L118-168 _function_ `FVertexInfo GetVertexInfo(FVertexFactoryInput Input)`
- L170-176 _function_ `float3 RotateLocalHairTangent(float3 In)`
- L180-191 _function_ `half3x3 AssembleTangentToWorldForHairStrand(half3 TangentToWorld0, half4 TangentToWorld2)` — Unlike AssembleTangentToWorld, this helper first adjusts the TangentToWorld0 direction using TangentToWorld2 to ensure they are perpendicular before constructing the matrix.
- L196-234 _function_ `FVertexFactoryInput LoadVertexFactoryInputForHGS(uint PrimitiveIndex, int VertexIndex)` _[#if RAYHITGROUPSHADER]_
- L253-256 _function_ `float3 GetPositionOffset()`
- L258-261 _function_ `float3 GetPrevPositionOffset()`
- L263-266 _function_ `uint GetHairControlPointId(FVertexFactoryInput Input)`
- L268-292 _function_ `FHairControlPoint GetVertexPosition(const FVertexInfo VertexInfo, bool bInvalidJointVertex=true)`
- L294-298 _function_ `FHairControlPoint GetVertexPosition(FVertexFactoryInput Input, bool bInvalidJointVertex=true)`
- L300-303 _function_ `float GetWorldStrandRadius(FVertexFactoryInput Input)`
- L305-330 _function_ `float3 GetVertexPreviousPosition(FVertexFactoryInput Input, bool bInvalidJointVertex = true)`
- L333-343 _function_ `float2 GetSegmentUVCoord(FVertexFactoryInput Input)` — Segment UV coord of an hair segment. This is different from the UV coord of the hair strands
- L346-366 _function_ `FMaterialPixelParameters GetMaterialPixelParameters(FVertexFactoryInterpolantsVSToPS Interpolants, float4 SvPosition)` — Converts from vertex factory specific interpolants to a FMaterialPixelParameters, which is used by material inputs.
- L368-376 _function_ `half3x3 CalcTangentToWorldNoScale(FPrimitiveSceneData SceneData, half3x3 TangentToLocal)`
- L379-382 _function_ `float3 VertexFactoryGetPreviousInstanceSpacePosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)`
- L387-412 _function_ `FMaterialVertexParameters GetMaterialVertexParameters( FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, float3 WorldPosition, float3 PositionInstanceSpace, half3x3 TangentToLocal, bool bIsPreviousFrame = false)` — Converts from vertex factory specific input to a FMaterialVertexParameters, which is used by vertex shader material inputs.
- L414-432 _function_ `FMaterialVertexParameters GetMaterialVertexParameters( FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, float3 WorldPosition, half3x3 TangentToLocal, FHairViewInfo HairInfo, bool bIsPreviousFrame = false)`
- L434-451 _function_ `FMaterialVertexParameters GetMaterialVertexParameters( FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, float3 WorldPosition, half3x3 TangentToLocal, bool bIsPreviousFrame = false)`
- L453-456 _function_ `float4 CalcWorldPosition(float3 Position, FDFMatrix LocalToWorld)`
- L458-479 _function_ `half3x3 CalcTangentToLocal(uint VertexIndex, inout float TangentSign)`
- L481-485 _function_ `half3x3 CalcTangentToLocal(FVertexFactoryInput Input, inout float TangentSign)`
- L487-490 _function_ `half3x3 CalcTangentToWorld(FPrimitiveSceneData SceneData, half3x3 TangentToLocal)`
- L492-499 _function_ `float3 GetTangent(FVertexFactoryIntermediates Intermediates)`
- L585-692 _function_ `FMaterialPixelParameters GetMaterialPixelParameters(float3 RayOrigin, float3 RayDirection, float HitT, uint HitPrimitiveIndex, uint HitClusterID, FRayTracingIntersectionAttributes HitAttributes, uint HitKind, float4 SvPosition, out float3 WorldGeoNormal)` _[#if RAYHITGROUPSHADER]_
- L699-713 _function_ `FVertexFactoryIntermediates GetVertexFactoryIntermediates(FVertexFactoryInput Input)`
- L722-725 _function_ `half3x3 VertexFactoryGetTangentToLocal( FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates )` — Get the 3x3 tangent basis vectors for this vertex factory this vertex factory will calculate the binormal on-the-fly @param Input - vertex input stream structure @return 3x3 matrix
- L729-732 _function_ `float4 VertexFactoryGetWorldPosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)` _[#if RAYHITGROUPSHADER]_
- L734-737 _function_ `float3 VertexFactoryGetInstanceSpacePosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)` _[#if RAYHITGROUPSHADER]_
- L741-754 _function_ `float4 ComputeViewAlignedWorldPosition(FVertexFactoryInput Input, float3 WorldTangent, float4 WorldPosition, float WorldStrandRadius, FHairViewInfo HairViewInfo)` _[#if !(RAYHITGROUPSHADER)]_
- L758-777 _function_ `float4 VertexFactoryGetWorldPosition_Visibility(FVertexFactoryInput Input, FHairViewInfo HairViewInfo, inout uint OutHairControlPointId)` — @return translated world position Specialized version of VertexFactoryGetWorldPosition & ComputeViewAlignedWorldPosition, for visibility VS shader. _[#if !(RAYHITGROUPSHADER)]_
- L781-799 _function_ `float4 VertexFactoryGetWorldPosition_Voxelization(FVertexFactoryInput Input, FHairViewInfo HairViewInfo, inout float OutHairWorldRadius, inout float OutHairDensity)` — @return translated world position Specialized version of VertexFactoryGetWorldPosition & ComputeViewAlignedWorldPosition, for voxelization VS shader. _[#if !(RAYHITGROUPSHADER)]_
- L802-811 _function_ `float4 VertexFactoryGetWorldPosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, FHairViewInfo HairViewInfo)` — @return translated world position _[#if !(RAYHITGROUPSHADER)]_
- L813-819 _function_ `float3 VertexFactoryGetInstanceSpacePosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, FHairViewInfo HairViewInfo)` _[#if !(RAYHITGROUPSHADER)]_
- L822-833 _function_ `float4 VertexFactoryGetWorldPosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)` — This function is referenced by several "system" shaders, but none of these shaders (apart HitProxy, are actually used) _[#if !(RAYHITGROUPSHADER)]_
- L835-841 _function_ `float3 VertexFactoryGetInstanceSpacePosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)` _[#if !(RAYHITGROUPSHADER)]_
- L844-847 _function_ `float4 VertexFactoryGetRasterizedWorldPosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, float4 InWorldPosition)`
- L849-852 _function_ `float3 VertexFactoryGetPositionForVertexLighting(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, float3 TranslatedWorldPosition)`
- L854-869 _function_ `FVertexFactoryInterpolantsVSToPS VertexFactoryGetInterpolantsVSToPS(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, FMaterialVertexParameters VertexParameters)`
- L872-875 _function_ `float4 VertexFactoryGetWorldPosition(FVertexFactoryInput Input)` — for depth-only pass (Not used by the actual hair shaders)
- L878-881 _function_ `float4 VertexFactoryGetWorldPositionRaw(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, bool bInvalidJointVertex)` — @return translated world position (without quad extension/reorientation).This is used only for velocity computation
- L882-885 _function_ `float4 VertexFactoryGetWorldPositionRaw(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)`
- L888-892 _function_ `float4 VertexFactoryGetPreviousWorldPosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, bool bInvalidJointVertex)` — @return previous translated world position
- L893-896 _function_ `float4 VertexFactoryGetPreviousWorldPosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)`
- L898-901 _function_ `float3 VertexFactoryGetPreviousInstanceSpacePosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, bool bInvalidJointVertex)`
- L903-907 _function_ `float4 VertexFactoryGetTranslatedPrimitiveVolumeBounds(FVertexFactoryInterpolantsVSToPS Interpolants)`
- L909-912 _function_ `uint VertexFactoryGetPrimitiveId(FVertexFactoryInterpolantsVSToPS Interpolants)`
- L914-917 _function_ `float3 VertexFactoryGetWorldNormal(FVertexFactoryInput Input)`
- L919-922 _function_ `float3 VertexFactoryGetWorldNormal(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)`
- L928-935 _function_ `FVertexFactoryInput LoadVertexFactoryInputForDynamicUpdate(uint PrimitiveIndex, int VertexIndex, uint PrimitiveId, uint DrawInstanceId)` _[#if COMPUTESHADER]_
- L937-940 _function_ `uint GetNumRayTracingDynamicMeshVerticesIndirect()` _[#if COMPUTESHADER]_
- L950-957 _function_ `float2 VertexFactoryGetRayTracingTextureCoordinate(FVertexFactoryRayTracingInterpolants Interpolants)` _[#if NEEDS_VERTEX_FACTORY_INTERPOLATION]_
- L959-962 _function_ `FVertexFactoryInterpolantsVSToPS VertexFactoryAssignInterpolants(FVertexFactoryRayTracingInterpolants Input)` _[#if NEEDS_VERTEX_FACTORY_INTERPOLATION]_
- L964-969 _function_ `FVertexFactoryRayTracingInterpolants VertexFactoryGetRayTracingInterpolants(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, FMaterialVertexParameters VertexParameters)` _[#if NEEDS_VERTEX_FACTORY_INTERPOLATION]_
- L971-1013 _function_ `FVertexFactoryRayTracingInterpolants VertexFactoryInterpolate(FVertexFactoryRayTracingInterpolants a, float aInterp, FVertexFactoryRayTracingInterpolants b, float bInterp)` _[#if NEEDS_VERTEX_FACTORY_INTERPOLATION]_
- L1017-1021 _function_ `bool IsFrontFaceHit()` _[#if RAYHITGROUPSHADER && ALLOW_CUSTOM_RAYTRACING_HIT_TYPE]_

#### Prototypes (4)

- L194 _prototype_ `FHairControlPoint GetVertexPosition(const FVertexInfo VertexInfo, bool bInvalidJointVertex)` _[#if RAYHITGROUPSHADER]_
- L378 _prototype_ `float3 VertexFactoryGetPreviousInstanceSpacePosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, bool bInvalidJointVertex)`
- L383 _prototype_ `float3 VertexFactoryGetInstanceSpacePosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)`
- L384 _prototype_ `float3 VertexFactoryGetInstanceSpacePosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, FHairViewInfo HairInfo)`

#### Top-level macro invocations (3)

- L99 _macro_call_ `VF_GPUSCENE_DECLARE_INPUT_BLOCK(13)` (scope `FVertexFactoryInput`)
- L102 _macro_call_ `VF_INSTANCED_STEREO_DECLARE_INPUT_BLOCK()` (scope `FVertexFactoryInput`)
- L103 _macro_call_ `VF_MOBILE_MULTI_VIEW_DECLARE_INPUT_BLOCK()` (scope `FVertexFactoryInput`)

#### C++ shader bindings (IMPLEMENT_* naming this file, 2)

- `EVertexFactoryFlags::UsedWithMaterials
	\| EVertexFactoryFlags::SupportsDynamicLighting
	\| EVertexFactoryFlags::SupportsPrecisePrevWorldPos
	\| EVertexFactoryFlags::SupportsCachingMeshDrawCommands
	\| (VF_STRANDS_SUPPORT_GPU_SCENE ? EVertexFactoryFlags::SupportsPrimitiveIdStream : EVertexFactoryFlags::None)
	\| EVertexFactoryFlags::SupportsRayTracing
	\| (VF_STRANDS_PROCEDURAL_INTERSECTOR ? EVertexFactoryFlags::SupportsRayTracingProceduralPrimitive : EVertexFactoryFlags::None)
	\| EVertexFactoryFlags::SupportsManualVertexFetch
	\| EVertexFactoryFlags::SupportsPSOPrecaching` → entry not found in file (macro-generated or #include'd); C++ `FHairStrandsVertexFactory`  via IMPLEMENT_TEMPLATE_VERTEX_FACTORY_TYPE (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsVertexFactory.cpp:359)
- `EVertexFactoryFlags::UsedWithMaterials
	\| EVertexFactoryFlags::SupportsDynamicLighting
	\| EVertexFactoryFlags::SupportsPrecisePrevWorldPos
	\| EVertexFactoryFlags::SupportsCachingMeshDrawCommands
	\| (VF_STRANDS_SUPPORT_GPU_SCENE ? EVertexFactoryFlags::SupportsPrimitiveIdStream : EVertexFactoryFlags::None)
	\| EVertexFactoryFlags::SupportsRayTracing
	\| EVertexFactoryFlags::SupportsManualVertexFetch
	\| EVertexFactoryFlags::SupportsPSOPrecaching` → entry not found in file (macro-generated or #include'd); C++ `FLinearSweptSpheresHairStrandsVertexFactory`  via IMPLEMENT_TEMPLATE_VERTEX_FACTORY_TYPE (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/HairStrandsVertexFactory.cpp:371)

### `Shaders/Private/HairStrands/HairStrandsVertexFactoryCommon.ush` (Private)

- lines: 100; parse: all-branches
- includes: L5 `/Engine/Shared/HairStrandsDefinitions.h`, L6 `/Engine/Private/HairStrands/HairStrandsPack.ush`

#### Macros (#define, 8)

- L9 `#define HAIR_STRANDS_PARAMETERS 0` _[#if !defined(HAIR_STRANDS_PARAMETERS)]_
- L12 `#define HAIR_SIM 0`
- L13 `#define HAIR_REN 1`
- L14 `#define HAIR_CAR 2`
- L15 `#define HAIR_MAX_CARDS_LOD 8`
- L17 `#define HAIR_CURR 0`
- L18 `#define HAIR_PREV 1`
- L54 `#define HAIR_STRANDS_INSTANCE_PARAMETERS(Prefix) uint Prefix##_RegisteredIndex; uint Prefix##_bCullingEnable; uint Prefix##_RaytracingProceduralSplits; uint Prefix##_GroupIndex; uint Prefix##_GroupCount; float Prefix##_Radius; float Prefix##_RootSca ...` (43 lines)
- L3 #pragma `once`

#### Functions (6)

- L20-23 _function_ `float3 ReadPositionOffset(StructuredBuffer<float4> In, uint InIndex, uint InType, uint InTime, uint InLOD)`
- L25-28 _function_ `void WritePositionOffset(RWStructuredBuffer<float4> Out, uint InIndex, uint InType, uint InTime, uint InLOD, float3 InPositionOffset)`
- L30-33 _function_ `float3 ReadRenPositionOffset(StructuredBuffer<float4> In, uint InIndex)`
- L35-38 _function_ `float3 ReadRenPrevPositionOffset(StructuredBuffer<float4> In, uint InIndex)`
- L40-43 _function_ `float3 ReadSimPositionOffset(StructuredBuffer<float4> In, uint InIndex)`
- L45-48 _function_ `float3 ReadCardPositionOffset(StructuredBuffer<float4> In, uint InIndex, uint InLOD)`

#### Top-level macro invocations (1)

- L99-100 _macro_call_ `HAIR_STRANDS_INSTANCE_PARAMETERS(HairStrandsVF)` _[#if HAIR_STRANDS_PARAMETERS == 1]_

### `Shaders/Private/HairStrands/HairStrandsVisibilityClearPS.usf` (Private)

- lines: 26; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`

#### Entry points (1)

- L9-26 _entry_ `void ClearPS( out uint OutColor : SV_Target0 out uint2 OutColor : SV_Target0 out float OutColor : SV_Target0 )` — stage: **pixel (from C++ binding)** — C++: `FClearUIntGraphicPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVisibility.cpp:1943)

#### Global parameters (uniforms) (2)

- L6 _parameter_ `uint uClearValue;`
- L7 _parameter_ `float fClearValue;`

### `Shaders/Private/HairStrands/HairStrandsVisibilityCommon.ush` (Private)

- lines: 439; parse: all-branches
- includes: L16 `../PackUnpack.ush`, L17 `/Engine/Shared/HairStrandsDefinitions.h`, L18 `HairStrandsVisibilityCommonStruct.ush`

#### Macros (#define, 7)

- L6 `#define RENDER_MODE_TRANSMITTANCE 0`
- L7 `#define RENDER_MODE_PPLL 1`
- L8 `#define RENDER_MODE_MSAA_VISIBILITY 2`
- L9 `#define RENDER_MODE_TRANSMITTANCE_AND_HAIRCOUNT 3`
- L10 `#define RENDER_MODE_COMPUTE_RASTER 4`
- L12 `#define INVALID_TILE_OFFSET ~0`
- L14 `#define HAIR_VISIBILITY_GROUP_COUNT_WIDTH 64`
- L3 #pragma `once`

#### Structs / classes (5)

- L120-124 _struct_ **`FNodeDesc`** `struct FNodeDesc` — Node Desc * Max 67,108,864 total nodes (This is 32 nodes per pixel at 1080p if all pixel were covered) * Max 63 nodes per pixel 26bits for offset \| 6 bits for count (max 63 nodes) TODO rename FHairSamplesDesc
  - L122 _member_ `uint Offset;`
  - L123 _member_ `uint Count;`
- L192-199 _struct_ **`FHairVis`** `struct FHairVis`
  - L194 _member_ `float Depth;`
  - L195 _member_ `float Coverage;` — Coverage in float point, but with 8-bits precision. For convenience.
  - L196 _member_ `uint Coverage8bit;`
  - L197 _member_ `uint ControlPointId;`
  - L198 _member_ `uint MaterialId;`
- L228-242 _struct_ **`FHairSample`** `struct FHairSample` — Footprint: 128bits \| 16bytes Option to reduce the footprint: * we don't use ControlPointId at the moment which is encoded on 3bytes * Deferred the evaluation of Coverage & material properties into some other pass?
  - L230 _member_ `float Depth;`
  - L231 _member_ `float3 Tangent;`
  - L232 _member_ `uint Coverage8bit;`
  - L233 _member_ `uint ControlPointId;`
  - L234 _member_ `uint MacroGroupId;`
  - L235 _member_ `float3 BaseColor;`
  - L236 _member_ `float Roughness;`
  - L237 _member_ `float Specular;`
  - L238 _member_ `float Backlit;`
  - L239 _member_ `uint LightChannelMask;`
  - L240 _member_ `float3 Emissive;`
  - L241 _member_ `uint Flags;`
- L340-351 _struct_ **`FHairRenderInfo`** `struct FHairRenderInfo`
  - L342 _member_ `float RadiusAtDepth1Primary;`
  - L343 _member_ `float RadiusAtDepth1Velocity;`
  - L344 _member_ `float VelocityMagnitudeScale;`
  - L346 _member_ `bool bIsGPUDriven;`
  - L347 _member_ `bool bIsOrthoView;` — Only used for shadow view
  - L349 _member_ `float3 ViewForward;`
  - L350 _member_ `float3 TranslatedWorldCameraOrigin;`
- L367-373 _struct_ **`FHairViewInfo`** `struct FHairViewInfo`
  - L369 _member_ `float3 TranslatedWorldCameraOrigin;`
  - L370 _member_ `float3 ViewForward;`
  - L371 _member_ `float RadiusAtDepth1;`
  - L372 _member_ `bool bIsOrthoView;`

#### Functions (45)

- L23-26 _function_ `float3 EncodeTangent(float3 N)`
- L28-31 _function_ `float3 DecodeTangent(float3 N)`
- L33-37 _function_ `uint float4ToUint(float4 v)`
- L39-47 _function_ `float4 UintToFloat4(uint In)`
- L49-52 _function_ `uint Uint16ToUint32(uint2 In)`
- L54-60 _function_ `uint2 Uint32ToUint16(uint In)`
- L62-65 _function_ `uint Float16ToUint32(float2 In)`
- L67-70 _function_ `float2 Uint32ToFloat16(uint In)`
- L72-75 _function_ `uint To8bitCoverage(float Coverage)`
- L77-80 _function_ `float From8bitCoverage(uint Coverage8bit)`
- L82-85 _function_ `uint To16bitCoverage(float Coverage)`
- L87-90 _function_ `float From16bitCoverage(uint Coverage16bit)`
- L92-96 _function_ `uint3 QuantizeTo8Bits(float3 T)`
- L98-101 _function_ `float3 From8bits(float3 In8bits)`
- L103-106 _function_ `uint PackVelocity(float2 EncodedVelocity)`
- L108-111 _function_ `float2 UnpackVelocity(uint PackedVelocity)`
- L126-129 _function_ `uint EncodeNodeDesc(const FNodeDesc Desc)`
- L131-137 _function_ `FNodeDesc DecodeNodeDesc(uint In)`
- L142-145 _function_ `uint PackHairVisDepthCoverage(float InDepth, float InCoverage)`
- L147-150 _function_ `uint PackHairVisDepthCoverage(float InDepth, uint InCoverage8bits)`
- L152-155 _function_ `uint PackHairVisControlPointMaterialId(uint ControlPointId, uint MaterialId)`
- L157-160 _function_ `uint UnpackHairVisControlPointId(uint RawVis)`
- L162-165 _function_ `uint UnpackHairVisMaterialId(uint RawVis)`
- L167-170 _function_ `float UnpackHairVisDepth(uint InPacked)`
- L172-175 _function_ `float UnpackHairVisCoverage(uint InPacked)`
- L177-180 _function_ `uint UnpackHairVisCoverage8bits(uint InPacked)`
- L182-185 _function_ `uint GetInvalidHairControlPointId()`
- L187-190 _function_ `void PatchPackedHairVisCoverage(inout FPackedHairVis Out, uint Coverage8bit)`
- L201-207 _function_ `FPackedHairVis PackHairVis(const FHairVis In)`
- L209-219 _function_ `FHairVis UnpackHairVis(const FPackedHairVis In)`
- L244-273 _function_ `FPackedHairSample PackHairSample(const FHairSample In)`
- L275-296 _function_ `FHairSample UnpackHairSample(const FPackedHairSample In)`
- L298-301 _function_ `void PatchPackedHairSampleCoverage(inout FPackedHairSample Out, uint Coverage8bit)`
- L303-306 _function_ `uint GetPackedHairSampleCoverage8bit(in FPackedHairSample In)`
- L308-312 _function_ `uint2 GetHairSampleResolution(uint InNodeCount)`
- L314-317 _function_ `uint2 GetHairSampleCoord(uint InLinearCoord, uint2 InResolution)`
- L324-328 _function_ `bool NeedFastResolve(float2 InEncodedVelocity, float2 InVelocity, float InVelocityThreshold)` — Return true if the underlying pixel need to run with TAA fast resolve. This is the case when the velocity is larger than a certain threshold.
- L330-335 _function_ `bool NeedFastResolve(float2 InEncodedVelocity, float InVelocityThreshold)`
- L353-365 _function_ `FHairRenderInfo GetHairRenderInfo(float4 ViewHairRenderInfo, uint ViewHairRenderInfoBits, bool bUseScableRasterization=false)`
- L378-381 _function_ `float TransmittanceToCoverage(float InTransmittance, float InCoverageThreashold)`
- L386-405 _function_ `FPackedHairVisPPLL PackHairVisPPLL( float Depth, float Coverage, uint ControlPointId, uint MaterialId, uint NextNodeIndex)`
- L407-413 _function_ `FHairVis UnpackHairVisPPLL(FPackedHairVisPPLL In)`
- L415-421 _function_ `FPackedHairVis ConvertToPackedHairVis(FPackedHairVisPPLL In)`
- L426-432 _function_ `uint PackCoverageAndHairCount(float InCoverage)`
- L434-437 _function_ `float UnpackCoverageAndHairCount(uint InPacked)`

### `Shaders/Private/HairStrands/HairStrandsVisibilityCommonStruct.ush` (Private)

- lines: 25; parse: all-branches
- L3 #pragma `once`

#### Structs / classes (3)

- L5-12 _struct_ **`FPackedHairSample`** `struct FPackedHairSample`
  - L7 _member_ `float Depth;`
  - L8 _member_ `uint ControlPointID_MacroGroupID;`
  - L9 _member_ `uint Tangent_Coverage8bit;`
  - L10 _member_ `uint BaseColor_Roughness;`
  - L11 _member_ `uint Data;`
- L14-18 _struct_ **`FPackedHairVis`** `struct FPackedHairVis`
  - L16 _member_ `uint Depth_Coverage8bit;`
  - L17 _member_ `uint ControlPointID_MaterialID;`
- L20-25 _struct_ **`FPackedHairVisPPLL`** `struct FPackedHairVisPPLL`
  - L22 _member_ `uint Depth_Coverage8bit;`
  - L23 _member_ `uint ControlPointID_MaterialID;`
  - L24 _member_ `uint NextNodeIndex;`

### `Shaders/Private/HairStrands/HairStrandsVisibilityCompaction.usf` (Private)

- lines: 463; parse: all-branches
- includes: L5 `../Common.ush`, L6 `HairStrandsVisibilityCommon.ush`, L7 `HairStrandsTileCommon.ush`

#### Macros (#define, 6)

- L10 `#define TILE_PIXEL_SIZE_X 8` _[#if PERMUTATION_GROUPSIZE ==32]_
- L11 `#define TILE_PIXEL_SIZE_Y 4` _[#if PERMUTATION_GROUPSIZE ==32]_
- L13 `#define TILE_PIXEL_SIZE_X 8` _[#if !(PERMUTATION_GROUPSIZE ==32) && PERMUTATION_GROUPSIZE == 64]_
- L14 `#define TILE_PIXEL_SIZE_Y 8` _[#if !(PERMUTATION_GROUPSIZE ==32) && PERMUTATION_GROUPSIZE == 64]_
- L50 `#define PPLL_MAX_RENDER_NODE_COUNT PERMUTATION_PPLL` _[#if PERMUTATION_PPLL]_
- L225 `#define MERGE_SAMPLE 0` _[#if !(PERMUTATION_PPLL)]_
- L3 #pragma `once`

#### Entry points (2)

- L61-213 _entry_ `[numthreads(TILE_PIXEL_SIZE_X, TILE_PIXEL_SIZE_Y, 1)] void MainCS( uint GroupIndex : SV_GroupIndex, uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FHairVisibilityControlPointIdCompactionCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVisibility.cpp:2135) _[#if PERMUTATION_PPLL]_
- L372-460 _entry_ `[numthreads(TILE_PIXEL_SIZE_X, TILE_PIXEL_SIZE_Y, 1)] void MainCS( uint GroupIndex : SV_GroupIndex, uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FHairVisibilityControlPointIdCompactionCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVisibility.cpp:2135) _[#if !(PERMUTATION_PPLL)]_

#### Structs / classes (1)

- L38-43 _struct_ **`FSampleSetDesc`** `struct FSampleSetDesc`
  - L40 _member_ `uint UniqueSampleCount;`
  - L41 _member_ `uint ValidSampleCount;`
  - L42 _member_ `uint HairSampleCount;`

#### Global resources (textures / buffers / samplers) (20)

- L28 _resource_ `RWStructuredBuffer<uint> OutCompactNodeCounter;`
- L29 _resource_ `RWTexture2D<uint> OutCompactNodeIndex;`
- L30 _resource_ `RWStructuredBuffer<FPackedHairVis> OutCompactNodeVis;`
- L31 _resource_ `RWBuffer<uint2> OutCompactNodeCoord;`
- L32 _resource_ `RWTexture2D<float> OutCoverageTexture;`
- L52 _resource_ `Buffer<uint> TileCountBuffer;` _[#if PERMUTATION_PPLL]_
- L53 _resource_ `Buffer<uint2> TileDataBuffer;` _[#if PERMUTATION_PPLL]_
- L56 _resource_ `Texture2D<uint> PPLLCounter;` _[#if PERMUTATION_PPLL]_
- L57 _resource_ `Texture2D<uint> PPLLNodeIndex;` _[#if PERMUTATION_PPLL]_
- L58 _resource_ `StructuredBuffer<FPackedHairVisPPLL> PPLLNodeData;` _[#if PERMUTATION_PPLL]_
- L227 _resource_ `Texture2D<float> SceneDepthTexture;` _[#if !(PERMUTATION_PPLL)]_
- L324 _resource_ `Texture2DMS<uint, PERMUTATION_MSAACOUNT> MSAA_IDTexture;` _[#if !(PERMUTATION_PPLL) && PERMUTATION_MSAACOUNT > 1]_
- L324 _resource_ `Texture2DMS<uint, PERMUTATION_MSAACOUNT> MSAA_IDTexture;` _[#if !(PERMUTATION_PPLL) && PERMUTATION_MSAACOUNT > 1]_
- L325 _resource_ `Texture2DMS<float, PERMUTATION_MSAACOUNT> MSAA_DepthTexture;` _[#if !(PERMUTATION_PPLL) && PERMUTATION_MSAACOUNT > 1]_
- L325 _resource_ `Texture2DMS<float, PERMUTATION_MSAACOUNT> MSAA_DepthTexture;` _[#if !(PERMUTATION_PPLL) && PERMUTATION_MSAACOUNT > 1]_
- L357 _resource_ `Texture2D<uint> MSAA_IDTexture;` _[#if !(PERMUTATION_PPLL) && !(PERMUTATION_MSAACOUNT > 1)]_
- L358 _resource_ `Texture2D<float> MSAA_DepthTexture;` _[#if !(PERMUTATION_PPLL) && !(PERMUTATION_MSAACOUNT > 1)]_
- L367 _resource_ `Buffer<uint> TileCountBuffer;` _[#if !(PERMUTATION_PPLL)]_
- L368 _resource_ `Buffer<uint2> TileDataBuffer;` _[#if !(PERMUTATION_PPLL)]_
- L370 _resource_ `Texture2D<float> ViewTransmittanceTexture;` _[#if !(PERMUTATION_PPLL)]_

#### Global parameters (uniforms) (11)

- L19 _parameter_ `int2 OutputResolution;`
- L20 _parameter_ `int2 ResolutionOffset;`
- L21 _parameter_ `uint MaxNodeCount;`
- L22 _parameter_ `uint bSortSampleByDepth;`
- L23 _parameter_ `float DepthTheshold;`
- L24 _parameter_ `float CosTangentThreshold;`
- L25 _parameter_ `float CoverageThreshold;` — Allow to scale the transmittance to compensate its asymptotic behavior
- L26 _parameter_ `uint VelocityType;`
- L55 _parameter_ `int2 TileCountXY;` _[#if PERMUTATION_PPLL]_
- L365 _parameter_ `int2 TileCountXY;` _[#if !(PERMUTATION_PPLL)]_
- L366 _parameter_ `uint TileSize;` _[#if !(PERMUTATION_PPLL)]_

#### groupshared (2)

- L34 _groupshared_ `groupshared uint AllocationNodeCount;`
- L35 _groupshared_ `groupshared uint AllocationNodeOffset;`

#### Functions (4)

- L230-322 _function_ `void ComputeUniqueSamplesWithoutDepthTest( inout uint4 OutSamples[PERMUTATION_MSAACOUNT], inout FSampleSetDesc OutSet, const uint2 PixelCoord, const float OpaqueDepth, Texture2DMS<uint, PERMUTATION_MSAACOUNT> InMSAA_IDTexture, Texture2DMS<float, PERMUTATION_MSAACOUNT> InMSAA_DepthTexture)` _[#if !(PERMUTATION_PPLL) && PERMUTATION_MSAACOUNT > 1]_
- L328-355 _function_ `void ComputeUniqueSamplesWithoutDepthTest( inout uint4 OutSamples[PERMUTATION_MSAACOUNT], inout FSampleSetDesc OutSet, const uint2 PixelCoord, const float OpaqueDepth, Texture2D<uint> InMSAA_IDTexture, Texture2D<float> InMSAA_DepthTexture)` _[#if !(PERMUTATION_PPLL) && !(PERMUTATION_MSAACOUNT > 1)]_
- L360 _function_ `uint2 GetIDTexture(uint2 PixelCoord, uint SampleIt)` _[#if !(PERMUTATION_PPLL) && !(PERMUTATION_MSAACOUNT > 1)]_
- L361 _function_ `float GetDepthTexture(uint2 PixelCoord, uint SampleIt)` _[#if !(PERMUTATION_PPLL) && !(PERMUTATION_MSAACOUNT > 1)]_

### `Shaders/Private/HairStrands/HairStrandsVisibilityCompactionComputeRaster.usf` (Private)

- lines: 244; parse: all-branches
- includes: L5 `../Common.ush`, L6 `HairStrandsVisibilityCommon.ush`, L7 `HairStrandsTileCommon.ush`

#### Macros (#define, 6)

- L10 `#define TILE_PIXEL_SIZE_X 8` _[#if PERMUTATION_GROUPSIZE == 0]_
- L11 `#define TILE_PIXEL_SIZE_Y 4` _[#if PERMUTATION_GROUPSIZE == 0]_
- L13 `#define TILE_PIXEL_SIZE_X 8` _[#if !(PERMUTATION_GROUPSIZE == 0)]_
- L14 `#define TILE_PIXEL_SIZE_Y 8` _[#if !(PERMUTATION_GROUPSIZE == 0)]_
- L18 `#define PERMUTATION_MULTI_SAMPLE_COUNT 1` _[#if !defined(PERMUTATION_MULTI_SAMPLE_COUNT)]_
- L78 `#define MERGE_SAMPLE 0`
- L3 #pragma `once`

#### Entry points (1)

- L168-243 _entry_ `[numthreads(TILE_PIXEL_SIZE_X, TILE_PIXEL_SIZE_Y, 1)] void MainCS(uint GroupIndex : SV_GroupIndex, uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FHairVisibilityCompactionComputeRasterCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVisibility.cpp:2296)

#### Structs / classes (1)

- L58-63 _struct_ **`FSampleSetDesc`** `struct FSampleSetDesc`
  - L60 _member_ `uint UniqueSampleCount;`
  - L61 _member_ `uint ValidSampleCount;`
  - L62 _member_ `uint HairSampleCount;`

#### Global resources (textures / buffers / samplers) (10)

- L48 _resource_ `RWStructuredBuffer<uint> OutCompactNodeCounter;`
- L49 _resource_ `RWTexture2D<uint> OutCompactNodeIndex;`
- L50 _resource_ `RWStructuredBuffer<FPackedHairVis> OutCompactNodeVis;`
- L51 _resource_ `RWBuffer<uint2> OutCompactNodeCoord;`
- L52 _resource_ `RWTexture2D<float> OutCoverageTexture;`
- L69 _resource_ `Texture2DArray<uint> DepthCovTexture;`
- L70 _resource_ `Texture2DArray<uint> PrimMatTexture;`
- L71 _resource_ `Texture2D<uint> HairCountTexture;`
- L75 _resource_ `Buffer<uint> TileCountBuffer;`
- L76 _resource_ `Buffer<uint2> TileDataBuffer;`

#### Global parameters (uniforms) (7)

- L42 _parameter_ `int2 OutputResolution;`
- L43 _parameter_ `uint MaxNodeCount;`
- L44 _parameter_ `uint SamplerPerPixel;`
- L45 _parameter_ `float CoverageThreshold;`
- L46 _parameter_ `uint bSortSampleByDepth;`
- L73 _parameter_ `int2 TileCountXY;`
- L74 _parameter_ `uint TileSize;`

#### groupshared (2)

- L54 _groupshared_ `groupshared uint AllocationNodeCount;`
- L55 _groupshared_ `groupshared uint AllocationNodeOffset;`

#### Functions (1)

- L80-166 _function_ `void ComputeUniqueSamples(const uint2 PixelCoord, out uint4 OutSamples[PERMUTATION_MULTI_SAMPLE_COUNT], out FSampleSetDesc OutSet)`

### `Shaders/Private/HairStrands/HairStrandsVisibilityComputeSampleCoverage.usf` (Private)

- lines: 55; parse: all-branches
- includes: L5 `../Common.ush`, L6 `HairStrandsVisibilityCommon.ush`

#### Macros (#define, 1)

- L8 `#define MAX_SAMPLE_COUNT 8`
- L3 #pragma `once`

#### Entry points (1)

- L16-55 _entry_ `[numthreads(8, 4, 1)] void MainCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FUpdateSampleCoverageCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVisibility.cpp:998) — TODO: Add permutation for group 32/64

#### Global resources (textures / buffers / samplers) (3)

- L11 _resource_ `Texture2D<uint> NodeIndexAndOffset;`
- L12 _resource_ `StructuredBuffer<FPackedHairSample> InNodeDataBuffer;`
- L13 _resource_ `RWStructuredBuffer<FPackedHairSample> OutNodeDataBuffer;`

#### Global parameters (uniforms) (1)

- L10 _parameter_ `int2 Resolution;`

### `Shaders/Private/HairStrands/HairStrandsVisibilityCopyIndirectArg.usf` (Private)

- lines: 45; parse: all-branches
- includes: L5 `../Common.ush`, L6 `HairStrandsVisibilityCommon.ush`
- L3 #pragma `once`

#### Entry points (1)

- L13-45 _entry_ `[numthreads(1, 1, 1)] void CopyCS(uint GroupIndex : SV_GroupIndex, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FCopyIndirectBufferCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVisibility.cpp:2030)

#### Global resources (textures / buffers / samplers) (2)

- L8 _resource_ `StructuredBuffer<uint> CounterBuffer;`
- L9 _resource_ `RWBuffer<uint> OutArgBuffer;`

#### Global parameters (uniforms) (2)

- L10 _parameter_ `uint ThreadGroupSize;`
- L11 _parameter_ `uint ItemCountPerGroup;`

### `Shaders/Private/HairStrands/HairStrandsVisibilityDepthPS.usf` (Private)

- lines: 146; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../SceneTexturesCommon.ush`, L5 `../DeferredShadingCommon.ush`, L6 `../Substrate/Substrate.ush`, L7 `HairStrandsVisibilityCommon.ush`

#### Macros (#define, 6)

- L9 `#define OUTPUT_DEPTH 0`
- L10 `#define OUTPUT_MATERIALDATA 1`
- L11 `#define OUTPUT_LIGHTCHANNEL 2`
- L12 `#define OUTPUT_MATERIALDATA_LIGHTCHANNEL 3`
- L54 `#define OUTPUT_FORMAT uint` _[#if SUBSTRATE_GBUFFER_FORMAT==1]_
- L56 `#define OUTPUT_FORMAT float4` _[#if !(SUBSTRATE_GBUFFER_FORMAT==1)]_

#### Entry points (3)

- L59-118 _entry_ `void MainPS( in FScreenVertexOutput Input , out float SvDepth : SV_DEPTH , out OUTPUT_FORMAT Output0 : SV_Target0 , out OUTPUT_FORMAT Output1 : SV_Target1 , out float4 OutColor : SV_Target2 , out OUTPUT_FORMAT Output2 : SV_Target3 )` — stage: **pixel (from C++ binding)** — C++: `FHairVisibilityDepthPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVisibility.cpp:2807) _[#if PERMUTATION_OUTPUT_TYPE == OUTPUT_MATERIALDATA \|\| PERMUTATION_OUTPUT_TYPE == OUTPUT_MATERIALDATA_LIGHTCHANNEL]_
- L124-129 _entry_ `void MainPS( in FScreenVertexOutput Input)` — stage: **pixel (from C++ binding)** — C++: `FHairVisibilityDepthPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVisibility.cpp:2807) _[#if PERMUTATION_OUTPUT_TYPE == OUTPUT_LIGHTCHANNEL]_
- L136-145 _entry_ `void MainPS( in FScreenVertexOutput Input, out float SvDepth : SV_DEPTH)` — stage: **pixel (from C++ binding)** — C++: `FHairVisibilityDepthPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVisibility.cpp:2807) _[#if PERMUTATION_OUTPUT_TYPE == OUTPUT_DEPTH]_

#### Structs / classes (1)

- L25-31 _struct_ **`FHairSampleData`** `struct FHairSampleData`
  - L27 _member_ `float DeviceZ;`
  - L28 _member_ `uint LightChannelMask;`
  - L29 _member_ `bool bCastContactShadow;`
  - L30 _member_ `bool bScatterSceneLight;`

#### Global resources (textures / buffers / samplers) (4)

- L15 _resource_ `Texture2D<float> CoverageTexture;` — Manual binding of the sample data as the uniform buffer is not created at this point
- L16 _resource_ `Texture2D<uint> HairSampleOffset;`
- L17 _resource_ `StructuredBuffer<FPackedHairSample> HairSampleData;`
- L20 _resource_ `RWTexture2D<uint> OutLightChannelMaskTexture;` _[#if PERMUTATION_OUTPUT_TYPE == OUTPUT_MATERIALDATA_LIGHTCHANNEL \|\| PERMUTATION_OUTPUT_TYPE == OUTPUT_LIGHTCHANNEL]_

#### Global parameters (uniforms) (1)

- L135 _parameter_ `uint bClear;` _[#if PERMUTATION_OUTPUT_TYPE == OUTPUT_DEPTH]_

#### Functions (1)

- L33-49 _function_ `FHairSampleData ExtractSampleData(uint3 PixelCoord)`

### `Shaders/Private/HairStrands/HairStrandsVisibilityFillOpaqueDepthPS.usf` (Private)

- lines: 15; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../SceneTexturesCommon.ush`

#### Entry points (1)

- L8-14 _entry_ `void MainPS( in FScreenVertexOutput Input, out float OutDepth: SV_DEPTH)` — stage: **pixel (from C++ binding)** — C++: `FHairVisibilityFillOpaqueDepthPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVisibility.cpp:2407)

#### Global resources (textures / buffers / samplers) (1)

- L6 _resource_ `Texture2D<float> SceneDepthTexture;`

### `Shaders/Private/HairStrands/HairStrandsVisibilityPS.usf` (Private)

- lines: 131; parse: all-branches
- includes: L3 `../Common.ush`, L7 `../SceneTexturesCommon.ush`, L8 `../DeferredShadingCommon.ush`, L9 `HairStrandsVisibilityCommon.ush`, L10 `../VelocityCommon.ush`, L12 `/Engine/Generated/Material.ush`, L13 `/Engine/Generated/VertexFactory.ush`

#### Macros (#define, 4)

- L19 `#define SUPPORT_OPACITY_MASK 0`
- L22 `#define SUPPORT_MATERIAL_PROPERTY 1` _[#if HAIR_RENDER_MODE == RENDER_MODE_PPLL]_
- L26 `#define SUPPORT_MATERIAL_PROPERTY 0` _[#if HAIR_RENDER_MODE == RENDER_MODE_TRANSMITTANCE \|\| HAIR_RENDER_MODE == RENDER_MODE_TRANSMITTANCE_AND_HAIRCOUNT]_
- L30 `#define SUPPORT_MATERIAL_PROPERTY 0` _[#if HAIR_RENDER_MODE == RENDER_MODE_MSAA_VISIBILITY]_

#### Entry points (1)

- L39-128 _entry_ `EARLYDEPTHSTENCIL void MainVisibility( nointerpolation uint HairControlPointId : HAIR_PRIMITIVE_ID centroid FVertexFactoryInterpolantsVSToPS Interpolants , in float4 SvPosition : SV_Position , centroid in float WorldStrandRadius : TEXCOORD8 OPTIONAL_IsFrontFace , out float OutColor0 : SV_Target0 , out float OutColor0 : SV_Target0 , out float2 OutColor1 : SV_Target1 , out uint OutColor0 : SV_Target0 )` — stage: **pixel (from C++ binding)** — C++: `FHairVisibilityPS<HairVisibilityRenderMode_MSAA_Visibility>` SF_Pixel via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVisibility.cpp:1581) — C++: `FHairVisibilityPS<HairVisibilityRenderMode_Transmittance>` SF_Pixel via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVisibility.cpp:1582) — C++: `FHairVisibilityPS<HairVisibilityRenderMode_TransmittanceAndHairCount>` SF_Pixel via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVisibility.cpp:1583) — C++: `FHairVisibilityPS<HairVisibilityRenderMode_PPLL>` SF_Pixel via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVisibility.cpp:1584) — Required for UAV operations to not happen. _[#if HAIR_RENDER_MODE == RENDER_MODE_PPLL]_

#### Global parameters (uniforms) (4)

- L33 _parameter_ `uint HairVisibilityPass_HairMacroGroupIndex;`
- L34 _parameter_ `uint HairVisibilityPass_HairMaterialId;`
- L35 _parameter_ `uint HairVisibilityPass_LightChannelMask;`
- L36 _parameter_ `float HairVisibilityPass_HairCoverageScale;`

### `Shaders/Private/HairStrands/HairStrandsVisibilityRasterClassification.usf` (Private)

- lines: 163; parse: all-branches
- includes: L9 `../Common.ush`, L10 `HairStrandsVisibilityCommon.ush`, L11 `HairStrandsVertexFactoryCommon.ush`

#### Macros (#define, 2)

- L3 `#define HAIR_STRANDS_PARAMETERS 1`
- L6 `#define PERMUTATION_CULLING 0` _[#if !defined(PERMUTATION_CULLING)]_

#### Entry points (1)

- L54-163 _entry_ `[numthreads(1024, 1, 1)] void CSMain(uint DispatchThreadID : SV_DispatchThreadID, uint GroupThreadID : SV_GroupThreadID, uint GroupID : SV_GroupID)` — stage: **compute** — C++: `FVisiblityRasterClassificationCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVisibility.cpp:3369)

#### Global resources (textures / buffers / samplers) (3)

- L13 _resource_ `RWBuffer<uint> OutPrimIDs;`
- L14 _resource_ `RWByteAddressBuffer OutDrawIndexedArgs;`
- L15 _resource_ `RWByteAddressBuffer OutSWRasterPrimitiveCount;`

#### Global parameters (uniforms) (3)

- L16 _parameter_ `uint ControlPointCount;`
- L17 _parameter_ `uint PrimIDsBufferSize;`
- L18 _parameter_ `uint NumWorkGroups;`

#### Functions (1)

- L20-52 _function_ `bool ShouldSoftwareRasterize(float3 PositionOffset, uint PrimID, out bool bSegValid)`

### `Shaders/Private/HairStrands/HairStrandsVisibilityRasterCompute.usf` (Private)

- lines: 1587; parse: all-branches
- includes: L5 `../Common.ush`, L6 `../WaveOpUtil.ush`, L7 `HairStrandsClusterCommon.ush`, L8 `HairStrandsVertexFactoryCommon.ush`, L9 `HairStrandsVisibilityCommon.ush`, L1476 `../ShaderPrint.ush` [SHADER_RASTERCOMPUTE_DEBUG]

#### Macros (#define, 20)

- L3 `#define HAIR_STRANDS_PARAMETERS 1`
- L50 `#define VT_SIZE 4` _[#if SHADER_RASTERCOMPUTE_BINNING \|\| SHADER_RASTERCOMPUTE_COMPACTION \|\| SHADER_RASTERCOMPUTE_RASTER \|\| SHADER_RASTERCOMPUTE_RASTER_MULTI_SAMPLE \|\| SHADER_RASTERCOMPUTE_DEPTH_GRID]_
- L52 `#define VT_PrimOffset 0` _[#if SHADER_RASTERCOMPUTE_BINNING \|\| SHADER_RASTERCOMPUTE_COMPACTION \|\| SHADER_RASTERCOMPUTE_RASTER \|\| SHADER_RASTERCOMPUTE_RASTER_MULTI_SAMPLE \|\| SHADER_RASTERCOMPUTE_DEPTH_GRID]_
- L53 `#define VT_PrimCount 1` _[#if SHADER_RASTERCOMPUTE_BINNING \|\| SHADER_RASTERCOMPUTE_COMPACTION \|\| SHADER_RASTERCOMPUTE_RASTER \|\| SHADER_RASTERCOMPUTE_RASTER_MULTI_SAMPLE \|\| SHADER_RASTERCOMPUTE_DEPTH_GRID]_
- L54 `#define VT_Coord 2` _[#if SHADER_RASTERCOMPUTE_BINNING \|\| SHADER_RASTERCOMPUTE_COMPACTION \|\| SHADER_RASTERCOMPUTE_RASTER \|\| SHADER_RASTERCOMPUTE_RASTER_MULTI_SAMPLE \|\| SHADER_RASTERCOMPUTE_DEPTH_GRID]_
- L55 `#define VT_MinWriteIndex 3` _[#if SHADER_RASTERCOMPUTE_BINNING \|\| SHADER_RASTERCOMPUTE_COMPACTION \|\| SHADER_RASTERCOMPUTE_RASTER \|\| SHADER_RASTERCOMPUTE_RASTER_MULTI_SAMPLE \|\| SHADER_RASTERCOMPUTE_DEPTH_GRID]_
- L325 `#define PERMUTATION_INDIRECT_PRIM_IDS 0` _[#if SHADER_RASTERCOMPUTE_BINNING && !defined(PERMUTATION_INDIRECT_PRIM_IDS)]_
- L337 `#define DDA_MAX_ITERATIONS 256` _[#if SHADER_RASTERCOMPUTE_BINNING]_
- L388 `#define TILES_TO_ALLOCATE_MAX 1024` _[#if SHADER_RASTERCOMPUTE_BINNING]_
- L782 `#define WAVE_SIZE 32` _[#if SHADER_RASTERCOMPUTE_RASTER && PERMUTATION_GROUP_SIZE == 64]_
- L784 `#define WAVE_SIZE 32` _[#if SHADER_RASTERCOMPUTE_RASTER && !(PERMUTATION_GROUP_SIZE == 64) && PERMUTATION_GROUP_SIZE == 32]_
- L791 `#define RASTER_LINEAR 0` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L794 `#define RASTER_WU 1` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L796 `#define ENABLE_RASTER_LINEAR_AA 0` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L798 `#define RASTER_ALGO RASTER_LINEAR` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L822 `#define GS_SEGS 320` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L1167 `#define PERMUTATION_MULTI_SAMPLE_COUNT 1` _[#if SHADER_RASTERCOMPUTE_RASTER_MULTI_SAMPLE && !defined(PERMUTATION_MULTI_SAMPLE_COUNT)]_
- L1172 `#define WAVE_SIZE 32` _[#if SHADER_RASTERCOMPUTE_RASTER_MULTI_SAMPLE && PERMUTATION_GROUP_SIZE == 64]_
- L1174 `#define WAVE_SIZE 32` _[#if SHADER_RASTERCOMPUTE_RASTER_MULTI_SAMPLE && !(PERMUTATION_GROUP_SIZE == 64) && PERMUTATION_GROUP_SIZE == 32]_
- L1485 `#define TilePrintOffset (TileSize >> 1)` _[#if SHADER_RASTERCOMPUTE_DEBUG]_

#### Entry points (6)

- L274-316 _entry_ `[numthreads(1024, 1, 1)] void PrepareDepthGridCS(uint DispatchThreadID : SV_DispatchThreadID, uint GroupThreadID : SV_GroupThreadID, uint2 GroupID : SV_GroupID)` — stage: **compute** — C++: `FVisiblityRasterComputePrepareDepthGridCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVisibility.cpp:3266) _[#if SHADER_RASTERCOMPUTE_DEPTH_GRID]_
- L395-625 _entry_ `[numthreads(1024, 1, 1)] void BinningCS(uint DispatchThreadID : SV_DispatchThreadID, uint GroupThreadID : SV_GroupThreadID, uint GroupID : SV_GroupID)` — stage: **compute** — C++: `FVisiblityRasterComputeBinningCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVisibility.cpp:3410) _[#if SHADER_RASTERCOMPUTE_BINNING]_
- L655-772 _entry_ `[numthreads(1024, 1, 1)] void CompactionCS(uint DispatchThreadID : SV_DispatchThreadID, uint GroupThreadID : SV_GroupThreadID, uint2 GroupID : SV_GroupID)` — stage: **compute** — C++: `FVisiblityRasterComputeCompactionCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVisibility.cpp:3442) _[#if SHADER_RASTERCOMPUTE_COMPACTION]_
- L878-1158 _entry_ `[numthreads(1024, 1, 1)] void RasterCS(uint DispatchThreadID : SV_DispatchThreadID, uint GroupThreadID : SV_GroupThreadID, uint GroupID : SV_GroupID)` — stage: **compute** — C++: `FVisiblityRasterComputeRasterizeCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVisibility.cpp:3479) _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L1291-1468 _entry_ `[numthreads(1024, 1, 1)] void RasterMultiSampleCS(uint DispatchThreadID : SV_DispatchThreadID, uint GroupThreadID : SV_GroupThreadID, uint GroupID : SV_GroupID)` — stage: **compute** — C++: `FVisiblityRasterComputeRasterizeMultiSampleCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVisibility.cpp:3517) _[#if SHADER_RASTERCOMPUTE_RASTER_MULTI_SAMPLE]_
- L1534-1584 _entry_ `[numthreads(8, 8, 1)] void MainCS(uint3 ThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FVisiblityRasterComputeDebugCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVisibility.cpp:3553) _[#if SHADER_RASTERCOMPUTE_DEBUG]_

#### Structs / classes (1)

- L339-345 _struct_ **`FDDAContext`** `struct FDDAContext` _[#if SHADER_RASTERCOMPUTE_BINNING]_
  - L341 _member_ `float2 Coord;` _[#if SHADER_RASTERCOMPUTE_BINNING]_
  - L342 _member_ `float2 DeltaDist;` _[#if SHADER_RASTERCOMPUTE_BINNING]_
  - L343 _member_ `float2 Step;` _[#if SHADER_RASTERCOMPUTE_BINNING]_
  - L344 _member_ `float2 SideDist;` _[#if SHADER_RASTERCOMPUTE_BINNING]_

#### Global resources (textures / buffers / samplers) (31)

- L73 _resource_ `Texture2D<float> SceneDepthTexture;` _[#if SHADER_RASTERCOMPUTE_BINNING \|\| SHADER_RASTERCOMPUTE_COMPACTION \|\| SHADER_RASTERCOMPUTE_RASTER \|\| SHADER_RASTERCOMPUTE_RASTER_MULTI_SAMPLE \|\| SHADER_RASTERCOMPUTE_DEPTH_GRID]_
- L268 _resource_ `RWTexture2D<uint> OutVisTileDepthGrid;` _[#if SHADER_RASTERCOMPUTE_DEPTH_GRID]_
- L269 _resource_ `RWTexture2DArray<uint> OutDepthCovTexture;` _[#if SHADER_RASTERCOMPUTE_DEPTH_GRID]_
- L328 _resource_ `RWTexture2DArray<uint> OutVisTileBinningGrid;` _[#if SHADER_RASTERCOMPUTE_BINNING]_
- L329 _resource_ `RWBuffer<uint> OutVisTilePrims;` _[#if SHADER_RASTERCOMPUTE_BINNING]_
- L330 _resource_ `RWBuffer<uint> OutVisTileArgs;` _[#if SHADER_RASTERCOMPUTE_BINNING]_
- L331 _resource_ `RWByteAddressBuffer OutVisTileData;` _[#if SHADER_RASTERCOMPUTE_BINNING]_
- L332 _resource_ `Texture2D<uint> VisTileDepthGrid;` _[#if SHADER_RASTERCOMPUTE_BINNING]_
- L333 _resource_ `ByteAddressBuffer IndirectPrimIDCount;` _[#if SHADER_RASTERCOMPUTE_BINNING]_
- L334 _resource_ `Buffer<uint> IndirectPrimIDs;` _[#if SHADER_RASTERCOMPUTE_BINNING]_
- L632 _resource_ `ByteAddressBuffer VisTileData;` _[#if SHADER_RASTERCOMPUTE_COMPACTION]_
- L633 _resource_ `Buffer<uint> VisTilePrims;` _[#if SHADER_RASTERCOMPUTE_COMPACTION]_
- L634 _resource_ `Buffer<uint> VisTileArgs;` _[#if SHADER_RASTERCOMPUTE_COMPACTION]_
- L635 _resource_ `RWByteAddressBuffer OutCompactedVisTileData;` _[#if SHADER_RASTERCOMPUTE_COMPACTION]_
- L636 _resource_ `RWBuffer<uint> OutCompactedVisTilePrims;` _[#if SHADER_RASTERCOMPUTE_COMPACTION]_
- L637 _resource_ `RWBuffer<uint> OutCompactedVisTileArgs;` _[#if SHADER_RASTERCOMPUTE_COMPACTION]_
- L800 _resource_ `Buffer<uint> VisTilePrims;` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L801 _resource_ `Buffer<uint> VisTileArgs;` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L802 _resource_ `ByteAddressBuffer VisTileData;` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L803 _resource_ `RWTexture2DArray<uint> OutHairCountTexture;` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L804 _resource_ `RWTexture2DArray<uint> OutDepthCovTexture;` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L805 _resource_ `RWTexture2DArray<uint> OutPrimMatTexture;` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L1179 _resource_ `Buffer<uint> VisTilePrims;` _[#if SHADER_RASTERCOMPUTE_RASTER_MULTI_SAMPLE]_
- L1180 _resource_ `Buffer<uint> VisTileArgs;` _[#if SHADER_RASTERCOMPUTE_RASTER_MULTI_SAMPLE]_
- L1181 _resource_ `ByteAddressBuffer VisTileData;` _[#if SHADER_RASTERCOMPUTE_RASTER_MULTI_SAMPLE]_
- L1182 _resource_ `RWTexture2D<uint> OutHairCountTexture;` _[#if SHADER_RASTERCOMPUTE_RASTER_MULTI_SAMPLE]_
- L1183 _resource_ `RWTexture2DArray<uint> OutDepthCovTexture;` _[#if SHADER_RASTERCOMPUTE_RASTER_MULTI_SAMPLE]_
- L1184 _resource_ `RWTexture2DArray<uint> OutPrimMatTexture;` _[#if SHADER_RASTERCOMPUTE_RASTER_MULTI_SAMPLE]_
- L1478 _resource_ `Texture2D<uint> VisTileDepthGrid;` _[#if SHADER_RASTERCOMPUTE_DEBUG]_
- L1479 _resource_ `Texture2DArray<uint> VisTileBinningGrid;` _[#if SHADER_RASTERCOMPUTE_DEBUG]_
- L1480 _resource_ `Buffer<uint> VisTileArgs;` _[#if SHADER_RASTERCOMPUTE_DEBUG]_

#### Global parameters (uniforms) (25)

- L14 _parameter_ `uint TileSizeAsShift;`
- L15 _parameter_ `uint TileSize;`
- L16 _parameter_ `float RcpTileSize;`
- L17 _parameter_ `uint SqrTileSize;`
- L18 _parameter_ `uint HalfTileSize;`
- L19 _parameter_ `float RcpHalfTileSize;`
- L20 _parameter_ `uint SqrHalfTileSize;`
- L21 _parameter_ `int2 TileRes;`
- L23 _parameter_ `uint NumBinners;`
- L24 _parameter_ `float RcpNumBinners;`
- L25 _parameter_ `uint NumRasterizers;`
- L26 _parameter_ `float RcpNumRasterizers;`
- L28 _parameter_ `uint MaxRasterCount;`
- L29 _parameter_ `uint FrameIdMod8;`
- L30 _parameter_ `uint ResolutionMultiplier;`
- L31 _parameter_ `int2 OutputResolution;`
- L32 _parameter_ `float2 OutputResolutionf;`
- L69 _parameter_ `uint MacroGroupId;` _[#if SHADER_RASTERCOMPUTE_BINNING \|\| SHADER_RASTERCOMPUTE_COMPACTION \|\| SHADER_RASTERCOMPUTE_RASTER \|\| SHADER_RASTERCOMPUTE_RASTER_MULTI_SAMPLE \|\| SHADER_RASTERCOMPUTE_DEPTH_GRID]_
- L70 _parameter_ `uint HairMaterialId;` _[#if SHADER_RASTERCOMPUTE_BINNING \|\| SHADER_RASTERCOMPUTE_COMPACTION \|\| SHADER_RASTERCOMPUTE_RASTER \|\| SHADER_RASTERCOMPUTE_RASTER_MULTI_SAMPLE \|\| SHADER_RASTERCOMPUTE_DEPTH_GRID]_
- L75 _parameter_ `uint VertexCount;` _[#if SHADER_RASTERCOMPUTE_BINNING \|\| SHADER_RASTERCOMPUTE_COMPACTION \|\| SHADER_RASTERCOMPUTE_RASTER \|\| SHADER_RASTERCOMPUTE_RASTER_MULTI_SAMPLE \|\| SHADER_RASTERCOMPUTE_DEPTH_GRID]_
- L76 _parameter_ `float CoverageScale;` _[#if SHADER_RASTERCOMPUTE_BINNING \|\| SHADER_RASTERCOMPUTE_COMPACTION \|\| SHADER_RASTERCOMPUTE_RASTER \|\| SHADER_RASTERCOMPUTE_RASTER_MULTI_SAMPLE \|\| SHADER_RASTERCOMPUTE_DEPTH_GRID]_
- L270 _parameter_ `uint NumSamples;` _[#if SHADER_RASTERCOMPUTE_DEPTH_GRID]_
- L1481 _parameter_ `uint MacroGroupId;` _[#if SHADER_RASTERCOMPUTE_DEBUG]_
- L1482 _parameter_ `uint PrimitiveInfoIndex;` _[#if SHADER_RASTERCOMPUTE_DEBUG]_
- L1483 _parameter_ `uint TotalPrimitiveInfoCount;` _[#if SHADER_RASTERCOMPUTE_DEBUG]_

#### groupshared (30)

- L272 _groupshared_ `groupshared uint group_FurthestDepth;` — (4 bytes) _[#if SHADER_RASTERCOMPUTE_DEPTH_GRID]_
- L384 _groupshared_ `groupshared uint group_LoopNum;` _[#if SHADER_RASTERCOMPUTE_BINNING]_
- L385 _groupshared_ `groupshared uint group_VerticesNum;` _[#if SHADER_RASTERCOMPUTE_BINNING]_
- L386 _groupshared_ `groupshared uint group_BatchNum;` _[#if SHADER_RASTERCOMPUTE_BINNING]_
- L389 _groupshared_ `groupshared uint group_TilesToAllocate[TILES_TO_ALLOCATE_MAX];` _[#if SHADER_RASTERCOMPUTE_BINNING]_
- L390 _groupshared_ `groupshared uint group_TilesToAllocateCount;` _[#if SHADER_RASTERCOMPUTE_BINNING]_
- L649 _groupshared_ `groupshared uint group_TotalPrimCount;` _[#if SHADER_RASTERCOMPUTE_COMPACTION]_
- L650 _groupshared_ `groupshared uint group_PrimWriteOffset;` _[#if SHADER_RASTERCOMPUTE_COMPACTION]_
- L651 _groupshared_ `groupshared uint group_NumTiles;` _[#if SHADER_RASTERCOMPUTE_COMPACTION]_
- L652 _groupshared_ `groupshared uint group_TilesToCompact[1024];` _[#if SHADER_RASTERCOMPUTE_COMPACTION]_
- L653 _groupshared_ `groupshared uint group_MaxLDSTileIdx;` _[#if SHADER_RASTERCOMPUTE_COMPACTION]_
- L812 _groupshared_ `groupshared uint4 group_SubTile[1024];` — (32 x 32 x 4 x 4 bytes = 16k bytes) _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L814 _groupshared_ `groupshared float3 group_PositionOffset;` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L815 _groupshared_ `groupshared float group_ooTileLODScale;` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L817 _groupshared_ `groupshared uint group_LoopNum;` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L818 _groupshared_ `groupshared uint group_TileNum;` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L820 _groupshared_ `groupshared uint group_ThreadsPerSeg;` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L824 _groupshared_ `groupshared float4 group_SP0[GS_SEGS];` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L825 _groupshared_ `groupshared float4 group_SP1[GS_SEGS];` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L826 _groupshared_ `groupshared float group_Rad0[GS_SEGS];` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L827 _groupshared_ `groupshared float group_Rad1[GS_SEGS];` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L828 _groupshared_ `groupshared uint group_PrimMatID[GS_SEGS];` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L830 _groupshared_ `groupshared uint group_TileIndex;` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L1191 _groupshared_ `groupshared uint group_SubTileSceneDepth[256];` — (16 x 16 x 4 bytes = 1k bytes) _[#if SHADER_RASTERCOMPUTE_RASTER_MULTI_SAMPLE]_
- L1192 _groupshared_ `groupshared uint group_SubTileHairCount[256];` — (16 x 16 x 4 bytes = 1k bytes) _[#if SHADER_RASTERCOMPUTE_RASTER_MULTI_SAMPLE]_
- L1193 _groupshared_ `groupshared uint group_SubTileHairDepth[PERMUTATION_MULTI_SAMPLE_COUNT][256];` — (16 x 16 x 4 bytes = 1k bytes) per sample _[#if SHADER_RASTERCOMPUTE_RASTER_MULTI_SAMPLE]_
- L1194 _groupshared_ `groupshared uint group_SubTilePrimMatID[PERMUTATION_MULTI_SAMPLE_COUNT][256];` — (16 x 16 x 4 bytes = 1k bytes) per sample _[#if SHADER_RASTERCOMPUTE_RASTER_MULTI_SAMPLE]_
- L1196 _groupshared_ `groupshared float3 group_PositionOffset;` _[#if SHADER_RASTERCOMPUTE_RASTER_MULTI_SAMPLE]_
- L1198 _groupshared_ `groupshared uint group_LoopNum;` _[#if SHADER_RASTERCOMPUTE_RASTER_MULTI_SAMPLE]_
- L1199 _groupshared_ `groupshared uint group_TileNum;` _[#if SHADER_RASTERCOMPUTE_RASTER_MULTI_SAMPLE]_

#### Functions (26)

- L57-60 _function_ `uint PackVisTileCoord(uint2 Coord)` _[#if SHADER_RASTERCOMPUTE_BINNING \|\| SHADER_RASTERCOMPUTE_COMPACTION \|\| SHADER_RASTERCOMPUTE_RASTER \|\| SHADER_RASTERCOMPUTE_RASTER_MULTI_SAMPLE \|\| SHADER_RASTERCOMPUTE_DEPTH_GRID]_
- L62-65 _function_ `uint2 UnpackVisTileCoord(uint Packed)` _[#if SHADER_RASTERCOMPUTE_BINNING \|\| SHADER_RASTERCOMPUTE_COMPACTION \|\| SHADER_RASTERCOMPUTE_RASTER \|\| SHADER_RASTERCOMPUTE_RASTER_MULTI_SAMPLE \|\| SHADER_RASTERCOMPUTE_DEPTH_GRID]_
- L78-83 _function_ `float3 NDCToPixelCoord(float4 InDC)` _[#if SHADER_RASTERCOMPUTE_BINNING \|\| SHADER_RASTERCOMPUTE_COMPACTION \|\| SHADER_RASTERCOMPUTE_RASTER \|\| SHADER_RASTERCOMPUTE_RASTER_MULTI_SAMPLE \|\| SHADER_RASTERCOMPUTE_DEPTH_GRID]_
- L85-98 _function_ `void CalcHomogenousPos(in uint InPointIndex, in float3 PBO, out float4 HP, out uint Type)` _[#if SHADER_RASTERCOMPUTE_BINNING \|\| SHADER_RASTERCOMPUTE_COMPACTION \|\| SHADER_RASTERCOMPUTE_RASTER \|\| SHADER_RASTERCOMPUTE_RASTER_MULTI_SAMPLE \|\| SHADER_RASTERCOMPUTE_DEPTH_GRID]_
- L100-114 _function_ `void CalcHomogenousPosAndRad(in uint InPointIndex, in float3 PBO, out float4 HP, out float Rad, out uint Type)` _[#if SHADER_RASTERCOMPUTE_BINNING \|\| SHADER_RASTERCOMPUTE_COMPACTION \|\| SHADER_RASTERCOMPUTE_RASTER \|\| SHADER_RASTERCOMPUTE_RASTER_MULTI_SAMPLE \|\| SHADER_RASTERCOMPUTE_DEPTH_GRID]_
- L116-126 _function_ `float ComputeLerpAlpha(int2 Coord, float2 P0, float2 P1, float SegmentLenSqRcp)` _[#if SHADER_RASTERCOMPUTE_BINNING \|\| SHADER_RASTERCOMPUTE_COMPACTION \|\| SHADER_RASTERCOMPUTE_RASTER \|\| SHADER_RASTERCOMPUTE_RASTER_MULTI_SAMPLE \|\| SHADER_RASTERCOMPUTE_DEPTH_GRID]_
- L128-138 _function_ `float ComputePerspectiveCorrectRadius(float Rad0, float Rad1, float Alpha, float RcpW0, float RcpW1)` _[#if SHADER_RASTERCOMPUTE_BINNING \|\| SHADER_RASTERCOMPUTE_COMPACTION \|\| SHADER_RASTERCOMPUTE_RASTER \|\| SHADER_RASTERCOMPUTE_RASTER_MULTI_SAMPLE \|\| SHADER_RASTERCOMPUTE_DEPTH_GRID]_
- L141-185 _function_ `bool BlinnLineClipping(inout float4 P0, inout float4 P1)` — Line clipping based on "CLIPPING USING HOMOGENEOUS COORDINATES" by Blinn et al. _[#if SHADER_RASTERCOMPUTE_BINNING \|\| SHADER_RASTERCOMPUTE_COMPACTION \|\| SHADER_RASTERCOMPUTE_RASTER \|\| SHADER_RASTERCOMPUTE_RASTER_MULTI_SAMPLE \|\| SHADER_RASTERCOMPUTE_DEPTH_GRID]_
- L187-225 _function_ `bool ClipRaySegment(float2 AABBMin, float2 AABBMax, float4 P0, float4 P1, out float2 T, out bool2 bClipped)` _[#if SHADER_RASTERCOMPUTE_BINNING \|\| SHADER_RASTERCOMPUTE_COMPACTION \|\| SHADER_RASTERCOMPUTE_RASTER \|\| SHADER_RASTERCOMPUTE_RASTER_MULTI_SAMPLE \|\| SHADER_RASTERCOMPUTE_DEPTH_GRID]_
- L227-260 _function_ `bool ClipRaySegment(float2 AABBMin, float2 AABBMax, inout float4 P0, inout float4 P1, inout float Rad0, inout float Rad1, out bool2 bClipped)` _[#if SHADER_RASTERCOMPUTE_BINNING \|\| SHADER_RASTERCOMPUTE_COMPACTION \|\| SHADER_RASTERCOMPUTE_RASTER \|\| SHADER_RASTERCOMPUTE_RASTER_MULTI_SAMPLE \|\| SHADER_RASTERCOMPUTE_DEPTH_GRID]_
- L347-358 _function_ `FDDAContext DDACreateContext(float2 RayStart, float2 RayDir)` _[#if SHADER_RASTERCOMPUTE_BINNING]_
- L360-372 _function_ `void DDAAdvance(inout FDDAContext Context)` _[#if SHADER_RASTERCOMPUTE_BINNING]_
- L374-377 _function_ `uint LoadOutVisTileData(uint index, uint offset)` _[#if SHADER_RASTERCOMPUTE_BINNING]_
- L379-382 _function_ `void StoreOutVisTileData(uint index, uint offset, uint value)` _[#if SHADER_RASTERCOMPUTE_BINNING]_
- L639-642 _function_ `uint LoadVisTileData(uint index, uint offset)` _[#if SHADER_RASTERCOMPUTE_COMPACTION]_
- L644-647 _function_ `void StoreCompactedVisTileData(uint index, uint offset, uint value)` _[#if SHADER_RASTERCOMPUTE_COMPACTION]_
- L807-810 _function_ `uint LoadVisTileData(uint index, uint offset)` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L832-858 _function_ `void PlotInternal(int2 Coords, float AntiAliasingFactor, float4 P0, float4 P1, float Rad0, float Rad1, float SegmentLenSqRcp, uint PackedTileMin, uint PrimMatID)` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L860-876 _function_ `void Plot(int2 Coord, float FracY, float AntiAliasingFactor, bool bIsSteep, float4 P0, float4 P1, float Rad0, float Rad1, float SegmentLenSqRcp, uint PackedTileMin, uint PrimMatID)` _[#if SHADER_RASTERCOMPUTE_RASTER]_
- L1186-1189 _function_ `uint LoadVisTileData(uint index, uint offset)` _[#if SHADER_RASTERCOMPUTE_RASTER_MULTI_SAMPLE]_
- L1201-1210 _function_ `float GetDistanceToLine(float2 P1, float2 P2, float2 P3, float RcpLineSegLength)` _[#if SHADER_RASTERCOMPUTE_RASTER_MULTI_SAMPLE]_
- L1212-1247 _function_ `uint GetCoverageMask(int2 PixelCoord, float2 P0, float2 P1)` _[#if SHADER_RASTERCOMPUTE_RASTER_MULTI_SAMPLE]_
- L1249-1289 _function_ `void Plot(int2 Coord, float4 P0, float4 P1, float Rad0, float Rad1, float SegmentLenSqRcp, uint PackedHalfTileMin, uint PrimMatID)` _[#if SHADER_RASTERCOMPUTE_RASTER_MULTI_SAMPLE]_
- L1487 _function_ `float4 Transparent(float4 Color)` _[#if SHADER_RASTERCOMPUTE_DEBUG]_
- L1489-1520 _function_ `uint GetTileTotalSegment(uint2 TileCoord, bool bPrintDetails)` _[#if SHADER_RASTERCOMPUTE_DEBUG]_
- L1522-1532 _function_ `void PrintTile(uint2 TileCoord, uint TotalSegments, bool bPrintText)` _[#if SHADER_RASTERCOMPUTE_DEBUG]_

### `Shaders/Private/HairStrands/HairStrandsVisibilityRasterComputeNaive.usf` (Private)

- lines: 235; parse: all-branches
- includes: L13 `../Common.ush`, L14 `HairStrandsVisibilityCommon.ush`, L15 `HairStrandsVertexFactoryCommon.ush`

#### Macros (#define, 3)

- L3 `#define HAIR_STRANDS_PARAMETERS 1`
- L6 `#define PERMUTATION_INDIRECT_PRIM_IDS 0` _[#if !defined(PERMUTATION_INDIRECT_PRIM_IDS)]_
- L10 `#define PERMUTATION_CULLING 0` _[#if !defined(PERMUTATION_CULLING)]_

#### Entry points (1)

- L117-235 _entry_ `[numthreads(64, 1, 1)] void CSMain(uint DispatchThreadID : SV_DispatchThreadID, uint GroupThreadID : SV_GroupThreadID, uint GroupID : SV_GroupID)` — stage: **compute** — C++: `FVisiblityRasterComputeNaiveCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVisibility.cpp:3658)

#### Global resources (textures / buffers / samplers) (6)

- L17 _resource_ `RWTexture2D<uint> OutHairCountTexture;`
- L18 _resource_ `RWTexture2D<uint> OutDepthCovTexture;`
- L19 _resource_ `RWTexture2D<uint> OutPrimMatTexture;`
- L20 _resource_ `Texture2D<float> SceneDepthTexture;`
- L21 _resource_ `ByteAddressBuffer IndirectPrimIDCount;`
- L22 _resource_ `Buffer<uint> IndirectPrimIDs;`

#### Global parameters (uniforms) (5)

- L23 _parameter_ `float2 OutputResolution;`
- L24 _parameter_ `uint HairMaterialId;`
- L25 _parameter_ `uint ControlPointCount;`
- L26 _parameter_ `float CoverageScale;`
- L27 _parameter_ `uint NumWorkGroups;`

#### Functions (3)

- L30-73 _function_ `bool BlinnLineClipping(inout float4 P0, inout float4 P1)` — Line clipping based on "CLIPPING USING HOMOGENEOUS COORDINATES" by Blinn et al.
- L75-80 _function_ `float3 NDCToPixelCoord(float4 InDC)`
- L82-115 _function_ `void Plot(int2 Coord, float AntiAliasingFactor, float4 P0, float4 P1, float Rad0, float Rad1, float SegmentLenSqRcp, uint PrimMatID)`

### `Shaders/Private/HairStrands/HairStrandsVisibilityRasterHW.usf` (Private)

- lines: 164; parse: all-branches
- includes: L5 `../Common.ush`, L6 `HairStrandsVisibilityCommon.ush`, L7 `HairStrandsVertexFactoryCommon.ush`

#### Macros (#define, 3)

- L3 `#define HAIR_STRANDS_PARAMETERS 1`
- L12 `#define PERMUTATION_DRAW_INDIRECT 0` _[#if SHADER_RASTER_HW_VS && !defined(PERMUTATION_DRAW_INDIRECT)]_
- L16 `#define PERMUTATION_CULLING 0` _[#if SHADER_RASTER_HW_VS && !defined(PERMUTATION_CULLING)]_

#### Entry points (2)

- L47-132 _entry_ `VSOutput VSMain(VSInput Input)` — stage: **vertex (from C++ binding)** — C++: `FVisiblityRasterHWVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVisibility.cpp:3587) _[#if SHADER_RASTER_HW_VS]_
- L143-162 _entry_ `EARLYDEPTHSTENCIL void PSMain( float4 Position : SV_Position, float Radius : RADIUS, nointerpolation uint PrimMatID : PRIM_MAT_ID )` — stage: **pixel (from C++ binding)** — C++: `FVisiblityRasterHWPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVisibility.cpp:3615) _[#if SHADER_RASTER_HW_PS]_

#### Structs / classes (2)

- L27-31 _struct_ **`VSInput`** `struct VSInput` _[#if SHADER_RASTER_HW_VS]_
  - L29 _member_ `uint VertexID : SV_VertexID;` _[#if SHADER_RASTER_HW_VS]_
  - L30 _member_ `uint InstanceID : SV_InstanceID;` _[#if SHADER_RASTER_HW_VS]_
- L33-38 _struct_ **`VSOutput`** `struct VSOutput` _[#if SHADER_RASTER_HW_VS]_
  - L35 _member_ `float4 Position : SV_Position;` _[#if SHADER_RASTER_HW_VS]_
  - L36 _member_ `float Radius : RADIUS;` _[#if SHADER_RASTER_HW_VS]_
  - L37 _member_ `nointerpolation uint PrimMatID : PRIM_MAT_ID;` _[#if SHADER_RASTER_HW_VS]_

#### Global resources (textures / buffers / samplers) (4)

- L19 _resource_ `Buffer<uint> RasterPrimIDs;` _[#if SHADER_RASTER_HW_VS]_
- L138 _resource_ `RWTexture2D<uint> OutHairCountTexture;` _[#if SHADER_RASTER_HW_PS]_
- L139 _resource_ `RWTexture2D<uint> OutDepthCovTexture;` _[#if SHADER_RASTER_HW_PS]_
- L140 _resource_ `RWTexture2D<uint> OutPrimMatTexture;` _[#if SHADER_RASTER_HW_PS]_

#### Global parameters (uniforms) (6)

- L20 _parameter_ `float3 ViewDir;` _[#if SHADER_RASTER_HW_VS]_
- L21 _parameter_ `uint HairMaterialId;` _[#if SHADER_RASTER_HW_VS]_
- L22 _parameter_ `float3 CameraOrigin;` _[#if SHADER_RASTER_HW_VS]_
- L23 _parameter_ `float RadiusAtDepth1;` _[#if SHADER_RASTER_HW_VS]_
- L24 _parameter_ `uint PrimIDsBufferSize;` _[#if SHADER_RASTER_HW_VS]_
- L141 _parameter_ `float CoverageScale;` _[#if SHADER_RASTER_HW_PS]_

#### Functions (1)

- L40-45 _function_ `VSOutput GetNullOutput()` _[#if SHADER_RASTER_HW_VS]_

### `Shaders/Private/HairStrands/HairStrandsVisibilityTile.usf` (Private)

- lines: 421; parse: all-branches
- includes: L4 `../Common.ush`, L5 `HairStrandsVisibilityCommon.ush`, L6 `HairStrandsTileCommon.ush`, L256 `../ShaderPrint.ush` [SHADER_TILE_DEBUG_PRINT]

#### Macros (#define, 1)

- L8 `#define GROUP_THREAD_COUNT (HAIR_TILE_SIZE*HAIR_TILE_SIZE)`
- L2 #pragma `once`

#### Entry points (6)

- L41-174 _entry_ `[numthreads(HAIR_TILE_SIZE, HAIR_TILE_SIZE, 1)] void TileMainCS(uint2 DispatchThreadId : SV_DispatchThreadID, uint LinearIndex : SV_GroupIndex, uint3 GroupId : SV_GroupID)` — stage: **compute** — C++: `FHairStrandsTileGenerationPassCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsTile.cpp:171) — C++: `FHairTileClearCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsTile.cpp:473) _[#if SHADER_TILE_GENERATION]_
- L222-230 _entry_ `[numthreads(HAIRTILE_COUNT, 1, 1)] void MainCS(uint2 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FHairStrandsTileCopyArgsPassCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsTile.cpp:94) — C++: `FHairStrandsTileDebugPrintPassCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsTile.cpp:320) _[#if SHADER_TILE_COPY_ARGS]_
- L239-249 _entry_ `void MainPS( in FScreenVertexOutput Input, out float4 OutColor0 : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FHairStrandsTileDebugPassPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsTile.cpp:351) _[#if SHADER_TILE_DEBUG]_
- L298-361 _entry_ `[numthreads(1, 1, 1)] void MainCS(uint GroupIndex : SV_GroupIndex, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FHairStrandsTileCopyArgsPassCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsTile.cpp:94) — C++: `FHairStrandsTileDebugPrintPassCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsTile.cpp:320) _[#if SHADER_TILE_DEBUG_PRINT]_
- L373-386 _entry_ `void MainVS( in uint InVertexId : SV_VertexID, in uint InInstanceId : SV_InstanceID, out FScreenVertexOutput Out)` — stage: **vertex (from C++ binding)** — C++: `FHairStrandsTilePassVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsTile.cpp:279) _[#if SHADER_TILE_VS]_
- L404-420 _entry_ `[numthreads(HAIR_TILE_SIZE, HAIR_TILE_SIZE, 1)] void TileMainCS(uint2 InGroupId : SV_GroupID, uint2 InGroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FHairStrandsTileGenerationPassCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsTile.cpp:171) — C++: `FHairTileClearCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsTile.cpp:473) _[#if SHADER_TILE_CLEAR]_

#### Global resources (textures / buffers / samplers) (16)

- L19 _resource_ `Texture2D<float> InputFloatTexture;` _[#if SHADER_TILE_GENERATION && PERMUTATION_INPUT_TYPE == 0]_
- L21 _resource_ `Texture2D<uint> InputUintTexture;` _[#if SHADER_TILE_GENERATION && !(PERMUTATION_INPUT_TYPE == 0) && PERMUTATION_INPUT_TYPE == 1]_
- L25 _resource_ `RWBuffer<uint> TileCountBuffer;` _[#if SHADER_TILE_GENERATION]_
- L27 _resource_ `RWBuffer<uint2> TileHairAllBuffer;` _[#if SHADER_TILE_GENERATION]_
- L28 _resource_ `RWBuffer<uint2> TileHairFullBuffer;` _[#if SHADER_TILE_GENERATION]_
- L29 _resource_ `RWBuffer<uint2> TileHairPartialBuffer;` _[#if SHADER_TILE_GENERATION]_
- L30 _resource_ `RWBuffer<uint2> TileOtherBuffer;` _[#if SHADER_TILE_GENERATION]_
- L184 _resource_ `Buffer<uint> TileCountBuffer;` _[#if SHADER_TILE_COPY_ARGS]_
- L185 _resource_ `RWBuffer<uint> TileIndirectDrawBuffer;` _[#if SHADER_TILE_COPY_ARGS]_
- L186 _resource_ `RWBuffer<uint> TileIndirectDispatchBuffer;` _[#if SHADER_TILE_COPY_ARGS]_
- L187 _resource_ `RWBuffer<uint> TilePerThreadIndirectDispatchBuffer;` _[#if SHADER_TILE_COPY_ARGS]_
- L188 _resource_ `RWBuffer<uint> TileIndirectRayDispatchBuffer;` _[#if SHADER_TILE_COPY_ARGS]_
- L371 _resource_ `Buffer<uint2> TileDataBuffer;` _[#if SHADER_TILE_VS]_
- L399 _resource_ `Buffer<uint> TileCountBuffer;` _[#if SHADER_TILE_CLEAR]_
- L400 _resource_ `Buffer<uint2> TileDataBuffer;` _[#if SHADER_TILE_CLEAR]_
- L402 _resource_ `RWTexture2D<float4> OutTexture;` _[#if SHADER_TILE_CLEAR]_

#### Global parameters (uniforms) (25)

- L13 _parameter_ `int2 BufferResolution;` _[#if SHADER_TILE_GENERATION]_
- L14 _parameter_ `uint bUintTexture;` _[#if SHADER_TILE_GENERATION]_
- L15 _parameter_ `uint bForceOutputAllTiles;` _[#if SHADER_TILE_GENERATION]_
- L16 _parameter_ `float TransmittanceThreshold;` _[#if SHADER_TILE_GENERATION]_
- L17 _parameter_ `uint IntCoverageThreshold;` _[#if SHADER_TILE_GENERATION]_
- L180 _parameter_ `uint2 TileCountXY;` _[#if SHADER_TILE_COPY_ARGS]_
- L181 _parameter_ `uint TilePerThread_GroupSize;` _[#if SHADER_TILE_COPY_ARGS]_
- L182 _parameter_ `uint bRectPrimitive;` _[#if SHADER_TILE_COPY_ARGS]_
- L183 _parameter_ `uint TileSize;` _[#if SHADER_TILE_COPY_ARGS]_
- L237 _parameter_ `float3 DebugColor;` _[#if SHADER_TILE_DEBUG]_
- L258 _parameter_ `int2 MaxResolution;` _[#if SHADER_TILE_DEBUG_PRINT]_
- L259 _parameter_ `uint TileGroupSize;` _[#if SHADER_TILE_DEBUG_PRINT]_
- L260 _parameter_ `uint TileSize;` _[#if SHADER_TILE_DEBUG_PRINT]_
- L261 _parameter_ `uint TileCount;` _[#if SHADER_TILE_DEBUG_PRINT]_
- L262 _parameter_ `uint TileType;` _[#if SHADER_TILE_DEBUG_PRINT]_
- L263 _parameter_ `int2 TileCountXY;` _[#if SHADER_TILE_DEBUG_PRINT]_
- L264 _parameter_ `uint bRectPrimitive;` _[#if SHADER_TILE_DEBUG_PRINT]_
- L368 _parameter_ `int2 ViewMin;` _[#if SHADER_TILE_VS]_
- L369 _parameter_ `float2 ViewInvSize;` _[#if SHADER_TILE_VS]_
- L370 _parameter_ `uint TileType;` _[#if SHADER_TILE_VS]_
- L394 _parameter_ `uint TileSize;` _[#if SHADER_TILE_CLEAR]_
- L395 _parameter_ `uint TileType;` _[#if SHADER_TILE_CLEAR]_
- L396 _parameter_ `int2 TileCountXY;` _[#if SHADER_TILE_CLEAR]_
- L397 _parameter_ `int2 ViewRectMin;` _[#if SHADER_TILE_CLEAR]_
- L398 _parameter_ `int2 Resolution;` _[#if SHADER_TILE_CLEAR]_

#### groupshared (2)

- L34 _groupshared_ `groupshared uint2 s_fMask[GROUP_THREAD_COUNT];` — 8x8 bit mask _[#if SHADER_TILE_GENERATION && PERMUTATION_WAVEOPS == 0]_
- L35 _groupshared_ `groupshared uint2 s_pMask[GROUP_THREAD_COUNT];` _[#if SHADER_TILE_GENERATION && PERMUTATION_WAVEOPS == 0]_

#### Functions (2)

- L190-220 _function_ `void FillIndirectBuffers(uint TileType)` _[#if SHADER_TILE_COPY_ARGS]_
- L266-296 _function_ `void AddTileCountLine(inout FShaderPrintContext Context, uint TileType)` _[#if SHADER_TILE_DEBUG_PRINT]_

#### Top-level macro invocations (1)

- L39 _macro_call_ `WAVESIZE(64)` _[#if SHADER_TILE_GENERATION && PERMUTATION_WAVE_OPS && COMPILER_SUPPORTS_WAVE_SIZE]_

### `Shaders/Private/HairStrands/HairStrandsVisibilityTransmittanceDepthPS.usf` (Private)

- lines: 43; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../SceneTexturesCommon.ush`, L5 `HairStrandsVisibilityCommon.ush`

#### Entry points (1)

- L11-42 _entry_ `void MainPS( in FScreenVertexOutput Input, out float OutColor : SV_Target0 out float2 OutColor : SV_Target0 )` — stage: **pixel (from C++ binding)** — C++: `FHairViewTransmittanceDepthPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVisibility.cpp:2712)

#### Global resources (textures / buffers / samplers) (2)

- L7 _resource_ `Texture2D<float> SceneDepthTexture;`
- L8 _resource_ `Texture2D<float> HairOnlyDepthTexture;`

#### Global parameters (uniforms) (1)

- L10 _parameter_ `float DistanceThreshold;`

### `Shaders/Private/HairStrands/HairStrandsVisibilityUtils.ush` (Private)

- lines: 24; parse: all-branches
- L3 #pragma `once`

#### Functions (1)

- L6-24 _function_ `FGBufferData HairSampleToGBufferData(in FHairSample In, in float InDualScatteringRoughnessOverride=0)` — Convert a FHairSample into a FGufferData

### `Shaders/Private/HairStrands/HairStrandsVisibilityVS.usf` (Private)

- lines: 132; parse: first-branch (retry, +1 merged from all-branches pass)
- includes: L3 `../Common.ush`, L4 `../VelocityCommon.ush`, L5 `/Engine/Generated/Material.ush`, L6 `/Engine/Generated/VertexFactory.ush`, L7 `HairStrandsVisibilityCommon.ush`

#### Macros (#define, 1)

- L26 `#define VS_OUTPUT_TYPE FHairVisibilityAccumulateVSToPS`

#### Entry points (1)

- L30-52 _entry_ `void Main( FVertexFactoryInput Input, out VS_OUTPUT_TYPE Output )` — stage: **vertex (from C++ binding)** — C++: `THairVisiblityVS_MSAAVisibility_NoCulling` SF_Vertex via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVisibility.cpp:1483) — C++: `THairVisiblityVS_MSAAVisibility_Culling` SF_Vertex via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVisibility.cpp:1484) — C++: `THairVisiblityVS_Transmittance` SF_Vertex via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVisibility.cpp:1485) — C++: `THairVisiblityVS_TransmittanceAndHairCount` SF_Vertex via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVisibility.cpp:1486) — C++: `THairVisiblityVS_PPLL` SF_Vertex via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVisibility.cpp:1487) _[#if VERTEXSHADER]_

#### Structs / classes (1)

- L9-24 _struct_ **`FHairVisibilityAccumulateVSToPS`** `struct FHairVisibilityAccumulateVSToPS`
  - L12 _member_ `nointerpolation uint HairControlPointId : HAIR_PRIMITIVE_ID;` _[#if HAIR_RENDER_MODE == RENDER_MODE_MSAA_VISIBILITY]_
  - L14 _member_ `FVertexFactoryInterpolantsVSToPS FactoryInterpolants;` _[#if !(HAIR_RENDER_MODE == RENDER_MODE_MSAA_VISIBILITY)]_
  - L16 _member_ `float4 Position : SV_POSITION;`
  - L18 _member_ `float WorldStrandRadius : TEXCOORD8;` _[#if HAIR_RENDER_MODE != RENDER_MODE_MSAA_VISIBILITY]_
  - L21 _member_ `INVARIANT_OUTPUT float4 PackedVelocityA : TEXCOORD9;` _[#if HAIR_RENDER_MODE == RENDER_MODE_PPLL]_
  - L22 _member_ `INVARIANT_OUTPUT float4 PackedVelocityC : TEXCOORD12;` _[#if HAIR_RENDER_MODE == RENDER_MODE_PPLL]_

### `Shaders/Private/HairStrands/HairStrandsVoxelDebug.usf` (Private)

- lines: 390; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../SceneTextureParameters.ush`, L5 `../DeferredShadingCommon.ush`, L6 `../ShaderPrint.ush`, L7 `../PositionReconstructionCommon.ush`, L8 `HairStrandsVisibilityCommon.ush`, L9 `HairStrandsVoxelPageCommon.ush`, L10 `../ColorMap.ush`, L21 `HairStrandsVoxelPageTraversal.ush` [SHADER_VOXEL_DEBUG]

#### Macros (#define, 7)

- L14 `#define VOXEL_TRAVERSAL_DEBUG 0` _[#if SHADER_VOXEL_DEBUG]_
- L15 `#define VOXEL_TRAVERSAL_FORCE_MIP_ENABLE 1` _[#if SHADER_VOXEL_DEBUG]_
- L17 `#define VOXEL_TRAVERSAL_TYPE VOXEL_TRAVERSAL_LINEAR_MIPMAP` _[#if SHADER_VOXEL_DEBUG && PERMUTATION_TRAVERSAL == 1]_
- L19 `#define VOXEL_TRAVERSAL_TYPE VOXEL_TRAVERSAL_LINEAR` _[#if SHADER_VOXEL_DEBUG && !(PERMUTATION_TRAVERSAL == 1)]_
- L32 `#define VOXEL_BLOCK 0` _[#if SHADER_VOXEL_DEBUG]_
- L33 `#define VOXEL_SMOOTH 1` _[#if SHADER_VOXEL_DEBUG]_
- L34 `#define VOXEL_FILTERING VOXEL_BLOCK` _[#if SHADER_VOXEL_DEBUG]_

#### Entry points (1)

- L48-388 _entry_ `[numthreads(8, 8, 1)] void MainCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FVoxelVirtualRaymarchingCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDebug.cpp:757) _[#if SHADER_VOXEL_DEBUG]_

#### Global resources (textures / buffers / samplers) (3)

- L28 _resource_ `Texture2D<float> SceneDepthBeforeCompositionTexture;` _[#if SHADER_VOXEL_DEBUG]_
- L29 _resource_ `RWTexture2D<float4> OutputTexture;` _[#if SHADER_VOXEL_DEBUG]_
- L30 _resource_ `Buffer<uint> TotalValidPageCounter;` _[#if SHADER_VOXEL_DEBUG]_

#### Global parameters (uniforms) (4)

- L23 _parameter_ `float2 OutputResolution;` _[#if SHADER_VOXEL_DEBUG]_
- L24 _parameter_ `uint MacroGroupId;` _[#if SHADER_VOXEL_DEBUG]_
- L25 _parameter_ `uint MacroGroupCount;` _[#if SHADER_VOXEL_DEBUG]_
- L26 _parameter_ `uint MaxTotalPageIndexCount;` _[#if SHADER_VOXEL_DEBUG]_

#### Functions (2)

- L36-40 _function_ `uint GetVoxelPageIndex(uint3 InPageIndexCoord, uint3 InPageIndexResolution, uint InLinearPageIndexOffset)` _[#if SHADER_VOXEL_DEBUG]_
- L42-46 _function_ `FFontColor GetOccupancyColor(float In)` _[#if SHADER_VOXEL_DEBUG]_

### `Shaders/Private/HairStrands/HairStrandsVoxelPageCommon.ush` (Private)

- lines: 230; parse: all-branches
- includes: L5 `HairStrandsVoxelPageCommonStruct.ush`, L6 `/Engine/Shared/HairStrandsDefinitions.h`

#### Macros (#define, 12)

- L10 `#define VOXEL_TRAVERSAL_NONE 0`
- L11 `#define VOXEL_TRAVERSAL_LINEAR 1`
- L12 `#define VOXEL_TRAVERSAL_SPARSE_LINEAR 2`
- L13 `#define VOXEL_TRAVERSAL_SPARSE_MIPMAP 3`
- L14 `#define VOXEL_TRAVERSAL_LINEAR_MIPMAP 4`
- L61 `#define INVALID_VOXEL_PAGE_INDEX 0xFFFFFFFF`
- L62 `#define INVALID_MACRO_GROUP_ID 0xFF`
- L64 `#define VOXEL_CAST_NO_SHADOW_MASK 0x80000000`
- L65 `#define VOXEL_HAIR_MASK 0x00FFFFFF`
- L66 `#define VOXEL_OPAQUE_MASK 0x7F000000`
- L67 `#define VOXEL_OPAQUE_ADD 0x7F000000`
- L68 `#define VOXEL_OPAQUE_SHIFT 24`
- L3 #pragma `once`

#### Structs / classes (3)

- L70-76 _struct_ **`FVirtualVoxelCommonDesc`** `struct FVirtualVoxelCommonDesc`
  - L72 _member_ `uint3 PageCountResolution;`
  - L73 _member_ `uint3 PageTextureResolution;`
  - L74 _member_ `uint PageResolution;`
  - L75 _member_ `uint PageResolutionLog2;`
- L78-87 _struct_ **`FVirtualVoxelNodeDesc`** `struct FVirtualVoxelNodeDesc`
  - L80 _member_ `float3 TranslatedWorldMinAABB;` — In translated world space
  - L81 _member_ `float3 TranslatedWorldMaxAABB;` — In translated world space
  - L82 _member_ `uint3 PageIndexResolution;`
  - L83 _member_ `uint3 VirtualResolution;`
  - L84 _member_ `uint PageIndexOffset;`
  - L85 _member_ `float VoxelWorldSize;`
  - L86 _member_ `bool bIsValid;`
- L145-150 _struct_ **`FHairTraversalResult`** `struct FHairTraversalResult`
  - L147 _member_ `float HairCount;`
  - L148 _member_ `float Visibility;`
  - L149 _member_ `float HitT;`

#### Functions (21)

- L17-23 _function_ `uint3 PositionToCoord(float3 P, float3 InMinAABB, float3 InMaxAABB, uint3 InResolution)`
- L25-28 _function_ `uint3 PositionToCoordUnclampled(float3 P, float3 InMinAABB, float3 InMaxAABB, uint3 InResolution)`
- L30-37 _function_ `uint CoordToIndex(uint3 InCoord, uint3 InResolution, uint LinearOffset)`
- L39-50 _function_ `uint3 IndexToCoord(uint InIndex, uint3 InResolution)`
- L52-57 _function_ `bool IsInVoxelBounds(float3 P, float3 MinP, float3 MaxP)`
- L89-92 _function_ `uint PackUnorm11(float Value)`
- L94-97 _function_ `float UnpackUnorm11(uint In)`
- L99-104 _function_ `uint PackVoxelWorldSize(float In)`
- L105-108 _function_ `float UnpackVoxelWorldSize(uint In)`
- L110-113 _function_ `float QuantizeVoxelWorldSize(float In)`
- L115-126 _function_ `FVirtualVoxelNodeDesc UnpackVoxelNode(FPackedVirtualVoxelNodeDesc In, uint InPageResolution)`
- L128-141 _function_ `FPackedVirtualVoxelNodeDesc PackVoxelNode(FVirtualVoxelNodeDesc In)`
- L152-159 _function_ `FHairTraversalResult InitHairTraversalResult()`
- L161-166 _function_ `void Acc(inout FHairTraversalResult Out, const FHairTraversalResult In)`
- L170-175 _function_ `float GetVoxelDensityFixPointScale()`
- L177-182 _function_ `float GetOpaqueVoxelValue()`
- L185-189 _function_ `float GetInternalVoxelOpaqueVisibility(uint RawDensity)` — Return a value in [0..1] 0:no opaque/occlusion 1:fully occluded
- L191-196 _function_ `float GetInternalVoxelHairCount(uint RawDensity)`
- L198-210 _function_ `FHairTraversalResult GetHairVirtualVoxelDensity(uint3 InVoxelPageCoord, Texture3D<uint> InPageTexture, uint MipIndex, float DensityScale, bool bCastShadow)`
- L214-221 _function_ `uint EncodeBaseColorAndRoughness(float3 BaseColor, float Roughness)`
- L223-229 _function_ `void DecodeBaseColorAndRoughness(uint Encoded, inout float3 BaseColor, out float Roughness)`

### `Shaders/Private/HairStrands/HairStrandsVoxelPageCommonStruct.ush` (Private)

- lines: 11; parse: all-branches
- L3 #pragma `once`

#### Structs / classes (1)

- L5-11 _struct_ **`FPackedVirtualVoxelNodeDesc`** `struct FPackedVirtualVoxelNodeDesc`
  - L7 _member_ `float3 TranslatedWorldMinAABB;`
  - L8 _member_ `uint PackedPageIndexResolution;` — 8bits encoding
  - L9 _member_ `float3 TranslatedWorldMaxAABB;`
  - L10 _member_ `uint PageIndexOffset_VoxelWorldSize;`

### `Shaders/Private/HairStrands/HairStrandsVoxelPageTraversal.ush` (Private)

- lines: 497; parse: all-branches; parse notes: 2
- includes: L14 `../ShaderPrint.ush` [!(!defined(VOXEL_TRAVERSAL_DEBUG))], L21 `HairStrandsVoxelPageCommon.ush`

#### Macros (#define, 4)

- L8 `#define VOXEL_TRAVERSAL_TYPE VOXEL_TRAVERSAL_NONE` _[#if !defined(VOXEL_TRAVERSAL_TYPE)]_
- L12 `#define VOXEL_TRAVERSAL_DEBUG 0` _[#if !defined(VOXEL_TRAVERSAL_DEBUG)]_
- L18 `#define VOXEL_TRAVERSAL_FORCE_MIP_ENABLE 0` _[#if !defined(VOXEL_TRAVERSAL_FORCE_MIP_ENABLE)]_
- L88 `#define DEFINE_HAIR_BLUE_NOISE_JITTER_FUNCTION float4 GetHairBlueNoiseJitter(uint2 PixelCoord, uint SampleIndex, uint MaxSampleCount, uint TimeIndex) { int2 Offset1 = int2(R2Sequence(SampleIndex) * BlueNoise.Dimensions.xy); int2 Offset2 = int2(R2S ...` (9 lines)
- L3 #pragma `once`

#### Structs / classes (1)

- L108-123 _struct_ **`FHairTraversalSettings`** `struct FHairTraversalSettings`
  - L110 _member_ `float DensityScale;`
  - L111 _member_ `float CountThreshold;`
  - L112 _member_ `float DistanceThreshold;`
  - L113 _member_ `float SteppingScale;` — Rate at which the raymarching step increase
  - L114 _member_ `float3 Random;`
  - L115 _member_ `float TanConeAngle;`
  - L116 _member_ `float PixelRadius;`
  - L117 _member_ `float JitterScale;`
  - L118 _member_ `float ForcedMip;`
  - L119 _member_ `bool bUseOpaqueVisibility;`
  - L120 _member_ `bool bDebugEnabled;`
  - L121 _member_ `bool bIsPrimaryRay;`
  - L122 _member_ `bool bCastShadow;` — True of the traversal is for casting (opaque) shadow, i.e., not for hair transmission

#### Functions (11)

- L26-32 _function_ `void AddLine(bool bEnabled, float3 P0, float3 P1)` _[#if VOXEL_TRAVERSAL_DEBUG]_
- L34-39 _function_ `void AddMacroGroupAABB(bool bEnabled, float3 P0, float3 P1)` _[#if VOXEL_TRAVERSAL_DEBUG]_
- L41-47 _function_ `void AddPageAABB(bool bEnabled, float3 P0, float3 P1, bool bIsPageValid)` _[#if VOXEL_TRAVERSAL_DEBUG]_
- L49-55 _function_ `void AddStepAABB(bool bEnabled, float3 P0, float3 P1, float3 Color)` _[#if VOXEL_TRAVERSAL_DEBUG]_
- L57-63 _function_ `void AddAABBVolume(bool bEnabled, float3 P0, float3 P1)` _[#if VOXEL_TRAVERSAL_DEBUG]_
- L70-77 _function_ `float3 GetHairVoxelJitter(uint2 PixelCoord, uint Seed, uint JitterMode)`
- L79-85 _function_ `float4 GetHairVoxelJitter2(uint2 PixelCoord, uint Seed, uint JitterMode)`
- L100-104 _function_ `bool ShouldStopTraversal(const FHairTraversalResult InResult, float InHairCountThreshold, bool InUseOpaqueVisibility=true)`
- L125-128 _function_ `float GetHairTraversalMaxT()`
- L130-147 _function_ `FHairTraversalSettings InitHairTraversalSettings()`
- L151-163 _function_ `FHairTraversalResult ComputeHairCountVirtualVoxel( float3 TranslatedWorldPosition0, float3 TranslatedWorldPosition1, FVirtualVoxelCommonDesc InCommonDesc, FVirtualVoxelNodeDesc InNodeDesc, Buffer<uint> InPageIndexBuffer, Texture3D<uint> InPageTexture, FHairTraversalSettings InSettings)` — Sparse voxel traversal routines

#### Stray brace blocks (function body split by #if) (2)

- L166-311 _stray_block_ `{ ... }` _[#if VOXEL_TRAVERSAL_TYPE == VOXEL_TRAVERSAL_LINEAR \|\| VOXEL_TRAVERSAL_TYPE == VOXEL_TRAVERSAL_LINEAR_MIPMAP]_
- L315-495 _stray_block_ `{ ... }` _[#if VOXEL_TRAVERSAL_TYPE == VOXEL_TRAVERSAL_SPARSE_LINEAR \|\| VOXEL_TRAVERSAL_TYPE == VOXEL_TRAVERSAL_SPARSE_MIPMAP]_

<details><summary>parse notes</summary>

- L166: brace block without header (code split across #if branches)
- L315: brace block without header (code split across #if branches)

</details>

### `Shaders/Private/HairStrands/HairStrandsVoxelRasterCompute.usf` (Private)

- lines: 1325; parse: all-branches
- includes: L5 `../Common.ush`, L6 `../Common.ush`, L7 `../Matrices.ush`, L8 `../SceneTextureParameters.ush`, L9 `../PositionReconstructionCommon.ush`, L10 `../DeferredShadingCommon.ush`, L11 `../ShaderPrint.ush`, L12 `HairStrandsAABBCommon.ush`, L13 `HairStrandsVisibilityCommon.ush`, L14 `HairStrandsClusterCommon.ush`, L15 `HairStrandsVertexFactoryCommon.ush`, L16 `HairStrandsVoxelPageCommon.ush`, L17 `HairStrandsDeepShadowCommonStruct.ush`, L529 `../ShaderPrint.ush` [SHADER_ADAPTIVE_FEEDBACK && DEBUG_ENABLE], L1008 `HairStrandsVoxelPageTraversal.ush` [SHADER_DEPTH_INJECTION], L1132 `../MortonCode.ush` [SHADER_MIP_VIRTUALVOXEL], L1300 `HairStrandsVoxelPageCommon.ush` [SHADER_MIP_INDIRECTARGS]

#### Macros (#define, 7)

- L3 `#define HAIR_STRANDS_PARAMETERS 1`
- L19 `#define GLOBAL_PAGE_COUNTER_INDEX 0`
- L20 `#define GROUPS_PAGE_COUNTER_INDEX 1`
- L54 `#define INVALID_OFFSET 0xFFFFFFFF` _[#if SHADER_ALLOCATEPAGEINDEX]_
- L526 `#define DEBUG_ENABLE 0` _[#if SHADER_ADAPTIVE_FEEDBACK]_
- L665 `#define JITTER_ENABLE 0` _[#if SHADER_RASTERCOMPUTE]_
- L1007 `#define VOXEL_TRAVERSAL_TYPE VOXEL_TRAVERSAL_LINEAR` _[#if SHADER_DEPTH_INJECTION]_

#### Entry points (14)

- L59-158 _entry_ `[numthreads(GROUP_SIZE, 1, 1)] void AllocatePageIndex(uint2 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FVoxelAllocatePageIndexCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVoxelization.cpp:460) — This code assume we have less than 32 macro group (which fit into a single CU/SM) _[#if SHADER_ALLOCATEPAGEINDEX]_
- L184-256 _entry_ `[numthreads(GROUP_SIZE, 1, 1)] void MarkValid_PrepareCS(uint2 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FVoxelMarkValidPageIndex_PrepareCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVoxelization.cpp:459) _[#if SHADER_MARKVALID_PREPARE && PERMUTATION_USE_CLUSTER]_
- L258-305 _entry_ `[numthreads(GROUP_SIZE, GROUP_SIZE, GROUP_SIZE)] void MarkValid_PrepareCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FVoxelMarkValidPageIndex_PrepareCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVoxelization.cpp:459) _[#if SHADER_MARKVALID_PREPARE && !(PERMUTATION_USE_CLUSTER)]_
- L329-398 _entry_ `[numthreads(GROUP_SIZE, 1, 1)] void AllocateCS(uint GroupIndex : SV_GroupIndex, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FVoxelAllocateVoxelPageCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVoxelization.cpp:461) _[#if SHADER_ALLOCATE]_
- L419-444 _entry_ `[numthreads(1, 1, 1)] void AddDescCS(uint GroupIndex : SV_GroupIndex, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FVoxelAddNodeDescCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVoxelization.cpp:462) _[#if SHADER_ADDDESC]_
- L467-482 _entry_ `[numthreads(GROUP_SIZE, 1, 1)] void AddIndirectBufferCS(uint GroupIndex : SV_GroupIndex, uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FVoxelAddIndirectBufferCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVoxelization.cpp:463) _[#if SHADER_ADDINDIRECTBUFFER]_
- L498-518 _entry_ `[numthreads(GROUP_SIZE_X, 1, GROUP_SIZE_Z)] void VoxelIndPageClearCS(uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupId : SV_GroupID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FVoxelIndPageClearCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVoxelization.cpp:464) _[#if SHADER_INDPAGECLEAR]_
- L547-639 _entry_ `[numthreads(1, 1, 1)] void FeedbackCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FVoxelAdaptiveFeedbackCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVoxelization.cpp:465) _[#if SHADER_ADAPTIVE_FEEDBACK]_
- L675-821 _entry_ `[numthreads(GROUP_SIZE, 1, 1)] void MainCS(uint2 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `FVirtualVoxelInjectOpaqueCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVoxelization.cpp:195) — C++: `FVoxelRasterComputeCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVoxelization.cpp:1072) — C++: `FVirtualVoxelGenerateMipCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVoxelization.cpp:1199) — C++: `FVirtualVoxelIndirectArgMipCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVoxelization.cpp:1200) _[#if SHADER_RASTERCOMPUTE]_
- L843-913 _entry_ `[numthreads(GROUP_SIZE_X, 1, GROUP_SIZE_Z)] void MainCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FVirtualVoxelInjectOpaqueCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVoxelization.cpp:195) — C++: `FVoxelRasterComputeCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVoxelization.cpp:1072) — C++: `FVirtualVoxelGenerateMipCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVoxelization.cpp:1199) — C++: `FVirtualVoxelIndirectArgMipCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVoxelization.cpp:1200) _[#if SHADER_INJECTOPAQUE_VIRTUALVOXEL]_
- L929-1004 _entry_ `void MainVS( uint VertexId : SV_VertexID, out float4 OutPosition : SV_POSITION, out float3 OutTranslatedWorldPosition : WORLD_POSITION)` — stage: **vertex (from C++ binding)** — C++: `FHairStrandsShadowDepthInjectionVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDeepShadow.cpp:82) _[#if SHADER_DEPTH_INJECTION]_
- L1010-1071 _entry_ `void MainPS( in float4 InPosition : SV_POSITION, in float3 InTranslatedWorldPosition : WORLD_POSITION, out float OutDepth : SV_DEPTH)` — stage: **pixel (from C++ binding)** — C++: `FHairStrandsShadowDepthInjectionPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsDeepShadow.cpp:81) _[#if SHADER_DEPTH_INJECTION]_
- L1167-1294 _entry_ `[numthreads(GROUP_SIZE_X, 1, GROUP_SIZE_Z)] void MainCS(uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FVirtualVoxelInjectOpaqueCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVoxelization.cpp:195) — C++: `FVoxelRasterComputeCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVoxelization.cpp:1072) — C++: `FVirtualVoxelGenerateMipCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVoxelization.cpp:1199) — C++: `FVirtualVoxelIndirectArgMipCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVoxelization.cpp:1200) — GroupSize is [64u,1u,16u] _[#if SHADER_MIP_VIRTUALVOXEL]_
- L1309-1319 _entry_ `[numthreads(1, 1, 1)] void MainCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FVirtualVoxelInjectOpaqueCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVoxelization.cpp:195) — C++: `FVoxelRasterComputeCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVoxelization.cpp:1072) — C++: `FVirtualVoxelGenerateMipCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVoxelization.cpp:1199) — C++: `FVirtualVoxelIndirectArgMipCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/HairStrandsVoxelization.cpp:1200) _[#if SHADER_MIP_INDIRECTARGS]_

#### Global resources (textures / buffers / samplers) (48)

- L42 _resource_ `Buffer<float> GPUVoxelWorldSize;` _[#if SHADER_ALLOCATEPAGEINDEX]_
- L43 _resource_ `Buffer<float> MacroGroupVoxelSizeBuffer;` _[#if SHADER_ALLOCATEPAGEINDEX]_
- L44 _resource_ `Buffer<int> MacroGroupAABBBuffer;` _[#if SHADER_ALLOCATEPAGEINDEX]_
- L45 _resource_ `RWBuffer<int> MacroGroupVoxelAlignedAABBBuffer;` _[#if SHADER_ALLOCATEPAGEINDEX]_
- L46 _resource_ `RWBuffer<uint4> OutPageIndexResolutionAndOffsetBuffer;` _[#if SHADER_ALLOCATEPAGEINDEX]_
- L47 _resource_ `RWBuffer<uint> OutPageIndexAllocationIndirectBufferArgs;` _[#if SHADER_ALLOCATEPAGEINDEX]_
- L173 _resource_ `Buffer<int> GroupAABBsBuffer;` _[#if SHADER_MARKVALID_PREPARE]_
- L174 _resource_ `Buffer<int> ClusterAABBsBuffer;` _[#if SHADER_MARKVALID_PREPARE]_
- L175 _resource_ `Buffer<int> MacroGroupVoxelAlignedAABBBuffer;` _[#if SHADER_MARKVALID_PREPARE]_
- L176 _resource_ `Buffer<uint4> PageIndexResolutionAndOffsetBuffer;` _[#if SHADER_MARKVALID_PREPARE]_
- L178 _resource_ `RWBuffer<uint> OutValidPageIndexBuffer;` _[#if SHADER_MARKVALID_PREPARE]_
- L318 _resource_ `Buffer<uint4> PageIndexResolutionAndOffsetBuffer;` _[#if SHADER_ALLOCATE]_
- L319 _resource_ `Buffer<int> IndirectBufferArgs;` _[#if SHADER_ALLOCATE]_
- L321 _resource_ `RWBuffer<uint> RWPageIndexGlobalCounter;` _[#if SHADER_ALLOCATE]_
- L322 _resource_ `RWBuffer<uint> RWPageIndexBuffer;` _[#if SHADER_ALLOCATE]_
- L323 _resource_ `RWBuffer<uint> RWPageToPageIndexBuffer;` _[#if SHADER_ALLOCATE]_
- L324 _resource_ `RWBuffer<uint4> RWPageIndexCoordBuffer;` _[#if SHADER_ALLOCATE]_
- L413 _resource_ `Buffer<float> GPU_VoxelWorldSize;` _[#if SHADER_ADDDESC]_
- L414 _resource_ `Buffer<int> MacroGroupVoxelAlignedAABBBuffer;` _[#if SHADER_ADDDESC]_
- L415 _resource_ `Buffer<float> MacroGroupVoxelSizeBuffer;` _[#if SHADER_ADDDESC]_
- L416 _resource_ `Buffer<uint4> PageIndexResolutionAndOffsetBuffer;` _[#if SHADER_ADDDESC]_
- L417 _resource_ `RWStructuredBuffer<FPackedVirtualVoxelNodeDesc> OutNodeDescBuffer;` _[#if SHADER_ADDDESC]_
- L456 _resource_ `Buffer<uint> PageIndexGlobalCounter;` _[#if SHADER_ADDINDIRECTBUFFER]_
- L457 _resource_ `RWBuffer<uint> OutIndirectArgsBuffer;` _[#if SHADER_ADDINDIRECTBUFFER]_
- L491 _resource_ `Buffer<uint> PageIndexGlobalCounter;` _[#if SHADER_INDPAGECLEAR]_
- L494 _resource_ `Buffer<uint4> VirtualVoxelParams_PageIndexCoordBuffer;` _[#if SHADER_INDPAGECLEAR]_
- L496 _resource_ `RWTexture3D<uint> OutPageTexture;` _[#if SHADER_INDPAGECLEAR]_
- L537 _resource_ `Buffer<uint> PageIndexGlobalCounter;` _[#if SHADER_ADAPTIVE_FEEDBACK]_
- L538 _resource_ `Buffer<float> CurrGPUMinVoxelWorldSize;` _[#if SHADER_ADAPTIVE_FEEDBACK]_
- L539 _resource_ `RWBuffer<float> NextGPUMinVoxelWorldSize;` _[#if SHADER_ADAPTIVE_FEEDBACK]_
- L658 _resource_ `Buffer<uint> VirtualVoxelParams_PageIndexBuffer;` _[#if SHADER_RASTERCOMPUTE]_
- L659 _resource_ `StructuredBuffer<FPackedVirtualVoxelNodeDesc> VirtualVoxelParams_NodeDescBuffer;` _[#if SHADER_RASTERCOMPUTE]_
- L661 _resource_ `RWTexture3D<uint> OutPageTexture;` _[#if SHADER_RASTERCOMPUTE]_
- L832 _resource_ `RWTexture3D<uint> OutPageTexture;` _[#if SHADER_INJECTOPAQUE_VIRTUALVOXEL]_
- L838 _resource_ `Buffer<uint> VirtualVoxelParams_PageIndexBuffer;` _[#if SHADER_INJECTOPAQUE_VIRTUALVOXEL]_
- L839 _resource_ `Buffer<uint> VirtualVoxelParams_AllocatedPageCountBuffer;` _[#if SHADER_INJECTOPAQUE_VIRTUALVOXEL]_
- L840 _resource_ `Buffer<uint4>VirtualVoxelParams_PageIndexCoordBuffer;` _[#if SHADER_INJECTOPAQUE_VIRTUALVOXEL]_
- L841 _resource_ `StructuredBuffer<FPackedVirtualVoxelNodeDesc> VirtualVoxelParams_NodeDescBuffer;` _[#if SHADER_INJECTOPAQUE_VIRTUALVOXEL]_
- L927 _resource_ `StructuredBuffer<FDeepShadowViewInfo> DeepShadowViewInfoBuffer;` _[#if SHADER_DEPTH_INJECTION]_
- L1140 _resource_ `Buffer<uint> AllocatedPageCountBuffer;` _[#if SHADER_MIP_VIRTUALVOXEL]_
- L1141 _resource_ `Texture3D<uint> InDensityTexture;` _[#if SHADER_MIP_VIRTUALVOXEL]_
- L1142 _resource_ `RWTexture3D<uint> OutDensityTexture;` _[#if SHADER_MIP_VIRTUALVOXEL]_
- L1156 _resource_ `Buffer<uint> PageToPageIndexBuffer;` _[#if SHADER_MIP_VIRTUALVOXEL && PERMUTATION_MIP_AGGREGATE]_
- L1157 _resource_ `RWBuffer<uint> OutPageIndexBuffer;` _[#if SHADER_MIP_VIRTUALVOXEL && PERMUTATION_MIP_AGGREGATE]_
- L1159 _resource_ `RWTexture3D<uint> OutDensityTexture2;` _[#if SHADER_MIP_VIRTUALVOXEL && PERMUTATION_MIP_AGGREGATE]_
- L1160 _resource_ `RWTexture3D<uint> OutDensityTexture1;` _[#if SHADER_MIP_VIRTUALVOXEL && PERMUTATION_MIP_AGGREGATE]_
- L1306 _resource_ `Buffer<uint> InIndirectArgs;` _[#if SHADER_MIP_INDIRECTARGS]_
- L1307 _resource_ `RWBuffer<uint> OutIndirectArgs;` _[#if SHADER_MIP_INDIRECTARGS]_

#### Global parameters (uniforms) (72)

- L27 _parameter_ `float CPUPageWorldSize;` _[#if SHADER_ALLOCATEPAGEINDEX]_
- L28 _parameter_ `float CPUVoxelWorldSize;` _[#if SHADER_ALLOCATEPAGEINDEX]_
- L29 _parameter_ `uint bUseCPUVoxelWorldSize;` — When adaptive voxel size is disabled, we use CPU voxel size value _[#if SHADER_ALLOCATEPAGEINDEX]_
- L30 _parameter_ `uint TotalPageIndexCount;` — This is the max page index count; _[#if SHADER_ALLOCATEPAGEINDEX]_
- L31 _parameter_ `uint PageResolution;` — Resolution of a page _[#if SHADER_ALLOCATEPAGEINDEX]_
- L32 _parameter_ `uint MacroGroupCount;` _[#if SHADER_ALLOCATEPAGEINDEX]_
- L33 _parameter_ `uint IndirectDispatchGroupSize;` _[#if SHADER_ALLOCATEPAGEINDEX]_
- L34 _parameter_ `uint bDoesMacroGroupSupportVoxelization;` _[#if SHADER_ALLOCATEPAGEINDEX]_
- L37 _parameter_ `float4 CPU_TranslatedWorldMinAABB[MAX_HAIR_MACROGROUP_COUNT];` — For testing parity with CPU version _[#if SHADER_ALLOCATEPAGEINDEX]_
- L38 _parameter_ `float4 CPU_TranslatedWorldMaxAABB[MAX_HAIR_MACROGROUP_COUNT];` _[#if SHADER_ALLOCATEPAGEINDEX]_
- L39 _parameter_ `int4 CPU_PageIndexResolution[MAX_HAIR_MACROGROUP_COUNT];` _[#if SHADER_ALLOCATEPAGEINDEX]_
- L40 _parameter_ `uint CPU_bUseCPUData;` _[#if SHADER_ALLOCATEPAGEINDEX]_
- L164 _parameter_ `uint InstanceRegisteredIndex;` _[#if SHADER_MARKVALID_PREPARE]_
- L165 _parameter_ `uint ClusterOffset;` _[#if SHADER_MARKVALID_PREPARE]_
- L166 _parameter_ `uint ClusterCount;` _[#if SHADER_MARKVALID_PREPARE]_
- L167 _parameter_ `uint MacroGroupId;` _[#if SHADER_MARKVALID_PREPARE]_
- L168 _parameter_ `uint bUseMacroGroupBoundCPU;` _[#if SHADER_MARKVALID_PREPARE]_
- L169 _parameter_ `float3 MacroGroupBoundCPU_TranslatedWorldMinAABB;` _[#if SHADER_MARKVALID_PREPARE]_
- L170 _parameter_ `float3 MacroGroupBoundCPU_TranslatedWorldMaxAABB;` _[#if SHADER_MARKVALID_PREPARE]_
- L171 _parameter_ `float3 TranslatedWorldOffsetCorrection;` _[#if SHADER_MARKVALID_PREPARE]_
- L312 _parameter_ `uint MacroGroupId;` _[#if SHADER_ALLOCATE]_
- L313 _parameter_ `uint PageCount;` _[#if SHADER_ALLOCATE]_
- L314 _parameter_ `uint CPU_PageIndexCount;` _[#if SHADER_ALLOCATE]_
- L315 _parameter_ `uint CPU_PageIndexOffset;` _[#if SHADER_ALLOCATE]_
- L316 _parameter_ `uint3 CPU_PageIndexResolution;` _[#if SHADER_ALLOCATE]_
- L405 _parameter_ `float3 CPU_TranslatedWorldMinAABB;` _[#if SHADER_ADDDESC]_
- L406 _parameter_ `uint MacroGroupId;` _[#if SHADER_ADDDESC]_
- L407 _parameter_ `float3 CPU_TranslatedWorldMaxAABB;` _[#if SHADER_ADDDESC]_
- L408 _parameter_ `uint CPU_PageIndexOffset;` _[#if SHADER_ADDDESC]_
- L409 _parameter_ `int3 CPU_PageIndexResolution;` _[#if SHADER_ADDDESC]_
- L410 _parameter_ `float CPU_VoxelWorldSize;` _[#if SHADER_ADDDESC]_
- L411 _parameter_ `uint bUseCPUVoxelWorldSize;` — When adaptive voxel size is disabled, we use CPU voxel size value _[#if SHADER_ADDDESC]_
- L452 _parameter_ `uint PageResolution;` _[#if SHADER_ADDINDIRECTBUFFER]_
- L453 _parameter_ `uint MacroGroupCount;` _[#if SHADER_ADDINDIRECTBUFFER]_
- L454 _parameter_ `int3 IndirectGroupSize;` _[#if SHADER_ADDINDIRECTBUFFER]_
- L492 _parameter_ `uint VirtualVoxelParams_PageResolution;` _[#if SHADER_INDPAGECLEAR]_
- L493 _parameter_ `int3 VirtualVoxelParams_PageCountResolution;` _[#if SHADER_INDPAGECLEAR]_
- L532 _parameter_ `uint CPUAllocatedPageCount;` _[#if SHADER_ADAPTIVE_FEEDBACK]_
- L533 _parameter_ `float CPUMinVoxelWorldSize;` _[#if SHADER_ADAPTIVE_FEEDBACK]_
- L534 _parameter_ `float AdaptiveCorrectionThreshold;` _[#if SHADER_ADAPTIVE_FEEDBACK]_
- L535 _parameter_ `float AdaptiveCorrectionSpeed;` _[#if SHADER_ADAPTIVE_FEEDBACK]_
- L648 _parameter_ `uint MaxRasterCount;` _[#if SHADER_RASTERCOMPUTE]_
- L649 _parameter_ `uint FrameIdMod8;` _[#if SHADER_RASTERCOMPUTE]_
- L650 _parameter_ `uint MacroGroupId;` _[#if SHADER_RASTERCOMPUTE]_
- L651 _parameter_ `uint VertexCount;` _[#if SHADER_RASTERCOMPUTE]_
- L653 _parameter_ `uint VirtualVoxelParams_PageIndexCount;` _[#if SHADER_RASTERCOMPUTE]_
- L654 _parameter_ `uint VirtualVoxelParams_PageResolution;` _[#if SHADER_RASTERCOMPUTE]_
- L655 _parameter_ `uint3 VirtualVoxelParams_PageCountResolution;` _[#if SHADER_RASTERCOMPUTE]_
- L656 _parameter_ `uint3 VirtualVoxelParams_PageTextureResolution;` _[#if SHADER_RASTERCOMPUTE]_
- L663 _parameter_ `float CoverageScale;` _[#if SHADER_RASTERCOMPUTE]_
- L828 _parameter_ `uint MacroGroupId;` _[#if SHADER_INJECTOPAQUE_VIRTUALVOXEL]_
- L829 _parameter_ `float2 SceneDepthResolution;` _[#if SHADER_INJECTOPAQUE_VIRTUALVOXEL]_
- L830 _parameter_ `uint VoxelBiasCount;` _[#if SHADER_INJECTOPAQUE_VIRTUALVOXEL]_
- L831 _parameter_ `uint VoxelMarkCount;` _[#if SHADER_INJECTOPAQUE_VIRTUALVOXEL]_
- L834 _parameter_ `uint VirtualVoxelParams_PageCount;` _[#if SHADER_INJECTOPAQUE_VIRTUALVOXEL]_
- L835 _parameter_ `uint VirtualVoxelParams_PageIndexCount;` _[#if SHADER_INJECTOPAQUE_VIRTUALVOXEL]_
- L836 _parameter_ `uint VirtualVoxelParams_PageResolution;` _[#if SHADER_INJECTOPAQUE_VIRTUALVOXEL]_
- L837 _parameter_ `uint3 VirtualVoxelParams_PageCountResolution;` _[#if SHADER_INJECTOPAQUE_VIRTUALVOXEL]_
- L919 _parameter_ `float2 OutputResolution;` _[#if SHADER_DEPTH_INJECTION]_
- L920 _parameter_ `uint MacroGroupId;` _[#if SHADER_DEPTH_INJECTION]_
- L921 _parameter_ `uint AtlasSlotIndex;` _[#if SHADER_DEPTH_INJECTION]_
- L923 _parameter_ `float3 LightDirection;` _[#if SHADER_DEPTH_INJECTION]_
- L924 _parameter_ `uint bIsDirectional;` _[#if SHADER_DEPTH_INJECTION]_
- L925 _parameter_ `float3 TranslatedLightPosition;` _[#if SHADER_DEPTH_INJECTION]_
- L1134 _parameter_ `uint bPatchEmptyPage;` _[#if SHADER_MIP_VIRTUALVOXEL]_
- L1135 _parameter_ `int3 PageCountResolution;` _[#if SHADER_MIP_VIRTUALVOXEL]_
- L1136 _parameter_ `uint PageResolution;` _[#if SHADER_MIP_VIRTUALVOXEL]_
- L1137 _parameter_ `uint SourceMip;` _[#if SHADER_MIP_VIRTUALVOXEL]_
- L1138 _parameter_ `uint TargetMip;` _[#if SHADER_MIP_VIRTUALVOXEL]_
- L1302 _parameter_ `uint PageResolution;` _[#if SHADER_MIP_INDIRECTARGS]_
- L1303 _parameter_ `uint TargetMipIndex;` _[#if SHADER_MIP_INDIRECTARGS]_
- L1304 _parameter_ `int3 DispatchGroupSize;` _[#if SHADER_MIP_INDIRECTARGS]_

#### groupshared (5)

- L56 _groupshared_ `groupshared uint PageIndexOffsets[MAX_HAIR_MACROGROUP_COUNT];` _[#if SHADER_ALLOCATEPAGEINDEX]_
- L326 _groupshared_ `groupshared uint LocalCounter;` _[#if SHADER_ALLOCATE]_
- L327 _groupshared_ `groupshared uint GroupBase[2];` _[#if SHADER_ALLOCATE]_
- L1162 _groupshared_ `groupshared uint g_Density4[64][GROUP_SIZE_Z];` _[#if SHADER_MIP_VIRTUALVOXEL && PERMUTATION_MIP_AGGREGATE]_
- L1163 _groupshared_ `groupshared uint g_Density2[8][GROUP_SIZE_Z];` _[#if SHADER_MIP_VIRTUALVOXEL && PERMUTATION_MIP_AGGREGATE]_

#### Functions (6)

- L459-465 _function_ `void WriteArgs(uint WriteIndex, uint AllocatedPageCount)` _[#if SHADER_ADDINDIRECTBUFFER]_
- L541-545 _function_ `float RoundHairVoxelSize(float In)` _[#if SHADER_ADAPTIVE_FEEDBACK]_
- L667-673 _function_ `float3 GetHairVoxelJitter(uint2 PixelCoord, uint Seed)` _[#if SHADER_RASTERCOMPUTE]_
- L1078-1126 _function_ `uint ComputeMipDensity( const uint RawDensity0, const uint RawDensity1, const uint RawDensity2, const uint RawDensity3, const uint RawDensity4, const uint RawDensity5, const uint RawDensity6, const uint RawDensity7)` _[#if SHADER_MIP_VIRTUALVOXEL \|\| SHADER_MIP_INDIRECTARGS]_
- L1144-1147 _function_ `uint MortonEncode3(uint3 Voxel)` _[#if SHADER_MIP_VIRTUALVOXEL]_
- L1149-1153 _function_ `uint3 MortonDecode3(uint Morton)` _[#if SHADER_MIP_VIRTUALVOXEL]_

### `Shaders/Private/HairStrands/RenderCurveRaster.usf` (Private)

- lines: 2638; parse: all-branches
- includes: L5 `/Engine/Public/Platform.ush`, L6 `/Engine/Private/Common.ush`, L7 `/Engine/Private/SceneData.ush`, L8 `/Engine/Shared/RenderCurveDefinitions.h`, L9 `../Nanite/NaniteHZBCull.ush`, L10 `../ColorMap.ush`, L13 `../ShaderPrint.ush` [PERMUTATION_DEBUG]

#### Macros (#define, 33)

- L3 `#define VF_SUPPORTS_PRIMITIVE_SCENE_DATA 1`
- L17 `#define BIN_TILE_SIZE 32`
- L18 `#define BIN_TILE_INV_SIZE (1.f / float(BIN_TILE_SIZE))`
- L19 `#define BIN_TILE_SIZE_DIV_AS_SHIFT 5`
- L22 `#define RASTER_TILE_SIZE 8`
- L23 `#define BIN_RASTER_INV_SIZE (1.f / float(RASTER_TILE_SIZE))`
- L24 `#define RASTER_TILE_SIZE_DIV_AS_SHIFT 3`
- L26 `#define FPackedSegmentType uint4`
- L288 `#define DDA_MAX_ITERATIONS 256`
- L327 `#define USE_SEGMENT_LUT 0`
- L754 `#define BIN_THREAD_COUNT THREADGROUP_SIZE` _[#if defined(SceneTileDepthCS)]_
- L812 `#define VT_PrimOffset 0`
- L813 `#define VT_PrimCount 1`
- L814 `#define VT_Coord 2`
- L815 `#define VT_MinWriteIndex 3`
- L816 `#define VT_SIZE 4`
- L836 `#define SEGMENT_COUNT_PER_ALLOC 1024`
- L843 `#define MAX_TILES_TO_ALLOCATE 1024` _[#if defined(BinningCS)]_
- L844 `#define MAX_THREAD_ITERATION_COUNT 4096` _[#if defined(BinningCS)]_
- L865 `#define PERMUTATION_NUM_POINT_PER_CURVE 16` _[#if defined(BinningCS)]_
- L1228 `#define MAX_SEGMENT_COUNT_PER_ZBIN 1024`
- L1229 `#define MAX_ALLOCATED_ZBIN_COUNT 16`
- L1230 `#define MAX_TILE_TO_COMPACT 1024`
- L1235 `#define COMPACTION_DEPTH_BUCKET 256` _[#if defined(CompactionCS)]_
- L1537 `#define MAX_THREAD_ITERATION_COUNT 4096` _[#if defined(SWRasterizerCS)]_
- L1538 `#define RASTER_TILE_COUNT_2D (BIN_TILE_SIZE / RASTER_TILE_SIZE)` _[#if defined(SWRasterizerCS)]_
- L1539 `#define RASTER_TILE_COUNT_1D (RASTER_TILE_COUNT_2D*RASTER_TILE_COUNT_2D)` _[#if defined(SWRasterizerCS)]_
- L1541 `#define MAX_SEGMENT_PER_RASTER_STEP 32` _[#if defined(SWRasterizerCS)]_
- L1543 `#define WAVE_RASTER 1` _[#if defined(SWRasterizerCS)]_
- L1583 `#define THREADGROUP_WAVE_COUNT (THREADGROUP_SIZE / 32)` _[#if defined(SWRasterizerCS) && WAVE_RASTER]_
- L1598 `#define COVERAGE_CULLING 1` _[#if defined(SWRasterizerCS)]_
- L2340 `#define LUT_RESOLUTION THREADGROUP_SIZE_X` _[#if defined(SegmentLUTCS)]_
- L2342 `#define THREADGROUP_SIZE_X and THREADGROUP_SIZE_Y needs to have the same size` _[#if defined(SegmentLUTCS) && THREADGROUP_SIZE_X != THREADGROUP_SIZE_Y]_

#### Entry points (11)

- L585-641 _entry_ `[numthreads(64, 1, 1)] void InstanceCullingCS(uint2 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FRenderCurveInstanceCullingCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/RenderCurveRaster.cpp:173) _[#if defined(InstanceCullingCS)]_
- L656-740 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void ClusterCullingCS(uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint LinearThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FRenderCurveClusterCullingCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/RenderCurveRaster.cpp:205) _[#if defined(ClusterCullingCS)]_
- L768-799 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void SceneTileDepthCS(uint DispatchThreadID : SV_DispatchThreadID, uint GroupThreadID : SV_GroupThreadID, uint2 GroupID : SV_GroupID)` — stage: **compute** — C++: `FRenderCurveSceneTileDepthCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/RenderCurveRaster.cpp:231) _[#if defined(SceneTileDepthCS)]_
- L1117-1171 _entry_ `[numthreads(THREADGROUP_SIZE_X, THREADGROUP_SIZE_Y, 1)] void BinningCS(uint2 GroupThreadID2D : SV_GroupThreadID, uint GroupThread1D : SV_GroupIndex, uint GroupID : SV_GroupID)` — stage: **compute** — C++: `FRenderCurveBinningCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/RenderCurveRaster.cpp:299) _[#if defined(BinningCS)]_
- L1278-1529 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void CompactionCS(uint DispatchThreadID : SV_DispatchThreadID, uint GroupThreadID : SV_GroupThreadID, uint2 GroupID : SV_GroupID)` — stage: **compute** — C++: `FRenderCurveCompactionCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/RenderCurveRaster.cpp:338) — Launch based on CPU BinTileResX x BinTileResY 1 group per screen-tile, 1 threads per bin-tile matching the screen-tile coord There can be/are several bins for the same screen area _[#if defined(CompactionCS)]_
- L1701-2056 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void SWRasterizerCS(uint DispatchThreadID : SV_DispatchThreadID, uint GroupThread1D : SV_GroupIndex, uint GroupID : SV_GroupID)` — stage: **compute** — C++: `FRenderCurveSWRasterizerCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/RenderCurveRaster.cpp:377) _[#if defined(SWRasterizerCS)]_
- L2096-2310 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void DebugDrawingCS(uint2 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FRenderCurveDebugDrawingCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/RenderCurveRaster.cpp:483) _[#if defined(DebugDrawingCS)]_
- L2345-2435 _entry_ `[numthreads(LUT_RESOLUTION, LUT_RESOLUTION, 1)] void SegmentLUTCS(uint2 DispatchThreadId : SV_DispatchThreadID, uint2 GroupThreadID2D : SV_GroupThreadID, uint2 GroupID : SV_GroupID)` — stage: **compute** — C++: `FRenderCurveSegmentLUTCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/RenderCurveRaster.cpp:144) _[#if defined(SegmentLUTCS)]_
- L2446-2458 _entry_ `[numthreads(THREADGROUP_SIZE, 1, 1)] void IndirectArgsCS(uint GroupThread1D : SV_GroupIndex, uint GroupID : SV_GroupID)` — stage: **compute** — C++: `FRenderCurveIndirectArgsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/RenderCurveRaster.cpp:259) _[#if defined(IndirectArgsCS)]_
- L2516-2624 _entry_ `void HWRasterizerMS( uint GroupThreadID : SV_GroupThreadID, uint3 GroupID : SV_GroupID, MESH_SHADER_VERTEX_EXPORT(VSOut, 128), MESH_SHADER_TRIANGLE_EXPORT(126), MESH_SHADER_PRIMITIVE_EXPORT(VSPrimiveOut, 126) )` — stage: **mesh (from C++ binding)** — C++: `FRenderCurveHWRasterizerMS` SF_Mesh via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/RenderCurveRaster.cpp:405) _[#if defined(HWRasterizerMS)]_
- L2629-2637 _entry_ `void HWRasterizerPS( in float4 SvPosition: SV_Position, in float InCoordU : TEXCOORD1, in uint InPackedAttribute : TEXCOORD2, out float4 OutColor0 : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FRenderCurveHWRasterizerPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/HairStrands/RenderCurveRaster.cpp:428) _[#if defined(HWRasterizerPS)]_

#### Structs / classes (15)

- L85-97 _struct_ **`FRenderCurveInstanceData`** `struct FRenderCurveInstanceData` — Instance
  - L87 _member_ `bool bIsValid;`
  - L88 _member_ `uint PersistentPrimitiveIndex;`
  - L89 _member_ `uint InstanceSceneDataOffset;`
  - L90 _member_ `uint ClusterOffset;`
  - L91 _member_ `uint ClusterCount;`
  - L93 _member_ `float4 TranslatedWorldBoundCenterAndRadius;`
  - L94 _member_ `float3 LocalBoundsCenter;`
  - L95 _member_ `float3 LocalBoundsExtent;`
  - L96 _member_ `float4x4 LocalToTranslatedWorld;`
- L124-134 _struct_ **`FClusterHeader`** `struct FClusterHeader` — Cluster Header
  - L126 _member_ `float3 Center;`
  - L127 _member_ `uint CurveCount;`
  - L128 _member_ `uint CurvePerCluster;`
  - L129 _member_ `uint PointPerCurve;`
  - L130 _member_ `float MaxLength;`
  - L131 _member_ `float MaxRadius;`
  - L132 _member_ `float3 LocalBoundCenter;`
  - L133 _member_ `float3 LocalBoundExtent;`
- L167-175 _struct_ **`FMinMaxZ`** `struct FMinMaxZ`
  - L169 _member_ `float MinZ;`
  - L170 _member_ `float MaxZ;`
  - L171 _member_ `float Range;`
  - L172 _member_ `float InvRange;`
  - L173 _member_ `float Offset;`
  - L174 _member_ `float Scale;`
- L194-200 _struct_ **`FCurvePoint`** `struct FCurvePoint`
  - L196 _member_ `float3 Position;`
  - L197 _member_ `float Radius;`
  - L198 _member_ `float UCoord;`
  - L199 _member_ `bool bValid;`
- L229-234 _struct_ **`FSegment`** `struct FSegment` — 64bit segment encoding Anchor point top-left tile corner * P0.xy = 7/7bit pos + 18bit depth = 32bit * P1.xy = 7/7bit pos + 18bit depth = 32bit
  - L231 _member_ `float3 P0;`
  - L232 _member_ `float3 P1;`
  - L233 _member_ `float3 Color;`
- L290-296 _struct_ **`FDDAContext`** `struct FDDAContext`
  - L292 _member_ `float2 Coord;`
  - L293 _member_ `float2 DeltaDist;`
  - L294 _member_ `float2 Step;`
  - L295 _member_ `float2 SideDist;`
- L867-874 _struct_ **`FDebug`** `struct FDebug` _[#if defined(BinningCS)]_
  - L870 _member_ `FShaderPrintContext Ctx;` _[#if defined(BinningCS) && PERMUTATION_DEBUG]_
  - L872 _member_ `uint GroupID;` _[#if defined(BinningCS)]_
  - L873 _member_ `uint Dummy;` _[#if defined(BinningCS)]_
- L1176-1181 _struct_ **`FRasterWork`** `struct FRasterWork`
  - L1178 _member_ `uint2 TileCoord;`
  - L1179 _member_ `uint ZBinOffset;`
  - L1180 _member_ `uint ZBinCount;`
- L1199-1204 _struct_ **`FZBin`** `struct FZBin`
  - L1201 _member_ `uint BinZIndex;`
  - L1202 _member_ `uint PrimOffset;`
  - L1203 _member_ `uint PrimCount;`
- L1606-1613 _struct_ **`FTileThreadCoord`** `struct FTileThreadCoord` — 8x256 = 2048 8x32  = 256  -> x16  =4096 8x8   = 64   -> x16  =1024 LDS 2.5k per group x16 = 32k _[#if defined(SWRasterizerCS)]_
  - L1608 _member_ `uint2 Tile;` _[#if defined(SWRasterizerCS)]_
  - L1609 _member_ `uint2 Thread;` _[#if defined(SWRasterizerCS)]_
  - L1611 _member_ `uint Tile1d;` _[#if defined(SWRasterizerCS)]_
  - L1612 _member_ `uint Thread1d;` _[#if defined(SWRasterizerCS)]_
- L1615-1618 _struct_ **`FOutputCoord`** `struct FOutputCoord` _[#if defined(SWRasterizerCS)]_
  - L1617 _member_ `uint2 PixelCoord;` _[#if defined(SWRasterizerCS)]_
- L1620-1625 _struct_ **`FCoord`** `struct FCoord` _[#if defined(SWRasterizerCS)]_
  - L1622 _member_ `FTileThreadCoord Bin;` _[#if defined(SWRasterizerCS)]_
  - L1623 _member_ `FTileThreadCoord Raster;` _[#if defined(SWRasterizerCS)]_
  - L1624 _member_ `FOutputCoord Out;` _[#if defined(SWRasterizerCS)]_
- L2464-2468 _struct_ **`VSOut`** `struct VSOut` _[#if defined(HWRasterizerMS) \|\| defined(HWRasterizerPS)]_
  - L2466 _member_ `float4 Position : SV_Position;` _[#if defined(HWRasterizerMS) \|\| defined(HWRasterizerPS)]_
  - L2467 _member_ `float CoordU : TEXCOORD1;` _[#if defined(HWRasterizerMS) \|\| defined(HWRasterizerPS)]_
- L2470-2474 _struct_ **`VSPrimiveOut`** `struct VSPrimiveOut` _[#if defined(HWRasterizerMS) \|\| defined(HWRasterizerPS)]_
  - L2473 _member_ `nointerpolation uint PackedVisibleCurve : TEXCOORD2;` — Use uint4 to prevent compiler from erroneously packing per-vertex and per-prim attributes together _[#if defined(HWRasterizerMS) \|\| defined(HWRasterizerPS)]_
- L2476-2481 _struct_ **`FVisibleCurve`** `struct FVisibleCurve` _[#if defined(HWRasterizerMS) \|\| defined(HWRasterizerPS)]_
  - L2478 _member_ `uint VisibleClusterIndex;` _[#if defined(HWRasterizerMS) \|\| defined(HWRasterizerPS)]_
  - L2479 _member_ `uint CurveIndex;` — uint VisibleClusterIndex;	  [0-65k] _[#if defined(HWRasterizerMS) \|\| defined(HWRasterizerPS)]_
  - L2480 _member_ `uint PointIndex;` — uint CurveIndex; 			  [0-64] _[#if defined(HWRasterizerMS) \|\| defined(HWRasterizerPS)]_

#### Global resources (textures / buffers / samplers) (66)

- L328 _resource_ `Texture2D<uint2> SegmentLUT;`
- L581 _resource_ `RWBuffer<uint> RWVisibleInstanceArgs;` _[#if defined(InstanceCullingCS)]_
- L582 _resource_ `RWStructuredBuffer<uint> RWVisibleInstances;` _[#if defined(InstanceCullingCS)]_
- L583 _resource_ `RWStructuredBuffer<uint> RWMinMaxZ;` _[#if defined(InstanceCullingCS)]_
- L649 _resource_ `Buffer<uint> VisibleInstanceArgs;` _[#if defined(ClusterCullingCS)]_
- L650 _resource_ `StructuredBuffer<uint> VisibleInstances;` _[#if defined(ClusterCullingCS)]_
- L652 _resource_ `RWBuffer<uint> RWVisibleClusterArgs;` _[#if defined(ClusterCullingCS)]_
- L653 _resource_ `RWStructuredBuffer<uint2> RWVisibleClusters;` _[#if defined(ClusterCullingCS)]_
- L654 _resource_ `RWStructuredBuffer<uint> RWMinMaxZ;` _[#if defined(ClusterCullingCS)]_
- L748 _resource_ `Texture2D<float> SceneDepthTexture;` _[#if defined(SceneTileDepthCS)]_
- L749 _resource_ `RWTexture2D<uint2> OutSceneTileDepthTexture;` _[#if defined(SceneTileDepthCS)]_
- L846 _resource_ `StructuredBuffer<uint> ViewMinMaxZ;` _[#if defined(BinningCS)]_
- L847 _resource_ `Texture2D<uint2> SceneTileDepthTexture;` _[#if defined(BinningCS)]_
- L848 _resource_ `StructuredBuffer<uint2> VisibleClusters;` _[#if defined(BinningCS)]_
- L849 _resource_ `StructuredBuffer<uint> VisibleClustersCount;` _[#if defined(BinningCS)]_
- L850 _resource_ `RWStructuredBuffer<uint> VisibleClustersQueue;` _[#if defined(BinningCS)]_
- L852 _resource_ `RWTexture2DArray<uint> RWTileSegmentCount;` _[#if defined(BinningCS)]_
- L853 _resource_ `RWStructuredBuffer<uint> RWTileData;` _[#if defined(BinningCS)]_
- L854 _resource_ `RWStructuredBuffer<FPackedSegmentType> RWSegmentData;` _[#if defined(BinningCS)]_
- L855 _resource_ `RWStructuredBuffer<uint> RWTileDataAllocatedCount;` _[#if defined(BinningCS)]_
- L1241 _resource_ `Texture2D<uint2> SceneTileDepthTexture;` _[#if defined(CompactionCS)]_
- L1242 _resource_ `StructuredBuffer<uint> ViewMinMaxZ;` _[#if defined(CompactionCS)]_
- L1243 _resource_ `Texture2DArray<uint> TileSegmentCount;` _[#if defined(CompactionCS)]_
- L1244 _resource_ `StructuredBuffer<uint> TileData;` _[#if defined(CompactionCS)]_
- L1245 _resource_ `StructuredBuffer<FPackedSegmentType> SegmentData;` _[#if defined(CompactionCS)]_
- L1246 _resource_ `StructuredBuffer<uint> TileDataAllocatedCount;` _[#if defined(CompactionCS)]_
- L1248 _resource_ `RWStructuredBuffer<uint> RWZBinDataAllocatedCount;` _[#if defined(CompactionCS)]_
- L1249 _resource_ `RWStructuredBuffer<uint2> RWZBinData;` _[#if defined(CompactionCS)]_
- L1250 _resource_ `RWStructuredBuffer<uint> RWZBinSegmentAllocatedCount;` _[#if defined(CompactionCS)]_
- L1251 _resource_ `RWStructuredBuffer<FPackedSegmentType> RWZBinSegmentData;` _[#if defined(CompactionCS)]_
- L1253 _resource_ `RWStructuredBuffer<uint> RWRasterWorkAllocatedCount;` _[#if defined(CompactionCS)]_
- L1254 _resource_ `RWStructuredBuffer<uint2> RWRasterWork;` — Offset & Count + tile coord _[#if defined(CompactionCS)]_
- L1562 _resource_ `StructuredBuffer<uint> ViewMinMaxZ;` _[#if defined(SWRasterizerCS)]_
- L1564 _resource_ `StructuredBuffer<uint> ZBinDataAllocatedCount;` _[#if defined(SWRasterizerCS)]_
- L1565 _resource_ `StructuredBuffer<uint2> ZBinData;` _[#if defined(SWRasterizerCS)]_
- L1566 _resource_ `StructuredBuffer<uint> ZBinSegmentAllocatedCount;` _[#if defined(SWRasterizerCS)]_
- L1567 _resource_ `StructuredBuffer<FPackedSegmentType> ZBinSegmentData;` _[#if defined(SWRasterizerCS)]_
- L1569 _resource_ `StructuredBuffer<uint> RasterWorkAllocatedCount;` _[#if defined(SWRasterizerCS)]_
- L1570 _resource_ `StructuredBuffer<uint2> RasterWork;` — Offset & Count + tile coord _[#if defined(SWRasterizerCS)]_
- L1571 _resource_ `RWStructuredBuffer<uint>RasterWorkQueue;` _[#if defined(SWRasterizerCS)]_
- L1573 _resource_ `Texture2D<uint2> SceneTileDepthTexture;` _[#if defined(SWRasterizerCS)]_
- L1574 _resource_ `Texture2D<float> SceneDepthTexture;` _[#if defined(SWRasterizerCS)]_
- L1575 _resource_ `RWTexture2D<float4> OutputTexture;` _[#if defined(SWRasterizerCS)]_
- L2070 _resource_ `Buffer<uint> VisibleInstanceArgs;` _[#if defined(DebugDrawingCS)]_
- L2071 _resource_ `StructuredBuffer<uint2> VisibleInstances;` _[#if defined(DebugDrawingCS)]_
- L2073 _resource_ `Buffer<uint> VisibleClusterArgs;` _[#if defined(DebugDrawingCS)]_
- L2074 _resource_ `StructuredBuffer<uint2> VisibleClusters;` _[#if defined(DebugDrawingCS)]_
- L2076 _resource_ `Texture2D<uint2> SceneTileDepthTexture;` _[#if defined(DebugDrawingCS)]_
- L2077 _resource_ `StructuredBuffer<uint> ViewMinMaxZ;` _[#if defined(DebugDrawingCS)]_
- L2080 _resource_ `Texture2DArray<uint> TileSegmentCount;` _[#if defined(DebugDrawingCS) && PERMUTATION_SWRASTER]_
- L2081 _resource_ `StructuredBuffer<uint> TileDataAllocatedCount;` _[#if defined(DebugDrawingCS) && PERMUTATION_SWRASTER]_
- L2083 _resource_ `StructuredBuffer<uint2> ZBinData;` _[#if defined(DebugDrawingCS) && PERMUTATION_SWRASTER]_
- L2084 _resource_ `StructuredBuffer<uint2> RasterWork;` _[#if defined(DebugDrawingCS) && PERMUTATION_SWRASTER]_
- L2085 _resource_ `StructuredBuffer<uint> RasterWorkAllocatedCount;` _[#if defined(DebugDrawingCS) && PERMUTATION_SWRASTER]_
- L2086 _resource_ `StructuredBuffer<FPackedSegmentType> ZBinSegmentData;` _[#if defined(DebugDrawingCS) && PERMUTATION_SWRASTER]_
- L2087 _resource_ `StructuredBuffer<uint> ZBinSegmentAllocatedCount;` _[#if defined(DebugDrawingCS) && PERMUTATION_SWRASTER]_
- L2088 _resource_ `StructuredBuffer<uint> ZBinDataAllocatedCount;` _[#if defined(DebugDrawingCS) && PERMUTATION_SWRASTER]_
- L2337 _resource_ `RWTexture2D<float4> RWDebugOutput;` _[#if defined(SegmentLUTCS)]_
- L2338 _resource_ `RWTexture2D<uint2> RWSegmentLUT;` _[#if defined(SegmentLUTCS)]_
- L2442 _resource_ `Buffer<uint> InVisibleClusterArgs;` _[#if defined(IndirectArgsCS)]_
- L2443 _resource_ `RWBuffer<uint> OutHWRasterIndirectArgs;` _[#if defined(IndirectArgsCS)]_
- L2444 _resource_ `RWStructuredBuffer<uint> OutVisibleClusterCount;` _[#if defined(IndirectArgsCS)]_
- L2500 _resource_ `StructuredBuffer<uint> ViewMinMaxZ;` _[#if defined(HWRasterizerMS)]_
- L2501 _resource_ `Texture2D<uint2> SceneTileDepthTexture;` _[#if defined(HWRasterizerMS)]_
- L2502 _resource_ `StructuredBuffer<uint2> VisibleClusters;` _[#if defined(HWRasterizerMS)]_
- L2503 _resource_ `StructuredBuffer<uint> VisibleClustersCount;` _[#if defined(HWRasterizerMS)]_

#### Global parameters (uniforms) (16)

- L559 _parameter_ `int2 Resolution;`
- L561 _parameter_ `uint BinTileSize;`
- L562 _parameter_ `int2 BinTileRes;`
- L563 _parameter_ `uint NumBinners;`
- L565 _parameter_ `uint RasterTileSize;`
- L566 _parameter_ `int2 RasterTileRes;`
- L567 _parameter_ `uint NumRasterizers;`
- L569 _parameter_ `uint MaxTileDataCount;`
- L570 _parameter_ `uint MaxSegmentDataCount;`
- L571 _parameter_ `uint MaxZBinDataCount;`
- L572 _parameter_ `uint MaxRasterWorkCount;`
- L573 _parameter_ `uint MaxZBinSegmentDataCount;`
- L575 _parameter_ `float MinCoverageThreshold;`
- L2067 _parameter_ `uint TotalBufferMemoryInMBytes;` _[#if defined(DebugDrawingCS)]_
- L2068 _parameter_ `uint TotalTextureMemoryInMBytes;` _[#if defined(DebugDrawingCS)]_
- L2336 _parameter_ `uint2 DebugOutputResolution;` _[#if defined(SegmentLUTCS)]_

#### groupshared (26)

- L750 _groupshared_ `groupshared uint group_MinDepth;` — (4 bytes) _[#if defined(SceneTileDepthCS)]_
- L751 _groupshared_ `groupshared uint group_MaxDepth;` — (4 bytes) _[#if defined(SceneTileDepthCS)]_
- L857 _groupshared_ `groupshared uint group_TilesToAllocate[MAX_TILES_TO_ALLOCATE];` _[#if defined(BinningCS)]_
- L858 _groupshared_ `groupshared uint group_TilesToAllocateCount;` _[#if defined(BinningCS)]_
- L859 _groupshared_ `groupshared uint group_ClusterIndex;` _[#if defined(BinningCS)]_
- L860 _groupshared_ `groupshared uint group_ClusterFetchIndex;` _[#if defined(BinningCS)]_
- L861 _groupshared_ `groupshared float4x4 group_LocalToClip;` _[#if defined(BinningCS)]_
- L862 _groupshared_ `groupshared FClusterHeader group_ClusterHeader;` _[#if defined(BinningCS)]_
- L1256 _groupshared_ `groupshared uint group_TilePrimCount;` _[#if defined(CompactionCS)]_
- L1257 _groupshared_ `groupshared uint group_TilePrimOffset;` _[#if defined(CompactionCS)]_
- L1258 _groupshared_ `groupshared uint group_TileToCompactCount;` _[#if defined(CompactionCS)]_
- L1259 _groupshared_ `groupshared uint group_TileToCompact[MAX_TILE_TO_COMPACT];` _[#if defined(CompactionCS)]_
- L1261 _groupshared_ `groupshared uint group_MaxZBinIndex;` _[#if defined(CompactionCS)]_
- L1262 _groupshared_ `groupshared uint group_ZBinOffset[COMPACTION_DEPTH_BUCKET];` _[#if defined(CompactionCS)]_
- L1263 _groupshared_ `groupshared uint group_ZBinCount[COMPACTION_DEPTH_BUCKET];` _[#if defined(CompactionCS)]_
- L1265 _groupshared_ `groupshared uint group_ZBinAllocatedOffset[MAX_ALLOCATED_ZBIN_COUNT];` _[#if defined(CompactionCS)]_
- L1266 _groupshared_ `groupshared uint group_ZBinAllocatedCount[MAX_ALLOCATED_ZBIN_COUNT];` _[#if defined(CompactionCS)]_
- L1577 _groupshared_ `groupshared uint group_WorkFetchIndex;` _[#if defined(SWRasterizerCS)]_
- L1578 _groupshared_ `groupshared uint group_Valid;` _[#if defined(SWRasterizerCS)]_
- L1579 _groupshared_ `groupshared FRasterWork group_Work;` _[#if defined(SWRasterizerCS)]_
- L1581 _groupshared_ `groupshared FPackedSegmentType group_PackedSegments[MAX_SEGMENT_COUNT_PER_ZBIN];` _[#if defined(SWRasterizerCS)]_
- L1587 _groupshared_ `groupshared uint2 group_SegmentsBits[THREADGROUP_SIZE];` _[#if defined(SWRasterizerCS) && WAVE_RASTER]_
- L1588 _groupshared_ `groupshared float group_SegmentsColor[THREADGROUP_SIZE];` _[#if defined(SWRasterizerCS) && WAVE_RASTER]_
- L1589 _groupshared_ `groupshared uint group_CompletedWaves[RASTER_TILE_COUNT_1D * 2];` — Wave _[#if defined(SWRasterizerCS) && WAVE_RASTER]_
- L1591 _groupshared_ `groupshared uint2 group_SegmentsBits[RASTER_TILE_COUNT_1D][MAX_SEGMENT_PER_RASTER_STEP];` — 8x8 bit mask per segments. 32 segments _[#if defined(SWRasterizerCS) && !(WAVE_RASTER)]_
- L1596 _groupshared_ `groupshared uint group_SceneMaxZ[RASTER_TILE_COUNT_1D];` _[#if defined(SWRasterizerCS)]_

#### Functions (45)

- L38-47 _function_ `FShaderPrintContext InitShaderPrintContextUnique(bool bActive, uint2 InBaseCoord, uint2 InOffset)` _[#if PERMUTATION_DEBUG]_
- L50-59 _function_ `FShaderPrintContext InitShaderPrintContextAtCursorUnique(uint2 ActiveCoord, uint2 InBaseCoord, uint2 InOffset)` _[#if PERMUTATION_DEBUG]_
- L61-71 _function_ `void PlotCondition(inout FShaderPrintContext Ctx, bool bCondition)` _[#if PERMUTATION_DEBUG]_
- L78 _function_ `uint PackR7(float In)`
- L79 _function_ `float UnpackR7(uint In)`
- L80 _function_ `uint PackR18(float In)`
- L81 _function_ `float UnpackR18(uint In)`
- L99-120 _function_ `FRenderCurveInstanceData GetRenderCurveInstanceData(uint InPrimitiveIndex)`
- L136-162 _function_ `FClusterHeader GetClusterHeader(uint InClusterIndex)`
- L177-189 _function_ `FMinMaxZ UnpackMinMaxZ(uint In0, uint In1, float SceneDepthMinZ=0.f)`
- L202-211 _function_ `FCurvePoint UnpackCurvePoint(uint2 In, float3 InPositionOffset, float InMaxRadius)`
- L213-220 _function_ `FCurvePoint GetClusterPoint(FClusterHeader Header, uint ClusterIndex, uint CurveIndex, uint PointIndex)`
- L238-265 _function_ `FPackedSegmentType PackSegment(uint2 TileCoord, FMinMaxZ MinMaxZ, FSegment In)`
- L267-282 _function_ `FSegment UnpackSegment(uint2 TileCoord, FMinMaxZ MinMaxZ, FPackedSegmentType In)`
- L298-309 _function_ `FDDAContext DDACreateContext(float2 RayStart, float2 RayDir)`
- L311-323 _function_ `void DDAAdvance(inout FDDAContext Context)`
- L333-394 _function_ `uint2 GetSegmentBits(Texture2D<float> InSceneDepthTexture, uint2 InCoordOffset, float2 Pos0, float2 Pos1, float PosZ0, float PosZ1, bool bDepthTestEnable)` — Output a 8x8 bitmask of the rastized segment * Pos0/Pos1 are in [0..1] * Pos0/Pos1 are clipped to border
- L398-409 _function_ `bool HZB(FFrustumCullData FrustumCull)` — HZB
- L413-416 _function_ `uint2 PackDepth(float2 In)`
- L418-421 _function_ `float2 UnpackDepth(uint2 In)`
- L426-431 _function_ `float3 NDCToPixelCoord(float4 InDC, uint2 InResolution)`
- L434-478 _function_ `bool BlinnLineClipping(inout float4 P0, inout float4 P1)` — Line clipping based on "CLIPPING USING HOMOGENEOUS COORDINATES" by Blinn et al.
- L480-518 _function_ `bool InternalClipSegment(float2 AABBMin, float2 AABBMax, float2 P0, float2 P1, out float2 T, out bool2 bClipped)`
- L520-548 _function_ `bool ClipSegment(float2 AABBMin, float2 AABBMax, inout float3 P0, inout float3 P1)`
- L551-554 _function_ `float3 GetCurveColor(uint ClusterIndex, uint CurveIndex)`
- L760-766 _function_ `uint2 LinearTo2D_Bin(uint In)` _[#if defined(SceneTileDepthCS)]_
- L818-822 _function_ `void StoreTileData(RWStructuredBuffer<uint> OutBuffer, uint Index, uint VTEntry, uint Value)`
- L823-827 _function_ `uint LoadTileData(RWStructuredBuffer<uint> OutBuffer, uint Index, uint VTEntry)`
- L828-832 _function_ `uint LoadTileData(StructuredBuffer<uint> OutBuffer, uint Index, uint VTEntry)`
- L880-1115 _function_ `void BinCluster(FClusterHeader ClusterHeader, uint BinnerIndex, uint ClusterIndex, uint CurveIt, uint PointIt0, uint PointIt1, float4x4 LocalToClip, uint GroupThreadID, inout FDebug Debug)` _[#if defined(BinningCS)]_
- L1183-1186 _function_ `uint2 PackRasterWork(FRasterWork In)`
- L1188-1195 _function_ `FRasterWork UnpackRasterWork(uint2 In)`
- L1206-1209 _function_ `uint2 PackZBin(FZBin In)`
- L1211-1218 _function_ `FZBin UnpackZBin(uint2 In)`
- L1268-1273 _function_ `uint GetZBinIndex(float InDepth, FMinMaxZ InMinMaxZ)` _[#if defined(CompactionCS)]_
- L1627-1641 _function_ `void DrawBitLine(RWTexture2D<float4> Out, uint2 OutResolution, uint2 OutBaseCoord, uint2 In)` _[#if defined(SWRasterizerCS)]_
- L1643-1660 _function_ `void PlotRasterTileCoverage(inout FShaderPrintContext Ctx, uint RasterTile1d)` _[#if defined(SWRasterizerCS) && PERMUTATION_DEBUG]_
- L1662-1676 _function_ `void PlotWorkInfo(inout FShaderPrintContext Ctx, FCoord InCoord)` _[#if defined(SWRasterizerCS) && PERMUTATION_DEBUG]_
- L1678-1683 _function_ `void PlotRasterTileAABB(inout FShaderPrintContext Ctx, FCoord InCoord)` _[#if defined(SWRasterizerCS) && PERMUTATION_DEBUG]_
- L1685-1690 _function_ `void PlotUnclippedSegment(FCoord InCoord, uint SegIt, FMinMaxZ MinMaxZ)` _[#if defined(SWRasterizerCS) && PERMUTATION_DEBUG]_
- L1692-1698 _function_ `FShaderPrintContext GetShaderPrintContextPerRasterThread(FCoord Coord)` _[#if defined(SWRasterizerCS) && PERMUTATION_DEBUG]_
- L2091-2094 _function_ `void PrintRatio(inout FShaderPrintContext Ctx, uint In, uint InMax, uint InDigit)` _[#if defined(DebugDrawingCS)]_
- L2319-2333 _function_ `void DrawBitLine(RWTexture2D<float4> Out, uint2 OutResolution, uint2 OutBaseCoord, uint2 In)` _[#if defined(SegmentLUTCS) && PERMUTATION_DEBUG]_
- L2483-2486 _function_ `uint PackCurveSegment(FVisibleCurve In)` _[#if defined(HWRasterizerMS) \|\| defined(HWRasterizerPS)]_
- L2488-2495 _function_ `FVisibleCurve UnpackCurveSegment(uint In)` _[#if defined(HWRasterizerMS) \|\| defined(HWRasterizerPS)]_

#### Prototypes (1)

- L236 _prototype_ `bool ClipSegment(float2 AABBMin, float2 AABBMax, inout float3 P0, inout float3 P1)`

#### Top-level macro invocations (1)

- L2515 _macro_call_ `MESH_SHADER_TRIANGLE_ATTRIBUTES(128)` _[#if defined(HWRasterizerMS)]_
