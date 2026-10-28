# Plugins / ChaosRigidPhysicsAsync

- module root: `Plugins/Experimental/ChaosRigidPhysicsAsync/Source/ChaosRigidPhysicsAsync`
- headers: 10; symbols: 424
- symbol kinds: class=16, function=6, member=56, namespace=36, prototype=291, struct=1, typedef=18
- PublicDependencyModuleNames: Core, CoreUObject, Engine, RigidPhysics

### `Plugins/Experimental/ChaosRigidPhysicsAsync/Source/ChaosRigidPhysicsAsync/Private/ChaosRigidPhysicsAsync/Conversions.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Chaos`
- L11 _namespace_ `namespace Rigids` (scope `Chaos`)
- L11 _namespace_ `namespace Async` (scope `Chaos::Rigids`)
- L13 _function_ `inline ECollisionTraceFlag ConvertCollisionTraceFlag(const Chaos::EChaosCollisionTraceFlag InFlag)` (scope `Chaos::Rigids::Async`)
- L35 _function_ `inline Chaos::EChaosCollisionTraceFlag ConvertCollisionTraceFlag(const ECollisionTraceFlag InFlag)` (scope `Chaos::Rigids::Async`)

### `Plugins/Experimental/ChaosRigidPhysicsAsync/Source/ChaosRigidPhysicsAsync/Public/ChaosRigidPhysicsAsync/JointConstraint6DOFAsync.h` (Public)


#### class `Chaos::Rigids::Async::FJointConstraint6DOFAsyncGT`  
`class UE_INTERNAL FJointConstraint6DOFAsyncGT : public UE::Physics::IJointConstraint6DOF`  
_L17-90_
- inherits: `UE::Physics::IJointConstraint6DOF`
- L19 _private typedef_ `using EJointMotionType = UE::Physics::EJointMotionType;`
- L20 _private typedef_ `using IRigidBody = UE::Physics::IRigidBody;`
- L25 _public prototype_ `UE_INTERNAL FJointConstraint6DOFAsyncGT(FRigidSceneAsyncGT* InScene);`
- L26 _public prototype_ `UE_INTERNAL virtual ~FJointConstraint6DOFAsyncGT();`
- L28 _public prototype_ `UE_INTERNAL virtual FJointConstraintHandle GetHandle() const override final;`
- L30 _public prototype_ `UE_INTERNAL virtual void Activate() override final;`
- L31 _public prototype_ `UE_INTERNAL virtual void SetBodies(IRigidBody* Body0, IRigidBody* Body1) override final;`
- L32 _public prototype_ `UE_INTERNAL virtual void SetJointTransforms(const FTransform3d& InTransform0, const FTransform3d& InTransform1) override final;`
- L34 _public prototype_ `UE_INTERNAL virtual double GetLinearLimit() const override final;`
- L35 _public prototype_ `UE_INTERNAL virtual void SetLinearLimit(const double InLinearLimit) override final;`
- L37 _public prototype_ `UE_INTERNAL virtual EJointMotionType GetLinearMotionTypesX() const override final;`
- L38 _public prototype_ `UE_INTERNAL virtual void SetLinearMotionTypesX(const EJointMotionType InMotionType) override final;`
- L40 _public prototype_ `UE_INTERNAL virtual EJointMotionType GetLinearMotionTypesY() const override final;`
- L41 _public prototype_ `UE_INTERNAL virtual void SetLinearMotionTypesY(const EJointMotionType InMotionType) override final;`
- L43 _public prototype_ `UE_INTERNAL virtual EJointMotionType GetLinearMotionTypesZ() const override final;`
- L44 _public prototype_ `UE_INTERNAL virtual void SetLinearMotionTypesZ(const EJointMotionType InMotionType) override final;`
- L46 _public prototype_ `UE_INTERNAL virtual void SetAngularMotionTypesX(const EJointMotionType InMotionType) override final;`
- L47 _public prototype_ `UE_INTERNAL virtual void SetAngularMotionTypesY(const EJointMotionType InMotionType) override final;`
- L48 _public prototype_ `UE_INTERNAL virtual void SetAngularMotionTypesZ(const EJointMotionType InMotionType) override final;`
- L50 _public prototype_ `UE_INTERNAL virtual void SetAngularLimits(const FVector3d& InAngularLimits) override final;`
- L52 _public prototype_ `UE_INTERNAL virtual void SetCollisionEnabled(const bool bCollisionEnabled) override final;`
- L53 _public prototype_ `UE_INTERNAL virtual void SetProjectionEnabled(const bool bProjectionEnabled) override final;`
- L54 _public prototype_ `UE_INTERNAL virtual void SetMassConditioningEnabled(const bool bMassConditioningEnabled) override final;`
- L55 _public prototype_ `UE_INTERNAL virtual void SetUseLinearSolver(const bool bUseLinearSolver) override final;`
- L57 _public prototype_ `UE_INTERNAL virtual void SetSoftLinearLimitsEnabled(const bool bSoftLinearLimitsEnabled) override final;`
- L58 _public prototype_ `UE_INTERNAL virtual void SetSoftTwistLimitsEnabled(const bool bSoftTwistLimitsEnabled) override final;`
- L59 _public prototype_ `UE_INTERNAL virtual void SetSoftSwingLimitsEnabled(const bool bSoftSwingLimitsEnabled) override final;`
- L61 _public prototype_ `UE_INTERNAL virtual void SetSoftLinearStiffness(const double InSoftLinearStiffness) override final;`
- L62 _public prototype_ `UE_INTERNAL virtual void SetSoftLinearDamping(const double InSoftLinearDamping) override final;`
- L63 _public prototype_ `UE_INTERNAL virtual void SetSoftTwistStiffness(const double InSoftTwistStiffness) override final;`
- L64 _public prototype_ `UE_INTERNAL virtual void SetSoftTwistDamping(const double InSoftTwistDamping) override final;`
- L65 _public prototype_ `UE_INTERNAL virtual void SetSoftSwingStiffness(const double InSoftSwingStiffness) override final;`
- L66 _public prototype_ `UE_INTERNAL virtual void SetSoftSwingDamping(const double InSoftSwingDamping) override final;`
- L68 _public prototype_ `UE_INTERNAL virtual void SetProjectionLinearAlpha(const double InProjectionLinearAlpha) override final;`
- L69 _public prototype_ `UE_INTERNAL virtual void SetProjectionAngularAlpha(const double InProjectionAngularAlpha) override final;`
- L70 _public prototype_ `UE_INTERNAL virtual void SetProjectionLinearTolerance(const double InProjectionLinearTolerance) override final;`
- L71 _public prototype_ `UE_INTERNAL virtual void SetProjectionAngularTolerance(const double InProjectionAngularTolerance) override final;`
- L73 _public prototype_ `UE_INTERNAL virtual void SetLinearContactDistance(const double InLinearContactDistance) override final;`
- L74 _public prototype_ `UE_INTERNAL virtual void SetTwistContactDistance(const double InTwistContactDistance) override final;`
- L75 _public prototype_ `UE_INTERNAL virtual void SetSwingContactDistance(const double InSwingContactDistance) override final;`
- L77 _public prototype_ `UE_INTERNAL virtual void SetAngularDriveStiffness(const FVector3d& InAngularDriveStiffness) override final;`
- L78 _public prototype_ `UE_INTERNAL virtual void SetAngularDriveDamping(const FVector3d& InAngularDriveDamping) override final;`
- L79 _public prototype_ `UE_INTERNAL virtual void SetLinearDriveStiffness(const FVector3d& InLinearDriveStiffness) override final;`
- L80 _public prototype_ `UE_INTERNAL virtual void SetLinearDriveDamping(const FVector3d& InLinearDriveDamping) override final;`
- L82 _public prototype_ `UE_INTERNAL void SetId(const FRigidObjectId& InId);`
- L83 _public prototype_ `UE_INTERNAL Chaos::FJointConstraint* GetJointConstraint();`
- L84 _public prototype_ `UE_INTERNAL const Chaos::FJointConstraint* GetJointConstraint() const;`
- L87 _private member_ `UE::Physics::FRigidObjectId ConstraintId;`
- L88 _private member_ `FRigidSceneAsyncGT* Scene = nullptr;`
- L89 _private member_ `Chaos::FJointConstraint* Constraint = nullptr;`

