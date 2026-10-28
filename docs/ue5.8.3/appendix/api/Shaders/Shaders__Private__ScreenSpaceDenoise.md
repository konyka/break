# Shaders / Shaders/Private/ScreenSpaceDenoise

- files: 20; lines: 10088
- record kinds: cpp_binding=5, define=617, entry=5, function=159, include=72, macro_call=3, member=91, parameter=89, resource=17, static_const=7, struct=16

### `Shaders/Private/ScreenSpaceDenoise/DenoisingCommon.ush` (Private)

- lines: 64; parse: all-branches
- includes: L8 `../Common.ush`, L9 `../MonteCarlo.ush`, L10 `../BRDF.ush`, L11 `../DeferredShadingCommon.ush`, L12 `../CommonViewUniformBuffer.ush`
- L3 #pragma `once`

#### Functions (4)

- L17-20 _function_ `float ComputeDenoisingCoc(float DistanceCameraToPixel, float ClosestHitDistance)`
- L22-25 _function_ `float ComputeHitDistanceFromDenoisingCoc(float DistanceCameraToPixel, float MaxCoc)`
- L27-57 _function_ `void ComputeSpecularLobeAngles(float3 V, float3 N, float Roughness, out float OutMajorRoughnessLobeAngle, out float OutMinorRoughnessLobeAngle)`
- L60-63 _function_ `float LobeAngleToViewportRadius(float LobeAngle)` — Return the size of the bluring radius caused by a lobe in ViewportUV.x space from radian opening angle.

### `Shaders/Private/ScreenSpaceDenoise/SSDCommon.ush` (Private)

- lines: 332; parse: first-branch (retry, +4 merged from all-branches pass)
- includes: L13 `../Common.ush`, L14 `../SceneTextureParameters.ush`, L15 `../ColorSpace.ush`, L16 `../SphericalGaussian.ush`, L17 `/Engine/Public/WaveBroadcastIntrinsics.ush`, L18 `/Engine/Private/Substrate/Substrate.ush`, L21 `../SHCommon.ush` [SPHERICAL_HARMONIC_ORDER > 0], L24 `SSDPublic.ush`, L25 `SSDDefinitions.ush`, L26 `SSDMetadata.ush`

#### Macros (#define, 18)

