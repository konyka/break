# Runtime / RigidPhysics

- module root: `Source/Runtime/Experimental/RigidPhysics`
- headers: 43; symbols: 941
- symbol kinds: class=48, enum=7, enumerator=19, function=251, macro=14, member=89, namespace=95, prototype=364, struct=3, typedef=51
- PublicDependencyModuleNames: Core, CoreUObject

### `Source/Runtime/Experimental/RigidPhysics/Public/RigidPhysics/Geometry/AnyGeometry.h` (Public)


#### class `UE::Physics::FAnyGeometry`  
`class FAnyGeometry`  
_L17-87_
- L20 _public prototype_ `FAnyGeometry() = default;`
- L21 _public prototype_ `FAnyGeometry(const FAnyGeometry&) = default;`
- L22 _public prototype_ `FAnyGeometry(FAnyGeometry&&) = default;`
- L25 _public function_ `template <typename GeometryType> FAnyGeometry(const GeometryType& InGeometry)`
- L30 _public prototype_ `FAnyGeometry& operator=(const FAnyGeometry& InGeometry) = default;`
- L33 _public function_ `template <typename GeometryType> FAnyGeometry& operator=(const GeometryType& InGeometry)`
- L39 _public prototype_ `bool operator==(const FAnyGeometry& Rhs) const;`
- L40 _public prototype_ `bool operator!=(const FAnyGeometry& Rhs) const = default;`
- L43 _public function_ `template <typename GeometryType> bool IsA() const`
- L49 _public function_ `template <typename GeometryType> GeometryType& Get()`
- L55 _public function_ `template <typename GeometryType> const GeometryType& Get() const`
- L61 _public function_ `template <typename GeometryType> GeometryType* TryGet()`
- L67 _public function_ `template <typename GeometryType> const GeometryType* TryGet() const`
- L73 _public function_ `template <typename TLambda> decltype(auto) Visit(const TLambda& Lambda)`
- L79 _public function_ `template <typename TLambda> decltype(auto) Visit(const TLambda& Lambda) const`
- L84 _public prototype_ `FString ToString() const;`
- L86 _private member_ `TVariant<FSphereGeometry, FBoxGeometry, FCapsuleGeometry, FConvexGeometry, FTriangleMeshGeometry, FHeightFieldGeometry> Geometry;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Physics` (scope `UE`)

### `Source/Runtime/Experimental/RigidPhysics/Public/RigidPhysics/Geometry/CommonCoreGeometry.h` (Public)


#### struct `UE::Physics::FSphereGeometry`  
`struct FSphereGeometry`  
_L13-28_
- L15 _public prototype_ `FSphereGeometry() = default;`
- L16 _public prototype_ `FSphereGeometry(const float InRadius);`
- L18 _public prototype_ `bool operator==(const FSphereGeometry&) const = default;`
- L19 _public prototype_ `bool operator!=(const FSphereGeometry&) const = default;`
- L21 _public prototype_ `float GetRadius() const;`
- L22 _public prototype_ `void SetRadius(float InRadius);`
- L24 _public prototype_ `FString ToString() const;`
- L27 _private member_ `float Radius = 0;`

#### struct `UE::Physics::FBoxGeometry`  
`struct FBoxGeometry`  
_L30-45_
- L32 _public prototype_ `FBoxGeometry() = default;`
- L33 _public prototype_ `FBoxGeometry(const FVector3f& InExtents);`
- L35 _public prototype_ `bool operator==(const FBoxGeometry&) const = default;`
- L36 _public prototype_ `bool operator!=(const FBoxGeometry&) const = default;`
- L38 _public prototype_ `FVector3f GetExtents() const;`
- L39 _public prototype_ `void SetExtents(const FVector3f& InExtents);`
- L41 _public prototype_ `FString ToString() const;`
- L44 _private member_ `FVector3f Extents = FVector3f::Zero();`

#### struct `UE::Physics::FCapsuleGeometry`  
`struct FCapsuleGeometry`  
_L47-66_
- L49 _public prototype_ `FCapsuleGeometry() = default;`
- L50 _public prototype_ `FCapsuleGeometry(float InRadius, float InSegmentHalfLength);`
- L52 _public prototype_ `bool operator==(const FCapsuleGeometry&) const = default;`
- L53 _public prototype_ `bool operator!=(const FCapsuleGeometry&) const = default;`
- L55 _public prototype_ `float GetRadius() const;`
- L56 _public prototype_ `void SetRadius(const float InRadius);`
- L58 _public prototype_ `float GetSegmentHalfLength() const;`
- L59 _public prototype_ `void SetSegmentHalfLength(const float InHalfLength);`
- L61 _public prototype_ `FString ToString() const;`
- L64 _private member_ `float Radius = 0;`
- L65 _private member_ `float SegmentHalfLength = 0;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Physics` (scope `UE`)

### `Source/Runtime/Experimental/RigidPhysics/Public/RigidPhysics/Geometry/ConvexGeometry.h` (Public)


#### class `UE::Physics::FConvexGeometrySetup`  
`class FConvexGeometrySetup`  
_L16-30_
- L27 _public member_ `TArray<FVector3f> Vertices;`
- L28 _public member_ `float Margin = 0.f;`
- L29 _public member_ `EBuildMethod BuildMethod = EBuildMethod::Default;`

#### enum `UE::Physics::FConvexGeometrySetup::EBuildMethod`  
`enum class EBuildMethod : uint8`  
_L19-25_
- L21 _public enumerator_ `Default = 0`
- L22 _public enumerator_ `Original = 1`
- L23 _public enumerator_ `ConvexHull3 = 2`
- L24 _public enumerator_ `ConvexHull3Simplified = 3`

#### class `UE::Physics::FConvexGeometry`  
`class FConvexGeometry`  
_L32-57_
- L35 _public prototype_ `FConvexGeometry() = delete;`
- L36 _public prototype_ `~FConvexGeometry();`
- L37 _public prototype_ `FConvexGeometry(const FConvexGeometry&);`
- L38 _public prototype_ `FConvexGeometry(FConvexGeometry&&);`
- L39 _public prototype_ `FConvexGeometry& operator=(const FConvexGeometry&);`
- L40 _public prototype_ `FConvexGeometry& operator=(FConvexGeometry&&);`
- L41 _public prototype_ `FConvexGeometry(FConvexGeometrySetup&& InSetup);`
- L42 _public prototype_ `UE_INTERNAL FConvexGeometry(Chaos::FConvex* InImplicit);`
- L44 _public prototype_ `bool operator==(const FConvexGeometry&) const = default;`
- L45 _public prototype_ `bool operator!=(const FConvexGeometry&) const = default;`
- L47 _public prototype_ `int32 GetNumVertices() const;`
- L48 _public prototype_ `FVector3f GetVertex(const int32 InIndex) const;`
- L49 _public prototype_ `float GetMargin() const;`
- L51 _public prototype_ `FString ToString() const;`
- L53 _public prototype_ `UE_INTERNAL TRefCountPtr<Chaos::FConvex> GetImplicit() const;`
- L56 _private member_ `TRefCountPtr<Chaos::FConvex> Implicit;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Chaos`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Physics` (scope `UE`)

### `Source/Runtime/Experimental/RigidPhysics/Public/RigidPhysics/Geometry/HeightFieldGeometry.h` (Public)


#### class `UE::Physics::FHeightFieldGeometrySetup`  
`class FHeightFieldGeometrySetup`  
_L16-24_
- L19 _public member_ `TArray<float> Heights;`
- L20 _public member_ `TArray<uint8> MaterialIndices;`
- L21 _public member_ `int32 NumRows = 0;`
- L22 _public member_ `int32 NumCols = 0;`
- L23 _public member_ `FVector3f Scale = FVector3f::OneVector;`

#### class `UE::Physics::FHeightFieldGeometry`  
`class FHeightFieldGeometry`  
_L26-54_
- L29 _public prototype_ `FHeightFieldGeometry() = delete;`
- L30 _public prototype_ `~FHeightFieldGeometry();`
- L31 _public prototype_ `FHeightFieldGeometry(const FHeightFieldGeometry&);`
- L32 _public prototype_ `FHeightFieldGeometry(FHeightFieldGeometry&&);`
- L33 _public prototype_ `FHeightFieldGeometry& operator=(const FHeightFieldGeometry&);`
- L34 _public prototype_ `FHeightFieldGeometry& operator=(FHeightFieldGeometry&&);`
- L35 _public prototype_ `FHeightFieldGeometry(FHeightFieldGeometrySetup&& InSetup);`
- L36 _public prototype_ `UE_INTERNAL FHeightFieldGeometry(Chaos::FHeightField* InImplicit);`
- L38 _public prototype_ `bool operator==(const FHeightFieldGeometry&) const = default;`
- L39 _public prototype_ `bool operator!=(const FHeightFieldGeometry&) const = default;`
- L41 _public prototype_ `int32 GetNumRows() const;`
- L42 _public prototype_ `int32 GetNumCols() const;`
- L43 _public prototype_ `FVector3f GetScale() const;`
- L45 _public prototype_ `float GetHeight(const int32 InIndex) const;`
- L46 _public prototype_ `uint8 GetMaterialIndex(const int32 InIndex) const;`
- L48 _public prototype_ `FString ToString() const;`
- L50 _public prototype_ `UE_INTERNAL TRefCountPtr<Chaos::FHeightField> GetImplicit() const;`
- L53 _private member_ `TRefCountPtr<Chaos::FHeightField> Implicit;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Chaos`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Physics` (scope `UE`)

### `Source/Runtime/Experimental/RigidPhysics/Public/RigidPhysics/Geometry/TriangleMeshGeometry.h` (Public)


#### class `UE::Physics::FTriangleMeshGeometrySetup`  
`class FTriangleMeshGeometrySetup`  
_L18-34_
- L27 _public member_ `TArray<FVector3f> Vertices;`
- L28 _public member_ `TArray<FInt32Vector3> TriangleIndices;`
- L29 _public member_ `TArray<FMaterialIndex> MaterialIndices;`
- L30 _public member_ `TArray<int32> ExternalFaceIndexMap;`
- L31 _public member_ `TArray<int32> ExternalVertexIndexMap;`
- L32 _public member_ `bool bCullsBackFaceRaycast = false;`
- L33 _public member_ `EPerFaceBoundsRepresentation PerFaceBoundsRepresentation = EPerFaceBoundsRepresentation::VectorizedFloat;`

#### enum `UE::Physics::FTriangleMeshGeometrySetup::EPerFaceBoundsRepresentation`  
`enum class EPerFaceBoundsRepresentation : uint8`  
_L21-25_
- L23 _public enumerator_ `VectorizedFloat = 0`
- L24 _public enumerator_ `Byte`

