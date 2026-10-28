# Runtime / PhysicsCore

- module root: `Source/Runtime/PhysicsCore`
- headers: 42; symbols: 1208
- symbol kinds: class=29, delegate=2, enum=24, enumerator=158, externvar=3, function=234, macro=12, member=228, namespace=36, prototype=400, struct=33, typedef=47, union=1, variable=1
- PrivateDependencyModuleNames: Core, CoreUObject
- PublicDependencyModuleNames: DeveloperSettings

### `Source/Runtime/PhysicsCore/Private/SceneQueryChaosImp.h` (Private)


#### Free symbols / members of external scopes

- L10 _function_ `inline bool LowLevelRaycastImp(const FVector& Start, const FVector& Dir, float DeltaMag, const Chaos::FImplicitObject& Shape, const FTransform ActorTM, EHitFlags OutputFlags, FHitRaycast& Hit)`
- L16 _function_ `inline bool LowLevelSweepImp(const FTransform& StartTM, const FVector& Dir, float DeltaMag, const FPhysicsGeometry& SweepGeom, const Chaos::FImplicitObject& Shape, const FTransform ActorTM, EHitFlags OutputFlags, FHitSweep& Hit)`
- L22 _function_ `inline bool LowLevelOverlapImp(const FTransform& GeomPose, const FPhysicsGeometry& OverlapGeom, const Chaos::FImplicitObject& Shape, const FTransform ActorTM, FHitOverlap& Overlap)`

### `Source/Runtime/PhysicsCore/Private/SceneQueryPhysXImp.h` (Private)
_(no declarations extracted)_

### `Source/Runtime/PhysicsCore/Public/BodyInstanceCore.h` (Public)


#### struct `FBodyInstanceCore`  
`struct FBodyInstanceCore`  
_L15-70_
- reflection: `USTRUCT(BlueprintType)`
- L20 _public member_ `TWeakObjectPtr<UBodySetupCore> BodySetup;` — BodySetupCore pointer that this instance is initialized from
- L22 _public prototype_ `FBodyInstanceCore();`
- L30 _public member_ `uint8 bSimulatePhysics : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Physics)` — If true, this body will use simulation. If false, will be 'fixed' (ie kinematic) and move where it is told. For a Skeletal Mesh Component, simulating requires a physics asset setup and assigned on the SkeletalMesh asset. For a Static Mesh Component, simulating requires simple collision to be setup on the StaticMesh asset.
- L35 _public member_ `uint8 bOverrideMass : 1;` — `UPROPERTY(EditAnywhere,Category = Physics,meta = (InlineEditConditionToggle))` — If true, mass will not be automatically computed and you must set it directly
- L39 _public member_ `uint8 bEnableGravity : 1;` — `UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = Physics)` — If object should have the force of gravity applied
- L43 _public member_ `uint8 bUpdateKinematicFromSimulation : 1;` — `UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = Physics)` — When kinematic, whether the actor transform should be updated as a result of movement in the simulation, rather than immediately whenever a target transform is set.
- L47 _public member_ `uint8 bGyroscopicTorqueEnabled : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Physics)` — Enabled/disables whether this body is affected by gyroscopic torque, mainly useful for long/thin objects that spin
- L51 _public member_ `uint8 bAutoWeld : 1;` — `UPROPERTY(EditAnywhere,AdvancedDisplay,BlueprintReadWrite,Category = Physics,meta = (editcondition = "!bSimulatePhysics"))` — If true and is attached to a parent, the two bodies will be joined into a single rigid body. Physical settings like collision profile and body settings are determined by the root
- L55 _public member_ `uint8 bStartAwake:1;` — `UPROPERTY(EditAnywhere,AdvancedDisplay,BlueprintReadOnly,Category = Physics,meta = (editcondition = "bSimulatePhysics"))` — If object should start awake, or if it should initially be sleeping
- L59 _public member_ `uint8 bGenerateWakeEvents : 1;` — `UPROPERTY(EditAnywhere,AdvancedDisplay,BlueprintReadOnly,Category = Physics)` — Should 'wake/sleep' events fire when this object is woken up or put to sleep by the physics simulation.
- L63 _public member_ `uint8 bUpdateMassWhenScaleChanges:1;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadWrite, Category=Physics)` — If true, it will update mass when scale change
- L66 _public member_ `uint8 bDirtyMassProps : 1;` — Indicates mass props need to be recomputed when switching from kinematic to simulated
- L69 _public prototype_ `bool ShouldInstanceSimulatingPhysics() const;` — Should Simulate Physics

### `Source/Runtime/PhysicsCore/Public/BodySetupCore.h` (Public)


#### class `UBodySetupCore`  
`class UBodySetupCore : public UObject`  
_L18-42_
- reflection: `UCLASS(collapseCategories, MinimalAPI)`
- inherits: `UObject`
- L23 _public prototype_ `TEnumAsByte<enum ECollisionTraceFlag> GetCollisionTraceFlag() const;`
- L27 _public member_ `FName BoneName;` — `UPROPERTY(Category=BodySetup,VisibleAnywhere)` — Used in the PhysicsAsset case. Associates this Body with Bone in a skeletal mesh.
- L33 _public member_ `TEnumAsByte<EPhysicsType> PhysicsType;` — `UPROPERTY(EditAnywhere, Category=Physics)` — If simulated it will use physics, if kinematic it will not be affected by physics, but can interact with physically simulated bodies. Default will inherit from OwnerComponent's behavior.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace physx`

### `Source/Runtime/PhysicsCore/Public/BodySetupEnums.h` (Public)


#### enum `ECollisionTraceFlag`  
`enum ECollisionTraceFlag : int`  
_L10-21_
- reflection: `UENUM(BlueprintType)`
- L13 _public enumerator_ `CTF_UseDefault UMETA(DisplayName="Project Default")` — Use project physics settings (DefaultShapeComplexity)
- L15 _public enumerator_ `CTF_UseSimpleAndComplex UMETA(DisplayName = "Simple And Complex")` — Create both simple and complex shapes. Simple shapes are used for regular scene queries and collision tests. Complex shape (per poly) is used for complex scene queries.
- L17 _public enumerator_ `CTF_UseSimpleAsComplex UMETA(DisplayName = "Use Simple Collision As Complex")` — Create only simple shapes. Use simple shapes for all scene queries and collision tests.
- L19 _public enumerator_ `CTF_UseComplexAsSimple UMETA(DisplayName = "Use Complex Collision As Simple")` — Create only complex shapes (per poly). Use complex shapes for all scene queries and collision tests. Can be used in simulation for static shapes only (i.e can be collided against but not moved through forces or velocity.)
- L20 _public enumerator_ `CTF_MAX`

#### enum `EPhysicsType`  
`enum EPhysicsType : int`  
_L24-32_
- reflection: `UENUM()`
- L27 _public enumerator_ `PhysType_Default UMETA(DisplayName="Default")` — Follow owner.
- L29 _public enumerator_ `PhysType_Kinematic UMETA(DisplayName="Kinematic")` — Do not follow owner, but make kinematic.
- L31 _public enumerator_ `PhysType_Simulated UMETA(DisplayName="Simulated")` — Do not follow owner, but simulate.

#### enum `EBodyCollisionResponse::Type`  
`enum Type : int`  
_L37-42_
- L39 _public enumerator_ `BodyCollision_Enabled UMETA(DisplayName="Enabled")`
- L40 _public enumerator_ `BodyCollision_Disabled UMETA(DisplayName="Disabled")` — ,

#### Free symbols / members of external scopes

- L35 _namespace_ `namespace EBodyCollisionResponse`
- L47 _prototype_ `const TCHAR* LexToString(ECollisionTraceFlag Enum);` — Helpers to convert enum to string
- L48 _prototype_ `const TCHAR* LexToString(EPhysicsType Enum);`
- L49 _prototype_ `const TCHAR* LexToString(EBodyCollisionResponse::Type Enum);`

### `Source/Runtime/PhysicsCore/Public/Chaos/ChaosConstraintSettings.h` (Public)


