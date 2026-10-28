# Shaders / Plugins/Experimental/GPULightmass/Shaders/Private

- files: 14; lines: 3176
- record kinds: cpp_binding=27, define=19, entry=27, function=30, groupshared=1, include=51, member=42, method=2, parameter=42, resource=90, static_const=5, struct=9

### `Plugins/Experimental/GPULightmass/Shaders/Private/BatchedTiles.ush` (Private)

- lines: 18; parse: all-branches

#### Structs / classes (1)

- L3-15 _struct_ **`FGPUTileDescription`** `struct FGPUTileDescription`
  - L5 _member_ `int2 LightmapSize;`
  - L6 _member_ `int2 VirtualTilePosition;`
  - L7 _member_ `int2 WorkingSetPosition;`
  - L8 _member_ `int2 ScratchPosition;`
  - L9 _member_ `int2 OutputLayer0Position;`
  - L10 _member_ `int2 OutputLayer1Position;`
  - L11 _member_ `int2 OutputLayer2Position;`
  - L12 _member_ `int2 OutputLayer3Position;`
  - L13 _member_ `int FrameIndex;`
  - L14 _member_ `int RenderPassIndex;`

#### Global resources (textures / buffers / samplers) (1)

- L17 _resource_ `StructuredBuffer<FGPUTileDescription> BatchedTiles;`

### `Plugins/Experimental/GPULightmass/Shaders/Private/BrickAllocationDefs.ush` (Private)

- lines: 27; parse: all-branches

#### Macros (#define, 7)

- L2 `#define Resolution 16`
- L4 `#define BRICK_NOT_ALLOCATED 0`
- L5 `#define BRICK_ALLOCATED 1`
- L6 `#define BRICK_DILATED 2`
- L7 `#define BRICK_IN_IMPORTANCE_VOLUME 3`
- L25 `#define NumBricksRequested BrickAllocatorParameters[0]`
- L26 `#define NumBricksAllocated BrickAllocatorParameters[1]`

#### Global resources (textures / buffers / samplers) (1)

- L24 _resource_ `RWBuffer<int> BrickAllocatorParameters;`

#### Functions (2)

- L9-17 _function_ `uint3 ComputeBrickLayoutPosition(int BrickLayoutAllocation, uint3 BrickLayoutDimensions)`
- L19-22 _function_ `uint ComputeBrickLinearAddress(uint3 BrickPosition, uint3 BrickLayoutDimensions)`

### `Plugins/Experimental/GPULightmass/Shaders/Private/BrickAllocationManagement.usf` (Private)

- lines: 507; parse: all-branches
- includes: L7 `/Engine/Public/Platform.ush`, L8 `BrickAllocationDefs.ush`, L9 `/Engine/Generated/UniformBuffers/VLMVoxelizationParams.ush`, L10 `/Engine/Private/MortonCode.ush`

#### Entry points (12)

