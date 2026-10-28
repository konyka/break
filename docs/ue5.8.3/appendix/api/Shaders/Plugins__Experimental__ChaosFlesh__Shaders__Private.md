# Shaders / Plugins/Experimental/ChaosFlesh/Shaders/Private

- files: 1; lines: 318
- record kinds: define=1, function=21, parameter=12, resource=7

### `Plugins/Experimental/ChaosFlesh/Shaders/Private/DIFleshDeformer.ush` (Private)

- lines: 318; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Macros (#define, 1)

- L34 `#define ENABLE_DEFORMER_FLESH 1`

#### Global resources (textures / buffers / samplers) (7)

- L20 _resource_ `Buffer<float> {DataInterfaceName}_TetRestVertexBuffer;`
- L21 _resource_ `Buffer<float> {DataInterfaceName}_TetVertexBuffer;`
- L23 _resource_ `Buffer<uint> {DataInterfaceName}_VertsToParentsBuffer;`
- L24 _resource_ `Buffer<uint> {DataInterfaceName}_ParentsBuffer;`
- L25 _resource_ `Buffer<half> {DataInterfaceName}_WeightsBuffer;`
- L26 _resource_ `Buffer<half> {DataInterfaceName}_OffsetBuffer;`
- L27 _resource_ `Buffer<half> {DataInterfaceName}_MaskBuffer;`

#### Global parameters (uniforms) (12)

- L3 _parameter_ `uint {DataInterfaceName}_NumVertices;`
- L5 _parameter_ `uint {DataInterfaceName}_NumTetVertexBuffer;`
- L6 _parameter_ `uint {DataInterfaceName}_NumTetRestVertexBuffer;`
- L8 _parameter_ `uint {DataInterfaceName}_NumVertsToParentsBuffer;`
- L9 _parameter_ `int {DataInterfaceName}_VertsToParentsBufferOffset;`
- L10 _parameter_ `uint {DataInterfaceName}_VertsToParentsBufferStride;`
- L12 _parameter_ `uint {DataInterfaceName}_NumParentsBuffer;`
- L13 _parameter_ `int {DataInterfaceName}_ParentsBufferOffset;`
- L14 _parameter_ `uint {DataInterfaceName}_ParentsBufferStride;` — 1 = 8 bit, 2 = 16 bit, 4 = 32 bit
- L16 _parameter_ `uint {DataInterfaceName}_NumWeightsBuffer;`
- L17 _parameter_ `uint {DataInterfaceName}_NumOffsetBuffer;`
- L18 _parameter_ `uint {DataInterfaceName}_NumMaskBuffer;`

#### Functions (21)

- L29-32 _function_ `uint ReadNumVertices_{DataInterfaceName}(uint Index)`
- L40-52 _function_ `float3 ReadRestTetVertex_{DataInterfaceName}(int Index)`
- L54-66 _function_ `float3 ReadTetVertex_{DataInterfaceName}(int Index)`
- L73-86 _function_ `uint UnpackUInt(const Buffer<uint> Array, const uint Index, const uint Stride, const uint NumValues)` — Stride 1 = 8 bit, 2 = 16 bit, 4 = 32 bit - based off of sizeof(<index type>)
- L88-91 _function_ `int UnpackInt_32bit(const Buffer<uint> Array, const uint Index, const uint ArraySize)`
- L93-99 _function_ `int UnpackInt_16bit(const Buffer<uint> Array, const uint Index, const uint ArraySize)`
- L101-107 _function_ `int UnpackInt_8bit(const Buffer<uint> Array, const uint Index, const uint ArraySize)`
- L109-119 _function_ `int4 ReadParents32_{DataInterfaceName}(uint BufferIndex)`
- L121-131 _function_ `int4 ReadParents16_{DataInterfaceName}(uint BufferIndex)`
- L133-143 _function_ `int4 ReadParents8_{DataInterfaceName}(uint BufferIndex)`
- L145-176 _function_ `int4 ReadParents_{DataInterfaceName}(uint VertexIndex)`
- L178-192 _function_ `half4 ReadWeights_{DataInterfaceName}(uint VertexIndex)`
- L194-207 _function_ `half3 ReadOffset_{DataInterfaceName}(uint VertexIndex)`
- L209-219 _function_ `half ReadMask_{DataInterfaceName}(uint VertexIndex)`
- L227-237 _function_ `float3x3 GetTangentBasis( float3 TangentZ )` — [ Duff et al. 2017, "Building an Orthonormal Basis, Revisited" ] Discontinuity at TangentZ.z == 0
- L239-247 _function_ `float3 SafeNormalize(float3 Vec)`
- L249-265 _function_ `float3x3 GetOrthogonalBasisVectors(float3 PtA, float3 PtB, float3 PtC)`
- L268-274 _function_ `float3x3 GetRestOrthogonalBasisVectors(int4 Tet)` — assumes Tet[3] == -1
- L276-282 _function_ `float3x3 GetDynamicOrthogonalBasisVectors(int4 Tet)` — assumes Tet[3] == -1
- L284-297 _function_ `float3 GetRotatedOffsetVector(uint VertexIndex, int4 Tet)`
- L303-317 _function_ `float3 GetEmbeddedPos_{DataInterfaceName}(uint VertexIndex)`
