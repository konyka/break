# Shaders / Plugins/Experimental/NeuralRendering/Source/NeuralPostProcessing/Shaders

- files: 1; lines: 516
- record kinds: cpp_binding=5, define=9, entry=5, function=12, include=3, macro_call=1, member=5, method=6, parameter=13, resource=7, struct=2

### `Plugins/Experimental/NeuralRendering/Source/NeuralPostProcessing/Shaders/NeuralPostProcessing.usf` (Other)

- lines: 516; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`, L4 `/Engine/Private/Common.ush`, L5 `/Engine/Private/ScreenPass.ush`

#### Macros (#define, 9)

- L7 `#define SOURCE_TYPE_TEXTURE 0`
- L8 `#define SOURCE_TYPE_BUFFER 1`
- L10 `#define BUFFER_COPY_TO_OVERLAPPING_TILE 0`
- L11 `#define BUFFER_COPY_FROM_OVERLAPPING_TILE 1`
- L14 `#define BUFFER_COPY_DIRECTION BUFFER_COPY_TO_OVERLAPPING_TILE` _[#if !defined(BUFFER_COPY_DIRECTION)]_
- L17 `#define OVERLAP_RESOLVE_IGNORE 0`
- L18 `#define OVERLAP_RESOLVE_FEATHERING 1`
- L21 `#define OVERLAP_RESOLVE_TYPE OVERLAP_RESOLVE_IGNORE` _[#if !defined(OVERLAP_RESOLVE_TYPE)]_
- L178 `#define TPVector2 float2`

#### Entry points (5)

- L48-66 _entry_ `[numthreads(8, 1, 1)] void BuildIndirectDispatchArgsCS(uint2 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FNeuralPostProcessingBuildIndirectDispatchArgsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NeuralRendering/Source/NeuralPostProcessing/Private/NeuralPostProcessingCS.cpp:52)
- L84-109 _entry_ `float4 UpscaleTexture(float4 Position : SV_POSITION) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FUpscaleTexture` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NeuralRendering/Source/NeuralPostProcessing/Private/NeuralPostProcessingCS.cpp:56)
- L147-151 _entry_ `float4 DownScaleTexture(float4 Position : SV_POSITION) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FDownScaleTexture` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NeuralRendering/Source/NeuralPostProcessing/Private/NeuralPostProcessingCS.cpp:55)
- L153-163 _entry_ `[numthreads(THREAD_GROUP_SIZE, THREAD_GROUP_SIZE, 1)] void DownScaleTextureCS(in const uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `FDownScaleTextureCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NeuralRendering/Source/NeuralPostProcessing/Private/NeuralPostProcessingCS.cpp:54)
- L323-515 _entry_ `[numthreads(THREAD_GROUP_SIZE, THREAD_GROUP_SIZE, 1)] void CopyBetweenTextureAndOverlappedTileBufferCS(in const uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `FCopyBetweenTextureAndOverlappedTileBufferCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/NeuralRendering/Source/NeuralPostProcessing/Private/NeuralPostProcessingCS.cpp:57)

#### Structs / classes (2)

- L180-224 _struct_ **`FTiledPosition`** `struct FTiledPosition`
  - L182 _member_ `int2 Index;`
  - L183 _member_ `TPVector2 Position;`
  - L187 _method_ `TPVector2 ToPosition(int2 TileDimension, TPVector2 Overlaps)` — For a given Tiled Position, get the corresponding Position with respect to tile dimension and overlap @TODO: float2 overlap
  - L194 _method_ `FTiledPosition TransformBy(int2 Offset, int2 TileDimension, TPVector2 Overlaps)` — Transform the current tiled position to the corresponding tiled position in the neighbor tile.
  - L205 _method_ `bool IsLeftEdge()`
  - L210 _method_ `bool IsRightEdge()`
  - L215 _method_ `bool IsTopEdge()`
  - L220 _method_ `bool IsBottomEdge()`
- L251-256 _struct_ **`FBufferLocation`** `struct FBufferLocation`
  - L253 _member_ `int Offset;`
  - L254 _member_ `int ChannelSize;`
  - L255 _member_ `int Valid;`

#### Global resources (textures / buffers / samplers) (7)

- L30 _resource_ `Buffer<uint> SourceType;`
- L31 _resource_ `RWBuffer<uint> RWIndirectDispatchArgsBuffer;`
- L37 _resource_ `Texture2D<float4> Source_Texture;`
- L39 _resource_ `SamplerState SourceTextureSampler;`
- L43 _resource_ `RWTexture2D<float4> TargetTexture;`
- L170 _resource_ `RWTexture2D<float4> RWSourceTexture;`
- L174 _resource_ `RWBuffer<float> TargetBuffer;`

#### Global parameters (uniforms) (13)

- L32 _parameter_ `int2 TargetDimension;`
- L34 _parameter_ `int SourceWidth;`
- L35 _parameter_ `int SourceHeight;`
- L36 _parameter_ `int2 ViewportSize;`
- L41 _parameter_ `int TargetWidth;`
- L42 _parameter_ `int TargetHeight;`
- L45 _parameter_ `int bVisualizeOverlap;`
- L46 _parameter_ `float OverlapVisualizeIntensity;`
- L171 _parameter_ `int TargetOverlappedTileWidth;`
- L172 _parameter_ `int TargetOverlappedTileHeight;`
- L173 _parameter_ `float2 TileOverlap;`
- L175 _parameter_ `int2 ViewTileDimension;`
- L176 _parameter_ `int NumOfChannel;`

#### Functions (12)

- L24-28 _function_ `float2 ConvertGridPos2UV(uint2 GridPosition,float2 ExtentInverse)`
- L68-74 _function_ `float3 BilinearInterpolate(float3 V00, float3 V10, float3 V01, float3 V11, float2 LerpFactors)`
- L76-82 _function_ `float4 BilinearInterpolate(float4 V00, float4 V10, float4 V01, float4 V11, float2 LerpFactors)`
- L111-145 _function_ `float4 GetSourceGridAverageValue(float2 Position)`
- L165-168 _function_ `bool IsInRect(int2 Position, int2 MinPosition, int2 MaxPosition)`
- L226-233 _function_ `FTiledPosition GetTiledPosition(int2 Position, int2 TileDimension)`
- L235-249 _function_ `float4 SampleSourceTexture(TPVector2 SamplePosition,int2 TextureSize)`
- L258-281 _function_ `FBufferLocation GetBufferLocation(FTiledPosition TiledPosition,int2 TargetOverlappedTileDim)`
- L284-290 _function_ `void SetTargetBufferValue(FBufferLocation BufferLocation, float4 Value)`
- L293-306 _function_ `float4 GetTargetBufferValue(FBufferLocation BufferLocation, float4 DefaultValue)` — Use the default value if the Buffer location is not valid
- L308-314 _function_ `float4 GetValueFromTransformedTile(FTiledPosition TiledPosition, int2 Offset, int2 TileDimension, TPVector2 InOverlap, float4 DefaultValue)`
- L316-320 _function_ `float4 EmbedDebugValue(float4 Value, float4 DebugValue, bool ForceDebug)`

#### Top-level macro invocations (1)

- L38 _macro_call_ `SCREEN_PASS_TEXTURE_VIEWPORT(Source)`
