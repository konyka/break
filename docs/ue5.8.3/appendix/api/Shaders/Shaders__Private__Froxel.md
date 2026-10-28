# Shaders / Shaders/Private/Froxel

- files: 2; lines: 394
- record kinds: function=18, groupshared=2, include=5, member=4, parameter=15, resource=2, struct=2

### `Shaders/Private/Froxel/Froxel.ush` (Private)

- lines: 163; parse: all-branches
- includes: L3 `../Common.ush`, L4 `/Engine/Shared/FroxelDefinitions.h`

#### Structs / classes (2)

- L99-103 _struct_ **`FFroxelViewBounds`** `struct FFroxelViewBounds`
  - L101 _member_ `float3 Min;`
  - L102 _member_ `float3 Max;`
- L144-148 _struct_ **`FFroxelClipBounds`** `struct FFroxelClipBounds`
  - L146 _member_ `float3 ClipMin;`
  - L147 _member_ `float3 ClipMax;`

#### Global parameters (uniforms) (15)

- L7 _parameter_ `float4 FroxelToViewScaleBias;` — Froxel grid constants
- L8 _parameter_ `float4 FroxelToClipScaleBias;`
- L9 _parameter_ `float2 FroxelClipToViewScale;`
- L10 _parameter_ `float FroxelRecLog2DepthScale1;` — 1 / log2(1.0 + DepthScale)
- L11 _parameter_ `float FroxelRecNearScale;`
- L12 _parameter_ `float FroxelDepthScale1;`
- L13 _parameter_ `float FroxelNear;`
- L14 _parameter_ `float FroxelViewToClipTransformScale;`
- L15 _parameter_ `float FroxelClipToViewTransformScale;`
- L16 _parameter_ `float FroxelClipToViewTransformBias;`
- L17 _parameter_ `float FroxelRadius;`
- L18 _parameter_ `float FroxelInvRadius;`
- L20 _parameter_ `uint bFroxelIsOrtho;`
- L21 _parameter_ `uint FroxelArgsStride;`
- L22 _parameter_ `uint FroxelArgsOffset;`

#### Functions (9)

- L24-42 _function_ `int CalcFroxelSliceFromDeviceZ(float DeviceZ)`
- L44-51 _function_ `float GetViewDepthFromFroxelSlice(float SliceZ)`
- L53-56 _function_ `float GetViewDepthFromFroxelSlice(int SliceZ)`
- L58-68 _function_ `float GetClipDepthFromFroxelSlice(float SliceZ)`
- L70-76 _function_ `FPackedFroxel PackFroxel(int3 Froxel)`
- L78-86 _function_ `int3 UnpackFroxel(FPackedFroxel PackedFroxel)`
- L88-97 _function_ `float3 GetFroxelViewSpaceCenter(int3 Froxel)`
- L105-142 _function_ `FFroxelViewBounds GetFroxelViewSpaceAABB(int3 Froxel)`
- L150-163 _function_ `FFroxelClipBounds GetFroxelClipBounds(int3 Froxel)`

### `Shaders/Private/Froxel/FroxelBuild.ush` (Private)

- lines: 231; parse: all-branches
- includes: L3 `../Common.ush`, L4 `Froxel.ush`, L5 `../WaveOpUtil.ush`

#### Global resources (textures / buffers / samplers) (2)

- L15 _resource_ `RWStructuredBuffer<FPackedFroxel> OutFroxels;`
- L16 _resource_ `RWBuffer<uint> OutFroxelArgs;`

#### groupshared (2)

- L18 _groupshared_ `groupshared int GroupShared_FroxelAnyTrue;`
- L91 _groupshared_ `groupshared int GroupShared_FroxelWorkLeft;`

#### Functions (9)

- L20-50 _function_ `bool GroupActiveAnyTrue(bool bValue)`
- L52-58 _function_ `void EmitFroxel(int3 Froxel)`
- L60-66 _function_ `void EmitValidFroxel(int3 Froxel)`
- L68-74 _function_ `void WriteHashedSlice(uint PackedSliceId)`
- L76-89 _function_ `void CheckHashedSlice(inout uint PackedSliceId, inout bool bAnyValidLeft)`
- L92-162 _function_ `void HashReduceFroxels(int MaxValid, uint GroupThreadIndex, uint LocalLinearTileId, uint2 GroupTileOffset, uint4 SortedSlices)`
- L164-170 _function_ `void CompSwap(inout uint A, inout uint B)`
- L172-217 _function_ `void HashBuildFroxelsFromDeviceZ(float4 DeviceZ, uint GroupThreadIndex, uint LocalLinearTileId, uint2 GroupTileOffset)`
- L219-230 _function_ `void HashBuildFroxelsFromDeviceZ(float DeviceZ, uint GroupThreadIndex, uint LocalLinearTileId, uint2 GroupTileOffset)`
