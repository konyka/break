# Shaders / Plugins/Tests/RHITests/Shaders/Private

- files: 8; lines: 419
- record kinds: cpp_binding=21, entry=22, function=2, include=10, macro_call=4, member=5, parameter=5, resource=20, struct=3

### `Plugins/Tests/RHITests/Shaders/Private/TestBindlessUniformBuffer.usf` (Private)

- lines: 20; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L8 `/Engine/Generated/UniformBuffers/BindlessAccessibleUniformBufferParameters.ush`

#### Entry points (1)

- L13-19 _entry_ `[numthreads(1, 1, 1)] void ReadBindlessUniformBuffer(uint3 GroupID : SV_GroupID)` — stage: **compute** — C++: `FBindlessUniformBufferTestCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Tests/RHITests/Source/RHITests/Private/RHIBindlessTests.cpp:733)

#### Global resources (textures / buffers / samplers) (1)

- L11 _resource_ `RWStructuredBuffer<float4> OutputUAV;`

#### Global parameters (uniforms) (1)

- L10 _parameter_ `uint BindlessUBIndex;`

### `Plugins/Tests/RHITests/Shaders/Private/TestDescriptorRange.usf` (Private)

- lines: 52; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`

#### Entry points (4)

- L15-21 _entry_ `[numthreads(THREADGROUP_SIZE_X, THREADGROUP_SIZE_Y, 1)] void FillFromTextures(uint3 GroupID : SV_GroupID)` — stage: **compute** — C++: `FDescriptorRangeFillFromTexturesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Tests/RHITests/Source/RHITests/Private/RHIBindlessTests.cpp:219)
- L25-32 _entry_ `[numthreads(THREADGROUP_SIZE_X, THREADGROUP_SIZE_Y, 1)] void WriteToUAVs(uint3 GroupID : SV_GroupID)` — stage: **compute** — C++: `FDescriptorRangeWriteToUAVsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Tests/RHITests/Source/RHITests/Private/RHIBindlessTests.cpp:368)
- L34-41 _entry_ `[numthreads(THREADGROUP_SIZE_X, THREADGROUP_SIZE_Y, 1)] void ReadSRVsWriteUAV(uint3 GroupID : SV_GroupID)` — stage: **compute** — C++: `FDescriptorRangeReadSRVsWriteUAVCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Tests/RHITests/Source/RHITests/Private/RHIBindlessTests.cpp:508)
- L43-51 _entry_ `[numthreads(THREADGROUP_SIZE_X, THREADGROUP_SIZE_Y, 1)] void FillFromMixedResources(uint3 GroupID : SV_GroupID)` — stage: **compute** — C++: `FDescriptorRangeFillFromMixedResourcesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Tests/RHITests/Source/RHITests/Private/RHIBindlessTests.cpp:596)

#### Global resources (textures / buffers / samplers) (2)

- L13 _resource_ `RWStructuredBuffer<float4> OutputUAV;`
- L23 _resource_ `StructuredBuffer<float4> InputSRV;`

#### Global parameters (uniforms) (1)

- L11 _parameter_ `FDescriptorRange DescriptorRange;`

#### Top-level macro invocations (3)

- L7 _macro_call_ `DESCRIPTOR_RANGE_HEAP_DECL_SRV(Texture2D<float4>)`
- L8 _macro_call_ `DESCRIPTOR_RANGE_HEAP_DECL_SRV(Buffer<float4>)`
- L9 _macro_call_ `DESCRIPTOR_RANGE_HEAP_DECL_UAV(RWStructuredBuffer<float4>)`

### `Plugins/Tests/RHITests/Shaders/Private/TestDrawInstanced.usf` (Private)

- lines: 28; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`

#### Entry points (2)

- L8-17 _entry_ `void TestDrawInstancedMainVS( in float4 VertexPosition : ATTRIBUTE0, in uint CustomInstanceID : ATTRIBUTE1, out uint OutInstanceID : Texcoord0, out float4 OutPosition : SV_Position )` — stage: **vertex (from C++ binding)** — C++: `FTestDrawInstancedVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Plugins/Tests/RHITests/Source/RHITests/Private/RHIDrawTests.cpp:23)
- L20-27 _entry_ `void TestDrawInstancedMainPS( in nointerpolation uint InstanceID : Texcoord0, out float4 OutColor : SV_Target0 )` — stage: **pixel (from C++ binding)** — C++: `FTestDrawInstancedPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Tests/RHITests/Source/RHITests/Private/RHIDrawTests.cpp:39)

#### Global resources (textures / buffers / samplers) (1)

- L19 _resource_ `RWBuffer<uint> OutDrawnInstances;`

### `Plugins/Tests/RHITests/Shaders/Private/TestFillBuffer.usf` (Private)

- lines: 60; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`

