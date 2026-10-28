# Shaders / Shaders/Private/Bloom

- files: 11; lines: 842
- record kinds: cpp_binding=10, define=8, entry=10, groupshared=9, include=11, member=5, parameter=21, resource=32, struct=1

### `Shaders/Private/Bloom/BloomClampKernel.usf` (Private)

- lines: 42; parse: all-branches
- includes: L3 `BloomCommon.ush`

#### Macros (#define, 1)

- L8 `#define TILE_SIZE 8`

#### Entry points (1)

- L22-41 _entry_ `[numthreads(TILE_SIZE, TILE_SIZE, 1)] void MainCS( uint2 GroupId : SV_GroupID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FBloomClampKernelCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/PostProcessFFTBloom.cpp:220)

#### Global resources (textures / buffers / samplers) (3)

- L15 _resource_ `Texture2D KernelSpatialTexture;`
- L16 _resource_ `StructuredBuffer<FBloomKernelInfo> KernelConstantsBuffer;`
- L17 _resource_ `RWTexture2D<float4> ClampedKernelSpatialOutput;`

#### Global parameters (uniforms) (1)

- L13 _parameter_ `uint bProcessAlpha;`

### `Shaders/Private/Bloom/BloomCommon.ush` (Private)

- lines: 31; parse: all-branches
- includes: L3 `../Common.ush`
- L9 #pragma `warning(error: 3206)`

#### Structs / classes (1)

- L14-30 _struct_ **`FBloomKernelInfo`** `struct FBloomKernelInfo`
  - L17 _member_ `float4 CenterEnergy;` — Total energy at the center of the kernel.
  - L20 _member_ `float4 ScatterDispersionEnergy;` — Total energy of the bloom.
  - L23 _member_ `float4 MaxScatterDispersionEnergy;` — Highest energy per pixel that should clamp with to remove the kernel center
  - L26 _member_ `uint2 CenterPixelCoord;` — Pixel coordinate of the center of the kernel
  - L29 _member_ `uint2 _Padding;` — Some padding to make vulkan happy

### `Shaders/Private/Bloom/BloomDownsampleKernel.usf` (Private)

- lines: 41; parse: all-branches
- includes: L3 `BloomCommon.ush`

#### Macros (#define, 1)

- L8 `#define TILE_SIZE 8`

#### Entry points (1)

- L22-40 _entry_ `[numthreads(TILE_SIZE, TILE_SIZE, 1)] void MainCS( uint2 GroupId : SV_GroupID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FBloomDownsampleKernelCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/PostProcessFFTBloom.cpp:221)

#### Global resources (textures / buffers / samplers) (3)

- L14 _resource_ `Texture2D KernelSpatialTexture;`
- L15 _resource_ `SamplerState KernelSpatialSampler;`
- L17 _resource_ `RWTexture2D<float4> DownsampleKernelSpatialOutput;`

#### Global parameters (uniforms) (1)

- L13 _parameter_ `uint2 KernelSpatialTextureSize;`

### `Shaders/Private/Bloom/BloomFinalizeApplyConstants.usf` (Private)

- lines: 43; parse: all-branches
- includes: L3 `BloomCommon.ush`

#### Entry points (1)

- L17-42 _entry_ `[numthreads(1, 1, 1)] void MainCS( uint2 GroupId : SV_GroupID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FBloomFinalizeApplyConstantsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/PostProcessFFTBloom.cpp:223)

#### Global resources (textures / buffers / samplers) (3)

- L10 _resource_ `StructuredBuffer<FBloomKernelInfo> KernelConstantsBuffer;`
- L11 _resource_ `RWStructuredBuffer<float4> SceneColorApplyOutput;`
- L12 _resource_ `RWStructuredBuffer<float4> FFTMulitplyOutput;`

#### Global parameters (uniforms) (1)

- L8 _parameter_ `float ScatterDispersionIntensity;`

### `Shaders/Private/Bloom/BloomFindKernelCenter.usf` (Private)

- lines: 136; parse: all-branches
- includes: L3 `BloomCommon.ush`

#### Macros (#define, 1)

