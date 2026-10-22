# Shaders / Plugins/Compositing/LensDistortion/Shaders/Private

- files: 1; lines: 138
- record kinds: cpp_binding=2, entry=2, function=3, include=1, parameter=6

### `Plugins/Compositing/LensDistortion/Shaders/Private/UVGeneration.usf` (Private)

- lines: 138; parse: all-branches
- includes: L20 `/Engine/Public/Platform.ush`

#### Entry points (2)

- L83-116 _entry_ `void MainVS( in uint GlobalVertexId : SV_VertexID, out float2 OutVertexDistortedViewportUV : TEXCOORD0, out float4 OutPosition : SV_POSITION )` — stage: **vertex (from C++ binding)** — C++: `FLensDistortionUVGenerationVS` SF_Vertex via IMPLEMENT_SHADER_TYPE (Plugins/Compositing/LensDistortion/Source/LensDistortion/Private/LensDistortionRendering.cpp:153)
- L119-137 _entry_ `void MainPS( in noperspective float2 VertexDistortedViewportUV : TEXCOORD0, in float4 SvPosition : SV_POSITION, out float4 OutColor : SV_Target0 )` — stage: **pixel (from C++ binding)** — C++: `FLensDistortionUVGenerationPS` SF_Pixel via IMPLEMENT_SHADER_TYPE (Plugins/Compositing/LensDistortion/Source/LensDistortion/Private/LensDistortionRendering.cpp:154)

#### Global parameters (uniforms) (6)

- L24 _parameter_ `float2 PixelUVSize;` — Size of the pixels in the viewport UV coordinates.
- L27 _parameter_ `float3 RadialDistortionCoefs;` — K1, K2, K3
- L30 _parameter_ `float2 TangentialDistortionCoefs;` — P1, P2
- L33 _parameter_ `float4 UndistortedCameraMatrix;` — Camera matrix of the undistorted viewport.
- L36 _parameter_ `float4 DistortedCameraMatrix;` — Camera matrix of the distorted viewport.
- L39 _parameter_ `float2 OutputMultiplyAndAdd;` — Output multiply and add to the render target.

#### Functions (3)

- L43-56 _function_ `float2 UndistortNormalizedViewPosition(float2 V)` — Undistort a view position at V.z=1.
- L63-73 _function_ `float2 UndistortViewportUV(float2 ViewportUV)` — Returns the undistorted viewport UV of the distorted's viewport UV. Notes: UVs are bottom left originated.
- L77-80 _function_ `float2 FlipUV(float2 UV)` — Flip UV's y component.
