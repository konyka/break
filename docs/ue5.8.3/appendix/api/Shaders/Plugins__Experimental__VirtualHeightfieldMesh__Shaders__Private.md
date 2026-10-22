# Shaders / Plugins/Experimental/VirtualHeightfieldMesh/Shaders/Private

- files: 4; lines: 976
- record kinds: cpp_binding=6, define=2, entry=5, function=44, groupshared=1, include=8, macro_call=2, member=19, parameter=21, prototype=2, resource=16, struct=7

### `Plugins/Experimental/VirtualHeightfieldMesh/Shaders/Private/HeightfieldMinMaxRender.usf` (Private)

- lines: 84; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`

#### Entry points (1)

- L43-83 _entry_ `[numthreads(8, 8, 1)] void MinMaxHeightCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `template<>` SF_Compute via IMPLEMENT_SHADER_TYPE (Plugins/Experimental/VirtualHeightfieldMesh/Source/VirtualHeightfieldMesh/Private/HeightfieldMinMaxRender.cpp:86)

#### Global resources (textures / buffers / samplers) (2)

- L5 _resource_ `Texture2D SrcTexture;`
- L8 _resource_ `RWTexture2D<float4> DstTexture;`

#### Global parameters (uniforms) (2)

- L6 _parameter_ `int2 SrcTextureSize;`
- L9 _parameter_ `int2 DstTextureCoord;`

#### Functions (4)

- L12-21 _function_ `float4 PackMinMax(in float2 UnPacked)` — Packing swizzles so that RGBA texture (required format for UAV) can be read after mapping on CPU as BGRA
- L23-29 _function_ `float2 UnPackMinMax(in float4 Packed)`
- L32-36 _function_ `float Min4(in float4 Values, in float ReplaceZero)` — Min downsample excludes zero values to avoid empty pixels affecting the calculation
- L38-41 _function_ `float Max4(in float4 Values)`

### `Plugins/Experimental/VirtualHeightfieldMesh/Shaders/Private/VirtualHeightfieldMesh.usf` (Private)

- lines: 424; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `/Engine/Private/MortonCode.ush`, L6 `VirtualHeightfieldMesh.ush`

#### Entry points (4)

- L176-209 _entry_ `[numthreads(1, 1, 1)] void InitBuffersCS()` — stage: **compute** — C++: `FInitBuffersVHM_CS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/VirtualHeightfieldMesh/Source/VirtualHeightfieldMesh/Private/VirtualHeightfieldMeshSceneProxy.cpp:743)
- L218-357 _entry_ `[numthreads(64, 1, 1)] void CollectQuadsCS( uint3 DispatchThreadId : SV_DispatchThreadID, uint GroupIndex : SV_GroupIndex )` — stage: **compute** — C++: `FCollectQuadsVHM_CS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/VirtualHeightfieldMesh/Source/VirtualHeightfieldMesh/Private/VirtualHeightfieldMeshSceneProxy.cpp:783)
- L363-371 _entry_ `[numthreads(1, 1, 1)] void InitInstanceBufferCS()` — stage: **compute** — C++: `FInitInstanceBufferVHM_CS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/VirtualHeightfieldMesh/Source/VirtualHeightfieldMesh/Private/VirtualHeightfieldMeshSceneProxy.cpp:803)
- L377-423 _entry_ `[numthreads(64, 1, 1)] void CullInstancesCS( uint3 DispatchThreadId : SV_DispatchThreadID )` — stage: **compute** — C++: `FCullInstancesVHM_CS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/VirtualHeightfieldMesh/Source/VirtualHeightfieldMesh/Private/VirtualHeightfieldMeshSceneProxy.cpp:838)

#### Global resources (textures / buffers / samplers) (13)

- L9 _resource_ `RWStructuredBuffer<WorkerQueueInfo> RWQueueInfo;`
- L13 _resource_ `RWBuffer<uint2> RWQuadBuffer;`
- L14 _resource_ `Buffer<uint2> QuadBuffer;`
- L16 _resource_ `RWBuffer<uint> RWIndirectArgsBuffer;`
- L17 _resource_ `Buffer<uint> IndirectArgsBufferSRV;`
- L19 _resource_ `RWStructuredBuffer<QuadRenderInstance> RWInstanceBuffer;`
- L20 _resource_ `StructuredBuffer<QuadRenderInstance> InstanceBuffer;`
- L22 _resource_ `RWBuffer<uint> RWFeedbackBuffer;`
- L24 _resource_ `Texture2D<uint> PageTableTexture;`
- L26 _resource_ `Texture2D<float4> HeightMinMaxTexture;`
- L27 _resource_ `Texture2D<float4> LodBiasMinMaxTexture;`
- L28 _resource_ `SamplerState MinMaxTextureSampler;`
- L31 _resource_ `Texture2D<float> OcclusionTexture;`

