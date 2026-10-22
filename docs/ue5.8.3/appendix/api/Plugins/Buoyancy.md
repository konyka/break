# Plugins / Buoyancy

- module root: `Plugins/Experimental/Buoyancy/Source/Runtime`
- headers: 13; symbols: 394
- symbol kinds: class=17, delegate=3, enum=2, enumerator=8, function=66, macro=4, member=150, namespace=4, prototype=123, struct=14, typedef=2, variable=1
- PrivateDependencyModuleNames: Chaos, ChaosCore, DeveloperSettings, PhysicsCore
- PublicDependencyModuleNames: ChaosUserDataPT, Core, CoreUObject, Engine, Water

### `Plugins/Experimental/Buoyancy/Source/Runtime/Public/BuoyancyAlgorithms.h` (Public)


#### struct `BuoyancyAlgorithms::FSubmersion`  
`struct FSubmersion`  
_L28-38_
- desc: Minimal struct containing essential data about a particular submersion
- L31 _public member_ `Chaos::FPBDRigidParticleHandle* SubmergedParticle;` — Indicates the submerged particle
- L34 _public member_ `float SubmergedVolume;` — Total submerged volume
- L37 _public member_ `Chaos::FVec3 SubmergedCoM;` — Effective submerged center of mass

#### struct `BuoyancyAlgorithms::FBuoyancyShapeTopologyLimits`  
`struct FBuoyancyShapeTopologyLimits`  
_L41-49_
- desc: #todo(dmp): adjust these
- L44 _public member_ `static const int32 MaxVerticesPerShape = 50;`
- L45 _public member_ `static const int32 MaxEdgesPerShape = 144;`
- L46 _public member_ `static const int32 MaxIntersectionPointsPerShape = MaxEdgesPerShape;`
- L47 _public member_ `static const int32 MaxVerticesPerFace = 10;`
- L48 _public member_ `static const int32 MaxSubmergedFaceVertices = MaxVerticesPerFace + 1;`

#### class `BuoyancyAlgorithms::FBuoyancyShape`  
`class FBuoyancyShape`  
_L52-73_
- desc: abstract class to sample water for a given particle
- L55 _public function_ `FBuoyancyShape()`
- L57 _public prototype_ `virtual ~FBuoyancyShape() = default;`
- L59 _public prototype_ `virtual void Initialize() = 0;`
- L61 _public prototype_ `virtual int32 NumVertices() const = 0;`
- L62 _public prototype_ `virtual int32 NumEdges() const = 0;`
- L63 _public prototype_ `virtual int32 NumFaces() const = 0;`
- L64 _public prototype_ `virtual int NumFaceVertices(const int Index) const = 0;`
- L65 _public prototype_ `virtual int NumMaxIntersectionsPoints() const = 0;`
- L67 _public prototype_ `virtual Chaos::FVec3 GetVertex(int32 Index) const = 0;`
- L68 _public prototype_ `virtual void GetEdgeVertices(int EdgeIndex, int32& OutIndex0, int32& OutIndex1) const = 0;`
- L69 _public prototype_ `virtual int32 GetFaceVertex(const int FaceIndex, const int FaceVertexIndex) const = 0;`
- L70 _public prototype_ `virtual int32 GetFaceEdge(const int FaceIndex, const int FaceEdgeIndex) const = 0;`
- L72 _public prototype_ `virtual Chaos::FVec3 GetCenter() const = 0;`

#### class `BuoyancyAlgorithms::FBuoyancyBoxShape`  
`class FBuoyancyBoxShape : public FBuoyancyShape`  
_L75-103_
- inherits: `FBuoyancyShape`
- L78 _public function_ `FBuoyancyBoxShape(const Chaos::FAABB3& InLocalBox) : LocalBox(InLocalBox)`
- L80 _public function_ `void Initialize()`
- L82 _public function_ `int32 NumVertices() const override`
- L83 _public function_ `int32 NumEdges() const override`
- L84 _public function_ `int32 NumFaces() const override`
- L85 _public function_ `int NumFaceVertices(const int Index) const override`
- L86 _public function_ `int NumMaxIntersectionsPoints() const override`
- L88 _public function_ `Chaos::FVec3 GetVertex(int32 Index) const override`
- L90 _public function_ `void GetEdgeVertices(int EdgeIndex, int32& OutIndex0, int32& OutIndex1) const`
- L97 _public function_ `int32 GetFaceVertex(const int FaceIndex, const int FaceVertexIndex) const override`
- L98 _public function_ `int32 GetFaceEdge(const int FaceIndex, const int FaceEdgeIndex) const override`
- L99 _public function_ `Chaos::FVec3 GetCenter() const override`
- L102 _private member_ `const Chaos::FAABB3& LocalBox;`