#### class `Chaos::Rigids::Async::FJointConstraint6DOFAsyncPT`  
`class UE_INTERNAL FJointConstraint6DOFAsyncPT : public UE::Physics::IJointConstraint6DOF`  
_L92-120_
- inherits: `UE::Physics::IJointConstraint6DOF`
- L94 _private typedef_ `using EJointMotionType = UE::Physics::EJointMotionType;`
- L99 _public prototype_ `UE_INTERNAL FJointConstraint6DOFAsyncPT(const FJointConstraintHandle& InHandle, FRigidSceneAsyncPT* InScene, Chaos::FJointConstraint* InConstraint);`
- L100 _public prototype_ `UE_INTERNAL virtual ~FJointConstraint6DOFAsyncPT() = default;`
- L102 _public prototype_ `UE_INTERNAL virtual FJointConstraintHandle GetHandle() const override final;`
- L104 _public prototype_ `UE_INTERNAL virtual double GetLinearLimit() const override final;`
- L105 _public prototype_ `UE_INTERNAL virtual void SetLinearLimit(const double InLinearLimit) override final;`
- L107 _public prototype_ `UE_INTERNAL virtual EJointMotionType GetLinearMotionTypesX() const override final;`
- L108 _public prototype_ `UE_INTERNAL virtual void SetLinearMotionTypesX(const EJointMotionType InMotionType) override final;`
- L110 _public prototype_ `UE_INTERNAL virtual EJointMotionType GetLinearMotionTypesY() const override final;`
- L111 _public prototype_ `UE_INTERNAL virtual void SetLinearMotionTypesY(const EJointMotionType InMotionType) override final;`
- L113 _public prototype_ `UE_INTERNAL virtual EJointMotionType GetLinearMotionTypesZ() const override final;`
- L114 _public prototype_ `UE_INTERNAL virtual void SetLinearMotionTypesZ(const EJointMotionType InMotionType) override final;`
- L117 _private member_ `FJointConstraintHandle Handle;`
- L118 _private member_ `FRigidSceneAsyncPT* Scene = nullptr;`
- L119 _private member_ `Chaos::FJointConstraint* Constraint = nullptr;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Chaos`
- L15 _namespace_ `namespace Chaos`
- L15 _namespace_ `namespace Rigids` (scope `Chaos`)
- L15 _namespace_ `namespace Async` (scope `Chaos::Rigids`)

### `Plugins/Experimental/ChaosRigidPhysicsAsync/Source/ChaosRigidPhysicsAsync/Public/ChaosRigidPhysicsAsync/RigidBodyAsync.h` (Public)


#### class `Chaos::Rigids::Async::FRigidBodyAsyncGT`  
`class UE_INTERNAL FRigidBodyAsyncGT : public UE::Physics::IRigidBody`  
_L34-108_
- inherits: `UE::Physics::IRigidBody`
- L39 _public prototype_ `UE_INTERNAL FRigidBodyAsyncGT(FRigidSceneAsyncGT* InScene, const UE::Physics::FRigidDebugName& InName, UE::Physics::ERigidMovementType InMovementType);`
- L41 _public prototype_ `virtual ~FRigidBodyAsyncGT();`
- L46 _public prototype_ `UE_INTERNAL virtual UE::Physics::FRigidBodyHandle GetHandle() const override final;`
- L47 _public prototype_ `UE_INTERNAL virtual void SetId(const UE::Physics::FRigidObjectId& InId) override final;`
- L49 _public prototype_ `UE_INTERNAL virtual bool IsActive() const override final;`
- L50 _public prototype_ `UE_INTERNAL virtual void Activate() override final;`
- L51 _public prototype_ `UE_INTERNAL virtual void Deactivate() override final;`
- L52 _public prototype_ `UE_INTERNAL virtual bool IsStatic() const override final;`
- L53 _public prototype_ `UE_INTERNAL virtual bool IsKinematic() const override final;`
- L54 _public prototype_ `UE_INTERNAL virtual bool IsDynamic() const override final;`
- L55 _public prototype_ `UE_INTERNAL virtual bool IsSleeping() const override final;`
- L57 _public prototype_ `UE_INTERNAL virtual int32 GetNumShapes() const override final;`
- L58 _public prototype_ `UE_INTERNAL virtual FRigidShapeInstanceAsync* GetShape(int32 InShapeIndex) const override final;`
- L59 _public prototype_ `UE_INTERNAL virtual FRigidShapeInstanceAsync* CreateShape(const UE::Physics::FRigidShapeInstanceSetup& InSetup) override final;`
- L60 _public prototype_ `UE_INTERNAL virtual FRigidShapeInstanceAsync* CreateShape(TUniquePtr<Chaos::FPerShapeData>&& InShapeData) override final;`
- L61 _public prototype_ `UE_INTERNAL virtual void DestroyShape(IRigidShapeInstance* InShape, bool bWakeTouching) override final;`
- L62 _public prototype_ `UE_INTERNAL FShapeInstanceView& GetShapeInstanceView();`
- L64 _public prototype_ `UE_INTERNAL virtual void InitTransform(const FTransform& InTransform) override final;`
- L65 _public prototype_ `UE_INTERNAL virtual void UpdateTransform(const FTransform& InTransform) override final;`
- L66 _public prototype_ `UE_INTERNAL virtual void SetKinematicTarget(const FTransform& InTransform) override final;`
- L67 _public prototype_ `UE_INTERNAL virtual FTransform GetTransform() const override final;`
- L68 _public prototype_ `UE_INTERNAL virtual FBounds3d GetBounds() const override final;`
- L69 _public prototype_ `UE_INTERNAL virtual double GetMass() const override final;`
- L70 _public prototype_ `UE_INTERNAL virtual void SetMass(double InMass) override final;`
- L71 _public prototype_ `UE_INTERNAL virtual FVector3d GetInertia() const override final;`
- L72 _public prototype_ `UE_INTERNAL virtual void SetInertia(const FVector3d& InInertia) override final;`
- L81 _public prototype_ `UE_INTERNAL virtual void SetCenterOfMass(const FVector3d& InCenterOfMass) override final;` — UE_INTERNAL virtual void SetCCDEnabled(bool bInEnabled) override final {  } UE_INTERNAL virtual void SetMACDEnabled(bool bInEnabled) override final {  } UE_INTERNAL virtual void SetSmoothEdgeCollisionsEnabled(bool bInEnabled) override final {  } UE_INTERNAL virtual void SetMaxLinearVelocity(float InMax) override final {  } UE_INTERNAL virtual void SetMaxAngularVelocity(float InMax) override final {  } UE_INTERNAL virtual void SetInertiaConditioningEnabled(bool bInEnabled) override final {  } UE_INTERNAL virtual void SetGyroscopicTorqueEnabled(bool bInEnabled) override final {  } UE_INTERNAL virtual void SetGravityGroup(int32 InId) override final {  }
- L82 _public prototype_ `UE_INTERNAL virtual void SetRotationOfMass(const FQuat& InRotationOfMass) override final;`
- L83 _public prototype_ `UE_INTERNAL virtual void SetGravityScale(float InScale) override final;`
- L88 _public prototype_ `UE_INTERNAL virtual void SetIsSleeping(const bool bInSleeping) override final;` — UE_INTERNAL virtual void SetWakeEventsEnabled(bool bInEnabled) override final {  } UE_INTERNAL virtual void SetNumPositionIterations(int32 InNum) override final {  } UE_INTERNAL virtual void SetNumVelocityIterations(int32 InNum) override final {  } UE_INTERNAL virtual void SetNumProjectionIterations(int32 InNum) override final {  }
- L93 _public prototype_ `UE_INTERNAL bool IsValid() const;`
- L94 _public prototype_ `UE_INTERNAL const FSingleParticlePhysicsProxy* GetProxy() const;`
- L95 _public prototype_ `UE_INTERNAL FSingleParticlePhysicsProxy* GetProxy();`
- L96 _public prototype_ `UE_INTERNAL const FRigidBodyHandle_External& GetProxyAPI() const;`
- L97 _public prototype_ `UE_INTERNAL FRigidBodyHandle_External& GetProxyAPI();`
- L98 _public prototype_ `UE_INTERNAL FRigidSceneAsyncGT* GetScene() const;`
- L102 _private prototype_ `FRigidShapeInstanceAsync* CreateShapeInternal(Chaos::FPerShapeData* InShapeData);`
- L104 _private member_ `UE::Physics::FRigidObjectId BodyId;`
- L105 _private member_ `FRigidSceneAsyncGT* SceneAsync = nullptr;`
- L106 _private member_ `FSingleParticlePhysicsProxy* Proxy;`
- L107 _private member_ `FShapeInstanceView ShapeInstanceView;`