#### Global parameters (uniforms) (17)

- L10 _parameter_ `RWCoherentBuffer(uint) RWQueueBuffer;`
- L11 _parameter_ `uint QueueBufferSizeMask;`
- L29 _parameter_ `int MinMaxLevelOffset;`
- L32 _parameter_ `int OcclusionLevelOffset;`
- L34 _parameter_ `uint MaxLevel;`
- L35 _parameter_ `uint NumForceLoadLods;`
- L36 _parameter_ `uint PageTableFeedbackId;`
- L37 _parameter_ `uint NumPhysicalAddressBits;`
- L38 _parameter_ `float4 PageTableSize;`
- L39 _parameter_ `float4 PhysicalPageTransform;`
- L41 _parameter_ `float4 LodDistances;`
- L42 _parameter_ `float LodBiasScale;`
- L43 _parameter_ `float3 ViewOrigin;`
- L44 _parameter_ `float4 FrustumPlanes[5];`
- L45 _parameter_ `float4x4 UVToWorld;`
- L46 _parameter_ `float3 UVToWorldScale;`
- L48 _parameter_ `int NumIndices;`

#### groupshared (1)

- L8 _groupshared_ `groupshared uint NumGroupTasks;`

#### Functions (10)

- L52-56 _function_ `uint GetVirtualLevelFromPhysicalAddress(uint InPhysicalAddress)` — Unpack the virtual level for a PhysicalAddress entry in the virtual texture page table.
- L59-72 _function_ `float2 VirtualToPhysicalUV(float2 InVirtualUV, uint InPhysicalAddress, float4 InTransformFactors, uint InNumAddressBits)` — Compute physical UV from virtual UV in the tile with the given PhysicalAddress.
- L75-86 _function_ `float3 GetVirtualToPhysicalUVTransform(uint2 InPos, uint InLevel, uint InPhysicalAddress, float4 InTransformFactors, uint InNumAddressBits)` — Returns transform from virtual to physical UV in the tile with the given PhysicalAddress. Returns float3 where .xy is bias and .z is scale.
- L89-97 _function_ `bool OcclusionTest(uint2 InPos, int InLevel)` — Return false if location is marked as occluded in the occlusion texture.
- L100-106 _function_ `float2 UnPackMinMaxHeight(float4 InPacked)` — Unpack the values from the MinMaxHeight texture from the packed 8888 format.
- L109-112 _function_ `float2 UnPackMinMaxLodBias(float4 InPacked, float InLodBiasScale)` — Unpack the values from the MinMaxLodBias texture from the packed 8888 format.
- L115-132 _function_ `bool PlaneTestAABB(float4 InPlanes[5], float3 InCenter, float3 InExtent)` — Return false if the AABB is completely outside one of the planes.
- L135-140 _function_ `float SquaredMinDistanceToAABB(float3 InPos, float3 InMin, float3 InMax, float3 InScale)` — Return squared distance of closest distance between a point and a bounding box.
- L143-147 _function_ `float SquaredMaxDistanceToAABB(float3 InPos, float3 InMin, float3 InMax, float3 InScale)` — Return squared distance of furthest distance between a point and a bounding box.
- L150-170 _function_ `void DebugDrawUVBox(float3 InUVMin, float3 InUVMax, float4x4 InTransform, float4 InColor)` — Draw a bounding box using the ShaderDrawDebug system.

#### Top-level macro invocations (1)

