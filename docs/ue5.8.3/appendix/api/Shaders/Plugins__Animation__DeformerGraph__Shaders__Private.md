# Shaders / Plugins/Animation/DeformerGraph/Shaders/Private

- files: 22; lines: 1298
- record kinds: define=9, function=87, include=9, member=11, method=5, parameter=64, resource=38, struct=3

### `Plugins/Animation/DeformerGraph/Shaders/Private/DataInterfaceAdvancedSkeleton.ush` (Private)

- lines: 117; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)
- includes: L3 `/Plugin/Optimus/Private/DataInterfaceSkeletonCommon.ush`

#### Global resources (textures / buffers / samplers) (3)

- L10 _resource_ `Buffer<uint> {DataInterfaceName}_InputWeightStream;`
- L11 _resource_ `Buffer<uint> {DataInterfaceName}_InputWeightLookupStream;`
- L13 _resource_ `StructuredBuffer<float3x4> {DataInterfaceName}_LayeredBoneMatrices;`

#### Global parameters (uniforms) (5)

- L5 _parameter_ `uint {DataInterfaceName}_NumVertices;`
- L6 _parameter_ `uint {DataInterfaceName}_NumBoneInfluences;`
- L7 _parameter_ `uint {DataInterfaceName}_InputWeightStride;`
- L8 _parameter_ `uint {DataInterfaceName}_InputWeightIndexSize;`
- L9 _parameter_ `FCompressedBoneTransformBuffer {DataInterfaceName}_BoneMatrices;`

#### Functions (7)

- L15-18 _function_ `uint ReadNumVertices_{DataInterfaceName}()`
- L20-27 _function_ `uint ReadNumBones_{DataInterfaceName}(uint VertexIndex)`
- L29-40 _function_ `float3x4 ReadBoneMatrix_{DataInterfaceName}(uint VertexIndex, uint BoneIndex)`
- L42-53 _function_ `float ReadBoneWeight_{DataInterfaceName}(uint VertexIndex, uint BoneIndex)`
- L55-66 _function_ `float3x4 ReadWeightedBoneMatrix_{DataInterfaceName}(uint VertexIndex)`
- L69-96 _function_ `float3x4 ReadLayeredBoneMatrix_{DataInterfaceName}(uint VertexIndex, uint BoneIndex)`
- L98-117 _function_ `float3x4 ReadWeightedLayeredBoneMatrix_{DataInterfaceName}(uint VertexIndex)`

### `Plugins/Animation/DeformerGraph/Shaders/Private/DataInterfaceAdvancedSkeletonAnimAttribute.ush` (Private)

- lines: 33; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global resources (textures / buffers / samplers) (1)

- L3 _resource_ `StructuredBuffer<{TypeName}> {DataInterfaceName}_{AttributeName};`

#### Functions (1)

- L6-33 _function_ `{TypeName} Read{AttributeName}_{DataInterfaceName}(uint VertexIndex, uint BoneIndex)`

### `Plugins/Animation/DeformerGraph/Shaders/Private/DataInterfaceCloth.ush` (Private)

