# Shaders / Plugins/FX/Niagara/Shaders/Private/Stateless/Modules

- files: 19; lines: 676
- record kinds: function=23, member=10, parameter=118, resource=1, static_const=2, struct=2

### `Plugins/FX/Niagara/Shaders/Private/Stateless/Modules/NiagaraStatelessModule_CalculateAccurateVelocity.ush` (Private)

- lines: 8; parse: all-branches

#### Functions (1)

- L3-7 _function_ `void CalculateAccurateVelocity_Simulate(inout FStatelessParticle Particle)`

### `Plugins/FX/Niagara/Shaders/Private/Stateless/Modules/NiagaraStatelessModule_CameraOffset.ush` (Private)

- lines: 15; parse: all-branches

#### Global parameters (uniforms) (2)

- L3 _parameter_ `FNiagaraStatelessBuiltDistributionType CameraOffset_Distribution;`
- L4 _parameter_ `float CameraOffset_Scale;`

#### Functions (1)

- L6-14 _function_ `void CameraOffset_Simulate(inout FStatelessParticle Particle)`

### `Plugins/FX/Niagara/Shaders/Private/Stateless/Modules/NiagaraStatelessModule_DynamicMaterialParameters.ush` (Private)

- lines: 60; parse: all-branches

#### Global parameters (uniforms) (17)

- L3 _parameter_ `uint DynamicMaterialParameters_ChannelMask;`
- L4 _parameter_ `FNiagaraStatelessBuiltDistributionType DynamicMaterialParameters_Parameter0X;`
- L5 _parameter_ `FNiagaraStatelessBuiltDistributionType DynamicMaterialParameters_Parameter0Y;`
- L6 _parameter_ `FNiagaraStatelessBuiltDistributionType DynamicMaterialParameters_Parameter0Z;`
- L7 _parameter_ `FNiagaraStatelessBuiltDistributionType DynamicMaterialParameters_Parameter0W;`
- L8 _parameter_ `FNiagaraStatelessBuiltDistributionType DynamicMaterialParameters_Parameter1X;`
- L9 _parameter_ `FNiagaraStatelessBuiltDistributionType DynamicMaterialParameters_Parameter1Y;`
- L10 _parameter_ `FNiagaraStatelessBuiltDistributionType DynamicMaterialParameters_Parameter1Z;`
- L11 _parameter_ `FNiagaraStatelessBuiltDistributionType DynamicMaterialParameters_Parameter1W;`
- L12 _parameter_ `FNiagaraStatelessBuiltDistributionType DynamicMaterialParameters_Parameter2X;`
- L13 _parameter_ `FNiagaraStatelessBuiltDistributionType DynamicMaterialParameters_Parameter2Y;`
- L14 _parameter_ `FNiagaraStatelessBuiltDistributionType DynamicMaterialParameters_Parameter2Z;`
- L15 _parameter_ `FNiagaraStatelessBuiltDistributionType DynamicMaterialParameters_Parameter2W;`
- L16 _parameter_ `FNiagaraStatelessBuiltDistributionType DynamicMaterialParameters_Parameter3X;`
- L17 _parameter_ `FNiagaraStatelessBuiltDistributionType DynamicMaterialParameters_Parameter3Y;`
- L18 _parameter_ `FNiagaraStatelessBuiltDistributionType DynamicMaterialParameters_Parameter3Z;`
- L19 _parameter_ `FNiagaraStatelessBuiltDistributionType DynamicMaterialParameters_Parameter3W;`

#### Functions (1)

- L21-59 _function_ `void DynamicMaterialParameters_Simulate(inout FStatelessParticle Particle)`

### `Plugins/FX/Niagara/Shaders/Private/Stateless/Modules/NiagaraStatelessModule_InitialMeshOrientation.ush` (Private)

- lines: 12; parse: all-branches

#### Global parameters (uniforms) (2)

- L3 _parameter_ `float3 InitialMeshOrientation_RotationScale;`
- L4 _parameter_ `float3 InitialMeshOrientation_RotationBias;`

#### Functions (1)

- L6-11 _function_ `void InitialMeshOrientation_Simulate(inout FStatelessParticle Particle)`