- L8 `#define TILE_SIZE 8`

#### Entry points (1)

- L36-135 _entry_ `[numthreads(TILE_SIZE, TILE_SIZE, 1)] void MainCS( uint2 GroupId : SV_GroupID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FBloomFindKernelCenterCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/PostProcessFFTBloom.cpp:214)

#### Global resources (textures / buffers / samplers) (1)

- L20 _resource_ `Texture2D KernelSpatialTexture;`

#### Global parameters (uniforms) (2)

- L19 _parameter_ `uint2 KernelSpatialTextureSize;` — uint uint float uint
- L22 _parameter_ `RWCoherentStructuredBuffer(uint) KernelCenterCoordOutput;`

#### groupshared (5)

- L27 _groupshared_ `groupshared uint MaxLuminance;`
- L28 _groupshared_ `groupshared uint2 MaxLuminancePixelPos;`
- L29 _groupshared_ `groupshared uint CurrentMaxLuminance;`
- L30 _groupshared_ `groupshared uint bDone;`
- L31 _groupshared_ `groupshared uint PrevLock;`

### `Shaders/Private/Bloom/BloomPackKernelConstants.usf` (Private)

- lines: 28; parse: all-branches
- includes: L3 `BloomCommon.ush`

#### Entry points (1)

- L18-27 _entry_ `[numthreads(1, 1, 1)] void MainCS( uint2 GroupId : SV_GroupID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FBloomPackKernelConstantsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/PostProcessFFTBloom.cpp:219)

#### Global resources (textures / buffers / samplers) (5)

- L8 _resource_ `StructuredBuffer<uint> KernelCenterCoordBuffer;`
- L9 _resource_ `StructuredBuffer<float4> KernelCenterEnergyBuffer;`
- L10 _resource_ `StructuredBuffer<float4> MaxScatterDispersionBuffer;`
- L11 _resource_ `Texture2D ScatterDispersionTexture;`
- L13 _resource_ `RWStructuredBuffer<FBloomKernelInfo> KernelConstantsOutput;`

### `Shaders/Private/Bloom/BloomReduceKernelSurvey.usf` (Private)

- lines: 95; parse: all-branches
- includes: L3 `BloomCommon.ush`

#### Macros (#define, 1)

- L8 `#define TILE_SIZE 64`

#### Entry points (1)

- L25-94 _entry_ `[numthreads(TILE_SIZE, 1, 1)] void MainCS(uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FBloomReduceKernelSurveyCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/PostProcessFFTBloom.cpp:217)

#### Global resources (textures / buffers / samplers) (1)

- L15 _resource_ `RWStructuredBuffer<float4> SurveyOutput;`

#### Global parameters (uniforms) (2)

- L13 _parameter_ `uint SurveyReduceOp;`
- L14 _parameter_ `uint SurveyGroupCount;`

#### groupshared (1)

- L20 _groupshared_ `groupshared float4 SharedColor[TILE_SIZE];`

### `Shaders/Private/Bloom/BloomResizeKernel.usf` (Private)

- lines: 161; parse: all-branches
- includes: L3 `BloomCommon.ush`

#### Macros (#define, 1)

- L8 `#define TILE_SIZE 8`

#### Entry points (1)

- L29-160 _entry_ `[numthreads(TILE_SIZE, TILE_SIZE, 1)] void MainCS( uint2 GroupId : SV_GroupID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FBloomResizeKernelCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/PostProcessFFTBloom.cpp:222)

#### Global resources (textures / buffers / samplers) (4)

- L19 _resource_ `StructuredBuffer<FBloomKernelInfo> KernelConstantsBuffer;`
- L21 _resource_ `Texture2D SrcTexture;`
- L22 _resource_ `SamplerState SrcSampler;`
- L24 _resource_ `RWTexture2D<float4> DstTexture;`

#### Global parameters (uniforms) (5)

- L13 _parameter_ `uint2 DstExtent;`
- L14 _parameter_ `uint2 ImageExtent;`
- L15 _parameter_ `float2 KernelSpatialTextureInvSize;`
- L16 _parameter_ `uint2 DstBufferExtent;`
- L17 _parameter_ `float KernelSupportScale;`

### `Shaders/Private/Bloom/BloomSumScatterDispersionEnergy.usf` (Private)

- lines: 81; parse: all-branches
- includes: L3 `BloomCommon.ush`

#### Macros (#define, 1)

- L8 `#define TILE_SIZE 8`