- L18-23 _entry_ `[numthreads(4, 4, 4)] void ClearVolumeCS(uint3 VoxelPos : SV_DispatchThreadID)` — stage: **compute** — C++: `FClearVolumeCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/GPULightmass/Source/GPULightmass/Private/VolumetricLightmap.cpp:21)
- L28-37 _entry_ `[numthreads(4, 4, 4)] void VoxelizeImportanceVolumeCS(uint3 VoxelPos : SV_DispatchThreadID)` — stage: **compute** — C++: `FVoxelizeImportanceVolumeCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/GPULightmass/Source/GPULightmass/Private/VolumetricLightmap.cpp:22)
- L41-52 _entry_ `[numthreads(4, 4, 4)] void DownsampleVolumeCS( uint3 VoxelPosPrevMip : SV_DispatchThreadID, uint3 VoxelPos : SV_GroupID )` — stage: **compute** — C++: `FDownsampleVolumeCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/GPULightmass/Source/GPULightmass/Private/VolumetricLightmap.cpp:23)
- L62-80 _entry_ `[numthreads(4, 4, 4)] void CountNumBricksCS( uint3 VoxelPos : SV_DispatchThreadID )` — stage: **compute** — C++: `FCountNumBricksCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/GPULightmass/Source/GPULightmass/Private/VolumetricLightmap.cpp:24)
- L82-95 _entry_ `[numthreads(4, 4, 4)] void GatherBrickRequestsCS( uint3 VoxelPos : SV_DispatchThreadID )` — stage: **compute** — C++: `FGatherBrickRequestsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/GPULightmass/Source/GPULightmass/Private/VolumetricLightmap.cpp:25)
- L97-114 _entry_ `[numthreads(4, 4, 4)] void SplatVolumeCS( uint3 VoxelPos : SV_DispatchThreadID )` — stage: **compute** — C++: `FSplatVolumeCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/GPULightmass/Source/GPULightmass/Private/VolumetricLightmap.cpp:26)
- L118-124 _entry_ `[numthreads(64, 1, 1)] void WriteSortedBrickRequestsCS(uint3 RequestIndex : SV_DispatchThreadID)` — stage: **compute** — C++: `FWriteSortedBrickRequestsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/GPULightmass/Source/GPULightmass/Private/VolumetricLightmap.cpp:31)
- L126-137 _entry_ `[numthreads(4, 4, 4)] void PermuteVoxelizeVolumeCS( uint3 VoxelPos : SV_DispatchThreadID )` — stage: **compute** — C++: `FPermuteVoxelizeVolumeCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/GPULightmass/Source/GPULightmass/Private/VolumetricLightmap.cpp:32)
- L366-398 _entry_ `[numthreads(5, 5, 5)] void CopyPaddingStripsCS(uint3 BrickID : SV_GroupID, uint3 CellPosInBrick : SV_GroupThreadID)` — stage: **compute** — C++: `FCopyPaddingStripsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/GPULightmass/Source/GPULightmass/Private/VolumetricLightmap.cpp:28)
- L400-423 _entry_ `[numthreads(5, 5, 5)] void FillInvalidCellCS(uint3 BrickID : SV_GroupID, uint3 CellPosInBrick : SV_GroupThreadID)` — stage: **compute** — C++: `FFillInvalidCellCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/GPULightmass/Source/GPULightmass/Private/VolumetricLightmap.cpp:29)
- L425-461 _entry_ `[numthreads(5, 5, 5)] void StitchBorderCS(uint3 BrickID : SV_GroupID, uint3 CellPosInBrick : SV_GroupThreadID)` — stage: **compute** — C++: `FStitchBorderCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/GPULightmass/Source/GPULightmass/Private/VolumetricLightmap.cpp:27)
- L465-506 _entry_ `[numthreads(5, 5, 5)] void FinalizeBrickResultsCS(uint3 BrickID : SV_GroupID, uint3 CellPosInBrick : SV_GroupThreadID)` — stage: **compute** — C++: `FFinalizeBrickResultsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/GPULightmass/Source/GPULightmass/Private/VolumetricLightmap.cpp:30)

#### Global resources (textures / buffers / samplers) (27)

- L13 _resource_ `RWTexture3D<uint> VoxelizeVolume;`
- L39 _resource_ `RWTexture3D<uint> VoxelizeVolumePrevMip;`
- L54 _resource_ `RWTexture3D<uint4> IndirectionTexture;`
- L56 _resource_ `RWBuffer<uint4> BrickRequests;`
- L57 _resource_ `RWBuffer<uint4> BrickRequestsUnsorted;`
- L58 _resource_ `RWBuffer<uint> BrickRequestKeys;`
- L59 _resource_ `RWBuffer<uint> BrickRequestSortedIndices;`
- L60 _resource_ `RWBuffer<uint> BrickRequestSortedIndicesInverse;`
- L142 _resource_ `Texture3D<float4> AmbientVector;`
- L143 _resource_ `Texture3D<float4> SHCoefficients0R;`
- L144 _resource_ `Texture3D<float4> SHCoefficients1R;`
- L145 _resource_ `Texture3D<float4> SHCoefficients0G;`
- L146 _resource_ `Texture3D<float4> SHCoefficients1G;`
- L147 _resource_ `Texture3D<float4> SHCoefficients0B;`
- L148 _resource_ `Texture3D<float4> SHCoefficients1B;`
- L149 _resource_ `Texture3D<float4> SkyBentNormal;`
- L150 _resource_ `Texture3D<UNORM float> DirectionalLightShadowing;`
- L152 _resource_ `RWTexture3D<float3> OutAmbientVector;`
- L153 _resource_ `RWTexture3D<UNORM float4> OutSHCoefficients0R;`
- L154 _resource_ `RWTexture3D<UNORM float4> OutSHCoefficients1R;`
- L155 _resource_ `RWTexture3D<UNORM float4> OutSHCoefficients0G;`
- L156 _resource_ `RWTexture3D<UNORM float4> OutSHCoefficients1G;`
- L157 _resource_ `RWTexture3D<UNORM float4> OutSHCoefficients0B;`
- L158 _resource_ `RWTexture3D<UNORM float4> OutSHCoefficients1B;`
- L159 _resource_ `RWTexture3D<UNORM float4> OutSkyBentNormal;`
- L160 _resource_ `RWTexture3D<UNORM float> OutDirectionalLightShadowing;`
- L364 _resource_ `RWTexture3D<uint> ValidityMask;`

#### Global parameters (uniforms) (12)

