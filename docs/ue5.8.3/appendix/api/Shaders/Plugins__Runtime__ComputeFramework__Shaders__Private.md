# Shaders / Plugins/Runtime/ComputeFramework/Shaders/Private

- files: 5; lines: 326
- record kinds: cpp_binding=1, define=13, function=50, include=3, parameter=2, resource=2

### `Plugins/Runtime/ComputeFramework/Shaders/Private/BufferAlias.ush` (Private)

- lines: 46; parse: all-branches
- L7 #pragma `once`

#### Functions (6)

- L9-14 _function_ `void ReadRawBuffer(in StructuredBuffer<float> InBuffer, in uint InBufferIndex, out float3 OutValue)`
- L15-20 _function_ `void ReadRawBuffer(in RWStructuredBuffer<float> InBuffer, in uint InBufferIndex, out float3 OutValue)`
- L21-26 _function_ `void WriteRawBuffer(in RWStructuredBuffer<float> InBuffer, in uint InBufferIndex, in float3 InValue)`
- L28-33 _function_ `void ReadRawBuffer(in StructuredBuffer<int> InBuffer, in uint InBufferIndex, out int3 OutValue)`
- L34-39 _function_ `void ReadRawBuffer(in RWStructuredBuffer<int> InBuffer, in uint InBufferIndex, out int3 OutValue)`
- L40-45 _function_ `void WriteRawBuffer(in RWStructuredBuffer<int> InBuffer, in uint InBufferIndex, in int3 InValue)`

### `Plugins/Runtime/ComputeFramework/Shaders/Private/ComputeDataInterfaceBuffer.ush` (Private)