#### class `Chaos::ConstraintSettings`  
`class ConstraintSettings`  
_L15-36_
- desc: Constraint settings all for generic defaults and scalars to the constraint parameters so that converting between existing (pre v4.26) simulation parameters and Chaos can produce similar simulation results.
- L17 _private function_ `ConstraintSettings()`
- L20 _public prototype_ `static FReal JointStiffness();`
- L21 _public prototype_ `static FReal LinearDriveStiffnessScale();`
- L22 _public prototype_ `static FReal LinearDriveDampingScale();`
- L23 _public prototype_ `static FReal AngularDriveStiffnessScale();`
- L24 _public prototype_ `static FReal AngularDriveDampingScale();`
- L26 _public prototype_ `static int SoftLinearForceMode();`
- L27 _public prototype_ `static FReal SoftLinearStiffnessScale();`
- L28 _public prototype_ `static FReal SoftLinearDampingScale();`
- L30 _public prototype_ `static int SoftAngularForceMode();`
- L31 _public prototype_ `static FReal SoftAngularStiffnessScale();`
- L32 _public prototype_ `static FReal SoftAngularDampingScale();`
- L34 _public prototype_ `static FReal LinearBreakScale();`
- L35 _public prototype_ `static FReal AngularBreakScale();`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Chaos`

### `Source/Runtime/PhysicsCore/Public/Chaos/ChaosEngineInterface.h` (Public)


#### enum `EPhysicalSurface`  
`enum EPhysicalSurface : int`  
_L20-86_
- reflection: `UENUM(BlueprintType)`
- desc: Types of surfaces in the game, used by Physical Materials
- L22 _public enumerator_ `SurfaceType_Default UMETA(DisplayName="Default")`
- L23 _public enumerator_ `SurfaceType1 UMETA(Hidden)`
- L24 _public enumerator_ `SurfaceType2 UMETA(Hidden)`
- L25 _public enumerator_ `SurfaceType3 UMETA(Hidden)`
- L26 _public enumerator_ `SurfaceType4 UMETA(Hidden)`
- L27 _public enumerator_ `SurfaceType5 UMETA(Hidden)`
- L28 _public enumerator_ `SurfaceType6 UMETA(Hidden)`
- L29 _public enumerator_ `SurfaceType7 UMETA(Hidden)`
- L30 _public enumerator_ `SurfaceType8 UMETA(Hidden)`
- L31 _public enumerator_ `SurfaceType9 UMETA(Hidden)`
- L32 _public enumerator_ `SurfaceType10 UMETA(Hidden)`
- L33 _public enumerator_ `SurfaceType11 UMETA(Hidden)`
- L34 _public enumerator_ `SurfaceType12 UMETA(Hidden)`
- L35 _public enumerator_ `SurfaceType13 UMETA(Hidden)`
- L36 _public enumerator_ `SurfaceType14 UMETA(Hidden)`
- L37 _public enumerator_ `SurfaceType15 UMETA(Hidden)`
- L38 _public enumerator_ `SurfaceType16 UMETA(Hidden)`
- L39 _public enumerator_ `SurfaceType17 UMETA(Hidden)`
- L40 _public enumerator_ `SurfaceType18 UMETA(Hidden)`
- L41 _public enumerator_ `SurfaceType19 UMETA(Hidden)`
- L42 _public enumerator_ `SurfaceType20 UMETA(Hidden)`
- L43 _public enumerator_ `SurfaceType21 UMETA(Hidden)`
- L44 _public enumerator_ `SurfaceType22 UMETA(Hidden)`
- L45 _public enumerator_ `SurfaceType23 UMETA(Hidden)`
- L46 _public enumerator_ `SurfaceType24 UMETA(Hidden)`
- L47 _public enumerator_ `SurfaceType25 UMETA(Hidden)`
- L48 _public enumerator_ `SurfaceType26 UMETA(Hidden)`
- L49 _public enumerator_ `SurfaceType27 UMETA(Hidden)`
- L50 _public enumerator_ `SurfaceType28 UMETA(Hidden)`
- L51 _public enumerator_ `SurfaceType29 UMETA(Hidden)`
- L52 _public enumerator_ `SurfaceType30 UMETA(Hidden)`
- L53 _public enumerator_ `SurfaceType31 UMETA(Hidden)`
- L54 _public enumerator_ `SurfaceType32 UMETA(Hidden)`
- L55 _public enumerator_ `SurfaceType33 UMETA(Hidden)`
- L56 _public enumerator_ `SurfaceType34 UMETA(Hidden)`
- L57 _public enumerator_ `SurfaceType35 UMETA(Hidden)`
- L58 _public enumerator_ `SurfaceType36 UMETA(Hidden)`
- L59 _public enumerator_ `SurfaceType37 UMETA(Hidden)`
- L60 _public enumerator_ `SurfaceType38 UMETA(Hidden)`
- L61 _public enumerator_ `SurfaceType39 UMETA(Hidden)`
- L62 _public enumerator_ `SurfaceType40 UMETA(Hidden)`
- L63 _public enumerator_ `SurfaceType41 UMETA(Hidden)`
- L64 _public enumerator_ `SurfaceType42 UMETA(Hidden)`
- L65 _public enumerator_ `SurfaceType43 UMETA(Hidden)`
- L66 _public enumerator_ `SurfaceType44 UMETA(Hidden)`
- L67 _public enumerator_ `SurfaceType45 UMETA(Hidden)`
- L68 _public enumerator_ `SurfaceType46 UMETA(Hidden)`
- L69 _public enumerator_ `SurfaceType47 UMETA(Hidden)`
- L70 _public enumerator_ `SurfaceType48 UMETA(Hidden)`
- L71 _public enumerator_ `SurfaceType49 UMETA(Hidden)`
- L72 _public enumerator_ `SurfaceType50 UMETA(Hidden)`
- L73 _public enumerator_ `SurfaceType51 UMETA(Hidden)`
- L74 _public enumerator_ `SurfaceType52 UMETA(Hidden)`
- L75 _public enumerator_ `SurfaceType53 UMETA(Hidden)`
- L76 _public enumerator_ `SurfaceType54 UMETA(Hidden)`
- L77 _public enumerator_ `SurfaceType55 UMETA(Hidden)`
- L78 _public enumerator_ `SurfaceType56 UMETA(Hidden)`
- L79 _public enumerator_ `SurfaceType57 UMETA(Hidden)`
- L80 _public enumerator_ `SurfaceType58 UMETA(Hidden)`
- L81 _public enumerator_ `SurfaceType59 UMETA(Hidden)`
- L82 _public enumerator_ `SurfaceType60 UMETA(Hidden)`
- L83 _public enumerator_ `SurfaceType61 UMETA(Hidden)`
- L84 _public enumerator_ `SurfaceType62 UMETA(Hidden)`
- L85 _public enumerator_ `SurfaceType_Max UMETA(Hidden)`

#### enum `ERadialImpulseFalloff`  
`enum ERadialImpulseFalloff : int`  
_L90-97_
- reflection: `UENUM()`
- desc: Enum for controlling the falloff of strength of a radial impulse as a function of distance from Origin.
- L93 _public enumerator_ `RIF_Constant` — Impulse is a constant strength, up to the limit of its range.
- L95 _public enumerator_ `RIF_Linear` — Impulse should get linearly weaker the further from origin.
- L96 _public enumerator_ `RIF_MAX`

#### enum `ESleepFamily`  
`enum class ESleepFamily: uint8`  
_L101-109_
- reflection: `UENUM()`
- desc: Presets of values used in considering when put this body to sleep.
- L104 _public enumerator_ `Normal` — Engine defaults.
- L106 _public enumerator_ `Sensitive` — A family of values with a lower sleep threshold; good for slower pendulum-like physics.
- L108 _public enumerator_ `Custom` — Specify your own sleep threshold multiplier

#### enum `EAngularConstraintMotion`  
`enum EAngularConstraintMotion : int`  
_L113-123_
- reflection: `UENUM()`
- desc: Specifies angular degrees of freedom
- L116 _public enumerator_ `ACM_Free UMETA(DisplayName="Free")` — No constraint against this axis.
- L118 _public enumerator_ `ACM_Limited UMETA(DisplayName="Limited")` — Limited freedom along this axis.
- L120 _public enumerator_ `ACM_Locked UMETA(DisplayName="Locked")` — Fully constraint against this axis.
- L122 _public enumerator_ `ACM_MAX`

#### enum `EConstraintFrame::Type`  
`enum Type : int`  
_L129-133_
- L131 _public enumerator_ `Frame1`
- L132 _public enumerator_ `Frame2`

#### enum `PhysicsInterfaceTypes::ELimitAxis`  
`enum class ELimitAxis : uint8`  
_L139-147_
- L141 _public enumerator_ `X`
- L142 _public enumerator_ `Y`
- L143 _public enumerator_ `Z`
- L144 _public enumerator_ `Twist`
- L145 _public enumerator_ `Swing1`
- L146 _public enumerator_ `Swing2`

#### enum `PhysicsInterfaceTypes::EDriveType`  
`enum class EDriveType : uint8`  
_L149-157_
- L151 _public enumerator_ `X`
- L152 _public enumerator_ `Y`
- L153 _public enumerator_ `Z`
- L154 _public enumerator_ `Swing`
- L155 _public enumerator_ `Twist`
- L156 _public enumerator_ `Slerp`

#### enum `PhysicsInterfaceTypes::(anonymous)`  
`enum`  
_L163-163_
- desc: Default number of inlined elements used in FInlineShapeArray. Increase if for instance character meshes use more than this number of physics bodies and are involved in many queries.

#### enum `EConstraintPlasticityType`  
`enum EConstraintPlasticityType : int`  
_L172-182_
- reflection: `UENUM()`
- desc: LINEAR CCPT
- L175 _public enumerator_ `CCPT_Free UMETA(DisplayName = "Free")`
- L177 _public enumerator_ `CCPT_Shrink UMETA(DisplayName = "Shrink")`
- L179 _public enumerator_ `CCPT_Grow UMETA(DisplayName = "Grow")`
- L181 _public enumerator_ `CCPT_MAX`

#### enum `ELinearConstraintMotion`  
`enum ELinearConstraintMotion : int`  
_L186-196_
- reflection: `UENUM()`
- desc: LINEAR DOF
- L189 _public enumerator_ `LCM_Free UMETA(DisplayName="Free")` — No constraint against this axis.
- L191 _public enumerator_ `LCM_Limited UMETA(DisplayName="Limited")` — Limited freedom along this axis.
- L193 _public enumerator_ `LCM_Locked UMETA(DisplayName="Locked")` — Fully constraint against this axis.
- L195 _public enumerator_ `LCM_MAX`

#### class `FPhysicsAggregateReference_Chaos`  
`class FPhysicsAggregateReference_Chaos`  
_L240-244_
- L243 _public function_ `bool IsValid() const`

#### class `FPhysicsConstraintReference_Chaos`  
`class FPhysicsConstraintReference_Chaos`  
_L246-260_
- L249 _public function_ `FPhysicsConstraintReference_Chaos()`
- L250 _public function_ `void Reset()`
- L252 _public prototype_ `bool IsValid() const;`
- L256 _public function_ `Chaos::FConstraintBase* operator->()`
- L257 _public function_ `const Chaos::FConstraintBase* operator->() const`
- L259 _public member_ `Chaos::FConstraintBase* Constraint;`

#### class `FPhysicsShapeReference_Chaos`  
`class FPhysicsShapeReference_Chaos`  
_L262-283_
- L266 _public function_ `FPhysicsShapeReference_Chaos() : Shape(nullptr), ActorRef()`
- L268 _public function_ `FPhysicsShapeReference_Chaos(Chaos::FPerShapeData* ShapeIn, const FPhysicsActorHandle& ActorRefIn) : Shape(ShapeIn), ActorRef(ActorRefIn)`
- L271 _public function_ `bool IsValid() const`
- L272 _public function_ `bool Equals(const FPhysicsShapeReference_Chaos& Other) const`
- L273 _public function_ `bool operator==(const FPhysicsShapeReference_Chaos& Other) const`
- L274 _public prototype_ `const Chaos::FImplicitObject& GetGeometry() const;`
- L276 _public member_ `Chaos::FPerShapeData* Shape;`
- L277 _public member_ `FPhysicsActorHandle ActorRef;`

#### class `FPhysicsShapeAdapter_Chaos`  
`class FPhysicsShapeAdapter_Chaos`  
_L285-298_
- L288 _public prototype_ `FPhysicsShapeAdapter_Chaos(const FQuat& Rot, const FCollisionShape& CollisionShape);`
- L289 _public prototype_ `~FPhysicsShapeAdapter_Chaos();`
- L291 _public prototype_ `const FPhysicsGeometry& GetGeometry() const;`
- L292 _public prototype_ `FTransform GetGeomPose(const FVector& Pos) const;`
- L293 _public prototype_ `const FQuat& GetGeomOrientation() const;`
- L296 _private member_ `TRefCountPtr<FPhysicsGeometry> Geometry;`
- L297 _private member_ `FQuat GeometryRotation;`

#### struct `FPhysicsGeometryCollection_Chaos`  
`struct FPhysicsGeometryCollection_Chaos`  
_L303-329_
- desc: Wrapper around geometry. This is really just needed to make the physx chaos abstraction easier
- L306 _public prototype_ `FPhysicsGeometryCollection_Chaos() = delete;` — Delete default constructor, want only construction by interface (private constructor below)
- L309 _public prototype_ `FPhysicsGeometryCollection_Chaos(const FPhysicsGeometryCollection_Chaos& Copy) = delete;` — No copying or assignment, move construction only, these are defaulted in the source file as they need to be able to delete physx::PxGeometryHolder which is incomplete here
- L310 _public prototype_ `FPhysicsGeometryCollection_Chaos& operator=(const FPhysicsGeometryCollection_Chaos& Copy) = delete;`
- L311 _public prototype_ `FPhysicsGeometryCollection_Chaos(FPhysicsGeometryCollection_Chaos&& Steal);`
- L312 _public prototype_ `FPhysicsGeometryCollection_Chaos& operator=(FPhysicsGeometryCollection_Chaos&& Steal) = delete;`
- L313 _public prototype_ `~FPhysicsGeometryCollection_Chaos();`
- L315 _public prototype_ `ECollisionShapeType GetType() const;`
- L316 _public prototype_ `const Chaos::FImplicitObject& GetGeometry() const;`
- L317 _public prototype_ `const Chaos::TBox<Chaos::FReal, 3>& GetBoxGeometry() const;`
- L318 _public prototype_ `const Chaos::FSphere& GetSphereGeometry() const;`
- L319 _public prototype_ `const Chaos::FCapsule& GetCapsuleGeometry() const;`
- L320 _public prototype_ `const Chaos::FConvex& GetConvexGeometry() const;`
- L321 _public prototype_ `const Chaos::FTriangleMeshImplicitObject& GetTriMeshGeometry() const;`
- L325 _private prototype_ `explicit FPhysicsGeometryCollection_Chaos(const FPhysicsShapeReference_Chaos& InShape);`
- L326 _private prototype_ `explicit FPhysicsGeometryCollection_Chaos(const FPhysicsGeometry& InGeom);`
- L328 _private member_ `const Chaos::FImplicitObject& Geom;`

#### class `FChaosEngineInterface`  
`class FChaosEngineInterface`  
_L346-593_
- L349 _public prototype_ `virtual ~FChaosEngineInterface() = default;`
- L351 _public prototype_ `static void CreateActor(const FActorCreationParams& InParams,FPhysicsActorHandle& Handle, UObject* InOwner = nullptr);`
- L352 _public prototype_ `static void ReleaseActor(FPhysicsActorHandle& InActorReference,FChaosScene* InScene = nullptr,bool bNeverDeferRelease=false);`
- L354 _public function_ `static bool IsValid(const FPhysicsActorHandle& Handle)`
- L355 _public prototype_ `static void AddActorToSolver(const FPhysicsActorHandle& Handle,Chaos::FPhysicsSolver* Solver);`
- L356 _public prototype_ `static void RemoveActorFromSolver(const FPhysicsActorHandle& Handle,Chaos::FPhysicsSolver* Solver);`
- L358 _public prototype_ `static void SetGlobalPose_AssumesLocked(const FPhysicsActorHandle& InActorReference,const FTransform& InNewPose,bool bAutoWake = true);`
- L359 _public prototype_ `static void SetKinematicTarget_AssumesLocked(const FPhysicsActorHandle& InActorReference,const FTransform& InNewTarget);`
- L361 _public prototype_ `static FChaosScene* GetCurrentScene(const FPhysicsActorHandle& InHandle);`
- L363 _public prototype_ `static FPhysicsMaterialHandle CreateMaterial(const UPhysicalMaterial* InMaterial);`
- L364 _public prototype_ `static void UpdateMaterial(FPhysicsMaterialHandle& InHandle, UPhysicalMaterial* InMaterial);`
- L365 _public prototype_ `static void ReleaseMaterial(FPhysicsMaterialHandle& InHandle);`
- L366 _public prototype_ `static void SetUserData(FPhysicsMaterialHandle& InHandle,void* InUserData);`
- L368 _public prototype_ `static void ReleaseMaterialMask(FPhysicsMaterialMaskHandle& InHandle);`
- L370 _public prototype_ `static FPhysicsAggregateReference_Chaos CreateAggregate(int32 MaxBodies);`
- L371 _public prototype_ `static void ReleaseAggregate(FPhysicsAggregateReference_Chaos& InAggregate);`
- L372 _public prototype_ `static int32 GetNumActorsInAggregate(const FPhysicsAggregateReference_Chaos& InAggregate);`
- L373 _public prototype_ `static void AddActorToAggregate_AssumesLocked(const FPhysicsAggregateReference_Chaos& InAggregate,const FPhysicsActorHandle& InActor);`
- L375 _public prototype_ `static int32 GetNumShapes(const FPhysicsActorHandle& InHandle);`
- L377 _public prototype_ `static void ReleaseShape(const FPhysicsShapeHandle& InShape);`
- L379 _public prototype_ `static void AttachShape(const FPhysicsActorHandle& InActor,const FPhysicsShapeHandle& InNewShape);`
- L380 _public prototype_ `static void DetachShape(const FPhysicsActorHandle& InActor,FPhysicsShapeHandle& InShape,bool bWakeTouching = true);`
- L382 _public prototype_ `static void SetSmoothEdgeCollisionsEnabled_AssumesLocked(const FPhysicsActorHandle& InActor, const bool bSmoothEdgeCollisionsEnabled);`
- L384 _public prototype_ `static void AddDisabledCollisionsFor_AssumesLocked(const TMap<FPhysicsActorHandle, TArray< FPhysicsActorHandle > >& InMap);`
- L385 _public prototype_ `static void RemoveDisabledCollisionsFor_AssumesLocked(TArray< FPhysicsActorHandle > & InPhysicsActors);`
- L387 _public prototype_ `static void SetDisabled(const FPhysicsActorHandle& InPhysicsActor, bool bSetDisabled);`
- L388 _public prototype_ `static bool IsDisabled(const FPhysicsActorHandle& InPhysicsActor);`
- L390 _public prototype_ `static void SetActorUserData_AssumesLocked(const FPhysicsActorHandle& InActorReference,FPhysicsUserData* InUserData);`
- L392 _public prototype_ `static bool IsRigidBody(const FPhysicsActorHandle& InActorReference);`
- L393 _public prototype_ `static bool IsDynamic(const FPhysicsActorHandle& InActorReference);`
- L394 _public prototype_ `static bool IsStatic(const FPhysicsActorHandle& InActorReference);`
- L395 _public prototype_ `static bool IsKinematic(const FPhysicsActorHandle& InActorReference);`
- L396 _public prototype_ `static bool IsKinematic_AssumesLocked(const FPhysicsActorHandle& InActorReference);`
- L397 _public prototype_ `static bool IsSleeping(const FPhysicsActorHandle& InActorReference);`
- L398 _public prototype_ `static bool IsCcdEnabled(const FPhysicsActorHandle& InActorReference);`
- L400 _public function_ `static bool HasSyncSceneData(const FPhysicsActorHandle& InHandle)` — @todo(mlentine): We don't have a notion of sync vs async and are a bit of both. Does this work?
- L401 _public function_ `static bool HasAsyncSceneData(const FPhysicsActorHandle& InHandle)`
- L402 _public prototype_ `static bool IsInScene(const FPhysicsActorHandle& InActorReference);`
- L404 _public prototype_ `static int32 GetAllShapes_AssumedLocked(const FPhysicsActorHandle& InActorHandle,TArray<FPhysicsShapeReference_Chaos,FDefaultAllocator>& OutShapes);`
- L405 _public prototype_ `static int32 GetAllShapes_AssumedLocked(const FPhysicsActorHandle& InActorHandle,PhysicsInterfaceTypes::FInlineShapeArray& OutShapes);`
- L407 _public prototype_ `static bool CanSimulate_AssumesLocked(const FPhysicsActorHandle& InActorReference);`
- L408 _public prototype_ `static float GetMass_AssumesLocked(const FPhysicsActorHandle& InActorReference);`
- L410 _public prototype_ `static void SetSendsSleepNotifies_AssumesLocked(const FPhysicsActorHandle& InActorReference,bool bSendSleepNotifies);`
- L411 _public prototype_ `static void ClearWakeEvent_AssumesLocked(const FPhysicsActorHandle& InActorReference);`
- L412 _public prototype_ `static void PutToSleep_AssumesLocked(const FPhysicsActorHandle& InActorReference);`
- L413 _public prototype_ `static void WakeUp_AssumesLocked(const FPhysicsActorHandle& InActorReference);`
- L415 _public prototype_ `static void SetIsKinematic_AssumesLocked(const FPhysicsActorHandle& InActorReference,bool bIsKinematic);`
- L416 _public prototype_ `static void SetCcdEnabled_AssumesLocked(const FPhysicsActorHandle& InActorReference,bool bIsCcdEnabled);`
- L417 _public prototype_ `static void SetMACDEnabled_AssumesLocked(const FPhysicsActorHandle& InActorReference, bool bIsMACDEnabled);`
- L418 _public prototype_ `static void SetPartialIslandSleepAllowed_AssumesLocked(const FPhysicsActorHandle& InActorReference, bool bIsPartialIslandSleepAllowed);`
- L419 _public prototype_ `static void SetPositionSolverIterationCount_AssumesLocked(const FPhysicsActorHandle& InActorReference, int32 PositionSolverIterationCount);`
- L420 _public prototype_ `static void SetVelocitySolverIterationCount_AssumesLocked(const FPhysicsActorHandle& InActorReference, int32 VelocitySolverIterationCount);`
- L421 _public prototype_ `static void SetProjectionSolverIterationCount_AssumesLocked(const FPhysicsActorHandle& InActorReference, int32 ProjectionSolverIterationCount);`
- L422 _public prototype_ `static void SetIgnoreAnalyticCollisions_AssumesLocked(const FPhysicsActorHandle& InActorReference,bool bIsCcdEnabled);`
- L424 _public prototype_ `static FTransform GetGlobalPose_AssumesLocked(const FPhysicsActorHandle& InActorReference);`
- L426 _public prototype_ `static FTransform GetTransform_AssumesLocked(const FPhysicsActorHandle& InRef,bool bForceGlobalPose = false);`
- L428 _public prototype_ `static bool HasKinematicTarget_AssumesLocked(const FPhysicsActorHandle& InActorReference);`
- L429 _public prototype_ `static FTransform GetKinematicTarget_AssumesLocked(const FPhysicsActorHandle& InActorReference);`
- L431 _public prototype_ `static FVector GetLinearVelocity_AssumesLocked(const FPhysicsActorHandle& InActorReference);`
- L432 _public prototype_ `static void SetLinearVelocity_AssumesLocked(const FPhysicsActorHandle& InActorReference,const FVector& InNewVelocity,bool bAutoWake = true);`
- L434 _public prototype_ `static FVector GetAngularVelocity_AssumesLocked(const FPhysicsActorHandle& InActorReference);`
- L435 _public prototype_ `static void SetAngularVelocity_AssumesLocked(const FPhysicsActorHandle& InActorReference,const FVector& InNewVelocity,bool bAutoWake = true);`
- L436 _public prototype_ `static float GetMaxAngularVelocity_AssumesLocked(const FPhysicsActorHandle& InActorReference);`
- L437 _public prototype_ `static float GetMaxLinearVelocity_AssumesLocked(const FPhysicsActorHandle& InActorReference);`
- L438 _public prototype_ `static void SetMaxAngularVelocity_AssumesLocked(const FPhysicsActorHandle& InActorReference,float InMaxAngularVelocityRadians);`
- L439 _public prototype_ `static void SetMaxLinearVelocity_AssumesLocked(const FPhysicsActorHandle& InActorReference, float InMaxLinearVelocity);`
- L441 _public prototype_ `static float GetMaxDepenetrationVelocity_AssumesLocked(const FPhysicsActorHandle& InActorReference);`
- L442 _public prototype_ `static void SetMaxDepenetrationVelocity_AssumesLocked(const FPhysicsActorHandle& InActorReference,float InMaxDepenetrationVelocity);`
- L444 _public prototype_ `static FVector GetWorldVelocityAtPoint_AssumesLocked(const FPhysicsActorHandle& InActorReference,const FVector& InPoint);`
- L445 _public prototype_ `static FVector GetWorldVelocityAtPoint_AssumesLocked(const Chaos::FRigidBodyHandle_Internal* InActorReference, const FVector& InPoint);`
- L447 _public prototype_ `static FTransform GetComTransform_AssumesLocked(const FPhysicsActorHandle& InActorReference);`
- L448 _public prototype_ `static FTransform GetComTransformLocal_AssumesLocked(const FPhysicsActorHandle& InActorReference);`
- L449 _public prototype_ `static void SetComTransformLocal_AssumesLocked(const FPhysicsActorHandle& InActorReference, const FTransform& InTransform);`
- L451 _public prototype_ `static FVector GetLocalInertiaTensor_AssumesLocked(const FPhysicsActorHandle& InActorReference);`
- L452 _public prototype_ `static void SetLocalInertiaTensor_AssumesLocked(const FPhysicsActorHandle& InActorReference, const FVector& InInertiaTensor);`
- L453 _public prototype_ `static FBox GetBounds_AssumesLocked(const FPhysicsActorHandle& InActorReference);`
- L454 _public prototype_ `static FBox GetBounds_AssumesLocked(const FPhysicsActorHandle& InActorReference, const FTransform& InTransform);`
- L455 _public prototype_ `static FBox GetBoundsLocal_AssumesLocked(const FPhysicsActorHandle& InActorReference);`
- L457 _public prototype_ `static void SetLinearDamping_AssumesLocked(const FPhysicsActorHandle& InActorReference,float InDamping);`
- L458 _public prototype_ `static void SetAngularDamping_AssumesLocked(const FPhysicsActorHandle& InActorReference,float InDamping);`
- L460 _public prototype_ `static void AddForce_AssumesLocked(const FPhysicsActorHandle& InActorReference, const FVector& Force, bool bAllowSubstepping, bool bAccelChange, bool bIsInternal = false);`
- L461 _public prototype_ `static void AddForceAtPosition_AssumesLocked(const FPhysicsActorHandle& InActorReference, const FVector& Force, const FVector& Position, bool bAllowSubstepping, bool bIsLocalForce = false, bool bIsInternal = false);`
- L462 _public prototype_ `static void AddRadialForce_AssumesLocked(const FPhysicsActorHandle& InActorReference, const FVector& Origin, const float Radius, const float Strength, const uint8 Falloff, bool bAccelChange, bool bAllowSubstepping, bool bIsInternal = false);`
- L463 _public prototype_ `static void AddTorque_AssumesLocked(const FPhysicsActorHandle& InActorReference, const FVector& Torque, bool bAllowSubstepping, bool bAccelChange, bool bIsInternal = false);`
- L465 _public prototype_ `static void AddImpulse_AssumesLocked(const FPhysicsActorHandle& InActorReference,const FVector& InForce, bool bIsInternal = false);`
- L466 _public prototype_ `static void AddAngularImpulseInRadians_AssumesLocked(const FPhysicsActorHandle& InActorReference,const FVector& InTorque, bool bIsInternal = false);`
- L467 _public prototype_ `static void AddVelocity_AssumesLocked(const FPhysicsActorHandle& InActorReference,const FVector& InForce, bool bIsInternal = false);`
- L468 _public prototype_ `static void AddAngularVelocityInRadians_AssumesLocked(const FPhysicsActorHandle& InActorReference,const FVector& InTorque, bool bIsInternal = false);`
- L469 _public prototype_ `static void AddImpulseAtLocation_AssumesLocked(const FPhysicsActorHandle& InActorReference,const FVector& InImpulse,const FVector& InLocation, bool bIsInternal = false);`
- L470 _public prototype_ `static void AddVelocityChangeImpulseAtLocation_AssumesLocked(const FPhysicsActorHandle& InActorReference, const FVector& InVelocityDelta, const FVector& InLocation, bool bIsInternal = false);`
- L471 _public prototype_ `static void AddRadialImpulse_AssumesLocked(const FPhysicsActorHandle& InActorReference,const FVector& InOrigin,float InRadius,float InStrength,ERadialImpulseFalloff InFalloff,bool bInVelChange, bool bIsInternal = false);`
- L473 _public prototype_ `static bool IsGravityEnabled_AssumesLocked(const FPhysicsActorHandle& InActorReference);`
- L474 _public prototype_ `static void SetGravityEnabled_AssumesLocked(const FPhysicsActorHandle& InActorReference,bool bEnabled);`
- L475 _public prototype_ `static int32 GetGravityGroupIndex_AssumesLocked(const FPhysicsActorHandle& InActorReference);`
- L476 _public prototype_ `static void SetGravityGroupIndex_AssumesLocked(const FPhysicsActorHandle& InActorReference, uint32 Index);`
- L478 _public prototype_ `static bool GetUpdateKinematicFromSimulation_AssumesLocked(const FPhysicsActorHandle& InActorReference);`
- L479 _public prototype_ `static void SetUpdateKinematicFromSimulation_AssumesLocked(const FPhysicsActorHandle& InActorReference, bool bUpdateKinematicFromSimulation);`
- L481 _public prototype_ `static bool GetGyroscopicTorqueEnabled_AssumesLocked(const FPhysicsActorHandle& InActorReference);`
- L482 _public prototype_ `static void SetGyroscopicTorqueEnabled_AssumesLocked(const FPhysicsActorHandle& InActorReference, bool bGyroscopicTorqueEnabled);`
- L484 _public prototype_ `static void SetOneWayInteraction_AssumesLocked(const FPhysicsActorHandle& InHandle, bool InOneWayInteraction);`
- L486 _public prototype_ `static float GetSleepEnergyThreshold_AssumesLocked(const FPhysicsActorHandle& InActorReference);`
- L487 _public prototype_ `static void SetSleepEnergyThreshold_AssumesLocked(const FPhysicsActorHandle& InActorReference, float InEnergyThreshold);`
- L489 _public prototype_ `static void SetSleepThresholdMultiplier_AssumesLocked(const FPhysicsActorHandle& InActorReference, float ThresholdMultiplier);`
- L491 _public prototype_ `static void SetMass_AssumesLocked(const FPhysicsActorHandle& InHandle,float InMass);`
- L492 _public prototype_ `static void SetMassSpaceInertiaTensor_AssumesLocked(const FPhysicsActorHandle& InHandle,const FVector& InTensor);`
- L493 _public prototype_ `static void SetComLocalPose_AssumesLocked(const FPhysicsActorHandle& InHandle,const FTransform& InComLocalPose);`
- L495 _public prototype_ `static bool IsInertiaConditioningEnabled_AssumesLocked(const FPhysicsActorHandle& InActorReference);`
- L496 _public prototype_ `static void SetInertiaConditioningEnabled_AssumesLocked(const FPhysicsActorHandle& InActorReference, bool bEnabled);`
- L498 _public prototype_ `static float GetStabilizationEnergyThreshold_AssumesLocked(const FPhysicsActorHandle& InHandle);`
- L499 _public prototype_ `static void SetStabilizationEnergyThreshold_AssumesLocked(const FPhysicsActorHandle& InHandle,float InThreshold);`
- L500 _public prototype_ `static void SetSolverPositionIterationCount_AssumesLocked(const FPhysicsActorHandle& InHandle, int32 InSolverIterationCount);`
- L501 _public prototype_ `static void SetSolverVelocityIterationCount_AssumesLocked(const FPhysicsActorHandle& InHandle, int32 InSolverIterationCount);`
- L502 _public prototype_ `static void SetSolverProjectionIterationCount_AssumesLocked(const FPhysicsActorHandle& InHandle, int32 InSolverIterationCount);`
- L503 _public prototype_ `static float GetWakeCounter_AssumesLocked(const FPhysicsActorHandle& InHandle);`
- L504 _public prototype_ `static void SetWakeCounter_AssumesLocked(const FPhysicsActorHandle& InHandle,float InWakeCounter);`
- L506 _public prototype_ `static void SetInitialized_AssumesLocked(const FPhysicsActorHandle& InHandle,bool InInitialized);`
- L508 _public prototype_ `static SIZE_T GetResourceSizeEx(const FPhysicsActorHandle& InActorRef);`
- L510 _public prototype_ `static FPhysicsConstraintHandle CreateConstraint(Chaos::FPhysicsObject* Body1, Chaos::FPhysicsObject* Body2, const FTransform& InLocalFrame1, const FTransform& InLocalFrame2);`
- L511 _public prototype_ `static FPhysicsConstraintHandle CreateConstraint(const FPhysicsActorHandle& InActorRef1,const FPhysicsActorHandle& InActorRef2,const FTransform& InLocalFrame1,const FTransform& InLocalFrame2);`
- L513 _public prototype_ `static FPhysicsConstraintHandle CreateSuspension(Chaos::FPhysicsObject* Body, const FVector& InLocalFrame);`
- L514 _public prototype_ `static FPhysicsConstraintHandle CreateSuspension(const FPhysicsActorHandle& InActorRef, const FVector& InLocalFrame);`
- L515 _public prototype_ `static void SetConstraintUserData(const FPhysicsConstraintHandle& InConstraintRef,void* InUserData);`
- L516 _public prototype_ `static void ReleaseConstraint(FPhysicsConstraintHandle& InConstraintRef);`
- L518 _public prototype_ `static FTransform GetLocalPose(const FPhysicsConstraintHandle& InConstraintRef,EConstraintFrame::Type InFrame);`
- L519 _public prototype_ `static FTransform GetGlobalPose(const FPhysicsConstraintHandle& InConstraintRef,EConstraintFrame::Type InFrame);`
- L520 _public prototype_ `static FVector GetLocation(const FPhysicsConstraintHandle& InConstraintRef);`
- L521 _public prototype_ `static void GetForce(const FPhysicsConstraintHandle& InConstraintRef,FVector& OutLinForce,FVector& OutAngForce);`
- L522 _public prototype_ `static void GetDriveLinearVelocity(const FPhysicsConstraintHandle& InConstraintRef,FVector& OutLinVelocity);`
- L523 _public prototype_ `static void GetDriveAngularVelocity(const FPhysicsConstraintHandle& InConstraintRef,FVector& OutAngVelocity);`
- L525 _public prototype_ `static float GetCurrentSwing1(const FPhysicsConstraintHandle& InConstraintRef);`
- L526 _public prototype_ `static float GetCurrentSwing2(const FPhysicsConstraintHandle& InConstraintRef);`
- L527 _public prototype_ `static float GetCurrentTwist(const FPhysicsConstraintHandle& InConstraintRef);`
- L529 _public prototype_ `static void SetCanVisualize(const FPhysicsConstraintHandle& InConstraintRef,bool bInCanVisualize);`
- L530 _public prototype_ `static void SetCollisionEnabled(const FPhysicsConstraintHandle& InConstraintRef,bool bInCollisionEnabled);`
- L531 _public prototype_ `static void SetProjectionEnabled_AssumesLocked(const FPhysicsConstraintHandle& InConstraintRef,bool bInProjectionEnabled,float InLinearAlpha = 1.0f,float InAngularAlpha = 0.0f, float InLinearTolerance = 0.0f, float InAngularToleranceDeg = 0.0f);`
- L532 _public prototype_ `static void SetShockPropagationEnabled_AssumesLocked(const FPhysicsConstraintHandle& InConstraintRef, bool bInShockPropagationEnabled, float InShockPropagationAlpha);`
- L533 _public prototype_ `static void SetParentDominates_AssumesLocked(const FPhysicsConstraintHandle& InConstraintRef, bool bInParentDominates);`
- L534 _public prototype_ `static void SetMassConditioningEnabled_AssumesLocked(const FPhysicsConstraintHandle& InConstraintRef, bool bInMassConditioningEnabled);`
- L535 _public prototype_ `static void SetUseLinearJointSolver_AssumesLocked(const FPhysicsConstraintHandle& InConstraintRef, bool bInUseLinearJointSolver);`
- L536 _public prototype_ `static void SetBreakForces_AssumesLocked(const FPhysicsConstraintHandle& InConstraintRef,float InLinearBreakForce,float InAngularBreakForce);`
- L537 _public prototype_ `static void SetViolationCallbackThresholds_AssumesLocked(const FPhysicsConstraintHandle& InConstraintRef,float InLinearBreakViolation,float InAngularBreakViolation);`
- L538 _public prototype_ `static void SetPlasticityLimits_AssumesLocked(const FPhysicsConstraintHandle& InConstraintRef, float InLinearPlasticityLimit, float InAngularPlasticityLimit, EConstraintPlasticityType InLinearPlasticityType);`
- L539 _public prototype_ `static void SetContactTransferScale_AssumesLocked(const FPhysicsConstraintHandle& InConstraintRef, float InContactTransferScale);`
- L540 _public prototype_ `static void SetLocalPose(const FPhysicsConstraintHandle& InConstraintRef, const FTransform& InPose, EConstraintFrame::Type InFrame);`
- L542 _public prototype_ `static void SetDrivePosition(const FPhysicsConstraintHandle& InConstraintRef,const FVector& InPosition);`
- L543 _public prototype_ `static void SetDriveOrientation(const FPhysicsConstraintHandle& InConstraintRef,const FQuat& InOrientation);`
- L544 _public prototype_ `static void SetDriveLinearVelocity(const FPhysicsConstraintHandle& InConstraintRef,const FVector& InLinVelocity);`
- L545 _public prototype_ `static void SetDriveAngularVelocity(const FPhysicsConstraintHandle& InConstraintRef,const FVector& InAngVelocity);`
- L547 _public prototype_ `static void SetTwistLimit(const FPhysicsConstraintHandle& InConstraintRef,float InLowerLimit,float InUpperLimit,float InContactDistance);`
- L548 _public prototype_ `static void SetSwingLimit(const FPhysicsConstraintHandle& InConstraintRef,float InYLimit,float InZLimit,float InContactDistance);`
- L549 _public prototype_ `static void SetLinearLimit(const FPhysicsConstraintHandle& InConstraintRef,float InLimit);`
- L551 _public prototype_ `static bool IsBroken(const FPhysicsConstraintHandle& InConstraintRef);`
- L553 _public prototype_ `static void SetGeometry(FPhysicsShapeHandle& InShape, Chaos::FImplicitObjectPtr&& InGeometry);`
- L556 _public function_ `static void SetGeometry(FPhysicsShapeHandle& InShape, TUniquePtr<Chaos::FImplicitObject>&& InGeometry)` — `UE_DEPRECATED(5.4, "Use SetGeometry with FImplicitObjectPtr instead.")`
- L558 _public prototype_ `UE_DEPRECATED(5.7, "Use GetCombinedShapeFilterData instead") static FCollisionFilterData GetSimulationFilte`
- L559 _public prototype_ `UE_DEPRECATED(5.7, "Use GetCombinedShapeFilterData instead") static FCollisionFilterData GetQueryFilte` — `UE_DEPRECATED(5.7, "Use GetCombinedShapeFilterData instead")`
- L560 _public prototype_ `static Chaos::Filter::FShapeFilterData GetShapeFilterData(const FPhysicsShapeHandle& InShape);` — `UE_DEPRECATED(5.7, "Use GetCombinedShapeFilterData instead")` — `UE_DEPRECATED(5.7, "Use GetCombinedShapeFilterData instead")`
- L561 _public prototype_ `static Chaos::Filter::FInstanceData GetFilterInstanceData(const FPhysicsShapeHandle& InShape);`
- L562 _public prototype_ `static Chaos::Filter::FCombinedShapeFilterData GetCombinedShapeFilterData(const FPhysicsShapeHandle& InShape);`
- L563 _public prototype_ `static bool IsSimulationShape(const FPhysicsShapeHandle& InShape);`
- L564 _public prototype_ `static bool IsQueryShape(const FPhysicsShapeHandle& InShape);`
- L565 _public prototype_ `static ECollisionShapeType GetShapeType(const FPhysicsShapeHandle& InShape);`
- L566 _public prototype_ `static FTransform GetLocalTransform(const FPhysicsShapeHandle& InShape);`
- L569 _public prototype_ `static void* GetUserData(const FPhysicsShapeHandle& InShape);`
- L570 _public prototype_ `static void SetUserData(const FPhysicsShapeHandle& InShape, void* InUserData);`
- L571 _public prototype_ `static FPhysicsShapeHandle CloneShape(const FPhysicsShapeHandle& InShape);`
- L572 _public prototype_ `static FPhysicsGeometryCollection_Chaos GetGeometryCollection(const FPhysicsShapeHandle& InShape);`
- L573 _public prototype_ `static FPhysicsGeometryCollection_Chaos GetGeometryCollection(const FPhysicsGeometry& InShape);`
- L577 _public prototype_ `static void SetMaskFilter(const FPhysicsShapeHandle& InShape,FMaskFilter InFilter);` — @todo(mlentine): Which of these do we need to support? Set the mask filter of a shape, which is an extra level of filtering during collision detection / query for extra channels like "Blue Team" and "Red Team"
- L578 _public prototype_ `UE_DEPRECATED(5.7, "Use SetCombinedShapeFilterData instead") static void SetSimulationFilter(const FPhysicsShapeHandle& InShape,`
- L579 _public prototype_ `UE_DEPRECATED(5.7, "Use SetCombinedShapeFilterData instead") static void SetQueryFilter(const FPhysicsShapeHandle& InShape,` — `UE_DEPRECATED(5.7, "Use SetCombinedShapeFilterData instead")`
- L580 _public prototype_ `static void SetShapeFilterData(const FPhysicsShapeHandle& InShape, const Chaos::Filter::FShapeFilterData& InFilter);` — `UE_DEPRECATED(5.7, "Use SetCombinedShapeFilterData instead")` — `UE_DEPRECATED(5.7, "Use SetCombinedShapeFilterData instead")`
- L581 _public prototype_ `static void SetFilterInstanceData(const FPhysicsShapeHandle& InShape, const Chaos::Filter::FInstanceData& InFilter);`
- L582 _public prototype_ `static void SetCombinedShapeFilterData(const FPhysicsShapeHandle& InShape, const Chaos::Filter::FCombinedShapeFilterData& InFilter);`
- L583 _public prototype_ `static void SetIsSimulationShape(const FPhysicsShapeHandle& InShape,bool bIsSimShape);`
- L584 _public prototype_ `static void SetIsProbeShape(const FPhysicsShapeHandle& InShape,bool bIsProbeShape);`
- L585 _public prototype_ `static void SetIsQueryShape(const FPhysicsShapeHandle& InShape,bool bIsQueryShape);`
- L586 _public prototype_ `static void SetLocalTransform(const FPhysicsShapeHandle& InShape,const FTransform& NewLocalTransform);`
- L588 _public prototype_ `UE_INTERNAL static void SerializeParticleStateToBuffer(const FPhysicsActorHandle& InActorHandle, Chaos::FSerializedDataBuffer& OutSerializedData, Chaos::ESerializedDataContext DataContext);`
- L589 _public prototype_ `UE_INTERNAL static void ApplySerializedStateToParticle(const FPhysicsActorHandle& InActorHandle, TUniquePtr<Chaos::FSerializedDataBuffer>&& InSerializedData, Chaos::ESerializedDataContext DataContext);`
- L591 _public prototype_ `UE_INTERNAL static void SerializeConstraintStateToBuffer(const FPhysicsConstraintHandle& ConstraintHandle, Chaos::FSerializedDataBuffer& OutSerializedData, Chaos::ESerializedDataContext DataContext);`
- L592 _public prototype_ `UE_INTERNAL static void ApplySerializedStateToConstraint(const FPhysicsConstraintHandle& ConstraintHandle, Chaos::FSerializedDataBufferPtr&& InSerializedData, Chaos::ESerializedDataContext DataContext);`

#### Free symbols / members of external scopes

- L127 _namespace_ `namespace EConstraintFrame`
- L137 _namespace_ `namespace PhysicsInterfaceTypes`
- L163 _enumerator_ `enum { NumInlinedPxShapeElements = 32 }; typedef TArray<FPhysicsShapeHandle` (scope `PhysicsInterfaceTypes::__anon971acb7a0103`) — Default number of inlined elements used in FInlineShapeArray. Increase if for instance character meshes use more than this number of physics bodies and are involved in many queries.
- L166 _typedef_ `typedef TArray<FPhysicsShapeHandle, TInlineAllocator<NumInlinedPxShapeElements>> FInlineShapeArray;` (scope `PhysicsInterfaceTypes`) — Array that is intended for use when fetching shapes from a rigid body.
- L200 _typedef_ `typedef uint8 FMaskFilter;` — This filter allows us to refine queries (channel, object) with an additional level of ignore by tagging entire classes of objects (e.g. "Red team", "Blue team") If(QueryIgnoreMask & ShapeFilter != 0) filter out
- L202 _namespace_ `namespace Chaos`
- L218 _typedef_ `using FAABB3 = TAABB<FReal, 3>;` (scope `Chaos`)
- L225 _typedef_ `using FSphere = TSphere<FReal, 3>;` (scope `Chaos`)
- L234 _typedef_ `using FSerializedDataBufferPtr = TUniquePtr<FSerializedDataBuffer>;` (scope `Chaos`)
- L279 _function_ `friend uint32 GetTypeHash(const FPhysicsShapeReference_Chaos& InShapeReference)`
- L333 _namespace_ `namespace physx`

### `Source/Runtime/PhysicsCore/Public/Chaos/ChaosPhysicalMaterial.h` (Public)


#### class `UChaosPhysicalMaterial`  
`class UChaosPhysicalMaterial : public UObject`  
_L22-60_
- reflection: `UCLASS(BlueprintType, Blueprintable, CollapseCategories, HideCategories = Object, MinimalAPI)`
- inherits: `UObject`
- desc: Physical materials are used to define the response of a physical object when interacting dynamically with the world.
- L27 _private prototype_ `void CopyTo(Chaos::FChaosPhysicsMaterial& Mat) const;` — Update the values in \p Mat to reflect the values in this \c UObject.
- L35 _private member_ `float Friction;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PhysicalMaterial, meta=(ClampMin=0))` — Friction value of a surface in motion, controls how easily things can slide on this surface (0 is frictionless, higher values increase the amount of friction)
- L39 _private member_ `float StaticFriction;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PhysicalMaterial, meta = (ClampMin = 0))` — Friction value of surface at rest, controls how easily things can slide on this surface (0 is frictionless, higher values increase the amount of friction)
- L43 _private member_ `float Restitution;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PhysicalMaterial, meta=(ClampMin=0))` — Restitution or 'bounciness' of this surface, between 0 (no bounce) and 1 (outgoing velocity is same as incoming).
- L47 _private member_ `float LinearEtherDrag;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PhysicalMaterial", meta=(ClampMin = 0))` — Uniform linear ether drag, the resistance a body experiences to its translation.
- L51 _private member_ `float AngularEtherDrag;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PhysicalMaterial", meta = (ClampMin = 0))` — Uniform angular ether drag, the resistance a body experiences to its rotation.
- L55 _private member_ `float SleepingLinearVelocityThreshold;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PhysicalMaterial, meta=(ClampMin=0))` — How much to scale the damage threshold by on any destructible we are applied to
- L59 _private member_ `float SleepingAngularVelocityThreshold;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PhysicalMaterial, meta=(ClampMin=0))` — How much to scale the damage threshold by on any destructible we are applied to

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Chaos`

### `Source/Runtime/PhysicsCore/Public/Chaos/ChaosScene.h` (Public)


#### struct `FChaosSceneCallbackInput`  
`struct FChaosSceneCallbackInput : public Chaos::FSimCallbackInput`  
_L68-73_
- inherits: `Chaos::FSimCallbackInput`
- L70 _public member_ `Chaos::FVec3 Gravity;`
- L72 _public function_ `void Reset()`

#### struct `FChaosSceneSimCallback`  
`struct FChaosSceneSimCallback : public Chaos::TSimCallbackObject<FChaosSceneCallbackInput>`  
_L75-79_
- inherits: `Chaos::TSimCallbackObject<FChaosSceneCallbackInput>`
- L77 _public prototype_ `virtual void OnPreSimulate_Internal() override;`
- L78 _public prototype_ `virtual FName GetFNameForStatId() const override;`

#### class `FChaosScene`  
`class FChaosScene #if WITH_ENGINE : public FGCObject #endif`  
_L84-223_
- inherits: `FGCObject`
- desc: Low level Chaos scene used when building custom simulations that don't exist in the main world physics scene.
- L90 _public prototype_ `FChaosScene( UObject* OwnerPtr , Chaos::FReal InAsyncDt , const FName& DebugName = NAME_None );`
- L96 _public prototype_ `virtual ~FChaosScene();`
- L101 _public function_ `Chaos::FPhysicsSolver* GetSolver() const` — Get the internal Chaos solver object
- L105 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject Interface ///////////////////////////////////////////////////
- L106 _public function_ `virtual FString GetReferencerName() const`
- L113 _public prototype_ `const Chaos::ISpatialAcceleration<Chaos::FAccelerationStructureHandle, Chaos::FReal, 3>* GetSpacialAcceleration() const;`
- L114 _public prototype_ `Chaos::ISpatialAcceleration<Chaos::FAccelerationStructureHandle, Chaos::FReal, 3>* GetSpacialAcceleration();`
- L116 _public prototype_ `void AddActorsToScene_AssumesLocked(TArray<FPhysicsActorHandle>& InHandles,const bool bImmediate=true);`
- L117 _public prototype_ `void RemoveActorFromAccelerationStructure(FPhysicsActorHandle Actor);`
- L118 _public prototype_ `void RemoveActorFromAccelerationStructureImp(Chaos::FGeometryParticle* Particle);`
- L119 _public prototype_ `void UpdateActorsInAccelerationStructure(const TArrayView<FPhysicsActorHandle>& Actors);`
- L120 _public prototype_ `void UpdateActorInAccelerationStructure(const FPhysicsActorHandle& Actor);`
- L122 _public prototype_ `void WaitPhysScenes();`
- L128 _public prototype_ `void CopySolverAccelerationStructure();` — Copies the acceleration structure out of the solver, does no thread safety checking so ensure calls to this are made at appropriate sync points if required
- L135 _public prototype_ `void Flush();` — Flushes all pending global, task and solver command queues and refreshes the spatial acceleration for the scene. Required when querying against a currently non-running scene to ensure the scene is correctly represented
- L137 _public prototype_ `void AddPieModifiedObject(UObject* InObj);`
- L140 _public prototype_ `void StartFrame();`
- L141 _public prototype_ `void SetUpForFrame(const FVector* NewGrav,float InDeltaSeconds,float InMinPhysicsDeltaTime,float InMaxPhysicsDeltaTime,float InMaxSubstepDeltaTime,int32 InMaxSubsteps,bool bSubstepping);`
- L142 _public prototype_ `void EndFrame();`
- L144 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPhysScenePostTick,FChaosScene*);`
- L145 _public member_ `FOnPhysScenePostTick OnPhysScenePostTick;`
- L147 _public prototype_ `void KillSafeAsyncTasks();`
- L148 _public prototype_ `void WaitSolverTasks();`
- L149 _public prototype_ `bool AreAnyTasksPending() const;`
- L150 _public prototype_ `void BeginDestroy();`
- L151 _public prototype_ `bool IsCompletionEventComplete() const;`
- L152 _public prototype_ `FGraphEventArray GetCompletionEvents();`
- L154 _public function_ `void SetNetworkDeltaTimeScale(float InDeltaTimeScale)`
- L155 _public function_ `float GetNetworkDeltaTimeScale() const`
- L159 _protected member_ `Chaos::ISpatialAccelerationCollection<Chaos::FAccelerationStructureHandle, Chaos::FReal, 3>* SolverAccelerationStructure;`
- L162 _protected member_ `FChaosSolversModule* ChaosModule;` — Control module for Chaos - cached to avoid constantly hitting the module manager
- L165 _protected member_ `Chaos::FPhysicsSolver* SceneSolver;` — Solver representing this scene
- L169 _protected member_ `TArray<TObjectPtr<UObject>> PieModifiedObjects;` — List of objects that we modified during a PIE run for physics simulation caching.
- L177 _protected function_ `virtual float OnStartFrame(float InDeltaTime)` — Engine interface BEGIN
- L178 _protected prototype_ `virtual void OnSyncBodies(Chaos::FPhysicsSolverBase* Solver);`
- L181 _protected member_ `float MDeltaTime;`
- L182 _protected member_ `float MNetworkDeltaTimeScale = 1.f;` — Scale passed in delta time by this. Used by NetworkPrediction to make clients slow down or catch up when needed
- L184 _protected member_ `UObject* Owner;`
- L188 _private prototype_ `TArray<Chaos::FPhysicsSolverBase*> GetPhysicsSolvers() const;` — Get all the physics solvers with the same owner
- L190 _private prototype_ `void SetGravity(const Chaos::FVec3& Acceleration);`
- L193 _private prototype_ `template <typename TSolver> void SyncBodies(TSolver* Solver);`
- L196 _private member_ `FGraphEventArray CompletionEvents;` — Taskgraph control
- L198 _private member_ `FChaosSceneSimCallback* SimCallback;`
- L202 _private member_ `FChaosVDContext CVDContextData;`
- L205 _public function_ `FChaosVDContext& GetChaosVDContextData()`
- L213 _public function_ `const ChaosDD::Private::FChaosDDScenePtr& GetDebugDrawScene() const`
- L218 _public prototype_ `void SetDebugDrawScene(const ChaosDD::Private::FChaosDDScenePtr& CDDScene);`
- L221 _private member_ `ChaosDD::Private::FChaosDDScenePtr CDDScene;`

#### Free symbols / members of external scopes

- L26 _macro_ `#define CHAOS_DEBUG_NAME 0`
- L30 _macro_ `#define XGE_FIXED 0` — Currently compilation issue with Incredibuild when including headers required by event template functions
- L43 _namespace_ `namespace Chaos`
- L144 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPhysScenePostTick,FChaosScene*);`

### `Source/Runtime/PhysicsCore/Public/Chaos/ChaosUserEntity.h` (Public)


#### class `FChaosUserDefinedEntity`  
`class FChaosUserDefinedEntity`  
_L8-24_
- L11 _public prototype_ `FChaosUserDefinedEntity() = delete;`
- L12 _public function_ `FChaosUserDefinedEntity(FName InEntityTypeName) : EntityTypeName(InEntityTypeName)`
- L13 _public prototype_ `virtual ~FChaosUserDefinedEntity() = default;`
- L15 _public function_ `FName GetEntityTypeName()`
- L20 _public prototype_ `virtual TWeakObjectPtr<UObject> GetOwnerObject() = 0;` — Get the UObject (usually a verse::component) that owns this FChaosUserDefinedEntity
- L23 _private member_ `FName EntityTypeName;`

#### struct `FChaosUserEntityAppend`  
`struct FChaosUserEntityAppend : public FChaosUserData`  
_L27-53_
- inherits: `FChaosUserData`
- desc: This is used to add your own Unreal Engine agnostic user entities to Chaos Physics Results
- L29 _public function_ `FChaosUserEntityAppend() : FChaosUserData() , ChaosUserData(nullptr) , UserDefinedEntity(nullptr)`
- L42 _public function_ `TWeakObjectPtr<UObject> GetOwnerObject()` — Get the UObject that controls the lifetime of the physics objects that will be referencing this UserData object. It will be stored as a weak pointer in hit/overlap results to verify that the raw PhysicsObject pointer they hold is valid.
- L51 _public member_ `FChaosUserData* ChaosUserData;` — Chaos data to access the physics body properties
- L52 _public member_ `FChaosUserDefinedEntity* UserDefinedEntity;`

### `Source/Runtime/PhysicsCore/Public/ChaosInterfaceWrapperCore.h` (Public)


#### struct `ChaosInterface::FDummyPhysType`  
`struct FDummyPhysType`  
_L28-28_

#### struct `ChaosInterface::FDummyPhysActor`  
`struct FDummyPhysActor`  
_L29-29_

#### struct `ChaosInterface::FDummyCallback`  
`template<typename DummyT> struct FDummyCallback`  
_L32-32_

#### struct `ChaosInterface::FPhysicsRaycastInputAdapater`  
`struct FPhysicsRaycastInputAdapater`  
_L39-51_
- desc: We use this struct so that if no conversion is needed in another API, we can avoid the copy (if we think that's critical)
- L41 _public function_ `FPhysicsRaycastInputAdapater(const FVector& InStart, const FVector& InDir, const EHitFlags InFlags) : Start(InStart) , Dir(InDir) , OutputFlags(InFlags)`
- L48 _public member_ `FVector Start;`
- L49 _public member_ `FVector Dir;`
- L50 _public member_ `EHitFlags OutputFlags;`

#### struct `ChaosInterface::FPhysicsSweepInputAdapater`  
`struct FPhysicsSweepInputAdapater`  
_L54-66_
- desc: We use this struct so that if no conversion is needed in another API, we can avoid the copy (if we think that's critical)
- L56 _public function_ `FPhysicsSweepInputAdapater(const FTransform& InStartTM, const FVector& InDir, const EHitFlags InFlags) : StartTM(InStartTM) , Dir(InDir) , OutputFlags(InFlags)`
- L63 _public member_ `FTransform StartTM;`
- L64 _public member_ `FVector Dir;`
- L65 _public member_ `EHitFlags OutputFlags;`

#### struct `ChaosInterface::FPhysicsOverlapInputAdapater`  
`struct FPhysicsOverlapInputAdapater`  
_L69-77_
- desc: We use this struct so that if no conversion is needed in another API, we can avoid the copy (if we think that's critical)
- L71 _public function_ `FPhysicsOverlapInputAdapater(const FTransform& InPose) : GeomPose(InPose)`
- L76 _public member_ `FTransform GeomPose;`

#### struct `ChaosInterface::FQueryDebugParams`  
`struct FQueryDebugParams`  
_L80-96_
- desc: This is used to add debug data to scene query visitors in non-shipping builds
- L83 _public function_ `FQueryDebugParams() : bDebugQuery(false) , bExternalQuery(true)`
- L86 _public member_ `bool bDebugQuery;`
- L87 _public member_ `bool bExternalQuery;`
- L88 _public function_ `bool IsDebugQuery() const`
- L89 _public function_ `bool IsExternalQuery() const`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace Chaos`
- L26 _namespace_ `namespace ChaosInterface`
- L35 _typedef_ `using FQueryFilterData UE_DEPRECATED(5.8, "Use ChaosInterface::FSceneQ` (scope `ChaosInterface`)
- L98 _prototype_ `UE_DEPRECATED(5.7, "Use GetCombinedShapeFilterData instead") extern FCollisionFilterData GetQueryFilterDa` (scope `ChaosInterface`)
- L99 _prototype_ `UE_DEPRECATED(5.7, "Use GetCombinedShapeFilterData instead") extern FCollisionFilterData GetSimulationFilterDa` (scope `ChaosInterface`) — `UE_DEPRECATED(5.7, "Use GetCombinedShapeFilterData instead")`
- L100 _prototype_ `extern Chaos::Filter::FShapeFilterData GetShapeFilterData(const Chaos::FPerShapeData& Shape);` (scope `ChaosInterface`) — `UE_DEPRECATED(5.7, "Use GetCombinedShapeFilterData instead")` — `UE_DEPRECATED(5.7, "Use GetCombinedShapeFilterData instead")`
- L101 _prototype_ `extern Chaos::Filter::FInstanceData GetFilterInstanceData(const Chaos::FPerShapeData& Shape);` (scope `ChaosInterface`)
- L102 _prototype_ `extern Chaos::Filter::FCombinedShapeFilterData GetCombinedShapeFilterData(const Chaos::FPerShapeData& Shape);` (scope `ChaosInterface`)
- L105 _prototype_ `ECollisionShapeType GetImplicitType(const Chaos::FImplicitObject& InGeometry);` (scope `ChaosInterface`)
- L107 _function_ `inline ECollisionShapeType GetType(const Chaos::FImplicitObject& InGeometry)` (scope `ChaosInterface`)
- L112 _prototype_ `Chaos::FReal GetRadius(const Chaos::FCapsule& InCapsule);` (scope `ChaosInterface`)
- L114 _prototype_ `Chaos::FReal GetHalfHeight(const Chaos::FCapsule& InCapsule);` (scope `ChaosInterface`)
- L117 _function_ `inline bool HadInitialOverlap(const FLocationHit& Hit)` (scope `ChaosInterface`)
- L122 _function_ `inline bool HadInitialOverlap(const FPTLocationHit& Hit)` (scope `ChaosInterface`)
- L127 _function_ `inline const Chaos::FPerShapeData* GetShape(const FActorShape& Hit)` (scope `ChaosInterface`)
- L132 _function_ `inline const Chaos::FPerShapeData* GetShape(const FPTActorShape& Hit)` (scope `ChaosInterface`)
- L137 _function_ `inline Chaos::FGeometryParticle* GetActor(const FActorShape& Hit)` (scope `ChaosInterface`)
- L142 _function_ `inline Chaos::FGeometryParticleHandle* GetActor(const FPTActorShape& Hit)` (scope `ChaosInterface`)
- L147 _function_ `inline Chaos::FReal GetDistance(const FLocationHit& Hit)` (scope `ChaosInterface`)
- L152 _function_ `inline Chaos::FReal GetDistance(const FPTLocationHit& Hit)` (scope `ChaosInterface`)
- L157 _function_ `inline FVector GetPosition(const FLocationHit& Hit)` (scope `ChaosInterface`)
- L162 _function_ `inline FVector GetPosition(const FPTLocationHit& Hit)` (scope `ChaosInterface`)
- L167 _function_ `inline FVector GetNormal(const FLocationHit& Hit)` (scope `ChaosInterface`)
- L172 _function_ `inline FVector GetNormal(const FPTLocationHit& Hit)` (scope `ChaosInterface`)
- L177 _function_ `inline FHitFlags GetFlags(const FLocationHit& Hit)` (scope `ChaosInterface`)
- L182 _function_ `inline FHitFlags GetFlags(const FPTLocationHit& Hit)` (scope `ChaosInterface`)
- L188 _function_ `FORCEINLINE void SetFlags(FLocationHit& Hit, FHitFlags Flags)` (scope `ChaosInterface`)
- L193 _function_ `FORCEINLINE void SetFlags(FPTLocationHit& Hit, FHitFlags Flags)` (scope `ChaosInterface`)
- L198 _function_ `inline uint32 GetInternalFaceIndex(const FQueryHit& Hit)` (scope `ChaosInterface`)
- L203 _function_ `inline uint32 GetInternalFaceIndex(const FPTQueryHit& Hit)` (scope `ChaosInterface`)
- L208 _function_ `inline void SetInternalFaceIndex(FQueryHit& Hit, uint32 FaceIndex)` (scope `ChaosInterface`)
- L213 _function_ `inline void SetInternalFaceIndex(FPTQueryHit& Hit, uint32 FaceIndex)` (scope `ChaosInterface`)
- L219 _function_ `inline uint32 GetInvalidPhysicsFaceIndex()` (scope `ChaosInterface`)
- L224 _function_ `inline uint32 GetTriangleMeshExternalFaceIndex(const FDummyPhysType& Shape, uint32 InternalFaceIndex)` (scope `ChaosInterface`)
- L229 _function_ `inline FTransform GetGlobalPose(const FDummyPhysActor& RigidActor)` (scope `ChaosInterface`)
- L234 _function_ `inline uint32 GetNumShapes(const FDummyPhysActor& RigidActor)` (scope `ChaosInterface`)
- L239 _function_ `inline void GetShapes(const FDummyPhysActor& RigidActor, Chaos::FImplicitObject** ShapesBuffer, uint32 NumShapes)` (scope `ChaosInterface`)
- L244 _function_ `inline void SetActor(FDummyPhysType& Hit, FDummyPhysActor* Actor)` (scope `ChaosInterface`)
- L249 _function_ `inline void SetShape(FDummyPhysType& Hit, Chaos::FImplicitObject* Shape)` (scope `ChaosInterface`)
- L255 _function_ `template <typename HitType> HitType* GetBlock(FSQHitBuffer<HitType>& Callback)` (scope `ChaosInterface`)
- L261 _function_ `template <typename HitType> bool GetHasBlock(const FSQHitBuffer<HitType>& Callback)` (scope `ChaosInterface`)

