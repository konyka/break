# Shaders / Plugins/Runtime/HairStrands/Shaders/Private

- files: 20; lines: 4399
- record kinds: cpp_binding=4, define=3, entry=5, function=209, groupshared=2, include=9, parameter=37, resource=32, static_const=15

### `Plugins/Runtime/HairStrands/Shaders/Private/NiagaraAngularSpringMaterial.ush` (Private)

- lines: 165; parse: all-branches
- L3 #pragma `once`

#### Functions (6)

- L10-31 _function_ `void ComputeMaterialFrame(in int StrandsSize)`
- L33-45 _function_ `void UpdateMaterialFrame(in int StrandsSize)`
- L74-83 _function_ `void SetupAngularSpringMaterial(in int StrandsSize, in float YoungModulus, in float RodThickness, in float RestLength, in float DeltaTime, in bool ProjectConstraint, in float MaterialDamping, out float OutMaterialCompliance, out float OutMaterialWeight, out float3 OutMaterialMultiplier)`
- L85-109 _function_ `void UpdateAngularSpringMultiplier( in float RestLength, in float3 RestDirection, in float DeltaTime, in bool ProjectConstraint, in float MaterialDamping, in float InMaterialCompliance, in float InMaterialWeight, inout float3 OutMaterialMultiplier)`
- L111-136 _function_ `void SolveAngularSpringMaterial(in bool EnableConstraint, in int StrandsSize, in float RestLength, in float3 RestDirection, in float DeltaTime, in float MaterialDamping, in float MaterialCompliance, in float MaterialWeight, in float3 MaterialMultiplier, out float3 OutMaterialMultiplier)`
- L138-164 _function_ `void ProjectAngularSpringMaterial(in bool EnableConstraint, in int StrandsSize, in float YoungModulus, in float RodThickness, in float RestLength, in float3 RestDirection, in float DeltaTime, out float3 OutNodePosition)`

### `Plugins/Runtime/HairStrands/Shaders/Private/NiagaraClearPressureGrid.usf` (Private)

- lines: 43; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`

#### Entry points (1)

- L17-43 _entry_ `[numthreads(THREAD_COUNT, THREAD_COUNT, THREAD_COUNT)] void MainCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FClearPressureGridCS` SF_Compute via IMPLEMENT_SHADER_TYPE (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/Niagara/NiagaraDataInterfacePressureGrid.cpp:391)

#### Global resources (textures / buffers / samplers) (2)

- L14 _resource_ `Buffer<int> GridCurrentBuffer;`
- L15 _resource_ `RWBuffer<int> GridDestinationBuffer;`

#### Global parameters (uniforms) (2)

- L11 _parameter_ `uint3 GridSize;`
- L12 _parameter_ `int CopyPressure;`

#### static const (4)

- L5 _static_const_ `static const int FLUID_PRESSURE_OFFSET = 6;`
- L6 _static_const_ `static const int FLUID_DISTANCE_OFFSET = 14;`
- L7 _static_const_ `static const int NUM_ATTRIBUTES = 18;`
- L9 _static_const_ `static const float MAX_DISTANCE = 1e+8;`

### `Plugins/Runtime/HairStrands/Shaders/Private/NiagaraClearVelocityGrid.usf` (Private)

- lines: 16; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`

#### Entry points (1)

- L8-16 _entry_ `[numthreads(THREAD_COUNT, THREAD_COUNT, THREAD_COUNT)] void MainCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FClearVelocityGridCS` SF_Compute via IMPLEMENT_SHADER_TYPE (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/Niagara/NiagaraDataInterfaceVelocityGrid.cpp:606)

#### Global resources (textures / buffers / samplers) (1)

- L6 _resource_ `RWBuffer<int> GridDestinationBuffer;`

#### Global parameters (uniforms) (1)

- L5 _parameter_ `uint3 GridSize;`

### `Plugins/Runtime/HairStrands/Shaders/Private/NiagaraConstantVolumeMaterial.ush` (Private)

- lines: 98; parse: all-branches
- L3 #pragma `once`

#### Functions (3)

- L10-25 _function_ `void SetupVolumeSpringMaterial(in int StrandsSize, in float YoungModulus, in float RestVolume, in float DeltaTime, in bool ProjectConstraint, in float MaterialDamping, out float OutMaterialCompliance, out float OutMaterialWeight, out float OutMaterialMultiplier)`
- L27-75 _function_ `void UpdateVolumeSpringMultiplier(in float RestVolume, in float DeltaTime, in bool ProjectConstraint, in float MaterialDamping, in float MaterialCompliance, in float MaterialWeight, inout float OutMaterialMultiplier)`
- L77-98 _function_ `void SolveVolumeSpringMaterial(in bool EnableConstraint, in int StrandsSize, in float RestVolume, in float DeltaTime, in float MaterialDamping, in float MaterialCompliance, in float MaterialWeight, in float MaterialMultiplier, out float OutMaterialMultiplier)`

### `Plugins/Runtime/HairStrands/Shaders/Private/NiagaraCopyBoundingBox.usf` (Private)

