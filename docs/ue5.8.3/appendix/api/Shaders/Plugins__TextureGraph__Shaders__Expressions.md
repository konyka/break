# Shaders / Plugins/TextureGraph/Shaders/Expressions

- files: 29; lines: 2204
- record kinds: cpp_binding=97, define=61, entry=96, function=23, include=82, parameter=82, resource=43

### `Plugins/TextureGraph/Shaders/Expressions/Expression_Blend.usf` (Other)

- lines: 246; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L3 `/Plugin/TextureGraph/SamplerStates.ush`

#### Entry points (11)

- L21-40 _entry_ `float4 FSH_BlendNormal(in float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_BlendNormal` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Blend.cpp:11)
- L42-60 _entry_ `float4 FSH_BlendAdd(in float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_BlendAdd` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Blend.cpp:12)
- L62-81 _entry_ `float4 FSH_BlendSubtract(in float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_BlendSubtract` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Blend.cpp:13)
- L83-102 _entry_ `float4 FSH_BlendMultiply(in float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_BlendMultiply` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Blend.cpp:14)
- L104-125 _entry_ `float4 FSH_BlendDivide(in float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_BlendDivide` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Blend.cpp:15)
- L127-146 _entry_ `float4 FSH_BlendDifference(in float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_BlendDifference` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Blend.cpp:16)
- L148-167 _entry_ `float4 FSH_BlendMax(in float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_BlendMax` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Blend.cpp:17)
- L169-188 _entry_ `float4 FSH_BlendMin(in float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_BlendMin` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Blend.cpp:18)
- L190-210 _entry_ `float4 FSH_BlendStep(in float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_BlendStep` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Blend.cpp:19)
- L222-241 _entry_ `float4 FSH_BlendOverlay(in float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_BlendOverlay` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Blend.cpp:20)
- L243-246 _entry_ `float4 FSH_BlendDistort(in float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_BlendDistort` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Blend.cpp:21)

#### Global resources (textures / buffers / samplers) (3)

- L5 _resource_ `Texture2D BackgroundTexture;`
- L6 _resource_ `Texture2D ForegroundTexture;`
- L7 _resource_ `Texture2D MaskTexture;`

#### Global parameters (uniforms) (1)

- L8 _parameter_ `float Opacity;`

#### Functions (3)

- L10-19 _function_ `float GetMask(Texture2D MaskTexture, float2 uv, float Opacity)`
- L212-215 _function_ `float4 OverlayBlend( float4 base , float4 overlay )`
- L217-220 _function_ `float3 OverlayBlend( float3 base , float3 overlay )`

### `Plugins/TextureGraph/Shaders/Expressions/Expression_Brightness.usf` (Other)

- lines: 15; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L3 `/Plugin/TextureGraph/SamplerStates.ush`, L4 `/Plugin/TextureGraph/ShaderUtil.ush`

#### Entry points (1)

- L10-14 _entry_ `float4 FSH_Brightness(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_Brightness` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Brightness.cpp:11)

#### Global resources (textures / buffers / samplers) (1)

- L6 _resource_ `Texture2D SourceTexture;`

#### Global parameters (uniforms) (2)

- L7 _parameter_ `float Brightness;`
- L8 _parameter_ `float Contrast;`

### `Plugins/TextureGraph/Shaders/Expressions/Expression_ChannelCombiner.usf` (Other)

- lines: 19; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L3 `/Plugin/TextureGraph/SamplerStates.ush`

#### Entry points (1)

- L10-18 _entry_ `float4 FSH_ChannelCombiner(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_ChannelCombiner` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Channel.cpp:18)

#### Global resources (textures / buffers / samplers) (4)

- L5 _resource_ `Texture2D SourceRed;`
- L6 _resource_ `Texture2D SourceGreen;`
- L7 _resource_ `Texture2D SourceBlue;`
- L8 _resource_ `Texture2D SourceAlpha;`

### `Plugins/TextureGraph/Shaders/Expressions/Expression_ChannelSplitter.usf` (Other)

- lines: 30; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L3 `/Plugin/TextureGraph/SamplerStates.ush`

#### Entry points (4)

- L7-11 _entry_ `float4 FSH_ChannelSplitter_Red(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_ChannelSplitter_Red` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Channel.cpp:13)
- L13-17 _entry_ `float4 FSH_ChannelSplitter_Green(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_ChannelSplitter_Green` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Channel.cpp:14)
- L19-23 _entry_ `float4 FSH_ChannelSplitter_Blue(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_ChannelSplitter_Blue` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Channel.cpp:15)
- L25-29 _entry_ `float4 FSH_ChannelSplitter_Alpha(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_ChannelSplitter_Alpha` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Channel.cpp:16)

