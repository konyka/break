# Shaders / Plugins/Compositing/OpenCVLensDistortion/Shaders/Private

- files: 1; lines: 98
- record kinds: cpp_binding=2, entry=2, function=2, include=2, parameter=1, resource=2

### `Plugins/Compositing/OpenCVLensDistortion/Shaders/Private/DisplacementMapGeneration.usf` (Private)

- lines: 98; parse: all-branches
- includes: L21 `/Engine/Public/Platform.ush`, L22 `/Engine/Private/Common.ush`

#### Entry points (2)

- L63-78 _entry_ `void MainVS(in uint GlobalVertexId : SV_VertexID , out float2 OutVertexDistortedViewportUV : TEXCOORD0 , out float4 OutPosition : SV_POSITION)` — stage: **vertex (from C++ binding)** — C++: `FLensDistortionDisplacementMapGenerationVS` SF_Vertex via IMPLEMENT_SHADER_TYPE (Plugins/Compositing/OpenCVLensDistortion/Source/OpenCVLensDistortion/Private/LensDistortionDisplacementMapRendering.cpp:100)
- L81-97 _entry_ `void MainPS(in noperspective float2 VertexDistortedViewportUV : TEXCOORD0 , in float4 SvPosition : SV_POSITION , out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FLensDistortionDisplacementMapGenerationPS` SF_Pixel via IMPLEMENT_SHADER_TYPE (Plugins/Compositing/OpenCVLensDistortion/Source/OpenCVLensDistortion/Private/LensDistortionDisplacementMapRendering.cpp:101)

#### Global resources (textures / buffers / samplers) (2)

- L29 _resource_ `Texture2D UndistortDisplacementMap;` — Pre computed undistort displacement map
- L32 _resource_ `SamplerState BilinearClampedSampler;` — Sampler to use with pre computed map

#### Global parameters (uniforms) (1)

- L26 _parameter_ `float2 PixelUVSize;` — Size of the pixels in the viewport UV coordinates.

#### Functions (2)

- L36-39 _function_ `float2 FlipUV(float2 UV)` — Flip UV's y component.
- L41-61 _function_ `float2 ComputeGridVertexUV(uint GlobalVertexId)`