#### Entry points (2)

- L16-32 _entry_ `[numthreads(THREADGROUP_SIZE_X, THREADGROUP_SIZE_Y, 1)] void FillBuffers(in uint3 ThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `FFillBufferCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Tests/RHITests/Source/RHITests/Private/RHIReadbackTests.cpp:39)
- L39-59 _entry_ `[numthreads(THREADGROUP_SIZE_X, THREADGROUP_SIZE_Y, 1)] void FillTextures(in uint3 ThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `FFillTexturesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Tests/RHITests/Source/RHITests/Private/RHIReadbackTests.cpp:64)

#### Structs / classes (1)

- L5-9 _struct_ **`FStructuredBufferElem`** `struct FStructuredBufferElem`
  - L7 _member_ `uint IntVal;`
  - L8 _member_ `float FloatVal;`

#### Global resources (textures / buffers / samplers) (7)

- L11 _resource_ `RWBuffer<uint> TypedBufferUAV;`
- L12 _resource_ `RWByteAddressBuffer ByteAddressBufferUAV;`
- L13 _resource_ `RWStructuredBuffer<FStructuredBufferElem> StructuredBufferUAV;`
- L34 _resource_ `RWTexture2D<uint> Texture2DUAV;`
- L35 _resource_ `RWTexture3D<uint> Texture3DUAV;`
- L36 _resource_ `RWTexture2DArray<uint> TextureArrayUAV;`
- L37 _resource_ `uint3 TextureSize;`

#### Global parameters (uniforms) (1)

- L14 _parameter_ `uint NumElements;`

### `Plugins/Tests/RHITests/Shaders/Private/TestFillTexture.usf` (Private)

- lines: 81; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`

#### Entry points (2)

- L8-27 _entry_ `void TestFillTextureVS( in uint VertexID : SV_VertexID, out float4 OutPosition : SV_Position )` — stage: **vertex (from C++ binding)** — C++: `FSimpleDrawVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Plugins/Tests/RHITests/Source/RHITests/Private/RHIClearTextureTests.cpp:457)
- L72-80 _entry_ `[numthreads(8, 8, 1)] void TestTextureToAtlasCS(uint3 Position : SV_DispatchThreadID)` — stage: **compute**

#### Global resources (textures / buffers / samplers) (4)

- L37 _resource_ `Texture2D <float4> SrcResource;` _[#if SRC_TYPE == 0]_
- L39 _resource_ `Texture2DArray<float4> SrcResource;` _[#if !(SRC_TYPE == 0) && SRC_TYPE == 1]_
- L41 _resource_ `Texture3D <float4> SrcResource;` _[#if !(SRC_TYPE == 0) && !(SRC_TYPE == 1)]_
- L44 _resource_ `RWTexture2D<float4> RWAtlas2D;`

#### Global parameters (uniforms) (2)

- L6 _parameter_ `float4 TestFillTextureConstant;`
- L45 _parameter_ `uint4 MipBiasMipNumsViewport;`

#### Functions (2)

- L29-34 _function_ `void TestFillTexturePS( out float4 OutColor : SV_Target0 )` — sv-semantics
- L48-70 _function_ `float4 TestTextureToAtlasCommon(uint2 PixelPositionInt)` — "unfolds" a given texture (2D/2D array/3D with mips) into a single 2D texture. X axis contains slices, Y axis contains mips

### `Plugins/Tests/RHITests/Shaders/Private/TestGraphicsUAV.usf` (Private)

- lines: 41; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`

#### Entry points (3)

- L9-20 _entry_ `void TestGraphicsUAVWriteMainVS( in float4 VertexPosition : ATTRIBUTE0, in uint VertexID : SV_VertexID, in uint InstanceID : SV_InstanceID, out uint OutInstanceID : Texcoord0, out float4 OutPosition : SV_Position )` — stage: **vertex (from C++ binding)** — C++: `FTestGraphicsUAVWriteVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Plugins/Tests/RHITests/Source/RHITests/Private/RHIGraphicsUAVTests.cpp:38)
- L22-31 _entry_ `void TestGraphicsUAVTrivialMainVS( in float4 VertexPosition : ATTRIBUTE0, in uint InstanceID : SV_InstanceID, out uint OutInstanceID : Texcoord0, out float4 OutPosition : SV_Position )` — stage: **vertex (from C++ binding)** — C++: `FTestGraphicsUAVTrivialVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Plugins/Tests/RHITests/Source/RHITests/Private/RHIGraphicsUAVTests.cpp:22)
- L33-40 _entry_ `void TestGraphicsUAVWriteMainPS( in nointerpolation uint InstanceID : Texcoord0, out float4 OutColor : SV_Target0 )` — stage: **pixel (from C++ binding)** — C++: `FTestGraphicsUAVWritePS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Tests/RHITests/Source/RHITests/Private/RHIGraphicsUAVTests.cpp:54)

#### Global resources (textures / buffers / samplers) (2)

- L6 _resource_ `RWStructuredBuffer<uint> RWPixelShaderOutput;` — NOTE: using a structured buffer here as workaround for UE-212251
- L7 _resource_ `RWStructuredBuffer<uint> RWVertexShaderOutput;`

### `Plugins/Tests/RHITests/Shaders/Private/TestRootConstants.usf` (Private)

- lines: 36; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `/Engine/Public/RootConstants.ush`

#### Entry points (3)

- L10-14 _entry_ `[numthreads(1, 1, 1)] void WriteRootConstants(uint3 GroupID : SV_GroupID)` — stage: **compute** — C++: `FRootConstantsTestCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Tests/RHITests/Source/RHITests/Private/RHIRootConstantsTests.cpp:74)
- L19-26 _entry_ `void RootConstantsMainVS( in uint VertexID : SV_VertexID, out float4 OutPos : SV_Position)` — stage: **vertex (from C++ binding)** — C++: `FRootConstantsTestVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Plugins/Tests/RHITests/Source/RHITests/Private/RHIRootConstantsTests.cpp:50) — Trivial fullscreen VS — emits a full-screen triangle from vertex ID.
- L31-35 _entry_ `void RootConstantsMainPS(out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FRootConstantsTestPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Tests/RHITests/Source/RHITests/Private/RHIRootConstantsTests.cpp:62)

#### Global resources (textures / buffers / samplers) (2)

- L8 _resource_ `RWStructuredBuffer<uint4> OutputUAV;`
- L29 _resource_ `RWStructuredBuffer<uint4> GraphicsOutputUAV;` — PS — writes the root constant values into a UAV so they can be read back.

### `Plugins/Tests/RHITests/Shaders/Private/TestShaderBundle.usf` (Private)

- lines: 101; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`

