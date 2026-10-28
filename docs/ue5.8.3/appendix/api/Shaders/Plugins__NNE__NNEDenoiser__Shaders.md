# Shaders / Plugins/NNE/NNEDenoiser/Shaders

- files: 7; lines: 409
- record kinds: cpp_binding=7, define=16, entry=7, function=4, groupshared=5, include=14, parameter=18, resource=19, static_var=11

### `Plugins/NNE/NNEDenoiser/Shaders/NNEDenoiserShadersAutoExposure.usf` (Other)

- lines: 40; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`, L4 `/Engine/Private/Common.ush`

#### Entry points (1)

- L11-40 _entry_ `[numthreads(1, 1, 1)] void AutoExposure(in const uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute**

#### Global resources (textures / buffers / samplers) (2)

- L8 _resource_ `Texture2D InputTexture;`
- L9 _resource_ `RWBuffer<float> OutputBuffer;`

#### Global parameters (uniforms) (2)

- L6 _parameter_ `int InputTextureWidth;`
- L7 _parameter_ `int InputTextureHeight;`

### `Plugins/NNE/NNEDenoiser/Shaders/NNEDenoiserShadersAutoExposureDownsample.usf` (Other)

- lines: 55; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`, L4 `/Engine/Private/Common.ush`

#### Entry points (1)

- L16-55 _entry_ `[numthreads(THREAD_GROUP_SIZE, THREAD_GROUP_SIZE, 1)] void Downsample(in const uint3 GroupThreadID : SV_GroupThreadID, in const uint3 GroupID : SV_GroupID, in const uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `FAutoExposureDownsampleCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/NNE/NNEDenoiser/Source/NNEDenoiserShaders/Private/NNEDenoiserShadersAutoExposureCS.cpp:45)

#### Global resources (textures / buffers / samplers) (2)

- L8 _resource_ `Texture2D InputTexture;`
- L12 _resource_ `RWBuffer<float> OutputBins;`

#### Global parameters (uniforms) (4)

- L6 _parameter_ `int InputTextureWidth;`
- L7 _parameter_ `int InputTextureHeight;`
- L10 _parameter_ `int NumBinsW;`
- L11 _parameter_ `int NumBinsH;`

#### groupshared (1)

- L14 _groupshared_ `groupshared float Sums[THREAD_GROUP_SIZE * THREAD_GROUP_SIZE];`

### `Plugins/NNE/NNEDenoiser/Shaders/NNEDenoiserShadersAutoExposureReduce.usf` (Other)

- lines: 50; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`, L4 `/Engine/Private/Common.ush`

#### Entry points (1)

- L15-50 _entry_ `[numthreads(THREAD_GROUP_SIZE, 1, 1)] void Reduce(in const uint3 GroupThreadID : SV_GroupThreadID, in const uint3 GroupID : SV_GroupID, in const uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `FAutoExposureReduceCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/NNE/NNEDenoiser/Source/NNEDenoiserShaders/Private/NNEDenoiserShadersAutoExposureCS.cpp:46)

#### Global resources (textures / buffers / samplers) (3)

- L7 _resource_ `Buffer<float> InputBins;`
- L8 _resource_ `RWBuffer<float> OutputSums;`
- L9 _resource_ `RWBuffer<int> OutputCounts;`

#### Global parameters (uniforms) (2)

- L6 _parameter_ `int InputSize;`
- L10 _parameter_ `int NumThreads;`

#### groupshared (2)

- L12 _groupshared_ `groupshared float Sums[THREAD_GROUP_SIZE];`
- L13 _groupshared_ `groupshared int Counts[THREAD_GROUP_SIZE];`

### `Plugins/NNE/NNEDenoiser/Shaders/NNEDenoiserShadersAutoExposureReduceFinal.usf` (Other)

- lines: 46; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`, L4 `/Engine/Private/Common.ush`

#### Entry points (1)

- L14-46 _entry_ `[numthreads(THREAD_GROUP_SIZE, 1, 1)] void ReduceFinal(in const uint3 GroupThreadID : SV_GroupThreadID)` — stage: **compute** — C++: `FAutoExposureReduceFinalCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/NNE/NNEDenoiser/Source/NNEDenoiserShaders/Private/NNEDenoiserShadersAutoExposureCS.cpp:47)

