# Shaders / Plugins/FX/ExampleCustomDataInterface/Shaders/Private

- files: 1; lines: 21
- record kinds: function=1, parameter=1

### `Plugins/FX/ExampleCustomDataInterface/Shaders/Private/NiagaraDataInterfaceMousePosition.ush` (Private)

- lines: 21; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global parameters (uniforms) (1)

- L5 _parameter_ `float4 {ParameterName}_MousePosition;` — when using a template ush file, we need the _TPLx0ParameterNamex0TPL appendix on global functions and parameters, because the template can be included multiple times for different data interfaces in a system.

#### Functions (1)

- L7-20 _function_ `void GetMousePosition_{ParameterName}(in bool In_Normalized, out float Out_PosX, out float Out_PosY)`