### `Source/Runtime/PhysicsCore/Public/ChaosSQTypes.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/PhysicsCore/Public/ChaosVDSQVisitorHelpers.h` (Public)


#### Free symbols / members of external scopes

- L13 _macro_ `#define CVD_TRACE_SCOPED_SCENE_QUERY_VISIT_HELPER(Type, ParticleTransform, ParticleIndex, ShapeIndex, CurData) \`
- L24 _macro_ `#define CVD_FILL_HIT_DATA_HELPER(Hit, HitType) \`
- L30 _macro_ `#define CVD_SET_SQ_SHAPE_REJECT_REASON(Reason) \`
- L34 _namespace_ `namespace Chaos`
- L34 _namespace_ `namespace VisualDebugger` (scope `Chaos`)
- L34 _namespace_ `namespace TraceHelpers` (scope `Chaos::VisualDebugger`)
- L37 _prototype_ `template <class THitType> void FillCVDHitDataHelper(THitType& Hit, ECollisionQueryHitType HitType, FChaosVDQueryVisitStep& InOutVisitData);` (scope `Chaos::VisualDebugger::TraceHelpers`)
- L38 _function_ `inline void FillCVDQueryVisitData(FChaosVDQueryVisitStep& InOutVisitData, EChaosVDSceneQueryVisitorType Type, const FTransform& ParticleTransform, int32 ParticleIndex, int32 ShapeIndex, const Chaos::FQueryFastData* CurData)` (scope `Chaos::VisualDebugger::TraceHelpers`)
- L66 _function_ `template <class THitType> void FillCVDHitDataHelper(THitType& Hit, ECollisionQueryHitType HitType, FChaosVDQueryVisitStep& InOutVisitData)` (scope `Chaos::VisualDebugger::TraceHelpers`)
- L95 _macro_ `#define CVD_TRACE_SCOPED_SCENE_QUERY_VISIT_HELPER(Type, ParticleTransform, ParticleIndex, ShapeIndex, CurData)`
- L98 _macro_ `#define CVD_FILL_HIT_DATA_HELPER(Hit, HitType)`
- L101 _macro_ `#define CVD_SET_SQ_SHAPE_REJECT_REASON(RejectReason)`

