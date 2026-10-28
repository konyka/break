# Shaders / Plugins/Enterprise/MDLImporter/Shaders/Private

- files: 2; lines: 264
- record kinds: define=5, parameter=57, unparsed=6

### `Plugins/Enterprise/MDLImporter/Shaders/Private/FlakesAccess.ush` (Private)

- lines: 138; parse: all-branches; parse notes: 4

#### Macros (#define, 5)

- L20 `#define PI2 1.5707963267948966`
- L21 `#define USE_GRADIENTS 1`
- L26 `#define SAMPLE_TEX_COORD(SampleTexCoord, Result) float2 DdxUV = DDX(SampleTexCoord); float2 DdyUV = DDY(SampleTexCoord); Result = Texture2DSampleGrad(FlakesTexArray, FlakesTexArraySampler, SampleTexCoord, DdxUV, DdyUV);` (4 lines) _[#if USE_GRADIENTS == 1]_
- L34 `#define SAMPLE_TEX_ARRAY(UV, Index, Result) { float SideCount = sqrt(FlakesTexCount); float InvSideCount = 1.0 / SideCount; float TexPadding = 8.0; float TexSize = FlakesTexValues.x; float PaddedTexSize = TexSize + TexPadding * 2.0; float Atlas ...` (20 lines)
- L55 `#define SAMPLE_LUT(BinThetaI, Result) { float TexelSize = FlakesTexValues.y; float Padding = 4.0; float Index = (BinThetaI) * Padding * TexelSize + TexelSize; float Value = Texture2DSampleLevel(ThetaSliceLUT, ThetaSliceLUTSampler, float2( ...` (8 lines)

#### Global parameters (uniforms) (18)

- L31 _parameter_ `Result = Texture2DSample(FlakesTexArray, FlakesTexArraySampler, SampleTexCoord);` _[#if !(USE_GRADIENTS == 1)]_
- L65 _parameter_ `float ThetaF = clamp(ThetaAngles.x / PI2, 0.0, 1.0) * NumThetaF + 0.5;` — ThetaF sampling defines the angular sampling, i.e. angular flake lifetime
- L66 _parameter_ `float ThetaI = clamp(ThetaAngles.y / PI2, 0.0, 1.0) * NumThetaF + 0.5;`
- L69 _parameter_ `float LowThetaF = floor(ThetaF);` — bilinear interpolation indices
- L70 _parameter_ `float HighThetaF = LowThetaF + 1.0;`
- L71 _parameter_ `float LowThetaI = floor(ThetaI);`
- L72 _parameter_ `float HighThetaI = LowThetaI + 1.0;`
- L74 _parameter_ `float2 UV = TexCoord * Tiling;`
- L75 _parameter_ `float2 DdxUV = DDX(UV);`
- L76 _parameter_ `float2 DdyUV = DDY(UV);`
- L91 _parameter_ `half3 ColorBottomLeft = 0.0;`
- L92 _parameter_ `half3 ColorTopLeft = 0.0;`
- L93 _parameter_ `half3 ColorBottomRight = 0.0;`
- L94 _parameter_ `half3 ColorTopRight = 0.0;`
- L133 _parameter_ `float DiffThetaF = ThetaF - float(LowThetaF);` — bilinear interpolation
- L134 _parameter_ `float DiffThetaI = ThetaI - float(LowThetaI);`
- L135 _parameter_ `half3 Bottom = (1.0 - DiffThetaF) * ColorBottomLeft + DiffThetaF * ColorBottomRight;`
- L136 _parameter_ `half3 Top = (1.0 - DiffThetaF) * ColorTopLeft + DiffThetaF * ColorTopRight;`

#### Unparsed (raw text) (4)

- L77-89 _unparsed_ `if (NumThetaI < NumThetaF)`
- L96-112 _unparsed_ `if (LowThetaI < MaxThetaI)` — access flakes texture and stay in the correct slices(no slip over)
- L114-130 _unparsed_ `if (HighThetaI < MaxThetaI)`
- L137 _unparsed_ `return (1.0 - DiffThetaI) * Bottom + DiffThetaI * Top;`

<details><summary>parse notes</summary>

- L77: unrecognised block header 'if (NumThetaI < NumThetaF)'
- L96: unrecognised block header 'if (LowThetaI < MaxThetaI)'
- L114: unrecognised block header 'if (HighThetaI < MaxThetaI)'
- L137: statement at declaration scope 'return (1.0 - DiffThetaI) * Bottom + DiffThetaI * Top'

</details>

### `Plugins/Enterprise/MDLImporter/Shaders/Private/SpiralBlurWithIOR.ush` (Private)

- lines: 126; parse: all-branches; parse notes: 2

#### Global parameters (uniforms) (39)

- L22 _parameter_ `const int RadialSteps = 48;`
- L23 _parameter_ `const int AngularSteps = 1;`
- L25 _parameter_ `const float MagicBlurNumber = 100.0;`
- L29 _parameter_ `const float RefractionThicknessCorrection = 50.0;` — Thickness added to account for normal texture features when calculating refraction light bending.
- L31 _parameter_ `float UVDistance = 0.2;`
- L32 _parameter_ `float AngularOffset = 0.618;`
- L34 _parameter_ `float SizeOnScreenFactor = View.ViewToClip[0][0] / PixelDepth;`
- L36 _parameter_ `float2 ScreenUV = MaterialFloat2(ScreenAlignedPosition(Parameters.ScreenPosition).xy);`
- L37 _parameter_ `float2 BaseUV = ScreenUV;`
- L40 _parameter_ `float3 PixelNormal = mul(mul(Normal, Parameters.TangentToWorld), (MaterialFloat3x3)ResolvedView.TranslatedWorldToView);` — Calculate PixelNormal
- L43 _parameter_ `float SceneDepth = CalcSceneDepth(BaseUV);` — Fetch SceneDepth
- L46 _parameter_ `float3 DistortedNormal = PixelNormal;` — Straighten PixelNormal to keep refraction closer to screen space
- L47 _parameter_ `DistortedNormal.z += sign(DistortedNormal.z) * NormalAlignFactor;`
- L48 _parameter_ `DistortedNormal = normalize(DistortedNormal);`
- L51 _parameter_ `float2 NormalUV = DistortedNormal.xy;` — Adjust BaseUV for refraction (based on IOR, PixelNormal, and ObjectThickness)
- L52 _parameter_ `NormalUV.y = -NormalUV.y;`
- L53 _parameter_ `float2 RefractionOffset = (ObjectThickness + RefractionThicknessCorrection) * NormalUV * (1.0 / IOR - 1.0);`
- L56 _parameter_ `RefractionOffset *= MagicRefractionNumber * SizeOnScreenFactor;` — Establish max RefractionOffset and scale by SizeOnScreenFactor
- L58 _parameter_ `BaseUV += RefractionOffset;`
- L60 _parameter_ `float2 NewUV = BaseUV;`
- L62 _parameter_ `float RadialStepSize = UVDistance / RadialSteps;`
- L63 _parameter_ `float2 CurOffset = { 0.0, 0.0 };`
- L66 _parameter_ `SceneDepth = CalcSceneDepth(NewUV);` — Recalculate SceneDepth with NewUV
- L69 _parameter_ `float2 ScenePixels = View.BufferSizeAndInvSize.xy * ScreenUV;` — Screen aligned TemporalAA jitter
- L70 _parameter_ `ScenePixels += View.TemporalAAParams.r;`
- L71 _parameter_ `float2 RandomSamp = ((uint)(ScenePixels.x) + 2 * (uint)(ScenePixels.y)) % 5;`
- L72 _parameter_ `RandomSamp += Texture2DSample(RandomTex, RandomTexSampler, View.BufferSizeAndInvSize.xy * ScreenUV / 64).xy;`
- L73 _parameter_ `RandomSamp /= 6;`
- L74 _parameter_ `RandomSamp -= 0.5;`
- L76 _parameter_ `float TempAARotation = RandomSamp.x;`
- L77 _parameter_ `float TempAADistance = RadialStepSize * RandomSamp.x;`
- L80 _parameter_ `BaseUV += View.BufferSizeAndInvSize.zw * RandomSamp;`
- L86 _parameter_ `float VolumeBlurAmount = 1.0 - exp(-ObjectThickness * VolumeScatter);` — Calculate BlurAmount
- L87 _parameter_ `float SurfaceBlurAmount = 1.0 - 1.0 * exp(-(SceneDepth - PixelDepth) * SurfaceScatter);` — - 0.5 * exp(-(RandomSceneDepth - PixelDepth) * SurfaceScatter);
- L88 _parameter_ `float BlurAmount = saturate(VolumeBlurAmount + SurfaceBlurAmount);`
- L90 _parameter_ `float TwoPi = 6.283185;`
- L91 _parameter_ `float3 CurColor = { 0.0, 0.0, 0.0 };`
- L92 _parameter_ `float CurDistance = 0.0;`
- L93 _parameter_ `float Substep = 0.0;`

#### Unparsed (raw text) (2)

- L95-98 _unparsed_ `if (BlurAmount == 0.0)`
- L99-125 _unparsed_ `else`

<details><summary>parse notes</summary>

- L95: unrecognised block header 'if (BlurAmount == 0.0)'
- L99: unrecognised block header 'else'

</details>
