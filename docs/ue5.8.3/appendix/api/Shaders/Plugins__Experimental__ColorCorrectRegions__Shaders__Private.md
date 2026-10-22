# Shaders / Plugins/Experimental/ColorCorrectRegions/Shaders/Private

- files: 4; lines: 902
- record kinds: cpp_binding=6, define=53, entry=6, function=19, include=20, macro_call=6, member=66, parameter=1, resource=16, struct=5

### `Plugins/Experimental/ColorCorrectRegions/Shaders/Private/ColorCorrectRegionsCommon.usf` (Private)

- lines: 379; parse: all-branches
- includes: L3 `/Engine/Private/DeferredShadingCommon.ush`

#### Macros (#define, 39)

- L9 `#define NEEDS_SCENE_TEXTURES 1`
- L34 `#define PostProcessInput_0_SharedSampler PostProcessInput_0_Sampler`
- L35 `#define PostProcessInput_1_SharedSampler PostProcessInput_1_Sampler`
- L36 `#define PostProcessInput_2_SharedSampler PostProcessInput_2_Sampler`
- L37 `#define PostProcessInput_3_SharedSampler PostProcessInput_3_Sampler`
- L38 `#define PostProcessInput_4_SharedSampler PostProcessInput_4_Sampler`
- L43 `#define PPI_SceneColor 0`
- L44 `#define PPI_SceneDepth 1`
- L45 `#define PPI_DiffuseColor 2`
- L46 `#define PPI_SpecularColor 3`
- L47 `#define PPI_SubsurfaceColor 4`
- L48 `#define PPI_BaseColor 5`
- L49 `#define PPI_Specular 6`
- L50 `#define PPI_Metallic 7`
- L51 `#define PPI_WorldNormal 8`
- L52 `#define PPI_SeparateTranslucency 9`
- L53 `#define PPI_Opacity 10`
- L54 `#define PPI_Roughness 11`
- L55 `#define PPI_MaterialAO 12`
- L56 `#define PPI_CustomDepth 13`
- L57 `#define PPI_PostProcessInput0 14`
- L58 `#define PPI_PostProcessInput1 15`
- L59 `#define PPI_PostProcessInput2 16`
- L60 `#define PPI_PostProcessInput3 17`
- L61 `#define PPI_PostProcessInput4 18`
- L62 `#define PPI_PostProcessInput5 19`
- L63 `#define PPI_PostProcessInput6 20`
- L64 `#define PPI_DecalMask 21`
- L65 `#define PPI_ShadingModelColor 22`
- L66 `#define PPI_ShadingModelID 23`
- L67 `#define PPI_AmbientOcclusion 24`
- L68 `#define PPI_CustomStencil 25`
- L69 `#define PPI_StoredBaseColor 26`
- L70 `#define PPI_StoredSpecular 27`
- L71 `#define PPI_Velocity 28`
- L72 `#define PPI_WorldTangent 29`
- L73 `#define PPI_Anisotropy 30`
- L74 `#define PPI_IsFirstPerson 31`
- L292 `#define POST_PROCESS_INPUT(Index) { if (bFiltered) { return Texture2DSample(PostProcessInput_##Index##_Texture, PostProcessInput_BilinearSampler, UV); } else { return Texture2DSample(PostProcessInput_##Index##_Texture, PostProcessInpu ...` (11 lines)
- L7 #undef `NEEDS_SCENE_TEXTURES`

#### Structs / classes (3)

- L84-117 _struct_ **`FMaterialPixelParameters`** `struct FMaterialPixelParameters` — Parameters needed by pixel shader material inputs, related to Geometry. These are independent of vertex factory.
  - L87 _member_ `half3 WorldNormal;` — Normalized world space normal.
  - L90 _member_ `half3 WorldTangent;` — Normalized world space tangent.
  - L93 _member_ `half3 ReflectionVector;` — Normalized world space reflected camera vector.
  - L96 _member_ `half3 CameraVector;` — Normalized world space camera vector, which is the vector from the point being shaded to the camera position.
  - L103 _member_ `MaterialFloat4 SvPosition;` — Like SV_Position (.xy is pixel position at pixel center, z:DeviceZ, .w:SceneDepth) using shader generated value SV_POSITION Note: this is not relative to the current viewport.  RelativePixelPosition = MaterialParameters.SvPosition.xy - View.ViewRectMin.xy;
  - L106 _member_ `MaterialFloat4 ScreenPosition;` — Post projection position reconstructed from SvPosition, before the divide by W. left..top -1..1, bottom..top -1..1  within the viewport, W is the SceneDepth
  - L111 _member_ `MaterialFloat3 AbsoluteWorldPosition;` — Interpolated worldspace position of this pixel
  - L116 _member_ `MaterialFloat3 WorldPosition_CamRelative;` — Interpolated worldspace position of this pixel, centered around the camera