#### Global resources (textures / buffers / samplers) (1)

- L5 _resource_ `Texture2D SourceTexture;`

### `Plugins/TextureGraph/Shaders/Expressions/Expression_ChannelSwizzle.usf` (Other)

- lines: 74; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L3 `/Plugin/TextureGraph/SamplerStates.ush`

#### Macros (#define, 7)

- L7 `#define LINEAR 0`
- L8 `#define EXP 1`
- L9 `#define LOG 1`
- L12 `#define DST_CHANNEL_RED 0` _[#if !defined(DST_CHANNEL_RED)]_
- L16 `#define DST_CHANNEL_GREEN 1` _[#if !defined(DST_CHANNEL_GREEN)]_
- L20 `#define DST_CHANNEL_BLUE 2` _[#if !defined(DST_CHANNEL_BLUE)]_
- L24 `#define DST_CHANNEL_ALPHA 3` _[#if !defined(DST_CHANNEL_ALPHA)]_

#### Entry points (1)

- L27-73 _entry_ `float4 FSH_ChannelSwizzle(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_ChannelSwizzle` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Channel.cpp:20)

#### Global resources (textures / buffers / samplers) (1)

- L5 _resource_ `Texture2D SourceTexture;`

### `Plugins/TextureGraph/Shaders/Expressions/Expression_Clamp.usf` (Other)

- lines: 26; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L3 `/Plugin/TextureGraph/SamplerStates.ush`

#### Entry points (2)

- L9-16 _entry_ `float4 FSH_Clamp(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_Clamp` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Clamp.cpp:11)
- L18-25 _entry_ `float4 FSH_SmoothStep(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_SmoothStep` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Clamp.cpp:12)

#### Global resources (textures / buffers / samplers) (3)

- L5 _resource_ `Texture2D SourceTexture;`
- L6 _resource_ `Texture2D MinValue;`
- L7 _resource_ `Texture2D MaxValue;`

### `Plugins/TextureGraph/Shaders/Expressions/Expression_ColorCorrection.usf` (Other)

- lines: 35; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L3 `/Plugin/TextureGraph/SamplerStates.ush`, L4 `/Plugin/TextureGraph/ShaderUtil.ush`

#### Entry points (1)

- L17-34 _entry_ `float4 FSH_ColorCorrection(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_ColorCorrection` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Color.cpp:16)

#### Global resources (textures / buffers / samplers) (1)

- L6 _resource_ `Texture2D Input;`

#### Global parameters (uniforms) (9)

- L7 _parameter_ `float Brightness;`
- L8 _parameter_ `float Contrast;`
- L9 _parameter_ `float Gain;`
- L10 _parameter_ `float Lift;`
- L11 _parameter_ `float Gamma;`
- L12 _parameter_ `float Saturation;`
- L13 _parameter_ `float4 TemperatureRGB;`
- L14 _parameter_ `float TemperatureStrength;`
- L15 _parameter_ `float TemperatureBrightnessNormalization;`

### `Plugins/TextureGraph/Shaders/Expressions/Expression_DirectionalBlur.usf` (Other)

- lines: 55; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L3 `/Plugin/TextureGraph/SamplerStates.ush`, L4 `/Plugin/TextureGraph/TileInfo.ush`

#### Entry points (1)

- L25-54 _entry_ `float4 FSH_DirectionalBlur(float2 UV : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_DirectionalBlur` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Blur.cpp:9)

#### Global resources (textures / buffers / samplers) (1)

- L6 _resource_ `Texture2D SourceTexture;`

#### Global parameters (uniforms) (5)

- L7 _parameter_ `float Angle;`
- L8 _parameter_ `float Strength;`
- L9 _parameter_ `float Steps;`
- L10 _parameter_ `float Sigma;`
- L11 _parameter_ `float StrengthMultiplier;`

#### Functions (1)

- L13-23 _function_ `float2 GetTexelSize(Texture2D Tex)`

### `Plugins/TextureGraph/Shaders/Expressions/Expression_EdgeDetect.usf` (Other)

- lines: 57; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L3 `/Plugin/TextureGraph/SamplerStates.ush`, L4 `/Plugin/TextureGraph/TileInfo.ush`

#### Entry points (1)

- L42-56 _entry_ `float4 FSH_EdgeDetect(float2 InUV : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_EdgeDetect` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Filter.cpp:10)

#### Global resources (textures / buffers / samplers) (1)

- L6 _resource_ `Texture2D SourceTexture;`

#### Global parameters (uniforms) (1)

- L7 _parameter_ `float Thickness;`

#### Functions (2)

- L9-12 _function_ `float Intensity(float4 Color)`
- L14-40 _function_ `float3 Sobel(float StepX, float StepY, float2 Center)`

