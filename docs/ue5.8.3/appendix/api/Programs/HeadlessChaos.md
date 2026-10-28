# Programs / HeadlessChaos

- module root: `Source/Programs/HeadlessChaos`
- headers: 66; symbols: 563
- symbol kinds: class=19, delegate=1, enum=3, enumerator=11, function=78, macro=5, member=121, namespace=62, prototype=250, struct=6, typedef=7
- PrivateDependencyModuleNames: ApplicationCore, ChaosVehiclesCore, Core, CoreUObject, GeometryCore, GoogleTest, Projects
- PublicIncludePathModuleNames: Launch

### `Source/Programs/HeadlessChaos/Private/HeadlessChaosTestJoint.h` (Private)


#### class `ChaosTest::FJointChainTest`  
`template <typename TEvolution> class FJointChainTest : public FConstraintsTest<TEvolution>`  
_L21-130_
- inherits: `FConstraintsTest<TEvolution>`
- desc: Base class for simple joint chain tests.
- L24 _public typedef_ `using Base = FConstraintsTest<TEvolution>;`
- L29 _public function_ `FJointChainTest(const int32 NumIterations, const FReal Gravity) : Base(NumIterations, Gravity)`
- L34 _public function_ `FPBDJointConstraintHandle* AddJoint(const TVec2<TGeometryParticleHandle<FReal, 3>*>& InConstrainedParticleIndices, const int32 JointIndex)`
- L64 _public function_ `FPBDJointConstraintHandle* GetJoint(const int32 JointIndex)`
- L77 _public function_ `void Create()`
- L92 _public function_ `void InitChain(int32 NumParticles, const FVec3& Dir, FReal Size = 10.f, FReal Separation = 30.f)` — Create a pendulum chain along the specified direction with the first particle kinematic
- L115 _public function_ `void Advance(const FReal Dt)`
- L122 _public member_ `TArray<FVec3> ParticlePositions;` — Initial particles setup
- L123 _public member_ `TArray<FVec3> ParticleSizes;`
- L124 _public member_ `TArray<FReal> ParticleMasses;`
- L127 _public member_ `TArray<FVec3> JointPositions;` — Initial joints setup
- L128 _public member_ `TArray<TVec2<int32>> JointParticleIndices;`
- L129 _public member_ `TArray<FPBDJointSettings> JointSettings;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace ChaosTest`

### `Source/Programs/HeadlessChaos/Public/GeometryCollection/GeometryCollectionTest.h` (Public)


#### Free symbols / members of external scopes

- L17 _prototype_ `DEFINE_LOG_CATEGORY_STATIC(LogTest, Verbose, All);`

### `Source/Programs/HeadlessChaos/Public/GeometryCollection/GeometryCollectionTestBoneHierarchy.h` (Public)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace GeometryCollectionTest`
- L9 _prototype_ `void TestImplicitBoneHierarchy();` (scope `GeometryCollectionTest`)

### `Source/Programs/HeadlessChaos/Public/GeometryCollection/GeometryCollectionTestClean.h` (Public)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace GeometryCollectionTest`
- L8 _prototype_ `void TestDeleteCoincidentVertices();` (scope `GeometryCollectionTest`)
- L10 _prototype_ `void TestDeleteCoincidentVertices2();` (scope `GeometryCollectionTest`)
- L12 _prototype_ `void TestDeleteZeroAreaFaces();` (scope `GeometryCollectionTest`)
- L14 _prototype_ `void TestDeleteHiddenFaces();` (scope `GeometryCollectionTest`)
- L16 _prototype_ `void TestFillHoles();` (scope `GeometryCollectionTest`)

### `Source/Programs/HeadlessChaos/Public/GeometryCollection/GeometryCollectionTestClustering.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace GeometryCollectionTest`

### `Source/Programs/HeadlessChaos/Public/GeometryCollection/GeometryCollectionTestCollisionResolution.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace GeometryCollectionTest`

### `Source/Programs/HeadlessChaos/Public/GeometryCollection/GeometryCollectionTestCreation.h` (Public)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace GeometryCollectionTest`
- L8 _prototype_ `void CheckClassTypes();` (scope `GeometryCollectionTest`)
- L10 _prototype_ `void CheckIncrementMask();` (scope `GeometryCollectionTest`)
- L12 _prototype_ `void Creation();` (scope `GeometryCollectionTest`)
- L14 _prototype_ `void Empty();` (scope `GeometryCollectionTest`)
- L16 _prototype_ `void AppendTransformHierarchy();` (scope `GeometryCollectionTest`)
- L18 _prototype_ `void ContiguousElementsTest();` (scope `GeometryCollectionTest`)
- L20 _prototype_ `void DeleteFromEnd();` (scope `GeometryCollectionTest`)
- L22 _prototype_ `void DeleteFromStart();` (scope `GeometryCollectionTest`)
- L24 _prototype_ `void DeleteFromMiddle();` (scope `GeometryCollectionTest`)
- L26 _prototype_ `void DeleteBranch();` (scope `GeometryCollectionTest`)
- L28 _prototype_ `void DeleteRootLeafMiddle();` (scope `GeometryCollectionTest`)
- L30 _prototype_ `void DeleteEverything();` (scope `GeometryCollectionTest`)
- L32 _prototype_ `void ParentTransformTest();` (scope `GeometryCollectionTest`)
- L34 _prototype_ `void ReindexMaterialsTest();` (scope `GeometryCollectionTest`)
- L36 _prototype_ `void AttributeTransferTest();` (scope `GeometryCollectionTest`)
- L38 _prototype_ `void AttributeDependencyTest();` (scope `GeometryCollectionTest`)
- L40 _prototype_ `void IntListReindexOnDeletionTest();` (scope `GeometryCollectionTest`)
- L42 _prototype_ `void IntListSelfDependencyTest();` (scope `GeometryCollectionTest`)
- L44 _prototype_ `void AppendManagedArrayCollectionTest();` (scope `GeometryCollectionTest`)
- L46 _prototype_ `void AppendTransformCollectionTest();` (scope `GeometryCollectionTest`)
- L48 _prototype_ `void CollectionCycleTest();` (scope `GeometryCollectionTest`)

### `Source/Programs/HeadlessChaos/Public/GeometryCollection/GeometryCollectionTestDecimation.h` (Public)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace GeometryCollectionTest`
- L9 _prototype_ `void TestGeometryDecimation();` (scope `GeometryCollectionTest`)

### `Source/Programs/HeadlessChaos/Public/GeometryCollection/GeometryCollectionTestEvents.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace GeometryCollectionTest`

### `Source/Programs/HeadlessChaos/Public/GeometryCollection/GeometryCollectionTestFields.h` (Public)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace GeometryCollectionTest`
- L8 _prototype_ `void Fields_NoiseSample();` (scope `GeometryCollectionTest`)
- L9 _prototype_ `void Fields_RadialIntMask();` (scope `GeometryCollectionTest`)
- L10 _prototype_ `void Fields_RadialFalloff();` (scope `GeometryCollectionTest`)
- L11 _prototype_ `void Fields_PlaneFalloff();` (scope `GeometryCollectionTest`)
- L12 _prototype_ `void Fields_UniformVector();` (scope `GeometryCollectionTest`)
- L13 _prototype_ `void Fields_RaidalVector();` (scope `GeometryCollectionTest`)
- L14 _prototype_ `void Fields_SumVectorFullMult();` (scope `GeometryCollectionTest`)
- L15 _prototype_ `void Fields_SumVectorFullDiv();` (scope `GeometryCollectionTest`)
- L16 _prototype_ `void Fields_SumVectorFullAdd();` (scope `GeometryCollectionTest`)
- L17 _prototype_ `void Fields_SumVectorFullSub();` (scope `GeometryCollectionTest`)
- L18 _prototype_ `void Fields_SumVectorLeftSide();` (scope `GeometryCollectionTest`)
- L19 _prototype_ `void Fields_SumVectorRightSide();` (scope `GeometryCollectionTest`)
- L20 _prototype_ `void Fields_SumScalar();` (scope `GeometryCollectionTest`)
- L21 _prototype_ `void Fields_SumScalarRightSide();` (scope `GeometryCollectionTest`)
- L22 _prototype_ `void Fields_SumScalarLeftSide();` (scope `GeometryCollectionTest`)
- L23 _prototype_ `void Fields_Culling();` (scope `GeometryCollectionTest`)
- L24 _prototype_ `void Fields_SerializeAPI();` (scope `GeometryCollectionTest`)

### `Source/Programs/HeadlessChaos/Public/GeometryCollection/GeometryCollectionTestFramework.h` (Public)


#### enum `GeometryCollectionTest::WrapperType`  
`enum WrapperType`  
_L18-22_
- L20 _public enumerator_ `RigidBody`
- L21 _public enumerator_ `GeometryCollection`

#### enum `GeometryCollectionTest::ESimplicialType`  
`enum ESimplicialType`  
_L24-32_
- L26 _public enumerator_ `Chaos_Simplicial_Box`
- L27 _public enumerator_ `Chaos_Simplicial_Sphere`
- L28 _public enumerator_ `Chaos_Simplicial_GriddleBox`
- L29 _public enumerator_ `Chaos_Simplicial_Tetrahedron`
- L30 _public enumerator_ `Chaos_Simplicial_Imported_Sphere`
- L31 _public enumerator_ `Chaos_Simplicial_None`

#### struct `GeometryCollectionTest::WrapperBase`  
`struct WrapperBase`  
_L34-41_
- L36 _public member_ `WrapperType Type;`
- L37 _public function_ `WrapperBase(WrapperType TypeIn) : Type(TypeIn)`
- L38 _public function_ `virtual ~WrapperBase()`
- L39 _public function_ `template<class AS_T> AS_T* As()`

