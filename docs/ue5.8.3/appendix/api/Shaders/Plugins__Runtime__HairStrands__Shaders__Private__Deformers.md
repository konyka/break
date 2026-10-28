# Shaders / Plugins/Runtime/HairStrands/Shaders/Private/Deformers

- files: 9; lines: 974
- record kinds: define=2, function=98, include=24, macro_call=2, member=2, parameter=48, resource=37, struct=1

### `Plugins/Runtime/HairStrands/Shaders/Private/Deformers/DeformerGroomAttributeRead.ush` (Private)

- lines: 129; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)
- includes: L3 `/Plugin/ComputeFramework/Private/ComputeKernelCommon.ush`, L4 `/Engine/Private/HairStrands/HairStrandsPack.ush`

#### Global resources (textures / buffers / samplers) (2)

- L11 _resource_ `StructuredBuffer<float> {DataInterfaceName}_ValueTypedData;`
- L13 _resource_ `ByteAddressBuffer {DataInterfaceName}_IndexMappingBuffer;`

#### Global parameters (uniforms) (4)

- L6 _parameter_ `uint {DataInterfaceName}_NumValues;`
- L7 _parameter_ `uint {DataInterfaceName}_BaseValueIndex;`
- L8 _parameter_ `uint {DataInterfaceName}_TotalValueCount;`
- L9 _parameter_ `uint {DataInterfaceName}_bHasIndexMapping;`

#### Functions (14)

- L17-22 _function_ `uint GetAttributeIndex_{DataInterfaceName}(uint GlobalIndex)`
- L26-29 _function_ `uint ReadNumValues_{DataInterfaceName}()`
- L31-35 _function_ `uint ReadValueTypedUint_{DataInterfaceName}(uint ValueIndex)`
- L37-41 _function_ `bool ReadValueTypedBool_{DataInterfaceName}(uint ValueIndex)`
- L43-47 _function_ `int ReadValueTypedInt_{DataInterfaceName}(uint ValueIndex)`
- L49-54 _function_ `int2 ReadValueTypedInt2_{DataInterfaceName}(uint ValueIndex)`
- L56-61 _function_ `int3 ReadValueTypedInt3_{DataInterfaceName}(uint ValueIndex)`
- L63-69 _function_ `int4 ReadValueTypedInt4_{DataInterfaceName}(uint ValueIndex)`
- L71-75 _function_ `float ReadValueTypedFloat_{DataInterfaceName}(uint ValueIndex)`
- L77-83 _function_ `float2 ReadValueTypedFloat2_{DataInterfaceName}(uint ValueIndex)`
- L85-90 _function_ `float3 ReadValueTypedFloat3_{DataInterfaceName}(uint ValueIndex)`
- L92-98 _function_ `float4 ReadValueTypedFloat4_{DataInterfaceName}(uint ValueIndex)`
- L100-113 _function_ `float4x4 ReadValueTypedFloat4x4_{DataInterfaceName}(uint ValueIndex)`
- L115-125 _function_ `float3x4 ReadValueTypedFloat3x4_{DataInterfaceName}(uint ValueIndex)`

### `Plugins/Runtime/HairStrands/Shaders/Private/Deformers/DeformerGroomCollisionRead.ush` (Private)

- lines: 47; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)
- includes: L3 `/Plugin/ComputeFramework/Private/ComputeKernelCommon.ush`

#### Global resources (textures / buffers / samplers) (2)

- L14 _resource_ `Buffer<float> {DataInterfaceName}_VertexGlobalPositions;`
- L15 _resource_ `Buffer<uint> {DataInterfaceName}_TriangleVertexIndices;`

#### Global parameters (uniforms) (8)

- L5 _parameter_ `uint {DataInterfaceName}_NumVertices;`
- L6 _parameter_ `uint {DataInterfaceName}_NumTriangles;`
- L7 _parameter_ `uint {DataInterfaceName}_VertexOffset;`
- L8 _parameter_ `uint {DataInterfaceName}_TriangleOffset;`
- L9 _parameter_ `uint {DataInterfaceName}_TotalNumVertices;`
- L10 _parameter_ `uint {DataInterfaceName}_TotalNumTriangles;`
- L11 _parameter_ `uint {DataInterfaceName}_BaseVertexIndex;`
- L12 _parameter_ `uint {DataInterfaceName}_BaseTriangleIndex;`