#### class `UE::Physics::FTriangleMeshGeometry`  
`class FTriangleMeshGeometry`  
_L36-79_
- L39 _public typedef_ `using EPerFaceBoundsRepresentation = FTriangleMeshGeometrySetup::EPerFaceBoundsRepresentation;`
- L41 _public prototype_ `~FTriangleMeshGeometry();`
- L42 _public prototype_ `FTriangleMeshGeometry(const FTriangleMeshGeometry&);`
- L43 _public prototype_ `FTriangleMeshGeometry(FTriangleMeshGeometry&&);`
- L44 _public prototype_ `FTriangleMeshGeometry& operator=(const FTriangleMeshGeometry&);`
- L45 _public prototype_ `FTriangleMeshGeometry& operator=(FTriangleMeshGeometry&&);`
- L46 _public prototype_ `UE_INTERNAL FTriangleMeshGeometry(TRefCountPtr<Chaos::FTriangleMeshImplicitObject> InImplicit);`
- L47 _public prototype_ `FTriangleMeshGeometry(FTriangleMeshGeometrySetup&& InSetup);`
- L49 _public prototype_ `bool operator==(const FTriangleMeshGeometry&) const = default;`
- L50 _public prototype_ `bool operator!=(const FTriangleMeshGeometry&) const = default;`
- L52 _public prototype_ `int32 GetNumVertices() const;`
- L53 _public prototype_ `FVector3f GetVertex(const int32 InIndex) const;`
- L55 _public prototype_ `int32 GetNumTriangleIndices() const;`
- L56 _public prototype_ `FInt32Vector3 GetTriangleIndices(const int32 InIndex) const;`
- L58 _public prototype_ `int32 GetNumMaterialIndices() const;`
- L59 _public prototype_ `FMaterialIndex GetMaterialIndex(const int32 InIndex) const;`
- L61 _public prototype_ `bool HasExternalFaceIndices() const;`
- L62 _public prototype_ `int32 GetExternalFaceIndex(const int32 InIndex) const;`
- L64 _public prototype_ `bool HasExternalVertexIndices() const;`
- L65 _public prototype_ `int32 GetExternalVertexIndex(const int32 InIndex) const;`
- L67 _public prototype_ `bool GetCullsBackFaceRaycast() const;`
- L68 _public prototype_ `EPerFaceBoundsRepresentation GetPerFaceBoundsRepresentation() const;`
- L70 _public prototype_ `FString ToString() const;`
- L72 _public prototype_ `UE_INTERNAL TRefCountPtr<Chaos::FTriangleMeshImplicitObject> GetImplicit() const;`
- L76 _private prototype_ `template <typename IndexType> void BuildInternal(FTriangleMeshGeometrySetup&& InSetup);`
- L78 _private member_ `TRefCountPtr<Chaos::FTriangleMeshImplicitObject> Implicit;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Chaos`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Physics` (scope `UE`)

### `Source/Runtime/Experimental/RigidPhysics/Public/RigidPhysics/Internal/IJointConstraint.h` (Public)


#### class `UE::Physics::IJointConstraint`  
`class UE_INTERNAL IJointConstraint : public IRigidTyped`  
_L13-22_
- inherits: `IRigidTyped`
- L18 _public prototype_ `IJointConstraint() = default;`
- L19 _public prototype_ `virtual ~IJointConstraint() = default;`
- L21 _public prototype_ `UE_INTERNAL virtual FJointConstraintHandle GetHandle() const = 0;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Physics` (scope `UE`)

### `Source/Runtime/Experimental/RigidPhysics/Public/RigidPhysics/Internal/IJointConstraint6DOF.h` (Public)


#### class `UE::Physics::IJointConstraint6DOF`  
`class UE_INTERNAL IJointConstraint6DOF : public IJointConstraint`  
_L14-95_
- inherits: `IJointConstraint`
- L19 _public prototype_ `IJointConstraint6DOF() = default;`
- L20 _public prototype_ `virtual ~IJointConstraint6DOF() = default;`
- L22 _public prototype_ `UE_INTERNAL virtual FJointConstraintHandle GetHandle() const = 0;`
- L23 _public prototype_ `UE_INTERNAL FJointConstraint6DOFHandle GetTypedHandle() const;`
- L25 _public prototype_ `UE_INTERNAL virtual void Activate();`
- L27 _public prototype_ `UE_INTERNAL virtual void SetBodies(IRigidBody* Body0, IRigidBody* Body1);`
- L29 _public prototype_ `UE_INTERNAL virtual void SetJointTransforms(const FTransform3d& InTransform0, const FTransform3d& InTransform1);`
- L31 _public prototype_ `UE_INTERNAL virtual double GetLinearLimit() const;`
- L32 _public prototype_ `UE_INTERNAL virtual void SetLinearLimit(const double InLinearLimit);`
- L34 _public prototype_ `UE_INTERNAL virtual EJointMotionType GetLinearMotionTypesX() const;`
- L35 _public prototype_ `UE_INTERNAL virtual void SetLinearMotionTypesX(EJointMotionType InMotionType);`
- L37 _public prototype_ `UE_INTERNAL virtual EJointMotionType GetLinearMotionTypesY() const;`
- L38 _public prototype_ `UE_INTERNAL virtual void SetLinearMotionTypesY(EJointMotionType InMotionType);`
- L40 _public prototype_ `UE_INTERNAL virtual EJointMotionType GetLinearMotionTypesZ() const;`
- L41 _public prototype_ `UE_INTERNAL virtual void SetLinearMotionTypesZ(EJointMotionType InMotionType);`
- L43 _public prototype_ `UE_INTERNAL virtual void SetAngularMotionTypesX(const EJointMotionType InMotionType);`
- L45 _public prototype_ `UE_INTERNAL virtual void SetAngularMotionTypesY(const EJointMotionType InMotionType);`
- L47 _public prototype_ `UE_INTERNAL virtual void SetAngularMotionTypesZ(const EJointMotionType InMotionType);`
- L49 _public prototype_ `UE_INTERNAL virtual void SetAngularLimits(const FVector3d& InAngularLimits);`
- L51 _public prototype_ `UE_INTERNAL virtual void SetCollisionEnabled(const bool bCollisionEnabled);`
- L53 _public prototype_ `UE_INTERNAL virtual void SetProjectionEnabled(const bool bProjectionEnabled);`
- L55 _public prototype_ `UE_INTERNAL virtual void SetMassConditioningEnabled(const bool bMassConditioningEnabled);`
- L57 _public prototype_ `UE_INTERNAL virtual void SetUseLinearSolver(const bool bUseLinearSolver);`
- L59 _public prototype_ `UE_INTERNAL virtual void SetSoftLinearLimitsEnabled(const bool bSoftLinearLimitsEnabled);`
- L61 _public prototype_ `UE_INTERNAL virtual void SetSoftTwistLimitsEnabled(const bool bSoftTwistLimitsEnabled);`
- L63 _public prototype_ `UE_INTERNAL virtual void SetSoftSwingLimitsEnabled(const bool bSoftSwingLimitsEnabled);`
- L65 _public prototype_ `UE_INTERNAL virtual void SetSoftLinearStiffness(const double InSoftLinearStiffness);`
- L67 _public prototype_ `UE_INTERNAL virtual void SetSoftLinearDamping(const double InSoftLinearDamping);`
- L69 _public prototype_ `UE_INTERNAL virtual void SetSoftTwistStiffness(const double InSoftTwistStiffness);`
- L71 _public prototype_ `UE_INTERNAL virtual void SetSoftTwistDamping(const double InSoftTwistDamping);`
- L73 _public prototype_ `UE_INTERNAL virtual void SetSoftSwingStiffness(const double InSoftSwingStiffness);`
- L75 _public prototype_ `UE_INTERNAL virtual void SetSoftSwingDamping(const double InSoftSwingDamping);`
- L77 _public prototype_ `UE_INTERNAL virtual void SetProjectionLinearAlpha(const double InProjectionLinearAlpha);`
- L79 _public prototype_ `UE_INTERNAL virtual void SetProjectionAngularAlpha(const double InProjectionAngularAlpha);`
- L81 _public prototype_ `UE_INTERNAL virtual void SetProjectionLinearTolerance(const double InProjectionLinearTolerance);`
- L83 _public prototype_ `UE_INTERNAL virtual void SetProjectionAngularTolerance(const double InProjectionAngularTolerance);`
- L85 _public prototype_ `UE_INTERNAL virtual void SetLinearContactDistance(const double InLinearContactDistance);`
- L87 _public prototype_ `UE_INTERNAL virtual void SetTwistContactDistance(const double InTwistContactDistance);`
- L89 _public prototype_ `UE_INTERNAL virtual void SetSwingContactDistance(const double InSwingContactDistance);`
- L91 _public prototype_ `UE_INTERNAL virtual void SetAngularDriveStiffness(const FVector3d& InAngularDriveStiffness);`
- L92 _public prototype_ `UE_INTERNAL virtual void SetAngularDriveDamping(const FVector3d& InAngularDriveDamping);`
- L93 _public prototype_ `UE_INTERNAL virtual void SetLinearDriveStiffness(const FVector3d& InLinearDriveStiffness);`
- L94 _public prototype_ `UE_INTERNAL virtual void SetLinearDriveDamping(const FVector3d& InLinearDriveDamping);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Physics` (scope `UE`)

### `Source/Runtime/Experimental/RigidPhysics/Public/RigidPhysics/Internal/IRigidBody.h` (Public)


#### class `UE::Physics::IRigidBody`  
`class UE_INTERNAL IRigidBody : public IRigidTyped`  
_L22-123_
- inherits: `IRigidTyped`
- desc: The full rigid body API. There will be several implementations of this API. E.g., synchronous physics, asynchronous physics, immediate physics, remote physics, etc. NOTE: for some implementations like async physics, there are both Game- and Physics-Context implementations within the async implementation. Pinning a handle will return the object appropriate for the context.
- L27 _public prototype_ `IRigidBody() = default;`
- L28 _public prototype_ `virtual ~IRigidBody() = default;`
- L32 _public prototype_ `UE_INTERNAL virtual bool IsActive() const;` — Is the body active in its scene? Inactive bodies do not participate in physics in any way.
- L33 _public prototype_ `UE_INTERNAL virtual void Activate();`
- L34 _public prototype_ `UE_INTERNAL virtual void Deactivate();`
- L38 _public prototype_ `UE_INTERNAL virtual FRigidBodyHandle GetHandle() const = 0;` — The handle to this body
- L40 _public prototype_ `UE_INTERNAL virtual void SetId(const FRigidObjectId& InId);`
- L43 _public prototype_ `UE_INTERNAL virtual bool IsStatic() const = 0;` — Is this body Static? Static bodies can be moved but have no velocity.
- L47 _public prototype_ `UE_INTERNAL virtual bool IsKinematic() const = 0;` — Is this body kinematic? Kinematic bodies can be explicitly moved and have velocity, but do not react to forces, collisions, etc.
- L50 _public prototype_ `UE_INTERNAL virtual bool IsDynamic() const = 0;` — Is this a dynamic body? Dynamic bodies have momentum and react to forces and collisions.
- L53 _public prototype_ `UE_INTERNAL virtual void SetIsDynamic(bool bIsDynamic) const;` — Make the body dynamic (will only affect Kinematic bodies. Static bodies cannot be made dynamic)
- L58 _public prototype_ `UE_INTERNAL virtual bool IsSleeping() const;` — Is this a sleeping dynamic body? Sleeping bodies are dynamic bodies that are ignored by the simulation (as an optimization) until the scene changes in a way that might affect them, or they are explicitly woken.
- L60 _public prototype_ `UE_INTERNAL virtual int32 GetNumShapes() const = 0;`
- L61 _public prototype_ `UE_INTERNAL virtual IRigidShapeInstance* GetShape(int32 ShapeIndex) const = 0;`
- L62 _public prototype_ `UE_INTERNAL virtual IRigidShapeInstance* CreateShape(const FRigidShapeInstanceSetup& InSetup);`
- L63 _public prototype_ `UE_INTERNAL virtual IRigidShapeInstance* CreateShape(TUniquePtr<Chaos::FPerShapeData>&& InShapeData);`
- L64 _public prototype_ `UE_INTERNAL virtual void DestroyShape(IRigidShapeInstance* InShape, bool bWakeTouching);`
- L67 _public prototype_ `UE_INTERNAL virtual void InitTransform(const FTransform3d& InTransform);` — Set the transform and initialize body state (velocity etc.) at the new location.
- L70 _public prototype_ `UE_INTERNAL virtual void UpdateTransform(const FTransform3d& InTransform);` — Set the transform without changing any other rigid body state.
- L76 _public prototype_ `UE_INTERNAL virtual void SetKinematicTarget(const FTransform3d& InTransform);` — Set the kinematic target. The body will attempt to reach the target at the next tick. Kinematic bodies will always reach the target bscause they do not respond to forces or collisions. Dynamic bodies will only reach their target if their velocity in the absence of interactions (forces, collisions, or other constraints).
- L81 _public prototype_ `UE_INTERNAL virtual FTransform3d GetTransform() const;` — Get the current transform. NOTE: This will immediately reflect any recent calls to to InitTransform or UpdateTransform, but will not reflect the latest KinematicTarget until after the next physics tick.
- L84 _public prototype_ `UE_INTERNAL virtual FBounds3d GetBounds() const;` — Get the world-space bounds at the current transform
- L87 _public prototype_ `UE_INTERNAL virtual double GetMass() const;` — TODO: Maybe just Set/GetMassProperties
- L88 _public prototype_ `UE_INTERNAL virtual void SetMass(double InM);`
- L90 _public prototype_ `UE_INTERNAL virtual FVector3d GetInertia() const;`
- L91 _public prototype_ `UE_INTERNAL virtual void SetInertia(const FVector3d& InInertia);`
- L93 _public prototype_ `UE_INTERNAL virtual void SetCenterOfMass(const FVector3d& InCenterOfMass);`
- L94 _public prototype_ `UE_INTERNAL virtual void SetRotationOfMass(const FQuat& InRotationOfMass);`
- L96 _public prototype_ `UE_INTERNAL virtual void SetCCDEnabled(bool bInEnabled);`
- L98 _public prototype_ `UE_INTERNAL virtual void SetMACDEnabled(bool bInEnabled);`
- L100 _public prototype_ `UE_INTERNAL virtual void SetSmoothEdgeCollisionsEnabled(bool bInEnabled);`
- L102 _public prototype_ `UE_INTERNAL virtual void SetMaxLinearVelocity(float InMax);`
- L104 _public prototype_ `UE_INTERNAL virtual void SetMaxAngularVelocity(float InMax);`
- L106 _public prototype_ `UE_INTERNAL virtual void SetInertiaConditioningEnabled(bool bInEnabled);`
- L108 _public prototype_ `UE_INTERNAL virtual void SetGyroscopicTorqueEnabled(bool bInEnabled);`
- L110 _public prototype_ `UE_INTERNAL virtual void SetGravityGroup(int32 InId);`
- L112 _public prototype_ `UE_INTERNAL virtual void SetGravityScale(float InScale);`
- L114 _public prototype_ `UE_INTERNAL virtual void SetWakeEventsEnabled(bool bInEnabled);`
- L116 _public prototype_ `UE_INTERNAL virtual void SetNumPositionIterations(int32 InNum);`
- L118 _public prototype_ `UE_INTERNAL virtual void SetNumVelocityIterations(int32 InNum);`
- L120 _public prototype_ `UE_INTERNAL virtual void SetNumProjectionIterations(int32 InNum);`
- L122 _public prototype_ `UE_INTERNAL virtual void SetIsSleeping(bool bInSleeping);`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Physics` (scope `UE`)

### `Source/Runtime/Experimental/RigidPhysics/Public/RigidPhysics/Internal/IRigidBodyContainer.h` (Public)


