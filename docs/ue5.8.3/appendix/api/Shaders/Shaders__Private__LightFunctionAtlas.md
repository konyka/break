# Shaders / Shaders/Private/LightFunctionAtlas

- files: 2; lines: 238
- record kinds: cpp_binding=1, define=6, entry=1, function=4, include=5, member=6, parameter=2, struct=1

### `Shaders/Private/LightFunctionAtlas/LightFunctionAtlasCommon.usf` (Private)

- lines: 150; parse: all-branches
- includes: L9 `../Common.ush`, L10 `/Engine/Shared/LightDefinitions.h`

#### Macros (#define, 5)

- L17 `#define LightFunctionAtlas LightFunctionAtlasStruct` _[#if defined(LightFunctionAtlasStruct)]_
- L21 `#define FLightFunctionColor float3` _[#if COLORED_LIGHT_FUNCTION_ATLAS]_
- L23 `#define FLightFunctionColor float` _[#if !(COLORED_LIGHT_FUNCTION_ATLAS)]_
- L27 `#define LightFunctionAtlasSampler View.SharedBilinearClampedSampler` _[#if SUPPORTS_INDEPENDENT_SAMPLERS]_
- L29 `#define LightFunctionAtlasSampler LightFunctionAtlas.LightFunctionAtlasSampler` _[#if !(SUPPORTS_INDEPENDENT_SAMPLERS)]_
- L7 #pragma `once`; L16 #undef `LightFunctionAtlas`

#### Structs / classes (1)

- L32-40 _struct_ **`FLightFunctionSlotData`** `struct FLightFunctionSlotData`
  - L34 _member_ `uint LightType;`
  - L35 _member_ `float DisabledBrightness;`
  - L36 _member_ `float FadeDistance;`
  - L37 _member_ `float TanOuterAngle;`
  - L38 _member_ `float2 MinUV;`
  - L39 _member_ `float4x4 TranslatedWorldToLight;`

#### Functions (4)

- L42-64 _function_ `FLightFunctionSlotData GetLightFunctionSlotData(uint LightFunctionAtlasLightIndex)`
- L66-78 _function_ `FLightFunctionColor SampleLightFunctionSlot(FLightFunctionSlotData Slot, float2 LightFunctionUV)`
- L80-92 _function_ `FLightFunctionColor ApplyLightFunctionFade(float3 TranslatedWorldPosition, FLightFunctionSlotData Slot, FLightFunctionColor LightFunctionColor)`
- L94-150 _function_ `FLightFunctionColor GetLocalLightFunctionCommon(float3 TranslatedWorldPosition, uint LightFunctionAtlasLightIndex)`

### `Shaders/Private/LightFunctionAtlas/LightFunctionAtlasRender.usf` (Private)

- lines: 88; parse: all-branches
- includes: L13 `../Common.ush`, L14 `/Engine/Generated/Material.ush`, L15 `../LightFunctionCommon.ush`

#### Macros (#define, 1)

- L8 `#define LIGHT_FUNCTION_ATLAS 1`
- L11 #pragma `message("UESHADERMETADATA_VERSION D13B08DE-2E66-447C-AF33-27D896D280CA")`

#### Entry points (1)

- L20-87 _entry_ `void Main( in noperspective float4 UV : TEXCOORD0, in FStereoPSInput StereoInput, in float4 SvPosition : SV_Position, out float4 OutColor : SV_Target0 )` — stage: **pixel (from C++ binding)** — C++: `FLightFunctionAtlasSlotPS` SF_Pixel via IMPLEMENT_MATERIAL_SHADER_TYPE (Source/Runtime/Renderer/Private/LightFunctionAtlas.cpp:210)

#### Global parameters (uniforms) (2)

- L17 _parameter_ `float2 LightFunctionTexelSize;`
- L18 _parameter_ `float4 SvPositionToUVScaleBias;`
