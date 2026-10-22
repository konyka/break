# Shaders / Plugins/VirtualProduction/CameraCalibrationCore/Shaders/Private

- files: 12; lines: 925
- record kinds: cpp_binding=14, define=8, entry=14, function=21, include=16, macro_call=1, parameter=69, resource=32

### `Plugins/VirtualProduction/CameraCalibrationCore/Shaders/Private/AnamorphicDistortion.usf` (Private)

- lines: 122; parse: all-branches
- includes: L7 `/Engine/Public/Platform.ush`, L8 `/Engine/Private/Common.ush`

#### Entry points (1)

- L109-122 _entry_ `[numthreads(8, 8, 1)] void MainCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FAnamorphicDistortionCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/VirtualProduction/CameraCalibrationCore/Source/CameraCalibrationCore/Private/AnamorphicLensDistortionModelHandler.cpp:59)

#### Global resources (textures / buffers / samplers) (1)

- L14 _resource_ `RWTexture2D<float2> OutDistortionMap;`

#### Global parameters (uniforms) (17)

- L11 _parameter_ `float2 ThreadIdToUV;` — Shared parameters
- L12 _parameter_ `float InverseOverscan;`
- L13 _parameter_ `float CameraOverscan;`
- L17 _parameter_ `float PixelAspect;` — Anamorphic distortion parameters (3DE4 Anamorphic - Standard, Degree 4 model)
- L18 _parameter_ `float2 FilmbackSize;`
- L19 _parameter_ `float2 Squeeze;`
- L20 _parameter_ `float LensRotation;`
- L21 _parameter_ `float CX02;`
- L22 _parameter_ `float CX04;`
- L23 _parameter_ `float CX22;`
- L24 _parameter_ `float CX24;`
- L25 _parameter_ `float CX44;`
- L26 _parameter_ `float CY02;`
- L27 _parameter_ `float CY04;`
- L28 _parameter_ `float CY22;`
- L29 _parameter_ `float CY24;`
- L30 _parameter_ `float CY44;`

#### Functions (4)

- L32-78 _function_ `float2 AnamorphicDistort(float2 InputUV)`
- L80-83 _function_ `float2 Distort(float2 InputUV)`
- L85-96 _function_ `bool IsDistortionWellOriented(float2 InputUV, float2 DistortedUV, float2 UVOffset)`
- L98-107 _function_ `float2 TryDistort(float2 InputUV)`

### `Plugins/VirtualProduction/CameraCalibrationCore/Shaders/Private/BlendDisplacementMaps.usf` (Private)

- lines: 128; parse: all-branches
- includes: L7 `/Engine/Public/Platform.ush`

#### Entry points (1)

- L91-127 _entry_ `[numthreads(8, 8, 1)] void MainCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FBlendDistortionDisplacementMapCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/VirtualProduction/CameraCalibrationCore/Source/CameraCalibrationCore/Private/LensDistortionSceneViewExtension.cpp:110)

#### Global resources (textures / buffers / samplers) (6)

- L19 _resource_ `Texture2D<float2> InputDistortionMap1;`
- L20 _resource_ `Texture2D<float2> InputDistortionMap2;`
- L21 _resource_ `Texture2D<float2> InputDistortionMap3;`
- L22 _resource_ `Texture2D<float2> InputDistortionMap4;`
- L24 _resource_ `SamplerState SourceTextureSampler;`
- L26 _resource_ `RWTexture2D<float2> OverscanDistortionMap;`

#### Global parameters (uniforms) (5)

- L9 _parameter_ `float2 ThreadIdToUV;`
- L10 _parameter_ `float2 FxFyScale;`
- L14 _parameter_ `float4 PatchCorners[4];` — Stores the x and y values and the x and y tangents for each corner of the blending patch Ordered (X0, Y0) -> (X1, Y0) -> (X1, Y1) -> (X0, Y1)
- L16 _parameter_ `float EvalFocus;`
- L17 _parameter_ `float EvalZoom;`

#### Functions (3)

- L28-38 _function_ `float2 BezierInterp(float2 P0, float2 P1, float2 P2, float2 P3, float Alpha)`
- L40-63 _function_ `float2 EvalAtTwoPoints(float EvalTime, float Time0, float Time1, float2 Value0, float2 Value1, float Tangent0, float Tangent1)`
- L65-89 _function_ `float2 CoonsPatchBlend(float X, float Y, float2 Values[4])`

### `Plugins/VirtualProduction/CameraCalibrationCore/Shaders/Private/BrownConradyUDDistortion.usf` (Private)

- lines: 115; parse: all-branches
- includes: L8 `/Engine/Public/Platform.ush`, L9 `/Engine/Private/Common.ush`

#### Entry points (1)