### `Plugins/TextureGraph/Shaders/Expressions/Expression_ErodeDilate.usf` (Other)

- lines: 93; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L3 `/Plugin/TextureGraph/SamplerStates.ush`, L4 `/Plugin/TextureGraph/TileInfo.ush`, L5 `/Plugin/TextureGraph/ShaderUtil.ush`

#### Macros (#define, 5)

- L8 `#define ED_KERNEL_BOX 0` _[#if !defined(ED_KERNEL_BOX)]_
- L12 `#define ED_KERNEL_CIRCULAR 1` _[#if !defined(ED_KERNEL_CIRCULAR)]_
- L16 `#define ED_KERNEL_DIAMOND 2` _[#if !defined(ED_KERNEL_DIAMOND)]_
- L20 `#define ED_ERODE 0` _[#if !defined(ED_ERODE)]_
- L24 `#define ED_DILATE 1` _[#if !defined(ED_DILATE)]_

#### Entry points (1)

- L30-92 _entry_ `float4 FSH_ErodeDilate(float2 InUV : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_ErodeDilate` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Filter.cpp:14)

#### Global resources (textures / buffers / samplers) (1)

- L27 _resource_ `Texture2D Input;`

#### Global parameters (uniforms) (1)

- L28 _parameter_ `int Size;`

### `Plugins/TextureGraph/Shaders/Expressions/Expression_GaussianBlur.usf` (Other)

- lines: 88; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L3 `/Plugin/TextureGraph/SamplerStates.ush`, L4 `/Plugin/TextureGraph/TileInfo.ush`

#### Entry points (1)

- L76-87 _entry_ `float4 FSH_GaussianBlur(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_GaussianBlur` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Blur.cpp:8)

#### Global resources (textures / buffers / samplers) (1)

- L7 _resource_ `Texture2D SourceTexture;`

#### Global parameters (uniforms) (1)

- L8 _parameter_ `int Radius;`

#### Functions (3)

- L11-24 _function_ `float NormalDistribution(float x, float y)` — Algorithm from https://www.pixelstech.net/article/1353768112-Gaussian-Blur-Algorithm
- L26-29 _function_ `float NormalDistribution1D(float x)`
- L32-74 _function_ `float4 GaussianBlur(float2 texelUV, float2 texelPos, int radius)`

### `Plugins/TextureGraph/Shaders/Expressions/Expression_Gradient.usf` (Other)

- lines: 145; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`, L4 `/Plugin/TextureGraph/SamplerStates.ush`, L5 `/Plugin/TextureGraph/TileInfo.ush`, L6 `/Plugin/TextureGraph/Paint.ush`

#### Macros (#define, 9)

- L8 `#define LINEAR 0`
- L9 `#define EXP 1`
- L10 `#define LOG 1`
- L12 `#define ROT_0 0`
- L13 `#define ROT_90 1`
- L14 `#define ROT_180 2`
- L15 `#define ROT_270 3`
- L18 `#define GRADIENT_INTERPOLATION LINEAR` _[#if !defined(GRADIENT_INTERPOLATION)]_
- L22 `#define GRADIENT_ROTATION ROT_0` _[#if !defined(GRADIENT_ROTATION)]_

#### Entry points (5)

- L37-59 _entry_ `float4 FSH_GradientLinear_1(float2 InUV : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_GradientLinear_1` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Mask/T_Gradient.cpp:16)
- L61-84 _entry_ `float4 FSH_GradientLinear_2(float2 InUV : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_GradientLinear_2` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Mask/T_Gradient.cpp:17)
- L86-102 _entry_ `float4 FSH_GradientRadial(float2 InUV : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_GradientRadial` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Mask/T_Gradient.cpp:18)
- L118-130 _entry_ `float4 FSH_GradientAxial1(float2 InUV : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_GradientAxial1` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Mask/T_Gradient.cpp:19)
- L132-144 _entry_ `float4 FSH_GradientAxial2(float2 InUV : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_GradientAxial2` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Mask/T_Gradient.cpp:20)

#### Global parameters (uniforms) (3)

- L25 _parameter_ `float4 Center = float4(0, 0, 0, 0);`
- L26 _parameter_ `float4 Line = float4(0, 0, 0, 0);`
- L27 _parameter_ `float4 LineDir = float4(0, 0, 0, 0);`

#### Functions (2)

- L29-35 _function_ `float CalcExp(float Input)`
- L104-116 _function_ `float GetAxialValue(float2 UV)`

### `Plugins/TextureGraph/Shaders/Expressions/Expression_Grayscale.usf` (Other)