#### class `UE::Physics::IRigidBodyContainer`  
`class UE_INTERNAL IRigidBodyContainer : public IRigidTyped`  
_L18-40_
- inherits: `IRigidTyped`
- desc: The interface for rigid body containers. There will be several implementations of this API. E.g., synchronous physics, asynchronous physics, immediate physics, remote physics, etc.
- L23 _public prototype_ `IRigidBodyContainer() = default;`
- L24 _public prototype_ `virtual ~IRigidBodyContainer() = default;`
- L26 _public prototype_ `UE_INTERNAL virtual FRigidBodyContainerHandle GetHandle() const = 0;`
- L28 _public prototype_ `UE_INTERNAL virtual int32 GetNumBodies() const = 0;`
- L30 _public prototype_ `UE_INTERNAL virtual IRigidBody* GetBody(const FRigidObjectId& InBodyId) const = 0;`
- L36 _public prototype_ `UE_INTERNAL virtual void SetId(const FRigidObjectId& InBodyId);`
- L38 _public prototype_ `UE_INTERNAL virtual IRigidBody* CreateBody(const FRigidDebugName& InName, ERigidMovementType InMovementType);`
- L39 _public prototype_ `UE_INTERNAL virtual void DestroyBody(IRigidBody* InBody);`

#### class `UE::Physics::FRigidBodyContainer`  
`class UE_INTERNAL FRigidBodyContainer : public IRigidBodyContainer`  
_L42-55_
- inherits: `IRigidBodyContainer`
- L45 _public prototype_ `UE_INTERNAL FRigidBodyContainer();`
- L46 _public prototype_ `virtual ~FRigidBodyContainer() = default;`
- L48 _public prototype_ `UE_INTERNAL virtual IRigidBody* GetBody(const FRigidObjectId& InBodyId) const override final;`
- L51 _protected prototype_ `UE_INTERNAL FRigidBodyRegistry* GetBodyRegistry() const;`
- L54 _private member_ `TUniquePtr<FRigidBodyRegistry> BodyRegistry;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Physics` (scope `UE`)

### `Source/Runtime/Experimental/RigidPhysics/Public/RigidPhysics/Internal/IRigidGeometryCollection.h` (Public)


#### class `UE::Physics::IRigidGeometryCollection`  
`class UE_INTERNAL IRigidGeometryCollection : public IRigidBodyContainer`  
_L15-25_
- inherits: `IRigidBodyContainer`
- desc: The interface for rigid body containers. There will be several implementations of this API. E.g., synchronous physics, asynchronous physics, immediate physics, remote physics, etc.
- L20 _public prototype_ `IRigidGeometryCollection() = default;`
- L21 _public prototype_ `virtual ~IRigidGeometryCollection() = default;`
- L24 _public prototype_ `UE_INTERNAL virtual IRigidBody* GetBodyAt(int32 BodyIndex) const = 0;` — TODO_CHAOSAPI: Figure out the public GeometryCollection API!!

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Physics` (scope `UE`)

### `Source/Runtime/Experimental/RigidPhysics/Public/RigidPhysics/Internal/IRigidScene.h` (Public)


#### class `UE::Physics::IRigidScene`  
`class UE_INTERNAL IRigidScene : public IRigidLockable`  
_L18-59_
- inherits: `IRigidLockable`
- desc: The interface to a rigid body scene. The rigid body scene owns the physics simulations and manages a set of rigid body containers which in turn manage sets of rigid bodies.
- L23 _public prototype_ `IRigidScene() = default;`
- L24 _public prototype_ `virtual ~IRigidScene() = default;`
- L26 _public prototype_ `UE_INTERNAL virtual FRigidSceneId GetId() const = 0;`
- L27 _public prototype_ `UE_INTERNAL virtual FRigidSceneHandle GetHandle() const = 0;`
- L29 _public prototype_ `UE_INTERNAL virtual IRigidBody* GetBody(const FRigidObjectId& InBodyId) const = 0;`
- L31 _public prototype_ `UE_INTERNAL virtual IRigidBodyContainer* GetBodyContainer(const FRigidObjectId& InBodyContainerId) const = 0;`
- L33 _public prototype_ `UE_INTERNAL virtual IRigidGeometryCollection* GetGeometryCollection(const FRigidObjectId& InGeometryCollectionId) const = 0;`
- L35 _public prototype_ `UE_INTERNAL virtual bool Query(const FRigidQueryDesc& InQueryDesc, TArray<FRigidQueryHit>& OutHits);`
- L38 _public prototype_ `UE_INTERNAL virtual void StartTick(const float InDt);` — Advance the simulation by Dt. If the implementation is asynchronous, this will return immediately
- L39 _public prototype_ `UE_INTERNAL virtual void WaitOnTick();`
- L40 _public prototype_ `UE_INTERNAL virtual void EndTick();`
- L43 _public prototype_ `UE_INTERNAL virtual void RegisterModifier(IRigidSceneModifier* InModifier);` — GT Only API - Move this somehow
- L44 _public prototype_ `UE_INTERNAL virtual void UnregisterModifier(IRigidSceneModifier* InModifier);`
- L46 _public prototype_ `UE_INTERNAL virtual IRigidShapeInstance* GetShape(const FRigidObjectId& InId) const = 0;`
- L48 _public prototype_ `UE_INTERNAL virtual IRigidBody* CreateBody(const FRigidDebugName& InName, ERigidMovementType InMovementType);`
- L49 _public prototype_ `UE_INTERNAL virtual void DestroyBody(IRigidBody* InBody);`
- L51 _public prototype_ `UE_INTERNAL virtual IRigidGeometryCollection* CreateGeometryCollection(const FRigidDebugName& InName, const FSimulationParameters& InParameters);`
- L52 _public prototype_ `UE_INTERNAL virtual void DestroyGeometryCollection(IRigidGeometryCollection* InGC);`
- L54 _public prototype_ `UE_INTERNAL virtual void AddDisabledCollisions(const TMap<FRigidBodyHandle, TArray<FRigidBodyHandle>>& InMap);`
- L56 _public prototype_ `UE_INTERNAL virtual IJointConstraint6DOF* CreateJointConstraint6DOF();`
- L57 _public prototype_ `UE_INTERNAL virtual void DestroyJointConstraint(IJointConstraint* InConstraint);`
- L58 _public prototype_ `UE_INTERNAL virtual IJointConstraint* GetJointConstraint(const FRigidObjectId& InConstraintId) const;`

#### class `UE::Physics::FRigidScene`  
`class UE_INTERNAL FRigidScene : public IRigidScene`  
_L65-86_
- inherits: `IRigidScene`
- desc: Base class for the Game Context Scene. This provides the BodyContainerRegistry, partly for convenience and partly so that we can convert Handles to Objects in the debugger with natvis
- L68 _public prototype_ `FRigidScene();`
- L69 _public prototype_ `virtual ~FRigidScene() = default;`
- L71 _public prototype_ `UE_INTERNAL virtual IRigidBody* GetBody(const FRigidObjectId& InBodyId) const override final;`
- L72 _public prototype_ `UE_INTERNAL virtual IRigidBodyContainer* GetBodyContainer(const FRigidObjectId& InBodyContainerId) const override final;`
- L73 _public prototype_ `UE_INTERNAL virtual IRigidGeometryCollection* GetGeometryCollection(const FRigidObjectId& InGeometryCollectionId) const override final;`
- L76 _protected prototype_ `UE_INTERNAL void DestructScene();`
- L78 _protected prototype_ `UE_INTERNAL FRigidBodyContainerRegistry* GetBodyContainerRegistry() const;`
- L79 _protected prototype_ `UE_INTERNAL FRigidBodyRegistry* GetBodyRegistry() const;`
- L80 _protected prototype_ `UE_INTERNAL FJointConstraintRegistry* GetJointConstraintRegistry() const;`
- L83 _private member_ `TUniquePtr<FRigidBodyContainerRegistry> BodyContainerRegistry;`
- L84 _private member_ `TUniquePtr<FRigidBodyRegistry> BodyRegistry;`
- L85 _private member_ `TUniquePtr<FJointConstraintRegistry> JointConstraintRegistry;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Physics` (scope `UE`)

### `Source/Runtime/Experimental/RigidPhysics/Public/RigidPhysics/Internal/IRigidShapeInstance.h` (Public)


#### class `UE::Physics::IRigidShapeInstance`  
`class UE_INTERNAL IRigidShapeInstance : public IRigidTyped`  
_L20-72_
- inherits: `IRigidTyped`
- L25 _public prototype_ `IRigidShapeInstance() = default;`
- L26 _public prototype_ `virtual ~IRigidShapeInstance() = default;`
- L28 _public prototype_ `UE_INTERNAL virtual FRigidShapeInstanceHandle GetHandle() const = 0;`
- L30 _public prototype_ `UE_INTERNAL virtual FAnyGeometry GetGeometry() const = 0;`
- L33 _public prototype_ `UE_INTERNAL virtual FTransform3f GetLocalTransform() const = 0;`
- L36 _public prototype_ `UE_INTERNAL virtual bool GetQueryEnabled() const = 0;`
- L37 _public prototype_ `UE_INTERNAL virtual void SetQueryEnabled(const bool bInEnabled) = 0;`
- L39 _public prototype_ `UE_INTERNAL virtual bool GetSimEnabled() const = 0;`
- L40 _public prototype_ `UE_INTERNAL virtual void SetSimEnabled(const bool bInEnabled) = 0;`
- L42 _public prototype_ `UE_INTERNAL virtual bool GetIsProbe() const = 0;`
- L43 _public prototype_ `UE_INTERNAL virtual void SetIsProbe(const bool bInIsProbe) = 0;`
- L45 _public prototype_ `UE_INTERNAL virtual ECollisionTraceFlag GetCollisionTraceType() const = 0;`
- L46 _public prototype_ `UE_INTERNAL virtual void SetCollisionTraceType(const ECollisionTraceFlag InTraceFlag) = 0;`
- L48 _public prototype_ `UE_INTERNAL virtual Chaos::Filter::FShapeFilterData GetShapeFilter() const = 0;`
- L49 _public prototype_ `UE_INTERNAL virtual void SetShapeFilter(const Chaos::Filter::FShapeFilterData& InShapeFilter) = 0;`
- L51 _public prototype_ `UE_INTERNAL virtual Chaos::Filter::FInstanceData GetFilterInstanceData() const = 0;`
- L52 _public prototype_ `UE_INTERNAL virtual void SetFilterInstanceData(const Chaos::Filter::FInstanceData& InInstanceData) = 0;`
- L54 _public prototype_ `UE_INTERNAL virtual int32 GetNumMaterials() const = 0;`
- L55 _public prototype_ `UE_INTERNAL virtual FMaterialHandle GetMaterial(const int32 InIndex) const = 0;`
- L56 _public prototype_ `UE_INTERNAL virtual void SetMaterials(TArray<FMaterialHandle>&& InMaterials) = 0;`
- L58 _public prototype_ `UE_INTERNAL virtual int32 GetNumMaterialMasks() const = 0;`
- L59 _public prototype_ `UE_INTERNAL virtual FMaterialMaskHandle GetMaterialMask(const int32 InIndex) const = 0;`
- L60 _public prototype_ `UE_INTERNAL virtual void SetMaterialMasks(TArray<FMaterialMaskHandle>&& InMaterialMasks) = 0;`
- L62 _public prototype_ `UE_INTERNAL virtual int32 GetNumMaterialMaskMaps() const = 0;`
- L63 _public prototype_ `UE_INTERNAL virtual uint32 GetMaterialMaskMap(const int32 InIndex) const = 0;`
- L64 _public prototype_ `UE_INTERNAL virtual void SetMaterialMaskMaps(TArray<uint32>&& InMaterialMaskMaps) = 0;`
- L66 _public prototype_ `UE_INTERNAL virtual int32 GetNumMaterialMaskMapMaterials() const = 0;`
- L67 _public prototype_ `UE_INTERNAL virtual FMaterialHandle GetMaterialMaskMapMaterial(const int32 InIndex) const = 0;`
- L68 _public prototype_ `UE_INTERNAL virtual void SetMaterialMaskMapMaterials(TArray<FMaterialHandle>&& InMaterialMaskMapMaterials) = 0;`
- L70 _public prototype_ `UE_INTERNAL virtual void* GetUserData() const = 0;`
- L71 _public prototype_ `UE_INTERNAL virtual void SetUserData(void* InUserData) = 0;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Physics` (scope `UE`)

### `Source/Runtime/Experimental/RigidPhysics/Public/RigidPhysics/JointConstraint.h` (Public)


#### class `UE::Physics::TJointConstraintPtrImpl`  
`template <typename ContextType> class TJointConstraintPtrImpl`  
_L18-78_
- L21 _public typedef_ `using FContext = ContextType;`
- L22 _public typedef_ `using FInterface = IJointConstraint;`
- L23 _public typedef_ `using FHandle = FJointConstraintHandle;`
- L25 _public prototype_ `UE_INTERNAL TJointConstraintPtrImpl() = default;`
- L26 _public function_ `UE_INTERNAL TJointConstraintPtrImpl(IJointConstraint* InConstraint) : ConstraintRaw(InConstraint)`
- L31 _public prototype_ `TJointConstraintPtrImpl(const TJointConstraintPtrImpl&) = delete;`
- L33 _public function_ `TJointConstraintPtrImpl(TJointConstraintPtrImpl&& InPtr) : ConstraintRaw(InPtr.ConstraintRaw)`
- L39 _public function_ `~TJointConstraintPtrImpl()`
- L47 _public function_ `bool IsValid() const`
- L52 _public function_ `FJointConstraintHandle GetHandle() const`
- L61 _public function_ `UE_INTERNAL void Reset()`
- L66 _public function_ `UE_INTERNAL const FRigidTypeId& GetTypeId() const`
- L71 _public function_ `UE_INTERNAL IJointConstraint* Get() const`
- L77 _private member_ `IJointConstraint* ConstraintRaw = nullptr;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Physics` (scope `UE`)

### `Source/Runtime/Experimental/RigidPhysics/Public/RigidPhysics/JointConstraint6DOF.h` (Public)


#### class `UE::Physics::TJointConstraint6DOFPtrImpl`  
`template <typename ContextType> class TJointConstraint6DOFPtrImpl`  
_L16-276_
- L19 _public typedef_ `using FContext = ContextType;`
- L20 _public typedef_ `using FInterface = IJointConstraint6DOF;`
- L21 _public typedef_ `using FHandle = FJointConstraint6DOFHandle;`
- L23 _public prototype_ `UE_INTERNAL TJointConstraint6DOFPtrImpl() = default;`
- L24 _public function_ `UE_INTERNAL TJointConstraint6DOFPtrImpl(IJointConstraint6DOF* InConstraint) : ConstraintRaw(InConstraint)`
- L30 _public function_ `UE_INTERNAL TJointConstraint6DOFPtrImpl(IJointConstraint* InConstraint) : ConstraintRaw(InConstraint ? InConstraint->AsA<IJointConstraint6DOF>() : nullptr)` — Construct from base class (does a safe downcast)
- L35 _public prototype_ `TJointConstraint6DOFPtrImpl(const TJointConstraint6DOFPtrImpl&) = delete;`
- L37 _public function_ `TJointConstraint6DOFPtrImpl(TJointConstraint6DOFPtrImpl&& InPtr) : ConstraintRaw(InPtr.ConstraintRaw)`
- L43 _public function_ `~TJointConstraint6DOFPtrImpl()`
- L51 _public function_ `bool IsValid() const`
- L56 _public function_ `FJointConstraint6DOFHandle GetHandle() const`
- L65 _public function_ `void Activate()`
- L70 _public function_ `void SetBodies(const TRigidBodyPtr<ContextType>& Body0, const TRigidBodyPtr<ContextType>& Body1) requires CIsGameContext<FContext>`
- L75 _public function_ `void SetJointTransforms(const FTransform3d& InTransform0, const FTransform3d& InTransform1) requires CIsGameContext<FContext>`
- L80 _public function_ `double GetLinearLimit() const`
- L85 _public function_ `void SetLinearLimit(const double InLinearLimit)`
- L90 _public function_ `EJointMotionType GetLinearMotionTypesX()`
- L95 _public function_ `void SetLinearMotionTypesX(const EJointMotionType InMotionType)`
- L100 _public function_ `EJointMotionType GetLinearMotionTypesY()`
- L105 _public function_ `void SetLinearMotionTypesY(const EJointMotionType InMotionType)`
- L110 _public function_ `EJointMotionType GetLinearMotionTypesZ()`
- L115 _public function_ `void SetLinearMotionTypesZ(const EJointMotionType InMotionType)`
- L120 _public function_ `void SetAngularMotionTypesX(const EJointMotionType InMotionType) requires CIsGameContext<FContext>`
- L125 _public function_ `void SetAngularMotionTypesY(const EJointMotionType InMotionType) requires CIsGameContext<FContext>`
- L130 _public function_ `void SetAngularMotionTypesZ(const EJointMotionType InMotionType) requires CIsGameContext<FContext>`
- L135 _public function_ `void SetAngularLimits(const FVector3d& InAngularLimits) requires CIsGameContext<FContext>`
- L140 _public function_ `void SetCollisionEnabled(const bool bCollisionEnabled) requires CIsGameContext<FContext>`
- L145 _public function_ `void SetProjectionEnabled(const bool bProjectionEnabled) requires CIsGameContext<FContext>`
- L150 _public function_ `void SetMassConditioningEnabled(const bool bMassConditioningEnabled) requires CIsGameContext<FContext>`
- L155 _public function_ `void SetUseLinearSolver(const bool bUseLinearSolver) requires CIsGameContext<FContext>`
- L160 _public function_ `void SetSoftLinearLimitsEnabled(const bool bSoftLinearLimitsEnabled) requires CIsGameContext<FContext>`
- L165 _public function_ `void SetSoftTwistLimitsEnabled(const bool bSoftTwistLimitsEnabled) requires CIsGameContext<FContext>`
- L170 _public function_ `void SetSoftSwingLimitsEnabled(const bool bSoftSwingLimitsEnabled) requires CIsGameContext<FContext>`
- L175 _public function_ `void SetSoftLinearStiffness(const double InSoftLinearStiffness) requires CIsGameContext<FContext>`
- L180 _public function_ `void SetSoftLinearDamping(const double InSoftLinearDamping) requires CIsGameContext<FContext>`
- L185 _public function_ `void SetSoftTwistStiffness(const double InSoftTwistStiffness) requires CIsGameContext<FContext>`
- L190 _public function_ `void SetSoftTwistDamping(const double InSoftTwistDamping) requires CIsGameContext<FContext>`
- L195 _public function_ `void SetSoftSwingStiffness(const double InSoftSwingStiffness) requires CIsGameContext<FContext>`
- L200 _public function_ `void SetSoftSwingDamping(const double InSoftSwingDamping) requires CIsGameContext<FContext>`
- L205 _public function_ `void SetProjectionLinearAlpha(const double InProjectionLinearAlpha) requires CIsGameContext<FContext>`
- L210 _public function_ `void SetProjectionAngularAlpha(const double InProjectionAngularAlpha) requires CIsGameContext<FContext>`
- L215 _public function_ `void SetProjectionLinearTolerance(const double InProjectionLinearTolerance) requires CIsGameContext<FContext>`
- L220 _public function_ `void SetProjectionAngularTolerance(const double InProjectionAngularTolerance) requires CIsGameContext<FContext>`
- L225 _public function_ `void SetLinearContactDistance(const double InLinearContactDistance) requires CIsGameContext<FContext>`
- L230 _public function_ `void SetTwistContactDistance(const double InTwistContactDistance) requires CIsGameContext<FContext>`
- L235 _public function_ `void SetSwingContactDistance(const double InSwingContactDistance) requires CIsGameContext<FContext>`
- L240 _public function_ `void SetAngularDriveStiffness(const FVector3d& InAngularDriveStiffness) requires CIsGameContext<FContext>`
- L245 _public function_ `void SetAngularDriveDamping(const FVector3d& InAngularDriveDamping) requires CIsGameContext<FContext>`
- L250 _public function_ `void SetLinearDriveStiffness(const FVector3d& InLinearDriveStiffness) requires CIsGameContext<FContext>`
- L255 _public function_ `void SetLinearDriveDamping(const FVector3d& InLinearDriveDamping) requires CIsGameContext<FContext>`
- L260 _public function_ `UE_INTERNAL void Reset()`
- L265 _public function_ `UE_INTERNAL const FRigidTypeId& GetTypeId() const`
- L270 _public function_ `UE_INTERNAL IJointConstraint6DOF* Get() const`
- L275 _private member_ `IJointConstraint6DOF* ConstraintRaw = nullptr;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Physics` (scope `UE`)

### `Source/Runtime/Experimental/RigidPhysics/Public/RigidPhysics/JointConstraint6DOFHandle.h` (Public)


#### class `UE::Physics::FJointConstraint6DOFHandle`  
`class FJointConstraint6DOFHandle : public FJointConstraintHandle`  
_L17-38_
- inherits: `FJointConstraintHandle`
- L20 _public prototype_ `FJointConstraint6DOFHandle() = default;`
- L21 _public prototype_ `FJointConstraint6DOFHandle(const FJointConstraint6DOFHandle&) = default;`
- L22 _public prototype_ `UE_INTERNAL FJointConstraint6DOFHandle(const FRigidSceneId& InSceneId, const FRigidObjectId& InConstraintId);`
- L28 _public function_ `template <typename ContextType> TJointConstraint6DOFPtr<ContextType> Pin(const ContextType& InContext) const`
- L37 _private prototype_ `UE_INTERNAL FJointConstraint6DOFHandle(const FJointConstraintHandle& InHandle);` — Private so we only allow downcast in the context where we explicitly know this constraint handle is the correct type.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Physics` (scope `UE`)