- L123-141 _struct_ **`FPixelMaterialInputs`** `struct FPixelMaterialInputs` — Parameters calculated from the pixel material inputs.
  - L125 _member_ `MaterialFloat3 EmissiveColor;`
  - L126 _member_ `MaterialFloat Opacity;`
  - L127 _member_ `MaterialFloat OpacityMask;`
  - L128 _member_ `MaterialFloat3 BaseColor;`
  - L129 _member_ `MaterialFloat Metallic;`
  - L130 _member_ `MaterialFloat Specular;`
  - L131 _member_ `MaterialFloat Roughness;`
  - L132 _member_ `MaterialFloat Anisotropy;`
  - L133 _member_ `MaterialFloat3 Normal;`
  - L134 _member_ `MaterialFloat3 Tangent;`
  - L135 _member_ `MaterialFloat4 Subsurface;`
  - L136 _member_ `MaterialFloat AmbientOcclusion;`
  - L137 _member_ `MaterialFloat2 Refraction;`
  - L138 _member_ `MaterialFloat PixelDepthOffset;`
  - L139 _member_ `uint ShadingModel;`
- L148-169 _struct_ **`FMaterialVertexParameters`** `struct FMaterialVertexParameters` — Parameters needed by vertex shader material inputs. These are independent of vertex factory.
  - L153 _member_ `MaterialFloat3 WorldPosition;` — Position in the translated world (VertexFactoryGetWorldPosition). Previous position in the translated world (VertexFactoryGetPreviousWorldPosition) if computing material's output for previous frame (See {BasePassVertex,Velocity}Shader.usf).
  - L155 _member_ `half3x3 TangentToWorld;` — TangentToWorld[2] is WorldVertexNormal
  - L159 _member_ `MaterialFloat4x4 PrevFrameLocalToWorld;` — If either USE_INSTANCING or (IS_MESHPARTICLE_FACTORY && FEATURE_LEVEL >= FEATURE_LEVEL_SM4) is true, PrevFrameLocalToWorld is a per-instance transform
  - L161 _member_ `MaterialFloat3 PreSkinnedPosition;`
  - L162 _member_ `MaterialFloat3 PreSkinnedNormal;`
  - L164 _member_ `half4 VertexColor;`
  - L167 _member_ `uint PrimitiveId;` — Index into View.PrimitiveSceneData

#### Global resources (textures / buffers / samplers) (12)

- L18 _resource_ `Texture2D PostProcessInput_0_Texture;`
- L19 _resource_ `Texture2D PostProcessInput_1_Texture;`
- L20 _resource_ `Texture2D PostProcessInput_2_Texture;`
- L21 _resource_ `Texture2D PostProcessInput_3_Texture;`
- L22 _resource_ `Texture2D PostProcessInput_4_Texture;`
- L24 _resource_ `SamplerState PostProcessInput_0_Sampler;`
- L25 _resource_ `SamplerState PostProcessInput_1_Sampler;`
- L26 _resource_ `SamplerState PostProcessInput_2_Sampler;`
- L27 _resource_ `SamplerState PostProcessInput_3_Sampler;`
- L28 _resource_ `SamplerState PostProcessInput_4_Sampler;`
- L31 _resource_ `SamplerState PostProcessInputSampler;`
- L32 _resource_ `SamplerState PostProcessInput_BilinearSampler;`

#### Functions (13)

