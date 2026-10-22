# Shaders / Plugins/Compositing/OpenColorIO/Shaders/Private

- files: 2; lines: 119
- record kinds: cpp_binding=2, define=2, entry=2, function=5, include=4, parameter=2, resource=4

### `Plugins/Compositing/OpenColorIO/Shaders/Private/OpenColorIOInvalidShader.usf` (Private)

- lines: 28; parse: all-branches
- includes: L7 `/Engine/Public/Platform.ush`, L8 `/Engine/Private/MiniFontCommon.ush`

#### Macros (#define, 1)

- L23 `#define P(x) PrintCharacter(PixelPos, OutColor.xyz, TextColor, Cursor, x);`

#### Entry points (1)

- L13-28 _entry_ `void MainPS(in noperspective float4 InUVAndScreenPos : TEXCOORD0, float4 SvPosition : SV_POSITION, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FOpenColorIOInvalidPixelShader` SF_Pixel via IMPLEMENT_SHADER_TYPE (Plugins/Compositing/OpenColorIO/Source/OpenColorIO/Private/OpenColorIOShader.cpp:30)

#### Global resources (textures / buffers / samplers) (2)

- L10 _resource_ `Texture2D InputTexture;`
- L11 _resource_ `SamplerState InputTextureSampler;`

### `Plugins/Compositing/OpenColorIO/Shaders/Private/OpenColorIOShader.usf` (Private)

- lines: 91; parse: all-branches
- includes: L7 `/Engine/Public/Platform.ush`, L24 `/Engine/Generated/OpenColorIOTransformShader.ush`

#### Macros (#define, 1)

- L10 `#define precise ` _[#if !defined(REFACTORING_ALLOWED)]_

#### Entry points (1)

- L63-91 _entry_ `void MainPS(in noperspective float4 InUVAndScreenPos : TEXCOORD0, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FOpenColorIOPixelShader` SF_Pixel via IMPLEMENT_SHADER_TYPE (Plugins/Compositing/OpenColorIO/Source/OpenColorIO/Private/OpenColorIOShader.cpp:29)

#### Global resources (textures / buffers / samplers) (2)

- L15 _resource_ `Texture2D InputTexture;` — Declaration of all variables
- L16 _resource_ `SamplerState InputTextureSampler;`

#### Global parameters (uniforms) (2)

- L17 _parameter_ `float Gamma;`
- L18 _parameter_ `uint TransformAlpha;`

#### Functions (5)

- L34-37 _function_ `float SafeRcp(float x)`
- L39-42 _function_ `float4 InvertAlpha(float4 InColor)`
- L44-47 _function_ `float4 Unpremultiply(float4 InColor)`
- L49-52 _function_ `float4 Premultiply(float4 InColor)`
- L55-58 _function_ `float3 DisplayGammaCorrection(precise float3 InColor, precise float InGamma)` — Note: For our (zero-tolerance) tests to succeed against a no-op, precise is required with the pow function.