- lines: 14; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L3 `/Plugin/TextureGraph/SamplerStates.ush`, L4 `/Plugin/TextureGraph/ShaderUtil.ush`

#### Entry points (1)

- L8-13 _entry_ `float4 FSH_Grayscale(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_Grayscale` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Color.cpp:11)

#### Global resources (textures / buffers / samplers) (1)

- L6 _resource_ `Texture2D SourceTexture;`

### `Plugins/TextureGraph/Shaders/Expressions/Expression_HSV.usf` (Other)

- lines: 32; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L3 `/Plugin/TextureGraph/SamplerStates.ush`, L4 `/Plugin/TextureGraph/ShaderUtil.ush`

#### Entry points (3)

- L11-17 _entry_ `float4 FSH_HSV(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_HSV` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Color.cpp:13)
- L19-24 _entry_ `float4 FSH_RGB2HSV(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_RGB2HSV` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Color.cpp:14)
- L26-31 _entry_ `float4 FSH_HSV2RGB(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_HSV2RGB` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Color.cpp:15)

#### Global resources (textures / buffers / samplers) (1)

- L6 _resource_ `Texture2D Input;`

#### Global parameters (uniforms) (3)

- L7 _parameter_ `float Hue = 1;`
- L8 _parameter_ `float Saturation = 1;`
- L9 _parameter_ `float Value = 1;`

### `Plugins/TextureGraph/Shaders/Expressions/Expression_IfThenElse.usf` (Other)

- lines: 317; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L3 `/Plugin/TextureGraph/SamplerStates.ush`, L4 `/Plugin/TextureGraph/ShaderUtil.ush`

#### Entry points (18)

- L14-28 _entry_ `float4 FSH_IfThenElse_GT_Component(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_IfThenElse` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_TwoInputs.cpp:23) — C++: `FSH_IfThenElse_GT_Component` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_TwoInputs.cpp:25) — GT
- L30-45 _entry_ `float4 FSH_IfThenElse_GT_All(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_IfThenElse_GT_All` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_TwoInputs.cpp:26)
- L47-59 _entry_ `float4 FSH_IfThenElse_GT_Grayscale(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_IfThenElse_GT_Grayscale` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_TwoInputs.cpp:27)
- L64-78 _entry_ `float4 FSH_IfThenElse_GTE_Component(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_IfThenElse_GTE_Component` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_TwoInputs.cpp:29) — GT
- L80-98 _entry_ `float4 FSH_IfThenElse_GTE_All(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_IfThenElse_GTE_All` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_TwoInputs.cpp:30)
- L100-112 _entry_ `float4 FSH_IfThenElse_GTE_Grayscale(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_IfThenElse_GTE_Grayscale` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_TwoInputs.cpp:31)
- L118-132 _entry_ `float4 FSH_IfThenElse_LT_Component(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_IfThenElse_LT_Component` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_TwoInputs.cpp:33) — LT
- L134-149 _entry_ `float4 FSH_IfThenElse_LT_All(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_IfThenElse_LT_All` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_TwoInputs.cpp:34)
- L151-163 _entry_ `float4 FSH_IfThenElse_LT_Grayscale(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_IfThenElse_LT_Grayscale` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_TwoInputs.cpp:35)
- L168-182 _entry_ `float4 FSH_IfThenElse_LTE_Component(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_IfThenElse_LTE_Component` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_TwoInputs.cpp:37) — LT
- L184-202 _entry_ `float4 FSH_IfThenElse_LTE_All(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_IfThenElse_LTE_All` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_TwoInputs.cpp:38)
- L204-216 _entry_ `float4 FSH_IfThenElse_LTE_Grayscale(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_IfThenElse_LTE_Grayscale` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_TwoInputs.cpp:39)
- L221-235 _entry_ `float4 FSH_IfThenElse_EQ_Component(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_IfThenElse_EQ_Component` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_TwoInputs.cpp:41) — EQ
- L237-252 _entry_ `float4 FSH_IfThenElse_EQ_All(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_IfThenElse_EQ_All` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_TwoInputs.cpp:42)
- L254-266 _entry_ `float4 FSH_IfThenElse_EQ_Grayscale(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_IfThenElse_EQ_Grayscale` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_TwoInputs.cpp:43)
- L271-285 _entry_ `float4 FSH_IfThenElse_NEQ_Component(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_IfThenElse_NEQ_Component` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_TwoInputs.cpp:45) — NEQ
- L287-302 _entry_ `float4 FSH_IfThenElse_NEQ_All(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_IfThenElse_NEQ_All` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_TwoInputs.cpp:46)
- L304-316 _entry_ `float4 FSH_IfThenElse_NEQ_Grayscale(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_IfThenElse_NEQ_Grayscale` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_TwoInputs.cpp:47)

