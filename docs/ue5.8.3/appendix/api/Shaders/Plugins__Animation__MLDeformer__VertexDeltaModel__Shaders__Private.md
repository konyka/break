# Shaders / Plugins/Animation/MLDeformer/VertexDeltaModel/Shaders/Private

- files: 2; lines: 60
- record kinds: function=7, parameter=7, resource=4

### `Plugins/Animation/MLDeformer/VertexDeltaModel/Shaders/Private/VertexDeltaModel.ush` (Private)

- lines: 19; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global resources (textures / buffers / samplers) (2)

- L5 _resource_ `Buffer<float> {DataInterfaceName}_PositionDeltaBuffer;`
- L6 _resource_ `Buffer<uint> {DataInterfaceName}_VertexMapBuffer;`

#### Global parameters (uniforms) (2)

- L3 _parameter_ `uint {DataInterfaceName}_NumVertices;`
- L4 _parameter_ `float {DataInterfaceName}_Weight;`

#### Functions (2)

- L8-11 _function_ `uint ReadNumVertices_{DataInterfaceName}()`
- L13-18 _function_ `float3 ReadPositionDelta_{DataInterfaceName}(uint VertexIndex)`

### `Plugins/Animation/MLDeformer/VertexDeltaModel/Shaders/Private/VertexDeltaModelHeatMap.ush` (Private)

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