- L12 _parameter_ `int3 VolumeSize;`
- L14 _parameter_ `int BrickSize;`
- L15 _parameter_ `int MipLevel;`
- L16 _parameter_ `int bIsHighestMip;`
- L25 _parameter_ `float3 ImportanceVolumeMin;`
- L26 _parameter_ `float3 ImportanceVolumeMax;`
- L116 _parameter_ `int NumTotalBricks;`
- L139 _parameter_ `int3 IndirectionTextureDim;`
- L140 _parameter_ `int3 BrickDataDimensions;`
- L162 _parameter_ `uint FrameNumber;`
- L363 _parameter_ `int BrickBatchOffset;`
- L463 _parameter_ `int NumTotalPassesToRender;`

#### Functions (6)

- L164-203 _function_ `float3 DilateWithValidityMask(RWTexture3D<float3> Texture, RWTexture3D<uint> CoverageMask, float3 UVW)`
- L205-246 _function_ `UNORM float4 DilateWithValidityMask(RWTexture3D<UNORM float4> Texture, RWTexture3D<uint> CoverageMask, float3 UVW)`
- L248-289 _function_ `UNORM float DilateWithValidityMask(RWTexture3D<UNORM float> Texture, RWTexture3D<uint> CoverageMask, float3 UVW)`
- L291-313 _function_ `float3 ManualTrilinearFilter(RWTexture3D<float3> Texture, float3 UVW)`
- L315-337 _function_ `UNORM float4 ManualTrilinearFilter(RWTexture3D<UNORM float4> Texture, float3 UVW)`
- L339-361 _function_ `float ManualTrilinearFilter(RWTexture3D<UNORM float> Texture, float3 UVW)`

### `Plugins/Experimental/GPULightmass/Shaders/Private/FirstBounceRayGuidingCDFBuild.usf` (Private)

- lines: 68; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L4 `/Engine/Private/PathTracing/Material/FirstBounceRayGuidingCommon.ush`, L6 `BatchedTiles.ush`

#### Entry points (1)

- L16-68 _entry_ `[numthreads(32, 16, 1)] void FirstBounceRayGuidingCDFBuildCS( uint3 ThreadId : SV_GroupThreadID, uint3 GroupID : SV_GroupID )` — stage: **compute** — C++: `FFirstBounceRayGuidingCDFBuildCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/GPULightmass/Source/GPULightmass/Private/LightmapRayTracing.cpp:23)

#### Global resources (textures / buffers / samplers) (3)

- L10 _resource_ `RWTexture2D<uint> RayGuidingLuminance;`
- L11 _resource_ `RWTexture2D<float> RayGuidingCDFX;`
- L12 _resource_ `RWTexture2D<float> RayGuidingCDFY;`

#### Global parameters (uniforms) (1)

- L8 _parameter_ `int RayGuidingEndPassIndex;`

#### groupshared (1)

- L14 _groupshared_ `groupshared float RowSum[DIRECTIONAL_BINS_ONE_DIM];`

### `Plugins/Experimental/GPULightmass/Shaders/Private/IrradianceCacheVisualization.usf` (Private)

- lines: 65; parse: all-branches
- includes: L8 `/Engine/Private/Common.ush`, L9 `/Engine/Private/DeferredShadingCommon.ush`, L10 `IrradianceCachingCommon.ush`

#### Entry points (1)

- L12-64 _entry_ `void VisualizeIrradianceCachePS( in float4 UVAndScreenPos : TEXCOORD0, in float4 SVPos : SV_POSITION, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FVisualizeIrradianceCachePS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/GPULightmass/Source/GPULightmass/Private/IrradianceCaching.cpp:12)

### `Plugins/Experimental/GPULightmass/Shaders/Private/IrradianceCachingCommon.ush` (Private)

- lines: 259; parse: all-branches
- includes: L2 `/Engine/Private/HashTable.ush`

#### Macros (#define, 4)

