# Shaders / Plugins/Runtime/nDisplay/Shaders/Private

- files: 18; lines: 2187
- record kinds: cpp_binding=18, define=25, entry=18, function=63, include=33, macro_call=5, member=30, parameter=47, resource=59, static_const=3, struct=13

### `Plugins/Runtime/nDisplay/Shaders/Private/DisplayClusterColorCorrection.ush` (Private)

- lines: 43; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`, L4 `/Engine/Private/GammaCorrectionCommon.ush`

#### Macros (#define, 1)

- L9 `#define precise ` _[#if !defined(REFACTORING_ALLOWED)]_

#### Functions (6)

- L14-17 _function_ `float3 DisplayGammaCorrection(precise float3 InColor, precise float InGamma)` — This function copied from the '\\Engine\Plugins\Compositing\OpenColorIO\Shaders\Private\OpenColorIOShader.usf' Note: For our (zero-tolerance) tests to succeed against a no-op, precise is required with the pow function.
- L19-22 _function_ `float SafeRcp(float x)`
- L24-27 _function_ `float4 Unpremultiply(float4 InColor)`
- L29-32 _function_ `float4 Premultiply(float4 InColor)`
- L34-37 _function_ `float4 InvertedUnpremultiply(float4 InColor)`
- L39-42 _function_ `float4 InvertedPremultiply(float4 InColor)`

### `Plugins/Runtime/nDisplay/Shaders/Private/FrameStats.usf` (Private)

