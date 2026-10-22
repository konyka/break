# Shaders / Shaders/Shared

- files: 37; lines: 4199
- record kinds: ctor=1, define=1059, enum=3, enumerator=21, function=45, include=28, macro_call=11, member=509, method=7, namespace=14, parameter=1, prototype=4, resource=1, static_const=2, static_var=2, struct=74, typedef=38, unparsed=3

### `Shaders/Shared/EnvironmentComponentsFlags.h` (Shared)

- lines: 34; parse: all-branches

#### Macros (#define, 12)

- L16 `#define ENVCOMP_FLAG_SKYATMOSPHERE_HOLDOUT 0x01`
- L17 `#define ENVCOMP_FLAG_VOLUMETRICCLOUD_HOLDOUT 0x02`
- L18 `#define ENVCOMP_FLAG_EXPONENTIALFOG_HOLDOUT 0x04`
- L20 `#define ENVCOMP_FLAG_SKYATMOSPHERE_RENDERINMAIN 0x08`
- L21 `#define ENVCOMP_FLAG_VOLUMETRICCLOUD_RENDERINMAIN 0x10`
- L22 `#define ENVCOMP_FLAG_EXPONENTIALFOG_RENDERINMAIN 0x20`
- L26 `#define IsSkyAtmosphereHoldout(EnvironmentComponentsFlags) ((EnvironmentComponentsFlags[0] & ENVCOMP_FLAG_SKYATMOSPHERE_HOLDOUT) > 0)`
- L27 `#define IsVolumetricCloudHoldout(EnvironmentComponentsFlags) ((EnvironmentComponentsFlags[0] & ENVCOMP_FLAG_VOLUMETRICCLOUD_HOLDOUT) > 0)`
- L28 `#define IsExponentialFogHoldout(EnvironmentComponentsFlags) ((EnvironmentComponentsFlags[0] & ENVCOMP_FLAG_EXPONENTIALFOG_HOLDOUT) > 0)`
- L30 `#define IsSkyAtmosphereRenderedInMain(EnvironmentComponentsFlags) ((EnvironmentComponentsFlags[0] & ENVCOMP_FLAG_SKYATMOSPHERE_RENDERINMAIN) > 0)`
- L31 `#define IsVolumetricCloudRenderedInMain(EnvironmentComponentsFlags) ((EnvironmentComponentsFlags[0] & ENVCOMP_FLAG_VOLUMETRICCLOUD_RENDERINMAIN) > 0)`
- L32 `#define IsExponentialFogRenderedInMain(EnvironmentComponentsFlags) ((EnvironmentComponentsFlags[0] & ENVCOMP_FLAG_EXPONENTIALFOG_RENDERINMAIN) > 0)`
- L7 #pragma `once`; L12 #pragma `message("UESHADERMETADATA_VERSION 8F92177A-03B9-4AA9-A983-3CA04895E84A")`

### `Shaders/Shared/FroxelDefinitions.h` (Shared)

- lines: 39; parse: all-branches
- includes: L18 `HLSLTypeAliases.h` [defined(__cplusplus)]

#### Macros (#define, 5)

- L10 `#define FROXEL_TILE_SIZE (8)`
- L11 `#define FROXEL_INVALID_SLICE (1 << 28)`
- L12 `#define FROXEL_INVALID_PACKED_SLICE (FROXEL_INVALID_SLICE << 2)`
- L13 `#define FROXEL_PACKED_SLICE_BIAS (1 << 20)`
- L14 `#define FROXEL_INDIRECT_ARG_WORKGROUP_SIZE (64)`
- L8 #pragma `once`

#### Structs / classes (1)

- L24-28 _struct_ **`UE::HLSL::FPackedFroxel`** `struct FPackedFroxel`
  - L26 _member_ `uint XY;`
  - L27 _member_ `int Z;`

#### Namespaces (2)

