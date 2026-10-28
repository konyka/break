# Shaders / Plugins/Runtime/AR/AppleAR/AppleARKit/Shaders/Private

- files: 1; lines: 72
- record kinds: cpp_binding=1, entry=1, function=1, include=1, parameter=4, resource=3

### `Plugins/Runtime/AR/AppleAR/AppleARKit/Shaders/Private/ColorSpaceConversion.usf` (Private)

- lines: 72; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`

#### Entry points (1)

- L47-71 _entry_ `[numthreads(THREADGROUPSIZE, THREADGROUPSIZE, 1)] void YCbCrToLinearRGB(uint3 ThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FComputeShaderYCbCrToRGB` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/AR/AppleAR/AppleARKit/Source/AppleARKit/Private/AppleARKitTextures.cpp:773)

#### Global resources (textures / buffers / samplers) (3)

- L5 _resource_ `RWTexture2D<float4> OutputTexture;`
- L8 _resource_ `Texture2D InputTextureY;`
- L11 _resource_ `Texture2D InputTextureCbCr;`

#### Global parameters (uniforms) (4)

- L6 _parameter_ `float2 OutputTextureSize;`
- L9 _parameter_ `float2 InputTextureYSize;`
- L12 _parameter_ `float2 InputTextureCbCrSize;`
- L21 _parameter_ `int DeviceOrientation;` — The device's current orientation 0 - Portrait 1 - PortraitUpsideDown 2 - LandscapeLeft 3 - LandscapeRight

#### Functions (1)

- L23-45 _function_ `float2 GetInputUV(float2 OutputUV)`
