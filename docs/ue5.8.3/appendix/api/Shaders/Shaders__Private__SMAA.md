# Shaders / Shaders/Private/SMAA

- files: 6; lines: 1696
- record kinds: cpp_binding=8, define=104, entry=8, function=28, include=7, macro_call=1, member=13, parameter=3, resource=13, struct=4

### `Shaders/Private/SMAA/SMAA.ush` (Private)

- lines: 1384; parse: all-branches

#### Macros (#define, 98)

- L307 `#define SMAA_THRESHOLD 0.15` _[#if defined(SMAA_PRESET_LOW)]_
- L308 `#define SMAA_MAX_SEARCH_STEPS 4` _[#if defined(SMAA_PRESET_LOW)]_
- L309 `#define SMAA_DISABLE_DIAG_DETECTION ` _[#if defined(SMAA_PRESET_LOW)]_
- L310 `#define SMAA_DISABLE_CORNER_DETECTION ` _[#if defined(SMAA_PRESET_LOW)]_
- L312 `#define SMAA_THRESHOLD 0.1` _[#if !(defined(SMAA_PRESET_LOW)) && defined(SMAA_PRESET_MEDIUM)]_
- L313 `#define SMAA_MAX_SEARCH_STEPS 8` _[#if !(defined(SMAA_PRESET_LOW)) && defined(SMAA_PRESET_MEDIUM)]_
- L314 `#define SMAA_DISABLE_DIAG_DETECTION ` _[#if !(defined(SMAA_PRESET_LOW)) && defined(SMAA_PRESET_MEDIUM)]_
- L315 `#define SMAA_DISABLE_CORNER_DETECTION ` _[#if !(defined(SMAA_PRESET_LOW)) && defined(SMAA_PRESET_MEDIUM)]_
- L317 `#define SMAA_THRESHOLD 0.1` _[#if !(defined(SMAA_PRESET_LOW)) && !(defined(SMAA_PRESET_MEDIUM)) && defined(SMAA_PRESET_HIGH)]_
- L318 `#define SMAA_MAX_SEARCH_STEPS 16` _[#if !(defined(SMAA_PRESET_LOW)) && !(defined(SMAA_PRESET_MEDIUM)) && defined(SMAA_PRESET_HIGH)]_
- L319 `#define SMAA_MAX_SEARCH_STEPS_DIAG 8` _[#if !(defined(SMAA_PRESET_LOW)) && !(defined(SMAA_PRESET_MEDIUM)) && defined(SMAA_PRESET_HIGH)]_
- L320 `#define SMAA_CORNER_ROUNDING 25` _[#if !(defined(SMAA_PRESET_LOW)) && !(defined(SMAA_PRESET_MEDIUM)) && defined(SMAA_PRESET_HIGH)]_
- L322 `#define SMAA_THRESHOLD 0.05` _[#if !(defined(SMAA_PRESET_LOW)) && !(defined(SMAA_PRESET_MEDIUM)) && !(defined(SMAA_PRESET_HIGH)) && defined(SMAA_PRESET_ULTRA)]_
- L323 `#define SMAA_MAX_SEARCH_STEPS 32` _[#if !(defined(SMAA_PRESET_LOW)) && !(defined(SMAA_PRESET_MEDIUM)) && !(defined(SMAA_PRESET_HIGH)) && defined(SMAA_PRESET_ULTRA)]_
- L324 `#define SMAA_MAX_SEARCH_STEPS_DIAG 16` _[#if !(defined(SMAA_PRESET_LOW)) && !(defined(SMAA_PRESET_MEDIUM)) && !(defined(SMAA_PRESET_HIGH)) && defined(SMAA_PRESET_ULTRA)]_
- L325 `#define SMAA_CORNER_ROUNDING 25` _[#if !(defined(SMAA_PRESET_LOW)) && !(defined(SMAA_PRESET_MEDIUM)) && !(defined(SMAA_PRESET_HIGH)) && defined(SMAA_PRESET_ULTRA)]_
- L344 `#define SMAA_THRESHOLD 0.1` _[#if !defined(SMAA_THRESHOLD)]_
- L353 `#define SMAA_DEPTH_THRESHOLD (0.1 * SMAA_THRESHOLD)` _[#if !defined(SMAA_DEPTH_THRESHOLD)]_
- L367 `#define SMAA_MAX_SEARCH_STEPS 16` _[#if !defined(SMAA_MAX_SEARCH_STEPS)]_
- L383 `#define SMAA_MAX_SEARCH_STEPS_DIAG 8` _[#if !defined(SMAA_MAX_SEARCH_STEPS_DIAG)]_
- L394 `#define SMAA_CORNER_ROUNDING 25` _[#if !defined(SMAA_CORNER_ROUNDING)]_
- L406 `#define SMAA_LOCAL_CONTRAST_ADAPTATION_FACTOR 2.0` _[#if !defined(SMAA_LOCAL_CONTRAST_ADAPTATION_FACTOR)]_
- L424 `#define SMAA_PREDICATION 0` _[#if !defined(SMAA_PREDICATION)]_
- L434 `#define SMAA_PREDICATION_THRESHOLD 0.01` _[#if !defined(SMAA_PREDICATION_THRESHOLD)]_
- L444 `#define SMAA_PREDICATION_SCALE 2.0` _[#if !defined(SMAA_PREDICATION_SCALE)]_
- L453 `#define SMAA_PREDICATION_STRENGTH 0.4` _[#if !defined(SMAA_PREDICATION_STRENGTH)]_
- L468 `#define SMAA_REPROJECTION 0` _[#if !defined(SMAA_REPROJECTION)]_
- L483 `#define SMAA_REPROJECTION_WEIGHT_SCALE 30.0` _[#if !defined(SMAA_REPROJECTION_WEIGHT_SCALE)]_
- L491 `#define SMAA_INCLUDE_VS 1` _[#if !defined(SMAA_INCLUDE_VS)]_
- L494 `#define SMAA_INCLUDE_PS 1` _[#if !defined(SMAA_INCLUDE_PS)]_
- L502 `#define SMAA_AREATEX_SELECT(sample) sample.ra` _[#if !defined(SMAA_AREATEX_SELECT) && defined(SMAA_HLSL_3)]_
- L504 `#define SMAA_AREATEX_SELECT(sample) sample.rg` _[#if !defined(SMAA_AREATEX_SELECT) && !(defined(SMAA_HLSL_3))]_
- L509 `#define SMAA_SEARCHTEX_SELECT(sample) sample.r` _[#if !defined(SMAA_SEARCHTEX_SELECT)]_
- L513 `#define SMAA_DECODE_VELOCITY(sample) sample.rg` _[#if !defined(SMAA_DECODE_VELOCITY)]_
- L519 `#define SMAA_AREATEX_MAX_DISTANCE 16`
- L520 `#define SMAA_AREATEX_MAX_DISTANCE_DIAG 20`
- L521 `#define SMAA_AREATEX_PIXEL_SIZE (1.0 / float2(160.0, 560.0))`
- L522 `#define SMAA_AREATEX_SUBTEX_SIZE (1.0 / 7.0)`
- L523 `#define SMAA_SEARCHTEX_SIZE float2(66.0, 33.0)`
- L524 `#define SMAA_SEARCHTEX_PACKED_SIZE float2(64.0, 16.0)`
- L525 `#define SMAA_CORNER_ROUNDING_NORM (float(SMAA_CORNER_ROUNDING) / 100.0)`
- L531 `#define SMAATexture2D(tex) sampler2D tex` _[#if defined(SMAA_HLSL_3)]_
- L532 `#define SMAATexturePass2D(tex) tex` _[#if defined(SMAA_HLSL_3)]_
- L533 `#define SMAASampleLevelZero(tex, coord) tex2Dlod(tex, float4(coord, 0.0, 0.0))` _[#if defined(SMAA_HLSL_3)]_
- L534 `#define SMAASampleLevelZeroPoint(tex, coord) tex2Dlod(tex, float4(coord, 0.0, 0.0))` _[#if defined(SMAA_HLSL_3)]_
- L535 `#define SMAASampleLevelZeroOffset(tex, coord, offset) tex2Dlod(tex, float4(coord + offset * SMAA_RT_METRICS.xy, 0.0, 0.0))` _[#if defined(SMAA_HLSL_3)]_
- L536 `#define SMAASample(tex, coord) tex2D(tex, coord)` _[#if defined(SMAA_HLSL_3)]_
- L537 `#define SMAASamplePoint(tex, coord) tex2D(tex, coord)` _[#if defined(SMAA_HLSL_3)]_
- L538 `#define SMAASampleOffset(tex, coord, offset) tex2D(tex, coord + offset * SMAA_RT_METRICS.xy)` _[#if defined(SMAA_HLSL_3)]_
- L539 `#define SMAA_FLATTEN [flatten]` _[#if defined(SMAA_HLSL_3)]_
- L540 `#define SMAA_BRANCH [branch]` _[#if defined(SMAA_HLSL_3)]_
- L545 `#define SMAATexture2D(tex) Texture2D tex` _[#if defined(SMAA_HLSL_4) \|\| defined(SMAA_HLSL_4_1)]_
- L546 `#define SMAATexturePass2D(tex) tex` _[#if defined(SMAA_HLSL_4) \|\| defined(SMAA_HLSL_4_1)]_
- L547 `#define SMAASampleLevelZero(tex, coord) tex.SampleLevel(LinearSampler, coord, 0)` _[#if defined(SMAA_HLSL_4) \|\| defined(SMAA_HLSL_4_1)]_
- L548 `#define SMAASampleLevelZeroPoint(tex, coord) tex.SampleLevel(PointSampler, coord, 0)` _[#if defined(SMAA_HLSL_4) \|\| defined(SMAA_HLSL_4_1)]_
- L549 `#define SMAASampleLevelZeroOffset(tex, coord, offset) tex.SampleLevel(LinearSampler, coord, 0, offset)` _[#if defined(SMAA_HLSL_4) \|\| defined(SMAA_HLSL_4_1)]_
- L550 `#define SMAASample(tex, coord) tex.Sample(LinearSampler, coord)` _[#if defined(SMAA_HLSL_4) \|\| defined(SMAA_HLSL_4_1)]_
- L551 `#define SMAASamplePoint(tex, coord) tex.Sample(PointSampler, coord)` _[#if defined(SMAA_HLSL_4) \|\| defined(SMAA_HLSL_4_1)]_
- L552 `#define SMAASampleOffset(tex, coord, offset) tex.Sample(LinearSampler, coord, offset)` _[#if defined(SMAA_HLSL_4) \|\| defined(SMAA_HLSL_4_1)]_
- L553 `#define SMAA_FLATTEN [flatten]` _[#if defined(SMAA_HLSL_4) \|\| defined(SMAA_HLSL_4_1)]_
- L554 `#define SMAA_BRANCH [branch]` _[#if defined(SMAA_HLSL_4) \|\| defined(SMAA_HLSL_4_1)]_
- L555 `#define SMAATexture2DMS2(tex) Texture2DMS<float4, 2> tex` _[#if defined(SMAA_HLSL_4) \|\| defined(SMAA_HLSL_4_1)]_
- L556 `#define SMAALoad(tex, pos, sample) tex.Load(pos, sample)` _[#if defined(SMAA_HLSL_4) \|\| defined(SMAA_HLSL_4_1)]_
- L558 `#define SMAAGather(tex, coord) tex.Gather(LinearSampler, coord, 0)` _[#if defined(SMAA_HLSL_4) \|\| defined(SMAA_HLSL_4_1) && defined(SMAA_HLSL_4_1)]_
- L562 `#define SMAATexture2D(tex) sampler2D tex` _[#if defined(SMAA_GLSL_3) \|\| defined(SMAA_GLSL_4)]_
- L563 `#define SMAATexturePass2D(tex) tex` _[#if defined(SMAA_GLSL_3) \|\| defined(SMAA_GLSL_4)]_
- L564 `#define SMAASampleLevelZero(tex, coord) textureLod(tex, coord, 0.0)` _[#if defined(SMAA_GLSL_3) \|\| defined(SMAA_GLSL_4)]_
- L565 `#define SMAASampleLevelZeroPoint(tex, coord) textureLod(tex, coord, 0.0)` _[#if defined(SMAA_GLSL_3) \|\| defined(SMAA_GLSL_4)]_
- L566 `#define SMAASampleLevelZeroOffset(tex, coord, offset) textureLodOffset(tex, coord, 0.0, offset)` _[#if defined(SMAA_GLSL_3) \|\| defined(SMAA_GLSL_4)]_
- L567 `#define SMAASample(tex, coord) texture(tex, coord)` _[#if defined(SMAA_GLSL_3) \|\| defined(SMAA_GLSL_4)]_
- L568 `#define SMAASamplePoint(tex, coord) texture(tex, coord)` _[#if defined(SMAA_GLSL_3) \|\| defined(SMAA_GLSL_4)]_
- L569 `#define SMAASampleOffset(tex, coord, offset) texture(tex, coord, offset)` _[#if defined(SMAA_GLSL_3) \|\| defined(SMAA_GLSL_4)]_
- L570 `#define SMAA_FLATTEN ` _[#if defined(SMAA_GLSL_3) \|\| defined(SMAA_GLSL_4)]_
- L571 `#define SMAA_BRANCH ` _[#if defined(SMAA_GLSL_3) \|\| defined(SMAA_GLSL_4)]_
- L572 `#define lerp(a, b, t) mix(a, b, t)` _[#if defined(SMAA_GLSL_3) \|\| defined(SMAA_GLSL_4)]_
- L573 `#define saturate(a) clamp(a, 0.0, 1.0)` _[#if defined(SMAA_GLSL_3) \|\| defined(SMAA_GLSL_4)]_
- L575 `#define mad(a, b, c) fma(a, b, c)` _[#if defined(SMAA_GLSL_3) \|\| defined(SMAA_GLSL_4) && defined(SMAA_GLSL_4)]_
- L576 `#define SMAAGather(tex, coord) textureGather(tex, coord)` _[#if defined(SMAA_GLSL_3) \|\| defined(SMAA_GLSL_4) && defined(SMAA_GLSL_4)]_
- L578 `#define mad(a, b, c) (a * b + c)` _[#if defined(SMAA_GLSL_3) \|\| defined(SMAA_GLSL_4) && !(defined(SMAA_GLSL_4))]_
- L580 `#define float2 vec2` _[#if defined(SMAA_GLSL_3) \|\| defined(SMAA_GLSL_4)]_
- L581 `#define float3 vec3` _[#if defined(SMAA_GLSL_3) \|\| defined(SMAA_GLSL_4)]_
- L582 `#define float4 vec4` _[#if defined(SMAA_GLSL_3) \|\| defined(SMAA_GLSL_4)]_
- L583 `#define int2 ivec2` _[#if defined(SMAA_GLSL_3) \|\| defined(SMAA_GLSL_4)]_
- L584 `#define int3 ivec3` _[#if defined(SMAA_GLSL_3) \|\| defined(SMAA_GLSL_4)]_
- L585 `#define int4 ivec4` _[#if defined(SMAA_GLSL_3) \|\| defined(SMAA_GLSL_4)]_
- L586 `#define bool2 bvec2` _[#if defined(SMAA_GLSL_3) \|\| defined(SMAA_GLSL_4)]_
- L587 `#define bool3 bvec3` _[#if defined(SMAA_GLSL_3) \|\| defined(SMAA_GLSL_4)]_
- L588 `#define bool4 bvec4` _[#if defined(SMAA_GLSL_3) \|\| defined(SMAA_GLSL_4)]_
- L593 `#define SMAATexture2DMMV(tex) Texture2DArray tex` _[#if MOBILE_MULTI_VIEW]_
- L594 `#define SMAASamplePointMMV(tex, coord, index) tex.Sample(PointSampler, float3(coord, index))` _[#if MOBILE_MULTI_VIEW]_
- L595 `#define SMAASampleLevelZeroMMV(tex, coord, index) tex.SampleLevel(LinearSampler, float3(coord, index), 0)` _[#if MOBILE_MULTI_VIEW]_
- L596 `#define SMAASampleLevelZeroOffsetMMV(tex, coord, offset, index) tex.SampleLevel(LinearSampler, float3(coord, index), 0, offset)` _[#if MOBILE_MULTI_VIEW]_
- L597 `#define SMAASampleMMV(tex, coord, index) tex.Sample(LinearSampler, float3(coord, index))` _[#if MOBILE_MULTI_VIEW]_
- L600 `#define SMAATexture2DMMV(tex) SMAATexture2D(tex)` _[#if !(MOBILE_MULTI_VIEW)]_
- L601 `#define SMAASamplePointMMV(tex, coord, index) SMAASamplePoint(tex, coord)` _[#if !(MOBILE_MULTI_VIEW)]_
- L602 `#define SMAASampleLevelZeroMMV(tex, coord, index) SMAASampleLevelZero(tex, coord)` _[#if !(MOBILE_MULTI_VIEW)]_
- L603 `#define SMAASampleLevelZeroOffsetMMV(tex, coord, offset, index) SMAASampleLevelZeroOffset(tex, coord, offset)` _[#if !(MOBILE_MULTI_VIEW)]_
- L604 `#define SMAASampleMMV(tex, coord, index) SMAASample(tex, coord)` _[#if !(MOBILE_MULTI_VIEW)]_

#### Global resources (textures / buffers / samplers) (2)

- L543 _resource_ `SamplerState LinearSampler;` — { Filter = MIN_MAG_LINEAR_MIP_POINT; AddressU = Clamp; AddressV = Clamp; }; _[#if defined(SMAA_HLSL_4) \|\| defined(SMAA_HLSL_4_1)]_
- L544 _resource_ `SamplerState PointSampler;` — { Filter = MIN_MAG_MIP_POINT; AddressU = Clamp; AddressV = Clamp; }; _[#if defined(SMAA_HLSL_4) \|\| defined(SMAA_HLSL_4_1)]_

#### Functions (28)

- L617-628 _function_ `float3 SMAAGatherNeighbours(float2 texcoord, float4 offset[3], SMAATexture2D(tex))` — Gathers current pixel, and the top-left neighbors.
- L633-640 _function_ `float2 SMAACalculatePredicatedThreshold(float2 texcoord, float4 offset[3], SMAATexture2D(predicationTex))` — Adjusts the threshold by means of predication.
- L645-648 _function_ `void SMAAMovc(bool2 cond, inout float2 variable, float2 value)` — Conditional move:
- L650-653 _function_ `void SMAAMovc(bool4 cond, inout float4 variable, float4 value)`
- L663-668 _function_ `void SMAAEdgeDetectionVS(float2 texcoord, out float4 offset[3])` — Edge Detection Vertex Shader _[#if SMAA_INCLUDE_VS]_
- L673-686 _function_ `void SMAABlendingWeightCalculationVS(float2 texcoord, out float2 pixcoord, out float4 offset[3])` — Blend Weight Calculation Vertex Shader _[#if SMAA_INCLUDE_VS]_
- L691-694 _function_ `void SMAANeighborhoodBlendingVS(float2 texcoord, out float4 offset)` — Neighborhood Blending Vertex Shader _[#if SMAA_INCLUDE_VS]_
- L707-759 _function_ `float2 SMAALumaEdgeDetectionPS(float2 texcoord, float4 offset[3], SMAATexture2DMMV(colorTex), SMAATexture2D(predicationTex) int ArrayIndex )` — Luma Edge Detection IMPORTANT NOTICE: luma edge detection requires gamma-corrected colors, and thus 'colorTex' should be a non-sRGB texture. _[#if SMAA_INCLUDE_PS]_
- L767-830 _function_ `float2 SMAAColorEdgeDetectionPS(float2 texcoord, float4 offset[3], SMAATexture2DMMV(colorTex), SMAATexture2D(predicationTex), int ArrayIndex )` — Color Edge Detection IMPORTANT NOTICE: color edge detection requires gamma-corrected colors, and thus 'colorTex' should be a non-sRGB texture. _[#if SMAA_INCLUDE_PS]_
- L835-846 _function_ `float2 SMAADepthEdgeDetectionPS(float2 texcoord, float4 offset[3], SMAATexture2D(depthTex))` — Depth Edge Detection _[#if SMAA_INCLUDE_PS]_
- L856-872 _function_ `float2 SMAADecodeDiagBilinearAccess(float2 e)` — Allows to decode two binary values from a bilinear-filtered access. _[#if SMAA_INCLUDE_PS && !defined(SMAA_DISABLE_DIAG_DETECTION)]_
- L874-877 _function_ `float4 SMAADecodeDiagBilinearAccess(float4 e)` _[#if SMAA_INCLUDE_PS && !defined(SMAA_DISABLE_DIAG_DETECTION)]_
- L882-892 _function_ `float2 SMAASearchDiag1(SMAATexture2DMMV(edgesTex), float2 texcoord, float2 dir, out float2 e, int ArrayIndex)` — These functions allows to perform diagonal pattern searches. _[#if SMAA_INCLUDE_PS && !defined(SMAA_DISABLE_DIAG_DETECTION)]_
- L894-914 _function_ `float2 SMAASearchDiag2(SMAATexture2DMMV(edgesTex), float2 texcoord, float2 dir, out float2 e, int ArrayIndex)` _[#if SMAA_INCLUDE_PS && !defined(SMAA_DISABLE_DIAG_DETECTION)]_
- L920-934 _function_ `float2 SMAAAreaDiag(SMAATexture2D(areaTex), float2 dist, float2 e, float offset)` — Similar to SMAAArea, this calculates the area corresponding to a certain diagonal distance and crossing edges 'e'. _[#if SMAA_INCLUDE_PS && !defined(SMAA_DISABLE_DIAG_DETECTION)]_
- L939-1005 _function_ `float2 SMAACalculateDiagWeights(SMAATexture2DMMV(edgesTex), SMAATexture2D(areaTex), float2 texcoord, float2 e, float4 subsampleIndices, int ArrayIndex)` — This searches for diagonal patterns and returns the corresponding weights. _[#if SMAA_INCLUDE_PS && !defined(SMAA_DISABLE_DIAG_DETECTION)]_
- L1017-1034 _function_ `float SMAASearchLength(SMAATexture2D(searchTex), float2 e, float offset)` — This allows to determine how much length should we add in the last step of the searches. It takes the bilinearly interpolated edge (see @PSEUDO_GATHER4), and adds 0, 1 or 2, depending on which edges and crossing edges are active. _[#if SMAA_INCLUDE_PS]_
- L1039-1069 _function_ `float SMAASearchXLeft(SMAATexture2DMMV(edgesTex), SMAATexture2D(searchTex), float2 texcoord, float end, int ArrayIndex)` — Horizontal/vertical search functions for the 2nd pass. _[#if SMAA_INCLUDE_PS]_
- L1071-1081 _function_ `float SMAASearchXRight(SMAATexture2DMMV(edgesTex), SMAATexture2D(searchTex), float2 texcoord, float end, int ArrayIndex)` _[#if SMAA_INCLUDE_PS]_
- L1083-1093 _function_ `float SMAASearchYUp(SMAATexture2DMMV(edgesTex), SMAATexture2D(searchTex), float2 texcoord, float end, int ArrayIndex)` _[#if SMAA_INCLUDE_PS]_
- L1095-1105 _function_ `float SMAASearchYDown(SMAATexture2DMMV(edgesTex), SMAATexture2D(searchTex), float2 texcoord, float end, int ArrayIndex)` _[#if SMAA_INCLUDE_PS]_
- L1111-1123 _function_ `float2 SMAAArea(SMAATexture2D(areaTex), float2 dist, float e1, float e2, float offset)` — Ok, we have the distance and both crossing edges. So, what are the areas at each side of current edge? _[#if SMAA_INCLUDE_PS]_
- L1128-1143 _function_ `void SMAADetectHorizontalCornerPattern(SMAATexture2DMMV(edgesTex), inout float2 weights, float4 texcoord, float2 d, int ArrayIndex)` _[#if SMAA_INCLUDE_PS]_
- L1145-1160 _function_ `void SMAADetectVerticalCornerPattern(SMAATexture2DMMV(edgesTex), inout float2 weights, float4 texcoord, float2 d, int ArrayIndex)` _[#if SMAA_INCLUDE_PS]_
- L1165-1268 _function_ `float4 SMAABlendingWeightCalculationPS(float2 texcoord, float2 pixcoord, float4 offset[3], SMAATexture2DMMV(edgesTex), SMAATexture2D(areaTex), SMAATexture2D(searchTex), float4 subsampleIndices, int ArrayIndex)` _[#if SMAA_INCLUDE_PS]_
- L1273-1330 _function_ `float4 SMAANeighborhoodBlendingPS(float2 texcoord, float4 offset, SMAATexture2DMMV(colorTex), SMAATexture2DMMV(blendTex) , SMAATexture2D(velocityTex) , int ArrayIndex )` _[#if SMAA_INCLUDE_PS]_
- L1335-1365 _function_ `float4 SMAAResolvePS(float2 texcoord, SMAATexture2D(currentColorTex), SMAATexture2D(previousColorTex) , SMAATexture2D(velocityTex) )` _[#if SMAA_INCLUDE_PS]_
- L1371-1379 _function_ `void SMAASeparatePS(float4 position, float2 texcoord, out float4 target0, out float4 target1, SMAATexture2DMS2(colorTexMS))` _[#if SMAA_INCLUDE_PS && defined(SMAALoad)]_

### `Shaders/Private/SMAA/SMAABlendingWeightCalculationShader.usf` (Private)

- lines: 55; parse: all-branches
- includes: L3 `SMAACommon.ush`

#### Entry points (2)

- L21-34 _entry_ `void MainVS( float2 InPosition : ATTRIBUTE0, float2 InUV : ATTRIBUTE1, in FStereoVSInput StereoInput, out FStereoVSOutput StereoOutput, out FSMAABlendingWeightCalculationVertexOutput Output )` — stage: **vertex (from C++ binding)** — C++: `FSMAABlendingWeightCalculationVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/SubpixelMorphologicalAA.cpp:118) _[#if defined(MainVS)]_
- L44-52 _entry_ `void MainPS( FSMAABlendingWeightCalculationVertexOutput Input, in FStereoPSInput StereoInput, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FSMAABlendingWeightCalculationPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/SubpixelMorphologicalAA.cpp:120) _[#if defined(MainPS)]_

#### Structs / classes (1)

- L5-11 _struct_ **`FSMAABlendingWeightCalculationVertexOutput`** `struct FSMAABlendingWeightCalculationVertexOutput`
  - L7 _member_ `noperspective float2 UV : TEXCOORD0;`
  - L8 _member_ `float4 Offset[3] : TEXCOORD1;`
  - L9 _member_ `float2 Pixcoord : TEXCOORD4;`
  - L10 _member_ `float4 Position : SV_POSITION;`

#### Global resources (textures / buffers / samplers) (2)

- L13 _resource_ `Texture2D AreaTex;`
- L14 _resource_ `Texture2D SearchTex;`

### `Shaders/Private/SMAA/SMAACommon.ush` (Private)

- lines: 31; parse: all-branches
- includes: L3 `../Common.ush`, L4 `../ScreenPass.ush`, L29 `SMAA.ush`

#### Macros (#define, 6)

- L18 `#define SMAA_PRESET_LOW ` _[#if SMAA_QUALITY == 0]_
- L20 `#define SMAA_PRESET_MEDIUM ` _[#if !(SMAA_QUALITY == 0) && SMAA_QUALITY == 1]_
- L22 `#define SMAA_PRESET_HIGH ` _[#if !(SMAA_QUALITY == 0) && !(SMAA_QUALITY == 1) && SMAA_QUALITY == 2]_
- L24 `#define SMAA_PRESET_ULTRA ` _[#if !(SMAA_QUALITY == 0) && !(SMAA_QUALITY == 1) && !(SMAA_QUALITY == 2) && SMAA_QUALITY == 3]_
- L27 `#define SMAA_HLSL_4 `
- L28 `#define SMAA_RT_METRICS RTMetrics`

#### Global resources (textures / buffers / samplers) (3)

- L9 _resource_ `Texture2DArray Input_Texture;` _[#if MOBILE_MULTI_VIEW]_
- L11 _resource_ `Texture2D Input_Texture;` _[#if !(MOBILE_MULTI_VIEW)]_
- L13 _resource_ `SamplerState Input_Sampler;`

#### Global parameters (uniforms) (1)

- L15 _parameter_ `float4 RTMetrics;`

#### Top-level macro invocations (1)

- L6 _macro_call_ `SCREEN_PASS_TEXTURE_VIEWPORT(Input)`

### `Shaders/Private/SMAA/SMAADebugVisualization.usf` (Private)

- lines: 103; parse: all-branches
- includes: L3 `SMAACommon.ush`

#### Entry points (2)

- L27-40 _entry_ `void MainVS( float2 InPosition : ATTRIBUTE0, float2 InUV : ATTRIBUTE1, in FStereoVSInput StereoInput, out FStereoVSOutput StereoOutput, out FSMAADebugVisualizationVertexOutput Output )` — stage: **vertex (from C++ binding)** — C++: `FSMAADebugVisualizationVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/SubpixelMorphologicalAA.cpp:179) _[#if defined(MainVS)]_
- L50-100 _entry_ `void MainPS( FSMAADebugVisualizationVertexOutput Input, in FStereoPSInput StereoInput, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FSMAADebugVisualizationPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/SubpixelMorphologicalAA.cpp:181) _[#if defined(MainPS)]_

#### Structs / classes (1)

- L5-10 _struct_ **`FSMAADebugVisualizationVertexOutput`** `struct FSMAADebugVisualizationVertexOutput`
  - L7 _member_ `noperspective float2 UV : TEXCOORD0;`
  - L8 _member_ `float4 Offset : TEXCOORD1;`
  - L9 _member_ `float4 Position : SV_POSITION;`

#### Global resources (textures / buffers / samplers) (4)

- L13 _resource_ `Texture2DArray EdgeTex;` _[#if MOBILE_MULTI_VIEW]_
- L14 _resource_ `Texture2DArray BlendTex;` _[#if MOBILE_MULTI_VIEW]_
- L16 _resource_ `Texture2D EdgeTex;` _[#if !(MOBILE_MULTI_VIEW)]_
- L17 _resource_ `Texture2D BlendTex;` _[#if !(MOBILE_MULTI_VIEW)]_

#### Global parameters (uniforms) (1)

- L20 _parameter_ `int DebugMode;`

### `Shaders/Private/SMAA/SMAAEdgeDetectionShader.usf` (Private)

- lines: 61; parse: all-branches
- includes: L3 `SMAACommon.ush`

#### Entry points (2)

- L19-32 _entry_ `void MainVS( float2 InPosition : ATTRIBUTE0, float2 InUV : ATTRIBUTE1, in FStereoVSInput StereoInput, out FStereoVSOutput StereoOutput, out FSMAAEdgeDetectionScreenVertexOutput Output )` — stage: **vertex (from C++ binding)** — C++: `FSMAAEdgeDetectionVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/SubpixelMorphologicalAA.cpp:82) _[#if defined(MainVS)]_
- L42-58 _entry_ `void MainPS( FSMAAEdgeDetectionScreenVertexOutput Input, in FStereoPSInput StereoInput, out float2 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FSMAAEdgeDetectionPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/SubpixelMorphologicalAA.cpp:84) _[#if defined(MainPS)]_

#### Structs / classes (1)

- L5-10 _struct_ **`FSMAAEdgeDetectionScreenVertexOutput`** `struct FSMAAEdgeDetectionScreenVertexOutput`
  - L7 _member_ `noperspective float2 UV : TEXCOORD0;`
  - L8 _member_ `float4 Offset[3] : TEXCOORD1;`
  - L9 _member_ `float4 Position : SV_POSITION;`

#### Global parameters (uniforms) (1)

- L12 _parameter_ `int EdgeMode;`

### `Shaders/Private/SMAA/SMAANeighborhoodBlendingShader.usf` (Private)

- lines: 62; parse: all-branches
- includes: L3 `SMAACommon.ush`

#### Entry points (2)

- L23-36 _entry_ `void MainVS( float2 InPosition : ATTRIBUTE0, float2 InUV : ATTRIBUTE1, in FStereoVSInput StereoInput, out FStereoVSOutput StereoOutput, out FSMAANeighborhoodBlendingScreenVertexOutput Output )` — stage: **vertex (from C++ binding)** — C++: `FSMAANeighborhoodBlendingVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/SubpixelMorphologicalAA.cpp:149) _[#if defined(MainVS)]_
- L46-59 _entry_ `void MainPS( FSMAANeighborhoodBlendingScreenVertexOutput Input, in FStereoPSInput StereoInput, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FSMAANeighborhoodBlendingPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/SubpixelMorphologicalAA.cpp:151) _[#if defined(MainPS)]_

#### Structs / classes (1)

- L5-10 _struct_ **`FSMAANeighborhoodBlendingScreenVertexOutput`** `struct FSMAANeighborhoodBlendingScreenVertexOutput`
  - L7 _member_ `noperspective float2 UV : TEXCOORD0;`
  - L8 _member_ `float4 Offset : TEXCOORD1;`
  - L9 _member_ `float4 Position : SV_POSITION;`

#### Global resources (textures / buffers / samplers) (2)

- L13 _resource_ `Texture2DArray BlendTex;` _[#if MOBILE_MULTI_VIEW]_
- L15 _resource_ `Texture2D BlendTex;` _[#if !(MOBILE_MULTI_VIEW)]_
