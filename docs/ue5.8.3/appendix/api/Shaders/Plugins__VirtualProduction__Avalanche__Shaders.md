# Shaders / Plugins/VirtualProduction/Avalanche/Shaders

- files: 1; lines: 25
- record kinds: function=1, include=2, parameter=2, resource=2

### `Plugins/VirtualProduction/Avalanche/Shaders/AvaRGBGammaConvert.usf` (Other)

- lines: 25; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `/Engine/Private/GammaCorrectionCommon.ush`

#### Global resources (textures / buffers / samplers) (2)

- L6 _resource_ `Texture2D InputTexture;`
- L7 _resource_ `SamplerState InputSampler;`

#### Global parameters (uniforms) (2)

- L8 _parameter_ `int SrgbToLinear;`
- L9 _parameter_ `float Gamma;`

#### Functions (1)

- L12-25 _function_ `void MainPS( noperspective float4 UVAndScreenPos : TEXCOORD0, out float4 OutColor : SV_Target0)` — sv-semantics — Shader to undo the HDR to LDR conversion done inPostProcessCombineLUTs.usf.
