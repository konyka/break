# Shaders / Shaders/Private/VariableRateShading

- files: 6; lines: 589
- record kinds: cpp_binding=5, define=25, entry=5, function=12, groupshared=2, include=12, parameter=18, resource=18

### `Shaders/Private/VariableRateShading/VRSShadingRateCalculate.usf` (Private)

- lines: 133; parse: all-branches
- includes: L3 `VRSShadingRateCommon.ush`, L4 `../Common.ush`, L5 `../ColorSpace.ush`

#### Macros (#define, 4)

- L17 `#define SOBEL_DIMENSION 3`
- L19 `#define HW_TILES_PER_GROUP_X ((THREADGROUP_SIZE_X * 2) / HARDWARE_TILE_SIZE)`
- L20 `#define HW_TILES_PER_GROUP_Y ((THREADGROUP_SIZE_Y * 2) / HARDWARE_TILE_SIZE)`
- L21 `#define HW_TILES_PER_GROUP (HW_TILES_PER_GROUP_X * HW_TILES_PER_GROUP_Y)`

#### Entry points (1)

- L24-132 _entry_ `[numthreads(THREADGROUP_SIZE_X, THREADGROUP_SIZE_Y, 1)] void CalculateShadingRateImage( uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID, uint3 GroupId : SV_GroupID, uint GroupIndex : SV_GroupIndex)` — stage: **compute** — C++: `FCalculateShadingRateImageCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VariableRateShading/ContrastAdaptiveImageGenerator.cpp:137)

#### Global resources (textures / buffers / samplers) (4)

- L12 _resource_ `Texture2D<float> LuminanceTexture;`
- L13 _resource_ `SamplerState LuminanceSampler;`
- L14 _resource_ `RWTexture2D<uint> HardwareShadingRateImage;`
- L15 _resource_ `RWTexture2D<uint> SoftwareShadingRateImage;`

#### Global parameters (uniforms) (4)

- L7 _parameter_ `float4 ViewRect;`
- L8 _parameter_ `float EdgeThreshold;`
- L9 _parameter_ `float ConservativeEdgeThreshold;`
- L10 _parameter_ `float2 InvLuminanceTextureSize;`

#### groupshared (1)

- L22 _groupshared_ `groupshared uint GroupHWUnsupported[HW_TILES_PER_GROUP];`

### `Shaders/Private/VariableRateShading/VRSShadingRateCombine.usf` (Private)

- lines: 37; parse: all-branches
- includes: L3 `VRSShadingRateCommon.ush`, L4 `../Common.ush`

#### Entry points (1)

- L24-35 _entry_ `[numthreads(THREADGROUP_SIZE_XY, THREADGROUP_SIZE_XY, 1)] void CombineShadingRateTextures(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FCombineShadingRateTexturesCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VariableRateShading/VariableRateShadingImageManager.cpp:237)

#### Global resources (textures / buffers / samplers) (6)

