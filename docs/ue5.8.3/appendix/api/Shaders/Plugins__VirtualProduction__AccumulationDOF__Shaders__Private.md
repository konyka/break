# Shaders / Plugins/VirtualProduction/AccumulationDOF/Shaders/Private

- files: 6; lines: 1161
- record kinds: cpp_binding=11, define=35, entry=11, function=12, include=7, parameter=50, resource=18, static_const=3

### `Plugins/VirtualProduction/AccumulationDOF/Shaders/Private/AccumulationDOFAccumulate.usf` (Private)

- lines: 543; parse: all-branches
- includes: L22 `/Engine/Public/Platform.ush`

#### Macros (#define, 4)

- L82 `#define BOKEH_SHAPE_CIRCLE 0`
- L83 `#define BOKEH_SHAPE_STRAIGHT_BLADES 1`
- L84 `#define BOKEH_SHAPE_ROUNDED_BLADES 2`
- L88 `#define PI 3.14159265358979323846` _[#if !defined(PI)]_

#### Entry points (2)

- L405-414 _entry_ `void MainVS( in uint VertexId : SV_VertexID, out float4 OutPosition : SV_POSITION, out float2 OutUV : TEXCOORD0 )` — stage: **vertex (from C++ binding)** — C++: `FAccumulationDOFAccumulateVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Plugins/VirtualProduction/AccumulationDOF/Source/AccumulationDOF/Private/Shaders/AccumulationDOFShaders.cpp:20)
- L416-542 _entry_ `void MainPS( in float4 SvPosition : SV_POSITION, in float2 UV : TEXCOORD0, out float4 OutColor : SV_Target0 )` — stage: **pixel (from C++ binding)** — C++: `FAccumulationDOFAccumulatePS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/VirtualProduction/AccumulationDOF/Source/AccumulationDOF/Private/Shaders/AccumulationDOFShaders.cpp:21)

#### Global resources (textures / buffers / samplers) (6)

- L24 _resource_ `Texture2D PrevAccumTexture;`
- L25 _resource_ `SamplerState PrevAccumSampler;`
- L27 _resource_ `Texture2D SampleTexture;`
- L28 _resource_ `SamplerState SampleSampler;`
- L30 _resource_ `Texture2D BokehTexture;`
- L31 _resource_ `SamplerState BokehSampler;`

#### Global parameters (uniforms) (29)

- L33 _parameter_ `float2 ApertureOffsetCm;`
- L34 _parameter_ `float ApertureRadiusCm;`
- L35 _parameter_ `int BokehWeightChannel;` — 0 = Alpha, 1 = Luminance
- L36 _parameter_ `int BokehUseTint;`
- L37 _parameter_ `float BokehTintStrength;`
- L38 _parameter_ `int BokehEnabled;`
- L41 _parameter_ `float SqueezeFactor;` — Anamorphic squeeze factor for bokeh
- L44 _parameter_ `float3 SpectralWeight;` — Spectral weight for axial chromatic aberration (1,1,1 : none)
- L47 _parameter_ `float BokehEdgeSoftness;` — Soft falloff at aperture edge (0: hard edge, 1: very soft)
- L50 _parameter_ `float Petzval;` — Petzval field curvature parameters. See PathTracingCore.ush for usage reference.
- L51 _parameter_ `float PetzvalFalloffPower;`
- L52 _parameter_ `float2 PetzvalExclusionBoxExtents;`
- L53 _parameter_ `float PetzvalExclusionBoxRadius;`
- L56 _parameter_ `float BarrelRadiusCm;` — Cat's eye bokeh from occlusion by the lens barrel
- L57 _parameter_ `float BarrelLengthCm;`
- L58 _parameter_ `float2 SensorHalfSizeCm;`
- L59 _parameter_ `float FocalLengthCm;`
- L60 _parameter_ `float FocusDistanceCm;`
- L63 _parameter_ `int DiaphragmBladeCount;` — Diaphragm blade parameters
- L64 _parameter_ `float DiaphragmRotationRad;`
- L65 _parameter_ `int BokehShape;` — 0:Circle, 1:StraightBlades, 2:RoundedBlades
- L66 _parameter_ `float CocRadiusToCircumscribedRadius;` — Scale factor for circumscribed radius
- L67 _parameter_ `float CocRadiusToIncircleRadius;` — Scale factor for incircle radius
- L68 _parameter_ `float DiaphragmBladeRadius;` — Blade arc radius
- L69 _parameter_ `float DiaphragmBladeCenterOffset;` — Blade arc center offset
- L72 _parameter_ `float AntiAliasingWeight;` — AA reconstruction weight
- L75 _parameter_ `float2 SubpixelOffset;` — Subpixel splatting 0-1
- L76 _parameter_ `float2 TexelSize;`
- L79 _parameter_ `float ComaStrength;` — Coma aberration strength (Seidel W131)