#### class `Chaos::Rigids::Async::FRigidBodyAsyncPT`  
`class UE_INTERNAL FRigidBodyAsyncPT : public UE::Physics::IRigidBody`  
_L111-169_
- inherits: `UE::Physics::IRigidBody`
- L114 _private function_ `inline FRigidBodyHandle_Internal* GetProxyAPI()`
- L119 _private function_ `inline const FRigidBodyHandle_Internal* GetProxyAPI() const`
- L127 _public prototype_ `UE_INTERNAL FRigidBodyAsyncPT( FRigidSceneAsyncPT* InScene, const UE::Physics::FRigidBodyHandle& InBodyHandle, FSingleParticlePhysicsProxy* InProxy);`
- L132 _public prototype_ `virtual ~FRigidBodyAsyncPT();`
- L137 _public prototype_ `UE_INTERNAL virtual UE::Physics::FRigidBodyHandle GetHandle() const override final;`
- L138 _public prototype_ `UE_INTERNAL virtual bool IsStatic() const override final;`
- L139 _public prototype_ `UE_INTERNAL virtual bool IsKinematic() const override final;`
- L140 _public prototype_ `UE_INTERNAL virtual bool IsDynamic() const override final;`
- L141 _public prototype_ `UE_INTERNAL virtual bool IsSleeping() const override final;`
- L143 _public prototype_ `UE_INTERNAL virtual int32 GetNumShapes() const override final;`
- L144 _public prototype_ `UE_INTERNAL virtual FRigidShapeInstanceAsync* GetShape(int32 InShapeIndex) const override final;`
- L145 _public prototype_ `UE_INTERNAL FShapeInstanceView& GetShapeInstanceView();`
- L146 _public prototype_ `UE_INTERNAL void UpdateShapeInstance(FRigidShapeInstanceAsync& ShapeInstance, const int32 InShapeIndex);`
- L148 _public prototype_ `UE_INTERNAL virtual void InitTransform(const FTransform& InTransform) override final;`
- L149 _public prototype_ `UE_INTERNAL virtual void UpdateTransform(const FTransform& InTransform) override final;`
- L150 _public prototype_ `UE_INTERNAL virtual void SetKinematicTarget(const FTransform& InTransform) override final;`
- L151 _public prototype_ `UE_INTERNAL virtual FTransform GetTransform() const override final;`
- L152 _public prototype_ `UE_INTERNAL virtual FBounds3d GetBounds() const override final;`
- L153 _public prototype_ `UE_INTERNAL virtual double GetMass() const override final;`
- L154 _public prototype_ `UE_INTERNAL virtual void SetMass(double InMass) override final;`
- L159 _public prototype_ `UE_INTERNAL bool IsValid() const;`
- L162 _private prototype_ `UE_INTERNAL void SetTransform(const FTransform& InTransform, bool bIsTeleport);`
- L163 _private prototype_ `const FString GetDebugName() const;`
- L165 _private member_ `FRigidSceneAsyncPT* Scene = nullptr;`
- L166 _private member_ `UE::Physics::FRigidBodyHandle Handle;`
- L167 _private member_ `FSingleParticlePhysicsProxy* Proxy;`
- L168 _private member_ `FShapeInstanceView ShapeInstanceView;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace Chaos`
- L17 _namespace_ `namespace Rigids` (scope `Chaos`)
- L17 _namespace_ `namespace Async` (scope `Chaos::Rigids`)

### `Plugins/Experimental/ChaosRigidPhysicsAsync/Source/ChaosRigidPhysicsAsync/Public/ChaosRigidPhysicsAsync/RigidFactoryAsync.h` (Public)


#### class `Chaos::Rigids::Async::FRigidFactoryAsync`  
`class FRigidFactoryAsync : public UE::Physics::IRigidFactory`  
_L16-27_
- inherits: `UE::Physics::IRigidFactory`
- desc: TODO_CHAOSAPI: We should be regsitering an instance of FRigidFactoryAsync with some kind of abstract factory system
- L19 _public prototype_ `FRigidFactoryAsync();`
- L20 _public prototype_ `virtual ~FRigidFactoryAsync();`
- L21 _public prototype_ `UE_INTERNAL virtual const UE::Physics::FRigidTypeId& GetSceneTypeId() const override final;`
- L22 _public prototype_ `UE_INTERNAL UE::Physics::FRigidSceneHandle CreateScene(const UE::Physics::FRigidDebugName& InName, const UE::Physics::IRigidSceneSettings* InSettings);`
- L23 _public prototype_ `UE_INTERNAL virtual void DestroyScene(const UE::Physics::FRigidSceneHandle& InSceneHandle) override final;`
- L26 _private member_ `TArray<UE::Physics::IRigidScene*> Scenes;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace Chaos`
- L11 _namespace_ `namespace Rigids` (scope `Chaos`)
- L11 _namespace_ `namespace Async` (scope `Chaos::Rigids`)

