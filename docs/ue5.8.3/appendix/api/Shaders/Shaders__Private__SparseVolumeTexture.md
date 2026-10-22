# Shaders / Shaders/Private/SparseVolumeTexture

- files: 3; lines: 551
- record kinds: cpp_binding=4, define=10, entry=4, function=17, include=5, member=5, parameter=25, resource=13, struct=1

### `Shaders/Private/SparseVolumeTexture/SparseVolumeTextureCommon.ush` (Private)

- lines: 175; parse: all-branches
- includes: L5 `../RandomInterleavedGradientNoise.ush`

#### Macros (#define, 7)

- L8 `#define SPARSE_VOLUME_TILE_RES 16`
- L9 `#define SPARSE_VOLUME_TILE_BORDER 1`
- L10 `#define SPARSE_VOLUME_TILE_RES_PADDED (SPARSE_VOLUME_TILE_RES + 2 * SPARSE_VOLUME_TILE_BORDER)`
- L12 `#define SVTADDRESSMODE_CLAMP 0u`
- L13 `#define SVTADDRESSMODE_WRAP 1u`
- L14 `#define SVTADDRESSMODE_MIRROR 2u`
- L17 `#define SPARSE_VOLUME_TEXTURE_SOFTWARE_LINEAR_MIP_FILTERING 1` _[#if !defined(SPARSE_VOLUME_TEXTURE_SOFTWARE_LINEAR_MIP_FILTERING)]_
- L3 #pragma `once`

#### Structs / classes (1)

- L50-57 _struct_ **`FSparseVolumeTextureUniforms`** `struct FSparseVolumeTextureUniforms`
  - L52 _member_ `float3 VolumePageResolution;`
  - L53 _member_ `float3 PageTableOffset;`
  - L54 _member_ `float3 TileDataTexelSize;`
  - L55 _member_ `int FrameIndex;`
  - L56 _member_ `int HighestMipLevel;`

#### Functions (12)

- L20-24 _function_ `float SparseVolumeTextureApplyAddressModeMirror(float v)`
- L26-40 _function_ `float SparseVolumeTextureApplyAddressMode(float v, uint AddressMode)`
- L42-48 _function_ `float3 SparseVolumeTextureApplyAddressMode(float3 UVW, uint AddressU, uint AddressV, uint AddressW)`
- L59-71 _function_ `FSparseVolumeTextureUniforms SparseVolumeTextureUnpackUniforms(const uint4 Packed0, const uint4 Packed1)`
- L73-91 _function_ `float SparseVolumeTextureCalculateMipLevel(FSparseVolumeTextureUniforms Uniforms, float3 UVWDDX, float3 UVWDDY, float MipBias, float2 SvPositionXY)`
- L93-106 _function_ `float3 SparseVolumeTextureGetVoxelCoord(Texture3D<uint> PageTable, FSparseVolumeTextureUniforms Uniforms, float3 PageTableCoord, int MipLevel)`
- L108-122 _function_ `float3 SparseVolumeTextureSamplePageTable(Texture3D<uint> PageTable, FSparseVolumeTextureUniforms Uniforms, float3 UVW, uint AddressU, uint AddressV, uint AddressW, int MipLevel = 0)`
- L124-137 _function_ `int3 SparseVolumeTextureLoadPageTable(Texture3D<uint> PageTable, FSparseVolumeTextureUniforms Uniforms, int3 TexelCoord, int MipLevel = 0)`
- L139-147 _function_ `float4 SparseVolumeTextureSamplePhysicalTileData(Texture3D PhysicalTileDataA, Texture3D PhysicalTileDataB, SamplerState TileDataSampler, float3 VoxelUVW, int PhysicalTileDataIndex)`
- L149-156 _function_ `float3 SparseVolumeTextureSamplePageTableSecondMipWrapper(Texture3D<uint> PageTable, FSparseVolumeTextureUniforms Uniforms, float3 UVW, uint AddressU, uint AddressV, uint AddressW, int MipLevel = 0)`
- L158-165 _function_ `float4 SparseVolumeTextureSamplePhysicalTileDataSecondMipWrapper(Texture3D PhysicalTileDataA, Texture3D PhysicalTileDataB, SamplerState TileDataSampler, float3 VoxelUVW, int PhysicalTileDataIndex)`
- L167-174 _function_ `float4 SparseVolumeTextureCombineMipSamples(float4 LowerMipSample, float4 UpperMipSample, float MipLevelFractionalPart)`

### `Shaders/Private/SparseVolumeTexture/UpdateSparseVolumeTexture.usf` (Private)

- lines: 166; parse: all-branches
- includes: L5 `/Engine/Public/Platform.ush`, L6 `SparseVolumeTextureCommon.ush`

#### Macros (#define, 3)

- L29 `#define TEXTURE_UPDATE_MASK 0` _[#if defined(UPDATE_TILE_TEXTURE_FROM_SPARSE_BUFFER) && !defined(TEXTURE_UPDATE_MASK)]_
- L32 `#define UPDATE_TEXTURE_A ((TEXTURE_UPDATE_MASK & 1) != 0)` _[#if defined(UPDATE_TILE_TEXTURE_FROM_SPARSE_BUFFER)]_
- L33 `#define UPDATE_TEXTURE_B ((TEXTURE_UPDATE_MASK & 2) != 0)` _[#if defined(UPDATE_TILE_TEXTURE_FROM_SPARSE_BUFFER)]_
- L3 #pragma `once`

#### Entry points (2)

- L110-134 _entry_ `[numthreads(64, 1, 1)] void SparseVolumeTextureUpdateFromSparseBufferCS(uint3 GroupId : SV_GroupID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FSparseVolumeTextureUpdateFromSparseBufferCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Engine/Private/SparseVolumeTexture/SparseVolumeTextureUpload.cpp:57) _[#if defined(UPDATE_TILE_TEXTURE_FROM_SPARSE_BUFFER)]_
- L146-163 _entry_ `[numthreads(64, 1, 1)] void SparseVolumeTextureUpdatePageTableCS(uint3 DispatchThreadID : SV_DispatchThreadID)` — stage: **compute** — C++: `FSparseVolumeTextureUpdatePageTableCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Engine/Private/SparseVolumeTexture/SparseVolumeTextureUpload.cpp:83) _[#if defined(UPDATE_PAGE_TABLE)]_

#### Global resources (textures / buffers / samplers) (9)

- L36 _resource_ `RWTexture3D<float4> DstPhysicalTileTextureA;` _[#if defined(UPDATE_TILE_TEXTURE_FROM_SPARSE_BUFFER) && UPDATE_TEXTURE_A]_
- L37 _resource_ `Buffer<float4> SrcPhysicalTileBufferA;` _[#if defined(UPDATE_TILE_TEXTURE_FROM_SPARSE_BUFFER) && UPDATE_TEXTURE_A]_
- L41 _resource_ `RWTexture3D<float4> DstPhysicalTileTextureB;` _[#if defined(UPDATE_TILE_TEXTURE_FROM_SPARSE_BUFFER) && UPDATE_TEXTURE_B]_
- L42 _resource_ `Buffer<float4> SrcPhysicalTileBufferB;` _[#if defined(UPDATE_TILE_TEXTURE_FROM_SPARSE_BUFFER) && UPDATE_TEXTURE_B]_
- L45 _resource_ `ByteAddressBuffer OccupancyBitsBuffer;` _[#if defined(UPDATE_TILE_TEXTURE_FROM_SPARSE_BUFFER)]_
- L46 _resource_ `ByteAddressBuffer TileDataOffsetsBuffer;` _[#if defined(UPDATE_TILE_TEXTURE_FROM_SPARSE_BUFFER)]_
- L47 _resource_ `ByteAddressBuffer DstTileCoordsBuffer;` _[#if defined(UPDATE_TILE_TEXTURE_FROM_SPARSE_BUFFER)]_
- L140 _resource_ `RWTexture3D<uint> PageTable;` _[#if defined(UPDATE_PAGE_TABLE)]_
- L141 _resource_ `ByteAddressBuffer PageTableUpdates;` _[#if defined(UPDATE_PAGE_TABLE)]_

#### Global parameters (uniforms) (12)

- L48 _parameter_ `float4 FallbackValueA;` _[#if defined(UPDATE_TILE_TEXTURE_FROM_SPARSE_BUFFER)]_
- L49 _parameter_ `float4 FallbackValueB;` _[#if defined(UPDATE_TILE_TEXTURE_FROM_SPARSE_BUFFER)]_
- L50 _parameter_ `uint TileIndexOffset;` — Number of tiles that have already been processed in previous dispatches _[#if defined(UPDATE_TILE_TEXTURE_FROM_SPARSE_BUFFER)]_
- L51 _parameter_ `uint SrcVoxelDataOffsetA;` — Start of the SrcPhysicalTileBufferA SRV. This value needs to be subtracted from any indices used for loads. _[#if defined(UPDATE_TILE_TEXTURE_FROM_SPARSE_BUFFER)]_
- L52 _parameter_ `uint SrcVoxelDataOffsetB;` — Start of the SrcPhysicalTileBufferB SRV. This value needs to be subtracted from any indices used for loads. _[#if defined(UPDATE_TILE_TEXTURE_FROM_SPARSE_BUFFER)]_
- L53 _parameter_ `uint NumTilesToCopy;` _[#if defined(UPDATE_TILE_TEXTURE_FROM_SPARSE_BUFFER)]_
- L54 _parameter_ `uint BufferTileStep;` _[#if defined(UPDATE_TILE_TEXTURE_FROM_SPARSE_BUFFER)]_
- L55 _parameter_ `uint NumDispatchedGroups;` _[#if defined(UPDATE_TILE_TEXTURE_FROM_SPARSE_BUFFER)]_
- L56 _parameter_ `uint PaddedTileSize;` _[#if defined(UPDATE_TILE_TEXTURE_FROM_SPARSE_BUFFER)]_
- L142 _parameter_ `uint UpdateCoordOffset;` _[#if defined(UPDATE_PAGE_TABLE)]_
- L143 _parameter_ `uint UpdatePayloadOffset;` _[#if defined(UPDATE_PAGE_TABLE)]_
- L144 _parameter_ `uint NumUpdates;` _[#if defined(UPDATE_PAGE_TABLE)]_

#### Functions (4)

- L8-11 _function_ `uint FlattenCoord(uint3 Coord, uint3 VolumeSize)`
- L13-24 _function_ `uint3 UnflattenCoord(uint Index, uint3 VolumeSize)`
- L58-75 _function_ `uint ComputeLocalVoxelDataLoadIndex(uint VoxelIndex, uint2 OccupancyBits, out bool bValidVoxel)` _[#if defined(UPDATE_TILE_TEXTURE_FROM_SPARSE_BUFFER)]_
- L77-108 _function_ `void CopyToTileDataTexture(RWTexture3D<float4> DstTileTexture, Buffer<float4> SrcBuffer, uint SrcVoxelDataOffset, uint TileIdx, uint TextureTileOffset, uint3 DstBaseCoord, float4 FallbackValue, uint GroupThreadIndex)` _[#if defined(UPDATE_TILE_TEXTURE_FROM_SPARSE_BUFFER)]_

### `Shaders/Private/SparseVolumeTexture/VisualizeSparseVolumeTexture.usf` (Private)

- lines: 210; parse: all-branches
- includes: L7 `/Engine/Private/Common.ush`, L8 `SparseVolumeTextureCommon.ush`

#### Entry points (2)

- L15-24 _entry_ `void VisualizeSparseVolumeTextureVS( in uint VertexId : SV_VertexID, out float4 Position : SV_POSITION)` — stage: **vertex (from C++ binding)** — C++: `FVisualizeSparseVolumeTextureVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/SparseVolumeTexture/SparseVolumeTextureViewerRendering.cpp:94) _[#if defined(VERTEX_SHADER)]_
- L61-204 _entry_ `void VisualizeSparseVolumeTexturePS( in float4 SVPos : SV_POSITION, out float4 OutLuminanceAlpha : SV_Target0 )` — stage: **pixel (from C++ binding)** — C++: `FVisualizeSparseVolumeTexturePS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/SparseVolumeTexture/SparseVolumeTextureViewerRendering.cpp:95) _[#if defined(PIXEL_SHADER)]_

#### Global resources (textures / buffers / samplers) (4)

- L44 _resource_ `SamplerState TileDataTextureSampler;` _[#if defined(PIXEL_SHADER)]_
- L45 _resource_ `Texture3D<uint> SparseVolumeTexturePageTable;` _[#if defined(PIXEL_SHADER)]_
- L46 _resource_ `Texture3D<float4> SparseVolumeTextureA;` _[#if defined(PIXEL_SHADER)]_
- L47 _resource_ `Texture3D<float4> SparseVolumeTextureB;` _[#if defined(PIXEL_SHADER)]_

#### Global parameters (uniforms) (13)

- L13 _parameter_ `float DepthAsDeviceZ;` _[#if defined(VERTEX_SHADER)]_
- L48 _parameter_ `uint4 PackedSVTUniforms0;` _[#if defined(PIXEL_SHADER)]_
- L49 _parameter_ `uint4 PackedSVTUniforms1;` _[#if defined(PIXEL_SHADER)]_
- L50 _parameter_ `float3 SparseVolumeTextureResolution;` _[#if defined(PIXEL_SHADER)]_
- L51 _parameter_ `int MipLevel;` _[#if defined(PIXEL_SHADER)]_
- L52 _parameter_ `float4 WorldToLocal0;` _[#if defined(PIXEL_SHADER)]_
- L53 _parameter_ `float4 WorldToLocal1;` _[#if defined(PIXEL_SHADER)]_
- L54 _parameter_ `float4 WorldToLocal2;` _[#if defined(PIXEL_SHADER)]_
- L55 _parameter_ `float3 WorldToLocalRotation0;` _[#if defined(PIXEL_SHADER)]_
- L56 _parameter_ `float3 WorldToLocalRotation1;` _[#if defined(PIXEL_SHADER)]_
- L57 _parameter_ `float3 WorldToLocalRotation2;` _[#if defined(PIXEL_SHADER)]_
- L58 _parameter_ `uint ComponentToVisualize;` _[#if defined(PIXEL_SHADER)]_
- L59 _parameter_ `float Extinction;` _[#if defined(PIXEL_SHADER)]_

#### Functions (1)

- L32-42 _function_ `bool Slabs(float3 p0, float3 p1, float3 rayOrigin, float3 invRaydir, out float outTMin, out float outTMax)` — Updated from http://jcgt.org/published/0007/03/04/ _[#if defined(PIXEL_SHADER)]_