#### Functions (6)

- L94-97 _function_ `float LuminanceSRGB(float3 InColor)` — Compute luminance from RGB using Rec. 709 coefficients. Based on CompositeColorKeyerCommon.ush
- L104-141 _function_ `float ComputeCocRadiusToBokehEdgeFactor(float PixelAngle)` — Compute scaling factor that needs to be applied to radial coordinate (R=1, PixelAngle)'s radius R, to have the point projected onto the bokeh's edge with the bokeh area remaining equal to PI. Based on DOFBokehLUT.usf ComputeCocRadiusToBokehEdgeFactor()
- L148-198 _function_ `float ComputeBladeMask(float2 DiskPos, float EdgeSoftness)` — Compute blade-shaped mask with edge softness @param DiskPos normalized disk position [-1,1] after Petzval and squeeze distortion @return 1.0 inside blade boundary (with soft falloff), 0.0 outside
- L210-255 _function_ `float2 ApplyPetzvalDistortion(float2 BokehCenterUV, float2 SamplePos)` — Apply Petzval field curvature distortion to bokeh shape This is the inverse of PathTracingCore.ush ApplyPetzval() because: - Path tracer compresses lens sample positions, i.e. narrower bokeh in that axis - We sample a bokeh texture, so we need to expand the UV to get narrower result @param BokehCenterUV Screen UV [0,1] of the pixel being shaded @param SamplePos Normalized disk position [-1,1] of the aperture sample @return Distorted disk position [-1,1] stretched radially or tangentially based on screen position
- L269-360 _function_ `float ComputeBarrelOcclusion(float2 BokehCenterUV, float2 ApertureOffsetCm, float ApertureRadiusCm, float EdgeSoftness)` — Compute barrel occlusion for cat's eye bokeh effect with soft edges When EdgeSoftness > 0, applies a smooth falloff at the barrel boundary based on how close the ray passes to the barrel wall, creating smoother cat's eye edges. @param BokehCenterUV    - Screen UV [0,1] of the pixel being shaded @param ApertureOffsetCm - Aperture sample offset from optical axis in cm @param ApertureRadiusCm - Aperture radius in cm (used for soft edge scaling) @param EdgeSoftness     - Softness factor for barrel boundary (0 = hard edge, 1 = very soft) @return 1.0 if not occluded, soft gradient 0..1 at edge, 0.0 
- L370-402 _function_ `float2 ComputeComaShift(float2 ScreenUV, float2 NormPupil)` — Compute coma aberration UV shift (Seidel W131) @param ScreenUV  Screen UV [0,1] of the pixel @param NormPupil Normalized aperture position [-1,1] @return UV offset to apply when sampling

### `Plugins/VirtualProduction/AccumulationDOF/Shaders/Private/AccumulationDOFCopy.usf` (Private)

- lines: 54; parse: all-branches
- includes: L8 `/Engine/Public/Platform.ush`

#### Entry points (1)

