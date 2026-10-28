# Shaders / Plugins/VirtualProduction/TextureShare/Shaders/Private

- files: 1; lines: 20
- record kinds: cpp_binding=1, entry=1, include=1, parameter=1, resource=2

### `Plugins/VirtualProduction/TextureShare/Shaders/Private/TextureShareScreenPixelShader.usf` (Private)

- lines: 20; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`

#### Entry points (1)

- L10-17 _entry_ `void Main( FScreenVertexOutput Input, out float4 OutColor : SV_Target0 )` — stage: **pixel (from C++ binding)** — C++: `FTextureShareScreenResamplePS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/VirtualProduction/TextureShare/Source/TextureShare/Private/Resources/TextureShareResourceUtils.cpp:146)

#### Global resources (textures / buffers / samplers) (2)

- L5 _resource_ `Texture2D InTexture;`
- L6 _resource_ `SamplerState InTextureSampler;`

#### Global parameters (uniforms) (1)

- L8 _parameter_ `float GammaModifier;`
