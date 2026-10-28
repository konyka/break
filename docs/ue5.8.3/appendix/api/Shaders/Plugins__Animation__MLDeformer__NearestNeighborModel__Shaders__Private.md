# Shaders / Plugins/Animation/MLDeformer/NearestNeighborModel/Shaders/Private

- files: 1; lines: 228
- record kinds: function=11, parameter=5, resource=3

### `Plugins/Animation/MLDeformer/NearestNeighborModel/Shaders/Private/DataInterfaceSkeletonWithQuats.ush` (Private)

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