#### Global resources (textures / buffers / samplers) (3)

- L7 _resource_ `Buffer<float> InputSums;`
- L8 _resource_ `Buffer<int> InputCounts;`
- L9 _resource_ `RWBuffer<float> OutputBuffer;` — 0: Result, 1: 1.0 / Result

#### Global parameters (uniforms) (1)

- L6 _parameter_ `int InputSize;`

#### groupshared (2)

- L11 _groupshared_ `groupshared float Sums[THREAD_GROUP_SIZE];`
- L12 _groupshared_ `groupshared int Counts[THREAD_GROUP_SIZE];`

### `Plugins/NNE/NNEDenoiser/Shaders/NNEDenoiserShadersDefaultIOProcess.usf` (Other)

- lines: 40; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`, L4 `/Engine/Private/Common.ush`

#### Entry points (1)

- L29-40 _entry_ `[numthreads(THREAD_GROUP_SIZE, THREAD_GROUP_SIZE, 1)] void IOProcess(in const uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `FDefaultIOProcessCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/NNE/NNEDenoiser/Source/NNEDenoiserShaders/Private/NNEDenoiserShadersDefaultIOProcessCS.cpp:20)

#### Global resources (textures / buffers / samplers) (2)

- L8 _resource_ `Texture2D InputTexture;`
- L9 _resource_ `RWTexture2D<float4> OutputTexture;`

#### Global parameters (uniforms) (2)

- L6 _parameter_ `int Width;`
- L7 _parameter_ `int Height;`

#### Functions (1)

- L11-26 _function_ `float3 GetProcessedValue(float3 Value)`

### `Plugins/NNE/NNEDenoiser/Shaders/NNEDenoiserShadersMappedCopy.usf` (Other)

- lines: 102; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`, L4 `/Engine/Private/Common.ush`

#### Macros (#define, 16)

- L6 `#define FLOAT16 half`
- L7 `#define FLOAT16_4 half4`
- L9 `#define FLOAT32 float`
- L10 `#define FLOAT32_4 float4`
- L13 `#define INPUT_SCALAR_DATA_TYPE FLOAT16` _[#if INPUT_DATA_TYPE_INDEX == 4]_
- L14 `#define INPUT_VECTOR_DATA_TYPE FLOAT16_4` _[#if INPUT_DATA_TYPE_INDEX == 4]_
- L16 `#define INPUT_SCALAR_DATA_TYPE FLOAT32` _[#if !(INPUT_DATA_TYPE_INDEX == 4)]_
- L17 `#define INPUT_VECTOR_DATA_TYPE FLOAT32_4` _[#if !(INPUT_DATA_TYPE_INDEX == 4)]_
- L21 `#define OUTPUT_SCALAR_DATA_TYPE FLOAT16` _[#if OUTPUT_DATA_TYPE_INDEX == 4]_
- L22 `#define OUTPUT_VECTOR_DATA_TYPE FLOAT16_4` _[#if OUTPUT_DATA_TYPE_INDEX == 4]_
- L24 `#define OUTPUT_SCALAR_DATA_TYPE FLOAT32` _[#if !(OUTPUT_DATA_TYPE_INDEX == 4)]_
- L25 `#define OUTPUT_VECTOR_DATA_TYPE FLOAT32_4` _[#if !(OUTPUT_DATA_TYPE_INDEX == 4)]_
- L30 `#define CONVERT(X) X` _[#if INPUT_DATA_TYPE_INDEX == 4 && OUTPUT_DATA_TYPE_INDEX == 4]_
- L32 `#define CONVERT(X) FLOAT32(X)` _[#if INPUT_DATA_TYPE_INDEX == 4 && !(OUTPUT_DATA_TYPE_INDEX == 4)]_
- L36 `#define CONVERT(X) FLOAT16(X)` _[#if !(INPUT_DATA_TYPE_INDEX == 4) && OUTPUT_DATA_TYPE_INDEX == 4]_
- L38 `#define CONVERT(X) X` _[#if !(INPUT_DATA_TYPE_INDEX == 4) && !(OUTPUT_DATA_TYPE_INDEX == 4)]_

#### Entry points (1)

- L58-102 _entry_ `[numthreads(THREAD_GROUP_SIZE, THREAD_GROUP_SIZE, 1)] void MappedCopy(in const uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `FTextureBufferMappedCopyCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/NNE/NNEDenoiser/Source/NNEDenoiserShaders/Private/NNEDenoiserShadersMappedCopyCS.cpp:62) — C++: `FBufferTextureMappedCopyCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/NNE/NNEDenoiser/Source/NNEDenoiserShaders/Private/NNEDenoiserShadersMappedCopyCS.cpp:63)

#### Global resources (textures / buffers / samplers) (4)

- L47 _resource_ `Texture2D<INPUT_VECTOR_DATA_TYPE> InputTexture;` _[#if INTRINSIC_INPUT_TYPE == 0]_
- L49 _resource_ `Buffer<INPUT_SCALAR_DATA_TYPE> InputBuffer;` _[#if !(INTRINSIC_INPUT_TYPE == 0)]_
- L53 _resource_ `RWTexture2D<OUTPUT_VECTOR_DATA_TYPE> OutputTexture;` _[#if INTRINSIC_OUTPUT_TYPE == 0]_
- L55 _resource_ `RWBuffer<OUTPUT_SCALAR_DATA_TYPE> OutputBuffer;` _[#if !(INTRINSIC_OUTPUT_TYPE == 0)]_

#### Global parameters (uniforms) (3)

- L42 _parameter_ `int Width;`
- L43 _parameter_ `int Height;`
- L44 _parameter_ `int4 OutputChannel_InputChannel_Unused_Unused[MAX_NUM_MAPPED_CHANNELS];`

### `Plugins/NNE/NNEDenoiser/Shaders/NNEDenoiserShadersTransferFunctionOidn.usf` (Other)

- lines: 76; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`, L4 `/Engine/Private/Common.ush`

#### Entry points (1)

- L65-76 _entry_ `[numthreads(THREAD_GROUP_SIZE, THREAD_GROUP_SIZE, 1)] void PreOrPostprocess(in const uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `FTransferFunctionOidnCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/NNE/NNEDenoiser/Source/NNEDenoiserShaders/Private/NNEDenoiserShadersTransferFunctionOidnCS.cpp:20)

#### Global resources (textures / buffers / samplers) (3)

- L8 _resource_ `Texture2D InputTexture;`
- L9 _resource_ `Buffer<float> InputScaleBuffer;`
- L12 _resource_ `RWTexture2D<float4> OutputTexture;`

#### Global parameters (uniforms) (4)

- L6 _parameter_ `int Width;`
- L7 _parameter_ `int Height;`
- L10 _parameter_ `float NormScale;`
- L11 _parameter_ `float InvNormScale;`

#### static variables (11)

- L20 _static_var_ `static float a = 1.41283765e+03;` — from https://github.com/OpenImageDenoise/oidn/blob/master/core/color.h struct FPU {
- L21 _static_var_ `static float b = 1.64593172e+00;`
- L22 _static_var_ `static float c = 4.31384981e-01;`
- L23 _static_var_ `static float d = -2.94139609e-03;`
- L24 _static_var_ `static float e = 1.92653254e-01;`
- L25 _static_var_ `static float f = 6.26026094e-03;`
- L26 _static_var_ `static float g = 9.98620152e-01;`
- L27 _static_var_ `static float y0 = 1.57945760e-06;`
- L28 _static_var_ `static float y1 = 3.22087631e-02;`
- L29 _static_var_ `static float x0 = 2.23151711e-03;`
- L30 _static_var_ `static float x1 = 3.70974749e-01;`

#### Functions (3)

- L32-37 _function_ `static float Forward(float y)`
- L39-44 _function_ `static float Inverse(float x)`
- L46-59 _function_ `float3 GetProcessedValue(float3 Value)`
