# Shaders / Plugins/Compositing/Composite/Shaders/Private

- files: 12; lines: 1268
- record kinds: cpp_binding=10, define=23, entry=10, function=47, groupshared=1, include=35, macro_call=8, parameter=71, resource=27, static_const=9

### `Plugins/Compositing/Composite/Shaders/Private/CompositeBlur.usf` (Private)

- lines: 112; parse: all-branches
- includes: L2 `/Engine/Private/Common.ush`, L3 `/Engine/Private/ScreenPass.ush`, L4 `/Engine/Public/Platform.ush`, L6 `CompositeCommon.ush`

#### Macros (#define, 4)

- L19 `#define BLUR_TYPE float` _[#if ALPHA_ONLY]_
- L20 `#define TO_BLUR_TYPE(x) (x).a` _[#if ALPHA_ONLY]_
- L22 `#define BLUR_TYPE float4` _[#if !(ALPHA_ONLY)]_
- L23 `#define TO_BLUR_TYPE(x) (x)` _[#if !(ALPHA_ONLY)]_

#### Entry points (1)

- L96-111 _entry_ `void MainPS( float4 SvPosition : SV_POSITION, out float4 OutColor : SV_Target0 )` — stage: **pixel (from C++ binding)** — C++: `FCompositePassBlurShader` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Compositing/Composite/Source/Composite/Private/Passes/CompositePassBlur.cpp:30)

#### Global resources (textures / buffers / samplers) (2)

- L10 _resource_ `Texture2D Input_Texture;`
- L11 _resource_ `SamplerState Input_Sampler;`

#### Global parameters (uniforms) (4)

- L12 _parameter_ `FScreenTransform SvPositionToInputTextureUV;`
- L14 _parameter_ `float2 Dir;`
- L15 _parameter_ `float Radius;`
- L16 _parameter_ `uint bInvertedAlpha;`

#### Functions (4)

- L26-30 _function_ `float NormalDistribution1D(float X)`
- L32-35 _function_ `float2 ClampInputUV(float2 UV)`
- L38-44 _function_ `float4 SampleInputTexture(float2 UV)` — Samples the input texture, normalizing inverted alpha (e.g. UE scene color) to standard opacity for processing.
- L46-94 _function_ `BLUR_TYPE GaussianBlur(float2 UV)`

#### Top-level macro invocations (1)

- L13 _macro_call_ `SCREEN_PASS_TEXTURE_VIEWPORT(Input)`

### `Plugins/Compositing/Composite/Shaders/Private/CompositeColorGrading.usf` (Private)

- lines: 143; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `/Engine/Private/ScreenPass.ush`, L5 `/Engine/Private/TonemapCommon.ush`, L6 `/Engine/Private/ACES/ACESCommon.ush`, L8 `CompositeCommon.ush`

#### Entry points (1)

- L105-142 _entry_ `void MainPS( float4 SvPosition : SV_POSITION, out float4 OutColor : SV_Target0 )` — stage: **pixel (from C++ binding)** — C++: `FCompositePassColorGradingShader` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Compositing/Composite/Source/Composite/Private/Passes/CompositePassColorGrading.cpp:58)

#### Global resources (textures / buffers / samplers) (2)

- L14 _resource_ `Texture2D Input_Texture;`
- L15 _resource_ `SamplerState Input_Sampler;`

#### Global parameters (uniforms) (29)

- L16 _parameter_ `FScreenTransform SvPositionToInputTextureUV;`
- L18 _parameter_ `uint bIsTemperatureWhiteBalance;`
- L19 _parameter_ `float WhiteTemp;`
- L20 _parameter_ `float WhiteTint;`
- L22 _parameter_ `float4 Global_Saturation;`
- L23 _parameter_ `float4 Global_Contrast;`
- L24 _parameter_ `float4 Global_Gamma;`
- L25 _parameter_ `float4 Global_Gain;`
- L26 _parameter_ `float4 Global_Offset;`
- L28 _parameter_ `float4 Shadows_Saturation;`
- L29 _parameter_ `float4 Shadows_Contrast;`
- L30 _parameter_ `float4 Shadows_Gamma;`
- L31 _parameter_ `float4 Shadows_Gain;`
- L32 _parameter_ `float4 Shadows_Offset;`
- L34 _parameter_ `float4 Midtones_Saturation;`
- L35 _parameter_ `float4 Midtones_Contrast;`
- L36 _parameter_ `float4 Midtones_Gamma;`
- L37 _parameter_ `float4 Midtones_Gain;`
- L38 _parameter_ `float4 Midtones_Offset;`
- L40 _parameter_ `float4 Highlights_Saturation;`
- L41 _parameter_ `float4 Highlights_Contrast;`
- L42 _parameter_ `float4 Highlights_Gamma;`
- L43 _parameter_ `float4 Highlights_Gain;`
- L44 _parameter_ `float4 Highlights_Offset;`
- L46 _parameter_ `uint bInputIsPremultiplied;`
- L47 _parameter_ `uint bInvertedAlpha;`
- L48 _parameter_ `float ShadowsMax;`
- L49 _parameter_ `float HighlightsMin;`
- L50 _parameter_ `float HighlightsMax;`

#### static const (3)

- L10 _static_const_ `static const float DefaultTemperature = 6500.0;`
- L11 _static_const_ `static const float DefaultTint = 0.0;`
- L12 _static_const_ `static const float Epsilon = 1e-8;`

#### Functions (2)

- L52-65 _function_ `float3 ColorCorrect( float3 WorkingColor, float4 ColorSaturation, float4 ColorContrast, float4 ColorGamma, float4 ColorGain, float4 ColorOffset )`
- L68-103 _function_ `float3 ColorCorrectAll( float3 WorkingColor )` — Nuke-style Color Correct

### `Plugins/Compositing/Composite/Shaders/Private/CompositeColorKeyer.usf` (Private)

- lines: 156; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `/Engine/Private/ScreenPass.ush`, L6 `CompositeColorKeyerCommon.ush`

#### Entry points (1)

- L55-155 _entry_ `float4 MainPS(float4 SvPosition : SV_POSITION) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FCompositePassColorKeyerShader` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Compositing/Composite/Source/Composite/Private/Passes/CompositePassColorKeyer.cpp:71)

#### Global resources (textures / buffers / samplers) (4)

- L8 _resource_ `Texture2D Input_Texture;`
- L9 _resource_ `SamplerState Input_Sampler;`
- L11 _resource_ `Texture2D CleanPlate_Texture;`
- L12 _resource_ `SamplerState CleanPlate_Sampler;`

#### Global parameters (uniforms) (10)

- L16 _parameter_ `FScreenTransform SvPositionToInputTextureUV;`
- L18 _parameter_ `float3 KeyColor;`
- L19 _parameter_ `float4 Params0;`
- L20 _parameter_ `float4 Params1;`
- L21 _parameter_ `uint KeyerMode;`
- L22 _parameter_ `uint bDisplaySpaceLuminance;`
- L23 _parameter_ `uint ScreenType;`
- L24 _parameter_ `uint Visualization;`
- L25 _parameter_ `uint bInvertAlpha;`
- L26 _parameter_ `uint bPreserveVignetteAfterKey;`

#### Functions (2)

- L28-31 _function_ `float2 UVToScreenPos(float2 UV, float2 Extent)`
- L34-53 _function_ `float4 Output(float4 Color)` — Output color function with debug convenience

#### Top-level macro invocations (2)

- L14 _macro_call_ `SCREEN_PASS_TEXTURE_VIEWPORT(Input)`
- L15 _macro_call_ `SCREEN_PASS_TEXTURE_VIEWPORT(Output)`

### `Plugins/Compositing/Composite/Shaders/Private/CompositeColorKeyerCommon.ush` (Private)

- lines: 329; parse: all-branches
- includes: L5 `/Engine/Private/ACES/ACESCommon.ush`, L6 `/Engine/Private/ColorSpace.ush`, L7 `/Engine/Private/GammaCorrectionCommon.ush`, L8 `/Engine/Private/PostProcessCommon.ush`, L10 `CompositeCommon.ush`
- L3 #pragma `once`

#### static const (5)

- L13 _static_const_ `static const float3 XYZ_n = xyY_2_XYZ(float3(0.3127, 0.3290, 1.0));` — CIE 1931 D65 white point
- L14 _static_const_ `static const float ZeroEpsilon = 1.0e-6;`
- L15 _static_const_ `static const float DeltaE_JND = 1.0;`
- L16 _static_const_ `static const float Lstar_CIELUV = 100.0;`
- L17 _static_const_ `static const float Lstar_CIELUV_Inv = 1.0 / Lstar_CIELUV;`

#### Functions (26)

- L19-22 _function_ `float LuminanceSRGB(float3 InColor)`
- L25-28 _function_ `float Linearstep(float Edge0, float Edge1, float X)` — Linear equivalent of smoothstep
- L30-36 _function_ `float2 Project(float2 VecA, float2 VecB)`
- L39-45 _function_ `float2 ProjectClamped(float2 VecA, float2 VecB)` — Project vector A onto B, and return 0 if the projection was negative
- L47-53 _function_ `float3 ProjectClamped(float3 VecA, float3 VecB)`
- L55-58 _function_ `float GetAngle(float2 A, float2 B)`
- L60-66 _function_ `float2 Rotate2D(float2 V, float Theta)`
- L70-95 _function_ `float3 CIE_XYZ_to_Luv(float3 XYZ)` — Convert color from XYZ to CIE 1976 L*, u*, v* color space. We use the latter for its improved perceptual uniformity, as a way to measure chromaticity distance for keying.
- L98-127 _function_ `float3 CIE_Luv_to_XYZ(float3 Luv)` — Convert color from CIE 1976 L*, u*, v* to XYZ color space.
- L129-132 _function_ `float3 RGB_to_Luv(float3 InRGB)`
- L134-137 _function_ `float3 Luv_to_RGB(float3 InLuv)`
- L139-148 _function_ `float3 GreenDespillAvg(float3 Color)`
- L150-159 _function_ `float3 BlueDespillAvg(float3 Color)`
- L161-173 _function_ `float Vignette(float2 ScreenPos, float AspectRatio, float Intensity)`
- L175-225 _function_ `float4 GreenScreenKeyer( float4 Foreground, float3 Background, float RedWeight, float BlueWeight)`
- L227-230 _function_ `float3 SwizzleRG(float3 InColor)`
- L232-235 _function_ `float3 SwizzleGB(float3 InColor)`
- L237-240 _function_ `float4 SwizzleRG(float4 InColor)`
- L242-245 _function_ `float4 SwizzleGB(float4 InColor)`
- L247-255 _function_ `float4 RedScreenKeyer(float4 Foreground, float3 Background, float GreenWeight, float BlueWeight)`
- L257-265 _function_ `float4 BlueScreenKeyer(float4 Foreground, float3 Background, float RedWeight, float GreenWeight)`
- L268-277 _function_ `float4 LuvDistanceKeyer(float3 Foreground_Luv, float3 Background_Luv, float MinDistance, float MaxDistance)` — Experimental
- L280-299 _function_ `float4 LuvAngleKeyer(float3 Foreground_Luv, float3 Background_Luv, float Acceptance, float Scale)` — Experimental
- L302-307 _function_ `void Sort2(inout float4 A, inout float4 B)` — Branchless 2-value sort
- L310-322 _function_ `float4 Median9(float4 A0, float4 A1, float4 A2, float4 A3, float4 A4, float4 A5, float4 A6, float4 A7, float4 A8)` — Median of 9 colors (https://bertdobbelaere.github.io/median_networks.html#N9L19D7)
- L325-328 _function_ `float4 DenoiseMedianFilter9(const float4 V[9])` — Denoising with per-channel median filter of 9 colors

### `Plugins/Compositing/Composite/Shaders/Private/CompositeCommon.ush` (Private)

- lines: 66; parse: all-branches
- includes: L5 `/Engine/Private/GammaCorrectionCommon.ush`

#### Macros (#define, 3)

- L7 `#define ESourceEncoding_None 0`
- L8 `#define ESourceEncoding_Gamma 1`
- L9 `#define ESourceEncoding_sRGB 2`
- L3 #pragma `once`

#### Functions (6)

- L12-15 _function_ `float SafeRcp(float x)` — Safe reciprocal
- L17-20 _function_ `float4 Unpremultiply(float4 InColor)`
- L22-25 _function_ `float4 Premultiply(float4 InColor)`
- L27-30 _function_ `float InvertAlpha(float InAlpha, uint bInvertedAlpha)`
- L32-47 _function_ `float3 Decode(float3 InColor, uint InEncoding)`
- L49-64 _function_ `float3 Encode(float3 InColor, uint InEncoding)`

### `Plugins/Compositing/Composite/Shaders/Private/CompositeDenoise.usf` (Private)

- lines: 108; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `/Engine/Private/ScreenPass.ush`, L6 `CompositeColorKeyerCommon.ush`

#### Macros (#define, 5)

- L12 `#define FILTER_SIZE 1`
- L13 `#define FILTER_COUNT (1 + 2 * FILTER_SIZE) * (1 + 2 * FILTER_SIZE)`
- L15 `#define LDS_TILE_WIDTH (TILE_SIZE + 2 * FILTER_SIZE)`
- L17 `#define LDS_ARRAY_SIZE (LDS_TILE_WIDTH * LDS_TILE_WIDTH)`
- L18 `#define THREADGROUP_TOTAL (TILE_SIZE * TILE_SIZE)`

#### Entry points (1)

- L53-107 _entry_ `[numthreads(TILE_SIZE, TILE_SIZE, 1)] void MainCS( uint2 GroupId : SV_GroupID, uint2 GroupThreadId : SV_GroupThreadID, uint GroupThreadIndex : SV_GroupIndex, uint2 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FCompositePassDenoiseShader` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Compositing/Composite/Source/Composite/Private/Passes/CompositePassColorKeyer.cpp:70)

#### Global resources (textures / buffers / samplers) (3)

- L20 _resource_ `Texture2D Input_Texture;`
- L21 _resource_ `SamplerState Input_Sampler;`
- L24 _resource_ `RWTexture2D<float4> RWOutputTexture;`

#### groupshared (1)

- L26 _groupshared_ `groupshared float4 SharedColor[LDS_ARRAY_SIZE];`

#### static const (1)

- L28-38 _static_const_ `static const int2 kOffsets[FILTER_COUNT] = { int2( 0, 0), int2(-1, 0), int2( 1, 0), int2( 0, 1), int2( 0, -1), int2(-1, 1), int2( 1, 1), int2( 1, -1), int2(-1, -1), };`

#### Functions (2)

- L41-45 _function_ `uint GetTileArrayIndexFromPixelOffset(in uint2 GroupThreadId, in int2 PixelOffset)` — Get the index within the LDS array.
- L47-50 _function_ `float4 SampleCachedColors(in uint2 GroupThreadId, int2 PixelOffset = int2(0,0))`

#### Top-level macro invocations (1)

- L22 _macro_call_ `SCREEN_PASS_TEXTURE_VIEWPORT(Input)`

### `Plugins/Compositing/Composite/Shaders/Private/CompositeDistortion.usf` (Private)

- lines: 49; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `/Engine/Private/LensDistortion.ush`, L5 `/Engine/Private/ScreenPass.ush`

#### Macros (#define, 3)

- L12 `#define EDistortionUV_None 0`
- L13 `#define EDistortionUV_Distorted 1`
- L14 `#define EDistortionUV_Undistorted 2`

#### Entry points (1)

- L38-48 _entry_ `void MainPS( float4 SvPosition : SV_POSITION, out float4 OutColor : SV_Target0 )` — stage: **pixel (from C++ binding)** — C++: `FCompositePassDistortionShader` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Compositing/Composite/Source/Composite/Private/Passes/CompositePassDistortion.cpp:36)

