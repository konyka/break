# Shaders / Plugins/Experimental/DynamicWind/Shaders

- files: 1; lines: 265
- record kinds: cpp_binding=1, define=12, entry=1, function=6, include=6, parameter=7, resource=6

### `Plugins/Experimental/DynamicWind/Shaders/DynamicWindEval.usf` (Other)

- lines: 265; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`, L4 `/Engine/Private/BoneTransform.ush`, L5 `/Engine/Shared/SkinningDefinitions.h`, L6 `/Engine/Private/ComputeShaderUtils.ush`, L7 `/Engine/Private/Skinning/SkinningDataDecode.ush`, L9 `Shared/DynamicWindCommon.ush`

#### Macros (#define, 12)

- L12 `#define FORCE_IDENTITY_OUTPUT 0`
- L32 `#define DYNAMIC_WIND_SPEED_MOD 1.25f`
- L33 `#define DYNAMIC_WIND_AMPLITUDE_MOD 3.0f`
- L36 `#define DYNAMIC_WIND_BEND_OFFSET 0.1f`
- L39 `#define DYNAMIC_WIND_ALIGN_ATTENUATION 0.5f`
- L44 `#define DYNAMIC_WIND_HEIGHT_ATTENUATION 0.1f`
- L47 `#define DYNAMIC_WIND_TORSION_MOD 0.5f`
- L50 `#define DYNAMIC_WIND_LONG_BRANCH_SPEED_MOD 0.5f`
- L51 `#define DYNAMIC_WIND_LONG_BRANCH_MAX 500.0f`
- L52 `#define DYNAMIC_WIND_LONG_BRANCH_MIN 100.0f`
- L55 `#define DYNAMIC_WIND_GUST_SPEED_MIN 0.05f`
- L56 `#define DYNAMIC_WIND_GUST_SPEED_MAX 0.1f`

#### Entry points (1)

- L105-265 _entry_ `[numthreads(BONES_PER_GROUP, 1, 1)] void WindEvalCS(uint3 GroupId : SV_GroupID, uint GroupThreadIndex : SV_GroupIndex)` — stage: **compute** — C++: `FDynamicWindEvalCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/Experimental/DynamicWind/Source/DynamicWind/Private/DynamicWindProvider.cpp:124)

#### Global resources (textures / buffers / samplers) (6)

- L14 _resource_ `StructuredBuffer<FDynamicWindSkeletonData> SkeletonBuffer;`
- L15 _resource_ `StructuredBuffer<FDynamicWindBlockHeader> HeaderBuffer;`
- L16 _resource_ `ByteAddressBuffer BoneDataBuffer;`
- L17 _resource_ `ByteAddressBuffer BoneMapBuffer;`
- L19 _resource_ `Texture2D<float4> WindTexture;`
- L20 _resource_ `SamplerState WindSampler;`

#### Global parameters (uniforms) (7)

- L18 _parameter_ `FCompressedBoneTransformRWBuffer TransformBuffer;`
- L22 _parameter_ `float Time;`
- L23 _parameter_ `float DeltaTime;`
- L24 _parameter_ `float WindSpeed;`
- L25 _parameter_ `float WindAmplitude;`
- L26 _parameter_ `float3 WindDirection;`
- L27 _parameter_ `float4 Debug;`

#### Functions (6)

- L58-61 _function_ `uint GetBoneDataAddress(uint BoneDataOffset, uint BoneIndex)`
- L63-66 _function_ `float RemapValue(float Value, float InLow, float InHigh, float OutLow, float OutHigh)`
- L68-73 _function_ `FQuat QuatAttenuate(FQuat Q1, half Attenuation)`
- L75-93 _function_ `float WindFlow(const float RandomValue, const float Distance = 0.0f, const float BlendByGroup = 0.0f, const float ChainLength = 0.0f, float TrunkBlend = 0.0f)`
- L95-98 _function_ `float WindWave(float T)`
- L100-103 _function_ `float RampStrength(float X)`