#### Global resources (textures / buffers / samplers) (4)

- L6 _resource_ `Texture2D LHS;`
- L7 _resource_ `Texture2D RHS;`
- L8 _resource_ `Texture2D Then;`
- L9 _resource_ `Texture2D Else;`

### `Plugins/TextureGraph/Shaders/Expressions/Expression_Invert.usf` (Other)

- lines: 34; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L3 `/Plugin/TextureGraph/SamplerStates.ush`

#### Macros (#define, 2)

- L9 `#define INVERT_INCLUDE_ALPHA 0` _[#if !defined(INVERT_INCLUDE_ALPHA)]_
- L13 `#define INVERT_CLAMP 0` _[#if !defined(INVERT_CLAMP)]_

#### Entry points (1)

- L16-33 _entry_ `float4 FSH_Invert(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_Invert` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Invert.cpp:11)

#### Global resources (textures / buffers / samplers) (1)

- L5 _resource_ `Texture2D SourceTexture;`

#### Global parameters (uniforms) (1)

- L6 _parameter_ `float MaxValue;`

### `Plugins/TextureGraph/Shaders/Expressions/Expression_Levels.usf` (Other)

- lines: 90; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L3 `/Plugin/TextureGraph/SamplerStates.ush`, L4 `/Plugin/TextureGraph/ShaderUtil.ush`

#### Macros (#define, 2)

- L8 `#define CONVERT_TO_GRAYSCALE 0` _[#if !defined(CONVERT_TO_GRAYSCALE)]_
- L12 `#define AUTO_LEVELS 0` _[#if !defined(AUTO_LEVELS)]_

#### Entry points (1)

- L45-88 _entry_ `float4 FSH_Levels(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_Levels` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Levels.cpp:12)

#### Global resources (textures / buffers / samplers) (2)

- L15 _resource_ `Texture2D SourceTexture;`
- L27 _resource_ `Texture2D Histogram;`

#### Global parameters (uniforms) (8)

- L16 _parameter_ `float LowValue;`
- L17 _parameter_ `float HighValue;`
- L18 _parameter_ `float MidValue;`
- L20 _parameter_ `float OutLow;`
- L21 _parameter_ `float OutHigh;`
- L22 _parameter_ `float OutputRange;`
- L24 _parameter_ `float DoAutoLevel;`
- L25 _parameter_ `float MidPercentage;`

#### Functions (1)

- L30-43 _function_ `float LevelsControlInputCurve(float Value, float LowInput, float HighInput, float MidInput)`

### `Plugins/TextureGraph/Shaders/Expressions/Expression_MaterialID.usf` (Other)

- lines: 151; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L3 `/Plugin/TextureGraph/SamplerStates.ush`, L4 `/Engine/Private/GammaCorrectionCommon.ush`

#### Entry points (1)

- L143-151 _entry_ `float4 FSH_MaterialIDMask(in float2 UvSource : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_MaterialIDMask` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_MaterialIDMask.cpp:7)

#### Global resources (textures / buffers / samplers) (1)

- L6 _resource_ `Texture2D MaterialIDTexture;`

#### Global parameters (uniforms) (3)

- L7 _parameter_ `float4 Buckets[375];`
- L8 _parameter_ `float4 ActiveColors[128];`
- L9 _parameter_ `int ActiveColorsCount;`

#### Functions (8)

- L13-19 _function_ `float3 SampleMaterialIDTex(float2 UV)`
- L20-29 _function_ `float3 Rgb2Hsv(float3 RgbColor)`
- L31-37 _function_ `float3 Hsv2Rgb(float3 HsvColor)`
- L39-45 _function_ `float3 GetBucket(float3 HSV, float3 Offset)`
- L47-53 _function_ `int GetBucketId(float3 HSV, float3 Offset)`
- L55-60 _function_ `float GetMaskAtOffset(float3 HSV, float3 Offset)`
- L62-82 _function_ `float GetMaskAtPoint(float2 UV, float Off)`
- L84-141 _function_ `float MatchAtPoint(float2 UV, out float3 RGB)`

### `Plugins/TextureGraph/Shaders/Expressions/Expression_Maths_OneInput.usf` (Other)

- lines: 128; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L3 `/Plugin/TextureGraph/SamplerStates.ush`

#### Entry points (20)

- L7-11 _entry_ `float4 FSH_Sin(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_Sin` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_OneInput.cpp:13)
- L13-17 _entry_ `float4 FSH_Cos(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_Cos` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_OneInput.cpp:14)
- L19-23 _entry_ `float4 FSH_Tan(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_Tan` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_OneInput.cpp:15)
- L25-29 _entry_ `float4 FSH_ASin(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_ASin` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_OneInput.cpp:16)
- L31-35 _entry_ `float4 FSH_ACos(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_ACos` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_OneInput.cpp:17)
- L37-41 _entry_ `float4 FSH_ATan(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_ATan` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_OneInput.cpp:18)
- L43-47 _entry_ `float4 FSH_ToRadians(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_ToRadians` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_OneInput.cpp:20)
- L49-53 _entry_ `float4 FSH_ToDegrees(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_ToDegrees` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_OneInput.cpp:21)
- L55-59 _entry_ `float4 FSH_Abs(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_Abs` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_OneInput.cpp:23)
- L61-65 _entry_ `float4 FSH_Sqrt(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_Sqrt` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_OneInput.cpp:24)
- L67-71 _entry_ `float4 FSH_Square(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_Square` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_OneInput.cpp:25)
- L73-77 _entry_ `float4 FSH_Cube(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_Cube` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_OneInput.cpp:26)
- L79-84 _entry_ `float4 FSH_Cbrt(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_Cbrt` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_OneInput.cpp:27)
- L86-90 _entry_ `float4 FSH_Exp(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_Exp` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_OneInput.cpp:28)
- L92-96 _entry_ `float4 FSH_Log2(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_Log2` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_OneInput.cpp:29)
- L98-102 _entry_ `float4 FSH_Log10(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_Log10` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_OneInput.cpp:30)
- L104-108 _entry_ `float4 FSH_Log(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_Log` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_OneInput.cpp:31)
- L110-114 _entry_ `float4 FSH_Floor(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_Floor` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_OneInput.cpp:32)
- L116-120 _entry_ `float4 FSH_Ceil(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_Ceil` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_OneInput.cpp:33)
- L122-126 _entry_ `float4 FSH_Round(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_Round` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_OneInput.cpp:34)

