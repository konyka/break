# Shaders / Shaders/Private/Tools

- files: 11; lines: 1223
- record kinds: cpp_binding=18, define=24, entry=16, function=15, groupshared=3, include=17, member=1, parameter=38, resource=38, struct=1

### `Shaders/Private/Tools/ColorGradingHistogram.usf` (Private)

- lines: 186; parse: all-branches
- includes: L9 `/Engine/Private/Common.ush`

#### Macros (#define, 2)

- L11 `#define THREADGROUP_THREADCOUNT (THREADGROUP_SIZE_X * THREADGROUP_SIZE_Y)`
- L27 `#define NUM_CHANNELS (3)` _[#if defined(BuildColorHistogramCS)]_

#### Entry points (2)

- L62-109 _entry_ `[numthreads(THREADGROUP_SIZE_X, THREADGROUP_SIZE_Y, 1)] void BuildColorHistogramCS( uint2 DispatchThreadId : SV_DispatchThreadID, uint2 GroupId : SV_GroupID, uint2 GroupThreadId : SV_GroupThreadID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FBuildColorHistogramCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/VisualizeColorGrading.cpp:444) _[#if defined(BuildColorHistogramCS)]_
- L122-183 _entry_ `[numthreads(THREADGROUP_SIZE_X, THREADGROUP_SIZE_Y, 1)] void DrawColorHistogramCS( uint2 DispatchThreadId : SV_DispatchThreadID, uint2 GroupId : SV_GroupID, uint2 GroupThreadId : SV_GroupThreadID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FDrawColorHistogramCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/VisualizeColorGrading.cpp:480) _[#if defined(DrawColorHistogramCS)]_

#### Global resources (textures / buffers / samplers) (6)

- L21 _resource_ `Texture2D InputColorTexture;` _[#if defined(BuildColorHistogramCS)]_
- L24 _resource_ `RWTexture2D<uint> OutputHistogramTexture;` _[#if defined(BuildColorHistogramCS)]_
- L25 _resource_ `RWStructuredBuffer<uint> OutputMetaDataBuffer;` _[#if defined(BuildColorHistogramCS)]_
- L115 _resource_ `Texture2D<uint> HistogramTexture;` _[#if defined(DrawColorHistogramCS)]_
- L116 _resource_ `StructuredBuffer<uint> MetaDataBuffer;` _[#if defined(DrawColorHistogramCS)]_
- L117 _resource_ `RWTexture2D<float3> OutputTexture;` _[#if defined(DrawColorHistogramCS)]_

#### Global parameters (uniforms) (5)

- L22 _parameter_ `int4 InputColorViewRect;` _[#if defined(BuildColorHistogramCS)]_
- L23 _parameter_ `float2 MinMaxValue;` _[#if defined(BuildColorHistogramCS)]_
- L118 _parameter_ `int4 OutputViewRect;` _[#if defined(DrawColorHistogramCS)]_
- L119 _parameter_ `int4 InputColorViewRect;` _[#if defined(DrawColorHistogramCS)]_
- L120 _parameter_ `uint Flags;` _[#if defined(DrawColorHistogramCS)]_

#### groupshared (2)

- L29 _groupshared_ `groupshared uint LDS[PER_CHANNEL_RESOLUTION];` _[#if defined(BuildColorHistogramCS)]_
- L30 _groupshared_ `groupshared uint LDS_Max[NUM_CHANNELS];` _[#if defined(BuildColorHistogramCS)]_

#### Functions (3)

- L13-17 _function_ `int IntensityToIntensityBin(float NormalizedIntensity)`
- L32-42 _function_ `void ClearLDS(uint GroupThreadIndex)` _[#if defined(BuildColorHistogramCS)]_
- L44-60 _function_ `void FlushAndClearLDS(uint Channel, uint GroupThreadIndex)` _[#if defined(BuildColorHistogramCS)]_

### `Shaders/Private/Tools/ColorGradingParade.usf` (Private)

- lines: 275; parse: all-branches
- includes: L9 `/Engine/Private/Common.ush`

#### Macros (#define, 10)

- L8 `#define MATERIAL_DOMAIN_UI 1`
- L12 `#define DIM_WAVE_OPS 0` _[#if !defined(DIM_WAVE_OPS)]_
- L18 `#define QUANT_FACTOR 1024.0`
- L19 `#define QUANT(x) (int((x) * QUANT_FACTOR))`
- L20 `#define DEQUANT(x) (float(x) / QUANT_FACTOR)`
- L22 `#define COLUMN_FLAG_HAS_NAN (1U << 0)`
- L23 `#define COLUMN_FLAG_HAS_INF (1U << 1)`
- L33 `#define THREADGROUP_THREADCOUNT (THREADGROUP_SIZE_X * THREADGROUP_SIZE_Y)` _[#if defined(BuildColorParadeHistogramCS)]_
- L34 `#define NUM_BINS_PER_THREAD (NUM_BINS / THREADGROUP_SIZE_Y)` _[#if defined(BuildColorParadeHistogramCS)]_
- L162 `#define THREADGROUP_THREADCOUNT (THREADGROUP_SIZE_X * THREADGROUP_SIZE_Y)` _[#if defined(DrawColorParadeCS)]_

#### Entry points (2)

- L52-156 _entry_ `[numthreads(THREADGROUP_SIZE_X, THREADGROUP_SIZE_Y, 1)] void BuildColorParadeHistogramCS( uint2 DispatchThreadId : SV_DispatchThreadID, uint2 GroupId : SV_GroupID, uint2 GroupThreadId : SV_GroupThreadID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FBuildColorParadeHistogramCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/VisualizeColorGrading.cpp:93) _[#if defined(BuildColorParadeHistogramCS)]_
- L197-272 _entry_ `[numthreads(THREADGROUP_SIZE_X, THREADGROUP_SIZE_Y, 1)] void DrawColorParadeCS( uint2 DispatchThreadId : SV_DispatchThreadID, uint2 GroupId : SV_GroupID, uint2 GroupThreadId : SV_GroupThreadID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FDrawColorParadeCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/VisualizeColorGrading.cpp:137) _[#if defined(DrawColorParadeCS)]_

#### Global resources (textures / buffers / samplers) (7)

- L36 _resource_ `Texture2D InputColorTexture;` _[#if defined(BuildColorParadeHistogramCS)]_
- L37 _resource_ `RWTexture2D<uint> OutputTexture;` _[#if defined(BuildColorParadeHistogramCS)]_
- L38 _resource_ `RWStructuredBuffer<uint> OutputColumnFlagsBuffer;` _[#if defined(BuildColorParadeHistogramCS)]_
- L164 _resource_ `Texture2D<uint> HistogramTexture;` _[#if defined(DrawColorParadeCS)]_
- L165 _resource_ `SamplerState HistogramTextureSampler;` _[#if defined(DrawColorParadeCS)]_
- L166 _resource_ `StructuredBuffer<uint> ColumnFlagsBuffer;` _[#if defined(DrawColorParadeCS)]_
- L167 _resource_ `RWTexture2D<float3> OutputTexture;` _[#if defined(DrawColorParadeCS)]_

#### Global parameters (uniforms) (10)

- L15 _parameter_ `float2 MinMaxValue;`
- L16 _parameter_ `uint Flags;`
- L39 _parameter_ `float4 InputColorViewRect;` _[#if defined(BuildColorParadeHistogramCS)]_
- L40 _parameter_ `int2 OutputHistogramSize;` — x is image columns, y is histogram bins _[#if defined(BuildColorParadeHistogramCS)]_
- L168 _parameter_ `int2 InputViewSize;` _[#if defined(DrawColorParadeCS)]_
- L169 _parameter_ `int2 HistogramSize;` _[#if defined(DrawColorParadeCS)]_
- L170 _parameter_ `int4 OutputViewRect;` _[#if defined(DrawColorParadeCS)]_
- L171 _parameter_ `float Brightness;` _[#if defined(DrawColorParadeCS)]_
- L172 _parameter_ `float Gamma;` _[#if defined(DrawColorParadeCS)]_
- L173 _parameter_ `float DesaturationPower;` _[#if defined(DrawColorParadeCS)]_

#### groupshared (1)

- L42 _groupshared_ `groupshared uint Bins[NUM_BINS];` _[#if defined(BuildColorParadeHistogramCS)]_

#### Functions (4)

- L25-29 _function_ `int ImageColumnToHistogramColumn(int Column, int ChannelIndex, int2 InputViewRectSize)`
- L44-50 _function_ `void ClearLDS(uint GroupThreadIndex)` _[#if defined(BuildColorParadeHistogramCS)]_
- L175-186 _function_ `float SampleHistogram(const float2 UV, int Channel)` _[#if defined(DrawColorParadeCS)]_
- L188-195 _function_ `uint GetColumnFlags(const float2 UV, int Channel)` _[#if defined(DrawColorParadeCS)]_

### `Shaders/Private/Tools/ColorGradingVectorScope.usf` (Private)

- lines: 189; parse: all-branches
- includes: L10 `/Engine/Private/Common.ush`

#### Macros (#define, 2)

- L9 `#define MATERIAL_DOMAIN_UI 1`
- L12 `#define THREADGROUP_THREADCOUNT (THREADGROUP_SIZE_X * THREADGROUP_SIZE_Y)`

#### Entry points (2)

- L72-107 _entry_ `[numthreads(THREADGROUP_SIZE_X, THREADGROUP_SIZE_Y, 1)] void BuildVectorScopeHistogramCS( uint2 DispatchThreadId : SV_DispatchThreadID, uint2 GroupId : SV_GroupID, uint2 GroupThreadId : SV_GroupThreadID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FBuildVectorScopeHistogramCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/VisualizeColorGrading.cpp:288) _[#if defined(BuildVectorScopeHistogramCS)]_
- L123-186 _entry_ `[numthreads(THREADGROUP_SIZE_X, THREADGROUP_SIZE_Y, 1)] void DrawVectorScopeCS( uint2 DispatchThreadId : SV_DispatchThreadID, uint2 GroupId : SV_GroupID, uint2 GroupThreadId : SV_GroupThreadID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FDrawVectorScopeCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/VisualizeColorGrading.cpp:327) _[#if defined(DrawVectorScopeCS)]_

#### Global resources (textures / buffers / samplers) (4)

- L67 _resource_ `Texture2D InputColorTexture;` _[#if defined(BuildVectorScopeHistogramCS)]_
- L70 _resource_ `RWTexture2D<uint> OutputHistogramTexture;` _[#if defined(BuildVectorScopeHistogramCS)]_
- L113 _resource_ `Texture2D<uint> HistogramTexture;` _[#if defined(DrawVectorScopeCS)]_
- L114 _resource_ `RWTexture2D<float3> OutputTexture;` _[#if defined(DrawVectorScopeCS)]_

#### Global parameters (uniforms) (9)

- L68 _parameter_ `int4 InputColorViewRect;` _[#if defined(BuildVectorScopeHistogramCS)]_
- L69 _parameter_ `float2 LuminanceFilterMinMax;` _[#if defined(BuildVectorScopeHistogramCS)]_
- L115 _parameter_ `int4 OutputViewRect;` _[#if defined(DrawVectorScopeCS)]_
- L116 _parameter_ `int4 InputColorViewRect;` _[#if defined(DrawVectorScopeCS)]_
- L117 _parameter_ `uint Flags;` _[#if defined(DrawVectorScopeCS)]_
- L118 _parameter_ `float Rotation;` _[#if defined(DrawVectorScopeCS)]_
- L119 _parameter_ `float Brightness;` _[#if defined(DrawVectorScopeCS)]_
- L120 _parameter_ `float Gamma;` _[#if defined(DrawVectorScopeCS)]_
- L121 _parameter_ `float DesaturationPower;` _[#if defined(DrawVectorScopeCS)]_

#### Functions (6)

- L14-21 _function_ `float3 RGBToYCbCr(float3 In)`
- L23-30 _function_ `float3 YCbCrToRGB(float3 In)`
- L32-43 _function_ `float3 RGBToNormalizedYCbCr(float3 In)`
- L45-51 _function_ `float3 NormalizedYCbCrToRGB(float3 In)`
- L53-57 _function_ `int HueToHueBin(float Hue)`
- L59-63 _function_ `int SaturationToSaturationBin(float Saturation)`

### `Shaders/Private/Tools/DebugAlphaChannel.usf` (Private)

- lines: 42; parse: all-branches
- includes: L3 `../Common.ush`

#### Entry points (1)

- L19-41 _entry_ `[numthreads(8, 8, 1)] void MainCS(uint2 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FDebugAlphaChannelCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/PostProcess/DebugAlphaChannel.cpp:46)

#### Global resources (textures / buffers / samplers) (3)

- L12 _resource_ `Texture2D<float4> SceneColorTexture;`
- L13 _resource_ `Texture2D<float> SceneDepthTexture;`
- L14 _resource_ `RWTexture2D<float4> SceneColorOutput;`

#### Global parameters (uniforms) (3)

- L8 _parameter_ `uint DebugModeId;`
- L9 _parameter_ `float OpaqueWorldDistance;`
- L10 _parameter_ `float OpaqueLerpWorldRange;`

### `Shaders/Private/Tools/DrawTexture.usf` (Private)

- lines: 11; parse: all-branches
- includes: L3 `../Common.ush`

#### Entry points (1)

- L8-11 _entry_ `float4 DrawTexturePS(float4 SvPosition : SV_POSITION) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FDrawTexturePS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/RenderCore/Private/RenderGraphUtils.cpp:266)

#### Global resources (textures / buffers / samplers) (1)

- L5 _resource_ `Texture2D InputTexture;`

#### Global parameters (uniforms) (1)

- L6 _parameter_ `uint2 InputOffset;`

### `Shaders/Private/Tools/DumpTexture.usf` (Private)

- lines: 45; parse: all-branches
- includes: L3 `../Common.ush`

#### Macros (#define, 5)

- L8 `#define TILE_SIZE 8`
- L11 `#define payload float4` _[#if DIM_TEXTURE_TYPE == 0]_
- L14 `#define payload uint4` _[#if !(DIM_TEXTURE_TYPE == 0) && DIM_TEXTURE_TYPE == 1]_
- L17 `#define payload uint4` _[#if !(DIM_TEXTURE_TYPE == 0) && !(DIM_TEXTURE_TYPE == 1) && DIM_TEXTURE_TYPE == 2]_
- L18 `#define SWIZZLE_STENCIL 1` _[#if !(DIM_TEXTURE_TYPE == 0) && !(DIM_TEXTURE_TYPE == 1) && DIM_TEXTURE_TYPE == 2]_

#### Entry points (1)

- L34-44 _entry_ `[numthreads(TILE_SIZE, TILE_SIZE, 1)] void MainCS(uint2 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FDumpTextureCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/RenderCore/Private/DumpGPU.cpp:222)

#### Global resources (textures / buffers / samplers) (2)

- L28 _resource_ `Texture2D<payload> Texture;`
- L29 _resource_ `RWTexture2D<payload> StagingOutput;`

### `Shaders/Private/Tools/FullscreenVertexShader.usf` (Private)

- lines: 52; parse: all-branches
- includes: L7 `../Common.ush`, L17 `../InstancedStereo.ush` [SCREEN_VS_FOR_MOBILE_MULTI_VIEW]

#### Macros (#define, 2)

- L10 `#define SCREEN_VS_FOR_INSTANCED_VIEWS 0` _[#if !defined(SCREEN_VS_FOR_INSTANCED_VIEWS)]_
- L13 `#define SCREEN_VS_FOR_MOBILE_MULTI_VIEW 0` _[#if !defined(SCREEN_VS_FOR_MOBILE_MULTI_VIEW)]_

#### Entry points (2)

- L20-43 _entry_ `void MainVS( float2 ViewportUV : ATTRIBUTE0, float2 UV : ATTRIBUTE1, out float4 OutPosition : SV_POSITION , uint InstanceId : SV_InstanceID , out uint OutViewportId : SV_ViewportArrayIndex , out nointerpolation uint OutViewId : VIEW_ID , out noperspective float2 OutUV : TEXCOORD0 )` — stage: **vertex (from C++ binding)** — C++: `FScreenVertexShaderVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/RenderCore/Private/CommonRenderResources.cpp:19) — C++: `FInstancedScreenVertexShaderVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/RenderCore/Private/CommonRenderResources.cpp:20) — C++: `FMobileMultiViewVertexShaderVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/RenderCore/Private/CommonRenderResources.cpp:21)
- L46-52 _entry_ `void MainForPreTransform(in uint VertexId : SV_VertexID, out FScreenVertexOutput Output)` — stage: **vertex (from C++ binding)** — C++: `FImagePreTransformVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/RenderCore/Private/CommonRenderResources.cpp:24)

#### Global parameters (uniforms) (1)

- L45 _parameter_ `float4 PreTransform;`

### `Shaders/Private/Tools/GPUDebugCrashUtils.usf` (Private)

- lines: 44; parse: all-branches
- includes: L7 `../Common.ush`

#### Entry points (1)

- L11-43 _entry_ `[numthreads(THREADGROUPSIZE, THREADGROUPSIZE, 1)] void MainCS(uint3 ThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `FGPUDebugCrashUtilsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/RenderCore/Private/GPUDebugCrashUtils.cpp:36)

#### Global resources (textures / buffers / samplers) (1)

- L9 _resource_ `RWTexture2D<uint> PageFaultUAV;`

### `Shaders/Private/Tools/SetupIndirectArgs.usf` (Private)

- lines: 18; parse: all-branches
- includes: L3 `../Common.ush`

#### Entry points (1)

- L11-17 _entry_ `[numthreads(1, 1, 1)] void InitIndirectArgs1DCS(uint3 DTID : SV_DispatchThreadID)` — stage: **compute** — C++: `FInitIndirectArgs1DCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/RenderCore/Private/RenderGraphUtils.cpp:878)

#### Global resources (textures / buffers / samplers) (2)

- L5 _resource_ `StructuredBuffer<uint> InputCountBuffer;`
- L6 _resource_ `RWBuffer<uint> IndirectDispatchArgsOut;`

#### Global parameters (uniforms) (3)

- L7 _parameter_ `uint Multiplier;`
- L8 _parameter_ `uint Divisor;`
- L9 _parameter_ `uint InputCountOffset;`

### `Shaders/Private/Tools/VisualizeLightShape.usf` (Private)

- lines: 140; parse: all-branches
- includes: L7 `../Common.ush`, L8 `../Hash.ush`, L9 `../Visualization.ush`, L10 `../MonteCarlo.ush`, L11 `../SceneTexturesCommon.ush`, L12 `../LightGridCommon.ush`

#### Entry points (2)

- L82-99 _entry_ `void VisualizeLightShapeVS( float3 LocalPosition : ATTRIBUTE0, uint2 ForwardLightIndex_LightType : ATTRIBUTE1, out FVSToPS VSToPS, out float4 OutPosition : SV_POSITION)` — stage: **vertex (from C++ binding)** — C++: `FVisualizeLightShapeVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VisualizeLightShape.cpp:437)
- L107-139 _entry_ `void VisualizeLightShapePS( FVSToPS VSToPS, float4 SvPosition : SV_POSITION, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FVisualizeLightShapePS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VisualizeLightShape.cpp:455)

#### Structs / classes (1)

- L77-80 _struct_ **`FVSToPS`** `struct FVSToPS`
  - L79 _member_ `uint LightSceneId : TEXCOORD0;`

#### Global parameters (uniforms) (5)

- L101 _parameter_ `float VisualizationToggleTime;`
- L102 _parameter_ `float InvFadeDuration;`
- L103 _parameter_ `float InvMaxDelayDistance;`
- L104 _parameter_ `float MaxDelay;`
- L105 _parameter_ `float MaxOpacity;`

#### Functions (2)

- L14-19 _function_ `float3 SafeNormalize(float3 V)`
- L21-75 _function_ `float3 GetLightShapeVertexTranslatedWorldPosition(float3 LocalPosition, FDeferredLightData LightData)`

### `Shaders/Private/Tools/VisualizeTexture.usf` (Private)

- lines: 221; parse: per-group
- includes: L7 `../Common.ush`

#### Macros (#define, 3)

- L9 `#define INPUT_MAPPING_COLOR 0`
- L10 `#define INPUT_MAPPING_DEPTH 1`
- L11 `#define INPUT_MAPPING_SHADOW 2`

#### Entry points (1)

- L41-221 _entry_ `void VisualizeTexturePS( float4 SvPosition : SV_POSITION, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FVisualizeTexturePS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/RenderCore/Private/VisualizeTexture.cpp:658)

#### Global resources (textures / buffers / samplers) (12)

- L15 _resource_ `Texture2D VisualizeTexture2D;` — to visualize the content of a texture to the screen, useful for debugging use "VisualizeTexture" in the console to activate
- L16 _resource_ `SamplerState VisualizeTexture2DSampler;`
- L17 _resource_ `Texture3D VisualizeTexture3D;`
- L18 _resource_ `SamplerState VisualizeTexture3DSampler;`
- L19 _resource_ `TextureCube VisualizeTextureCube;`
- L20 _resource_ `SamplerState VisualizeTextureCubeSampler;`
- L23 _resource_ `Texture2D<uint4> VisualizeDepthStencil;` — default Texture2D type is <float4>, which won't read the X28_G8UINT format properly.
- L25 _resource_ `Texture2D<uint> VisualizeUINT8Texture2D;`
- L28 _resource_ `Texture2DMS<float4> VisualizeTexture2DMS;` _[#if FEATURE_LEVEL >= FEATURE_LEVEL_SM5]_
- L29 _resource_ `TextureCubeArray VisualizeTextureCubeArray;` _[#if FEATURE_LEVEL >= FEATURE_LEVEL_SM5]_
- L30 _resource_ `SamplerState VisualizeTextureCubeArraySampler;` _[#if FEATURE_LEVEL >= FEATURE_LEVEL_SM5]_
- L38 _resource_ `float3 TextureExtent;` — x, y (0 for 2D textures), z(only !=0 if 3d texture), w unused

#### Global parameters (uniforms) (1)

- L36 _parameter_ `float4 VisualizeParam[3];` — [0]: r:RGBAdd, g:SingleChannelMul, b:Add, a:FracScale [1]: r:BlinkState=0/1, g:Frac when 0, saturate when 1, b:array index, a:custom mip [2]: r:0=normal 1=depth, 2=shadow depth, g:unwrapcubemap, b:singlechannel(0-3), a:unused