### `Source/Runtime/Experimental/RigidPhysics/Public/RigidPhysics/JointConstraintHandle.h` (Public)


#### class `UE::Physics::FJointConstraintHandle`  
`class FJointConstraintHandle`  
_L19-50_
- L22 _public prototype_ `FJointConstraintHandle() = default;`
- L23 _public prototype_ `FJointConstraintHandle(const FJointConstraintHandle&) = default;`
- L24 _public prototype_ `UE_INTERNAL FJointConstraintHandle(const FRigidSceneId& InSceneId, const FRigidObjectId& InConstraintId);`
- L29 _public prototype_ `FRigidSceneHandle GetSceneHandle() const;`
- L32 _public function_ `template <typename ContextType> TJointConstraintPtr<ContextType> Pin(const ContextType& InContext) const`
- L41 _public prototype_ `UE_INTERNAL const FRigidObjectId& GetId() const;`
- L42 _public prototype_ `UE_INTERNAL const FRigidSceneId& GetSceneId() const;`
- L43 _public prototype_ `UE_INTERNAL void Reset();`
- L46 _private prototype_ `IJointConstraint* PinInternal(const IRigidScene* Scene) const;`
- L48 _private member_ `FRigidSceneId SceneId;`
- L49 _private member_ `FRigidObjectId ConstraintId;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Physics` (scope `UE`)

### `Source/Runtime/Experimental/RigidPhysics/Public/RigidPhysics/RigidBody.h` (Public)


