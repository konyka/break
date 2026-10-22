# Runtime / ClothingSystemRuntimeNv

- module root: `Source/Runtime/ClothingSystemRuntimeNv`
- headers: 10; symbols: 100
- symbol kinds: class=6, delegate=1, enum=2, enumerator=6, function=9, member=42, namespace=2, prototype=30, struct=2
- PrivateDependencyModuleNames: Engine
- PublicDependencyModuleNames: ClothingSystemRuntimeCommon, ClothingSystemRuntimeInterface, Core, CoreUObject
- PublicIncludePathModuleNames: ClothingSystemRuntimeInterface

### `Source/Runtime/ClothingSystemRuntimeNv/Private/ClothConfigNvCustomVersion.h` (Private)


#### struct `FClothConfigNvCustomVersion`  
`struct FClothConfigNvCustomVersion`  
_L9-28_
- desc: Custom serialization version for config
- L24 _public member_ `const static FGuid GUID;` — The GUID for this custom version number
- L27 _private function_ `FClothConfigNvCustomVersion()`

#### enum `FClothConfigNvCustomVersion::Type`  
`enum Type`  
_L11-21_
- L14 _public enumerator_ `BeforeCustomVersionWasAdded = 0` — Before any version changes were made
- L16 _public enumerator_ `DeprecateLegacyStructureAndEnum = 1` — Deprecate legacy structure and enum that couldn't be redirected
- L19 _public enumerator_ `VersionPlusOne` — -----<new versions can be added above this line>-------------------------------------------------
- L20 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

### `Source/Runtime/ClothingSystemRuntimeNv/Public/ClothConfigNv.h` (Public)


#### struct `FClothConstraintSetupNv`  
`struct FClothConstraintSetupNv`  
_L19-46_
- reflection: `USTRUCT()`
- desc: Container for a constraint setup, these can be horizontal, vertical, shear and bend.
- L23 _public prototype_ `FClothConstraintSetupNv();`
- L26 _public prototype_ `void MigrateFrom(const FClothConstraintSetup_Legacy& Setup);` — Migrate from the legacy FClothConstraintSetup structure.
- L29 _public prototype_ `void MigrateTo(FClothConstraintSetup_Legacy& Setup) const;` — Migrate to the legacy FClothConstraintSetup structure.
- L33 _public member_ `float Stiffness;` — `UPROPERTY(EditAnywhere, Category=Constraint)` — How stiff this constraint is, this affects how closely it will follow the desired position
- L37 _public member_ `float StiffnessMultiplier;` — `UPROPERTY(EditAnywhere, Category = Constraint)` — A multiplier affecting the above value
- L41 _public member_ `float StretchLimit;` — `UPROPERTY(EditAnywhere, Category = Constraint)` — The hard limit on how far this constraint can stretch
- L45 _public member_ `float CompressionLimit;` — `UPROPERTY(EditAnywhere, Category = Constraint)` — The hard limit on how far this constraint can compress

#### enum `EClothingWindMethodNv`  
`enum class EClothingWindMethodNv : uint8`  
_L50-60_
- reflection: `UENUM()`
- desc: Cloth wind method.
- L54 _public enumerator_ `Legacy` — Use legacy wind mode, where accelerations are modified directly by the simulation with no regard for drag or lift
- L59 _public enumerator_ `Accurate` — Use updated wind calculation for NvCloth based solved taking into account drag and lift, this will require those properties to be correctly set in the clothing configuration