#### class `BuoyancyAlgorithms::FBuoyancyConvexShape`  
`class FBuoyancyConvexShape : public FBuoyancyShape`  
_L105-140_
- inherits: `FBuoyancyShape`
- L108 _public function_ `FBuoyancyConvexShape(const Chaos::FConvex *InConvex) : Convex(InConvex)`
- L110 _public prototype_ `virtual void Initialize() override;`
- L112 _public function_ `int32 NumVertices() const override`
- L113 _public function_ `int32 NumEdges() const override`
- L114 _public function_ `int32 NumFaces() const override`
- L115 _public function_ `int NumFaceVertices(const int Index) const override`
- L118 _public function_ `int NumMaxIntersectionsPoints() const override` — #todo(dmp): whats the best upper bound for max number of intersection points between a convex and plane?
- L119 _public function_ `Chaos::FVec3 GetVertex(int32 Index) const override`
- L121 _public function_ `void GetEdgeVertices(int EdgeIndex, int32& OutIndex0, int32& OutIndex1) const`
- L127 _public function_ `int32 GetFaceVertex(const int FaceIndex, const int FaceVertexIndex) const override`
- L128 _public function_ `int32 GetFaceEdge(const int FaceIndex, const int FaceEdgeIndex) const override`
- L134 _public function_ `Chaos::FVec3 GetCenter() const override`
- L137 _private member_ `const Chaos::FConvex* Convex;`
- L139 _private member_ `TArray<int32, TInlineAllocator<FBuoyancyShapeTopologyLimits::MaxEdgesPerShape * 2>> HalfEdgeToEdge;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Chaos`
- L25 _namespace_ `namespace BuoyancyAlgorithms`
- L144 _prototype_ `Chaos::FRealSingle ComputeParticleVolume(const Chaos::FPBDRigidsEvolutionGBF& Evolution, const Chaos::FGeometryParticleHandle* Particle);` (scope `BuoyancyAlgorithms`) — Compute the effective volume of an entire particle based on its material density and mass.
- L148 _prototype_ `Chaos::FRealSingle ComputeShapeVolume(const Chaos::FGeometryParticleHandle* Particle, const bool UseBoundingBoxVolume = true);` (scope `BuoyancyAlgorithms`) — Compute the effective volume of a shape. This method must reflect the maximum possible output value of the non-scaled ComputeSubmergedVolume.
- L151 _prototype_ `void ComputeShapeVolumes(const Chaos::FGeometryParticleHandle* Particle, Chaos::FRealSingle& OutBBoxVol, Chaos::FRealSingle& OutGeomVol);` (scope `BuoyancyAlgorithms`) — Compute both bounding box and geometric shape volumes in a single traversal.
- L154 _prototype_ `void ScaleSubmergedVolume(const Chaos::FPBDRigidsEvolutionGBF& Evolution, const Chaos::FGeometryParticleHandle* Particle, const bool UseBoundingBoxVolume, Chaos::FRealSingle& SubmergedVol, Chaos::FRealSingle& TotalVol);` (scope `BuoyancyAlgorithms`)
- L158 _prototype_ `bool ComputeSubmergedVolume(FBuoyancyParticleData& ParticleData, const Chaos::FPBDRigidsEvolutionGBF& Evolution, const Chaos::FGeometryParticleHandle* ParticleA, const Chaos::FGeometryParticleHandle* ParticleB, int32 NumSubdivisions, float MinVolume, float& SubmergedVol, Chaos::FVec3& SubmergedCoM, float& TotalVol);` (scope `BuoyancyAlgorithms`) — Compute an approximate volume and center of mass of particle B submerged in particle A, adjusting for the volume of the object based on the material density and mass of the object
- L161 _prototype_ `bool ComputeSubmergedVolume(FBuoyancyParticleData& ParticleData, const Chaos::FGeometryParticleHandle* ParticleA, const Chaos::FGeometryParticleHandle* ParticleB, int32 NumSubdivisions, float MinVolume, float& SubmergedVol, Chaos::FVec3& SubmergedCoM);` (scope `BuoyancyAlgorithms`) — Compute an approximate volume and center of mass of particle B submerged in particle A
- L164 _prototype_ `bool ComputeSubmergedVolume(FBuoyancyParticleData& ParticleData, const Chaos::FPBDRigidsEvolutionGBF& Evolution, const Chaos::FGeometryParticleHandle* SubmergedParticle, const Chaos::FGeometryParticleHandle* WaterParticle, const FVector& WaterX, const FVector& WaterN, int32 NumSubdivisions, float MinVolume, float& SubmergedVol, Chaos::FVec3& SubmergedCoM, float& TotalVol);` (scope `BuoyancyAlgorithms`) — Compute submerged volume given a single waterlevel
- L166 _prototype_ `bool ComputeSubmergedVolume(FBuoyancyParticleData& ParticleData, const Chaos::FGeometryParticleHandle* SubmergedParticle, const Chaos::FGeometryParticleHandle* WaterParticle, const FVector& WaterX, const FVector& WaterN, int32 NumSubdivisions, float MinVolume, float& SubmergedVol, Chaos::FVec3& SubmergedCoM);` (scope `BuoyancyAlgorithms`)
- L171 _prototype_ `bool ComputeSubmergedBounds(const FVector& SurfacePointLocal, const FVector& SurfaceNormalLocal, const Chaos::FAABB3& RigidBox, Chaos::FAABB3& OutSubmergedBounds);` (scope `BuoyancyAlgorithms`) — Given an OOBB and a water level, generate another OOBB which is 1. entirely contained within the input OOBB and 2. entirely contains the portion of the OOBB which is submerged below the water level.
- L175 _prototype_ `bool SubdivideBounds(const Chaos::FAABB3& Bounds, int32 NumSubdivisions, float MinVolume, TArray<Chaos::FAABB3>& OutBounds);` (scope `BuoyancyAlgorithms`) — Given a bounds object, recursively subdivide it in eighths to a fixed maximum depth and a fixed minimum smallest subdivision volume.
- L179 _prototype_ `bool ComputeBuoyantForce(const Chaos::FPBDRigidParticleHandle* RigidParticle, const float DeltaSeconds, const float WaterDensity, const float WaterDrag, const Chaos::FVec3& GravityAccelVec, const Chaos::FVec3& SubmergedCoM, const float SubmergedVol, const Chaos::FVec3& WaterVel, const Chaos::FVec3& WaterN, Chaos::FVec3& OutDeltaV, Chaos::FVec3& OutDeltaW);` (scope `BuoyancyAlgorithms`) — Given a rigid particle and it's submerged CoM and Volume, compute delta velocities for integrated buoyancy forces on an object
- L186 _prototype_ `template <typename SamplerType> void ComputeSubmergedVolumeAndForcesForParticle(FBuoyancyParticleData& ParticleData, const Chaos::FGeometryParticleHandle* SubmergedParticle, const Chaos::FGeometryParticleHandle* WaterParticle, TSharedPtr<SamplerType> WaterSampler, const Chaos::FPBDRigidsEvolution& Evolution, const float DeltaSeconds, const float WaterDensity, const float WaterDrag, const float WaterLift, float& OutTotalParticleVol, float& OutTotalSubmergedVol, Chaos::FVec3& OutTotalSubmergedCoM, Chaos::FVec3& OutTotalDragForce, Chaos::FVec3& OutTotalDragTorque, Chaos::FVec3& OutTotalBuoyancyForce, Chaos::FVec3& OutTotalBuoyancyTorque);` (scope `BuoyancyAlgorithms`) — given a particle, loop over the contained shapes and accumulate force/torque/submerged CoM values Drag/lift and buoyancy forces are output separately to allow semi-implicit drag integration.
- L197 _prototype_ `template <typename ShapeType, typename SamplerType> void ComputeSubmergedVolumeAndForcesForShape( const Chaos::FGeometryParticleHandle* SubmergedParticle, const ShapeType& BoxShape, const Chaos::FPBDRigidsEvolution& Evolution, float DeltaSeconds, const float WaterDensity, const float WaterDrag, const float WaterLift, const float ParticleVol, const float ShapeVol, const Chaos::FRigidTransform3 &ShapeWorldTransform, TSharedPtr<SamplerType> WaterSampler, float& OutSubmergedVol, Chaos::FVec3& OutSubmergedCoM, Chaos::FVec3& OutForce, Chaos::FVec3& OutTorque, Chaos::FVec3& OutBuoyancyForce, Chaos::FVec3& OutBuoyancyTorque);` (scope `BuoyancyAlgorithms`) — given a shape, compute the submerged volume and accumulate forces this is done in a single function call because of the iterative nature of the algorithm
- L208 _prototype_ `template <typename ShapeType> void FindAllIntersectionPoints(const Chaos::FVec3& WaterP, const Chaos::FVec3& WaterN, const ShapeType& BoxShape, const TArray<FVector, TInlineAllocator<FBuoyancyShapeTopologyLimits::MaxVerticesPerShape>> &WorldVertexPosition, const TArray<bool, TInlineAllocator<FBuoyancyShapeTopologyLimits::MaxVerticesPerShape>> &VertexIsUnderwater, TArray<FVector, TInlineAllocator<FBuoyancyShapeTopologyLimits::MaxEdgesPerShape>>& EdgeIntersectionPoints, int32& NumIntersections, TArray<FVector, TInlineAllocator<FBuoyancyShapeTopologyLimits::MaxIntersectionPointsPerShape>>& OutOrderedIntersectionPoints, FVector& OutIntersectionCenter);` (scope `BuoyancyAlgorithms`) — find intersection points between a plane and aabbox
- L216 _prototype_ `void SortIntersectionPointsByAngle(const Chaos::FVec3& WaterN, const Chaos::FVec3& IntersectionCenter, const TArray<FVector, TInlineAllocator<FBuoyancyShapeTopologyLimits::MaxEdgesPerShape>>& EdgeIntersectionPoints, int32 NumIntersections, TArray<FVector, TInlineAllocator<FBuoyancyShapeTopologyLimits::MaxIntersectionPointsPerShape>>& OutOrderedIntersectionPoints);` (scope `BuoyancyAlgorithms`) — sort intersection points by angle
- L221 _prototype_ `bool EdgePlaneIntersection(const Chaos::FVec3& WaterP, const Chaos::FVec3& WaterN, const Chaos::FVec3& V0, const Chaos::FVec3& V1, Chaos::FVec3& IntersectionPoint);` (scope `BuoyancyAlgorithms`)
- L224 _function_ `FORCEINLINE void ComputeTriangleAreaAndVolume(const FVector &V0, const FVector &V1, const FVector &V2, const FVector &MeshCenterPoint, FVector& OutTriangleBaryCenter, FVector& OutNormal, float& OutArea, float& OutVolume)` (scope `BuoyancyAlgorithms`) — compute area and volume of a tet from a triangle and center point on mesh
- L249 _function_ `FORCEINLINE void ComputeFluidForceForTriangle(const float WaterDrag, const float WaterLift, const float WaterDensity, const float DeltaSeconds, const Chaos::FVec3& ParticleV, const Chaos::FVec3& ParticleW, const FVector WorldCoM, const FVector &TriBaryCenter, const FVector &TriNormal, const float TriArea, const float TetVolume, const FVector &WaterVelocity, const FVector &WaterP, const FVector &WaterN, FVector& OutTotalWorldForce, FVector& OutTotalWorldTorque)` (scope `BuoyancyAlgorithms`) — compute the force the fluid exerts on a triangle
- L309 _prototype_ `void ComputeBuoyantForceForShape(const Chaos::FPBDRigidsEvolution& Evolution, const Chaos::FPBDRigidParticleHandle* RigidParticle, const float DeltaSeconds, const float WaterDensity, const float ParticleVol, const float ShapeVol, const Chaos::FVec3& SubmergedCoM, const float SubmergedVol, const Chaos::FVec3& WaterN, Chaos::FVec3& OutWorldBuoyantForce, Chaos::FVec3& OutWorldBuoyantTorque);` (scope `BuoyancyAlgorithms`) — compute the force the buoyancy exerts on a shape

### `Plugins/Experimental/Buoyancy/Source/Runtime/Public/BuoyancyEventFlags.h` (Public)