#### class `UE::Physics::TRigidBodyPtrImpl`  
`template <typename ContextType> class UE_INTERNAL TRigidBodyPtrImpl`  
_L23-264_
- desc: This class only exists so that TRigidBodyPtr can have pointer semantics rather than object semantics, and so that we can disable functions based on ContextType See TRigidBodyPtr for comments.
- L26 _public typedef_ `using FContext = ContextType;`
- L27 _public typedef_ `using FInterface = IRigidBody;`
- L28 _public typedef_ `using FHandle = FRigidBodyHandle;`
- L30 _public prototype_ `UE_INTERNAL TRigidBodyPtrImpl() = default;`
- L31 _public function_ `UE_INTERNAL TRigidBodyPtrImpl(IRigidBody* InBody) : BodyRaw(InBody)`
- L36 _public prototype_ `TRigidBodyPtrImpl(const TRigidBodyPtrImpl& InBodyPtr) = delete;`
- L38 _public function_ `TRigidBodyPtrImpl(TRigidBodyPtrImpl&& InBodyPtr) : BodyRaw(InBodyPtr.BodyRaw)`
- L44 _public function_ `~TRigidBodyPtrImpl()`
- L52 _public function_ `bool IsValid() const`
- L57 _public function_ `FRigidBodyHandle GetHandle() const`
- L66 _public function_ `bool IsActive() const`
- L71 _public function_ `void Activate() requires CIsGameContext<FContext>`
- L76 _public function_ `void Deactivate() requires CIsGameContext<FContext>`
- L81 _public function_ `bool IsStatic() const`
- L86 _public function_ `bool IsKinematic() const`
- L91 _public function_ `bool IsDynamic() const`
- L96 _public function_ `int32 GetNumShapes() const`
- L101 _public function_ `TRigidShapeInstancePtr<FContext> GetShape(int32 InShapeIndex) const`
- L106 _public function_ `TRigidShapeInstancePtr<FContext> CreateShape(const FRigidShapeInstanceSetup& InSetup) requires CIsGameContext<FContext>`
- L111 _public function_ `TRigidShapeInstancePtr<FContext> CreateShape(TUniquePtr<Chaos::FPerShapeData>&& InShapeData) requires CIsGameContext<FContext>`
- L116 _public function_ `void DestroyShape(const TRigidShapeInstancePtr<FContext>& InShape, bool bWakeTouching = true) requires CIsGameContext<FContext>`
- L121 _public function_ `void InitTransform(const FTransform3d& InTransform)`
- L126 _public function_ `void UpdateTransform(const FTransform3d& InTransform)`
- L131 _public function_ `void SetKinematicTarget(const FTransform3d& InTransform)`
- L136 _public function_ `FTransform3d GetTransform() const`
- L141 _public function_ `FBounds3d GetBounds() const`
- L146 _public function_ `double GetMass() const`
- L151 _public function_ `void SetMass(double InMass)`
- L156 _public function_ `FVector3d GetInertia() const`
- L161 _public function_ `void SetInertia(const FVector3d& InInertia)`
- L166 _public function_ `void SetCenterOfMass(const FVector3d& InCenterOfMass) requires CIsGameContext<FContext>`
- L171 _public function_ `void SetRotationOfMass(const FQuat& InRotationOfMass) requires CIsGameContext<FContext>`
- L176 _public function_ `void SetCCDEnabled(bool bInEnabled)`
- L181 _public function_ `void SetMACDEnabled(bool bInEnabled)`
- L186 _public function_ `void SetSmoothEdgeCollisionsEnabled(bool bInEnabled)`
- L191 _public function_ `void SetMaxLinearVelocity(float InMax)`
- L196 _public function_ `void SetMaxAngularVelocity(float InMax)`
- L201 _public function_ `void SetInertiaConditioningEnabled(bool bInEnabled)`
- L206 _public function_ `void SetGyroscopicTorqueEnabled(bool bInEnabled)`
- L211 _public function_ `void SetGravityGroup(int32 InId)`
- L216 _public function_ `void SetGravityScale(float InScale)`
- L221 _public function_ `void SetWakeEventsEnabled(bool bInEnabled)`
- L226 _public function_ `void SetNumPositionIterations(int32 InNum)`
- L231 _public function_ `void SetNumVelocityIterations(int32 InNum)`
- L236 _public function_ `void SetNumProjectionIterations(int32 InNum)`
- L241 _public function_ `void SetIsSleeping(bool bInSleeping)`
- L246 _public function_ `UE_INTERNAL void Reset()`
- L251 _public function_ `UE_INTERNAL IRigidBody* Get() const`
- L256 _public function_ `UE_INTERNAL const FRigidTypeId& GetTypeId() const`
- L263 _private member_ `IRigidBody* BodyRaw = nullptr;` — IRigidBody implementation depends on Context type

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Physics` (scope `UE`)

### `Source/Runtime/Experimental/RigidPhysics/Public/RigidPhysics/RigidBodyContainer.h` (Public)


#### class `UE::Physics::TRigidBodyContainerPtrImpl`  
`template <typename ContextType> class UE_INTERNAL TRigidBodyContainerPtrImpl`  
_L22-86_
- desc: Utility wrapper around IRigidBodyContainer that adds Context and allows TRigidBodyContainerPtr to have pointer semantics without exposing IRigidBodyContainer
- L25 _public typedef_ `using FContext = ContextType;`
- L26 _public typedef_ `using FInterface = IRigidBodyContainer;`
- L27 _public typedef_ `using FHandle = FRigidBodyContainerHandle;`
- L28 _public typedef_ `using FRigidScenePtr = TRigidScenePtr<FContext>;`
- L30 _public function_ `UE_INTERNAL TRigidBodyContainerPtrImpl(IRigidBodyContainer* InBodyContainer) : BodyContainerRaw(InBodyContainer)`
- L35 _public prototype_ `~TRigidBodyContainerPtrImpl() = default;`
- L38 _public function_ `bool IsValid() const`
- L43 _public function_ `FRigidBodyContainerHandle GetHandle() const`
- L48 _public function_ `int32 GetNumBodies() const`
- L53 _public function_ `TRigidBodyPtr<FContext> GetBody(const FRigidObjectId& InBodyId) const`
- L58 _public function_ `TRigidBodyPtr<FContext> CreateBody(const FRigidDebugName& InName, ERigidMovementType InMovementType) const`
- L63 _public function_ `void DestroyBody(TRigidBodyPtr<FContext>&& InBodyPtr)`
- L68 _public function_ `UE_INTERNAL void Reset()`
- L73 _public function_ `UE_INTERNAL const FRigidTypeId& GetTypeId() const`
- L78 _public function_ `UE_INTERNAL IRigidBodyContainer* Get() const`
- L85 _private member_ `IRigidBodyContainer* BodyContainerRaw = nullptr;` — Pointer to implementation, object depends on Context type

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Physics` (scope `UE`)

### `Source/Runtime/Experimental/RigidPhysics/Public/RigidPhysics/RigidBodyContainerHandle.h` (Public)


#### class `UE::Physics::FRigidBodyContainerHandle`  
`class FRigidBodyContainerHandle`  
_L18-47_
- L21 _public prototype_ `FRigidBodyContainerHandle() = default;`
- L22 _public prototype_ `UE_INTERNAL FRigidBodyContainerHandle(const FRigidSceneId& InSceneId, const FRigidObjectId& InBodyContainerId);`
- L29 _public function_ `template <typename ContextType> TRigidBodyContainerPtr<ContextType> Pin(const ContextType& InContext) const` — Convert the handle to a pointer in the specified context.
- L38 _public prototype_ `UE_INTERNAL void Reset();`
- L39 _public prototype_ `UE_INTERNAL const FRigidObjectId& GetId() const;`
- L40 _public prototype_ `UE_INTERNAL const FRigidSceneId& GetSceneId() const;`
- L43 _private prototype_ `IRigidBodyContainer* PinInternal(const IRigidScene* InScene) const;`
- L45 _private member_ `FRigidObjectId BodyContainerId;`
- L46 _private member_ `FRigidSceneId SceneId;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Physics` (scope `UE`)

### `Source/Runtime/Experimental/RigidPhysics/Public/RigidPhysics/RigidBodyHandle.h` (Public)


#### class `UE::Physics::FRigidBodyHandle`  
`class FRigidBodyHandle`  
_L21-54_
- desc: A handle to a rigid body that may be copied and stored. A body reference can be retrieved by pinning the handle with a context.
- L24 _public prototype_ `FRigidBodyHandle() = default;`
- L25 _public prototype_ `FRigidBodyHandle(const FRigidBodyHandle&) = default;`
- L27 _public prototype_ `UE_INTERNAL FRigidBodyHandle(const FRigidSceneId& InSceneId, const FRigidObjectId& InBodyId);`
- L34 _public function_ `template <typename ContextType> TRigidBodyPtr<ContextType> Pin(const ContextType& InContext) const` — Convert the handle to a pointer in the specified context.
- L43 _public prototype_ `UE_INTERNAL const FRigidObjectId& GetId() const;`
- L44 _public prototype_ `UE_INTERNAL const FRigidSceneId& GetSceneId() const;`
- L45 _public prototype_ `UE_INTERNAL void Reset();`
- L50 _private prototype_ `IRigidBody* PinInternal(const IRigidScene* Scene) const;`
- L52 _private member_ `FRigidObjectId BodyId;`
- L53 _private member_ `FRigidSceneId SceneId;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Physics` (scope `UE`)

### `Source/Runtime/Experimental/RigidPhysics/Public/RigidPhysics/RigidContext.h` (Public)


#### class `UE::Physics::TRigidContext`  
`template <ERigidContextType ContextTypeParam, ERigidLockType LockTypeParam> class TRigidContext`  
_L18-79_
- desc: A Context holds a lock (RW or RO) and converts object handles to context-specific object pointers.
- L21 _public member_ `static constexpr ERigidContextType ContextType = ContextTypeParam;`
- L22 _public member_ `static constexpr ERigidLockType LockType = LockTypeParam;`
- L23 _public member_ `static constexpr bool bWriteEnabled = (LockType == ERigidLockType::ReadWrite);`
- L25 _public typedef_ `using FContext = TRigidContext<ContextType, LockType>;`
- L27 _public function_ `UE_INTERNAL TRigidContext(IRigidScene* InScene)`
- L37 _public function_ `~TRigidContext()`
- L45 _public function_ `bool IsValid() const`
- L50 _public function_ `operator bool() const`
- L56 _public function_ `const TRigidScenePtrImpl<FContext>* operator->() const requires (!FContext::bWriteEnabled)` — Expose Scene API on Context
- L61 _public function_ `TRigidScenePtrImpl<FContext>* operator->() const requires (FContext::bWriteEnabled)`
- L66 _public function_ `UE_INTERNAL const TRigidScenePtr<FContext>& GetScene() const`
- L71 _public function_ `UE_INTERNAL const IRigidScene* GetRawSceneChecked(const FRigidSceneId InSceneId) const`
- L77 _private member_ `TRigidScenePtr<FContext> ScenePtr;`
- L78 _private member_ `FRigidSceneId SceneId;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Physics` (scope `UE`)

### `Source/Runtime/Experimental/RigidPhysics/Public/RigidPhysics/RigidFactory.h` (Public)


#### class `UE::Physics::IRigidFactory`  
`class IRigidFactory`  
_L12-21_
- L15 _public prototype_ `IRigidFactory() = default;`
- L16 _public prototype_ `virtual ~IRigidFactory() = default;`
- L18 _public prototype_ `virtual const FRigidTypeId& GetSceneTypeId() const = 0;`
- L19 _public prototype_ `virtual FRigidSceneHandle CreateScene(const FRigidDebugName& InName, const IRigidSceneSettings* InSettings) = 0;`
- L20 _public prototype_ `virtual void DestroyScene(const FRigidSceneHandle& InSceneHandle) = 0;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Physics` (scope `UE`)

### `Source/Runtime/Experimental/RigidPhysics/Public/RigidPhysics/RigidFwd.h` (Public)


#### enum `UE::Physics::EJointMotionType`  
`enum class EJointMotionType : int32`  
_L111-116_
- L113 _public enumerator_ `Free`
- L114 _public enumerator_ `Limited`
- L115 _public enumerator_ `Locked`

#### enum `UE::Physics::ERigidVisitorResponse`  
`enum class ERigidVisitorResponse`  
_L118-122_
- L120 _public enumerator_ `Continue`
- L121 _public enumerator_ `Break`

#### enum `UE::Physics::ERigidMovementType`  
`enum class ERigidMovementType`  
_L124-129_
- L126 _public enumerator_ `Static`
- L127 _public enumerator_ `Kinematic`
- L128 _public enumerator_ `Dynamic`

#### enum `UE::Physics::ERigidContextType`  
`enum class ERigidContextType`  
_L133-137_
- desc: Physics execution is split into Game and Simulation contexts. In async modes, these are on different threads.
- L135 _public enumerator_ `Game`
- L136 _public enumerator_ `Sim`

#### enum `UE::Physics::ERigidLockType`  
`enum class ERigidLockType`  
_L141-146_
- desc: The context must be locked before reading or writing to any objects in physics. The lock may be read-only or read-write.
- L143 _public enumerator_ `None`
- L144 _public enumerator_ `ReadOnly`
- L145 _public enumerator_ `ReadWrite`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_RIGIDPHYSICS_API_ENABLED 0` — NOTE: Must be 0 (for now)
- L19 _macro_ `#define UE_RIGIDPHYSICS_LEGACY_API UE_INTERNAL /*UE_DEPRECATED(5.8, "TODO")*/`
- L24 _macro_ `#define UE_RIGIDPHYSICS_CHECK_ENABLED 1` — Enable checks in the Rigid accessors. This can add significant overhead.
- L27 _macro_ `#define UE_RIGIDPHYSICS_CONTAINERSCENEHANDLE_ENABLED 1` — Required to show the Objects associated with a Handle in the debugger
- L32 _macro_ `#define UE_RIGIDPHYSICS_SCENEHANDLE_SAFTEY_ENABLED 0` — Enable to assert when Handles are Pinned after their scene is destroyed. This adds a Weak Pointer to SceneHandle which must be checked every time we pin so is not recommended if performance is a concern
- L35 _macro_ `#define UE_RIGIDPHYSICS_CHECK_ENABLED 0`
- L36 _macro_ `#define UE_RIGIDPHYSICS_CONTAINERSCENEHANDLE_ENABLED 0`
- L41 _macro_ `#define UE_RIGIDPHYSICS_CHECK(expr) check(expr)`
- L42 _macro_ `#define UE_RIGIDPHYSICS_CHECKF(expr, format, ...) checkf(expr, format, ##__VA_ARGS__)`
- L44 _macro_ `#define UE_RIGIDPHYSICS_CHECK(X)`
- L45 _macro_ `#define UE_RIGIDPHYSICS_CHECKF(expr, format, ...)`
- L51 _typedef_ `template<typename T> struct TBounds;` — Math/Bounds.h
- L52 _typedef_ `using FBounds3d = TBounds<double>;`
- L58 _namespace_ `namespace UE`
- L58 _namespace_ `namespace Physics` (scope `UE`)
- L97 _typedef_ `template<typename ContextType> using TJointConstraintPtr = TRigidObjectPtr<TJointConstraintPtrImpl<ContextType>>;` (scope `UE::Physics`)
- L98 _typedef_ `template<typename ContextType> using TJointConstraintPtr = TRigidObjectPtr<TJointConstraintPtrImpl<ContextType>>;` (scope `UE::Physics`)
- L99 _typedef_ `template<typename ContextType> using TJointConstraintPtr = TRigidObjectPtr<TJointConstraintPtrImpl<ContextType>>;` (scope `UE::Physics`)
- L100 _typedef_ `template<typename ContextType> using TJointConstraintPtr = TRigidObjectPtr<TJointConstraintPtrImpl<ContextType>>;` (scope `UE::Physics`)
- L101 _typedef_ `template<typename ContextType> using TJointConstraint6DOFPtr = TRigidObjectPtr<TJointConstraint6DOFPtrImpl<ContextType>>;` (scope `UE::Physics`)
- L102 _typedef_ `template<typename ContextType> using TRigidBodyContainerPtr = TRigidObjectPtr<TRigidBodyContainerPtrImpl<ContextType>>;` (scope `UE::Physics`)
- L103 _typedef_ `template<typename ContextType> using TRigidBodyPtr = TRigidObjectPtr<TRigidBodyPtrImpl<ContextType>>;` (scope `UE::Physics`)
- L105 _typedef_ `using FRigidDebugName = ::Chaos::FSharedDebugName;` (scope `UE::Physics`)
- L106 _typedef_ `using FRigidSceneWeakPtr = TWeakPtr<IRigidScene, ESPMode::ThreadSafe>;` (scope `UE::Physics`)
- L109 _namespace_ `namespace UE`
- L109 _namespace_ `namespace Physics` (scope `UE`)
- L149 _typedef_ `template<ERigidContextType ContextTypeParam, ERigidLockType LockTypeParam> class TRigidContext;` (scope `UE::Physics`)
- L150 _typedef_ `using FRigidContextGameRW = TRigidContext<ERigidContextType::Game, ERigidLockType::ReadWrite>;` (scope `UE::Physics`)
- L151 _typedef_ `using FRigidContextSimRW = TRigidContext<ERigidContextType::Sim, ERigidLockType::ReadWrite>;` (scope `UE::Physics`)
- L161 _namespace_ `namespace UE`
- L161 _namespace_ `namespace Physics` (scope `UE`)
- L164 _typedef_ `template<typename ObjectType> class UE_INTERNAL TRigidObjectRegistry;` (scope `UE::Physics`)
- L165 _typedef_ `using UE_INTERNAL FRigidBodyContainerRegistry = TRigidObjectRegistry<IRigidBodyContainer>;` (scope `UE::Physics`)
- L166 _typedef_ `using UE_INTERNAL FRigidGeometryCollectionRegistry = TRigidObjectRegistry<IRigidGeometryCollection>;` (scope `UE::Physics`)
- L167 _typedef_ `using UE_INTERNAL FRigidBodyRegistry = TRigidObjectRegistry<IRigidBody>;` (scope `UE::Physics`)
- L170 _prototype_ `extern uint32 GetTypeHash(UE::Physics::FRigidObjectId& RigidBodyId);`