### `Plugins/Experimental/ChaosRigidPhysicsAsync/Source/ChaosRigidPhysicsAsync/Public/ChaosRigidPhysicsAsync/RigidFwdAsync.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Chaos`
- L8 _namespace_ `namespace Rigids` (scope `Chaos`)
- L8 _namespace_ `namespace Async` (scope `Chaos::Rigids`)
- L14 _namespace_ `namespace Chaos`
- L14 _namespace_ `namespace Rigids` (scope `Chaos`)
- L14 _namespace_ `namespace Async` (scope `Chaos::Rigids`)
- L28 _typedef_ `using UE_INTERNAL FJointConstraintHandle = UE::Physics::FJointConstraintHandle;` (scope `Chaos::Rigids::Async`)
- L29 _typedef_ `using UE_INTERNAL FJointConstraint6DOFHandle = UE::Physics::FJointConstraint6DOFHandle;` (scope `Chaos::Rigids::Async`)
- L30 _typedef_ `using UE_INTERNAL FJointConstraintRegistry = UE::Physics::FJointConstraintRegistry;` (scope `Chaos::Rigids::Async`)
- L31 _typedef_ `using UE_INTERNAL FRigidBodyHandle = UE::Physics::FRigidBodyHandle;` (scope `Chaos::Rigids::Async`)
- L32 _typedef_ `using UE_INTERNAL FRigidObjectId = UE::Physics::FRigidObjectId;` (scope `Chaos::Rigids::Async`)
- L33 _typedef_ `using UE_INTERNAL FRigidShapeInstanceHandle = UE::Physics::FRigidShapeInstanceHandle;` (scope `Chaos::Rigids::Async`)
- L34 _typedef_ `using UE_INTERNAL IJointConstraint = UE::Physics::IJointConstraint;` (scope `Chaos::Rigids::Async`)
- L35 _typedef_ `using UE_INTERNAL IJointConstraint6DOF = UE::Physics::IJointConstraint6DOF;` (scope `Chaos::Rigids::Async`)
- L36 _typedef_ `using UE_INTERNAL IRigidShapeInstance = UE::Physics::IRigidShapeInstance;` (scope `Chaos::Rigids::Async`)

### `Plugins/Experimental/ChaosRigidPhysicsAsync/Source/ChaosRigidPhysicsAsync/Public/ChaosRigidPhysicsAsync/RigidGeometryCollectionAsync.h` (Public)


#### class `Chaos::Rigids::Async::FRigidGeometryCollectionBodyAsyncGT`  
`class UE_INTERNAL FRigidGeometryCollectionBodyAsyncGT : public UE::Physics::IRigidBody`  
_L14-64_
- inherits: `UE::Physics::IRigidBody`
- L19 _public prototype_ `UE_INTERNAL FRigidGeometryCollectionBodyAsyncGT(FRigidGeometryCollectionAsyncGT* InGeometryCollection);`
- L21 _public prototype_ `virtual ~FRigidGeometryCollectionBodyAsyncGT();`
- L26 _public prototype_ `UE_INTERNAL virtual UE::Physics::FRigidBodyHandle GetHandle() const override final;`
- L27 _public prototype_ `UE_INTERNAL virtual bool IsActive() const override final;`
- L28 _public prototype_ `UE_INTERNAL virtual void Activate() override final;`
- L29 _public prototype_ `UE_INTERNAL virtual void Deactivate() override final;`
- L30 _public prototype_ `UE_INTERNAL virtual bool IsStatic() const override final;`
- L31 _public prototype_ `UE_INTERNAL virtual bool IsKinematic() const override final;`
- L32 _public prototype_ `UE_INTERNAL virtual bool IsDynamic() const override final;`
- L33 _public prototype_ `UE_INTERNAL virtual bool IsSleeping() const override final;`
- L34 _public prototype_ `UE_INTERNAL virtual int32 GetNumShapes() const override final;`
- L35 _public prototype_ `UE_INTERNAL virtual UE::Physics::IRigidShapeInstance* GetShape(int32 InShapeIndex) const override final;`

#### class `Chaos::Rigids::Async::FRigidGeometryCollectionBodyAsyncPT`  
`class UE_INTERNAL FRigidGeometryCollectionBodyAsyncPT : public UE::Physics::IRigidBody`  
_L66-116_
- inherits: `UE::Physics::IRigidBody`
- L71 _public prototype_ `UE_INTERNAL FRigidGeometryCollectionBodyAsyncPT(FRigidGeometryCollectionAsyncPT* InGeometryCollection);`
- L73 _public prototype_ `virtual ~FRigidGeometryCollectionBodyAsyncPT();`
- L78 _public prototype_ `UE_INTERNAL virtual UE::Physics::FRigidBodyHandle GetHandle() const override final;`
- L79 _public prototype_ `UE_INTERNAL virtual bool IsActive() const override final;`
- L80 _public prototype_ `UE_INTERNAL virtual void Activate() override final;`
- L81 _public prototype_ `UE_INTERNAL virtual void Deactivate() override final;`
- L82 _public prototype_ `UE_INTERNAL virtual bool IsStatic() const override final;`
- L83 _public prototype_ `UE_INTERNAL virtual bool IsKinematic() const override final;`
- L84 _public prototype_ `UE_INTERNAL virtual bool IsDynamic() const override final;`
- L85 _public prototype_ `UE_INTERNAL virtual bool IsSleeping() const override final;`
- L86 _public prototype_ `UE_INTERNAL virtual int32 GetNumShapes() const override final;`
- L87 _public prototype_ `UE_INTERNAL virtual UE::Physics::IRigidShapeInstance* GetShape(int32 InShapeIndex) const override final;`

#### class `Chaos::Rigids::Async::FRigidGeometryCollectionAsyncGT`  
`class UE_INTERNAL FRigidGeometryCollectionAsyncGT : public UE::Physics::IRigidGeometryCollection`  
_L123-163_
- inherits: `UE::Physics::IRigidGeometryCollection`
- desc: The full rigid body API. There will be several implementations of this API. E.g., synchronous physics, asynchronous physics, immediate physics, remote physics, etc. NOTE: for some implementations like async physics, there are both Game- and Physics-Context implementations within the async implementation. Pinning a handle will return the object appropriate for the context.
- L128 _public prototype_ `FRigidGeometryCollectionAsyncGT(FRigidSceneAsyncGT* InScene, const UE::Physics::FRigidDebugName& InName, const FSimulationParameters& InParameters);`
- L129 _public prototype_ `virtual ~FRigidGeometryCollectionAsyncGT();`
- L134 _public prototype_ `UE_INTERNAL virtual UE::Physics::FRigidBodyContainerHandle GetHandle() const override final;`
- L135 _public prototype_ `UE_INTERNAL virtual int32 GetNumBodies() const override final;`
- L136 _public prototype_ `UE_INTERNAL virtual FRigidGeometryCollectionBodyAsyncGT* GetBody(const UE::Physics::FRigidObjectId& InBodyId) const override final;`
- L137 _public prototype_ `UE_INTERNAL virtual void SetId(const UE::Physics::FRigidObjectId& InBodyContainerId) override final;`
- L145 _public prototype_ `UE_INTERNAL virtual FRigidGeometryCollectionBodyAsyncGT* GetBodyAt(int32 BodyIndex) const override final;`
- L152 _public function_ `UE_INTERNAL FGeometryCollectionPhysicsProxy* GetProxy() const`
- L158 _private member_ `UE::Physics::FRigidDebugName Name;`
- L159 _private member_ `UE::Physics::FRigidObjectId BodyContainerId;`
- L160 _private member_ `TSharedPtr<FGeometryCollection> RestCollection;`
- L161 _private member_ `FRigidSceneAsyncGT* Scene;`
- L162 _private member_ `FGeometryCollectionPhysicsProxy* Proxy;`