- lines: 42; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`

#### Entry points (1)

- L17-42 _entry_ `[numthreads(THREAD_COUNT, 1, 1)] void MainCS(uint2 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute**

#### Global resources (textures / buffers / samplers) (2)

- L6 _resource_ `RWBuffer<uint> BoundingBoxBufferA;`
- L7 _resource_ `RWBuffer<uint> OutBoundingBoxBufferB;`

#### Global parameters (uniforms) (1)

- L5 _parameter_ `uint NumElements;`

#### Functions (1)

- L9-15 _function_ `uint FloatToUint( in float FloatValue)`

### `Plugins/Runtime/HairStrands/Shaders/Private/NiagaraCopyVelocityGrid.usf` (Private)

- lines: 17; parse: all-branches
- includes: L3 `/Engine/Private/Common.ush`

#### Entry points (1)

- L9-17 _entry_ `[numthreads(THREAD_COUNT, THREAD_COUNT, THREAD_COUNT)] void MainCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FCopyVelocityGridCS` SF_Compute via IMPLEMENT_SHADER_TYPE (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/Niagara/NiagaraDataInterfaceVelocityGrid.cpp:659)

#### Global resources (textures / buffers / samplers) (2)

- L6 _resource_ `Buffer<int> GridCurrentBuffer;`
- L7 _resource_ `RWBuffer<int> GridDestinationBuffer;`

#### Global parameters (uniforms) (1)

- L5 _parameter_ `uint3 GridSize;`

### `Plugins/Runtime/HairStrands/Shaders/Private/NiagaraCosseratRodMaterial.ush` (Private)

- lines: 399; parse: all-branches
- L3 #pragma `once`

#### Functions (12)

- L10-31 _function_ `void SetupAlignRodMaterial(in int StrandsSize, in float YoungModulus, in float RodThickness, in float RestLength, in float DeltaTime, in bool ProjectConstraint, in float MaterialDamping, out float OutMaterialCompliance, out float OutMaterialWeight, out float3 OutMaterialMultiplier)`
- L33-65 _function_ `void UpdateAlignRodMultiplier( in float RestLength, in float DeltaTime, in bool ProjectConstraint, in float MaterialDamping, in float MaterialCompliance, in float MaterialWeight, inout float3 OutMaterialMultiplier)`
- L67-91 _function_ `void SolveAlignRodMaterial(in bool EnableConstraint, in int StrandsSize, in float RestLength, in float DeltaTime, in float MaterialDamping, in float MaterialCompliance, in float MaterialWeight, in float3 MaterialMultiplier, out float3 OutMaterialMultiplier)`
- L93-118 _function_ `void ProjectAlignRodMaterial(in bool EnableConstraint, in int StrandsSize, in float YoungModulus, in float RodThickness, in float RestLength, in float DeltaTime, out float4 OutNodeOrientation)`
- L125-147 _function_ `void SetupStretchRodMaterial(in int StrandsSize, in float YoungModulus, in float RodThickness, in float RestLength, in float DeltaTime, in bool ProjectConstraint, in float MaterialDamping, out float OutMaterialCompliance, out float OutMaterialWeight, out float3 OutMaterialMultiplier)`
- L149-178 _function_ `void UpdateStretchRodMultiplier( in float RestLength, in float DeltaTime, in bool ProjectConstraint, in float MaterialDamping, in float MaterialCompliance, in float MaterialWeight, inout float3 OutMaterialMultiplier)`
- L180-204 _function_ `void SolveStretchRodMaterial(in bool EnableConstraint, in int StrandsSize, in float RestLength, in float DeltaTime, in float MaterialDamping, in float MaterialCompliance, in float MaterialWeight, in float3 MaterialMultiplier, out float3 OutMaterialMultiplier)`
- L206-231 _function_ `void ProjectStretchRodMaterial(in bool EnableConstraint, in int StrandsSize, in float YoungModulus, in float RodThickness, in float RestLength, in float DeltaTime, out float3 OutNodePosition)`
- L238-263 _function_ `void SetupBendRodMaterial(in int StrandsSize, in float YoungModulus, in float RodThickness, in float RestLength, in float DeltaTime, in bool ProjectConstraint, in float MaterialDamping, out float OutMaterialCompliance, out float OutMaterialWeight, out float3 OutMaterialMultiplier)`
- L265-300 _function_ `void UpdateBendRodMultiplier(in float RestLength, in float4 RestDarboux, in float DeltaTime, in bool ProjectConstraint, in float MaterialDamping, in float MaterialCompliance, in float MaterialWeight, inout float3 OutMaterialMultiplier)`
- L302-328 _function_ `void SolveBendRodMaterial(in bool EnableConstraint, in int StrandsSize, in float RestLength, in float4 RestDarboux, in float DeltaTime, in float MaterialDamping, in float MaterialCompliance, in float MaterialWeight, in float3 MaterialMultiplier, out float3 OutMaterialMultiplier)`
- L330-357 _function_ `void ProjectBendRodMaterial(in bool EnableConstraint, in int StrandsSize, in float YoungModulus, in float RodThickness, in float RestLength, in float4 RestDarboux, in float DeltaTime, out float4 OutNodeOrientation)`

### `Plugins/Runtime/HairStrands/Shaders/Private/NiagaraDataInterfaceHairStrands.ush` (Private)

- lines: 40; parse: all-branches
- L7 #pragma `once`

#### static const (2)

- L9 _static_const_ `static const float M_PI = 3.14159265;`
- L10 _static_const_ `static const float3 MAX_POS = float3(1e+8,1e+8,1e+8);`

#### Functions (3)

- L12-20 _function_ `float3 Uint3ToFloat3( in uint3 Uint3Vector)`
- L22-30 _function_ `uint3 Float3ToUint3( in float3 Float3Vector)`
- L32-38 _function_ `uint FloatToUint( in float FloatValue)`

### `Plugins/Runtime/HairStrands/Shaders/Private/NiagaraDataInterfaceHairStrandsTemplate.ush` (Private)

- lines: 1172; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)
- includes: L6 `/Engine/Private/HairStrands/HairStrandsBindingCommon.ush`

#### Global resources (textures / buffers / samplers) (13)

- L8 _resource_ `RWByteAddressBuffer {ParameterName}_DeformedPositionBuffer;`
- L9 _resource_ `ByteAddressBuffer {ParameterName}_RestPositionBuffer;`
- L10 _resource_ `ByteAddressBuffer {ParameterName}_CurvesOffsetsBuffer;`
- L11 _resource_ `Buffer<float4> {ParameterName}_RestTrianglePositionBuffer;`
- L12 _resource_ `Buffer<float4> {ParameterName}_DeformedTrianglePositionBuffer;`
- L13 _resource_ `Buffer<uint> {ParameterName}_RootBarycentricCoordinatesBuffer;`
- L14 _resource_ `Buffer<uint> {ParameterName}_RootToUniqueTriangleIndexBuffer;`
- L27 _resource_ `StructuredBuffer<float4> {ParameterName}_DeformedPositionOffset;`
- L28 _resource_ `RWBuffer<uint> {ParameterName}_BoundingBoxBuffer;`
- L35 _resource_ `StructuredBuffer<float4> {ParameterName}_RestSamplePositionsBuffer;`
- L36 _resource_ `StructuredBuffer<float4> {ParameterName}_MeshSampleWeightsBuffer;`
- L37 _resource_ `StructuredBuffer<float4> {ParameterName}_DeformedSamplePositionsBuffer;`
- L38 _resource_ `Buffer<float> {ParameterName}_ParamsScaleBuffer;`

#### Global parameters (uniforms) (22)

- L15 _parameter_ `float4x4 {ParameterName}_WorldTransform;`
- L16 _parameter_ `float4x4 {ParameterName}_WorldInverse;`
- L17 _parameter_ `float4 {ParameterName}_WorldRotation;`
- L18 _parameter_ `float4x4 {ParameterName}_BoneTransform;`
- L19 _parameter_ `float4x4 {ParameterName}_BoneInverse;`
- L20 _parameter_ `float4 {ParameterName}_BoneRotation;`
- L21 _parameter_ `int {ParameterName}_NumStrands;`
- L22 _parameter_ `int {ParameterName}_StrandSize;`
- L23 _parameter_ `int {ParameterName}_InterpolationMode;`
- L24 _parameter_ `float3 {ParameterName}_RestRootOffset;`
- L25 _parameter_ `float3 {ParameterName}_DeformedRootOffset;`
- L26 _parameter_ `float3 {ParameterName}_RestPositionOffset;`
- L29 _parameter_ `uint {ParameterName}_ResetSimulation;`
- L30 _parameter_ `uint {ParameterName}_RestUpdate;`
- L31 _parameter_ `uint {ParameterName}_LocalSimulation;`
- L32 _parameter_ `int {ParameterName}_SampleCount;`
- L33 _parameter_ `uint {ParameterName}_RBFLocalSpace;`
- L34 _parameter_ `int4 {ParameterName}_BoundingBoxOffsets;`
- L39 _parameter_ `float3 {ParameterName}_BoneLinearVelocity;`
- L40 _parameter_ `float3 {ParameterName}_BoneAngularVelocity;`
- L41 _parameter_ `float3 {ParameterName}_BoneLinearAcceleration;`
- L42 _parameter_ `float3 {ParameterName}_BoneAngularAcceleration;`

#### Functions (82)