#### struct `GeometryCollectionTest::FGeometryCollectionWrapper`  
`struct FGeometryCollectionWrapper : public WrapperBase`  
_L43-59_
- inherits: `WrapperBase`
- L45 _public prototype_ `FGeometryCollectionWrapper();`
- L54 _public function_ `static WrapperType StaticType()` — FGeometryCollectionWrapper( TSharedPtr<FGeometryCollection> RestCollectionIn, TSharedPtr<FGeometryDynamicCollection> DynamicCollectionIn, FGeometryCollectionPhysicsProxy* PhysObjectIn) : WrapperBase(WrapperType::GeometryCollection) , RestCollection(RestCollectionIn) , DynamicCollection(DynamicCollectionIn) , PhysObject(PhysObjectIn) {}
- L55 _public member_ `TSharedPtr<FGeometryCollection> RestCollection;`
- L56 _public member_ `TSharedPtr<FGeometryDynamicCollection> DynamicCollection;`
- L57 _public member_ `FGeometryCollectionPhysicsProxy* PhysObject;`
- L58 _public member_ `FChaosUserData UserData;`

#### struct `GeometryCollectionTest::RigidBodyWrapper`  
`struct RigidBodyWrapper : public WrapperBase`  
_L61-72_
- inherits: `WrapperBase`
- L63 _public function_ `RigidBodyWrapper( TSharedPtr<Chaos::FChaosPhysicsMaterial> PhysicalMaterialIn, FPhysicsActorHandle ParticleIn) : WrapperBase(WrapperType::RigidBody) , PhysicalMaterial(PhysicalMaterialIn) , Particle(ParticleIn)`
- L69 _public function_ `static WrapperType StaticType()`
- L70 _public member_ `TSharedPtr<Chaos::FChaosPhysicsMaterial> PhysicalMaterial;`
- L71 _public member_ `FPhysicsActorHandle Particle;`

#### struct `GeometryCollectionTest::CreationParameters`  
`struct CreationParameters`  
_L75-104_
- L77 _public member_ `FTransform RootTransform = FTransform::Identity;`
- L82 _public member_ `FVector3f InitialLinearVelocity = FVector3f::ZeroVector;` — Implicit box uses Scale X, Y, Z for dimensions. Implicit sphere uses Scale X for radius.
- L83 _public member_ `EObjectStateTypeEnum DynamicState = EObjectStateTypeEnum::Chaos_Object_Dynamic;`
- L84 _public member_ `bool Simulating = true;`
- L85 _public member_ `FReal Mass = 1.0;`
- L86 _public member_ `bool bMassAsDensity = false;`
- L87 _public member_ `ECollisionTypeEnum CollisionType = ECollisionTypeEnum::Chaos_Surface_Volumetric;`
- L88 _public member_ `ESimplicialType SimplicialType = ESimplicialType::Chaos_Simplicial_Sphere;`
- L89 _public member_ `EImplicitTypeEnum ImplicitType = EImplicitTypeEnum::Chaos_Implicit_Sphere;`
- L90 _public member_ `float CollisionParticleFraction = 1.0f;`
- L91 _public member_ `EInitialVelocityTypeEnum InitialVelocityType = EInitialVelocityTypeEnum::Chaos_Initial_Velocity_None;`
- L92 _public member_ `TArray<FTransform> NestedTransforms;`
- L93 _public member_ `bool EnableClustering = true;`
- L94 _public member_ `FTransform GeomTransform = FTransform::Identity;`
- L95 _public member_ `TSharedPtr<FGeometryCollection> RestCollection = nullptr;`
- L96 _public member_ `int32 MaxClusterLevel = 100;`
- L97 _public member_ `int32 MaxSimulatedLevel = 100;`
- L98 _public member_ `TArray<float> DamageThreshold = { 1000.0 };`
- L99 _public member_ `Chaos::FClusterCreationParameters::EConnectionMethod ClusterConnectionMethod = Chaos::FClusterCreationParameters::EConnectionMethod::PointImplicit;`
- L100 _public member_ `int32 CollisionGroup = 0;`
- L101 _public member_ `int32 MinLevelSetResolution = 5;`
- L102 _public member_ `int32 MaxLevelSetResolution = 10;`
- L103 _public member_ `int32 ClusterGroupIndex = 0;`

#### enum `GeometryCollectionTest::GeometryType`  
`enum GeometryType`  
_L107-111_
- L108 _public enumerator_ `GeometryCollectionWithSingleRigid`
- L109 _public enumerator_ `RigidFloor`
- L110 _public enumerator_ `GeometryCollectionWithSuppliedRestCollection`

#### struct `GeometryCollectionTest::TNewSimulationObject`  
`template <GeometryType> struct TNewSimulationObject`  
_L115-118_
- L117 _public prototype_ `static WrapperBase* Init(const CreationParameters Params = CreationParameters());`

#### struct `GeometryCollectionTest::FrameworkParameters`  
`struct FrameworkParameters`  
_L124-129_
- L126 _public member_ `FReal Dt = 1.0 / 60.0;`
- L127 _public member_ `FReal AsyncDt = -1.0;`
- L128 _public member_ `Chaos::EThreadingMode ThreadingMode = Chaos::EThreadingMode::SingleThread;`

#### class `GeometryCollectionTest::FFramework`  
`class FFramework`  
_L131-146_
- L135 _public prototype_ `FFramework(FrameworkParameters Properties = FrameworkParameters());`
- L136 _public prototype_ `virtual ~FFramework();`
- L138 _public prototype_ `void AddSimulationObject(WrapperBase* Object);`
- L139 _public prototype_ `void RemoveSimulationObject(WrapperBase* Object);`
- L140 _public prototype_ `void Initialize();`
- L141 _public prototype_ `void Advance();`
- L142 _public member_ `FReal Dt;`
- L143 _public member_ `FChaosSolversModule* Module = FChaosSolversModule::GetModule();`
- L144 _public member_ `Chaos::FPBDRigidsSolver* Solver;`
- L145 _public member_ `TArray< WrapperBase* > PhysicsObjects;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace GeometryCollectionTest`
- L120 _prototype_ `template<> WrapperBase* TNewSimulationObject<GeometryType::GeometryCollectionWithSingleRigid>::Init(const CreationParameters);` (scope `GeometryCollectionTest::TNewSimulationObject::GeometryCollectionWithSingleRigid`)
- L121 _prototype_ `template<> WrapperBase* TNewSimulationObject<GeometryType::GeometryCollectionWithSingleRigid>::Init(const CreationParameters);` (scope `GeometryCollectionTest::TNewSimulationObject::RigidFloor`)
- L122 _prototype_ `template<> WrapperBase* TNewSimulationObject<GeometryType::GeometryCollectionWithSingleRigid>::Init(const CreationParameters);` (scope `GeometryCollectionTest::TNewSimulationObject::GeometryCollectionWithSuppliedRestCollection`)

### `Source/Programs/HeadlessChaos/Public/GeometryCollection/GeometryCollectionTestImplicitCapsule.h` (Public)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace GeometryCollectionTest`
- L9 _prototype_ `void TestImplicitCapsule();` (scope `GeometryCollectionTest`)

### `Source/Programs/HeadlessChaos/Public/GeometryCollection/GeometryCollectionTestImplicitCylinder.h` (Public)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace GeometryCollectionTest`
- L9 _prototype_ `void TestImplicitCylinder();` (scope `GeometryCollectionTest`)

### `Source/Programs/HeadlessChaos/Public/GeometryCollection/GeometryCollectionTestImplicitSphere.h` (Public)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace GeometryCollectionTest`
- L9 _prototype_ `void TestImplicitSphere();` (scope `GeometryCollectionTest`)

### `Source/Programs/HeadlessChaos/Public/GeometryCollection/GeometryCollectionTestInitilization.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace GeometryCollectionTest`

### `Source/Programs/HeadlessChaos/Public/GeometryCollection/GeometryCollectionTestMassProperties.h` (Public)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace GeometryCollectionTest`

### `Source/Programs/HeadlessChaos/Public/GeometryCollection/GeometryCollectionTestMatrices.h` (Public)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace GeometryCollectionTest`
- L9 _prototype_ `void BasicGlobalMatrices();` (scope `GeometryCollectionTest`)
- L11 _prototype_ `void ReparentingMatrices();` (scope `GeometryCollectionTest`)
- L13 _prototype_ `void TransformMatrixElement();` (scope `GeometryCollectionTest`)

### `Source/Programs/HeadlessChaos/Public/GeometryCollection/GeometryCollectionTestProximity.h` (Public)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace GeometryCollectionTest`
- L9 _prototype_ `void BuildProximity();` (scope `GeometryCollectionTest`)
- L11 _prototype_ `void GeometryDeleteFromStart();` (scope `GeometryCollectionTest`)
- L13 _prototype_ `void GeometryDeleteFromEnd();` (scope `GeometryCollectionTest`)
- L15 _prototype_ `void GeometryDeleteFromMiddle();` (scope `GeometryCollectionTest`)
- L17 _prototype_ `void GeometryDeleteMultipleFromMiddle();` (scope `GeometryCollectionTest`)
- L19 _prototype_ `void GeometryDeleteRandom();` (scope `GeometryCollectionTest`)
- L21 _prototype_ `void GeometryDeleteRandom2();` (scope `GeometryCollectionTest`)
- L23 _prototype_ `void GeometryDeleteAll();` (scope `GeometryCollectionTest`)
- L25 _prototype_ `void GeometrySwapFlat();` (scope `GeometryCollectionTest`)
- L27 _prototype_ `void TestFracturedGeometry();` (scope `GeometryCollectionTest`)

