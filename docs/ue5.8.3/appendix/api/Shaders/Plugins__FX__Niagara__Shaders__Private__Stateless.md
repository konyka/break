# Shaders / Plugins/FX/Niagara/Shaders/Private/Stateless

- files: 3; lines: 368
- record kinds: cpp_binding=1, define=12, function=57, include=27, macro_call=1, parameter=2, resource=4, static_var=1

### `Plugins/FX/Niagara/Shaders/Private/Stateless/NiagaraStatelessCommon.ush` (Private)

- lines: 189; parse: all-branches
- includes: L4 `/Engine/Private/Common.ush`, L5 `/Engine/Private/Random.ush`, L7 `/Plugin/FX/Niagara/Shared/NiagaraStatelessDefinitions.h`, L8 `/Plugin/FX/Niagara/Shared/NiagaraStatelessBuiltDistribution.h`, L9 `/Plugin/FX/Niagara/Private/NiagaraQuaternionUtils.ush`, L188 `/Plugin/FX/Niagara/Private/Stateless/NiagaraStatelessDistribution.ush`

#### Macros (#define, 9)

- L13 `#define INVALID_COMPONENT -1`
- L14 `#define UE_SMALL_NUMBER (1.e-8f)`
- L15 `#define UE_KINDA_SMALL_NUMBER (1.e-4f)`
- L16 `#define UE_PI (3.1415926535897932f)`
- L17 `#define UE_INV_PI (0.31830988618f)`
- L18 `#define UE_HALF_PI (1.57079632679f)`
- L19 `#define UE_TWO_PI (6.28318530717f)`
- L20 `#define UE_PI_SQUARED (9.86960440108f)`
- L21 `#define UE_DEG_TO_RAD (UE_PI / 180.0f)`
- L2 #pragma `once`

#### Global resources (textures / buffers / samplers) (4)

- L30 _resource_ `RWBuffer<float> Common_FloatOutputBuffer;`
- L31 _resource_ `RWBuffer<int> Common_IntOutputBuffer;`
- L32 _resource_ `ByteAddressBuffer Common_StaticDataBuffer;`
- L33 _resource_ `ByteAddressBuffer Common_DynamicDataBuffer;`

#### Global parameters (uniforms) (2)

- L28 _parameter_ `float4 Common_ToSimulationRotations[3];`
- L29 _parameter_ `uint Common_OutputBufferStride;`

#### static variables (1)

- L73 _static_var_ `static uint4 GRandomSeedInternal;`

#### Functions (57)