- L50-64 _function_ `void GetBoundingBox_{ParameterName}(in int BoxIndex, out float3 OutBoxCenter, out float3 OutBoxExtent)` — Get the boundingh box
- L67-89 _function_ `void ResetBoundingBox_{ParameterName}(out bool FunctionStatus)` — Reset the bounding box
- L91-112 _function_ `void BuildBoundingBox_{ParameterName}(in float3 NodePosition, out bool FunctionStatus)`
- L118-121 _function_ `FHairCurve UnpackCurve_{ParameterName}(in uint InCurveIndex)` — Utilities regarding strands curve
- L129-132 _function_ `int GetNumNodes_{ParameterName}()` — Given a node index return the strand index and the local index within the strand
- L140-160 _function_ `float ComputeStrandLength_{ParameterName}(in int StrandIndex)` — Given a strand index return the corresponding strand length
- L168-185 _function_ `void ComputeNodeMass_{ParameterName}(in float StrandsDensity, in float NodeThickness, out float OutNodeMass)` — Compute the node mass
- L188-203 _function_ `void ComputeNodeInertia_{ParameterName}(in float StrandsDensity, in float NodeThickness, out float3 OutNodeInertia)` — Compute the node inertia
- L206-231 _function_ `void SetNodePosition_{ParameterName}(in bool RootNode, const float NodePoint, const float PointCount, const float CoordScale, const int PointPrev, const int PointNext, const int PointOffset, in int StrandIndex, out float3 OutNodePosition)` — Set the node position by linear interpolation over the points
- L234-257 _function_ `void ComputeNodePosition_{ParameterName}(out float3 OutNodePosition)` — Compute the node position by linear interpolation over the points
- L260-293 _function_ `void SmoothNodePosition_{ParameterName}(in float SmoothingFilter, inout float3 OutNodePosition)` — Compute the node position by linear interpolation over the points
- L296-312 _function_ `void ComputeRootOrientation_{ParameterName}()` — Compute the root orientation
- L315-327 _function_ `void UpdateRootOrientation_{ParameterName}()` — Update the root orientation
- L330-340 _function_ `void ComputeNodeOrientation_{ParameterName}(in float3 NodePosition, out float4 OutNodeOrientation)` — Compute the node orientation
- L348-378 _function_ `void InitGridSamples_{ParameterName}(in float3 NodePosition, in float3 NodeVelocity, in float NodeMass, in float GridLength, out int OutNumSamples, out float3 OutDeltaPosition, out float3 OutDeltaVelocity, out float OutSampleMass)` — Init the samples along the strands that will be used to transfer informations to the grid
- L381-397 _function_ `void GetSampleState_{ParameterName}(in float3 NodePosition, in float3 NodeVelocity, in float3 DeltaPosition, in float3 DeltaVelocity, in int NumSamples, in int SampleIndex, out float3 OutSamplePosition, out float3 OutSampleVelocity)` — Get the sample state given an index and a delta position/velocity
- L405-427 _function_ `void ComputeEdgeVolume_{ParameterName}(in float3 NodePosition, out float OutEdgeVolume)` — Compute the edge volume value
- L430-439 _function_ `void ComputeEdgeLengthInternal_{ParameterName}(in float3 NodePosition, in int NodeOffset, out float OutEdgeLength)` — Compute the edge length value
- L442-466 _function_ `void ComputeEdgeRotation_{ParameterName}(in float4 NodeOrientation, out float4 OutEdgeRotation)` — Compute the edge darboux vector (diff between consecutive edge orientations)
- L468-547 _function_ `void ComputeEdgeDirection_{ParameterName}(in float3 NodePosition, in float4 NodeOrientation, in float NodeMass, in float3 GravityVector, in float GravityPreloading, in float BendStiffness, in float StrandThickness, in float RestLength, out float3 OutRestDirection)`
- L556-579 _function_ `void ResetPointPosition_{ParameterName}(out bool ReportStatus)` — Reset the deformed points position to the rest ones
- L582-596 _function_ `void ComputeProjectionTriangle_{ParameterName}(in float2 ProjectionUV, in float3 PA, in float3 PB, in float3 PC, in float3 Offset, out float3 OutTrianglePosition, out float4 OutTriangleRotation)` — Compute the projection triangle
- L599-606 _function_ `void BuildDeformedTriangle_{ParameterName}(in float2 ProjectionUV, in int TriangleIndex, out float3 OutTrianglePosition, out float4 OutTriangleRotation)` — Get the deformed triangle
- L609-616 _function_ `void BuildRestTriangle_{ParameterName}(in float2 ProjectionUV, in int TriangleIndex, out float3 OutTrianglePosition, out float4 OutTriangleRotation)` — Get the rest triangle
- L619-622 _function_ `float3 TriangleLocalPosition_{ParameterName}(in float3 TrianglePosition, in float4 TriangleRotation, in float3 WorldPosition)` — Eval the triangle local position
- L625-628 _function_ `float4 TriangleLocalOrientation_{ParameterName}(in float3 TrianglePosition, in float4 TriangleRotation, in float4 WorldOrientation)` — Eval the triangle local orientation
- L631-634 _function_ `float3 TriangleWorldPosition_{ParameterName}(in float3 TrianglePosition, in float4 TriangleRotation, in float3 LocalPosition)` — Eval the triangle world position
- L637-640 _function_ `float4 TriangleWorldOrientation_{ParameterName}(in float3 TrianglePosition, in float4 TriangleRotation, in float4 LocalOrientation)` — Eval the triangle local orientation
- L643-665 _function_ `void UpdateTriangleDisplace_{ParameterName}(in int StrandIndex, in float3 NodePosition, in float3 RestPosition, out float3 RestTrianglePosition, out float4 RestTriangleOrientation, out float3 DeformedTrianglePosition, out float4 DeformedTriangleOrientation)` — Report interpolated nodes displacements onto the points positions
- L668-692 _function_ `void UpdateDeformedPositions_{ParameterName}(in float3 LocalDisplace, in int PositionIndex, in float3 RestTrianglePosition, in float4 RestTriangleOrientation, in float3 DeformedTrianglePosition, in float4 DeformedTriangleOrientation)` — Report interpolated nodes displacements onto the points positions
- L695-732 _function_ `void UpdatePointPosition_{ParameterName}(in float3 NodePosition, in float3 RestPosition, out bool OutReportStatus)` — Report interpolated nodes displacements onto the points positions
- L735-739 _function_ `void GetPointPosition_{ParameterName}(in int PointIndex, out float3 OutPointPosition)` — Get the point position
- L747-765 _function_ `void AdvectNodePosition_{ParameterName}(in float NodeMass, in bool IsPositionMobile, in float3 ExternalForce, in float3 ForceGradient, in float DeltaTime, inout float3 OutLinearVelocity, inout float3 OutNodePosition)` — Add external force to the linear velocity and advect node position
- L768-783 _function_ `void AdvectNodeOrientation_{ParameterName}(in float3 NodeInertia, in bool IsOrientationMobile, in float3 ExternalTorque, in float3 TorqueGradient, in float DeltaTime, inout float3 OutAngularVelocity, inout float4 OutNodeOrientation)` — Add external torque to the angular velocity and advect node orientation
- L786-789 _function_ `void UpdateLinearVelocity_{ParameterName}(in float3 PreviousPosition, in float3 NodePosition, in float DeltaTime, out float3 OutLinearVelocity)` — Update the node linear velocity based on the node position difference
- L793-807 _function_ `void UpdateAngularVelocity_{ParameterName}(in float4 PreviousOrientation, in float4 NodeOrientation, in float DeltaTime, out float3 OutAngularVelocity)` — Update the node angular velocity based on the node orientation difference
- L815-818 _function_ `void ComputeRestPosition_{ParameterName}(in float3 NodePosition, out float3 OutRestPosition)` — Compute rest position
- L821-824 _function_ `void ComputeRestOrientation_{ParameterName}(in float4 NodeOrientation, out float4 OutRestOrientation)` — Compute rest orientation
- L827-830 _function_ `void AttachNodePosition_{ParameterName}(in float3 RestPosition, out float3 OutNodePosition)` — Update Node Position
- L833-836 _function_ `void AttachNodeOrientation_{ParameterName}(in float4 RestOrientation, out float4 OutNodeOrientation)` — Update Node Orientation
- L839-842 _function_ `void GetWorldVector_{ParameterName}(in float3 LocalVector, in bool IsPosition, out float3 OutWorldVector)` — Get World Vector
- L845-848 _function_ `void GetLocalVector_{ParameterName}(in float3 WorldVector, in bool IsPosition, out float3 OutLocalVector)` — Get Local Vector
- L856-865 _function_ `float3 ApplyRBF_{ParameterName}(in float3 RestControlPoint)`
- L868-872 _function_ `void EvalGlobalPosition_{ParameterName}(in float3 RestPosition, out float3 OutGlobalPosition)` — Compute the global position
- L875-885 _function_ `void EvalGlobalOrientation_{ParameterName}(in float3 GlobalPosition, inout float4 OutGlobalOrientation)` — Compute the global position
- L888-907 _function_ `void ComputeLocalState_{ParameterName}(in float3 RestPosition, in float4 RestOrientation, out float3 OutLocalPosition, out float4 OutLocalOrientation)` — Compute rest position and orientation
- L910-928 _function_ `void AttachNodeState_{ParameterName}(in float3 LocalPosition, in float4 LocalOrientation, out float3 OutNodePosition, out float4 OutNodeOrientation)` — Update Node Position and orientation
- L930-942 _function_ `void UpdateNodeState_{ParameterName}(in float3 RestPosition, in float3 NodePosition, in float4 NodeOrientation, out float3 OutNodePosition, out float4 OutNodeOrientation)`
- L949-952 _function_ `void GetNumStrands_{ParameterName}(out int OutNumStrands)`
- L954-957 _function_ `void GetWorldTransform_{ParameterName}(out float4x4 OutWorldTransform)`
- L959-962 _function_ `void GetWorldInverse_{ParameterName}(out float4x4 OutWorldInverse)`
- L964-967 _function_ `void GetStretchScale_{ParameterName}(out float OutStretchScale)`
- L969-972 _function_ `void GetBendScale_{ParameterName}(out float OutBendScale)`
- L974-977 _function_ `void GetRadiusScale_{ParameterName}(out float OutRadiusScale)`
- L979-982 _function_ `void GetThicknessScale_{ParameterName}(out float OutThicknessScale)`
- L984-988 _function_ `void ComputeNodePosition_{ParameterName}(in float SmoothingFilter, out float3 OutNodePosition)`
- L990-1000 _function_ `void ComputeEdgeLength_{ParameterName}(in float3 NodePosition, in int NodeOffset, out float OutEdgeLength)`
- L1002-1008 _function_ `void AdvectNodePosition_{ParameterName}(in float NodeMass, in bool IsPositionMobile, in float3 ExternalForce, in float3 ForceGradient, in float DeltaTime, in float3 LinearVelocity, in float3 NodePosition, out float3 OutLinearVelocity, out float3 OutNodePosition)`
- L1010-1016 _function_ `void AdvectNodeOrientation_{ParameterName}(in float3 NodeInertia, in bool IsOrientationMobile, in float3 ExternalTorque, in float3 TorqueGradient, in float DeltaTime, in float3 AngularVelocity, in float4 NodeOrientation, out float3 OutAngularVelocity, out float4 OutNodeOrientation)`
- L1019-1033 _function_ `void SetupDistanceSpringMaterial_{ParameterName}(in float YoungModulus, in float RodThickness, in float RestLength, in float DeltaTime, in int NodeOffset, in float MaterialDamping, out float OutMaterialCompliance, out float OutMaterialWeight, out float OutMaterialMultiplier)`
- L1035-1049 _function_ `void SolveDistanceSpringMaterial_{ParameterName} (in bool EnableConstraint, in float RestLength, in float DeltaTime, in int NodeOffset, in float MaterialDamping, in float MaterialCompliance, in float MaterialWeight, in float MaterialMultiplier, out float OutMaterialMultiplier)`
- L1051-1065 _function_ `void ProjectDistanceSpringMaterial_{ParameterName} (in bool EnableConstraint, in float YoungModulus, in float RodThickness, in float RestLength, in float DeltaTime, in int NodeOffset, out float3 OutNodePosition)`
- L1067-1070 _function_ `void SetupAngularSpringMaterial_{ParameterName} (in float YoungModulus, in float RodThickness, in float RestLength, in float DeltaTime, in float MaterialDamping, out float OutMaterialCompliance, out float OutMaterialWeight, out float3 OutMaterialMultiplier)`
- L1072-1075 _function_ `void SolveAngularSpringMaterial_{ParameterName} (in bool EnableConstraint, in float RestLength, in float3 RestDirection, in float DeltaTime, in float MaterialDamping, in float MaterialCompliance, in float MaterialWeight, in float3 MaterialMultiplier, out float3 OutMaterialMultiplier)`
- L1077-1080 _function_ `void ProjectAngularSpringMaterial_{ParameterName} (in bool EnableConstraint, in float YoungModulus, in float RodThickness, in float RestLength, in float3 RestDirection, in float DeltaTime, out float3 OutNodePosition)`
- L1082-1085 _function_ `void SetupStretchRodMaterial_{ParameterName} (in float YoungModulus, in float RodThickness, in float RestLength, in float DeltaTime, in float MaterialDamping, out float OutMaterialCompliance, out float OutMaterialWeight, out float3 OutMaterialMultiplier)`
- L1087-1090 _function_ `void SolveStretchRodMaterial_{ParameterName} (in bool EnableConstraint, in float RestLength, in float DeltaTime, in float MaterialDamping, in float MaterialCompliance, in float MaterialWeight, in float3 MaterialMultiplier, out float3 OutMaterialMultiplier)`
- L1092-1095 _function_ `void ProjectStretchRodMaterial_{ParameterName} (in bool EnableConstraint, in float YoungModulus, in float RodThickness, in float RestLength, in float DeltaTime, out float3 OutNodePosition)`
- L1097-1100 _function_ `void SetupBendRodMaterial_{ParameterName} (in float YoungModulus, in float RodThickness, in float RestLength, in float DeltaTime, in float MaterialDamping, out float OutMaterialCompliance, out float OutMaterialWeight, out float3 OutMaterialMultiplier)`
- L1102-1105 _function_ `void SolveBendRodMaterial_{ParameterName} (in bool EnableConstraint, in float RestLength, in float4 RestRotation, in float DeltaTime, in float MaterialDamping, in float MaterialCompliance, in float MaterialWeight, in float3 MaterialMultiplier, out float3 OutMaterialMultiplier)`
- L1107-1110 _function_ `void ProjectBendRodMaterial_{ParameterName} (in bool EnableConstraint, in float YoungModulus, in float RodThickness, in float RestLength, in float4 RestRotation, in float DeltaTime, out float4 OutNodeOrientation)`
- L1112-1116 _function_ `void SolveHardCollisionConstraint_{ParameterName} (in bool EnableConstraint, in float PenetrationDepth, in float3 CollisionPosition, in float3 CollisionVelocity, in float3 CollisionNormal, in float StaticFriction, in float KineticFriction, in float DeltaTime, out float3 OutMaterialMultiplier )`
- L1118-1121 _function_ `void ProjectHardCollisionConstraint_{ParameterName}(in bool EnableConstraint, in float PenetrationDepth, in float3 CollisionPosition, in float3 CollisionVelocity, in float3 CollisionNormal, in float StaticFriction, in float KineticFriction, in float DeltaTime, out float3 OutNodePosition)`
- L1123-1129 _function_ `void SolveSoftCollisionConstraint_{ParameterName} (in bool EnableConstraint, in float PenetrationDepth, in float3 CollisionPosition, in float3 CollisionVelocity, in float3 CollisionNormal, in float StaticFriction, in float KineticFriction, in float DeltaTime, in float MaterialDamping, in float MaterialCompliance, in float MaterialWeight, in float3 MaterialMultiplier, out float3 OutMaterialMultiplier )`
- L1131-1134 _function_ `void ProjectSoftCollisionConstraint_{ParameterName} (in bool EnableConstraint, in float ConstraintStiffness, in float PenetrationDepth, in float3 CollisionPosition, in float3 CollisionVelocity, in float3 CollisionNormal, in float StaticFriction, in float KineticFriction, in float DeltaTime, out float3 OutNodePosition )`
- L1136-1139 _function_ `void SetupSoftCollisionConstraint_{ParameterName} (in float ConstraintStiffness, in float DeltaTime, in float MaterialDamping, out float OutMaterialCompliance, out float OutMaterialWeight, out float3 OutMaterialMultiplier )`
- L1141-1145 _function_ `void UpdateMaterialFrame_{ParameterName} (out float4 OutNodeOrientation)`
- L1147-1151 _function_ `void ComputeMaterialFrame_{ParameterName} ( out float4 OutNodeOrientation)`
- L1153-1156 _function_ `void ComputeAirDragForce_{ParameterName}(in float AirDensity, in float AirViscosity, in float AirDrag, in float3 AirVelocity, in float NodeThickness, in float3 NodePosition, in float3 NodeVelocity, out float3 OutAirDrag, out float3 OutDragGradient)`
- L1158-1161 _function_ `void NeedSimulationReset_{ParameterName} ( out bool ResetSimulation)`
- L1163-1166 _function_ `void HasGlobalInterpolation_{ParameterName}(out bool GlobalInterpolation)`
- L1168-1171 _function_ `void NeedRestUpdate_{ParameterName}( out bool RestUpdate)`

