# Shaders / Plugins/Enterprise/GLTFExporter/Shaders/Private

- files: 1; lines: 18
- record kinds: cpp_binding=1, entry=1, include=1, resource=2

### `Plugins/Enterprise/GLTFExporter/Shaders/Private/SimpleTexture2DPS.usf` (Private)

- lines: 18; parse: all-branches
- includes: L5 `/Engine/Private/Common.ush`
- L3 #pragma `once`

#### Entry points (1)

- L10-17 _entry_ `void Main( in float2 TextureCoordinate : TEXCOORD0, out float4 OutColor : SV_Target0 )` — stage: **pixel (from C++ binding)** — C++: `FGLTFSimpleTexture2DPS` SF_Pixel via IMPLEMENT_SHADER_TYPE (Plugins/Enterprise/GLTFExporter/Source/GLTFExporter/Private/Converters/GLTFSimpleTexture2DPreview.cpp:53)

#### Global resources (textures / buffers / samplers) (2)

- L7 _resource_ `Texture2D Texture;`
- L8 _resource_ `SamplerState TextureSampler;`
