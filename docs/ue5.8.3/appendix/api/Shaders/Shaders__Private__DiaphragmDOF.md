# Shaders / Shaders/Private/DiaphragmDOF

- files: 22; lines: 8216
- record kinds: cpp_binding=12, define=218, entry=14, function=121, groupshared=22, include=46, member=145, method=12, parameter=91, resource=77, static_const=6, struct=25

### `Shaders/Private/DiaphragmDOF/DOFBokehLUT.usf` (Private)

- lines: 271; parse: all-branches
- includes: L7 `DOFCommon.ush`

#### Macros (#define, 13)

- L13 `#define BOKEH_SHAPE_CIRCLE 0`
- L14 `#define BOKEH_SHAPE_STRAIGHT_BLADES 1`
- L15 `#define BOKEH_SHAPE_ROUNDED_BLADES 2`
- L18 `#define LUT_FORMAT_DISTANCE_FACTOR 0`
- L19 `#define LUT_FORMAT_FULL_RES_TO_COC_DISTANCE 1`
- L20 `#define LUT_FORMAT_GATHER_SAMPLE_POS 2`
- L26 `#define BOKEH_SHAPE (BOKEH_SHAPE_ROUNDED_BLADES)` _[#if DIM_ROUND_BLADES]_
- L29 `#define BOKEH_SHAPE (BOKEH_SHAPE_STRAIGHT_BLADES)` _[#if !(DIM_ROUND_BLADES)]_
- L34 `#define CONFIG_CENTER_BOKEH_AT_UV_ORIGIN 1` _[#if DIM_LUT_FORMAT == LUT_FORMAT_DISTANCE_FACTOR]_
- L42 `#define CONFIG_CENTER_BOKEH_AT_UV_ORIGIN 0` _[#if !defined(CONFIG_CENTER_BOKEH_AT_UV_ORIGIN)]_
- L48 `#define THREADGROUP_SIZEX (8)`
- L49 `#define THREADGROUP_SIZEY (THREADGROUP_SIZEX)`
- L50 `#define THREADGROUP_TOTALSIZE (THREADGROUP_SIZEX * THREADGROUP_SIZEY)`

#### Entry points (1)

- L161-270 _entry_ `[numthreads(THREADGROUP_SIZEX, THREADGROUP_SIZEY, 1)] void BuildBokehLUTMainCS(uint2 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FDiaphragmDOFBuildBokehLUTCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/DiaphragmDOF.cpp:1473)

#### Global resources (textures / buffers / samplers) (1)

- L156 _resource_ `RWTexture2D<float4> BokehLUTOutput;`

#### Global parameters (uniforms) (6)

- L56 _parameter_ `uint BladeCount;` — Number of blades >= 4.
- L59 _parameter_ `float CocRadiusToCircumscribedRadius;` — Factor to convert a coc radius to bokeh's circomscribed & incircle radius
- L60 _parameter_ `float CocRadiusToIncircleRadius;`
- L63 _parameter_ `float DiaphragmRotation;` — Rotation of the blades of the diaphragm.
- L66 _parameter_ `float DiaphragmBladeRadius;` — Radius of the blade for a boked area=PI.
- L69 _parameter_ `float DiaphragmBladeCenterOffset;` — Offset.

#### Functions (2)

- L77-120 _function_ `float ComputeCocRadiusToBokehEdgeFactor(float PixelAngle)` — Compute scaling factor that needs to be applied to radial coordinate (R=1, PixelAngle)'s radius R, to have the point projected onto the bokeh's edge with the bokeh area remaining equal to PI.
- L123-151 _function_ `void RingCoordinateFromCartesianCoordinate(const float2 C, out float OutRingRadius, out float OutRingSampleId)`

### `Shaders/Private/DiaphragmDOF/DOFCocTileCommon.ush` (Private)

- lines: 143; parse: all-branches
- includes: L9 `DOFCommon.ush`

#### Macros (#define, 4)

- L15 `#define COC_TILE_MAX_BUFFER_COUNT 2`
- L23 `#define COC_TILE_LAYOUT_FGD_BGD 0`
- L27 `#define COC_TILE_LAYOUT_FGD (COC_TILE_LAYOUT_FGD_BGD)`
- L30 `#define COC_TILE_LAYOUT_FGD_SEP_BGD 1`
- L7 #pragma `once`

#### Structs / classes (1)

- L47-66 _struct_ **`FCocTileSample`** `struct FCocTileSample` — Tile buffer.
  - L50 _member_ `float FgdMinCoc;` — The minimum Coc for foreground <= 0.
  - L53 _member_ `float FgdMaxCoc;` — The maximum Coc for forground <= 0.
  - L56 _member_ `float BgdMinCoc;` — The minimum Coc for background >= 0.
  - L59 _member_ `float BgdMaxCoc;` — The maximum Coc for background >= 0.
  - L62 _member_ `float BgdMinIntersectableCoc;` — The minimum intersectable Coc radius >= 0.
  - L65 _member_ `float BgdMinConservativeCloserGoemetryDistance;` — The conservative distance field to any closer geometry.

#### Functions (5)

- L34-41 _function_ `uint GetBufferCountForCocTileLayour(uint Layout)` — Returns the number of buffers for a Coc tile layout.
- L71-79 _function_ `void InitCocTileSample(out FCocTileSample Sample)`
- L84-101 _function_ `void EncodeCocTileSample(in FCocTileSample Sample, in uint Layout, out float4 Raw[COC_TILE_MAX_BUFFER_COUNT])` — Encode coc tile sample. @param <OutputLayout>: the layout of the coc buffer to output.
- L106-126 _function_ `void DecodeCocTileSample(in float4 Raw[COC_TILE_MAX_BUFFER_COUNT], in uint Layout, out FCocTileSample Sample)` — Decode coc tile sample. @param <InputLayout>: the layout of the coc buffer.
- L133-142 _function_ `FCocTileSample LoadCocTile(const uint Layout, Texture2D Buffer0, Texture2D Buffer1, int2 TilePos)` — Sample and decode tile buffer.

### `Shaders/Private/DiaphragmDOF/DOFCocTileDilate.usf` (Private)

- lines: 259; parse: all-branches
- includes: L7 `DOFCommon.ush`, L8 `DOFCocTileCommon.ush`

#### Macros (#define, 3)

- L14 `#define DILATE_MODE_STANDALONE 0`
- L15 `#define DILATE_MODE_MIN_MAX 1`
- L16 `#define DILATE_MODE_MIN_ABS 2`

#### Entry points (1)

- L45-258 _entry_ `[numthreads(DEFAULT_GROUP_BORDER_SIZE, DEFAULT_GROUP_BORDER_SIZE, 1)] void CocDilateMainCS(uint2 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FDiaphragmDOFCocDilateCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/DiaphragmDOF.cpp:1469) — TODO: could support larger radius with LDS.

#### Global resources (textures / buffers / samplers) (6)

- L29 _resource_ `Texture2D TileInput_Foreground;`
- L30 _resource_ `Texture2D TileInput_Background;`
- L32 _resource_ `Texture2D DilatedTileMinMax_Foreground;`
- L33 _resource_ `Texture2D DilatedTileMinMax_Background;`
- L38 _resource_ `RWTexture2D<float4> TileOutput_Foreground;`
- L39 _resource_ `RWTexture2D<float4> TileOutput_Background;`

#### Global parameters (uniforms) (5)

- L21 _parameter_ `uint4 ViewportRect;`
- L22 _parameter_ `uint SampleOffsetMultipler;`
- L23 _parameter_ `float fSampleOffsetMultipler;`
- L26 _parameter_ `float CocRadiusToBucketDistanceUpperBound;` — Multiplier to compare CocRadius and bucket distance.
- L27 _parameter_ `float BucketDistanceToCocRadius;`

### `Shaders/Private/DiaphragmDOF/DOFCocTileFlatten.usf` (Private)

- lines: 317; parse: all-branches
- includes: L7 `DOFCommon.ush`, L8 `DOFCocTileCommon.ush`

#### Macros (#define, 6)

- L14 `#define FLATTEN_METHOD_REDUCE_LDS 0`
- L15 `#define FLATTEN_METHOD_ATOMIC_LDS 1`
- L16 `#define FLATTEN_METHOD_WAVE_MINMAX 2`
- L19 `#define CONFIG_FLATTEN_METHOD (FLATTEN_METHOD_WAVE_MINMAX)` _[#if COMPILER_SUPPORTS_WAVE_MINMAX && COMPILER_SUPPORTS_WAVE_ONCE]_
- L21 `#define CONFIG_FLATTEN_METHOD (FLATTEN_METHOD_REDUCE_LDS)` _[#if !(COMPILER_SUPPORTS_WAVE_MINMAX && COMPILER_SUPPORTS_WAVE_ONCE)]_
- L43 `#define LDS_LAYOUT (COC_TILE_LAYOUT_FGD_SEP_BGD)`

#### Entry points (1)

- L123-316 _entry_ `[numthreads(DEFAULT_GROUP_BORDER_SIZE, DEFAULT_GROUP_BORDER_SIZE, 1)] void CocFlattenMainCS( uint2 GroupId : SV_GroupID, uint2 DispatchThreadId : SV_DispatchThreadID, uint GroupIndex : SV_GroupIndex)` — stage: **compute** — C++: `FDiaphragmDOFCocFlattenCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/DiaphragmDOF.cpp:1468)

#### Global resources (textures / buffers / samplers) (4)

- L31 _resource_ `Texture2D GatherInput_SceneColor;`
- L32 _resource_ `Texture2D GatherInput_SeparateCoc;`
- L37 _resource_ `RWTexture2D<float4> TileOutput_Foreground;`
- L38 _resource_ `RWTexture2D<float4> TileOutput_Background;`

#### Global parameters (uniforms) (3)

- L27 _parameter_ `float2 Stride;`
- L28 _parameter_ `float4 GatherInputExtentAndInvExtent;`
- L29 _parameter_ `float4 GatherInputViewRectUV;`

#### groupshared (7)

- L72 _groupshared_ `groupshared float4 Shared0[DEFAULT_GROUP_BORDER_SIZE * DEFAULT_GROUP_BORDER_SIZE];` — TODO: could technically only need half of it: would this be faster? _[#if CONFIG_FLATTEN_METHOD == FLATTEN_METHOD_REDUCE_LDS]_
- L73 _groupshared_ `groupshared float Shared1[DEFAULT_GROUP_BORDER_SIZE * DEFAULT_GROUP_BORDER_SIZE];` _[#if CONFIG_FLATTEN_METHOD == FLATTEN_METHOD_REDUCE_LDS]_
- L112 _groupshared_ `groupshared uint SharedForegroundMinCocRadius;` _[#if !(CONFIG_FLATTEN_METHOD == FLATTEN_METHOD_REDUCE_LDS)]_
- L113 _groupshared_ `groupshared uint SharedForegroundMaxCocRadius;` _[#if !(CONFIG_FLATTEN_METHOD == FLATTEN_METHOD_REDUCE_LDS)]_
- L114 _groupshared_ `groupshared uint SharedBackgroundMinCocRadius;` _[#if !(CONFIG_FLATTEN_METHOD == FLATTEN_METHOD_REDUCE_LDS)]_
- L115 _groupshared_ `groupshared uint SharedBackgroundMinIntersectableCocRadius;` _[#if !(CONFIG_FLATTEN_METHOD == FLATTEN_METHOD_REDUCE_LDS)]_
- L116 _groupshared_ `groupshared uint SharedBackgroundMaxCocRadius;` _[#if !(CONFIG_FLATTEN_METHOD == FLATTEN_METHOD_REDUCE_LDS)]_

#### Functions (4)

- L46-56 _function_ `void InitCocTileSampleFromCocRadius(float CocRadius, out FCocTileSample OutA)`
- L58-66 _function_ `void ReduceOperator(inout FCocTileSample A, in const FCocTileSample B)`
- L75-91 _function_ `FCocTileSample LoadFromLds(uint i)` _[#if CONFIG_FLATTEN_METHOD == FLATTEN_METHOD_REDUCE_LDS]_
- L93-107 _function_ `void StoreToLds(uint i, in const FCocTileSample Sample)` _[#if CONFIG_FLATTEN_METHOD == FLATTEN_METHOD_REDUCE_LDS]_

### `Shaders/Private/DiaphragmDOF/DOFCommon.ush` (Private)

- lines: 265; parse: all-branches
- includes: L9 `../Common.ush`, L10 `../ScreenPass.ush`, L13 `../CircleDOFCommon.ush`

#### Macros (#define, 31)

- L44 `#define static_condition(test) (test)`
- L50 `#define LAYER_PROCESSING_FOREGROUND_ONLY 0`
- L51 `#define LAYER_PROCESSING_FOREGROUND_HOLE_FILLING 1`
- L52 `#define LAYER_PROCESSING_BACKGROUND_ONLY 2`
- L53 `#define LAYER_PROCESSING_COMBINED 3`
- L54 `#define LAYER_PROCESSING_SLIGHT_OUT_OF_FOCUS 4`
- L58 `#define BOKEH_SIMULATION_DISABLED 0`
- L59 `#define BOKEH_SIMULATION_SIMMETRIC 1`
- L60 `#define BOKEH_SIMULATION_GENERAL 2`
- L67 `#define HOLE_FILLING_METHOD_OPACITY_AMEND 0`
- L70 `#define HOLE_FILLING_METHOD_SEPARATE_GATHER 1`
- L73 `#define HOLE_FILLING_METHOD_BILATERAL 2`
- L77 `#define GATHER_INPUT_LAYOUT_RGB_COC 0`
- L80 `#define GATHER_INPUT_LAYOUT_RGB_ALPHA_COC 1`
- L83 `#define GATHER_INPUT_LAYOUT_RGB_SEPARATE_COC 2`
- L89 `#define EXTREMELY_LARGE_COC_RADIUS 16384`
- L93 `#define DEFAULT_GROUP_BORDER_SIZE 8`
- L96 `#define COC_TILE_SIZE 8`
- L100 `#define PASS_RES_DIVISOR 2`
- L103 `#define COC_TILE_RES_DIVISOR 2`
- L106 `#define MAIN_KERNEL_RING_COUNT 5`
- L109 `#define MAX_RECOMBINE_ABS_COC_RADIUS 3.0`
- L112 `#define BOKEH_LUT_SIZE 32`
- L116 `#define CONFIG_DOF_ALPHA (DIM_ALPHA_CHANNEL)` _[#if defined(DIM_ALPHA_CHANNEL)]_
- L118 `#define CONFIG_DOF_ALPHA 0` _[#if !(defined(DIM_ALPHA_CHANNEL))]_
- L122 `#define FAST_GATHERING_COC_ERROR 0.05`
- L125 `#define DEBUG_OUTPUT 0`
- L247 `#define FullResPixelDistanceToCocDistance(x) (0.5 * (x))`
- L250 `#define CocDistanceToFullResPixelDistance(x) (2.0 * (x))`
- L260 `#define kContantlyPassingAffineTransformation float2(0, 1)`
- L261 `#define kContantlyBlockingAffineTransformation float2(0, 0)`
- L7 #pragma `once`; L18 #pragma `message("UESHADERMETADATA_VERSION EADEBBCC-57EB-41E0-9606-DC289F55A057")`; L24 #pragma `warning(error: 3206)`; L27 #pragma `warning(error: 3203)`; L30 #pragma `warning(disable: 3584)`; L33 #pragma `dxc diagnostic ignored "-Wparentheses-equality"`

#### Global resources (textures / buffers / samplers) (3)

- L175 _resource_ `Texture2D DynamicRadiusOffsetLUT;`
- L176 _resource_ `SamplerState DynamicRadiusOffsetLUTSampler;`
- L181 _resource_ `RWTexture2D<float4> DebugOutput;` _[#if DEBUG_OUTPUT]_

#### Global parameters (uniforms) (9)

- L164 _parameter_ `float CocInfinityRadius;` — See SetCocModelParameters, CocRadiusBasis
- L165 _parameter_ `float CocInFocusRadius;`
- L166 _parameter_ `uint bCocEnableDynamicRadiusOffset;`
- L167 _parameter_ `float CocMinRadius;`
- L168 _parameter_ `float CocMaxRadius;`
- L169 _parameter_ `float CocSqueeze;`
- L170 _parameter_ `float CocInvSqueeze;`
- L172 _parameter_ `float DepthBlurRadius;`
- L173 _parameter_ `float DepthBlurExponent;`

#### static const (4)

- L131 _static_const_ `static const float kCocRadiusToFullResFactor = 0.5;` — Coc radiuses are in half res.
- L134-139 _static_const_ `static const int2 kSquare2x2[4] = { int2(0, 0), int2(1, 0), int2(0, 1), int2(1, 1), };`
- L141-146 _static_const_ `static const int2 kOffsetsCross3x3[4] = { int2(-1, -1), int2( 1, -1), int2(-1, 1), int2( 1, 1), };`
- L148-158 _static_const_ `static const int2 kOffsetsSquare3x3[9] = { int2(-1, +1), int2(-1, 0), int2(-1, -1), int2( 0, +1), int2( 0, 0), int2( 0, -1), int2(+1, +1), int2(+1, 0), int2(+1, -1), };`

#### Functions (6)

- L188-204 _function_ `float GetCocOffset(float CocRadius)` _[#if WITH_DYNAMIC_COC_OFFSET]_
- L209-226 _function_ `float SceneDepthToCocRadius(float SceneDepth)` — Returns the coc radius The unit for the output, i.e. 'encoded' pixels or physical pixels, depends on what CocRadiusBasis was used.
- L229-232 _function_ `bool IsForeground(float CocRadius)` — Return whether this is front element from CocRadius.
- L235-238 _function_ `float Luma4(float3 Color)` — Faster but less accurate luma computation with a scaling by 4.
- L241-244 _function_ `float SafeRcp(float x, float d = 0.0)` — Returns 1/x if x > 0, d otherwise.
- L253-257 _function_ `float SaturateWithAffineTransformation(float x, float2 AffineTransformation)` — Utility to use a saturating affine transformation.

### `Shaders/Private/DiaphragmDOF/DOFDownsample.usf` (Private)

- lines: 93; parse: all-branches
- includes: L7 `DOFDownsample.ush`

#### Entry points (1)

- L32-92 _entry_ `[numthreads(DEFAULT_GROUP_BORDER_SIZE, DEFAULT_GROUP_BORDER_SIZE, 1)] void DownsampleCS(uint2 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FDiaphragmDOFDownsampleCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/DiaphragmDOF.cpp:1470)

#### Global resources (textures / buffers / samplers) (4)

- L17 _resource_ `Texture2D GatherInput_SceneColor;`
- L18 _resource_ `Texture2D GatherInput_SeparateCoc;`
- L23 _resource_ `RWTexture2D<float4> OutDownsampledGatherInput_SceneColor;`
- L26 _resource_ `RWTexture2D<float> OutDownsampledGatherInput_SeparateCoc;` _[#if CONFIG_DOF_ALPHA]_

#### Global parameters (uniforms) (4)

- L12 _parameter_ `uint4 ViewportRect;`
- L13 _parameter_ `float OutputCocRadiusMultiplier;`
- L15 _parameter_ `float4 GatherInputExtentAndInvExtent;`
- L16 _parameter_ `float4 GatherInputViewRectUV;`

### `Shaders/Private/DiaphragmDOF/DOFDownsample.ush` (Private)

- lines: 285; parse: all-branches
- includes: L7 `DOFCommon.ush`, L8 `/Engine/Public/WaveBroadcastIntrinsics.ush`

#### Macros (#define, 2)

- L14 `#define DOWNSAMPLE_COC_OPERATOR 4` _[#if defined(CONFIG_SETUP)]_
- L18 `#define DOWNSAMPLE_COC_OPERATOR 2` _[#if !(defined(CONFIG_SETUP))]_

#### Structs / classes (1)

- L122-132 _struct_ **`FCocDownsampleParams`** `struct FCocDownsampleParams`
  - L125 _member_ `float CocRadiusMultiplier;` — Multiplier to apply on the bilateral weights.
  - L128 _member_ `float FrameExposureScale;` — The exposure scale of the frame.
  - L131 _member_ `bool bDoColorBasedWeighting;` — Whether should color based weightings to reduce highlight contamination.

#### Functions (6)

- L26-110 _function_ `float DownsampleCoc(float CocRadii[4])` — Operator to use to downsample 4 sample to 1. TODO: This as been fetched from Circle DOF, so redo this experiments, and try new ones.
- L114-119 _function_ `float HdrWeight4(float3 Color, float Exposure)` — Optimized HDR weighting function.
- L136-164 _function_ `float ComputeDownsamplingBilateralWeight( FCocDownsampleParams DownsampleParams, float OutCocRadius, float SampleCocRadius, float3 SampleColor = 0)` — Compute the bilateral weight of sample to downsample.
- L168-193 _function_ `void DownsampleSceneColorWithCoc( FCocDownsampleParams DownsampleParams, float4 Color[4], float CocRadii[4], out float4 OutColor, out float OutCocRadius)` — Operator to use to downsample 4 scene sample to 1.
- L203-259 _function_ `float DownsampleCoc_Wave8x8(float CocRadius, const uint ReductionScale)` — Returns the downsampling Coc from the Coc radius on 4 different lane: (0; 0) (ReductionScale; 0) (0; ReductionScale) (ReductionScale; ReductionScale) _[#if PLATFORM_SUPPORTS_WAVE_BROADCAST]_
- L266-282 _function_ `float Sum2x2WithinWave8x8(float x, const uint ReductionScale)` — Sums values on 4 different lane when dispatched as 8x8 tile: (0; 0) (ReductionScale; 0) (0; ReductionScale) (ReductionScale; ReductionScale) _[#if PLATFORM_SUPPORTS_WAVE_BROADCAST]_

### `Shaders/Private/DiaphragmDOF/DOFGatherAccumulator.ush` (Private)

- lines: 832; parse: all-branches
- includes: L9 `DOFGatherCommon.ush`

#### Macros (#define, 2)

- L610 `#define LARGEST_RINGS_FIRST 1` _[#if GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_RINGBINNING && DIM_LAYER_PROCESSING == LAYER_PROCESSING_BACKGROUND_ONLY]_
- L612 `#define LARGEST_RINGS_FIRST 0` _[#if GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_RINGBINNING && !(DIM_LAYER_PROCESSING == LAYER_PROCESSING_BACKGROUND_ONLY) && DIM_LAYER_PROCESSING == LAYER_PROCESSING_FOREGROUND_ONLY]_
- L7 #pragma `once`

#### Structs / classes (2)

- L15-90 _struct_ **`FGatherAccumulator`** `struct FGatherAccumulator` — Accumulator of all gathered samples.
  - L18 _member_ `FGatherInputParameters GatherParameters;` — Gather parameters.
  - L21 _member_ `FLargerConvolution LargerConvolution;` — Gathering kernel for larger.
  - L24 _member_ `uint LayerProcessing;` — Layer to process.
  - L28 _member_ `float4 Color;` — One single layer. _[#if GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_SIMPLE]_
  - L29 _member_ `float ColorWeight;` _[#if GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_SIMPLE]_
  - L31 _member_ `float Opacity;` _[#if GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_SIMPLE]_
  - L32 _member_ `float OpacityWeight;` _[#if GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_SIMPLE]_
  - L35 _member_ `float DistanceToClosestForeground;` — Distance to the closest foreground sample. _[#if GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_SIMPLE]_
  - L41 _member_ `bool bIsHoleFillingForForeground;` — Hole filling? _[#if !(GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_SIMPLE) && GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_JIMENEZ2014]_
  - L44 _member_ `float CenterCocRadius;` — Coc radius of the center of the kernel. _[#if !(GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_SIMPLE) && GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_JIMENEZ2014]_
  - L47 _member_ `float4 Layer[2];` — Scene color per layer. _[#if !(GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_SIMPLE) && GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_JIMENEZ2014]_
  - L50 _member_ `float LayerWeight[2];` — Weight of Layer. _[#if !(GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_SIMPLE) && GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_JIMENEZ2014]_
  - L53 _member_ `float LayerSampleCount[2];` — Number of samples accumulated in each layers. _[#if !(GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_SIMPLE) && GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_JIMENEZ2014]_
  - L55 _member_ `float IntersectionSum;` _[#if !(GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_SIMPLE) && GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_JIMENEZ2014]_
  - L56 _member_ `float ForegroundSum;` _[#if !(GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_SIMPLE) && GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_JIMENEZ2014]_
  - L63 _member_ `float4 PreviousColor;` — Accumulated results for previous bucket. _[#if !(GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_SIMPLE) && !(GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_JIMENEZ2014) && GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_R...]_
  - L64 _member_ `float PreviousCocRadius;` _[#if !(GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_SIMPLE) && !(GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_JIMENEZ2014) && GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_R...]_
  - L65 _member_ `float PreviousCocRadiusSquare;` _[#if !(GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_SIMPLE) && !(GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_JIMENEZ2014) && GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_R...]_
  - L66 _member_ `float PreviousWeight;` _[#if !(GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_SIMPLE) && !(GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_JIMENEZ2014) && GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_R...]_
  - L69 _member_ `float4 CurrentColor;` — Accumulating results for current bucket. _[#if !(GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_SIMPLE) && !(GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_JIMENEZ2014) && GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_R...]_
  - L70 _member_ `float CurrentCocRadius;` _[#if !(GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_SIMPLE) && !(GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_JIMENEZ2014) && GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_R...]_
  - L71 _member_ `float CurrentCocRadiusSquare;` _[#if !(GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_SIMPLE) && !(GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_JIMENEZ2014) && GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_R...]_
  - L72 _member_ `float CurrentWeight;` _[#if !(GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_SIMPLE) && !(GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_JIMENEZ2014) && GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_R...]_
  - L74 _member_ `float CurrentTranslucency;` _[#if !(GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_SIMPLE) && !(GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_JIMENEZ2014) && GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_R...]_
  - L77 _member_ `float BorderingRadius;` — The bordering radius between current and previous buckets. _[#if !(GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_SIMPLE) && !(GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_JIMENEZ2014) && GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_R...]_
  - L79 _member_ `bool bIsFirstRing;` _[#if !(GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_SIMPLE) && !(GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_JIMENEZ2014) && GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_R...]_
  - L87 _member_ `float FarBorderingRadius;` _[#if CONFIG_LAYER_GATHERING]_
  - L88 _member_ `float CloseBorderingRadius;` _[#if CONFIG_LAYER_GATHERING]_
- L158-163 _struct_ **`FGatherSampleDerivedParameters`** `struct FGatherSampleDerivedParameters` _[#if GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_SIMPLE]_
  - L160 _member_ `float Weight;` _[#if GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_SIMPLE]_
  - L161 _member_ `float IsConsidered;` _[#if GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_SIMPLE]_
  - L162 _member_ `float Opacity;` _[#if GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_SIMPLE]_

#### Functions (31)

- L93-152 _function_ `FGatherAccumulator CreateGatherAccumulator( in FGatherInputParameters GatherParameters, in FLargerConvolution LargerConvolution)` — Create an accumulator for gathering.
- L166-170 _function_ `float ComputeBackgroundSampleOpacity(in const FGatherInputParameters GatherParameters, float CocRadius)` — Returns the opacity to use to transition to background. _[#if GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_SIMPLE]_
- L172-203 _function_ `FGatherSampleDerivedParameters ComputeSampleDerivates(in FGatherAccumulator Accumulator, in FGatherSample A)` _[#if GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_SIMPLE]_
- L205-238 _function_ `void HoleFillCloserSample( in FGatherAccumulator Accumulator, inout FGatherSample A, inout FGatherSampleDerivedParameters DerivedA, in FGatherSample Closer, in FGatherSampleDerivedParameters DerivedCloser)` _[#if GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_SIMPLE]_
- L241-263 _function_ `void AccumulateSample( inout FGatherAccumulator Accumulator, in FGatherSample A, in FGatherSampleDerivedParameters DerivedA)` — Accumulates sample. _[#if GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_SIMPLE]_
- L266-270 _function_ `void AccumulateCenterSample(inout FGatherAccumulator Accumulator, in FGatherSample A)` — Accumulates center sample. _[#if GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_SIMPLE]_
- L272-275 _function_ `void AccumulateCenterSampleAsItsOwnRing(inout FGatherAccumulator Accumulator, in FGatherSample A)` _[#if GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_SIMPLE]_
- L278-284 _function_ `void AmendAccumulatedRingsWeight( inout FGatherAccumulator Accumulator, in FGatherInputParameters NewGatherParameters, float AccumulatedWeightMultiplier)` — Changes the already accumulated weight, used when doing varying gathering sample density. _[#if GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_SIMPLE]_
- L287-290 _function_ `void StartRingSamples(inout FGatherAccumulator Accumulator, in FGatherRingInfos RingInfos)` — Setup up the accumulator for a ring. _[#if GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_SIMPLE]_
- L293-329 _function_ `void AccumulateMirrorSamples(inout FGatherAccumulator Accumulator, in FGatherSample A, in FGatherSample B)` — Accumulates mirror samples. _[#if GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_SIMPLE]_
- L332-335 _function_ `void EndRingSamples(inout FGatherAccumulator Accumulator, in FGatherRingInfos RingInfos)` — Digests all samples accumulated for the ring. _[#if GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_SIMPLE]_
- L338-366 _function_ `void ResolveAccumulatorOutputs( in FGatherAccumulator Accumulator, in FGatherResolveInfos GatherResolveInfos, out FAccumulatorOutput Output)` — Resolves the background layer output from the accumulator. _[#if GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_SIMPLE]_
- L376-388 _function_ `float ComputeSampleLayer(in FGatherAccumulator Accumulator, in FGatherSample A)` — Returns the layer id the sample should go in. (Jiminez 2014, slide 100) _[#if GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_JIMENEZ2014]_
- L390-393 _function_ `float ComputeForegroundFading(in const FGatherInputParameters GatherParameters, float CocRadius)` _[#if GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_JIMENEZ2014]_
- L396-432 _function_ `void AccumulateSample(inout FGatherAccumulator Accumulator, in FGatherSample A, float Weight)` — Accumulates a sample. _[#if GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_JIMENEZ2014]_
- L435-447 _function_ `void AccumulateCenterSample(inout FGatherAccumulator Accumulator, in FGatherSample A)` — Accumulates center sample. _[#if GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_JIMENEZ2014]_
- L449-452 _function_ `void AccumulateCenterSampleAsItsOwnRing(inout FGatherAccumulator Accumulator, in FGatherSample A)` _[#if GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_JIMENEZ2014]_
- L455-461 _function_ `void AmendAccumulatedRingsWeight( inout FGatherAccumulator Accumulator, in FGatherInputParameters NewGatherParameters, float AccumulatedWeightMultiplier)` — Changes the already accumulated weight, used when doing varying gathering sample density. _[#if GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_JIMENEZ2014]_
- L463-466 _function_ `void StartRingSamples(inout FGatherAccumulator Accumulator, in FGatherRingInfos RingInfos)` _[#if GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_JIMENEZ2014]_
- L469-499 _function_ `void AccumulateMirrorSamples(inout FGatherAccumulator Accumulator, in FGatherSample A, in FGatherSample B)` — Accumulates mirror samples. _[#if GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_JIMENEZ2014]_
- L501-504 _function_ `void EndRingSamples(inout FGatherAccumulator Accumulator, in FGatherRingInfos RingInfos)` _[#if GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_JIMENEZ2014]_
- L507-557 _function_ `void ResolveAccumulatorOutputs( in FGatherAccumulator Accumulator, in FGatherResolveInfos GatherResolveInfos, out FAccumulatorOutput Output)` — Resolves the foreground layer output from the accumulator. _[#if GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_JIMENEZ2014]_
- L620-686 _function_ `void AccumulateSample(inout FGatherAccumulator Accumulator, in FGatherSample A, float Weight)` — Accumulates sample. _[#if GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_RINGBINNING]_
- L689-717 _function_ `void MergeCurrentBucketIntoPreviousBucket(inout FGatherAccumulator Accumulator, float SampleCount)` — Merge current bucket into the previous bucket. _[#if GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_RINGBINNING]_
- L720-724 _function_ `void AccumulateCenterSample(inout FGatherAccumulator Accumulator, in FGatherSample A)` — Like mirror samples. _[#if GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_RINGBINNING]_
- L727-742 _function_ `void AccumulateCenterSampleAsItsOwnRing(inout FGatherAccumulator Accumulator, in FGatherSample A)` — Accumulates center sample as it s own ring potentially occluding previous ring instead of between StartRingSamples() and EndRingSamples(). _[#if GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_RINGBINNING]_
- L745-755 _function_ `void AmendAccumulatedRingsWeight( inout FGatherAccumulator Accumulator, in FGatherInputParameters NewGatherParameters, float AccumulatedWeightMultiplier)` — Changes the already accumulated weight, used when doing varying gathering sample density. _[#if GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_RINGBINNING]_
- L758-772 _function_ `void StartRingSamples(inout FGatherAccumulator Accumulator, in FGatherRingInfos RingInfos)` — Setup up the accumulator for a ring. _[#if GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_RINGBINNING]_
- L775-785 _function_ `void AccumulateMirrorSamples(inout FGatherAccumulator Accumulator, in FGatherSample A, in FGatherSample B)` — Accumulates mirror samples. _[#if GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_RINGBINNING]_
- L788-809 _function_ `void EndRingSamples(inout FGatherAccumulator Accumulator, in FGatherRingInfos RingInfos)` — Digests all samples accumulated for the ring. _[#if GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_RINGBINNING]_
- L812-829 _function_ `void ResolveAccumulatorOutputs( in FGatherAccumulator Accumulator, in FGatherResolveInfos GatherResolveInfos, out FAccumulatorOutput Output)` — Resolves the background layer output from the accumulator. _[#if GATHER_ACCUMULATOR_METHOD == GATHER_ACCUMULATOR_METHOD_RINGBINNING]_

### `Shaders/Private/DiaphragmDOF/DOFGatherCommon.ush` (Private)

- lines: 451; parse: all-branches
- includes: L10 `DOFCommon.ush`, L11 `DOFCocTileCommon.ush`

#### Macros (#define, 69)

- L18 `#define DEBUG_FORCE_LOW_RING_COUNT 0`
- L19 `#define DEBUG_NO_FAST_ACCUMULATOR 0`
- L22 `#define DEBUG_FAST_ACCUMULATOR 0`
- L25 `#define DEBUG_NO_RANDOM_OFFSET 0`
- L28 `#define DEBUG_FORCE_GATHER_HIGHEST_MIP_LEVEL 0`
- L34 `#define GATHER_QUALITY_LOW_QUALITY 0`
- L35 `#define GATHER_QUALITY_HIGH_QUALITY 1`
- L36 `#define GATHER_QUALITY_SCATTER_OCCLUSION_OUTPUT 2`
- L37 `#define GATHER_QUALITY_CINEMATIC 3`
- L44 `#define GATHER_ACCUMULATOR_METHOD_SIMPLE 0`
- L47 `#define GATHER_ACCUMULATOR_METHOD_JIMENEZ2014 1`
- L50 `#define GATHER_ACCUMULATOR_METHOD_RINGBINNING 2`
- L55 `#define KERNEL_LAYOUT_SCALABLE_DISK 0`
- L58 `#define KERNEL_LAYOUT_ALIGNED_SQUARE 1`
- L63 `#define KERNEL_DENSITY_CONSTANT 0`
- L64 `#define KERNEL_DENSITY_CONSTANT_HEXAWEB 1`
- L69 `#define KERNEL_DENSITY_HIGHER_IN_CENTER_DISK 2`
- L73 `#define KERNEL_DENSITY_LOWER_IN_CENTER_HEXAWEB 3`
- L76 `#define KERNEL_DENSITY_RECURSIVE_DISKS 4`
- L79 `#define KERNEL_DENSITY_CONSTANT_DYNAMIC_RING_COUNT 5`
- L84 `#define MIP_LEVEL_METHOD_INTERLEAVED_OFFSET 0`
- L87 `#define MIP_LEVEL_METHOD_CONSERVATIVE_NO_RANDOM 1`
- L94 `#define GATHER_ACCUMULATOR_METHOD (GATHER_ACCUMULATOR_METHOD_JIMENEZ2014)` _[#if DIM_LAYER_PROCESSING == LAYER_PROCESSING_FOREGROUND_ONLY]_
- L95 `#define CONFIG_ENABLE_FAST_ACCUMULATOR 1` _[#if DIM_LAYER_PROCESSING == LAYER_PROCESSING_FOREGROUND_ONLY]_
- L98 `#define GATHER_ACCUMULATOR_METHOD (GATHER_ACCUMULATOR_METHOD_SIMPLE)` _[#if !(DIM_LAYER_PROCESSING == LAYER_PROCESSING_FOREGROUND_ONLY) && DIM_LAYER_PROCESSING == LAYER_PROCESSING_FOREGROUND_HOLE_FILLING]_
- L101 `#define GATHER_ACCUMULATOR_METHOD (GATHER_ACCUMULATOR_METHOD_RINGBINNING)` _[#if !(DIM_LAYER_PROCESSING == LAYER_PROCESSING_FOREGROUND_ONLY) && !(DIM_LAYER_PROCESSING == LAYER_PROCESSING_FOREGROUND_HOLE_FILLING) && DIM_LAYER_PROCESSING == LAYER_PROCESSING_BACKGROUND_ONLY]_
- L102 `#define CONFIG_ENABLE_FAST_ACCUMULATOR 1` _[#if !(DIM_LAYER_PROCESSING == LAYER_PROCESSING_FOREGROUND_ONLY) && !(DIM_LAYER_PROCESSING == LAYER_PROCESSING_FOREGROUND_HOLE_FILLING) && DIM_LAYER_PROCESSING == LAYER_PROCESSING_BACKGROUND_ONLY]_
- L105 `#define CONFIG_POINT_MIRROR_BOKEH -1` _[#if !(DIM_LAYER_PROCESSING == LAYER_PROCESSING_FOREGROUND_ONLY) && !(DIM_LAYER_PROCESSING == LAYER_PROCESSING_FOREGROUND_HOLE_FILLING) && DIM_LAYER_PROCESSING == LAYER_PROCESSING_BACKGROUND_ONLY]_
- L109 `#define CONFIG_KERNEL_SAMPLING_DENSITY_DRIVER 1` _[#if !(DIM_LAYER_PROCESSING == LAYER_PROCESSING_FOREGROUND_ONLY) && !(DIM_LAYER_PROCESSING == LAYER_PROCESSING_FOREGROUND_HOLE_FILLING) && DIM_LAYER_PROCESSING == LAYER_PROCESSING_BACKGROUND_ONLY]_
- L112 `#define CONFIG_COC_RADIUS_CORRECTION 1` _[#if !(DIM_LAYER_PROCESSING == LAYER_PROCESSING_FOREGROUND_ONLY) && !(DIM_LAYER_PROCESSING == LAYER_PROCESSING_FOREGROUND_HOLE_FILLING) && DIM_LAYER_PROCESSING == LAYER_PROCESSING_BACKGROUND_ONLY]_
- L115 `#define GATHER_ACCUMULATOR_METHOD (GATHER_ACCUMULATOR_METHOD_SIMPLE)` _[#if !(DIM_LAYER_PROCESSING == LAYER_PROCESSING_FOREGROUND_ONLY) && !(DIM_LAYER_PROCESSING == LAYER_PROCESSING_FOREGROUND_HOLE_FILLING) && !(DIM_LAYER_PROCESSING == LAYER_PROCESSING_BACKGROUND_ONLY) && ...]_
- L118 `#define CONFIG_KERNEL_LAYOUT (KERNEL_LAYOUT_ALIGNED_SQUARE)` _[#if !(DIM_LAYER_PROCESSING == LAYER_PROCESSING_FOREGROUND_ONLY) && !(DIM_LAYER_PROCESSING == LAYER_PROCESSING_FOREGROUND_HOLE_FILLING) && !(DIM_LAYER_PROCESSING == LAYER_PROCESSING_BACKGROUND_ONLY) && ...]_
- L127 `#define CONFIG_ACCUMULATOR_FULL_ALU 0` _[#if DIM_GATHER_QUALITY == GATHER_QUALITY_LOW_QUALITY]_
- L128 `#define CONFIG_FAST_ACCUMULATOR_RING_COUNT ((DIM_GATHER_RING_COUNT) - 1)` _[#if DIM_GATHER_QUALITY == GATHER_QUALITY_LOW_QUALITY]_
- L129 `#define CONFIG_FAST_ACCUMULATOR_KERNEL_DENSITY (KERNEL_DENSITY_CONSTANT_HEXAWEB)` _[#if DIM_GATHER_QUALITY == GATHER_QUALITY_LOW_QUALITY]_
- L133 `#define CONFIG_SLIGHT_RING_ROTATION 1` _[#if DIM_GATHER_QUALITY == GATHER_QUALITY_LOW_QUALITY]_
- L136 `#define CONFIG_WEIGHT_SAMPLE_FROM_COC 1` _[#if !(DIM_GATHER_QUALITY == GATHER_QUALITY_LOW_QUALITY) && DIM_GATHER_QUALITY == GATHER_QUALITY_HIGH_QUALITY]_
- L137 `#define CONFIG_MIRRORED_SAMPLER 1` _[#if !(DIM_GATHER_QUALITY == GATHER_QUALITY_LOW_QUALITY) && DIM_GATHER_QUALITY == GATHER_QUALITY_HIGH_QUALITY]_
- L138 `#define CONFIG_PETZVAL 1` _[#if !(DIM_GATHER_QUALITY == GATHER_QUALITY_LOW_QUALITY) && DIM_GATHER_QUALITY == GATHER_QUALITY_HIGH_QUALITY]_
- L141 `#define CONFIG_WEIGHT_SAMPLE_FROM_COC 1` _[#if !(DIM_GATHER_QUALITY == GATHER_QUALITY_LOW_QUALITY) && !(DIM_GATHER_QUALITY == GATHER_QUALITY_HIGH_QUALITY) && DIM_GATHER_QUALITY == GATHER_QUALITY_SCATTER_OCCLUSION_OUTPUT]_
- L142 `#define CONFIG_GENERATE_SCATTER_OCCLUSION_BUFFER 1` _[#if !(DIM_GATHER_QUALITY == GATHER_QUALITY_LOW_QUALITY) && !(DIM_GATHER_QUALITY == GATHER_QUALITY_HIGH_QUALITY) && DIM_GATHER_QUALITY == GATHER_QUALITY_SCATTER_OCCLUSION_OUTPUT]_
- L143 `#define CONFIG_MIRRORED_SAMPLER 1` _[#if !(DIM_GATHER_QUALITY == GATHER_QUALITY_LOW_QUALITY) && !(DIM_GATHER_QUALITY == GATHER_QUALITY_HIGH_QUALITY) && DIM_GATHER_QUALITY == GATHER_QUALITY_SCATTER_OCCLUSION_OUTPUT]_
- L144 `#define CONFIG_PETZVAL 1` _[#if !(DIM_GATHER_QUALITY == GATHER_QUALITY_LOW_QUALITY) && !(DIM_GATHER_QUALITY == GATHER_QUALITY_HIGH_QUALITY) && DIM_GATHER_QUALITY == GATHER_QUALITY_SCATTER_OCCLUSION_OUTPUT]_
- L147 `#define CONFIG_WEIGHT_SAMPLE_FROM_COC 1` _[#if !(DIM_GATHER_QUALITY == GATHER_QUALITY_LOW_QUALITY) && !(DIM_GATHER_QUALITY == GATHER_QUALITY_HIGH_QUALITY) && !(DIM_GATHER_QUALITY == GATHER_QUALITY_SCATTER_OCCLUSION_OUTPUT) && DIM_GATHER_QUALITY...]_
- L148 `#define CONFIG_GENERATE_SCATTER_OCCLUSION_BUFFER 1` _[#if !(DIM_GATHER_QUALITY == GATHER_QUALITY_LOW_QUALITY) && !(DIM_GATHER_QUALITY == GATHER_QUALITY_HIGH_QUALITY) && !(DIM_GATHER_QUALITY == GATHER_QUALITY_SCATTER_OCCLUSION_OUTPUT) && DIM_GATHER_QUALITY...]_
- L149 `#define CONFIG_MIRRORED_SAMPLER 1` _[#if !(DIM_GATHER_QUALITY == GATHER_QUALITY_LOW_QUALITY) && !(DIM_GATHER_QUALITY == GATHER_QUALITY_HIGH_QUALITY) && !(DIM_GATHER_QUALITY == GATHER_QUALITY_SCATTER_OCCLUSION_OUTPUT) && DIM_GATHER_QUALITY...]_
- L150 `#define CONFIG_LAYER_GATHERING 1` _[#if !(DIM_GATHER_QUALITY == GATHER_QUALITY_LOW_QUALITY) && !(DIM_GATHER_QUALITY == GATHER_QUALITY_HIGH_QUALITY) && !(DIM_GATHER_QUALITY == GATHER_QUALITY_SCATTER_OCCLUSION_OUTPUT) && DIM_GATHER_QUALITY...]_
- L151 `#define CONFIG_PETZVAL 1` _[#if !(DIM_GATHER_QUALITY == GATHER_QUALITY_LOW_QUALITY) && !(DIM_GATHER_QUALITY == GATHER_QUALITY_HIGH_QUALITY) && !(DIM_GATHER_QUALITY == GATHER_QUALITY_SCATTER_OCCLUSION_OUTPUT) && DIM_GATHER_QUALITY...]_
- L159 `#define CONFIG_GATHER_INPUT_LAYOUT (GATHER_INPUT_LAYOUT_RGB_ALPHA_COC)` _[#if CONFIG_DOF_ALPHA]_
- L161 `#define CONFIG_GATHER_INPUT_LAYOUT (GATHER_INPUT_LAYOUT_RGB_SEPARATE_COC)` _[#if !(CONFIG_DOF_ALPHA) && DIM_RGB_COLOR_BUFFER]_
- L163 `#define CONFIG_GATHER_INPUT_LAYOUT (GATHER_INPUT_LAYOUT_RGB_COC)` _[#if !(CONFIG_DOF_ALPHA) && !(DIM_RGB_COLOR_BUFFER)]_
- L172 `#define CONFIG_ENABLE_FAST_ACCUMULATOR 0` _[#if !defined(CONFIG_ENABLE_FAST_ACCUMULATOR)]_
- L177 `#define CONFIG_FAST_ACCUMULATOR_KERNEL_DENSITY (KERNEL_DENSITY_CONSTANT)` _[#if !defined(CONFIG_FAST_ACCUMULATOR_KERNEL_DENSITY)]_
- L184 `#define CONFIG_FAST_ACCUMULATOR_RING_COUNT (DIM_GATHER_RING_COUNT)` _[#if !defined(CONFIG_FAST_ACCUMULATOR_RING_COUNT)]_
- L189 `#define CONFIG_KERNEL_SAMPLING_DENSITY_DRIVER 0` _[#if !defined(CONFIG_KERNEL_SAMPLING_DENSITY_DRIVER)]_
- L194 `#define CONFIG_MIP_LEVEL_METHOD (MIP_LEVEL_METHOD_INTERLEAVED_OFFSET)` _[#if !defined(CONFIG_MIP_LEVEL_METHOD)]_
- L199 `#define CONFIG_KERNEL_LAYOUT (KERNEL_LAYOUT_SCALABLE_DISK)` _[#if !defined(CONFIG_KERNEL_LAYOUT)]_
- L203 `#define CONFIG_SGPR_HINTS 1`
- L206 `#define CONFIG_CLAMP_INPUT_BUFFER_UV 1`
- L210 `#define CONFIG_GENERATE_SCATTER_OCCLUSION_BUFFER 0` _[#if !defined(CONFIG_GENERATE_SCATTER_OCCLUSION_BUFFER)]_
- L215 `#define CONFIG_WEIGHT_SAMPLE_FROM_COC 0` _[#if !defined(CONFIG_WEIGHT_SAMPLE_FROM_COC)]_
- L220 `#define CONFIG_ACCUMULATOR_FULL_ALU 1` _[#if !defined(CONFIG_ACCUMULATOR_FULL_ALU)]_
- L225 `#define CONFIG_POINT_MIRROR_BOKEH 1` _[#if !defined(CONFIG_POINT_MIRROR_BOKEH)]_
- L230 `#define CONFIG_MIRRORED_SAMPLER 0` _[#if !defined(CONFIG_MIRRORED_SAMPLER)]_
- L235 `#define CONFIG_COC_RADIUS_CORRECTION 0` _[#if !defined(CONFIG_COC_RADIUS_CORRECTION)]_
- L240 `#define CONFIG_MAX_SAMPLING_DENSITY_CHANGES 3` _[#if !defined(CONFIG_MAX_SAMPLING_DENSITY_CHANGES)]_
- L246 `#define CONFIG_SLIGHT_RING_ROTATION 0` _[#if !defined(CONFIG_SLIGHT_RING_ROTATION)]_
- L251 `#define CONFIG_LAYER_GATHERING 0` _[#if !defined(CONFIG_LAYER_GATHERING)]_
- L268 `#define GROUP_SIZE_IS_LARGER_THAN_COC_TILE_SIZE 0`
- L8 #pragma `once`

#### Structs / classes (6)

- L288-298 _struct_ **`FLargerConvolution`** `struct FLargerConvolution` — Gather input generally from larger gathering radius.
  - L291 _member_ `float4 Color;` — Gathered color.
  - L294 _member_ `float Weight;` — Weight of the color.
  - L297 _member_ `float2 CocAvgAndSquareAvg;` — Coc average and squared average.
- L301-348 _struct_ **`FGatherInputParameters`** `struct FGatherInputParameters` — Gathering parameters.
  - L304 _member_ `uint MaxRingCount;` — Compile time maximum number of rings to gather.
  - L307 _member_ `uint RingCount;` — Runtime number of rings to gather <= MaxRingCount.
  - L310 _member_ `float2 InputBufferCenterUV;` — buffer UV coordinate of the center of the kernel to gather.
  - L312 _member_ `float2 ViewportUV;`
  - L315 _member_ `float2 DispatchThreadIdToInputBufferUV;` — Multiplication factors to map DispatchThreadID -> InputBufferUV.
  - L318 _member_ `float KernelRadius;` — Radius of the kernel at half res pixels.
  - L321 _member_ `float Random[2];` — Random signals
  - L324 _member_ `bool bFastGathering;` — Whether going to use accumulator or fast accumulator.
  - L327 _member_ `float ClosestCocRadius;` — The Coc radius that is the closest to the camera.
  - L330 _member_ `float2 ConsiderCocRadiusAffineTransformation0;` — Saturated affine transformation.
  - L331 _member_ `float2 ConsiderCocRadiusAffineTransformation1;`
  - L332 _member_ `float2 ConsiderAbsCocRadiusAffineTransformation;`
  - L335 _member_ `float MaxRecombineAbsCocRadius;` — TODO: clean that with CocRadiusMinMaxBoundaries
  - L338 _member_ `uint KernelSamplingDensityMode;` — Sampling density compile time mode. KERNEL_DENSITY_*
  - L341 _member_ `uint DensityChangeRingCount;` — Compile time number of rings for density changes.
  - L344 _member_ `uint MaxDensityChangeCount;` — Compile time max number of density changes allowed.
  - L347 _member_ `float MinIntersectableCocRadiusAbs;` — Tile constant about what is the smallest intersectable radius.
- L351-367 _struct_ **`FGatherRingInfos`** `struct FGatherRingInfos` — Informations about a ring.
  - L354 _member_ `uint RingId;` — Id of the ring. 0 is the smallest ring after the center sample.
  - L357 _member_ `uint SampleCount;` — Total number of samples on the ring.
  - L360 _member_ `bool bIsFirstRing;` — Compile time constant on whether this is the first accumualted ring.
  - L363 _member_ `float Weight;` — Total weight of the ring.
  - L366 _member_ `float Radius;` — Radius of the ring in pixels from the center of the kernel.
- L370-375 _struct_ **`FGatherResolveInfos`** `struct FGatherResolveInfos` — Informations about the kernel when the accumulator resolves.
  - L374 _member_ `float SamplesCount;` — Number of accumulated samples. This is a float because of density changes that can happen with AmendAccumulatedRingsWeight().
- L378-391 _struct_ **`FGatherSample`** `struct FGatherSample` — Structs that holds data about a sample for gathering.
  - L381 _member_ `float4 Color;` — Sample's scene color (and optionally alpha channel).
  - L384 _member_ `float CocRadius;` — Sample's radius of the Coc
  - L387 _member_ `float Distance;` — Sample distance from center of kernel, in CocRadius unit.
  - L390 _member_ `float Intersection;` — Sample's intersection.
- L394-418 _struct_ **`FAccumulatorOutput`** `struct FAccumulatorOutput` — Gathering accumulator output.
  - L397 _member_ `float4 ForegroundColor;` — Foreground color.
  - L400 _member_ `float ForegroundAlpha;` — Foreground alpha channel to use to compose on in focus and background.
  - L403 _member_ `float4 ForegroundHoleFillingColor;` — Foreground hole filling color and alpha.
  - L404 _member_ `float ForegroundHoleFillingAlpha;`
  - L407 _member_ `float4 BackgroundColor;` — Background color.
  - L410 _member_ `float BackgroundWeight;` — Weight of the backrgound.
  - L413 _member_ `float2 BackgroundCocAvgAndSquareAvg;` — Coc average and variance for background.
  - L416 _member_ `float4 SlightFocusColor;` — Slight out of focus color and opacity.
  - L417 _member_ `float SlightFocusOpacity;`

#### Functions (3)

- L273-282 _function_ `float ComputeSampleWeight(float CocRadius)` — Compute sample weight according's to its Coc radius.
- L425-434 _function_ `float IsConsideredCocRadius(in const FGatherInputParameters GatherParameters, float SampleCocRadius)` — Returns whether this Coc radius is considered or not for this pass. If not considered, it means this Coc radius will be gathered at higher or lower resolution gathering pass.
- L437-450 _function_ `FAccumulatorOutput CreateAccumulatorOutput()`

### `Shaders/Private/DiaphragmDOF/DOFGatherKernel.ush` (Private)

- lines: 1045; parse: all-branches
- includes: L9 `DOFGatherCommon.ush`, L10 `DOFGatherAccumulator.ush`

#### Macros (#define, 1)

- L32 `#define LARGEST_RINGS_FIRST 0` _[#if !defined(LARGEST_RINGS_FIRST)]_
- L7 #pragma `once`

#### Structs / classes (2)

- L70-74 _struct_ **`FFastAccumulatorOutput`** `struct FFastAccumulatorOutput`
  - L73 _member_ `float4 Color;` — Accumulated Color.
- L83-115 _struct_ **`FPrivateKernelSharedScope`** `struct FPrivateKernelSharedScope` — Shared scope with the different functions of the kernel.
  - L88 _member_ `bool bBilinearSampleInput;` — sampler to use.
  - L91 _member_ `bool bKenrelHasEnoughSamples;` — Whether the kernel has enough samples enought sample to do the entire convolution (use by slight out of focus).
  - L97 _member_ `float2 KernelCenterUV;` — UV coordinate of the kernel center in GatherInput.
  - L101 _member_ `float SampleCountToSamplePosition;` — Multiplier to transform sample count unit to sample position in pixels of GatherInput's mip level 0. Set at compile time to 1 when bKenrelHasEnoughSamples==true.
  - L104 _member_ `float GatherInputMipLevel;` — Sampling mip level for GatherInput.
  - L108 _member_ `float2 GatherInputMaxUV;` — GatherInput's max UVs. TODO: this is currently MipLevel  depent, but could save some VGPR by making it independent.
  - L111 _member_ `float IntersectionMultiplier;` — Multiplier to apply when computing sample intersection. Higher value sharpen, lower value feather.
  - L114 _member_ `float2x2 PetzvalTransform;` — Used to stretch sample positions for petzval lens effect

#### Global resources (textures / buffers / samplers) (3)

- L18 _resource_ `Texture2D GatherInput_SceneColor;`
- L19 _resource_ `Texture2D GatherInput_SeparateCoc;`
- L21 _resource_ `Texture2D BokehLUT;`

#### Global parameters (uniforms) (7)

- L15 _parameter_ `float4 ViewportSize;`
- L16 _parameter_ `float4 GatherInputSize;`
- L17 _parameter_ `float2 GatherInputViewportSize;`
- L23 _parameter_ `float Petzval;`
- L24 _parameter_ `float PetzvalFalloffPower;`
- L25 _parameter_ `float2 PetzvalExclusionBoxExtents;`
- L26 _parameter_ `float PetzvalExclusionBoxRadius;`

#### Functions (13)

- L37-54 _function_ `float2 GetDiskSampleOnUnitCirle(uint RingId, uint RingSampleIteration, uint RingSampleId)` — Returns the position of the sample on the unit circle (radius = 1) for a given ring.
- L57-67 _function_ `float2x2 GetSampleRotationMatrix(uint RingSampleIteration)` — Returns the rotation matrix to use between sample of the ring.
- L77-80 _function_ `void AmendAccumulatedRingsWeight(inout FFastAccumulatorOutput FastAccumulator, const float AccumulatedWeightMultiplier)` — Amends the weight of the previously accumulated samples in the fast accumulator.
- L120-155 _function_ `float ComputeSampleIntersection(FPrivateKernelSharedScope KernelScope, float SampleCocRadius, float SampleDistance)` — Computes intersection of sample from its Coc and its distance. Returns 0: no intersection, 1: intersection.
- L159-169 _function_ `uint GetRingSamplingPairCount(const uint KernelSamplingDensityMode, uint RingId)` — Returns the total number of sampling iteration for a given ring id.
- L172-182 _function_ `uint GetKernelSampleCount(const uint KernelSamplingDensityMode, uint RingCount)` — Returns the total number of sample of the kernel.
- L186-246 _function_ `FGatherSample FetchGatherSample(in FPrivateKernelSharedScope KernelScope, float2 SampleUV)` — Fetch and unpack a sample from GatherInput.
- L250-361 _function_ `void UpdateRuntimeKernelScope( in FGatherInputParameters GatherParameters, inout FPrivateKernelSharedScope KernelScope)` — Update run time kernel scope's members from compile time one, and gather parameters.
- L368-380 _function_ `float2 ApplyApproxPetzval(in FPrivateKernelSharedScope KernelScope, float2 SampleUV)` — Apply approximate Petzval bokeh lens effect. A more precise version would calculate the transform per sample, rather than per kernel. This version assumes the bokeh that are gathered are all centered on the kernel center, rather than on the sample center. This is incorrect and can cause bokeh to stretch into a 'banana shape', rather than oval. But it's significantly faster and usually not noticeable (more prominent bokeh are scattered anyway).
- L383-398 _function_ `float2 SampleConstFromBatchConst(const uint BatchSampleId, float2 BatchConst)` — Transform at compile time a 2 dimensional batch's constant into sample pair constant, by using rotation invariance.
- L402-606 _function_ `void GatherRingSamples( in FGatherInputParameters GatherParameters, in FPrivateKernelSharedScope KernelScope, in uint RingId, in bool bIsFirstRing, inout FGatherAccumulator Accumulator, inout FFastAccumulatorOutput FastAccumulator)` — Gather a ring into the accumulator.
- L609-649 _function_ `void GatherRing( in FGatherInputParameters GatherParameters, in FPrivateKernelSharedScope KernelScope, in uint RingId, in bool bIsFirstRing, inout FGatherAccumulator Accumulator, inout FFastAccumulatorOutput FastAccumulator)` — Gather a ring into the accumulator.
- L652-1044 _function_ `uint GatherSamplesAndResolve( in FGatherInputParameters GatherParameters, in FGatherAccumulator Accumulator, out FAccumulatorOutput AccumulatorOutput, out FFastAccumulatorOutput FastAccumulator)` — Gathers samples with an preconfigured accumulator and resolve its output.

### `Shaders/Private/DiaphragmDOF/DOFGatherPass.usf` (Private)

- lines: 467; parse: all-branches
- includes: L7 `DOFGatherCommon.ush`, L8 `DOFGatherAccumulator.ush`, L9 `DOFGatherKernel.ush`, L10 `DOFGatherTileSuggest.ush`

#### Macros (#define, 3)

- L15 `#define THREADGROUP_SIZEX (COC_TILE_SIZE)`
- L16 `#define THREADGROUP_SIZEY (THREADGROUP_SIZEX)`
- L17 `#define THREADGROUP_TOTALSIZE (THREADGROUP_SIZEX * THREADGROUP_SIZEY)`

#### Entry points (1)

- L150-466 _entry_ `[numthreads(THREADGROUP_SIZEX, THREADGROUP_SIZEY, 1)] void GatherMainCS( uint2 DispatchThreadId : SV_DispatchThreadID, uint2 GroupId : SV_GroupID)` — stage: **compute** — C++: `FDiaphragmDOFGatherCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/DiaphragmDOF.cpp:1474)

#### Global resources (textures / buffers / samplers) (5)

- L39 _resource_ `Texture2D TileClassification_Foreground;`
- L40 _resource_ `Texture2D TileClassification_Background;`
- L45 _resource_ `RWTexture2D<float4> ConvolutionOutput_SceneColor;`
- L46 _resource_ `RWTexture2D<float4> ConvolutionOutput_SeparateAlpha;`
- L49 _resource_ `RWTexture2D<float4> ScatterOcclusionOutput;` _[#if CONFIG_GENERATE_SCATTER_OCCLUSION_BUFFER]_

#### Global parameters (uniforms) (9)

- L23 _parameter_ `float2 TemporalJitterPixels;` — Frame's temporal offset in pixels.
- L26 _parameter_ `float MipBias;` — Mip bias for the gathering kernel.
- L28 _parameter_ `uint4 ViewportRect;`
- L29 _parameter_ `float2 DispatchThreadIdToInputBufferUV;`
- L30 _parameter_ `float MaxRecombineAbsCocRadius;`
- L33 _parameter_ `float2 ConsiderCocRadiusAffineTransformation0;` — Affine transformation to consider the CocRadius.
- L34 _parameter_ `float2 ConsiderCocRadiusAffineTransformation1;`
- L35 _parameter_ `float2 ConsiderAbsCocRadiusAffineTransformation;`
- L37 _parameter_ `float2 InputBufferUVToOutputPixel;`

#### groupshared (1)

- L145 _groupshared_ `groupshared uint RequiresAccurateGather;`

#### Functions (1)

- L61-140 _function_ `void StoreAccumulatorOutput(in uint2 OutputPixelPosition, in FAccumulatorOutput AccumulatorOutput)` — Store the accumulator output to RWTexture. This is implemented as separate function to be called in different branch of GatherMainCS to help the compiler reduce VGPR pressure that is critical for this amount of samples.

### `Shaders/Private/DiaphragmDOF/DOFGatherTileSuggest.ush` (Private)

- lines: 143; parse: all-branches
- includes: L10 `DOFCocTileCommon.ush`
- L8 #pragma `once`

#### Structs / classes (1)

- L21-40 _struct_ **`FGatheringTileSuggestion`** `struct FGatheringTileSuggestion`
  - L24 _member_ `bool bCanEarlyReturn;` — True when we know from coc tile that there is no gathering.
  - L27 _member_ `bool bCanDofastGathering;` — True when we can use fast gather accumulator.
  - L30 _member_ `float MinCocRadiusAbs;` — Smallest absolute coc radius
  - L33 _member_ `float MinIntersectableCocRadiusAbs;` — Smallest absolute coc radius
  - L36 _member_ `float MaxCocRadiusAbs;` — Largest absolute coc radius
  - L39 _member_ `float ClosestCocRadius;` — Coc radius the closest from the camera.

#### Global parameters (uniforms) (2)

- L15 _parameter_ `float MinGatherRadius;`
- L16 _parameter_ `float SlightOutOfFocusRadiusBoundary;`

#### Functions (1)

- L44-142 _function_ `FGatheringTileSuggestion InferGatherTileSuggestion( in FCocTileSample CocTileInfos, const uint LayerProcessing)` — Infers the gather processing to do from coc tile buffer sample, for a given LayerProcessing.

### `Shaders/Private/DiaphragmDOF/DOFHybridScatterCommon.ush` (Private)

- lines: 103; parse: all-branches
- includes: L8 `DOFCommon.ush`

#### Macros (#define, 28)

- L17 `#define DEBUG_HYBRID_SCATTERING_SPRITE 0`
- L24 `#define BOKEH_DRAW_METHOD_TRIANGLE 0`
- L27 `#define BOKEH_DRAW_METHOD_INDEXED_TRIANGLE 1`
- L30 `#define BOKEH_DRAW_METHOD_RECT 2`
- L37 `#define HYBRID_SCATTERING_GROUP_BORDER_SIZE 2`
- L41 `#define PIXEL_COUNT_PER_SCATTER_GROUP (HYBRID_SCATTERING_GROUP_BORDER_SIZE * HYBRID_SCATTERING_GROUP_BORDER_SIZE)`
- L44 `#define VIGNETTE_DATA_PER_PIXEL (2)`
- L46 `#define SCATTER_DRAW_LIST_DATA_PER_PIXEL (1 + VIGNETTE_DATA_PER_PIXEL)`
- L49 `#define SCATTER_DRAW_LIST_GROUP_STRIDE (1 + (PIXEL_COUNT_PER_SCATTER_GROUP * SCATTER_DRAW_LIST_DATA_PER_PIXEL))`
- L54 `#define BOKEH_DRAW_METHOD (BOKEH_DRAW_METHOD_RECT)` _[#if PLATFORM_SUPPORTS_RECT_LIST]_
- L56 `#define BOKEH_DRAW_METHOD (BOKEH_DRAW_METHOD_INDEXED_TRIANGLE)` _[#if !(PLATFORM_SUPPORTS_RECT_LIST)]_
- L62 `#define ANTI_ALIASING_FEATHER_OFFSET 0.5`
- L65 `#define SCATTERING_GROUP_PACKING 1`
- L68 `#define TAYLOR_EXPENDED_COC_INTERSECTION 1`
- L71 `#define VERTEX_SHADER_INVOCATION_TARGET 64`
- L78 `#define VERTEX_PER_SCATTERING_GROUP 6` _[#if BOKEH_DRAW_METHOD == BOKEH_DRAW_METHOD_TRIANGLE]_
- L79 `#define VERTEX_SHADER_INVOCATION_PER_SCATTERING_GROUP 6` _[#if BOKEH_DRAW_METHOD == BOKEH_DRAW_METHOD_TRIANGLE]_
- L80 `#define SCATTERING_INDIRECT_PARAMETER_SIZE (DRAW_INDIRECT_UINT_COUNT)` _[#if BOKEH_DRAW_METHOD == BOKEH_DRAW_METHOD_TRIANGLE]_
- L83 `#define VERTEX_PER_SCATTERING_GROUP 6` _[#if !(BOKEH_DRAW_METHOD == BOKEH_DRAW_METHOD_TRIANGLE) && BOKEH_DRAW_METHOD == BOKEH_DRAW_METHOD_INDEXED_TRIANGLE]_
- L84 `#define VERTEX_SHADER_INVOCATION_PER_SCATTERING_GROUP 4` _[#if !(BOKEH_DRAW_METHOD == BOKEH_DRAW_METHOD_TRIANGLE) && BOKEH_DRAW_METHOD == BOKEH_DRAW_METHOD_INDEXED_TRIANGLE]_
- L85 `#define SCATTERING_INDIRECT_PARAMETER_SIZE (DRAW_INDEXED_INDIRECT_UINT_COUNT)` _[#if !(BOKEH_DRAW_METHOD == BOKEH_DRAW_METHOD_TRIANGLE) && BOKEH_DRAW_METHOD == BOKEH_DRAW_METHOD_INDEXED_TRIANGLE]_
- L88 `#define VERTEX_PER_SCATTERING_GROUP 3` _[#if !(BOKEH_DRAW_METHOD == BOKEH_DRAW_METHOD_TRIANGLE) && !(BOKEH_DRAW_METHOD == BOKEH_DRAW_METHOD_INDEXED_TRIANGLE) && BOKEH_DRAW_METHOD == BOKEH_DRAW_METHOD_RECT]_
- L89 `#define VERTEX_SHADER_INVOCATION_PER_SCATTERING_GROUP 3` _[#if !(BOKEH_DRAW_METHOD == BOKEH_DRAW_METHOD_TRIANGLE) && !(BOKEH_DRAW_METHOD == BOKEH_DRAW_METHOD_INDEXED_TRIANGLE) && BOKEH_DRAW_METHOD == BOKEH_DRAW_METHOD_RECT]_
- L90 `#define SCATTERING_INDIRECT_PARAMETER_SIZE (DRAW_INDIRECT_UINT_COUNT)` _[#if !(BOKEH_DRAW_METHOD == BOKEH_DRAW_METHOD_TRIANGLE) && !(BOKEH_DRAW_METHOD == BOKEH_DRAW_METHOD_INDEXED_TRIANGLE) && BOKEH_DRAW_METHOD == BOKEH_DRAW_METHOD_RECT]_
- L98 `#define CONFIG_PETZVAL 0` _[#if DIM_SCATTER_QUALITY == SCATTER_QUALITY_MEDIUM]_
- L99 `#define CONFIG_VIGNETTE 0` _[#if DIM_SCATTER_QUALITY == SCATTER_QUALITY_MEDIUM]_
- L101 `#define CONFIG_PETZVAL 1` _[#if !(DIM_SCATTER_QUALITY == SCATTER_QUALITY_MEDIUM) && DIM_SCATTER_QUALITY == SCATTER_QUALITY_HIGH]_
- L102 `#define CONFIG_VIGNETTE 1` _[#if !(DIM_SCATTER_QUALITY == SCATTER_QUALITY_MEDIUM) && DIM_SCATTER_QUALITY == SCATTER_QUALITY_HIGH]_

### `Shaders/Private/DiaphragmDOF/DOFHybridScatterCompilation.usf` (Private)

- lines: 102; parse: all-branches
- includes: L7 `DOFHybridScatterCommon.ush`

#### Macros (#define, 1)

- L12 `#define SCATTER_GROUP_PER_INSTANCE (VERTEX_SHADER_INVOCATION_TARGET / VERTEX_SHADER_INVOCATION_PER_SCATTERING_GROUP)`

#### Entry points (1)

- L36-101 _entry_ `[numthreads(1, SCATTER_GROUP_PER_INSTANCE, 1)] [numthreads(1, 1, 1)] void ScatterGroupPackMainCS( uint GroupId : SV_GroupID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FDiaphragmDOFScatterGroupPackCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/DiaphragmDOF.cpp:1472) _[#if SCATTERING_GROUP_PACKING]_

#### Global resources (textures / buffers / samplers) (3)

- L22 _resource_ `RWBuffer<uint> OutScatterDrawIndirectParameters;`
- L24 _resource_ `RWStructuredBuffer<float4> OutForegroundScatterDrawList;`
- L25 _resource_ `RWStructuredBuffer<float4> OutBackgroundScatterDrawList;`

#### Global parameters (uniforms) (1)

- L17 _parameter_ `uint MaxScatteringGroupCount;`

#### groupshared (1)

- L30 _groupshared_ `groupshared uint ScatterGroupCount;`

### `Shaders/Private/DiaphragmDOF/DOFHybridScatterCompilation.ush` (Private)

- lines: 103; parse: all-branches
- includes: L7 `DOFHybridScatterCommon.ush`, L8 `../EyeAdaptationCommon.ush`

#### Structs / classes (1)

- L16-35 _struct_ **`FHybridScatterInputs`** `struct FHybridScatterInputs` — Parameters for ComputeScatterFactor.
  - L21 _member_ `Texture2D NeighborhoodComparisonBuffer;` — Texture used for performing neighborhood comparison.
  - L22 _member_ `float2 NeighborhoodComparisonBufferInvExtent;`
  - L23 _member_ `float4 NeighborhoodComparisonViewRectUV;`
  - L27 _member_ `float FrameExposureScale;`
  - L30 _member_ `float4 Color;`
  - L31 _member_ `float CocRadius;`
  - L34 _member_ `float2 BufferUV;` — Coordinate of input pixel.

#### Global parameters (uniforms) (1)

- L13 _parameter_ `float NeighborCompareMaxColor;`

#### Functions (2)

- L38-46 _function_ `float ComputeLuminanceOnlyBasedScatterFactor(in const FHybridScatterInputs Parameters)` — Return the minimal luma for a pixel to be scattered.
- L49-102 _function_ `float ComputeNeighborBasedScatterFactor(in const FHybridScatterInputs Parameters)` — Determines whether a sample should be scattered.

### `Shaders/Private/DiaphragmDOF/DOFHybridScatterPixelShader.usf` (Private)

- lines: 263; parse: all-branches
- includes: L7 `DOFHybridScatterCommon.ush`, L8 `DOFVignetteCommon.ush`, L9 `../FastMath.ush`, L10 `/Engine/Public/DualPixelVectorization.ush`

#### Macros (#define, 2)

- L16 `#define CONFIG_POINT_MIRROR_BOKEH -1` _[#if DIM_LAYER_PROCESSING == LAYER_PROCESSING_FOREGROUND_ONLY]_
- L18 `#define CONFIG_POINT_MIRROR_BOKEH 1` _[#if !(DIM_LAYER_PROCESSING == LAYER_PROCESSING_FOREGROUND_ONLY) && DIM_LAYER_PROCESSING == LAYER_PROCESSING_BACKGROUND_ONLY]_

#### Entry points (1)

- L108-262 _entry_ `void ScatterMainPS( in nointerpolation float4 BokehCenterScreenAndClipPos : TEXCOORD0, in nointerpolation float4 ColorAndAbsCocRadius0 : TEXCOORD1, in nointerpolation float4 ColorAndAbsCocRadius1 : TEXCOORD2, in nointerpolation uint3 GlobalSpriteIdAndPetzvalTransformPacked : TEXCOORD3, in nointerpolation float4 TaylorExpensionMAD0 : TEXCOORD4, in nointerpolation float4 TaylorExpensionMAD1 : TEXCOORD5, in float4 SvPosition : SV_Position, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FDiaphragmDOFHybridScatterPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/DiaphragmDOF.cpp:1477)

#### Global resources (textures / buffers / samplers) (3)

- L26 _resource_ `StructuredBuffer<float4> ScatterDrawList;`
- L28 _resource_ `Texture2D BokehLUT;`
- L31 _resource_ `Texture2D ScatterOcclusion;`

#### Global parameters (uniforms) (4)

- L24 _parameter_ `float ScatteringScaling;`
- L30 _parameter_ `float4 ScatterOcclusionSize;`
- L33 _parameter_ `float BarrelRadius;`
- L34 _parameter_ `float BarrelLength;`

#### Functions (3)

- L39-45 _function_ `half2 HalfSafeRcp(half2 Value)`
- L47-53 _function_ `half2x2 dpv_mul_vec_mat(half2x2 InVector, half2x2 InMatrix)`
- L56-106 _function_ `half2 GetPixelVisibility_DPV(half2x2 PixelOffset, uint2 VignetteDataOffset)` — Calculate the visibility of the pixel for a specific bokeh through the lens barrel

### `Shaders/Private/DiaphragmDOF/DOFHybridScatterVertexShader.usf` (Private)

- lines: 206; parse: all-branches
- includes: L7 `DOFHybridScatterCommon.ush`

#### Entry points (1)

- L73-206 _entry_ `void ScatterMainVS( in uint VertexId : SV_VertexID, in uint InstanceId : SV_InstanceID, out nointerpolation float4 BokehCenterScreenAndClipPos : TEXCOORD0, out nointerpolation float4 ColorAndAbsCocRadius0 : TEXCOORD1, out nointerpolation float4 ColorAndAbsCocRadius1 : TEXCOORD2, out nointerpolation uint3 GlobalSpriteIdAndPetzvalTransformPacked : TEXCOORD3, out nointerpolation float4 TaylorExpensionMAD0 : TEXCOORD4, out nointerpolation float4 TaylorExpensionMAD1 : TEXCOORD5, out float4 OutPosition : SV_POSITION)` — stage: **vertex (from C++ binding)** — C++: `FDiaphragmDOFHybridScatterVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/DiaphragmDOF.cpp:1476)

#### Global resources (textures / buffers / samplers) (1)

- L28 _resource_ `StructuredBuffer<float4> ScatterDrawList;`

#### Global parameters (uniforms) (7)

- L24 _parameter_ `float4 ViewportSize;`
- L26 _parameter_ `float ScatteringScaling;`
- L27 _parameter_ `float CocRadiusToCircumscribedRadius;`
- L30 _parameter_ `float Petzval;`
- L31 _parameter_ `float PetzvalFalloffPower;`
- L32 _parameter_ `float2 PetzvalExclusionBoxExtents;`
- L33 _parameter_ `float PetzvalExclusionBoxRadius;`

#### static const (1)

- L12-19 _static_const_ `static const float2 kSpriteVertices[6] = { float2(-1.0, +1.0), float2(+1.0, +1.0), float2(+1.0, -1.0), float2(-1.0, -1.0), float2(+1.0, -1.0), float2(-1.0, +1.0), };`

#### Functions (1)

- L37-71 _function_ `float2x2 CalcPetzvalTransform(float2 BokehCenter)`

### `Shaders/Private/DiaphragmDOF/DOFPostfiltering.usf` (Private)

- lines: 226; parse: all-branches
- includes: L7 `DOFCommon.ush`, L8 `DOFGatherTileSuggest.ush`, L9 `../Random.ush`

#### Macros (#define, 3)

- L12 `#define THREADGROUP_SIZEX (COC_TILE_SIZE)`
- L13 `#define THREADGROUP_SIZEY (THREADGROUP_SIZEX)`
- L14 `#define THREADGROUP_TOTALSIZE (THREADGROUP_SIZEX * THREADGROUP_SIZEY)`

#### Entry points (1)

- L158-225 _entry_ `[numthreads(THREADGROUP_SIZEX, THREADGROUP_SIZEY, 1)] void PostfilterMainCS( uint2 DispatchThreadId : SV_DispatchThreadID, uint2 GroupId : SV_GroupID)` — stage: **compute** — C++: `FDiaphragmDOFPostfilterCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/DiaphragmDOF.cpp:1475) — Reduce noise of background and foreground layers by taking the 3x3 median.

#### Global resources (textures / buffers / samplers) (6)

- L21 _resource_ `Texture2D ConvolutionInput_SceneColor;`
- L22 _resource_ `Texture2D ConvolutionInput_SeparateAlpha;`
- L24 _resource_ `Texture2D TileClassification_Foreground;`
- L25 _resource_ `Texture2D TileClassification_Background;`
- L28 _resource_ `RWTexture2D<float4> ConvolutionOutput_SceneColor;`
- L29 _resource_ `RWTexture2D<float4> ConvolutionOutput_SeparateAlpha;`

#### Global parameters (uniforms) (3)

- L16 _parameter_ `uint4 ViewportRect;`
- L17 _parameter_ `float2 MaxInputBufferUV;`
- L20 _parameter_ `float4 ConvolutionInputSize;`

#### static const (1)

- L32-42 _static_const_ `static const int2 kOffsets3x3[9] = { int2(-1, -1), int2( 0, -1), int2( 1, -1), int2(-1, 0), int2( 0, 0), int2( 1, 0), int2(-1, 1), int2( 0, 1), int2( 1, 1), };`

#### Functions (7)

- L45-56 _function_ `void LMHOperator(float4 A, float4 B, float4 C, out float4 L, out float4 M, out float4 H)` — Operator that output, lowest, median and highest values from 3 input values.
- L59-65 _function_ `float4 Median(float4 A, float4 B, float4 C)` — 3 samples median.
- L68-88 _function_ `float4 Median9(float4 In[9])` — 9 samples median using Smith1996.
- L92-101 _function_ `float4 SampleInputBuffer(Texture2D Tex, float2 SampleUV)` — Sample input buffer
- L105-115 _function_ `float4 SampleMedian3x3(Texture2D Tex, float2 TexInvSize, float2 BufferUV)` — 3x3 neighborhood median sampling.
- L119-138 _function_ `float4 SampleMax3x3(Texture2D Tex, float2 TexInvSize, float2 BufferUV)` — 3x3 neighborhood max sampling.
- L142-154 _function_ `float4 PostfilterInput(Texture2D Tex, float2 TexInvSize, float2 BufferUV)` — Postfilter input according to the method permutation dimension.

### `Shaders/Private/DiaphragmDOF/DOFRecombine.usf` (Private)

- lines: 1189; parse: first-branch (retry, +1 merged from all-branches pass)
- includes: L9 `DOFCommon.ush`, L10 `../SceneTexturesCommon.ush`, L11 `../Random.ush`, L12 `../MonteCarlo.ush`, L13 `../SobolRandom.ush`, L176 `../SeparateTranslucency.ush`

#### Macros (#define, 32)

- L20 `#define DEBUG_FAST_PATHS 0`
- L27 `#define SLIGHT_FOCUS_METHOD_DISABLED 0`
- L30 `#define SLIGHT_FOCUS_METHOD_UNIQUE_CONVOLUTIONS 1`
- L33 `#define SLIGHT_FOCUS_METHOD_SEPARATE_CONVOLUTIONS 2`
- L38 `#define NEIGHBORHOOD_ANALISIS_ATOMIC 0`
- L41 `#define NEIGHBORHOOD_ANALISIS_WAVE 1`
- L44 `#define NEIGHBORHOOD_ANALISIS_LDS_REDUCE 2`
- L49 `#define COMPOSITING_METHOD_NONE 0`
- L50 `#define COMPOSITING_METHOD_BILINEAR_BKG 1`
- L57 `#define CONFIG_COMPOSITING_METHOD (COMPOSITING_METHOD_NONE)` _[#if DIM_LAYER_PROCESSING == LAYER_PROCESSING_FOREGROUND_ONLY]_
- L60 `#define CONFIG_COMPOSITING_METHOD (COMPOSITING_METHOD_BILINEAR_BKG)` _[#if !(DIM_LAYER_PROCESSING == LAYER_PROCESSING_FOREGROUND_ONLY) && DIM_LAYER_PROCESSING == LAYER_PROCESSING_BACKGROUND_ONLY]_
- L63 `#define CONFIG_COMPOSITING_METHOD (COMPOSITING_METHOD_BILINEAR_BKG)` _[#if !(DIM_LAYER_PROCESSING == LAYER_PROCESSING_FOREGROUND_ONLY) && !(DIM_LAYER_PROCESSING == LAYER_PROCESSING_BACKGROUND_ONLY) && DIM_LAYER_PROCESSING == LAYER_PROCESSING_COMBINED]_
- L72 `#define CONFIG_GATHER_PAIR_COUNT 0` _[#if DIM_QUALITY == 0]_
- L73 `#define CONFIG_SLIGHT_FOCUS_METHOD (SLIGHT_FOCUS_METHOD_DISABLED)` _[#if DIM_QUALITY == 0]_
- L74 `#define CONFIG_HOLE_FILLING_METHOD (HOLE_FILLING_METHOD_OPACITY_AMEND)` _[#if DIM_QUALITY == 0]_
- L77 `#define CONFIG_GATHER_PAIR_COUNT 12` _[#if !(DIM_QUALITY == 0) && DIM_QUALITY == 1]_
- L78 `#define CONFIG_SLIGHT_FOCUS_METHOD (SLIGHT_FOCUS_METHOD_UNIQUE_CONVOLUTIONS)` _[#if !(DIM_QUALITY == 0) && DIM_QUALITY == 1]_
- L79 `#define CONFIG_HOLE_FILLING_METHOD (HOLE_FILLING_METHOD_SEPARATE_GATHER)` _[#if !(DIM_QUALITY == 0) && DIM_QUALITY == 1]_
- L80 `#define CONFIG_FETCH_FULLRES_COC_FROM_ALPHA (!CONFIG_DOF_ALPHA)` _[#if !(DIM_QUALITY == 0) && DIM_QUALITY == 1]_
- L83 `#define CONFIG_GATHER_PAIR_COUNT 16` _[#if !(DIM_QUALITY == 0) && !(DIM_QUALITY == 1) && DIM_QUALITY == 2]_
- L84 `#define CONFIG_SLIGHT_FOCUS_METHOD (SLIGHT_FOCUS_METHOD_UNIQUE_CONVOLUTIONS)` _[#if !(DIM_QUALITY == 0) && !(DIM_QUALITY == 1) && DIM_QUALITY == 2]_
- L85 `#define CONFIG_HOLE_FILLING_METHOD (HOLE_FILLING_METHOD_SEPARATE_GATHER)` _[#if !(DIM_QUALITY == 0) && !(DIM_QUALITY == 1) && DIM_QUALITY == 2]_
- L86 `#define CONFIG_FETCH_FULLRES_COC_FROM_ALPHA (!CONFIG_DOF_ALPHA)` _[#if !(DIM_QUALITY == 0) && !(DIM_QUALITY == 1) && DIM_QUALITY == 2]_
- L96 `#define NEIGHBORHOOD_ANALISIS_METHOD (NEIGHBORHOOD_ANALISIS_WAVE)` _[#if COMPILER_SUPPORTS_WAVE_MINMAX && (PS4_PROFILE \|\| XBOXONE_PROFILE)]_
- L100 `#define NEIGHBORHOOD_ANALISIS_METHOD (NEIGHBORHOOD_ANALISIS_LDS_REDUCE)` _[#if !(COMPILER_SUPPORTS_WAVE_MINMAX && (PS4_PROFILE \|\| XBOXONE_PROFILE)) && COMPILER_HLSLCC]_
- L103 `#define NEIGHBORHOOD_ANALISIS_METHOD (NEIGHBORHOOD_ANALISIS_ATOMIC)` _[#if !(COMPILER_SUPPORTS_WAVE_MINMAX && (PS4_PROFILE \|\| XBOXONE_PROFILE)) && !(COMPILER_HLSLCC)]_
- L108 `#define CONFIG_CLAMP_FULLRES_GATHER 1`
- L111 `#define CONFIG_CLAMP_DOF_BUFFER_UV 1`
- L115 `#define CONFIG_FETCH_FULLRES_COC_FROM_ALPHA 0` _[#if !defined(CONFIG_FETCH_FULLRES_COC_FROM_ALPHA)]_
- L122 `#define OPACITY_EPSILON 0.01`
- L125 `#define GROUP_BORDER_SIZE (DEFAULT_GROUP_BORDER_SIZE)`
- L126 `#define THREADGROUP_TOTALSIZE (GROUP_BORDER_SIZE * GROUP_BORDER_SIZE)`

#### Entry points (1)

- L686-1188 _entry_ `[numthreads(GROUP_BORDER_SIZE, GROUP_BORDER_SIZE, 1)] void RecombineMainCS( uint2 DispatchThreadId : SV_DispatchThreadID, uint2 GroupThreadId : SV_GroupThreadID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FDiaphragmDOFRecombineCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/DiaphragmDOF.cpp:1478)

#### Structs / classes (5)

- L182-198 _struct_ **`FRecombineInputParameters`** `struct FRecombineInputParameters` — Intermediary results of the recombine.
  - L185 _member_ `float2 ViewportUV;` — The viewport UV of the output pixel.
  - L188 _member_ `float2 SceneBufferUV;` — Buffer UV to sample scene texture buffers.
  - L191 _member_ `float2 DOFBufferUV;` — Buffer UV to sample DOF buffers.
  - L194 _member_ `float4 DOFBufferSize;` — Buffer size and inv size for the DOF inputs.
  - L197 _member_ `uint2 Seed0;` — Random seeds
- L317-327 _struct_ **`FGatherSample`** `struct FGatherSample` — Structs that holds data about a sample for gathering.
  - L320 _member_ `float4 Color;` — Sample's scene color (and optionally alpha channel).
  - L323 _member_ `float CocRadius;` — Sample's radius of the Coc
  - L326 _member_ `float Intersection;` — Sample's intersection.
- L330-338 _struct_ **`FFullResGatherParameters`** `struct FFullResGatherParameters` — Gathering parameters in recombine pass
  - L333 _member_ `float KernelPixelRadius;` — Radius size in FULL res pixels.
  - L336 _member_ `uint SamplePairCount;` — Number of pair of gathering samples.
- L341-353 _struct_ **`FFullResGatherAccumulator`** `struct FFullResGatherAccumulator` — Gathering accumulator for recombine pass
  - L344 _member_ `FFullResGatherParameters Parameters;` — Parameters of the full res gather.
  - L346 _member_ `float4 Color;`
  - L347 _member_ `float ColorWeight;`
  - L349 _member_ `float Opacity;`
  - L350 _member_ `float OpacityWeight;`
  - L352 _member_ `uint LayerProcessing;`
- L369-374 _struct_ **`FGatherSampleDerivedParameters`** `struct FGatherSampleDerivedParameters`
  - L371 _member_ `float Weight;`
  - L372 _member_ `float IsConsidered;`
  - L373 _member_ `float Opacity;`

#### Global resources (textures / buffers / samplers) (17)

- L146 _resource_ `Texture2D BokehLUT;`
- L148 _resource_ `Texture2D SceneColorInput;`
- L149 _resource_ `Texture2D SceneDepthTexture;`
- L150 _resource_ `Texture2D SceneSeparateCoc;`
- L152 _resource_ `Texture2D<float> LowResDepthTexture;`
- L153 _resource_ `Texture2D<float> FullResDepthTexture;`
- L155 _resource_ `Texture2D SceneSeparateTranslucency;`
- L156 _resource_ `Texture2D SceneSeparateTranslucencyModulateColor;`
- L160 _resource_ `Texture2D ForegroundConvolution_SceneColor;`
- L161 _resource_ `Texture2D ForegroundConvolution_SeparateAlpha;`
- L163 _resource_ `Texture2D ForegroundHoleFillingConvolution_SceneColor;`
- L164 _resource_ `Texture2D ForegroundHoleFillingConvolution_SeparateAlpha;`
- L166 _resource_ `Texture2D SlightOutOfFocusConvolution_SceneColor;`
- L167 _resource_ `Texture2D SlightOutOfFocusConvolution_SeparateAlpha;`
- L169 _resource_ `Texture2D BackgroundConvolution_SceneColor;`
- L170 _resource_ `Texture2D BackgroundConvolution_SeparateAlpha;`
- L173 _resource_ `RWTexture2D<float4> SceneColorOutput;`

#### Global parameters (uniforms) (13)

- L131 _parameter_ `float4 ViewportSize;`
- L132 _parameter_ `uint4 ViewportRect;`
- L134 _parameter_ `FScreenTransform DispatchThreadIdToDOFBufferUV;`
- L135 _parameter_ `float2 DOFBufferUVMax;`
- L137 _parameter_ `float4 SeparateTranslucencyBilinearUVMinMax;`
- L138 _parameter_ `uint SeparateTranslucencyUpscaling;`
- L139 _parameter_ `float EncodedCocRadiusToRecombineCocRadius;`
- L140 _parameter_ `float MaxRecombineAbsCocRadius;`
- L141 _parameter_ `float SOFHistoryRejectionBoost;`
- L143 _parameter_ `float4 SceneColorExtentAndInvExtent;`
- L144 _parameter_ `float4 SceneColorViewRectUV;`
- L158 _parameter_ `float4 ConvolutionInputSize;`
- L177 _parameter_ `float2 SeparateTranslucencyTextureLowResExtentInverse;`

#### groupshared (2)

- L676 _groupshared_ `groupshared uint SharedMaxConsideredAbsCocRadius;` _[#if NEIGHBORHOOD_ANALISIS_METHOD == NEIGHBORHOOD_ANALISIS_ATOMIC]_
- L681 _groupshared_ `groupshared float SharedMaxConsideredAbsCocRadius[GROUP_BORDER_SIZE * GROUP_BORDER_SIZE];` _[#if !(NEIGHBORHOOD_ANALISIS_METHOD == NEIGHBORHOOD_ANALISIS_ATOMIC) && NEIGHBORHOOD_ANALISIS_METHOD == NEIGHBORHOOD_ANALISIS_LDS_REDUCE]_

#### Functions (20)

- L203-206 _function_ `float SampleWorldDepth(float2 BufferUV)`
- L209-213 _function_ `float NoizNorm(float2 N, float X)` — {0 to 1} output.
- L215-218 _function_ `float2 RotVec(float Radius, float Radians)`
- L220-228 _function_ `void AmendAdditiveColorWithMaxTranslucency(inout float4 Color, inout float Translucency, float MaxTranslucency)`
- L235-252 _function_ `float ComputeSampleWeight(float CocRadius)` — Compute sample weight according's to its Coc radius.
- L254-278 _function_ `float ComputeSampleIntersection(float SampleCocRadius, float SampleDistance)`
- L281-285 _function_ `float ComputeBackgroundSampleOpacity(float CocRadius)` — Returns the opacity to use to transition to background.
- L288-291 _function_ `float IsConsideredBackgroundSample(float CocRadius)` — Returns the opacity to use to transition to background.
- L294-298 _function_ `float ComputeInFocusOpacity(float CocRadius)` — Compute translucency of the in focus sample.
- L301-304 _function_ `float ComputeForegroundSampleOpacity(float CocRadius)` — Returns the opacity to use to transition foreground slight out of focus over in focus.
- L307-310 _function_ `float IsConsideredForegroundSample(float CocRadius)` — Returns the opacity to use to transition to background.
- L355-367 _function_ `FFullResGatherAccumulator CreateFullResGatherAccumulator(in FFullResGatherParameters GatherParameters)`
- L376-406 _function_ `FGatherSampleDerivedParameters ComputeSampleDerivates(in FFullResGatherAccumulator Accumulator, in FGatherSample A)`
- L408-441 _function_ `void HoleFillCloserSample( in FFullResGatherAccumulator Accumulator, inout FGatherSample A, inout FGatherSampleDerivedParameters DerivedA, in FGatherSample Closer, in FGatherSampleDerivedParameters DerivedCloser)`
- L443-470 _function_ `void AccumulateSample( inout FFullResGatherAccumulator Accumulator, in FGatherSample A, in FGatherSampleDerivedParameters DerivedA)`
- L473-509 _function_ `void AccumulateMirrorSamples(inout FFullResGatherAccumulator Accumulator, in FGatherSample S[2])` — Accumulates mirror samples.
- L512-520 _function_ `void AccumulateCenterSample(inout FFullResGatherAccumulator Accumulator, in FGatherSample A)` — Accumulates center sample.
- L523-547 _function_ `void ResolveAccumulator( in FFullResGatherAccumulator Accumulator, out float4 OutGatherBackgroundUnpremultipliedColor, out float OutGatherBackgroundOpacity)` — Resolves the slightly out of focus.
- L554-614 _function_ `void FetchAndAccumulateSamplePair( in const FRecombineInputParameters InputParameters, in float2 PixelOffset, inout FFullResGatherAccumulator Accumulator)` _[#if CONFIG_SLIGHT_FOCUS_METHOD != SLIGHT_FOCUS_METHOD_DISABLED]_
- L616-644 _function_ `void GatherToAccumulator( in const FRecombineInputParameters InputParameters, in const FFullResGatherParameters GatherParameters, inout FFullResGatherAccumulator Accumulator)` _[#if CONFIG_SLIGHT_FOCUS_METHOD != SLIGHT_FOCUS_METHOD_DISABLED]_

### `Shaders/Private/DiaphragmDOF/DOFReduce.usf` (Private)

- lines: 729; parse: all-branches
- includes: L9 `DOFDownsample.ush`, L10 `DOFHybridScatterCompilation.ush`, L11 `DOFVignetteCommon.ush`, L12 `../ReductionCommon.ush`

#### Macros (#define, 14)

- L7 `#define EYE_ADAPTATION_LOOSE_PARAMETERS 1`
- L19 `#define SCATTER_ALLOC_METHOD_ATOMIC 0`
- L22 `#define SCATTER_ALLOC_METHOD_WAVE 1`
- L25 `#define SCATTER_ALLOC_METHOD_LDS 2`
- L30 `#define SHARED_REDUCE_COUNT 3`
- L32 `#define OUTPUT_MIP_COUNT (SHARED_REDUCE_COUNT + 1)`
- L34 `#define THREADGROUP_TILE_SIZE (1 << SHARED_REDUCE_COUNT)`
- L35 `#define THREADGROUP_TOTALSIZE (THREADGROUP_TILE_SIZE * THREADGROUP_TILE_SIZE)`
- L38 `#define CONFIG_GATHER_INPUT_LAYOUT (GATHER_INPUT_LAYOUT_RGB_ALPHA_COC)` _[#if CONFIG_DOF_ALPHA]_
- L40 `#define CONFIG_GATHER_INPUT_LAYOUT (GATHER_INPUT_LAYOUT_RGB_SEPARATE_COC)` _[#if !(CONFIG_DOF_ALPHA) && DIM_RGB_COLOR_BUFFER]_
- L42 `#define CONFIG_GATHER_INPUT_LAYOUT (GATHER_INPUT_LAYOUT_RGB_COC)` _[#if !(CONFIG_DOF_ALPHA) && !(DIM_RGB_COLOR_BUFFER)]_
- L49 `#define SCATTER_ALLOC_METHOD (SCATTER_ALLOC_METHOD_WAVE)` _[#if COMPILER_SUPPORTS_WAVE_BIT_ORAND && (COMPILER_PSSL \|\| XBOXONE_PROFILE)]_
- L53 `#define SCATTER_ALLOC_METHOD (SCATTER_ALLOC_METHOD_LDS)` _[#if !(COMPILER_SUPPORTS_WAVE_BIT_ORAND && (COMPILER_PSSL \|\| XBOXONE_PROFILE)) && COMPILER_HLSLCC]_
- L56 `#define SCATTER_ALLOC_METHOD (SCATTER_ALLOC_METHOD_ATOMIC)` _[#if !(COMPILER_SUPPORTS_WAVE_BIT_ORAND && (COMPILER_PSSL \|\| XBOXONE_PROFILE)) && !(COMPILER_HLSLCC)]_

#### Entry points (1)

- L331-728 _entry_ `[numthreads(THREADGROUP_TILE_SIZE, THREADGROUP_TILE_SIZE, 1)] void ReduceCS( uint2 GroupId : SV_GroupID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FDiaphragmDOFReduceCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/DiaphragmDOF.cpp:1471)

#### Structs / classes (2)

- L136-140 _struct_ **`FReductionInput`** `struct FReductionInput`
  - L138 _member_ `float4 Colors[4];`
  - L139 _member_ `float CocRadii[4];`
- L142-146 _struct_ **`FReductionOutput`** `struct FReductionOutput`
  - L144 _member_ `float4 Color;`
  - L145 _member_ `float CocRadius;`

#### Global resources (textures / buffers / samplers) (14)

- L81 _resource_ `Texture2D GatherInput_SceneColor;`
- L82 _resource_ `Texture2D GatherInput_SeparateCoc;`
- L86 _resource_ `Texture2D QuarterResGatherInput_SceneColor;`
- L91 _resource_ `RWTexture2D<float4> OutputMips_0_SceneColor;`
- L92 _resource_ `RWTexture2D<float4> OutputMips_1_SceneColor;`
- L93 _resource_ `RWTexture2D<float4> OutputMips_2_SceneColor;`
- L94 _resource_ `RWTexture2D<float4> OutputMips_3_SceneColor;`
- L98 _resource_ `RWTexture2D<float> OutputMips_0_SeparateCoc;` _[#if CONFIG_GATHER_INPUT_LAYOUT == GATHER_INPUT_LAYOUT_RGB_ALPHA_COC \|\| CONFIG_GATHER_INPUT_LAYOUT == GATHER_INPUT_LAYOUT_RGB_SEPARATE_COC]_
- L99 _resource_ `RWTexture2D<float> OutputMips_1_SeparateCoc;` _[#if CONFIG_GATHER_INPUT_LAYOUT == GATHER_INPUT_LAYOUT_RGB_ALPHA_COC \|\| CONFIG_GATHER_INPUT_LAYOUT == GATHER_INPUT_LAYOUT_RGB_SEPARATE_COC]_
- L100 _resource_ `RWTexture2D<float> OutputMips_2_SeparateCoc;` _[#if CONFIG_GATHER_INPUT_LAYOUT == GATHER_INPUT_LAYOUT_RGB_ALPHA_COC \|\| CONFIG_GATHER_INPUT_LAYOUT == GATHER_INPUT_LAYOUT_RGB_SEPARATE_COC]_
- L101 _resource_ `RWTexture2D<float> OutputMips_3_SeparateCoc;` _[#if CONFIG_GATHER_INPUT_LAYOUT == GATHER_INPUT_LAYOUT_RGB_ALPHA_COC \|\| CONFIG_GATHER_INPUT_LAYOUT == GATHER_INPUT_LAYOUT_RGB_SEPARATE_COC]_
- L106 _resource_ `RWBuffer<uint> OutScatterDrawIndirectParameters;` _[#if DIM_HYBRID_SCATTER_FGD \|\| DIM_HYBRID_SCATTER_BGD]_
- L108 _resource_ `RWStructuredBuffer<float4> OutForegroundScatterDrawList;` _[#if DIM_HYBRID_SCATTER_FGD \|\| DIM_HYBRID_SCATTER_BGD]_
- L109 _resource_ `RWStructuredBuffer<float4> OutBackgroundScatterDrawList;` _[#if DIM_HYBRID_SCATTER_FGD \|\| DIM_HYBRID_SCATTER_BGD]_

#### Global parameters (uniforms) (17)

- L64 _parameter_ `uint2 PassViewSize;`
- L65 _parameter_ `float4 ScatteringViewportSize;`
- L66 _parameter_ `float ScatteringScaling;`
- L67 _parameter_ `uint MaxScatteringGroupCount;`
- L68 _parameter_ `float MinScatteringCocRadius;`
- L69 _parameter_ `float PreProcessingToProcessingCocRadiusFactor;`
- L70 _parameter_ `float BokehGatherDistinctionLimit;`
- L72 _parameter_ `float2 SensorSize;`
- L73 _parameter_ `float Aperture;`
- L74 _parameter_ `float LensImageDistance;`
- L75 _parameter_ `float BarrelRadius;`
- L76 _parameter_ `float BarrelLength;`
- L77 _parameter_ `uint4 MatteBoxPlanes[MAX_MATTE_BOX_FLAGS];`
- L79 _parameter_ `float4 GatherInputExtentAndInvExtent;`
- L80 _parameter_ `float4 GatherInputViewRectUV;`
- L84 _parameter_ `float4 QuarterResGatherInputExtentAndInvExtent;`
- L85 _parameter_ `float4 QuarterResGatherInputViewRectUV;`

#### groupshared (8)

- L116 _groupshared_ `groupshared uint SharedForegroundScatterGroupMask;` _[#if SCATTER_ALLOC_METHOD == SCATTER_ALLOC_METHOD_ATOMIC]_
- L117 _groupshared_ `groupshared uint SharedBackgroundScatterGroupMask;` _[#if SCATTER_ALLOC_METHOD == SCATTER_ALLOC_METHOD_ATOMIC]_
- L120 _groupshared_ `groupshared uint SharedForegroundScatterGroupMask[THREADGROUP_TOTALSIZE];` _[#if !(SCATTER_ALLOC_METHOD == SCATTER_ALLOC_METHOD_ATOMIC) && SCATTER_ALLOC_METHOD == SCATTER_ALLOC_METHOD_LDS]_
- L121 _groupshared_ `groupshared uint SharedBackgroundScatterGroupMask[THREADGROUP_TOTALSIZE];` _[#if !(SCATTER_ALLOC_METHOD == SCATTER_ALLOC_METHOD_ATOMIC) && SCATTER_ALLOC_METHOD == SCATTER_ALLOC_METHOD_LDS]_
- L125 _groupshared_ `groupshared uint SharedForegroundAtomic;`
- L126 _groupshared_ `groupshared uint SharedBackgroundAtomic;`
- L128 _groupshared_ `groupshared float4 GroupSharedArray[THREADGROUP_TOTALSIZE];`
- L130 _groupshared_ `groupshared float GroupSharedArray2[THREADGROUP_TOTALSIZE];` _[#if CONFIG_GATHER_INPUT_LAYOUT == GATHER_INPUT_LAYOUT_RGB_ALPHA_COC]_

#### Functions (6)

- L148-172 _function_ `FReductionInput ReadReductionInputFromLDS(uint OutId, uint ReduceBankSize)`
- L174-187 _function_ `void WriteReductionOutputToLDS(FReductionOutput Output, uint OutId)`
- L189-201 _function_ `FReductionOutput ReduceOperator(FReductionInput Input, FCocDownsampleParams DownsampleParams, uint OutId)`
- L204-278 _function_ `void OutputMipLevel(const uint MipLevel, uint2 MipPixelPos, float4 Color, float CocRadius)` — Output buffer.
- L286-299 _function_ `float ApplyBokehGatherDistinctionFilter(float CocRadius, float4 Color, float FrameExposureScale)` — Pixels that are bright and have a large CoC should be scattered instead of gathered, to avoid gather noise. If they aren't, e.g. due to performance reasons, we may prefer to cull them instead of gathering them anyway. This will bias the image, as bokeh may appear slightly darker, but helps clean up noise in large bokeh.
- L301-329 _function_ `void ComputeVignetteData(uint2 DispatchThreadId, float CocRadius, out float4 Output[VIGNETTE_DATA_PER_PIXEL])`

### `Shaders/Private/DiaphragmDOF/DOFSetup.usf` (Private)

- lines: 514; parse: all-branches
- includes: L9 `DOFDownsample.ush`

#### Macros (#define, 4)

- L7 `#define CONFIG_SETUP 1`
- L14 `#define THREADGROUP_SIZE_X (8)`
- L15 `#define THREADGROUP_SIZE_Y (8)`
- L16 `#define THREADGROUP_SIZE_TOTAL (THREADGROUP_SIZE_X * THREADGROUP_SIZE_Y)`

#### Entry points (3)

- L396-439 _entry_ `[numthreads(THREADGROUP_SIZE_X, THREADGROUP_SIZE_Y, 1)] void SetupCS( uint2 GroupId : SV_GroupID, uint GroupThreadIndex : SV_GroupIndex, uint2 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FDiaphragmDOFSetupCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/DiaphragmDOF.cpp:1467) _[#if DIM_OUTPUT_RES_DIVISOR == 0]_
- L444-473 _entry_ `[numthreads(THREADGROUP_SIZE_X, THREADGROUP_SIZE_Y, 1)] void SetupCS( uint2 GroupId : SV_GroupID, uint GroupThreadIndex : SV_GroupIndex, uint2 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FDiaphragmDOFSetupCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/DiaphragmDOF.cpp:1467) _[#if !(DIM_OUTPUT_RES_DIVISOR == 0) && DIM_OUTPUT_RES_DIVISOR == 1]_
- L478-508 _entry_ `[numthreads(THREADGROUP_SIZE_X, THREADGROUP_SIZE_Y, 1)] void SetupCS( uint2 GroupId : SV_GroupID, uint GroupThreadIndex : SV_GroupIndex, uint2 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FDiaphragmDOFSetupCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/DiaphragmDOF.cpp:1467) _[#if !(DIM_OUTPUT_RES_DIVISOR == 0) && !(DIM_OUTPUT_RES_DIVISOR == 1) && DIM_OUTPUT_RES_DIVISOR == 2]_

#### Structs / classes (4)

- L41-49 _struct_ **`FDOFSetupParameters`** `struct FDOFSetupParameters`
  - L44 _member_ `bool bOutputFullRes;` — Compile-time variables
  - L45 _member_ `bool bOutputHalfRes;`
  - L47 _member_ `Texture2D SceneColorTexture;`
  - L48 _member_ `Texture2D SceneDepthTexture;`
- L51-64 _struct_ **`FDOFSetupOutput`** `struct FDOFSetupOutput`
  - L54 _member_ `bool bFullResIsValid;` — Requires bOutputFullRes
  - L55 _member_ `uint2 FullResOutputPixelPosition;`
  - L56 _member_ `float4 FullResColor;`
  - L57 _member_ `float FullResCocRadius;`
  - L60 _member_ `bool bHalfResIsValid;` — Requires bOutputHalfRes
  - L61 _member_ `uint2 HalfResOutputPixelPosition;`
  - L62 _member_ `float4 HalfResColor;`
  - L63 _member_ `float HalfResCocRadius;`
- L87-167 _struct_ **`FSoftwareQuad`** `struct FSoftwareQuad` _[#if WAVE_OPS]_
  - L89 _member_ `uint WaveQuadLeaderLane;` _[#if WAVE_OPS]_
  - L90 _member_ `bool bIsLeaderLane;` _[#if WAVE_OPS]_
  - L91 _member_ `uint2 LocalPixelPosition;` _[#if WAVE_OPS]_
  - L93 _member_ `float4 LocalColor;` _[#if WAVE_OPS]_
  - L94 _member_ `float LocalCocRadius;` _[#if WAVE_OPS]_
  - L96 _method_ `void Setup(uint2 GroupId, uint GroupThreadIndex)` _[#if WAVE_OPS]_
  - L125 _method_ `bool IsLeader()` _[#if WAVE_OPS]_
  - L130 _method_ `uint2 GetLocalPixelPosition()` _[#if WAVE_OPS]_
  - L135 _method_ `void SetLocalPixel(float4 Color, float CocRadius)` _[#if WAVE_OPS]_
  - L141 _method_ `void Sync()` _[#if WAVE_OPS]_
  - L144 _method_ `void GetPixel(uint PixelIndex, out float4 Color, out float CocRadius)` _[#if WAVE_OPS]_
  - L175 _member_ `uint GroupLaneIndex;` _[#if !(WAVE_OPS)]_
  - L176 _member_ `uint QuadLeaderLane;` _[#if !(WAVE_OPS)]_
  - L177 _member_ `bool bIsLeaderLane;` _[#if !(WAVE_OPS)]_
  - L178 _member_ `uint2 LocalPixelPosition;` _[#if !(WAVE_OPS)]_
  - L180 _method_ `void Setup(uint2 GroupId, uint GroupThreadIndex)` _[#if !(WAVE_OPS)]_
  - L191 _method_ `bool IsLeader()` _[#if !(WAVE_OPS)]_
  - L196 _method_ `uint2 GetLocalPixelPosition()` _[#if !(WAVE_OPS)]_
  - L201 _method_ `void SetLocalPixel(float4 Color, float CocRadius)` _[#if !(WAVE_OPS)]_
  - L207 _method_ `void Sync()` _[#if !(WAVE_OPS)]_
  - L212 _method_ `void GetPixel(uint PixelIndex, out float4 Color, out float CocRadius)` _[#if !(WAVE_OPS)]_
- L173-223 _struct_ **`FSoftwareQuad`** `struct FSoftwareQuad` _[#if !(WAVE_OPS)]_
  - L89 _member_ `uint WaveQuadLeaderLane;` _[#if WAVE_OPS]_
  - L90 _member_ `bool bIsLeaderLane;` _[#if WAVE_OPS]_
  - L91 _member_ `uint2 LocalPixelPosition;` _[#if WAVE_OPS]_
  - L93 _member_ `float4 LocalColor;` _[#if WAVE_OPS]_
  - L94 _member_ `float LocalCocRadius;` _[#if WAVE_OPS]_
  - L96 _method_ `void Setup(uint2 GroupId, uint GroupThreadIndex)` _[#if WAVE_OPS]_
  - L125 _method_ `bool IsLeader()` _[#if WAVE_OPS]_
  - L130 _method_ `uint2 GetLocalPixelPosition()` _[#if WAVE_OPS]_
  - L135 _method_ `void SetLocalPixel(float4 Color, float CocRadius)` _[#if WAVE_OPS]_
  - L141 _method_ `void Sync()` _[#if WAVE_OPS]_
  - L144 _method_ `void GetPixel(uint PixelIndex, out float4 Color, out float CocRadius)` _[#if WAVE_OPS]_
  - L175 _member_ `uint GroupLaneIndex;` _[#if !(WAVE_OPS)]_
  - L176 _member_ `uint QuadLeaderLane;` _[#if !(WAVE_OPS)]_
  - L177 _member_ `bool bIsLeaderLane;` _[#if !(WAVE_OPS)]_
  - L178 _member_ `uint2 LocalPixelPosition;` _[#if !(WAVE_OPS)]_
  - L180 _method_ `void Setup(uint2 GroupId, uint GroupThreadIndex)` _[#if !(WAVE_OPS)]_
  - L191 _method_ `bool IsLeader()` _[#if !(WAVE_OPS)]_
  - L196 _method_ `uint2 GetLocalPixelPosition()` _[#if !(WAVE_OPS)]_
  - L201 _method_ `void SetLocalPixel(float4 Color, float CocRadius)` _[#if !(WAVE_OPS)]_
  - L207 _method_ `void Sync()` _[#if !(WAVE_OPS)]_
  - L212 _method_ `void GetPixel(uint PixelIndex, out float4 Color, out float CocRadius)` _[#if !(WAVE_OPS)]_

#### Global resources (textures / buffers / samplers) (7)

- L21 _resource_ `Texture2D SceneColorTexture;`
- L22 _resource_ `Texture2D SceneDepthTexture;`
- L28 _resource_ `RWTexture2D<float> Output0;` _[#if CONFIG_DOF_ALPHA]_
- L29 _resource_ `RWTexture2D<float4> Output1;` _[#if CONFIG_DOF_ALPHA]_
- L30 _resource_ `RWTexture2D<float> Output2;` _[#if CONFIG_DOF_ALPHA]_
- L33 _resource_ `RWTexture2D<float4> Output0;` _[#if !(CONFIG_DOF_ALPHA)]_
- L34 _resource_ `RWTexture2D<float4> Output1;` _[#if !(CONFIG_DOF_ALPHA)]_

#### groupshared (3)

- L85 _groupshared_ `groupshared uint GroupNumWaves;` _[#if WAVE_OPS]_
- L171 _groupshared_ `groupshared float4 SoftQuadColors[THREADGROUP_SIZE_TOTAL];` _[#if !(WAVE_OPS)]_
- L172 _groupshared_ `groupshared float SoftQuadCocRadius[THREADGROUP_SIZE_TOTAL];` _[#if !(WAVE_OPS)]_

#### Functions (2)

- L76-82 _function_ `uint2 MortonLikeDecode(uint Index)` — Calculate a 2D space-filling curve, similar to Morton, from a 1D coordinate. From the AMD GPUOpen "Optimizing for the Radeon RDNA architecture" 00 01 08 09 16 17 24 25 02 03 10 11 18 19 26 27 04 05 12 13 20 21 28 29 06 07 14 15 22 23 30 31 32 33 40 41 48 49 56 57 34 35 42 43 50 51 58 59 36 37 44 45 52 53 60 61 38 39 46 47 54 55 62 63
- L228-391 _function_ `FDOFSetupOutput SetupDOF( FDOFSetupParameters Parameters, uint2 GroupId, uint GroupThreadIndex, uint2 DispatchThreadId )` — Launch with 1 thread per fullres pixel, and 8x8 groupsize

### `Shaders/Private/DiaphragmDOF/DOFVignetteCommon.ush` (Private)

- lines: 210; parse: all-branches
- includes: L8 `/Engine/Public/DualPixelVectorization.ush`

#### Functions (8)

- L13-31 _function_ `float HitTestCylinder(float2 RayOrigin, float3 RayDirection, float BarrelRadius, float BarrelLength)` — Given a ray and a cylinder (barrel) around the origin, calculate the height on the barrel where the ray hits.
- L35-58 _function_ `uint2 ProjectAndPackCylinder( const float CocRadius, const float2 BokehCenterClipPos, const float BarrelRadius, const float BarrelLength, const float2 SensorSize, const float Focus, const float Aperture, const float CocInfinityRadius, const float LensImageDistance )` — Project the aperture onto the end of a cylinder (lens barrel). Use the output for fast vignette occlusion testing.
- L60-72 _function_ `float HitTestProjectedCylinder( const float2 PixelOffset, const float2 BarrelData, const float BarrelRadius, out float2 SamplePositionAtBarrelEnd )`
- L74-90 _function_ `half2 HitTestProjectedCylinder_DPV( const half2x2 PixelOffset, const uint2 BarrelData[2], const float BarrelRadius, out half2x2 SamplePositionAtBarrelEnd )`
- L95-128 _function_ `float HitTestMatteBoxFlag(float3 RayOrigin, float3 RayDirection, float BarrelRadius, float BarrelLength, uint4 FlagDefinition)` — Test a ray for intersection with a single panel on a matte box at the end of the lens barrel.
- L132-172 _function_ `uint2 ProjectAndPackMatteBoxFlag( const float3 ObjectDirection, const float BarrelRadius, const float BarrelLength, const uint4 FlagDefinition )` — Project a matte box flag for onto the end of the lens barrel along a given object direction. Use the output for fast vignette occlusion testing.
- L174-187 _function_ `float HitTestProjectedMatteBoxFlag( const float2 SamplePositionAtBarrelEnd, const uint2 PackedProjectedMatteBoxFlag )`
- L189-209 _function_ `half2 HitTestProjectedMatteBoxFlag_DPV( const half2x2 SamplePositionAtBarrelEnd, const uint2 PackedProjectedMatteBoxFlag[2] )`