#### Functions (4)

- L19-22 _function_ `uint ReadNumVertices_{DataInterfaceName}()`
- L24-27 _function_ `uint ReadNumTriangles_{DataInterfaceName}()`
- L29-35 _function_ `float3 ReadVertexGlobalPosition_{DataInterfaceName}(uint VertexIndex)`
- L37-45 _function_ `uint3 ReadTriangleVertexIndices_{DataInterfaceName}(uint TriangleIndex)`

### `Plugins/Runtime/HairStrands/Shaders/Private/Deformers/DeformerGroomDomainsExec.ush` (Private)

- lines: 11; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)
- includes: L3 `/Plugin/ComputeFramework/Private/ComputeKernelCommon.ush`

#### Global parameters (uniforms) (1)

- L5 _parameter_ `int3 {DataInterfaceName}_NumThreads;`

#### Functions (1)

- L7-10 _function_ `int3 ReadNumThreads_{DataInterfaceName}()`

### `Plugins/Runtime/HairStrands/Shaders/Private/Deformers/DeformerGroomGuidesRead.ush` (Private)

- lines: 124; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)
- includes: L3 `/Plugin/ComputeFramework/Private/ComputeKernelCommon.ush`, L4 `/Engine/Private/HairStrands/HairStrandsVertexFactoryCommon.ush`, L5 `/Engine/Private/HairStrands/HairStrandsAttributeCommon.ush`, L6 `/Engine/Private/HairStrands/HairStrandsBindingCommon.ush`

#### Global resources (textures / buffers / samplers) (7)

