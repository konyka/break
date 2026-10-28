# Plugins / PhysicsToolsets

- module root: `Plugins/Experimental/Toolsets/PhysicsToolsets/Source/PhysicsToolsets`
- headers: 2; symbols: 60
- symbol kinds: class=2, delegate=1, enum=3, enumerator=9, member=17, prototype=26, struct=2
- PrivateDependencyModuleNames: AssetRegistry, CoreUObject, Engine, PhysicsUtilities, ToolsetRegistry, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/Toolsets/PhysicsToolsets/Source/PhysicsToolsets/Private/PhysicsToolsets/Module.h` (Private)


#### class `FPhysicsToolsetsModule`  
`class FPhysicsToolsetsModule : public IModuleInterface`  
_L10-15_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;`
- L14 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPhysicsToolsets, Log, Log);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPhysicsToolsets, Log, Log);`

### `Plugins/Experimental/Toolsets/PhysicsToolsets/Source/PhysicsToolsets/Private/PhysicsToolsets/PhysicsAssetToolset.h` (Private)


#### enum `EPhysicsShapeType`  
`enum class EPhysicsShapeType : uint8`  
_L16-21_
- reflection: `UENUM(BlueprintType)`
- desc: The type of collision primitive.
- L18 _public enumerator_ `Sphere`
- L19 _public enumerator_ `Capsule`
- L20 _public enumerator_ `Box`

#### enum `EBodyPhysicsMode`  
`enum class EBodyPhysicsMode : uint8`  
_L25-33_
- reflection: `UENUM(BlueprintType)`
- desc: Controls whether a physics body participates in world simulation.
- L28 _public enumerator_ `Default` — Follows the skeletal mesh component's simulation state.
- L30 _public enumerator_ `Kinematic` — Always kinematic: moves with animation and is not simulated.
- L32 _public enumerator_ `Simulated` — Always simulated, regardless of the component's state.

#### enum `EConstraintMotion`  
`enum class EConstraintMotion : uint8`  
_L37-45_
- reflection: `UENUM(BlueprintType)`
- desc: How a constraint axis may move.
- L40 _public enumerator_ `Free` — No restriction — the axis is completely free.
- L42 _public enumerator_ `Limited` — Restricted to the specified limit angle.
- L44 _public enumerator_ `Locked` — Fully locked — no movement on this axis.

#### struct `FPhysicsShapeInfo`  
`struct FPhysicsShapeInfo`  
_L52-97_
- reflection: `USTRUCT(BlueprintType)`
- desc: Describes a single collision primitive on a physics body. All positions and rotations are in the bone's local space.
- L58 _public member_ `FString ShapeName;` — `UPROPERTY(BlueprintReadWrite, Category = "PhysicsShape")` — User-defined name that uniquely identifies this shape on the body.
- L62 _public member_ `EPhysicsShapeType ShapeType = EPhysicsShapeType::Sphere;` — `UPROPERTY(BlueprintReadWrite, Category = "PhysicsShape")` — The type of collision primitive.
- L66 _public member_ `FVector Center = FVector::ZeroVector;` — `UPROPERTY(BlueprintReadWrite, Category = "PhysicsShape")` — Center position in bone-local space (cm).
- L73 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(BlueprintReadWrite, Category = "PhysicsShape")` — Orientation in bone-local space. For Capsule, Z is the long axis. Unused for Sphere.
- L77 _public member_ `float Radius = 0.f;` — `UPROPERTY(BlueprintReadWrite, Category = "PhysicsShape")` — Radius (cm). Used by Sphere and Capsule.
- L84 _public member_ `float Length = 0.f;` — `UPROPERTY(BlueprintReadWrite, Category = "PhysicsShape")` — Cylinder section length (cm). Used by Capsule only. Total capsule height = Length + 2 * Radius.
- L88 _public member_ `float ExtentX = 0.f;` — `UPROPERTY(BlueprintReadWrite, Category = "PhysicsShape")` — Full extent along local X (cm). Used by Box only.
- L92 _public member_ `float ExtentY = 0.f;` — `UPROPERTY(BlueprintReadWrite, Category = "PhysicsShape")` — Full extent along local Y (cm). Used by Box only.
- L96 _public member_ `float ExtentZ = 0.f;` — `UPROPERTY(BlueprintReadWrite, Category = "PhysicsShape")` — Full extent along local Z (cm). Used by Box only.