- L29-53 _entry_ `void MainPS( in float4 SvPosition : SV_POSITION, in float2 UV : TEXCOORD0, out float4 OutColor : SV_Target0 )` — stage: **pixel (from C++ binding)** — C++: `FAccumulationDOFCopyPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/VirtualProduction/AccumulationDOF/Source/AccumulationDOF/Private/Shaders/AccumulationDOFShaders.cpp:24)

#### Global resources (textures / buffers / samplers) (2)

- L11 _resource_ `Texture2D SourceTexture;`
- L12 _resource_ `SamplerState SourceSampler;`

#### Global parameters (uniforms) (4)

- L15 _parameter_ `uint FrameCounter;` — Dithering parameters for f32->f16 format conversion
- L16 _parameter_ `float DitherStrength;`
- L19 _parameter_ `float2 SourceUVMin;` — Source UV crop region (for overscan cropping)
- L20 _parameter_ `float2 SourceUVMax;`

#### Functions (1)

- L23-27 _function_ `float InterleavedGradientNoise(float2 PixelPos, uint FrameId)` — Interleaved gradient noise (IGN) for temporal dithering

### `Plugins/VirtualProduction/AccumulationDOF/Shaders/Private/AccumulationDOFInject.usf` (Private)

- lines: 252; parse: all-branches
- includes: L12 `/Engine/Public/Platform.ush`, L13 `/Engine/Private/MiniFontCommon.ush`

#### Macros (#define, 28)

- L18 `#define _LPAREN_ 40`
- L19 `#define _RPAREN_ 41`
- L21 `#define _a_ 97`
- L22 `#define _b_ 98`
- L23 `#define _c_ 99`
- L24 `#define _d_ 100`
- L25 `#define _e_ 101`
- L26 `#define _f_ 102`
- L27 `#define _g_ 103`
- L28 `#define _h_ 104`
- L29 `#define _i_ 105`
- L30 `#define _j_ 106`
- L31 `#define _k_ 107`
- L32 `#define _l_ 108`
- L33 `#define _m_ 109`
- L34 `#define _n_ 110`
- L35 `#define _o_ 111`
- L36 `#define _p_ 112`
- L37 `#define _q_ 113`
- L38 `#define _r_ 114`
- L39 `#define _s_ 115`
- L40 `#define _t_ 116`
- L41 `#define _u_ 117`
- L42 `#define _v_ 118`
- L43 `#define _w_ 119`
- L44 `#define _x_ 120`
- L45 `#define _y_ 121`
- L46 `#define _z_ 122`

#### Entry points (2)

- L81-90 _entry_ `void MainVS( in uint VertexId : SV_VertexID, out float4 OutPosition : SV_POSITION, out float2 OutUV : TEXCOORD0 )` — stage: **vertex (from C++ binding)** — C++: `FAccumulationDOFInjectVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Plugins/VirtualProduction/AccumulationDOF/Source/AccumulationDOF/Private/Shaders/AccumulationDOFShaders.cpp:371)
- L92-251 _entry_ `void MainPS( in float4 SvPosition : SV_POSITION, in float2 UV : TEXCOORD0, out float4 OutColor : SV_Target0 )` — stage: **pixel (from C++ binding)** — C++: `FAccumulationDOFInjectPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/VirtualProduction/AccumulationDOF/Source/AccumulationDOF/Private/Shaders/AccumulationDOFShaders.cpp:372)

#### Global resources (textures / buffers / samplers) (4)

- L48 _resource_ `Texture2D AccumulatedTexture;`
- L49 _resource_ `SamplerState AccumulatedSampler;`
- L66 _resource_ `Texture2D UndistortingDisplacementTexture;`
- L67 _resource_ `SamplerState UndistortingDisplacementSampler;`

#### Global parameters (uniforms) (12)

