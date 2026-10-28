# Shaders / Plugins/Experimental/NFORDenoise/Shaders

- files: 3; lines: 2483
- record kinds: cpp_binding=25, define=103, entry=22, function=60, groupshared=1, include=7, member=9, parameter=47, resource=53, struct=7

### `Plugins/Experimental/NFORDenoise/Shaders/NFORDenoise.usf` (Other)

- lines: 1719; parse: per-group
- includes: L3 `/Engine/Public/Platform.ush`, L4 `/Engine/Private/Common.ush`, L5 `/Engine/Private/ScreenPass.ush`, L6 `NFORRegressionCommon.ush`, L1072 `/Engine/Private/DoubleFloat.ush`, L1348 `NFORRegression.ush`

#### Macros (#define, 79)

- L9 `#define SOURCE_CHANNEL_COUNT 4` _[#if !defined(SOURCE_CHANNEL_COUNT)]_
- L13 `#define THREAD_GROUP_SIZE 1` _[#if !COMPUTESHADER]_
- L17 `#define TPixelValue float` _[#if SOURCE_CHANNEL_COUNT == 1]_
- L19 `#define TPixelValue float2` _[#if !(SOURCE_CHANNEL_COUNT == 1) && SOURCE_CHANNEL_COUNT == 2]_
- L21 `#define TPixelValue float3` _[#if !(SOURCE_CHANNEL_COUNT == 1) && !(SOURCE_CHANNEL_COUNT == 2) && SOURCE_CHANNEL_COUNT == 3]_
- L23 `#define TPixelValue float4` _[#if !(SOURCE_CHANNEL_COUNT == 1) && !(SOURCE_CHANNEL_COUNT == 2) && !(SOURCE_CHANNEL_COUNT == 3) && SOURCE_CHANNEL_COUNT == 4]_
- L26 `#define IMAGE_VARINCE_NORMAL 0`
- L27 `#define IMAGE_VARIANCE_GREYSCALE 1`
- L28 `#define IMAGE_VARIANCE_COLORED 2`
- L31 `#define IMAGE_VARIANCE_TYPE IMAGE_VARIANCE_GREYSCALE` _[#if !defined(IMAGE_VARIANCE_TYPE)]_
- L34 `#define PRE_ALBEDO_DIVIDE_DISABLED 0`
- L35 `#define PRE_ALBEDO_DIVIDE_EACH 1`
- L36 `#define PRE_ALBEDO_DIVIDE_FINAL 2`
- L39 `#define PRE_ALBEDO_DIVIDE PRE_ALBEDO_DIVIDE_DISABLED` _[#if !defined(PRE_ALBEDO_DIVIDE)]_
- L43 `#define APPEND_CONSTANT_DIMENSION_TO_X 0` _[#if !defined(APPEND_CONSTANT_DIMENSION_TO_X)]_
- L47 `#define NONLOCALMEAN_SEPARATE_SOURCE 0` _[#if !defined(NONLOCALMEAN_SEPARATE_SOURCE)]_
- L50 `#define NONLOCALMEAN_PATCHONLY 0`
- L51 `#define NONLOCALMEAN_DISTACNE_PATCH 1`
- L52 `#define NONLOCALMEAN_WEIGHT_TYPE NONLOCALMEAN_PATCHONLY`
- L54 `#define NONLOCALMEAN_SEPERABLE_FILTER_HORIZONTAL 0`
- L55 `#define NONLOCALMEAN_SEPERABLE_FILTER_VERTICAL 1`
- L58 `#define NONLOCALMEAN_SEPRERABLE_PASS NONLOCALMEAN_SEPERABLE_FILTER_HORIZONTAL` _[#if !defined(NONLOCALMEAN_SEPRERABLE_PASS)]_
- L61 `#define NONLOCALMEAN_ATLAS_ONE_SYMMETRIC_PAIR 0`
- L62 `#define NONLOCALMEAN_ATLAS_TWO_SYMMETRIC_PAIR 1`
- L65 `#define NONLOCALMEAN_ATLAS_TYPE NONLOCALMEAN_ATLAS_TWO_SYMMETRIC_PAIR` _[#if !defined(NONLOCALMEAN_ATLAS_TYPE)]_
- L69 `#define TAtlasValueType float2` _[#if NONLOCALMEAN_ATLAS_TYPE == NONLOCALMEAN_ATLAS_ONE_SYMMETRIC_PAIR]_
- L71 `#define TAtlasValueType float4` _[#if !(NONLOCALMEAN_ATLAS_TYPE == NONLOCALMEAN_ATLAS_ONE_SYMMETRIC_PAIR) && NONLOCALMEAN_ATLAS_TYPE == NONLOCALMEAN_ATLAS_TWO_SYMMETRIC_PAIR]_
- L77 `#define BUFFER_PASS_THROUGH 0` _[#if !defined(BUFFER_PASS_THROUGH)]_
- L80 `#define NONLOCALMEAN_ATLAS_SYMMETRIC_PAIR_COUNT (NONLOCALMEAN_ATLAS_TYPE+1)`
- L82 `#define NLM_WEIGHTLAYOUT_NONE 0`
- L83 `#define NLM_WEIGHTLAYOUT_NUM_OF_WEIGHTS_PER_PIXELxWxH 1`
- L84 `#define NLM_WEIGHTLAYOUT_WxHxNUM_OF_WEIGHTS_PER_PIXEL 2`
- L85 `#define NLM_WEIGHTLAYOUT_4xWxHxNUM_OF_WEIGHTS_BY_4 3`
- L88 `#define NLM_WEIGHTLAYOUT NLM_WEIGHTLAYOUT_NONE` _[#if !defined(NLM_WEIGHTLAYOUT)]_
- L92 `#define TWeightReadType float4` _[#if NLM_WEIGHTLAYOUT == NLM_WEIGHTLAYOUT_4xWxHxNUM_OF_WEIGHTS_BY_4]_
- L93 `#define WEIGHT_PIXEL_INCREMENT 4` _[#if NLM_WEIGHTLAYOUT == NLM_WEIGHTLAYOUT_4xWxHxNUM_OF_WEIGHTS_BY_4]_
- L95 `#define TWeightReadType float` _[#if !(NLM_WEIGHTLAYOUT == NLM_WEIGHTLAYOUT_4xWxHxNUM_OF_WEIGHTS_BY_4)]_
- L96 `#define WEIGHT_PIXEL_INCREMENT 1` _[#if !(NLM_WEIGHTLAYOUT == NLM_WEIGHTLAYOUT_4xWxHxNUM_OF_WEIGHTS_BY_4)]_
- L100 `#define NUM_FEATURE 0` _[#if !defined(NUM_FEATURE)]_
- L104 `#define SMALL_MATRIX_OPTIMIZE 0` _[#if !defined(SMALL_MATRIX_OPTIMIZE)]_
- L109 `#define USE_SAMPLING_STEP 0` _[#if !defined(USE_SAMPLING_STEP)]_
- L112 `#define SAMPLING_TYPE_INCREMENTAL 0`
- L113 `#define SAMPLING_TYPE_FOCUS_CURRENT_FRAME 1`
- L115 `#define SAMPLING_TYPE SAMPLING_TYPE_FOCUS_CURRENT_FRAME`
- L118 `#define WEIGHTED_MULTIPLICATION_QUADRATIC 0`
- L119 `#define WEIGHTED_MULTIPLICATION_GENERALIZED 1`
- L122 `#define WEIGHTED_MULTIPLICATION_TYPE WEIGHTED_MULTIPLICATION_QUADRATIC` _[#if !defined(WEIGHTED_MULTIPLICATION_TYPE)]_
- L126 `#define INPUT_MATRIX_TYPE_SUCCESS 0`
- L127 `#define INPUT_MATRIX_TYPE_FAIL 1`
- L130 `#define INPUT_MATRIX_TYPE INPUT_MATRIX_TYPE_SUCCESS` _[#if !defined(INPUT_MATRIX_TYPE)]_
- L133 `#define OUTPUT_MATRIX_TYPE_SUCCESS 0`
- L134 `#define OUTPUT_MATRIX_TYPE_FAIL 1`
- L137 `#define OUTPUT_INDICES 0` _[#if !defined(OUTPUT_INDICES)]_
- L141 `#define RECONSTRUCTION_TYPE_SCATTER 0`
- L142 `#define RECONSTRUCTION_TYPE_GATHER 1`
- L145 `#define RECONSTRUCTION_TYPE RECONSTRUCTION_TYPE_SCATTER` _[#if !defined(RECONSTRUCTION_TYPE)]_
- L148 `#define RADIANCE_PREPROCESS_SCALE_FACTOR 0.1f`
- L149 `#define RADIANCE_POSTPROCESS_INVERSE_SCALE_FACTOR (1/RADIANCE_PREPROCESS_SCALE_FACTOR);`
- L154 `#define TEXTURE_OPS_MULTIPLY 0`
- L155 `#define TEXTURE_OPS_DIVIDE 1`
- L156 `#define TEXTURE_OPS_ADD_CONSTANT 2`
- L157 `#define TEXTURE_OPS_ACCUMULATE 3`
- L160 `#define TEXTURE_OPS TEXTURE_OPS_MULTIPLY` _[#if !defined(TEXTURE_OPS)]_
- L163 `#define TEXTURE_COPY_TARGET_SINGLE_CHANNEL 0`
- L164 `#define TEXTURE_COPY_SOURCE_SINGLE_CHANNEL 1`
- L167 `#define TEXTURE_COPY_TYPE TEXTURE_COPY_TARGET_SINGLE_CHANNEL` _[#if !defined(TEXTURE_COPY_TYPE)]_
- L171 `#define ACCUMULATE_BY_MASK 0` _[#if !defined(ACCUMULATE_BY_MASK)]_
- L306 `#define TImageVariance float4`
- L434 `#define TargetImage Image` _[#if !(NONLOCALMEAN_SEPARATE_SOURCE)]_
- L435 `#define TargetVariance Variance` _[#if !(NONLOCALMEAN_SEPARATE_SOURCE)]_
- L721 `#define DISTANCE_QUERY_COUNT ((NONLOCALMEAN_SEPARATE_SOURCE+1)*NONLOCALMEAN_ATLAS_SYMMETRIC_PAIR_COUNT)`
- L988 `#define YDim XDim` _[#if !(WEIGHTED_MULTIPLICATION_TYPE == WEIGHTED_MULTIPLICATION_GENERALIZED)]_
- L1133 `#define MATRIX_CACHE_SIZE (((NUM_FEATURE + APPEND_CONSTANT_DIMENSION_TO_X) * (NUM_FEATURE + APPEND_CONSTANT_DIMENSION_TO_X) + 1) / 2)` _[#if WEIGHTED_MULTIPLICATION_TYPE == WEIGHTED_MULTIPLICATION_QUADRATIC]_
- L1135 `#define MATRIX_CACHE_SIZE ((NUM_FEATURE + APPEND_CONSTANT_DIMENSION_TO_X)*3)` _[#if !(WEIGHTED_MULTIPLICATION_TYPE == WEIGHTED_MULTIPLICATION_QUADRATIC) && WEIGHTED_MULTIPLICATION_TYPE == WEIGHTED_MULTIPLICATION_GENERALIZED]_
- L1334 `#define NUM_NEWTON_SCHULTZ_ITERATIONS 20` _[#if LINEAR_SOLVER_TYPE == LINEAR_SOLVER_TYPE_NEWTON_SCHULZ]_
- L1336 `#define NEWTON_INITIAL_GUESS_TYPE INITIAL_GUESS_EUCLIDEAN_NORM` _[#if LINEAR_SOLVER_TYPE == LINEAR_SOLVER_TYPE_NEWTON_SCHULZ]_
- L1341 `#define NUM_NEWTON_SCHULTZ_ITERATIONS 3` _[#if !(LINEAR_SOLVER_TYPE == LINEAR_SOLVER_TYPE_NEWTON_SCHULZ) && LINEAR_SOLVER_TYPE == LINEAR_SOLVER_TYPE_NEWTON_CHOLESKY]_
- L1343 `#define NEWTON_INITIAL_GUESS_TYPE INITIAL_GUESS_INVERSE_CHOLESKY_DECOMPOSITION` _[#if !(LINEAR_SOLVER_TYPE == LINEAR_SOLVER_TYPE_NEWTON_SCHULZ) && LINEAR_SOLVER_TYPE == LINEAR_SOLVER_TYPE_NEWTON_CHOLESKY]_
- L1347 `#define MATRIX_DIM NUM_FEATURE`

#### Entry points (22)

- L224-258 _entry_ `[numthreads(THREAD_GROUP_SIZE, THREAD_GROUP_SIZE, 1)] void TextureOperationCS(in const uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `FTextureMultiplyCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NFORDenoise/Source/NFORDenoise/Private/NFORDenoiseCS.cpp:670) — C++: `FTextureDivideCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NFORDenoise/Source/NFORDenoise/Private/NFORDenoiseCS.cpp:671) — C++: `FTextureAccumulateConstantCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NFORDenoise/Source/NFORDenoise/Private/NFORDenoiseCS.cpp:672) — C++: `FTextureAccumulateCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NFORDenoise/Source/NFORDenoise/Private/NFORDenoiseCS.cpp:673)
- L266-270 _entry_ `TPixelValue CopyTexturePS(float4 SvPosition : SV_POSITION) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FCopyTexturePS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NFORDenoise/Source/NFORDenoise/Private/NFORDenoiseCS.cpp:674)
- L280-299 _entry_ `[numthreads(THREAD_GROUP_SIZE, THREAD_GROUP_SIZE, 1)] void CopyTextureSingleChannelCS(in const uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `FCopyTextureSingleChannelCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NFORDenoise/Source/NFORDenoise/Private/NFORDenoiseCS.cpp:675)
- L335-356 _entry_ `[numthreads(THREAD_GROUP_SIZE, THREAD_GROUP_SIZE, 1)] void ClassifyPreAlbedoDivideMaskIdCS(in const uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `FClassifyPreAlbedoDivideMaskIdCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NFORDenoise/Source/NFORDenoise/Private/NFORDenoiseCS.cpp:679)
- L361-374 _entry_ `[numthreads(THREAD_GROUP_SIZE, THREAD_GROUP_SIZE, 1)] void NormalizeRadianceVarianceByAlbedoCS(in const uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `FNormalizeRadianceVarianceByAlbedoCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NFORDenoise/Source/NFORDenoise/Private/NFORDenoiseCS.cpp:680)
- L381-408 _entry_ `[numthreads(THREAD_GROUP_SIZE, THREAD_GROUP_SIZE, 1)] void AdjustFeatureRangeCS(in const uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `FAdjustFeatureRangeCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NFORDenoise/Source/NFORDenoise/Private/NFORDenoiseCS.cpp:681)
- L600-660 _entry_ `[numthreads(THREAD_GROUP_SIZE, THREAD_GROUP_SIZE, 1)] void NonLocalMeanFilteringCS(in const uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `FNonLocalMeanFilteringCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NFORDenoise/Source/NFORDenoise/Private/NFORDenoiseCS.cpp:685)
- L666-691 _entry_ `[numthreads(THREAD_GROUP_SIZE, THREAD_GROUP_SIZE, 1)] void NonLocalMeanWeightsCS(in const uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `FNonLocalMeanWeightsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NFORDenoise/Source/NFORDenoise/Private/NFORDenoiseCS.cpp:686)
- L705-750 _entry_ `[numthreads(THREAD_GROUP_SIZE, THREAD_GROUP_SIZE, THREAD_GROUP_SIZE)] void NonLocalMeanGetSqauredDistanceToAtlasCS(in const uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `FNonLocalMeanGetSqauredDistanceToAtlasCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NFORDenoise/Source/NFORDenoise/Private/NFORDenoiseCS.cpp:689)
- L757-814 _entry_ `[numthreads(THREAD_GROUP_SIZE, THREAD_GROUP_SIZE, THREAD_GROUP_SIZE)] void NonLocalMeanSeperableFilterPatchSqauredDistanceCS(in const uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `FNonLocalMeanSeperableFilterPatchSqauredDistanceCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NFORDenoise/Source/NFORDenoise/Private/NFORDenoiseCS.cpp:690)
- L854-909 _entry_ `[numthreads(THREAD_GROUP_SIZE, THREAD_GROUP_SIZE, THREAD_GROUP_SIZE)] void NonLocalMeanReshapeBufferCS(in const uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `FNonLocalMeanReshapeBufferCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NFORDenoise/Source/NFORDenoise/Private/NFORDenoiseCS.cpp:691)
- L923-948 _entry_ `[numthreads(THREAD_GROUP_SIZE, THREAD_GROUP_SIZE, 1)] void CopyTextureToBufferCS(in const uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `FCopyTextureToBufferCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NFORDenoise/Source/NFORDenoise/Private/NFORDenoiseCS.cpp:696)
- L952-969 _entry_ `[numthreads(THREAD_GROUP_SIZE, THREAD_GROUP_SIZE, 1)] void NormalizeTextureCS(in const uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `FNormalizeTextureCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NFORDenoise/Source/NFORDenoise/Private/NFORDenoiseCS.cpp:697)
- L1301-1330 _entry_ `[numthreads(THREAD_GROUP_SIZE, THREAD_GROUP_SIZE, 1)] void InPlaceBatchedMatrixMultiplicationCS(in const uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `RegressionKernel::FInPlaceBatchedMatrixMultiplicationCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NFORDenoise/Source/NFORDenoise/Private/NFORDenoiseCS.cpp:700)
- L1374-1388 _entry_ `[numthreads(THREAD_GROUP_SIZE, THREAD_GROUP_SIZE, 1)] void LinearSolverCS(in const uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `RegressionKernel::FLinearSolverCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NFORDenoise/Source/NFORDenoise/Private/NFORDenoiseCS.cpp:701)
- L1394-1408 _entry_ `[numthreads(1, 1, 1)] void LinearSolverBuildIndirectDispatchArgsCS(in const uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `RegressionKernel::FLinearSolverBuildIndirectDispatchArgsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NFORDenoise/Source/NFORDenoise/Private/NFORDenoiseCS.cpp:704)
- L1412-1437 _entry_ `[numthreads(THREAD_GROUP_SIZE*THREAD_GROUP_SIZE, 1, 1)] void LinearSolverIndirectCS(in const uint3 DispatchThreadID : SV_DispatchThreadID, uint GI : SV_GroupIndex)` — stage: **compute** — C++: `RegressionKernel::FLinearSolverIndirectCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NFORDenoise/Source/NFORDenoise/Private/NFORDenoiseCS.cpp:705)
- L1501-1606 _entry_ `[numthreads(THREAD_GROUP_SIZE, THREAD_GROUP_SIZE, 1)] void ReconstructSpatialTemporalImageCS(in const uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `RegressionKernel::FReconstructSpatialTemporalImage` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NFORDenoise/Source/NFORDenoise/Private/NFORDenoiseCS.cpp:708)
- L1644-1655 _entry_ `[numthreads(THREAD_GROUP_SIZE, THREAD_GROUP_SIZE, 1)] void AccumulateBufferToTextureCS(in const uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `FAccumulateBufferToTextureCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NFORDenoise/Source/NFORDenoise/Private/NFORDenoiseCS.cpp:709)
- L1664-1680 _entry_ `[numthreads(THREAD_GROUP_SIZE, THREAD_GROUP_SIZE, 1)] void MSEEstimationCS(in const uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `FMSEEstimationCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NFORDenoise/Source/NFORDenoise/Private/NFORDenoiseCS.cpp:713)
- L1686-1698 _entry_ `[numthreads(THREAD_GROUP_SIZE, THREAD_GROUP_SIZE, 1)] void GenerateSelectionMapCS(in const uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `FGenerateSelectionMapCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NFORDenoise/Source/NFORDenoise/Private/NFORDenoiseCS.cpp:714)
- L1705-1718 _entry_ `[numthreads(THREAD_GROUP_SIZE, THREAD_GROUP_SIZE, 1)] void CombineFilteredImageCS(in const uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `FCombineFilteredImageCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NFORDenoise/Source/NFORDenoise/Private/NFORDenoiseCS.cpp:715)

#### Structs / classes (4)

- L438-442 _struct_ **`FImageContext`** `struct FImageContext`
  - L440 _member_ `TPixelValue Value;`
  - L441 _member_ `float Variance;`
- L1138-1141 _struct_ **`FMatrixCache`** `struct FMatrixCache`
  - L1140 _member_ `float Data[MATRIX_CACHE_SIZE];`
- L1143-1146 _struct_ **`FFeatureXCache`** `struct FFeatureXCache`
  - L1145 _member_ `float Data[NUM_FEATURE + APPEND_CONSTANT_DIMENSION_TO_X];`
- L1148-1155 _struct_ **`FFeatureYCache`** `struct FFeatureYCache`
  - L1151 _member_ `float Data[NUM_FEATURE + APPEND_CONSTANT_DIMENSION_TO_X];` _[#if WEIGHTED_MULTIPLICATION_TYPE == WEIGHTED_MULTIPLICATION_QUADRATIC]_
  - L1153 _member_ `float3 Data;` _[#if !(WEIGHTED_MULTIPLICATION_TYPE == WEIGHTED_MULTIPLICATION_QUADRATIC)]_

#### Global resources (textures / buffers / samplers) (51)

- L199 _resource_ `Texture2D<TPixelValue> Source;` — General texture operations
- L200 _resource_ `Texture2D<uint> Mask;`
- L201 _resource_ `RWTexture2D<float4> RWTarget;`
- L264 _resource_ `int2 TextureSize;`
- L273 _resource_ `Texture2D<float4> CopySource;` _[#if TEXTURE_COPY_TYPE == TEXTURE_COPY_TARGET_SINGLE_CHANNEL]_
- L274 _resource_ `RWTexture2D<float> RWCopyTarget;` _[#if TEXTURE_COPY_TYPE == TEXTURE_COPY_TARGET_SINGLE_CHANNEL]_
- L276 _resource_ `Texture2D<float> CopySource;` _[#if !(TEXTURE_COPY_TYPE == TEXTURE_COPY_TARGET_SINGLE_CHANNEL) && TEXTURE_COPY_TYPE == TEXTURE_COPY_SOURCE_SINGLE_CHANNEL]_
- L277 _resource_ `RWTexture2D<float4> RWCopyTarget;` _[#if !(TEXTURE_COPY_TYPE == TEXTURE_COPY_TARGET_SINGLE_CHANNEL) && TEXTURE_COPY_TYPE == TEXTURE_COPY_SOURCE_SINGLE_CHANNEL]_
- L331 _resource_ `Texture2D<float4> Normal;`
- L332 _resource_ `Texture2D<float4> NormalVariance;`
- L333 _resource_ `RWTexture2D<uint> RWMask;`
- L358 _resource_ `Texture2D<float4> Albedo;`
- L359 _resource_ `RWTexture2D<float4> RWRadianceVariance;`
- L376 _resource_ `RWTexture2D<float4> RWImage;`
- L377 _resource_ `RWTexture2D<float4> RWImageVariance;`
- L427 _resource_ `Texture2D<TPixelValue> Image;`
- L428 _resource_ `Texture2D<TImageVariance> Variance;`
- L431 _resource_ `Texture2D<TPixelValue> TargetImage;` _[#if NONLOCALMEAN_SEPARATE_SOURCE]_
- L432 _resource_ `Texture2D<TImageVariance> TargetVariance;` _[#if NONLOCALMEAN_SEPARATE_SOURCE]_
- L574 _resource_ `RWTexture2D<TPixelValue> DenoisedImage;`
- L575 _resource_ `Buffer<TWeightReadType> NonLocalMeanWeights;`
- L664 _resource_ `RWBuffer<float> RWNonLocalMeanWeights;`
- L693 _resource_ `RWTexture2D<TAtlasValueType> RWNLMWeightAtlas;`
- L752 _resource_ `RWBuffer<TAtlasValueType> RWNLMWeights;`
- L753 _resource_ `Texture2D<TAtlasValueType> NLMWeightAtlasSource;`
- L754 _resource_ `RWTexture2D<TAtlasValueType> RWNLMWeightAtlasTarget;`
- L816 _resource_ `Buffer<float2> SourceBuffer;`
- L817 _resource_ `RWBuffer<float> RWTargetBuffer;`
- L916 _resource_ `RWBuffer<float> Dest;`
- L950 _resource_ `RWTexture2D<float4> RWSource;`
- L974 _resource_ `Buffer<float> X;`
- L975 _resource_ `Buffer<TWeightReadType> W;`
- L976 _resource_ `Buffer<float> Y;`
- L978 _resource_ `RWBuffer<float> Result;`
- L1351 _resource_ `RWBuffer<uint> RWSuccessAndFailIndexBuffer;`
- L1391 _resource_ `RWBuffer<uint> RWIndirectDispatchArgsBuffer;`
- L1392 _resource_ `Buffer<uint> SuccessAndFailIndexBuffer;`
- L1443 _resource_ `RWTexture2D<float4> RWReconstruction;`
- L1444 _resource_ `RWStructuredBuffer<uint4> RWReconstructBuffer;`
- L1445 _resource_ `RWTexture2D<UlongType> RWReconstructBuffer64;`
- L1608 _resource_ `StructuredBuffer<uint4> StructuredBufferSource;`
- L1609 _resource_ `Texture2D<UlongType> ReconstructBuffer64;`
- L1661 _resource_ `Texture2D<TPixelValue> FilteredImage;`
- L1662 _resource_ `RWTexture2D<float> MSE;`
- L1682 _resource_ `Texture2D<float> FilteredMSEs_0;`
- L1683 _resource_ `Texture2D<float> FilteredMSEs_1;`
- L1684 _resource_ `RWTexture2D<float> RWSelectionMap;`
- L1700 _resource_ `Texture2D<float4> FilteredImages_0;`
- L1701 _resource_ `Texture2D<float4> FilteredImages_1;`
- L1702 _resource_ `Texture2D<float> SelectionMap;`
- L1703 _resource_ `RWTexture2D<float4> RWFilteredImage;`

#### Global parameters (uniforms) (42)

- L202 _parameter_ `int2 SourcePosition;`
- L203 _parameter_ `int2 TargetPosition;`
- L204 _parameter_ `int2 Size;`
- L205 _parameter_ `int ForceOperation;`
- L206 _parameter_ `float4 ConstantValue;`
- L260 _parameter_ `int2 SourceOffset;`
- L261 _parameter_ `int2 TargetOffset;`
- L262 _parameter_ `int Channel;`
- L263 _parameter_ `int2 CopySize;`
- L378 _parameter_ `float MaxValue;`
- L379 _parameter_ `int VarianceChannelOffset;`
- L416 _parameter_ `int PatchSize;`
- L417 _parameter_ `int PatchDistance;`
- L418 _parameter_ `float Bandwidth;`
- L421 _parameter_ `int DispatchId;` — Dispatch parameters
- L422 _parameter_ `int2 DispatchTileSize;`
- L423 _parameter_ `int DispatchTileCount;`
- L424 _parameter_ `int4 SeparableFilteringRegion;`
- L425 _parameter_ `int3 DispatchRegionSize;`
- L576 _parameter_ `int DenoisingChannelCount;`
- L577 _parameter_ `int4 FilteringRegion;`
- L663 _parameter_ `int4 Region;` — Calculate the non-local mean weights for Region
- L694 _parameter_ `int2 NLMWeightAtlasSize;`
- L755 _parameter_ `int3 SeperableRegionSize;`
- L818 _parameter_ `int4 SourceBufferDim;` — B,X+2*pd, Y+2*pd, Wb
- L819 _parameter_ `int3 TargetBufferDim;` — W, X, Y
- L820 _parameter_ `int HalfOffsetSearchCount;`
- L917 _parameter_ `int CopyChannelOffset;`
- L918 _parameter_ `int CopyChannelCount;`
- L919 _parameter_ `int BufferChannelOffset;`
- L920 _parameter_ `int BufferChannelSize;`
- L921 _parameter_ `int4 CopyRegion;`
- L980 _parameter_ `int2 XDim;`
- L981 _parameter_ `int WDim;`
- L982 _parameter_ `int NumOfTemporalFrames;`
- L983 _parameter_ `int NumOfWeigthsPerPixelPerFrame;`
- L986 _parameter_ `int2 YDim;` _[#if WEIGHTED_MULTIPLICATION_TYPE == WEIGHTED_MULTIPLICATION_GENERALIZED]_
- L1074 _parameter_ `int SamplingStep;`
- L1177 _parameter_ `int SourceFrameIndex;`
- L1350 _parameter_ `float Lambda;`
- L1441 _parameter_ `int FrameIndex;` — Reconstruct spatial temporal images
- L1442 _parameter_ `float AlbedoOffset;`

#### groupshared (1)

- L1410 _groupshared_ `groupshared uint CompactNumOfElements;`

#### Functions (36)

- L174-183 _function_ `float Length2(TPixelValue Value)`
- L185-188 _function_ `TPixelValue GetImageValue(int2 P, Texture2D<TPixelValue> inImage)`
- L190-195 _function_ `int2 GetMirroredPosition(int2 P, int2 inTextureSize)`
- L208-222 _function_ `float4 LoadSource(uint2 Position)`
- L308-325 _function_ `float GetImageVariance(int2 P, Texture2D inVariance, int inVarianceChannelOffset)`
- L444-455 _function_ `FImageContext GetImageContext(int2 Position, Texture2D<TPixelValue> inImage, Texture2D inVariance, float VarianceScale = 1.0f)`
- L458-468 _function_ `float GetSquaredDistance(TPixelValue Cp, float VarP, TPixelValue Cq, float VarQ)` — Note that GetSquaredDistance(P,Q) != GetSquaredDistance(Q,P), So we cannot share the weight with this asymetric distance.
- L471-484 _function_ `float2 GetSymmetricSquaredDistance(TPixelValue Cp, float VarP, TPixelValue Cq, float VarQ)` — Get the both way x=GetSquaredDistance(P,Q) and y=GetSquaredDistance(Q,P) together.
- L486-489 _function_ `float GetSquaredDistance(FImageContext PCtx, FImageContext QCtx)`
- L491-497 _function_ `float GetSquaredDistance(int2 P, int2 Q, float VarianceScale = 1.0f)`
- L499-502 _function_ `float2 GetSymmetricSquaredDistance(FImageContext PCtx, FImageContext QCtx)`
- L504-510 _function_ `float2 GetSymmetricSquaredDistance(int2 P, int2 Q, float VarianceScale = 1.0f)`
- L512-531 _function_ `float GetPatchSquaredDistance(int2 P, int2 Q)`
- L533-550 _function_ `TAtlasValueType GetNonLocalMeanWeight(int2 P, int2 Q, TAtlasValueType PatchPQSqaureDistance)`
- L553-572 _function_ `float GetNonLocalMeanWeight(int2 P, int2 Q)` — P is on source image, Q is on target image
- L579-598 _function_ `uint GetWeightBufferIndex(uint2 LocalPositionInRegion, uint WeightIndex, uint2 RegionSize)`
- L696-703 _function_ `uint2 GetAtlasPosition(uint3 DispatchThreadID, uint2 TileRegionSize,uint2 Offset = 0)`
- L822-834 _function_ `float2 GetInputFromBuffer(uint x, uint y, uint w)`
- L836-852 _function_ `void WriteWeight(uint2 PixelPosition, uint2 WeightPosition, float Weight)`
- L1001-1008 _function_ `float GetX(uint2 Position, uint f)`
- L1010-1014 _function_ `float GetX(uint2 Position, uint Db, uint FrameIndex)`
- L1016-1027 _function_ `float GetY(int2 Position, int f)`
- L1029-1051 _function_ `TWeightReadType GetW(int2 Position, int WeightIndex, int FrameIndex)`
- L1053-1063 _function_ `int2 GetModifiedXyYyDimension()`
- L1065-1070 _function_ `void WriteResult(int2 Position, int f, float Value)`
- L1076-1130 _function_ `void SolveMatrixMultiplicationPerMatrixItem(int2 Position, int2 ModifiedXyYyDim, int PatchWidth, int SingleFrameDataCount)`
- L1157-1167 _function_ `void FillFeatureXCache(out FFeatureXCache FeatureCache,uint2 Position, int2 ModifiedXyYyDim, uint FrameFeatureOffset)`
- L1169-1175 _function_ `void FillFeatureYCache(out FFeatureYCache FeatureCache, uint2 Position, int2 ModifiedXyYyDim, uint FrameFeatureOffset)`
- L1179-1299 _function_ `void MatrixMultiplicationSmallMatrixOptimization(int2 Position, int2 ModifiedXyYyDim, int PatchWidth, int SingleFrameDataCount)`
- L1353-1372 _function_ `void LinearSolveEntry(uint AOffset, uint ASize, uint BOffset, uint MatrixIndex)`
- L1447-1451 _function_ `float GetB(int2 Position, int f)`
- L1453-1458 _function_ `uint4 EncodeFloat4(float4 Value)`
- L1460-1464 _function_ `float4 DecodeFloat4(uint4 Value)`
- L1466-1499 _function_ `void SaveFloat4ToBufferOrTexture(uint2 Position, float4 Value, uint NumOfScattering)`
- L1611-1615 _function_ `float DecodeUint64ToFloat(Texture2D<UlongType> inTexture, uint2 Position)`
- L1617-1642 _function_ `float4 DecodeFloat4FromBufferOrTexture(uint2 Position)`

### `Plugins/Experimental/NFORDenoise/Shaders/NFORRegression.ush` (Other)

- lines: 742; parse: all-branches
- includes: L15 `NFORRegressionCommon.ush`

#### Macros (#define, 16)

- L18 `#define MATRIX_DIM 8` _[#if !defined(MATRIX_DIM)]_
- L22 `#define NUM_NEWTON_SCHULTZ_ITERATIONS 3` _[#if !defined(NUM_NEWTON_SCHULTZ_ITERATIONS)]_
- L25 `#define FULL_MATRIX_SIZE ((MATRIX_DIM)*(MATRIX_DIM))`
- L26 `#define SYMMETRIC_MATRIX_SIZE (((MATRIX_DIM+1)*MATRIX_DIM)/2)`
- L27 `#define LOWER_TRIANGLE_MATRIX_SIZE SYMMETRIC_MATRIX_SIZE`
- L29 `#define QR_DECOMPOSITION_TYPE_DEFAULT 0`
- L30 `#define QR_DECOMPOSITION_TYPE_COLUMN_PIVOT 1`
- L32 `#define QR_DECOMPOSITION_TYPE QR_DECOMPOSITION_TYPE_DEFAULT`
- L49 `#define LMatrixIndex2D(a,b) select(a>b, int2(b,a), int2(a,b))`
- L50 `#define LMatrixIndex1D(i) LMatrixIndex2D((i)%MATRIX_DIM, (i)/MATRIX_DIM)`
- L51 `#define LMatrix(_L,y,x) (_L.M[(x) + (((y) +1) * (y)/2)])`
- L54 `#define TLMatrixIndex2D(a,b) select(a>b, int2(a,b), int2(b,a))`
- L55 `#define TLMatrixIndex1D(i) TLMatrixIndex2D((i)%MATRIX_DIM, (i)/MATRIX_DIM)`
- L56 `#define TLMatrix(_L,y,x) LMatrix(_L,x,y)`
- L68 `#define MATRIX(_A,y,x) (_A.M[y * MATRIX_DIM + x])`
- L661 `#define NUM_INVERSE_ITERATIONS_DOUBLE NUM_NEWTON_SCHULTZ_ITERATIONS`
- L13 #pragma `once`

#### Structs / classes (3)

- L44-47 _struct_ **`FLMatrix`** `struct FLMatrix`
  - L46 _member_ `FDFScalar M[LOWER_TRIANGLE_MATRIX_SIZE];`
- L58-61 _struct_ **`FNFORVector`** `struct FNFORVector`
  - L60 _member_ `FDFScalar V[MATRIX_DIM];`
- L63-66 _struct_ **`FMatrix`** `struct FMatrix`
  - L65 _member_ `FDFScalar M[FULL_MATRIX_SIZE];`

#### Global resources (textures / buffers / samplers) (2)

- L34 _resource_ `Buffer<float> A;`
- L35 _resource_ `Buffer<float> B;`

#### Global parameters (uniforms) (5)

- L37 _parameter_ `int2 ADim;`
- L38 _parameter_ `int2 BDim;`
- L39 _parameter_ `int NumOfElements;`
- L40 _parameter_ `int NumOfElementsPerRow;`
- L42 _parameter_ `float MinLambda;`

#### Functions (24)

- L70-79 _function_ `void LMatrixNegate(inout FLMatrix A)`
- L83-104 _function_ `FMatrix LMatrixMultiply(in FLMatrix A, in FLMatrix B)` — Assume A and B is symmetric and stored in FLMatrix. A@B != B@A even if A=A^T, B^T=B
- L106-114 _function_ `float LMatrixMaxAbsValue(in FLMatrix A)`
- L117-137 _function_ `FLMatrix ToLMatrixMultiply(in FLMatrix A, in FMatrix B)` — Assume A is symmetric, and B is not. However, A*B is symmetric
- L139-147 _function_ `void Identity(out FMatrix M)`
- L149-159 _function_ `void LMatrixEuclideanNorm(in FLMatrix A, out float EuclideanNorm)`
- L162-174 _function_ `void MatrixConvergence(in FMatrix A, out float ConvergenceCriteria)` — \|AX-I\|. Euclidean norm of AX-I
- L177-183 _function_ `void MatrixNegate(inout FMatrix Matrix)`
- L185-195 _function_ `FMatrix Copy(in FMatrix Matrix)`
- L197-215 _function_ `FMatrix MatrixMultiply(in FMatrix A, in FMatrix B)`
- L217-229 _function_ `FDFScalar GetNFORVectorNorm2(in FDFScalar V[MATRIX_DIM], int N)`
- L231-236 _function_ `void SwapIntVector(inout int V[MATRIX_DIM], int i, int j)`
- L238-247 _function_ `void SwampColumn(inout FMatrix Matrix, int i, int j)`
- L249-260 _function_ `FMatrix SelectSubMatrix(in FMatrix Matrix, int StartRowColumnIndex)`
- L262-284 _function_ `int GetPivot(in FMatrix Matrix, int N)`
- L286-315 _function_ `void HouseHoldReflection(in FDFScalar A[MATRIX_DIM], out FMatrix O, int N)`
- L319-361 _function_ `void QRDecomposition(in FMatrix A, out FMatrix Q, out FMatrix R , out int PivotIndices[MATRIX_DIM] )` — Calculate AX=B with (Household) QR decomposition and back substitution. TODO: Reduce the memory used in calculation.
- L363-452 _function_ `void QR_Solve(int AOffset, int ASize, int BOffset)`
- L454-494 _function_ `bool CholeskeyDecomposition(inout FLMatrix L, FLMatrix AMatrix, float lambda)`
- L496-534 _function_ `FLMatrix CholeskyFactorInverse(FLMatrix L)`
- L536-622 _function_ `bool CholeskeySolve(int AOffset, int ASize, int BOffset, float lambda, RWBuffer<float> Result)`
- L624-651 _function_ `bool InitializeGuess(inout FLMatrix L, FLMatrix AMatrix, float inLambda)`
- L653-699 _function_ `FLMatrix MatrixInverse(FLMatrix AMatrix, float inLambda, inout bool bComplete)`
- L701-740 _function_ `bool NewtonIterativeSolve(int AOffset, int ASize, int BOffset, float inLambda, RWBuffer<float> Result)`

### `Plugins/Experimental/NFORDenoise/Shaders/NFORRegressionCommon.ush` (Other)

- lines: 22; parse: all-branches

#### Macros (#define, 8)

- L7 `#define LINEAR_SOLVER_TYPE_NEWTON_SCHULZ 0`
- L8 `#define LINEAR_SOLVER_TYPE_CHOLESKY 1`
- L9 `#define LINEAR_SOLVER_TYPE_NEWTON_CHOLESKY 2`
- L12 `#define LINEAR_SOLVER_TYPE LINEAR_SOLVER_TYPE_NEWTON_SCHULZ` _[#if !defined(LINEAR_SOLVER_TYPE)]_
- L15 `#define INITIAL_GUESS_INVERSE_CHOLESKY_DECOMPOSITION 0`
- L16 `#define INITIAL_GUESS_EUCLIDEAN_NORM 1`
- L19 `#define NEWTON_INITIAL_GUESS_TYPE INITIAL_GUESS_INVERSE_CHOLESKY_DECOMPOSITION` _[#if !defined(NEWTON_INITIAL_GUESS_TYPE)]_
- L22 `#define NEWTON_SCHULZ_EARLY_STOP 1`
