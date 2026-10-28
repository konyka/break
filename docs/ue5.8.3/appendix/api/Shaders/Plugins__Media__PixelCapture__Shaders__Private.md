# Shaders / Plugins/Media/PixelCapture/Shaders/Private

- files: 1; lines: 42
- record kinds: cpp_binding=1, entry=1, include=2, parameter=1, resource=5, static_const=1

### `Plugins/Media/PixelCapture/Shaders/Private/RGBToYUV.usf` (Private)

- lines: 42; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`, L4 `/Engine/Private/ColorUtils.ush`

#### Entry points (1)

- L18-41 _entry_ `[numthreads(THREADGROUPSIZE_X, THREADGROUPSIZE_Y, THREADGROUPSIZE_Z)] void ExtractI420(uint3 Gid : SV_GroupID, uint3 DTid : SV_DispatchThreadID, uint3 GTid : SV_GroupThreadID, uint GI : SV_GroupIndex)` — stage: **compute** — C++: `FExtractI420CS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Media/PixelCapture/Source/PixelCaptureShaders/Private/RGBToYUVShader.cpp:42)

#### Global resources (textures / buffers / samplers) (5)

- L6 _resource_ `Texture2D SourceTexture;`
- L7 _resource_ `SamplerState SourceSampler;`
- L9 _resource_ `RWTexture2D<float> OutputY;`
- L10 _resource_ `RWTexture2D<float> OutputU;`
- L11 _resource_ `RWTexture2D<float> OutputV;`

#### Global parameters (uniforms) (1)

- L8 _parameter_ `float2 SourceDimensions;`

#### static const (1)

- L13-16 _static_const_ `static const float4x4 ColorTransform = float4x4( 0.257, 0.504, 0.098, 0.063, -0.148, -0.291, 0.439, 0.500, 0.439, -0.368, -0.071, 0.500, 0.000, 0.000, 0.000, 1.000);`
