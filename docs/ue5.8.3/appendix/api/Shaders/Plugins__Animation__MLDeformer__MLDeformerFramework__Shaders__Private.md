# Shaders / Plugins/Animation/MLDeformer/MLDeformerFramework/Shaders/Private

- files: 2; lines: 269
- record kinds: function=16, parameter=10, resource=5

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Shaders/Private/MLDeformerModelHeatMap.ush` (Private)

- lines: 41; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global resources (textures / buffers / samplers) (2)

- L8 _resource_ `StructuredBuffer<float> {DataInterfaceName}_PositionGroundTruthBuffer;`
- L9 _resource_ `Buffer<uint> {DataInterfaceName}_VertexMapBuffer;`

#### Global parameters (uniforms) (5)

- L3 _parameter_ `uint {DataInterfaceName}_NumVertices;`
- L4 _parameter_ `uint {DataInterfaceName}_HeatMapMode;`
- L5 _parameter_ `float {DataInterfaceName}_HeatMapMax;`
- L6 _parameter_ `float {DataInterfaceName}_GroundTruthLerp;`
- L7 _parameter_ `uint {DataInterfaceName}_GroundTruthBufferSize;`

#### Functions (5)

- L11-14 _function_ `uint ReadNumVertices_{DataInterfaceName}()`
- L16-25 _function_ `float3 ReadPositionGroundTruth_{DataInterfaceName}(uint VertexIndex)`
- L27-30 _function_ `uint ReadHeatMapMode_{DataInterfaceName}()`
- L32-35 _function_ `float ReadHeatMapMax_{DataInterfaceName}()`
- L37-40 _function_ `float ReadGroundTruthLerp_{DataInterfaceName}()`

### `Plugins/Animation/MLDeformer/MLDeformerFramework/Shaders/Private/SkeletonWithWeightedQuats.ush` (Private)

- lines: 228; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global resources (textures / buffers / samplers) (3)

- L8 _resource_ `Buffer<float4> {DataInterfaceName}_BoneQuats;`
- L9 _resource_ `Buffer<uint> {DataInterfaceName}_InputWeightStream;`
- L10 _resource_ `Buffer<uint> {DataInterfaceName}_InputWeightLookupStream;`

#### Global parameters (uniforms) (5)

- L3 _parameter_ `uint {DataInterfaceName}_NumVertices;`
- L4 _parameter_ `uint {DataInterfaceName}_NumBoneInfluences;`
- L5 _parameter_ `uint {DataInterfaceName}_InputWeightStride;`
- L6 _parameter_ `uint {DataInterfaceName}_InputWeightIndexSize;`
- L7 _parameter_ `FCompressedBoneTransformBuffer {DataInterfaceName}_BoneMatrices;`

#### Functions (11)

- L12-15 _function_ `uint ReadNumVertices_{DataInterfaceName}()`
- L19-22 _function_ `int4 GetBlendIndices_{DataInterfaceName}(uint StreamOffset, uint ExtraInfluenceIndex)` _[#if !GPUSKIN_UNLIMITED_BONE_INFLUENCE]_
- L24-27 _function_ `float4 GetBlendWeights_{DataInterfaceName}(uint StreamOffset, uint ExtraInfluenceIndex)` _[#if !GPUSKIN_UNLIMITED_BONE_INFLUENCE]_
- L31-34 _function_ `float3x4 GetBoneMatrix_{DataInterfaceName}(uint BoneIndex)`
- L36-46 _function_ `uint ReadNumBones_{DataInterfaceName}(uint VertexIndex)`
- L48-75 _function_ `float3x4 ReadBoneMatrix_{DataInterfaceName}(uint VertexIndex, uint BoneIndex)`
- L77-109 _function_ `float ReadBoneWeight_{DataInterfaceName}(uint VertexIndex, uint BoneIndex)`
- L111-140 _function_ `float3x4 ReadWeightedBoneMatrix_{DataInterfaceName}(uint VertexIndex)`
- L142-145 _function_ `float4 GetBoneQuat_{DataInterfaceName}(uint BoneIndex)`
- L147-151 _function_ `float4 GetBoneQuatToBlend_{DataInterfaceName}(uint BoneIndex, float4 BoneQuat0, float Weight)`
- L153-227 _function_ `float4 ReadWeightedBoneQuat_{DataInterfaceName}(uint VertexIndex)`