- L51 _parameter_ `float2 AccumulatedTextureSize;` — Accumulated texture dimensions for aspect ratio letterboxing
- L52 _parameter_ `float2 OutputTextureSize;` — Output texture dimensions
- L54 _parameter_ `float ProgressBarFraction;` — 0.0 to 1.0
- L55 _parameter_ `uint bDrawProgressBar;` — Non-zero to draw progress bar
- L56 _parameter_ `float2 ViewportSize;` — Viewport dimensions in pixels
- L57 _parameter_ `float OverscanFraction;` — Overscan fraction for progress bar positioning (0.0 = none, 0.1 = 10%)
- L58 _parameter_ `uint bDrawPreviewLabel;` — Non-zero to draw "Accumulation DOF Preview" label
- L59 _parameter_ `uint bIsFrozen;` — Non-zero to append "(FROZEN)" to preview label
- L60 _parameter_ `uint bApplyAspectFit;` — Non-zero to letterbox/pillarbox when accumulator and viewport aspects differ
- L68 _parameter_ `uint bApplyLensDistortion;`
- L71 _parameter_ `uint FrameCounter;` — Dithering parameters to counter tone curve quantization, although the 64-bit one is working out well
- L72 _parameter_ `float DitherStrength;`

#### Functions (1)

- L75-79 _function_ `float InterleavedGradientNoise(float2 PixelPos, uint FrameId)` — Interleaved gradient noise for temporal dithering

### `Plugins/VirtualProduction/AccumulationDOF/Shaders/Private/AccumulationDOFLateralCA.usf` (Private)

- lines: 162; parse: all-branches
- includes: L18 `/Engine/Public/Platform.ush`

#### Macros (#define, 3)

- L30 `#define NUM_SPECTRAL_BANDS 19`
- L46 `#define SPECTRAL_LUT_SIZE 32`
- L47 `#define SPECTRAL_LUT_MAX_INDEX (SPECTRAL_LUT_SIZE - 1)`

#### Entry points (2)

- L95-104 _entry_ `void MainVS( in uint VertexId : SV_VertexID, out float4 OutPosition : SV_POSITION, out float2 OutUV : TEXCOORD0 )` — stage: **vertex (from C++ binding)** — C++: `FAccumulationDOFLateralCAVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Plugins/VirtualProduction/AccumulationDOF/Source/AccumulationDOF/Private/Shaders/AccumulationDOFShaders.cpp:375)
- L106-161 _entry_ `void MainPS( in float4 SvPosition : SV_POSITION, in float2 UV : TEXCOORD0, out float4 OutColor : SV_Target0 )` — stage: **pixel (from C++ binding)** — C++: `FAccumulationDOFLateralCAPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/VirtualProduction/AccumulationDOF/Source/AccumulationDOF/Private/Shaders/AccumulationDOFShaders.cpp:376)

#### Global resources (textures / buffers / samplers) (2)

- L20 _resource_ `Texture2D SampleTexture;`
- L21 _resource_ `SamplerState SampleSampler;`

#### Global parameters (uniforms) (3)

- L24 _parameter_ `float IntensityUV;` — Intensity in UV space
- L27 _parameter_ `float StartOffset;` — Start offset threshold per axis (0-1). Creates a rectangular dead zone in the center where no dispersion occurs.
- L36 _parameter_ `float2 Center;` — Center in UV space (typically 0.5, 0.5)

#### static const (2)

- L33 _static_const_ `static const float Epsilon = 1e-6;` — Small value to avoid division by zero
- L49-82 _static_const_ `static const float3 SpectralLUT[SPECTRAL_LUT_SIZE] = { float3(0.175237, 0.000000, 0.824763), float3(0.167134, 0.000000, 0.832866), float3(0.149273, 0.000000, 0.850727), float3(0.113597, 0.000000, 0.886403), float3(0.062576, 0.000000, 0.937424), float3(0.017058, 0.046903, 0.936039), float3(0.000000, 0.149028, 0.850972), float3(0.000000, 0.258459, 0.741541), float3(0.000000, 0.360560, 0.639440), float3(0.000000, 0.458963, 0.541037), float3(0.000000, 0.558498, 0.441502), float3(0.000000, 0.660484, 0.339516), float3(0.000000, 0.763419, 0.236581), float3(0.000000, 0.860713, 0.139287), float3(0.0000`

