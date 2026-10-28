# Shaders / Plugins/TextureGraph/Shaders/Mask/Blend

- files: 2; lines: 47
- record kinds: cpp_binding=2, entry=2, include=4, parameter=5, resource=5

### `Plugins/TextureGraph/Shaders/Mask/Blend/MaskBlend_Multiply.usf` (Other)

- lines: 21; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L3 `/Plugin/TextureGraph/SamplerStates.ush`

#### Entry points (1)

- L13-21 _entry_ `float4 FSH_MaskBlend_Multiply(in float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_MaskBlend_Multiply` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Mask/T_MaskBlend_Multiply.cpp:6)

#### Global resources (textures / buffers / samplers) (2)

- L6 _resource_ `Texture2D Mask0;`
- L9 _resource_ `Texture2D Mask1;`

#### Global parameters (uniforms) (2)

- L5 _parameter_ `float MaskFactor0;`
- L8 _parameter_ `float MaskFactor1;`

### `Plugins/TextureGraph/Shaders/Mask/Blend/NormalBlendWithHeightMask.usf` (Other)

- lines: 26; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L3 `/Plugin/TextureGraph/SamplerStates.ush`

#### Entry points (1)

- L12-25 _entry_ `float4 FSH_NormalBlend(in float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_NormalBlendWithHeightMask` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Layer/T_BlendWithHeightMask.cpp:11)

#### Global resources (textures / buffers / samplers) (3)

- L5 _resource_ `Texture2D DestinationTexture;`
- L6 _resource_ `Texture2D SourceTexture;`
- L7 _resource_ `Texture2D Mask;`

#### Global parameters (uniforms) (3)

- L8 _parameter_ `float Opacity;`
- L9 _parameter_ `float LerpRGB;` — 0 or 1 depending on whether we want the RGB lerp
- L10 _parameter_ `float LerpAlpha;` — 0 or 1 depending on whether we want the RGB lerp