#### enum `EBuoyancyEventFlags`  
`enum EBuoyancyEventFlags : uint8`  
_L9-15_
- reflection: `UENUM(BlueprintType, meta=(Bitflags, UseEnumValuesAsMaskValuesInEditor="true"))`
- L11 _public enumerator_ `None = 0 UMETA(Hidden)`
- L12 _public enumerator_ `Begin = 1 << 0`
- L13 _public enumerator_ `Continue = 1 << 1`
- L14 _public enumerator_ `End = 1 << 2`

#### Free symbols / members of external scopes

- L16 _prototype_ `ENUM_CLASS_FLAGS(EBuoyancyEventFlags);`

### `Plugins/Experimental/Buoyancy/Source/Runtime/Public/BuoyancyEventInterface.h` (Public)


#### class `UBuoyancyEventInterface`  
`class UBuoyancyEventInterface : public UInterface`  
_L13-16_
- reflection: `UINTERFACE(MinimalAPI, Blueprintable)`
- inherits: `UInterface`

#### class `IBuoyancyEventInterface`  
`class IBuoyancyEventInterface`  
_L18-97_
- L29 _public prototype_ `virtual void OnSurfaceTouchBegin_Native( UPrimitiveComponent* WaterComponent, UPrimitiveComponent* SubmergedComponent, float SubmergedVolume, const FVector& SubmergedCenterOfMass, const FVector& SubmergedVelocity) = 0;` — Called when part of a submerged simulated actor first comes in contact with a water surface. This can be called for multiple parts of a complex body.
- L40 _public prototype_ `virtual void OnSurfaceTouching_Native( UPrimitiveComponent* WaterComponent, UPrimitiveComponent* SubmergedComponent, float SubmergedVolume, const FVector& SubmergedCenterOfMass, const FVector& SubmergedVelocity) = 0;` — Called continually while objects maintain contact with a water surface. May be called multiple times for different parts of an object.
- L51 _public prototype_ `virtual void OnSurfaceTouchEnd_Native( UPrimitiveComponent* WaterComponent, UPrimitiveComponent* SubmergedComponent, float SubmergedVolume, const FVector& SubmergedCenterOfMass, const FVector& SubmergedVelocity) = 0;` — Called when a submerged body loses contact with all water surfaces. This can result from total submersion or from coming completely out of water.
- L64 _public prototype_ `void OnSurfaceTouchBegin( class AWaterBody* WaterBodyActor, UPrimitiveComponent* WaterComponent, UPrimitiveComponent* SubmergedComponent, float SubmergedVolume, const FVector& SubmergedCenterOfMass, const FVector& SubmergedVelocity);` — `UFUNCTION(BlueprintImplementableEvent, Category = WaterBody)` — Called when part of a submerged simulated actor first comes in contact with a water surface. This can be called for multiple parts of a complex body.
- L77 _public prototype_ `void OnSurfaceTouching( class AWaterBody* WaterBodyActor, UPrimitiveComponent* WaterComponent, UPrimitiveComponent* SubmergedComponent, float SubmergedVolume, const FVector& SubmergedCenterOfMass, const FVector& SubmergedVelocity);` — `UFUNCTION(BlueprintImplementableEvent, Category = WaterBody)` — Called continually while objects maintain contact with a water surface. May be called multiple times for different parts of an object.
- L90 _public prototype_ `void OnSurfaceTouchEnd( class AWaterBody* WaterBodyActor, UPrimitiveComponent* WaterComponent, UPrimitiveComponent* SubmergedComponent, float SubmergedVolume, const FVector& SubmergedCenterOfMass, const FVector& SubmergedVelocity);` — `UFUNCTION(BlueprintImplementableEvent, Category = WaterBody)` — Called when a submerged body loses contact with all water surfaces. This can result from total submersion or from coming completely out of water.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API BUOYANCY_API`

### `Plugins/Experimental/Buoyancy/Source/Runtime/Public/BuoyancyField.h` (Public)


#### class `Buoyancy::FBuoyancyField`  
`class FBuoyancyField : public Chaos::Softs::FVelocityAndPressureField`  
_L14-110_
- inherits: `Chaos::Softs::FVelocityAndPressureField`
- desc: Velocity field used solely for aerodynamics effects including water submersion
- L18 _public function_ `explicit FBuoyancyField(const Chaos::Softs::FCollectionPropertyConstFacade& PropertyCollection) : Chaos::Softs::FVelocityAndPressureField(PropertyCollection), ClothDensityInWaterIndex(PropertyCollection), WaterDensityIndex(PropertyCollection), WaterTurbulenceRatioIndex(PropertyCollection)`
- L26 _public function_ `FBuoyancyField( const Chaos::Softs::FSolverParticlesRange& Particles, const Chaos::FTriangleMesh* TriangleMesh, const Chaos::Softs::FCollectionPropertyConstFacade& PropertyCollection, const TMap<FString, TConstArrayView<Chaos::FRealSingle>>& Weightmaps, Chaos::FSolverReal WorldScale, TSharedPtr<Chaos::Softs::FExternalForces> InExternalForces) : Chaos::Softs::FVelocityAndPressureField(Particles, TriangleMesh, PropertyCollection, Weightmaps, WorldScale), ClothDensityInWaterIndex(PropertyCollection), WaterDensityIndex(PropertyCollection), WaterTurbulenceRatioIndex(PropertyCollection), ExternalForces(InExternalForces)`
- L42 _public function_ `FBuoyancyField() : Chaos::Softs::FVelocityAndPressureField(), ClothDensityInWaterIndex(ForceInit), WaterDensityIndex(ForceInit), WaterTurbulenceRatioIndex(ForceInit)` — Construct an uninitialized field. Mesh, properties, and velocity will have to be set for this field to be valid.
- L49 _public function_ `~FBuoyancyField()`
- L51 _public prototype_ `void Apply(Chaos::Softs::FSolverParticlesRange& InParticles, const Chaos::FSolverReal Dt) const;`
- L53 _public prototype_ `void SetPropertiesAndBuoyancy( const Chaos::Softs::FCollectionPropertyConstFacade& PropertyCollection, const TMap<FString, TConstArrayView<Chaos::FRealSingle>>& Weightmaps, FSolverReal WorldScale, bool bEnableAerodynamics, const FSolverVec3& SolverWind, const Chaos::FRotation3& LocalSpaceRotation = Chaos::FRotation3::Identity, const Chaos::Softs::FSolverReal LocalSpaceScale = (Chaos::Softs::FSolverReal)1., const Chaos::FSolverVec3 LocalSpaceLocation = FSolverVec3::ZeroVector, const Chaos::FRotation3& ReferenceSpaceRotation = Chaos::FRotation3::Identity );`
- L65 _public prototype_ `void PreSimulate_GameThread(float DeltaTime, const UWorld* World, const FBox BoundingBox);`
- L67 _public prototype_ `UE_CHAOS_DECLARE_INDEXLESS_PROPERTYCOLLECTION_NAME(ClothDensityInWater, float);`
- L68 _public prototype_ `UE_CHAOS_DECLARE_INDEXLESS_PROPERTYCOLLECTION_NAME(WaterDensity, float);`
- L69 _public prototype_ `UE_CHAOS_DECLARE_INDEXLESS_PROPERTYCOLLECTION_NAME(WaterTurbulenceRatio, float);`
- L73 _private function_ `FSolverVec3 CalculateForce(FSolverVec3 N, const FSolverVec3& SurfaceVelocity, const FSolverReal SubmergedTriArea, const FSolverVec3& FluidVelocity, const FSolverReal CdI, const FSolverReal CdO, const FSolverReal ClI, const FSolverReal ClO, const FSolverReal Cp, const FSolverReal MaxVelocitySquared) const`
- L91 _private member_ `bool bUseWaterBodies = true;`
- L93 _private member_ `FBuoyancyCollisionData WaterBodyCollisions;`
- L94 _private member_ `FSolverReal LocalSpaceScale = 1.f;`
- L95 _private member_ `FSolverVec3 LocalSpaceLocation = {0.f,0.f,0.f};`
- L96 _private member_ `FSolverReal ClothDensityInWater = 1000.f;`
- L97 _private member_ `FSolverReal WaterDensity = 1.f;`
- L98 _private member_ `FSolverReal WaterTurbulenceRatio = 1.f;`
- L100 _private member_ `FSolverReal WaterRho = 1.f;`
- L101 _private member_ `FSolverReal QuarterWaterRho = 1.f;`
- L103 _private member_ `FSolverReal ClothRho = 1.f;`
- L105 _private prototype_ `UE_CHAOS_DECLARE_INDEXED_PROPERTYCOLLECTION_NAME(ClothDensityInWater, float);`
- L106 _private prototype_ `UE_CHAOS_DECLARE_INDEXED_PROPERTYCOLLECTION_NAME(WaterDensity, float);`
- L107 _private prototype_ `UE_CHAOS_DECLARE_INDEXED_PROPERTYCOLLECTION_NAME(WaterTurbulenceRatio, float);`
- L109 _private member_ `TSharedPtr<Chaos::Softs::FExternalForces> ExternalForces;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Buoyancy`

### `Plugins/Experimental/Buoyancy/Source/Runtime/Public/BuoyancyMacros.h` (Public)


#### Free symbols / members of external scopes

- L7 _macro_ `#define WITH_BUOYANCY_MEMORY_TRACKING (!UE_BUILD_SHIPPING && !UE_BUILD_TEST)`

