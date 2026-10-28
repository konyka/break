# Shaders / Plugins/Experimental/ChaosNiagara/Shaders

- files: 3; lines: 527
- record kinds: define=3, function=43, include=3, parameter=18, resource=35

### `Plugins/Experimental/ChaosNiagara/Shaders/NiagaraDataInterfaceChaosDestruction.ush` (Other)

- lines: 181; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global resources (textures / buffers / samplers) (25)

- L3 _resource_ `Buffer<float3> {ParameterName}_PositionBuffer;`
- L4 _resource_ `Buffer<float3> {ParameterName}_VelocityBuffer;`
- L5 _resource_ `Buffer<float> {ParameterName}_ExtentMinBuffer;`
- L6 _resource_ `Buffer<float> {ParameterName}_ExtentMaxBuffer;`
- L7 _resource_ `Buffer<float> {ParameterName}_VolumeBuffer;`
- L8 _resource_ `Buffer<int> {ParameterName}_SolverIDBuffer;` — NOTE(mv): Not used?
- L9 _resource_ `Buffer<float> {ParameterName}_DensityBuffer;`
- L10 _resource_ `Buffer<float> {ParameterName}_FrictionBuffer;`
- L11 _resource_ `Buffer<float> {ParameterName}_RestitutionBuffer;`
- L12 _resource_ `Buffer<int> {ParameterName}_SurfaceTypeBuffer;`
- L13 _resource_ `Buffer<float4> {ParameterName}_ColorBuffer;`
- L15 _resource_ `Buffer<float3> {ParameterName}_IncomingLocationBuffer;`
- L16 _resource_ `Buffer<float3> {ParameterName}_IncomingAccumulatedImpulseBuffer;`
- L17 _resource_ `Buffer<float3> {ParameterName}_IncomingNormalBuffer;`
- L18 _resource_ `Buffer<float3> {ParameterName}_IncomingVelocity1Buffer;`
- L19 _resource_ `Buffer<float3> {ParameterName}_IncomingVelocity2Buffer;`
- L20 _resource_ `Buffer<float3> {ParameterName}_IncomingAngularVelocity1Buffer;`
- L21 _resource_ `Buffer<float3> {ParameterName}_IncomingAngularVelocity2Buffer;`
- L22 _resource_ `Buffer<float> {ParameterName}_IncomingMass1Buffer;`
- L23 _resource_ `Buffer<float> {ParameterName}_IncomingMass2Buffer;`
- L24 _resource_ `Buffer<float> {ParameterName}_IncomingTimeBuffer;`
- L26 _resource_ `Buffer<float3> {ParameterName}_TransformTranslationBuffer;`
- L27 _resource_ `Buffer<float4> {ParameterName}_TransformRotationBuffer;`
- L28 _resource_ `Buffer<float3> {ParameterName}_TransformScaleBuffer;`
- L29 _resource_ `Buffer<float3> {ParameterName}_BoundsBuffer;`

#### Global parameters (uniforms) (2)

- L36 _parameter_ `int {ParameterName}_LastSpawnedPointID;`
- L38 _parameter_ `float {ParameterName}_SolverTime;`

#### Functions (20)