### `Plugins/Runtime/HairStrands/Shaders/Private/NiagaraDataInterfacePressureGrid.ush` (Private)

- lines: 16; parse: all-branches
- L7 #pragma `once`

#### static const (6)

- L9 _static_const_ `static const int FLUID_PRESSURE_OFFSET = 6;`
- L10 _static_const_ `static const int SOLID_WEIGHT_OFFSET = 7;`
- L11 _static_const_ `static const int SOLID_VELOCITY_OFFSET = 10;`
- L12 _static_const_ `static const int SOLID_DISTANCE_OFFSET = 13;`
- L13 _static_const_ `static const int FLUID_DISTANCE_OFFSET = 14;`
- L14 _static_const_ `static const int FLUID_DENSITY_OFFSET = 15;`

### `Plugins/Runtime/HairStrands/Shaders/Private/NiagaraDataInterfacePressureGridTemplate.ush` (Private)

- lines: 549; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Functions (19)

- L12-32 _function_ `void ScaleCellDistance_{ParameterName}(in int3 GridIndex, in float GridLength )`
- L34-43 _function_ `void ScaleFaceVelocity_{ParameterName}(in int3 GridIndex, in int ComponentIndex)`
- L45-76 _function_ `void ScaleCellFields_{ParameterName}(in int GridHash, in float GridLength, in float DeltaTime, out bool OutTransferStatus)`
- L84-108 _function_ `void BuildDistanceField_{ParameterName}(in float3 GridOrigin, in float GridLength, in float3 ParticlePosition, out bool OutFunctionStatus )` — Compute the distance from the particle to the grid
- L111-142 _function_ `void BuildDensityField_{ParameterName}(in float3 GridOrigin, in float GridLength, in float3 ParticlePosition, in float ParticleMass, in float ParticleDensity, out bool OutFunctionStatus )` — Transfer the density from the particle to the grid
- L150-183 _function_ `void GetDensityField_{ParameterName}(in float3 GridOrigin, in float GridLength, in float3 ParticlePosition, out float OutParticleDensity)` — Sample the grid velocity field and gradient at the particle world position
- L186-209 _function_ `void UpdateDeformationGradient_{ParameterName}(in float DeltaTime, in float4x4 VelocityGradient, in float4x4 DeformationGradient, out float4x4 OutDeformationGradient, out float OutGradientDeterminant)` — Sample the grid velocity field and gradient at the particle world position
- L216-223 _function_ `float GetFractionInsideEdge_{ParameterName}(in float SignedDistanceA, in float SignedDistanceB)`
- L225-230 _function_ `float GetFractionInsideImplA_{ParameterName}(in float SignedDistanceA, in float SignedDistanceB, in float SignedDistanceD)`
- L232-237 _function_ `float GetFractionInsideImplB_{ParameterName}(in float SignedDistanceA, in float SignedDistanceB, in float SignedDistanceC, in float SignedDistanceD)`
- L239-271 _function_ `float GetFractionInsideImplC_{ParameterName}(in float SignedDistanceA, in float SignedDistanceB, in float SignedDistanceC, in float SignedDistanceD)`
- L273-278 _function_ `float GetFractionInsideImplD_{ParameterName}(in float SignedDistanceA, in float SignedDistanceB, in float SignedDistanceD)`
- L280-363 _function_ `float GetFractionInsideFace_{ParameterName}(in float SignedDistanceA, in float SignedDistanceB, in float SignedDistanceC, in float SignedDistanceD )`
- L366-378 _function_ `void SetSolidBoundary_{ParameterName}(in int GridHash, in float SolidDistance, in float3 SolidVelocity, out bool OutBoundaryStatus)` — Update the solid weights and velocities
- L380-384 _function_ `void ComputeFaceWeights_{ParameterName}(in int3 GridLocation, in int ComponentIndex, out float SignedDistance, inout float ParticleVelocity )`
- L386-423 _function_ `void ComputeComponentWeights_{ParameterName}(in int3 GridIndex, in int ComponentIndex)`
- L426-434 _function_ `void ComputeBoundaryWeights_{ParameterName}(in int GridHash, out bool OutWeightsStatus)` — Update the solid weights and velocities
- L452-484 _function_ `float ComputeGridPressure_{ParameterName}(in int3 PrevIndex, in float CentreDistance, out float3 PrevFraction, out float3 NextFraction)`
- L487-548 _function_ `void SolveGridPressure_{ParameterName}(in int GridHash, in int InitStage, out bool OutProjectStatus)` — Project the pressure grid to be divergence free