### `Plugins/Experimental/Buoyancy/Source/Runtime/Public/BuoyancyModule.h` (Public)


#### class `FBuoyancyModule`  
`class FBuoyancyModule : public IModuleInterface`  
_L7-7_
- inherits: `IModuleInterface`

### `Plugins/Experimental/Buoyancy/Source/Runtime/Public/BuoyancyParticleData.h` (Public)


#### enum `EWaterSamplerType`  
`enum class EWaterSamplerType : uint8`  
_L16-22_
- L18 _public enumerator_ `ConstantSpline`
- L19 _public enumerator_ `ShallowWater`
- L20 _public enumerator_ `ConstantSplineWithWaves`
- L21 _public enumerator_ `Invalid`

#### class `FBuoyancyWaterSampler`  
`class FBuoyancyWaterSampler`  
_L25-51_
- desc: abstract class to sample water for a given particle
- L28 _public function_ `FBuoyancyWaterSampler() : SamplerType(EWaterSamplerType::Invalid), bUsePerShapeWaterPlane(true), ClosestWaterPointToParticle(0,0,0), AverageVelocity(0,0,0)`
- L33 _public prototype_ `virtual ~FBuoyancyWaterSampler() = default;`
- L35 _public function_ `bool UsePerShapeWaterPlane() const`
- L36 _public function_ `FVector GetClosestWaterPointToParticle() const`
- L39 _public function_ `FVector GetAverageWaterVelocity() const` — average fluid velocity for the particle
- L40 _public function_ `virtual void InitializeForSubmersion()`
- L41 _public prototype_ `virtual void SampleWaterAtPosition(const FVector& WorldPosition, FVector& OutVelocity, float& OutHeight, float& OutDepth) const = 0;`
- L42 _public prototype_ `virtual FVector SampleVelocityAtPosition(const FVector& WorldPosition) const = 0;`
- L43 _public prototype_ `virtual FVector SampleNormalAtPosition(const FVector& WorldPosition) const = 0;`
- L45 _public function_ `EWaterSamplerType GetSamplerType() const`
- L47 _protected member_ `EWaterSamplerType SamplerType;`
- L48 _protected member_ `bool bUsePerShapeWaterPlane;`
- L49 _protected member_ `FVector ClosestWaterPointToParticle;`
- L50 _protected member_ `FVector AverageVelocity;`

#### class `FBuoyancyShallowWaterSampler`  
`class FBuoyancyShallowWaterSampler : public FBuoyancyWaterSampler`  
_L54-107_
- inherits: `FBuoyancyWaterSampler`
- desc: sample water from a baked shallow water simulation
- L57 _public function_ `FBuoyancyShallowWaterSampler(const TWeakObjectPtr<UShallowWaterSimulationDataBase> InWaterSampler, const FVector& InClosestWaterPointToParticle, const FVector &InAverageVelocity) : WaterSampler(InWaterSampler)`
- L66 _public function_ `virtual void SampleWaterAtPosition(const FVector& WorldPosition, FVector& OutVelocity, float& OutHeight, float& OutDepth) const override`
- L80 _public function_ `virtual FVector SampleVelocityAtPosition(const FVector& WorldPosition) const override`
- L93 _public function_ `virtual FVector SampleNormalAtPosition(const FVector& WorldPosition) const override`
- L106 _private member_ `const TWeakObjectPtr<UShallowWaterSimulationDataBase> WaterSampler;`

#### class `FBuoyancyConstantSplineSampler`  
`class FBuoyancyConstantSplineSampler : public FBuoyancyWaterSampler`  
_L112-164_
- inherits: `FBuoyancyWaterSampler`
- desc: sampler for spline rivers, but we are only doing 1 spline sample per interaction to match the perf of the old system.  Also, spline velocities don't vary much, so the net effect isn't too different
- L115 _public function_ `FBuoyancyConstantSplineSampler(const FBuoyancyWaterSplineData& InWaterSpline, const FVector& InClosestPoint, const FVector& InClosestPointDerivative, const float InClosestSplineKey, const FVector& InWaterN) : WaterSpline(InWaterSpline), ClosestPointDerivative(InClosestPointDerivative), ClosestSplineKey(InClosestSplineKey), WaterN(InWaterN), WaterVel(FVector(0, 0, 0)), WaterVelSet(false)`
- L126 _public function_ `virtual void InitializeForSubmersion()`
- L135 _public function_ `virtual void SampleWaterAtPosition(const FVector& WorldPosition, FVector& OutVelocity, float& OutHeight, float& OutDepth) const override`
- L145 _public function_ `virtual FVector SampleVelocityAtPosition(const FVector& WorldPosition) const override`
- L150 _public function_ `virtual FVector SampleNormalAtPosition(const FVector& WorldPosition) const override`
- L156 _public member_ `const FBuoyancyWaterSplineData &WaterSpline;`
- L158 _public member_ `FVector ClosestPointDerivative = FVector::ZeroVector;`
- L159 _public member_ `float ClosestSplineKey = 0;`
- L161 _public member_ `FVector WaterN = FVector::ZeroVector;`
- L162 _public member_ `FVector WaterVel = FVector::ZeroVector;`
- L163 _public member_ `bool WaterVelSet = false;`

#### class `FBuoyancyConstantSplineWithWavesSampler`  
`class FBuoyancyConstantSplineWithWavesSampler : public FBuoyancyWaterSampler`  
_L168-254_
- inherits: `FBuoyancyWaterSampler`
- desc: Sampler for water bodies with Gerstner waves. Evaluates wave height and normal per-position using the wave data stored on the spline data struct.
- L171 _public function_ `FBuoyancyConstantSplineWithWavesSampler( const FBuoyancyWaterSplineData& InWaterSpline, const FVector& InParticlePosition, const FVector& InClosestPoint, const FVector& InClosestPointDerivative, const float InClosestSplineKey, const FVector& InWaterN, float InWaveReferenceTime, bool bInUseSimpleWaves = false) : WaterSpline(InWaterSpline) , SplineBaseHeight(InClosestPoint.Z) , ClosestPointDerivative(InClosestPointDerivative) , ClosestSplineKey(InClosestSplineKey) , BaseWaterN(InWaterN) , WaveReferenceTime(InWaveReferenceTime) , bUseSimpleWaves(bInUseSimpleWaves)`
- L204 _public function_ `virtual void SampleWaterAtPosition(const FVector& WorldPosition, FVector& OutVelocity, float& OutHeight, float& OutDepth) const override`
- L227 _public function_ `virtual FVector SampleVelocityAtPosition(const FVector& WorldPosition) const override`
- L232 _public function_ `virtual FVector SampleNormalAtPosition(const FVector& WorldPosition) const override`
- L245 _public member_ `const FBuoyancyWaterSplineData& WaterSpline;`
- L246 _public member_ `float SplineBaseHeight = 0.f;`
- L247 _public member_ `FVector ClosestPointDerivative = FVector::ZeroVector;`
- L248 _public member_ `float ClosestSplineKey = 0.f;`
- L249 _public member_ `FVector BaseWaterN = FVector::ZeroVector;`
- L250 _public member_ `float WaveReferenceTime = 0.f;`
- L251 _public member_ `bool bUseSimpleWaves = false;`
- L252 _public member_ `float EstimatedDepth = MAX_FLT;`
- L253 _public member_ `float WaveAttenuationFactor = 1.f;`

#### struct `FBuoyancyInteraction`  
`struct FBuoyancyInteraction`  
_L259-264_
- desc: Each particle will have a list of potential midphases to process, which must be sorted in descending Z order. This struct is used to store them
- L261 _public member_ `Chaos::FPBDRigidParticleHandle* RigidParticle = nullptr;`
- L262 _public member_ `Chaos::FGeometryParticleHandle* WaterParticle = nullptr;`
- L263 _public member_ `TSharedPtr<FBuoyancyWaterSampler> WaterSampler;`

