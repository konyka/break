# Shaders / Plugins/TextureGraph/Shaders/Mask

- files: 9; lines: 843
- record kinds: cpp_binding=13, define=29, entry=8, function=11, include=25, parameter=63, resource=24

### `Plugins/TextureGraph/Shaders/Mask/CombineDisplacementAndWorldPos.usf` (Other)

- lines: 33; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L3 `../ShaderUtil.ush`, L4 `/Plugin/TextureGraph/SamplerStates.ush`

#### Entry points (1)

- L17-32 _entry_ `float4 FSH_CombineDisplacementAndWorldPos(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_CombineDisplacementAndWorldPos` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Mask/T_PositionGradientMask.cpp:8)

#### Global resources (textures / buffers / samplers) (5)

- L6 _resource_ `Texture2D SourceDisplacement;`
- L7 _resource_ `Texture2D WorldPos;`
- L8 _resource_ `Texture2D WorldNormals;`
- L9 _resource_ `Texture2D WorldUVMask;`
- L10 _resource_ `Texture2D MinMaxTex;`

#### Global parameters (uniforms) (4)

- L11 _parameter_ `float MidPoint;`
- L12 _parameter_ `float StandardHeight;`
- L13 _parameter_ `float4 MeshBoundsMin;`
- L14 _parameter_ `float4 MeshBoundsSize;`

### `Plugins/TextureGraph/Shaders/Mask/ImageMask.usf` (Other)

- lines: 48; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L3 `/Plugin/TextureGraph/SamplerStates.ush`

#### Macros (#define, 2)