- L41-45 _function_ `void GetPosition_{ParameterName}(in int ParticleID, out float3 Out_Position)`
- L47-51 _function_ `void GetNormal_{ParameterName}(in int ParticleID, out float3 Out_Normal)`
- L53-57 _function_ `void GetVelocity_{ParameterName}(in int ParticleID, out float3 Out_Velocity)`
- L59-63 _function_ `void GetAngularVelocity_{ParameterName}(in int ParticleID, out float3 Out_AngularVelocity)`
- L65-69 _function_ `void GetExtentMin_{ParameterName}(in int ParticleID, out float Out_ExtentMin)`
- L71-75 _function_ `void GetExtentMax_{ParameterName}(in int ParticleID, out float Out_ExtentMax)`
- L77-81 _function_ `void GetVolume_{ParameterName}(in int ParticleID, out float Out_Volume)`
- L83-90 _function_ `void GetParticleIdsToSpawnAtTime_{ParameterName}(in float Time, out int Out_Min, out int Out_Max, out int Out_Count)`
- L92-96 _function_ `void GetPointType_{ParameterName}(in int ParticleID, out int Out_PointType)`
- L98-102 _function_ `void GetColor_{ParameterName}(in int ParticleID, out float4 Out_Color)`
- L104-107 _function_ `void GetSolverTime_{ParameterName}(out float Out_SolverTime)`
- L109-113 _function_ `void GetDensity_{ParameterName}(in int ParticleID, out float Out_Density)`
- L115-119 _function_ `void GetFriction_{ParameterName}(in int ParticleID, out float Out_Friction)`
- L121-125 _function_ `void GetRestitution_{ParameterName}(in int ParticleID, out float Out_Restitution)`
- L127-133 _function_ `void GetTransform_{ParameterName}(in int ParticleID, out float3 Out_Translation, out float4 Out_Rotation, out float3 Out_Scale)`
- L135-139 _function_ `void GetSize_{ParameterName}(in int ParticleID, out float3 Out_Size)`
- L141-145 _function_ `void GetSurfaceType_{ParameterName}(in int ParticleID, out int Out_SurfaceType)`
- L147-160 _function_ `void GetCollisionData_{ParameterName}(in int ParticleID, out float3 Out_Location, out float3 Out_AccumulatedImpulse, out float3 Out_Normal, out float3 Out_Velocity1, out float3 Out_Velocity2, out float3 Out_AngularVelocity1, out float3 Out_AngularVelocity2, out float Out_Mass1, out float Out_Mass2, out float Out_Time)`
- L162-170 _function_ `void GetBreakingData_{ParameterName}(in int ParticleID, out float3 Out_Location, out float3 Out_Velocity, out float3 Out_AngularVelocity, out float Out_Mass, out float Out_Time)`
- L172-180 _function_ `void GetTrailingData_{ParameterName}(in int ParticleID, out float3 Out_Location, out float3 Out_Velocity, out float3 Out_AngularVelocity, out float Out_Mass, out float Out_Time)`

### `Plugins/Experimental/ChaosNiagara/Shaders/NiagaraDataInterfaceGeometryCollection.ush` (Other)

- lines: 219; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)
- includes: L7 `/Plugin/FX/Niagara/Private/NiagaraTransformUtils.ush`

#### Macros (#define, 3)

- L14 `#define BOX_INDEX 0`
- L15 `#define SPHERE_INDEX 1`
- L16 `#define CAPSULE_INDEX 2`
- L216 #undef `BOX_INDEX`; L217 #undef `SPHERE_INDEX`; L218 #undef `CAPSULE_INDEX`

#### Global resources (textures / buffers / samplers) (6)

- L24 _resource_ `Buffer<float4> {ParameterName}_WorldTransformBuffer;`
- L25 _resource_ `Buffer<float4> {ParameterName}_PrevWorldTransformBuffer;`
- L26 _resource_ `Buffer<float4> {ParameterName}_WorldInverseTransformBuffer;`
- L27 _resource_ `Buffer<float4> {ParameterName}_PrevWorldInverseTransformBuffer;`
- L28 _resource_ `Buffer<float4> {ParameterName}_BoundsBuffer;`
- L29 _resource_ `ByteAddressBuffer {ParameterName}_ElementTransforms;`

#### Global parameters (uniforms) (6)

- L18 _parameter_ `float3 {ParameterName}_BoundsMin;`
- L19 _parameter_ `float3 {ParameterName}_BoundsMax;`
- L20 _parameter_ `int {ParameterName}_NumPieces;`
- L21 _parameter_ `float3 {ParameterName}_RootTransform_Translation;`
- L22 _parameter_ `float4 {ParameterName}_RootTransform_Rotation;`
- L23 _parameter_ `float3 {ParameterName}_RootTransform_Scale;`

#### Functions (12)

- L36-40 _function_ `float3x4 DIGeometryCollection_GetCurrentTransform_{ParameterName}(in int ElementIndex)`
- L42-46 _function_ `float3x4 DIGeometryCollection_GetInverseTransform_{ParameterName}(in int ElementIndex)`
- L48-52 _function_ `float3x4 DIGeometryCollection_GetPreviousTransform_{ParameterName}(in int ElementIndex)`
- L54-58 _function_ `float3x4 DIGeometryCollection_GetPreviousInverse_{ParameterName}(in int ElementIndex)`
- L66-110 _function_ `float DIGeometryCollection_GetBoxProjection_{ParameterName}(in float3 LocalPosition, in float3 BoxExtent, in int BoxIndex, inout float3 OutClosestPosition, inout float3 OutClosestNormal, inout int OutElementIndex, inout float OutMinDistance)` — Given a world space position (WorldPosition) compute the sphere closest point (position,normal,velocity)
- L112-115 _function_ `void GetNumElements_{ParameterName}(out int OutCount)`
- L117-122 _function_ `void GetGeometryComponentTransform_{ParameterName}(out float3 OutPosition, out float4 OutRotation, out float3 OutScale)`
- L124-137 _function_ `void GetElementTransform_{ParameterName}(in int InElementIndex, out float3 OutTranslation, out float4 OutRotation, out float3 OutScale)`
- L139-153 _function_ `void GetElementBounds_{ParameterName}(in int InElementIndex, out float3 OutCenter, out float3 OutBoundingBox)`
- L160-166 _function_ `float3 DIGeometryCollection_GetLocalPosition_{ParameterName}(in float3 WorldPosition, in int ElementIndex, in float TimeFraction )`
- L169-208 _function_ `void DIGeometryCollection_GetClosestPointNoNormal_{ParameterName}(in float3 WorldPosition, in float DeltaTime, in float TimeFraction, out float OutClosestDistance, out float3 OutClosestPosition, out float3 OutClosestVelocity, out int ElementIndex)` — Given a world space position (WorldPosition) compute the static mesh closest point (position,normal,velocity)
- L211-214 _function_ `void GetClosestPointNoNormal_{ParameterName}(in float3 WorldPosition, in float DeltaTime, in float TimeFraction, out float ClosestDistance, out float3 OutClosestPosition, out float3 OutClosestVelocity, out int ElementIndex)`