- L23-26 _function_ `bool IsValidComponent(int ComponentOffset)`
- L37-40 _function_ `float4 GetToSimulationRotation(int SourceSpace)`
- L44-49 _function_ `float2 SinCos(float v)`
- L51-55 _function_ `float2 SafeNormalize(float2 v, float2 Fallback)`
- L57-60 _function_ `float2 SafeNormalize(float2 v)`
- L62-66 _function_ `float3 SafeNormalize(float3 v, float3 Fallback)`
- L68-71 _function_ `float3 SafeNormalize(float3 v)`
- L75-79 _function_ `uint4 RandomUInt4(uint RandomSeedOffset)`
- L80 _function_ `uint RandomUInt(uint RandomSeedOffset)`
- L81 _function_ `uint2 RandomUInt2(uint RandomSeedOffset)`
- L82 _function_ `uint3 RandomUInt3(uint RandomSeedOffset)`
- L84-88 _function_ `float4 RandomFloat4(uint RandomSeedOffset)`
- L89 _function_ `float RandomFloat(uint RandomSeedOffset)`
- L90 _function_ `float2 RandomFloat2(uint RandomSeedOffset)`
- L91 _function_ `float3 RandomFloat3(uint RandomSeedOffset)`
- L93 _function_ `float RandomRangeFloat(uint RandomSeedOffset, float Min, float Max)`
- L94 _function_ `float2 RandomRangeFloat(uint RandomSeedOffset, float2 Min, float2 Max)`
- L95 _function_ `float3 RandomRangeFloat(uint RandomSeedOffset, float3 Min, float3 Max)`
- L96 _function_ `float4 RandomRangeFloat(uint RandomSeedOffset, float4 Min, float4 Max)`
- L98 _function_ `float RandomScaleBiasFloat(uint RandomSeedOffset, float Scale, float Bias)`
- L99 _function_ `float2 RandomScaleBiasFloat(uint RandomSeedOffset, float2 Scale, float2 Bias)`
- L100 _function_ `float3 RandomScaleBiasFloat(uint RandomSeedOffset, float3 Scale, float3 Bias)`
- L101 _function_ `float4 RandomScaleBiasFloat(uint RandomSeedOffset, float4 Scale, float4 Bias)`
- L103 _function_ `float RandomScaleBiasFloat(uint RandomSeedOffset, float Scale, float Bias, bool bUniform)`
- L104 _function_ `float2 RandomScaleBiasFloat(uint RandomSeedOffset, float2 Scale, float2 Bias, bool bUniform)`
- L105 _function_ `float3 RandomScaleBiasFloat(uint RandomSeedOffset, float3 Scale, float3 Bias, bool bUniform)`
- L106 _function_ `float4 RandomScaleBiasFloat(uint RandomSeedOffset, float4 Scale, float4 Bias, bool bUniform)`
- L108 _function_ `float2 RandomUnitFloat2(uint RandomSeedOffset)`
- L109 _function_ `float3 RandomUnitFloat3(uint RandomSeedOffset)`
- L111 _function_ `uint GetStaticUInt (int BaseOffset, int Element)`
- L112 _function_ `int GetStaticInt (int BaseOffset, int Element)`
- L113 _function_ `float GetStaticFloat (int BaseOffset, int Element)`
- L114 _function_ `float2 GetStaticFloat2(int BaseOffset, int Element)`
- L115 _function_ `float3 GetStaticFloat3(int BaseOffset, int Element)`
- L116 _function_ `float4 GetStaticFloat4(int BaseOffset, int Element)`
- L118 _function_ `uint GetParameterBufferUint (int BaseOffset, int Element)`
- L119 _function_ `int GetParameterBufferInt (int BaseOffset, int Element)`
- L120 _function_ `float GetParameterBufferFloat (int BaseOffset, int Element)`
- L121 _function_ `float2 GetParameterBufferFloat2(int BaseOffset, int Element)`
- L122 _function_ `float3 GetParameterBufferFloat3(int BaseOffset, int Element)`
- L123 _function_ `float4 GetParameterBufferFloat4(int BaseOffset, int Element)`
- L125 _function_ `uint GetParameterBufferUint (int BaseOffset, int Element, uint DefaultValue)`
- L126 _function_ `int GetParameterBufferInt (int BaseOffset, int Element, int DefaultValue)`
- L127 _function_ `float GetParameterBufferFloat (int BaseOffset, int Element, float DefaultValue)`
- L128 _function_ `float2 GetParameterBufferFloat2(int BaseOffset, int Element, float2 DefaultValue)`
- L129 _function_ `float3 GetParameterBufferFloat3(int BaseOffset, int Element, float3 DefaultValue)`
- L130 _function_ `float4 GetParameterBufferFloat4(int BaseOffset, int Element, float4 DefaultValue)`
- L132 _function_ `float StatelessLerp(float lhs, float rhs, float u, bool bUniform)`
- L133 _function_ `float2 StatelessLerp(float2 lhs, float2 rhs, float2 u, bool bUniform)`
- L134 _function_ `float3 StatelessLerp(float3 lhs, float3 rhs, float3 u, bool bUniform)`
- L135 _function_ `float4 StatelessLerp(float4 lhs, float4 rhs, float4 u, bool bUniform)`
- L137-140 _function_ `uint GetComponentOffset(uint OutputIndex, int ComponentOffset)`
- L142-148 _function_ `void OutputComponentData(uint OutputIndex, int ComponentOffset, float Value)`
- L150-157 _function_ `void OutputComponentData(uint OutputIndex, int ComponentOffset, float2 Value)`
- L159-167 _function_ `void OutputComponentData(uint OutputIndex, int ComponentOffset, float3 Value)`
- L169-178 _function_ `void OutputComponentData(uint OutputIndex, int ComponentOffset, float4 Value)`
- L180-186 _function_ `void OutputComponentData(uint OutputIndex, int ComponentOffset, int Value)`

### `Plugins/FX/Niagara/Shaders/Private/Stateless/NiagaraStatelessDistribution.ush` (Private)

- lines: 84; parse: all-branches

#### Macros (#define, 1)

- L4 `#define SAMPLEFUNC(HLSLTYPE, HLSLPAIRTYPE, NAMETYPE) HLSLPAIRTYPE Private_GetDistributionTableValues##NAMETYPE##(FNiagaraStatelessBuiltDistributionType BuiltData, uint IndexA, uint IndexB) { const uint BaseOffset = FNiagaraStatelessBuiltDistribution::Ge ...` (73 lines)
- L2 #pragma `once`; L83 #undef `READFUNCS`

#### Top-level macro invocations (1)