#### Functions (1)

- L86-93 _function_ `float3 SpectralWeight(float NormalizedSpectralPosition)` — Compute spectral RGB weight for normalized spectral position using our physically-based LUT. Maps [0,1] to wavelength 380-700nm with linear interpolation.

### `Plugins/VirtualProduction/AccumulationDOF/Shaders/Private/AccumulationDOFMedian.usf` (Private)

- lines: 102; parse: all-branches
- includes: L9 `/Engine/Private/Common.ush`

#### Entry points (2)

- L19-27 _entry_ `void MainVS( in uint VertexId : SV_VertexID, out float4 OutPosition : SV_POSITION, out float2 OutUV : TEXCOORD0)` — stage: **vertex (from C++ binding)** — C++: `FAccumulationDOFMedianVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Plugins/VirtualProduction/AccumulationDOF/Source/AccumulationDOF/Private/Shaders/AccumulationDOFShaders.cpp:367)
- L84-101 _entry_ `void MainPS( in float4 SvPosition : SV_POSITION, in float2 UV : TEXCOORD0, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FAccumulationDOFMedianPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/VirtualProduction/AccumulationDOF/Source/AccumulationDOF/Private/Shaders/AccumulationDOFShaders.cpp:368)

#### Global resources (textures / buffers / samplers) (2)

- L12 _resource_ `Texture2D InputTexture;` — Input texture
- L13 _resource_ `SamplerState InputSampler;`

#### Global parameters (uniforms) (1)

- L16 _parameter_ `float2 InputTexelSize;` — Texture dimensions for offset calculation

#### static const (1)

- L29-39 _static_const_ `static const int2 kOffsets3x3[9] = { int2(-1, -1), int2( 0, -1), int2( 1, -1), int2(-1, 0), int2( 0, 0), int2( 1, 0), int2(-1, 1), int2( 0, 1), int2( 1, 1), };`

#### Functions (3)

- L42-52 _function_ `void LMHOperator(float4 A, float4 B, float4 C, out float4 L, out float4 M, out float4 H)` — Operator that outputs lowest, median and highest values from 3 input values
- L55-60 _function_ `float4 Median3(float4 A, float4 B, float4 C)` — 3 samples median
- L63-82 _function_ `float4 Median9(float4 In[9])` — Finds the median in O(n) comparisons (uses Smith1996 algo)

### `Plugins/VirtualProduction/AccumulationDOF/Shaders/Private/AccumulationDOFNormalize.usf` (Private)

- lines: 48; parse: all-branches
- includes: L7 `/Engine/Public/Platform.ush`

#### Entry points (2)

- L14-23 _entry_ `void MainVS( in uint VertexId : SV_VertexID, out float4 OutPosition : SV_POSITION, out float2 OutUV : TEXCOORD0 )` — stage: **vertex (from C++ binding)** — C++: `FAccumulationDOFNormalizeVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Plugins/VirtualProduction/AccumulationDOF/Source/AccumulationDOF/Private/Shaders/AccumulationDOFShaders.cpp:22)
- L25-47 _entry_ `void MainPS( in float4 SvPosition : SV_POSITION, in float2 UV : TEXCOORD0, out float4 OutColor : SV_Target0 )` — stage: **pixel (from C++ binding)** — C++: `FAccumulationDOFNormalizePS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/VirtualProduction/AccumulationDOF/Source/AccumulationDOF/Private/Shaders/AccumulationDOFShaders.cpp:23)

#### Global resources (textures / buffers / samplers) (2)

- L9 _resource_ `Texture2D AccumTexture;`
- L10 _resource_ `SamplerState AccumSampler;`

#### Global parameters (uniforms) (1)

- L12 _parameter_ `float InvWeightSum;`