- L102-115 _entry_ `[numthreads(8, 8, 1)] void MainCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FBrownConradyUDDistortionCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/VirtualProduction/CameraCalibrationCore/Source/CameraCalibrationCore/Private/BrownConradyUDLensDistortionModelHandler.cpp:52)

#### Global resources (textures / buffers / samplers) (1)

- L15 _resource_ `RWTexture2D<float2> OutDistortionMap;`

#### Global parameters (uniforms) (14)

- L12 _parameter_ `float2 ThreadIdToUV;` — Shared parameters
- L13 _parameter_ `float InverseOverscan;`
- L14 _parameter_ `float CameraOverscan;`
- L16 _parameter_ `int bIsUD;`
- L19 _parameter_ `float2 FocalLength;` — Brown-Conrady U-D distortion parameters (polynomial division model)
- L20 _parameter_ `float2 ImageCenter;`
- L21 _parameter_ `float K1;`
- L22 _parameter_ `float K2;`
- L23 _parameter_ `float K3;`
- L24 _parameter_ `float K4;`
- L25 _parameter_ `float K5;`
- L26 _parameter_ `float K6;`
- L27 _parameter_ `float P1;`
- L28 _parameter_ `float P2;`

#### Functions (4)

- L30-71 _function_ `float2 BrownConradyUDDistort(float2 InputUV)`
- L73-76 _function_ `float2 Distort(float2 InputUV)`
- L78-89 _function_ `bool IsDistortionWellOriented(float2 InputUV, float2 DistortedUV, float2 UVOffset)`
- L91-100 _function_ `float2 TryDistort(float2 InputUV)`

### `Plugins/VirtualProduction/CameraCalibrationCore/Shaders/Private/CropDisplacementMap.usf` (Private)

- lines: 21; parse: all-branches
- includes: L7 `/Engine/Public/Platform.ush`

#### Entry points (1)

- L15-20 _entry_ `[numthreads(8, 8, 1)] void MainCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FCropDistortionDisplacementMapCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/VirtualProduction/CameraCalibrationCore/Source/CameraCalibrationCore/Private/LensDistortionSceneViewExtension.cpp:124)

#### Global resources (textures / buffers / samplers) (2)

- L9 _resource_ `Texture2D<float2> InDistortionMapWithOverscan;`
- L10 _resource_ `RWTexture2D<float2> OutDistortionMap;`

#### Global parameters (uniforms) (1)

- L13 _parameter_ `int2 OverscanOffset;` — 2D offset from the top left of the overscan displacement map

### `Plugins/VirtualProduction/CameraCalibrationCore/Shaders/Private/CrosshairOverlay.usf` (Private)

- lines: 56; parse: all-branches
- includes: L7 `/Engine/Public/Platform.ush`

#### Entry points (1)

- L34-55 _entry_ `void MainPS(float4 SvPosition : SV_POSITION, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FCrosshairOverlayPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/VirtualProduction/CameraCalibrationCore/Source/CameraCalibrationCore/Private/OverlayRendering.cpp:34)

#### Global parameters (uniforms) (5)

- L10 _parameter_ `float2 PrincipalPoint;` — Normalized image center of the lens where the crosshair will be centered
- L13 _parameter_ `uint2 OutputTextureExtent;` — Size of the output texture in (pixels)
- L16 _parameter_ `float LengthInPixels;` — Length of one side of the crosshair (in pixels)
- L19 _parameter_ `float GapSizeInPixels;` — Size of the gap in the center of the crosshair (in pixels)
- L22 _parameter_ `float4 OutputColor;` — Color to draw the crosshair

#### Functions (1)

- L24-32 _function_ `bool IsEqualCoordinate(float A, float B)`

### `Plugins/VirtualProduction/CameraCalibrationCore/Shaders/Private/DisplacementMapBlending.usf` (Private)

- lines: 131; parse: all-branches
- includes: L7 `/Engine/Private/Common.ush`

#### Entry points (1)

- L89-130 _entry_ `void BlendPS(float4 SvPosition : SV_POSITION, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FDisplacementMapBlendPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/VirtualProduction/CameraCalibrationCore/Source/CameraCalibrationCore/Private/LensFileRendering.cpp:50)

#### Global resources (textures / buffers / samplers) (5)

- L20 _resource_ `Texture2D SourceTextureOne;`
- L21 _resource_ `Texture2D SourceTextureTwo;`
- L22 _resource_ `Texture2D SourceTextureThree;`
- L23 _resource_ `Texture2D SourceTextureFour;`
- L24 _resource_ `SamplerState SourceTextureSampler;`

#### Global parameters (uniforms) (6)

