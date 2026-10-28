# Shaders / Plugins/Compositing/CompositeCore/Shaders/Private

- files: 4; lines: 1014
- record kinds: cpp_binding=4, define=41, entry=3, function=40, groupshared=1, include=9, macro_call=7, parameter=15, resource=9, static_const=2

### `Plugins/Compositing/CompositeCore/Shaders/Private/CompositeCoreBlending.ush` (Private)

- lines: 236; parse: all-branches

#### Functions (18)

- L4-7 _function_ `float CoverageCombined(float As, float Ad)` — Combined alpha coverage
- L10-13 _function_ `float CoverageSrcOnly(float As, float Ad)` — Alpha coverage of source
- L16-19 _function_ `float CoverageDstOnly(float As, float Ad)` — Alpha coverage of destination
- L22-29 _function_ `float3 CoverageWeights(float As, float Ad)` — Coverage weights: combined, source only, destination only.
- L32-35 _function_ `float3 Unpremult(float4 Color)` — Obtain the base unpremultiplied color
- L38-49 _function_ `float4 ScreenBlend( float4 Src, float4 Dst)` — Screen alpha blend
- L52-63 _function_ `float4 OverlayBlend(float4 Src, float4 Dst)` — Overlay alpha blend
- L66-77 _function_ `float4 DarkenBlend(float4 Src, float4 Dst)` — Darken alpha blend
- L80-91 _function_ `float4 LightenBlend(float4 Src, float4 Dst)` — Lighten alpha blend
- L93-107 _function_ `float ColorDodgeBlend(float Src, float Dst)`
- L110-125 _function_ `float4 ColorDodgeBlend(float4 Src, float4 Dst)` — Color dodge alpha blend
- L127-141 _function_ `float ColorBurnBlend(float Src, float Dst)`
- L144-159 _function_ `float4 ColorBurnBlend(float4 Src, float4 Dst)` — Color burn alpha blend
- L162-173 _function_ `float4 HardLightBlend(float4 Src, float4 Dst)` — Hard light alpha blend
- L175-189 _function_ `float SoftLightBlend(float Src, float Dst)`
- L192-207 _function_ `float4 SoftLightBlend(float4 Src, float4 Dst)` — Soft light alpha blend
- L210-221 _function_ `float4 DifferenceBlend(float4 Src, float4 Dst)` — Difference alpha blend
- L224-235 _function_ `float4 ExclusionBlend(float4 Src, float4 Dst)` — Exclusion alpha blend

### `Plugins/Compositing/CompositeCore/Shaders/Private/CompositeCoreDilate.usf` (Private)

- lines: 403; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `/Engine/Private/ScreenPass.ush`

#### Macros (#define, 10)