- L10 `#define SPHERICAL_HARMONIC_ORDER 0` _[#if !defined(SPHERICAL_HARMONIC_ORDER)]_
- L32 `#define TARGETED_SAMPLE_COUNT 1024` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_REFLECTIONS]_
- L36 `#define TARGETED_SAMPLE_COUNT 1024` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_REFLECTIONS) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK]_
- L39 `#define TARGETED_SAMPLE_COUNT 256` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_REFLECTIONS) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_AO]_
- L43 `#define TARGETED_SAMPLE_COUNT 1024` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_REFLECTIONS) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_AO) && CON...]_
- L47 `#define TARGETED_SAMPLE_COUNT 4096` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_REFLECTIONS) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_AO) && !(C...]_
- L50 `#define TARGETED_SAMPLE_COUNT 128` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_REFLECTIONS) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_AO) && !(C...]_
- L53 `#define TARGETED_SAMPLE_COUNT 128` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_REFLECTIONS) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_AO) && !(C...]_
- L58 `#define TARGETED_SAMPLE_COUNT 32` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_REFLECTIONS) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_AO) && !(C...]_
- L59 `#define CONFIG_METADATA_BUFFER_LAYOUT METADATA_BUFFER_LAYOUT_FED_DEPTH_SHADINGMODEL` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_REFLECTIONS) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_AO) && !(C...]_
- L67 `#define CONFIG_METADATA_BUFFER_LAYOUT METADATA_BUFFER_LAYOUT_DISABLED` _[#if !defined(CONFIG_METADATA_BUFFER_LAYOUT)]_
- L71 `#define CONFIG_USE_VIEW_SPACE 0` _[#if !defined(CONFIG_USE_VIEW_SPACE)]_
- L168 `#define FSSDSphericalHarmonic FTwoBandSHVector` _[#if !(SPHERICAL_HARMONIC_ORDER == 0) && SPHERICAL_HARMONIC_ORDER == 2]_
- L169 `#define FSSDSphericalHarmonicRGB FTwoBandSHVectorRGB` _[#if !(SPHERICAL_HARMONIC_ORDER == 0) && SPHERICAL_HARMONIC_ORDER == 2]_
- L170 `#define SSDAddSH AddSH` _[#if !(SPHERICAL_HARMONIC_ORDER == 0) && SPHERICAL_HARMONIC_ORDER == 2]_
- L173 `#define FSSDSphericalHarmonic FThreeBandSHVector` _[#if !(SPHERICAL_HARMONIC_ORDER == 0) && !(SPHERICAL_HARMONIC_ORDER == 2) && SPHERICAL_HARMONIC_ORDER == 3]_
- L174 `#define FSSDSphericalHarmonicRGB FThreeBandSHVectorRGB` _[#if !(SPHERICAL_HARMONIC_ORDER == 0) && !(SPHERICAL_HARMONIC_ORDER == 2) && SPHERICAL_HARMONIC_ORDER == 3]_
- L175 `#define SSDAddSH AddSH3` _[#if !(SPHERICAL_HARMONIC_ORDER == 0) && !(SPHERICAL_HARMONIC_ORDER == 2) && SPHERICAL_HARMONIC_ORDER == 3]_
- L7 #pragma `once`

#### Global resources (textures / buffers / samplers) (12)

- L94 _resource_ `Texture2D PrevDepthBuffer;`
- L95 _resource_ `Texture2D PrevGBufferA;`
- L96 _resource_ `Texture2D PrevGBufferB;`
- L101 _resource_ `Texture2D<float> CompressedMetadata_0;` _[#if CONFIG_METADATA_BUFFER_LAYOUT == METADATA_BUFFER_LAYOUT_FED_DEPTH_SHADINGMODEL]_
- L102 _resource_ `Texture2D<uint> CompressedMetadata_1;` _[#if CONFIG_METADATA_BUFFER_LAYOUT == METADATA_BUFFER_LAYOUT_FED_DEPTH_SHADINGMODEL]_
- L104 _resource_ `Texture2D<float> PrevCompressedMetadata_0;` _[#if CONFIG_METADATA_BUFFER_LAYOUT == METADATA_BUFFER_LAYOUT_FED_DEPTH_SHADINGMODEL]_
- L105 _resource_ `Texture2D<uint> PrevCompressedMetadata_1;` _[#if CONFIG_METADATA_BUFFER_LAYOUT == METADATA_BUFFER_LAYOUT_FED_DEPTH_SHADINGMODEL]_
- L109 _resource_ `Texture2D<uint> CompressedMetadata_0;` _[#if !(CONFIG_METADATA_BUFFER_LAYOUT == METADATA_BUFFER_LAYOUT_FED_DEPTH_SHADINGMODEL)]_
- L110 _resource_ `Texture2D<uint> CompressedMetadata_1;` _[#if !(CONFIG_METADATA_BUFFER_LAYOUT == METADATA_BUFFER_LAYOUT_FED_DEPTH_SHADINGMODEL)]_
- L112 _resource_ `Texture2D<uint> PrevCompressedMetadata_0;` _[#if !(CONFIG_METADATA_BUFFER_LAYOUT == METADATA_BUFFER_LAYOUT_FED_DEPTH_SHADINGMODEL)]_
- L113 _resource_ `Texture2D<uint> PrevCompressedMetadata_1;` _[#if !(CONFIG_METADATA_BUFFER_LAYOUT == METADATA_BUFFER_LAYOUT_FED_DEPTH_SHADINGMODEL)]_
- L118 _resource_ `RWTexture2D<float4> DebugOutput;` _[#if DEBUG_OUTPUT]_

#### Global parameters (uniforms) (10)

- L81 _parameter_ `uint2 ViewportMin;`
- L82 _parameter_ `uint2 ViewportMax;`
- L83 _parameter_ `float4 ThreadIdToBufferUV;`
- L84 _parameter_ `float4 DenoiserBufferSizeAndInvSize;`
- L85 _parameter_ `float4 DenoiserBufferBilinearUVMinMax;`
- L86 _parameter_ `float2 BufferUVToOutputPixelPosition;`
- L87 _parameter_ `float4 SceneBufferUVToScreenPosition;`
- L88 _parameter_ `float4x4 ScreenToView;`
- L89 _parameter_ `float2 BufferUVBilinearCorrection;`
- L92 _parameter_ `float4 PrevSceneBufferUVToScreenPosition;`

#### Functions (9)

- L124-129 _function_ `float SafeRcp(float x)`
- L132-159 _function_ `float4x4 GetScreenToViewDistanceMatrix()` _[#if CONFIG_USE_VIEW_SPACE]_
- L184-194 _function_ `float ComputeAnisotropyInvFactor(FSSDSampleSceneInfos SceneMetadata)` — Compute the anisotropy value. The lower the value is, the more anysotropic the sample is.
- L197-201 _function_ `float ComputeWorldBluringRadiusCausedByPixelSize(FSSDSampleSceneInfos SceneMetadata)` — Returns the radius of a pixel in world space.
- L204-218 _function_ `float WorldBluringRadiusToBilateralWorldDistance(float WorldBluringRadius)` — Convert to bilateral world distance.
- L220-223 _function_ `uint2 BufferUVToBufferPixelCoord(float2 SceneBufferUV)`
- L225-228 _function_ `float2 DenoiserBufferUVToScreenPosition(float2 SceneBufferUV)`
- L230-242 _function_ `FSSDCompressedSceneInfos MaterialToCompressedSceneMetadata(float Depth, float3 WorldNormal, float Roughness, uint ShadingID)`
- L244-294 _function_ `FSSDCompressedSceneInfos SampleCompressedSceneMetadata( const bool bPrevFrame, float2 BufferUV, uint2 PixelCoord)`

### `Shaders/Private/ScreenSpaceDenoise/SSDComposeHarmonics.usf` (Private)

- lines: 312; parse: all-branches
- includes: L3 `SSDDefinitions.ush`, L4 `SSDPublicHarmonics.ush`, L44 `SSDSignalFramework.ush`, L45 `SSDSignalArray.ush`, L46 `SSDSignalBufferEncoding.ush`

#### Macros (#define, 32)

- L9 `#define TILE_PIXEL_SIZE 8`
- L11 `#define CONFIG_SIGNAL_PROCESSING SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC`
- L15 `#define MAX_SIGNAL_BATCH_SIZE 2` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC]_
- L16 `#define SIGNAL_ARRAY_SIZE 2` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC]_
- L17 `#define CONFIG_SIGNAL_BATCH_SIZE 2` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC]_
- L20 `#define COMPILE_SIGNAL_COLOR_ARRAY 2` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC]_
- L23 `#define COMPILE_SIGNAL_COLOR 1` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC]_
- L26 `#define CONFIG_MULTIPLEXED_SIGNALS_PER_SIGNAL_DOMAIN 1` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC]_
- L29 `#define CONFIG_SIGNAL_INPUT_LAYOUT SIGNAL_BUFFER_LAYOUT_POLYCHROMATIC_PENUMBRA_HARMONIC_INPUT` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC]_
- L30 `#define CONFIG_SIGNAL_RECONSTRUCTED_LAYOUT SIGNAL_BUFFER_LAYOUT_POLYCHROMATIC_PENUMBRA_HARMONIC_RECONSTRUCTION` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC]_
- L31 `#define CONFIG_SIGNAL_OUTPUT_LAYOUT SIGNAL_BUFFER_LAYOUT_POLYCHROMATIC_PENUMBRA_HISTORY` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC]_
- L32 `#define CONFIG_INPUT_TEXTURE_COUNT 4` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC]_
- L33 `#define CONFIG_OUTPUT_TEXTURE_COUNT 2` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC]_
- L35 `#define CONFIG_HARMONIC_COUNT DENOISER_HARMONICS_COUNT` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC]_
- L69 `#define SignalHarmonics_0_Textures_1 SignalHarmonics_0_Textures_0` _[#if !(CONFIG_INPUT_TEXTURE_COUNT > 1)]_
- L70 `#define SignalHarmonics_1_Textures_1 SignalHarmonics_1_Textures_0` _[#if !(CONFIG_INPUT_TEXTURE_COUNT > 1)]_
- L71 `#define SignalHarmonics_2_Textures_1 SignalHarmonics_2_Textures_0` _[#if !(CONFIG_INPUT_TEXTURE_COUNT > 1)]_
- L72 `#define SignalHarmonics_3_Textures_1 SignalHarmonics_3_Textures_0` _[#if !(CONFIG_INPUT_TEXTURE_COUNT > 1)]_
- L73 `#define SignalIntegrand_Textures_1 SignalIntegrand_Textures_0` _[#if !(CONFIG_INPUT_TEXTURE_COUNT > 1)]_
- L83 `#define SignalHarmonics_0_Textures_2 SignalHarmonics_0_Textures_0` _[#if !(CONFIG_INPUT_TEXTURE_COUNT > 2)]_
- L84 `#define SignalHarmonics_1_Textures_2 SignalHarmonics_1_Textures_0` _[#if !(CONFIG_INPUT_TEXTURE_COUNT > 2)]_
- L85 `#define SignalHarmonics_2_Textures_2 SignalHarmonics_2_Textures_0` _[#if !(CONFIG_INPUT_TEXTURE_COUNT > 2)]_
- L86 `#define SignalHarmonics_3_Textures_2 SignalHarmonics_3_Textures_0` _[#if !(CONFIG_INPUT_TEXTURE_COUNT > 2)]_
- L87 `#define SignalIntegrand_Textures_2 SignalIntegrand_Textures_0` _[#if !(CONFIG_INPUT_TEXTURE_COUNT > 2)]_
- L97 `#define SignalHarmonics_0_Textures_3 SignalHarmonics_0_Textures_0` _[#if !(CONFIG_INPUT_TEXTURE_COUNT > 3)]_
- L98 `#define SignalHarmonics_1_Textures_3 SignalHarmonics_1_Textures_0` _[#if !(CONFIG_INPUT_TEXTURE_COUNT > 3)]_
- L99 `#define SignalHarmonics_2_Textures_3 SignalHarmonics_2_Textures_0` _[#if !(CONFIG_INPUT_TEXTURE_COUNT > 3)]_
- L100 `#define SignalHarmonics_3_Textures_3 SignalHarmonics_3_Textures_0` _[#if !(CONFIG_INPUT_TEXTURE_COUNT > 3)]_
- L101 `#define SignalIntegrand_Textures_3 SignalIntegrand_Textures_0` _[#if !(CONFIG_INPUT_TEXTURE_COUNT > 3)]_
- L114 `#define SignalOutput_UAVs_1 SignalOutput_UAVs_0` _[#if !(CONFIG_OUTPUT_TEXTURE_COUNT > 1)]_
- L120 `#define SignalOutput_UAVs_2 SignalOutput_UAVs_0` _[#if !(CONFIG_OUTPUT_TEXTURE_COUNT > 2)]_
- L126 `#define SignalOutput_UAVs_3 SignalOutput_UAVs_0` _[#if !(CONFIG_OUTPUT_TEXTURE_COUNT > 3)]_

#### Entry points (1)

- L132-311 _entry_ `[numthreads(TILE_PIXEL_SIZE, TILE_PIXEL_SIZE, 1)] void MainCS( uint2 DispatchThreadId : SV_DispatchThreadID, uint2 GroupId : SV_GroupID, uint2 GroupThreadId : SV_GroupThreadID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FSSDComposeHarmonicsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/ScreenSpaceDenoise.cpp:1256)

#### Global parameters (uniforms) (24)

- L55 _parameter_ `FSSDTexture2D SignalHarmonics_0_Textures_0;`
- L56 _parameter_ `FSSDTexture2D SignalHarmonics_1_Textures_0;`
- L57 _parameter_ `FSSDTexture2D SignalHarmonics_2_Textures_0;`
- L58 _parameter_ `FSSDTexture2D SignalHarmonics_3_Textures_0;`
- L60 _parameter_ `FSSDTexture2D SignalIntegrand_Textures_0;`
- L63 _parameter_ `FSSDTexture2D SignalHarmonics_0_Textures_1;` _[#if CONFIG_INPUT_TEXTURE_COUNT > 1]_
- L64 _parameter_ `FSSDTexture2D SignalHarmonics_1_Textures_1;` _[#if CONFIG_INPUT_TEXTURE_COUNT > 1]_
- L65 _parameter_ `FSSDTexture2D SignalHarmonics_2_Textures_1;` _[#if CONFIG_INPUT_TEXTURE_COUNT > 1]_
- L66 _parameter_ `FSSDTexture2D SignalHarmonics_3_Textures_1;` _[#if CONFIG_INPUT_TEXTURE_COUNT > 1]_
- L67 _parameter_ `FSSDTexture2D SignalIntegrand_Textures_1;` _[#if CONFIG_INPUT_TEXTURE_COUNT > 1]_
- L77 _parameter_ `FSSDTexture2D SignalHarmonics_0_Textures_2;` _[#if CONFIG_INPUT_TEXTURE_COUNT > 2]_
- L78 _parameter_ `FSSDTexture2D SignalHarmonics_1_Textures_2;` _[#if CONFIG_INPUT_TEXTURE_COUNT > 2]_
- L79 _parameter_ `FSSDTexture2D SignalHarmonics_2_Textures_2;` _[#if CONFIG_INPUT_TEXTURE_COUNT > 2]_
- L80 _parameter_ `FSSDTexture2D SignalHarmonics_3_Textures_2;` _[#if CONFIG_INPUT_TEXTURE_COUNT > 2]_
- L81 _parameter_ `FSSDTexture2D SignalIntegrand_Textures_2;` _[#if CONFIG_INPUT_TEXTURE_COUNT > 2]_
- L91 _parameter_ `FSSDTexture2D SignalHarmonics_0_Textures_3;` _[#if CONFIG_INPUT_TEXTURE_COUNT > 3]_
- L92 _parameter_ `FSSDTexture2D SignalHarmonics_1_Textures_3;` _[#if CONFIG_INPUT_TEXTURE_COUNT > 3]_
- L93 _parameter_ `FSSDTexture2D SignalHarmonics_2_Textures_3;` _[#if CONFIG_INPUT_TEXTURE_COUNT > 3]_
- L94 _parameter_ `FSSDTexture2D SignalHarmonics_3_Textures_3;` _[#if CONFIG_INPUT_TEXTURE_COUNT > 3]_
- L95 _parameter_ `FSSDTexture2D SignalIntegrand_Textures_3;` _[#if CONFIG_INPUT_TEXTURE_COUNT > 3]_
- L109 _parameter_ `FSSDRWTexture2D SignalOutput_UAVs_0;`
- L112 _parameter_ `FSSDRWTexture2D SignalOutput_UAVs_1;` _[#if CONFIG_OUTPUT_TEXTURE_COUNT > 1]_
- L118 _parameter_ `FSSDRWTexture2D SignalOutput_UAVs_2;` _[#if CONFIG_OUTPUT_TEXTURE_COUNT > 2]_
- L124 _parameter_ `FSSDRWTexture2D SignalOutput_UAVs_3;` _[#if CONFIG_OUTPUT_TEXTURE_COUNT > 3]_

### `Shaders/Private/ScreenSpaceDenoise/SSDCompressMetadata.usf` (Private)

- lines: 76; parse: all-branches
- includes: L3 `SSDMetadata.ush`, L4 `../SceneTextureParameters.ush`

#### Macros (#define, 1)

- L9 `#define TILE_PIXEL_SIZE 8`

#### Entry points (1)

- L53-75 _entry_ `[numthreads(TILE_PIXEL_SIZE, TILE_PIXEL_SIZE, 1)] void MainCS(uint2 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FSSDCompressMetadataCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/ScreenSpaceDenoise.cpp:1252)

#### Global resources (textures / buffers / samplers) (1)

- L20 _resource_ `RWTexture2D<uint> CompressedMetadataOutput_0;`

#### Global parameters (uniforms) (5)

- L14 _parameter_ `uint2 ViewportMin;`
- L15 _parameter_ `uint2 ViewportMax;`
- L16 _parameter_ `float4 ThreadIdToBufferUV;`
- L17 _parameter_ `float4 BufferBilinearUVMinMax;`
- L18 _parameter_ `float2 BufferUVToOutputPixelPosition;`

#### Functions (1)

- L25-48 _function_ `FSSDSampleSceneInfos FetchCurrentSceneInfosFromGBuffer(float2 ScreenPosition, float2 BufferUV)`

### `Shaders/Private/ScreenSpaceDenoise/SSDDefinitions.ush` (Private)

- lines: 333; parse: all-branches
- includes: L5 `/Engine/Public/Platform.ush`

#### Macros (#define, 112)

- L17 `#define DEBUG_ENABLE_TILE_CLASSIFICATION 1`
- L21 `#define DEBUG_WASTFUL_OUTPUT 1`
- L24 `#define DEBUG_MIP_LEVEL -1`
- L27 `#define DEBUG_MODE_DISABLED -1`
- L28 `#define DEBUG_MODE_BRUTE_FORCE_ONLY 0`
- L29 `#define DEBUG_MODE_FAST_ONLY 1`
- L30 `#define DEBUG_MODE DEBUG_MODE_DISABLED`
- L34 `#define DEBUG_DISABLE_BILATERAL 0` _[#if !defined(DEBUG_DISABLE_BILATERAL)]_
- L38 `#define DEBUG_STORE_NORMALIZED_COMPONENTS 1`
- L41 `#define DEBUG_DISABLE_SIGNAL_COMPRESSION 0`
- L44 `#define DEBUG_OUTPUT 0`
- L50 `#define MAX_MIP_LEVEL_COUNT 4`
- L55 `#define BLURING_ESTIMATION_MULTIPLIER 3.0`
- L58 `#define WORLD_RADIUS_INVALID -1`
- L59 `#define WORLD_RADIUS_MISS (100000)`
- L62 `#define CONFUSION_FACTOR_INVALID -1`
- L63 `#define CONFUSION_FACTOR_MISS 1`
- L67 `#define MIP_LEVEL_INVALID -1`
- L68 `#define MIP_LEVEL_MISS 1024`
- L71 `#define MAX_MULTIPLEXED_TEXTURES 4`
- L78 `#define METADATA_BUFFER_LAYOUT_DISABLED 0`
- L81 `#define METADATA_BUFFER_LAYOUT_DEPTH_NORMAL 1`
- L84 `#define METADATA_BUFFER_LAYOUT_DEPTH_VIEWNORMAL 2`
- L87 `#define METADATA_BUFFER_LAYOUT_FED_DEPTH_SHADINGMODEL 3`
- L90 `#define METADATA_BUFFER_LAYOUT_WORLD_POS_SHADINGMODEL 4`
- L97 `#define SIGNAL_BUFFER_LAYOUT_UNINITIALIZED 0xDEAD`
- L101 `#define SIGNAL_BUFFER_LAYOUT_PENUMBRA_INPUT_NSPP 15`
- L104 `#define SIGNAL_BUFFER_LAYOUT_PENUMBRA_INJESTION_NSPP 16`
- L107 `#define SIGNAL_BUFFER_LAYOUT_PENUMBRA_HISTORY 11`
- L111 `#define SIGNAL_BUFFER_LAYOUT_POLYCHROMATIC_PENUMBRA_HARMONIC_INPUT 0x1000`
- L114 `#define SIGNAL_BUFFER_LAYOUT_POLYCHROMATIC_PENUMBRA_HARMONIC_RECONSTRUCTION 0x1001`
- L117 `#define SIGNAL_BUFFER_LAYOUT_POLYCHROMATIC_PENUMBRA_HISTORY 0x1002`
- L121 `#define SIGNAL_BUFFER_LAYOUT_REFLECTIONS_INPUT 3`
- L124 `#define SIGNAL_BUFFER_LAYOUT_REFLECTIONS_HISTORY 4`
- L128 `#define SIGNAL_BUFFER_LAYOUT_AO_INPUT 0xA000`
- L131 `#define SIGNAL_BUFFER_LAYOUT_AO_REJECTION 0xA001`
- L134 `#define SIGNAL_BUFFER_LAYOUT_AO_HISTORY 0xA002`
- L138 `#define SIGNAL_BUFFER_LAYOUT_DIFFUSE_INDIRECT_AND_AO_INPUT_NSPP 0xD100`
- L141 `#define SIGNAL_BUFFER_LAYOUT_DIFFUSE_INDIRECT_AND_AO_RECONSTRUCTION 0xD101`
- L144 `#define SIGNAL_BUFFER_LAYOUT_DIFFUSE_INDIRECT_AND_AO_HISTORY 0xD102`
- L148 `#define SIGNAL_BUFFER_LAYOUT_DIFFUSE_INDIRECT_HARMONIC 0xD200`
- L152 `#define SIGNAL_BUFFER_LAYOUT_SSGI_INPUT 0xD300`
- L154 `#define SIGNAL_BUFFER_LAYOUT_SSGI_HISTORY_R11G11B10 0xD301`
- L158 `#define SIGNAL_BUFFER_LAYOUT_LUMEN_DIFFUSE_INPUT 0xD400`
- L160 `#define SIGNAL_BUFFER_LAYOUT_LUMEN_DIFFUSE_HISTORY 0xD401`
- L164 `#define SIGNAL_BUFFER_LAYOUT_DIFFUSE_PROBE_HIERARCHY_INPUT 0xD500`
- L166 `#define SIGNAL_BUFFER_LAYOUT_DIFFUSE_PROBE_HIERARCHY_HISTORY 0xD501`
- L171 `#define SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK 0`
- L174 `#define SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC 1`
- L177 `#define SIGNAL_PROCESSING_REFLECTIONS 2`
- L180 `#define SIGNAL_PROCESSING_AO 3`
- L183 `#define SIGNAL_PROCESSING_DIFFUSE_INDIRECT_AND_AO 4`
- L186 `#define SIGNAL_PROCESSING_DIFFUSE_SPHERICAL_HARMONIC 5`
- L189 `#define SIGNAL_PROCESSING_SSGI 6`
- L192 `#define SIGNAL_PROCESSING_DIFFUSE_PROBE_HIERARCHY 7`
- L197 `#define COLOR_SPACE_RGB 0x0`
- L198 `#define COLOR_SPACE_YCOCG 0x1`
- L199 `#define COLOR_SPACE_LCOCG 0x2`
- L201 `#define COLOR_SPACE_UNPREMULTIPLY 0x4`
- L202 `#define COLOR_SPACE_KARIS_WEIGHTING 0x8`
- L207 `#define SAMPLE_SET_1X1 0`
- L210 `#define SAMPLE_SET_2X2_BILINEAR 1`
- L213 `#define SAMPLE_SET_2X2_STOCASTIC 13`
- L216 `#define SAMPLE_SET_2X2_ADAPTIVE 17`
- L219 `#define SAMPLE_SET_3X3 2`
- L220 `#define SAMPLE_SET_3X3_SOBEK2018 3`
- L221 `#define SAMPLE_SET_5X5_WAVELET 4`
- L223 `#define SAMPLE_SET_3X3_PLUS 5`
- L224 `#define SAMPLE_SET_3X3_CROSS 6`
- L226 `#define SAMPLE_SET_NXN 7`
- L229 `#define SAMPLE_SET_STACKOWIAK_4_SETS 8`
- L231 `#define SAMPLE_SET_HEXAWEB 11`
- L233 `#define SAMPLE_SET_DIRECTIONAL_RECT 14`
- L234 `#define SAMPLE_SET_DIRECTIONAL_ELLIPSE 15`
- L236 `#define SAMPLE_SET_RAW_EXPERIMENTAL_KERNEL 16`
- L241 `#define SIGNAL_COMPRESSION_DISABLED 0`
- L244 `#define SIGNAL_COMPRESSION_DIFFUSE_INDIRECT_HARMONIC 0xD200`
- L249 `#define ACCUMULATOR_COMPRESSION_DISABLED 0`
- L252 `#define ACCUMULATOR_COMPRESSION_PENUMBRA_DRB 0x0001`
- L257 `#define NEIGHBOR_TO_REF_CACHE_WORLD_POSITION 0`
- L261 `#define NEIGHBOR_TO_REF_LOWEST_VGPR_PRESSURE 1`
- L265 `#define SIGNAL_TEXTURE_TYPE_FLOAT4 0`
- L266 `#define SIGNAL_TEXTURE_TYPE_UINT1 1`
- L267 `#define SIGNAL_TEXTURE_TYPE_UINT2 2`
- L268 `#define SIGNAL_TEXTURE_TYPE_UINT3 3`
- L269 `#define SIGNAL_TEXTURE_TYPE_UINT4 4`
- L273 `#define BILATERAL_POSITION_BASED(n) (0x0000 + (n) & 0xF)`
- L274 `#define BILATERAL_NORMAL 0x0010`
- L275 `#define BILATERAL_TOKOYASHI_LOBE 0x0020`
- L276 `#define BILATERAL_TOKOYASHI_AXES 0x0040`
- L277 `#define BILATERAL_TOKOYASHI (BILATERAL_TOKOYASHI_LOBE \| BILATERAL_TOKOYASHI_AXES)`
- L278 `#define BILATERAL_SHADING_MODEL 0x0080`
- L282 `#define BILATERAL_PRESET_DISABLED 0x0000`
- L284 `#define BILATERAL_PRESET_MONOCHROMATIC_PENUMBRA 0x0011`
- L286 `#define BILATERAL_PRESET_POLYCHROMATIC_PENUMBRA 0x0022`
- L288 `#define BILATERAL_PRESET_REFLECTIONS 0x1001`
- L289 `#define BILATERAL_PRESET_REFLECTIONS_1SPP 0x1002`
- L290 `#define BILATERAL_PRESET_REFLECTIONS_TAA 0x1003`
- L292 `#define BILATERAL_PRESET_DIFFUSE 0x2001`
- L294 `#define BILATERAL_PRESET_SPHERICAL_HARMONIC 0x3001`
- L296 `#define BILATERAL_PRESET_AO 0x4001`
- L297 `#define BILATERAL_PRESET_AO_HISTORY 0x4002`
- L298 `#define BILATERAL_PRESET_PROBE_HIERARCHY 0xF000`
- L306 `#define CONFIG_NORMAL_ANISOTROPY 0`
- L309 `#define CONFIG_VGPR_OPTIMIZATION 1`
- L312 `#define CONFIG_VALU_OPTIMIZATIONS 1`
- L316 `#define CONFIG_SGPR_HINT_OPTIMIZATION 0`
- L319 `#define CONFIG_COMPRESS_WORLD_NORMAL 1`
- L322 `#define CONFIG_COMPRESS_WORLD_POSITION 1`
- L325 `#define STANDARD_BUFFER_COLOR_SPACE COLOR_SPACE_RGB`
- L328 `#define REFLECTIONS_REJECTION_COLOR_SPACE (COLOR_SPACE_LCOCG \| COLOR_SPACE_UNPREMULTIPLY)`
- L332 `#define SPHERICAL_HARMONIC_ORDER 2`
- L3 #pragma `once`; L11 #pragma `warning(error: 3206)`

### `Shaders/Private/ScreenSpaceDenoise/SSDInjest.usf` (Private)

- lines: 171; parse: all-branches
- includes: L3 `SSDDefinitions.ush`, L34 `SSDSignalFramework.ush`, L35 `SSDSignalArray.ush`, L36 `SSDSignalBufferEncoding.ush`

#### Macros (#define, 18)

- L8 `#define TILE_PIXEL_SIZE 8`
- L10 `#define CONFIG_SIGNAL_PROCESSING DIM_SIGNAL_PROCESSING`
- L11 `#define CONFIG_SIGNAL_BATCH_SIZE DIM_SIGNAL_BATCH_SIZE`
- L14 `#define MAX_SIGNAL_BATCH_SIZE CONFIG_SIGNAL_BATCH_SIZE` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK]_
- L15 `#define SIGNAL_ARRAY_SIZE CONFIG_SIGNAL_BATCH_SIZE` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK]_
- L17 `#define CONFIG_SIGNAL_INPUT_LAYOUT SIGNAL_BUFFER_LAYOUT_PENUMBRA_INPUT_NSPP` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK]_
- L18 `#define CONFIG_SIGNAL_OUTPUT_LAYOUT SIGNAL_BUFFER_LAYOUT_PENUMBRA_INJESTION_NSPP` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK]_
- L19 `#define CONFIG_MULTIPLEXED_SIGNALS_PER_SIGNAL_DOMAIN 1` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK]_
- L21 `#define CONFIG_SIGNAL_INPUT_TEXTURE_TYPE SIGNAL_TEXTURE_TYPE_FLOAT4` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK]_
- L22 `#define CONFIG_SIGNAL_OUTPUT_TEXTURE_TYPE SIGNAL_TEXTURE_TYPE_UINT2` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK]_
- L24 `#define CONFIG_INPUT_TEXTURE_COUNT DIM_SIGNAL_BATCH_SIZE` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK]_
- L25 `#define CONFIG_OUTPUT_TEXTURE_COUNT ((DIM_SIGNAL_BATCH_SIZE + 1) / 2)` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK]_
- L50 `#define SignalInput_Textures_1 SignalInput_Textures_0` _[#if !(CONFIG_INPUT_TEXTURE_COUNT > 1)]_
- L56 `#define SignalInput_Textures_2 SignalInput_Textures_0` _[#if !(CONFIG_INPUT_TEXTURE_COUNT > 2)]_
- L62 `#define SignalInput_Textures_3 SignalInput_Textures_0` _[#if !(CONFIG_INPUT_TEXTURE_COUNT > 3)]_
- L75 `#define SignalOutput_UAVs_1 SignalOutput_UAVs_0` _[#if !(CONFIG_OUTPUT_TEXTURE_COUNT > 1)]_
- L81 `#define SignalOutput_UAVs_2 SignalOutput_UAVs_0` _[#if !(CONFIG_OUTPUT_TEXTURE_COUNT > 2)]_
- L87 `#define SignalOutput_UAVs_3 SignalOutput_UAVs_0` _[#if !(CONFIG_OUTPUT_TEXTURE_COUNT > 3)]_

#### Entry points (1)

- L93-170 _entry_ `[numthreads(TILE_PIXEL_SIZE, TILE_PIXEL_SIZE, 1)] void MainCS( uint2 DispatchThreadId : SV_DispatchThreadID, uint2 GroupId : SV_GroupID, uint2 GroupThreadId : SV_GroupThreadID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FSSDInjestCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/ScreenSpaceDenoise.cpp:1253)

#### Global parameters (uniforms) (8)

- L45 _parameter_ `FSSDTexture2D SignalInput_Textures_0;`
- L48 _parameter_ `FSSDTexture2D SignalInput_Textures_1;` _[#if CONFIG_INPUT_TEXTURE_COUNT > 1]_
- L54 _parameter_ `FSSDTexture2D SignalInput_Textures_2;` _[#if CONFIG_INPUT_TEXTURE_COUNT > 2]_
- L60 _parameter_ `FSSDTexture2D SignalInput_Textures_3;` _[#if CONFIG_INPUT_TEXTURE_COUNT > 3]_
- L70 _parameter_ `FSSDRWTexture2D SignalOutput_UAVs_0;`
- L73 _parameter_ `FSSDRWTexture2D SignalOutput_UAVs_1;` _[#if CONFIG_OUTPUT_TEXTURE_COUNT > 1]_
- L79 _parameter_ `FSSDRWTexture2D SignalOutput_UAVs_2;` _[#if CONFIG_OUTPUT_TEXTURE_COUNT > 2]_
- L85 _parameter_ `FSSDRWTexture2D SignalOutput_UAVs_3;` _[#if CONFIG_OUTPUT_TEXTURE_COUNT > 3]_

### `Shaders/Private/ScreenSpaceDenoise/SSDMetadata.ush` (Private)

- lines: 284; parse: all-branches
- includes: L5 `SSDDefinitions.ush`, L6 `../Common.ush`, L7 `../SceneTextureParameters.ush`, L8 `/Engine/Public/WaveBroadcastIntrinsics.ush`

#### Macros (#define, 1)

- L13 `#define MAX_COMPRESSED_METADATA_VGPRS 6`
- L3 #pragma `once`

#### Structs / classes (2)

- L51-55 _struct_ **`FSSDCompressedSceneInfos`** `struct FSSDCompressedSceneInfos` — olds commonly used information of the scene of a given sample.
  - L54 _member_ `uint VGPR[MAX_COMPRESSED_METADATA_VGPRS];` — Raw compressed buffer, kept fully compressed to have minimal VGPR footprint.
- L73-98 _struct_ **`FSSDSampleSceneInfos`** `struct FSSDSampleSceneInfos` — olds commonly used information of the scene of a given sample.
  - L76 _member_ `float2 ScreenPosition;` — Raw screen position of the sample.
  - L79 _member_ `float DeviceZ;` — The raw device Z.
  - L82 _member_ `float WorldDepth;` — Raw pixel depth in world space.
  - L85 _member_ `float Roughness;` — Roughness of the pixel.
  - L88 _member_ `float3 WorldNormal;` — Normal of the pixel in world space.
  - L91 _member_ `float3 ViewNormal;` — Normal of the pixel in view space.
  - L94 _member_ `float3 TranslatedWorldPosition;` — Position of the pixel in the translated world frame to save VALU.
  - L97 _member_ `uint ShadingModelID;` — Shading model of the scene pixel.

#### Functions (11)

- L18-29 _function_ `void DecompressDevizeZAndN(uint Compressed, out float DevizeZ, out float3 N)`
- L31-39 _function_ `uint CompressDevizeZAndN(float DevizeZ, float3 N)`
- L42-45 _function_ `bool DenoiseShadingModelID(uint ShadingModelID)` — Return whether this shading model id should be denoised or not.
- L58-67 _function_ `FSSDCompressedSceneInfos CreateCompressedSceneInfos()`
- L100-111 _function_ `FSSDSampleSceneInfos CreateSampleSceneInfos()`
- L117-211 _function_ `ISOLATE FSSDSampleSceneInfos UncompressSampleSceneInfo( const uint CompressedLayout, const bool bIsPrevFrame, float2 ScreenPosition, FSSDCompressedSceneInfos CompressedInfos)` — SUBSTRATE_TODO
- L214-255 _function_ `FSSDCompressedSceneInfos CompressSampleSceneInfo( const uint CompressedLayout, FSSDSampleSceneInfos Infos)` — SUBSTRATE_TODO
- L257-260 _function_ `float3 GetWorldNormal(FSSDSampleSceneInfos SceneMetadata)`
- L262-265 _function_ `float GetWorldDepth(FSSDSampleSceneInfos SceneMetadata)`
- L267-270 _function_ `float3 GetTranslatedWorldPosition(FSSDSampleSceneInfos SceneMetadata)`
- L273-283 _function_ `FSSDSampleSceneInfos WaveBroadcastSceneMetadata(const FWaveBroadcastSettings Settings, FSSDSampleSceneInfos SceneMetadata)`

### `Shaders/Private/ScreenSpaceDenoise/SSDPublic.ush` (Private)

- lines: 51; parse: all-branches
- includes: L5 `../Random.ush`, L6 `../MonteCarlo.ush`, L7 `../SobolRandom.ush`

#### Macros (#define, 4)

- L12 `#define GGX_IMPORTANT_SAMPLE_BIAS 0.1`
- L15 `#define DENOISER_INVALID_HIT_DISTANCE -2.0`
- L18 `#define DENOISER_MISS_HIT_DISTANCE -1.0`
- L21 `#define DENOISER_INVALID_CONFUSION_FACTOR -1.0`
- L3 #pragma `once`

#### Functions (2)

- L25-44 _function_ `float2 Rand1SPPDenoiserInput(uint2 PixelPos)` — Random generator used for 1 sample per pixel for denoiser input.
- L47-50 _function_ `float ComputeDenoiserConfusionFactor(bool bValid, float DistanceCameraToPixel, float ClosestHitDistance)` — Compute the factor to apply to inifinity bluring radius based on the sample's hit distance.

### `Shaders/Private/ScreenSpaceDenoise/SSDPublicBufferEncoding.ush` (Private)

- lines: 118; parse: all-branches
- includes: L5 `../Common.ush`, L6 `../SHCommon.ush`

#### Macros (#define, 5)

- L10 `#define SSD_ENCODE_CLAMP_COLOR 0x1`
- L11 `#define SSD_ENCODE_NORMALIZE_MISS 0x2`
- L12 `#define SSD_ENCODE_NORMALIZE_COLOR 0x4`
- L13 `#define SSD_ENCODE_NORMALIZE (SSD_ENCODE_NORMALIZE_MISS \| SSD_ENCODE_NORMALIZE_COLOR)`
- L16 `#define SSD_DECODE_NORMALIZE 0x1`
- L3 #pragma `once`

#### Functions (7)

- L19-23 _function_ `uint Compress2Floats(float2 v)`
- L25-29 _function_ `float2 Uncompress2Floats(uint v)`
- L31-34 _function_ `uint2 Compress4Floats(float4 v)`
- L36-39 _function_ `float4 Uncompress4Floats(uint2 v)`
- L41-44 _function_ `float4 f32x4tof16(float4 OutRawSample)`
- L48-89 _function_ `void EncodeDiffuseSphericalHarmonicTexel( float SampleCount, float MissCount, FTwoBandSHVectorRGB ColorSH, const uint Options, out uint2 OutRawSample[4])` — Encode a SIGNAL_BUFFER_LAYOUT_DIFFUSE_INDIRECT_HARMONIC formated buffer.
- L92-117 _function_ `void DecodeDiffuseSphericalHarmonicTexel( uint2 RawSample[4], const uint Options, out float OutSampleCount, out float OutMissCount, out FTwoBandSHVectorRGB OutColorSH)` — Decodes a SIGNAL_BUFFER_LAYOUT_DIFFUSE_INDIRECT_HARMONIC formated buffer.

### `Shaders/Private/ScreenSpaceDenoise/SSDPublicHarmonics.ush` (Private)

- lines: 142; parse: all-branches
- includes: L8 `../Common.ush`, L9 `../LightShaderParameters.ush`

#### Macros (#define, 2)

- L15 `#define DENOISER_HARMONICS_COUNT 4`
- L16 `#define DENOISER_HARMONIC_BORDERS_COUNT (DENOISER_HARMONICS_COUNT + 1)`
- L3 #pragma `once`

#### Structs / classes (1)

- L80-83 _struct_ **`FSSDHarmonicAccumulator`** `struct FSSDHarmonicAccumulator` — TODO(Denoiser): That is a lot of VGPR for ray gen, implement texture atomic one.
  - L82 _member_ `float3 HarmonicBorders[DENOISER_HARMONIC_BORDERS_COUNT];`

#### Functions (6)

- L21-60 _function_ `float ComputeLightSampleWorldBluringRadius(float3 TranslatedWorldPosition, uint LightType, FLightShaderParameters Light, float HitT)`
- L62-65 _function_ `float ProjectWorldDistanceToPixelDistance(float WorldDepth, float WorldDistance)`
- L67-74 _function_ `float WorldBluringRadiusToHarmonic(float WorldDepth, float WorldBluringRadius)`
- L85-94 _function_ `FSSDHarmonicAccumulator InitHarmonicAccumulator()`
- L96-104 _function_ `void AccumulateSampleHarmonic(inout FSSDHarmonicAccumulator Accumulator, float3 Color, float SceneDepth, float HitHarmonic)`
- L106-141 _function_ `void OutputHarmonicAccumulator( RWTexture2D<float4> OutputTexture0, RWTexture2D<float4> OutputTexture1, RWTexture2D<float4> OutputTexture2, RWTexture2D<float4> OutputTexture3, RWTexture2D<float4> OutputTexture4, uint2 PixelPosition, FSSDHarmonicAccumulator Accumulator, bool bIsValidPixel)`

### `Shaders/Private/ScreenSpaceDenoise/SSDSignalAccumulator.ush` (Private)

- lines: 392; parse: all-branches
- includes: L5 `SSDSignalCore.ush`, L6 `SSDSignalCompression.ush`

#### Macros (#define, 6)

- L10 `#define CONFIG_SIGNAL_VGPR_COMPRESSION SIGNAL_COMPRESSION_DISABLED` _[#if !defined(CONFIG_SIGNAL_VGPR_COMPRESSION)]_
- L14 `#define COMPILE_MOMENT1_ACCUMULATOR 0` _[#if !defined(COMPILE_MOMENT1_ACCUMULATOR)]_
- L18 `#define COMPILE_MOMENT2_ACCUMULATOR 0` _[#if !defined(COMPILE_MOMENT2_ACCUMULATOR)]_
- L22 `#define COMPILE_MINMAX_ACCUMULATOR 0` _[#if !defined(COMPILE_MINMAX_ACCUMULATOR)]_
- L26 `#define COMPILE_MIN_FREQUENCY_ACCUMULATOR 0` _[#if !defined(COMPILE_MIN_FREQUENCY_ACCUMULATOR)]_
- L30 `#define COMPILE_DRB_ACCUMULATOR 0` _[#if !defined(COMPILE_DRB_ACCUMULATOR)]_
- L3 #pragma `once`

#### Structs / classes (3)

- L39-82 _struct_ **`FSSDSignalAccumulator`** `struct FSSDSignalAccumulator` — Accumulator of multiple signals. Multiple accumulators are actually implemented in the same structure because lack of templating in shading language, so relly on shader compiler ability's to prune useless stuf.
  - L43 _member_ `FSSDSignalSample Moment1;` _[#if COMPILE_MOMENT1_ACCUMULATOR]_
  - L47 _member_ `FSSDSignalSample Moment2;` _[#if COMPILE_MOMENT2_ACCUMULATOR]_
  - L52 _member_ `FSSDCompressedSignalSample CompressedMoment1;` _[#if COMPILE_MOMENT1_ACCUMULATOR]_
  - L56 _member_ `FSSDCompressedSignalSample CompressedMoment2;` _[#if COMPILE_MOMENT2_ACCUMULATOR]_
  - L61 _member_ `FSSDSignalSample Min;` _[#if COMPILE_MINMAX_ACCUMULATOR]_
  - L62 _member_ `FSSDSignalSample Max;` _[#if COMPILE_MINMAX_ACCUMULATOR]_
  - L67 _member_ `FSSDSignalFrequency MinFrequency;` _[#if COMPILE_MIN_FREQUENCY_ACCUMULATOR]_
  - L72 _member_ `FSSDSignalSample Current;` _[#if COMPILE_DRB_ACCUMULATOR]_
  - L73 _member_ `float CurrentInvFrequency;` _[#if COMPILE_DRB_ACCUMULATOR]_
  - L74 _member_ `float CurrentTranslucency;` _[#if COMPILE_DRB_ACCUMULATOR]_
  - L76 _member_ `FSSDSignalSample Previous;` _[#if COMPILE_DRB_ACCUMULATOR]_
  - L77 _member_ `float PreviousInvFrequency;` _[#if COMPILE_DRB_ACCUMULATOR]_
  - L79 _member_ `float BorderingRadius;` _[#if COMPILE_DRB_ACCUMULATOR]_
  - L80 _member_ `float HighestInvFrequency;` _[#if COMPILE_DRB_ACCUMULATOR]_
- L85-89 _struct_ **`FSSDSampleClusterInfo`** `struct FSSDSampleClusterInfo` — Informations about cluster of sample
  - L88 _member_ `float OutterBoundaryRadius;` — Outter radius boundary of the cluster.
- L144-157 _struct_ **`FSSDSampleAccumulationInfos`** `struct FSSDSampleAccumulationInfos`
  - L147 _member_ `FSSDSignalSample Sample;` — Sample to accumulate.
  - L150 _member_ `FSSDSignalFrequency Frequency;` — Frequency of the sample.
  - L153 _member_ `float FinalWeight;` — Weight of the sample in the kernel.
  - L156 _member_ `float InvFrequency;` — 1 / SignalFrequency

#### Functions (12)

- L92-139 _function_ `FSSDSignalAccumulator CreateSignalAccumulator()`
- L161-172 _function_ `float AmendWorldBluringRadiusCausedByPixelSize(float WorldBluringDistance)` — Transform the world bluring distance due to pixel size with some conservative to be forgiving
- L179-190 _function_ `void AccumulateSampleInOneBin(inout FSSDSignalAccumulator Accumulator, FSSDSampleAccumulationInfos SampleInfos)` — Accumulate a sample withing the accumulator.
- L196-217 _function_ `void AccumulateSampleInDomainBoundaries(inout FSSDSignalAccumulator Accumulator, FSSDSampleAccumulationInfos SampleInfos)` — Tracks min and max values accumulator.
- L225-253 _function_ `void StartAccumulatingClusterInDRB( FSSDSampleSceneInfos RefSceneMetadata, inout FSSDSignalAccumulator Accumulator, FSSDSampleClusterInfo ClusterInfo)` _[#if COMPILE_DRB_ACCUMULATOR]_
- L255-290 _function_ `void AccumulateSampleInDRB(inout FSSDSignalAccumulator Accumulator, FSSDSampleAccumulationInfos A)` _[#if COMPILE_DRB_ACCUMULATOR]_
- L292-323 _function_ `void DijestSampleClusterInDRB( inout FSSDSignalAccumulator Accumulator, uint RingId, uint SampleCount)` _[#if COMPILE_DRB_ACCUMULATOR]_
- L330-339 _function_ `void CompressSignalAccumulator(inout FSSDSignalAccumulator Accumulator)`
- L341-350 _function_ `void UncompressSignalAccumulator(inout FSSDSignalAccumulator Accumulator)`
- L356-364 _function_ `void StartAccumulatingCluster( FSSDSampleSceneInfos RefSceneMetadata, inout FSSDSignalAccumulator Accumulator, FSSDSampleClusterInfo ClusterInfo)` — Start accumulating a cluster of samples.
- L367-381 _function_ `void AccumulateSample( inout FSSDSignalAccumulator Accumulator, FSSDSampleAccumulationInfos SampleInfos)` — Accumulate a sample withing the accumulator.
- L384-391 _function_ `void DijestAccumulatedClusterSamples( inout FSSDSignalAccumulator Accumulator, uint RingId, uint SampleCount)` — Digest the accumulated cluster of samples.

### `Shaders/Private/ScreenSpaceDenoise/SSDSignalAccumulatorArray.ush` (Private)

- lines: 145; parse: all-branches
- includes: L3 `SSDSignalAccumulator.ush`

#### Macros (#define, 1)

- L7 `#define MAX_ACCUMULATOR_COMPRESSED_VGPRS 20`

#### Structs / classes (2)

- L11-14 _struct_ **`FSSDSignalAccumulatorArray`** `struct FSSDSignalAccumulatorArray` — Structure that is just an array of accumulators, to work arround shader compiler bug on "out" of arrays.
  - L13 _member_ `FSSDSignalAccumulator Array[SIGNAL_ARRAY_SIZE];`
- L17-20 _struct_ **`FSSDCompressedSignalAccumulatorArray`** `struct FSSDCompressedSignalAccumulatorArray` — Accumulator array that is compressed to have lower VGPR footprint.
  - L19 _member_ `uint VGPR[MAX_ACCUMULATOR_COMPRESSED_VGPRS];`

#### Functions (4)

- L23-33 _function_ `FSSDSignalAccumulatorArray CreateSignalAccumulatorArray()` — Created an initialised accumulator array.
- L36-45 _function_ `FSSDCompressedSignalAccumulatorArray CreateUninitialisedCompressedAccumulatorArray()` — Created an uninitialized accumulator array that is compressed.
- L48-97 _function_ `FSSDCompressedSignalAccumulatorArray CompressAccumulatorArray(in FSSDSignalAccumulatorArray Accumulators, uint CompressionLayout)` — Compress the accumulator array.
- L100-144 _function_ `FSSDSignalAccumulatorArray UncompressAccumulatorArray(in FSSDCompressedSignalAccumulatorArray CompressedAccumulators, uint CompressionLayout)` — Uncompress the accumulator array.

### `Shaders/Private/ScreenSpaceDenoise/SSDSignalArray.ush` (Private)

- lines: 161; parse: all-branches
- includes: L5 `SSDSignalCore.ush`
- L3 #pragma `once`

#### Functions (14)

- L8-17 _function_ `FSSDSignalArray MulSignalArray(FSSDSignalArray Samples, float Scalar[SIGNAL_ARRAY_SIZE])`
- L19-28 _function_ `FSSDSignalArray AddSignalArray(FSSDSignalArray SamplesA, FSSDSignalArray SamplesB)`
- L30-39 _function_ `FSSDSignalArray MinusSignalArray(FSSDSignalArray Samples)`
- L41-50 _function_ `FSSDSignalArray SubtractSignalArray(FSSDSignalArray SamplesA, FSSDSignalArray SamplesB)`
- L52-61 _function_ `FSSDSignalArray AbsSignalArray(FSSDSignalArray Samples)`
- L63-72 _function_ `FSSDSignalArray SqrtSignalArray(FSSDSignalArray Samples)`
- L74-83 _function_ `FSSDSignalArray PowerSignalArray(FSSDSignalArray Samples, float Exponent)`
- L85-94 _function_ `FSSDSignalArray MinSignalArray(FSSDSignalArray SamplesA, FSSDSignalArray SamplesB)`
- L96-105 _function_ `FSSDSignalArray MaxSignalArray(FSSDSignalArray SamplesA, FSSDSignalArray SamplesB)`
- L107-116 _function_ `FSSDSignalArray ClampSignalArray(FSSDSignalArray Samples, FSSDSignalArray SamplesMin, FSSDSignalArray SamplesMax)`
- L118-127 _function_ `FSSDSignalArray LerpSignalArray(FSSDSignalArray Samples0, FSSDSignalArray Samples1, float Interp[SIGNAL_ARRAY_SIZE])`
- L129-138 _function_ `FSSDSignalArray NormalizeToOneSampleArray(FSSDSignalArray Samples)`
- L140-149 _function_ `FSSDSignalArray WaveBroadcastSignalArray(const FWaveBroadcastSettings BroadcastSettings, FSSDSignalArray Samples)`
- L151-160 _function_ `FSSDSignalFrequencyArray WaveBroadcastSignalFrequenciesArray(const FWaveBroadcastSettings BroadcastSettings, FSSDSignalFrequencyArray Frequencies)`

### `Shaders/Private/ScreenSpaceDenoise/SSDSignalBufferEncoding.ush` (Private)

- lines: 850; parse: first-branch (retry, +0 merged from all-branches pass)
- includes: L5 `SSDSignalCore.ush`, L6 `SSDPublicBufferEncoding.ush`, L7 `../Lumen/LumenBufferEncoding.ush`

#### Macros (#define, 16)

- L10 `#define CONFIG_ENCODING_CLAMP_COLOR 1`
- L14 `#define CONFIG_SIGNAL_INPUT_TEXTURE_TYPE SIGNAL_TEXTURE_TYPE_FLOAT4` _[#if !defined(CONFIG_SIGNAL_INPUT_TEXTURE_TYPE)]_
- L19 `#define CONFIG_SIGNAL_OUTPUT_TEXTURE_TYPE SIGNAL_TEXTURE_TYPE_FLOAT4` _[#if !defined(CONFIG_SIGNAL_OUTPUT_TEXTURE_TYPE)]_
- L24 `#define FSSDRawSample float4` _[#if CONFIG_SIGNAL_INPUT_TEXTURE_TYPE == SIGNAL_TEXTURE_TYPE_FLOAT4]_
- L25 `#define FSSDTexture2D Texture2D` _[#if CONFIG_SIGNAL_INPUT_TEXTURE_TYPE == SIGNAL_TEXTURE_TYPE_FLOAT4]_
- L28 `#define FSSDRawSample uint` _[#if !(CONFIG_SIGNAL_INPUT_TEXTURE_TYPE == SIGNAL_TEXTURE_TYPE_FLOAT4) && CONFIG_SIGNAL_INPUT_TEXTURE_TYPE == SIGNAL_TEXTURE_TYPE_UINT1 \|\| CONFIG_SIGNAL_INPUT_TEXTURE_TYPE == SIGNAL_TEXTURE_TYPE_UINT2 \|...]_
- L30 `#define FSSDRawSample uint2` _[#if !(CONFIG_SIGNAL_INPUT_TEXTURE_TYPE == SIGNAL_TEXTURE_TYPE_FLOAT4) && CONFIG_SIGNAL_INPUT_TEXTURE_TYPE == SIGNAL_TEXTURE_TYPE_UINT1 \|\| CONFIG_SIGNAL_INPUT_TEXTURE_TYPE == SIGNAL_TEXTURE_TYPE_UINT2 \|...]_
- L32 `#define FSSDRawSample uint3` _[#if !(CONFIG_SIGNAL_INPUT_TEXTURE_TYPE == SIGNAL_TEXTURE_TYPE_FLOAT4) && CONFIG_SIGNAL_INPUT_TEXTURE_TYPE == SIGNAL_TEXTURE_TYPE_UINT1 \|\| CONFIG_SIGNAL_INPUT_TEXTURE_TYPE == SIGNAL_TEXTURE_TYPE_UINT2 \|...]_
- L34 `#define FSSDRawSample uint4` _[#if !(CONFIG_SIGNAL_INPUT_TEXTURE_TYPE == SIGNAL_TEXTURE_TYPE_FLOAT4) && CONFIG_SIGNAL_INPUT_TEXTURE_TYPE == SIGNAL_TEXTURE_TYPE_UINT1 \|\| CONFIG_SIGNAL_INPUT_TEXTURE_TYPE == SIGNAL_TEXTURE_TYPE_UINT2 \|...]_
- L38 `#define FSSDTexture2D Texture2D<FSSDRawSample>` _[#if !(CONFIG_SIGNAL_INPUT_TEXTURE_TYPE == SIGNAL_TEXTURE_TYPE_FLOAT4) && CONFIG_SIGNAL_INPUT_TEXTURE_TYPE == SIGNAL_TEXTURE_TYPE_UINT1 \|\| CONFIG_SIGNAL_INPUT_TEXTURE_TYPE == SIGNAL_TEXTURE_TYPE_UINT2 \|...]_
- L44 `#define FSSDOutputRawSample float4` _[#if CONFIG_SIGNAL_OUTPUT_TEXTURE_TYPE == SIGNAL_TEXTURE_TYPE_FLOAT4]_
- L46 `#define FSSDOutputRawSample uint` _[#if !(CONFIG_SIGNAL_OUTPUT_TEXTURE_TYPE == SIGNAL_TEXTURE_TYPE_FLOAT4) && CONFIG_SIGNAL_OUTPUT_TEXTURE_TYPE == SIGNAL_TEXTURE_TYPE_UINT1]_
- L48 `#define FSSDOutputRawSample uint2` _[#if !(CONFIG_SIGNAL_OUTPUT_TEXTURE_TYPE == SIGNAL_TEXTURE_TYPE_FLOAT4) && !(CONFIG_SIGNAL_OUTPUT_TEXTURE_TYPE == SIGNAL_TEXTURE_TYPE_UINT1) && CONFIG_SIGNAL_OUTPUT_TEXTURE_TYPE == SIGNAL_TEXTURE_TYPE_U...]_
- L50 `#define FSSDOutputRawSample uint3` _[#if !(CONFIG_SIGNAL_OUTPUT_TEXTURE_TYPE == SIGNAL_TEXTURE_TYPE_FLOAT4) && !(CONFIG_SIGNAL_OUTPUT_TEXTURE_TYPE == SIGNAL_TEXTURE_TYPE_UINT1) && !(CONFIG_SIGNAL_OUTPUT_TEXTURE_TYPE == SIGNAL_TEXTURE_TYPE...]_
- L52 `#define FSSDOutputRawSample uint4` _[#if !(CONFIG_SIGNAL_OUTPUT_TEXTURE_TYPE == SIGNAL_TEXTURE_TYPE_FLOAT4) && !(CONFIG_SIGNAL_OUTPUT_TEXTURE_TYPE == SIGNAL_TEXTURE_TYPE_UINT1) && !(CONFIG_SIGNAL_OUTPUT_TEXTURE_TYPE == SIGNAL_TEXTURE_TYPE...]_
- L57 `#define FSSDRWTexture2D RWTexture2D<FSSDOutputRawSample>`
- L3 #pragma `once`

#### Structs / classes (1)

- L75-78 _struct_ **`FSSDCompressedMultiplexedSample`** `struct FSSDCompressedMultiplexedSample` — Raw data layout when sampling input texture of the denoiser.
  - L77 _member_ `FSSDRawSample VGPRArray[MAX_MULTIPLEXED_TEXTURES];`

#### Functions (9)

- L60-66 _function_ `float3 ClampColorForEncoding(float3 Color)`
- L68-71 _function_ `float4 ClampColorForEncoding(float4 Color)`
- L82-431 _function_ `void DecodeMultiplexedSignalsFromFloat4( const uint SignalBufferLayout, const uint MultiplexedSampleId, const bool bNormalizeSample, float4 RawSample[MAX_MULTIPLEXED_TEXTURES], out FSSDSignalArray OutSamples, out FSSDSignalFrequencyArray OutSampleFrequencies)` — Decode input signal sample from raw float.
- L433-472 _function_ `void DecodeMultiplexedSignalsFromUint2( const uint SignalBufferLayout, const uint MultiplexedSampleId, const bool bNormalizeSample, uint2 RawSample[MAX_MULTIPLEXED_TEXTURES], out FSSDSignalArray OutSamples, out FSSDSignalFrequencyArray OutSampleFrequencies)`
- L475-491 _function_ `void DecodeMultiplexedSignals( const uint SignalBufferLayout, const uint MultiplexedSampleId, const bool bNormalizeSample, FSSDCompressedMultiplexedSample CompressedSample, out FSSDSignalArray OutSamples, out FSSDSignalFrequencyArray OutSampleFrequencies)` — Decode input signal sample from raw float.
- L506-694 _function_ `void EncodeMultiplexedSignals( const uint SignalBufferLayout, const uint MultiplexCount, FSSDSignalSample Sample[SIGNAL_ARRAY_SIZE], FSSDSignalFrequency SampleFrequency[SIGNAL_ARRAY_SIZE], out FSSDOutputRawSample OutRawSample[MAX_MULTIPLEXED_TEXTURES], out uint OutBufferCount)` — Encode output signal sample.
- L762-794 _function_ `FSSDCompressedMultiplexedSample SampleCompressedMultiplexedSignals( FSSDTexture2D SignalBuffer0, FSSDTexture2D SignalBuffer1, FSSDTexture2D SignalBuffer2, FSSDTexture2D SignalBuffer3, SamplerState Sampler, float2 UV, uint2 PixelCoord)` — Sample the raw of multiple input signals that have been multiplexed.
- L798-817 _function_ `void SampleMultiplexedSignals( FSSDTexture2D SignalBuffer0, FSSDTexture2D SignalBuffer1, FSSDTexture2D SignalBuffer2, FSSDTexture2D SignalBuffer3, SamplerState Sampler, const uint SignalBufferLayout, const uint MultiplexedSampleId, const bool bNormalizeSample, float2 UV, out FSSDSignalArray OutMultiplexedSamples, out FSSDSignalFrequencyArray OutMultiplexedFrequencies)` — Sample multiple input signals that have been multiplexed.
- L821-849 _function_ `void OutputMultiplexedSignal( FSSDRWTexture2D OutputSignalBuffer0, FSSDRWTexture2D OutputSignalBuffer1, FSSDRWTexture2D OutputSignalBuffer2, FSSDRWTexture2D OutputSignalBuffer3, const uint SignalBufferLayout, const uint MultiplexCount, const uint2 PixelPosition, FSSDSignalArray MultiplexedSamples, FSSDSignalFrequencyArray MultiplexedFrequencies)` — Outputs multiplexed signal.

### `Shaders/Private/ScreenSpaceDenoise/SSDSignalCompression.ush` (Private)

- lines: 90; parse: all-branches
- includes: L5 `SSDSignalCore.ush`, L6 `SSDPublicBufferEncoding.ush`

#### Macros (#define, 2)

- L12 `#define MAX_SIGNAL_COMPRESSED_VGPRS 7` _[#if COMPILE_SIGNAL_COLOR_SH]_
- L14 `#define MAX_SIGNAL_COMPRESSED_VGPRS 1` _[#if !(COMPILE_SIGNAL_COLOR_SH)]_
- L3 #pragma `once`

#### Structs / classes (1)

- L18-22 _struct_ **`FSSDCompressedSignalSample`** `struct FSSDCompressedSignalSample` — Generic data structure to store a signal sample in a compressed form.
  - L21 _member_ `uint VGPR[MAX_SIGNAL_COMPRESSED_VGPRS];` — Raw array of vector general purpose registers used to store signal.

#### Functions (3)

- L26-54 _function_ `void CompressSignalSample(in FSSDSignalSample Sample, uint CompressionLayout, out FSSDCompressedSignalSample OutCompressedSample)` — Compress part of signal into smaller VGPR foorprint.
- L57-80 _function_ `void UncompressSignalSample(in FSSDCompressedSignalSample CompressedSample, uint CompressionLayout, inout FSSDSignalSample OutSample)` — Decompress signal from tight VGPR layout into a sample.
- L82-89 _function_ `FSSDCompressedSignalSample CreateCompressedSignalSampleFromScalarValue(float Scalar, uint CompressionLayout)`

### `Shaders/Private/ScreenSpaceDenoise/SSDSignalCore.ush` (Private)

- lines: 496; parse: all-branches
- includes: L5 `SSDCommon.ush`

#### Macros (#define, 3)

- L9 `#define COMPILE_SIGNAL_COLOR 0` _[#if !defined(COMPILE_SIGNAL_COLOR)]_
- L13 `#define COMPILE_SIGNAL_COLOR_SH 0` _[#if !defined(COMPILE_SIGNAL_COLOR_SH)]_
- L17 `#define COMPILE_SIGNAL_COLOR_ARRAY 0` _[#if !defined(COMPILE_SIGNAL_COLOR_ARRAY)]_
- L3 #pragma `once`

#### Structs / classes (4)

- L34-58 _struct_ **`FSSDSignalSample`** `struct FSSDSignalSample` — Generic linearily filterable data structure to manipulate any kind of signal.
  - L37 _member_ `float SampleCount;` — Number of sample accumulated.
  - L41 _member_ `float4 SceneColor;` _[#if COMPILE_SIGNAL_COLOR]_
  - L46 _member_ `float3 ColorArray[COMPILE_SIGNAL_COLOR_ARRAY];` _[#if COMPILE_SIGNAL_COLOR_ARRAY]_
  - L51 _member_ `FSSDSphericalHarmonicRGB ColorSH;` _[#if COMPILE_SIGNAL_COLOR_SH]_
  - L55 _member_ `float MissCount;` — Number of ray that did not find any intersections.
  - L57 _member_ `float TransmissionDistance;`
- L61-71 _struct_ **`FSSDSignalFrequency`** `struct FSSDSignalFrequency` — Generic data structure about the frequency of a FSSDSignalSample.
  - L64 _member_ `float ClosestHitDistance;` — Hit distance of a this sample.
  - L67 _member_ `float WorldBluringRadius;` — Blur radius allowed for this sample.
  - L70 _member_ `float ConfusionFactor;` — Circle confusion multiplier.
- L74-77 _struct_ **`FSSDSignalArray`** `struct FSSDSignalArray` — Array of signal samples. Technically should be a typedef, but there is a bug in HLSL with the out operator of an array.
  - L76 _member_ `FSSDSignalSample Array[SIGNAL_ARRAY_SIZE];`
- L80-83 _struct_ **`FSSDSignalFrequencyArray`** `struct FSSDSignalFrequencyArray` — Array of signal frequencies. Technically should be a typedef, but there is a bug in HLSL with the out operator of an array.
  - L82 _member_ `FSSDSignalFrequency Array[SIGNAL_ARRAY_SIZE];`

#### Functions (20)

- L86-118 _function_ `FSSDSignalSample CreateSignalSampleFromScalarValue(float Scalar)`
- L120-127 _function_ `FSSDSignalFrequency CreateInvalidSignalFrequency()`
- L129-132 _function_ `FSSDSignalSample CreateSignalSample()`
- L134-143 _function_ `FSSDSignalArray CreateSignalArrayFromScalarValue(float Scalar)`
- L145-154 _function_ `FSSDSignalFrequencyArray CreateInvalidSignalFrequencyArray()`
- L159-179 _function_ `FSSDSignalSample MulSignal(FSSDSignalSample Sample, float Scalar)`
- L181-200 _function_ `FSSDSignalSample AddSignal(FSSDSignalSample SampleA, FSSDSignalSample SampleB)`
- L202-221 _function_ `FSSDSignalSample MinusSignal(FSSDSignalSample Sample)`
- L223-226 _function_ `FSSDSignalSample SubtractSignal(FSSDSignalSample SampleA, FSSDSignalSample SampleB)`
- L228-259 _function_ `FSSDSignalSample AbsSignal(FSSDSignalSample Sample)`
- L261-292 _function_ `FSSDSignalSample SqrtSignal(FSSDSignalSample Sample)`
- L294-328 _function_ `FSSDSignalSample PowerSignal(FSSDSignalSample Sample, float Exponent)`
- L330-362 _function_ `FSSDSignalSample MinSignal(FSSDSignalSample SampleA, FSSDSignalSample SampleB)`
- L364-396 _function_ `FSSDSignalSample MaxSignal(FSSDSignalSample SampleA, FSSDSignalSample SampleB)`
- L398-430 _function_ `FSSDSignalSample ClampSignal(FSSDSignalSample Sample, FSSDSignalSample SampleMin, FSSDSignalSample SampleMax)`
- L432-435 _function_ `FSSDSignalSample LerpSignal(FSSDSignalSample Sample0, FSSDSignalSample Sample1, float Interp)`
- L438-443 _function_ `FSSDSignalSample NormalizeToOneSample(FSSDSignalSample Sample)` — Normalize the signal sample to one.
- L445-477 _function_ `FSSDSignalSample WaveBroadcastSignal(const FWaveBroadcastSettings BroadcastSettings, FSSDSignalSample Sample)`
- L479-486 _function_ `FSSDSignalFrequency MinSignalFrequency(FSSDSignalFrequency FrequencyA, FSSDSignalFrequency FrequencyB)`
- L488-495 _function_ `FSSDSignalFrequency WaveBroadcastSignalFrequency(const FWaveBroadcastSettings BroadcastSettings, FSSDSignalFrequency Frequency)`

### `Shaders/Private/ScreenSpaceDenoise/SSDSignalFramework.ush` (Private)

- lines: 704; parse: first-branch (retry, +0 merged from all-branches pass)
- includes: L21 `SSDCommon.ush`, L22 `SSDSignalCore.ush`, L24 `DenoisingCommon.ush`, L26 `../ColorSpace.ush`, L27 `../EyeAdaptationCommon.ush`, L28 `../LightShaderParameters.ush`, L34 `SSDPublicHarmonics.ush` [!(!defined(CONFIG_SIGNAL_PROCESSING)) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK], L39 `../MonteCarlo.ush` [!(!defined(CONFIG_SIGNAL_PROCESSING)) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) ...], L40 `../BRDF.ush` [!(!defined(CONFIG_SIGNAL_PROCESSING)) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) ...], L41 `../DeferredShadingCommon.ush` [!(!defined(CONFIG_SIGNAL_PROCESSING)) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) ...], L42 `../CommonViewUniformBuffer.ush` [!(!defined(CONFIG_SIGNAL_PROCESSING)) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) ...]

#### Macros (#define, 3)

- L5 `#define EYE_ADAPTATION_LOOSE_PARAMETERS 1`
- L10 `#define CONFIG_SPECULAR_RATIO_ESTIMATOR 0` _[#if !defined(CONFIG_SPECULAR_RATIO_ESTIMATOR)]_
- L15 `#define CONFIG_COLOR_SPACE_TRANSFORMATION COLOR_SPACE_TRANSFORMATION_DISABLED` _[#if !defined(CONFIG_COLOR_SPACE_TRANSFORMATION)]_
- L3 #pragma `once`

#### Structs / classes (1)

- L59-69 _struct_ **`FSSDSignalDomainKnowledge`** `struct FSSDSignalDomainKnowledge` — Knowledge specific to the signal being.
  - L62 _member_ `FLightShaderParameters Light;` — Light specific parameters
  - L65 _member_ `float HitDistanceToWorldBluringRadius;` — Directional light specific.
  - L68 _member_ `uint LightType;` — The type of light.

#### Global parameters (uniforms) (3)

- L71 _parameter_ `float4 LightPositionAndRadius[MAX_SIGNAL_BATCH_SIZE];`
- L72 _parameter_ `float4 LightDirectionAndLength[MAX_SIGNAL_BATCH_SIZE];`
- L76 _parameter_ `uint FrameIndex;`

#### Functions (20)

- L79-107 _function_ `FSSDSignalDomainKnowledge GetSignalDomainKnowledge(uint BatchedSignalId)` — Returns the FLightShaderParameters from the root shader parameters.
- L113-116 _function_ `float Luma4(float3 Color)`
- L118-121 _function_ `float KarisHdrWeightY(float Color, float Exposure)`
- L123-126 _function_ `float KarisHdrWeightInvY(float Color, float Exposure)`
- L128-131 _function_ `float Luma_To_LumaLog(float x)`
- L134-144 _function_ `float GetSignalColorTransformationExposure()` — Returns the exposure multiplier that should be used for the color transformation of the signal.
- L147-180 _function_ `float GetSignalLuma4(FSSDSignalSample Sample, const uint Basis)` — Returns the linear color space Luma with a 4 multiplier for ALU perf reasons.
- L188-298 _function_ `FSSDSignalSample TransformSignal(FSSDSignalSample Sample, const uint SrcBasis, const uint DestBasis)` — Conveniently transform one simple from a source basis to a destination basis.
- L306-314 _function_ `float4 WeightedLerp( float4 ColorA, float WeightA, float4 ColorB, float WeightB, float Blend )` _[#if 0]_
- L319-337 _function_ `FSphericalGaussian ComputeRoughnessLobe(float Roughness, float3 N, float3 V)` — Create a spherical gaussian lob for a given roughness.
- L340-353 _function_ `FSphericalGaussian ComputeRoughnessLobe(FSSDSampleSceneInfos RefSceneMetadata)` — Create a spherical gaussian lob for a given scene metadata.
- L356-361 _function_ `float ComputeBluringOutOfFocusOfNormalizedSample(FSSDSignalFrequency SampleFrequency, FSSDSampleSceneInfos SceneMetadata)` — Compute the factor to apply to inifinity bluring radius based on the sample's hit distance.
- L364-394 _function_ `void ProjectSpecularLobeToScreenSpace( FSSDSampleSceneInfos SceneMetadata, out float2 NormalizedScreenMajorAxis, out float InifinityMajorViewportRadius, out float InifinityMinorViewportRadius)` — Project the specular lobe in screen space. Returns the major axis of the lobe anysotropy, and the inifinity bluring in ViewportUV.x space.
- L399-412 _function_ `float3 ComputeMajorLightRayDirection(FSSDSampleSceneInfos SceneMetadata, FSSDSignalDomainKnowledge DomainKnowledge)`
- L420-424 _function_ `float ComputeLightSourceRadius(FSSDSignalDomainKnowledge DomainKnowledge)`
- L432-592 _function_ `float ComputeBilateralWeight( const uint BilateralSettings, float MaxWorldBluringDistance, FSSDSignalDomainKnowledge DomainKnowledge, FSSDSampleSceneInfos RefSceneMetadata, FSSDSampleSceneInfos NeighborSceneMetadata, float3 NeighborToRefVector)` — COmpute the weight of the bilateral filter to use between a reference sample and a neighbor.
- L594-622 _function_ `float GetSignalWorldBluringRadius(FSSDSignalFrequency SampleFrequency, FSSDSampleSceneInfos SceneMetadata, FSSDSignalDomainKnowledge DomainKnowledge)`
- L667-670 _function_ `float GetSamplePenumbraSafe(FSSDSignalSample Sample)` — Returns the penumbra of this sample, or 1 if invalid.
- L673-680 _function_ `float GetSamplePenumbra(FSSDSignalSample Sample)` — Get penumbra, but be aware of NaN.
- L686-702 _function_ `FSSDSphericalHarmonicRGB ComputeSampleColorSH(FSSDSampleSceneInfos SampleSceneMetadata, FSSDSignalSample Sample, uint2 NeighborPixelCoord)` _[#if COMPILE_SIGNAL_COLOR_SH && COMPILE_SIGNAL_COLOR]_

#### Top-level macro invocations (2)

- L73 _macro_call_ `DECLARE_SCALAR_ARRAY(float, HitDistanceToWorldBluringRadius, MAX_SIGNAL_BATCH_SIZE)`
- L74 _macro_call_ `DECLARE_SCALAR_ARRAY(uint, LightType, MAX_SIGNAL_BATCH_SIZE)`

### `Shaders/Private/ScreenSpaceDenoise/SSDSpatialAccumulation.usf` (Private)

- lines: 1351; parse: all-branches
- includes: L3 `SSDDefinitions.ush`, L551 `SSDSignalFramework.ush`, L552 `SSDSignalArray.ush`, L553 `SSDSpatialKernel.ush`

#### Macros (#define, 219)

- L9 `#define STAGE_RECONSTRUCTION 0`
- L10 `#define STAGE_PRE_CONVOLUTION 1`
- L11 `#define STAGE_REJECTION_PRE_CONVOLUTION 2`
- L12 `#define STAGE_POST_FILTERING 3`
- L13 `#define STAGE_FINAL_OUTPUT 4`
- L16 `#define SAMPLE_COUNT_POLICY_DISABLED 0`
- L17 `#define SAMPLE_COUNT_POLICY_SAMPLE_ACCUMULATION_BASED 4`
- L21 `#define OUTPUT_MODE_SUM 0`
- L23 `#define OUTPUT_MODE_2MOMMENT_SUM 1`
- L26 `#define OUTPUT_MODE_DRB 2`
- L31 `#define TILE_PIXEL_SIZE 8`
- L33 `#define CONFIG_SIGNAL_PROCESSING DIM_SIGNAL_PROCESSING`
- L34 `#define CONFIG_UPSCALE DIM_UPSCALE`
- L35 `#define CONFIG_SIGNAL_BATCH_SIZE DIM_SIGNAL_BATCH_SIZE`
- L36 `#define CONFIG_DENOISE_TRANSMISSION DIM_DENOISE_TRANSMISSION`
- L40 `#define MAX_SIGNAL_BATCH_SIZE CONFIG_SIGNAL_BATCH_SIZE` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK]_
- L41 `#define SIGNAL_ARRAY_SIZE CONFIG_SIGNAL_BATCH_SIZE` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK]_
- L43 `#define CONFIG_BILATERAL_PRESET BILATERAL_PRESET_MONOCHROMATIC_PENUMBRA` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK]_
- L44 `#define CONFIG_MULTIPLEXED_SIGNALS_PER_SIGNAL_DOMAIN 1` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK]_
- L48 `#define CONFIG_SIGNAL_INPUT_LAYOUT SIGNAL_BUFFER_LAYOUT_PENUMBRA_INJESTION_NSPP` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK && DIM_STAGE == STAGE_RECONSTRUCTION]_
- L49 `#define CONFIG_SIGNAL_OUTPUT_LAYOUT SIGNAL_BUFFER_LAYOUT_PENUMBRA_HISTORY` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK && DIM_STAGE == STAGE_RECONSTRUCTION]_
- L51 `#define CONFIG_SIGNAL_INPUT_TEXTURE_TYPE SIGNAL_TEXTURE_TYPE_UINT2` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK && DIM_STAGE == STAGE_RECONSTRUCTION]_
- L52 `#define CONFIG_SIGNAL_OUTPUT_TEXTURE_TYPE SIGNAL_TEXTURE_TYPE_FLOAT4` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK && DIM_STAGE == STAGE_RECONSTRUCTION]_
- L53 `#define CONFIG_INPUT_TEXTURE_COUNT ((CONFIG_SIGNAL_BATCH_SIZE + 1) / 2)` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK && DIM_STAGE == STAGE_RECONSTRUCTION]_
- L54 `#define CONFIG_OUTPUT_TEXTURE_COUNT CONFIG_SIGNAL_BATCH_SIZE` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK && DIM_STAGE == STAGE_RECONSTRUCTION]_
- L56 `#define CONFIG_SAMPLE_SET SAMPLE_SET_STACKOWIAK_4_SETS` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK && DIM_STAGE == STAGE_RECONSTRUCTION]_
- L57 `#define CONFIG_BILATERAL_DISTANCE_COMPUTATION SIGNAL_WORLD_FREQUENCY_PRECOMPUTED_BLURING_RADIUS` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK && DIM_STAGE == STAGE_RECONSTRUCTION]_
- L58 `#define CONFIG_MAX_WITH_REF_DISTANCE 1` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK && DIM_STAGE == STAGE_RECONSTRUCTION]_
- L59 `#define CONFIG_OUTPUT_MODE OUTPUT_MODE_DRB` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK && DIM_STAGE == STAGE_RECONSTRUCTION]_
- L62 `#define CONFIG_CLAMP_UV_PER_SIGNAL 1` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK && DIM_STAGE == STAGE_RECONSTRUCTION && DIM_SIGNAL_BATCH_SIZE > 1]_
- L67 `#define CONFIG_SIGNAL_INPUT_LAYOUT SIGNAL_BUFFER_LAYOUT_PENUMBRA_HISTORY` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK && !(DIM_STAGE == STAGE_RECONSTRUCTION) && DIM_STAGE == STAGE_PRE_CONVOLUTION]_
- L68 `#define CONFIG_SIGNAL_OUTPUT_LAYOUT SIGNAL_BUFFER_LAYOUT_PENUMBRA_HISTORY` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK && !(DIM_STAGE == STAGE_RECONSTRUCTION) && DIM_STAGE == STAGE_PRE_CONVOLUTION]_
- L70 `#define CONFIG_SIGNAL_INPUT_TEXTURE_TYPE SIGNAL_TEXTURE_TYPE_FLOAT4` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK && !(DIM_STAGE == STAGE_RECONSTRUCTION) && DIM_STAGE == STAGE_PRE_CONVOLUTION]_
- L71 `#define CONFIG_SIGNAL_OUTPUT_TEXTURE_TYPE SIGNAL_TEXTURE_TYPE_FLOAT4` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK && !(DIM_STAGE == STAGE_RECONSTRUCTION) && DIM_STAGE == STAGE_PRE_CONVOLUTION]_
- L73 `#define CONFIG_INPUT_TEXTURE_COUNT CONFIG_SIGNAL_BATCH_SIZE` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK && !(DIM_STAGE == STAGE_RECONSTRUCTION) && DIM_STAGE == STAGE_PRE_CONVOLUTION]_
- L74 `#define CONFIG_OUTPUT_TEXTURE_COUNT CONFIG_SIGNAL_BATCH_SIZE` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK && !(DIM_STAGE == STAGE_RECONSTRUCTION) && DIM_STAGE == STAGE_PRE_CONVOLUTION]_
- L76 `#define CONFIG_SAMPLE_SET SAMPLE_SET_HEXAWEB` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK && !(DIM_STAGE == STAGE_RECONSTRUCTION) && DIM_STAGE == STAGE_PRE_CONVOLUTION]_
- L77 `#define CONFIG_CUSTOM_SPREAD_FACTOR 1` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK && !(DIM_STAGE == STAGE_RECONSTRUCTION) && DIM_STAGE == STAGE_PRE_CONVOLUTION]_
- L79 `#define CONFIG_BILATERAL_DISTANCE_COMPUTATION SIGNAL_WORLD_FREQUENCY_PRECOMPUTED_BLURING_RADIUS` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK && !(DIM_STAGE == STAGE_RECONSTRUCTION) && DIM_STAGE == STAGE_PRE_CONVOLUTION]_
- L80 `#define CONFIG_MAX_WITH_REF_DISTANCE 1` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK && !(DIM_STAGE == STAGE_RECONSTRUCTION) && DIM_STAGE == STAGE_PRE_CONVOLUTION]_
- L81 `#define CONFIG_OUTPUT_MODE OUTPUT_MODE_DRB` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK && !(DIM_STAGE == STAGE_RECONSTRUCTION) && DIM_STAGE == STAGE_PRE_CONVOLUTION]_
- L84 `#define CONFIG_SIGNAL_INPUT_TEXTURE_TYPE SIGNAL_TEXTURE_TYPE_FLOAT4` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK && !(DIM_STAGE == STAGE_RECONSTRUCTION) && !(DIM_STAGE == STAGE_PRE_CONVOLUTION) && DIM_STAGE == STAGE_REJECTION_PRE_CONVOLUTION]_
- L85 `#define CONFIG_SIGNAL_OUTPUT_TEXTURE_TYPE SIGNAL_TEXTURE_TYPE_FLOAT4` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK && !(DIM_STAGE == STAGE_RECONSTRUCTION) && !(DIM_STAGE == STAGE_PRE_CONVOLUTION) && DIM_STAGE == STAGE_REJECTION_PRE_CONVOLUTION]_
- L89 `#define CONFIG_SIGNAL_INPUT_LAYOUT SIGNAL_BUFFER_LAYOUT_PENUMBRA_HISTORY` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK && !(DIM_STAGE == STAGE_RECONSTRUCTION) && !(DIM_STAGE == STAGE_PRE_CONVOLUTION) && !(DIM_STAGE == STAGE_REJECTION_PRE_CONVOLUTI...]_
- L90 `#define CONFIG_SIGNAL_OUTPUT_LAYOUT SIGNAL_BUFFER_LAYOUT_PENUMBRA_HISTORY` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK && !(DIM_STAGE == STAGE_RECONSTRUCTION) && !(DIM_STAGE == STAGE_PRE_CONVOLUTION) && !(DIM_STAGE == STAGE_REJECTION_PRE_CONVOLUTI...]_
- L92 `#define CONFIG_SIGNAL_INPUT_TEXTURE_TYPE SIGNAL_TEXTURE_TYPE_FLOAT4` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK && !(DIM_STAGE == STAGE_RECONSTRUCTION) && !(DIM_STAGE == STAGE_PRE_CONVOLUTION) && !(DIM_STAGE == STAGE_REJECTION_PRE_CONVOLUTI...]_
- L93 `#define CONFIG_SIGNAL_OUTPUT_TEXTURE_TYPE SIGNAL_TEXTURE_TYPE_FLOAT4` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK && !(DIM_STAGE == STAGE_RECONSTRUCTION) && !(DIM_STAGE == STAGE_PRE_CONVOLUTION) && !(DIM_STAGE == STAGE_REJECTION_PRE_CONVOLUTI...]_
- L95 `#define CONFIG_INPUT_TEXTURE_COUNT CONFIG_SIGNAL_BATCH_SIZE` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK && !(DIM_STAGE == STAGE_RECONSTRUCTION) && !(DIM_STAGE == STAGE_PRE_CONVOLUTION) && !(DIM_STAGE == STAGE_REJECTION_PRE_CONVOLUTI...]_
- L96 `#define CONFIG_OUTPUT_TEXTURE_COUNT CONFIG_SIGNAL_BATCH_SIZE` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK && !(DIM_STAGE == STAGE_RECONSTRUCTION) && !(DIM_STAGE == STAGE_PRE_CONVOLUTION) && !(DIM_STAGE == STAGE_REJECTION_PRE_CONVOLUTI...]_
- L98 `#define CONFIG_SAMPLE_SET SAMPLE_SET_STACKOWIAK_4_SETS` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK && !(DIM_STAGE == STAGE_RECONSTRUCTION) && !(DIM_STAGE == STAGE_PRE_CONVOLUTION) && !(DIM_STAGE == STAGE_REJECTION_PRE_CONVOLUTI...]_
- L100 `#define CONFIG_BILATERAL_DISTANCE_COMPUTATION SIGNAL_WORLD_FREQUENCY_PRECOMPUTED_BLURING_RADIUS` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK && !(DIM_STAGE == STAGE_RECONSTRUCTION) && !(DIM_STAGE == STAGE_PRE_CONVOLUTION) && !(DIM_STAGE == STAGE_REJECTION_PRE_CONVOLUTI...]_
- L101 `#define CONFIG_OUTPUT_MODE OUTPUT_MODE_DRB` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK && !(DIM_STAGE == STAGE_RECONSTRUCTION) && !(DIM_STAGE == STAGE_PRE_CONVOLUTION) && !(DIM_STAGE == STAGE_REJECTION_PRE_CONVOLUTI...]_
- L104 `#define CONFIG_SIGNAL_INPUT_LAYOUT SIGNAL_BUFFER_LAYOUT_PENUMBRA_HISTORY` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK && !(DIM_STAGE == STAGE_RECONSTRUCTION) && !(DIM_STAGE == STAGE_PRE_CONVOLUTION) && !(DIM_STAGE == STAGE_REJECTION_PRE_CONVOLUTI...]_
- L106 `#define CONFIG_SIGNAL_INPUT_TEXTURE_TYPE SIGNAL_TEXTURE_TYPE_FLOAT4` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK && !(DIM_STAGE == STAGE_RECONSTRUCTION) && !(DIM_STAGE == STAGE_PRE_CONVOLUTION) && !(DIM_STAGE == STAGE_REJECTION_PRE_CONVOLUTI...]_
- L107 `#define CONFIG_SIGNAL_OUTPUT_TEXTURE_TYPE SIGNAL_TEXTURE_TYPE_FLOAT4` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK && !(DIM_STAGE == STAGE_RECONSTRUCTION) && !(DIM_STAGE == STAGE_PRE_CONVOLUTION) && !(DIM_STAGE == STAGE_REJECTION_PRE_CONVOLUTI...]_
- L109 `#define CONFIG_INPUT_TEXTURE_COUNT CONFIG_SIGNAL_BATCH_SIZE` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK && !(DIM_STAGE == STAGE_RECONSTRUCTION) && !(DIM_STAGE == STAGE_PRE_CONVOLUTION) && !(DIM_STAGE == STAGE_REJECTION_PRE_CONVOLUTI...]_
- L110 `#define CONFIG_OUTPUT_TEXTURE_COUNT CONFIG_SIGNAL_BATCH_SIZE` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK && !(DIM_STAGE == STAGE_RECONSTRUCTION) && !(DIM_STAGE == STAGE_PRE_CONVOLUTION) && !(DIM_STAGE == STAGE_REJECTION_PRE_CONVOLUTI...]_
- L112 `#define CONFIG_SAMPLE_SET SAMPLE_SET_1X1` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK && !(DIM_STAGE == STAGE_RECONSTRUCTION) && !(DIM_STAGE == STAGE_PRE_CONVOLUTION) && !(DIM_STAGE == STAGE_REJECTION_PRE_CONVOLUTI...]_
- L126 `#define MAX_SIGNAL_BATCH_SIZE 2` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC]_
- L127 `#define SIGNAL_ARRAY_SIZE 2` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC]_
- L129 `#define CONFIG_SIGNAL_BATCH_SIZE 2` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC]_
- L132 `#define COMPILE_SIGNAL_COLOR_ARRAY 2` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC]_
- L134 `#define CONFIG_BILATERAL_PRESET BILATERAL_PRESET_POLYCHROMATIC_PENUMBRA` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC]_
- L135 `#define CONFIG_MULTIPLEXED_SIGNALS_PER_SIGNAL_DOMAIN 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC]_
- L138 `#define CONFIG_BILATERAL_DISTANCE_COMPUTATION SIGNAL_WORLD_FREQUENCY_HARMONIC` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC]_
- L142 `#define CONFIG_SIGNAL_INPUT_LAYOUT SIGNAL_BUFFER_LAYOUT_POLYCHROMATIC_PENUMBRA_HARMONIC_INPUT` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC && DIM_STAGE == STAGE_RECONSTRUCTION]_
- L143 `#define CONFIG_SIGNAL_OUTPUT_LAYOUT SIGNAL_BUFFER_LAYOUT_POLYCHROMATIC_PENUMBRA_HARMONIC_RECONSTRUCTION` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC && DIM_STAGE == STAGE_RECONSTRUCTION]_
- L145 `#define CONFIG_INPUT_TEXTURE_COUNT 4` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC && DIM_STAGE == STAGE_RECONSTRUCTION]_
- L146 `#define CONFIG_OUTPUT_TEXTURE_COUNT 4` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC && DIM_STAGE == STAGE_RECONSTRUCTION]_
- L148 `#define CONFIG_SAMPLE_SET SAMPLE_SET_STACKOWIAK_4_SETS` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC && DIM_STAGE == STAGE_RECONSTRUCTION]_
- L157 `#define MAX_SIGNAL_BATCH_SIZE 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PRO...]_
- L158 `#define SIGNAL_ARRAY_SIZE 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PRO...]_
- L160 `#define COMPILE_SIGNAL_COLOR 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PRO...]_
- L161 `#define CONFIG_BILATERAL_PRESET BILATERAL_PRESET_REFLECTIONS` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PRO...]_
- L164 `#define SIGNAL_ARRAY_SIZE 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PRO...]_
- L168 `#define CONFIG_INPUT_TEXTURE_COUNT 2` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PRO...]_
- L169 `#define CONFIG_SIGNAL_INPUT_LAYOUT SIGNAL_BUFFER_LAYOUT_REFLECTIONS_INPUT` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PRO...]_
- L171 `#define CONFIG_INPUT_TEXTURE_COUNT 2` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PRO...]_
- L172 `#define CONFIG_SIGNAL_INPUT_LAYOUT SIGNAL_BUFFER_LAYOUT_REFLECTIONS_HISTORY` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PRO...]_
- L174 `#define CONFIG_SIGNAL_OUTPUT_LAYOUT SIGNAL_BUFFER_LAYOUT_REFLECTIONS_HISTORY` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PRO...]_
- L175 `#define CONFIG_OUTPUT_TEXTURE_COUNT 2` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PRO...]_
- L177 `#define CONFIG_SAMPLE_SET SAMPLE_SET_DIRECTIONAL_ELLIPSE` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PRO...]_
- L181 `#define CONFIG_ACCUMULATION_COLOR_SPACE (COLOR_SPACE_RGB \| COLOR_SPACE_KARIS_WEIGHTING)` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PRO...]_
- L189 `#define MAX_SIGNAL_BATCH_SIZE 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L192 `#define SIGNAL_ARRAY_SIZE 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L195 `#define CONFIG_SIGNAL_INPUT_LAYOUT SIGNAL_BUFFER_LAYOUT_AO_INPUT` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L196 `#define CONFIG_SIGNAL_OUTPUT_LAYOUT SIGNAL_BUFFER_LAYOUT_AO_HISTORY` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L198 `#define CONFIG_INPUT_TEXTURE_COUNT 2` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L199 `#define CONFIG_OUTPUT_TEXTURE_COUNT 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L201 `#define CONFIG_SAMPLE_SET SAMPLE_SET_STACKOWIAK_4_SETS` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L202 `#define CONFIG_OUTPUT_MODE OUTPUT_MODE_DRB` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L204 `#define CONFIG_BILATERAL_PRESET BILATERAL_PRESET_AO` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L207 `#define SIGNAL_ARRAY_SIZE 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L210 `#define CONFIG_SIGNAL_INPUT_LAYOUT SIGNAL_BUFFER_LAYOUT_AO_HISTORY` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L211 `#define CONFIG_SIGNAL_OUTPUT_LAYOUT SIGNAL_BUFFER_LAYOUT_AO_HISTORY` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L213 `#define CONFIG_INPUT_TEXTURE_COUNT 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L214 `#define CONFIG_OUTPUT_TEXTURE_COUNT 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L216 `#define CONFIG_SAMPLE_SET SAMPLE_SET_HEXAWEB` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L217 `#define CONFIG_CUSTOM_SPREAD_FACTOR 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L220 `#define CONFIG_OUTPUT_MODE OUTPUT_MODE_DRB` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L222 `#define CONFIG_BILATERAL_PRESET BILATERAL_PRESET_AO` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L225 `#define SIGNAL_ARRAY_SIZE 2` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L228 `#define CONFIG_SIGNAL_INPUT_LAYOUT SIGNAL_BUFFER_LAYOUT_AO_HISTORY` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L229 `#define CONFIG_SIGNAL_OUTPUT_LAYOUT SIGNAL_BUFFER_LAYOUT_AO_REJECTION` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L231 `#define CONFIG_INPUT_TEXTURE_COUNT 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L232 `#define CONFIG_OUTPUT_TEXTURE_COUNT 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L234 `#define CONFIG_BILATERAL_PRESET BILATERAL_PRESET_AO_HISTORY` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L237 `#define SIGNAL_ARRAY_SIZE 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L240 `#define CONFIG_SIGNAL_INPUT_LAYOUT SIGNAL_BUFFER_LAYOUT_AO_HISTORY` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L241 `#define CONFIG_SIGNAL_OUTPUT_LAYOUT SIGNAL_BUFFER_LAYOUT_AO_HISTORY` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L243 `#define CONFIG_INPUT_TEXTURE_COUNT 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L244 `#define CONFIG_OUTPUT_TEXTURE_COUNT 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L246 `#define CONFIG_SAMPLE_SET SAMPLE_SET_HEXAWEB` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L247 `#define CONFIG_OUTPUT_MODE OUTPUT_MODE_DRB` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L248 `#define CONFIG_CUSTOM_SPREAD_FACTOR 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L250 `#define CONFIG_SAMPLE_COUNT_POLICY SAMPLE_COUNT_POLICY_SAMPLE_ACCUMULATION_BASED` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L252 `#define CONFIG_BILATERAL_PRESET BILATERAL_PRESET_AO` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L260 `#define MAX_SIGNAL_BATCH_SIZE 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L261 `#define SIGNAL_ARRAY_SIZE 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L263 `#define COMPILE_SIGNAL_COLOR 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L265 `#define CONFIG_BILATERAL_PRESET BILATERAL_PRESET_DIFFUSE` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L267 `#define CONFIG_INPUT_TEXTURE_COUNT 2` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L268 `#define CONFIG_OUTPUT_TEXTURE_COUNT 2` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L272 `#define CONFIG_SIGNAL_INPUT_LAYOUT SIGNAL_BUFFER_LAYOUT_DIFFUSE_INDIRECT_AND_AO_INPUT_NSPP` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L273 `#define CONFIG_SIGNAL_OUTPUT_LAYOUT SIGNAL_BUFFER_LAYOUT_DIFFUSE_INDIRECT_AND_AO_RECONSTRUCTION` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L275 `#define CONFIG_SAMPLE_SET SAMPLE_SET_STACKOWIAK_4_SETS` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L277 `#define CONFIG_BILATERAL_DISTANCE_COMPUTATION SIGNAL_WORLD_FREQUENCY_HIT_DISTANCE` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L281 `#define CONFIG_SIGNAL_INPUT_LAYOUT SIGNAL_BUFFER_LAYOUT_DIFFUSE_INDIRECT_AND_AO_RECONSTRUCTION` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L282 `#define CONFIG_SIGNAL_OUTPUT_LAYOUT SIGNAL_BUFFER_LAYOUT_DIFFUSE_INDIRECT_AND_AO_RECONSTRUCTION` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L284 `#define CONFIG_SAMPLE_SET SAMPLE_SET_HEXAWEB` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L285 `#define CONFIG_CUSTOM_SPREAD_FACTOR 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L290 `#define CONFIG_SIGNAL_INPUT_LAYOUT SIGNAL_BUFFER_LAYOUT_DIFFUSE_INDIRECT_AND_AO_HISTORY` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L291 `#define CONFIG_SIGNAL_OUTPUT_LAYOUT SIGNAL_BUFFER_LAYOUT_DIFFUSE_INDIRECT_AND_AO_HISTORY` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L293 `#define CONFIG_SAMPLE_SET SAMPLE_SET_STACKOWIAK_4_SETS` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L294 `#define CONFIG_SAMPLE_SUBSET 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L296 `#define CONFIG_SAMPLE_COUNT_POLICY SAMPLE_COUNT_POLICY_SAMPLE_ACCUMULATION_BASED` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L303 `#define MAX_SIGNAL_BATCH_SIZE 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L304 `#define SIGNAL_ARRAY_SIZE 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L306 `#define COMPILE_SIGNAL_COLOR_SH 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L309 `#define CONFIG_BILATERAL_PRESET BILATERAL_PRESET_SPHERICAL_HARMONIC` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L311 `#define CONFIG_INPUT_TEXTURE_COUNT 4` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L312 `#define CONFIG_OUTPUT_TEXTURE_COUNT 4` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L314 `#define CONFIG_BILATERAL_DISTANCE_COMPUTATION SIGNAL_WORLD_FREQUENCY_MIN_METADATA` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L317 `#define CONFIG_SIGNAL_INPUT_LAYOUT SIGNAL_BUFFER_LAYOUT_DIFFUSE_INDIRECT_HARMONIC` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L318 `#define CONFIG_SIGNAL_INPUT_TEXTURE_TYPE SIGNAL_TEXTURE_TYPE_UINT2` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L319 `#define CONFIG_SIGNAL_OUTPUT_LAYOUT SIGNAL_BUFFER_LAYOUT_DIFFUSE_INDIRECT_HARMONIC` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L320 `#define CONFIG_SIGNAL_OUTPUT_TEXTURE_TYPE SIGNAL_TEXTURE_TYPE_UINT2` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L325 `#define CONFIG_SIGNAL_VGPR_COMPRESSION SIGNAL_COMPRESSION_DIFFUSE_INDIRECT_HARMONIC` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L328 `#define CONFIG_SAMPLE_SET SAMPLE_SET_STACKOWIAK_4_SETS` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L337 `#define MAX_SIGNAL_BATCH_SIZE 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L338 `#define SIGNAL_ARRAY_SIZE 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L340 `#define COMPILE_SIGNAL_COLOR_SH 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L343 `#define CONFIG_BILATERAL_DISTANCE_COMPUTATION SIGNAL_WORLD_FREQUENCY_MIN_METADATA` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L344 `#define CONFIG_BILATERAL_PRESET BILATERAL_PRESET_SPHERICAL_HARMONIC` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L346 `#define CONFIG_BILATERAL_DISTANCE_MULTIPLIER 6.0` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L348 `#define CONFIG_INPUT_TEXTURE_COUNT 2` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L349 `#define CONFIG_OUTPUT_TEXTURE_COUNT 2` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L352 `#define CONFIG_SIGNAL_INPUT_LAYOUT SIGNAL_BUFFER_LAYOUT_LUMEN_DIFFUSE_INPUT` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L353 `#define CONFIG_SIGNAL_OUTPUT_LAYOUT SIGNAL_BUFFER_LAYOUT_LUMEN_DIFFUSE_HISTORY` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L357 `#define CONFIG_SAMPLE_SET SAMPLE_SET_RAW_EXPERIMENTAL_KERNEL` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L365 `#define MAX_SIGNAL_BATCH_SIZE 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L366 `#define SIGNAL_ARRAY_SIZE 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L368 `#define COMPILE_SIGNAL_COLOR 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L370 `#define CONFIG_BILATERAL_PRESET BILATERAL_PRESET_DIFFUSE` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L374 `#define CONFIG_BILATERAL_DISTANCE_MULTIPLIER 3.0` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L376 `#define CONFIG_INPUT_TEXTURE_COUNT 2` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L377 `#define CONFIG_OUTPUT_TEXTURE_COUNT 2` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L381 `#define CONFIG_SIGNAL_INPUT_LAYOUT SIGNAL_BUFFER_LAYOUT_SSGI_INPUT` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L383 `#define CONFIG_SIGNAL_OUTPUT_LAYOUT SIGNAL_BUFFER_LAYOUT_SSGI_HISTORY_R11G11B10` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L385 `#define CONFIG_SAMPLE_SET SAMPLE_SET_STACKOWIAK_4_SETS` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L394 `#define MAX_SIGNAL_BATCH_SIZE 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L395 `#define SIGNAL_ARRAY_SIZE 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L396 `#define CONFIG_MULTIPLEXED_SIGNALS_PER_SIGNAL_DOMAIN 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L398 `#define COMPILE_SIGNAL_COLOR_ARRAY 2` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L400 `#define CONFIG_BILATERAL_PRESET BILATERAL_PRESET_PROBE_HIERARCHY` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L404 `#define CONFIG_BILATERAL_DISTANCE_MULTIPLIER 3.0` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L406 `#define CONFIG_INPUT_TEXTURE_COUNT 2` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L407 `#define CONFIG_OUTPUT_TEXTURE_COUNT 2` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L411 `#define CONFIG_SIGNAL_INPUT_LAYOUT SIGNAL_BUFFER_LAYOUT_DIFFUSE_PROBE_HIERARCHY_INPUT` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L413 `#define CONFIG_SIGNAL_OUTPUT_LAYOUT SIGNAL_BUFFER_LAYOUT_DIFFUSE_PROBE_HIERARCHY_HISTORY` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L416 `#define CONFIG_SAMPLE_SET SAMPLE_SET_1X1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L428 `#define CONFIG_SAMPLE_SET SAMPLE_SET_3X3_PLUS` _[#if DIM_STAGE == STAGE_REJECTION_PRE_CONVOLUTION]_
- L431 `#define CONFIG_NORMALIZE_INPUT 1` _[#if DIM_STAGE == STAGE_REJECTION_PRE_CONVOLUTION]_
- L435 `#define CONFIG_OUTPUT_MODE OUTPUT_MODE_2MOMMENT_SUM` _[#if DIM_STAGE == STAGE_REJECTION_PRE_CONVOLUTION]_
- L448 `#define CONFIG_CLAMP_UV_PER_SIGNAL 0` _[#if !defined(CONFIG_CLAMP_UV_PER_SIGNAL)]_
- L453 `#define CONFIG_SAMPLE_COUNT_POLICY SAMPLE_COUNT_POLICY_DISABLED` _[#if !defined(CONFIG_SAMPLE_COUNT_POLICY)]_
- L458 `#define CONFIG_SAMPLE_SUBSET 0` _[#if !defined(CONFIG_SAMPLE_SUBSET)]_
- L463 `#define CONFIG_UPSCALE 0` _[#if !defined(CONFIG_UPSCALE)]_
- L468 `#define CONFIG_INPUT_COLOR_SPACE STANDARD_BUFFER_COLOR_SPACE` _[#if !defined(CONFIG_INPUT_COLOR_SPACE)]_
- L473 `#define CONFIG_ACCUMULATION_COLOR_SPACE STANDARD_BUFFER_COLOR_SPACE` _[#if !defined(CONFIG_ACCUMULATION_COLOR_SPACE)]_
- L478 `#define CONFIG_OUTPUT_COLOR_SPACE STANDARD_BUFFER_COLOR_SPACE` _[#if !defined(CONFIG_OUTPUT_COLOR_SPACE)]_
- L483 `#define CONFIG_REJECT_HIGHEST_COLOR 0` _[#if !defined(CONFIG_REJECT_HIGHEST_COLOR)]_
- L488 `#define CONFIG_NORMALIZE_INPUT 0` _[#if !defined(CONFIG_NORMALIZE_INPUT)]_
- L493 `#define CONFIG_OUTPUT_MODE OUTPUT_MODE_SUM` _[#if !defined(CONFIG_OUTPUT_MODE)]_
- L498 `#define CONFIG_MULTIPLEXED_SIGNALS_PER_SIGNAL_DOMAIN SIGNAL_ARRAY_SIZE` _[#if !defined(CONFIG_MULTIPLEXED_SIGNALS_PER_SIGNAL_DOMAIN)]_
- L503 `#define CONFIG_BILATERAL_DISTANCE_COMPUTATION SIGNAL_WORLD_FREQUENCY_MIN_METADATA` _[#if !defined(CONFIG_BILATERAL_DISTANCE_COMPUTATION)]_
- L508 `#define CONFIG_BILATERAL_DISTANCE_MULTIPLIER 1.0` _[#if !defined(CONFIG_BILATERAL_DISTANCE_MULTIPLIER)]_
- L513 `#define CONFIG_MAX_WITH_REF_DISTANCE 0` _[#if !defined(CONFIG_MAX_WITH_REF_DISTANCE)]_
- L521 `#define COMPILE_STACKOWIAK_KERNEL 1` _[#if CONFIG_SAMPLE_SET == SAMPLE_SET_STACKOWIAK_4_SETS]_
- L523 `#define COMPILE_DISK_KERNEL 1` _[#if !(CONFIG_SAMPLE_SET == SAMPLE_SET_STACKOWIAK_4_SETS) && CONFIG_SAMPLE_SET == SAMPLE_SET_HEXAWEB]_
- L525 `#define COMPILE_DIRECTIONAL_KERNEL 1` _[#if !(CONFIG_SAMPLE_SET == SAMPLE_SET_STACKOWIAK_4_SETS) && !(CONFIG_SAMPLE_SET == SAMPLE_SET_HEXAWEB) && CONFIG_SAMPLE_SET == SAMPLE_SET_DIRECTIONAL_RECT \|\| CONFIG_SAMPLE_SET == SAMPLE_SET_DIRECTIONAL...]_
- L527 `#define COMPILE_RAW_EXPERIMENTAL_KERNEL 1` _[#if !(CONFIG_SAMPLE_SET == SAMPLE_SET_STACKOWIAK_4_SETS) && !(CONFIG_SAMPLE_SET == SAMPLE_SET_HEXAWEB) && !(CONFIG_SAMPLE_SET == SAMPLE_SET_DIRECTIONAL_RECT \|\| CONFIG_SAMPLE_SET == SAMPLE_SET_DIRECTION...]_
- L529 `#define COMPILE_BOX_KERNEL 1` _[#if !(CONFIG_SAMPLE_SET == SAMPLE_SET_STACKOWIAK_4_SETS) && !(CONFIG_SAMPLE_SET == SAMPLE_SET_HEXAWEB) && !(CONFIG_SAMPLE_SET == SAMPLE_SET_DIRECTIONAL_RECT \|\| CONFIG_SAMPLE_SET == SAMPLE_SET_DIRECTION...]_
- L534 `#define COMPILE_DRB_ACCUMULATOR 1` _[#if CONFIG_OUTPUT_MODE == OUTPUT_MODE_DRB]_
- L535 `#define COMPILE_MIN_FREQUENCY_ACCUMULATOR 1` _[#if CONFIG_OUTPUT_MODE == OUTPUT_MODE_DRB]_
- L538 `#define COMPILE_MOMENT1_ACCUMULATOR 1` _[#if !(CONFIG_OUTPUT_MODE == OUTPUT_MODE_DRB) && CONFIG_OUTPUT_MODE == OUTPUT_MODE_2MOMMENT_SUM]_
- L539 `#define COMPILE_MOMENT2_ACCUMULATOR 1` _[#if !(CONFIG_OUTPUT_MODE == OUTPUT_MODE_DRB) && CONFIG_OUTPUT_MODE == OUTPUT_MODE_2MOMMENT_SUM]_
- L542 `#define COMPILE_MOMENT1_ACCUMULATOR 1` _[#if !(CONFIG_OUTPUT_MODE == OUTPUT_MODE_DRB) && !(CONFIG_OUTPUT_MODE == OUTPUT_MODE_2MOMMENT_SUM) && CONFIG_OUTPUT_MODE == OUTPUT_MODE_SUM]_
- L543 `#define COMPILE_MIN_FREQUENCY_ACCUMULATOR 1` _[#if !(CONFIG_OUTPUT_MODE == OUTPUT_MODE_DRB) && !(CONFIG_OUTPUT_MODE == OUTPUT_MODE_2MOMMENT_SUM) && CONFIG_OUTPUT_MODE == OUTPUT_MODE_SUM]_
- L560 `#define CONFIG_REF_METADATA_COMPRESSION CONFIG_METADATA_BUFFER_LAYOUT` _[#if !defined(CONFIG_REF_METADATA_COMPRESSION)]_
- L590 `#define SignalInput_Textures_1 SignalInput_Textures_0` _[#if !(CONFIG_INPUT_TEXTURE_COUNT > 1)]_
- L591 `#define SignalInputUint_Textures_1 SignalInputUint_Textures_0` _[#if !(CONFIG_INPUT_TEXTURE_COUNT > 1)]_
- L598 `#define SignalInput_Textures_2 SignalInput_Textures_0` _[#if !(CONFIG_INPUT_TEXTURE_COUNT > 2)]_
- L599 `#define SignalInputUint_Textures_2 SignalInputUint_Textures_0` _[#if !(CONFIG_INPUT_TEXTURE_COUNT > 2)]_
- L606 `#define SignalInput_Textures_3 SignalInput_Textures_0` _[#if !(CONFIG_INPUT_TEXTURE_COUNT > 3)]_
- L607 `#define SignalInputUint_Textures_3 SignalInputUint_Textures_0` _[#if !(CONFIG_INPUT_TEXTURE_COUNT > 3)]_
- L638 `#define SignalOutput_UAVs_1 SignalOutput_UAVs_0` _[#if !(CONFIG_OUTPUT_TEXTURE_COUNT > 1)]_
- L644 `#define SignalOutput_UAVs_2 SignalOutput_UAVs_0` _[#if !(CONFIG_OUTPUT_TEXTURE_COUNT > 2)]_
- L650 `#define SignalOutput_UAVs_3 SignalOutput_UAVs_0` _[#if !(CONFIG_OUTPUT_TEXTURE_COUNT > 3)]_
- L128 #undef `CONFIG_SIGNAL_BATCH_SIZE`

#### Entry points (1)

- L670-1350 _entry_ `[numthreads(TILE_PIXEL_SIZE, TILE_PIXEL_SIZE, 1)] void MainCS( uint2 DispatchThreadId : SV_DispatchThreadID, uint2 GroupId : SV_GroupID, uint2 GroupThreadId : SV_GroupThreadID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FSSDSpatialAccumulationCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/ScreenSpaceDenoise.cpp:1254)

#### Global resources (textures / buffers / samplers) (4)

- L614 _resource_ `Texture2D OriginalInput_Textures_0;` _[#if DIM_STAGE == STAGE_FINAL_OUTPUT && CONFIG_SIGNAL_PROCESS == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK && !CONFIG_DENOISE_TRANSMISSION]_
- L617 _resource_ `Texture2D OriginalInput_Textures_1;` _[#if DIM_STAGE == STAGE_FINAL_OUTPUT && CONFIG_SIGNAL_PROCESS == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK && !CONFIG_DENOISE_TRANSMISSION && CONFIG_INPUT_TEXTURE_COUNT > 1]_
- L621 _resource_ `Texture2D OriginalInput_Textures_2;` _[#if DIM_STAGE == STAGE_FINAL_OUTPUT && CONFIG_SIGNAL_PROCESS == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK && !CONFIG_DENOISE_TRANSMISSION && CONFIG_INPUT_TEXTURE_COUNT > 2]_
- L625 _resource_ `Texture2D OriginalInput_Textures_3;` _[#if DIM_STAGE == STAGE_FINAL_OUTPUT && CONFIG_SIGNAL_PROCESS == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK && !CONFIG_DENOISE_TRANSMISSION && CONFIG_INPUT_TEXTURE_COUNT > 3]_

#### Global parameters (uniforms) (18)

- L566 _parameter_ `uint MaxSampleCount;`
- L567 _parameter_ `uint PreviousCumulativeMaxSampleCount;`
- L568 _parameter_ `uint UpscaleFactor;`
- L571 _parameter_ `float KernelSpreadFactor;` _[#if !CONFIG_UPSCALE && CONFIG_CUSTOM_SPREAD_FACTOR]_
- L574 _parameter_ `float HarmonicPeriode;`
- L576 _parameter_ `float4 InputBufferUVMinMax[CONFIG_SIGNAL_BATCH_SIZE];`
- L583 _parameter_ `FSSDTexture2D SignalInput_Textures_0;`
- L584 _parameter_ `FSSDTexture2D SignalInputUint_Textures_0;`
- L587 _parameter_ `FSSDTexture2D SignalInput_Textures_1;` _[#if CONFIG_INPUT_TEXTURE_COUNT > 1]_
- L588 _parameter_ `FSSDTexture2D SignalInputUint_Textures_1;` _[#if CONFIG_INPUT_TEXTURE_COUNT > 1]_
- L595 _parameter_ `FSSDTexture2D SignalInput_Textures_2;` _[#if CONFIG_INPUT_TEXTURE_COUNT > 2]_
- L596 _parameter_ `FSSDTexture2D SignalInputUint_Textures_2;` _[#if CONFIG_INPUT_TEXTURE_COUNT > 2]_
- L603 _parameter_ `FSSDTexture2D SignalInput_Textures_3;` _[#if CONFIG_INPUT_TEXTURE_COUNT > 3]_
- L604 _parameter_ `FSSDTexture2D SignalInputUint_Textures_3;` _[#if CONFIG_INPUT_TEXTURE_COUNT > 3]_
- L633 _parameter_ `FSSDRWTexture2D SignalOutput_UAVs_0;`
- L636 _parameter_ `FSSDRWTexture2D SignalOutput_UAVs_1;` _[#if CONFIG_OUTPUT_TEXTURE_COUNT > 1]_
- L642 _parameter_ `FSSDRWTexture2D SignalOutput_UAVs_2;` _[#if CONFIG_OUTPUT_TEXTURE_COUNT > 2]_
- L648 _parameter_ `FSSDRWTexture2D SignalOutput_UAVs_3;` _[#if CONFIG_OUTPUT_TEXTURE_COUNT > 3]_

#### Functions (1)

- L657-665 _function_ `uint2 GetPixelCoord(uint2 DispatchThreadId)` — TODO(Denoiser): duplicated with reflection code.

### `Shaders/Private/ScreenSpaceDenoise/SSDSpatialKernel.ush` (Private)

- lines: 2833; parse: first-branch (retry, +1 merged from all-branches pass)
- includes: L3 `SSDSignalAccumulatorArray.ush`, L4 `SSDSignalBufferEncoding.ush`, L5 `../TextureSampling.ush`, L6 `../MonteCarlo.ush`

#### Macros (#define, 14)

- L13 `#define SIGNAL_WORLD_FREQUENCY_REF_METADATA_ONLY 0`
- L16 `#define SIGNAL_WORLD_FREQUENCY_SAMPLE_METADATA_ONLY 1`
- L19 `#define SIGNAL_WORLD_FREQUENCY_MIN_METADATA 2`
- L22 `#define SIGNAL_WORLD_FREQUENCY_HIT_DISTANCE 3`
- L25 `#define SIGNAL_WORLD_FREQUENCY_PRECOMPUTED_BLURING_RADIUS 4`
- L28 `#define SIGNAL_WORLD_FREQUENCY_HARMONIC 5`
- L34 `#define CONFIG_ACCUMULATOR_VGPR_COMPRESSION ACCUMULATOR_COMPRESSION_DISABLED` _[#if !defined(CONFIG_ACCUMULATOR_VGPR_COMPRESSION)]_
- L37 `#define CONFIG_ENABLE_WAVE_BROADCAST (PLATFORM_SUPPORTS_WAVE_BROADCAST)`
- L41 `#define COMPILE_BOX_KERNEL 0` _[#if !defined(COMPILE_BOX_KERNEL)]_
- L45 `#define COMPILE_STACKOWIAK_KERNEL 0` _[#if !defined(COMPILE_STACKOWIAK_KERNEL)]_
- L49 `#define COMPILE_DISK_KERNEL 0` _[#if !defined(COMPILE_DISK_KERNEL)]_
- L53 `#define COMPILE_DIRECTIONAL_KERNEL 0` _[#if !defined(COMPILE_DIRECTIONAL_KERNEL)]_
- L57 `#define COMPILE_RAW_EXPERIMENTAL_KERNEL 0` _[#if !defined(COMPILE_RAW_EXPERIMENTAL_KERNEL)]_
- L61 `#define FORCE_IDENTICAL_COLOR_SPACE 0` _[#if !defined(FORCE_IDENTICAL_COLOR_SPACE)]_

#### Structs / classes (1)

- L67-206 _struct_ **`FSSDKernelConfig`** `struct FSSDKernelConfig` — Configures the spatial kernel.
  - L72 _member_ `uint SampleSet;` — Compile time set of sample to use.
  - L75 _member_ `uint SampleSubSetId;` — Compile time selection of sample to use.
  - L78 _member_ `uint BufferLayout;` — Compile time layout of the buffer to accumulate.
  - L81 _member_ `uint MultiplexedSignalsPerSignalDomain;` — Compile time number of multiplexed signal per signal domain.
  - L84 _member_ `uint BilateralDistanceComputation;` — Selects how the world distance should be computed for bilateral rejection at compile time.
  - L87 _member_ `uint RingCount;` — Number of ring for a disk kernel.
  - L90 _member_ `uint NeighborToRefComputation;` — Selects how the computation of world vector between the reference and neighbor should be computed.
  - L93 _member_ `uint RefSceneMetadataLayout;` — Layout of RefSceneMetadata
  - L96 _member_ `float WorldBluringDistanceMultiplier;` — Multiplier applied on the world bluring distance of the signal.
  - L100 _member_ `bool bUnroll;` — Compile time configuration whether want do LOOP or UNROLL false by default to expose in user code when the shader byte code might potentially be big.
  - L103 _member_ `bool bSampleKernelCenter;` — Compile time whether the center of the kernel sample is sampled.
  - L106 _member_ `bool bPreviousFrameMetadata;` — Compile time whether sampling previous frame or current frame metadata.
  - L109 _member_ `bool bPreviousFrameRefMetadata;` — Compile time whether reference metadata is current frame or previous frame.
  - L112 _member_ `bool bDescOrder;` — The sample should be accumulated starting from the further away.
  - L115 _member_ `bool bNormalizeSample;` — Whether a sample should be normalised to 1 before accmulation.
  - L119 _member_ `bool bMinSamplePairInvFrequency;` — Whether should min sample frequency of pair of samples [ Jimenez 2014, "Next Generation Post Processing in Call of Duty: Advanced Warfare" ]
  - L122 _member_ `bool bMaxWithRefBilateralDistance;` — Whether the bilateral distance should be maxed with reference bilateral distance.
  - L125 _member_ `bool bComputeSampleColorSH;` — Whether the spherical harmonic of a sample should be computed before accumulation.
  - L128 _member_ `bool bClampUVPerMultiplexedSignal;` — Whether should clamp the UV individually per signal.
  - L131 _member_ `uint BufferColorSpace[SIGNAL_ARRAY_SIZE];` — The color space that has been encoded in the buffer.
  - L134 _member_ `uint AccumulatorColorSpace[SIGNAL_ARRAY_SIZE];` — The color space of the accumulation.
  - L137 _member_ `uint BilateralSettings[SIGNAL_ARRAY_SIZE];` — The color space of the accumulation.
  - L143 _member_ `float4 BufferSizeAndInvSize;` — Buffer size and inv size.
  - L144 _member_ `float4 BufferBilinearUVMinMax;`
  - L147 _member_ `float KernelSpreadFactor;` — Multiplier on the sample's offset.
  - L150 _member_ `float HarmonicPeriode;` — The periode of the harmonic being sampled.
  - L153 _member_ `float4 PerSignalUVMinMax[SIGNAL_ARRAY_SIZE];` — Buffer's min and max UV, per texture.
  - L159 _member_ `uint BoxKernelRadius;` — Number of samples should be done when doing variable box sampling.
  - L162 _member_ `uint SampleCount;` — Runtime number of samples
  - L165 _member_ `float2 BufferUV;` — Buffer coordinate of the center of the kernel.
  - L168 _member_ `FSSDCompressedSceneInfos CompressedRefSceneMetadata;` — Metadata of the scene for the bilateral therm.
  - L172 _member_ `float2 RefBufferUV;` — Buffer coordinate of the reference used for decompression. Please try to make this same as BufferUV.
  - L175 _member_ `bool bForceKernelCenterAccumulation;` — Runtime to force the first sample of the kernel to be accumulated.
  - L178 _member_ `bool bForceAllAccumulation;` — Runtime to force accumulating all sample.
  - L181 _member_ `bool bIsDynamicPixel;` — Runtime whether this pixel is dynamic object.
  - L184 _member_ `uint SampleTrackId;` — Runtime selection of a track of sample.
  - L187 _member_ `float RefBilateralDistance[SIGNAL_ARRAY_SIZE];` — Reference meta data.
  - L190 _member_ `float Randoms[1];` — Uniform random values required for stocastic kernel.
  - L193 _member_ `uint2 HammersleySeed;` — Seed for hamerley sequence used for stocastic kernel.
  - L196 _member_ `float2 MajorAxis;` — Normalized pixel space direction for directional kernels.
  - L199 _member_ `float MajorPixelRadius;` — The pixel radius along the major and minor axes for directional kernels.
  - L200 _member_ `float MinorPixelRadius;`
  - L203 _member_ `uint2 DebugPixelPosition;` _[#if DEBUG_OUTPUT]_
  - L204 _member_ `uint DebugEventCounter;` _[#if DEBUG_OUTPUT]_

#### static const (7)

- L394 _static_const_ `static const float kWaveletFilterWeights5x5[] = { 3.0 / 8.0, 1.0 / 4.0, 1.0 / 16.0 };`
- L1536-1594 _static_const_ `static const float2 kStackowiakSampleSet0[56 * 4] = { float2(-0.5, -0.5), float2(+0.5, -0.5), float2(-0.5, +0.5), float2(+0.5, +0.5), float2(-1.5, +0.5), float2(-1.5, -0.5), float2(-0.5, +1.5), float2(+1.5, -0.5), float2(+0.5, -1.5), float2(+2.5, -0.5), float2(+1.5, +0.5), float2(-0.5, -1.5), float2(-1.5, -2.5), float2(-0.5, -2.5), float2(-1.5, -1.5), float2(-0.5, +2.5), float2(-1.5, +1.5), float2(+1.5, -2.5), float2(-1.5, +2.5), float2(+1.5, +2.5), float2(+0.5, -2.5), float2(-2.5, -0.5), float2(-2.5, -1.5), float2(-2.5, +0.5), float2(+0.5, +1.5), float2(+0.5, +2.5), float2(-3.5, +0.5), float2` _[#if COMPILE_STACKOWIAK_KERNEL]_
- L1596-1654 _static_const_ `static const float2 kStackowiakSampleSet1[56 * 4] = { float2(-0.5, -0.5), float2(+0.5, -0.5), float2(-0.5, +0.5), float2(+0.5, +0.5), float2(+0.5, -1.5), float2(+1.5, -1.5), float2(-1.5, -0.5), float2(+1.5, +1.5), float2(-0.5, -2.5), float2(-1.5, -1.5), float2(+0.5, +1.5), float2(-1.5, +0.5), float2(+1.5, -0.5), float2(-0.5, +1.5), float2(-2.5, +0.5), float2(+0.5, +2.5), float2(-2.5, -1.5), float2(+2.5, +0.5), float2(+1.5, +0.5), float2(-0.5, -1.5), float2(-1.5, +1.5), float2(+2.5, -2.5), float2(-3.5, -0.5), float2(-1.5, +2.5), float2(-2.5, +1.5), float2(-2.5, -0.5), float2(-1.5, -2.5), float2` _[#if COMPILE_STACKOWIAK_KERNEL]_
- L1656 _static_const_ `static const uint kStackowiakSampleSetCount = 4;` _[#if COMPILE_STACKOWIAK_KERNEL]_
- L1657 _static_const_ `static const uint kStackowiakSampleCountPerSet = 56;` _[#if COMPILE_STACKOWIAK_KERNEL]_
- L2197-2326 _static_const_ `static const float2 SampleArray4x4x8[128] = { float2(0.000000, 0.000000), float2(1.000000, 0.000000), float2(0.000000, 1.000000), float2(2.000000, 1.000000), float2(-1.000000, 2.000000), float2(-1.000000, 1.000000), float2(1.000000, 2.000000), float2(1.000000, 1.000000), float2(0.000000, 0.000000), float2(-2.000000, 0.000000), float2(-1.000000, 1.000000), float2(0.000000, 2.000000), float2(-1.000000, 2.000000), float2(-1.000000, -1.000000), float2(0.000000, 1.000000), float2(-1.000000, 0.000000), float2(0.000000, 0.000000), float2(1.000000, -1.000000), float2(1.000000, 2.000000), float2(0.0000` _[#if COMPILE_RAW_EXPERIMENTAL_KERNEL && 0]_
- L2330-2587 _static_const_ `static const float2 SampleArray4x4x16[256] = { float2(0.000000, 0.000000), float2(-1.000000, -1.000000), float2(1.000000, -1.000000), float2(-1.000000, 0.000000), float2(0.000000, -1.000000), float2(1.000000, 0.000000), float2(-2.000000, 1.000000), float2(2.000000, -1.000000), float2(1.000000, 1.000000), float2(-1.000000, -2.000000), float2(2.000000, 0.000000), float2(0.000000, 1.000000), float2(0.000000, 2.000000), float2(2.000000, 2.000000), float2(2.000000, -2.000000), float2(1.000000, 2.000000), float2(0.000000, 0.000000), float2(-1.000000, 0.000000), float2(2.000000, 3.000000), float2(-1.` _[#if COMPILE_RAW_EXPERIMENTAL_KERNEL && !(0)]_

#### Functions (33)

- L208-294 _function_ `FSSDKernelConfig CreateKernelConfig()`
- L297-389 _function_ `void SetBilateralPreset(uint BilateralPresetId, inout FSSDKernelConfig KernelConfig)`
- L400-427 _function_ `ISOLATE float2 ComputeRefBufferUV(FSSDKernelConfig KernelConfig)` — Deduce the buffer UV of the output pixel this kernel has been configured for.
- L430-451 _function_ `ISOLATE FSSDSampleSceneInfos UncompressRefSceneMetadata(FSSDKernelConfig KernelConfig)` — Uncompress the reference scene metadata to keep a low VGPR pressure.
- L454-473 _function_ `FSSDSampleSceneInfos UncompressSampleSceneMetadata( FSSDKernelConfig KernelConfig, float2 SampleBufferUV, FSSDCompressedSceneInfos CompressedSampleSceneMetadata)` — Uncompress the scene metadata of a sample.
- L475-511 _function_ `float3 ComputeVectorFromNeighborToRef( FSSDKernelConfig KernelConfig, FSSDSampleSceneInfos RefSceneMetadata, FSSDSampleSceneInfos NeighborSceneMetadata)`
- L516-541 _function_ `FSSDSignalSample TransformSignalSampleForAccumulation( FSSDKernelConfig KernelConfig, uint MultiplexId, FSSDSampleSceneInfos SampleSceneMetadata, FSSDSignalSample Sample, uint2 SamplePixelCoord)`
- L544-547 _function_ `uint ComputeSignalBatchIdFromSignalMultiplexId(FSSDKernelConfig KernelConfig, const uint SignalMultiplexId)` — Compute at compile time the index of the signal in the batch, from the index of the multiplexed signal.
- L550-553 _function_ `bool IsOutsideViewport(FSSDKernelConfig KernelConfig, float2 SampleBufferUV)` — Returns whether this sample is outside the viewport.
- L556-580 _function_ `void SampleMultiplexedSignals( FSSDKernelConfig KernelConfig, FSSDTexture2D SignalBuffer0, FSSDTexture2D SignalBuffer1, FSSDTexture2D SignalBuffer2, FSSDTexture2D SignalBuffer3, float2 SampleBufferUV, out FSSDCompressedSceneInfos OutCompressedSampleSceneMetadata, out FSSDCompressedMultiplexedSample OutCompressedMultiplexedSamples)` — Sample multiplexed samples and their metadata for kernel use.
- L583-613 _function_ `void UncompressMultiplexedSignals( FSSDKernelConfig KernelConfig, float2 SampleBufferUV, FSSDCompressedMultiplexedSample CompressedMultiplexedSamples, out FSSDSignalArray MultiplexedSamples, out FSSDSignalFrequencyArray MultiplexedFrequencies)` — Uncompressed multiplexed signal for accumulation.
- L616-784 _function_ `void AccumulateSampledMultiplexedSignals( FSSDKernelConfig KernelConfig, inout FSSDSignalAccumulatorArray UncompressedAccumulators, inout FSSDCompressedSignalAccumulatorArray CompressedAccumulators, FSSDSampleSceneInfos RefSceneMetadata, float2 SampleBufferUV, FSSDSampleSceneInfos SampleSceneMetadata, FSSDSignalArray MultiplexedSamples, FSSDSignalFrequencyArray MultiplexedFrequencies, float KernelSampleWeight, const bool bForceSample, bool bIsOutsideFrustum)` — Accumulate multiplexed samples and their metadata to an accumulator.
- L790-849 _function_ `void SampleAndAccumulateMultiplexedSignals( FSSDKernelConfig KernelConfig, FSSDTexture2D SignalBuffer0, FSSDTexture2D SignalBuffer1, FSSDTexture2D SignalBuffer2, FSSDTexture2D SignalBuffer3, inout FSSDSignalAccumulatorArray UncompressedAccumulators, inout FSSDCompressedSignalAccumulatorArray CompressedAccumulators, float2 SampleBufferUV, float KernelSampleWeight, const bool bForceSample)` — Sample and accumulate to accumulatore array. Caution: you probably want to explicitly do this manually to help the shader compiler to do lattency hiding.
- L851-945 _function_ `void SampleAndAccumulateMultiplexedSignalsPair( FSSDKernelConfig KernelConfig, FSSDTexture2D SignalBuffer0, FSSDTexture2D SignalBuffer1, FSSDTexture2D SignalBuffer2, FSSDTexture2D SignalBuffer3, inout FSSDSignalAccumulatorArray UncompressedAccumulators, inout FSSDCompressedSignalAccumulatorArray CompressedAccumulators, float2 SampleBufferUV[2], float KernelSampleWeight)`
- L947-982 _function_ `void StartAccumulatingCluster( FSSDKernelConfig KernelConfig, inout FSSDSignalAccumulatorArray UncompressedAccumulators, inout FSSDCompressedSignalAccumulatorArray CompressedAccumulators, FSSDSampleClusterInfo ClusterInfo)`
- L984-1014 _function_ `void DijestAccumulatedClusterSamples( inout FSSDSignalAccumulatorArray UncompressedAccumulators, inout FSSDCompressedSignalAccumulatorArray CompressedAccumulators, uint RingId, uint SampleCount)`
- L1016-1052 _function_ `void SampleAndAccumulateCenterSampleAsItsOwnCluster( FSSDKernelConfig KernelConfig, FSSDTexture2D SignalBuffer0, FSSDTexture2D SignalBuffer1, FSSDTexture2D SignalBuffer2, FSSDTexture2D SignalBuffer3, inout FSSDSignalAccumulatorArray UncompressedAccumulators, inout FSSDCompressedSignalAccumulatorArray CompressedAccumulators)`
- L1059-1161 _function_ `void AccumulateBilinear2x2Kernel( FSSDKernelConfig KernelConfig, FSSDTexture2D SignalBuffer0, FSSDTexture2D SignalBuffer1, FSSDTexture2D SignalBuffer2, FSSDTexture2D SignalBuffer3, inout FSSDSignalAccumulatorArray UncompressedAccumulators, inout FSSDCompressedSignalAccumulatorArray CompressedAccumulators)` _[#if COMPILE_BOX_KERNEL]_
- L1163-1265 _function_ `void AccumulateSquareKernel( FSSDKernelConfig KernelConfig, FSSDTexture2D SignalBuffer0, FSSDTexture2D SignalBuffer1, FSSDTexture2D SignalBuffer2, FSSDTexture2D SignalBuffer3, inout FSSDSignalAccumulatorArray UncompressedAccumulators, inout FSSDCompressedSignalAccumulatorArray CompressedAccumulators)` _[#if COMPILE_BOX_KERNEL]_
- L1267-1346 _function_ `void BroadcastAccumulateSquare3x3KernelCenter( FSSDKernelConfig KernelConfig, inout FSSDSignalAccumulatorArray UncompressedAccumulators, inout FSSDCompressedSignalAccumulatorArray CompressedAccumulators, FSSDSampleSceneInfos RefSceneMetadata, float2 SampleBufferUV, FSSDSampleSceneInfos SampleSceneMetadata, FSSDSignalArray SampleMultiplexedSamples, FSSDSignalFrequencyArray SampleMultiplexedFrequencies)` _[#if COMPILE_BOX_KERNEL]_
- L1351-1480 _function_ `void AccumulateSquare3x3Kernel( FSSDKernelConfig KernelConfig, FSSDTexture2D SignalBuffer0, FSSDTexture2D SignalBuffer1, FSSDTexture2D SignalBuffer2, FSSDTexture2D SignalBuffer3, inout FSSDSignalAccumulatorArray UncompressedAccumulators, inout FSSDCompressedSignalAccumulatorArray CompressedAccumulators)` _[#if COMPILE_BOX_KERNEL]_
- L1659-1866 _function_ `void ConvolveStackowiakKernel( FSSDKernelConfig KernelConfig, FSSDTexture2D SignalBuffer0, FSSDTexture2D SignalBuffer1, FSSDTexture2D SignalBuffer2, FSSDTexture2D SignalBuffer3, inout FSSDSignalAccumulatorArray UncompressedAccumulators, inout FSSDCompressedSignalAccumulatorArray CompressedAccumulators)` _[#if COMPILE_STACKOWIAK_KERNEL]_
- L1876-1895 _function_ `float2 GetDiskSampleOnUnitCirle(uint RingId, uint RingSampleIteration, uint RingSampleId)` — Returns the position of the sample on the unit circle (radius = 1) for a given ring. _[#if COMPILE_DISK_KERNEL]_
- L1898-1908 _function_ `float2x2 GetSampleRotationMatrix(uint RingSampleIteration)` — Returns the rotation matrix to use between sample of the ring. _[#if COMPILE_DISK_KERNEL]_
- L1911-1920 _function_ `uint GetRingSamplingPairCount(const uint SampleSet, uint RingId)` — Returns the total number of sampling iteration for a given ring id. _[#if COMPILE_DISK_KERNEL]_
- L1923-1932 _function_ `uint GetDiskKernelSampleCount(const uint SampleSet, uint RingCount)` — Returns the total number of sample of the kernel. _[#if COMPILE_DISK_KERNEL]_
- L1935-1950 _function_ `float2 SampleConstFromBatchConst(const uint BatchSampleId, float2 BatchConst)` — Transform at compile time a 2 dimensional batch's constant into sample pair constant, by using rotation invariance. _[#if COMPILE_DISK_KERNEL]_
- L1955-2036 _function_ `void GatherRingSamples( FSSDKernelConfig KernelConfig, FSSDTexture2D SignalBuffer0, FSSDTexture2D SignalBuffer1, FSSDTexture2D SignalBuffer2, FSSDTexture2D SignalBuffer3, inout FSSDSignalAccumulatorArray UncompressedAccumulators, inout FSSDCompressedSignalAccumulatorArray CompressedAccumulators, const uint RingId)` — Gather a ring into the accumulator. _[#if COMPILE_DISK_KERNEL]_
- L2038-2110 _function_ `void ConvolveDiskKernel( FSSDKernelConfig KernelConfig, FSSDTexture2D SignalBuffer0, FSSDTexture2D SignalBuffer1, FSSDTexture2D SignalBuffer2, FSSDTexture2D SignalBuffer3, inout FSSDSignalAccumulatorArray UncompressedAccumulators, inout FSSDCompressedSignalAccumulatorArray CompressedAccumulators)` _[#if COMPILE_DISK_KERNEL]_
- L2119-2188 _function_ `void ConvolveDirectionalRect( FSSDKernelConfig KernelConfig, FSSDTexture2D SignalBuffer0, FSSDTexture2D SignalBuffer1, FSSDTexture2D SignalBuffer2, FSSDTexture2D SignalBuffer3, inout FSSDSignalAccumulatorArray UncompressedAccumulators, inout FSSDCompressedSignalAccumulatorArray CompressedAccumulators)` _[#if COMPILE_DIRECTIONAL_KERNEL]_
- L2592-2652 _function_ `void ConvolveRawExperimentalKernel( FSSDKernelConfig KernelConfig, FSSDTexture2D SignalBuffer0, FSSDTexture2D SignalBuffer1, FSSDTexture2D SignalBuffer2, FSSDTexture2D SignalBuffer3, inout FSSDSignalAccumulatorArray UncompressedAccumulators, inout FSSDCompressedSignalAccumulatorArray CompressedAccumulators)` _[#if COMPILE_RAW_EXPERIMENTAL_KERNEL]_
- L2664-2708 _function_ `void AccumulateRefSampleAsKernelCenter( FSSDKernelConfig KernelConfig, inout FSSDSignalAccumulatorArray UncompressedAccumulators, inout FSSDCompressedSignalAccumulatorArray CompressedAccumulators, float2 RefBufferUV, FSSDSampleSceneInfos RefSceneMetadata, FSSDSignalArray RefMultiplexedSamples, FSSDSignalFrequencyArray RefMultiplexedFrequencies)` — Accumulate the center of the kernel when KernelConfig.bSampleKernelCenter == false. RefSceneMetadata and SampleSceneMetadata needs to be uncompressed upfront intentionally to share the uncompression with other part of the shader that might have required uncompression anyway.
- L2710-2832 _function_ `void AccumulateKernel( FSSDKernelConfig KernelConfig, FSSDTexture2D SignalBuffer0, FSSDTexture2D SignalBuffer1, FSSDTexture2D SignalBuffer2, FSSDTexture2D SignalBuffer3, inout FSSDSignalAccumulatorArray UncompressedAccumulators, inout FSSDCompressedSignalAccumulatorArray CompressedAccumulators)`

### `Shaders/Private/ScreenSpaceDenoise/SSDTemporalAccumulation.usf` (Private)

- lines: 1183; parse: all-branches
- includes: L3 `SSDDefinitions.ush`, L365 `SSDSignalFramework.ush`, L366 `SSDSignalArray.ush`, L367 `SSDSpatialKernel.ush`, L368 `../Random.ush`

#### Macros (#define, 160)

- L9 `#define REJECTION_INPUT_MODE_1UNNORMALIZED 0`
- L10 `#define REJECTION_INPUT_MODE_2PRETRANSFORMED_MOMMENTS 1`
- L13 `#define HISTORY_REJECTION_DISABLED 0`
- L14 `#define HISTORY_REJECTION_MINMAX_BOUNDARIES 1`
- L15 `#define HISTORY_REJECTION_VAR_BOUNDARIES 2`
- L20 `#define TILE_PIXEL_SIZE 8`
- L23 `#define CONFIG_SIGNAL_PROCESSING DIM_SIGNAL_PROCESSING`
- L24 `#define CONFIG_SIGNAL_BATCH_SIZE DIM_SIGNAL_BATCH_SIZE`
- L29 `#define MAX_SIGNAL_BATCH_SIZE CONFIG_SIGNAL_BATCH_SIZE` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK]_
- L30 `#define SIGNAL_ARRAY_SIZE CONFIG_SIGNAL_BATCH_SIZE` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK]_
- L32 `#define CONFIG_BILATERAL_PRESET BILATERAL_PRESET_MONOCHROMATIC_PENUMBRA` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK]_
- L33 `#define CONFIG_HISTORY_BILATERAL_PRESET BILATERAL_PRESET_MONOCHROMATIC_PENUMBRA` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK]_
- L34 `#define CONFIG_MULTIPLEXED_SIGNALS_PER_SIGNAL_DOMAIN 1` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK]_
- L36 `#define CONFIG_SIGNAL_INPUT_TEXTURE_TYPE SIGNAL_TEXTURE_TYPE_FLOAT4` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK]_
- L37 `#define CONFIG_SIGNAL_OUTPUT_TEXTURE_TYPE SIGNAL_TEXTURE_TYPE_FLOAT4` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK]_
- L39 `#define CONFIG_INPUT_TEXTURE_COUNT CONFIG_SIGNAL_BATCH_SIZE` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK]_
- L40 `#define CONFIG_HISTORY_TEXTURE_COUNT CONFIG_SIGNAL_BATCH_SIZE` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK]_
- L42 `#define CONFIG_SIGNAL_INPUT_LAYOUT SIGNAL_BUFFER_LAYOUT_PENUMBRA_HISTORY` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK]_
- L43 `#define CONFIG_SIGNAL_HISTORY_LAYOUT SIGNAL_BUFFER_LAYOUT_PENUMBRA_HISTORY` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK]_
- L45 `#define CONFIG_HISTORY_REJECTION HISTORY_REJECTION_VAR_BOUNDARIES` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK]_
- L47 `#define CONFIG_NORMALIZED_INPUT 1` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK]_
- L49 `#define CONFIG_REJECTION_SAMPLE_SET SAMPLE_SET_3X3_PLUS` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK]_
- L57 `#define CONFIG_CLAMP_UV_PER_SIGNAL 1` _[#if CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK && DIM_SIGNAL_BATCH_SIZE > 1]_
- L62 `#define MAX_SIGNAL_BATCH_SIZE 2` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC]_
- L63 `#define SIGNAL_ARRAY_SIZE 2` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC]_
- L65 `#define CONFIG_SIGNAL_BATCH_SIZE 2` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC]_
- L67 `#define COMPILE_SIGNAL_COLOR 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC]_
- L69 `#define CONFIG_BILATERAL_PRESET BILATERAL_PRESET_POLYCHROMATIC_PENUMBRA` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC]_
- L70 `#define CONFIG_HISTORY_BILATERAL_PRESET BILATERAL_PRESET_POLYCHROMATIC_PENUMBRA` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC]_
- L71 `#define CONFIG_MULTIPLEXED_SIGNALS_PER_SIGNAL_DOMAIN 2` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC]_
- L74 `#define CONFIG_SIGNAL_INPUT_LAYOUT SIGNAL_BUFFER_LAYOUT_POLYCHROMATIC_PENUMBRA_HISTORY` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC]_
- L75 `#define CONFIG_SIGNAL_HISTORY_LAYOUT SIGNAL_BUFFER_LAYOUT_POLYCHROMATIC_PENUMBRA_HISTORY` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC]_
- L76 `#define CONFIG_INPUT_TEXTURE_COUNT 2` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC]_
- L77 `#define CONFIG_HISTORY_TEXTURE_COUNT 2` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC]_
- L79 `#define CONFIG_HISTORY_REJECTION HISTORY_REJECTION_VAR_BOUNDARIES` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC]_
- L82 `#define COMPILE_SIGNAL_COLOR 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PRO...]_
- L84 `#define MAX_SIGNAL_BATCH_SIZE 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PRO...]_
- L85 `#define SIGNAL_ARRAY_SIZE 2` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PRO...]_
- L88 `#define CONFIG_SIGNAL_INPUT_LAYOUT SIGNAL_BUFFER_LAYOUT_REFLECTIONS_HISTORY` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PRO...]_
- L89 `#define CONFIG_SIGNAL_HISTORY_LAYOUT SIGNAL_BUFFER_LAYOUT_REFLECTIONS_HISTORY` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PRO...]_
- L91 `#define CONFIG_INPUT_TEXTURE_COUNT 2` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PRO...]_
- L92 `#define CONFIG_HISTORY_TEXTURE_COUNT 2` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PRO...]_
- L94 `#define CONFIG_BILATERAL_PRESET BILATERAL_PRESET_REFLECTIONS_TAA` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PRO...]_
- L95 `#define CONFIG_HISTORY_BILATERAL_PRESET BILATERAL_PRESET_REFLECTIONS_TAA` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PRO...]_
- L97 `#define CONFIG_REJECTION_SAMPLE_SET SAMPLE_SET_3X3_PLUS` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PRO...]_
- L100 `#define CONFIG_HISTORY_REJECTION HISTORY_REJECTION_VAR_BOUNDARIES` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PRO...]_
- L101 `#define CONFIG_HISTORY_REJECTION_COLOR_SPACE REFLECTIONS_REJECTION_COLOR_SPACE` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && CONFIG_SIGNAL_PROCESSING == SIGNAL_PRO...]_
- L104 `#define MAX_SIGNAL_BATCH_SIZE 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L105 `#define SIGNAL_ARRAY_SIZE 2` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L108 `#define CONFIG_SIGNAL_INPUT_LAYOUT SIGNAL_BUFFER_LAYOUT_AO_HISTORY` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L109 `#define CONFIG_SIGNAL_HISTORY_LAYOUT SIGNAL_BUFFER_LAYOUT_AO_HISTORY` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L111 `#define CONFIG_INPUT_TEXTURE_COUNT 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L112 `#define CONFIG_HISTORY_TEXTURE_COUNT 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L114 `#define CONFIG_NORMALIZED_INPUT 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L116 `#define CONFIG_HISTORY_REJECTION HISTORY_REJECTION_VAR_BOUNDARIES` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L118 `#define CONFIG_BILATERAL_PRESET BILATERAL_PRESET_AO_HISTORY` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L119 `#define CONFIG_HISTORY_BILATERAL_PRESET BILATERAL_PRESET_AO_HISTORY` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L120 `#define CONFIG_PATCH_PREV_SCENE_DEPTH 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L121 `#define CONFIG_USE_UNLIT_HISTORY_REJECTION 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L125 `#define CONFIG_USE_REJECTION_BUFFER 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L126 `#define CONFIG_SIGNAL_HISTORY_REJECTION_LAYOUT SIGNAL_BUFFER_LAYOUT_AO_REJECTION` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L127 `#define CONFIG_REJECTION_TEXTURE_COUNT 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L129 `#define CONFIG_REJECTION_INPUT_MODE REJECTION_INPUT_MODE_2PRETRANSFORMED_MOMMENTS` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L130 `#define CONFIG_REJECTION_SAMPLE_SET SAMPLE_SET_3X3_SOBEK2018` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L132 `#define CONFIG_REJECTION_SAMPLE_SET SAMPLE_SET_3X3` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L136 `#define MAX_SIGNAL_BATCH_SIZE 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L137 `#define SIGNAL_ARRAY_SIZE 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L139 `#define COMPILE_SIGNAL_COLOR 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L142 `#define CONFIG_SIGNAL_INPUT_LAYOUT SIGNAL_BUFFER_LAYOUT_DIFFUSE_INDIRECT_AND_AO_RECONSTRUCTION` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L143 `#define CONFIG_SIGNAL_HISTORY_LAYOUT SIGNAL_BUFFER_LAYOUT_DIFFUSE_INDIRECT_AND_AO_HISTORY` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L145 `#define CONFIG_INPUT_TEXTURE_COUNT 2` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L146 `#define CONFIG_HISTORY_TEXTURE_COUNT 2` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L148 `#define CONFIG_HISTORY_REJECTION HISTORY_REJECTION_MINMAX_BOUNDARIES` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L149 `#define CONFIG_MULTIPLEXED_SIGNALS_PER_SIGNAL_DOMAIN 3` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L151 `#define CONFIG_BILATERAL_PRESET BILATERAL_PRESET_DIFFUSE` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L152 `#define CONFIG_HISTORY_BILATERAL_PRESET BILATERAL_PRESET_DIFFUSE` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L155 `#define MAX_SIGNAL_BATCH_SIZE 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L156 `#define SIGNAL_ARRAY_SIZE 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L158 `#define COMPILE_SIGNAL_COLOR_SH 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L161 `#define CONFIG_SIGNAL_INPUT_LAYOUT SIGNAL_BUFFER_LAYOUT_DIFFUSE_INDIRECT_HARMONIC` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L162 `#define CONFIG_SIGNAL_INPUT_TEXTURE_TYPE SIGNAL_TEXTURE_TYPE_UINT2` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L163 `#define CONFIG_SIGNAL_HISTORY_LAYOUT SIGNAL_BUFFER_LAYOUT_DIFFUSE_INDIRECT_HARMONIC` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L164 `#define CONFIG_SIGNAL_OUTPUT_TEXTURE_TYPE SIGNAL_TEXTURE_TYPE_UINT2` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L166 `#define CONFIG_INPUT_TEXTURE_COUNT 4` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L167 `#define CONFIG_HISTORY_TEXTURE_COUNT 4` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L169 `#define CONFIG_HISTORY_REJECTION HISTORY_REJECTION_MINMAX_BOUNDARIES` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L170 `#define CONFIG_MULTIPLEXED_SIGNALS_PER_SIGNAL_DOMAIN 4` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L173 `#define CONFIG_BILATERAL_PRESET BILATERAL_PRESET_SPHERICAL_HARMONIC` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L174 `#define CONFIG_HISTORY_BILATERAL_PRESET BILATERAL_PRESET_SPHERICAL_HARMONIC` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L177 `#define MAX_SIGNAL_BATCH_SIZE 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L178 `#define SIGNAL_ARRAY_SIZE 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L180 `#define COMPILE_SIGNAL_COLOR_SH 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L183 `#define CONFIG_SIGNAL_INPUT_LAYOUT SIGNAL_BUFFER_LAYOUT_LUMEN_DIFFUSE_HISTORY` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L184 `#define CONFIG_SIGNAL_HISTORY_LAYOUT SIGNAL_BUFFER_LAYOUT_LUMEN_DIFFUSE_HISTORY` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L186 `#define CONFIG_INPUT_TEXTURE_COUNT 2` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L187 `#define CONFIG_HISTORY_TEXTURE_COUNT 2` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L189 `#define CONFIG_HISTORY_KERNEL SAMPLE_SET_2X2_STOCASTIC` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L193 `#define CONFIG_BILATERAL_PRESET BILATERAL_PRESET_SPHERICAL_HARMONIC` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L194 `#define CONFIG_HISTORY_BILATERAL_PRESET BILATERAL_PRESET_SPHERICAL_HARMONIC` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L199 `#define MAX_SIGNAL_BATCH_SIZE 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L200 `#define SIGNAL_ARRAY_SIZE 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L202 `#define COMPILE_SIGNAL_COLOR 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L203 `#define CONFIG_MULTIPLEXED_SIGNALS_PER_SIGNAL_DOMAIN 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L206 `#define CONFIG_SIGNAL_INPUT_LAYOUT SIGNAL_BUFFER_LAYOUT_SSGI_HISTORY_R11G11B10` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L207 `#define CONFIG_SIGNAL_HISTORY_LAYOUT SIGNAL_BUFFER_LAYOUT_SSGI_HISTORY_R11G11B10` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L209 `#define CONFIG_INPUT_TEXTURE_COUNT 2` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L210 `#define CONFIG_HISTORY_TEXTURE_COUNT 2` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L213 `#define CONFIG_BILATERAL_DISTANCE_MULTIPLIER 3.0` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L216 `#define CONFIG_HISTORY_KERNEL SAMPLE_SET_2X2_STOCASTIC` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L219 `#define CONFIG_HISTORY_REJECTION HISTORY_REJECTION_VAR_BOUNDARIES` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L221 `#define CONFIG_REJECTION_SAMPLE_SET SAMPLE_SET_3X3_PLUS` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L224 `#define CONFIG_BILATERAL_PRESET BILATERAL_PRESET_DIFFUSE` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L225 `#define CONFIG_HISTORY_BILATERAL_PRESET BILATERAL_PRESET_DIFFUSE` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L228 `#define MAX_SIGNAL_BATCH_SIZE 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L229 `#define SIGNAL_ARRAY_SIZE 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L230 `#define CONFIG_MULTIPLEXED_SIGNALS_PER_SIGNAL_DOMAIN 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L232 `#define COMPILE_SIGNAL_COLOR_ARRAY 2` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L235 `#define CONFIG_SIGNAL_INPUT_LAYOUT SIGNAL_BUFFER_LAYOUT_DIFFUSE_PROBE_HIERARCHY_INPUT` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L236 `#define CONFIG_SIGNAL_HISTORY_LAYOUT SIGNAL_BUFFER_LAYOUT_DIFFUSE_PROBE_HIERARCHY_HISTORY` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L238 `#define CONFIG_INPUT_TEXTURE_COUNT 2` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L239 `#define CONFIG_HISTORY_TEXTURE_COUNT 3` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L242 `#define CONFIG_BILATERAL_DISTANCE_MULTIPLIER 3.0` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L247 `#define CONFIG_HISTORY_KERNEL SAMPLE_SET_2X2_ADAPTIVE` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L250 `#define CONFIG_HISTORY_REJECTION HISTORY_REJECTION_MINMAX_BOUNDARIES` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L254 `#define CONFIG_BILATERAL_PRESET BILATERAL_PRESET_DISABLED` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L256 `#define CONFIG_PATCH_PREV_SCENE_DEPTH 1` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L257 `#define CONFIG_HISTORY_BILATERAL_PRESET BILATERAL_PRESET_PROBE_HIERARCHY` _[#if !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_SHADOW_VISIBILITY_MASK) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_PROCESSING_POLYCHROMATIC_PENUMBRA_HARMONIC) && !(CONFIG_SIGNAL_PROCESSING == SIGNAL_P...]_
- L269 `#define CONFIG_CLAMP_UV_PER_SIGNAL 0` _[#if !defined(CONFIG_CLAMP_UV_PER_SIGNAL)]_
- L274 `#define CONFIG_USE_TILE_CLASSIFICATION 0` _[#if !defined(CONFIG_USE_TILE_CLASSIFICATION)]_
- L279 `#define CONFIG_USE_REJECTION_BUFFER 0` _[#if !defined(CONFIG_USE_REJECTION_BUFFER)]_
- L280 `#define CONFIG_SIGNAL_HISTORY_REJECTION_LAYOUT CONFIG_SIGNAL_INPUT_LAYOUT` _[#if !defined(CONFIG_USE_REJECTION_BUFFER)]_
- L285 `#define CONFIG_REJECTION_INPUT_MODE REJECTION_INPUT_MODE_1UNNORMALIZED` _[#if !defined(CONFIG_REJECTION_INPUT_MODE)]_
- L290 `#define CONFIG_REJECTION_SAMPLE_SET SAMPLE_SET_NXN` _[#if !defined(CONFIG_REJECTION_SAMPLE_SET)]_
- L295 `#define CONFIG_REJECTION_BUFFER_COLOR_SPACE STANDARD_BUFFER_COLOR_SPACE` _[#if !defined(CONFIG_REJECTION_BUFFER_COLOR_SPACE)]_
- L300 `#define CONFIG_MULTIPLEXED_SIGNALS_PER_SIGNAL_DOMAIN SIGNAL_ARRAY_SIZE` _[#if !defined(CONFIG_MULTIPLEXED_SIGNALS_PER_SIGNAL_DOMAIN)]_
- L305 `#define CONFIG_HISTORY_KERNEL SAMPLE_SET_2X2_BILINEAR` _[#if !defined(CONFIG_HISTORY_KERNEL)]_
- L310 `#define CONFIG_BILATERAL_DISTANCE_MULTIPLIER 1.0` _[#if !defined(CONFIG_BILATERAL_DISTANCE_MULTIPLIER)]_
- L315 `#define CONFIG_PATCH_PREV_REF_SCENE_DEPTH 0` _[#if !defined(CONFIG_PATCH_PREV_SCENE_DEPTH)]_
- L319 `#define CONFIG_NORMALIZED_INPUT 0` _[#if !defined(CONFIG_NORMALIZED_INPUT)]_
- L324 `#define CONFIG_USE_UNLIT_HISTORY_REJECTION 0` _[#if !defined(CONFIG_USE_UNLIT_HISTORY_REJECTION)]_
- L331 `#define CONFIG_HISTORY_REJECTION HISTORY_REJECTION_DISABLED` _[#if !defined(CONFIG_HISTORY_REJECTION)]_
- L336 `#define CONFIG_HISTORY_REJECTION_COLOR_SPACE STANDARD_BUFFER_COLOR_SPACE` _[#if !defined(CONFIG_HISTORY_REJECTION_COLOR_SPACE)]_
- L341 `#define CONFIG_HISTORY_BLENDING_COLOR_SPACE STANDARD_BUFFER_COLOR_SPACE` _[#if !defined(CONFIG_HISTORY_BLENDING_COLOR_SPACE)]_
- L347 `#define COMPILE_BOX_KERNEL 1`
- L350 `#define COMPILE_MOMENT1_ACCUMULATOR 1`
- L353 `#define COMPILE_MIN_FREQUENCY_ACCUMULATOR 1` _[#if CONFIG_HISTORY_REJECTION != HISTORY_REJECTION_DISABLED]_
- L357 `#define COMPILE_MINMAX_ACCUMULATOR 1` _[#if CONFIG_HISTORY_REJECTION == HISTORY_REJECTION_MINMAX_BOUNDARIES]_
- L359 `#define COMPILE_MOMENT2_ACCUMULATOR 1` _[#if !(CONFIG_HISTORY_REJECTION == HISTORY_REJECTION_MINMAX_BOUNDARIES) && CONFIG_HISTORY_REJECTION == HISTORY_REJECTION_VAR_BOUNDARIES && CONFIG_REJECTION_INPUT_MODE == REJECTION_INPUT_MODE_1UNNORMALIZED]_
- L392 `#define SignalInput_Textures_1 SignalInput_Textures_0` _[#if !(CONFIG_INPUT_TEXTURE_COUNT > 1)]_
- L398 `#define SignalInput_Textures_2 SignalInput_Textures_0` _[#if !(CONFIG_INPUT_TEXTURE_COUNT > 2)]_
- L404 `#define SignalInput_Textures_3 SignalInput_Textures_0` _[#if !(CONFIG_INPUT_TEXTURE_COUNT > 3)]_
- L418 `#define HistoryRejectionSignal_Textures_1 HistoryRejectionSignal_Textures_0` _[#if CONFIG_USE_REJECTION_BUFFER && !(CONFIG_REJECTION_TEXTURE_COUNT > 1)]_
- L424 `#define HistoryRejectionSignal_Textures_2 HistoryRejectionSignal_Textures_0` _[#if CONFIG_USE_REJECTION_BUFFER && !(CONFIG_REJECTION_TEXTURE_COUNT > 2)]_
- L430 `#define HistoryRejectionSignal_Textures_3 HistoryRejectionSignal_Textures_0` _[#if CONFIG_USE_REJECTION_BUFFER && !(CONFIG_REJECTION_TEXTURE_COUNT > 3)]_
- L446 `#define PrevHistory_Textures_1 PrevHistory_Textures_0` _[#if !(CONFIG_HISTORY_TEXTURE_COUNT > 1)]_
- L447 `#define SignalHistoryOutput_UAVs_1 SignalHistoryOutput_UAVs_0` _[#if !(CONFIG_HISTORY_TEXTURE_COUNT > 1)]_
- L454 `#define PrevHistory_Textures_2 PrevHistory_Textures_0` _[#if !(CONFIG_HISTORY_TEXTURE_COUNT > 2)]_
- L455 `#define SignalHistoryOutput_UAVs_2 SignalHistoryOutput_UAVs_0` _[#if !(CONFIG_HISTORY_TEXTURE_COUNT > 2)]_
- L462 `#define PrevHistory_Textures_3 PrevHistory_Textures_0` _[#if !(CONFIG_HISTORY_TEXTURE_COUNT > 3)]_
- L463 `#define SignalHistoryOutput_UAVs_3 SignalHistoryOutput_UAVs_0` _[#if !(CONFIG_HISTORY_TEXTURE_COUNT > 3)]_
- L64 #undef `CONFIG_SIGNAL_BATCH_SIZE`

#### Entry points (1)

- L1174-1182 _entry_ `[numthreads(TILE_PIXEL_SIZE, TILE_PIXEL_SIZE, 1)] void MainCS( uint2 DispatchThreadId : SV_DispatchThreadID, uint2 GroupId : SV_GroupID, uint2 GroupThreadId : SV_GroupThreadID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FSSDTemporalAccumulationCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/ScreenSpaceDenoise.cpp:1255)

#### Global parameters (uniforms) (21)

- L375 _parameter_ `float HistoryPreExposureCorrection;`
- L377 _parameter_ `float4 ScreenPosToHistoryBufferUV;`
- L378 _parameter_ `float4 HistoryBufferSizeAndInvSize;`
- L379 _parameter_ `float4 HistoryBufferUVMinMax;`
- L380 _parameter_ `float4 HistoryBufferScissorUVMinMax[CONFIG_SIGNAL_BATCH_SIZE];`
- L387 _parameter_ `FSSDTexture2D SignalInput_Textures_0;`
- L390 _parameter_ `FSSDTexture2D SignalInput_Textures_1;` _[#if CONFIG_INPUT_TEXTURE_COUNT > 1]_
- L396 _parameter_ `FSSDTexture2D SignalInput_Textures_2;` _[#if CONFIG_INPUT_TEXTURE_COUNT > 2]_
- L402 _parameter_ `FSSDTexture2D SignalInput_Textures_3;` _[#if CONFIG_INPUT_TEXTURE_COUNT > 3]_
- L413 _parameter_ `FSSDTexture2D HistoryRejectionSignal_Textures_0;` _[#if CONFIG_USE_REJECTION_BUFFER]_
- L416 _parameter_ `FSSDTexture2D HistoryRejectionSignal_Textures_1;` _[#if CONFIG_USE_REJECTION_BUFFER && CONFIG_REJECTION_TEXTURE_COUNT > 1]_
- L422 _parameter_ `FSSDTexture2D HistoryRejectionSignal_Textures_2;` _[#if CONFIG_USE_REJECTION_BUFFER && CONFIG_REJECTION_TEXTURE_COUNT > 2]_
- L428 _parameter_ `FSSDTexture2D HistoryRejectionSignal_Textures_3;` _[#if CONFIG_USE_REJECTION_BUFFER && CONFIG_REJECTION_TEXTURE_COUNT > 3]_
- L439 _parameter_ `FSSDTexture2D PrevHistory_Textures_0;`
- L440 _parameter_ `FSSDRWTexture2D SignalHistoryOutput_UAVs_0;`
- L443 _parameter_ `FSSDTexture2D PrevHistory_Textures_1;` _[#if CONFIG_HISTORY_TEXTURE_COUNT > 1]_
- L444 _parameter_ `FSSDRWTexture2D SignalHistoryOutput_UAVs_1;` _[#if CONFIG_HISTORY_TEXTURE_COUNT > 1]_
- L451 _parameter_ `FSSDTexture2D PrevHistory_Textures_2;` _[#if CONFIG_HISTORY_TEXTURE_COUNT > 2]_
- L452 _parameter_ `FSSDRWTexture2D SignalHistoryOutput_UAVs_2;` _[#if CONFIG_HISTORY_TEXTURE_COUNT > 2]_
- L459 _parameter_ `FSSDTexture2D PrevHistory_Textures_3;` _[#if CONFIG_HISTORY_TEXTURE_COUNT > 3]_
- L460 _parameter_ `FSSDRWTexture2D SignalHistoryOutput_UAVs_3;` _[#if CONFIG_HISTORY_TEXTURE_COUNT > 3]_

#### Functions (3)

- L469-475 _function_ `FSSDSignalSample TransformInputBufferForPreRejection(FSSDSignalSample Sample)`
- L477-483 _function_ `FSSDSignalSample TransformSignalForPostRejection(FSSDSignalSample Sample)`
- L486-1169 _function_ `void TemporallyAccumulate( uint2 DispatchThreadId : SV_DispatchThreadID, uint2 GroupId : SV_GroupID, uint2 GroupThreadId : SV_GroupThreadID, uint GroupThreadIndex : SV_GroupIndex)` — sv-semantics — Temporally accumulate the input.

#### Top-level macro invocations (1)

- L373 _macro_call_ `DECLARE_SCALAR_ARRAY(int, bCameraCut, MAX_SIGNAL_BATCH_SIZE)`