### `Source/Runtime/Experimental/RigidPhysics/Public/RigidPhysics/RigidGeometryCollection.h` (Public)


#### class `UE::Physics::TRigidGeometryCollectionPtrImpl`  
`template <typename ContextType> class UE_INTERNAL TRigidGeometryCollectionPtrImpl`  
_L19-100_
- desc: Utility wrapper around IRigidGeometryCollection that adds Context and allows TRigidGeometryCollectionPtr to have pointer semantics without exposing IRigidGeometryCollection
- L22 _public typedef_ `using FContext = ContextType;`
- L23 _public typedef_ `using FInterface = IRigidGeometryCollection;`
- L24 _public typedef_ `using FHandle = FRigidGeometryCollectionHandle;`
- L25 _public typedef_ `using FRigidScenePtr = TRigidScenePtr<FContext>;`
- L27 _public prototype_ `TRigidGeometryCollectionPtrImpl() = default;`
- L28 _public function_ `UE_INTERNAL TRigidGeometryCollectionPtrImpl(IRigidGeometryCollection* InGeometryCollection) : GeometryCollectionRaw(InGeometryCollection)`
- L33 _public function_ `UE_INTERNAL TRigidGeometryCollectionPtrImpl(IRigidBodyContainer* InBodyContainer) : GeometryCollectionRaw(nullptr)`
- L42 _public prototype_ `~TRigidGeometryCollectionPtrImpl() = default;`
- L47 _public function_ `bool IsValid() const`
- L52 _public function_ `FRigidGeometryCollectionHandle GetHandle() const`
- L62 _public function_ `int32 GetNumBodies() const`
- L67 _public function_ `TRigidBodyPtr<FContext> GetBodyAt(int32 InBodyIndex) const`
- L72 _public function_ `TRigidBodyPtr<FContext> GetBody(const FRigidObjectId& InBodyId) const`
- L77 _public function_ `UE_INTERNAL void Reset()`
- L82 _public function_ `UE_INTERNAL const FRigidTypeId& GetTypeId() const`
- L87 _public function_ `UE_INTERNAL IRigidGeometryCollection* Get() const`
- L92 _public function_ `UE_INTERNAL TRigidBodyPtr<FContext> CreateBody(const FRigidDebugName& InName, ERigidMovementType InMovementType)`
- L99 _private member_ `IRigidGeometryCollection* GeometryCollectionRaw = nullptr;` — Pointer to implementation, object depends on Context type

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Physics` (scope `UE`)

### `Source/Runtime/Experimental/RigidPhysics/Public/RigidPhysics/RigidGeometryCollectionHandle.h` (Public)


#### class `UE::Physics::FRigidGeometryCollectionHandle`  
`class FRigidGeometryCollectionHandle`  
_L35-67_
- desc: A handle to a GeometryCollection. A GeometryCollection is a type of BodyContainer and the handle is auto-castable to FRigidBodyContainerHandle, but the reverse is more complex. NOTE: If the GeometryCollectionHandle has a valid BodyContainerHandle, it will always reference a GC. There should be no way to get a GCHandle that contains a non-GC body container handle. This is enforced because the only way to create a FRigidGeometryCollectionHandle is from a TRigidGeometryCollectionPtr. To safely convert a FRigidBodyContainerHandle to FRigidGeometryCollectionHandle we must go through pointer conversion: FRigidBodyContainerHandle BodyContainerHandle = ...; TRigidGeometryCollectionPtrImpl<FRigidContextGameRW> GCPtr = BodyContainerHandle.Pin(Context); FRigidGeometryCollectionHandle GCHandle = GCPtr; This ensures that we get an empty handle if BodyContainerHandle is not a GC, because the cast from TRigidBodyContainerPtr to TRigidGeometryCollectionPtr will fail and return nullptr.
- L38 _public prototype_ `FRigidGeometryCollectionHandle() = default;`
- L39 _public prototype_ `UE_INTERNAL FRigidGeometryCollectionHandle(const FRigidSceneId& InSceneId, const FRigidObjectId& InBodyContainerId);`
- L46 _public function_ `template <typename ContextType> TRigidGeometryCollectionPtr<ContextType> Pin(const ContextType& InContext) const` — Convert the handle to a pointer in the specified context
- L56 _public prototype_ `UE_INTERNAL void Reset();`
- L57 _public prototype_ `UE_INTERNAL const FRigidObjectId& GetId() const;`
- L58 _public prototype_ `UE_INTERNAL const FRigidSceneId& GetSceneId() const;`
- L60 _public prototype_ `UE_INTERNAL FRigidBodyContainerHandle AsBodyContainerHandle() const;`
- L61 _public prototype_ `UE_INTERNAL operator FRigidBodyContainerHandle() const;`
- L64 _private prototype_ `IRigidGeometryCollection* PinInternal(IRigidBodyContainer* Container) const;`
- L66 _private member_ `FRigidBodyContainerHandle BodyContainerHandle;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Physics` (scope `UE`)

### `Source/Runtime/Experimental/RigidPhysics/Public/RigidPhysics/RigidLockable.h` (Public)


#### class `UE::Physics::IRigidLockable`  
`class UE_INTERNAL IRigidLockable : public IRigidTyped`  
_L12-22_
- inherits: `IRigidTyped`
- L17 _public prototype_ `UE_INTERNAL IRigidLockable() = default;`
- L18 _public prototype_ `UE_INTERNAL virtual ~IRigidLockable() = default;`
- L20 _public prototype_ `UE_INTERNAL virtual void Lock(ERigidLockType InLockType) const = 0;`
- L21 _public prototype_ `UE_INTERNAL virtual void Unlock(ERigidLockType InLockType) const = 0;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Physics` (scope `UE`)

### `Source/Runtime/Experimental/RigidPhysics/Public/RigidPhysics/RigidLog.h` (Public)


#### Free symbols / members of external scopes

- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogRigidPhysics, Log, All);`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Physics` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Physics`)
- L15 _function_ `template <typename FuncNameType, typename TypeNameType> UE_INTERNAL inline void LogUnsupportedAPI(const FuncNameType& FuncName, const TypeNameType& TypeName)` (scope `UE::Physics::Private`)
- L23 _macro_ `#define RIGIDPHYSICS_API_UNSUPPORTED() UE::Physics::Private::LogUnsupportedAPI(__FUNCTION__, GetTypeName());`

### `Source/Runtime/Experimental/RigidPhysics/Public/RigidPhysics/RigidMaterialIndex.h` (Public)


#### class `UE::Physics::FMaterialIndex`  
`class FMaterialIndex`  
_L11-19_
- L14 _public prototype_ `FMaterialIndex(const uint16 InIndex);`
- L15 _public prototype_ `operator uint16() const;`
- L18 _private member_ `uint16 Index = INDEX_NONE;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Physics` (scope `UE`)

### `Source/Runtime/Experimental/RigidPhysics/Public/RigidPhysics/RigidMaterials.h` (Public)


#### class `UE::Physics::FMaterialHandle`  
`class FMaterialHandle`  
_L19-33_
- L22 _public prototype_ `FMaterialHandle() = default;`
- L23 _public prototype_ `UE_INTERNAL FMaterialHandle(const Chaos::FMaterialHandle& InMaterialHandle);`
- L25 _public prototype_ `bool operator==(const FMaterialHandle&) const = default;`
- L26 _public prototype_ `bool operator!=(const FMaterialHandle&) const = default;`
- L28 _public prototype_ `UE_INTERNAL Chaos::FMaterialHandle GetMaterialHandle() const;`
- L29 _public prototype_ `UE_INTERNAL Chaos::FChaosPhysicsMaterial* GetMaterial() const;`
- L32 _private member_ `uint32 HandleData = 0;`

#### class `UE::Physics::FMaterialMaskHandle`  
`class FMaterialMaskHandle`  
_L35-49_
- L38 _public prototype_ `FMaterialMaskHandle() = default;`
- L39 _public prototype_ `UE_INTERNAL FMaterialMaskHandle(const Chaos::FMaterialMaskHandle& InMaterialMaskHandle);`
- L41 _public prototype_ `bool operator==(const FMaterialMaskHandle&) const = default;`
- L42 _public prototype_ `bool operator!=(const FMaterialMaskHandle&) const = default;`
- L44 _public prototype_ `UE_INTERNAL Chaos::FMaterialMaskHandle GetMaterialMaskHandle() const;`
- L45 _public prototype_ `UE_INTERNAL Chaos::FChaosPhysicsMaterialMask* GetMaterialMask() const;`
- L48 _private member_ `uint32 HandleData = 0;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Chaos`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Physics` (scope `UE`)

### `Source/Runtime/Experimental/RigidPhysics/Public/RigidPhysics/RigidModifier.h` (Public)


#### class `UE::Physics::IRigidSceneModifier`  
`class IRigidSceneModifier`  
_L13-42_
- L16 _public prototype_ `IRigidSceneModifier() = default;`
- L17 _public prototype_ `virtual ~IRigidSceneModifier() = default;`
- L21 _public function_ `virtual void PreSimulate(const FRigidContextGameRW& Context)` — Called from the game context before physics is ticked for this frame. Can be used to update inputs to the objects used in the sim context.
- L27 _public function_ `virtual void PostSimulate(const FRigidContextGameRW& Context)` — Call from the game context after physics is ticked for this frame, but before the sim results have been sent out to the game framework objects (Actors, Components, etc.)
- L33 _public function_ `virtual void PreTick(const FRigidContextSimRW& Context)` — Called from the simulation context before each simulation tick. At this point you can add forces, move bodies, or do pretty much anything to the scene or objects in it, and the results will impact the next tick.
- L39 _public function_ `virtual void PostTick(const FRigidContextSimRW& Context)` — Called from the simulation context at the end of each simulation tick. At this point you can modify physics object state and the altered results will be reported back to the game, and be used for the next tick.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Physics` (scope `UE`)

### `Source/Runtime/Experimental/RigidPhysics/Public/RigidPhysics/RigidObjectId.h` (Public)


#### class `UE::Physics::FRigidObjectId`  
`class FRigidObjectId`  
_L15-77_
- desc: An ID for an object held in an array that is guaranteed to be unique and never reused within its container (as long as less than 1<<31 objects are allocated). There is no guarantee of uniqueness between containers, which means you need a Container + Id to access an object. (E.g., see FRigidBodyHandle, and FRigidBodyContainerHandle).
- L18 _public function_ `FRigidObjectId() : ArrayIndex(INDEX_NONE) , Epoch(INDEX_NONE)`
- L24 _public function_ `FRigidObjectId(int32 InIndex, int32 InEpoch) : ArrayIndex(InIndex) , Epoch(InEpoch)`
- L30 _public function_ `bool IsValid() const`
- L47 _public function_ `UE_INTERNAL int32 GetArrayIndex() const`
- L52 _public function_ `UE_INTERNAL int32 GetEpoch() const`
- L57 _public function_ `UE_INTERNAL void Reset()`
- L64 _protected function_ `uint64 ToUInt64() const`
- L69 _protected function_ `void FromInt64(uint64 InInt)`
- L75 _protected member_ `int32 ArrayIndex = INDEX_NONE;`
- L76 _protected member_ `int32 Epoch = INDEX_NONE;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Physics` (scope `UE`)
- L37 _function_ `friend bool operator<(const FRigidObjectId& L, const FRigidObjectId& R)` (scope `UE::Physics`)
- L42 _function_ `friend uint32 GetTypeHash(const FRigidObjectId& InId)` (scope `UE::Physics`)