### `Plugins/FX/Niagara/Shaders/Private/Stateless/Modules/NiagaraStatelessModule_InitializeParticle.ush` (Private)

- lines: 38; parse: all-branches

#### Global parameters (uniforms) (11)

- L6 _parameter_ `uint InitializeParticle_ModuleFlags;`
- L7 _parameter_ `FNiagaraStatelessBuiltDistributionType InitializeParticle_InitialPosition;`
- L8 _parameter_ `FNiagaraStatelessBuiltDistributionType InitializeParticle_InitialColor;`
- L9 _parameter_ `float2 InitializeParticle_SpriteSizeScale;`
- L10 _parameter_ `float2 InitializeParticle_SpriteSizeBias;`
- L11 _parameter_ `float InitializeParticle_SpriteRotationScale;`
- L12 _parameter_ `float InitializeParticle_SpriteRotationBias;`
- L14 _parameter_ `float3 InitializeParticle_MeshScaleScale;`
- L15 _parameter_ `float3 InitializeParticle_MeshScaleBias;`
- L17 _parameter_ `float InitializeParticle_RibbonWidthScale;`
- L18 _parameter_ `float InitializeParticle_RibbonWidthBias;`

#### static const (2)

- L3 _static_const_ `static const uint EInitializeParticleModuleFlag_UniformSpriteSize = 1 << 0;`
- L4 _static_const_ `static const uint EInitializeParticleModuleFlag_UniformMeshScale = 1 << 1;`

#### Functions (1)

- L20-37 _function_ `void InitializeParticle_Simulate(inout FStatelessParticle Particle)`

### `Plugins/FX/Niagara/Shaders/Private/Stateless/Modules/NiagaraStatelessModule_MeshIndex.ush` (Private)

- lines: 32; parse: all-branches

#### Global parameters (uniforms) (3)

- L3 _parameter_ `int MeshIndex_Index;`
- L4 _parameter_ `int MeshIndex_TableOffset;`
- L5 _parameter_ `int MeshIndex_TableNumElements;` — -1 to avoid added instructions

#### Functions (1)

- L7-30 _function_ `void MeshIndex_Simulate(inout FStatelessParticle Particle)`

### `Plugins/FX/Niagara/Shaders/Private/Stateless/Modules/NiagaraStatelessModule_MeshRotationRate.ush` (Private)

- lines: 22; parse: all-branches

#### Global parameters (uniforms) (4)

- L3 _parameter_ `int MeshRotationRate_ModuleEnabled;`
- L4 _parameter_ `float3 MeshRotationRate_Scale;`
- L5 _parameter_ `float3 MeshRotationRate_Bias;`
- L6 _parameter_ `FNiagaraStatelessBuiltDistributionType MeshRotationRate_RateScaleParameters;`

#### Functions (1)

- L8-20 _function_ `void MeshRotationRate_Simulate(inout FStatelessParticle Particle)`

### `Plugins/FX/Niagara/Shaders/Private/Stateless/Modules/NiagaraStatelessModule_RotateAroundPoint.ush` (Private)

- lines: 43; parse: all-branches

#### Structs / classes (1)

- L14-21 _struct_ **`FStatelessModule_RotateAroundPoint`** `struct FStatelessModule_RotateAroundPoint`
  - L16 _member_ `float Rate;`
  - L17 _member_ `float Radius;`
  - L18 _member_ `float InitialPhase;`
  - L19 _member_ `float3 Center;`
  - L20 _member_ `float4 RotationQuat;`

#### Global parameters (uniforms) (10)

- L3 _parameter_ `float RotateAroundPoint_RateScale;`
- L4 _parameter_ `float RotateAroundPoint_RateBias;`
- L5 _parameter_ `float RotateAroundPoint_RadiusScale;`
- L6 _parameter_ `float RotateAroundPoint_RadiusBias;`
- L7 _parameter_ `float RotateAroundPoint_InitialPhaseScale;`
- L8 _parameter_ `float RotateAroundPoint_InitialPhaseBias;`
- L9 _parameter_ `float3 RotateAroundPoint_CenterScale;`
- L10 _parameter_ `float3 RotateAroundPoint_CenterBias;`
- L11 _parameter_ `float3 RotateAroundPoint_RotationAxisScale;`
- L12 _parameter_ `float3 RotateAroundPoint_RotationAxisBias;`

