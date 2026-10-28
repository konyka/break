# Shaders / Plugins/Runtime/WarpUtils/Shaders/Private

- files: 1; lines: 44
- record kinds: function=2, include=1, member=5, parameter=1, struct=3

### `Plugins/Runtime/WarpUtils/Shaders/Private/PFMExporterShaders.usf` (Private)

- lines: 44; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`

#### Structs / classes (3)

- L8-12 _struct_ **`InputVS`** `struct InputVS`
  - L10 _member_ `float4 Position : ATTRIBUTE0;`
  - L11 _member_ `float2 UV : ATTRIBUTE1;`
- L13-17 _struct_ **`OutputVS`** `struct OutputVS`
  - L15 _member_ `float4 Position : SV_POSITION;`
  - L16 _member_ `float3 PFMPosition : NORMAL;`
- L18-21 _struct_ **`OutputPS`** `struct OutputPS`
  - L20 _member_ `float4 PFMPosition : SV_Target0;`

#### Global parameters (uniforms) (1)

- L6 _parameter_ `float4x4 MeshToPFMMatrix;`

#### Functions (2)

- L23-36 _function_ `OutputVS PFMExporterUV_VS(InputVS IN)`
- L38-43 _function_ `OutputPS PFMExporterPassthrough_PS(OutputVS IN)`