### `Source/Programs/HeadlessChaos/Public/GeometryCollection/GeometryCollectionTestResponse.h` (Public)


#### class `GeometryCollectionTest::ExampleResponse`  
`class ExampleResponse`  
_L8-17_
- L11 _public function_ `ExampleResponse() : ErrorFlag(false)`
- L12 _public function_ `virtual ~ExampleResponse()`
- L13 _public prototype_ `virtual void ExpectTrue(bool, FString Reason = "");`
- L14 _public function_ `virtual bool HasError()`
- L15 _public member_ `TArray<FString> Reasons;`
- L16 _public member_ `bool ErrorFlag;`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace GeometryCollectionTest`

### `Source/Programs/HeadlessChaos/Public/GeometryCollection/GeometryCollectionTestSerialization.h` (Public)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace GeometryCollectionTests`
- L8 _prototype_ `void GeometryCollectionSerialization();` (scope `GeometryCollectionTests`)

### `Source/Programs/HeadlessChaos/Public/GeometryCollection/GeometryCollectionTestSimulation.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace GeometryCollectionTest`

### `Source/Programs/HeadlessChaos/Public/GeometryCollection/GeometryCollectionTestSimulationField.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace GeometryCollectionTest`

### `Source/Programs/HeadlessChaos/Public/GeometryCollection/GeometryCollectionTestSimulationSolver.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace GeometryCollectionTest`

### `Source/Programs/HeadlessChaos/Public/GeometryCollection/GeometryCollectionTestSimulationStreaming.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace GeometryCollectionTest`
- L9 _prototype_ `void RigidBodies_Streaming_StartSolverEmpty();` (scope `GeometryCollectionTest`)
- L11 _prototype_ `void RigidBodies_Streaming_BulkInitialization();` (scope `GeometryCollectionTest`)
- L13 _prototype_ `void RigidBodies_Streaming_DeferedClusteringInitialization();` (scope `GeometryCollectionTest`)

### `Source/Programs/HeadlessChaos/Public/GeometryCollection/GeometryCollectionTestSpatialHash.h` (Public)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace GeometryCollectionTest`
- L9 _prototype_ `void GetClosestPointsTest1();` (scope `GeometryCollectionTest`)
- L11 _prototype_ `void GetClosestPointsTest2();` (scope `GeometryCollectionTest`)
- L13 _prototype_ `void GetClosestPointsTest3();` (scope `GeometryCollectionTest`)
- L15 _prototype_ `void GetClosestPointTest();` (scope `GeometryCollectionTest`)
- L17 _prototype_ `void HashTableUpdateTest();` (scope `GeometryCollectionTest`)
- L19 _prototype_ `void HashTablePressureTest();` (scope `GeometryCollectionTest`)

### `Source/Programs/HeadlessChaos/Public/GeometryCollection/GeometryCollectionTestUtility.h` (Public)


#### Free symbols / members of external scopes

- L16 _namespace_ `namespace GeometryCollectionTest`
- L18 _prototype_ `TSharedPtr<FGeometryDynamicCollection> GeometryCollectionToGeometryDynamicCollection(TSharedPtr<const FGeometryCollection> InputCollection, EObjectStateTypeEnum DynamicStateDefault = EObjectStateTypeEnum::Chaos_Object_Dynamic);` (scope `GeometryCollectionTest`)
- L20 _prototype_ `TSharedPtr<FGeometryCollection> CreateClusteredBody(FVector Position);` (scope `GeometryCollectionTest`)
- L21 _prototype_ `TSharedPtr<FGeometryCollection> CreateClusteredBody_OnePartent_FourBodies(FVector Position);` (scope `GeometryCollectionTest`)
- L22 _prototype_ `TSharedPtr<FGeometryCollection> CreateClusteredBody_TwoParents_TwoBodies(FVector Position);` (scope `GeometryCollectionTest`)
- L23 _prototype_ `TSharedPtr<FGeometryCollection> CreateClusteredBody_TwoParents_TwoBodiesB(FVector Position);` (scope `GeometryCollectionTest`)
- L24 _prototype_ `TSharedPtr<FGeometryCollection> CreateClusteredBody_FourParents_OneBody(FVector Position);` (scope `GeometryCollectionTest`)
- L25 _prototype_ `TSharedPtr<FGeometryCollection> CreateClusteredBody_TwoByTwo_ThreeTransform(FVector Position);` (scope `GeometryCollectionTest`)
- L26 _prototype_ `TSharedPtr<FGeometryCollection> CreateClusteredBody_ThreeByTwo_ThreeTransform(FVector Position);` (scope `GeometryCollectionTest`)
- L27 _prototype_ `TSharedPtr<FGeometryCollection> CreateClusteredBody_FracturedGeometry(FVector Position = FVector(0));` (scope `GeometryCollectionTest`)
- L29 _prototype_ `void InitMaterialToZero(Chaos::FChaosPhysicsMaterial * PhysicalMaterial);` (scope `GeometryCollectionTest`)

### `Source/Programs/HeadlessChaos/Public/GeometryCollection/GeometryCollectionTestVisibility.h` (Public)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace GeometryCollectionTest`
- L8 _prototype_ `void TestHideVertices();` (scope `GeometryCollectionTest`)

### `Source/Programs/HeadlessChaos/Public/HeadlessChaos.h` (Public)


#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogHeadlessChaos, Verbose, All);`
- L15 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogHeadlessChaos, Verbose, All);`

### `Source/Programs/HeadlessChaos/Public/HeadlessChaosApp.h` (Public)
_(no declarations extracted)_

### `Source/Programs/HeadlessChaos/Public/HeadlessChaosCache.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace ChaosTest`
- L8 _namespace_ `namespace ChaosCache` (scope `ChaosTest`)
- L10 _prototype_ `void TrackCompressionTest();` (scope `ChaosTest::ChaosCache`)

### `Source/Programs/HeadlessChaos/Public/HeadlessChaosCollisionConstraints.h` (Public)


#### class `Chaos::FPBDCollisionConstraintAccessor`  
`class FPBDCollisionConstraintAccessor`  
_L28-180_
- desc: Test collision constraints.
- L31 _public typedef_ `using FCollisionConstraints = FPBDCollisionConstraints;`
- L32 _public typedef_ `using FConstraintContainerHandle = FPBDCollisionConstraintHandle;`
- L33 _public typedef_ `using FConstraintHandleAllocator = TConstraintHandleAllocator<FPBDCollisionConstraint>;`
- L34 _public typedef_ `using FConstraintHandleID = TPair<const FGeometryParticleHandle*, const FGeometryParticleHandle*>;`
- L35 _public typedef_ `using FCollisionDetector = FSpatialAccelerationCollisionDetector;`
- L36 _public typedef_ `using FAccelerationStructure = TBoundingVolume<FAccelerationStructureHandle>;`
- L38 _public function_ `FPBDCollisionConstraintAccessor() : EmptyParticles(UniqueIndices) , SpatialAcceleration(EmptyParticles.GetNonDisabledView()) , CollisionConstraints(EmptyParticles, EmptyCollided, EmptyPhysicsMaterials, EmptyUniquePhysicsMaterials, nullptr) , BroadPhase(EmptyParticles) , CollisionDetector(BroadPhase, CollisionConstraints) , ConstraintSolver(Iterations)`
- L53 _public function_ `FPBDCollisionConstraintAccessor(const FPBDRigidsSOAs& InParticles, TArrayCollectionArray<bool>& Collided, const TArrayCollectionArray<TSerializablePtr<FChaosPhysicsMaterial>>& PerParticleMaterials, const TArrayCollectionArray<TUniquePtr<FChaosPhysicsMaterial>>& PerParticleUniqueMaterials, const int32 PushOutIterations, const int32 PushOutPairIterations) : EmptyParticles(UniqueIndices) , SpatialAcceleration(InParticles.GetNonDisabledView()) , CollisionConstraints(InParticles, Collided, PerParticleMaterials, PerParticleUniqueMaterials, nullptr) , BroadPhase(InParticles) , CollisionDetector(BroadPhase, CollisionConstraints) , ConstraintSolver(Iterations)`
- L69 _public function_ `virtual ~FPBDCollisionConstraintAccessor()`
- L71 _public function_ `void ComputeConstraints(FReal Dt)`
- L86 _public function_ `void Update(FPBDCollisionConstraint& Constraint)`
- L103 _public function_ `void UpdateLevelsetConstraint(FPBDCollisionConstraint& Constraint)`
- L115 _public function_ `int32 NumConstraints() const`
- L120 _public function_ `FPBDCollisionConstraint& GetConstraint(int32 Index)`
- L129 _public function_ `const FConstraintContainerHandle* GetConstraintHandle(int32 ConstraintIndex) const`
- L134 _public function_ `FConstraintContainerHandle* GetConstraintHandle(int32 ConstraintIndex)`
- L139 _public function_ `void Apply(const FReal Dt, const int32 NumIts)`
- L146 _public function_ `void ApplyPushOut(const FReal Dt, int32 NumIts)`
- L153 _public function_ `void GatherInput(FReal Dt)`
- L161 _public function_ `void ScatterOutput(FReal Dt)`
- L167 _public member_ `FPBDCollisionConstraint EmptyConstraint;`
- L168 _public member_ `FParticleUniqueIndicesMultithreaded UniqueIndices;`
- L169 _public member_ `FPBDRigidsSOAs EmptyParticles;`
- L170 _public member_ `TArrayCollectionArray<bool> EmptyCollided;`
- L171 _public member_ `TArrayCollectionArray<TSerializablePtr<FChaosPhysicsMaterial>> EmptyPhysicsMaterials;`
- L172 _public member_ `TArrayCollectionArray<TUniquePtr<FChaosPhysicsMaterial>> EmptyUniquePhysicsMaterials;`
- L174 _public member_ `FAccelerationStructure SpatialAcceleration;`
- L175 _public member_ `FCollisionConstraints CollisionConstraints;`
- L176 _public member_ `FSpatialAccelerationBroadPhase BroadPhase;`
- L177 _public member_ `FCollisionDetector CollisionDetector;`
- L178 _public member_ `Private::FPBDSceneConstraintGroupSolver ConstraintSolver;`
- L179 _public member_ `Private::FIterationSettings Iterations;`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace Chaos`

