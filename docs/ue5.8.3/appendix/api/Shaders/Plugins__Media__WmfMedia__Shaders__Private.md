# Shaders / Plugins/Media/WmfMedia/Shaders/Private

- files: 1; lines: 118
- record kinds: cpp_binding=6, entry=6, include=3, parameter=2, resource=5, static_const=3

### `Plugins/Media/WmfMedia/Shaders/Private/MediaHardwareVideoDecoding.usf` (Private)

- lines: 118; parse: all-branches
- includes: L6 `/Engine/Private/Common.ush`, L7 `/Engine/Private/GammaCorrectionCommon.ush`, L8 `/Engine/Private/ColorUtils.ush`

#### Entry points (6)

- L40-49 _entry_ `void MainVS(in uint GlobalVertexId : SV_VertexID , out float2 TexCoord : TEXCOORD0 , out float4 OutPosition : SV_POSITION)` — stage: **vertex (from C++ binding)** — C++: `FHardwareVideoDecodingVS` SF_Vertex via IMPLEMENT_SHADER_TYPE (Plugins/Media/WmfMedia/Source/WmfMedia/Private/Wmf/WmfMediaHardwareVideoDecodingShaders.cpp:5)
- L51-61 _entry_ `void NV12ConvertPS(in noperspective float2 InUV : TEXCOORD0 , in float4 SvPosition : SV_POSITION , out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FHardwareVideoDecodingPS` SF_Pixel via IMPLEMENT_SHADER_TYPE (Plugins/Media/WmfMedia/Source/WmfMedia/Private/Wmf/WmfMediaHardwareVideoDecodingShaders.cpp:6)
- L64-69 _entry_ `void PassThroughPS(in noperspective float2 InUV : TEXCOORD0 , in float4 SvPosition : SV_POSITION , out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FHardwareVideoDecodingPassThroughPS` SF_Pixel via IMPLEMENT_SHADER_TYPE (Plugins/Media/WmfMedia/Source/WmfMedia/Private/Wmf/WmfMediaHardwareVideoDecodingShaders.cpp:7)
- L71-79 _entry_ `void Y416ConvertPS(in noperspective float2 InUV : TEXCOORD0 , in float4 SvPosition : SV_POSITION , out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FHardwareVideoDecodingY416PS` SF_Pixel via IMPLEMENT_SHADER_TYPE (Plugins/Media/WmfMedia/Source/WmfMedia/Private/Wmf/WmfMediaHardwareVideoDecodingShaders.cpp:8)
- L81-97 _entry_ `void YCoCgConvertPS(in noperspective float2 InUV : TEXCOORD0 , in float4 SvPosition : SV_POSITION , out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FHardwareVideoDecodingYCoCgPS` SF_Pixel via IMPLEMENT_SHADER_TYPE (Plugins/Media/WmfMedia/Source/WmfMedia/Private/Wmf/WmfMediaHardwareVideoDecodingShaders.cpp:9)
- L99-116 _entry_ `void YCoCgAlphaConvertPS(in noperspective float2 InUV : TEXCOORD0 , in float4 SvPosition : SV_POSITION , out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FHardwareVideoDecodingYCoCgAlphaPS` SF_Pixel via IMPLEMENT_SHADER_TYPE (Plugins/Media/WmfMedia/Source/WmfMedia/Private/Wmf/WmfMediaHardwareVideoDecodingShaders.cpp:10)

#### Global resources (textures / buffers / samplers) (5)

- L32 _resource_ `Texture2D TextureY;`
- L33 _resource_ `Texture2D TextureUV;`
- L34 _resource_ `SamplerState PointClampedSamplerY;`
- L35 _resource_ `SamplerState BilinearClampedSamplerUV;`
- L36 _resource_ `SamplerState BilinearClampedSamplerUVAlpha;`

#### Global parameters (uniforms) (2)

- L37 _parameter_ `float4x4 ColorTransform;`
- L38 _parameter_ `uint SrgbToLinear;`

#### static const (3)

- L10-18 _static_const_ `static const float2 kQuadPos[6] = { float2(-1.0, 1.0), float2( 1.0, 1.0), float2( 1.0,-1.0), float2(-1.0,-1.0), float2( 1.0,-1.0), float2(-1.0, 1.0), };`
- L20-28 _static_const_ `static const float2 kQuadUVs[6] = { float2(0.0, 0.0), float2(1.0, 0.0), float2(1.0, 1.0), float2(0.0, 1.0), float2(1.0, 1.0), float2(0.0, 0.0), };`
- L30 _static_const_ `static const float4 kYCoCgOffsets = float4(-0.50196078431373, -0.50196078431373, 0, 0);`