#### class `Chaos::Rigids::Async::FRigidGeometryCollectionAsyncPT`  
`class UE_INTERNAL FRigidGeometryCollectionAsyncPT : public UE::Physics::IRigidGeometryCollection`  
_L165-202_
- inherits: `UE::Physics::IRigidGeometryCollection`
- L170 _public prototype_ `FRigidGeometryCollectionAsyncPT(FRigidSceneAsyncPT* InScene, const UE::Physics::FRigidObjectId& InId, FGeometryCollectionPhysicsProxy* InProxy);`
- L171 _public prototype_ `virtual ~FRigidGeometryCollectionAsyncPT();`
- L176 _public prototype_ `UE_INTERNAL virtual UE::Physics::FRigidBodyContainerHandle GetHandle() const override final;`
- L177 _public prototype_ `UE_INTERNAL virtual int32 GetNumBodies() const override final;`
- L178 _public prototype_ `UE_INTERNAL virtual FRigidGeometryCollectionBodyAsyncGT* GetBody(const UE::Physics::FRigidObjectId& InBodyId) const override final;`
- L179 _public prototype_ `UE_INTERNAL virtual void SetId(const UE::Physics::FRigidObjectId& InBodyContainerId) override final;`
- L187 _public prototype_ `UE_INTERNAL virtual FRigidGeometryCollectionBodyAsyncGT* GetBodyAt(int32 BodyIndex) const override final;`
- L193 _public function_ `UE_INTERNAL FGeometryCollectionPhysicsProxy* GetProxy() const`
- L199 _private member_ `UE::Physics::FRigidObjectId BodyContainerId;`
- L200 _private member_ `FRigidSceneAsyncPT* Scene;`
- L201 _private member_ `FGeometryCollectionPhysicsProxy* Proxy;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Chaos`
- L12 _namespace_ `namespace Rigids` (scope `Chaos`)
- L12 _namespace_ `namespace Async` (scope `Chaos::Rigids`)

### `Plugins/Experimental/ChaosRigidPhysicsAsync/Source/ChaosRigidPhysicsAsync/Public/ChaosRigidPhysicsAsync/RigidSceneAsync.h` (Public)


#### class `Chaos::Rigids::Async::FRigidSceneAsyncGT`  
`class UE_INTERNAL FRigidSceneAsyncGT : public UE::Physics::FRigidScene , public TSharedFromThis<FRigidSceneAsyncGT, ESPMode::ThreadSafe>`  
_L44-144_
- inherits: `UE::Physics::FRigidScene,TSharedFromThis<FRigidSceneAsyncGT,ESPMode::ThreadSafe>`
- L51 _public prototype_ `UE_INTERNAL FRigidSceneAsyncGT( const UE::Physics::FRigidDebugName& InName, const FRigidSceneSettingsAsync& InSceneSettings);`
- L54 _public prototype_ `virtual ~FRigidSceneAsyncGT();`
- L60 _protected prototype_ `UE_INTERNAL virtual void Lock(UE::Physics::ERigidLockType InLockType) const override final;`
- L61 _protected prototype_ `UE_INTERNAL virtual void Unlock(UE::Physics::ERigidLockType InLockType) const override final;`
- L71 _public prototype_ `UE_INTERNAL virtual UE::Physics::FRigidSceneId GetId() const override final;`
- L72 _public prototype_ `UE_INTERNAL void SetId(const UE::Physics::FRigidSceneId InId);`
- L73 _public prototype_ `UE_INTERNAL virtual UE::Physics::FRigidSceneHandle GetHandle() const override final;`
- L74 _public prototype_ `UE_INTERNAL virtual void RegisterModifier(UE::Physics::IRigidSceneModifier* Modifier) override final;`
- L75 _public prototype_ `UE_INTERNAL virtual void UnregisterModifier(UE::Physics::IRigidSceneModifier* Modifier) override final;`
- L76 _public prototype_ `UE_INTERNAL virtual bool Query(const UE::Physics::FRigidQueryDesc& QueryDesc, TArray<UE::Physics::FRigidQueryHit>& OutHits) override final;`
- L77 _public prototype_ `UE_INTERNAL virtual void StartTick(const float InDt) override final;`
- L78 _public prototype_ `UE_INTERNAL virtual void WaitOnTick() override final;`
- L79 _public prototype_ `UE_INTERNAL virtual void EndTick() override final;`
- L80 _public prototype_ `UE_INTERNAL virtual FRigidBodyAsyncGT* CreateBody(const UE::Physics::FRigidDebugName& InName, UE::Physics::ERigidMovementType InMovementType) override final;`
- L81 _public prototype_ `UE_INTERNAL virtual void DestroyBody(UE::Physics::IRigidBody* InBody) override final;`
- L82 _public prototype_ `UE_INTERNAL virtual FRigidGeometryCollectionAsyncGT* CreateGeometryCollection(const UE::Physics::FRigidDebugName& InName, const FSimulationParameters& InParameters) override final;`
- L83 _public prototype_ `UE_INTERNAL virtual void DestroyGeometryCollection(UE::Physics::IRigidGeometryCollection* InGC) override final;`
- L85 _public prototype_ `UE_INTERNAL virtual void AddDisabledCollisions(const TMap<UE::Physics::FRigidBodyHandle, TArray<UE::Physics::FRigidBodyHandle>>& InMap) override final;`
- L91 _public prototype_ `UE_INTERNAL FRigidShapeInstanceAsync* AllocateShape();` — ShapeInstance
- L92 _public prototype_ `UE_INTERNAL void DestroyShape(FRigidShapeInstanceAsync* InShape);`
- L93 _public prototype_ `UE_INTERNAL virtual FRigidShapeInstanceAsync* GetShape(const FRigidObjectId& InId) const override final;`
- L95 _public prototype_ `UE_INTERNAL void AddShape(FRigidBodyAsyncGT& Body, FRigidShapeInstanceAsync& InShapeInstance);` — ShapeInstance: Body
- L96 _public prototype_ `UE_INTERNAL void RemoveShape(FRigidBodyAsyncGT& Body, FRigidShapeInstanceAsync& InShapeInstance);`
- L97 _public prototype_ `UE_INTERNAL FRigidShapeInstanceAsync* GetShape(const FShapeInstanceView& InView, const int32 InIndex) const;`
- L100 _public prototype_ `UE_INTERNAL virtual FJointConstraint6DOFAsyncGT* CreateJointConstraint6DOF() override final;` — Joint Constraint
- L101 _public prototype_ `UE_INTERNAL virtual void DestroyJointConstraint(IJointConstraint* InConstraint) override final;`
- L102 _public prototype_ `UE_INTERNAL virtual IJointConstraint* GetJointConstraint(const FRigidObjectId& InConstraintId) const override final;`
- L103 _public prototype_ `UE_INTERNAL void ActivateConstraint(FJointConstraint6DOFAsyncGT* InConstraint);`
- L104 _public prototype_ `UE_INTERNAL void DeactivateConstraint(FJointConstraint6DOFAsyncGT* InConstraint);`
- L107 _public prototype_ `UE_INTERNAL void Startup();`
- L108 _public prototype_ `UE_INTERNAL void Shutdown();`
- L109 _public prototype_ `UE_INTERNAL void RegisterBody(UE::Physics::IRigidBody* InBody);`
- L110 _public prototype_ `UE_INTERNAL void UnRegisterBody(const UE::Physics::FRigidBodyHandle& InBodyHandle, const UE::Physics::IRigidBody* InBody);`
- L111 _public prototype_ `UE_INTERNAL void RegisterBodyContainer(UE::Physics::IRigidBodyContainer* InContainer);`
- L112 _public prototype_ `UE_INTERNAL void UnregisterBodyContainer(UE::Physics::IRigidBodyContainer* InContainer);`
- L113 _public prototype_ `UE_INTERNAL void ActivateBody(FRigidBodyAsyncGT* InBody);`
- L114 _public prototype_ `UE_INTERNAL void DeactivateBody(FRigidBodyAsyncGT* InBody);`
- L115 _public prototype_ `UE_INTERNAL void OnRigidBodyTransformUpdated(FRigidBodyAsyncGT* Body);`
- L118 _private prototype_ `void CheckGameReadLocked() const;`
- L119 _private prototype_ `void CheckGameWriteLocked() const;`
- L120 _private prototype_ `void ConstructScene();`
- L121 _private prototype_ `void DestructScene();`
- L122 _private prototype_ `void OnPreSimulate(FReal Dt);`
- L123 _private prototype_ `void OnPostSimulate();`
- L124 _private prototype_ `void UpdateRigidBodyInAccelerationStructure(FRigidBodyAsyncGT* Body);`
- L125 _private prototype_ `FPBDRigidsSolver* GetSolver() const;`
- L127 _private member_ `UE::Physics::FRigidDebugName Name;`
- L129 _private member_ `FRigidSceneSettingsAsync SceneSettings;`
- L130 _private member_ `UE::Physics::FRigidSceneId SceneId;`
- L132 _private member_ `FChaosScene* Scene;`
- L133 _private member_ `TStrongObjectPtr<UObject> Owner;`
- L135 _private member_ `TObjectPool<FRigidBodyAsyncGT> BodyPool;`
- L137 _private member_ `TArray<UE::Physics::IRigidSceneModifier*> SceneModifiers;`
- L139 _private member_ `TUniquePtr<FRigidSceneAsyncPT> ScenePT;`
- L140 _private member_ `FShapeInstanceContainerAsyncGT ShapeInstanceContainer;`
- L143 _private member_ `bool bOwnsScene;` — TODO_CHAOSAPI: Temp until Scene is always created through new API

