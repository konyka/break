# Shaders / Shaders/Public

- files: 13; lines: 5394
- record kinds: define=500, function=245, groupshared=3, include=27, macro_call=59, member=82, method=66, parameter=1, static_var=1, struct=10, typedef=4

### `Shaders/Public/BindlessResources.ush` (Public)

- lines: 196; parse: all-branches
- includes: L5 `Platform.ush`, L192 `/Platform/Public/PlatformBindlessResources.ush` [defined(INCLUDE_PLATFORM_BINDLESS_RESOURCES_USH)], L194 `Platform/D3D/PlatformBindlessResources.ush` [!(defined(INCLUDE_PLATFORM_BINDLESS_RESOURCES_USH)) && SM6_PROFILE]

#### Macros (#define, 38)

- L8 `#define SUPPORTS_BINDLESS_UNIFORM_BUFFER 0` _[#if !defined(SUPPORTS_BINDLESS_UNIFORM_BUFFER)]_
- L15 `#define SUPPORTS_BINDLESS_UNIFORM_BUFFER 0` _[#if !(!defined(SUPPORTS_BINDLESS_UNIFORM_BUFFER)) && !PLATFORM_SUPPORTS_CONSTANTBUFFER_OBJECT]_
- L20 `#define UE_BINDLESS_SRV_HEAP_DECL(Type) ` _[#if UE_BINDLESS_ENABLED && !defined(UE_BINDLESS_SRV_HEAP_DECL)]_
- L24 `#define UE_BINDLESS_UAV_HEAP_DECL(Type) ` _[#if UE_BINDLESS_ENABLED && !defined(UE_BINDLESS_UAV_HEAP_DECL)]_
- L28 `#define UE_BINDLESS_CBV_HEAP_DECL(Type) ` _[#if UE_BINDLESS_ENABLED && !defined(UE_BINDLESS_CBV_HEAP_DECL)]_
- L32 `#define UE_BINDLESS_SAMPLER_HEAP_DECL(Type) ` _[#if UE_BINDLESS_ENABLED && !defined(UE_BINDLESS_SAMPLER_HEAP_DECL)]_
- L36 `#define UB_SAFE_TYPE(UniformBufferName) SafeType##UniformBufferName##Constants` _[#if UE_BINDLESS_ENABLED && SUPPORTS_BINDLESS_UNIFORM_BUFFER]_
- L38 `#define UB_BINDLESS_DECL(UniformBufferType, UniformBufferName) typedef ConstantBuffer<UniformBufferType> UB_SAFE_TYPE(UniformBufferName); UE_BINDLESS_CBV_HEAP_DECL(UB_SAFE_TYPE(UniformBufferName)); UB_SAFE_TYPE(UniformBufferName) Get##UniformBufferName##Constants ...` (4 lines) _[#if UE_BINDLESS_ENABLED && SUPPORTS_BINDLESS_UNIFORM_BUFFER]_
- L45 `#define UB_RES_SAFE_TYPE(UniformBufferName, UniformBufferMember) SafeType##UniformBufferName##_##UniformBufferMember` _[#if UE_BINDLESS_ENABLED]_
- L48 `#define UB_RES_DECL_SRV(Type, UniformBufferName, UniformBufferMember) typedef Type UB_RES_SAFE_TYPE(UniformBufferName, UniformBufferMember); UE_BINDLESS_SRV_HEAP_DECL(UB_RES_SAFE_TYPE(UniformBufferName, UniformBufferMember))` (3 lines) _[#if UE_BINDLESS_ENABLED]_
- L52 `#define UB_RES_DECL_UAV(Type, UniformBufferName, UniformBufferMember) typedef Type UB_RES_SAFE_TYPE(UniformBufferName, UniformBufferMember); UE_BINDLESS_UAV_HEAP_DECL(UB_RES_SAFE_TYPE(UniformBufferName, UniformBufferMember))` (3 lines) _[#if UE_BINDLESS_ENABLED]_
- L56 `#define UB_RES_DECL_SAMPLER(Type, UniformBufferName, UniformBufferMember) typedef Type UB_RES_SAFE_TYPE(UniformBufferName, UniformBufferMember); UE_BINDLESS_SAMPLER_HEAP_DECL(UB_RES_SAFE_TYPE(UniformBufferName, UniformBufferMember))` (3 lines) _[#if UE_BINDLESS_ENABLED]_
- L61 `#define UB_CB_LOAD_SRV(UniformBufferName, UniformBufferMember) GetSRVFromHeap(UB_RES_SAFE_TYPE(UniformBufferName, UniformBufferMember), UB_CB_PREFIXED_MEMBER_ACCESS(UniformBufferName, BindlessSRV_, UniformBufferMember))` (2 lines) _[#if UE_BINDLESS_ENABLED]_
- L64 `#define UB_CB_LOAD_UAV(UniformBufferName, UniformBufferMember) GetUAVFromHeap(UB_RES_SAFE_TYPE(UniformBufferName, UniformBufferMember), UB_CB_PREFIXED_MEMBER_ACCESS(UniformBufferName, BindlessUAV_, UniformBufferMember))` (2 lines) _[#if UE_BINDLESS_ENABLED]_
- L67 `#define UB_CB_LOAD_SAMPLER(UniformBufferName, UniformBufferMember) GetSamplerFromHeap(UB_RES_SAFE_TYPE(UniformBufferName, UniformBufferMember), UB_CB_PREFIXED_MEMBER_ACCESS(UniformBufferName, BindlessSampler_, UniformBufferMember))` (2 lines) _[#if UE_BINDLESS_ENABLED]_
- L71 `#define UB_CBO_LOAD_SRV(UniformBufferName, VarName, UniformBufferMember) GetSRVFromHeap(UB_RES_SAFE_TYPE(UniformBufferName, UniformBufferMember), VarName##.BindlessSRV_##UniformBufferMember)` (2 lines) _[#if UE_BINDLESS_ENABLED]_
- L74 `#define UB_CBO_LOAD_UAV(UniformBufferName, VarName, UniformBufferMember) GetUAVFromHeap(UB_RES_SAFE_TYPE(UniformBufferName, UniformBufferMember), VarName##.BindlessUAV_##UniformBufferMember)` (2 lines) _[#if UE_BINDLESS_ENABLED]_
- L77 `#define UB_CBO_LOAD_SAMPLER(UniformBufferName, VarName, UniformBufferMember) GetSamplerFromHeap(UB_RES_SAFE_TYPE(UniformBufferName, UniformBufferMember), VarName##.BindlessSampler_##UniformBufferMember)` (2 lines) _[#if UE_BINDLESS_ENABLED]_
- L81 `#define UB_RESOURCE_MEMBER_SRV(Type, UBName, Name) UB_RES_SAFE_TYPE(UBName, Name) GetBindlessResource##UBName##_##Name() { return UB_CB_LOAD_SRV(UBName, Name); } static const UB_RES_SAFE_TYPE(UBName, Name) UBName##_##Name = GetBindlessResource##UBName ...` (3 lines) _[#if UE_BINDLESS_ENABLED]_
- L85 `#define UB_RESOURCE_MEMBER_UAV(Type, UBName, Name) UB_RES_SAFE_TYPE(UBName, Name) GetBindlessResource##UBName##_##Name() { return UB_CB_LOAD_UAV(UBName, Name); } static const UB_RES_SAFE_TYPE(UBName, Name) UBName##_##Name = GetBindlessResource##UBName ...` (3 lines) _[#if UE_BINDLESS_ENABLED]_
- L89 `#define UB_RESOURCE_MEMBER_SAMPLER(Type, UBName, Name) UB_RES_SAFE_TYPE(UBName, Name) GetBindlessSampler##UBName##_##Name() { return UB_CB_LOAD_SAMPLER(UBName, Name); } static const UB_RES_SAFE_TYPE(UBName, Name) UBName##_##Name = GetBindlessSampler##UBNa ...` (3 lines) _[#if UE_BINDLESS_ENABLED]_
- L94 `#define UB_RES_DECL_SRV(Type, UniformBufferName, UniformBufferMember) ` _[#if !(UE_BINDLESS_ENABLED)]_
- L95 `#define UB_RES_DECL_UAV(Type, UniformBufferName, UniformBufferMember) ` _[#if !(UE_BINDLESS_ENABLED)]_
- L96 `#define UB_RES_DECL_SAMPLER(Type, UniformBufferName, UniformBufferMember) ` _[#if !(UE_BINDLESS_ENABLED)]_
- L98 `#define UB_RESOURCE_MEMBER_SRV(Type, UBName, Name) Type UBName##_##Name` _[#if !(UE_BINDLESS_ENABLED)]_
- L99 `#define UB_RESOURCE_MEMBER_UAV(Type, UBName, Name) Type UBName##_##Name` _[#if !(UE_BINDLESS_ENABLED)]_
- L100 `#define UB_RESOURCE_MEMBER_SAMPLER(Type, UBName, Name) Type UBName##_##Name` _[#if !(UE_BINDLESS_ENABLED)]_
- L114 `#define GetDescriptorRangeSRV(InType, InDescriptorRange, InIndex) GetSRVFromHeap(InType, GetDescriptorRangeStartIndex(InDescriptorRange) + InIndex)` _[#if UE_BINDLESS_ENABLED && PLATFORM_SUPPORTS_DESCRIPTOR_RANGE]_
- L115 `#define GetDescriptorRangeUAV(InType, InDescriptorRange, InIndex) GetUAVFromHeap(InType, GetDescriptorRangeStartIndex(InDescriptorRange) + InIndex)` _[#if UE_BINDLESS_ENABLED && PLATFORM_SUPPORTS_DESCRIPTOR_RANGE]_
- L120 `#define DESCRIPTOR_RANGE_HEAP_DECL_SRV(Type) UE_BINDLESS_SRV_HEAP_DECL(Type)` _[#if UE_BINDLESS_ENABLED && PLATFORM_SUPPORTS_DESCRIPTOR_RANGE]_
- L121 `#define DESCRIPTOR_RANGE_HEAP_DECL_UAV(Type) UE_BINDLESS_UAV_HEAP_DECL(Type)` _[#if UE_BINDLESS_ENABLED && PLATFORM_SUPPORTS_DESCRIPTOR_RANGE]_
- L143 `#define RESOURCE_COLLECTION_HEAP_NAME_INNER1(Prefix, Name) Prefix##Name` _[#if UE_BINDLESS_ENABLED && defined(BINDLESS_SRV_ARRAY_PREFIX)]_
- L144 `#define RESOURCE_COLLECTION_HEAP_NAME_INNER(Prefix, Name) RESOURCE_COLLECTION_HEAP_NAME_INNER1(Prefix,Name)` _[#if UE_BINDLESS_ENABLED && defined(BINDLESS_SRV_ARRAY_PREFIX)]_
- L145 `#define RESOURCE_COLLECTION_HEAP_NAME(Name) RESOURCE_COLLECTION_HEAP_NAME_INNER(BINDLESS_SRV_ARRAY_PREFIX, Name)` _[#if UE_BINDLESS_ENABLED && defined(BINDLESS_SRV_ARRAY_PREFIX)]_
- L147 `#define TEXTURE_FROM_COLLECTION_T(TType) typedef TType SafeType##TType; SafeType##TType RESOURCE_COLLECTION_HEAP_NAME(TType)[]; SafeType##TType TextureFromCollection_##TType(FResourceCollection ResourceCollection, uint CollectionIndex) { uin ...` (8 lines) _[#if UE_BINDLESS_ENABLED && defined(BINDLESS_SRV_ARRAY_PREFIX)]_
- L156 `#define BUFFER_FROM_COLLECTION_T(TType) typedef TType SafeType##TType; SafeType##TType RESOURCE_COLLECTION_HEAP_NAME(TType)[]; SafeType##TType BufferFromCollection_##TType(FResourceCollection ResourceCollection, uint CollectionIndex) { uint ...` (8 lines) _[#if UE_BINDLESS_ENABLED && defined(BINDLESS_SRV_ARRAY_PREFIX)]_
- L165 `#define TEXTURE_FROM_COLLECTION_T(TType) TType TextureFromCollection_##TType(FResourceCollection ResourceCollection, uint CollectionIndex) { uint ResourceIndex = GetResourceIndexFromResourceCollection(ResourceCollection, CollectionIndex); re ...` (6 lines) _[#if UE_BINDLESS_ENABLED && !(defined(BINDLESS_SRV_ARRAY_PREFIX))]_
- L172 `#define BUFFER_FROM_COLLECTION_T(TType) TType BufferFromCollection_##TType(FResourceCollection ResourceCollection, uint CollectionIndex) { uint ResourceIndex = GetResourceIndexFromResourceCollection(ResourceCollection, CollectionIndex); ret ...` (6 lines) _[#if UE_BINDLESS_ENABLED && !(defined(BINDLESS_SRV_ARRAY_PREFIX))]_
- L3 #pragma `once`; L14 #undef `SUPPORTS_BINDLESS_UNIFORM_BUFFER`

#### typedef / using (3)

- L109 _typedef_ `typedef uint2 FDescriptorRange;` — .x = StartIndex .y = Count _[#if UE_BINDLESS_ENABLED && PLATFORM_SUPPORTS_DESCRIPTOR_RANGE]_
- L129 _typedef_ `typedef ByteAddressBuffer FResourceCollection;` _[#if UE_BINDLESS_ENABLED]_
- L186 _typedef_ `typedef Buffer<float2> Buffer_float2;` _[#if UE_BINDLESS_ENABLED]_

#### Functions (4)

- L111 _function_ `uint GetDescriptorRangeStartIndex(FDescriptorRange InDescriptorRange)` _[#if UE_BINDLESS_ENABLED && PLATFORM_SUPPORTS_DESCRIPTOR_RANGE]_
- L112 _function_ `uint GetDescriptorRangeCount (FDescriptorRange InDescriptorRange)` _[#if UE_BINDLESS_ENABLED && PLATFORM_SUPPORTS_DESCRIPTOR_RANGE]_
- L131-134 _function_ `uint GetCountFromResourceCollection(FResourceCollection ResourceCollection)` _[#if UE_BINDLESS_ENABLED]_
- L136-140 _function_ `uint GetResourceIndexFromResourceCollection(FResourceCollection ResourceCollection, uint CollectionIndex)` _[#if UE_BINDLESS_ENABLED]_

#### Top-level macro invocations (6)

- L180 _macro_call_ `TEXTURE_FROM_COLLECTION_T(Texture2D)` _[#if UE_BINDLESS_ENABLED]_
- L181 _macro_call_ `TEXTURE_FROM_COLLECTION_T(TextureCube)` _[#if UE_BINDLESS_ENABLED]_
- L182 _macro_call_ `TEXTURE_FROM_COLLECTION_T(Texture2DArray)` _[#if UE_BINDLESS_ENABLED]_
- L183 _macro_call_ `TEXTURE_FROM_COLLECTION_T(TextureCubeArray)` _[#if UE_BINDLESS_ENABLED]_
- L184 _macro_call_ `TEXTURE_FROM_COLLECTION_T(Texture3D)` _[#if UE_BINDLESS_ENABLED]_
- L187-196 _macro_call_ `BUFFER_FROM_COLLECTION_T(Buffer_float2)` _[#if UE_BINDLESS_ENABLED]_

### `Shaders/Public/DualPixelVectorization.ush` (Public)

- lines: 467; parse: all-branches
- includes: L10 `Platform.ush`

#### Macros (#define, 58)

- L12 `#define PLATFORM_SUPPORT_16BITS_DPV (PLATFORM_SUPPORTS_REAL_TYPES)`
- L15 `#define DPV_PIXEL_PER_LANE 2`
- L21 `#define __DPV_VECTOR(TYPE, COMPONENTS) TYPE##COMPONENTS` (2 lines)
- L25 `#define __DPV_MULTI_SCALAR(TYPE) TYPE##2` (2 lines)
- L29 `#define __DPV_MULTI_VECTOR(TYPE, COMPONENTS) TYPE##COMPONENTS##x2` (2 lines)
- L33 `#define __DPV_MULTI_VECTOR_TRANSPOSED(TYPE, COMPONENTS) TYPE##2x##COMPONENTS` (2 lines)
- L38 `#define __DPV_FOREACH_COMPONENTS_2(COMPONENT_CODE, COMPONENT_SEPARATOR, ...) COMPONENT_CODE(0, __VA_ARGS__) COMPONENT_SEPARATOR COMPONENT_CODE(1, __VA_ARGS__)` (5 lines)
- L43 `#define __DPV_FOREACH_COMPONENTS_3(COMPONENT_CODE, COMPONENT_SEPARATOR, ...) COMPONENT_CODE(0, __VA_ARGS__) COMPONENT_SEPARATOR COMPONENT_CODE(1, __VA_ARGS__) COMPONENT_SEPARATOR COMPONENT_CODE(2, __VA_ARGS__)` (7 lines)
- L50 `#define __DPV_FOREACH_COMPONENTS_4(COMPONENT_CODE, COMPONENT_SEPARATOR, ...) COMPONENT_CODE(0, __VA_ARGS__) COMPONENT_SEPARATOR COMPONENT_CODE(1, __VA_ARGS__) COMPONENT_SEPARATOR COMPONENT_CODE(2, __VA_ARGS__) COMPONENT_SEPARATOR COMPONENT_CODE(3, __VA_ARGS__)` (9 lines)
- L59 `#define __DPV_FOREACH_COMPONENTS(COMPONENTS, COMPONENT_CODE, COMPONENT_SEPARATOR, ...) __DPV_FOREACH_COMPONENTS_##COMPONENTS(COMPONENT_CODE, COMPONENT_SEPARATOR, __VA_ARGS__)` (2 lines)
- L64 `#define __DPV_FOREACH_COMPONENTS_ARGS_2(COMPONENT_CODE, ...) COMPONENT_CODE(0, __VA_ARGS__), COMPONENT_CODE(1, __VA_ARGS__)` (4 lines)
- L68 `#define __DPV_FOREACH_COMPONENTS_ARGS_3(COMPONENT_CODE, ...) COMPONENT_CODE(0, __VA_ARGS__), COMPONENT_CODE(1, __VA_ARGS__), COMPONENT_CODE(2, __VA_ARGS__)` (5 lines)
- L73 `#define __DPV_FOREACH_COMPONENTS_ARGS_4(COMPONENT_CODE, ...) COMPONENT_CODE(0, __VA_ARGS__), COMPONENT_CODE(1, __VA_ARGS__), COMPONENT_CODE(2, __VA_ARGS__), COMPONENT_CODE(3, __VA_ARGS__)` (6 lines)
- L79 `#define __DPV_FOREACH_COMPONENTS_ARGS(COMPONENTS, COMPONENT_CODE, ...) __DPV_FOREACH_COMPONENTS_ARGS_##COMPONENTS(COMPONENT_CODE, __VA_ARGS__)` (2 lines)
- L84 `#define __DPV_FOREACH_COMPONENTS_CONSTRUCTOR(TYPE, COMPONENTS, COMPONENT_CODE, ...) __DPV_MULTI_VECTOR(TYPE, COMPONENTS)(__DPV_FOREACH_COMPONENTS_ARGS(COMPONENTS, COMPONENT_CODE, __VA_ARGS__))` (2 lines)
- L89 `#define __DPV_CODE_FUNCTION_2_ARGS(c, FUNCTION_NAME, ARG_NAME_0, ARG_NAME_1) FUNCTION_NAME(ARG_NAME_0[c], ARG_NAME_1[c])`
- L90 `#define __DPV_CODE_FUNCTION_3_ARGS(c, FUNCTION_NAME, ARG_NAME_0, ARG_NAME_1, ARG_NAME_2) FUNCTION_NAME(ARG_NAME_0[c], ARG_NAME_1[c], ARG_NAME_2[c])`
- L93 `#define __DPV_CODE_OPERATOR_VECTOR_VECTOR(c, ARG_NAME_0, OPERATOR, ARG_NAME_1) (ARG_NAME_0[c] OPERATOR ARG_NAME_1[c])`
- L94 `#define __DPV_CODE_OPERATOR_VECTOR_SCALAR(c, ARG_NAME_0, OPERATOR, ARG_NAME_1) (ARG_NAME_0[c] OPERATOR ARG_NAME_1)`
- L98 `#define DEFINE_DPV_FUNCTION_FOR_FLOAT_SCALARS(DEFINE_DPV_FUNCTION) DEFINE_DPV_FUNCTION(float)` (3 lines)
- L101 `#define DEFINE_DPV_FUNCTION_FOR_INT_SCALARS(DEFINE_DPV_FUNCTION) DEFINE_DPV_FUNCTION(uint) DEFINE_DPV_FUNCTION(int)` (4 lines)
- L105 `#define DEFINE_DPV_FUNCTION_FOR_FLOAT_VECTOR(DEFINE_DPV_FUNCTION, COMPONENTS) DEFINE_DPV_FUNCTION(float, COMPONENTS)` (3 lines)
- L108 `#define DEFINE_DPV_FUNCTION_FOR_INT_VECTOR(DEFINE_DPV_FUNCTION, COMPONENTS) DEFINE_DPV_FUNCTION(uint, COMPONENTS) DEFINE_DPV_FUNCTION(int, COMPONENTS)` (4 lines)
- L112 `#define DEFINE_DPV_FUNCTION_FOR_FLOAT_VECTORS(DEFINE_DPV_FUNCTION) DEFINE_DPV_FUNCTION_FOR_FLOAT_VECTOR(DEFINE_DPV_FUNCTION, 2) DEFINE_DPV_FUNCTION_FOR_FLOAT_VECTOR(DEFINE_DPV_FUNCTION, 3) DEFINE_DPV_FUNCTION_FOR_FLOAT_VECTOR(DEFINE_DPV_FUNCTION, 4)` (5 lines)
- L117 `#define DEFINE_DPV_FUNCTION_FOR_INT_VECTORS(DEFINE_DPV_FUNCTION) DEFINE_DPV_FUNCTION_FOR_INT_VECTOR(DEFINE_DPV_FUNCTION, 2) DEFINE_DPV_FUNCTION_FOR_INT_VECTOR(DEFINE_DPV_FUNCTION, 3) DEFINE_DPV_FUNCTION_FOR_INT_VECTOR(DEFINE_DPV_FUNCTION, 4)` (5 lines)
- L124 `#define DEFINE_DPV_FUNCTION_FOR_HALF_SCALARS(DEFINE_DPV_FUNCTION) DEFINE_DPV_FUNCTION(float16_t)` (3 lines) _[#if PLATFORM_SUPPORT_16BITS_DPV]_
- L127 `#define DEFINE_DPV_FUNCTION_FOR_SHORT_SCALARS(DEFINE_DPV_FUNCTION) DEFINE_DPV_FUNCTION(uint16_t) DEFINE_DPV_FUNCTION(int16_t)` (4 lines) _[#if PLATFORM_SUPPORT_16BITS_DPV]_
- L131 `#define DEFINE_DPV_FUNCTION_FOR_HALF_VECTORS(DEFINE_DPV_FUNCTION) DEFINE_DPV_FUNCTION(float16_t, 2) DEFINE_DPV_FUNCTION(float16_t, 3) DEFINE_DPV_FUNCTION(float16_t, 4)` (5 lines) _[#if PLATFORM_SUPPORT_16BITS_DPV]_
- L136 `#define DEFINE_DPV_FUNCTION_FOR_HALF_VECTOR2(DEFINE_DPV_FUNCTION) DEFINE_DPV_FUNCTION(float16_t, 2)` (3 lines) _[#if PLATFORM_SUPPORT_16BITS_DPV]_
- L139 `#define DEFINE_DPV_FUNCTION_FOR_SHORT_VECTORS(DEFINE_DPV_FUNCTION) DEFINE_DPV_FUNCTION(uint16_t, 2) DEFINE_DPV_FUNCTION(uint16_t, 3) DEFINE_DPV_FUNCTION(uint16_t, 4) DEFINE_DPV_FUNCTION(int16_t, 2) DEFINE_DPV_FUNCTION(int16_t, 3) DEFINE_DPV_FUNCTION(int16_t, 4)` (8 lines) _[#if PLATFORM_SUPPORT_16BITS_DPV]_
- L149 `#define DEFINE_DPV_FUNCTION_FOR_HALF_SCALARS(DEFINE_DPV_FUNCTION) ` _[#if !(PLATFORM_SUPPORT_16BITS_DPV)]_
- L151 `#define DEFINE_DPV_FUNCTION_FOR_SHORT_SCALARS(DEFINE_DPV_FUNCTION) ` _[#if !(PLATFORM_SUPPORT_16BITS_DPV)]_
- L153 `#define DEFINE_DPV_FUNCTION_FOR_HALF_VECTORS(DEFINE_DPV_FUNCTION) ` _[#if !(PLATFORM_SUPPORT_16BITS_DPV)]_
- L155 `#define DEFINE_DPV_FUNCTION_FOR_HALF_VECTOR2(DEFINE_DPV_FUNCTION) ` _[#if !(PLATFORM_SUPPORT_16BITS_DPV)]_
- L157 `#define DEFINE_DPV_FUNCTION_FOR_SHORT_VECTORS(DEFINE_DPV_FUNCTION) ` _[#if !(PLATFORM_SUPPORT_16BITS_DPV)]_
- L161 `#define DEFINE_DPV_FUNCTION_FOR_ALL_32BIT_SCALARS(DEFINE_DPV_FUNCTION) DEFINE_DPV_FUNCTION_FOR_FLOAT_SCALARS(DEFINE_DPV_FUNCTION) DEFINE_DPV_FUNCTION_FOR_INT_SCALARS(DEFINE_DPV_FUNCTION)` (4 lines)
- L165 `#define DEFINE_DPV_FUNCTION_FOR_ALL_16BIT_SCALARS(DEFINE_DPV_FUNCTION) DEFINE_DPV_FUNCTION_FOR_HALF_SCALARS(DEFINE_DPV_FUNCTION) DEFINE_DPV_FUNCTION_FOR_SHORT_SCALARS(DEFINE_DPV_FUNCTION)` (4 lines)
- L169 `#define DEFINE_DPV_FUNCTION_FOR_ALL_SCALARS(DEFINE_DPV_FUNCTION) DEFINE_DPV_FUNCTION_FOR_ALL_32BIT_SCALARS(DEFINE_DPV_FUNCTION) DEFINE_DPV_FUNCTION_FOR_ALL_16BIT_SCALARS(DEFINE_DPV_FUNCTION)` (4 lines)
- L174 `#define DEFINE_DPV_FUNCTION_FOR_ALL_32BIT_VECTORS(DEFINE_DPV_FUNCTION) DEFINE_DPV_FUNCTION_FOR_FLOAT_VECTORS(DEFINE_DPV_FUNCTION) DEFINE_DPV_FUNCTION_FOR_INT_VECTORS(DEFINE_DPV_FUNCTION)` (4 lines)
- L178 `#define DEFINE_DPV_FUNCTION_FOR_ALL_16BIT_VECTORS(DEFINE_DPV_FUNCTION) DEFINE_DPV_FUNCTION_FOR_HALF_VECTORS(DEFINE_DPV_FUNCTION) DEFINE_DPV_FUNCTION_FOR_SHORT_VECTORS(DEFINE_DPV_FUNCTION)` (4 lines)
- L182 `#define DEFINE_DPV_FUNCTION_FOR_ALL_VECTORS(DEFINE_DPV_FUNCTION) DEFINE_DPV_FUNCTION_FOR_ALL_32BIT_VECTORS(DEFINE_DPV_FUNCTION) DEFINE_DPV_FUNCTION_FOR_ALL_16BIT_VECTORS(DEFINE_DPV_FUNCTION)` (4 lines)
- L208 `#define DEFINE_DPV_FUNCTION_SCALAR(TYPE) CALL_SITE_DEBUGLOC __DPV_MULTI_SCALAR(TYPE) dpv_interleave_registers(TYPE lo, TYPE hi) { return __DPV_MULTI_SCALAR(TYPE)(lo, hi); } CALL_SITE_DEBUGLOC TYPE dpv_lo(__DPV_MULTI_SCALAR(TYPE) x) { return  ...` (6 lines)
- L214 `#define DEFINE_DPV_FUNCTION_VECTOR(TYPE, COMPONENTS) CALL_SITE_DEBUGLOC __DPV_MULTI_VECTOR(TYPE, COMPONENTS) dpv_interleave_registers(__DPV_VECTOR(TYPE, COMPONENTS) lo, __DPV_VECTOR(TYPE, COMPONENTS) hi) { return transpose(__DPV_MULTI_VECTOR_TRANSPOSED( ...` (6 lines)
- L234 `#define DEFINE_DPV_FUNCTION_SCALAR(TYPE) CALL_SITE_DEBUGLOC __DPV_MULTI_SCALAR(TYPE) dpv_force_interleave_registers(TYPE lo, TYPE hi) { return dpv_interleave_registers(lo, hi); }` (3 lines)
- L237 `#define DEFINE_DPV_FUNCTION_VECTOR(TYPE, COMPONENTS) CALL_SITE_DEBUGLOC __DPV_MULTI_VECTOR(TYPE, COMPONENTS) dpv_force_interleave_registers(__DPV_VECTOR(TYPE, COMPONENTS) lo, __DPV_VECTOR(TYPE, COMPONENTS) hi) { return dpv_interleave_registers(lo, hi);  ...` (3 lines)
- L246 `#define DEFINE_DPV_FUNCTION_SCALAR(TYPE) CALL_SITE_DEBUGLOC __DPV_MULTI_SCALAR(TYPE) dpv_force_interleave_registers(TYPE lo, TYPE hi) { return v_pack_b32_b16(lo, hi); }` (3 lines)
- L249 `#define DEFINE_DPV_FUNCTION_VECTOR(TYPE, COMPONENTS) CALL_SITE_DEBUGLOC __DPV_MULTI_VECTOR(TYPE, COMPONENTS) dpv_force_interleave_registers(__DPV_VECTOR(TYPE, COMPONENTS) lo, __DPV_VECTOR(TYPE, COMPONENTS) hi) { return __DPV_FOREACH_COMPONENTS_CONSTRUCT ...` (5 lines)
- L271 `#define dpv_interleave_registers_array(ArrayName) dpv_interleave_registers((ArrayName)[0], (ArrayName)[1])`
- L272 `#define dpv_force_interleave_registers_array(ArrayName) dpv_force_interleave_registers((ArrayName)[0], (ArrayName)[1])`
- L289 `#define DEFINE_DPV_FUNCTION_SCALAR(TYPE) CALL_SITE_DEBUGLOC __DPV_MULTI_SCALAR(TYPE) dpv_interleave_mono_registers(TYPE lo) { return dpv_interleave_registers(lo, lo); }` (2 lines)
- L292 `#define DEFINE_DPV_FUNCTION_VECTOR(TYPE, COMPONENTS) CALL_SITE_DEBUGLOC __DPV_MULTI_VECTOR(TYPE, COMPONENTS) dpv_interleave_mono_registers(__DPV_VECTOR(TYPE, COMPONENTS) lo) { return dpv_interleave_registers(lo, lo); }` (2 lines)
- L310 `#define DEFINE_DPV_FUNCTION_SCALAR(TYPE) CALL_SITE_DEBUGLOC __DPV_MULTI_SCALAR(TYPE) dpv_scale(__DPV_MULTI_SCALAR(TYPE) a, __DPV_MULTI_SCALAR(TYPE) b) { return a * b; }` (5 lines)
- L315 `#define DEFINE_DPV_FUNCTION_VECTOR(TYPE, COMPONENTS) CALL_SITE_DEBUGLOC __DPV_MULTI_VECTOR(TYPE, COMPONENTS) dpv_mul(__DPV_MULTI_VECTOR(TYPE, COMPONENTS) a, __DPV_MULTI_VECTOR(TYPE, COMPONENTS) b) { return __DPV_FOREACH_COMPONENTS_CONSTRUCTOR(TYPE, COMP ...` (23 lines)
- L352 `#define DEFINE_DPV_FUNCTION_VECTOR(TYPE, COMPONENTS) CALL_SITE_DEBUGLOC __DPV_MULTI_VECTOR(TYPE, COMPONENTS) dpv_add(__DPV_MULTI_VECTOR(TYPE, COMPONENTS) a, __DPV_MULTI_VECTOR(TYPE, COMPONENTS) b) { return __DPV_FOREACH_COMPONENTS_CONSTRUCTOR(TYPE, COMP ...` (20 lines)
- L383 `#define DEFINE_DPV_FUNCTION_SCALAR(TYPE) CALL_SITE_DEBUGLOC __DPV_MULTI_SCALAR(TYPE) dpv_min(__DPV_MULTI_SCALAR(TYPE) a, __DPV_MULTI_SCALAR(TYPE) b) { return min(a, b); } CALL_SITE_DEBUGLOC __DPV_MULTI_SCALAR(TYPE) dpv_max(__DPV_MULTI_SCALAR ...` (8 lines)
- L391 `#define DEFINE_DPV_FUNCTION_VECTOR(TYPE, COMPONENTS) CALL_SITE_DEBUGLOC __DPV_MULTI_SCALAR(TYPE) dpv_dot(__DPV_MULTI_VECTOR(TYPE, COMPONENTS) a, __DPV_MULTI_VECTOR(TYPE, COMPONENTS) b) { return __DPV_FOREACH_COMPONENTS(COMPONENTS, __DPV_CODE_OPERATOR_VE ...` (32 lines)
- L430 `#define DEFINE_DPV_FUNCTION_VECTOR(TYPE, COMPONENTS) CALL_SITE_DEBUGLOC __DPV_VECTOR(TYPE, COMPONENTS) dpv_cross(__DPV_MULTI_VECTOR(TYPE, COMPONENTS) a, __DPV_MULTI_VECTOR(TYPE, COMPONENTS) b) { __DPV_VECTOR(TYPE, COMPONENTS) lo = dpv_lo(b); __DPV_VECTO ...` (9 lines)
- L452 `#define DEFINE_DPV_FUNCTION_VECTOR(TYPE, COMPONENTS) CALL_SITE_DEBUGLOC __DPV_MULTI_SCALAR(TYPE) dpv_length2(__DPV_MULTI_VECTOR(TYPE, COMPONENTS) v) { return dpv_dot(v, v); } CALL_SITE_DEBUGLOC __DPV_MULTI_SCALAR(TYPE) dpv_length(__DPV_MULTI_VECTOR(TYPE ...` (11 lines)
- L8 #pragma `once`; L222 #undef `DEFINE_DPV_FUNCTION_SCALAR`; L223 #undef `DEFINE_DPV_FUNCTION_VECTOR`; L242 #undef `DEFINE_DPV_FUNCTION_SCALAR`; L243 #undef `DEFINE_DPV_FUNCTION_VECTOR`; L256 #undef `DEFINE_DPV_FUNCTION_SCALAR`; L257 #undef `DEFINE_DPV_FUNCTION_VECTOR`; L297 #undef `DEFINE_DPV_FUNCTION_SCALAR`; L298 #undef `DEFINE_DPV_FUNCTION_VECTOR`; L340 #undef `DEFINE_DPV_FUNCTION_SCALAR`; L341 #undef `DEFINE_DPV_FUNCTION_VECTOR`; L373 #undef `DEFINE_DPV_FUNCTION_VECTOR`; L425 #undef `DEFINE_DPV_FUNCTION_SCALAR`; L426 #undef `DEFINE_DPV_FUNCTION_VECTOR`; L442 #undef `DEFINE_DPV_FUNCTION_VECTOR`; L466 #undef `DEFINE_DPV_FUNCTION_VECTOR`

#### Top-level macro invocations (1)

- L220-467 _macro_call_ `DEFINE_DPV_FUNCTION_FOR_ALL_SCALARS(DEFINE_DPV_FUNCTION_SCALAR) DEFINE_DPV_FUNCTION_FOR_ALL_VECTORS(DEFINE_DPV_FUNCTION_VECTOR) DEFINE_DPV_FUNCTION_FOR_ALL_32BIT_SCALARS(DEFINE_DPV_FUNCTION_SCALAR) DEFINE_DPV_FUNCTION_FOR_ALL_32BIT_VECTORS(DEFINE_DPV_FUNCTION_VECTOR) DEFINE_DPV_FUNCTION_FOR_ALL_16BIT_SCALARS(DEFINE_DPV_FUNCTION_SCALAR) DEFINE_DPV_FUNCTION_FOR_ALL_16BIT_VECTORS(DEFINE_DPV_FUNCTION_`

### `Shaders/Public/FP16Math.ush` (Public)

- lines: 44; parse: all-branches

#### Macros (#define, 23)

- L10 `#define EXPERIMENTAL_FP16 1` _[#if !defined(EXPERIMENTAL_FP16)]_
- L14 `#define USE_MIN16FLOAT 0` _[#if !defined(USE_MIN16FLOAT)]_
- L19 `#define EXP_FLT min16float` _[#if EXPERIMENTAL_FP16 && USE_MIN16FLOAT]_
- L20 `#define EXP_FLT2 min16float2` _[#if EXPERIMENTAL_FP16 && USE_MIN16FLOAT]_
- L21 `#define EXP_FLT3 min16float3` _[#if EXPERIMENTAL_FP16 && USE_MIN16FLOAT]_
- L22 `#define EXP_FLT4 min16float4` _[#if EXPERIMENTAL_FP16 && USE_MIN16FLOAT]_
- L23 `#define EXP_FLT3x3 min16float3x3` _[#if EXPERIMENTAL_FP16 && USE_MIN16FLOAT]_
- L24 `#define EXP_FLT4x4 min16float4x4` _[#if EXPERIMENTAL_FP16 && USE_MIN16FLOAT]_
- L25 `#define EXP_FLT4x3 min16float4x3` _[#if EXPERIMENTAL_FP16 && USE_MIN16FLOAT]_
- L27 `#define EXP_FLT half` _[#if EXPERIMENTAL_FP16 && !(USE_MIN16FLOAT)]_
- L28 `#define EXP_FLT2 half2` _[#if EXPERIMENTAL_FP16 && !(USE_MIN16FLOAT)]_
- L29 `#define EXP_FLT3 half3` _[#if EXPERIMENTAL_FP16 && !(USE_MIN16FLOAT)]_
- L30 `#define EXP_FLT4 half4` _[#if EXPERIMENTAL_FP16 && !(USE_MIN16FLOAT)]_
- L31 `#define EXP_FLT3x3 half3x3` _[#if EXPERIMENTAL_FP16 && !(USE_MIN16FLOAT)]_
- L32 `#define EXP_FLT4x4 half4x4` _[#if EXPERIMENTAL_FP16 && !(USE_MIN16FLOAT)]_
- L33 `#define EXP_FLT4x3 half4x3` _[#if EXPERIMENTAL_FP16 && !(USE_MIN16FLOAT)]_
- L36 `#define EXP_FLT float` _[#if !(EXPERIMENTAL_FP16)]_
- L37 `#define EXP_FLT2 float2` _[#if !(EXPERIMENTAL_FP16)]_
- L38 `#define EXP_FLT3 float3` _[#if !(EXPERIMENTAL_FP16)]_
- L39 `#define EXP_FLT4 float4` _[#if !(EXPERIMENTAL_FP16)]_
- L40 `#define EXP_FLT3x3 float3x3` _[#if !(EXPERIMENTAL_FP16)]_
- L41 `#define EXP_FLT4x4 float4x4` _[#if !(EXPERIMENTAL_FP16)]_
- L42 `#define EXP_FLT4x3 float4x3` _[#if !(EXPERIMENTAL_FP16)]_
- L7 #pragma `once`

### `Shaders/Public/IndirectVirtualTexture.ush` (Public)

- lines: 13; parse: all-branches
- includes: L5 `/Engine/Shared/IndirectVirtualTextureDefinitions.h`

#### Macros (#define, 1)

- L11 `#define FIndirectVirtualTexture Buffer<uint2>` _[#if !(defined(__cplusplus))]_
- L3 #pragma `once`

#### typedef / using (1)

- L8 _typedef_ `typedef Buffer<uint2> FIndirectVirtualTexture;` _[#if defined(__cplusplus)]_

### `Shaders/Public/IndirectVirtualTextureCommon.ush` (Public)

- lines: 75; parse: all-branches
- includes: L5 `/Engine/Public/IndirectVirtualTexture.ush`, L6 `/Engine/Private/VirtualTextureCommon.ush`
- L3 #pragma `once`

#### Structs / classes (1)

- L8-15 _struct_ **`FIndirectVirtualTextureInfo`** `struct FIndirectVirtualTextureInfo`
  - L10 _member_ `uint BlockX;`
  - L11 _member_ `uint BlockY;`
  - L12 _member_ `uint BlockWidth;`
  - L13 _member_ `uint BlockHeight;`
  - L14 _member_ `uint MaxLevel;`

#### Functions (5)

- L17-28 _function_ `FIndirectVirtualTextureUniform GetIndirectVirtualTextureUniform(uint4 MaterialTextureCollectionPackedUniforms0, uint4 MaterialTextureCollectionPackedUniforms1 , uint4 MaterialTextureCollectionPackedUniforms2, uint4 MaterialTextureCollectionPackedUniforms3)`
- L30-33 _function_ `uint GetIndirectVirtualTextureCount(in FIndirectVirtualTextureUniform Uniform)`
- L35-42 _function_ `FIndirectVirtualTextureEntry LoadIndirectVirtualTexture(in FIndirectVirtualTexture Collection, in FIndirectVirtualTextureUniform Uniform, uint CollectionIndex)`
- L44-53 _function_ `FIndirectVirtualTextureInfo UnpackIndirectVirtualTexture(in FIndirectVirtualTextureEntry Entry)`
- L55-74 _function_ `VTPageTableUniform UnpackIndirectVirtualTexturePageTableUniform(in FIndirectVirtualTextureEntry Entry, uint4 A, uint4 B)`

### `Shaders/Public/LaneVectorization.ush` (Public)

- lines: 2269; parse: first-branch (retry, +8 merged from all-branches pass)
- includes: L9 `Platform.ush`, L10 `WaveBroadcastIntrinsics.ush`

#### Macros (#define, 9)

- L16 `#define TENSOR_REGISTER_LAYOUT FRegisters_AoS_VectorArray` _[#if !defined(TENSOR_REGISTER_LAYOUT)]_
- L20 `#define TENSOR_REGISTER_TIGHTENING 0` _[#if !defined(TENSOR_REGISTER_TIGHTENING)]_
- L359 `#define GetVectorByteSize(ScalarType, VectorSize) uint(sizeof(ScalarType) * uint(VectorSize))`
- L362 `#define GetVectorDwordSize(ScalarType, VectorSize) (uint(GetVectorByteSize(ScalarType, VectorSize) + 3u) / 4u)`
- L2027 `#define TVECTOR_FUNCTION_1PARAMS_ALIASE_FUNCTION_NAME(ReturnScalarType, FunctionName,AliasFunctionName) CALL_SITE_DEBUGLOC template<typename ScalarType, uint VectorSize, uint SimdSizeX, uint SimdSizeY> TLaneVector2D<ReturnScalarType, VectorSize, SimdSizeX, SimdSizeY> AliasFunctionName( TLaneVector2D<Sca ...` (28 lines)
- L2055 `#define TVECTOR_FUNCTION_1PARAMS(ReturnScalarType, FunctionName) TVECTOR_FUNCTION_1PARAMS_ALIASE_FUNCTION_NAME(ReturnScalarType, FunctionName, FunctionName)`
- L2080 `#define TVECTOR_FUNCTION_2PARAMS(FunctionName) CALL_SITE_DEBUGLOC template<typename ScalarType, uint VectorSize, uint SimdSizeX, uint SimdSizeY> TLaneVector2D<ScalarType, VectorSize, SimdSizeX, SimdSizeY> FunctionName( TLaneVector2D<ScalarType, Ve ...` (29 lines)
- L2122 `#define TVECTOR_FUNCTION_2PARAMS_DIFF_RETURN(ReturnVectorSize, FunctionName) CALL_SITE_DEBUGLOC template<typename ScalarType, uint VectorSize, uint SimdSizeX, uint SimdSizeY> TLaneVector2D<ScalarType, ReturnVectorSize, SimdSizeX, SimdSizeY> FunctionName( TLaneVector2D<ScalarTy ...` (29 lines)
- L2155 `#define TVECTOR_FUNCTION_3PARAMS(FunctionName, ScalarTypeA) CALL_SITE_DEBUGLOC template<typename ScalarType, uint VectorSize, uint SimdSizeX, uint SimdSizeY> TLaneVector2D<ScalarType, VectorSize, SimdSizeX, SimdSizeY> FunctionName( TLaneVector2D<ScalarTypeA, V ...` (30 lines)
- L7 #pragma `once`

#### Structs / classes (7)

- L759-823 _struct_ **`FRegisters_S_OneVector`** `template<typename ScalarType, uint InVectorSize, uint InElementCount> struct FRegisters_S_OneVector` — Stores one unique vector<>. InElementCount must be == 1
  - L763 _member_ `static const uint VectorSize = InVectorSize;` — Size of each element.
  - L766 _member_ `static const uint ElementCount = 1;` — Number of elememnts
  - L769 _member_ `static const uint RegisterRowSize = VectorSize;` — Size and number of register rows
  - L770 _member_ `static const uint RegisterRowCount = 1;`
  - L772 _member_ `vector<ScalarType, VectorSize> E;`
  - L772 _member_ `vector<ScalarType, VectorSize> E;`
  - L777 _method_ `CALL_SITE_DEBUGLOC vector<ScalarType, RegisterRowSize> GetRegisterRow(const uint RegisterRowIndex)`
  - L783 _method_ `CALL_SITE_DEBUGLOC void SetRegisterRow(const uint RegisterRowIndex, vector<ScalarType, RegisterRowSize> RegisterRow)`
  - L792 _method_ `CALL_SITE_DEBUGLOC vector<ScalarType, VectorSize> GetElement(const uint ElementIndex)`
  - L798 _method_ `CALL_SITE_DEBUGLOC void SetElement(const uint ElementIndex, vector<ScalarType, VectorSize> Element)`
  - L804 _method_ `vector<ScalarType, VectorSize> WaveBroadcastElement(const FWaveBroadcastSettings BroadcastSettings, const uint ElementIndex)`
  - L812 _method_ `CALL_SITE_DEBUGLOC ScalarType GetElementComponent(const uint ElementIndex, const uint ComponentIndex)`
  - L818 _method_ `CALL_SITE_DEBUGLOC void SetElementComponent(const uint ElementIndex, const uint ComponentIndex, ScalarType Component)`
- L826-890 _struct_ **`FRegisters_AoS_VectorArray`** `template<typename ScalarType, uint InVectorSize, uint InElementCount> struct FRegisters_AoS_VectorArray` — Stores an array of vector<> as an array of structure in registers.
  - L830 _member_ `static const uint VectorSize = InVectorSize;` — Size of each element.
  - L833 _member_ `static const uint ElementCount = InElementCount;` — Number of elememnts
  - L836 _member_ `static const uint RegisterRowSize = VectorSize;` — Size and number of register rows
  - L837 _member_ `static const uint RegisterRowCount = ElementCount;`
  - L839 _member_ `vector<ScalarType, VectorSize> Array[ElementCount];`
  - L839 _member_ `vector<ScalarType, VectorSize> Array[ElementCount];`
  - L844 _method_ `CALL_SITE_DEBUGLOC vector<ScalarType, RegisterRowSize> GetRegisterRow(const uint RegisterRowIndex)`
  - L850 _method_ `CALL_SITE_DEBUGLOC void SetRegisterRow(const uint RegisterRowIndex, vector<ScalarType, RegisterRowSize> RegisterRow)`
  - L859 _method_ `CALL_SITE_DEBUGLOC vector<ScalarType, VectorSize> GetElement(const uint ElementIndex)`
  - L865 _method_ `CALL_SITE_DEBUGLOC void SetElement(const uint ElementIndex, vector<ScalarType, VectorSize> Element)`
  - L871 _method_ `vector<ScalarType, VectorSize> WaveBroadcastElement(const FWaveBroadcastSettings BroadcastSettings, const uint ElementIndex)`
  - L879 _method_ `CALL_SITE_DEBUGLOC ScalarType GetElementComponent(const uint ElementIndex, const uint ComponentIndex)`
  - L885 _method_ `CALL_SITE_DEBUGLOC void SetElementComponent(const uint ElementIndex, const uint ComponentIndex, ScalarType Component)`
- L893-957 _struct_ **`FRegisters_AoS_Matrix`** `template<typename ScalarType, uint InVectorSize, uint InElementCount> struct FRegisters_AoS_Matrix` — Stores an array of vector<> as an array of structure in registers using a matrix<>.
  - L897 _member_ `static const uint VectorSize = InVectorSize;` — Size of each element.
  - L900 _member_ `static const uint ElementCount = InElementCount;` — Number of elememnts
  - L903 _member_ `static const uint RegisterRowSize = VectorSize;` — Size and number of register rows
  - L904 _member_ `static const uint RegisterRowCount = ElementCount;`
  - L906 _member_ `matrix<ScalarType, ElementCount, VectorSize> M;`
  - L906 _member_ `matrix<ScalarType, ElementCount, VectorSize> M;`
  - L906 _member_ `matrix<ScalarType, ElementCount, VectorSize> M;`
  - L911 _method_ `CALL_SITE_DEBUGLOC vector<ScalarType, RegisterRowSize> GetRegisterRow(const uint RegisterRowIndex)`
  - L917 _method_ `CALL_SITE_DEBUGLOC void SetRegisterRow(const uint RegisterRowIndex, vector<ScalarType, RegisterRowSize> RegisterRow)`
  - L926 _method_ `CALL_SITE_DEBUGLOC vector<ScalarType, VectorSize> GetElement(const uint ElementIndex)`
  - L932 _method_ `CALL_SITE_DEBUGLOC void SetElement(const uint ElementIndex, vector<ScalarType, VectorSize> Element)`
  - L938 _method_ `vector<ScalarType, VectorSize> WaveBroadcastElement(const FWaveBroadcastSettings BroadcastSettings, const uint ElementIndex)`
  - L946 _method_ `CALL_SITE_DEBUGLOC ScalarType GetElementComponent(const uint ElementIndex, const uint ComponentIndex)`
  - L952 _method_ `CALL_SITE_DEBUGLOC void SetElementComponent(const uint ElementIndex, const uint ComponentIndex, ScalarType Component)`
- L960-1080 _struct_ **`FRegisters_SoA_Matrix`** `template<typename ScalarType, uint InVectorSize, uint InElementCount> struct FRegisters_SoA_Matrix` — Stores an array of vector<> as a structure of array in registers using a matrix<>. Requires InElementCount a pair >= 2
  - L964 _member_ `static const uint VectorSize = InVectorSize;` — Size of each element.
  - L967 _member_ `static const uint ElementCount = InElementCount;` — Number of elememnts
  - L970 _member_ `static const uint RegisterRowSize = ElementCount;` — Size and number of register rows
  - L971 _member_ `static const uint RegisterRowCount = VectorSize;`
  - L973 _member_ `matrix<ScalarType, VectorSize, ElementCount> M;`
  - L973 _member_ `matrix<ScalarType, VectorSize, ElementCount> M;`
  - L973 _member_ `matrix<ScalarType, VectorSize, ElementCount> M;`
  - L978 _method_ `CALL_SITE_DEBUGLOC vector<ScalarType, RegisterRowSize> GetRegisterRow(const uint RegisterRowIndex)`
  - L984 _method_ `CALL_SITE_DEBUGLOC void SetRegisterRow(const uint RegisterRowIndex, vector<ScalarType, RegisterRowSize> RegisterRow)`
  - L993 _method_ `CALL_SITE_DEBUGLOC vector<ScalarType, VectorSize> GetElement(const uint ElementIndex)`
  - L1018 _method_ `CALL_SITE_DEBUGLOC void SetElement(const uint ElementIndex, vector<ScalarType, VectorSize> Element)`
  - L1041 _method_ `vector<ScalarType, VectorSize> WaveBroadcastElement(const FWaveBroadcastSettings BroadcastSettings, const uint ElementIndex)`
  - L1069 _method_ `CALL_SITE_DEBUGLOC ScalarType GetElementComponent(const uint ElementIndex, const uint ComponentIndex)`
  - L1075 _method_ `CALL_SITE_DEBUGLOC void SetElementComponent(const uint ElementIndex, const uint ComponentIndex, ScalarType Component)`
- L1083-1187 _struct_ **`FRegisters_AoS_PairArray`** `template<typename ScalarType, uint InVectorSize, uint InElementCount> struct FRegisters_AoS_PairArray` — Stores an array of vector<> as a structure of array in registers using a array of vector<X, 2>. Requires InElementCount a pair >= 2
  - L1087 _member_ `static const uint VectorSize = InVectorSize;` — Size of each element.
  - L1090 _member_ `static const uint ElementCount = InElementCount;` — Number of elememnts
  - L1093 _member_ `static const uint RegisterRowSize = 2;` — Size and number of register rows
  - L1094 _member_ `static const uint RegisterRowCount = (ElementCount * VectorSize) / 2;`
  - L1096 _member_ `vector<ScalarType, RegisterRowSize> M[RegisterRowCount];`
  - L1096 _member_ `vector<ScalarType, RegisterRowSize> M[RegisterRowCount];`
  - L1101 _method_ `CALL_SITE_DEBUGLOC vector<ScalarType, RegisterRowSize> GetRegisterRow(const uint RegisterRowIndex)`
  - L1107 _method_ `CALL_SITE_DEBUGLOC void SetRegisterRow(const uint RegisterRowIndex, vector<ScalarType, RegisterRowSize> RegisterRow)`
  - L1116 _method_ `CALL_SITE_DEBUGLOC vector<ScalarType, VectorSize> GetElement(const uint ElementIndex)`
  - L1128 _method_ `CALL_SITE_DEBUGLOC void SetElement(const uint ElementIndex, vector<ScalarType, VectorSize> Element)`
  - L1138 _method_ `vector<ScalarType, VectorSize> WaveBroadcastElement(const FWaveBroadcastSettings BroadcastSettings, const uint ElementIndex)`
  - L1174 _method_ `CALL_SITE_DEBUGLOC ScalarType GetElementComponent(const uint ElementIndex, const uint ComponentIndex)`
  - L1181 _method_ `CALL_SITE_DEBUGLOC void SetElementComponent(const uint ElementIndex, const uint ComponentIndex, ScalarType Component)`
- L1190-1273 _struct_ **`FRegisters_SoA_PairArray`** `template<typename ScalarType, uint InVectorSize, uint InElementCount> struct FRegisters_SoA_PairArray` — Stores an array of vector<> as a structure of array in registers using a array of vector<X, 2>. Requires InElementCount a pair >= 2
  - L1194 _member_ `static const uint VectorSize = InVectorSize;` — Size of each element.
  - L1197 _member_ `static const uint ElementCount = InElementCount;` — Number of elememnts
  - L1200 _member_ `static const uint RegisterRowSize = 2;` — Size and number of register rows
  - L1201 _member_ `static const uint RegisterRowCount = (ElementCount * VectorSize) / 2;`
  - L1203 _member_ `vector<ScalarType, RegisterRowSize> M[RegisterRowCount];`
  - L1203 _member_ `vector<ScalarType, RegisterRowSize> M[RegisterRowCount];`
  - L1208 _method_ `CALL_SITE_DEBUGLOC vector<ScalarType, RegisterRowSize> GetRegisterRow(const uint RegisterRowIndex)`
  - L1214 _method_ `CALL_SITE_DEBUGLOC void SetRegisterRow(const uint RegisterRowIndex, vector<ScalarType, RegisterRowSize> RegisterRow)`
  - L1223 _method_ `CALL_SITE_DEBUGLOC vector<ScalarType, VectorSize> GetElement(const uint ElementIndex)`
  - L1235 _method_ `CALL_SITE_DEBUGLOC void SetElement(const uint ElementIndex, vector<ScalarType, VectorSize> Element)`
  - L1245 _method_ `vector<ScalarType, VectorSize> WaveBroadcastElement(const FWaveBroadcastSettings BroadcastSettings, const uint ElementIndex)`
  - L1260 _method_ `CALL_SITE_DEBUGLOC ScalarType GetElementComponent(const uint ElementIndex, const uint ComponentIndex)`
  - L1267 _method_ `CALL_SITE_DEBUGLOC void SetElementComponent(const uint ElementIndex, const uint ComponentIndex, ScalarType Component)`
- L1279-1890 _struct_ **`TLaneVector2D`** `template<typename ScalarType, uint InVectorSize, uint InSimdSizeX, uint InSimdSizeY> struct TLaneVector2D` — Packs a vector<> in 2 dimension.
  - L1283 _member_ `static const uint VectorSize = InVectorSize;` — Size of each element.
  - L1286 _member_ `static const uint SimdSize = InSimdSizeX * InSimdSizeY;` — Number of elememnts
  - L1287 _member_ `static const uint SimdSizeX = InSimdSizeX;`
  - L1288 _member_ `static const uint SimdSizeY = InSimdSizeY;`
  - L1291 _member_ `static const uint RegisterRowSize = TENSOR_REGISTER_LAYOUT<ScalarType, InVectorSize, InSimdSizeX * InSimdSizeY>::RegisterRowSize;` — Size and number of register rows
  - L1291 _member_ `static const uint RegisterRowSize = TENSOR_REGISTER_LAYOUT<ScalarType, InVectorSize, InSimdSizeX * InSimdSizeY>::RegisterRowSize;` — Size and number of register rows
  - L1291 _member_ `static const uint RegisterRowSize = TENSOR_REGISTER_LAYOUT<ScalarType, InVectorSize, InSimdSizeX * InSimdSizeY>::RegisterRowSize;` — Size and number of register rows
  - L1292 _member_ `static const uint RegisterRowCount = TENSOR_REGISTER_LAYOUT<ScalarType, InVectorSize, InSimdSizeX * InSimdSizeY>::RegisterRowCount;`
  - L1292 _member_ `static const uint RegisterRowCount = TENSOR_REGISTER_LAYOUT<ScalarType, InVectorSize, InSimdSizeX * InSimdSizeY>::RegisterRowCount;`
  - L1292 _member_ `static const uint RegisterRowCount = TENSOR_REGISTER_LAYOUT<ScalarType, InVectorSize, InSimdSizeX * InSimdSizeY>::RegisterRowCount;`
  - L1294 _member_ `TENSOR_REGISTER_LAYOUT<ScalarType, InVectorSize, InSimdSizeX * InSimdSizeY> Registers;`
  - L1294 _member_ `TENSOR_REGISTER_LAYOUT<ScalarType, InVectorSize, InSimdSizeX * InSimdSizeY> Registers;`
  - L1294 _member_ `TENSOR_REGISTER_LAYOUT<ScalarType, InVectorSize, InSimdSizeX * InSimdSizeY> Registers;`
  - L1300 _method_ `CALL_SITE_DEBUGLOC vector<ScalarType, VectorSize> GetElement(const uint ElementIndex)` — Access and set individual element of the vector.
  - L1306 _method_ `CALL_SITE_DEBUGLOC void SetElement(const uint ElementIndex, vector<ScalarType, VectorSize> Element)`
  - L1312 _method_ `CALL_SITE_DEBUGLOC void SetAllElements(vector<ScalarType, VectorSize> Element)`
  - L1339 _method_ `CALL_SITE_DEBUGLOC TLaneVector2D<ScalarType, 1, SimdSizeX, SimdSizeY> GetComponent(const uint ComponentIndex)` — Access and set a component of the vector
  - L1366 _method_ `CALL_SITE_DEBUGLOC void SetComponent(uint ComponentIndex, TLaneVector2D<ScalarType, 1, SimdSizeX, SimdSizeY> Comp)`
  - L1391 _method_ `CALL_SITE_DEBUGLOC TLaneVector2D<ScalarType, 1, SimdSizeX, SimdSizeY> operator [](const uint ComponentIndex)`
  - L1401 _method_ `CALL_SITE_DEBUGLOC static TLaneVector2D<ScalarType, VectorSize, SimdSizeX, SimdSizeY> Vectorize( TLaneVector2D<ScalarType, 1, SimdSizeX, SimdSizeY> A)` — Casts a scalar into a vector<>.
  - L1430 _method_ `CALL_SITE_DEBUGLOC static TLaneVector2D<ScalarType, VectorSize, SimdSizeX, SimdSizeY> Const( vector<ScalarType, VectorSize> A)` — Initialize all elements with a single same vector<>.
  - L1459 _method_ `CALL_SITE_DEBUGLOC template<typename SourceScalarType> static TLaneVector2D<ScalarType, VectorSize, SimdSizeX, SimdSizeY> CastFrom( TLaneVector2D<SourceScalarType, VectorSize, SimdSizeX, SimdSizeY> A)` — Casts vector<A> to vector<B>.
  - L1489 _method_ `CALL_SITE_DEBUGLOC void TightenRegisters()` — Force tight register packing.
  - L1523 _method_ `static uint GetLDSSpillDwordSize()` — Returns the LDS spill size in dwords _[#if defined(LDS_DESPILL_DWORD_COUNT)]_
  - L1529 _method_ `CALL_SITE_DEBUGLOC void StoreLDSSpill(const uint DespillDwordOffset)` — Store to LDS spill to save VGPR. _[#if defined(LDS_DESPILL_DWORD_COUNT)]_
  - L1549 _method_ `CALL_SITE_DEBUGLOC static TLaneVector2D<ScalarType, VectorSize, SimdSizeX, SimdSizeY> LoadLDSSpill(const uint DespillDwordOffset)` — Load from LDS spill to save VGPR. _[#if defined(LDS_DESPILL_DWORD_COUNT)]_
  - L1575 _method_ `CALL_SITE_DEBUGLOC TLaneVector2D<ScalarType, VectorSize, SimdSizeX, SimdSizeY> operator + (TLaneVector2D<ScalarType, VectorSize, SimdSizeX, SimdSizeY> B)`
  - L1602 _method_ `CALL_SITE_DEBUGLOC TLaneVector2D<ScalarType, VectorSize, SimdSizeX, SimdSizeY> operator + (vector<ScalarType, VectorSize> B)`
  - L1634 _method_ `CALL_SITE_DEBUGLOC TLaneVector2D<ScalarType, VectorSize, SimdSizeX, SimdSizeY> operator - ()`
  - L1662 _method_ `CALL_SITE_DEBUGLOC TLaneVector2D<ScalarType, VectorSize, SimdSizeX, SimdSizeY> operator - (TLaneVector2D<ScalarType, VectorSize, SimdSizeX, SimdSizeY> B)`
  - L1689 _method_ `CALL_SITE_DEBUGLOC TLaneVector2D<ScalarType, VectorSize, SimdSizeX, SimdSizeY> operator - (vector<ScalarType, VectorSize> B)`
  - L1721 _method_ `CALL_SITE_DEBUGLOC TLaneVector2D<ScalarType, VectorSize, SimdSizeX, SimdSizeY> operator * (TLaneVector2D<ScalarType, VectorSize, SimdSizeX, SimdSizeY> B)`
  - L1748 _method_ `CALL_SITE_DEBUGLOC TLaneVector2D<ScalarType, VectorSize, SimdSizeX, SimdSizeY> operator * (vector<ScalarType, VectorSize> B)`
  - L1779 _method_ `CALL_SITE_DEBUGLOC TLaneVector2D<bool, VectorSize, SimdSizeX, SimdSizeY> operator > (TLaneVector2D<ScalarType, VectorSize, SimdSizeX, SimdSizeY> B)`
  - L1806 _method_ `CALL_SITE_DEBUGLOC TLaneVector2D<bool, VectorSize, SimdSizeX, SimdSizeY> operator < (TLaneVector2D<ScalarType, VectorSize, SimdSizeX, SimdSizeY> B)`
  - L1834 _method_ `CALL_SITE_DEBUGLOC TLaneVector2D<bool, VectorSize, SimdSizeX, SimdSizeY> operator != (TLaneVector2D<ScalarType, VectorSize, SimdSizeX, SimdSizeY> B)`
  - L1862 _method_ `CALL_SITE_DEBUGLOC TLaneVector2D<bool, VectorSize, SimdSizeX, SimdSizeY> operator == (TLaneVector2D<ScalarType, VectorSize, SimdSizeX, SimdSizeY> B)`

#### groupshared (2)

- L676 _groupshared_ `groupshared uint SharedData[LDS_SIZE * LDS_DWORD_COMPONENT_COUNT];` _[#if defined(LDS_SIZE)]_
- L751 _groupshared_ `groupshared uint DespilledData[LDS_DESPILL_DWORD_COUNT];` _[#if defined(LDS_DESPILL_DWORD_COUNT)]_

#### static variables (1)

- L26 _static_var_ `static uint GGroupThreadIndex = 0;`

#### Functions (121)

- L31-34 _function_ `bool not(bool x)`
- L36-39 _function_ `bool2 not(bool2 x)`
- L41-44 _function_ `bool3 not(bool3 x)`
- L46-49 _function_ `bool4 not(bool4 x)`
- L51-54 _function_ `uint bit_not(uint x)`
- L56-59 _function_ `uint2 bit_not(uint2 x)`
- L63-66 _function_ `uint16_t bit_not(uint16_t x)` _[#if PLATFORM_SUPPORTS_REAL_TYPES]_
- L68-71 _function_ `uint16_t2 bit_not(uint16_t2 x)` _[#if PLATFORM_SUPPORTS_REAL_TYPES]_
- L74-77 _function_ `bool2 v_pack_b32_b16(bool a, bool b)`
- L79-82 _function_ `float2 v_pack_b32_b16(float a, float b)`
- L84-87 _function_ `uint2 v_pack_b32_b16(uint a, uint b)`
- L89-92 _function_ `int2 v_pack_b32_b16(int a, int b)`
- L94-97 _function_ `float fast_sign(float x)`
- L99-102 _function_ `float2 fast_sign(float2 x)`
- L106-109 _function_ `half fast_sign(half x)` _[#if PLATFORM_SUPPORTS_REAL_TYPES]_
- L111-114 _function_ `half2 fast_sign(half2 x)` _[#if PLATFORM_SUPPORTS_REAL_TYPES]_
- L118-121 _function_ `uint bit_and(uint a, uint b)`
- L123-126 _function_ `uint2 bit_and(uint2 a, uint2 b)`
- L128-131 _function_ `uint bit_or(uint a, uint b)`
- L133-136 _function_ `uint2 bit_or(uint2 a, uint2 b)`
- L140-143 _function_ `uint16_t bit_and(uint16_t a, uint16_t b)` _[#if PLATFORM_SUPPORTS_REAL_TYPES]_
- L145-148 _function_ `uint16_t2 bit_and(uint16_t2 a, uint16_t2 b)` _[#if PLATFORM_SUPPORTS_REAL_TYPES]_
- L150-153 _function_ `uint16_t bit_or(uint16_t a, uint16_t b)` _[#if PLATFORM_SUPPORTS_REAL_TYPES]_
- L155-158 _function_ `uint16_t2 bit_or(uint16_t2 a, uint16_t2 b)` _[#if PLATFORM_SUPPORTS_REAL_TYPES]_
- L162-165 _function_ `uint bit_shift_left(uint a, uint b)`
- L167-170 _function_ `uint2 bit_shift_left(uint2 a, uint2 b)`
- L172-175 _function_ `uint bit_shift_right(uint a, uint b)`
- L177-180 _function_ `uint2 bit_shift_right(uint2 a, uint2 b)`
- L184-187 _function_ `uint16_t bit_shift_left(uint16_t a, uint16_t b)` _[#if PLATFORM_SUPPORTS_REAL_TYPES]_
- L189-192 _function_ `uint16_t2 bit_shift_left(uint16_t2 a, uint16_t2 b)` _[#if PLATFORM_SUPPORTS_REAL_TYPES]_
- L194-197 _function_ `uint16_t bit_shift_right(uint16_t a, uint16_t b)` _[#if PLATFORM_SUPPORTS_REAL_TYPES]_
- L199-202 _function_ `uint16_t2 bit_shift_right(uint16_t2 a, uint16_t2 b)` _[#if PLATFORM_SUPPORTS_REAL_TYPES]_
- L209-212 _function_ `bool PackRegistersTightly(bool v)`
- L214-217 _function_ `bool2 PackRegistersTightly(bool2 v)`
- L219-222 _function_ `bool3 PackRegistersTightly(bool3 v)`
- L224-227 _function_ `bool4 PackRegistersTightly(bool4 v)`
- L229-232 _function_ `float PackRegistersTightly(float v)`
- L234-237 _function_ `float2 PackRegistersTightly(float2 v)`
- L239-242 _function_ `float3 PackRegistersTightly(float3 v)`
- L244-247 _function_ `float4 PackRegistersTightly(float4 v)`
- L249-252 _function_ `uint PackRegistersTightly(uint v)`
- L254-257 _function_ `uint2 PackRegistersTightly(uint2 v)`
- L259-262 _function_ `uint3 PackRegistersTightly(uint3 v)`
- L264-267 _function_ `uint4 PackRegistersTightly(uint4 v)`
- L269-272 _function_ `int PackRegistersTightly(int v)`
- L274-277 _function_ `int2 PackRegistersTightly(int2 v)`
- L279-282 _function_ `int3 PackRegistersTightly(int3 v)`
- L284-287 _function_ `int4 PackRegistersTightly(int4 v)`
- L292-295 _function_ `half PackRegistersTightly(half v)` _[#if PLATFORM_SUPPORTS_REAL_TYPES]_
- L297-300 _function_ `half2 PackRegistersTightly(half2 v)` _[#if PLATFORM_SUPPORTS_REAL_TYPES]_
- L302-305 _function_ `half3 PackRegistersTightly(half3 v)` _[#if PLATFORM_SUPPORTS_REAL_TYPES]_
- L307-310 _function_ `half4 PackRegistersTightly(half4 v)` _[#if PLATFORM_SUPPORTS_REAL_TYPES]_
- L312-315 _function_ `uint16_t PackRegistersTightly(uint16_t v)` _[#if PLATFORM_SUPPORTS_REAL_TYPES]_
- L317-320 _function_ `uint16_t2 PackRegistersTightly(uint16_t2 v)` _[#if PLATFORM_SUPPORTS_REAL_TYPES]_
- L322-325 _function_ `uint16_t3 PackRegistersTightly(uint16_t3 v)` _[#if PLATFORM_SUPPORTS_REAL_TYPES]_
- L327-330 _function_ `uint16_t4 PackRegistersTightly(uint16_t4 v)` _[#if PLATFORM_SUPPORTS_REAL_TYPES]_
- L332-335 _function_ `int16_t PackRegistersTightly(int16_t v)` _[#if PLATFORM_SUPPORTS_REAL_TYPES]_
- L337-340 _function_ `int16_t2 PackRegistersTightly(int16_t2 v)` _[#if PLATFORM_SUPPORTS_REAL_TYPES]_
- L342-345 _function_ `int16_t3 PackRegistersTightly(int16_t3 v)` _[#if PLATFORM_SUPPORTS_REAL_TYPES]_
- L347-350 _function_ `int16_t4 PackRegistersTightly(int16_t4 v)` _[#if PLATFORM_SUPPORTS_REAL_TYPES]_
- L365-368 _function_ `void PackVectorToDwords(uint V, out uint DW[1])` — uint
- L370-374 _function_ `void PackVectorToDwords(uint2 V, out uint DW[2])`
- L376-381 _function_ `void PackVectorToDwords(uint3 V, out uint DW[3])`
- L383-389 _function_ `void PackVectorToDwords(uint4 V, out uint DW[4])`
- L391-394 _function_ `void UnpackDwordsToVector(uint DW[1], out uint V)`
- L396-400 _function_ `void UnpackDwordsToVector(uint DW[2], out uint2 V)`
- L402-407 _function_ `void UnpackDwordsToVector(uint DW[3], out uint3 V)`
- L409-415 _function_ `void UnpackDwordsToVector(uint DW[4], out uint4 V)`
- L418-421 _function_ `void PackVectorToDwords(float V, out uint DW[1])` — float
- L423-427 _function_ `void PackVectorToDwords(float2 V, out uint DW[2])`
- L429-434 _function_ `void PackVectorToDwords(float3 V, out uint DW[3])`
- L436-442 _function_ `void PackVectorToDwords(float4 V, out uint DW[4])`
- L444-447 _function_ `void UnpackDwordsToVector(uint DW[1], out float V)`
- L449-453 _function_ `void UnpackDwordsToVector(uint DW[2], out float2 V)`
- L455-460 _function_ `void UnpackDwordsToVector(uint DW[3], out float3 V)`
- L462-468 _function_ `void UnpackDwordsToVector(uint DW[4], out float4 V)`
- L475-478 _function_ `void PackVectorToDwords(uint16_t V, out uint DW[1])` — uint16_t _[#if PLATFORM_SUPPORTS_REAL_TYPES && COMPILER_SUPPORT_UINT16_BITCAST]_
- L480-483 _function_ `void PackVectorToDwords(uint16_t2 V, out uint DW[1])` _[#if PLATFORM_SUPPORTS_REAL_TYPES && COMPILER_SUPPORT_UINT16_BITCAST]_
- L485-489 _function_ `void PackVectorToDwords(uint16_t3 V, out uint DW[2])` _[#if PLATFORM_SUPPORTS_REAL_TYPES && COMPILER_SUPPORT_UINT16_BITCAST]_
- L491-495 _function_ `void PackVectorToDwords(uint16_t4 V, out uint DW[2])` _[#if PLATFORM_SUPPORTS_REAL_TYPES && COMPILER_SUPPORT_UINT16_BITCAST]_
- L497-500 _function_ `void UnpackDwordsToVector(uint DW[1], out uint16_t V)` _[#if PLATFORM_SUPPORTS_REAL_TYPES && COMPILER_SUPPORT_UINT16_BITCAST]_
- L502-505 _function_ `void UnpackDwordsToVector(uint DW[1], out uint16_t2 V)` _[#if PLATFORM_SUPPORTS_REAL_TYPES && COMPILER_SUPPORT_UINT16_BITCAST]_
- L507-511 _function_ `void UnpackDwordsToVector(uint DW[2], out uint16_t3 V)` _[#if PLATFORM_SUPPORTS_REAL_TYPES && COMPILER_SUPPORT_UINT16_BITCAST]_
- L513-517 _function_ `void UnpackDwordsToVector(uint DW[2], out uint16_t4 V)` _[#if PLATFORM_SUPPORTS_REAL_TYPES && COMPILER_SUPPORT_UINT16_BITCAST]_
- L522-525 _function_ `void PackVectorToDwords(uint16_t V, out uint DW[1])` — uint16_t _[#if PLATFORM_SUPPORTS_REAL_TYPES && !(COMPILER_SUPPORT_UINT16_BITCAST)]_
- L527-530 _function_ `void PackVectorToDwords(uint16_t2 V, out uint DW[1])` _[#if PLATFORM_SUPPORTS_REAL_TYPES && !(COMPILER_SUPPORT_UINT16_BITCAST)]_
- L532-536 _function_ `void PackVectorToDwords(uint16_t3 V, out uint DW[2])` _[#if PLATFORM_SUPPORTS_REAL_TYPES && !(COMPILER_SUPPORT_UINT16_BITCAST)]_
- L538-542 _function_ `void PackVectorToDwords(uint16_t4 V, out uint DW[2])` _[#if PLATFORM_SUPPORTS_REAL_TYPES && !(COMPILER_SUPPORT_UINT16_BITCAST)]_
- L544-547 _function_ `void UnpackDwordsToVector(uint DW[1], out uint16_t V)` _[#if PLATFORM_SUPPORTS_REAL_TYPES && !(COMPILER_SUPPORT_UINT16_BITCAST)]_
- L549-553 _function_ `void UnpackDwordsToVector(uint DW[1], out uint16_t2 V)` _[#if PLATFORM_SUPPORTS_REAL_TYPES && !(COMPILER_SUPPORT_UINT16_BITCAST)]_
- L555-560 _function_ `void UnpackDwordsToVector(uint DW[2], out uint16_t3 V)` _[#if PLATFORM_SUPPORTS_REAL_TYPES && !(COMPILER_SUPPORT_UINT16_BITCAST)]_
- L562-568 _function_ `void UnpackDwordsToVector(uint DW[2], out uint16_t4 V)` _[#if PLATFORM_SUPPORTS_REAL_TYPES && !(COMPILER_SUPPORT_UINT16_BITCAST)]_
- L573-576 _function_ `void PackVectorToDwords(half V, out uint DW[1])` — half _[#if PLATFORM_SUPPORTS_REAL_TYPES]_
- L578-581 _function_ `void PackVectorToDwords(half2 V, out uint DW[1])` _[#if PLATFORM_SUPPORTS_REAL_TYPES]_
- L583-586 _function_ `void PackVectorToDwords(half3 V, out uint DW[2])` _[#if PLATFORM_SUPPORTS_REAL_TYPES]_
- L588-591 _function_ `void PackVectorToDwords(half4 V, out uint DW[2])` _[#if PLATFORM_SUPPORTS_REAL_TYPES]_
- L593-598 _function_ `void UnpackDwordsToVector(uint DW[1], out half V)` _[#if PLATFORM_SUPPORTS_REAL_TYPES]_
- L600-606 _function_ `void UnpackDwordsToVector(uint DW[1], out half2 V)` _[#if PLATFORM_SUPPORTS_REAL_TYPES]_
- L608-615 _function_ `void UnpackDwordsToVector(uint DW[2], out half3 V)` _[#if PLATFORM_SUPPORTS_REAL_TYPES]_
- L617-625 _function_ `void UnpackDwordsToVector(uint DW[2], out half4 V)` _[#if PLATFORM_SUPPORTS_REAL_TYPES]_
- L632-635 _function_ `uint GetDW(uint DW[1], const uint Index)`
- L637-640 _function_ `uint GetDW(uint DW[2], const uint Index)`
- L642-645 _function_ `uint GetDW(uint DW[3], const uint Index)`
- L647-650 _function_ `uint GetDW(uint DW[4], const uint Index)`
- L652-655 _function_ `void SetDW(inout uint DW[1], const uint Index, uint V)`
- L657-660 _function_ `void SetDW(inout uint DW[2], const uint Index, uint V)`
- L662-665 _function_ `void SetDW(inout uint DW[3], const uint Index, uint V)`
- L667-670 _function_ `void SetDW(inout uint DW[4], const uint Index, uint V)`
- L678-681 _function_ `void WriteDwordToLDS(const uint SharedIndex, uint V)` _[#if defined(LDS_SIZE)]_
- L683-686 _function_ `uint ReadDwordFromLDS(const uint SharedIndex)` _[#if defined(LDS_SIZE)]_
- L688-691 _function_ `void AtomicIncrementLDSDword(const uint SharedIndex, uint V)` _[#if defined(LDS_SIZE)]_
- L693-718 _function_ `template<typename ScalarType, uint VectorSize> void WriteVectorToLDS(const uint SharedIndex, vector<ScalarType, VectorSize> V)` _[#if defined(LDS_SIZE)]_
- L720-743 _function_ `template<typename ScalarType, uint VectorSize> void ReadVectorFromLDS(const uint SharedIndex, out vector<ScalarType, VectorSize> V)` _[#if defined(LDS_SIZE)]_
- L1893-1910 _function_ `CALL_SITE_DEBUGLOC template<uint DestVectorSize, typename ScalarType, uint VectorSize, uint SimdSizeX, uint SimdSizeY> TLaneVector2D<ScalarType, DestVectorSize, SimdSizeX, SimdSizeY> ResizeChannels( TLaneVector2D<ScalarType, VectorSize, SimdSizeX, SimdSizeY> A)`
- L1912-1935 _function_ `CALL_SITE_DEBUGLOC template<typename ScalarType, uint VectorSizeA, uint VectorSizeB, uint SimdSizeX, uint SimdSizeY> TLaneVector2D<ScalarType, VectorSizeA + VectorSizeB, SimdSizeX, SimdSizeY> Concatenate( TLaneVector2D<ScalarType, VectorSizeA, SimdSizeX, SimdSizeY> A, TLaneVector2D<ScalarType, VectorSizeB, SimdSizeX, SimdSizeY> B)`
- L1937-1967 _function_ `CALL_SITE_DEBUGLOC template<typename ScalarType, uint VectorSizeA, uint VectorSizeB, uint VectorSizeC, uint SimdSizeX, uint SimdSizeY> TLaneVector2D<ScalarType, VectorSizeA + VectorSizeB + VectorSizeC, SimdSizeX, SimdSizeY> Concatenate( TLaneVector2D<ScalarType, VectorSizeA, SimdSizeX, SimdSizeY> A, TLaneVector2D<ScalarType, VectorSizeB, SimdSizeX, SimdSizeY> B, TLaneVector2D<ScalarType, VectorSizeC, SimdSizeX, SimdSizeY> C)`
- L1969-1991 _function_ `CALL_SITE_DEBUGLOC template<typename ScalarType, uint VectorSizeA, uint VectorSizeB, uint SimdSizeX, uint SimdSizeY> void Deconcatenate( TLaneVector2D<ScalarType, VectorSizeA + VectorSizeB, SimdSizeX, SimdSizeY> M, out TLaneVector2D<ScalarType, VectorSizeA, SimdSizeX, SimdSizeY> A, out TLaneVector2D<ScalarType, VectorSizeB, SimdSizeX, SimdSizeY> B)`
- L1993-2022 _function_ `CALL_SITE_DEBUGLOC template<typename ScalarType, uint VectorSizeA, uint VectorSizeB, uint VectorSizeC, uint SimdSizeX, uint SimdSizeY> void Deconcatenate( TLaneVector2D<ScalarType, VectorSizeA + VectorSizeB + VectorSizeC, SimdSizeX, SimdSizeY> M, out TLaneVector2D<ScalarType, VectorSizeA, SimdSizeX, SimdSizeY> A, out TLaneVector2D<ScalarType, VectorSizeB, SimdSizeX, SimdSizeY> B, out TLaneVector2D<ScalarType, VectorSizeC, SimdSizeX, SimdSizeY> C)`
- L2197-2220 _function_ `CALL_SITE_DEBUGLOC template<uint VectorSize, uint SimdSizeX, uint SimdSizeY> TLaneVector2D<bool, 1, SimdSizeX, SimdSizeY> AnyElement(TLaneVector2D<bool, VectorSize, SimdSizeX, SimdSizeY> A)`
- L2222-2245 _function_ `CALL_SITE_DEBUGLOC template<uint VectorSize, uint SimdSizeX, uint SimdSizeY> TLaneVector2D<bool, 1, SimdSizeX, SimdSizeY> AllElement(TLaneVector2D<bool, VectorSize, SimdSizeX, SimdSizeY> A)`
- L2247-2268 _function_ `CALL_SITE_DEBUGLOC template<uint VectorSize, uint SimdSizeX, uint SimdSizeY> bool AnyComponent(TLaneVector2D<bool, VectorSize, SimdSizeX, SimdSizeY> A)`

#### Top-level macro invocations (33)

- L2057 _macro_call_ `TVECTOR_FUNCTION_1PARAMS(ScalarType, log)`
- L2058 _macro_call_ `TVECTOR_FUNCTION_1PARAMS(ScalarType, log2)`
- L2059 _macro_call_ `TVECTOR_FUNCTION_1PARAMS(ScalarType, sqrt)`
- L2060 _macro_call_ `TVECTOR_FUNCTION_1PARAMS(ScalarType, rsqrt)`
- L2061 _macro_call_ `TVECTOR_FUNCTION_1PARAMS(ScalarType, exp)`
- L2062 _macro_call_ `TVECTOR_FUNCTION_1PARAMS(ScalarType, rcp)`
- L2063 _macro_call_ `TVECTOR_FUNCTION_1PARAMS(ScalarType, saturate)`
- L2064 _macro_call_ `TVECTOR_FUNCTION_1PARAMS(ScalarType, abs)`
- L2065 _macro_call_ `TVECTOR_FUNCTION_1PARAMS(ScalarType, floor)`
- L2066 _macro_call_ `TVECTOR_FUNCTION_1PARAMS(ScalarType, ceil)`
- L2067 _macro_call_ `TVECTOR_FUNCTION_1PARAMS(ScalarType, round)`
- L2068 _macro_call_ `TVECTOR_FUNCTION_1PARAMS(ScalarType, fast_sign)`
- L2069 _macro_call_ `TVECTOR_FUNCTION_1PARAMS(bool, not)`
- L2070 _macro_call_ `TVECTOR_FUNCTION_1PARAMS(uint, bit_not)`
- L2072 _macro_call_ `TVECTOR_FUNCTION_1PARAMS(uint16_t, asuint16)` _[#if PLATFORM_SUPPORTS_REAL_TYPES]_
- L2075 _macro_call_ `TVECTOR_FUNCTION_1PARAMS_ALIASE_FUNCTION_NAME(uint, asuint, azuint)` — Work around: cannot use keyword asuint and asfloat on struct.
- L2076 _macro_call_ `TVECTOR_FUNCTION_1PARAMS_ALIASE_FUNCTION_NAME(float,asfloat, azfloat)`
- L2109 _macro_call_ `TVECTOR_FUNCTION_2PARAMS(pow)`
- L2110 _macro_call_ `TVECTOR_FUNCTION_2PARAMS(min)`
- L2111 _macro_call_ `TVECTOR_FUNCTION_2PARAMS(max)`
- L2112 _macro_call_ `TVECTOR_FUNCTION_2PARAMS(and_internal)`
- L2113 _macro_call_ `TVECTOR_FUNCTION_2PARAMS(or_internal)`
- L2114 _macro_call_ `TVECTOR_FUNCTION_2PARAMS(bit_and)`
- L2115 _macro_call_ `TVECTOR_FUNCTION_2PARAMS(bit_or)`
- L2116 _macro_call_ `TVECTOR_FUNCTION_2PARAMS(bit_shift_left)`
- L2117 _macro_call_ `TVECTOR_FUNCTION_2PARAMS(bit_shift_right)`
- L2151 _macro_call_ `TVECTOR_FUNCTION_2PARAMS_DIFF_RETURN( 1, dot)`
- L2185 _macro_call_ `TVECTOR_FUNCTION_3PARAMS(select_internal, bool)`
- L2186 _macro_call_ `TVECTOR_FUNCTION_3PARAMS(clamp, ScalarType)`
- L2187 _macro_call_ `TVECTOR_FUNCTION_3PARAMS(lerp, ScalarType)`
- L2188 _macro_call_ `TVECTOR_FUNCTION_3PARAMS(min3, ScalarType)`
- L2189 _macro_call_ `TVECTOR_FUNCTION_3PARAMS(max3, ScalarType)`
- L2191 _macro_call_ `TVECTOR_FUNCTION_3PARAMS(med3, ScalarType)` _[#if COMPILER_SUPPORTS_MED3]_

### `Shaders/Public/NvidiaExtensionsCommon.ush` (Public)

- lines: 8; parse: all-branches
- includes: L7 `/Engine/Shared/ThirdParty/NVIDIA/nvHLSLExtns.h`

#### Macros (#define, 1)

- L5 `#define NV_HITOBJECT_USE_MACRO_API `
- L3 #pragma `once`

### `Shaders/Public/OverloadMacros.ush` (Public)

- lines: 27; parse: all-branches

#### Macros (#define, 3)

- L11 `#define DECLARE_VECTOR_FUNCTION_OVERLOAD_1_PARAM(FunctionName,Type) Type##2 FunctionName(Type##2 v) { return Type##2(FunctionName(v.x), FunctionName(v.y)); } Type##3 FunctionName(Type##3 v) { return Type##3(FunctionName(v.xy), FunctionName(v.z)); } Type##4 FunctionNam ...` (4 lines)
- L17 `#define DECLARE_VECTOR_FUNCTION_OVERLOAD_2_PARAM(FunctionName,Type) Type##2 FunctionName(Type##2 a, Type##2 b) { return Type##2(FunctionName(a.x , b.x ), FunctionName(a.y , b.y )); } Type##3 FunctionName(Type##3 a, Type##3 b) { return Type##3(FunctionName(a.xy, b.xy), ...` (4 lines)
- L23 `#define DECLARE_VECTOR_FUNCTION_OVERLOAD_3_PARAM(FunctionName,Type) Type##2 FunctionName(Type##2 a, Type##2 b, Type##2 c) { return Type##2(FunctionName(a.x , b.x , c.x ), FunctionName(a.y , b.y , c.y )); } Type##3 FunctionName(Type##3 a, Type##3 b, Type##3 c) { return ...` (4 lines)
- L8 #pragma `once`

### `Shaders/Public/Platform.ush` (Public)

- lines: 1557; parse: all-branches
- includes: L9 `FP16Math.ush`, L54 `/Platform/Public/PlatformCommon.ush` [defined(OVERRIDE_PLATFORMCOMMON_USH)], L57 `Platform/Metal/MetalCommon.ush` [!(defined(OVERRIDE_PLATFORMCOMMON_USH)) && COMPILER_METAL], L60 `Platform/Vulkan/VulkanCommon.ush` [!(defined(OVERRIDE_PLATFORMCOMMON_USH)) && !(COMPILER_METAL) && COMPILER_VULKAN], L63 `Platform/GL/GLCommon.ush` [!(defined(OVERRIDE_PLATFORMCOMMON_USH)) && !(COMPILER_METAL) && !(COMPILER_VULKAN) && COMPILER_GLSL \|\| COMPILER_GLSL_ES3_1], L65 `Platform/D3D/D3DCommon.ush` [!(defined(OVERRIDE_PLATFORMCOMMON_USH)) && !(COMPILER_METAL) && !(COMPILER_VULKAN) && !(COMPILER_GLSL \|\| COMPILER_GLSL_ES3_1) && COMPILER_HLSL], L68 `/Engine/Public/BindlessResources.ush`, L69 `/Engine/Shared/MaterialCacheDefinitions.h`, L70 `/Engine/Public/IndirectVirtualTexture.ush`, L71 `/Engine/Public/OverloadMacros.ush`, L76 `ShaderVersion.ush`, L635 `NvidiaExtensionsCommon.ush` [!defined(PLATFORM_SUPPORTS_SHADER_TIMESTAMP) && USE_NVAPI_TIMESTAMP]

#### Macros (#define, 352)

- L12 `#define FEATURE_LEVEL_ES2_REMOVED 1`
- L13 `#define FEATURE_LEVEL_ES3_1 2`
- L14 `#define FEATURE_LEVEL_SM3 3`
- L15 `#define FEATURE_LEVEL_SM4 4`
- L16 `#define FEATURE_LEVEL_SM5 5`
- L17 `#define FEATURE_LEVEL_SM6 6`
- L18 `#define FEATURE_LEVEL_MAX 7`
- L21 `#define PLATFORM_GPU_ARCH_UNKNOWN 0x0000`
- L23 `#define PLATFORM_GPU_ARCH_AMD 0x1000`
- L24 `#define PLATFORM_GPU_ARCH_AMD_GCN_1 0x1010`
- L25 `#define PLATFORM_GPU_ARCH_AMD_GCN_2 0x1020`
- L26 `#define PLATFORM_GPU_ARCH_AMD_GCN_3 0x1030`
- L27 `#define PLATFORM_GPU_ARCH_AMD_GCN_4 0x1040`
- L28 `#define PLATFORM_GPU_ARCH_AMD_GCN_5 0x1050`
- L29 `#define PLATFORM_GPU_ARCH_AMD_RDNA_1 0x1110`
- L30 `#define PLATFORM_GPU_ARCH_AMD_RDNA_2 0x1120`
- L31 `#define PLATFORM_GPU_ARCH_AMD_RDNA_3 0x1130`
- L32 `#define PLATFORM_GPU_ARCH_AMD_LATTEST PLATFORM_GPU_ARCH_AMD_RDNA_3`
- L34 `#define PLATFORM_GPU_ARCH_NVIDIA 0x2000`
- L35 `#define PLATFORM_GPU_ARCH_NVIDIA_KEPLER 0x2010`
- L36 `#define PLATFORM_GPU_ARCH_NVIDIA_MAXWELL 0x2020`
- L37 `#define PLATFORM_GPU_ARCH_NVIDIA_PASCAL 0x2030`
- L38 `#define PLATFORM_GPU_ARCH_NVIDIA_VOLTA 0x2040`
- L39 `#define PLATFORM_GPU_ARCH_NVIDIA_TURING 0x2050`
- L40 `#define PLATFORM_GPU_ARCH_NVIDIA_AMPERE 0x2060`
- L41 `#define PLATFORM_GPU_ARCH_NVIDIA_ADA 0x2070`
- L42 `#define PLATFORM_GPU_ARCH_NVIDIA_LATTEST PLATFORM_GPU_ARCH_NVIDIA_ADA`
- L44 `#define PLATFORM_GPU_ARCH_INTEL 0x3000`
- L45 `#define PLATFORM_GPU_ARCH_INTEL_ARC 0x3010`
- L46 `#define PLATFORM_GPU_ARCH_INTEL_LATTEST PLATFORM_GPU_ARCH_INTEL_ARC`
- L82 `#define COMPILER_HLSLCC 0` _[#if !defined(COMPILER_HLSLCC)]_
- L86 `#define COMPILER_DXC 0` _[#if !defined(COMPILER_DXC)]_
- L90 `#define COMPILER_FXC 0` _[#if !defined(COMPILER_FXC)]_
- L94 `#define COMPILER_HLSL 0` _[#if !defined(COMPILER_HLSL)]_
- L98 `#define COMPILER_PSSL 0` _[#if !defined(COMPILER_PSSL)]_
- L102 `#define COMPILER_GLSL 0` _[#if !defined(COMPILER_GLSL)]_
- L106 `#define COMPILER_GLSL_ES3_1 0` _[#if !defined(COMPILER_GLSL_ES3_1)]_
- L110 `#define COMPILER_METAL 0` _[#if !defined(COMPILER_METAL)]_
- L114 `#define COMPILER_SUPPORTS_ATTRIBUTES 0` _[#if !defined(COMPILER_SUPPORTS_ATTRIBUTES)]_
- L118 `#define COMPILER_SUPPORTS_QUAD_PASS 0` _[#if !defined(COMPILER_SUPPORTS_QUAD_PASS)]_
- L122 `#define COMPILER_SUPPORTS_DUAL_SOURCE_BLENDING_SLOT_DECORATION 0` _[#if !defined(COMPILER_SUPPORTS_DUAL_SOURCE_BLENDING_SLOT_DECORATION)]_
- L126 `#define COMPILER_SUPPORTS_PRIMITIVE_SHADERS 0` _[#if !defined(COMPILER_SUPPORTS_PRIMITIVE_SHADERS)]_
- L130 `#define COMPILER_SUPPORTS_BARYCENTRIC_INTRINSICS 0` _[#if !defined(COMPILER_SUPPORTS_BARYCENTRIC_INTRINSICS)]_
- L135 `#define COMPILER_SUPPORTS_WAVE_SIZE 0` _[#if !defined(COMPILER_SUPPORTS_WAVE_SIZE)]_
- L139 `#define COMPILER_SUPPORTS_WAVE_MATCH_INTRINSICS 0` _[#if !defined(COMPILER_SUPPORTS_WAVE_MATCH_INTRINSICS)]_
- L143 `#define COMPILER_FORCE_WAVE32_MODE ` _[#if !defined(COMPILER_FORCE_WAVE32_MODE)]_
- L147 `#define COMPILER_ALLOW_CS_DERIVATIVES ` _[#if !defined(COMPILER_ALLOW_CS_DERIVATIVES)]_
- L151 `#define COMPILER_ALLOW_NON_UNIFORM_DESCRIPTORS ` _[#if !defined(COMPILER_ALLOW_NON_UNIFORM_DESCRIPTORS)]_
- L155 `#define PLATFORM_REQUIRES_UNWRAPPED_MESH_SHADER_ARGS 0` _[#if !defined(PLATFORM_REQUIRES_UNWRAPPED_MESH_SHADER_ARGS)]_
- L159 `#define PLATFORM_SUPPORTS_ROV 0` _[#if !defined(PLATFORM_SUPPORTS_ROV)]_
- L163 `#define RasterizerOrderedTexture2D RWTexture2D` _[#if !PLATFORM_SUPPORTS_ROV]_
- L167 `#define SM6_PROFILE 0` _[#if !defined(SM6_PROFILE)]_
- L171 `#define SM5_PROFILE 0` _[#if !defined(SM5_PROFILE)]_
- L175 `#define OPENGL_PROFILE 0` _[#if !defined(OPENGL_PROFILE)]_
- L179 `#define ES3_1_PROFILE 0` _[#if !defined(ES3_1_PROFILE)]_
- L183 `#define METAL_ES3_1_PROFILE 0` _[#if !defined(METAL_ES3_1_PROFILE)]_
- L188 `#define METAL_PROFILE METAL_ES3_1_PROFILE` _[#if !defined(METAL_PROFILE)]_
- L192 `#define METAL_SM5_IOS_TVOS_PROFILE 0` _[#if !defined(METAL_SM5_IOS_TVOS_PROFILE)]_
- L197 `#define METAL_MRT_PROFILE METAL_SM5_IOS_TVOS_PROFILE` _[#if !defined(METAL_MRT_PROFILE)]_
- L201 `#define METAL_SM5_PROFILE 0` _[#if !defined(METAL_SM5_PROFILE)]_
- L205 `#define METAL_SM6_PROFILE 0` _[#if !defined(METAL_SM6_PROFILE)]_
- L209 `#define COMPILER_VULKAN 0` _[#if !defined(COMPILER_VULKAN)]_
- L213 `#define VULKAN_PROFILE 0` _[#if !defined(VULKAN_PROFILE)]_
- L217 `#define VULKAN_PROFILE_SM5 0` _[#if !defined(VULKAN_PROFILE_SM5)]_
- L221 `#define VULKAN_PROFILE_SM6 0` _[#if !defined(VULKAN_PROFILE_SM6)]_
- L225 `#define IOS 0` _[#if !defined(IOS)]_
- L229 `#define MAC 0` _[#if !defined(MAC)]_
- L233 `#define VECTORVM_PROFILE 0` _[#if !defined(VECTORVM_PROFILE)]_
- L237 `#define IR_LANGUAGE_DXBC 0` _[#if !defined(IR_LANGUAGE_DXBC)]_
- L248 `#define PLATFORM_SUPPORTS_CALLABLE_SHADERS 0` _[#if !defined(PLATFORM_SUPPORTS_CALLABLE_SHADERS)]_
- L254 `#define PLATFORM_SUPPORTS_SM6_0_WAVE_OPERATIONS 0` _[#if !defined(PLATFORM_SUPPORTS_SM6_0_WAVE_OPERATIONS)]_
- L258 `#define PLATFORM_SUPPORTS_REAL_TYPES 0` _[#if !defined(PLATFORM_SUPPORTS_REAL_TYPES)]_
- L262 `#define PLATFORM_SUPPORTS_RELAXED_PRECISION 0` _[#if !defined(PLATFORM_SUPPORTS_RELAXED_PRECISION)]_
- L266 `#define COMPILER_SUPPORTS_WAVE_32_64_MODE 0` _[#if !defined(COMPILER_SUPPORTS_WAVE_32_64_MODE)]_
- L271 `#define PLATFORM_SUPPORTS_EDITOR_SHADERS 1` _[#if !defined(PLATFORM_SUPPORTS_EDITOR_SHADERS)]_
- L275 `#define COMPILER_SUPPORTS_HLSL2021 0` _[#if !defined(COMPILER_SUPPORTS_HLSL2021)]_
- L279 `#define PLATFORM_SUPPORTS_CONSTANTBUFFER_OBJECT 0` _[#if !defined(PLATFORM_SUPPORTS_CONSTANTBUFFER_OBJECT)]_
- L283 `#define PLATFORM_SUPPORTS_UNIFORM_BUFFER_OBJECTS 0` _[#if !defined(PLATFORM_SUPPORTS_UNIFORM_BUFFER_OBJECTS)]_
- L287 `#define PLATFORM_GPU_ARCH PLATFORM_GPU_ARCH_UNKNOWN` _[#if !defined(PLATFORM_GPU_ARCH)]_
- L291 `#define PLATFORM_NEEDS_DEPTH_TEXTURE_READS 0` _[#if !defined(PLATFORM_NEEDS_DEPTH_TEXTURE_READS)]_
- L295 `#define PLATFORM_NEEDS_SELECT_UINT 0` _[#if !defined(PLATFORM_NEEDS_SELECT_UINT)]_
- L299 `#define PLATFORM_NEEDS_SEPARATE_SHADOW_DEPTH_CUBE_TEXTURE 0` _[#if !defined(PLATFORM_NEEDS_SEPARATE_SHADOW_DEPTH_CUBE_TEXTURE)]_
- L303 `#define PLATFORM_SUPPORTS_SUBSTRATE_UINT1 1` _[#if !defined(PLATFORM_SUPPORTS_SUBSTRATE_UINT1)]_
- L307 `#define COMPILER_NEEDS_DETERMINANT 0` _[#if !defined(COMPILER_NEEDS_DETERMINANT)]_
- L312 `#define SHADER_PUSH_WARNINGS_STATE _Pragma("dxc diagnostic push")` _[#if COMPILER_DXC == 1]_
- L313 `#define SHADER_POP_WARNINGS_STATE _Pragma("dxc diagnostic pop")` _[#if COMPILER_DXC == 1]_
- L316 `#define SHADER_DISABLE_WARNINGS _Pragma("dxc diagnostic ignored \"-Wall\"") _Pragma("dxc diagnostic ignored \"-Wconversion\"") _Pragma("dxc diagnostic ignored \"-Wfor-redefinition\"") _Pragma("dxc diagnostic ignored \"-Winline-asm\" ...` (6 lines) _[#if COMPILER_DXC == 1]_
- L327 `#define SHADER_DISABLE_WARNINGS ` _[#if !defined(SHADER_DISABLE_WARNINGS)]_
- L331 `#define SHADER_PUSH_WARNINGS_STATE ` _[#if !defined(SHADER_PUSH_WARNINGS_STATE)]_
- L335 `#define SHADER_POP_WARNINGS_STATE ` _[#if !defined(SHADER_POP_WARNINGS_STATE)]_
- L341 `#define FORCE_FLOATS 0` _[#if !defined(FORCE_FLOATS)]_
- L349 `#define half min16float` _[#if !FORCE_FLOATS && PLATFORM_SUPPORTS_RELAXED_PRECISION]_
- L350 `#define half1 min16float1` _[#if !FORCE_FLOATS && PLATFORM_SUPPORTS_RELAXED_PRECISION]_
- L351 `#define half2 min16float2` _[#if !FORCE_FLOATS && PLATFORM_SUPPORTS_RELAXED_PRECISION]_
- L352 `#define half3 min16float3` _[#if !FORCE_FLOATS && PLATFORM_SUPPORTS_RELAXED_PRECISION]_
- L353 `#define half4 min16float4` _[#if !FORCE_FLOATS && PLATFORM_SUPPORTS_RELAXED_PRECISION]_
- L354 `#define half3x3 min16float3x3` _[#if !FORCE_FLOATS && PLATFORM_SUPPORTS_RELAXED_PRECISION]_
- L355 `#define half3x4 min16float3x4` _[#if !FORCE_FLOATS && PLATFORM_SUPPORTS_RELAXED_PRECISION]_
- L356 `#define half4x4 min16float4x4` _[#if !FORCE_FLOATS && PLATFORM_SUPPORTS_RELAXED_PRECISION]_
- L358 `#define half float` _[#if !(!FORCE_FLOATS && PLATFORM_SUPPORTS_RELAXED_PRECISION) && FORCE_FLOATS \|\| !PLATFORM_SUPPORTS_REAL_TYPES]_
- L359 `#define half1 float1` _[#if !(!FORCE_FLOATS && PLATFORM_SUPPORTS_RELAXED_PRECISION) && FORCE_FLOATS \|\| !PLATFORM_SUPPORTS_REAL_TYPES]_
- L360 `#define half2 float2` _[#if !(!FORCE_FLOATS && PLATFORM_SUPPORTS_RELAXED_PRECISION) && FORCE_FLOATS \|\| !PLATFORM_SUPPORTS_REAL_TYPES]_
- L361 `#define half3 float3` _[#if !(!FORCE_FLOATS && PLATFORM_SUPPORTS_RELAXED_PRECISION) && FORCE_FLOATS \|\| !PLATFORM_SUPPORTS_REAL_TYPES]_
- L362 `#define half4 float4` _[#if !(!FORCE_FLOATS && PLATFORM_SUPPORTS_RELAXED_PRECISION) && FORCE_FLOATS \|\| !PLATFORM_SUPPORTS_REAL_TYPES]_
- L363 `#define half3x3 float3x3` _[#if !(!FORCE_FLOATS && PLATFORM_SUPPORTS_RELAXED_PRECISION) && FORCE_FLOATS \|\| !PLATFORM_SUPPORTS_REAL_TYPES]_
- L364 `#define half4x4 float4x4` _[#if !(!FORCE_FLOATS && PLATFORM_SUPPORTS_RELAXED_PRECISION) && FORCE_FLOATS \|\| !PLATFORM_SUPPORTS_REAL_TYPES]_
- L365 `#define half4x3 float4x3` _[#if !(!FORCE_FLOATS && PLATFORM_SUPPORTS_RELAXED_PRECISION) && FORCE_FLOATS \|\| !PLATFORM_SUPPORTS_REAL_TYPES]_
- L366 `#define fixed float` _[#if !(!FORCE_FLOATS && PLATFORM_SUPPORTS_RELAXED_PRECISION) && FORCE_FLOATS \|\| !PLATFORM_SUPPORTS_REAL_TYPES]_
- L367 `#define fixed1 float1` _[#if !(!FORCE_FLOATS && PLATFORM_SUPPORTS_RELAXED_PRECISION) && FORCE_FLOATS \|\| !PLATFORM_SUPPORTS_REAL_TYPES]_
- L368 `#define fixed2 float2` _[#if !(!FORCE_FLOATS && PLATFORM_SUPPORTS_RELAXED_PRECISION) && FORCE_FLOATS \|\| !PLATFORM_SUPPORTS_REAL_TYPES]_
- L369 `#define fixed3 float3` _[#if !(!FORCE_FLOATS && PLATFORM_SUPPORTS_RELAXED_PRECISION) && FORCE_FLOATS \|\| !PLATFORM_SUPPORTS_REAL_TYPES]_
- L370 `#define fixed4 float4` _[#if !(!FORCE_FLOATS && PLATFORM_SUPPORTS_RELAXED_PRECISION) && FORCE_FLOATS \|\| !PLATFORM_SUPPORTS_REAL_TYPES]_
- L371 `#define fixed3x3 float3x3` _[#if !(!FORCE_FLOATS && PLATFORM_SUPPORTS_RELAXED_PRECISION) && FORCE_FLOATS \|\| !PLATFORM_SUPPORTS_REAL_TYPES]_
- L372 `#define fixed4x4 float4x4` _[#if !(!FORCE_FLOATS && PLATFORM_SUPPORTS_RELAXED_PRECISION) && FORCE_FLOATS \|\| !PLATFORM_SUPPORTS_REAL_TYPES]_
- L373 `#define fixed4x3 float4x3` _[#if !(!FORCE_FLOATS && PLATFORM_SUPPORTS_RELAXED_PRECISION) && FORCE_FLOATS \|\| !PLATFORM_SUPPORTS_REAL_TYPES]_
- L381 `#define FEATURE_LEVEL FEATURE_LEVEL_SM6` _[#if SM6_PROFILE]_
- L385 `#define FEATURE_LEVEL FEATURE_LEVEL_SM5` _[#if !(SM6_PROFILE) && SM5_PROFILE]_
- L391 `#define FEATURE_LEVEL FEATURE_LEVEL_SM5` _[#if !(SM6_PROFILE) && !(SM5_PROFILE) && SWITCH_PROFILE \|\| SWITCH_PROFILE_FORWARD && SWITCH_PROFILE]_
- L393 `#define FEATURE_LEVEL FEATURE_LEVEL_ES3_1` _[#if !(SM6_PROFILE) && !(SM5_PROFILE) && SWITCH_PROFILE \|\| SWITCH_PROFILE_FORWARD && !(SWITCH_PROFILE)]_
- L395 `#define ES3_1_PROFILE 1` _[#if !(SM6_PROFILE) && !(SM5_PROFILE) && SWITCH_PROFILE \|\| SWITCH_PROFILE_FORWARD && !(SWITCH_PROFILE)]_
- L399 `#define FEATURE_LEVEL FEATURE_LEVEL_ES3_1` _[#if !(SM6_PROFILE) && !(SM5_PROFILE) && !(SWITCH_PROFILE \|\| SWITCH_PROFILE_FORWARD) && VULKAN_PROFILE]_
- L402 `#define ES3_1_PROFILE 1` _[#if !(SM6_PROFILE) && !(SM5_PROFILE) && !(SWITCH_PROFILE \|\| SWITCH_PROFILE_FORWARD) && VULKAN_PROFILE]_
- L405 `#define FEATURE_LEVEL FEATURE_LEVEL_SM5` _[#if !(SM6_PROFILE) && !(SM5_PROFILE) && !(SWITCH_PROFILE \|\| SWITCH_PROFILE_FORWARD) && !(VULKAN_PROFILE) && VULKAN_PROFILE_SM5]_
- L406 `#define STENCIL_COMPONENT_SWIZZLE .x` _[#if !(SM6_PROFILE) && !(SM5_PROFILE) && !(SWITCH_PROFILE \|\| SWITCH_PROFILE_FORWARD) && !(VULKAN_PROFILE) && VULKAN_PROFILE_SM5]_
- L409 `#define FEATURE_LEVEL FEATURE_LEVEL_SM6` _[#if !(SM6_PROFILE) && !(SM5_PROFILE) && !(SWITCH_PROFILE \|\| SWITCH_PROFILE_FORWARD) && !(VULKAN_PROFILE) && !(VULKAN_PROFILE_SM5) && VULKAN_PROFILE_SM6]_
- L410 `#define STENCIL_COMPONENT_SWIZZLE .x` _[#if !(SM6_PROFILE) && !(SM5_PROFILE) && !(SWITCH_PROFILE \|\| SWITCH_PROFILE_FORWARD) && !(VULKAN_PROFILE) && !(VULKAN_PROFILE_SM5) && VULKAN_PROFILE_SM6]_
- L413 `#define FEATURE_LEVEL FEATURE_LEVEL_ES3_1` _[#if !(SM6_PROFILE) && !(SM5_PROFILE) && !(SWITCH_PROFILE \|\| SWITCH_PROFILE_FORWARD) && !(VULKAN_PROFILE) && !(VULKAN_PROFILE_SM5) && !(VULKAN_PROFILE_SM6) && METAL_ES3_1_PROFILE]_
- L416 `#define ES3_1_PROFILE 1` _[#if !(SM6_PROFILE) && !(SM5_PROFILE) && !(SWITCH_PROFILE \|\| SWITCH_PROFILE_FORWARD) && !(VULKAN_PROFILE) && !(VULKAN_PROFILE_SM5) && !(VULKAN_PROFILE_SM6) && METAL_ES3_1_PROFILE]_
- L417 `#define FCOLOR_COMPONENT_SWIZZLE .rgba` _[#if !(SM6_PROFILE) && !(SM5_PROFILE) && !(SWITCH_PROFILE \|\| SWITCH_PROFILE_FORWARD) && !(VULKAN_PROFILE) && !(VULKAN_PROFILE_SM5) && !(VULKAN_PROFILE_SM6) && METAL_ES3_1_PROFILE]_
- L418 `#define FMANUALFETCH_COLOR_COMPONENT_SWIZZLE .bgra` _[#if !(SM6_PROFILE) && !(SM5_PROFILE) && !(SWITCH_PROFILE \|\| SWITCH_PROFILE_FORWARD) && !(VULKAN_PROFILE) && !(VULKAN_PROFILE_SM5) && !(VULKAN_PROFILE_SM6) && METAL_ES3_1_PROFILE]_
- L419 `#define STENCIL_COMPONENT_SWIZZLE .x` _[#if !(SM6_PROFILE) && !(SM5_PROFILE) && !(SWITCH_PROFILE \|\| SWITCH_PROFILE_FORWARD) && !(VULKAN_PROFILE) && !(VULKAN_PROFILE_SM5) && !(VULKAN_PROFILE_SM6) && METAL_ES3_1_PROFILE]_
- L422 `#define FEATURE_LEVEL FEATURE_LEVEL_SM5` _[#if !(SM6_PROFILE) && !(SM5_PROFILE) && !(SWITCH_PROFILE \|\| SWITCH_PROFILE_FORWARD) && !(VULKAN_PROFILE) && !(VULKAN_PROFILE_SM5) && !(VULKAN_PROFILE_SM6) && !(METAL_ES3_1_PROFILE) && METAL_SM5_IOS_TVO...]_
- L423 `#define FCOLOR_COMPONENT_SWIZZLE .rgba` _[#if !(SM6_PROFILE) && !(SM5_PROFILE) && !(SWITCH_PROFILE \|\| SWITCH_PROFILE_FORWARD) && !(VULKAN_PROFILE) && !(VULKAN_PROFILE_SM5) && !(VULKAN_PROFILE_SM6) && !(METAL_ES3_1_PROFILE) && METAL_SM5_IOS_TVO...]_
- L424 `#define FMANUALFETCH_COLOR_COMPONENT_SWIZZLE .bgra` _[#if !(SM6_PROFILE) && !(SM5_PROFILE) && !(SWITCH_PROFILE \|\| SWITCH_PROFILE_FORWARD) && !(VULKAN_PROFILE) && !(VULKAN_PROFILE_SM5) && !(VULKAN_PROFILE_SM6) && !(METAL_ES3_1_PROFILE) && METAL_SM5_IOS_TVO...]_
- L425 `#define STENCIL_COMPONENT_SWIZZLE .x` _[#if !(SM6_PROFILE) && !(SM5_PROFILE) && !(SWITCH_PROFILE \|\| SWITCH_PROFILE_FORWARD) && !(VULKAN_PROFILE) && !(VULKAN_PROFILE_SM5) && !(VULKAN_PROFILE_SM6) && !(METAL_ES3_1_PROFILE) && METAL_SM5_IOS_TVO...]_
- L428 `#define FEATURE_LEVEL FEATURE_LEVEL_SM5` _[#if !(SM6_PROFILE) && !(SM5_PROFILE) && !(SWITCH_PROFILE \|\| SWITCH_PROFILE_FORWARD) && !(VULKAN_PROFILE) && !(VULKAN_PROFILE_SM5) && !(VULKAN_PROFILE_SM6) && !(METAL_ES3_1_PROFILE) && !(METAL_SM5_IOS_T...]_
- L429 `#define FCOLOR_COMPONENT_SWIZZLE .rgba` _[#if !(SM6_PROFILE) && !(SM5_PROFILE) && !(SWITCH_PROFILE \|\| SWITCH_PROFILE_FORWARD) && !(VULKAN_PROFILE) && !(VULKAN_PROFILE_SM5) && !(VULKAN_PROFILE_SM6) && !(METAL_ES3_1_PROFILE) && !(METAL_SM5_IOS_T...]_
- L430 `#define FMANUALFETCH_COLOR_COMPONENT_SWIZZLE .bgra` _[#if !(SM6_PROFILE) && !(SM5_PROFILE) && !(SWITCH_PROFILE \|\| SWITCH_PROFILE_FORWARD) && !(VULKAN_PROFILE) && !(VULKAN_PROFILE_SM5) && !(VULKAN_PROFILE_SM6) && !(METAL_ES3_1_PROFILE) && !(METAL_SM5_IOS_T...]_
- L431 `#define STENCIL_COMPONENT_SWIZZLE .x` _[#if !(SM6_PROFILE) && !(SM5_PROFILE) && !(SWITCH_PROFILE \|\| SWITCH_PROFILE_FORWARD) && !(VULKAN_PROFILE) && !(VULKAN_PROFILE_SM5) && !(VULKAN_PROFILE_SM6) && !(METAL_ES3_1_PROFILE) && !(METAL_SM5_IOS_T...]_
- L434 `#define FEATURE_LEVEL FEATURE_LEVEL_SM6` _[#if !(SM6_PROFILE) && !(SM5_PROFILE) && !(SWITCH_PROFILE \|\| SWITCH_PROFILE_FORWARD) && !(VULKAN_PROFILE) && !(VULKAN_PROFILE_SM5) && !(VULKAN_PROFILE_SM6) && !(METAL_ES3_1_PROFILE) && !(METAL_SM5_IOS_T...]_
- L435 `#define FCOLOR_COMPONENT_SWIZZLE .rgba` _[#if !(SM6_PROFILE) && !(SM5_PROFILE) && !(SWITCH_PROFILE \|\| SWITCH_PROFILE_FORWARD) && !(VULKAN_PROFILE) && !(VULKAN_PROFILE_SM5) && !(VULKAN_PROFILE_SM6) && !(METAL_ES3_1_PROFILE) && !(METAL_SM5_IOS_T...]_
- L436 `#define FMANUALFETCH_COLOR_COMPONENT_SWIZZLE .bgra` _[#if !(SM6_PROFILE) && !(SM5_PROFILE) && !(SWITCH_PROFILE \|\| SWITCH_PROFILE_FORWARD) && !(VULKAN_PROFILE) && !(VULKAN_PROFILE_SM5) && !(VULKAN_PROFILE_SM6) && !(METAL_ES3_1_PROFILE) && !(METAL_SM5_IOS_T...]_
- L437 `#define STENCIL_COMPONENT_SWIZZLE .x` _[#if !(SM6_PROFILE) && !(SM5_PROFILE) && !(SWITCH_PROFILE \|\| SWITCH_PROFILE_FORWARD) && !(VULKAN_PROFILE) && !(VULKAN_PROFILE_SM5) && !(VULKAN_PROFILE_SM6) && !(METAL_ES3_1_PROFILE) && !(METAL_SM5_IOS_T...]_
- L440 `#define FEATURE_LEVEL FEATURE_LEVEL_ES3_1` _[#if !(SM6_PROFILE) && !(SM5_PROFILE) && !(SWITCH_PROFILE \|\| SWITCH_PROFILE_FORWARD) && !(VULKAN_PROFILE) && !(VULKAN_PROFILE_SM5) && !(VULKAN_PROFILE_SM6) && !(METAL_ES3_1_PROFILE) && !(METAL_SM5_IOS_T...]_
- L443 `#define FCOLOR_COMPONENT_SWIZZLE .bgra` _[#if !(SM6_PROFILE) && !(SM5_PROFILE) && !(SWITCH_PROFILE \|\| SWITCH_PROFILE_FORWARD) && !(VULKAN_PROFILE) && !(VULKAN_PROFILE_SM5) && !(VULKAN_PROFILE_SM6) && !(METAL_ES3_1_PROFILE) && !(METAL_SM5_IOS_T...]_
- L444 `#define FMANUALFETCH_COLOR_COMPONENT_SWIZZLE .bgra` _[#if !(SM6_PROFILE) && !(SM5_PROFILE) && !(SWITCH_PROFILE \|\| SWITCH_PROFILE_FORWARD) && !(VULKAN_PROFILE) && !(VULKAN_PROFILE_SM5) && !(VULKAN_PROFILE_SM6) && !(METAL_ES3_1_PROFILE) && !(METAL_SM5_IOS_T...]_
- L446 `#define FCOLOR_COMPONENT_SWIZZLE .rgba` _[#if !(SM6_PROFILE) && !(SM5_PROFILE) && !(SWITCH_PROFILE \|\| SWITCH_PROFILE_FORWARD) && !(VULKAN_PROFILE) && !(VULKAN_PROFILE_SM5) && !(VULKAN_PROFILE_SM6) && !(METAL_ES3_1_PROFILE) && !(METAL_SM5_IOS_T...]_
- L447 `#define FMANUALFETCH_COLOR_COMPONENT_SWIZZLE .bgra` _[#if !(SM6_PROFILE) && !(SM5_PROFILE) && !(SWITCH_PROFILE \|\| SWITCH_PROFILE_FORWARD) && !(VULKAN_PROFILE) && !(VULKAN_PROFILE_SM5) && !(VULKAN_PROFILE_SM6) && !(METAL_ES3_1_PROFILE) && !(METAL_SM5_IOS_T...]_
- L452 `#define A8_SAMPLE_MASK .r` _[#if !(SM6_PROFILE) && !(SM5_PROFILE) && !(SWITCH_PROFILE \|\| SWITCH_PROFILE_FORWARD) && !(VULKAN_PROFILE) && !(VULKAN_PROFILE_SM5) && !(VULKAN_PROFILE_SM6) && !(METAL_ES3_1_PROFILE) && !(METAL_SM5_IOS_T...]_
- L455 `#define FEATURE_LEVEL FEATURE_LEVEL_SM5` _[#if !(SM6_PROFILE) && !(SM5_PROFILE) && !(SWITCH_PROFILE \|\| SWITCH_PROFILE_FORWARD) && !(VULKAN_PROFILE) && !(VULKAN_PROFILE_SM5) && !(VULKAN_PROFILE_SM6) && !(METAL_ES3_1_PROFILE) && !(METAL_SM5_IOS_T...]_
- L461 `#define FEATURE_LEVEL FEATURE_LEVEL_MAX` _[#if !defined(FEATURE_LEVEL)]_
- L468 `#define A8_SAMPLE_MASK .r` _[#if COMPILER_METAL]_
- L476 `#define FCOLOR_COMPONENT_SWIZZLE .rgba` _[#if !defined(FCOLOR_COMPONENT_SWIZZLE)]_
- L480 `#define FMANUALFETCH_COLOR_COMPONENT_SWIZZLE .bgra` _[#if !defined(FMANUALFETCH_COLOR_COMPONENT_SWIZZLE)]_
- L484 `#define STENCIL_COMPONENT_SWIZZLE .g` _[#if !defined(STENCIL_COMPONENT_SWIZZLE)]_
- L488 `#define A8_SAMPLE_MASK .a` _[#if !defined(A8_SAMPLE_MASK)]_
- L496 `#define UB_INT(Dim) int##Dim` _[#if (FEATURE_LEVEL == FEATURE_LEVEL_ES3_1)]_
- L497 `#define UB_UINT(Dim) uint##Dim` _[#if (FEATURE_LEVEL == FEATURE_LEVEL_ES3_1)]_
- L498 `#define UB_FLOAT(Dim) float##Dim` _[#if (FEATURE_LEVEL == FEATURE_LEVEL_ES3_1)]_
- L500 `#define UB_HALF_FLOAT(Dim) float##Dim` _[#if (FEATURE_LEVEL == FEATURE_LEVEL_ES3_1) && METAL_ES3_1_PROFILE \|\| COMPILER_HLSL]_
- L502 `#define UB_HALF_FLOAT(Dim) half##Dim` _[#if (FEATURE_LEVEL == FEATURE_LEVEL_ES3_1) && !(METAL_ES3_1_PROFILE \|\| COMPILER_HLSL)]_
- L504 `#define UB_FIXED_FLOAT(Dim) fixed##Dim` _[#if (FEATURE_LEVEL == FEATURE_LEVEL_ES3_1)]_
- L506 `#define UB_INT(Dim) int##Dim` _[#if !((FEATURE_LEVEL == FEATURE_LEVEL_ES3_1))]_
- L507 `#define UB_UINT(Dim) uint##Dim` _[#if !((FEATURE_LEVEL == FEATURE_LEVEL_ES3_1))]_
- L508 `#define UB_FLOAT(Dim) float##Dim` _[#if !((FEATURE_LEVEL == FEATURE_LEVEL_ES3_1))]_
- L509 `#define UB_HALF_FLOAT(Dim) float##Dim` _[#if !((FEATURE_LEVEL == FEATURE_LEVEL_ES3_1))]_
- L510 `#define UB_FIXED_FLOAT(Dim) float##Dim` _[#if !((FEATURE_LEVEL == FEATURE_LEVEL_ES3_1))]_
- L515 `#define PLATFORM_MAX_UNIFORM_BUFFER_RANGE (16u*1024u)` _[#if !defined(PLATFORM_MAX_UNIFORM_BUFFER_RANGE)]_
- L517 `#define PLATFORM_MAX_UNIFORM_BUFFER_RANGE_FLOAT4 (PLATFORM_MAX_UNIFORM_BUFFER_RANGE/16u)`
- L522 `#define UB_CB_DEFINITION_START( UBName ) cbuffer UBName {`
- L523 `#define UB_CB_DEFINITION_START_REG( UBName, Register, Space ) cbuffer UBName : register(b##Register, space##Space) {`
- L524 `#define UB_CB_MEMBER_NAME( UBName, MemberName) UBName##_##MemberName`
- L525 `#define UB_CB_PREFIXED_MEMBER_NAME( UBName, Prefix, MemberName) Prefix##UBName##_##MemberName`
- L526 `#define UB_CB_DEFINITION_END( UBName ) }`
- L527 `#define UB_CB_FINALIZE( UBName ) `
- L528 `#define UB_CB_FINALIZE_REG( UBName, Register, Space ) `
- L529 `#define UB_CB_MEMBER_ACCESS( UBName, MemberName) UBName##_##MemberName`
- L530 `#define UB_CB_PREFIXED_MEMBER_ACCESS(UBName, Prefix, MemberName) Prefix##UBName##_##MemberName`
- L532 `#define UB_CB_REMAP_PARAMETER(UBName, StructName, GlobalName) UBName##.##StructName = UBName##_##GlobalName`
- L533 `#define UB_CB_REMAP_RESOURCE(UBName, StructName, GlobalName) UBName##.##StructName = UBName##_##GlobalName`
- L535 `#define UB_CB_UNIFORM_BLOCK(UBName, MemberName) UB_FLOAT(4) UB_CB_MEMBER_NAME(UBName,MemberName)[PLATFORM_MAX_UNIFORM_BUFFER_RANGE_FLOAT4]`
- L538 `#define UB_CBO_TYPE(UBName) F##UBName##Constants` _[#if PLATFORM_SUPPORTS_CONSTANTBUFFER_OBJECT]_
- L540 `#define UB_CBO_DEFINITION_START( UBName ) struct UB_CBO_TYPE(UBName) {` _[#if PLATFORM_SUPPORTS_CONSTANTBUFFER_OBJECT]_
- L541 `#define UB_CBO_DEFINITION_START_REG( UBName, Register, Space ) UB_CBO_DEFINITION_START(UBName)` _[#if PLATFORM_SUPPORTS_CONSTANTBUFFER_OBJECT]_
- L542 `#define UB_CBO_MEMBER_NAME( UBName, MemberName) MemberName` _[#if PLATFORM_SUPPORTS_CONSTANTBUFFER_OBJECT]_
- L543 `#define UB_CBO_PREFIXED_MEMBER_NAME( UBName, Prefix, MemberName) Prefix##MemberName` _[#if PLATFORM_SUPPORTS_CONSTANTBUFFER_OBJECT]_
- L544 `#define UB_CBO_DEFINITION_END( UBName ) };` _[#if PLATFORM_SUPPORTS_CONSTANTBUFFER_OBJECT]_
- L545 `#define UB_CBO_FINALIZE( UBName ) ConstantBuffer<UB_CBO_TYPE(UBName)> UBName;` _[#if PLATFORM_SUPPORTS_CONSTANTBUFFER_OBJECT]_
- L546 `#define UB_CBO_FINALIZE_REG( UBName, Register, Space ) ConstantBuffer<UB_CBO_TYPE(UBName)> UBName : register(b##Register, space##Space);` _[#if PLATFORM_SUPPORTS_CONSTANTBUFFER_OBJECT]_
- L547 `#define UB_CBO_MEMBER_ACCESS( UBName, MemberName) UBName##.##MemberName` _[#if PLATFORM_SUPPORTS_CONSTANTBUFFER_OBJECT]_
- L548 `#define UB_CBO_PREFIXED_MEMBER_ACCESS(UBName, Prefix, MemberName) UBName##.##Prefix##MemberName` _[#if PLATFORM_SUPPORTS_CONSTANTBUFFER_OBJECT]_
- L550 `#define UB_CBO_REMAP_PARAMETER(UBName, StructName, GlobalName) UBName##.##StructName = UBName##.##GlobalName` _[#if PLATFORM_SUPPORTS_CONSTANTBUFFER_OBJECT]_
- L551 `#define UB_CBO_REMAP_RESOURCE(UBName, StructName, GlobalName) UBName##.##StructName = UBName##_##GlobalName` _[#if PLATFORM_SUPPORTS_CONSTANTBUFFER_OBJECT]_
- L553 `#define UB_CBO_UNIFORM_BLOCK(UBName, MemberName) UB_FLOAT(4) UB_CBO_MEMBER_NAME(UBName,MemberName)[PLATFORM_MAX_UNIFORM_BUFFER_RANGE_FLOAT4]` _[#if PLATFORM_SUPPORTS_CONSTANTBUFFER_OBJECT]_
- L556 `#define UB_CBO_DEFINITION_START( UBName ) UB_CB_DEFINITION_START(UBName)` _[#if !(PLATFORM_SUPPORTS_CONSTANTBUFFER_OBJECT)]_
- L557 `#define UB_CBO_DEFINITION_START_REG( UBName, Register, Space ) UB_CB_DEFINITION_START_REG(UBName,Register,Space)` _[#if !(PLATFORM_SUPPORTS_CONSTANTBUFFER_OBJECT)]_
- L558 `#define UB_CBO_MEMBER_NAME( UBName, MemberName) UB_CB_MEMBER_NAME(UBName,MemberName)` _[#if !(PLATFORM_SUPPORTS_CONSTANTBUFFER_OBJECT)]_
- L559 `#define UB_CBO_PREFIXED_MEMBER_NAME( UBName, Prefix, MemberName) UB_CB_PREFIXED_MEMBER_NAME(UBName,Prefix,MemberName)` _[#if !(PLATFORM_SUPPORTS_CONSTANTBUFFER_OBJECT)]_
- L560 `#define UB_CBO_DEFINITION_END( UBName ) UB_CB_DEFINITION_END(UBName)` _[#if !(PLATFORM_SUPPORTS_CONSTANTBUFFER_OBJECT)]_
- L561 `#define UB_CBO_FINALIZE( UBName ) UB_CB_FINALIZE(UBName)` _[#if !(PLATFORM_SUPPORTS_CONSTANTBUFFER_OBJECT)]_
- L562 `#define UB_CBO_FINALIZE_REG( UBName, Register, Space ) UB_CB_FINALIZE_REG(UBName,Register,Space)` _[#if !(PLATFORM_SUPPORTS_CONSTANTBUFFER_OBJECT)]_
- L563 `#define UB_CBO_MEMBER_ACCESS( UBName, MemberName) UB_CB_MEMBER_ACCESS(UBName,MemberName)` _[#if !(PLATFORM_SUPPORTS_CONSTANTBUFFER_OBJECT)]_
- L564 `#define UB_CBO_PREFIXED_MEMBER_ACCESS(UBName, Prefix, MemberName) UB_CB_PREFIXED_MEMBER_ACCESS(UBName,Prefix,MemberName)` _[#if !(PLATFORM_SUPPORTS_CONSTANTBUFFER_OBJECT)]_
- L566 `#define UB_CBO_REMAP_PARAMETER(UBName, StructName, GlobalName) UB_CB_REMAP_PARAMETER(UBName,StructName,GlobalName)` _[#if !(PLATFORM_SUPPORTS_CONSTANTBUFFER_OBJECT)]_
- L567 `#define UB_CBO_REMAP_RESOURCE( UBName, StructName, GlobalName) UB_CB_REMAP_RESOURCE(UBName,StructName,GlobalName)` _[#if !(PLATFORM_SUPPORTS_CONSTANTBUFFER_OBJECT)]_
- L569 `#define UB_CBO_UNIFORM_BLOCK(UBName, MemberName) UB_CB_UNIFORM_BLOCK(UBName, MemberName)` _[#if !(PLATFORM_SUPPORTS_CONSTANTBUFFER_OBJECT)]_
- L574 `#define SV_ClipDistance OUTCLIPDIST` _[#if !PLATFORM_SUPPORTS_CLIP_DISTANCE]_
- L579 `#define PLATFORM_SUPPORTS_DEVELOPMENT_SHADERS 1` _[#if !defined(PLATFORM_SUPPORTS_DEVELOPMENT_SHADERS)]_
- L583 `#define MOBILE_EMULATION 0` _[#if !defined(MOBILE_EMULATION)]_
- L590 `#define SUPPORTS_INDEPENDENT_SAMPLERS 0` _[#if !defined(SUPPORTS_INDEPENDENT_SAMPLERS)]_
- L594 `#define SUPPORTS_PIXEL_COVERAGE (FEATURE_LEVEL >= FEATURE_LEVEL_SM5 && !COMPILER_GLSL && !MOBILE_EMULATION)`
- L599 `#define PLATFORM_SUPPORTS_4COMPONENT_UAV_READ_WRITE (XBOXONE_PROFILE \|\| COMPILER_METAL)` _[#if !defined(PLATFORM_SUPPORTS_4COMPONENT_UAV_READ_WRITE)]_
- L606 `#define PLATFORM_SUPPORTS_VERTEX_SHADER_SRVS 1` _[#if !defined(PLATFORM_SUPPORTS_VERTEX_SHADER_SRVS)]_
- L611 `#define PLATFORM_SUPPORTS_VERTEX_SHADER_UAVS 0` _[#if !defined(PLATFORM_SUPPORTS_VERTEX_SHADER_UAVS)]_
- L615 `#define PLATFORM_SUPPORTS_RAYTRACING_CLUSTER_OPS 0` _[#if !defined(PLATFORM_SUPPORTS_RAYTRACING_CLUSTER_OPS)]_
- L622 `#define PLATFORM_BREAK() ` _[#if !defined(PLATFORM_BREAK)]_
- L626 `#define PLATFORM_ASSERT(condition, assert_id) ` _[#if !defined(PLATFORM_ASSERT)]_
- L627 `#define PLATFORM_ASSERT1(condition, assert_id, a) ` _[#if !defined(PLATFORM_ASSERT)]_
- L628 `#define PLATFORM_ASSERT2(condition, assert_id, a, b) ` _[#if !defined(PLATFORM_ASSERT)]_
- L629 `#define PLATFORM_ASSERT3(condition, assert_id, a, b, c) ` _[#if !defined(PLATFORM_ASSERT)]_
- L630 `#define PLATFORM_ASSERT4(condition, assert_id, a, b, c, d) ` _[#if !defined(PLATFORM_ASSERT)]_
- L637 `#define PLATFORM_SUPPORTS_SHADER_TIMESTAMP 1` _[#if !defined(PLATFORM_SUPPORTS_SHADER_TIMESTAMP) && USE_NVAPI_TIMESTAMP]_
- L639 `#define FTimestamp uint` _[#if !defined(PLATFORM_SUPPORTS_SHADER_TIMESTAMP) && USE_NVAPI_TIMESTAMP]_
- L652 `#define PLATFORM_SUPPORTS_SHADER_TIMESTAMP 0` _[#if !defined(PLATFORM_SUPPORTS_SHADER_TIMESTAMP) && !(USE_NVAPI_TIMESTAMP)]_
- L658 `#define uniform ` _[#if COMPILER_HLSLCC]_
- L663 `#define COMPILER_SUPPORTS_WAVE_ONCE 1` _[#if PLATFORM_SUPPORTS_SM6_0_WAVE_OPERATIONS && !defined(COMPILER_SUPPORTS_WAVE_ONCE)]_
- L666 `#define COMPILER_SUPPORTS_WAVE_VOTE 1` _[#if PLATFORM_SUPPORTS_SM6_0_WAVE_OPERATIONS && !defined(COMPILER_SUPPORTS_WAVE_VOTE)]_
- L669 `#define COMPILER_SUPPORTS_WAVE_MINMAX 1` _[#if PLATFORM_SUPPORTS_SM6_0_WAVE_OPERATIONS && !defined(COMPILER_SUPPORTS_WAVE_MINMAX)]_
- L672 `#define COMPILER_SUPPORTS_WAVE_BIT_ORAND 1` _[#if PLATFORM_SUPPORTS_SM6_0_WAVE_OPERATIONS && !defined(COMPILER_SUPPORTS_WAVE_BIT_ORAND)]_
- L681 `#define COMPILER_SUPPORTS_WAVE_ONCE 0` _[#if !defined(COMPILER_SUPPORTS_WAVE_ONCE)]_
- L689 `#define COMPILER_SUPPORTS_WAVE_VOTE 0` _[#if !defined(COMPILER_SUPPORTS_WAVE_VOTE)]_
- L700 `#define COMPILER_SUPPORTS_WAVE_MINMAX 0` _[#if !defined(COMPILER_SUPPORTS_WAVE_MINMAX)]_
- L707 `#define COMPILER_SUPPORTS_WAVE_BIT_ORAND 0` _[#if !defined(COMPILER_SUPPORTS_WAVE_BIT_ORAND)]_
- L713 `#define COMPILER_SUPPORTS_WAVE_SWIZZLE_GCN 0` _[#if !defined(COMPILER_SUPPORTS_WAVE_SWIZZLE_GCN)]_
- L717 `#define COMPILER_SUPPORTS_WAVE_PERMUTE 0` _[#if !defined(COMPILER_SUPPORTS_WAVE_PERMUTE)]_
- L721 `#define COMPILER_SUPPORTS_WAVE_READCROSSLANE 0` _[#if !defined(COMPILER_SUPPORTS_WAVE_READCROSSLANE)]_
- L726 `#define COMPILER_SUPPORTS_PRIMITIVE_SHADERS 0` _[#if !defined(COMPILER_SUPPORTS_PRIMITIVE_SHADERS)]_
- L731 `#define PLATFORM_SUPPORTS_RECT_LIST 0` _[#if !defined(PLATFORM_SUPPORTS_RECT_LIST)]_
- L736 `#define PLATFORM_SUPPORTS_ATOMIC_UINT64 0` _[#if !defined(PLATFORM_SUPPORTS_ATOMIC_UINT64)]_
- L741 `#define COMPILER_SUPPORTS_DEPTHSTENCIL_EARLYTEST_LATEWRITE 0` _[#if !defined(COMPILER_SUPPORTS_DEPTHSTENCIL_EARLYTEST_LATEWRITE)]_
- L745 `#define COMPILER_SUPPORTS_SHADER_YIELD 0` _[#if !defined(COMPILER_SUPPORTS_SHADER_YIELD)]_
- L753 `#define COMPILER_SUPPORTS_GATHER_LOD_RED 0` _[#if !defined(COMPILER_SUPPORTS_GATHER_LOD_RED)]_
- L757 `#define COMPILER_SUPPORTS_GATHER_UINT 0` _[#if !defined(COMPILER_SUPPORTS_GATHER_UINT)]_
- L761 `#define COMPILER_SUPPORTS_MED3 0` _[#if !defined(COMPILER_SUPPORTS_MED3)]_
- L765 `#define HALF_TYPE half` _[#if (ES3_1_PROFILE && !METAL_ES3_1_PROFILE) \|\| VULKAN_PROFILE_SM5]_
- L766 `#define HALF2_TYPE half2` _[#if (ES3_1_PROFILE && !METAL_ES3_1_PROFILE) \|\| VULKAN_PROFILE_SM5]_
- L767 `#define HALF3_TYPE half3` _[#if (ES3_1_PROFILE && !METAL_ES3_1_PROFILE) \|\| VULKAN_PROFILE_SM5]_
- L768 `#define HALF4_TYPE half4` _[#if (ES3_1_PROFILE && !METAL_ES3_1_PROFILE) \|\| VULKAN_PROFILE_SM5]_
- L770 `#define HALF_TYPE float` _[#if !((ES3_1_PROFILE && !METAL_ES3_1_PROFILE) \|\| VULKAN_PROFILE_SM5)]_
- L771 `#define HALF2_TYPE float2` _[#if !((ES3_1_PROFILE && !METAL_ES3_1_PROFILE) \|\| VULKAN_PROFILE_SM5)]_
- L772 `#define HALF3_TYPE float3` _[#if !((ES3_1_PROFILE && !METAL_ES3_1_PROFILE) \|\| VULKAN_PROFILE_SM5)]_
- L773 `#define HALF4_TYPE float4` _[#if !((ES3_1_PROFILE && !METAL_ES3_1_PROFILE) \|\| VULKAN_PROFILE_SM5)]_
- L781 `#define UNROLL [unroll]` _[#if SM6_PROFILE \|\| SM5_PROFILE \|\| COMPILER_SUPPORTS_ATTRIBUTES]_
- L782 `#define UNROLL_N(N) [unroll(N)]` _[#if SM6_PROFILE \|\| SM5_PROFILE \|\| COMPILER_SUPPORTS_ATTRIBUTES]_
- L785 `#define LOOP [loop]` _[#if SM6_PROFILE \|\| SM5_PROFILE \|\| COMPILER_SUPPORTS_ATTRIBUTES]_
- L788 `#define BRANCH [branch]` _[#if SM6_PROFILE \|\| SM5_PROFILE \|\| COMPILER_SUPPORTS_ATTRIBUTES]_
- L791 `#define FLATTEN [flatten]` _[#if SM6_PROFILE \|\| SM5_PROFILE \|\| COMPILER_SUPPORTS_ATTRIBUTES]_
- L794 `#define ALLOW_UAV_CONDITION [allow_uav_condition]` _[#if SM6_PROFILE \|\| SM5_PROFILE \|\| COMPILER_SUPPORTS_ATTRIBUTES]_
- L801 `#define EARLYDEPTHSTENCIL [earlydepthstencil]` _[#if !defined(EARLYDEPTHSTENCIL) && SM6_PROFILE \|\| SM5_PROFILE \|\| METAL_SM5_IOS_TVOS_PROFILE \|\| METAL_SM5_PROFILE \|\| METAL_SM6_PROFILE \|\| ES3_1_PROFILE \|\| VULKAN_PROFILE_SM5 \|\| VULKAN_PROFILE_SM6]_
- L806 `#define DUAL_SOURCE_BLENDING_SLOT(SLOT) [[vk::location(0), vk::index(SLOT)]]` _[#if COMPILER_SUPPORTS_DUAL_SOURCE_BLENDING_SLOT_DECORATION]_
- L812 `#define UNROLL ` _[#if !defined(UNROLL)]_
- L816 `#define UNROLL_N(N) ` _[#if !defined(UNROLL_N)]_
- L820 `#define LOOP ` _[#if !defined(LOOP)]_
- L824 `#define BRANCH ` _[#if !defined(BRANCH)]_
- L828 `#define FLATTEN ` _[#if !defined(FLATTEN)]_
- L832 `#define ALLOW_UAV_CONDITION ` _[#if !defined(ALLOW_UAV_CONDITION)]_
- L840 `#define INVARIANT(X) MakePrecise(X)` _[#if !defined(INVARIANT)]_
- L844 `#define INVARIANT_ADD(Lhs, Rhs) INVARIANT((Lhs) + (Rhs))` _[#if !defined(INVARIANT_ADD)]_
- L848 `#define INVARIANT_SUB(Lhs, Rhs) INVARIANT((Lhs) - (Rhs))` _[#if !defined(INVARIANT_SUB)]_
- L852 `#define INVARIANT_MUL(Lhs, Rhs) INVARIANT((Lhs) * (Rhs))` _[#if !defined(INVARIANT_MUL)]_
- L856 `#define INVARIANT_DIV(Lhs, Rhs) INVARIANT((Lhs) / (Rhs))` _[#if !defined(INVARIANT_DIV)]_
- L860 `#define INVARIANT_FMA(A, B, C) INVARIANT(FMA((A), (B), (C)))` _[#if !defined(INVARIANT_FMA)]_
- L864 `#define INVARIANT_OUTPUT ` _[#if !defined(INVARIANT_OUTPUT)]_
- L868 `#define PLATFORM_SUPPORTS_FMA 1` _[#if !defined(PLATFORM_SUPPORTS_FMA)]_
- L869 `#define FMA(a, b, c) mad(a, b, c)` _[#if !defined(PLATFORM_SUPPORTS_FMA)]_
- L873 `#define ENABLE_RE_Z ` _[#if !defined(ENABLE_RE_Z)]_
- L877 `#define COMPILER_SUPPORTS_NOINLINE 0` _[#if !defined(COMPILER_SUPPORTS_NOINLINE)]_
- L887 `#define NOINLINE [noinline]` _[#if COMPILER_SUPPORTS_NOINLINE]_
- L889 `#define NOINLINE ` _[#if !(COMPILER_SUPPORTS_NOINLINE)]_
- L893 `#define EARLYDEPTHSTENCIL ` _[#if !defined(EARLYDEPTHSTENCIL)]_
- L897 `#define DUAL_SOURCE_BLENDING_SLOT(SLOT) ` _[#if !defined(DUAL_SOURCE_BLENDING_SLOT)]_
- L901 `#define DEPTHSTENCIL_EARLYTEST_LATEWRITE ` _[#if !defined(DEPTHSTENCIL_EARLYTEST_LATEWRITE)]_
- L905 `#define STRONG_TYPE ` _[#if !defined(STRONG_TYPE)]_
- L909 `#define StrongTypedBuffer Buffer` _[#if !defined(StrongTypedBuffer)]_
- L913 `#define RWCoherentBuffer(TYPE) globallycoherent RWBuffer<TYPE>` _[#if !defined(RWCoherentBuffer)]_
- L917 `#define RWCoherentStructuredBuffer(TYPE) globallycoherent RWStructuredBuffer<TYPE>` _[#if !defined(RWCoherentStructuredBuffer)]_
- L922 `#define RWCoherentStructuredBufferRef(TYPE) RWStructuredBuffer<TYPE>` _[#if !defined(RWCoherentStructuredBufferRef)]_
- L926 `#define RWCoherentByteAddressBuffer globallycoherent RWByteAddressBuffer` _[#if !defined(RWCoherentByteAddressBuffer)]_
- L931 `#define RWCoherentByteAddressBufferRef RWByteAddressBuffer` _[#if !defined(RWCoherentByteAddressBufferRef)]_
- L936 `#define COMPILER_NEEDS_GLOBALLYCOHERENT_LOCALS 0` _[#if !defined(COMPILER_NEEDS_GLOBALLYCOHERENT_LOCALS)]_
- L940 `#define ISOLATE ` _[#if !defined(ISOLATE)]_
- L944 `#define HOIST_DESCRIPTORS ` _[#if !defined(HOIST_DESCRIPTORS)]_
- L948 `#define CALL_SITE_DEBUGLOC ` _[#if !defined(CALL_SITE_DEBUGLOC)]_
- L952 `#define NO_LICM ` _[#if !defined(NO_LICM)]_
- L956 `#define SCHEDULER_MIN_PRESSURE ` _[#if !defined(SCHEDULER_MIN_PRESSURE)]_
- L960 `#define MAX_OCCUPANCY ` _[#if !defined(MAX_OCCUPANCY)]_
- L964 `#define DISABLE_TARGET_OCCUPANCY_WARNING ` _[#if !defined(DISABLE_TARGET_OCCUPANCY_WARNING)]_
- L968 `#define DISABLE_POTENTIALLY_UNINITIALIZED_WARNING ` _[#if !defined(DISABLE_POTENTIALLY_UNINITIALIZED_WARNING)]_
- L972 `#define ALLOW_NO_PS_EXPORT ` _[#if !defined(ALLOW_NO_PS_EXPORT)]_
- L976 `#define ADAPTIVE_LICM ` _[#if !defined(ADAPTIVE_LICM)]_
- L982 `#define COMPRESSED_16_FLOAT ` _[#if !defined(COMPRESSED_16_FLOAT)]_
- L986 `#define COMPRESSED_16_UNORM ` _[#if !defined(COMPRESSED_16_UNORM)]_
- L990 `#define COMPRESSED_16_SNORM ` _[#if !defined(COMPRESSED_16_SNORM)]_
- L994 `#define COMPRESSED_16_UINT ` _[#if !defined(COMPRESSED_16_UINT)]_
- L998 `#define COMPRESSED_16_INT ` _[#if !defined(COMPRESSED_16_INT)]_
- L1002 `#define COMPRESSED_8_UNORM ` _[#if !defined(COMPRESSED_8_UNORM)]_
- L1006 `#define COMPRESSED_8_SNORM ` _[#if !defined(COMPRESSED_8_SNORM)]_
- L1010 `#define COMPRESSED_8_UINT ` _[#if !defined(COMPRESSED_8_UINT)]_
- L1014 `#define CUSTOM_INTERPOLATION nointerpolation` _[#if !defined(CUSTOM_INTERPOLATION)]_
- L1019 `#define USE_DEVELOPMENT_SHADERS (COMPILE_SHADERS_FOR_DEVELOPMENT && PLATFORM_SUPPORTS_DEVELOPMENT_SHADERS)`
- L1025 `#define DISPATCH_INDIRECT_NO_PADDING_UINT_COUNT 3`
- L1032 `#define DISPATCH_INDIRECT_UINT_COUNT DISPATCH_INDIRECT_NO_PADDING_UINT_COUNT` _[#if !defined(DISPATCH_INDIRECT_UINT_COUNT)]_
- L1048 `#define DRAW_INDIRECT_UINT_COUNT 4`
- L1059 `#define DRAW_INDEXED_INDIRECT_UINT_COUNT 5`
- L1085 `#define log10(x) log((x)) / log(10.0)` _[#if COMPILER_HLSLCC]_
- L1176 `#define select(cond,a,b) select_internal(cond,a,b)`
- L1177 `#define DEFINE_SELECT(TYPE) TYPE select_internal(bool c, TYPE a, TYPE b) { return TYPE (c ? a.x : b.x); } TYPE##2 select_internal(bool c, TYPE a, TYPE##2 b) { return TYPE##2(c ? a : b.x, c ? a : b.y); } TYPE##2 select_internal(b ...` (27 lines)
- L1232 `#define and(a, b) and_internal(a, b)`
- L1233 `#define or(a, b) or_internal(a, b)`
- L1283 `#define COMPILER_SUPPORTS_BITFIELD_INTRINSICS 0` _[#if !defined(COMPILER_SUPPORTS_BITFIELD_INTRINSICS)]_
- L1322 `#define COMPILER_SUPPORTS_24BIT_INTRINSICS 0` _[#if !defined(COMPILER_SUPPORTS_24BIT_INTRINSICS)]_
- L1366 `#define COMPILER_SUPPORTS_BITALIGN 0` _[#if !defined(COMPILER_SUPPORTS_BITALIGN)]_
- L1378 `#define COMPILER_SUPPORTS_BYTEALIGN 0` _[#if !defined(COMPILER_SUPPORTS_BYTEALIGN)]_
- L1386 `#define ddx_fine(x) ddx(x)` _[#if COMPILER_HLSLCC]_
- L1387 `#define ddy_fine(y) ddy(y)` _[#if COMPILER_HLSLCC]_
- L1392 `#define UlongType uint2` _[#if !defined(COMPILER_SUPPORTS_ULONG_TYPES)]_
- L1422 `#define RASTER_ORDERED_VIEW_LOCK() ` _[#if !defined(RASTER_ORDERED_VIEW_LOCK)]_
- L1427 `#define RASTER_ORDERED_VIEW_UNLOCK() ` _[#if !defined(RASTER_ORDERED_VIEW_UNLOCK)]_
- L1433 `#define COMPILER_SUPPORTS_TO_SCALAR_MEMORY 1` _[#if PLATFORM_SUPPORTS_SM6_0_WAVE_OPERATIONS && !defined(COMPILER_SUPPORTS_TO_SCALAR_MEMORY)]_
- L1434 `#define ToScalarMemory(x) WaveReadLaneFirst(x)` _[#if PLATFORM_SUPPORTS_SM6_0_WAVE_OPERATIONS && !defined(COMPILER_SUPPORTS_TO_SCALAR_MEMORY)]_
- L1438 `#define COMPILER_SUPPORTS_MASKED_BIT_COUNT 1` _[#if PLATFORM_SUPPORTS_SM6_0_WAVE_OPERATIONS && !defined(COMPILER_SUPPORTS_MASKED_BIT_COUNT)]_
- L1481 `#define WaveReadLaneLast(x) WaveReadLaneAt( x, WaveGetActiveLaneIndexLast() )` _[#if PLATFORM_SUPPORTS_SM6_0_WAVE_OPERATIONS && !defined(WaveReadLaneLast)]_
- L1487 `#define COMPILER_SUPPORTS_WAVE_INCLUSIVE_PREFIX_SUM 0` _[#if !defined(COMPILER_SUPPORTS_WAVE_INCLUSIVE_PREFIX_SUM)]_
- L1488 `#define WaveInclusivePrefixSum(x) (WavePrefixSum(x) + x)` _[#if !defined(COMPILER_SUPPORTS_WAVE_INCLUSIVE_PREFIX_SUM)]_
- L1493 `#define ToScalarMemory(x) (x)` _[#if !defined(ToScalarMemory) && !defined(COMPILER_SUPPORTS_TO_SCALAR_MEMORY)]_
- L1498 `#define uint4 int4` _[#if FEATURE_LEVEL < FEATURE_LEVEL_ES3_1 && !COMPILER_METAL]_
- L1503 `#define SNORM ` _[#if !defined(SNORM) && COMPILER_HLSLCC]_
- L1504 `#define UNORM ` _[#if !defined(SNORM) && COMPILER_HLSLCC]_
- L1506 `#define SNORM snorm` _[#if !defined(SNORM) && !(COMPILER_HLSLCC)]_
- L1507 `#define UNORM unorm` _[#if !defined(SNORM) && !(COMPILER_HLSLCC)]_
- L1513 `#define INFINITE_FLOAT 3.402823e+38` _[#if !defined(INFINITE_FLOAT) && COMPILER_HLSLCC]_
- L1515 `#define INFINITE_FLOAT 1.#INF` _[#if !defined(INFINITE_FLOAT) && !(COMPILER_HLSLCC)]_
- L1520 `#define RWTextureCube RWTexture2DArray` _[#if !defined(RWTextureCube)]_
- L1524 `#define PLATFORM_NEEDS_PRECISE_SHADOW_DEPTH 0` _[#if !defined(PLATFORM_NEEDS_PRECISE_SHADOW_DEPTH)]_
- L1529 `#define CALC_SCALAR_ARRAY_SIZE(ElementCount) ((ElementCount+3)/4)` _[#if !defined(CALC_SCALAR_ARRAY_SIZE)]_
- L1532 `#define DECLARE_SCALAR_ARRAY(ScalarType, ScalarName, ElementCount) ScalarType##4 ScalarName[CALC_SCALAR_ARRAY_SIZE(ElementCount)]` _[#if !defined(DECLARE_SCALAR_ARRAY)]_
- L1535 `#define GET_SCALAR_ARRAY_ELEMENT(PackedArray, ElementIndex) PackedArray[(uint)ElementIndex>>2u][(uint)ElementIndex&3u]` _[#if !defined(GET_SCALAR_ARRAY_ELEMENT)]_
- L1540 `#define UE_DECL(Name) ` _[#if !defined(UE_DECL)]_
- L1544 `#define UE_EVAL(Name) Name##_DEFAULT` _[#if !defined(UE_EVAL) && ENABLE_SPECIALIZATION_CONSTANTS]_
- L1546 `#define UE_EVAL(Name) Name` _[#if !defined(UE_EVAL) && !(ENABLE_SPECIALIZATION_CONSTANTS)]_
- L1552 `#define MESH_SHADING_PER_PRIMITIVE_ATTRIBUTE ` _[#if !defined(MESH_SHADING_PER_PRIMITIVE_ATTRIBUTE)]_
- L1555 `#define MESH_SHADING_COMPATIBLE_PS_ENTRY_POINT ` _[#if !defined(MESH_SHADING_COMPATIBLE_PS_ENTRY_POINT)]_
- L7 #pragma `once`; L345 #pragma `dxc diagnostic ignored "-Wconversion"`; L388 #undef `ES3_1_PROFILE`; L401 #undef `ES3_1_PROFILE`; L415 #undef `ES3_1_PROFILE`; L1219 #undef `DEFINE_SELECT`

#### Functions (70)

- L641-644 _function_ `FTimestamp GetShaderTimestamp()` _[#if !defined(PLATFORM_SUPPORTS_SHADER_TIMESTAMP) && USE_NVAPI_TIMESTAMP]_
- L646-650 _function_ `uint ShaderTimestampDiff(FTimestamp TimeBegin, FTimestamp TimeEnd)` _[#if !defined(PLATFORM_SUPPORTS_SHADER_TIMESTAMP) && USE_NVAPI_TIMESTAMP]_
- L746-749 _function_ `void ShaderYield()` _[#if !defined(COMPILER_SUPPORTS_SHADER_YIELD)]_
- L836 _function_ `precise float MakePrecise(in precise float v)` _[#if !defined(INVARIANT)]_
- L837 _function_ `precise float2 MakePrecise(in precise float2 v)` _[#if !defined(INVARIANT)]_
- L838 _function_ `precise float3 MakePrecise(in precise float3 v)` _[#if !defined(INVARIANT)]_
- L839 _function_ `precise float4 MakePrecise(in precise float4 v)` _[#if !defined(INVARIANT)]_
- L1034-1039 _function_ `void WriteDispatchIndirectArgs(RWBuffer<uint> RWIndirectDispatchArgsBuffer, in uint InIndex, in uint InIndirectArgX, in uint InIndirectArgY, in uint InIndirectArgZ)` _[#if !defined(DISPATCH_INDIRECT_UINT_COUNT)]_
- L1042-1045 _function_ `void WriteDispatchIndirectArgs(RWBuffer<uint> RWIndirectDispatchArgsBuffer, in uint InIndex, in uint3 InIndirectArg)`
- L1050-1056 _function_ `void WriteIndirectDrawArgs(RWBuffer<uint> OutIndirectArgsBuffer, in uint InIndex, in uint InVertexCount, in uint InInstanceCount, in uint StartVertexLocation=0, in uint StartInstanceLocation=0)`
- L1061-1068 _function_ `void WriteIndirectIndexedDrawArgs(RWBuffer<uint> OutIndirectArgsBuffer, in uint InIndex, in uint InIndexCount, in uint InInstanceCount, in uint InStartIndexLocation=0, in uint InBaseVertexLocation=0, in uint InStartInstanceLocation=0)`
- L1074-1080 _function_ `float determinant(float3x3 M)` _[#if COMPILER_NEEDS_DETERMINANT]_
- L1091-1094 _function_ `float min3(float a, float b, float c)` _[#if !COMPILER_SUPPORTS_MINMAX3]_
- L1096-1099 _function_ `int min3(int a, int b, int c)` _[#if !COMPILER_SUPPORTS_MINMAX3]_
- L1101-1104 _function_ `uint min3(uint a, uint b, uint c)` _[#if !COMPILER_SUPPORTS_MINMAX3]_
- L1110-1113 _function_ `float max3(float a, float b, float c)` _[#if !COMPILER_SUPPORTS_MINMAX3]_
- L1115-1118 _function_ `int max3(int a, int b, int c)` _[#if !COMPILER_SUPPORTS_MINMAX3]_
- L1120-1123 _function_ `uint max3(uint a, uint b, uint c)` _[#if !COMPILER_SUPPORTS_MINMAX3]_
- L1131-1134 _function_ `half min3(half a, half b, half c)` _[#if !COMPILER_SUPPORTS_MINMAX3 && PLATFORM_SUPPORTS_REAL_TYPES]_
- L1136-1139 _function_ `int16_t min3(int16_t a, int16_t b, int16_t c)` _[#if !COMPILER_SUPPORTS_MINMAX3 && PLATFORM_SUPPORTS_REAL_TYPES]_
- L1141-1144 _function_ `uint16_t min3(uint16_t a, uint16_t b, uint16_t c)` _[#if !COMPILER_SUPPORTS_MINMAX3 && PLATFORM_SUPPORTS_REAL_TYPES]_
- L1150-1153 _function_ `half max3(half a, half b, half c)` _[#if !COMPILER_SUPPORTS_MINMAX3 && PLATFORM_SUPPORTS_REAL_TYPES]_
- L1155-1158 _function_ `int16_t max3(int16_t a, int16_t b, int16_t c)` _[#if !COMPILER_SUPPORTS_MINMAX3 && PLATFORM_SUPPORTS_REAL_TYPES]_
- L1160-1163 _function_ `uint16_t max3(uint16_t a, uint16_t b, uint16_t c)` _[#if !COMPILER_SUPPORTS_MINMAX3 && PLATFORM_SUPPORTS_REAL_TYPES]_
- L1222 _function_ `bool and_internal(bool a, bool b)` — Works around bug in the spirv for the missing implementation of the and() and or() intrinsics.
- L1223 _function_ `bool2 and_internal(bool2 a, bool2 b)`
- L1224 _function_ `bool3 and_internal(bool3 a, bool3 b)`
- L1225 _function_ `bool4 and_internal(bool4 a, bool4 b)`
- L1227 _function_ `bool or_internal(bool a, bool b)`
- L1228 _function_ `bool2 or_internal(bool2 a, bool2 b)`
- L1229 _function_ `bool3 or_internal(bool3 a, bool3 b)`
- L1230 _function_ `bool4 or_internal(bool4 a, bool4 b)`
- L1239-1242 _function_ `half2 v_pack_b32_b16(half a, half b)` — Function that explicitly use RDNA's v_pack_b32_f16 on supported platform. Note that RDNA's documentation call this instruction v_pack_b32_f16 but really is a v_pack_b32_b16. _[#if PLATFORM_SUPPORTS_REAL_TYPES && !defined(COMPILER_SUPPORTS_PACK_B32_B16)]_
- L1244-1247 _function_ `int16_t2 v_pack_b32_b16(int16_t a, int16_t b)` _[#if PLATFORM_SUPPORTS_REAL_TYPES && !defined(COMPILER_SUPPORTS_PACK_B32_B16)]_
- L1249-1252 _function_ `uint16_t2 v_pack_b32_b16(uint16_t a, uint16_t b)` _[#if PLATFORM_SUPPORTS_REAL_TYPES && !defined(COMPILER_SUPPORTS_PACK_B32_B16)]_
- L1258 _function_ `float CondMask(bool Cond, float Src0, float Src1)` _[#if !defined(COMPILER_SUPPORTS_COND_MASK)]_
- L1259 _function_ `float2 CondMask(bool Cond, float2 Src0, float2 Src1)` _[#if !defined(COMPILER_SUPPORTS_COND_MASK)]_
- L1260 _function_ `float3 CondMask(bool Cond, float3 Src0, float3 Src1)` _[#if !defined(COMPILER_SUPPORTS_COND_MASK)]_
- L1261 _function_ `float4 CondMask(bool Cond, float4 Src0, float4 Src1)` _[#if !defined(COMPILER_SUPPORTS_COND_MASK)]_
- L1263 _function_ `int CondMask(bool Cond, int Src0, int Src1)` _[#if !defined(COMPILER_SUPPORTS_COND_MASK)]_
- L1264 _function_ `int2 CondMask(bool Cond, int2 Src0, int2 Src1)` _[#if !defined(COMPILER_SUPPORTS_COND_MASK)]_
- L1265 _function_ `int3 CondMask(bool Cond, int3 Src0, int3 Src1)` _[#if !defined(COMPILER_SUPPORTS_COND_MASK)]_
- L1266 _function_ `int4 CondMask(bool Cond, int4 Src0, int4 Src1)` _[#if !defined(COMPILER_SUPPORTS_COND_MASK)]_
- L1268 _function_ `uint CondMask(bool Cond, uint Src0, uint Src1)` _[#if !defined(COMPILER_SUPPORTS_COND_MASK)]_
- L1269 _function_ `uint2 CondMask(bool Cond, uint2 Src0, uint2 Src1)` _[#if !defined(COMPILER_SUPPORTS_COND_MASK)]_
- L1270 _function_ `uint3 CondMask(bool Cond, uint3 Src0, uint3 Src1)` _[#if !defined(COMPILER_SUPPORTS_COND_MASK)]_
- L1271 _function_ `uint4 CondMask(bool Cond, uint4 Src0, uint4 Src1)` _[#if !defined(COMPILER_SUPPORTS_COND_MASK)]_
- L1276 _function_ `float UnpackByte0(uint v)` _[#if !defined(COMPILER_SUPPORTS_UNPACKBYTEN)]_
- L1277 _function_ `float UnpackByte1(uint v)` _[#if !defined(COMPILER_SUPPORTS_UNPACKBYTEN)]_
- L1278 _function_ `float UnpackByte2(uint v)` _[#if !defined(COMPILER_SUPPORTS_UNPACKBYTEN)]_
- L1279 _function_ `float UnpackByte3(uint v)` _[#if !defined(COMPILER_SUPPORTS_UNPACKBYTEN)]_
- L1289-1292 _function_ `uint BitFieldInsertU32(uint Mask, uint Preserve, uint Enable)` _[#if !defined(COMPILER_SUPPORTS_BITFIELD_INTRINSICS)]_
- L1294-1301 _function_ `uint BitFieldExtractU32(uint Data, uint Size, uint Offset)` _[#if !defined(COMPILER_SUPPORTS_BITFIELD_INTRINSICS)]_
- L1303-1310 _function_ `int BitFieldExtractI32(int Data, uint Size, uint Offset)` _[#if !defined(COMPILER_SUPPORTS_BITFIELD_INTRINSICS)]_
- L1312-1318 _function_ `uint BitFieldMaskU32(uint MaskWidth, uint MaskLocation)` _[#if !defined(COMPILER_SUPPORTS_BITFIELD_INTRINSICS)]_
- L1324-1328 _function_ `int MulI24(int I1, int I2)` _[#if !defined(COMPILER_SUPPORTS_24BIT_INTRINSICS)]_
- L1330-1334 _function_ `uint MulU24(uint U1, uint U2)` _[#if !defined(COMPILER_SUPPORTS_24BIT_INTRINSICS)]_
- L1336-1340 _function_ `int MadI24(int I1, int I2, int I3)` _[#if !defined(COMPILER_SUPPORTS_24BIT_INTRINSICS)]_
- L1342-1346 _function_ `uint MadU24(uint U1, uint U2, uint U3)` _[#if !defined(COMPILER_SUPPORTS_24BIT_INTRINSICS)]_
- L1350-1353 _function_ `uint Padding(uint Value, uint Pow2)`
- L1355-1358 _function_ `uint CeilLog2(uint Value)`
- L1360-1363 _function_ `float BitFieldExtractFloat(uint Bits, uint Count, uint Offset)`
- L1367-1374 _function_ `uint BitAlignU32(uint High, uint Low, uint Shift)` _[#if !defined(COMPILER_SUPPORTS_BITALIGN)]_
- L1379-1382 _function_ `uint ByteAlignU32(uint High, uint Low, uint Shift)` _[#if !defined(COMPILER_SUPPORTS_BYTEALIGN)]_
- L1394-1397 _function_ `UlongType PackUlongType(uint2 Value)` _[#if !defined(COMPILER_SUPPORTS_ULONG_TYPES)]_
- L1399-1402 _function_ `uint2 UnpackUlongType(UlongType Value)` _[#if !defined(COMPILER_SUPPORTS_ULONG_TYPES)]_
- L1407-1418 _function_ `uint MaskedBitCount( uint2 Bits, uint Index )` — Prefix sum of Bits masked to the bits lower than Index.
- L1439-1442 _function_ `uint MaskedBitCount( uint2 Bits )` _[#if PLATFORM_SUPPORTS_SM6_0_WAVE_OPERATIONS && !defined(COMPILER_SUPPORTS_MASKED_BIT_COUNT)]_
- L1446-1449 _function_ `uint2 WaveBallot( bool Expr )` _[#if PLATFORM_SUPPORTS_SM6_0_WAVE_OPERATIONS && COMPILER_DXC]_
- L1453-1479 _function_ `uint WaveGetActiveLaneIndexLast()` _[#if PLATFORM_SUPPORTS_SM6_0_WAVE_OPERATIONS && !defined(WaveReadLaneLast)]_

#### Top-level macro invocations (19)

- L1106 _macro_call_ `DECLARE_VECTOR_FUNCTION_OVERLOAD_3_PARAM(min3, float)` _[#if !COMPILER_SUPPORTS_MINMAX3]_
- L1107 _macro_call_ `DECLARE_VECTOR_FUNCTION_OVERLOAD_3_PARAM(min3, int)` _[#if !COMPILER_SUPPORTS_MINMAX3]_
- L1108 _macro_call_ `DECLARE_VECTOR_FUNCTION_OVERLOAD_3_PARAM(min3, uint)` _[#if !COMPILER_SUPPORTS_MINMAX3]_
- L1125 _macro_call_ `DECLARE_VECTOR_FUNCTION_OVERLOAD_3_PARAM(max3, float)` _[#if !COMPILER_SUPPORTS_MINMAX3]_
- L1126 _macro_call_ `DECLARE_VECTOR_FUNCTION_OVERLOAD_3_PARAM(max3, int)` _[#if !COMPILER_SUPPORTS_MINMAX3]_
- L1127 _macro_call_ `DECLARE_VECTOR_FUNCTION_OVERLOAD_3_PARAM(max3, uint)` _[#if !COMPILER_SUPPORTS_MINMAX3]_
- L1146 _macro_call_ `DECLARE_VECTOR_FUNCTION_OVERLOAD_3_PARAM(min3, half)` _[#if !COMPILER_SUPPORTS_MINMAX3 && PLATFORM_SUPPORTS_REAL_TYPES]_
- L1147 _macro_call_ `DECLARE_VECTOR_FUNCTION_OVERLOAD_3_PARAM(min3, int16_t)` _[#if !COMPILER_SUPPORTS_MINMAX3 && PLATFORM_SUPPORTS_REAL_TYPES]_
- L1148 _macro_call_ `DECLARE_VECTOR_FUNCTION_OVERLOAD_3_PARAM(min3, uint16_t)` _[#if !COMPILER_SUPPORTS_MINMAX3 && PLATFORM_SUPPORTS_REAL_TYPES]_
- L1165 _macro_call_ `DECLARE_VECTOR_FUNCTION_OVERLOAD_3_PARAM(max3, half)` _[#if !COMPILER_SUPPORTS_MINMAX3 && PLATFORM_SUPPORTS_REAL_TYPES]_
- L1166 _macro_call_ `DECLARE_VECTOR_FUNCTION_OVERLOAD_3_PARAM(max3, int16_t)` _[#if !COMPILER_SUPPORTS_MINMAX3 && PLATFORM_SUPPORTS_REAL_TYPES]_
- L1167 _macro_call_ `DECLARE_VECTOR_FUNCTION_OVERLOAD_3_PARAM(max3, uint16_t)` _[#if !COMPILER_SUPPORTS_MINMAX3 && PLATFORM_SUPPORTS_REAL_TYPES]_
- L1204 _macro_call_ `DEFINE_SELECT(bool)`
- L1207 _macro_call_ `DEFINE_SELECT(uint)` _[#if !(COMPILER_HLSL \|\| COMPILER_DXC \|\| COMPILER_HLSLCC) \|\| PLATFORM_NEEDS_SELECT_UINT]_
- L1209 _macro_call_ `DEFINE_SELECT(int)`
- L1210 _macro_call_ `DEFINE_SELECT(float)`
- L1212 _macro_call_ `DEFINE_SELECT(half)` _[#if PLATFORM_SUPPORTS_REAL_TYPES]_
- L1215 _macro_call_ `DEFINE_SELECT(uint16_t)` _[#if PLATFORM_SUPPORTS_REAL_TYPES && !(COMPILER_HLSL \|\| COMPILER_DXC \|\| COMPILER_HLSLCC)]_
- L1217 _macro_call_ `DEFINE_SELECT(int16_t)` _[#if PLATFORM_SUPPORTS_REAL_TYPES]_

### `Shaders/Public/RootConstants.ush` (Public)

- lines: 21; parse: all-branches
- includes: L7 `/Platform/Public/PlatformRootConstants.ush` [PLATFORM_SUPPORTS_SHADER_ROOT_CONSTANTS && OVERRIDE_ROOTCONSTANTS_USH], L9 `Platform/D3D/D3DRootConstants.ush` [PLATFORM_SUPPORTS_SHADER_ROOT_CONSTANTS && !(OVERRIDE_ROOTCONSTANTS_USH) && SM6_PROFILE \|\| SM5_PROFILE]
- L3 #pragma `once`

#### Global parameters (uniforms) (1)

- L12 _parameter_ `uint4 PassData;` _[#if !(PLATFORM_SUPPORTS_SHADER_ROOT_CONSTANTS)]_

#### Functions (5)

- L14 _function_ `uint4 GetAllRootConstants()` _[#if !(PLATFORM_SUPPORTS_SHADER_ROOT_CONSTANTS)]_
- L16 _function_ `uint GetRootConstant0()` _[#if !(PLATFORM_SUPPORTS_SHADER_ROOT_CONSTANTS)]_
- L17 _function_ `uint GetRootConstant1()` _[#if !(PLATFORM_SUPPORTS_SHADER_ROOT_CONSTANTS)]_
- L18 _function_ `uint GetRootConstant2()` _[#if !(PLATFORM_SUPPORTS_SHADER_ROOT_CONSTANTS)]_
- L19 _function_ `uint GetRootConstant3()` _[#if !(PLATFORM_SUPPORTS_SHADER_ROOT_CONSTANTS)]_

### `Shaders/Public/ShaderVersion.ush` (Public)

- lines: 6; parse: all-branches
- L6 #pragma `message("UESHADERMETADATA_VERSION DDA9A115-612F-4F64-8206-999DB9C8320D")`

### `Shaders/Public/SubstratePublic.ush` (Public)

- lines: 149; parse: all-branches
- includes: L9 `/Engine/Private/Substrate/Substrate.ush`, L10 `/Engine/Private/Substrate/SubstrateRead.ush`

#### Macros (#define, 1)

- L14 `#define SUBSTRATE_ALLOWS_GBUFFER_SAMPLING ((NEEDS_SCENE_TEXTURES && !SCENE_TEXTURES_DISABLED)) && SHADING_PATH_DEFERRED` _[#if SUBSTRATE_ENABLED]_
- L3 #pragma `once`

#### Structs / classes (1)

- L22-43 _struct_ **`FSubstrateGBuffer`** `struct FSubstrateGBuffer` _[#if SUBSTRATE_ENABLED]_
  - L24 _member_ `bool bIsValid;` _[#if SUBSTRATE_ENABLED]_
  - L26 _member_ `float3 DiffuseColor;` _[#if SUBSTRATE_ENABLED]_
  - L27 _member_ `float3 SpecularColor;` _[#if SUBSTRATE_ENABLED]_
  - L28 _member_ `float3 SubsurfaceColor;` _[#if SUBSTRATE_ENABLED]_
  - L29 _member_ `float3 BaseColor;` _[#if SUBSTRATE_ENABLED]_
  - L30 _member_ `float Specular;` _[#if SUBSTRATE_ENABLED]_
  - L31 _member_ `float Metallic;` _[#if SUBSTRATE_ENABLED]_
  - L32 _member_ `float3 WorldNormal;` _[#if SUBSTRATE_ENABLED]_
  - L33 _member_ `float Opacity;` _[#if SUBSTRATE_ENABLED]_
  - L34 _member_ `float Roughness;` _[#if SUBSTRATE_ENABLED]_
  - L35 _member_ `float MaterialAO;` _[#if SUBSTRATE_ENABLED]_
  - L36 _member_ `float3 ShadingModelColor;` _[#if SUBSTRATE_ENABLED]_
  - L37 _member_ `float ShadingModelID;` _[#if SUBSTRATE_ENABLED]_
  - L38 _member_ `float3 StoredBaseColor;` _[#if SUBSTRATE_ENABLED]_
  - L39 _member_ `float3 StoredSpecular;` _[#if SUBSTRATE_ENABLED]_
  - L40 _member_ `float3 WorldTangent;` _[#if SUBSTRATE_ENABLED]_
  - L41 _member_ `float Anisotropy;` _[#if SUBSTRATE_ENABLED]_
  - L42 _member_ `bool bIsFirstPerson;` _[#if SUBSTRATE_ENABLED]_

#### Functions (3)

- L45-119 _function_ `FSubstrateGBuffer SubstratePublic_GetSubstrateGBufferFromFirstBSDF(uint2 PixelCoord, bool bGetNormalizedNormal = true)` _[#if SUBSTRATE_ENABLED]_
- L122-134 _function_ `float3 SubstratePublic_GetWorldNormal(uint2 PixelCoord)` — Optimised data fetch from the TopLayer texture _[#if SUBSTRATE_ENABLED]_
- L135-147 _function_ `float SubstratePublic_GetRoughness(uint2 PixelCoord)` _[#if SUBSTRATE_ENABLED]_

### `Shaders/Public/WaveBroadcastIntrinsics.ush` (Public)

- lines: 562; parse: first-branch (retry, +0 merged from all-branches pass)
- includes: L10 `Platform.ush`

#### Macros (#define, 14)

- L14 `#define PLATFORM_SUPPORTS_WAVE_READ_AT 1` _[#if COMPILER_SUPPORTS_WAVE_PERMUTE]_
- L16 `#define PLATFORM_SUPPORTS_WAVE_READ_AT 1` _[#if !(COMPILER_SUPPORTS_WAVE_PERMUTE) && FEATURE_LEVEL >= FEATURE_LEVEL_SM6 \|\| PLATFORM_SUPPORTS_SM6_0_WAVE_OPERATIONS]_
- L18 `#define PLATFORM_SUPPORTS_WAVE_READ_AT 0` _[#if !(COMPILER_SUPPORTS_WAVE_PERMUTE) && !(FEATURE_LEVEL >= FEATURE_LEVEL_SM6 \|\| PLATFORM_SUPPORTS_SM6_0_WAVE_OPERATIONS)]_
- L22 `#define PLATFORM_SUPPORTS_WAVE_BROADCAST 1` _[#if COMPILER_SUPPORTS_WAVE_SWIZZLE_GCN]_
- L24 `#define PLATFORM_SUPPORTS_WAVE_BROADCAST 1` _[#if !(COMPILER_SUPPORTS_WAVE_SWIZZLE_GCN) && FEATURE_LEVEL >= FEATURE_LEVEL_SM6 \|\| PLATFORM_SUPPORTS_SM6_0_WAVE_OPERATIONS]_
- L26 `#define PLATFORM_SUPPORTS_WAVE_BROADCAST 0` _[#if !(COMPILER_SUPPORTS_WAVE_SWIZZLE_GCN) && !(FEATURE_LEVEL >= FEATURE_LEVEL_SM6 \|\| PLATFORM_SUPPORTS_SM6_0_WAVE_OPERATIONS)]_
- L30 `#define PLATFORM_SUPPORTS_WAVE_ROTATE 1` _[#if defined(COMPILER_SUPPORTS_WAVE_SWIZZLE_RDNA) && COMPILER_SUPPORTS_WAVE_SWIZZLE_RDNA]_
- L32 `#define PLATFORM_SUPPORTS_WAVE_ROTATE 1` _[#if !(defined(COMPILER_SUPPORTS_WAVE_SWIZZLE_RDNA) && COMPILER_SUPPORTS_WAVE_SWIZZLE_RDNA) && FEATURE_LEVEL >= FEATURE_LEVEL_SM6 \|\| PLATFORM_SUPPORTS_SM6_0_WAVE_OPERATIONS]_
- L34 `#define PLATFORM_SUPPORTS_WAVE_ROTATE 0` _[#if !(defined(COMPILER_SUPPORTS_WAVE_SWIZZLE_RDNA) && COMPILER_SUPPORTS_WAVE_SWIZZLE_RDNA) && !(FEATURE_LEVEL >= FEATURE_LEVEL_SM6 \|\| PLATFORM_SUPPORTS_SM6_0_WAVE_OPERATIONS)]_
- L39 `#define WAVE_BROADCAST_NOP 0`
- L40 `#define WAVE_BROADCAST_READ_LANE_AT 1`
- L41 `#define WAVE_BROADCAST_READ_LDS_AT 2`
- L42 `#define WAVE_BROADCAST_GCN_SWIZZLE 3`
- L43 `#define WAVE_BROADCAST_ROTATE 4`
- L8 #pragma `once`

#### Structs / classes (1)

- L46-65 _struct_ **`FWaveBroadcastSettings`** `struct FWaveBroadcastSettings` — Compile time structure to choose which broadcasting should be done.
  - L49 _member_ `uint Operation;` — Broadcast operations.
  - L52 _member_ `uint SourceLaneIndex;` — Lane index to read from
  - L55 _member_ `uint GroupThreadIndex;` — index of the thread.
  - L58 _member_ `uint SwizzleAnd;` — Informations about the broadcast for GCN's ds_swizzle.
  - L59 _member_ `uint SwizzleOr;`
  - L60 _member_ `uint SwizzleXor;`
  - L63 _member_ `int Rotate;` — Information about the broadcast for RDNA's ds_swizzle's rotate functionality
  - L64 _member_ `uint RotateFixMask;`

#### groupshared (1)

- L69 _groupshared_ `groupshared uint SharedBroadcastLDS[WAVE_BROADCAST_GROUPSIZE];` _[#if defined(WAVE_BROADCAST_GROUPSIZE)]_

#### Functions (37)

- L73-97 _function_ `CALL_SITE_DEBUGLOC uint GetWaveBroadcastSourceLaneIndex(const FWaveBroadcastSettings Settings, uint DestLaneIndex)` — Returns the index of the source lane for a dest lane index.
- L100-169 _function_ `CALL_SITE_DEBUGLOC uint WaveBroadcast(const FWaveBroadcastSettings Settings, uint x)` — Generic broadcast instruction.
- L171-177 _function_ `CALL_SITE_DEBUGLOC uint2 WaveBroadcast(const FWaveBroadcastSettings Settings, uint2 v)`
- L179-186 _function_ `CALL_SITE_DEBUGLOC uint3 WaveBroadcast(const FWaveBroadcastSettings Settings, uint3 v)`
- L188-196 _function_ `CALL_SITE_DEBUGLOC uint4 WaveBroadcast(const FWaveBroadcastSettings Settings, uint4 v)`
- L199-203 _function_ `CALL_SITE_DEBUGLOC int WaveBroadcast(const FWaveBroadcastSettings Settings, int x)`
- L205-211 _function_ `CALL_SITE_DEBUGLOC int2 WaveBroadcast(const FWaveBroadcastSettings Settings, int2 v)`
- L213-220 _function_ `CALL_SITE_DEBUGLOC int3 WaveBroadcast(const FWaveBroadcastSettings Settings, int3 v)`
- L222-230 _function_ `CALL_SITE_DEBUGLOC int4 WaveBroadcast(const FWaveBroadcastSettings Settings, int4 v)`
- L233-237 _function_ `CALL_SITE_DEBUGLOC float WaveBroadcast(const FWaveBroadcastSettings Settings, float x)`
- L239-245 _function_ `CALL_SITE_DEBUGLOC float2 WaveBroadcast(const FWaveBroadcastSettings Settings, float2 v)`
- L247-254 _function_ `CALL_SITE_DEBUGLOC float3 WaveBroadcast(const FWaveBroadcastSettings Settings, float3 v)`
- L256-264 _function_ `CALL_SITE_DEBUGLOC float4 WaveBroadcast(const FWaveBroadcastSettings Settings, float4 v)`
- L267-271 _function_ `CALL_SITE_DEBUGLOC bool WaveBroadcast(const FWaveBroadcastSettings Settings, bool x)`
- L273-279 _function_ `CALL_SITE_DEBUGLOC bool2 WaveBroadcast(const FWaveBroadcastSettings Settings, bool2 v)`
- L281-288 _function_ `CALL_SITE_DEBUGLOC bool3 WaveBroadcast(const FWaveBroadcastSettings Settings, bool3 v)`
- L290-298 _function_ `CALL_SITE_DEBUGLOC bool4 WaveBroadcast(const FWaveBroadcastSettings Settings, bool4 v)`
- L303-307 _function_ `CALL_SITE_DEBUGLOC uint16_t WaveBroadcast(const FWaveBroadcastSettings Settings, uint16_t x)` _[#if PLATFORM_SUPPORTS_REAL_TYPES]_
- L309-316 _function_ `CALL_SITE_DEBUGLOC uint16_t2 WaveBroadcast(const FWaveBroadcastSettings Settings, uint16_t2 v)` _[#if PLATFORM_SUPPORTS_REAL_TYPES]_
- L331-337 _function_ `CALL_SITE_DEBUGLOC uint16_t3 WaveBroadcast(const FWaveBroadcastSettings Settings, uint16_t3 v)` _[#if PLATFORM_SUPPORTS_REAL_TYPES]_
- L339-345 _function_ `CALL_SITE_DEBUGLOC uint16_t4 WaveBroadcast(const FWaveBroadcastSettings Settings, uint16_t4 v)` _[#if PLATFORM_SUPPORTS_REAL_TYPES]_
- L348-352 _function_ `CALL_SITE_DEBUGLOC int16_t WaveBroadcast(const FWaveBroadcastSettings Settings, int16_t x)` _[#if PLATFORM_SUPPORTS_REAL_TYPES]_
- L354-358 _function_ `CALL_SITE_DEBUGLOC int16_t2 WaveBroadcast(const FWaveBroadcastSettings Settings, int16_t2 v)` _[#if PLATFORM_SUPPORTS_REAL_TYPES]_
- L360-364 _function_ `CALL_SITE_DEBUGLOC int16_t3 WaveBroadcast(const FWaveBroadcastSettings Settings, int16_t3 v)` _[#if PLATFORM_SUPPORTS_REAL_TYPES]_
- L366-370 _function_ `CALL_SITE_DEBUGLOC int16_t4 WaveBroadcast(const FWaveBroadcastSettings Settings, int16_t4 v)` _[#if PLATFORM_SUPPORTS_REAL_TYPES]_
- L373-377 _function_ `CALL_SITE_DEBUGLOC half WaveBroadcast(const FWaveBroadcastSettings Settings, half x)` _[#if PLATFORM_SUPPORTS_REAL_TYPES]_
- L379-383 _function_ `CALL_SITE_DEBUGLOC half2 WaveBroadcast(const FWaveBroadcastSettings Settings, half2 v)` _[#if PLATFORM_SUPPORTS_REAL_TYPES]_
- L385-389 _function_ `CALL_SITE_DEBUGLOC half3 WaveBroadcast(const FWaveBroadcastSettings Settings, half3 v)` _[#if PLATFORM_SUPPORTS_REAL_TYPES]_
- L391-395 _function_ `CALL_SITE_DEBUGLOC half4 WaveBroadcast(const FWaveBroadcastSettings Settings, half4 v)` _[#if PLATFORM_SUPPORTS_REAL_TYPES]_
- L402-415 _function_ `CALL_SITE_DEBUGLOC FWaveBroadcastSettings InitNopBroadcast()` — Init a nop broadcast
- L426-433 _function_ `CALL_SITE_DEBUGLOC FWaveBroadcastSettings InitWaveReadLaneAt(uint SourceLaneIndex)` — Dynamically read another lane's register Requires PLATFORM_SUPPORTS_WAVE_READ_AT. return src[SourceLaneIndex]; Note the SourceLaneIndex can be dynamic according to SM 6.0's WaveReadLaneAt()
- L442-450 _function_ `CALL_SITE_DEBUGLOC FWaveBroadcastSettings InitWaveReadLDS(uint SourceLaneIndex, uint GroupThreadIndex)` — Dynamically read another group thread's register through LDS Requires setting WAVE_BROADCAST_GROUPSIZE to allocate groupshared memory. LDS[GroupThreadIndex] = src; return LDS[SourceLaneIndex];
- L466-470 _function_ `CALL_SITE_DEBUGLOC FWaveBroadcastSettings ConvertWaveBroadcastToLDS(const FWaveBroadcastSettings Settings, uint GroupThreadIndex)` — Converts a broadcast operation to be performed in SM5. Requires setting WAVE_BROADCAST_GROUPSIZE to allocate groupshared memory. Returns the exact sames data as Settings would otherwise return, but through LDS. Example: const FWaveBroadcastSettings BroadcastSettings = InitWaveReadLaneAt(SourceLaneIndex); #if PLATFORM_SUPPORTS_WAVE_READ_AT uint Desc = WaveBroadcast(BroadcastSettings, Src); #else uint Desc = WaveBroadcast(ConvertWaveBroadcastToLDS(BroadcastSettings, GroupThreadIndex), Src); #endif
- L478-487 _function_ `CALL_SITE_DEBUGLOC FWaveBroadcastSettings InitWaveXorButterfly(const uint XorButterFly)` — Broadcast in butterfly pattern. Requires PLATFORM_SUPPORTS_WAVE_BROADCAST. return src[laneId ^ XorButterFly];
- L503-507 _function_ `CALL_SITE_DEBUGLOC FWaveBroadcastSettings InitWaveSwapWithinLaneGroup(const uint LaneGroupSize)` — Swap left lane with righ lanes within lane group (size is power of two in [2; 64]). Requires PLATFORM_SUPPORTS_WAVE_BROADCAST. If a lane is not active, the VGPR value returned is 0. LaneGroupSize = 8 LaneId = 1 \|  lane group (size=8)  \| x = \| 0  1  2  3\| 4  5  6  7\| 8  9 ... return \| 4  5  6  7\| 0  1  2  3\|12 13 ...
- L524-535 _function_ `CALL_SITE_DEBUGLOC FWaveBroadcastSettings InitWaveBroadcastLaneGroup(const uint LaneGroupSize, const uint InnerLaneGroupSize, const uint InnerLaneGroupId)` — Broadcast inner lane group over a lane group (size is power of two in [2; 64]). Requires PLATFORM_SUPPORTS_WAVE_BROADCAST. If a lane is not active, the VGPR value returned is 0. LaneGroupSize = 8 InnerLaneGroupSize = 2 InnerLaneGroupId = 1 \|  lane group (size=8)  \| x = \| 0  1  2  3  4  5  6  7\| 8  9 ... return \| 2  3  2  3  2  3  2  3\|10 11 ...
- L553-561 _function_ `CALL_SITE_DEBUGLOC FWaveBroadcastSettings InitWaveRotateLaneGroup(const uint LaneGroupSize, const int LaneRotation)` — Rotate lane (-127 to +127) over a lane group (size is power of two in [2; 128]). Notes: RDNA can only do this with LaneGroupSize <= 32 Requires PLATFORM_SUPPORTS_WAVE_ROTATE. If a lane is not active, the VGPR value returned is 0. LaneGroupSize = 8 LaneRotation = +3 \|  lane group (size=8)  \| x = \| 0  1  2  3  4  5  6  7\| 8  9 ... return \| 3  4  5  6  7  0  1  2\|11 12 ...