### `Source/Runtime/PhysicsCore/Public/CollisionQueryFilterCallbackCore.h` (Public)


#### enum `ECollisionQueryHitType`  
`enum class ECollisionQueryHitType : uint8`  
_L12-17_
- desc: Make sure this matches PxQueryHitType for HitTypeToPxQueryHitType to work
- L14 _public enumerator_ `None = 0`
- L15 _public enumerator_ `Touch = 1`
- L16 _public enumerator_ `Block = 2`

#### class `ICollisionQueryFilterCallback`  
`class ICollisionQueryFilterCallback`  
_L24-36_
- L27 _public typedef_ `using FQueryFilterData = Chaos::Filter::FQueryFilterData;`
- L29 _public prototype_ `virtual ~ICollisionQueryFilterCallback() = default;`
- L31 _public prototype_ `virtual ECollisionQueryHitType PreFilter(const FQueryFilterData& FilterData, const Chaos::FPerShapeData& Shape, const Chaos::FGeometryParticle& Actor) = 0;`
- L32 _public prototype_ `virtual ECollisionQueryHitType PreFilter(const FQueryFilterData& FilterData, const Chaos::FPerShapeData& Shape, const Chaos::FGeometryParticleHandle& Actor) = 0;`
- L34 _public prototype_ `virtual ECollisionQueryHitType PostFilter(const FQueryFilterData& FilterData, const ChaosInterface::FQueryHit& Hit) = 0;`
- L35 _public prototype_ `virtual ECollisionQueryHitType PostFilter(const FQueryFilterData& FilterData, const ChaosInterface::FPTQueryHit& Hit) = 0;`

#### class `FBlockAllCollisionQueryFilterCallback`  
`class FBlockAllCollisionQueryFilterCallback : public ICollisionQueryFilterCallback`  
_L38-48_
- inherits: `ICollisionQueryFilterCallback`
- L41 _public prototype_ `virtual ~FBlockAllCollisionQueryFilterCallback() = default;`
- L43 _public function_ `virtual ECollisionQueryHitType PreFilter(const FQueryFilterData& FilterData, const Chaos::FPerShapeData& Shape, const Chaos::FGeometryParticle& Actor)`
- L44 _public function_ `virtual ECollisionQueryHitType PreFilter(const FQueryFilterData& FilterData, const Chaos::FPerShapeData& Shape, const Chaos::FGeometryParticleHandle& Actor)`
- L46 _public function_ `virtual ECollisionQueryHitType PostFilter(const FQueryFilterData& FilterData, const ChaosInterface::FQueryHit& Hit)`
- L47 _public function_ `virtual ECollisionQueryHitType PostFilter(const FQueryFilterData& FilterData, const ChaosInterface::FPTQueryHit& Hit)`

#### class `FOverlapAllCollisionQueryFilterCallback`  
`class FOverlapAllCollisionQueryFilterCallback : public ICollisionQueryFilterCallback`  
_L50-60_
- inherits: `ICollisionQueryFilterCallback`
- L53 _public prototype_ `virtual ~FOverlapAllCollisionQueryFilterCallback() = default;`
- L55 _public function_ `virtual ECollisionQueryHitType PreFilter(const FQueryFilterData& FilterData, const Chaos::FPerShapeData& Shape, const Chaos::FGeometryParticle& Actor)`
- L56 _public function_ `virtual ECollisionQueryHitType PreFilter(const FQueryFilterData& FilterData, const Chaos::FPerShapeData& Shape, const Chaos::FGeometryParticleHandle& Actor)`
- L58 _public function_ `virtual ECollisionQueryHitType PostFilter(const FQueryFilterData& FilterData, const ChaosInterface::FQueryHit& Hit)`
- L59 _public function_ `virtual ECollisionQueryHitType PostFilter(const FQueryFilterData& FilterData, const ChaosInterface::FPTQueryHit& Hit)`

#### class `ICollisionQueryFilterCallbackBase`  
`class UE_DEPRECATED(5.8, "Use ICollisionQueryFilterCallback instead") ICollisionQueryFilterCallbackBase : public ICollisionQueryFilterCallback`  
_L63-99_
- inherits: `ICollisionQueryFilterCallback`
- L67 _public prototype_ `virtual ~ICollisionQueryFilterCallbackBase() = default;`
- L68 _public prototype_ `virtual ECollisionQueryHitType PostFilter(const FCollisionFilterData& FilterData, const ChaosInterface::FQueryHit& Hit) = 0;`
- L69 _public prototype_ `virtual ECollisionQueryHitType PreFilter(const FCollisionFilterData& FilterData, const Chaos::FPerShapeData& Shape, const Chaos::FGeometryParticle& Actor) = 0;`
- L71 _public prototype_ `virtual ECollisionQueryHitType PostFilter(const FCollisionFilterData& FilterData, const ChaosInterface::FPTQueryHit& Hit) = 0;`
- L72 _public prototype_ `virtual ECollisionQueryHitType PreFilter(const FCollisionFilterData& FilterData, const Chaos::FPerShapeData& Shape, const Chaos::FGeometryParticleHandle& Actor) = 0;`
- L75 _private function_ `static FCollisionFilterData GetLegacyFilterData(const FQueryFilterData& FilterData)`
- L80 _private function_ `virtual ECollisionQueryHitType PostFilter(const FQueryFilterData& FilterData, const ChaosInterface::FQueryHit& Hit) override`
- L85 _private function_ `virtual ECollisionQueryHitType PreFilter(const FQueryFilterData& FilterData, const Chaos::FPerShapeData& Shape, const Chaos::FGeometryParticle& Actor) override`
- L90 _private function_ `virtual ECollisionQueryHitType PostFilter(const FQueryFilterData& FilterData, const ChaosInterface::FPTQueryHit& Hit) override`
- L95 _private function_ `virtual ECollisionQueryHitType PreFilter(const FQueryFilterData& FilterData, const Chaos::FPerShapeData& Shape, const Chaos::FGeometryParticleHandle& Actor) override`

#### class `FBlockAllQueryCallback`  
`class UE_DEPRECATED(5.8, "Use FBlockAllCollisionQueryFilterCallback instead") FBlockAllQueryCallback : public ICollisionQueryFilterCallbackBase`  
_L101-110_
- inherits: `ICollisionQueryFilterCallbackBase`
- L104 _public prototype_ `virtual ~FBlockAllQueryCallback() = default;`
- L105 _public function_ `virtual ECollisionQueryHitType PostFilter(const FCollisionFilterData& FilterData, const ChaosInterface::FQueryHit& Hit) override`
- L106 _public function_ `virtual ECollisionQueryHitType PreFilter(const FCollisionFilterData& FilterData, const Chaos::FPerShapeData& Shape, const Chaos::FGeometryParticle& Actor) override`
- L108 _public function_ `virtual ECollisionQueryHitType PostFilter(const FCollisionFilterData& FilterData, const ChaosInterface::FPTQueryHit& Hit) override`
- L109 _public function_ `virtual ECollisionQueryHitType PreFilter(const FCollisionFilterData& FilterData, const Chaos::FPerShapeData& Shape, const Chaos::FGeometryParticleHandle& Actor) override`

#### class `FOverlapAllQueryCallback`  
`class UE_DEPRECATED(5.8, "Use FOverlapAllCollisionQueryFilterCallback instead") FOverlapAllQueryCallback : public ICollisionQueryFilterCallbackBase`  
_L112-121_
- inherits: `ICollisionQueryFilterCallbackBase`
- L115 _public prototype_ `virtual ~FOverlapAllQueryCallback() = default;`
- L116 _public function_ `virtual ECollisionQueryHitType PostFilter(const FCollisionFilterData& FilterData, const ChaosInterface::FQueryHit& Hit) override`
- L117 _public function_ `virtual ECollisionQueryHitType PreFilter(const FCollisionFilterData& FilterData, const Chaos::FPerShapeData& Shape, const Chaos::FGeometryParticle& Actor) override`
- L119 _public function_ `virtual ECollisionQueryHitType PostFilter(const FCollisionFilterData& FilterData, const ChaosInterface::FPTQueryHit& Hit) override`
- L120 _public function_ `virtual ECollisionQueryHitType PreFilter(const FCollisionFilterData& FilterData, const Chaos::FPerShapeData& Shape, const Chaos::FGeometryParticleHandle& Actor) override`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace Chaos`

### `Source/Runtime/PhysicsCore/Public/CollisionShape.h` (Public)


#### enum `ECollisionShape::Type`  
`enum Type`  
_L10-16_
- L12 _public enumerator_ `Line`
- L13 _public enumerator_ `Box`
- L14 _public enumerator_ `Sphere`
- L15 _public enumerator_ `Capsule`

#### struct `FCollisionShape`  
`struct FCollisionShape`  
_L20-322_
- desc: Collision Shapes that supports Sphere, Capsule, Box, or Line
- L22 _public member_ `ECollisionShape::Type ShapeType;`
- L24 _public function_ `static constexpr float MinBoxExtent()`
- L25 _public function_ `static constexpr float MinSphereRadius()`
- L26 _public function_ `static constexpr float MinCapsuleRadius()`
- L27 _public function_ `static constexpr float MinCapsuleAxisHalfHeight()`
- L51 _public function_ `FCollisionShape()`
- L57 _public function_ `bool IsLine() const` — Is the shape currently a Line (Default)?
- L63 _public function_ `bool IsBox() const` — Is the shape currently a box?
- L69 _public function_ `bool IsSphere() const` — Is the shape currently a sphere?
- L75 _public function_ `bool IsCapsule() const` — Is the shape currently a capsule?
- L81 _public function_ `void SetBox(const FVector3f& HalfExtent)` — Utility function to Set Box and dimension
- L90 _public function_ `void SetSphere(const float Radius)` — Utility function to set Sphere with Radius
- L97 _public function_ `void SetCapsule(const float Radius, const float HalfHeight)` — Utility function to set Capsule with Radius and Half Height. Note: This is the full half-height (needs to include the sphere radius)
- L105 _public function_ `void SetCapsule(const FVector3f& Extent)` — Utility function to set Capsule from Extent data
- L113 _public function_ `void SetShape(const ECollisionShape::Type InShapeType, const FVector& Extent)` — Utility function to set a shape from a type and extent
- L139 _public function_ `bool IsNearlyZero() const` — Return true if nearly zero. If so, it will back out and use line trace instead
- L162 _public function_ `FVector GetExtent() const` — Utility function to return Extent of the shape
- L185 _public function_ `float GetCapsuleAxisHalfLength() const` — Get distance from center of capsule to center of sphere ends
- L192 _public function_ `FVector GetBox() const` — Utility function to get Box Extention
- L198 _public function_ `const float GetSphereRadius() const` — Utility function to get Sphere Radius
- L204 _public function_ `const float GetCapsuleRadius() const` — Utility function to get Capsule Radius
- L210 _public function_ `const float GetCapsuleHalfHeight() const` — Utility function to get Capsule Half Height. Note: This is the full half height which includes the sphere radius
- L215 _public function_ `FCollisionShape Inflate(const float Inflation) const`
- L256 _public function_ `inline FString ToString() const`
- L281 _public member_ `static struct FCollisionShape LineShape;` — Used by engine in multiple places. Since LineShape doesn't need any dimension, declare once and used by all codes.
- L284 _public function_ `static FCollisionShape MakeBox(const FVector& BoxHalfExtent)` — Static utility function to make a box
- L292 _public function_ `static FCollisionShape MakeBox(const FVector3f& BoxHalfExtent)` — Static utility function to make a box
- L300 _public function_ `static FCollisionShape MakeSphere(const float SphereRadius)` — Static utility function to make a sphere
- L308 _public function_ `static FCollisionShape MakeCapsule(const float CapsuleRadius, const float CapsuleHalfHeight)` — Static utility function to make a capsule. Note: This is the full half-height (needs to include the sphere radius)
- L316 _public function_ `static FCollisionShape MakeCapsule(const FVector& Extent)` — Static utility function to make a capsule

#### union `FCollisionShape::(anonymous)`  
``  
_L31-49_

#### struct `FCollisionShape::__anond2d7af05010a::(anonymous)`  
``  
_L33-37_

#### struct `FCollisionShape::__anond2d7af05010a::(anonymous)`  
``  
_L40-42_

#### struct `FCollisionShape::__anond2d7af05010a::(anonymous)`  
``  
_L45-48_

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace ECollisionShape`
- L34 _member_ `float HalfExtentX;` (scope `FCollisionShape::__anond2d7af05010a::__anond2d7af050208`)
- L35 _member_ `float HalfExtentY;` (scope `FCollisionShape::__anond2d7af05010a::__anond2d7af050208`)
- L36 _member_ `float HalfExtentZ;` (scope `FCollisionShape::__anond2d7af05010a::__anond2d7af050208`)
- L37 _member_ `} Box;` (scope `FCollisionShape::__anond2d7af05010a`)
- L41 _member_ `float Radius;` (scope `FCollisionShape::__anond2d7af05010a::__anond2d7af050308`)
- L42 _member_ `} Sphere;` (scope `FCollisionShape::__anond2d7af05010a`)
- L46 _member_ `float Radius;` (scope `FCollisionShape::__anond2d7af05010a::__anond2d7af050408`)
- L47 _member_ `float HalfHeight;` (scope `FCollisionShape::__anond2d7af05010a::__anond2d7af050408`)
- L48 _member_ `} Capsule;` (scope `FCollisionShape::__anond2d7af05010a`)