#### Global resources (textures / buffers / samplers) (6)

- L7 _resource_ `Texture2D Input_Texture;`
- L8 _resource_ `SamplerState Input_Sampler;`
- L16 _resource_ `Texture2D<float2> DistortingDisplacementTexture;`
- L17 _resource_ `SamplerState DistortingDisplacementSampler;`
- L18 _resource_ `Texture2D<float2> UndistortingDisplacementTexture;`
- L19 _resource_ `SamplerState UndistortingDisplacementSampler;`

#### Global parameters (uniforms) (1)

- L21 _parameter_ `uint DistortionUV;`

#### Functions (1)

- L23-36 _function_ `float2 CalcInputUVs(float2 ViewportUV, float2 ViewportSize, float2 ViewportMin, float2 ExtentInverse, uint InDistortionUV)`

#### Top-level macro invocations (2)

- L9 _macro_call_ `SCREEN_PASS_TEXTURE_VIEWPORT(Input)`
- L10 _macro_call_ `SCREEN_PASS_TEXTURE_VIEWPORT(Output)`

### `Plugins/Compositing/Composite/Shaders/Private/CompositeMasking.usf` (Private)

- lines: 82; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `/Engine/Private/ScreenPass.ush`, L6 `CompositeCommon.ush`

#### Macros (#define, 2)