- L5 `#define NORMALIZE 0` _[#if !defined(NORMALIZE)]_
- L9 `#define INVERT 0` _[#if !defined(INVERT)]_

#### Entry points (1)

- L19-47 _entry_ `float4 FSH_ImageMask(in float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_ImageMask` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Mask/T_ImageMask.cpp:7)

#### Global resources (textures / buffers / samplers) (2)

- L14 _resource_ `Texture2D SourceTexture;`
- L15 _resource_ `Texture2D MinMax;`

#### Global parameters (uniforms) (2)

- L16 _parameter_ `float RangeMin;`
- L17 _parameter_ `float RangeMax;`

### `Plugins/TextureGraph/Shaders/Mask/LayerMask.usf` (Other)

- lines: 128; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L3 `/Plugin/TextureGraph/SamplerStates.ush`

#### Macros (#define, 8)

- L8 `#define FROMABOVE 0` _[#if !defined(FROMABOVE)]_
- L11 `#define HEIGHTMASK 0` _[#if !defined(HEIGHTMASK)]_
- L14 `#define DETAILS 0` _[#if !defined(DETAILS)]_
- L17 `#define MATERIALID 0` _[#if !defined(MATERIALID)]_
- L20 `#define PAINTMASK 0` _[#if !defined(PAINTMASK)]_
- L23 `#define UVMASK 0` _[#if !defined(UVMASK)]_
- L26 `#define OPACITY 0` _[#if !defined(OPACITY)]_
- L29 `#define MASKSTACK 0` _[#if !defined(MASKSTACK)]_

#### Entry points (1)

- L67-127 _entry_ `float4 FSH_LayerMask(in float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_LayerMask` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Layer/T_LayerMask.cpp:13)

#### Global resources (textures / buffers / samplers) (9)

- L51 _resource_ `Texture2D Displacement;` — Current layer adjusted displacement map
- L52 _resource_ `Texture2D OldDisplacement;` — Previous layer displacement map
- L53 _resource_ `Texture2D Occlusion;` — Current layer adjusted occlusion map
- L54 _resource_ `Texture2D OldOcclusion;` — Previous layer occlusion map
- L55 _resource_ `Texture2D OpacityChannel;` — Current layer adjusted opacity channel map
- L57 _resource_ `Texture2D MaskStack;` — Mask stack map from current layer
- L58 _resource_ `Texture2D UVMask;` — UVMask map for target set
- L59 _resource_ `Texture2D PaintMask;` — Paint mask map from layer
- L60 _resource_ `Texture2D MaterialID;` — Material ID map for target set

#### Global parameters (uniforms) (4)

- L62 _parameter_ `float PreserveDetails;`
- L63 _parameter_ `float BorderFade;`
- L64 _parameter_ `float BorderThreshold;`
- L65 _parameter_ `float Opacity;`

#### Functions (2)

- L32-41 _function_ `float MakeSoftMask(float newHeight, float oldHeight, float radius)`
- L43-49 _function_ `float MakeDetailMask(float softMask, float layerAO, float oldAO, float detailAmount)` — This function will likely be based on something other than ao when we skip ao channels per layer

### `Plugins/TextureGraph/Shaders/Mask/MaskModifier.usf` (Other)

- lines: 124; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L28 `/Plugin/TextureGraph/TiledFetch_Combined.ush`

#### Macros (#define, 6)

- L5 `#define BRIGHTNESS_MODIFIER 0` _[#if !defined(BRIGHTNESS_MODIFIER)]_
- L9 `#define CLAMP_MODIFIER 0` _[#if !defined(CLAMP_MODIFIER)]_
- L13 `#define INVERT_MODIFIER 0` _[#if !defined(INVERT_MODIFIER)]_
- L17 `#define NORMALIZE_MODIFIER 0` _[#if !defined(NORMALIZE_MODIFIER)]_
- L21 `#define GRADIENT_REMAP_MODIFIER 0` _[#if !defined(GRADIENT_REMAP_MODIFIER)]_
- L25 `#define POSTERIZE_MODIFIER 0` _[#if !defined(POSTERIZE_MODIFIER)]_

#### Entry points (1)

- L68-123 _entry_ `float4 FSH_MaskModifier(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_BrightnessMaskModifier` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Mask/T_MaskModifier.cpp:6) — C++: `FSH_ClampMaskModifier` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Mask/T_MaskModifier.cpp:7) — C++: `FSH_InvertMaskModifier` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Mask/T_MaskModifier.cpp:8) — C++: `FSH_NormalizeMaskModifier` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Mask/T_MaskModifier.cpp:9) — C++: `FSH_GradientRemapMaskModifier` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Mask/T_MaskModifier.cpp:10) — C++: `FSH_PosterizeMaskModifier` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Mask/T_MaskModifier.cpp:11)

#### Global resources (textures / buffers / samplers) (3)

- L30 _resource_ `Texture2D SourceTexture;`
- L35 _resource_ `Texture2D MinMaxTexture;` _[#if BRIGHTNESS_MODIFIER]_
- L44 _resource_ `Texture2D MinMaxTexture;` _[#if NORMALIZE_MODIFIER]_

#### Global parameters (uniforms) (10)

- L33 _parameter_ `float Brightness;` _[#if BRIGHTNESS_MODIFIER]_
- L34 _parameter_ `float Contrast;` _[#if BRIGHTNESS_MODIFIER]_
- L39 _parameter_ `float ClampMin;` _[#if CLAMP_MODIFIER]_
- L40 _parameter_ `float ClampMax;` _[#if CLAMP_MODIFIER]_
- L48 _parameter_ `float RangeMin;` _[#if GRADIENT_REMAP_MODIFIER]_
- L49 _parameter_ `float RangeMax;` _[#if GRADIENT_REMAP_MODIFIER]_
- L50 _parameter_ `int Repeat;` _[#if GRADIENT_REMAP_MODIFIER]_
- L51 _parameter_ `float Curve;` _[#if GRADIENT_REMAP_MODIFIER]_
- L52 _parameter_ `int Mirror;` _[#if GRADIENT_REMAP_MODIFIER]_
- L64 _parameter_ `int StepCount;` _[#if POSTERIZE_MODIFIER]_

#### Functions (1)

- L54-60 _function_ `float SimpleCurve(float input, float curve)` _[#if GRADIENT_REMAP_MODIFIER]_

### `Plugins/TextureGraph/Shaders/Mask/MaskUtil.usf` (Other)

- lines: 21; parse: all-branches

#### Functions (2)

- L2-11 _function_ `float MakeSoftMask(float newHeight, float oldHeight, float radius)`
- L13-19 _function_ `float MakeDetailMask(float softMask, float layerAO, float oldAO, float detailAmount)` — This function will likely be based on something other than ao when we skip ao channels per layer

### `Plugins/TextureGraph/Shaders/Mask/NoiseMask.usf` (Other)

- lines: 69; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L10 `/Engine/Public/Platform.ush`, L11 `/Plugin/TextureGraph/TileInfo.ush`, L18 `/Plugin/TextureGraph/Noise/Noise_Simplex.ush` [NOISE_TYPE == NOISE_SIMPLEX], L20 `/Plugin/TextureGraph/Noise/Noise_Perlin.ush` [!(NOISE_TYPE == NOISE_SIMPLEX) && NOISE_TYPE == NOISE_PERLIN], L22 `/Plugin/TextureGraph/Noise/Noise_Voronoise.ush` [!(NOISE_TYPE == NOISE_SIMPLEX) && !(NOISE_TYPE == NOISE_PERLIN)]

#### Macros (#define, 6)

- L4 `#define NOISE_SIMPLEX 0`
- L5 `#define NOISE_PERLIN 1`
- L6 `#define NOISE_WORLEY1 2`
- L7 `#define NOISE_WORLEY2 3`
- L8 `#define NOISE_WORLEY3 4`
- L14 `#define NOISE_TYPE NOISE_SIMPLEX` _[#if !defined(NOISE_TYPE)]_

#### Entry points (1)

- L35-68 _entry_ `float4 FSH_NoiseMask(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_NoiseMask` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Mask/T_NoiseMask.cpp:11)

#### Global parameters (uniforms) (8)

- L25 _parameter_ `int NoiseType;`
- L27 _parameter_ `float Seed;`
- L28 _parameter_ `float Amplitude;`
- L29 _parameter_ `float Frequency;`
- L30 _parameter_ `int Octaves;`
- L31 _parameter_ `float Lacunarity;`
- L32 _parameter_ `float Persistance;`
- L33 _parameter_ `float Invert;`

### `Plugins/TextureGraph/Shaders/Mask/NormalMask.usf` (Other)

- lines: 55; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L3 `../ShaderUtil.ush`, L4 `/Plugin/TextureGraph/SamplerStates.ush`

#### Macros (#define, 1)

- L8 `#define THREE_DIMESIONS 0` _[#if !defined(THREE_DIMESIONS)]_

#### Entry points (1)

- L22-54 _entry_ `float4 FSH_NormalMask(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_NormalMask` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Mask/T_NormalMask.cpp:6)

#### Global resources (textures / buffers / samplers) (3)

- L11 _resource_ `Texture2D SourceTex;`
- L12 _resource_ `Texture2D MeshNormals;`
- L13 _resource_ `Texture2D MeshTangents;`

#### Global parameters (uniforms) (7)

- L14 _parameter_ `float Range;`
- L15 _parameter_ `float Radius;`
- L16 _parameter_ `float DirectionX;`
- L17 _parameter_ `float DirectionY;`
- L18 _parameter_ `float DirectionZ;`
- L19 _parameter_ `int ObjectSpace;`
- L20 _parameter_ `float4x4 LocalToWorldMatrix;`

### `Plugins/TextureGraph/Shaders/Mask/PatternMask.usf` (Other)

- lines: 262; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L5 `/Plugin/TextureGraph/TileInfo.ush`, L6 `/Plugin/TextureGraph/ShaderUtil.ush`

#### Macros (#define, 5)

- L8 `#define PATTERN_SQUARE 0`
- L9 `#define PATTERN_CIRCLE 1`
- L10 `#define PATTERN_CHECKER 2`
- L11 `#define PATTERN_GRADIENT 3`
- L14 `#define PATTERN_TYPE PATTERN_SQUARE` _[#if !defined(PATTERN_TYPE)]_

#### Entry points (1)

- L121-261 _entry_ `float4 FSH_PatternMask(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_PatternMask` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Mask/T_PatternMask.cpp:15)

#### Global parameters (uniforms) (21)

- L17 _parameter_ `float2 Repeat;`
- L18 _parameter_ `float2 Spacing;`
- L19 _parameter_ `float2 Offset;`
- L20 _parameter_ `float Invert;`
- L21 _parameter_ `int PatternType;`
- L24 _parameter_ `float Bevel;` — Bevel
- L25 _parameter_ `float BevelCurve;`
- L28 _parameter_ `float JS_Amount;` — Size Jitter Variables
- L29 _parameter_ `float JS_Threshold;`
- L30 _parameter_ `int JS_Seed;`
- L33 _parameter_ `float JB_Amount;` — Brightness Jitter Variables
- L34 _parameter_ `float JB_Threshold;`
- L35 _parameter_ `int JB_Seed;`
- L38 _parameter_ `float2 JT_Amount;` — Tilt Jitter Variables
- L39 _parameter_ `float JT_Threshold;`
- L40 _parameter_ `int JT_Seed;`
- L43 _parameter_ `float2 JA_Amount;` — Angle Jitter Variables
- L44 _parameter_ `int JA_Seed;`
- L47 _parameter_ `float CO_Threshold;` — Cut off
- L48 _parameter_ `int CO_Seed;`
- L51 _parameter_ `float2 GradientDir;` — Gradient

#### Functions (6)

- L53-58 _function_ `float2 GetAddedOffset(float2 uv, float2 tiles, float2 offsets)`
- L61-66 _function_ `float ApplyBevel(float value, float bevel, float curve)`
- L68-76 _function_ `float GetSizeJitter(float2 jitterUVs)`
- L78-85 _function_ `float GetBrightnessJitter(float2 jitterUVs)`
- L87-105 _function_ `float GetAngleTiltJitter(float2 jitterUVs, float2 pattern_cell_uv)`
- L106-119 _function_ `float2 StretchCompensation(float tx, float ty, float sx, float sy, float2 spacingApplied)`

### `Plugins/TextureGraph/Shaders/Mask/PositionGradientMask.usf` (Other)

- lines: 103; parse: all-branches
- includes: L2 `/Engine/Public/Platform.ush`, L3 `/Plugin/TextureGraph/SamplerStates.ush`, L4 `/Plugin/TextureGraph/TileInfo.ush`, L5 `/Plugin/TextureGraph/ShaderUtil.ush`

#### Macros (#define, 1)

- L9 `#define THREE_DIMESIONS 0` _[#if !defined(THREE_DIMESIONS)]_

#### Entry points (1)

- L22-102 _entry_ `float4 FSH_PositionGradientMask(float2 uv : TEXCOORD0) : SV_Target0` — stage: **pixel (from C++ binding)** — C++: `FSH_PositionGradientMask` SF_Pixel via IMPLEMENT_GLOBAL_SHADER (Plugins/TextureGraph/Source/TextureGraphEngine/Transform/Mask/T_PositionGradientMask.cpp:7)

#### Global resources (textures / buffers / samplers) (2)

- L12 _resource_ `Texture2D SourceTex;`
- L13 _resource_ `Texture2D MinMaxTex;`

#### Global parameters (uniforms) (7)

- L14 _parameter_ `float Falloff;`
- L15 _parameter_ `float StartingOffset;`
- L16 _parameter_ `float DirectionX;` — X is forward
- L17 _parameter_ `float DirectionY;` — Y is right
- L18 _parameter_ `float DirectionZ;` — Z is up
- L19 _parameter_ `float4 RelativeBoundsMin;`
- L20 _parameter_ `float4 RelativeBoundsMax;`