- L17 _resource_ `ByteAddressBuffer {DataInterfaceName}_PointRestPositions;`
- L18 _resource_ `ByteAddressBuffer {DataInterfaceName}_CurvePointOffsets;`
- L19 _resource_ `ByteAddressBuffer {DataInterfaceName}_PointCurveIndices;`
- L30 _resource_ `Buffer<float4> {DataInterfaceName}_TriangleRestPositions;` _[#if ENABLE_SKINNED_TRANSFORM == 1]_
- L31 _resource_ `Buffer<float4> {DataInterfaceName}_TriangleDeformedPositions;` _[#if ENABLE_SKINNED_TRANSFORM == 1]_
- L32 _resource_ `Buffer<uint> {DataInterfaceName}_CurveBarycentricCoordinates;` _[#if ENABLE_SKINNED_TRANSFORM == 1]_
- L33 _resource_ `Buffer<uint> {DataInterfaceName}_CurveTriangleIndices;` _[#if ENABLE_SKINNED_TRANSFORM == 1]_

#### Global parameters (uniforms) (10)

- L8 _parameter_ `uint {DataInterfaceName}_PointCount;`
- L9 _parameter_ `uint {DataInterfaceName}_CurveCount;`
- L10 _parameter_ `uint {DataInterfaceName}_BasePointIndex;`
- L11 _parameter_ `uint {DataInterfaceName}_BaseCurveIndex;`
- L12 _parameter_ `uint {DataInterfaceName}_TotalPointCount;`
- L13 _parameter_ `uint {DataInterfaceName}_TotalCurveCount;`
- L14 _parameter_ `uint {DataInterfaceName}_ObjectIndex;`
- L15 _parameter_ `float3 {DataInterfaceName}_RestPositionOffset;`
- L21 _parameter_ `float4x4 {DataInterfaceName}_ObjectRestTransform;`
- L22 _parameter_ `float4x4 {DataInterfaceName}_ObjectDeformedTransform;`

#### Functions (13)

- L24-27 _function_ `float3x4 BuildRigidTransform(float4x4 RigidTransform)`
- L35-46 _function_ `float3x4 BuildGuidesSkinnedTransform(uint CurveIndex, Buffer<float4> TrianglePositions, Buffer<uint> BarycentricCoordinates, Buffer<uint> TriangleIndices)` _[#if ENABLE_SKINNED_TRANSFORM == 1]_
- L51-54 _function_ `uint ReadNumPoints_{DataInterfaceName}()`
- L56-59 _function_ `uint ReadNumCurves_{DataInterfaceName}()`
- L61-64 _function_ `uint ReadObjectIndex_{DataInterfaceName}()`
- L66-70 _function_ `float3 ReadPointRestPosition_{DataInterfaceName}(uint PointIndex)`
- L72-76 _function_ `float ReadCurvePointOffset_{DataInterfaceName}(uint CurveIndex)`
- L78-82 _function_ `float ReadCurveNumPoints_{DataInterfaceName}(uint CurveIndex)`
- L84-88 _function_ `uint ReadPointCurveIndex_{DataInterfaceName}(uint PointIndex)`
- L90-101 _function_ `float3x4 ReadCurveRestTransform_{DataInterfaceName}(uint CurveIndex)`
- L103-114 _function_ `float3x4 ReadCurveDeformedTransform_{DataInterfaceName}(uint CurveIndex)`
- L116-119 _function_ `float3x4 ReadObjectRestTransform_{DataInterfaceName}()`
- L121-124 _function_ `float3x4 ReadObjectDeformedTransform_{DataInterfaceName}()`

### `Plugins/Runtime/HairStrands/Shaders/Private/Deformers/DeformerGroomGuidesWrite.ush` (Private)

- lines: 39; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)
- includes: L3 `/Plugin/ComputeFramework/Private/ComputeKernelCommon.ush`, L4 `/Engine/Private/HairStrands/HairStrandsVertexFactoryCommon.ush`

#### Global resources (textures / buffers / samplers) (3)

- L11 _resource_ `StructuredBuffer<float4> {DataInterfaceName}_DeformedPositionOffset;`
- L12 _resource_ `ByteAddressBuffer {DataInterfaceName}_PointRestPositions;`
- L13 _resource_ `RWByteAddressBuffer {DataInterfaceName}_PointDeformedPositions;`

#### Global parameters (uniforms) (4)

- L6 _parameter_ `uint {DataInterfaceName}_RegisteredIndex;`
- L7 _parameter_ `uint {DataInterfaceName}_PointCount;`
- L8 _parameter_ `uint {DataInterfaceName}_TotalPointCount;`
- L9 _parameter_ `uint {DataInterfaceName}_BasePointIndex;`

#### Functions (3)

- L17-20 _function_ `float3 {DataInterfaceName}_GetDeformedPositionOffset()`
- L24-27 _function_ `uint ReadNumPoints_{DataInterfaceName}()`
- L29-38 _function_ `void WritePointDeformedPosition_{DataInterfaceName}(uint PointIndex, float3 PointPosition)`

### `Plugins/Runtime/HairStrands/Shaders/Private/Deformers/DeformerGroomMeshesRead.ush` (Private)

- lines: 33; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)
- includes: L3 `/Plugin/ComputeFramework/Private/ComputeKernelCommon.ush`

#### Global resources (textures / buffers / samplers) (1)

- L7 _resource_ `StructuredBuffer<float4> {DataInterfaceName}_BoneTransformMatrices;`

#### Global parameters (uniforms) (1)

- L5 _parameter_ `uint {DataInterfaceName}_NumBones;`

#### Functions (3)

- L11-14 _function_ `uint ReadNumBones_{DataInterfaceName}()`
- L16-20 _function_ `float3x4 ReadBoneTransformMatrix_{DataInterfaceName}(uint BoneIndex)`
- L22-29 _function_ `float3x4 ReadBindTransformMatrix_{DataInterfaceName}(uint BoneIndex)`

### `Plugins/Runtime/HairStrands/Shaders/Private/Deformers/DeformerGroomSolverRead.ush` (Private)

- lines: 172; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)
- includes: L3 `/Plugin/ComputeFramework/Private/ComputeKernelCommon.ush`, L7 `/Engine/Private/Common.ush` [defined(RAYTRACING_SOLVER_BINDING)], L8 `/Engine/Private/SceneData.ush` [defined(RAYTRACING_SOLVER_BINDING)], L9 `/Engine/Private/ShadingCommon.ush` [defined(RAYTRACING_SOLVER_BINDING)], L10 `/Engine/Private/RayTracing/RayTracingCommon.ush` [defined(RAYTRACING_SOLVER_BINDING)], L11 `/Engine/Private/RayTracing/RayTracingHitGroupCommon.ush` [defined(RAYTRACING_SOLVER_BINDING)]

#### Macros (#define, 1)

- L14 `#define DATA_INTERFACE_ACCELERATION_STRUCTURE_ONCE 1` _[#if defined(RAYTRACING_SOLVER_BINDING) && !defined(DATA_INTERFACE_ACCELERATION_STRUCTURE_ONCE)]_

#### Structs / classes (1)

- L16-20 _struct_ **`FAccelerationStructure`** `struct FAccelerationStructure` _[#if defined(RAYTRACING_SOLVER_BINDING) && !defined(DATA_INTERFACE_ACCELERATION_STRUCTURE_ONCE)]_
  - L18 _member_ `RaytracingAccelerationStructure WorldTLAS;` _[#if defined(RAYTRACING_SOLVER_BINDING) && !defined(DATA_INTERFACE_ACCELERATION_STRUCTURE_ONCE)]_
  - L19 _member_ `int ValidTLAS;` _[#if defined(RAYTRACING_SOLVER_BINDING) && !defined(DATA_INTERFACE_ACCELERATION_STRUCTURE_ONCE)]_

#### Global resources (textures / buffers / samplers) (12)

- L24 _resource_ `RaytracingAccelerationStructure {DataInterfaceName}_WorldAccelerationStructure;` _[#if defined(RAYTRACING_SOLVER_BINDING)]_
- L49 _resource_ `StructuredBuffer<uint> {DataInterfaceName}_ObjectCurveOffsets;`
- L50 _resource_ `StructuredBuffer<uint> {DataInterfaceName}_ObjectPointOffsets;`
- L52 _resource_ `StructuredBuffer<uint> {DataInterfaceName}_ObjectNumCurves;`
- L53 _resource_ `StructuredBuffer<uint> {DataInterfaceName}_ObjectNumPoints;`
- L55 _resource_ `StructuredBuffer<int> {DataInterfaceName}_PointObjectIndices;`
- L56 _resource_ `StructuredBuffer<int> {DataInterfaceName}_CurveObjectIndices;`
- L58 _resource_ `StructuredBuffer<int> {DataInterfaceName}_DynamicPointIndices;`
- L59 _resource_ `StructuredBuffer<int> {DataInterfaceName}_DynamicCurveIndices;`
- L61 _resource_ `StructuredBuffer<int> {DataInterfaceName}_KinematicPointIndices;`
- L62 _resource_ `StructuredBuffer<int> {DataInterfaceName}_KinematicCurveIndices;`
- L64 _resource_ `StructuredBuffer<uint> {DataInterfaceName}_ObjectDistanceLods;`

#### Global parameters (uniforms) (9)

- L36 _parameter_ `uint {DataInterfaceName}_NumSolverPoints;`
- L37 _parameter_ `uint {DataInterfaceName}_NumSolverCurves;`
- L38 _parameter_ `uint {DataInterfaceName}_NumSolverObjects;`
- L40 _parameter_ `uint {DataInterfaceName}_NumDynamicPoints;`
- L41 _parameter_ `uint {DataInterfaceName}_NumDynamicCurves;`
- L43 _parameter_ `uint {DataInterfaceName}_NumKinematicPoints;`
- L44 _parameter_ `uint {DataInterfaceName}_NumKinematicCurves;`
- L46 _parameter_ `float3 {DataInterfaceName}_BoundingBoxMin;`
- L47 _parameter_ `float3 {DataInterfaceName}_BoundingBoxMax;`

#### Functions (21)

- L26-32 _function_ `FAccelerationStructure ReadWorldAccelerationStructure_{DataInterfaceName}()` _[#if defined(RAYTRACING_SOLVER_BINDING)]_
- L68-71 _function_ `uint ReadNumSolverPoints_{DataInterfaceName}()`
- L73-76 _function_ `uint ReadNumSolverCurves_{DataInterfaceName}()`
- L78-81 _function_ `uint ReadNumSolverObjects_{DataInterfaceName}()`
- L83-86 _function_ `uint ReadNumDynamicPoints_{DataInterfaceName}()`
- L88-91 _function_ `uint ReadNumDynamicCurves_{DataInterfaceName}()`
- L93-96 _function_ `uint ReadNumKinematicPoints_{DataInterfaceName}()`
- L98-101 _function_ `uint ReadNumKinematicCurves_{DataInterfaceName}()`
- L103-106 _function_ `float3 ReadBoundingBoxMin_{DataInterfaceName}()`
- L108-111 _function_ `float3 ReadBoundingBoxMax_{DataInterfaceName}()`
- L113-116 _function_ `uint ReadObjectPointOffset_{DataInterfaceName}(uint ObjectIndex)`
- L118-121 _function_ `uint ReadObjectCurveOffset_{DataInterfaceName}(uint ObjectIndex)`
- L123-126 _function_ `uint ReadObjectNumPoints_{DataInterfaceName}(uint ObjectIndex)`
- L128-131 _function_ `uint ReadObjectNumCurves_{DataInterfaceName}(uint ObjectIndex)`
- L133-136 _function_ `uint ReadObjectDistanceLod_{DataInterfaceName}(uint ObjectIndex)`
- L138-141 _function_ `int ReadPointObjectIndex_{DataInterfaceName}(uint PointIndex)`
- L143-146 _function_ `int ReadCurveObjectIndex_{DataInterfaceName}(uint CurveIndex)`
- L148-151 _function_ `int ReadDynamicPointIndex_{DataInterfaceName}(uint PointIndex)`
- L153-156 _function_ `int ReadKinematicPointIndex_{DataInterfaceName}(uint PointIndex)`
- L158-161 _function_ `int ReadDynamicCurveIndex_{DataInterfaceName}(uint CurveIndex)`
- L163-166 _function_ `int ReadKinematicCurveIndex_{DataInterfaceName}(uint CurveIndex)`

### `Plugins/Runtime/HairStrands/Shaders/Private/Deformers/DeformerGroomStrandsRead.ush` (Private)

- lines: 239; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)
- includes: L3 `/Plugin/ComputeFramework/Private/ComputeKernelCommon.ush`, L4 `/Engine/Private/HairStrands/HairStrandsVertexFactoryCommon.ush`, L5 `/Engine/Private/HairStrands/HairStrandsAttributeCommon.ush`, L6 `/Engine/Private/HairStrands/HairStrandsBindingCommon.ush`, L17 `/Engine/Private/HairStrands/HairStrandsAttributeTemplate.ush`

#### Macros (#define, 1)

- L16 `#define HAIR_STRANDS_ATTRIBUTE_ACCESSORS(Name) {DataInterfaceName}_##Name`

#### Global resources (textures / buffers / samplers) (6)

- L19 _resource_ `ByteAddressBuffer {DataInterfaceName}_CurveInterpolationBuffer;`
- L20 _resource_ `ByteAddressBuffer {DataInterfaceName}_PointInterpolationBuffer;`
- L33 _resource_ `Buffer<float4> {DataInterfaceName}_TriangleRestPositions;` _[#if ENABLE_SKINNED_TRANSFORM == 1]_
- L34 _resource_ `Buffer<float4> {DataInterfaceName}_TriangleDeformedPositions;` _[#if ENABLE_SKINNED_TRANSFORM == 1]_
- L35 _resource_ `Buffer<uint> {DataInterfaceName}_CurveBarycentricCoordinates;` _[#if ENABLE_SKINNED_TRANSFORM == 1]_
- L36 _resource_ `Buffer<uint> {DataInterfaceName}_CurveTriangleIndices;` _[#if ENABLE_SKINNED_TRANSFORM == 1]_

#### Global parameters (uniforms) (7)

- L10 _parameter_ `uint {DataInterfaceName}_BasePointIndex;`
- L11 _parameter_ `uint {DataInterfaceName}_BaseCurveIndex;`
- L12 _parameter_ `uint {DataInterfaceName}_BaseGuidePointIndex;`
- L13 _parameter_ `uint {DataInterfaceName}_TotalPointCount;`
- L14 _parameter_ `uint {DataInterfaceName}_TotalCurveCount;`
- L23 _parameter_ `float4x4 {DataInterfaceName}_RigidRestTransform;` _[#if ENABLE_SKINNED_TRANSFORM == 0]_
- L24 _parameter_ `float4x4 {DataInterfaceName}_RigidDeformedTransform;` _[#if ENABLE_SKINNED_TRANSFORM == 0]_

#### Functions (25)

- L26-29 _function_ `float3x4 BuildRigidTransform(float4x4 RigidTransform)` _[#if ENABLE_SKINNED_TRANSFORM == 0]_
- L38-49 _function_ `float3x4 BuildStrandsSkinnedTransform(uint CurveIndex, Buffer<float4> TrianglePositions, Buffer<uint> CurveBarycentricCoordinates, Buffer<uint> CurveTriangleIndices)` _[#if ENABLE_SKINNED_TRANSFORM == 1]_
- L55-71 _function_ `FHairControlPoint ReadPointData(uint PointIndex)`
- L73-82 _function_ `FHairCurve ReadCurveData(uint CurveIndex)`
- L86-89 _function_ `uint ReadNumPoints_{DataInterfaceName}()`
- L91-94 _function_ `uint ReadNumCurves_{DataInterfaceName}()`
- L96-100 _function_ `float3 ReadPointRestPosition_{DataInterfaceName}(uint PointIndex)`
- L102-106 _function_ `float ReadPointRadius_{DataInterfaceName}(uint PointIndex)`
- L108-112 _function_ `float ReadPointCoordU_{DataInterfaceName}(uint PointIndex)`
- L114-118 _function_ `float ReadPointLength_{DataInterfaceName}(uint PointIndex)`
- L120-124 _function_ `float2 ReadPointRootUV_{DataInterfaceName}(uint PointIndex)`
- L126-130 _function_ `float ReadPointSeed_{DataInterfaceName}(uint PointIndex)`
- L132-136 _function_ `uint ReadPointClumpId_{DataInterfaceName}(uint PointIndex)`
- L138-142 _function_ `float3 ReadPointColor_{DataInterfaceName}(uint PointIndex)`
- L144-148 _function_ `float ReadPointRoughness_{DataInterfaceName}(uint PointIndex)`
- L150-154 _function_ `float ReadPointAO_{DataInterfaceName}(uint PointIndex)`
- L156-160 _function_ `uint ReadCurvePointOffset_{DataInterfaceName}(uint CurveIndex)`
- L162-166 _function_ `uint ReadCurveNumPoints_{DataInterfaceName}(uint CurveIndex)`
- L168-173 _function_ `uint ReadPointCurveIndex_{DataInterfaceName}(uint PointIndex)`
- L175-188 _function_ `int2 ReadPointGuideIndices_{DataInterfaceName}(uint PointIndex)`
- L190-201 _function_ `float2 ReadPointGuideWeights_{DataInterfaceName}(uint PointIndex)`
- L203-214 _function_ `float3x4 ReadCurveRestTransform_{DataInterfaceName}(uint CurveIndex)`
- L216-227 _function_ `float3x4 ReadCurveDeformedTransform_{DataInterfaceName}(uint CurveIndex)`
- L229-233 _function_ `uint ReadCurveSourceIndex_{DataInterfaceName}(uint CurveIndex)`
- L235-239 _function_ `uint ReadPointSourceIndex_{DataInterfaceName}(uint PointIndex)`

#### Top-level macro invocations (1)

- L8 _macro_call_ `HAIR_STRANDS_INSTANCE_PARAMETERS({DataInterfaceName})`

### `Plugins/Runtime/HairStrands/Shaders/Private/Deformers/DeformerGroomStrandsWrite.ush` (Private)

- lines: 180; parse: all-branches; HLSL template with {Placeholder} identifiers (instantiated from C++)
- includes: L3 `/Plugin/ComputeFramework/Private/ComputeKernelCommon.ush`, L4 `/Engine/Private/HairStrands/HairStrandsVertexFactoryCommon.ush`

#### Global resources (textures / buffers / samplers) (4)

- L15 _resource_ `StructuredBuffer<float4> {DataInterfaceName}_DeformedPositionOffset;` — Note: resources are explicitly bound here (instance of using HAIR_STRANDS_INSTANCE_PARAMETERS's resources) because we write out data which would be bound as SRV otherwise (position, attributes, ...)
- L16 _resource_ `ByteAddressBuffer {DataInterfaceName}_PointRestPositions;`
- L17 _resource_ `RWByteAddressBuffer {DataInterfaceName}_OutPointDeformedPositions;`
- L18 _resource_ `RWByteAddressBuffer {DataInterfaceName}_OutPointAttributeBuffer;`

#### Global parameters (uniforms) (4)

- L8 _parameter_ `uint {DataInterfaceName}_BasePointIndex;`
- L9 _parameter_ `uint {DataInterfaceName}_BaseCurveIndex;`
- L10 _parameter_ `uint {DataInterfaceName}_TotalPointCount;`
- L11 _parameter_ `uint {DataInterfaceName}_TotalCurveCount;`

#### Functions (14)

- L22-42 _function_ `void InternalSetHairStrandsAttributes(uint Index, uint AttributeOffsetInBytes, uint AttributeStrideInBytes, RWByteAddressBuffer InAttributeBuffer, uint In, uint InIndexToChunkDivAsShift, uint InChunkElementCount, uint InChunkStrideInBytes)`
- L44-57 _function_ `void InternalSetHairStrandsAttributes32(uint Index, uint AttributeOffsetInBytes, uint AttributeStrideInBytes, RWByteAddressBuffer InAttributeBuffer, uint In, uint InIndexToChunkDivAsShift, uint InChunkElementCount, uint InChunkStrideInBytes)`
- L61-64 _function_ `float3 {DataInterfaceName}_GetDeformedPositionOffset()`
- L66-69 _function_ `uint ReadNumPoints_{DataInterfaceName}()`
- L71-74 _function_ `uint ReadNumCurves_{DataInterfaceName}()`
- L76-86 _function_ `void WritePointDeformedPosition_{DataInterfaceName}(uint PointIndex, float3 Position)`
- L88-99 _function_ `void WritePointRadius_{DataInterfaceName}(uint PointIndex, float Radius)`
- L101-114 _function_ `void WritePointPositionRadius_{DataInterfaceName}(uint PointIndex, float4 PositionAndRadius)`
- L116-125 _function_ `void WriteCurveRootUV_{DataInterfaceName}(uint CurveIndex, float2 RootUV)`
- L127-136 _function_ `void WriteCurveSeed_{DataInterfaceName}(uint CurveIndex, float Seed)`
- L138-147 _function_ `void WriteCurveClumpId_{DataInterfaceName}(uint CurveIndex, uint ClumpId)`
- L149-158 _function_ `void WritePointColor_{DataInterfaceName}(uint PointIndex, float3 Color)`
- L160-169 _function_ `void WritePointRoughness_{DataInterfaceName}(uint PointIndex, float Roughness)`
- L171-180 _function_ `void WritePointAO_{DataInterfaceName}(uint PointIndex, float Ao)`

#### Top-level macro invocations (1)

- L6 _macro_call_ `HAIR_STRANDS_INSTANCE_PARAMETERS({DataInterfaceName})`
