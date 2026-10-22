# Shaders / Plugins/TextureGraph/Shaders/Layer

- files: 17; lines: 895
- record kinds: cpp_binding=6, define=14, entry=6, function=29, include=30, macro_call=2, parameter=68, resource=23

### `Plugins/TextureGraph/Shaders/Layer/AdjustColor.usf` (Other)

- lines: 45; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L3 `/Plugin/TextureGraph/SamplerStates.ush`

#### Macros (#define, 3)

- L6 `#define CLEAR_COLOR 0` _[#if !defined(CLEAR_COLOR)]_
- L9 `#define SHIFT_ALPHA 0` _[#if !defined(SHIFT_ALPHA)]_
- L12 `#define INVERT 0` _[#if !defined(INVERT)]_

#### Entry points (1)

- L19-45 _entry_ `float4 FSH_AdjustColor(in float2 uvSource : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_AdjustColor` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Layer/T_AdjustColor.cpp:10)

#### Global resources (textures / buffers / samplers) (1)

- L17 _resource_ `Texture2D SourceTex;`

#### Global parameters (uniforms) (3)

- L14 _parameter_ `float4 ColorOffset;`
- L15 _parameter_ `float Contrast;`
- L16 _parameter_ `float4 AverageColor;`

### `Plugins/TextureGraph/Shaders/Layer/AdjustDisplacement.usf` (Other)

- lines: 16; parse: all-branches
- includes: L3 `AdjustUVCommon.ush`

#### Global resources (textures / buffers / samplers) (1)

- L8 _resource_ `Texture2D SourceTex;`

#### Global parameters (uniforms) (3)

- L5 _parameter_ `float HeightMultiplier;`
- L6 _parameter_ `float HeightMidPoint;`
- L7 _parameter_ `float IsGreyscale;`

#### Functions (1)

- L10-15 _function_ `float4 FSH_AdjustDisplacement(in float2 uv : TEXCOORD0) : SV_Target0` — sv-semantics

### `Plugins/TextureGraph/Shaders/Layer/AdjustFrequency.usf` (Other)

- lines: 41; parse: all-branches
- includes: L6 `/Engine/Public/Platform.ush`, L12 `../TiledFetch.ush`

#### Macros (#define, 1)

- L3 `#define SOLID 0` _[#if !defined(SOLID)]_

#### Entry points (1)

- L20-40 _entry_ `float4 FSH_AdjustFrequency(in float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_AdjustFrequency` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Layer/T_AdjustFrequency.cpp:11)

#### Global resources (textures / buffers / samplers) (1)

- L9 _resource_ `Texture2D MainTex;`

#### Global parameters (uniforms) (3)

- L15 _parameter_ `float FreqLow;`
- L16 _parameter_ `float Threshold;`
- L17 _parameter_ `float FreqHigh;`

#### Top-level macro invocations (1)

- L13 _macro_call_ `Declare_Tiles_And_FetchTiled(BlurredTex)`

### `Plugins/TextureGraph/Shaders/Layer/AdjustFrequencyNormals.usf` (Other)

- lines: 84; parse: all-branches
- includes: L6 `/Engine/Public/Platform.ush`, L12 `../TiledFetch.ush`

#### Macros (#define, 1)

- L3 `#define RENORMALIZE 0` _[#if !defined(RENORMALIZE)]_

#### Entry points (1)

- L67-83 _entry_ `float4 FSH_AdjustFrequencyNormals(in float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_AdjustFrequencyNormals` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Layer/T_AdjustFrequency.cpp:12)

#### Global resources (textures / buffers / samplers) (1)

- L9 _resource_ `Texture2D MainTex;`

#### Global parameters (uniforms) (3)

- L15 _parameter_ `float FreqLow;`
- L16 _parameter_ `float Threshold;`
- L17 _parameter_ `float FreqHigh;`

#### Functions (7)

- L19-22 _function_ `float3 PartialDerivatesBlend(float3 n1, float3 n2)`
- L24-27 _function_ `float3 BlendNormals(float3 n1, float3 n2)`
- L29-33 _function_ `float3 ReconstructNormalZ(float2 rg)`
- L35-38 _function_ `float3 ReconstructNormalZ(float3 rgb)`
- L41-47 _function_ `float3 ConformNormals(float3 inputNormals)`
- L49-56 _function_ `float3 ConformBlurry(float3 A)`
- L58-65 _function_ `float3 ConformCrisp(float3 A)`

#### Top-level macro invocations (1)

- L13 _macro_call_ `Declare_Tiles_And_FetchTiled(BlurredTex)`

### `Plugins/TextureGraph/Shaders/Layer/AdjustGeneric.usf` (Other)

- lines: 17; parse: all-branches
- includes: L2 `AdjustUVCommon.ush`

#### Global resources (textures / buffers / samplers) (1)

- L6 _resource_ `Texture2D SourceTex;`

#### Global parameters (uniforms) (2)

- L4 _parameter_ `float ClampMaskX;`
- L5 _parameter_ `float ClampMaskY;`

#### Functions (1)

- L8-16 _function_ `float4 FSH_AdjustGeneric(in float2 uv : TEXCOORD0) : SV_Target0` — sv-semantics

### `Plugins/TextureGraph/Shaders/Layer/AdjustHexaplanarDisplacement.usf` (Other)

- lines: 57; parse: all-branches
- includes: L4 `/Engine/Public/Platform.ush`, L6 `../Placement_Projection.ush`

#### Global resources (textures / buffers / samplers) (1)

- L8 _resource_ `Texture2DArray CombinedBlob;`

#### Global parameters (uniforms) (7)

- L10 _parameter_ `float2 VerticalAxisRotation;`
- L11 _parameter_ `float2 LateralAxisRotation;`
- L12 _parameter_ `float2 UVScaling;`
- L14 _parameter_ `float Radius;`
- L15 _parameter_ `float HeightInfluence;`
- L16 _parameter_ `float HeightMultiplier;`
- L17 _parameter_ `float HeightMidPoint;`

#### Functions (1)

- L20-57 _function_ `float4 FSH_AdjustHexaplanarDisplacement (in float2 tile_uv : TEXCOORD0) : SV_Target0` — sv-semantics

### `Plugins/TextureGraph/Shaders/Layer/AdjustHexaplanarGeneric.usf` (Other)

- lines: 55; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L4 `../Placement_Projection.ush`

#### Macros (#define, 1)

- L7 `#define DEBUG_TILES 0` _[#if !defined(DEBUG_TILES)]_

#### Global resources (textures / buffers / samplers) (2)

- L10 _resource_ `Texture2DArray CombinedBlob;`
- L11 _resource_ `Texture2DArray DisplacementLayer;`

#### Global parameters (uniforms) (7)

- L13 _parameter_ `float2 VerticalAxisRotation;`
- L14 _parameter_ `float2 LateralAxisRotation;`
- L15 _parameter_ `float2 UVScaling;`
- L17 _parameter_ `float Radius;`
- L18 _parameter_ `float HeightInfluence;`
- L19 _parameter_ `float HeightMultiplier;` — Not used but keep for now
- L20 _parameter_ `float HeightMidPoint;`

#### Functions (1)

- L22-55 _function_ `float4 FSH_AdjustHexaplanarGeneric (in float2 tile_uv : TEXCOORD0) : SV_Target0` — sv-semantics

### `Plugins/TextureGraph/Shaders/Layer/AdjustHexaplanarNormal.usf` (Other)

- lines: 120; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L4 `/Plugin/TextureGraph/NormalsCommon.ush`, L50 `../Placement_Projection.ush`

#### Macros (#define, 1)

- L53 `#define DEBUG_TILES 0` _[#if !defined(DEBUG_TILES)]_

#### Global resources (textures / buffers / samplers) (2)

- L56 _resource_ `Texture2DArray CombinedBlob;`
- L57 _resource_ `Texture2DArray DisplacementLayer;`

#### Global parameters (uniforms) (7)

- L59 _parameter_ `float2 VerticalAxisRotation;`
- L60 _parameter_ `float2 LateralAxisRotation;`
- L61 _parameter_ `float2 UVScaling;`
- L63 _parameter_ `float Radius;`
- L64 _parameter_ `float HeightInfluence;`
- L65 _parameter_ `float HeightMultiplier;` — Not used but keep for now
- L66 _parameter_ `float HeightMidPoint;`

#### Functions (1)

- L68-120 _function_ `float4 FSH_AdjustHexaplanarNormals (in float2 tile_uv : TEXCOORD0) : SV_Target0` — sv-semantics

### `Plugins/TextureGraph/Shaders/Layer/AdjustNormals.usf` (Other)

- lines: 15; parse: all-branches
- includes: L2 `AdjustUVCommon.ush`, L3 `/Plugin/TextureGraph/NormalsCommon.ush`

#### Global resources (textures / buffers / samplers) (1)

- L5 _resource_ `Texture2D SourceTex;`

#### Global parameters (uniforms) (1)

- L6 _parameter_ `float Renormalize;`

#### Functions (1)

- L8-15 _function_ `float4 FSH_AdjustNormals(in float2 uv : TEXCOORD0) : SV_Target0` — sv-semantics

### `Plugins/TextureGraph/Shaders/Layer/AdjustUVCommon.ush` (Other)

- lines: 61; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L59 `/Plugin/TextureGraph/TiledFetch_Combined.ush`

#### Macros (#define, 6)

- L7 `#define FREEFORM 0` _[#if !defined(FREEFORM)]_
- L11 `#define TILING 0` _[#if !defined(TILING)]_
- L15 `#define CLAMP 0` _[#if !defined(CLAMP)]_
- L19 `#define WRAP 0` _[#if !defined(WRAP)]_
- L26 `#define CLAMP 1` _[#if FREEFORM]_
- L31 `#define WRAP 1` _[#if TILING]_
- L25 #undef `CLAMP`; L30 #undef `WRAP`

#### Functions (2)

- L37-50 _function_ `float4 AdjustDisplacement(float4 FinalDisplacement, float HeightMidPoint, float HeightMultiplier, float IsGreyscale)`
- L52-57 _function_ `float3 AdjustGeneric(float4 blob, float2 uv, float ClampMaskX, float ClampMaskY, float scaleX, float scaleY)`

### `Plugins/TextureGraph/Shaders/Layer/AdjustUVDisplacement.usf` (Other)

- lines: 54; parse: all-branches
- includes: L3 `AdjustUVCommon.ush`

#### Global resources (textures / buffers / samplers) (1)

- L5 _resource_ `Texture2DArray CombinedBlob;`

#### Global parameters (uniforms) (6)

- L6 _parameter_ `float RotateUV;`
- L7 _parameter_ `float Center;`
- L8 _parameter_ `float4 ScaleOffset;`
- L9 _parameter_ `float HeightMultiplier;`
- L10 _parameter_ `float HeightMidPoint;`
- L11 _parameter_ `float IsGreyscale;`

#### Functions (1)

- L13-53 _function_ `float4 FSH_AdjustUVDisplacement(in float2 uvSource : TEXCOORD0) : SV_Target0` — sv-semantics

### `Plugins/TextureGraph/Shaders/Layer/AdjustUVGeneric.usf` (Other)

- lines: 76; parse: all-branches
- includes: L2 `AdjustUVCommon.ush`, L3 `/Plugin/TextureGraph/TiledFetch_Combined.ush`

#### Macros (#define, 1)

- L6 `#define DEBUG_TILES 0` _[#if !defined(DEBUG_TILES)]_

#### Global resources (textures / buffers / samplers) (1)

- L14 _resource_ `Texture2DArray CombinedBlob;`

#### Global parameters (uniforms) (5)

- L9 _parameter_ `float RotateUV;`
- L10 _parameter_ `float Center;`
- L11 _parameter_ `float ClampMaskX;`
- L12 _parameter_ `float ClampMaskY;`
- L13 _parameter_ `float4 ScaleOffset;`

#### Functions (1)

- L16-76 _function_ `float4 FSH_AdjustUVGeneric(in float2 uvSource : TEXCOORD0) : SV_Target0` — sv-semantics

### `Plugins/TextureGraph/Shaders/Layer/AdjustUVNormals.usf` (Other)

- lines: 46; parse: all-branches
- includes: L2 `AdjustUVCommon.ush`, L3 `/Plugin/TextureGraph/NormalsCommon.ush`

#### Global resources (textures / buffers / samplers) (1)

- L5 _resource_ `Texture2DArray CombinedBlob;`

#### Global parameters (uniforms) (4)

- L6 _parameter_ `float RotateUV;`
- L7 _parameter_ `float Center;`
- L8 _parameter_ `float4 ScaleOffset;`
- L9 _parameter_ `float Renormalize;`

#### Functions (1)

- L11-46 _function_ `float4 FSH_AdjustUVNormals(in float2 uvSource : TEXCOORD0) : SV_Target0` — sv-semantics

### `Plugins/TextureGraph/Shaders/Layer/BlitSourceOffset.usf` (Other)

- lines: 12; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`

#### Global parameters (uniforms) (3)

- L4 _parameter_ `sampler Source;`
- L5 _parameter_ `float OffsetX;`
- L6 _parameter_ `float OffsetY;`

#### Functions (1)

- L8-12 _function_ `float4 FSH_BlitSourceOffset(in float2 uv : TEXCOORD0) : SV_Target0` — sv-semantics

### `Plugins/TextureGraph/Shaders/Layer/ChannelSourceFlat.usf` (Other)

- lines: 9; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`

#### Entry points (1)

- L6-9 _entry_ `float4 FSH_FlatColorTexture(in float2 uvSource : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_FlatColorTexture` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Expressions/T_FlatColorTexture.cpp:13)

#### Global parameters (uniforms) (1)

- L4 _parameter_ `float4 Color;`

### `Plugins/TextureGraph/Shaders/Layer/Layer_Displacement.usf` (Other)

- lines: 95; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L3 `/Plugin/TextureGraph/SamplerStates.ush`

#### Entry points (1)

- L67-94 _entry_ `float4 FSH_Displacement(in float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_LayerDisplacement` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Layer/T_Displacement.cpp:6)

#### Global resources (textures / buffers / samplers) (4)

- L5 _resource_ `Texture2D SourceTexture;`
- L6 _resource_ `Texture2D DestinationTexture;`
- L7 _resource_ `Texture2D Mask;`
- L8 _resource_ `Texture2D BlurredBase;`

#### Global parameters (uniforms) (7)

- L10 _parameter_ `float BorderThreshold;`
- L11 _parameter_ `float ReplaceHeight;`
- L12 _parameter_ `float ReplaceHeightMip;`
- L13 _parameter_ `float Opacity;`
- L14 _parameter_ `float ChannelOpacity;`
- L16 _parameter_ `float BorderFade;`
- L17 _parameter_ `float FromAbove;`

#### Functions (4)

- L19-37 _function_ `float LowFrequencyBlend(float mask, float map1, float map2, float radius, float flip)`
- L39-45 _function_ `float4 heightBlend(float4 input1, float4 height1, float4 input2, float4 height2)`
- L47-51 _function_ `float4 heightlerp(float4 input1, float4 height1, float4 input2, float4 height2, float t)`
- L53-64 _function_ `float MakeSoftMask(float newHeight, float oldHeight, float radius)`

### `Plugins/TextureGraph/Shaders/Layer/Layer_Normal.usf` (Other)

- lines: 92; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L3 `/Plugin/TextureGraph/SamplerStates.ush`

#### Entry points (1)

- L61-91 _entry_ `float4 FSH_Normal(in float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_LayerNormal` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Layer/T_Normal.cpp:7)

#### Global resources (textures / buffers / samplers) (5)

- L5 _resource_ `Texture2D Destination;`
- L6 _resource_ `Texture2D SourceTexture;`
- L7 _resource_ `Texture2D Mask;`
- L8 _resource_ `Texture2D BlurredBase;`
- L9 _resource_ `Texture2D NormalDiff;`

#### Global parameters (uniforms) (6)

- L11 _parameter_ `float Opacity;`
- L12 _parameter_ `float InvertX;`
- L13 _parameter_ `float InvertY;`
- L14 _parameter_ `float Strength;`
- L15 _parameter_ `float ReplaceHeightMip;`
- L16 _parameter_ `float ReplaceHeight;`

#### Functions (6)

- L19-22 _function_ `float3 PartialDerivatesBlend(float3 n1, float3 n2)`
- L24-29 _function_ `float3 PartialDerivatesTransition(float3 a, float3 b, float t)`
- L31-35 _function_ `float3 ReconstructNormalZ(float2 rg)`
- L37-40 _function_ `float3 ReconstructNormalZ(float3 rgb)`
- L43-49 _function_ `float3 ConformNormals(float3 inputNormals)`
- L52-59 _function_ `float3 FillBlackPixels01Range(float3 nm)` — if nothing is in red or green channel, return flat normal. Works on [0,1] space normals