#### struct `FPhysicsConstraintInfo`  
`struct FPhysicsConstraintInfo`  
_L105-140_
- reflection: `USTRUCT(BlueprintType)`
- desc: Describes the angular limits for a single constraint between two bodies. Bone1 is the child bone; Bone2 is the parent bone. All limit angles are in degrees [0, 180].
- L111 _public member_ `FString Bone1Name;` — `UPROPERTY(BlueprintReadWrite, Category = "PhysicsConstraint")` — Name of the child bone.
- L115 _public member_ `FString Bone2Name;` — `UPROPERTY(BlueprintReadWrite, Category = "PhysicsConstraint")` — Name of the parent bone.
- L119 _public member_ `EConstraintMotion Swing1Motion = EConstraintMotion::Free;` — `UPROPERTY(BlueprintReadWrite, Category = "PhysicsConstraint")` — Motion type for Swing 1 (rotation around the body-local Y axis).
- L123 _public member_ `float Swing1LimitDegrees = 45.f;` — `UPROPERTY(BlueprintReadWrite, Category = "PhysicsConstraint")` — Swing 1 limit in degrees. Used when Swing1Motion is Limited.
- L127 _public member_ `EConstraintMotion Swing2Motion = EConstraintMotion::Free;` — `UPROPERTY(BlueprintReadWrite, Category = "PhysicsConstraint")` — Motion type for Swing 2 (rotation around the body-local Z axis).
- L131 _public member_ `float Swing2LimitDegrees = 45.f;` — `UPROPERTY(BlueprintReadWrite, Category = "PhysicsConstraint")` — Swing 2 limit in degrees. Used when Swing2Motion is Limited.
- L135 _public member_ `EConstraintMotion TwistMotion = EConstraintMotion::Free;` — `UPROPERTY(BlueprintReadWrite, Category = "PhysicsConstraint")` — Motion type for Twist (rotation around the body-local X axis).
- L139 _public member_ `float TwistLimitDegrees = 45.f;` — `UPROPERTY(BlueprintReadWrite, Category = "PhysicsConstraint")` — Twist limit in degrees. Used when TwistMotion is Limited.