- L20-32 _namespace_ **`UE::HLSL`** `namespace UE::HLSL` _[#if defined(__cplusplus)]_
- L34-37 _namespace_ **`Froxel`** `namespace Froxel` _[#if defined(__cplusplus)]_

#### typedef / using (1)

- L36 _typedef_ `using FPackedFroxel = UE::HLSL::FPackedFroxel;` (scope `Froxel`) _[#if defined(__cplusplus)]_

### `Shaders/Shared/HLSLMathAliases.h` (Shared)

- lines: 36; parse: all-branches
- includes: L10 `Math/UnrealMathUtility.h`
- L3 #pragma `once`

#### Namespaces (1)

- L12-34 _namespace_ **`UE::HLSL`** `namespace UE::HLSL`

#### Functions (4)

- L14-17 _function_ `inline float log2(float Value)` (scope `UE::HLSL`)
- L19-22 _function_ `inline float floor(float Value)` (scope `UE::HLSL`)
- L24-28 _function_ `template <typename ValueType> inline float max(ValueType A, ValueType B)` (scope `UE::HLSL`)
- L29-33 _function_ `template <typename ValueType> inline float min(ValueType A, ValueType B)` (scope `UE::HLSL`)

### `Shaders/Shared/HLSLReservedSpaces.h` (Shared)

- lines: 58; parse: all-branches

#### Macros (#define, 21)

- L6 `#define INCLUDED_FROM_CPP_CODE 1` _[#if defined(__cplusplus)]_
- L7 `#define INCLUDED_FROM_HLSL_CODE 0` _[#if defined(__cplusplus)]_
- L9 `#define INCLUDED_FROM_CPP_CODE 0` _[#if !(defined(__cplusplus))]_
- L10 `#define INCLUDED_FROM_HLSL_CODE 1` _[#if !(defined(__cplusplus))]_
- L14 `#define UE_REG_CONCATENATE2(a, b) a##b` _[#if INCLUDED_FROM_HLSL_CODE]_
- L15 `#define UE_REG_CONCATENATE(a, b) UE_REG_CONCATENATE2(a, b)` _[#if INCLUDED_FROM_HLSL_CODE]_
- L16 `#define UE_HLSL_REGISTER(InType, InIndex, InSpace) register(UE_REG_CONCATENATE(InType, InIndex), UE_REG_CONCATENATE(space, InSpace))` _[#if INCLUDED_FROM_HLSL_CODE]_
- L20 `#define UE_HLSL_SPACE_DEFAULT 0`
- L23 `#define UE_HLSL_SPACE_RAY_TRACING_LOCAL 0`
- L26 `#define UE_HLSL_SPACE_RAY_TRACING_GLOBAL 1`
- L29 `#define UE_HLSL_SPACE_RAY_TRACING_SYSTEM 2`
- L33 `#define UE_HLSL_SPACE_WORK_GRAPH_LOCAL_PIXEL UE_HLSL_SPACE_DEFAULT`
- L36 `#define UE_HLSL_SPACE_WORK_GRAPH_GLOBAL 1`
- L39 `#define UE_HLSL_SPACE_WORK_GRAPH_LOCAL 2`
- L42 `#define UE_HLSL_SPACE_SHADER_ROOT_CONSTANTS 3`
- L45 `#define UE_HLSL_SPACE_STATIC_SHADER_BINDINGS 4`
- L48 `#define UE_HLSL_SPACE_DIAGNOSTIC 999`
- L53 `#define UE_HLSL_SLOT_NV_SHADER_EXTN 0`
- L54 `#define UE_HLSL_SPACE_NV_SHADER_EXTN 1001`
- L56 `#define NV_SHADER_EXTN_SLOT UE_REG_CONCATENATE(u, UE_HLSL_SLOT_NV_SHADER_EXTN)`
- L57 `#define NV_SHADER_EXTN_REGISTER_SPACE UE_REG_CONCATENATE(space, UE_HLSL_SPACE_NV_SHADER_EXTN)`
- L3 #pragma `once`

### `Shaders/Shared/HLSLStaticAssert.h` (Shared)

- lines: 30; parse: all-branches

#### Macros (#define, 3)

- L15 `#define HLSL_STATIC_ASSERT(Expr, Msg) static_assert(Expr, Msg)` _[#if !(defined(HLSL_STATIC_ASSERT)) && defined(__cplusplus) \|\| COMPILER_PSSL]_
- L20 `#define HLSL_STATIC_ASSERT(Expr, Msg) _Static_assert(Expr, Msg)` _[#if !(defined(HLSL_STATIC_ASSERT)) && !(defined(__cplusplus) \|\| COMPILER_PSSL) && COMPILER_DXC && !COMPILER_VULKAN]_
- L25 `#define HLSL_STATIC_ASSERT(Expr, Msg) ` _[#if !(defined(HLSL_STATIC_ASSERT)) && !(defined(__cplusplus) \|\| COMPILER_PSSL) && !(COMPILER_DXC && !COMPILER_VULKAN)]_
- L3 #pragma `once`

#### Top-level macro invocations (1)

- L8 _macro_call_ `HLSL_STATIC_ASSERT(true, "Verify that custom static assert works")` _[#if defined(HLSL_STATIC_ASSERT)]_

### `Shaders/Shared/HLSLTypeAliases.h` (Shared)

- lines: 36; parse: all-branches
- includes: L10 `Math/MathFwd.h`, L11 `Misc/LargeWorldRenderPosition.h`
- L3 #pragma `once`

#### Namespaces (1)

- L13-34 _namespace_ **`UE::HLSL`** `namespace UE::HLSL`

#### typedef / using (12)

- L15 _typedef_ `using int2 = FIntVector2;` (scope `UE::HLSL`)
- L16 _typedef_ `using int3 = FIntVector3;` (scope `UE::HLSL`)
- L17 _typedef_ `using int4 = FIntVector4;` (scope `UE::HLSL`)
- L19 _typedef_ `using uint = uint32;` (scope `UE::HLSL`)
- L20 _typedef_ `using uint2 = FUintVector2;` (scope `UE::HLSL`)
- L21 _typedef_ `using uint3 = FUintVector3;` (scope `UE::HLSL`)
- L22 _typedef_ `using uint4 = FUintVector4;` (scope `UE::HLSL`)
- L27 _typedef_ `using float2 = FVector2f;` (scope `UE::HLSL`)
- L28 _typedef_ `using float3 = FVector3f;` (scope `UE::HLSL`)
- L29 _typedef_ `using float4 = FVector4f;` (scope `UE::HLSL`)
- L31 _typedef_ `using float4x4 = FMatrix44f;` (scope `UE::HLSL`)
- L33 _typedef_ `using FLWCVector3 = TLargeWorldRenderPosition<float>;` (scope `UE::HLSL`)

### `Shaders/Shared/HairStrandsDefinitions.h` (Shared)

- lines: 147; parse: last-branch (retry, +0 merged from all-branches pass)

#### Macros (#define, 55)

- L11 `#define HAIRSTRANDS_SHADER_VERSION 0x3ba5af0e`
- L14 `#define HAIR_CURVE_ATTRIBUTE_ROOTUV 0`
- L15 `#define HAIR_CURVE_ATTRIBUTE_SEED 1`
- L16 `#define HAIR_CURVE_ATTRIBUTE_LENGTH 2`
- L17 `#define HAIR_CURVE_ATTRIBUTE_CLUMPID 3`
- L18 `#define HAIR_CURVE_ATTRIBUTE_CLUMPID3 4`
- L19 `#define HAIR_CURVE_ATTRIBUTE_COUNT 5`
- L22 `#define HAIR_POINT_ATTRIBUTE_COLOR 0`
- L23 `#define HAIR_POINT_ATTRIBUTE_ROUGHNESS 1`
- L24 `#define HAIR_POINT_ATTRIBUTE_AO 2`
- L25 `#define HAIR_POINT_ATTRIBUTE_COUNT 3`
- L28 `#define HAIR_MAX_NUM_POINT_PER_CURVE ((1u<<8)-1u)`
- L29 `#define HAIR_MAX_NUM_POINT_PER_GROUP ((1u<<24)-1u)`
- L30 `#define HAIR_MAX_NUM_CURVE_PER_GROUP ((1u<<22)-1u)`
- L32 `#define HAIR_ATTRIBUTE_INVALID_OFFSET 0xFFFFFFFF`
- L35 `#define HAIR_INTERPOLATION_CURVE_STRIDE 8`
- L36 `#define HAIR_INTERPOLATION_POINT_STRIDE 2`
- L37 `#define HAIR_INTERPOLATION_MAX_GUIDE_COUNT 2`
- L39 `#define HAIR_INTERPOLATION_CARDS_GUIDE_STRIDE 4`
- L42 `#define MAX_HAIR_LOD 8`
- L45 `#define STRANDS_PROCEDURAL_INTERSECTOR_MAX_SPLITS 4`
- L48 `#define HAIR_POINT_TO_VERTEX_FOR_TRISTRP 2u`
- L49 `#define HAIR_POINT_TO_VERTEX_FOR_TRILIST 6u`
- L53 `#define HAIR_POINT_TO_VERTEX HAIR_POINT_TO_VERTEX_FOR_TRISTRP` _[#if !defined(__cplusplus) && USE_HAIR_TRIANGLE_STRIP]_
- L55 `#define HAIR_POINT_TO_VERTEX HAIR_POINT_TO_VERTEX_FOR_TRILIST` _[#if !defined(__cplusplus) && !(USE_HAIR_TRIANGLE_STRIP)]_
- L60 `#define HAIR_POINT_TO_TRIANGLE 2u`
- L63 `#define HAIR_CONTROLPOINT_INSIDE 0u`
- L64 `#define HAIR_CONTROLPOINT_START 1u`
- L65 `#define HAIR_CONTROLPOINT_END 2u`
- L70 `#define HAIR_VERTEXCOUNT_GROUP_SIZE 1024u`
- L71 `#define HAIR_CURVECOUNT_GROUP_SIZE 1024u`
- L72 `#define HAIR_CLUSTERCOUNT_GROUP_SIZE 1024u`
- L74 `#define MAX_HAIR_MACROGROUP_COUNT 16`
- L77 `#define HAIR_CURVE_ATTRIBUTE_OFFSET_COUNT ((HAIR_CURVE_ATTRIBUTE_COUNT + 3) / 4)`
- L78 `#define HAIR_POINT_ATTRIBUTE_OFFSET_COUNT ((HAIR_POINT_ATTRIBUTE_COUNT + 3) / 4)`
- L81 `#define PACK_HAIR_ATTRIBUTE_OFFSETS(Out, In, Offset, Count) for (uint32 AttributeIt4 = 0; AttributeIt4 < Offset; ++AttributeIt4) { Out[AttributeIt4] = FUintVector4(HAIR_ATTRIBUTE_INVALID_OFFSET, HAIR_ATTRIBUTE_INVALID_OFFSET, HAIR_ATTRIBUTE_INVALID_OFFSET, HAI ...` (12 lines)
- L94 `#define PACK_CURVE_HAIR_ATTRIBUTE_OFFSETS(Out, In) PACK_HAIR_ATTRIBUTE_OFFSETS(Out, In, HAIR_CURVE_ATTRIBUTE_OFFSET_COUNT, HAIR_CURVE_ATTRIBUTE_COUNT)`
- L95 `#define PACK_POINT_HAIR_ATTRIBUTE_OFFSETS(Out, In) PACK_HAIR_ATTRIBUTE_OFFSETS(Out, In, HAIR_POINT_ATTRIBUTE_OFFSET_COUNT, HAIR_POINT_ATTRIBUTE_COUNT)`
- L100 `#define HAIR_POINT_LOD_BIT_COUNT 4`
- L101 `#define HAIR_POINT_LOD_COUNT_PER_UINT (32u/4u)`
- L102 `#define HAIR_POINT_LOD_COUNT_PER_UINT_DIV_AS_SHIFT 3`
- L104 `#define HAIR_RBF_ENTRY_COUNT(InSampleCount) ((InSampleCount)+4u)`
- L106 `#define HAIR_CARDS_MAX_TEXTURE_COUNT 6`
- L108 `#define HAIR_MIN_VOXEL_SIZE 0.01f`
- L109 `#define HAIR_MAX_VOXEL_SIZE 100.f`
- L112 `#define HAIR_FLAGS_SCATTER_SCENE_LIGHT 0x1u`
- L113 `#define HAIR_FLAGS_STABLE_RASTER 0x2u`
- L114 `#define HAIR_FLAGS_RAYTRACING_GEOMETRY 0x4u`
- L115 `#define HAIR_FLAGS_HOLDOUT 0x8u`
- L116 `#define HAIR_FLAGS_CAST_CONTACT_SHADOW 0x10u`
- L137 `#define FPackedHairPosition uint2`
- L138 `#define FPackedHairPositionStrideInBytes 8u`
- L145 `#define FCompressedHairPositions uint4`
- L146 `#define FCompressedHairPositionsStrideInBytes 16u`
- L147 `#define HAIR_POINT_COUNT_PER_COMPRESSED_POSITION_CHUNK 3`
- L8 #pragma `once`

#### Functions (1)

- L121-125 _function_ `FORCEINLINE bool HasHairFlags(uint32 In, uint32 Flags)` _[#if !(!defined(__cplusplus))]_

### `Shaders/Shared/IndirectVirtualTextureDefinitions.h` (Shared)

- lines: 30; parse: all-branches
- includes: L6 `HLSLTypeAliases.h` [defined(__cplusplus)]
- L3 #pragma `once`

#### Structs / classes (2)

- L11-17 _struct_ **`UE::HLSL::FIndirectVirtualTextureUniform`** `struct FIndirectVirtualTextureUniform`
  - L13 _member_ `uint3 Pad;`
  - L14 _member_ `uint UniformCountSub1;`
  - L15 _member_ `uint4 PackedPageTableUniform[2];`
  - L16 _member_ `uint4 PackedUniform;`
- L19-23 _struct_ **`UE::HLSL::FIndirectVirtualTextureEntry`** `struct FIndirectVirtualTextureEntry`
  - L22 _member_ `uint2 PackedCoordinateAndSize;` — Could be packed in one uint if we accept 4k textures as max

#### Namespaces (1)

- L7-28 _namespace_ **`UE::HLSL`** `namespace UE::HLSL` _[#if defined(__cplusplus)]_

#### static const (1)

- L25 _static_const_ `static const uint IndirectVirtualTextureUniformDWord4Count = 4u;` (scope `UE::HLSL`)

### `Shaders/Shared/InstanceCullingDefinitions.h` (Shared)

- lines: 12; parse: all-branches

#### Macros (#define, 6)

- L5 `#define INSTANCE_CULLING_PRESERVE_INSTANCE_ORDER_BIT_MASK 1U`
- L6 `#define INSTANCE_CULLING_DYNAMIC_INSTANCE_DATA_OFFSET_BIT_MASK 2U`
- L8 `#define INSTANCE_CULLING_PAYLOAD_NUM_COMMON_BITS 2U`
- L10 `#define INSTANCE_CULLING_FLAGS_BITS (2u)`
- L11 `#define INSTANCE_CULLING_FLAGS_ALLOW_OCCLUSION_CULLING (1u << 0u)`
- L12 `#define INSTANCE_CULLING_FLAGS_DRAW_ONLY_SELECTED (1u << 1u)`
- L3 #pragma `once`

### `Shaders/Shared/LightDefinitions.h` (Shared)

- lines: 24; parse: all-branches

#### Macros (#define, 16)

- L5 `#define LIGHT_TYPE_DIRECTIONAL 0`
- L6 `#define LIGHT_TYPE_POINT 1`
- L7 `#define LIGHT_TYPE_SPOT 2`
- L8 `#define LIGHT_TYPE_RECT 3`
- L9 `#define LIGHT_TYPE_MAX 4`
- L11 `#define LIGHT_EXTRA_DATA_BIT_OFFSET_SHADOW_MAP_CHANNEL_MASK 0`
- L12 `#define LIGHT_EXTRA_DATA_BIT_OFFSET_LIGHTING_CHANNEL_MASK 8`
- L13 `#define LIGHT_EXTRA_DATA_BIT_OFFSET_LIGHT_TYPE 11`
- L14 `#define LIGHT_EXTRA_DATA_BIT_OFFSET_CAST_SHADOW 13`
- L15 `#define LIGHT_EXTRA_DATA_BIT_OFFSET_HAS_LIGHT_FUNCTION 14`
- L16 `#define LIGHT_EXTRA_DATA_BIT_OFFSET_LIGHT_FUNCTION_ATLAS_LIGHT_INDEX 15`
- L17 `#define LIGHT_EXTRA_DATA_BIT_OFFSET_AFFECT_TRANSLUCENT_LIGHTING 23`
- L18 `#define LIGHT_EXTRA_DATA_BIT_OFFSET_MEGA_LIGHT 24`
- L19 `#define LIGHT_EXTRA_DATA_BIT_OFFSET_CLUSTERED_DEFERRED_SUPPORTED 25`
- L20 `#define LIGHT_EXTRA_DATA_BIT_OFFSET_CAST_VOLUMETRIC_SHADOWS 26`
- L21 `#define LIGHT_EXTRA_DATA_BIT_OFFSET_USE_TRANSMISSION 27`
- L3 #pragma `once`

### `Shaders/Shared/LightGridDefinitions.h` (Shared)

- lines: 15; parse: all-branches

#### Macros (#define, 4)

- L10 `#define LIGHT_GRID_CELL_WRITER_MAX_NUM_PRIMITIVES (1 << 24)`
- L11 `#define LIGHT_GRID_CELL_WRITER_MAX_PRIMITIVE_INDEX (LIGHT_GRID_CELL_WRITER_MAX_NUM_PRIMITIVES - 1)`
- L13 `#define LIGHT_GRID_CELL_WRITER_MAX_NUM_LINKS (1 << 24)`
- L14 `#define LIGHT_GRID_CELL_WRITER_MAX_LINK_OFFSET (LIGHT_GRID_CELL_WRITER_MAX_NUM_LINKS - 1)`
- L7 #pragma `once`

### `Shaders/Shared/LightSceneData.h` (Shared)

- lines: 97; parse: all-branches
- includes: L6 `HLSLTypeAliases.h` [defined(__cplusplus)], L12 `/Engine/Private/LargeWorldCoordinates.ush` [!defined(__cplusplus)]

#### Macros (#define, 1)

- L91 `#define SIZEOF_LIGHT_SCENE_DATA 96`
- L3 #pragma `once`

#### Structs / classes (1)

- L19-62 _struct_ **`UE::HLSL::FLightSceneData`** `struct FLightSceneData` — Has a 1:1 mapping with FLightRenderParameters, but unlike FLightShaderParameters, this is view-independent
  - L22 _member_ `FDFVector3 WorldPosition;` — Position of the light in world space.
  - L25 _member_ `float InvRadius;` — 1 / light's falloff radius from Position.
  - L28 _member_ `float FalloffExponent;` — The exponent for the falloff of the light intensity from the distance.
  - L31 _member_ `float3 Direction;` — Direction of the light if applies.
  - L33 _member_ `float InverseExposureBlend;`
  - L37 _member_ `float3 Tangent;` — One tangent of the light if applies. Note: BiTangent is on purpose not stored for memory optimisation purposes.
  - L40 _member_ `float SourceRadius;` — Radius of the point light.
  - L43 _member_ `float2 SpotAngles;` — Dimensions of the light, for spot light, but also
  - L46 _member_ `float SoftSourceRadius;` — Radius of the soft source.
  - L49 _member_ `float SourceLength;` — Other dimensions of the light source for rect light specifically.
  - L52 _member_ `float RectLightBarnCosAngle;` — Barn door angle for rect light
  - L55 _member_ `float RectLightBarnLength;` — Barn door length for rect light
  - L58 _member_ `float SpecularScale;` — Factor to applies on the specular.
  - L61 _member_ `float DiffuseScale;` — Factor to applies on the diffuse.

#### Namespaces (1)

- L8-94 _namespace_ **`UE::HLSL`** `namespace UE::HLSL` _[#if defined(__cplusplus)]_

#### typedef / using (1)

- L95 _typedef_ `using FLightSceneData = UE::HLSL::FLightSceneData;` _[#if defined(__cplusplus)]_

### `Shaders/Shared/LightViewData.h` (Shared)

- lines: 40; parse: all-branches
- includes: L6 `HLSLTypeAliases.h` [defined(__cplusplus)]
- L3 #pragma `once`

#### Structs / classes (1)

- L15-34 _struct_ **`UE::HLSL::FLightViewData`** `struct FLightViewData` — Light view-dependent data
  - L18 _member_ `float3 TranslatedWorldPosition;` — TODO: pack members to reduce memory overhead/bandwidth
  - L19 _member_ `float3 Color;`
  - L20 _member_ `float VolumetricScatteringIntensity;`
  - L21 _member_ `uint VirtualShadowMapId;`
  - L23 _member_ `uint LightSceneInfoExtraDataPacked;`
  - L26 _member_ `float2 RectLightAtlasUVOffset;` — Rect. light atlas transformation
  - L27 _member_ `float2 RectLightAtlasUVScale;`
  - L28 _member_ `float RectLightAtlasMaxLevel;`
  - L33 _member_ `float IESAtlasIndex;` — could pack IESAtlasIndex with other data in the future since it doesn't require 32 bits FLocalLightData packs it in 16 bits (see UnpackLigthIESAtlasIndex(...)) could probably go down to 8 bits (with some logic in GIESTextureManager to warn about overflow)

#### Namespaces (1)

- L8-37 _namespace_ **`UE::HLSL`** `namespace UE::HLSL` _[#if defined(__cplusplus)]_

#### typedef / using (1)

- L38 _typedef_ `using FLightViewData = UE::HLSL::FLightViewData;` _[#if defined(__cplusplus)]_

### `Shaders/Shared/LumenDefinitions.h` (Shared)

- lines: 8; parse: all-branches

#### Macros (#define, 3)

- L5 `#define LUMEN_MAX_VIEWS 2`
- L6 `#define LUMEN_MAX_CAMERA_PLANES 5`
- L7 `#define LUMEN_MATERIAL_SHADER_INDEX_MASK 0x007FFFFF`
- L3 #pragma `once`

### `Shaders/Shared/MaterialCacheDefinitions.h` (Shared)

- lines: 56; parse: all-branches
- includes: L6 `HLSLTypeAliases.h` [defined(__cplusplus)]

#### Macros (#define, 1)

- L48 `#define EMaterialCacheFlag uint` _[#if !(defined(__cplusplus))]_
- L3 #pragma `once`

#### Structs / classes (3)

- L12-15 _struct_ **`UE::HLSL::FMaterialCacheTagEntry`** `struct FMaterialCacheTagEntry`
  - L14 _member_ `uint2 PackedUniform;`
- L17-28 _struct_ **`UE::HLSL::FMaterialCacheBinData`** `struct FMaterialCacheBinData`
  - L20 _member_ `uint3 ABufferPhysicalPosition;` — DW0
  - L21 _member_ `uint PrimitiveData;`
  - L23 _member_ `float4 UVMinAndThreadAdvance;` — DW4
  - L25 _member_ `float4 UVMinAndInvSize;` — DW8
  - L27 _member_ `uint4 Pad16;` — DW12
- L30-38 _struct_ **`UE::HLSL::FMaterialCachePageWriteData`** `struct FMaterialCachePageWriteData`
  - L33 _member_ `uint3 ABufferPhysicalPosition;` — DW0
  - L34 _member_ `uint Pad;`
  - L36 _member_ `uint2 VTPhysicalPosition;` — DW4
  - L37 _member_ `uint Pad2;`

#### Enums (1)

- L41-45 _enum_ **`UE::HLSL::EMaterialCacheFlag`** `enum EMaterialCacheFlag` _[#if defined(__cplusplus)]_
  - L43 _enumerator_ `MatCache_None = 0u` _[#if defined(__cplusplus)]_
  - L44 _enumerator_ `MatCache_DefaultBottomLayer = 1u << 0u` _[#if defined(__cplusplus)]_

#### Namespaces (1)

- L8-54 _namespace_ **`UE::HLSL`** `namespace UE::HLSL` _[#if defined(__cplusplus)]_

#### static variables (2)

- L49 _static_var_ `static uint MatCache_None = 0u;` (scope `UE::HLSL`) _[#if !(defined(__cplusplus))]_
- L50 _static_var_ `static uint MatCache_DefaultBottomLayer = 1u << 0u;` (scope `UE::HLSL`) _[#if !(defined(__cplusplus))]_

### `Shaders/Shared/MegaLightsDefinitions.h` (Shared)

- lines: 56; parse: all-branches

#### Macros (#define, 38)

- L10 `#define TILE_MODE_SIMPLE_SHADING 0`
- L11 `#define TILE_MODE_COMPLEX_SHADING 1`
- L12 `#define TILE_MODE_SIMPLE_SHADING_RECT 2`
- L13 `#define TILE_MODE_COMPLEX_SHADING_RECT 3`
- L14 `#define TILE_MODE_SIMPLE_SHADING_RECT_TEXTURED 4`
- L15 `#define TILE_MODE_COMPLEX_SHADING_RECT_TEXTURED 5`
- L16 `#define TILE_MODE_EMPTY 6`
- L18 `#define TILE_MODE_SINGLE_SHADING 7`
- L19 `#define TILE_MODE_SINGLE_SHADING_RECT 8`
- L20 `#define TILE_MODE_SINGLE_SHADING_RECT_TEXTURED 9`
- L22 `#define TILE_MODE_COMPLEX_SPECIAL_SHADING 10`
- L23 `#define TILE_MODE_COMPLEX_SPECIAL_SHADING_RECT 11`
- L24 `#define TILE_MODE_COMPLEX_SPECIAL_SHADING_RECT_TEXTURED 12`
- L26 `#define TILE_MODE_MAX_LEGACY 7`
- L27 `#define TILE_MODE_MAX_SUBSTRATE_BLENDABLE 10`
- L28 `#define TILE_MODE_MAX_SUBSTRATE_ADAPTIVE 13`
- L31 `#define TILE_SIZE 8`
- L32 `#define VISIBLE_LIGHT_HASH_TILE_SIZE 8`
- L35 `#define MAX_LOCAL_LIGHT_NUM 32768`
- L36 `#define MAX_LOCAL_LIGHT_INDEX (MAX_LOCAL_LIGHT_NUM - 1)`
- L39 `#define MEGA_LIGHTS_VISUALIZE_OVERVIEW 1`
- L40 `#define MEGA_LIGHTS_VISUALIZE_SHADOW_CASTERS 2`
- L41 `#define MEGA_LIGHTS_VISUALIZE_SHADOW_CASTER_QUALITY 3`
- L42 `#define MEGA_LIGHTS_VISUALIZE_DENOISER_OVERVIEW 4`
- L43 `#define MEGA_LIGHTS_VISUALIZE_DENOISER_OVERVIEW2 5`
- L44 `#define MEGA_LIGHTS_VISUALIZE_SHADING_CONFIDENCE 6`
- L45 `#define MEGA_LIGHTS_VISUALIZE_NUM_FRAMES_ACCUMULATED 7`
- L46 `#define MEGA_LIGHTS_VISUALIZE_UPSAMPLE_MASK 8`
- L47 `#define MEGA_LIGHTS_VISUALIZE_DIFFUSE_DEMODULATE 9`
- L48 `#define MEGA_LIGHTS_VISUALIZE_SPECULAR_DEMODULATE 10`
- L49 `#define MEGA_LIGHTS_VISUALIZE_DIFFUSE_STD_DEV 11`
- L50 `#define MEGA_LIGHTS_VISUALIZE_SPECULAR_STD_DEV 12`
- L51 `#define MEGA_LIGHTS_VISUALIZE_DIFFUSE_HISTORY_SPATIAL_STD_DEV 13`
- L52 `#define MEGA_LIGHTS_VISUALIZE_SPECULAR_HISTORY_SPATIAL_STD_DEV 14`
- L53 `#define MEGA_LIGHTS_VISUALIZE_DIFFUSE_HISTORY_CLAMP 15`
- L54 `#define MEGA_LIGHTS_VISUALIZE_SPECULAR_HISTORY_CLAMP 16`
- L55 `#define MEGA_LIGHTS_VISUALIZE_MIN MEGA_LIGHTS_VISUALIZE_OVERVIEW`
- L56 `#define MEGA_LIGHTS_VISUALIZE_MAX MEGA_LIGHTS_VISUALIZE_SPECULAR_HISTORY_CLAMP`
- L3 #pragma `once`

### `Shaders/Shared/NaniteDefinitions.h` (Shared)

- lines: 705; parse: all-branches

#### Macros (#define, 297)

- L5 `#define NANITE_SUBPIXEL_BITS 8`
- L6 `#define NANITE_SUBPIXEL_SAMPLES (1 << NANITE_SUBPIXEL_BITS)`
- L7 `#define NANITE_SUBPIXEL_MASK (NANITE_SUBPIXEL_SAMPLES - 1)`
- L8 `#define NANITE_SUBPIXEL_DILATE 0`
- L10 `#define NANITE_LATE_VSM_PAGE_TRANSLATION 1`
- L11 `#define NANITE_VSM_PAGE_TABLE_CACHE_DIM 8`
- L13 `#define NANITE_USE_UNCOMPRESSED_VERTEX_DATA 0`
- L14 `#define NANITE_USE_ANALYTIC_SGGX 0`
- L16 `#define NANITE_NUM_DEPTH_BUCKETS_PER_BLOCK_BITS 8`
- L17 `#define NANITE_NUM_DEPTH_BUCKETS_PER_BLOCK (1 << NANITE_NUM_DEPTH_BUCKETS_PER_BLOCK_BITS)`
- L19 `#define NANITE_CONSTRAINED_CLUSTER_CACHE_SIZE 32`
- L21 `#define NANITE_MAX_CLUSTER_TRIANGLES_BITS 7`
- L22 `#define NANITE_MAX_CLUSTER_TRIANGLES (1 << NANITE_MAX_CLUSTER_TRIANGLES_BITS)`
- L23 `#define NANITE_MAX_CLUSTER_TRIANGLES_MASK ((1 << NANITE_MAX_CLUSTER_TRIANGLES_BITS)) - 1`
- L24 `#define NANITE_MAX_CLUSTER_VERTICES_BITS 8`
- L25 `#define NANITE_MAX_CLUSTER_VERTICES (1 << NANITE_MAX_CLUSTER_VERTICES_BITS)`
- L26 `#define NANITE_MAX_CLUSTER_VERTICES_MASK ((1 << NANITE_MAX_CLUSTER_VERTICES_BITS) - 1)`
- L28 `#define NANITE_MAX_CLUSTER_INDICES (NANITE_MAX_CLUSTER_TRIANGLES * 3)`
- L29 `#define NANITE_MAX_UVS 4`
- L31 `#define NANITE_MAX_CLUSTER_MATERIALS 64`
- L33 `#define NANITE_MAX_CLUSTER_BONE_INFLUENCES 16`
- L34 `#define NANITE_MAX_HIERARCHY_BONE_INFLUENCES 16`
- L35 `#define NANITE_HIERARCHY_NUM_BONES_BITS 5`
- L36 `#define NANITE_HIERARCHY_BONE_INDICES_OFFSET_BITS 27`
- L37 `#define NANITE_MAX_VOXEL_ANIMATION_BONE_INFLUENCES 1`
- L39 `#define NANITE_USE_STRIP_INDICES 1`
- L42 `#define NANITE_SANITY_CHECK_STREAMING_REQUESTS 0`
- L44 `#define NANITE_FIXUP_MAGIC 0x464Eu`
- L46 `#define NANITE_CLUSTER_MIN_EXPECTED_GPU_SIZE_BITS 9`
- L49 `#define NANITE_STREAMING_REQUEST_MAGIC_BITS 6`
- L50 `#define NANITE_STREAMING_REQUEST_MAGIC_MASK ((1 << NANITE_STREAMING_REQUEST_MAGIC_BITS) - 1)`
- L52 `#define NANITE_ROOT_PAGE_GPU_SIZE_BITS 15`
- L53 `#define NANITE_ROOT_PAGE_GPU_SIZE (1u << NANITE_ROOT_PAGE_GPU_SIZE_BITS)`
- L54 `#define NANITE_ROOT_PAGE_MAX_CLUSTERS_BITS (NANITE_ROOT_PAGE_GPU_SIZE_BITS - NANITE_CLUSTER_MIN_EXPECTED_GPU_SIZE_BITS)`
- L55 `#define NANITE_ROOT_PAGE_MAX_CLUSTERS (1u << NANITE_ROOT_PAGE_MAX_CLUSTERS_BITS)`
- L57 `#define NANITE_STREAMING_PAGE_GPU_SIZE_BITS 17`
- L58 `#define NANITE_STREAMING_PAGE_GPU_SIZE (1u << NANITE_STREAMING_PAGE_GPU_SIZE_BITS)`
- L59 `#define NANITE_STREAMING_PAGE_MAX_CLUSTERS_BITS (NANITE_STREAMING_PAGE_GPU_SIZE_BITS - NANITE_CLUSTER_MIN_EXPECTED_GPU_SIZE_BITS)`
- L60 `#define NANITE_STREAMING_PAGE_MAX_CLUSTERS (1u << NANITE_STREAMING_PAGE_MAX_CLUSTERS_BITS)`
- L61 `#define NANITE_ESTIMATED_MAX_PAGE_DISK_SIZE uint32(NANITE_STREAMING_PAGE_GPU_SIZE * 1.5)`
- L63 `#define NANITE_MAX_CLUSTERS_PER_PAGE_BITS (NANITE_STREAMING_PAGE_MAX_CLUSTERS_BITS > NANITE_ROOT_PAGE_MAX_CLUSTERS_BITS ? NANITE_STREAMING_PAGE_MAX_CLUSTERS_BITS : NANITE_ROOT_PAGE_MAX_CLUSTERS_BITS)`
- L64 `#define NANITE_MAX_CLUSTERS_PER_PAGE_MASK ((1 << NANITE_MAX_CLUSTERS_PER_PAGE_BITS) - 1)`
- L65 `#define NANITE_MAX_CLUSTERS_PER_PAGE ( 1 << NANITE_MAX_CLUSTERS_PER_PAGE_BITS)`
- L66 `#define NANITE_MAX_CLUSTERS_PER_GROUP_BITS 9`
- L67 `#define NANITE_MAX_CLUSTERS_PER_GROUP_MASK ((1 << NANITE_MAX_CLUSTERS_PER_GROUP_BITS) - 1)`
- L68 `#define NANITE_MAX_CLUSTERS_PER_GROUP ((1 << NANITE_MAX_CLUSTERS_PER_GROUP_BITS) - 1)`
- L69 `#define NANITE_MAX_CLUSTERS_PER_GROUP_TARGET 128`
- L70 `#define NANITE_MAX_CLUSTER_HIERARCHY_DEPTH 32`
- L72 `#define NANITE_POOL_CLUSTER_REF_BITS (32 - NANITE_CLUSTER_MIN_EXPECTED_GPU_SIZE_BITS)`
- L74 `#define NANITE_MAX_HIERARCHY_CHILDREN_BITS 6`
- L75 `#define NANITE_MAX_HIERARCHY_CHILDREN (1 << NANITE_MAX_HIERARCHY_CHILDREN_BITS)`
- L76 `#define NANITE_MAX_VIEWS_PER_CULL_RASTERIZE_PASS_BITS 12`
- L77 `#define NANITE_MAX_VIEWS_PER_CULL_RASTERIZE_PASS_MASK ((1 << NANITE_MAX_VIEWS_PER_CULL_RASTERIZE_PASS_BITS) - 1)`
- L78 `#define NANITE_MAX_VIEWS_PER_CULL_RASTERIZE_PASS (1 << NANITE_MAX_VIEWS_PER_CULL_RASTERIZE_PASS_BITS)`
- L79 `#define NANITE_MAX_GPU_PAGES_BITS 17`
- L80 `#define NANITE_MAX_GPU_PAGES_MASK ((1 << NANITE_MAX_GPU_PAGES_BITS) - 1)`
- L81 `#define NANITE_MAX_GPU_PAGES ( 1 << NANITE_MAX_GPU_PAGES_BITS)`
- L82 `#define NANITE_MAX_INSTANCES_BITS 24`
- L83 `#define NANITE_MAX_INSTANCES (1 << NANITE_MAX_INSTANCES_BITS)`
- L85 `#define NANITE_MAX_NODES_PER_PRIMITIVE_BITS 16`
- L86 `#define NANITE_MAX_RESOURCE_PAGES_BITS 16`
- L87 `#define NANITE_MAX_RESOURCE_PAGES_MASK ((1 << NANITE_MAX_RESOURCE_PAGES_BITS) - 1)`
- L88 `#define NANITE_MAX_RESOURCE_PAGES (1 << NANITE_MAX_RESOURCE_PAGES_BITS)`
- L89 `#define NANITE_MAX_GROUP_PARTS_BITS 5`
- L90 `#define NANITE_MAX_GROUP_PARTS_MASK ((1 << NANITE_MAX_GROUP_PARTS_BITS) - 1)`
- L91 `#define NANITE_MAX_GROUP_PARTS (1 << NANITE_MAX_GROUP_PARTS_BITS)`
- L93 `#define NANITE_PAGE_RANGE_KEY_COUNT_BITS (NANITE_MAX_GROUP_PARTS_BITS)`
- L94 `#define NANITE_PAGE_RANGE_KEY_COUNT_MASK ((1u << NANITE_PAGE_RANGE_KEY_COUNT_BITS) - 1u)`
- L95 `#define NANITE_PAGE_RANGE_KEY_MAX_COUNT (NANITE_PAGE_RANGE_KEY_COUNT_MASK)`
- L96 `#define NANITE_PAGE_RANGE_KEY_INDEX_BITS 25u`
- L97 `#define NANITE_PAGE_RANGE_KEY_INDEX_MASK ((1u << NANITE_PAGE_RANGE_KEY_INDEX_BITS) - 1u)`
- L98 `#define NANITE_PAGE_RANGE_KEY_MAX_INDEX (NANITE_PAGE_RANGE_KEY_INDEX_MASK - 1u)`
- L99 `#define NANITE_PAGE_RANGE_KEY_FLAG_MULTI_RANGE (1u << 31u)`
- L100 `#define NANITE_PAGE_RANGE_KEY_FLAG_HAS_STREAMING_PAGES (1u << 30u)`
- L101 `#define NANITE_PAGE_RANGE_KEY_EMPTY_RANGE (0u)`
- L103 `#define NANITE_MAX_BVH_NODE_FANOUT_BITS 2`
- L104 `#define NANITE_MAX_BVH_NODE_FANOUT_MASK ((1 << NANITE_MAX_BVH_NODE_FANOUT_BITS)-1)`
- L105 `#define NANITE_MAX_BVH_NODE_FANOUT (1 << NANITE_MAX_BVH_NODE_FANOUT_BITS)`
- L106 `#define NANITE_BVH_NODE_ENABLE_MASK ((1 << NANITE_MAX_BVH_NODE_FANOUT)-1)`
- L108 `#define NANITE_PERSISTENT_CLUSTER_CULLING_GROUP_SIZE 64`
- L109 `#define NANITE_MAX_BVH_NODES_PER_GROUP (NANITE_PERSISTENT_CLUSTER_CULLING_GROUP_SIZE / NANITE_MAX_BVH_NODE_FANOUT)`
- L111 `#define NANITE_HIERARCHY_NODE_SLICE_SIZE_DWORDS 60`
- L113 `#define NANITE_ASSEMBLY_TRANSFORM_SIZE_DWORDS 12`
- L115 `#define NANITE_HIERARCHY_ASSEMBLY_TRANSFORM_INDEX_BITS 16`
- L116 `#define NANITE_HIERARCHY_MAX_ASSEMBLY_TRANSFORMS ((1 << NANITE_HIERARCHY_ASSEMBLY_TRANSFORM_INDEX_BITS) - 1)`
- L118 `#define NANITE_ASSEMBLY_TRANSFORM_INDEX_BITS 24`
- L119 `#define NANITE_MAX_ASSEMBLY_TRANSFORMS ((1 << NANITE_ASSEMBLY_TRANSFORM_INDEX_BITS) - 1)`
- L121 `#define NANITE_NUM_STREAMING_PRIORITY_CATEGORY_BITS 2`
- L122 `#define NANITE_STREAMING_PRIORITY_CATEGORY_MASK ((1 << NANITE_NUM_STREAMING_PRIORITY_CATEGORY_BITS) - 1)`
- L123 `#define NANITE_MAX_PRIORITY_BEFORE_PARENTS 0xFFFFFFE0u`
- L125 `#define NANITE_TESSELLATION_TABLE_SIZE 14`
- L126 `#define NANITE_TESSELLATION_TABLE_PO2_SIZE 16`
- L127 `#define NANITE_TESSELLATION_TABLE_IMMEDIATE_SIZE 8`
- L128 `#define NANITE_TESSELLATION_MAX_PATCH_SPLIT_LEVELS 6`
- L130 `#define NANITE_VIEW_FLAG_HZBTEST 0x1`
- L131 `#define NANITE_VIEW_FLAG_NEAR_CLIP 0x2`
- L132 `#define NANITE_VIEW_FLAG_DISTANCE_CULL 0x4`
- L133 `#define NANITE_VIEW_FLAG_UNCACHED 0x8`
- L134 `#define NANITE_VIEW_FLAG_REVERSE_CULLING 0x10`
- L135 `#define NANITE_VIEW_MIN_SCREEN_RADIUS_CULL 0x20`
- L136 `#define NANITE_VIEW_FLAG_USE_RECEIVER_MASK 0x40`
- L137 `#define NANITE_VIEW_FLAG_PREFILTERED_DISTANT_DEPTH_CULL 0x80`
- L138 `#define NANITE_VIEW_FLAG_FORCE_DISPLACEMENT_FALLBACK 0x100`
- L140 `#define NANITE_CLUSTER_FLAG_ROOT_LEAF 0x1`
- L141 `#define NANITE_CLUSTER_FLAG_STREAMING_LEAF 0x2`
- L142 `#define NANITE_CLUSTER_FLAG_FULL_LEAF 0x4`
- L143 `#define NANITE_CLUSTER_FLAG_ROOT_GROUP 0x8`
- L145 `#define NANITE_MAX_TRANSCODE_GROUPS_PER_PAGE 128`
- L147 `#define NANITE_NUM_PACKED_CLUSTER_FLOAT4S 8`
- L148 `#define NANITE_GPU_PAGE_HEADER_SIZE 16`
- L150 `#define NANITE_MAX_COORDINATE_VALUE 1e12f`
- L153 `#define NANITE_UV_FLOAT_NUM_EXPONENT_BITS 5`
- L154 `#define NANITE_UV_FLOAT_MAX_MANTISSA_BITS 14`
- L155 `#define NANITE_UV_FLOAT_NUM_MANTISSA_BITS 14`
- L157 `#define NANITE_UV_FLOAT_MAX_BITS (1 + NANITE_UV_FLOAT_NUM_EXPONENT_BITS + NANITE_UV_FLOAT_MAX_MANTISSA_BITS)`
- L159 `#define NANITE_MIN_POSITION_PRECISION -20`
- L160 `#define NANITE_MAX_POSITION_PRECISION 43`
- L162 `#define NANITE_MAX_POSITION_QUANTIZATION_BITS 21`
- L163 `#define NANITE_MAX_POSITION_QUANTIZATION_BYTES ((NANITE_MAX_POSITION_QUANTIZATION_BITS + 7) / 8)`
- L165 `#define NANITE_MAX_NORMAL_QUANTIZATION_BITS 15`
- L166 `#define NANITE_MAX_NORMAL_QUANTIZATION_BYTES ((NANITE_MAX_NORMAL_QUANTIZATION_BITS + 7) / 8)`
- L168 `#define NANITE_MAX_TANGENT_QUANTIZATION_BITS 12`
- L169 `#define NANITE_MAX_TANGENT_AND_SIGN_QUANTIZATION_BYTES ((NANITE_MAX_TANGENT_QUANTIZATION_BITS + 7 + 1) / 8)`
- L171 `#define NANITE_MAX_TEXCOORD_COMPONENT_BITS NANITE_UV_FLOAT_MAX_BITS`
- L172 `#define NANITE_MAX_TEXCOORD_COMPONENT_BYTES ((NANITE_MAX_TEXCOORD_COMPONENT_BITS + 7) / 8)`
- L174 `#define NANITE_MAX_CURVE_RADIUS_QUANTIZATION_BITS 8`
- L175 `#define NANITE_MAX_CURVE_RADIUS_QUANTIZATION_BYTES ((NANITE_MAX_CURVE_RADIUS_QUANTIZATION_BITS + 7) / 8)`
- L177 `#define NANITE_MAX_COLOR_QUANTIZATION_BITS 8`
- L178 `#define NANITE_MAX_COLOR_QUANTIZATION_BYTES ((NANITE_MAX_COLOR_QUANTIZATION_BITS + 7) / 8)`
- L180 `#define NANITE_MAX_BONE_INDEX_BITS 16`
- L181 `#define NANITE_MAX_BLEND_WEIGHT_BITS 16`
- L183 `#define NANITE_RAY_TRACING_NODE_DATA_SIZE_IN_BYTES 80`
- L185 `#define NANITE_NUM_CULLING_FLAG_BITS 5`
- L186 `#define NANITE_CULLING_FLAG_TEST_LOD (1u << 0u)`
- L187 `#define NANITE_CULLING_FLAG_USE_HW (1u << 1u)`
- L188 `#define NANITE_CULLING_FLAG_CACHE_AS_STATIC (1u << 2u)`
- L189 `#define NANITE_CULLING_FLAG_ENABLE_WPO (1u << 3u)`
- L190 `#define NANITE_CULLING_FLAG_FALLBACK_RASTER (1u << 4u)`
- L192 `#define NANITE_CULLING_TYPE_NODES 0`
- L193 `#define NANITE_CULLING_TYPE_CLUSTERS 1`
- L194 `#define NANITE_CULLING_TYPE_PERSISTENT_NODES_AND_CLUSTERS 2`
- L196 `#define NANITE_VERTEX_COLOR_MODE_CONSTANT 0`
- L197 `#define NANITE_VERTEX_COLOR_MODE_VARIABLE 1`
- L199 `#define NANITE_PAGE_FLAG_RELATIVE_ENCODING 0x1`
- L201 `#define NANITE_INVALID_PERSISTENT_HASH 0`
- L203 `#define NANITE_RESOURCE_FLAG_STREAMING_DATA_IN_DDC 0x1`
- L205 `#define NANITE_RENDER_FLAG_DISABLE_PROGRAMMABLE 0x1`
- L206 `#define NANITE_RENDER_FLAG_FORCE_HW_RASTER 0x2`
- L207 `#define NANITE_RENDER_FLAG_PRIMITIVE_SHADER 0x4`
- L208 `#define NANITE_RENDER_FLAG_MESH_SHADER 0x8`
- L209 `#define NANITE_RENDER_FLAG_OUTPUT_STREAMING_REQUESTS 0x10`
- L210 `#define NANITE_RENDER_FLAG_IS_SHADOW_PASS 0x20`
- L211 `#define NANITE_RENDER_FLAG_IS_SCENE_CAPTURE 0x40`
- L212 `#define NANITE_RENDER_FLAG_IS_REFLECTION_CAPTURE 0x80`
- L213 `#define NANITE_RENDER_FLAG_IS_GAME_VIEW 0x100`
- L214 `#define NANITE_RENDER_FLAG_GAME_SHOW_FLAG_ENABLED 0x200`
- L215 `#define NANITE_RENDER_FLAG_EDITOR_SHOW_FLAG_ENABLED 0x400`
- L216 `#define NANITE_RENDER_FLAG_IS_LUMEN_CAPTURE 0x800`
- L217 `#define NANITE_RENDER_FLAG_ADD_CLUSTER_OFFSET 0x1000`
- L218 `#define NANITE_RENDER_FLAG_HAS_PREV_DRAW_DATA 0x2000`
- L219 `#define NANITE_RENDER_FLAG_INVALIDATE_VSM_ON_LOD_DELTA 0x4000`
- L220 `#define NANITE_RENDER_FLAG_WRITE_STATS 0x8000`
- L221 `#define NANITE_RENDER_FLAG_IS_MATERIAL_CACHE 0x10000`
- L222 `#define NANITE_RENDER_FLAG_DRAW_ONLY_RAYTRACING_FAR_FIELD 0x20000`
- L224 `#define NANITE_MATERIAL_FLAG_WORLD_POSITION_OFFSET 0x1`
- L225 `#define NANITE_MATERIAL_FLAG_PIXEL_DEPTH_OFFSET 0x2`
- L226 `#define NANITE_MATERIAL_FLAG_PIXEL_DISCARD 0x4`
- L227 `#define NANITE_MATERIAL_FLAG_DISPLACEMENT 0x8`
- L228 `#define NANITE_MATERIAL_FLAG_SPLINE_MESH 0x10`
- L229 `#define NANITE_MATERIAL_FLAG_SKINNED_MESH 0x20`
- L230 `#define NANITE_MATERIAL_FLAG_TWO_SIDED 0x40`
- L231 `#define NANITE_MATERIAL_FLAG_ALLOW_VRS 0x80`
- L232 `#define NANITE_MATERIAL_FLAG_NO_DERIVATIVE_OPS 0x100`
- L233 `#define NANITE_MATERIAL_FLAG_CAST_SHADOW 0x200`
- L234 `#define NANITE_MATERIAL_FLAG_VERTEX_UVS 0x400`
- L235 `#define NANITE_MATERIAL_FLAG_VOXEL 0x800`
- L236 `#define NANITE_MATERIAL_FLAG_FIRST_PERSON_LERP 0x1000`
- L237 `#define NANITE_MATERIAL_FLAG_TRANSLUCENT 0x2000`
- L238 `#define NANITE_MATERIAL_FLAG_USED 0x4000`
- L239 `#define NANITE_MATERIAL_FLAG_CURVE 0x8000`
- L241 `#define NANITE_TRANSCODE_PASS_INDEPENDENT 0`
- L242 `#define NANITE_TRANSCODE_PASS_PARENT_DEPENDENT 1`
- L244 `#define NANITE_MATERIAL_VERTEX_PROGRAMMABLE_FLAGS (NANITE_MATERIAL_FLAG_WORLD_POSITION_OFFSET \| NANITE_MATERIAL_FLAG_DISPLACEMENT \| NANITE_MATERIAL_FLAG_VERTEX_UVS \| NANITE_MATERIAL_FLAG_FIRST_PERSON_LERP)`
- L245 `#define NANITE_MATERIAL_PIXEL_PROGRAMMABLE_FLAGS (NANITE_MATERIAL_FLAG_PIXEL_DEPTH_OFFSET \| NANITE_MATERIAL_FLAG_PIXEL_DISCARD)`
- L248 `#define NANITE_FIXED_FUNCTION_BIN 0x0`
- L249 `#define NANITE_FIXED_FUNCTION_BIN_TWOSIDED 0x1`
- L250 `#define NANITE_FIXED_FUNCTION_BIN_SPLINE 0x2`
- L251 `#define NANITE_FIXED_FUNCTION_BIN_SKINNED 0x4`
- L252 `#define NANITE_FIXED_FUNCTION_BIN_CAST_SHADOW 0x8`
- L253 `#define NANITE_FIXED_FUNCTION_BIN_VOXEL 0x10`
- L254 `#define NANITE_FIXED_FUNCTION_BIN_CURVE 0x20`
- L258 `#define NANITE_DEBUG_FLAG_DISABLE_CULL_HZB 0x1`
- L259 `#define NANITE_DEBUG_FLAG_DISABLE_CULL_FRUSTUM 0x2`
- L260 `#define NANITE_DEBUG_FLAG_DISABLE_CULL_DRAW_DISTANCE 0x4`
- L261 `#define NANITE_DEBUG_FLAG_DISABLE_CULL_GLOBAL_CLIP_PLANE 0x8`
- L262 `#define NANITE_DEBUG_FLAG_DISABLE_CULL_MIN_LOD 0x10`
- L263 `#define NANITE_DEBUG_FLAG_DISABLE_SKINNED_NODE_BOUNDS 0x20`
- L264 `#define NANITE_DEBUG_FLAG_DISABLE_WPO_DISABLE_DISTANCE 0x40`
- L265 `#define NANITE_DEBUG_FLAG_DISABLE_PIXEL_PROGRAMMABLE_DISTANCE 0x80`
- L266 `#define NANITE_DEBUG_FLAG_DISABLE_DISPLACEMENT_FADE_OUT_DISTANCE 0x100`
- L267 `#define NANITE_DEBUG_FLAG_DRAW_ONLY_ROOT_DATA 0x200`
- L268 `#define NANITE_DEBUG_FLAG_HIDE_ASSEMBLY_PARTS 0x400`
- L269 `#define NANITE_DEBUG_FLAG_WRITE_ASSEMBLY_META 0x800`
- L271 `#define NANITE_INVALID_RASTER_BIN 0xFFFFu`
- L272 `#define NANITE_INVALID_RASTER_GROUP 0xFFFFu`
- L273 `#define NANITE_INVALID_SHADING_GROUP 0xFFFFu`
- L275 `#define NANITE_RASTER_BIN_INIT 0`
- L276 `#define NANITE_RASTER_BIN_COUNT 1`
- L277 `#define NANITE_RASTER_BIN_RESERVE 2`
- L278 `#define NANITE_RASTER_BIN_SCATTER 3`
- L279 `#define NANITE_RASTER_BIN_DEPTHBLOCK 4`
- L280 `#define NANITE_RASTER_BIN_FINALIZE 5`
- L282 `#define NANITE_SHADING_BIN_COUNT 0`
- L283 `#define NANITE_SHADING_BIN_RESERVE 1`
- L284 `#define NANITE_SHADING_BIN_SCATTER 2`
- L285 `#define NANITE_SHADING_BIN_VALIDATE 3`
- L286 `#define NANITE_SHADING_BIN_CMASK_CLEAR 4`
- L287 `#define NANITE_SHADING_BIN_GROUP_COUNT 5`
- L288 `#define NANITE_SHADING_BIN_GROUP_RESERVE 6`
- L292 `#define NANITE_RASTERIZER_ARG_COUNT 8u`
- L293 `#define NANITE_NODE_CULLING_ARG_COUNT 8u`
- L294 `#define NANITE_PATCH_SPLIT_ARG_COUNT 8u`
- L298 `#define NANITE_VISUALIZE_OVERVIEW 0u`
- L299 `#define NANITE_VISUALIZE_TRIANGLES 1u`
- L300 `#define NANITE_VISUALIZE_PATCHES 2u`
- L301 `#define NANITE_VISUALIZE_CLUSTERS 3u`
- L302 `#define NANITE_VISUALIZE_PRIMITIVES 4u`
- L303 `#define NANITE_VISUALIZE_INSTANCES 5u`
- L304 `#define NANITE_VISUALIZE_GROUPS 6u`
- L305 `#define NANITE_VISUALIZE_PAGES 7u`
- L306 `#define NANITE_VISUALIZE_OVERDRAW 8u`
- L307 `#define NANITE_VISUALIZE_RASTER_MODE 9u`
- L308 `#define NANITE_VISUALIZE_RASTER_BINS 10u`
- L309 `#define NANITE_VISUALIZE_SHADING_BINS 11u`
- L310 `#define NANITE_VISUALIZE_SCENE_Z_MIN 12u`
- L311 `#define NANITE_VISUALIZE_SCENE_Z_MAX 13u`
- L312 `#define NANITE_VISUALIZE_SCENE_Z_DELTA 14u`
- L313 `#define NANITE_VISUALIZE_SCENE_Z_DECODED 15u`
- L314 `#define NANITE_VISUALIZE_MATERIAL_COUNT 16u`
- L315 `#define NANITE_VISUALIZE_MATERIAL_MODE 17u`
- L316 `#define NANITE_VISUALIZE_MATERIAL_INDEX 18u`
- L317 `#define NANITE_VISUALIZE_HIT_PROXY_DEPTH 19u`
- L318 `#define NANITE_VISUALIZE_NANITE_MASK 20u`
- L319 `#define NANITE_VISUALIZE_LIGHTMAP_UVS 21u`
- L320 `#define NANITE_VISUALIZE_LIGHTMAP_UV_INDEX 22u`
- L321 `#define NANITE_VISUALIZE_LIGHTMAP_DATA_INDEX 23u`
- L322 `#define NANITE_VISUALIZE_HIERARCHY_OFFSET 24u`
- L323 `#define NANITE_VISUALIZE_POSITION_BITS 25u`
- L324 `#define NANITE_VISUALIZE_SHADOW_CASTERS 26u`
- L325 `#define NANITE_VISUALIZE_EVALUATE_WORLD_POSITION_OFFSET 27u`
- L326 `#define NANITE_VISUALIZE_PIXEL_PROGRAMMABLE_RASTER 28u`
- L327 `#define NANITE_VISUALIZE_PICKING 29u`
- L328 `#define NANITE_VISUALIZE_SHADING_WRITE_MASK 30u`
- L329 `#define NANITE_VISUALIZE_NO_DERIVATIVE_OPS 31u`
- L330 `#define NANITE_VISUALIZE_FAST_CLEAR_TILES 32u`
- L331 `#define NANITE_VISUALIZE_TESSELLATION 33u`
- L332 `#define NANITE_VISUALIZE_DISPLACEMENT_SCALE 34u`
- L333 `#define NANITE_VISUALIZE_VERTEX_COLOR 35u`
- L334 `#define NANITE_VISUALIZE_MESH_PAINT_TEXTURE 36u`
- L335 `#define NANITE_VISUALIZE_VOXELS 37u`
- L336 `#define NANITE_VISUALIZE_ASSEMBLIES 38u`
- L337 `#define NANITE_VISUALIZE_SKINNING 39u`
- L338 `#define NANITE_VISUALIZE_CURVES 40u`
- L340 `#define NANITE_VISUALIZE_FLAG_ENABLE_OUTLINE (1u << 0u)`
- L341 `#define NANITE_VISUALIZE_FLAG_ENABLE_DEBUG_SHADING (1u << 1u)`
- L343 `#define NANITE_PICKING_DOMAIN_TRIANGLE 0`
- L344 `#define NANITE_PICKING_DOMAIN_CLUSTER 1`
- L345 `#define NANITE_PICKING_DOMAIN_INSTANCE 2`
- L346 `#define NANITE_PICKING_DOMAIN_PRIMITIVE 3`
- L348 `#define NANITE_PIXEL_PROG_VIS_MODE_DEFAULT 0`
- L349 `#define NANITE_PIXEL_PROG_VIS_MODE_MASKED_ONLY 1`
- L350 `#define NANITE_PIXEL_PROG_VIS_MODE_PDO_ONLY 2`
- L352 `#define NANITE_MESH_PAINTING_SHOW_ALL 0`
- L353 `#define NANITE_MESH_PAINTING_SHOW_SELECTED 1`
- L355 `#define NANITE_MESH_PAINTING_CHANNELS_DEFAULT 0`
- L356 `#define NANITE_MESH_PAINTING_CHANNELS_RGB 1`
- L357 `#define NANITE_MESH_PAINTING_CHANNELS_A 2`
- L358 `#define NANITE_MESH_PAINTING_CHANNELS_R 3`
- L359 `#define NANITE_MESH_PAINTING_CHANNELS_G 4`
- L360 `#define NANITE_MESH_PAINTING_CHANNELS_B 5`
- L362 `#define NANITE_MESH_PAINTING_TEXTURE_DEFAULT 0`
- L363 `#define NANITE_MESH_PAINTING_TEXTURE_ASSET 1`
- L366 `#define UINT_TYPE unsigned int` _[#if defined(__cplusplus)]_
- L367 `#define INT_TYPE int` _[#if defined(__cplusplus)]_
- L368 `#define INLINE_ATTR inline` _[#if defined(__cplusplus)]_
- L370 `#define UINT_TYPE uint` _[#if !(defined(__cplusplus))]_
- L371 `#define INT_TYPE int` _[#if !(defined(__cplusplus))]_
- L372 `#define INLINE_ATTR ` _[#if !(defined(__cplusplus))]_
- L659 `#define NANITE_SHADING_BIN_META_ELEMENT_COUNT_OFFSET 0u`
- L660 `#define NANITE_SHADING_BIN_META_RANGE_START_OFFSET 4u`
- L661 `#define NANITE_SHADING_BIN_META_MATERIAL_FLAGS_OFFSET 8u`
- L662 `#define NANITE_SHADING_BIN_META_SHADING_GROUP_OFFSET 12u`
- L663 `#define NANITE_SHADING_BIN_META_MATERIAL_CB_INDEX_OFFSET 16u`
- L664 `#define NANITE_SHADING_BIN_META_FIRST_THREAD_GROUP 20u`
- L665 `#define NANITE_SHADING_BIN_META_QUAD_BINNING 24u`
- L668 `#define NANITE_SHADING_BIN_META_BYTES sizeof(FNaniteShadingBinMeta)` _[#if defined(__cplusplus)]_
- L670 `#define NANITE_SHADING_BIN_META_BYTES uint(sizeof(FNaniteShadingBinMeta))` _[#if !(defined(__cplusplus))]_
- L3 #pragma `once`; L702 #undef `INT_TYPE`; L703 #undef `UINT_TYPE`; L704 #undef `INLINE_ATTR`

#### Structs / classes (13)

- L375-395 _struct_ **`FNaniteMaterialFlags`** `struct FNaniteMaterialFlags`
  - L377 _member_ `bool bWorldPositionOffset;`
  - L378 _member_ `bool bPixelDepthOffset;`
  - L379 _member_ `bool bPixelDiscard;`
  - L380 _member_ `bool bDisplacement;`
  - L381 _member_ `bool bSplineMesh;`
  - L382 _member_ `bool bSkinnedMesh;`
  - L383 _member_ `bool bTwoSided;`
  - L384 _member_ `bool bAllowVRS;`
  - L385 _member_ `bool bNoDerivativeOps;`
  - L386 _member_ `bool bCastShadow;`
  - L387 _member_ `bool bVertexUVs;`
  - L388 _member_ `bool bVoxel;`
  - L389 _member_ `bool bCurve;`
  - L390 _member_ `bool bFirstPersonLerp;`
  - L391 _member_ `bool bTranslucent;`
  - L393 _member_ `bool bVertexProgrammable;`
  - L394 _member_ `bool bPixelProgrammable;`
- L517-557 _struct_ **`FNaniteStats`** `struct FNaniteStats`
  - L519 _member_ `UINT_TYPE NumTris;`
  - L520 _member_ `UINT_TYPE NumVerts;`
  - L521 _member_ `UINT_TYPE NumBricks;`
  - L522 _member_ `UINT_TYPE NumBrickThreads;`
  - L523 _member_ `UINT_TYPE NumViews;`
  - L524 _member_ `UINT_TYPE NumMainInstancesPreCull;`
  - L525 _member_ `UINT_TYPE NumMainInstancesPostCull;`
  - L526 _member_ `UINT_TYPE NumMainVisitedNodes;`
  - L527 _member_ `UINT_TYPE NumMainCandidateClusters;`
  - L528 _member_ `UINT_TYPE NumPostInstancesPreCull;`
  - L529 _member_ `UINT_TYPE NumPostInstancesPostCull;`
  - L530 _member_ `UINT_TYPE NumPostVisitedNodes;`
  - L531 _member_ `UINT_TYPE NumPostCandidateClusters;`
  - L532 _member_ `UINT_TYPE NumLargePageRectClusters;`
  - L533 _member_ `UINT_TYPE NumPrimaryViews;`
  - L534 _member_ `UINT_TYPE NumTotalViews;`
  - L535 _member_ `UINT_TYPE NumActiveRasterBins;`
  - L536 _member_ `UINT_TYPE NumActiveRasterGroups;`
  - L537 _member_ `UINT_TYPE NumEmptySWRasterGroups;`
  - L538 _member_ `UINT_TYPE NumEmptyHWRasterGroups;`
  - L539 _member_ `UINT_TYPE NumTotalShadingBins;`
  - L540 _member_ `UINT_TYPE NumTotalShadingGroups;`
  - L541 _member_ `UINT_TYPE NumEmptyShadingDispatches;`
  - L542 _member_ `UINT_TYPE NumNanitePixels;`
  - L543 _member_ `UINT_TYPE NumShadedQuads;`
  - L544 _member_ `UINT_TYPE NumShadedPixels;`
  - L545 _member_ `UINT_TYPE NumHelperLanes;`
  - L546 _member_ `UINT_TYPE NumMainPassIndirections;`
  - L547 _member_ `UINT_TYPE NumPostPassIndirections;`
  - L548 _member_ `UINT_TYPE NumMainHierarchyChunksPreCull;`
  - L549 _member_ `UINT_TYPE NumPostHierarchyChunksPreCull;`
  - L550 _member_ `UINT_TYPE NumDicedTrianglesClusters;`
  - L551 _member_ `UINT_TYPE NumDicedTrianglesPatches;`
  - L552 _member_ `UINT_TYPE NumImmediatePatches;`
  - L553 _member_ `UINT_TYPE NumCandidateSplitPatches;`
  - L554 _member_ `UINT_TYPE NumVisibleSplitPatches;`
  - L555 _member_ `UINT_TYPE NumAssemblyTransforms;`
  - L556 _member_ `UINT_TYPE Debug[4];`
- L559-585 _struct_ **`FNanitePickingFeedback`** `struct FNanitePickingFeedback`
  - L561 _member_ `UINT_TYPE PixelX;`
  - L562 _member_ `UINT_TYPE PixelY;`
  - L563 _member_ `UINT_TYPE PrimitiveId;`
  - L564 _member_ `UINT_TYPE InstanceId;`
  - L566 _member_ `UINT_TYPE PersistentIndex;`
  - L567 _member_ `UINT_TYPE ClusterIndex;`
  - L568 _member_ `UINT_TYPE GroupIndex;`
  - L569 _member_ `UINT_TYPE PageIndex;`
  - L571 _member_ `UINT_TYPE TriangleIndex;`
  - L572 _member_ `UINT_TYPE DepthInt;`
  - L573 _member_ `UINT_TYPE RasterMode;`
  - L574 _member_ `UINT_TYPE RasterBin;`
  - L576 _member_ `UINT_TYPE ShadingBin;`
  - L577 _member_ `UINT_TYPE MaterialIndex;`
  - L578 _member_ `UINT_TYPE MaterialCount;`
  - L579 _member_ `UINT_TYPE MaterialMode;`
  - L581 _member_ `UINT_TYPE HierarchyOffset;`
  - L582 _member_ `UINT_TYPE RuntimeResourceID;`
  - L583 _member_ `UINT_TYPE AssemblyTransformOffset;`
  - L584 _member_ `UINT_TYPE AssemblyTransformIndex;`
- L587-593 _struct_ **`FNaniteMaterialDisplacementParams`** `struct FNaniteMaterialDisplacementParams`
  - L589 _member_ `float Center;`
  - L590 _member_ `float Magnitude;`
  - L591 _member_ `float FadeSizeStart;`
  - L592 _member_ `float FadeSizeStop;`
- L595-608 _struct_ **`FNaniteRasterBinMeta`** `struct FNaniteRasterBinMeta`
  - L597 _member_ `UINT_TYPE GroupIndex;`
  - L598 _member_ `UINT_TYPE MaterialCBIndexVS;`
  - L599 _member_ `UINT_TYPE MaterialCBIndexPS;`
  - L600 _member_ `UINT_TYPE MaterialCBIndexCS;`
  - L601 _member_ `UINT_TYPE MaterialCBIndexVS_Compact;`
  - L602 _member_ `UINT_TYPE MaterialCBIndexCS_Compact;`
  - L604 _member_ `UINT_TYPE MaterialFlags;`
  - L605 _member_ `UINT_TYPE Pad;`
  - L607 _member_ `FNaniteMaterialDisplacementParams MaterialDisplacementParams;`
- L610-616 _struct_ **`FNaniteRasterGroupMeta`** `struct FNaniteRasterGroupMeta`
  - L612 _member_ `UINT_TYPE SWCount;`
  - L613 _member_ `UINT_TYPE HWCount;`
  - L614 _member_ `UINT_TYPE ClusterOffset;`
  - L615 _member_ `UINT_TYPE MaterialFlags_DepthBlock;`
- L618-627 _struct_ **`FNaniteShadingGroupMeta`** `struct FNaniteShadingGroupMeta`
  - L620 _member_ `UINT_TYPE ElementDwordCount;`
  - L621 _member_ `UINT_TYPE ElementDwordStart;`
  - L622 _member_ `UINT_TYPE ElementDwordWriteOffset;`
  - L623 _member_ `UINT_TYPE ThreadGroupCount;`
  - L624 _member_ `UINT_TYPE ThreadGroupStart;`
  - L625 _member_ `UINT_TYPE ThreadGroupWriteOffset;`
  - L626 _member_ `UINT_TYPE Pad[2];`
- L629-634 _struct_ **`FNaniteShadingGroupAllocator`** `struct FNaniteShadingGroupAllocator`
  - L631 _member_ `UINT_TYPE NextElementDword;`
  - L632 _member_ `UINT_TYPE NextThreadGroup;`
  - L633 _member_ `UINT_TYPE Pad[2];`
- L636-656 _struct_ **`FNaniteShadingBinMeta`** `struct FNaniteShadingBinMeta`
  - L640 _member_ `UINT_TYPE ElementCount;` — Common Quad/pixel count shaded by bin
  - L643 _member_ `UINT_TYPE RangeStart;` — Quad/pixel coord range start
  - L646 _member_ `UINT_TYPE MaterialFlags;` — 0:23 Material bit flags, 24:31 Bound Target Mask
  - L650 _member_ `UINT_TYPE ShadingGroup;` — Bindless Only Shading group index
  - L652 _member_ `UINT_TYPE MaterialCBIndex;`
  - L653 _member_ `UINT_TYPE FirstThreadGroup;` — Relative to current group
  - L654 _member_ `UINT_TYPE QuadBinning;`
  - L655 _member_ `UINT_TYPE Pad;`
- L673-678 _struct_ **`FNaniteShadingBinScatterMeta`** `struct FNaniteShadingBinScatterMeta`
  - L675 _member_ `UINT_TYPE RangeEnd;`
  - L676 _member_ `UINT_TYPE FullTileElementCount;`
  - L677 _member_ `UINT_TYPE LooseElementCount;`
- L680-685 _struct_ **`FNaniteShadingBinScatterCounters`** `struct FNaniteShadingBinScatterCounters`
  - L682 _member_ `UINT_TYPE FullTileElementCount;`
  - L683 _member_ `UINT_TYPE LooseElementCount;`
  - L684 _member_ `UINT_TYPE Pad0[30];` — Pad to 128b to better distribute the atomics operations across banks.
- L688-692 _struct_ **`FNaniteShadingBinScatterRanges`** `struct FNaniteShadingBinScatterRanges` — Intentionally separate from counters, so binning pass can use scalar SRV reads.
  - L690 _member_ `UINT_TYPE RangeStart;`
  - L691 _member_ `UINT_TYPE RangeNum;`
- L694-700 _struct_ **`FNaniteShadingBinStats`** `struct FNaniteShadingBinStats`
  - L696 _member_ `UINT_TYPE TotalNanitePixels;`
  - L697 _member_ `UINT_TYPE TotalShadedPixels;`
  - L698 _member_ `UINT_TYPE TotalShadedQuads;`
  - L699 _member_ `UINT_TYPE TotalHelperCount;`

#### Functions (5)

- L397-418 _function_ `INLINE_ATTR FNaniteMaterialFlags UnpackNaniteMaterialFlags(UINT_TYPE Packed)`
- L420-423 _function_ `INLINE_ATTR bool IsNaniteMaterialVertexProgrammable(FNaniteMaterialFlags MaterialFlags)`
- L425-428 _function_ `INLINE_ATTR bool IsNaniteMaterialPixelProgrammable(FNaniteMaterialFlags MaterialFlags)`
- L430-433 _function_ `INLINE_ATTR bool IsNaniteMaterialProgrammable(FNaniteMaterialFlags MaterialFlags)`
- L435-515 _function_ `INLINE_ATTR UINT_TYPE PackNaniteMaterialBitFlags(FNaniteMaterialFlags Flags)`

### `Shaders/Shared/NaniteRayTracingDefinitions.h` (Shared)

- lines: 176; parse: all-branches

#### Macros (#define, 11)

- L6 `#define UINT32_TYPE uint32` _[#if defined(__cplusplus)]_
- L7 `#define UINT64_TYPE uint64` _[#if defined(__cplusplus)]_
- L9 `#define UINT32_TYPE uint` _[#if !(defined(__cplusplus))]_
- L10 `#define UINT64_TYPE uint64_t` _[#if !(defined(__cplusplus))]_
- L15 `#define NANITERT_STAT_BLAS_BUILD_COUNT 0`
- L16 `#define NANITERT_STAT_BLAS_UNUSED_COUNT 1`
- L17 `#define NANITERT_STAT_BLAS_CACHED_COUNT 2`
- L18 `#define NANITERT_STAT_BLAS_CACHED_SIZE 3`
- L19 `#define NANITERT_STAT_BLAS_STAGING_SIZE 4`
- L20 `#define NANITERT_STAT_CLAS_BUILD_COUNT 5`
- L21 `#define NANITERT_STAT_NUM 6`
- L3 #pragma `once`

#### Structs / classes (16)

- L27-31 _struct_ **`GPU_VIRTUAL_ADDRESS_AND_STRIDE`** `struct GPU_VIRTUAL_ADDRESS_AND_STRIDE`
  - L29 _member_ `GPU_VIRTUAL_ADDRESS StartAddress;`
  - L30 _member_ `UINT64_TYPE StrideInBytes;`
- L33-36 _struct_ **`RAYTRACING_CLUSTER_OPS_MOVE_DESC`** `struct RAYTRACING_CLUSTER_OPS_MOVE_DESC` — NVAPI_D3D12_RAYTRACING_ACCELERATION_STRUCTURE_MULTI_INDIRECT_MOVE_ARGS
  - L35 _member_ `GPU_VIRTUAL_ADDRESS SrcAccelerationStructure;` — GPUVA of the object to move
- L38-62 _struct_ **`RAYTRACING_CLUSTER_OPS_BUILD_CLAS_DESC`** `struct RAYTRACING_CLUSTER_OPS_BUILD_CLAS_DESC` — NVAPI_D3D12_RAYTRACING_ACCELERATION_STRUCTURE_MULTI_INDIRECT_TRIANGLE_CLUSTER_ARGS
  - L40 _member_ `UINT32_TYPE ClusterId;`
  - L41 _member_ `UINT32_TYPE ClusterFlags;`
  - L43 _member_ `UINT32_TYPE TriangleCount : 9;`
  - L44 _member_ `UINT32_TYPE VertexCount: 9;`
  - L45 _member_ `UINT32_TYPE PositionTruncateBitCount : 6;`
  - L46 _member_ `UINT32_TYPE IndexFormat : 4;`
  - L47 _member_ `UINT32_TYPE OpacityMicromapIndexFormat : 4;`
  - L49 _member_ `UINT32_TYPE BaseGeometryIndexAndFlags;`
  - L51 _member_ `UINT32_TYPE IndexBufferStride : 16;`
  - L52 _member_ `UINT32_TYPE VertexBufferStride : 16;`
  - L54 _member_ `UINT32_TYPE GeometryIndexAndFlagsBufferStride : 16;`
  - L55 _member_ `UINT32_TYPE OpacityMicromapIndexBufferStride : 16;`
  - L57 _member_ `GPU_VIRTUAL_ADDRESS IndexBuffer;`
  - L58 _member_ `GPU_VIRTUAL_ADDRESS VertexBuffer;`
  - L59 _member_ `GPU_VIRTUAL_ADDRESS GeometryIndexAndFlagsBuffer;`
  - L60 _member_ `GPU_VIRTUAL_ADDRESS OpacityMicromapArray;`
  - L61 _member_ `GPU_VIRTUAL_ADDRESS OpacityMicromapIndexBuffer;`
- L64-89 _struct_ **`RAYTRACING_CLUSTER_OPS_BUILD_CLAS_TEMPLATE_DESC`** `struct RAYTRACING_CLUSTER_OPS_BUILD_CLAS_TEMPLATE_DESC` — NVAPI_D3D12_RAYTRACING_ACCELERATION_STRUCTURE_MULTI_INDIRECT_TRIANGLE_TEMPLATE_ARGS
  - L66 _member_ `UINT32_TYPE ClusterId;`
  - L67 _member_ `UINT32_TYPE ClusterFlags;`
  - L69 _member_ `UINT32_TYPE TriangleCount : 9;`
  - L70 _member_ `UINT32_TYPE VertexCount : 9;`
  - L71 _member_ `UINT32_TYPE PositionTruncateBitCount : 6;`
  - L72 _member_ `UINT32_TYPE IndexFormat : 4;`
  - L73 _member_ `UINT32_TYPE OpacityMicromapIndexFormat : 4;`
  - L75 _member_ `UINT32_TYPE BaseGeometryIndexAndFlags;`
  - L77 _member_ `UINT32_TYPE IndexBufferStride : 16;`
  - L78 _member_ `UINT32_TYPE VertexBufferStride : 16;`
  - L80 _member_ `UINT32_TYPE GeometryIndexAndFlagsBufferStride : 16;`
  - L81 _member_ `UINT32_TYPE OpacityMicromapIndexBufferStride : 16;`
  - L83 _member_ `GPU_VIRTUAL_ADDRESS IndexBuffer;`
  - L84 _member_ `GPU_VIRTUAL_ADDRESS VertexBuffer;`
  - L85 _member_ `GPU_VIRTUAL_ADDRESS GeometryIndexAndFlagsBuffer;`
  - L86 _member_ `GPU_VIRTUAL_ADDRESS OpacityMicromapArray;`
  - L87 _member_ `GPU_VIRTUAL_ADDRESS OpacityMicromapIndexBuffer;`
  - L88 _member_ `GPU_VIRTUAL_ADDRESS InstantiationBoundingBoxLimit;`
- L91-98 _struct_ **`RAYTRACING_CLUSTER_OPS_INSTANTIATE_CLAS_TEMPLATE_DESC`** `struct RAYTRACING_CLUSTER_OPS_INSTANTIATE_CLAS_TEMPLATE_DESC` — NVAPI_D3D12_RAYTRACING_ACCELERATION_STRUCTURE_MULTI_INDIRECT_INSTANTIATE_TEMPLATE_ARGS
  - L93 _member_ `UINT32_TYPE ClusterIdOffset;`
  - L94 _member_ `UINT32_TYPE GeometryIndexOffset;`
  - L96 _member_ `GPU_VIRTUAL_ADDRESS ClusterTemplate;`
  - L97 _member_ `GPU_VIRTUAL_ADDRESS_AND_STRIDE VertexBuffer;`
- L100-105 _struct_ **`RAYTRACING_CLUSTER_OPS_BUILD_BLAS_DESC`** `struct RAYTRACING_CLUSTER_OPS_BUILD_BLAS_DESC` — NVAPI_D3D12_RAYTRACING_ACCELERATION_STRUCTURE_MULTI_INDIRECT_CLUSTER_ARGS
  - L102 _member_ `UINT32_TYPE ClusterCount;`
  - L103 _member_ `UINT32_TYPE Reserved;`
  - L104 _member_ `GPU_VIRTUAL_ADDRESS ClusterVAs;` — Array of CLAS addresses
- L109-114 _struct_ **`FNaniteRayTracingPageData`** `struct FNaniteRayTracingPageData`
  - L111 _member_ `UINT32_TYPE BaseCLASDataIndex;`
  - L112 _member_ `UINT32_TYPE NumClusters;`
  - L113 _member_ `UINT32_TYPE NumAllocatedBlocks;`
- L116-121 _struct_ **`FNaniteRayTracingASData`** `struct FNaniteRayTracingASData`
  - L118 _member_ `GPU_VIRTUAL_ADDRESS Address;`
  - L119 _member_ `UINT32_TYPE Size;`
  - L120 _member_ `UINT32_TYPE AllocationIndex;`
- L123-131 _struct_ **`FClusterStreamOutRequest`** `struct FClusterStreamOutRequest`
  - L125 _member_ `UINT32_TYPE GPUPageIndex;`
  - L126 _member_ `UINT32_TYPE ClusterIndex;`
  - L127 _member_ `UINT32_TYPE VertexBufferOffset;`
  - L128 _member_ `UINT32_TYPE IndexBufferOffset;`
  - L129 _member_ `UINT32_TYPE GeometryIndexAndFlagsBufferOffset;`
  - L130 _member_ `UINT32_TYPE SegmentMappingOffset;`
- L133-138 _struct_ **`FGeometryClusterCutRequest`** `struct FGeometryClusterCutRequest`
  - L135 _member_ `UINT32_TYPE HierarchyOffset;`
  - L136 _member_ `UINT32_TYPE BaseAddressIndex;`
  - L137 _member_ `UINT32_TYPE RuntimeResourceID;`
- L140-145 _struct_ **`FAllocateClustersRequest`** `struct FAllocateClustersRequest`
  - L142 _member_ `UINT32_TYPE BaseCLASIndex;`
  - L143 _member_ `UINT32_TYPE NumClusters;`
  - L144 _member_ `UINT32_TYPE GPUPageIndex;`
- L147-150 _struct_ **`FFreeClustersRequest`** `struct FFreeClustersRequest`
  - L149 _member_ `UINT32_TYPE GPUPageIndex;`
- L152-156 _struct_ **`FStreamingTraversalRequest`** `struct FStreamingTraversalRequest`
  - L154 _member_ `UINT32_TYPE HierarchyOffset;`
  - L155 _member_ `UINT32_TYPE RuntimeResourceID;`
- L158-161 _struct_ **`FNaniteRayTracingASCacheRequest`** `struct FNaniteRayTracingASCacheRequest`
  - L160 _member_ `UINT32_TYPE Size;`
- L163-168 _struct_ **`FNaniteRayTracingASCacheEntry`** `struct FNaniteRayTracingASCacheEntry`
  - L165 _member_ `UINT32_TYPE ByteSize;` — (0 = empty slot)
  - L166 _member_ `UINT32_TYPE ByteOffset;`
  - L167 _member_ `UINT32_TYPE UpdateSequenceId;` — Incremented by CPU to force invalidation
- L170-174 _struct_ **`FNaniteRayTracingASCacheMetadata`** `struct FNaniteRayTracingASCacheMetadata`
  - L172 _member_ `UINT32_TYPE Key;`
  - L173 _member_ `UINT32_TYPE UpdateSequenceId;`

#### typedef / using (1)

- L25 _typedef_ `typedef UINT64_TYPE GPU_VIRTUAL_ADDRESS;`

### `Shaders/Shared/PathTracingDefinitions.h` (Shared)

- lines: 144; parse: all-branches

#### Macros (#define, 115)

- L6 `#define PATHTRACER_SAMPLER_DEFAULT 0`
- L7 `#define PATHTRACER_SAMPLER_ERROR_DIFFUSION 1`
- L10 `#define PATH_TRACER_KERNEL_CAMERA 0`
- L11 `#define PATH_TRACER_KERNEL_INNER 1`
- L12 `#define PATH_TRACER_KERNEL_TAIL 2`
- L15 `#define PATHTRACER_FLAG_LIGHTING_CHANNEL_MASK (7 << 0)`
- L16 `#define PATHTRACER_FLAG_TRANSMISSION_MASK (1 << 3)`
- L17 `#define PATHTRACER_FLAG_NON_INVERSE_SQUARE_FALLOFF_MASK (1 << 4)`
- L18 `#define PATHTRACER_FLAG_STATIONARY_MASK (1 << 5)`
- L19 `#define PATHTRACER_FLAG_TYPE_MASK (7 << 6)`
- L20 `#define PATHTRACING_LIGHT_SKY (0 << 6)`
- L21 `#define PATHTRACING_LIGHT_DIRECTIONAL (1 << 6)`
- L22 `#define PATHTRACING_LIGHT_POINT (2 << 6)`
- L23 `#define PATHTRACING_LIGHT_SPOT (3 << 6)`
- L24 `#define PATHTRACING_LIGHT_RECT (4 << 6)`
- L25 `#define PATHTRACER_FLAG_CAST_SHADOW_MASK (1 << 9)`
- L26 `#define PATHTRACER_FLAG_CAST_VOL_SHADOW_MASK (1 << 10)`
- L27 `#define PATHTRACER_FLAG_CAST_CLOUD_SHADOW_MASK (1 << 11)`
- L28 `#define PATHTRACER_FLAG_HAS_RECT_TEXTURE_MASK (1 << 12)`
- L30 `#define PATHTRACER_MASK_CAMERA_OPAQUE 0x01`
- L31 `#define PATHTRACER_MASK_CAMERA_TRANSLUCENT 0x02`
- L32 `#define PATHTRACER_MASK_SHADOW 0x04`
- L33 `#define PATHTRACER_MASK_INDIRECT_OPAQUE 0x08`
- L34 `#define PATHTRACER_MASK_INDIRECT_TRANSLUCENT 0x10`
- L35 `#define PATHTRACER_MASK_REFLECTION_OPAQUE 0x20`
- L36 `#define PATHTRACER_MASK_REFLECTION_TRANSLUCENT 0x40`
- L37 `#define PATHTRACER_MASK_SSS_RANDOM_WALK 0x80`
- L39 `#define PATHTRACER_MASK_IGNORE 0x00`
- L40 `#define PATHTRACER_MASK_ALL 0xFF`
- L45 `#define PATHTRACER_CONTRIBUTION_EMISSIVE 1`
- L46 `#define PATHTRACER_CONTRIBUTION_DIFFUSE 2`
- L47 `#define PATHTRACER_CONTRIBUTION_SPECULAR 4`
- L48 `#define PATHTRACER_CONTRIBUTION_VOLUME 8`
- L51 `#define PATHTRACER_LIGHT_GRID_SINGULAR_MASK 0x80000000u`
- L52 `#define PATHTRACER_LIGHT_GRID_LIGHT_COUNT_MASK 0x7FFFFFFFu`
- L55 `#define VOLUMEID_ATMOSPHERE 0`
- L56 `#define VOLUMEID_CLOUDS 1`
- L57 `#define VOLUMEID_FOG 2`
- L58 `#define VOLUMEID_HETEROGENEOUS_VOLUMES 3`
- L59 `#define PATH_TRACER_MAX_VOLUMES 4`
- L61 `#define PATH_TRACER_VOLUME_ENABLE_BIT (1u)`
- L62 `#define PATH_TRACER_VOLUME_ENABLE_ATMOSPHERE (PATH_TRACER_VOLUME_ENABLE_BIT << VOLUMEID_ATMOSPHERE)`
- L63 `#define PATH_TRACER_VOLUME_ENABLE_CLOUDS (PATH_TRACER_VOLUME_ENABLE_BIT << VOLUMEID_CLOUDS)`
- L64 `#define PATH_TRACER_VOLUME_ENABLE_FOG (PATH_TRACER_VOLUME_ENABLE_BIT << VOLUMEID_FOG)`
- L65 `#define PATH_TRACER_VOLUME_ENABLE_HETEROGENEOUS_VOLUMES (PATH_TRACER_VOLUME_ENABLE_BIT << VOLUMEID_HETEROGENEOUS_VOLUMES)`
- L66 `#define PATH_TRACER_VOLUME_ENABLE_MASK ((1u << PATH_TRACER_MAX_VOLUMES) - 1)`
- L68 `#define PATH_TRACER_VOLUME_HOLDOUT_BIT (PATH_TRACER_VOLUME_ENABLE_BIT << PATH_TRACER_MAX_VOLUMES)`
- L69 `#define PATH_TRACER_VOLUME_HOLDOUT_ATMOSPHERE (PATH_TRACER_VOLUME_HOLDOUT_BIT << VOLUMEID_ATMOSPHERE)`
- L70 `#define PATH_TRACER_VOLUME_HOLDOUT_CLOUDS (PATH_TRACER_VOLUME_HOLDOUT_BIT << VOLUMEID_CLOUDS)`
- L71 `#define PATH_TRACER_VOLUME_HOLDOUT_FOG (PATH_TRACER_VOLUME_HOLDOUT_BIT << VOLUMEID_FOG)`
- L72 `#define PATH_TRACER_VOLUME_HOLDOUT_HETEROGENEOUS_VOLUMES (PATH_TRACER_VOLUME_HOLDOUT_BIT << VOLUMEID_HETEROGENEOUS_VOLUMES)`
- L73 `#define PATH_TRACER_VOLUME_HOLDOUT_MASK (PATH_TRACER_VOLUME_ENABLE_MASK << PATH_TRACER_MAX_VOLUMES)`
- L75 `#define PATH_TRACER_VOLUME_USE_ANALYTIC_TRANSMITTANCE (256u)`
- L78 `#define PATH_TRACER_VOLUME_CALLABLE_FLAGS_TRANSMITTANCE (512u)`
- L79 `#define PATH_TRACER_VOLUME_CALLABLE_FLAGS_GET_SAMPLE (1024u)`
- L80 `#define PATH_TRACER_VOLUME_CALLABLE_FLAGS_BOUNCE_MASK (2048u * 31)`
- L81 `#define PATH_TRACER_VOLUME_CALLABLE_FLAGS_BOUNCE_SHIFT (11)`
- L84 `#define PATH_TRACER_VOLUME_SHOW_PLANET_GROUND (65536u)`
- L87 `#define PATH_TRACER_DEBUG_VIZ_RADIANCE 0`
- L88 `#define PATH_TRACER_DEBUG_VIZ_WORLD_NORMAL 1`
- L89 `#define PATH_TRACER_DEBUG_VIZ_WORLD_SMOOTH_NORMAL 2`
- L90 `#define PATH_TRACER_DEBUG_VIZ_WORLD_GEO_NORMAL 3`
- L91 `#define PATH_TRACER_DEBUG_VIZ_BASE_COLOR 4`
- L92 `#define PATH_TRACER_DEBUG_VIZ_DIFFUSE_COLOR 5`
- L93 `#define PATH_TRACER_DEBUG_VIZ_SPECULAR_COLOR 6`
- L94 `#define PATH_TRACER_DEBUG_VIZ_TRANSPARENCY_COLOR 7`
- L95 `#define PATH_TRACER_DEBUG_VIZ_METALLIC 8`
- L96 `#define PATH_TRACER_DEBUG_VIZ_SPECULAR 9`
- L97 `#define PATH_TRACER_DEBUG_VIZ_ROUGHNESS 10`
- L98 `#define PATH_TRACER_DEBUG_VIZ_IOR 11`
- L99 `#define PATH_TRACER_DEBUG_VIZ_SHADING_MODEL 12`
- L100 `#define PATH_TRACER_DEBUG_VIZ_LIGHTING_CHANNEL_MASK 13`
- L101 `#define PATH_TRACER_DEBUG_VIZ_CUSTOM_DATA0 14`
- L102 `#define PATH_TRACER_DEBUG_VIZ_CUSTOM_DATA1 15`
- L103 `#define PATH_TRACER_DEBUG_VIZ_WORLD_POSITION 16`
- L104 `#define PATH_TRACER_DEBUG_VIZ_PRIMARY_RAYS 17`
- L105 `#define PATH_TRACER_DEBUG_VIZ_WORLD_TANGENT 18`
- L106 `#define PATH_TRACER_DEBUG_VIZ_ANISOTROPY 19`
- L107 `#define PATH_TRACER_DEBUG_VIZ_LIGHT_GRID_COUNT 20`
- L108 `#define PATH_TRACER_DEBUG_VIZ_LIGHT_GRID_AXIS 21`
- L109 `#define PATH_TRACER_DEBUG_VIZ_LIGHT_GRID_LIST_HASH 22`
- L110 `#define PATH_TRACER_DEBUG_VIZ_LIGHT_GRID_SINGULAR 23`
- L111 `#define PATH_TRACER_DEBUG_VIZ_DECAL_GRID_COUNT 24`
- L112 `#define PATH_TRACER_DEBUG_VIZ_DECAL_GRID_AXIS 25`
- L113 `#define PATH_TRACER_DEBUG_VIZ_DECAL_GRID_LIST_HASH 26`
- L114 `#define PATH_TRACER_DEBUG_VIZ_VOLUME_LIGHT_COUNT 27`
- L115 `#define PATH_TRACER_DEBUG_VIZ_HITKIND 28`
- L116 `#define PATH_TRACER_DEBUG_VIZ_TRANSPARENCY_COUNT 29`
- L117 `#define PATH_TRACER_DEBUG_VIZ_SSS_COLOR 30`
- L118 `#define PATH_TRACER_DEBUG_VIZ_SSS_RADIUS 31`
- L119 `#define PATH_TRACER_DEBUG_VIZ_SSS_WEIGHT 32`
- L120 `#define PATH_TRACER_DEBUG_VIZ_SSS_PHASE 33`
- L121 `#define PATH_TRACER_DEBUG_VIZ_FUZZ_COLOR 34`
- L122 `#define PATH_TRACER_DEBUG_VIZ_FUZZ_ROUGHNESS 35`
- L123 `#define PATH_TRACER_DEBUG_VIZ_FUZZ_AMOUNT 36`
- L124 `#define PATH_TRACER_DEBUG_VIZ_BSDF_OPACITY 37`
- L125 `#define PATH_TRACER_DEBUG_VIZ_SUBSTRATE_WEIGHT_V 38`
- L126 `#define PATH_TRACER_DEBUG_VIZ_SUBSTRATE_TRANSMITTANCE_N 39`
- L127 `#define PATH_TRACER_DEBUG_VIZ_SUBSTRATE_COVERAGE_ABOVE_N 40`
- L128 `#define PATH_TRACER_DEBUG_VIZ_SUBSTRATE_F90 41`
- L129 `#define PATH_TRACER_DEBUG_VIZ_EYE_IRIS_MASK 42`
- L130 `#define PATH_TRACER_DEBUG_VIZ_EYE_CAUSTIC_NORMAL 43`
- L131 `#define PATH_TRACER_DEBUG_VIZ_EYE_IRIS_NORMAL 44`
- L132 `#define PATH_TRACER_DEBUG_VIZ_BACKFACING_NORMAL 45`
- L133 `#define PATH_TRACER_DEBUG_VIZ_HAIR_PRIMITIVE_UV 46`
- L134 `#define PATH_TRACER_DEBUG_VIZ_TRIANGLE_ID 47`
- L135 `#define PATH_TRACER_DEBUG_VIZ_INSTANCE_ID 48`
- L136 `#define PATH_TRACER_DEBUG_VIZ_CLUSTER_ID 49`
- L137 `#define PATH_TRACER_DEBUG_VIZ_DECAL_COVERAGE 50`
- L138 `#define PATH_TRACER_DEBUG_VIZ_DECAL_COLOR 51`
- L139 `#define PATH_TRACER_DEBUG_VIZ_DECAL_NORMAL 52`
- L140 `#define PATH_TRACER_DEBUG_VIZ_DECAL_RMS 53`
- L141 `#define PATH_TRACER_DEBUG_VIZ_DECAL_RADIANCE 54`
- L142 `#define PATH_TRACER_DEBUG_VIZ_DECAL_RESPONSE_MASK 55`
- L143 `#define PATH_TRACER_DEBUG_VIZ_DECAL_USE_DBUFFER 56`
- L3 #pragma `once`

### `Shaders/Shared/RayTracingBuiltInResources.h` (Shared)

- lines: 85; parse: all-branches
- includes: L11 `RayTracingDefinitions.h`, L12 `HLSLReservedSpaces.h`

#### Macros (#define, 10)

- L15 `#define INCLUDED_FROM_CPP_CODE 1` _[#if defined(__cplusplus)]_
- L16 `#define INCLUDED_FROM_HLSL_CODE 0` _[#if defined(__cplusplus)]_
- L18 `#define INCLUDED_FROM_CPP_CODE 0` _[#if !(defined(__cplusplus))]_
- L19 `#define INCLUDED_FROM_HLSL_CODE 1` _[#if !(defined(__cplusplus))]_
- L23 `#define UINT_TYPE uint` _[#if INCLUDED_FROM_HLSL_CODE]_
- L25 `#define UINT_TYPE unsigned int` _[#if !(INCLUDED_FROM_HLSL_CODE) && INCLUDED_FROM_CPP_CODE]_
- L65 `#define RAY_TRACING_SYSTEM_INDEXBUFFER_REGISTER 0`
- L66 `#define RAY_TRACING_SYSTEM_VERTEXBUFFER_REGISTER 1`
- L67 `#define RAY_TRACING_SYSTEM_ROOTCONSTANT_REGISTER 0`
- L70 `#define OVERRIDE_RAY_TRACING_HIT_GROUP_SYSTEM_RESOURCES 0` _[#if !defined(OVERRIDE_RAY_TRACING_HIT_GROUP_SYSTEM_RESOURCES)]_
- L9 #pragma `once`; L81 #undef `INCLUDED_FROM_CPP_CODE`; L82 #undef `INCLUDED_FROM_HLSL_CODE`; L83 #undef `UINT_TYPE`

#### Structs / classes (1)

- L28-63 _struct_ **`FHitGroupSystemRootConstants`** `struct FHitGroupSystemRootConstants`
  - L34 _member_ `UINT_TYPE Config;` — Config is a bitfield: uint IndexStride  : 8; // Can be just 1 bit to indicate 16 or 32 bit indices uint VertexStride : 8; // Can be just 2 bits to indicate float3, float2 or half2 format uint Unused       : 16;
  - L37 _member_ `UINT_TYPE IndexBufferOffsetInBytes;` — Offset into HitGroupSystemIndexBuffer
  - L40 _member_ `UINT_TYPE FirstPrimitive;` — First primitive of the segment (as set in FRayTracingGeometrySegment)
  - L43 _member_ `UINT_TYPE UserData;` — User-provided constant assigned to the hit group
  - L47 _method_ `UINT_TYPE GetIndexStride()`
  - L52 _method_ `UINT_TYPE GetVertexStride()`
  - L58 _method_ `void SetVertexAndIndexStride(UINT_TYPE Vertex, UINT_TYPE Index)` _[#if INCLUDED_FROM_CPP_CODE]_

#### Prototypes (3)

- L75 _prototype_ `ByteAddressBuffer HitGroupSystemIndexBuffer : UE_HLSL_REGISTER(t, RAY_TRACING_SYSTEM_INDEXBUFFER_REGISTER, UE_HLSL_SPACE_RAY_TRACING_SYSTEM)` — Built-in local root parameters that are always bound to all hit shaders _[#if INCLUDED_FROM_HLSL_CODE && !OVERRIDE_RAY_TRACING_HIT_GROUP_SYSTEM_RESOURCES]_
- L76 _prototype_ `ByteAddressBuffer HitGroupSystemVertexBuffer : UE_HLSL_REGISTER(t, RAY_TRACING_SYSTEM_VERTEXBUFFER_REGISTER, UE_HLSL_SPACE_RAY_TRACING_SYSTEM)` _[#if INCLUDED_FROM_HLSL_CODE && !OVERRIDE_RAY_TRACING_HIT_GROUP_SYSTEM_RESOURCES]_
- L77 _prototype_ `ConstantBuffer<FHitGroupSystemRootConstants> HitGroupSystemRootConstants : UE_HLSL_REGISTER(b, RAY_TRACING_SYSTEM_ROOTCONSTANT_REGISTER, UE_HLSL_SPACE_RAY_TRACING_SYSTEM)` _[#if INCLUDED_FROM_HLSL_CODE && !OVERRIDE_RAY_TRACING_HIT_GROUP_SYSTEM_RESOURCES]_

### `Shaders/Shared/RayTracingDebugTypes.h` (Shared)

- lines: 83; parse: all-branches; parse notes: 3

#### Macros (#define, 4)

- L11 `#define UINT32_TYPE uint32` _[#if defined(__cplusplus)]_
- L12 `#define UINT64_TYPE uint64` _[#if defined(__cplusplus)]_
- L14 `#define UINT32_TYPE uint` _[#if !(defined(__cplusplus))]_
- L15 `#define UINT64_TYPE uint64_t` _[#if !(defined(__cplusplus))]_
- L3 #pragma `once`; L81 #undef `UINT32_TYPE`; L82 #undef `UINT64_TYPE`

#### Structs / classes (4)

- L18-31 _struct_ **`FRayTracingInstanceDebugData`** `struct FRayTracingInstanceDebugData`
  - L20 _member_ `UINT32_TYPE Flags;`
  - L21 _member_ `UINT32_TYPE ProxyHash;`
  - L22 _member_ `UINT64_TYPE GeometryAddress;`
- L33-44 _struct_ **`FRayTracingInstanceExtraData`** `struct FRayTracingInstanceExtraData`
  - L35 _member_ `UINT32_TYPE SceneInstanceIndex;`
  - L36 _member_ `UINT32_TYPE GPUSceneInstanceId;`
- L46-68 _struct_ **`FRayTracingPickingFeedback`** `struct FRayTracingPickingFeedback`
  - L49 _member_ `UINT32_TYPE InstanceIndex;` — Hit data
  - L50 _member_ `UINT32_TYPE GeometryIndex;`
  - L51 _member_ `UINT32_TYPE TriangleIndex;`
  - L54 _member_ `UINT64_TYPE GeometryAddress;` — Geometry data
  - L57 _member_ `UINT32_TYPE InstanceId;` — Instance data
  - L58 _member_ `UINT32_TYPE Mask;`
  - L59 _member_ `UINT32_TYPE InstanceContributionToHitGroupIndex;`
  - L60 _member_ `UINT32_TYPE Flags;`
- L70-79 _struct_ **`FRayTracingHitStatsEntry`** `struct FRayTracingHitStatsEntry`
  - L72 _member_ `UINT32_TYPE PrimitiveID;`
  - L73 _member_ `UINT32_TYPE Count;`
  - L76 _ctor_ `FRayTracingHitStatsEntry()` _[#if defined(__cplusplus)]_

#### Unparsed (raw text) (3)

- L25-29 _unparsed_ `FRayTracingInstanceDebugData() : Flags(0) , ProxyHash(0) , GeometryAddress(0)` (scope `FRayTracingInstanceDebugData`) _[#if defined(__cplusplus)]_
- L39-42 _unparsed_ `FRayTracingInstanceExtraData() : SceneInstanceIndex(-1) , GPUSceneInstanceId(-1)` (scope `FRayTracingInstanceExtraData`) _[#if defined(__cplusplus)]_
- L63-66 _unparsed_ `FRayTracingPickingFeedback() : InstanceIndex(0xFFFFFFFF) , GeometryAddress(0xFFFFFFFFFFFFFFFF)` (scope `FRayTracingPickingFeedback`) _[#if defined(__cplusplus)]_

<details><summary>parse notes</summary>

- L25: unrecognised block header 'FRayTracingInstanceDebugData() : Flags(0) , ProxyHash(0) , GeometryAddress(0)'
- L39: unrecognised block header 'FRayTracingInstanceExtraData() : SceneInstanceIndex(-1) , GPUSceneInstanceId(-1)'
- L63: unrecognised block header 'FRayTracingPickingFeedback() : InstanceIndex(0xFFFFFFFF) , GeometryAddress(0xFFF'

</details>

### `Shaders/Shared/RayTracingDefinitions.h` (Shared)

- lines: 49; parse: all-branches
- includes: L10 `HLSLReservedSpaces.h`

#### Macros (#define, 27)

- L14 `#define RAY_TRACING_SHADER_VERSION 0x500880FC`
- L16 `#define RAY_TRACING_MASK_OPAQUE 0x01`
- L17 `#define RAY_TRACING_MASK_TRANSLUCENT 0x02`
- L18 `#define RAY_TRACING_MASK_OPAQUE_SHADOW 0x04`
- L19 `#define RAY_TRACING_MASK_TRANSLUCENT_SHADOW 0x08`
- L20 `#define RAY_TRACING_MASK_THIN_SHADOW 0x10`
- L21 `#define RAY_TRACING_MASK_OPAQUE_REFLECTION 0x20`
- L22 `#define RAY_TRACING_MASK_HAIR_STRANDS 0x40`
- L23 `#define RAY_TRACING_MASK_OPAQUE_FP_WORLD_SPACE 0x80`
- L24 `#define RAY_TRACING_MASK_ALL 0xFF`
- L26 `#define RAY_TRACING_MASK_SHADOW (RAY_TRACING_MASK_OPAQUE_SHADOW \| RAY_TRACING_MASK_TRANSLUCENT_SHADOW)`
- L28 `#define RAY_TRACING_SHADER_SLOT_MATERIAL 0`
- L29 `#define RAY_TRACING_SHADER_SLOT_SHADOW 1`
- L30 `#define RAY_TRACING_NUM_SHADER_SLOTS 2`
- L32 `#define RAY_TRACING_MISS_SHADER_SLOT_DEFAULT 0`
- L33 `#define RAY_TRACING_MISS_SHADER_SLOT_LIGHTING 1`
- L34 `#define RAY_TRACING_NUM_MISS_SHADER_SLOTS 2`
- L36 `#define RAY_TRACING_LIGHT_COUNT_MAXIMUM 256`
- L37 `#define RAY_TRACING_DECAL_COUNT_MAXIMUM 256`
- L39 `#define RAY_TRACING_MAX_ALLOWED_RECURSION_DEPTH 1`
- L40 `#define RAY_TRACING_MAX_ALLOWED_ATTRIBUTE_SIZE 8`
- L43 `#define RAY_TRACING_SHADOWS_TYPE_OFF 0`
- L44 `#define RAY_TRACING_SHADOWS_TYPE_HARD 1`
- L45 `#define RAY_TRACING_SHADOWS_TYPE_SOFT 2`
- L47 `#define RAY_TRACING_SHADOWS_TRANSLUCENCY_TYPE_OPAQUE 0`
- L48 `#define RAY_TRACING_SHADOWS_TRANSLUCENCY_TYPE_MASKED 1`
- L49 `#define RAY_TRACING_SHADOWS_TRANSLUCENCY_TYPE_FRACTIONAL_VISIBILITY 2`
- L8 #pragma `once`

### `Shaders/Shared/RayTracingPayloadType.h` (Shared)

- lines: 68; parse: last-branch (retry, +0 merged from all-branches pass)
- includes: L5 `HLSLStaticAssert.h`

#### Macros (#define, 15)

- L7 `#define RT_PAYLOAD_TYPE_MINIMAL (1 << 0)`
- L8 `#define RT_PAYLOAD_TYPE_DEFAULT (1 << 1)`
- L9 `#define RT_PAYLOAD_TYPE_RAYTRACING_MATERIAL (1 << 2)`
- L10 `#define RT_PAYLOAD_TYPE_RAYTRACING_DEBUG (1 << 3)`
- L11 `#define RT_PAYLOAD_TYPE_DEFERRED (1 << 4)`
- L12 `#define RT_PAYLOAD_TYPE_PATHTRACING_MATERIAL (1 << 5)`
- L13 `#define RT_PAYLOAD_TYPE_LUMEN_MINIMAL (1 << 6)`
- L14 `#define RT_PAYLOAD_TYPE_VFX (1 << 7)`
- L15 `#define RT_PAYLOAD_TYPE_DECALS (1 << 8)`
- L16 `#define RT_PAYLOAD_TYPE_SPARSE_VOXEL (1 << 9)`
- L17 `#define RT_PAYLOAD_TYPE_GPULIGHTMASS (1 << 10)`
- L50 `#define IS_PAYLOAD_ENABLED(T) ((RT_PAYLOAD_TYPE & (T)) != 0)` _[#if defined(RT_PAYLOAD_TYPE)]_
- L55 `#define IS_PAYLOAD_ENABLED(T) (0)` _[#if !(defined(RT_PAYLOAD_TYPE))]_
- L62 `#define CHECK_RT_PAYLOAD_SIZE(StructName) HLSL_STATIC_ASSERT(sizeof(StructName) <= RT_PAYLOAD_MAX_SIZE, "Payload " #StructName " is larger than expected");` _[#if defined(RT_PAYLOAD_MAX_SIZE)]_
- L66 `#define CHECK_RT_PAYLOAD_SIZE(StructName) ` _[#if !(defined(RT_PAYLOAD_MAX_SIZE))]_
- L3 #pragma `once`

#### Enums (1)

- L29-44 _enum_ **`ERayTracingPayloadType`** `enum ERayTracingPayloadType : uint` — base/reg: `uint` — HLSL _[#if !(defined(__cplusplus))]_
  - L32 _enumerator_ `None = 0` — placeholder for non-raytracing shaders
  - L33 _enumerator_ `Minimal = RT_PAYLOAD_TYPE_MINIMAL`
  - L34 _enumerator_ `Default = RT_PAYLOAD_TYPE_DEFAULT`
  - L35 _enumerator_ `RayTracingMaterial = RT_PAYLOAD_TYPE_RAYTRACING_MATERIAL`
  - L36 _enumerator_ `RayTracingDebug = RT_PAYLOAD_TYPE_RAYTRACING_DEBUG`
  - L37 _enumerator_ `Deferred = RT_PAYLOAD_TYPE_DEFERRED`
  - L38 _enumerator_ `PathTracingMaterial = RT_PAYLOAD_TYPE_PATHTRACING_MATERIAL`
  - L39 _enumerator_ `LumenMinimal = RT_PAYLOAD_TYPE_LUMEN_MINIMAL`
  - L40 _enumerator_ `VFX = RT_PAYLOAD_TYPE_VFX`
  - L41 _enumerator_ `Decals = RT_PAYLOAD_TYPE_DECALS`
  - L42 _enumerator_ `SparseVoxel = RT_PAYLOAD_TYPE_SPARSE_VOXEL`
  - L43 _enumerator_ `GPULightmass = RT_PAYLOAD_TYPE_GPULIGHTMASS`

### `Shaders/Shared/RayTracingTypes.h` (Shared)

- lines: 121; parse: all-branches
- includes: L10 `HLSLStaticAssert.h`, L13 `HLSLTypeAliases.h` [defined(__cplusplus)]
- L3 #pragma `once`

#### Structs / classes (5)

- L19-42 _struct_ **`UE::HLSL::FRTLightingData`** `struct FRTLightingData`
  - L21 _member_ `uint Type;`
  - L22 _member_ `float IESAtlasIndex;`
  - L23 _member_ `float RectLightAtlasMaxLevel;`
  - L24 _member_ `uint LightMissShaderIndex;`
  - L25 _member_ `float3 TranslatedLightPosition;`
  - L26 _member_ `float InvRadius;`
  - L27 _member_ `float3 Direction;`
  - L28 _member_ `float FalloffExponent;`
  - L29 _member_ `float3 LightColor;`
  - L30 _member_ `uint DiffuseSpecularScale;`
  - L31 _member_ `float3 Tangent;`
  - L32 _member_ `float SourceRadius;`
  - L33 _member_ `float2 SpotAngles;`
  - L34 _member_ `float SourceLength;`
  - L35 _member_ `float SoftSourceRadius;`
  - L36 _member_ `uint DistanceFadeMAD;`
  - L37 _member_ `float IndirectLightScale;`
  - L38 _member_ `float RectLightBarnCosAngle;`
  - L39 _member_ `float RectLightBarnLength;`
  - L40 _member_ `float2 RectLightAtlasUVOffset;`
  - L41 _member_ `float2 RectLightAtlasUVScale;`
- L46-66 _struct_ **`UE::HLSL::FPathTracingLight`** `struct FPathTracingLight` — #dxr_todo: Unify this with FRTLightingData ?
  - L48 _member_ `float3 TranslatedWorldPosition;`
  - L49 _member_ `float3 Normal;`
  - L50 _member_ `float3 Tangent;`
  - L51 _member_ `float3 Color;`
  - L52 _member_ `float2 Dimensions;` — Radius,Length or RectWidth,RectHeight or Sin(Angle/2),0 depending on light type
  - L53 _member_ `float2 Shaping;` — Barndoor controls for RectLights, Cone angles for spot lights
  - L54 _member_ `uint DiffuseSpecularScale;`
  - L55 _member_ `float IndirectLightingScale;`
  - L56 _member_ `float Attenuation;`
  - L57 _member_ `float FalloffExponent;` — for non-inverse square decay lights only
  - L58 _member_ `float VolumetricScatteringIntensity;` — scale for volume contributions
  - L59 _member_ `float IESAtlasIndex;`
  - L60 _member_ `uint Flags;` — see defines PATHTRACER_FLAG_*
  - L61 _member_ `uint MissShaderIndex;` — used to implement light functions
  - L62 _member_ `float2 RectLightAtlasUVScale;` — Rect. light atlas UV transformation
  - L63 _member_ `float2 RectLightAtlasUVOffset;` — Rect. light atlas UV transformation
  - L64 _member_ `float3 CameraColorScale;` — Tinting factor for camera rays only
  - L65 _member_ `uint Padding;`
- L69-81 _struct_ **`UE::HLSL::FPathTracingPackedPathState`** `struct FPathTracingPackedPathState`
  - L71 _member_ `uint RandSeqSampleIndex;`
  - L72 _member_ `uint RandSeqSampleSeed;`
  - L73 _member_ `float3 Radiance;`
  - L74 _member_ `float Alpha;`
  - L75 _member_ `uint3 PackedAlbedoNormal;`
  - L76 _member_ `float3 RayOrigin;`
  - L77 _member_ `float3 RayDirection;`
  - L78 _member_ `float3 PathThroughput;`
  - L79 _member_ `uint2 PackedRoughnessSigma;`
  - L80 _member_ `uint2 PackedScatterPhase;`
- L84-97 _struct_ **`UE::HLSL::FPathTracingDebugPackedPathState`** `struct FPathTracingDebugPackedPathState`
  - L86 _member_ `uint RandSeqSampleIndex;`
  - L87 _member_ `uint RandSeqSampleSeed;`
  - L88 _member_ `float3 Radiance;`
  - L89 _member_ `float Alpha;`
  - L90 _member_ `uint3 PackedDiffSpecColor;`
  - L91 _member_ `uint2 PackedNormalRoughness;`
  - L92 _member_ `float3 RayOrigin;`
  - L93 _member_ `float3 RayDirection;`
  - L94 _member_ `float3 PathThroughput;`
  - L95 _member_ `uint2 PackedRoughnessSigma;`
  - L96 _member_ `uint2 PackedScatterPhase;`
- L101-108 _struct_ **`UE::HLSL::FRayTracingDecal`** `struct FRayTracingDecal`
  - L103 _member_ `float3 TranslatedBoundMin;`
  - L104 _member_ `uint Pad0;` — keep structure aligned
  - L105 _member_ `float3 TranslatedBoundMax;`
  - L106 _member_ `uint CallableSlotIndex;`
  - L107 _member_ `float4x4 TranslatedWorldToDecal;`

#### Namespaces (1)

- L15-112 _namespace_ **`UE::HLSL`** `namespace UE::HLSL` _[#if defined(__cplusplus)]_

#### typedef / using (5)

- L114 _typedef_ `using FRTLightingData = UE::HLSL::FRTLightingData;` _[#if defined(__cplusplus)]_
- L115 _typedef_ `using FPathTracingLight = UE::HLSL::FPathTracingLight;` _[#if defined(__cplusplus)]_
- L116 _typedef_ `using FPathTracingPackedPathState = UE::HLSL::FPathTracingPackedPathState;` _[#if defined(__cplusplus)]_
- L117 _typedef_ `using FPathTracingDebugPackedPathState = UE::HLSL::FPathTracingDebugPackedPathState;` _[#if defined(__cplusplus)]_
- L118 _typedef_ `using FRayTracingDecal = UE::HLSL::FRayTracingDecal;` _[#if defined(__cplusplus)]_

#### Top-level macro invocations (5)

- L43 _macro_call_ `HLSL_STATIC_ASSERT(sizeof(FRTLightingData) == 128, "Ray tracing light structure should be kept as small as possible")` (scope `UE::HLSL`)
- L67 _macro_call_ `HLSL_STATIC_ASSERT(sizeof(FPathTracingLight) == 128, "Path tracing light structure should be kept as small as possible")` (scope `UE::HLSL`)
- L82 _macro_call_ `HLSL_STATIC_ASSERT(sizeof(FPathTracingPackedPathState) == 88, "Packed Path State size should be minimized")` (scope `UE::HLSL`)
- L98 _macro_call_ `HLSL_STATIC_ASSERT(sizeof(FPathTracingDebugPackedPathState) == 96, "Packed Path State size should be minimized")` (scope `UE::HLSL`)
- L109 _macro_call_ `HLSL_STATIC_ASSERT(sizeof(FRayTracingDecal) == 96, "Ray tracing decal structure should be aligned to 32 bytes for optimal access on the GPU")` (scope `UE::HLSL`)

### `Shaders/Shared/RaytracingDebugDefinitions.h` (Shared)

- lines: 113; parse: all-branches

#### Macros (#define, 57)

- L10 `#define RAY_TRACING_DEBUG_VIZ_RADIANCE 0`
- L11 `#define RAY_TRACING_DEBUG_VIZ_WORLD_NORMAL 1`
- L12 `#define RAY_TRACING_DEBUG_VIZ_BASE_COLOR 2`
- L13 `#define RAY_TRACING_DEBUG_VIZ_DIFFUSE_COLOR 3`
- L14 `#define RAY_TRACING_DEBUG_VIZ_SPECULAR_COLOR 4`
- L15 `#define RAY_TRACING_DEBUG_VIZ_OPACITY 5`
- L16 `#define RAY_TRACING_DEBUG_VIZ_METALLIC 6`
- L17 `#define RAY_TRACING_DEBUG_VIZ_SPECULAR 7`
- L18 `#define RAY_TRACING_DEBUG_VIZ_ROUGHNESS 8`
- L19 `#define RAY_TRACING_DEBUG_VIZ_IOR 9`
- L20 `#define RAY_TRACING_DEBUG_VIZ_SHADING_MODEL 10`
- L21 `#define RAY_TRACING_DEBUG_VIZ_BLENDING_MODE 11`
- L22 `#define RAY_TRACING_DEBUG_VIZ_LIGHTING_CHANNEL_MASK 12`
- L23 `#define RAY_TRACING_DEBUG_VIZ_CUSTOM_DATA 13`
- L24 `#define RAY_TRACING_DEBUG_VIZ_GBUFFER_AO 14`
- L25 `#define RAY_TRACING_DEBUG_VIZ_INDIRECT_IRRADIANCE 15`
- L26 `#define RAY_TRACING_DEBUG_VIZ_WORLD_POSITION 16`
- L27 `#define RAY_TRACING_DEBUG_VIZ_HITKIND 17`
- L28 `#define RAY_TRACING_DEBUG_VIZ_BARYCENTRICS 18`
- L29 `#define RAY_TRACING_DEBUG_VIZ_PRIMARY_RAYS 19`
- L30 `#define RAY_TRACING_DEBUG_VIZ_WORLD_TANGENT 20`
- L31 `#define RAY_TRACING_DEBUG_VIZ_ANISOTROPY 21`
- L32 `#define RAY_TRACING_DEBUG_VIZ_INSTANCES 22`
- L33 `#define RAY_TRACING_DEBUG_VIZ_TIMING_TRAVERSAL 23`
- L34 `#define RAY_TRACING_DEBUG_VIZ_TIMING_ANY_HIT 24`
- L35 `#define RAY_TRACING_DEBUG_VIZ_TIMING_MATERIAL 25`
- L36 `#define RAY_TRACING_DEBUG_VIZ_TRIANGLES 26`
- L37 `#define RAY_TRACING_DEBUG_VIZ_CLUSTERS 27`
- L38 `#define RAY_TRACING_DEBUG_VIZ_TRAVERSAL_PRIMARY_NODE 28`
- L39 `#define RAY_TRACING_DEBUG_VIZ_TRAVERSAL_PRIMARY_CLUSTER 29`
- L40 `#define RAY_TRACING_DEBUG_VIZ_TRAVERSAL_PRIMARY_TRIANGLE 30`
- L41 `#define RAY_TRACING_DEBUG_VIZ_TRAVERSAL_PRIMARY_ALL 31`
- L42 `#define RAY_TRACING_DEBUG_VIZ_TRAVERSAL_PRIMARY_STATISTICS 32`
- L43 `#define RAY_TRACING_DEBUG_VIZ_TRAVERSAL_SECONDARY_NODE 33`
- L44 `#define RAY_TRACING_DEBUG_VIZ_TRAVERSAL_SECONDARY_CLUSTER 34`
- L45 `#define RAY_TRACING_DEBUG_VIZ_TRAVERSAL_SECONDARY_TRIANGLE 35`
- L46 `#define RAY_TRACING_DEBUG_VIZ_TRAVERSAL_SECONDARY_ALL 36`
- L47 `#define RAY_TRACING_DEBUG_VIZ_TRAVERSAL_SECONDARY_STATISTICS 37`
- L48 `#define RAY_TRACING_DEBUG_VIZ_DYNAMIC_INSTANCES 38`
- L49 `#define RAY_TRACING_DEBUG_VIZ_PROXY_TYPE 39`
- L50 `#define RAY_TRACING_DEBUG_VIZ_PICKER 40`
- L51 `#define RAY_TRACING_DEBUG_VIZ_INSTANCE_OVERLAP 41`
- L52 `#define RAY_TRACING_DEBUG_VIZ_TRIANGLE_HITCOUNT 42`
- L53 `#define RAY_TRACING_DEBUG_VIZ_HITCOUNT_PER_INSTANCE 43`
- L54 `#define RAY_TRACING_DEBUG_VIZ_LIGHT_GRID_COUNT 44`
- L55 `#define RAY_TRACING_DEBUG_VIZ_SUBSTRATE_DATA 45`
- L57 `#define RAY_TRACING_DEBUG_PICKER_DOMAIN_TRIANGLE 0`
- L58 `#define RAY_TRACING_DEBUG_PICKER_DOMAIN_INSTANCE 1`
- L59 `#define RAY_TRACING_DEBUG_PICKER_DOMAIN_SEGMENT 2`
- L60 `#define RAY_TRACING_DEBUG_PICKER_DOMAIN_FLAGS 3`
- L61 `#define RAY_TRACING_DEBUG_PICKER_DOMAIN_MASK 4`
- L64 `#define UINT_TYPE unsigned int` _[#if defined(__cplusplus)]_
- L65 `#define INT_TYPE int` _[#if defined(__cplusplus)]_
- L66 `#define INLINE_ATTR inline` _[#if defined(__cplusplus)]_
- L68 `#define UINT_TYPE uint` _[#if !(defined(__cplusplus))]_
- L69 `#define INT_TYPE int` _[#if !(defined(__cplusplus))]_
- L70 `#define INLINE_ATTR ` _[#if !(defined(__cplusplus))]_
- L8 #pragma `once`

#### Functions (3)

- L73-84 _function_ `INLINE_ATTR bool RequiresRayTracingDebugCHS(UINT_TYPE DebugVisualizationMode)`
- L86-98 _function_ `INLINE_ATTR bool IsRayTracingDebugTraversalMode(UINT_TYPE DebugVisualizationMode)`
- L100-112 _function_ `INLINE_ATTR bool RayTracingDebugModeSupportsInline(UINT_TYPE DebugVisualizationMode)`

### `Shaders/Shared/RenderCurveDefinitions.h` (Shared)

- lines: 9; parse: all-branches

#### Macros (#define, 2)

- L6 `#define RENDERCURVE_CURVE_PER_CLUSTER 64u`
- L9 `#define RENDERCURVE_PRIMITIVE_DATA_STRIDE_IN_BYTES 16`
- L3 #pragma `once`

### `Shaders/Shared/SceneCullingDefinitions.h` (Shared)

- lines: 112; parse: all-branches
- includes: L16 `HLSLTypeAliases.h` [defined(__cplusplus)], L22 `/Engine/Private/LargeWorldCoordinates.ush` [!defined(__cplusplus)]

#### Macros (#define, 8)

- L6 `#define INSTANCE_HIERARCHY_ITEM_CHUNK_COUNT_SHIFT (24u)`
- L7 `#define INSTANCE_HIERARCHY_ITEM_CHUNK_ID_MASK ((1u << INSTANCE_HIERARCHY_ITEM_CHUNK_COUNT_SHIFT) - 1u)`
- L8 `#define INSTANCE_HIERARCHY_ITEM_CHUNK_COMPRESSED_FLAG (1u << 31u)`
- L9 `#define INSTANCE_HIERARCHY_ITEM_CHUNK_COMPRESSED_PAYLOAD_MASK ((1u << 31u) - 1u)`
- L10 `#define INSTANCE_HIERARCHY_MAX_CHUNK_SIZE (64u)`
- L12 `#define INSTANCE_HIERARCHY_CELL_HEADER_OFFSET_BITS (22u)`
- L13 `#define INSTANCE_HIERARCHY_CELL_HEADER_COUNT_BITS (21u)`
- L80 `#define SIZEOF_PACKED_CHUNK_ATTRIBUTES 20u`
- L3 #pragma `once`

#### Structs / classes (8)

- L26-30 _struct_ **`UE::HLSL::FPackedCellHeader`** `struct FPackedCellHeader` — Representation in hierarchy buffer
  - L28 _member_ `uint Packed0;`
  - L29 _member_ `uint Packed1;`
- L33-40 _struct_ **`UE::HLSL::FCellHeader`** `struct FCellHeader` — Unpacked version of the struct
  - L35 _member_ `uint NumItemChunks;`
  - L36 _member_ `uint ItemChunksOffset;`
  - L37 _member_ `uint NumStaticChunks;`
  - L38 _member_ `uint NumDynamicChunks;`
  - L39 _member_ `bool bIsValid;`
- L42-47 _struct_ **`UE::HLSL::FCellBlockData`** `struct FCellBlockData`
  - L44 _member_ `FDFVector3 WorldPos;`
  - L45 _member_ `float LevelCellSize;` — Note, not the block size, but the cell size.
  - L46 _member_ `uint Pad;`
- L52-56 _struct_ **`UE::HLSL::FCellChunkDraw`** `struct FCellChunkDraw` — Represent one item of work for the hierarchical culling stage, linking a cell to either a group of views (main-pass) or a singlular view (post-pass).
  - L54 _member_ `uint ItemChunksOffset;`
  - L55 _member_ `uint ViewGroupId;`
- L63-67 _struct_ **`UE::HLSL::FViewDrawGroup`** `struct FViewDrawGroup` — Represents a group of views, e.g., for a clipmap or point light, or anything else really that share the same broad-phase culling result. Wrt mip-views, there is no explicit handling in the hierarchical culling stage, as they are expected to come in a compact range (post view compaction) A view group should typically share view flags, might want/need to make assumptions around that.
  - L65 _member_ `uint FirstView;`
  - L66 _member_ `uint NumViews;`
- L72-77 _struct_ **`UE::HLSL::FInstanceCullingGroupWork`** `struct FInstanceCullingGroupWork` — Info for one instance culling workgroup (64 threads). TODO: Pack/unpack into fewer bits? TODO: Move to some nanite specific header probably.
  - L74 _member_ `uint ViewGroupId;`
  - L75 _member_ `uint PackedItemChunkDesc;`
  - L76 _member_ `uint ActiveViewMask;` — Up to 32 active views in the group (NOTE: this may overflow for example if all mip levels were mapped at the same time on a point light, 48 mips)
- L83-88 _struct_ **`UE::HLSL::FPackedChunkAttributes`** `struct FPackedChunkAttributes`
  - L85 _member_ `uint2 Aabb;`
  - L86 _member_ `float2 InstanceDrawDistanceMinMaxSquared;`
  - L87 _member_ `float MinAnimationMinScreenSize;`
- L92-97 _struct_ **`UE::HLSL::FOccludedChunkDraw`** `struct FOccludedChunkDraw`
  - L94 _member_ `uint ViewGroupId;`
  - L95 _member_ `uint OccludedViewMask;`
  - L96 _member_ `uint ChunkId;`

#### Namespaces (1)

- L18-100 _namespace_ **`UE::HLSL`** `namespace UE::HLSL` _[#if defined(__cplusplus)]_

#### typedef / using (8)

- L102 _typedef_ `using FCellHeader = UE::HLSL::FCellHeader;` _[#if defined(__cplusplus)]_
- L103 _typedef_ `using FPackedCellHeader = UE::HLSL::FPackedCellHeader;` _[#if defined(__cplusplus)]_
- L104 _typedef_ `using FCellBlockData = UE::HLSL::FCellBlockData;` _[#if defined(__cplusplus)]_
- L105 _typedef_ `using FCellChunkDraw = UE::HLSL::FCellChunkDraw;` _[#if defined(__cplusplus)]_
- L106 _typedef_ `using FViewDrawGroup = UE::HLSL::FViewDrawGroup;` _[#if defined(__cplusplus)]_
- L107 _typedef_ `using FInstanceCullingGroupWork = UE::HLSL::FInstanceCullingGroupWork;` _[#if defined(__cplusplus)]_
- L108 _typedef_ `using FPackedChunkAttributes = UE::HLSL::FPackedChunkAttributes;` _[#if defined(__cplusplus)]_
- L109 _typedef_ `using FOccludedChunkDraw = UE::HLSL::FOccludedChunkDraw;` _[#if defined(__cplusplus)]_

### `Shaders/Shared/SceneDefinitions.h` (Shared)

- lines: 121; parse: all-branches

#### Macros (#define, 78)

- L9 `#define ENABLE_SCENE_DATA_DX11_UB_ERROR_WORKAROUND 1`
- L12 `#define VF_TREAT_INSTANCE_ID_OFFSET_AS_PRIMITIVE_ID_FLAG (1U << 31U)`
- L14 `#define PRIMITIVE_ID_NUM_BITS (20u)`
- L15 `#define INSTANCE_ID_NUM_BITS (24u)`
- L16 `#define INSTANCE_SCENE_DATA_FLAGS_NUM_BITS (12u)`
- L17 `#define INSTANCE_RELATIVE_ID_NUM_BITS (24u)`
- L18 `#define INSTANCE_CUSTOM_DATA_COUNT_NUM_BITS (8u)`
- L19 `#define LIGHT_ID_NUM_BITS (23u)`
- L21 `#define MAX_PRIMITIVE_ID (1U << PRIMITIVE_ID_NUM_BITS)`
- L22 `#define MAX_INSTANCE_ID (1U << INSTANCE_ID_NUM_BITS)`
- L23 `#define MAX_LIGHT_ID (1U << LIGHT_ID_NUM_BITS)`
- L25 `#define PRIMITIVE_ID_MASK ((1u << PRIMITIVE_ID_NUM_BITS) - 1u)`
- L26 `#define INSTANCE_ID_MASK ((1u << INSTANCE_ID_NUM_BITS) - 1u)`
- L27 `#define INSTANCE_RELATIVE_ID_MASK ((1u << INSTANCE_RELATIVE_ID_NUM_BITS) - 1u)`
- L28 `#define LIGHT_ID_MASK ((1u << LIGHT_ID_NUM_BITS) - 1u)`
- L30 `#define INVALID_PRIMITIVE_ID PRIMITIVE_ID_MASK`
- L33 `#define PRIMITIVE_SCENE_DATA_FLAG_CAST_SHADOWS 0x1`
- L34 `#define PRIMITIVE_SCENE_DATA_FLAG_USE_SINGLE_SAMPLE_SHADOW_SL 0x2`
- L35 `#define PRIMITIVE_SCENE_DATA_FLAG_USE_VOLUMETRIC_LM_SHADOW_SL 0x4`
- L36 `#define PRIMITIVE_SCENE_DATA_FLAG_DECAL_RECEIVER 0x8`
- L37 `#define PRIMITIVE_SCENE_DATA_FLAG_UNUSED_1 0x10`
- L38 `#define PRIMITIVE_SCENE_DATA_FLAG_OUTPUT_VELOCITY 0x20`
- L39 `#define PRIMITIVE_SCENE_DATA_FLAG_DETERMINANT_SIGN 0x40`
- L40 `#define PRIMITIVE_SCENE_DATA_FLAG_HAS_RAY_TRACING_REPRESENTATION 0x80`
- L41 `#define PRIMITIVE_SCENE_DATA_FLAG_HAS_CAPSULE_REPRESENTATION 0x100`
- L42 `#define PRIMITIVE_SCENE_DATA_FLAG_HAS_CAST_CONTACT_SHADOW 0x200`
- L43 `#define PRIMITIVE_SCENE_DATA_FLAG_HAS_PRIMITIVE_CUSTOM_DATA 0x400`
- L44 `#define PRIMITIVE_SCENE_DATA_FLAG_LIGHTING_CHANNEL_0 0x800`
- L45 `#define PRIMITIVE_SCENE_DATA_FLAG_LIGHTING_CHANNEL_1 0x1000`
- L46 `#define PRIMITIVE_SCENE_DATA_FLAG_LIGHTING_CHANNEL_2 0x2000`
- L47 `#define PRIMITIVE_SCENE_DATA_FLAG_HAS_INSTANCE_LOCAL_BOUNDS 0x4000`
- L48 `#define PRIMITIVE_SCENE_DATA_FLAG_EVALUATE_WORLD_POSITION_OFFSET 0x8000`
- L49 `#define PRIMITIVE_SCENE_DATA_FLAG_UNUSED_2 0x10000`
- L50 `#define PRIMITIVE_SCENE_DATA_FLAG_INSTANCE_DRAW_DISTANCE_CULL 0x20000`
- L51 `#define PRIMITIVE_SCENE_DATA_FLAG_WPO_DISABLE_DISTANCE 0x40000`
- L52 `#define PRIMITIVE_SCENE_DATA_FLAG_HAS_ALWAYS_EVALUATE_WPO_MATERIALS 0x80000`
- L53 `#define PRIMITIVE_SCENE_DATA_FLAG_UNUSED_3 0x100000`
- L54 `#define PRIMITIVE_SCENE_DATA_FLAG_DISABLE_MATERIAL_INVALIDATIONS 0x200000`
- L55 `#define PRIMITIVE_SCENE_DATA_FLAG_HOLDOUT 0x400000`
- L56 `#define PRIMITIVE_SCENE_DATA_FLAG_SPLINE_MESH 0x800000`
- L57 `#define PRIMITIVE_SCENE_DATA_FLAG_SKINNED_MESH 0x1000000`
- L58 `#define PRIMITIVE_SCENE_DATA_FLAG_INSTANCE_CULLING_OCCLUSION_QUERIES 0x2000000`
- L59 `#define PRIMITIVE_SCENE_DATA_FLAG_HAS_PIXEL_ANIMATION 0x4000000`
- L60 `#define PRIMITIVE_SCENE_DATA_FLAG_RAYTRACING_FAR_FIELD 0x8000000`
- L61 `#define PRIMITIVE_SCENE_DATA_FLAG_RAYTRACING_HAS_GROUPID 0x10000000`
- L62 `#define PRIMITIVE_SCENE_DATA_FLAG_PER_CLUSTER_DISPLACEMENT_FALLBACK_RASTER 0x20000000`
- L63 `#define PRIMITIVE_SCENE_DATA_FLAG_IS_FIRST_PERSON 0x40000000`
- L67 `#define PRIMITIVE_VISIBILITY_FLAG_FORCE_HIDDEN 0x1`
- L68 `#define PRIMITIVE_VISIBILITY_FLAG_CAST_HIDDEN_SHADOW 0x2`
- L69 `#define PRIMITIVE_VISIBILITY_FLAG_VISIBLE_IN_GAME 0x4`
- L70 `#define PRIMITIVE_VISIBILITY_FLAG_VISIBLE_IN_EDITOR 0x8`
- L71 `#define PRIMITIVE_VISIBILITY_FLAG_VISIBLE_IN_MAIN_PASS 0x10`
- L72 `#define PRIMITIVE_VISIBILITY_FLAG_VISIBLE_IN_REFLECTION_CAPTURES 0x20`
- L73 `#define PRIMITIVE_VISIBILITY_FLAG_VISIBLE_IN_REAL_TIME_SKY_CAPTURES 0x40`
- L74 `#define PRIMITIVE_VISIBILITY_FLAG_VISIBLE_IN_RAY_TRACING 0x80`
- L75 `#define PRIMITIVE_VISIBILITY_FLAG_VISIBLE_IN_SCENE_CAPTURE_ONLY 0x100`
- L76 `#define PRIMITIVE_VISIBILITY_FLAG_HIDDEN_IN_SCENE_CAPTURE 0x200`
- L77 `#define PRIMITIVE_VISIBILITY_FLAG_VISIBLE_IN_LUMEN_SCENE 0x400`
- L81 `#define SUPPORT_REVERSE_CULLING_IN_NANITE 0`
- L84 `#define PRIMITIVE_SCENE_DATA_FLAG_REVERSE_CULLING NOTE: Out of flags` _[#if SUPPORT_REVERSE_CULLING_IN_NANITE]_
- L87 `#define PRIMITIVE_SCENE_DATA_STRIDE 44`
- L90 `#define PRIMITIVE_SCENE_DATA_MAX_PAYLOAD_EXTENSION_SIZE 255`
- L93 `#define INSTANCE_SCENE_DATA_FLAG_DETERMINANT_SIGN 0x1`
- L94 `#define INSTANCE_SCENE_DATA_FLAG_HAS_RANDOM 0x2`
- L95 `#define INSTANCE_SCENE_DATA_FLAG_HAS_CUSTOM_DATA 0x4`
- L96 `#define INSTANCE_SCENE_DATA_FLAG_HAS_DYNAMIC_DATA 0x8`
- L97 `#define INSTANCE_SCENE_DATA_FLAG_HAS_SKINNING_DATA 0x10`
- L98 `#define INSTANCE_SCENE_DATA_FLAG_HAS_LIGHTSHADOW_UV_BIAS 0x20`
- L99 `#define INSTANCE_SCENE_DATA_FLAG_HAS_HIERARCHY_OFFSET 0x40`
- L100 `#define INSTANCE_SCENE_DATA_FLAG_HAS_LOCAL_BOUNDS 0x80`
- L101 `#define INSTANCE_SCENE_DATA_FLAG_HAS_PAYLOAD_EXTENSION 0x100`
- L102 `#define INSTANCE_SCENE_DATA_FLAG_HAS_EDITOR_DATA 0x200`
- L103 `#define INSTANCE_SCENE_DATA_FLAG_HIDDEN 0x400`
- L105 `#define INSTANCE_SCENE_DATA_FLAG_PAYLOAD_MASK ( INSTANCE_SCENE_DATA_FLAG_HAS_RANDOM \| INSTANCE_SCENE_DATA_FLAG_HAS_CUSTOM_DATA \| INSTANCE_SCENE_DATA_FLAG_HAS_DYNAMIC_DATA \| INSTANCE_SCENE_DATA_FLAG_HAS_SKINNING_DATA \| INSTANCE_SCENE_DATA_FLAG_HAS ...` (11 lines)
- L118 `#define BATCHED_PRIMITIVE_DATA_STRIDE 512u`
- L119 `#define BATCHED_INSTANCE_DATA_STRIDE 256u`
- L120 `#define BATCHED_PRIMITIVE_DATA_STRIDE_FLOAT4 (BATCHED_PRIMITIVE_DATA_STRIDE/16u)`
- L121 `#define BATCHED_INSTANCE_DATA_STRIDE_FLOAT4 (BATCHED_INSTANCE_DATA_STRIDE/16u)`
- L7 #pragma `once`

### `Shaders/Shared/SingleLayerWaterDefinitions.h` (Shared)

- lines: 10; parse: all-branches

#### Macros (#define, 1)

- L10 `#define SLW_TILE_SIZE_XY (8U)`
- L8 #pragma `once`

### `Shaders/Shared/SkinningDefinitions.h` (Shared)

- lines: 299; parse: all-branches
- includes: L20 `HLSLTypeAliases.h` [defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021 && defined(__cplusplus)], L229 `Matrix3x4.h` [defined(__cplusplus)]

#### Macros (#define, 55)

- L5 `#define USE_COMPRESSED_BONE_TRANSFORM 0`
- L7 `#define GPUSKIN_TRANSFORM_STORAGE_BONE_MAP 0`
- L8 `#define GPUSKIN_TRANSFORM_STORAGE_DIRECT 1`
- L11 `#define SKINNING_STATIC_ASSERT(bCondition, Message) static_assert(bCondition, Message)` _[#if defined(__cplusplus)]_
- L13 `#define SKINNING_STATIC_ASSERT(bCondition, Message) ` _[#if !(defined(__cplusplus))]_
- L48 `#define MAX_ANIM_SEQUENCE_LAYERS 4` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
- L50 `#define SKINNING_LAYER_MODE_OVERRIDE 0` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
- L51 `#define SKINNING_LAYER_MODE_ADDITIVE 1` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
- L53 `#define SKINNING_MAX_KEY_INDEX 65535` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
- L55 `#define SKINNING_LAYER_MODE_BITS_PER_LAYER 2` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
- L56 `#define SKINNING_LAYER_MODE_MASK_PER_LAYER ((1 << SKINNING_LAYER_MODE_BITS_PER_LAYER) - 1)` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
- L58 `#define SKINNING_INVALID_BONE_MASK_OFFSET 0x3FFFFFF` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
- L60 `#define SKINNING_MAX_BONES_PER_GROUP 1024` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
- L61 `#define SKINNING_MAX_BONES_PER_GROUP_MESHSPACE 256` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
- L141 `#define ANIM_BANK_FLAG_NONE 0x0` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
- L142 `#define ANIM_BANK_FLAG_LOOPING 0x1` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
- L143 `#define ANIM_BANK_FLAG_AUTOSTART 0x2` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
- L150 `#define UINT_TYPE unsigned int` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021 && defined(__cplusplus)]_
- L152 `#define UINT_TYPE uint` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021 && !(defined(__cplusplus))]_
- L156 `#define ANIM_BANK_SAMPLE_RATE 30.0f` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
- L158 `#define SKINNING_BUFFER_HIERARCHY_OFFSET_BITS 22` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
- L159 `#define SKINNING_BUFFER_HIERARCHY_OFFSET_INVALID ((1u << SKINNING_BUFFER_HIERARCHY_OFFSET_BITS) - 1u)` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
- L160 `#define SKINNING_BUFFER_HIERARCHY_OFFSET_MAX SKINNING_BUFFER_HIERARCHY_OFFSET_INVALID - 1` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
- L162 `#define SKINNING_BUFFER_TRANSFORM_OFFSET_BITS 22` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
- L163 `#define SKINNING_BUFFER_TRANSFORM_OFFSET_INVALID ((1u << SKINNING_BUFFER_TRANSFORM_OFFSET_BITS) - 1u)` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
- L164 `#define SKINNING_BUFFER_TRANSFORM_OFFSET_MAX SKINNING_BUFFER_TRANSFORM_OFFSET_INVALID - 1` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
- L166 `#define SKINNING_BUFFER_OBJECT_SPACE_OFFSET_BITS 22` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
- L167 `#define SKINNING_BUFFER_OBJECT_SPACE_OFFSET_INVALID ((1u << SKINNING_BUFFER_OBJECT_SPACE_OFFSET_BITS) - 1u)` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
- L168 `#define SKINNING_BUFFER_OBJECT_SPACE_OFFSET_MAX SKINNING_BUFFER_OBJECT_SPACE_OFFSET_INVALID - 1` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
- L170 `#define SKINNING_BUFFER_INFLUENCE_BITS 5` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
- L171 `#define SKINNING_BUFFER_INFLUENCE_MAX (1 << SKINNING_BUFFER_INFLUENCE_BITS)` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
- L195 `#define FCompressedBoneTransform FMatrix3x4` _[#if !(USE_COMPRESSED_BONE_TRANSFORM) && defined(__cplusplus)]_
- L197 `#define FCompressedBoneTransform float3x4` _[#if !(USE_COMPRESSED_BONE_TRANSFORM) && !(defined(__cplusplus))]_
- L203 `#define COMPRESSED_BONE_TRANSFORM_PIXEL_FORMAT PF_Unknown` _[#if USE_COMPRESSED_BONE_TRANSFORM]_
- L204 `#define FPersistentCompressedBoneTransformBuffer TPersistentByteAddressBuffer<FCompressedBoneTransform>` _[#if USE_COMPRESSED_BONE_TRANSFORM]_
- L205 `#define FCompressedBoneTransformBufferScatterUploader TByteAddressBufferScatterUploader<FCompressedBoneTransform>` _[#if USE_COMPRESSED_BONE_TRANSFORM]_
- L206 `#define FCompressedBoneTransformBuffer ByteAddressBuffer` _[#if USE_COMPRESSED_BONE_TRANSFORM]_
- L207 `#define FCompressedBoneTransformRWBuffer RWByteAddressBuffer` _[#if USE_COMPRESSED_BONE_TRANSFORM]_
- L209 `#define SHADER_PARAMETER_COMPRESSED_BONE_TRANSFORM_SRV(Name) SHADER_PARAMETER_SRV(ByteAddressBuffer, Name)` _[#if USE_COMPRESSED_BONE_TRANSFORM]_
- L210 `#define SHADER_PARAMETER_RDG_COMPRESSED_BONE_TRANSFORM_SRV(Name) SHADER_PARAMETER_RDG_BUFFER_SRV(ByteAddressBuffer, Name)` _[#if USE_COMPRESSED_BONE_TRANSFORM]_
- L211 `#define SHADER_PARAMETER_RDG_COMPRESSED_BONE_TRANSFORM_UAV(Name) SHADER_PARAMETER_RDG_BUFFER_UAV(RWByteAddressBuffer, Name)` _[#if USE_COMPRESSED_BONE_TRANSFORM]_
- L215 `#define COMPRESSED_BONE_TRANSFORM_PIXEL_FORMAT PF_A32B32G32R32F` _[#if !(USE_COMPRESSED_BONE_TRANSFORM)]_
- L216 `#define FPersistentCompressedBoneTransformBuffer TPersistentFloat4Buffer<FCompressedBoneTransform>` _[#if !(USE_COMPRESSED_BONE_TRANSFORM)]_
- L217 `#define FCompressedBoneTransformBufferScatterUploader TFloat4BufferScatterUploader<FCompressedBoneTransform>` _[#if !(USE_COMPRESSED_BONE_TRANSFORM)]_
- L218 `#define FCompressedBoneTransformBuffer Buffer<float4>` _[#if !(USE_COMPRESSED_BONE_TRANSFORM)]_
- L219 `#define FCompressedBoneTransformRWBuffer RWBuffer<float4>` _[#if !(USE_COMPRESSED_BONE_TRANSFORM)]_
- L221 `#define SHADER_PARAMETER_COMPRESSED_BONE_TRANSFORM_SRV(Name) SHADER_PARAMETER_SRV(Buffer<float4>, Name)` _[#if !(USE_COMPRESSED_BONE_TRANSFORM)]_
- L222 `#define SHADER_PARAMETER_RDG_COMPRESSED_BONE_TRANSFORM_SRV(Name) SHADER_PARAMETER_RDG_BUFFER_SRV(Buffer<float4>, Name)` _[#if !(USE_COMPRESSED_BONE_TRANSFORM)]_
- L223 `#define SHADER_PARAMETER_RDG_COMPRESSED_BONE_TRANSFORM_UAV(Name) SHADER_PARAMETER_RDG_BUFFER_UAV(RWBuffer<float4>, Name)` _[#if !(USE_COMPRESSED_BONE_TRANSFORM)]_
- L231 `#define REF_POSE_TRANSFORM_PROVIDER_GUID 0x665207E7, 0x449A4FB1, 0xA298F7AD, 0x8F989B11` _[#if defined(__cplusplus)]_
- L232 `#define ANIM_BANK_GPU_TRANSFORM_PROVIDER_GUID 0xA5C0027A, 0x8F884C7C, 0x9312F138, 0x71A9300F` _[#if defined(__cplusplus)]_
- L233 `#define ANIM_BANK_CPU_TRANSFORM_PROVIDER_GUID 0xE7D6173D, 0x246F431A, 0x912D384E, 0x156C0D2C` _[#if defined(__cplusplus)]_
- L234 `#define ANIM_SEQUENCE_GPU_TRANSFORM_PROVIDER_GUID 0x5CFA81C1, 0xF3D8486B, 0x81FF23D3, 0x72EB523F` _[#if defined(__cplusplus)]_
- L235 `#define ANIM_RUNTIME_TRANSFORM_PROVIDER_GUID 0xF1508490, 0xFCC24BB9, 0xA9F277B3, 0x1AF766F0` _[#if defined(__cplusplus)]_
- L236 `#define ANIM_MESH_OBJECT_TRANSFORM_PROVIDER_GUID 0x1073C0C5, 0xB981F6FD, 0xBF41B1C2, 0xC4BA0C50` _[#if defined(__cplusplus)]_
- L3 #pragma `once`

#### Structs / classes (8)

- L26-38 _struct_ **`UE::HLSL::FAnimBankBlockHeader`** `struct FAnimBankBlockHeader` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
  - L28 _member_ `float Time;` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
  - L29 _member_ `uint BoneMapOffset;` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
  - L30 _member_ `uint SequenceTransformIndex;` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
  - L31 _member_ `uint MappingTransformIndex;` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
  - L32 _member_ `uint OutputTransformIndex;` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
  - L33 _member_ `uint FrameCount;` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
  - L34 _member_ `uint BoneCount : 16;` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
  - L35 _member_ `uint OutputTransformCopyIndexOffset : 16;` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
  - L36 _member_ `uint BlockLocalIndex : 16;` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
  - L37 _member_ `uint BlockTransformCount : 16;` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
- L40-45 _struct_ **`UE::HLSL::FBoneRetargetingData`** `struct FBoneRetargetingData` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
  - L42 _member_ `uint AnimBoneIndex : 16;` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
  - L43 _member_ `uint RetargetMode : 15;` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
  - L44 _member_ `uint bRequiresRefPoseRetarget : 1;` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
- L64-74 _struct_ **`UE::HLSL::FEvaluateLayerHeader`** `struct FEvaluateLayerHeader` — Per-layer header. One entry per layer per track. _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
  - L66 _member_ `uint BoneMapBufferOffset;` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
  - L67 _member_ `uint DstTransformBufferOffset1;` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
  - L68 _member_ `uint DstTransformBufferOffset2;` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
  - L69 _member_ `uint SampleDataOffset;` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
  - L70 _member_ `float BlendWeight;` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
  - L71 _member_ `float LayerWeight;` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
  - L72 _member_ `uint BoneMaskAndSampleCounts;` — [0:25] BoneMask, [26:28] NumSourceSamples, [29:31] NumTargetSamples _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
  - L73 _member_ `uint InvGlobalRefPoseTransformBufferOffset;` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
- L78-88 _struct_ **`UE::HLSL::FSamplePoseData`** `struct FSamplePoseData` — Per-sample pose evaluation data. Tightly packed per track. _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
  - L80 _member_ `float Alpha;` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
  - L81 _member_ `uint KeyIndex0;` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
  - L82 _member_ `uint KeyIndex1;` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
  - L83 _member_ `uint SequenceTransformBufferOffset;` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
  - L84 _member_ `uint RetargetingTransformBufferOffset;` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
  - L85 _member_ `uint RetargetingDataBufferOffset;` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
  - L86 _member_ `uint NumAnimBones;` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
  - L87 _member_ `float Weight;` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
- L91-95 _struct_ **`UE::HLSL::FBoneHierarchyData`** `struct FBoneHierarchyData` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
  - L93 _member_ `uint ParentIndex : 16;` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
  - L94 _member_ `uint TransformIndex : 16;` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
- L110-122 _struct_ **`UE::HLSL::FResolveAttachmentBlockHeader`** `struct FResolveAttachmentBlockHeader` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
  - L112 _member_ `uint ParentTransformBufferOffset;` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
  - L113 _member_ `uint ParentMaxTransformCountAndBoneIndex;` — bits [15:0] = MaxTransformCount, [31:16] = BoneIndex _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
  - L114 _member_ `uint ParentCurrentTransformSlotAndInstanceId;` — bits [7:0] = CurrentTransformSlot, [31:8] = ParentInstanceId _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
  - L115 _member_ `uint ChildInstanceId;` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
  - L116 _member_ `uint ChildPrimitiveId;` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
  - L117 _member_ `float LocalOffsetTranslation[3];` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
  - L118 _member_ `float LocalOffsetRotation[4];` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
  - L119 _member_ `float BoneRefPoseRow0[4];` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
  - L120 _member_ `float BoneRefPoseRow1[4];` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
  - L121 _member_ `float BoneRefPoseRow2[4];` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
- L173-184 _struct_ **`FSkinningHeader`** `struct FSkinningHeader` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
  - L175 _member_ `UINT_TYPE HierarchyBufferOffset : SKINNING_BUFFER_HIERARCHY_OFFSET_BITS;` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
  - L176 _member_ `UINT_TYPE TransformBufferOffset : SKINNING_BUFFER_TRANSFORM_OFFSET_BITS;` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
  - L177 _member_ `UINT_TYPE ObjectSpaceBufferOffset : SKINNING_BUFFER_OBJECT_SPACE_OFFSET_BITS;` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
  - L178 _member_ `UINT_TYPE MaxTransformCount : 16;` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
  - L179 _member_ `UINT_TYPE CurrentTransformSlot : 1;` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
  - L180 _member_ `UINT_TYPE MaxInfluenceCount : SKINNING_BUFFER_INFLUENCE_BITS;` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
  - L181 _member_ `UINT_TYPE bHasScale : 1;` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
  - L182 _member_ `UINT_TYPE bIsRefPose : 1;` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
  - L183 _member_ `UINT_TYPE Unused : 6;` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
- L189-192 _struct_ **`FCompressedBoneTransform`** `struct FCompressedBoneTransform` _[#if USE_COMPRESSED_BONE_TRANSFORM]_
  - L191 _member_ `UINT_TYPE Data[8];` _[#if USE_COMPRESSED_BONE_TRANSFORM]_

#### Namespaces (1)

- L22-146 _namespace_ **`UE::HLSL`** `namespace UE::HLSL` _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021 && defined(__cplusplus)]_

#### Functions (21)

- L99-102 _function_ `inline void SetBoneMaskAndSampleCounts(FEvaluateLayerHeader& H, uint32 BoneMask, uint32 NumSource, uint32 NumTarget)` (scope `UE::HLSL`) _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021 && defined(__cplusplus)]_
- L104 _function_ `uint GetBoneMaskOffset(FEvaluateLayerHeader H)` (scope `UE::HLSL`) _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021 && !(defined(__cplusplus))]_
- L105 _function_ `uint GetNumSourceSamples(FEvaluateLayerHeader H)` (scope `UE::HLSL`) _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021 && !(defined(__cplusplus))]_
- L106 _function_ `uint GetNumTargetSamples(FEvaluateLayerHeader H)` (scope `UE::HLSL`) _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021 && !(defined(__cplusplus))]_
- L107 _function_ `bool HasBoneMask(FEvaluateLayerHeader H)` (scope `UE::HLSL`) _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021 && !(defined(__cplusplus))]_
- L126 _function_ `inline void SetMaxTransformCount(FResolveAttachmentBlockHeader& H, uint32 V)` (scope `UE::HLSL`) _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021 && defined(__cplusplus)]_
- L127 _function_ `inline void SetBoneIndex(FResolveAttachmentBlockHeader& H, uint32 V)` (scope `UE::HLSL`) _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021 && defined(__cplusplus)]_
- L128 _function_ `inline void SetCurrentTransformSlot(FResolveAttachmentBlockHeader& H, uint32 V)` (scope `UE::HLSL`) _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021 && defined(__cplusplus)]_
- L129 _function_ `inline void SetParentInstanceId(FResolveAttachmentBlockHeader& H, uint32 V)` (scope `UE::HLSL`) _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021 && defined(__cplusplus)]_
- L130 _function_ `inline uint32 GetMaxTransformCount(const FResolveAttachmentBlockHeader& H)` (scope `UE::HLSL`) _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021 && defined(__cplusplus)]_
- L131 _function_ `inline uint32 GetBoneIndex(const FResolveAttachmentBlockHeader& H)` (scope `UE::HLSL`) _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021 && defined(__cplusplus)]_
- L132 _function_ `inline uint32 GetCurrentTransformSlot(const FResolveAttachmentBlockHeader& H)` (scope `UE::HLSL`) _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021 && defined(__cplusplus)]_
- L133 _function_ `inline uint32 GetParentInstanceId(const FResolveAttachmentBlockHeader& H)` (scope `UE::HLSL`) _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021 && defined(__cplusplus)]_
- L135 _function_ `uint GetMaxTransformCount(FResolveAttachmentBlockHeader H)` (scope `UE::HLSL`) _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021 && !(defined(__cplusplus))]_
- L136 _function_ `uint GetBoneIndex(FResolveAttachmentBlockHeader H)` (scope `UE::HLSL`) _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021 && !(defined(__cplusplus))]_
- L137 _function_ `uint GetCurrentTransformSlot(FResolveAttachmentBlockHeader H)` (scope `UE::HLSL`) _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021 && !(defined(__cplusplus))]_
- L138 _function_ `uint GetParentInstanceId(FResolveAttachmentBlockHeader H)` (scope `UE::HLSL`) _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021 && !(defined(__cplusplus))]_
- L238-256 _function_ `inline void StoreCompressedBoneTransform(FCompressedBoneTransform& CompressedTransform, const FMatrix44f& Transform)` _[#if defined(__cplusplus)]_
- L258-261 _function_ `inline void StoreCompressedBoneTransform(FCompressedBoneTransform* CompressedTransform, const FMatrix44f& Transform)` _[#if defined(__cplusplus)]_
- L263-280 _function_ `inline void StoreCompressedBoneTransform(FCompressedBoneTransform& CompressedTransform, const FMatrix3x4& Transform)` _[#if defined(__cplusplus)]_
- L282-296 _function_ `inline void SetCompressedBoneTransformIdentity(FCompressedBoneTransform& Transform)` _[#if defined(__cplusplus)]_

#### Top-level macro invocations (5)

- L46 _macro_call_ `SKINNING_STATIC_ASSERT(sizeof(FBoneRetargetingData) == 4, "FBoneRetargetingData must be 4 bytes")` (scope `UE::HLSL`) _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
- L75 _macro_call_ `SKINNING_STATIC_ASSERT(sizeof(FEvaluateLayerHeader) == 32, "FEvaluateLayerHeader must be 32 bytes")` (scope `UE::HLSL`) _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
- L89 _macro_call_ `SKINNING_STATIC_ASSERT(sizeof(FSamplePoseData) == 32, "FSamplePoseData must be 32 bytes")` (scope `UE::HLSL`) _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
- L96 _macro_call_ `SKINNING_STATIC_ASSERT(sizeof(FBoneHierarchyData) == 4, "FBoneHierarchyData must be 4 bytes")` (scope `UE::HLSL`) _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_
- L123 _macro_call_ `SKINNING_STATIC_ASSERT(sizeof(FResolveAttachmentBlockHeader) == 96, "FResolveAttachmentBlockHeader must be 96 bytes")` (scope `UE::HLSL`) _[#if defined(__cplusplus) \|\| COMPILER_SUPPORTS_HLSL2021]_

### `Shaders/Shared/SplineMeshShaderParams.h` (Shared)

- lines: 103; parse: all-branches
- includes: L15 `HLSLTypeAliases.h` [defined(__cplusplus)], L60 `/Engine/Private/Quaternion.ush` [!defined(__cplusplus)]

#### Macros (#define, 5)

- L6 `#define SPLINE_MESH_PARAMS_FLOAT4_SIZE 7`
- L9 `#define SPLINE_MESH_TEXEL_WIDTH_BITS (6u)`
- L10 `#define SPLINE_MESH_TEXEL_WIDTH (1u << SPLINE_MESH_TEXEL_WIDTH_BITS)`
- L11 `#define SPLINE_MESH_TEXEL_WIDTH_MASK (SPLINE_MESH_TEXEL_WIDTH - 1u)`
- L12 `#define SPLINE_MESH_TEXTURE_MAX_DIMENSION (16 * 1024)`
- L3 #pragma `once`

#### Structs / classes (1)

- L28-52 _struct_ **`SplineMeshInternal::ShaderParams::HLSL::FSplineMeshShaderParams`** `struct FSplineMeshShaderParams`
  - L30 _member_ `float3 StartPos;`
  - L31 _member_ `float3 EndPos;`
  - L32 _member_ `float3 StartTangent;`
  - L33 _member_ `float3 EndTangent;`
  - L34 _member_ `float2 StartOffset;`
  - L35 _member_ `float2 EndOffset;`
  - L36 _member_ `half StartRoll;`
  - L37 _member_ `half EndRoll;`
  - L38 _member_ `half2 StartScale;`
  - L39 _member_ `half2 EndScale;`
  - L40 _member_ `float MeshZScale;`
  - L41 _member_ `float MeshZOffset;`
  - L42 _member_ `float2 MeshDeformScaleMinMax;`
  - L43 _member_ `bool bSmoothInterpRollScale;`
  - L44 _member_ `half3 SplineUpDir;`
  - L45 _member_ `half3 MeshDir;`
  - L46 _member_ `half3 MeshX;`
  - L47 _member_ `half3 MeshY;`
  - L48 _member_ `uint2 TextureCoord;`
  - L49 _member_ `half SplineDistToTexelScale;`
  - L50 _member_ `half SplineDistToTexelOffset;`
  - L51 _member_ `half NaniteClusterBoundsScale;`

#### Namespaces (1)

- L17-55 _namespace_ **`SplineMeshInternal::ShaderParams::HLSL`** `namespace SplineMeshInternal::ShaderParams::HLSL` _[#if defined(__cplusplus)]_

#### typedef / using (5)

- L22 _typedef_ `using namespace UE::HLSL;` (scope `SplineMeshInternal::ShaderParams::HLSL`) — The struct below doesn't need to be binary compatible between C++ and HLSL because of custom packing/unpacking methods. So we'll let "half" just mean float on the C++ side in this particular context. (NOTE: placed in separate namespace so as not to pollute UE::HLSL) _[#if defined(__cplusplus)]_
- L23 _typedef_ `using half = float;` (scope `SplineMeshInternal::ShaderParams::HLSL`) _[#if defined(__cplusplus)]_
- L24 _typedef_ `using half2 = float2;` (scope `SplineMeshInternal::ShaderParams::HLSL`) _[#if defined(__cplusplus)]_
- L25 _typedef_ `using half3 = float3;` (scope `SplineMeshInternal::ShaderParams::HLSL`) _[#if defined(__cplusplus)]_
- L56 _typedef_ `using FSplineMeshShaderParams = SplineMeshInternal::ShaderParams::HLSL::FSplineMeshShaderParams;` _[#if defined(__cplusplus)]_

#### Functions (1)

- L63-101 _function_ `FSplineMeshShaderParams UnpackSplineMeshParams(float4 PackedParams[SPLINE_MESH_PARAMS_FLOAT4_SIZE])` — HLSL unpack method _[#if !defined(__cplusplus)]_

### `Shaders/Shared/SubstrateDefinitions.h` (Shared)

- lines: 155; parse: all-branches

#### Macros (#define, 93)

- L16 `#define SUBSTRATE_MAX_CLOSURE_COUNT_FOR_CLOSUREOFFSET 8u`
- L17 `#define SUBSTRATE_CLOSURE_OFFSET_BIT_COUNT 4u`
- L18 `#define SUBSTRATE_CLOSURE_OFFSET_BIT_MASK 0xF`
- L21 `#define SUBSTRATE_MAX_CLOSURE_COUNT SUBSTRATE_MAX_CLOSURE_COUNT_FOR_CLOSUREOFFSET`
- L22 `#define SUBSTRATE_MAX_OPERATOR_COUNT 15`
- L25 `#define SUBSTRATE_MAX_SHAREDLOCALBASES_REGISTERS 4`
- L27 `#define SUBSTRATE_PACKED_SHAREDLOCALBASIS_STRIDE_BYTES 4`
- L31 `#define SUBSTRATE_FULLY_SIMPLIFIED_NUM_UINTS (32/4)`
- L33 `#define SUBSTRATE_BSDF_TYPE_SLAB 0`
- L34 `#define SUBSTRATE_BSDF_TYPE_VOLUMETRICFOGCLOUD 1`
- L35 `#define SUBSTRATE_BSDF_TYPE_UNLIT 2`
- L36 `#define SUBSTRATE_BSDF_TYPE_HAIR 3`
- L37 `#define SUBSTRATE_BSDF_TYPE_SINGLELAYERWATER 4`
- L38 `#define SUBSTRATE_BSDF_TYPE_EYE 5`
- L39 `#define SUBSTRATE_BSDF_TYPE_TOON 6`
- L44 `#define SUBSTRATE_TILE_SIZE 8`
- L45 `#define SUBSTRATE_TILE_SIZE_DIV_AS_SHIFT 3`
- L48 `#define SUBSTRATE_LAYER_DEFAULT_THICKNESS_CM 0.01f`
- L52 `#define SUBSTRATE_MIN_GGX_ROUGHNESS 0.02f`
- L53 `#define SUBSTRATE_MIN_FUZZ_ROUGHNESS 0.02f`
- L55 `#define SUBSTRATE_BASE_PASS_MRT_OUTPUT_COUNT 3`
- L57 `#define SUBSTRATE_SSS_DATA_UINT_COUNT 2`
- L59 `#define SUBSTRATE_OPERATOR_WEIGHT 0`
- L60 `#define SUBSTRATE_OPERATOR_VERTICAL 1`
- L61 `#define SUBSTRATE_OPERATOR_HORIZONTAL 2`
- L62 `#define SUBSTRATE_OPERATOR_ADD 3`
- L63 `#define SUBSTRATE_OPERATOR_SELECT 4`
- L64 `#define SUBSTRATE_OPERATOR_BSDF 5`
- L65 `#define SUBSTRATE_OPERATOR_BSDF_LEGACY 6`
- L68 `#define SUBSTRATE_OPERATOR_SUBUSAGE_NONE 0`
- L69 `#define SUBSTRATE_OPERATOR_SUBUSAGE_UI 1`
- L70 `#define SUBSTRATE_OPERATOR_SUBUSAGE_LIGHTFUNCTION 2`
- L71 `#define SUBSTRATE_OPERATOR_SUBUSAGE_POSTPROCESS 3`
- L72 `#define SUBSTRATE_OPERATOR_SUBUSAGE_DECAL 4`
- L75 `#define SUBSTRATE_TILE_TYPE_SIMPLE 0`
- L76 `#define SUBSTRATE_TILE_TYPE_SINGLE 1`
- L77 `#define SUBSTRATE_TILE_TYPE_COMPLEX 2`
- L78 `#define SUBSTRATE_TILE_TYPE_COMPLEX_SPECIAL 3`
- L79 `#define SUBSTRATE_TILE_TYPE_ROUGH_REFRACT 4`
- L80 `#define SUBSTRATE_TILE_TYPE_ROUGH_REFRACT_SSS_WITHOUT 5`
- L81 `#define SUBSTRATE_TILE_TYPE_DECAL_SIMPLE 6`
- L82 `#define SUBSTRATE_TILE_TYPE_DECAL_SINGLE 7`
- L83 `#define SUBSTRATE_TILE_TYPE_DECAL_COMPLEX 8`
- L84 `#define SUBSTRATE_TILE_TYPE_COUNT 9`
- L87 `#define SUBSTRATE_TILE_BITMASK_SIMPLE (1u<<SUBSTRATE_TILE_TYPE_SIMPLE)`
- L88 `#define SUBSTRATE_TILE_BITMASK_SINGLE (1u<<SUBSTRATE_TILE_TYPE_SINGLE)`
- L89 `#define SUBSTRATE_TILE_BITMASK_COMPLEX (1u<<SUBSTRATE_TILE_TYPE_COMPLEX)`
- L90 `#define SUBSTRATE_TILE_BITMASK_COMPLEXSPECIAL (1u<<SUBSTRATE_TILE_TYPE_COMPLEX_SPECIAL)`
- L91 `#define SUBSTRATE_TILE_BITMASK_ROUGH_REFRACT (1u<<SUBSTRATE_TILE_TYPE_ROUGH_REFRACT)`
- L92 `#define SUBSTRATE_TILE_BITMASK_ROUGH_REFRACT_SSS_WITHOUT (1u<<SUBSTRATE_TILE_TYPE_ROUGH_REFRACT_SSS_WITHOUT)`
- L93 `#define SUBSTRATE_TILE_BITMASK_DECAL_SIMPLE (1u<<SUBSTRATE_TILE_TYPE_DECAL_SIMPLE)`
- L94 `#define SUBSTRATE_TILE_BITMASK_DECAL_SINGLE (1u<<SUBSTRATE_TILE_TYPE_DECAL_SINGLE)`
- L95 `#define SUBSTRATE_TILE_BITMASK_DECAL_COMPLEX (1u<<SUBSTRATE_TILE_TYPE_DECAL_COMPLEX)`
- L96 `#define SUBSTRATE_TILE_BITMASK_DECAL (SUBSTRATE_TILE_BITMASK_DECAL_SIMPLE\|SUBSTRATE_TILE_BITMASK_DECAL_SINGLE\|SUBSTRATE_TILE_BITMASK_DECAL_COMPLEX)`
- L99 `#define SUBSTRATE_MATERIAL_TYPE_SIMPLE 0`
- L100 `#define SUBSTRATE_MATERIAL_TYPE_SINGLE 1`
- L101 `#define SUBSTRATE_MATERIAL_TYPE_COMPLEX 2`
- L102 `#define SUBSTRATE_MATERIAL_TYPE_COMPLEX_SPECIAL 3`
- L103 `#define SUBSTRATE_MATERIAL_TYPE_COUNT 4`
- L105 `#define SUBSTRATE_TILE_ENCODING_16BITS 0`
- L106 `#define SUBSTRATE_TILE_ENCODING_8BITS 1`
- L109 `#define SUBSTRATE_SPECULAR_PROFILE_ENTRY_LIGHT 0u`
- L110 `#define SUBSTRATE_SPECULAR_PROFILE_ENTRY_ENV 1u`
- L111 `#define SUBSTRATE_SPECULAR_PROFILE_ENTRY_COUNT 2u`
- L114 `#define GetSubstrateTileTypeDrawIndirectArgOffset_Byte(x) (x * 16)`
- L115 `#define GetSubstrateTileTypeDrawIndirectArgOffset_DWord(x) (x * 4)`
- L119 `#define GetSubstrateTileTypeDispatchIndirectArgOffset_Byte(x) (x * sizeof(FRHIDispatchIndirectParameters))` _[#if defined(__cplusplus)]_
- L120 `#define GetSubstrateTileTypeDispatchIndirectArgOffset_DWord(x) (x * sizeof(FRHIDispatchIndirectParameters) / sizeof(uint32))` _[#if defined(__cplusplus)]_
- L122 `#define GetSubstrateTileTypeDispatchIndirectArgOffset_Byte(x) (x * DISPATCH_INDIRECT_UINT_COUNT * 4)` _[#if !(defined(__cplusplus))]_
- L123 `#define GetSubstrateTileTypeDispatchIndirectArgOffset_DWord(x) (x * DISPATCH_INDIRECT_UINT_COUNT)` _[#if !(defined(__cplusplus))]_
- L126 `#define HEADER_MATERIALMODE_NONE 0`
- L127 `#define HEADER_MATERIALMODE_SLAB_SIMPLE 1`
- L128 `#define HEADER_MATERIALMODE_SLAB_SINGLE 2`
- L129 `#define HEADER_MATERIALMODE_SLAB_COMPLEX 3`
- L130 `#define HEADER_MATERIALMODE_SLWATER 4`
- L131 `#define HEADER_MATERIALMODE_HAIR 5`
- L132 `#define HEADER_MATERIALMODE_EYE 6`
- L136 `#define HEADER_SINGLE_OPTLEGACYMODE_BIT_COUNT 3`
- L137 `#define HEADER_SINGLE_OPTLEGACYMODE_BIT_MASK ((1u<<HEADER_SINGLE_OPTLEGACYMODE_BIT_COUNT)-1u)`
- L138 `#define SINGLE_OPTLEGACYMODE_NONE 0`
- L139 `#define SINGLE_OPTLEGACYMODE_CLEARCOAT 1`
- L140 `#define SINGLE_OPTLEGACYMODE_CLOTH 2`
- L141 `#define SINGLE_OPTLEGACYMODE_SSSWRAP 3`
- L142 `#define SINGLE_OPTLEGACYMODE_SSSPROFILE 4`
- L143 `#define SINGLE_OPTLEGACYMODE_TWO_SIDED_SSSWRAP 5`
- L147 `#define SSS_TYPE_NONE (0u)`
- L148 `#define SSS_TYPE_WRAP (1u)`
- L149 `#define SSS_TYPE_TWO_SIDED_WRAP (2u)`
- L150 `#define SSS_TYPE_DIFFUSION (3u)`
- L151 `#define SSS_TYPE_DIFFUSION_PROFILE (4u)`
- L152 `#define SSS_TYPE_SIMPLEVOLUME (5u)`
- L153 `#define SSS_TYPE_TRANSMITTANCE_SHADOW (6u)`
- L154 `#define SSS_TYPE_COUNT (7u)`
- L8 #pragma `once`; L12 #pragma `message("UESHADERMETADATA_VERSION 96CDF7E5-2EB8-4E48-8C1E-23B557A7B5BB")`

### `Shaders/Shared/SubstrateVisualizeDefinitions.h` (Shared)

- lines: 855; parse: last-branch (retry, +6 merged from all-branches pass)
- includes: L15 `/Engine/Shared/SubstrateDefinitions.h` [defined(__cplusplus) \|\| SUBSTRATE_ENABLED && !defined(__cplusplus)], L26 `SubstrateDefinitions.h` [defined(__cplusplus) \|\| SUBSTRATE_ENABLED && !(!defined(__cplusplus))], L273 `/Engine/Private/Substrate/SubstrateRead.ush` [defined(__cplusplus) \|\| SUBSTRATE_ENABLED && !defined(__cplusplus) && SUBSTRATE_MATERIALCONTAINER_IS_VIEWRESOURCE && SUBSTRATE_GBUFFER_FORMAT == 0], L274 `/Engine/Private/Substrate/SubstrateSubsurface.ush` [defined(__cplusplus) \|\| SUBSTRATE_ENABLED && !defined(__cplusplus) && SUBSTRATE_MATERIALCONTAINER_IS_VIEWRESOURCE && SUBSTRATE_GBUFFER_FORMAT == 0]

#### Macros (#define, 3)

- L20 `#define SUBSTRATE_VIS_CLOSURE_COUNT 1` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED && !defined(__cplusplus) && PS4_PROFILE \|\| FEATURE_LEVEL <= FEATURE_LEVEL_SM5]_
- L22 `#define SUBSTRATE_VIS_CLOSURE_COUNT SUBSTRATE_MAX_CLOSURE_COUNT` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED && !defined(__cplusplus) && !(PS4_PROFILE \|\| FEATURE_LEVEL <= FEATURE_LEVEL_SM5)]_
- L27 `#define SUBSTRATE_VIS_CLOSURE_COUNT SUBSTRATE_MAX_CLOSURE_COUNT` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED && !(!defined(__cplusplus))]_
- L8 #pragma `once`; L14 #pragma `message("UESHADERMETADATA_VERSION 24677C38-A71C-49D5-B60A-DFF59F57B39D")`

#### Structs / classes (5)

- L30-86 _struct_ **`FSubsterateDebugClosure`** `struct FSubsterateDebugClosure` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L32 _member_ `int Type;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L34 _member_ `int bHasWeightL;` — = BSDF_GETHASTRANSABOVE(BSDF); _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L35 _member_ `int bHasGreyWeightV;` — = BSDF_GETHASGREYWEIGHT_V(BSDF); _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L36 _member_ `int Address;` — SubstrateAddressing.CurrentIndex _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L38 _member_ `int NormalID;` — BSDF_GETSHAREDLOCALBASISID(BSDF) _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L39 _member_ `int BasisType;` — SubstrateGetSharedLocalBasisType(HEADER_GETSHAREDLOCALBASESTYPE(Header.PackedHeader), BSDF_GETSHAREDLOCALBASISID(BSDF)); _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L43 _member_ `int bIsTopLayer;` — Slabs _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L44 _member_ `int SSSType;` — BSDF_GETSSSTYPE(BSDF) != SSS_TYPE_NONE _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L45 _member_ `int bIsThin;` — BSDF_GETISTHIN(BSDF) _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L46 _member_ `float LuminanceWeightR, LuminanceWeightG, LuminanceWeightB;` — bHasGreyWeightV BSDF.LuminanceWeightV.x or rgb _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L46 _member_ `float LuminanceWeightR, LuminanceWeightG, LuminanceWeightB;` — bHasGreyWeightV BSDF.LuminanceWeightV.x or rgb _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L46 _member_ `float LuminanceWeightR, LuminanceWeightG, LuminanceWeightB;` — bHasGreyWeightV BSDF.LuminanceWeightV.x or rgb _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L47 _member_ `float TransmittanceAboveAlongNR, TransmittanceAboveAlongNG, TransmittanceAboveAlongNB;` — bHasGreyTopTrans BSDF.TransmittanceAboveAlongN.x or rgb _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L47 _member_ `float TransmittanceAboveAlongNR, TransmittanceAboveAlongNG, TransmittanceAboveAlongNB;` — bHasGreyTopTrans BSDF.TransmittanceAboveAlongN.x or rgb _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L47 _member_ `float TransmittanceAboveAlongNR, TransmittanceAboveAlongNG, TransmittanceAboveAlongNB;` — bHasGreyTopTrans BSDF.TransmittanceAboveAlongN.x or rgb _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L48 _member_ `float CoverageAboveAlongN;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L50 _member_ `float DiffuseR, DiffuseG, DiffuseB;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L50 _member_ `float DiffuseR, DiffuseG, DiffuseB;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L50 _member_ `float DiffuseR, DiffuseG, DiffuseB;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L51 _member_ `float F0R, F0G, F0B;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L51 _member_ `float F0R, F0G, F0B;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L51 _member_ `float F0R, F0G, F0B;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L52 _member_ `float Roughness;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L54 _member_ `int bHasF90;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L55 _member_ `float F90R, F90G, F90B;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L55 _member_ `float F90R, F90G, F90B;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L55 _member_ `float F90R, F90G, F90B;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L57 _member_ `int bHasAnisotropy;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L58 _member_ `float Anisotropy;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L60 _member_ `int bHasHaziness;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L61 _member_ `float HazeRoughness;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L62 _member_ `float HazeWeight;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L63 _member_ `int HazeSimpleClearCoatMode;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L64 _member_ `int HasBottomNormal;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L66 _member_ `float SSSOpacity;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L67 _member_ `float SSSMFPR, SSSMFPG, SSSMFPB;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L67 _member_ `float SSSMFPR, SSSMFPG, SSSMFPB;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L67 _member_ `float SSSMFPR, SSSMFPG, SSSMFPB;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L68 _member_ `float SSSRescaledMFPR, SSSRescaledMFPG, SSSRescaledMFPB;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L68 _member_ `float SSSRescaledMFPR, SSSRescaledMFPG, SSSRescaledMFPB;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L68 _member_ `float SSSRescaledMFPR, SSSRescaledMFPG, SSSRescaledMFPB;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L69 _member_ `float SSSPhase;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L70 _member_ `float SSSThickness;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L71 _member_ `float SSSProfileRadius;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L72 _member_ `int SSSPRofileID;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L74 _member_ `float FuzzAmount;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L75 _member_ `float FuzzColorR, FuzzColorG, FuzzColorB;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L75 _member_ `float FuzzColorR, FuzzColorG, FuzzColorB;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L75 _member_ `float FuzzColorR, FuzzColorG, FuzzColorB;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L76 _member_ `float FuzzRoughness;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L78 _member_ `float GlintValue;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L79 _member_ `float GlintUVDDXx;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L80 _member_ `float GlintUVDDXy;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L81 _member_ `float GlintUVDDYx;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L82 _member_ `float GlintUVDDYy;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L84 _member_ `int SpecProfileID;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L85 _member_ `int SpecProfileParameterization;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
- L88-115 _struct_ **`FSubstratePixelDebugData`** `struct FSubstratePixelDebugData` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L90 _member_ `int ClosureCount;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L91 _member_ `int MaterialMode;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L92 _member_ `int bIsComplexSpecialMaterial;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L93 _member_ `int OptimisedLegacyMode;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L95 _member_ `float MaterialAO;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L96 _member_ `float IndirectIrradiance;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L97 _member_ `float TopLayerRoughness;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L98 _member_ `int HasPrecShadowMask;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L99 _member_ `int HasZeroPrecShadowMask;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L100 _member_ `int DoesCastContactShadow;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L101 _member_ `int HasDynamicIndirectShadowCasterRepresentation;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L102 _member_ `int HasSubsurface;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L103 _member_ `int LocalBasesCount;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L105 _member_ `FSubsterateDebugClosure Closures[SUBSTRATE_VIS_CLOSURE_COUNT];` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L107 _member_ `int MemoryDisplayMode;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L108 _member_ `int MemorySlotA;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L109 _member_ `int MemorySlotB;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L110 _member_ `int MemorySlotC;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L111 _member_ `int MemorySSSData;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L112 _member_ `int MemoryTotal;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L114 _member_ `int GPUFrameNumber;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
- L120-139 _struct_ **`FSubstrateDebugDataSerializer`** `struct FSubstrateDebugDataSerializer` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED && !defined(__cplusplus)]_
  - L122 _member_ `int WriteIndex;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED && !defined(__cplusplus)]_
  - L124 _method_ `void Serialize(int Data)` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED && !defined(__cplusplus)]_
  - L132 _method_ `void Serialize(float Data)` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED && !defined(__cplusplus)]_
  - L143 _member_ `int ReadIndex = 0;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED && !(!defined(__cplusplus))]_
  - L144 _member_ `int* SubstratePixelDebugData = nullptr;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED && !(!defined(__cplusplus))]_
  - L146 _method_ `void Serialize(int& Data)` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED && !(!defined(__cplusplus))]_
  - L151 _method_ `void Serialize(float& Data)` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED && !(!defined(__cplusplus))]_
- L141-155 _struct_ **`FSubstrateDebugDataSerializer`** `struct FSubstrateDebugDataSerializer` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED && !(!defined(__cplusplus))]_
  - L122 _member_ `int WriteIndex;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED && !defined(__cplusplus)]_
  - L124 _method_ `void Serialize(int Data)` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED && !defined(__cplusplus)]_
  - L132 _method_ `void Serialize(float Data)` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED && !defined(__cplusplus)]_
  - L143 _member_ `int ReadIndex = 0;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED && !(!defined(__cplusplus))]_
  - L144 _member_ `int* SubstratePixelDebugData = nullptr;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED && !(!defined(__cplusplus))]_
  - L146 _method_ `void Serialize(int& Data)` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED && !(!defined(__cplusplus))]_
  - L151 _method_ `void Serialize(float& Data)` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED && !(!defined(__cplusplus))]_
- L816-819 _struct_ **`FSubstrateSystemInfoData`** `struct FSubstrateSystemInfoData` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_
  - L818 _member_ `int TileCount[SUBSTRATE_TILE_TYPE_COUNT];` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED]_

#### Global resources (textures / buffers / samplers) (1)

- L119 _resource_ `RWStructuredBuffer<int> SubstrateDebugDataUAV;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED && !defined(__cplusplus)]_

#### Global parameters (uniforms) (1)

- L118 _parameter_ `uint SubstrateDebugDataSizeInUints;` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED && !defined(__cplusplus)]_

#### Functions (9)

- L161-266 _function_ `void SerializeSubstratePixelDebugData(FSubstrateDebugDataSerializer& S, FSubstratePixelDebugData& D)` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED && !(!defined(__cplusplus))]_
- L276-331 _function_ `FSubstratePixelHeader UnpackSubstrateHeaderIn(inout FSubstrateAddressing SubstrateAddressing)` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED && !defined(__cplusplus) && SUBSTRATE_MATERIALCONTAINER_IS_VIEWRESOURCE && SUBSTRATE_GBUFFER_FORMAT == 0]_
- L333-370 _function_ `FSubstrateSubsurfaceHeader SubstrateLoadSubsurfaceHeader(inout FSubstrateAddressing SubstrateAddressing)` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED && !defined(__cplusplus) && SUBSTRATE_MATERIALCONTAINER_IS_VIEWRESOURCE && SUBSTRATE_GBUFFER_FORMAT == 0]_
- L372-384 _function_ `FSubstrateTopLayerData SubstrateUnpackTopLayerData(inout FSubstrateAddressing SubstrateAddressing)` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED && !defined(__cplusplus) && SUBSTRATE_MATERIALCONTAINER_IS_VIEWRESOURCE && SUBSTRATE_GBUFFER_FORMAT == 0]_
- L392-781 _function_ `FSubstratePixelDebugData ConvertToSerializableSubstratePixelDebugData(uint2 InCoord, FSubstrateRaytracingPayload Payload, uint GPUFrameNumber)` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED && !defined(__cplusplus) && !(SUBSTRATE_MATERIALCONTAINER_IS_VIEWRESOURCE)]_
- L786-799 _function_ `void SerializeSubstratePixelDebugDataEntry(uint2 InCoord, FSubstrateRaytracingPayload Payload, uint GPUFrameNumber)` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED && !defined(__cplusplus) && !(SUBSTRATE_MATERIALCONTAINER_IS_VIEWRESOURCE)]_
- L801-806 _function_ `void SerializeNullPixelDebugDataEntry()` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED && !defined(__cplusplus)]_
- L824-831 _function_ `void SerializeSubstrateSystemInfoDebugData(FSubstrateDebugDataSerializer& S, FSubstrateSystemInfoData& D)` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED && !(!defined(__cplusplus))]_
- L837-850 _function_ `void ConvertToSerializableSubstratePixelDebugData()` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED && !defined(__cplusplus)]_

#### Prototypes (1)

- L835 _prototype_ `uint GetTileCount(uint InType)` _[#if defined(__cplusplus) \|\| SUBSTRATE_ENABLED && !defined(__cplusplus)]_

### `Shaders/Shared/ToonProfileDefinitions.h` (Shared)

- lines: 20; parse: all-branches

#### Macros (#define, 13)

- L5 `#define TOON_PROFILE_DIFFUSE_RAMP_Y 0`
- L6 `#define TOON_PROFILE_SPECULAR_RAMP_Y 1`
- L7 `#define TOON_PROFILE_SHADOW_RAMP_Y 2`
- L8 `#define TOON_PROFILE_SPEC_IND_RAMP_Y 3`
- L9 `#define TOON_PROFILE_PARAMETERS_Y 4`
- L10 `#define TOON_PROFILE_TEXTURES_Y 5`
- L12 `#define TOON_PROFILE_EVAL_PARAMS_X 0`
- L13 `#define TOON_PROFILE_EVAL_PARAMS2_X 1`
- L14 `#define TOON_PROFILE_SHADOW_PARAMS_X 2`
- L15 `#define TOON_PROFILE_GI_PARAMS_X 3`
- L17 `#define TOON_PROFILE_TEXTURE_RAMPOFFSET_IDX 0`
- L18 `#define TOON_PROFILE_TEXTURE_SHADOWHATCHING_IDX 1`
- L19 `#define TOON_PROFILE_TEXTURE_COUNT 2`
- L3 #pragma `once`

### `Shaders/Shared/ViewDefinitions.h` (Shared)

- lines: 7; parse: all-branches

#### Macros (#define, 2)

- L5 `#define VIEW_DATA_ACCESS_SCENE_UB 0`
- L6 `#define VIEW_DATA_ACCESS_RW 1`
- L3 #pragma `once`

### `Shaders/Shared/VirtualShadowMapDefinitions.h` (Shared)

- lines: 229; parse: all-branches
- includes: L140 `HLSLTypeAliases.h` [defined(__cplusplus)], L141 `HLSLMathAliases.h` [defined(__cplusplus)]

#### Macros (#define, 98)

- L10 `#define VSM_ENABLE_VISUALIZATION (WITH_EDITOR \|\| !UE_BUILD_SHIPPING)`
- L13 `#define VSM_LOG2_PAGE_SIZE 7u`
- L14 `#define VSM_PAGE_SIZE (1u << VSM_LOG2_PAGE_SIZE)`
- L15 `#define VSM_PAGE_SIZE_MASK (VSM_PAGE_SIZE - 1u)`
- L17 `#define VSM_LOG2_LEVEL0_DIM_PAGES_XY 7u`
- L18 `#define VSM_LEVEL0_DIM_PAGES_XY (1u << VSM_LOG2_LEVEL0_DIM_PAGES_XY)`
- L19 `#define VSM_MAX_MIP_LEVELS (VSM_LOG2_LEVEL0_DIM_PAGES_XY + 1u)`
- L20 `#define VSM_VIRTUAL_MAX_RESOLUTION_XY (VSM_LEVEL0_DIM_PAGES_XY * VSM_PAGE_SIZE)`
- L21 `#define VSM_RASTER_WINDOW_PAGES (4u)`
- L24 `#define VSM_DIRTY_PAGE_FLAGS_NUM_SLICES 6`
- L27 `#define VSM_PREFILTERED_DISTANT_BORDER_SIZE 1u`
- L28 `#define VSM_PREFILTERED_DISTANT_PAGE_SIZE (VSM_PAGE_SIZE + 2u * VSM_PREFILTERED_DISTANT_BORDER_SIZE)`
- L31 `#define VSM_LOG2_RECEIVER_MASK_SIZE 3u`
- L32 `#define VSM_RECEIVER_MASK_SIZE (1u << VSM_LOG2_RECEIVER_MASK_SIZE)`
- L33 `#define VSM_RECEIVER_MASK_MASK (VSM_RECEIVER_MASK_SIZE - 1u)`
- L34 `#define VSM_RECEIVER_MASK_SUBMASK (VSM_RECEIVER_MASK_MASK >> 1u)`
- L37 `#define VSM_PAGE_TABLE_TEX2D_SIZE_X (VSM_LEVEL0_DIM_PAGES_XY)`
- L38 `#define VSM_PAGE_TABLE_TEX2D_SIZE_Y (VSM_LEVEL0_DIM_PAGES_XY + VSM_LEVEL0_DIM_PAGES_XY / 2)`
- L40 `#define VIRTUAL_SHADOW_MAP_VISUALIZE_NONE 0`
- L41 `#define VIRTUAL_SHADOW_MAP_VISUALIZE_SHADOW_FACTOR (1 << 0)`
- L42 `#define VIRTUAL_SHADOW_MAP_VISUALIZE_CLIPMAP_OR_MIP (1 << 1)`
- L43 `#define VIRTUAL_SHADOW_MAP_VISUALIZE_VIRTUAL_PAGE (1 << 2)`
- L44 `#define VIRTUAL_SHADOW_MAP_VISUALIZE_CACHED_PAGE (1 << 3)`
- L45 `#define VIRTUAL_SHADOW_MAP_VISUALIZE_SMRT_RAY_COUNT (1 << 4)`
- L46 `#define VIRTUAL_SHADOW_MAP_VISUALIZE_CLIPMAP_VIRTUAL_SPACE (1 << 5)`
- L47 `#define VIRTUAL_SHADOW_MAP_VISUALIZE_GENERAL_DEBUG (1 << 6)`
- L48 `#define VIRTUAL_SHADOW_MAP_VISUALIZE_DIRTY_PAGE (1 << 7)`
- L49 `#define VIRTUAL_SHADOW_MAP_VISUALIZE_GPU_INVALIDATED_PAGE (1 << 8)`
- L50 `#define VIRTUAL_SHADOW_MAP_VISUALIZE_MERGED_PAGE (1 << 9)`
- L51 `#define VIRTUAL_SHADOW_MAP_VISUALIZE_NANITE_OVERDRAW (1 << 10)`
- L52 `#define VIRTUAL_SHADOW_MAP_VISUALIZE_SHADOW_CASTERS (1 << 11)`
- L55 `#define VSM_PACKED_CLIP_LEVEL_BIAS 1024`
- L57 `#define VSM_PROJ_FLAG_CURRENT_DISTANT_LIGHT (1U << 0)`
- L58 `#define VSM_PROJ_FLAG_UNCACHED (1U << 1)`
- L59 `#define VSM_PROJ_FLAG_UNREFERENCED (1U << 2)`
- L60 `#define VSM_PROJ_FLAG_IS_COARSE_CLIP_LEVEL (1U << 3)`
- L61 `#define VSM_PROJ_FLAG_IS_FIRST_PERSON_SHADOW (1U << 4)`
- L62 `#define VSM_PROJ_FLAG_USE_RECEIVER_MASK (1U << 5)`
- L63 `#define VSM_PROJ_FLAG_FORCE_CACHE_DYNAMIC_COARSE (1U << 6)`
- L64 `#define VSM_PROJ_FLAG_HAS_PREFILTERED_DISTANT (1U << 7)`
- L67 `#define VSM_MAX_SINGLE_PAGE_SHADOW_MAPS (1024U * 8U)`
- L69 `#define VSM_INVALIDATION_PAYLOAD_FLAG_NONE 0`
- L70 `#define VSM_INVALIDATION_PAYLOAD_FLAG_FORCE_STATIC (1 << 0)`
- L72 `#define VSM_INVALIDATION_PAYLOAD_FLAG_BITS 8`
- L75 `#define VSM_STAT_REQUESTED_THIS_FRAME_PAGES 0`
- L76 `#define VSM_STAT_STATIC_CACHED_PAGES 1`
- L77 `#define VSM_STAT_STATIC_INVALIDATED_PAGES 2`
- L78 `#define VSM_STAT_DYNAMIC_CACHED_PAGES 3`
- L79 `#define VSM_STAT_DYNAMIC_INVALIDATED_PAGES 4`
- L80 `#define VSM_STAT_EMPTY_PAGES 5`
- L81 `#define VSM_STAT_NON_NANITE_INSTANCES_TOTAL 6`
- L82 `#define VSM_STAT_NON_NANITE_INSTANCES_DRAWN 7`
- L83 `#define VSM_STAT_NON_NANITE_INSTANCES_HZB_CULLED 8`
- L84 `#define VSM_STAT_NON_NANITE_INSTANCES_PAGE_MASK_CULLED 9`
- L85 `#define VSM_STAT_NON_NANITE_INSTANCES_EMPTY_RECT_CULLED 10`
- L86 `#define VSM_STAT_NON_NANITE_INSTANCES_FRUSTUM_CULLED 11`
- L87 `#define VSM_STAT_NUM_PAGES_TO_MERGE 12`
- L88 `#define VSM_STAT_NUM_PAGES_TO_CLEAR 13`
- L89 `#define VSM_STAT_NUM_HZB_PAGES_BUILT 14`
- L90 `#define VSM_STAT_ALLOCATED_NEW 15`
- L91 `#define VSM_STAT_NANITE_CLUSTERS_HW 16`
- L92 `#define VSM_STAT_NANITE_CLUSTERS_SW 17`
- L93 `#define VSM_STAT_NANITE_TRIANGLES 18`
- L94 `#define VSM_STAT_NANITE_INSTANCES_MAIN 19`
- L95 `#define VSM_STAT_NANITE_INSTANCES_POST 20`
- L96 `#define VSM_STAT_WPO_CONSIDERED_PAGES 21`
- L97 `#define VSM_STAT_OVERFLOW_FLAGS 22`
- L98 `#define VSM_STAT_PREFILTERED_DISTANT_PAGES 23`
- L99 `#define VSM_STAT_TMP_2 24`
- L100 `#define VSM_STAT_TMP_3 25`
- L101 `#define VSM_STAT_NUM 26`
- L103 `#define VSM_STAT_OVERFLOW_FLAG_MARKING_JOB_QUEUE (1<<0)`
- L104 `#define VSM_STAT_OVERFLOW_FLAG_OPP_MAX_LIGHTS (1<<1)`
- L105 `#define VSM_STAT_OVERFLOW_FLAG_PAGE_POOL (1<<2)`
- L106 `#define VSM_STAT_OVERFLOW_FLAG_VISIBLE_INSTANCES (1<<3)`
- L107 `#define VSM_STAT_OVERFLOW_FLAG_NUM 4`
- L109 `#define VSM_STATUS_MSG_PAGE_MANAGEMENT 0`
- L110 `#define VSM_STATUS_MSG_OVERFLOW 1`
- L113 `#define VSM_PSD_STRIDE (16 * 23)`
- L116 `#define VSM_NPF_HEADER_TOTAL_HW_CLUSTERS 0`
- L117 `#define VSM_NPF_HEADER_TOTAL_SW_CLUSTERS 1`
- L118 `#define VSM_NPF_SIZEOF_HEADER 2`
- L119 `#define VSM_NPF_ENTRY_HW_CLUSTERS 0`
- L120 `#define VSM_NPF_ENTRY_SW_CLUSTERS 1`
- L121 `#define VSM_NPF_SIZEOF_ENTRY 2`
- L124 `#define VSM_TB_HEADER_TOTAL_HW_CLUSTERS 0`
- L125 `#define VSM_TB_HEADER_TOTAL_SW_CLUSTERS 1`
- L126 `#define VSM_TB_HEADER_MAX_HW_CLUSTERS 2`
- L127 `#define VSM_TB_HEADER_MAX_SW_CLUSTERS 3`
- L128 `#define VSM_TB_HEADER_TOTAL_THROTTLE 4`
- L129 `#define VSM_TB_SIZEOF_HEADER 5`
- L130 `#define VSM_TB_ENTRY_HW_CLUSTERS 0`
- L131 `#define VSM_TB_ENTRY_SW_CLUSTERS 1`
- L132 `#define VSM_TB_ENTRY_THROTTLE 2`
- L133 `#define VSM_TB_SIZEOF_ENTRY 3`
- L136 `#define VSM_NEXT_FLAG_KEEP_PAGE (1u << 0)`
- L137 `#define VSM_NEXT_FLAG_ID_VALID (1u << 1)`
- L215 `#define ENUMERATE_VSM_STAT_SECTIONS(op) op(PhysicalPages) op(NonNanite) op(Clusters)` (5 lines)
- L8 #pragma `once`

#### Structs / classes (5)

- L147-155 _struct_ **`UE::HLSL::FPhysicalPageMetaData`** `struct FPhysicalPageMetaData`
  - L149 _member_ `uint Flags;` — VSM_FLAG_* (not all relevant to physical pages) and VSM_EXTENDED_FLAG_*
  - L150 _member_ `uint LastRequestedSceneFrameNumber;`
  - L152 _member_ `uint VirtualShadowMapId;` — Link back to the virtual shadow map & page table slot that references this physical page
  - L153 _member_ `uint MipLevel;`
  - L154 _member_ `uint2 PageAddress;`
- L157-162 _struct_ **`UE::HLSL::FVSMVisibleInstanceCmd`** `struct FVSMVisibleInstanceCmd`
  - L159 _member_ `uint PackedPageInfo;`
  - L160 _member_ `uint InstanceIdAndFlags;`
  - L161 _member_ `uint IndirectArgIndex;`
- L164-168 _struct_ **`UE::HLSL::FVSMCullingBatchInfo`** `struct FVSMCullingBatchInfo`
  - L166 _member_ `uint FirstPrimaryView;`
  - L167 _member_ `uint NumPrimaryViews;`
- L170-175 _struct_ **`UE::HLSL::FNextVirtualShadowMapData`** `struct FNextVirtualShadowMapData`
  - L172 _member_ `uint Flags;`
  - L173 _member_ `int NextVirtualShadowMapId;`
  - L174 _member_ `int2 PageAddressOffset;`
- L198-213 _struct_ **`UE::HLSL::EVSMStatSection`** `struct EVSMStatSection`

#### Enums (1)

- L200-212 _enum_ **`UE::HLSL::EVSMStatSection::Type`** `enum Type`
  - L202 _enumerator_ `None = 0`
  - L203 _enumerator_ `Basic = 1U << 0`
  - L205 _enumerator_ `PhysicalPages = 1U << 1`
  - L206 _enumerator_ `NonNanite = 1U << 2`
  - L207 _enumerator_ `Clusters = 1U << 3`
  - L209 _enumerator_ `MAX = 1U << 4`
  - L211 _enumerator_ `All = (MAX - 1)`

#### Namespaces (1)

- L143-221 _namespace_ **`UE::HLSL`** `namespace UE::HLSL` _[#if defined(__cplusplus)]_

#### typedef / using (4)

- L223 _typedef_ `using FVSMVisibleInstanceCmd = UE::HLSL::FVSMVisibleInstanceCmd;` _[#if defined(__cplusplus)]_
- L224 _typedef_ `using FVSMCullingBatchInfo = UE::HLSL::FVSMCullingBatchInfo;` _[#if defined(__cplusplus)]_
- L225 _typedef_ `using FNextVirtualShadowMapData = UE::HLSL::FNextVirtualShadowMapData;` _[#if defined(__cplusplus)]_
- L226 _typedef_ `using EVSMStatSection = UE::HLSL::EVSMStatSection;` _[#if defined(__cplusplus)]_

#### Functions (1)

- L178-196 _function_ `inline uint GetMipLevelLocal(float Footprint, uint MipMode, float ShadowMapResolutionLodBias, float GlobalResolutionLodBias, float ExtraBias = 0.0f)` (scope `UE::HLSL`) — ExtraBias must >= 0

### `Shaders/Shared/VirtualTextureDefinitions.h` (Shared)

- lines: 17; parse: all-branches
- includes: L6 `HLSLTypeAliases.h` [defined(__cplusplus)]
- L3 #pragma `once`

#### Namespaces (1)

- L7-15 _namespace_ **`UE::HLSL`** `namespace UE::HLSL` _[#if defined(__cplusplus)]_

#### static const (1)

- L12 _static_const_ `static const int VirtualTextureFeedbackBias = 3;` (scope `UE::HLSL`) — Bias applied to all feedback, allows for negative (mag) levels