#### Functions (2)

- L23-29 _function_ `void RotateAroundPoint_IntegratePosition(in FStatelessModule_RotateAroundPoint ModuleData, float Age, inout float3 Position)`
- L31-42 _function_ `void RotateAroundPoint_Simulate(inout FStatelessParticle Particle)`

### `Plugins/FX/Niagara/Shaders/Private/Stateless/Modules/NiagaraStatelessModule_ScaleColor.ush` (Private)

- lines: 12; parse: all-branches

#### Global parameters (uniforms) (1)

- L3 _parameter_ `FNiagaraStatelessBuiltDistributionType ScaleColor_Distribution;`

#### Functions (1)

- L5-11 _function_ `void ScaleColor_Simulate(inout FStatelessParticle Particle)`

### `Plugins/FX/Niagara/Shaders/Private/Stateless/Modules/NiagaraStatelessModule_ScaleMeshSize.ush` (Private)

- lines: 18; parse: all-branches

#### Global parameters (uniforms) (3)

- L3 _parameter_ `FNiagaraStatelessBuiltDistributionType ScaleMeshSize_Distribution;`
- L4 _parameter_ `float3 ScaleMeshSize_CurveScale;`
- L5 _parameter_ `int ScaleMeshSize_CurveScaleOffset;`

#### Functions (1)

- L7-17 _function_ `void ScaleMeshSize_Simulate(inout FStatelessParticle Particle)`

### `Plugins/FX/Niagara/Shaders/Private/Stateless/Modules/NiagaraStatelessModule_ScaleMeshSizeBySpeed.ush` (Private)

- lines: 22; parse: all-branches

#### Global parameters (uniforms) (4)

- L3 _parameter_ `float3 ScaleMeshSizeBySpeed_ScaleFactorBias;`
- L4 _parameter_ `float3 ScaleMeshSizeBySpeed_ScaleFactorScale;`
- L5 _parameter_ `FNiagaraStatelessBuiltDistributionType ScaleMeshSizeBySpeed_ScaleDistribution;`
- L6 _parameter_ `float ScaleMeshSizeBySpeed_VelocityNorm;`

#### Functions (1)

- L8-21 _function_ `void ScaleMeshSizeBySpeed_Simulate(inout FStatelessParticle Particle)`

### `Plugins/FX/Niagara/Shaders/Private/Stateless/Modules/NiagaraStatelessModule_ScaleRibbonWidth.ush` (Private)

- lines: 17; parse: all-branches

#### Global parameters (uniforms) (2)

- L3 _parameter_ `FNiagaraStatelessBuiltDistributionType ScaleRibbonWidth_Distribution;`
- L4 _parameter_ `float ScaleRibbonWidth_CurveScale;`

#### Functions (1)

- L6-16 _function_ `void ScaleRibbonWidth_Simulate(inout FStatelessParticle Particle)`

### `Plugins/FX/Niagara/Shaders/Private/Stateless/Modules/NiagaraStatelessModule_ScaleSpriteSize.ush` (Private)

- lines: 17; parse: all-branches

#### Global parameters (uniforms) (2)

- L3 _parameter_ `FNiagaraStatelessBuiltDistributionType ScaleSpriteSize_Distribution;`
- L4 _parameter_ `float2 ScaleSpriteSize_CurveScale;`

#### Functions (1)

- L6-16 _function_ `void ScaleSpriteSize_Simulate(inout FStatelessParticle Particle)`

### `Plugins/FX/Niagara/Shaders/Private/Stateless/Modules/NiagaraStatelessModule_ScaleSpriteSizeBySpeed.ush` (Private)

- lines: 22; parse: all-branches

#### Global parameters (uniforms) (4)