### `Source/Runtime/PhysicsCore/Public/Interface_CollisionDataProviderCore.h` (Public)


#### struct `FTriIndices`  
`struct FTriIndices`  
_L8-20_
- desc: Vertex indices necessary to describe the vertices listed in TriMeshCollisionData
- L10 _public member_ `int32 v0;`
- L11 _public member_ `int32 v1;`
- L12 _public member_ `int32 v2;`
- L14 _public function_ `FTriIndices() : v0(0) , v1(0) , v2(0)`

#### struct `FTriMeshCollisionData`  
`struct FTriMeshCollisionData`  
_L27-64_
- desc: Description of triangle mesh collision data necessary for cooking physics data
- L30 _public member_ `TArray<FVector3f> Vertices;` — Array of vertices included in the triangle mesh
- L33 _public member_ `TArray<FTriIndices> Indices;` — Array of indices defining the ordering of triangles in the mesh
- L36 _public member_ `TArray<uint16> MaterialIndices;` — Array of optional material indices (must equal num triangles)
- L39 _public member_ `TArray< TArray<FVector2D> > UVs;` — Optional UV co-ordinates (each array must be zero of equal num vertices)
- L42 _public member_ `uint32 bFlipNormals : 1;` — Does the mesh require its normals flipped (see PxMeshFlag)
- L45 _public member_ `uint32 bDeformableMesh : 1;` — If mesh is deformable, we don't clean it, so that vertex layout does not change and it can be updated
- L48 _public member_ `uint32 bFastCook : 1;` — Prioritize cooking speed over runtime speed
- L51 _public member_ `uint32 bDisableActiveEdgePrecompute : 1;` — Turn off ActiveEdgePrecompute (This makes cooking faster, but will slow contact generation)
- L54 _public member_ `uint32 bReducedMemoryRepresentation : 1;` — Use a reduced memory representation for the triangle mesh data, which may have additional query cost
- L56 _public function_ `FTriMeshCollisionData() : bFlipNormals(false) , bDeformableMesh(false) , bFastCook(false) , bDisableActiveEdgePrecompute(false) , bReducedMemoryRepresentation(false)`

#### struct `FTriMeshCollisionDataEstimates`  
`struct FTriMeshCollisionDataEstimates`  
_L71-74_
- desc: Estimates of triangle mesh collision data necessary for cooking physics data
- L73 _public member_ `int64 VerticeCount = 0;`

#### Free symbols / members of external scopes

- L23 _prototype_ `void operator<<(class FArchive& Ar, FTriIndices& TriIndices);`
- L67 _prototype_ `void operator<<(class FArchive& Ar, FTriMeshCollisionData& TriMeshCollisionData);`

### `Source/Runtime/PhysicsCore/Public/PhysDerivedDataPublic.h` (Public)


#### Free symbols / members of external scopes

- L5 _macro_ `#define PHYSX_DDC TEXT("A08609EF508D460CBB6710540B03AACF");`

### `Source/Runtime/PhysicsCore/Public/PhysTestSerializer.h` (Public)


#### class `FPhysTestSerializer`  
`class FPhysTestSerializer`  
_L36-140_
- L39 _public prototype_ `FPhysTestSerializer();`
- L40 _public prototype_ `FPhysTestSerializer(const FPhysTestSerializer& Other) = delete;`
- L41 _public prototype_ `FPhysTestSerializer(FPhysTestSerializer&& Other) = delete;`
- L42 _public prototype_ `FPhysTestSerializer& operator=(const FPhysTestSerializer&) = delete;`
- L43 _public prototype_ `FPhysTestSerializer& operator=(FPhysTestSerializer&&) = delete;`
- L46 _public prototype_ `void Serialize(Chaos::FChaosArchive& Ar);` — `UE_DEPRECATED(5.8, "Use the Serializer that takes an FArchive")`
- L47 _public prototype_ `void Serialize(FArchive& Ar);`
- L48 _public prototype_ `void Serialize(const TCHAR* FilePrefix);`
- L51 _public prototype_ `void SetPhysicsData(Chaos::FPBDRigidsEvolution& ChaosEvolution);` — Set the data from an external source. This will obliterate any existing data. Make sure you are not holding on to old internal data as it will go away
- L53 _public function_ `const Chaos::FChaosArchiveContext* GetChaosContext() const`
- L61 _public function_ `FSQCapture& CaptureSQ()` — `UE_DEPRECATED(5.8, "FSQCapture is unused and will be removed")`
- L69 _public function_ `const FSQCapture* GetSQCapture()` — `UE_DEPRECATED(5.8, "FSQCapture is unused and will be removed")`
- L84 _public function_ `Chaos::FPBDRigidsEvolution* GetChaosData()`
- L119 _private member_ `TArray<uint8> Data;` — how the data is stored before going to disk
- L120 _private member_ `bool bDiskDataIsChaos;`
- L121 _private member_ `bool bChaosDataReady;`
- L127 _private member_ `TUniquePtr<FSQCapture> SQCapture;` — `UE_DEPRECATED(5.8, "FSQCapture is unused and will be removed")`
- L131 _private member_ `TUniquePtr<Chaos::FPBDRigidsEvolution> ChaosEvolution;`
- L132 _private member_ `Chaos::FParticleUniqueIndicesMultithreaded UniqueIndices;`
- L133 _private member_ `Chaos::FPBDRigidsSOAs Particles;`
- L134 _private member_ `Chaos::THandleArray<Chaos::FChaosPhysicsMaterial> PhysicalMaterials;`
- L135 _private member_ `TArray <TUniquePtr<Chaos::FGeometryParticle>> GTParticles;`
- L137 _private member_ `TSharedRef<Chaos::FChaosArchiveContext> ChaosContext;`
- L139 _private member_ `FCustomVersionContainer ArchiveVersion;`

#### class `FPhysTestSerializer::FArchiveWithExternalContext`  
`class FArchiveWithExternalContext : public Chaos::FChaosArchive`  
_L105-117_
- inherits: `Chaos::FChaosArchive`
- L108 _public function_ `FArchiveWithExternalContext(FArchive& ArIn) : FChaosArchive(ArIn)`
- L113 _public function_ `explicit FArchiveWithExternalContext(FArchive& ArIn, const TSharedRef<Chaos::FChaosArchiveContext>& InExternalSharedContext) : FChaosArchive(ArIn, InExternalSharedContext)`

#### Free symbols / members of external scopes

- L23 _macro_ `#define PHYS_TEST_SERIALIZER 1`
- L30 _namespace_ `namespace Chaos`

### `Source/Runtime/PhysicsCore/Public/PhysXIncludes.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/PhysicsCore/Public/PhysXInterfaceWrapperCore.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/PhysicsCore/Public/PhysXPublicCore.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/PhysicsCore/Public/PhysXSupportCore.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/PhysicsCore/Public/PhysXToChaosUtil.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/PhysicsCore/Public/PhysicalMaterials/PhysicalMaterial.h` (Public)


#### struct `FPhysicalMaterialStrength`  
`struct FPhysicalMaterialStrength`  
_L32-58_
- reflection: `USTRUCT(BlueprintType)`
- desc: Defines the directional strengths of a physical material in term of force per surface area
- L36 _public prototype_ `FPhysicalMaterialStrength();`
- L43 _public member_ `float TensileStrength;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PhysicalMaterial|Strength", meta = (ClampMin = 0, ForceUnits = "MPa"))` — Tensile strength of the material in MegaPascal ( 10^6 N/m2 ) This amount of tension force per area the material can withstand before it fractures
- L50 _public member_ `float CompressionStrength;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PhysicalMaterial|Strength", meta = (ClampMin = 0, ForceUnits = "MPa"))` — Compression strength of the material in MegaPascal ( 10^6 N/m2 ) This amount of compression force per area the material can withstand before it fractures, crumbles or buckles
- L57 _public member_ `float ShearStrength;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PhysicalMaterial|Strength", meta = (ClampMin = 0, ForceUnits = "MPa"))` — Shear strength of the material in MegaPascal ( 10^6 N/m2 ) This amount of shear force per area the material can withstand before it fractures

#### struct `FPhysicalMaterialDamageModifier`  
`struct FPhysicalMaterialDamageModifier`  
_L65-78_
- reflection: `USTRUCT(BlueprintType)`
- desc: Damage threshold modifiers, used by the Chaos destruction system
- L69 _public prototype_ `FPhysicalMaterialDamageModifier();`
- L77 _public member_ `float DamageThresholdMultiplier;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PhysicalMaterial|DamageModifier", meta = (ClampMin = 0))` — Multiplier for the geometry collection damage thresholds/ internal strain this allows for setting up unit damage threshold and use the material to scale them to the desired range of values Note that the geometry collection asset needs to opt-in for the material modifer to be able to use it

#### enum `EPhysicalMaterialSoftCollisionMode`  
`enum class EPhysicalMaterialSoftCollisionMode : uint8`  
_L86-96_
- reflection: `UENUM()`
- desc: Soft collision mode for a physical material. NOTE: Must match EChaosPhysicsMaterialSoftCollisionMode
- L89 _public enumerator_ `None` — No soft collisionss
- L92 _public enumerator_ `RelativeThickness` — SoftCollisionThickess is a fraction of the bounds (minimum axis). Should be less than 0.5
- L95 _public enumerator_ `AbsoluteThickess` — SoftCollisionThickess is an absolute value in cm

#### class `UPhysicalMaterial`  
`class UPhysicalMaterial : public UObject`  
_L103-247_
- reflection: `UCLASS(BlueprintType, Blueprintable, CollapseCategories, HideCategories = Object, MinimalAPI)`
- inherits: `UObject`
- desc: Physical materials are used to define the response of a physical object when interacting dynamically with the world.
- L107 _private prototype_ `virtual ~UPhysicalMaterial();`
- L108 _private prototype_ `UPhysicalMaterial(FVTableHelper& Helper);`
- L115 _private member_ `float Friction;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=PhysicalMaterial, meta=(ClampMin=0))` — Friction value of surface, controls how easily things can slide on this surface (0 is frictionless, higher values increase the amount of friction)
- L119 _private member_ `float StaticFriction;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PhysicalMaterial, meta = (ClampMin = 0))` — Static Friction value of surface, controls how easily things can slide on this surface (0 is frictionless, higher values increase the amount of friction)
- L123 _private member_ `TEnumAsByte<EFrictionCombineMode::Type> FrictionCombineMode;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PhysicalMaterial, meta = (editcondition = "bOverrideFrictionCombineMode"))` — Friction combine mode, controls how friction is computed for multiple materials.
- L127 _private member_ `bool bOverrideFrictionCombineMode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicalMaterial)` — If set we will use the FrictionCombineMode of this material, instead of the FrictionCombineMode found in the project settings.
- L131 _private member_ `float Restitution;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PhysicalMaterial, meta=(ClampMin=0, ClampMax=1))` — Restitution or 'bounciness' of this surface, between 0 (no bounce) and 1 (outgoing velocity is same as incoming).
- L135 _private member_ `TEnumAsByte<EFrictionCombineMode::Type> RestitutionCombineMode;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PhysicalMaterial, meta = (editcondition = "bOverrideRestitutionCombineMode"))` — Restitution combine mode, controls how restitution is computed for multiple materials.
- L139 _private member_ `bool bOverrideRestitutionCombineMode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhysicalMaterial)` — If set we will use the RestitutionCombineMode of this material, instead of the RestitutionCombineMode found in the project settings.
- L147 _private member_ `float Density;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PhysicalMaterial, meta = (ClampMin = 0, ForceUnits = "g/cm3"))` — Used with the shape of the object to calculate its mass properties. The higher the number, the heavier the object. g per cubic cm.
- L151 _private member_ `float SleepLinearVelocityThreshold;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PhysicalMaterial, meta = (ClampMin = 0))` — How low the linear velocity can be before solver puts body to sleep.
- L155 _private member_ `float SleepAngularVelocityThreshold;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PhysicalMaterial, meta = (ClampMin = 0))` — How low the angular velocity can be before solver puts body to sleep.
- L159 _private member_ `int32 SleepCounterThreshold;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PhysicalMaterial, meta = (ClampMin = 0))` — How many ticks we can be under thresholds for before solver puts body to sleep.
- L167 _private member_ `float RaiseMassToPower;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Advanced, meta=(ClampMin=0.1, ClampMax=1))` — Used to adjust the way that mass increases as objects get larger. This is applied to the mass as calculated based on a 'solid' object. In actuality, larger objects do not tend to be solid, and become more like 'shells' (e.g. a car is not a solid piece of metal). Values are clamped to 1 or less.
- L172 _private member_ `float DestructibleDamageThresholdScale_DEPRECATED;` — `UE_DEPRECATED(5.3, "This property is not used anywhere, use Geometry Collection damage threshold related features instead")` — `UPROPERTY()` — How much to scale the damage threshold by on any destructible we are applied to
- L175 _private member_ `TObjectPtr<class UDEPRECATED_PhysicalMaterialPropertyBase> PhysicalMaterialProperty_DEPRECATED;` — `UPROPERTY()`
- L181 _private member_ `TEnumAsByte<EPhysicalSurface> SurfaceType;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PhysicalProperties)` — To edit surface type for your project, use ProjectSettings/Physics/PhysicalSurface section
- L184 _private member_ `FPhysicalMaterialStrength Strength;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PhysicalProperties)`
- L187 _private member_ `FPhysicalMaterialDamageModifier DamageModifier;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PhysicalProperties)`
- L191 _private member_ `FLinearColor DebugColor;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Debugging", AdvancedDisplay)` — Color used to represent this material in certain debug views (e.g. landscape collision)
- L200 _private member_ `bool bShowExperimentalProperties = PhysicalMaterialCVars::bShowExperimentalProperties;` — `UPROPERTY(VisibleAnywhere, Transient, Category = "Experimental")` — Experimental material properties are enabled via the p.PhysicalMaterial.ShowExperimentalProperties console variable. NOTE: These are _experimental_ properties which may change. Use at your own risk!
- L204 _private member_ `EPhysicalMaterialSoftCollisionMode SoftCollisionMode;` — `UPROPERTY(EditAnywhere, Category = "Experimental|Softness", meta = (EditCondition = "bShowExperimentalProperties"))` — For enable soft collision shell thickness mode
- L209 _private member_ `float SoftCollisionThickness;` — `UPROPERTY(EditAnywhere, Category = "Experimental|Softness", meta = (ClampMin = 0, EditCondition = "bShowExperimentalProperties"))` — Thickness of the layer just inside the collision shape in which contact is considered "soft". The units depend on SoftCollisionMode
- L215 _private member_ `float BaseFrictionImpulse;` — `UPROPERTY(EditAnywhere, Category = "Experimental|Stickiness", meta = (ClampMin = 0, Units = kgcm, EditCondition = "bShowExperimentalProperties"))` — A friction (positional) impulse of at least this magnitude may be applied, regardless the normal force. This is analogous to adding only the lateral part of a "stickiness" to a material
- L219 _public member_ `TUniquePtr<FPhysicsMaterialHandle> MaterialHandle;`
- L221 _public member_ `FChaosUserData UserData;`
- L225 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L226 _public prototype_ `static void RebuildPhysicalMaterials();`
- L228 _public prototype_ `virtual void PostLoad() override;`
- L229 _public prototype_ `virtual void FinishDestroy() override;`
- L232 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L235 _public prototype_ `FPhysicsMaterialHandle& GetPhysicsMaterial();` — Get the physics-interface derived version of this material
- L237 _public prototype_ `static void SetEngineDefaultPhysMaterial(UPhysicalMaterial* Material);`
- L239 _public prototype_ `static void SetEngineDefaultDestructiblePhysMaterial(UPhysicalMaterial* Material);`
- L242 _public prototype_ `static EPhysicalSurface DetermineSurfaceType(UPhysicalMaterial const* PhysicalMaterial);` — Determine Material Type from input PhysicalMaterial
- L246 _private prototype_ `void EnsurePhysicsMaterialCreated();`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace PhysicalMaterialCVars`
- L24 _externvar_ `extern bool bShowExperimentalProperties;` (scope `PhysicalMaterialCVars`)

### `Source/Runtime/PhysicsCore/Public/PhysicalMaterials/PhysicalMaterialPropertyBase.h` (Public)


#### class `UDEPRECATED_PhysicalMaterialPropertyBase`  
`class UDEPRECATED_PhysicalMaterialPropertyBase : public UObject`  
_L32-51_
- reflection: `UCLASS(collapsecategories, hidecategories=Object, editinlinenew, abstract,MinimalAPI, deprecated)`
- inherits: `UObject`
- L37 _private function_ `virtual bool IsAsset() const override`
- L41 _private function_ `virtual EPhysicalSurface ConvertToSurfaceType()` — compatibility support function
- L45 _protected function_ `EPhysicalSurface GetSurfaceType(int32 Value)` — set material type from int

### `Source/Runtime/PhysicsCore/Public/PhysicsCore.h` (Public)


#### Free symbols / members of external scopes

- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPhysicsCore, Warning, All);`

### `Source/Runtime/PhysicsCore/Public/PhysicsCoreModule.h` (Public)


#### class `IPhysicsCoreModule`  
`class IPhysicsCoreModule : public IModuleInterface`  
_L11-14_
- inherits: `IModuleInterface`
- desc: Physics Core module interface

### `Source/Runtime/PhysicsCore/Public/PhysicsInitialization.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace PhysDLLHelper`
- L13 _prototype_ `bool LoadPhysXModules(bool bLoadCooking);` (scope `PhysDLLHelper`) — Load the required modules for PhysX
- L18 _prototype_ `void UnloadPhysXModules();` (scope `PhysDLLHelper`) — Unload the required modules for PhysX
- L21 _prototype_ `bool InitGamePhysCore();`
- L22 _prototype_ `void TermGamePhysCore();`

### `Source/Runtime/PhysicsCore/Public/PhysicsInterfaceDeclaresCore.h` (Public)


#### Free symbols / members of external scopes

- L5 _macro_ `#define MAX_PHYSICS_FIELD_TARGETS 32`
- L11 _namespace_ `namespace Chaos`
- L19 _typedef_ `using FGeometryParticle = TGeometryParticle<FReal, 3>;` (scope `Chaos`)
- L39 _namespace_ `namespace ChaosInterface`
- L46 _typedef_ `using FPhysTypeDummy = ChaosInterface::FDummyPhysType;`
- L47 _typedef_ `using FPhysActorDummy = ChaosInterface::FDummyPhysActor;`
- L50 _typedef_ `template<typename T> using FCallbackDummy = ChaosInterface::FDummyCallback<T>;`
- L52 _typedef_ `using FHitLocation = ChaosInterface::FLocationHit;`
- L53 _typedef_ `using FHitSweep = ChaosInterface::FSweepHit;`
- L54 _typedef_ `using FHitRaycast = ChaosInterface::FRaycastHit;`
- L55 _typedef_ `using FHitOverlap = ChaosInterface::FOverlapHit;`
- L56 _typedef_ `using FPhysicsQueryHit = ChaosInterface::FQueryHit;`
- L58 _typedef_ `using FPhysicsTransform = FTransform;`
- L60 _typedef_ `using FPhysicsShape = Chaos::FPerShapeData;`
- L61 _typedef_ `using FPhysicsGeometry = Chaos::FImplicitObject;`
- L62 _typedef_ `using FPhysicsCapsuleGeometry = Chaos::FCapsule;`
- L63 _typedef_ `using FPhysicsMaterial = Chaos::FChaosPhysicsMaterial;`
- L64 _typedef_ `using FPhysicsMaterialMask = Chaos::FChaosPhysicsMaterialMask;`
- L65 _typedef_ `using FPhysicsActor = Chaos::FGeometryParticle;`
- L68 _typedef_ `template <typename T> using FPhysicsHitCallback = ChaosInterface::FSQHitBuffer<T>;`
- L71 _typedef_ `template <typename T> using FSingleHitBuffer = ChaosInterface::FSQSingleHitBuffer<T>;`
- L74 _typedef_ `template <typename T> using FDynamicHitBuffer = ChaosInterface::FSQHitBuffer<T>;`
- L76 _typedef_ `using FPhysicsActorHandle = Chaos::FSingleParticlePhysicsProxy*;`
- L88 _typedef_ `typedef FPhysicsConstraintReference_Chaos FPhysicsConstraintHandle;`
- L89 _typedef_ `typedef FPhysInterface_Chaos FPhysicsInterface;`
- L90 _typedef_ `typedef FPhysScene_Chaos FPhysScene;`
- L91 _typedef_ `typedef FPhysicsAggregateReference_Chaos FPhysicsAggregateHandle;`
- L92 _typedef_ `typedef FPhysInterface_Chaos FPhysicsCommand;`
- L93 _typedef_ `typedef FPhysicsShapeReference_Chaos FPhysicsShapeHandle;`
- L94 _typedef_ `typedef FPhysicsGeometryCollection_Chaos FPhysicsGeometryCollection;`
- L95 _typedef_ `typedef Chaos::FMaterialHandle FPhysicsMaterialHandle;`
- L96 _typedef_ `typedef Chaos::FMaterialMaskHandle FPhysicsMaterialMaskHandle;`
- L97 _typedef_ `typedef FPhysicsShapeAdapter_Chaos FPhysicsShapeAdapter;`
- L98 _typedef_ `typedef FPhysicsUserData_Chaos FPhysicsUserData;`
- L100 _function_ `inline FPhysicsActorHandle DefaultPhysicsActorHandle()`