- L8 `#define INPUT_PASS_TEXTURE_MEMBER(StructName, MemberType, MemberName) MemberType StructName##_##MemberName;`
- L10 `#define INPUT_PASS_TEXTURE(StructName) INPUT_PASS_TEXTURE_MEMBER(StructName, Texture2D, Texture) INPUT_PASS_TEXTURE_MEMBER(StructName, SamplerState, Sampler) INPUT_PASS_TEXTURE_MEMBER(StructName, uint, bInvertedAlpha) INPUT_PASS_TEXTURE_ME ...` (5 lines)

#### Entry points (1)

- L27-81 _entry_ `void MainPS( float4 SvPosition : SV_POSITION, out float4 OutColor : SV_Target0 )` — stage: **pixel (from C++ binding)** — C++: `FCompositePassMaskingShader` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Compositing/Composite/Source/Composite/Private/Passes/CompositePassMasking.cpp:44)

#### Global parameters (uniforms) (6)

- L19 _parameter_ `FScreenTransform SvPositionToInputTextureUV;`
- L20 _parameter_ `FScreenTransform SvPositionToMaskTextureUV;`
- L22 _parameter_ `uint MaskSourceChannel;`
- L23 _parameter_ `uint bInputIsPremultiplied;`
- L24 _parameter_ `uint bPremultipliedInDisplaySpace;`
- L25 _parameter_ `uint bInvert;`

