# Shaders / Plugins/Media/NDIMedia/Shaders/Private

- files: 1; lines: 131
- record kinds: cpp_binding=3, define=20, entry=3, function=2, include=4

### `Plugins/Media/NDIMedia/Shaders/Private/NDIMediaShaders.usf` (Private)

- lines: 131; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`, L4 `/Engine/Generated/GeneratedUniformBuffers.ush`, L5 `/Engine/Private/GammaCorrectionCommon.ush`, L6 `/Engine/Private/TonemapCommon.ush`

#### Macros (#define, 20)

- L11 `#define UE_Color_EEncoding_Linear 1u`
- L12 `#define UE_Color_EEncoding_sRGB 2u`
- L13 `#define UE_Color_EEncoding_ST2084 3u`
- L14 `#define UE_Color_EEncoding_Gamma22 4u`
- L15 `#define UE_Color_EEncoding_BT1886 5u`
- L16 `#define UE_Color_EEncoding_Gamma26 6u`
- L17 `#define UE_Color_EEncoding_Cineon 7u`
- L18 `#define UE_Color_EEncoding_REDLog 8u`
- L19 `#define UE_Color_EEncoding_REDLog3G10 9u`
- L20 `#define UE_Color_EEncoding_SLog1 10u`
- L21 `#define UE_Color_EEncoding_SLog2 11u`
- L22 `#define UE_Color_EEncoding_SLog3 12u`
- L23 `#define UE_Color_EEncoding_AlexaV3LogC 13u`
- L24 `#define UE_Color_EEncoding_CanonLog 14u`
- L25 `#define UE_Color_EEncoding_ProTune 15u`
- L26 `#define UE_Color_EEncoding_VLog 16u`
- L27 `#define UE_Color_EEncoding_HLG 17u`
- L29 `#define ToneMapMethod_None 0u`
- L30 `#define ToneMapMethod_Hable 1u`
- L31 `#define ToneMapMethod_SimpleReinhard 2u`

#### Entry points (3)

- L81-97 _entry_ `void NDIMediaUYVYAConvertPS( float4 InPosition : SV_POSITION, float2 InUV : TEXCOORD0, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FNDIMediaShaderUYVAtoBGRAPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Media/NDIMedia/Source/NDIMediaRendering/Private/NDIMediaShaders.cpp:24) — Conversion of UYVY-A format to RGBA. Input has 2 textures: - YUVTexture: UYVY 4:2:2 - AlphaTexture: A8
- L100-113 _entry_ `void NDIMediaP216ConvertPS( float4 InPosition : SV_POSITION, float2 InUV : TEXCOORD0, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FNDIMediaShaderP216toBGRAPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Media/NDIMedia/Source/NDIMediaRendering/Private/NDIMediaShaders.cpp:62) — Conversion of P216 (Y + UV interleaved, 16-bit 4:2:2) to RGBA.
- L116-130 _entry_ `void NDIMediaPA16ConvertPS( float4 InPosition : SV_POSITION, float2 InUV : TEXCOORD0, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FNDIMediaShaderPA16toBGRAPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Media/NDIMedia/Source/NDIMediaRendering/Private/NDIMediaShaders.cpp:98) — Conversion of PA16 (Y + UV interleaved + A, 16-bit 4:2:2) to RGBA.

#### Functions (2)

- L33-59 _function_ `float3 ApplyColorProcessingRGB(float3 Color, float4x4 CSMtx, uint EOTF, uint ToneMapMethod = 0)`
- L61-73 _function_ `float3 ApplyColorProcessing(float3 YUV, float4x4 YUVMtx, float4x4 CSMtx, uint EOTF, uint ToneMapMethod = 0)`