#### class `Chaos::Rigids::Async::FRigidSceneAsyncPT`  
`class UE_INTERNAL FRigidSceneAsyncPT : public UE::Physics::IRigidScene`  
_L147-228_
- inherits: `UE::Physics::IRigidScene`
- L152 _public prototype_ `UE_INTERNAL FRigidSceneAsyncPT(const UE::Physics::FRigidDebugName& InName);`
- L154 _public prototype_ `virtual ~FRigidSceneAsyncPT();`
- L160 _protected prototype_ `UE_INTERNAL virtual void Lock(UE::Physics::ERigidLockType InLockType) const override final;`
- L161 _protected prototype_ `UE_INTERNAL virtual void Unlock(UE::Physics::ERigidLockType InLockType) const override final;`
- L170 _public prototype_ `UE_INTERNAL virtual UE::Physics::FRigidSceneId GetId() const override final;`
- L171 _public prototype_ `UE_INTERNAL virtual UE::Physics::FRigidSceneHandle GetHandle() const override final;`
- L172 _public prototype_ `UE_INTERNAL virtual UE::Physics::IRigidBody* GetBody(const UE::Physics::FRigidObjectId& InBodyId) const override final;`
- L173 _public prototype_ `UE_INTERNAL virtual UE::Physics::IRigidBodyContainer* GetBodyContainer(const UE::Physics::FRigidObjectId& InBodyContainerId) const override final;`
- L174 _public prototype_ `UE_INTERNAL virtual FRigidGeometryCollectionAsyncPT* GetGeometryCollection(const UE::Physics::FRigidObjectId& InGeometryCollectionId) const override final;`
- L175 _public prototype_ `UE_INTERNAL virtual void RegisterModifier(UE::Physics::IRigidSceneModifier* Modifier) override final;`
- L176 _public prototype_ `UE_INTERNAL virtual void UnregisterModifier(UE::Physics::IRigidSceneModifier* Modifier) override final;`
- L177 _public prototype_ `UE_INTERNAL virtual bool Query(const UE::Physics::FRigidQueryDesc& QueryDesc, TArray<UE::Physics::FRigidQueryHit>& OutHits) override final;`
- L183 _public prototype_ `UE_INTERNAL UE::Physics::FRigidSceneHandle GetSceneHandle() const;`
- L184 _public prototype_ `UE_INTERNAL void Startup(UE::Physics::FRigidSceneHandle InSceneHandle, FPBDRigidsSolver* InSolver);`
- L185 _public prototype_ `UE_INTERNAL void Shutdown();`
- L186 _public prototype_ `UE_INTERNAL void RegisterBodyContainer(UE::Physics::IRigidBodyContainer* InContainer);`
- L187 _public prototype_ `UE_INTERNAL void UnregisterBodyContainer(UE::Physics::IRigidBodyContainer* InContainer);`
- L188 _public prototype_ `UE_INTERNAL void CreateGeometryCollectionPT(const UE::Physics::FRigidBodyContainerHandle& InHandle, FGeometryCollectionPhysicsProxy* InProxy);`
- L189 _public prototype_ `UE_INTERNAL void DestroyGeometryCollectionPT(const UE::Physics::FRigidBodyContainerHandle& InHandle);`
- L190 _public prototype_ `UE_INTERNAL void CreateBodyPT(const UE::Physics::FRigidBodyHandle& InBodyHandle, FSingleParticlePhysicsProxy* InProxy);`
- L191 _public prototype_ `UE_INTERNAL void DestroyBodyPT(const UE::Physics::FRigidBodyHandle& InBodyHandle);`
- L192 _public prototype_ `UE_INTERNAL void RegisterBody(const UE::Physics::FRigidBodyHandle& InBodyHandle, UE::Physics::IRigidBody* InBody);`
- L193 _public prototype_ `UE_INTERNAL void UnRegisterBody(const UE::Physics::FRigidBodyHandle& InBodyHandle, const UE::Physics::IRigidBody* InBody);`
- L194 _public prototype_ `UE_INTERNAL void ActivateBody(const UE::Physics::FRigidBodyHandle& InBodyHandle);`
- L195 _public prototype_ `UE_INTERNAL void DeactivateBody(const UE::Physics::FRigidBodyHandle& InBodyHandle);`
- L198 _public prototype_ `UE_INTERNAL virtual FRigidShapeInstanceAsync* GetShape(const FRigidObjectId& InId) const override final;` — ShapeInstance
- L200 _public prototype_ `UE_INTERNAL void AddShapePT(const FRigidBodyHandle BodyHandle, const FRigidShapeInstanceHandle ShapeInstanceHandle, const int32 ShapeIndex);` — ShapeInstance: Body
- L201 _public prototype_ `UE_INTERNAL void RemoveShapePT(const FRigidBodyHandle BodyHandle, const FRigidShapeInstanceHandle ShapeInstanceHandle);`
- L202 _public prototype_ `UE_INTERNAL FRigidShapeInstanceAsync* GetShape(const FShapeInstanceView& InView, const int32 InIndex) const;`
- L205 _public prototype_ `UE_INTERNAL FJointConstraint6DOFAsyncPT* CreateJointConstraint6DOFPT(const FJointConstraint6DOFHandle& InHandle, Chaos::FJointConstraint* InJointConstraint);` — Joint Constraint
- L206 _public prototype_ `UE_INTERNAL void DestroyJointConstraintPT(const FJointConstraint6DOFHandle& InHandle);`
- L207 _public prototype_ `UE_INTERNAL virtual IJointConstraint* GetJointConstraint(const FRigidObjectId& InConstraintId) const override final;`
- L208 _public prototype_ `UE_INTERNAL void ActiveJointConstraint(const FJointConstraint6DOFHandle& InHandle);`
- L209 _public prototype_ `UE_INTERNAL void DeactivateJointConstraint(const FJointConstraint6DOFHandle& InHandle);`
- L212 _private prototype_ `void CheckGameContext() const;`
- L213 _private prototype_ `void CheckSimContext() const;`
- L215 _private prototype_ `void OnPreTick(FReal Dt);`
- L216 _private prototype_ `void OnPostTick(FReal Dt);`
- L218 _private member_ `UE::Physics::FRigidDebugName Name;`
- L219 _private member_ `UE::Physics::FRigidSceneHandle SceneHandle;`
- L220 _private member_ `FPBDRigidsSolver* Solver;`
- L221 _private member_ `TObjectPool<FRigidBodyAsyncPT> BodyPool;`
- L222 _private member_ `TMap<UE::Physics::FRigidObjectId, UE::Physics::IRigidBodyContainer*> BodyContainerRegistry;`
- L223 _private member_ `TMap<UE::Physics::FRigidObjectId, UE::Physics::IRigidBody*> BodyRegistry;`
- L224 _private member_ `TMap<UE::Physics::FRigidObjectId, UE::Physics::IJointConstraint*> JointConstraintRegistry;`
- L225 _private member_ `FShapeInstanceContainerAsyncPT ShapeInstanceContainer;`
- L226 _private member_ `TArray<UE::Physics::IRigidSceneModifier*> SceneModifiers;`
- L227 _private member_ `bool bIsStarted;`