- L216 _macro_call_ `WAVESIZE(32)` _[#if COMPILER_SUPPORTS_WAVE_SIZE]_

### `Plugins/Experimental/VirtualHeightfieldMesh/Shaders/Private/VirtualHeightfieldMesh.ush` (Private)

- lines: 122; parse: all-branches
- L3 #pragma `once`

#### Structs / classes (4)

- L11-16 _struct_ **`WorkerQueueInfo`** `struct WorkerQueueInfo` — Structure used for tracking work queues in persistent wave style shaders.
  - L13 _member_ `uint Read;`
  - L14 _member_ `uint Write;`
  - L15 _member_ `int NumActive;`
- L19-23 _struct_ **`QuadItem`** `struct QuadItem` — Item description used when traversing the virtual page table quad tree. Packs as uint so store in Buffer declared as uint.
  - L21 _member_ `uint Address;`
  - L22 _member_ `uint Level;`
- L50-56 _struct_ **`QuadRenderItem`** `struct QuadRenderItem` — Description for items that are output by the quad tree collect stage. Packs as uint2 so store in Buffer declared as uint2.
  - L52 _member_ `uint2 Pos;`
  - L53 _member_ `uint Level;`
  - L54 _member_ `uint PhysicalAddress;`
  - L55 _member_ `bool bCull;`
- L91-95 _struct_ **`QuadRenderInstance`** `struct QuadRenderInstance` — Final render instance description used by the DrawInstancedIndirect().
  - L93 _member_ `float3 UVTransform;`
  - L94 _member_ `uint PosLevelPacked;`

#### Functions (10)

- L25-31 _function_ `uint Pack(QuadItem Item)`
- L33-39 _function_ `QuadItem InitQuadItem(uint Address, uint Level)`
- L41-47 _function_ `QuadItem UnpackQuadItem(uint PackedItem)`
- L58-67 _function_ `uint2 Pack(QuadRenderItem Item)`
- L69-77 _function_ `QuadRenderItem InitQuadRenderItem(uint2 Pos, uint Level, uint PhysicalAddress, bool bCull)`
- L79-88 _function_ `QuadRenderItem UnpackQuadRenderItem(uint2 PackedItem)`
- L97-100 _function_ `uint2 UnpackPos(QuadRenderInstance Item)`
- L102-105 _function_ `uint UnpackLevel(QuadRenderInstance Item)`
- L109-115 _function_ `float CalculateDistanceLod(float InDistanceSq, float4 InLodFactors)` — Shared helper function to calculate a LOD based on distance from camera.
- L118-121 _function_ `float CalculateBiasLod(float InValue, float InLodBiasScale)` — Shared helper function to calculate a LOD bias based on our LodBias texture value.

### `Plugins/Experimental/VirtualHeightfieldMesh/Shaders/Private/VirtualHeightfieldMeshVertexFactory.ush` (Private)

- lines: 346; parse: all-branches
- includes: L3 `/Engine/Private/VertexFactoryCommon.ush`, L4 `/Engine/Private/VirtualTextureCommon.ush`, L5 `VirtualHeightfieldMesh.ush`, L345 `/Engine/Private/VertexFactoryDefaultInterface.ush`

#### Macros (#define, 2)

- L7 `#define GRID_SIZE (VHM.NumQuadsPerTileSide+1)`
- L14 `#define GetInstanceIdFromVF(VFInput) (VFInput.InstanceId)`
- L13 #undef `GetInstanceIdFromVF`

#### Structs / classes (3)

- L17-22 _struct_ **`FVertexFactoryInput`** `struct FVertexFactoryInput` — Per-vertex inputs. No vertex buffers are bound.
  - L19 _member_ `uint InstanceId : SV_InstanceID;`
  - L20 _member_ `uint VertexId : SV_VertexID;`
- L25-33 _struct_ **`FVertexFactoryIntermediates`** `struct FVertexFactoryIntermediates` — Cached intermediates that would otherwise have to be computed multiple times. Avoids relying on the compiler to optimize out redundant operations.
  - L27 _member_ `float2 LocalUV;`
  - L28 _member_ `float3 VTPos;`
  - L29 _member_ `float3 LocalPos;`
  - L30 _member_ `float3 WorldNormal;`
  - L32 _member_ `FSceneDataIntermediates SceneData;` — Cached primitive and instance data
- L41-46 _struct_ **`FVertexFactoryInterpolantsVSToPS`** `struct FVertexFactoryInterpolantsVSToPS` — Attributes to interpolate from the vertex shader to the pixel shader.
  - L44 _member_ `float4 TexCoords[(NUM_TEX_COORD_INTERPOLATORS + 1) / 2] : TEXCOORD0;` _[#if NUM_TEX_COORD_INTERPOLATORS]_

#### Global resources (textures / buffers / samplers) (1)

- L9 _resource_ `StructuredBuffer<QuadRenderInstance> InstanceBuffer;`

#### Global parameters (uniforms) (2)

- L10 _parameter_ `float3 LodViewOrigin;`
- L11 _parameter_ `float4 LodDistances;`

#### Functions (20)

- L35-38 _function_ `FPrimitiveSceneData GetPrimitiveData(FVertexFactoryIntermediates Intermediates)`
- L49-52 _function_ `float GetLodBias(float2 InUV, float InLodBiasScale)` — Fetch the lod bias for the location.
- L55-70 _function_ `float2 MorphVertex(float2 InLocalUV, uint InGridSize, uint InMorphFactorFloor, float InMorphFactorFrac)` — Helper to morph the UV location of a vertex. First snaps down InMorphFactorFloor LOD levels and then morphs InMorphFactorFrac towards the next LOD level.
- L73-149 _function_ `FVertexFactoryIntermediates GetVertexFactoryIntermediates(FVertexFactoryInput Input)` — Compute the intermediates for a given vertex.
- L155-199 _function_ `FMaterialVertexParameters GetMaterialVertexParameters( FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, float3 WorldPosition, half3x3 TangentToLocal, bool bIsPreviousFrame = false)` — Converts from vertex factory specific input to a FMaterialVertexParameters, which is used by vertex shader material inputs.
- L202-205 _function_ `uint GetPrimitiveId(FVertexFactoryInterpolantsVSToPS Interpolants)` — Get ID in GPU Scene. We don't implement support because we create/consume our own instancing buffer.
- L208-211 _function_ `uint VertexFactoryGetPrimitiveId(FVertexFactoryInterpolantsVSToPS Interpolants)` — Get ID in the GPU Scene.
- L214-218 _function_ `float4 VertexFactoryGetWorldPosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)` — Computes the world space position of this vertex.
- L221-224 _function_ `float3 VertexFactoryGetInstanceSpacePosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)` — local position relative to instance
- L227-239 _function_ `float4 VertexFactoryGetRasterizedWorldPosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, float4 InWorldPosition)` — Computes the world space position of this vertex.
- L242-245 _function_ `float3 VertexFactoryGetPositionForVertexLighting(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, float3 TranslatedWorldPosition)` — Computes the world space position used by vertex lighting for this vertex.
- L248-251 _function_ `float4 VertexFactoryGetPreviousWorldPosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)` — Computes the world space position of this vertex last frame.
- L254-257 _function_ `float3 VertexFactoryGetPreviousInstanceSpacePosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)` — Computes the instance space position of this vertex last frame.
- L260-263 _function_ `float3 VertexFactoryGetWorldNormal(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)` — Computes the world space normal of this vertex.
- L266-269 _function_ `half3x3 VertexFactoryGetTangentToLocal(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)` — Get the 3x3 tangent basis vectors for this vertex factory. This vertex factory will calculate the binormal on-the-fly.
- L272-276 _function_ `float4 VertexFactoryGetTranslatedPrimitiveVolumeBounds(FVertexFactoryInterpolantsVSToPS Interpolants)` — Get the translated bounding sphere for this primitive.
- L280-291 _function_ `void SetUV(inout FVertexFactoryInterpolantsVSToPS Interpolants, uint UVIndex, float2 InValue)` _[#if NUM_TEX_COORD_INTERPOLATORS]_
- L293-297 _function_ `float2 GetUV(FVertexFactoryInterpolantsVSToPS Interpolants, uint UVIndex)` _[#if NUM_TEX_COORD_INTERPOLATORS]_
- L302-323 _function_ `FVertexFactoryInterpolantsVSToPS VertexFactoryGetInterpolantsVSToPS(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates, FMaterialVertexParameters VertexParameters)` — Constructs values that need to be interpolated from the vertex shader to the pixel shader.
- L326-343 _function_ `FMaterialPixelParameters GetMaterialPixelParameters(FVertexFactoryInterpolantsVSToPS Interpolants, float4 SvPosition)` — Converts from vertex factory specific interpolants to a FMaterialPixelParameters, which is used by material inputs.

#### Prototypes (2)

- L151 _prototype_ `float3 VertexFactoryGetPreviousInstanceSpacePosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)`
- L152 _prototype_ `float3 VertexFactoryGetInstanceSpacePosition(FVertexFactoryInput Input, FVertexFactoryIntermediates Intermediates)`

#### Top-level macro invocations (1)

- L21-22 _macro_call_ `VF_MOBILE_MULTI_VIEW_DECLARE_INPUT_BLOCK()` (scope `FVertexFactoryInput`)

#### C++ shader bindings (IMPLEMENT_* naming this file, 1)

- `EVertexFactoryFlags::UsedWithMaterials
	\| EVertexFactoryFlags::SupportsDynamicLighting
	\| EVertexFactoryFlags::SupportsPrimitiveIdStream` → entry not found in file (macro-generated or #include'd); C++ `FVirtualHeightfieldMeshVertexFactory`  via IMPLEMENT_VERTEX_FACTORY_TYPE (Plugins/Experimental/VirtualHeightfieldMesh/Source/VirtualHeightfieldMesh/Private/VirtualHeightfieldMeshVertexFactory.cpp:227)