- L11 `#define MORPHOLOGY_ERODE 0` _[#if !defined(MORPHOLOGY_ERODE)]_
- L17 `#define CHANNELS_MODE_ALPHA_ONLY 0`
- L18 `#define CHANNELS_MODE_GENERAL 1`
- L20 `#define DILATION_CHANNELS_MODE CHANNELS_MODE_ALPHA_ONLY` _[#if !defined(DILATION_CHANNELS_MODE)]_
- L29 `#define DILATION_USE_THRESHOLD 1` _[#if !defined(DILATION_USE_THRESHOLD)]_
- L32 `#define KERNEL_COUNT ((1 + 2 * DILATION_SIZE) * (1 + 2 * DILATION_SIZE) - 1)`
- L35 `#define LDS_TILE_BORDER_SIZE DILATION_SIZE`
- L38 `#define LDS_TILE_WIDTH (TILE_SIZE + 2 * LDS_TILE_BORDER_SIZE)`
- L41 `#define LDS_ARRAY_SIZE (LDS_TILE_WIDTH * LDS_TILE_WIDTH)`
- L43 `#define THREADGROUP_TOTAL (TILE_SIZE * TILE_SIZE)`

#### Entry points (1)

- L304-402 _entry_ `[numthreads(TILE_SIZE, TILE_SIZE, 1)] void MainCS( uint2 GroupId : SV_GroupID, uint2 GroupThreadId : SV_GroupThreadID, uint GroupThreadIndex : SV_GroupIndex, uint2 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FCompositeCoreDilateShader` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Compositing/CompositeCore/Source/CompositeCore/Private/Passes/CompositeCorePassDilate.cpp:40) — C++: `FCompositePassDilationShader` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Compositing/Composite/Source/Composite/Private/Passes/CompositePassDilation.cpp:65)

#### Global resources (textures / buffers / samplers) (3)

- L45 _resource_ `Texture2D Input_Texture;`
- L46 _resource_ `SamplerState Input_Sampler;`
- L49 _resource_ `RWTexture2D<float4> RWOutputTexture;`

#### Global parameters (uniforms) (5)

- L50 _parameter_ `uint bInvertedAlpha;`
- L51 _parameter_ `uint bOpacifyOutput;`
- L54 _parameter_ `float AlphaThreshold;` — Opacity at or below this threshold is treated as fully transparent for morphological operations. Read by the thresholded paths and by the Opacify step when bOpacifyOutput is set.
- L56 _parameter_ `uint ChannelMask;` — Bitmask selecting which channels the GENERAL path operates on (R=0x1, G=0x2, B=0x4, A=0x8).
- L59 _parameter_ `uint bCarryRGBWithAlpha;` — When true and Alpha is in the mask, the alpha-winning neighbor's RGB is copied into color channels that are NOT in the mask. Holdout defaults it to 0; the user pass defaults it to 1.

#### groupshared (1)

- L109 _groupshared_ `groupshared float4 SharedColor[LDS_ARRAY_SIZE];`

#### static const (2)

- L70-79 _static_const_ `static const int2 kOffsets[KERNEL_COUNT] = { int2(-1, 0), int2( 1, 0), int2( 0, 1), int2( 0, -1), int2(-1, 1), int2( 1, 1), int2( 1, -1), int2(-1, -1), };` _[#if DILATION_SIZE == 1]_
- L81-106 _static_const_ `static const int2 kOffsets[24] = { int2(-1, 0), int2( 1, 0), int2( 0, 1), int2( 0, -1), int2(-1, 1), int2( 1, 1), int2( 1, -1), int2(-1, -1), int2(-2, 0), int2( 2, 0), int2( 0, -2), int2( 0, 2), int2(-2, -1), int2(-1, -2), int2( 1, -2), int2( 2, -1), int2( 2, 1), int2( 1, 2), int2(-1, 2), int2(-2, 1), int2(-2, -2), int2( 2, -2), int2( 2, 2), int2(-2, 2), };` _[#if !(DILATION_SIZE == 1) && DILATION_SIZE == 2]_

#### Functions (9)

- L64-67 _function_ `float InvertAlpha(float InAlpha, uint bInvert)` — Normalize or restore alpha between inverted UE convention (A=0 opaque, A=1 transparent) and standard opacity (0 transparent, 1 opaque). Self-inverse: apply twice to round-trip. Defined inline - CompositeCommon.ush lives in the Composite plugin and is not accessible here.
- L112-116 _function_ `uint GetTileArrayIndexFromPixelOffset(in uint2 GroupThreadId, in int2 PixelOffset)` — Get the index within the LDS array.
- L118-121 _function_ `float4 SampleCachedColors(in uint2 GroupThreadId, int2 PixelOffset = int2(0,0))`
- L123-126 _function_ `float SafeRcp(float x)`
- L129-133 _function_ `float4 Opacify(float4 InColor)` — Unpremultiply and force full opacity. Operates in standard opacity space (a = 1 = opaque).
- L146-181 _function_ `float4 AlphaCoupledThresholdedStep(float4 TexelColor, uint2 GroupThreadId)` — Thresholded, alpha-coupled step: when the threshold is crossed, copy the *neighbor's full* unpremultiplied RGBA into TexelColor - this is what carries fringe colour outward with an alpha dilate in today's premultiplied workflow. Used by ALPHA_ONLY and by GENERAL when the A bit of ChannelMask is set. _[#if DILATION_SIZE > 0]_
- L184-216 _function_ `float AlphaOnlyThresholdedStep(float SelfAlpha, uint2 GroupThreadId)` — Thresholded step that only modifies alpha (no RGB copy). Used when bCarryRGBWithAlpha is off. _[#if DILATION_SIZE > 0]_
- L220-252 _function_ `float PerChannelThresholdedStep(float SelfValue, uint2 GroupThreadId, uint Channel)` — Per-channel thresholded step for a single R/G/B channel (Channel ∈ {0,1,2}). No RGB coupling: only the given channel's value is modified. _[#if DILATION_SIZE > 0]_
- L258-300 _function_ `float4 MinMaxKernelGeneral(float4 TexelColor, uint2 GroupThreadId)` — True min/max over the kernel for any selected channel (graded output). TexelColor.a must already be in standard opacity space; kernel neighbors are normalized inline. When Alpha is selected and bCarryRGBWithAlpha is set, the alpha-winning neighbor's RGB is copied into color channels that are NOT selected in the mask (so mattes expand visibly). _[#if DILATION_SIZE > 0]_

#### Top-level macro invocations (2)

- L47 _macro_call_ `SCREEN_PASS_TEXTURE_VIEWPORT(Input)`
- L48 _macro_call_ `SCREEN_PASS_TEXTURE_VIEWPORT(Output)`

### `Plugins/Compositing/CompositeCore/Shaders/Private/CompositeCoreDisplayTransform.usf` (Private)

- lines: 64; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `/Engine/Private/ScreenPass.ush`

#### Macros (#define, 2)

- L14 `#define VERSION 0`
- L15 `#define R_K 1.0`

#### Entry points (1)

- L41-63 _entry_ `void MainPS( float4 SvPosition : SV_POSITION, out float4 OutColor : SV_Target0 )` — stage: **pixel (from C++ binding)** — C++: `FCompositeCoreDisplayTransformShader` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Compositing/CompositeCore/Source/CompositeCore/Private/Passes/CompositeCorePassFXAAProxy.cpp:31)

#### Global resources (textures / buffers / samplers) (2)

- L7 _resource_ `Texture2D Input_Texture;`
- L8 _resource_ `SamplerState Input_Sampler;`

#### Global parameters (uniforms) (4)

- L6 _parameter_ `FScreenTransform SvPositionToInputTextureUV;`
- L10 _parameter_ `uint bIsForward;`
- L11 _parameter_ `float Gamma;`
- L12 _parameter_ `float InvGamma;`

#### Functions (4)

- L18-21 _function_ `float3 Reinhard(float3 ColorHDR, float K = R_K)` — Simple Reinhard tone curve
- L24-27 _function_ `float3 InvReinhard(float3 ColorSDR, float K = R_K)` — Inverse simple Reinhard tone curve
- L30-33 _function_ `float3 GammaEncode(float3 Color)` — Gamma encode (faster approximation of sRGB)
- L36-39 _function_ `float3 GammaDecode(float3 Color)` — Gamma decode transfer function (faster approximation of sRGB)

### `Plugins/Compositing/CompositeCore/Shaders/Private/CompositeCoreMerge.usf` (Private)

- lines: 311; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `/Engine/Private/GammaCorrectionCommon.ush`, L5 `/Engine/Private/ScreenPass.ush`, L6 `/Engine/Private/LensDistortion.ush`, L8 `CompositeCoreBlending.ush`

#### Macros (#define, 29)

- L10 `#define ESourceEncoding_None 0`
- L11 `#define ESourceEncoding_Gamma 1`
- L12 `#define ESourceEncoding_sRGB 2`
- L14 `#define EDistortionUV_None 0`
- L15 `#define EDistortionUV_Distorted 1`
- L16 `#define EDistortionUV_Undistorted 2`
- L18 `#define ECompositeCoreMergeOp_None 0`
- L19 `#define ECompositeCoreMergeOp_Over 1`
- L20 `#define ECompositeCoreMergeOp_Under 2`
- L21 `#define ECompositeCoreMergeOp_Add 3`
- L22 `#define ECompositeCoreMergeOp_Subtract 4`
- L23 `#define ECompositeCoreMergeOp_Mul 5`
- L24 `#define ECompositeCoreMergeOp_Div 6`
- L25 `#define ECompositeCoreMergeOp_Min 7`
- L26 `#define ECompositeCoreMergeOp_Max 8`
- L27 `#define ECompositeCoreMergeOp_In 9`
- L28 `#define ECompositeCoreMergeOp_Mask 10`
- L30 `#define ECompositeCoreMergeOp_Screen 11`
- L31 `#define ECompositeCoreMergeOp_Overlay 12`
- L32 `#define ECompositeCoreMergeOp_Darken 13`
- L33 `#define ECompositeCoreMergeOp_Lighten 14`
- L34 `#define ECompositeCoreMergeOp_ColorDodge 15`
- L35 `#define ECompositeCoreMergeOp_ColorBurn 16`
- L36 `#define ECompositeCoreMergeOp_HardLight 17`
- L37 `#define ECompositeCoreMergeOp_SoftLight 18`
- L38 `#define ECompositeCoreMergeOp_Difference 19`
- L39 `#define ECompositeCoreMergeOp_Exclusion 20`
- L45 `#define INPUT_PASS_TEXTURE_MEMBER(StructName, MemberType, MemberName) MemberType StructName##_##MemberName;`
- L47 `#define INPUT_PASS_TEXTURE(StructName) INPUT_PASS_TEXTURE_MEMBER(StructName, Texture2D, Texture) INPUT_PASS_TEXTURE_MEMBER(StructName, SamplerState, Sampler) INPUT_PASS_TEXTURE_MEMBER(StructName, uint, bInvertedAlpha) INPUT_PASS_TEXTURE_ME ...` (7 lines)

#### Entry points (1)

- L161-310 _entry_ `void MainPS( float4 SvPosition : SV_POSITION, out float4 OutColor : SV_Target0 )` — stage: **pixel (from C++ binding)** — C++: `FCompositeCoreMergeShader` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Compositing/CompositeCore/Source/CompositeCore/Private/Passes/CompositeCorePassMergeProxy.cpp:66)

#### Global resources (textures / buffers / samplers) (4)

- L59 _resource_ `Texture2D<float2> DistortingDisplacementTexture;`
- L60 _resource_ `SamplerState DistortingDisplacementSampler;`
- L61 _resource_ `Texture2D<float2> UndistortingDisplacementTexture;`
- L62 _resource_ `SamplerState UndistortingDisplacementSampler;`

#### Global parameters (uniforms) (6)

- L64 _parameter_ `float2 DisplayGamma;` — DisplayGamma, 1/DisplayGamma
- L65 _parameter_ `uint MergeOp;`
- L66 _parameter_ `uint OutputEncoding;`
- L67 _parameter_ `uint bFlags;` — 0: bInvertedAlphaOutput
- L68 _parameter_ `uint bBlendInDisplaySpace;`
- L69 _parameter_ `uint bLuminanceOnly;` — Divide-only: when set, the matte's RGB uses a single luminance ratio uniformly across all channels.

#### Functions (9)

- L71-87 _function_ `float3 Decode(float3 InColor, uint InEncoding)`
- L89-104 _function_ `float3 Encode(float3 InColor, uint InEncoding)`
- L106-121 _function_ `float2 CalcInputUVs(float2 ViewportUV, float2 ViewportSize, float2 ViewportMin, float2 ExtentInverse, uint DistortionUVType)`
- L123-126 _function_ `float GetOpacity(float InAlpha, uint bInvertedAlpha)`
- L128-131 _function_ `float SafeDiv(float A, float B)`
- L133-141 _function_ `float4 SafeDiv(float4 A, float4 B)`
- L144-147 _function_ `float4 BiasedDiv(float4 A, float4 B, float Eps)` — Biased ratio: pulls (A + eps) / (B + eps) toward 1.0 in low-signal regions to suppress speckle.
- L150-153 _function_ `float3 EncodeForDisplayBlend(float4 Color)` — Encode RGB to sRGB for display-space blending; un-premultiplies first so the operand at blend is encode(straight)*alpha rather than encode(straight*alpha) - sRGB encoding is non-linear so the two diverge for fractional alpha. Inputs are expected linear-premult (engine convention; masking-pass output for Ultimatte content is converted upstream via the Ultimatte Blend option on the masking pass).
- L156-159 _function_ `float3 DecodeFromDisplayBlend(float4 Color)` — Inverse of EncodeForDisplayBlend: decode the post-blend display-space result back to linear-premult.

#### Top-level macro invocations (5)

- L41 _macro_call_ `SCREEN_PASS_TEXTURE_VIEWPORT(Input0)`
- L42 _macro_call_ `SCREEN_PASS_TEXTURE_VIEWPORT(Input1)`
- L43 _macro_call_ `SCREEN_PASS_TEXTURE_VIEWPORT(Output)`
- L56 _macro_call_ `INPUT_PASS_TEXTURE(Tex0)`
- L57 _macro_call_ `INPUT_PASS_TEXTURE(Tex1)`