#### Top-level macro invocations (2)

- L16 _macro_call_ `INPUT_PASS_TEXTURE(Input)`
- L17 _macro_call_ `INPUT_PASS_TEXTURE(Mask)`

### `Plugins/Compositing/Composite/Shaders/Private/CompositePlanarReflection.usf` (Private)

- lines: 20; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`

#### Entry points (1)

- L9-19 _entry_ `void MainPS( noperspective float4 InUVAndScreenPos : TEXCOORD0, out float4 OutColor : SV_Target0 )` — stage: **pixel (from C++ binding)** — C++: `FCompositePlanarReflectionShader` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Compositing/Composite/Source/Composite/Private/Layers/CompositeLayerPlanarReflection.cpp:35)

#### Global resources (textures / buffers / samplers) (2)

- L5 _resource_ `Texture2D InputTexture;`
- L6 _resource_ `SamplerState InputSampler;`

#### Global parameters (uniforms) (1)

- L7 _parameter_ `float ReflectionStrength;`

### `Plugins/Compositing/Composite/Shaders/Private/CompositeSingleLightShadow.usf` (Private)

- lines: 94; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `/Engine/Private/ShadowFilteringCommon.ush`

#### Entry points (1)

- L65-93 _entry_ `void MainPS( noperspective float4 InUVAndScreenPos : TEXCOORD0, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FCompositeSingleLightShadowShader` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Compositing/Composite/Source/Composite/Private/Layers/CompositeLayerSingleLightShadow.cpp:42)

#### Global resources (textures / buffers / samplers) (4)

- L6 _resource_ `Texture2D SceneDepthTex;`
- L7 _resource_ `SamplerState SceneDepthSampler;`
- L9 _resource_ `Texture2D ShadowDepthTexture;`
- L10 _resource_ `SamplerState ShadowDepthTextureSampler;`

#### Global parameters (uniforms) (8)

- L12 _parameter_ `float4 SceneDepthPositionScaleBias;`
- L13 _parameter_ `float4x4 SceneDepthScreenToWorld;`
- L15 _parameter_ `float4x4 ShadowMatrix;`
- L16 _parameter_ `float4 ShadowBufferSize;`
- L17 _parameter_ `float4 ShadowInvDeviceZToWorldZ;`
- L18 _parameter_ `float4 ShadowStrengthBias;`
- L19 _parameter_ `float3 LightWorldDirection;`
- L21 _parameter_ `uint bIsPerspectiveProjection;`

#### Functions (4)

- L24-27 _function_ `float2 GetScreenPositionForProj(in float2 ScreenPosition, in float SceneDepth)` — Returns the screen position for projection matrix calculations depending on the type of projection the view is using
- L30-37 _function_ `float4 CalcWorldFromSceneDepth(in float2 UV, in float Depth)` — Calculate world position from scene depth
- L40-43 _function_ `float ShadowDeviceZToSceneDepth(float DeviceZ)` — Convert device-z depth to scene depth
- L46-63 _function_ `float ManualPCF(in float4 ShadowPosition, in float NoL)` — Percentage-close filtering shadow mapping

### `Plugins/Compositing/Composite/Shaders/Private/CompositeTransform2D.usf` (Private)

- lines: 46; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `/Engine/Private/ScreenPass.ush`

#### Entry points (1)

- L16-45 _entry_ `void MainPS( float4 SvPosition : SV_POSITION, out float4 OutColor : SV_Target0 )` — stage: **pixel (from C++ binding)** — C++: `FCompositePassTransform2DShader` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Compositing/Composite/Source/Composite/Private/Passes/CompositePassTransform2D.cpp:36)

#### Global resources (textures / buffers / samplers) (2)

- L6 _resource_ `Texture2D Input_Texture;`
- L7 _resource_ `SamplerState Input_Sampler;`

#### Global parameters (uniforms) (7)

- L8 _parameter_ `FScreenTransform SvPositionToOutputViewportUV;`
- L9 _parameter_ `FScreenTransform OutputViewportUVToInputTextureUV;`
- L10 _parameter_ `float2 Pivot;`
- L11 _parameter_ `float2 ScaleUV;`
- L12 _parameter_ `float RotationRadians;`
- L13 _parameter_ `float2 Translation;`
- L14 _parameter_ `float AspectRatio;`

### `Plugins/Compositing/Composite/Shaders/Private/CompositeTranslucency.usf` (Private)

- lines: 63; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `/Engine/Private/ScreenPass.ush`, L6 `CompositeCommon.ush`

#### Macros (#define, 6)

- L17 `#define PremultOp_None 0u`
- L18 `#define PremultOp_Premultiply 1u`
- L19 `#define PremultOp_Unpremultiply 2u`
- L21 `#define OverrideOutput_None 0u`
- L22 `#define OverrideOutput_Zero 1u`
- L23 `#define OverrideOutput_One 2u`

#### Entry points (1)

- L25-62 _entry_ `void MainPS( float4 SvPosition : SV_POSITION, out float4 OutColor : SV_Target0 )` — stage: **pixel (from C++ binding)** — C++: `FCompositePassTranslucencyShader` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Compositing/Composite/Source/Composite/Private/Passes/CompositePassTranslucency.cpp:29)

#### Global resources (textures / buffers / samplers) (2)

- L9 _resource_ `Texture2D Input_Texture;`
- L10 _resource_ `SamplerState Input_Sampler;`

#### Global parameters (uniforms) (5)

- L8 _parameter_ `FScreenTransform SvPositionToInputTextureUV;`
- L12 _parameter_ `uint PremultOp;`
- L13 _parameter_ `float Fade;`
- L14 _parameter_ `uint OverrideOutputAlpha;`
- L15 _parameter_ `uint bInvertedAlpha;`