### `Source/Programs/HeadlessChaos/Public/HeadlessChaosTestBP.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace ChaosTest`
- L10 _prototype_ `void BPPerfTest();` (scope `ChaosTest`)

### `Source/Programs/HeadlessChaos/Public/HeadlessChaosTestBroadphase.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace ChaosTest`
- L10 _prototype_ `void GridBPTest();` (scope `ChaosTest`)
- L12 _prototype_ `void GridBPEarlyExitTest();` (scope `ChaosTest`)
- L14 _prototype_ `void GridBPTest2();` (scope `ChaosTest`)
- L16 _prototype_ `void AABBTreeTest();` (scope `ChaosTest`)
- L18 _prototype_ `void AABBTreeTestDynamic();` (scope `ChaosTest`)
- L20 _prototype_ `void AABBTreeDirtyTreeTest();` (scope `ChaosTest`)
- L22 _prototype_ `void AABBTreeDirtyGridTest();` (scope `ChaosTest`)
- L24 _prototype_ `void AABBTreeTimesliceTest();` (scope `ChaosTest`)
- L26 _prototype_ `void DoForSweepIntersectCellsImpTest();` (scope `ChaosTest`)
- L28 _prototype_ `void AABBTreeDirtyGridFunctionsWithEdgeCase();` (scope `ChaosTest`)
- L30 _prototype_ `void BroadphaseCollectionTest();` (scope `ChaosTest`)
- L32 _prototype_ `void BoundingVolumeNoBoundsTest();` (scope `ChaosTest`)
- L34 _prototype_ `void SpatialAccelerationDirtyAndGlobalQueryStrestTest();` (scope `ChaosTest`)

### `Source/Programs/HeadlessChaos/Public/HeadlessChaosTestCloth.h` (Public)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace ChaosTest`
- L8 _prototype_ `void DeformableGravity();` (scope `ChaosTest`) — /
- L11 _prototype_ `void EdgeConstraints();` (scope `ChaosTest`) — /
- L14 _prototype_ `void ClothCollection();` (scope `ChaosTest`) — Test Remove & Insert at position as used in the ClothCollection.

### `Source/Programs/HeadlessChaos/Public/HeadlessChaosTestClustering.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace ChaosTest`
- L11 _prototype_ `void ImplicitCluster();` (scope `ChaosTest`) — /
- L13 _prototype_ `void FractureCluster();` (scope `ChaosTest`)
- L15 _prototype_ `void PartialFractureCluster();` (scope `ChaosTest`)

### `Source/Programs/HeadlessChaos/Public/HeadlessChaosTestCollisions.h` (Public)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace ChaosTest`
- L15 _prototype_ `void LevelsetConstraint();` (scope `ChaosTest`)
- L17 _prototype_ `void LevelsetConstraintGJK();` (scope `ChaosTest`)
- L19 _prototype_ `void CollisionBoxPlane();` (scope `ChaosTest`)
- L21 _prototype_ `void CollisionConvexConvex();` (scope `ChaosTest`)
- L23 _prototype_ `void CollisionBoxPlaneZeroResitution();` (scope `ChaosTest`)
- L25 _prototype_ `void CollisionBoxPlaneRestitution();` (scope `ChaosTest`)
- L27 _prototype_ `void CollisionCubeCubeRestitution();` (scope `ChaosTest`)
- L29 _prototype_ `void CollisionBoxToStaticBox();` (scope `ChaosTest`)
- L31 _prototype_ `void CollisionCapsuleCapsule();` (scope `ChaosTest`)

### `Source/Programs/HeadlessChaos/Public/HeadlessChaosTestConstraints.h` (Public)


#### class `ChaosTest::FConstraintsTest`  
`template <typename TEvolution> class FConstraintsTest`  
_L19-108_
- desc: Base class for constraint tests. Provides a basic sim with no builtin constraint support.
- L23 _public function_ `FConstraintsTest(const int32 NumIterations, const FReal Gravity) : SOAs(UniqueIndices) , Evolution(SOAs, PhysicalMaterials)`
- L42 _public function_ `virtual ~FConstraintsTest()`
- L47 _public function_ `void EnableSleeping()` — By default the tests are set up to disable sleeping. Undo this by giving the physical material a non-zero sleep threshold
- L55 _public function_ `FGeometryParticleHandle* AddParticleBox(const FVec3& Position, const FRotation3& Rotation, const FVec3& Size, FReal Mass)`
- L81 _public function_ `void ResetParticle(FGeometryParticleHandle* Particle, const FVec3& Position, const FRotation3& Rotation, const FVec3& Velocity, const FVec3& AngularVelocity)`
- L98 _public member_ `FParticleUniqueIndicesMultithreaded UniqueIndices;` — Solver state
- L99 _public member_ `FPBDRigidsSOAs SOAs;`
- L100 _public member_ `TEvolution Evolution;`
- L101 _public member_ `TUniquePtr<FChaosPhysicsMaterial> PhysicalMaterial;`
- L102 _public member_ `THandleArray<FChaosPhysicsMaterial> PhysicalMaterials;`
- L104 _public function_ `FGeometryParticleHandle* GetParticle(const int32 Idx)`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace ChaosTest`

### `Source/Programs/HeadlessChaos/Public/HeadlessChaosTestEPA.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace ChaosTest`
- L10 _prototype_ `void EPAInitTest();` (scope `ChaosTest`)
- L12 _prototype_ `void EPASimpleTest();` (scope `ChaosTest`)

### `Source/Programs/HeadlessChaos/Public/HeadlessChaosTestEvolution.h` (Public)


#### class `ChaosTest::FEvolutionTest`  
`class FEvolutionTest`  
_L18-196_
- desc: Base class for evolution tests
- L22 _public function_ `FEvolutionTest() : SOAs(UniqueIndices) , Evolution(SOAs, PhysicalMaterials)`
- L36 _public function_ `virtual ~FEvolutionTest()`
- L40 _public function_ `FPBDRigidsEvolutionGBF& GetEvolution()`
- L45 _public function_ `FPBDCollisionConstraints& GetCollisionConstraints()`
- L51 _public function_ `FGeometryParticleHandle* GetParticle(const int32 ParticleIndex)` — Get a particle. The index is the order in which they were created by the AddParticleXXX methods
- L57 _public function_ `void EnableSleeping()` — Set up the physical material to allow sleeping (sleeping is enabled by default)
- L67 _public function_ `void DisableSleeping()` — Set up the physical material to disable sleeping (sleeping is enabled by default)
- L76 _public function_ `void Tick()`
- L82 _public function_ `bool TickUntilSleep(const int32 MaxTicks = 1000)`
- L93 _public function_ `bool AreAllParticlesAsleep() const`
- L109 _public function_ `FPBDRigidParticleHandle* AddParticleBox(const FVec3& Position, const FRotation3& Rotation, const FVec3& Size, FReal Mass)` — Create a dynamic or kinematic particle depending on the mass
- L138 _public function_ `FGeometryParticleHandle* AddStaticParticleBox(const FVec3& Position, const FRotation3& Rotation, const FVec3& Size)` — Add a static particle, e.g., for the floor
- L154 _public function_ `FGeometryParticleHandle* AddParticleFloor(const FVec3& Size)` — Add a static particle for the floor consisting of a box with the specified size and the upper surface at Z=0
- L159 _public function_ `void ResetParticle(FGeometryParticleHandle* Particle, const FVec3& Position, const FRotation3& Rotation, const FVec3& Velocity, const FVec3& AngularVelocity)`
- L175 _public function_ `void OnMaterialChanged()`
- L187 _public member_ `FParticleUniqueIndicesMultithreaded UniqueIndices;` — Solver state
- L188 _public member_ `FPBDRigidsSOAs SOAs;`
- L189 _public member_ `FPBDRigidsEvolutionGBF Evolution;`
- L190 _public member_ `TUniquePtr<FChaosPhysicsMaterial> PhysicalMaterial;`
- L191 _public member_ `THandleArray<FChaosPhysicsMaterial> PhysicalMaterials;`
- L193 _public member_ `TArray<FGeometryParticleHandle*> Particles;`
- L195 _public member_ `FReal Dt;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace ChaosTest`
- L180 _function_ `` (scope `ChaosTest::FEvolutionTest::OnMaterialChanged`)

### `Source/Programs/HeadlessChaos/Public/HeadlessChaosTestForces.h` (Public)
_(no declarations extracted)_

### `Source/Programs/HeadlessChaos/Public/HeadlessChaosTestGJK.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace ChaosTest`
- L11 _prototype_ `void SimplexLine();` (scope `ChaosTest`) — /
- L13 _prototype_ `void SimplexTriangle();` (scope `ChaosTest`)
- L15 _prototype_ `void SimplexTetrahedron();` (scope `ChaosTest`)
- L17 _prototype_ `void GJKSphereSphereTest();` (scope `ChaosTest`)
- L19 _prototype_ `void GJKSphereBoxTest();` (scope `ChaosTest`)
- L21 _prototype_ `void GJKSphereCapsuleTest();` (scope `ChaosTest`)
- L23 _prototype_ `void GJKSphereConvexTest();` (scope `ChaosTest`)
- L25 _prototype_ `void GJKSphereScaledSphereTest();` (scope `ChaosTest`)
- L27 _prototype_ `void GJKSphereSphereSweep();` (scope `ChaosTest`)
- L29 _prototype_ `void GJKSphereBoxSweep();` (scope `ChaosTest`)
- L31 _prototype_ `void GJKSphereCapsuleSweep();` (scope `ChaosTest`)
- L33 _prototype_ `void GJKSphereConvexSweep();` (scope `ChaosTest`)
- L35 _prototype_ `void GJKSphereScaledSphereSweep();` (scope `ChaosTest`)
- L37 _prototype_ `void GJKSphereTransformedSphereSweep();` (scope `ChaosTest`)
- L39 _prototype_ `void GJKBoxCapsuleSweep();` (scope `ChaosTest`)
- L41 _prototype_ `void GJKBoxBoxSweep();` (scope `ChaosTest`)
- L43 _prototype_ `void GJKCapsuleConvexInitialOverlapSweep();` (scope `ChaosTest`)
- L45 _prototype_ `void GJKLargeDistanceCapsuleSweep();` (scope `ChaosTest`)
- L47 _prototype_ `void GJKConvexCapsule();` (scope `ChaosTest`)

### `Source/Programs/HeadlessChaos/Public/HeadlessChaosTestHandles.h` (Public)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace ChaosTest`
- L7 _namespace_ `namespace Handles` (scope `ChaosTest`)
- L9 _prototype_ `void HandleArrayTest();` (scope `ChaosTest::Handles`)
- L11 _prototype_ `void HandleHeapTest();` (scope `ChaosTest::Handles`)
- L13 _prototype_ `void HandleSerializeTest();` (scope `ChaosTest::Handles`)
- L15 _prototype_ `void HandleArrayIteratorTest();` (scope `ChaosTest::Handles`)