- L5 `#define IC_BACKFACE_DETECTION 0` _[#if !defined(IC_BACKFACE_DETECTION)]_
- L8 `#define BackfaceThresholdRejection (1.0f / 64)`
- L9 `#define BackfaceThresholdInsideGeometry (2.0f)`
- L220 `#define ATOMIC_ADD_FLOAT(Value, Increment) { uint NewValue = asuint(Increment); uint CompareValue = 0; uint OldValue; [allow_uav_condition] while (true) { InterlockedCompareExchange(Value, CompareValue, NewValue, OldValue); if (OldValue == Com ...` (15 lines)

#### Structs / classes (1)

- L11-15 _struct_ **`FFinalGatherHitPoint`** `struct FFinalGatherHitPoint`
  - L13 _member_ `float3 WorldPosition;`
  - L14 _member_ `float3 WorldNormal;`

#### Functions (9)

- L17-20 _function_ `uint ICKeyMix(uint2 Key)`
- L22-91 _function_ `bool ICHashTableAdd(uint2 Key, out uint Index)`
- L95-141 _function_ `bool ICHashTableFind(uint2 Key, out uint Index)` — Returns true if key is found. Index output is the hash table bucket this key is stored in if found.
- L143-153 _function_ `uint3 EncodeVoxelKey(float3 VoxelPos)`
- L155-181 _function_ `float3 EncodePositionKey(float3 WorldPosition, float3 WorldNormal, float Spacing)`
- L183-192 _function_ `uint EncodeNormalBits(float3 WorldNormal)`
- L194-218 _function_ `uint2 EncodeICHashKey(float3 WorldPosition, float3 WorldNormal, float Spacing)`
- L236-253 _function_ `void EmitGeometryHitPoint(FFinalGatherHitPoint HitPoint, uint Size)`
- L255-258 _function_ `int GetIrradianceCachingQuality()`

### `Plugins/Experimental/GPULightmass/Shaders/Private/LightmapBufferClear.usf` (Private)

- lines: 130; parse: all-branches
- includes: L7 `/Engine/Private/Common.ush`, L9 `LightmapEncoding.ush`, L10 `BatchedTiles.ush`

#### Entry points (3)

- L30-87 _entry_ `[numthreads(8, 8, 1)] void CopyConvergedLightmapTilesCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FCopyConvergedLightmapTilesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/GPULightmass/Source/GPULightmass/Private/LightmapRenderer.cpp:158)
- L94-108 _entry_ `[numthreads(8, 8, 1)] void UploadConvergedLightmapTilesCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FUploadConvergedLightmapTilesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/GPULightmass/Source/GPULightmass/Private/LightmapRenderer.cpp:159)
- L115-129 _entry_ `[numthreads(8, 8, 1)] void MultiTileClearCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FMultiTileClearCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/GPULightmass/Source/GPULightmass/Private/LightmapRenderer.cpp:161)

#### Global resources (textures / buffers / samplers) (19)

- L14 _resource_ `RWTexture2D<float4> OutputTileAtlas;`
- L15 _resource_ `RWTexture2D<float4> GBufferWorldPosition;`
- L16 _resource_ `RWTexture2D<float4> GBufferWorldNormal;`
- L17 _resource_ `RWTexture2D<float4> GBufferShadingNormal;`
- L18 _resource_ `RWTexture2D<float4> IrradianceAndSampleCount;`
- L19 _resource_ `RWTexture2D<float4> SHDirectionality;`
- L20 _resource_ `RWTexture2D<float4> SHCorrectionAndStationarySkyLightBentNormal;`
- L21 _resource_ `RWTexture2D<float4> ShadowMask;`
- L22 _resource_ `RWTexture2D<float4> ShadowMaskSampleCount;`
- L25 _resource_ `RWTexture2D<float4> StagingHQLayer0;`
- L26 _resource_ `RWTexture2D<float4> StagingHQLayer1;`
- L27 _resource_ `RWTexture2D<float4> StagingShadowMask;`
- L28 _resource_ `RWTexture2D<float4> StagingSkyOcclusion;`
- L89 _resource_ `RWTexture2D<float4> SrcTexture;`
- L90 _resource_ `RWTexture2D<float4> DstTexture;`
- L91 _resource_ `StructuredBuffer<int2> SrcTilePositions;`
- L92 _resource_ `StructuredBuffer<int2> DstTilePositions;`
- L112 _resource_ `Buffer<int2> TilePositions;`
- L113 _resource_ `RWTexture2D<float4> TilePool;`

#### Global parameters (uniforms) (4)

- L12 _parameter_ `int NumBatchedTiles;`
- L24 _parameter_ `uint StagingPoolSizeX;`
- L110 _parameter_ `int NumTiles;`
- L111 _parameter_ `int TileSize;`

### `Plugins/Experimental/GPULightmass/Shaders/Private/LightmapCommon.ush` (Private)

- lines: 30; parse: all-branches
- includes: L5 `/Engine/Private/PathTracing/PathTracingCommon.ush`
- L3 #pragma `once`

#### Functions (1)

- L7-30 _function_ `FMinimalPayload TraceLightmapVisibilityRay( in RaytracingAccelerationStructure TLAS, in uint RayFlags, in FRayDesc Ray)`

### `Plugins/Experimental/GPULightmass/Shaders/Private/LightmapEncoding.ush` (Private)

- lines: 73; parse: all-branches

#### Structs / classes (1)

- L13-28 _struct_ **`FL2SHAndCorrection`** `struct FL2SHAndCorrection`
  - L15 _member_ `float4 L2SHCoefficients;`
  - L16 _member_ `float Correction;`
  - L18 _method_ `void AddIncomingRadiance(float Luminance, float3 WorldDirection, float TangentZ)`

#### Functions (3)

- L2-11 _function_ `float4 SHBasisFunctionFloat(float3 InputVector)`
- L30-49 _function_ `void FinalizeLightmapSH( in float3 Irradiance, in FL2SHAndCorrection L2SHAndCorrection, inout float4 EncodedSH )`
- L51-72 _function_ `void FinalizeLightmapIrradiance( in float3 Irradiance, in FL2SHAndCorrection L2SHAndCorrection, inout float4 EncodedIrradiance )`

### `Plugins/Experimental/GPULightmass/Shaders/Private/LightmapGBuffer.usf` (Private)

- lines: 96; parse: all-branches
- includes: L7 `/Engine/Private/Common.ush`, L9 `/Engine/Generated/Material.ush`, L10 `/Engine/Generated/VertexFactory.ush`, L12 `/Engine/Private/PathTracing/Utilities/PathTracingRandomSequence.ush`

#### Macros (#define, 1)

- L69 `#define WorldPositionScalar 0.00001f`

