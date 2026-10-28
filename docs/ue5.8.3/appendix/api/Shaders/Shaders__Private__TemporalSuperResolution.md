# Shaders / Shaders/Private/TemporalSuperResolution

- files: 23; lines: 10874
- record kinds: cpp_binding=12, define=276, entry=13, function=277, groupshared=16, include=57, macro_call=5, member=30, method=10, parameter=152, resource=101, static_const=50, static_var=17, struct=6

### `Shaders/Private/TemporalSuperResolution/TSRClearPrevTextures.usf` (Private)

- lines: 47; parse: all-branches
- includes: L3 `TSRClosestOccluder.ush`

#### Macros (#define, 2)

- L8 `#define TILE_SIZE 8`
- L10 `#define TILE_ROWS 2`

#### Entry points (1)

- L20-46 _entry_ `[numthreads(TILE_SIZE * TILE_SIZE, 1, 1)] void ClearPrevTexturesCS( uint2 GroupId : SV_GroupID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FTSRClearPrevTexturesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/TemporalSuperResolution.cpp:1508)

#### Global resources (textures / buffers / samplers) (1)

- L15 _resource_ `RWTexture2DArray<uint> PrevAtomicOutput;`

### `Shaders/Private/TemporalSuperResolution/TSRClosestOccluder.ush` (Private)

- lines: 332; parse: all-branches
- includes: L5 `TSRCommon.ush`

#### Macros (#define, 5)

- L10 `#define CONFIG_SUPPORT_ORTHO_VIEW 1`
- L12 `#define VELOCITY_HOLE_FILLING_BITS 18`
- L13 `#define VELOCITY_HOLE_FILLING_LENGTH_BITS 13`
- L14 `#define VELOCITY_HOLE_FILLING_ANGLE_BITS (VELOCITY_HOLE_FILLING_BITS - VELOCITY_HOLE_FILLING_LENGTH_BITS)`
- L15 `#define VELOCITY_HOLE_FILLING_LENGTH_PRECISION (pow(2.0, 5))`
- L3 #pragma `once`

#### Global parameters (uniforms) (2)

- L20 _parameter_ `float2 PrevOutputBufferUVMin;`
- L21 _parameter_ `float2 PrevOutputBufferUVMax;`

#### Functions (9)

- L26-31 _function_ `CALL_SITE_DEBUGLOC void PolarCoordinateHoleFillingVelocity(float2 PixelVelocity, out float PixelVelocityAngle, out float PixelVelocityLength)`
- L33-39 _function_ `CALL_SITE_DEBUGLOC float2 CartesianHoleFillingVelocity(float PixelVelocityAngle, float PixelVelocityLength)`
- L41-53 _function_ `CALL_SITE_DEBUGLOC void QuantizeHoleFillingVelocity(float2 PixelVelocity, out float EncodedAngle, out float EncodedLength)`
- L55-70 _function_ `CALL_SITE_DEBUGLOC uint EncodeHoleFillingVelocity(float2 PixelVelocity)`
- L72-87 _function_ `CALL_SITE_DEBUGLOC void DecodeHoleFillingVelocity(uint EncodedHoleFillingVelocity, out float PixelAngle, out float PixelLength)`
- L89-96 _function_ `CALL_SITE_DEBUGLOC float GetMaxEncodableHoleFillingPixelLength()`
- L101-158 _function_ `void ScatterClosestOccluder(globallycoherent RWTexture2DArray<uint> PrevAtomicOutput, bool bValidOutputPixel, float2 ScreenPos, float2 FinalScreenVelocity, float PrevClosestDeviceZ)`
- L160-188 _function_ `void LoadPrevAtomicTexturesSamples( Texture2DArray<uint> PrevAtomicTextureArray, float2 PrevScreenPos, out uint HistoryClosestDeviceZSamples0[4], out uint HistoryClosestDeviceZSamples1[4])`
- L190-331 _function_ `void ProcessPrevAtomicTexturesSamples( uint HistoryClosestDeviceZSamples0[4], uint HistoryClosestDeviceZSamples1[4], float2 ScreenPos, float2 ScreenVelocity, float PrevDeviceZ, float DeviceZError, bool bIsOffScreen, out bool bIsParallaxDisocclusion, out float2 HoleFillingPixelVelocity, out bool bCanHoleFill)`

### `Shaders/Private/TemporalSuperResolution/TSRColorSpace.ush` (Private)

- lines: 294; parse: all-branches
- includes: L5 `TSRCommon.ush`

#### Macros (#define, 1)

- L53 `#define HDR_WEIGHT_SAFE_MIN_VALUE 0.0001`
- L3 #pragma `once`

#### static const (6)

- L42 _static_const_ `static const tsr_half3 LargestSceneColorRGB = (LargestNormalNumber * tsr_half(0.25)).xxx;` — Largest encodable scene color value to not overflaw in Luma4() with halfs on console
- L43 _static_const_ `static const tsr_half4 LargestSceneColorRGBA = (LargestNormalNumber * tsr_half(0.25)).xxxx;`
- L46 _static_const_ `static const tsr_half kMoireLumaToChannel = tsr_half(3.0);` — Weight of each channel for the computation of luminance.
- L47 _static_const_ `static const tsr_half3 kMoireSMCSWeights = rcp(kMoireLumaToChannel).xxx;`
- L49 _static_const_ `static const float kHistoryAccumulationPreceptionAdd = 1.0;`
- L50 _static_const_ `static const float kGCSPreceptionAdd = 0.17;`

#### Functions (32)

- L58-63 _function_ `CALL_SITE_DEBUGLOC tsr_half3 LinearToGCS(tsr_half3 LinearColor)`
- L65-69 _function_ `CALL_SITE_DEBUGLOC tsr_half4 LinearToGCS(tsr_half4 LinearColor)`
- L71-78 _function_ `CALL_SITE_DEBUGLOC tsr_half3 GCSToLinear(tsr_half3 GColor)`
- L80-84 _function_ `CALL_SITE_DEBUGLOC tsr_half4 GCSToLinear(tsr_half4 GColor)`
- L86-90 _function_ `CALL_SITE_DEBUGLOC tsr_half3 PreExposureCorrectGCS(tsr_half3 GColor, const float PreExposureCorrection)`
- L92-96 _function_ `CALL_SITE_DEBUGLOC tsr_half4 PreExposureCorrectGCS(tsr_half4 GColor, const float PreExposureCorrection)`
- L101-106 _function_ `CALL_SITE_DEBUGLOC tsr_half GCSToSMCS(tsr_half GColor)`
- L108-113 _function_ `CALL_SITE_DEBUGLOC tsr_half3 GCSToSMCS(tsr_half3 GColor)`
- L115-119 _function_ `CALL_SITE_DEBUGLOC tsr_half4 GCSToSMCS(tsr_half4 GColor)`
- L121-126 _function_ `CALL_SITE_DEBUGLOC tsr_half3 SMCSToGCS(tsr_half3 SMColor)`
- L128-132 _function_ `CALL_SITE_DEBUGLOC tsr_half4 SMCSToGCS(tsr_half4 GColor)`
- L137-141 _function_ `CALL_SITE_DEBUGLOC tsr_half3 LinearToSMCS(tsr_half3 LinearColor)`
- L143-147 _function_ `CALL_SITE_DEBUGLOC tsr_half4 LinearToSMCS(tsr_half4 LinearColor)`
- L149-153 _function_ `CALL_SITE_DEBUGLOC tsr_half3 SMCSToLinear(tsr_half3 SMColor)`
- L155-159 _function_ `CALL_SITE_DEBUGLOC tsr_half4 SMCSToLinear(tsr_half4 SMColor)`
- L166-170 _function_ `CALL_SITE_DEBUGLOC tsr_half2 Luma4(tsr_half3x2 Color)` — Faster but less accurate luma computation. Luma includes a scaling by 4.
- L172-176 _function_ `CALL_SITE_DEBUGLOC tsr_half2 Luma4(tsr_half4x2 Color)`
- L178-182 _function_ `CALL_SITE_DEBUGLOC tsr_half Luma4(tsr_half3 Color)`
- L184-188 _function_ `CALL_SITE_DEBUGLOC tsr_half Luma4(tsr_half4 Color)`
- L190-196 _function_ `CALL_SITE_DEBUGLOC tsr_half2 HdrWeightY(tsr_half2 Luma)`
- L198-202 _function_ `CALL_SITE_DEBUGLOC tsr_half HdrWeightY(tsr_half Luma)`
- L204-208 _function_ `CALL_SITE_DEBUGLOC tsr_half2 HdrWeightInvY(tsr_half2 LDRLuma)`
- L210-214 _function_ `CALL_SITE_DEBUGLOC tsr_half HdrWeightInvY(tsr_half LDRLuma)`
- L216-220 _function_ `CALL_SITE_DEBUGLOC tsr_half2 HdrWeight4(tsr_half3x2 Color)`
- L222-226 _function_ `CALL_SITE_DEBUGLOC tsr_half2 HdrWeight4(tsr_half4x2 Color)`
- L228-232 _function_ `CALL_SITE_DEBUGLOC tsr_half HdrWeight4(tsr_half3 Color)`
- L234-238 _function_ `CALL_SITE_DEBUGLOC tsr_half HdrWeight4(tsr_half4 Color)`
- L243-248 _function_ `CALL_SITE_DEBUGLOC tsr_half MeasureBackbufferLDRQuantizationError()`
- L253-257 _function_ `CALL_SITE_DEBUGLOC tsr_half3x2 QuantizeForUNormRenderTarget(tsr_half3x2 Color, tsr_half E, const float3 QuantizationError)`
- L259-263 _function_ `CALL_SITE_DEBUGLOC tsr_half3 QuantizeForUNormRenderTarget(tsr_half3 Color, tsr_half E, const float3 QuantizationError)`
- L265-287 _function_ `CALL_SITE_DEBUGLOC tsr_half3x2 QuantizeForFloatRenderTarget(tsr_half3x2 Color, tsr_half E, const float3 QuantizationError)`
- L289-293 _function_ `CALL_SITE_DEBUGLOC tsr_half3 QuantizeForFloatRenderTarget(tsr_half3 Color, tsr_half E, const float3 QuantizationError)`

### `Shaders/Private/TemporalSuperResolution/TSRCommon.ush` (Private)

- lines: 506; parse: first-branch (retry, +0 merged from all-branches pass)
- includes: L5 `../Common.ush`, L6 `../Random.ush`, L7 `../TextureSampling.ush`, L8 `../FastMath.ush`, L9 `../MonteCarlo.ush`, L10 `../ScreenPass.ush`, L11 `/Engine/Public/DualPixelVectorization.ush`, L12 `/Engine/Public/WaveBroadcastIntrinsics.ush`

#### Macros (#define, 76)

