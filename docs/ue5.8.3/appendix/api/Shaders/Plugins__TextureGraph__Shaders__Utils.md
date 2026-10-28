# Shaders / Plugins/TextureGraph/Shaders/Utils

- files: 5; lines: 377
- record kinds: cpp_binding=6, define=20, entry=6, function=8, groupshared=1, include=9, parameter=4, resource=15

### `Plugins/TextureGraph/Shaders/Utils/Histogram_comp.usf` (Other)

- lines: 133; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L3 `/Plugin/TextureGraph/ShaderUtil.ush`

#### Macros (#define, 5)

- L6 `#define MAX_flt (3.402823466e+38F)` _[#if !defined(MAX_flt)]_
- L19 `#define HistogramSize 256`
- L23 `#define THREADGROUPSIZE_X 16` _[#if !defined(THREADGROUPSIZE_X)]_
- L24 `#define THREADGROUPSIZE_Y 16` _[#if !defined(THREADGROUPSIZE_X)]_
- L25 `#define THREADGROUPSIZE_Z 1` _[#if !defined(THREADGROUPSIZE_X)]_

#### Entry points (2)

- L28-56 _entry_ `[numthreads(THREADGROUPSIZE_X, THREADGROUPSIZE_Y, THREADGROUPSIZE_Z)] void CSH_HistogramPerTile( uint3 GroupId : SV_GroupID, uint3 ThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID, uint GroupIndex: SV_GroupIndex )` — stage: **compute** — C++: `CSH_HistogramPerTile` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Utility/T_TextureHistogram.cpp:69)
- L59-133 _entry_ `[numthreads(256, 1, 1)] void CSH_Histogram( uint3 GroupId : SV_GroupID, uint3 ThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID, uint GroupIndex: SV_GroupIndex )` — stage: **compute** — C++: `CSH_Histogram` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Utility/T_TextureHistogram.cpp:70)

#### Global resources (textures / buffers / samplers) (4)

- L9 _resource_ `Texture2D SourceTiles;`
- L11 _resource_ `RWStructuredBuffer<uint4> TilesHistogramUAV;`
- L12 _resource_ `StructuredBuffer<uint4> TilesHistogramSRV;`
- L14 _resource_ `RWTexture2D<float4> Result;`

#### Global parameters (uniforms) (1)

- L16 _parameter_ `int4 InvocationDim;`

#### groupshared (1)

- L20 _groupshared_ `groupshared uint4 _SharedHistogram[HistogramSize];`

### `Plugins/TextureGraph/Shaders/Utils/MinMaxDownsample.usf` (Other)

- lines: 84; parse: all-branches
- includes: L4 `/Engine/Public/Platform.ush`, L5 `/Plugin/TextureGraph/SamplerStates.ush`, L6 `/Plugin/TextureGraph/ShaderUtil.ush`

#### Macros (#define, 2)

- L10 `#define CHECK_UVMASK 0` _[#if !defined(CHECK_UVMASK)]_
- L14 `#define FIRST_PASS 0` _[#if !defined(FIRST_PASS)]_
- L2 #pragma `once`

#### Entry points (1)

- L76-83 _entry_ `float4 FSH_MinMaxDownsample(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_MinMaxDownsample` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Utility/T_MinMax.cpp:13)

#### Global resources (textures / buffers / samplers) (2)

- L17 _resource_ `Texture2D SourceTexture;`
- L18 _resource_ `Texture2D WorldUVMask;`

#### Global parameters (uniforms) (2)

- L20 _parameter_ `float DX;`
- L21 _parameter_ `float DY;`

#### Functions (5)

- L23-38 _function_ `float2 tex2Dlod_UVMask(Texture2D tex, Texture2D uvMask, float2 uv)`
- L40-51 _function_ `float2 CalcMinMaxWithUVMask(Texture2D tex, float2 uv, float2 pixelSize)`
- L53-64 _function_ `float2 CalcMinMax(Texture2D tex, float2 uv, float2 pixelSize)`
- L66-69 _function_ `float4 FSH_MinMaxDownsampleFirstPass(float2 uv : TEXCOORD0) : SV_Target0` — sv-semantics
- L71-74 _function_ `float4 FSH_MinMaxDownsampleSecondPass(float2 uv : TEXCOORD0) : SV_Target0` — sv-semantics

### `Plugins/TextureGraph/Shaders/Utils/MinMaxDownsample_comp.usf` (Other)

- lines: 89; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`

#### Macros (#define, 6)

- L6 `#define SOURCE_TO_MIN_MAX_PASS 0` _[#if !defined(SOURCE_TO_MIN_MAX_PASS)]_
- L19 `#define Fetch4(tex) float4( tex.Load(uint3(tile_pos, 0)).x, tex.Load(uint3(tile_pos.x + 1, tile_pos.y, 0)).x, tex.Load(uint3(tile_pos.x, tile_pos.y + 1, 0)).x, tex.Load(uint3(tile_pos.x + 1, tile_pos.y + 1, 0)).x)` (5 lines)
- L42 `#define Fetch4XY(tex) float4x2( tex.Load(uint3(tile_pos, 0)).xy, tex.Load(uint3(tile_pos.x + 1, tile_pos.y, 0)).xy, tex.Load(uint3(tile_pos.x, tile_pos.y + 1, 0)).xy, tex.Load(uint3(tile_pos.x + 1, tile_pos.y + 1, 0)).xy )` (5 lines)
- L67 `#define THREADGROUPSIZE_X 4` _[#if !defined(THREADGROUPSIZE_X)]_
- L68 `#define THREADGROUPSIZE_Y 4` _[#if !defined(THREADGROUPSIZE_X)]_
- L69 `#define THREADGROUPSIZE_Z 1` _[#if !defined(THREADGROUPSIZE_X)]_

#### Entry points (1)

- L72-88 _entry_ `[numthreads(THREADGROUPSIZE_X, THREADGROUPSIZE_Y, THREADGROUPSIZE_Z)] void CSH_MinMaxDownsample(uint3 ThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `CSH_MinMaxDownsample` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Utility/T_MinMax.cpp:15)

#### Global resources (textures / buffers / samplers) (5)

- L11 _resource_ `Texture2D SourceTiles_0;`
- L12 _resource_ `Texture2D SourceTiles_1;`
- L13 _resource_ `Texture2D SourceTiles_2;`
- L14 _resource_ `Texture2D SourceTiles_3;`
- L16 _resource_ `RWTexture2D<float2> Result;`

#### Global parameters (uniforms) (1)

- L9 _parameter_ `int4 TilingDimensions;` — The width and height of each dst tiles (xy) and the number of tiles in the source (zw)

#### Functions (2)

- L25-40 _function_ `float4 fetch4At(int2 tile_pos)`
- L48-63 _function_ `float4x2 fetch4XYAt(int2 tile_pos)`

### `Plugins/TextureGraph/Shaders/Utils/MipMapDownsample_comp.usf` (Other)

- lines: 44; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`

#### Macros (#define, 4)

- L9 `#define Fetch4XYZW(tex) float4x4( tex.Load(uint3(tile_pos, 0)), tex.Load(uint3(tile_pos.x + 1, tile_pos.y, 0)), tex.Load(uint3(tile_pos.x, tile_pos.y + 1, 0)), tex.Load(uint3(tile_pos.x + 1, tile_pos.y + 1, 0)) )` (5 lines)
- L23 `#define THREADGROUPSIZE_X 4` _[#if !defined(THREADGROUPSIZE_X)]_
- L24 `#define THREADGROUPSIZE_Y 4` _[#if !defined(THREADGROUPSIZE_X)]_
- L25 `#define THREADGROUPSIZE_Z 1` _[#if !defined(THREADGROUPSIZE_X)]_

#### Entry points (1)

- L28-43 _entry_ `[numthreads(THREADGROUPSIZE_X, THREADGROUPSIZE_Y, THREADGROUPSIZE_Z)] void CSH_MipMapDownsample(uint3 ThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `CSH_MipMapDownsample` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Utility/T_MipMap.cpp:9)

#### Global resources (textures / buffers / samplers) (2)

- L4 _resource_ `Texture2D SourceTiles;`
- L6 _resource_ `RWTexture2D<float4> Result;`

#### Functions (1)

- L15-19 _function_ `float4x4 fetch4XYZWAt(int2 tile_pos)`

### `Plugins/TextureGraph/Shaders/Utils/SplitToTiles_comp.usf` (Other)

- lines: 27; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L3 `/Plugin/TextureGraph/TileInfo.ush`

#### Macros (#define, 3)

- L10 `#define THREADGROUPSIZE_X 4` _[#if !defined(THREADGROUPSIZE_X)]_
- L11 `#define THREADGROUPSIZE_Y 4` _[#if !defined(THREADGROUPSIZE_X)]_
- L12 `#define THREADGROUPSIZE_Z 1` _[#if !defined(THREADGROUPSIZE_X)]_

#### Entry points (1)

- L15-26 _entry_ `[numthreads(THREADGROUPSIZE_X, THREADGROUPSIZE_Y, THREADGROUPSIZE_Z)] void CSH_SplitToTiles(uint3 ThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `CSH_SplitToTiles` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Utility/T_SplitToTiles.cpp:10)

#### Global resources (textures / buffers / samplers) (2)

- L5 _resource_ `Texture2D SourceTexture;`
- L7 _resource_ `RWTexture2D<float4> Result;`