- L171-179 _function_ `MaterialFloat3 ComposureColorGradePerRange(MaterialFloat3 ColorAP1, MaterialFloat4 ColorSaturation, MaterialFloat4 ColorContrast, MaterialFloat4 ColorGamma, MaterialFloat4 ColorGain, MaterialFloat4 ColorOffset)`
- L183-191 _function_ `MaterialFloat3 ReflectionAboutCustomWorldNormal(FMaterialPixelParameters Parameters, MaterialFloat3 WorldNormal, bool bNormalizeInputNormal)` — Calculate a reflection vector about the specified world space normal. Optionally normalize this normal
- L194-197 _function_ `MaterialFloat3 GetWorldPosition(FMaterialPixelParameters Parameters)`
- L199-202 _function_ `MaterialFloat2 GetPixelPosition(FMaterialPixelParameters Parameters)`
- L204-207 _function_ `MaterialFloat2 GetViewportUV(FMaterialPixelParameters Parameters)`
- L209-212 _function_ `half3 GetMaterialNormalRaw(FPixelMaterialInputs PixelMaterialInputs)`
- L214-219 _function_ `half3 GetMaterialNormal(FMaterialPixelParameters Parameters, FPixelMaterialInputs PixelMaterialInputs)`
- L222-225 _function_ `bool IsPostProcessInputSceneTexture(const uint SceneTextureId)` — Returns whether a scene texture id is a for a post process input or not.
- L228-250 _function_ `MaterialFloat2 ViewportUVToSceneTextureUV(MaterialFloat2 ViewportUV, const uint SceneTextureId)` — Transforms viewport UV to scene texture's UV.
- L253-256 _function_ `MaterialFloat2 GetDefaultSceneTextureUV(FMaterialPixelParameters Parameters, const uint SceneTextureId)` — Get default scene texture's UV.
- L259-275 _function_ `MaterialFloat3 RotateAboutAxis(MaterialFloat4 NormalizedRotationAxisAndAngle, MaterialFloat3 PositionOnAxis, MaterialFloat3 Position)` — Rotates Position about the given axis by the given angle, in radians, and returns the offset to Position.
- L277-289 _function_ `MaterialFloat3 RotateTranslateScale(MaterialFloat3 OriginalVec, MaterialFloat3 Translation, MaterialFloat3 Rotation, MaterialFloat3 Scale)`
- L305-377 _function_ `float4 SceneTextureLookup(float2 UV, int SceneTextureIndex, bool bFiltered)` — Applies an offset to the scene texture lookup and decodes the HDR linear space color.

#### Top-level macro invocations (6)

- L11 _macro_call_ `SCREEN_PASS_TEXTURE_VIEWPORT(PostProcessInput_0)`
- L12 _macro_call_ `SCREEN_PASS_TEXTURE_VIEWPORT(PostProcessInput_1)`
- L13 _macro_call_ `SCREEN_PASS_TEXTURE_VIEWPORT(PostProcessInput_2)`
- L14 _macro_call_ `SCREEN_PASS_TEXTURE_VIEWPORT(PostProcessInput_3)`
- L15 _macro_call_ `SCREEN_PASS_TEXTURE_VIEWPORT(PostProcessInput_4)`
- L16 _macro_call_ `SCREEN_PASS_TEXTURE_VIEWPORT(PostProcessOutput)`

### `Plugins/Experimental/ColorCorrectRegions/Shaders/Private/ColorCorrectRegionsScreenPass.usf` (Private)