#### class `UPhysicsAssetToolset`  
`class UPhysicsAssetToolset : public UToolsetDefinition`  
_L144-371_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UToolsetDefinition`
- desc: Provides tools for creating and managing Physics Assets.
- L158 _public prototype_ `static UPhysicsAsset* CreateFromMesh(const FString& MeshPath, bool bAssignToMesh);` — `UFUNCTION(Category = "PhysicsAsset", meta = (AICallable))` — Creates a physics asset from a skeletal mesh, auto-generating collision bodies for each bone. The asset is placed in the same folder as the mesh with the suffix "_PhysicsAsset". @param MeshPath Content-browser path to the skeletal mesh, e.g. '/Game/Characters/SKM_Hero'. @param bAssignToMesh If true, assigns the new physics asset to the mesh. @return The newly created physics asset.
- L166 _public prototype_ `static TArray<FString> GetBodyNames(UPhysicsAsset* PhysicsAsset);` — `UFUNCTION(Category = "PhysicsAsset", meta = (AICallable))` — Returns the bone name for each rigid body in a physics asset. @param PhysicsAsset The physics asset to query. @return A list of bone names, one per body.
- L175 _public prototype_ `static TArray<FPhysicsShapeInfo> GetBodyShapes( UPhysicsAsset* PhysicsAsset, const FString& BoneName);` — `UFUNCTION(Category = "PhysicsAsset", meta = (AICallable))` — Returns all collision shapes assigned to a body. @param PhysicsAsset The physics asset to query. @param BoneName The name of the bone whose body shapes to retrieve. @return A list of shape descriptors. Raises a script error if no body exists for the bone.
- L188 _public prototype_ `static void SetSphere( UPhysicsAsset* PhysicsAsset, const FString& BoneName, const FString& ShapeName, const FVector& Center, float Radius);` — `UFUNCTION(Category = "PhysicsAsset", meta = (AICallable))` — Adds or replaces a sphere collision primitive on a body. If any shape with the given name already exists on the body it is removed first. @param PhysicsAsset The physics asset to modify. @param BoneName The name of the bone whose body to modify. @param ShapeName A name that uniquely identifies this shape on the body. @param Center Center of the sphere in bone-local space (cm). @param Radius Radius of the sphere (cm). Must be greater than zero.
- L206 _public prototype_ `static void SetCapsule( UPhysicsAsset* PhysicsAsset, const FString& BoneName, const FString& ShapeName, const FVector& Center, const FRotator& Rotation, float Radius, float Length);` — `UFUNCTION(Category = "PhysicsAsset", meta = (AICallable))` — Adds or replaces a capsule collision primitive on a body. If any shape with the given name already exists on the body it is removed first. The capsule's long axis is its local Z after applying Rotation. @param PhysicsAsset The physics asset to modify. @param BoneName The name of the bone whose body to modify. @param ShapeName A name that uniquely identifies this shape on the body. @param Center Center of the capsule in bone-local space (cm). @param Rotation Orientation of the capsule in bone-local space. @param Radius Radius of the capsule end-caps (cm). Must be greater than zero. @param Length Length of the cylindrical section (cm). Must be non-negative. Total capsule height = Length + 2 * Radius.
- L224 _public prototype_ `static void SetBox( UPhysicsAsset* PhysicsAsset, const FString& BoneName, const FString& ShapeName, const FVector& Center, const FRotator& Rotation, float ExtentX, float ExtentY, float ExtentZ);` — `UFUNCTION(Category = "PhysicsAsset", meta = (AICallable))` — Adds or replaces a box collision primitive on a body. If any shape with the given name already exists on the body it is removed first. @param PhysicsAsset The physics asset to modify. @param BoneName The name of the bone whose body to modify. @param ShapeName A name that uniquely identifies this shape on the body. @param Center Center of the box in bone-local space (cm). @param Rotation Orientation of the box in bone-local space. @param ExtentX Full extent along local X (cm). Must be greater than zero. @param ExtentY Full extent along local Y (cm). Must be greater than zero. @param ExtentZ Full extent along local Z (cm). Must be greater than zero.
- L236 _public prototype_ `static void RemoveShape( UPhysicsAsset* PhysicsAsset, const FString& BoneName, const FString& ShapeName);` — `UFUNCTION(Category = "PhysicsAsset", meta = (AICallable))` — Removes a collision primitive from a body by name. @param PhysicsAsset The physics asset to modify. @param BoneName The name of the bone whose body to modify. @param ShapeName The name of the shape to remove.
- L249 _public prototype_ `static void AddBody(UPhysicsAsset* PhysicsAsset, const FString& BoneName);` — `UFUNCTION(Category = "PhysicsAsset", meta = (AICallable))` — Adds a new empty body for the given bone. @param PhysicsAsset The physics asset to modify. @param BoneName The name of the bone to add a body for.
- L258 _public prototype_ `static void RemoveBody(UPhysicsAsset* PhysicsAsset, const FString& BoneName);` — `UFUNCTION(Category = "PhysicsAsset", meta = (AICallable))` — Removes the body for the given bone along with any constraints that reference it. Raises a script error if PhysicsAsset is null or no body exists for BoneName. @param PhysicsAsset The physics asset to modify. @param BoneName The name of the bone whose body to remove.
- L270 _public prototype_ `static EBodyPhysicsMode GetBodyPhysicsMode( UPhysicsAsset* PhysicsAsset, const FString& BoneName);` — `UFUNCTION(Category = "PhysicsAsset", meta = (AICallable))` — Returns the physics simulation mode for the given body. @param PhysicsAsset The physics asset to query. @param BoneName The name of the bone whose body to query.
- L280 _public prototype_ `static void SetBodyPhysicsMode( UPhysicsAsset* PhysicsAsset, const FString& BoneName, EBodyPhysicsMode Mode);` — `UFUNCTION(Category = "PhysicsAsset", meta = (AICallable))` — Sets the physics simulation mode for the given body. @param PhysicsAsset The physics asset to modify. @param BoneName The name of the bone whose body to modify. @param Mode The desired simulation mode.
- L289 _public prototype_ `static float GetBodyMassScale(UPhysicsAsset* PhysicsAsset, const FString& BoneName);` — `UFUNCTION(Category = "PhysicsAsset", meta = (AICallable))` — Returns the mass-scale multiplier for the given body. @param PhysicsAsset The physics asset to query. @param BoneName The name of the bone whose body to query.
- L298 _public prototype_ `static void SetBodyMassScale( UPhysicsAsset* PhysicsAsset, const FString& BoneName, float MassScale);` — `UFUNCTION(Category = "PhysicsAsset", meta = (AICallable))` — Sets the mass-scale multiplier for the given body. @param PhysicsAsset The physics asset to modify. @param BoneName The name of the bone whose body to modify. @param MassScale Multiplier applied to the computed mass. Must be greater than zero.
- L311 _public prototype_ `static TArray<FPhysicsConstraintInfo> GetConstraints(UPhysicsAsset* PhysicsAsset);` — `UFUNCTION(Category = "PhysicsAsset", meta = (AICallable))` — Returns all constraints in the physics asset with their current angular limits. @param PhysicsAsset The physics asset to query. @return A list of constraint descriptors.
- L320 _public prototype_ `static void AddConstraint( UPhysicsAsset* PhysicsAsset, const FString& Bone1Name, const FString& Bone2Name);` — `UFUNCTION(Category = "PhysicsAsset", meta = (AICallable))` — Adds a new constraint between two bodies. Both bodies must already exist. @param PhysicsAsset The physics asset to modify. @param Bone1Name Name of the child bone. @param Bone2Name Name of the parent bone.
- L329 _public prototype_ `static void SetConstraintLimits(UPhysicsAsset* PhysicsAsset, FPhysicsConstraintInfo Info);` — `UFUNCTION(Category = "PhysicsAsset", meta = (AICallable))` — Updates the angular limits for an existing constraint. @param PhysicsAsset The physics asset to modify. @param Info Constraint descriptor. Bone1Name and Bone2Name identify the constraint.
- L338 _public prototype_ `static void RemoveConstraint( UPhysicsAsset* PhysicsAsset, const FString& Bone1Name, const FString& Bone2Name);` — `UFUNCTION(Category = "PhysicsAsset", meta = (AICallable))` — Removes the constraint between two bodies. @param PhysicsAsset The physics asset to modify. @param Bone1Name Name of the child bone. @param Bone2Name Name of the parent bone.
- L343 _private prototype_ `static USkeletalBodySetup* FindBody(UPhysicsAsset* PhysicsAsset, const FString& BoneName);` — Returns the body for BoneName, or nullptr if not found.
- L346 _private prototype_ `static void RemoveShapeByName(USkeletalBodySetup* Body, const FName& Name);` — Removes all shapes named Name from Body across all primitive types.
- L352 _private prototype_ `static USkeletalBodySetup* FindBodyForShape( UPhysicsAsset* PhysicsAsset, const FString& BoneName, const FString& ShapeName);` — Validates PhysicsAsset is non-null, ShapeName is non-empty, and a body exists for BoneName. Raises a script error and returns nullptr on the first failed check.
- L359 _private prototype_ `static FName BeginShapeEdit( UPhysicsAsset* PhysicsAsset, USkeletalBodySetup* Body, const FString& ShapeName);` — Marks PhysicsAsset and Body dirty, removes any existing shape named ShapeName, and returns the FName to assign to the new element.
- L363 _private prototype_ `static void NotifyAssetChanged(UPhysicsAsset* PhysicsAsset);` — Marks the asset dirty and triggers editor refresh.
- L369 _private prototype_ `static UPhysicsConstraintTemplate* FindConstraintTemplate( UPhysicsAsset* PhysicsAsset, const FString& Bone1Name, const FString& Bone2Name);` — Returns the constraint template between the two bones, or nullptr if not found. Tries both orderings of the bone names.