### `Source/Runtime/PhysicsCore/Public/PhysicsInterfaceTypesCore.h` (Public)


#### struct `FActorCreationParams`  
`struct FActorCreationParams`  
_L13-35_
- L15 _public function_ `FActorCreationParams() : Scene(nullptr) , InitialTM(FTransform::Identity) , bStatic(false) , bQueryOnly(false) , bEnableGravity(false) , bUpdateKinematicFromSimulation(false) , bSimulatePhysics(false) , bStartAwake(true) , DebugName(nullptr)`
- L26 _public member_ `FChaosScene* Scene;`
- L27 _public member_ `FTransform InitialTM;`
- L28 _public member_ `bool bStatic;`
- L29 _public member_ `bool bQueryOnly;`
- L30 _public member_ `bool bEnableGravity;`
- L31 _public member_ `bool bUpdateKinematicFromSimulation;`
- L32 _public member_ `bool bSimulatePhysics;`
- L33 _public member_ `bool bStartAwake;`
- L34 _public member_ `char* DebugName;`

#### enum `ECollisionQuery`  
`enum class ECollisionQuery : uint8`  
_L42-46_
- desc: Type of query for object type or trace type Trace queries correspond to trace functions with TravelChannel/ResponseParams Object queries correspond to trace functions with Object types
- L44 _public enumerator_ `ObjectQuery = 0`
- L45 _public enumerator_ `TraceQuery = 1`

#### enum `ECollisionShapeType`  
`enum class ECollisionShapeType : uint8`  
_L48-58_
- L50 _public enumerator_ `Sphere`
- L51 _public enumerator_ `Plane`
- L52 _public enumerator_ `Box`
- L53 _public enumerator_ `Capsule`
- L54 _public enumerator_ `Convex`
- L55 _public enumerator_ `Trimesh`
- L56 _public enumerator_ `Heightfield`
- L57 _public enumerator_ `None`

#### struct `FBodyCollisionFilterData`  
`struct FBodyCollisionFilterData`  
_L61-83_
- desc: Helper struct holding physics body filter data during initialisation
- L65 _public prototype_ `FBodyCollisionFilterData() = default;` — These must be explicitly declared to get rid of deprecation warnings.
- L66 _public prototype_ `FBodyCollisionFilterData(const FBodyCollisionFilterData&) = default;`
- L67 _public prototype_ `FBodyCollisionFilterData(FBodyCollisionFilterData&&) = default;`
- L69 _public prototype_ `FBodyCollisionFilterData& operator=(const FBodyCollisionFilterData&) = default;`
- L70 _public prototype_ `FBodyCollisionFilterData& operator=(FBodyCollisionFilterData&&) = default;`
- L74 _public member_ `FCollisionFilterData SimFilter;` — `UE_DEPRECATED(5.8, "Use the FilterInstanceData and Simple/Complex ShapeFilterData objects instead")`
- L76 _public member_ `FCollisionFilterData QuerySimpleFilter;` — `UE_DEPRECATED(5.8, "Use the FilterInstanceData and Simple/Complex ShapeFilterData objects instead")`
- L78 _public member_ `FCollisionFilterData QueryComplexFilter;` — `UE_DEPRECATED(5.8, "Use the FilterInstanceData and Simple/Complex ShapeFilterData objects instead")`
- L80 _public member_ `Chaos::Filter::FInstanceData FilterInstanceData;`
- L81 _public member_ `Chaos::Filter::FShapeFilterData SimpleShapeFilterData;`
- L82 _public member_ `Chaos::Filter::FShapeFilterData ComplexShapeFilterData;`

#### struct `FBodyCollisionFlags`  
`struct FBodyCollisionFlags`  
_L85-99_
- L87 _public function_ `FBodyCollisionFlags() : bEnableSimCollisionSimple(false) , bEnableSimCollisionComplex(false) , bEnableQueryCollision(false) , bEnableProbeCollision(false)`
- L95 _public member_ `bool bEnableSimCollisionSimple;`
- L96 _public member_ `bool bEnableSimCollisionComplex;`
- L97 _public member_ `bool bEnableQueryCollision;`
- L98 _public member_ `bool bEnableProbeCollision;`

#### struct `FBodyCollisionData`  
`struct FBodyCollisionData`  
_L103-107_
- desc: Helper object to hold initialisation data for shapes
- L105 _public member_ `FBodyCollisionFilterData CollisionFilterData;`
- L106 _public member_ `FBodyCollisionFlags CollisionFlags;`

#### enum `EChaosUserDataType::Type`  
`enum Type`  
_L202-214_
- L204 _public enumerator_ `Invalid`
- L205 _public enumerator_ `BodyInstance`
- L206 _public enumerator_ `PhysicalMaterial`
- L207 _public enumerator_ `PhysScene`
- L208 _public enumerator_ `ConstraintInstance`
- L209 _public enumerator_ `PrimitiveComponent`
- L210 _public enumerator_ `AggShape`
- L211 _public enumerator_ `PhysicsObject` — This will replace BodyInstances in the future
- L212 _public enumerator_ `ChaosUserEntity` — This is used for adding custom user entities (unknown to UE)
- L213 _public enumerator_ `CustomPayload` — This is intended for plugins

#### struct `FChaosUserData`  
`struct FChaosUserData`  
_L218-244_
- L221 _protected member_ `EChaosUserDataType::Type Type;`
- L222 _protected member_ `void* Payload;`
- L225 _public function_ `FChaosUserData() :Type(EChaosUserDataType::Invalid), Payload(nullptr)`
- L226 _public function_ `FChaosUserData(FBodyInstance* InPayload) :Type(EChaosUserDataType::BodyInstance), Payload(InPayload)`
- L227 _public function_ `FChaosUserData(UPhysicalMaterial* InPayload) :Type(EChaosUserDataType::PhysicalMaterial), Payload(InPayload)`
- L228 _public function_ `FChaosUserData(FPhysScene* InPayload) :Type(EChaosUserDataType::PhysScene), Payload(InPayload)`
- L229 _public function_ `FChaosUserData(FConstraintInstance* InPayload) :Type(EChaosUserDataType::ConstraintInstance), Payload(InPayload)`
- L230 _public function_ `FChaosUserData(UPrimitiveComponent* InPayload) :Type(EChaosUserDataType::PrimitiveComponent), Payload(InPayload)`
- L231 _public function_ `FChaosUserData(FKShapeElem* InPayload) :Type(EChaosUserDataType::AggShape), Payload(InPayload)`
- L232 _public function_ `FChaosUserData(Chaos::FPhysicsObject* InPayload) :Type(EChaosUserDataType::PhysicsObject), Payload(InPayload)`
- L233 _public function_ `FChaosUserData(FChaosUserEntityAppend* InPayload) :Type(EChaosUserDataType::ChaosUserEntity), Payload(InPayload)`
- L234 _public function_ `FChaosUserData(FCustomChaosPayload* InPayload) :Type(EChaosUserDataType::CustomPayload), Payload(InPayload)`
- L236 _public prototype_ `template <class T> static T* Get(void* UserData);`
- L237 _public prototype_ `template <class T> static T* Get(void* UserData);`
- L240 _public function_ `static bool IsGarbage(void* UserData)` — helper function to determine if userData is garbage (maybe dangling pointer)
- L243 _public function_ `template <EChaosUserDataType::Type UserDataType> bool Is() const`
- L249 _function_ `template <> FORCEINLINE FBodyInstance* FChaosUserData::Get(void* UserData)`
- L253 _function_ `template <> FORCEINLINE UPhysicalMaterial* FChaosUserData::Get(void* UserData)`
- L254 _function_ `template <> FORCEINLINE FPhysScene* FChaosUserData::Get(void* UserData)`
- L255 _function_ `template <> FORCEINLINE FConstraintInstance* FChaosUserData::Get(void* UserData)`
- L256 _function_ `template <> FORCEINLINE UPrimitiveComponent* FChaosUserData::Get(void* UserData)`
- L257 _function_ `template <> FORCEINLINE FKShapeElem* FChaosUserData::Get(void* UserData)`
- L259 _function_ `template <> FORCEINLINE void FChaosUserData::Set(void* UserData, FBodyInstance* Payload)`
- L263 _function_ `template <> FORCEINLINE void FChaosUserData::Set(void* UserData, UPhysicalMaterial* Payload)`
- L264 _function_ `template <> FORCEINLINE void FChaosUserData::Set(void* UserData, FPhysScene* Payload)`
- L265 _function_ `template <> FORCEINLINE void FChaosUserData::Set(void* UserData, FConstraintInstance* Payload)`
- L266 _function_ `template <> FORCEINLINE void FChaosUserData::Set(void* UserData, UPrimitiveComponent* Payload)`
- L267 _function_ `template <> FORCEINLINE void FChaosUserData::Set(void* UserData, FKShapeElem* Payload)`

#### struct `FChaosFilterData`  
`struct UE_DEPRECATED(5.8, "Use Chaos::Filter::FQueryFilterData instead") FChaosFilterData`  
_L269-297_
- L271 _public function_ `FORCEINLINE FChaosFilterData()`
- L276 _public function_ `FORCEINLINE FChaosFilterData(uint32 w0, uint32 w1, uint32 w2, uint32 w3) : word0(w0), word1(w1), word2(w2), word3(w3)`
- L278 _public function_ `FORCEINLINE void Reset()`
- L283 _public function_ `FORCEINLINE bool operator== (const FChaosFilterData& Other) const`
- L288 _public function_ `FORCEINLINE bool operator != (const FChaosFilterData& Other) const`
- L293 _public member_ `uint32 word0;`
- L294 _public member_ `uint32 word1;`
- L295 _public member_ `uint32 word2;`
- L296 _public member_ `uint32 word3;`

#### struct `FChaosQueryFlag`  
`struct FChaosQueryFlag`  
_L299-321_

#### enum `FChaosQueryFlag::Enum`  
`enum Enum`  
_L301-320_
- L303 _public enumerator_ `eSTATIC = (1 << 0)` — Traverse static shapes
- L305 _public enumerator_ `eDYNAMIC = (1 << 1)` — Traverse dynamic shapes
- L307 _public enumerator_ `ePREFILTER = (1 << 2)` — Run the pre-intersection-test filter
- L309 _public enumerator_ `ePOSTFILTER = (1 << 3)` — Run the post-intersection-test filter
- L311 _public enumerator_ `eANY_HIT = (1 << 4)` — Abort traversal as soon as any hit is found and return it via callback.block.
- L314 _public enumerator_ `eNO_BLOCK = (1 << 5)` — All hits are reported as touching. Overrides eBLOCK returned from user filters with eTOUCH.
- L317 _public enumerator_ `eSKIPNARROWPHASE = (1 << 6)` — Skip narrow phase check for the query
- L319 _public enumerator_ `eRESERVED = (1 << 15)` — Reserved for internal use

#### class `ChaosFlags`  
`template <typename enumtype, typename storagetype = uint32_t> class ChaosFlags`  
_L324-379_
- L327 _public typedef_ `typedef storagetype InternalType;`
- L329 _public prototype_ `FORCEINLINE ChaosFlags(void);`
- L330 _public prototype_ `FORCEINLINE ChaosFlags(enumtype e);`
- L331 _public prototype_ `FORCEINLINE ChaosFlags(const ChaosFlags<enumtype, storagetype>& f);`
- L332 _public prototype_ `FORCEINLINE explicit ChaosFlags(storagetype b);`
- L334 _public prototype_ `FORCEINLINE bool isSet(enumtype e) const;`
- L335 _public prototype_ `FORCEINLINE ChaosFlags<enumtype, storagetype>& set(enumtype e);`
- L336 _public prototype_ `FORCEINLINE bool operator==(enumtype e) const;`
- L337 _public prototype_ `FORCEINLINE bool operator==(const ChaosFlags<enumtype, storagetype>& f) const;`
- L338 _public prototype_ `FORCEINLINE bool operator==(bool b) const;`
- L339 _public prototype_ `FORCEINLINE bool operator!=(enumtype e) const;`
- L340 _public prototype_ `FORCEINLINE bool operator!=(const ChaosFlags<enumtype, storagetype>& f) const;`
- L342 _public prototype_ `FORCEINLINE ChaosFlags<enumtype, storagetype>& operator=(const ChaosFlags<enumtype, storagetype>& f);`
- L343 _public prototype_ `FORCEINLINE ChaosFlags<enumtype, storagetype>& operator=(enumtype e);`
- L345 _public prototype_ `FORCEINLINE ChaosFlags<enumtype, storagetype>& operator|=(enumtype e);`
- L346 _public prototype_ `FORCEINLINE ChaosFlags<enumtype, storagetype>& operator|=(const ChaosFlags<enumtype, storagetype>& f);`
- L347 _public prototype_ `FORCEINLINE ChaosFlags<enumtype, storagetype> operator|(enumtype e) const;`
- L348 _public prototype_ `FORCEINLINE ChaosFlags<enumtype, storagetype> operator|(const ChaosFlags<enumtype, storagetype>& f) const;`
- L350 _public prototype_ `FORCEINLINE ChaosFlags<enumtype, storagetype>& operator&=(enumtype e);`
- L351 _public prototype_ `FORCEINLINE ChaosFlags<enumtype, storagetype>& operator&=(const ChaosFlags<enumtype, storagetype>& f);`
- L352 _public prototype_ `FORCEINLINE ChaosFlags<enumtype, storagetype> operator&(enumtype e) const;`
- L353 _public prototype_ `FORCEINLINE ChaosFlags<enumtype, storagetype> operator&(const ChaosFlags<enumtype, storagetype>& f) const;`
- L355 _public prototype_ `FORCEINLINE ChaosFlags<enumtype, storagetype>& operator^=(enumtype e);`
- L356 _public prototype_ `FORCEINLINE ChaosFlags<enumtype, storagetype>& operator^=(const ChaosFlags<enumtype, storagetype>& f);`
- L357 _public prototype_ `FORCEINLINE ChaosFlags<enumtype, storagetype> operator^(enumtype e) const;`
- L358 _public prototype_ `FORCEINLINE ChaosFlags<enumtype, storagetype> operator^(const ChaosFlags<enumtype, storagetype>& f) const;`
- L360 _public prototype_ `FORCEINLINE ChaosFlags<enumtype, storagetype> operator~(void) const;`
- L362 _public prototype_ `FORCEINLINE operator bool(void) const;`
- L363 _public prototype_ `FORCEINLINE operator uint8_t(void) const;`
- L364 _public prototype_ `FORCEINLINE operator uint16_t(void) const;`
- L365 _public prototype_ `FORCEINLINE operator uint32_t(void) const;`
- L367 _public prototype_ `FORCEINLINE void clear(enumtype e);`
- L378 _private member_ `storagetype mBits;`
- L425 _function_ `template <typename enumtype, typename storagetype> FORCEINLINE ChaosFlags<enumtype, storagetype>::ChaosFlags(void)`
- L431 _function_ `template <typename enumtype, typename storagetype> FORCEINLINE ChaosFlags<enumtype, storagetype>::ChaosFlags(enumtype e)`
- L437 _function_ `template <typename enumtype, typename storagetype> FORCEINLINE ChaosFlags<enumtype, storagetype>::ChaosFlags(const ChaosFlags<enumtype, storagetype>& f)`
- L443 _function_ `template <typename enumtype, typename storagetype> FORCEINLINE ChaosFlags<enumtype, storagetype>::ChaosFlags(storagetype b)`
- L449 _function_ `template <typename enumtype, typename storagetype> FORCEINLINE bool ChaosFlags<enumtype, storagetype>::isSet(enumtype e) const`
- L455 _function_ `template <typename enumtype, typename storagetype> FORCEINLINE ChaosFlags<enumtype, storagetype>& ChaosFlags<enumtype, storagetype>::set(enumtype e)`
- L462 _function_ `template <typename enumtype, typename storagetype> FORCEINLINE bool ChaosFlags<enumtype, storagetype>::operator==(enumtype e) const`
- L468 _function_ `template <typename enumtype, typename storagetype> FORCEINLINE bool ChaosFlags<enumtype, storagetype>::operator==(const ChaosFlags<enumtype, storagetype>& f) const`
- L474 _function_ `template <typename enumtype, typename storagetype> FORCEINLINE bool ChaosFlags<enumtype, storagetype>::operator==(bool b) const`
- L480 _function_ `template <typename enumtype, typename storagetype> FORCEINLINE bool ChaosFlags<enumtype, storagetype>::operator!=(enumtype e) const`
- L486 _function_ `template <typename enumtype, typename storagetype> FORCEINLINE bool ChaosFlags<enumtype, storagetype>::operator!=(const ChaosFlags<enumtype, storagetype>& f) const`
- L492 _function_ `template <typename enumtype, typename storagetype> FORCEINLINE ChaosFlags<enumtype, storagetype>& ChaosFlags<enumtype, storagetype>::operator=(enumtype e)`
- L499 _function_ `template <typename enumtype, typename storagetype> FORCEINLINE ChaosFlags<enumtype, storagetype>& ChaosFlags<enumtype, storagetype>::operator=(const ChaosFlags<enumtype, storagetype>& f)`
- L506 _function_ `template <typename enumtype, typename storagetype> FORCEINLINE ChaosFlags<enumtype, storagetype>& ChaosFlags<enumtype, storagetype>::operator|=(enumtype e)`
- L514 _function_ `operator|=(const ChaosFlags<enumtype, storagetype>& f)`
- L521 _function_ `template <typename enumtype, typename storagetype> FORCEINLINE ChaosFlags<enumtype, storagetype> ChaosFlags<enumtype, storagetype>::operator|(enumtype e) const`
- L530 _function_ `operator|(const ChaosFlags<enumtype, storagetype>& f) const`
- L538 _function_ `template <typename enumtype, typename storagetype> FORCEINLINE ChaosFlags<enumtype, storagetype>& ChaosFlags<enumtype, storagetype>::operator&=(enumtype e)`
- L546 _function_ `operator&=(const ChaosFlags<enumtype, storagetype>& f)`
- L553 _function_ `template <typename enumtype, typename storagetype> FORCEINLINE ChaosFlags<enumtype, storagetype> ChaosFlags<enumtype, storagetype>::operator&(enumtype e) const`
- L562 _function_ `operator&(const ChaosFlags<enumtype, storagetype>& f) const`
- L570 _function_ `template <typename enumtype, typename storagetype> FORCEINLINE ChaosFlags<enumtype, storagetype>& ChaosFlags<enumtype, storagetype>::operator^=(enumtype e)`
- L578 _function_ `operator^=(const ChaosFlags<enumtype, storagetype>& f)`
- L585 _function_ `template <typename enumtype, typename storagetype> FORCEINLINE ChaosFlags<enumtype, storagetype> ChaosFlags<enumtype, storagetype>::operator^(enumtype e) const`
- L594 _function_ `operator^(const ChaosFlags<enumtype, storagetype>& f) const`
- L602 _function_ `template <typename enumtype, typename storagetype> FORCEINLINE ChaosFlags<enumtype, storagetype> ChaosFlags<enumtype, storagetype>::operator~(void) const`
- L610 _function_ `template <typename enumtype, typename storagetype> FORCEINLINE ChaosFlags<enumtype, storagetype>::operator bool(void) const`
- L616 _function_ `template <typename enumtype, typename storagetype> FORCEINLINE ChaosFlags<enumtype, storagetype>::operator uint8_t(void) const`
- L622 _function_ `template <typename enumtype, typename storagetype> FORCEINLINE ChaosFlags<enumtype, storagetype>::operator uint16_t(void) const`
- L628 _function_ `template <typename enumtype, typename storagetype> FORCEINLINE ChaosFlags<enumtype, storagetype>::operator uint32_t(void) const`
- L634 _function_ `template <typename enumtype, typename storagetype> FORCEINLINE void ChaosFlags<enumtype, storagetype>::clear(enumtype e)`

#### struct `FChaosQueryFilterData`  
`struct UE_DEPRECATED(5.8, "Use ChaosInterface::FSceneQueryCommonParams instead.") FChaosQueryFilterData`  
_L410-421_
- L412 _public function_ `explicit FORCEINLINE FChaosQueryFilterData() : flags(FChaosQueryFlag::eDYNAMIC | FChaosQueryFlag::eSTATIC), clientId(0)`
- L414 _public function_ `explicit FORCEINLINE FChaosQueryFilterData(const FChaosFilterData& fd, FChaosQueryFlags f) : data(fd), flags(f), clientId(0)`
- L416 _public function_ `explicit FORCEINLINE FChaosQueryFilterData(FChaosQueryFlags f) : flags(f), clientId(0)`
- L418 _public member_ `FChaosFilterData data;`
- L419 _public member_ `FChaosQueryFlags flags;`
- L420 _public member_ `uint8 clientId;`

#### Free symbols / members of external scopes