- lines: 34; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`

#### Entry points (3)

- L10-17 _entry_ `void MainVS( in float4 InPosition : ATTRIBUTE0, in float2 InTexCoord : ATTRIBUTE1, out noperspective float4 OutUVAndScreenPos : TEXCOORD0, out float4 OutPosition : SV_POSITION)` — stage: **vertex (from C++ binding)** — C++: `FColorCorrectScreenPassVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/ColorCorrectRegions/Source/ColorCorrectRegions/Private/ColorCorrectRegionsPostProcessMaterial.cpp:15)
- L20-26 _entry_ `float4 MainPS( noperspective float4 UVAndScreenPos : TEXCOORD0 ) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FClearRectPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/ColorCorrectRegions/Source/ColorCorrectRegions/Private/ColorCorrectRegionsPostProcessMaterial.cpp:16) _[#if !CLEAR_PS]_
- L28-33 _entry_ `float4 MainPS( noperspective float4 UVAndScreenPos : TEXCOORD0 ) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FClearRectPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/ColorCorrectRegions/Source/ColorCorrectRegions/Private/ColorCorrectRegionsPostProcessMaterial.cpp:16) _[#if !(!CLEAR_PS)]_

#### Global resources (textures / buffers / samplers) (2)

- L6 _resource_ `Texture2D InputTexture;` _[#if !CLEAR_PS]_
- L7 _resource_ `SamplerState InputSampler;` _[#if !CLEAR_PS]_

### `Plugins/Experimental/ColorCorrectRegions/Shaders/Private/ColorCorrectRegionsShader.usf` (Private)

- lines: 449; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `/Engine/Private/ColorUtils.ush`, L5 `/Engine/Private/DistanceField/GlobalDistanceFieldShared.ush`, L6 `/Engine/Generated/GeneratedUniformBuffers.ush`, L7 `/Engine/Private/Random.ush`, L8 `/Engine/Private/SceneTexturesCommon.ush`, L9 `/Engine/Private/SceneData.ush`, L10 `/Engine/Private/ScreenPass.ush`, L11 `/Engine/Private/SceneTextureParameters.ush`, L12 `/Engine/Private/TonemapCommon.ush`, L14 `/ColorCorrectRegionsShaders/Private/ColorCorrectRegionsCommon.usf`

#### Macros (#define, 14)

- L19 `#define SHAPE_TYPE_SPHERE 0`
- L20 `#define SHAPE_TYPE_BOX 1`
- L21 `#define SHAPE_TYPE_CYLINDER 2`
- L22 `#define SHAPE_TYPE_CONE 3`
- L24 `#define WINDOW_TYPE_PLANE 0`
- L25 `#define WINDOW_TYPE_CIRCLE 1`
- L27 `#define TEMPERATURE_TYPE_LEGACY 0`
- L28 `#define TEMPERATURE_TYPE_WHITE_BALANCE 1`
- L29 `#define TEMPERATURE_TYPE_COLOR_TEMP 2`
- L30 `#define TEMPERATURE_TYPE_SKIP 3`
- L32 `#define CCR_SHADER_DISPLAY_BOUNDING_RECT 0`
- L33 `#define CLIP_PIXELS_OUTSIDE_AABB 1`
- L35 `#define EXCLUDE_STENCIL 0`
- L94 `#define HIGHLIGHT_INTERPOLATION_THRESHOLD_WIDTH 1.0` _[#if ADVANCED_CC]_

#### Entry points (2)

- L395-403 _entry_ `void MainVS( in float4 InPosition : ATTRIBUTE0, out FPostProcessMaterialVSToPS Output )` — stage: **vertex (from C++ binding)** — C++: `FColorCorrectRegionMaterialVS` SF_Vertex via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/ColorCorrectRegions/Source/ColorCorrectRegions/Private/ColorCorrectRegionsPostProcessMaterial.cpp:12) _[#if (FEATURE_LEVEL > FEATURE_LEVEL_ES3_1)]_
- L429-446 _entry_ `void MainPS( in FPostProcessMaterialVSToPS Input, out float4 OutColor : SV_Target0 )` — stage: **pixel (from C++ binding)** — C++: `FColorCorrectRegionMaterialPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/ColorCorrectRegions/Source/ColorCorrectRegions/Private/ColorCorrectRegionsPostProcessMaterial.cpp:13) — C++: `FColorCorrectWindowMaterialPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/ColorCorrectRegions/Source/ColorCorrectRegions/Private/ColorCorrectRegionsPostProcessMaterial.cpp:14) _[#if (FEATURE_LEVEL > FEATURE_LEVEL_ES3_1)]_

#### Structs / classes (2)

- L39-85 _struct_ **`FExternalExpressions`** `struct FExternalExpressions`
  - L41 _member_ `float3 Rotate;`
  - L42 _member_ `float3 Translate;`
  - L43 _member_ `float3 Scale;`
  - L45 _member_ `float4 ColorSaturation;`
  - L46 _member_ `float4 ColorContrast;`
  - L47 _member_ `float4 ColorGamma;`
  - L48 _member_ `float4 ColorGain;`
  - L49 _member_ `float4 ColorOffset;`
  - L52 _member_ `float4 ColorSaturationShadows;` _[#if ADVANCED_CC]_
  - L53 _member_ `float4 ColorContrastShadows;` _[#if ADVANCED_CC]_
  - L54 _member_ `float4 ColorGammaShadows;` _[#if ADVANCED_CC]_
  - L55 _member_ `float4 ColorGainShadows;` _[#if ADVANCED_CC]_
  - L56 _member_ `float4 ColorOffsetShadows;` _[#if ADVANCED_CC]_
  - L57 _member_ `float ShadowMax;` _[#if ADVANCED_CC]_
  - L59 _member_ `float4 ColorSaturationMidtones;` _[#if ADVANCED_CC]_
  - L60 _member_ `float4 ColorContrastMidtones;` _[#if ADVANCED_CC]_
  - L61 _member_ `float4 ColorGammaMidtones;` _[#if ADVANCED_CC]_
  - L62 _member_ `float4 ColorGainMidtones;` _[#if ADVANCED_CC]_
  - L63 _member_ `float4 ColorOffsetMidtones;` _[#if ADVANCED_CC]_
  - L65 _member_ `float4 ColorSaturationHighlights;` _[#if ADVANCED_CC]_
  - L66 _member_ `float4 ColorContrastHighlights;` _[#if ADVANCED_CC]_
  - L67 _member_ `float4 ColorGammaHighlights;` _[#if ADVANCED_CC]_
  - L68 _member_ `float4 ColorGainHighlights;` _[#if ADVANCED_CC]_
  - L69 _member_ `float4 ColorOffsetHighlights;` _[#if ADVANCED_CC]_
  - L70 _member_ `float HighlightsMin;` _[#if ADVANCED_CC]_
  - L72 _member_ `float WhiteTemp;`
  - L73 _member_ `float Tint;`
  - L74 _member_ `float Inner;`
  - L75 _member_ `float Outer;`
  - L77 _member_ `float Falloff;`
  - L78 _member_ `float Invert;`
  - L79 _member_ `float Intensity;`
  - L81 _member_ `float FakeLight;`
  - L82 _member_ `uint ExcludeStencil;`
  - L84 _member_ `float4 SceneTexture;`
- L389-392 _struct_ **`FPostProcessMaterialVSToPS`** `struct FPostProcessMaterialVSToPS`
  - L391 _member_ `float4 Position : SV_POSITION;`

#### Global resources (textures / buffers / samplers) (1)

- L37 _resource_ `Texture2D<uint> MergedStencilTexture;`

#### Functions (6)

- L87-150 _function_ `MaterialFloat3 ProcessColor(in FExternalExpressions ExternalExpressions)`
- L153-193 _function_ `float GetShapeAlpha(in out FMaterialPixelParameters Parameters, in FExternalExpressions ExternalExpressions)` _[#if defined(WINDOW_TYPE)]_
- L196-247 _function_ `float GetShapeAlpha(in out FMaterialPixelParameters Parameters, in FExternalExpressions ExternalExpressions)` _[#if !(defined(WINDOW_TYPE))]_
- L250-300 _function_ `MaterialFloat4 ProcessRegion(in out FMaterialPixelParameters Parameters, in FExternalExpressions ExternalExpressions)`
- L302-387 _function_ `void CalcPixelMaterialInputs(in out FMaterialPixelParameters Parameters, in out FPixelMaterialInputs PixelMaterialInputs)`
- L404-427 _function_ `void BuildParameters(in FPostProcessMaterialVSToPS Input, inout FMaterialPixelParameters Parameters)` _[#if (FEATURE_LEVEL > FEATURE_LEVEL_ES3_1)]_

### `Plugins/Experimental/ColorCorrectRegions/Shaders/Private/ColorCorrectRegionsStencilMerger.usf` (Private)

- lines: 40; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `/Engine/Private/DeferredShadingCommon.ush`, L5 `/Engine/Private/SceneTexturesCommon.ush`, L6 `/Engine/Private/ScreenPass.ush`, L7 `/Engine/Private/SceneTextureParameters.ush`, L8 `/Engine/Private/SceneData.ush`, L9 `/ColorCorrectRegionsShaders/Private/ColorCorrectRegionsCommon.usf`

#### Entry points (1)

- L15-39 _entry_ `uint MainPS( noperspective float4 UVAndScreenPos : TEXCOORD0 ) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FCCRStencilMergerPS` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/ColorCorrectRegions/Source/ColorCorrectRegions/Private/ColorCorrectRegionsPostProcessMaterial.cpp:18)

#### Global resources (textures / buffers / samplers) (1)

- L12 _resource_ `StructuredBuffer<uint> StencilIds;`

#### Global parameters (uniforms) (1)

- L13 _parameter_ `uint StencilIdCount;`