- L10 _parameter_ `float EvalZoom;`
- L11 _parameter_ `float EvalFocus;`
- L15 _parameter_ `float4 PatchCorners[4];` — Stores the x and y values and the x and y tangents for each corner of the blending patch Ordered (X0, Y0) -> (X1, Y0) -> (X1, Y1) -> (X0, Y1)
- L17 _parameter_ `float2 FxFyScale;`
- L18 _parameter_ `float2 PrincipalPoint;`
- L19 _parameter_ `uint2 OutputTextureExtent;`

#### Functions (3)

- L26-36 _function_ `float4 BezierInterp(float4 P0, float4 P1, float4 P2, float4 P3, float Alpha)`
- L38-61 _function_ `float4 EvalAtTwoPoints(float EvalTime, float Time0, float Time1, float4 Value0, float4 Value1, float Tangent0, float Tangent1)`
- L63-87 _function_ `float4 CoonsPatchBlend(float X, float Y, float4 Values[4])`

### `Plugins/VirtualProduction/CameraCalibrationCore/Shaders/Private/DistortionSTMapProcessor.usf` (Private)

- lines: 97; parse: all-branches
- includes: L7 `/Engine/Public/Platform.ush`

#### Macros (#define, 8)

- L19 `#define PIXEL_ORIGIN_TOPLEFT 0`
- L20 `#define PIXEL_ORIGIN_BOTTOMLEFT 1`
- L23 `#define DISTORTION_CHANNELS_RG 0`
- L24 `#define DISTORTION_CHANNELS_BA 1`
- L25 `#define DISTORTION_CHANNELS_NONE 2`
- L28 `#define UNDISTORTION_CHANNELS_RG 0`
- L29 `#define UNDISTORTION_CHANNELS_BA 1`
- L30 `#define UNDISTORTION_CHANNELS_NONE 2`

#### Entry points (1)

- L32-96 _entry_ `[numthreads(8,8,1)] void DistortionSTMapProcessorMainCS(uint3 ThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FCalibratedMapDerivedDataCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/VirtualProduction/CameraCalibrationCore/Source/CameraCalibrationCore/Private/CalibratedMapProcessor.cpp:51)

#### Global resources (textures / buffers / samplers) (6)

- L10 _resource_ `uint2 TextureSize;`
- L11 _resource_ `Texture2D DistortionSTMap;`
- L12 _resource_ `SamplerState DistortionSTMapSampler;`
- L14 _resource_ `RWBuffer<float2> OutDistortedUV;`
- L15 _resource_ `RWTexture2D<float2> OutUndistortionDisplacementMap;`
- L16 _resource_ `RWTexture2D<float2> OutDistortionDisplacementMap;`

#### Global parameters (uniforms) (1)

- L9 _parameter_ `float2 TexelSize;`

### `Plugins/VirtualProduction/CameraCalibrationCore/Shaders/Private/FillSTDisplacementMap.usf` (Private)

- lines: 50; parse: all-branches
- includes: L7 `/Engine/Public/Platform.ush`

#### Entry points (2)

- L23-39 _entry_ `void MainVS( in uint VertexId : SV_VertexID, out noperspective float4 OutTexCoord : TEXCOORD0, out float4 OutPosition : SV_POSITION)` — stage: **vertex (from C++ binding)** — C++: `FFillSTDisplacementMapVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Plugins/VirtualProduction/CameraCalibrationCore/Source/CameraCalibrationCore/Private/LensDistortionSceneViewExtension.cpp:181)
- L41-50 _entry_ `void MainPS( in noperspective float4 InTexCoord : TEXCOORD0, in float4 SvPosition : SV_POSITION, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FFillSTDisplacementMapPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/VirtualProduction/CameraCalibrationCore/Source/CameraCalibrationCore/Private/LensDistortionSceneViewExtension.cpp:182)

#### Global resources (textures / buffers / samplers) (2)

- L15 _resource_ `Texture2D UndisplacementMap;`
- L16 _resource_ `SamplerState UndisplacementMapSampler;`

#### Global parameters (uniforms) (4)

- L9 _parameter_ `uint2 GridDimensions;`
- L11 _parameter_ `float Overscan;`
- L12 _parameter_ `float2 PixelToUV;`
- L13 _parameter_ `float2 PixelToOverscannedUV;`

#### Functions (1)

- L18-21 _function_ `float2 ToOverscannedSpace(float2 UV)`

### `Plugins/VirtualProduction/CameraCalibrationCore/Shaders/Private/InvertDisplacementMap.usf` (Private)

- lines: 54; parse: all-branches
- includes: L7 `/Engine/Public/Platform.ush`

#### Entry points (2)

- L19-41 _entry_ `void MainVS( in uint VertexId : SV_VertexID, out noperspective float4 OutTexCoord : TEXCOORD0, out float4 OutPosition : SV_POSITION)` — stage: **vertex (from C++ binding)** — C++: `FInvertDisplacementVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Plugins/VirtualProduction/CameraCalibrationCore/Source/CameraCalibrationCore/Private/LensDistortionSceneViewExtension.cpp:152)
- L44-53 _entry_ `void MainPS( in noperspective float4 InTexCoord : TEXCOORD0, in float4 SvPosition : SV_POSITION, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FInvertDisplacementPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/VirtualProduction/CameraCalibrationCore/Source/CameraCalibrationCore/Private/LensDistortionSceneViewExtension.cpp:153)

#### Global resources (textures / buffers / samplers) (2)

- L16 _resource_ `Texture2D<float2> DistortionMap;`
- L17 _resource_ `SamplerState DistortionMapSampler;`

#### Global parameters (uniforms) (4)

- L9 _parameter_ `uint2 GridDimensions;`
- L11 _parameter_ `float2 PixelToUV;`
- L12 _parameter_ `float2 PixelToOverscanUV;`
- L14 _parameter_ `float OverscanFactor;`

### `Plugins/VirtualProduction/CameraCalibrationCore/Shaders/Private/RecenterSTDisplacementMaps.usf` (Private)

- lines: 26; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `/Engine/Private/ScreenPass.ush`

#### Entry points (1)

- L20-26 _entry_ `void MainPS(noperspective float4 UVAndScreenPos : TEXCOORD0, float4 SvPosition : SV_POSITION, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FRecenterSTDisplacementMapPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/VirtualProduction/CameraCalibrationCore/Source/CameraCalibrationCore/Private/LensDistortionSceneViewExtension.cpp:200)