#### struct `FBuoyancySubmersion`  
`struct FBuoyancySubmersion`  
_L270-286_
- desc: A minimal struct of data tracking all the submersions in a frame.
- L272 _public member_ `Chaos::FPBDRigidParticleHandle* Particle = nullptr;`
- L273 _public member_ `TWeakPtr<FProxyTimestampBase, ESPMode::ThreadSafe> SyncTimestamp = nullptr;`
- L275 _public member_ `float Vol = 0.f;`
- L276 _public member_ `FVector CoM = FVector::ZeroVector;`
- L278 _public member_ `FVector Vel = FVector::ZeroVector;`
- L279 _public member_ `FVector Norm = FVector::ZeroVector;`
- L283 _public member_ `bool HasIntegratedQuantities = false;` — #todo(dmp): only used for accurate submersion calculations for now because we integrate those per body.  Ideally we'd convert to only using this
- L284 _public member_ `FVector DeltaV = FVector::ZeroVector;`
- L285 _public member_ `FVector DeltaW = FVector::ZeroVector;`

#### struct `FBuoyancySubmersionMetaData`  
`struct FBuoyancySubmersionMetaData`  
_L289-303_
- desc: Metadata for submersions, used for event callbacks
- L301 _public member_ `static constexpr int32 MaxNumWaterContacts = 3;` — How many metadata's allowed per submerged particle
- L302 _public member_ `TArray<FWaterContact, TInlineAllocator<MaxNumWaterContacts>> WaterContacts;`

#### struct `FBuoyancySubmersionMetaData::FWaterContact`  
`struct FWaterContact`  
_L291-298_
- L293 _public member_ `Chaos::FGeometryParticleHandle* Water = nullptr;`
- L294 _public member_ `TWeakPtr<FProxyTimestampBase, ESPMode::ThreadSafe> SyncTimestamp = nullptr;`
- L295 _public member_ `float Vol = 0.f;`
- L296 _public member_ `FVector CoM = FVector::ZeroVector;`
- L297 _public member_ `FVector Vel = FVector::ZeroVector;`

#### struct `FBuoyancyParticleData`  
`struct FBuoyancyParticleData`  
_L305-425_
- L312 _private function_ `template <typename TData> TData& GetData(const Chaos::FGeometryParticleHandle& ParticleHandle, TSparseArray<TData>& DataArray)` — Access an element in a specific array, adding an uninitialized one if it doesn't exist yet.
- L330 _public prototype_ `FBuoyancyParticleData();`
- L331 _public prototype_ `~FBuoyancyParticleData();`
- L334 _public prototype_ `void Reset();` — Clear all data without freeing memory, for quick repopulation
- L337 _public prototype_ `SIZE_T GetAllocatedSize() const;` — For memory debugging, log the number of bytes that this class has allocated
- L340 _public prototype_ `int32 GetIndex(const Chaos::FGeometryParticleHandle& ParticleHandle);` — Internal index accessor
- L342 _public prototype_ `int32 AddOrGetIndex(const Chaos::FGeometryParticleHandle& ParticleHandle);`
- L344 _public prototype_ `bool RemoveIndex(const Chaos::FGeometryParticleHandle& ParticleHandle);`
- L350 _public member_ `FHashTable IndexMap;` — Bookkeeping arrays Map of indices from unique particle indices to internal array indices TSparseArray<int32> IndexMap;
- L351 _public member_ `TSparseArray<int32> ReverseIndexMap;`
- L360 _public member_ `TSparseArray<FBuoyancyInteractionArray> Interactions;` — Sparse array of arrays of buoyancy interactions - the outer array has one entry per particle, the inner array has an entry per water body that it interacts with. Each will be a very small array, sorted by Z. We use inline allocator to avoid more heap allocations, and to express the assumption that a single particle is unlikely to exceed interactions with a certain number of waterbodies at a time.
- L366 _public member_ `TSparseArray<FBuoyancySubmersion> Submersions;` — This sparse array of submersion events is indexed on particle unique indices. All buoyant forces due to submersions are applied at once. It's stored as a member variable and reset every frame, to avoid reallocation of similarly sized data.
- L367 _public member_ `TSparseArray<FBuoyancySubmersion> PrevSubmersions;`
- L371 _public member_ `TSparseArray<FBuoyancySubmersionMetaData> SubmersionMetaData;` — Another sparse array to be kept in sync with Submersions, which will contain metadata useful for event callbacks
- L372 _public member_ `TSparseArray<FBuoyancySubmersionMetaData> PrevSubmersionMetaData;`
- L383 _public member_ `TSparseArray<TBitArray<>> SubmergedShapes;` — This is a sparse array of bit arrays representing which shapes in an object have already been accounted for when submerging an object. For example, if a massive BVH object has two leaf node shapes submerged in different pools of water and we've already detected that leaf A is submerged, we don't need to test A again. This helps to avoid double counting submerged shapes. Just like Submersions, we have this as a member variable only to keep the memory hot - the array is reset, repopulated and traversed, every frame, so we want to minimize allocations.
- L386 _public function_ `FBuoyancyInteractionArray& GetInteractions(const Chaos::FGeometryParticleHandle& ParticleHandle)` — Element accessors
- L391 _public function_ `FBuoyancySubmersion& GetSubmersion(const Chaos::FGeometryParticleHandle& ParticleHandle)`
- L396 _public function_ `FBuoyancySubmersion& GetPrevSubmersion(const Chaos::FGeometryParticleHandle& ParticleHandle)`
- L401 _public function_ `FBuoyancySubmersionMetaData& GetSubmersionMetaData(const Chaos::FGeometryParticleHandle& ParticleHandle)`
- L406 _public function_ `FBuoyancySubmersionMetaData& GetPrevSubmersionMetaData(const Chaos::FGeometryParticleHandle& ParticleHandle)`
- L411 _public function_ `TBitArray<>& GetSubmergedShapes(const Chaos::FGeometryParticleHandle& ParticleHandle)`
- L418 _private prototype_ `int32 GetIndex(const Chaos::FGeometryParticleHandle& ParticleHandle, int32& OutParticleIndex, int32& OutParticleKey);`
- L420 _private prototype_ `int32 GetIndex(const int32 ParticleIndex, const int32 ParticleKey);`
- L424 _private prototype_ `void OptimizeMemory();` — Shrink or grow internal memory - this operation may be slow when a resize is performed, but should result in more optimal storage and faster data accesses on average.

#### Free symbols / members of external scopes

- L266 _variable_ `static constexpr int32 MaxNumBuoyancyInteractions = 2;`
- L267 _typedef_ `using FBuoyancyInteractionArray = TArray<FBuoyancyInteraction, TInlineAllocator<MaxNumBuoyancyInteractions>>;`

### `Plugins/Experimental/Buoyancy/Source/Runtime/Public/BuoyancyRuntimeSettings.h` (Public)


