# Shaders / Shaders/Public/Platform/Vulkan

- files: 2; lines: 243
- record kinds: define=49, function=5, include=1, member=7, parameter=11, resource=10, static_const=7, struct=3, typedef=1

### `Shaders/Public/Platform/Vulkan/VulkanCommon.ush` (Public)

- lines: 184; parse: all-branches
- includes: L85 `/Engine/Shared/RayTracingBuiltInResources.h` [UE_BINDLESS_ENABLED && (RAYCALLABLESHADER \|\| RAYHITGROUPSHADER \|\| RAYGENSHADER \|\| RAYMISSSHADER)]

#### Macros (#define, 39)

- L12 `#define COMPILER_SUPPORTS_ULONG_TYPES 1`
- L13 `#define COMPILER_SUPPORTS_UINT64_IMAGE_ATOMICS (1 && COMPILER_SUPPORTS_ULONG_TYPES)`
- L17 `#define UlongType uint64_t` _[#if COMPILER_SUPPORTS_ULONG_TYPES]_
- L50 `#define VULKAN_HEAP_NAME_INNER(Prefix, Type) Prefix##Type` _[#if UE_BINDLESS_ENABLED]_
- L51 `#define VULKAN_HEAP_NAME(Prefix, Type) VULKAN_HEAP_NAME_INNER(Prefix, Type)` _[#if UE_BINDLESS_ENABLED]_
- L52 `#define VULKAN_SAMPLER_HEAP(Type) VULKAN_HEAP_NAME(BINDLESS_SAMPLER_ARRAY_PREFIX,Type)` _[#if UE_BINDLESS_ENABLED]_
- L53 `#define VULKAN_SRV_HEAP(Type) VULKAN_HEAP_NAME(BINDLESS_SRV_ARRAY_PREFIX,Type)` _[#if UE_BINDLESS_ENABLED]_
- L54 `#define VULKAN_UAV_HEAP(Type) VULKAN_HEAP_NAME(BINDLESS_UAV_ARRAY_PREFIX,Type)` _[#if UE_BINDLESS_ENABLED]_
- L55 `#define VULKAN_CBV_HEAP(Type) VULKAN_HEAP_NAME(BINDLESS_CBV_ARRAY_PREFIX,Type)` _[#if UE_BINDLESS_ENABLED]_
- L58 `#define VULKAN_HEAP_ACCESS(BindlessIndex) NonUniformResourceIndex(BindlessIndex)` _[#if UE_BINDLESS_ENABLED && (RAYCALLABLESHADER \|\| RAYHITGROUPSHADER \|\| RAYGENSHADER \|\| RAYMISSSHADER)]_
- L60 `#define VULKAN_HEAP_ACCESS(BindlessIndex) BindlessIndex` _[#if UE_BINDLESS_ENABLED && !((RAYCALLABLESHADER \|\| RAYHITGROUPSHADER \|\| RAYGENSHADER \|\| RAYMISSSHADER))]_
- L63 `#define UE_BINDLESS_SRV_HEAP_DECL(Type) Type VULKAN_SRV_HEAP(Type)[];` _[#if UE_BINDLESS_ENABLED]_
- L64 `#define UE_BINDLESS_UAV_HEAP_DECL(Type) Type VULKAN_UAV_HEAP(Type)[];` _[#if UE_BINDLESS_ENABLED]_
- L65 `#define UE_BINDLESS_CBV_HEAP_DECL(Type) Type VULKAN_CBV_HEAP(Type)[];` _[#if UE_BINDLESS_ENABLED]_
- L66 `#define UE_BINDLESS_SAMPLER_HEAP_DECL(Type) Type VULKAN_SAMPLER_HEAP(Type)[];` _[#if UE_BINDLESS_ENABLED]_
- L68 `#define GetSRVFromHeap(Type, Index) VULKAN_SRV_HEAP(Type)[VULKAN_HEAP_ACCESS(Index)]` _[#if UE_BINDLESS_ENABLED]_
- L69 `#define GetUAVFromHeap(Type, Index) VULKAN_UAV_HEAP(Type)[VULKAN_HEAP_ACCESS(Index)]` _[#if UE_BINDLESS_ENABLED]_
- L70 `#define GetCBVFromHeap(Type, Index) VULKAN_CBV_HEAP(Type)[VULKAN_HEAP_ACCESS(Index)]` _[#if UE_BINDLESS_ENABLED]_
- L71 `#define GetSamplerFromHeap(Type, Index) VULKAN_SAMPLER_HEAP(Type)[VULKAN_HEAP_ACCESS(Index)]` _[#if UE_BINDLESS_ENABLED]_
- L75 `#define COMPILER_SUPPORTS_WAVE_SIZE 1` _[#if VULKAN_SUPPORTS_SUBGROUP_SIZE_CONTROL]_
- L80 `#define WAVESIZE(N) VULKAN_WAVESIZE(N)` _[#if VULKAN_SUPPORTS_SUBGROUP_SIZE_CONTROL]_
- L84 `#define OVERRIDE_RAY_TRACING_HIT_GROUP_SYSTEM_RESOURCES 1` _[#if UE_BINDLESS_ENABLED && (RAYCALLABLESHADER \|\| RAYHITGROUPSHADER \|\| RAYGENSHADER \|\| RAYMISSSHADER)]_
- L118 `#define MESH_SHADER_TRIANGLE_ATTRIBUTES(InThreadsX) [numthreads(InThreadsX, 1, 1)][outputtopology("triangle")]` _[#if PLATFORM_SUPPORTS_MESH_SHADERS_TIER0]_
- L119 `#define MESH_SHADER_LINE_ATTRIBUTES(InThreadsX) [numthreads(InThreadsX, 1, 1)][outputtopology("line")]` _[#if PLATFORM_SUPPORTS_MESH_SHADERS_TIER0]_
- L121 `#define AMPLIFICATION_SHADER_TRIANGLE_ATTRIBUTES(InThreadsX) [numthreads(InThreadsX, 1, 1)][outputtopology("triangle")]` _[#if PLATFORM_SUPPORTS_MESH_SHADERS_TIER0]_
- L122 `#define AMPLIFICATION_SHADER_LINE_ATTRIBUTES(InThreadsX) [numthreads(InThreadsX, 1, 1)][outputtopology("line")]` _[#if PLATFORM_SUPPORTS_MESH_SHADERS_TIER0]_
- L124 `#define MESH_SHADER_VERTEX_EXPORT(VertexType, InMaxVertexCount) out vertices VertexType OutVertices[InMaxVertexCount]` _[#if PLATFORM_SUPPORTS_MESH_SHADERS_TIER0]_
- L125 `#define MESH_SHADER_TRIANGLE_EXPORT(InMaxTriangleCount) out indices uint3 OutTriangles[InMaxTriangleCount]` _[#if PLATFORM_SUPPORTS_MESH_SHADERS_TIER0]_
- L126 `#define MESH_SHADER_LINE_EXPORT(InMaxLineCount) out indices uint2 OutLines[InMaxLineCount]` _[#if PLATFORM_SUPPORTS_MESH_SHADERS_TIER0]_
- L128 `#define MESH_SHADER_WRITE_VERTEX(InVertexIndex, Value) OutVertices[InVertexIndex] = Value;` _[#if PLATFORM_SUPPORTS_MESH_SHADERS_TIER0]_
- L129 `#define MESH_SHADER_WRITE_TRIANGLE(InTriangleIndex, Value) OutTriangles[InTriangleIndex] = Value;` _[#if PLATFORM_SUPPORTS_MESH_SHADERS_TIER0]_
- L130 `#define MESH_SHADER_WRITE_LINE(InLineIndex, Value) OutLines[InLineIndex] = Value;` _[#if PLATFORM_SUPPORTS_MESH_SHADERS_TIER0]_
- L134 `#define MESH_SHADER_PRIMITIVE_EXPORT(PrimitiveType, InMaxPrimitiveCount) out primitives PrimitiveType OutPrimitives[InMaxPrimitiveCount]` _[#if PLATFORM_SUPPORTS_MESH_SHADERS_TIER1]_
- L136 `#define MESH_SHADER_WRITE_PRIMITIVE(InPrimitiveIndex, Value) OutPrimitives[InPrimitiveIndex] = Value;` _[#if PLATFORM_SUPPORTS_MESH_SHADERS_TIER1]_
- L141 `#define MESH_SHADING_PER_PRIMITIVE_ATTRIBUTE [[vk::ext_decorate(5271)]]` _[#if PIXELSHADER]_
- L142 `#define MESH_SHADING_COMPATIBLE_PS_ENTRY_POINT [[vk::ext_extension("SPV_EXT_mesh_shader")]] [[vk::ext_capability(5283)]]` _[#if PIXELSHADER]_
- L167 `#define GetGlobalSampler(Filter, WrapMode) VulkanGlobal##Filter##WrapMode##Sampler`
- L181 `#define UE_DECL(Name) [[vk::constant_id(Name##_INDEX)]] const int Name = 0` _[#if PLATFORM_SUPPORTS_SPECIALIZATION_CONSTANTS && ENABLE_SPECIALIZATION_CONSTANTS]_
- L182 `#define UE_EVAL(Name) Name` _[#if PLATFORM_SUPPORTS_SPECIALIZATION_CONSTANTS && ENABLE_SPECIALIZATION_CONSTANTS]_
- L7 #pragma `once`; L10 #pragma `message("UESHADERMETADATA_VERSION 2252475E-CF8A-45F3-85D7-E06B3EDCCCFC")`

#### Structs / classes (3)

- L87-90 _struct_ **`VulkanShaderRecordLooseParameterData`** `struct VulkanShaderRecordLooseParameterData` _[#if UE_BINDLESS_ENABLED && (RAYCALLABLESHADER \|\| RAYHITGROUPSHADER \|\| RAYGENSHADER \|\| RAYMISSSHADER)]_
  - L89 _member_ `COMPILER_DEFINE VULKAN_WAVESIZE(N) uint VulkanShaderRecordDummyGlobals;` _[#if UE_BINDLESS_ENABLED && (RAYCALLABLESHADER \|\| RAYHITGROUPSHADER \|\| RAYGENSHADER \|\| RAYMISSSHADER)]_
- L94-105 _struct_ **`FVulkanHitGroupSystemParameters`** `struct FVulkanHitGroupSystemParameters` — Combine the common FHitGroupSystemRootConstants with bindless parameters :todo-jn: must match with VulkanRayTracing.h decl until we create a common header like RayTracingBuiltInResources.h _[#if UE_BINDLESS_ENABLED && (RAYCALLABLESHADER \|\| RAYHITGROUPSHADER \|\| RAYGENSHADER \|\| RAYMISSSHADER)]_
  - L96 _member_ `FHitGroupSystemRootConstants RootConstants;` _[#if UE_BINDLESS_ENABLED && (RAYCALLABLESHADER \|\| RAYHITGROUPSHADER \|\| RAYGENSHADER \|\| RAYMISSSHADER)]_
  - L98 _member_ `uint BindlessHitGroupSystemIndexBuffer;` _[#if UE_BINDLESS_ENABLED && (RAYCALLABLESHADER \|\| RAYHITGROUPSHADER \|\| RAYGENSHADER \|\| RAYMISSSHADER)]_
  - L99 _member_ `uint BindlessHitGroupSystemVertexBuffer;` _[#if UE_BINDLESS_ENABLED && (RAYCALLABLESHADER \|\| RAYHITGROUPSHADER \|\| RAYGENSHADER \|\| RAYMISSSHADER)]_
  - L101 _member_ `uint BindlessUniformBuffers[32];` _[#if UE_BINDLESS_ENABLED && (RAYCALLABLESHADER \|\| RAYHITGROUPSHADER \|\| RAYGENSHADER \|\| RAYMISSSHADER)]_
  - L104 _member_ `VulkanShaderRecordLooseParameterData Globals;` — Globals must be kept at the end of FVulkanHitGroupSystemParameters _[#if UE_BINDLESS_ENABLED && (RAYCALLABLESHADER \|\| RAYHITGROUPSHADER \|\| RAYGENSHADER \|\| RAYMISSSHADER)]_
- L172-175 _struct_ **`FVulkanPushConstants`** `struct FVulkanPushConstants` — Push constants are currently only used for ray tracing's static UBs (Scene, View, NaniteRayTracing, LumenHardwareRayTracing) _[#if UE_BINDLESS_ENABLED && RAYGENSHADER]_
  - L174 _member_ `uint StaticUniformBufferBindings[8];` — keep in sync with FRHIShaderBindingLayout::MaxUniformBufferEntries _[#if UE_BINDLESS_ENABLED && RAYGENSHADER]_

#### Global resources (textures / buffers / samplers) (10)

- L107 _resource_ `[[vk::shader_record_ext]] ConstantBuffer<FVulkanHitGroupSystemParameters> VulkanHitGroupSystemParameters;` _[#if UE_BINDLESS_ENABLED && (RAYCALLABLESHADER \|\| RAYHITGROUPSHADER \|\| RAYGENSHADER \|\| RAYMISSSHADER)]_
- L112 _resource_ `ByteAddressBuffer HitGroupSystemIndexBuffer;` — Will get filled in with the bindless index in VulkanHitGroupSystemParameters.BindlessHitGroupSystemIndexBuffer _[#if UE_BINDLESS_ENABLED && (RAYCALLABLESHADER \|\| RAYHITGROUPSHADER \|\| RAYGENSHADER \|\| RAYMISSSHADER)]_
- L114 _resource_ `ByteAddressBuffer HitGroupSystemVertexBuffer;` — Will get filled in with the bindless index in VulkanHitGroupSystemParameters.BindlessHitGroupSystemVertexBuffer _[#if UE_BINDLESS_ENABLED && (RAYCALLABLESHADER \|\| RAYHITGROUPSHADER \|\| RAYGENSHADER \|\| RAYMISSSHADER)]_
- L159 _resource_ `SamplerState VulkanGlobalPointWrappedSampler;` _[#if !(UE_BINDLESS_ENABLED)]_
- L160 _resource_ `SamplerState VulkanGlobalPointClampedSampler;` _[#if !(UE_BINDLESS_ENABLED)]_
- L161 _resource_ `SamplerState VulkanGlobalBilinearWrappedSampler;` _[#if !(UE_BINDLESS_ENABLED)]_
- L162 _resource_ `SamplerState VulkanGlobalBilinearClampedSampler;` _[#if !(UE_BINDLESS_ENABLED)]_
- L163 _resource_ `SamplerState VulkanGlobalTrilinearWrappedSampler;` _[#if !(UE_BINDLESS_ENABLED)]_
- L164 _resource_ `SamplerState VulkanGlobalTrilinearClampedSampler;` _[#if !(UE_BINDLESS_ENABLED)]_
- L176 _resource_ `[[vk::push_constant]] ConstantBuffer<FVulkanPushConstants> VulkanPushConstants;` _[#if UE_BINDLESS_ENABLED && RAYGENSHADER]_

#### Global parameters (uniforms) (1)

- L151 _parameter_ `SafeTypeGlobalSamplers VULKAN_SAMPLER_HEAP(GlobalSamplers)[];` _[#if UE_BINDLESS_ENABLED]_

#### static const (7)

- L109 _static_const_ `static const FHitGroupSystemRootConstants HitGroupSystemRootConstants = VulkanHitGroupSystemParameters.RootConstants;` _[#if UE_BINDLESS_ENABLED && (RAYCALLABLESHADER \|\| RAYHITGROUPSHADER \|\| RAYGENSHADER \|\| RAYMISSSHADER)]_
- L152 _static_const_ `static const SamplerState VulkanGlobalPointClampedSampler = VULKAN_SAMPLER_HEAP(GlobalSamplers)[0];` _[#if UE_BINDLESS_ENABLED]_
- L153 _static_const_ `static const SamplerState VulkanGlobalPointWrappedSampler = VULKAN_SAMPLER_HEAP(GlobalSamplers)[1];` _[#if UE_BINDLESS_ENABLED]_
- L154 _static_const_ `static const SamplerState VulkanGlobalBilinearClampedSampler = VULKAN_SAMPLER_HEAP(GlobalSamplers)[2];` _[#if UE_BINDLESS_ENABLED]_
- L155 _static_const_ `static const SamplerState VulkanGlobalBilinearWrappedSampler = VULKAN_SAMPLER_HEAP(GlobalSamplers)[3];` _[#if UE_BINDLESS_ENABLED]_
- L156 _static_const_ `static const SamplerState VulkanGlobalTrilinearClampedSampler = VULKAN_SAMPLER_HEAP(GlobalSamplers)[4];` _[#if UE_BINDLESS_ENABLED]_
- L157 _static_const_ `static const SamplerState VulkanGlobalTrilinearWrappedSampler = VULKAN_SAMPLER_HEAP(GlobalSamplers)[5];` _[#if UE_BINDLESS_ENABLED]_

#### typedef / using (1)

- L150 _typedef_ `typedef SamplerState SafeTypeGlobalSamplers;` _[#if UE_BINDLESS_ENABLED]_

#### Functions (5)

- L19-22 _function_ `UlongType PackUlongType(uint2 Value)` _[#if COMPILER_SUPPORTS_ULONG_TYPES]_
- L24-27 _function_ `uint2 UnpackUlongType(UlongType Value)` _[#if COMPILER_SUPPORTS_ULONG_TYPES]_
- L32-35 _function_ `void ImageInterlockedMaxUInt64(RWTexture2D<UlongType> Dest, uint2 Coord, UlongType Value)` _[#if COMPILER_SUPPORTS_UINT64_IMAGE_ATOMICS]_
- L37-40 _function_ `void ImageInterlockedAddUInt64(RWTexture2D<UlongType> Dest, uint2 Coord, UlongType Value)` _[#if COMPILER_SUPPORTS_UINT64_IMAGE_ATOMICS]_
- L42-45 _function_ `void ImageInterlockedOrUInt64(RWTexture2D<UlongType> Dest, uint2 Coord, UlongType Value)` _[#if COMPILER_SUPPORTS_UINT64_IMAGE_ATOMICS]_

### `Shaders/Public/Platform/Vulkan/VulkanSubpassSupport.ush` (Public)

- lines: 59; parse: all-branches

#### Macros (#define, 10)

- L12 `#define USE_MULTI_SAMPLE 1` _[#if COMPILER_DXC && PIXELSHADER && defined(SUBPASS_MSAA_SAMPLES) && SUBPASS_MSAA_SAMPLES > 1]_
- L20 `#define VulkanSubpassDepthFetch() GENERATED_SubpassDepthFetchAttachment.SubpassLoad( )` _[#if COMPILER_DXC && PIXELSHADER]_
- L28 `#define VulkanSubpassFetch0 GENERATED_SubpassFetchAttachment0.SubpassLoad` _[#if COMPILER_DXC && PIXELSHADER]_
- L32 `#define VulkanSubpassFetch1() GENERATED_SubpassFetchAttachment1.SubpassLoad()` _[#if COMPILER_DXC && PIXELSHADER]_
- L36 `#define VulkanSubpassFetch2() GENERATED_SubpassFetchAttachment2.SubpassLoad()` _[#if COMPILER_DXC && PIXELSHADER]_
- L40 `#define VulkanSubpassFetch3() GENERATED_SubpassFetchAttachment3.SubpassLoad()` _[#if COMPILER_DXC && PIXELSHADER]_
- L44 `#define VulkanSubpassFetch4() GENERATED_SubpassFetchAttachment4.SubpassLoad()` _[#if COMPILER_DXC && PIXELSHADER]_
- L48 `#define VulkanSubpassFetch5() GENERATED_SubpassFetchAttachment5.SubpassLoad()` _[#if COMPILER_DXC && PIXELSHADER]_
- L52 `#define VulkanSubpassFetch6() GENERATED_SubpassFetchAttachment6.SubpassLoad()` _[#if COMPILER_DXC && PIXELSHADER]_
- L56 `#define VulkanSubpassFetch7() GENERATED_SubpassFetchAttachment7.SubpassLoad()` _[#if COMPILER_DXC && PIXELSHADER]_
- L6 #pragma `once`

#### Global parameters (uniforms) (10)

- L18-19 _parameter_ `[[vk::input_attachment_index(0)]] SubpassInput<float> GENERATED_SubpassDepthFetchAttachment;` _[#if COMPILER_DXC && PIXELSHADER]_
- L22-24 _parameter_ `[[vk::input_attachment_index(1)]] SubpassInput<float4> GENERATED_SubpassFetchAttachment0;` _[#if COMPILER_DXC && PIXELSHADER]_
- L26 _parameter_ `SubpassInputMS<float4> GENERATED_SubpassFetchAttachment0;` _[#if COMPILER_DXC && PIXELSHADER && !(!defined(USE_MULTI_SAMPLE))]_
- L30-31 _parameter_ `[[vk::input_attachment_index(2)]] SubpassInput<float4> GENERATED_SubpassFetchAttachment1;` _[#if COMPILER_DXC && PIXELSHADER]_
- L34-35 _parameter_ `[[vk::input_attachment_index(3)]] SubpassInput<float4> GENERATED_SubpassFetchAttachment2;` _[#if COMPILER_DXC && PIXELSHADER]_
- L38-39 _parameter_ `[[vk::input_attachment_index(4)]] SubpassInput<float4> GENERATED_SubpassFetchAttachment3;` _[#if COMPILER_DXC && PIXELSHADER]_
- L42-43 _parameter_ `[[vk::input_attachment_index(5)]] SubpassInput<float4> GENERATED_SubpassFetchAttachment4;` _[#if COMPILER_DXC && PIXELSHADER]_
- L46-47 _parameter_ `[[vk::input_attachment_index(6)]] SubpassInput<float4> GENERATED_SubpassFetchAttachment5;` _[#if COMPILER_DXC && PIXELSHADER]_
- L50-51 _parameter_ `[[vk::input_attachment_index(7)]] SubpassInput<float4> GENERATED_SubpassFetchAttachment6;` _[#if COMPILER_DXC && PIXELSHADER]_
- L54-55 _parameter_ `[[vk::input_attachment_index(8)]] SubpassInput<float4> GENERATED_SubpassFetchAttachment7;` _[#if COMPILER_DXC && PIXELSHADER]_
