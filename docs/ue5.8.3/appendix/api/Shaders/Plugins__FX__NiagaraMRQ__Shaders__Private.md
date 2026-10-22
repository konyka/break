# Shaders / Plugins/FX/NiagaraMRQ/Shaders/Private

- files: 1; lines: 15
- record kinds: function=1, parameter=4

### `Plugins/FX/NiagaraMRQ/Shaders/Private/NiagaraDataInterfaceMRQ.ush` (Private)

- lines: 15; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global parameters (uniforms) (4)

- L3 _parameter_ `int {ParameterName}_Active;`
- L4 _parameter_ `int {ParameterName}_TemporalSampleCount;`
- L5 _parameter_ `int {ParameterName}_TemporalSampleIndex;`
- L6 _parameter_ `float {ParameterName}_SequenceFPS;`

#### Functions (1)

- L8-14 _function_ `void GetMRQInfo_{ParameterName}(out bool bActive, out int TemporalSampleCount, out int TemporalSampleIndex, out float SequenceFPS)`
