# Shaders / Shaders/Private/Nanite/Voxel

- files: 6; lines: 1939
- record kinds: cpp_binding=11, define=7, entry=11, function=30, include=20, member=20, resource=25, static_const=14, struct=6

### `Shaders/Private/Nanite/Voxel/AutoVoxel.usf` (Private)

- lines: 201; parse: all-branches
- includes: L3 `../../Common.ush`, L4 `../../SceneTexturesCommon.ush`, L5 `../../HashTable.ush`, L6 `../../WaveOpUtil.ush`, L7 `../../ShaderPrint.ush`, L8 `Voxel.ush`, L9 `Brick.ush`

#### Entry points (4)

- L44-94 _entry_ `[numthreads(8, 8, 1)] void VisibleBricksHash( uint2 PixelPos : SV_DispatchThreadID, uint GroupIndex : SV_GroupIndex )` — stage: **compute** — C++: `FBuildBricksParameters` SF_Compute via IMPLEMENT_GLOBAL_SHADER_STRUCT (Source/Runtime/Renderer/Private/Nanite/Voxel.cpp:108)
- L96-129 _entry_ `[numthreads(32, 1, 1)] void FillArgs( uint GroupIndex : SV_GroupIndex )` — stage: **compute** — C++: `FBuildBricksParameters` SF_Compute via IMPLEMENT_GLOBAL_SHADER_STRUCT (Source/Runtime/Renderer/Private/Nanite/Voxel.cpp:109)
- L132-163 _entry_ `[numthreads(64, 1, 1)] void AllocBlocks( uint BrickIndex : SV_DispatchThreadID, uint GroupIndex : SV_GroupIndex )` — stage: **compute** — C++: `FBuildBricksParameters` SF_Compute via IMPLEMENT_GLOBAL_SHADER_STRUCT (Source/Runtime/Renderer/Private/Nanite/Voxel.cpp:110)
- L166-201 _entry_ `[numthreads(8, 8, 1)] void FillBlocks( uint2 PixelPos : SV_DispatchThreadID )` — stage: **compute** — C++: `FBuildBricksParameters` SF_Compute via IMPLEMENT_GLOBAL_SHADER_STRUCT (Source/Runtime/Renderer/Private/Nanite/Voxel.cpp:111)

#### Global resources (textures / buffers / samplers) (3)

- L11 _resource_ `StructuredBuffer< uint > IndexBuffer;`
- L12 _resource_ `RWStructuredBuffer< uint > RWIndexBuffer;`
- L14 _resource_ `RWByteAddressBuffer RWBlockBuffer;`

#### Functions (2)

- L16-34 _function_ `int4 DepthToVoxel( uint2 PixelPos, float Depth )`
- L36-42 _function_ `void AddVoxelToBlock( uint BlockOffset, uint3 Voxel )`

### `Shaders/Private/Nanite/Voxel/Brick.ush` (Private)

- lines: 157; parse: all-branches
- includes: L3 `../../Common.ush`, L4 `Voxel.ush`

#### Macros (#define, 3)

- L6 `#define VOXEL_NUM_LEVELS 2`
- L7 `#define VOXEL_SCATTER 0`
- L113 `#define DRAW_RECTS 1`

#### Structs / classes (1)

- L13-17 _struct_ **`FBrick`** `struct FBrick`
  - L15 _member_ `uint3 Key;`
  - L16 _member_ `uint BlockOffset;`

#### Global resources (textures / buffers / samplers) (6)

- L19 _resource_ `StructuredBuffer< FBrick > BrickBuffer;`
- L20 _resource_ `RWStructuredBuffer< FBrick > RWBrickBuffer;`
- L129 _resource_ `Buffer< uint > DrawIndirectArgs;`
- L130 _resource_ `RWBuffer< uint > RWDrawIndirectArgs;`
- L132 _resource_ `Buffer< uint > DispatchIndirectArgs;`
- L133 _resource_ `RWBuffer< uint > RWDispatchIndirectArgs;`

#### static const (12)