### `Source/Programs/HeadlessChaos/Public/HeadlessChaosTestImplicits.h` (Public)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace ChaosTest`
- L16 _prototype_ `void ImplicitCube();` (scope `ChaosTest`) — /
- L19 _prototype_ `void ImplicitPlane();` (scope `ChaosTest`) — /
- L22 _prototype_ `void ImplicitTetrahedron();` (scope `ChaosTest`) — /
- L25 _prototype_ `void ImplicitSphere();` (scope `ChaosTest`) — /
- L28 _prototype_ `void ImplicitCylinder();` (scope `ChaosTest`) — /
- L31 _prototype_ `void ImplicitTaperedCylinder();` (scope `ChaosTest`) — /
- L34 _prototype_ `void ImplicitTaperedCapsule();` (scope `ChaosTest`) — /
- L37 _prototype_ `void ImplicitCapsule();` (scope `ChaosTest`) — /
- L40 _prototype_ `void ImplicitScaled();` (scope `ChaosTest`) — /
- L43 _prototype_ `void ImplicitTransformed();` (scope `ChaosTest`) — /
- L46 _prototype_ `void ImplicitIntersection();` (scope `ChaosTest`) — /
- L49 _prototype_ `void ImplicitUnion();` (scope `ChaosTest`) — /
- L52 _prototype_ `void ImplicitLevelset();` (scope `ChaosTest`) — /
- L55 _prototype_ `void RasterizationImplicit();` (scope `ChaosTest`) — /
- L57 _prototype_ `void RasterizationImplicitWithHole();` (scope `ChaosTest`)
- L59 _prototype_ `void ConvexHull();` (scope `ChaosTest`)
- L61 _prototype_ `void ConvexHull2();` (scope `ChaosTest`)
- L63 _prototype_ `void Simplify();` (scope `ChaosTest`)
- L65 _prototype_ `void ImplicitScaled2();` (scope `ChaosTest`)
- L67 _prototype_ `void UpdateImplicitUnion();` (scope `ChaosTest`)

### `Source/Programs/HeadlessChaos/Public/HeadlessChaosTestMostOpposing.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace ChaosTest`
- L10 _prototype_ `void ConvexMostOpposing();` (scope `ChaosTest`)
- L12 _prototype_ `void TrimeshMostOpposing();` (scope `ChaosTest`)
- L14 _prototype_ `void ScaledMostOpposing();` (scope `ChaosTest`)

### `Source/Programs/HeadlessChaos/Public/HeadlessChaosTestOverlap.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace ChaosTest`
- L9 _prototype_ `void OverlapTriMesh();` (scope `ChaosTest`)

### `Source/Programs/HeadlessChaos/Public/HeadlessChaosTestParticleHandle.h` (Public)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace ChaosTest`
- L7 _prototype_ `void ParticleIteratorTest();` (scope `ChaosTest`)
- L9 _prototype_ `void ParticleHandleTest();` (scope `ChaosTest`)
- L11 _prototype_ `void AccelerationStructureHandleComparison();` (scope `ChaosTest`)
- L13 _prototype_ `void HandleObjectStateChangeTest();` (scope `ChaosTest`)

### `Source/Programs/HeadlessChaos/Public/HeadlessChaosTestRaycast.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace ChaosTest`
- L10 _prototype_ `void SphereRaycast();` (scope `ChaosTest`)
- L12 _prototype_ `void PlaneRaycast();` (scope `ChaosTest`)
- L14 _prototype_ `void CylinderRaycast();` (scope `ChaosTest`)
- L16 _prototype_ `void TaperedCylinderRaycast();` (scope `ChaosTest`)
- L18 _prototype_ `void CapsuleRaycast();` (scope `ChaosTest`)
- L20 _prototype_ `void CapsuleRaycastFastLargeDistance();` (scope `ChaosTest`)
- L22 _prototype_ `void CapsuleRaycastMissWithEndPointOnBounds();` (scope `ChaosTest`)
- L24 _prototype_ `void TriangleRaycast();` (scope `ChaosTest`)
- L26 _prototype_ `void TriangleRaycastDenegerated();` (scope `ChaosTest`)
- L28 _prototype_ `void BoxRaycast();` (scope `ChaosTest`)
- L30 _prototype_ `void VectorizedAABBRaycast();` (scope `ChaosTest`)
- L32 _prototype_ `void ScaledRaycast();` (scope `ChaosTest`)
- L34 _prototype_ `void TransformedRaycast();` (scope `ChaosTest`)
- L36 _prototype_ `void UnionRaycast();` (scope `ChaosTest`)
- L38 _prototype_ `void IntersectionRaycast();` (scope `ChaosTest`)

### `Source/Programs/HeadlessChaos/Public/HeadlessChaosTestSerialization.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace ChaosTest`
- L10 _prototype_ `void SimpleTypesSerialization();` (scope `ChaosTest`)
- L12 _prototype_ `void SimpleObjectsSerialization();` (scope `ChaosTest`)
- L14 _prototype_ `void SharedObjectsSerialization();` (scope `ChaosTest`)
- L16 _prototype_ `void GraphSerialization();` (scope `ChaosTest`)
- L18 _prototype_ `void ObjectUnionSerialization();` (scope `ChaosTest`)
- L20 _prototype_ `void ParticleSerialization();` (scope `ChaosTest`)
- L22 _prototype_ `void BVHSerialization();` (scope `ChaosTest`)
- L24 _prototype_ `void RigidParticlesSerialization();` (scope `ChaosTest`)
- L26 _prototype_ `void BVHParticlesSerialization();` (scope `ChaosTest`)
- L28 _prototype_ `void GeometryCollectionSerialization();` (scope `ChaosTest`)
- L30 _prototype_ `void EvolutionPerfHarness();` (scope `ChaosTest`)
- L32 _prototype_ `void HeightFieldSerialization();` (scope `ChaosTest`)

### `Source/Programs/HeadlessChaos/Public/HeadlessChaosTestSolverCommandList.h` (Public)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace ChaosTest`
- L8 _prototype_ `template <typename T> void CommandListTest();` (scope `ChaosTest`)

### `Source/Programs/HeadlessChaos/Public/HeadlessChaosTestSolverProxies.h` (Public)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace ChaosTest`
- L7 _prototype_ `void SingleParticleProxySingleThreadTest();` (scope `ChaosTest`)
- L9 _prototype_ `void SingleParticleProxyTaskGraphTest();` (scope `ChaosTest`)
- L11 _prototype_ `void SingleParticleProxyWakeEventPropergationTest();` (scope `ChaosTest`)

### `Source/Programs/HeadlessChaos/Public/HeadlessChaosTestSpatialHashing.h` (Public)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace ChaosTest`
- L17 _prototype_ `template<class T> void SpatialHashing();` (scope `ChaosTest`) — /

### `Source/Programs/HeadlessChaos/Public/HeadlessChaosTestSweep.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace ChaosTest`
- L11 _prototype_ `void CapsuleSweepAgainstTriMeshReal();` (scope `ChaosTest`)

### `Source/Programs/HeadlessChaos/Public/HeadlessChaosTestTriangleMesh.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace ChaosTest`
- L10 _prototype_ `void TriangleMeshProjectTest();` (scope `ChaosTest`)

### `Source/Programs/HeadlessChaos/Public/HeadlessChaosTestUtility.h` (Public)


