# Shaders / Shaders/Private/GPUScene

- files: 2; lines: 309
- record kinds: cpp_binding=1, define=1, entry=1, function=22, include=4

### `Shaders/Private/GPUScene/GPUSceneDataManagement.usf` (Private)

- lines: 25; parse: all-branches
- includes: L3 `../Common.ush`, L4 `GPUSceneWriter.ush`, L5 `../InstanceCulling/InstanceCullingLoadBalancer.ush`

#### Entry points (1)

- L10-24 _entry_ `[numthreads(NUM_THREADS_PER_GROUP, 1, 1)] void GPUSceneSetInstancePrimitiveIdCS(uint3 GroupId : SV_GroupID, int GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FGPUSceneSetInstancePrimitiveIdCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/GPUScene.cpp:2306) — Clear instances - set their primitive ID and set them to hidden.

### `Shaders/Private/GPUScene/GPUSceneWriter.ush` (Private)

- lines: 284; parse: all-branches
- includes: L15 `../SceneData.ush`

#### Macros (#define, 1)

- L13 `#define USE_GPU_SCENE_DATA_RW 1`
- L3 #pragma `once`

#### Functions (22)

- L17-25 _function_ `void StoreInstanceSceneDataElement(uint InstanceId, uint ElementIndex, float4 DataElement)`
- L27-37 _function_ `void StoreInstanceSceneDataElementX(uint InstanceId, uint ElementIndex, float Data)`
- L39-46 _function_ `void StoreInstancePayloadDataElement(uint PayloadDataOffset, uint ElementIndex, float4 DataElement)`
- L48-55 _function_ `void StoreInstancePayloadDataElementZW(uint PayloadDataOffset, uint ElementIndex, float2 DataElement)`
- L61-65 _function_ `void WriteInstancePrimitiveIdAndFlags(uint InstanceId, uint PrimitiveId, uint InstanceFlags)`
- L71-76 _function_ `void WriteInstancePrimitiveId(uint InstanceId, uint NewPrimitiveId)` — Store the contents of InstanceData.PrimitiveId to the GPUScene buffers. NOTE: As the primitive ID is packed with the instance flags, the flags are loaded and re-stored
- L85-109 _function_ `void WriteInstanceLocalToRelativeWorld(uint InstanceId, float4x4 LocalToRelativeWorld, bool StoreDeterminantSign)` — Store the contents of InstanceData.LocalToWorld to the GPUScene buffers. Optionally, also calculates the determinant of the transform's rotation to set or unset the determinant sign flag on the instance flags. NOTE: With Large World Coordinates, the transform provided is expected to be relative to the primitive's PositionHigh. Use the WriteInstanceLocalToWorld helper if you don't already have a relative transform.
- L111-116 _function_ `void WriteInstanceLocalToWorld(uint InstanceId, uint PrimitiveId, FDFMatrix LocalToWorld, bool StoreDeterminantSign)`
- L124-144 _function_ `void InitializeInstanceSceneData( uint InstanceId, uint PrimitiveId, uint InstanceRelativeId, uint InstanceFlags, uint CustomDataCount, float RandomId, float4x4 LocalToRelativeWorld)` — Initializes the instance scene data of the specified instance data slot using a LocalToWorld matrix that is already relative to its primitive's render tile position (When LWC. Otherwise, the matrix is simply LocalToWorld). Use InitializeInstanceSceneDataWS or InitializeInstanceSceneDataLS if you don't already have a LocalToRelativeWorldMatrix NOTE: This function must match FInstanceSceneShaderData::BuildInternal
- L147-158 _function_ `void InitializeInstanceSceneDataWS( uint InstanceId, uint PrimitiveId, uint InstanceRelativeId, uint PayloadDataFlags, uint CustomDataCount, float RandomId, FDFMatrix LocalToWorld)` — This version initializes the instance with a world-space transform
- L161-175 _function_ `void InitializeInstanceSceneDataLS( uint InstanceId, uint PrimitiveId, uint InstanceRelativeId, uint PayloadDataFlags, uint CustomDataCount, float RandomId, float4x4 LocalToPrimitive)` — This version initializes the instance with a transform that is relative to its primitive's local space
- L180-186 _function_ `FInstancePayloadDataOffsets GetInstancePayloadDataOffsets(uint InstanceId)` — Helper for loading instance payload offsets for GPU writers (assumes global parameter for SOA stride)
- L191-201 _function_ `void WriteInstanceLocalBounds(FInstancePayloadDataOffsets PayloadOffsets, float3 LocalCenter, float3 LocalExtent)` — Store the local instance bounds to the GPU Scene sidecar payload buffer.
- L203-207 _function_ `void WriteInstanceLocalBounds(uint InstanceId, float3 LocalCenter, float3 LocalExtent)`
- L213-234 _function_ `void WriteInstanceDynamicData(FInstancePayloadDataOffsets PayloadOffsets, float4x4 PrevLocalToRelativeWorld)` — Store the data for dynamic instances to the GPUScene sidecar payload buffer. Use WriteInstanceDynamicDataWS or WriteInstanceDynamicDataLS if you don't have a relative transform.
- L236-239 _function_ `void WriteInstanceDynamicData(uint InstanceId, float4x4 PrevLocalToRelativeWorld)`
- L242-246 _function_ `void WriteInstanceDynamicDataWS(FInstancePayloadDataOffsets PayloadOffsets, uint PrimitiveId, FDFMatrix PrevLocalToWorld)` — This version computes the relative transform from the specified world transform
- L248-251 _function_ `void WriteInstanceDynamicDataWS(uint InstanceId, uint PrimitiveId, FDFMatrix PrevLocalToWorld)`
- L254-258 _function_ `void WriteInstanceDynamicDataLS(FInstancePayloadDataOffsets PayloadOffsets, uint PrimitiveId, float4x4 PrevLocalToPrimitive)` — This version computes the relative transform from the specified local-space transform
- L260-263 _function_ `void WriteInstanceDynamicDataLS(uint InstanceId, uint PrimitiveId, float4x4 PrevLocalToPrimitive)`
- L268-278 _function_ `void WriteInstanceCustomData(FInstancePayloadDataOffsets PayloadOffsets, uint ElementIndex, float4 ElementData)` — Stores a float4 element of custom data for the given instance
- L280-284 _function_ `void WriteInstanceCustomData(uint InstanceId, uint ElementIndex, float4 ElementData)`
