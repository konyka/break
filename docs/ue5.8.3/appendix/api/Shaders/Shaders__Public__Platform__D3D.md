# Shaders / Shaders/Public/Platform/D3D

- files: 3; lines: 216
- record kinds: define=36, function=11, include=3, member=4, prototype=9, resource=2, static_const=1, struct=2

### `Shaders/Public/Platform/D3D/D3DCommon.ush` (Public)

- lines: 168; parse: all-branches
- includes: L10 `/Engine/Shared/HLSLReservedSpaces.h`

#### Macros (#define, 35)

- L13 `#define COMPILER_NEEDS_GLOBALLYCOHERENT_LOCALS 1`
- L16 `#define COMPILER_SUPPORTS_WAVE_SIZE 1` _[#if SM6_PROFILE]_
- L17 `#define WAVESIZE(N) [WaveSize(N)]` _[#if SM6_PROFILE]_
- L30 `#define GetGlobalSampler(Filter, WrapMode) D3DStatic##Filter##WrapMode##Sampler` _[#if PLATFORM_SUPPORTS_STATIC_SAMPLERS]_
- L77 `#define PLATFORM_BREAK() UEReportAssertWithPayload(0xCECC, uint4(__LINE__, 0, 0, 0))` _[#if PLATFORM_SUPPORTS_DIAGNOSTIC_BUFFER && (PIXELSHADER \|\| COMPUTESHADER \|\| RAYGENSHADER)]_
- L79 `#define PLATFORM_ASSERT(condition, assert_id) { if (!(condition)) UEReportAssertWithPayload(assert_id, uint4(0, 0, 0, 0)); }` _[#if PLATFORM_SUPPORTS_DIAGNOSTIC_BUFFER && (PIXELSHADER \|\| COMPUTESHADER \|\| RAYGENSHADER)]_
- L80 `#define PLATFORM_ASSERT1(condition, assert_id, a) { if (!(condition)) UEReportAssertWithPayload(assert_id, uint4(a, 0, 0, 0)); }` _[#if PLATFORM_SUPPORTS_DIAGNOSTIC_BUFFER && (PIXELSHADER \|\| COMPUTESHADER \|\| RAYGENSHADER)]_
- L81 `#define PLATFORM_ASSERT2(condition, assert_id, a, b) { if (!(condition)) UEReportAssertWithPayload(assert_id, uint4(a, b, 0, 0)); }` _[#if PLATFORM_SUPPORTS_DIAGNOSTIC_BUFFER && (PIXELSHADER \|\| COMPUTESHADER \|\| RAYGENSHADER)]_
- L82 `#define PLATFORM_ASSERT3(condition, assert_id, a, b, c) { if (!(condition)) UEReportAssertWithPayload(assert_id, uint4(a, b, c, 0)); }` _[#if PLATFORM_SUPPORTS_DIAGNOSTIC_BUFFER && (PIXELSHADER \|\| COMPUTESHADER \|\| RAYGENSHADER)]_
- L83 `#define PLATFORM_ASSERT4(condition, assert_id, a, b, c, d) { if (!(condition)) UEReportAssertWithPayload(assert_id, uint4(a, b, c, d)); }` _[#if PLATFORM_SUPPORTS_DIAGNOSTIC_BUFFER && (PIXELSHADER \|\| COMPUTESHADER \|\| RAYGENSHADER)]_
- L85 `#define check(condition) { if (!(condition)) { UEReportAssertWithPayload(0xCECC, uint4(__LINE__, TEXT(__FILE__), TEXT(#condition), 0)); } }` _[#if PLATFORM_SUPPORTS_DIAGNOSTIC_BUFFER && (PIXELSHADER \|\| COMPUTESHADER \|\| RAYGENSHADER)]_
- L86 `#define checkf(condition, message) { if (!(condition)) { UEReportAssertWithPayload(0xCECC, uint4(__LINE__, TEXT(__FILE__), message, 0)); } }` _[#if PLATFORM_SUPPORTS_DIAGNOSTIC_BUFFER && (PIXELSHADER \|\| COMPUTESHADER \|\| RAYGENSHADER)]_
- L91 `#define MESH_SHADER_TRIANGLE_ATTRIBUTES(InThreadsX) [numthreads(InThreadsX, 1, 1)][outputtopology("triangle")]` _[#if PLATFORM_SUPPORTS_MESH_SHADERS_TIER0]_
- L92 `#define MESH_SHADER_LINE_ATTRIBUTES(InThreadsX) [numthreads(InThreadsX, 1, 1)][outputtopology("line")]` _[#if PLATFORM_SUPPORTS_MESH_SHADERS_TIER0]_
- L94 `#define AMPLIFICATION_SHADER_TRIANGLE_ATTRIBUTES(InThreadsX) [numthreads(InThreadsX, 1, 1)][outputtopology("triangle")]` _[#if PLATFORM_SUPPORTS_MESH_SHADERS_TIER0]_
- L95 `#define AMPLIFICATION_SHADER_LINE_ATTRIBUTES(InThreadsX) [numthreads(InThreadsX, 1, 1)][outputtopology("line")]` _[#if PLATFORM_SUPPORTS_MESH_SHADERS_TIER0]_
- L97 `#define MESH_SHADER_VERTEX_EXPORT(VertexType, InMaxVertexCount) out vertices VertexType OutVertices[InMaxVertexCount]` _[#if PLATFORM_SUPPORTS_MESH_SHADERS_TIER0]_
- L98 `#define MESH_SHADER_TRIANGLE_EXPORT(InMaxTriangleCount) out indices uint3 OutTriangles[InMaxTriangleCount]` _[#if PLATFORM_SUPPORTS_MESH_SHADERS_TIER0]_
- L99 `#define MESH_SHADER_LINE_EXPORT(InMaxLineCount) out indices uint2 OutLines[InMaxLineCount]` _[#if PLATFORM_SUPPORTS_MESH_SHADERS_TIER0]_
- L101 `#define MESH_SHADER_WRITE_VERTEX(InVertexIndex, Value) OutVertices[InVertexIndex] = Value;` _[#if PLATFORM_SUPPORTS_MESH_SHADERS_TIER0]_
- L102 `#define MESH_SHADER_WRITE_TRIANGLE(InTriangleIndex, Value) OutTriangles[InTriangleIndex] = Value;` _[#if PLATFORM_SUPPORTS_MESH_SHADERS_TIER0]_
- L103 `#define MESH_SHADER_WRITE_LINE(InLineIndex, Value) OutLines[InLineIndex] = Value;` _[#if PLATFORM_SUPPORTS_MESH_SHADERS_TIER0]_
- L107 `#define MESH_SHADER_PRIMITIVE_EXPORT(PrimitiveType, InMaxPrimitiveCount) out primitives PrimitiveType OutPrimitives[InMaxPrimitiveCount]` _[#if PLATFORM_SUPPORTS_MESH_SHADERS_TIER1]_
- L109 `#define MESH_SHADER_WRITE_PRIMITIVE(InPrimitiveIndex, Value) OutPrimitives[InPrimitiveIndex] = Value;` _[#if PLATFORM_SUPPORTS_MESH_SHADERS_TIER1]_
- L113 `#define PLATFORM_NEEDS_PRECISE_SHADOW_DEPTH 1`
- L116 `#define COMPILER_SUPPORTS_ULONG_TYPES 1` _[#if __SHADER_TARGET_MAJOR == 6 && __SHADER_TARGET_MINOR >= 6]_
- L117 `#define COMPILER_SUPPORTS_UINT64_IMAGE_ATOMICS (1 && COMPILER_SUPPORTS_ULONG_TYPES)` _[#if __SHADER_TARGET_MAJOR == 6 && __SHADER_TARGET_MINOR >= 6]_
- L120 `#define UlongType uint64_t` _[#if __SHADER_TARGET_MAJOR == 6 && __SHADER_TARGET_MINOR >= 6 && COMPILER_SUPPORTS_ULONG_TYPES]_
- L152 `#define COMPILER_SUPPORTS_WAVE_MATCH_INTRINSICS 1` _[#if __SHADER_TARGET_MAJOR >= 6 && __SHADER_TARGET_MINOR >= 5]_
- L158 `#define UE_BINDLESS_INDEX(Index) NonUniformResourceIndex(Index)` _[#if PLATFORM_SUPPORTS_BINDLESS && (RAYCALLABLESHADER \|\| RAYHITGROUPSHADER \|\| RAYGENSHADER \|\| RAYMISSSHADER)]_
- L160 `#define UE_BINDLESS_INDEX(Index) Index` _[#if PLATFORM_SUPPORTS_BINDLESS && !((RAYCALLABLESHADER \|\| RAYHITGROUPSHADER \|\| RAYGENSHADER \|\| RAYMISSSHADER))]_
- L163 `#define GetSRVFromHeap(Type, Index) ResourceDescriptorHeap[UE_BINDLESS_INDEX(Index)]` _[#if PLATFORM_SUPPORTS_BINDLESS]_
- L164 `#define GetUAVFromHeap(Type, Index) ResourceDescriptorHeap[UE_BINDLESS_INDEX(Index)]` _[#if PLATFORM_SUPPORTS_BINDLESS]_
- L165 `#define GetCBVFromHeap(Type, Index) ResourceDescriptorHeap[UE_BINDLESS_INDEX(Index)]` _[#if PLATFORM_SUPPORTS_BINDLESS]_
- L166 `#define GetSamplerFromHeap(Type, Index) SamplerDescriptorHeap[UE_BINDLESS_INDEX(Index)]` _[#if PLATFORM_SUPPORTS_BINDLESS]_
- L8 #pragma `message("UESHADERMETADATA_VERSION ACD85E2E-2A94-4B29-B94B-608B96CABB3C")`

#### Functions (6)

- L42-75 _function_ `void UEReportAssertWithPayload(uint AssertID, uint4 Payload)` _[#if PLATFORM_SUPPORTS_DIAGNOSTIC_BUFFER && (PIXELSHADER \|\| COMPUTESHADER \|\| RAYGENSHADER)]_
- L122-125 _function_ `UlongType PackUlongType(uint2 Value)` _[#if __SHADER_TARGET_MAJOR == 6 && __SHADER_TARGET_MINOR >= 6 && COMPILER_SUPPORTS_ULONG_TYPES]_
- L127-130 _function_ `uint2 UnpackUlongType(UlongType Value)` _[#if __SHADER_TARGET_MAJOR == 6 && __SHADER_TARGET_MINOR >= 6 && COMPILER_SUPPORTS_ULONG_TYPES]_
- L134-137 _function_ `void ImageInterlockedMaxUInt64(RWTexture2D<UlongType> Dest, uint2 Coord, UlongType Value)` _[#if __SHADER_TARGET_MAJOR == 6 && __SHADER_TARGET_MINOR >= 6 && COMPILER_SUPPORTS_UINT64_IMAGE_ATOMICS]_
- L139-142 _function_ `void ImageInterlockedAddUInt64(RWTexture2D<UlongType> Dest, uint2 Coord, UlongType Value)` _[#if __SHADER_TARGET_MAJOR == 6 && __SHADER_TARGET_MINOR >= 6 && COMPILER_SUPPORTS_UINT64_IMAGE_ATOMICS]_
- L144-147 _function_ `void ImageInterlockedOrUInt64(RWTexture2D<UlongType> Dest, uint2 Coord, UlongType Value)` _[#if __SHADER_TARGET_MAJOR == 6 && __SHADER_TARGET_MINOR >= 6 && COMPILER_SUPPORTS_UINT64_IMAGE_ATOMICS]_

#### Prototypes (7)

- L23 _prototype_ `SamplerState D3DStaticPointWrappedSampler : register(s0, space1000)` — Static sampler table must match D3D12RootSignature.cpp _[#if PLATFORM_SUPPORTS_STATIC_SAMPLERS]_
- L24 _prototype_ `SamplerState D3DStaticPointClampedSampler : register(s1, space1000)` _[#if PLATFORM_SUPPORTS_STATIC_SAMPLERS]_
- L25 _prototype_ `SamplerState D3DStaticBilinearWrappedSampler : register(s2, space1000)` _[#if PLATFORM_SUPPORTS_STATIC_SAMPLERS]_
- L26 _prototype_ `SamplerState D3DStaticBilinearClampedSampler : register(s3, space1000)` _[#if PLATFORM_SUPPORTS_STATIC_SAMPLERS]_
- L27 _prototype_ `SamplerState D3DStaticTrilinearWrappedSampler : register(s4, space1000)` _[#if PLATFORM_SUPPORTS_STATIC_SAMPLERS]_
- L28 _prototype_ `SamplerState D3DStaticTrilinearClampedSampler : register(s5, space1000)` _[#if PLATFORM_SUPPORTS_STATIC_SAMPLERS]_
- L40 _prototype_ `RWStructuredBuffer<uint> UEDiagnosticBuffer : UE_HLSL_REGISTER(u, 0, UE_HLSL_SPACE_DIAGNOSTIC)` — Diagnostic buffer which will be automatically bound by the RHI as a root parameter Counterpart to FD3D12DiagnosticBuffer::FQueue.Lanes in D3D12Adapter.h Diagnostic message layout: [uint counter, uint message_id, uint4 payload] (6 DWORDs total) _[#if PLATFORM_SUPPORTS_DIAGNOSTIC_BUFFER && (PIXELSHADER \|\| COMPUTESHADER \|\| RAYGENSHADER)]_

### `Shaders/Public/Platform/D3D/D3DRootConstants.ush` (Public)

- lines: 20; parse: all-branches
- includes: L5 `/Engine/Shared/HLSLReservedSpaces.h`
- L3 #pragma `once`

#### Structs / classes (1)

- L7-10 _struct_ **`FUERootConstants`** `struct FUERootConstants`
  - L9 _member_ `uint4 Values;`

#### Functions (5)

- L14 _function_ `uint4 GetAllRootConstants()`
- L16 _function_ `uint GetRootConstant0()`
- L17 _function_ `uint GetRootConstant1()`
- L18 _function_ `uint GetRootConstant2()`
- L19 _function_ `uint GetRootConstant3()`

#### Prototypes (1)

- L12 _prototype_ `ConstantBuffer<FUERootConstants> UERootConstants : UE_HLSL_REGISTER(b, 0, UE_HLSL_SPACE_SHADER_ROOT_CONSTANTS)`

### `Shaders/Public/Platform/D3D/PlatformBindlessResources.ush` (Public)

- lines: 28; parse: all-branches
- includes: L7 `/Engine/Shared/RayTracingBuiltInResources.h` [UE_BINDLESS_ENABLED && (RAYCALLABLESHADER \|\| RAYHITGROUPSHADER \|\| RAYGENSHADER \|\| RAYMISSSHADER \|\| COMPUTESHADER)]

#### Macros (#define, 1)

- L6 `#define OVERRIDE_RAY_TRACING_HIT_GROUP_SYSTEM_RESOURCES 1` _[#if UE_BINDLESS_ENABLED && (RAYCALLABLESHADER \|\| RAYHITGROUPSHADER \|\| RAYGENSHADER \|\| RAYMISSSHADER \|\| COMPUTESHADER)]_
- L3 #pragma `once`

#### Structs / classes (1)

- L10-16 _struct_ **`FD3DHitGroupSystemParameters`** `struct FD3DHitGroupSystemParameters` — Combine the common FHitGroupSystemRootConstants with bindless parameters _[#if UE_BINDLESS_ENABLED && (RAYCALLABLESHADER \|\| RAYHITGROUPSHADER \|\| RAYGENSHADER \|\| RAYMISSSHADER \|\| COMPUTESHADER)]_
  - L12 _member_ `FHitGroupSystemRootConstants RootConstants;` _[#if UE_BINDLESS_ENABLED && (RAYCALLABLESHADER \|\| RAYHITGROUPSHADER \|\| RAYGENSHADER \|\| RAYMISSSHADER \|\| COMPUTESHADER)]_
  - L14 _member_ `uint BindlessHitGroupSystemIndexBuffer;` _[#if UE_BINDLESS_ENABLED && (RAYCALLABLESHADER \|\| RAYHITGROUPSHADER \|\| RAYGENSHADER \|\| RAYMISSSHADER \|\| COMPUTESHADER)]_
  - L15 _member_ `uint BindlessHitGroupSystemVertexBuffer;` _[#if UE_BINDLESS_ENABLED && (RAYCALLABLESHADER \|\| RAYHITGROUPSHADER \|\| RAYGENSHADER \|\| RAYMISSSHADER \|\| COMPUTESHADER)]_

#### Global resources (textures / buffers / samplers) (2)

- L23 _resource_ `ByteAddressBuffer HitGroupSystemIndexBuffer;` — Will get filled in with the bindless index in D3DHitGroupSystemParameters.BindlessHitGroupSystemIndexBuffer _[#if UE_BINDLESS_ENABLED && (RAYCALLABLESHADER \|\| RAYHITGROUPSHADER \|\| RAYGENSHADER \|\| RAYMISSSHADER \|\| COMPUTESHADER)]_
- L26 _resource_ `ByteAddressBuffer HitGroupSystemVertexBuffer;` — Will get filled in with the bindless index in D3DHitGroupSystemParameters.BindlessHitGroupSystemVertexBuffer _[#if UE_BINDLESS_ENABLED && (RAYCALLABLESHADER \|\| RAYHITGROUPSHADER \|\| RAYGENSHADER \|\| RAYMISSSHADER \|\| COMPUTESHADER)]_

#### static const (1)

- L20 _static_const_ `static const FHitGroupSystemRootConstants HitGroupSystemRootConstants = D3DHitGroupSystemParameters.RootConstants;` _[#if UE_BINDLESS_ENABLED && (RAYCALLABLESHADER \|\| RAYHITGROUPSHADER \|\| RAYGENSHADER \|\| RAYMISSSHADER \|\| COMPUTESHADER)]_

#### Prototypes (1)

- L18 _prototype_ `ConstantBuffer<FD3DHitGroupSystemParameters> D3DHitGroupSystemParameters : UE_HLSL_REGISTER(b, RAY_TRACING_SYSTEM_ROOTCONSTANT_REGISTER, UE_HLSL_SPACE_RAY_TRACING_SYSTEM)` _[#if UE_BINDLESS_ENABLED && (RAYCALLABLESHADER \|\| RAYHITGROUPSHADER \|\| RAYGENSHADER \|\| RAYMISSSHADER \|\| COMPUTESHADER)]_