#### Free symbols / members of external scopes

- L26 _namespace_ `namespace Chaos`
- L31 _namespace_ `namespace Chaos`
- L31 _namespace_ `namespace Rigids` (scope `Chaos`)
- L31 _namespace_ `namespace Async` (scope `Chaos::Rigids`)

### `Plugins/Experimental/ChaosRigidPhysicsAsync/Source/ChaosRigidPhysicsAsync/Public/ChaosRigidPhysicsAsync/RigidSceneSettingsAsync.h` (Public)


#### class `Chaos::Rigids::Async::FRigidSceneSettingsAsync`  
`class UE_INTERNAL FRigidSceneSettingsAsync : public UE::Physics::IRigidSceneSettings`  
_L20-33_
- inherits: `UE::Physics::IRigidSceneSettings`
- L26 _public member_ `float AsyncDt = -1.0f;` — The fixed timestep to use when async physics is enabled
- L29 _public member_ `EChaosThreadingMode ThreadingMode = EChaosThreadingMode::SingleThread;` — The threading mode
- L32 _public member_ `FChaosSolverConfiguration SolverConfig;` — Solver settings

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Chaos`
- L18 _namespace_ `namespace Chaos`
- L18 _namespace_ `namespace Rigids` (scope `Chaos`)
- L18 _namespace_ `namespace Async` (scope `Chaos::Rigids`)

### `Plugins/Experimental/ChaosRigidPhysicsAsync/Source/ChaosRigidPhysicsAsync/Public/ChaosRigidPhysicsAsync/RigidShapeInstanceAsync.h` (Public)


#### class `Chaos::Rigids::Async::FRigidShapeInstanceAsync`  
`class UE_INTERNAL FRigidShapeInstanceAsync : public UE::Physics::IRigidShapeInstance`  
_L14-74_
- inherits: `UE::Physics::IRigidShapeInstance`
- L16 _private typedef_ `using FShapeFilterData = Chaos::Filter::FShapeFilterData;`
- L20 _public prototype_ `FRigidShapeInstanceAsync() = default;`
- L21 _public prototype_ `virtual ~FRigidShapeInstanceAsync() = default;`
- L23 _public prototype_ `UE_INTERNAL static Chaos::FPerShapeData* Create(const UE::Physics::FRigidShapeInstanceSetup& InSetup);`
- L25 _public prototype_ `UE_INTERNAL virtual UE::Physics::FRigidShapeInstanceHandle GetHandle() const override final;`
- L26 _public prototype_ `UE_INTERNAL virtual UE::Physics::FAnyGeometry GetGeometry() const override final;`
- L28 _public prototype_ `UE_INTERNAL virtual FTransform3f GetLocalTransform() const override final;`
- L30 _public prototype_ `UE_INTERNAL virtual bool GetQueryEnabled() const override final;`
- L31 _public prototype_ `UE_INTERNAL virtual void SetQueryEnabled(const bool bInEnabled) override final;`
- L33 _public prototype_ `UE_INTERNAL virtual bool GetSimEnabled() const override final;`
- L34 _public prototype_ `UE_INTERNAL virtual void SetSimEnabled(const bool bInEnabled) override final;`
- L36 _public prototype_ `UE_INTERNAL virtual bool GetIsProbe() const override final;`
- L37 _public prototype_ `UE_INTERNAL virtual void SetIsProbe(const bool bInIsProbe) override final;`
- L39 _public prototype_ `UE_INTERNAL virtual ECollisionTraceFlag GetCollisionTraceType() const override final;`
- L40 _public prototype_ `UE_INTERNAL virtual void SetCollisionTraceType(const ECollisionTraceFlag InTraceFlag) override final;`
- L42 _public prototype_ `UE_INTERNAL virtual FShapeFilterData GetShapeFilter() const override final;`
- L43 _public prototype_ `UE_INTERNAL virtual void SetShapeFilter(const FShapeFilterData& InShapeFilter) override final;`
- L45 _public prototype_ `UE_INTERNAL virtual Chaos::Filter::FInstanceData GetFilterInstanceData() const override final;`
- L46 _public prototype_ `UE_INTERNAL virtual void SetFilterInstanceData(const Chaos::Filter::FInstanceData& InInstanceData) override final;`
- L48 _public prototype_ `UE_INTERNAL virtual int32 GetNumMaterials() const override final;`
- L49 _public prototype_ `UE_INTERNAL virtual UE::Physics::FMaterialHandle GetMaterial(const int32 InIndex) const override final;`
- L50 _public prototype_ `UE_INTERNAL virtual void SetMaterials(TArray<UE::Physics::FMaterialHandle>&& InMaterials) override final;`
- L52 _public prototype_ `UE_INTERNAL virtual int32 GetNumMaterialMasks() const override final;`
- L53 _public prototype_ `UE_INTERNAL virtual UE::Physics::FMaterialMaskHandle GetMaterialMask(const int32 InIndex) const override final;`
- L54 _public prototype_ `UE_INTERNAL virtual void SetMaterialMasks(TArray<UE::Physics::FMaterialMaskHandle>&& InMaterialMasks) override final;`
- L56 _public prototype_ `UE_INTERNAL virtual int32 GetNumMaterialMaskMaps() const override final;`
- L57 _public prototype_ `UE_INTERNAL virtual uint32 GetMaterialMaskMap(const int32 InIndex) const override final;`
- L58 _public prototype_ `UE_INTERNAL virtual void SetMaterialMaskMaps(TArray<uint32>&& InMaterialMaskMaps) override final;`
- L60 _public prototype_ `UE_INTERNAL virtual int32 GetNumMaterialMaskMapMaterials() const override final;`
- L61 _public prototype_ `UE_INTERNAL virtual UE::Physics::FMaterialHandle GetMaterialMaskMapMaterial(const int32 InIndex) const override final;`
- L62 _public prototype_ `UE_INTERNAL virtual void SetMaterialMaskMapMaterials(TArray<UE::Physics::FMaterialHandle>&& InMaterialMaskMapMaterials) override final;`
- L64 _public prototype_ `UE_INTERNAL virtual void* GetUserData() const override final;`
- L65 _public prototype_ `UE_INTERNAL virtual void SetUserData(void* InUserData) override final;`
- L67 _public member_ `UE_INTERNAL Chaos::FPerShapeData* PerShapeData = nullptr;`
- L68 _public member_ `UE_INTERNAL UE::Physics::FRigidShapeInstanceHandle Handle;`
- L69 _public member_ `UE_INTERNAL bool bAttachedToBody = false;`
- L73 _private prototype_ `template <typename Lambda> static EImplicitObjectType GetLeafImplicit(FImplicitObject*& InOutImplicit, const Lambda& Func);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace Chaos`
- L12 _namespace_ `namespace Rigids` (scope `Chaos`)
- L12 _namespace_ `namespace Async` (scope `Chaos::Rigids`)

### `Plugins/Experimental/ChaosRigidPhysicsAsync/Source/ChaosRigidPhysicsAsync/Public/ChaosRigidPhysicsAsync/ShapeInstanceContainerAsync.h` (Public)


#### class `Chaos::Rigids::Async::FShapeInstanceView`  
`class UE_INTERNAL FShapeInstanceView`  
_L15-24_
- L18 _public prototype_ `int32 Num() const;`
- L23 _private member_ `TArray<UE::Physics::FRigidObjectId> Ids;`

#### class `Chaos::Rigids::Async::FShapeInstanceContainerAsyncGT`  
`class UE_INTERNAL FShapeInstanceContainerAsyncGT`  
_L26-46_
- L28 _private typedef_ `using FRigidObjectId = UE::Physics::FRigidObjectId;`
- L29 _private typedef_ `using FRigidSceneId = UE::Physics::FRigidSceneId;`
- L31 _public prototype_ `FShapeInstanceContainerAsyncGT();`
- L33 _public prototype_ `FRigidShapeInstanceAsync* Allocate(const FRigidSceneId InSceneId);`
- L34 _public prototype_ `void Free(FRigidShapeInstanceAsync* InInstance);`
- L36 _public prototype_ `FRigidShapeInstanceAsync* Find(const FRigidObjectId& InId) const;`
- L38 _public prototype_ `int32 Add(FRigidShapeInstanceAsync& InInstance, FShapeInstanceView& InOutView);`
- L39 _public prototype_ `void Remove(FRigidShapeInstanceAsync& InInstance, FShapeInstanceView& InOutView);`
- L40 _public prototype_ `FRigidShapeInstanceAsync* Get(const FShapeInstanceView& InView, const int32 InIndex) const;`
- L41 _public prototype_ `void Free(FShapeInstanceView& InView);`
- L44 _private member_ `TObjectPool<FRigidShapeInstanceAsync> Pool;`
- L45 _private member_ `UE::Physics::TRigidObjectRegistry<FRigidShapeInstanceAsync> Registry;`

#### class `Chaos::Rigids::Async::FShapeInstanceContainerAsyncPT`  
`class UE_INTERNAL FShapeInstanceContainerAsyncPT`  
_L48-76_
- L50 _private typedef_ `using FRigidObjectId = UE::Physics::FRigidObjectId;`
- L51 _private typedef_ `using FRigidSceneId = UE::Physics::FRigidSceneId;`
- L52 _private typedef_ `using FRigidShapeInstanceHandle = UE::Physics::FRigidShapeInstanceHandle;`
- L55 _public prototype_ `FShapeInstanceContainerAsyncPT();`
- L57 _public prototype_ `FRigidShapeInstanceAsync* Allocate(const FRigidShapeInstanceHandle& InHandle);`
- L58 _public prototype_ `void Free(FRigidShapeInstanceAsync* InInstance);`
- L60 _public prototype_ `FRigidShapeInstanceAsync* Find(const FRigidObjectId& InId) const;`
- L62 _public prototype_ `void Add(FRigidShapeInstanceAsync& InInstance, const int32 InShapeIndex, FShapeInstanceView& InOutView);`
- L63 _public prototype_ `void Remove(FRigidShapeInstanceAsync& InInstance, FShapeInstanceView& InOutView);`
- L64 _public prototype_ `FRigidShapeInstanceAsync* Get(const FShapeInstanceView& InView, const int32 InIndex) const;`
- L65 _public prototype_ `void Free(FShapeInstanceView& InView);`
- L74 _private member_ `TObjectPool<FRigidShapeInstanceAsync> Pool;`
- L75 _private member_ `TArray<FRegistryItem> Registry;`

#### struct `Chaos::Rigids::Async::FShapeInstanceContainerAsyncPT::FRegistryItem`  
`struct FRegistryItem`  
_L68-72_
- L70 _public member_ `FRigidShapeInstanceAsync* Object = nullptr;`
- L71 _public member_ `int32 Epoch = 0;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace Chaos`
- L13 _namespace_ `namespace Rigids` (scope `Chaos`)
- L13 _namespace_ `namespace Async` (scope `Chaos::Rigids`)