- L78-84 _macro_call_ `SAMPLEFUNC(float, float2, Float) SAMPLEFUNC(float2, float2x2, Float2) SAMPLEFUNC(float3, float2x3, Float3) SAMPLEFUNC(float4, float2x4, Float4)`

### `Plugins/FX/Niagara/Shaders/Private/Stateless/NiagaraStatelessSimulationDefault.usf` (Private)

- lines: 95; parse: all-branches
- includes: L3 `/Plugin/FX/Niagara/Private/NiagaraQuaternionUtils.ush`, L4 `/Plugin/FX/Niagara/Private/Stateless/NiagaraStatelessCommon.ush`, L72 `/Plugin/FX/Niagara/Private/Stateless/Template/GenerateCS_PreModules.ush`, L75 `/Plugin/FX/Niagara/Private/Stateless/Modules/NiagaraStatelessModule_CameraOffset.ush`, L76 `/Plugin/FX/Niagara/Private/Stateless/Modules/NiagaraStatelessModule_DynamicMaterialParameters.ush`, L77 `/Plugin/FX/Niagara/Private/Stateless/Modules/NiagaraStatelessModule_InitializeParticle.ush`, L78 `/Plugin/FX/Niagara/Private/Stateless/Modules/NiagaraStatelessModule_InitialMeshOrientation.ush`, L79 `/Plugin/FX/Niagara/Private/Stateless/Modules/NiagaraStatelessModule_MeshIndex.ush`, L80 `/Plugin/FX/Niagara/Private/Stateless/Modules/NiagaraStatelessModule_MeshRotationRate.ush`, L82 `/Plugin/FX/Niagara/Private/Stateless/Modules/NiagaraStatelessModule_ShapeLocation.ush`, L83 `/Plugin/FX/Niagara/Private/Stateless/Modules/NiagaraStatelessModule_ScaleColor.ush`, L84 `/Plugin/FX/Niagara/Private/Stateless/Modules/NiagaraStatelessModule_ScaleRibbonWidth.ush`, L85 `/Plugin/FX/Niagara/Private/Stateless/Modules/NiagaraStatelessModule_ScaleSpriteSize.ush`, L86 `/Plugin/FX/Niagara/Private/Stateless/Modules/NiagaraStatelessModule_ScaleSpriteSizeBySpeed.ush`, L87 `/Plugin/FX/Niagara/Private/Stateless/Modules/NiagaraStatelessModule_ScaleMeshSize.ush`, L88 `/Plugin/FX/Niagara/Private/Stateless/Modules/NiagaraStatelessModule_ScaleMeshSizeBySpeed.ush`, L89 `/Plugin/FX/Niagara/Private/Stateless/Modules/NiagaraStatelessModule_SolveVelocitiesAndForces.ush`, L90 `/Plugin/FX/Niagara/Private/Stateless/Modules/NiagaraStatelessModule_SpriteFacingAndAlignment.ush`, L91 `/Plugin/FX/Niagara/Private/Stateless/Modules/NiagaraStatelessModule_SpriteRotationRate.ush`, L92 `/Plugin/FX/Niagara/Private/Stateless/Modules/NiagaraStatelessModule_SubUVAnimation.ush`, L94 `/Plugin/FX/Niagara/Private/Stateless/Template/GenerateCS_PostModules.ush`

#### Macros (#define, 2)

- L10 `#define PARTICLE_ATTRIBUTES PARTICLE_ATTRIBUTE_OUTPUT_IMPLICIT(int, UniqueID) PARTICLE_ATTRIBUTE_OUTPUT_IMPLICIT(float, MaterialRandom) PARTICLE_ATTRIBUTE_OUTPUT(float3, Position) PARTICLE_ATTRIBUTE_OUTPUT(float, CameraOffset) P ...` (31 lines)
- L42 `#define PARTICLE_MODULES PARTICLE_MODULE(InitializeParticle) PARTICLE_MODULE(InitialMeshOrientation) PARTICLE_MODULE(ShapeLocation) PARTICLE_MODULE(Null) PARTICLE_MODULE(Null) PARTICLE_MODULE(Null) PARTICLE_MODULE(Null) PARTI ...` (30 lines)

#### C++ shader bindings (IMPLEMENT_* naming this file, 1)

- `StatelessMain` → entry not found in file (macro-generated or #include'd); C++ `FSimulationShaderDefaultCS` SF_Compute via IMPLEMENT_GLOBAL_SHADER (Plugins/FX/Niagara/Source/NiagaraShader/Private/Stateless/NiagaraStatelessEmitterShaders.cpp:7)