### `Plugins/Experimental/ChaosNiagara/Shaders/NiagaraDataInterfacePhysicsField.ush` (Other)

- lines: 127; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)
- includes: L12 `/Engine/Private/PhysicsFieldShared.ush`, L13 `/Engine/Private/PhysicsFieldEval.ush`

#### Global resources (textures / buffers / samplers) (4)

- L19 _resource_ `Buffer<float> {ParameterName}_ClipmapBuffer;`
- L28 _resource_ `Buffer<float> {ParameterName}_NodesParams;`
- L29 _resource_ `Buffer<int> {ParameterName}_NodesOffsets;`
- L30 _resource_ `Buffer<int> {ParameterName}_TargetsOffsets;`

#### Global parameters (uniforms) (10)

- L16 _parameter_ `int4 {ParameterName}_TargetMappings[MAX_PHYSICS_FIELD_TARGETS];` — Global param for the world field
- L17 _parameter_ `int {ParameterName}_bClipmapAvailable;`
- L20 _parameter_ `float3 {ParameterName}_ClipmapCenter;`
- L21 _parameter_ `float {ParameterName}_ClipmapDistance;`
- L22 _parameter_ `int {ParameterName}_ClipmapResolution;`
- L23 _parameter_ `int {ParameterName}_ClipmapExponent;`
- L24 _parameter_ `int {ParameterName}_ClipmapCount;`
- L25 _parameter_ `int {ParameterName}_TargetCount;`
- L26 _parameter_ `int4 {ParameterName}_FieldTargets[MAX_PHYSICS_FIELD_TARGETS];`
- L31 _parameter_ `float {ParameterName}_TimeSeconds;`

#### Functions (11)

- L33-49 _function_ `float3 PhysicsVectorField_{ParameterName}(in float3 WorldPosition, in int TargetIndex, in bool bUseClipmap)`
- L51-67 _function_ `float PhysicsScalarField_{ParameterName}(in float3 WorldPosition, in int TargetIndex, in bool bUseClipmap)`
- L69-85 _function_ `int PhysicsIntegerField_{ParameterName}(in float3 WorldPosition, in int TargetIndex, in bool bUseClipmap)`
- L87-90 _function_ `void SamplePhysicsVectorField_{ParameterName}(in float3 WorldPosition, in int TargetIndex, out float3 OutFieldVector)`
- L92-95 _function_ `void SamplePhysicsScalarField_{ParameterName}(in float3 WorldPosition, in int TargetIndex, out float OutFieldScalar)`
- L97-100 _function_ `void SamplePhysicsIntegerField_{ParameterName}(in float3 WorldPosition, in int TargetIndex, out int OutFieldInteger)`
- L102-105 _function_ `void EvalPhysicsVectorField_{ParameterName}(in float3 WorldPosition, in int TargetIndex, out float3 OutFieldVector)`
- L107-110 _function_ `void EvalPhysicsScalarField_{ParameterName}(in float3 WorldPosition, in int TargetIndex, out float OutFieldScalar)`
- L112-115 _function_ `void EvalPhysicsIntegerField_{ParameterName}(in float3 WorldPosition, in int TargetIndex, out int OutFieldInteger)`
- L117-120 _function_ `void GetPhysicsFieldResolution_{ParameterName}(out float3 OutTextureSize)`
- L122-126 _function_ `void GetPhysicsFieldBounds_{ParameterName}(out float3 OutMinBounds, out float3 OutMaxBounds)`