- lines: 99; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`, L4 `/Engine/Private/MiniFontCommon.ush`

#### Entry points (2)

- L52-80 _entry_ `void MainPS(in noperspective float4 InUVAndScreenPos : TEXCOORD0, float4 SvPosition : SV_POSITION, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FDisplayClusterFrameStatsShader` SF_Pixel via IMPLEMENT_SHADER_TYPE (Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/DisplayClusterViewportFrameStatsViewExtension.cpp:45)
- L87-98 _entry_ `void MainOutputPS(in noperspective float4 InUVAndScreenPos : TEXCOORD0, float4 SvPosition : SV_POSITION, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FDisplayClusterFrameStatsOutputShader` SF_Pixel via IMPLEMENT_SHADER_TYPE (Plugins/Runtime/nDisplay/Source/DisplayCluster/Private/Render/Viewport/DisplayClusterViewportFrameStatsViewExtension.cpp:65)

#### Global resources (textures / buffers / samplers) (4)

- L82 _resource_ `Texture2D InputTexture;`
- L83 _resource_ `SamplerState InputTextureSampler;`
- L84 _resource_ `Texture2D FrameStatsTexture;`
- L85 _resource_ `SamplerState FrameStatsTextureSampler;`

#### Global parameters (uniforms) (2)

- L6 _parameter_ `uint FrameCount;`
- L7 _parameter_ `uint Timecode;`

#### static const (2)

- L8 _static_const_ `static const uint Semicolon = 58;`
- L9 _static_const_ `static const float4 FontColor = float4(0.1f, 0.9f, 0.1f, 0.0f);`

#### Functions (3)

- L12-28 _function_ `void PrintCharacterA(int2 PixelPos, inout float4 OutColor, float4 FontColor, inout int2 LeftTop, int CharacterID)` — Function taken from MiniFontCommon.ush, but with alpha support
- L30-36 _function_ `void PrintTwoDigitUintA(int2 PixelPos, inout float4 OutColor, float4 FontColor, inout int2 Cursor, uint Number)`
- L38-50 _function_ `void PrintLargeUintA(int2 PixelPos, inout float4 OutColor, float4 FontColor, inout int2 Cursor, uint Number)`

### `Plugins/Runtime/nDisplay/Shaders/Private/MPCDIOverlayShaders.usf` (Private)

- lines: 460; parse: all-branches
- includes: L2 `MPCDIUtils.ush`

#### static const (1)

- L4 _static_const_ `static const float DefaultChromakeyTileMultiplier = 10.0;`

#### Functions (19)

- L6-22 _function_ `OutputVS IcvfxWarpVS(InputVS IN)`
- L24-33 _function_ `OutputPS Passthrough_PS(OutputVS IN)`
- L35-38 _function_ `float3 ComposeOverlayColor(float4 InColor, float4 InOverlayColor)`
- L41-46 _function_ `float4 GetFinalLightcardColor(float4 InColor)` — Apply final gamma for LightCard color.
- L51-54 _function_ `float4 ComposeRenderPassTwoOverlays(float4 InOverlay1, float4 InOverlay2)` — Additive render pass with 2 overlays a = in\out, b,c = ordered overlays (a + b + c) c.xyz + (b.xyz + a.xyz * b.w)*c.w = a.xyz * (b.w *c.w) + b.xyz*c.w + c.xyz
- L59-62 _function_ `float4 GetLightCardUnderTextureColor(float2 InUV)` — LightCard
- L64-67 _function_ `float4 GetLightCardOverTextureColor(float2 InUV)`
- L69-84 _function_ `float4 GetUVLightCardUnderTextureColor(float2 InUV)`
- L86-101 _function_ `float4 GetUVLightCardOverTextureColor(float2 InUV)`
- L104-120 _function_ `float4 GetLightCardUnderColor(OutputVS IN, float2 OverlayUV)` — This function expects that (LightCardMode & (LIGHTCARD_UNDER \| UVLIGHTCARD_UNDER)) != 0
- L124-140 _function_ `float4 GetLightCardOverColor(OutputVS IN, float2 OverlayUV)` — This function expects that (LightCardMode & (LIGHTCARD_OVER \| UVLIGHTCARD_OVER)) != 0
- L142-155 _function_ `float3 ComposeLightCardUnderColor(float4 InColor, OutputVS IN, float2 OverlayUV)`
- L157-170 _function_ `float3 ComposeLightCardOverColor(float4 InColor, OutputVS IN, float2 OverlayUV)`
- L173-176 _function_ `float2 TileUV(float2 InUV, float InScale)`
- L178-195 _function_ `float GetFeatherAlpha(float2 EdgeOffset, float Feather)`
- L197-231 _function_ `float GetInnerCameraSoftEdgeAlpha(float2 CameraUV, float4 InInnerCameraSoftEdge)`
- L233-257 _function_ `float4 GetChromakeyMarkerColor(float2 InMarkersUV)`
- L259-387 _function_ `float4 GetInnerCameraColor(float4 WarpedUV, OutputVS IN)`
- L389-459 _function_ `OutputPS IcvfxWarpPS(OutputVS IN)`

### `Plugins/Runtime/nDisplay/Shaders/Private/MPCDIShaders.usf` (Private)

- lines: 60; parse: all-branches
- includes: L2 `MPCDIUtils.ush`

#### Functions (3)

- L4-20 _function_ `OutputVS WarpVS(InputVS IN)`
- L22-31 _function_ `OutputPS Passthrough_PS(OutputVS IN)`
- L33-59 _function_ `OutputPS WarpPS(OutputVS IN)`

### `Plugins/Runtime/nDisplay/Shaders/Private/MPCDIUtils.ush` (Private)

- lines: 248; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`, L4 `DisplayClusterColorCorrection.ush`

#### Macros (#define, 8)

- L61 `#define ENABLE_INNER_CAMERA_OVERLAP 1` _[#if defined(MAX_INNER_CAMERAS_AMOUNT)]_
- L67 `#define ENABLE_INNER_CAMERA_OVERLAP 0` _[#if !(defined(MAX_INNER_CAMERAS_AMOUNT))]_
- L75 `#define LIGHTCARD_UNDER (1 << 0)`
- L78 `#define LIGHTCARD_OVER (1 << 1)`
- L81 `#define UVLIGHTCARD_UNDER (1 << 2)`
- L84 `#define UVLIGHTCARD_OVER (1 << 3)`
- L90 `#define UVLIGHTCARD_MERGE (1 << 4)`
- L97 `#define SCENE_ALPHA_OPAQUE 0.0f`

#### Structs / classes (3)

- L115-122 _struct_ **`InputVS`** `struct InputVS`
  - L117 _member_ `float4 Position : ATTRIBUTE0;`
  - L118 _member_ `float2 UV : ATTRIBUTE1;`
  - L120 _member_ `float2 UV_Chromakey : ATTRIBUTE2;` _[#if MESH_WARP]_
- L124-132 _struct_ **`OutputVS`** `struct OutputVS`
  - L126 _member_ `float4 Position : SV_POSITION;`
  - L127 _member_ `float4 UV : TEXCOORD0;`
  - L129 _member_ `float4 UV_Chromakey : TEXCOORD1;` _[#if MESH_WARP]_
  - L130 _member_ `float3 PFMPosition : NORMAL;` _[#if MESH_WARP]_
- L134-137 _struct_ **`OutputPS`** `struct OutputPS`
  - L136 _member_ `float4 Color : SV_Target0;`

#### Global resources (textures / buffers / samplers) (22)

- L12 _resource_ `Texture2D InputTexture;` — PS parameters
- L13 _resource_ `Texture2D WarpMapTexture;`
- L16 _resource_ `Texture2D AlphaMapTexture;` — AlphaMap and BetaMap textures.
- L17 _resource_ `Texture2D BetaMapTexture;`
- L29 _resource_ `Texture2D InnerCameraTexture;`
- L30 _resource_ `Texture2D ChromakeyCameraTexture;`
- L31 _resource_ `Texture2D ChromakeyMarkerTexture;`
- L33 _resource_ `Texture2D LightCardUnderTexture;`
- L34 _resource_ `Texture2D LightCardOverTexture;`
- L35 _resource_ `Texture2D UVLightCardUnderTexture;`
- L36 _resource_ `Texture2D UVLightCardOverTexture;`
- L38 _resource_ `SamplerState InputSampler;`
- L39 _resource_ `SamplerState WarpMapSampler;`
- L40 _resource_ `SamplerState AlphaMapSampler;`
- L41 _resource_ `SamplerState BetaMapSampler;`
- L43 _resource_ `SamplerState InnerCameraSampler;`
- L44 _resource_ `SamplerState ChromakeyCameraSampler;`
- L45 _resource_ `SamplerState ChromakeyMarkerSampler;`
- L47 _resource_ `SamplerState LightCardUnderSampler;`
- L48 _resource_ `SamplerState LightCardOverSampler;`
- L49 _resource_ `SamplerState UVLightCardUnderSampler;`
- L50 _resource_ `SamplerState UVLightCardOverSampler;`

#### Global parameters (uniforms) (24)

- L7 _parameter_ `float4 DrawRectanglePosScaleBias;` — VS Parameters
- L8 _parameter_ `float4 DrawRectangleInvTargetSizeAndTextureSize;`
- L9 _parameter_ `float4 DrawRectangleUVScaleBias;`
- L20 _parameter_ `int AlphaMapComponentDepth;` — Indicates the number of components within the alpha or beta map. Valid values are 1 or 3.
- L21 _parameter_ `int BetaMapComponentDepth;`
- L27 _parameter_ `float AlphaMapGammaEmbedded;` — This parameter contains the 'gammaEmbedded' tag value, which is the gamma value for the AlphaMap texture. Note: The MPCDI 2.0 standard does not define an 'EmbeddedGamma' tag value for the BetaMap tag. However, it does require gamma correction for BetaMap. Therefore, this parameter is also used for the BetaMap texture.
- L52 _parameter_ `float4x4 MeshToStageProjectionMatrix;`
- L53 _parameter_ `float4x4 ViewportTextureProjectionMatrix;`
- L54 _parameter_ `float4x4 OverlayProjectionMatrix;`
- L55 _parameter_ `float4x4 InnerCameraProjectionMatrix;`
- L58 _parameter_ `int OverlappedInnerCamerasNum;` — The total number of InCameras, which are rendered below.
- L64 _parameter_ `float4x4 OverlappedInnerCamerasProjectionMatrices[MAX_INNER_CAMERAS_AMOUNT];` — Matrices and SoftEdges for InCameras, which are rendered below. _[#if defined(MAX_INNER_CAMERAS_AMOUNT)]_
- L65 _parameter_ `float4 OverlappedInnerCameraSoftEdges[MAX_INNER_CAMERAS_AMOUNT];` _[#if defined(MAX_INNER_CAMERAS_AMOUNT)]_
- L70 _parameter_ `float LightCardGamma;`
- L100 _parameter_ `int LightCardMode;` — Several flags in this parameter: LIGHTCARD_UNDER, LIGHTCARD_OVER, UVLIGHTCARD_UNDER, UVLIGHTCARD_OVER, UVLIGHTCARD_MERGE
- L102 _parameter_ `float4 InnerCameraSoftEdge;`
- L104 _parameter_ `float4 InnerCameraBorderColor;`
- L105 _parameter_ `float InnerCameraBorderThickness;`
- L106 _parameter_ `float InnerCameraFrameAspectRatio;`
- L108 _parameter_ `float4 ChromakeyColor;`
- L109 _parameter_ `float4 ChromakeyMarkerColor;`
- L111 _parameter_ `float ChromakeyMarkerScale;`
- L112 _parameter_ `float ChromakeyMarkerDistance;`
- L113 _parameter_ `float2 ChromakeyMarkerOffset;`

#### Functions (7)

- L139-142 _function_ `float Pow2(float X)`
- L144-150 _function_ `float MPCDI_sRGBToLinear(float srgb)`
- L152-158 _function_ `float MPCDI_LinarTosRGB(float lin)`
- L160-165 _function_ `float3 MPCDI_sRGBToLinear(float3 srgb)`
- L167-172 _function_ `float3 MPCDI_LinearTosRGB(float3 lin)`
- L175-181 _function_ `void DrawRectangle(in float4 InPosition, in float2 InTexCoord, out float4 OutPosition, out float2 OutTexCoord)` — Used for calculating vertex positions and UVs when drawing with DrawRectangle
- L184-247 _function_ `float4 ApplyBlending(float3 InColor_sRGB, OutputVS IN, float ColorAlphaValue)`

### `Plugins/Runtime/nDisplay/Shaders/Private/MediaShaders.usf` (Private)

- lines: 29; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `/Engine/Private/GammaCorrectionCommon.ush`

#### Global resources (textures / buffers / samplers) (2)

- L6 _resource_ `Texture2D InputTexture;`
- L7 _resource_ `SamplerState InputSampler;`

#### Functions (2)

- L11-18 _function_ `float4 LinearToPQ_PS(float2 uv : TEXCOORD) : SV_Target` — sv-semantics — Pixel shader for Linear-PQ conversion
- L22-28 _function_ `float4 PQToLinear_PS(float2 uv : TEXCOORD) : SV_Target` — sv-semantics — Pixel shader for PQ-Linear conversion

### `Plugins/Runtime/nDisplay/Shaders/Private/MeshProjectionHitProxy.usf` (Private)

- lines: 18; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `/Engine/Generated/Material.ush`, L5 `/Engine/Generated/VertexFactory.ush`

#### Entry points (1)

- L9-18 _entry_ `void Main(FVertexFactoryInterpolantsVSToPS FactoryInterpolants, in INPUT_POSITION_QUALIFIERS float4 SvPosition : SV_Position OPTIONAL_IsFrontFace, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FMeshProjectionHitProxyPS` SF_Pixel via IMPLEMENT_MATERIAL_SHADER_TYPE (Plugins/Runtime/nDisplay/Source/DisplayClusterLightCardEditorShaders/Private/DisplayClusterMeshProjectionRenderer.cpp:480)

#### Global parameters (uniforms) (1)

- L7 _parameter_ `float4 HitProxyId;`

### `Plugins/Runtime/nDisplay/Shaders/Private/MeshProjectionNormalSmoothing.usf` (Private)

- lines: 300; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `/Engine/Private/ScreenPass.ush`

#### Macros (#define, 1)

- L23 `#define FILTER_KERNEL_SIZE 25`

#### Entry points (5)

- L82-124 _entry_ `[numthreads(8, 8, 1)] void CreateRWTexturesCS(uint2 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FMeshProjectionNormalsCreateRWTexturesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/nDisplay/Source/DisplayClusterLightCardEditorShaders/Private/DisplayClusterMeshProjectionRenderer.cpp:572) — A compute pass that copies the scene's color, depth, and stencil buffers into RW textures, as well as converting all normals from world space to radial space
- L127-174 _entry_ `[numthreads(8, 8, 1)] void DepthDilationCS(uint2 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FMeshProjectionNormalsDepthDilationCS` SF_Compute via IMPLEMENT_SHADER_TYPE (Plugins/Runtime/nDisplay/Source/DisplayClusterLightCardEditorShaders/Private/DisplayClusterMeshProjectionRenderer.cpp:635) — A compute pass that dilates the depth buffer of overlapping geometry, allowing nearer geometry depth to dilate into further geometry depth
- L177-241 _entry_ `[numthreads(8, 8, 1)] void DilationCS(uint2 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FMeshProjectionNormalsDilationCS` SF_Compute via IMPLEMENT_SHADER_TYPE (Plugins/Runtime/nDisplay/Source/DisplayClusterLightCardEditorShaders/Private/DisplayClusterMeshProjectionRenderer.cpp:636) — A compute pass that dilates the normal, depth, and stencil buffer of geometry into empty space
- L244-287 _entry_ `[numthreads(8, 8, 1)] void BlurCS(uint2 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FMeshProjectionNormalsBlurCS` SF_Compute via IMPLEMENT_SHADER_TYPE (Plugins/Runtime/nDisplay/Source/DisplayClusterLightCardEditorShaders/Private/DisplayClusterMeshProjectionRenderer.cpp:637) — A compute pass that performs a standard Gaussian blur of the normal and depth buffers. Uses a different spatial deviation for blurring empty space or geometry
- L290-300 _entry_ `void OutputNormalMapPS(noperspective float4 UVAndScreenPos : TEXCOORD0, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FMeshProjectionNormalsOutputPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/nDisplay/Source/DisplayClusterLightCardEditorShaders/Private/DisplayClusterMeshProjectionRenderer.cpp:664) — A pixel shader that renders the results of any compute shader passes to an output render target, packing the normal and depth values into the correct RGBA channels

#### Global resources (textures / buffers / samplers) (11)

- L8 _resource_ `Texture2D SceneColor;`
- L9 _resource_ `Texture2D SceneDepth;`
- L10 _resource_ `Texture2D<uint2> SceneStencil;`
- L12 _resource_ `RWTexture2D<float4> RWColorIn;`
- L13 _resource_ `RWTexture2D<float4> RWColorOut;`
- L14 _resource_ `RWTexture2D<float> RWDepthIn;`
- L15 _resource_ `RWTexture2D<float> RWDepthOut;`
- L16 _resource_ `RWTexture2D<uint> RWStencilIn;`
- L17 _resource_ `RWTexture2D<uint> RWStencilOut;`
- L18 _resource_ `RWTexture2D<uint> RWBlurStencilIn;`
- L19 _resource_ `RWTexture2D<uint> RWBlurStencilOut;`

#### Global parameters (uniforms) (5)

- L21 _parameter_ `float4x4 NormalCorrectionMatrix;`
- L28 _parameter_ `float2 SampleDirection;`
- L29 _parameter_ `float2 SampleOffsetScale;`
- L30 _parameter_ `float InvSigma;`
- L33 _parameter_ `uint bCopyToBlurStencil;` — Determines if the contents of the geometry stencil buffer should be copied to the blur stencil buffer during the dilation pass

#### Functions (5)

- L36-42 _function_ `bool ClipToAzimuthalBounds(uint2 PixelPos)` — Returns true if the current pixel is beyond the circular azimuthal bounds and should be clipped
- L45-54 _function_ `uint2 AdjustPixelPos(uint2 PixelPos, int2 PixelOffset)` — Applies an offset to the specified pixel position, ensuring that the resulting offset position is within the azimuthal bounds
- L57-60 _function_ `float3 NormalToColorSpace(float3 Normal)` — Converts a vector in normal space to color space
- L63-66 _function_ `float3 NormalFromColorSpace(float3 Color)` — Converts a color from color space to normal space
- L70-79 _function_ `float3 TransformToRadialBasis(float3 Vector, float3 RadialVector)` — Transforms the specified world vector into the radial space of the specified vector, oriented so that the x axis points in the direction of the radial vector

#### Top-level macro invocations (3)

- L6 _macro_call_ `SCREEN_PASS_TEXTURE_VIEWPORT(Input)`
- L25 _macro_call_ `DECLARE_SCALAR_ARRAY(float, SpatialKernel, FILTER_KERNEL_SIZE)`
- L26 _macro_call_ `DECLARE_SCALAR_ARRAY(float, InteriorSpatialKernel, FILTER_KERNEL_SIZE)`

### `Plugins/Runtime/nDisplay/Shaders/Private/MeshProjectionSelectionOutline.usf` (Private)

- lines: 222; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `/Engine/Private/ScreenPass.ush`

#### Entry points (1)

- L167-221 _entry_ `void Main( noperspective float4 UVAndScreenPos : TEXCOORD0, float4 SvPosition : SV_POSITION, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FMeshProjectionSelectionOutlinePS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/nDisplay/Source/DisplayClusterLightCardEditorShaders/Private/DisplayClusterMeshProjectionRenderer.cpp:697)

#### Structs / classes (1)

- L22-32 _struct_ **`FPixelInfo`** `struct FPixelInfo`
  - L25 _member_ `bool bObjectMask;` — if there is an selected object
  - L27 _member_ `int ObjectId;`
  - L29 _member_ `float fVisible;` — if the current pixel is not occluded by some other object in front of it
  - L31 _member_ `bool bVisible;` — hard version of fVisible

#### Global resources (textures / buffers / samplers) (6)

- L7 _resource_ `Texture2D EditorPrimitivesDepth;` — Note: opengl compiler doesn't like Texture2D<float>
- L8 _resource_ `Texture2D<uint2> EditorPrimitivesStencil;`
- L10 _resource_ `Texture2D ColorTexture;`
- L11 _resource_ `SamplerState ColorSampler;`
- L13 _resource_ `Texture2D DepthTexture;`
- L14 _resource_ `SamplerState DepthSampler;`

#### Global parameters (uniforms) (2)

- L19 _parameter_ `float3 OutlineColor;`
- L20 _parameter_ `float SelectionHighlightIntensity;`

#### Functions (4)

- L35-38 _function_ `float ReconstructDeviceZ(float3 DeviceZPlane, float2 PixelOffset)` — @param DeviceZPlane plane in screenspace .x: ddx(DeviceZ), y: ddy(DeviceZ) z:DeviceZ
- L41-80 _function_ `FPixelInfo GetPixelInfo(int2 PixelPos, int OffsetX, int OffsetY, float3 DeviceZPlane, float2 DeviceZMinMax)` — @param DeviceZPlane plane in screenspace .x: ddx(DeviceZ), y: ddy(DeviceZ) z:DeviceZ
- L83-87 _function_ `void MinMax(inout int2 Var, int Value)` — Computes min and max at once.
- L89-165 _function_ `float4 GetOutline(int2 PixelPos, FPixelInfo CenterPixelInfo, float3 DeviceZPlane, float2 DeviceZMinMax)`

#### Top-level macro invocations (2)

- L16 _macro_call_ `SCREEN_PASS_TEXTURE_VIEWPORT(Color)`
- L17 _macro_call_ `SCREEN_PASS_TEXTURE_VIEWPORT(Depth)`

### `Plugins/Runtime/nDisplay/Shaders/Private/MeshProjectionShaders.usf` (Private)

- lines: 161; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `/Engine/Generated/Material.ush`, L5 `/Engine/Generated/VertexFactory.ush`, L7 `SubstrateUtils.ush`

#### Entry points (5)

- L18-49 _entry_ `void AzimuthalVS(FVertexFactoryInput Input, out FMeshProjectionVSToPS Output)` — stage: **vertex (from C++ binding)** — C++: `FMeshAzimuthalProjectionVS` SF_Vertex via IMPLEMENT_MATERIAL_SHADER_TYPE (Plugins/Runtime/nDisplay/Source/DisplayClusterLightCardEditorShaders/Private/DisplayClusterMeshProjectionRenderer.cpp:259)
- L51-66 _entry_ `void PerspectiveVS(FVertexFactoryInput Input, out FMeshProjectionVSToPS Output)` — stage: **vertex (from C++ binding)** — C++: `FMeshPerspectiveProjectionVS` SF_Vertex via IMPLEMENT_MATERIAL_SHADER_TYPE (Plugins/Runtime/nDisplay/Source/DisplayClusterLightCardEditorShaders/Private/DisplayClusterMeshProjectionRenderer.cpp:258)
- L73-102 _entry_ `void UVProjectionVS(FVertexFactoryInput Input, out FMeshProjectionVSToPS Output)` — stage: **vertex (from C++ binding)** — C++: `FMeshUVProjectionVS` SF_Vertex via IMPLEMENT_MATERIAL_SHADER_TYPE (Plugins/Runtime/nDisplay/Source/DisplayClusterLightCardEditorShaders/Private/DisplayClusterMeshProjectionRenderer.cpp:260)
- L126-141 _entry_ `void MainPS(FMeshProjectionVSToPS Input OPTIONAL_IsFrontFace, out float4 OutputColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FMeshProjectionColorPS` SF_Pixel via IMPLEMENT_MATERIAL_SHADER_TYPE (Plugins/Runtime/nDisplay/Source/DisplayClusterLightCardEditorShaders/Private/DisplayClusterMeshProjectionRenderer.cpp:302)
- L145-161 _entry_ `void NormalPS(FMeshProjectionVSToPS Input OPTIONAL_IsFrontFace, out float4 OutputColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FMeshProjectionNormalPS` SF_Pixel via IMPLEMENT_MATERIAL_SHADER_TYPE (Plugins/Runtime/nDisplay/Source/DisplayClusterLightCardEditorShaders/Private/DisplayClusterMeshProjectionRenderer.cpp:303)

#### Structs / classes (1)

- L10-16 _struct_ **`FMeshProjectionVSToPS`** `struct FMeshProjectionVSToPS`
  - L12 _member_ `FVertexFactoryInterpolantsVSToPS FactoryInterpolants;`
  - L13 _member_ `float4 Position : SV_POSITION;`
  - L14 _member_ `float4 SavedWorldPosition : POSITION1;`
  - L15 _member_ `float Azimuth : CUSTOM_AZIMUTH;`

#### Global parameters (uniforms) (5)

- L68 _parameter_ `uint ProjectionParameters_UVProjectionIndex;`
- L69 _parameter_ `float ProjectionParameters_UVProjectionPlaneSize;`
- L70 _parameter_ `float ProjectionParameters_UVProjectionPlaneDistance;`
- L71 _parameter_ `float3 ProjectionParameters_UVProjectionPlaneOffset;`
- L143 _parameter_ `float4x4 NormalCorrectionMatrix;`

#### Functions (2)

- L105-117 _function_ `float GetProjectionDivergence(FMeshProjectionVSToPS Input)` — Gets a scalar value that indicates how much the current pixel diverges from where it should be from the projected vertices
- L120-124 _function_ `void ClipDivergentPixel(FMeshProjectionVSToPS Input, float DivergenceThreshold)` — Clips any pixel whose projection divergence exceeds the specified threshold

### `Plugins/Runtime/nDisplay/Shaders/Private/OutputRemapShaders.usf` (Private)

- lines: 48; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`

#### Structs / classes (3)

- L9-13 _struct_ **`InputVS`** `struct InputVS`
  - L11 _member_ `float4 Position : ATTRIBUTE0;`
  - L12 _member_ `float2 UV : ATTRIBUTE1;`
- L15-19 _struct_ **`OutputVS`** `struct OutputVS`
  - L17 _member_ `float4 Position : SV_POSITION;`
  - L18 _member_ `float4 UV : TEXCOORD0;`
- L21-24 _struct_ **`OutputPS`** `struct OutputPS`
  - L23 _member_ `float4 Color : SV_Target0;`

#### Global resources (textures / buffers / samplers) (2)

- L5 _resource_ `Texture2D PostprocessInput0;`
- L6 _resource_ `SamplerState PostprocessInput0Sampler;`

#### Functions (2)

- L27-37 _function_ `OutputVS OutputRemap_VS(InputVS IN)`
- L40-47 _function_ `OutputPS OutputRemap_PS(OutputVS IN)`

### `Plugins/Runtime/nDisplay/Shaders/Private/OverlayShaders.usf` (Private)

- lines: 21; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`

#### Global resources (textures / buffers / samplers) (4)

- L5 _resource_ `Texture2D TextureOverlay;`
- L6 _resource_ `SamplerState SamplerOverlay;`
- L8 _resource_ `Texture2D TextureBase;`
- L9 _resource_ `SamplerState SamplerBase;`

#### Functions (1)

- L11-20 _function_ `float4 DrawOverlay_PS(float2 uv : TEXCOORD) : SV_Target` — sv-semantics

### `Plugins/Runtime/nDisplay/Shaders/Private/PicpPostProcessShaders.usf` (Private)

- lines: 99; parse: all-branches
- includes: L3 `/Engine/Public/Platform.ush`

#### Structs / classes (3)

- L5-9 _struct_ **`InputVS`** `struct InputVS`
  - L7 _member_ `float4 Position : ATTRIBUTE0;`
  - L8 _member_ `float2 UV : ATTRIBUTE1;`
- L10-14 _struct_ **`OutputVS`** `struct OutputVS`
  - L12 _member_ `float4 Position : SV_POSITION;`
  - L13 _member_ `float4 UV : TEXCOORD0;`
- L15-18 _struct_ **`OutputPS`** `struct OutputPS`
  - L17 _member_ `float4 Color : SV_Target0;`

#### Global resources (textures / buffers / samplers) (2)

- L35 _resource_ `Texture2D SrcTexture;`
- L38 _resource_ `SamplerState BilinearClampTextureSampler;`

#### Global parameters (uniforms) (2)

- L36 _parameter_ `float2 SampleOffset;`
- L37 _parameter_ `int KernelRadius;`

#### Functions (4)

- L21-32 _function_ `OutputVS DirectProjectionVS(InputVS IN)`
- L41-49 _function_ `OutputPS DirectComposePS(OutputVS IN)`
- L51-55 _function_ `float GaussianWeight1d(float u, float KernelRadius)`
- L58-99 _function_ `OutputPS BlurPostProcessPS(OutputVS IN)`

### `Plugins/Runtime/nDisplay/Shaders/Private/ResourceUtils.usf` (Private)

- lines: 239; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `DisplayClusterColorCorrection.ush`

#### Macros (#define, 14)

- L15 `#define ESourceEncoding_Linear 0`
- L16 `#define ESourceEncoding_Gamma 1`
- L17 `#define ESourceEncoding_sRGB 2`
- L18 `#define ESourceEncoding_MediaPQ 3`
- L20 `#define EOverrideAlpha_None 0`
- L21 `#define EOverrideAlpha_Invert 1`
- L22 `#define EOverrideAlpha_One 2`
- L23 `#define EOverrideAlpha_Zero 3`
- L34 `#define EColorPremultiply_None 0`
- L35 `#define EColorPremultiply_Alpha 1`
- L36 `#define EColorPremultiply_InvertedAlpha 2`
- L38 `#define ESideFeather_None 0`
- L39 `#define ESideFeather_Linear 1`
- L40 `#define ESideFeather_Smooth 2`

#### Entry points (1)

- L232-239 _entry_ `void Main( FScreenVertexOutput Input, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FColorEncodingCopyRectPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/nDisplay/Source/DisplayClusterShaders/Private/Shaders/DisplayClusterShadersCopyTexture.cpp:468)

#### Global resources (textures / buffers / samplers) (2)

- L7 _resource_ `Texture2D InputTexture;` — Input texture and sampler
- L8 _resource_ `SamplerState InputTextureSampler;`

#### Global parameters (uniforms) (5)

- L26 _parameter_ `uint3 Encodings;` — Color encoding parameters:
- L27 _parameter_ `float3 DisplayGamma;`
- L43 _parameter_ `uint3 ColorPremultiply;` — Color modifier
- L62 _parameter_ `float4 InnerFeatherMargins;` — Feather margins Outer LT              RT +---------------------+ \|                     \| \|  Inner LT      RT   \| \|     +----------+    \| \|     \|          \|    \| \|     +----------+    \| \|     LB         RB   \| +---------------------+ LB                    RB L,R,T,B = Left, Right, Top, Bottom InnerFeatherMargins = <InnerL, 1-InnerR, InnerT, 1-InnerB>  // Fully opaque region OuterFeatherMargins = <OuterL, 1-OuterR, OuterT, 1-OuterB>  // Fully transparent region
- L63 _parameter_ `float4 OuterFeatherMargins;`

#### Functions (3)

- L69-92 _function_ `float GetSideFeatherLinear(float2 UV)` — Returns a linearly feathered alpha based on UV position and side margins. The feathering fades from fully transparent (Max margins) to fully opaque (Min margins).
- L105-118 _function_ `float GetSideFeatherSmooth(float2 UV)` — Computes a feathered alpha value based on side-specific margins using smoothstep transitions. Logic: - Inside the inner margins ('InnerFeatherMargins'): alpha = 1 (fully opaque) - Outside the outer margins ('OuterFeatherMargins'): alpha = 0 (fully transparent) - Between Min and Max: alpha fades smoothly using smoothstep @param UV   UV coordinates (float2), expected in [0, 1] range @return       Alpha value in [0, 1] with smooth feathering on each side
- L121-230 _function_ `float4 DisplayClusterEncodeColorAndAlpha( FScreenVertexOutput Input, float4 InColorArg)` — Implements color encoding.

### `Plugins/Runtime/nDisplay/Shaders/Private/SubstrateUtils.ush` (Private)

- lines: 48; parse: all-branches

#### Macros (#define, 1)

- L33 `#define CurrentBSDF SubstratePixelHeader.SubstrateTree.BSDFs[BSDFIdx]` _[#if TEMPLATE_USES_SUBSTRATE]_
- L3 #pragma `once`; L38 #undef `CurrentBSDF`

#### Functions (1)

- L6-47 _function_ `float4 GetMaterialProperties(in FPixelMaterialInputs PixelMaterialInputs, in FMaterialPixelParameters MaterialParameters)`

### `Plugins/Runtime/nDisplay/Shaders/Private/TransformTexture.usf` (Private)

- lines: 25; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`

#### Global resources (textures / buffers / samplers) (2)

- L5 _resource_ `Texture2D Texture;`
- L6 _resource_ `SamplerState Sampler;`

#### Global parameters (uniforms) (1)

- L7 _parameter_ `float4 TransformMatrix;`

#### Functions (1)

- L9-24 _function_ `float4 TransformTexture_PS(float2 UV : TEXCOORD) : SV_Target` — sv-semantics

### `Plugins/Runtime/nDisplay/Shaders/Private/UVLightCardGammaCorrection.usf` (Private)

- lines: 18; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `DisplayClusterColorCorrection.ush`

#### Entry points (1)

- L10-18 _entry_ `float4 GammaCorrectionPS(noperspective float4 UVAndScreenPos : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FGammaCorrectionPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Runtime/nDisplay/Source/DisplayClusterShaders/Private/Shaders/DisplayClusterShadersPreprocess_UVLightCards.cpp:242)

#### Global resources (textures / buffers / samplers) (2)

- L6 _resource_ `Texture2D InputTexture;`
- L7 _resource_ `SamplerState InputSampler;`

### `Plugins/Runtime/nDisplay/Shaders/Private/UVLightCardShaders.usf` (Private)

- lines: 49; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `/Engine/Generated/Material.ush`, L5 `/Engine/Generated/VertexFactory.ush`, L7 `SubstrateUtils.ush`

#### Entry points (2)

- L23-37 _entry_ `void MainVS(FVertexFactoryInput Input, out FUVLightCardVSToPS Output)` — stage: **vertex (from C++ binding)** — C++: `FUVLightCardVS` SF_Vertex via IMPLEMENT_MATERIAL_SHADER_TYPE (Plugins/Runtime/nDisplay/Source/DisplayClusterShaders/Private/Shaders/DisplayClusterShadersPreprocess_UVLightCards.cpp:49)
- L39-48 _entry_ `void MainPS(FUVLightCardVSToPS Input OPTIONAL_IsFrontFace, out float4 OutputColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FUVLightCardPS` SF_Pixel via IMPLEMENT_MATERIAL_SHADER_TYPE (Plugins/Runtime/nDisplay/Source/DisplayClusterShaders/Private/Shaders/DisplayClusterShadersPreprocess_UVLightCards.cpp:75)

#### Structs / classes (2)

- L10-15 _struct_ **`FUVLightCardVSToPS`** `struct FUVLightCardVSToPS`
  - L12 _member_ `FVertexFactoryInterpolantsVSToPS FactoryInterpolants;`
  - L13 _member_ `float4 Position : SV_POSITION;`
  - L14 _member_ `float4 SavedWorldPosition : POSITION1;`
- L17-20 _struct_ **`OutputPS`** `struct OutputPS`
  - L19 _member_ `float4 Color : SV_Target0;`