#### Entry points (1)

- L28-80 _entry_ `[numthreads(TILE_SIZE, TILE_SIZE, 1)] void MainCS( uint2 GroupId : SV_GroupID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FBloomSumScatterDispersionEnergyCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/PostProcessFFTBloom.cpp:218)

#### Global resources (textures / buffers / samplers) (3)

- L15 _resource_ `Texture2D ScatterDispersionTexture;`
- L16 _resource_ `StructuredBuffer<float4> MaxScatterDispersionBuffer;`
- L18 _resource_ `RWTexture2D<float4> ScatterDispersionOutput;`

#### Global parameters (uniforms) (2)

- L13 _parameter_ `uint PassId;`
- L14 _parameter_ `uint2 ScatterDispersionTextureSize;`

#### groupshared (1)

- L23 _groupshared_ `groupshared float4 SharedColor[TILE_SIZE * TILE_SIZE];`

### `Shaders/Private/Bloom/BloomSurveyKernelCenterEnergy.usf` (Private)

- lines: 89; parse: all-branches
- includes: L3 `BloomCommon.ush`

#### Macros (#define, 1)

- L8 `#define TILE_SIZE 8`

#### Entry points (1)

- L33-88 _entry_ `[numthreads(TILE_SIZE, TILE_SIZE, 1)] void MainCS( uint2 GroupId : SV_GroupID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FBloomSurveyKernelCenterEnergyCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/PostProcessFFTBloom.cpp:216)

#### Global resources (textures / buffers / samplers) (5)

- L18 _resource_ `Texture2D KernelSpatialTexture;`
- L19 _resource_ `StructuredBuffer<uint> KernelCenterCoordBuffer;`
- L20 _resource_ `StructuredBuffer<float4> MaxScatterDispersionBuffer;`
- L22 _resource_ `RWStructuredBuffer<float4> SurveyOutput;`
- L23 _resource_ `RWTexture2D<float4> DebugOutput;`

#### Global parameters (uniforms) (3)

- L13 _parameter_ `float ViewTexelRadiusInKernelTexels;`
- L14 _parameter_ `uint SurveyGroupGridSize;`
- L17 _parameter_ `uint2 KernelSpatialTextureSize;`

#### groupshared (1)

- L28 _groupshared_ `groupshared float4 SharedColor[TILE_SIZE * TILE_SIZE];`

### `Shaders/Private/Bloom/BloomSurveyMaxScatterDispersion.usf` (Private)

- lines: 95; parse: all-branches
- includes: L3 `BloomCommon.ush`

#### Macros (#define, 1)

- L8 `#define TILE_SIZE 8`

#### Entry points (1)

- L32-94 _entry_ `[numthreads(TILE_SIZE, TILE_SIZE, 1)] void MainCS( uint2 GroupId : SV_GroupID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FBloomSurveyMaxScatterDispersionCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/PostProcessFFTBloom.cpp:215)

#### Global resources (textures / buffers / samplers) (4)

- L19 _resource_ `Texture2D KernelSpatialTexture;`
- L20 _resource_ `StructuredBuffer<uint> KernelCenterCoordBuffer;`
- L22 _resource_ `RWStructuredBuffer<float4> SurveyOutput;`
- L23 _resource_ `RWTexture2D<float4> DebugOutput;`

#### Global parameters (uniforms) (4)

- L13 _parameter_ `float ViewTexelRadiusInKernelTexels;`
- L14 _parameter_ `uint SurveyGroupGridSize;`
- L15 _parameter_ `uint SurveyType;`
- L18 _parameter_ `uint2 KernelSpatialTextureSize;`

#### groupshared (1)

- L27 _groupshared_ `groupshared uint SharedMaxNeighborColor[4];`