### `Plugins/Runtime/HairStrands/Shaders/Private/NiagaraDataInterfaceVelocityGrid.ush` (Private)

- lines: 15; parse: all-branches

#### Macros (#define, 1)

- L9 `#define FAST_MODE 1`
- L7 #pragma `once`

#### static const (3)

- L11 _static_const_ `static const float FLOAT_PRECISION = 1e+4;`
- L13 _static_const_ `static const int FLUID_MASS_OFFSET = 0;`
- L14 _static_const_ `static const int FLUID_VELOCITY_OFFSET = 3;`

### `Plugins/Runtime/HairStrands/Shaders/Private/NiagaraDataInterfaceVelocityGridTemplate.ush` (Private)

- lines: 558; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)

#### Global resources (textures / buffers / samplers) (2)

- L6 _resource_ `Buffer<int> {ParameterName}_GridCurrentBuffer;`
- L7 _resource_ `RWBuffer<int> {ParameterName}_GridDestinationBuffer;`

#### Global parameters (uniforms) (3)

- L3 _parameter_ `float4x4 {ParameterName}_WorldTransform;`
- L4 _parameter_ `float4x4 {ParameterName}_WorldInverse;`
- L5 _parameter_ `int3 {ParameterName}_GridSize;`

#### Functions (37)