#### Entry points (5)

- L13-17 _entry_ `[numthreads(1, 1, 1)] void BundleComputeMain(uint3 ThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `FBundleTestCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Tests/RHITests/Source/RHITests/Private/RHIShaderBundleTests.cpp:81)
- L32-54 _entry_ `void BundleMeshMain( uint GroupThreadID : SV_GroupThreadID, MESH_SHADER_VERTEX_EXPORT(FMeshToPixel, 3), MESH_SHADER_TRIANGLE_EXPORT(1))` — stage: **mesh (from C++ binding)** — C++: `FBundleTestMS` SF_Mesh via IMPLEMENT_GLOBAL_SHADER (Plugins/Tests/RHITests/Source/RHITests/Private/RHIShaderBundleTests.cpp:113) _[#if SHADER_BUNDLE_TEST_MS]_
- L60-66 _entry_ `void BundlePixelMain( in FMeshToPixel Input, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FBundleTestPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Tests/RHITests/Source/RHITests/Private/RHIShaderBundleTests.cpp:145) _[#if SHADER_BUNDLE_TEST_PS]_
- L79-86 _entry_ `void BundleVertexMain( uint VertexID : SV_VertexID, out FVertexToPixel Output)` — stage: **vertex (from C++ binding)** — C++: `FBundleTestVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Plugins/Tests/RHITests/Source/RHITests/Private/RHIShaderBundleTests.cpp:174) _[#if SHADER_BUNDLE_TEST_VS]_
- L92-98 _entry_ `void BundleVSPSPixelMain( in float4 SvPosition : SV_Position, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FBundleTestVSPS_PS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Tests/RHITests/Source/RHITests/Private/RHIShaderBundleTests.cpp:208) _[#if SHADER_BUNDLE_TEST_VSPS_PS]_

#### Structs / classes (2)

- L23-27 _struct_ **`FMeshToPixel`** `struct FMeshToPixel`
  - L25 _member_ `float4 Position : SV_Position;`
  - L26 _member_ `uint SlotValue : SLOT_VALUE;`
- L74-77 _struct_ **`FVertexToPixel`** `struct FVertexToPixel` _[#if SHADER_BUNDLE_TEST_VS]_
  - L76 _member_ `float4 Position : SV_Position;` _[#if SHADER_BUNDLE_TEST_VS]_

#### Global resources (textures / buffers / samplers) (1)

- L11 _resource_ `RWBuffer<uint> OutBuffer;`

#### Top-level macro invocations (1)

- L31 _macro_call_ `MESH_SHADER_TRIANGLE_ATTRIBUTES(64)` _[#if SHADER_BUNDLE_TEST_MS]_