### `Source/Runtime/Experimental/RigidPhysics/Public/RigidPhysics/RigidObjectPtr.h` (Public)


#### class `UE::Physics::TRigidObjectPtr`  
`template <typename PointerImplType> class TRigidObjectPtr`  
_L30-129_
- desc: A Context-Specific Smart Pointer to a physics object. This is a wrapper around a smart pointer implementation object like TRigidBodyPtrImpl, TRigidBodyContainerPtrImpl, etc. It provides operator-> to give it const and non-const pointer semantics and behaviour. May be "null". Check IsValid() (or cast to bool) before dereferencing. Cannot be copied or stored - use Handles for that. NOTE: Much like a regular pointer, a "valid" pointer may still reference deleted memory if the object is destroyed after the Handle is Pinned. Do not use pointers, even to check for validity, after the underlying object has been destroyed. If the underlying object may have been destroyed, you should re-Pin the Handle to obtain a new pointer.
- L33 _public typedef_ `using FPointerImpl = PointerImplType;`
- L34 _public typedef_ `using FContext = FPointerImpl::FContext;`
- L35 _public typedef_ `using FInterface = FPointerImpl::FInterface;`
- L36 _public typedef_ `using FHandle = FPointerImpl::FHandle;`
- L40 _public prototype_ `TRigidObjectPtr() = default;`
- L41 _public function_ `UE_INTERNAL TRigidObjectPtr(FInterface* InObject) : Impl(InObject)`
- L53 _public function_ `UE_INTERNAL TRigidObjectPtr(const TRigidObjectPtr<OtherPointerImplType>& InPtr) : Impl(InPtr.Get())`
- L58 _public prototype_ `~TRigidObjectPtr() = default;`
- L61 _public function_ `void Reset()` — Reset the pointer (it will now be Invalid)
- L69 _public function_ `bool IsValid() const` — Has this pointer been initialized with a valid body pointer? NOTE: This will still return true if the underlying object is destroyed after the Handle is Pinned. If this is a possibility, the Handle should be re-Pinned.
- L76 _public function_ `operator bool() const` — Auto cast to bool to support using in if statements e.g., if (TRigidBodyPtr<FRigidContextGameRW> Body = BodyHandle.Pin(Context)) { ... }
- L82 _public function_ `FHandle ToHandle() const` — Extract the handle
- L88 _public function_ `operator FHandle() const` — Cast to a handle
- L94 _public function_ `const FPointerImpl* operator->() const` — Const pointer semantics
- L101 _public function_ `FPointerImpl* operator->() const requires (FContext::bWriteEnabled)` — Non-const pointer semantics
- L108 _public function_ `UE_INTERNAL FInterface* Get() const` — Extract the object interface (internal use only)
- L113 _public function_ `UE_INTERNAL void Init(FInterface* InObject)`
- L119 _private function_ `void CheckIsValid() const`
- L128 _private member_ `mutable FPointerImpl Impl = nullptr;` — Mutable to support const TRigidObjectPtr to an non-const object i.e., this wrapper cannot change, but the pointee is mutabale if the wrapper was created from a mutable context. This avoids an undefined behaviour compiler warning.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Physics` (scope `UE`)

### `Source/Runtime/Experimental/RigidPhysics/Public/RigidPhysics/RigidObjectRegistry.h` (Public)


#### class `UE::Physics::TRigidObjectRegistryItem`  
`template <typename ObjectPtrType> class UE_INTERNAL TRigidObjectRegistryItem`  
_L17-39_
- desc: Info held in the TRigidObjectRegistry indexed by ObjectId
- L20 _public typedef_ `using FObjectPtrType = ObjectPtrType;`
- L22 _public function_ `UE_INTERNAL TRigidObjectRegistryItem() : Object(nullptr) , Epoch(0) , AddedObjectsIndex(INDEX_NONE)`
- L30 _public member_ `FObjectPtrType Object;` — The object that was added
- L35 _public member_ `int32 Epoch;` — How many times the Object's slot in TRigidObjectRegistry has been used. This will be unique for every reuse of the slot and is used by Object Handles to determine if they have expired or not.
- L38 _public member_ `int32 AddedObjectsIndex;` — Index into the AddedObjects array in TRigidObjectRegistry

#### class `UE::Physics::TRigidObjectRegistry`  
`template <typename ObjectType> class UE_INTERNAL TRigidObjectRegistry`  
_L57-246_
- desc: A Registry for Rigid Objects that allows us to convert from a Handle to an Object Pointer. Each registered object is assigned an Id, which is a combination of an array index and an epoch counter. The array index and epoch counter combined are unique for every allocated object, even when array indices get reused after an object is unregistered and a new one takes its place. ObjectType must have a GetHandle() function. TODO_CHAOSAPI: ideally would not require a GetHandle() function on the object - it is only used the repack the AddedObjects array. Should be a template policy instead to get to the Id? See RemoveObject(). TODO_CHAOSAPI: this container will fail to work if we reuse any ObjectsById array index enough times to wrap its Epoch. We can mitigate this by removing those indices from the free list. This will leave unusable gaps in the array but would allow for infinite growth at the cost of some wasted memory.
- L60 _public typedef_ `using FObjectType = ObjectType;`
- L61 _public typedef_ `using FObjectPtrType = ObjectType*;`
- L62 _public typedef_ `using FObjectRegistryItem = TRigidObjectRegistryItem<FObjectPtrType>;`
- L65 _public function_ `UE_INTERNAL TRigidObjectRegistry(int32 InSlack) : ArraySlack(InSlack) , TotalNumAdded(0) , bIsVisiting(false)`
- L72 _public prototype_ `UE_INTERNAL ~TRigidObjectRegistry() = default;`
- L75 _public function_ `UE_INTERNAL int32 GetNumObjects() const` — The number of objects that have been added (and not yet removed)
- L81 _public function_ `UE_INTERNAL bool IsEmpty() const` — True if there are no objects in the registry
- L89 _public function_ `UE_INTERNAL FRigidObjectId AddObject(FObjectPtrType InObject)` — Add an object to the registry and assign it an Id. The Id is persistent and will never be reused as long as less that 1<<31 objects are added. After that, Ids may start to repeat.
- L121 _public function_ `UE_INTERNAL void RemoveObject(const FRigidObjectId& InObjectId)`
- L167 _public function_ `UE_INTERNAL void RemoveObjectChecked(const FRigidObjectId& InObjectId, const ObjectType* Object)`
- L173 _public function_ `UE_INTERNAL FObjectType* FindObject(const FRigidObjectId& InId) const`
- L188 _public function_ `UE_INTERNAL void VisitObjects(const TFunctionRef<ERigidVisitorResponse(FObjectType*)>& Visitor)` — Visit all of the added objects in somewhat arbitrary order that may change whenever objects are added or removed.
- L203 _private function_ `void ReserveArray(int32 MaxItems)`
- L226 _private member_ `TArray<FObjectType*> AddedObjects;` — An array with no holes containing all currently allocated objects indexed by ObjectId.AddedObjectsIndex. This exists to support iteration over items and easier debugging - we may be able remove it later. NOTE: Object position in this array is not persistent (RemoveObject uses RemoveAtSwap) TODO_CHAOSAPI: see if we really need the AddedObjects array.
- L233 _private member_ `TArray<FObjectRegistryItem> ObjectsById;` — An Id->Object map, implemented as an array indexed by ObjectId.ArrayIndex. Indices into this array are persistent as long as the object exists, but the array may contain holes. Array Entries will be reused after objects have been deleted, and the Epoch counter is used to validate handles against the current object at the array index. This array is presized and will often contain many empty (unused) elements.
- L236 _private member_ `TArray<int32> ObjectsByIdFreeIndices;` — A pool of unused entries in ObjectsById.
- L239 _private member_ `int32 ArraySlack;` — How much extra to allocate in ObjectsById when we run out of space.
- L242 _private member_ `int32 TotalNumAdded;` — How many objects have been added. This is only used to assert if we may reuse Ids.
- L245 _private member_ `bool bIsVisiting;` — Use to trap modifications while in the Visitor loop

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Physics` (scope `UE`)

### `Source/Runtime/Experimental/RigidPhysics/Public/RigidPhysics/RigidPhysicsService.h` (Public)


#### class `UE::Physics::FRigidPhysicsService`  
`class FRigidPhysicsService`  
_L15-29_
- L18 _public prototype_ `static FRigidPhysicsService& GetInstance();`
- L20 _public prototype_ `void RegisterFactory(TUniquePtr<IRigidFactory>&& InFactory, TUniquePtr<IRigidSceneSettings>&& InDefaultSettings);`
- L22 _public prototype_ `FRigidSceneHandle CreateScene(const FRigidDebugName& InName) const;`
- L23 _public prototype_ `void DestroyScene(const FRigidSceneHandle& InHandle) const;`
- L25 _public prototype_ `void Reset();`
- L27 _private member_ `TUniquePtr<IRigidFactory> Factory;`
- L28 _private member_ `TUniquePtr<IRigidSceneSettings> SceneSettings;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Physics` (scope `UE`)

### `Source/Runtime/Experimental/RigidPhysics/Public/RigidPhysics/RigidScene.h` (Public)


#### class `UE::Physics::TRigidScenePtrImpl`  
`template <typename ContextType> class UE_INTERNAL TRigidScenePtrImpl`  
_L23-148_
- desc: A wrapper around IRigidScene. Exists only to give pointer semantics to TRigidScenePtr.
- L26 _public typedef_ `using FContext = ContextType;`
- L27 _public typedef_ `using FInterface = IRigidScene;`
- L28 _public typedef_ `using FHandle = FRigidSceneHandle;`
- L30 _public prototype_ `UE_INTERNAL TRigidScenePtrImpl() = default;`
- L31 _public function_ `UE_INTERNAL TRigidScenePtrImpl(IRigidScene* InScene) : SceneRaw(InScene)`
- L35 _public prototype_ `~TRigidScenePtrImpl() = default;`
- L37 _public function_ `bool IsValid() const`
- L42 _public function_ `FRigidSceneHandle GetHandle() const`
- L47 _public function_ `IRigidBodyContainer* GetBodyContainer(const FRigidObjectId& InBodyContainerId) const`
- L52 _public function_ `IRigidGeometryCollection* GetGeometryCollection(const FRigidObjectId& InGeometryCollectionId) const`
- L57 _public function_ `void RegisterModifier(IRigidSceneModifier* Modifier) requires CIsGameContext<FContext>`
- L62 _public function_ `void UnregisterModifier(IRigidSceneModifier* Modifier) requires CIsGameContext<FContext>`
- L67 _public function_ `TRigidBodyPtr<FContext> CreateBody(const FRigidDebugName& InName, ERigidMovementType InMovementType) requires CIsGameContext<FContext>`
- L72 _public function_ `void DestroyBody(TRigidBodyPtr<FContext>&& InBody) requires CIsGameContext<FContext>`
- L81 _public function_ `TRigidGeometryCollectionPtr<FContext> CreateGeometryCollection(const FRigidDebugName& InName, const FSimulationParameters& InParameters) requires CIsGameContext<FContext>`
- L86 _public function_ `void DestroyGeometryCollection(TRigidGeometryCollectionPtr<ContextType>&& InGC) requires CIsGameContext<FContext>`
- L92 _public function_ `void AddDisabledCollisions(const TMap<FRigidBodyHandle, TArray<FRigidBodyHandle>>& InMap) requires CIsGameContext<FContext>`
- L97 _public function_ `TJointConstraint6DOFPtr<FContext> CreateJointConstraint6DOF() requires CIsGameContext<FContext>`
- L102 _public function_ `void DestroyJointConstraint(TJointConstraint6DOFPtr<FContext>&& InConstraint) requires CIsGameContext<FContext>`
- L111 _public function_ `UE_INTERNAL IJointConstraint* GetJointConstraint(const FRigidObjectId& InConstraintId) const`
- L116 _public function_ `bool Query(const FRigidQueryDesc& QueryDesc, TArray<FRigidQueryHit>& OutHits) const`
- L121 _public function_ `void StartTick(const float InDt) requires CIsGameContext<FContext>`
- L126 _public function_ `void WaitOnTick() requires CIsGameContext<FContext>`
- L131 _public function_ `void EndTick() requires CIsGameContext<FContext>`
- L136 _public function_ `UE_INTERNAL void Reset()`
- L141 _public function_ `UE_INTERNAL IRigidScene* Get() const`
- L147 _private member_ `IRigidScene* SceneRaw = nullptr;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Physics` (scope `UE`)

### `Source/Runtime/Experimental/RigidPhysics/Public/RigidPhysics/RigidSceneHandle.h` (Public)