#### Entry points (2)

- L29-66 _entry_ `void LightmapGBufferVS( FVertexFactoryInput Input, out FLightmapGBufferVSToPS Output )` — stage: **vertex (from C++ binding)** — C++: `FLightmapGBufferVS` SF_Vertex via IMPLEMENT_MATERIAL_SHADER_TYPE (Plugins/Experimental/GPULightmass/Source/GPULightmass/Private/LightmapGBuffer.cpp:7) _[#if VERTEXSHADER]_
- L71-95 _entry_ `void LightmapGBufferPS( FLightmapGBufferVSToPS Input OPTIONAL_IsFrontFace )` — stage: **pixel (from C++ binding)** — C++: `FLightmapGBufferPS` SF_Pixel via IMPLEMENT_MATERIAL_SHADER_TYPE (Plugins/Experimental/GPULightmass/Source/GPULightmass/Private/LightmapGBuffer.cpp:8)

#### Structs / classes (1)

- L19-26 _struct_ **`FLightmapGBufferVSToPS`** `struct FLightmapGBufferVSToPS`
  - L21 _member_ `FVertexFactoryInterpolantsVSToPS FactoryInterpolants;`
  - L22 _member_ `float4 Position : SV_POSITION;`
  - L23 _member_ `float4 SavedWorldPosition : POSITION1;`

#### Global parameters (uniforms) (4)

- L14 _parameter_ `float4 VirtualTexturePhysicalTileCoordinateScaleAndBias;`
- L15 _parameter_ `int2 ScratchTilePoolOffset;`
- L16 _parameter_ `int RenderPassIndex;`
- L17 _parameter_ `int bMaterialTwoSided;`

### `Plugins/Experimental/GPULightmass/Shaders/Private/LightmapOutput.usf` (Private)

- lines: 144; parse: all-branches
- includes: L2 `/Engine/Private/Common.ush`, L4 `LightmapEncoding.ush`, L5 `BatchedTiles.ush`

#### Entry points (1)

- L23-143 _entry_ `[numthreads(8, 8, 1)] void SelectiveLightmapOutputCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FSelectiveLightmapOutputCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/GPULightmass/Source/GPULightmass/Private/LightmapRenderer.cpp:160)

#### Global resources (textures / buffers / samplers) (9)

- L9 _resource_ `RWTexture2D<float4> OutputTileAtlas;`
- L10 _resource_ `RWTexture2D<float4> GBufferWorldPosition;`
- L11 _resource_ `RWTexture2D<float4> GBufferWorldNormal;`
- L12 _resource_ `RWTexture2D<float4> GBufferShadingNormal;`
- L13 _resource_ `RWTexture2D<float4> IrradianceAndSampleCount;`
- L14 _resource_ `RWTexture2D<float4> SHDirectionality;`
- L15 _resource_ `RWTexture2D<float4> SHCorrectionAndStationarySkyLightBentNormal;`
- L16 _resource_ `RWTexture2D<float4> ShadowMask;`
- L17 _resource_ `RWTexture2D<float4> ShadowMaskSampleCount;`

#### Global parameters (uniforms) (4)

- L7 _parameter_ `int NumBatchedTiles;`
- L19 _parameter_ `int NumTotalSamples;`
- L20 _parameter_ `int NumIrradianceCachePasses;`
- L21 _parameter_ `int NumRayGuidingTrialSamples;`

### `Plugins/Experimental/GPULightmass/Shaders/Private/LightmapPathTracing.usf` (Private)

- lines: 1485; parse: all-branches
- includes: L11 `/Engine/Private/Common.ush`, L12 `/Engine/Private/PostProcessCommon.ush`, L13 `/Engine/Private/RectLight.ush`, L14 `/Engine/Private/RayTracing/RayTracingCommon.ush`, L15 `/Engine/Private/RayTracing/RayTracingDirectionalLight.ush`, L16 `/Engine/Private/RayTracing/RayTracingRectLight.ush`, L17 `/Engine/Private/RayTracing/RayTracingSphereLight.ush`, L18 `/Engine/Private/RayTracing/RayTracingCapsuleLight.ush`, L20 `/Engine/Private/PathTracing/PathTracingCommon.ush`, L21 `/Engine/Private/PathTracing/Light/PathTracingLightGrid.ush`, L22 `/Engine/Private/RayTracing/RayTracingHitGroupCommon.ush`, L24 `BatchedTiles.ush`, L25 `/Engine/Private/PathTracing/Material/FirstBounceRayGuidingCommon.ush`, L32 `IrradianceCachingCommon.ush`, L34 `/Engine/Private/ShadingModels.ush`, L35 `/Engine/Private/PathTracing/Utilities/PathTracingRandomSequence.ush`, L36 `/Engine/Private/PathTracing/Light/PathTracingLightSampling.ush`, L37 `/Engine/Private/PathTracing/Material/PathTracingMaterialSampling.ush`, L38 `/Engine/Private/PathTracing/Material/PathTracingRadianceProbe.ush`, L40 `/Engine/Shared/LightDefinitions.h`, L42 `LightmapEncoding.ush`, L43 `LightmapCommon.ush`, L1051 `BrickAllocationDefs.ush`

#### Macros (#define, 5)

- L7 `#define SIMPLIFIED_MATERIAL_SHADER 1`
- L8 `#define RANDSEQ_UNROLL_SOBOL 0`
- L9 `#define USE_PATH_TRACING_LIGHT_GRID 1`
- L118 `#define WorldPositionScalar 0.00001f`
- L121 `#define USE_IRRADIANCE_CACHING 0` _[#if !defined(USE_IRRADIANCE_CACHING)]_

#### Entry points (3)

- L844-1049 _entry_ `[shader("raygeneration")] void LightmapPathTracingMainRG()` — stage: **raygeneration** — C++: `FLightmapPathTracingRGS` SF_RayGen via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/GPULightmass/Source/GPULightmass/Private/LightmapRayTracing.cpp:18)
- L1196-1388 _entry_ `[shader("raygeneration")] void VolumetricLightmapPathTracingMainRG()` — stage: **raygeneration** — C++: `FVolumetricLightmapPathTracingRGS` SF_RayGen via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/GPULightmass/Source/GPULightmass/Private/LightmapRayTracing.cpp:19)
- L1396-1484 _entry_ `[shader("raygeneration")] void StationaryLightShadowTracingMainRG()` — stage: **raygeneration** — C++: `FStationaryLightShadowTracingRGS` SF_RayGen via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/GPULightmass/Source/GPULightmass/Private/LightmapRayTracing.cpp:20)

