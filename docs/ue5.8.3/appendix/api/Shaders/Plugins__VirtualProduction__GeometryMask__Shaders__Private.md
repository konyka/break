# Shaders / Plugins/VirtualProduction/GeometryMask/Shaders/Private

- files: 4; lines: 300
- record kinds: cpp_binding=4, define=4, entry=4, function=1, include=5, parameter=15, resource=12

### `Plugins/VirtualProduction/GeometryMask/Shaders/Private/GeometryMaskBlurCS.usf` (Private)

- lines: 81; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `/Engine/Public/Platform.ush`

#### Macros (#define, 3)

- L6 `#define TILE_SIZE 8`
- L7 `#define MAX_SAMPLES 127`
- L8 `#define HALF_MAX_SAMPLES MAX_SAMPLES / 2`

#### Entry points (1)

- L34-80 _entry_ `[numthreads(TILE_SIZE, TILE_SIZE, 1)] void MainCS( uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID, uint3 GroupId : SV_GroupID)` — stage: **compute** — C++: `FGeometryMaskBlurCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/VirtualProduction/GeometryMask/Source/GeometryMask/Private/Shaders/GeometryMaskPostProcess_Blur.cpp:41) — Loosely based on Engine/Shaders/Private/SlatePostProcessPixelShader.usf

#### Global resources (textures / buffers / samplers) (3)

- L15 _resource_ `Texture2D InputTexture;`
- L16 _resource_ `SamplerState InputSampler;`
- L17 _resource_ `RWTexture2D<float4> OutputTexture;`

#### Global parameters (uniforms) (4)

- L10 _parameter_ `int SampleCount;`
- L11 _parameter_ `float4 WeightsAndOffsets[HALF_MAX_SAMPLES];`
- L12 _parameter_ `float4 BufferSizeAndDirection;`
- L14 _parameter_ `uint2 InputDimensions;`

#### Functions (1)

- L19-31 _function_ `float4 GetSample(float Weight, float Offset, float2 UV)`

### `Plugins/VirtualProduction/GeometryMask/Shaders/Private/GeometryMaskJFInitCS.usf` (Private)

- lines: 85; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`

#### Entry points (1)

- L12-84 _entry_ `[numthreads(TILE_SIZE, TILE_SIZE, 1)] void MainCS( uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID, uint3 GroupId : SV_GroupID)` — stage: **compute** — C++: `FGeometryMaskJFInitCS1` SF_Compute via IMPLEMENT_SHADER_TYPE (Plugins/VirtualProduction/GeometryMask/Source/GeometryMask/Private/Shaders/GeometryMaskPostProcess_DistanceField.cpp:74)

#### Global resources (textures / buffers / samplers) (3)

- L8 _resource_ `Texture2D InputTexture;`
- L9 _resource_ `SamplerState InputSampler;`
- L10 _resource_ `RWBuffer<float4> OutputBuffer;`

#### Global parameters (uniforms) (3)

- L5 _parameter_ `uint2 InputDimensions;`
- L6 _parameter_ `float2 OneOverInputDimensions;`
- L7 _parameter_ `float2 UVRatioAdjustment;`

### `Plugins/VirtualProduction/GeometryMask/Shaders/Private/GeometryMaskJFStepCS.usf` (Private)

- lines: 76; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`

#### Entry points (1)

- L12-75 _entry_ `[numthreads(TILE_SIZE, TILE_SIZE, 1)] void MainCS( uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID, uint3 GroupId : SV_GroupID)` — stage: **compute** — C++: `FGeometryMaskJFStepCS1` SF_Compute via IMPLEMENT_SHADER_TYPE (Plugins/VirtualProduction/GeometryMask/Source/GeometryMask/Private/Shaders/GeometryMaskPostProcess_DistanceField.cpp:115)

#### Global resources (textures / buffers / samplers) (2)

- L9 _resource_ `Buffer<float4> InputBuffer;`
- L10 _resource_ `RWBuffer<float4> OutputBuffer;`

#### Global parameters (uniforms) (4)

- L5 _parameter_ `uint2 InputDimensions;`
- L6 _parameter_ `float2 OneOverInputDimensions;`
- L7 _parameter_ `float2 UVRatioAdjustment;`
- L8 _parameter_ `uint StepSize;`

### `Plugins/VirtualProduction/GeometryMask/Shaders/Private/GeometryMaskJFtoDFCS.usf` (Private)

- lines: 58; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`

#### Macros (#define, 1)

- L5 `#define DEBUG_SOBEL 0`

#### Entry points (1)

- L16-57 _entry_ `[numthreads(TILE_SIZE, TILE_SIZE, 1)] void MainCS( uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID, uint3 GroupId : SV_GroupID)` — stage: **compute** — C++: `FGeometryMaskJFtoDFCS1` SF_Compute via IMPLEMENT_SHADER_TYPE (Plugins/VirtualProduction/GeometryMask/Source/GeometryMask/Private/Shaders/GeometryMaskPostProcess_DistanceField.cpp:158)

#### Global resources (textures / buffers / samplers) (4)

- L11 _resource_ `Texture2D OriginalInputTexture;`
- L12 _resource_ `SamplerState OriginalInputSampler;`
- L13 _resource_ `Buffer<float4> InputBuffer;`
- L14 _resource_ `RWTexture2D<float4> OutputTexture;`

#### Global parameters (uniforms) (4)

- L7 _parameter_ `uint2 InputDimensions;`
- L8 _parameter_ `float2 OneOverInputDimensions;`
- L9 _parameter_ `float2 UVRatioAdjustment;`
- L10 _parameter_ `float StepDistanceMultiplier;` — To normalize