- L28 `#define DEBUG_OUTPUT 0`
- L31 `#define CONFIG_COMPILE_FP16 DIM_16BIT_VALU` _[#if defined(DIM_16BIT_VALU)]_
- L33 `#define CONFIG_COMPILE_FP16 1` _[#if !(defined(DIM_16BIT_VALU)) && PLATFORM_SUPPORTS_REAL_TYPES]_
- L35 `#define CONFIG_COMPILE_FP16 0` _[#if !(defined(DIM_16BIT_VALU)) && !(PLATFORM_SUPPORTS_REAL_TYPES)]_
- L38 `#define CONFIG_SCENE_COLOR_OVERFLOW 1`
- L41 `#define CONFIG_SCENE_COLOR_ALPHA DIM_ALPHA_CHANNEL` _[#if defined(DIM_ALPHA_CHANNEL)]_
- L43 `#define CONFIG_SCENE_COLOR_ALPHA 0` _[#if !(defined(DIM_ALPHA_CHANNEL))]_
- L46 `#define CONFIG_ENABLE_STOCASTIC_QUANTIZATION (!CONFIG_SCENE_COLOR_ALPHA)`
- L50 `#define CONFIG_FP16_PRECISE_MULTIPLY_ORDER 1`
- L56 `#define MAX_SAMPLE_COUNT 8`
- L59 `#define tsr_half half` _[#if CONFIG_COMPILE_FP16]_
- L60 `#define tsr_half2 half2` _[#if CONFIG_COMPILE_FP16]_
- L61 `#define tsr_half3 half3` _[#if CONFIG_COMPILE_FP16]_
- L62 `#define tsr_half4 half4` _[#if CONFIG_COMPILE_FP16]_
- L64 `#define tsr_short int16_t` _[#if CONFIG_COMPILE_FP16]_
- L65 `#define tsr_short2 int16_t2` _[#if CONFIG_COMPILE_FP16]_
- L66 `#define tsr_short3 int16_t3` _[#if CONFIG_COMPILE_FP16]_
- L67 `#define tsr_short4 int16_t4` _[#if CONFIG_COMPILE_FP16]_
- L69 `#define tsr_ushort uint16_t` _[#if CONFIG_COMPILE_FP16]_
- L70 `#define tsr_ushort2 uint16_t2` _[#if CONFIG_COMPILE_FP16]_
- L71 `#define tsr_ushort3 uint16_t3` _[#if CONFIG_COMPILE_FP16]_
- L72 `#define tsr_ushort4 uint16_t4` _[#if CONFIG_COMPILE_FP16]_
- L74 `#define tsr_half2x2 half2x2` _[#if CONFIG_COMPILE_FP16]_
- L75 `#define tsr_half3x2 half3x2` _[#if CONFIG_COMPILE_FP16]_
- L76 `#define tsr_half4x2 half4x2` _[#if CONFIG_COMPILE_FP16]_
- L78 `#define tsr_short2x2 int16_t2x2` _[#if CONFIG_COMPILE_FP16]_
- L79 `#define tsr_short3x2 int16_t3x2` _[#if CONFIG_COMPILE_FP16]_
- L80 `#define tsr_short4x2 int16_t4x2` _[#if CONFIG_COMPILE_FP16]_
- L82 `#define tsr_ushort2x2 uint16_t2x2` _[#if CONFIG_COMPILE_FP16]_
- L83 `#define tsr_ushort3x2 uint16_t3x2` _[#if CONFIG_COMPILE_FP16]_
- L84 `#define tsr_ushort4x2 uint16_t4x2` _[#if CONFIG_COMPILE_FP16]_
- L86 `#define as_tsr_short(x) asint16(x)` _[#if CONFIG_COMPILE_FP16]_
- L87 `#define as_tsr_ushort(x) asuint16(x)` _[#if CONFIG_COMPILE_FP16]_
- L88 `#define as_tsr_half(x) asfloat16(x)` _[#if CONFIG_COMPILE_FP16]_
- L91 `#define tsr_half float` _[#if !(CONFIG_COMPILE_FP16)]_
- L92 `#define tsr_half2 float2` _[#if !(CONFIG_COMPILE_FP16)]_
- L93 `#define tsr_half3 float3` _[#if !(CONFIG_COMPILE_FP16)]_
- L94 `#define tsr_half4 float4` _[#if !(CONFIG_COMPILE_FP16)]_
- L96 `#define tsr_short int` _[#if !(CONFIG_COMPILE_FP16)]_
- L97 `#define tsr_short2 int2` _[#if !(CONFIG_COMPILE_FP16)]_
- L98 `#define tsr_short3 int3` _[#if !(CONFIG_COMPILE_FP16)]_
- L99 `#define tsr_short4 int4` _[#if !(CONFIG_COMPILE_FP16)]_
- L101 `#define tsr_ushort uint` _[#if !(CONFIG_COMPILE_FP16)]_
- L102 `#define tsr_ushort2 uint2` _[#if !(CONFIG_COMPILE_FP16)]_
- L103 `#define tsr_ushort3 uint3` _[#if !(CONFIG_COMPILE_FP16)]_
- L104 `#define tsr_ushort4 uint4` _[#if !(CONFIG_COMPILE_FP16)]_
- L106 `#define tsr_half2x2 float2x2` _[#if !(CONFIG_COMPILE_FP16)]_
- L107 `#define tsr_half3x2 float3x2` _[#if !(CONFIG_COMPILE_FP16)]_
- L108 `#define tsr_half4x2 float4x2` _[#if !(CONFIG_COMPILE_FP16)]_
- L110 `#define tsr_short2x2 int2x2` _[#if !(CONFIG_COMPILE_FP16)]_
- L111 `#define tsr_short3x2 int3x2` _[#if !(CONFIG_COMPILE_FP16)]_
- L112 `#define tsr_short4x2 int4x2` _[#if !(CONFIG_COMPILE_FP16)]_
- L114 `#define tsr_ushort2x2 uint2x2` _[#if !(CONFIG_COMPILE_FP16)]_
- L115 `#define tsr_ushort3x2 uint3x2` _[#if !(CONFIG_COMPILE_FP16)]_
- L116 `#define tsr_ushort4x2 uint4x2` _[#if !(CONFIG_COMPILE_FP16)]_
- L118 `#define as_tsr_short(x) asint(x)` _[#if !(CONFIG_COMPILE_FP16)]_
- L119 `#define as_tsr_ushort(x) asuint(x)` _[#if !(CONFIG_COMPILE_FP16)]_
- L120 `#define as_tsr_half(x) asfloat(x)` _[#if !(CONFIG_COMPILE_FP16)]_
- L125 `#define tsr_halfC tsr_half4` _[#if CONFIG_SCENE_COLOR_ALPHA]_
- L126 `#define tsr_halfCx2 tsr_half4x2` _[#if CONFIG_SCENE_COLOR_ALPHA]_
- L127 `#define CONFIG_CHANNEL_COUNT 4` _[#if CONFIG_SCENE_COLOR_ALPHA]_
- L130 `#define tsr_halfC tsr_half3` _[#if !(CONFIG_SCENE_COLOR_ALPHA)]_
- L131 `#define tsr_halfCx2 tsr_half3x2` _[#if !(CONFIG_SCENE_COLOR_ALPHA)]_
- L132 `#define CONFIG_CHANNEL_COUNT 3` _[#if !(CONFIG_SCENE_COLOR_ALPHA)]_
- L138 `#define tsr_half_resource float` _[#if CONFIG_COMPILE_FP16 && PLATFORM_USES_SPIRV_RESOURCE_TYPES]_
- L139 `#define tsr_half2_resource float2` _[#if CONFIG_COMPILE_FP16 && PLATFORM_USES_SPIRV_RESOURCE_TYPES]_
- L140 `#define tsr_half3_resource float3` _[#if CONFIG_COMPILE_FP16 && PLATFORM_USES_SPIRV_RESOURCE_TYPES]_
- L141 `#define tsr_half4_resource float4` _[#if CONFIG_COMPILE_FP16 && PLATFORM_USES_SPIRV_RESOURCE_TYPES]_
- L142 `#define tsr_ushort_resource uint` _[#if CONFIG_COMPILE_FP16 && PLATFORM_USES_SPIRV_RESOURCE_TYPES]_
- L144 `#define tsr_half_resource tsr_half` _[#if !(CONFIG_COMPILE_FP16 && PLATFORM_USES_SPIRV_RESOURCE_TYPES)]_
- L145 `#define tsr_half2_resource tsr_half2` _[#if !(CONFIG_COMPILE_FP16 && PLATFORM_USES_SPIRV_RESOURCE_TYPES)]_
- L146 `#define tsr_half3_resource tsr_half3` _[#if !(CONFIG_COMPILE_FP16 && PLATFORM_USES_SPIRV_RESOURCE_TYPES)]_
- L147 `#define tsr_half4_resource tsr_half4` _[#if !(CONFIG_COMPILE_FP16 && PLATFORM_USES_SPIRV_RESOURCE_TYPES)]_
- L148 `#define tsr_ushort_resource tsr_ushort` _[#if !(CONFIG_COMPILE_FP16 && PLATFORM_USES_SPIRV_RESOURCE_TYPES)]_
- L152 `#define tsr_halfC_resource tsr_half4_resource` _[#if CONFIG_SCENE_COLOR_ALPHA]_
- L154 `#define tsr_halfC_resource tsr_half3_resource` _[#if !(CONFIG_SCENE_COLOR_ALPHA)]_
- L3 #pragma `once`; L17 #pragma `message("UESHADERMETADATA_VERSION F3C5FF82-E809-4903-98CD-5DC7E2254C87")`; L23 #pragma `warning(error: 3206)`

#### Global resources (textures / buffers / samplers) (1)

- L217 _resource_ `RWTexture2DArray<float4> DebugOutput;` _[#if DEBUG_OUTPUT]_

#### Global parameters (uniforms) (46)

- L165 _parameter_ `float2 InputInfo_Extent;`
- L166 _parameter_ `float2 InputInfo_ExtentInverse;`
- L167 _parameter_ `float2 InputInfo_ScreenPosToViewportScale;`
- L168 _parameter_ `float2 InputInfo_ScreenPosToViewportBias;`
- L169 _parameter_ `uint2 InputInfo_ViewportMin;`
- L170 _parameter_ `uint2 InputInfo_ViewportMax;`
- L171 _parameter_ `float2 InputInfo_ViewportSize;`
- L172 _parameter_ `float2 InputInfo_ViewportSizeInverse;`
- L173 _parameter_ `float2 InputInfo_UVViewportMin;`
- L174 _parameter_ `float2 InputInfo_UVViewportMax;`
- L175 _parameter_ `float2 InputInfo_UVViewportSize;`
- L176 _parameter_ `float2 InputInfo_UVViewportSizeInverse;`
- L177 _parameter_ `float2 InputInfo_UVViewportBilinearMin;`
- L178 _parameter_ `float2 InputInfo_UVViewportBilinearMax;`
- L179 _parameter_ `float2 InputJitter;`
- L180 _parameter_ `int2 InputPixelPosMin;`
- L181 _parameter_ `int2 InputPixelPosMax;`
- L182 _parameter_ `FScreenTransform InputPixelPosToScreenPos;`
- L183 _parameter_ `float2 ScreenVelocityToInputPixelVelocity;`
- L184 _parameter_ `float2 InputPixelVelocityToScreenVelocity;`
- L186 _parameter_ `float2 HistoryInfo_Extent;`
- L187 _parameter_ `float2 HistoryInfo_ExtentInverse;`
- L188 _parameter_ `uint2 HistoryInfo_ViewportMin;`
- L189 _parameter_ `uint2 HistoryInfo_ViewportMax;`
- L190 _parameter_ `float2 HistoryInfo_ViewportSize;`
- L191 _parameter_ `float2 HistoryInfo_ViewportSizeInverse;`
- L192 _parameter_ `float2 HistoryInfo_UVViewportBilinearMin;`
- L193 _parameter_ `float2 HistoryInfo_UVViewportBilinearMax;`
- L196 _parameter_ `float2 PrevHistoryInfo_Extent;` — FTSRPrevHistoryParameters
- L197 _parameter_ `float2 PrevHistoryInfo_ExtentInverse;`
- L198 _parameter_ `float2 PrevHistoryInfo_ScreenPosToViewportScale;`
- L199 _parameter_ `float2 PrevHistoryInfo_ScreenPosToViewportBias;`
- L200 _parameter_ `uint2 PrevHistoryInfo_ViewportMin;`
- L201 _parameter_ `uint2 PrevHistoryInfo_ViewportMax;`
- L202 _parameter_ `float2 PrevHistoryInfo_ViewportSize;`
- L203 _parameter_ `float2 PrevHistoryInfo_ViewportSizeInverse;`
- L204 _parameter_ `float2 PrevHistoryInfo_UVViewportMin;`
- L205 _parameter_ `float2 PrevHistoryInfo_UVViewportMax;`
- L206 _parameter_ `float2 PrevHistoryInfo_UVViewportSize;`
- L207 _parameter_ `float2 PrevHistoryInfo_UVViewportSizeInverse;`
- L208 _parameter_ `float2 PrevHistoryInfo_UVViewportBilinearMin;`
- L209 _parameter_ `float2 PrevHistoryInfo_UVViewportBilinearMax;`
- L210 _parameter_ `FScreenTransform ScreenPosToPrevHistoryBufferUV;`
- L211 _parameter_ `float HistoryPreExposureCorrection;`
- L212 _parameter_ `float ResurrectionPreExposureCorrection;`
- L214 _parameter_ `uint bCameraCut;`

#### static const (1)

- L159 _static_const_ `static const tsr_half LargestNormalNumber = tsr_half(65504.0);` — Largest encodable normal number in a half used on console.

#### Functions (27)

- L223-226 _function_ `uint sign_bit(float x)`
- L228-231 _function_ `uint2 sign_bit(float2 x)`
- L235-238 _function_ `uint16_t sign_bit(half x)` _[#if PLATFORM_SUPPORTS_REAL_TYPES]_
- L240-243 _function_ `uint16_t2 sign_bit(half2 x)` _[#if PLATFORM_SUPPORTS_REAL_TYPES]_
- L250-254 _function_ `CALL_SITE_DEBUGLOC float2x2 ApplyScreenTransform(float2x2 PInA, FScreenTransform AToB)`
- L258-262 _function_ `CALL_SITE_DEBUGLOC half2x2 ApplyScreenTransform(half2x2 PInA, FScreenTransform AToB)` _[#if PLATFORM_SUPPORTS_REAL_TYPES]_
- L268-280 _function_ `CALL_SITE_DEBUGLOC uint GetGroupWaveIndex(uint GroupThreadIndex, uint GroupSize)` — Compute the group wave index into SGRP to then recompue the GroupThreadIndex latter
- L288-303 _function_ `CALL_SITE_DEBUGLOC uint GetGroupThreadIndex(uint GroupThreadIndex, uint GroupWaveIndex)` — Force compute the group GroupThreadIndex through lane index and wave index if possible to reduce VGPR pressure.
- L310-324 _function_ `CALL_SITE_DEBUGLOC tsr_short2x2 InvalidateOutputPixelPos(tsr_short2x2 PixelPos, uint2 ViewportMax)`
- L333-347 _function_ `CALL_SITE_DEBUGLOC tsr_short2 InvalidateOutputPixelPos(tsr_short2 PixelPos, uint2 ViewportMax)`
- L356-362 _function_ `CALL_SITE_DEBUGLOC tsr_ushort2 Map8x8Tile2x2Lane(uint GroupThreadIndex)`
- L364-374 _function_ `CALL_SITE_DEBUGLOC tsr_ushort2 Map16x16Tile2x2Lane(uint GroupThreadIndex)`
- L376-380 _function_ `CALL_SITE_DEBUGLOC float SafeRcp(float x)`
- L382-386 _function_ `CALL_SITE_DEBUGLOC float2 SafeRcp(float2 x)`
- L388-392 _function_ `CALL_SITE_DEBUGLOC float3 SafeRcp(float3 x)`
- L394-398 _function_ `CALL_SITE_DEBUGLOC float4 SafeRcp(float4 x)`
- L402-408 _function_ `CALL_SITE_DEBUGLOC half SafeRcp(half x)` _[#if CONFIG_COMPILE_FP16]_
- L415-421 _function_ `CALL_SITE_DEBUGLOC half2 SafeRcp(half2 x)` _[#if CONFIG_COMPILE_FP16]_
- L428-434 _function_ `CALL_SITE_DEBUGLOC half3 SafeRcp(half3 x)` _[#if CONFIG_COMPILE_FP16]_
- L441-447 _function_ `CALL_SITE_DEBUGLOC half4 SafeRcp(half4 x)` _[#if CONFIG_COMPILE_FP16]_
- L456-465 _function_ `CALL_SITE_DEBUGLOC tsr_half2x2 WeightedLerpFactors(tsr_half2 WeightA, tsr_half2 WeightB, tsr_half2 Blend)`
- L467-474 _function_ `CALL_SITE_DEBUGLOC tsr_half2 WeightedLerpFactors(tsr_half WeightA, tsr_half WeightB, tsr_half Blend)`
- L476-480 _function_ `CALL_SITE_DEBUGLOC bool TakeOnlyOneSamplePair(float2 Offset)`
- L482-485 _function_ `tsr_half ComputePredictionCompleteness(tsr_half SampleHistoryValidity)`
- L487-495 _function_ `CALL_SITE_DEBUGLOC void IsOffScreenOrDisoccluded(uint bCameraCut, float2x2 ScreenPos, bool2 bIsParallaxRejected, out bool2 bIsOffScreen, out bool2 bIsDisoccluded)`
- L497-500 _function_ `tsr_half2 ComputePrevWeightMultiplier(tsr_half2 BlendFactor)`
- L502-505 _function_ `tsr_half2 RejectionFactorToBlendFactor(tsr_half2 RejectionFactor)`

### `Shaders/Private/TemporalSuperResolution/TSRConvolutionNetwork.ush` (Private)

- lines: 1159; parse: first-branch (retry, +0 merged from all-branches pass)
- includes: L5 `TSRKernels.ush`, L6 `/Engine/Public/LaneVectorization.ush`

#### Macros (#define, 2)

- L30 `#define WAVE_COUNT (WAVE_COUNT_X * WAVE_COUNT_Y)`
- L33 `#define LANE_COUNT (LANE_COUNT_X * LANE_COUNT_Y)`
- L3 #pragma `once`

#### Structs / classes (2)

- L672-698 _struct_ **`TConvolutionSinkMin`** `template<typename ScalarType, uint VectorSize, uint InSimdSizeX, uint InSimdSizeY> struct TConvolutionSinkMin`
  - L675 _member_ `static const uint RegisterRowSize = TLaneVector2D<ScalarType, VectorSize, InSimdSizeX, InSimdSizeY>::RegisterRowSize;`
  - L675 _member_ `static const uint RegisterRowSize = TLaneVector2D<ScalarType, VectorSize, InSimdSizeX, InSimdSizeY>::RegisterRowSize;`
  - L675 _member_ `static const uint RegisterRowSize = TLaneVector2D<ScalarType, VectorSize, InSimdSizeX, InSimdSizeY>::RegisterRowSize;`
  - L675 _member_ `static const uint RegisterRowSize = TLaneVector2D<ScalarType, VectorSize, InSimdSizeX, InSimdSizeY>::RegisterRowSize;`
  - L677 _member_ `uint Unused;`
  - L679 _method_ `vector<ScalarType, VectorSize> ConvolveElements3x1(vector<ScalarType, VectorSize> N, vector<ScalarType, VectorSize> C, vector<ScalarType, VectorSize> P)`
  - L684 _method_ `vector<ScalarType, VectorSize> ConvolveElements1x3(vector<ScalarType, VectorSize> N, vector<ScalarType, VectorSize> C, vector<ScalarType, VectorSize> P)`
  - L689 _method_ `vector<ScalarType, RegisterRowSize> ConvolveRegisterRows3x1(vector<ScalarType, RegisterRowSize> N, vector<ScalarType, RegisterRowSize> C, vector<ScalarType, RegisterRowSize> P)`
  - L694 _method_ `vector<ScalarType, RegisterRowSize> ConvolveRegisterRows1x3(vector<ScalarType, RegisterRowSize> N, vector<ScalarType, RegisterRowSize> C, vector<ScalarType, RegisterRowSize> P)`
- L700-726 _struct_ **`TConvolutionSinkMax`** `template<typename ScalarType, uint VectorSize, uint InSimdSizeX, uint InSimdSizeY> struct TConvolutionSinkMax`
  - L703 _member_ `static const uint RegisterRowSize = TLaneVector2D<ScalarType, VectorSize, InSimdSizeX, InSimdSizeY>::RegisterRowSize;`
  - L703 _member_ `static const uint RegisterRowSize = TLaneVector2D<ScalarType, VectorSize, InSimdSizeX, InSimdSizeY>::RegisterRowSize;`
  - L703 _member_ `static const uint RegisterRowSize = TLaneVector2D<ScalarType, VectorSize, InSimdSizeX, InSimdSizeY>::RegisterRowSize;`
  - L703 _member_ `static const uint RegisterRowSize = TLaneVector2D<ScalarType, VectorSize, InSimdSizeX, InSimdSizeY>::RegisterRowSize;`
  - L705 _member_ `uint Unused;`
  - L707 _method_ `vector<ScalarType, VectorSize> ConvolveElements3x1(vector<ScalarType, VectorSize> N, vector<ScalarType, VectorSize> C, vector<ScalarType, VectorSize> P)`
  - L712 _method_ `vector<ScalarType, VectorSize> ConvolveElements1x3(vector<ScalarType, VectorSize> N, vector<ScalarType, VectorSize> C, vector<ScalarType, VectorSize> P)`
  - L717 _method_ `vector<ScalarType, RegisterRowSize> ConvolveRegisterRows3x1(vector<ScalarType, RegisterRowSize> N, vector<ScalarType, RegisterRowSize> C, vector<ScalarType, RegisterRowSize> P)`
  - L722 _method_ `vector<ScalarType, RegisterRowSize> ConvolveRegisterRows1x3(vector<ScalarType, RegisterRowSize> N, vector<ScalarType, RegisterRowSize> C, vector<ScalarType, RegisterRowSize> P)`

#### groupshared (1)

- L201 _groupshared_ `groupshared uint SharedAtomic;`

#### Functions (48)

- L54-59 _function_ `CALL_SITE_DEBUGLOC template<uint LaneStrideX, uint LaneStrideY> tsr_short2 GetSimdIndexPixelCoordinateInLane(const uint SimdIndex)` — Returns coordinate of a pixel within a lane.
- L61-66 _function_ `CALL_SITE_DEBUGLOC template<uint LaneStrideX, uint LaneStrideY> uint GetPixelCoordinateInLaneSimdIndex(const tsr_short2 PixelCoordinateInLane)`
- L70-78 _function_ `CALL_SITE_DEBUGLOC template<uint LaneStrideX, uint LaneStrideY> tsr_short2 GetLaneSimdPixelOffset(const uint LaneIndex, const uint SimdIndex)` — Returns coordinate of a pixel within a wave.
- L81-85 _function_ `CALL_SITE_DEBUGLOC tsr_short2 GetElementPixelPosInLane(const uint LaneStrideX, const uint LaneStrideY, const uint ElementIndex)` — Returns coordinate of a element within a lane.
- L88-95 _function_ `CALL_SITE_DEBUGLOC tsr_short2 GetElementPixelOffsetInTile(const uint LaneStrideX, const uint LaneStrideY, const uint LaneIndex, const uint SimdIndex)` — Returns coordinate of a element within a tile.
- L97-123 _function_ `CALL_SITE_DEBUGLOC tsr_short2 ComputeElementInputPixelPos( const uint2 LaneStride, const uint2 TileOverscan, const uint2 PixelViewportMin, const uint2 PixelViewportMax, const uint2 GroupId, const uint GroupThreadIndex, const uint InputElementIndex, const int2 InputDataOffset = int2(0, 0), const uint InputResDivisor = 1)`
- L125-166 _function_ `CALL_SITE_DEBUGLOC tsr_short2 ComputeElementOutputPixelPos( const uint2 LaneStride, const uint2 TileOverscan, const uint2 PixelViewportMin, const uint2 PixelViewportMax, const uint2 GroupId, const uint GroupThreadIndex, const uint OutputElementIndex, const int2 OutputDataOffset = int2(0, 0), const uint OutputResDivisor = 1, const bool bDebugDisablePadding = false)`
- L171-196 _function_ `CALL_SITE_DEBUGLOC template<uint LaneStrideX, uint LaneStrideY> TLaneVector2D<bool, 1, LaneStrideX, LaneStrideY> IsValidTilePixel(const uint2 TileOverscan)`
- L203-208 _function_ `CALL_SITE_DEBUGLOC bool AnyThread(bool X)`
- L271-281 _function_ `CALL_SITE_DEBUGLOC template<uint LaneStrideX, uint LaneStrideY> uint GetNeighborElementIndex(const uint ElementIndex, const tsr_short2 Offset)`
- L285-295 _function_ `CALL_SITE_DEBUGLOC template<uint LaneStrideX, uint LaneStrideY> FWaveBroadcastSettings GetWaveBroadcastSettingsForNeighbor(const uint ElementIndex, const tsr_short2 Offset)` _[#if WAVE_COUNT_X == 1 \|\| WAVE_COUNT_Y == 1]_
- L297-318 _function_ `CALL_SITE_DEBUGLOC template<typename ScalarType, uint VectorSize, uint LaneStrideX, uint LaneStrideY> vector<ScalarType, VectorSize> WaveAccessNeighborElement( TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> Center, const uint ElementIndex, const tsr_short2 Offset)` _[#if WAVE_COUNT_X == 1 \|\| WAVE_COUNT_Y == 1]_
- L320-336 _function_ `CALL_SITE_DEBUGLOC template<typename ScalarType, uint VectorSize, uint LaneStrideX, uint LaneStrideY> TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> WaveAccessNeighborTexel( TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> Center, const tsr_short2 Offset)` _[#if WAVE_COUNT_X == 1 \|\| WAVE_COUNT_Y == 1]_
- L343-383 _function_ `CALL_SITE_DEBUGLOC template<typename ScalarType, uint VectorSize, uint LaneStrideX, uint LaneStrideY> void AccessNeighborTexels3x1( TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> CO, out TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> CP, out TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> CN)`
- L394-426 _function_ `CALL_SITE_DEBUGLOC ISOLATE template<typename ScalarType, uint VectorSize, uint LaneStrideX, uint LaneStrideY> void Write1x3CenterToLDS(TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> CO)`
- L433-471 _function_ `CALL_SITE_DEBUGLOC ISOLATE template<typename ScalarType, uint VectorSize, uint LaneStrideX, uint LaneStrideY> void Read1x3NeighborElementsFromLDS( TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> CO, const uint ElementIndex, out vector<ScalarType, VectorSize> CP, out vector<ScalarType, VectorSize> CN)`
- L479-500 _function_ `CALL_SITE_DEBUGLOC ISOLATE template<typename ScalarType, uint VectorSize, uint LaneStrideX, uint LaneStrideY> void Read1x3CenterFromLDS( TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> CO, out TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> CP, out TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> CN)`
- L502-512 _function_ `CALL_SITE_DEBUGLOC ISOLATE template<typename ScalarType, uint VectorSize, uint LaneStrideX, uint LaneStrideY> void AccessNeighborTexels1x3( TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> CO, out TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> CP, out TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> CN)`
- L517-544 _function_ `CALL_SITE_DEBUGLOC template<typename ScalarType, uint VectorSize, uint LaneStrideX, uint LaneStrideY, typename ConvolutionSinkType> TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> Convolve1x3Then3x1FromLDS(TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> C, ConvolutionSinkType ConvolutionSink)`
- L579-585 _function_ `CALL_SITE_DEBUGLOC template<typename ScalarType, uint VectorSize, uint LaneStrideX, uint LaneStrideY, typename ConvolutionSinkType> TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> Convolve1x3Then3x1(TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> Center, ConvolutionSinkType ConvolutionSink)`
- L590-612 _function_ `CALL_SITE_DEBUGLOC template<typename ScalarType, uint VectorSize, uint LaneStrideX, uint LaneStrideY> TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> WeightedSum3x3(TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> Center, float3 HorizontalWeights, float3 VerticalWeights)`
- L614-619 _function_ `CALL_SITE_DEBUGLOC template<typename ScalarType, uint VectorSize, uint LaneStrideX, uint LaneStrideY> TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> Sum3x3(TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> Center)`
- L621-626 _function_ `CALL_SITE_DEBUGLOC template<typename ScalarType, uint VectorSize, uint LaneStrideX, uint LaneStrideY> TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> WeightedAvg3x3(TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> Center, float3 NormalizedWeights)`
- L628-633 _function_ `CALL_SITE_DEBUGLOC template<typename ScalarType, uint VectorSize, uint LaneStrideX, uint LaneStrideY> TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> Blur3x3(TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> Center)`
- L635-640 _function_ `CALL_SITE_DEBUGLOC template<typename ScalarType, uint VectorSize, uint LaneStrideX, uint LaneStrideY> TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> BlurEven3x3(TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> Center)`
- L642-647 _function_ `CALL_SITE_DEBUGLOC template<typename ScalarType, uint VectorSize, uint LaneStrideX, uint LaneStrideY> TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> Sharpen3x3(TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> Center)`
- L652-660 _function_ `CALL_SITE_DEBUGLOC template<typename ScalarType, uint VectorSize, uint LaneStrideX, uint LaneStrideY> TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> TotalVariation3x3(TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> Center)`
- L728-735 _function_ `CALL_SITE_DEBUGLOC template<typename ScalarType, uint VectorSize, uint LaneStrideX, uint LaneStrideY> TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> Min3x3(TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> Center)`
- L752-759 _function_ `CALL_SITE_DEBUGLOC template<typename ScalarType, uint VectorSize, uint LaneStrideX, uint LaneStrideY> TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> Max3x3(TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> Center)`
- L776-796 _function_ `CALL_SITE_DEBUGLOC template<typename ScalarType, uint LaneStrideX, uint LaneStrideY> TLaneVector2D<ScalarType, 4, LaneStrideX, LaneStrideY> MaxRGBMinA3x3(TLaneVector2D<ScalarType, 4, LaneStrideX, LaneStrideY> Center)`
- L798-818 _function_ `CALL_SITE_DEBUGLOC template<typename ScalarType, uint LaneStrideX, uint LaneStrideY> TLaneVector2D<ScalarType, 2, LaneStrideX, LaneStrideY> MaxRMinG3x3(TLaneVector2D<ScalarType, 2, LaneStrideX, LaneStrideY> Center)`
- L820-834 _function_ `CALL_SITE_DEBUGLOC template<typename ScalarType, uint VectorSize, uint LaneStrideX, uint LaneStrideY> void MinMax3x3( TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> Center, out TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> OutMin, out TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> OutMax)`
- L862-871 _function_ `CALL_SITE_DEBUGLOC template<typename ScalarType, uint VectorSize, uint LaneStrideX, uint LaneStrideY> TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> MaxMinusMin3x3( TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> Center)`
- L876-887 _function_ `CALL_SITE_DEBUGLOC template<typename ScalarType, uint VectorSize, uint LaneStrideX, uint LaneStrideY> TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> Clamp3x3( TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> ToClamp, TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> BoundaryCenter)`
- L889-926 _function_ `CALL_SITE_DEBUGLOC template<typename ScalarType, uint VectorSize, uint LaneStrideX, uint LaneStrideY> TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> LerpClamp3x3( TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> ToClamp, TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> Boundary , TLaneVector2D<ScalarType, 1, LaneStrideX, LaneStrideY> LerpFactor)`
- L928-935 _function_ `CALL_SITE_DEBUGLOC template<typename ScalarType, uint VectorSize, uint LaneStrideX, uint LaneStrideY> TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> AnnihilateToGuide3x3( TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> ToClamp, TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> Guide)`
- L937-947 _function_ `CALL_SITE_DEBUGLOC template<typename ScalarType, uint VectorSize, uint LaneStrideX, uint LaneStrideY> void AnnihilateMutually3x3( TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> Input, TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> History, out TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> AnnihilatedInput, out TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> AnnihilatedHistory)`
- L949-958 _function_ `CALL_SITE_DEBUGLOC template<typename ScalarType, uint LaneStrideX, uint LaneStrideY> void AnnihilateMutuallySingleChannel3x3( TLaneVector2D<ScalarType, 1, LaneStrideX, LaneStrideY> Input, TLaneVector2D<ScalarType, 1, LaneStrideX, LaneStrideY> History, out TLaneVector2D<ScalarType, 1, LaneStrideX, LaneStrideY> AnnihilatedInput, out TLaneVector2D<ScalarType, 1, LaneStrideX, LaneStrideY> AnnihilatedHistory)`
- L963-979 _function_ `CALL_SITE_DEBUGLOC template<typename ScalarType, uint VectorSize, uint LaneStrideX, uint LaneStrideY> void MinMaxPlus3x3( TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> Center, out TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> OutMin, out TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> OutMax)`
- L981-992 _function_ `CALL_SITE_DEBUGLOC template<typename ScalarType, uint VectorSize, uint LaneStrideX, uint LaneStrideY> TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> ClampPlus3x3( TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> ToClamp, TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> BoundaryCenter)`
- L998-1006 _function_ `CALL_SITE_DEBUGLOC template<typename FSampleType> void LMHOperator(FSampleType A, FSampleType B, FSampleType C, out FSampleType L, out FSampleType M, out FSampleType H)` — Operator that output, lowest, median and highest values from 3 input values.
- L1021-1027 _function_ `CALL_SITE_DEBUGLOC template<typename FSampleType> FSampleType Median(FSampleType A, FSampleType B, FSampleType C)` — 3 samples median.
- L1036-1071 _function_ `CALL_SITE_DEBUGLOC template<typename ScalarType, uint VectorSize, uint LaneStrideX, uint LaneStrideY> TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> Median3x3(TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> Center)`
- L1073-1086 _function_ `CALL_SITE_DEBUGLOC template<uint VectorSize, uint LaneStrideX, uint LaneStrideY> TLaneVector2D<bool, VectorSize, LaneStrideX, LaneStrideY> MedianBool3x3(TLaneVector2D<bool, VectorSize, LaneStrideX, LaneStrideY> Center)`
- L1091-1109 _function_ `CALL_SITE_DEBUGLOC template<typename ScalarType, uint VectorSize, uint LaneStrideX, uint LaneStrideY> TLaneVector2D<ScalarType, VectorSize, LaneStrideX / 2, LaneStrideY / 2> DownsampleMin2x2( TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> Input)`
- L1111-1129 _function_ `CALL_SITE_DEBUGLOC template<typename ScalarType, uint VectorSize, uint LaneStrideX, uint LaneStrideY> TLaneVector2D<ScalarType, VectorSize, LaneStrideX / 2, LaneStrideY / 2> DownsampleMax2x2( TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> Input)`
- L1131-1149 _function_ `CALL_SITE_DEBUGLOC template<typename ScalarType, uint VectorSize, uint LaneStrideX, uint LaneStrideY> TLaneVector2D<ScalarType, VectorSize, LaneStrideX / 2, LaneStrideY / 2> DownsampleDot2x2( TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> Input, const ScalarType Weights[4])`
- L1151-1158 _function_ `CALL_SITE_DEBUGLOC template<typename ScalarType, uint VectorSize, uint LaneStrideX, uint LaneStrideY> TLaneVector2D<ScalarType, VectorSize, LaneStrideX / 2, LaneStrideY / 2> DownsampleAvg2x2( TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> Input)`

#### Top-level macro invocations (1)

- L9 _macro_call_ `TVECTOR_FUNCTION_1PARAMS(ScalarType, SafeRcp)`

### `Shaders/Private/TemporalSuperResolution/TSRConvolutionNetworkPass.ush` (Private)

- lines: 152; parse: all-branches
- includes: L5 `TSRCommon.ush`, L106 `TSRConvolutionNetwork.ush`

#### Macros (#define, 66)

- L12 `#define GROUP_TILE_SIZE 32` _[#if DIM_WAVE_SIZE == 0 \|\| DEBUG_DIGESTABLE]_
- L14 `#define WAVE_COUNT_X GROUP_TILE_SIZE` _[#if DIM_WAVE_SIZE == 0 \|\| DEBUG_DIGESTABLE]_
- L15 `#define WAVE_COUNT_Y GROUP_TILE_SIZE` _[#if DIM_WAVE_SIZE == 0 \|\| DEBUG_DIGESTABLE]_
- L17 `#define LANE_COUNT_X 1` _[#if DIM_WAVE_SIZE == 0 \|\| DEBUG_DIGESTABLE]_
- L18 `#define LANE_COUNT_Y 1` _[#if DIM_WAVE_SIZE == 0 \|\| DEBUG_DIGESTABLE]_
- L20 `#define LANE_STRIDE_X 1` _[#if DIM_WAVE_SIZE == 0 \|\| DEBUG_DIGESTABLE]_
- L21 `#define LANE_STRIDE_Y 1` _[#if DIM_WAVE_SIZE == 0 \|\| DEBUG_DIGESTABLE]_
- L23 `#define LDS_SIZE (GROUP_TILE_SIZE * GROUP_TILE_SIZE)` _[#if DIM_WAVE_SIZE == 0 \|\| DEBUG_DIGESTABLE]_
- L25 `#define TENSOR_REGISTER_LAYOUT FRegisters_S_OneVector` _[#if DIM_WAVE_SIZE == 0 \|\| DEBUG_DIGESTABLE]_
- L31 `#define GROUP_TILE_SIZE 32` _[#if !(DIM_WAVE_SIZE == 0 \|\| DEBUG_DIGESTABLE) && DIM_WAVE_SIZE == 64 \|\| DIM_WAVE_SIZE == 32 \|\| DIM_WAVE_SIZE == 16]_
- L35 `#define LANE_STRIDE_X 2` _[#if !(DIM_WAVE_SIZE == 0 \|\| DEBUG_DIGESTABLE) && DIM_WAVE_SIZE == 64 \|\| DIM_WAVE_SIZE == 32 \|\| DIM_WAVE_SIZE == 16 && DIM_WAVE_SIZE == 16]_
- L38 `#define LANE_STRIDE_Y 1` _[#if !(DIM_WAVE_SIZE == 0 \|\| DEBUG_DIGESTABLE) && DIM_WAVE_SIZE == 64 \|\| DIM_WAVE_SIZE == 32 \|\| DIM_WAVE_SIZE == 16 && DIM_WAVE_SIZE == 16]_
- L40 `#define LANE_STRIDE_X 1` _[#if !(DIM_WAVE_SIZE == 0 \|\| DEBUG_DIGESTABLE) && DIM_WAVE_SIZE == 64 \|\| DIM_WAVE_SIZE == 32 \|\| DIM_WAVE_SIZE == 16 && !(DIM_WAVE_SIZE == 16)]_
- L42 `#define LANE_STRIDE_Y 4` _[#if !(DIM_WAVE_SIZE == 0 \|\| DEBUG_DIGESTABLE) && DIM_WAVE_SIZE == 64 \|\| DIM_WAVE_SIZE == 32 \|\| DIM_WAVE_SIZE == 16 && !(DIM_WAVE_SIZE == 16) && CONFIG_COMPILE_FP16]_
- L44 `#define LANE_STRIDE_Y 2` _[#if !(DIM_WAVE_SIZE == 0 \|\| DEBUG_DIGESTABLE) && DIM_WAVE_SIZE == 64 \|\| DIM_WAVE_SIZE == 32 \|\| DIM_WAVE_SIZE == 16 && !(DIM_WAVE_SIZE == 16) && !(CONFIG_COMPILE_FP16)]_
- L48 `#define WAVE_COUNT_X 1` _[#if !(DIM_WAVE_SIZE == 0 \|\| DEBUG_DIGESTABLE) && DIM_WAVE_SIZE == 64 \|\| DIM_WAVE_SIZE == 32 \|\| DIM_WAVE_SIZE == 16]_
- L49 `#define WAVE_COUNT_Y (GROUP_TILE_SIZE / LANE_STRIDE_Y)` _[#if !(DIM_WAVE_SIZE == 0 \|\| DEBUG_DIGESTABLE) && DIM_WAVE_SIZE == 64 \|\| DIM_WAVE_SIZE == 32 \|\| DIM_WAVE_SIZE == 16]_
- L51 `#define LANE_COUNT_X (GROUP_TILE_SIZE / LANE_STRIDE_X)` _[#if !(DIM_WAVE_SIZE == 0 \|\| DEBUG_DIGESTABLE) && DIM_WAVE_SIZE == 64 \|\| DIM_WAVE_SIZE == 32 \|\| DIM_WAVE_SIZE == 16]_
- L52 `#define LANE_COUNT_Y 1` _[#if !(DIM_WAVE_SIZE == 0 \|\| DEBUG_DIGESTABLE) && DIM_WAVE_SIZE == 64 \|\| DIM_WAVE_SIZE == 32 \|\| DIM_WAVE_SIZE == 16]_
- L56 `#define LDS_SIZE ((2 * LANE_STRIDE_X) * LANE_COUNT_X * WAVE_COUNT_Y)` _[#if !(DIM_WAVE_SIZE == 0 \|\| DEBUG_DIGESTABLE) && DIM_WAVE_SIZE == 64 \|\| DIM_WAVE_SIZE == 32 \|\| DIM_WAVE_SIZE == 16 && LANE_STRIDE_Y > 1]_
- L58 `#define LDS_SIZE (GROUP_TILE_SIZE * GROUP_TILE_SIZE)` _[#if !(DIM_WAVE_SIZE == 0 \|\| DEBUG_DIGESTABLE) && DIM_WAVE_SIZE == 64 \|\| DIM_WAVE_SIZE == 32 \|\| DIM_WAVE_SIZE == 16 && !(LANE_STRIDE_Y > 1)]_
- L62 `#define TENSOR_REGISTER_LAYOUT PLATFORM_SPECIFIC_TENSOR_REGISTER_LAYOUT` _[#if !(DIM_WAVE_SIZE == 0 \|\| DEBUG_DIGESTABLE) && DIM_WAVE_SIZE == 64 \|\| DIM_WAVE_SIZE == 32 \|\| DIM_WAVE_SIZE == 16 && defined(PLATFORM_SPECIFIC_TENSOR_REGISTER_LAYOUT)]_
- L67 `#define CONFIG_LDS_DESPILL 1` _[#if !(DIM_WAVE_SIZE == 0 \|\| DEBUG_DIGESTABLE) && DIM_WAVE_SIZE == 64 \|\| DIM_WAVE_SIZE == 32 \|\| DIM_WAVE_SIZE == 16 && CONFIG_COMPILE_FP16 && !CONFIG_SCENE_COLOR_ALPHA]_
- L68 `#define CONFIG_CACHE_REFETCH 1` _[#if !(DIM_WAVE_SIZE == 0 \|\| DEBUG_DIGESTABLE) && DIM_WAVE_SIZE == 64 \|\| DIM_WAVE_SIZE == 32 \|\| DIM_WAVE_SIZE == 16 && CONFIG_COMPILE_FP16 && !CONFIG_SCENE_COLOR_ALPHA]_
- L76 `#define LDS_DWORD_COMPONENT_COUNT 2` _[#if CONFIG_COMPILE_FP16]_
- L78 `#define LDS_DWORD_COMPONENT_COUNT 4` _[#if !(CONFIG_COMPILE_FP16)]_
- L82 `#define CONFIG_LDS_DESPILL 0` _[#if !defined(CONFIG_LDS_DESPILL)]_
- L87 `#define CONFIG_CACHE_REFETCH 0` _[#if !defined(CONFIG_CACHE_REFETCH)]_
- L92 `#define LDS_DESPILL_THREAD_COUNT (WAVE_COUNT_X * WAVE_COUNT_Y) * (LANE_COUNT_X * LANE_COUNT_Y)` _[#if CONFIG_LDS_DESPILL]_
- L93 `#define LDS_DESPILL_OFFSET (LANE_STRIDE_X * LANE_STRIDE_Y) * GetVectorDwordSize(tsr_half, 4)` _[#if CONFIG_LDS_DESPILL]_
- L95 `#define LDS_DESPILL_OFFSET_COUNT 2` _[#if CONFIG_LDS_DESPILL]_
- L97 `#define LDS_DESPILL_DWORD_COUNT LDS_DESPILL_THREAD_COUNT * LDS_DESPILL_OFFSET * LDS_DESPILL_OFFSET_COUNT` _[#if CONFIG_LDS_DESPILL]_
- L101 `#define SIMD_SIZE (LANE_STRIDE_X * LANE_STRIDE_Y)`
- L111 `#define tsr_tensor_float TLaneVector2D<float, 1, LANE_STRIDE_X, LANE_STRIDE_Y>`
- L112 `#define tsr_tensor_float2 TLaneVector2D<float, 2, LANE_STRIDE_X, LANE_STRIDE_Y>`
- L113 `#define tsr_tensor_float3 TLaneVector2D<float, 3, LANE_STRIDE_X, LANE_STRIDE_Y>`
- L114 `#define tsr_tensor_float4 TLaneVector2D<float, 4, LANE_STRIDE_X, LANE_STRIDE_Y>`
- L115 `#define tsr_tensor_floatC TLaneVector2D<float, CONFIG_CHANNEL_COUNT, LANE_STRIDE_X, LANE_STRIDE_Y>`
- L116 `#define tsr_tensor_half TLaneVector2D<tsr_half, 1, LANE_STRIDE_X, LANE_STRIDE_Y>`
- L117 `#define tsr_tensor_half2 TLaneVector2D<tsr_half, 2, LANE_STRIDE_X, LANE_STRIDE_Y>`
- L118 `#define tsr_tensor_half3 TLaneVector2D<tsr_half, 3, LANE_STRIDE_X, LANE_STRIDE_Y>`
- L119 `#define tsr_tensor_half4 TLaneVector2D<tsr_half, 4, LANE_STRIDE_X, LANE_STRIDE_Y>`
- L120 `#define tsr_tensor_halfC TLaneVector2D<tsr_half, CONFIG_CHANNEL_COUNT, LANE_STRIDE_X, LANE_STRIDE_Y>`
- L122 `#define tsr_tensor_uint TLaneVector2D<uint, 1, LANE_STRIDE_X, LANE_STRIDE_Y>`
- L123 `#define tsr_tensor_uint2 TLaneVector2D<uint, 2, LANE_STRIDE_X, LANE_STRIDE_Y>`
- L124 `#define tsr_tensor_uint3 TLaneVector2D<uint, 3, LANE_STRIDE_X, LANE_STRIDE_Y>`
- L125 `#define tsr_tensor_uint4 TLaneVector2D<uint, 4, LANE_STRIDE_X, LANE_STRIDE_Y>`
- L126 `#define tsr_tensor_int TLaneVector2D<int, 1, LANE_STRIDE_X, LANE_STRIDE_Y>`
- L127 `#define tsr_tensor_int2 TLaneVector2D<int, 2, LANE_STRIDE_X, LANE_STRIDE_Y>`
- L128 `#define tsr_tensor_int3 TLaneVector2D<int, 3, LANE_STRIDE_X, LANE_STRIDE_Y>`
- L129 `#define tsr_tensor_int4 TLaneVector2D<int, 4, LANE_STRIDE_X, LANE_STRIDE_Y>`
- L130 `#define tsr_tensor_ushort TLaneVector2D<tsr_ushort, 1, LANE_STRIDE_X, LANE_STRIDE_Y>`
- L131 `#define tsr_tensor_ushort2 TLaneVector2D<tsr_ushort, 2, LANE_STRIDE_X, LANE_STRIDE_Y>`
- L132 `#define tsr_tensor_ushort3 TLaneVector2D<tsr_ushort, 3, LANE_STRIDE_X, LANE_STRIDE_Y>`
- L133 `#define tsr_tensor_ushort4 TLaneVector2D<tsr_ushort, 4, LANE_STRIDE_X, LANE_STRIDE_Y>`
- L134 `#define tsr_tensor_short TLaneVector2D<tsr_short, 1, LANE_STRIDE_X, LANE_STRIDE_Y>`
- L135 `#define tsr_tensor_short2 TLaneVector2D<tsr_short, 2, LANE_STRIDE_X, LANE_STRIDE_Y>`
- L136 `#define tsr_tensor_short3 TLaneVector2D<tsr_short, 3, LANE_STRIDE_X, LANE_STRIDE_Y>`
- L137 `#define tsr_tensor_short4 TLaneVector2D<tsr_short, 4, LANE_STRIDE_X, LANE_STRIDE_Y>`
- L139 `#define tsr_tensor_bool TLaneVector2D<bool, 1, LANE_STRIDE_X, LANE_STRIDE_Y>`
- L140 `#define tsr_tensor_bool2 TLaneVector2D<bool, 2, LANE_STRIDE_X, LANE_STRIDE_Y>`
- L141 `#define tsr_tensor_bool3 TLaneVector2D<bool, 3, LANE_STRIDE_X, LANE_STRIDE_Y>`
- L142 `#define tsr_tensor_bool4 TLaneVector2D<bool, 4, LANE_STRIDE_X, LANE_STRIDE_Y>`
- L143 `#define tsr_tensor_boolC TLaneVector2D<bool, CONFIG_CHANNEL_COUNT, LANE_STRIDE_X, LANE_STRIDE_Y>`
- L147 `#define PLATFORM_SPECIFIC_ISOLATE ` _[#if !defined(PLATFORM_SPECIFIC_ISOLATE) && UE_BINDLESS_ENABLED]_
- L149 `#define PLATFORM_SPECIFIC_ISOLATE ISOLATE` _[#if !defined(PLATFORM_SPECIFIC_ISOLATE) && !(UE_BINDLESS_ENABLED)]_
- L3 #pragma `once`

### `Shaders/Private/TemporalSuperResolution/TSRDecimateHistory.usf` (Private)

- lines: 544; parse: all-branches
- includes: L3 `TSRDepthVelocityAnalysis.ush`, L4 `TSRClosestOccluder.ush`, L5 `TSRColorSpace.ush`, L6 `TSRReprojectionField.ush`

#### Macros (#define, 7)

- L11 `#define TILE_SIZE 8`
- L13 `#define CONFIG_KERNEL 0`
- L15 `#define CONFIG_MANUAL_LDS_SPILL 1`
- L18 `#define CONFIG_MOIRE_REPROJECTION (DIM_MOIRE_REPROJECTION)`
- L21 `#define CONFIG_RESURRECTION_REPROJECTION (DIM_RESURRECTION_REPROJECTION)`
- L24 `#define CONFIG_THIN_GEOMETRY_COVERAGE_REPROJECTION (DIM_THIN_GEOMETRY_COVERAGE_REPROJECTION)`
- L74 `#define DEBUG_ARRAY_SIZE 8`

#### Entry points (1)

- L256-543 _entry_ `[numthreads(TILE_SIZE * TILE_SIZE, 1, 1)] void DecimateHistoryCS( uint2 GroupId : SV_GroupID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FTSRDecimateHistoryCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/TemporalSuperResolution.cpp:1512)

#### Global resources (textures / buffers / samplers) (14)

- L30 _resource_ `Texture2D<uint> DilatedReprojectionVectorTexture;`
- L32 _resource_ `Texture2D<float2> ClosestDepthTexture;` _[#if CONFIG_RESURRECTION_REPROJECTION]_
- L34 _resource_ `Texture2D<float> ClosestDepthTexture;` _[#if !(CONFIG_RESURRECTION_REPROJECTION)]_
- L36 _resource_ `Texture2D<uint> DilateMaskTexture;`
- L37 _resource_ `Texture2D<uint> DepthErrorTexture;`
- L38 _resource_ `Texture2DArray<uint> PrevAtomicTextureArray;`
- L40 _resource_ `Texture2DArray<tsr_half4> PrevHistoryGuide;`
- L41 _resource_ `Texture2DArray<tsr_half4> PrevHistoryMoire;`
- L43 _resource_ `Texture2DArray<tsr_half> PrevHistoryCoverage;` _[#if CONFIG_THIN_GEOMETRY_COVERAGE_REPROJECTION]_
- L63 _resource_ `RWTexture2DArray<tsr_half4> ReprojectedHistoryGuideOutput;`
- L64 _resource_ `RWTexture2DArray<tsr_half4> ReprojectedHistoryMoireOutput;`
- L66 _resource_ `RWTexture2DArray<tsr_half> ReprojectedHistoryCoverageOutput;` _[#if CONFIG_THIN_GEOMETRY_COVERAGE_REPROJECTION]_
- L68 _resource_ `RWTexture2DArray<uint> ReprojectionFieldOutput;`
- L69 _resource_ `RWTexture2D<tsr_half2> DecimateMaskOutput;`

#### Global parameters (uniforms) (18)

- L28 _parameter_ `float4x4 RotationalClipToPrevClip;`
- L45 _parameter_ `float2 PrevGuideInfo_Extent;`
- L46 _parameter_ `float2 PrevGuideInfo_ExtentInverse;`
- L47 _parameter_ `uint2 PrevGuideInfo_ViewportMin;`
- L48 _parameter_ `uint2 PrevGuideInfo_ViewportMax;`
- L49 _parameter_ `float2 PrevGuideInfo_ViewportSize;`
- L50 _parameter_ `float2 PrevGuideInfo_ViewportSizeInverse;`
- L51 _parameter_ `float2 PrevGuideInfo_UVViewportBilinearMin;`
- L52 _parameter_ `float2 PrevGuideInfo_UVViewportBilinearMax;`
- L53 _parameter_ `FScreenTransform InputPixelPosToReprojectScreenPos;`
- L54 _parameter_ `FScreenTransform ScreenPosToPrevHistoryGuideBufferUV;`
- L55 _parameter_ `FScreenTransform ScreenPosToResurrectionGuideBufferUV;`
- L56 _parameter_ `float2 ResurrectionGuideUVViewportBilinearMin;`
- L57 _parameter_ `float2 ResurrectionGuideUVViewportBilinearMax;`
- L58 _parameter_ `float3 HistoryGuideQuantizationError;`
- L59 _parameter_ `float ResurrectionFrameIndex;`
- L60 _parameter_ `float PrevFrameIndex;`
- L61 _parameter_ `float4x4 ClipToResurrectionClip;`

#### groupshared (2)

- L82 _groupshared_ `groupshared uint SharedArray0[TILE_SIZE * TILE_SIZE];` _[#if CONFIG_MANUAL_LDS_SPILL]_
- L83 _groupshared_ `groupshared float SharedArray1[TILE_SIZE * TILE_SIZE];` _[#if CONFIG_MANUAL_LDS_SPILL]_

#### static variables (1)

- L76 _static_var_ `static float4 Debug[DEBUG_ARRAY_SIZE];`

#### Functions (5)

- L90-98 _function_ `tsr_halfC CorrectGuideColorExposure(tsr_halfC ReprojectedHistoryGuideColor, const float PreExposureCorrection)` — Correct pre exposure of the guide color.
- L102-108 _function_ `tsr_half4 ReprojectPrevHistoryMoire(tsr_ushort2 InputPixelPos, float2 TextureUV)` — Sample previous moire history _[#if CONFIG_MOIRE_REPROJECTION]_
- L111-121 _function_ `tsr_half4 CorrectMoireExposure(tsr_half4 ReprojectedHistoryMoireColor, const float PreExposureCorrection)` — Correct pre exposure of the moire history. _[#if CONFIG_MOIRE_REPROJECTION]_
- L125-128 _function_ `tsr_half ReprojectPrevHistoryCoverage(tsr_ushort2 InputPixelPos, float2 TextureUV)` _[#if CONFIG_THIN_GEOMETRY_COVERAGE_REPROJECTION]_
- L132-252 _function_ `void ReprojectAllPrevTextures( uint2 GroupId, uint GroupThreadIndex, uint EncodedReprojectionVector, float DeviceZ, out uint HistoryClosestDeviceZSamples0[4], out uint HistoryClosestDeviceZSamples1[4], out FCatmullRomFetches<tsr_half4> ReprojectedHistoryGuideSamples, out FCatmullRomFetches<tsr_half4> ReprojectedHistoryGuideUncertaintySamples, out tsr_half4 ReprojectedHistoryMoireColor, out tsr_half ReprojectedHistoryCoverage, out tsr_halfC ResurrectedHistoryGuideColor, out tsr_half ResurrectedHistoryGuideUncertainty, out bool bIsResurrectionOffScreen, out bool bIsOffScreen)` — ISOLATE

### `Shaders/Private/TemporalSuperResolution/TSRDepthVelocityAnalysis.ush` (Private)

- lines: 608; parse: all-branches
- includes: L5 `TSRKernels.ush`, L6 `TSRReprojectionField.ush`

#### Macros (#define, 5)

- L12 `#define CONFIG_USE_SCENE_VELOCITY 1`
- L15 `#define CONFIG_DEPTH_EDGE_DETECTION 1`
- L20 `#define MAX_DEVICE_Z_ERROR 64.0`
- L22 `#define CONFIG_VELOCITY_SAMPLES 9`
- L23 `#define CONFIG_VELOCITY_SAMPLE_PAIRS ((CONFIG_VELOCITY_SAMPLES - 1) / 2)`
- L3 #pragma `once`

#### Functions (19)

- L28-37 _function_ `CALL_SITE_DEBUGLOC float3 ComputeStaticVelocity(float2 ScreenPos, float DeviceZ)`
- L40-47 _function_ `CALL_SITE_DEBUGLOC float ComputePixelDeviceZError(float DeviceZ)` — Compute the devize Z error due to the size of a pixel in world space at that given depth.
- L50-58 _function_ `CALL_SITE_DEBUGLOC uint EncodeDeviceZError(float PrevClosestDeviceZ, float ParallaxDepthError)` — Encode the devize Z error relatively to the closest depth to squeeze to 8bit per pixel
- L61-68 _function_ `CALL_SITE_DEBUGLOC float DecodeDeviceZError(float PrevClosestDeviceZ, uint EncodedDeviceZError)` — Inverse of EncodeDeviceZError()
- L74-87 _function_ `CALL_SITE_DEBUGLOC void FetchDepth3x3( Texture2D<float> SceneDepthTexture, tsr_short2 InputPixelPos, out float DevizeZNeighborhood[CONFIG_BUTTERFLY_SAMPLES])` — Loads all the 3x3's depth.
- L90-106 _function_ `CALL_SITE_DEBUGLOC void FetchDepthVelocity3x3( Texture2D<float> SceneDepthTexture, Texture2D<float4> SceneVelocityTexture, tsr_short2 InputPixelPos, out float DevizeZNeighborhood[CONFIG_BUTTERFLY_SAMPLES], out float4 VelocityNeighborhood[CONFIG_BUTTERFLY_SAMPLES])` — Loads all the 3x3's depth and velocities.
- L108-144 _function_ `CALL_SITE_DEBUGLOC void FetchAndComputeScreenVelocity( Texture2D<float4> SceneVelocityTexture, tsr_short2 InputPixelPos, float ClosestDeviceZ, tsr_short2 ReprojectionOffset, out float3 ScreenVelocity, out bool bHasPixelAnimation, out bool bDisableAnimationAA)`
- L147-227 _function_ `void ComputePixelVelocityNeighborhood( tsr_short2 InputPixelPos, float DevizeZNeighborhood[CONFIG_BUTTERFLY_SAMPLES], float4 VelocityNeighborhood[CONFIG_BUTTERFLY_SAMPLES], out float2 PixelVelocityNeighborhood[CONFIG_BUTTERFLY_SAMPLES], out float DepthVelocityNeighborhood[CONFIG_BUTTERFLY_SAMPLES], out bool bIsDrawingVelocityNeighborhood[CONFIG_BUTTERFLY_SAMPLES])` — Convert the fetches velocities to pixel velocities.
- L232-246 _function_ `CALL_SITE_DEBUGLOC void FetchReprojectionNeighborhood( Texture2D<uint> ReprojectionVectorTexture, tsr_short2 InputPixelPos, out uint EncodedReprojectionVectorNeighborhood[CONFIG_BUTTERFLY_SAMPLES])`
- L248-258 _function_ `CALL_SITE_DEBUGLOC void ComputePixelVelocityNeighborhood( uint EncodedReprojectionVectorNeighborhood[CONFIG_BUTTERFLY_SAMPLES], out float2 PixelVelocityNeighborhood[CONFIG_BUTTERFLY_SAMPLES])`
- L263-267 _function_ `CALL_SITE_DEBUGLOC uint PackDepthAndOffset(const int2 Offset, float DeviceZ)`
- L269-275 _function_ `CALL_SITE_DEBUGLOC void UnpackDepthAndOffset(uint Packed, out tsr_short2 Offset, out float DeviceZ)`
- L278-329 _function_ `void FindClosestDepthOffset( float DevizeZNeighborhood[CONFIG_BUTTERFLY_SAMPLES], out float ClosestDeviceZ, out tsr_short2 ReprojectionOffset)` — Find the closest DevizeZ and its corresponding offset
- L332-415 _function_ `bool ComputeDepthBilaterals( const int2 DirectionE, const int2 DirectionS, bool bCompute, float DevizeZNeighborhood[CONFIG_BUTTERFLY_SAMPLES], inout float DepthError, out tsr_half BilateralWeights[4])` — Compute the velocity jacobian along a two orthogonal axes, taking a common closest depth.
- L418-431 _function_ `float ComputeDepthError(float DevizeZNeighborhood[CONFIG_BUTTERFLY_SAMPLES])` — Compute the depth error on horizontal and vertical.
- L437-469 _function_ `CALL_SITE_DEBUGLOC void ComputeVelocityJacobian( const int2 DirectionE, const int2 DirectionS, bool bCompute, float2 PixelVelocityNeighborhood[CONFIG_BUTTERFLY_SAMPLES], tsr_half BilateralWeights[4], inout tsr_half2x2 ReprojectionJacobian)` — Computes the velocity's jacobian from the depth bilateral weighs.
- L472-546 _function_ `void ComputeReprojectionJacobian( float DevizeZNeighborhood[CONFIG_BUTTERFLY_SAMPLES], float2 PixelVelocityNeighborhood[CONFIG_BUTTERFLY_SAMPLES], out tsr_half2x2 ReprojectionJacobian, out float DepthError)` — Find the closest DevizeZ and its corresponding offset
- L549-557 _function_ `CALL_SITE_DEBUGLOC tsr_half ComputeReprojectionEdge( float2 ScreenVelocity, float2 DilatedScreenVelocity)` — Compute the reprojection edge from non-dilated to dilated screen velocity.
- L560-607 _function_ `tsr_half ComputeReprojectionEdge( float2 PixelVelocityNeighborhood[CONFIG_BUTTERFLY_SAMPLES])` — Compute the reprojection edge from the pixel velocity neighborhood.

### `Shaders/Private/TemporalSuperResolution/TSRDetectThinGeometry.usf` (Private)

- lines: 646; parse: all-branches
- includes: L7 `TSRColorSpace.ush`, L8 `TSRDepthVelocityAnalysis.ush`, L9 `TSRConvolutionNetworkPass.ush`, L10 `TSRReprojectionField.ush`, L11 `TSRThinGeometryCommon.ush`

#### Macros (#define, 11)

- L3 `#define CONFIG_INTENSITY_LINE_DETECTION (DIM_INTENSITY_LINE_DETECTION)`
- L4 `#define CONFIG_TRANSLUCENCY_COVERAGE_BIT (DIM_REJECT_TRANSLUCENCY_DETECTION)`
- L14 `#define DEBUG_ARRAY_SIZE 8`
- L16 `#define DEBUG_DISABLE_PADDING 0`
- L18 `#define DEBUG_DIGESTABLE 0`
- L20 `#define EDGE_HORIZONTAL_VERTICAL 1`
- L21 `#define EDGE_HORIZONTAL_VERTICAL_DIAGNAL 2`
- L23 `#define EDGE_TYPE EDGE_HORIZONTAL_VERTICAL_DIAGNAL`
- L25 `#define CONFIG_VARYING_RANGE_DETECTION (DIM_VARYING_RANGE_DETECTION)`
- L28 `#define TLineEdgeType tsr_tensor_half2` _[#if CONFIG_INTENSITY_LINE_DETECTION]_
- L30 `#define TLineEdgeType tsr_tensor_half` _[#if !(CONFIG_INTENSITY_LINE_DETECTION)]_

#### Entry points (1)

- L325-645 _entry_ `[numthreads(LANE_COUNT * WAVE_COUNT, 1, 1)] void DetectThinGeometryCS( uint2 GroupId : SV_GroupID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FTSRDetectThinGeometryCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/TemporalSuperResolution.cpp:1510)

#### Global resources (textures / buffers / samplers) (7)

- L50 _resource_ `Texture2D<float> SceneDepthTexture;`
- L51 _resource_ `Texture2D<tsr_half> CurrentCoverageTexture;`
- L53 _resource_ `Texture2D<tsr_half> FlickeringLumaTexture;` _[#if CONFIG_INTENSITY_LINE_DETECTION]_
- L55 _resource_ `Texture2D<tsr_half> ReprojectedHistoryCoverageTexture;`
- L56 _resource_ `Texture2D<tsr_half2> DecimateMaskTexture;`
- L58 _resource_ `RWTexture2DArray<tsr_half> HistoryCoverageOutput;`
- L59 _resource_ `RWTexture2DArray<tsr_ushort> R8Output;`

#### Global parameters (uniforms) (8)

- L41 _parameter_ `int TileOverscan;`
- L42 _parameter_ `int ThinGeometryTextureIndex;`
- L43 _parameter_ `float ErrorMultiplier;`
- L44 _parameter_ `float MaxRelaxationWeight;`
- L45 _parameter_ `float MinKeepLineContrast;`
- L46 _parameter_ `float HighContrastLineFadeRate;`
- L47 _parameter_ `float HighContrastLineFadeRateInsideRegion;`
- L48 _parameter_ `float HighContrastLineWeight;`

#### static const (2)

- L35 _static_const_ `static const uint kDespillInput = LDS_DESPILL_THREAD_COUNT * LDS_DESPILL_OFFSET * 0;` _[#if CONFIG_LDS_DESPILL]_
- L36 _static_const_ `static const uint kDespillHistory = LDS_DESPILL_THREAD_COUNT * LDS_DESPILL_OFFSET * 1;` _[#if CONFIG_LDS_DESPILL]_

#### static variables (2)

- L62 _static_var_ `static uint2 GGroupId = 0;`
- L66 _static_var_ `static tsr_tensor_half4 Debug[DEBUG_ARRAY_SIZE];`

#### Functions (8)

- L70-82 _function_ `tsr_short2 ComputeElementPixelPos(const uint ElementIndex)`
- L84-95 _function_ `tsr_tensor_short2 ComputePixelPos()`
- L97-107 _function_ `tsr_short2 ComputeElementOutputPixelPos(const uint ElementIndex)`
- L109-149 _function_ `void FetchCommonInput( tsr_tensor_short2 PixelPos ,out tsr_tensor_half CurrentCoverage ,out tsr_tensor_bool bHasPixelAnimation ,out tsr_tensor_ushort MaterialMask )`
- L151-210 _function_ `void FetchRegularPassInput( tsr_tensor_short2 PixelPos ,out tsr_tensor_half SceneDepth ,out tsr_tensor_half DeviceZThinGeometryDetectionError ,out tsr_tensor_half ReprojectedHistoryCoverage ,out tsr_tensor_half PrevHighIntensity ,out tsr_tensor_half FlickeringLuma ,out tsr_tensor_half HadTranslucency )`
- L220-259 _function_ `CALL_SITE_DEBUGLOC template< typename ScalarType, uint VectorSize, uint LaneStrideX, uint LaneStrideY> TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> HorizontalThinEdge3x3( TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> Center, TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> EdgeThreshold)`
- L266-302 _function_ `CALL_SITE_DEBUGLOC template< typename ScalarType, uint VectorSize, uint LaneStrideX, uint LaneStrideY> TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> VerticalThinEdge3x3( TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> Center, TLaneVector2D<ScalarType, VectorSize, LaneStrideX, LaneStrideY> EdgeThreshold)`
- L304-318 _function_ `tsr_tensor_ushort EncodeThinGeometryWeight(tsr_tensor_half ThinGeometryEdge , tsr_tensor_bool IsClusterHoleRegion, tsr_tensor_half Weight )`

#### Top-level macro invocations (1)

- L323 _macro_call_ `WAVESIZE(DIM_WAVE_SIZE)` _[#if COMPILER_SUPPORTS_WAVE_SIZE && DIM_WAVE_SIZE > 0]_

### `Shaders/Private/TemporalSuperResolution/TSRDilateVelocity.usf` (Private)

- lines: 433; parse: all-branches
- includes: L3 `TSRDepthVelocityAnalysis.ush`, L4 `TSRSpatialAntiAliasing.ush`, L5 `TSRReprojectionField.ush`, L6 `TSRClosestOccluder.ush`, L10 `../MotionBlur/MotionBlurVelocityFlatten.ush` [DIM_MOTION_BLUR_DIRECTIONS > 0]

#### Macros (#define, 5)

- L9 `#define CONFIG_MAX_RANGE_SIZE (DIM_MOTION_BLUR_DIRECTIONS)` _[#if DIM_MOTION_BLUR_DIRECTIONS > 0]_
- L17 `#define TILE_SIZE (VELOCITY_FLATTEN_TILE_SIZE)` _[#if DIM_MOTION_BLUR_DIRECTIONS > 0]_
- L19 `#define TILE_SIZE 8` _[#if !(DIM_MOTION_BLUR_DIRECTIONS > 0)]_
- L22 `#define CONFIG_THIN_GEOMETRY_EDGE_REPROJECTION (DIM_THIN_GEOMETRY_EDGE_REPROJECTION)`
- L50 `#define DEBUG_ARRAY_SIZE 8`

#### Entry points (1)

- L148-432 _entry_ `[numthreads(TILE_SIZE * TILE_SIZE, 1, 1)] void DilateVelocityCS( uint2 GroupId : SV_GroupID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FTSRDilateVelocityCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/TemporalSuperResolution.cpp:1509)

#### Global resources (textures / buffers / samplers) (8)

- L36 _resource_ `Texture2D<float> SceneDepthTexture;`
- L37 _resource_ `Texture2D<float4> SceneVelocityTexture;`
- L39 _resource_ `RWTexture2D<float2> ClosestDepthOutput;`
- L40 _resource_ `globallycoherent RWTexture2DArray<uint> PrevAtomicOutput;`
- L41 _resource_ `RWTexture2DArray<uint> ReprojectionFieldOutput;`
- L42 _resource_ `RWTexture2DArray<uint> R8Output;`
- L44 _resource_ `RWTexture2D<float3> VelocityFlattenOutput;`
- L45 _resource_ `RWTexture2DArray<float4> VelocityTileArrayOutput;`

#### Global parameters (uniforms) (7)

- L26 _parameter_ `float4x4 RotationalClipToPrevClip;`
- L27 _parameter_ `float InvFlickeringMaxParralaxVelocity;`
- L28 _parameter_ `float ReprojectionFieldAntiAliasVelocityThreshold;`
- L29 _parameter_ `uint bReprojectionField;`
- L30 _parameter_ `uint bOutputIsMovingTexture;`
- L31 _parameter_ `uint ReprojectionVectorOutputIndex;`
- L33 _parameter_ `uint ThinGeometryTextureIndex;` _[#if CONFIG_THIN_GEOMETRY_EDGE_REPROJECTION]_

#### static variables (1)

- L52 _static_var_ `static float4 Debug[DEBUG_ARRAY_SIZE];`

#### Functions (1)

- L58-143 _function_ `tsr_half2 ComputeReprojectionBoundary( tsr_short2 InputPixelPos, tsr_short2 ReprojectionOffset, float2 ScreenVelocity, float2 DilatedScreenVelocity, float DevizeZNeighborhood[CONFIG_BUTTERFLY_SAMPLES])` — Spatial anti-alias the depth buffer and return the boundary.

### `Shaders/Private/TemporalSuperResolution/TSRKernels.ush` (Private)

- lines: 456; parse: first-branch (retry, +0 merged from all-branches pass)
- includes: L5 `TSRCommon.ush`

#### Macros (#define, 4)

- L90 `#define CONFIG_BUTTERFLY_KERNEL 1` _[#if PLATFORM_SUPPORTS_WAVE_BROADCAST && 1]_
- L91 `#define CONFIG_BUTTERFLY_SAMPLES 4` _[#if PLATFORM_SUPPORTS_WAVE_BROADCAST && 1]_
- L93 `#define CONFIG_BUTTERFLY_KERNEL 0` _[#if !(PLATFORM_SUPPORTS_WAVE_BROADCAST && 1)]_
- L94 `#define CONFIG_BUTTERFLY_SAMPLES 9` _[#if !(PLATFORM_SUPPORTS_WAVE_BROADCAST && 1)]_
- L3 #pragma `once`

#### Structs / classes (1)

- L397-431 _struct_ **`FCatmullRomFetches`** `template<typename Type> struct FCatmullRomFetches`
  - L400 _member_ `Type Colors[BICUBIC_CATMULL_ROM_SAMPLES];`
  - L401 _member_ `tsr_half Weights[BICUBIC_CATMULL_ROM_SAMPLES];`
  - L403 _method_ `void FetchSamples(Texture2DArray<Type> InTexture, float2 UV, float SliceIndex, float2 Size, float2 InvSize, float2 MinUV, float2 MaxUV)`
  - L421 _method_ `Type AccumulateSamples()`

#### static const (14)

- L29-40 _static_const_ `static const int2 kOffsets3x3[9] = { int2(-1, -1), int2(0, -1), int2(1, -1), int2(-1, 0), int2(0, 0), int2(1, 0), int2(-1, 1), int2(0, 1), int2(1, 1), };` — K = Center of the nearest input pixel. O = Center of the output pixel. \|           \| 0     \|     1     \|     2 \|           \| \|           \| \|           \| \| O         \| 3     \|     K     \|     5 \|           \| \|           \| \|           \| \|           \| 6     \|     7     \|     8 \|           \|
- L54-60 _static_const_ `static const int2 Offsets2x2[4] = { int2( 0, 0), int2( 1, 0), int2( 0, 1), int2( 1, 1), };` — T = Center of the nearest top left pixel input pixel. O = Center of the output pixel. \| T     \|     . \| O  \| \| \| .     \|     . \|
- L63 _static_const_ `static const uint kSquareIndexes3x3[9] = { 4, 0, 1, 2, 3, 8, 7, 6, 5 };` — Indexes of the 3x3 square.
- L66 _static_const_ `static const uint kPlusIndexes3x3[5] = { 4, 1, 3, 7, 5 };` — Indexes of the offsets to have plus + shape.
- L69 _static_const_ `static const int2 kOffsetC = int2( 0, 0);` — Cardinal pixel directions;
- L70 _static_const_ `static const int2 kOffsetN = int2( 0, -1);`
- L71 _static_const_ `static const int2 kOffsetS = int2( 0, +1);`
- L72 _static_const_ `static const int2 kOffsetE = int2(+1, 0);`
- L73 _static_const_ `static const int2 kOffsetW = int2(-1, 0);`
- L74 _static_const_ `static const int2 kOffsetNE = int2(+1, -1);`
- L75 _static_const_ `static const int2 kOffsetNW = int2(-1, -1);`
- L76 _static_const_ `static const int2 kOffsetSE = int2(+1, +1);`
- L77 _static_const_ `static const int2 kOffsetSW = int2(-1, +1);`
- L79-84 _static_const_ `static const int2 kPairOffsets[4] = { int2( 1, 0), int2( 1, 1), int2( 0, 1), int2(-1, 1), };`

#### Functions (14)

- L101-134 _function_ `CALL_SITE_DEBUGLOC tsr_short2x2 ClampPixelOffset( tsr_short2x2 KernelCenterPixelPos, tsr_short2x2 Offset, const tsr_short2 OffsetDirection, int2 MinPixelPos, int2 MaxPixelPos)` — Clamp the offset to be shared across multiple samples
- L136-161 _function_ `CALL_SITE_DEBUGLOC tsr_short2 ClampPixelOffset( tsr_short2 KernelCenterPixelPos, tsr_short2 Offset, const tsr_short2 OffsetDirection, int2 MinPixelPos, int2 MaxPixelPos)`
- L163-171 _function_ `CALL_SITE_DEBUGLOC tsr_short2x2 ClampPixelOffset( tsr_short2x2 SamplePixelPos, int2 MinPixelPos, int2 MaxPixelPos)`
- L173-179 _function_ `CALL_SITE_DEBUGLOC tsr_short2 ClampPixelOffset( tsr_short2 SamplePixelPos, int2 MinPixelPos, int2 MaxPixelPos)`
- L181-216 _function_ `CALL_SITE_DEBUGLOC tsr_short2x2 AddAndClampPixelOffset( tsr_short2x2 KernelCenterPixelPos, tsr_short2x2 Offset, const tsr_short2 OffsetDirection, int2 MinPixelPos, int2 MaxPixelPos)`
- L218-240 _function_ `CALL_SITE_DEBUGLOC tsr_short2 AddAndClampPixelOffset( tsr_short2 KernelCenterPixelPos, tsr_short2 Offset, const tsr_short2 OffsetDirection, int2 MinPixelPos, int2 MaxPixelPos)`
- L245-252 _function_ `CALL_SITE_DEBUGLOC tsr_short2 GetLaneOffsetSign()`
- L259-282 _function_ `CALL_SITE_DEBUGLOC tsr_short2 GetNeighborhoodPixelPos(const uint ArrayIndex, tsr_short2 InputPixelPos)`
- L284-308 _function_ `CALL_SITE_DEBUGLOC template<typename Type> Type AccessNeighborhoodStaticOffset(Type Array[CONFIG_BUTTERFLY_SAMPLES], const int2 Offset)`
- L310-337 _function_ `CALL_SITE_DEBUGLOC template<typename Type> Type AccessNeighborhoodDynamicOffset(Type Array[CONFIG_BUTTERFLY_SAMPLES], const tsr_short2 Offset)`
- L339-345 _function_ `CALL_SITE_DEBUGLOC template<typename Type> Type AccessNeighborhoodCenter(Type Array[CONFIG_BUTTERFLY_SAMPLES])`
- L355-395 _function_ `FCatmullRomSamples GetBicubic2DCatmullRomSamples_Stubbe(float2 UV, float2 Size, in float2 InvSize)`
- L437-446 _function_ `CALL_SITE_DEBUGLOC tsr_half2 ComputeSampleWeigth(tsr_half2 UpscaleFactor, tsr_half2x2 PixelDelta, const float MinimalContribution)` — Returns the weight of a pixels at a coordinate <PixelDelta> from the PDF highest point.
- L448-455 _function_ `CALL_SITE_DEBUGLOC tsr_half ComputeSampleWeigth(tsr_half UpscaleFactor, tsr_half2 PixelDelta, const float MinimalContribution)`

### `Shaders/Private/TemporalSuperResolution/TSRMeasureCoverage.usf` (Private)

- lines: 85; parse: all-branches
- includes: L4 `../DeferredShadingCommon.ush`, L5 `TSRColorSpace.ush`, L6 `TSRThinGeometryCommon.ush`

#### Macros (#define, 6)

- L9 `#define TILE_SIZE 8`
- L11 `#define TILE_ROWS 2`
- L13 `#define THIN_GEOMETRY_SHADING_RANGE_FOLIAGE 0`
- L14 `#define THIN_GEOMETRY_SHADING_RANGE_FOLIAGE_HAIR 1`
- L15 `#define THIN_GEOMETRY_SHADING_RANGE_ALL 2`
- L17 `#define CONFIG_THIN_GEOMETRY_SHADING_RANGE (DIM_THIN_GEOMETRY_SHADING_RANGE)`

#### Entry points (1)

- L41-84 _entry_ `[numthreads(TILE_SIZE * TILE_SIZE, 1, 1)] void MeasureCoverageCS( uint2 GroupId : SV_GroupID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FTSRMeasureThinGeometryCoverageCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/TemporalSuperResolution.cpp:1507)

#### Global resources (textures / buffers / samplers) (1)

- L23 _resource_ `RWTexture2DArray<float> ThinGeometryCoverageOutput;`

#### Global parameters (uniforms) (1)

- L22 _parameter_ `int OutputArrayIndex;`

#### Functions (1)

- L25-37 _function_ `uint GetThinGeometry(const FGBufferData GBufferData)`

### `Shaders/Private/TemporalSuperResolution/TSRMeasureFlickeringLuma.usf` (Private)

- lines: 70; parse: all-branches
- includes: L3 `TSRColorSpace.ush`

#### Macros (#define, 2)

- L8 `#define TILE_SIZE 8`
- L10 `#define TILE_ROWS 2`

#### Entry points (1)

- L21-69 _entry_ `[numthreads(TILE_SIZE * TILE_SIZE, 1, 1)] void MeasureFlickeringLumaCS( uint2 GroupId : SV_GroupID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FTSRMeasureFlickeringLumaCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/TemporalSuperResolution.cpp:1506)

#### Global resources (textures / buffers / samplers) (2)

- L15 _resource_ `Texture2D<tsr_half3> SceneColorTexture;`
- L16 _resource_ `RWTexture2DArray<tsr_half> FlickeringLumaOutput;`

#### Global parameters (uniforms) (1)

- L14 _parameter_ `float ExposureOffsetFactor;`

### `Shaders/Private/TemporalSuperResolution/TSRRejectShading.usf` (Private)

- lines: 954; parse: first-branch (retry, +0 merged from all-branches pass)
- includes: L7 `TSRShadingAnalysis.ush`, L8 `TSRReprojectionField.ush`

#### Macros (#define, 6)

- L5 `#define CONFIG_THIN_GEOMETRY_DETECTION (DIM_THIN_GEOMETRY_DETECTION)`
- L13 `#define DEBUG_ARRAY_SIZE 8`
- L15 `#define DEBUG_DISABLE_PADDING 0`
- L17 `#define DEBUG_DIGESTABLE 0`
- L20 `#define CONFIG_MOIRE_DETECTION (DIM_FLICKERING_DETECTION)`
- L22 `#define CONFIG_HISTORY_RESURRECTION (DIM_HISTORY_RESURRECTION)`

#### Entry points (1)

- L451-953 _entry_ `[numthreads(LANE_COUNT * WAVE_COUNT, 1, 1)] void RejectShadingCS( uint2 GroupId : SV_GroupID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FTSRRejectShadingCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/TemporalSuperResolution.cpp:1513)

#### Global resources (textures / buffers / samplers) (19)

- L51 _resource_ `Texture2D<tsr_halfC_resource> InputTexture;`
- L52 _resource_ `Texture2D<tsr_half_resource> InputMoireLumaTexture;`
- L53 _resource_ `Texture2D<tsr_half4_resource> InputSceneTranslucencyTexture;`
- L54 _resource_ `Texture2D<tsr_half4_resource> ReprojectedHistoryGuideTexture;`
- L55 _resource_ `Texture2D<tsr_half_resource> ReprojectedHistoryGuideMetadataTexture;`
- L56 _resource_ `Texture2D<tsr_half4_resource> ReprojectedHistoryMoireTexture;`
- L58 _resource_ `Texture2D<tsr_half4_resource> ResurrectedHistoryGuideTexture;` _[#if CONFIG_HISTORY_RESURRECTION]_
- L59 _resource_ `Texture2D<tsr_half_resource> ResurrectedHistoryGuideMetadataTexture;` _[#if CONFIG_HISTORY_RESURRECTION]_
- L61 _resource_ `Texture2D<tsr_half2_resource> DecimateMaskTexture;`
- L62 _resource_ `Texture2D<tsr_ushort_resource> IsMovingMaskTexture;`
- L63 _resource_ `Texture2D<tsr_ushort_resource> ThinGeometryTexture;`
- L64 _resource_ `Texture2D<float2> ClosestDepthTexture;`
- L66 _resource_ `RWTexture2DArray<tsr_half4_resource> HistoryGuideOutput;`
- L67 _resource_ `RWTexture2DArray<tsr_half4_resource> HistoryMoireOutput;`
- L68 _resource_ `RWTexture2D<tsr_half4_resource> HistoryRejectionOutput;`
- L69 _resource_ `RWTexture2DArray<uint> ReprojectionFieldOutput;`
- L70 _resource_ `RWTexture2D<tsr_halfC_resource> InputSceneColorOutput;`
- L71 _resource_ `RWTexture2D<tsr_half_resource> InputSceneColorLdrLumaOutput;`
- L72 _resource_ `RWTexture2D<tsr_ushort_resource> AntiAliasMaskOutput;`

#### Global parameters (uniforms) (14)

- L35 _parameter_ `FScreenTransform InputPixelPosToTranslucencyTextureUV;`
- L36 _parameter_ `float4x4 ClipToResurrectionClip;`
- L37 _parameter_ `float2 ResurrectionJacobianXMul;`
- L38 _parameter_ `float2 ResurrectionJacobianXAdd;`
- L39 _parameter_ `float2 ResurrectionJacobianYMul;`
- L40 _parameter_ `float2 ResurrectionJacobianYAdd;`
- L41 _parameter_ `float2 TranslucencyTextureUVMin;`
- L42 _parameter_ `float2 TranslucencyTextureUVMax;`
- L43 _parameter_ `float3 HistoryGuideQuantizationError;`
- L44 _parameter_ `float3 SceneColorOutputQuantizationError;`
- L45 _parameter_ `float TheoricBlendFactor;`
- L46 _parameter_ `uint TileOverscan;`
- L47 _parameter_ `uint bEnableResurrection;`
- L48 _parameter_ `uint bEnableFlickeringHeuristic;`

#### static const (2)

- L28 _static_const_ `static const uint kDespillInput = LDS_DESPILL_THREAD_COUNT * LDS_DESPILL_OFFSET * 0;` _[#if CONFIG_LDS_DESPILL]_
- L29 _static_const_ `static const uint kDespillHistory = LDS_DESPILL_THREAD_COUNT * LDS_DESPILL_OFFSET * 1;` _[#if CONFIG_LDS_DESPILL]_

#### static variables (2)

- L77 _static_var_ `static uint2 GGroupId = 0;`
- L79 _static_var_ `static tsr_tensor_half4 Debug[DEBUG_ARRAY_SIZE];`

#### Functions (17)

- L84-96 _function_ `tsr_short2 ComputeElementPixelPos(const uint ElementIndex)`
- L98-109 _function_ `tsr_tensor_short2 ComputePixelPos()`
- L111-121 _function_ `tsr_short2 ComputeElementOutputPixelPos(const uint ElementIndex)`
- L123-140 _function_ `void FetchThinGeometryEdge( tsr_tensor_short2 PixelPos, out tsr_tensor_half HistoryRelaxationWeight, out tsr_tensor_bool IsClusterHoleRegion)`
- L142-163 _function_ `void FetchDecimateMask( tsr_tensor_short2 PixelPos, out tsr_tensor_half VelocityEdge, out tsr_tensor_bool bIsDisoccluded, out tsr_tensor_bool bHasPixelAnimation, out tsr_tensor_bool bIsResurrectionOffScreen)`
- L165-181 _function_ `void FetchSceneColorAndTranslucency( tsr_tensor_short2 PixelPos, out tsr_tensor_halfC OriginalOpaqueInput, out tsr_tensor_half4 OriginalTranslucencyInput)`
- L183-208 _function_ `void FetchHistoryGuide( Texture2D<tsr_half4_resource> HistoryGuideTexture, Texture2D<tsr_half_resource> HistoryGuideMetadataTexture, tsr_tensor_short2 PixelPos, out tsr_tensor_halfC History, out tsr_tensor_half HistoryUncertainty)`
- L211-222 _function_ `void FetchReprojectedHistoryGuide( tsr_tensor_short2 PixelPos, out tsr_tensor_halfC History, out tsr_tensor_half HistoryUncertainty)` — Fetch the previous history history.
- L226-241 _function_ `void FetchMoireInput( tsr_tensor_short2 PixelPos, out tsr_tensor_half MoireInput, out tsr_tensor_half4 PrevMoireHistory, out tsr_tensor_half bIsStatic)` _[#if CONFIG_MOIRE_DETECTION]_
- L248-259 _function_ `void FetchResurrectedHistoryGuide( tsr_tensor_short2 PixelPos, out tsr_tensor_halfC History, out tsr_tensor_half HistoryUncertainty)` — Fetch the resurrected history. _[#if CONFIG_HISTORY_RESURRECTION]_
- L262-282 _function_ `CALL_SITE_DEBUGLOC tsr_tensor_bool IsResurrectedFrameCloserThanPreviousFrame(tsr_tensor_bool bIsResurrectionOffScreen, tsr_tensor_halfC ExposedInput, tsr_tensor_halfC ExposedHistory, tsr_tensor_halfC ExposedResurrectedHistory)` — Returns whether resurrected frame is closer than previous frame on per pixel basis. _[#if CONFIG_HISTORY_RESURRECTION]_
- L285-304 _function_ `CALL_SITE_DEBUGLOC bool IsWorthMeasuringRejectionOfResurrectedFrame(tsr_tensor_half PrevRejectionBlendFinal, tsr_tensor_bool bResurrectionIsCloser)` — Whether it is worth for the entire tile to MeasureRejection() on the resurrected frame. _[#if CONFIG_HISTORY_RESURRECTION]_
- L307-315 _function_ `CALL_SITE_DEBUGLOC tsr_tensor_bool ShouldResurrectHistory(tsr_tensor_half PrevRejectionBlendFinal, tsr_tensor_half ResurrectionRejectionBlendFinal, tsr_tensor_bool bResurrectionIsCloser)` — Final logic whether the resurrection must actually happen on per pixel basis. _[#if CONFIG_HISTORY_RESURRECTION]_
- L318-330 _function_ `CALL_SITE_DEBUGLOC void FetchDeviceZ( tsr_tensor_short2 PixelPos, out tsr_tensor_float DeviceZ)` — Load the depth for ComputeResurrectionVelocity() _[#if CONFIG_HISTORY_RESURRECTION]_
- L333-377 _function_ `CALL_SITE_DEBUGLOC void OverwriteReprojectionFieldWithResurrection(tsr_tensor_bool bResurrectHistory, tsr_tensor_float DeviceZ)` — Overwrite the reprojection field for pixels that needs resurrection. _[#if CONFIG_HISTORY_RESURRECTION]_
- L385-397 _function_ `CALL_SITE_DEBUGLOC tsr_tensor_halfC UpdateGuide(tsr_tensor_halfC ExposedInput, tsr_tensor_halfC ExposedHistory, tsr_tensor_bool bIsDisoccluded, tsr_tensor_half RejectionBlendFinal)` — Update the guide for next frame.
- L404-413 _function_ `void RefetchInputAndHistoryFromLDSOrCache( out tsr_tensor_halfC Input, out tsr_tensor_half InputUncertainty, out tsr_tensor_halfC History, out tsr_tensor_half HistoryUncertainty)` _[#if CONFIG_LDS_DESPILL \|\| CONFIG_CACHE_REFETCH]_

#### Top-level macro invocations (1)

- L449 _macro_call_ `WAVESIZE(DIM_WAVE_SIZE)` _[#if COMPILER_SUPPORTS_WAVE_SIZE && DIM_WAVE_SIZE > 0]_

### `Shaders/Private/TemporalSuperResolution/TSRReprojectionField.ush` (Private)

- lines: 167; parse: all-branches
- includes: L5 `TSRCommon.ush`
- L3 #pragma `once`

#### static const (6)

- L10 _static_const_ `static const uint kReprojectionVectorOutputIndex = 0;`
- L11 _static_const_ `static const uint kReprojectionJacobianOutputIndex = 1;`
- L12 _static_const_ `static const uint kReprojectionBoundaryOutputIndex = 2;`
- L17 _static_const_ `static const tsr_half2 kFullDilateBoundary = tsr_half2(0.0, 1.0);`
- L107 _static_const_ `static const tsr_half kVelocityJacobianRange = tsr_half(2.0);`
- L109 _static_const_ `static const uint kVelocityJacobianBits = 8u;` — static const tsr_half kVelocityJacobianRange = tsr_half(0.5);

#### Functions (12)

- L19-22 _function_ `uint EncodeReprojectionOffset(tsr_short2 ReprojectionOffset)`
- L25-34 _function_ `uint EncodeReprojectionBoundary(tsr_short2 ReprojectionOffset, tsr_half2 ReprojectionBoundary)` — Encodes the reprojection field's dilating offset [-1;1]^2 in first 4bits, and ReprojectionBoundary.xy in 11bit eachs, 26bits total.
- L37-41 _function_ `tsr_short2 DecodeReprojectionOffset(uint EncodedReprojectionBoundary)` — Decodes EncodeReprojectionBoundary()'s ReprojectionOffset.
- L44-49 _function_ `bool HasEncodedReprojectionOffset(uint EncodedReprojectionBoundary)` — Returns any(EncodeReprojectionBoundary() != 0).
- L52-57 _function_ `tsr_half2 DecodeReprojectionBoundary(uint EncodedReprojectionBoundary)` — Decodes EncodeReprojectionBoundary()'s ReprojectionBoundary.
- L60-64 _function_ `tsr_half ComputeReprojectionBoundaryCoverage(tsr_half2 ReprojectionBoundary)` — Estimate the coverage of the boundary over the rendered pixel.
- L67-77 _function_ `bool IsHistoryPixelWithinOffsetBoundary(tsr_half2 dInputKO, tsr_half2 ReprojectionBoundary, float HistoryToInputFactor)` — Returns whether the history's pixel has any overlap with the velocity boundary, to apply the ReprojectionOffset.
- L83-93 _function_ `uint EncodeReprojectionVector(float2 ReprojectionVector)` — Encodes the reprojection vector into 32bits.
- L96-102 _function_ `float2 DecodeReprojectionVector(uint EncodedReprojectionVector)` — Inverse of EncodeReprojectionVector()
- L112-133 _function_ `uint EncodeReprojectionJacobian(tsr_half2x2 ReprojectionJacobian)` — Encodes the reprojection's jacobian into 32bits.
- L136-156 _function_ `tsr_half2x2 DecodeReprojectionJacobian(uint EncodedReprojectionJacobian)` — Inverse of EncodeReprojectionJacobian()
- L159-166 _function_ `tsr_half ComputeReprojectionUpscaleFactorFromJacobian(tsr_half2x2 ReprojectionJacobian)` — Estimate upscale ratio of the reprojection jsut from the jacobian.

### `Shaders/Private/TemporalSuperResolution/TSRResolveHistory.usf` (Private)

- lines: 431; parse: all-branches
- includes: L3 `TSRColorSpace.ush`, L55 `TSRConvolutionNetwork.ush` [DIM_NYQUIST_WAVE_SIZE != 0]

#### Macros (#define, 21)

- L9 `#define WAVE_COUNT_X 1` _[#if DIM_NYQUIST_WAVE_SIZE != 0]_
- L10 `#define WAVE_COUNT_Y 1` _[#if DIM_NYQUIST_WAVE_SIZE != 0]_
- L12 `#define DOWNSAMPLE_FACTOR 2u` _[#if DIM_NYQUIST_WAVE_SIZE != 0]_
- L15 `#define GROUP_TILE_SIZE 8u` _[#if DIM_NYQUIST_WAVE_SIZE != 0]_
- L16 `#define TILE_SIZE (GROUP_TILE_SIZE - 2u)` _[#if DIM_NYQUIST_WAVE_SIZE != 0]_
- L18 `#define LANE_OUTPUT_STRIDE_X 2u` _[#if DIM_NYQUIST_WAVE_SIZE != 0]_
- L20 `#define LANE_OUTPUT_STRIDE_Y 2u` _[#if DIM_NYQUIST_WAVE_SIZE != 0 && DIM_NYQUIST_WAVE_SIZE == 16]_
- L22 `#define LANE_OUTPUT_STRIDE_Y 1u` _[#if DIM_NYQUIST_WAVE_SIZE != 0 && !(DIM_NYQUIST_WAVE_SIZE == 16) && DIM_NYQUIST_WAVE_SIZE == 32]_
- L26 `#define LANE_INPUT_STRIDE_X (LANE_OUTPUT_STRIDE_X * DOWNSAMPLE_FACTOR)` _[#if DIM_NYQUIST_WAVE_SIZE != 0]_
- L27 `#define LANE_INPUT_STRIDE_Y (LANE_OUTPUT_STRIDE_Y * DOWNSAMPLE_FACTOR)` _[#if DIM_NYQUIST_WAVE_SIZE != 0]_
- L30 `#define LANE_COUNT_X (GROUP_TILE_SIZE / LANE_OUTPUT_STRIDE_X)` _[#if DIM_NYQUIST_WAVE_SIZE != 0]_
- L31 `#define LANE_COUNT_Y (GROUP_TILE_SIZE / LANE_OUTPUT_STRIDE_Y)` _[#if DIM_NYQUIST_WAVE_SIZE != 0]_
- L34 `#define INPUT_SIMD_SIZE (LANE_INPUT_STRIDE_X * LANE_INPUT_STRIDE_Y)` _[#if DIM_NYQUIST_WAVE_SIZE != 0]_
- L35 `#define OUTPUT_SIMD_SIZE (LANE_OUTPUT_STRIDE_X * LANE_OUTPUT_STRIDE_Y)` _[#if DIM_NYQUIST_WAVE_SIZE != 0]_
- L37 `#define tsr_input_halfC TLaneVector2D<tsr_half, CONFIG_CHANNEL_COUNT, LANE_INPUT_STRIDE_X, LANE_INPUT_STRIDE_Y>` _[#if DIM_NYQUIST_WAVE_SIZE != 0]_
- L38 `#define tsr_output_halfC TLaneVector2D<tsr_half, CONFIG_CHANNEL_COUNT, LANE_OUTPUT_STRIDE_X, LANE_OUTPUT_STRIDE_Y>` _[#if DIM_NYQUIST_WAVE_SIZE != 0]_
- L39 `#define tsr_output_half TLaneVector2D<tsr_half, 1, LANE_OUTPUT_STRIDE_X, LANE_OUTPUT_STRIDE_Y>` _[#if DIM_NYQUIST_WAVE_SIZE != 0]_
- L42 `#define TILE_SIZE 8` _[#if !(DIM_NYQUIST_WAVE_SIZE != 0)]_
- L45 `#define KERNEL_SIZE 4`
- L47 `#define CONFIG_CLAMP 1`
- L49 `#define CONFIG_HDR_WEIGHT 1`

#### Entry points (2)

- L148-293 _entry_ `[numthreads(LANE_COUNT, 1, 1)] void ResolveHistoryCS( uint2 GroupId : SV_GroupID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FTSRResolveHistoryCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/TemporalSuperResolution.cpp:1516) _[#if DIM_NYQUIST_WAVE_SIZE != 0]_
- L299-428 _entry_ `[numthreads(TILE_SIZE * TILE_SIZE, 1, 1)] void ResolveHistoryCS( uint2 GroupId : SV_GroupID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FTSRResolveHistoryCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/TemporalSuperResolution.cpp:1516) _[#if !(DIM_NYQUIST_WAVE_SIZE != 0)]_

#### Global resources (textures / buffers / samplers) (5)

- L71 _resource_ `RWTexture2D<uint> PrevUseCountOutput;`
- L72 _resource_ `RWTexture2D<uint> PrevClosestDepthOutput;`
- L135 _resource_ `Texture2D<tsr_halfC> UpdateHistoryOutputTexture;`
- L137 _resource_ `RWTexture2D<tsr_halfC> SceneColorOutputMip0;`
- L138 _resource_ `RWTexture2D<tsr_halfC> SceneColorOutputMip1;`

#### Global parameters (uniforms) (5)

- L129 _parameter_ `FScreenTransform DispatchThreadToHistoryPixelPos;`
- L130 _parameter_ `uint2 OutputViewRectMin;`
- L131 _parameter_ `uint2 OutputViewRectMax;`
- L132 _parameter_ `uint bGenerateOutputMip1;`
- L133 _parameter_ `float HistoryValidityMultiply;`

#### groupshared (1)

- L77 _groupshared_ `groupshared tsr_halfC SharedArray0[TILE_SIZE * TILE_SIZE];`

#### static const (3)

- L61-66 _static_const_ `static const int2 kOffsetsCross3x3[4] = { int2(-1, -1), int2( 1, -1), int2(-1, 1), int2( 1, 1), };`
- L82 _static_const_ `static const float MitchellNetravaliB = rcp(3.0);`
- L83 _static_const_ `static const float MitchellNetravaliC = rcp(3.0);`

#### Functions (2)

- L92-103 _function_ `void MitchellNetravaliCoefs(const float B, const float C, out float OutQ0[4], out float OutQ1[4])` — Mitchell Netravali B-spline:       B=1      C=0 Mitchell:       B=1/3    C=1/3 Catmull-Rom:    B=0      C=1/2 Robidoux:       B=0.3782 C=0.3109 (cylindrical) Robidoux Sharp: B=0.2620 C=0.3690 (cylindrical) Robidoux Soft:  B=0.6796 C=0.1602 (cylindrical)
- L105-124 _function_ `float MitchellNetravali(float d, const float B, const float C)`

#### Top-level macro invocations (1)

- L146 _macro_call_ `WAVESIZE(DIM_NYQUIST_WAVE_SIZE)` _[#if DIM_NYQUIST_WAVE_SIZE != 0 && COMPILER_SUPPORTS_WAVE_SIZE]_

### `Shaders/Private/TemporalSuperResolution/TSRShadingAnalysis.ush` (Private)

- lines: 645; parse: all-branches
- includes: L8 `TSRColorSpace.ush`, L9 `TSRSpatialAntiAliasing.ush`, L10 `TSRConvolutionNetworkPass.ush`

#### Macros (#define, 3)

- L15 `#define CONFIG_THIN_GEOMETRY_DETECTION 0` _[#if !defined(CONFIG_THIN_GEOMETRY_DETECTION)]_
- L18 `#define REJECT_SHADING_RESPONSIVE 0`
- L19 `#define REJECT_SHADING_STABILITY 1`
- L3 #pragma `once`

#### Global parameters (uniforms) (6)

- L29 _parameter_ `float ExposureOffsetFactor;`
- L30 _parameter_ `float FlickeringFramePeriod;`
- L31 _parameter_ `uint bPassthroughAlpha;`
- L32 _parameter_ `uint RejectShadingMode;`
- L33 _parameter_ `int ThinGeometryAffectMoireError;`
- L36 _parameter_ `float2 TotalVariationCountInvThreshold;` — Cache the threshold at which the variation count should quick in

#### static const (2)

- L23 _static_const_ `static const float kHistoryGuidePreceptionAdd = 1.0;`
- L25 _static_const_ `static const tsr_half FilteringWeight = rcp(tsr_half(1.0 + 4 * 0.5 + 4 * 0.25));`

#### Functions (15)

- L41-55 _function_ `CALL_SITE_DEBUGLOC tsr_tensor_halfC ComposeTranslucency(tsr_tensor_halfC Color, tsr_tensor_half4 Translucency, tsr_tensor_bool bAllowPassthroughAlpha = tsr_tensor_bool::Const(true))` — Compose translucency in linear color space.
- L58-86 _function_ `tsr_tensor_halfC ComposeTranslucencyForRejection(tsr_tensor_halfC OriginalOpaqueInput, tsr_tensor_half4 OriginalTranslucencyInput, tsr_tensor_bool bHasPixelAnimation)` — Compose blurry translucency for tighter rejection in linear color space.
- L91-98 _function_ `CALL_SITE_DEBUGLOC tsr_tensor_halfC RemovePerceptionAdd(tsr_tensor_halfC SrcColor, const float SourcePerceptionAdd)`
- L100-105 _function_ `CALL_SITE_DEBUGLOC tsr_tensor_halfC AddPerceptionAdd(tsr_tensor_halfC SrcColor, const float DestPerceptionAdd)`
- L110-119 _function_ `CALL_SITE_DEBUGLOC tsr_tensor_halfC LinearToGCS(tsr_tensor_halfC SrcColor)`
- L121-134 _function_ `CALL_SITE_DEBUGLOC tsr_tensor_halfC GCSToLinear(tsr_tensor_halfC GColor)`
- L138-143 _function_ `CALL_SITE_DEBUGLOC tsr_tensor_half GCSToSMCS(tsr_tensor_half GColor)`
- L145-150 _function_ `CALL_SITE_DEBUGLOC tsr_tensor_half SMCSToGCS(tsr_tensor_half SMColor)`
- L152-160 _function_ `CALL_SITE_DEBUGLOC tsr_tensor_halfC GCSToSMCS(tsr_tensor_halfC GColor)`
- L162-166 _function_ `CALL_SITE_DEBUGLOC tsr_tensor_halfC LinearToSMCS(tsr_tensor_halfC LinearColor)`
- L172-187 _function_ `CALL_SITE_DEBUGLOC tsr_tensor_half ComputeSpatialAntiAliaserLumaLDR(tsr_tensor_halfC SceneColor)` — Compute the LDR luminance the spatial anti-aliaser should anti-alias.
- L190-202 _function_ `CALL_SITE_DEBUGLOC tsr_tensor_bool IsAliasingVisible(tsr_tensor_halfC ExposedInputBoxSize)` — Returns whether the aliasing is visible at all, to avoid paying spatial-antialiaser on low contrasts areas.
- L205-211 _function_ `CALL_SITE_DEBUGLOC tsr_tensor_bool ShouldSpatialAntiAlias(tsr_tensor_bool bIsDisoccluded, tsr_tensor_bool bResurrectHistory, tsr_tensor_bool bAliasingIsVisible, tsr_tensor_half RejectionBlendFinal)` — Whether to run spatial anti-aliaser on the frame. Must match SpatialAntiAliasingLerp.
- L215-491 _function_ `void ComputeMoireError( tsr_tensor_bool bIsDisoccluded, tsr_tensor_half bIsStatic, tsr_tensor_half MoireInput, tsr_tensor_halfC OriginalOpaqueInput, tsr_tensor_half4 OriginalTranslucencyInput, tsr_tensor_half4 PrevMoireHistory, tsr_tensor_half HistoryRelaxationFactor, const bool bEnableThinGeometry, out tsr_tensor_half4 OutMoireHistory, out tsr_tensor_half OutMoireError)`
- L496-644 _function_ `void MeasureRejection( tsr_tensor_halfC InputC0, tsr_tensor_halfC InputC2, tsr_tensor_halfC HistoryC2, tsr_tensor_half MoireError, tsr_tensor_half HistoryRelaxationFactor, const bool bEnableHistoryControl, bool bEnableMoireError, out tsr_tensor_half OutRejectionBlendFinal, out tsr_tensor_half OutRejectionClampBlend)`

### `Shaders/Private/TemporalSuperResolution/TSRSpatialAntiAliasing.usf` (Private)

- lines: 236; parse: first-branch (retry, +0 merged from all-branches pass)
- includes: L3 `TSRSpatialAntiAliasing.ush`

#### Macros (#define, 7)

- L8 `#define TILE_SIZE 8`
- L11 `#define CONFIG_ITERATIONS 3` _[#if DIM_QUALITY_PRESET == 1]_
- L14 `#define CONFIG_ITERATIONS 8` _[#if !(DIM_QUALITY_PRESET == 1) && DIM_QUALITY_PRESET == 2]_
- L22 `#define CONFIG_ENABLE_DUAL_PIXEL_VECTORIZATION 1` _[#if CONFIG_COMPILE_FP16]_
- L24 `#define CONFIG_ENABLE_DUAL_PIXEL_VECTORIZATION 0` _[#if !(CONFIG_COMPILE_FP16)]_
- L133 `#define ReadCache(x, y) tsr_half2(InputCache[(x + 1) + 4 * (y + 1)], InputCache[(x + 2) + 4 * (y + 1)])` _[#if CONFIG_ENABLE_DUAL_PIXEL_VECTORIZATION && 1]_
- L135 `#define ReadCache(x, y) SampleInputLDRLuma(InputPixelPos, tsr_short2(x, y));` _[#if !(CONFIG_ENABLE_DUAL_PIXEL_VECTORIZATION && 1)]_

#### Entry points (1)

- L84-235 _entry_ `[numthreads(TILE_SIZE * TILE_SIZE / 2, 1, 1)] [numthreads(TILE_SIZE * TILE_SIZE, 1, 1)] void SpatialAntiAliasingCS( uint2 GroupId : SV_GroupID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FTSRSpatialAntiAliasingCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/TemporalSuperResolution.cpp:1514) _[#if CONFIG_ENABLE_DUAL_PIXEL_VECTORIZATION]_

#### Global resources (textures / buffers / samplers) (3)

- L30 _resource_ `Texture2D<tsr_ushort> AntiAliasMaskTexture;`
- L31 _resource_ `Texture2D<tsr_half> InputSceneColorLdrLumaTexture;`
- L33 _resource_ `RWTexture2D<tsr_ushort2> AntiAliasingOutput;`

#### Functions (3)

- L38-48 _function_ `tsr_ushort2x2 Map8x8Tile2x2LaneDPV(uint GroupThreadIndex)`
- L56-64 _function_ `tsr_half SampleInputLDRLuma(tsr_short2 KernelCenter, tsr_short2 Offset)`
- L66-78 _function_ `tsr_half2 SampleInputLDRLuma(tsr_short2x2 KernelCenter, tsr_short2 Offset)`

### `Shaders/Private/TemporalSuperResolution/TSRSpatialAntiAliasing.ush` (Private)

- lines: 680; parse: all-branches
- includes: L5 `TSRKernels.ush`

#### Macros (#define, 5)

- L10 `#define SPATIAL_ANTI_ALIASER_MIN_LUMIMANCE 0.05`
- L308 `#define asuintX(x) asuint16(x)` _[#if CONFIG_COMPILE_FP16]_
- L312 `#define asuintX(x) asuint(x)` _[#if !(CONFIG_COMPILE_FP16)]_
- L637 `#define SPATIAL_ANTI_ALIASING_OFFSET_RANGE 0.5`
- L638 `#define SPATIAL_ANTI_ALIASING_OFFSET_BITDEPTH_PER_CHANNEL 4`
- L3 #pragma `once`

#### Functions (15)

- L15-26 _function_ `tsr_half2 SampleAAInput(Texture2D<tsr_half> Texture, tsr_short2x2 KernelCenter, tsr_short2x2 Offset)`
- L28-38 _function_ `float BilinearSampleAAInput(Texture2D<float> Texture, float2 KernelCenterUV, float2 UVOffset, const bool bIsNegativeDirection)`
- L40-54 _function_ `tsr_half2 BilinearSampleAAInput(Texture2D<tsr_half> Texture, float2x2 KernelCenterUV, float2x2 UVOffset, const bool bIsNegativeDirection)`
- L60-110 _function_ `void FindBrowsingDirection( float InputC, float InputN, float InputS, float InputE, float InputW, float InputNE, float InputNW, float InputSE, float InputSW, out float NoiseFiltering, out tsr_short2 BrowseDirection, out tsr_short2 EdgeSide, out float EdgeInput)` — Finds the browsing direction of the spatial anti-aliaser out from the neighborhood.
- L113-175 _function_ `void FindBrowsingDirection( tsr_half2 InputC, tsr_half2 InputN, tsr_half2 InputS, tsr_half2 InputE, tsr_half2 InputW, tsr_half2 InputNE, tsr_half2 InputNW, tsr_half2 InputSE, tsr_half2 InputSW, out tsr_half2 NoiseFiltering, out tsr_short2x2 BrowseDirection, out tsr_short2x2 EdgeSide, out tsr_half2 EdgeLuma)` — Finds the browsing direction of the spatial anti-aliaser out from the neighborhood.
- L181-205 _function_ `void AccumulateEdgeLength( tsr_half2 StartLuma, tsr_half2 StartEdgeLuma, tsr_half2 SampleLuma, tsr_half2 SampleEdgeLuma, tsr_half2 LumaDelta, inout bool2 bEdgeStopedByIncrement, inout bool2 bEdgeStopedByDecrement, inout tsr_ushort2 EdgeLength)` — Accumulate an edge length
- L207-263 _function_ `void BrowseNeighborhood( const uint Iterations, Texture2D<tsr_half> Texture, tsr_half2 InputC, tsr_half2 EdgeLuma, tsr_half2 LumaDelta, tsr_short2x2 KernelCenter, tsr_short2x2 BrowseDirection, tsr_short2x2 EdgeSide, out tsr_ushort2 EdgeLengthP, out tsr_ushort2 EdgeLengthN, out bool2 bEdgeStopedByIncrementP, out bool2 bEdgeStopedByIncrementN, out bool2 bEdgeStopedByDecrementP, out bool2 bEdgeStopedByDecrementN)`
- L265-358 _function_ `void BrowseNeighborhoodBilinearOptimized( const uint Iterations, Texture2D<tsr_half> Texture, tsr_half2 InputC, tsr_half2 EdgeLuma, tsr_short2x2 InputPixelPos, tsr_short2x2 BrowseDirection, tsr_short2x2 EdgeSide, out tsr_ushort2 EdgeLengthP, out tsr_ushort2 EdgeLengthN, out bool2 bEdgeStopedByIncrementP, out bool2 bEdgeStopedByIncrementN, out bool2 bEdgeStopedByDecrementP, out bool2 bEdgeStopedByDecrementN)`
- L360-446 _function_ `void BrowseNeighborhoodBilinearOptimized( const uint Iterations, Texture2D<float> Texture, float InputC, float EdgeLuma, tsr_short2 InputPixelPos, tsr_short2 BrowseDirection, tsr_short2 EdgeSide, out tsr_ushort EdgeLengthP, out tsr_ushort EdgeLengthN, out bool bEdgeStopedByIncrementP, out bool bEdgeStopedByIncrementN, out bool bEdgeStopedByDecrementP, out bool bEdgeStopedByDecrementN)`
- L448-494 _function_ `tsr_half ComputeDistanceToEdge( bool bEdgeStopedByIncrementN, bool bEdgeStopedByIncrementP, bool bEdgeStopedByDecrementN, bool bEdgeStopedByDecrementP, tsr_ushort EdgeLengthN, tsr_ushort EdgeLengthP)`
- L496-631 _function_ `tsr_half2 ComputeReprojectionBoundary( const uint BrowsingIterations, tsr_short2 EdgeSide, tsr_ushort EdgeLengthP, tsr_ushort EdgeLengthN, bool bEdgeStopedByIncrementP, bool bEdgeStopedByIncrementN, bool bEdgeStopedByDecrementP, bool bEdgeStopedByDecrementN)`
- L640-652 _function_ `CALL_SITE_DEBUGLOC uint2 EncodeSpatialAntiAliasingOffset(tsr_half2x2 TexelOffset)`
- L654-658 _function_ `CALL_SITE_DEBUGLOC uint EncodeSpatialAntiAliasingOffset(tsr_half2 TexelOffset)`
- L660-673 _function_ `CALL_SITE_DEBUGLOC tsr_half2x2 DecodeSpatialAntiAliasingOffset(tsr_ushort2 EncodedInputTexelOffset)`
- L675-679 _function_ `CALL_SITE_DEBUGLOC tsr_half2 DecodeSpatialAntiAliasingOffset(tsr_ushort EncodedInputTexelOffset)`

### `Shaders/Private/TemporalSuperResolution/TSRThinGeometryCommon.ush` (Private)

- lines: 142; parse: all-branches
- includes: L6 `TSRColorSpace.ush`, L7 `TSRConvolutionNetworkPass.ush`

#### Macros (#define, 2)

- L19 `#define CONFIG_TRANSLUCENCY_COVERAGE_BIT 0` _[#if !defined(CONFIG_TRANSLUCENCY_COVERAGE_BIT)]_
- L23 `#define CONFIG_INTENSITY_LINE_DETECTION 0` _[#if !defined(CONFIG_INTENSITY_LINE_DETECTION)]_
- L3 #pragma `once`

#### static const (12)

- L27 _static_const_ `static const tsr_half kCoverageMaxValue = tsr_half(63.0);` _[#if CONFIG_TRANSLUCENCY_COVERAGE_BIT && CONFIG_INTENSITY_LINE_DETECTION]_
- L28 _static_const_ `static const tsr_ushort kCoverageShift = tsr_ushort(0x2);` _[#if CONFIG_TRANSLUCENCY_COVERAGE_BIT && CONFIG_INTENSITY_LINE_DETECTION]_
- L29 _static_const_ `static const tsr_ushort kTranslucencyBit = tsr_ushort(0x2);` _[#if CONFIG_TRANSLUCENCY_COVERAGE_BIT && CONFIG_INTENSITY_LINE_DETECTION]_
- L31 _static_const_ `static const tsr_half kCoverageMaxValue = tsr_half(127.0);` _[#if !(CONFIG_TRANSLUCENCY_COVERAGE_BIT && CONFIG_INTENSITY_LINE_DETECTION) && CONFIG_INTENSITY_LINE_DETECTION]_
- L32 _static_const_ `static const tsr_ushort kCoverageShift = tsr_ushort(0x1);` _[#if !(CONFIG_TRANSLUCENCY_COVERAGE_BIT && CONFIG_INTENSITY_LINE_DETECTION) && CONFIG_INTENSITY_LINE_DETECTION]_
- L33 _static_const_ `static const tsr_ushort kTranslucencyBit = tsr_ushort(0x0);` _[#if !(CONFIG_TRANSLUCENCY_COVERAGE_BIT && CONFIG_INTENSITY_LINE_DETECTION) && CONFIG_INTENSITY_LINE_DETECTION]_
- L35 _static_const_ `static const tsr_half kCoverageMaxValue = tsr_half(127.0);` _[#if !(CONFIG_TRANSLUCENCY_COVERAGE_BIT && CONFIG_INTENSITY_LINE_DETECTION) && !(CONFIG_INTENSITY_LINE_DETECTION) && CONFIG_TRANSLUCENCY_COVERAGE_BIT]_
- L36 _static_const_ `static const tsr_ushort kCoverageShift = tsr_ushort(0x1);` _[#if !(CONFIG_TRANSLUCENCY_COVERAGE_BIT && CONFIG_INTENSITY_LINE_DETECTION) && !(CONFIG_INTENSITY_LINE_DETECTION) && CONFIG_TRANSLUCENCY_COVERAGE_BIT]_
- L37 _static_const_ `static const tsr_ushort kTranslucencyBit = tsr_ushort(0x1);` _[#if !(CONFIG_TRANSLUCENCY_COVERAGE_BIT && CONFIG_INTENSITY_LINE_DETECTION) && !(CONFIG_INTENSITY_LINE_DETECTION) && CONFIG_TRANSLUCENCY_COVERAGE_BIT]_
- L39 _static_const_ `static const tsr_half kCoverageMaxValue = tsr_half(255.0);` _[#if !(CONFIG_TRANSLUCENCY_COVERAGE_BIT && CONFIG_INTENSITY_LINE_DETECTION) && !(CONFIG_INTENSITY_LINE_DETECTION) && !(CONFIG_TRANSLUCENCY_COVERAGE_BIT)]_
- L40 _static_const_ `static const tsr_ushort kCoverageShift = tsr_ushort(0x0);` _[#if !(CONFIG_TRANSLUCENCY_COVERAGE_BIT && CONFIG_INTENSITY_LINE_DETECTION) && !(CONFIG_INTENSITY_LINE_DETECTION) && !(CONFIG_TRANSLUCENCY_COVERAGE_BIT)]_
- L43 _static_const_ `static const tsr_ushort kHighContrastLineBit = tsr_ushort(0x1);`

#### Functions (9)

- L46-49 _function_ `float EncodeThinGeometryMaterial(uint ThinGeometryFlag)`
- L51-55 _function_ `CALL_SITE_DEBUGLOC tsr_tensor_bool IsThinGeometry(tsr_tensor_half CurrentCoverage)`
- L57-61 _function_ `CALL_SITE_DEBUGLOC tsr_tensor_half ToBinaryCoverage(tsr_tensor_half EncodedThinGeometryMaterial)`
- L63-73 _function_ `CALL_SITE_DEBUGLOC void DecodeThinGeometry( tsr_tensor_ushort EncodedThinGeometryWeight, out tsr_tensor_half HistoryRelaxationWeight, out tsr_tensor_bool IsClusterHoleRegion)`
- L75-84 _function_ `CALL_SITE_DEBUGLOC tsr_tensor_ushort EncodeThinGeometry( tsr_tensor_half HistoryRelaxationWeight, tsr_tensor_bool IsClusterHoleRegion)`
- L88-94 _function_ `tsr_half EncodeCoverage(tsr_half Coverage, bool bHighContrastLine, tsr_half Dither)` — HadTranslucency bit resets to 0
- L96-103 _function_ `tsr_ushort GetTranslucencyOnlyBitMask(bool bIntensityLineDetectionEnabled)`
- L105-114 _function_ `tsr_half OverwriteCoverageWithTranslucencyBit(tsr_half EncodedCoverage, bool bHadTranslucency, bool bIntensityLineDetectionEnabled)`
- L116-142 _function_ `CALL_SITE_DEBUGLOC void DecodeCoverage( tsr_tensor_half RawValue, out tsr_tensor_half Coverage ,out tsr_tensor_half HighContrastLine ,out tsr_tensor_half HadTranslucency )`

### `Shaders/Private/TemporalSuperResolution/TSRUpdateHistory.usf` (Private)

- lines: 1427; parse: first-branch (retry, +0 merged from all-branches pass)
- includes: L3 `TSRKernels.ush`, L4 `TSRSpatialAntiAliasing.ush`, L5 `TSRColorSpace.ush`, L6 `TSRReprojectionField.ush`

#### Macros (#define, 35)

- L11 `#define DEBUG_ARRAY_SIZE 8`
- L18 `#define CONFIG_SAMPLES_1X1 0`
- L21 `#define CONFIG_SAMPLES_3X3 1`
- L24 `#define CONFIG_SAMPLES_PLUS 2`
- L27 `#define CONFIG_SAMPLES_PLUS_AND_CORNER 3`
- L30 `#define CONFIG_SAMPLES_PLUS_DISABLE_FAR 4`
- L33 `#define CONFIG_SAMPLES_PLUS_MOVE_FAR 5`
- L39 `#define CONFIG_SAMPLES CONFIG_SAMPLES_PLUS` _[#if DIM_UPDATE_QUALITY == 0]_
- L40 `#define CONFIG_REJECTION_ANTI_ALIASING 0` _[#if DIM_UPDATE_QUALITY == 0]_
- L43 `#define CONFIG_SAMPLES CONFIG_SAMPLES_PLUS` _[#if !(DIM_UPDATE_QUALITY == 0) && DIM_UPDATE_QUALITY == 1]_
- L44 `#define CONFIG_REJECTION_ANTI_ALIASING 1` _[#if !(DIM_UPDATE_QUALITY == 0) && DIM_UPDATE_QUALITY == 1]_
- L47 `#define CONFIG_SAMPLES CONFIG_SAMPLES_PLUS_MOVE_FAR` _[#if !(DIM_UPDATE_QUALITY == 0) && !(DIM_UPDATE_QUALITY == 1) && DIM_UPDATE_QUALITY == 2]_
- L48 `#define CONFIG_REJECTION_ANTI_ALIASING 1` _[#if !(DIM_UPDATE_QUALITY == 0) && !(DIM_UPDATE_QUALITY == 1) && DIM_UPDATE_QUALITY == 2]_
- L51 `#define CONFIG_SAMPLES CONFIG_SAMPLES_PLUS_MOVE_FAR` _[#if !(DIM_UPDATE_QUALITY == 0) && !(DIM_UPDATE_QUALITY == 1) && !(DIM_UPDATE_QUALITY == 2) && DIM_UPDATE_QUALITY == 3]_
- L52 `#define CONFIG_REJECTION_ANTI_ALIASING 1` _[#if !(DIM_UPDATE_QUALITY == 0) && !(DIM_UPDATE_QUALITY == 1) && !(DIM_UPDATE_QUALITY == 2) && DIM_UPDATE_QUALITY == 3]_
- L62 `#define CONFIG_HISTORY_RESURRECTION 1`
- L65 `#define CONFIG_REPROJECTION_FIELD 1`
- L68 `#define CONFIG_LENS_DISTORTION TSR_SUPPORT_LENS_DISTORTION`
- L71 `#define CONFIG_CLAMP 1`
- L75 `#define CONFIG_SAMPLES_COUNT 1` _[#if CONFIG_SAMPLES == CONFIG_SAMPLES_1X1]_
- L77 `#define CONFIG_SAMPLES_COUNT 9` _[#if !(CONFIG_SAMPLES == CONFIG_SAMPLES_1X1) && CONFIG_SAMPLES == CONFIG_SAMPLES_3X3]_
- L79 `#define CONFIG_SAMPLES_COUNT 6` _[#if !(CONFIG_SAMPLES == CONFIG_SAMPLES_1X1) && !(CONFIG_SAMPLES == CONFIG_SAMPLES_3X3) && CONFIG_SAMPLES == CONFIG_SAMPLES_PLUS_6]_
- L81 `#define CONFIG_SAMPLES_COUNT 5` _[#if !(CONFIG_SAMPLES == CONFIG_SAMPLES_1X1) && !(CONFIG_SAMPLES == CONFIG_SAMPLES_3X3) && !(CONFIG_SAMPLES == CONFIG_SAMPLES_PLUS_6)]_
- L85 `#define CONFIG_SELECTIVE_REPROJECTION 1`
- L90 `#define CONFIG_ENABLE_DUAL_PIXEL_VECTORIZATION 1` _[#if CONFIG_COMPILE_FP16]_
- L92 `#define CONFIG_ENABLE_DUAL_PIXEL_VECTORIZATION 0` _[#if !(CONFIG_COMPILE_FP16)]_
- L96 `#define PLATFORM_SPECIFIC_ISOLATE ISOLATE` _[#if !defined(PLATFORM_SPECIFIC_ISOLATE)]_
- L102 `#define TILE_SIZE 8`
- L104 `#define CONFIG_METADATA_CHANNELS 1`
- L107 `#define tsr_halfM tsr_half2` _[#if CONFIG_METADATA_CHANNELS == 2]_
- L108 `#define tsr_halfMx2 tsr_half2x2` _[#if CONFIG_METADATA_CHANNELS == 2]_
- L110 `#define tsr_halfM tsr_half` _[#if !(CONFIG_METADATA_CHANNELS == 2) && CONFIG_METADATA_CHANNELS == 1]_
- L111 `#define tsr_halfMx2 tsr_half2` _[#if !(CONFIG_METADATA_CHANNELS == 2) && CONFIG_METADATA_CHANNELS == 1]_
- L173 `#define GROUP_SHARED_SIZE (TILE_SIZE * TILE_SIZE / 2)` _[#if CONFIG_ENABLE_DUAL_PIXEL_VECTORIZATION]_
- L175 `#define GROUP_SHARED_SIZE (TILE_SIZE * TILE_SIZE)` _[#if !(CONFIG_ENABLE_DUAL_PIXEL_VECTORIZATION)]_

#### Entry points (1)

- L634-1426 _entry_ `[numthreads(TILE_SIZE * TILE_SIZE / 2, 1, 1)] [numthreads(TILE_SIZE * TILE_SIZE, 1, 1)] void UpdateHistoryCS( uint2 GroupId : SV_GroupID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FTSRUpdateHistoryCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/TemporalSuperResolution.cpp:1515) _[#if CONFIG_ENABLE_DUAL_PIXEL_VECTORIZATION]_

#### Global resources (textures / buffers / samplers) (14)

- L119 _resource_ `Texture2D<tsr_halfC> InputSceneColorTexture;`
- L121 _resource_ `Texture2D<tsr_half4> HistoryRejectionTexture;`
- L124 _resource_ `Texture2D<uint> ReprojectionBoundaryTexture;` _[#if CONFIG_REPROJECTION_FIELD]_
- L125 _resource_ `Texture2D<uint> ReprojectionJacobianTexture;` _[#if CONFIG_REPROJECTION_FIELD]_
- L127 _resource_ `Texture2D<uint> ReprojectionVectorTexture;`
- L128 _resource_ `Texture2D<tsr_ushort2> AntiAliasingTexture;`
- L131 _resource_ `Texture2D<float2> PrevDistortingDisplacementTexture;` _[#if CONFIG_LENS_DISTORTION]_
- L132 _resource_ `Texture2D<float2> ResurrectedDistortingDisplacementTexture;` _[#if CONFIG_LENS_DISTORTION]_
- L133 _resource_ `Texture2D<float2> UndistortingDisplacementTexture;` _[#if CONFIG_LENS_DISTORTION]_
- L161 _resource_ `Texture2DArray<tsr_halfC> PrevHistoryColorTexture;`
- L162 _resource_ `Texture2DArray<tsr_halfM> PrevHistoryMetadataTexture;`
- L164 _resource_ `RWTexture2DArray<tsr_halfC> HistoryColorOutput;`
- L165 _resource_ `RWTexture2DArray<tsr_halfM> HistoryMetadataOutput;`
- L167 _resource_ `RWTexture2DArray<tsr_halfC> SceneColorOutputMip1;`

#### Global parameters (uniforms) (20)

- L134 _parameter_ `float DistortionOverscan;` _[#if CONFIG_LENS_DISTORTION]_
- L137 _parameter_ `FScreenTransform HistoryPixelPosToViewportUV;`
- L138 _parameter_ `FScreenTransform ViewportUVToInputPPCo;`
- L139 _parameter_ `FScreenTransform HistoryPixelPosToScreenPos;`
- L140 _parameter_ `FScreenTransform HistoryPixelPosToInputPPCo;`
- L141 _parameter_ `float3 HistoryQuantizationError;`
- L142 _parameter_ `float HistorySampleCount;`
- L143 _parameter_ `float HistoryHisteresis;`
- L144 _parameter_ `float WeightClampingRejection;`
- L145 _parameter_ `float WeightClampingPixelSpeedAmplitude;`
- L146 _parameter_ `float InvWeightClampingPixelSpeed;`
- L147 _parameter_ `float InputToHistoryFactor;`
- L148 _parameter_ `float ResurrectionFrameIndex;`
- L149 _parameter_ `float PrevFrameIndex;`
- L151 _parameter_ `uint bLensDistortion;` _[#if CONFIG_LENS_DISTORTION]_
- L154 _parameter_ `uint bReprojectionField;` _[#if CONFIG_REPROJECTION_FIELD]_
- L156 _parameter_ `uint bGenerateOutputMip1;`
- L157 _parameter_ `uint bGenerateOutputMip2;`
- L158 _parameter_ `uint bGenerateOutputMip3;`
- L159 _parameter_ `uint HistoryArrayIndices_HighFrequency;`

#### groupshared (12)

- L178 _groupshared_ `groupshared tsr_half4 SharedArray0[GROUP_SHARED_SIZE];`
- L179 _groupshared_ `groupshared tsr_half4 SharedArray1[GROUP_SHARED_SIZE];`
- L180 _groupshared_ `groupshared tsr_half4 SharedArray2[GROUP_SHARED_SIZE];`
- L181 _groupshared_ `groupshared tsr_half4 SharedArray3[GROUP_SHARED_SIZE];`
- L182 _groupshared_ `groupshared tsr_half4 SharedArray4[GROUP_SHARED_SIZE];`
- L183 _groupshared_ `groupshared tsr_half4 SharedArray5[GROUP_SHARED_SIZE];`
- L185 _groupshared_ `groupshared tsr_half4 SharedArray6[GROUP_SHARED_SIZE];`
- L186 _groupshared_ `groupshared tsr_half4 SharedArray7[GROUP_SHARED_SIZE];`
- L187 _groupshared_ `groupshared tsr_half4 SharedArray8[GROUP_SHARED_SIZE];`
- L188 _groupshared_ `groupshared tsr_half4 SharedArray9[GROUP_SHARED_SIZE];`
- L189 _groupshared_ `groupshared tsr_half4 SharedArray10[GROUP_SHARED_SIZE];`
- L190 _groupshared_ `groupshared tsr_half4 SharedArray11[GROUP_SHARED_SIZE];`

#### Functions (12)

- L197-204 _function_ `CALL_SITE_DEBUGLOC tsr_half3x2 med3(tsr_half3x2 a, tsr_half3x2 b, tsr_half3x2 c)` _[#if COMPILER_SUPPORTS_MED3]_
- L206-214 _function_ `CALL_SITE_DEBUGLOC tsr_half4x2 med3(tsr_half4x2 a, tsr_half4x2 b, tsr_half4x2 c)` _[#if COMPILER_SUPPORTS_MED3]_
- L220-227 _function_ `CALL_SITE_DEBUGLOC tsr_half3x2 WaveBroadcast(const FWaveBroadcastSettings Settings, tsr_half3x2 v)` _[#if PLATFORM_SUPPORTS_WAVE_BROADCAST]_
- L229-237 _function_ `CALL_SITE_DEBUGLOC tsr_half4x2 WaveBroadcast(const FWaveBroadcastSettings Settings, tsr_half4x2 v)` _[#if PLATFORM_SUPPORTS_WAVE_BROADCAST]_
- L244-253 _function_ `CALL_SITE_DEBUGLOC tsr_ushort2x2 Map8x8Tile2x2LaneDPV(uint GroupThreadIndex)`
- L255-261 _function_ `CALL_SITE_DEBUGLOC tsr_half3x2 GetColorChannel(tsr_half4x2 Color)`
- L263-401 _function_ `void ComputeInputKernelSamplePosition( tsr_short2x2 PixelPos, tsr_half2x2 dKO, const uint SampleId, int2 PixelPosMin, int2 PixelPosMax, out tsr_short2x2 SamplePixelPos, out tsr_half2x2 PixelOffset, out bool2 bIsDuplicatedSample, out bool2 bIsDisabledSample)`
- L403-408 _function_ `template<typename T> T BilinearSampleColorHistory(Texture2DArray<T> Texture, float3 SampleUV)`
- L437-566 _function_ `tsr_halfCx2 DownsampleSceneColor(tsr_halfCx2 SceneColor, uint LocalGroupThreadIndex, const uint2 XorButterFly)`
- L570-577 _function_ `float2 SampleDisplacementTexture(Texture2D<float2> DisplacementTexture, float2 TexCoord, float2 ViewportUV)` — Samples a displacement texture and crops any values beyond the texture's original bounds _[#if CONFIG_LENS_DISTORTION]_
- L579-587 _function_ `float2 ApplyDisplacementTextureOnScreenPos(Texture2D<float2> DisplacementTexture, float2 DistortedScreenPos, float2 ViewportScreenPos)` _[#if CONFIG_LENS_DISTORTION]_
- L592-626 _function_ `void FetchVelocityDilateBoundary( tsr_short2x2 InputPixelPos, out uint EncodedReprojectionBoundary[DPV_PIXEL_PER_LANE], out bool bApplyReprojectionBoundary)` _[#if CONFIG_REPROJECTION_FIELD]_

### `Shaders/Private/TemporalSuperResolution/TSRVisualize.usf` (Private)

- lines: 596; parse: all-branches
- includes: L3 `TSRColorSpace.ush`, L4 `TSRReprojectionField.ush`, L6 `../LensDistortion.ush` [TSR_SUPPORT_LENS_DISTORTION]

#### Macros (#define, 1)

- L12 `#define TILE_SIZE 8`

#### Entry points (1)

- L496-595 _entry_ `[numthreads(TILE_SIZE * TILE_SIZE, 1, 1)] void VisualizeCS( uint2 GroupId : SV_GroupID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FTSRVisualizeCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/TemporalSuperResolution.cpp:1517)

#### Structs / classes (3)

- L92-98 _struct_ **`FContext`** `struct FContext`
  - L94 _member_ `tsr_short2 OutputPixelPos;`
  - L95 _member_ `float2 ScreenPos;`
  - L96 _member_ `float2 InputUV;`
  - L97 _member_ `tsr_short2 InputPixelPos;`
- L110-120 _struct_ **`FReprojectionFieldSample`** `struct FReprojectionFieldSample`
  - L112 _member_ `bool bIsOffScreen;`
  - L113 _member_ `bool bIsFullDilate;`
  - L114 _member_ `bool bAntiAliasReprojectionField;`
  - L115 _member_ `tsr_short2 Offset;`
  - L116 _member_ `tsr_half2 Boundary;`
  - L117 _member_ `float2 Vector;`
  - L118 _member_ `float2 PrevScreenPos;`
  - L119 _member_ `tsr_half2x2 Jacobian;`
- L155-163 _struct_ **`FDecimateMaskSample`** `struct FDecimateMaskSample`
  - L157 _member_ `bool bIsOffScreen;`
  - L158 _member_ `bool bIsParallaxDisocclusion;`
  - L159 _member_ `bool bIsDisoccluded;`
  - L160 _member_ `bool bHasPixelAnimation;`
  - L161 _member_ `bool bDisableAnimationAA;`
  - L162 _member_ `bool bReprojectionHollFill;`

#### Global resources (textures / buffers / samplers) (20)

- L48 _resource_ `Texture2D<float2> PrevDistortingDisplacementTexture;`
- L49 _resource_ `Texture2D<float2> ResurrectedDistortingDisplacementTexture;`
- L50 _resource_ `Texture2D<float2> UndistortingDisplacementTexture;`
- L51 _resource_ `Texture2D<tsr_half3> InputTexture;`
- L52 _resource_ `Texture2D<tsr_half> InputMoireLumaTexture;`
- L53 _resource_ `Texture2D<tsr_half4> InputSceneTranslucencyTexture;`
- L54 _resource_ `Texture2D<tsr_half3> SceneColorTexture;`
- L55 _resource_ `Texture2D<float2> ClosestDepthTexture;`
- L56 _resource_ `Texture2D<uint> ReprojectionBoundaryTexture;`
- L57 _resource_ `Texture2D<uint> ReprojectionJacobianTexture;`
- L58 _resource_ `Texture2D<uint> ReprojectionVectorTexture;`
- L59 _resource_ `Texture2D<tsr_ushort> IsMovingMaskTexture;`
- L60 _resource_ `Texture2D<tsr_ushort> ThinGeometryTexture;`
- L61 _resource_ `Texture2D<tsr_half2> DecimateMaskTexture;`
- L62 _resource_ `Texture2D<tsr_half4> HistoryRejectionTexture;`
- L63 _resource_ `Texture2D<tsr_half4> MoireHistoryTexture;`
- L64 _resource_ `Texture2D<tsr_ushort> AntiAliasMaskTexture;`
- L65 _resource_ `Texture2D<tsr_half4> HistoryMetadataTexture;`
- L66 _resource_ `Texture2D<tsr_half3> ResurrectedHistoryColorTexture;`
- L68 _resource_ `RWTexture2D<tsr_half4> Output;`

#### Global parameters (uniforms) (18)

- L29 _parameter_ `FScreenTransform OutputPixelPosToScreenPos;`
- L30 _parameter_ `FScreenTransform ScreenPosToHistoryUV;`
- L31 _parameter_ `FScreenTransform ScreenPosToInputPixelPos;`
- L32 _parameter_ `FScreenTransform ScreenPosToInputUV;`
- L33 _parameter_ `FScreenTransform ScreenPosToMoireHistoryUV;`
- L34 _parameter_ `float2 MoireHistoryUVBilinearMin;`
- L35 _parameter_ `float2 MoireHistoryUVBilinearMax;`
- L36 _parameter_ `float4x4 ClipToResurrectionClip;`
- L37 _parameter_ `uint2 OutputViewRectMin;`
- L38 _parameter_ `uint2 OutputViewRectMax;`
- L39 _parameter_ `uint VisualizeId;`
- L40 _parameter_ `uint bCanResurrectHistory;`
- L41 _parameter_ `uint bCanSpatialAntiAlias;`
- L42 _parameter_ `uint bReprojectionField;`
- L43 _parameter_ `float MaxHistorySampleCount;`
- L44 _parameter_ `float OutputToHistoryResolutionFractionSquare;`
- L45 _parameter_ `float FlickeringFramePeriod;`
- L46 _parameter_ `float ExposureOffsetFactor;`

#### static variables (9)

- L17 _static_var_ `static tsr_half3 kWhite = tsr_half3(0.33, 0.33, 0.33);`
- L18 _static_var_ `static tsr_half3 kYellow = tsr_half3(1.00, 1.00, 0.10);`
- L19 _static_var_ `static tsr_half3 kRed = tsr_half3(1.00, 0.10, 0.10);`
- L20 _static_var_ `static tsr_half3 kOrange = tsr_half3(1.00, 0.75, 0.10);`
- L21 _static_var_ `static tsr_half3 kGreen = tsr_half3(0.10, 1.00, 0.10);`
- L22 _static_var_ `static tsr_half3 kBlue = tsr_half3(0.10, 0.10, 1.00);`
- L23 _static_var_ `static tsr_half3 kCyan = tsr_half3(0.10, 1.00, 1.00);`
- L24 _static_var_ `static tsr_half3 kPink = tsr_half3(1.00, 0.10, 0.50);`
- L73 _static_var_ `static float4 Debug;`

#### Functions (22)

- L79-82 _function_ `float2 ApplyLensDistortionOnScreenPos(Texture2D<float2> DisplacementTexture, float2 DestScreenPos)` _[#if !TSR_SUPPORT_LENS_DISTORTION]_
- L85-90 _function_ `tsr_half3 GrayScaleColor(tsr_half3 SceneColor)`
- L100-103 _function_ `tsr_half3 SampleTSROutputColor(FContext Ctx)`
- L105-108 _function_ `tsr_half3 SampleTSROutputGray(FContext Ctx)`
- L122-153 _function_ `FReprojectionFieldSample SampleReprojectionField(FContext Ctx)`
- L165-179 _function_ `FDecimateMaskSample SampleDecimateMask(FContext Ctx)`
- L184-205 _function_ `tsr_half3 DisplayHistorySampleCount(FContext Ctx)`
- L207-220 _function_ `tsr_half3 DisplayThinGeometry(FContext Ctx)`
- L222-232 _function_ `tsr_half3 DisplayHistoryRejection(FContext Ctx)`
- L234-244 _function_ `tsr_half3 DisplayHistoryClamp(FContext Ctx)`
- L246-255 _function_ `tsr_half3 DisplayParallaxDisocclusionMask(FContext Ctx)`
- L257-277 _function_ `tsr_half3 DisplayResurrectionMask(FContext Ctx)`
- L279-304 _function_ `tsr_half3 DisplayResurrectedColor(FContext Ctx)`
- L306-314 _function_ `tsr_half3 DisplaySpatialAntiAliasingMask(FContext Ctx)`
- L316-385 _function_ `tsr_half3 DisplayAntiFlickering(FContext Ctx)`
- L390-408 _function_ `tsr_half3 DisplayReprojectionFieldSummary(FContext Ctx)`
- L410-419 _function_ `tsr_half3 DisplayReprojectionFieldOffset(FContext Ctx)`
- L421-433 _function_ `tsr_half3 DisplayReprojectionOffsetCoverage(FContext Ctx)`
- L435-449 _function_ `tsr_half3 DisplayReprojectionNullJacobian(FContext Ctx)`
- L451-464 _function_ `tsr_half3 DisplayReprojectionClampedJacobian(FContext Ctx)`
- L466-478 _function_ `tsr_half3 DisplayReprojectionFieldDilatedJacobian(FContext Ctx)`
- L480-491 _function_ `tsr_half3 DisplayReprojectionFieldAA(FContext Ctx)`

### `Shaders/Private/TemporalSuperResolution/TSRWeightRelaxation.usf` (Private)

- lines: 264; parse: all-branches
- includes: L8 `TSRColorSpace.ush`, L10 `TSRThinGeometryCommon.ush`

#### Macros (#define, 4)

- L5 `#define CONFIG_TRANSLUCENCY_COVERAGE_BIT (DIM_REJECT_TRANSLUCENCY_DETECTION)`
- L14 `#define DEBUG_ARRAY_SIZE 8`
- L16 `#define DEBUG_DISABLE_PADDING 0`
- L18 `#define DEBUG_DIGESTABLE 0`

#### Entry points (1)

- L149-263 _entry_ `[numthreads(LANE_COUNT * WAVE_COUNT, 1, 1)] void WeightRelaxationCS( uint2 GroupId : SV_GroupID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FTSRWeightRelaxationCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/TemporalSuperResolution.cpp:1511)

#### Global resources (textures / buffers / samplers) (6)

- L36 _resource_ `Texture2D<tsr_half> CurrentCoverageTexture;`
- L37 _resource_ `Texture2D<tsr_half> InputMoireLumaTexture;`
- L38 _resource_ `Texture2D<tsr_halfC> InputTexture;`
- L39 _resource_ `Texture2D<tsr_half4> InputSceneTranslucencyTexture;`
- L41 _resource_ `RWTexture2DArray<tsr_ushort> R8Output;`
- L42 _resource_ `RWTexture2DArray<tsr_half> HistoryCoverageOutput;`

#### Global parameters (uniforms) (6)

- L29 _parameter_ `int TileOverscan;`
- L30 _parameter_ `int ThinGeometryTextureIndex;`
- L31 _parameter_ `float ErrorMultiplier;`
- L32 _parameter_ `float MaxRelaxationWeight;`
- L33 _parameter_ `float TranslucencyRejectionThreshold;`
- L34 _parameter_ `int bIntensityLineDetectionEnabled;`

#### static const (2)

- L23 _static_const_ `static const uint kDespillInput = LDS_DESPILL_THREAD_COUNT * LDS_DESPILL_OFFSET * 0;` _[#if CONFIG_LDS_DESPILL]_
- L24 _static_const_ `static const uint kDespillHistory = LDS_DESPILL_THREAD_COUNT * LDS_DESPILL_OFFSET * 1;` _[#if CONFIG_LDS_DESPILL]_

#### static variables (2)

- L45 _static_var_ `static uint2 GGroupId = 0;`
- L49 _static_var_ `static tsr_tensor_half4 Debug[DEBUG_ARRAY_SIZE];`

#### Functions (6)

- L53-65 _function_ `tsr_short2 ComputeElementPixelPos(const uint ElementIndex)`
- L67-78 _function_ `tsr_tensor_short2 ComputePixelPos()`
- L80-90 _function_ `tsr_short2 ComputeElementOutputPixelPos(const uint ElementIndex)`
- L92-103 _function_ `CALL_SITE_DEBUGLOC tsr_half ComputeRGBLuma(tsr_half3 Input)`
- L105-119 _function_ `CALL_SITE_DEBUGLOC tsr_tensor_half ComputeRGBLuma(tsr_tensor_half3 Input)`
- L121-142 _function_ `void FetchInput( tsr_tensor_short2 PixelPos, out tsr_tensor_half InputLuma, out tsr_tensor_half2 Translucency, out tsr_tensor_half HistoryRelaxationWeight, out tsr_tensor_bool IsClusterHoleRegion )`

#### Top-level macro invocations (1)

- L147 _macro_call_ `WAVESIZE(DIM_WAVE_SIZE)` _[#if COMPILER_SUPPORTS_WAVE_SIZE && DIM_WAVE_SIZE > 0]_