#### Global resources (textures / buffers / samplers) (1)

- L5 _resource_ `Texture2D Input;`

### `Plugins/TextureGraph/Shaders/Expressions/Expression_Maths_ThreeInputs.usf` (Other)

- lines: 24; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L3 `/Plugin/TextureGraph/SamplerStates.ush`

#### Entry points (2)

- L9-15 _entry_ `float4 FSH_Mad(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_Mad` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_ThreeInputs.cpp:11)
- L17-23 _entry_ `float4 FSH_Lerp(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_Lerp` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_ThreeInputs.cpp:12)

#### Global resources (textures / buffers / samplers) (3)

- L5 _resource_ `Texture2D Operand1;`
- L6 _resource_ `Texture2D Operand2;`
- L7 _resource_ `Texture2D Operand3;`

### `Plugins/TextureGraph/Shaders/Expressions/Expression_Maths_TwoInputs.usf` (Other)

- lines: 66; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L3 `/Plugin/TextureGraph/SamplerStates.ush`

#### Entry points (8)

- L8-13 _entry_ `float4 FSH_Multiply(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_Multiply` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_TwoInputs.cpp:13)
- L15-20 _entry_ `float4 FSH_Divide(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_Divide` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_TwoInputs.cpp:14)
- L22-27 _entry_ `float4 FSH_Add(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_Add` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_TwoInputs.cpp:15)
- L29-34 _entry_ `float4 FSH_Subtract(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_Subtract` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_TwoInputs.cpp:16)
- L36-42 _entry_ `float4 FSH_Dot(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_Dot` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_TwoInputs.cpp:18)
- L44-50 _entry_ `float4 FSH_Cross(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_Cross` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_TwoInputs.cpp:19)
- L52-57 _entry_ `float4 FSH_Pow(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_Pow` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_TwoInputs.cpp:20)
- L59-64 _entry_ `float4 FSH_Step(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_Step` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Maths_TwoInputs.cpp:21)

#### Global resources (textures / buffers / samplers) (2)

- L5 _resource_ `Texture2D Operand1;`
- L6 _resource_ `Texture2D Operand2;`

### `Plugins/TextureGraph/Shaders/Expressions/Expression_MinMax.usf` (Other)

- lines: 24; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L3 `/Plugin/TextureGraph/SamplerStates.ush`

#### Entry points (2)

- L8-14 _entry_ `float4 FSH_Min(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_Min` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Clamp.cpp:13)
- L16-22 _entry_ `float4 FSH_Max(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_Max` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Clamp.cpp:14)

#### Global resources (textures / buffers / samplers) (2)

- L5 _resource_ `Texture2D Input1;`
- L6 _resource_ `Texture2D Input2;`

### `Plugins/TextureGraph/Shaders/Expressions/Expression_NormalFromHeightMap.usf` (Other)