- L7 _resource_ `RWTexture2D<float2> RWOutputTexture;` _[#if FRAGMENT_DENSITY_MAP]_
- L8 _resource_ `Texture2D<float2> SourceTexture0;` _[#if FRAGMENT_DENSITY_MAP]_
- L9 _resource_ `Texture2D<float2> SourceTexture1;` _[#if FRAGMENT_DENSITY_MAP]_
- L11 _resource_ `RWTexture2D<uint> RWOutputTexture;` _[#if !(FRAGMENT_DENSITY_MAP)]_
- L12 _resource_ `Texture2D<uint> SourceTexture0;` _[#if !(FRAGMENT_DENSITY_MAP)]_
- L13 _resource_ `Texture2D<uint> SourceTexture1;` _[#if !(FRAGMENT_DENSITY_MAP)]_

#### Functions (1)

- L16-22 _function_ `uint ShadingRateMax(uint InputRate0, uint InputRate1)`

### `Shaders/Private/VariableRateShading/VRSShadingRateCommon.ush` (Private)

- lines: 150; parse: all-branches

#### Macros (#define, 21)

- L6 `#define D3D12_AXIS_SHADING_RATE_1X 0x0`
- L7 `#define D3D12_AXIS_SHADING_RATE_2X 0x1`
- L8 `#define D3D12_AXIS_SHADING_RATE_4X 0x2`
- L10 `#define D3D12_SHADING_RATE_1X1 0x0`
- L11 `#define D3D12_SHADING_RATE_1X2 0x1`
- L12 `#define D3D12_SHADING_RATE_2X1 0x4`
- L13 `#define D3D12_SHADING_RATE_2X2 0x5`
- L14 `#define D3D12_SHADING_RATE_2X4 0x6`
- L15 `#define D3D12_SHADING_RATE_4X2 0x9`
- L16 `#define D3D12_SHADING_RATE_4X4 0xa`
- L18 `#define D3D12_SHADING_RATE_X_AXIS_SHIFT 2`
- L19 `#define D3D12_SHADING_RATE_VALID_MASK 3`
- L20 `#define D3D12_SHADING_RATE_MAX_BITS 4`
- L23 `#define CONSERVATIVE_SHADING_RATE_SHIFT D3D12_SHADING_RATE_MAX_BITS`
- L26 `#define RATE_1X1_COLOR float3(1.0, 0.0, 0.0)`
- L27 `#define RATE_1X2_COLOR float3(1.0, 0.5, 0.0)`
- L28 `#define RATE_2X1_COLOR float3(1.0, 1.0, 0.0)`
- L29 `#define RATE_2X2_COLOR float3(0.0, 1.0, 0.0)`
- L30 `#define RATE_2X4_COLOR float3(0.0, 0.0, 1.0)`
- L31 `#define RATE_4X2_COLOR float3(1.0, 0.0, 1.0)`
- L32 `#define RATE_4X4_COLOR float3(1.0, 0.5, 1.0)`
- L3 #pragma `once`

#### Functions (8)

- L35-41 _function_ `uint2 SeparateShadingRateAxes(uint CombinedShadingRate)` — Utilities to go to/from a single uint representing the shading rate of both axes <--> a uint2 representing each per-axis rate
- L43-46 _function_ `uint CombineShadingRateAxes(uint2 SeparatedShadingRate)`
- L51-65 _function_ `float AxisShadingRateToFragmentDensity(uint AxisShadingRate)` — Utilities to convert to/from a palette shading rate <--> fragment density These conversions are approximate and may exactly match how the requested rate/density is interpreted by the driver
- L67-83 _function_ `uint AxisFragmentDensityToShadingRate(float AxisFragmentDensity)`
- L85-91 _function_ `float2 ShadingRateToFragmentDensity(uint ShadingRate)`
- L93-110 _function_ `uint FragmentDensityToShadingRate(float2 FragmentDensity)`
- L114-144 _function_ `float4 VisualizeShadingRate(uint ShadingRate)` — Utilities to convert a shading rate or fragment density into a preview overlay color
- L146-150 _function_ `float4 VisualizeFragmentDensity(float2 FragmentDensity)`

### `Shaders/Private/VariableRateShading/VRSShadingRateFoveated.usf` (Private)

- lines: 100; parse: all-branches
- includes: L7 `../Common.ush`

#### Entry points (1)

- L94-99 _entry_ `[numthreads(THREADGROUP_SIZEX, THREADGROUP_SIZEY, 1)] void GenerateShadingRateTexture(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FComputeVariableRateShadingImageGeneration` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VariableRateShading/FoveatedImageGenerator.cpp:122)

#### Global resources (textures / buffers / samplers) (1)

- L25 _resource_ `RWTexture2D<uint> RWOutputTexture;` — Generated output shading rate attachment.

#### Global parameters (uniforms) (7)

- L28 _parameter_ `float2 FieldOfView;` — Horizontal and vertical field of view for the current view.
- L31 _parameter_ `float2 LeftEyeCenterPixelXY;` — Center pixel coordinate for the left eye.
- L34 _parameter_ `float2 RightEyeCenterPixelXY;` — Center pixel coordinate for the right eye.
- L37 _parameter_ `float ViewDiagonalSquaredInPixels;` — Diagonal of the view in pixels, squared.
- L39 _parameter_ `float FoveationFullRateCutoffSquared;` — Cutoff percentage for full-rate shading, foveation (0.0 to 1.0), squared. Outside this range will be shaded at half-rate in x and y.
- L41 _parameter_ `float FoveationHalfRateCutoffSquared;` — Cutoff percentage for half-rate shading, foveation (0.0 to 1.0), squared. Outside this range will be shaded at quarter-rate in x and y.
- L47 _parameter_ `uint ShadingRateAttachmentGenerationFlags;` — Bitfield indicating optional supporting things (defined in the EVRSGenerationFlags enum:) EVRSGenerationFlags::None = 0x0, EVRSGenerationFlags::StereoRendering = 0x1, EVRSGenerationFlags::SideBySideStereo = 0x2,

#### Functions (2)

- L55-69 _function_ `float GetFractionalOffsetFromEyeOrigin(float2 PixelPosition)`
- L75-91 _function_ `uint GetFoveatedShadingRate(uint2 PixelPositionIn)`

### `Shaders/Private/VariableRateShading/VRSShadingRatePreview.usf` (Private)

- lines: 34; parse: all-branches
- includes: L3 `VRSShadingRateCommon.ush`, L4 `../Common.ush`, L5 `../ColorSpace.ush`

#### Entry points (1)

- L17-33 _entry_ `void PreviewVariableRateShadingTexturePS( noperspective float4 UVAndScreenPos : TEXCOORD0, out float4 OutColor : SV_Target0)` — stage: **pixel (from C++ binding)** — C++: `FDebugVariableRateShadingPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VariableRateShading/VariableRateShadingImageManager.cpp:266)

#### Global resources (textures / buffers / samplers) (3)

- L10 _resource_ `RWTexture2D<float4> SceneColorOut;`
- L12 _resource_ `Texture2D<float2> VariableRateShadingTextureIn;` _[#if FRAGMENT_DENSITY_MAP]_
- L14 _resource_ `Texture2D<uint> VariableRateShadingTextureIn;` _[#if !(FRAGMENT_DENSITY_MAP)]_

#### Global parameters (uniforms) (2)

- L7 _parameter_ `float4 ViewRect;`
- L8 _parameter_ `float DynamicResolutionScale;`

### `Shaders/Private/VariableRateShading/VRSShadingRateReproject.usf` (Private)

- lines: 135; parse: all-branches
- includes: L3 `VRSShadingRateCommon.ush`, L4 `../Common.ush`, L5 `../SceneTexturesCommon.ush`

#### Entry points (1)

- L65-134 _entry_ `[numthreads(THREADGROUP_SIZE, THREADGROUP_SIZE, 1)] void RescaleVariableRateShading( uint3 DispatchThreadId : SV_DispatchThreadID, uint3 GroupThreadId : SV_GroupThreadID)` — stage: **compute** — C++: `FRescaleVariableRateShadingCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Source/Runtime/Renderer/Private/VariableRateShading/ContrastAdaptiveImageGenerator.cpp:198)

#### Global resources (textures / buffers / samplers) (4)

- L9 _resource_ `float2 TextureDimensions;`
- L15 _resource_ `Texture2D<uint> InputSRITexture;`
- L16 _resource_ `RWTexture2D<uint> ScaledSRITexture;`
- L17 _resource_ `RWTexture2D<uint> ScaledConservativeSRITexture;`

#### Global parameters (uniforms) (5)

- L7 _parameter_ `float2 InputSRIDimensions;`
- L8 _parameter_ `float2 ScaledSRIDimensions;`
- L10 _parameter_ `float2 InvTextureDimensions;`
- L12 _parameter_ `float2 ScaledUVOffset;`
- L13 _parameter_ `float InvDynamicResolutionScale;`

#### groupshared (1)

- L19 _groupshared_ `groupshared float CachedDepth[THREADGROUP_SIZE / 2][THREADGROUP_SIZE / 2];`

#### Functions (1)

- L34-63 _function_ `float2 ReprojectBufferUV(uint3 DispatchThreadId, uint3 GroupThreadId, float2 BufferUV, bool bValidThread)` — This is a large approximation of reprojection in a couple of ways in favor of performance: 1. We only look at reprojection based on the camera, not velocity vectors. I.E. this will be incorrect for dynamic objects. In most cases motion blur will hide this entirely, though I found no perceptable artifacts even with motion blur off 2. The reprojection only does one depth texture fetch in the center of each 16x16 pixel block. Both of these approximations are fine because VRS doesn't require a whole lot of accuracy since the side-effect is just lower resolution in areas that are "wrong" rather tha