#### Structs / classes (3)

- L85-90 _struct_ **`FThreeBandSHVectorFloat`** `struct FThreeBandSHVectorFloat`
  - L87 _member_ `float4 V0;`
  - L88 _member_ `float4 V1;`
  - L89 _member_ `float V2;`
- L92-97 _struct_ **`FThreeBandSHVectorRGBFloat`** `struct FThreeBandSHVectorRGBFloat`
  - L94 _member_ `FThreeBandSHVectorFloat R;`
  - L95 _member_ `FThreeBandSHVectorFloat G;`
  - L96 _member_ `FThreeBandSHVectorFloat B;`
- L1079-1116 _struct_ **`FLightShaderConstants`** `struct FLightShaderConstants` — Must match C++
  - L1081 _member_ `float3 PositionHigh;`
  - L1082 _member_ `float InvRadius;`
  - L1083 _member_ `float3 Color;`
  - L1084 _member_ `float FalloffExponent;`
  - L1085 _member_ `float3 Direction;`
  - L1086 _member_ `float SpecularScale;`
  - L1087 _member_ `float DiffuseScale;`
  - L1088 _member_ `float3 Tangent;`
  - L1089 _member_ `float SourceRadius;`
  - L1090 _member_ `float3 PositionLow;`
  - L1091 _member_ `float SourceLength;`
  - L1092 _member_ `float2 SpotAngles;`
  - L1093 _member_ `float SoftSourceRadius;`
  - L1094 _member_ `float RectLightBarnCosAngle;`
  - L1095 _member_ `float RectLightBarnLength;`
  - L1097 _method_ `void FillLightShaderParameters(inout FLightShaderParameters LightShaderParameters)`

#### Global resources (textures / buffers / samplers) (28)