- L9 _static_const_ `static const float VoxelSize = 0.125;` — World space size of smallest voxel
- L10 _static_const_ `static const float BrickSize = VOXEL_NUM_LEVELS == 2 ? 16 : 4;` — Num voxels wide
- L11 _static_const_ `static const float BrickSizeLog2 = log2( BrickSize );`
- L116 _static_const_ `static const uint VertsPerBrick = 3;` _[#if PLATFORM_SUPPORTS_RECT_LIST]_
- L117 _static_const_ `static const uint IndexesPerBrick = 3;` _[#if PLATFORM_SUPPORTS_RECT_LIST]_
- L118 _static_const_ `static const uint BricksPerInstance = 21;` _[#if PLATFORM_SUPPORTS_RECT_LIST]_
- L120 _static_const_ `static const uint VertsPerBrick = 4;` _[#if !(PLATFORM_SUPPORTS_RECT_LIST) && DRAW_RECTS]_
- L121 _static_const_ `static const uint IndexesPerBrick = 6;` _[#if !(PLATFORM_SUPPORTS_RECT_LIST) && DRAW_RECTS]_
- L122 _static_const_ `static const uint BricksPerInstance = 16;` _[#if !(PLATFORM_SUPPORTS_RECT_LIST) && DRAW_RECTS]_
- L124 _static_const_ `static const uint VertsPerBrick = 8;` _[#if !(PLATFORM_SUPPORTS_RECT_LIST) && !(DRAW_RECTS)]_
- L125 _static_const_ `static const uint IndexesPerBrick = 36;` _[#if !(PLATFORM_SUPPORTS_RECT_LIST) && !(DRAW_RECTS)]_
- L126 _static_const_ `static const uint BricksPerInstance = 8;` _[#if !(PLATFORM_SUPPORTS_RECT_LIST) && !(DRAW_RECTS)]_

#### Functions (9)

- L23-36 _function_ `uint EncodeBrickKey( float3 BrickPos, float Level )` _[#if 0]_
- L38-49 _function_ `void DecodeBrickKey( uint BrickKey, out float3 BrickPos, out float CubeSize )` _[#if 0]_
- L51-63 _function_ `uint3 EncodeBrickKey( float3 BrickPos, float Level )` _[#if !(0)]_
- L65-77 _function_ `void DecodeBrickKey( uint3 BrickKey, out float3 BrickPos, out float CubeSize )` _[#if !(0)]_
- L80-95 _function_ `FRay GetViewRay( float2 SvPosition )`
- L97-110 _function_ `float3 VisualizeCount( uint Count )`
- L135-138 _function_ `uint GetNumBricks()`
- L140-143 _function_ `uint GetNumBlocks()`
- L145-157 _function_ `void SetDrawIndirectArgs( uint NumBricks )`

### `Shaders/Private/Nanite/Voxel/RasterizeBricks.usf` (Private)

- lines: 259; parse: all-branches
- includes: L3 `../../Common.ush`, L4 `Brick.ush`, L5 `Voxel.ush`

#### Macros (#define, 4)

- L10 `#define SUPPORTS_CONSERVATIVE_DEPTH_WRITES ((COMPILER_HLSL && FEATURE_LEVEL >= FEATURE_LEVEL_SM5) \|\| COMPILER_PSSL \|\| (COMPILER_METAL && FEATURE_LEVEL >= FEATURE_LEVEL_SM5) \|\| SWITCH_PROFILE \|\| SWITCH_PROFILE_FORWARD)`
- L15 `#define DEPTH_LE_OUTPUT SV_DepthLessEqual` _[#if SUPPORTS_CONSERVATIVE_DEPTH_WRITES && COMPILER_HLSL \|\| COMPILER_METAL_SHADER_CONVERTER \|\| COMPILER_METAL \|\| SWITCH_PROFILE \|\| SWITCH_PROFILE_FORWARD]_
- L17 `#define DEPTH_LE_OUTPUT S_DEPTH_LE_OUTPUT` _[#if SUPPORTS_CONSERVATIVE_DEPTH_WRITES && !(COMPILER_HLSL \|\| COMPILER_METAL_SHADER_CONVERTER \|\| COMPILER_METAL \|\| SWITCH_PROFILE \|\| SWITCH_PROFILE_FORWARD) && COMPILER_PSSL]_
- L23 `#define DEPTH_LE_OUTPUT SV_DEPTH` _[#if !(SUPPORTS_CONSERVATIVE_DEPTH_WRITES)]_

#### Entry points (2)

- L26-146 _entry_ `void DrawBricksVS( uint VertexID : SV_VertexID, uint InstanceID : SV_InstanceID, out uint OutBrickOffset : TEXCOORD0, out uint OutBounds : TEXCOORD1, out float3 RayOrigin : TEXCOORD2, out float3 RayDirection : TEXCOORD3, out float4 OutPosition : SV_POSITION )` — stage: **vertex (from C++ binding)** — C++: `FDrawBricksVS` SF_Vertex via IMPLEMENT_SHADER_TYPE (Source/Runtime/Renderer/Private/Nanite/Voxel.cpp:179)
- L149-259 _entry_ `ENABLE_RE_Z void DrawBricksPS( in nointerpolation uint BrickOffset : TEXCOORD0, in nointerpolation uint BrickBounds : TEXCOORD1, in noperspective float3 RayOrigin : TEXCOORD2, in noperspective float3 RayDirection : TEXCOORD3, in centroid float4 SvPosition : SV_Position, out float4 OutColor : SV_Target0, out float OutDepth : DEPTH_LE_OUTPUT )` — stage: **pixel (from C++ binding)** — C++: `FDrawBricksPS` SF_Pixel via IMPLEMENT_SHADER_TYPE (Source/Runtime/Renderer/Private/Nanite/Voxel.cpp:180)

### `Shaders/Private/Nanite/Voxel/ScatterBricks.usf` (Private)

- lines: 176; parse: all-branches
- includes: L3 `../../Common.ush`, L4 `Brick.ush`, L5 `Voxel.ush`

#### Entry points (2)

- L25-138 _entry_ `[numthreads(4, 4, 4)] void ScatterVoxels( uint BrickIndex : SV_GroupID, uint3 Voxel : SV_GroupThreadID )` — stage: **compute** — C++: `FTileBricksParameters` SF_Compute via IMPLEMENT_GLOBAL_SHADER_STRUCT (Source/Runtime/Renderer/Private/Nanite/Voxel.cpp:144)
- L143-176 _entry_ `[numthreads(8, 8, 1)] void ScatterResolve( uint2 PixelPos : SV_DispatchThreadID )` — stage: **compute** — C++: `FTileBricksParameters` SF_Compute via IMPLEMENT_GLOBAL_SHADER_STRUCT (Source/Runtime/Renderer/Private/Nanite/Voxel.cpp:145)

#### Global resources (textures / buffers / samplers) (3)

- L7 _resource_ `Texture2D< uint > TileCount;`
- L8 _resource_ `RWTexture2D< uint > RWTileCount;`
- L141 _resource_ `RWTexture2D< float4 > OutSceneColor;`

#### Functions (1)

- L10-23 _function_ `void WritePixel( uint TriIndex, uint2 PixelPos, float DeviceZ )`

### `Shaders/Private/Nanite/Voxel/TileBricks.usf` (Private)

- lines: 310; parse: per-group
- includes: L3 `../../Common.ush`, L4 `../../WaveOpUtil.ush`, L5 `Brick.ush`, L6 `Voxel.ush`

#### Entry points (3)

- L41-134 _entry_ `[numthreads(64, 1, 1)] void BinBricksInTiles( uint BrickIndex : SV_DispatchThreadID )` — stage: **compute** — C++: `FTileBricksParameters` SF_Compute via IMPLEMENT_GLOBAL_SHADER_STRUCT (Source/Runtime/Renderer/Private/Nanite/Voxel.cpp:140)
- L137-175 _entry_ `[numthreads(8, 8, 1)] void BuildTileArrays( uint2 TileIndex : SV_DispatchThreadID, uint GroupIndex : SV_GroupIndex )` — stage: **compute** — C++: `FTileBricksParameters` SF_Compute via IMPLEMENT_GLOBAL_SHADER_STRUCT (Source/Runtime/Renderer/Private/Nanite/Voxel.cpp:141)
- L180-310 _entry_ `[numthreads(8, 8, 1)] void RayCastTiles( uint2 PixelPos : SV_DispatchThreadID )` — stage: **compute** — C++: `FTileBricksParameters` SF_Compute via IMPLEMENT_GLOBAL_SHADER_STRUCT (Source/Runtime/Renderer/Private/Nanite/Voxel.cpp:142)

#### Structs / classes (2)

- L11-17 _struct_ **`FTileListElement`** `struct FTileListElement`
  - L13 _member_ `float Depth;`
  - L15 _member_ `uint BrickIndex;` — uint	Bounds;
  - L16 _member_ `uint NextIndex;`
- L19-23 _struct_ **`FTileArrayElement`** `struct FTileArrayElement`
  - L21 _member_ `float Depth;`
  - L22 _member_ `uint BrickIndex;`

#### Global resources (textures / buffers / samplers) (11)

- L25 _resource_ `StructuredBuffer< FTileListElement > TileListBuffer;`
- L26 _resource_ `RWStructuredBuffer< FTileListElement > RWTileListBuffer;`
- L28 _resource_ `StructuredBuffer< FTileArrayElement > TileArrayBuffer;`
- L29 _resource_ `RWStructuredBuffer< FTileArrayElement > RWTileArrayBuffer;`
- L31 _resource_ `Texture2D< uint > TileHead;`
- L32 _resource_ `RWTexture2D< uint > RWTileHead;`
- L34 _resource_ `Texture2D< uint > TileCount;`
- L35 _resource_ `RWTexture2D< uint > RWTileCount;`
- L37 _resource_ `Texture2D< uint > TileOffset;`
- L38 _resource_ `RWTexture2D< uint > RWTileOffset;`
- L178 _resource_ `RWTexture2D< float4 > OutSceneColor;`

#### static const (2)

- L8 _static_const_ `static const uint TileShift = 3;` — 8x8
- L9 _static_const_ `static const uint TileListBufferSize = 1u << 25;`

### `Shaders/Private/Nanite/Voxel/Voxel.ush` (Private)

- lines: 836; parse: all-branches
- includes: L5 `/Engine/Public/Platform.ush`
- L3 #pragma `once`

#### Structs / classes (3)

- L33-39 _struct_ **`FRay`** `struct FRay`
  - L35 _member_ `float3 Origin;`
  - L36 _member_ `float3 Direction;`
  - L38 _member_ `float2 Time;`
- L41-51 _struct_ **`FDDA`** `struct FDDA`
  - L43 _member_ `float2 Time;`
  - L45 _member_ `bool3 IsPositive;`
  - L46 _member_ `int3 Step;`
  - L47 _member_ `uint VoxelIndex;`
  - L49 _member_ `float3 InvDir;`
  - L50 _member_ `float3 Next;`
- L198-204 _struct_ **`FRayCastCounters`** `struct FRayCastCounters`
  - L200 _member_ `int Tests;`
  - L201 _member_ `uint Steps;`
  - L202 _member_ `uint StepIn;`
  - L203 _member_ `uint StepOut;`

#### Global resources (textures / buffers / samplers) (2)

- L7 _resource_ `ByteAddressBuffer BlockBuffer;`
- L8 _resource_ `Texture3D<float> DistValues;`

#### Functions (18)

- L10-31 _function_ `void BlockBounds( uint2 Block, out uint3 Min, out uint3 Max )`
- L53-62 _function_ `FDDA InitDDA( FRay Ray )`
- L64-75 _function_ `void StartDDA( inout FDDA DDA, const uint Dimension, const FRay Ray )`
- L77-80 _function_ `float NextTime( FDDA DDA )`
- L82-132 _function_ `void StepDDA( inout FDDA DDA, const uint Dimension )`
- L134-141 _function_ `uint PrefixSum64( uint2 Occupency, uint Index, uint Mask )`
- L143-147 _function_ `uint PrefixSum64( uint2 Occupency, uint Index )`
- L149-166 _function_ `float2 RayUnitBox( FRay Ray )`
- L168-181 _function_ `float2 Intersect( FRay Ray, float3 BoundsCenter, float3 BoundsExtent )`
- L183-195 _function_ `float2 Intersect( FRay Ray, float3 Bounds[2] )`
- L207-298 _function_ `float RayCastBrick_L1( FRay Ray, uint BrickOffset, inout FRayCastCounters Counters )` — Assumes Ray in local 0-1 space
- L301-369 _function_ `float RayCastBrick_L1_YZ( FRay Ray, uint BrickOffset, inout FRayCastCounters Counters )` — Assumes Ray in local 0-1 space
- L372-497 _function_ `float RayCastBrick_L2_Flat( FRay Ray, uint BrickOffset, inout FRayCastCounters Counters )` — Assumes Ray in local 0-1 space
- L500-588 _function_ `float RayCastBrick_L2( FRay Ray, uint BrickOffset, inout FRayCastCounters Counters )` — Assumes Ray in local 0-1 space
- L591-598 _function_ `void StartDDA2( inout FDDA DDA, const float Scale, const FRay Ray )` _[#if 1]_
- L600-618 _function_ `void StepDDA2( inout FDDA DDA, const float Scale )` _[#if 1]_
- L621-744 _function_ `float RayCastBrick_L2_WhileWhile( FRay Ray, uint BrickOffset, inout FRayCastCounters Counters )` — Assumes Ray in local 0-1 space _[#if 1]_
- L748-836 _function_ `float RayCastBrick_L2_WhileIf( FRay Ray, uint BrickOffset, inout FRayCastCounters Counters )` — Assumes Ray in local 0-1 space