- L109 _function_ `inline void SetupNonUniformHelper(FVector InScale3D, double& OutMinScale, double& OutMinScaleAbs, FVector& OutScale3DAbs)`
- L132 _function_ `inline void SetupNonUniformHelper(FVector InScale3D, float& OutMinScale, float& OutMinScaleAbs, FVector& OutScale3DAbs)`
- L142 _function_ `inline bool CalcMeshNegScaleCompensation(const FVector& InScale3D, FTransform& OutTransform)` — Util to determine whether to use NegX version of mesh, and what transform (rotation) to apply.
- L183 _variable_ `inline constexpr uint32 AggregateMaxSize = 128;`
- L195 _namespace_ `namespace Chaos`
- L200 _namespace_ `namespace EChaosUserDataType`
- L246 _typedef_ `using FUserData = FChaosUserData;`
- L247 _typedef_ `using FPhysicsQueryFlag = FChaosQueryFlag;`
- L370 _function_ `friend FORCEINLINE ChaosFlags<enumtype, storagetype> operator&(enumtype a, ChaosFlags<enumtype, storagetype>& b)`
- L381 _typedef_ `typedef ChaosFlags<FChaosQueryFlag::Enum, uint16> FChaosQueryFlags;`
- L383 _function_ `inline FChaosQueryFlags U2CQueryFlags(FQueryFlags Flags)`

### `Source/Runtime/PhysicsCore/Public/PhysicsInterfaceUtilsCore.h` (Public)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace ChaosInterface`
- L13 _prototype_ `UE_INTERNAL FCollisionFilterData C2UFilterData(const FChaosFilterData& FilterData);`
- L14 _prototype_ `UE_INTERNAL FChaosFilterData U2CFilterData(const FCollisionFilterData& FilterData);`
- L16 _prototype_ `UE_INTERNAL FCollisionFilterData ToUnrealFilterData(const FChaosFilterData& FilterData);`
- L21 _prototype_ `uint32 FindFaceIndex(const FHitLocation& PHit, const FVector& UnitDirection);`
- L22 _prototype_ `uint32 FindFaceIndex(const ChaosInterface::FPTLocationHit& PHit, const FVector& UnitDirection);`

### `Source/Runtime/PhysicsCore/Public/PhysicsInterfaceWrapperShared.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/PhysicsCore/Public/PhysicsObjectPhysicsCoreInterface.h` (Public)


#### class `PhysicsObjectPhysicsCoreInterface`  
`class PhysicsObjectPhysicsCoreInterface`  
_L10-15_
- L13 _public prototype_ `static FChaosScene* GetScene(TArrayView<const Chaos::FConstPhysicsObjectHandle> InObjects);`
- L14 _public prototype_ `static FChaosScene* GetScene(const Chaos::FConstPhysicsObjectHandle InObject);`

### `Source/Runtime/PhysicsCore/Public/PhysicsPublicCore.h` (Public)


#### class `FPhysicsDelegatesCore`  
`class FPhysicsDelegatesCore`  
_L10-15_
- desc: Set of delegates to allowing hooking different parts of the physics engine
- L13 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnUpdatePhysXMaterial, UPhysicalMaterial*);`
- L14 _public member_ `static FOnUpdatePhysXMaterial OnUpdatePhysXMaterial;`

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnUpdatePhysXMaterial, UPhysicalMaterial*);`

### `Source/Runtime/PhysicsCore/Public/PhysicsSQ.h` (Public)


#### class `IPhysicsSQModule`  
`class IPhysicsSQModule : public IModuleInterface`  
_L11-14_
- inherits: `IModuleInterface`
- desc: Physics SQ module interface

### `Source/Runtime/PhysicsCore/Public/PhysicsSettingsCore.h` (Public)


#### class `UPhysicsSettingsCore`  
`class UPhysicsSettingsCore: public UDeveloperSettings`  
_L19-136_
- reflection: `UCLASS(config=Engine,defaultconfig,meta=(DisplayName="Physics"), MinimalAPI)`
- inherits: `UDeveloperSettings`
- desc: Default physics settings.
- L25 _private member_ `float DefaultGravityZ;` — `UPROPERTY(config,EditAnywhere,Category = Constants)` — Default gravity.
- L29 _private member_ `float DefaultTerminalVelocity;` — `UPROPERTY(config,EditAnywhere,Category = Constants)` — Default terminal velocity for Physics Volumes.
- L33 _private member_ `float DefaultFluidFriction;` — `UPROPERTY(config,EditAnywhere,Category = Constants)` — Default fluid friction for Physics Volumes.
- L37 _private member_ `int32 SimulateScratchMemorySize;` — `UPROPERTY(config,EditAnywhere,Category = Constants,meta = (ClampMin = "0",UIMin = "0"))` — Amount of memory to reserve for PhysX simulate(), this is per pxscene and will be rounded up to the next 16K boundary
- L41 _private member_ `int32 RagdollAggregateThreshold;` — `UPROPERTY(config,EditAnywhere,meta = (ClampMin = "1",UIMin = "1",ClampMax = "127",UIMax = "127"),Category = Constants)` — Threshold for ragdoll bodies above which they will be added to an aggregate before being added to the scene
- L45 _private member_ `float TriangleMeshTriangleMinAreaThreshold;` — `UPROPERTY(config,EditAnywhere,AdvancedDisplay,meta = (ClampMin = "-1.0",UIMin = "-1.0",ClampMax = "10.0",UIMax = "10.0"),Category = Constants)` — Triangles from triangle meshes (BSP) with an area less than or equal to this value will be removed from physics collision data. Set to less than 0 to disable.
- L49 _private member_ `bool bEnableEnhancedDeterminism;` — `UPROPERTY(config,EditAnywhere,Category = Simulation)` — If set to true, the scene will use enhanced determinism at the cost of a bit more resources. See eENABLE_ENHANCED_DETERMINISM to learn about the specifics
- L53 _private member_ `bool bEnableShapeSharing;` — `UPROPERTY(config,EditAnywhere,AdvancedDisplay,Category = Simulation)` — Enables shape sharing between sync and async scene for static rigid actors
- L57 _private member_ `bool bEnablePCM;` — `UPROPERTY(config,EditAnywhere,AdvancedDisplay,Category = Simulation)` — Enables persistent contact manifolds. This will generate fewer contact points, but with more accuracy. Reduces stability of stacking, but can help energy conservation.
- L61 _private member_ `bool bEnableStabilization;` — `UPROPERTY(config,EditAnywhere,AdvancedDisplay,Category = Simulation)` — Enables stabilization of contacts for slow moving bodies. This will help improve the stability of stacking.
- L65 _private member_ `bool bWarnMissingLocks;` — `UPROPERTY(config,EditAnywhere,AdvancedDisplay,Category = Simulation)` — Whether to warn when physics locks are used incorrectly. Turning this off is not recommended and should only be used by very advanced users.
- L69 _private member_ `bool bEnable2DPhysics;` — `UPROPERTY(config,EditAnywhere,Category = Simulation)` — Can 2D physics be used (Box2D)?
- L74 _private member_ `bool bDefaultHasComplexCollision_DEPRECATED;` — `UPROPERTY(config)` — If true, static meshes will use per poly collision as complex collision by default. If false the default behavior is the same as UseSimpleAsComplex.
- L79 _private member_ `float BounceThresholdVelocity;` — `UPROPERTY(config, EditAnywhere, Category = Simulation, meta = (ClampMin = "0", UIMin = "0"))` — Minimum relative velocity required for an object to bounce. A typical value for simulation stability is about 0.2 * gravity
- L83 _private member_ `TEnumAsByte<EFrictionCombineMode::Type> FrictionCombineMode;` — `UPROPERTY(config, EditAnywhere, Category=Simulation)` — Friction combine mode, controls how friction is computed for multiple materials.
- L87 _private member_ `TEnumAsByte<EFrictionCombineMode::Type> RestitutionCombineMode;` — `UPROPERTY(config, EditAnywhere, Category = Simulation)` — Restitution combine mode, controls how restitution is computed for multiple materials.
- L91 _private member_ `float MaxAngularVelocity;` — `UPROPERTY(config, EditAnywhere, Category = Simulation)` — Max angular velocity that a simulated object can achieve.
- L95 _private member_ `float MaxDepenetrationVelocity;` — `UPROPERTY(config, EditAnywhere, Category = Simulation)` — Max velocity which may be used to depenetrate simulated physics objects. 0 means no maximum.
- L99 _private member_ `float ContactOffsetMultiplier;` — `UPROPERTY(config, EditAnywhere, Category = Simulation, meta = (ClampMin = "0.001", UIMin = "0.001"))` — Contact offset multiplier. When creating a physics shape we look at its bounding volume and multiply its minimum value by this multiplier. A bigger number will generate contact points earlier which results in higher stability at the cost of performance.
- L103 _private member_ `float MinContactOffset;` — `UPROPERTY(config, EditAnywhere, Category = Simulation, meta = (ClampMin = "0.0001", UIMin = "0.0001"))` — Min Contact offset.
- L107 _private member_ `float MaxContactOffset;` — `UPROPERTY(config, EditAnywhere, Category = Simulation, meta = (ClampMin = "0.001", UIMin = "0.001"))` — Max Contact offset.
- L114 _private member_ `bool bSimulateSkeletalMeshOnDedicatedServer;` — `UPROPERTY(config, EditAnywhere, Category = Simulation)` — If true, simulate physics for this component on a dedicated server. This should be set if simulating physics and replicating with a dedicated server.
- L119 _private member_ `TEnumAsByte<ECollisionTraceFlag> DefaultShapeComplexity;` — `UPROPERTY(config, EditAnywhere, Category = Simulation)` — Determines the default physics shape complexity.
- L123 _private member_ `FChaosSolverConfiguration SolverOptions;` — `UPROPERTY(config, EditAnywhere, Category = ChaosPhysics)` — Options to apply to Chaos solvers on creation
- L125 _private prototype_ `static UPhysicsSettingsCore* Get();`
- L127 _private prototype_ `virtual void PostInitProperties() override;`
- L130 _protected prototype_ `static void SetDefaultSettings(UPhysicsSettingsCore* InSettings);`
- L135 _private member_ `static UPhysicsSettingsCore* DefaultSettings;` — Override default settings. This should be set up to point to the CDO of the leaf settings class (as edited in Project Settings)

### `Source/Runtime/PhysicsCore/Public/PhysicsSettingsEnums.h` (Public)


#### enum `EFrictionCombineMode::Type`  
`enum Type : int`  
_L16-26_
- L19 _public enumerator_ `Average = 0` — Uses the average value of the materials touching: (a+b)/2
- L21 _public enumerator_ `Min = 1` — Uses the minimum value of the materials touching: min(a,b)
- L23 _public enumerator_ `Multiply = 2` — Uses the product of the values of the materials touching: a*b
- L25 _public enumerator_ `Max = 3` — Uses the maximum value of materials touching: max(a,b)

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace EFrictionCombineMode`

### `Source/Runtime/PhysicsCore/Public/SQAccelerator.h` (Public)


#### class `FChaosSQAccelerator`  
`class FChaosSQAccelerator`  
_L38-77_
- L42 _public prototype_ `FChaosSQAccelerator(const Chaos::ISpatialAcceleration<Chaos::FAccelerationStructureHandle,Chaos::FReal, 3>& InSpatialAcceleration);`
- L43 _public prototype_ `virtual ~FChaosSQAccelerator() = default;`
- L45 _public prototype_ `void Raycast(const FVector& Start, const FVector& Dir, const float DeltaMagnitude, ChaosInterface::FSQHitBuffer<ChaosInterface::FRaycastHit>& HitBuffer, EHitFlags OutputFlags, const ChaosInterface::FSceneQueryCommonParams& CommonParams) const;`
- L46 _public prototype_ `void Raycast(const FVector& Start, const FVector& Dir, const float DeltaMagnitude, ChaosInterface::FSQHitBuffer<ChaosInterface::FPTRaycastHit>& HitBuffer, EHitFlags OutputFlags, const ChaosInterface::FSceneQueryCommonParams& CommonParams) const;`
- L48 _public prototype_ `void Sweep(const Chaos::FImplicitObject& QueryGeom, const FTransform& StartTM, const FVector& Dir, const float DeltaMagnitude, ChaosInterface::FSQHitBuffer<ChaosInterface::FSweepHit>& HitBuffer, EHitFlags OutputFlags, const ChaosInterface::FSceneQueryCommonParams& CommonParams) const;`
- L49 _public prototype_ `void Sweep(const Chaos::FImplicitObject& QueryGeom, const FTransform& StartTM, const FVector& Dir, const float DeltaMagnitude, ChaosInterface::FSQHitBuffer<ChaosInterface::FPTSweepHit>& HitBuffer, EHitFlags OutputFlags, const ChaosInterface::FSceneQueryCommonParams& CommonParams) const;`
- L51 _public prototype_ `void Overlap(const Chaos::FImplicitObject& QueryGeom, const FTransform& GeomPose, ChaosInterface::FSQHitBuffer<ChaosInterface::FOverlapHit>& HitBuffer, const ChaosInterface::FSceneQueryCommonParams& CommonParams) const;`
- L52 _public prototype_ `void Overlap(const Chaos::FImplicitObject& QueryGeom, const FTransform& GeomPose, ChaosInterface::FSQHitBuffer<ChaosInterface::FPTOverlapHit>& HitBuffer, const ChaosInterface::FSceneQueryCommonParams& CommonParams) const;`
- L57 _public prototype_ `void Raycast(const FVector& Start, const FVector& Dir, const float DeltaMagnitude, ChaosInterface::FSQHitBuffer<ChaosInterface::FRaycastHit>& HitBuffer, EHitFlags OutputFlags, const ChaosInterface::FQueryFilterData& QueryFilterData, ICollisionQueryFilterCallbackBase& QueryCallback, const ChaosInterface::FQueryDebugParams& DebugParams = {}) const;` — `UE_DEPRECATED(5.8, "Use the overload that takes ChaosInterface::FSceneQueryCommonParams instead")`
- L59 _public prototype_ `void Raycast(const FVector& Start, const FVector& Dir, const float DeltaMagnitude, ChaosInterface::FSQHitBuffer<ChaosInterface::FPTRaycastHit>& HitBuffer, EHitFlags OutputFlags, const ChaosInterface::FQueryFilterData& QueryFilterData, ICollisionQueryFilterCallbackBase& QueryCallback, const ChaosInterface::FQueryDebugParams& DebugParams = {}) const;` — `UE_DEPRECATED(5.8, "Use the overload that takes ChaosInterface::FSceneQueryCommonParams instead")`
- L67 _public prototype_ `void Overlap(const Chaos::FImplicitObject& QueryGeom, const FTransform& GeomPose, ChaosInterface::FSQHitBuffer<ChaosInterface::FOverlapHit>& HitBuffer, const ChaosInterface::FQueryFilterData& QueryFilterData, ICollisionQueryFilterCallbackBase& QueryCallback, const ChaosInterface::FQueryDebugParams& DebugParams = {}) const;` — `UE_DEPRECATED(5.8, "Use the overload that takes ChaosInterface::FSceneQueryCommonParams instead")`
- L69 _public prototype_ `void Overlap(const Chaos::FImplicitObject& QueryGeom, const FTransform& GeomPose, ChaosInterface::FSQHitBuffer<ChaosInterface::FPTOverlapHit>& HitBuffer, const ChaosInterface::FQueryFilterData& QueryFilterData, ICollisionQueryFilterCallbackBase& QueryCallback, const ChaosInterface::FQueryDebugParams& DebugParams = {}) const;` — `UE_DEPRECATED(5.8, "Use the overload that takes ChaosInterface::FSceneQueryCommonParams instead")`
- L73 _private member_ `const Chaos::ISpatialAcceleration<Chaos::FAccelerationStructureHandle, Chaos::FReal, 3>& SpatialAcceleration;`
- L76 _private prototype_ `template <typename TRaycastHit> void RaycastImp(const FVector& Start, const FVector& Dir, const float DeltaMagnitude, ChaosInterface::FSQHitBuffer<TRaycastHit>& HitBuffer, EHitFlags OutputFlags, const ChaosInterface::FSceneQueryCommonParams& CommonParams) const;`

#### class `ISQAccelerator`  
`class UE_DEPRECATED(5.8, "This is unused and will be removed") ISQAccelerator`  
_L84-91_
- desc: An interface to the scene query accelerator that allows us to run queries against either PhysX or Chaos This was used in the 2019 GDC demos and is now broken. To make it work again, we would need to implement the FChaosSQAcceleratorAdapter below to use its internal SQ accelerator and convert the inputs and outputs from/to PhysX types.
- L87 _public prototype_ `virtual ~ISQAccelerator() = default;`
- L88 _public prototype_ `virtual void Raycast(const FVector& Start, const FVector& Dir, const float DeltaMagnitude, FPhysicsHitCallback<FHitRaycast>& HitBuffer, EHitFlags OutputFlags, const ChaosInterface::FQueryFilterData& QueryFilterData, ICollisionQueryFilterCallbackBase& QueryCallback) const = 0;`
- L89 _public prototype_ `virtual void Sweep(const FPhysicsGeometry& QueryGeom, const FTransform& StartTM, const FVector& Dir, const float DeltaMagnitude, FPhysicsHitCallback<FHitSweep>& HitBuffer, EHitFlags OutputFlags, const ChaosInterface::FQueryFilterData& QueryFilterData, ICollisionQueryFilterCallbackBase& QueryCallback) const = 0;`
- L90 _public prototype_ `virtual void Overlap(const FPhysicsGeometry& QueryGeom, const FTransform& GeomPose, FPhysicsHitCallback<FHitOverlap>& HitBuffer, const ChaosInterface::FQueryFilterData& QueryFilterData, ICollisionQueryFilterCallbackBase& QueryCallback) const = 0;`

#### class `FSQAcceleratorUnion`  
`class UE_DEPRECATED(5.8, "This is unused and will be removed") FSQAcceleratorUnion : public ISQAccelerator`  
_L93-106_
- inherits: `ISQAccelerator`
- L97 _public prototype_ `virtual void Raycast(const FVector& Start, const FVector& Dir, const float DeltaMagnitude, FPhysicsHitCallback<FHitRaycast>& HitBuffer, EHitFlags OutputFlags, const ChaosInterface::FQueryFilterData& QueryFilterData, ICollisionQueryFilterCallbackBase& QueryCallback) const override;`
- L98 _public prototype_ `virtual void Sweep(const FPhysicsGeometry& QueryGeom, const FTransform& StartTM, const FVector& Dir, const float DeltaMagnitude, FPhysicsHitCallback<FHitSweep>& HitBuffer, EHitFlags OutputFlags, const ChaosInterface::FQueryFilterData& QueryFilterData, ICollisionQueryFilterCallbackBase& QueryCallback) const override;`
- L99 _public prototype_ `virtual void Overlap(const FPhysicsGeometry& QueryGeom, const FTransform& GeomPose, FPhysicsHitCallback<FHitOverlap>& HitBuffer, const ChaosInterface::FQueryFilterData& QueryFilterData, ICollisionQueryFilterCallbackBase& QueryCallback) const override;`
- L101 _public prototype_ `void AddSQAccelerator(ISQAccelerator* InAccelerator);`
- L102 _public prototype_ `void RemoveSQAccelerator(ISQAccelerator* AcceleratorToRemove);`
- L105 _private member_ `TArray<ISQAccelerator*> Accelerators;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace ChaosInterface`
- L17 _namespace_ `namespace ChaosInterface`
- L18 _namespace_ `namespace ChaosInterface`
- L19 _namespace_ `namespace ChaosInterface`
- L20 _namespace_ `namespace ChaosInterface`
- L21 _namespace_ `namespace ChaosInterface`
- L22 _namespace_ `namespace ChaosInterface`
- L24 _namespace_ `namespace Chaos`

### `Source/Runtime/PhysicsCore/Public/SQCapture.h` (Public)


#### struct `FSQCapture`  
`struct UE_INTERNAL FSQCapture`  
_L41-117_
- desc: Allows us to capture a scene query with either physx or chaos and then load it into either format for testing purposes
- L43 _public prototype_ `~FSQCapture();`
- L44 _public prototype_ `FSQCapture(const FSQCapture&) = delete;`
- L45 _public prototype_ `FSQCapture& operator=(const FSQCapture&) = delete;`
- L52 _public member_ `} SQType;`
- L54 _public prototype_ `void StartCaptureChaosSweep(const Chaos::FPBDRigidsEvolution& Evolution, const Chaos::FImplicitObject& InQueryGeom, const FTransform& InStartTM, const FVector& InDir, float InDeltaMag, FHitFlags InOutputFlags, const ChaosInterface::FQueryFilterData& QueryFilter, const FCollisionFilterData& FilterData, ICollisionQueryFilterCallbackBase& Callback);`
- L55 _public prototype_ `void EndCaptureChaosSweep(const ChaosInterface::FSQHitBuffer<ChaosInterface::FSweepHit>& Results);`
- L57 _public prototype_ `void StartCaptureChaosRaycast(const Chaos::FPBDRigidsEvolution& Evolution, const FVector& InStartPoint, const FVector& InDir, float InDeltaMag, FHitFlags InOutputFlags, const ChaosInterface::FQueryFilterData& QueryFilter, const FCollisionFilterData& FilterData, ICollisionQueryFilterCallbackBase& Callback);`
- L58 _public prototype_ `void EndCaptureChaosRaycast(const ChaosInterface::FSQHitBuffer<ChaosInterface::FRaycastHit>& Results);`
- L60 _public prototype_ `void StartCaptureChaosOverlap(const Chaos::FPBDRigidsEvolution& Evolution, const Chaos::FImplicitObject& InQueryGeom, const FTransform& InStartTM, const ChaosInterface::FQueryFilterData& QueryFilter, const FCollisionFilterData& FilterData, ICollisionQueryFilterCallbackBase& Callback);`
- L61 _public prototype_ `void EndCaptureChaosOverlap(const ChaosInterface::FSQHitBuffer<ChaosInterface::FOverlapHit>& Results);`
- L63 _public prototype_ `ECollisionQueryHitType GetFilterResult(const Chaos::FPerShapeData* Shape, const Chaos::FGeometryParticle* Actor) const;`
- L65 _public member_ `FVector Dir;`
- L66 _public member_ `FTransform StartTM;` — only valid if overlap or sweep
- L67 _public member_ `FVector StartPoint;` — only valid if raycast
- L69 _public member_ `float DeltaMag;`
- L70 _public member_ `FHitFlags OutputFlags;`
- L71 _public member_ `ChaosInterface::FQueryFilterData QueryFilterData;`
- L72 _public member_ `TUniquePtr<ICollisionQueryFilterCallbackBase> FilterCallback;`
- L74 _public member_ `Chaos::FImplicitObjectPtr ChaosImplicitGeometry;`
- L76 _public member_ `ChaosInterface::FSQHitBuffer<ChaosInterface::FSweepHit> ChaosSweepBuffer;`
- L77 _public member_ `TArray<ChaosInterface::FSweepHit> ChaosSweepTouches;`
- L79 _public member_ `ChaosInterface::FSQHitBuffer<ChaosInterface::FRaycastHit> ChaosRaycastBuffer;`
- L80 _public member_ `TArray<ChaosInterface::FRaycastHit> ChaosRaycastTouches;`
- L82 _public member_ `ChaosInterface::FSQHitBuffer<ChaosInterface::FOverlapHit> ChaosOverlapBuffer;`
- L83 _public member_ `TArray<ChaosInterface::FOverlapHit> ChaosOverlapTouches;`
- L86 _public member_ `TUniquePtr<Chaos::FImplicitObject> ChaosOwnerObject;` — `UE_DEPRECATED(5.4, "Please use ChaosImplicitGeometry instead.")` — should be private, do not access directly
- L89 _public member_ `const Chaos::FImplicitObject* ChaosGeometry;` — `UE_DEPRECATED(5.4, "Please use ChaosImplicitGeometry instead.")`
- L92 _public member_ `TUniquePtr<Chaos::FImplicitObject> SerializableChaosGeometry;` — `UE_DEPRECATED(5.4, "Please use ChaosImplicitGeometry instead.")`
- L95 _private prototype_ `FSQCapture(FPhysTestSerializer& OwningPhysSerializer);` — This should be created by PhysTestSerializer
- L96 _private prototype_ `void Serialize(Chaos::FChaosArchive& Ar);`
- L100 _private member_ `TArray<uint8> GeomData;`
- L101 _private member_ `TArray<uint8> HitData;`
- L103 _private member_ `FPhysTestSerializer& PhysSerializer;`
- L105 _private prototype_ `void CaptureChaosFilterResults(const Chaos::FPBDRigidsEvolution& Evolution, const FCollisionFilterData& FilterData, ICollisionQueryFilterCallbackBase& Callback);`
- L107 _private member_ `TMap<Chaos::FGeometryParticle*, TArray<TPair<Chaos::FPerShapeData*, ECollisionQueryHitType>>> ChaosActorToShapeHitsArray;`
- L110 _private prototype_ `template <typename THit> void SerializeChaosBuffers(Chaos::FChaosArchive& Ar, int32 Version, ChaosInterface::FSQHitBuffer<THit>& ChaosBuffer);`
- L112 _private prototype_ `void SerializeChaosActorToShapeHitsArray(Chaos::FChaosArchive& Ar);`
- L114 _private member_ `bool bDiskDataIsChaos;`
- L115 _private member_ `bool bChaosDataReady;`
- L116 _private member_ `bool bPhysXDataReady;`

#### enum `FSQCapture::ESQType`  
`enum class ESQType : uint8`  
_L47-52_
- L49 _public enumerator_ `Raycast`
- L50 _public enumerator_ `Sweep`
- L51 _public enumerator_ `Overlap`

#### Free symbols / members of external scopes

- L25 _namespace_ `namespace ChaosInterface`
- L32 _namespace_ `namespace Chaos`

### `Source/Runtime/PhysicsCore/Public/SQVerifier.h` (Public)


#### Free symbols / members of external scopes

- L16 _macro_ `#define SQ_REPLAY_TEST(cond) bEnsureOnMismatch ? ensure(cond) : (cond)`
- L22 _function_ `void SQPerfComparisonHelper(const FString& TestName, FPhysTestSerializer& Serializer, bool bEnsureOnMismatch = false)` — `UE_DEPRECATED(5.8, "This is unused and will be removed")`
- L219 _function_ `bool SQValidityHelper(FPhysTestSerializer& Serializer)` — `UE_DEPRECATED(5.8, "This is unused and will be removed")`