#### class `UBuoyancyRuntimeSettings`  
`class UBuoyancyRuntimeSettings : public UDeveloperSettings`  
_L15-97_
- reflection: `UCLASS(MinimalAPI, Config = Engine, DefaultConfig, Meta = (DisplayName = "Buoyancy"))`
- inherits: `UDeveloperSettings`
- L21 _public prototype_ `virtual FName GetCategoryName() const;`
- L27 _public member_ `bool bBuoyancyEnabled = true;` — `UPROPERTY(EditAnywhere, Config, Category = Buoyancy, Meta = (ClampMin = 0, ForceUnits = "g/cm3"))` — Whether or not the buoyancy subsystem should run. The subsystem has a public interface for enabling/disabling, so it's possible that a game overrides this at runtime
- L32 _public member_ `bool bKeepFloatingObjectsAwake = false;` — `UPROPERTY(EditAnywhere, Config, Category = Buoyancy)` — Prevent floating particles from falling asleep by explicitly setting object state to dynamic when they are detected.
- L36 _public member_ `float WaterDensity = 1.f;` — `UPROPERTY(EditAnywhere, Config, Category = WaterProperties, Meta = (ClampMin = 0, ForceUnits = "g/cm3"))` — Density of water to use in buoyancy calculations. The density of water is approximately 1g/cm3
- L41 _public member_ `float WaterDrag = 1.f;` — `UPROPERTY(EditAnywhere, Config, Category = WaterProperties, Meta = (ClampMin = 0))` — Drag factor for submerged objects. This unitless number approximates the idea of viscosity, but internally functions identically to the "ether drag" concept.
- L47 _public member_ `float WaterLift = 0.f;` — `UPROPERTY(EditAnywhere, Config, Category = WaterProperties, Meta = (ClampMin = 0))` — Lift coefficient for submerged surfaces. Controls how much angled surfaces deflect objects perpendicular to the flow (rudder steering, planing). 0 = no lift (current behavior), 1 = standard lift.
- L51 _public member_ `TEnumAsByte<ECollisionChannel> CollisionChannelForWaterObjects;` — `UPROPERTY(EditAnywhere, Config, Category = WaterProperties)` — Collision channel to use for water ObjectTypes
- L55 _public member_ `int32 MaxNumBoundsSubdivisions = 2;` — `UPROPERTY(EditAnywhere, Config, Category = SubmergedVolumeCalculation, Meta = (ClampMin = 0))` — Maximum number of times that a buoyancy bounds can be split into 8
- L59 _public member_ `float MinBoundsSubdivisionVol = FMath::Pow(125.f, 3.f);` — `UPROPERTY(EditAnywhere, Config, Category = SubmergedVolumeCalculation)` — Minimum volume bounding box which can be produced by a subdivision operation
- L63 _public member_ `uint8 SurfaceTouchCallbackFlags = EBuoyancyEventFlags::Begin | EBuoyancyEventFlags::End;` — `UPROPERTY(EditAnywhere, Config, Category = Callbacks, Meta = (Bitmask, BitmaskEnum = "/Script/Buoyancy.EBuoyancyEventFlags"))` — Callback data for water surface contacts will be generated according to these flags
- L69 _public member_ `float MinVelocityForSurfaceTouchCallback = 100.f;` — `UPROPERTY(EditAnywhere, Config, Category = Callbacks, Meta = (ClampMin = 0, ForceUnits = "cm/s", EditCondition = "bSubmersionCallbackEnabled"))` — Minimum velocity of an object relative to a water required in order to trigger a submersion callback. If this is zero, then the callback will be triggered every frame for as long as any object is submerged.
- L73 _public member_ `bool bEnableSplineKeyCacheGrid = true;` — `UPROPERTY(EditAnywhere, Config, Category = Splines)` — When enabled, cache computed water spline keys in a grid to avoid recalculation
- L78 _public member_ `float SplineKeyCacheGridSize = 300.f;` — `UPROPERTY(EditAnywhere, Config, Category = Splines, Meta = (ClampMin = 1, ForceUnits = "cm"))` — When using EnableSplineKeyCacheGrid, set grid size to this value. Larger means more caching/fewer spline evaluations, but less accurate water surface interactions.
- L85 _public member_ `uint32 SplineKeyCacheLimit = 256;` — `UPROPERTY(EditAnywhere, Config, Category = Splines, Meta = (ClampMin = 1))` — Number of grid cells a single spline can cache at one time. After this limit has been exceeded, the cache will be reset. If the number of queries against a single body of water exceeds this number, then the caching system will likely fail to continue to provide performance benefits.
- L87 _public prototype_ `virtual void PostInitProperties() override;`
- L90 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L94 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnUpdateSettings, const UBuoyancyRuntimeSettings* , EPropertyChangeType::Type );`
- L95 _public member_ `static FOnUpdateSettings OnSettingsChange;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API BUOYANCY_API`
- L94 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnUpdateSettings, const UBuoyancyRuntimeSettings* , EPropertyChangeType::Type );`

### `Plugins/Experimental/Buoyancy/Source/Runtime/Public/BuoyancyStats.h` (Public)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_STATS_GROUP(TEXT("Buoyancy"), STATGROUP_Buoyancy, STATCAT_Ad`
- L60 _prototype_ `LLM_DECLARE_TAG(BuoyancyParticleDataTag);` — Memory tracking tags

### `Plugins/Experimental/Buoyancy/Source/Runtime/Public/BuoyancySubsystem.h` (Public)


#### class `FBuoyancyWaterSplineDataManager`  
`class FBuoyancyWaterSplineDataManager : public Chaos::TUserDataManagerPT< TSharedPtr<FBuoyancyWaterSplineData> >`  
_L33-33_
- inherits: `Chaos::TUserDataManagerPT<TSharedPtr<FBuoyancyWaterSplineData>>`

#### struct `FBuoyancySettings`  
`struct FBuoyancySettings`  
_L46-78_
- L49 _public member_ `bool bKeepAwake = false;` — Force buoyant particles which are in water to stay awake
- L53 _public member_ `float WaterDensity = 0.0001f;` — Density of water is about 1g/cm^3 Source: https://en.wikipedia.org/wiki/Properties_of_water
- L55 _public member_ `float MaxDeltaV = 500.f;` — cm/s
- L57 _public member_ `float MaxDeltaW = 5.f;` — rad/s
- L59 _public member_ `float WaterDrag = 1.f;` — unitless
- L61 _public member_ `float WaterLift = 0.f;` — unitless
- L63 _public member_ `int32 MaxNumBoundsSubdivisions = 2;`
- L65 _public member_ `float MinBoundsSubdivisionVol = FMath::Pow(125.f, 3.f);` — 1m^3
- L67 _public member_ `ECollisionChannel WaterCollisionChannel = ECollisionChannel::ECC_MAX;`
- L69 _public member_ `uint8 SurfaceTouchCallbackFlags = EBuoyancyEventFlags::None;`
- L71 _public member_ `float MinVelocityForSurfaceTouchCallback = 10.f;`
- L73 _public member_ `bool bSplineKeyCacheGrid = true;`
- L75 _public member_ `float SplineKeyCacheGridSize = 300.f;`
- L77 _public member_ `uint32 SplineKeyCacheLimit = 256;`

#### class `FBuoyancyCollisionData`  
`class FBuoyancyCollisionData`  
_L80-119_
- L83 _public function_ `FBuoyancyCollisionData(UBuoyancySubsystem *InTheBuoyancySubsystem, TArray<const TSharedPtr<FBuoyancyWaterSplineData>> InWaterBodyCollisionData, FBox InWorldBounds, bool InHasCollision, bool InHasPlane, FVector InWaterPlaneLocation, FVector InWaterPlaneNormal, FVector InWaterPlaneVelocity) : TheBuoyancySubsystem(InTheBuoyancySubsystem) , WaterBodyCollisionData(InWaterBodyCollisionData) , WorldBounds(InWorldBounds) , HasCollision(InHasCollision) , HasPlane(InHasPlane) , WaterPlaneLocation(InWaterPlaneLocation) , WaterPlaneNormal(InWaterPlaneNormal) , WaterPlaneVelocity(InWaterPlaneVelocity)`
- L100 _public function_ `FBuoyancyCollisionData() : TheBuoyancySubsystem(nullptr) , WaterBodyCollisionData(TArray<const TSharedPtr<FBuoyancyWaterSplineData>>()) , WorldBounds() , HasCollision(false) , HasPlane(false) , WaterPlaneLocation(0,0,0) , WaterPlaneNormal(0,0,1) , WaterPlaneVelocity(0,0,0)`
- L111 _public member_ `UBuoyancySubsystem *TheBuoyancySubsystem;`
- L112 _public member_ `TArray<const TSharedPtr<FBuoyancyWaterSplineData>> WaterBodyCollisionData;`
- L113 _public member_ `FBox WorldBounds;`
- L114 _public member_ `bool HasCollision;`
- L115 _public member_ `bool HasPlane;`
- L116 _public member_ `FVector WaterPlaneLocation;`
- L117 _public member_ `FVector WaterPlaneNormal;`
- L118 _public member_ `FVector WaterPlaneVelocity;`

