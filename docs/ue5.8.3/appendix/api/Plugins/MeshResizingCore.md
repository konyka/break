# Plugins / MeshResizingCore

- module root: `Plugins/Experimental/MeshResizing/Source/MeshResizingCore`
- headers: 4; symbols: 83
- symbol kinds: class=4, enum=1, enumerator=1, function=2, macro=3, member=25, namespace=16, prototype=26, struct=5
- PrivateDependencyModuleNames: Chaos, Core, CoreUObject, GeometryCore, HairStrandsCore, MeshDescription

### `Plugins/Experimental/MeshResizing/Source/MeshResizingCore/Public/MeshResizing/BaseBodyTools.h` (Public)


#### struct `UE::MeshResizing::FBaseBodyTools`  
`struct FBaseBodyTools`  
_L15-30_
- L17 _public member_ `static const FName ImportedVertexVIDsAttrName;`
- L18 _public member_ `static const FName RawPointIndicesVIDsAttrName;`
- L21 _public prototype_ `static bool AttachVertexMappingData(const FName& AttrName, const TArray<int32>& Data, UE::Geometry::FDynamicMesh3& Mesh);` — @return success
- L24 _public prototype_ `static bool GenerateResizableProxyFromVertexMappingData(const UE::Geometry::FDynamicMesh3& SourceMesh, const FName& SourceMappingName, const UE::Geometry::FDynamicMesh3& TargetMesh, const FName& TargetMappingName, UE::Geometry::FDynamicMesh3& ProxyMesh);` — @return success
- L27 _public prototype_ `static bool InterpolateResizableProxy(const UE::Geometry::FDynamicMesh3& SourceMesh, const UE::Geometry::FDynamicMesh3& TargetMesh, float BlendAlpha, UE::Geometry::FDynamicMesh3& ProxyMesh);` — @return success

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API MESHRESIZINGCORE_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Geometry` (scope `UE`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MeshResizing` (scope `UE`)

### `Plugins/Experimental/MeshResizing/Source/MeshResizingCore/Public/MeshResizing/CustomRegionResizing.h` (Public)


#### enum `EMeshResizingCustomRegionType`  
`enum struct EMeshResizingCustomRegionType : uint8`  
_L19-28_
- reflection: `UENUM()`
- L21 _public enumerator_ `TrilinearInterpolation`

#### struct `FMeshResizingCustomRegion`  
`struct FMeshResizingCustomRegion`  
_L31-73_
- reflection: `USTRUCT()`
- L36 _public member_ `TArray<int32> RegionVertices;` — `UPROPERTY()`
- L38 _public member_ `TArray<FVector3f> RegionVertexCoords;` — `UPROPERTY()` — Trilinear interpolation within Bounds: (0,0,0) = RegionBoundsCentroid - RegionBoundsExtents; (1,1,1) = RegionBoundsCentroid + RegionBoundsExtents
- L41 _public member_ `int32 SourceFaceIndex = INDEX_NONE;` — `UPROPERTY()`
- L43 _public member_ `FVector3f SourceBaryCoords = FVector3f(0.f);` — `UPROPERTY()`
- L45 _public member_ `FVector3d SourceOrigin = FVector3d(0.f);` — `UPROPERTY()`
- L47 _public member_ `FVector3f SourceAxis0 = FVector3f(0.f);` — `UPROPERTY()`
- L49 _public member_ `FVector3f SourceAxis1 = FVector3f(0.f);` — `UPROPERTY()`
- L51 _public member_ `FVector3f SourceAxis2 = FVector3f(0.f);` — `UPROPERTY()`
- L55 _public member_ `FVector3f RegionBoundsCentroid = FVector3f(0.f);` — `UPROPERTY()` — Relative to Source
- L58 _public member_ `FVector3f RegionBoundsExtents = FVector3f(0.f);` — `UPROPERTY()`
- L60 _public function_ `void Reset()`
- L69 _public function_ `bool IsValid() const`