- L28 _resource_ `RWTexture2D<uint> RayGuidingLuminance;`
- L29 _resource_ `Texture2D<float> RayGuidingCDFX;`
- L30 _resource_ `Texture2D<float> RayGuidingCDFY;`
- L48 _resource_ `Texture2D<float4> GBufferWorldPosition;`
- L49 _resource_ `Texture2D<float4> GBufferWorldNormal;`
- L50 _resource_ `Texture2D<float4> GBufferShadingNormal;`
- L51 _resource_ `RWTexture2D<float4> IrradianceAndSampleCount;`
- L52 _resource_ `RWTexture2D<float4> SHDirectionality;`
- L53 _resource_ `RWTexture2D<float4> SHCorrectionAndStationarySkyLightBentNormal;`
- L55 _resource_ `RWTexture2D<float4> OutputTileAtlas;`
- L135 _resource_ `RaytracingAccelerationStructure TLAS;`
- L1057 _resource_ `Texture3D<uint4> IndirectionTexture;`
- L1058 _resource_ `Buffer<uint4> BrickRequests;`
- L1062 _resource_ `RWTexture3D<float4> AmbientVector;`
- L1063 _resource_ `RWTexture3D<float4> SHCoefficients0R;`
- L1064 _resource_ `RWTexture3D<float4> SHCoefficients1R;`
- L1065 _resource_ `RWTexture3D<float4> SHCoefficients0G;`
- L1066 _resource_ `RWTexture3D<float4> SHCoefficients1G;`
- L1067 _resource_ `RWTexture3D<float4> SHCoefficients0B;`
- L1068 _resource_ `RWTexture3D<float4> SHCoefficients1B;`
- L1069 _resource_ `RWTexture3D<float4> SkyBentNormal;`
- L1070 _resource_ `RWTexture3D<UNORM float> DirectionalLightShadowing;`
- L1194 _resource_ `StructuredBuffer<FLightShaderConstants> LightShaderParametersArray;`
- L1390 _resource_ `Buffer<int> LightTypeArray;`
- L1391 _resource_ `Buffer<int> ChannelIndexArray;`
- L1392 _resource_ `Buffer<int> LightSampleIndexArray;`
- L1393 _resource_ `RWTexture2D<float4> ShadowMask;`
- L1394 _resource_ `RWTexture2D<float4> ShadowMaskSampleCount;`

#### Global parameters (uniforms) (10)

- L27 _parameter_ `int NumRayGuidingTrialSamples;`
- L45 _parameter_ `int LastInvalidationFrame;`
- L46 _parameter_ `int NumTotalSamples;`
- L136 _parameter_ `uint SceneVisibleLightCount;`
- L1053 _parameter_ `uint FrameNumber;`
- L1054 _parameter_ `float4 VolumeMin;`
- L1055 _parameter_ `float4 VolumeSize;`
- L1056 _parameter_ `int3 IndirectionTextureDim;`
- L1059 _parameter_ `int NumTotalBricks;`
- L1060 _parameter_ `int BrickBatchOffset;`

#### static const (5)

- L124 _static_const_ `static const uint MaxBounces = 32;`
- L129 _static_const_ `static const uint MISMode = 2;` — 0: only Material sampling 1: only Light sampling 2: both Material and Light
- L131 _static_const_ `static const uint ApproximateCaustics = 1;`
- L132 _static_const_ `static const uint EnableEmissive = 1;`
- L133 _static_const_ `static const float MaxNormalBias = 0.1;`

#### Functions (9)

- L57-83 _function_ `void GenerateCosineNormalRay( float3 TranslatedWorldPosition, float3 WorldNormal, inout FRandomSequence RandSequence, out float3 RayOrigin, out float3 RayDirection, out float3 TangentDirection, out float RayTMin, out float RayTMax, out float RayPdf )`
- L99-116 _function_ `FThreeBandSHVectorFloat SHBasisFunction3Float(float3 InputVector)`
- L138-152 _function_ `void AccumulateRadiance(inout float3 TotalRadiance, float3 PathRadiance)`
- L154-157 _function_ `bool IsInvalidSurfaceHit(FPathTracingPayload Payload)`
- L159-273 _function_ `FPathTracingPayload TraceTransparentRay(FRayDesc Ray, bool IsCameraRay, bool LastBounce, bool IncludeEmission, uint2 LaunchIndex, uint NumLights, inout RandomSequence RandSequence, inout float3 PathThroughput, inout float3 Radiance)`
- L275-299 _function_ `float3 TraceTransparentVisibilityRay(FRayDesc Ray, float PathRoughness)`
- L301-842 _function_ `void PathTracingKernel( in uint RenderPassIndex, float3 TranslatedWorldPosition, float3 ShadingNormal, inout RandomSequence RandSequence, inout uint SampleIndex, inout bool bIsValidSample, inout float3 RadianceValue, inout float3 RadianceDirection, inout float3 DirectLightingIrradiance, inout FL2SHAndCorrection DirectLightingSH, inout FThreeBandSHVectorRGBFloat DirectLightingSH, inout float LuminanceForFirstBounceRayGuiding, inout float3 SkyLightBentNormal, inout float4 PrimaryRandSample)`
- L1072-1076 _function_ `uint MortonEncode3(uint3 Pixel)`
- L1118-1192 _function_ `bool GenerateOcclusionRay( int LightType, FLightShaderParameters LightParameters, float3 TranslatedWorldPosition, float3 WorldNormal, float2 RandSample, inout float3 RayOrigin, inout float3 RayDirection, inout float RayTMin, inout float RayTMax )`