#### class `UBuoyancySubsystem`  
`class UBuoyancySubsystem : public UTickableWorldSubsystem`  
_L126-235_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTickableWorldSubsystem`
- L130 _private function_ `UBuoyancySubsystem() : UTickableWorldSubsystem() , bWaterObjectsChanged(false) , bBuoyancySettingsChanged(false) , BuoyancySettings(FBuoyancySettings()) , SplineData(nullptr) , SimCallback(nullptr) , NetMode(ENetMode::NM_MAX)`
- L144 _public prototype_ `bool SetEnabled(const bool bEnabled);` — Return true if enable/disable was successful, or if we were already in the target state.
- L148 _public prototype_ `bool IsEnabled() const;` — `UFUNCTION()` — Return true if subsystem is enabled and running
- L150 _public prototype_ `bool SetEnabledWithUpdatedNetModeCallback(const bool bEnabled);`
- L153 _public prototype_ `SIZE_T GetAllocatedSize() const;`
- L160 _public prototype_ `bool FindOverlappingWaterBodies( const FBox BoundingBox, bool ComputePlane, FVector &ClosestWaterPlaneLocation, FVector &ClosestWaterPlaneNormal, FVector &ClosestWaterPlaneVelocity, TArray<const TSharedPtr<FBuoyancyWaterSplineData>> &CollisionWaterBodySplineData);` — Given a bounding box, perform an overlap test and filter for water bodies, returning the data needed for buoyancy. There are threading issues here since we are storing pointers to FBuoyancyWaterSplineDataManager physics thread data on the gt to use for tests later on (with FindOverlappingWaterBodies). Ideally the Cloth solver would be able to make use of TUserDataManagerPT even if it doesn't run on the pt
- L172 _public prototype_ `bool QueryWaterBody(const FVector& InputPosition, const TSharedPtr<FBuoyancyWaterSplineData> WaterData, FVector& WaterVel, FVector& WaterPlaneN, FVector& WaterPlanePos);` — Query a water body given a FBuoyancyWaterSplineData object representing a water body #todo(dmp): This is designed to only work on the physics thread, needs to be more robust if used elsewhere IE: Ideally the Cloth solver would be able to make use of TUserDataManagerPT even if it doesn't run on the pt and it'd need to support the spline cache
- L178 _protected prototype_ `virtual void PostInitialize() override;` — UTickableWorldSubsystem begin interface
- L179 _protected prototype_ `virtual void Deinitialize() override;`
- L180 _protected prototype_ `virtual void Tick(float DeltaTime) override;`
- L181 _protected prototype_ `virtual TStatId GetStatId() const override;`
- L185 _protected prototype_ `void OnWaterBodyAdded(UWaterBodyComponent* WaterBodyComponent);` — FWaterBodyManager delegate begin callbacks
- L186 _protected prototype_ `void OnWaterBodyRemoved(UWaterBodyComponent* WaterBodyComponent);`
- L191 _private prototype_ `void CreateSimCallback();`
- L192 _private prototype_ `void DestroySimCallback();`
- L195 _private prototype_ `void UpdateAllAsyncInputs();` — Self explanatory function name :D
- L198 _private prototype_ `void UpdateNetMode();` — Get netmode from world and send it to PT
- L201 _private prototype_ `void UpdateSplineData();` — Update PT spline data structs for each waterbody in the map
- L204 _private prototype_ `void UpdateBuoyancySettings();` — Put updated settings struct onto async input to be sent to sim callback
- L207 _private prototype_ `void UpdateWaveReferenceTime();` — Send wave reference time to physics thread each frame
- L210 _private prototype_ `void ProcessSurfaceTouchCallbacks();` — Process async outputs which hold data for triggering callbacks
- L212 _private prototype_ `Chaos::FPhysicsSolver* GetSolver() const;`
- L215 _private prototype_ `void ApplyRuntimeSettings(const class UBuoyancyRuntimeSettings* InSettings, EPropertyChangeType::Type ChangeType);` — When water plugin settings change, this callback will apply changes
- L217 _private member_ `bool bWaterObjectsChanged;`
- L219 _private member_ `bool bBuoyancySettingsChanged;`
- L222 _private member_ `IConsoleVariable* OceanFallbackDepthCVar = nullptr;` — Cached pointer to r.Water.OceanFallbackDepth CVar (looked up once in PostInitialize)
- L224 _private member_ `FBuoyancySettings BuoyancySettings;`
- L226 _private member_ `FBuoyancyWaterSplineDataManager* SplineData;`
- L228 _private member_ `class FBuoyancySubsystemSimCallback* SimCallback;`
- L230 _private member_ `ENetMode NetMode;`
- L233 _private member_ `uint32 SimCallback_AllocatedSize;`

#### struct `FBuoyancySubsystemSimCallbackInput`  
`struct FBuoyancySubsystemSimCallbackInput : public Chaos::FSimCallbackInput`  
_L242-261_
- inherits: `Chaos::FSimCallbackInput`
- L246 _public member_ `TOptional<FBuoyancyWaterSplineDataManager*> SplineData;` — If this ptr is set, then we have a new spline data manager... That should only probably happen one time
- L252 _public member_ `mutable TUniquePtr<FBuoyancySettings> BuoyancySettings;` — Here we use a unique ptr so that it is possible to provide an async input _without_ buoyancy settings (which may be eventually desirable when we eventually are passing lists of water bodies or water wave data).
- L255 _public member_ `TOptional<ENetMode> NetMode;` — Set when net mode changes - should be one time on initialization.
- L258 _public member_ `TOptional<float> WaveReferenceTime;` — Wave reference time, sent every frame when waves are active
- L260 _public prototype_ `void Reset();`

#### struct `FBuoyancySubsystemSimCallbackOutput`  
`struct FBuoyancySubsystemSimCallbackOutput : public Chaos::FSimCallbackOutput`  
_L263-283_
- inherits: `Chaos::FSimCallbackOutput`
- L275 _public member_ `TArray<FSurfaceTouch> SurfaceTouches;`
- L279 _public member_ `TOptional<uint32> AllocatedSize;` — Optional update to allocated num bytes
- L282 _public prototype_ `void Reset();`

#### struct `FBuoyancySubsystemSimCallbackOutput::FSurfaceTouch`  
`struct FSurfaceTouch`  
_L265-273_
- L267 _public member_ `uint8 Flag;`
- L268 _public member_ `IPhysicsProxyBase* RigidProxy;`
- L269 _public member_ `IPhysicsProxyBase* WaterProxy;`
- L270 _public member_ `float Vol;`
- L271 _public member_ `FVector CoM;`
- L272 _public member_ `FVector Vel;`

#### class `FBuoyancySubsystemSimCallback`  
`class FBuoyancySubsystemSimCallback : public Chaos::TSimCallbackObject< FBuoyancySubsystemSimCallbackInput, FBuoyancySubsystemSimCallbackOutput, Chaos::ESimCallbackOptions::Presimulate | Chaos::ESimCallbackOptions::MidPhaseModification>`  
_L287-339_
- inherits: `Chaos::TSimCallbackObject<FBuoyancySubsystemSimCallbackInput,FBuoyancySubsystemSimCallbackOutput,Chaos::ESimCallbackOptions::Presimulate|Chaos::ESimCallbackOptions::MidPhaseModification>`
- desc: NOTE: The Presimulate option is only needed for proper registry with the solver. We don't actually need (or want!) a presimulate tick.
- L294 _public prototype_ `SIZE_T GetAllocatedSize() const;`
- L295 _public function_ `FSplineKeyCacheGrid &GetSplineKeyCache()`
- L297 _public prototype_ `bool QuerySpline(const FVector &QueryPos, const FBuoyancyWaterSplineData& WaterSpline, float &ClosestSplineKey, FVector &ClosestPoint, FVector &ClosestPointDerivative, FVector &WaterN);`
- L301 _private prototype_ `virtual void OnPreSimulate_Internal() override;`
- L302 _private prototype_ `virtual void OnMidPhaseModification_Internal(Chaos::FMidPhaseModifierAccessor& Modifier) override;`
- L304 _private prototype_ `void TrackInteractions(Chaos::FPBDRigidsSolver& PBDSolver, Chaos::FPBDRigidsEvolution& Evolution, Chaos::FMidPhaseModifierAccessor& MidPhaseAccessor);`
- L306 _private prototype_ `void TrackInteraction(Chaos::FPBDRigidsEvolution& Evolution, Chaos::FGeometryParticleHandle* WaterParticle, Chaos::FPBDRigidParticleHandle* RigidParticle, const FBuoyancyWaterSplineData& WaterSpline, Chaos::FMidPhaseModifier& MidPhase);`
- L307 _private prototype_ `void ProcessInteractions(Chaos::FPBDRigidsEvolution& Evolution);`
- L308 _private prototype_ `void ProcessAccurateInteraction(Chaos::FPBDRigidsEvolution& Evolution, FBuoyancyInteraction& Interaction, TSharedPtr<FBuoyancyWaterSampler> WaterSampler);`
- L309 _private prototype_ `void ProcessInteraction(Chaos::FPBDRigidsEvolution& Evolution, FBuoyancyInteraction& Interaction);`
- L310 _private prototype_ `void AddSurfaceTouchCallback(FBuoyancyInteraction& Interaction, FBuoyancySubmersion& Submersion, float TotalVol, float SubmergedVol, FVector SubmergedCoM);`
- L311 _private prototype_ `void ApplyBuoyantForces(Chaos::FPBDRigidsEvolution& Evolution);`
- L312 _private prototype_ `void GenerateCallbackData();`
- L315 _private prototype_ `void GenerateAllocationData();`
- L316 _private member_ `SIZE_T AllocatedSize = 0;`
- L321 _private member_ `FBuoyancyWaterSplineDataManager* SplineData = nullptr;` — Reference to UserDataPT sim callback which manages synchronization of water spline data
- L326 _private member_ `TUniquePtr<FBuoyancySettings> BuoyancySettings;` — Initially we won't have any settings - they have to get passed down via async input. I used TUniquePtr to control access to the same memory that was allocated by GT to minimize copies.
- L328 _private member_ `FBuoyancyParticleData BuoyancyParticleData;`
- L332 _private member_ `ENetMode NetMode = ENetMode::NM_MAX;` — Used to track the net mode of the world that owns the phys scene that this sim tick is taking place in.
- L335 _private member_ `float WaveReferenceTime = 0.0f;` — Wave reference time for evaluating wave heights on the physics thread
- L338 _private member_ `FSplineKeyCacheGrid SplineKeyCache;` — Local cache of spline keys to reduce spline evaluations.

#### Free symbols / members of external scopes

- L21 _macro_ `#define UE_API BUOYANCY_API`
- L23 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogBuoyancySubsystem, Log, All);`
- L23 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogBuoyancySubsystem, Log, All);`
- L35 _namespace_ `namespace Chaos`