#### class `UE::Physics::FRigidSceneHandle`  
`class FRigidSceneHandle`  
_L18-45_
- desc: A handle to a rigid body scene. FRigidSceneHandle is only used in the GameContext because all PhysicsContext use cases (callbacks, modifiers, etc.) will be passed their scene as a TRigidScenePtr.
- L21 _public prototype_ `FRigidSceneHandle() = default;`
- L22 _public prototype_ `UE_INTERNAL FRigidSceneHandle(FRigidScene* InScene);`
- L23 _public prototype_ `UE_INTERNAL FRigidSceneHandle(const FRigidSceneId& InSceneId);`
- L29 _public prototype_ `FRigidContextGameRO LockRO() const;` — Lock the scene on the game thread and return a locked context for use in pinning object handles
- L30 _public prototype_ `FRigidContextGameRW LockRW() const;`
- L32 _public prototype_ `UE_INTERNAL void Reset();`
- L33 _public prototype_ `UE_INTERNAL FRigidSceneId GetId() const;`
- L34 _public prototype_ `UE_INTERNAL IRigidScene* GetScene() const;`
- L37 _private prototype_ `void DoSafetyCheck() const;`
- L39 _private member_ `FRigidSceneId SceneId;`
- L41 _private member_ `IRigidScene* SceneRaw = nullptr;` — NOTE: Always the GT Scene, but never accessed on PT
- L43 _private member_ `FRigidSceneWeakPtr SceneWeak;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Physics` (scope `UE`)

### `Source/Runtime/Experimental/RigidPhysics/Public/RigidPhysics/RigidSceneId.h` (Public)


#### class `UE::Physics::FRigidSceneId`  
`class FRigidSceneId`  
_L11-26_
- L14 _public prototype_ `bool operator==(const FRigidSceneId&) const = default;`
- L15 _public prototype_ `bool operator!=(const FRigidSceneId&) const = default;`
- L19 _public prototype_ `UE_INTERNAL IRigidScene* Get() const;`
- L20 _public prototype_ `UE_INTERNAL void Reset();`
- L25 _private member_ `uint8 Id = static_cast<uint8>(INDEX_NONE);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Physics` (scope `UE`)

### `Source/Runtime/Experimental/RigidPhysics/Public/RigidPhysics/RigidSceneRegistry.h` (Public)


#### class `UE::Physics::FRigidSceneRegistry`  
`class FRigidSceneRegistry`  
_L14-35_
- L17 _public prototype_ `static FRigidSceneRegistry& GetInstance();`
- L19 _public prototype_ `FRigidSceneId Register(IRigidScene* Scene);`
- L20 _public prototype_ `void Unregister(const FRigidSceneId Id);`
- L22 _public prototype_ `IRigidScene* Get(const FRigidSceneId Id) const;`
- L25 _public prototype_ `UE_INTERNAL void Reset();` — Resets the singleton back to empty. Primarily used for tests.
- L28 _private member_ `static constexpr uint32 MaxScenes = 255;`
- L29 _private member_ `static FRigidSceneRegistry Instance;`
- L31 _private prototype_ `FRigidSceneRegistry() = default;`
- L33 _private member_ `uint8 SceneCount = 0;`
- L34 _private member_ `TStaticArray<IRigidScene*, MaxScenes> Scenes;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Physics` (scope `UE`)

### `Source/Runtime/Experimental/RigidPhysics/Public/RigidPhysics/RigidSceneSettings.h` (Public)


#### class `UE::Physics::IRigidSceneSettings`  
`class IRigidSceneSettings : public IRigidTyped`  
_L13-20_
- inherits: `IRigidTyped`
- L18 _public prototype_ `IRigidSceneSettings() = default;`
- L19 _public prototype_ `virtual ~IRigidSceneSettings() = default;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Physics` (scope `UE`)

### `Source/Runtime/Experimental/RigidPhysics/Public/RigidPhysics/RigidShapeInstance.h` (Public)


#### class `UE::Physics::TRigidShapeInstancePtrImpl`  
`template <typename ContextType> class TRigidShapeInstancePtrImpl`  
_L19-221_
- L22 _public typedef_ `using FContext = ContextType;`
- L23 _public typedef_ `using FInterface = IRigidShapeInstance;`
- L24 _public typedef_ `using FHandle = FRigidShapeInstanceHandle;`
- L26 _public prototype_ `UE_INTERNAL TRigidShapeInstancePtrImpl() = default;`
- L27 _public function_ `UE_INTERNAL TRigidShapeInstancePtrImpl(IRigidShapeInstance* InShapeInstance) : ShapeInstanceRaw(InShapeInstance)`
- L32 _public prototype_ `TRigidShapeInstancePtrImpl(const TRigidShapeInstancePtrImpl&) = delete;`
- L34 _public function_ `TRigidShapeInstancePtrImpl(TRigidShapeInstancePtrImpl&& InPtr) : ShapeInstanceRaw(InPtr.ShapeInstanceRaw)`
- L40 _public function_ `~TRigidShapeInstancePtrImpl()`
- L48 _public function_ `bool IsValid() const`
- L53 _public function_ `FRigidShapeInstanceHandle GetHandle() const`
- L62 _public function_ `FAnyGeometry GetGeometry() const`
- L68 _public function_ `FTransform3f GetLocalTransform() const`
- L74 _public function_ `bool GetQueryEnabled() const`
- L79 _public function_ `void SetQueryEnabled(const bool bInEnabled) requires CIsGameContext<FContext>`
- L84 _public function_ `bool GetSimEnabled() const`
- L89 _public function_ `void SetSimEnabled(const bool bInEnabled) requires CIsGameContext<FContext>`
- L94 _public function_ `bool GetIsProbe() const`
- L99 _public function_ `void SetIsProbe(const bool bInIsProbe) requires CIsGameContext<FContext>`
- L104 _public function_ `ECollisionTraceFlag GetCollisionTraceType() const`
- L109 _public function_ `void SetCollisionTraceType(const ECollisionTraceFlag InTraceFlag) requires CIsGameContext<FContext>`
- L114 _public function_ `Chaos::Filter::FShapeFilterData GetShapeFilter() const`
- L119 _public function_ `void SetShapeFilter(const Chaos::Filter::FShapeFilterData& InShapeFilter) requires CIsGameContext<FContext>`
- L124 _public function_ `Chaos::Filter::FInstanceData GetFilterInstanceData() const`
- L129 _public function_ `void SetFilterInstanceData(const Chaos::Filter::FInstanceData& InInstanceData) requires CIsGameContext<FContext>`
- L134 _public function_ `int32 GetNumMaterials() const`
- L139 _public function_ `FMaterialHandle GetMaterial(const int32 InIndex) const`
- L144 _public function_ `void SetMaterials(TArray<FMaterialHandle>&& InMaterials) requires CIsGameContext<FContext>`
- L149 _public function_ `int32 GetNumMaterialMasks() const`
- L154 _public function_ `FMaterialMaskHandle GetMaterialMask(const int32 InIndex) const`
- L159 _public function_ `void SetMaterialMasks(TArray<FMaterialMaskHandle>&& InMaterialMasks) requires CIsGameContext<FContext>`
- L164 _public function_ `int32 GetNumMaterialMaskMaps() const`
- L169 _public function_ `uint32 GetMaterialMaskMap(const int32 InIndex) const`
- L174 _public function_ `void SetMaterialMaskMaps(TArray<uint32>&& InMaterialMaskMaps) requires CIsGameContext<FContext>`
- L179 _public function_ `int32 GetNumMaterialMaskMapMaterials() const`
- L184 _public function_ `FMaterialHandle GetMaterialMaskMapMaterial(const int32 InIndex) const`
- L189 _public function_ `void SetMaterialMaskMapMaterials(TArray<FMaterialHandle>&& InMaterialMaskMapMaterials) requires CIsGameContext<FContext>`
- L194 _public function_ `void* GetUserData() const`
- L199 _public function_ `void SetUserData(void* InUserData) requires CIsGameContext<FContext>`
- L204 _public function_ `UE_INTERNAL void Reset()`
- L209 _public function_ `UE_INTERNAL const FRigidTypeId& GetTypeId() const`
- L214 _public function_ `UE_INTERNAL IRigidShapeInstance* Get() const`
- L220 _private member_ `IRigidShapeInstance* ShapeInstanceRaw = nullptr;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Physics` (scope `UE`)

### `Source/Runtime/Experimental/RigidPhysics/Public/RigidPhysics/RigidShapeInstanceHandle.h` (Public)


#### class `UE::Physics::FRigidShapeInstanceHandle`  
`class FRigidShapeInstanceHandle`  
_L15-42_
- L18 _public prototype_ `FRigidShapeInstanceHandle() = default;`
- L19 _public prototype_ `FRigidShapeInstanceHandle(const FRigidShapeInstanceHandle&) = default;`
- L20 _public prototype_ `UE_INTERNAL FRigidShapeInstanceHandle(const FRigidSceneId& InSceneId, const FRigidObjectId& InId);`
- L26 _public function_ `template <typename ContextType> TRigidShapeInstancePtr<ContextType> Pin(const ContextType& InContext) const`
- L35 _public prototype_ `UE_INTERNAL const FRigidObjectId& GetId() const;`
- L36 _public prototype_ `UE_INTERNAL const FRigidSceneId& GetSceneId() const;`
- L38 _private prototype_ `IRigidShapeInstance* PinInternal(const IRigidScene* Scene) const;`
- L40 _private member_ `FRigidObjectId Id;`
- L41 _private member_ `FRigidSceneId SceneId;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Physics` (scope `UE`)

### `Source/Runtime/Experimental/RigidPhysics/Public/RigidPhysics/RigidShapeInstanceSetup.h` (Public)


#### class `UE::Physics::FRigidShapeInstanceSetup`  
`class FRigidShapeInstanceSetup`  
_L16-34_
- L19 _public prototype_ `FRigidShapeInstanceSetup(const FAnyGeometry& InGeometry);`
- L21 _public member_ `FAnyGeometry Geometry;`
- L22 _public member_ `FTransform3f LocalTransform;`
- L23 _public member_ `Chaos::Filter::FShapeFilterData ShapeFilterData;`
- L24 _public member_ `Chaos::Filter::FInstanceData FilterInstanceData;`
- L25 _public member_ `ECollisionTraceFlag CollisionTraceType = ECollisionTraceFlag::CTF_UseDefault;`
- L26 _public member_ `TArray<FMaterialHandle> Materials;`
- L27 _public member_ `TArray<FMaterialMaskHandle> MaterialMaskHandles;`
- L28 _public member_ `TArray<uint32> MaterialMaskMaps;`
- L29 _public member_ `TArray<FMaterialHandle> MaterialMaskMapMaterials;`
- L30 _public member_ `bool bEnableSim = true;`
- L31 _public member_ `bool bEnableQuery = true;`
- L32 _public member_ `bool bEnableProbe = false;`
- L33 _public member_ `void* UserData = nullptr;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Physics` (scope `UE`)

### `Source/Runtime/Experimental/RigidPhysics/Public/RigidPhysics/RigidTyped.h` (Public)


#### class `UE::Physics::FRigidTypeId`  
`class FRigidTypeId`  
_L19-72_
- desc: A type ID for a rigid object to support downcasting and type checking. Each type-checkable class will contain a static FRigidTypeId. NOTE: Only support single inheritance because that's all we need for now and hopefully we can keep it that way. TODO_CHAOSAPI: Consider using a more robust Id generator (to avoid CRC collisions). TODO_CHAOSAPI: Consider using USTRUCT rather than this custom RTTI system.
- L22 _public function_ `FRigidTypeId(const TCHAR* InTypeName, const FRigidTypeId* InBaseTypeId) : TypeIdValue(FCrc::StrCrc32(InTypeName)) , BaseTypeId(InBaseTypeId) , TypeName(InTypeName)`
- L29 _public function_ `const uint64 GetValue() const`
- L34 _public function_ `const FString& GetTypeName() const`
- L39 _public function_ `const FRigidTypeId* GetBase() const`
- L44 _public function_ `inline bool IsCastableTo(const FRigidTypeId& Other) const`
- L69 _private member_ `uint64 TypeIdValue = 0;`
- L70 _private member_ `const FRigidTypeId* BaseTypeId = nullptr;`
- L71 _private member_ `const FString TypeName;`

#### class `UE::Physics::IRigidTyped`  
`class IRigidTyped`  
_L74-135_
- L77 _public prototype_ `IRigidTyped() = default;`
- L78 _public prototype_ `virtual ~IRigidTyped() = default;`
- L81 _public prototype_ `static const FRigidTypeId& GetStaticTypeId();` — Get the TypeId of this class
- L84 _public prototype_ `virtual const FRigidTypeId& GetTypeId() const;` — Get the leaf TypeId of this object
- L86 _public function_ `const FString& GetTypeName() const`
- L93 _public function_ `template <typename T> bool IsA() const` — Is T the same class or a base class of this object?
- L100 _public function_ `template <typename T> T* AsA()` — Try to cast this object to type T. Returns null if T is not a base class of this object.
- L111 _public function_ `template <typename T> const T* AsA() const` — Try to cast this object to type T. Returns null if T is not a base class of this object.
- L122 _public function_ `template <typename T> T* AsAChecked()` — Try to cast this object to type T. Assert T is a base class of this object.
- L130 _public function_ `template <typename T> const T* AsAChecked() const` — Try to cast this object to type T. Assert T is a base class of this object.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Physics` (scope `UE`)
- L58 _function_ `friend inline bool operator==(const FRigidTypeId& L, const FRigidTypeId& R)` (scope `UE::Physics`)
- L63 _function_ `friend inline bool operator<(const FRigidTypeId& L, const FRigidTypeId& R)` (scope `UE::Physics`)
- L139 _macro_ `#define UE_RIGIDPHYSICS_RIGIDTYPED_DECL(API, T) \`
- L143 _macro_ `#define UE_RIGIDPHYSICS_RIGIDTYPED_IMPL(T, TBASE) \`