#### class `UClothConfigNv`  
`class UClothConfigNv : public UClothConfigCommon`  
_L65-220_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UClothConfigCommon`
- desc: Holds initial, asset level config for clothing actors.
- L69 _public prototype_ `UClothConfigNv();`
- L72 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — Set up custom version serialization.
- L75 _public prototype_ `virtual void PostLoad() override;` — Update the deprecated properties.
- L78 _public prototype_ `virtual void MigrateFrom(const FClothConfig_Legacy& ClothConfig) override;` — Migrate from the legacy FClothConfig structure.
- L81 _public prototype_ `virtual bool MigrateTo(FClothConfig_Legacy& ClothConfig) const override;` — Migrate to the legacy FClothConfig structure.
- L84 _public function_ `virtual bool NeedsSelfCollisionData() const override` — Return whether to pre-compute self collision data.
- L87 _public function_ `virtual bool NeedsInverseMasses() const override` — Return whether to pre-compute inverse masses.
- L90 _public function_ `virtual bool NeedsTethers() const override` — Return whether to pre-compute the long range attachment tethers.
- L93 _public function_ `virtual float GetSelfCollisionRadius() const override` — Return the collision radius required to calculate the self collision indices, or 0.f if self collision is disabled.
- L97 _public member_ `EClothingWindMethodNv ClothingWindMethod;` — `UPROPERTY(EditAnywhere, Category = ClothConfig)` — How wind should be processed, Accurate uses drag and lift to make the cloth react differently, legacy applies similar forces to all clothing without drag and lift (similar to APEX)
- L101 _public member_ `FClothConstraintSetupNv VerticalConstraint;` — `UPROPERTY(EditAnywhere, Category = ClothConfig)` — Constraint data for vertical constraints
- L105 _public member_ `FClothConstraintSetupNv HorizontalConstraint;` — `UPROPERTY(EditAnywhere, Category = ClothConfig)` — Constraint data for horizontal constraints
- L109 _public member_ `FClothConstraintSetupNv BendConstraint;` — `UPROPERTY(EditAnywhere, Category = ClothConfig)` — Constraint data for bend constraints
- L113 _public member_ `FClothConstraintSetupNv ShearConstraint;` — `UPROPERTY(EditAnywhere, Category = ClothConfig)` — Constraint data for shear constraints
- L117 _public member_ `float SelfCollisionRadius;` — `UPROPERTY(EditAnywhere, Category = ClothConfig)` — Size of self collision spheres centered on each vert
- L121 _public member_ `float SelfCollisionStiffness;` — `UPROPERTY(EditAnywhere, Category = ClothConfig)` — Stiffness of the spring force that will resolve self collisions
- L131 _public member_ `float SelfCollisionCullScale;` — `UPROPERTY(EditAnywhere, Category = ClothConfig, meta = (UIMin="0", ClampMin="0"))` — Scale to use for the radius of the culling checks for self collisions. Any other self collision body within the radius of this check will be culled. This helps performance with higher resolution meshes by reducing the number of colliding bodies within the cloth. Reducing this will have a negative effect on performance!
- L135 _public member_ `FVector Damping;` — `UPROPERTY(EditAnywhere, Category = ClothConfig)` — Damping of particle motion per-axis
- L139 _public member_ `float Friction;` — `UPROPERTY(EditAnywhere, Category = ClothConfig)` — Friction of the surface when colliding
- L143 _public member_ `float WindDragCoefficient;` — `UPROPERTY(EditAnywhere, Category = ClothConfig)` — Drag coefficient for wind calculations, higher values mean wind has more lateral effect on cloth
- L147 _public member_ `float WindLiftCoefficient;` — `UPROPERTY(EditAnywhere, Category = ClothConfig)` — Lift coefficient for wind calculations, higher values make cloth rise easier in wind
- L151 _public member_ `FVector LinearDrag;` — `UPROPERTY(EditAnywhere, Category = ClothConfig)` — Drag applied to linear particle movement per-axis
- L155 _public member_ `FVector AngularDrag;` — `UPROPERTY(EditAnywhere, Category = ClothConfig)` — Drag applied to angular particle movement, higher values should limit material bending (per-axis)
- L159 _public member_ `FVector LinearInertiaScale;` — `UPROPERTY(EditAnywhere, Category = ClothConfig, meta = (UIMin="0", UIMax="1", ClampMin="0", ClampMax="1"))` — Scale for linear particle inertia, how much movement should translate to linear motion (per-axis)
- L163 _public member_ `FVector AngularInertiaScale;` — `UPROPERTY(EditAnywhere, Category = ClothConfig, meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))` — Scale for angular particle inertia, how much movement should translate to angular motion (per-axis)
- L167 _public member_ `FVector CentrifugalInertiaScale;` — `UPROPERTY(EditAnywhere, Category = ClothConfig, meta = (UIMin = "0", UIMax = "1", ClampMin = "0", ClampMax = "1"))` — Scale for centrifugal particle inertia, how much movement should translate to angular motion (per-axis)
- L171 _public member_ `float SolverFrequency;` — `UPROPERTY(EditAnywhere, Category = ClothConfig, meta = (UIMin = "30", UIMax = "240", ClampMin = "30", ClampMax = "1000"))` — Frequency of the position solver, lower values will lead to stretchier, bouncier cloth
- L175 _public member_ `float StiffnessFrequency;` — `UPROPERTY(EditAnywhere, Category = ClothConfig)` — Frequency for stiffness calculations, lower values will degrade stiffness of constraints
- L179 _public member_ `float GravityScale;` — `UPROPERTY(EditAnywhere, Category = ClothConfig, meta = (EditCondition = "!bUseGravityOverride"))` — Scale of gravity effect on particles
- L183 _public member_ `FVector GravityOverride;` — `UPROPERTY(EditAnywhere, Category = ClothConfig, meta = (EditCondition = "bUseGravityOverride"))` — Direct gravity override value
- L187 _public member_ `bool bUseGravityOverride;` — `UPROPERTY(EditAnywhere, Category = ClothConfig, meta = (InlineEditConditionToggle))` — Use gravity override value vs gravity scale
- L191 _public member_ `float TetherStiffness;` — `UPROPERTY(EditAnywhere, Category = ClothConfig)` — Scale for stiffness of particle tethers between each other
- L195 _public member_ `float TetherLimit;` — `UPROPERTY(EditAnywhere, Category = ClothConfig)` — Scale for the limit of particle tethers (how far they can separate)
- L199 _public member_ `float CollisionThickness;` — `UPROPERTY(EditAnywhere, Category = ClothConfig)` — 'Thickness' of the simulated cloth, used to adjust collisions
- L203 _public member_ `float AnimDriveSpringStiffness;` — `UPROPERTY(EditAnywhere, Category = ClothConfig)` — Default spring stiffness for anim drive if an anim drive is in use
- L207 _public member_ `float AnimDriveDamperStiffness;` — `UPROPERTY(EditAnywhere, Category = ClothConfig)` — Default damper stiffness for anim drive if an anim drive is in use
- L211 _public member_ `EClothingWindMethod_Legacy WindMethod_DEPRECATED;` — `UPROPERTY()` — Deprecated properties using old legacy structure and enum that couldn't be redirected
- L213 _public member_ `FClothConstraintSetup_Legacy VerticalConstraintConfig_DEPRECATED;` — `UPROPERTY()`
- L215 _public member_ `FClothConstraintSetup_Legacy HorizontalConstraintConfig_DEPRECATED;` — `UPROPERTY()`
- L217 _public member_ `FClothConstraintSetup_Legacy BendConstraintConfig_DEPRECATED;` — `UPROPERTY()`
- L219 _public member_ `FClothConstraintSetup_Legacy ShearConstraintConfig_DEPRECATED;` — `UPROPERTY()`

### `Source/Runtime/ClothingSystemRuntimeNv/Public/ClothPhysicalMeshDataNv_Legacy.h` (Public)


#### class `UClothPhysicalMeshDataNv_Legacy`  
`class UClothPhysicalMeshDataNv_Legacy: public UClothPhysicalMeshDataBase_Legacy`  
_L18-40_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UClothPhysicalMeshDataBase_Legacy`
- desc: Deprecated, use FClothPhysicalMeshData instead. NV specific spatial simulation data for a mesh.
- L22 _public prototype_ `UClothPhysicalMeshDataNv_Legacy();`
- L23 _public prototype_ `virtual ~UClothPhysicalMeshDataNv_Legacy();`
- L27 _public member_ `TArray<float> MaxDistances;` — `UPROPERTY()` — The distance that each vertex can move away from its reference (skinned) position
- L31 _public member_ `TArray<float> BackstopDistances;` — `UPROPERTY()` — Distance along the plane of the surface that the particles can travel (separation constraint)
- L35 _public member_ `TArray<float> BackstopRadiuses;` — `UPROPERTY()` — Radius of movement to allow for backstop movement
- L39 _public member_ `TArray<float> AnimDriveMultipliers;` — `UPROPERTY()` — Strength of anim drive per-particle (spring driving particle back to skinned location

### `Source/Runtime/ClothingSystemRuntimeNv/Public/ClothingActor.h` (Public)


#### class `FClothingActorBase`  
`class FClothingActorBase`  
_L8-14_
- desc: Base clothing actor just needs a link back to its parent asset, everything else defined by derived simulation
- L13 _public member_ `UClothingAssetCommon* AssetCreatedFrom;` — Link back to parent asset

### `Source/Runtime/ClothingSystemRuntimeNv/Public/ClothingSimulationFactoryNv.h` (Public)


#### class `UClothingSimulationFactoryNv`  
`class UClothingSimulationFactoryNv final : public UClothingSimulationFactory`  
_L23-37_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UClothingSimulationFactory`
- L28 _public prototype_ `virtual IClothingSimulationInterface* CreateSimulation() const override;`
- L29 _public prototype_ `virtual void DestroySimulation(IClothingSimulationInterface* InSimulation) const override;`
- L30 _public prototype_ `virtual bool SupportsAsset(const UClothingAssetBase* InAsset) const override;`
- L32 _public prototype_ `virtual bool SupportsRuntimeInteraction() const override;`
- L33 _public prototype_ `virtual UClothingSimulationInteractor* CreateInteractor() override;`
- L35 _public prototype_ `virtual TArrayView<const TSubclassOf<UClothConfigBase>> GetClothConfigClasses() const override;`
- L36 _public prototype_ `virtual const UEnum* GetWeightMapTargetEnum() const override;`

### `Source/Runtime/ClothingSystemRuntimeNv/Public/ClothingSimulationInteractorNv.h` (Public)


#### class `UClothingSimulationInteractorNv`  
`class UClothingSimulationInteractorNv : public UClothingSimulationInteractor`  
_L26-56_
- reflection: `UE_DEPRECATED(5.1, "NvCloth is no longer a supported clothing simlation provider, prefer the Chaos simulation moving forward.")`
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UClothingSimulationInteractor`
- L33 _public prototype_ `virtual void Sync(IClothingSimulationInterface* InSimulation, const IClothingSimulationContext* InContext) override;` — UClothingSimulationInteractor Interface
- L35 _public prototype_ `virtual void PhysicsAssetUpdated() override;`
- L36 _public prototype_ `virtual void ClothConfigUpdated() override;`
- L37 _public prototype_ `virtual void SetAnimDriveSpringStiffness(float InStiffness) override;`
- L38 _public prototype_ `virtual void EnableGravityOverride(const FVector& InVector) override;`
- L39 _public prototype_ `virtual void DisableGravityOverride() override;`
- L42 _public function_ `virtual void SetNumIterations(int32 ) override` — TODO: These new functions are currently unimplemented
- L43 _public function_ `virtual void SetMaxNumIterations(int32 ) override`
- L44 _public function_ `virtual void SetNumSubsteps(int32 ) override`
- L49 _public prototype_ `void SetAnimDriveDamperStiffness(float InStiffness);` — `UFUNCTION(BlueprintCallable, Category=ClothingSimulation)` — Set the stiffness of the resistive damping force for anim drive
- L53 _protected function_ `virtual UClothingInteractor* CreateClothingInteractor() override`

#### Free symbols / members of external scopes

- L22 _delegate_ `DECLARE_DELEGATE_TwoParams(NvInteractorCommand, FClothingSimulationNv*, FClothingSimulationContextNv*) class UE_DEPRECATED(5.1, "NvCloth is no longer a supported cl` — Command signature for handling synced command buffer

### `Source/Runtime/ClothingSystemRuntimeNv/Public/ClothingSimulationNv.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/ClothingSystemRuntimeNv/Public/ClothingSystemRuntimeModuleNv.h` (Public)


#### class `FClothingSystemRuntimeModuleNv`  
`class FClothingSystemRuntimeModuleNv : public IModuleInterface, public IClothingSimulationFactoryClassProvider`  
_L18-37_
- inherits: `IModuleInterface,IClothingSimulationFactoryClassProvider`
- L23 _public prototype_ `FClothingSystemRuntimeModuleNv();`
- L25 _public prototype_ `virtual void StartupModule() override;`
- L26 _public prototype_ `virtual void ShutdownModule() override;`
- L28 _public prototype_ `nv::cloth::Factory* GetSoftwareFactory();`
- L29 _public prototype_ `nv::cloth::ClothMeshQuadifier* GetMeshQuadifier();`
- L32 _public prototype_ `virtual TSubclassOf<UClothingSimulationFactory> GetClothingSimulationFactoryClass() const override;` — IClothingSimulationFactoryClassProvider Interface

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace nv`
- L11 _namespace_ `namespace cloth` (scope `nv`)

### `Source/Runtime/ClothingSystemRuntimeNv/Public/NvClothIncludes.h` (Public)
_(no declarations extracted)_

### `Source/Runtime/ClothingSystemRuntimeNv/Public/NvClothSupport.h` (Public)
_(no declarations extracted)_
