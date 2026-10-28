# Shaders / Plugins/VirtualProduction/DMX/DMXPixelMapping/Shaders/Private

- files: 2; lines: 166
- record kinds: cpp_binding=4, define=5, entry=2, function=1, include=3, member=5, parameter=6, resource=2, struct=3

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Shaders/Private/DMXPixelMapping.usf` (Private)

- lines: 104; parse: all-branches
- includes: L3 `DMXPixelMapping.ush`

#### Macros (#define, 5)

- L26 `#define PIXELBLENDING_QUALITY_LOW 0`
- L27 `#define PIXELBLENDING_QUALITY_MEDIUM 1`
- L28 `#define PIXELBLENDING_QUALITY_HIGH 2`
- L55 `#define NUM_CELLS 4` _[#if PIXELBLENDING_QUALITY == PIXELBLENDING_QUALITY_MEDIUM]_
- L74 `#define NUM_CELLS 8` _[#if !(PIXELBLENDING_QUALITY == PIXELBLENDING_QUALITY_MEDIUM) && PIXELBLENDING_QUALITY == PIXELBLENDING_QUALITY_HIGH]_

#### Entry points (2)

- L13-21 _entry_ `OutputVS DMXPixelMappingVS(InputVS IN)` — stage: **vertex (from C++ binding)** — C++: `FDMXPixelMappingRendererVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingRenderer/Private/DMXPixelMappingRenderPixelMapProxy.cpp:69) — C++: `FDEPRECATED_DMXPixelMappingRendererVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingRenderer/Private/DMXPixelMappingRenderer.cpp:102)
- L34-103 _entry_ `OutputPS DMXPixelMappingPS(OutputVS IN)` — stage: **pixel (from C++ binding)** — C++: `FDMXPixelMappingRendererPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingRenderer/Private/DMXPixelMappingRenderPixelMapProxy.cpp:70) — C++: `FDEPRECATED_DMXPixelMappingRendererPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/VirtualProduction/DMX/DMXPixelMapping/Source/DMXPixelMappingRenderer/Private/DMXPixelMappingRenderer.cpp:103)

### `Plugins/VirtualProduction/DMX/DMXPixelMapping/Shaders/Private/DMXPixelMapping.ush` (Private)

- lines: 62; parse: all-branches
- includes: L7 `/Engine/Public/Platform.ush`, L8 `/Engine/Private/Common.ush`

#### Structs / classes (3)

- L24-28 _struct_ **`InputVS`** `struct InputVS`
  - L26 _member_ `float4 Position : ATTRIBUTE0;`
  - L27 _member_ `float2 UV : ATTRIBUTE1;`
- L30-34 _struct_ **`OutputVS`** `struct OutputVS`
  - L32 _member_ `float4 Position : SV_Position;`
  - L33 _member_ `float4 UV : TEXCOORD0;`
- L36-39 _struct_ **`OutputPS`** `struct OutputPS`
  - L38 _member_ `float4 Color : SV_Target0;`

#### Global resources (textures / buffers / samplers) (2)

- L16 _resource_ `Texture2D InputTexture;` — PS Textures Parameters
- L17 _resource_ `SamplerState InputSampler;`

#### Global parameters (uniforms) (6)

- L11 _parameter_ `float4 DrawRectanglePosScaleBias;` — VS Parameters
- L12 _parameter_ `float4 DrawRectangleInvTargetSizeAndTextureSize;`
- L13 _parameter_ `float4 DrawRectangleUVScaleBias;`
- L20 _parameter_ `float Brightness;` — PS Parameters
- L21 _parameter_ `float2 UVTopLeftRotated;`
- L22 _parameter_ `float2 UVTopRightRotated;`

#### Functions (1)

- L50-62 _function_ `void DrawRectangleForPixelMapping(in float4 InPosition, in float2 InTexCoord, out float4 OutPosition, out float2 OutTexCoord)` — Used for calculating vertex positions and UVs when drawing with DrawRectangleForPixelMapping