- L3 _parameter_ `float2 ScaleSpriteSizeBySpeed_ScaleFactorBias;`
- L4 _parameter_ `float2 ScaleSpriteSizeBySpeed_ScaleFactorScale;`
- L5 _parameter_ `FNiagaraStatelessBuiltDistributionType ScaleSpriteSizeBySpeed_ScaleDistribution;`
- L6 _parameter_ `float ScaleSpriteSizeBySpeed_VelocityNorm;`

#### Functions (1)

- L8-21 _function_ `void ScaleSpriteSizeBySpeed_Simulate(inout FStatelessParticle Particle)`

### `Plugins/FX/Niagara/Shaders/Private/Stateless/Modules/NiagaraStatelessModule_ShapeLocation.ush` (Private)

- lines: 118; parse: all-branches

#### Global parameters (uniforms) (6)

- L3 _parameter_ `uint4 ShapeLocation_Mode;`
- L4 _parameter_ `float4 ShapeLocation_Parameters0;`
- L5 _parameter_ `float4 ShapeLocation_Parameters1;`
- L6 _parameter_ `float4 ShapeLocation_Parameters2;`
- L7 _parameter_ `FNiagaraStatelessBuiltDistributionType ShapeLocation_TransformOffset;`
- L8 _parameter_ `float3 ShapeLocation_TransformOffsetScale;`

#### Functions (2)

- L10-109 _function_ `float3 ShapeLocation_GetLocation()`
- L111-117 _function_ `void ShapeLocation_Simulate(inout FStatelessParticle Particle)`

### `Plugins/FX/Niagara/Shaders/Private/Stateless/Modules/NiagaraStatelessModule_SolveVelocitiesAndForces.ush` (Private)

- lines: 155; parse: all-branches

#### Structs / classes (1)

- L42-49 _struct_ **`FStatelessModule_SolveVelocitiesAndForces`** `struct FStatelessModule_SolveVelocitiesAndForces`
  - L44 _member_ `float Mass;`
  - L45 _member_ `float Drag;`
  - L46 _member_ `float3 Velocity;`
  - L47 _member_ `float3 Wind;`
  - L48 _member_ `float3 Acceleration;`

#### Global resources (textures / buffers / samplers) (1)

- L40 _resource_ `ByteAddressBuffer SolveVelocitiesAndForces_NoiseLUT;`

#### Global parameters (uniforms) (33)

- L3 _parameter_ `float3 SolveVelocitiesAndForces_OwnerAccelerationScale;`
- L5 _parameter_ `float3 SolveVelocitiesAndForces_OwnerVelocityScale;` — float	SolveVelocitiesAndForces_OwnerDragScale;
- L6 _parameter_ `float SolveVelocitiesAndForces_MassScale;`
- L7 _parameter_ `float SolveVelocitiesAndForces_MassBias;`
- L8 _parameter_ `float SolveVelocitiesAndForces_DragScale;`
- L9 _parameter_ `float SolveVelocitiesAndForces_DragBias;`
- L10 _parameter_ `float3 SolveVelocitiesAndForces_VelocityScale;`
- L11 _parameter_ `float3 SolveVelocitiesAndForces_VelocityBias;`
- L12 _parameter_ `float3 SolveVelocitiesAndForces_WindScale;`
- L13 _parameter_ `float3 SolveVelocitiesAndForces_WindBias;`
- L14 _parameter_ `float3 SolveVelocitiesAndForces_AccelerationScale;`
- L15 _parameter_ `float3 SolveVelocitiesAndForces_AccelerationBias;`
- L16 _parameter_ `float3 SolveVelocitiesAndForces_GravityScale;`
- L17 _parameter_ `float3 SolveVelocitiesAndForces_GravityBias;`
- L19 _parameter_ `uint SolveVelocitiesAndForces_ConeVelocityEnabled;`
- L20 _parameter_ `float4 SolveVelocitiesAndForces_ConeQuat;`
- L21 _parameter_ `float SolveVelocitiesAndForces_ConeVelocityScale;`
- L22 _parameter_ `float SolveVelocitiesAndForces_ConeVelocityBias;`
- L23 _parameter_ `float SolveVelocitiesAndForces_ConeAngleScale;`
- L24 _parameter_ `float SolveVelocitiesAndForces_ConeAngleBias;`
- L25 _parameter_ `float SolveVelocitiesAndForces_ConeVelocityFalloff;`
- L27 _parameter_ `uint SolveVelocitiesAndForces_PointVelocityEnabled;`
- L28 _parameter_ `float SolveVelocitiesAndForces_PointVelocityScale;`
- L29 _parameter_ `float SolveVelocitiesAndForces_PointVelocityBias;`
- L30 _parameter_ `float3 SolveVelocitiesAndForces_PointOrigin;`
- L32 _parameter_ `uint SolveVelocitiesAndForces_NoiseEnabled;`
- L33 _parameter_ `float SolveVelocitiesAndForces_NoiseStrength;`
- L34 _parameter_ `float SolveVelocitiesAndForces_NoiseFrequency;`
- L35 _parameter_ `float3 SolveVelocitiesAndForces_NoiseFieldOffsetScale;`
- L36 _parameter_ `float3 SolveVelocitiesAndForces_NoiseFieldOffsetBias;`
- L37 _parameter_ `float SolveVelocitiesAndForces_NoiseLUTNormalize;`
- L38 _parameter_ `uint SolveVelocitiesAndForces_NoiseLUTRowMask;`
- L39 _parameter_ `uint SolveVelocitiesAndForces_NoiseLUTRowWidth;`