- L15-29 _function_ `void ComputeGridSize_{ParameterName}(in float3 GridCenter, in float3 GridExtent, out float3 OutGridOrigin, out float OutGridLength)` — Compute the grid origin and grid length
- L32-35 _function_ `float3 GetGridPosition_{ParameterName}(in float3 ParticlePosition, in float3 GridOrigin)` — Transform the node world position in grid space
- L43-48 _function_ `bool IsCellValid_{ParameterName}(in int3 CellIndex)` — Return true if the grid cell index is in any voxel center (0,N-1)
- L51-68 _function_ `bool IsFaceValid_{ParameterName}(in int3 FaceIndex, in int ComponentIndex)` — Return true if the grid face index is for the component one (0,N) and in the voxel center for the others (0,N-1)
- L71-76 _function_ `bool IsNodeValid_{ParameterName}(in int3 NodeIndex)` — Return true if the grid node index is valid (0,N)
- L79-96 _function_ `bool IsFaceInside_{ParameterName}(in int3 FaceIndex, in int ComponentIndex)` — Return true if the grid face index is inside the grid
- L98-103 _function_ `bool IsCellInside_{ParameterName}(in int3 CellIndex)`
- L105-110 _function_ `bool IsNodeInside_{ParameterName}(in int3 NodeIndex)`
- L118-125 _function_ `int3 ComputeGridIndex_{ParameterName}(in float3 GridPosition, in float3 GridOffset, in float GridLength, out float3 OutGridFraction)` — Compute the grid index and fraction given a grid position and a grid offset
- L128-134 _function_ `int3 GetGridIndex_{ParameterName}(in int GridHash)` — Compute the grid index given a grid hash
- L142-155 _function_ `void GetFacePosition_{ParameterName}(in int GridHash, in float3 GridOrigin, in float GridLength, in int ComponentIndex, out float3 OutFacePosition)` — Compute the world face position
- L158-170 _function_ `void GetCellPosition_{ParameterName}(in int GridHash, in float3 GridOrigin, in float GridLength, out float3 OutCellPosition)` — Compute the world cell position
- L173-185 _function_ `void GetNodePosition_{ParameterName}(in int GridHash, in float3 GridOrigin, in float GridLength, out float3 OutNodePosition)` — Compute the world node position
- L193-197 _function_ `int GetDataIndex_{ParameterName}(in int3 GridIndex, in int DataOffset)` — Compute the data index from agrid index and a data offset
- L201-204 _function_ `void InterlockedAddInt_{ParameterName}(in int3 GridIndex, in int DataOffset, in int IntValue)` _[#if FAST_MODE == 1]_
- L206-209 _function_ `void InterlockedMinInt_{ParameterName}(in int3 GridIndex, in int DataOffset, in int IntValue)` _[#if FAST_MODE == 1]_
- L213-229 _function_ `void InterlockedAddFloat_{ParameterName}(in int3 GridIndex, in int DataOffset, in float FloatValue)` _[#if !(FAST_MODE == 1)]_
- L231-247 _function_ `void InterlockedMinFloat_{ParameterName}(in int3 GridIndex, in int DataOffset, in float FloatValue)` _[#if !(FAST_MODE == 1)]_
- L256-264 _function_ `void InterlockedMinScalar_{ParameterName}(in int3 GridIndex, in int DataOffset, in float FloatValue)`
- L266-274 _function_ `void InterlockedAddScalar_{ParameterName}(in int3 GridIndex, in int DataOffset, in float FloatValue)`
- L276-285 _function_ `float ConvertGridScalar_{ParameterName}(in int3 GridIndex, in int DataOffset)`
- L287-291 _function_ `void AddGridScalar_{ParameterName}(in int3 GridIndex, in int DataOffset, in float FloatValue)`
- L293-296 _function_ `float GetGridScalar_{ParameterName}(in int3 GridIndex, in int DataOffset)`
- L298-301 _function_ `void SetGridScalar_{ParameterName}(in int3 GridIndex, in int DataOffset, in float FloatValue)`
- L303-308 _function_ `void SetGridVector_{ParameterName}(in int3 GridIndex, in int DataOffset, in float3 NodeVector)`
- L310-315 _function_ `void AddGridVector_{ParameterName}(in int3 GridIndex, in int DataOffset, in float3 NodeVector)`
- L317-322 _function_ `float3 GetGridVector_{ParameterName}(in int3 GridIndex, in int DataOffset)`
- L329-336 _function_ `float GetShapeFunction_{ParameterName}( in float3 GridFraction, in int3 ijk)`
- L338-351 _function_ `float3 GetShapeGradient_{ParameterName}( in float3 GridFraction, in int3 ijk)`
- L359-371 _function_ `void BuildVelocityFace_{ParameterName}(in int3 GridIndex, in float ShapeFunction, in int3 ijk, in float3 GridPosition, in float SampleMass, in float SampleMomentum, in float3 MomentumGradient, in float3 ComponentOffset, in int ComponentIndex, in float GridLength )` — Transfer the velocity field component on a face from the particle to the grid
- L374-396 _function_ `void BuildVelocityComponent_{ParameterName}(in float3 GridPosition, in float SampleMass, in float SampleMomentum, in float3 MomentumGradient, in float3 ComponentOffset, in int ComponentIndex, in float GridLength )` — Transfer the velocity field component from the particle to the grid
- L399-419 _function_ `void BuildVelocityField_{ParameterName}(in float3 GridOrigin, in float GridLength, in float3 ParticlePosition, in float ParticleMass, in float3 ParticleVelocity, in float4x4 VelocityGradient, out bool OutFunctionStatus )` — Transfer the velocity field from the particle to the grid
- L427-454 _function_ `void SampleVelocityFace_{ParameterName}(in int3 GridIndex, in float ShapeFunction, in float3 ShapeGradient, in int3 ijk, in float3 GridPosition, in float3 ComponentOffset, in int ComponentIndex, in float GridLength, in bool ScaledVelocity, inout float OutGridVelocity, inout float OutGridMass, inout float3 OutGridGradient)` — Sample the grid velocity field and gradient component on a face at the particle local position
- L457-493 _function_ `void SampleVelocityComponent_{ParameterName}(in float3 GridPosition, in float3 ComponentOffset, in int ComponentIndex, in float GridLength, in bool ScaledVelocity, out float OutGridVelocity, out float OutGridMass, out float3 OutGridGradient)` — Sample the grid velocity field and gradient component at the particle local position
- L496-510 _function_ `void SampleVelocityField_{ParameterName}(in float3 GridOrigin, in float GridLength, in float3 ParticlePosition, in bool ScaledVelocity, out float OutParticleMass, out float3 OutParticleVelocity, out float4x4 OutParticleGradient)` — Sample the grid velocity field and gradient at the particle world position
- L517-537 _function_ `void AddGridVelocity_{ParameterName}(in int GridHash, in float3 GridVelocity, out bool OutAddStatus)`
- L539-557 _function_ `void GetGridVelocity_{ParameterName}(in int GridHash, out float3 OutGridVelocity)`

### `Plugins/Runtime/HairStrands/Shaders/Private/NiagaraDirectSolver.ush` (Private)

- lines: 300; parse: all-branches

#### groupshared (2)

- L14 _groupshared_ `groupshared float4 SharedTridiagValues[THREADGROUP_SIZE];` _[#if GPU_SIMULATION]_
- L15 _groupshared_ `groupshared float4 SharedTridiagResult[THREADGROUP_SIZE];` _[#if GPU_SIMULATION]_

#### Functions (6)

- L17-48 _function_ `void SolveTridiagSerial2()` _[#if GPU_SIMULATION]_
- L50-76 _function_ `void SolveTridiagSerial()` _[#if GPU_SIMULATION]_
- L78-144 _function_ `void SolveConjugateResidual()` _[#if GPU_SIMULATION]_
- L147-204 _function_ `void SolveConjugateGradient()` _[#if GPU_SIMULATION]_
- L206-250 _function_ `void SolveTridiagSystem()` _[#if GPU_SIMULATION]_
- L252-298 _function_ `float SolveTridiag()` _[#if GPU_SIMULATION]_

### `Plugins/Runtime/HairStrands/Shaders/Private/NiagaraElasticRodMaterial.ush` (Private)

- lines: 228; parse: unbalanced
- L3 #pragma `once`

#### Functions (13)

- L10-14 _function_ `float4 AddTwistRotation(in float4 RefOrientation, in float TwistAngle)`
- L16-22 _function_ `float3 ComputeReferenceTangent(in float4 RefOrientation)`
- L24-30 _function_ `float3 ComputeReferenceNormalX(in float4 RefOrientation)`
- L32-38 _function_ `float3 ComputeReferenceNormalY(in float4 RefOrientation)`
- L40-45 _function_ `float GetSignedAngle( in float3 RefNormalX, in float3 RefNormalY, in float3 RefTangent)`
- L52-59 _function_ `float4 ComputeReferenceFrame(in int FrameOffset)`
- L61-64 _function_ `float3 ComputeCurvatureBinormal(const float3 PrevReferenceTangent, const float3 NextReferenceTangent)`
- L66-72 _function_ `void UpdateReferenceTwist(const float3 PrevReferenceTangent, const float3 NextReferenceTangent, const float4 PrevReferenceFrame, const float4 NextReferenceFrame, inout float RefTwist)`
- L74-81 _function_ `float2 ComputeRodKappa( in float3 CurvatureBinormal, in float3 PrevMaterialNormalX, in float3 PrevMaterialNormalY, in float3 NextMaterialNormalX, in float3 NextMaterialNormalY)`
- L83-114 _function_ `void ComputeKappaGradient( in float3 CurvatureBinormal, in float2 RodKappa, in float3 PrevReferenceTangent, in float3 PrevMaterialNormalX, in float3 PrevMaterialNormalY, in float3 NextReferenceTangent, in float3 NextMaterialNormalX, in float3 NextMaterialNormalY, out float3 KappaGradients[3][2])`
- L121-182 _function_ `void UpdateElasticRodMultiplier( in float RestLength, in float DeltaTime, in bool ProjectConstraint, in float MaterialDamping, in float MaterialCompliance, in float MaterialWeight, inout float3 OutMaterialMultiplier)`
- L184-205 _function_ `void SolveElasticRodMaterial(in int StrandsSize, in float RestLength, in float DeltaTime, in float MaterialDamping, in float MaterialCompliance, in float MaterialWeight, in float3 MaterialMultiplier, out float3 OutMaterialMultiplier)`
- L207-227 _function_ `void ProjectElasticRodMaterial(in int StrandsSize, in float YoungModulus, in float RodThickness, in float RestLength, in float DeltaTime, out float3 OutMaterialMultiplier)`

### `Plugins/Runtime/HairStrands/Shaders/Private/NiagaraGroomInterpolationUtils.ush` (Private)

- lines: 50; parse: all-branches
- includes: L9 `/Plugin/FX/Niagara/Private/NiagaraQuaternionUtils.ush`
- L7 #pragma `once`

#### Functions (5)

- L12-26 _function_ `void DIHairStrands_ComputeProjectionTriangle(in float2 ProjectionUV, in float3 PA, in float3 PB, in float3 PC, in float3 Offset, out float3 OutTrianglePosition, out float4 OutTriangleRotation)` — Compute the projection triangle
- L29-32 _function_ `float3 DIHairStrands_TriangleLocalPosition(in float3 TrianglePosition, in float4 TriangleRotation, in float3 WorldPosition)` — Eval the triangle local position
- L35-38 _function_ `float4 DIHairStrands_TriangleLocalOrientation(in float3 TrianglePosition, in float4 TriangleRotation, in float4 WorldOrientation)` — Eval the triangle local orientation
- L41-44 _function_ `float3 DIHairStrands_TriangleWorldPosition(in float3 TrianglePosition, in float4 TriangleRotation, in float3 LocalPosition)` — Eval the triangle world position
- L47-50 _function_ `float4 DIHairStrands_TriangleWorldOrientation(in float3 TrianglePosition, in float4 TriangleRotation, in float4 LocalOrientation)` — Eval the triangle local orientation

### `Plugins/Runtime/HairStrands/Shaders/Private/NiagaraHookeSpringMaterial.ush` (Private)

- lines: 263; parse: all-branches
- L3 #pragma `once`

#### Functions (11)

- L10-25 _function_ `void ResetStretchSpringMaterial(in int StrandsSize, in float YoungModulus, in float RodThickness, in float RestLength, in float DeltaTime, in bool ProjectConstraint, in float MaterialDamping, out float OutMaterialCompliance, out float OutMaterialWeight, out float OutMaterialMultiplier, in int NodeOffset)`
- L28-52 _function_ `void UpdateStretchSpringMultiplier(in float RestLength, in float DeltaTime, in bool ProjectConstraint, in float MaterialDamping, in float MaterialCompliance, in float MaterialWeight, inout float OutMaterialMultiplier, in int NodeOffset)`
- L54-65 _function_ `void SetupStretchSpringMaterial(in int StrandsSize, in float YoungModulus, in float RodThickness, in float RestLength, in float DeltaTime, in bool ProjectConstraint, in float MaterialDamping, out float OutMaterialCompliance, out float OutMaterialWeight, out float OutMaterialMultiplier)`
- L67-91 _function_ `void SolveStretchSpringMaterial(in bool EnableConstraint, in int StrandsSize, in float RestLength, in float DeltaTime, in float MaterialDamping, in float MaterialCompliance, in float MaterialWeight, in float MaterialMultiplier, out float OutMaterialMultiplier)`
- L93-119 _function_ `void ProjectStretchSpringMaterial(in bool EnableConstraint, in int StrandsSize, in float YoungModulus, in float RodThickness, in float RestLength, in float DeltaTime, out float3 OutNodePosition)`
- L126-137 _function_ `void SetupBendSpringMaterial(in int StrandsSize, in float YoungModulus, in float RodThickness, in float RestLength, in float DeltaTime, in bool ProjectConstraint, in float MaterialDamping, out float OutMaterialCompliance, out float OutMaterialWeight, out float OutMaterialMultiplier)`
- L139-163 _function_ `void SolveBendSpringMaterial(in bool EnableConstraint, in int StrandsSize, in float RestLength, in float DeltaTime, in float MaterialDamping, in float MaterialCompliance, in float MaterialWeight, in float MaterialMultiplier, out float OutMaterialMultiplier)`
- L165-190 _function_ `void ProjectBendSpringMaterial(in bool EnableConstraint, in int StrandsSize, in float YoungModulus, in float RodThickness, in float RestLength, in float DeltaTime, out float3 OutNodePosition)`
- L197-208 _function_ `void SetupTwistSpringMaterial(in int StrandsSize, in float YoungModulus, in float RodThickness, in float RestLength, in float DeltaTime, in bool ProjectConstraint, in float MaterialDamping, out float OutMaterialCompliance, out float OutMaterialWeight, out float OutMaterialMultiplier)`
- L210-234 _function_ `void SolveTwistSpringMaterial(in bool EnableConstraint, in int StrandsSize, in float RestLength, in float DeltaTime, in float MaterialDamping, in float MaterialCompliance, in float MaterialWeight, in float MaterialMultiplier, out float OutMaterialMultiplier)`
- L236-262 _function_ `void ProjectTwistSpringMaterial(in bool EnableConstraint, in int StrandsSize, in float YoungModulus, in float RodThickness, in float RestLength, in float DeltaTime, out float3 OutNodePosition)`

### `Plugins/Runtime/HairStrands/Shaders/Private/NiagaraInterpolateGroomGuides.usf` (Private)

- lines: 153; parse: all-branches
- includes: L12 `/Engine/Public/Platform.ush`, L13 `/Engine/Private/HairStrands/HairStrandsPack.ush`, L17 `NiagaraGroomInterpolationUtils.ush` [PERMUTATION_INTERPOLATION == LOCAL_INTERPOLATION]

#### Macros (#define, 2)

- L9 `#define LOCAL_INTERPOLATION 0`
- L10 `#define WORLD_INTERPOLATION 1`
- L7 #pragma `once`

#### Entry points (1)

- L69-152 _entry_ `[numthreads(THREAD_COUNT, 1, 1)] void MainCS(uint3 DispatchThreadId : SV_DispatchThreadID)` — stage: **compute** — C++: `FInterpolateGroomGuidesCS` SF_Compute via IMPLEMENT_SHADER_TYPE (Plugins/Runtime/HairStrands/Source/HairStrandsCore/Private/Niagara/NiagaraDataInterfaceHairStrands.cpp:1000)

#### Global resources (textures / buffers / samplers) (10)

- L19 _resource_ `Buffer<float4> RestTrianglePositionBuffer;` _[#if PERMUTATION_INTERPOLATION == LOCAL_INTERPOLATION]_
- L20 _resource_ `Buffer<float4> DeformedTrianglePositionBuffer;` _[#if PERMUTATION_INTERPOLATION == LOCAL_INTERPOLATION]_
- L21 _resource_ `Buffer<uint> RootBarycentricCoordinatesBuffer;` _[#if PERMUTATION_INTERPOLATION == LOCAL_INTERPOLATION]_
- L22 _resource_ `Buffer<uint> RootToUniqueTriangleIndexBuffer;` _[#if PERMUTATION_INTERPOLATION == LOCAL_INTERPOLATION]_
- L26 _resource_ `ByteAddressBuffer PointToCurveIndexBuffer;`
- L27 _resource_ `RWByteAddressBuffer DeformedPositionBuffer;`
- L28 _resource_ `ByteAddressBuffer RestPositionBuffer;`
- L29 _resource_ `ByteAddressBuffer CurvesOffsetsBuffer;`
- L30 _resource_ `StructuredBuffer<float4> DeformedPositionOffset;`
- L37 _resource_ `Buffer<float> NiagaraFloatBuffer;`

#### Global parameters (uniforms) (7)

- L31 _parameter_ `float3 RestPositionOffset;`
- L32 _parameter_ `float4x4 WorldToLocal;`
- L34 _parameter_ `int StrandsSize;`
- L35 _parameter_ `int NumPoints;`
- L38 _parameter_ `int NiagaraFloatStride;`
- L40 _parameter_ `int NodePositionComponent;`
- L41 _parameter_ `int RestPositionComponent;`

#### Functions (2)

- L46-54 _function_ `void DIHairStrands_BuildDeformedTriangle(in float2 ProjectionUV, in uint TriangleIndex, in int StrandIndex, out float3 OutTrianglePosition, out float4 OutTriangleRotation)` — Get the deformed triangle _[#if PERMUTATION_INTERPOLATION == LOCAL_INTERPOLATION]_
- L57-65 _function_ `void DIHairStrands_BuildRestTriangle(in float2 ProjectionUV, in uint TriangleIndex, in int StrandIndex, out float3 OutTrianglePosition, out float4 OutTriangleRotation)` — Get the rest triangle _[#if PERMUTATION_INTERPOLATION == LOCAL_INTERPOLATION]_

### `Plugins/Runtime/HairStrands/Shaders/Private/NiagaraStaticCollisionConstraint.ush` (Private)

- lines: 206; parse: all-branches
- L3 #pragma `once`

#### Functions (8)

- L10-49 _function_ `bool ComputeCollisionDatas( in float3 DeltaPosition, in float3 DeltaVelocity, in float3 CollisionNormal, in float PenetrationDepth, in float StaticFriction, in float KineticFriction, in bool IsProjection, inout float DeltaFNormal, inout float AlphaTangentA, inout float DeltaVTangentA, inout float3 CollisionTangentA, inout float AlphaTangentB, inout float DeltaVTangentB, inout float3 CollisionTangentB)`
- L56-74 _function_ `void UpdateHardCollisionConstraint( in float3 DeltaPosition, in float3 DeltaVelocity, in float3 CollisionNormal, in float PenetrationDepth, in float StaticFriction, in float KineticFriction, in bool IsProjection)`
- L76-88 _function_ `void SolveHardCollisionConstraint(in bool EnableConstraint, in int StrandsSize, in float PenetrationDepth, in float3 CollisionPosition, in float3 CollisionVelocity, in float3 CollisionNormal, in float StaticFriction, in float KineticFriction, in bool IsProjection, in float DeltaTime )`
- L90-101 _function_ `void ProjectHardCollisionConstraint(in bool EnableConstraint, in int StrandsSize, in float PenetrationDepth, in float3 CollisionPosition, in float3 CollisionVelocity, in float3 CollisionNormal, in float StaticFriction, in float KineticFriction, in float DeltaTime, out float3 OutNodePosition )`
- L109-150 _function_ `void UpdateSoftCollisionConstraint(in float3 DeltaPosition, in float3 DeltaVelocity, in float3 CollisionNormal, in float PenetrationDepth, in float StaticFriction, in float KineticFriction, in bool IsProjection, in float DeltaTime, in float MaterialDamping, in float MaterialCompliance, in float MaterialWeight, inout float3 OutMaterialMultiplier )`
- L152-164 _function_ `void SetupSoftCollisionConstraint(in int StrandsSize, in float ConstraintStiffness, in float DeltaTime, in float MaterialDamping, out float OutMaterialCompliance, out float OutMaterialWeight, out float3 OutMaterialMultiplier)`
- L166-183 _function_ `void SolveSoftCollisionConstraint(in bool EnableConstraint, in int StrandsSize, in float PenetrationDepth, in float3 CollisionPosition, in float3 CollisionVelocity, in float3 CollisionNormal, in float StaticFriction, in float KineticFriction, in bool IsProjection, in float DeltaTime, in float MaterialDamping, in float MaterialCompliance, in float MaterialWeight, in float3 MaterialMultiplier, out float3 OutMaterialMultiplier )`
- L185-203 _function_ `void ProjectSoftCollisionConstraint(in bool EnableConstraint, in int StrandsSize, in float ConstraintStiffness, in float PenetrationDepth, in float3 CollisionPosition, in float3 CollisionVelocity, in float3 CollisionNormal, in float StaticFriction, in float KineticFriction, in float DeltaTime, out float3 OutNodePosition )`

### `Plugins/Runtime/HairStrands/Shaders/Private/NiagaraStrandsExternalForce.ush` (Private)

- lines: 69; parse: all-branches
- L7 #pragma `once`

#### Functions (1)

- L17-59 _function_ `void ComputeAirDragForce(in int StrandSize, in float AirDensity, in float AirViscosity, in float AirDrag, in float3 AirVelocity, in float NodeThickness, in float3 NodePosition, in float3 NodeVelocity, out float3 OutAirDrag, out float3 OutForceGradient)` — Air Density = 1 kg/m3 = 1e-3 g/cm3 Dynamic Viscosity = 1e-5 Pa.s = 1e-6 g/(cm.s) Compute air drag force