#### struct `UE::MeshResizing::FCustomRegionResizing`  
`struct FCustomRegionResizing`  
_L77-82_
- L79 _public prototype_ `static void GenerateCustomRegion(const TConstArrayView<FVector3f>& BoundPositions, const UE::Geometry::FDynamicMesh3& SourceMesh, const TSet<int32>& BoundVertices, FMeshResizingCustomRegion& OutData);`
- L80 _public prototype_ `static bool CalculateFrameForCustomRegion(const UE::Geometry::FDynamicMesh3& SourceMesh, const FMeshResizingCustomRegion& BindingGroup, FVector3d& OutOrigin, FVector3f& OutTangentU, FVector3f& OutTangentV, FVector3f& OutNormal);`
- L81 _public prototype_ `static void InterpolateCustomRegionPoints(const FMeshResizingCustomRegion& BindingGroup, const TConstArrayView<FVector3d>& BoundsCorners, TArrayView<FVector3f> BoundPositions);`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MESHRESIZINGCORE_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Geometry` (scope `UE`)
- L75 _namespace_ `namespace UE`
- L75 _namespace_ `namespace MeshResizing` (scope `UE`)

### `Plugins/Experimental/MeshResizing/Source/MeshResizingCore/Public/MeshResizing/Mesh3DConstraints.h` (Public)


#### class `UE::MeshResizing::FShearConstraint`  
`class FShearConstraint`  
_L16-26_
- L19 _public prototype_ `FShearConstraint(float ShearConstraintStrength, const TArray<float>& ShearConstraintWeights, const int32 NumParticles);`
- L20 _public prototype_ `void Apply(UE::Geometry::FDynamicMesh3& ResizedMesh, const UE::Geometry::FDynamicMesh3& InitialResizedMesh, const UE::Geometry::FDynamicMesh3& BaseMesh) const;`
- L21 _public prototype_ `void Apply(UE::Geometry::FDynamicMesh3& ResizedMesh, const UE::Geometry::FDynamicMesh3& InitialResizedMesh, const UE::Geometry::FDynamicMesh3& BaseMesh, const TArray<float>& InvMass) const;`
- L24 _private member_ `int32 NumParticles;`
- L25 _private member_ `Chaos::Softs::FPBDFlatWeightMapView ShearWeightMap;`

#### class `UE::MeshResizing::FEdgeConstraint`  
`class FEdgeConstraint`  
_L28-37_
- L31 _public prototype_ `FEdgeConstraint(float EdgeConstraintStrength, const TArray<float>& EdgeConstraintWeights, const int32 NumParticles);`
- L32 _public prototype_ `void Apply(UE::Geometry::FDynamicMesh3& ResizedMesh, const UE::Geometry::FDynamicMesh3& InitialResizedMesh, const UE::Geometry::FDynamicMesh3& BaseMesh, const TArray<float>& InvMass) const;`
- L35 _private member_ `int32 NumParticles;`
- L36 _private member_ `Chaos::Softs::FPBDFlatWeightMapView EdgeWeightMap;`

#### class `UE::MeshResizing::FBendingConstraint`  
`class FBendingConstraint`  
_L39-51_
- L42 _public prototype_ `FBendingConstraint(const UE::Geometry::FDynamicMesh3& BaseMesh, float BendingConstraintStrength, const TArray<float>& BendingConstraintWeights, const int32 NumParticles);`
- L43 _public prototype_ `Chaos::Softs::FSolverReal GetScalingFactor(const UE::Geometry::FDynamicMesh3 & Mesh, int32 ConstraintIndex, const TStaticArray<FVector3d, 4>&Grads, const Chaos::Softs::FSolverReal ExpStiffnessValue, const TArray<float>&InvMass) const;`
- L44 _public prototype_ `void Apply(UE::Geometry::FDynamicMesh3& ResizedMesh, const TArray<float>& InvMass) const;`
- L47 _private member_ `int32 NumParticles;`
- L48 _private member_ `Chaos::Softs::FPBDFlatWeightMapView BendingConstraintWeightMap;`
- L49 _private member_ `TArray<Chaos::TVec4<int32>> Constraints;`
- L50 _private member_ `TArray<float> RestAngles;`

#### class `UE::MeshResizing::FExternalForceConstraint`  
`class FExternalForceConstraint`  
_L53-62_
- L56 _public prototype_ `FExternalForceConstraint(const TArray<FVector3d>& InParticleExternalForce, const int32 NumParticles);`
- L57 _public prototype_ `void Apply(UE::Geometry::FDynamicMesh3& ResizedMesh, const TArray<float>& InvMass) const;`
- L60 _private member_ `int32 NumParticles;`
- L61 _private member_ `TArray<FVector3d> ParticleExternalForce;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Geometry` (scope `UE`)
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MeshResizing` (scope `UE`)