#### Functions (3)

- L51-74 _function_ `void SolveVelocitiesAndForces_EvaluateNoise(in FStatelessModule_SolveVelocitiesAndForces ModuleData, float Lifetime, float NormalizedAge, float Age, float3 NoiseFieldOffset, inout float3 Position)`
- L76-90 _function_ `void SolveVelocitiesAndForces_IntegratePosition(in FStatelessModule_SolveVelocitiesAndForces ModuleData, float Age, inout float3 Position)`
- L92-154 _function_ `void SolveVelocitiesAndForces_Simulate(inout FStatelessParticle Particle)`

### `Plugins/FX/Niagara/Shaders/Private/Stateless/Modules/NiagaraStatelessModule_SpriteFacingAndAlignment.ush` (Private)

- lines: 14; parse: all-branches

#### Global parameters (uniforms) (2)

- L3 _parameter_ `float3 SpriteFacingAndAlignment_SpriteFacing;`
- L4 _parameter_ `float3 SpriteFacingAndAlignment_SpriteAlignment;`

#### Functions (1)

- L6-13 _function_ `void SpriteFacingAndAlignment_Simulate(inout FStatelessParticle Particle)`

### `Plugins/FX/Niagara/Shaders/Private/Stateless/Modules/NiagaraStatelessModule_SpriteRotationRate.ush` (Private)

- lines: 22; parse: all-branches

#### Global parameters (uniforms) (4)

- L3 _parameter_ `int SpriteRotationRate_Enabled;`
- L4 _parameter_ `float SpriteRotationRate_Scale;`
- L5 _parameter_ `float SpriteRotationRate_Bias;`
- L6 _parameter_ `FNiagaraStatelessBuiltDistributionType SpriteRotationRate_RateScaleParameters;`

#### Functions (1)

- L8-21 _function_ `void SpriteRotationRate_Simulate(inout FStatelessParticle Particle)`

### `Plugins/FX/Niagara/Shaders/Private/Stateless/Modules/NiagaraStatelessModule_SubUVAnimation.ush` (Private)

- lines: 29; parse: all-branches

#### Global parameters (uniforms) (8)

- L3 _parameter_ `int SubUVAnimation_Mode;`
- L4 _parameter_ `float SubUVAnimation_NumFrames;`
- L5 _parameter_ `float SubUVAnimation_InitialFrameScale;`
- L6 _parameter_ `float SubUVAnimation_InitialFrameBias;`
- L7 _parameter_ `float SubUVAnimation_InitialFrameRateChange;`
- L8 _parameter_ `float SubUVAnimation_AnimFrameStart;`
- L9 _parameter_ `float SubUVAnimation_AnimFrameRange;`
- L10 _parameter_ `float SubUVAnimation_RateScale;`

#### Functions (1)

- L12-28 _function_ `void SubUVAnimation_Simulate(inout FStatelessParticle Particle)`
