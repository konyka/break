# Shaders / Shaders/Public/Platform/Metal

- files: 2; lines: 261
- record kinds: define=65, function=5, include=1, member=3, prototype=7, resource=18, static_const=1, struct=1

### `Shaders/Public/Platform/Metal/MetalCommon.ush` (Public)

- lines: 190; parse: all-branches
- includes: L147 `/Engine/Shared/RayTracingBuiltInResources.h` [UE_BINDLESS_ENABLED && ((RAYCALLABLESHADER \|\| RAYHITGROUPSHADER \|\| RAYGENSHADER \|\| RAYMISSSHADER) \|\| (defined(PLATFORM_SUPPORTS_INLINE_RAY_TRACING) && PLATFORM_SUPPORTS_INLINE_RAY_TRACING == 1))]

#### Macros (#define, 40)

- L14 `#define TESSELLATIONSHADER 1` _[#if VERTEXSHADER && HULLSHADER && !defined(TESSELLATIONSHADER)]_
- L18 `#define STRONG_TYPE `
- L19 `#define StrongTypedBuffer Buffer`
- L31 `#define GetGlobalSampler(Filter, WrapMode) MetalStatic##Filter##WrapMode##Sampler` _[#if PLATFORM_SUPPORTS_STATIC_SAMPLERS]_
- L36 `#define PLATFORM_SUPPORTS_SM6_0_WAVE_OPERATIONS 1` _[#if METAL_SM6_PROFILE == 1]_
- L40 `#define USE_FORCE_TEXTURE_MIP 1` _[#if IS_BASE_PASS && COMPUTE_SHADED && !defined(USE_FORCE_TEXTURE_MIP)]_
- L46 `#define APPLE_DEPTH_BIAS_HACK 1` _[#if METAL_SM5_PROFILE \|\| METAL_SM6_PROFILE \|\| METAL_MRT_PROFILE]_
- L47 `#define APPLE_DEPTH_BIAS_VALUE 0.000001` _[#if METAL_SM5_PROFILE \|\| METAL_SM6_PROFILE \|\| METAL_MRT_PROFILE]_
- L59 `#define COMPILER_SUPPORTS_MINMAX3 0`
- L67 `#define SubpassFetchRGBA_0() gl_LastFragDataRGBA_0.Load(uint3(0, 0, 0), 0)` _[#if IOS && PIXELSHADER]_
- L71 `#define SubpassFetchR_4() gl_LastFragDataR_4.Load(uint3(0, 0, 0), 0)` _[#if IOS && PIXELSHADER]_
- L75 `#define SubpassFetchR_5() gl_LastFragDataR_5.Load(uint3(0, 0, 0), 0)` _[#if IOS && PIXELSHADER]_
- L78 `#define SubpassFetchR_1() gl_LastFragDataR_1.Load(uint3(0, 0, 0), 0)` _[#if IOS && PIXELSHADER]_
- L84 `#define DepthbufferFetchES2() SubpassFetchR_5()` _[#if IOS && PIXELSHADER && MOBILE_DEFERRED_SHADING && MOBILE_EXTENDED_GBUFFER]_
- L86 `#define DepthbufferFetchES2() SubpassFetchR_4()` _[#if IOS && PIXELSHADER && MOBILE_DEFERRED_SHADING && !(MOBILE_EXTENDED_GBUFFER)]_
- L89 `#define DepthbufferFetchES2() SubpassFetchR_1()` _[#if IOS && PIXELSHADER && !(MOBILE_DEFERRED_SHADING)]_
- L92 `#define SubpassFetchRGBA_0() ((float4)0.0)` _[#if !(IOS && PIXELSHADER)]_
- L93 `#define SubpassFetchR_0() (0.0)` _[#if !(IOS && PIXELSHADER)]_
- L94 `#define SubpassFetchR_4() (0.0)` _[#if !(IOS && PIXELSHADER)]_
- L95 `#define SubpassFetchR_5() (0.0)` _[#if !(IOS && PIXELSHADER)]_
- L99 `#define GetSRVFromHeap(Type, Index) ResourceDescriptorHeap[Index]` _[#if PLATFORM_SUPPORTS_BINDLESS]_
- L100 `#define GetUAVFromHeap(Type, Index) ResourceDescriptorHeap[Index]` _[#if PLATFORM_SUPPORTS_BINDLESS]_
- L101 `#define GetCBVFromHeap(Type, Index) ResourceDescriptorHeap[Index]` _[#if PLATFORM_SUPPORTS_BINDLESS]_
- L102 `#define GetSamplerFromHeap(Type, Index) SamplerDescriptorHeap[Index]` _[#if PLATFORM_SUPPORTS_BINDLESS]_
- L106 `#define COMPILER_SUPPORTS_ULONG_TYPES 1` _[#if METAL_SM6_PROFILE == 1]_
- L107 `#define COMPILER_SUPPORTS_UINT64_IMAGE_ATOMICS 1` _[#if METAL_SM6_PROFILE == 1]_
- L110 `#define UlongType uint64_t` _[#if METAL_SM6_PROFILE == 1 && COMPILER_SUPPORTS_ULONG_TYPES]_
- L146 `#define OVERRIDE_RAY_TRACING_HIT_GROUP_SYSTEM_RESOURCES 1` _[#if UE_BINDLESS_ENABLED && ((RAYCALLABLESHADER \|\| RAYHITGROUPSHADER \|\| RAYGENSHADER \|\| RAYMISSSHADER) \|\| (defined(PLATFORM_SUPPORTS_INLINE_RAY_TRACING) && PLATFORM_SUPPORTS_INLINE_RAY_TRACING == 1))]_
- L170 `#define MESH_SHADER_TRIANGLE_ATTRIBUTES(InThreadsX) [numthreads(InThreadsX, 1, 1)][outputtopology("triangle")]` _[#if PLATFORM_SUPPORTS_MESH_SHADERS_TIER0]_
- L171 `#define MESH_SHADER_LINE_ATTRIBUTES(InThreadsX) [numthreads(InThreadsX, 1, 1)][outputtopology("line")]` _[#if PLATFORM_SUPPORTS_MESH_SHADERS_TIER0]_
- L173 `#define AMPLIFICATION_SHADER_TRIANGLE_ATTRIBUTES(InThreadsX) [numthreads(InThreadsX, 1, 1)][outputtopology("triangle")]` _[#if PLATFORM_SUPPORTS_MESH_SHADERS_TIER0]_
- L174 `#define AMPLIFICATION_SHADER_LINE_ATTRIBUTES(InThreadsX) [numthreads(InThreadsX, 1, 1)][outputtopology("line")]` _[#if PLATFORM_SUPPORTS_MESH_SHADERS_TIER0]_
- L176 `#define MESH_SHADER_VERTEX_EXPORT(VertexType, InMaxVertexCount) out vertices VertexType OutVertices[InMaxVertexCount]` _[#if PLATFORM_SUPPORTS_MESH_SHADERS_TIER0]_
- L177 `#define MESH_SHADER_TRIANGLE_EXPORT(InMaxTriangleCount) out indices uint3 OutTriangles[InMaxTriangleCount]` _[#if PLATFORM_SUPPORTS_MESH_SHADERS_TIER0]_
- L178 `#define MESH_SHADER_LINE_EXPORT(InMaxLineCount) out indices uint2 OutLines[InMaxLineCount]` _[#if PLATFORM_SUPPORTS_MESH_SHADERS_TIER0]_
- L180 `#define MESH_SHADER_WRITE_VERTEX(InVertexIndex, Value) OutVertices[InVertexIndex] = Value;` _[#if PLATFORM_SUPPORTS_MESH_SHADERS_TIER0]_
- L181 `#define MESH_SHADER_WRITE_TRIANGLE(InTriangleIndex, Value) OutTriangles[InTriangleIndex] = Value;` _[#if PLATFORM_SUPPORTS_MESH_SHADERS_TIER0]_
- L182 `#define MESH_SHADER_WRITE_LINE(InLineIndex, Value) OutLines[InLineIndex] = Value;` _[#if PLATFORM_SUPPORTS_MESH_SHADERS_TIER0]_
- L186 `#define MESH_SHADER_PRIMITIVE_EXPORT(PrimitiveType, InMaxPrimitiveCount) out primitives PrimitiveType OutPrimitives[InMaxPrimitiveCount]` _[#if PLATFORM_SUPPORTS_MESH_SHADERS_TIER1]_
- L188 `#define MESH_SHADER_WRITE_PRIMITIVE(InPrimitiveIndex, Value) OutPrimitives[InPrimitiveIndex] = Value;` _[#if PLATFORM_SUPPORTS_MESH_SHADERS_TIER1]_
- L7 #pragma `once`; L10 #pragma `message("UESHADERMETADATA_VERSION D1B69FDA-FF60-4414-8915-01A07FC67FF4")`

#### Structs / classes (1)

- L149-155 _struct_ **`FMetalHitGroupSystemParameters`** `struct FMetalHitGroupSystemParameters` _[#if UE_BINDLESS_ENABLED && ((RAYCALLABLESHADER \|\| RAYHITGROUPSHADER \|\| RAYGENSHADER \|\| RAYMISSSHADER) \|\| (defined(PLATFORM_SUPPORTS_INLINE_RAY_TRACING) && PLATFORM_SUPPORTS_INLINE_RAY_TRACING == 1))]_
  - L151 _member_ `FHitGroupSystemRootConstants RootConstants;` _[#if UE_BINDLESS_ENABLED && ((RAYCALLABLESHADER \|\| RAYHITGROUPSHADER \|\| RAYGENSHADER \|\| RAYMISSSHADER) \|\| (defined(PLATFORM_SUPPORTS_INLINE_RAY_TRACING) && PLATFORM_SUPPORTS_INLINE_RAY_TRACING == 1))]_
  - L153 _member_ `uint BindlessHitGroupSystemIndexBuffer;` _[#if UE_BINDLESS_ENABLED && ((RAYCALLABLESHADER \|\| RAYHITGROUPSHADER \|\| RAYGENSHADER \|\| RAYMISSSHADER) \|\| (defined(PLATFORM_SUPPORTS_INLINE_RAY_TRACING) && PLATFORM_SUPPORTS_INLINE_RAY_TRACING == 1))]_
  - L154 _member_ `uint BindlessHitGroupSystemVertexBuffer;` _[#if UE_BINDLESS_ENABLED && ((RAYCALLABLESHADER \|\| RAYHITGROUPSHADER \|\| RAYGENSHADER \|\| RAYMISSSHADER) \|\| (defined(PLATFORM_SUPPORTS_INLINE_RAY_TRACING) && PLATFORM_SUPPORTS_INLINE_RAY_TRACING == 1))]_

#### Global resources (textures / buffers / samplers) (6)

- L66 _resource_ `Texture2D<float4> gl_LastFragDataRGBA_0;` — 4 components: RGBA_0 _[#if IOS && PIXELSHADER]_
- L70 _resource_ `Texture2D<float> gl_LastFragDataR_4;` — 1 component: R_4 _[#if IOS && PIXELSHADER]_
- L74 _resource_ `Texture2D<float> gl_LastFragDataR_5;` — 1 component: R_5 _[#if IOS && PIXELSHADER]_
- L77 _resource_ `Texture2D<float> gl_LastFragDataR_1;` _[#if IOS && PIXELSHADER]_
- L162 _resource_ `ByteAddressBuffer HitGroupSystemIndexBuffer;` — Will get filled in with the bindless index in MetalHitGroupSystemParameters.BindlessHitGroupSystemIndexBuffer _[#if UE_BINDLESS_ENABLED && ((RAYCALLABLESHADER \|\| RAYHITGROUPSHADER \|\| RAYGENSHADER \|\| RAYMISSSHADER) \|\| (defined(PLATFORM_SUPPORTS_INLINE_RAY_TRACING) && PLATFORM_SUPPORTS_INLINE_RAY_TRACING == 1))]_
- L165 _resource_ `ByteAddressBuffer HitGroupSystemVertexBuffer;` — Will get filled in with the bindless index in MetalHitGroupSystemParameters.BindlessHitGroupSystemVertexBuffer _[#if UE_BINDLESS_ENABLED && ((RAYCALLABLESHADER \|\| RAYHITGROUPSHADER \|\| RAYGENSHADER \|\| RAYMISSSHADER) \|\| (defined(PLATFORM_SUPPORTS_INLINE_RAY_TRACING) && PLATFORM_SUPPORTS_INLINE_RAY_TRACING == 1))]_

#### static const (1)

- L159 _static_const_ `static const FHitGroupSystemRootConstants HitGroupSystemRootConstants = MetalHitGroupSystemParameters.RootConstants;` _[#if UE_BINDLESS_ENABLED && ((RAYCALLABLESHADER \|\| RAYHITGROUPSHADER \|\| RAYGENSHADER \|\| RAYMISSSHADER) \|\| (defined(PLATFORM_SUPPORTS_INLINE_RAY_TRACING) && PLATFORM_SUPPORTS_INLINE_RAY_TRACING == 1))]_

#### Functions (5)

- L112-115 _function_ `UlongType PackUlongType(uint2 Value)` _[#if METAL_SM6_PROFILE == 1 && COMPILER_SUPPORTS_ULONG_TYPES]_
- L117-120 _function_ `uint2 UnpackUlongType(UlongType Value)` _[#if METAL_SM6_PROFILE == 1 && COMPILER_SUPPORTS_ULONG_TYPES]_
- L124-127 _function_ `void ImageInterlockedMaxUInt64(RWTexture2D<UlongType> Dest, uint2 Coord, UlongType Value)` _[#if METAL_SM6_PROFILE == 1 && COMPILER_SUPPORTS_UINT64_IMAGE_ATOMICS]_
- L129-132 _function_ `void ImageInterlockedAddUInt64(RWTexture2D<UlongType> Dest, uint2 Coord, UlongType Value)` _[#if METAL_SM6_PROFILE == 1 && COMPILER_SUPPORTS_UINT64_IMAGE_ATOMICS]_
- L134-137 _function_ `void ImageInterlockedOrUInt64(RWTexture2D<UlongType> Dest, uint2 Coord, UlongType Value)` _[#if METAL_SM6_PROFILE == 1 && COMPILER_SUPPORTS_UINT64_IMAGE_ATOMICS]_

#### Prototypes (7)

- L24 _prototype_ `SamplerState MetalStaticPointWrappedSampler : register(s0, space1000)` — Static sampler table must match MetalStaticSamplers.cpp _[#if PLATFORM_SUPPORTS_STATIC_SAMPLERS]_
- L25 _prototype_ `SamplerState MetalStaticPointClampedSampler : register(s1, space1000)` _[#if PLATFORM_SUPPORTS_STATIC_SAMPLERS]_
- L26 _prototype_ `SamplerState MetalStaticBilinearWrappedSampler : register(s2, space1000)` _[#if PLATFORM_SUPPORTS_STATIC_SAMPLERS]_
- L27 _prototype_ `SamplerState MetalStaticBilinearClampedSampler : register(s3, space1000)` _[#if PLATFORM_SUPPORTS_STATIC_SAMPLERS]_
- L28 _prototype_ `SamplerState MetalStaticTrilinearWrappedSampler : register(s4, space1000)` _[#if PLATFORM_SUPPORTS_STATIC_SAMPLERS]_
- L29 _prototype_ `SamplerState MetalStaticTrilinearClampedSampler : register(s5, space1000)` _[#if PLATFORM_SUPPORTS_STATIC_SAMPLERS]_
- L157 _prototype_ `ConstantBuffer<FMetalHitGroupSystemParameters> MetalHitGroupSystemParameters : UE_HLSL_REGISTER(b, RAY_TRACING_SYSTEM_ROOTCONSTANT_REGISTER, UE_HLSL_SPACE_RAY_TRACING_SYSTEM)` _[#if UE_BINDLESS_ENABLED && ((RAYCALLABLESHADER \|\| RAYHITGROUPSHADER \|\| RAYGENSHADER \|\| RAYMISSSHADER) \|\| (defined(PLATFORM_SUPPORTS_INLINE_RAY_TRACING) && PLATFORM_SUPPORTS_INLINE_RAY_TRACING == 1))]_

### `Shaders/Public/Platform/Metal/MetalSubpassSupport.ush` (Public)

- lines: 71; parse: all-branches

#### Macros (#define, 25)

- L17 `#define SubpassFetchRGBA_1() gl_LastFragDataRGBA_1.Load(uint3(0, 0, 0), 0)` _[#if IOS && PIXELSHADER]_
- L20 `#define SubpassFetchRGBA_2() gl_LastFragDataRGBA_2.Load(uint3(0, 0, 0), 0)` _[#if IOS && PIXELSHADER]_
- L23 `#define SubpassFetchRGBA_3() gl_LastFragDataRGBA_3.Load(uint3(0, 0, 0), 0)` _[#if IOS && PIXELSHADER]_
- L26 `#define SubpassFetchRGBA_4() gl_LastFragDataRGBA_4.Load(uint3(0, 0, 0), 0)` _[#if IOS && PIXELSHADER]_
- L29 `#define SubpassFetchRGBA_5() gl_LastFragDataRGBA_5.Load(uint3(0, 0, 0), 0)` _[#if IOS && PIXELSHADER]_
- L32 `#define SubpassFetchRGBA_6() gl_LastFragDataRGBA_6.Load(uint3(0, 0, 0), 0)` _[#if IOS && PIXELSHADER]_
- L35 `#define SubpassFetchRGBA_7() gl_LastFragDataRGBA_7.Load(uint3(0, 0, 0), 0)` _[#if IOS && PIXELSHADER]_
- L39 `#define SubpassFetchR_0() gl_LastFragDataR_0.Load(uint3(0, 0, 0), 0)` _[#if IOS && PIXELSHADER]_
- L44 `#define SubpassFetchR_2() gl_LastFragDataR_2.Load(uint3(0, 0, 0), 0)` _[#if IOS && PIXELSHADER]_
- L47 `#define SubpassFetchR_3() gl_LastFragDataR_3.Load(uint3(0, 0, 0), 0)` _[#if IOS && PIXELSHADER]_
- L52 `#define SubpassFetchR_6() gl_LastFragDataR_6.Load(uint3(0, 0, 0), 0)` _[#if IOS && PIXELSHADER]_
- L55 `#define SubpassFetchR_7() gl_LastFragDataR_7.Load(uint3(0, 0, 0), 0)` _[#if IOS && PIXELSHADER]_
- L57 `#define SubpassFetchRGBA_1() ((float4)0.0)` _[#if !(IOS && PIXELSHADER)]_
- L58 `#define SubpassFetchRGBA_2() ((float4)0.0)` _[#if !(IOS && PIXELSHADER)]_
- L59 `#define SubpassFetchRGBA_3() ((float4)0.0)` _[#if !(IOS && PIXELSHADER)]_
- L60 `#define SubpassFetchRGBA_4() ((float4)0.0)` _[#if !(IOS && PIXELSHADER)]_
- L61 `#define SubpassFetchRGBA_5() ((float4)0.0)` _[#if !(IOS && PIXELSHADER)]_
- L62 `#define SubpassFetchRGBA_6() ((float4)0.0)` _[#if !(IOS && PIXELSHADER)]_
- L63 `#define SubpassFetchRGBA_7() ((float4)0.0)` _[#if !(IOS && PIXELSHADER)]_
- L64 `#define SubpassFetchR_0() (0.0)` _[#if !(IOS && PIXELSHADER)]_
- L65 `#define SubpassFetchR_1() (0.0)` _[#if !(IOS && PIXELSHADER)]_
- L66 `#define SubpassFetchR_2() (0.0)` _[#if !(IOS && PIXELSHADER)]_
- L67 `#define SubpassFetchR_3() (0.0)` _[#if !(IOS && PIXELSHADER)]_
- L68 `#define SubpassFetchR_6() (0.0)` _[#if !(IOS && PIXELSHADER)]_
- L69 `#define SubpassFetchR_7() (0.0)` _[#if !(IOS && PIXELSHADER)]_
- L6 #pragma `once`

#### Global resources (textures / buffers / samplers) (12)

- L16 _resource_ `Texture2D<float4> gl_LastFragDataRGBA_1;` — 4 components _[#if IOS && PIXELSHADER]_
- L19 _resource_ `Texture2D<float4> gl_LastFragDataRGBA_2;` _[#if IOS && PIXELSHADER]_
- L22 _resource_ `Texture2D<float4> gl_LastFragDataRGBA_3;` _[#if IOS && PIXELSHADER]_
- L25 _resource_ `Texture2D<float4> gl_LastFragDataRGBA_4;` _[#if IOS && PIXELSHADER]_
- L28 _resource_ `Texture2D<float4> gl_LastFragDataRGBA_5;` _[#if IOS && PIXELSHADER]_
- L31 _resource_ `Texture2D<float4> gl_LastFragDataRGBA_6;` _[#if IOS && PIXELSHADER]_
- L34 _resource_ `Texture2D<float4> gl_LastFragDataRGBA_7;` _[#if IOS && PIXELSHADER]_
- L38 _resource_ `Texture2D<float> gl_LastFragDataR_0;` — 1 component _[#if IOS && PIXELSHADER]_
- L43 _resource_ `Texture2D<float> gl_LastFragDataR_2;` _[#if IOS && PIXELSHADER]_
- L46 _resource_ `Texture2D<float> gl_LastFragDataR_3;` _[#if IOS && PIXELSHADER]_
- L51 _resource_ `Texture2D<float> gl_LastFragDataR_6;` _[#if IOS && PIXELSHADER]_
- L54 _resource_ `Texture2D<float> gl_LastFragDataR_7;` _[#if IOS && PIXELSHADER]_
