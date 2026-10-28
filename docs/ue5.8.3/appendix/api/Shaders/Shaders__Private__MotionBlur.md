# Shaders / Shaders/Private/MotionBlur

- files: 9; lines: 2547
- record kinds: cpp_binding=9, define=102, entry=9, function=36, groupshared=7, include=19, macro_call=10, member=2, parameter=41, resource=61, struct=1

### `Shaders/Private/MotionBlur/MotionBlurApply.usf` (Private)

- lines: 1149; parse: all-branches
- includes: L6 `MotionBlurCommon.ush`, L7 `../LensDistortion.ush`, L8 `../Random.ush`, L9 `/Engine/Public/WaveBroadcastIntrinsics.ush`

#### Macros (#define, 27)

- L3 `#define CONFIG_MAX_RANGE_SIZE DIM_BLUR_DIRECTIONS`
- L15 `#define DEBUG_OVERLAY_INPUT_RES 0`
- L18 `#define DEBUG_OVERLAY_GATHER_RES 0`
- L21 `#define DEBUG_OVERLAY_TILE_CLASSIFICATION 0`
- L24 `#define DEBUG_OVERLAY_SKIP_CENTER 0`
- L29 `#define DEBUG_OVERLAY_SAMPLES 0`
- L35 `#define CONFIG_IS_HALF_RES 1` _[#if DIM_TILE_CLASSIFICATION == FILTER_TILE_CLASSIFY_GATHER_HALF_RES]_
- L38 `#define CONFIG_IS_HALF_RES 0` _[#if !(DIM_TILE_CLASSIFICATION == FILTER_TILE_CLASSIFY_GATHER_HALF_RES) && DIM_TILE_CLASSIFICATION == FILTER_TILE_CLASSIFY_GATHER_FULL_RES]_
- L41 `#define CONFIG_IS_HALF_RES 1` _[#if !(DIM_TILE_CLASSIFICATION == FILTER_TILE_CLASSIFY_GATHER_HALF_RES) && !(DIM_TILE_CLASSIFICATION == FILTER_TILE_CLASSIFY_GATHER_FULL_RES) && DIM_TILE_CLASSIFICATION == FILTER_TILE_CLASSIFY_SCATTER_A...]_
- L44 `#define CONFIG_IS_HALF_RES 0` _[#if !(DIM_TILE_CLASSIFICATION == FILTER_TILE_CLASSIFY_GATHER_HALF_RES) && !(DIM_TILE_CLASSIFICATION == FILTER_TILE_CLASSIFY_GATHER_FULL_RES) && !(DIM_TILE_CLASSIFICATION == FILTER_TILE_CLASSIFY_SCATTER...]_
- L47 `#define CONFIG_IS_HALF_RES 0` _[#if !(DIM_TILE_CLASSIFICATION == FILTER_TILE_CLASSIFY_GATHER_HALF_RES) && !(DIM_TILE_CLASSIFICATION == FILTER_TILE_CLASSIFY_GATHER_FULL_RES) && !(DIM_TILE_CLASSIFICATION == FILTER_TILE_CLASSIFY_SCATTER...]_
- L54 `#define SOFT_Z_EXTENT 1`
- L57 `#define CONFIG_SHUFFLE_HALF_RES 0`
- L60 `#define CONFIG_POST_MOTIONBLUR_TRANSLUCENCY 1`
- L64 `#define CONFIG_SKIP_CENTER 1` _[#if COMPILER_SUPPORTS_WAVE_MINMAX]_
- L66 `#define CONFIG_SKIP_CENTER 0` _[#if !(COMPILER_SUPPORTS_WAVE_MINMAX)]_
- L69 `#define CONFIG_SCENE_COLOR_ALPHA (DIM_ALPHA_CHANNEL)`
- L75 `#define TILE_SIZE (VELOCITY_FILTER_TILE_SIZE / 2)` _[#if CONFIG_IS_HALF_RES]_
- L77 `#define TILE_SIZE (VELOCITY_FILTER_TILE_SIZE)` _[#if !(CONFIG_IS_HALF_RES)]_
- L121 `#define SharedVelocitySampler VelocitySampler` _[#if SUPPORTS_INDEPENDENT_SAMPLERS]_
- L122 `#define SharedVelocityTileSampler VelocitySampler` _[#if SUPPORTS_INDEPENDENT_SAMPLERS]_
- L123 `#define SharedVelocityFlatSampler VelocitySampler` _[#if SUPPORTS_INDEPENDENT_SAMPLERS]_
- L124 `#define SharedDepthSampler VelocitySampler` _[#if SUPPORTS_INDEPENDENT_SAMPLERS]_
- L126 `#define SharedVelocitySampler VelocitySampler` _[#if !(SUPPORTS_INDEPENDENT_SAMPLERS)]_
- L127 `#define SharedVelocityTileSampler VelocityTileSampler` _[#if !(SUPPORTS_INDEPENDENT_SAMPLERS)]_
- L128 `#define SharedVelocityFlatSampler VelocityFlatSampler` _[#if !(SUPPORTS_INDEPENDENT_SAMPLERS)]_
- L129 `#define SharedDepthSampler DepthSampler` _[#if !(SUPPORTS_INDEPENDENT_SAMPLERS)]_

#### Entry points (1)

- L269-1148 _entry_ `[numthreads(TILE_SIZE, TILE_SIZE, 1)] void MainCS( uint GroupId : SV_GroupID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FMotionBlurFilterCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/PostProcessMotionBlur.cpp:570)

#### Global resources (textures / buffers / samplers) (20)

- L95 _resource_ `StructuredBuffer<uint> TileListsBuffer;`
- L96 _resource_ `StructuredBuffer<uint> TileListsSizeBuffer;`
- L98 _resource_ `Texture2D<mb_half4> ColorTexture;`
- L99 _resource_ `Texture2D<mb_half3> VelocityFlatTexture;`
- L100 _resource_ `Texture2D VelocityTileTextures_Textures_0;`
- L101 _resource_ `Texture2D VelocityTileTextures_Textures_1;`
- L102 _resource_ `Texture2D<mb_half4> HalfResMotionBlurTexture;`
- L104 _resource_ `SamplerState ColorSampler;`
- L105 _resource_ `SamplerState VelocitySampler;`
- L106 _resource_ `SamplerState VelocityTileSampler;`
- L107 _resource_ `SamplerState VelocityFlatSampler;`
- L108 _resource_ `SamplerState DepthSampler;`
- L110 _resource_ `Texture2D<float2> UndistortingDisplacementTexture;`
- L111 _resource_ `SamplerState UndistortingDisplacementSampler;`
- L113 _resource_ `Texture2D TranslucencyTexture;`
- L114 _resource_ `SamplerState TranslucencySampler;`
- L132 _resource_ `RWTexture2D<mb_half4> SceneColorOutputMip0;`
- L133 _resource_ `RWTexture2D<mb_half4> SceneColorOutputMip1;`
- L134 _resource_ `RWTexture2D<mb_half4> SceneColorOutputMip2;`
- L135 _resource_ `RWTexture2D<float4> DebugOutput;`

#### Global parameters (uniforms) (12)

- L86 _parameter_ `FScreenTransform ColorToVelocity;`
- L87 _parameter_ `FScreenTransform SeparateTranslucencyUVToViewportUV;`
- L88 _parameter_ `FScreenTransform ViewportUVToSeparateTranslucencyUV;`
- L89 _parameter_ `uint MaxSampleCount;`
- L90 _parameter_ `uint OutputMip1;`
- L91 _parameter_ `uint OutputMip2;`
- L92 _parameter_ `uint bLensDistortion;`
- L94 _parameter_ `uint TileListOffset;`
- L115 _parameter_ `FScreenTransform ColorToTranslucency;`
- L116 _parameter_ `float2 TranslucencyUVMin;`
- L117 _parameter_ `float2 TranslucencyUVMax;`
- L118 _parameter_ `float2 TranslucencyExtentInverse;`

#### groupshared (4)

- L142 _groupshared_ `groupshared mb_half4 SharedArray0[TILE_SIZE * TILE_SIZE];` _[#if !PLATFORM_SUPPORTS_WAVE_BROADCAST]_
- L145 _groupshared_ `groupshared mb_half SharedArray1[TILE_SIZE * TILE_SIZE];` _[#if !PLATFORM_SUPPORTS_WAVE_BROADCAST && CONFIG_SCENE_COLOR_ALPHA]_
- L152 _groupshared_ `groupshared uint SharedSampleCount;` _[#if !COMPILER_SUPPORTS_WAVE_VOTE]_
- L153 _groupshared_ `groupshared uint SharedFastPath;` _[#if !COMPILER_SUPPORTS_WAVE_VOTE]_

#### Functions (10)

- L160-163 _function_ `float NormalizeAccumulator(float Accumulator, mb_half AccumulatorWeight)`
- L165-168 _function_ `float4 NormalizeAccumulator(float4 Accumulator, float AccumulatorWeight)`
- L172-175 _function_ `mb_half NormalizeAccumulator(mb_half Accumulator, mb_half AccumulatorWeight)` _[#if CONFIG_MOTION_BLUR_COMPILE_FP16]_
- L177-180 _function_ `mb_half4 NormalizeAccumulator(mb_half4 Accumulator, mb_half AccumulatorWeight)` _[#if CONFIG_MOTION_BLUR_COMPILE_FP16]_
- L184-201 _function_ `void NormalizeAccumulatorWithHoleFill( mb_half4 Color, mb_half ColorWeight, mb_half HoleFillWeight, mb_half DepthAware, mb_half4 HoleFillingColor, mb_half InvSampleCount, out mb_half4 ColorOutput, out mb_half OpacityOutput, out bool bValidColorOutput)`
- L205-208 _function_ `mb_half ComputeSampleHoleFillWeight(mb_half CenterDepth, mb_half SampleDepth, mb_half DepthScale)` — Compute the weight of the sample for hole filling.
- L211-226 _function_ `mb_half ComputeSampleConvolutionWeight( mb_half SampleDepth, mb_half SampleSpreadLength, mb_half SampleVelocityAngle, mb_half OffsetLength, mb_half BlurAngle, mb_half PixelToSampleScale)` — Computes the contribution weight of one sample.
- L229-249 _function_ `mb_half ComputeCenterOrSampleWeight( mb_half CenterDepth, mb_half CenterSpreadLength, mb_half CenterVelocityAngle, mb_half SampleDepth, mb_half SampleSpreadLength, mb_half SampleVelocityAngle, mb_half OffsetLength, mb_half BlurAngle, mb_half PixelToSampleScale, mb_half DepthScale)` — Selectively computes the contribution weight of the center or the sample based on whether sample is respectively behind center or not
- L252-256 _function_ `mb_half GetVelocityLengthPixels(mb_half2 EncodedVelocity)` — TODO: move that to velocity flatten.
- L258-264 _function_ `float2 ApplyLensDistortionOnTranslucencyUV(float2 SeparateTranslucencyUV)`

#### Top-level macro invocations (3)

- L83 _macro_call_ `SCREEN_PASS_TEXTURE_VIEWPORT(Color)`
- L84 _macro_call_ `SCREEN_PASS_TEXTURE_VIEWPORT(Velocity)`
- L85 _macro_call_ `SCREEN_PASS_TEXTURE_VIEWPORT(VelocityTile)`

### `Shaders/Private/MotionBlur/MotionBlurCommon.ush` (Private)

- lines: 266; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../FastMath.ush`, L5 `../ScreenPass.ush`

#### Macros (#define, 54)

- L16 `#define DEBUG_MOTION_BLUR_OUTPUT 0`
- L23 `#define VELOCITY_FLATTEN_TILE_SIZE 16`
- L26 `#define VELOCITY_FILTER_TILE_SIZE 16`
- L29 `#define CONFIG_MOTION_BLUR_COMPILE_FP16 1` _[#if PLATFORM_SUPPORTS_REAL_TYPES && 0]_
- L31 `#define CONFIG_MOTION_BLUR_COMPILE_FP16 0` _[#if !(PLATFORM_SUPPORTS_REAL_TYPES && 0)]_
- L34 `#define CONFIG_MINIMAL_PIXEL_VELOCITY 0.5`
- L40 `#define mb_half half` _[#if CONFIG_MOTION_BLUR_COMPILE_FP16]_
- L41 `#define mb_half2 half2` _[#if CONFIG_MOTION_BLUR_COMPILE_FP16]_
- L42 `#define mb_half3 half3` _[#if CONFIG_MOTION_BLUR_COMPILE_FP16]_
- L43 `#define mb_half4 half4` _[#if CONFIG_MOTION_BLUR_COMPILE_FP16]_
- L45 `#define mb_short int16_t` _[#if CONFIG_MOTION_BLUR_COMPILE_FP16]_
- L46 `#define mb_short2 int16_t2` _[#if CONFIG_MOTION_BLUR_COMPILE_FP16]_
- L47 `#define mb_short3 int16_t3` _[#if CONFIG_MOTION_BLUR_COMPILE_FP16]_
- L48 `#define mb_short4 int16_t4` _[#if CONFIG_MOTION_BLUR_COMPILE_FP16]_
- L50 `#define mb_ushort uint16_t` _[#if CONFIG_MOTION_BLUR_COMPILE_FP16]_
- L51 `#define mb_ushort2 uint16_t2` _[#if CONFIG_MOTION_BLUR_COMPILE_FP16]_
- L52 `#define mb_ushort3 uint16_t3` _[#if CONFIG_MOTION_BLUR_COMPILE_FP16]_
- L53 `#define mb_ushort4 uint16_t4` _[#if CONFIG_MOTION_BLUR_COMPILE_FP16]_
- L55 `#define mb_half2x2 half2x2` _[#if CONFIG_MOTION_BLUR_COMPILE_FP16]_
- L56 `#define mb_half3x2 half3x2` _[#if CONFIG_MOTION_BLUR_COMPILE_FP16]_
- L57 `#define mb_half4x2 half4x2` _[#if CONFIG_MOTION_BLUR_COMPILE_FP16]_
- L59 `#define mb_short2x2 int16_t2x2` _[#if CONFIG_MOTION_BLUR_COMPILE_FP16]_
- L60 `#define mb_short3x2 int16_t3x2` _[#if CONFIG_MOTION_BLUR_COMPILE_FP16]_
- L61 `#define mb_short4x2 int16_t4x2` _[#if CONFIG_MOTION_BLUR_COMPILE_FP16]_
- L63 `#define mb_ushort2x2 uint16_t2x2` _[#if CONFIG_MOTION_BLUR_COMPILE_FP16]_
- L64 `#define mb_ushort3x2 uint16_t3x2` _[#if CONFIG_MOTION_BLUR_COMPILE_FP16]_
- L65 `#define mb_ushort4x2 uint16_t4x2` _[#if CONFIG_MOTION_BLUR_COMPILE_FP16]_
- L68 `#define mb_half float` _[#if !(CONFIG_MOTION_BLUR_COMPILE_FP16)]_
- L69 `#define mb_half2 float2` _[#if !(CONFIG_MOTION_BLUR_COMPILE_FP16)]_
- L70 `#define mb_half3 float3` _[#if !(CONFIG_MOTION_BLUR_COMPILE_FP16)]_
- L71 `#define mb_half4 float4` _[#if !(CONFIG_MOTION_BLUR_COMPILE_FP16)]_
- L73 `#define mb_short int` _[#if !(CONFIG_MOTION_BLUR_COMPILE_FP16)]_
- L74 `#define mb_short2 int2` _[#if !(CONFIG_MOTION_BLUR_COMPILE_FP16)]_
- L75 `#define mb_short3 int3` _[#if !(CONFIG_MOTION_BLUR_COMPILE_FP16)]_
- L76 `#define mb_short4 int4` _[#if !(CONFIG_MOTION_BLUR_COMPILE_FP16)]_
- L78 `#define mb_ushort uint` _[#if !(CONFIG_MOTION_BLUR_COMPILE_FP16)]_
- L79 `#define mb_ushort2 uint2` _[#if !(CONFIG_MOTION_BLUR_COMPILE_FP16)]_
- L80 `#define mb_ushort3 uint3` _[#if !(CONFIG_MOTION_BLUR_COMPILE_FP16)]_
- L81 `#define mb_ushort4 uint4` _[#if !(CONFIG_MOTION_BLUR_COMPILE_FP16)]_
- L83 `#define mb_half2x2 float2x2` _[#if !(CONFIG_MOTION_BLUR_COMPILE_FP16)]_
- L84 `#define mb_half3x2 float3x2` _[#if !(CONFIG_MOTION_BLUR_COMPILE_FP16)]_
- L85 `#define mb_half4x2 float4x2` _[#if !(CONFIG_MOTION_BLUR_COMPILE_FP16)]_
- L87 `#define mb_short2x2 int2x2` _[#if !(CONFIG_MOTION_BLUR_COMPILE_FP16)]_
- L88 `#define mb_short3x2 int3x2` _[#if !(CONFIG_MOTION_BLUR_COMPILE_FP16)]_
- L89 `#define mb_short4x2 int4x2` _[#if !(CONFIG_MOTION_BLUR_COMPILE_FP16)]_
- L91 `#define mb_ushort2x2 uint2x2` _[#if !(CONFIG_MOTION_BLUR_COMPILE_FP16)]_
- L92 `#define mb_ushort3x2 uint3x2` _[#if !(CONFIG_MOTION_BLUR_COMPILE_FP16)]_
- L93 `#define mb_ushort4x2 uint4x2` _[#if !(CONFIG_MOTION_BLUR_COMPILE_FP16)]_
- L100 `#define FILTER_TILE_CLASSIFY_GATHER_HALF_RES 0`
- L101 `#define FILTER_TILE_CLASSIFY_GATHER_FULL_RES 1`
- L102 `#define FILTER_TILE_CLASSIFY_SCATTER_AS_GATHER_1_VELOCITY_HALF_RES 2`
- L103 `#define FILTER_TILE_CLASSIFY_SCATTER_AS_GATHER_1_VELOCITY_FULL_RES 3`
- L104 `#define FILTER_TILE_CLASSIFY_SCATTER_AS_GATHER_2_VELOCITY_FULL_RES 4`
- L105 `#define FILTER_TILE_CLASSIFY_COUNT 5`
- L11 #pragma `warning(error: 3206)`

#### Structs / classes (1)

- L170-174 _struct_ **`FVelocityRange`** `struct FVelocityRange`
  - L172 _member_ `float2 Max[CONFIG_MAX_RANGE_SIZE];`
  - L173 _member_ `float2 Min;`

#### Functions (15)

- L111-116 _function_ `float4 MinMaxLength(float4 v0, float4 v1)`
- L118-123 _function_ `float4 MinMaxLengthPolar(float4 v0, float4 v1)`
- L125-130 _function_ `float2 CartesianToPolar(float2 Velocity)`
- L132-138 _function_ `float2 PolarToCartesian(float2 Velocity)`
- L140-150 _function_ `float GetPolarRelativeAngle(float V0, float V1)`
- L152-155 _function_ `float2 GetMaxPolarvelocity(float2 V0, float2 V1)`
- L157-160 _function_ `float2 GetMinPolarvelocity(float2 V0, float2 V1)`
- L162-165 _function_ `float2 GetMaxPolarvelocity(float2 V0, float2 V1, float2 V2)`
- L176-187 _function_ `FVelocityRange SetupPolarVelocityRange(float2 PolarVelocity)`
- L189-208 _function_ `FVelocityRange ReducePolarVelocityRange(FVelocityRange V0, FVelocityRange V1)`
- L210-219 _function_ `FVelocityRange CartesianToPolar(FVelocityRange CartesianRange)`
- L221-230 _function_ `FVelocityRange PolarToCartesian(FVelocityRange PolarRange)`
- L232-241 _function_ `void StoreVelocityRange( RWTexture2DArray<float4> VelocityFlatTextureArray, uint2 PixelCoord, FVelocityRange CartesianRange)`
- L243-254 _function_ `FVelocityRange DecodeVelocityRange( float4 Raw0, float4 Raw1)`
- L256-265 _function_ `FVelocityRange LoadVelocityRange( Texture2D<float4> VelocityFlatTexture_0, Texture2D<float4> VelocityTileTexture_1, uint2 PixelCoord)`

### `Shaders/Private/MotionBlur/MotionBlurFilterTileClassify.usf` (Private)

- lines: 186; parse: all-branches
- includes: L6 `MotionBlurCommon.ush`

#### Macros (#define, 2)

- L3 `#define CONFIG_MAX_RANGE_SIZE DIM_BLUR_DIRECTIONS`
- L10 `#define TILE_SIZE 16`

#### Entry points (2)

- L43-50 _entry_ `[numthreads(FILTER_TILE_CLASSIFY_COUNT, 1, 1)] void MainCS(uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FMotionBlurFilterTileClassifyCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/PostProcessMotionBlur.cpp:568) — C++: `FSetupMotionBlurFilterCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/PostProcessMotionBlur.cpp:569) _[#if defined(SETUP_PASS)]_
- L54-183 _entry_ `[numthreads(TILE_SIZE, TILE_SIZE, 1)] void MainCS( uint2 GroupId : SV_GroupID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FMotionBlurFilterTileClassifyCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/PostProcessMotionBlur.cpp:568) — C++: `FSetupMotionBlurFilterCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/PostProcessMotionBlur.cpp:569) _[#if !(defined(SETUP_PASS))]_

#### Global resources (textures / buffers / samplers) (5)

- L22 _resource_ `Texture2D VelocityTileTextures_Textures_0;`
- L23 _resource_ `Texture2D VelocityTileTextures_Textures_1;`
- L28 _resource_ `RWTexture2D<float4> DebugOutput;`
- L40 _resource_ `StructuredBuffer<uint> TileListsSizeBuffer;` _[#if defined(SETUP_PASS)]_
- L41 _resource_ `RWBuffer<uint> DispatchParametersOutput;` _[#if defined(SETUP_PASS)]_

#### Global parameters (uniforms) (8)

- L15 _parameter_ `FScreenTransform FilterTileIdToFlattenTileId;`
- L16 _parameter_ `uint2 FlattenTileMaxId;`
- L17 _parameter_ `uint2 FilterTileCount;`
- L18 _parameter_ `uint bAllowHalfResGather;`
- L19 _parameter_ `uint TileListMaxSize;`
- L20 _parameter_ `float HalfResPixelVelocityThreshold;`
- L25 _parameter_ `RWCoherentStructuredBuffer(uint) TileListsOutput;`
- L26 _parameter_ `RWCoherentStructuredBuffer(uint) TileListsSizeOutput;`

#### groupshared (1)

- L33 _groupshared_ `groupshared uint SharedTileCount[FILTER_TILE_CLASSIFY_COUNT];`

### `Shaders/Private/MotionBlur/MotionBlurTileGather.usf` (Private)

- lines: 92; parse: all-branches
- includes: L5 `MotionBlurCommon.ush`

#### Macros (#define, 1)

- L3 `#define CONFIG_MAX_RANGE_SIZE DIM_BLUR_DIRECTIONS`

#### Entry points (1)

- L24-91 _entry_ `[numthreads(16, 16, 1)] void MainCS( uint3 GroupId : SV_GroupID, uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID, uint GroupIndex : SV_GroupIndex)` — stage: **compute** — C++: `FMotionBlurVelocityDilateGatherCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/PostProcessMotionBlur.cpp:565)

#### Global resources (textures / buffers / samplers) (5)

- L13 _resource_ `Texture2D CenterVelocityTileTextures_Textures_0;`
- L14 _resource_ `Texture2D CenterVelocityTileTextures_Textures_1;`
- L16 _resource_ `Texture2D VelocityTileTextures_Textures_0;`
- L17 _resource_ `Texture2D VelocityTileTextures_Textures_1;`
- L19 _resource_ `RWTexture2DArray<float4> OutVelocityTileArray;`

#### Global parameters (uniforms) (1)

- L11 _parameter_ `float VelocityScaleForFlattenTiles;`

#### Top-level macro invocations (1)

- L10 _macro_call_ `SCREEN_PASS_TEXTURE_VIEWPORT(VelocityTile)`

### `Shaders/Private/MotionBlur/MotionBlurTileScatter.usf` (Private)

- lines: 102; parse: all-branches
- includes: L6 `MotionBlurCommon.ush`

#### Macros (#define, 3)

- L3 `#define CONFIG_MAX_RANGE_SIZE 1`
- L10 `#define VELOCITY_SCATTER_PASS_MIN 0`
- L11 `#define VELOCITY_SCATTER_PASS_MAX 1`

#### Entry points (2)

- L26-94 _entry_ `void MainVS( uint VId : SV_VertexID, uint IId : SV_InstanceID, out nointerpolation float4 OutColor : TEXCOORD0, out float4 OutPosition : SV_POSITION)` — stage: **vertex (from C++ binding)** — C++: `FMotionBlurVelocityDilateScatterVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/PostProcessMotionBlur.cpp:566)
- L96-101 _entry_ `void MainPS( nointerpolation float4 InColor : TEXCOORD0, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FMotionBlurVelocityDilateScatterPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/PostProcessMotionBlur.cpp:567)

#### Global resources (textures / buffers / samplers) (2)

- L20 _resource_ `Texture2D VelocityTileTextures_Textures_0;`
- L21 _resource_ `Texture2D VelocityTileTextures_Textures_1;`

#### Global parameters (uniforms) (2)

- L17 _parameter_ `float VelocityScaleForFlattenTiles;`
- L18 _parameter_ `uint ScatterPass;`

#### Top-level macro invocations (1)

- L16 _macro_call_ `SCREEN_PASS_TEXTURE_VIEWPORT(VelocityTile)`

### `Shaders/Private/MotionBlur/MotionBlurVelocityFlatten.usf` (Private)

- lines: 166; parse: all-branches
- includes: L5 `MotionBlurVelocityFlatten.ush`, L6 `../LensDistortion.ush`

#### Macros (#define, 4)

- L3 `#define CONFIG_MAX_RANGE_SIZE DIM_BLUR_DIRECTIONS`
- L11 `#define TILE_SIZE (VELOCITY_FLATTEN_TILE_SIZE)`
- L12 `#define THREADGROUP_TOTALSIZE (TILE_SIZE * TILE_SIZE)`
- L16 `#define CAMERA_MOTION_BLUR_MODE 1` _[#if !defined(CAMERA_MOTION_BLUR_MODE)]_

#### Entry points (1)

- L79-165 _entry_ `[numthreads(VELOCITY_FLATTEN_TILE_SIZE, VELOCITY_FLATTEN_TILE_SIZE, 1)] void MainCS( uint2 GroupId : SV_GroupID, uint2 DispatchThreadId : SV_DispatchThreadID, uint2 GroupThreadId : SV_GroupThreadID, uint GroupIndex : SV_GroupIndex)` — stage: **compute** — C++: `FMotionBlurVelocityFlattenCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/PostProcessMotionBlur.cpp:564)

#### Global resources (textures / buffers / samplers) (9)

- L22 _resource_ `Texture2D<float2> DistortingDisplacementTexture;`
- L23 _resource_ `SamplerState DistortingDisplacementSampler;`
- L25 _resource_ `Texture2D<float2> UndistortingDisplacementTexture;`
- L26 _resource_ `SamplerState UndistortingDisplacementSampler;`
- L37 _resource_ `Texture2D VelocityTexture;`
- L38 _resource_ `Texture2D DepthTexture;`
- L40 _resource_ `RWTexture2D<float3> OutVelocityFlatTexture;`
- L41 _resource_ `RWTexture2DArray<float4> OutVelocityTileArray;`
- L43 _resource_ `RWTexture2D<float4> DebugOutput;`

#### Global parameters (uniforms) (6)

- L30 _parameter_ `float4x4 ClipToPrevClipOverride;`
- L31 _parameter_ `FScreenTransform ThreadIdToViewportUV;`
- L32 _parameter_ `FScreenTransform ViewportUVToPixelPos;`
- L33 _parameter_ `uint bCancelCameraMotion;`
- L34 _parameter_ `uint bAddCustomCameraMotion;`
- L35 _parameter_ `uint bLensDistortion;`

#### Functions (2)

- L48-57 _function_ `float2 GetCameraMotionVelocity(uint2 DispatchThreadId, float Depth, float4x4 ClipToPrevClip)`
- L59-74 _function_ `float2 PreprocessVelocityForMotionBlur(uint2 DispatchThreadId, float DeviceZ, float2 Velocity, float2 CameraMotionVelocity)`

#### Top-level macro invocations (1)

- L28 _macro_call_ `SCREEN_PASS_TEXTURE_VIEWPORT(Velocity)`

### `Shaders/Private/MotionBlur/MotionBlurVelocityFlatten.ush` (Private)

- lines: 146; parse: all-branches
- includes: L3 `MotionBlurCommon.ush`

#### Macros (#define, 1)

- L8 `#define VELOCITY_FLATTEN_THREAD_COUNT (VELOCITY_FLATTEN_TILE_SIZE * VELOCITY_FLATTEN_TILE_SIZE)`

#### Global parameters (uniforms) (2)

- L13 _parameter_ `float2 VelocityScale;`
- L14 _parameter_ `float VelocityMax;`

#### groupshared (2)

- L19 _groupshared_ `groupshared float4 SharedArray0[VELOCITY_FLATTEN_THREAD_COUNT];`
- L20 _groupshared_ `groupshared float2 SharedArray1[VELOCITY_FLATTEN_THREAD_COUNT];`

#### Functions (5)

- L25-32 _function_ `void WritePolarVelocityRangeToLDS(uint LDSSlotId, FVelocityRange V)`
- L34-43 _function_ `FVelocityRange ReadPolarVelocityRangeFromLDS(uint LDSSlotId)`
- L45-65 _function_ `void VelocityFlattenStep(uint GroupIndex, const uint GroupSize, inout FVelocityRange V)`
- L67-135 _function_ `void ReduceVelocityFlattenTile(uint GroupIndex, float2 Velocity, out FVelocityRange OutVelocityPolarRange, out float2 VelocityPolar)`
- L137-145 _function_ `float3 EncodeVelocityFlatten(float2 VelocityPolar, float DeviceZ)`

### `Shaders/Private/MotionBlur/MotionBlurVisualize.usf` (Private)

- lines: 314; parse: all-branches
- includes: L5 `MotionBlurCommon.ush`, L6 `../LensDistortion.ush`, L7 `../ColorMap.ush`

#### Macros (#define, 10)

- L3 `#define CONFIG_MAX_RANGE_SIZE 1`
- L12 `#define MOTIONBLUR_TESTCHART 0`
- L14 `#define VISUALIZE_COLOR_ENCODING 1`
- L15 `#define TILE_SIZE 48.0f`
- L16 `#define COLOR_METER_LENGTH TILE_SIZE`
- L17 `#define COLOR_METER_OFFSET 5`
- L46 `#define SharedVelocitySampler VelocitySampler` _[#if SUPPORTS_INDEPENDENT_SAMPLERS]_
- L47 `#define SharedDepthSampler VelocitySampler` _[#if SUPPORTS_INDEPENDENT_SAMPLERS]_
- L49 `#define SharedVelocitySampler VelocitySampler` _[#if !(SUPPORTS_INDEPENDENT_SAMPLERS)]_
- L50 `#define SharedDepthSampler DepthSampler` _[#if !(SUPPORTS_INDEPENDENT_SAMPLERS)]_

#### Entry points (1)

- L134-313 _entry_ `void MainPS( float4 SvPosition : SV_POSITION, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FMotionBlurVisualizePS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/PostProcessMotionBlur.cpp:571)

#### Global resources (textures / buffers / samplers) (8)

- L21 _resource_ `Texture2D<float2> UndistortingDisplacementTexture;`
- L22 _resource_ `SamplerState UndistortingDisplacementSampler;`
- L26 _resource_ `Texture2D VelocityTexture;`
- L27 _resource_ `Texture2D DepthTexture;`
- L29 _resource_ `SamplerState VelocitySampler;`
- L30 _resource_ `SamplerState DepthSampler;`
- L40 _resource_ `Texture2D PostMotionBlurTranslucencyTexture;` _[#if USE_POST_MOTION_BLUR_TRANSLUCENCY]_
- L41 _resource_ `SamplerState PostMotionBlurTranslucencySampler;` _[#if USE_POST_MOTION_BLUR_TRANSLUCENCY]_

#### Global parameters (uniforms) (5)

- L32 _parameter_ `FScreenTransform SvPositionToScreenPos;`
- L33 _parameter_ `FScreenTransform ScreenPosToColorUV;`
- L34 _parameter_ `FScreenTransform ScreenPosToVelocityUV;`
- L35 _parameter_ `int CheckerboardEnabled;`
- L36 _parameter_ `int VisualizeMode;`

#### Functions (3)

- L61-115 _function_ `void OverrideWithTestChart(float2 ScreenPos, inout float2 ObjectVelocity, inout float2 BackgroundVelocity, inout float4 Color, inout float AvgObject)` — debug motionblur (very useful, keep) @param ScreenPos -1..1 -1..1 for viewport @param Velocity in -1..1 range for full motionblur @apram Color RGB and depth in alpha @param AvgObject 0:background, 1:foregound
- L118-122 _function_ `float3 PeriodicWorldPosition(float3 TranslatedWorldPosition, float Scale)` — Scale must be a power of two
- L126-130 _function_ `float Compute3DCheckerBoard(float3 Pos)` — used to visualize the motion blur @return 0/1

#### Top-level macro invocations (1)

- L24 _macro_call_ `SCREEN_PASS_TEXTURE_VIEWPORT(Velocity)`

### `Shaders/Private/MotionBlur/VisualizeMotionVectors.usf` (Private)

- lines: 126; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../ScreenPass.ush`, L5 `../LensDistortion.ush`

#### Entry points (1)

- L51-125 _entry_ `void MainPS( float4 SvPosition : SV_POSITION, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FVisualizeMotionVectorsPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/VisualizeMotionVectors.cpp:44)

#### Global resources (textures / buffers / samplers) (12)

- L10 _resource_ `Texture2D<float2> PrevDistortingDisplacementTexture;`
- L11 _resource_ `SamplerState PrevDistortingDisplacementSampler;`
- L12 _resource_ `Texture2D<float2> UndistortingDisplacementTexture;`
- L13 _resource_ `SamplerState UndistortingDisplacementSampler;`
- L15 _resource_ `Texture2D ColorTexture;`
- L16 _resource_ `Texture2D VelocityTexture;`
- L17 _resource_ `Texture2D DepthTexture;`
- L18 _resource_ `Texture2D PrevColorTexture;`
- L24 _resource_ `SamplerState ColorSampler;`
- L25 _resource_ `SamplerState VelocitySampler;`
- L26 _resource_ `SamplerState DepthSampler;`
- L27 _resource_ `SamplerState PrevColorSampler;`

#### Global parameters (uniforms) (5)

- L29 _parameter_ `FScreenTransform SvPositionToScreenPos;`
- L30 _parameter_ `FScreenTransform ScreenPosToVelocity;`
- L31 _parameter_ `FScreenTransform ScreenPosToColor;`
- L32 _parameter_ `FScreenTransform PrevScreenPosToPrevColor;`
- L33 _parameter_ `uint VisualizeType;`

#### Functions (1)

- L38-46 _function_ `float2 ComputeStaticVelocity(float2 ScreenPos, float DeviceZ)`

#### Top-level macro invocations (3)

- L20 _macro_call_ `SCREEN_PASS_TEXTURE_VIEWPORT(Color)`
- L21 _macro_call_ `SCREEN_PASS_TEXTURE_VIEWPORT(Velocity)`
- L22 _macro_call_ `SCREEN_PASS_TEXTURE_VIEWPORT(PrevColor)`