### `Plugins/Experimental/MeshResizing/Source/MeshResizingCore/Public/MeshResizing/RBFInterpolation.h` (Public)


#### struct `FMeshResizingRBFInterpolationData`  
`struct FMeshResizingRBFInterpolationData`  
_L17-27_
- reflection: `USTRUCT()`
- L22 _public member_ `TArray<int32> SampleIndices;` — `UPROPERTY()`
- L24 _public member_ `TArray<FVector3f> SampleRestPositions;` — `UPROPERTY()`
- L26 _public member_ `TArray<float> InterpolationWeights;` — `UPROPERTY()`

#### struct `UE::MeshResizing::FRBFInterpolation`  
`struct FRBFInterpolation`  
_L31-43_
- L33 _public prototype_ `static void GenerateWeights(const TConstArrayView<FVector3f>& SourcePositions, int32 NumInterpolationPoints, FMeshResizingRBFInterpolationData& OutData);`
- L34 _public prototype_ `static void GenerateWeights(const UE::Geometry::FDynamicMesh3& BaseMesh, int32 NumInterpolationPoints, FMeshResizingRBFInterpolationData& OutData);`
- L35 _public prototype_ `static void GenerateMeshSamples(const TArray<FVector3f>& TargetPositions, const FMeshResizingRBFInterpolationData& InterpolationData, TArray<FVector3f>& SampleDeformations);`
- L36 _public prototype_ `static void GenerateWeights(const FMeshDescription& BaseMesh, int32 NumInterpolationPoints, FMeshResizingRBFInterpolationData& OutData);`
- L37 _public prototype_ `static void DeformPoints(const TArray<FVector3f>& TargetPositions, const FMeshResizingRBFInterpolationData& InterpolationData, bool bInterpolateNormals, UE::Geometry::FDynamicMesh3& DeformingMesh);`
- L38 _public prototype_ `static void DeformCoordinateFrames(const TArray<FVector3f>& TargetPositions, const FMeshResizingRBFInterpolationData& InterpolationData, bool bNormalize, bool bOrthogonalize, TArray<FMatrix44f>& Coordinates);`
- L39 _public prototype_ `static void DeformPoints(const FMeshDescription& TargetMesh, const FMeshResizingRBFInterpolationData& InterpolationData, TArray<FVector3d>& Points);`
- L40 _public prototype_ `static void DeformPoints(const FMeshDescription& TargetMesh, const FMeshResizingRBFInterpolationData& InterpolationData, bool bInterpolateNormals, UE::Geometry::FDynamicMesh3& DeformingMesh);`
- L41 _public prototype_ `static void DeformPoints(const FMeshDescription& TargetMesh, const FMeshResizingRBFInterpolationData& InterpolationData, TArrayView<FVector3f> Points, TArrayView<FVector3f> Normals);`
- L42 _public prototype_ `static void DeformPoints(const FMeshDescription& TargetMesh, const FMeshResizingRBFInterpolationData& InterpolationData, TArrayView<FVector3f> Points, TArrayView<FVector3f> Normals, TArrayView<FVector3f> TangentUs, TArrayView<FVector3f> TangentVs);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MESHRESIZINGCORE_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Geometry` (scope `UE`)
- L29 _namespace_ `namespace UE`
- L29 _namespace_ `namespace MeshResizing` (scope `UE`)