- lines: 32; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L3 `/Plugin/TextureGraph/SamplerStates.ush`, L4 `/Plugin/TextureGraph/ShaderUtil.ush`, L5 `/Plugin/TextureGraph/TileInfo.ush`

#### Entry points (1)

- L11-31 _entry_ `float4 FSH_NormalFromHeightMap(float2 UV : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_NormalFromHeightMap` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Conversions.cpp:9)

#### Global resources (textures / buffers / samplers) (1)

- L7 _resource_ `Texture2D SourceTexture;`

#### Global parameters (uniforms) (2)

- L8 _parameter_ `float Strength;`
- L9 _parameter_ `float Offset;`

### `Plugins/TextureGraph/Shaders/Expressions/Expression_Premult.usf` (Other)

- lines: 13; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L3 `/Plugin/TextureGraph/SamplerStates.ush`, L4 `/Plugin/TextureGraph/ShaderUtil.ush`

#### Entry points (1)

- L8-12 _entry_ `float4 FSH_Premult(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_Premult` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Color.cpp:17)

#### Global resources (textures / buffers / samplers) (1)

- L6 _resource_ `Texture2D Input;`

### `Plugins/TextureGraph/Shaders/Expressions/Expression_RadialBlur.usf` (Other)

- lines: 31; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L3 `/Plugin/TextureGraph/SamplerStates.ush`, L4 `/Plugin/TextureGraph/TileInfo.ush`

#### Entry points (1)

- L14-30 _entry_ `float4 FSH_RadialBlur(float2 UV : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_RadialBlur` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Blur.cpp:10)

#### Global resources (textures / buffers / samplers) (1)

- L7 _resource_ `Texture2D SourceTexture;`

#### Global parameters (uniforms) (5)

- L8 _parameter_ `int Radius;`
- L9 _parameter_ `float Strength;`
- L10 _parameter_ `float CenterX;`
- L11 _parameter_ `float CenterY;`
- L12 _parameter_ `float Samples;`

### `Plugins/TextureGraph/Shaders/Expressions/Expression_Shape.usf` (Other)

- lines: 105; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L3 `/Plugin/TextureGraph/SamplerStates.ush`, L4 `/Plugin/TextureGraph/TileInfo.ush`, L5 `/Plugin/TextureGraph/ShapeMask.ush`

#### Macros (#define, 34)

- L8 `#define SHAPE_CIRCLE 0`
- L9 `#define SHAPE_SEGMENT 1`
- L10 `#define SHAPE_RECT 2`
- L11 `#define SHAPE_TRIANGLE 3`
- L12 `#define SHAPE_ELLIPSE 4`
- L13 `#define SHAPE_PENTAGON 5`
- L14 `#define SHAPE_HEXAGON 6`
- L15 `#define SHAPE_REGULARPOLYGON_7 7`
- L16 `#define SHAPE_REGULARPOLYGON_8 8`
- L17 `#define SHAPE_REGULARPOLYGON_9 9`
- L18 `#define SHAPE_REGULARPOLYGON_10 10`
- L19 `#define SHAPE_REGULARPOLYGON_11 11`
- L20 `#define SHAPE_REGULARPOLYGON_12 12`
- L21 `#define SHAPE_REGULARPOLYGON_13 13`
- L22 `#define SHAPE_REGULARPOLYGON_14 14`
- L23 `#define SHAPE_REGULARPOLYGON_15 15`
- L24 `#define SHAPE_REGULARPOLYGON_16 16`
- L25 `#define SHAPE_REGULARPOLYGON_17 17`
- L26 `#define SHAPE_REGULARPOLYGON_18 18`
- L27 `#define SHAPE_REGULARPOLYGON_19 19`
- L28 `#define SHAPE_REGULARPOLYGON_20 20`
- L29 `#define SHAPE_REGULARPOLYGON_21 21`
- L30 `#define SHAPE_REGULARPOLYGON_22 22`
- L31 `#define SHAPE_REGULARPOLYGON_23 23`
- L32 `#define SHAPE_REGULARPOLYGON_24 24`
- L33 `#define SHAPE_REGULARPOLYGON_25 25`
- L34 `#define SHAPE_REGULARPOLYGON_26 26`
- L35 `#define SHAPE_REGULARPOLYGON_27 27`
- L36 `#define SHAPE_REGULARPOLYGON_28 28`
- L37 `#define SHAPE_REGULARPOLYGON_29 29`
- L38 `#define SHAPE_REGULARPOLYGON_30 30`
- L39 `#define SHAPE_REGULARPOLYGON_31 31`
- L40 `#define SHAPE_REGULARPOLYGON_32 32`
- L43 `#define SHAPE_TYPE SHAPE_CIRCLE` _[#if !defined(SHAPE_TYPE)]_

#### Entry points (1)

- L60-104 _entry_ `float4 FSH_DrawShapeMask(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_ShapeMask` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Mask/T_ShapeMask.cpp:15)