### `Source/Runtime/PhysicsCore/Public/SQVisitor.h` (Public)


#### struct `TSQVisitor`  
`template <typename QueryGeometryType, typename TPayload, typename THitType, bool bGTData = true> struct TSQVisitor : public Chaos::ISpatialVisitor<TPayload, Chaos::FReal>`  
_L43-530_
- inherits: `Chaos::ISpatialVisitor<TPayload,Chaos::FReal>`
- L45 _public typedef_ `using TGeometryType = std::conditional_t<bGTData, Chaos::FGeometryParticle, Chaos::FGeometryParticleHandle>;`
- L46 _public typedef_ `using FAABB3 = Chaos::FAABB3;`
- L47 _public typedef_ `using FVec3 = Chaos::FVec3;`
- L48 _public function_ `TSQVisitor(const FVector& InStartPoint, const FVector& InDir, ChaosInterface::FSQHitBuffer<THitType>& InHitBuffer, EHitFlags InOutputFlags, const ChaosInterface::FSceneQueryCommonParams& InCommonParams) : StartPoint(InStartPoint) , Dir(InDir) , OutputFlags(InOutputFlags) , bAnyHit(false) , DebugParams(InCommonParams.DebugParams) , HitFaceNormal(Chaos::FVec3::ZeroVector) , HitBuffer(InHitBuffer) , QueryFlags(InCommonParams.Flags) , QueryFilterData(InCommonParams.FilterData) , QueryCallback(InCommonParams.GetQueryCallback()) , QueryCenter(StartTM.GetLocation())`
- L68 _public function_ `TSQVisitor(const FVector& InStartPoint, const FVector& InDir, ChaosInterface::FSQHitBuffer<THitType>& InHitBuffer, EHitFlags InOutputFlags, const ChaosInterface::FQueryFilterData& InQueryFilterData, ICollisionQueryFilterCallbackBase& InQueryCallback, const ChaosInterface::FQueryDebugParams& InDebugParams) : TSQVisitor(InStartPoint, InDir, InHitBuffer, InOutputFlags, ChaosInterface::FSceneQueryCommonParams(InQueryCallback, InQueryFilterData, InDebugParams))` — `UE_DEPRECATED(5.8, "Use the overload that takes a ChaosInterface::FSceneQueryCommonParams instead")`
- L75 _public function_ `TSQVisitor(const FTransform& InStartTM, const FVector& InDir, ChaosInterface::FSQHitBuffer<THitType>& InHitBuffer, EHitFlags InOutputFlags, const QueryGeometryType& InQueryGeom, const FAABB3& InQueryGeomWorldBounds, const ChaosInterface::FSceneQueryCommonParams& InCommonParams) : Dir(InDir) , OutputFlags(InOutputFlags) , bAnyHit(false) , DebugParams(InCommonParams.DebugParams) , HitFaceNormal(Chaos::FVec3::ZeroVector) , HitBuffer(InHitBuffer) , QueryFlags(InCommonParams.Flags) , QueryFilterData(InCommonParams.FilterData) , QueryGeom(&InQueryGeom) , QueryCallback(InCommonParams.GetQueryCallback()) , StartTM(InStartTM) , QueryGeomWorldBounds(InQueryGeomWorldBounds) , QueryCenter(InQueryGeomWorldBounds.Center())`
- L97 _public function_ `TSQVisitor(const FTransform& InStartTM, const FVector& InDir, ChaosInterface::FSQHitBuffer<THitType>& InHitBuffer, EHitFlags InOutputFlags, const ChaosInterface::FQueryFilterData& InQueryFilterData, ICollisionQueryFilterCallbackBase& InQueryCallback, const QueryGeometryType& InQueryGeom, const FAABB3& InQueryGeomWorldBounds, const ChaosInterface::FQueryDebugParams& InDebugParams) : TSQVisitor(InStartTM, InDir, InHitBuffer, InOutputFlags, InQueryGeom, InQueryGeomWorldBounds, ChaosInterface::FSceneQueryCommonParams(InQueryCallback, InQueryFilterData, InDebugParams))` — `UE_DEPRECATED(5.8, "Use the overload that takes a ChaosInterface::FSceneQueryCommonParams instead")`
- L111 _public function_ `TSQVisitor(const FTransform& InWorldTM, ChaosInterface::FSQHitBuffer<THitType>& InHitBuffer, const QueryGeometryType& InQueryGeom, const FAABB3& InQueryGeomWorldBounds, const ChaosInterface::FSceneQueryCommonParams& InCommonParams) : bAnyHit(false) , DebugParams(InCommonParams.DebugParams) , HitFaceNormal(Chaos::FVec3::ZeroVector) , HitBuffer(InHitBuffer) , QueryFlags(InCommonParams.Flags) , QueryFilterData(InCommonParams.FilterData) , QueryGeom(&InQueryGeom) , QueryCallback(InCommonParams.GetQueryCallback()) , StartTM(InWorldTM) , QueryGeomWorldBounds(InQueryGeomWorldBounds) , QueryCenter(InQueryGeomWorldBounds.Center())`
- L131 _public function_ `TSQVisitor(const FTransform& InWorldTM, ChaosInterface::FSQHitBuffer<THitType>& InHitBuffer, const ChaosInterface::FQueryFilterData& InQueryFilterData, ICollisionQueryFilterCallbackBase& InQueryCallback, const QueryGeometryType& InQueryGeom, const FAABB3& InQueryGeomWorldBounds, const ChaosInterface::FQueryDebugParams& InDebugParams) : TSQVisitor(InWorldTM, InHitBuffer, InQueryGeom, InQueryGeomWorldBounds, ChaosInterface::FSceneQueryCommonParams(InQueryCallback, InQueryFilterData, InDebugParams))` — `UE_DEPRECATED(5.8, "Use the overload that takes a ChaosInterface::FSceneQueryCommonParams instead")`
- L145 _public prototype_ `virtual ~TSQVisitor() = default;`
- L147 _public function_ `virtual bool Raycast(const Chaos::TSpatialVisitorData<TPayload>& Instance, Chaos::FQueryFastData& CurData) override`
- L152 _public function_ `virtual bool Sweep(const Chaos::TSpatialVisitorData<TPayload>& Instance, Chaos::FQueryFastData& CurData) override`
- L157 _public function_ `virtual bool Overlap(const Chaos::TSpatialVisitorData<TPayload>& Instance) override`
- L162 _public function_ `virtual bool PrePreFilter(const TPayload& Payload) const override`
- L168 _public function_ `virtual const void* GetQueryPayload() const override` — Return a pointer to the payload on which we are querying the acceleration structure
- L173 _public function_ `virtual bool HasBlockingHit() const override`
- L187 _private function_ `TGeometryType* GetPayloadForThread(const TPayload& Payload)`
- L204 _private function_ `template <ESQType SQ> bool Visit(const Chaos::TSpatialVisitorData<TPayload>& Instance, Chaos::FQueryFastData* CurData)`
- L480 _private function_ `void DebugDrawPayloadImpl(const TPayload& Payload, const bool bExternal, const bool bHit, decltype(&TPayload::DebugDraw))`
- L484 _private function_ `void DebugDrawPayloadImpl(const TPayload& Payload, const bool bExternal, const bool bHit, ...)`
- L486 _private function_ `void DebugDrawPayload(const TPayload& Payload, const bool bExternal, const bool bHit)`
- L492 _private function_ `template <ESQType SQ> void DebugDraw(const Chaos::TSpatialVisitorData<TPayload>& Instance, const Chaos::FQueryFastData* CurData, const bool bPrefiltered, const bool bHit)`
- L516 _private member_ `const FVector StartPoint = FVector::ZeroVector;`
- L517 _private member_ `const FVector Dir = FVector::ZeroVector;`
- L518 _private member_ `FHitFlags OutputFlags;`
- L519 _private member_ `bool bAnyHit;`
- L520 _private member_ `const ChaosInterface::FQueryDebugParams DebugParams;`
- L521 _private member_ `Chaos::FVec3 HitFaceNormal;`
- L522 _private member_ `ChaosInterface::FSQHitBuffer<THitType>& HitBuffer;`
- L523 _private member_ `const FChaosQueryFlags QueryFlags;`
- L524 _private member_ `const Chaos::Filter::FQueryFilterData QueryFilterData;`
- L525 _private member_ `const QueryGeometryType* QueryGeom = nullptr;`
- L526 _private member_ `ICollisionQueryFilterCallback& QueryCallback;`
- L527 _private member_ `const FTransform StartTM;`
- L528 _private member_ `FAABB3 QueryGeomWorldBounds = FAABB3::ZeroAABB();`
- L529 _private member_ `FVec3 QueryCenter = FVec3::ZeroVector;`

#### enum `TSQVisitor::ESQType`  
`enum class ESQType`  
_L180-185_
- L182 _public enumerator_ `Raycast`
- L183 _public enumerator_ `Sweep`
- L184 _public enumerator_ `Overlap`

#### struct `TBPVisitor`  
`template <typename QueryGeometryType, typename TPayload, typename THitType, bool bGTData = true> struct TBPVisitor : public Chaos::ISpatialVisitor<TPayload, Chaos::FReal>`  
_L534-677_
- inherits: `Chaos::ISpatialVisitor<TPayload,Chaos::FReal>`
- L536 _public typedef_ `using TGeometryType = std::conditional_t<bGTData, Chaos::FGeometryParticle, Chaos::FGeometryParticleHandle>;`
- L538 _public function_ `TBPVisitor(const FTransform& InWorldTM, ChaosInterface::FSQHitBuffer<THitType>& InHitBuffer, const QueryGeometryType& InQueryGeom, const ChaosInterface::FSceneQueryCommonParams& InCommonParams) : HalfExtents(InQueryGeom.BoundingBox().Extents() * 0.5) , bAnyHit(false) , DebugParams(InCommonParams.DebugParams) , HitBuffer(InHitBuffer) , QueryFlags(InCommonParams.Flags) , QueryFilterData(InCommonParams.FilterData) , QueryGeom(&InQueryGeom) , QueryCallback(InCommonParams.GetQueryCallback()) , StartTM(InWorldTM)`
- L555 _public function_ `TBPVisitor(const FTransform& InWorldTM, ChaosInterface::FSQHitBuffer<THitType>& InHitBuffer, const ChaosInterface::FQueryFilterData& InQueryFilterData, ICollisionQueryFilterCallbackBase& InQueryCallback, const QueryGeometryType& InQueryGeom, const ChaosInterface::FQueryDebugParams& InDebugParams) : TBPVisitor(InWorldTM, InHitBuffer, InQueryGeom, ChaosInterface::FSceneQueryCommonParams(InQueryCallback, InQueryFilterData, InDebugParams))` — `UE_DEPRECATED(5.8, "Use the overload that takes a ChaosInterface::FSceneQueryCommonParams instead")`
- L562 _public prototype_ `virtual ~TBPVisitor() = default;`
- L564 _public function_ `virtual bool Overlap(const Chaos::TSpatialVisitorData<TPayload>& Instance) override`
- L569 _public function_ `virtual bool Raycast(const Chaos::TSpatialVisitorData<TPayload>& Instance, Chaos::FQueryFastData& CurData) override`
- L575 _public function_ `virtual bool Sweep(const Chaos::TSpatialVisitorData<TPayload>& Instance, Chaos::FQueryFastData& CurData) override`
- L581 _public function_ `virtual bool PrePreFilter(const TPayload& Payload) const override`
- L587 _public function_ `virtual const void* GetQueryPayload() const override` — Return a pointer to the payload on which we are querying the acceleration structure
- L601 _private function_ `TGeometryType* GetPayloadForThread(const TPayload& Payload)`
- L618 _private function_ `template <ESQType SQ> bool Visit(const Chaos::TSpatialVisitorData<TPayload>& Instance, Chaos::FQueryFastData* CurData)`
- L665 _private member_ `const FVector StartPoint = FVector::ZeroVector;`
- L666 _private member_ `const FVector Dir = FVector::ZeroVector;`
- L667 _private member_ `const FVector HalfExtents = FVector::ZeroVector;`
- L668 _private member_ `FHitFlags OutputFlags;`
- L669 _private member_ `bool bAnyHit;`
- L670 _private member_ `const ChaosInterface::FQueryDebugParams DebugParams;`
- L671 _private member_ `ChaosInterface::FSQHitBuffer<THitType>& HitBuffer;`
- L672 _private member_ `const FChaosQueryFlags QueryFlags;`
- L673 _private member_ `const Chaos::Filter::FQueryFilterData QueryFilterData;`
- L674 _private member_ `const QueryGeometryType* QueryGeom;`
- L675 _private member_ `ICollisionQueryFilterCallback& QueryCallback;`
- L676 _private member_ `const FTransform StartTM;`

#### enum `TBPVisitor::ESQType`  
`enum class ESQType`  
_L594-599_
- L596 _public enumerator_ `Raycast`
- L597 _public enumerator_ `Sweep`
- L598 _public enumerator_ `Overlap`

#### Free symbols / members of external scopes

- L25 _externvar_ `extern int32 ChaosSQDrawDebugVisitorQueries;`
- L26 _externvar_ `extern FAutoConsoleVariableRef CVarChaosSQDrawDebugQueries;`
- L30 _function_ `template <typename TLocationHit> void FillHitHelper(TLocationHit& Hit, const Chaos::FReal Distance, const FVector& WorldPosition, const FVector& WorldNormal, int32 FaceIdx, bool bComputeMTD)`
- L681 _function_ `template <typename QueryGeomType, typename TSweepHit, typename TPayload> void SweepHelper(const QueryGeomType& QueryGeom, const Chaos::ISpatialAcceleration<TPayload, Chaos::FReal, 3>& SpatialAcceleration, const FTransform& StartTM, const FVector& Dir, const float DeltaMagnitude, ChaosInterface::FSQHitBuffer<TSweepHit>& HitBuffer, EHitFlags OutputFlags, const ChaosInterface::FSceneQueryCommonParams& InCommonParams)`
- L706 _function_ `template <typename QueryGeomType, typename TOverlapHit, typename TPayload> void OverlapHelper(const QueryGeomType& QueryGeom, const Chaos::ISpatialAcceleration<TPayload, Chaos::FReal, 3>& SpatialAcceleration, const FTransform& GeomPose, ChaosInterface::FSQHitBuffer<TOverlapHit>& HitBuffer, const ChaosInterface::FSceneQueryCommonParams& InCommonParams)`
- L738 _function_ `void SweepHelper(const QueryGeomType& QueryGeom, const Chaos::ISpatialAcceleration<TPayload, Chaos::FReal, 3>& SpatialAcceleration, const FTransform& StartTM, const FVector& Dir, const float DeltaMagnitude, ChaosInterface::FSQHitBuffer<TSweepHit>& HitBuffer, EHitFlags OutputFlags, const ChaosInterface::FQueryFilterData& QueryFilterData, ICollisionQueryFilterCallbackBase& QueryCallback, const ChaosInterface::FQueryDebugParams& DebugParams)` — `UE_DEPRECATED(5.8, "Use the overload that takes ChaosInterface::FSceneQueryCommonParams instead")`
- L746 _function_ `void OverlapHelper(const QueryGeomType& QueryGeom, const Chaos::ISpatialAcceleration<TPayload, Chaos::FReal, 3>& SpatialAcceleration, const FTransform& GeomPose, ChaosInterface::FSQHitBuffer<TOverlapHit>& HitBuffer, const ChaosInterface::FQueryFilterData& QueryFilterData, ICollisionQueryFilterCallbackBase& QueryCallback, const ChaosInterface::FQueryDebugParams& DebugParams)` — `UE_DEPRECATED(5.8, "Use the overload that takes ChaosInterface::FSceneQueryCommonParams instead")`

### `Source/Runtime/PhysicsCore/Public/SceneQueryCommonParams.h` (Public)


#### struct `ChaosInterface::FSceneQueryCommonParams`  
`struct FSceneQueryCommonParams`  
_L13-34_
- L15 _public typedef_ `using FQueryFilterData = Chaos::Filter::FQueryFilterData;`
- L17 _public prototype_ `explicit FSceneQueryCommonParams(ICollisionQueryFilterCallback& InQueryCallback);`
- L18 _public prototype_ `explicit FSceneQueryCommonParams(ICollisionQueryFilterCallback& InQueryCallback, const FQueryFilterData& InFilterData, FChaosQueryFlags InFlags, const FQueryDebugParams& InDebugParams = {});`
- L19 _public prototype_ `explicit FSceneQueryCommonParams(ICollisionQueryFilterCallback& InQueryCallback, const FQueryFilterData& InFilterData, EQueryFlags InFlags, const FQueryDebugParams& InDebugParams = {});`
- L23 _public prototype_ `UE_INTERNAL explicit FSceneQueryCommonParams(ICollisionQueryFilterCallback& InQueryCallback, const FChaosQueryFilterData& InFilterData, const FQueryDebugParams& InDebugParams = {});` — Temporary constructor for deprecated code.
- L26 _public prototype_ `ICollisionQueryFilterCallback& GetQueryCallback() const;`
- L28 _public member_ `FQueryFilterData FilterData;`
- L29 _public member_ `FChaosQueryFlags Flags;`
- L30 _public member_ `FQueryDebugParams DebugParams;`
- L33 _private member_ `ICollisionQueryFilterCallback* QueryCallback = nullptr;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace ChaosInterface`