- lines: 206; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Macros (#define, 1)

- L4 `#define DATA_INTERFACE_CLOTH_ONCE 1` _[#if !defined(DATA_INTERFACE_CLOTH_ONCE)]_

#### Structs / classes (2)

- L6-13 _struct_ **`FVertexTriangleInfluence`** `struct FVertexTriangleInfluence` _[#if !defined(DATA_INTERFACE_CLOTH_ONCE)]_
  - L8 _member_ `float4 PositionBaryCoordsAndDist;` _[#if !defined(DATA_INTERFACE_CLOTH_ONCE)]_
  - L9 _member_ `float4 NormalBaryCoordsAndDist;` _[#if !defined(DATA_INTERFACE_CLOTH_ONCE)]_
  - L10 _member_ `float4 TangentBaryCoordsAndDist;` _[#if !defined(DATA_INTERFACE_CLOTH_ONCE)]_
  - L11 _member_ `uint4 SourceMeshVertIndices;` _[#if !defined(DATA_INTERFACE_CLOTH_ONCE)]_
  - L12 _member_ `float Weight;` _[#if !defined(DATA_INTERFACE_CLOTH_ONCE)]_
- L15-21 _struct_ **`FClothResult`** `struct FClothResult` _[#if !defined(DATA_INTERFACE_CLOTH_ONCE)]_
  - L17 _member_ `float ClothWeight;` _[#if !defined(DATA_INTERFACE_CLOTH_ONCE)]_
  - L18 _member_ `float3 Position;` _[#if !defined(DATA_INTERFACE_CLOTH_ONCE)]_
  - L19 _member_ `float3 TangentX;` _[#if !defined(DATA_INTERFACE_CLOTH_ONCE)]_
  - L20 _member_ `float3 TangentZ;` _[#if !defined(DATA_INTERFACE_CLOTH_ONCE)]_

#### Global resources (textures / buffers / samplers) (2)

- L32 _resource_ `Buffer<float4> {DataInterfaceName}_ClothBuffer;`
- L33 _resource_ `Buffer<float2> {DataInterfaceName}_ClothPositionsAndNormalsBuffer;`

#### Global parameters (uniforms) (7)

- L25 _parameter_ `uint {DataInterfaceName}_NumVertices;`
- L26 _parameter_ `uint {DataInterfaceName}_BaseVertexIndex;`
- L27 _parameter_ `uint {DataInterfaceName}_InputStreamStart;`
- L28 _parameter_ `uint {DataInterfaceName}_NumInfluencesPerVertex;`
- L29 _parameter_ `float {DataInterfaceName}_ClothBlendWeight;`
- L30 _parameter_ `float3 {DataInterfaceName}_MeshScale;`
- L31 _parameter_ `float4x4 {DataInterfaceName}_ClothToLocal;`

#### Functions (8)

- L35-38 _function_ `uint ReadNumVertices_{DataInterfaceName}()`
- L40-47 _function_ `float4x4 ReadClothToLocal_{DataInterfaceName}()`
- L49-69 _function_ `FVertexTriangleInfluence GetClothInfluence_{DataInterfaceName}(uint VertexIndex, uint InfluenceIndex)`
- L71-161 _function_ `FClothResult GetClothResult_{DataInterfaceName}(uint VertexIndex)`
- L167-175 _function_ `float ReadClothWeight_{DataInterfaceName}(uint VertexIndex)`
- L177-185 _function_ `float3 ReadClothPosition_{DataInterfaceName}(uint VertexIndex)`
- L187-195 _function_ `float3 ReadClothTangentX_{DataInterfaceName}(uint VertexIndex)`
- L197-205 _function_ `float3 ReadClothTangentZ_{DataInterfaceName}(uint VertexIndex)`

### `Plugins/Animation/DeformerGraph/Shaders/Private/DataInterfaceConnectivity.ush` (Private)

- lines: 23; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global resources (textures / buffers / samplers) (1)

- L5 _resource_ `StructuredBuffer<uint> {DataInterfaceName}_ConnectivityBuffer;`

#### Global parameters (uniforms) (2)

- L3 _parameter_ `uint {DataInterfaceName}_NumVertices;`
- L4 _parameter_ `uint {DataInterfaceName}_MaxConnectedVertexCount;`

#### Functions (3)

- L7-10 _function_ `uint ReadNumVertices_{DataInterfaceName}()`
- L12-15 _function_ `uint ReadNumConnectedVertices_{DataInterfaceName}(uint VertexIndex)`
- L17-22 _function_ `uint ReadConnectedVertex_{DataInterfaceName}(uint VertexIndex, uint ConnectedVertexSubIndex)`

### `Plugins/Animation/DeformerGraph/Shaders/Private/DataInterfaceCopyKernel.ush` (Private)

- lines: 20; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global parameters (uniforms) (3)

- L3 _parameter_ `uint3 {DataInterfaceName}_NumThreads;`
- L4 _parameter_ `uint {DataInterfaceName}_NumThreadsPerInvocation;`
- L5 _parameter_ `uint {DataInterfaceName}_ThreadIndexOffset;`

#### Functions (3)

- L7-10 _function_ `uint3 ReadNumThreads_{DataInterfaceName}()`
- L12-15 _function_ `uint ReadNumThreadsPerInvocation_{DataInterfaceName}()`
- L17-20 _function_ `uint ReadThreadIndexOffset_{DataInterfaceName}()`

### `Plugins/Animation/DeformerGraph/Shaders/Private/DataInterfaceCustomComputeKernel.ush` (Private)

- lines: 20; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global parameters (uniforms) (3)

- L3 _parameter_ `uint3 {DataInterfaceName}_NumThreads;`
- L4 _parameter_ `uint {DataInterfaceName}_NumThreadsPerInvocation;`
- L5 _parameter_ `uint {DataInterfaceName}_ThreadIndexOffset;`

#### Functions (3)

- L7-10 _function_ `uint3 ReadNumThreads_{DataInterfaceName}()`
- L12-15 _function_ `uint ReadNumThreadsPerInvocation_{DataInterfaceName}()`
- L17-20 _function_ `uint ReadThreadIndexOffset_{DataInterfaceName}()`

### `Plugins/Animation/DeformerGraph/Shaders/Private/DataInterfaceDebugDraw.ush` (Private)

- lines: 80; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)
- includes: L3 `/Engine/Private/ShaderPrintCommon.ush`

#### Macros (#define, 1)

- L6 `#define DATA_INTERFACE_DEBUGDRAW_ONCE 1` _[#if !defined(DATA_INTERFACE_DEBUGDRAW_ONCE)]_

#### Structs / classes (1)

- L8-43 _struct_ **`FDebugDraw`** `struct FDebugDraw` _[#if !defined(DATA_INTERFACE_DEBUGDRAW_ONCE)]_
  - L10 _member_ `FShaderPrintContext Context;` _[#if !defined(DATA_INTERFACE_DEBUGDRAW_ONCE)]_
  - L11 _member_ `float4x4 LocalToWorld;` _[#if !defined(DATA_INTERFACE_DEBUGDRAW_ONCE)]_
  - L13 _method_ `float3 TransformLocalToWorld(float3 P)` _[#if !defined(DATA_INTERFACE_DEBUGDRAW_ONCE)]_
  - L18 _method_ `void AddLine(float3 Pos0, float3 Pos1, float4 Color)` _[#if !defined(DATA_INTERFACE_DEBUGDRAW_ONCE)]_
  - L23 _method_ `void AddCross(float3 Pos, float Size, float4 Color)` _[#if !defined(DATA_INTERFACE_DEBUGDRAW_ONCE)]_
  - L28 _method_ `void AddQuad(float3 Pos0, float3 Pos1, float3 Pos2, float3 Pos3, float4 Color)` _[#if !defined(DATA_INTERFACE_DEBUGDRAW_ONCE)]_
  - L39 _method_ `void AddAxis(float3 Pos, float3x3 InM, float Scale)` _[#if !defined(DATA_INTERFACE_DEBUGDRAW_ONCE)]_

#### Global resources (textures / buffers / samplers) (2)

- L56 _resource_ `Buffer<uint> {DataInterfaceName}_StateBuffer;`
- L57 _resource_ `RWBuffer<uint> {DataInterfaceName}_RWEntryBuffer;`

#### Global parameters (uniforms) (9)

- L47 _parameter_ `float4x4 {DataInterfaceName}_LocalToWorld;`
- L48 _parameter_ `int2 {DataInterfaceName}_Resolution;`
- L49 _parameter_ `float2 {DataInterfaceName}_FontSize;`
- L50 _parameter_ `float2 {DataInterfaceName}_FontSpacing;`
- L51 _parameter_ `uint {DataInterfaceName}_MaxCharacterCount;`
- L52 _parameter_ `uint {DataInterfaceName}_MaxSymbolCount;`
- L53 _parameter_ `uint {DataInterfaceName}_MaxStateCount;`
- L54 _parameter_ `uint {DataInterfaceName}_MaxLineCount;`
- L55 _parameter_ `uint {DataInterfaceName}_MaxTriangleCount;`

#### Functions (1)

- L59-79 _function_ `FDebugDraw ReadDebugDraw_{DataInterfaceName}()`

### `Plugins/Animation/DeformerGraph/Shaders/Private/DataInterfaceDuplicateVertices.ush` (Private)

- lines: 37; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global resources (textures / buffers / samplers) (2)

- L6 _resource_ `Buffer<uint> {DataInterfaceName}_DuplicateVertexStartAndLength;`
- L7 _resource_ `Buffer<uint> {DataInterfaceName}_DuplicateVertices;`

#### Global parameters (uniforms) (3)

- L3 _parameter_ `uint {DataInterfaceName}_NumVertices;`
- L4 _parameter_ `uint {DataInterfaceName}_NumDuplicateVertices;`
- L5 _parameter_ `uint {DataInterfaceName}_BaseVertexIndex;`

#### Functions (4)

- L9-12 _function_ `uint ReadNumVertices_{DataInterfaceName}()`
- L14-17 _function_ `uint ReadNumDuplicateVertices_{DataInterfaceName}()`
- L19-27 _function_ `int2 ReadDuplicateVerticesStartAndLength_{DataInterfaceName}(uint VertexIndex)`
- L29-36 _function_ `uint ReadDuplicateVertex_{DataInterfaceName}(uint Index)`

### `Plugins/Animation/DeformerGraph/Shaders/Private/DataInterfaceHalfEdge.ush` (Private)

- lines: 37; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global resources (textures / buffers / samplers) (4)

- L5 _resource_ `StructuredBuffer<int> {DataInterfaceName}_VertexToEdgeBuffer;`
- L6 _resource_ `StructuredBuffer<int> {DataInterfaceName}_EdgeToTwinEdgeBuffer;`
- L9 _resource_ `StructuredBuffer<int> {DataInterfaceName}_RenderDataVertexToEdgeBuffer;`
- L10 _resource_ `StructuredBuffer<int> {DataInterfaceName}_RenderDataEdgeToTwinEdgeBuffer;`

#### Global parameters (uniforms) (3)

- L3 _parameter_ `uint {DataInterfaceName}_NumVertices;`
- L4 _parameter_ `uint {DataInterfaceName}_NumTriangles;`
- L8 _parameter_ `uint {DataInterfaceName}_bUseBufferFromRenderData;`

#### Functions (4)

- L12-15 _function_ `uint ReadNumVertices_{DataInterfaceName}()`
- L17-20 _function_ `uint ReadNumTriangles_{DataInterfaceName}()`
- L22-27 _function_ `int ReadEdge_{DataInterfaceName}(uint VertexIndex)`
- L29-36 _function_ `int ReadTwinEdge_{DataInterfaceName}(uint EdgeIndex)`

### `Plugins/Animation/DeformerGraph/Shaders/Private/DataInterfaceLoopTerminal.ush` (Private)

- lines: 16; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global parameters (uniforms) (2)

- L3 _parameter_ `uint {DataInterfaceName}_Index;`
- L4 _parameter_ `uint {DataInterfaceName}_Count;`

#### Functions (2)

- L6-9 _function_ `uint ReadIndex_{DataInterfaceName}()`
- L11-14 _function_ `uint ReadCount_{DataInterfaceName}()`

### `Plugins/Animation/DeformerGraph/Shaders/Private/DataInterfaceMorphTarget.ush` (Private)

- lines: 30; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global resources (textures / buffers / samplers) (1)

- L4 _resource_ `Buffer<float> {DataInterfaceName}_MorphBuffer;`

#### Global parameters (uniforms) (1)

- L3 _parameter_ `uint {DataInterfaceName}_NumVertices;`

#### Functions (3)

- L6-9 _function_ `uint ReadNumVertices_{DataInterfaceName}()`
- L11-19 _function_ `float3 ReadDeltaPosition_{DataInterfaceName}(uint VertexIndex)`
- L21-29 _function_ `float3 ReadDeltaNormal_{DataInterfaceName}(uint VertexIndex)`

### `Plugins/Animation/DeformerGraph/Shaders/Private/DataInterfaceRawBuffer.ush` (Private)

- lines: 109; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)
- includes: L3 `/Plugin/ComputeFramework/Private/BufferAlias.ush`

#### Macros (#define, 5)

- L8 `#define PUBLIC_TYPE {PublicType}`
- L9 `#define BUFFER_TYPE {BufferType}`
- L10 `#define BUFFER_TYPE_RAW {BufferTypeRaw}`
- L12 `#define BUFFER_TYPE_SUPPORTS_ATOMIC {SupportAtomic}`
- L14 `#define BUFFER_SPLIT_READ_WRITE {SplitReadWrite}`
- L104 #undef `PUBLIC_TYPE`; L105 #undef `BUFFER_TYPE`; L106 #undef `BUFFER_TYPE_RAW`; L107 #undef `BUFFER_TYPE_SUPPORTS_ATOMIC`; L108 #undef `BUFFER_SPLIT_READ_WRITE`

#### Global resources (textures / buffers / samplers) (2)

- L18 _resource_ `StructuredBuffer<BUFFER_TYPE> {DataInterfaceName}_BufferSRV;` _[#if BUFFER_SPLIT_READ_WRITE]_
- L20 _resource_ `RWStructuredBuffer<BUFFER_TYPE> {DataInterfaceName}_BufferUAV;`

#### Global parameters (uniforms) (1)

- L16 _parameter_ `uint {DataInterfaceName}_BufferSize;`

#### Functions (7)

- L22-25 _function_ `uint ReadNumValues_{DataInterfaceName}()`
- L27-45 _function_ `PUBLIC_TYPE ReadValue_{DataInterfaceName}(uint Index)`
- L47-59 _function_ `PUBLIC_TYPE ReadValueUAV_{DataInterfaceName}(uint Index)`
- L61-69 _function_ `void WriteValue_{DataInterfaceName}(uint Index, PUBLIC_TYPE Value)`
- L71-80 _function_ `PUBLIC_TYPE WriteAtomicAdd_{DataInterfaceName}(uint Index, PUBLIC_TYPE Value)`
- L82-91 _function_ `PUBLIC_TYPE WriteAtomicMin_{DataInterfaceName}(uint Index, PUBLIC_TYPE Value)`
- L93-102 _function_ `PUBLIC_TYPE WriteAtomicMax_{DataInterfaceName}(uint Index, PUBLIC_TYPE Value)`

### `Plugins/Animation/DeformerGraph/Shaders/Private/DataInterfaceScene.ush` (Private)

- lines: 21; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global parameters (uniforms) (3)

- L3 _parameter_ `float {DataInterfaceName}_GameTime;`
- L4 _parameter_ `float {DataInterfaceName}_GameTimeDelta;`
- L5 _parameter_ `uint {DataInterfaceName}_FrameNumber;`

#### Functions (3)

- L7-10 _function_ `float ReadGameTime_{DataInterfaceName}()`
- L12-15 _function_ `float ReadGameTimeDelta_{DataInterfaceName}()`
- L17-20 _function_ `float ReadFrameNumber_{DataInterfaceName}()`

### `Plugins/Animation/DeformerGraph/Shaders/Private/DataInterfaceSceneComponent.ush` (Private)

- lines: 8; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global parameters (uniforms) (1)

- L3 _parameter_ `float4x4 {DataInterfaceName}_WorldTransform;`

#### Functions (1)

- L5-8 _function_ `float4x4 ReadWorldTransform_{DataInterfaceName}()`

### `Plugins/Animation/DeformerGraph/Shaders/Private/DataInterfaceSkeleton.ush` (Private)

- lines: 65; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)
- includes: L3 `/Plugin/Optimus/Private/DataInterfaceSkeletonCommon.ush`

#### Global resources (textures / buffers / samplers) (2)

- L10 _resource_ `Buffer<uint> {DataInterfaceName}_InputWeightStream;`
- L11 _resource_ `Buffer<uint> {DataInterfaceName}_InputWeightLookupStream;`

#### Global parameters (uniforms) (5)

- L5 _parameter_ `uint {DataInterfaceName}_NumVertices;`
- L6 _parameter_ `uint {DataInterfaceName}_NumBoneInfluences;`
- L7 _parameter_ `uint {DataInterfaceName}_InputWeightStride;`
- L8 _parameter_ `uint {DataInterfaceName}_InputWeightIndexSize;`
- L9 _parameter_ `FCompressedBoneTransformBuffer {DataInterfaceName}_BoneMatrices;`

#### Functions (5)

- L13-16 _function_ `uint ReadNumVertices_{DataInterfaceName}()`
- L18-25 _function_ `uint ReadNumBones_{DataInterfaceName}(uint VertexIndex)`
- L27-38 _function_ `float3x4 ReadBoneMatrix_{DataInterfaceName}(uint VertexIndex, uint BoneIndex)`
- L40-51 _function_ `float ReadBoneWeight_{DataInterfaceName}(uint VertexIndex, uint BoneIndex)`
- L53-64 _function_ `float3x4 ReadWeightedBoneMatrix_{DataInterfaceName}(uint VertexIndex)`

### `Plugins/Animation/DeformerGraph/Shaders/Private/DataInterfaceSkeletonCommon.ush` (Private)

- lines: 146; parse: all-branches
- includes: L3 `/Engine/Private/GpuSkinCommon.ush`
- L2 #pragma `once`

#### Functions (5)

- L5-20 _function_ `uint ReadNumBones( Buffer<uint> InputWeightLookupStream, uint NumBoneInfluences, uint VertexIndex )`
- L22-62 _function_ `float ReadBoneWeight( Buffer<uint> InputWeightLookupStream, uint InputWeightIndexSize, Buffer<uint> InputWeightStream, uint InputWeightStride, uint NumBoneInfluences, uint VertexIndex, uint BoneIndex )`
- L64-67 _function_ `float3x4 GetBoneMatrix(FCompressedBoneTransformBuffer BoneMatrices, uint BoneIndex)`
- L69-104 _function_ `float3x4 ReadBoneMatrix( Buffer<uint> InputWeightLookupStream, uint InputWeightIndexSize, Buffer<uint> InputWeightStream, uint InputWeightStride, FCompressedBoneTransformBuffer BoneMatrices, uint VertexIndex, uint BoneIndex )`
- L106-145 _function_ `float3x4 ReadWeightedBoneMatrix( Buffer<uint> InputWeightLookupStream, uint InputWeightIndexSize, Buffer<uint> InputWeightStream, uint InputWeightStride, uint NumBoneInfluences, FCompressedBoneTransformBuffer BoneMatrices, uint VertexIndex )`

### `Plugins/Animation/DeformerGraph/Shaders/Private/DataInterfaceSkinWeightsAsVertexMask.ush` (Private)

- lines: 94; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)
- includes: L3 `/Plugin/Optimus/Private/DataInterfaceSkeletonCommon.ush`

#### Global resources (textures / buffers / samplers) (3)

- L9 _resource_ `Buffer<uint> {DataInterfaceName}_InputWeightStream;`
- L10 _resource_ `Buffer<uint> {DataInterfaceName}_InputWeightLookupStream;`
- L12 _resource_ `StructuredBuffer<uint> {DataInterfaceName}_BoneIsSelected;`

#### Global parameters (uniforms) (4)

- L5 _parameter_ `uint {DataInterfaceName}_NumVertices;`
- L6 _parameter_ `uint {DataInterfaceName}_NumBoneInfluences;`
- L7 _parameter_ `uint {DataInterfaceName}_InputWeightStride;`
- L8 _parameter_ `uint {DataInterfaceName}_InputWeightIndexSize;`

#### Functions (5)

- L14-17 _function_ `uint ReadNumVertices_{DataInterfaceName}()`
- L19-26 _function_ `uint ReadNumBones_{DataInterfaceName}(uint VertexIndex)`
- L28-39 _function_ `float ReadBoneWeight_{DataInterfaceName}(uint VertexIndex, uint BoneIndex)`
- L41-68 _function_ `uint ReadBoneIsSelected_{DataInterfaceName}(uint VertexIndex, uint BoneIndex)`
- L71-93 _function_ `float ReadMask_{DataInterfaceName}(uint VertexIndex)`

### `Plugins/Animation/DeformerGraph/Shaders/Private/DataInterfaceSkinnedMesh.ush` (Private)

- lines: 67; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)
- includes: L4 `/Engine/Private/GpuSkinCommon.ush`

#### Global resources (textures / buffers / samplers) (5)

- L9 _resource_ `Buffer<uint> {DataInterfaceName}_IndexBuffer;`
- L10 _resource_ `Buffer<float> {DataInterfaceName}_PositionInputBuffer;`
- L11 _resource_ `Buffer<SNORM float4> {DataInterfaceName}_TangentInputBuffer;`
- L12 _resource_ `Buffer<float4> {DataInterfaceName}_ColorInputBuffer;`
- L14 _resource_ `Buffer<float2> {DataInterfaceName}_UVInputBuffer;`

#### Global parameters (uniforms) (4)

- L6 _parameter_ `uint {DataInterfaceName}_NumVertices;`
- L7 _parameter_ `uint {DataInterfaceName}_NumTriangles;`
- L8 _parameter_ `uint {DataInterfaceName}_NumUVChannels;`
- L13 _parameter_ `uint {DataInterfaceName}_ColorIndexMask;`

#### Functions (9)

- L16-19 _function_ `uint ReadNumVertices_{DataInterfaceName}()`
- L21-24 _function_ `uint ReadNumTriangles_{DataInterfaceName}()`
- L26-29 _function_ `uint ReadNumUVChannels_{DataInterfaceName}()`
- L31-35 _function_ `uint ReadIndexBuffer_{DataInterfaceName}(uint Index)`
- L37-41 _function_ `float3 ReadPosition_{DataInterfaceName}(uint VertexIndex)`
- L43-47 _function_ `float4 ReadTangentX_{DataInterfaceName}(uint VertexIndex)`
- L49-53 _function_ `float4 ReadTangentZ_{DataInterfaceName}(uint VertexIndex)`
- L55-60 _function_ `float4 ReadColor_{DataInterfaceName}(uint VertexIndex)`
- L62-66 _function_ `float2 ReadUV_{DataInterfaceName}(uint VertexIndex, uint UVChannelIndex)`

### `Plugins/Animation/DeformerGraph/Shaders/Private/DataInterfaceSkinnedMeshExec.ush` (Private)

- lines: 9; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global parameters (uniforms) (1)

- L3 _parameter_ `int3 {DataInterfaceName}_NumThreads;`

#### Functions (1)

- L5-8 _function_ `int3 ReadNumThreads_{DataInterfaceName}()`

### `Plugins/Animation/DeformerGraph/Shaders/Private/DataInterfaceSkinnedMeshRead.ush` (Private)

- lines: 94; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)
- includes: L4 `/Engine/Private/GpuSkinCommon.ush`

#### Macros (#define, 2)

- L8 `#define TangentRead_SkinCache(X) (X / 32767.0)` _[#if OPENGL_PROFILE]_
- L10 `#define TangentRead_SkinCache(X) (X)` _[#if !(OPENGL_PROFILE)]_

#### Global resources (textures / buffers / samplers) (6)

- L15 _resource_ `Buffer<float> {DataInterfaceName}_PositionBufferSRV;`
- L16 _resource_ `Buffer<TANGENT_RWBUFFER_FORMAT> {DataInterfaceName}_TangentBufferSRV;`
- L17 _resource_ `Buffer<UNORM float4> {DataInterfaceName}_ColorBufferSRV;`
- L19 _resource_ `Buffer<float> {DataInterfaceName}_PositionStaticBuffer;`
- L20 _resource_ `Buffer<SNORM float4> {DataInterfaceName}_TangentStaticBuffer;`
- L21 _resource_ `Buffer<float4> {DataInterfaceName}_ColorStaticBuffer;`

#### Global parameters (uniforms) (3)

- L13 _parameter_ `uint {DataInterfaceName}_NumVertices;`
- L22 _parameter_ `uint {DataInterfaceName}_ColorIndexMask;`
- L23 _parameter_ `uint {DataInterfaceName}_ReadableOutputBuffers;`

#### Functions (5)

- L25-28 _function_ `uint ReadNumVertices_{DataInterfaceName}()`
- L30-48 _function_ `float3 ReadPosition_{DataInterfaceName}(uint VertexIndex)`
- L50-62 _function_ `float4 ReadTangentX_{DataInterfaceName}(uint VertexIndex)`
- L64-76 _function_ `float4 ReadTangentZ_{DataInterfaceName}(uint VertexIndex)`
- L78-91 _function_ `float4 ReadColor_{DataInterfaceName}(uint VertexIndex)`

### `Plugins/Animation/DeformerGraph/Shaders/Private/DataInterfaceSkinnedMeshVertexAttribute.ush` (Private)

- lines: 25; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global resources (textures / buffers / samplers) (1)

- L6 _resource_ `Buffer<float> {DataInterfaceName}_ValueBuffer;`

#### Global parameters (uniforms) (3)

- L3 _parameter_ `uint {DataInterfaceName}_NumVertices;`
- L4 _parameter_ `uint {DataInterfaceName}_bIsValid;`
- L5 _parameter_ `float {DataInterfaceName}_DefaultValue;`

#### Functions (2)

- L8-11 _function_ `uint ReadNumVertices_{DataInterfaceName}()`
- L13-24 _function_ `float ReadValue_{DataInterfaceName}(uint VertexIndex)`

### `Plugins/Animation/DeformerGraph/Shaders/Private/DataInterfaceSkinnedMeshWrite.ush` (Private)

- lines: 41; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)
- includes: L4 `/Engine/Private/GpuSkinCommon.ush`

#### Global resources (textures / buffers / samplers) (3)

- L7 _resource_ `RWBuffer<float> {DataInterfaceName}_PositionBufferUAV;`
- L8 _resource_ `RWBuffer<TANGENT_RWBUFFER_FORMAT> {DataInterfaceName}_TangentBufferUAV;`
- L9 _resource_ `RWBuffer<UNORM float4> {DataInterfaceName}_ColorBufferUAV;`

#### Global parameters (uniforms) (1)

- L6 _parameter_ `uint {DataInterfaceName}_NumVertices;`

#### Functions (5)

- L11-14 _function_ `uint ReadNumVertices_{DataInterfaceName}()`
- L16-22 _function_ `void WritePosition_{DataInterfaceName}(uint VertexIndex, float3 Position)`
- L24-28 _function_ `void WriteTangentX_{DataInterfaceName}(uint VertexIndex, float4 TangentX)`
- L30-34 _function_ `void WriteTangentZ_{DataInterfaceName}(uint VertexIndex, float4 TangentZ)`
- L36-40 _function_ `void WriteColor_{DataInterfaceName}(uint VertexIndex, float4 Color)`