### `Plugins/Experimental/Buoyancy/Source/Runtime/Public/BuoyancyWaterSplineData.h` (Public)


#### struct `FBuoyancyWaterSplineData`  
`struct FBuoyancyWaterSplineData`  
_L8-122_
- L10 _public function_ `FBuoyancyWaterSplineData()`
- L11 _public function_ `FBuoyancyWaterSplineData( const Chaos::FRigidTransform3& InTransform, const FInterpCurveVector& InPosition, const EWaterBodyType InBodyType, const TOptional<FInterpCurveFloat>& InWidth, const TOptional<FInterpCurveFloat>& InVelocity, const TWeakObjectPtr<UShallowWaterSimulationDataBase> InShallowWaterSimData, TSharedPtr<FBuoyancyWaveData> InWaveData = nullptr, const TOptional<FInterpCurveFloat>& InDepth = TOptional<FInterpCurveFloat>(), float InChannelDepth = 0.f, float InCurveRampWidth = 512.f, float InChannelEdgeOffset = 0.f, float InOceanFallbackDepth = 0.f ) : Transform(InTransform) , Position(InPosition) , BodyType(InBodyType) , Width(InWidth) , Velocity(InVelocity) , ShallowWaterSimData(InShallowWaterSimData) , WaveData(InWaveData) , Depth(InDepth) , ChannelDepth(InChannelDepth) , CurveRampWidth(InCurveRampWidth) , ChannelEdgeOffset(InChannelEdgeOffset) , OceanFallbackDepth(InOceanFallbackDepth)`
- L40 _public function_ `bool ShouldSampleFromShallowWaterSimulation() const`
- L46 _public member_ `Chaos::FRigidTransform3 Transform;` — Parameters that all water bodies have
- L47 _public member_ `FInterpCurveVector Position;`
- L48 _public member_ `EWaterBodyType BodyType;`
- L51 _public member_ `TOptional<FInterpCurveFloat> Width;` — Parameters that only _some_ water bodies have
- L52 _public member_ `TOptional<FInterpCurveFloat> Velocity;`
- L56 _public member_ `const TWeakObjectPtr<UShallowWaterSimulationDataBase> ShallowWaterSimData;` — Only some water bodies can have a baked shallow water sim representation, which overrides the splines for water height/depth/velocity/normal
- L59 _public member_ `TSharedPtr<FBuoyancyWaveData> WaveData;` — Wave data (null if water body has no waves)
- L62 _public member_ `TOptional<FInterpCurveFloat> Depth;` — For rivers: actual depth curve from spline metadata
- L65 _public member_ `float ChannelDepth = 0.f;` — For ocean/lake: estimate depth from distance to shoreline spline
- L66 _public member_ `float CurveRampWidth = 512.f;`
- L67 _public member_ `float ChannelEdgeOffset = 0.f;`
- L70 _public member_ `float OceanFallbackDepth = 0.f;` — For ocean: fallback depth when beyond terrain carving zone
- L72 _public function_ `bool HasWaves() const`
- L76 _public function_ `float EstimateWaterDepth(const FVector& WorldPosition, const FVector& ClosestSplinePoint, float SplineKey) const` — Estimate water depth at a world position given closest spline point and key. Rivers use the actual depth spline curve; ocean/lake estimate from XY distance to shoreline.

### `Plugins/Experimental/Buoyancy/Source/Runtime/Public/BuoyancyWaterSplineKeyCacheGrid.h` (Public)


#### class `FSplineKeyCacheGrid`  
`class FSplineKeyCacheGrid`  
_L8-38_
- L12 _public prototype_ `float GetClosestSplineKey(const FBuoyancyWaterSplineData& WaterSplineData, const Chaos::FVec3& WorldPosition);`
- L14 _public prototype_ `void Reset();`
- L16 _public prototype_ `void ForEachSplineKey(const TFunction<void(const FBuoyancyWaterSplineData&, const FVector&, float)>& Lambda);`
- L18 _public prototype_ `void SetGridSize(const float InGridSize);`
- L19 _public prototype_ `void SetCacheLimit(const uint32 InCacheLimit);`
- L21 _public prototype_ `float GetGridSize() const;`
- L22 _public prototype_ `uint32 GetCacheLimit() const;`
- L24 _public prototype_ `SIZE_T GetAllocatedSize() const;`
- L28 _private prototype_ `Chaos::TVec3<int32> GetCacheKey(const FVector& LocalPos) const;`
- L30 _private prototype_ `FVector GetLocalPos(const Chaos::TVec3<int32>& CacheKey) const;`
- L32 _private member_ `float GridSize = 300.f;`
- L34 _private member_ `uint32 CacheLimit = 256;`
- L36 _private typedef_ `using FSplineKeyCache = TMap<const FBuoyancyWaterSplineData*, TMap<Chaos::TVec3<int32>, float>>;`
- L37 _private member_ `FSplineKeyCache SplineKeyCache;`

### `Plugins/Experimental/Buoyancy/Source/Runtime/Public/BuoyancyWaveData.h` (Public)


#### struct `FBuoyancyWaveData`  
`struct FBuoyancyWaveData`  
_L11-28_
- desc: Abstract base for wave data evaluable on the physics thread (no UObject access). Copied from game-thread UWaterWaves data so that the physics thread can evaluate wave heights without touching UObjects.
- L13 _public prototype_ `virtual ~FBuoyancyWaveData() = default;`
- L15 _public prototype_ `virtual float GetMaxWaveHeight() const = 0;`
- L18 _public prototype_ `virtual float GetSimpleWaveHeightAtPosition( const FVector& InPosition, float InTime) const = 0;` — Fast version: height only, no normal perturbation
- L22 _public prototype_ `virtual float GetWaveHeightAtPosition( const FVector& InPosition, float InTime, FVector& OutNormal) const = 0;` — Full version: height + perturbed normal
- L26 _public prototype_ `virtual float GetWaveAttenuationFactor( const FVector& InPosition, float InWaterDepth) const = 0;` — Attenuation factor (0-1) based on water depth (e.g. shore dampening)

#### struct `FBuoyancyGerstnerWaveData`  
`struct FBuoyancyGerstnerWaveData : public FBuoyancyWaveData`  
_L32-50_
- inherits: `FBuoyancyWaveData`
- desc: Gerstner wave implementation - self-contained copy of wave params for physics thread use. Math mirrors UGerstnerWaterWaves::GetWaveHeightAtPosition / GetSimpleWaveHeightAtPosition.
- L34 _public member_ `TArray<FGerstnerWave> WaveParams;`
- L35 _public member_ `float MaxWaveHeightValue = 0.0f;`
- L36 _public member_ `float TargetWaveMaskDepth = 0.0f;`
- L38 _public prototype_ `FBuoyancyGerstnerWaveData( const TArray<FGerstnerWave>& InWaveParams, float InMaxWaveHeight, float InTargetWaveMaskDepth);`
- L43 _public prototype_ `virtual float GetMaxWaveHeight() const override;`
- L44 _public prototype_ `virtual float GetSimpleWaveHeightAtPosition( const FVector& InPosition, float InTime) const override;`
- L46 _public prototype_ `virtual float GetWaveHeightAtPosition( const FVector& InPosition, float InTime, FVector& OutNormal) const override;`
- L48 _public prototype_ `virtual float GetWaveAttenuationFactor( const FVector& InPosition, float InWaterDepth) const override;`