#### Free symbols / members of external scopes

- L23 _namespace_ `namespace Chaos`
- L28 _namespace_ `namespace ChaosTest`
- L35 _macro_ `#define EXPECT_VECTOR_NEAR(A,B,T) EXPECT_THAT(A, VectorNear(B, T)) << *FString("Expected: " + B.ToString() + "\nActual: " + A.ToString());` — Expects each component of the vector is within T of its corresponding component in A.
- L37 _macro_ `#define EXPECT_VECTOR_NEAR_DEFAULT(A,B) EXPECT_THAT(A, VectorNear(B, KINDA_SMALL_NUMBER)) << *FString("Expected: " + B.ToString() + "\nActual: " + A.ToString())` — Default comparison to KINDA_SMALL_NUMBER.
- L39 _macro_ `#define EXPECT_VECTOR_NEAR_ERR(A,B,T,E) EXPECT_THAT(A, VectorNear(B, T)) << *(FString("Expected: " + B.ToString() + "\nActual: " + A.ToString() + "\n") + E);` — Print an additional error string if the expect fails.
- L42 _macro_ `#define EXPECT_VECTOR_FLOAT_EQ(A, B) EXPECT_FLOAT_EQ(A.X, B.X); EXPECT_FLOAT_EQ(A.Y, B.Y); EXPECT_FLOAT_EQ(A.Z, B.Z);` — Similar to EXPECT_VECTOR_NEAR_DEFAULT but only prints the component(s) that are wrong, and prints with more precision.
- L44 _macro_ `#define EXPECT_VECTOR_FLOAT_EQ_ERR(A, B, E) EXPECT_FLOAT_EQ(A.X, B.X) << *E; EXPECT_FLOAT_EQ(A.Y, B.Y) << *E; EXPECT_FLOAT_EQ(A.Z, B.Z) << *E;` — Print an additional error string if the expect fails.
- L47 _prototype_ `int32 AppendAnalyticSphere(FPBDRigidParticles& InParticles, FReal Scale = (FReal)1);` (scope `ChaosTest`) — /
- L50 _prototype_ `int32 AppendAnalyticBox(FPBDRigidParticles& InParticles, FVec3 Scale = FVec3(1));` (scope `ChaosTest`) — /
- L53 _prototype_ `int32 AppendParticleBox(FPBDRigidParticles& InParticles, FVec3 Scale = FVec3(1), TArray<TVec3<int32>>* OutElements = nullptr);` (scope `ChaosTest`) — /
- L55 _prototype_ `FPBDRigidParticleHandle* AppendDynamicParticleBox(FPBDRigidsSOAs& SOAs, const FVec3& Scale = FVec3(1), TArray<TVec3<int32>>* OutElements = nullptr);` (scope `ChaosTest`)
- L57 _prototype_ `FPBDRigidParticleHandle* AppendDynamicParticleBoxMargin(FPBDRigidsSOAs& SOAs, const FVec3& Scale, FReal Margin, TArray<TVec3<int32>>* OutElements = nullptr);` (scope `ChaosTest`)
- L59 _prototype_ `FPBDRigidParticleHandle* AppendDynamicParticleSphere(FPBDRigidsSOAs& SOAs, const FVec3& Scale = FVec3(1), TArray<TVec3<int32>>* OutElements = nullptr);` (scope `ChaosTest`)
- L61 _prototype_ `FPBDRigidParticleHandle* AppendDynamicParticleCylinder(FPBDRigidsSOAs& SOAs, const FVec3& Scale = FVec3(1), TArray<TVec3<int32>>* OutElements = nullptr);` (scope `ChaosTest`)
- L63 _prototype_ `FPBDRigidParticleHandle* AppendDynamicParticleTaperedCylinder(FPBDRigidsSOAs& SOAs, const FVec3& Scale = FVec3(1), TArray<TVec3<int32>>* OutElements = nullptr);` (scope `ChaosTest`)
- L65 _prototype_ `FGeometryParticleHandle* AppendStaticParticleBox(FPBDRigidsSOAs& SOAs, const FVec3& Scale = FVec3(1), TArray<TVec3<int32>>* OutElements = nullptr);` (scope `ChaosTest`)
- L67 _prototype_ `FPBDRigidParticleHandle* AppendClusteredParticleBox(FPBDRigidsSOAs& SOAs, const FVec3& Scale = FVec3(1), TArray<TVec3<int32>>* OutElements = nullptr);` (scope `ChaosTest`)
- L70 _prototype_ `int32 AppendStaticAnalyticFloor(FPBDRigidParticles& InParticles);` (scope `ChaosTest`) — /
- L72 _prototype_ `FKinematicGeometryParticleHandle* AppendStaticAnalyticFloor(FPBDRigidsSOAs& SOAs);` (scope `ChaosTest`)
- L74 _prototype_ `FKinematicGeometryParticleHandle* AppendStaticConvexFloor(FPBDRigidsSOAs& SOAs);` (scope `ChaosTest`)
- L77 _prototype_ `FLevelSet ConstructLevelset(FParticles& SurfaceParticles, TArray<TVec3<int32>> & Elements);` (scope `ChaosTest`) — /
- L80 _prototype_ `void AppendDynamicParticleConvexBox(FPBDRigidParticleHandle& InParticles, const FVec3& Scale, FReal Margin);` (scope `ChaosTest`) — /
- L82 _prototype_ `FPBDRigidParticleHandle* AppendDynamicParticleConvexBox(FPBDRigidsSOAs& SOAs, const FVec3& Scale = FVec3(1));` (scope `ChaosTest`)
- L84 _prototype_ `FPBDRigidParticleHandle* AppendDynamicParticleConvexBoxMargin(FPBDRigidsSOAs& SOAs, const FVec3& Scale, FReal Margin);` (scope `ChaosTest`)
- L87 _prototype_ `FVec3 ObjectSpacePoint(FPBDRigidParticles& InParticles, const int32 Index, const FVec3& WorldSpacePoint);` (scope `ChaosTest`) — /
- L90 _prototype_ `FReal PhiWithNormal(FPBDRigidParticles& InParticles, const int32 Index, const FVec3& WorldSpacePoint, FVec3& Normal);` (scope `ChaosTest`) — /
- L93 _prototype_ `FReal SignedDistance(FPBDRigidParticles& InParticles, const int32 Index, const FVec3& WorldSpacePoint);` (scope `ChaosTest`) — /
- L96 _prototype_ `FVec3 ObjectSpacePoint(FGeometryParticleHandle& Particle, const FVec3& WorldSpacePoint);` (scope `ChaosTest`) — /
- L99 _prototype_ `FReal PhiWithNormal(FGeometryParticleHandle& Particle, const FVec3& WorldSpacePoint, FVec3& Normal);` (scope `ChaosTest`) — /
- L102 _prototype_ `FReal SignedDistance(FGeometryParticleHandle& Particle, const FVec3& WorldSpacePoint);` (scope `ChaosTest`) — /
- L108 _prototype_ `FVec3 RandAxis();` (scope `ChaosTest`) — Return a random normalized axis. @note: not spherically distributed - actually calculates a point on a box and normalizes.
- L112 _function_ `inline FVec3 RandomVector(FReal MinValue, FReal MaxValue)` (scope `ChaosTest`) — /
- L122 _function_ `inline FMatrix33 RandomMatrix(FReal MinValue, FReal MaxValue)` (scope `ChaosTest`) — /
- L131 _function_ `inline FRotation3 RandomRotation(FReal XMax, FReal YMax, FReal ZMax)` (scope `ChaosTest`) — /
- L140 _prototype_ `void SetParticleSimDataToCollide(TArray< Chaos::FGeometryParticle* > ParticleArray);` (scope `ChaosTest`) — /
- L141 _prototype_ `void SetParticleSimDataToCollide(TArray< Chaos::FGeometryParticleHandle* > ParticleArray);` (scope `ChaosTest`)
- L148 _function_ `template<typename T_Evolution> void InitEvolutionSettings(T_Evolution& Evolution)` (scope `ChaosTest`) — Set settings on Evolution to those used by the tests
- L160 _function_ `template<typename T_SOLVER> void InitSolverSettings(T_SOLVER& Solver)` (scope `ChaosTest`)
- L167 _function_ `template <typename TParticle> void SetCubeInertiaTensor(TParticle& Particle, float Dimension, float Mass)` (scope `ChaosTest`)
- L176 _function_ `template <typename TParticle> void SetBoxInertiaTensor(TParticle& Particle, const FVec3& Dimensions, float Mass)` (scope `ChaosTest`)
- L189 _function_ `template <typename TParticle> void SetSphereInertiaTensor(TParticle& Particle, float Radius, float Mass)` (scope `ChaosTest`)
- L197 _prototype_ `extern FImplicitConvex3 CreateConvexBox(const FConvex::FVec3Type& BoxSize, const FReal Margin);` (scope `ChaosTest`)
- L198 _prototype_ `extern FImplicitConvex3 CreateConvexBox(const FConvex::FVec3Type& BoxMin, const FConvex::FVec3Type& BoxMax, const FReal Margin);` (scope `ChaosTest`)
- L199 _prototype_ `extern TImplicitObjectInstanced<FImplicitConvex3> CreateInstancedConvexBox(const FConvex::FVec3Type& BoxSize, const FReal Margin);` (scope `ChaosTest`)
- L200 _prototype_ `extern TImplicitObjectScaled<FImplicitConvex3> CreateScaledConvexBox(const FConvex::FVec3Type& BoxSize, const FVec3 BoxScale, const FReal Margin);` (scope `ChaosTest`)