- lines: 226; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Macros (#define, 4)

- L4 `#define VALUE_TYPE {ValueType}`
- L5 `#define VALUE_TYPE_STRIDE_BYTES {ValueTypeStride}`
- L7 `#define VALUE_TYPE_SUPPORTS_ATOMIC {SupportAtomic}`
- L9 `#define BUFFER_SPLIT_READ_WRITE {SplitReadWrite}`
- L222 #undef `VALUE_TYPE`; L223 #undef `VALUE_TYPE_STRIDE_BYTES`; L224 #undef `VALUE_TYPE_SUPPORTS_ATOMIC`; L225 #undef `BUFFER_SPLIT_READ_WRITE`

#### Global resources (textures / buffers / samplers) (2)

- L13 _resource_ `ByteAddressBuffer {DataInterfaceName}_BufferSRV;` _[#if BUFFER_SPLIT_READ_WRITE]_
- L15 _resource_ `RWByteAddressBuffer {DataInterfaceName}_BufferUAV;`

#### Global parameters (uniforms) (1)

- L11 _parameter_ `uint {DataInterfaceName}_BufferElementCount;`

#### Functions (43)

- L17-20 _function_ `void ReadBufferSRV_{DataInterfaceName}(in uint Index, out uint ReturnValue)`
- L21-24 _function_ `void ReadBufferSRV_{DataInterfaceName}(in uint Index, out uint2 ReturnValue)`
- L25-28 _function_ `void ReadBufferSRV_{DataInterfaceName}(in uint Index, out uint3 ReturnValue)`
- L29-32 _function_ `void ReadBufferSRV_{DataInterfaceName}(in uint Index, out uint4 ReturnValue)`
- L33-36 _function_ `void ReadBufferUAV_{DataInterfaceName}(in uint Index, out uint ReturnValue)`
- L37-40 _function_ `void ReadBufferUAV_{DataInterfaceName}(in uint Index, out uint2 ReturnValue)`
- L41-44 _function_ `void ReadBufferUAV_{DataInterfaceName}(in uint Index, out uint3 ReturnValue)`
- L45-48 _function_ `void ReadBufferUAV_{DataInterfaceName}(in uint Index, out uint4 ReturnValue)`
- L49-52 _function_ `void WriteBuffer_{DataInterfaceName}(in uint Index, in uint Value)`
- L53-56 _function_ `void WriteBuffer_{DataInterfaceName}(in uint Index, in uint2 Value)`
- L57-60 _function_ `void WriteBuffer_{DataInterfaceName}(in uint Index, in uint3 Value)`
- L61-64 _function_ `void WriteBuffer_{DataInterfaceName}(in uint Index, in uint4 Value)`
- L66-69 _function_ `void ReadBufferSRV_{DataInterfaceName}(in uint Index, out int ReturnValue)`
- L70-73 _function_ `void ReadBufferSRV_{DataInterfaceName}(in uint Index, out int2 ReturnValue)`
- L74-77 _function_ `void ReadBufferSRV_{DataInterfaceName}(in uint Index, out int3 ReturnValue)`
- L78-81 _function_ `void ReadBufferSRV_{DataInterfaceName}(in uint Index, out int4 ReturnValue)`
- L82-85 _function_ `void ReadBufferUAV_{DataInterfaceName}(in uint Index, out int ReturnValue)`
- L86-89 _function_ `void ReadBufferUAV_{DataInterfaceName}(in uint Index, out int2 ReturnValue)`
- L90-93 _function_ `void ReadBufferUAV_{DataInterfaceName}(in uint Index, out int3 ReturnValue)`
- L94-97 _function_ `void ReadBufferUAV_{DataInterfaceName}(in uint Index, out int4 ReturnValue)`
- L98-101 _function_ `void WriteBuffer_{DataInterfaceName}(in uint Index, in int Value)`
- L102-105 _function_ `void WriteBuffer_{DataInterfaceName}(in uint Index, in int2 Value)`
- L106-109 _function_ `void WriteBuffer_{DataInterfaceName}(in uint Index, in int3 Value)`
- L110-113 _function_ `void WriteBuffer_{DataInterfaceName}(in uint Index, in int4 Value)`
- L115-118 _function_ `void ReadBufferSRV_{DataInterfaceName}(in uint Index, out float ReturnValue)`
- L119-122 _function_ `void ReadBufferSRV_{DataInterfaceName}(in uint Index, out float2 ReturnValue)`
- L123-126 _function_ `void ReadBufferSRV_{DataInterfaceName}(in uint Index, out float3 ReturnValue)`
- L127-130 _function_ `void ReadBufferSRV_{DataInterfaceName}(in uint Index, out float4 ReturnValue)`
- L131-134 _function_ `void ReadBufferUAV_{DataInterfaceName}(in uint Index, out float ReturnValue)`
- L135-138 _function_ `void ReadBufferUAV_{DataInterfaceName}(in uint Index, out float2 ReturnValue)`
- L139-142 _function_ `void ReadBufferUAV_{DataInterfaceName}(in uint Index, out float3 ReturnValue)`
- L143-146 _function_ `void ReadBufferUAV_{DataInterfaceName}(in uint Index, out float4 ReturnValue)`
- L147-150 _function_ `void WriteBuffer_{DataInterfaceName}(in uint Index, in float Value)`
- L151-154 _function_ `void WriteBuffer_{DataInterfaceName}(in uint Index, in float2 Value)`
- L155-158 _function_ `void WriteBuffer_{DataInterfaceName}(in uint Index, in float3 Value)`
- L159-162 _function_ `void WriteBuffer_{DataInterfaceName}(in uint Index, in float4 Value)`
- L164-167 _function_ `uint ReadNumValues_{DataInterfaceName}()`
- L169-178 _function_ `VALUE_TYPE ReadValue_{DataInterfaceName}(uint Index)`
- L180-185 _function_ `VALUE_TYPE ReadValueUAV_{DataInterfaceName}(uint Index)`
- L187-190 _function_ `void WriteValue_{DataInterfaceName}(uint Index, VALUE_TYPE Value)`
- L192-200 _function_ `VALUE_TYPE WriteAtomicAdd_{DataInterfaceName}(uint Index, VALUE_TYPE Value)`
- L202-210 _function_ `VALUE_TYPE WriteAtomicMin_{DataInterfaceName}(uint Index, VALUE_TYPE Value)`
- L212-220 _function_ `VALUE_TYPE WriteAtomicMax_{DataInterfaceName}(uint Index, VALUE_TYPE Value)`

### `Plugins/Runtime/ComputeFramework/Shaders/Private/ComputeDataInterfaceDispatch.ush` (Private)

- lines: 9; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global parameters (uniforms) (1)

- L3 _parameter_ `uint3 {DataInterfaceName}_NumThreads;`

#### Functions (1)

- L5-8 _function_ `uint3 ReadNumThreads_{DataInterfaceName}()`

### `Plugins/Runtime/ComputeFramework/Shaders/Private/ComputeKernel.usf` (Private)

- lines: 7; parse: all-branches
- includes: L3 `/Plugin/ComputeFramework/Private/ComputeKernelCommon.ush`, L6 `/Plugin/ComputeFramework/Generated/ComputeKernel.ush`

#### C++ shader bindings (IMPLEMENT_* naming this file, 1)

- `__` → entry not found in file (macro-generated or #include'd); C++ `FComputeKernelShader` SF_Compute via IMPLEMENT_SHADER_TYPE (Plugins/Runtime/ComputeFramework/Source/ComputeFramework/Private/ComputeKernelShader.cpp:7)

### `Plugins/Runtime/ComputeFramework/Shaders/Private/ComputeKernelCommon.ush` (Private)

- lines: 38; parse: all-branches
- includes: L5 `/Engine/Private/Common.ush`

#### Macros (#define, 9)

- L10 `#define KERNEL_ENTRY_POINT(EntryPointName) void EntryPointName( uint Gidx : SV_GroupIndex, uint3 Gid : SV_GroupID, uint3 GTid: SV_GroupThreadID, uint3 DTid : SV_DispatchThreadID)` (6 lines)
- L20 `#define KERNEL_EXTERN_READ(Name, ...) `
- L21 `#define KERNEL_EXTERN_WRITE(Name, ...) `
- L27 `#define _DI_CAT_IMPL_(A, B) A##B`
- L28 `#define _DI_CAT_(A, B) _DI_CAT_IMPL_(A, B)`
- L29 `#define DI_UNIFORM_LOCAL(Name) _DI_CAT_(DI_UID, Name)`
- L30 `#define DI_FUNCTION_LOCAL(Name) _DI_CAT_(Name, DI_UID)`
- L36 `#define DI_IMPL_READ(Name, ReturnType, ...) ReturnType DI_FUNCTION_LOCAL(Name)(__VA_ARGS__)`
- L37 `#define DI_IMPL_WRITE(Name, ...) void DI_FUNCTION_LOCAL(Name)(__VA_ARGS__)`
- L3 #pragma `once`