#### Global parameters (uniforms) (8)

- L46 _parameter_ `float RotateX;`
- L47 _parameter_ `float RotateY;`
- L49 _parameter_ `float ParamX;`
- L50 _parameter_ `float ParamY;`
- L52 _parameter_ `float Rounding;`
- L54 _parameter_ `float BevelWidth;`
- L55 _parameter_ `float BevelCurve;`
- L57 _parameter_ `float BlendSDF;`

### `Plugins/TextureGraph/Shaders/Expressions/Expression_Threshold.usf` (Other)

- lines: 19; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L3 `/Plugin/TextureGraph/SamplerStates.ush`, L4 `/Plugin/TextureGraph/ShaderUtil.ush`

#### Entry points (1)

- L9-17 _entry_ `float4 FSH_Threshold(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_Threshold` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Color.cpp:12)

#### Global resources (textures / buffers / samplers) (1)

- L6 _resource_ `Texture2D Input;`

#### Global parameters (uniforms) (1)

- L7 _parameter_ `float Threshold;`

### `Plugins/TextureGraph/Shaders/Expressions/Expression_Transform.usf` (Other)

- lines: 161; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L3 `/Plugin/TextureGraph/SamplerStates.ush`, L4 `/Plugin/TextureGraph/TileInfo.ush`, L5 `/Plugin/TextureGraph/Paint.ush`

#### Entry points (1)

- L55-160 _entry_ `float4 FSH_TransformBlit(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_TransformBlit` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Transform.cpp:13)

#### Global resources (textures / buffers / samplers) (1)

- L7 _resource_ `Texture2D SourceTexture;`

#### Global parameters (uniforms) (24)

- L8 _parameter_ `float4 FillColor;`
- L10 _parameter_ `float CoverageX;`
- L11 _parameter_ `float CoverageY;`
- L13 _parameter_ `float TranslationX;`
- L14 _parameter_ `float TranslationY;`
- L16 _parameter_ `float PivotX;`
- L17 _parameter_ `float PivotY;`
- L19 _parameter_ `float RotationX;`
- L20 _parameter_ `float RotationY;`
- L22 _parameter_ `float ScaleX;`
- L23 _parameter_ `float ScaleY;`
- L25 _parameter_ `float FilterMode;`
- L26 _parameter_ `float MirrorX;`
- L27 _parameter_ `float MirrorY;`
- L29 _parameter_ `float StaggerX;`
- L30 _parameter_ `float StaggerY;`
- L32 _parameter_ `float StrideX;`
- L33 _parameter_ `float StrideY;`
- L35 _parameter_ `float Zoom;`
- L36 _parameter_ `float StretchToFit;`
- L37 _parameter_ `float SpacingX;`
- L38 _parameter_ `float SpacingY;`
- L40 _parameter_ `float CellScaling;`
- L43 _parameter_ `float BlendDebugGrid;`

#### Functions (2)

- L45-49 _function_ `float MaskBox(in float2 uv, in float2 minValue, in float2 maxValue)`
- L50-53 _function_ `float MaskBox(in float2 uv, in float minValue, in float maxValue)`

### `Plugins/TextureGraph/Shaders/Expressions/Expression_Warp.usf` (Other)

- lines: 80; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L3 `/Plugin/TextureGraph/SamplerStates.ush`, L4 `/Plugin/TextureGraph/TileInfo.ush`

#### Macros (#define, 2)

- L13 `#define HALF_PI 1.5707963267948966`
- L14 `#define QUARTER_PI HALF_PI * 0.5`

#### Entry points (3)

- L26-45 _entry_ `float4 FSH_DirectionalWarp(float2 InUV_ : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_DirectionalWarp` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Filter.cpp:11)
- L47-66 _entry_ `float4 FSH_NormalWarp(float2 InUV_ : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_NormalWarp` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Filter.cpp:12)
- L68-79 _entry_ `float4 FSH_SineWarp(float2 InUV_ : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_SineWarp` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_Filter.cpp:13)

#### Global resources (textures / buffers / samplers) (2)

- L6 _resource_ `Texture2D SourceTexture;`
- L7 _resource_ `Texture2D Mask;`

#### Global parameters (uniforms) (4)

- L8 _parameter_ `float Intensity;`
- L9 _parameter_ `float AngleRad;`
- L10 _parameter_ `float PhaseU;`
- L11 _parameter_ `float PhaseV;`

#### Functions (1)

- L16-24 _function_ `float2 SineWave(float2 p, float tx, float ty)`