### `Plugins/Experimental/GPULightmass/Shaders/Private/StaticShadowDepthMap.usf` (Private)

- lines: 74; parse: all-branches
- includes: L3 `/Engine/Private/RayTracing/RayTracingCommon.ush`, L4 `LightmapCommon.ush`

#### Entry points (1)

- L17-73 _entry_ `[shader("raygeneration")] void StaticShadowDepthMapTracingRG()` — stage: **raygeneration** — C++: `FStaticShadowDepthMapTracingRGS` SF_RayGen via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/GPULightmass/Source/GPULightmass/Private/LightmapRayTracing.cpp:21)

#### Global resources (textures / buffers / samplers) (2)

- L6 _resource_ `RaytracingAccelerationStructure TLAS;`
- L15 _resource_ `RWTexture2D<half> DepthMapTexture;`

#### Global parameters (uniforms) (7)

- L8 _parameter_ `int StaticShadowDepthMapSuperSampleFactor;`
- L9 _parameter_ `int2 ShadowMapSize;`
- L10 _parameter_ `float4x4 LightToWorld;`
- L11 _parameter_ `float4x4 WorldToLight;`
- L12 _parameter_ `float3 LightSpaceImportanceBoundsMin;`
- L13 _parameter_ `float3 LightSpaceImportanceBoundsMax;`
- L14 _parameter_ `float MaxPossibleDistance;`

### `Plugins/Experimental/GPULightmass/Shaders/Private/VolumetricLightmapVoxelization.usf` (Private)

- lines: 200; parse: all-branches
- includes: L7 `/Engine/Private/Common.ush`, L9 `/Engine/Generated/Material.ush`, L10 `/Engine/Generated/VertexFactory.ush`, L12 `BrickAllocationDefs.ush`

#### Macros (#define, 2)

- L14 `#define SOFTWARE_CONSERVATIVE_RASTERIZATION 1`
- L15 `#define SUPER_RESOLUTION_FACTOR 4`

#### Entry points (3)

- L22-32 _entry_ `void VLMVoxelizationVS( FVertexFactoryInput Input, out FVLMVoxelizationVSToGS Output )` — stage: **vertex (from C++ binding)** — C++: `FVLMVoxelizationVS` SF_Vertex via IMPLEMENT_MATERIAL_SHADER_TYPE (Plugins/Experimental/GPULightmass/Source/GPULightmass/Private/VolumetricLightmap.cpp:18)
- L43-151 _entry_ `[maxvertexcount(3)] void VLMVoxelizationGS(triangle FVLMVoxelizationVSToGS Inputs[3], inout TriangleStream<FVLMVoxelizationVertex> OutStream)` — stage: **geometry** — C++: `FVLMVoxelizationGS` SF_Geometry via IMPLEMENT_MATERIAL_SHADER_TYPE (Plugins/Experimental/GPULightmass/Source/GPULightmass/Private/VolumetricLightmap.cpp:19)
- L153-199 _entry_ `void VLMVoxelizationPS( FVLMVoxelizationVertex Input )` — stage: **pixel (from C++ binding)** — C++: `FVLMVoxelizationPS` SF_Pixel via IMPLEMENT_MATERIAL_SHADER_TYPE (Plugins/Experimental/GPULightmass/Source/GPULightmass/Private/VolumetricLightmap.cpp:20)

#### Structs / classes (2)

- L17-20 _struct_ **`FVLMVoxelizationVSToGS`** `struct FVLMVoxelizationVSToGS`
  - L19 _member_ `float4 WorldPosition : SV_POSITION;`
- L34-41 _struct_ **`FVLMVoxelizationVertex`** `struct FVLMVoxelizationVertex`
  - L36 _member_ `float4 ScreenPosition : SV_POSITION;`
  - L37 _member_ `uint DominantAxis : DOMAXIS;`
  - L39 _member_ `float4 AABB : AABB;` _[#if SOFTWARE_CONSERVATIVE_RASTERIZATION]_
