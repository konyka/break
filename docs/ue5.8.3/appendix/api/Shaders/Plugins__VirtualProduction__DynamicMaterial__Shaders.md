# Shaders / Plugins/VirtualProduction/DynamicMaterial/Shaders

- files: 1; lines: 18
- record kinds: function=1, include=1, resource=2

### `Plugins/VirtualProduction/DynamicMaterial/Shaders/DMAlphaOneMinusPS.usf` (Other)

- lines: 18; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`

#### Global resources (textures / buffers / samplers) (2)

- L5 _resource_ `Texture2D InputTexture;`
- L6 _resource_ `SamplerState InputSampler;`

#### Functions (1)

- L9-17 _function_ `void MainPS( noperspective float4 UVAndScreenPos : TEXCOORD0, out float4 OutColor : SV_Target0 )` — sv-semantics — Shader to apply 1-x to the alpha channel