#### Global resources (textures / buffers / samplers) (2)

- L10 _resource_ `Texture2D<float2> STMap;`
- L11 _resource_ `SamplerState STMapSampler;`

#### Global parameters (uniforms) (2)

- L8 _parameter_ `float Overscan;`
- L9 _parameter_ `float2 STMapInvSize;`

#### Functions (1)

- L13-18 _function_ `bool ShouldCrop(float2 UV)`

#### Top-level macro invocations (1)

- L6 _macro_call_ `SCREEN_PASS_TEXTURE_VIEWPORT(Output)`

### `Plugins/VirtualProduction/CameraCalibrationCore/Shaders/Private/SphericalDistortion.usf` (Private)

- lines: 102; parse: all-branches
- includes: L7 `/Engine/Public/Platform.ush`, L8 `/Engine/Private/Common.ush`

#### Entry points (1)

- L89-102 _entry_ `[numthreads(8, 8, 1)] void MainCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FSphericalDistortionCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/VirtualProduction/CameraCalibrationCore/Source/CameraCalibrationCore/Private/SphericalLensDistortionModelHandler.cpp:48)

#### Global resources (textures / buffers / samplers) (1)

- L14 _resource_ `RWTexture2D<float2> OutDistortionMap;`

#### Global parameters (uniforms) (10)

- L11 _parameter_ `float2 ThreadIdToUV;` — Shared parameters
- L12 _parameter_ `float InverseOverscan;`
- L13 _parameter_ `float CameraOverscan;`
- L17 _parameter_ `float2 FocalLength;` — Spherical distortion parameters (Brown-Conrady model)
- L18 _parameter_ `float2 ImageCenter;`
- L19 _parameter_ `float K1;`
- L20 _parameter_ `float K2;`
- L21 _parameter_ `float K3;`
- L22 _parameter_ `float P1;`
- L23 _parameter_ `float P2;`

#### Functions (4)

- L25-58 _function_ `float2 SphericalDistort(float2 InputUV)`
- L60-63 _function_ `float2 Distort(float2 InputUV)`
- L65-76 _function_ `bool IsDistortionWellOriented(float2 InputUV, float2 DistortedUV, float2 UVOffset)`
- L78-87 _function_ `float2 TryDistort(float2 InputUV)`

### `Plugins/VirtualProduction/CameraCalibrationCore/Shaders/Private/UndistortImagePoints.usf` (Private)

- lines: 23; parse: all-branches
- includes: L7 `/Engine/Public/Platform.ush`

#### Entry points (1)

- L15-22 _entry_ `[numthreads(1,1,1)] void UndistortImagePointsCS(int3 Index : SV_GroupID)` — stage: **compute** — C++: `FUndistortImagePointsCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/VirtualProduction/CameraCalibrationCore/Source/CameraCalibrationCore/Private/DistortionRenderingUtils.cpp:40)

#### Global resources (textures / buffers / samplers) (4)

- L9 _resource_ `Texture2D DistortionMap;`
- L10 _resource_ `SamplerState DistortionMapSampler;`
- L12 _resource_ `StructuredBuffer<float2> InputPoints;`
- L13 _resource_ `RWBuffer<float2> UndistortedPoints;`