### `Source/Programs/HeadlessChaos/Resource/BoxGeometry.h` (Other)


#### class `GeometryCollectionTest::BoxGeometry`  
`class BoxGeometry`  
_L9-18_
- L13 _public function_ `BoxGeometry()`
- L14 _public function_ `~BoxGeometry()`
- L16 _public member_ `static const TArray<float> RawVertexArray;`
- L17 _public member_ `static const TArray<int32> RawIndicesArray;`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace GeometryCollectionTest`

### `Source/Programs/HeadlessChaos/Resource/CubeGeometry.h` (Other)


#### class `GeometryCollectionTest::CubeGeometry`  
`class CubeGeometry`  
_L9-18_
- L13 _public function_ `CubeGeometry()`
- L14 _public function_ `~CubeGeometry()`
- L16 _public member_ `static const TArray<float> RawVertexArray;`
- L17 _public member_ `static const TArray<int32> RawIndicesArray;`
- L21 _member_ `const TArray<float> CubeGeometry::RawVertexArray = { 50.000000, -50.000000, 50.000000, 25.000000, -50.000000, 50.000000, 0.000000, -50.000000, 50.000000, -25.000000, -50.000000, 50.000000, -50.000000, -50.000000, 50.000000, 50.000000, -25.000000, 50.000000, 25.000000, -25.000000, 50.000000, 0.000000, -25.000000, 50.000000, -25.000000, -25.000000, 50.000000, -50.000000, -25.000000, 50.000000, 50.000000, 0.000000, 50.000000, 25.000000, 0.000000, 50.000000, 0.000000, 0.000000, 50.000000, -25.000000, 0.000000, 50.000000, -50.000000, 0.000000, 50.000000, 50.000000, 25.000000, 50.000000, 25.000000, 25.000000, 50.000000, 0.000000, 25.000000, 50.000000, -25.000000, 25.000000, 50.000000, -50.000000, 25.000000, 50.000000, 50.000000, 50.000000, 50.000000, 25.000000, 50.000000, 50.000000, 0.000000, 50.000000, 50.000000, -25.000000, 50.000000, 50.000000, -50.000000, 50.000000, 50.000000, -50.000000, -50.000000, -50.000000, -25.000000, -50.000000, -50.000000, 0.000000, -50.000000, -50.000000, 25.000000, -50.000000, -50.000000, 50.000000, -50.000000, -50.000000, -50.000000, -25.000000, -50.000000, -25.000000, -25.000000, -50.000000, 0.000000, -25.000000, -50.000000, 25.000000, -25.000000, -50.000000, 50.000000, -25.000000, -50.000000, -50.000000, 0.000000, -50.000000, -25.000000, 0.000000, -50.000000, 0.000000, 0.000000, -50.000000, 25.000000, 0.000000, -50.000000,`
- L122 _member_ `const TArray<int32> CubeGeometry::RawIndicesArray = { 0, 1, 6, 1, 2, 7, 2, 3, 8, 3, 4, 9, 5, 6, 11, 6, 7, 12, 7, 8, 13, 8, 9, 14, 10, 11, 16, 11, 12, 17, 12, 13, 18, 13, 14, 19, 15, 16, 21, 16, 17, 22, 17, 18, 23, 18, 19, 24, 25, 26, 31, 26, 27, 32, 27, 28, 33, 28, 29, 34, 30, 31, 36, 31, 32, 37, 32, 33, 38, 33, 34, 39, 35, 36, 41, 36, 37, 42, 37, 38, 43, 38, 39, 44, 40, 41, 46, 41, 42, 47, 42, 43, 48, 43, 44, 49, 45, 46, 51, 46, 47, 52, 47, 48, 53, 48, 49, 54, 50, 51, 56, 51, 52, 57, 52, 53, 58,`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace GeometryCollectionTest`

### `Source/Programs/HeadlessChaos/Resource/Cylinder.h` (Other)


#### class `GeometryCollectionTest::CylinderGeometry`  
`class CylinderGeometry`  
_L8-17_
- L12 _public prototype_ `CylinderGeometry();`
- L13 _public function_ `~CylinderGeometry()`
- L15 _public member_ `static const TArray<float> RawVertexArray;`
- L16 _public member_ `static const TArray<int32> RawIndicesArray;`
- L19 _member_ `const TArray<float> CylinderGeometry::RawVertexArray = { 100.000000, 0.000000, 100.000000, 95.105652, 30.901701, 100.000000, 80.901703, 58.778526, 100.000000, 58.778526, 80.901703, 100.000000, 30.901697, 95.105652, 100.000000, -0.000004, 100.000000, 100.000000, -30.901703, 95.105652, 100.000000, -58.778519, 80.901703, 100.000000, -80.901703, 58.778519, 100.000000, -95.105659, 30.901680, 100.000000, -100.000000, -0.000009, 100.000000, -95.105652, -30.901697, 100.000000, -80.901695, -58.778538, 100.000000, -58.778507, -80.901711, 100.000000, -30.901709, -95.105652, 100.000000, 0.000001, -100.000000, 100.000000, 30.901712, -95.105652, 100.000000, 58.778549, -80.901680, 100.000000, 80.901726, -58.778496, 100.000000, 95.105652, -30.901695, 100.000000, 100.000000, 0.000000, 60.000004, 95.105652, 30.901701, 60.000004, 80.901703, 58.778526, 60.000004, 58.778526, 80.901703, 60.000004, 30.901697, 95.105652, 60.000004, -0.000004, 100.000000, 60.000004, -30.901703, 95.105652, 60.000004, -58.778519, 80.901703, 60.000004, -80.901703, 58.778519, 60.000004, -95.105659, 30.901680, 60.000004, -100.000000, -0.000009, 60.000004, -95.105652, -30.901697, 60.000004, -80.901695, -58.778538, 60.000004, -58.778507, -80.901711, 60.000004, -30.901709, -95.105652, 60.000004, 0.000001, -100.000000, 60.000004, 30.901712, -95.105652, 60.000004, 58.778549, -80.901680, 60.000004, 80.901726, -58.778496, 60.000004,`
- L502 _member_ `const TArray<int32> CylinderGeometry::RawIndicesArray = { 10, 9, 8, 109, 110, 111, 0, 1, 21, 1, 2, 22, 2, 3, 23, 3, 4, 24, 4, 5, 25, 5, 6, 26, 6, 7, 27, 7, 8, 28, 8, 9, 29, 9, 10, 30, 10, 11, 31, 11, 12, 32, 12, 13, 33, 13, 14, 34, 14, 15, 35, 15, 16, 36, 16, 17, 37, 17, 18, 38, 18, 19, 39, 19, 0, 20, 20, 21, 41, 21, 22, 42, 22, 23, 43, 23, 24, 44, 24, 25, 45, 25, 26, 46, 26, 27, 47, 27, 28, 48, 28, 29, 49, 29, 30, 50, 30, 31, 51, 31, 32, 52, 32, 33, 53, 33, 34, 54, 34, 35, 55, 35, 36, 56, 36, 37, 57,`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace GeometryCollectionTest`

### `Source/Programs/HeadlessChaos/Resource/CylinderGeometry.h` (Other)


#### class `GeometryCollectionTest::CylinderGeometry`  
`class CylinderGeometry`  
_L8-17_
- L12 _public function_ `CylinderGeometry()`
- L13 _public function_ `~CylinderGeometry()`
- L15 _public member_ `static const TArray<float> RawVertexArray;`
- L16 _public member_ `static const TArray<int32> RawIndicesArray;`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace GeometryCollectionTest`

### `Source/Programs/HeadlessChaos/Resource/EllipsoidGeometry.h` (Other)


#### class `GeometryCollectionTest::EllipsoidGeometry`  
`class EllipsoidGeometry`  
_L8-17_
- L12 _public function_ `EllipsoidGeometry()`
- L13 _public function_ `~EllipsoidGeometry()`
- L15 _public member_ `static const TArray<float> RawVertexArray;`
- L16 _public member_ `static const TArray<int32> RawIndicesArray;`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace GeometryCollectionTest`

### `Source/Programs/HeadlessChaos/Resource/EllipsoidGeometry2.h` (Other)


#### class `GeometryCollectionTest::EllipsoidGeometry2`  
`class EllipsoidGeometry2`  
_L8-17_
- L12 _public function_ `EllipsoidGeometry2()`
- L13 _public function_ `~EllipsoidGeometry2()`
- L15 _public member_ `static const TArray<float> RawVertexArray;`
- L16 _public member_ `static const TArray<int32> RawIndicesArray;`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace GeometryCollectionTest`

### `Source/Programs/HeadlessChaos/Resource/EllipsoidGeometry3.h` (Other)


#### class `GeometryCollectionTest::EllipsoidGeometry3`  
`class EllipsoidGeometry3`  
_L8-17_
- L12 _public function_ `EllipsoidGeometry3()`
- L13 _public function_ `~EllipsoidGeometry3()`
- L15 _public member_ `static const TArray<float> RawVertexArray;`
- L16 _public member_ `static const TArray<int32> RawIndicesArray;`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace GeometryCollectionTest`

### `Source/Programs/HeadlessChaos/Resource/FracturedGeometry.h` (Other)


#### class `GeometryCollectionTest::FracturedGeometry`  
`class FracturedGeometry`  
_L11-26_
- L14 _public prototype_ `FracturedGeometry();`
- L15 _public prototype_ `~FracturedGeometry();`
- L17 _public member_ `static const TArray<float> RawVertexArray;`
- L18 _public member_ `static const TArray<int32> RawIndicesArray;`
- L19 _public member_ `static const TArray<int32> RawBoneMapArray;`
- L20 _public member_ `static const TArray<FTransform> RawTransformArray;`
- L21 _public member_ `static const TArray<int32> RawLevelArray;`
- L22 _public member_ `static const TArray<int32> RawParentArray;`
- L23 _public member_ `static const TArray<TSet<int32>> RawChildrenArray;`
- L24 _public member_ `static const TArray<int32> RawSimulationTypeArray;`
- L25 _public member_ `static const TArray<int32> RawStatusFlagsArray;`

#### class `GeometryCollectionTest::GlobalFracturedGeometry`  
`class GlobalFracturedGeometry`  
_L31-50_
- desc: A version of \c FracturedGeometry in a global point pool.
- L34 _public prototype_ `GlobalFracturedGeometry();`
- L35 _public prototype_ `~GlobalFracturedGeometry();`
- L37 _public member_ `TArray<float> RawVertexArray;`
- L38 _public member_ `TArray<int32> RawIndicesArray0;` — Randomly coincident to RawIndicesArray1
- L39 _public member_ `TArray<int32> RawIndicesArray1;` — Unchanged from FracturedGeometry
- L40 _public member_ `TArray<int32> RawIndicesArray2;` — Offset in Y
- L41 _public member_ `const TArray<int32> & RawIndicesArray;` — Points to RawIndicesArray1
- L42 _public member_ `TArray<int32> RawIndicesArrayMerged;` — RawIndicesArray 0, 1, and 2 concatenated
- L43 _public member_ `const TArray<int32> RawBoneMapArray;`
- L44 _public member_ `const TArray<FTransform> RawTransformArray;`
- L45 _public member_ `const TArray<int32> RawLevelArray;`
- L46 _public member_ `const TArray<int32> RawParentArray;`
- L47 _public member_ `const TArray<TSet<int32>> RawChildrenArray;`
- L48 _public member_ `const TArray<int32> RawSimulationTypeArray;`
- L49 _public member_ `const TArray<int32> RawStatusFlagsArray;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace GeometryCollectionTest`

### `Source/Programs/HeadlessChaos/Resource/SphereGeometry.h` (Other)


#### class `GeometryCollectionTest::SphereGeometry`  
`class SphereGeometry`  
_L10-19_
- L14 _public function_ `SphereGeometry()`
- L15 _public function_ `~SphereGeometry()`
- L17 _public member_ `static const TArray<float> RawVertexArray;`
- L18 _public member_ `static const TArray<int32> RawIndicesArray;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace GeometryCollectionTest`

### `Source/Programs/HeadlessChaos/Resource/TestGeometry1.h` (Other)


#### class `TestGeometry1`  
`class TestGeometry1`  
_L6-15_
- L10 _public prototype_ `TestGeometry1();`
- L11 _public function_ `~TestGeometry1()`
- L13 _public member_ `static const TArray<float> RawVertexArray;`
- L14 _public member_ `static const TArray<int32> RawIndicesArray;`
- L18 _member_ `const TArray<float> TestGeometry1::RawVertexArray = { -0.118278, 2.164261, 0.478031, 0.718749, 2.083855, 0.478031, 1.996569, -3.569340, 108.680893, -1.337000, -1.467590, 0.478031, -0.769773, -3.303612, 108.680908, -3.126952, 3.547722, 108.321014, 1.344566, -1.725174, 0.478031, 5.406225, 2.745453, 108.614349, -0.016398, 1.967595, -0.166328, 1.364451, 0.926640, -0.166328, 0.248418, -2.341320, -0.166325, -1.132432, -1.300364, -0.166325, -0.505581, -3.006680, 109.182297, 4.463128, -1.863823, 109.187286, 2.423427, 4.341752, 108.944153, -2.562841, 3.195637, 108.834076, -0.798691, -2.429302, 19.550392, -1.710983, -2.839973, 34.633438, -2.137956, -2.842075, 48.920158, -1.520910, 3.391621, 89.422653, -1.023157, 2.832703, 75.749176, 0.466790, 2.115548, 19.550064, -0.284844, 1.749657, 34.631626, -0.030453, 1.842498, 48.914162, 0.571760, -3.149826, 89.479492, 0.860690, -2.889763, 75.783325, -1.463210, -2.974493, 62.579678, -2.737792, -1.023791, 75.785049, -4.645150, -1.379299, 89.484047, -1.098912, 2.182862, 62.565571, -3.242825, 1.197943, 48.917366, -2.573089, 1.047616, 34.632591, -1.490659, 1.393471, 19.550217, 0.762244, 1.981854, 62.565571, 1.200588, 2.592537, 75.749161, 1.076512, 3.226872, 89.420547, 0.412727, -3.177101, 62.579678, -0.407297, -3.008318, 48.920177, -0.653349, -2.941570, 34.633438,`
- L193 _member_ `const TArray<int> TestGeometry1::RawIndicesArray = { 69, 66, 58, 76, 73, 63, 33, 29, 70, 25, 36, 26, 40, 3, 11, 1, 0, 8, 6, 41, 9, 43, 46, 10, 44, 5, 15, 2, 4, 12, 7, 42, 13, 45, 47, 14, 13, 53, 14, 9, 49, 8, 59, 5, 44, 59, 28, 27, 69, 60, 27, 56, 3, 40, 56, 32, 31, 58, 57, 31, 64, 42, 7, 64, 75, 74, 76, 65, 74, 61, 41, 6, 61, 39, 78, 63, 62, 78, 35, 47, 45, 35, 19, 20, 33, 34, 20, 72, 0, 1, 72, 21, 22, 70, 71, 22, 79, 46, 43, 79, 16, 17, 37, 38, 17, 37, 18, 26, 68, 4, 2, 25, 67, 68, 43, 3, 56,`

### `Source/Programs/HeadlessChaos/Resource/TestGeometry2.h` (Other)


#### class `TestGeometry2`  
`class TestGeometry2`  
_L6-15_
- L10 _public prototype_ `TestGeometry2();`
- L11 _public function_ `~TestGeometry2()`
- L13 _public member_ `static const TArray<float> RawVertexArray;`
- L14 _public member_ `static const TArray<int32> RawIndicesArray;`
- L17 _member_ `const TArray<float> TestGeometry2::RawVertexArray = { 0.073882f, -51.063614f, 187.396667f, 0.392873f, -53.486588f, 188.051514f, 0.711864f, -55.909561f, 187.396667f, 0.945381f, -57.362549f, 185.607635f, 1.030854f, -58.133938f, 183.163742f, 1.064601f, -57.683296f, 180.728546f, 1.018947f, -56.211304f, 178.615570f, 0.637275f, -53.486588f, 177.973206f, 12.971017f, -49.190517f, 187.198456f, 12.971020f, -51.634399f, 187.853302f, 13.220634f, -54.079868f, 186.952927f, 13.436441f, -55.546570f, 185.409424f, 13.576239f, -56.522156f, 182.965530f, 13.576239f, -55.867321f, 180.521652f, 13.576239f, -54.214188f, 178.850143f, 13.576238f, -51.468567f, 178.571091f, -27.638752f, -52.471001f, 192.457352f, -27.275444f, -54.826904f, 193.346420f, -14.439268f, -54.438148f, 191.295074f, -14.467831f, -51.654587f, 190.133972f, -27.021297f, -57.306438f, 192.816345f, -14.467831f, -56.882027f, 190.640869f, -26.944401f, -59.245201f, 191.009171f, -14.545873f, -58.671074f, 188.853531f, -27.065357f, -60.123711f, 188.409088f, -14.652473f, -59.325909f, 186.411957f, -27.351749f, -59.706573f, 185.712845f, -14.759071f, -58.671078f, 183.970413f, -27.726856f, -58.105556f, 183.642853f, -14.837107f, -57.383820f, 182.566650f, -28.090158f, -55.749653f, 182.753769f, -14.865672f, -54.521561f, 182.375427f, -18.654972f, -54.180893f, 192.974304f, -18.843723f, -50.877609f, 191.736115f, -18.563026f, -57.326668f, 192.192963f, -18.592527f, -59.685738f, 189.895126f, -18.735569f, -60.625984f, 186.696472f, -18.953808f, -59.895481f, 1 ...`
- L916 _member_ `const TArray<int> TestGeometry2::RawIndicesArray = { 0, 9, 1, 9, 0, 8, 1, 10, 2, 10, 1, 9, 2, 11, 3, 11, 2, 10, 3, 12, 4, 12, 3, 11, 4, 13, 5, 13, 4, 12, 5, 14, 6, 14, 5, 13, 6, 15, 7, 15, 6, 14, 6, 4, 5, 4, 2, 3, 2, 0, 1, 4, 0, 2, 6, 0, 4, 7, 0, 6, 9, 11, 10, 11, 13, 12, 13, 15, 14, 11, 15, 13, 9, 15, 11, 8, 15, 9, 17, 33, 32, 33, 17, 16, 20, 32, 34, 32, 20, 17, 22, 34, 35, 34, 22, 20, 24, 35, 36, 35, 24, 22, 26, 36, 37, 36, 26, 24, 28, 37, 38, 37, 28, 26, 30, 38, 39,`

### `Source/Programs/HeadlessChaos/Resource/TorusGeometry.h` (Other)


#### class `TorusGeometry`  
`class TorusGeometry`  
_L7-16_
- L11 _public function_ `TorusGeometry()`
- L12 _public function_ `~TorusGeometry()`
- L14 _public member_ `static const TArray<float> RawVertexArray;`
- L15 _public member_ `static const TArray<int32> RawIndicesArray;`
